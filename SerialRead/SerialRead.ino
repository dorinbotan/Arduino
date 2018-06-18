int buffer_size = 0;
char *input_buffer;

void setup()
{
  Serial.begin(9600);

  input_buffer = (char *)malloc(1024);
}

void loop() 
{
  while(Serial.available() > 0) 
  {
    *(input_buffer + buffer_size) = Serial.read();
    buffer_size++;
  }
    
  if(buffer_size != 0)
  {
    *(input_buffer + buffer_size) = '\0';
    buffer_size = 0;

    Serial.print(input_buffer);
  }
}

#if 0
void loop() 
{
  if(Serial.available() > 0)
  {
    receivedByte = Serial.read();

    Serial.print("0x");
    Serial.println(receivedByte, HEX);
  }
}
#endif
