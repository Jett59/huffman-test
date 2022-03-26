#include "huffman.h"
#include <algorithm>
#include <string>

using std::min;
using std::string;

string Bitstring::toBinaryString() const {
  string result;
  result.reserve(bits.size());
  for (auto bit : bits) {
    if (bit) {
      result += '1';
    } else {
      result += '0';
    }
  }
  return result;
}
string Bitstring::toByteString() const {
  int byteCount = (bits.size() + 7) / 8;
  string result;
  result.reserve(byteCount);
  for (int bytePosition = 0; bytePosition < byteCount; bytePosition++) {
    char byte = 0;
    int remainingBits = bits.size() - (bytePosition * 8);
    int bitsInByte = min(8, remainingBits);
    for (int bitPosition = 0; bitPosition < bitsInByte; bitPosition++) {
      bool bit = bits[bitPosition + (bytePosition * 8)];
      if (bit) {
        byte |= 1 << (bitsInByte - bitPosition - 1);
      }
    }
    result += byte;
  }
  return result;
}
