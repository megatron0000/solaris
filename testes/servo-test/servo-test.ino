#include <Servo.h> // include Servo library 
Servo vertical;
Servo horizontal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  vertical.attach(9);
  horizontal.attach(8);
  delay(50);
  vertical.write(120);
  horizontal.write(130);
}

void loop() {
  // put your main code here, to run repeatedly:

}
