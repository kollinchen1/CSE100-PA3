/**
 *  CSE 100 PA3 C++ Huffman Coding
 *  Authors: Pen Cheung Chu, Kunlun Chen
 */
#include <iostream>

typedef unsigned char byte;

/* A class to convert BitInput into readible Char, Int or Bits */
class BitInputStream
{
private:
  char buf; //one byte buffer of bits
  int nbits; // how many bits have been read from buf
  std::istream & in;// the input stream to use

public:
  
  /** Initialize a BitInputStream that will use
   *  the given istream for input. */
  BitInputStream(std::istream & is);
  
  /** Fill the buffer from the input */
  void fill(); 
 
  /** Read the next 4 byte from the bit buffer and return 
   *  the result as an integer. */
  unsigned int readInt();
  
  /** Read the next byte from the bit buffer and return 
   *  the character as an integer. */
  int readByte();
  
  /** Read the next bit from the bit buffer
   *  Fill the buffer from the input stream first if needed.
   *  Return 1 if the bit read is 1;
   *  return 0 if the bit read is 0. */
  int readBit();
  
  /** Helper method for readBit which will shift the bit 
   *  at n to the last bit. */
  byte bitVal(byte b, int n);

};
