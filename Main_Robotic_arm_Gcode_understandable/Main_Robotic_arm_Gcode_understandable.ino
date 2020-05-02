#include<Servo.h>
Servo ro;
Servo revro;
Servo phy;
Servo theta;

extern int SetPin;                // Define the pins connected to the power supply in order to manipulate it
extern int OnOffPin;
extern int PlusPin;
extern int MinusPin;

void setup() {
  ro.attach(5);    //Violet cable
  revro.attach(11);  //White cable
  phy.attach(6);    //Blue
  theta.attach(3);   //Whitecable from 3 group

  pinMode(SetPin,OUTPUT);
  pinMode(OnOffPin,OUTPUT);
  pinMode(PlusPin,OUTPUT);
  pinMode(MinusPin,OUTPUT);

  pinMode(SetPin,HIGH);
  pinMode(OnOffPin,HIGH);
  pinMode(PlusPin,HIGH);
  pinMode(MinusPin,HIGH);
  
  Serial.begin(250000);                                    // Begin Serial communication 
  StartCode();                                             // Send the startcode
}

void loop() {
GcodeCommandReceive();
GcodeToInstructions();
}
