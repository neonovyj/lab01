// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "Student.h"
TEST(Example, EmptyTest) {
  std::vector<Student> students;
  try {
    students =LoadFromFile("test.json");
  }
  catch (std::runtime_error &e)
  {
    std::cout << "исключение: " << e.what() << std::endl;
    return;
  }
  for (std::size_t i = 0; i < students.size(); i++)
  {
    students[i].PrintName(std::cout);
    std::cout << " ";
    students[i].PrintGroup(std::cout);
    std::cout << " ";
    students[i].PrintAvg(std::cout);
    std::cout << " ";
    students[i].PrintDebt(std::cout);
    std::cout << std::endl;
  }
    EXPECT_TRUE(true);
  }



