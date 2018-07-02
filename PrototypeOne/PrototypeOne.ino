int solenoidPin = 4;
int lightPin = 5;
long openTimeS = 5; // time open [s] (5 sec)
long closedTimeS = 300; // time closed [s] (5 min)
long closedTimeL = 28800; // time lights are off [s] (8 hours)
long openTimeL = 43200; // time lights are on [s] (12 hours)
long totTime = 22200; // time from 5 am till when the program is started [s] ( 6 hours 10 min) void setup() {
 Serial.begin(9600);
 
 // put your setup code here, to run once:
 pinMode(solenoidPin, OUTPUT); //This sets the output pin to the chosen one(solenoidPin)
 pinMode(lightPin, OUTPUT);
}
void loop() {
 Serial.println("Beggining of the loop");
 
 // put your main code here, to run repeatedly:
 digitalWrite(lightPin, HIGH); //switch on the lights
 digitalWrite(solenoidPin, HIGH); // open the solenoid valve
 delay(openTimeS*1000);  // wait for openTimeS seconds
 digitalWrite(solenoidPin, LOW); // close the solenoid valve
 delay(closedTimeS*1000);  // wait for closedTimeS
 Serial.println("Just finished the code outside the if statement");
   
 totTime = totTime + (openTimeS+closedTimeS);
 Serial.println("totTime is ");
 Serial.print(totTime);
 Serial.println("");
 if(totTime >= openTimeL)
 {
   Serial.println("INSIDE THE IF STATEMENT");
   digitalWrite(lightPin, LOW); //switch off the lights
   delay(closedTimeL*1000);  // wait for 12 hours
   totTime = 0;
 }
}
