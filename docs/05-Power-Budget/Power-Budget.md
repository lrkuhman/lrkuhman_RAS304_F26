---
title: Power Budget
---

## Overview

This power budget checks that the +5 V regulator selected on the [Component Selection](../02-Component-Selection/Component-Selection.md) page can power everything on my **LiDAR subsystem** daughter board at the same time, with the required 25% safety margin. It follows the course power budget template; the filled-in spreadsheet is available under [Resources](#resources).

The LiDAR board has one power rail (+5 V), made by an LM2940CT-5.0 regulator from a 3S Li-ion battery pack on the robot, or from a 9 V DC adapter on the bench. The Curiosity Nano makes its own 3.3 V target voltage (VTG) from its VBUS pin with its on-board MIC5353 regulator, so no separate 3.3 V regulator is needed and the +12 V and +3.3 V sections of the template are unused.

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
| Indicator LEDs (D1 power, D3 debug, D4 "LiDAR OK") | Green/red LEDs with 1 kΩ / 330 Ω resistors | +3.3 to +5 V | 3 | 4 | 12 |
| | | | | **Subtotal** | **402** |
| | | | | **Safety margin** | **25%** |
| | | | | **Total current required on +5 V rail** | **502.5** |

Each LED draws about 4 mA. The debug LEDs run from the Nano's 3.3 V, which comes from the +5 V rail.

## C. Regulator

| Regulator | Part number | Input voltage range | Qty. | Max current (mA) | Total current (mA) |
| --- | --- | --- | --- | --- | --- |
| +5 V low-dropout linear regulator | TI LM2940CT-5.0/NOPB | +6 to +26 V | 1 | 1000 | 1000 |
| | | | | **Total remaining current available on +5 V rail** | **497.5** |

The regulator selection table and rationale are on the [Component Selection](../02-Component-Selection/Component-Selection.md#2-lidar-subsystem-5-v-voltage-regulator) page.

**Regulator heat:** (V<sub>in</sub> − 5 V) × 0.5025 A ≈ 2.0 W at 9 V and 3.8 W at 12.6 V, so U2 gets a TO-220 heatsink.

## D. External Power Sources

| Power source | Part number | Supply voltage range | Output voltage | Max current (mA) | Total current (mA) |
| --- | --- | --- | --- | --- | --- |
| **Source 1 (robot):** 3S Li-ion pack, three 18650 cells in series | POWOBEST POWO18B 3000 mAh (×3) | +9.0 to +12.6 V | 11.1 V nominal | 3000 | 3000 |
| **Rail connected:** +5 V rail, through the LM2940CT-5.0 | | | | | 502.5 |
| | | | | **Total remaining current available on Source 1** | **2497.5** |
| **Source 2 (bench):** 9 V DC wall adapter | 2.1 mm barrel plug (fits J1) | 100 to 240 V AC | 9 V DC | 1000 | 1000 |
| **Rail connected:** +5 V rail, through the LM2940CT-5.0 | | | | | 502.5 |
| | | | | **Total remaining current available on Source 2** | **497.5** |

Both sources plug into J1, one at a time. The battery's max current assumes 1C (3000 mA), since no cell datasheet is available. The cells are charged one at a time with TP4056 modules, outside the series pack.

## E. Battery Life

| Battery | Part number | Voltage range | Capacity (mAh) | Required by regulator (mA) | Battery life |
| --- | --- | --- | --- | --- | --- |
| 3S Li-ion pack | POWOBEST POWO18B 3000 mAh (×3, in series) | +9.0 to +12.6 V | 3000 | 502.5 | **6.0 hours** |

3000 mAh ÷ 502.5 mA ≈ **6.0 hours**, which meets the team's 4-hour runtime requirement ([PR-2](https://ras4-f26-2028-team-1.github.io/RAS304-F26-team1.github.io/product-requirements/)).

## Conclusions

- The board needs **502.5 mA** on +5 V with the 25% margin. The LM2940CT-5.0 supplies 1000 mA, leaving **497.5 mA** of headroom for the LiDAR's start-up surge.
- The regulator dissipates 2.0 W to 3.8 W, so it needs a TO-220 heatsink.
- The 3S pack runs the board for about **6 hours**.
- On the bench, the D500 drew **247 mA**, below the 290 mA used here, so the budget is conservative.

## Resources

The completed power budget is available as a [PDF](PowerBudget-LiDAR.pdf) and as a [Microsoft Excel sheet](PowerBudget-LiDAR.xlsx), built from the course template.
