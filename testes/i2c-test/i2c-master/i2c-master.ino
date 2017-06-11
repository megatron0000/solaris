#include <DS3231.h>
#include <Wire.h>


// Init the DS3231 using the hardware interface
DS3231  rtc(4, 5);

void setup()
{
  // Setup Serial connection
  Serial.begin(9600);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  Wire.begin(); // join i2c bus (address optional for master)

  // Initialize the rtc object
  rtc.begin();

  // The following lines can be uncommented to set the date and time
  rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(15, 18, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(10, 6, 2017);   // Set the date to January 1st, 2014
}

byte x = 0;

void loop()
{

  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  x++;
  delay(500);
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");

  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());

  // Wait one second before repeating :)
  delay (1000);
}
