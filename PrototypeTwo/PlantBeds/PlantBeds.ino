#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

//Constants
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define NUM_PINS 6

//pin numbers associated with the analog input for each DHT sensor
DHT* dhtSensors[NUM_PINS];
int DHTPinNums[NUM_PINS] = {31, 33, 43, 45, 50, 51};
int lightPinNums[NUM_PINS] = {A0, A1, A2, A3, A5, A7};
float temp, humid;
int bucketNum; 

void setup()
{
  //initialize all DHT instances
  for(int i = 0; i < NUM_PINS; ++i)
    dhtSensors[i] = new DHT(DHTPinNums[i], DHTTYPE);
  
  Serial.begin(9600);
}

void loop()
{
    //data is available to read
    if (Serial.available() > 0)
    { 
      bucketNum = Serial.read(); 
      if(bucketNum >= 0 && bucketNum <= 6) //GUI is asking for data regarding a bucket
      {
        for(int i = 0; i < NUM_PINS; ++i)
        {
          Serial.print("BUCKET #"); Serial.println(bucketNum);
    
          //temp = dhtSensors[i]->readTemperature();
          humid = dhtSensors[bucketNum]->readHumidity();
          
          //Serial.print("T = "); Serial.print(temp); 
          Serial.print("H = "); Serial.println(humid); 
    
           //light
           Serial.print("L = ");
           Serial.println(analogRead(lightPinNums[bucketNum]));
           Serial.println("END" + );
        }
      }
    }
      
    delay(1000);
}

