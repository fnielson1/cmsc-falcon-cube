#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "definitions.h"
#include "radio_utils.h"
#include "speaker_utils.h"


RF24 radio(PIN_CE, PIN_CSN); // CE, CSN


/**
 * Blink the LEDs if there is a failure
 */
void blinkFailure() {
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
  digitalWrite(LED_PIN, HIGH);
  Serial.println("");
  delay(1000);
}

/**
 * Setup the radio to get it ready to listen or transmit
 */
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

/**
 * Check if there is a radio failure
 */
void checkForFailure() {
  if (radio.failureDetected) {
    Serial.println(F("\nRadio failure detected\n"));
    blinkFailure();
    setupRadio();
  }
}

/**
 * Send a message
 */
void sendMessage(String strMsg) {
  char charMsg[MAX_MESSAGE_SIZE] = "";
  strncpy(charMsg, strMsg.c_str(), sizeof(charMsg));

  Serial.print(F("Sending message: "));
  Serial.println(charMsg);

  digitalWrite(LED_PIN, LOW);
  radio.write(&charMsg, sizeof(charMsg)); // Sending the message to receiver

  boolean txOk = false;
  boolean txFail = false;
  boolean rxReady = false;

  radio.whatHappened(txOk, txFail, rxReady);

  if (txFail) {
    Serial.println(F("Tx failed to be acked\n"));

    if (!txOk) {
      Serial.println("Tx failed to send");
    }
    blinkFailure();
  }

  digitalWrite(LED_PIN, HIGH);
}

/**
 * Determine the action to take based on the message contents
 */
void determineAction(char* msgArg) {
  String msg = String(msgArg);

  if (msg.compareTo(ALARM_URL)) {
    playAlarmAndLights();
  }
}

/**
 * Check if we've received a message
 */
void receiveMessage() {
  if (radio.available()) {
    radio.closeReadingPipe(0); // Don't get anymore requests until the alarm is done

    char msg[MAX_MESSAGE_SIZE] = "";
    radio.read(&msg, sizeof(msg)); // Reading the message off the SPI bus

    radio.flush_rx(); // Flush the buffer of any extra messages

    Serial.print(F("Received message: "));
    Serial.println(msg);

    determineAction(msg);

    playAlarmAndLights();

    radio.openReadingPipe(0, RADIO_ADDRESS);
  }
  else {
    Serial.println(F("No message received"));
  }
}