/*
  libraries to install:
  - WebSockets by Markus Sattler
  - ESPAsyncWebServer by Me-No-Dev
  - Async TCP by Me-No-Dev
*/

#include <WiFi.h>
#include <WebSocketsServer.h>   // ws, port 8080
#include <ESPAsyncWebServer.h>  // http, port 80

const char *ssid = "Marco-Wifi";
const char *password = NULL;
const int dns_port = 53;

AsyncWebServer webServer(80);
WebSocketsServer webSocket = WebSocketsServer(8080);

#include "index.h"


void setup() {

  Serial.begin(9600);

  // Wifi network
  WiFi.softAP(ssid, password);
  delay(2000);
  Serial.println("Access Point active!");
  Serial.print("Arduino IP address: ");
  Serial.println(WiFi.softAPIP());

  // webServer
  webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", indexHtml);
  });
  webServer.begin();

  // webSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvents);

  //pinout
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  webSocket.loop();
}

void webSocketEvents(uint8_t client_num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println(String(client_num) + " disconnected!");
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_num);
        Serial.print(String(client_num) + " connected from IP ");
        Serial.println(ip.toString());
      }
      break;
    case WStype_TEXT:
      String msg = String((char *)payload);
      decodeMessage(msg);
      break;
  }
}

void decodeMessage(String msg) {
  if(msg.equals("ON")) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if(msg.equals("OFF")) {
    digitalWrite(LED_BUILTIN, LOW);
  }
}






