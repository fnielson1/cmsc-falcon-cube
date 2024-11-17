#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include "definitions.h"
#include "wifi_utils.h"
#include "../lib/server_utils.cpp"


String wifiStatusToString(wl_status_t);
IPAddress convertCharArrayToIPAddress(IPAddress, const char*);


#ifndef IS_CUBE
  WiFiClient wifiClient;
  HttpClient httpClient(wifiClient, cubeIP);
#endif


void sendAction(String url) {
  #ifndef IS_CUBE
    int statusCode = 0;

    statusCode = httpClient.get(url);
    if (statusCode == 0)
    {
      Serial.println(F("startedRequest ok"));

      statusCode = httpClient.responseStatusCode();
      if (statusCode >= 0)
      {
        String response = httpClient.responseBody();
        Serial.print(F("Status code: "));
        Serial.println(statusCode);
        Serial.print(F("Response: "));
        Serial.println(response);
      }
      else
      {    
        Serial.print(F("Getting response failed: "));
        Serial.println(statusCode);
      }
    }
    else
    {
      Serial.print(F("Connect failed: "));
      Serial.println(statusCode);
      Serial.println(F("Attempting to reconnect"));
      setupWifi();
    }
  #endif 
 }


void setupWifi()
{
  WiFi.mode(WIFI_STA);

  #ifdef IS_CUBE
    IPAddress localIP = convertCharArrayToIPAddress(cubeIPAddress, cubeIP);
  #else
    IPAddress localIP = convertCharArrayToIPAddress(remoteControllerIPAddress, remoteControllerIP);
  #endif


  if (!WiFi.config(localIP, gateway, subnet))
  {
    Serial.println(F("STA Failed to configure"));
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print(F("Connecting to wifi"));
    WiFi.begin(ssid, pass);
  }

  for (int i = WIFI_MAX_CONNECT_ATTEMPTS; i >= 0; i--) {
    if (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_PIN, LOW);
      delay(WIFI_SLEEP_MS);
      Serial.print(".");
      digitalWrite(LED_PIN, HIGH);
      delay(WIFI_SLEEP_MS);
    }
    else {
      break;
    }
  }

  // Connected
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print(F("Connected, IP address: "));
    Serial.println(WiFi.localIP());

    digitalWrite(LED_PIN, HIGH);
  }
  else {
    Serial.println(F("Failed to connect to wifi."));
    Serial.println(F("Wifi status:"));
    Serial.println(wifiStatusToString(WiFi.status()));
  }
}


IPAddress convertCharArrayToIPAddress(IPAddress ipAddress, const char *ipChar)
{
  Serial.print(F("Attempting to convert to IPAddress: "));
  Serial.println(ipChar); 

  // try to parse into the IPAddress
  if (ipAddress.fromString(ipChar))
  {
    Serial.print(F("Converted to IPAddress: "));
    Serial.println(ipAddress); // print the parsed IPAddress
  }
  else
  {
    Serial.print(F("Failed to convert to IPAddress: "));
    Serial.println(ipChar); // print the parsed IPAddress

    Serial.println(F("UnParsable IP: ") + String(ipChar));
  }

  return ipAddress;
}

String wifiStatusToString(wl_status_t status) {
  switch (status)
  {
  case WL_IDLE_STATUS:
    return F("WL_IDLE_STATUS");
  case WL_NO_SSID_AVAIL:
    return F("WL_NO_SSID_AVAIL");
  case WL_SCAN_COMPLETED:
    return F("WL_SCAN_COMPLETED");
  case WL_CONNECTED:
    return F("WL_CONNECTED");
  case WL_CONNECT_FAILED:
    return F("WL_CONNECT_FAILED");
  case WL_CONNECTION_LOST:
    return F("WL_CONNECTION_LOST");
  case WL_WRONG_PASSWORD:
    return F("WL_WRONG_PASSWORD");
  default:
    return F("WL_DISCONNECTED");
  }
}