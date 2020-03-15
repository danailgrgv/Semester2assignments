#include<SoftwareSerial.h>
SoftwareSerial slave(10,11);
const int RLED = 4;
const int GLED = 5;
const int timeout = 3100;
unsigned long timer = 0;
enum TlStates
{
  Red = 1,
  Green = 0
};
enum TlStates state;
void setup() 
{
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  slave.begin(9600);
}

void loop() 
{
  if(slave.available() > 0)
  {
    state = slave.read();
    timer = millis();
    slave.write('s');
  }
  switch (state)
  {
    case Red:
    {
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      break;
    }
    case Green:
    {
      if(millis() - timer < timeout)
      {
        digitalWrite(RLED, LOW);
        digitalWrite(GLED, HIGH);
      }
      else
      {
        digitalWrite(RLED, HIGH);
        digitalWrite(GLED, LOW);
      }
      break;
    }
    default:
    {
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      break;
    }
  }
}
