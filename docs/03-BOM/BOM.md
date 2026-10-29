---
title: Bill of Materials
---

## Overview

Everything needed to build my LiDAR subsystem board. Reference designators match the [schematic](../04-Schematic/Schematics.md). Prices are single-quantity, in US dollars, without shipping.

## Bill of Materials (Spreadsheet)

![LiDAR subsystem bill of materials](BOM_LiDAR_LK.png)

Download the [Excel file](BOM_LiDAR_LK.xlsx).

## Component Bill of Materials

| Component | Ref. Des. | Qty | Unit Cost | Total Cost | Vendor | Purchase Link | Datasheet |
|---|---|---:|---:|---:|---|---|---|
| PIC18F57Q43 Curiosity Nano (DM164150) | U1 | 1 | &#92;&#36;10.95 | &#92;&#36;10.95 | DigiKey | [View Product](https://www.digikey.com/en/products/detail/microchip-technology/DM164150/11586705) | [View Datasheet](https://www.microchip.com/en-us/development-tool/DM164150) |
| Waveshare D500 360° LiDAR Kit | J2 | 1 | &#92;&#36;50.00 | &#92;&#36;50.00 | Amazon | [View Product](https://www.amazon.com/dp/B0GSTXW158) | [View Datasheet](https://www.waveshare.com/wiki/D500_LiDAR_Kit) |
| TI LM2940CT-5.0 5 V Regulator | U2 | 1 | &#92;&#36;1.94 | &#92;&#36;1.94 | DigiKey | [View Product](https://www.digikey.com/en/products/detail/texas-instruments/LM2940CT-5-0-NOPB/32575) | [View Datasheet](https://www.ti.com/lit/ds/symlink/lm2940-n.pdf) |
| TO-220 Heatsink | U2 | 1 | &#92;&#36;0.60 | &#92;&#36;0.60 | Generic | — | — |
| CUI PJ-063AH Barrel Jack | J1 | 1 | &#92;&#36;1.50 | &#92;&#36;1.50 | DigiKey | [View Product](https://www.digikey.com/en/products/detail/cui-devices/PJ-063AH/2161208) | — |
| 750 mA Slow-Blow Fuse, 5 × 20 mm | F1 | 1 | &#92;&#36;0.30 | &#92;&#36;0.30 | Generic | — | — |
| BLX-A Fuse Holder, 5 × 20 mm | F1 | 1 | &#92;&#36;0.10 | &#92;&#36;0.10 | Tayda | [View Product](https://www.taydaelectronics.com/fuse-holder-with-cover-5x20mm-blx-a-pcb-6-3a-250v.html) | — |
| SS14 Schottky Diode | D2 | 1 | &#92;&#36;0.50 | &#92;&#36;0.50 | DigiKey | [View Product](https://www.digikey.com/en/products/detail/onsemi/SS14/965474) | — |
| JST B4B-PH-K-S 4-Pin Header | J2 | 1 | &#92;&#36;0.20 | &#92;&#36;0.20 | Generic | — | — |
| Omron B3F-1000 Pushbutton | SW1 | 1 | &#92;&#36;0.26 | &#92;&#36;0.26 | Generic | — | — |
| Shrouded IDC Header, 2 × 4 | J3 | 1 | &#92;&#36;0.60 | &#92;&#36;0.60 | Generic | — | — |
| Pin Header, 1 × 10 | J4, J5 | 2 | &#92;&#36;0.50 | &#92;&#36;1.00 | Generic | — | — |
| Pin Header, 1 × 2, with Jumper | JP1–JP5 | 5 | &#92;&#36;0.25 | &#92;&#36;1.25 | Generic | — | — |
| Green LED, 0805 | D1, D4 | 2 | &#92;&#36;0.25 | &#92;&#36;0.50 | Generic | — | — |
| Red LED, 0805 | D3 | 1 | &#92;&#36;0.25 | &#92;&#36;0.25 | Generic | — | — |
| Resistor, 1 kΩ, 0805 | R1, R8 | 2 | &#92;&#36;0.10 | &#92;&#36;0.20 | Generic | — | — |
| Resistor, 330 Ω, 0805 | R5, R6 | 2 | &#92;&#36;0.10 | &#92;&#36;0.20 | Generic | — | — |
| Resistor, 10 kΩ, 0805 | R4, R7 | 2 | &#92;&#36;0.10 | &#92;&#36;0.20 | Generic | — | — |
| Resistor, 100 Ω, 0805 | R2 | 1 | &#92;&#36;0.10 | &#92;&#36;0.10 | Generic | — | — |
| Capacitor, 100 µF, 25 V, Electrolytic | C1 | 1 | &#92;&#36;0.30 | &#92;&#36;0.30 | Generic | — | — |
| Capacitor, 22 µF, 16 V, Electrolytic | C3 | 1 | &#92;&#36;0.20 | &#92;&#36;0.20 | Generic | — | — |
| Capacitor, 10 µF, 16 V, 0805 | C7 | 1 | &#92;&#36;0.25 | &#92;&#36;0.25 | Generic | — | — |
| Capacitor, 1 µF, 16 V, 0805 | C9 | 1 | &#92;&#36;0.10 | &#92;&#36;0.10 | Generic | — | — |
| Capacitor, 0.47 µF, 50 V, 0805 | C2 | 1 | &#92;&#36;0.10 | &#92;&#36;0.10 | Generic | — | — |
| Capacitor, 0.1 µF, 50 V, 0805 | C4, C5, C6, C8 | 4 | &#92;&#36;0.10 | &#92;&#36;0.40 | Generic | — | — |

**Total estimated cost: &#92;&#36;72.00**

## Battery Pack

| Component | Qty | Unit Cost | Total Cost | Vendor |
|---|---:|---:|---:|---|
| POWOBEST 18650 Cell, 3000 mAh | 3 | — | — | Amazon |
| DIANN 18650 Battery Holder | 3 | — | — | Amazon |
| HiLetgo TP4056 USB-C Charger | 3 | — | — | Amazon |
| 2.1 mm DC Barrel Plug with Leads | 1 | — | — | Generic |
