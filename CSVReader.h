#ifndef HOARDINGCPPVERSION_CSVREADER_H
#define HOARDINGCPPVERSION_CSVREADER_H

#include <fstream>
#include <string>
namespace Monopoly {

class CSVReader {
 public:
  CSVReader(const std::string& fileName);
  virtual ~CSVReader();

  std::string get_next_field();
  int get_next_field_as_int();

  void skip_until(const std::string& stopChars);
  void skip_field();
  void skip_line();

  bool good() const;

  const std::string& getFileName() const;

 private:
  std::ifstream file;
  std::string fileName;
};
}

#endif //HOARDINGCPPVERSION_CSVREADER_H
