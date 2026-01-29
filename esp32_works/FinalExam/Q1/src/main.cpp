#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <time.h>
#include <string.h>

#define DHTPIN 1
#define DHTTYPE DHT11
#define TOGGLE_PIN 2
#define PROG_DELAY 100
#define DHT_READ_DELAY 10000
#define TOGGLE_DELAY 60000

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

unsigned long previousToggleMillis = 0;
unsigned long previousDhtReadMillis = 0;
float humidityP = 0;
float tempC = 0;

DHT dht(DHTPIN, DHTTYPE);
WiFiServer server(80);

void setupWiFi() {
    Serial.print("\nConnecting to WiFi");

    // Connect to WiFi network
    WiFi.begin(ssid, password);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\n✅ WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void timeSync() {
    // Configure time via NTP. TLS certificate validation requires correct system time.
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    Serial.print("Waiting for NTP time sync");
    time_t now = time(nullptr);
    int retry = 0;
    const time_t valid_time = 1514764800; // Jan 1, 2018
    while (now < valid_time && retry < 20) {
        Serial.print(".");
        delay(1000);
        now = time(nullptr);
        retry++;
    }
    if (now < valid_time) {
        Serial.println("\n⚠️  NTP sync failed or slow. TLS may fail if clock is wrong.");
    } else {
        Serial.println("\n✅ Time synced.");
    }

    // Print epoch for debugging TLS verification issues
    Serial.print("Current epoch: ");
    Serial.println(now);
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(TOGGLE_PIN, OUTPUT);

    dht.begin();
    setupWiFi();
    timeSync();
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousToggleMillis >= TOGGLE_DELAY) {
        previousToggleMillis = currentMillis;
        digitalWrite(TOGGLE_PIN, !digitalRead(TOGGLE_PIN));
        Serial.println("Toggled pin state.");
    }

    if (currentMillis - previousDhtReadMillis >= DHT_READ_DELAY) {
        previousDhtReadMillis = currentMillis;
        humidityP = dht.readHumidity();
        tempC = dht.readTemperature();

        if (isnan(humidityP) || isnan(tempC)) {
            Serial.println("Failed to read from DHT sensor!");
        } else {
            Serial.print("Temperature: ");
            Serial.print(tempC);
            Serial.println(" °C");

            Serial.print("Humidity: ");
            Serial.print(humidityP);
            Serial.println(" %");
        }
    }

    WiFiClient client = server.available();
    if (!client) return;

    String req = client.readStringUntil('\r');
    Serial.println(req);

    // Wait for request
    while (!client.available()) delay(1);

    client.read();  // skip \n
    Serial.println(req);

    // -------------------------------
    // JSON ENDPOINT
    // -------------------------------
    if (req.startsWith("GET /dht")) {
        // Build JSON
        String json = "{";
        json += "\"temperature\": " + String(tempC, 1) + ",";
        json += "\"humidity\": " + String(humidityP, 1);
        json += "}";

        // Send HTTP headers
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: application/json");
        client.println("Access-Control-Allow-Origin: *");
        client.println("Connection: close");
        client.println();

        // Send body
        client.println(json);

        return;
    }

    // Unknown endpoint
    client.println("HTTP/1.1 404 Not Found");
    client.println("Connection: close");
    client.println();

    delay(PROG_DELAY);
}
