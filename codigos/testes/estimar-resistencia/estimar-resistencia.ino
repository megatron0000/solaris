void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(float(analogRead(A4))/1024);
  delay(50);
}
