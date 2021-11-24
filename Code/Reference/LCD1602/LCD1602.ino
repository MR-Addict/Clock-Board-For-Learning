#include <LiquidCrystal.h>

const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte dog[] = {
  0x00, 0x0C, 0x0F, 0x0E, 0x0F, 0x1E, 0x0E, 0x0A
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, dog);

  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.setCursor(2, 0);
  lcd.print("Author: ");
  lcd.setCursor(5, 1);
  lcd.print("MR.Addict");
}

void loop() {
}
