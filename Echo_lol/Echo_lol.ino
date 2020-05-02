int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //have Arduino waiting to receive input
  while (Serial.available () == 0);

  //read the input
  int val = Serial.read() - '0';

  if (val == 1) 
  {
  Serial.println("Led is On");
  digitalWrite(ledPin,HIGH);
  }
  else if (val == 0)
  {
    Serial.println("Led is Off");
    digitalWrite(ledPin,LOW);
  }
  else
  {
    Serial.println("Invalid");
  }
  while(Serial.available()>0) Serial.read();

}
