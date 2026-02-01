#include "data_structures.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <string>

static constexpr uint8_t MAX_MOVIES = 1;
static constexpr float MAX_MOVIE_DURATION = 2000.0F;

struct Movie {
  std::string name_;
  float duration_;
  void print() const noexcept {
    std::cout << name_ << ":" << duration_ << "\n";
  }
};

static void structs() {
  std::array<Movie, MAX_MOVIES> movies;

  movies[0] = {.name_ = "memes", .duration_ = MAX_MOVIE_DURATION};

  for (auto &movie : movies) {
    movie.print();
  }
}

static void unions() {
  union Power {
    int8_t low_power_;
    int8_t high_power_;
  };
}

void data_structures() {
  structs();
  unions();
}
