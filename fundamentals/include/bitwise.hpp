/*
Bit Shifting & Manipulation
Essential for microcontrollers!
*/

#pragma once

#include <cstdint>

// ===== BIT POSITIONS =====
// Bit positions in a byte (0-7)
constexpr uint8_t BIT_0 = 0;
constexpr uint8_t BIT_1 = 1;
constexpr uint8_t BIT_2 = 2;
constexpr uint8_t BIT_3 = 3;
constexpr uint8_t BIT_4 = 4;
constexpr uint8_t BIT_5 = 5;
constexpr uint8_t BIT_6 = 6;
constexpr uint8_t BIT_7 = 7;

// ===== BIT MANIPULATION OPERATIONS =====

class Bitwise {
public:
  // SET a bit (make it 1)
  // Example: setBit(0b00000000, 3) = 0b00001000
  // USE CASE: Turn on a specific hardware pin or flag
  static constexpr uint8_t setBit(uint8_t byte, uint8_t bit) noexcept {
    return byte | (1 << bit);
    //            ↑   ↑
    //            |   Create mask: 1 shifted to position
    //            OR with original (sets the bit)
  }

  // CLEAR a bit (make it 0)
  // Example: clearBit(0b11111111, 3) = 0b11110111
  // USE CASE: Turn off a specific hardware pin or flag
  static constexpr uint8_t clearBit(uint8_t byte, uint8_t bit) noexcept {
    return byte & ~(1 << bit);
    //            ↑ ↑
    //            | NOT inverts: ~(00001000) = 11110111
    //            AND with original (clears the bit)
  }

  // TOGGLE a bit (flip it: 0→1 or 1→0)
  // Example: toggleBit(0b00001000, 3) = 0b00000000
  // USE CASE: Toggle LED state, flip flags
  static constexpr uint8_t toggleBit(uint8_t byte, uint8_t bit) noexcept {
    return byte ^ (1 << bit);
    //            ↑
    //            XOR flips the bit
  }

  // CHECK if bit is set (is it 1?)
  // Example: isBitSet(0b00001000, 3) = true
  // USE CASE: Read hardware pin state, check flags
  static constexpr bool isBitSet(uint8_t byte, uint8_t bit) noexcept {
    return (byte & (1 << bit)) != 0;
    //             ↑
    //             AND isolates the bit, check if non-zero
  }

  // GET bit value (0 or 1)
  // Example: getBit(0b00001000, 3) = 1
  static constexpr uint8_t getBit(uint8_t byte, uint8_t bit) noexcept {
    return (byte >> bit) & 1;
    //            ↑      ↑
    //            |      Mask to get only bit 0
    //            Shift bit to position 0
  }

  // SET multiple bits at once using a mask
  // Example: setBits(0b00000000, 0b00001111) = 0b00001111
  // USE CASE: Configure multiple pins at once
  static constexpr uint8_t setBits(uint8_t byte, uint8_t mask) noexcept {
    return byte | mask;
  }

  // CLEAR multiple bits using a mask
  // Example: clearBits(0b11111111, 0b00001111) = 0b11110000
  static constexpr uint8_t clearBits(uint8_t byte, uint8_t mask) noexcept {
    return byte & ~mask;
  }

  // WRITE bit (set to specific value: 0 or 1)
  // Example: writeBit(0b00000000, 3, true) = 0b00001000
  static constexpr uint8_t writeBit(uint8_t byte, uint8_t bit,
                                    bool value) noexcept {
    return value ? setBit(byte, bit) : clearBit(byte, bit);
  }

  // CREATE a bitmask (single bit set)
  // Example: bitMask(3) = 0b00001000
  static constexpr uint8_t bitMask(uint8_t bit) noexcept { return 1 << bit; }

  // EXTRACT bits from a range
  // Example: extractBits(0b11010110, 2, 4) extracts bits 2-4
  static constexpr uint8_t extractBits(uint8_t byte, uint8_t start,
                                       uint8_t length) noexcept {
    uint8_t mask = (1 << length) - 1; // Create mask of 'length' 1s
    return (byte >> start) & mask;
  }

  // COUNT number of set bits (population count)
  // Example: countBits(0b00101101) = 4
  static constexpr uint8_t countBits(uint8_t byte) noexcept {
    uint8_t count = 0;
    while (byte) {
      count += byte & 1;
      byte >>= 1;
    }
    return count;
  }
};

