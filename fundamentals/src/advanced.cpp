#include "advanced.hpp"
#include <bitset>
#include <iostream>

// ===== STATIC FREE FUNCTIONS =====
// These are ONLY visible in this .cpp file (internal linkage)
// Other files can't see them, even with extern
// USE CASE: Private helper functions for this file only

// Static free function - file-local helper
static int privateHelper(int x) { return x * 2; }

// Static free function - another helper
static constexpr int PRIVATE_CONSTANT = 100;

static bool isEven(int n) { return n % 2 == 0; }

void advanced_demo() {
  std::cout << "\n\n=== ADVANCED KEYWORD COMBINATIONS ===" << std::endl;

  // ===== CONSTEXPR VARIABLES =====
  std::cout << "\n--- Constexpr Variables ---" << std::endl;
  std::cout << "Max buffer size: " << MAX_BUFFER_SIZE << std::endl;
  std::cout << "Max pins: " << static_cast<int>(MAX_PINS) << std::endl;
  std::cout << "Clock speed: " << CLOCK_SPEED << " Hz" << std::endl;
  std::cout << "PI: " << PI << std::endl;
  std::cout << "Timeout: " << TIMEOUT_MS << " ms" << std::endl;

  // ===== MATH CLASS =====
  std::cout << "\n--- Math Class (constexpr + noexcept) ---" << std::endl;
  Math math;

  // These can be computed at compile time
  constexpr int square_5 = 25; // Would be: Math{}.square(5)
  std::cout << "Square of 5: " << math.square(5) << std::endl;
  std::cout << "Cube of 3: " << math.cube(3) << std::endl;
  std::cout << "2^10: " << math.power(2, 10) << std::endl;

  int a = 42, b = 99;
  std::cout << "Before swap: a=" << a << ", b=" << b << std::endl;
  math.swap(a, b);
  std::cout << "After swap: a=" << a << ", b=" << b << std::endl;

  std::cout << "Math::E = " << Math::E << std::endl;
  std::cout << "Math::GOLDEN_RATIO = " << Math::GOLDEN_RATIO << std::endl;

  // ===== MICROCONTROLLER CLASS =====
  std::cout << "\n--- MicroController Class ---" << std::endl;
  MicroController mcu;

  std::cout << "Total pins: " << static_cast<int>(MicroController::TOTAL_PINS)
            << std::endl;
  std::cout << "Clock: " << MicroController::DEFAULT_CLOCK << " Hz"
            << std::endl;

  // Set some pins high
  mcu.digitalWrite(13, true); // LED pin
  mcu.digitalWrite(3, true);
  mcu.digitalWrite(5, true);

  std::cout << "Pin 13 state: " << static_cast<int>(mcu.digitalRead(13))
            << std::endl;
  std::cout << "Pin 12 state: " << static_cast<int>(mcu.digitalRead(12))
            << std::endl;

  std::cout << "Is pin 13 high? " << (mcu.isPinHigh(13) ? "YES" : "NO")
            << std::endl;
  std::cout << "Is pin 12 high? " << (mcu.isPinHigh(12) ? "YES" : "NO")
            << std::endl;

  // ===== FREE FUNCTIONS =====
  std::cout << "\n--- Free Functions (constexpr + noexcept) ---" << std::endl;

  constexpr uint32_t fact_5 = factorial(5);
  std::cout << "Factorial of 5 (compile-time): " << fact_5 << std::endl;

  constexpr uint8_t original = 0b11010010;
  constexpr uint8_t reversed = reverseBits(original);
  std::cout << "Original bits:  " << std::bitset<8>(original) << std::endl;
  std::cout << "Reversed bits:  " << std::bitset<8>(reversed) << std::endl;

  std::cout << "Is pin 13 valid? " << (isValidPin(13) ? "YES" : "NO")
            << std::endl;
  std::cout << "Is pin 100 valid? " << (isValidPin(100) ? "YES" : "NO")
            << std::endl;

  uint16_t word = makeWord(0xAB, 0xCD);
  std::cout << "Make word from 0xAB, 0xCD: 0x" << std::hex << word << std::dec
            << std::endl;

  // [[nodiscard]] function
  int delay = calculateDelay(1000); // 1 kHz
  std::cout << "Delay for 1kHz: " << delay << " microseconds" << std::endl;

  // ===== TEMPLATE FUNCTIONS =====
  std::cout << "\n--- Template Functions (constexpr + noexcept) ---"
            << std::endl;

  constexpr int max_val = max(42, 99);
  constexpr int min_val = min(42, 99);
  std::cout << "Max(42, 99) = " << max_val << std::endl;
  std::cout << "Min(42, 99) = " << min_val << std::endl;

  constexpr int clamped = clamp(150, 0, 100);
  std::cout << "Clamp(150, 0, 100) = " << clamped << std::endl;

  constexpr float clamped_float = clamp(0.5f, 0.0f, 1.0f);
  std::cout << "Clamp(0.5, 0.0, 1.0) = " << clamped_float << std::endl;

  // ===== PERFORMANCE DEMONSTRATION =====
  std::cout << "\n--- Compile-Time vs Runtime ---" << std::endl;
  std::cout << "All constexpr calculations above were done at compile-time!"
            << std::endl;
  std::cout << "This means ZERO runtime cost for those computations."
            << std::endl;
  std::cout << "noexcept guarantees no exceptions = faster code generation."
            << std::endl;
}

