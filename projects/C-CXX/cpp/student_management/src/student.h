#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
  Student(std::string name, int age, int id);
  std::string getName() const;
  int getAge() const;
  int getId() const;

private:
  std::string name;
  int age;
  int id;
};

#endif
