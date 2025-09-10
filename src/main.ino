/*
 * Project: MT07 CAN Bus Interface
 * Author: Andreas Panagiotakis
 * Date: 3/8/2024
 * License: MIT License
 * 
 * Description:
 * This program uses the MT07_CANBus library to interact with the CAN bus of a Yamaha MT-07 motorcycle (2014 model).
 * It initializes the CAN bus, decodes incoming messages, and displays the following data in real-time:
 * - Gear position
 * - Throttle position sensor (TPS)
 * - Motor and air temperature
 * - Speed and RPM
 * 
 * Usage:
 * - Connect the MCP2515 module to the ESP32.
 * - Wire the CAN bus to the motorcycle.
 * - Compile and upload the program to the ESP32.
 * - View the decoded data in the Serial Monitor at 115200 baud.
 * 
 * License Information:
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MT07_CAN_Library.h"

const int CS_PIN = 5;  // Chip select pin for MCP2515
MT07_CANBus mt07(CS_PIN);

void setup() {
    Serial.begin(115200);
    
    if (mt07.begin(CAN_500KBPS, MCP_8MHZ)) {
        Serial.println("MT-07 CANBus initialized successfully.");
    } else {
        Serial.println("Failed to initialize MT-07 CANBus.");
        while (1);  // Halt the program if initialization fails
    }
}

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
