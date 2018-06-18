int msg = 0;

void setup() 
{
  Serial.begin(9600);
  randomSeed(analogRead(0));

  Serial.println(1, DEC);
}

void loop() 
{  
//  Serial.println(" Hello world!");
//  Serial.write(random(94) + 32);

  msg = Serial.read();

  if(msg > -1)
    Serial.println(msg, DEC);
}
