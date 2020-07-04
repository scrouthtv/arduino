#include <math.h>

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

#define CT 3200 // cycle time for brightness

#define BRG   3 // photo resistor on PC3 (A3)
// this setup: +5V - LDR07 - 5kOhm - 0V
// results in voltages ranging from
// 20 (in literal darkness) to
// 800 (shining at the sensor with a lamp)

byte one = 0b10101010; // the leftmost digit
byte two = 0b01010101;
byte thr = 0b11001100;
byte fur = 0b00110011; // the rightmost digit

int nthdigit(const int number, const int digit); 

void setup() {
  int outputs[] = {AN1, AN2, AN3, AN4, CTA, CTB, CTC, CTD, CTE, CTF, CTG, CTP};
  for (int i : outputs)
    pinMode(i, OUTPUT);
  int inputs[] = {BT1, BT2};
  for (int i : inputs)
    pinMode(i, INPUT);

  digitalWrite(CTA, LOW);
  analogWrite(CTB, LOW);
  digitalWrite(CTC, LOW);
  digitalWrite(CTD, LOW);
  digitalWrite(CTE, LOW);
  analogWrite(CTF, LOW);
  digitalWrite(CTG, LOW);
  digitalWrite(CTP, LOW);

  digitalWrite(AN1, HIGH);
  digitalWrite(AN2, HIGH);
  digitalWrite(AN3, HIGH);
  digitalWrite(AN4, HIGH);
  
  //randomSeed(analogRead(5));

  one = displayDigit(8) | 0b1;
  two = displayDigit(2);
  thr = displayDigit(4);
  fur = displayDigit(9);

  //Serial.begin(9600);
}

void loop() {  
  digitalWrite(AN1, LOW);
  //digitalWrite(AN2, HIGH);
  //digitalWrite(AN3, HIGH);
  //digitalWrite(AN4, HIGH);
  illuminateCathodes(one);
  delayMicroseconds(brightDelay());
  digitalWrite(AN1, HIGH);
  delayMicroseconds(darkDelay());
  
  //digitalWrite(AN1, HIGH);
  digitalWrite(AN2, LOW);
  //digitalWrite(AN3, HIGH);
  //digitalWrite(AN4, HIGH);
  illuminateCathodes(two);
  delayMicroseconds(brightDelay());
  digitalWrite(AN2, HIGH);
  delayMicroseconds(darkDelay());
  
  //digitalWrite(AN1, HIGH);
  //digitalWrite(AN2, HIGH);
  digitalWrite(AN3, LOW);
  //digitalWrite(AN4, HIGH);
  illuminateCathodes(thr);
  delayMicroseconds(brightDelay());
  digitalWrite(AN3, HIGH);
  delayMicroseconds(darkDelay());
  
  //digitalWrite(AN1, HIGH);
  //digitalWrite(AN2, HIGH);
  //digitalWrite(AN3, HIGH);
  digitalWrite(AN4, LOW);
  illuminateCathodes(fur);
  delayMicroseconds(brightDelay());
  digitalWrite(AN4, HIGH);
  delayMicroseconds(darkDelay());
}

int brightness() {
  int brightness = analogRead(BRG);
  if (brightness < 3) return 3;
  if (brightness > 799) return 799;
  return brightness;
}

/**
 * Returns microseconds
 */
int brightDelay() {
  return ((4 * brightness()) % CT);
}

/**
 * Returns microseconds
 */
int darkDelay() {
  return CT - ((4 * brightness()) % CT);
}

int delay() {
  const int delay = analogRead(POT);
  if (delay < 1) return 1;
  else return delay;
}

byte displayDigit(int digit) {
  // 0bABCDEFGP
  //  A
  // F B
  //  G
  // E C
  //  D P
  switch (digit) {
                         // v notice how the last bit is always 0. its the dot.
                   //ABCDEFGP
    case 0: return 0b11111100;
    case 1: return 0b01100000;
    case 2: return 0b11011010;
    case 3: return 0b11110010;
    case 4: return 0b01100110;
    case 5: return 0b10110110;
    case 6: return 0b10111110;
    case 7: return 0b11100000;
    case 8: return 0b11111110;
    case 9: return 0b11110110;
    default: return 0;
  }
}

void illuminateCathodes(byte b) {
  digitalWrite(CTA, (b & 0b10000000) == 0);
  digitalWrite(CTB, (b & 0b01000000) == 0);
  digitalWrite(CTC, (b & 0b00100000) == 0);
  digitalWrite(CTD, (b & 0b00010000) == 0);
  digitalWrite(CTE, (b & 0b00001000) == 0);
  digitalWrite(CTF, (b & 0b00000100) == 0);
  digitalWrite(CTG, (b & 0b00000010) == 0);
  digitalWrite(CTP, (b & 0b00000001) == 0);
}

/**
 * RTL. e. g. nth(5678, 1) would be 8 while nth(5678, 4) would be 5.
 */
int nthdigit(const int number, const int digit) {
  return (number / (int) pow(10, digit)) % 10;
}
