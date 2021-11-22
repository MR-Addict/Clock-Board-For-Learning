void BootingUP() {
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(0));
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    delay(100);
  }
  lcd.clear();
  delay(500);
  for (int i = 15; i >= 0; i--) {
    lcd.setCursor(i, 0);
    lcd.write(byte(0));
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    delay(100);
  }
  lcd.clear();
  delay(500);
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(0));
    delay(100);
  }
  for (int i = 15; i >= 0; i--) {
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    delay(100);
  }
  lcd.clear();
  delay(500);
}

void DisplayTime() {
  static unsigned long LastTime;
  if (millis() - LastTime >= 1000) {
    DateTime now = rtc.now();
    YEAR = now.year(), MONTH = now.month(), DATE = now.day(), HOUR = now.hour(), MINUTE = now.minute(), SECOND = now.second();
    String TimeFormat;
    if (HOUR < 10)TimeFormat += '0' + (String)HOUR + ':';
    else TimeFormat += (String)HOUR + ':';
    if (MINUTE < 10)TimeFormat += '0' + (String)MINUTE + ':';
    else TimeFormat += (String)MINUTE + ':';
    if (SECOND < 10)TimeFormat += '0' + (String)SECOND;
    else TimeFormat += (String)SECOND;
    lcd.setCursor(4, 0);
    lcd.print(TimeFormat);

    String DateFormat = (String)YEAR + '-';
    if (MONTH < 10)DateFormat += '0' + (String)MONTH + '-';
    else DateFormat += (String)MONTH + '-';
    if (DATE < 10)DateFormat += '0' + (String)DATE + '-';
    else DateFormat += (String)DATE;
    lcd.setCursor(3, 1);
    lcd.print(DateFormat);

    LastTime = millis();
  }
}

void DisplayMenu(uint8_t MenuIndex) {
  lcd.clear();
  if (MenuIndex == 0) {
    lcd.setCursor(0, 0);
    lcd.write(byte(1));

    for (uint8_t i = 0; i < 2; i++) {
      lcd.setCursor(1, i);
      lcd.print(Menu[MenuIndex + i]);
    }
  }
  else {
    lcd.setCursor(0, 1);
    lcd.write(byte(1));

    for (uint8_t i = 0; i < 2; i++) {
      lcd.setCursor(1, i);
      lcd.print(Menu[MenuIndex + i - 1]);
    }
  }
  String Message = (String)MenuIndex + ':' + Menu[MenuIndex];
  Serial.println(Message);
}

void SelectMenu() {
  uint8_t MenuIndex = 0;
  lcd.clear();
  DisplayMenu(MenuIndex);
  LastTime = millis();

  while (1) {
    boolean ButtonStatus = digitalRead(Button);
    if (ButtonStatus == 0 && millis() - LastTime > 300) {
      lcd.clear();
      LastTime = millis();
      break;
    }
    else {
      boolean CurrentPinA = digitalRead(PinA);
      if (CurrentPinA != LastPinA && CurrentPinA == LOW) {
        if (digitalRead(PinB) != LOW) {
          if (MenuIndex > 0) {
            MenuIndex--;
            DisplayMenu(MenuIndex);
          }
        }
        else if (MenuIndex < MenuNum - 1) {
          MenuIndex++;
          DisplayMenu(MenuIndex);
        }
      }
      LastPinA = CurrentPinA;
    }
  }
}
