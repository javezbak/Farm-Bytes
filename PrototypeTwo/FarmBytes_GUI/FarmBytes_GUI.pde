import processing.serial.*;

abstract class Bucket
{
  int bucketNum;
  
  int x;
  int y;
  
  int recWidth;
  int recHeight;
  
  color fillColor;
  
  int sizeOfText;
  
  public abstract void display();
  //public abstract void fillData();
  //public abstract void logData();
}

class plantBucket extends Bucket
{
  //sensor data
  //double temp;
  double humid;
  double light;
  //double CO2;

  //constructor
  public plantBucket(int _bucketNum, int _x, int _y)
  {
    x = _x;
    y = _y;
    bucketNum = _bucketNum;
    
    //display data
    recWidth = 200;
    recHeight = 60;
    fillColor = color(211, 227, 151);
    sizeOfText = 12;
  }
  
  public void display()
  {
    //rectangle
    fill(fillColor);
    rect(x, y, recWidth, recHeight);
    
    //data
    fill(0,0,0);
    textSize(sizeOfText);
    //text("Temp: " + temp, x + 5, y, recWidth/3, recHeight);
    text("Humidity: " + humid, x + (recWidth/3), y, recWidth/3, recHeight);
    text("Light: " + light, x + ((recWidth/3)*2), y, recWidth/3, recHeight);
  }
  
}

class waterSupply extends Bucket
{
  //sensor data
  double pH;
  double EC;
  double temp;

  //constructor
  public waterSupply(int _bucketNum, int _x, int _y)
  {
    x = _x;
    y = _y;
    bucketNum = _bucketNum;
    
    //display data
    recWidth = 410;
    recHeight = 60;
    fillColor = color(141, 205, 193);
    sizeOfText = 17;
  }
  
  public void display()
  {
    //rectangle
    fill(fillColor);
    rect(x, y, recWidth, recHeight);
    
    //data
    fill(0,0,0);
    textSize(sizeOfText);
    text("Temperature: " + temp, x + 5, y, recWidth/3, recHeight);
    text("EC: " + EC, x + (recWidth/3), y, recWidth/3, recHeight);
    text("pH " + pH, x + ((recWidth/3)*2), y, recWidth/3, recHeight);
  }
}

Serial port;
Bucket allBuckets[];

void setup()
{
  //resolution of pi display
  size(480, 320);
  
  allBuckets = new Bucket[]
  {
    new plantBucket(1, 30, 20),
    new plantBucket(2, 240, 20),
    new plantBucket(3, 30, 90),
    new plantBucket(4, 240, 90),
    new plantBucket(5, 30, 160),
    new plantBucket(6, 240, 160),
    new waterSupply(7, 30, 230)
  };
  
  //port for Arduino
  port = new Serial(this, "/dev/tty.usbmodem1431", 9600);
}

void draw()
{
  //gray
  background(226, 226, 226);
  
  //read in the data from the arduino
  String inBuffer = port.readString(); 
  
  //draw the rectangles
  for(int i = 0; i < allBuckets.length; ++i)
  {
    if(i == 6)
    {
      waterSupply temper = (waterSupply)allBuckets[i];
      temper.pH = 7;
      temper.temp = 80;
      temper.EC = 5;
      allBuckets[i] = temper;
    }
    else
    {
      int startData = inBuffer.indexOf("#" + i);
      int endData = inBuffer.indexOf("END", startData);
      
      if(startData == -1 || endData == -1)
         break;
         
      String dataForBucket = inBuffer.substring(startData, endData);
      
      println("The data for this bucket is:");
      println(dataForBucket);
      println("end");
      
      plantBucket pB = (plantBucket)allBuckets[i];
      //pB.temp = 75;
      
      int hStart = dataForBucket.indexOf("H = ");
      println("hStart is " + hStart);
      int lStart = dataForBucket.indexOf("L");
      println("lStart is " + hStart);
      
      pB.humid = Double.parseDouble(dataForBucket.substring(hStart+4, lStart));
      pB.light = 45;
      allBuckets[i] = pB;
    }
    allBuckets[i].display();
  }

  delay(4000);
}
