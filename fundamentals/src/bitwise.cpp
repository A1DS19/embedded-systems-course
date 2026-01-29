#include "bitwise.hpp"
#include <bitset>
#include <iomanip>
#include <iostream>

// Helper to print byte in binary with label
static void printBinary(const char *label, uint8_t value) {
  std::cout << label << std::bitset<8>(value) << " (0x" << std::hex
            << std::setw(2) << std::setfill('0') << static_cast<int>(value)
            << std::dec << " = " << static_cast<int>(value) << ")" << std::endl;
}

void bitwise_basics_demo() {
  std::cout << "\n\n=== BIT MANIPULATION BASICS ===" << std::endl;

  // ===== BIT SHIFTING =====
  std::cout << "\n--- Left Shift (<<) - Multiply by 2 ---" << std::endl;
  uint8_t value = 5;
  printBinary("Original:     ", value);
  printBinary("Left << 1:    ", value << 1); // 5 * 2 = 10
  printBinary("Left << 2:    ", value << 2); // 5 * 4 = 20
  printBinary("Left << 3:    ", value << 3); // 5 * 8 = 40

  std::cout << "\n--- Right Shift (>>) - Divide by 2 ---" << std::endl;
  value = 40;
  printBinary("Original:     ", value);
  printBinary("Right >> 1:   ", value >> 1); // 40 / 2 = 20
  printBinary("Right >> 2:   ", value >> 2); // 40 / 4 = 10
  printBinary("Right >> 3:   ", value >> 3); // 40 / 8 = 5

  // ===== BITWISE OPERATORS =====
  std::cout << "\n--- AND (&) - Both bits must be 1 ---" << std::endl;
  uint8_t a = 0b10110010;
  uint8_t b = 0b11110000;
  printBinary("A:            ", a);
  printBinary("B:            ", b);
  printBinary("A & B:        ", a & b);
  std::cout << "Use case: Masking/isolating specific bits" << std::endl;

  std::cout << "\n--- OR (|) - Either bit is 1 ---" << std::endl;
  a = 0b10110010;
  b = 0b00001111;
  printBinary("A:            ", a);
  printBinary("B:            ", b);
  printBinary("A | B:        ", a | b);
  std::cout << "Use case: Setting multiple bits at once" << std::endl;

  std::cout << "\n--- XOR (^) - Bits are different ---" << std::endl;
  a = 0b10110010;
  b = 0b11110000;
  printBinary("A:            ", a);
  printBinary("B:            ", b);
  printBinary("A ^ B:        ", a ^ b);
  std::cout << "Use case: Toggling bits, encryption" << std::endl;

  std::cout << "\n--- NOT (~) - Flip all bits ---" << std::endl;
  a = 0b10110010;
  printBinary("A:            ", a);
  printBinary("~A:           ", static_cast<uint8_t>(~a));
  std::cout << "Use case: Creating inverse masks" << std::endl;
}

