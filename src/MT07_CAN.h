/**
 * \file MT07_CAN.h
 * \brief Header file for the MT-07 CAN bus library.
 *
 * \details This library provides functions for interacting with the MT-07 motorcycle CAN bus.
 * It allows for decoding data such as gear position, throttle position sensor (TPS),
 * motor and air temperature, speed, and RPM.
 *
 * \author Andreas Panagiotakis
 * \date 2024-08-03
 * \license MIT License
 */

#ifndef MT07_CAN_H
#define MT07_CAN_H

#include <mcp_can.h>
#include <SPI.h>

/// CAN message IDs
#define GEAR_POSITION_ID 0x236  ///< CAN ID for gear position
#define TPS_ID 0x216            ///< CAN ID for throttle position sensor (TPS)
#define TEMP_ID 0x23E           ///< CAN ID for temperature sensors
#define RPM_SPEED_ID 0x20A      ///< CAN ID for RPM and speed data

/// SPI Chip Select Pin for MCP2515 (the hardware CAN controller)
#define SPI_CS_PIN 9

/**
 * \class MT07_CAN
 * \brief Handles MT-07 motorcycle CAN bus operations.
 */
class MT07_CAN {
public:
    /**
     * \brief Constructor to initialize the CAN controller.
     */
    MT07_CAN();

    /**
     * \brief Initializes the CAN bus and sets it to normal mode.
     * \return True if initialization succeeds, false otherwise.
     */
    bool begin();

    /**
     * \brief Reads messages from the CAN bus and decodes the data.
     */
    void readMessages();

    /**
     * \brief Returns the throttle position as a percentage.
     * \return Throttle position in percentage.
     */
    float getTPS();

    /**
     * \brief Returns the current RPM.
     * \return RPM value.
     */
    unsigned int getRPM();

    /**
     * \brief Returns the gear position as a string.
     * \return Gear position.
     */
    String getGearPosition();

    /**
     * \brief Returns the motor temperature in degrees Celsius.
     * \return Motor temperature as a string.
     */
    String getMotorTemp();

    /**
     * \brief Returns the air temperature in degrees Celsius.
     * \return Air temperature as a string.
     */
    String getAirTemp();

    /**
     * \brief Returns the average speed calculated from received data.
     * \return Speed in km/h.
     */
    float getSpeed();

private:
    MCP_CAN CAN;            ///< MCP2515 CAN controller object
    unsigned long rxId;     ///< ID of the received CAN message
    byte rxDlc;             ///< Data Length Code (DLC) of the received message
    byte rxBuf[8];          ///< Buffer to hold the received CAN message data
    unsigned int speedSum;  ///< Sum of the speed values for averaging
    unsigned int speedCount;///< Number of speed values received
    unsigned int rpm;       ///< RPM value
    byte gearPositionValue; ///< Raw value for gear position
    byte tpsValue;          ///< Raw value for throttle position
    byte motorTempValue;    ///< Raw value for motor temperature
    byte airTempValue;      ///< Raw value for air temperature

    /**
     * \brief Decodes the throttle position sensor (TPS) value to a percentage.
     * \param data Raw byte data.
     * \return Throttle position in percentage.
     */
    float decodeTPS(byte data);

    /**
     * \brief Decodes the gear position from the raw byte data.
     * \param data Raw byte data.
     * \return Gear position as a string.
     */
    String decodeGearPosition(byte data);

    /**
     * \brief Decodes the motor temperature from the raw byte data.
     * \param data Raw byte data.
     * \return Motor temperature in degrees Celsius as a string.
     */
    String decodeMotorTemp(byte data);

    /**
     * \brief Decodes the air temperature from the raw byte data.
     * \param data Raw byte data.
     * \return Air temperature in degrees Celsius as a string.
     */
    String decodeAirTemp(byte data);

    /**
     * \brief Decodes the RPM from the raw byte data.
     * \param byte3 The third byte of the CAN message.
     * \param byte4 The fourth byte of the CAN message.
     * \return Decoded RPM value.
     */
    unsigned int decodeRPM(byte byte3, byte byte4);

    /**
     * \brief Decodes the speed based on the sum of speed values and count.
     * \param sum Sum of speed values.
     * \param count Number of speed messages.
     * \return Speed in km/h.
     */
    float decodeSpeed(unsigned int sum, unsigned int count);
};

#endif
s
