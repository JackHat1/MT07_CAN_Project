/**
 * \file main.ino
 * \brief Main program for MT-07 CAN Bus Interface.
 *
 * \details This program uses the MT07_CANBus library to interact with the CAN bus of a Yamaha MT-07 motorcycle (2014 model).
 * It initializes the CAN bus, decodes incoming messages, and displays the following data in real-time:
 * - Gear position
 * - Throttle position sensor (TPS)
 * - Motor and air temperature
 * - Speed and RPM
 *
 * \author Andreas Panagiotakis
 * \date 2024-08-03
 * \license MIT License
 *
 * \usage
 * - Connect the MCP2515 module to the ESP32.
 * - Wire the CAN bus to the motorcycle.
 * - Compile and upload the program to the ESP32.
 * - View the decoded data in the Serial Monitor at 115200 baud.
 */

#include "MT07_CANBus.h"

/// Chip select pin for MCP2515
const int CS_PIN = 5;

/// Instance of the MT07_CANBus class
MT07_CANBus mt07(CS_PIN);

/**
 * \brief Arduino setup function.
 *
 * Initializes the Serial Monitor and CAN bus. If the CAN bus fails to initialize, the program halts.
 */
void setup() {
    Serial.begin(115200);
    
    if (mt07.begin(CAN_500KBPS, MCP_8MHZ)) {
        Serial.println("MT-07 CANBus initialized successfully.");
    } else {
        Serial.println("Failed to initialize MT-07 CANBus.");
        while (1);  // Halt the program if initialization fails
    }
}

/**
 * \brief Arduino loop function.
 *
 * Checks for incoming CAN messages, processes them, and displays the decoded data in the Serial Monitor.
 */
void loop() {
    unsigned long rxId;
    byte rxBuf[8];
    byte rxDlc;

    // Check for incoming CAN messages
    if (CAN_MSGAVAIL == mt07.CAN.checkReceive()) {
        if (mt07.CAN.readMsgBuf(&rxId, &rxDlc, rxBuf) == CAN_OK) {
            mt07.processMessage(rxId, rxBuf);  // Decode the message
            
            // Display decoded data
            Serial.print("Gear Position: ");
            Serial.println(mt07.getGearPosition());

            Serial.print("TPS: ");
            Serial.print(mt07.getTPS());
            Serial.println("%");

            Serial.print("Motor Temp: ");
            Serial.println(mt07.getMotorTemp());

            Serial.print("Air Temp: ");
            Serial.println(mt07.getAirTemp());

            Serial.print("Speed: ");
            Serial.print(mt07.getSpeed());
            Serial.println(" km/h");

            Serial.print("RPM: ");
            Serial.println(mt07.getRPM());
            Serial.println("---------------------------");
        } else {
            Serial.println("Error reading CAN message.");
        }
    }
}
