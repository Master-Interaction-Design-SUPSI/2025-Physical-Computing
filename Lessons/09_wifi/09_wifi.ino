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

}

void loop() {

}
