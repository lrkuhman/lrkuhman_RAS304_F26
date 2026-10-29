---
title: Power Budget
---

## Overview

This power budget checks that the +5 V regulator selected on the [Component Selection](../02-Component-Selection/Component-Selection.md) page can power everything on my **LiDAR subsystem** daughter board at the same time, with the required 25% safety margin. It follows the course power budget template; the filled-in spreadsheet is available under [Resources](#resources).

The LiDAR board has one power rail (+5 V), made from a 9 V DC adapter (or a battery on the robot) by an LM2940CT-5.0 regulator. The Curiosity Nano makes its own 3.3 V target voltage (VTG) from its VBUS pin with its on-board MIC5353 regulator, so no separate 3.3 V regulator is needed and the +12 V and +3.3 V sections of the template are unused.

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

The two debug LEDs run from the Nano's 3.3 V output, which the Nano makes from the +5 V rail, so their current is counted here. Each LED draws about (3.3 V − 2.0 V) / 330 Ω ≈ 4 mA. The power LED draws about 3 mA, rounded up to 4 mA.

## C. Regulator

| Regulator | Part number | Input voltage range | Qty. | Max current (mA) | Total current (mA) |
| --- | --- | --- | --- | --- | --- |
| +5 V low-dropout linear regulator | TI LM2940CT-5.0/NOPB | +6 to +26 V | 1 | 1000 | 1000 |
| | | | | **Total remaining current available on +5 V rail** | **497.5** |

The regulator selection table and rationale are on the [Component Selection](../02-Component-Selection/Component-Selection.md#2-lidar-subsystem-5-v-voltage-regulator) page.

**Regulator heat:** A linear regulator turns the extra input voltage into heat: P = (V<sub>in</sub> − 5 V) × I.

| Input | Heat in the LM2940 at 502.5 mA |
| --- | --- |
| 9 V adapter | (9 − 5) × 0.5025 ≈ **2.0 W** |
| 12.6 V (fully charged 3S battery) | (12.6 − 5) × 0.5025 ≈ **3.8 W** |

Both are too much for a bare TO-220 package, so U2 gets a TO-220 heatsink (about 15 °C/W or better).

## D. External Power Source

| Power source | Part number | Supply voltage range | Output voltage | Max current (mA) | Total current (mA) |
| --- | --- | --- | --- | --- | --- |
| 9 V DC wall adapter | Barrel plug to fit J1 (CUI PJ-063AH) | 100 to 240 V AC | 9 V DC | 1000 | 1000 |
| **Rail connected:** +5 V rail, through the LM2940CT-5.0 | | | | | 502.5 |
| | | | | **Total remaining current available on the adapter** | **497.5** |

Because the LM2940 is a linear regulator, the current it takes from the adapter is about the same as the current it delivers on the +5 V rail. The 750 mA slow-blow fuse (F1) sits above this 502.5 mA load, leaving room for the LiDAR motor's start-up surge without blowing.

## E. Battery Life

On the robot, the board runs from a battery instead of the adapter. The final robot battery is chosen as a group, so this calculation uses an example pack that fits the board's input range.

| Battery | Part number | Voltage range | Capacity (mAh) | Required by regulator (mA) | Battery life |
| --- | --- | --- | --- | --- | --- |
| 3S Li-ion pack (example) | 3 × 18650 cells in series, 2600 mAh | +9.0 to +12.6 V | 2600 | 502.5 | **5.2 hours** |

Battery life = capacity ÷ current = 2600 mAh ÷ 502.5 mA ≈ **5.2 hours**.

Our team's [product requirements](https://ras4-f26-2028-team-1.github.io/RAS304-F26-team1.github.io/product-requirements/) call for at least **4 hours** of runtime (PR-2). For 4 hours, this board alone needs at least 4 h × 502.5 mA ≈ **2,010 mAh**, so a 2600 mAh pack meets the requirement with about 30% to spare.

## How the Power Budget Helped

- **Regulator choice confirmed:** The board needs 502.5 mA with a 25% safety margin. The LM2940CT-5.0 supplies 1000 mA, leaving 497.5 mA of headroom for the LiDAR motor's start-up surge.
- **Heatsink needed:** The budget showed the regulator will burn 2.0 W to 3.8 W as heat, so I added a TO-220 heatsink to the design.
- **Fuse sized:** The 750 mA slow-blow fuse sits above the normal 502.5 mA load but well below the adapter's 1 A rating.
- **Battery sized:** The LiDAR board needs at least 2,010 mAh to meet the team's 4-hour runtime requirement. This number goes into the team's battery decision.
- **Bench check:** On the breadboard, the D500 drew **247 mA** at 5.00 V, below the 290 mA used here, so the budget is conservative. (See [Schematics](../04-Schematic/Schematics.md#breadboard-verification).)

## Resources

The completed power budget is available as a [PDF](PowerBudget-LiDAR.pdf) and as a [Microsoft Excel sheet](PowerBudget-LiDAR.xlsx), built from the course template.
