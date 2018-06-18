#include <SPI.h>

SPISettings settings(100000, MSBFIRST, SPI_MODE0);

void setup() 
{
  Serial.begin(9600);
  SPI.begin();
}

void loop() 
{
  int in1, in2;
  
  SPI.beginTransaction(settings);
  in1 = SPI.transfer('h');
  in1 = SPI.transfer('e');
  in1 = SPI.transfer('l');
  in1 = SPI.transfer('l');
  in1 = SPI.transfer('o');
  SPI.endTransaction();

  delay(100);
}
