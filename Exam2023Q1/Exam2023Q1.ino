#include<Arduino.h>

const uint8_t LED_GND = 11;
const uint8_t SSD_GND = 12;
const uint8_t LEDS[4] = {2, 3, 4, 5};
const uint8_t SW1 = 10;
const uint8_t SW2 = 13;

unsigned int dl = 500;

void setup() {
    Serial.begin(9600);

    pinMode(SW1, INPUT);
    pinMode(SW2, INPUT);
    pinMode(LED_GND, OUTPUT);
    pinMode(SSD_GND, OUTPUT);

    for (uint8_t i = 0; i < sizeof(LEDS)/sizeof(LEDS[0]); i++) {
        pinMode(LEDS[i], OUTPUT);
    }

    digitalWrite(LED_GND, LOW);
    digitalWrite(SSD_GND, HIGH);
}

void loop() {
    if (digitalRead(SW1) == HIGH) {
        while (digitalRead(SW1) == HIGH) {
            delay (50);
        }

        dl = dl * 2;
    }

    if (digitalRead(SW2) == HIGH) {
        while (digitalRead(SW2) == HIGH) {
            delay (50);
        }

        dl = dl / 2;
    }

    blink(dl);

    float freq = 500.0/dl;

    Serial.print("Frequency: ");
    Serial.println((float) freq);
}

void blink(uint8_t d) {
    for (uint8_t i = 0; i < sizeof(LEDS)/sizeof(LEDS[0]); i++) {
        digitalWrite(LEDS[i], HIGH);
    }

    delay(d);

    for (uint8_t i = 0; i < sizeof(LEDS)/sizeof(LEDS[0]); i++) {
        digitalWrite(LEDS[i], LOW);
    }

    delay(d);
}
