#define OUT 9
#define POT 3 // analog 3

unsigned long lastClick;

unsigned int generateNoise();

void setup() {
  pinMode(OUT, OUTPUT);

  lastClick = micros();
}

#define FREQ ((unsigned int) analogRead(POT))
void loop() {
  //if ((micros() - lastClick) > FREQ) { // Changing this value changes the frequency.
    //lastClick = micros();
    digitalWrite (OUT, generateNoise());
  //}
}

// see https://arduino.stackexchange.com/a/18092
#define LFSR_INIT  0xfeedfaceUL
#define LFSR_MASK  ((unsigned long) ( 1UL<<31 | 1UL <<15 | 1UL <<2 | 1UL <<1  ))
unsigned int generateNoise() { 
  static unsigned long int lfsr = LFSR_INIT;  /* 32 bit init, nonzero */
  if(lfsr & 1) {
    lfsr = (lfsr >>1) ^ LFSR_MASK;
    return(1);
  } else {
    lfsr >>= 1;
    return(0);
  }
}
