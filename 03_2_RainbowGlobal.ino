CRGBPalette16 effect_rainbowglobal_currentPalette = RainbowColors_p;;
TBlendType    effect_rainbowglobal_currentBlending = LINEARBLEND;

boolean Effect_RainbowGlobal_Active() {
  return (effect_active == true && effect_name == "rainbow_global");
}

void Effect_RainbowGlobal_Loop() {
  if(Effect_RainbowGlobal_Active()) {
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    effect_rainbowglobal_FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    delay(15 * effect_speed);
  }
}

void effect_rainbowglobal_FillLEDsFromPaletteColors( uint8_t colorIndex) {
    fill_solid( leds, NUM_LEDS, ColorFromPalette( effect_rainbowglobal_currentPalette, colorIndex, 255, effect_rainbowglobal_currentBlending));
}
