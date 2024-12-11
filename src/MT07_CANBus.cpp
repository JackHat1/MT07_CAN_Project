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

#include <mcp_can.h>
#include <SPI.h>

#ifndef MT07_CANBus_H
#define MT07_CANBus_H

class MT07_CANBus {
public:
    // Constructor
    MT07_CANBus(int csPin);

    // Initialization
    bool begin(long baudRate, byte clock);

    // Process a CAN message
    void processMessage(unsigned long id, byte* data);

    // Getters for decoded values
    String getGearPosition();
    float getTPS();
    String getMotorTemp();
    String getAirTemp();
    float getSpeed();
    unsigned int getRPM();

private:
    MCP_CAN CAN;
    
    // Decoded values
    byte gearPositionValue = 0xFF;
    byte tpsValue = 0xFF;
    byte motorTempValue = 0xFF;
    byte airTempValue = 0xFF;
    unsigned int speedSum = 0;
    unsigned int speedCount = 0;
    unsigned int rpm = 0;

    // Helper methods for decoding data
    String decodeGearPosition(byte data);
    float decodeTPS(byte data);
    String decodeMotorTemp(byte data);
    String decodeAirTemp(byte data);
    float decodeSpeed(unsigned int sum, unsigned int count);
    unsigned int decodeRPM(byte byte3, byte byte4);
};

#endif

/* Implementation */

MT07_CANBus::MT07_CANBus(int csPin) : CAN(csPin) {}

/*
 * Initialize the CAN bus.
 *
 * Parameters:
 * - baudRate: The desired CAN bus speed in kbps (e.g., CAN_500KBPS).
 * - clock: The MCP2515 oscillator frequency (e.g., MCP_8MHZ).
 *
 * Returns:
 * - true if the initialization was successful, false otherwise.
 */
bool MT07_CANBus::begin(long baudRate, byte clock) {
    if (CAN.begin(MCP_ANY, baudRate, clock) == CAN_OK) {
        CAN.setMode(MCP_NORMAL);
        return true;
    }
    return false;
}

/*
 * Process an incoming CAN message.
 *
 * Parameters:
 * - id: The ID of the CAN message.
 * - data: The data bytes of the CAN message.
 *
 * Decodes specific CAN message IDs and stores their values.
 */
void MT07_CANBus::processMessage(unsigned long id, byte* data) {
    if (id == 0x236) {
        gearPositionValue = data[0];
    } else if (id == 0x216) {
        tpsValue = data[0];
    } else if (id == 0x23E) {
        motorTempValue = data[0];
        airTempValue = data[1];
    } else if (id == 0x20A) {
        rpm = decodeRPM(data[2], data[3]);
        speedSum += data[2];
        speedCount++;
    }
}

/*
 * Get the decoded gear position as a string.
 *
 * Returns:
 * - A string representing the gear position (e.g., "Neutral", "1st Gear").
 */
String MT07_CANBus::getGearPosition() {
    return decodeGearPosition(gearPositionValue);
}

/*
 * Get the decoded throttle position sensor (TPS) value.
 *
 * Returns:
 * - A float representing the TPS percentage (0.0 to 100.0).
 */
float MT07_CANBus::getTPS() {
    return decodeTPS(tpsValue);
}

/*
 * Get the decoded motor temperature.
 *
 * Returns:
 * - A string representing the motor temperature in °C, or "Low"/"High" for out-of-range values.
 */
String MT07_CANBus::getMotorTemp() {
    return decodeMotorTemp(motorTempValue);
}

/*
 * Get the decoded air temperature.
 *
 * Returns:
 * - A string representing the air temperature in °C, or "Low"/"High" for out-of-range values.
 */
String MT07_CANBus::getAirTemp() {
    return decodeAirTemp(airTempValue);
}

/*
 * Get the calculated average speed.
 *
 * Returns:
 * - A float representing the average speed in km/h.
 */
float MT07_CANBus::getSpeed() {
    if (speedCount == 0) return 0;
    float speed = decodeSpeed(speedSum, speedCount);
    speedSum = 0;
    speedCount = 0;
    return speed;
}

/*
 * Get the decoded RPM value.
 *
 * Returns:
 * - An unsigned integer representing the RPM.
 */
unsigned int MT07_CANBus::getRPM() {
    return rpm;
}

/*
 * Decode the gear position from the raw data byte.
 *
 * Parameters:
 * - data: The raw data byte representing the gear position.
 *
 * Returns:
 * - A string representing the gear position (e.g., "Neutral", "1st Gear").
 */
String MT07_CANBus::decodeGearPosition(byte data) {
    switch (data) {
        case 0x0: return "Neutral";
        case 0x20: return "1st Gear";
        case 0x40: return "2nd Gear";
        case 0x60: return "3rd Gear";
        case 0x80: return "4th Gear";
        case 0xA0: return "5th Gear";
        case 0xC0: return "6th Gear";
        default: return "Unknown";
    }
}

/*
 * Decode the throttle position sensor (TPS) value from the raw data byte.
 *
 * Parameters:
 * - data: The raw data byte representing the TPS value.
 *
 * Returns:
 * - A float representing the TPS percentage (0.0 to 100.0).
 */
float MT07_CANBus::decodeTPS(byte data) {
    return (data / 255.0) * 100.0;
}

/*
 * Decode the motor temperature from the raw data byte.
 *
 * Parameters:
 * - data: The raw data byte representing the motor temperature.
 *
 * Returns:
 * - A string representing the temperature in °C, or "Low"/"High" for out-of-range values.
 */
String MT07_CANBus::decodeMotorTemp(byte data) {
    if (data < 0x70) return "Low";
    if (data > 0xEA) return "High";
    float temp = (data - 0x70) * 0.625 + 40;
    return String(temp, 2) + "\u00B0C";
}

/*
 * Decode the air temperature from the raw data byte.
 *
 * Parameters:
 * - data: The raw data byte representing the air temperature.
 *
 * Returns:
 * - A string representing the temperature in °C, or "Low"/"High" for out-of-range values.
 */
String MT07_CANBus::decodeAirTemp(byte data) {
    if (data < 0x21) return "Low";
    if (data > 0xCF) return "High";
    float temp = (data - 0x30) * 0.625;
    return String(temp, 2) + "\u00B0C";
}

/*
 * Calculate the average speed from the sum of raw speed values and the message count.
 *
 * Parameters:
 * - sum: The sum of raw speed values from the CAN messages.
 * - count: The number of messages containing speed data.
 *
 * Returns:
 * - A float representing the average speed in km/h.
 */
float MT07_CANBus::decodeSpeed(unsigned int sum, unsigned int count) {
    return (sum / (float)count) * 0.75;
}

/*
 * Decode the RPM value from two bytes of raw data.
 *
 * Parameters:
 * - byte3: The first byte representing the base RPM value.
 * - byte4: The second byte representing the fine adjustment.
 *
 * Returns:
 * - An unsigned integer representing the RPM.
 */
unsigned int MT07_CANBus::decodeRPM(byte byte3, byte byte4) {
    return (byte3 * 100) + byte4;
}
