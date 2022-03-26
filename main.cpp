#include "huffman.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
  string input = "This is text! It will hopefully get nicely compressed into a small little blob of bits and then converted to a series of bytes for storage on a file!";
  string output = encode(input);
  cout << output.length() << endl;
  return 0;
}
