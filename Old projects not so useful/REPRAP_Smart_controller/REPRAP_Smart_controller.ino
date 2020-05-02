
#include <U8x8lib.h>

#include "U8glib.h"

#define encoderPin1 2
#define encoderPin2 4
#define pinEncButt 3

const int encoderDivider = 4;
boolean buttonFlag = false;
int currentScreen = 0;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;
int coordinates[] = {0, 0};

int lastMSB = 0;
int lastLSB = 0;

U8GLIB_ST7920_128X64_1X u8g(17, 15, 16);

void cleardisplay() {
  u8g.firstPage();
  do {
  } while ( u8g.nextPage() );
}

void drawMain(void) {
  u8g.setFont(u8g_font_fur11);
  u8g.drawStr( 0, 20, "Move");
  u8g.drawStr( 73, 20, "Home");
  u8g.drawStr( 0, 50, "Approach");
  u8g.drawStr( 73, 50, "Retract");

  u8g.drawLine(coordinates[0], coordinates[1], coordinates[0] - 5, coordinates[1]);
  u8g.drawLine(coordinates[0], coordinates[1], coordinates[0], coordinates[1] - 5);

  //  char buf[8];
  //  sprintf(buf, "%d %d", digitalRead(pinEncButt), encoderValue);
  //  u8g.drawStr( 10, 50, buf);

}

void drawMove(void) {
  u8g.setFont(u8g_font_fur11);

  u8g.drawStr( 0, 40, "Z position");

  char buf[8];
  sprintf(buf, "%d", encoderValue);
  u8g.drawStr( 73, 35, buf);

}

void updateEncoder() {
  int MSB = digitalRead(encoderPin1);
  int LSB = digitalRead(encoderPin2);

  int encoded = (MSB << 1) | LSB;
  int sum  = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue--;

  lastEncoded = encoded; //store this value for next time
}

void buttonChange () {
  buttonFlag = ! buttonFlag;

}

void setup(void) {
  Serial.begin(9600);
  if (u8g.getMode() == U8G_MODE_BW)       {
    u8g.setColorIndex(1);
  }
  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);
  pinMode(pinEncButt,  INPUT_PULLUP);

  attachInterrupt(0, updateEncoder, RISING);
  attachInterrupt(1, buttonChange, RISING);
}

void loop(void) {
//  if (encoderValue / encoderDivider == 0) {                           //Move Menu
//    coordinates[0] = 39;
//    coordinates[1] = 22;
//    if (buttonFlag == true) {
//      cleardisplay();
//      encoderValue = 0;
//      currentScreen = 1;
//    }
//  }
//  else if (encoderValue / encoderDivider == 1) {                      //Home Menu
//    coordinates[0] = 114;
//    coordinates[1] = 22;
//  }
//  else if (encoderValue / encoderDivider == 2) {                    //Approach Menu
//    coordinates[0] = 67;
//    coordinates[1] = 51;
//  }
//  else if (encoderValue / encoderDivider == 3) {                    //retract Menu
//    coordinates[0] = 123;
//    coordinates[1] = 51;
//  }
//  else {
//    encoderValue = 0;
//  }

  Serial.print( digitalRead(pinEncButt) );
  Serial.print("      {");
  Serial.print(coordinates[0]);
  Serial.print(",");
  Serial.print(coordinates[1]);
  Serial.print("}      ");
  Serial.println(encoderValue);
  u8g.firstPage();
      do {
    drawMain();
  } while ( u8g.nextPage() );
  delay(50);
}
