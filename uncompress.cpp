/**
 *  CSE 100 PA3 C++ Huffman Coding
 *  Authors: Pen Cheung Chu, Kunlun Chen
 */

#include "HCNode.h"
#include "HCTree.h"

#define INPUT 1
#define OUTPUT 2
#define EXPECTEDARG 3

int main(int argc, char** argv)
{
  //Huffman Coding Tree
  HCTree hctree;
  
  //Arguments for reading
  int buffer;
  unsigned int totalWords;

  /*
  //Default case
  if(argc == 1)
  {
   argc = 3;
   argv[0] = "DEFAULT CASE";
   argv[1] = "compressOutput.txt";
   argv[2] = "uncompressOutput.txt";
  }
  */

  //Incorrect arguments
  if(argc != EXPECTEDARG)
  {
    std::cout<<"There should be 2 Arguments ./compress input output\n";
    return -1;
  }

  //Input and output Stream
  ifstream in;
  ofstream out;
  
  in.open(argv[INPUT]);
  out.open(argv[OUTPUT]);
  
  BitInputStream bis(in);
  
  if(!in.is_open())
  {
    cout<<"Invalid input file. No file was opened. Please try again\n";
    return -1;
  }

  if(!out.is_open())
  {
    cout<<"Invalid output file. No file was opened. Please try again\n";
    return -1;
  }

  //Read the first 32bits as totalWords in file
  totalWords = (unsigned int)bis.readInt();
  
  //Decode if the file is not empty
  if(totalWords > 0)
  {
    //Build the heap using the preOrder Encoding
    hctree.buildHeap(bis);   

    //Decode the file
    int i = 0; 
    //use counter to make sure it won't read any extra char
    while(!in.eof()&& i<totalWords)
    { 
      buffer = hctree.decode(bis);
     
      //Check if decode returns error output
      if(buffer != -1)
        out << ((char)buffer);
    
      i++;
    }
  }

  //Close both files
  in.close();
  out.close();

  return 0;
}
