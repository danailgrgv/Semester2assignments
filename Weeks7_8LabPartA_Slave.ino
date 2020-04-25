#include <Wire.h>
byte c = 0;

void setup()
{
  Wire.begin(42);                // join i2c bus with address 42
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestHandler); // register request
  Serial.begin(9600);           // start serial for output
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany)
{
  while (0 < Wire.available())
  {
    c = Wire.read();
    Serial.println("Received : ");
    Serial.println(c);
  }
}

// function that executes whenever data is requested from master
void requestHandler()
{
  if(c>100)
  {
    Wire.write(2);
    Serial.println("Sent back 2");
  }
  else
  {
    Wire.write(4);
    Serial.println("Sent back 4");
  }
  
}
