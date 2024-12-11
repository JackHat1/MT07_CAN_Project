/*
 * Library: MT07_CANBus
 * Author: Andreas Panagiotakis
 * Date: [Date]
 * License: MIT License
 *
 * Description:
 * This library provides functions for interacting with the MT-07 motorcycle CAN bus.
 * It allows for decoding data such as gear position, throttle position sensor (TPS),
 * motor and air temperature, speed, and RPM.
 */

#ifndef MT07_CANBus_H
#define MT07_CANBus_H

#include <mcp_can.h>
#include <SPI.h>

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
