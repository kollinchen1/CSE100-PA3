/**
 *  CSE 100 PA3 C++ Huffman Coding
 *  Authors: Pen Cheung Chu, Kunlun Chen
 */
#include "BitOutputStream.h"
#define ONEBYTE 8
#define FOURBYTE 32
#define BINARY 2
#define TWOTOSEVEN 128
#define TWOTOTHIRTYONE 2147483648
#define ABYTE 256

/** Initialize a BitOutputStream that will use
 *  the given ostream for output */
BitOutputStream::BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) 
{
  // clear buffer and bit counter
}

/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() 
{
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/** Write the least significant 32bits of the argument to
 *  the bit buffer using writeBit as helper*/
void BitOutputStream::writeInt(unsigned int i)
{
  unsigned int powerOfTwo = TWOTOTHIRTYONE;
 
  //32bits will be written
  for(int j = 0; j < FOURBYTE; j++)
  {
    if(i >= powerOfTwo)
    {
      i -= powerOfTwo;
      writeBit(1);
    }    
    else
      writeBit(0);
    
    powerOfTwo /= BINARY;
  }
}

/** Write the least significant 8bits of the argument to
 *  the bit buffer using writeBit as helper*/
void BitOutputStream::writeByte(int i)
{
  int powerOfTwo = TWOTOSEVEN;
  
  //8bits will be written
  for(int j = 0; j < ONEBYTE; j++)
  {
    if(i >= powerOfTwo)
    {
      i -= powerOfTwo;
      writeBit(1);
    }    
    else
      writeBit(0);
    
    powerOfTwo /= BINARY;
  }

}

/** Write the least significant bit of the argument to
 * the bit buffer, and increment the bit buffer index.
 * But flush the buffer first, if it is full. */
void BitOutputStream::writeBit(int i) 
{
  // Is the bit buffer full? Then flush it.
  if(nbits >= ONEBYTE)
    flush();

  // Write the least significant bit of i into the buffer
  // at the current index
  buf = setBit(buf, i, nbits);

  // Increment the index
  nbits++;
}

/** Helper method of writeBit to help clear the bit at n
 *  and set the bit to b. */
byte BitOutputStream::setBit(byte b, int bit, int n) 
{
  byte value = 0x00;

  if(bit == 0)
    value = 0x00<<n;
  else if(bit == 1)
    value = 0x01<<n;

  byte mask = ~(0x01<<n);
  return ((buf&mask)|value);
}
