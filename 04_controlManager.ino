String espalexa_name = "NanoLeaf";

Espalexa espalexa;
AsyncWebServer server(80);

void espalexaColorChange(uint8_t brightness, uint32_t rgb);

void webServerSetup() {
  server.onNotFound([](AsyncWebServerRequest *request){
    if (!espalexa.handleAlexaApiCall(request)) //if you don't know the URI, ask espalexa whether it is an Alexa control request
      {
        //whatever you want to do with 404s
        request->send(404, "text/plain", "Not found");
      }
  });

  server.serveStatic("/", SPIFFS, "/www/").setTemplateProcessor(placeholderManager).setDefaultFile("index.html");

  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {
    if(request->hasParam("action", true)) {
      String action = request->getParam("action", true)->value();
      if(action == "changecolor" && request->hasParam("newcolor", true)) {
          String newColor = request->getParam("newcolor", true)->value();
          long color = strtol(newColor.c_str(), NULL, 16);
          
          if(effect_supportcolors && effect_active) {
            curr_color = color;
            saveAllData();
          } else{
            colorChanged();
            setColorOfAllLeds(color);
            saveAllData();
          }
          request->send(200, "text/plain", "Success");
          return;
      }
      if(action == "changemode" && request->hasParam("newmode", true)) {
        String newMode = request->getParam("newmode", true)->value();
        changeEffect(newMode);
        request->send(200, "text/plain", "Success");
        return;
      }
      if(action == "changemodespeed" && request->hasParam("newspeed", true)) {
        String newSpeed = request->getParam("newspeed", true)->value();
        effect_speed = newSpeed.toFloat();
        saveAllData();
        request->send(200, "text/plain", "Success");
        return;
      }
      if(action == "get_currentcolor") {
        request->send(200, "text/plain", "#" + CRGBtoHex(curr_color));
        return;
      }
      if(action == "get_currentmodespeed") {
        request->send(200, "text/plain", String(275 - effect_speed * 100));
        return;
      }
    }
    request->send(400, "text/plain", "Your Request could not be Processed");
  });
}

void espAlexaSetup() {
  espalexa.addDevice(espalexa_name, espalexaColorChange);
  espalexa.begin(&server);
}

String placeholderManager(const String& var) {
  if(var == "UPTIME") {
    return String(uptime_formatter::getUptime());
  }
  if(var == "CURRENT_COLOR") {
    //return "'" + CRGBtoHexHTMLString(getCurrentColor()) + "'";
  }

  if(var == "LEAF_COUNT") {
    return String(NUM_ELEMENTS);
  }

  if(var == "LED_COUNT") {
    return String(NUM_LEDS);
  }

  if(var == "DEVICE_NAME") {
    return DEVICE_NAME;
  }

  if(var == "HOSTNAME") {
    return WiFi.hostname();
  }

  if(var == "ESPALEXA_NAME") {
    return espalexa_name;
  }

  if(var == "IP_ADDRESS") {
    return WiFi.localIP().toString();
  }

  if(var == "FIRM_VERSION") {
    return FIRMWARE_VERSION;
  }

  if(var == "ESPALEXA_VERSION") {
    return ESPALEXA_VERSION;
  }

  if(var == "LED_DRIVER") {
    return LED_DRIVER;
  }

  if(var == "LED_TYPE") {
    return  LED_TYPE_STR;
  }

  if(var == "FIRM_AUTHOR") {
    return "Tobias Dickes";
  }

  if(var == "LED_DRIVER_VERSION") {
    return LED_DRIVER_VERSION;
  }
  
  return "NULL";
}

Espalexa getEspAlexa() {
  return espalexa;
}
