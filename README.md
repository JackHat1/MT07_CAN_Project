![csm_FS_TUC-logo-transparent_40e7fd597a](https://github.com/user-attachments/assets/2219371f-b14c-4e27-865a-f8f728e16e57)

Hardware Requirements : 

· ESP32: Microcontroller for processing CAN bus messages.

· MCP2515 CAN Bus Module: Interface for CAN communication.

· Yamaha MT-07 (2014 model): Source of CAN bus data.

· CAN Bus Cables: For connecting to the motorcycle's CAN network.

Description
The MT07 CAN Bus Interface Library is a robust solution designed to facilitate data acquisition and real-time telemetry from the Yamaha MT-07 motorcycle (2014 model). Built specifically for the FSTUC team during the summer of 2024, this project aims to decode essential CAN bus messages and display critical vehicle parameters.

The library is implemented using the ESP32 microcontroller and the MCP2515 CAN module, offering a modular and extensible framework for researchers, engineers, and enthusiasts who need efficient access to real-time motorcycle data for analysis, optimization, or control system development.

Key features include:

· Easy Integration: Ready-to-use library compatible with the Arduino ecosystem.
· Real-Time Telemetry: Provides instantaneous feedback on parameters like speed, RPM, temperatures, and gear position.
· Modular Design: Enables easy addition of support for new CAN message IDs or functionality.
· This project serves as a foundational tool for telemetry systems, especially in motorsport and research contexts, enabling seamless communication with the MT-07's onboard systems.
