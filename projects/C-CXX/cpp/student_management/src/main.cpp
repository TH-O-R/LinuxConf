#include "student.h"
#include "studentManager.h"
#include <cstdio>
#include <iostream>
#include <string>

void displayMenu() {
  std::cout << "\n--- Student Management System ---\n";
  std::cout << "1. Add Student\n";
  std::cout << "2. Remove Student\n";
  std::cout << "3. Display Student\n";
  std::cout << "4. Exit\n";
  std::cout << "Enter your choice: ";
}

int main() {
  StudentManager manager;
  int choice;

  while (true) {
    displayMenu();
    std::cin >> choice;

    if (choice == 1) {
      std::string name;
      int age, id;

      std::cout << "Enter student name: ";
      std::cin.ignore(); // clear the buffer
      std::getline(std::cin, name);
      std::cout << "Enter student age: ";
      std::cin >> age;
      std::cout << "Enter student ID: ";
      std::cin >> id;

      manager.addStudent(Student(name, age, id));
    } else if (choice == 2) {
      int id;
      std::cout << "Enter student ID to remove: ";
      std::cin >> id;
      manager.removeStudent(id);
    } else if (choice == 3) {
      manager.displayStudent();
    } else if (choice == 4) {
      std::cout << "Exiting program.\n";
      break;
    } else {
      std::cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}
