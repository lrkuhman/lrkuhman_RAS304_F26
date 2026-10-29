---
title: Individual Block Diagram
---

## Overview

This block diagram shows how power and data flow through my **LiDAR subsystem** board for OpenField. The board reads a 360° LiDAR, processes each scan on its own PIC18F57Q43 Curiosity Nano, and reports obstacle data to the team's MASTER board over the ribbon cable. It connects to the rest of the robot through Connector 1 in the [team block diagram](https://ras4-f26-2028-team-1.github.io/RAS304-F26-team1.github.io/06-team-block-diagram/).

![LiDAR subsystem block diagram](LiDAR_Block_Diagram_LK.png)

**Figure 1:** LiDAR subsystem block diagram. Click the image to enlarge it.

## Blocks

* **Power source:** A 3S lithium-ion pack (three 18650 cells in series, 9.0–12.6 V, 3000 mAh) plugs into the J1 barrel jack. On the bench, a 9 V adapter plugs into the same jack. See the [Power Budget](../05-Power-Budget/Power-Budget.md).
* **Protection and regulation:** The input passes through F1, a 750 mA slow-blow fuse, to U2, an LM2940CT-5.0 low-dropout regulator with a heatsink. U2 makes the board's single +5 V rail.
* **Power levels:** The +5 V rail powers the LiDAR (through jumper JP2) and the Curiosity Nano's VBUS pin (through Schottky diode D2 and jumper JP1). The Nano makes its own 3.3 V for the PIC and the debug LEDs. All grounds are shared, including ribbon pin 8.
* **Sensor:** The Waveshare D500 time-of-flight LiDAR sends scan data on its TX line to RC7 (UART1 RX, 230400 baud). Its PWM speed input is left unconnected, so it uses its internal 10 Hz speed control.
* **Actuator:** None on this board. The LiDAR's spinning motor is controlled inside the sensor.
* **User interface and debugging:** Two debug LEDs (D3 red on RD0, D4 green on RD1) and a debounced pushbutton (SW1 on RA4).
* **Team connection:** UART2 links the board to the MASTER board through Connector 1: RB0 (TX) goes to ribbon pin 2, and ribbon pin 1 comes in on RB1 (RX), at 115200 baud.

## Changes Since the First Version

* Added the **power path** (battery, barrel jack, fuse, and regulator), which the first version did not show.
* Replaced the "TX/RX" LiDAR link with the D500's real interface: one TX data line, plus a PWM input that is left unconnected. The D500 has no RX line.
* Added the debug LEDs and pushbutton, and labeled every connection with its pin, UART, and baud rate.

## Source Files

* Block diagram source (draw.io): [LiDAR_Block_Diagram_LK.drawio](LiDAR_Block_Diagram_LK.drawio)
* ZIP of the source and image files: [LiDAR_Block_Diagram_LK_source.zip](LiDAR_Block_Diagram_LK_source.zip)