// ===== SHIFT OPERATIONS =====

class ShiftOps {
public:
  // LEFT SHIFT - multiply by powers of 2
  // Example: leftShift(5, 2) = 5 * 4 = 20
  // Each shift left multiplies by 2
  static constexpr uint32_t leftShift(uint32_t value,
                                      uint8_t positions) noexcept {
    return value << positions;
  }

  // RIGHT SHIFT - divide by powers of 2
  // Example: rightShift(20, 2) = 20 / 4 = 5
  // Each shift right divides by 2
  static constexpr uint32_t rightShift(uint32_t value,
                                       uint8_t positions) noexcept {
    return value >> positions;
  }

  // ROTATE LEFT (circular shift)
  // Bits that fall off the left come back on the right
  static constexpr uint8_t rotateLeft(uint8_t byte,
                                      uint8_t positions) noexcept {
    positions %= 8; // Handle positions > 8
    return (byte << positions) | (byte >> (8 - positions));
  }

  // ROTATE RIGHT (circular shift)
  static constexpr uint8_t rotateRight(uint8_t byte,
                                       uint8_t positions) noexcept {
    positions %= 8;
    return (byte >> positions) | (byte << (8 - positions));
  }
};

// ===== BYTE OPERATIONS =====

class ByteOps {
public:
  // Get LOW byte of 16-bit word
  // Example: lowByte(0xABCD) = 0xCD
  static constexpr uint8_t lowByte(uint16_t word) noexcept {
    return word & 0xFF;
  }

  // Get HIGH byte of 16-bit word
  // Example: highByte(0xABCD) = 0xAB
  static constexpr uint8_t highByte(uint16_t word) noexcept {
    return word >> 8;
  }

  // Make 16-bit word from two bytes
  // Example: makeWord(0xAB, 0xCD) = 0xABCD
  static constexpr uint16_t makeWord(uint8_t high, uint8_t low) noexcept {
    return (static_cast<uint16_t>(high) << 8) | low;
  }

  // SWAP nibbles (4-bit halves)
  // Example: swapNibbles(0xAB) = 0xBA
  static constexpr uint8_t swapNibbles(uint8_t byte) noexcept {
    return (byte << 4) | (byte >> 4);
  }

  // REVERSE all bits in a byte
  // Example: reverseBits(0b10110010) = 0b01001101
  static constexpr uint8_t reverseBits(uint8_t byte) noexcept {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
      result = (result << 1) | ((byte >> i) & 1);
    }
    return result;
  }
};

// ===== MICROCONTROLLER-SPECIFIC =====

// Simulate Arduino digital pin registers
class DigitalPin {
private:
  uint8_t portRegister = 0x00; // Simulates PORT register (output values)
  uint8_t dirRegister = 0x00;  // Simulates DDR register (direction)
  uint8_t pinRegister = 0x00;  // Simulates PIN register (input values)

public:
  // Set pin mode (INPUT=0, OUTPUT=1)
  constexpr void pinMode(uint8_t pin, bool output) noexcept {
    if (output) {
      dirRegister = Bitwise::setBit(dirRegister, pin);
    } else {
      dirRegister = Bitwise::clearBit(dirRegister, pin);
    }
  }

  // Write digital value (LOW=0, HIGH=1)
  constexpr void digitalWrite(uint8_t pin, bool value) noexcept {
    if (value) {
      portRegister = Bitwise::setBit(portRegister, pin);
    } else {
      portRegister = Bitwise::clearBit(portRegister, pin);
    }
  }

  // Read digital value
  constexpr bool digitalRead(uint8_t pin) const noexcept {
    return Bitwise::isBitSet(pinRegister, pin);
  }

  // Toggle pin
  constexpr void togglePin(uint8_t pin) noexcept {
    portRegister = Bitwise::toggleBit(portRegister, pin);
  }

  // Get register values (for demonstration)
  constexpr uint8_t getPORT() const noexcept { return portRegister; }
  constexpr uint8_t getDDR() const noexcept { return dirRegister; }
};

// Demo functions
void bitwise_basics_demo();
void bitwise_advanced_demo();
void bitwise_microcontroller_demo();
