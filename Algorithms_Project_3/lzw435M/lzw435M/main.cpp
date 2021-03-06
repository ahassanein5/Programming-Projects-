#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <sys/stat.h>

using namespace std;
/*
  This code is derived from LZW@RosettaCode for UA CS435
*/
 
// Compress a string to a list of output symbols.
// The result will be written to the output iterator
// starting at "result"; the final iterator is returned.
template <typename Iterator>
Iterator compress(const std::string &uncompressed, Iterator result) {
  // Build the dictionary.
  int dictSize = 256;
  std::map<std::string,int> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[std::string(1, i)] = i;               //this dont make sense
 
  std::string w;
  for (std::string::const_iterator it = uncompressed.begin();
       it != uncompressed.end(); ++it) {
    char c = *it;
    std::string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else {
      *result++ = dictionary[w];
      // Add wc to the dictionary. Assuming the size is 4096!!!
      if (dictionary.size()<4096)
         dictionary[wc] = dictSize++;
      w = std::string(1, c);
    }
  }
 
  // Output the code for w.
  if (!w.empty())
    *result++ = dictionary[w];
  return result;
}
 
// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
template <typename Iterator>
std::string decompress(Iterator begin, Iterator end) {
  // Build the dictionary.
  int dictSize = 256;
  std::map<int,std::string> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[i] = std::string(1, i);
 
  std::string w(1, *begin++);
  std::string result = w;
  std::string entry;
  for ( ; begin != end; begin++) {
    int k = *begin;
    if (dictionary.count(k))
      entry = dictionary[k];
    else if (k == dictSize)
      entry = w + w[0];
    else
      throw "Bad compressed k";
 
    result += entry;
 
    // Add w+entry[0] to the dictionary.
    if (dictionary.size()<4096)                       //2^12
      dictionary[dictSize++] = w + entry[0];
 
    w = entry;
  }
  return result;
}

std::string int2BinaryString(int c, int cl) {
      std::string p = ""; //a binary code string with code length = cl
      int code = c;
      while (c>0) {
           if (c%2==0)
            p="0"+p;
         else
            p="1"+p;
         c=c>>1;
      }
      int zeros = cl-p.size();
      if (zeros<0) {
         std::cout << "\nWarning: Overflow. code " << code <<" is too big to be coded by " << cl <<" bits!\n";
         p = p.substr(p.size()-cl);
      }
      else {
         for (int i=0; i<zeros; i++)  //pad 0s to left of the binary code if needed
            p = "0" + p;
      }
      return p;
}

int binaryString2Int(std::string p) {
   int code = 0;
   if (p.size()>0) {
      if (p.at(0)=='1')
         code = 1;
      p = p.substr(1);
      while (p.size()>0) {
         code = code << 1;
           if (p.at(0)=='1')
            code++;
         p = p.substr(1);
      }
   }
   return code;
}


void binaryIODemo(std::vector<int> compressed, int& bits) {
    int c = 69, count = 0;
   std::string p = int2BinaryString(c, bits);

   std::string bcode= "";
   for (std::vector<int>::iterator it = compressed.begin() ; it != compressed.end(); ++it) {
      if (count < 256)
          bits = 9;
       else if (count < 512)
           bits = 10;
       else if (count < 768)
           bits = 11;
       else if (count < 1024)
           bits = 12;
       else if (count < 1280)
           bits = 13;
       else if (count < 1536)
           bits = 14;
       else if (count < 1792)
           bits = 15;
       else
           bits = 16;
      
      p = int2BinaryString(*it, bits);
      std::cout << "c=" << *it <<" : binary string="<<p<<"; back to code=" << binaryString2Int(p)<<"\n";
      bcode+=p;
      count++;
   }

   //writing to file
   std::cout << "string 2 save : "<<bcode << "\n";
   std::string fileName = "example435.lzw";
   std::ofstream myfile;
   myfile.open(fileName.c_str(),  std::ios::binary);

   std::string zeros = "00000000";
   if (bcode.size()%8!=0) //make sure the length of the binary string is a multiple of 8
      bcode += zeros.substr(0, 8-bcode.size()%8);

   int b;
   for (int i = 0; i < bcode.size(); i+=8) {
      b = 1;
      for (int j = 0; j < 8; j++) {
         b = b<<1;
         if (bcode.at(i+j) == '1')
           b+=1;
      }
      char c = (char) (b & 255); //save the string byte by byte
      myfile.write(&c, 1);
   }
   myfile.close();

   
}
 
void binaryFromFile(std::string fileName, std::string &s){

    std::string zeros = "00000000";
   //reading from a file
   std::ifstream myfile2;
   myfile2.open (fileName.c_str(),  std::ios::binary);

   struct stat filestatus;
   stat(fileName.c_str(), &filestatus );
   long fsize = filestatus.st_size; //get the size of the file in bytes

   char c2[fsize];
   myfile2.read(c2, fsize);

   long count = 0;
   while(count<fsize) {
      unsigned char uc =  (unsigned char) c2[count];
      std::string p = ""; //a binary string
      for (int j=0; j<8 && uc>0; j++) {
           if (uc%2==0)
            p="0"+p;
         else
            p="1"+p;
         uc=uc>>1;
      }
      p = zeros.substr(0, 8-p.size()) + p; //pad 0s to left if needed
      s+= p;
      count++;
   }
   myfile2.close();
   std::cout << " saved string : "<<s << "\n";
    std::cout << " it saved";
}
 



int main(int argc, char *argv[]) {
    int bits = 9;
    std::string uncompressed, temp, filename;
    std::ofstream outFileBits, outFileDecompress;
    std::ifstream getBit;
    if(argc == 3){
        filename = argv[2];
    }
    std::ifstream inFile;
    inFile.open(filename);
    while(!inFile.eof()){
        inFile >> temp;
        uncompressed += temp;
    }
    
    std::string s = "";
    std::vector<int> compressed;
    std::string compressType = argv[1];
    
    if(compressType == "c"){
        //compress
        compress(uncompressed, std::back_inserter(compressed));
        copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
        
        binaryIODemo(compressed, bits);
        outFileBits.open("bits.txt");
        outFileBits << bits;
        outFileBits.close();
        
    }
    
    // this needs to be edited
    else if (compressType == "e"){
        getBit.open("bits.txt");
        getBit >> bits;
        getBit.close();
        //decompress
        std::vector<int> holdInts;      //ints converted from binary
        binaryFromFile(filename, s);         //binary string from file
        //confirm that binaryF string is multiple of 12
        if(s.size()%8 != 0)
            std::cout << "something went wrong...\n";
        else{
            int count = 0;
            int tempBit = 9;
            for(int i=0; i < s.size(); i+=tempBit){
                if(tempBit <= bits){
                    string temp = s.substr(i, tempBit);
                    int tempInt = binaryString2Int(temp);
                    holdInts.push_back(tempInt);
                }
                count++;
                if(count == 256)
                    tempBit++;
            }
        }
        cout << "start decompression......\n";
        outFileDecompress.open("decompressed.txt");
        std::string decompressed = decompress(holdInts.begin(), holdInts.end());
        cout << "decompress finished....\n";
        outFileDecompress << decompressed << std::endl;
        outFileDecompress.close();
    }
    
  

  return 0;
}
