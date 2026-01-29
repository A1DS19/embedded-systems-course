#include "operators.hpp"
#include <iostream>

void IncrementDemo::prefixDemo() {
  std::cout << "\n=== PREFIX INCREMENT (++var) ===" << std::endl;
  std::cout << "Increments FIRST, then returns new value\n" << std::endl;

  // Example 1: Simple assignment
  std::cout << "Example 1: Simple assignment" << std::endl;
  int x = 5;
  std::cout << "x = " << x << std::endl;
  std::cout << "Executing: int result = ++x;" << std::endl;
  int result = ++x;
  std::cout << "result = " << result << " (got incremented value)" << std::endl;
  std::cout << "x = " << x << " (was incremented)" << std::endl;

  // Example 2: In expression
  std::cout << "\nExample 2: In expression" << std::endl;
  int a = 10;
  std::cout << "a = " << a << std::endl;
  std::cout << "Executing: int b = ++a * 2;" << std::endl;
  int b = ++a * 2; // a becomes 11, then 11 * 2
  std::cout << "b = " << b << " (11 * 2)" << std::endl;
  std::cout << "a = " << a << " (incremented to 11)" << std::endl;

  // Example 3: Multiple operations
  std::cout << "\nExample 3: Multiple operations" << std::endl;
  int count = 0;
  std::cout << "count = " << count << std::endl;
  std::cout << "++count = " << ++count << " (now 1)" << std::endl;
  std::cout << "++count = " << ++count << " (now 2)" << std::endl;
  std::cout << "++count = " << ++count << " (now 3)" << std::endl;
  std::cout << "Final count = " << count << std::endl;

  // Example 4: In array indexing
  std::cout << "\nExample 4: Array indexing" << std::endl;
  int arr[] = {10, 20, 30, 40, 50};
  int i = 0;
  std::cout << "i = " << i << std::endl;
  std::cout << "arr[++i] = " << arr[++i]
            << " (i becomes 1 first, then access arr[1])" << std::endl;
  std::cout << "i = " << i << std::endl;
}

void IncrementDemo::postfixDemo() {
  std::cout << "\n=== POSTFIX INCREMENT (var++) ===" << std::endl;
  std::cout << "Returns CURRENT value, then increments\n" << std::endl;

  // Example 1: Simple assignment
  std::cout << "Example 1: Simple assignment" << std::endl;
  int x = 5;
  std::cout << "x = " << x << std::endl;
  std::cout << "Executing: int result = x++;" << std::endl;
  int result = x++;
  std::cout << "result = " << result << " (got old value)" << std::endl;
  std::cout << "x = " << x << " (incremented after)" << std::endl;

  // Example 2: In expression
  std::cout << "\nExample 2: In expression" << std::endl;
  int a = 10;
  std::cout << "a = " << a << std::endl;
  std::cout << "Executing: int b = a++ * 2;" << std::endl;
  int b = a++ * 2; // 10 * 2, then a becomes 11
  std::cout << "b = " << b << " (10 * 2)" << std::endl;
  std::cout << "a = " << a << " (incremented to 11)" << std::endl;

  // Example 3: Multiple operations
  std::cout << "\nExample 3: Multiple operations" << std::endl;
  int count = 0;
  std::cout << "count = " << count << std::endl;
  std::cout << "count++ = " << count++ << " (returns 0)" << std::endl;
  std::cout << "count++ = " << count++ << " (returns 1)" << std::endl;
  std::cout << "count++ = " << count++ << " (returns 2)" << std::endl;
  std::cout << "Final count = " << count << std::endl;

  // Example 4: In array indexing
  std::cout << "\nExample 4: Array indexing" << std::endl;
  int arr[] = {10, 20, 30, 40, 50};
  int i = 0;
  std::cout << "i = " << i << std::endl;
  std::cout << "arr[i++] = " << arr[i++] << " (access arr[0], then i becomes 1)"
            << std::endl;
  std::cout << "i = " << i << std::endl;
}

