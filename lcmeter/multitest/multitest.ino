class Prescaler {
  public:
    byte CS2, CS1, CS0;
    double ms;
    Prescaler(byte CS2, byte CS1, byte CS0, double ms) {
      this->CS2 = CS2;
      this->CS1 = CS1;
      this->CS0 = CS0;
      this->ms = ms;
    }
};

volatile uint16_t count = 0;

void setup() {
  Serial.begin(9600);

  cli();
  
  TCCR1A = 0;
  TCCR1B = (0 << ICES1) | (1 << CS12) | (1 << CS11) | (1 << CS10);
  TCCR1C = 0;

  TCCR2A = (1 << WGM21);
  TIMSK2 = (1 << OCIE2A);
  OCR2A = 64-1;

  sei();
}

Prescaler* pcs[] = {
  new Prescaler(0, 0, 1, 0.004),
  new Prescaler(0, 1, 0, 0.032),
  new Prescaler(0, 1, 1, 0.256),
  new Prescaler(1, 0, 0, 1.024),
  new Prescaler(1, 0, 1, 4.096),
};

void loop() {
  delay(1000);
  double freq;
  uint16_t mycount;
  Serial.println("---");
  for (Prescaler* pcr : pcs) {
    TCCR2B = (pcr->CS2 << CS22) | (pcr->CS1 << CS21) | (pcr->CS0 << CS20);
    delay(10);
    mycount = count;
    freq = (double) mycount / (pcr->ms);
    Serial.print("# ");
    Serial.print(mycount);
    Serial.print("   ");  
    Serial.print(freq);
    Serial.println(" kHz");
  }
  delay(1000);
}

ISR(TIMER2_COMPA_vect) {
  count = TCNT1;
  TCNT1 = 0;
}
