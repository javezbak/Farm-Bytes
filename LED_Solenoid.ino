int solenoidPin1 = 4;
int LED = 6;

void setup() {
  // put your setup code here, to run once:
pinMode(solenoidPin1, OUTPUT);
pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(solenoidPin1, HIGH); //Solenoid ON
  delay(2000);                      //2 sec delay
  digitalWrite(solenoidPin1, LOW);  //Solenoid OFF
  delay(2000);                       //2 sec delay

  digitalWrite(LED, HIGH);            //LED ON
  delay(4000);                      //4 sec delay
  digitalWrite(LED, LOW);             //LED OFF
  delay(4000);                      //4 sec delay
  
}

