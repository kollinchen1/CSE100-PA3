/**
 *  CSE 100 PA3 C++ Huffman Coding
 *  Authors: Pen Cheung Chu, Kunlun Chen
 */
#include <iostream>

typedef unsigned char byte;

/* A class to convert Char, Int or Bit into chunk of bytes for compression. */
class BitOutputStream 
{
private:
  char buf; // one byte buffer of bits
  int nbits; // how many bits have been written to buf
  std::ostream & out; // reference to the output stream to use

public:
  
  /** Initialize a BitOutputStream that will use
   *  the given ostream for output */
  BitOutputStream(std::ostream & os);
  
  /** Send the buffer to the output, and clear it */
  void flush();
  
  /** Write the least significant 32bits of the argument to
   *  the bit buffer using writeBit as helper*/
  void writeInt(unsigned int i);
  
  /** Write the least significant 8bits of the argument to
   *  the bit buffer using writeBit as helper*/
  void writeByte(int i);
  
  /** Write the least significant bit of the argument to
   * the bit buffer, and increment the bit buffer index.
   * But flush the buffer first, if it is full. */
  void writeBit(int i);
  
  /** Helper method of writeBit to help clear the bit at n
   *  and set the bit to b. */
  byte setBit(byte b, int bit, int n);

};
