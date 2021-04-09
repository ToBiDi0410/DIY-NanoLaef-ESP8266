int effect_breath_currentindex = 0;
int effect_breath_currentbrightness = 0;
boolean effect_breath_reverse = false;


boolean Effect_Breath_Active() {
  return (effect_active == true && effect_name == "breath");
}

void Effect_Breath_Loop() {  
  if (Effect_Breath_Active()) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    effect_supportcolors = true;
    if(effect_breath_currentindex > NUM_ELEMENTS) {
      effect_breath_currentindex = 0;
    }
    if(effect_breath_reverse == false) {
      effect_breath_currentbrightness += 5;
      if(effect_breath_currentbrightness > 254) {
        effect_breath_reverse = true;
      }
    } else {
      effect_breath_currentbrightness -= 5;
      if(effect_breath_currentbrightness < 1) {
        setColorOfSingleLeaf(CRGB::Black, effect_breath_currentindex, false);
        effect_breath_currentindex++;
        effect_breath_reverse = false;
      }
    }
    CHSV newhsv = rgb2hsv_approximate(curr_color);
    newhsv.v = effect_breath_currentbrightness;
    //CHSV newhsv = CHSV(curr_color, 255, effect_breath_currentbrightness);
    setColorOfSingleLeaf(newhsv, effect_breath_currentindex, false);
    delay(15 * effect_speed);
  } else {
    effect_breath_currentindex = 0;
    effect_breath_currentbrightness = 0;
    effect_breath_reverse = false;
  }
}
