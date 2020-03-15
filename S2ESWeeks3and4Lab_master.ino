#include<SoftwareSerial.h>
SoftwareSerial master(10,11);
const int RLED = 4;
const int GLED = 5;
const int tltime = 3000;
unsigned long lastTime = 0;
const int timeout = 3100;
unsigned long timer = 0;
enum TlStates
{
  Red = 0,
  Green = 1
};
enum TlStates state = Green;
void setup() 
{
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  master.begin(9600);
  while(!master)
  {
    
  }
  master.write(state);
  digitalWrite(GLED, HIGH);
}

void loop() 
{
  if(millis()-lastTime >= tltime)
  {
    lastTime = millis();
    state = state + 1;
    if(state > 1)
    {
      state = 0;
    }
    master.write(state);
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
  if(master.available() > 0)
  {
    if(master.read() == 's')
    {
      timer = millis();
    }
  }
}
