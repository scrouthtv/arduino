#ifndef V1_VFD-Driver_PCA9505_inlude_h
#define V1_VFD-Driver_PCA9505_inlude_h
//#######################################################################################################################################################
/*
 *                             /---5V                                   /---9V+
 *                             |                    /--------\          |
 * /---------------\           |          /--------/ A1 A2 A3 \--\      |
 * |           VCC o-----------o----------o Vl                 Vd o-----/
 * |               |                      |                       |
 * | Arduino   SCL o----------------------o SCL    VFD_Driver     |
 * |           SDA o----------------------o SDA                   |
 * |               |                      |              Ports0-4 =------// -> Display Grids and Segments
 * |           GND o---GND          GND---o GND                   |
 * \---------------/                      \-----------------------/
 * 
 *   no additional pullups needed
 *
 *  >> tsamsiyu.yt@gmail.com <<
 */

      //DeviceAddress 0b0100 A2 A1 A0
#ifndef DeviceAddress
  #define DeviceAddress 0b0100000
#endif

//See datasheet for more detailed info
//Available Registers (each 5*8bits)
// IP  Input Port                   read only
// OP  OututPort                    state reflects value
// PI  Input Polarity Inversion     0 = not inverted
// IOC Input/Output Configuration   0 = output
// MSK Mask Interrupt               0 = interrupt

//CommandRegister 0b AI 0 D5 D4 D3 D2 D1 D0
                     //AutoIncrement Flag 
                     #define AIFlag 0x80
                          //Port to be accessed
                          //Input-Registers
                          #define IP0    0x00
                          #define IP1    0x01
                          #define IP2    0x02
                          #define IP3    0x03
                          #define IP4    0x04
                          //(IP 0x05,0x06,0x07 reserved for future use)
                          //Output-Registers
                          #define OP0    0x08
                          #define OP1    0x09
                          #define OP2    0x0A
                          #define OP3    0x0B
                          #define OP4    0x0C
                          //(OP 0x0D,0x0E,0x0f reserved for future use)
                          //Polarity Inversion registers
                          #define PI0    0x10
                          #define PI1    0x11
                          #define PI2    0x12
                          #define PI3    0x13
                          #define PI4    0x14
                          //(PI 0x15,0x16,0x17 reserved for future use)
                          //IO Configuration registers
                          #define IOC0    0x18
                          #define IOC1    0x19
                          #define IOC2    0x1A
                          #define IOC3    0x1B
                          #define IOC4    0x1C
                          //(IOC 0x0D,0x0E,0x0f reserved for future use)
                          //masked inerrupt registers
                          #define MSK0    0x20
                          #define MSK1    0x21
                          #define MSK2    0x22
                          #define MSK3    0x23
                          #define MSK4    0x24
                          //(MSK 0x25,0x26,0x27 reserved for future use)

#include <Wire.h>

 const byte PCA950xConfig[4][5]
{
  //OP
  {
    /*0b00000000*/0x00,
    /*0b00000000*/0x00,
    /*0b00000000*/0x00,
    /*0b00000000*/0x00,
    /*0b00000000*/0x00
  },
  //PI
  {
    /*0b00000000*/0x00,
    /*0b00000000*/0x00,
    /*0b00000000*/0x00,
    /*0b00000000*/0x00,
    /*0b00000000*/0x00
  },
  //IOC
  {
    /*0b00000000*/0x00,
    /*0b00000000*/0x00,
    /*0b00000000*/0x00,
    /*0b00000000*/0x00,
    /*0b00000000*/0x00
  },
  //MSK
  {
    /*0b11111111*/0xff,
    /*0b11111111*/0xff,
    /*0b11111111*/0xff,
    /*0b11111111*/0xff,
    /*0b11111111*/0xff
  }
};

void InitPCA950x(/*reads setup from Array in PROGMEM: change if desired*/)//#######################################################################################################################################################
{
  //Wire.begin();
  
//InputRegisters//--------------------------------------------------------------------------------

  //no config needed, read only

//OutputRegisters//--------------------------------------------------------------------------------

  //begin communication with device
  Wire.beginTransmission(DeviceAddress);
  
  //CommandCode for wanted register with auto increment 
  Wire.write(OP0 | AIFlag);

  //write port data
  for(int i = 0; i < 5; i++)
  {
    Wire.write(PCA950xConfig[0][i]);
  }
  //terminate communication
  Wire.endTransmission(true);

//PolarityRegisters//--------------------------------------------------------------------------------

  //begin communication with device
  Wire.beginTransmission(DeviceAddress);
  
  //CommandCode for wanted register with auto increment 
  Wire.write(PI0 | AIFlag);

  //write port data
  for(int i = 0; i < 5; i++)
  {
    Wire.write(PCA950xConfig[1][i]);
  }
  //terminate communication
  Wire.endTransmission(true);

//DataDirectionRegister//--------------------------------------------------------------------------------

  //begin communication with device
  Wire.beginTransmission(DeviceAddress);
  
  //CommandCode for wanted register with auto increment 
  Wire.write(IOC0 | AIFlag);

  //write port data
  for(int i = 0; i < 5; i++)
  {
    Wire.write(PCA950xConfig[2][i]);
  }
  //terminate communication
  Wire.endTransmission(true);

//InterruptMaskRegister//--------------------------------------------------------------------------------

  //begin communication with device
  Wire.beginTransmission(DeviceAddress);
  
  //CommandCode for wanted register with auto increment 
  Wire.write(MSK0 | AIFlag);

  //write port data
  for(int i = 0; i < 5; i++)
  {
    Wire.write(PCA950xConfig[3][i]);
  }
  //terminate communication
  Wire.endTransmission(true);
  
}



void PCA950x_Write(byte PCARegister, byte data)//#######################################################################################################################################################
{
  //begin communication with device
  Wire.beginTransmission(DeviceAddress);
  //desired register
  Wire.write(PCARegister);
  //write data
  Wire.write(data);
  //terminate communication
  Wire.endTransmission(true);
}

void PCA950x_WriteOP(byte data[5])//#######################################################################################################################################################
{
  //begin communication with device
  Wire.beginTransmission(DeviceAddress);
  //start at the first
  Wire.write(OP0 | AIFlag);

  //write all data
  for(int i = 0; i < 5; i++)
  {
    Wire.write(data[i]);
  }

  //terminate communication
  Wire.endTransmission(true);
}




#endif
