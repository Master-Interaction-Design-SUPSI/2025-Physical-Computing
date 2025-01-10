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

char msg_buffer[30];

#include "index.h"
#include "js.h"
#include "css.h"

// pinout
int pin_button_on = 11;
int pin_button_off = 10;
int pin_pot = A0;

// variables
bool old_off_button = 0;
bool old_on_button = 0;
unsigned long old_millis_pot = 0;
int pot_read_interval = 20;  // milliseconds
int client_count = 0; // number of clients

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
  webServer.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/script", scriptJS);
  });
  webServer.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/css", styleCSS);
  });

  webServer.begin();

  // webSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvents);

  //pinout
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pin_button_on, INPUT);
  pinMode(pin_button_off, INPUT);

}

void loop() {
  webSocket.loop();
  readOnButton();
  readOffButton();
  readPot();
}


void readOnButton() {
  bool btn_val = digitalRead(pin_button_on);
  if(btn_val == 1 && old_on_button == 0) { // rising edge
    Serial.println("Button ON pressed");
    digitalWrite(LED_BUILTIN, HIGH);
    sendClientMessage("ON");
    old_on_button = 1;
  }
  else if(btn_val == 0 && old_on_button == 1) { // falling edge
    old_on_button = 0;
  }
}

void readOffButton() {
  bool btn_val = digitalRead(pin_button_off);
  if(btn_val == 1 && old_off_button == 0) { // rising edge
    Serial.println("Button OFF pressed");
    digitalWrite(LED_BUILTIN, LOW);
    sendClientMessage("OFF");
    old_off_button = 1;
  }
  else if(btn_val == 0 && old_off_button == 1) { // falling edge
    old_off_button = 0;
  }
}

void readPot() {
  if(millis() - old_millis_pot > pot_read_interval) {
    int pot_value = map(analogRead(pin_pot), 0, 4095, 0, 100);
    sendClientMessage(String(pot_value));
    old_millis_pot = millis();
  }
}

void sendClientMessage(String text) {
  sprintf(msg_buffer, "%s", text);
  for(int i=0; i<client_count; i++) {
    webSocket.sendTXT(i, msg_buffer);
  }
}

void webSocketEvents(uint8_t client_num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println(String(client_num) + " disconnected!");
      client_count--;
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_num);
        Serial.print(String(client_num) + " connected from IP ");
        Serial.println(ip.toString());
        client_count++;
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
    sendClientMessage("ON");
  }
  else if(msg.equals("OFF")) {
    digitalWrite(LED_BUILTIN, LOW);
    sendClientMessage("OFF");
  }
}

