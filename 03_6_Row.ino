boolean Effect_Row_Active() {
  return (effect_active == true && effect_name == "row");
}

void Effect_Row_Loop() {
  static uint8_t startIndex = 0;
  if (Effect_Row_Active()) {
    effect_supportcolors = true;

    if(startIndex > NUM_LEDS) {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      startIndex = 0;
    }

    leds[startIndex] = curr_color;
    FastLED.show();
    startIndex = startIndex + 1; 
    delay(100 * effect_speed);
  } else {
    startIndex = 0;
  }
}
