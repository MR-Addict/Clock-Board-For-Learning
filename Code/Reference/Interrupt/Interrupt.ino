#include <MsTimer2.h>

#if ARDUINO >= 100
const int led_pin = LED_BUILTIN;	// 1.0 built in LED pin var
#else
const int led_pin = 13;			// default to pin 13
#endif


void flash()
{
  static boolean output = HIGH;

  digitalWrite(led_pin, output);
  output = !output;
}

void setup()
{
  pinMode(led_pin, OUTPUT);

  MsTimer2::set(500, flash); // 500ms period
  MsTimer2::start();
}

void loop()
{
}
