
#include "VFD-Driver_PCA9505_include.h"
#include "CharacterMap.h"
#include <Wire.h>

#define DEBUG
#define UseDelay

//#define DeviceAddress 0x21

#define MultiplexDelay 100
int counter = 0;
int data[9] = {0,1,2,3,4,5,6,7,8};
long timer = 0;
int multiplexDelay = MultiplexDelay;

void setup()//#######################################################################################################################################################
{
  //pinMode(A1, INPUT);
  //Serial.begin(9600);
  //initialize I2C Library
  Wire.begin();
  //initialize PCA9505
  InitPCA950x();
  PCA950x_Write(OP0, 0b00000000);
  PCA950x_Write(OP1, 0b00000000);
  PCA950x_Write(OP2, 0b00000000);
  //timer = millis();
}

void loop()//#######################################################################################################################################################
{
  PCA950x_Write(OP0, 0b00000001);
  PCA950x_Write(OP1, 0b00000001);
  delay(1000);
  PCA950x_Write(OP0, 0b00000010);
  PCA950x_Write(OP1, 0b00000010);
  delay(1000);
  PCA950x_Write(OP0, 0b00000100);
  PCA950x_Write(OP1, 0b00000100);
  delay(1000);
  PCA950x_Write(OP0, 0b00001000);
  PCA950x_Write(OP1, 0b00001000);
  delay(1000);
  PCA950x_Write(OP0, 0b00010000);
  PCA950x_Write(OP1, 0b00010000);
  delay(1000);
  PCA950x_Write(OP0, 0b00100000);
  PCA950x_Write(OP1, 0b00100000);
  delay(1000);
  PCA950x_Write(OP0, 0b01000000);
  PCA950x_Write(OP1, 0b01000000);
  delay(1000);
  PCA950x_Write(OP0, 0b10000000);
  PCA950x_Write(OP1, 0b10000000);
  delay(1000);
  PCA950x_Write(OP0, 0b00000000);
  PCA950x_Write(OP1, 0b00000000);
  PCA950x_Write(OP2, 0b00000101);
  delay(1000);
  PCA950x_Write(OP2, 0b00001010);
  delay(1000);
  PCA950x_Write(OP2, 0b00000000);

  /*PCA950x_Write(OP0, 0b11111111);
  PCA950x_Write(OP1, 0b11111111);
  PCA950x_Write(OP2, 0b11111111);
  PCA950x_Write(OP3, 0b11111111);
  PCA950x_Write(OP4, 0b11111111);
  delay(1000);
  PCA950x_Write(OP0, 0b00000000);
  PCA950x_Write(OP1, 0b00000000);
  PCA950x_Write(OP2, 0b00000000);
  PCA950x_Write(OP3, 0b00000000);
  PCA950x_Write(OP4, 0b00000000);
  delay(1000);*/


  
  //Multiplexing example
  /*/clear segments
  PCA950x_Write(OP0, 0b11111111);
  //switch grid
  PCA950x_Write(OP1, LD8161_Grids_pinMap[counter]);
  //write segments
  PCA950x_Write(OP0, LD8161_charMap[data[counter]]);

  counter++;
  if(counter > 7)
  {
    counter = 0;
  }*/
  /*if(millis() > (timer + 500))
  {
    timer = millis();
    for(int i = 0; i > 9; i++)
    {
      data[i] = data[i] + 1;
      if(data[i] > 9)
      {
        data[i] = 0;
      }
    }
  }*/

  /*#ifdef UseDelay
    multiplexDelay = map(analogRead(A1), 0, 1023, 0, 200);
    //delay(MultiplexDelay);
    delay(multiplexDelay);
  #endif

  #ifdef DEBUG
    Serial.println(analogRead(A1));
    //Serial.println(timer);
    Serial.println();
  #endif*/
}
