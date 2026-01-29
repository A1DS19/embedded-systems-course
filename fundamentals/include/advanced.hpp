/*
Advanced C++ - Keyword Combinations
*/

#pragma once

#include <cstdint>

// ===== CONSTEXPR VARIABLES =====
// USE CASE: Constants that never change - evaluated at compile-time
// BENEFIT: Zero runtime cost, stored in read-only memory

// Good - with explicit type
constexpr int MAX_BUFFER_SIZE = 256;
constexpr uint8_t MAX_PINS = 64;
constexpr uint32_t CLOCK_SPEED = 16000000; // 16 MHz
constexpr float PI = 3.14159f;

// Good - with auto deduction (C++11+)
constexpr auto TIMEOUT_MS = 1000;
constexpr auto BAUD_RATE = 9600;

// ===== SIMPLE MATH CLASS =====

class Math {
public:
  // constexpr: Can evaluate at compile-time OR runtime (flexible!)
  // const: Doesn't modify member variables (read-only function)
  // noexcept: Never throws exceptions (enables optimizations)
  // USE CASE: Pure math functions with no side effects
  constexpr int square(int x) const noexcept { return x * x; }

  constexpr int cube(int x) const noexcept { return x * x * x; }

  // constexpr works with loops since C++14
  constexpr int power(int base, int exp) const noexcept {
    int result = 1;
    for (int i = 0; i < exp; i++) {
      result *= base;
    }
    return result;
  }

  // inline: Suggests compiler to insert code directly (avoid function call)
  // noexcept: No exceptions
  // NOT const: Modifies the parameters passed by reference
  // USE CASE: Small, frequently called functions that modify data
  inline void swap(int &a, int &b) noexcept {
    int temp = a;
    a = b;
    b = temp;
  }

  // Static constexpr: Class-level constants, accessible without instance
  // USE CASE: Mathematical constants, configuration values
  static constexpr double E = 2.71828;
  static constexpr double GOLDEN_RATIO = 1.61803;
};

// ===== MICROCONTROLLER SIMULATION CLASS =====

class MicroController {
public:
  // constexpr constructor: Can create objects at compile-time
  // noexcept: No exceptions during construction
  constexpr MicroController() noexcept : pins(0), portA(0), portB(0) {}

  // WHY constexpr? Works in BOTH contexts:
  // 1. Compile-time: constexpr MicroController mcu; mcu.digitalRead(13);
  // 2. Runtime: mcu.digitalRead(userInput);
  // BENEFIT: One function, dual use - compiler optimizes compile-time calls
  //
  // const: Doesn't modify member variables (read-only)
  // noexcept: No exceptions
  constexpr uint8_t digitalRead(uint8_t pin) const noexcept {
    return (pins >> pin) & 0x01;
  }

  // NOT const: Modifies member variable 'pins'
  // Still constexpr: Can be used at compile-time if object is not const
  // USE CASE: Modify state but allow compile-time evaluation when possible
  constexpr void digitalWrite(uint8_t pin, bool value) noexcept {
    if (value) {
      pins |= (1 << pin); // Set bit
    } else {
      pins &= ~(1 << pin); // Clear bit
    }
  }

  // const: Pure calculation, doesn't need to read member variables
  // USE CASE: Static helper functions that don't need object state
  constexpr uint8_t setPinHigh(uint8_t pin) const noexcept {
    return (1 << pin);
  }

  constexpr uint8_t setPinLow(uint8_t pin) const noexcept {
    return ~(1 << pin);
  }

  // const: Only reads member variables, doesn't modify
  constexpr bool isPinHigh(uint8_t pin) const noexcept {
    return (pins & (1 << pin)) != 0;
  }

  // inline: Small getter functions - avoid function call overhead
  // const: Read-only access to member variables
  inline uint64_t getPins() const noexcept { return pins; }

  // NOT const: Modifies member variable
  inline void reset() noexcept { pins = 0; }

  // Static constexpr: Class constants, no object needed
  // USE CASE: Hardware specifications, compile-time configuration
  static constexpr uint8_t TOTAL_PINS = 64;
  static constexpr uint32_t DEFAULT_CLOCK = 16000000;
  static constexpr uint8_t PWM_PINS = 6;

private:
  uint64_t pins;
  uint8_t portA;
  uint8_t portB;
};

// ===== FREE FUNCTIONS WITH COMBINATIONS =====
// YES! All these keywords work OUTSIDE classes too!

// constexpr: Compile-time if input is constant, runtime otherwise
// noexcept: No exceptions (important for embedded systems)
// USE CASE: Pure functions with no side effects
// EXAMPLE: constexpr uint32_t f = factorial(5); // Computed at compile-time!
constexpr uint32_t factorial(uint32_t n) noexcept {
  return n <= 1 ? 1 : n * factorial(n - 1);
}

// constexpr with loops (C++14+)
// USE CASE: Bit manipulation that can be pre-computed
// EXAMPLE: constexpr uint8_t r = reverseBits(0b10110001); // Compile-time!
constexpr uint8_t reverseBits(uint8_t byte) noexcept {
  uint8_t result = 0;
  for (int i = 0; i < 8; i++) {
    result = (result << 1) | ((byte >> i) & 1);
  }
  return result;
}

// Simple constexpr validation
// USE CASE: Input validation that can be checked at compile-time
constexpr bool isValidPin(uint8_t pin) noexcept { return pin < 64; }

