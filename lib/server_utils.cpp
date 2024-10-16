#include "definitions.h"
#include "server_utils.h"
#include "speaker_utils.h"


AsyncWebServer server(80);

const String ALARM_URL = "/alarm";



void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", F("404 Not found"));
}

void setupServer() {
  server.on(ALARM_URL.c_str(), HTTP_GET, [](AsyncWebServerRequest *request) {
          Serial.println(F("GET: ") + ALARM_URL);

          playAlarmAndLights();

          request->send(200, "text/plain", F("Hello, GET: ALARMING")); 
          });

  server.onNotFound(notFound);

  server.begin();
  Serial.println(F("Listening"));
}