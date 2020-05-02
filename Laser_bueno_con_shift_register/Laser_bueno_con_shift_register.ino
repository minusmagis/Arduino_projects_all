/*
 SD card read/write

This example shows how to read and write data to and from an SD card file   
The circuit:
* SD card attached to SPI bus as follows:
** MOSI - pin 11
** MISO - pin 12
** CLK - pin 13
** CS - pin 4

*/

#include <SD.h>

File myFile;
int nSR=1;
int nLaser=10;
char buf[10];
char dummy[2];
int thetasize= 15;
String image;
int LatchPin = A0;
int ClockPin = A1;
int DataPin = A2;
int ClearPin = 2;
int BlankPin = 3;

void setup()
{
  delay(100);
// Open serial communications and wait for port to open:
 Serial.begin(9600);
 Serial.print("Initializing SD card...");
  for(int f=2;f<14;f++){
   pinMode(f,OUTPUT);
  }
 // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
 // Note that even if it's not used as the CS pin, the hardware SS pin 
 // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
 // or the SD library functions will not work. 
  pinMode(10, OUTPUT);
  
 if (!SD.begin(4)) {
   Serial.println("initialization failed!");
   return;
 }
 Serial.println("initialization done.");  


   
 

}




void loop()
{
    delay(2000); 
   
 // re-open the file for reading:
 myFile = SD.open("test.txt");
 if (myFile) {
   Serial.println("test.txt:");
   
   // read from the file until there's nothing else in it:
    for(int i=0; i < thetasize;i++){
       myFile.read(buf, 11);        
       Serial.println(buf);
       for(int j=0; j< nLaser; j++){
        delay(100);
           int a = buf[j] - '0';
           if (a==1){
           digitalWrite(DataPin,HIGH);
           }
           else {
           digitalWrite(DataPin,LOW);
           }
           delay(50);
           digitalWrite(ClockPin,HIGH);
           delay(50);
           digitalWrite(ClockPin,LOW);
           delay(50);
           digitalWrite(DataPin,LOW);
           
       }
       delay(20);
       digitalWrite(LatchPin,HIGH);
       delay(50);
       digitalWrite(LatchPin,LOW);
       myFile.read(dummy,1); //Paso de linea
       delay(1000); 
   }
   
   // close the file:
   myFile.close();
 } else {
  // if the file didn't open, print an error:
   Serial.println("error opening test.txt");
 }
}
