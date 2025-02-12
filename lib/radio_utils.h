#pragma once

#define PIN_CE 4
#define PIN_CSN 15
#define MAX_MESSAGE_SIZE 32

// Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
const byte RADIO_ADDRESS[10] = "ADDR54321"; 


void setupRadio();
void checkForFailure();
void transmitMessage(String);
void receiveMessage();
