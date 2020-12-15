// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <Student.h>

#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>

using nlohmann::json;
const int name_tablewidth = 15;
const int group_tablewidth = 8;
const int avg_tablewidth = 5;
const int debt_tablewidth = 8;
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

void from_json(const json &j,
               student_t &s) {  //иницализирует структуру из джейсона
  s.name = get_Name(j.at("name"));  //оператор at - обращение по ключу
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}

std::vector<student_t> parse_file(const std::string &filepath) {
  std::fstream file;  //чтение файла
  file.open(filepath, std::ios::in);
  if (!file.is_open()) {  //тру еси файл отрклся, фолс если не отркылся
    throw std::runtime_error(filepath +" unable to open json");
  }  //программа остановится, если сработало исключение передаст исключение
     //назад по
  //функциям, если никто не обрабатывает, то исключение
  //остановит программу

  json j;
  file >> j;
  file.close();

  if (!j.at("items").is_array()) {  // виды исключений: logic_error
                                    // runtime_error invalid_argument
    throw std::runtime_error("Items most be array type");
  }

  if (j.at("items").size() !=
      j.at("_meta").at(
          "count")) {  //мы сравниваем значение массива с ключом каунт из меты
    throw std::runtime_error("meta_: error with count");
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

  std::vector<int> widths{name_tablewidth, group_tablewidth, avg_tablewidth,
                          debt_tablewidth};

  separator = create_separator(widths);

  os << "| " << std::left << std::setw(name_tablewidth) << "name";
  os << "| " << std::left << std::setw(group_tablewidth) << "group";
  os << "| " << std::left << std::setw(avg_tablewidth) << "avg";
  os << "| " << std::left << std::setw(debt_tablewidth) << "debt";
  os << std::right << "|";
  os << std::endl << separator << std::endl;
  for (const auto &student : students) {
    print(student, os);
    os << std::endl << separator << std::endl;
  }
}
