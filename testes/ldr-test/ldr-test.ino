int ldrld = A0;
int ldrrd = A1;
int ldrlt = A2;
int ldrrt = A3;

void setup() {
  Serial.begin(19200);
}

void loop() {
  int ldrValues [4];

  ldrValues[0] = analogRead(ldrlt);
  ldrValues[1] = analogRead(ldrrt);
  ldrValues[2] = analogRead(ldrld);
  ldrValues[3] = analogRead(ldrrd);

  for (int i = 0; i < 4; i++) {
    Serial.print(ldrValues[i]);
    Serial.print(" ");
  }
  Serial.print("\n");
}

