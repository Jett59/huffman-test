#include "huffman.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
  Bitstring encoding;
  encoding += true;
  encoding += true;
  cout << encoding.toBinaryString() << endl;
  return 0;
}
