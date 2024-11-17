#pragma once

#include <ESP8266WiFi.h>

#define LED_PIN LED_BUILTIN
#define LED_PIN_1 D5 
#define LED_PIN_2 D6 
#define LED_PIN_3 D7 
#define LED_PIN_4 D8
#define SPEAKER_OUTPUT_PIN SDA
#define ALARM_BUTTON_PIN SCL 

#define WIFI_MAX_CONNECT_ATTEMPTS 10 
#define WIFI_SLEEP_MS 500


/* -------------- SETTINGS TO CHANGE BELOW --------------------- */
// Comment this out if you are programming the controller instead of the cube.
// #define IS_CUBE


/* ------------ REMOTE ----------- */
// Remote controller IP address (change as needed)
const char remoteControllerIP[] = "192.168.2.35";
IPAddress remoteControllerIPAddress;


/* ------------ CUBE ----------- */
// The IP address of the cube (change as needed)
const char cubeIP[] = "192.168.2.36";
IPAddress cubeIPAddress;

// Change the speaker timing (if you like)
#define ALARM_ITERATIONS 10
#define SPEAKER_OFF_MS 100
#define SPEAKER_ON_MS 50


/* ----------- SHARED ------------ */
const char ssid[] = "network_name"; // SSID (also called the Network name or Wifi name)
const char pass[] = "password"; // Wifi password

// Change these IP Addresses as needed
IPAddress gateway(192, 168, 2, 1);  // 192.168.2.1
IPAddress subnet(255, 255, 255, 0); // 255.255.255.0