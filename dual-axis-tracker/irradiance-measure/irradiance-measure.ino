/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int plate1 = analogRead(A0);
  int plate2 = analogRead(A1);
  // print out the value you read:
  Serial.print(plate1);
  Serial.print("  ");
  Serial.print(plate2);
  Serial.print("\n");
  delay(10);        // delay in between reads for stability
}
