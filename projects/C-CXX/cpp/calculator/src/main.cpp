#include "calculator.h"
#include <iostream>

int main() {
  Calculator calc;
  int a, b;

  std::cout << "give 'a' value: ";
  std::cin >> a;

  std::cout << "give 'b' value: ";
  std::cin >> b;

  std::cout << "Addition: " << calc.add(a, b) << std::endl;
  std::cout << "Substraction: " << calc.substract(a, b) << std::endl;
  std::cout << "multiplication: " << calc.multiply(a, b) << std::endl;
  std::cout << "Divsion: " << calc.divide(a, b) << std::endl;

  return 0;
}
