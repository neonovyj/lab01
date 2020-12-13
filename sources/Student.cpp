// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <Student.h>

#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>

using nlohmann::json;
//мы не знаем, что предствялет собой джейсон

//все гет функции оборачив в себя некрасив функции джейсона чтобы не писать
//лишний код, код красивее становится гет функции из джейсона преобразуют в
//объект эни
std::string get_Name(const json &j) { return j.get<std::string>(); }
//знаем что название-строка и преобр в строку

//не знаем чем является джейсон поэтому достаем либо число
//либо строку и отдаем эни
std::any get_group(const json &j) {  //гет групп проверяет какой тип хранится в
                                     //джейсоне смотрит какой тип и исходя из
                                     //типа в джейсоне записывает в эни
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
    return nullptr;  //нулптр это ключевое слово, а NULL это макрос
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else {
    return j.get<std::vector<std::string>>();
  }
}

void from_json(const json &j, student_t &s) {
  s.name = get_Name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}

std::vector<student_t> parse_file(
    const std::string &filepath) {  //то же самое что и лоад фром файл
  std::fstream file;
  file.open(filepath, std::ios::in);
  if (!file.is_open()) {  //тру еси файл отрклся, фолс если не отркылся
    throw std::runtime_error(filepath + " not open");  //запускаем исключение
  }  //программа остановится, передаст исключение назад по
  //функциям, если никто не обрабатывает, то исключение
  //остановит программу

  json j;
  file >> j;
  file.close();

  if (!j.at("items").is_array()) {
    throw std::runtime_error("Items most be array type");
  }

  if (j.at("items").size() !=
      j.at("_meta").at(
          "count")) {  //мы сравниваем значение массива с ключом каунт из меты
    throw std::runtime_error(
        "meta_: count and items size mismatch");  //перефразировать
  }

  std::vector<student_t> result;

  for (std::size_t i = 0; i < j.at("items").size();
       i++) {  // std::size_t макрос который принято использовать для
               // обозначения размера. Возвращает размер этого массива.
    auto student =
        j.at("items")[i]
            .get<student_t>();  //создаем студента из массива. воид джейсон
                                //является сиреализатором, авто автоматический
                                //вывод типов, компилятор сам заменяет на нужный
                                //тип
    result.push_back(student);  //студента, кот создали запихиваем в вектор,
                                //который мы должны получить. Добавляем элемент,
                                //чтобы Сделать массив структур студента
  }
  return result;
}

//заменить цифры на константы
// name_column_width = 14
const int name_column_width = 14;
const int group_column_width = 10;
const int avg_column_width = 5;
const int debt_column_width = 10;

void print(const student_t &student, std::ostream &os) {
  os << "| " << std::left << std::setw(name_column_width) << student.name;

  if (student.group.type() == typeid(int)) {
    os << "| " << std::setw(group_column_width) << std::left
       << std::any_cast<int>(student.group);
  } else {
    os << "| " << std::setw(group_column_width) << std::left
       << std::any_cast<std::string>(student.group);
  }

  if (student.avg.type() == typeid(float)) {
    os << "| " << std::setw(avg_column_width) << std::left
       << std::any_cast<float>(student.avg);
  } else if (student.avg.type() == typeid(int)) {
    os << "| " << std::setw(avg_column_width) << std::left
       << std::any_cast<int>(student.avg);
  } else {
    os << "| " << std::setw(avg_column_width) << std::left
       << std::any_cast<std::string>(student.avg);
  }

  if (student.debt.type() == typeid(std::nullptr_t)) {
    os << "| " << std::setw(debt_column_width) << std::left << "null"
       << std::right << "|";
  } else if (student.debt.type() == typeid(std::string)) {
    os << "| " << std::setw(debt_column_width) << std::left
       << std::any_cast<std::string>(student.debt) << std::right << "|";
  } else {
    os << "| " << std::setw(debt_column_width - 5) << std::left
       << std::any_cast<std::vector<std::string>>(student.debt).size()
       << std::left << std::setw(5) << "items" << std::right << "|";
  }
}

std::string create_separator(const std::vector<int> &column_widths) {
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
  std::string separator;

  std::vector<int> widths{name_column_width, group_column_width,
                          avg_column_width, debt_column_width};

  separator = create_separator(widths);

  os << "| " << std::left << std::setw(name_column_width) << "name";
  os << "| " << std::left << std::setw(group_column_width) << "group";
  os << "| " << std::left << std::setw(avg_column_width) << "avg";
  os << "| " << std::left << std::setw(debt_column_width) << "debt";
  os << std::right << "|";
  os << std::endl << separator << std::endl;
  for (const auto &student : students) {
    print(student, os);
    os << std::endl << separator << std::endl;
  }
}
