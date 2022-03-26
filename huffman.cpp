#include "huffman.h"
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using std::make_shared;
using std::map;
using std::move;
using std::optional;
using std::priority_queue;
using std::shared_ptr;
using std::string;
using std::vector;

struct DictionaryEntry {
  Bitstring code;
  char byte;

  Bitstring getBits() const {
    Bitstring result;
    result.append(code.size() - 1, 4);
    result += code;
    result += byte;
    return result;
  }
  DictionaryEntry() = default;
  DictionaryEntry(const Bitstring &bits, int offset) {
    int codeLength = bits.read(offset, 4) + 1;
    code = bits.readBits(offset + 4, codeLength);
    byte = bits.read(offset + 4 + codeLength, 8);
  }
};

struct ByteFrequency {
  int frequency;
  char byte;
};

using HuffmanTree = BTree<ByteFrequency>;

struct HuffmanTreeCompare {
  bool operator()(shared_ptr<HuffmanTree> left, shared_ptr<HuffmanTree> right) {
    return left->value.frequency > right->value.frequency;
  }
};

using PriorityQueue =
    priority_queue<shared_ptr<HuffmanTree>, vector<shared_ptr<HuffmanTree>>,
                   HuffmanTreeCompare>;

map<char, int> getFrequencies(const string &input) {
  map<char, int> result;
  for (char c : input) {
    result[c]++;
  }
  return result;
}

shared_ptr<HuffmanTree> buildTree(const string &input) {
  PriorityQueue queue;
  map<char, int> byteFrequencies = getFrequencies(input);
  for (auto &entry : byteFrequencies) {
    ByteFrequency byteFrequency;
    byteFrequency.byte = entry.first;
    byteFrequency.frequency = entry.second;
    queue.push(make_shared<HuffmanTree>(byteFrequency));
  }
  while (queue.size() > 1) {
    auto left = queue.top();
    queue.pop();
    auto right = queue.top();
    queue.pop();
    auto top = make_shared<HuffmanTree>();
    top->value.frequency = left->value.frequency + right->value.frequency;
    top->left = move(left);
    top->right = move(right);
    queue.push(move(top));
  }
  return queue.top();
}

void addCodesToMap(const HuffmanTree &tree, map<char, Bitstring> &output, const Bitstring &bits) {
  if (tree.left == nullptr && tree.right == nullptr) {
    // Leaf
    output[tree.value.byte] = bits;
  }else {
    if (tree.left != nullptr) {
      addCodesToMap(*tree.left, output, bits + /*0*/ false);
    }
    if (tree.right != nullptr) {
      addCodesToMap(*tree.right, output, bits + /*1*/ true);
    }
  }
}

map<char, Bitstring> getCodeMap(const HuffmanTree &tree) {
  map<char, Bitstring> result;
  addCodesToMap(tree, result, Bitstring());
  return result;
}

string encode(const string &input) {
  Bitstring result;
  auto tree = buildTree(input);
  auto codeMap = getCodeMap(*tree);
  Bitstring dictionary;
  dictionary.append(codeMap.size() - 1, 8);
  for (auto &entry : codeMap) {
    DictionaryEntry dictionaryEntry;
    dictionaryEntry.byte = entry.first;
    dictionaryEntry.code = entry.second;
    dictionary += dictionaryEntry.getBits();
  }
  Bitstring payload;
  for (char c : input) {
    payload += codeMap[c];
  }
  int outputSize = payload.size() + dictionary.size() + 3;
  int paddingBits = 8 - outputSize % 8;
  if (paddingBits == 8) {
    paddingBits = 0;
  }
  result.append(paddingBits, 3);
  result += dictionary;
  result += payload;
  return result.toByteString();
}
