#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "definitions.h"
#include "radio_utils.h"

RF24 radio(PIN_CE, PIN_CSN); // CE, CSN


void blinkFailure() {
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
  digitalWrite(LED_PIN, HIGH);
  Serial.println("");
  delay(1000);
}

void setupRadio() {
  // Starting the Wireless communication
  while (!radio.begin()) {                   
    Serial.println(F("nRF24L01 not found"));
    blinkFailure();
  }

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
    Serial.println(F("\nRadio failure detected\n"));
    blinkFailure();
    setupRadio();
  }
}

void sendMessage(String strMsg) {
  Serial.print(F("Sending message: "));
  Serial.println(strMsg);
  boolean buttonState = true;

  const char* charMsg = strMsg.c_str();

  digitalWrite(LED_PIN, LOW);
  radio.write(&charMsg, sizeof(charMsg)); // Sending the message to receiver

  boolean txOk = false;
  boolean txFail = false;
  boolean rxReady = false;

  radio.whatHappened(txOk, txFail, rxReady);

  if (!txOk) {
    Serial.println("Tx failed to send");
    blinkFailure();
  }

  if (txFail) {
    Serial.println(F("Tx failed to be acked\n"));
  }

  delay(500);
  digitalWrite(LED_PIN, HIGH);
}

void receiveMessage() {
  boolean txOk = false;
  boolean txFail = true;
  boolean rxReady = false;

  if (radio.available()) {
    char msg[MAX_MESSAGE_SIZE];
    radio.read(&msg, sizeof(msg)); // Reading the message off the SPI bus

    Serial.print(F("Received message: "));
    Serial.println(msg);
    delay(500);
  }
  else {
    Serial.println(F("Radio isn't available for listening"));

    radio.whatHappened(txOk, txFail, rxReady);

    if (!rxReady)
    {
      Serial.println(F("Rx not ready"));
    }
    blinkFailure();
  }
}