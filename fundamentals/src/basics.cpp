#include "basics.hpp"
#include <bitset>
#include <cstdio>
#include <iostream>

void hex() {
  /*
   0x123 is hexadecimal notation:
    - 1 is in the 16² place = 1 × 256 = 256
    - 2 is in the 16¹ place = 2 × 16 = 32
    - 3 is in the 16⁰ place = 3 × 1 = 3
    - Total: 256 + 32 + 3 = 29
  */

  int hex_number = 0X123;
  std::cout << hex_number << std::endl;
}

void binary() {
  /*
   For getting the binary number from decimal we must devide the number
   from its value/2 until we get 0.

   2/100  0
   2/50   0
   2/25   1
   2/12   0
   2/6    0
   2/3    1
   2/1    1

   Result = 1100100
*/

  int binary_number = 0b1100100;
  std::cout << binary_number << std::endl;
}

void preprocessor() {
  int result = SUM(500);
  printf("%d", result);

#ifdef FUN
  printf("\nFUN IS DEFINED!");
#else
  printf("\nFUN NOT DEFINED!");
#endif

#if MEME == 100
  printf("\nMEME IS A 100!");
#endif
}

void enums_demo() {
  std::cout << "\n\n=== ENUM EXAMPLES ===" << std::endl;

  // Traditional enum
  LogLevel currentLevel = WARNING_LEVEL;
  std::cout << "Log level: " << currentLevel << std::endl; // Prints: 2

  // Enum class (strongly typed)
  PinMode pin13 = PinMode::OUTPUT;

  // Must use scope with enum class
  if (pin13 == PinMode::OUTPUT) {
    std::cout << "Pin 13 is set to OUTPUT" << std::endl;
  }

  // Using underlying type
  LedState led = LedState::ON;
  std::cout << "LED state value: " << static_cast<int>(led) << std::endl; // 255

  // Practical use case - state machine
  LedState states[] = {LedState::OFF, LedState::ON, LedState::BLINK};
  for (auto state : states) {
    switch (state) {
    case LedState::OFF:
      std::cout << "LED is OFF" << std::endl;
      break;
    case LedState::ON:
      std::cout << "LED is ON (0x" << std::hex << static_cast<int>(state)
                << std::dec << ")" << std::endl;
      break;
    case LedState::BLINK:
      std::cout << "LED is BLINKING" << std::endl;
      break;
    }
  }
}

// ===== PERFORMANCE KEYWORD EXAMPLES =====

void performance_demo() {
  std::cout << "\n\n=== PERFORMANCE KEYWORDS ===" << std::endl;

  // constexpr - computed at compile time
  constexpr int fact5 = factorial(5);
  std::cout << "Factorial of 5 (compile-time): " << fact5 << std::endl; // 120

  constexpr int fact10 = factorial(10);
  std::cout << "Factorial of 10 (compile-time): " << fact10
            << std::endl; // 3628800

  // inline functions - fast operations
  int result = fastAdd(100, 200);
  std::cout << "Fast add (inline): " << result << std::endl;

  // Bit manipulation with inline
  uint8_t pinMask = setPinHigh(3); // Set bit 3
  std::cout << "Pin 3 mask (inline): 0b" << std::bitset<8>(pinMask)
            << std::endl;

  // noexcept swap - guaranteed no exceptions
  int a = 42, b = 99;
  std::cout << "Before swap: a=" << a << ", b=" << b << std::endl;
  fastSwap(a, b);
  std::cout << "After swap (noexcept): a=" << a << ", b=" << b << std::endl;

  // const - prevents modification
  const int MAX_BUFFER = 256;
  std::cout << "Max buffer size (const): " << MAX_BUFFER << std::endl;

  // constexpr in practice
  constexpr uint32_t bits = toBits(0b11110000);
  std::cout << "Bits value (constexpr): " << bits << std::endl;
}
