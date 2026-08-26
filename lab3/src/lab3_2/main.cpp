#include <Arduino.h>

const int READ_ANALOG_INPUT = 0;
int state;

void setup()
{
  state = 0;
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  switch (state)
  {
    case READ_ANALOG_INPUT:
    {
      int Val = analogRead(A0);
      float Volt = Val * 3.3 / 1023.0;

      analogWrite(LED_BUILTIN, 1023 - Val);   // Active LOW → กลับค่า

      Serial.print("ADC = ");
      Serial.print(Val);
      Serial.print("  ->  ");
      Serial.print(Volt, 2);
      Serial.println(" V");

      delay(200);
      state = READ_ANALOG_INPUT;
      break;
    }
  }
}