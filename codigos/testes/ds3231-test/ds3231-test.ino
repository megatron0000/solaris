#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");

  // Initialize the rtc object
  rtc.begin();

  Serial.println("Began");

  // The following lines can be uncommented to set the date and time
    rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
    rtc.setTime(16, 40, 0);     // Set the time to 12:00:00 (24hr format)
    rtc.setDate(27, 6, 2017);   // Set the date to January 1st, 2014

  Serial.println("Configured RTC");
}

void loop()
{
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
