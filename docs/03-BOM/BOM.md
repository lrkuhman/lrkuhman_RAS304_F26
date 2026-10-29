---
title: Bill of Materials
---

## Overview

This is the bill of materials for my **LiDAR subsystem** board, taken from the [KiCad schematic](../04-Schematic/Schematics.md). Reference designators match the schematic. Parts marked **DNP** are on the board layout but are not fitted. The battery pack and charging parts are listed separately because they plug into the board rather than being soldered to it.

Unit costs are listed for the parts already priced on the [Component Selection](../02-Component-Selection/Component-Selection.md) page. The remaining costs will be added when the parts are ordered.

## Board Components

*Table 1: LiDAR board bill of materials.*

| **Part / Description** | **Qty** | **Manufacturer** | **Manufacturer #** | **Unit Cost** | **Vendor / Datasheet** | **Reference Designators** |
| :--- | :---: | :--- | :--- | :---: | :--- | :--- |
| PIC18F57Q43 Curiosity Nano development board | 1 | Microchip | DM164150 | Provided by course | [Product page](https://www.microchip.com/en-us/development-tool/DM164150) | U1 |
| 360° DTOF LiDAR kit (D500 / STL-19P), with 4-pin cable | 1 | Waveshare / LDRobot | D500 (STL-19P) | about 50 USD | [Amazon](https://www.amazon.com/dp/B0GSTXW158), [wiki](https://www.waveshare.com/wiki/D500_LiDAR_Kit) | Plugs into J2 |
| 5 V 1 A low-dropout linear regulator, TO-220 | 1 | Texas Instruments | LM2940CT-5.0/NOPB | 1.94 USD | [DigiKey](https://www.digikey.com/en/products/detail/texas-instruments/LM2940CT-5-0-NOPB/32575), [datasheet](https://www.ti.com/lit/ds/symlink/lm2940-n.pdf) | U2 |
| TO-220 heatsink, about 15 °C/W or better, with thermal compound | 1 | — | — | — | — | On U2 |
| DC barrel jack, 2.1 mm center pin, through-hole | 1 | CUI Devices | PJ-063AH | — | — | J1 |
| 750 mA slow-blow fuse, 5 × 20 mm, 250 V | 1 | — | T750mA 5×20 mm | — | — | F1 |
| Enclosed 5 × 20 mm PCB fuse holder | 1 | — | BLX-A | — | — | F1 |
| Schottky diode, 40 V 1 A, SMA | 1 | — | SS14 | — | — | D2 |
| JST PH 4-pin vertical header, 2.0 mm (mates PHR-4) | 1 | JST | B4B-PH-K-S | — | — | J2 |
| Shrouded IDC header, 2 × 4, 2.54 mm | 1 | — | — | — | — | J3 |
| Pin header, 1 × 10, 2.54 mm | 2 | — | — | — | — | J4, J5 |
| Pin header, 1 × 2, 2.54 mm, with jumper shunt | 5 | — | — | — | — | JP1, JP2, JP3, JP4, JP5 |
| Tactile pushbutton, 6 mm, through-hole | 1 | Omron | B3F-1000 | — | — | SW1 |
| Green LED, 0805 | 2 | — | — | — | — | D1 (power), D4 (LiDAR OK) |
| Red LED, 0805 | 1 | — | — | — | — | D3 (debug) |
| Resistor 1 kΩ, 1/8 W, 0805 | 2 | — | — | — | — | R1, R8 |
| Resistor 330 Ω, 1/8 W, 0805 | 2 | — | — | — | — | R5, R6 |
| Resistor 10 kΩ, 1/8 W, 0805 | 2 | — | — | — | — | R4, R7 |
| Resistor 100 Ω, 1/8 W, 0805 | 1 | — | — | — | — | R2 |
| Resistor 10 kΩ, 1/8 W, 0805 (**DNP**) | 0 | — | — | — | — | R3 |
| Electrolytic capacitor 100 µF, 25 V, radial 6.3 mm | 1 | — | — | — | — | C1 |
| Electrolytic capacitor 22 µF, 16 V, radial 5 mm | 1 | — | — | — | — | C3 |
| Ceramic capacitor 0.47 µF, 50 V, 0805 | 1 | — | — | — | — | C2 |
| Ceramic capacitor 0.1 µF, 50 V, 0805 | 4 | — | — | — | — | C4, C5, C6, C8 |
| Ceramic capacitor 10 µF, 16 V, 0805 | 1 | — | — | — | — | C7 |
| Ceramic capacitor 1 µF, 16 V, 0805 | 1 | — | — | — | — | C9 |
| Test point, through-hole pad | 8 | — | — | — | — | TP1–TP8 |

## Battery Pack and Charging

*Table 2: Power source parts (see the [Power Budget](../05-Power-Budget/Power-Budget.md)).*

| **Part / Description** | **Qty** | **Manufacturer** | **Manufacturer #** | **Unit Cost** | **Vendor** | **Use** |
| :--- | :---: | :--- | :--- | :---: | :--- | :--- |
| 18650 Li-ion cell, 3.7 V, 3000 mAh | 3 | POWOBEST | POWO18B | — | Amazon | Wired in series as a 3S pack (9.0–12.6 V) |
| Single 18650 battery holder with wire leads | 3 | DIANN | — | — | Amazon | Holds each cell; leads wired in series |
| TP4056 USB-C 1 A single-cell charger module with protection | 3 | HiLetgo | TP4056 | — | Amazon | Charges one cell at a time, removed from the pack |
| 9 V 1 A DC wall adapter, 2.1 mm barrel plug | 1 | — | — | — | — | Bench power through J1 |
