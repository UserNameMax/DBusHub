#include "../include/FileReader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
FileReader::FileReader(std::string path) { _fstream = std::ifstream(path); }
FileReader::~FileReader() {
  if (_fstream.is_open())
    _fstream.close();
}
std::map<std::string, std::string> FileReader::readSimpleMap() {
  if (!_fstream.is_open()) {
    return std::map<std::string, std::string>();
  }
  std::map<std::string, std::string> result;
  std::string line;
  while (!_fstream.eof()) {
    std::getline(_fstream, line);
    std::string key = line.substr(0, line.find(": "));
    line.erase(0, line.find(": ") + 2);
    result.insert(std::pair(key, line));
  }
  return result;
};
std::map<std::string, std::set<std::string>> FileReader::readMultiMap() {
  if (!_fstream.is_open()) {
    return std::map<std::string, std::set<std::string>>();
  }
  std::map<std::string, std::set<std::string>> result;
  std::string line;
  while (!_fstream.eof()) {
    std::getline(_fstream, line);
    std::string key = line.substr(0, line.find(": "));
    line.erase(0, line.find(": ") + 2);
    std::set<std::string> value;
    while (line.find(" ") + 1 > 0) {
      value.insert(line.substr(0, line.find(" ")));
      line.erase(0, line.find(" ") + 1);
    }
    result.insert(std::pair(key, value));
  }
  return result;
};