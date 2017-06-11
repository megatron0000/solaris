#include <SD.h>
#include <SPI.h>
#include "easySD.h"
#include <dht.h>
#include <DS3231.h>
#include <Adafruit_INA219.h>

#define CS_PIN 10
#define DHT11_PIN 2

dht DHT;
File temperatureFile;
File humidityFile;
DS3231 rtc(SDA, SCL);
Adafruit_INA219 ina219Master = Adafruit_INA219();
Adafruit_INA219 ina219Slave = Adafruit_INA219(/** outro endereço */);

void setup() {
  Serial.begin(9600);
  initializeSD(CS_PIN);
  rtc.begin();
  ina219Master.begin();
  ina219Slave.begin();
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
