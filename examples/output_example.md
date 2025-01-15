### Example Output from the MT07 CAN Bus Interface

```plaintext
MT-07 CANBus initialized successfully.
TPS: 45.12% | RPM: 2300 | Gear Position: Neutral (N) | Motor Temp: 52.50°C | Air Temp: 22.00°C | Speed: 40.25 km/h
TPS: 60.23% | RPM: 3500 | Gear Position: First Gear (1) | Motor Temp: 55.75°C | Air Temp: 21.75°C | Speed: 65.00 km/h
TPS: 72.58% | RPM: 4200 | Gear Position: Second Gear (2) | Motor Temp: 58.50°C | Air Temp: 22.25°C | Speed: 85.50 km/h
TPS: 84.14% | RPM: 5000 | Gear Position: Third Gear (3) | Motor Temp: 60.00°C | Air Temp: 23.00°C | Speed: 105.75 km/h
TPS: 92.48% | RPM: 6500 | Gear Position: Fourth Gear (4) | Motor Temp: 62.25°C | Air Temp: 22.50°C | Speed: 130.00 km/h
TPS: 98.00% | RPM: 7000 | Gear Position: Fifth Gear (5) | Motor Temp: 64.00°C | Air Temp: 23.25°C | Speed: 150.00 km/h
TPS: 100.00% | RPM: 8000 | Gear Position: Sixth Gear (6) | Motor Temp: 66.50°C | Air Temp: 23.50°C | Speed: 175.00 km/h

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

