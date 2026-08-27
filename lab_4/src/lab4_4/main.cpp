#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int SCROLL_ROW1 = 0;
const int SCROLL_ROW2 = 1;
int state;
int pos;

void setup()
{
  state = SCROLL_ROW1;
  pos = 0;
  lcd.init();
  lcd.backlight();
}

void loop()
{
  switch (state)
  {
  case SCROLL_ROW1:
    lcd.clear();
    lcd.setCursor(pos, 0);       // บรรทัดที่ 1
    lcd.print("RMUTT");
    delay(300);
    pos++;
    if (pos > 11)                // 16 - 5 = 11 คือตำแหน่งสุดท้าย
    {
      pos = 0;
      state = SCROLL_ROW2;
    }
    break;

  case SCROLL_ROW2:
    lcd.clear();
    lcd.setCursor(pos, 1);       // บรรทัดที่ 2
    lcd.print("RMUTT");
    delay(300);
    pos++;
    if (pos > 11)
    {
      pos = 0;
      state = SCROLL_ROW1;
    }
    break;
  }
}