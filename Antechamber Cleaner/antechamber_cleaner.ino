/* This Software has been writen to track the cleanliness of the air in a glovebox antechamber. It has several features:
    -It detects if the dor is open or not, and tracks the state of the door over time.
    -It detects the level of vacuum
    -It cann actuate a servo to make vacuum or to refil the antechamber
*/

/*
   Things to implement:
   -A calibration function that stores the values on memory and when reset reapplies the memory held values
   -double tab on buttons as a norm to be able to do anything (check)
   -a mechanism for half cycles (check)
   -timeout function (check)
   -a mechanism that tells you if the state has been reached or not (Move and wait) (check, but needs further checking with the actual glovebox))

   SWITCH BACK ALL THE CHANGES LIKE COLOR READOUT CYCLES OR MOVE AND WAIT RETURNING TRUE FOR NORMAL OPERATION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11

*/

#include "Pin_Setup.h"
#include "Header_file.h"
#include<Servo.h>
Servo handle;

extern int air_state;
boolean air_dirty = true;
boolean door_open = false;
boolean door_has_open = false;
extern int current_valve_pos;
int count = 0;

extern int clean_button_state;
extern int refill_button_state;

extern int clean_button_counter;
extern int refill_button_counter;

extern int clean_button_last_state;
extern int refill_button_last_state;

extern int Current_Command;
int Latest_Command = 0;


boolean Time_out(boolean reset = false);
int photoRead(boolean fast = false, int calibration = 0 );

//void setupPins();
//void EEPROMRead();

void setup() {

  cli();//stop interrupts
  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // Set CS21 bit for 1024 prescaler
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
  // enable timer overflow interrupt
  TIMSK2 |= (1 << TOIE2);


  sei();//allow interrupts

  //end setup

  handle.attach(servoPin);    //Violet cable
  setupPins();
#if defined debug
  Serial.begin(250000);
  Serial.println("Antechamber Arduino");
#endif
  //EEPROMWrite();
  //EEPROMRead();
}

void loop() {
  air_process();
  Command_Update();
//   Serial.println(air_state);
}

ISR(TIMER2_OVF_vect)
{
  count++;
  if (count >= 10) {
    count = 0;
    
    //    Serial.print("  Button clean: " );
    //    Serial.print(digitalRead(clean_button));
    //        Serial.print("  Button refill: " );
    //    Serial.println(digitalRead(refill_button));
    //    Serial.print("  CB state: " );
    //    Serial.print(clean_button_state);
    //    Serial.print("  CB counter: " );
    //    Serial.print(clean_button_counter);
    //    Serial.print("  RB state: " );
    //    Serial.print(refill_button_state);
    //    Serial.print("  RB counter: " );
    //    Serial.print(refill_button_counter);
    //    Serial.print("     ");
    //    Serial.print(Button_Read());
    //    Serial.print("   Current_Command   = ");
    //    Serial.println(Current_Command);
    if (magRead()) {
      air_dirty = true;
      door_open = true;
      door_has_open = true;
    }
    else {
      door_open = false;
    }
  }
}

void Command_Update() {
  Latest_Command = Button_Read();
  if (Latest_Command != Unknown_Command) {
    Current_Command = Latest_Command;
  }
}
