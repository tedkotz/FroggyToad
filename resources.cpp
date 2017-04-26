
#include "resources.h"
#include "soundserver.h"

//12345678
//   #      
//# ### #
//## # ## 
// #####  
// ##### 
//#######
//#     #
// 7x7       
const byte frogLtImg[] PROGMEM = {
  B00010000, 
  B10111010, 
  B11010110, 
  B01111100, 
  B01111100, 
  B11111110, 
  B10000010, 
};

const byte frogRtImg[] PROGMEM = {
  B10000010, 
  B11111110, 
  B01111100, 
  B01111100, 
  B11010110, 
  B10111010, 
  B00010000, 
};

const byte frogDnImg[] PROGMEM = {
  B01100110, 
  B00111100, 
  B01011100, 
  B11111100, 
  B01011100, 
  B00111100, 
  B01100110, 
};

const byte frogUpImg[] PROGMEM = {
  B11001100, 
  B01111000, 
  B01110100, 
  B01111110, 
  B01110100, 
  B01111000, 
  B11001100, 
};

/*const byte starImg[] PROGMEM = {
  B10001000, 
  B01010000, 
  B00110000, 
  B00111110, 
  B00110000, 
  B01010000, 
  B10001000, 
};*/


const byte starImg[] PROGMEM = {
  B10010010, 
  B01010100, 
  B00111000, 
  B11111110, 
  B00111000, 
  B01010100, 
  B10010010, 
};

const byte bugImg[] PROGMEM = {
  B11011100, 
  B01111000, 
  B00110010, 
  B11111100, 
  B00110010, 
  B01111000, 
  B11011100, 
};

/*
const byte lillypadImg[] PROGMEM = {
  B00111000, 
  B01000100, 
  B10000010, 
  B10010010, 
  B10001010, 
  B01000100, 
  B00111000, 
};
*
*
 */
const byte lillypadImg[] PROGMEM = {
  B00111000, 
  B01111100, 
  B11111110, 
  B11101110, 
  B11110110, 
  B01111000, 
  B00111000, 
};


//12345678
//  ###
// #   # 
//#  #  #
//# # # #
//#  #  #
//##   ##
//# ### #
//#     #
// 24x8
const byte logImg[] PROGMEM = {
  B00111100, 
  B01000010, 
  B10011001, 
  B10100101,
  B10011001, 
  B11000011, 
  B10111101, 
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B01000010, 
  B00111100, 
};

//12345678
//#    
//#      
// #     
//  #    
//  ###  
// ##    
//#      
// 8x5       
const byte rippleImg[] PROGMEM = {
  B10000000, 
  B10000000, 
  B01000000, 
  B00100000, 
  B00011000, 
  B01110000, 
  B11000000, 
  B10000000, 
};


// 10x8
const byte carImg[] PROGMEM = {
  B01111100, 
  B11111110, 
  B11000110, 
  B11111110,
  B01111100, 
  B01111100, 
  B11111110, 
  B11000110,
  B11111110,
  B01111100,
};

//  ###
//# ### #
//#######
//# # # # 
//  # # 
//# # # #
//#######
//# ### #
// 8x8
const byte roadsterLtImg[] PROGMEM = {
  B00111000, 
  B10111010, 
  B11111110, 
  B10101010,
  B00101000, 
  B10101010, 
  B11111110, 
  B10111010,
};

const byte roadsterRtImg[] PROGMEM = {
  B10111010, 
  B11111110, 
  B10101010,
  B00101000, 
  B10101010, 
  B11111110, 
  B10111010,
  B00111000, 
};

// 24x8
const byte truckLtImg[] PROGMEM = {
  B01111100, 
  B01111100, 
  B11000110, 
  B11111110, 
  B11111110, 
  B01111100, 
  B00111000,
  B00111000, 
  B11111110, 
  B11111110,
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110,
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110,
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110,
};

// 24x8
const byte truckRtImg[] PROGMEM = {
  B11111110, 
  B11111110,
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110,
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110,
  B11111110, 
  B11111110, 
  B11111110, 
  B11111110,
  B00111000,
  B00111000, 
  B01111100, 
  B11111110, 
  B11111110, 
  B11000110, 
  B01111100, 
  B01111100, 
};

// 10x8
const byte tractorLtImg[] PROGMEM = {
  B11111110,
  B00101000, 
  B00101000, 
  B10111010, 
  B11111110, 
  B11111110,
  B11111110, 
  B11101110, 
  B11101110, 
  B10111010, 
};

// 10x8
const byte tractorRtImg[] PROGMEM = {
  B10111010, 
  B11101110, 
  B11101110, 
  B11111110, 
  B11111110,
  B11111110, 
  B10111010, 
  B00101000, 
  B00101000, 
  B11111110,
};

