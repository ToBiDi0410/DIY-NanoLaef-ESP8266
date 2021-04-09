CRGB effect_star_bgcolor = strtol(String("0d0d0d").c_str(), NULL, 16);
CRGB effect_star_fgcolor = strtol(String("fbf2ff").c_str(), NULL, 16);

boolean Effect_Stars_Active() {
  return (effect_active == true && effect_name == "stars");
}

void Effect_Stars_Loop() {
  if (Effect_Stars_Active()) {
    setColorOfAllLedsStealth(effect_star_bgcolor);
    FastLED.show();
    delay(random(100, 350) * effect_speed);
    leds[random(0, NUM_LEDS)] = effect_star_fgcolor;
    FastLED.show();
    delay(random(100, 350) * effect_speed);
  }
}
