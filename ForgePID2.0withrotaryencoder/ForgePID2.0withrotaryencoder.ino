/* Arduino Foundry PID Controller by minusmagis*/
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MAX31855.h"
#include <PID_v1.h>


//Define the rotary encoder pins
#define outputA A5 //Clk
#define outputB A6 //Data
#define outputC A7 //button

//Define the pins for the thermocouple MAX31855 circuit connections
#define MAXDO   8
#define MAXCS   9
#define MAXCLK  10

//Define the relay pins
#define RelayPin 11

//Define the variables for the Temperature control
float set_temperature = 0; 
float temperature_read = 0.0;
float PID_value= 0;

//Define the variables for the rotary encoder control
int counter = 0;
int aState;
int aLastState;
int bState = 0;
int state = 0;      // the current state of the output pin
int reading = 0;          // the current reading from the input pin
int previous = 0;    // the previous reading from the input pin
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

//Define Variables for the PID algorhythm
double Setpoint, Input, Output;

//Define the variables to prevent the lcd from overusing arduino computing time
unsigned long previousMillis = 0;
const long interval = 50; 

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, 30, 1, 100, DIRECT);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Define the window size at wich the relay will be activated
int WindowSize = 500;
unsigned long windowStartTime;

// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);



void setup() {
    //Define inputs for the encoder
  pinMode(outputA,INPUT);
  pinMode(outputB,INPUT);
  pinMode(outputC,INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Minusmagis Foundry");  //Display a welcome message
  // wait for MAX chip to stabilize
  delay(500);
  //Serial.println("Foundry Software ---------------------------- minusmagis");
  //Define the relay pins as outputs
  pinMode(13,OUTPUT);
  
  windowStartTime = millis();


  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  state = 0; //Write the first state of the encoder to prevent an unintended movement
  lcd.clear();

  Serial.begin (9600);
}


void loop() {
   button();
   unsigned long now = millis();
     if (now - windowStartTime > WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if (Output > now - windowStartTime) digitalWrite(13, HIGH);
  else digitalWrite(13, LOW);
     if (state == 1)
  {    
    Rotary();
  }
    if (now - previousMillis >= interval) {
          previousMillis = now;
    if (state == 0)
  {
    if (counter < 0){
    set_temperature = 0;
    counter = 0;
    lcd.clear();
    lcd.print("THIS IS NOT A");
    lcd.setCursor(0,1);
    lcd.print("FREEZER");
    delay(1000);
    }
    else{
    set_temperature = counter/2;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set T = ");
    lcd.print(set_temperature);
    lcd.setCursor(0,1);
    lcd.print("Real T = ");
    lcd.print(temperature_read);
  }
    else if (state == 1)
  {    
    printLCD(counter);
  }
  else 
  {
    lcd.print("Error");
  }
} 
}

void printLCD(int counter) { //Function that decides what to print on the lcd

    //Serial.print("Set T = ");
    //Serial.println(counter/2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set T = ");
    lcd.setCursor(0, 1);
    lcd.print(counter/2);

}

void Rotary() {
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (analogRead(outputB) > 500) {
    bState = 1;
  }
  else
  {
    bState = 0;
  }
  if (aState != aLastState) {
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (bState != aState) {
      counter++;
    } else {
      counter--;
    }
  }
  aLastState = aState; // Updates the previous state of the outputA with the current state
}

void button() {
  if (analogRead(outputC) > 500) {
    reading = 1;
  }
  else
  {
    reading = 0;
  }

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == 1 && previous == 0 && millis() - time > debounce) {
    if (state == 1)
    {
      state = 0;
    }
    else
    {
      state = 1;
    }
    time = millis();
  }
  previous = reading;

}



