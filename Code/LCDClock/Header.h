uint8_t MONTH, DATE, HOUR, MINUTE, SECOND;
uint16_t YEAR;
uint8_t PaletteMode;

const uint8_t LED_PIN = 12;
const uint8_t NUM_LEDS = 8;
const uint8_t BRIGHTNESS = 10;

uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t arrow[8] = {0x00, 0x04, 0x06, 0x1F, 0x1F, 0x06, 0x04, 0x00};

const uint8_t MenuNum = 7;
String Menu[MenuNum] = {"Back", "Set Time", "Set Date", "Set Alarm", "Alarm ON/OFF", "Buzzer ON/OFF", "Light ON/OFF"};

const uint8_t Button = 3;
const uint8_t PinA = 2;
const uint8_t PinB = 10;
boolean LastPinA;

unsigned long LastTime;

RTC_DS3231 rtc;
CRGB leds[NUM_LEDS];
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
RotaryEncoder encoder(PinA, PinB, RotaryEncoder::LatchMode::TWO03);