void bitwise_advanced_demo() {
  std::cout << "\n\n=== ADVANCED BIT OPERATIONS ===" << std::endl;

  uint8_t byte = 0b00000000;

  // ===== SETTING BITS =====
  std::cout << "\n--- Setting Bits ---" << std::endl;
  printBinary("Start:        ", byte);

  byte = Bitwise::setBit(byte, 3);
  printBinary("Set bit 3:    ", byte);

  byte = Bitwise::setBit(byte, 7);
  printBinary("Set bit 7:    ", byte);

  byte = Bitwise::setBit(byte, 0);
  printBinary("Set bit 0:    ", byte);

  // ===== CLEARING BITS =====
  std::cout << "\n--- Clearing Bits ---" << std::endl;
  printBinary("Current:      ", byte);

  byte = Bitwise::clearBit(byte, 3);
  printBinary("Clear bit 3:  ", byte);

  byte = Bitwise::clearBit(byte, 0);
  printBinary("Clear bit 0:  ", byte);

  // ===== TOGGLING BITS =====
  std::cout << "\n--- Toggling Bits ---" << std::endl;
  byte = 0b10101010;
  printBinary("Start:        ", byte);

  byte = Bitwise::toggleBit(byte, 0);
  printBinary("Toggle bit 0: ", byte);

  byte = Bitwise::toggleBit(byte, 7);
  printBinary("Toggle bit 7: ", byte);

  // ===== CHECKING BITS =====
  std::cout << "\n--- Checking Bits ---" << std::endl;
  byte = 0b10001000;
  printBinary("Value:        ", byte);
  std::cout << "Bit 3 is: " << (Bitwise::isBitSet(byte, 3) ? "SET" : "CLEAR")
            << std::endl;
  std::cout << "Bit 7 is: " << (Bitwise::isBitSet(byte, 7) ? "SET" : "CLEAR")
            << std::endl;
  std::cout << "Bit 0 is: " << (Bitwise::isBitSet(byte, 0) ? "SET" : "CLEAR")
            << std::endl;

  // ===== EXTRACTING BITS =====
  std::cout << "\n--- Extracting Bit Ranges ---" << std::endl;
  byte = 0b11010110;
  printBinary("Value:        ", byte);
  uint8_t extracted = Bitwise::extractBits(byte, 2, 4);
  std::cout << "Bits 2-5:     " << std::bitset<4>(extracted)
            << " (decimal: " << static_cast<int>(extracted) << ")" << std::endl;

  // ===== COUNTING BITS =====
  std::cout << "\n--- Counting Set Bits ---" << std::endl;
  byte = 0b10101101;
  printBinary("Value:        ", byte);
  std::cout << "Number of 1s: " << static_cast<int>(Bitwise::countBits(byte))
            << std::endl;

  // ===== ROTATION =====
  std::cout << "\n--- Rotating Bits ---" << std::endl;
  byte = 0b10110001;
  printBinary("Original:     ", byte);
  printBinary("Rotate left:  ", ShiftOps::rotateLeft(byte, 2));
  printBinary("Rotate right: ", ShiftOps::rotateRight(byte, 2));

  // ===== BYTE OPERATIONS =====
  std::cout << "\n--- Byte Operations ---" << std::endl;
  byte = 0xAB;
  printBinary("Original:     ", byte);
  printBinary("Swap nibbles: ", ByteOps::swapNibbles(byte));
  printBinary("Reverse bits: ", ByteOps::reverseBits(byte));

  uint16_t word = 0xABCD;
  std::cout << "\nWord: 0x" << std::hex << word << std::dec << std::endl;
  std::cout << "High byte: 0x" << std::hex
            << static_cast<int>(ByteOps::highByte(word)) << std::dec
            << std::endl;
  std::cout << "Low byte: 0x" << std::hex
            << static_cast<int>(ByteOps::lowByte(word)) << std::dec
            << std::endl;

  uint16_t reconstructed =
      ByteOps::makeWord(ByteOps::highByte(word), ByteOps::lowByte(word));
  std::cout << "Reconstructed: 0x" << std::hex << reconstructed << std::dec
            << std::endl;
}

