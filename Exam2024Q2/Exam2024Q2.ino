#include<Arduino.h>
#include<DHT.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11
#define US_TRIG 3
#define US_ECHO 4
#define PROG_DELAY 10

String command = "";
bool displayDone = false;
float humidityP = 0;
float tempC = 0;
long durationMicro = 0;
float distanceCm = 0;

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    dht.begin();
    Serial.begin(9600);

    pinMode(US_TRIG, OUTPUT);
    pinMode(US_ECHO, INPUT);
}

void loop() {
    humidityP = dht.readHumidity();
    tempC = dht.readTemperature();
    distanceCm = getDistance();

    if (Serial.available()) {
        command = Serial.readStringUntil('\n');
        displayDone = false;
    }

    if (command == "read_temp" && !displayDone) {
        Serial.print("Temperature: ");
        Serial.print(tempC);
        Serial.println(" °C");

        displayDone = true;
    }

    if (command == "read_humid" && !displayDone) {
        Serial.print("Humidity: ");
        Serial.print(humidityP);
        Serial.println(" %");

        displayDone = true;
    }

    if (command == "read_dist" && !displayDone) {
        Serial.print("Distance: ");
        Serial.print(distanceCm);
        Serial.println(" cm");

        displayDone = true;
    }

    delay(PROG_DELAY);
}

float getDistance() {
    digitalWrite(US_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(US_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(US_TRIG, LOW);

    durationMicro = pulseIn(US_ECHO, HIGH);

    return (durationMicro * 0.0343) / 2;
}
