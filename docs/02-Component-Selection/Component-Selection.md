---
title: Component Selection
---

## Overview

This page compares candidate parts for every major block in my **LiDAR subsystem** of OpenField (Team 1, Group 101), the open-source line-marking robot. The LiDAR subsystem is a daughter board with its own PIC18F57Q43 Curiosity Nano. It reads a 360° ToF LiDAR, reduces the scan to the data the robot needs for navigation, and sends it to the MASTER board over UART (Connector 1, pins 1–2). See the [Individual Block Diagram](../01-Block-Diagram/Block-Diagram.md) for how the blocks connect.

The major components on this board are:

1. **LiDAR Subsystem – Ranging sensor (ToF LiDAR)**
2. **LiDAR Subsystem – +5 V voltage regulator** (the "5V step-down" block)
3. **LiDAR Subsystem – Power source** (shared team battery that feeds the regulator)

The PIC18F57Q43 Curiosity Nano was selected for us and is not compared here (it does appear in the [Power Budget](../05-Power-Budget/Power-Budget.md)).

### Design requirements that drive these choices

| Requirement | Why it matters for the LiDAR board |
| --- | --- |
| Works outdoors on grass, concrete and job sites | OpenField marks sports fields, floor plans and road markings, so the sensor must tolerate bright ambient light and dust |
| 360° obstacle and landmark detection out to several meters | The robot needs to see walls, stakes, cones and people around it, not just straight ahead |
| Interfaces directly with the PIC18F57Q43 | UART at a rate the 8-bit PIC can parse, 3.3 V logic so no level shifting is needed |
| Single +5 V supply from a linear regulator | Course requirement; keeps the board to one rail |
| Open-source friendly and commonly available | Core to the OpenField pitch against Dusty Robotics and HP SitePrint |
| Through-hole parts where practical | RAS 304 boards are hand-soldered |

---

## 1. LiDAR Subsystem – Ranging Sensor (ToF LiDAR)

