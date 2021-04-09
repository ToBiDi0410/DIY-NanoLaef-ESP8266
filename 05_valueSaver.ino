String fileName = "/config.json";

void saveAllData() {

  File configFile = SPIFFS.open(fileName, "w");

  if(configFile) {
    DynamicJsonDocument doc(1300);
    doc["wifi_ssid"] = ssid;
    doc["wifi_password"] = password;

    doc["curr_color"] = CRGBtoHex(curr_color);

    doc["effect_active"] = effect_active;
    doc["effect_name"] = effect_name;
    doc["effect_speed"] = effect_speed;

    doc["num_elements"] = NUM_ELEMENTS;
    doc["espalexa_name"] = espalexa_name;

    serializeJson(doc, configFile);
    configFile.close();
    Serial.println("[INFO] Saved Configuration to SPIFFS");
  } else {
    Serial.println("[ERROR] Config File could not be opened while trying to write!");
  }
  
  
}

boolean readAllData() {
  File configFile = SPIFFS.open(fileName, "r");

  if(configFile && configFile.size()) {
    DynamicJsonDocument configJson(1300);
    DeserializationError error = deserializeJson(configJson, configFile);
    if(error) {
      Serial.println("[WARNING] The Config File could not be loaded! Is it corrupt?");
      return false;
    }
    JsonObject obj = configJson.as<JsonObject>();

    //WIRELESS DATA
    String ssid_read = obj["wifi_ssid"];
    ssid = ssid_read;
    String password_read = obj["wifi_password"];
    password = password_read;
    
    //COLOR DATA
    String curr_color_hex_string = obj["curr_color"];
    curr_color = strtol(curr_color_hex_string.c_str(), NULL, 16);

    //EFFECT DATA
    effect_active = obj["effect_active"];
    String effect_name_zer = obj["effect_name"];
    effect_name = effect_name_zer;
    effect_speed = obj["effect_speed"];
    
    NUM_ELEMENTS = obj["num_elements"];
    NUM_LEDS = NUM_ELEMENTS * NUM_LEDS_PER_ELEMENT;

    String espalexa_name_read = obj["espalexa_name"];
    espalexa_name = espalexa_name_read;
    
    configFile.close();
    Serial.println("[INFO] Loaded Configuration from SPIFFS");
    return true;
    
  } else {
    Serial.println("[WARNING] The Config File was not found!");
    return false;
  }
}
