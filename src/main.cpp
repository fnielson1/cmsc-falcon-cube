#include <Arduino.h>
#include "definitions.h"
#include "../lib/wifi_utils.cpp"
#include "../lib/speaker_utils.cpp"


void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(ALARM_PIN, INPUT_PULLUP);

  Serial.begin(9600);

  // Wait for serial to initialize.
  while (!Serial)
  {
  }

  setupWifi();

  #ifdef IS_CUBE
    setupServer();
  #endif

  Serial.println("");
  Serial.println("Started up");
}

void loop() {
  #ifndef IS_CUBE
    int shouldNotAlarm = digitalRead(ALARM_PIN);
    Serial.print(F("Should not alarm: "));
    Serial.println(shouldNotAlarm);

    if (!shouldNotAlarm) {
      sendAction(ALARM_URL);
    }
    delay(500); // Do we even need to loop this frequently? Does it matter?
  #endif
}