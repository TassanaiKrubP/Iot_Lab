#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Address, ขนาดจอ 16x2

const int DISPLAY_VOLTAGE = 0;
int state;
int adc;
float volt;

void setup()
{
  state = DISPLAY_VOLTAGE;
  lcd.init();
  lcd.backlight();
}

void loop()
{
  switch (state)
  {
  case DISPLAY_VOLTAGE:
    adc = analogRead(A0);          // อ่านค่า 0-1023
    volt = adc * 3.3 / 1023.0;     // แปลงเป็นแรงดัน 0-3.3V
    lcd.setCursor(0, 0);
    lcd.print(volt, 2);            // ทศนิยม 2 ตำแหน่ง
    lcd.print("V ");
    delay(200);
    break;
  }
}