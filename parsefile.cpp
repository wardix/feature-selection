#include "parsefile.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define STATE_INIT 0
#define STATE_RECORD_START 1
#define STATE_ATTRIBUTE_START 2
#define STATE_ATTRIBUTE_END 3
#define STATE_ATTRIBUTE_SEPARATOR 4
#define STATE_VALUE_STRING_START 5
#define STATE_VALUE_NUMBER_START 6
#define STATE_VALUE_END 7
#define STATE_NEXT_ATTRIBUTE 8
#define STATE_RECORD_END 9

void parseFile(const string path, parseResultType &result) {
  attributeMapType attributeMap;
  string attribute, value, buffer = "";
  char byte = 0;
  int state = STATE_INIT;
  const string number = "0123456789.";
  const string whiteSpace = " \t\r\n";

  ifstream inputFile(path);
  if (!inputFile.is_open()) {
    cerr << "Could not open the file " << path << endl;
    exit(EXIT_FAILURE);
  }
  while (inputFile.get(byte)) {
    if (state == STATE_INIT) {
      if (byte == '{') {
        state = STATE_RECORD_START;
      }
      continue;
    }
    if (state == STATE_RECORD_START) {
      if (byte == '"') {
        state = STATE_ATTRIBUTE_START;
      }
      continue;
    }
    if (state == STATE_ATTRIBUTE_START) {
      if (byte == '"') {
        state = STATE_ATTRIBUTE_END;
        attribute = buffer;
        buffer = "";
        continue;
      }
      buffer.push_back(byte);
      continue;
    }
    if (state == STATE_ATTRIBUTE_END) {
      if (byte == ':') {
        state = STATE_ATTRIBUTE_SEPARATOR;
      }
      continue;
    }
    if (state == STATE_ATTRIBUTE_SEPARATOR) {
      if (byte == '"') {
        state = STATE_VALUE_STRING_START;
        continue;
      }
      if (number.find(byte) != string::npos) {
        state = STATE_VALUE_NUMBER_START;
        buffer.push_back(byte);
      }
      continue;
    }
    if (state == STATE_VALUE_STRING_START) {
      if (byte == '"') {
        state = STATE_VALUE_END;
        value = buffer;
        attributeMap[attribute] = value;
        buffer = "";
        continue;
      }
      buffer.push_back(byte);
      continue;
    }
    if (state == STATE_VALUE_NUMBER_START) {
      if (byte == ',') {
        state = STATE_NEXT_ATTRIBUTE;
        value = buffer;
        attributeMap[attribute] = value;
        buffer = "";
        continue;
      }
      if (byte == '}') {
        state = STATE_RECORD_END;
        value = buffer;
        attributeMap[attribute] = value;
        buffer = "";
        continue;
      }
      if (whiteSpace.find(byte) != string::npos) {
        state = STATE_VALUE_END;
        value = buffer;
        attributeMap[attribute] = value;
        buffer = "";
        continue;
      }
      buffer.push_back(byte);
      continue;
    }
    if (state == STATE_VALUE_END) {
      if (byte == ',') {
        state = STATE_NEXT_ATTRIBUTE;
        continue;
      }
      if (byte == '}') {
        state = STATE_RECORD_END;
        result.push_back(attributeMap);
      }
      continue;
    }
    if (state == STATE_NEXT_ATTRIBUTE) {
      if (byte == '"') {
        state = STATE_ATTRIBUTE_START;
      }
      continue;
    }
    if (state == STATE_RECORD_END) {
      if (byte == '{') {
        state = STATE_RECORD_START;
      }
    }
  }
  inputFile.close();
}
