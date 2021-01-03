#define OUT 9

void setup() {
  pinMode(OUT, OUTPUT);

  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 127;            // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS10);    // no prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();
}

ISR(TIMER1_OVF_vect) { // Interrupt service routine
  TCNT1 = 127;            // preload timer
  digitalWrite(OUT, digitalRead(OUT) ^ 1);
}

void loop() {
  delay(10);
}
