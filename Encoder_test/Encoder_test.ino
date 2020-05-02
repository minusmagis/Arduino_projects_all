/*     Arduino Rotary Encoder Tutorial

    by Dejan Nedelkovski, www.HowToMechatronics.com

*/
#include <LiquidCrystal.h>

#define outputA A5 //Clk
#define outputB A6 //Data
#define outputC A7 //button

int counter = 0;
int aState;
int aLastState;
int bState = 0;
int previousMenu = 0;
int SetT = 0;
int RealT = 0;

int state = 0;      // the current state of the output pin
int reading = 0;          // the current reading from the input pin
int previous = 0;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.

long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);



void setup() {
  pinMode (outputA, INPUT);
  pinMode (outputB, INPUT);
  pinMode(A7, INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}


void loop() {
  button();
  if (state == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("Set T = ");
    lcd.print(SetT);
    lcd.setCursor(0,1);
    lcd.print("Real T = ");
    lcd.print(RealT);
  }
  else if (state == 1)
  {
    Rotary();
  }
  else if (state == 2)
  {
    lcd.print("State 2");
  }
  else 
  {
    lcd.print("Error");
  }
}

String MenuName(int x) { //Function that gives each menu name
  String Menu;
  if (x == 0) {
    Menu = "Real Temperature";
  }
  else if (x == 1) {
    Menu = "Set Temperature";
  }
  else if (x == 2) {
    Menu = "Test2";
  }
  else if (x == 3) {
    Menu = "Test3";
  }
  else {
    Menu = "ERROR";
  }
  return Menu;
}

int counterReset(int x) { //Function that transforms any number to 0-n
  int result = 0;
  const int n = 4;     //Number of menus
  result = abs(x % n);
  return result;
}

void printLCD(int counter) { //Function that decides what to print on the lcd

  if (state == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(MenuName(counterReset(counter / 2)));
    lcd.setCursor(0, 1);
    lcd.print("current value");
    previousMenu = counterReset(counter / 2);
    Serial.print("Position: ");
    Serial.print(MenuName(previousMenu));
    Serial.println(MenuName(counterReset(counter / 2)));
  }

  else if (state == 0) {
    Serial.print("value = ");
    Serial.println(MenuName(previousMenu));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(MenuName(previousMenu));
    lcd.setCursor(0, 1);
    lcd.print(counter / 2);
  }
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
    printLCD(counter);
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
      state = 2;
    }
    else if (state == 2)
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

