#include "memory.hpp"
#include <iostream>
#include <vector>

void memory() {
  struct Player {
    int pos_x_;
    int pos_y_;
    void print() const noexcept {
      std::cout << pos_x_ << ":" << pos_y_ << "\n";
    }
  };

  std::vector<Player *> players;

  Player player_1 = {.pos_x_ = 0, .pos_y_ = 1};

  players.push_back(&player_1);

  for (auto &player : players) {
    player->print();
  }
}