const byte LadiesOfSpain [] PROGMEM = 
{
  HEADER(4,10), 
  NOTE(nB,0,nd1_2,0), 
  
  NOTE(nE,1,nd1_2,0), NOTE(nE,1,nd1_2,0), NOTE(nFs,1,nd1_2,0),
  
  NOTE(nE,1,nd1,0), NOTE(nE,1,nd1_4,0), NOTE(nFs,1,nd1_4,0),

  NOTE(nG,1,nd1_2,0), NOTE(nFs,1,nd1_2,0), NOTE(nE,1,nd1_2,0),

  NOTE(nE,1,nd1_4,0), NOTE(nD,1,nd1_4,0), NOTE(nB,0,nd1_2,0), NOTE(nB,0,nd1_2,0),

  NOTE(nE,1,nd1_2,0), NOTE(nE,1,nd1_2,0), NOTE(nFs,1,nd1_2,0),
  
  NOTE(nE,1,nd1_2,DOT), NOTE(nE,1,nd1_4,0), NOTE(nFs,1,nd1_2,0),

  NOTE(nG,1,nd1_2,0), NOTE(nA,1,nd1_2,0), NOTE(nG,1,nd1_2,0),

  NOTE(nFs,1,nd1,0), NOTE(nFs,1,nd1_2,0),

  NOTE(nG,1,nd1_2,0), NOTE(nFs,1,nd1_2,0), NOTE(nG,1,nd1_2,0),

  NOTE(nA,1,nd1_2,0), NOTE(nG,1,nd1_2,0), NOTE(nA,1,nd1_2,0),

  NOTE(nB,1,nd1_4,0), NOTE(nA,1,nd1_4,0), NOTE(nG,1,nd1_2,0), NOTE(nE,1,nd1_2,0),

  NOTE(nE,1,nd1_4,0), NOTE(nD,1,nd1_4,0), NOTE(nB,0,nd1_2,0), NOTE(nB,1,nd1_4,0), NOTE(nA,1,nd1_4,0),

  NOTE(nG,1,nd1_2,0), NOTE(nE,1,nd1_2,0), NOTE(nE,1,nd1_2,0),

  NOTE(nE,1,nd1_4,0), NOTE(nD,1,nd1_4,0), NOTE(nB,0,nd1_2,0), NOTE(nA,0,nd1_2,0),

  NOTE(nB,1,nd1_2,0), NOTE(nG,1,nd1_2,0), NOTE(nFs,1,nd1_2,0),

  NOTE(nE,1,nd1_2,0), 
  END_OF_SEQUENCE
};

const byte ScarboroughFair [] PROGMEM = 
{
  HEADER(4,9), 
  NOTE(nE, 0,nd1,0), NOTE(nE, 0,nd1_2,0), 
  
  NOTE(nB, 0,nd1,0), NOTE(nB, 0,nd1_2,0), 

  NOTE(nF, 0,nd1_2,DOT), NOTE(nG, 0,nd1_4,0), NOTE(nF, 0,nd1_2,0), 

  NOTE(nE, 0,nd1,DOT), 

  NOTE(nE, 0,nd1_2,0), NOTE(nB, 0,nd1_2,0), NOTE(nD, 1,nd1_2,0), 

  NOTE(nE, 1,nd1,0), NOTE(nD, 1,nd1_2,0), 

  NOTE(nB, 0,nd1_2,0), NOTE(nCs, 1,nd1_2,0), NOTE(nA, 0,nd1_2,0), 

  NOTE(nB, 0,nd1,DOT), 

  NOTE(nB, 0,nd1,0), NOTE(nE, 1,nd1_2,0), 

  NOTE(nE, 1,nd1,0), NOTE(nE, 1,nd1_2,0), 

  NOTE(nD, 1,nd1,0), NOTE(nB, 0,nd1_2,0), 

  NOTE(nB, 0,nd1_2,0), NOTE(nA, 0,nd1_2,0), NOTE(nG, 0,nd1_2,0), 
  
  NOTE(nF, 0,nd1_2,0), NOTE(nD, 0,nd1,0), 

  NOTE(nD, 0,nd1,DOT), 

  NOTE(nE, 0,nd1,0), NOTE(nB, 0,nd1_2,0), 

  NOTE(nA, 0, nd1,0), NOTE(nG, 0,nd1_2,0), 

  NOTE(nF, 0,nd1_2,0), NOTE(nE, 0,nd1_2,0), NOTE(nD, 0,nd1_2,0), 
  
  NOTE(nE, 0,nd1,DOT), 

  NOTE(nE, 0,nd1,DOT), 

  END_OF_SEQUENCE
};

