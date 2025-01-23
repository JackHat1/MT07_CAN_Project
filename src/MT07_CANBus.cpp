/**
 * \file MT07_CANBus.cpp
 * \brief Implementation file for the MT-07 CAN bus library.
 *
 * \details This library provides functions for interacting with the MT-07 motorcycle CAN bus.
 * It allows for decoding data such as gear position, throttle position sensor (TPS),
 * motor and air temperature, speed, and RPM.
 *
 * \author Andreas Panagiotakis
 * \date 2024-08-03
 * \license MIT License
 *
 * \usage
 * - Include this library in your project.
 * - Initialize the MCP2515 module using the \c begin() method.
 * - Use the \c readMessages() method to decode incoming CAN messages.
 * - Retrieve decoded values using the respective getter methods.
 */

#include "MT07_CAN.h"

/**
 * \brief Constructor: Initializes the member variables.
 */
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

/**
 * \brief Initializes the CAN bus and sets the MCP2515 to normal mode.
 * \return True if initialization succeeds, false otherwise.
 */
bool MT07_CAN::begin() {
    if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
        Serial.println("CAN bus initialized.");
        CAN.setMode(MCP_NORMAL);
        return true;
    } else {
        Serial.println("Failed to initialize CAN bus.");
        return false;
    }
}

/**
 * \brief Reads the CAN messages and decodes their content based on ID.
 */
void MT07_CAN::readMessages() {
    if (CAN_MSGAVAIL == CAN.checkReceive()) {
        if (CAN.readMsgBuf(&rxId, &rxDlc, rxBuf) == CAN_OK) {
            if (rxId == GEAR_POSITION_ID) {
                gearPositionValue = rxBuf[0];
            } else if (rxId == TPS_ID) {
                tpsValue = rxBuf[0];
            } else if (rxId == TEMP_ID) {
                motorTempValue = rxBuf[0];
                airTempValue = rxBuf[1];
            } else if (rxId == RPM_SPEED_ID) {
                rpm = decodeRPM(rxBuf[2], rxBuf[3]);
                speedSum += rxBuf[2];
                speedCount++;
            }
        }
    }
}

/**
 * \brief Returns the throttle position as a percentage.
 * \return Throttle position in percentage.
 */
float MT07_CAN::getTPS() {
    return decodeTPS(tpsValue);
}

/**
 * \brief Returns the current RPM.
 * \return RPM value.
 */
unsigned int MT07_CAN::getRPM() {
    return rpm;
}

/**
 * \brief Returns the gear position as a string.
 * \return Gear position.
 */
String MT07_CAN::getGearPosition() {
    return decodeGearPosition(gearPositionValue);
}

/**
 * \brief Returns the motor temperature in degrees Celsius.
 * \return Motor temperature as a string.
 */
String MT07_CAN::getMotorTemp() {
    float temp = decodeMotorTemp(motorTempValue);
    return MotorTemp_to_String(temp);
}

/**
 * \brief Returns the air temperature in degrees Celsius.
 * \return Air temperature as a string.
 */
String MT07_CAN::getAirTemp() {
    float temp = decodeAirTemp(airTempValue);
    return AirTemP_to_String(temp);
}

/**
 * \brief Returns the average speed calculated from received data.
 * \return Speed in km/h.
 */
float MT07_CAN::getSpeed() {
    return decodeSpeed(speedSum, speedCount);
}

/**
 * \brief Decodes the throttle position sensor (TPS) value to a percentage.
 * \param data Raw byte data.
 * \return Throttle position in percentage.
 */
float MT07_CAN::decodeTPS(byte data) {
    return (data / 255.0) * 100.0;
}

/**
 * \brief Decodes the gear position based on raw byte data.
 * \param data Raw byte data.
 * \return Gear position as a string.
 */
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

/**
 * \brief Decodes the motor temperature based on raw byte data.
 * \param data Raw byte data.
 * \return Motor temperature in degrees Celsius.
 */
String MT07_CAN::decodeMotorTemp(byte data) {
    float temp = (data - 0x70) * 0.625 + 40;
    return temp;
}

/**
 * \brief Decodes the motor temperature to a string.
 * \param data Raw byte data.
 * \return Motor temperature as a string.
 */
String MT07_CAN::MotorTemp_to_String(byte data) {
    if (data < 0x70) return "LO";
    if (data > 0xEA) return "HI";
    return String(data, 2) + "\u00B0C";
}

/**
 * \brief Decodes the air temperature based on raw byte data.
 * \param data Raw byte data.
 * \return Air temperature in degrees Celsius.
 */
String MT07_CAN::decodeAirTemp(byte data) {
    float temp = (data - 0x30) * 0.625;
    return temp;
}

/**
 * \brief Decodes the air temperature to a string.
 * \param data Raw byte data.
 * \return Air temperature as a string.
 */
String MT07_CAN::AirTemP_to_String(byte data) {
    if (data < 0x21) return "LO";
    if (data > 0xCF) return "HI";
    float temp = (data - 0x30) * 0.625;
    return String(data, 2) + "\u00B0C";
}

/**
 * \brief Decodes the speed based on the sum of speed values and count.
 * \param sum Sum of speed values.
 * \param count Number of speed messages.
 * \return Speed in km/h.
 */
float MT07_CAN::decodeSpeed(unsigned int sum, unsigned int count) {
    return (sum / (float)count) * 0.75;
}

/**
 * \brief Decodes the RPM based on raw byte data from the CAN message.
 * \param byte3 The third byte of the CAN message.
 * \param byte4 The fourth byte of the CAN message.
 * \return Decoded RPM value.
 */
unsigned int MT07_CAN::decodeRPM(byte byte3, byte byte4) {
    unsigned int baseRPM = byte3 * 100;
    unsigned int adjustedRPM = baseRPM + byte4;
    return adjustedRPM;
}
