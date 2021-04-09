String ssid = ""; 
String password = "";

void setupWifi() {
  WiFi.begin(ssid, password);
  Serial.print("[INFO] Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.print("[INFO] Connected successfully with IP: ");
  Serial.println(WiFi.localIP());
}
