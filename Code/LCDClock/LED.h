void Mode1(uint8_t PosIndex, uint8_t ColorIndex, uint8_t ModeIndex) {
  if (ModeIndex == 0 || ModeIndex == 2)
    leds[PosIndex] = ColorFromPalette( RainbowColors_p, ColorIndex, 255, LINEARBLEND);
  else leds[7 - PosIndex] = ColorFromPalette( RainbowColors_p, ColorIndex, 255, LINEARBLEND);
  PosIndex = (PosIndex + 1) % NUM_LEDS;
  if (ModeIndex == 2 || ModeIndex == 3)fadeToBlackBy( leds, NUM_LEDS, 100);
}

void Mode2() {
  if (random8() < 180)leds[random8(NUM_LEDS)] = ColorFromPalette( RainbowColors_p, random8(255), 255, LINEARBLEND);
  fadeToBlackBy( leds, NUM_LEDS, 100);
}

void Blink() {
  static uint8_t Mode;
  static uint8_t PosIndex;
  static uint8_t ColorIndex;
  switch (Mode) {
    case 0: Mode1(PosIndex, ColorIndex, 0); break;
    case 1: Mode1(PosIndex, ColorIndex, 1); break;
    case 2: Mode1(PosIndex, ColorIndex, 2); break;
    case 3: Mode1(PosIndex, ColorIndex, 3); break;
    case 4: Mode2(); break;
    case 5: Mode2(); break;
    case 6: Mode2(); break;
  }
  ColorIndex += 16;
  PosIndex = (PosIndex + 1) % 8;
  if (PosIndex == 0) {
    Mode = (Mode + 1) % 7;
    if (Mode == 0 || Mode == 1 || Mode == 2)FastLED.clear();
  }
  FastLED.show();
}
