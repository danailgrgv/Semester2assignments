void setup() 
{
  DDRD |= _BV(DDD5); 
  DDRD |= _BV(DDD6); // Sets the pins 5 and 6 to output

  DDRB &= ~_BV(DDB2);
  DDRB &= ~_BV(DDB3); // Sets the pins 10 and 11 to input
  
  PORTB |= _BV(PORT2);
  PORTB |= _BV(PORT3); // Internal pull-up resistor

  Serial.begin(9600);
}

void loop() 
{
  if(!((PINB>>2)&1)) //If the button connected to pin 10 is pressed
  {
    if(!((PINB>>3)&1)) //If the button connected to pin 11 is also pressed
    {
      PORTD |= _BV(PORT6); //Turn both LEDs on for 0.5 sec and off for 0.5 sec again
      PORTD |= _BV(PORT5);
      delay(500);
      PORTD &= ~_BV(PORT5);
      PORTD &= ~_BV(PORT6);
      delay(500);
    }
    PORTD |= _BV(PORT5); //Turn the LED on pin 5 on
  }
  else if(!((PINB>>3)&1)) //If only the button connected to pin 11 is pressed
  {
    PORTD |= _BV(PORT6); //Turn the LED on pin 6 on
    Serial.println("Hello world!");
  }
  else //If no buttons are pressed, turn both LEDs off
  {
    PORTD &= ~_BV(PORT5);
    PORTD &= ~_BV(PORT6);
  }
}
