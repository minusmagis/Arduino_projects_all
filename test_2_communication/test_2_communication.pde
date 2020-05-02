import processing.serial.*;

Serial myPort;
void setup()
{
  String portName = "COM3";
    
   myPort = new Serial(this, portName, 9600);
}
void draw()
{
  if(myPort.available()>0)
  {
  println(myPort.read());
  delay(200);
  }
  else
  {
  println("no devices found");
  }
}