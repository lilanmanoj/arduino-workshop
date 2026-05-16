#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseClient.h>

#define DHTPIN 1
#define DHTTYPE DHT11
#define PROG_DELAY 100
#define DHT_READ_DELAY 4000
#define ENABLE_USER_AUTH
#define ENABLE_DATABASE

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;
const char* web_api_key = API_KEY;
const char* database_url = DB_URL;
const char* auth_email = AUTH_EMAIL;
const char* auth_pass = AUTH_PASS;

unsigned long previousMillis = 0;
float humidity = 0;
float temp = 0;

// WiFi Secure Client Init
WiFiClientSecure ssl_client;

// DHT11 init
DHT dht(DHTPIN, DHTTYPE);

// Firebase Authentication
UserAuth user_auth(web_api_key, database_url, auth_pass);

// Firebase components
FirebaseApp app;
using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client);
RealtimeDatabase Database;

void processData(AsyncResult &aResult) {
  if (!aResult.isResult())
    return;

  if (aResult.isEvent())
    Firebase.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.eventLog().message().c_str(), aResult.eventLog().code());

  if (aResult.isDebug())
    Firebase.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());

  if (aResult.isError())
    Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());

  if (aResult.available())
    Firebase.printf("task: %s, payload: %s\n", aResult.uid().c_str(), aResult.c_str());
}

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

    // Configure SSL client
    ssl_client.setInsecure();
    ssl_client.setConnectionTimeout(1000);
    ssl_client.setHandshakeTimeout(5);
}

void setupFirebase() {
    // Initialize Firebase
    initializeApp(aClient, app, getAuth(user_auth), processData, "🔐 authTask");
    app.getApp<RealtimeDatabase>(Database);
    Database.url(database_url);
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    dht.begin();
    setupWiFi();
    setupFirebase();
}

void loop() {
    // Maintain authentication and async tasks
    app.loop();

    // Check if authentication is ready
    if (app.ready()){ 
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= DHT_READ_DELAY) {
            previousMillis = currentMillis;
            humidity = dht.readHumidity();
            temp = dht.readTemperature();

            if (isnan(humidity) || isnan(temp)) {
                Serial.println("Failed to read from DHT sensor!");
            } else {
                Serial.print("Temperature: ");
                Serial.print(temp);
                Serial.println(" °C");

                Serial.print("Humidity: ");
                Serial.print(humidity);
                Serial.println(" %");

                // send data to Firebase
                Database.set<float>(aClient, "/esp32/temperature", temp, processData, "RTDB_Send_Float");
                Database.set<float>(aClient, "/esp32/humidity", humidity, processData, "RTDB_Send_Float");
            }
        }

        delay(PROG_DELAY);
    }
}
