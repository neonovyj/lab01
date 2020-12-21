// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <Student.h>
//тк мы не знаем, что представляет собой json поэтому передаем все в any с помощью get функций, которые позволяют получить доступ к полям в json
std::string get_Name(const json &j) { //any- контейнер, в кот. хранятся любое значение, не заботясь о безопасности типов .
  return j.get<std::string>(); //Name - всегда string, поэтому преобразовываем только в string
}
std::any get_group(const json &j) {// any от auto отличается тем, что any можно переназначить
  if (j.is_string()) //group может быть и string и int, поэтому get group проверяет, какой тип хранится в json
    return j.get<std::string>(); //и исходя из этого записывает его в any
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

void push_student(const json &j, std::vector<student_t> &result) {
  for (std::size_t i = 0; i < j.size(); i++) {
    student_t student; //инициализация student, которого мы записываем в массив result
    student.name = get_Name(j[i].at("name")); //at-оператор, служит для обращения по ключу, если значение ключа вне диапозона, то исключение
    student.group = get_group(j[i].at("group")); //обращаемся к items и с помощью get возвращаем вектор студентов
    student.avg = get_avg(j[i].at("avg"));
    student.debt = get_debt(j[i].at("debt"));
    result.push_back(student); //добавление нового элемента в конец вектора
  }
}
std::vector<student_t> parse_file(const std::string &filepath) {
  std::fstream file; //c помощью fstream происходит чтение данных их файла, файловый ввод
  file.open(filepath, std::ios::in); //std::ios::in - флаг на то, что из этого файла идет чтение
  if (!file.is_open()) { //проверяем,открыт ли файл !!! Требование проверки, есть ли аргумент, который указывае путь до файла
    throw std::runtime_error(filepath + " unable to open json"); //если нет, выбрасываем исключение, программа остановится
  } //Требование, существует ли файл

  json j; //объявляем наш json файл?
  file >> j;
  file.close();

  if (!j.at("items").is_array()) { //Требование, что все элементы образуют массив
    throw std::runtime_error("Items most be array type"); // runtime_error - базовое исключение,которое бросается во время выполнения программы.
  }

  if (j.at("items").size() != j.at("_meta").at("count")) { //Требование: сравниваем значение с ключом из meta
    throw std::runtime_error("meta_: error with count");
  }
  std::vector<student_t> result;
  push_student(j.at("items"), result); //вызываем метод push_student
  return result;
}

void print(const student_t &student, std::ostream &os) { //ostream для записи в поток
  os << "| " << std::left << std::setw(name_tablewidth) << student.name; // тут используются манипуляторы
//Манипулятор — это объект, который применяется для изменения потока данных с использованием операторов извлечения (>>) или вставки (<<).
  if (student.group.type() == typeid(int)) { //setw() - используется для ограничения количества символов, считываемых из потока.
    os << "| " << std::setw(group_tablewidth) << std::left //выводимое поле выравниваем по левому краю
       << std::any_cast<int>(student.group); //если поле не занимает ширину полностью, мы заполняем его пробелами
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
