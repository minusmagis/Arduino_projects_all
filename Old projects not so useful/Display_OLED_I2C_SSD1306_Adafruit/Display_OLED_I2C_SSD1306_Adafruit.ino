/*
This is an example of how to use the OLED 128x64 I2C with SSD1306 driver using the Adafruit library.
It also applies to the 128x32 version, but not all components would fit the smaller screen.

Pins:
 * GND = GND
 * VCC = 5V
 * SCL = A5
 * SDA = A4

You can connect VCC to 3.3V to reduce the amount of high pitched noise that the display produces.

It's a good idea to put a resistor between A4-5V and A5-5V to help stabilize the connection.
What that does is pull-up the I2C pins to make it more reliable and prevents lock-ups.


Libraries needed:
https://github.com/adafruit/Adafruit_SSD1306
https://github.com/adafruit/Adafruit-GFX-Library


Guide for the GFX Library: https://cdn-learn.adafruit.com/downloads/pdf/adafruit-gfx-graphics-library.pdf

List of fonts: https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts

List of fonts that support right alignment:
FreeMono9pt7b.h
FreeMono12pt7b.h
FreeMono18pt7b.h
FreeMono24pt7b.h
FreeMonoBold9pt7b.h
FreeMonoBold12pt7b.h
FreeMonoBold18pt7b.h
FreeMonoBold24pt7b.h
FreeMonoBoldOblique9pt7b.h
FreeMonoBoldOblique12pt7b.h
FreeMonoBoldOblique18pt7b.h
FreeMonoBoldOblique24pt7b.h
FreeMonoOblique9pt7b.h  
FreeMonoOblique12pt7b.h
FreeMonoOblique18pt7b.h
FreeMonoOblique24pt7b.h


This sketch was featured on my video tutorial for this display: https://www.youtube.com/watch?v=PrIAnDZ9dp8

Sketch made by: InterlinkKnight
Last modification: 10/05/2019
*/



#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display


Adafruit_SSD1306 display(128, 64);  // Create display



void setup()  // Start of setup
{                

  delay(100);  // This delay is needed to let the display to initialize

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C
 
  display.clearDisplay();  // Clear the buffer

  display.setTextColor(WHITE);  // Set color of the text

  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3

  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                               // To override this behavior (so text will run off the right side of the display - useful for
                               // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                               // with setTextWrap(true).

  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)

}  // End of setup






void loop()  // Start of loop
{




  display.clearDisplay();  // Clear the display so we can refresh

  // Draw rounded rectangle:
  display.drawRoundRect(79, 37, 49, 27, 8, WHITE);  // Draw rounded rectangle (x,y,width,height,radius,color)
                                                    // It draws from the location to down-right



  
  display.display();  // Print everything we set previously



  

}  // End of loop
