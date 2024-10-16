#include <Arduino.h>
#include "definitions.h"
#include "../lib/wifi_utils.cpp"


void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);

  // Wait for serial to initialize.
  while (!Serial)
  {
  }

  setupWifi();

  Serial.println("");
  Serial.println("Started up");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, LOW);
  delay(500);
  connectToWifiAndTransmitSignal();
  digitalWrite(LED_PIN, HIGH);
  delay(500);
}