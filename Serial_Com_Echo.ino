char character;

void setup()
{
Serial.begin(9600);
}

void loop()
{
if(Serial.available() > 0)
{
  character = Serial.read();
  Serial.print(character);
}
}
