#include "definitions.h"


void playAlarmAndLights() {
  for (int i = 0; i < ALARM_ITERATIONS; i++) {
    delay(SPEAKER_OFF_MS);

    Serial.println(F("SPEAKER ON"));
    digitalWrite(LED_PIN, LOW);
    digitalWrite(SPEAKER_OUTPUT_PIN, HIGH);

    delay(SPEAKER_ON_MS);

    Serial.println(F("SPEAKER OFF"));
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(SPEAKER_OUTPUT_PIN, LOW);
  }
}