const byte DrunkenSailor [] PROGMEM = 
{
  HEADER(4,9),
  
  NOTE(nA, 0,nd1_2,0), NOTE(nA, 0,nd1_4,0), NOTE(nA, 0,nd1_4,0), NOTE(nA, 0,nd1_2,0), NOTE(nA, 0,nd1_4,0), NOTE(nA, 0,nd1_4,0), 

  NOTE(nA, 0,nd1_2,0), NOTE(nD, 0,nd1_2,0), NOTE(nF, 0,nd1_2,0), NOTE(nA, 0,nd1_2,0), 
  
  NOTE(nG, 0,nd1_2,0), NOTE(nG, 0,nd1_4,0), NOTE(nG, 0,nd1_4,0), NOTE(nG, 0,nd1_2,0), NOTE(nG, 0,nd1_4,0), NOTE(nG, 0,nd1_4,0), 

  NOTE(nG, 0,nd1_2,0), NOTE(nC, 0,nd1_2,0), NOTE(nE, 0,nd1_2,0), NOTE(nG, 0,nd1_2,0), 
  
  NOTE(nA, 0,nd1_2,0), NOTE(nA, 0,nd1_4,0), NOTE(nA, 0,nd1_4,0), NOTE(nA, 0,nd1_2,0), NOTE(nA, 0,nd1_4,0), NOTE(nA, 0,nd1_4,0), 

  NOTE(nA, 0,nd1_2,0), NOTE(nB, 0,nd1_2,0), NOTE(nC, 1,nd1_2,0), NOTE(nD, 1,nd1_2,0), 
  
  NOTE(nC, 1,nd1_2,0), NOTE(nA, 0,nd1_2,0), NOTE(nG, 0,nd1_2,0), NOTE(nE, 0,nd1_2,0), 

  NOTE(nD, 0,nd1,0), NOTE(nD, 0,nd1,0), 

  NOTE(nA, 0,nd1,0), NOTE(nA, 0,nd1_2,1), NOTE(nA, 0,nd1_4,0), 

  NOTE(nA, 0,nd1_2,0), NOTE(nD, 0,nd1_2,0), NOTE(nF, 0,nd1_2,0), NOTE(nA, 0,nd1_2,0), 

  NOTE(nG, 0,nd1,0), NOTE(nG, 0,nd1_2,1), NOTE(nG, 0,nd1_4,0), 

  NOTE(nG, 0,nd1_2,0), NOTE(nC, 0,nd1_2,0), NOTE(nE, 0,nd1_2,0), NOTE(nG, 0,nd1_2,0), 

  NOTE(nA, 0,nd1,0), NOTE(nA, 0,nd1_2,1), NOTE(nA, 0,nd1_4,0), 

  NOTE(nA, 0,nd1_2,0), NOTE(nB, 0,nd1_2,0), NOTE(nC, 1,nd1_2,0), NOTE(nD, 1,nd1_2,0), 

  NOTE(nC, 1,nd1_2,0), NOTE(nA, 0,nd1_2,0), NOTE(nG, 0,nd1_2,0), NOTE(nE, 0,nd1_2,0), 

  NOTE(nD, 0,nd1,0), NOTE(nD, 0,nd1,0), 

  END_OF_SEQUENCE
};


const byte SFX_Hit [] PROGMEM = 
{
  HEADER(5,5), 
  NOTE(nE, 0,nd1,0), 
  NOTE(nDs,0,nd1,0), 
  NOTE(nD, 0,nd1,0), 
  NOTE(nCs,0,nd1,0), 
  END_OF_SEQUENCE
};

const byte SFX_Bell [] PROGMEM = 
{
  HEADER(6,6), 
  NOTE(nC, 0,nd1,0), 
  NOTE(nD,0,nd1,0), 
  NOTE(nC, 0,nd1,0), 
  NOTE(nD,0,nd1,0), 
  END_OF_SEQUENCE
};

const byte SFX_Beep [] PROGMEM = 
{
  HEADER(4,6), 
  NOTE(nC, 0,nd1,0), 
  NOTE(nD,0,nd1,0), 
  END_OF_SEQUENCE
};

const byte SFX_Pickup [] PROGMEM = 
{
  HEADER(3,8), 
  NOTE(nC, 0,nd1,0), 
  NOTE(nF,1,nd1_4,0), 
  NOTE(nG,1,nd1_4,0), 
  NOTE(nA,1,nd1_4,0), 
  NOTE(nB,1,nd1_4,0), 
  END_OF_SEQUENCE
};
/*
const byte SFX_Coin [] PROGMEM = 
{
  HEADER(5,8), 
  NOTE(nC, 0, nd1_4,0), 
  NOTE(nE,1,nd1_2,DOT), 
  NOTE(nE,1,nd1,0), 
  END_OF_SEQUENCE
};*/

