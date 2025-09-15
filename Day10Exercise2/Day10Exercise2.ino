#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int TEMP = 2;
const int USS = 3;

long duration;
int distancecm;

unsigned long currentMil = 0;
unsigned long tempLastMil = 0;
unsigned long ussLastMil = 0;

OneWire oneWire(TEMP); // Setup a oneWire instance to communicate with any OneWire device
DallasTemperature sensors(&oneWire); // Pass oneWire reference to DallasTemperature library

void setup() {
    Serial.begin(9600);
    sensors.begin();

    pinMode(USS, INPUT);
}

void loop() {
    currentMil = millis();

    if (currentMil - tempLastMil >= 5000) {
        tempLastMil = currentMil;
        
        sensors.requestTemperatures(); // Send the command to get temperatures

        /** print the temperature in Celsius **/
        Serial.print("Temperature: ");
        Serial.print(sensors.getTempCByIndex(0));
        Serial.print((char)176); //shows degrees character
        Serial.println("C");
    }

    if (currentMil - ussLastMil >= 1000) {
        ussLastMil = currentMil;

        //Trigger the sensor with a 2usec HIGH pulse
        pinMode(8, OUTPUT);
        digitalWrite(8, HIGH);
        delayMicroseconds(2);
        digitalWrite(8, LOW);
        pinMode(8, INPUT);              //set pin as input   to read return pulse from sensor
        duration = pulseIn(8, HIGH);    //obtain length   of HIGH pulse in microseconds
        distancecm = duration*0.034/2;
        Serial.print("Distance: ");
        Serial.print(distancecm);
        Serial.println(" cm");
    }

    delay(1000);
}
