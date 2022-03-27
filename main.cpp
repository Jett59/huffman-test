#include "huffman.h"
#include <fstream>
#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;

void usage(const char *programName) {
  cerr << "Usage: " << programName
       << " <zip | unzip> <input file> <output file>" << endl;
}

int main(int argc, char **argv) {
  if (argc < 4) {
    usage(argv[0]);
    return 1;
  }
  string action = argv[1];
  string inputFileName = argv[2];
  string outputFileName = argv[3];
  ifstream inputFile(inputFileName, ios::binary);
  ofstream outputFile(outputFileName, ios::binary);
  string input;
  char c;
  c = inputFile.get();
  while (!inputFile.eof()) {
    input += c;
    c = inputFile.get();
  }
  string output;
  if (action == "zip") {
    output = encode(input);
  } else if (action == "unzip") {
    output = decode(input);
  } else {
    usage(argv[0]);
    return 1;
  }
  outputFile << output;
  return 0;
}
