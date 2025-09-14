#include <Arduino.h>

const int LED1 = 2;
const int LED2 = 3;

unsigned long currentMil = 0;
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
    currentMil = millis();

    if (currentMil - led1LastMil >= 300) {
        // Serial com for debug purposes
        // Serial.print(millis() - led1LastMil);
        // Serial.print(" | ");
        Serial.print(led1State);
        Serial.println(" | Led 1");

        led1LastMil = currentMil;
        led1State = !led1State;

        digitalWrite(LED1, led1State);
    }

    if (currentMil - led2LastMil >= 1000) {
        // Serial com for debug purposes
        // Serial.print(millis() - led2LastMil);
        // Serial.print(" | ");
        Serial.print(led2State);
        Serial.println(" | Led 2");

        led2LastMil = currentMil;
        led2State = !led2State;

        digitalWrite(LED2, led2State);
    }
}
