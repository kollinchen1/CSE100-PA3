/**
 *  CSE 100 PA3 C++ Huffman Coding
 *  Authors: Pen Cheung Chu, Kunlun Chen
 */
#include "HCNode.h"

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically. */
bool HCNode::operator<  (const HCNode& other)
{
  if(this->count != other.count)
    return (this->count > other.count);
  else
    return (this->symbol > other.symbol);
}

/** Output the Pre-Order Traversal of the Heap as Tree Encoding. */
void HCNode::preOrderEncode(BitOutputStream& bos) const
{
  if(c0 == 0 && c1 == 0) 
  {  
    //Its a Leaf
    bos.writeBit(1);
    bos.writeByte(symbol);
  }
  else
  {  
    //Not a Leaf
    bos.writeBit(0);
   
    c0->preOrderEncode(bos);
    c1->preOrderEncode(bos);
  }
}


/* Destructor */
HCNode::~HCNode()
{
  if(c0 != 0)
    delete(c0);
  if(c1 != 0)
    delete(c1);
}
