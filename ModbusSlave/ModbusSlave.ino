#define BROADCAST_ADDRESS 0x00
//#define SLAVE_ADDRESS     0xCB
#define SLAVE_ADDRESS     0xDE

int buffer_size = 0;
unsigned char *input_buffer;
unsigned long my_delay = 0;

void processFrame(unsigned char *frame, int frame_size)
{
  unsigned char addr = frame[0];

  if(addr == SLAVE_ADDRESS || 
     addr == BROADCAST_ADDRESS)
  {
    unsigned char instr = frame[1];
    
    Serial.println("Slave accessed");
    Serial.println(instr, HEX);
  }
}

void setup()
{
  Serial.begin(9600);

  input_buffer = (unsigned char *)malloc(1024);
}

void loop() 
{  
  while(Serial.available() > 0) 
  {
    input_buffer[buffer_size] = (char)Serial.read();
    buffer_size++;
    
    my_delay = 0;
  }

  if(buffer_size != 0)
  {
    // Frame received
    if(my_delay > 500) // (~190 delay between bytes, ~112k = ~100ms)
    {
      processFrame(input_buffer, buffer_size);
      
      my_delay = 0;
      buffer_size = 0;
    }
  }

  my_delay++;
}
