#include "memory.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

void memory() {
  const char *source = "hello world";
  char *destination = (char *)malloc(strlen(source) + 1);

  memcpy(destination, source, strlen(source) + 1);
  printf("\n%s", destination);

  char source_2[5] = "1234";
  const int source_2_len = strlen(source_2) + 1;
  char destination_2[source_2_len];
  memcpy(destination_2, source_2, source_2_len);
  printf("\n%s", destination_2);
}
