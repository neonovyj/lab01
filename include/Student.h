//
// Created by ivan on 22.11.2020.
//

#ifndef LAB_01_PARSER_STUDENT_H
#define LAB_01_PARSER_STUDENT_H
#pragma once
#include <any>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <fstream>
#include <sstream>

struct Students {
  std::string Name;
  std::any Group;
  std::any Avg;
  std::any Debt;
};

#endif  // LAB_01_PARSER_STUDENT_H
