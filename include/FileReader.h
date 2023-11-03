#include <fstream>
#include <map>
#include <set>
class FileReader {
  std::ifstream _fstream;

public:
  FileReader(std::string path);
  std::map<std::string, std::string> readSimpleMap();
  std::map<std::string, std::set<std::string>> readMultiMap();
  ~FileReader();
};