#include <Wire.h>

int slave_address = 0x1;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
}

void loop() 
{
  if(Serial.available() > 0)
  {
//    for(int i = 0; i < 256; i++) {
  int i = 10;
//      unsigned char readVal = Serial.read();
      Wire.beginTransmission(slave_address);
      Wire.write(i);
      Wire.endTransmission();

      Wire.requestFrom(slave_address, 1);
      while(Wire.available() == 0);
      Serial.println(Wire.read());
      
//      delay(100); 
//    }
  }
}
