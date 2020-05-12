volatile int ledState5 = LOW;
volatile int ledState6 = LOW;

void setup()
{ 
  DDRD |= _BV(DDD5); 
  DDRD |= _BV(DDD6); // Sets the pins 5 and 6 to output

  DDRD &= ~_BV(DDD2);
  DDRD &= ~_BV(DDD3); //Sets pins 2 and 3 to input

  PORTD |= _BV(PORT2);
  PORTD |= _BV(PORT3); // Internal pull-up resistor

  Serial.begin(9600);
  attachInterrupt(0, pin2_ISR, FALLING);
  attachInterrupt(1, pin3_ISR, FALLING);
}

void loop()
{
  if(ledState6 == HIGH)
  {
    Serial.println("Hello world!");
  }
}

void pin2_ISR()
{
  if(ledState5 == HIGH)
  {
    PORTD &= ~_BV(PORT5);
    ledState5 = LOW;
  }
  else
  {
    PORTD |= _BV(PORT5);
    ledState5 = HIGH;
  }
}

void pin3_ISR()
{
  if(ledState6 == HIGH)
  {
    PORTD &= ~_BV(PORT6);
    ledState6 = LOW;
  }
  else
  {
    PORTD |= _BV(PORT6);
    ledState6 = HIGH;
  }
}
