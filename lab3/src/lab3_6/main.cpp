#include <Arduino.h>

#define POT_PIN   A0
#define MOTOR_PIN D1

const int ADC_MAX = 1023;   // ปรับตามค่าจริงที่หมุนสุดได้

const int MOTOR_RUN = 0;
int state;
unsigned long lastPrint = 0;

void setup()
{
  state = MOTOR_RUN;
  Serial.begin(115200);
  pinMode(MOTOR_PIN, OUTPUT);
  analogWriteRange(1023);        // ← เพิ่มบรรทัดนี้
  analogWrite(MOTOR_PIN, 0);
  Serial.println("System Initialized - Motor Speed Control");
}

void loop()
{
  switch (state)
  {
    case MOTOR_RUN:
    {
      int Val = analogRead(POT_PIN);
      int Speed = map(constrain(Val, 0, ADC_MAX), 0, ADC_MAX, 0, 1023);
      int Duty = map(Speed, 0, 1023, 0, 100);

      if (Duty < 30) { Speed = 0; Duty = 0; }
      analogWrite(MOTOR_PIN, Speed);

      const char* label;
      if      (Duty == 0) label = "STOP";
      else if (Duty < 40) label = "LOW SPEED";
      else if (Duty < 80) label = "MED SPEED";
      else                label = "HIGH SPEED";

      if (millis() - lastPrint >= 300)
      { 
        lastPrint = millis();
        Serial.print("ADC: ");
        Serial.print(Val);
        Serial.print(" | PWM (0-1023): ");
        Serial.print(Speed);
        Serial.print(" | Duty: ");
        Serial.print(Duty);
        Serial.print("% | State: ");
        Serial.println(label);
      }

      state = MOTOR_RUN;
      break;
    }
  }
}