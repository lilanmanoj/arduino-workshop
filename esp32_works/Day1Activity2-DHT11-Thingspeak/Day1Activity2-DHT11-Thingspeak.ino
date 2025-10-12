#include <DHT.h>
#include <WiFi.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define PROG_DELAY 5000

DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "UOC_Staff";
const char *password = "admin106";

const char *host = "api.thingspeak.com";
const int httpPort = 80;
const String channelID = "3111734";
const String writeApiKey = "BFV9H4CXB4J7T25P";
const String readApiKey = "S8EOQQRY9TYN213N";
float humidityP = 0;
float tempC = 0;

void setup() {
    dht.begin();
    Serial.begin(9600);

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

    humidityP = dht.readHumidity();
    tempC = dht.readTemperature();

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidityP);
    Serial.println(" %");

    String footer = String(" HTTP/1.1\r\n") + "Host: " + String(host) + "\r\n" + "Connection: close\r\n\r\n";

    // WRITE --------------------------------------------------------------------------------------------
    if (!client.connect(host, httpPort)) {
        return;
    }

    client.print("GET /update?api_key=" + writeApiKey + "&field1=" + tempC + "&field2=" + humidityP + footer);
    readResponse(&client);

    delay(PROG_DELAY);
}
