#include <Servo.h>

Servo horizontal;
int servoh = 90;
int servohLimitHigh = 170;
int servohLimitLow = 15;

Servo vertical;
int servov = 90;
int servovLimitHigh = 120;
int servovLimitLow = 20;

int ldrld = A0;
int ldrrd = A1;
int ldrlt = A2;
int ldrrt = A3;

int cyclicTime = 1; //otherwise first iteration would trigger servo move

float avt = 0;
float avd = 0;
float avl = 0;
float avr = 0;

int tol = 2;

void setup()
{
  Serial.begin(19200);

  horizontal.attach(9);
  vertical.attach(8);

  horizontal.write(90);
  vertical.write(10);

  delay(5000);
}

void loop() {

  if (cyclicTime != 0) {

    int lt = analogRead(ldrlt);
    int rt = analogRead(ldrrt);
    int ld = analogRead(ldrld);
    int rd = analogRead(ldrrd);

    avt += (lt + rt) / 2;
    avd += (ld + rd) / 2;
    avl += (lt + ld) / 2;
    avr += (rt + rd) / 2;

    //    Serial.print(avt);
    //    Serial.print(" ");
    //    Serial.print(avd);
    //    Serial.print(" ");
    //    Serial.print(avl);
    //    Serial.print(" ");
    //    Serial.print(avr);
    //    Serial.print("\n");

  } else {

    avt = avt / 100;
    avd = avd / 100;
    avl = avl / 100;
    avr = avr / 100;

    Serial.print(avt);
    Serial.print(" ");
    Serial.print(avd);
    Serial.print(" ");
    Serial.print(avl);
    Serial.print(" ");
    Serial.print(avr);
    Serial.print("\n");

    if (abs(avt - avd) > tol) {
      if (avt > avd) {
        servov = constrain(servov - 1, servovLimitLow, servovLimitHigh);
      } else {
        servov = constrain(servov + 1, servovLimitLow, servovLimitHigh);
      }
      vertical.write(servov);
    }

    if (abs(avl - avr) > tol) {
      if (avr > avl) {
        servoh = constrain(servoh + 1, servohLimitLow, servohLimitHigh);
      } else {
        servoh = constrain(servoh - 1, servohLimitLow, servohLimitHigh);
      }
      horizontal.write(servoh);
    }

    avt = 0;
    avd = 0;
    avl = 0;
    avr = 0;

    delay(50);

  }

  cyclicTime = (cyclicTime + 1) % 100;

}




