/**
 *  CSE 100 PA3 C++ Huffman Coding
 *  Authors: Pen Cheung Chu, Kunlun Chen
 */
#include "HCNode.h"
#include "HCTree.h"

#define INPUT 1
#define OUTPUT 2
#define EXPECTEDARG 3
#define TWOBYTE 255
#define ALLCHAR 256
int main(int argc, char** argv)
{
  //Huffman Coding Tree
  HCTree hctree;
  
  //Arguments for reading
  vector<int> freqs (ALLCHAR, 0);
  unsigned char readingByte;
  unsigned int totalWords = 0; 

  /*
  //Default case
  if(argc == 1)
  {
   argc = 3;
   argv[0] = "DEFAULT CASE";
   argv[1] = "warandpeace.txt";
   argv[2] = "compressOutput.txt";
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
 
  //BitOutputStream
  BitOutputStream bos(out);
  
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

  //Reading character and construct frequency vector
  readingByte = in.get();
  while(!in.eof())
  {
    freqs.at(readingByte)++;
    totalWords++;
    
    readingByte = in.get();
  }
  in.close();

  //Output total characters into output
  bos.writeInt(totalWords);

  //Coding Tree will only be built if there is input
  if(totalWords > 0)
  {
  
    //Build the tree
    hctree.build(freqs);
    
    //Output preorder encoding to output
    hctree.preOrderEncode(bos);

    //Encode the file
    in.open(argv[INPUT]);
  
    //Encode each character until EOF
    readingByte = in.get();  
    while(!in.eof())
    {    
        hctree.encode(readingByte, bos);
        readingByte = in.get(); 
    }

    //Flush out the last bits
    bos.flush();
  }

  //Close the two files
  in.close();
  out.close();

  return 0;
}
