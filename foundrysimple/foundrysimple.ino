/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MAX31855.h"
#include <LiquidCrystal.h>

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   8
#define MAXCS   9
#define MAXCLK  10

  int Tset = 0;

// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif
  
void setup() {
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  lcd.clear();
  lcd.print("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp

  Tset = analogRead(A0); 
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Ti=");
 lcd.print(int(thermocouple.readInternal()));
   lcd.print(" Tset=");
   if(Tset > 1015){
   lcd.print("T Max");
   }
   else{
   lcd.print(Tset);
   }   
   Serial.print("Int. Temp = ");
   Serial.println(thermocouple.readInternal());
     
   int c = thermocouple.readCelsius();
   lcd.setCursor(0, 1);
   if (isnan(c)) 
   {
     lcd.print("T/C Problem");
   } 
   else 
   {
     lcd.print("Tcur = "); 
     lcd.print(c);
     lcd.print("  "); 
     Serial.print("Thermocouple Temp = *");
     Serial.println(c);
   }
Tset = analogRead(A0);                                 //Read the potentiometer that sets the temperature
  if (Tset > 1015){
    digitalWrite(11,HIGH);
    digitalWrite(13,HIGH);
    Serial.println("ON"); 
  }
  else if (Tset >  (c)){
    digitalWrite(11,HIGH);
    digitalWrite(13,HIGH);
    Serial.println("ON");    
  }
  else if (Tset > (c+10)){
    digitalWrite(11,HIGH);
    digitalWrite(13,HIGH);
        Serial.println("ONOff");  
    delay(200);
    digitalWrite(11,LOW);
    digitalWrite(13,LOW);
  }
  else {
    digitalWrite(11,LOW);
    digitalWrite(13,LOW);
    Serial.println("Off");  
  }
   delay(500);
}
