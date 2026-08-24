#include <Wire.h>
#include <RH_ASK.h>
#include <SPI.h>

#define MPU 0x68

// RF transmitter
// Speed = 2000
// TX data pin = 12
RH_ASK driver(2000, 12, 10, 0);

// Gesture sensitivity
float threshold = 0.35;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Wake up MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  if (!driver.init()) {
    Serial.println("RF transmitter failed!");
  } else {
    Serial.println("RF transmitter ready!");
  }
}

void loop() {

  // Read accelerometer data from MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU, 6, true);

  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();

  // Convert raw accelerometer values to g
  float X = AcX / 16384.0;
  float Y = AcY / 16384.0;
  float Z = AcZ / 16384.0;

  char command;

  // Determine gesture
  if (X > threshold) {
    command = 'F';
  }
  else if (X < -threshold) {
    command = 'B';
  }
  else if (Y > threshold) {
    command = 'L';
  }
  else if (Y < -threshold) {
    command = 'R';
  }
  else {
    command = 'S';
  }

  // Send command through RF transmitter
  driver.send((uint8_t *)&command, 1);
  driver.waitPacketSent();

  Serial.print("Sending: ");
  Serial.println(command);

  delay(100);
}
