/*
 * LiDAR board breadboard tests - OpenField (Team 1), Landon Kuhman
 * Target : PIC18F57Q43 Curiosity Nano (DM164150), XC8 compiler, no MCC needed
 *
 * Change TEST_STAGE, then Build + Program:
 *   2 = debug LEDs + debounced button        (RD0 red, RD1 green, RA4 button)
 *   3 = Waveshare D500 LiDAR packet reader   (LiDAR TX -> RC7, UART1 230400)
 *   4 = team UART on the ribbon pins         (RB0 = TX, RB1 = RX, UART2 115200)
 *   5 = LiDAR + status LEDs + button, USB-powered (stage 3 plus: press SW1 to
 *       print the closest object in each 30-degree sector)
 *   6 = point-cloud bridge: forwards the D500 data stream to the PC at 230400
 *       baud for lidar_view.py (green LED = valid packets, red = heartbeat)
 *
 * Every stage prints to the Nano's USB virtual COM port:
 *   UART5, RF0 = TX, RF1 = RX, 115200 baud 8N1 (230400 in stage 6)
 */
#define TEST_STAGE 6

#pragma config FEXTOSC = OFF            // no external crystal
#pragma config RSTOSC  = HFINTOSC_64MHZ // run from the 64 MHz internal oscillator
#pragma config WDTE    = OFF            // watchdog off
#pragma config LVP     = ON             // low-voltage programming (Curiosity Nano)

#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#define _XTAL_FREQ 64000000UL

#define LED_DBG   LATDbits.LATD0        // red LED, 1 = on
#define LED_STAT  LATDbits.LATD1        // green LED, 1 = on
#define BTN_IN    PORTAbits.RA4         // 0 = pressed (active-low)

/* ---------------- USB serial (UART5 -> Nano debugger CDC) ---------------- */
static void usb_uart_init(void)
{
    ANSELFbits.ANSELF0 = 0; ANSELFbits.ANSELF1 = 0;
    TRISFbits.TRISF0 = 0;               // RF0 = TX out
    TRISFbits.TRISF1 = 1;               // RF1 = RX in
    RF0PPS   = 0x2C;                    // RF0 <- UART5 TX
    U5RXPPS  = 0x29;                    // UART5 RX <- RF1 (port F = 101, pin 1)
#if TEST_STAGE == 6
    U5BRGL = 68;  U5BRGH = 0;           // 64 MHz / (4 x 69) = 231884 baud, same as the LiDAR UART
#else
    U5BRGL = 138; U5BRGH = 0;           // 64 MHz / (4 x 139) = 115108 baud
#endif
    U5CON0 = 0xB0;                      // BRGS=1, TXEN=1, RXEN=1, async 8-bit
    U5CON2 = 0x80;                      // RUNOVF=1: stay in sync after overflow
    U5CON1 = 0x80;                      // ON
}
void putch(char c)                      // printf() sends through this
{
    while (U5FIFObits.TXBF) { }
    U5TXB = (uint8_t)c;
}

/* ---------------- LEDs and button ---------------- */
static void io_init(void)
{
    ANSELD = 0x00;
    TRISDbits.TRISD0 = 0; TRISDbits.TRISD1 = 0;
    LED_DBG = 0; LED_STAT = 0;
    ANSELAbits.ANSELA4 = 0;
    TRISAbits.TRISA4 = 1;               // button input (external 10k pull-up + RC debounce)
    ANSELCbits.ANSELC6 = 0;
    TRISCbits.TRISC6 = 1;               // RC6 = LiDAR PWM pin: high-Z so the D500 uses its internal 10 Hz speed control
}

#if TEST_STAGE == 2
/* ===================== STAGE 2: LEDs + button ===================== */
static void stage_run(void)
{
    uint16_t ms = 0, presses = 0;
    uint8_t last = 1;
    printf("\r\nStage 2: red LED blinks, green LED = button held, one count per press\r\n");
    while (1) {
        __delay_ms(1);
        if (++ms >= 500) { ms = 0; LED_DBG = !LED_DBG; }   // 1 Hz heartbeat
        uint8_t now = BTN_IN;
        LED_STAT = !now;                                    // green while pressed
        if (last == 1 && now == 0) {                        // falling edge = press
            presses++;
            printf("Button press #%u\r\n", presses);
        }
        last = now;
    }
}
#endif

