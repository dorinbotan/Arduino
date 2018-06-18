#include <SPI.h>

char buf[1000];
volatile byte pos;
volatile boolean process_it;

ISR(SPI_STC_vect)
{
  char c = SPDR;

  buf[pos++] = SPDR;   
    
  if(c == 'o')
  {
    process_it = true;
  }
  else if(c == 0)
  {
    pos--;
    Serial.println("EmptY");
    Serial.println(pos);
  }
}

void setup(void)
{
  Serial.begin(9600);

  // have to send on master in, *slave out*
  pinMode(MISO, INPUT);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  pos = 0;
  process_it = false;

  SPI.attachInterrupt();
}

void loop(void)
{
  if(process_it)
  {
    process_it = false;

    Serial.println(buf);
    Serial.println(pos);
    
    pos = 0;
  }
}
