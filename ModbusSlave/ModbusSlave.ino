#define BROADCAST 0x00
#define ADDRESS   0xCB

int buffer_size = 0;
unsigned char *input_buffer;

void setup()
{
  Serial.begin(9600);

  input_buffer = (unsigned char *)malloc(1024);
}

void loop() 
{
  while(Serial.available() > 0) 
  {
    *(input_buffer + buffer_size) = (char)Serial.read();
    buffer_size++;
  }
  
  if(buffer_size != 0)
  {
    buffer_size = 0;

//    Serial.print(input_buffer[0], HEX);
  }
}