void bitwise_microcontroller_demo() {
  std::cout << "\n\n=== MICROCONTROLLER APPLICATIONS ===" << std::endl;

  // ===== DIGITAL PIN CONTROL =====
  std::cout << "\n--- Digital Pin Control (Arduino-style) ---" << std::endl;
  DigitalPin port;

  std::cout << "\nConfiguring pins as OUTPUT:" << std::endl;
  port.pinMode(13, true); // LED pin
  port.pinMode(12, true);
  port.pinMode(11, true);
  printBinary("DDR Register: ", port.getDDR());

  std::cout << "\nSetting pins HIGH:" << std::endl;
  port.digitalWrite(13, true); // Turn on LED
  port.digitalWrite(11, true);
  printBinary("PORT Register:", port.getPORT());

  std::cout << "\nToggling pin 13:" << std::endl;
  port.togglePin(13);
  printBinary("PORT Register:", port.getPORT());

  port.togglePin(13);
  printBinary("PORT Register:", port.getPORT());

  // ===== REAL-WORLD EXAMPLES =====
  std::cout << "\n--- Real-World Examples ---" << std::endl;

  // Example 1: Status register with flags
  std::cout << "\n1. Status Register (multiple flags):" << std::endl;
  uint8_t status = 0x00;
  constexpr uint8_t FLAG_READY = 0;
  constexpr uint8_t FLAG_ERROR = 1;
  constexpr uint8_t FLAG_BUSY = 2;
  constexpr uint8_t FLAG_COMPLETE = 3;

  status = Bitwise::setBit(status, FLAG_READY);
  status = Bitwise::setBit(status, FLAG_COMPLETE);
  printBinary("Status:       ", status);
  std::cout << "  Ready? " << (Bitwise::isBitSet(status, FLAG_READY) ? "YES" : "NO")
            << std::endl;
  std::cout << "  Error? " << (Bitwise::isBitSet(status, FLAG_ERROR) ? "YES" : "NO")
            << std::endl;
  std::cout << "  Complete? "
            << (Bitwise::isBitSet(status, FLAG_COMPLETE) ? "YES" : "NO")
            << std::endl;

  // Example 2: PWM duty cycle
  std::cout << "\n2. PWM Duty Cycle (8-bit):" << std::endl;
  uint8_t dutyCycle = 128; // 50%
  printBinary("50% duty:     ", dutyCycle);
  dutyCycle = 192; // 75%
  printBinary("75% duty:     ", dutyCycle);
  dutyCycle = 64; // 25%
  printBinary("25% duty:     ", dutyCycle);

  // Example 3: Sensor data packing
  std::cout << "\n3. Packing Multiple Sensors:" << std::endl;
  uint8_t sensors = 0x00;
  // Bits 0-1: temperature sensor (0-3)
  // Bits 2-4: light sensor (0-7)
  // Bits 5-7: humidity sensor (0-7)

  uint8_t temp = 2;   // 0-3
  uint8_t light = 5;  // 0-7
  uint8_t humid = 6;  // 0-7

  sensors |= (temp & 0b11);         // Bits 0-1
  sensors |= ((light & 0b111) << 2); // Bits 2-4
  sensors |= ((humid & 0b111) << 5); // Bits 5-7

  printBinary("Packed data:  ", sensors);
  std::cout << "Temperature: " << static_cast<int>(Bitwise::extractBits(sensors, 0, 2))
            << std::endl;
  std::cout << "Light:       " << static_cast<int>(Bitwise::extractBits(sensors, 2, 3))
            << std::endl;
  std::cout << "Humidity:    " << static_cast<int>(Bitwise::extractBits(sensors, 5, 3))
            << std::endl;

  // Example 4: Bitmask for multiple pins
  std::cout << "\n4. Operating on Multiple Pins at Once:" << std::endl;
  uint8_t pins = 0x00;
  uint8_t ledMask = 0b00111000; // Pins 3, 4, 5

  printBinary("Start:        ", pins);
  pins = Bitwise::setBits(pins, ledMask);
  printBinary("LEDs ON:      ", pins);
  pins = Bitwise::clearBits(pins, ledMask);
  printBinary("LEDs OFF:     ", pins);

  std::cout << "\n=== KEY TAKEAWAYS ===" << std::endl;
  std::cout << "• Bit manipulation is ESSENTIAL for microcontrollers" << std::endl;
  std::cout << "• Direct hardware register access (PORT, DDR, etc.)" << std::endl;
  std::cout << "• Efficient memory usage (pack multiple values)" << std::endl;
  std::cout << "• Fast operations (no division/multiplication)" << std::endl;
  std::cout << "• constexpr allows compile-time bit calculations!" << std::endl;
}
