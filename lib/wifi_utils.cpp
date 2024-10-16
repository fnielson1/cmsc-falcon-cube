#include <Arduino.h>
#include "definitions.h"


/* Update the SSID, password, IP address, gateway, and subnet mask here */
const char ssid[] = "Monkey";
const char pass[] = "nielsonfamilyhome";
IPAddress localIP(192, 168, 2, 35);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);



void connectToWifiAndTransmitSignal() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to wifi");
    WiFi.begin(ssid, pass);
  }

  for (int i = WIFI_MAX_CONNECT_ATTEMPTS; i >= 0; i--) {
    if (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_PIN, LOW);
      delay(WIFI_SLEEP_MS);
      Serial.print(".");
      digitalWrite(LED_PIN, HIGH);
      delay(WIFI_SLEEP_MS);
    }
    else {
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    digitalWrite(LED_PIN, HIGH);
  }
}

void setupWifi()
{
  WiFi.mode(WIFI_STA);
  if (!WiFi.config(localIP, gateway, subnet))
  {
    Serial.println("STA Failed to configure");
  }
}