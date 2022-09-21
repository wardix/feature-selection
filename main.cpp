#include "parsefile.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {

  const string path = "honeypot.txt";
  parseResultType parseResult;

  // parse input file
  parseFile(path, parseResult);

  // display parse result
  for (attributeMapType attributeMap : parseResult) {
    for (auto const &attr : attributeMap) {
      cout << attr.first << '=' << attr.second << endl;
    }
    cout << endl;
  }

  return EXIT_SUCCESS;
}
