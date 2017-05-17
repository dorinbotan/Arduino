int sensorValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  sensorValue = analogRead(A1);
  Serial.println(sensorValue);
//  sensorValue = analogRead(A2);
//  Serial.println(sensorValue);
  sensorValue = analogRead(A3);
  Serial.println(sensorValue);
  sensorValue = analogRead(A4);
  Serial.println(sensorValue);
  sensorValue = analogRead(A5);
  Serial.println(sensorValue);
}
