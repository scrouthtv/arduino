// See https://www.arduino.cc/en/Hacking/PinMapping168


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PD5, OUTPUT);
  pinMode(PD6, OUTPUT);
  pinMode(PD7, OUTPUT);
  pinMode(8, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(8, LOW);
  digitalWrite(PD5, HIGH);
  delay(100);
  digitalWrite(PD5, LOW);
  digitalWrite(PD6, HIGH);
  delay(100);
  digitalWrite(PD6, LOW);
  digitalWrite(PD7, HIGH);
  delay(100);
  digitalWrite(PD7, LOW);
  digitalWrite(8, HIGH);
  delay(100);
}
