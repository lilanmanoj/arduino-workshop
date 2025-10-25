#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;
const char* mqtt_broker = "broker.hivemq.com";
const int port = 1883;
const String client_id = "esp32s3-client-24sea052";
const char* topic = "ea2121/group04/24sea052";
const char* message = "Hello from group 04 - 24SEA052";
int lastTime = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void setup() {
    Serial.begin(115200);

    // Init wifi
    WiFi.disconnect();
    delay(1000);
    WiFi.begin((char*)ssid, (char*)password);

    // Wait while wifi to connect
    Serial.printf("Wifi connecting to SSID: %s\n", ssid);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(1000);
        int status = WiFi.status();
        Serial.printf("Attempt %d - WiFi Status: %d\n", attempts + 1, status);
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
    } else {
        Serial.println("\nWiFi connection failed!");
        ESP.restart();
    }

    // MQTT Connection
    client.setServer(mqtt_broker, port);
    client.setCallback(callback);
    while (!client.connected()) {
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str())) {
            Serial.println("Public Hive MQTT broker connected!");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    client.subscribe(topic);

    // Publishing message
    Serial.println("Publishing message");
    client.publish(topic, message);
}

void loop() {
    client.loop();
}
