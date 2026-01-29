#include <Arduino.h>
#include <WiFi.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;
const char* server = "www.google.com";

WiFiClient client;

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

    Serial.print("Connecting to ");
    Serial.println(server);

    if (client.connect(server, 80)) {
        Serial.println("✅ Connected");
        // Make a HTTP request:
        client.println("GET /search?q=arduino HTTP/1.0");
        client.println();

        String line = client.readStringUntil('\n');
        while (client.available()) {
            line = client.readStringUntil('\n');
            Serial.println(line);
        }

        client.stop();
        Serial.println("Client disconnected!");
    } else {
        Serial.println("❌ Connection failed");
    }
}

void loop() {
    // put your main code here, to run repeatedly:
}