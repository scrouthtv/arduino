volatile unsigned long lastMillis = 0;
volatile unsigned long lastDelta = 0;

void setup() {

  Serial.begin(9600);

  noInterrupts();           // disable all interrupts
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  OCR2A = 255;            // compare match register 16MHz/256/2Hz
  TCCR2A |= (1 << WGM21);   // CTC mode
  TCCR2B |= (1 << CS22) | (0 << CS21) | (1 << CS20);    // 1024 prescaler 
  TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER2_COMPA_vect) {
  noInterrupts();
  
  lastDelta = millis() - lastMillis;
  lastMillis = millis();

  interrupts();
}

void loop() {
  Serial.printf("Last isr's were %d ms apart\n", lastDelta);
  Serial.printf("Read: %d\n", TCNT2);
  delay(1000);
}
