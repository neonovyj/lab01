#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <any>
#include <nlohmann/json.hpp>
#include <ostream>
#include <string>
#include <vector>

using nlohmann::json;

struct Student {
  explicit Student(const json &j); //конструктор- метод проводящий стартовую инициализацию
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

std::vector<Student> LoadFromFile(const std::string &filepath); //из файла функция читает файл джисон и формирует структуру студентов



void PrintTable(const std::vector<Student> &students, std::ostream &out);

//оборачив в себя некрасив функции джейсона чтобы не писать лишний код, код красивее становится
//статик если функцию объявили где то, то при лок связывании (include) эту функцию не можем больше нигде использовать, только тут и в source
std::string getName(const json &j); //из объекта джейсона должна вернуть строкй с именем
std::any getGroup(const json &j);
std::any getAvg(const json &j);
std::any getDebt(const json &j);

#endif  // INCLUDE_HEADER_HPP_
