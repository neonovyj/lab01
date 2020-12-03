//
// Created by ivan on 22.11.2020.
//

#include "Student.h"
//мы не знаем, что предствялет собой джейсон

//все гет функции оборачив в себя некрасив функции джейсона чтобы не писать лишний код, код красивее становится
//гет функции из джейсона преобразуют в объект эни
std::string getName(const json &j) { return j.get<std::string>(); } //знаем что название-строка и преобр в строку

std::any getGroup(const json &j) { //не знаем чем является джейсон поэтому достаем либо число либо строку и отдаем эни
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<int>();
}

std::any getAvg(const json &j) {
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

std::any getDebt(const json &j) {
  if (j.is_null()) {
    return nullptr;
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else {
    return j.get<std::vector<std::string>>();
  }
}

Student::Student(const json &j) { //эта структура выполняет парсинг
  name = getName(j);
  group = getGroup(j);
  avg = getAvg(j);
  debt = getDebt(j);
}