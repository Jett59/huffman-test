#include "test.h"
#include "huffman.h"
#include <iostream>

using std::cerr;
using std::endl;

void bitstringTest();
void huffmanTest();

int main() {
  bitstringTest();
  huffmanTest();
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
  assert(bitString.toByteString() == "\xf9");
  assert((Bitstring() + bitString.toByteString()).toByteString() ==
         bitString.toByteString());
  bitString += 'A';
  assert(bitString.toByteString() == "\xf9\x41");
  bitString += false;
  bitString += true;
  assert((Bitstring() + bitString.toByteString()).toByteString() ==
         bitString.toByteString());
}
void huffmanTest() {}
