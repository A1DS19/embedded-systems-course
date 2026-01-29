#include "vectors_arrays.hpp"
#include <iostream>
#include <vector>

void vectors() {
  std::vector<char> characters = {'a', 'b', 'c'};
  for (char c : characters) {
    std::cout << c << std::endl;
  }
}
