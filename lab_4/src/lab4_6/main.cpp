#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Adafruit_SHTC3.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

const int DISPLAY_SHTC3 = 0;
int state;
float temp;
float humid;

void setup()
{
  state = DISPLAY_SHTC3;
  lcd.init();
  lcd.backlight();
  shtc3.begin();
}

void loop()
{
  sensors_event_t h, t;

  switch (state)
  {
  case DISPLAY_SHTC3:
    shtc3.getEvent(&h, &t);
    temp = t.temperature;
    humid = h.relative_humidity;

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print("Humi: ");
    lcd.print(humid);
    lcd.print("  ");
    delay(1000);
    break;
  }
}