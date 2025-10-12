#include <DHT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define PROG_DELAY 3000

const char *ssid = "UOC_Staff";
const char *password = "admin106";
const String scriptUrl = "https://script.google.com/macros/s/AKfycbzZSe03aQPkWeqjTLWhR0jF1ZwBClJ3so8kJGUrFkzM-lSk_ASp30GyzTGC0T-gw2mz/exec";

float humidityP = 0;
float tempC = 0;

DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure espClient; // Secure client for TLS connection

void publishData(float temperature, float humidity) {
  HTTPClient https;
  https.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);  // Enable redirect following

  if (https.begin(espClient, scriptUrl)) {
    https.addHeader("Content-Type", "application/json");
    String message = "{\"temperature\":\"" + String(temperature) + "\",\"humidity\":\"" + String(humidity) + "\"}";
    int httpCode = https.POST(message);
    if (httpCode > 0) {
      Serial.printf("POST... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        String payload = https.getString();
        Serial.println("Response: " + payload);
      } else {
        Serial.printf("POST failed with code: %d\n", httpCode);
      }
    } else {
      Serial.printf("POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  } else {
    Serial.println("Unable to connect");
  }
}

void setup() {
    Serial.begin(9600);
    dht.begin();

    Serial.println();
    Serial.println("******************************************************");
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /** Use this line to ignore SSL certificate verification for simplicity.
     * Remove in production for security.
     **/
    espClient.setInsecure();
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

    publishData(tempC, humidityP);

    delay(PROG_DELAY);
}
