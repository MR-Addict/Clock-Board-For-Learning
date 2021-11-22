#include <LiquidCrystal.h>
#include <FastLED.h>
#include <RTClib.h>
#include <MsTimer2.h>
#include <RotaryEncoder.h>
#include "Header.h"
#include "LED.h"
#include "LCD.h"

void setup() {
  Serial.begin(115200);

  MsTimer2::set(300, Blink);
  MsTimer2::start();

  pinMode(Button, INPUT_PULLUP);
  pinMode(PinA, INPUT_PULLUP);
  pinMode(PinB, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.createChar(0, duck);
  lcd.createChar(1, arrow);
  rtc.begin();

  if (rtc.lostPower())rtc.adjust(DateTime(2021, 10, 20, 12, 30, 0));
  DateTime now = rtc.now();
  YEAR = now.year(), MONTH = now.month(), DATE = now.day(), HOUR = now.hour(), MINUTE = now.minute(), SECOND = now.second();

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );

  //BootingUP();
}

void loop() {
  boolean ButtonStatus = digitalRead(Button);
  if (ButtonStatus == 0 && millis() - LastTime > 300)SelectMenu();
  else DisplayTime();
}
