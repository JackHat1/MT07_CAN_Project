### Example Output from the MT07 CAN Bus Interface

```plaintext
MT-07 CANBus initialized successfully.

Gear Position: 2nd Gear
TPS: 45.6%
Motor Temp: 90.00°C
Air Temp: 28.00°C
Speed: 65.0 km/h
RPM: 7500
---------------------------

Gear Position: 3rd Gear
TPS: 78.2%
Motor Temp: 95.00°C
Air Temp: 30.00°C
Speed: 85.0 km/h
RPM: 8200
---------------------------

Gear Position: Neutral
TPS: 0.0%
Motor Temp: 88.00°C
Air Temp: 28.00°C
Speed: 0.0 km/h
RPM: 1000
---------------------------

Gear Position: 1st Gear
TPS: 15.5%
Motor Temp: 92.00°C
Air Temp: 29.00°C
Speed: 15.0 km/h
RPM: 2000
---------------------------
```

### Explanation of Output
1. **Initialization**: The program initializes successfully and starts processing CAN messages.
2. **Gear Position**: Displays the decoded gear position (e.g., "2nd Gear", "Neutral").
3. **TPS**: Shows throttle position sensor percentage (e.g., "45.6%").
4. **Motor Temp**: Displays the motor temperature in Celsius (e.g., "90.00°C").
5. **Air Temp**: Shows the air intake temperature in Celsius (e.g., "28.00°C").
6. **Speed**: Displays the vehicle's speed in km/h (e.g., "65.0 km/h").
7. **RPM**: Shows engine revolutions per minute (e.g., "7500 RPM").


### Notes
- The output reflects real-time telemetry data decoded from the MT-07 motorcycle's CAN bus.
- Readings are updated dynamically as messages are received.
- Values may vary based on the motorcycle's current operating conditions.

