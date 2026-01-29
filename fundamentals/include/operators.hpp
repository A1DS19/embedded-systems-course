/*
Operator Demonstrations - Prefix vs Postfix
*/

#pragma once

#include <cstdint>

// ===== INCREMENT/DECREMENT OPERATORS =====

class IncrementDemo {
public:
  // Demonstrate prefix increment
  static void prefixDemo();

  // Demonstrate postfix increment
  static void postfixDemo();

  // Demonstrate decrement operators
  static void decrementDemo();

  // Show performance difference
  static void performanceDemo();
};

// ===== COMPOUND ASSIGNMENT OPERATORS =====
// These are shortcuts for common operations

class CompoundAssignment {
public:
  // Demonstrate all compound operators
  static void demo();

  // Examples:
  // x += 5   same as   x = x + 5
  // x -= 3   same as   x = x - 3
  // x *= 2   same as   x = x * 2
  // x /= 4   same as   x = x / 4
  // x %= 3   same as   x = x % 3
  // x &= 0xF same as   x = x & 0xF
  // x |= 0xF same as   x = x | 0xF
  // x ^= 0xF same as   x = x ^ 0xF
  // x <<= 2  same as   x = x << 2
  // x >>= 2  same as   x = x >> 2
};

// ===== WHEN TO USE WHICH =====
/*
PREFIX (++var):
  ✓ Use in for loops (slightly more efficient)
  ✓ Use when you need the incremented value
  ✓ Use when increment is standalone statement
  ✓ Generally preferred in C++

POSTFIX (var++):
  ✓ Use when you need the OLD value before increment
  ✓ Use in complex expressions where order matters
  ✗ Slightly less efficient (creates temporary copy)

BEST PRACTICE:
  • Use ++i in for loops (more efficient)
  • Use i++ only when you explicitly need old value
  • For standalone statements: ++i and i++ are equivalent
*/

// Demo function
void operators_demo();
