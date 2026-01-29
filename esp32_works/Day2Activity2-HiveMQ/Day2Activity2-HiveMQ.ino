#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "UOC_Staff";
const char* password = "admin106";
const char* mqtt_broker = "broker.hivemq.com";
const int port = 1883;
// const char *mqtt_username = "ea2121_04";
// const char *mqtt_password = "ea2121_04";
const String client_id = "clientId-24sea052";
const char* topic = "ea2121/04/24sea052";
const char* message = "Hello from group 04 - Lilan";
int lastTime = 0;

WiFiClient espClient;
PubSubClient client(espClient);

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

void loop() {
    client.loop();

    if (millis() - lastTime >= 1000) {
        lastTime = millis();
        Serial.println("Publishing message");
        client.publish(topic, message);
    }
}
