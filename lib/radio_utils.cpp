#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "definitions.h"
#include "radio_utils.h"


RF24 radio(PIN_CE, PIN_CSN); // CE, CSN


void setupRadio() {
  radio.begin();                  // Starting the Wireless communication
  radio.setDataRate(RF24_250KBPS);
  // radio.setPALevel(RF24_PA_MIN); // You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.setPALevel(RF24_PA_MAX); // You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.failureDetected = 0; // Reset the detection value

  #ifdef IS_CUBE
    radio.openReadingPipe(0, RADIO_ADDRESS); // Setting the address at which we will receive the data
    radio.startListening(); // This sets the module as receiver
  #else
    radio.openWritingPipe(RADIO_ADDRESS); // Setting the address where we will send the data
    radio.stopListening(); // This sets the module as transmitter
  #endif
}

void checkForFailure() {
  if (radio.failureDetected) {
    Serial.println(F("Radio failure detected"));
    setupRadio();
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
  }
}

void sendMessage(String msg) {
  Serial.print(F("Sending message: "));
  Serial.println(msg);
  boolean buttonState = true;
  radio.write(&buttonState, sizeof(buttonState)); // Sending the message to receiver
}

void receiveMessage() {
  if (radio.available()) {
    char msg[sizeof(boolean)];
    radio.read(&msg, sizeof(msg)); // Reading the message off the SPI bus

    Serial.print(F("Received message: "));
    Serial.println(msg);
  }
  else {
    Serial.println(F("Radio isn't available for listening"));
  }
}