| **Solution** | **Pros** | **Cons** |
| --- | --- | --- |
| <img src="https://cdn-shop.adafruit.com/970x728/4010-07.jpg" alt="RPLIDAR A1M8" width="220"><br>**Option 1.**<br>Slamtec RPLIDAR A1M8, 360° laser scanner<br>&#92;&#36;99.95/each<br>[RPLIDAR A1 at Adafruit](https://www.adafruit.com/product/4010)<br>[A1M8 datasheet](https://cdn-shop.adafruit.com/product-files/4010/4010_datasheet.pdf) | \* Full 360° scan at 2–10 Hz with 8,000 samples/s and 1° angular resolution, enough to map the area around the robot<br>\* 12 m range covers a typical room or a section of a field<br>\* Very large user base and open-source SDK, so example parsing code is easy to find<br>\* 3.3 V TTL UART at 115200 baud, which the PIC can read directly | \* Laser triangulation ranging; the datasheet only rates it for outdoor use without direct sunlight, which conflicts with our sports-field and road-marking use cases<br>\* Highest current draw of the options: 300–350 mA for the core plus about 100 mA for the motor, with a 500–600 mA start-up surge<br>\* Large and heavy for our 3D-printed body (98.5 mm wide, 170 g)<br>\* Exposed spinning head collects dust and debris on a job site<br>\* Operating range only 0–45 °C |
| <img src="https://www.waveshare.com/media/catalog/product/cache/1/image/800x800/9df78eab33525d08d6e5fb8d27136e95/d/5/d500-lidar-kit-1.jpg" alt="D500 LiDAR Kit" width="220"><br>**Option 2.**<br>Waveshare D500 LiDAR Kit (LDRobot STL-19P, successor to the LD19)<br>about &#92;&#36;50/each<br>[D500 / LD19-class LiDAR on Amazon](https://www.amazon.com/dp/B0GSTXW158)<br>[D500 wiki / protocol manual](https://www.waveshare.com/wiki/D500_LiDAR_Kit) | \* About half the price of the RPLIDAR A1 (about &#92;&#36;50 vs. &#92;&#36;99.95), which keeps the team inside its budget<br>\* Direct time-of-flight (DTOF) ranging rated for 60 klux ambient light, much better suited to outdoor work than triangulation<br>\* Full 360° at 10 Hz, 5,000 measurements/s, 0.03–12 m range<br>\* Single +5 V supply runs both the sensor and its motor (290 mA working current), so only one rail is needed<br>\* Streams data on its own over a 3.3 V UART (230400 baud, 8N1); no start command is needed, which keeps PIC firmware simple<br>\* Built-in motor speed control, with an optional PWM input if we want to set the speed ourselves<br>\* Compact (38.6 × 38.6 × 33.5 mm), fits on top of the robot body<br>\* Supported by open-source ROS / Python drivers | \* Transmit-only interface; the PIC cannot request status or change settings except motor speed<br>\* 230400 baud stream uses about 85% of the UART's capacity, so the PIC must parse it with an interrupt or DMA, not polling<br>\* Data is in a vendor packet format with a CRC that we have to implement in C<br>\* The older LD19 version of this sensor is already discontinued, so we should buy a spare early<br>\* 60 klux still falls short of full summer sun (~100 klux), so a small sun hood may be needed |
| <img src="https://www.waveshare.com/media/catalog/product/cache/1/image/800x800/9df78eab33525d08d6e5fb8d27136e95/t/f/tf-luna-lidar-range-sensor-1.jpg" alt="TF-Luna" width="200"><br><img src="https://cdn-shop.adafruit.com/970x728/169-06.jpg" alt="SG92R micro servo" width="140"><br>**Option 3 (custom).**<br>Sweeping scanner built from a Benewake TF-Luna single-point LiDAR on a TowerPro SG92R micro servo<br>&#92;&#36;30.99 + &#92;&#36;5.95 = about &#92;&#36;37<br>[TF-Luna at Waveshare](https://www.waveshare.com/tf-luna-lidar-range-sensor.htm) ([wiki](https://www.waveshare.com/wiki/TF-Luna_LiDAR_Range_Sensor))<br>[SG92R servo at Adafruit](https://www.adafruit.com/product/169) | \* Lowest cost of the options (about &#92;&#36;37)<br>\* TF-Luna is rated for 70 klux ambient light, indoors and outdoors<br>\* Low sensor current (70 mA average, 150 mA peak)<br>\* Fully open design; we control the scan pattern and can point the sensor where the robot needs it (e.g. ahead only)<br>\* The PIC can drive the servo with a standard 50 Hz PWM output | \* Covers about 180°, not 360°; the robot is blind behind itself<br>\* Very slow scan: at 250 readings/s and 0.1 s/60° the servo gives roughly one 180° sweep every 0.3–0.6 s with 2–3° spacing between points<br>\* Range drops to 2.5 m on dark (10%) surfaces such as asphalt<br>\* Servo gears wear out under continuous sweeping, and servo current spikes add noise to the +5 V rail<br>\* We must design and print a mount and calibrate the servo angle, which adds mechanical work and error |

**Choice:** Option 2: Waveshare D500 LiDAR Kit (LDRobot STL-19P)

**Rationale:** OpenField works outside, so sunlight tolerance is the deciding requirement. The RPLIDAR A1 uses triangulation and is only rated for use without direct sunlight. The D500 uses direct time-of-flight and is rated for 60 klux, while still giving the full 360° view that the custom servo scanner cannot. The D500 also draws less current than the A1 (290 mA vs. about 400 mA working and up to 600 mA at start-up), runs from the same +5 V rail as the Curiosity Nano, and outputs 3.3 V UART that connects straight to a PIC pin with no level shifter. Because it streams continuously without a start command, the PIC only needs a UART receive interrupt (or DMA) and a packet parser, which fits in the PIC18F57Q43's 8 KB of RAM (a 360-bin distance table is 720 bytes). It also comes with a published wiki and protocol manual, so there is real documentation to design against. Since the earlier LD19 has already been discontinued, the team should order a spare when we order the first unit.

---

## 2. LiDAR Subsystem – +5 V Voltage Regulator