void IncrementDemo::decrementDemo() {
  std::cout << "\n=== DECREMENT OPERATORS (--var and var--) ===" << std::endl;
  std::cout << "Same logic as increment, but subtracts 1\n" << std::endl;

  // Prefix decrement
  std::cout << "PREFIX (--var):" << std::endl;
  int x = 10;
  std::cout << "x = " << x << std::endl;
  std::cout << "--x = " << --x << " (decrements to 9, returns 9)" << std::endl;
  std::cout << "x = " << x << std::endl;

  // Postfix decrement
  std::cout << "\nPOSTFIX (var--):" << std::endl;
  int y = 10;
  std::cout << "y = " << y << std::endl;
  std::cout << "y-- = " << y-- << " (returns 10, then decrements to 9)"
            << std::endl;
  std::cout << "y = " << y << std::endl;

  // Practical example: countdown
  std::cout << "\nCountdown example:" << std::endl;
  int countdown = 5;
  std::cout << "Starting countdown from " << countdown << ":" << std::endl;
  while (countdown > 0) {
    std::cout << countdown-- << "... "; // Print current, then decrement
  }
  std::cout << "Liftoff!" << std::endl;
}

void IncrementDemo::performanceDemo() {
  std::cout << "\n=== PERFORMANCE: PREFIX vs POSTFIX ===" << std::endl;

  std::cout << "\nFor PRIMITIVE TYPES (int, char, etc.):" << std::endl;
  std::cout << "  • Modern compilers optimize both equally" << std::endl;
  std::cout << "  • No performance difference in practice" << std::endl;

  std::cout << "\nFor COMPLEX TYPES (objects, iterators):" << std::endl;
  std::cout << "  • PREFIX (++i) is MORE EFFICIENT" << std::endl;
  std::cout << "  • POSTFIX (i++) creates a temporary copy" << std::endl;

  std::cout << "\nWHY?" << std::endl;
  std::cout << "Postfix implementation:" << std::endl;
  std::cout << "  Type operator++(int) {" << std::endl;
  std::cout << "    Type temp = *this;  // <-- Extra copy!" << std::endl;
  std::cout << "    ++(*this);" << std::endl;
  std::cout << "    return temp;" << std::endl;
  std::cout << "  }" << std::endl;

  std::cout << "\nPrefix implementation:" << std::endl;
  std::cout << "  Type& operator++() {" << std::endl;
  std::cout << "    // increment" << std::endl;
  std::cout << "    return *this;  // <-- No copy!" << std::endl;
  std::cout << "  }" << std::endl;

  std::cout << "\nBEST PRACTICE:" << std::endl;
  std::cout << "  • Use ++i in for loops (habit from C++)" << std::endl;
  std::cout << "  • Use i++ only when you need old value" << std::endl;
}

