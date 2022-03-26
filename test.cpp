#include "test.h"
#include "huffman.h"
#include <iostream>

using std::cerr;
using std::endl;

void bitstringTest();

int main() {
  bitstringTest();
  return 0;
}

void bitstringTest() {
  Bitstring bitString;
  assert(bitString.size() == 0);
  bitString += true;
  bitString += false;
  assert(bitString.size() == 2);
  Bitstring other;
  other += false;
  other += true;
  bitString += other;
  assert(bitString.size() == 4);
  assert(bitString.toBinaryString() == "1001");
  bitString += true;
  bitString += true;
  bitString += true;
  bitString += true;
  assert(bitString.size() == 8);
  assert(bitString.toByteString() == "\x9f");
  bitString += 'A';
  assert(bitString.toByteString() == "\x9f\x41");
}
