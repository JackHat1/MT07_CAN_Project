#include "MT07_CANBus.h"

const int CS_PIN = 15;  // Chip select pin for MCP2515
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
