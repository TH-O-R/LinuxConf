#include "studentManager.h"
#include <algorithm>
#include <cstdio>
#include <iostream>

void StudentManager::addStudent(const Student &student) {
  students.push_back(student);
}

void StudentManager::removeStudent(int id) {
  auto it = std::remove_if(students.begin(), students.end(),
                           [id](const Student &s) { return s.getId() == id; });
  students.erase(it, students.end());
}

void StudentManager::displayStudent() const {
  if (students.empty()) {
    std::cout << "No students available.\n";
    return;
  }

  for (const auto &student : students) {
    std::cout << "ID: " << student.getId() << ", Name: " << student.getName()
              << ", Age: " << student.getAge() << std::endl;
  }
}
