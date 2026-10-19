---
title: Power Budget
---

## Overview

This power budget checks that the +5 V regulator selected on the [Component Selection](../02-Component-Selection/Component-Selection.md) page can power everything on my **LiDAR subsystem** daughter board at the same time, with the required 25% safety margin. It follows the course power budget template; the filled-in spreadsheet is available under [Resources](#resources).

The LiDAR board has one power rail (+5 V). The Curiosity Nano makes its own 3.3 V target voltage (VTG) from its VBUS pin with its on-board MIC5353 regulator, so no separate 3.3 V regulator is needed and the +12 V and +3.3 V sections of the template are unused.

## A. Major Components

| Component | Part number | Supply voltage range | Qty. | Max current (mA) | Total current (mA) |
| --- | --- | --- | --- | --- | --- |
| ToF LiDAR (Waveshare D500 / LDRobot STL-19P) | STL-19P | +4.5 to +5.5 V | 1 | 290 | 290 |
| PIC18F57Q43 Curiosity Nano | DM164150 | +4.4 to +5.25 V (VBUS) | 1 | 100 | 100 |

**Current sources:** 290 mA is the D500's rated working current from the Waveshare documentation. 100 mA for the Curiosity Nano is a conservative allowance covering the PIC18F57Q43 running at 64 MHz with UART, PWM and DMA active, plus the on-board nEDBG debugger chip, which is powered whenever the board is.

## B. +5 V Power Rail

| Component | Part number | Supply voltage range | Qty. | Max current (mA) | Total current (mA) |
| --- | --- | --- | --- | --- | --- |
| ToF LiDAR (D500) | STL-19P | +4.5 to +5.5 V | 1 | 290 | 290 |
| PIC18F57Q43 Curiosity Nano | DM164150 | +4.4 to +5.25 V | 1 | 100 | 100 |
| | | | | **Subtotal** | **390** |
| | | | | **Safety margin** | **25%** |
| | | | | **Total current required on +5 V rail** | **487.5** |

## C. Regulator

| Regulator | Part number | Input voltage range | Qty. | Max current (mA) | Total current (mA) |
| --- | --- | --- | --- | --- | --- |
| +5 V low-dropout linear regulator | TI LM2940CT-5.0/NOPB | +6 to +26 V | 1 | 1000 | 1000 |
| | | | | **Total remaining current available on +5 V rail** | **512.5** |

The regulator selection table and rationale are on the [Component Selection](../02-Component-Selection/Component-Selection.md#2-lidar-subsystem-5-v-voltage-regulator) page. Because it is a linear regulator, it will likely need a TO-220 heatsink: if the group picks a 12 V-class battery (12.6 V fully charged), it dissipates about 3.9 W at 487.5 mA.

## D. External Power Source

Will calculate and decide as a group.

## E. Battery Life

Will calculate and decide as a group.

## Conclusions

- The LiDAR board needs **487.5 mA** at +5 V with the 25% margin, and the LM2940CT-5.0 can supply **1000 mA**, leaving **512.5 mA** of headroom, enough for a start-up surge from the LiDAR motor.
- A single +5 V rail powers everything on the board; the Curiosity Nano generates the PIC's 3.3 V internally.
- **Design actions:** add a TO-220 heatsink (about 15 °C/W or better) to the LM2940, and measure the D500's start-up current on the bench to confirm it stays under the regulator's 1 A rating.

## Resources

The completed power budget is available as a [PDF](PowerBudget-LiDAR.pdf) and as a [Microsoft Excel sheet](PowerBudget-LiDAR.xlsx), built from the course template.
