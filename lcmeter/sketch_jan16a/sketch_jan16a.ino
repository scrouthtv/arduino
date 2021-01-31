

void setup() {
  Serial.begin(9600);
  noInterrupts(); // Arduino.h: noInterrupts() = cli()

    TCCR1A = 0;
    TCCR1B = 0 | (1 << ICES1) | (1 << CS12) | (1 << CS11) | (1 << CS10);
    TCCR1C = 0;
    // alternatively: use FOC to compare

  // COM1A1 = 0, COM1A0 = 0 => no output
  // WGM10 = 0, WGM11 = 0 => timer/counter 1 as timer/counter

  // TCRB1:
  // 7. ICNC1 = 0 => no noise cancelling
  // 6. ICES1 = 1 => rising edge
  // 5. n. c.
  // 4. WGM13 = 0 => timer/counter 1 as timer/counter
  // 3. WGM12 = 0 =>  - " -
  // 2. CS12 = 1 // use T1
  // 1. CS11 = 1 // as timer 
  // 0. CS10 = 1 // input

  // === measure the time with timer 2 ===
  TCCR2A = (1 << WGM21); // ctc
  OCR2A = 64-1;
  TCCR2B = (0 << CS22) | (1 << CS21) | (0 << CS20);
  //TIMSK2 |= (1 << TOIE2); // isr on overflow
  TIMSK2 |= (1 << OCIE2A);

  interrupts();
}

volatile double freq = 0;
volatile uint16_t count = 0;

void loop() {
  noInterrupts();
  Serial.print("Got ");
  //Serial.print(freq);
  Serial.println(" kHz");
  interrupts();
  //Serial.println(freq);
  //Serial.println(count);
  delay(1000);
}

// isr on timer 2, gets called every 32 us
ISR(TIMER2_COMPA_vect) {
  noInterrupts();
  
  count = TCNT1;
  freq = count / 0.032;
  TCNT1 = 0;

  interrupts();
}
