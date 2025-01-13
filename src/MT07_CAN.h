/*
 * Library: MT07_CANBus
 * Author: Andreas Panagiotakis
 * Date:   3/8/2024
 * License: MIT License
 *
 * Description:
 * This library provides functions for interacting with the MT-07 motorcycle CAN bus.
 * It allows for decoding data such as gear position, throttle position sensor (TPS),
 * motor and air temperature, speed, and RPM.
 */

#ifndef MT07_CAN_H
#define MT07_CAN_H

#include <mcp_can.h>
#include <SPI.h>

// Define CAN message IDs
#define GEAR_POSITION_ID 0x236  // CAN ID for gear position
#define TPS_ID 0x216            // CAN ID for throttle position sensor (TPS)
#define TEMP_ID 0x23E           // CAN ID for temperature sensors
#define RPM_SPEED_ID 0x20A      // CAN ID for RPM and speed data

// Define the SPI Chip Select Pin for MCP2515 (the hardware CAN controller)
#define SPI_CS_PIN 9

class MT07_CAN {
public:
    // Constructor to initialize the CAN controller
    MT07_CAN();

    // Initializes the CAN bus and sets it to normal mode
    bool begin();

    // Reads messages from the CAN bus and decodes the data
    void readMessages();

    // Getter functions for each sensor's decoded value
    float getTPS();           // Returns the throttle position in percentage
    unsigned int getRPM();    // Returns the current RPM
    String getGearPosition(); // Returns the current gear position as a string
    String getMotorTemp();    // Returns the motor temperature in °C
    String getAirTemp();      // Returns the air temperature in °C
    float getSpeed();         // Returns the average speed in km/h

private:
    MCP_CAN CAN;            // MCP2515 CAN controller object
    unsigned long rxId;     // ID of the received CAN message
    byte rxDlc;             // Data Length Code (DLC) of the received message
    byte rxBuf[8];          // Buffer to hold the received CAN message data
    unsigned int speedSum;  // Sum of the speed values for averaging
    unsigned int speedCount;// Number of speed values received
    unsigned int rpm;       // RPM value
    byte gearPositionValue; // Raw value for gear position
    byte tpsValue;          // Raw value for throttle position
    byte motorTempValue;    // Raw value for motor temperature
    byte airTempValue;      // Raw value for air temperature

    // Private methods to decode the raw data from the CAN message
    float decodeTPS(byte data);           // Decodes TPS value to percentage
    String decodeGearPosition(byte data); // Decodes gear position to string
    String decodeMotorTemp(byte data);    // Decodes motor temperature to string
    String decodeAirTemp(byte data);      // Decodes air temperature to string
    unsigned int decodeRPM(byte byte3, byte byte4); // Decodes RPM from byte data
    float decodeSpeed(unsigned int sum, unsigned int count); // Decodes speed from average
};

#endif
