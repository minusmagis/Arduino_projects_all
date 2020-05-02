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
int i = 0;
int diffT = 50;
int Tcurrent = 0;
float Tread1 = 0;
float Tread = 0;
// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
/*
#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif
*/  
void setup() {
  /*
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif */
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  pinMode(11,OUTPUT);
  
  lcd.clear();
  lcd.print("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop(){
 Tread1 = thermocouple.readCelsius();
  if(isnan(Tread1)){
    lcd.setCursor(15,1);
    lcd.print("St");
    delay(100);
    Tread = 0;
  }
  else{
  Tread = (0.01*thermocouple.readCelsius() + 0.99*Tread);            //Read the temperature from the thermocouple and smooth it
  delay(10);
   Serial.print("Tcurrent= ");
   Serial.print(Tcurrent);
   Serial.print(" Tread= ");
   Serial.println(Tread);
  Tcurrent = Tread;
  }
  i++;
  readTemp(Tcurrent);
  PIDcontrol(i,Tcurrent);
  if (i > diffT){
    i = 0;
  }
 }

void readTemp(int Tcurrent) {

   int Tset = analogRead(A0);                                 //Read the potentiometer that sets the temperature
   int Tref = thermocouple.readInternal();                    //Read the reference temperature of the internal junction
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Ti=");                                          //Print on the LCD the internal junction's temperature
   lcd.print(Tref);
   lcd.print(" Tset=");                                       //Print on the LCD the set temperature
   lcd.print(Tset);
   lcd.setCursor(0, 1);
   lcd.print("Tcurrent = ");                                  //Print on the LCD the current temperature
   lcd.print(Tcurrent);  

}

void PIDcontrol(int iteration,int Tcurrent)
{
   int Tset = analogRead(A0);                                 //Read the potentiometer that sets the temperature
   int Tref = thermocouple.readInternal();                    //Read the reference temperature of the internal junction

   float timeOn = Tset-Tcurrent;
   if (Tcurrent == 0 )
   {
    digitalWrite(11,LOW); 
   }
   else if (timeOn >= iteration)
   {
    //Serial.println("ON");
    digitalWrite(11,HIGH);
   }
   else 
   {
    //Serial.println("OFF");
    digitalWrite(11,LOW);
   }
}


