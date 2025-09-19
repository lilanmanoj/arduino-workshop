#include <Arduino.h>

const uint8_t LED_GND = 11;
const uint8_t SSD_GND = 12;
const uint8_t DIGIT1 = 16;

void setup() {
    // Initiate Serial communication
    // at a baud rate of 9600
    Serial.begin(9600);

    pinMode(LED_GND, OUTPUT);
    pinMode(SSD_GND, OUTPUT);
    pinMode(DIGIT1, OUTPUT);

    digitalWrite(LED_GND, HIGH);
    digitalWrite(SSD_GND, LOW);
    digitalWrite(DIGIT1, HIGH);

    pinMode(2, OUTPUT);
}

void loop() {
    // Blink the LED_BUILTIN every second
    blink();
}

void blink() {
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
}