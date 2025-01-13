/*
 * Library: MT07_CANBus
 * Author: Andreas Panagiotakis
 * Date: 3/8/2024 
 * License: MIT License
 *
 * Description:
 * This library provides functions for interacting with the MT-07 motorcycle CAN bus.
 * It allows for decoding data such as gear position, throttle position sensor (TPS),
 * motor and air temperature, speed, and RPM.
 *
 * Usage:
 * - Include this library in your project.
 * - Initialize the MCP2515 module using the begin() method.
 * - Use the processMessage() method to decode incoming CAN messages.
 * - Retrieve decoded values using the respective getter methods.
 */

#include "MT07_CAN.h"

// Constructor: Initializes the member variables
MT07_CAN::MT07_CAN() : CAN(SPI_CS_PIN) {
    // Initialize sensor values to invalid states
    speedSum = 0;
    speedCount = 0;
    rpm = 0;
    gearPositionValue = 0xFF;
    tpsValue = 0xFF;
    motorTempValue = 0xFF;
    airTempValue = 0xFF;
}

// begin() - Initializes the CAN bus and sets the MCP2515 to normal mode
bool MT07_CAN::begin() {
    // Attempt to initialize the CAN bus at 500 Kbps speed
    if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
        Serial.println("CAN bus initialized.");
        CAN.setMode(MCP_NORMAL);  // Set CAN bus to normal mode
        return true;
    } else {
        Serial.println("Failed to initialize CAN bus.");
        return false;
    }
}

// readMessages() - Reads the CAN messages and decodes their content based on ID
void MT07_CAN::readMessages() {
    // Check if a CAN message is available to be read
    if (CAN_MSGAVAIL == CAN.checkReceive()) {
        // Read the CAN message into the buffer
        if (CAN.readMsgBuf(&rxId, &rxDlc, rxBuf) == CAN_OK) {
            // Decode the message based on the ID
            if (rxId == GEAR_POSITION_ID) {
                gearPositionValue = rxBuf[0];  // Store gear position byte
            } else if (rxId == TPS_ID) {
                tpsValue = rxBuf[0];  // Store throttle position byte
            } else if (rxId == TEMP_ID) {
                motorTempValue = rxBuf[0]; // Store motor temperature byte
                airTempValue = rxBuf[1];   // Store air temperature byte
            } else if (rxId == RPM_SPEED_ID) {
                rpm = decodeRPM(rxBuf[2], rxBuf[3]); // Decode RPM from bytes
                speedSum += rxBuf[2];  // Add speed value to the sum
                speedCount++;           // Increment the count of speed values
            }
        }
    }
}

// Getter methods for the decoded sensor values

// getTPS() - Returns the throttle position as a percentage
float MT07_CAN::getTPS() {
    return decodeTPS(tpsValue);
}

// getRPM() - Returns the current RPM
unsigned int MT07_CAN::getRPM() {
    return rpm;
}

// getGearPosition() - Returns the gear position as a string
String MT07_CAN::getGearPosition() {
    return decodeGearPosition(gearPositionValue);
}

// getMotorTemp() - Returns the motor temperature in °C
String MT07_CAN::getMotorTemp() {
    return decodeMotorTemp(motorTempValue);
}

// getAirTemp() - Returns the air temperature in °C
String MT07_CAN::getAirTemp() {
    return decodeAirTemp(airTempValue);
}

// getSpeed() - Returns the average speed calculated from received data
float MT07_CAN::getSpeed() {
    return decodeSpeed(speedSum, speedCount);
}

// Decodes the throttle position sensor (TPS) value to a percentage
float MT07_CAN::decodeTPS(byte data) {
    // Convert raw byte (0-255) to percentage (0-100%)
    return (data / 255.0) * 100.0;
}

// Decodes the gear position based on raw byte data
String MT07_CAN::decodeGearPosition(byte data) {
    switch (data) {
        case 0x0: return "Neutral (N)";
        case 0x20: return "First Gear (1)";
        case 0x40: return "Second Gear (2)";
        case 0x60: return "Third Gear (3)";
        case 0x80: return "Fourth Gear (4)";
        case 0xA0: return "Fifth Gear (5)";
        case 0xC0: return "Sixth Gear (6)";
        default: return "Unknown Gear Position";
    }
}

// Decodes the motor temperature based on raw byte data
String MT07_CAN::decodeMotorTemp(byte data) {
    if (data < 0x70) return "LO"; // Low temperature range
    if (data > 0xEA) return "HI"; // High temperature range
    // Convert raw byte data to temperature in °C
    float temp = (data - 0x70) * 0.625 + 40;
    return String(temp, 2) + "°C";
}

// Decodes the air temperature based on raw byte data
String MT07_CAN::decodeAirTemp(byte data) {
    if (data < 0x21) return "LO"; // Low temperature range
    if (data > 0xCF) return "HI"; // High temperature range
    // Convert raw byte data to temperature in °C
    float temp = (data - 0x30) * 0.625;
    return String(temp, 2) + "°C";
}

// Decodes the speed based on the sum of speed values and count
float MT07_CAN::decodeSpeed(unsigned int sum, unsigned int count) {
    // Calculate the average speed from the received data
    return (sum / (float)count) * 0.75; // Adjust factor for speed
}

// Decodes the RPM based on raw byte data from the CAN message
unsigned int MT07_CAN::decodeRPM(byte byte3, byte byte4) {
    unsigned int baseRPM = byte3 * 100;       // Base RPM from byte 3
    unsigned int adjustedRPM = baseRPM + byte4; // Fine adjustment from byte 4
    return adjustedRPM;
}
