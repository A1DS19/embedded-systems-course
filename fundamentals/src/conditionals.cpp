#include "conditionals.hpp"
#include <cstdio>

void conditionals() {
  static constexpr int health = 50;

  switch (health) {
  case MAX_PLAYER_HEALTH:
    printf("%s", "max health active");
    break;
  case MIN_PLAYER_HEALTH:
    printf("\n%s", "min player health active");
    break;
  case LOW_PLAYER_HEALTH:
    printf("\n%s", "low player health active");
    break;
  default:
    printf("\n%s", "memes");
    break;
  }
}
