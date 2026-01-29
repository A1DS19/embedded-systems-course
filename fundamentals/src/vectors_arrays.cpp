#include "vectors_arrays.hpp"
#include <iostream>
#include <vector>

using namespace std;

void vectors() {
  vector<char> characters = {'a', 'b', 'c'};
  for (auto c : characters) {
    cout << c << endl;
  }
}
