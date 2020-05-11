const int debounceDelay = 50;

volatile int ledState5 = LOW;
volatile int ledState6 = LOW;

volatile int lastTime2;
volatile int lastTime3;

void setup()
{
  lastTime2 = 0;
  lastTime3 = 0;
  
  DDRD |= _BV(DDD5); 
  DDRD |= _BV(DDD6); // Sets the pins 5 and 6 to output

  DDRD &= ~_BV(DDD2);
  DDRD &= ~_BV(DDD3); //Sets pins 2 and 3 to input

  PORTB |= _BV(PORT2);
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
  if(millis() -lastTime2 > debounceDelay)
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
    lastTime2 = millis();
  }
}

void pin3_ISR()
{
  if(millis() -lastTime3 > debounceDelay)
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
    lastTime3 = millis();
  }
}
