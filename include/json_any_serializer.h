//
// Created by ivan on 03.12.2020.
//

#ifndef LAB_01_PARSER_JSON_ANY_SERIALIZER_H
#define LAB_01_PARSER_JSON_ANY_SERIALIZER_H

#include <any>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
//эни спец класс который может быть чем угодно часто используется для парсинга.
namespace nlohmann {
template <> //++статич типизированный язык. все типы переменных должны быть известны. template является шаблоном класса.
struct adl_serializer<std::any> {
  //ту джейсон объясняем как класс эни перобразовать в джейсон
  //Проверяет явл наш эни строкой. если явл преобраз эни в джейсон
  static void to_json(json &j, const std::any &a_any) { //объясняем функции как преобразов в эни
    if (a_any.type() == typeid(std::string)) { //тайпайди возвращает числовой индекс типа
      j = std::any_cast<std::string>(a_any);
    } else if (a_any.type() == typeid(int)) { //смотрим явл ли интом
      j = std::any_cast<int>(a_any);
    } else if (a_any.type() == typeid(float)) { //Если у нас в эни хранится массив
      j = std::any_cast<float>(a_any);
    } else if (a_any.type() == typeid(std::vector<std::string>)) {
      j = std::any_cast<std::vector<std::string>>(a_any);
    } else {
      j = nullptr; // надо научить рабоать только с теми типами кот нужны, если эни не явл нужным нам типом, то тут будет ноль и он нам не нужен
    }
  }

  static void from_json(const json &j, std::any &a_any) { //из готового джейсона делает эни
    //смотрим какой тип хранится в джейсоне и отдаем этот тип эни
    if (j.is_string()) {
      a_any = j.get<std::string>();
    } else if (j.is_number_integer()) {
      a_any = j.get<int>();
    } else if (j.is_number_float()) {
      a_any = j.get<float>();
    } else if (j.is_null()) {
      a_any = nullptr;
    } else if (j.is_array()) {
      std::vector<std::string> v;
      for (json::const_iterator i = j.cbegin(); i != j.cend(); i++) {
        v.push_back(i.value());
      }
      a_any = v;
    }
  }
};
}  // namespace nlohmann

#endif  // LAB_01_PARSER_JSON_ANY_SERIALIZER_H
