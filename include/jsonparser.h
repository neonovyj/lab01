//
// Created by ivan on 22.11.2020.
//

#ifndef LAB_01_PARSER_JSONPARSER_H
#define LAB_01_PARSER_JSONPARSER_H

#pragma once
#include <any>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

#include <iomanip>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
using namespace std;//господипрости

class jsonparser {
 public:

  static jsonparser FromFile(const string&);

};
#endif // INCLUDE_JSONPARSER_HPP_