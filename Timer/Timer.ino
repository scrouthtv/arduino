#define AN1  11 // LCD pin 12 on PB3 (D11)
#define AN2  10 // LCD pin  9 on PB2 (D10)
#define AN3   4 // LCD pin  8 on PD4 (D4)
#define AN4   3 // LCD pin  6 on PD3 (D3)

#define CTA   9 // LCD pin 11 on PB1 (D9)
#define CTB  A1 // LCD pin  8 on PC1 (A1)
#define CTC   8 // LCD pin  4 on PB0 (D8)
#define CTD   6 // LCD pin  2 on PD6 (D6)
#define CTE   5 // LCD pin  1 on PD5 (D5)
#define CTF  A0 // LCD pin  7 on PC0 (A0)
#define CTG   2 // LCD pin  5 on PD2 (D2)
#define CTP   7 // LCD pin  3 on PD7 (D7)

#define BT1  13 // Left button on PB5
#define BT2  12 // Right button on PB4

#define POT   2 // potentiometer on PC2 (A2)

byte one = 0b11110010;
byte two = 0b11100000;
byte thr = 0b11111110;
byte fur = 0b10111010;

void flashDisplay() {
  Serial.println("Hello");
}

void setup() {
  Serial.begin(9600);

  cli(); // stop interrupts
  
  // http://sculland.com/ATmega168/Interrupts-And-Timers/Show-All/
  // Timer 0 and 2 have 8 bits so they can only count up to 255
  // and the output compare register has to be < 255

  TCCR1A = 0; // clear control register
  TCCR1B = 0; // clear control register
  TCNT1 = 0; // intialize counter to 0

  // "output compare register" compare match register
  OCR1A = 15; // must be <255 for 0 & 2 or 65535 for 1
  // 15624 = (16*10^6 Hz) / (1 Hz * 1024 prescaler) - 1
  // 15 = (16*10^6) / (1000 Hz * 1024 prescaler) - 1
  
  //              clock speed (16 MHz)
  // ----------------------------------------------
  //  (prescaler * wanted interrupt frequency) - 1
  
  TCCR1B |= (1 << WGM12); // CTC (clear timer on compare) mode
  // WGM01 or WGM21 is WGM12 on Timer 1

  TCCR1B |= (1 << CS10) | (1 << CS12); // 1024 prescaler
  TIMSK1 |= (1 << OCIE1A); // callback interrupt when compare match occurs

  sei(); // allow interrupts
}

/**
 * Callback for Timer 0
 */
ISR(TIMER1_COMPA_vect) {
  Serial.print(OCR1A);
  Serial.print(", speed is ");
  Serial.println(analogRead(POT));
}

void loop() {
  cli();
             // 16  MHz  prescaler   speed  zero-indexed cmr
  int clock = (16000000) / (1024   * analogRead(POT)) - 1;
  if (clock > 65535) clock = 65535;
  if (clock < 1) clock = 1;
  Serial.println(clock);
  OCR1A = clock;
  sei();
}
