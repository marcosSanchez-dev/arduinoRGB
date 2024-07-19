#include <Adafruit_NeoPixel.h>

#define PIN 25
#define NUMPIXELS 59

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial para depuración
  Serial2.begin(115200, SERIAL_8N1, 16, 17); // Inicializa el puerto serial 2 en los pines RX2 (16) y TX2 (17)
  pixels.begin(); // Inicializa la tira de LEDs
  pixels.show();  // Apaga todos los LEDs al inicio
}

void loop() {
  static char lastCommand = 0;
  
  // Aquí vamos a recibir una señal desde el ESP8266 para encender los LEDs
  if (Serial2.available() > 0) {
    char command = Serial2.read();
    if (command != lastCommand) {
      lastCommand = command;
      
      uint32_t color1 = 0, color2 = 0, color3 = 0;
      int activeSensors = 0;

      if (command & 0b001) {
        color1 = pixels.Color(255, 0, 0); // Rojo
        activeSensors++;
      }
      if (command & 0b010) {
        color2 = pixels.Color(0, 255, 0); // Verde
        activeSensors++;
      }
      if (command & 0b100) {
        color3 = pixels.Color(0, 0, 255); // Azul
        activeSensors++;
      }

      if (activeSensors == 1) {
        uint32_t color = color1 | color2 | color3;
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(i, color);
        }
      } else if (activeSensors == 2) {
        uint32_t startColor, endColor;
        
        if (command & 0b001) startColor = color1;
        else if (command & 0b010) startColor = color2;
        else startColor = color3;
        
        if (command & 0b100) endColor = color3;
        else if (command & 0b010) endColor = color2;
        else endColor = color1;

        for (int i = 0; i < NUMPIXELS; i++) {
          float ratio = (float)i / (NUMPIXELS - 1);
          uint8_t r = ((startColor >> 16 & 0xFF) * (1 - ratio) + (endColor >> 16 & 0xFF) * ratio);
          uint8_t g = ((startColor >> 8 & 0xFF) * (1 - ratio) + (endColor >> 8 & 0xFF) * ratio);
          uint8_t b = ((startColor & 0xFF) * (1 - ratio) + (endColor & 0xFF) * ratio);
          pixels.setPixelColor(i, pixels.Color(r, g, b));
        }
      } else if (activeSensors == 3) {
        for (int i = 0; i < NUMPIXELS; i++) {
          float ratio1 = (float)i / (NUMPIXELS - 1);
          float ratio2 = 1 - ratio1;
          uint8_t r = ((color1 >> 16 & 0xFF) * ratio2 + (color2 >> 16 & 0xFF) * ratio1);
          uint8_t g = ((color2 >> 8 & 0xFF) * ratio2 + (color3 >> 8 & 0xFF) * ratio1);
          uint8_t b = ((color1 & 0xFF) * ratio2 + (color3 & 0xFF) * ratio1);
          pixels.setPixelColor(i, pixels.Color(r, g, b));
        }
      } else {
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(i, 0);
        }
      }

      pixels.show();
    }
  }
}
