// Copyright 2020 ivan <ikhonyak@gmail.com>

#include <gtest/gtest.h>

#include "Student.h"
#include "fstream"  //файловые потоки

TEST(PrintTable, PrintTable) {
  std::fstream file{"file.json", std::ios::out};

  std::string json_string = R"({
    "items": [
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
    {
      "name": "Sidorov Ivan",
          "group": 31,
          "avg": 4,
          "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
          "group": "IU8-31",
          "avg": 3.33,
          "debt": [
      "C++",
          "Linux",
          "Network"
      ]
    }
    ],
    "_meta": {
      "count": 3
    }
 })";

  file << json_string;
  file.close();

  auto students = parse_file("file.json");
  print(students, std::cout);
  EXPECT_TRUE(true);
}

TEST(Errors, NonExistingFile) {
  std::string exception_string;
  try {
    auto students = parse_file("non/existing/file.json");
  } catch (std::runtime_error &e) {
    exception_string = e.what();
  }
  EXPECT_EQ(exception_string, "non/existing/file.json unable to open json");
}

TEST(Errors, ItemsIsNotArray) {
  std::fstream file{"file.json", std::ios::out};
  std::string exception_string;

  std::string json_string = R"({
    "items":
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
    "_meta": {
      "count": 3
    }
 })";

  file << json_string;
  file.close();

  try {
    auto students = parse_file("file.json");
  } catch (std::runtime_error &e) {
    exception_string = e.what();
  }
  EXPECT_EQ(exception_string, "Items most be array type");
}

TEST(Errors, IncorrectMeta) {
  std::fstream file{"file.json", std::ios::out};
  std::string exception_string;

  std::string json_string = R"({
    "items": [
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
    {
      "name": "Sidorov Ivan",
          "group": 31,
          "avg": 4,
          "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
          "group": "IU8-31",
          "avg": 3.33,
          "debt": [
      "C++",
          "Linux",
          "Network"
      ]
    }
    ],
    "_meta": {
      "count": 123
    }
 })";

  file << json_string;
  file.close();

  try {
    auto students = parse_file("file.json");
  } catch (std::runtime_error &e) {
    exception_string = e.what();
  }
  EXPECT_EQ(exception_string, "meta_: error with count");
}
