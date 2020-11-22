//
// Created by ivan on 22.11.2020.
//

#ifndef LAB_01_PARSER_STUDENT_H
#define LAB_01_PARSER_STUDENT_H


#include <any>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
using string = std :: string;
using any = std :: any;
using std :: cout;
using std :: setw;
using std :: runtime_error;
using std :: setfill;
using std :: any_cast;

const string FieldName[4] = {"name", "group", "avg", "debt"};

struct Student {
 public:
  enum Type {
    Null,
    String,
    Integer,
    Array,
    Double};

  explicit Student(json);

  explicit Student(string, any, any, any);

  bool operator==(const Student&) const;

  string ToString(const string&) const;

  auto GetType(const string&) const -> Type;

  auto GetField(const string&) const -> any;

 private:
  string name;
  any group;
  any avg;
  any debt;

  Type name_type = String;
  Type group_type;
  Type avg_type;
  Type debt_type;
};

#endif  // LAB_01_PARSER_STUDENT_H
