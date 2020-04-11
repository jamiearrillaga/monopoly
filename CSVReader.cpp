//
// Created by mfbut on 1/20/2018.
//

#include <string>
#include "CSVReader.h"
#include <sstream>

Monopoly::CSVReader::CSVReader(const std::string& fileName) : file(fileName), fileName(fileName) {

}

Monopoly::CSVReader::~CSVReader() {
  if (file.is_open()) {
    file.close();
  }
}

/**
 * Read the next field from the csv file and give it back as a string
 * @return
 */
std::string Monopoly::CSVReader::get_next_field() {
  std::string field;
  char c;
  while (file.get(c)) {
    if (c == ',' || c == '\n') {
      break;
    } else {
      field.push_back(c);
    }
  }

  return field;
}

/**
 * Read the next field from the stream as an int
 * @return
 */
int Monopoly::CSVReader::get_next_field_as_int() {

  int num;
  std::stringstream field(get_next_field());
  field >> num;

  return num;
}

/**
 * Read characters from the file until one of the stop characters is encountered
 * @param stopChars
 */
void Monopoly::CSVReader::skip_until(const std::string& stopChars) {
  char c;
  while (file.get(c)) {
    //if we found one of the stop characters

    if (stopChars.find_first_of(c) != std::string::npos) {
      break; //stop searching
    }
  }
}

/**
 * Skip the next field in the file
 */
void Monopoly::CSVReader::skip_field() {
  skip_until(",\n");
}

/**
 * Skip the next line of the file
 */
void Monopoly::CSVReader::skip_line() {
  skip_until("\n");
}

bool Monopoly::CSVReader::good() const {
  return file.good();
}

const std::string& Monopoly::CSVReader::getFileName() const {
  return fileName;
}