/*
const byte SFX_Beep [] PROGMEM = 
{
  HEADER(4,5), 
  NOTE(nC, 1, nd1_8,0), 
  NOTE(nB, 0, nd1_8,0), 
  NOTE(nC, 1, nd1_8,0), 
  NOTE(nB, 0, nd1_8,0), 
  NOTE(nC, 1, nd1_8,0), 
  NOTE(nB, 0, nd1_8,0), 
  NOTE(nC, 1, nd1_8,0), 
  NOTE(nB, 0, nd1_8,0), 
  END_OF_SEQUENCE
};
*/

////// From Squario /////////////////////////////////////////////////////////////
//unsigned long currTime;
//unsigned long prevTime = 0;

//const byte SFX_Hit [] PROGMEM = { 0, 5, 0xC1, 0xB1, 0xA1, 0x91, 0xFF };
//const byte SFX_Jump[] PROGMEM = { 0, 4, 0x21, 0x11, 0x31, 0x21, 0xFF };
//PROGMEM const byte SFX_Pipe [] = { 0, 5, 0xD1, 0xC1, 0xB1, 0xA3, 0xD1, 0xC1, 0xB1, 0xA1, 0xFF };
//PROGMEM const byte SFX_Mushroom [] = { 0, 6, 0x41, 0x41, 0x51, 0x51, 0x61, 0x61, 0x71, 0x71, 0xFF };
//PROGMEM const byte SFX_Coin [] = { 0, 4, 0xF1, 0xE4, 0xFF };
//PROGMEM const byte SFX_Life [] = { 0, 5, 0xE3, 0xD3, 0xE3, 0xD3, 0xC5, 0x85, 0xFF };
/*
PROGMEM const byte Verse [] = {
0x90,47, 0,170, 
0x80, 0,170, 
0x90,47, 0,170, 
0x80,
0x90,54, 0,170,
0x80, 0,170,
0x90,54, 0,170,
0x80,
0x90,50, 0,170,
0x80, 0,170,
0x90,50, 0,170,
0x80,
0x90,52, 0,170,
0x80, 0,170, 
0x90,52, 0,170,
0x80,
0x90,52, 0,170,
0x80, 0,170,
0x90,52, 0,170,
0x80, 0,170,
0xf0};
PROGMEM const byte PreChorus [] = {
0x90,47, 0,85, 0x80, 0,85, 0x90,45, 0,170, 0x80, 0,170, 0x90,47, 0,170, 0x80, 1,84, 
0x90,61, 0,170, 0x80, 0,170, 0x90,61, 0,170, 0x80, 0x90,61, 0,170, 0x80, 0x90,61, 0,170, 
0x80, 0x90,61, 0,170, 0x80, 0x90,62, 0,170, 0x80, 0x90,59, 1,84, 0x80, 0xf0};
PROGMEM const byte Chorus [] = {
0x90,64, 0,227, 0x80, 0,227, 0x90,64, 0,227, 0x80, 0,227, 0x90,62, 3,141, 0x80, 0x90,62, 
0,227, 0x80, 0,227, 0x90,62, 0,227, 0x80, 0,227, 0x90,61, 3,141, 0x80, 0x90,62, 0,227, 
0x80, 0,227, 0x90,62, 0,227, 0x80, 0,227, 0x90,61, 3,141, 0x80, 0x90,61, 0,227, 0x80, 0,227, 
0x90,61, 0,227, 0x80, 0,227, 0x90,59, 3,141, 0x80, 0xf0};
*/
/*
#define nG3S         415  // 0x01
#define nA3          440  // 0x02
#define nB3          494  // 0x03
#define nC4          523  // 0x04
#define nD4          587  // 0x05
#define nE4          659  // 0x06
#define nG4S         831  // 0x07
#define nA4          880  // 0x08
#define nB4          988  // 0x09
#define nC5          1047  // 0x0A
#define nD5          1175  // 0x0B
#define nE5          1319  // 0x0C
#define nF5          1397  // 0x0D
#define nG5          1568  // 0x0E
#define nA5          1760  // 0x0F

#define nA4S         932

#define nB1          123  // 0x1
#define nD2          147  // 0x2
#define nF2          175  // 0x3
#define nA2          220  // 0x4
#define nD3          294  // 0x5
#define nB5          1975 // 0xF
#define nC5S         1109 // 0x9
#define nD5S         1245 // 0xB
#define nC6          2094 // 0xD
#define nE6          2638 // 0xE
PROGMEM const unsigned int SFXNoteSet [] {
  nB1, nD2, nF2,
  nA2, nD3, nA3, nD4,
  nC5, nC5S, nD5, nD5S, nE5,
  nC6, nE6, nB5
};
*/





