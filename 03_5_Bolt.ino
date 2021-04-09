CRGB effect_bolt_fgcolor = strtol(String("fbf2ff").c_str(), NULL, 16);

boolean Effect_Bolt_Active() {
  return (effect_active == true && effect_name == "bolt");
}

void Effect_Bolt_Loop() {
  if (Effect_Bolt_Active()) {
    effect_supportcolors = true;
    setColorOfAllLedsStealth(curr_color);
    FastLED.show();
    delay(random(100, 350) * effect_speed);
    leds[random(0, NUM_LEDS)] = effect_bolt_fgcolor;
    FastLED.show();
    delay(random(100, 350) * effect_speed);
  }
}
