---
title: Welcome
---
<center>
<font size= "6">Landon Kuhman Datasheet</font><br>
as part of<br>
<font size= "8"> OpenField</font><br>
for<br>
<font size= "5"> Team 1 (Group 101) </font><br>

**Submission: October 19, 2026**
</center>

## Introduction

This datasheet documents my individual subsystem, the **LiDAR subsystem**, for OpenField, our RAS 304 team project. It collects the block diagram, component selections, power budget and (later) the schematic and BOM for the LiDAR daughter board.

### Project Summary

OpenField is an open-source robot that sprays field lines, construction floor plans and temporary road markings using ordinary inverted spray-paint cans. It is built from commonly available parts with open firmware and hardware, as an affordable alternative to closed systems such as Dusty Robotics and HP SitePrint. The full team design is in our [team report](https://ras4-f26-2028-team-1.github.io/RAS304-F26-team1.github.io/).

### My Contribution

I am responsible for the LiDAR subsystem: a daughter board with its own PIC18F57Q43 Curiosity Nano that reads a 360° time-of-flight LiDAR, reduces each scan to the obstacle and landmark data the robot needs to navigate, and sends it to the MASTER board over UART.

### Datasheet Pages

* [Individual Block Diagram](01-Block-Diagram/Block-Diagram.md)
* [Component Selection](02-Component-Selection/Component-Selection.md): LiDAR sensor, +5 V regulator and power source comparisons, final selections and pin table
* [Power Budget](05-Power-Budget/Power-Budget.md): +5 V rail current, regulator headroom and battery life for the LiDAR board
* [BOM](03-BOM/BOM.md)
* [Schematic](04-Schematic/schematic.md)
