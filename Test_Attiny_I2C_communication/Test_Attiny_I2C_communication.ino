// ---------------------------------
// Stress test program/example for TinyWireS I2C library.
// Run this slave program on the Attiny.
// Run the other master program on the Arduino Uno R3.
// ---------------------------------
// // Written by Scott Hartog, 2/6/2016, to stress test the TinyWireS library.
// https://github.com/rambo/TinyWire
//
// This project uses the Tiny85 as an I2C slave.
//
// The slave program using TinyWireS, running on a Attiny85, receives
// N bytes of random data in a single receiveEvent() callback and
// stores that data in a global buffer. It then responds the first requestEvent()
// callback with that same data. The requestEvent() callback overwrites the data
// buffer with zeros after responding so it will only respond correctly to the
// first requestEvent() callback after each receiveEvent() callback. Subsequent
// requestEvent() will respond with 0xff for all data bytes.
//
//
// SETUP:
// AtTiny Pin 5 (PB0/SDA) = I2C SDA 
//     connect to SDA on master with external pull-up (~4.7K)
// AtTiny Pin 7 (PB0/SCL) = I2C SCL 
//     connect to SCL on master with external pull-up (~4.7K)
// AtTiny Pin 1 (PB5/!RST)
//     connect to reset on master (or just pull-up)
//
// Please see credits and usage for usiTwiSlave and TinyWireS in the .h files of 
// those libraries.

#include "TinyWireS.h"                  // wrapper class for I2C slave routines

#define I2C_SLAVE_ADDR  0x26            // i2c slave address (38, 0x26)

//const char myString[4] = "HOLI";

// Gets called when the ATtiny receives an i2c read slave request
void requestEvent()
{
 TinyWireS.beginTransmission();
 TinyWireS.send('h'); 
 TinyWireS.send('o');
 TinyWireS.send('l');
 TinyWireS.send('i');
 TinyWireS.endTransmission();
}

void setup()
{
  // initialize the TinyWireS and usiTwiSlave libraries
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
  
  // register the onRequest() callback function
  TinyWireS.onRequest(requestEvent);
}

void loop()
{
  // This needs to be here
  TinyWireS_stop_check();  
  // otherwise empty loop
}
