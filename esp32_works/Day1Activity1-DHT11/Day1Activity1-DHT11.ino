#include<DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define PROG_DELAY 1000

float humidityP = 0;
float tempC = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    humidityP = dht.readHumidity();
    tempC = dht.readTemperature();

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidityP);
    Serial.println(" %");

    delay(PROG_DELAY);
}
