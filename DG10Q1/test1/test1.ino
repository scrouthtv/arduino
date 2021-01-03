#include "1.0_VFD-Driver_PCA9505_include.h"
#include <Wire.h>

#define DeviceAddress 0b0100000

//           BPACGDFE
byte one = 0b10011011;
byte two = 0b10111011;
byte thr = 0b00000111;
byte fur = 0b11110111;

void setup() {
  // init I2C
  Wire.begin();

  // init PCA9505
  InitPCA950x();
  PCA950x_Write(OP3, 0b0); // grid at 3.0
  PCA950x_Write(OP4, ~0); // data from 4.0 thru 4.8
}

void loop() {
  // put your main code here, to run repeatedly:
  PCA950x_Write(OP4, ~one); // data from 4.0 thru 4.8
  delay(1000);
  PCA950x_Write(OP4, ~0); // data from 4.0 thru 4.8
  delay(100);
  PCA950x_Write(OP4, ~two); // data from 4.0 thru 4.8
  delay(1000);
  PCA950x_Write(OP4, ~0); // data from 4.0 thru 4.8
  delay(100);
  PCA950x_Write(OP4, ~thr); // data from 4.0 thru 4.8
  delay(1000);
  PCA950x_Write(OP4, ~0); // data from 4.0 thru 4.8
  delay(100);
  PCA950x_Write(OP4, ~thr); // data from 4.0 thru 4.8
  delay(1000);
  PCA950x_Write(OP4, ~0); // data from 4.0 thru 4.8
  delay(100);
  PCA950x_Write(OP4, ~fur); // data from 4.0 thru 4.8
  delay(1000);
  PCA950x_Write(OP4, ~0); // data from 4.0 thru 4.8
  delay(100);
}
