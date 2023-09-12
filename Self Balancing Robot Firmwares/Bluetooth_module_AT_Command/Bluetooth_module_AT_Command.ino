#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup()
{
  Serial.begin(38400);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);       
}

void loop()
{
  if (BTSerial.available())    // read from HC-05 and send to Arduino Serial Monitor
  Serial.write(BTSerial.read());

  if (Serial.available())     // Keep reading from Arduino Serial Monitor and send to HC-05
  BTSerial.write(Serial.read());
}
