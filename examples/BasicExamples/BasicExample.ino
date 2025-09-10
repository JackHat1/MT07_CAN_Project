/*
 * Example: MT07 CAN Bus Library
 * Author: Andreas Panagiotakis
 * Description:
 * Demonstrates how to use the MT07_CANBus library to read CAN bus data
 * from a Yamaha MT-07 motorcycle using the MCP2515 module.
 */

#include "MT07_CAN_Library.h"

// Initialize MT07_CAN object with SPI CS pin
const int CS_PIN = 9;
MT07_CAN mt07;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize CAN bus
  if (mt07.begin()) {
    Serial.println("MT-07 CANBus initialized successfully.");
  } else {
    Serial.println("Failed to initialize MT-07 CANBus.");
    while (1); // Halt program if initialization fails
  }
}

void loop() {
  // Read CAN messages and decode them
  mt07.readMessages();

  // Print decoded values to Serial Monitor
  Serial.print("Gear: ");
  Serial.println(mt07.getGearPosition());

  Serial.print("TPS: ");
  Serial.print(mt07.getTPS());
  Serial.println(" %");

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
  delay(500); // Wait half a second before reading again
}
