
/*
 SD card read/write

This example shows how to read and write data to and from an SD card file   
The circuit:
* SD card attached to SPI bus as follows:
** MOSI - pin 11
** MISO - pin 12
** CLK - pin 13
** CS - pin 4

created   Nov 2010
by David A. Mellis
modified 9 Apr 2012
by Tom Igoe

This example code is in the public domain.
   
*/

#include <SD.h>

File myFile;
char buf[10];
int datasize= 15;



void setup()
{
  delay(100);
// Open serial communications and wait for port to open:
 Serial.begin(9600);
 Serial.print("Initializing SD card...");
  for(int f=2;f<14;f++){
   pinMode(f,OUTPUT);
 // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
 // Note that even if it's not used as the CS pin, the hardware SS pin 
 // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
 // or the SD library functions will not work. 
  
 if (!SD.begin(4)) {
   Serial.println("initialization failed!");
   return;
 }
 Serial.println("initialization done.");  

   
 }

}

char ReadOut(){
  String image[datasize];
  char buf[10];
    for(int i; i < datasize;i++){
       myFile.read(buf,8);        
           Serial.println(buf);
           image += String(buf);
           myFile.read(buf,2); 
           delay(100); 
    }
    return buf[10];
}

void Turnpinon(char a[10]){
int i= a[0]-'0';
int j= a[1]-'0';
int k= a[2]-'0';
int l= a[3]-'0';
int m= a[4]-'0';
int n= a[5]-'0';
int o= a[6]-'0';
int p= a[7]-'0';

digitalWrite(6,i);
digitalWrite(7,j);/*
digitalWrite(8,k);
digitalWrite(9,l);*/
  }

void loop()
{
    delay(2000); 
   
 // re-open the file for reading:
 myFile = SD.open("test.txt");
 if (myFile) {
   Serial.println("test.txt:");
   
   // read from the file until there's nothing else in it:
ReadOut();

   
/*
    for(int i; i < datasize;i++){
       myFile.read(buf,8);        
           Serial.println(buf);
 
           myFile.read(buf,2); 
           delay(100);     
    
   }*/
   // close the file:
   myFile.close();
 } else {
  // if the file didn't open, print an error:
   Serial.println("error opening test.txt");
 }
}
