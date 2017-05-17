int dl = 17;

void setup() {
}

void loop() {
  pinMode(8, OUTPUT);
  delay(dl);
  pinMode(8, INPUT);
  delay(dl);
}
