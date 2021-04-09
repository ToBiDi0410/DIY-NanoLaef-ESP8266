#define LED_PIN     2
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[120];
CRGB curr_color = CRGB::Red;

int NUM_LEDS_PER_ELEMENT = 3;
int NUM_ELEMENTS = 1;
int NUM_LEDS = NUM_ELEMENTS * NUM_LEDS_PER_ELEMENT;

void lightSetup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  setColorOfAllLeds(curr_color);
}

void setColorOfAllLeds(CRGB value) {
  for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = value;
  }
  curr_color = value;
  FastLED.show();
}

void setColorOfAllLedsStealth(CRGB value) {
  for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = value;
  }
  //curr_color = value;
}

void setColorOfSingleLeaf(CRGB value, int index, boolean stealth) {
  leds[(index * 3)] = value;
  leds[(index * 3) + 1] = value;
  leds[(index * 3) + 2] = value;
  if(stealth == false) {
    FastLED.show();
  }
  return;
}

void espalexaColorChange(uint8_t brightness, uint32_t rgb) {
  float r = ((rgb >> 16) & 0xFF);
  float g = ((rgb >>  8) & 0xFF);
  float b = (rgb & 0xFF);
  int rd = round( r / 255 * brightness );
  int gd = round( g / 255 * brightness );
  int bd = round( b / 255 * brightness );
  setColorOfAllLeds(CRGB(rd,gd,bd));
  colorChanged();
}

//CONVERSION

String CRGBtoHex(CRGB value) {
  long HexRGB = ((long)value.r << 16) | ((long)value.g << 8 ) | (long)value.b; // get value and convert.
  String hexString = String(HexRGB, HEX);
  while(hexString.length() < 6) {
    hexString = "0" + hexString;
  }
  return hexString;
}


CRGB getCurrentColor() {
  return curr_color;
}
