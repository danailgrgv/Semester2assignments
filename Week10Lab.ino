#include <avr/io.h>
#include <avr/interrupt.h>

volatile int timerCounter; // For counting in the timer to achieve the desired frequency
volatile int numberCounter; // The number that will be displayed with the LEDs
volatile boolean updateSpeed = LOW; // The speed at which the LEDs are updated with the number
volatile boolean changed = 0;

void setup()
{
  timerCounter = 0;
  numberCounter = 0;

  // Sets the Data direction register of port b so that pins 9, 10, 11 and 12 are output
  DDRB |= _BV(DDB1);
  DDRB |= _BV(DDB2);
  DDRB |= _BV(DDB3);
  DDRB |= _BV(DDB4);

  // Sets the Data direction register of port D so that pins 2 and 3 are input
  DDRD &= ~_BV(DDD2);
  DDRD &= ~_BV(DDD3);

  // Enables the internal pull-up resistors for pins 2 and 3
  PORTD |= _BV(PORT2);
  PORTD |= _BV(PORT3); 
  
  // Timer 1
  cli(); // Disables global interrupts
  
  TCCR1A = 0; // sets the TCCR1A and TCCR1B registers to 0
  TCCR1B = 0;
  
  OCR1A = 750000; // Sets the compare match register to desired timer count, so that the number is displayed 3-4 times per second
  
  TCCR1B |= (1 << WGM12); // Turns on CTC mode
  
  // Set CS10 and CS11 bits for 64 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS11);
  
  TIMSK1 |= (1 << OCIE1A); // Enables timer compare interrupt
  attachInterrupt(0, pin2_ISR, FALLING); // Enables an interrupt on pin 2 when falling
  attachInterrupt(1, pin3_ISR, FALLING); // Enables an interrupt on pin 2 when falling
  sei(); // Enables global interrupts
}

void loop()
{
  if(changed)
  {
    if(updateSpeed == LOW)
    {
      cli();
      TCCR1B |= (1 << CS11); // Set CS11 bit for 64 prescaler
      sei();
    }
    else
    {
      cli();
      TCCR1B &= ~(1 << CS11);  // Sets the prescaler to 1; i.e. no prescaler
      sei();
    }
    changed = 0;
  }
}

ISR(TIMER1_COMPA_vect)
{
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

void pin2_ISR()
{
  updateSpeed = HIGH;
  changed = 1;
}

void pin3_ISR()
{
  changed = 1;
  updateSpeed = LOW;
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
