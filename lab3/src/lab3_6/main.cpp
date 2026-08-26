#include <Arduino.h>

const int MOTOR_RUN = 0;
int state;
unsigned long lastPrint = 0;

void setup()
{
  state = MOTOR_RUN;
  Serial.begin(115200);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  digitalWrite(D6, HIGH);   // ตรึงทิศทาง
  digitalWrite(D7, LOW);
}

void loop()
{
  switch (state)
  {
    case MOTOR_RUN:
    {
      int Val = analogRead(A0);
      int Speed = Val;

      if (Speed < 300) Speed = 0;
      analogWrite(D5, Speed);

      if (millis() - lastPrint >= 300)
      {
        lastPrint = millis();
        Serial.print("ADC = ");
        Serial.print(Val);
        Serial.print("  Speed = ");
        Serial.print(map(Speed, 0, 1023, 0, 100));
        Serial.println(" %");
      }

      state = MOTOR_RUN;
      break;
    }
  }
}