#include <SD.h>
#include <SPI.h>
#include "easySD.h"

int CS_PIN = 10;

void setup() {
  Serial.begin(9600);

  initializeSD(CS_PIN);
  File file = openFileWrite("sd-test.txt");
  writeToFile(file, "This is sample text that I made to test the arduino SD card module");
  closeFile(file);

  file = openFileRead("old-file.txt");
  Serial.println(readLine(file));
  Serial.println(readLine(file));
  closeFile(file);
}

void loop() {

}







