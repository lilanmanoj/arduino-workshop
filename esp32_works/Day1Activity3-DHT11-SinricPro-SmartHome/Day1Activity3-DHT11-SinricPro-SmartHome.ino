#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

const char* ssid = "UOC_Staff";
const char* password = "admin106";

const char* APP_KEY = "ca1d8f8f-f387-4b78-ad6b-b271e2441e61";
const char* APP_SECRET = "8662cc80-659c-4f80-86a5-46c9a7b2fac6-f4b25c38-e382-48c3-9008-1cff342070d2";
const char* SWITCH_ID = "68eb8634ba649e246c0b94d0";

const int relayPin = RGB_BUILTIN;

void setupWiFi() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

bool onPowerState(String deviceId, bool &state) {
  digitalWrite(relayPin, state ? HIGH : LOW);
  Serial.printf("Device %s turned %s\r\n", deviceId.c_str(), state?"ON":"OFF");
  return true;
}

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Relay off

  setupWiFi();
  
  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];
  mySwitch.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  SinricPro.handle();
}