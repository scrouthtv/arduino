/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/


#define TMP 2 // LM335Z on PC2 (analog 2)

// include the library code:
#include <LiquidCrystal.h>

#include <math.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
// d4..d7 connected to PB4..PB1 (digital 12..9)
// RS connected to PB5 (digital 13)
// EN connected to PD4 (digital 4)
const int rs = 13, en = 4, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
const int d0 = 8, d1 = 7, d2 = 6, d3 = 5;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);

double last = -1;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  Serial.begin(9600);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  double orig = temparature(analogRead(TMP));
  Serial.print("rounding ");
  Serial.print(orig);
  Serial.print(" to ");
  double temp = round(orig * 10.0) / 10.0;
  Serial.println(temp);
  Serial.println(orig * 10.0);
  if (temp != last) {
    lcd.setCursor(3, 1);
    lcd.print(temp);
    lcd.print(" ");
    lcd.print((char) 0b11011111);
    lcd.print("C");
    last = temp;
  }
  delay(10);
}

double temparature(int analog) {
  double volts = 5.0 * analog / 1023.0;
  //Serial.println(volts);
  return 25 + ((volts - 2.98) / .01);
}
