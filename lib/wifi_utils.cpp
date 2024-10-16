#include <Arduino.h>
#include "definitions.h"


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
  else {
    Serial.println("Failed to connect to wifi.");
    Serial.println("Wifi stats:");
    Serial.println(WiFi.status());
  }
}


void setupWifi()
{
  WiFi.mode(WIFI_STA);
  #ifdef IS_CUBE
    IPAddress localIP = cubeIP;
  #else
    IPAddress localIP = remoteControllerIP;
  #endif

  if (!WiFi.config(localIP, gateway, subnet))
  {
    Serial.println("STA Failed to configure");
  }
}