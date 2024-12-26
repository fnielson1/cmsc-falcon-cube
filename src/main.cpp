#include <Arduino.h>
#include <SPI.h>
#include "definitions.h"
#include "../lib/wifi_utils.cpp"
#include "../lib/speaker_utils.cpp"
#include "../lib/radio_utils.cpp"


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

  // setupWifi(); Cannot connect to 5Ghz wifi
  setupRadio();

  #ifdef IS_CUBE
    // setupServer(); Cannot connect to 5Ghz wifi
  #endif

  Serial.println("");
  Serial.println("Started up");
}

void loop() {
  checkForFailure();

  #ifdef IS_CUBE
    receiveMessage();
    delay(5);
  #else
    int shouldNotAlarm = digitalRead(ALARM_BUTTON_PIN);
    Serial.print(F("Should not alarm: "));
    Serial.println(shouldNotAlarm);

    // Debug
    sendMessage(ALARM_URL);

    if (!shouldNotAlarm) {
      digitalWrite(LED_PIN, LOW);
      // sendAction(ALARM_URL); // Cannot connect to 5Ghz wifi
      sendMessage(ALARM_URL);
    }
    digitalWrite(LED_PIN, HIGH);
    delay(500);
  #endif
}