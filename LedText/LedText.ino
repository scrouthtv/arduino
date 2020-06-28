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

#define SPACING 1 // spacing between repeating text

int DELAY = 4; // in ms
int SPEED = 100; // time in ms to switch to the next part

byte one = 0b10101010; // the leftmost digit
byte two = 0b01010101;
byte thr = 0b11001100;
byte fur = 0b00110011; // the rightmost digit

long counter = 0;
int pos = 0;

String text = "Hallo 2020. Fritz jagt im komplett verwahrlosten Taxi quer durch Bayern."; 
//String text = "YyYy"; // doesnt work when text is too small
//String text = "Hallo 2020";

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

  Serial.begin(9600);
  randomSeed(analogRead(5));

  one = displayDigit(8);
  two = displayDigit(8);
  thr = displayDigit(8);
  fur = displayDigit(8);
}

void loop() {
  if ((counter % (SPEED/DELAY)) == 0) {
    pos++;
    pos = pos % (text.length() + 3);

    one = displayDigit(text[(pos + 0) % (text.length() + SPACING)]);
    two = displayDigit(text[(pos + 1) % (text.length() + SPACING)]);
    thr = displayDigit(text[(pos + 2) % (text.length() + SPACING)]);
    fur = displayDigit(text[(pos + 3) % (text.length() + SPACING)]);
  }
  
  digitalWrite(AN1, LOW);
  digitalWrite(AN2, HIGH);
  digitalWrite(AN3, HIGH);
  digitalWrite(AN4, HIGH);
  illuminateCathodes(one);
  delay(DELAY);
  digitalWrite(AN1, HIGH);
  digitalWrite(AN2, LOW);
  digitalWrite(AN3, HIGH);
  digitalWrite(AN4, HIGH);
  illuminateCathodes(two);
  delay(DELAY);
  digitalWrite(AN1, HIGH);
  digitalWrite(AN2, HIGH);
  digitalWrite(AN3, LOW);
  digitalWrite(AN4, HIGH);
  illuminateCathodes(thr);
  delay(DELAY);
  digitalWrite(AN1, HIGH);
  digitalWrite(AN2, HIGH);
  digitalWrite(AN3, HIGH);
  digitalWrite(AN4, LOW);
  illuminateCathodes(fur);
  delay(DELAY);

  if (digitalRead(BT1) == HIGH) {
    DELAY *= 2;
    Serial.print("Button was pressed, delay is now ");
    Serial.println(DELAY);
  }
  if (digitalRead(BT2) == HIGH) {
    DELAY /= 2;
  }
  
  counter++;
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

byte displayDigit(char digit) {
  if (digit >= (int) '0' && digit <= (int) '9')
    return displayDigit(((int) digit) - '0');
  switch (digit) {
    case 'a':
    case 'A': return 0b11101110;
    case 'b': return 0b00111110;
    case 'B': return 0b00111110;
    case 'c': return 0b00011010;
    case 'C': return 0b10011100;
    case 'd': 
    case 'D': return 0b01111010;
    case 'e':
    case 'E': return 0b10011110;
    case 'f':
    case 'F': return 0b10001110;
    case 'g':
    case 'G': return 0b10111100;
    case 'h': return 0b00101110;
    case 'H': return 0b01101110;
    case 'i':
    case 'I': return 0b00001100;
    case 'j':
    case 'J': return 0b01110000;
    case 'k':
    case 'K': return 0; // no nice picture for K
    case 'l':
    case 'L': return 0b00011100;
    case 'm':
    case 'M': return 0; // no nice picture for M
    case 'n':
    case 'N': return 0b00101010; // lowercase n
    case 'o': return 0b00111010;
    case 'O': return 0b11111100;
    case 'p':
    case 'P': return 0b11001110;
    case 'q':
    case 'Q': return 0b11100110;
    case 'r':
    case 'R': return 0b00001010;
    case 's':
    case 'S': return 0b10110110; // same as 5
    case 't':
    case 'T': return 0b00011110; // lowercase t
    case 'u': return 0b00111000;
    case 'U': return 0b01111100;
    case 'v': return 0b00111000;
    case 'V': return 0b01111100; // same as u
    case 'w':
    case 'W': return 0; // no nice picture for W
    case 'x':
    case 'X': return 0; // no nice picture for X
    case 'y': return 0b01100110;
    case 'Y': return 0b01110110;
    case 'z':
    case 'Z': return 0b11011010; // same as 2
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
