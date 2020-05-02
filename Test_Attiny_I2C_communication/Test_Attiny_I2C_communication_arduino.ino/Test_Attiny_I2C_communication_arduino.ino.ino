// ---------------------------------
// Stress test program/example for TinyWireS I2C library.
// Run this master program on the Arduino Uno R3.
// Run the other slave program on the Attiny.
// ---------------------------------
// Written by Scott Hartog, 2/6/2016
// This is the I2C master program which runs on on a regular Arduino
// (not a AtTiny). This program uses the regular Wire library from the Arduino IDE.
//
// It performs these steps in a loop:
//    1. picks a random number of bytes between 1 and 12
//    2. sends that many bytes of random data to the AtTiny slave within
//       a single Wire.beginTransmission() / Wire.write() / Wire.endTransmission() set
//    3. reads that same number of bytes back with a single Wire.requestFrom() call
//    4. compares the received data to the originally transmitted data
//    5. displays the number of requests, number of requests with mismatches,
//       and enough of the data so that the operator can tell it's working.
//
#include <Wire.h>

// BREADBOARD SETUP:
// Arduino Uno R3 (D18/SDA) = I2C SDA
//     connect to SDA on slave with external pull-up (~4.7K)
// Arduino Uno R3 (D19/SCL) = I2C SCL
//     connect to SCL on slave with external pull-up (~4.7K)
// Arduino Uno R3 (D2)
//     connect to !RST on slave
//     Can alternatively connect !RST on slave to the Ardiuno "!RESET" pin

#define I2C_SLAVE_ADDR  0x26            // i2c slave address (38, 0x26)

#define SLAVE_RESET_PIN 2

unsigned long pulse_count = 0;
byte bufferbyte[4];

void setup()
{
  // set pin modes
  pinMode(SLAVE_RESET_PIN, OUTPUT);

  // init the serial port
  Serial.begin(115200);

  // print some useful pinnout info for the Arduino
  //Serial.println(String("SCL:")+String(SCL)+String(", SDA:")+String(SDA));
  //Serial.println(String("MOSI:")+String(MOSI)+String(", SCK:")+String(SCK));

  // init the Wire object (for I2C)
  Wire.begin();

  // reset the slave
  digitalWrite(SLAVE_RESET_PIN, LOW);
  delay(10);
  digitalWrite(SLAVE_RESET_PIN, HIGH);

  // wait for slave to finish any init sequence
  delay(2000);
}

void loop()
{
  uint8_t req_rtn;       // num bytes returned by requestFrom() call

  // read N bytes from slave
  req_rtn = Wire.requestFrom(I2C_SLAVE_ADDR, 11);      // Request N bytes from slave
  for (int i = 0; i < req_rtn - 4; i++) {
    int buff = Wire.read();
    char buff1 = buff;
    Serial.print(buff1);
  }
  bufferbyte[0] = Wire.read();
  bufferbyte[1] = Wire.read();
  bufferbyte[2] = Wire.read();
  bufferbyte[3] = Wire.read();
  //  for (int j = 0; j<4;j++){
  //    Serial.print(bufferbyte[j]);
  //  }
  pulse_count = bufferbyte[0] + bufferbyte[1] * 256 + bufferbyte[2] * 256 * 256 + bufferbyte[3] * 256 * 256 * 256;
  Serial.println(pulse_count);
  // delay 1 second so user can watch results
  delay(1000);
}
