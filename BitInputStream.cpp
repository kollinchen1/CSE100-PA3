/**
 *  CSE 100 PA3 C++ Huffman Coding
 *  Authors: Pen Cheung Chu, Kunlun Chen
 */
#include "BitInputStream.h"
#define ONEBYTE 8
#define FOURBYTE 32
#define BINARY 2
#define TWOTOSEVEN 128
#define TWOTOTHIRTYONE 2147483648
#define ABYTE 256

/** Initialize a BitInputStream that will use
 *  the given istream for input. */
BitInputStream::BitInputStream(std::istream & is) : in(is)
{
  buf = 0; // clear buffer
  nbits = ONEBYTE; // initialize bit index
}

/** Fill the buffer from the input */
void BitInputStream::fill() 
{
  buf = in.get();
  nbits = 0;
}

/** Read the next 4 byte from the bit buffer and return 
 *  the result as an integer. */
unsigned int BitInputStream::readInt()
{
  unsigned int returnVal = 0;
  unsigned int powerOfTwo = TWOTOTHIRTYONE;
  
  //Read the following 32 bits
  for(int i = 0; i < FOURBYTE; i++)
  {

    if(readBit() == 1)
      returnVal += powerOfTwo;
      //Sum up when bit is not 0

    powerOfTwo /= BINARY;
  }
  return returnVal;
}

/** Read the next byte from the bit buffer and return 
 *  the character as an integer. */
int BitInputStream::readByte()
{
  int returnVal = 0;
  int powerOfTwo = TWOTOSEVEN;

  //Read the following 8 bits
  for(int i = 0; i < ONEBYTE; i++)
  {
    if(readBit() == 1)
      returnVal += powerOfTwo;
      //Sum up when bit is not 0
    
    powerOfTwo /= BINARY;
  }
  return returnVal;
}

/** Read the next bit from the bit buffer
 *  Fill the buffer from the input stream first if needed.
 *  Return 1 if the bit read is 1;
 *  return 0 if the bit read is 0. */
int BitInputStream::readBit() 
{
  int returnVal = -1;
  byte bitAtN;
  
  // If all bits in the buffer are read, fill the buffer first
  if(nbits >= ONEBYTE)
    fill();

  // if EOF reached  
  if(in.eof())
  {
    return returnVal;
  }
  // Get the bit at the appriopriate location in the bit
  // buffer, and return the appropriate int
  bitAtN = bitVal(buf, nbits);

  if(bitAtN == 0x01)
    returnVal = 1;
  
  else 
  if(bitAtN == 0x00)
    returnVal = 0;

  // Increment the index
  nbits++;
  
  return returnVal;
}

/** Helper method for readBit which will shift the bit 
 *  at n to the last bit. */
byte BitInputStream::bitVal(byte b, int n)
{
  byte returnVal; 
  byte mask = 0x01<<n;
  returnVal = ((b&mask)>>n);
  return returnVal;
}