#if TEST_STAGE == 3 || TEST_STAGE == 5 || TEST_STAGE == 6
/* ============ STAGE 3 / 5 / 6: D500 LiDAR (5 adds sector printout on SW1) ============ */
static uint8_t crc_table[256];
static void crc_init(void)              // CRC-8, polynomial 0x4D (LDRobot protocol)
{
    for (uint16_t i = 0; i < 256; i++) {
        uint8_t c = (uint8_t)i;
        for (uint8_t b = 0; b < 8; b++)
            c = (c & 0x80) ? (uint8_t)((c << 1) ^ 0x4D) : (uint8_t)(c << 1);
        crc_table[i] = c;
    }
}
static void lidar_uart_init(void)
{
    ANSELCbits.ANSELC7 = 0;
    TRISCbits.TRISC7 = 1;               // RC7 = LiDAR TX in
    U1RXPPS = 0x17;                     // UART1 RX <- RC7 (port C = 010, pin 7)
    U1BRGL = 68; U1BRGH = 0;            // 64 MHz / (4 x 69) = 231884 baud (+0.6%)
    U1CON0 = 0x90;                      // BRGS=1, RXEN=1, async 8-bit (receive only)
    U1CON2 = 0x80;                      // RUNOVF=1
    U1CON1 = 0x80;                      // ON
}

#define PKT_LEN 47
static uint8_t  pkt[PKT_LEN];
static uint16_t good = 0, bad = 0, speed_dps = 0;
static uint16_t front_mm = 0, near_mm = 0xFFFF, near_deg = 0;
static uint16_t sector_mm[12];                         // closest return per 30-degree sector

static uint16_t rd16(uint8_t i) { return (uint16_t)pkt[i] | ((uint16_t)pkt[i + 1] << 8); }

static void handle_packet(void)
{
    uint32_t start = rd16(4), end = rd16(42);          // angles in 0.01 deg
    if (end < start) end += 36000UL;                   // packet crosses 0 deg
    uint32_t step = (end - start) / 11UL;              // 12 points per packet
    speed_dps = rd16(2);
    for (uint8_t i = 0; i < 12; i++) {
        uint16_t mm = rd16((uint8_t)(6 + 3 * i));
        if (mm == 0) continue;                         // 0 = no return
        uint32_t a = (start + step * i) % 36000UL;
        uint16_t deg = (uint16_t)(a / 100UL);
        if (deg <= 5 || deg >= 355) front_mm = mm;     // straight ahead (+/- 5 deg)
        if (mm < near_mm) { near_mm = mm; near_deg = deg; }
        uint8_t s = (uint8_t)(deg / 30);
        if (s < 12 && (sector_mm[s] == 0 || mm < sector_mm[s])) sector_mm[s] = mm;
    }
    good++;
}

#if TEST_STAGE == 6
/* Stage 6: forward every LiDAR byte to the PC unchanged, and check packets on the way */
static void stage_run(void)
{
    uint8_t idx = 0, crc = 0;
    uint16_t stat_timer = 0, pk = 0;
    crc_init();
    lidar_uart_init();
    while (1) {
        if (U1ERRIRbits.RXFOIF) U1ERRIRbits.RXFOIF = 0;
        if (!U1FIFObits.RXBE) {
            uint8_t b = U1RXB;
            while (U5FIFObits.TXBF) { }                    // USB UART is slightly faster, so this rarely waits
            U5TXB = b;
            if (idx == 0) {
                if (b == 0x54) { pkt[0] = b; crc = crc_table[b]; idx = 1; }
            } else if (idx == 1) {
                if (b == 0x2C) { pkt[1] = b; crc = crc_table[crc ^ b]; idx = 2; }
                else if (b == 0x54) { pkt[0] = b; crc = crc_table[b]; idx = 1; }
                else idx = 0;
            } else if (idx < PKT_LEN - 1) {
                pkt[idx++] = b; crc = crc_table[crc ^ b];
            } else {
                idx = 0;
                if (b == crc) {
                    LED_STAT = 1; stat_timer = 20000;
                    if (++pk >= 400) { pk = 0; LED_DBG = !LED_DBG; }   // ~1 s heartbeat
                }
            }
        } else if (stat_timer && --stat_timer == 0) {
            LED_STAT = 0;                                  // no valid packets recently
        }
    }
}
#else
static void stage_run(void)
{
    uint8_t idx = 0, crc = 0;
    uint16_t stat_timer = 0;
    uint32_t idle = 0;
    crc_init();
    lidar_uart_init();
    printf("\r\nStage %u: D500 LiDAR on RC7 @ 230400 baud\r\n", TEST_STAGE);
#if TEST_STAGE == 5
    uint8_t btn_last = 1;
    printf("Press SW1 for a 360-degree sector printout\r\n");
#endif
    while (1) {
#if TEST_STAGE == 5
        uint8_t btn = BTN_IN;
        if (btn_last == 1 && btn == 0) {                   // SW1 pressed
            printf("Sectors (closest mm, 0 = nothing):");
            for (uint8_t s = 0; s < 12; s++) { printf(" %u:%u", s * 30, sector_mm[s]); sector_mm[s] = 0; }
            printf("\r\n");
        }
        btn_last = btn;
#endif
        if (U1ERRIRbits.RXFOIF) U1ERRIRbits.RXFOIF = 0;   // clear overflow (data lost while printing)
        if (!U1FIFObits.RXBE) {                            // a byte is waiting
            uint8_t b = U1RXB;
            idle = 0;
            if (idx == 0) {
                if (b == 0x54) { pkt[0] = b; crc = crc_table[b]; idx = 1; }
            } else if (idx == 1) {
                if (b == 0x2C) { pkt[1] = b; crc = crc_table[crc ^ b]; idx = 2; }
                else if (b == 0x54) { pkt[0] = b; crc = crc_table[b]; idx = 1; }
                else idx = 0;
            } else if (idx < PKT_LEN - 1) {
                pkt[idx++] = b; crc = crc_table[crc ^ b];
            } else {                                       // last byte = CRC
                pkt[idx] = b; idx = 0;
                if (b == crc) { handle_packet(); LED_STAT = 1; stat_timer = 20000; }
                else bad++;
            }
            if (good >= 400) {                             // ~1 s of data (about 417 packets/s)
                LED_DBG = !LED_DBG;                        // heartbeat
                printf("scan %u.%u Hz | front %u mm | closest %u mm @ %u deg | good %u, CRC errors %u\r\n",
                       speed_dps / 360, (speed_dps % 360) * 10 / 360,
                       front_mm, near_mm, near_deg, good, bad);
                good = 0; bad = 0; near_mm = 0xFFFF; front_mm = 0;
                idx = 0;                                   // resync after the print
            }
        } else {
            if (stat_timer && --stat_timer == 0) LED_STAT = 0;   // no good packet recently
            if (++idle == 3000000UL) {                     // roughly 1-2 s with no bytes
                idle = 0; LED_STAT = 0; LED_DBG = !LED_DBG;
                printf("No LiDAR data - check 5 V, GND and TX -> RC7\r\n");
            }
        }
    }
}
#endif /* stage 3/5 */
#endif

