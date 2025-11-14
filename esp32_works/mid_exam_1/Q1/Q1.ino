#include <WiFi.h>

const char *ssid = "UOC_Staff";
const char *password = "admin106";

const char *host = "10.21.92.169";
const int httpPort = 80;

const int PROG_DELAY = 1000;

void setup() {
    Serial.begin(115200);

    // We start by connecting to a WiFi network
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
}

void readResponse(NetworkClient *client) {
    unsigned long timeout = millis();
    while (client->available() == 0) {
        if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client->stop();
        return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while (client->available()) {
        String line = client->readStringUntil('\r');
        Serial.print(line);
    }

    Serial.printf("\nClosing connection\n\n");
}

void loop() {
    NetworkClient client;

    String footer = String(" HTTP/1.1\r\n") + "Host: " + String(host) + "\r\n" + "Connection: close\r\n\r\n";

    // WRITE --------------------------------------------------------------------------------------------
    // if (!client.connect(host, httpPort)) {
    //     return;
    // }

    client.print("GET /24sea052" + footer);
    readResponse(&client);

    delay(PROG_DELAY);
}
