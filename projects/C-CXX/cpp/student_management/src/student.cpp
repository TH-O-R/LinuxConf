#include "student.h"

Student::Student(std::string name, int age, int id)
    : name(name), age(age), id(id) {}

std::string Student::getName() const { return name; }

int Student::getAge() const { return age; }

int Student::getId() const { return id; }
