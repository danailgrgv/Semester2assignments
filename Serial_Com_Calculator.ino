int firstNumber;
int secondNumber;
char operation;
int result;

void setup()
{
  Serial.begin(9600);
  result = 0;
  firstNumber = 0;
  secondNumber = 0;
}

void loop()
{
  if(Serial.available() > 0)
  {
    firstNumber = Serial.parseInt();
    operation = Serial.read();
    secondNumber = Serial.parseInt();
    calculate();
    Serial.print("Result : ");
    Serial.print(result);
    Serial.println();
  }
}

void calculate()
{
  switch(operation)
  {
    case '+':
    {
     result = firstNumber+secondNumber;
     break;
    }
    case '-':
    {
    result = firstNumber-secondNumber;
    break; 
    }
    case '*':
    {
      result = firstNumber*secondNumber;
      break;
    }
    case '/':
    {
      result = firstNumber/secondNumber;
      break;
    }
    default :
    Serial.println("Invalid input for operation");
    result = 0;
  }
}
