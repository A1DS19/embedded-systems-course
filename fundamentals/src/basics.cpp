#include "basics.hpp"
#include <cstdio>
#include <iostream>

void hex() {
  /*
   0x123 is hexadecimal notation:
    - 1 is in the 16² place = 1 × 256 = 256
    - 2 is in the 16¹ place = 2 × 16 = 32
    - 3 is in the 16⁰ place = 3 × 1 = 3
    - Total: 256 + 32 + 3 = 29
  */

  int hex_number = 0X123;
  std::cout << hex_number << std::endl;
}

void binary() {
  /*
   For getting the binary number from decimal we must devide the number
   from its value/2 until we get 0.

   2/100  0
   2/50   0
   2/25   1
   2/12   0
   2/6    0
   2/3    1
   2/1    1

   Result = 1100100
*/

  int binary_number = 0b1100100;
  std::cout << binary_number << std::endl;
}

void preprocessor() {
  int result = SUM(500);
  printf("%d", result);
}
