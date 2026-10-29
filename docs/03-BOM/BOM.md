---
title: Bill of Materials
---

## Overview

This is the bill of materials for my **LiDAR subsystem** board, taken from the [KiCad schematic](../04-Schematic/Schematics.md). Reference designators match the schematic, and the parts are grouped by the schematic's sections. Parts marked **DNP** have a place on the board but are not fitted.

Prices are single-quantity distributor prices in US dollars, checked in October 2026, and do not include shipping. Generic passives (resistors, capacitors, LEDs, headers) are listed at typical single-quantity prices because any brand with the same value and package will work.


## Power Input and Regulation

| **Ref. Designators** | **Qty** | **Description** | **Manufacturer** | **Manufacturer #** | **Unit Cost** | **Total** | **Vendor / Datasheet** |
| :--- | :---: | :--- | :--- | :--- | ---: | ---: | :--- |
| J1 | 1 | DC barrel jack, 2.1 mm center pin, through-hole | CUI Devices | PJ-063AH | 1.50 | 1.50 | [DigiKey](https://www.digikey.com/en/products/detail/cui-devices/PJ-063AH/2161208) |
| F1 | 1 | Fuse, 750 mA slow-blow, 5 × 20 mm, 250 V | Generic | T750mA 5×20 mm | 0.30 | 0.30 | — |
| F1 | 1 | Enclosed 5 × 20 mm PCB fuse holder | Xucheng / generic | BLX-A | 0.10 | 0.10 | [Tayda](https://www.taydaelectronics.com/fuse-holder-with-cover-5x20mm-blx-a-pcb-6-3a-250v.html) |
| U2 | 1 | 5 V 1 A low-dropout linear regulator, TO-220 | Texas Instruments | LM2940CT-5.0/NOPB | 1.94 | 1.94 | [DigiKey](https://www.digikey.com/en/products/detail/texas-instruments/LM2940CT-5-0-NOPB/32575), [datasheet](https://www.ti.com/lit/ds/symlink/lm2940-n.pdf) |
| U2 | 1 | TO-220 heatsink, 15 °C/W or better, with thermal compound | Generic | — | 0.60 | 0.60 | — |
| C1 | 1 | Electrolytic capacitor, 100 µF, 25 V, radial 6.3 mm | Generic | — | 0.30 | 0.30 | — |
| C2 | 1 | Ceramic capacitor, 0.47 µF, 50 V, 0805 | Generic | — | 0.10 | 0.10 | — |
| C3 | 1 | Electrolytic capacitor, 22 µF, 16 V, radial 5 mm | Generic | — | 0.20 | 0.20 | — |
| C4 | 1 | Ceramic capacitor, 0.1 µF, 50 V, 0805 | Generic | — | 0.10 | 0.10 | — |
| D1 | 1 | Green LED, 0805 (power indicator) | Generic | — | 0.25 | 0.25 | — |
| R1 | 1 | Resistor, 1 kΩ, 1/8 W, 0805 | Generic | — | 0.10 | 0.10 | — |
| | | | | | **Subtotal** | **5.49** | |

## Microcontroller

| **Ref. Designators** | **Qty** | **Description** | **Manufacturer** | **Manufacturer #** | **Unit Cost** | **Total** | **Vendor / Datasheet** |
| :--- | :---: | :--- | :--- | :--- | ---: | ---: | :--- |
| U1 | 1 | PIC18F57Q43 Curiosity Nano development board | Microchip | DM164150 | 10.95 | 10.95 | [DigiKey](https://www.digikey.com/en/products/detail/microchip-technology/DM164150/11586705) |
| D2 | 1 | Schottky diode, 40 V 1 A, SMA (blocks USB back-feed) | onsemi | SS14 | 0.50 | 0.50 | [DigiKey](https://www.digikey.com/en/products/detail/onsemi/SS14/965474) |
| C5, C6 | 2 | Ceramic capacitor, 0.1 µF, 50 V, 0805 (VBUS / VTG bypass) | Generic | — | 0.10 | 0.20 | — |
| | | | | | **Subtotal** | **11.65** | |

## LiDAR Interface

| **Ref. Designators** | **Qty** | **Description** | **Manufacturer** | **Manufacturer #** | **Unit Cost** | **Total** | **Vendor / Datasheet** |
| :--- | :---: | :--- | :--- | :--- | ---: | ---: | :--- |
| — | 1 | 360° DTOF LiDAR kit with 4-pin cable | Waveshare / LDRobot | D500 (STL-19P) | 50.00 | 50.00 | [Amazon](https://www.amazon.com/dp/B0GSTXW158), [wiki](https://www.waveshare.com/wiki/D500_LiDAR_Kit) |
| J2 | 1 | JST PH 4-pin vertical header, 2.0 mm (mates PHR-4) | JST | B4B-PH-K-S | 0.20 | 0.20 | — |
| C7 | 1 | Ceramic capacitor, 10 µF, 16 V, 0805 | Generic | — | 0.25 | 0.25 | — |
| C8 | 1 | Ceramic capacitor, 0.1 µF, 50 V, 0805 | Generic | — | 0.10 | 0.10 | — |
| R2 | 1 | Resistor, 100 Ω, 1/8 W, 0805 | Generic | — | 0.10 | 0.10 | — |
| R3 | 0 | Resistor, 10 kΩ, 1/8 W, 0805 (**DNP**, not fitted) | Generic | — | 0.10 | 0.00 | — |
| | | | | | **Subtotal** | **50.65** | |

## Team Bus, Debug LEDs, and Button

| **Ref. Designators** | **Qty** | **Description** | **Manufacturer** | **Manufacturer #** | **Unit Cost** | **Total** | **Vendor / Datasheet** |
| :--- | :---: | :--- | :--- | :--- | ---: | ---: | :--- |
| J3 | 1 | Shrouded IDC header, 2 × 4, 2.54 mm | Generic | — | 0.60 | 0.60 | — |
| R4, R7 | 2 | Resistor, 10 kΩ, 1/8 W, 0805 | Generic | — | 0.10 | 0.20 | — |
| D3 | 1 | Red LED, 0805 (debug) | Generic | — | 0.25 | 0.25 | — |
| D4 | 1 | Green LED, 0805 (LiDAR OK) | Generic | — | 0.25 | 0.25 | — |
| R5, R6 | 2 | Resistor, 330 Ω, 1/8 W, 0805 | Generic | — | 0.10 | 0.20 | — |
| SW1 | 1 | Tactile pushbutton, 6 mm, through-hole | Omron | B3F-1000 | 0.26 | 0.26 | — |
| R8 | 1 | Resistor, 1 kΩ, 1/8 W, 0805 | Generic | — | 0.10 | 0.10 | — |
| C9 | 1 | Ceramic capacitor, 1 µF, 16 V, 0805 | Generic | — | 0.10 | 0.10 | — |
| | | | | | **Subtotal** | **1.96** | |

## Headers, Jumpers, and Test Points

| **Ref. Designators** | **Qty** | **Description** | **Manufacturer** | **Manufacturer #** | **Unit Cost** | **Total** | **Vendor / Datasheet** |
| :--- | :---: | :--- | :--- | :--- | ---: | ---: | :--- |
| J4, J5 | 2 | Pin header, 1 × 10, 2.54 mm | Generic | — | 0.50 | 1.00 | — |
| JP1–JP5 | 5 | Pin header, 1 × 2, 2.54 mm, with jumper shunt | Generic | — | 0.25 | 1.25 | — |
| TP1–TP8 | 8 | Test point, through-hole pad on the PCB | — | — | 0.00 | 0.00 | — |
| | | | | | **Subtotal** | **2.25** | |

## Battery Pack and Charging

These parts plug into J1 instead of being soldered to the board. See the [Power Budget](../05-Power-Budget/Power-Budget.md) for how the pack was sized.

| **Qty** | **Description** | **Manufacturer** | **Manufacturer #** | **Pack Price** | **Vendor** | **Use** |
| :---: | :--- | :--- | :--- | ---: | :--- | :--- |
| 3 | 18650 Li-ion cell, 3.7 V, 3000 mAh | POWOBEST | POWO18B | — | Amazon | Wired in series as a 3S pack (9.0–12.6 V) |
| 3 | Single 18650 battery holder with wire leads | DIANN | — | — | Amazon | One holder per cell; leads wired in series |
| 3 | TP4056 USB-C 1 A single-cell charger module with protection | HiLetgo | TP4056 | — | Amazon | Charges one cell at a time, removed from the pack |
| 1 | 2.1 mm DC barrel plug with wire leads | Generic | — | — | — | Connects the pack's series leads to J1 |

## Cost Summary

| **Item** | **Cost (USD)** |
| :--- | ---: |
| Board components, including the D500 LiDAR and Curiosity Nano | **72.00** |
| Battery pack, holders, chargers, and plug | Prices to be added from our order |
| **Total for the LiDAR subsystem** | **72.00 + battery parts** |
