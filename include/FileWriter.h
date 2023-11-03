#include <fstream>
#include <map>
#include <set>
#include <string>
class FileWriter {
  std::ofstream _fstream;

public:
  FileWriter(std::string path);
  void writeSimpleMap(std::map<std::string, std::string> map);
  void writeMultiMap(std::map<std::string, std::set<std::string>> map);
  ~FileWriter();
};