The regulator takes the team battery voltage down to the +5 V that powers the D500 and the Curiosity Nano's VBUS pin. The budgeted load is 502.5 mA including the 25% margin (see the [Power Budget](../05-Power-Budget/Power-Budget.md)).

| **Solution** | **Pros** | **Cons** |
| --- | --- | --- |
| <img src="https://cdn-shop.adafruit.com/970x728/2164-00.jpg" alt="L7805CV" width="200"><br>**Option 1.**<br>STMicroelectronics L7805CV, 5 V 1.5 A linear regulator (TO-220)<br>&#92;&#36;0.75/each<br>[7805 at Adafruit](https://www.adafruit.com/product/2164)<br>[L7805CV datasheet](https://cdn-shop.adafruit.com/product-files/2164/L7805CV.pdf) | \* Inexpensive and in stock almost everywhere, including the lab<br>\* 1.5 A rating gives three times the current we need<br>\* Through-hole TO-220 package is easy to solder and bolt to a heatsink<br>\* Low 6 mA quiescent current<br>\* Internal current limit and thermal shutdown | \* About 2 V dropout, so the input must stay above 7 V; it would not work if the team picks a 2S (7.4 V) pack<br>\* No reverse-battery protection; a backwards battery plug can destroy the regulator and the LiDAR<br>\* Like any linear regulator, it burns the extra voltage as heat (about 3.8 W at 12.6 V in), so it needs a heatsink |
| <img src="https://www.electrokit.com/upload/product/common/TO-220.jpg" alt="LM2940CT-5.0" width="200"><br>**Option 2.**<br>Texas Instruments LM2940CT-5.0/NOPB, 5 V 1 A low-dropout regulator (TO-220)<br>&#92;&#36;1.94/each<br>[LM2940CT-5.0 at DigiKey](https://www.digikey.com/en/products/detail/texas-instruments/LM2940CT-5-0-NOPB/32575)<br>[LM2940 product page and datasheet](https://www.ti.com/product/LM2940-N) | \* Low dropout (0.5 V typical, 1 V max at 1 A), so it works from any pack above 6 V: 2S or 3S LiPo, 9.6 V NiMH or 12 V lead-acid<br>\* Built-in reverse-battery protection, which protects the LiDAR from a backwards plug<br>\* 1 A rating is about twice the 502.5 mA we need<br>\* 26 V maximum input survives charger and motor-noise spikes<br>\* Same through-hole TO-220 footprint as the 7805 | \* Costs more than the 7805 (still under &#92;&#36;2)<br>\* Higher quiescent current (10–15 mA), which slightly shortens battery life<br>\* Needs a larger output capacitor (22 µF or more) for stability, per the datasheet<br>\* Still dissipates about 3.9 W at a full 3S pack and needs a heatsink |
| <img src="https://www.wiltronics.com.au/wp-content/uploads/images/components/to-220-transistor-3-lead-component-package.jpg" alt="TIP31C" width="200"><br>**Option 3 (custom).**<br>Discrete regulator: TIP31C NPN pass transistor driven by a 5.6 V zener (1N4734A) as an emitter follower<br>about &#92;&#36;1.50 in parts<br>[TIP31C at Wiltronics](https://www.wiltronics.com.au/product/5440/tip31c-npn-bipolar-transistor-to220/) (&#92;&#36;0.88 AUD)<br>[TIP31C datasheet (ST)](https://www.st.com/resource/en/datasheet/tip31c.pdf) | \* Very inexpensive parts we already understand from class<br>\* TIP31C handles 3 A, so it has plenty of headroom<br>\* Good learning exercise and fully "open" with no IC behavior to trust | \* Poor regulation: output is the zener voltage minus V<sub>BE</sub> (about 4.9 V), which drifts with load and temperature and can fall below the Nano's 4.4 V VBUS minimum<br>\* No current limit or thermal shutdown, so a short can destroy the transistor or the LiDAR<br>\* No reverse-battery protection<br>\* More parts, more board space and more solder joints to fail<br>\* Zener bias current is wasted all the time |

**Choice:** Option 2: Texas Instruments LM2940CT-5.0/NOPB

