const double referenceValue = 720; // pF
double referenceTicks = 0;
volatile uint64_t count = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");

  cli();
  
  TCCR1A = 0;
  TCCR1B = (0 << ICES1) | (1 << CS12) | (1 << CS11) | (1 << CS10);
  TCCR1C = 0;

  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS22) | (0 << CS21) | (1 << CS20);
  TIMSK2 = (1 << OCIE2A);
  OCR2A = 256-1;

  sei();

  // initialize reference to the first value:
  delay(10);
  referenceTicks = count;
}

void loop() {
  delay(500);
  const double myC = referenceValue * (pow(referenceTicks, 2) / pow(count, 2) - 1);
  if (myC < -100) {
    Serial.println("very negative value, reset reference value");
    referenceTicks = count;
  } else {
    Serial.print(myC);
    Serial.println(" pF"); 
  }
}

ISR(TIMER2_COMPA_vect) {
  count = TCNT1;
  TCNT1 = 0;
}
