void BuzzerRing(boolean flag) {
  for (uint8_t i = 0; i < 2; i++) {
    digitalWrite(Buzzer, HIGH);
    if (flag)delay(300);
    else delay(100);
    digitalWrite(Buzzer, LOW);
    delay(100);
  }
}

boolean BootingUP() {
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(0));
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    delay(100);
  }
  lcd.clear();
  delay(300);
  for (int i = 15; i >= 0; i--) {
    lcd.setCursor(i, 0);
    lcd.write(byte(0));
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    delay(100);
  }
  lcd.clear();
  delay(300);
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
  BuzzerRing(false);
  lcd.setCursor(2, 0);
  lcd.print("MR.Addict");
  lcd.setCursor(6, 1);
  lcd.print("Welcome!");
  delay(1000);
  lcd.clear();
}

void DisplayTime() {
  static unsigned long LASTTIME;
  if (millis() - LASTTIME >= 1000) {
    DateTime now = rtc.now();
    YEAR = now.year(), MONTH = now.month(), DATE = now.day(), HOUR = now.hour(), MINUTE = now.minute(), SECOND = now.second();
    if (HOUR == ALARMHOUR && MINUTE == ALARMMINUTE && SECOND == ALARMSECOND && SECOND == ALARMSECOND && isAlarm) {
      digitalWrite(Buzzer, HIGH);
      lcd.clear();
      lcd.setCursor(8, 0);
      lcd.write(3);
      lcd.setCursor(7, 1);
      for (uint8_t i = 0; i < 3; i++)lcd.write(3);
      while (digitalRead(Button));
      digitalWrite(Buzzer, LOW);
      LastTime = millis();
      return 0;
    }
    if (isAlarm) {
      lcd.setCursor(15, 1);
      lcd.write(3);
    }
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
    if (DATE < 10)DateFormat += '0' + (String)DATE;
    else DateFormat += (String)DATE;
    lcd.setCursor(3, 1);
    lcd.print(DateFormat);

    LASTTIME = millis();
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
}

void UpdateTime(uint8_t TimeArrey[], uint8_t Position) {
  lcd.clear();
  String TimeFormat;
  for (uint8_t i = 0; i < 6; i++) {
    TimeFormat += (String)TimeArrey[i];
    if (i == 1 || i == 3)TimeFormat += ':';
  }
  lcd.setCursor(4, 0);
  lcd.print(TimeFormat);
  lcd.setCursor(4 + Position, 1);
  lcd.write(byte(2));
}

void UpdateDate(uint8_t DateArrey[], uint8_t Position) {
  lcd.clear();
  String DateFormat;
  for (uint8_t i = 0; i < 8; i++) {
    DateFormat += (String)DateArrey[i];
    if (i == 3 || i == 5)DateFormat += '-';
  }
  lcd.setCursor(3, 0);
  lcd.print(DateFormat);
  lcd.setCursor(3 + Position, 1);
  lcd.write(byte(2));
}

boolean TimeConsole() {
  uint8_t Position = 0, Position2 = 0;
  uint8_t hour1 = HOUR / 10, hour2 = HOUR % 10, minute1 = (MINUTE + 1) / 10, minute2 = (MINUTE + 1) % 10, second1 = 0, second2 = 0;
  uint8_t TimeArrey[6] = {hour1, hour2, minute1, minute2, second1, second2};
  UpdateTime(TimeArrey, Position);
  LastTime = millis();
  while (1) {
    boolean ButtonStatus = digitalRead(Button);
    if (ButtonStatus == 0 && millis() - LastTime > 300) {
      if (Position == 1 || Position == 4)Position += 2;
      else Position++;
      Position2++;
      if (Position2 == 6)break;
      UpdateTime(TimeArrey, Position);
      LastTime = millis();
    }
    else {
      boolean CurrentPinA = digitalRead(PinA);
      if (CurrentPinA != LastPinA && CurrentPinA == LOW) {
        if (digitalRead(PinB) != LOW) {
          if (TimeArrey[Position2] > 0) {
            TimeArrey[Position2]--;
            UpdateTime(TimeArrey, Position);
          }
        }
        else if (TimeArrey[Position2] < 9) {
          TimeArrey[Position2]++;
          UpdateTime(TimeArrey, Position);
        }
      }
      LastPinA = CurrentPinA;
    }
  }
  lcd.clear();
  if (TimeArrey[0] * 10 + TimeArrey[1] < 24 &&
      TimeArrey[2] * 10 + TimeArrey[3] < 61 &&
      TimeArrey[4] * 10 + TimeArrey[5] < 61) {
    HOUR = TimeArrey[0] * 10 + TimeArrey[1];
    MINUTE = TimeArrey[2] * 10 + TimeArrey[3];
    SECOND = TimeArrey[4] * 10 + TimeArrey[5];
    return true;
  }
  else return false;
}

boolean AlarmConsole() {
  uint8_t Position = 0, Position2 = 0;
  uint8_t hour1 = ALARMHOUR / 10, hour2 = ALARMHOUR % 10, minute1 = ALARMMINUTE / 10, minute2 = ALARMMINUTE % 10, second1 = ALARMSECOND, second2 = ALARMSECOND;
  uint8_t TimeArrey[6] = {hour1, hour2, minute1, minute2, second1, second2};
  UpdateTime(TimeArrey, Position);
  LastTime = millis();
  while (1) {
    boolean ButtonStatus = digitalRead(Button);
    if (ButtonStatus == 0 && millis() - LastTime > 300) {
      if (Position == 1 || Position == 4)Position += 2;
      else Position++;
      Position2++;
      if (Position2 == 6)break;
      UpdateTime(TimeArrey, Position);
      LastTime = millis();
    }
    else {
      boolean CurrentPinA = digitalRead(PinA);
      if (CurrentPinA != LastPinA && CurrentPinA == LOW) {
        if (digitalRead(PinB) != LOW) {
          if (TimeArrey[Position2] > 0) {
            TimeArrey[Position2]--;
            UpdateTime(TimeArrey, Position);
          }
        }
        else if (TimeArrey[Position2] < 9) {
          TimeArrey[Position2]++;
          UpdateTime(TimeArrey, Position);
        }
      }
      LastPinA = CurrentPinA;
    }
  }
  lcd.clear();
  if (TimeArrey[0] * 10 + TimeArrey[1] < 24 &&
      TimeArrey[2] * 10 + TimeArrey[3] < 60 &&
      TimeArrey[4] * 10 + TimeArrey[5] < 60) {
    ALARMHOUR = TimeArrey[0] * 10 + TimeArrey[1];
    ALARMMINUTE = TimeArrey[2] * 10 + TimeArrey[3];
    ALARMSECOND = TimeArrey[4] * 10 + TimeArrey[5];
    return true;
  }
  else return false;
}

boolean DateConsole() {
  uint8_t Position = 0, Position2 = 0;
  uint8_t year1 = YEAR / 1000, year2 = (YEAR % 1000) / 100, year3 = (YEAR % 100) / 10, year4 = YEAR % 10, month1 = MONTH / 10, month2 = MONTH % 10, date1 = DATE / 10, date2 = DATE % 10;
  uint8_t DateArrey[8] = {year1, year2, year3, year4, month1, month2, date1, date2};
  UpdateDate(DateArrey, Position);
  LastTime = millis();
  while (1) {
    boolean ButtonStatus = digitalRead(Button);
    if (ButtonStatus == 0 && millis() - LastTime > 300) {
      if (Position == 3 || Position == 6)Position += 2;
      else Position++;
      Position2++;
      if (Position2 == 8)break;
      UpdateDate(DateArrey, Position);
      LastTime = millis();
    }
    else {
      boolean CurrentPinA = digitalRead(PinA);
      if (CurrentPinA != LastPinA && CurrentPinA == LOW) {
        if (digitalRead(PinB) != LOW) {
          if (DateArrey[Position2] > 0) {
            DateArrey[Position2]--;
            UpdateDate(DateArrey, Position);
          }
        }
        else if (DateArrey[Position2] < 9) {
          DateArrey[Position2]++;
          UpdateDate(DateArrey, Position);
        }
      }
      LastPinA = CurrentPinA;
    }
  }
  lcd.clear();
  if (DateArrey[0] * 1000 + DateArrey[1] * 100 + DateArrey[2] * 10 + DateArrey[3] < 2050 &&
      DateArrey[4] * 10 + DateArrey[5] < 13 &&
      DateArrey[6] * 10 + DateArrey[7] < 32) {
    HOUR = DateArrey[0] * 1000 + DateArrey[1] * 100 + DateArrey[2] * 10 + DateArrey[3];
    MINUTE = DateArrey[4] * 10 + DateArrey[5];
    SECOND = DateArrey[6] * 10 + DateArrey[7];
    return true;
  }
  else return false;
}

void SetTime() {
  if (TimeConsole()) {
    lcd.setCursor(7, 0);
    lcd.print(":)");
    lcd.setCursor(4, 1);
    lcd.print("Success!");
    rtc.adjust(DateTime(YEAR, MONTH, DATE, HOUR, MINUTE, SECOND));
    BuzzerRing(false);
  }
  else {
    lcd.setCursor(7, 0);
    lcd.print(":(");
    lcd.setCursor(5, 1);
    lcd.print("Error!");
    BuzzerRing(true);
  }
  delay(1000);
}

void SetDate() {
  if (DateConsole()) {
    lcd.setCursor(7, 0);
    lcd.print(":)");
    lcd.setCursor(4, 1);
    lcd.print("Success!");
    rtc.adjust(DateTime(YEAR, MONTH, DATE, HOUR, MINUTE, SECOND));
    BuzzerRing(false);
  }
  else {
    lcd.setCursor(7, 0);
    lcd.print(":(");
    lcd.setCursor(5, 1);
    lcd.print("Error!");
    BuzzerRing(true);
  }
  delay(1000);
}

void SetAlarm() {
  if (AlarmConsole()) {
    lcd.setCursor(7, 0);
    lcd.print(":)");
    lcd.setCursor(4, 1);
    lcd.print("Success!");
    isAlarm = true;
    EEPROM.write(0, isAlarm);
    EEPROM.write(1, ALARMHOUR);
    EEPROM.write(2, ALARMMINUTE);
    EEPROM.write(3, ALARMSECOND);
    BuzzerRing(false);
  }
  else {
    lcd.setCursor(7, 0);
    lcd.print(":(");
    lcd.setCursor(5, 1);
    lcd.print("Error!");
    BuzzerRing(true);
  }
  delay(1000);
}

void AlarmONOFF() {
  isAlarm = !isAlarm;
  EEPROM.write(0, isAlarm);
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print(":)");
  if (isAlarm) {
    lcd.setCursor(4, 1);
    lcd.print("Alarm ON!");
  }
  else {
    lcd.setCursor(3, 1);
    lcd.print("Alarm OFF!");
  }
  BuzzerRing(false);
  delay(1000);
}

void LightONOFF() {
  isLight = !isLight;
  EEPROM.write(4, isLight);
  if (isLight)MsTimer2::start();
  else {
    FastLED.clear();
    FastLED.show();
    MsTimer2::stop();
  }
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print(":)");
  if (isLight) {
    lcd.setCursor(4, 1);
    lcd.print("Light ON!");
  }
  else {
    lcd.setCursor(3, 1);
    lcd.print("Light OFF!");
  }
  BuzzerRing(false);
  delay(1000);
}

void DisplayTemp() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Temperature:");
  lcd.setCursor(5, 1);
  lcd.print((String)rtc.getTemperature());
  lcd.print("\337C");
  LastTime = millis();
  while (digitalRead(Button) || millis() - LastTime < 300);
}

void SelectMenu() {
  uint8_t MenuIndex = 0;
  lcd.clear();
  DisplayMenu(MenuIndex);
  LastTime = millis();

  while (1) {
    boolean ButtonStatus = digitalRead(Button);
    if (ButtonStatus == 0 && millis() - LastTime > 300) {
      switch (MenuIndex) {
        case 0: break;
        case 1: SetTime(); break;
        case 2: SetDate(); break;
        case 3: SetAlarm(); break;
        case 4: AlarmONOFF(); break;
        case 5: LightONOFF(); break;
        case 6: DisplayTemp(); break;
      }
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
