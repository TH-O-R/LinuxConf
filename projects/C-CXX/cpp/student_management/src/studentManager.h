#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "student.h"
#include <vector>

class StudentManager {
public:
  void addStudent(const Student &student);
  void removeStudent(int id);
  void displayStudent() const;

private:
  std::vector<Student> students;
};

#endif
