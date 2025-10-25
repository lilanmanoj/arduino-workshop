#include <WiFi.h>

const char* ssid = "UOC_Staff";
const char* password = "admin106";

void setup() {
    Serial.begin(9600);

    // Init wifi
    WiFi.begin(ssid, password);

    // Wait while wifi to connect
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWifi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
}
