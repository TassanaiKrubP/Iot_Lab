#include <Arduino.h>

const int BATT_LOW = 0;   // 0 - 25%   
const int BATT_25  = 1;   // 25 - 50%  
const int BATT_50  = 2;   // 50 - 75%  
const int BATT_75  = 3;   // 75 - 100% 

int state;
unsigned long lastBlink = 0;
unsigned long lastPrint = 0;
bool blinkOn = LOW;

void checkVal();

void setup()
{
  state = BATT_LOW;
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
}

void loop()
{
  switch (state)
  {
    case BATT_LOW:
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      if (millis() - lastBlink >= 300)
      {
        lastBlink = millis();
        blinkOn = !blinkOn;
        digitalWrite(D0, blinkOn);
      }
      checkVal();
      break;

    case BATT_25:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      checkVal();
      break;

    case BATT_50:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      checkVal();
      break;

    case BATT_75:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      checkVal();
      break;
  }
}

void checkVal()
{
  int Val = map(analogRead(A0), 0, 1023, 0, 100);

  if (millis() - lastPrint >= 300)
  {
    lastPrint = millis();
    Serial.print("Batt = ");
    Serial.print(Val);
    Serial.println(" %");
  }

  if (Val < 25)       state = BATT_LOW;
  else if (Val < 50)  state = BATT_25;
  else if (Val < 75)  state = BATT_50;
  else                state = BATT_75;
}