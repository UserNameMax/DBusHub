#include "../include/FileWriter.h"
#include <fstream>
#include <map>
FileWriter::FileWriter(std::string path) { _fstream = std::ofstream(path); }
FileWriter::~FileWriter() { _fstream.close(); }
void FileWriter::writeSimpleMap(std::map<std::string, std::string> map) {
  for (auto pair : map) {
    _fstream << pair.first << ": " << pair.second << "\n";
  }
}
void FileWriter::writeMultiMap(
    std::map<std::string, std::set<std::string>> map) {
  for (auto pair : map) {
    _fstream << pair.first << ": ";
    for (auto item : pair.second) {
      _fstream << item << " ";
    }
    _fstream << "\n";
  }
}