#include <Servo.h> // include Servo library 
Servo vertical;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  vertical.attach(8);
  delay(50);
  vertical.write(10);
}

void loop() {
  // put your main code here, to run repeatedly:

}