void static_functions_demo() {
  std::cout << "\n\n=== STATIC FUNCTIONS ===" << std::endl;

  // ===== STATIC MEMBER FUNCTIONS =====
  std::cout << "\n--- Static Member Functions ---" << std::endl;

  // Call without creating an object - use class name
  uint8_t byte = 0b00000000;
  std::cout << "Initial: " << std::bitset<8>(byte) << std::endl;

  byte = BitManipulation::setBit(byte, 3); // Set bit 3
  std::cout << "After setBit(3): " << std::bitset<8>(byte) << std::endl;

  byte = BitManipulation::setBit(byte, 7); // Set bit 7
  std::cout << "After setBit(7): " << std::bitset<8>(byte) << std::endl;

  byte = BitManipulation::clearBit(byte, 3); // Clear bit 3
  std::cout << "After clearBit(3): " << std::bitset<8>(byte) << std::endl;

  byte = BitManipulation::toggleBit(byte, 7); // Toggle bit 7
  std::cout << "After toggleBit(7): " << std::bitset<8>(byte) << std::endl;

  bool isSet = BitManipulation::isBitSet(byte, 7);
  std::cout << "Is bit 7 set? " << (isSet ? "YES" : "NO") << std::endl;

  // Access static constants
  std::cout << "ALL_BITS_SET: " << std::bitset<8>(BitManipulation::ALL_BITS_SET)
            << std::endl;

  // ===== ARDUINO STATIC UTILITIES =====
  std::cout << "\n--- Arduino Static Utilities ---" << std::endl;

  // Map sensor reading (0-1023) to PWM (0-255)
  uint32_t sensorValue = 512;
  uint32_t pwmValue = Arduino::map(sensorValue, 0, 1023, 0, 255);
  std::cout << "Sensor " << sensorValue << " -> PWM " << pwmValue << std::endl;

  // Constrain value to range
  uint32_t reading = 300;
  uint32_t constrained = Arduino::constrain(reading, 0, 255);
  std::cout << "Constrain " << reading << " to [0,255]: " << constrained
            << std::endl;

  // Access static constants
  std::cout << "LED_PIN: " << static_cast<int>(Arduino::LED_PIN) << std::endl;
  std::cout << "SERIAL_BAUD: " << Arduino::SERIAL_BAUD << std::endl;

  // ===== STATIC FREE FUNCTIONS =====
  std::cout << "\n--- Static Free Functions (file-local) ---" << std::endl;

  // These are only accessible in this .cpp file
  int result = privateHelper(21);
  std::cout << "Private helper(21): " << result << std::endl;

  std::cout << "Private constant: " << PRIVATE_CONSTANT << std::endl;

  std::cout << "Is 42 even? " << (isEven(42) ? "YES" : "NO") << std::endl;
  std::cout << "Is 43 even? " << (isEven(43) ? "YES" : "NO") << std::endl;

  // ===== KEY DIFFERENCES =====
  std::cout << "\n--- Key Differences ---" << std::endl;
  std::cout << "Static member functions:" << std::endl;
  std::cout << "  - Called with ClassName::functionName()" << std::endl;
  std::cout << "  - No access to non-static members" << std::endl;
  std::cout << "  - No 'this' pointer" << std::endl;
  std::cout << "  - Like namespaced utilities" << std::endl;

  std::cout << "\nStatic free functions:" << std::endl;
  std::cout << "  - Only visible in current .cpp file" << std::endl;
  std::cout << "  - Internal linkage (not exported)" << std::endl;
  std::cout << "  - Perfect for private helper functions" << std::endl;
}
