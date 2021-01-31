volatile unsigned long lastMicros = 0;
volatile unsigned long lastDelta = 0;

#define LED 8

// If you change the prescale value, it affects CS22, CS21, and CS20
// For a given prescale value, the eight-bit number that you
// load into OCR2A determines the frequency according to the
// following formulas:
// Note that, due to the time spent in the ISR, it's not practical to generate
// a waveform with period much less than 20 microseconds.  You can speed it up
// a little by using bit manipulation on the output port instead of digitalWrite.
//
// Better yet: Enable "Toggle Output on Compare Match" and don't do any port
// reading or writing in the ISR.  For this scheme, uou will have to use an
// Output Compare pin on the ATmega instead of an arbitrary output pin.
//

// The following are scaled for convenient printing
//
// Interrupt interval in microseconds
// iinterval = prescale * (ocr2aval + 1) / (F_CPU / 1.0e6);

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  
  // I like to disable global interrupts while initializing counter registers.
  // That may not be necessary, but...
  cli();

  TCCR1A = 0;
  TCCR1B = (1 << ICES1) | (1 << CS12) | (1 << CS11) | (1 << CS10);
  TCCR1C = 0;

  // Set Timer 2 CTC mode and prescale by 64
  //
  // WGM22:0 = 010: CTC Mode
  // WGM2 bits 1 and 0 are in TCCR2A,
  // WGM2 bit 2 is in TCCR2B
  //
  TCCR2A = (1 << WGM21);

  // Set Timer 2  No prescaling
  //
  // CS22:0 = 101: prescale = 1024
  // CS2 bits 2:0 are all in TCCR2B
  TCCR2B = (1 << CS22) | (0 << CS21) | (1 << CS20);
  // 210 CS with OCR 64-1                       I am expecting 337.71 kHz
  // 001 => clock/1    =>  250  kHz ~ 0.004 ms got   1 tick
  // 010 => clock/8    => 31.25 kHz ~ 0.032 ms got  10 ticks -> 343.75 kHz
  // 011 => clock/64   =>  3.91 kHz ~ 0.256 ms got  43 ticks -> 167.97 kHz
  // 100 => clock/256  =>  977   Hz ~ 1.024 ms got  86 ticks ->  83.98 kHz
  // 101 => clock/1024 =>  244   Hz ~ 4.096 ms got 155 ticks ->  37.84 kHz
  
  // Enable Compare-match register A interrupt for timer2
  TIMSK2 = (1 << OCIE2A);

  // This value determines the interrupt interval
  OCR2A = 64-1;

  // Enable global interrupts: Ready to run!
  sei();

}

volatile uint16_t count = 0;

void loop() {
  delay(1000);
  //Serial.printf("Last isr's were %d us apart\n", lastDelta);
  //Serial.print("Got:");
  //Serial.print(count);
  //Serial.println(" Hz");
  
  // freq [kHz] = ticks [Hz]/1.024 ms
  //double freq = count / 1.024;
  Serial.println(count);
  //Serial.println(freq);
}

// ISR For Timer 2 Compare-match overflow
volatile unsigned char value = 0;
volatile bool state = true;
ISR(TIMER2_COMPA_vect) {
  
  /*if (state) state = false;
  else return;*/

  count = TCNT1;
  TCNT1 = 0;

  /*Serial.println(count);
  Serial.println("Hello");*/

}
