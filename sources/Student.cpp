//
// Created by ivan on 22.11.2020.
//

#include "Student.h"

#include "fstream"

//мы не знаем, что предствялет собой джейсон

//все гет функции оборачив в себя некрасив функции джейсона чтобы не писать
//лишний код, код красивее становится гет функции из джейсона преобразуют в
//объект эни
std::string getName(const json &j) {
  return j.get<std::string>();
}  //знаем что название-строка и преобр в строку

std::any getGroup(
    const json &j) {  //не знаем чем является джейсон поэтому достаем либо число
                      //либо строку и отдаем эни
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
std::vector<Student> LoadFromFile(const std::string &filepath) {
  std::fstream file;  // fstream инпут файл стрим, создаем объект ст потока
  file.open(filepath, std::ios::in);  //отркываем файл по пути файлпас, с флагом
                                      //иос ин, который гооврит
  if (!file.is_open())  //тру еси файл отрклся, фолс если не отркылся и
                        //запускаем исключение
    throw std::runtime_error(
        filepath +
        "not open");  //программа остановится, передаст исключение назад по
                      //функциям, если никто не обрабатывает, то исключение
                      //остановит программу
  json j;
  file >> j;
  file.close();

  std::vector<Student> result;

  if (!j.at("items").is_array()) {
    throw std::runtime_error("Items most be array type");
  }

  if (j.at("items").size() != j.at("_meta").at("count")) { //мы сравниваем значение массива с ключом каунт из меты
    throw std::runtime_error("meta_: count and items size mismatch"); //перефразировать
  }

  for (std::size_t i = 0; i < j.at("items").size(); i++) {//std::size_t макрос который принято использовать для обозначения размера. Возвращает размер этого массива.
    Student student(j.at("items")[i]);//создаем студента из массива
    result.push_back(student);//студента, кот создали запихиваем в вектор, который мы должны получить. Добавляем элемент, чтобы Сделать массив структур студента
  }

  return result;
}
//по ключу мы получаем значение из джейсона
// возращает гет нейм переводит из джейсона в строку, метод at- обращение по
// ключу
Student::Student(const json &j) {  //эта структура выполняет парсинг
  name = getName(j.at("name"));
  group = getGroup(j.at("group"));
  avg = getAvg(j.at("avg"));
  debt = getDebt(j.at("debt"));
}

//
void Student::PrintName(std::ostream &out) const { out << name; } //мы знаем что имя строка в аут отдаем просто имя

void Student::PrintDebt(std::ostream &out) const { //вывод долгов, они могут бть строкой либо массивом строк либо нуль
  if (debt.type() == typeid(std::string)) { //если в дебт который явл эни то
    out << std::any_cast<std::string>(debt); //этой функцией приводим к строке и выводим( в скобочках что нужно преобразов в треугольных то к чему нужно преобразовать
  } else if (debt.type() == typeid(std::vector<std::string>)) { //если массив строк, то берем размер массива и выводим кол во значений
    out << std::any_cast<std::vector<std::string>>(debt).size() << " items";
  } else if (debt.type() == typeid(std::nullptr_t)) { //сравниваем тип значений хранящийся в поле дэбт в стд эни с типом нульптр дэбт (которым когда долгов нет)если совпадает мы выводим ноне
    out << "null";
  }
  }


void Student::PrintAvg(std::ostream &out) const {
  if (avg.type() == typeid(int)) {
    out << std::any_cast<int>(avg);
  } else if (avg.type() == typeid(float)) {
    out.precision(3); //чтобы из флоат не выводит больше трех значений после точки, ограничиваем средний балл
    out << std::any_cast<float>(avg);//any_cast преобразует в данном случае ко флоат
    //out.precision(0);
  } else if (avg.type() == typeid(std::string)) {
    out << std::any_cast<std::string>(avg);
  }
}

void Student::PrintGroup(std::ostream &out) const {
  if (group.type() == typeid(int)) {
    out << std::any_cast<int>(group);
  } else if (group.type() == typeid(std::string)) {
    out << std::any_cast<std::string>(group);
  }
}