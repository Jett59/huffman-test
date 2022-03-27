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
  size_t byteCount = (bits.size() + 7) / 8;
  string result;
  result.reserve(byteCount);
  for (size_t bytePosition = 0; bytePosition < byteCount; bytePosition++) {
    char byte = 0;
    size_t remainingBits = bits.size() - (bytePosition * 8);
    size_t bitsInByte = min(size_t(8), remainingBits);
    for (size_t bitPosition = 0; bitPosition < bitsInByte; bitPosition++) {
      bool bit = bits[bitPosition + (bytePosition * 8)];
      if (bit) {
        byte |= 1 << bitPosition;
      }
    }
    result += byte;
  }
  return result;
}
