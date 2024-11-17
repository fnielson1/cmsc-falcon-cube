#include <Arduino.h>
#include "definitions.h"
#include "../lib/wifi_utils.cpp"
#include "../lib/speaker_utils.cpp"


void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(SPEAKER_OUTPUT_PIN, OUTPUT);
  pinMode(ALARM_BUTTON_PIN, INPUT_PULLUP);

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
    int shouldNotAlarm = digitalRead(ALARM_BUTTON_PIN);
    Serial.print(F("Should not alarm: "));
    Serial.println(shouldNotAlarm);

    if (!shouldNotAlarm) {
      digitalWrite(LED_PIN, LOW);
      sendAction(ALARM_URL);
    }
    digitalWrite(LED_PIN, HIGH);
    delay(500); // Do we even need to loop this frequently? Does it matter?
  #endif
}