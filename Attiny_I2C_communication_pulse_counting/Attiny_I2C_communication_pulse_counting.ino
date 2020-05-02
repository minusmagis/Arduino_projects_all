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


// Requires headers for AVR defines and ISR function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TinyWireS.h"                  // wrapper class for I2C slave routines

#define INTERRUPT_PIN PCINT1  // This is PB1 per the schematic
#define INT_PIN PB1           // Interrupt pin of choice: PB1 (same as PCINT1) - Pin 6
#define LED_PIN PB4           // PB4 - Pin 3
#define PCINT_VECTOR PCINT0_vect      // This step is not necessary - it's a naming thing for clarit

#define I2C_SLAVE_ADDR  0x26            // i2c slave address (38, 0x26)

//const char myString[4] = "HOLI";

unsigned long pulse_count = 0;
//byte pulse_count = 0;

// Gets called when the ATtiny receives an i2c read slave request
void requestEvent()
{
  TinyWireS.send('P');
  TinyWireS.send('o');
  TinyWireS.send('s');
  TinyWireS.send('E');
  TinyWireS.send('1');
  TinyWireS.send(':');
  TinyWireS.send(' ');
  TinyWireS.send(pulse_count);
  TinyWireS.send(pulse_count >> 8);
  TinyWireS.send(pulse_count >> 16);
  TinyWireS.send(pulse_count >> 24);

}

void setup() {
  pinMode(LED_PIN, INPUT_PULLUP);
  cli();                            // Disable interrupts during setup
  PCMSK |= (1 << INTERRUPT_PIN);    // Enable interrupt handler (ISR) for our chosen interrupt pin (PCINT1/PB1/pin 6)
  GIMSK |= (1 << PCIE);             // Enable PCINT interrupt in the general interrupt mask
  pinMode(INT_PIN, INPUT_PULLUP);   // Set our interrupt pin as input with a pullup to keep it stable
  sei();                            //last line of setup - enable interrupts after setup

  // initialize the TinyWireS and usiTwiSlave libraries
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode

  // register the onRequest() callback function
  TinyWireS.onRequest(requestEvent);
}
// This is the interrupt handler called when there is any change on the INT_PIN
// ISR is defined in the headers - the ATtiny85 only has one handler

ISR(PCINT_VECTOR)
{
  if ( digitalRead(LED_PIN) == HIGH ) {
    pulse_count += 1;
  }
  else {
    pulse_count -= 1;
  }
}

void loop()
{
  // This needs to be here
  TinyWireS_stop_check();
  // otherwise empty loop
}
