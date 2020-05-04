#include <Wire.h>

int *prA;
int *prB;
int *prMin;
int *prMax;
int *address;
bool addressesSent;
bool readMode;
int requestCounter;
int writeCounter;

void setup()
{
  register int registerA;
  register int registerB;
  register int Min;
  register int Max;
  Wire.begin(42);                // join i2c bus with address 42
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestHandler); // register request
  Serial.begin(9600);           // start serial for output
  registerA = 52;
  registerB = 42;
  Min = 0;
  Max = 0;
  prA = &registerA;
  prB = &registerB;
  addressesSent = 0;
  requestCounter++;
  writeCounter++;
  readMode = false;
  Serial.println("Adress of registerA");
  Serial.println((int)prA);
  Serial.println("Adress of registerB");
  Serial.println((int)prB);
  Serial.println("Value of registerA");
  Serial.println(*prA);
  Serial.println("Value of registerB");
  Serial.println(*prB);
  Serial.println();
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
    if(readMode)
    {
      address = Wire.read();
    }
    else if(writeCounter == 0)
    {
      address = Wire.read();
      writeCounter++;
    }
    else if(writeCounter == 1)
    {
      *address = Wire.read();
      writeCounter = 0;
      if(*prA > *prB)
      {
        *prMin = *prB;
      }
      else
      {
        *prMin = *prA;
      }
    }
  }
}

// function that executes whenever data is requested from master
void requestHandler()
{
  if(addressesSent == 0)
  {
    Wire.write((int)prA);
    addressesSent = 1;
  }
  else if(addressesSent == 1)
  {
    Wire.write((int)prB);
    addressesSent = 2;
  }
  else if(addressesSent == 2)
  {
    Wire.write((int)prMin);
    addressesSent = 3;
  }
  else if(addressesSent == 3)
  {
    Wire.write((int)prMax);
    addressesSent = 4;
  }
  else if(requestCounter == 0)
  {
    requestCounter++;
    readMode = true;
    Wire.write(1);
  }
  else if(requestCounter == 1)
  {
    Wire.write(*address);
    requestCounter = 0;
  }
}
