extern float PosZ;
extern char Command[];
extern float Extruder;
extern float Feedrate;
extern int toolPower;

void Debugging_Serial_print(){
  Serial.println("");
  Serial.println("--------------Debugging Section-------------------");
  Serial.print("Received Command: ");
  Serial.println(Command);
  Serial.print("Understood Command: ");
  Serial.print(Command[0]);
  Serial.println(CommandNumberExtractor());
  Serial.print("Z Position = ");
  Serial.println(PosZ);
  Serial.print("Feedrate = ");
  Serial.println(Feedrate);
  Serial.println("--------------------------------------------------");
  Serial.println("");
}
