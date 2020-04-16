const int period = 5000; // set the interval to 5 seconds
unsigned long lastTime; // to count the time for the interval
byte state; // to save the state

// here i use macros for setting the registeres, but otherwise it would have had to be done with a mask like that
// #define DDRBMask B00000100;

void setup()
{
  //We set the data direction of pin 10 on the arduino to output
  DDRB  |=  _BV(DDB2); // bit 2 corresponds to pin 10 on the arduino

  //Or, if we used masks :
  //DDRB |= DDRBMask;
  
  lastTime = 0;
  state = 0;
 
  TCCR1A = _BV(COM1B1) | _BV(WGM11) | _BV(WGM10); // Sets the COM2B bit to provide non-inverted PWM for output B (pin 10) and WGM selects fast PWM for the pins
  TCCR1B = TCCR1B & B11111000 | B00000011; // set timer 1 divisor to 64 for PWM frequency of 490.20 Hz, which is the default
}

void loop()
{
  while(millis()-lastTime < period)// a five-second loop
  {
    if(state & 1) // turns the led on 40% duty by setting the output compare register value to 200, which is ~ 40% of 490
    {
      OCR1B = 200;
    }
    else // turns the led off
    {
      OCR1B = 0;
    }
  }

  //reset the interval
  lastTime=millis();
  
  //flip the state
  if(state & 1)
  {
    state &= 0;
  }
  else
  {
    state |= 1;
  }
}
