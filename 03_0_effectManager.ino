boolean effect_active = false;
boolean effect_supportcolors = false;
float effect_speed = 1;
String effect_name = "none";

void changeEffect(String effect) {
  effect_name = effect;
  effect_supportcolors = false;
  effect_active = true;
  Serial.print("[DEBUG] Effect set to: "); Serial.println(effect_name);
  saveAllData();
}

boolean colorChanged() {
  //WHENEVER A COLOR IS CHANGED
  if(!effect_supportcolors) {
    effect_active = false;
    return false;
  } else {
    return true;
  }
}
