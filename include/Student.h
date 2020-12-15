// Copyright 2020 ivan <ikhonyak@gmail.com>
#ifndef INCLUDE_STUDENT_H_
#define INCLUDE_STUDENT_H_

#include <any>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using nlohmann::json;

const int name_tablewidth = 15;
const int group_tablewidth = 9;
const int avg_tablewidth = 5;
const int debt_tablewidth = 8;

struct student_t {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};
void print(const student_t &student, std::ostream &os);
void print(const std::vector<student_t> &students, std::ostream &os);
std::vector<student_t> parse_file(const std::string &filepath);

#endif  // INCLUDE_STUDENT_H_
