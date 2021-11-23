#include <LiquidCrystal.h>
#include <FastLED.h>
#include <RTClib.h>
#include <MsTimer2.h>
#include <EEPROM.h>

#include "Header.h"
#include "LED.h"
#include "LCD.h"

void setup() {
  Serial.begin(115200);
  MsTimer2::set(150, Blink);

  pinMode(Button, INPUT_PULLUP);
  pinMode(PinA, INPUT_PULLUP);
  pinMode(PinB, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.createChar(0, duck);
  lcd.createChar(1, arrow);
  lcd.createChar(2, arrowUp);
  lcd.createChar(3, bell);
  rtc.begin();

  if (rtc.lostPower()) rtc.adjust(DateTime(2021, 10, 20, 12, 30, 0));
  DateTime now = rtc.now();
  YEAR = now.year(), MONTH = now.month(), DATE = now.day(), HOUR = now.hour(), MINUTE = now.minute(), SECOND = now.second();

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);

  isAlarm = EEPROM.read(0);
  ALARMHOUR = EEPROM.read(1);
  ALARMMINUTE = EEPROM.read(2);
  ALARMSECOND = EEPROM.read(3);
  isLight = EEPROM.read(4);
  if (isLight)MsTimer2::start();
  else {
    FastLED.clear();
    FastLED.show();
    MsTimer2::stop();
  }
  BootingUP();
}

void loop() {
  boolean ButtonStatus = digitalRead(Button);
  if (ButtonStatus == 0 && millis() - LastTime > 300)SelectMenu();
  else DisplayTime();
}
