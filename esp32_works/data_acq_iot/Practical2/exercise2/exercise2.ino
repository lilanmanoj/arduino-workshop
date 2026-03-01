#include "driver/dac.h"

#define DAC_PIN 25

const unsigned long stepInterval = 1;

int dacValue = 0;
int direction = 1;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= stepInterval) {
    previousMillis = currentMillis;

    dacWrite(DAC_PIN, dacValue);

    dacValue += direction;

    if (dacValue >= 255) {
      dacValue = 255;
      direction = -1;
    } else if (dacValue <= 0) {
      dacValue = 0;
      direction = 1;
    }
  }
}