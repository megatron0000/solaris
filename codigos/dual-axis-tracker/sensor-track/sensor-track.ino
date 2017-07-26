#include <Servo.h>
Servo horizontal;
int servoh = 90;
int servohLimitHigh = 170;
int servohLimitLow = 15;
Servo vertical;
int servov = 110;
int servovLimitHigh = 140;
int servovLimitLow = 80;

int ldrld = A0;
int ldrrd = A1;
int ldrlt = A2;
int ldrrt = A3;

int cyclicTime = 1; //otherwise first iteration would trigger servo move

float avt = 0;
float avd = 0;
float avl = 0;
float avr = 0;

float tol = 1;

void setup()
{
  Serial.begin(9600);

  horizontal.attach(8);
  vertical.attach(9);

  horizontal.write(servoh);
  vertical.write(servov);

  delay(1000);
}

void loop() {

  if (cyclicTime != 0) {

    float lt = analogRead(ldrlt);
    float rt = analogRead(ldrrt);
    float ld = analogRead(ldrld);
    float rd = analogRead(ldrrd);

    avt += (lt + rt) / 2;
    avd += (ld + rd) / 2;
    avl += (lt + ld) / 2;
    avr += (rt + rd) / 2;

  } else {

    avt = avt / 60;
    avd = avd / 60;
    avl = avl / 60;
    avr = avr / 60;

    Serial.print(avt);
    Serial.print(" ");
    Serial.print(avd);
    Serial.print(" ");
    Serial.print(avl);
    Serial.print(" ");
    Serial.print(avr);
    Serial.print(" ");
    Serial.print(servov);
    Serial.print(" ");
    Serial.print(servoh);
    Serial.print("\n");

    if (abs(avt - avd) > tol) {
      if (avt > avd) {
        servov = constrain(servov - 1, servovLimitLow, servovLimitHigh);
      } else {
        servov = constrain(servov + 1, servovLimitLow, servovLimitHigh);
      }
      vertical.write(servov);
      delay(50);
    }

    if (abs(avl - avr) > tol) {

      int reverse = +1;
      if (servov < 90) {
        reverse = -1;
      }
      
      if (avr > avl) {
        servoh = constrain(servoh + 1*reverse, servohLimitLow, servohLimitHigh);
      } else {
        servoh = constrain(servoh - 1*reverse, servohLimitLow, servohLimitHigh);
      }
      horizontal.write(servoh);
      delay(50);
    }

    avt = 0;
    avd = 0;
    avl = 0;
    avr = 0;

    delay(50);

  }

  cyclicTime = (cyclicTime + 1) % 60;

}




