#include <avr/io.h>
#include <avr/interrupt.h>

volatile int timerCounter; // For counting in the timer to achieve the desired frequency
volatile int numberCounter; // The number that will be displayed with the LEDs

void setup()
{
  timerCounter = 0;
  numberCounter = 0;

  // Set the Data direction register of port b so that pins 9, 10, 11 and 12 are output
  DDRB |= _BV(DDB1);
  DDRB |= _BV(DDB2);
  DDRB |= _BV(DDB3);
  DDRB |= _BV(DDB4);
  
  // Timer 1
  cli(); // Disables global interrupts
  
  TCCR1A = 0; // sets the TCCR1A and TCCR1B registers to 0
  TCCR1B = 0;
  
  OCR1A = 750000; // Sets the compare match register to desired timer count, so that the number is displayed every 3 seconds
  
  TCCR1B |= (1 << WGM12); // Turns on CTC mode
  
  // Set CS10 and CS11 bits for 64 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS11);
  
  TIMSK1 |= (1 << OCIE1A); // Enables timer compare interrupt
  sei(); // Enables global interrupts
}

void loop()
{
  
}

ISR(TIMER1_COMPA_vect)
{
  timerCounter++;
  if(timerCounter == 20)
  {
    timerCounter = 0;
    displayNumber();
    if(numberCounter == 0b1111)
    {
      numberCounter = 0;
    }
    else
    {
      numberCounter++;
    }
  }
}

void displayNumber()
{
  if(1&(numberCounter))
  {
    PORTB |= _BV(PORT1);
  }
  else
  {
    PORTB &= ~_BV(PORT1);
  }

  if(1&(numberCounter>>1))
  {
    PORTB |= _BV(PORT2);
  }
  else
  {
    PORTB &= ~_BV(PORT2);
  }

  if(1&(numberCounter>>2))
  {
    PORTB |= _BV(PORT3);
  }
  else
  {
    PORTB &= ~_BV(PORT3);
  }

  if(1&(numberCounter>>3))
  {
    PORTB |= _BV(PORT4);
  }
  else
  {
    PORTB &= ~_BV(PORT4);
  }
  
}
