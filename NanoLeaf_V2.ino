#define ESPALEXA_ASYNC

#include <FS.h>
#include "uptime_formatter.h"
#include <FastLED.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Espalexa.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

extern String DEVICE_NAME = "ESP8266";
extern String FIRMWARE_VERSION = "v1.0.1";
extern String ESPALEXA_VERSION = "v2.7.0";
extern String LED_DRIVER = "FastLED";
extern String LED_DRIVER_VERSION = "v3.4.0";
extern String LED_TYPE_STR = "WS2812B";

boolean fs_mounted = false;

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println(" ");
  if(!SPIFFS.begin()){
    Serial.println("[FATAL] An Error has occurred while mounting SPIFFS");
    return;
  } else {
    fs_mounted = true; 
  }

  readAllData();
 
  setupWifi();
  lightSetup();
  webServerSetup();
  espAlexaSetup();
}

void loop() {
  getEspAlexa().loop();  
  Effect_Rainbow_Loop();
  Effect_Stars_Loop();
  Effect_RainbowGlobal_Loop();
  Effect_Breath_Loop();
  Effect_Bolt_Loop();
  Effect_Row_Loop();
  delay(1);
}
