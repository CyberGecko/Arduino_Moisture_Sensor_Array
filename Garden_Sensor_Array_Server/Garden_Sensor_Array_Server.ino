#include "WebServer.h"

WebServer SensorArrayWebServer;

void setup() {
  Serial.begin(9600);
}

void loop() {
  SensorArrayWebServer.handleClient();
  delay(100);
}
