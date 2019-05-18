/**
 *  CSE 100 PA3 C++ Huffman Coding
 *  Authors: Pen Cheung Chu, Kunlun Chen
 */
#include "HCTree.h"

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build (const vector<int>& freqs)
{
  std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> myPQ;

  //Construct all Heap Node base on frequency vector
  for(int i = 0; i < freqs.size(); i++)
  { 
    
    //Node created and push into PQ only if freq>0
    if(freqs.at(i)>0)
    {  
      HCNode* tempNode = new HCNode(freqs.at(i), i);
      myPQ.push(tempNode); 
      leaves.at(i) = tempNode;
      //Reference this Node as the Leaf Node
    }
  }

  //Temporary pointers
  HCNode* left;
  HCNode* right;
  HCNode* parent;
  
  while(myPQ.size() > 1)
  {
    //Reference left and right to correct Node
    left = myPQ.top();
    myPQ.pop();
    right = myPQ.top();
    myPQ.pop();
    
    //Create dummy parent
    parent = new HCNode((left->count + right->count), right->symbol);
    
    //Link up
    parent->c0 = left;
    parent->c1 = right;
    left->p  = parent;
    right->p = parent;
 
    //Push back to PQ
    myPQ.push(parent);

  }
  
  //Root will be the current parent dummyNode
  root = myPQ.top();
  myPQ.pop();

  return;
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode (byte symbol, BitOutputStream& out) const
{
  HCNode* target = leaves.at(symbol); //Current HeapNode Reference

  //Case Node not found
  if(target == (HCNode*)0)
    return;
  
  std::stack<int> cipher; //Encoded CipherText
  HCNode* parent = target->p; //Parent HeapNode Reference
  
  //While loop won't stop until cipher is complete
  while(target != root)
  {
    
    //Converting path to ciphertext
    if(parent->c0 == target)
      cipher.push(0);
    else
      cipher.push(1);

    //Move one level above in heap
    target = parent;
    parent = target->p;
  }

  //Reverse the ciphertext using the stack
  while(!cipher.empty())
  {
    out.writeBit(cipher.top());
    cipher.pop();
  }

}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode (byte symbol, ofstream& out) const
{
  HCNode* target = leaves.at(symbol); //Current HeapNode Reference

  //Case Node not found
  if(target == (HCNode*)0)
    return;
  
  std::stack<byte> cipher; //Encoded CipherText
  HCNode* parent = target->p; //Parent HeapNode Reference
  
  //While loop won't stop until cipher is complete
  while(target != root)
  {
    
    //Converting path to ciphertext
    if(parent->c0 == target)
      cipher.push('0');
    else
      cipher.push('1');

    //Move one level above in heap
    target = parent;
    parent = target->p;
  }

  //Reverse the ciphertext using the stack
  while(!cipher.empty())
  {
    std::cout<<cipher.top();
    out<<cipher.top();
    cipher.pop();
  }

  return;
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode (BitInputStream& in) const
{
  //Decoding start from the root
  HCNode* current = root;
  
  //Character buffer for the input file
  int c;
  
  while((c = in.readBit())!= -1)
  {
    //Traverse the Heap based on buffer
    if(c == 0)
      current = current->c0;
    else if( c == 1)
      current = current->c1;
    //Case which an invalid character is read, return error
    else
      return -1;

    //Case a Leave Node has been reached
    if(current->c0 == 0 && current->c1 == 0)
      break;
  }
 
  //Return Error if such node is not a leave node
  if(current->c0 != 0 && current->c1 != 0)
    return -1;

  //Debug Message
  //std::cout<<" Decoded: "<<current->symbol<<"\n";
  return current->symbol;
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode (ifstream& in) const
{
  //Decoding start from the root
  HCNode* current = root;
  
  //Character buffer for the input file
  char c;
  
  while((c = in.get())!=EOF)
  {
    //Traverse the Heap based on buffer
    if(c == '0')
      current = current->c0;
    else if( c == '1')
      current = current->c1;
    //Case which an invalid character is read, return error
    else
      return -1;

    //Case a Leave Node has been reached
    if(current->c0 == 0 && current->c1 == 0)
      break;
  }
 
  //Return Error if such node is not a leave node
  if(current->c0 != 0 && current->c1 != 0)
    return -1;

  //Debug Message
  //std::cout<<" Decoded: "<<current->symbol<<"\n";
  return current->symbol;
}


/** Output the Pre-Order Traversal of the Heap as Tree Encoding. */
void HCTree::preOrderEncode(BitOutputStream& bos) const
{
  root->preOrderEncode(bos);
}

/** Build the Huffman Coding Heap using it's preOrder encoding from input. */
void HCTree::buildHeap(BitInputStream& bis)
{
  root = buildHeapHelper(bis);
}

/** Recursive Helper function to identify input and build Node and link up. */
HCNode* HCTree::buildHeapHelper(BitInputStream& bis)
{
  //Base on this first bit to determine what to build
  int isLeaf = bis.readBit();
  HCNode* returnVal = 0;
  
  //if first bit is 1, its a leaf
  if(isLeaf == 1)
  {
    //Build Node as Leaf Node
    unsigned char symbol = (unsigned char)bis.readByte();
    returnVal = new HCNode(0, symbol, 0, 0, 0);   
    
    //Set Leaf pointing to this Node
    leaves.at((int)symbol) = returnVal; 
  }
  
  //if first bit is 0, its a dummy parent
  else
  {
    //The dummy Node will always have two children
    HCNode* c0 = buildHeapHelper(bis);
    HCNode* c1 = buildHeapHelper(bis);
   
    //Build Node as Dummy Node
    returnVal = new HCNode(0, 0, c0, c1, 0);
    returnVal->c0 = c0;
    returnVal->c1 = c1;
    //Shouldn't be necessary for decoding but well
    c0->p = returnVal;
    c1->p = returnVal;
  }

  return returnVal;
}

/* Destructor */
HCTree::~HCTree()
{
  delete(root);
}