void CompoundAssignment::demo() {
  std::cout << "\n=== COMPOUND ASSIGNMENT OPERATORS ===" << std::endl;
  std::cout << "Shortcuts for common operations\n" << std::endl;

  int x = 10;

  std::cout << "Starting value: x = " << x << std::endl;

  // Arithmetic compound operators
  std::cout << "\n--- Arithmetic ---" << std::endl;
  x += 5; // x = x + 5
  std::cout << "x += 5  → x = " << x << std::endl;

  x -= 3; // x = x - 3
  std::cout << "x -= 3  → x = " << x << std::endl;

  x *= 2; // x = x * 2
  std::cout << "x *= 2  → x = " << x << std::endl;

  x /= 4; // x = x / 4
  std::cout << "x /= 4  → x = " << x << std::endl;

  x %= 5; // x = x % 5
  std::cout << "x %= 5  → x = " << x << std::endl;

  // Bitwise compound operators
  std::cout << "\n--- Bitwise ---" << std::endl;
  uint8_t byte = 0b11110000;
  std::cout << "Starting: byte = 0b11110000" << std::endl;

  byte &= 0b11001100; // byte = byte & 0b11001100
  std::cout << "byte &= 0b11001100 → 0b11000000" << std::endl;

  byte |= 0b00001111; // byte = byte | 0b00001111
  std::cout << "byte |= 0b00001111 → 0b11001111" << std::endl;

  byte ^= 0b11111111; // byte = byte ^ 0b11111111
  std::cout << "byte ^= 0b11111111 → 0b00110000 (flip all)" << std::endl;

  // Shift compound operators
  std::cout << "\n--- Shifts ---" << std::endl;
  int value = 4;
  std::cout << "Starting: value = " << value << std::endl;

  value <<= 2; // value = value << 2 (multiply by 4)
  std::cout << "value <<= 2 → " << value << " (4 * 4)" << std::endl;

  value >>= 1; // value = value >> 1 (divide by 2)
  std::cout << "value >>= 1 → " << value << " (16 / 2)" << std::endl;

  // Practical microcontroller example
  std::cout << "\n--- Microcontroller Example ---" << std::endl;
  uint8_t PORT = 0b00000000;
  std::cout << "PORT register: 0b00000000" << std::endl;

  PORT |= (1 << 3); // Set bit 3
  std::cout << "PORT |= (1<<3) → 0b00001000 (set pin 3)" << std::endl;

  PORT |= (1 << 5); // Set bit 5
  std::cout << "PORT |= (1<<5) → 0b00101000 (set pin 5)" << std::endl;

  PORT &= ~(1 << 3); // Clear bit 3
  std::cout << "PORT &= ~(1<<3) → 0b00100000 (clear pin 3)" << std::endl;
}

void operators_demo() {
  std::cout << "\n\n=== INCREMENT/DECREMENT OPERATORS ===" << std::endl;

  IncrementDemo::prefixDemo();
  IncrementDemo::postfixDemo();
  IncrementDemo::decrementDemo();
  IncrementDemo::performanceDemo();
  CompoundAssignment::demo();

  // Side-by-side comparison
  std::cout << "\n\n=== SIDE-BY-SIDE COMPARISON ===" << std::endl;

  std::cout << "\nSAME starting value:" << std::endl;
  int a = 5, b = 5;
  std::cout << "a = " << a << ", b = " << b << std::endl;

  std::cout << "\nUsing in assignment:" << std::endl;
  int result_prefix = ++a;
  int result_postfix = b++;
  std::cout << "result_prefix = ++a  → result_prefix = " << result_prefix
            << ", a = " << a << std::endl;
  std::cout << "result_postfix = b++ → result_postfix = " << result_postfix
            << ", b = " << b << std::endl;

  // Common for loop comparison
  std::cout << "\n=== IN FOR LOOPS ===" << std::endl;
  std::cout << "Both produce same result, but ++i is preferred:\n" << std::endl;

  std::cout << "for (int i = 0; i < 5; i++)  → ";
  for (int i = 0; i < 5; i++) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::cout << "for (int i = 0; i < 5; ++i) → ";
  for (int i = 0; i < 5; ++i) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  // When it matters
  std::cout << "\n=== WHEN IT REALLY MATTERS ===" << std::endl;
  int arr[] = {10, 20, 30, 40, 50};
  int i = 0, j = 0;

  std::cout << "int x = arr[i++]; // x gets arr[0]=10, then i becomes 1"
            << std::endl;
  int x = arr[i++];
  std::cout << "x = " << x << ", i = " << i << std::endl;

  std::cout << "int y = arr[++j]; // j becomes 1, then y gets arr[1]=20"
            << std::endl;
  int y = arr[++j];
  std::cout << "y = " << y << ", j = " << j << std::endl;

  std::cout << "\n=== KEY TAKEAWAY ===" << std::endl;
  std::cout << "PREFIX (++var):  Increment first, return new value"
            << std::endl;
  std::cout << "POSTFIX (var++): Return old value, increment after"
            << std::endl;
  std::cout << "\nPrefer ++i in loops (better habit, works for all types)"
            << std::endl;
}
