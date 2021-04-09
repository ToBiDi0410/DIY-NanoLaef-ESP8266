# DIY-NanoLaef-ESP8266
Eine Repository mit der Software zur Steuerung von DIY NanoLeafs basierend auf WS2812B Leds mit jeweils 3 Leds pro Stück.

## Vorwort
Ich habe dieses "Steuerungssystem" in meiner Freizeit Entwickelt. Bugs können deshalb eventuell sehr lange bestehen bis sie behoben werden!

## Projektinfos
Dieses Projekt beeinhaltet die Arduino Software zum steuern von meinen DIY-NanoLeafs. Die NanoLeafs bestehen jeweils aus 3 Leds (in jeder Ecke der Dreiecke eine LED), dies kann manuell (hier kein Tutorial dazu) geändert werden (einfach für Fortgeschrittene Nutzer).

## Features
- Webinterface (Cross-Kompatibel) (Nur deutsch)
- Alexa Support
- Verschiedene Effekte
- Basierend auf FastLED und somit für viele LED-Type einsetzbar
- Deutsches Webinterface
- Speicherung des aktuellen Zustands bei Trennung der Stromverbindung

## Installation

### Vorbereitung
Um dieses Projekt zu kompilieren benötigst du folgende Bibliotheken installiert (in deiner Arduino IDE):
- FastLED: https://github.com/FastLED/FastLED/archive/refs/tags/3.4.0.zip
- ESPAlexa: https://github.com/Aircoookie/Espalexa/archive/refs/tags/v2.7.0.zip
- ArduinoJSON: https://github.com/bblanchon/ArduinoJson/releases/download/v6.17.3/ArduinoJson-v6.17.3.zip
- ESPAsyncWebServer: https://github.com/me-no-dev/ESPAsyncWebServer
- ESPAsyncTCP: https://github.com/me-no-dev/ESPAsyncTCP

Ausserdem musst du das ESP8266 Board installiert haben!
(Einfach Googlen, ist nicht so schwer :))

Um die Dateien auf den ESP8266 zu flashen, benötigst du ausserdem:
- SPIFFS Uploader für ESP8266: https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.5.0/ESP8266FS-0.5.0.zip

### Flashen
Öffne nachdem du alle Vorbereitungen abgeschlossen hast, die Datei 'NanoLeaf_V2.ino' aus diesem Projekt mit der Arduino IDE (Entweder bei Windows --> Rechtsklick --> Öffnen mit --> Arduino IDE oder erst die IDE starten und dann oben links Datei --> Öffnen)

Nun sollten sich mehrere Dateien in der Arduino IDE öffnen. 

Öffne nun mit einem Text-Editor die Datei 'Data --> config.json' aus dem Sketch Ordner von hier, und fügst bei 'wifi_ssid' in den Anführungszeichen dahinter deine WLAN SSID ein und bei 'wifi_password' dein WLAN Passwort. Zudem musst du bei 'num_elements' die Zahl durch die Anzahl verschiedener Elemente ersetzen (in diesem Fall die Anzahl der NanoLeafs).
Den LED Pin (Data) kannst du in der Datei '02_lightmanager.ino' ändern. Standardmäßig ist es GPIO 2 was z.B. bei eiem Wemos D1 Mini der Pin D2 ist. Wichtig ist dass als Board 'Generic ESP8266' gewählt ist, damit die Alexa Funktion funktioniert.

#### !WICHTIG! Öffne nun den Libraries Ordner deiner Arduino IDE und gehe zu 'ESPAsyncWebServer' --> 'src' --> 'WebResponseImpl.h'.
#### Ändere nun in Zeile 63 "#define TEMPLATE_PLACEHOLDER '%'" zu "#define TEMPLATE_PLACEHOLDER '~'"

Nutz du den ESP8266 und WS2812B LEDs, dann kannst du den Sketch nun einfach hochladen. Benutzt du andere LEDs musst du in der Datei '02_lightManager.ino' '#define LED_TYPE WS2812B' zu deinem gewünschten LED-Modell ändern (VORSICHT! Es muss auch von FastLED unterstützt werden)

Nachdem der Sketch hochgeladen ist, musst du noch das Dateisystem hochladen. Das geht indem du einfach auf 'Werkzeuge' und dann auf 'ESP8266 Sketch Data Upload' klickst.

Nachdem nun der Sketch und das Dateisystem hochgeladen ist  solltest du im Serial Monitor (Werkzeuge --> Serieller Monitor) bei Start die IP-Addresse ausgegeben bekommen. 
Gib in deinem Browser nun 'http://IP-ADDRESSE:80' ein.

Hat alles geklappt landest du im Webinterface und kannst dort Farbe und Effekte wählen. Wenn das Webinterface funktioniert solltest du auch 'Alexa, suche neue Geräte' sagen können, um das Gerät bei Alexa hinzuzufügen.
