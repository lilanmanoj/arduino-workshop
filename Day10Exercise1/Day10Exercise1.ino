#include <Arduino.h>

const uint8_t LED1 = 2;
const uint8_t LED2 = 3;

unsigned long led1LastMil = 0;
unsigned long led2LastMil = 0;

bool led1State = false;
bool led2State = false;


void setup() {
    // Debug purposes
    Serial.begin(9600);

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    digitalWrite(LED1, led1State);
    digitalWrite(LED2, led2State);
}

void loop() {
    if (millis() - led1LastMil >= 300) {
        // Serial com for debug purposes
        // Serial.print(millis() - led1LastMil);
        // Serial.print(" | ");
        Serial.print(led1State);
        Serial.println(" | Led 1");

        led1LastMil = millis();
        led1State = !led1State;

        digitalWrite(LED1, led1State);
    }

    if (millis() - led2LastMil >= 1000) {
        // Serial com for debug purposes
        // Serial.print(millis() - led2LastMil);
        // Serial.print(" | ");
        Serial.print(led2State);
        Serial.println(" | Led 2");

        led2LastMil = millis();
        led2State = !led2State;

        digitalWrite(LED2, led2State);
    }
}
