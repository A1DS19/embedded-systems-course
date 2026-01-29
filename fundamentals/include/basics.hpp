/*
C++ 101
*/

#pragma once

#include <cstdint>

#define SUM(n) (n + n)

void hex();
void binary();
void preprocessor();

// ===== ENUMS =====

// Traditional enum
enum LogLevel { DEBUG_LEVEL, INFO_LEVEL, WARNING_LEVEL, ERROR_LEVEL };

// Enum class (strongly typed) - RECOMMENDED
enum class PinMode : uint8_t { INPUT = 0, OUTPUT = 1, INPUT_PULLUP = 2 };

enum class LedState : uint8_t { OFF = 0x00, ON = 0xFF, BLINK = 0x80 };

void enums_demo();

// ===== PERFORMANCE KEYWORDS =====

// constexpr - compile-time evaluation
constexpr int factorial(int n) { return n <= 1 ? 1 : n * factorial(n - 1); }

constexpr uint32_t toBits(uint8_t byte) { return byte; }

// inline - suggest inlining for performance
inline int fastAdd(int a, int b) { return a + b; }

inline uint8_t setPinHigh(uint8_t pin) { return (1 << pin); }

// noexcept - no exceptions, allows optimizations
inline void fastSwap(int &a, int &b) noexcept {
  int temp = a;
  a = b;
  b = temp;
}

void performance_demo();
