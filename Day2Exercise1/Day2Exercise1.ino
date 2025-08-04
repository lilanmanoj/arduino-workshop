#include <Arduino.h>

const int SW = 11;
const int LED = 13;

void setup() {
    pinMode(SW, INPUT); // Set pin 11 as an input
    pinMode(LED, OUTPUT); // Set pin 11 as an output
}

void loop() {
    bool state = digitalRead(SW); // Read the state of the switch

    if (state) {
        digitalWrite(LED, HIGH); // Turn on the LED if the switch is pressed
    } else {
        digitalWrite(LED, LOW); // Turn off the LED if the switch is not pressed
    }
}
