#include <SPI.h>
#include "WiFi.h"
#include "ardOinus.h"
#include "ArdoFastLED.h"
#include <ArduinoOTA.h>
#include <ESPmDNS.h>

#include "parklights.h"
void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}