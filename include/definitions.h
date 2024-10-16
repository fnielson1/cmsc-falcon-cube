#pragma once

#include <ESP8266WiFi.h>

#define LED_PIN LED_BUILTIN

#define WIFI_MAX_CONNECT_ATTEMPTS 10 
#define WIFI_SLEEP_MS 500


/* -------------- SETTINGS TO CHANGE BELOW --------------------- */
// Comment this out if you are programming the controller instead of the cube.
#define IS_CUBE


// Remote controller IP address
IPAddress remoteControllerIP(192, 168, 2, 35);

// The IP address of the cube
IPAddress cubeIP(192, 168, 2, 36);


// The Remote Controller and the Cube should share these settings
const char ssid[] = "Monkey"; // SSID (also called the Network name or Wifi name)
const char pass[] = "nielsonfamilyhome"; // Wifi password

IPAddress gateway(192, 168, 2, 1);  // 192.168.2.1
IPAddress subnet(255, 255, 255, 0); // 255.255.255.0