//
// Created by ivan on 22.11.2020.
//

#include "jsonparser.h"

jsonparser jsonparser::FromFile(const string& jsonPath) {
  std::cout << "Read JSON file and processes it\n";
  std::ifstream file(jsonPath);
  if (!file) {
    throw std::runtime_error{"unable to open file"};
  }
  json data;
  file >> data;
  if (data.empty()){
    throw std::runtime_error
        {"file is empty"};
  }


