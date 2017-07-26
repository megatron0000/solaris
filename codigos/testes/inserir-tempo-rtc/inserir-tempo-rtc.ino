#include<Wire.h>
#include<DS3231.h>

const int DS1307 = 0x68; // Address of DS1307 see data sheets
const char* days[] =
{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* months[] =
{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// Initializes all values:
byte second = 0;
byte minute = 0;
byte currentHour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte currentYear = 0;

DS3231  rtc(SDA, SCL);

void setup() {
  Serial.begin(9600);
  rtc.begin();
  delay(2000); // This delay allows the MCU to read the current date and time.

  Serial.print("The current date and time is: ");
  printTime();
  Serial.println("Please change to newline ending the settings on the lower right of the Serial Monitor");
  Serial.println("Would you like to set the date and time now? Y/N");

  while (!Serial.available()) delay(10);
  if (Serial.read() == 'y' || Serial.read() == 'Y')

    // This set of functions allows the user to change the date and time
  {
    Serial.read();
    setTime();
    Serial.print("The current date and time is now: ");
    printTime();
  }


  Serial.println("Thank you.");
}

// Continuous function for converting bytes to decimals and vice versa
void loop() {
}
byte decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}
byte bcdToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}


// This set of codes is allows input of data
void setTime() {
  Serial.print("Please enter the current year, 00-99. - ");
  currentYear = readByte();
  Serial.println(currentYear);
  Serial.print("Please enter the current month, 1-12. - ");
  month = readByte();
  Serial.println(months[month - 1]);
  Serial.print("Please enter the current day of the month, 1-31. - ");
  monthday = readByte();
  Serial.println(monthday);
  Serial.println("Please enter the current day of the week, 1-7.");
  Serial.print("7 Sun | 1 Mon | 2 Tues | 3 Weds | 4 Thu | 5 Fri | 6 Sat - ");
  weekday = readByte();
  Serial.println(days[weekday - 1]);
  Serial.print("Please enter the current hour in 24hr format, 0-23. - ");
  currentHour = readByte();
  Serial.println(currentHour);
  Serial.print("Please enter the current minute, 0-59. - ");
  minute = readByte();
  Serial.println(minute);
  second = 0;
  Serial.println("The data has been entered.");

  rtc.setTime(currentHour, minute, second);
  rtc.setDate(monthday, month, currentYear);
  rtc.setDOW(weekday);
  
}

void printTime() {
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");

  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
}


int readByte() {
  while (!Serial.available()) delay(10);
  int reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n' && Serial.available()) {
    Serial.print(incomingByte);
    if (incomingByte >= '0' && incomingByte <= '9') {
      reading = reading * 10 + (incomingByte - '0'); 
    }
    incomingByte = Serial.read();
  }
  Serial.println(reading);
  Serial.flush();
  return reading;
}

