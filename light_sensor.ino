int AnalogValue = 0;

void setup(){
Serial.begin(9600);
}

void loop(){
AnalogValue = analogRead(A0);
Serial.println(AnalogValue);
delay(500);
}
