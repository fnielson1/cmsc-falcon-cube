#include "definitions.h"


void playAlarmAndLights() {
  for (int i = 0; i < ALARM_ITERATIONS; i++) {
    delay(SPEAKER_OFF_MS);

    Serial.println(F("SPEAKER ON"));
    digitalWrite(LED_PIN, LOW); // This has inverse logic (I don't know why)
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(LED_PIN_3, HIGH);
    digitalWrite(LED_PIN_4, HIGH);
    digitalWrite(SPEAKER_OUTPUT_PIN, HIGH);

    delay(SPEAKER_ON_MS);

    Serial.println(F("SPEAKER OFF"));
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);
    digitalWrite(LED_PIN_4, LOW);
    digitalWrite(SPEAKER_OUTPUT_PIN, LOW);
  }
}