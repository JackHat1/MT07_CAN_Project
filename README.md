![csm_FS_TUC-logo-transparent_40e7fd597a](https://github.com/user-attachments/assets/2219371f-b14c-4e27-865a-f8f728e16e57)

## Table of Contents
1. [Overview](#overview)
2. [Hardware Requirements](#hardware-requirements)
3. [Software Requirements](#software-requirements)
4. [Future Improvements](#future-improvements)
5. [Troubleshooting](#Troubleshooting)
6. [Example Output](examples/output_example.md)
7. [License](License.txt)


## Hardware Requirements

- **ESP32**: Microcontroller for processing CAN bus messages.
- **MCP2515 CAN Bus Module**: Interface for CAN communication.
- **Yamaha MT-07 (2014 model)**: Source of CAN bus data.
- **CAN Bus Cables**: For connecting to the motorcycle's CAN network.

---
### Software Requirements
- [MCP_CAN Library](https://github.com/coryjfowler/MCP_CAN_lib)
- Install via Arduino Library Manager or clone from the GitHub repository.
- Built-in SPI library

## Description

The **MT07 CAN Bus Interface Library** is a robust solution designed to facilitate data acquisition and real-time telemetry from the Yamaha MT-07 motorcycle (2014 model). Built specifically for the **FSTUC team** during the summer of 2024, this project aims to decode essential CAN bus messages and display critical vehicle parameters.

The library is implemented using the ESP32 microcontroller and the MCP2515 CAN module, offering a modular and extensible framework for researchers, engineers, and enthusiasts who need efficient access to real-time motorcycle data for analysis, optimization, or control system development.

### Key Features

- **Easy Integration**: Ready-to-use library compatible with the Arduino ecosystem.
- **Real-Time Telemetry**: Provides instantaneous feedback on parameters like speed, RPM, temperatures, and gear position.
- **Modular Design**: Enables easy addition of support for new CAN message IDs or functionality.

This project serves as a foundational tool for telemetry systems, especially in motorsport and research contexts, enabling seamless communication with the MT-07's onboard systems.
### Future Improvements
- Support for additional CAN IDs for more data types.
- Integration with a graphical dashboard for better visualization.
- Add Bluetooth or Wi-Fi support for wireless telemetry.

### Troubleshooting

#### 1. CAN Bus Initialization Failure
- **Issue**: The Serial Monitor displays "Failed to initialize MT-07 CANBus."
- **Solution**:
  1. Verify that the MCP2515 module is properly connected to the ESP32.
  2. Check that the crystal oscillator on the MCP2515 module matches the declared value in the code (`8 MHz` or `16 MHz`).
  3. Ensure the correct SPI pins are configured in the wiring and code.

#### 2. No Data Received from the CAN Bus
- **Issue**: No messages are being processed.
- **Solution**:
  1. Verify that the Yamaha MT-07's diagnostic port is connected properly.
  2. Confirm the MCP2515 is powered and CAN_H / CAN_L lines are correctly connected.
  3. Check if the CAN bus speed (`500 KBPS`) is compatible with the MT-07.

#### 3. Incorrect Data or Noise
- **Issue**: Data displayed on the Serial Monitor is incorrect or contains noise.
- **Solution**:
  1. Ensure the CAN_H and CAN_L wires are properly twisted to reduce noise.
  2. Verify that the grounding is secure and consistent across all devices.
  3. Double-check the decoding logic in the library for compatibility with the MT-07's CAN protocol.


[Example Output](examples/output_example.md)

[License](License.txt)
