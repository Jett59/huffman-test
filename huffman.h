#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

class Bitstring {
private:
  std::vector<bool> bits;

public:
  size_t size() const { return bits.size(); }

  void clear() { bits.clear(); }
  void append(bool bit) { bits.push_back(bit); }
  void append(const Bitstring &value) {
    for (auto bit : value.bits) {
      append(bit);
    }
  }
  void append(char byte) {
    append((byte & 1) != 0);
    append((byte & 2) != 0);
    append((byte & 4) != 0);
    append((byte & 8) != 0);
    append((byte & 16) != 0);
    append((byte & 32) != 0);
    append((byte & 64) != 0);
    append((byte & 128) != 0);
  }
  void append(const std::string &s) {
    for (auto byte : s) {
      append(byte);
    }
  }
  void append(int value, int bitCount) {
    for (int i = 0; i < bitCount; i++) {
      bool bit = (value & (1 << i)) != 0;
      append(bit);
    }
  }

  std::string toBinaryString() const;
  std::string toByteString() const;

  bool operator[](size_t index) const { return bits.at(index); }
  int read(size_t offset, int bitCount) const {
    int result = 0;
    for (int i = 0; i < bitCount; i++) {
      bool bit = bits[offset + i];
      if (bit) {
        result |= 1 << i;
      }
    }
    return result;
  }
  Bitstring readBits(size_t offset, int bitCount) const {
    Bitstring result;
    for (int i = 0; i < bitCount; i++) {
      result += bits[offset + i];
    }
    return result;
  }

  Bitstring operator+(bool b) const {
    Bitstring result = *this;
    result.append(b);
    return result;
  }
  Bitstring operator+(const Bitstring &value) const {
    Bitstring result = *this;
    result.append(value);
    return result;
  }
  Bitstring operator+(char byte) const {
    Bitstring result = *this;
    result.append(byte);
    return result;
  }
  Bitstring operator+(const std::string &s) const {
    Bitstring result = *this;
    result.append(s);
    return result;
  }
  Bitstring &operator+=(bool bit) {
    append(bit);
    return *this;
  }
  Bitstring &operator+=(const Bitstring &other) {
    append(other);
    return *this;
  }
  Bitstring &operator+=(char byte) {
    append(byte);
    return *this;
  }
  Bitstring &operator+=(const std::string &s) {
    append(s);
    return *this;
  }
};

template <typename T> class BTree {
public:
 std::shared_ptr<BTree<T>> left, right;
 T value;

 BTree() = default;
 BTree(T value) : value(value) {}
};

std::string encode(const std::string &input);
std::string decode(const std::string &input);

#endif