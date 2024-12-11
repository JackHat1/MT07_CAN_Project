MT07 CAN Bus Interface Library



Overview

This project provides a custom library and application for interacting with the CAN bus of a Yamaha MT-07 motorcycle (2014 model). Developed during the summer of 2024 for the FSTUC team, this system allows for real-time telemetry and data acquisition.

Features

Gear Position Detection: Decodes and displays the current gear.

Throttle Position Sensor (TPS): Shows throttle opening as a percentage.

Motor and Air Temperature: Displays temperature data from the CAN bus.

Speed and RPM: Provides live readings of speed and engine RPM.

Extensible: Easily add support for additional CAN IDs.

Hardware Requirements

ESP32: Microcontroller for processing CAN bus messages.

MCP2515 CAN Bus Module: Interface for CAN communication.

Yamaha MT-07 (2014 model): Source of CAN bus data.

CAN Bus Cables: For connecting to the motorcycle's CAN network.

Software Requirements

Arduino IDE: For development and uploading the firmware.

Libraries:

MCP_CAN

Built-in SPI library
