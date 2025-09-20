#include<Arduino.h>
#include<DHT.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11
#define US_TRIG 3
#define US_ECHO 4
#define PROG_DELAY 1000

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

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(" ");
    Serial.print((char)223);
    Serial.println("C");

    Serial.print("Humidity: ");
    Serial.print(humidityP);
    Serial.println(" %");

    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");

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