**Rationale:** The course requires a linear regulator, and the team has not locked in the battery yet. The LM2940's 1 V maximum dropout lets the same board run from a 2S LiPo, a 3S LiPo, a 9.6 V NiMH pack or a 12 V lead-acid battery, while the 7805 needs at least 7 V and rules out 2S packs. Its built-in reverse-battery protection matters on a robot whose battery is plugged and unplugged every session, since one backwards plug could destroy the LiDAR. Its 1 A rating covers the 502.5 mA budget with 497.5 mA left over. The custom transistor regulator was rejected because it cannot hold 5 V within the Curiosity Nano's VBUS limits and has no protection.

**Thermal check:** With a fully charged 3S pack (12.6 V) and the budgeted 502.5 mA load, the regulator dissipates about (12.6 V − 5 V) × 0.5025 A + 12.6 V × 0.015 A ≈ 4.0 W. To keep the junction below 125 °C at a 45 °C ambient (a robot running outside in Arizona), the total junction-to-air resistance must be under about 20 °C/W. A bare TO-220 is far above that, so the regulator gets a bolt-on TO-220 heatsink rated at about 15 °C/W or better, with thermal compound. If the team chooses a 2S pack, dissipation drops to about 1.8 W.

---

## 3. LiDAR Subsystem – Power Source (shared team battery)

Will calculate and decide as a group.

---

## Final Selections Summary

| Block | Part | Unit cost | Supplier |
| --- | --- | --- | --- |
| **LiDAR Subsystem – Ranging sensor** | Waveshare D500 LiDAR Kit (LDRobot STL-19P) | about &#92;&#36;50 | [Amazon](https://www.amazon.com/dp/B0GSTXW158) |
| **LiDAR Subsystem – +5 V regulator** | TI LM2940CT-5.0/NOPB + TO-220 heatsink | &#92;&#36;1.94 | [DigiKey](https://www.digikey.com/en/products/detail/texas-instruments/LM2940CT-5-0-NOPB/32575) |
| **LiDAR Subsystem – Power source (team)** | Will calculate and decide as a group. | — | — |
| Microcontroller (selected for us) | Microchip PIC18F57Q43 Curiosity Nano (DM164150) | — | — |

*Prices were checked on October 19, 2026 and do not include shipping.*

## Pin Table

Proposed pin assignments for the PIC18F57Q43 Curiosity Nano on the LiDAR daughter board. All UART and PWM functions are routed with Peripheral Pin Select (PPS), so pins can move when the schematic is drawn. The Nano's target voltage (VTG) stays at its default 3.3 V, which matches the D500's 3.3 V UART output and its 3.6 V maximum PWM input.

| Signal | PIC18F57Q43 pin | Peripheral | Direction | Connects to |
| --- | --- | --- | --- | --- |
| LiDAR data | RC7 | UART1 RX (PPS) | Input | D500 pin 1 (Tx) |
| LiDAR motor speed (optional) | RC6 | PWM1 output (PPS) | Output | D500 pin 2 (PWM); leave low for the default 10 Hz scan |
| Team bus TX | RB0 | UART2 TX (PPS) | Output | Connector 1, pin 2 → MASTER RX |
| Team bus RX | RB1 | UART2 RX (PPS) | Input | Connector 1, pin 1 ← MASTER TX |
| Debug serial TX | RF0 | UART (PPS) to on-board debugger CDC | Output | USB virtual COM port (development only) |
| Debug serial RX | RF1 | UART (PPS) from on-board debugger CDC | Input | USB virtual COM port (development only) |
| Status LED | RF3 | GPIO | Output | On-board LED0 (shows "LiDAR packets OK") |
| +5 V | VBUS | Power in | — | LM2940 output, also D500 pin 4 (P5V) |
| Ground | GND | — | — | Battery ground, D500 pin 3, Connector 1 ground |

> Note: The D500 has only a Tx line and a PWM input (no Rx), so the "RX" line from the PIC to the LiDAR in the block diagram becomes the optional PWM speed-control line. The block diagram will be updated to match.
