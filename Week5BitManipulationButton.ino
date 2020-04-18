// the states of the LED and the button
int ledState;
int buttonState;

// for the debouncing of the button
int lastButtonState = LOW;  
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    

void setup() 
{
  DDRB |= _BV(DDB2); // Sets pin 10 on the arduino to output
  DDRD &= ~_BV(DDD7); // Sets the pin 7 to input
  PORTD |= _BV(PORT7); // Internal pull-up resistor
  PORTB |= ~_BV(PORT2); // Set the initial output of the LED pin to 0
  ledState = LOW; // Sets the initial 
}

void loop() 
{
  int reading = PIND>>7; // We get the reading from the button on pin 7 from the register
  
  if (reading != lastButtonState) // We check for noise
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) // We check if the debounce interval has passed
  {
    if (reading != buttonState) // If the button state has changed from the previous loop
    {
      buttonState = reading;

      if (buttonState == LOW) // If the button is pressed, we toggle the LED state
      {
        ledState = !ledState;
      }
    }
  }

  // Turn the LED on or off, according to the state
  if(ledState == HIGH)
  {
    PORTB |= _BV(PORT2);
  }
  else
  {
    PORTB &= ~_BV(PORT2);
  }

  lastButtonState = reading; // We save the current reading of the button to check for noise in the next loop
}
