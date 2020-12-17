// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <Student.h>

std::string get_Name(const json &j) { return j.get<std::string>(); }

std::any get_group(const json &j) {
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<int>();
}

std::any get_avg(const json &j) {
  if (j.is_null()) {
    return nullptr;
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else if (j.is_number_float()) {
    return j.get<float>();
  } else {
    return j.get<int>();
  }
}

std::any get_debt(const json &j) {
  if (j.is_null()) {
    return nullptr;
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else {
    return j.get<std::vector<std::string>>();
  }
}

void push_student(const json &j,std::vector<student_t> &result) {
  for (std::size_t i = 0; i < j.size(); i++) {
    student_t student;
    student.name = get_Name(j[i].at("name"));
    student.group = get_group(j[i].at("group"));
    student.avg = get_avg(j[i].at("avg"));
    student.debt = get_debt(j[i].at("debt"));
    result.push_back(student);
  }

}
std::vector<student_t> parse_file(const std::string &filepath) {
  std::fstream file;
  file.open(filepath, std::ios::in);
  if (!file.is_open()) {
    throw std::runtime_error(filepath + " unable to open json");
  }

  json j;
  file >> j;
  file.close();

  if (!j.at("items").is_array()) {
    throw std::runtime_error("Items most be array type");
  }

  if (j.at("items").size() != j.at("_meta").at("count")) {
    throw std::runtime_error("meta_: error with count");
  }
  std::vector<student_t> result;
  push_student(j.at("items"), result);
  return result;
}

void print(const student_t &student, std::ostream &os) {
  os << "| " << std::left << std::setw(name_tablewidth) << student.name;

  if (student.group.type() == typeid(int)) {
    os << "| " << std::setw(group_tablewidth) << std::left
       << std::any_cast<int>(student.group);
  } else {
    os << "| " << std::setw(group_tablewidth) << std::left
       << std::any_cast<std::string>(student.group);
  }

  if (student.avg.type() == typeid(float)) {
    os << "| " << std::setw(avg_tablewidth) << std::left
       << std::any_cast<float>(student.avg);
  } else if (student.avg.type() == typeid(int)) {
    os << "| " << std::setw(avg_tablewidth) << std::left
       << std::any_cast<int>(student.avg);
  } else {
    os << "| " << std::setw(avg_tablewidth) << std::left
       << std::any_cast<std::string>(student.avg);
  }

  if (student.debt.type() == typeid(std::nullptr_t)) {
    os << "| " << std::setw(debt_tablewidth) << std::left << "null"
       << std::right << "|";
  } else if (student.debt.type() == typeid(std::string)) {
    os << "| " << std::setw(debt_tablewidth) << std::left
       << std::any_cast<std::string>(student.debt) << std::right << "|";
  } else {
    os << "| " << std::setw(debt_tablewidth - 5) << std::left
       << std::any_cast<std::vector<std::string>>(student.debt).size()
       << std::left << std::setw(5) << "items" << std::right << "|";
  }
}

std::string do_line(const std::vector<int> &column_widths) {
  std::string result;
  for (const auto &width : column_widths) {
    result += "|-";
    for (int i = 0; i < width; ++i) {
      result += "-";
    }
  }
  result += "|";
  return result;
}

void print(const std::vector<student_t> &students, std::ostream &os) {
  std::string line;
  std::vector<int> widths{name_tablewidth, group_tablewidth, avg_tablewidth,
                          debt_tablewidth};

  line = do_line(widths);
  os << "| " << std::left << std::setw(name_tablewidth) << "name";
  os << "| " << std::left << std::setw(group_tablewidth) << "group";
  os << "| " << std::left << std::setw(avg_tablewidth) << "avg";
  os << "| " << std::left << std::setw(debt_tablewidth) << "debt";
  os << std::right << "|";
  os << std::endl << line << std::endl;
  for (const auto &student : students) {
    print(student, os);
    os << std::endl << line << std::endl;
  }
}
