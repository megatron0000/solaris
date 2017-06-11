#include <SD.h>
#include <SPI.h>
#include "easySD.h"
#include <dht.h>

#define CS_PIN 10
#define DHT11_PIN 2

dht DHT;
File temperatureFile;
File humidityFile;

void setup() {
  Serial.begin(9600);
  initializeSD(CS_PIN);

  
}

void loop() {
  DHT.read11(DHT11_PIN);
  /**
   * Existe restrição de tamanho para nome de arquivo (por isso "temperat.csv")
   */
  temperatureFile = openFileWrite("temperat.csv");
  humidityFile = openFileWrite("humidity.csv");
  writeToFile(temperatureFile, String(DHT.temperature));
  writeToFile(humidityFile, String(DHT.humidity));
  closeFile(temperatureFile);
  closeFile(humidityFile);
  delay(1000);
}
