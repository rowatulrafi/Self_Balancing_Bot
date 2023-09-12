#include <Wire.h>
#include <SoftwareSerial.h>  // Include the SoftwareSerial library for Bluetooth communication

int nunchuk_address = 0x52;           // Nunchuk I2C address (0x52)
byte received_data[6];
SoftwareSerial bluetooth(10, 11);     // RX, TX for Bluetooth module (connect RX to TX and TX to RX on HC-05)

void setup() {
  Serial.begin(9600);                 // Start the serial port at 9600 bps for debugging
  Wire.begin();                       // Start the I2C as master
  TWBR = 12;                          // Set the I2C clock speed to 400kHz
  Wire.beginTransmission(nunchuk_address);
  Wire.write(0xF0);
  Wire.write(0x55);
  Wire.endTransmission();
  delay(20);
  Wire.beginTransmission(nunchuk_address);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(20);

  bluetooth.begin(9600);              // Start Bluetooth communication at 9600 bps
}

void loop() {
  Wire.beginTransmission(nunchuk_address);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(nunchuk_address, 6);

  for (byte i = 0; i < 6; i++) {
    received_data[i] = Wire.read();
  }

  // Read the analog values from KY-023 joystick
  int joyX = analogRead(A0); // Connect X-axis of KY-023 to A0
  int joyY = analogRead(A1); // Connect Y-axis of KY-023 to A1

  // Map and send the joystick values over Bluetooth
  int mappedX = map(joyX, 0, 1023, 0, 255);  // Map analog values to 0-255 range
  int mappedY = map(joyY, 0, 1023, 0, 255);

  // Send the values as a comma-separated string
  bluetooth.print(mappedX);
  bluetooth.print(",");
  bluetooth.print(mappedY);
  bluetooth.println();

  delay(40);
}
