#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::max;
using std::move;
using std::string;
using std::vector;

class Bitstring {
private:
  vector<bool> bits;

public:
  void append(bool bit) { bits.push_back(bit); }
  void append(Bitstring &value) {
    for (auto bit : value.bits) {
      append(bit);
    }
  }
  string toBinaryString() {
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
  string toByteString() {
    int byteCount = (bits.size() + 7) / 8 * 8;
    string result;
    result.reserve(byteCount);
    for (int bytePosition = 0; bytePosition < byteCount; bytePosition++) {
      char byte = 0;
      int remainingBits = bits.size() - (bytePosition * 8);
      int bitsInByte = max(8, remainingBits);
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
  bool operator[](int index) const { return bits.at(index); }
  Bitstring operator+(bool b) const {
    Bitstring result = *this;
    result.append(b);
    return result;
  }
  Bitstring operator+(Bitstring &value) const {
    Bitstring result = *this;
    result.append(value);
    return result;
  }
  Bitstring &operator+=(bool bit) {
    append(bit);
    return *this;
  }
  Bitstring &operator+=(Bitstring &other) {
    append(other);
    return *this;
  }
};
