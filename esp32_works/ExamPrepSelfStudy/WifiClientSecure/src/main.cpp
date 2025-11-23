#include <Arduino.h>
#include "cert.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include <string.h>

// Set to 1 to disable certificate verification (INSECURE, testing only)
#define USE_INSECURE 0

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;
const char* server = "baconipsum.com";
const uint16_t httpsPort = 443;

WiFiClientSecure client;

// helper to print WiFiClientSecure last error (if available)
void printLastError(WiFiClientSecure &c) {
    char buf[256];
    memset(buf, 0, sizeof(buf));
    int r = c.lastError(buf, sizeof(buf));
    if (r != 0) {
        Serial.print("lastError() returned "); Serial.print(r); Serial.print(" -> ");
    }
    if (strlen(buf)) {
        Serial.print("TLS lastError: ");
        Serial.println(buf);
    } else if (r != 0) {
        Serial.println("TLS lastError: <no text>");
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("Connecting to WiFi");

    // Connect to WiFi network
    WiFi.begin(ssid, password);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("✅ WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

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

    Serial.print("Connecting to ");
    Serial.println(server);

    // Configure TLS: use either the provided CA or an insecure connection for testing
    #if USE_INSECURE
        Serial.println("⚠️  Using INSECURE TLS (certificate verification disabled)");
        client.setInsecure();
    #else
        // Setting the root CA certificate (preferred)
        client.setCACert(root_ca);
    #endif

    if (client.connect(server, httpsPort)) {
        Serial.println("✅ Connected");
        // Make a HTTPS request:
        client.print("GET /api/?type=meat-and-filler&paras=1\r\n");
        client.print("Host: baconipsum.com\r\n");
        client.print("Accept: application/json\r\n");
        client.print("User-Agent: ESP32-WiFiClientSecure\r\n");
        client.print("Connection: close\r\n\r\n");

        String line = client.readStringUntil('\n');
        while (client.available()) {
            line = client.readStringUntil('\n');
            Serial.println(line);
        }

        printLastError(client);
        client.stop();
        Serial.println("Client disconnected!");
    } else {
        Serial.println("❌ Connection failed");
    }
}

void loop() {
    // put your main code here, to run repeatedly:
}
