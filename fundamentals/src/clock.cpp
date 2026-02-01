#include "clock.hpp"
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <iostream>

void my_clock() {
  clock_t curr_time, start_time, end_time;
  uint8_t count = 0;

  while (1) {
    start_time = clock();
    printf("\nTick...");

    while ((clock() - start_time) < 3 * CLOCKS_PER_SEC)
      ;

    count++;

    if (count == 3) {
      std::cout << "done: " << count << std::endl;
      break;
    }
  }
}
