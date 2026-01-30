#include "clock.hpp"
#include <cstdio>
#include <ctime>

void my_clock() {
  clock_t curr_time, start_time, end_time;

  while (1) {
    start_time = clock();
    printf("\nTick...");

    while ((clock() - start_time) < 3 * CLOCKS_PER_SEC)
      ;
  }
}
