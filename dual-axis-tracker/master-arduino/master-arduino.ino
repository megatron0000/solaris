#include <SD.h>
#include <SPI.h>
#include <easySD.h>
#include <dht.h>
#include <DS3231.h>
#include <Adafruit_INA219.h>
#include <Servo.h>


/**
   Temperatura e humidade
*/
#define CS_PIN 10
#define DHT11_PIN 2
dht DHT;

/**
   Cartão SD
*/
File dataFile;
#define DATA_FILE "dados.csv"
#define DATA_HEADER "dados.hea"

/**
   Relógio
*/
DS3231 rtc(SDA, SCL);

/**
   Sensor de corrente/tensão
*/
Adafruit_INA219 ina219Master = Adafruit_INA219(0x41);
Adafruit_INA219 ina219Slave = Adafruit_INA219(/** outro endereço */);

/**
   Servos
*/
Servo horizontal;
int servoh = 15;
#define SERVOH_LIMIT_HIGH 170
#define SERVOH_LIMIT_LOW 15

Servo vertical;
int servov = 20;
#define SERVOV_LIMIT_HIGH 140
#define SERVOV_LIMIT_LOW 20

/**
   LDRs
*/
#define LDRLD A0
#define LDRRD A1
#define LDRLT A2
#define LDRRT A3

float avt = 0;
float avd = 0;
float avl = 0;
float avr = 0;

#define TOL 5

/**
   Contador
*/
int cyclicTime = 1; //otherwise first iteration would trigger servo move

void setup() {
  Serial.begin(9600);
  
  initializeSD(CS_PIN);
  dataFile = openFileWrite(DATA_FILE);

  //overwriteFile(DATA_HEADER, "Data (ISO), umidade, temperatura (ºC), corrente (master) (mA), tensão (master) (V), potência (master) (mW), corrente (slave) (mA), tensão (slave) (V), potência (slave) (mW), ");
  
  rtc.begin();
  ina219Master.begin();
  ina219Slave.begin();
  horizontal.attach(8);
  vertical.attach(9);
  horizontal.write(servoh);
  vertical.write(servov);

  delay(1000);
}

void loop() {
  DHT.read11(DHT11_PIN);


  String concatString = "";
  Time now = rtc.getTime();
  
  concatString += String(now.year) + "-" + String(now.mon) + "-" + String(now.date) + "T" + rtc.getTimeStr() + ",";
  concatString += String(DHT.humidity) + "," + String(DHT.temperature) + ",";
  concatString += String(ina219Master.getCurrent_mA()) + ",";
  concatString += String(ina219Master.getBusVoltage_V() + (ina219Master.getShuntVoltage_mV() / 1000)) + ",";
  concatString += String(ina219Master.getCurrent_mA() * (ina219Master.getBusVoltage_V() + (ina219Master.getShuntVoltage_mV() / 1000))) + ",";
  concatString += String(ina219Slave.getCurrent_mA()) + ",";
  concatString += String(ina219Slave.getBusVoltage_V() + (ina219Slave.getShuntVoltage_mV() / 1000)) + ",";
  concatString += String(ina219Slave.getCurrent_mA() * (ina219Slave.getBusVoltage_V() + (ina219Slave.getShuntVoltage_mV() / 1000)));

  Serial.println(concatString);

  writeToFile(dataFile, concatString);

  if (cyclicTime % 5 == 0) {
    closeFile(dataFile);
    dataFile = openFileWrite(DATA_FILE);
    Serial.println("Data written to SD");
  }


  if (cyclicTime == 0) {

    for (int i = 1; i <= 100; i++) {
      float lt = analogRead(LDRLT);
      float rt = analogRead(LDRRT);
      float ld = analogRead(LDRLD);
      float rd = analogRead(LDRRD);

      avt += (lt + rt) / 2;
      avd += (ld + rd) / 2;
      avl += (lt + ld) / 2;
      avr += (rt + rd) / 2;
      delay(10);
    }

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
    Serial.print(" ");
    Serial.print(servov);
    Serial.print(" ");
    Serial.print(servoh);
    Serial.print("\n");

    if (abs(avt - avd) > TOL) {
      if (avt > avd) {
        servov = constrain(servov - 1, SERVOV_LIMIT_LOW, SERVOV_LIMIT_HIGH);
      } else {
        servov = constrain(servov + 1, SERVOV_LIMIT_LOW, SERVOV_LIMIT_HIGH);
      }
      vertical.write(servov);
      delay(100);
    }

    if (abs(avl - avr) > TOL) {

      int reverse = +1;
      if (servov < 35) {
        reverse = -1;
      }

      if (avr > avl) {
        servoh = constrain(servoh + floor(random(1, 4)) * reverse, SERVOH_LIMIT_LOW, SERVOH_LIMIT_HIGH);
      } else {
        servoh = constrain(servoh - floor(random(1, 4)) * reverse, SERVOH_LIMIT_LOW, SERVOH_LIMIT_HIGH);
      }
      horizontal.write(servoh);
      delay(100);
    }

    avt = 0;
    avd = 0;
    avl = 0;
    avr = 0;

  }

  cyclicTime = (cyclicTime + 1) % 100;

  delay(1000);
}
