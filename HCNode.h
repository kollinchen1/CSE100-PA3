/**
 *  CSE 100 PA3 C++ Huffman Coding
 *  Authors: Pen Cheung Chu, Kunlun Chen
 */
#ifndef HCNODE_H
#define HCNODE_H

#include <iostream>
#include "BitInputStream.h"
#include "BitOutputStream.h"

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree. */
class HCNode {

public:
    int count;   // frequency of the word in file
    byte symbol; // byte in the file we're keeping track of
    HCNode* c0;  // pointer to '0' child
    HCNode* c1;  // pointer to '1' child
    HCNode* p;   // pointer to parent

    /** Default Constructor */
    HCNode(int count,
      byte symbol,
      HCNode* c0 = 0,
      HCNode* c1 = 0,
      HCNode* p = 0)
        : count(count), symbol(symbol), c0(c0), c1(c1), p(p) { }

    /** Less-than comparison, so HCNodes will work in std::priority_queue
     *  We want small counts to have high priority.
     *  And we want to break ties deterministically. */
    bool operator<(const HCNode& other);
    
    /** Output the Pre-Order Traversal of the Heap as Tree Encoding. */
    void preOrderEncode(BitOutputStream& out) const;
    
    /** Destructor */
    ~HCNode();
};

/** For printing an HCNode to an ostream
 *  Possibly useful for debugging.
 */
ostream& operator<<(ostream&, const HCNode&) __attribute__((weak)); 
  // shut the linker up
ostream& operator<<(ostream& stm, const HCNode& n) {
    stm << "[" << n.count << "," << (int) (n.symbol) << "]";
    return stm;
}


#endif // HCNODE_H
