#include <Wire.h>

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

byte x = 90;

void loop() {
  Wire.beginTransmission(42); // transmit to device with adress 42
  Wire.write(x);              // sends one byte
  Serial.println("Sent : ");
  Serial.println(x);
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(42, 8); // requests one byte
  byte c = Wire.read();
  Serial.println("Received : ");
  Serial.println(c);
  Serial.println();
  
  x++;
  delay(1000);
}
