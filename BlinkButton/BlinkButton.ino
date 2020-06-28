#define LEDPIN 13
#define BUTPIN 12

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTPIN, INPUT);
}

void loop() {
  digitalWrite(LEDPIN, digitalRead(BUTPIN));
  delay(100);
}
