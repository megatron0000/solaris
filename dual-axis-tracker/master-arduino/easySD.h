#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

void initializeSD(int CS_PIN)
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}

File openFileWrite(String filename)
{
  File file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    Serial.println("File created successfully.");
    return file;
  } else
  {
    Serial.println("Error while creating file.");
    return file;
  }
}

int writeToFile(File file, String text)
{
  if (file)
  {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile(File file)
{
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}

File openFileRead(String filename)
{
  File file = SD.open(filename);
  if (file)
  {
    Serial.println("File opened with success!");
    return file;
  } else
  {
    Serial.println("Error opening file...");
    return file;
  }
}

String readLine(File file)
{
  String received = "";
  char ch;
  while (file.available())
  {
    ch = file.read();
    if (ch == '\n')
    {
      return String(received);
    }
    else
    {
      received += ch;
    }
  }
  return String(received);
}

String readAll(File file) {
  file.seek(0);
  String received = "";
  while (file.available()) {
    received += file.read();
  }
  return String(received);
}

