#include <Arduino.h>
#include <SPI.h>
#include "definitions.h"
#include "../lib/wifi_utils.cpp"
#include "../lib/speaker_utils.cpp"
#include "../lib/radio_utils.cpp"


void setup() {
  pinMode(LED_PIN, OUTPUT);

  #ifdef IS_CUBE
  // pinMode(LED_PIN_1, OUTPUT);
  // pinMode(LED_PIN_2, OUTPUT);
  // pinMode(LED_PIN_3, OUTPUT);
  // pinMode(LED_PIN_4, OUTPUT);
    pinMode(SPEAKER_OUTPUT_PIN, OUTPUT);
  #else
    // setupServer(); Cannot connect to 5Ghz wifi
    pinMode(ALARM_BUTTON_PIN, INPUT_PULLUP); // No need to use the alarm button pin if we are the cube
  #endif


  Serial.begin(9600);

  digitalWrite(LED_PIN, HIGH);

  // setupWifi(); Cannot connect to 5Ghz wifi
  setupRadio();

  Serial.println("");
  Serial.println("Started up");
}

void loop() {
  checkForFailure();

  #ifdef IS_CUBE
    receiveMessage();
  #else
    int shouldNotAlarm = digitalRead(ALARM_BUTTON_PIN);
    Serial.print(F("Should not alarm: "));
    Serial.println(shouldNotAlarm);

    if (!shouldNotAlarm) {
      digitalWrite(LED_PIN, LOW);
      // sendAction(ALARM_URL); // Cannot connect to 5Ghz wifi
      sendMessage(ALARM_URL);
    }
    digitalWrite(LED_PIN, HIGH);
    delay(10);
  #endif
}