// inline: Avoid function call overhead for small functions
// USE CASE: Small utility functions called frequently
// NOTE: For free functions, inline MUST be in header to avoid linker errors
inline uint16_t makeWord(uint8_t high, uint8_t low) noexcept {
  return (high << 8) | low;
}

// [[nodiscard]]: Compiler warns if return value is ignored
// USE CASE: Functions where ignoring return value is likely a bug
// EXAMPLE: calculateDelay(1000); // WARNING: result unused!
[[nodiscard]] constexpr int calculateDelay(int frequency) noexcept {
  return frequency > 0 ? 1000000 / frequency : 0;
}

// ===== TEMPLATED FUNCTIONS =====
// Templates + constexpr = Type-generic compile-time functions!

// USE CASE: Generic algorithms that work with any type
// BENEFIT: One function works for int, float, double, etc.
// EXAMPLE: constexpr int m = max(5, 10);
//          constexpr float m2 = max(5.5f, 10.2f);
template <typename T> constexpr T max(T a, T b) noexcept {
  return (a > b) ? a : b;
}

template <typename T> constexpr T min(T a, T b) noexcept {
  return (a < b) ? a : b;
}

// Clamp value between bounds
// USE CASE: Constrain sensor readings, PWM values, etc.
template <typename T> constexpr T clamp(T value, T low, T high) noexcept {
  return (value < low) ? low : (value > high) ? high : value;
}

/*
=============================================================================
DECISION GUIDE: When to Use What?
=============================================================================

┌─────────────────┬───────────────────────────────────────────────────────┐
│ Keyword         │ Use When...                                           │
├─────────────────┼───────────────────────────────────────────────────────┤
│ constexpr       │ Function CAN be evaluated at compile-time            │
│                 │ (pure functions, no I/O, no side effects)             │
├─────────────────┼───────────────────────────────────────────────────────┤
│ const           │ Member function doesn't modify object state          │
│                 │ (getters, calculations using member data)             │
├─────────────────┼───────────────────────────────────────────────────────┤
│ noexcept        │ Function never throws exceptions                      │
│                 │ (critical for destructors, move constructors, swaps)  │
├─────────────────┼───────────────────────────────────────────────────────┤
│ inline          │ Small functions called frequently                     │
│                 │ (getters, simple calculations, utilities)             │
├─────────────────┼───────────────────────────────────────────────────────┤
│ [[nodiscard]]   │ Ignoring return value is likely a bug                │
│                 │ (error codes, calculations, allocations)              │
├─────────────────┼───────────────────────────────────────────────────────┤
│ static          │ Function doesn't need object instance                │
│ constexpr       │ (class constants, factory methods)                    │
└─────────────────┴───────────────────────────────────────────────────────┘

COMMON COMBINATIONS:
  • constexpr + noexcept          → Compile-time math (factorial, pow)
  • const + noexcept              → Read-only accessors (getters)
  • inline + noexcept             → Fast utilities (swap, helpers)
  • constexpr + const + noexcept  → Pure member functions (calculations)
  • [[nodiscard]] + constexpr     → Important calculations

IN CLASSES vs FREE FUNCTIONS:
  • Member functions: Use 'const' to mark read-only functions
  • Free functions: 'const' only for parameters (const int& x)
  • Both: constexpr, noexcept, inline, [[nodiscard]] work the same!

MICROCONTROLLER TIPS:
  • constexpr → Pre-compute at compile-time (saves flash/RAM)
  • noexcept → Smaller binary size (no exception handling code)
  • inline → Faster execution (no function call overhead)
=============================================================================
*/

// ===== STATIC FUNCTIONS =====

class BitManipulation {
public:
  // STATIC MEMBER FUNCTION
  // - No object needed, call with BitManipulation::setBit(...)
  // - Can't access member variables (no 'this' pointer)
  // - USE CASE: Utility functions that don't need object state
  static constexpr uint8_t setBit(uint8_t byte, uint8_t bit) noexcept {
    return byte | (1 << bit);
  }

  static constexpr uint8_t clearBit(uint8_t byte, uint8_t bit) noexcept {
    return byte & ~(1 << bit);
  }

  static constexpr uint8_t toggleBit(uint8_t byte, uint8_t bit) noexcept {
    return byte ^ (1 << bit);
  }

  static constexpr bool isBitSet(uint8_t byte, uint8_t bit) noexcept {
    return (byte & (1 << bit)) != 0;
  }

  // STATIC + CONSTEXPR CONSTANT
  static constexpr uint8_t ALL_BITS_SET = 0xFF;
  static constexpr uint8_t NO_BITS_SET = 0x00;
};

class Arduino {
public:
  // Static utility functions - no Arduino object needed
  static constexpr uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max,
                                uint32_t out_min, uint32_t out_max) noexcept {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  static constexpr uint32_t constrain(uint32_t x, uint32_t min,
                                      uint32_t max) noexcept {
    return (x < min) ? min : (x > max) ? max : x;
  }

  // Static constants
  static constexpr uint8_t LED_PIN = 13;
  static constexpr uint32_t SERIAL_BAUD = 9600;
};

// STATIC FREE FUNCTION (declaration only)
// Implementation in .cpp will be file-local
// NOTE: In header, we typically DON'T use static for free functions
// (Use 'inline' or anonymous namespace instead)

void static_functions_demo();

// Demo function
void advanced_demo();