#if TEST_STAGE == 4
/* ===================== STAGE 4: team UART (ribbon pins 1/2) ===================== */
static char rxbuf[64];
static uint8_t rxn = 0;

static void team_uart_init(void)
{
    ANSELBbits.ANSELB0 = 0; ANSELBbits.ANSELB1 = 0;
    TRISBbits.TRISB0 = 0;               // RB0 = TX out (ribbon pin 2)
    TRISBbits.TRISB1 = 1;               // RB1 = RX in  (ribbon pin 1)
    WPUBbits.WPUB1 = 1;                 // internal pull-up stands in for R4 on the breadboard
    RB0PPS  = 0x23;                     // RB0 <- UART2 TX
    U2RXPPS = 0x09;                     // UART2 RX <- RB1 (port B = 001, pin 1)
    U2BRGL = 138; U2BRGH = 0;           // 115200 baud (agree on this with the team)
    U2CON0 = 0xB0;                      // BRGS=1, TXEN=1, RXEN=1
    U2CON2 = 0x80;
    U2CON1 = 0x80;
}
static void team_poll(void)             // move received bytes into rxbuf
{
    if (U2ERRIRbits.RXFOIF) U2ERRIRbits.RXFOIF = 0;
    while (!U2FIFObits.RXBE) {
        char c = (char)U2RXB;
        if (rxn < sizeof(rxbuf) - 1) rxbuf[rxn++] = c;
    }
}
static void team_send(const char *s)
{
    while (*s) {
        while (U2FIFObits.TXBF) team_poll();   // keep reading while sending
        U2TXB = (uint8_t)*s++;
    }
}
static void stage_run(void)
{
    char msg[24];
    uint16_t n = 0;
    team_uart_init();
    printf("\r\nStage 4: sending on RB0 every second, printing anything received on RB1\r\n");
    while (1) {
        sprintf(msg, "LIDAR,%u\r\n", n++);
        team_send(msg);
        LED_DBG = !LED_DBG;
        for (uint16_t t = 0; t < 1000; t++) { __delay_ms(1); team_poll(); }
        if (rxn) {
            rxbuf[rxn] = 0;
            printf("RX from team bus: %s", rxbuf);
            LED_STAT = 1;
            rxn = 0;
        } else {
            printf("Sent %s", msg);
            printf("  (nothing received - check the RB0/RB1 wiring)\r\n");
            LED_STAT = 0;
        }
    }
}
#endif

void main(void)
{
    io_init();
    usb_uart_init();
    __delay_ms(100);
    printf("\r\nOpenField LiDAR board - breadboard test, stage %u\r\n", TEST_STAGE);
    stage_run();
}
