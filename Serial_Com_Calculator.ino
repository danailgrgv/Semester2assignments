#include <Arduino.h>
char equation[3][10];
int inputCounter;
char trash;

float calculate()
{
  float result;
  int numbers[2];
  sscanf(equation[0], "%d", &numbers[0]);
  sscanf(equation[2], "%d", &numbers[1]);
  switch(equation[1][0])
  {
    case '+':
    {
     result = numbers[0]+numbers[1];
     break;
    }
    case '-':
    {
    result = numbers[0]-numbers[1];
    break; 
    }
    case '*':
    {
      result = numbers[0]*numbers[1];
      break;
    }
    case '/':
    {
      result = numbers[0]/numbers[1];
      break;
    }
    default :
    Serial.println("Invalid input for operation");
    result = 0;
  }
  return result;
}

void setup()
{
  Serial.begin(9600);
  inputCounter = 0;
  Serial.println("Input the equation");
}

void loop()
{
  if(Serial.available() > 0)
  {
    if(Serial.peek() == '\n')
    {
      trash = Serial.read();
      inputCounter++;
    }
    int bytesToRead = Serial.available();
    for(int i=0; i<bytesToRead; i++)
    {
      equation[inputCounter][i] = Serial.read();
    }
    if(inputCounter<3)
    {
      Serial.print(equation[inputCounter]);
    }
  }
  if(inputCounter == 3)
  {
    Serial.print("=");
    Serial.println();
    Serial.println(calculate());
    inputCounter = 0;
  }
}
