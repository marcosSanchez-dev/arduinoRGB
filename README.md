# ESP32 and ESP8266 Neopixel and Ultrasonic Sensor Simplified Project

This project involves two microcontrollers, the ESP32 and ESP8266, working together to create a simple interactive light display using a Neopixel strip and ultrasonic sensors. The ultrasonic sensors measure distances and send this information to the ESP32, which then adjusts the Neopixel strip's colors accordingly.

## Components

- **ESP32**
  - Neopixel strip (59 pixels)
- **ESP8266**
  - 3 HC-SR04 ultrasonic sensors

## ESP32 Code

The ESP32 code controls the Neopixel strip based on commands received from the ESP8266.

```cpp
// Insert ESP32 code here


### Parte 2:

```markdown
## ESP8266 Code

The ESP8266 code reads the distance from three ultrasonic sensors and sends a command to the ESP32.

```cpp
// Insert ESP8266 code here


### Parte 3:

```markdown
## How It Works

1. **ESP8266:**
   - Measures distance using three HC-SR04 ultrasonic sensors.
   - Sends a command to the ESP32 based on the measured distances.

2. **ESP32:**
   - Receives commands from the ESP8266 via Serial2.
   - Adjusts the Neopixel strip colors based on the received command.

## Setup

1. **Connect the ESP8266** to the HC-SR04 sensors:
   - TRIG_PIN1 -> D1
   - ECHO_PIN1 -> D4
   - TRIG_PIN2 -> D2
   - ECHO_PIN2 -> D5
   - TRIG_PIN3 -> D3
   - ECHO_PIN3 -> D7

2. **Connect the ESP32** to the Neopixel strip:
   - Data pin of the Neopixel strip -> GPIO 25

## Usage

1. Upload the respective codes to the ESP32 and ESP8266.
2. Power on both microcontrollers.
3. Observe how the Neopixel strip reacts to changes in distance measured by the ultrasonic sensors.

## Dependencies

- Adafruit NeoPixel library for controlling the Neopixel strip.

## Future Improvements

- Add more Neopixel strips or sensors for a more complex display.
- Integrate additional sensor types for more interactive effects.

Feel free to contribute to this project by submitting pull requests or opening issues. Enjoy experimenting with interactive light and sound!
