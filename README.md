ESP32-Based Heater Control System
This project implements a simple temperature-controlled heater system using an "ESP32 microcontroller", a "DHT22 temperature sensor", and a "Relay module" to control a heater. An onboard "LED" gives visual feedback for the `Overheat` condition.

Components Used
| Component        | Description                                  | Wokwi Pin |
|------------------|----------------------------------------------|-----------|
| ESP32            | Microcontroller                              | -         |
| DHT22            | Temperature & humidity sensor                | GPIO 21   |
| Relay Module     | Controls heater ON/OFF                       | GPIO 26   |
| Onboard LED      | Visual alert for overheat                   | GPIO 2    |
| Heater (imaginary) | Controlled by the relay (abstracted in code) | -         |

"Note:" Wokwi simulation environment is used for testing without physical hardware.

 Pin Connections
| ESP32 GPIO Pin | Connected Component     |
|----------------|-------------------------|
| GPIO 21        | DHT22 Data Pin          |
| GPIO 26        | Relay IN (control pin)  |
| GPIO 2         | Onboard LED             |
| VCC & GND      | Power for DHT22 & Relay |

 Temperature Thresholds and States

| State            | Temperature Condition         | Relay Action     | LED Action        |
|------------------|-------------------------------|------------------|-------------------|
| IDLE             | < 25°C                         | OFF              | OFF               |
| HEATING          | 25°C ≤ Temp < 30°C             | ON               | OFF               |
| STABILIZING      | 30°C ≤ Temp < 35°C             | ON               | OFF               |
| TARGET_REACHED   | 35°C ≤ Temp ≤ 38°C             | OFF              | OFF               |
| OVERHEAT         | > 40°C                         | OFF              | ON (Alert Blink)  |

Code Logic
- Reads temperature using DHT22 sensor.
- Based on thresholds, sets heater state.
- Turns ON/OFF relay accordingly.
- Turns ON LED during Overheat only.
- Logs current state and temperature to Serial Monitor.

How to Run (on [Wokwi](https://wokwi.com))
1. Create a new ESP32 project on Wokwi.
2. Paste the provided code into `main.ino`.
3. Connect the DHT22 to GPIO 21.
4. Connect Relay IN to GPIO 26.
5. Use GPIO 2 for the onboard LED.
6. Simulate to test behavior by adjusting temperature sensor values.

Communication Protocol Justification
This project does "not require external communication", but in real-world deployment, "UART", "I2C", or "MQTT (WiFi-based)" could be used to send temperature and state data to a central server or UI dashboard. For simplicity and offline usage, everything runs on the ESP32 locally.

Future Enhancements
- Add OLED or LCD display to show current state.
- Add Wi-Fi communication using MQTT to send data to a dashboard.
- Add hysteresis to avoid rapid state switching.
- Integrate physical push button for manual override.
