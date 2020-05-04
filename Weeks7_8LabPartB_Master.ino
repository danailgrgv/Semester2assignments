#include <Wire.h>
#include <string.h>
int *addressA;
int *addressB;
int *addressMin;
int *addressMax;
bool addressesReceived;
int dump;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  addressesReceived = false;
}

void loop()
{
  if(!addressesReceived) //Gets the addresses (only once)
  {
    Wire.requestFrom(42, 8);
    addressA = Wire.read();
    Wire.requestFrom(42, 8);
    addressB = Wire.read();
    Wire.requestFrom(42, 8);
    addressMin = Wire.read();
    Wire.requestFrom(42, 8);
    addressMax = Wire.read();
    addressesReceived = true;
  }
  Serial.println("Please select r or w");
  while(Serial.peek() == '\n')
  {
    dump = Serial.read();
  }
  while(Serial.available() == 0)
  {}
  char c = Serial.read();
  Serial.println(c);
  if(c == 'r')
  {
    Serial.println("Please select the register you want to read from : A, B, Min, Max");
    while(Serial.peek() == '\n')
    {
      dump = Serial.read();
    }
    char answer;
    while(Serial.available() <= 0)
    {
      //do nothing
    }
    answer = Serial.read();
    
    int reading;
    Serial.println(answer);
    if(answer == 'A')
    {
      reading = readFromRegister(addressA);
      Serial.print("The value of register A is ");
      Serial.print(reading);
      Serial.println();
    }
    else if(answer == 'B')
    {
      reading = readFromRegister(addressB);
      Serial.print("The value of register B is ");
      Serial.print(reading);
      Serial.println();
    }
    /*else if(answer == "Min")
    {
      reading = readFromRegister(addressMin);
      Serial.print("The value of register Min is ");
      Serial.print(reading);
      Serial.println();
    }
    else if(answer == "Max")
    {
      reading = readFromRegister(addressMax);
      Serial.print("The value of register Max is ");
      Serial.print(reading);
      Serial.println();
    }*/
    else
    {
      Serial.println("That register does not exist, please try again!");
      Serial.println();
    }
  }
  else if(c == 'w')
  {
    Serial.println("Please select the register you want to write in : A or B");
    delay(100);
    while(Serial.peek() == '\n')
    {
      dump = Serial.read();
    }
    while(Serial.available() == 0)
    {}
    c = Serial.read();
    Serial.println(c);
    if(c == 'A')
    {
      Serial.println("Please type in the value for register A");
      while(Serial.peek() == '\n')
      {
        dump = Serial.read();
      }
      while(Serial.available() == 0)
      {}
      int value = Serial.read();
      writeInRegister(addressA, value);
      Serial.println(value);
    }
    else if(c == 'B')
    {
      Serial.println("Please type in the value for register B");
      while(Serial.peek() == '\n')
      {
        dump = Serial.read();
      }
      while(Serial.available() == 0)
      {}
      int value = Serial.read();
      Serial.println(value);
      writeInRegister(addressB, value);
    }
    else
    {
      Serial.println("That register does not exist, please try again!");
      Serial.println();
    }
  }
  else
  {
    Serial.println("There isnt such a procedure, please try again!");
    Serial.println();
  }
  delay(100);
}

int readFromRegister(int *address)
{
  Wire.requestFrom(42,8);
  int confirm = 0;
  int value;
  confirm = Wire.read();
  if(confirm)
  {
    Wire.beginTransmission(42);
    Wire.write((int)address);
    Wire.endTransmission();
    Wire.requestFrom(42, 8);
    value = Wire.read();
    return value;
  }
  else
  {
    Serial.println("Reading unsuccessful!");
    return NULL;
  }
}

void writeInRegister(int *address, int value)
{
  Wire.beginTransmission(42);
  Wire.write((int)address);
  Wire.write(value);
  Wire.endTransmission();
}
