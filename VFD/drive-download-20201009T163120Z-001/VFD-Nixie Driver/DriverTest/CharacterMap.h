#ifndef CharakterMap_h
#define CharakterMap_h

byte portData[6] = {0,0,0,0,0,0};     //item at location 5 is used for ignored adresses

//NEC_LD8161_VFD-Tube//#######################################################################################################################################################

#define LD8161_Grids 9
#define LD8161_GridsPortA 1
#define LD8161_GridsPortB 2        //only needed if total pins exceed 8; 6 will be ignored
#define LD8161_GridsPortC 6        //only needed if total pins exceed 8; 6 will be ignored
#define LD8161_GridsPortD 6        //only needed if total pins exceed 8; 6 will be ignored
#define LD8161_GridsTotalPorts 2

#define LD8161_Segments 8
#define LD8161_SegmentsPortA 0
#define LD8161_SegmentsPortB 6        //only needed if total pins exceed 8; 6 will be ignored
#define LD8161_SegmentsPortC 6        //only needed if total pins exceed 8; 6 will be ignored
#define LD8161_SegmentsPortD 6        //only needed if total pins exceed 8; 6 will be ignored
#define LD8161_SegmentsTotalPorts 1

const byte LD8161_Grids_pinMap[LD8161_Grids]
{
  //PortA
  0b11111110,
  0b11111101,
  0b11111011,
  0b11110111,
  0b11101111,
  0b11011111,
  0b10111111,
  0b01111111,
  //PortB
  0b11111110
};



const byte LD8161_charMap[10]
{
  0b10000100,
  0b11101101,
  0b10011000,
  0b10101000,
  0b11100001,
  0b10100010,
  0b10000010,
  0b11101100,
  0b10000000,
  0b10100000
};

/*  0b 0 0 0 0 0 0 0 0
 *     7 6 5 4 3 2 1 0
 * 
 *         ||
 *         \/
 *          
 *        +-0-+
 *        3   1
 *        +-2-+
 *        5   4
 *        +-6-+  7
 */



#endif
