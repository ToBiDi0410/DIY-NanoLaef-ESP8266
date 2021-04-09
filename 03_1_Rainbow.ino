CRGBPalette16 effect_rainbow_currentPalette = RainbowColors_p;;
TBlendType    effect_rainbow_currentBlending = LINEARBLEND;

boolean Effect_Rainbow_Active() {
  return (effect_active == true && effect_name == "rainbow");
}

void Effect_Rainbow_Loop() {
  if(Effect_Rainbow_Active()) {
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    effect_rainbow_FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    delay(15 * effect_speed);
  }
}

void effect_rainbow_FillLEDsFromPaletteColors( uint8_t colorIndex) {
    uint8_t brightness = 255;
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( effect_rainbow_currentPalette, colorIndex, 255, effect_rainbow_currentBlending);
        colorIndex += 3;
    }
}
