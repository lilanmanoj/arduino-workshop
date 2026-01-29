#include <Arduino.h>
#include "cert.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <time.h>
#include <string.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;
const char* endpoint = "https://baconipsum.com/api/?type=meat-and-filler&paras=1";

WiFiClientSecure client;
HTTPClient https;

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

void connectGetRequest() {
    // Connecting to endpoint
    Serial.print("Connecting with ");
    Serial.println(endpoint);

    client.setCACert(root_ca);

    if (https.begin(client, endpoint)) {
        Serial.println("✅ Connected");
        
        int httpResponseCode = https.GET();

        // httpResponseCode is negative on library error
        if (httpResponseCode > 0) {
            // Request sent and response handled
            Serial.printf("[HTTPS] Response: %d\n", httpResponseCode);

            if (httpResponseCode == HTTP_CODE_OK) {
                String payload = https.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTPS] GET failed, error: %s\n", https.errorToString(httpResponseCode).c_str());
        }

        // Closing the connection
        https.end();
    } else {
        Serial.println("❌ Connection failed");
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    setupWiFi();
    timeSync();
    connectGetRequest();
}

void loop() {
    // put your main code here, to run repeatedly:
}
