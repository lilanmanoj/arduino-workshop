#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <time.h>
#include "string.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;
const char* endpoint = "http://10.21.82.181:8080/iot/data_post.php";
const char* device_id = "24sea052";
const long interval = 5000; // Interval at which to send data (milliseconds)
unsigned long previousMillis = 0;
time_t now = time(nullptr);

WiFiClient client;
HTTPClient http;

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
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    Serial.print("Waiting for NTP time sync");
    int retry = 0;
    const time_t valid_time = 1514764800; // Jan 1, 2018
    while (now < valid_time && retry < 20) {
        Serial.print(".");
        delay(500);
        now = time(nullptr);
        retry++;
    }
    if (now < valid_time) {
        Serial.println("\n⚠️  NTP sync failed or slow.");
    } else {
        Serial.println("\n✅ Time synced.");
    }

    // Print epoch for debugging TLS verification issues
    Serial.print("Current epoch: ");
    Serial.println(now);
}

void connectGetRequest() {
    unsigned long timestamp = now + (millis() / 1000);
    // String data = "{\"lasttime\":\"" + String(previousMillis) + ", \"timestamp\":" + String(timestamp) + "\"device\":" + String(device_id) + "}";
    String data = "lasttime=" + String(previousMillis) + "&timestamp=" + String(timestamp) + "&device=" + String(device_id);
    String url = String(endpoint);

    // Connecting to endpoint
    Serial.print("Connecting with ");
    Serial.println(url);

    if (http.begin(client, url)) {
        Serial.println("✅ Connected");
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpResponseCode = http.POST(data);

        // httpResponseCode is negative on library error
        if (httpResponseCode > 0) {
            // Request sent and response handled
            Serial.printf("[HTTP] Response: %d\n", httpResponseCode);

            if (httpResponseCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] POST failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        // Closing the connection
        http.end();
    } else {
        Serial.println("❌ Connection failed");
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    setupWiFi();
    timeSync();
}

void loop() {
    if ((millis()-previousMillis) > interval && WiFi.status() == WL_CONNECTED) {
        connectGetRequest();
        previousMillis = millis();
    }
}
