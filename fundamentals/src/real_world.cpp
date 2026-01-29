#include "real_world.hpp"
#include <bitset>
#include <iostream>

void led_strip_demo() {
  std::cout << "\n=== SCENARIO 1: LED STRIP CONTROL ===" << std::endl;
  std::cout << "PROBLEM: Control 8 LEDs, but only have 1 GPIO pin to a shift "
               "register"
            << std::endl;
  std::cout << "SOLUTION: Each bit = one LED state\n" << std::endl;

  LEDStrip strip;

  std::cout << "Initial (all off): " << std::bitset<8>(strip.getState())
            << std::endl;

  // Turn on LEDs 0, 2, 4 (every other one)
  strip.turnOn(0);
  strip.turnOn(2);
  strip.turnOn(4);
  std::cout << "LEDs 0,2,4 ON:     " << std::bitset<8>(strip.getState())
            << " (0x" << std::hex << (int)strip.getState() << std::dec << ")"
            << std::endl;

  // Toggle LED 4 (turn it off)
  strip.toggle(4);
  std::cout << "Toggle LED 4:      " << std::bitset<8>(strip.getState())
            << std::endl;

  // Set a pattern (alternating)
  strip.setPattern(0b10101010);
  std::cout << "Pattern 10101010:  " << std::bitset<8>(strip.getState())
            << std::endl;

  // Shift pattern (chase effect)
  std::cout << "\nChase effect:" << std::endl;
  strip.setPattern(0b00000001);
  for (int i = 0; i < 8; i++) {
    std::cout << "  " << std::bitset<8>(strip.getState()) << std::endl;
    strip.shiftLeft();
  }

  std::cout << "\n💡 WHY USEFUL: Send 1 byte instead of 8 separate GPIO "
               "operations!"
            << std::endl;
}

void permissions_demo() {
  std::cout << "\n=== SCENARIO 2: USER PERMISSIONS ===" << std::endl;
  std::cout << "PROBLEM: Track multiple user permissions efficiently"
            << std::endl;
  std::cout << "SOLUTION: Each bit = one permission (like Unix file "
               "permissions!)\n"
            << std::endl;

  Permissions user;

  std::cout << "New user (no permissions): " << std::bitset<8>(user.flags)
            << std::endl;

  // Grant read and write
  user.grant(Permissions::READ);
  user.grant(Permissions::WRITE);
  std::cout << "Grant READ + WRITE:        " << std::bitset<8>(user.flags)
            << std::endl;

  // Check permissions
  std::cout << "Has READ?    " << (user.has(Permissions::READ) ? "YES" : "NO")
            << std::endl;
  std::cout << "Has EXECUTE? "
            << (user.has(Permissions::EXECUTE) ? "YES" : "NO") << std::endl;

  // Grant multiple at once
  user.grant(Permissions::EXECUTE | Permissions::DELETE);
  std::cout << "Grant EXECUTE + DELETE:    " << std::bitset<8>(user.flags)
            << std::endl;

  // Check if has all required permissions
  bool canModify = user.hasAll(Permissions::READ | Permissions::WRITE);
  std::cout << "Can modify files? " << (canModify ? "YES" : "NO") << std::endl;

  // Revoke permission
  user.revoke(Permissions::DELETE);
  std::cout << "Revoke DELETE:             " << std::bitset<8>(user.flags)
            << std::endl;

  std::cout << "\n💡 REAL USE: File systems (rwx), databases, APIs, game "
               "abilities"
            << std::endl;
}

void network_demo() {
  std::cout << "\n=== SCENARIO 3: NETWORK PROTOCOL (TCP) ===" << std::endl;
  std::cout << "PROBLEM: TCP packets need control flags in header" << std::endl;
  std::cout << "SOLUTION: Pack all flags into 1 byte (actual TCP does "
               "this!)\n"
            << std::endl;

  TCPFlags packet;

  // TCP handshake: SYN
  packet.setFlag(TCPFlags::SYN);
  std::cout << "SYN packet:         " << std::bitset<6>(packet.flags)
            << " (initiate connection)" << std::endl;

  // Response: SYN-ACK
  TCPFlags response;
  response.setFlag(TCPFlags::SYN | TCPFlags::ACK);
  std::cout << "SYN-ACK response:   " << std::bitset<6>(response.flags)
            << " (acknowledge)" << std::endl;
  std::cout << "Is SYN-ACK? " << (response.isSYNACK() ? "YES" : "NO")
            << std::endl;

  // Final ACK
  TCPFlags ack;
  ack.setFlag(TCPFlags::ACK);
  std::cout << "ACK packet:         " << std::bitset<6>(ack.flags)
            << " (connection established)" << std::endl;

  // Close connection: FIN-ACK
  TCPFlags closing;
  closing.setFlag(TCPFlags::FIN | TCPFlags::ACK);
  std::cout << "FIN-ACK packet:     " << std::bitset<6>(closing.flags)
            << " (closing connection)" << std::endl;

  std::cout << "\n💡 REAL USE: Every TCP packet you send uses this!"
            << std::endl;
}

void color_demo() {
  std::cout << "\n=== SCENARIO 4: RGB COLOR MANIPULATION ===" << std::endl;
  std::cout << "PROBLEM: Work with RGB colors (LEDs, displays)" << std::endl;
  std::cout << "SOLUTION: Pack R, G, B into 3 bytes (24-bit color)\n"
            << std::endl;

  // Purple color
  RGBColor purple(128, 0, 128);
  std::cout << "Purple RGB(128, 0, 128):" << std::endl;
  std::cout << "  Hex value: 0x" << std::hex << purple.getValue() << std::dec
            << std::endl;
  std::cout << "  Red:   " << (int)purple.getRed() << std::endl;
  std::cout << "  Green: " << (int)purple.getGreen() << std::endl;
  std::cout << "  Blue:  " << (int)purple.getBlue() << std::endl;

  // Modify just one channel
  RGBColor color(255, 100, 50);
  std::cout << "\nOriginal RGB(255, 100, 50):" << std::endl;
  std::cout << "  Hex: 0x" << std::hex << color.getValue() << std::dec
            << std::endl;

  color.setGreen(200);
  std::cout << "Change green to 200:" << std::endl;
  std::cout << "  Hex: 0x" << std::hex << color.getValue() << std::dec
            << std::endl;

  // Dim (divide by 2 using shift!)
  color.dim();
  std::cout << "Dim (>> 1):" << std::endl;
  std::cout << "  RGB(" << (int)color.getRed() << ", " << (int)color.getGreen()
            << ", " << (int)color.getBlue() << ")" << std::endl;

  std::cout << "\n💡 REAL USE: LED strips (WS2812B), displays, graphics"
            << std::endl;
}

void sensor_packing_demo() {
  std::cout << "\n=== SCENARIO 5: SENSOR DATA PACKING ===" << std::endl;
  std::cout << "PROBLEM: Send 3 sensor readings wirelessly (minimize bytes)"
            << std::endl;
  std::cout << "SOLUTION: Pack into 2 bytes instead of 6!\n" << std::endl;

  SensorPacket packet;

  // Set sensor values
  packet.setTemperature(25); // 0-31°C
  packet.setHumidity(18);    // 0-31 (scaled)
  packet.setLight(45);       // 0-63

  std::cout << "Sensor readings:" << std::endl;
  std::cout << "  Temperature: " << (int)packet.getTemperature() << "°C"
            << std::endl;
  std::cout << "  Humidity:    " << (int)packet.getHumidity() << "%"
            << std::endl;
  std::cout << "  Light:       " << (int)packet.getLight() << "%" << std::endl;

  std::cout << "\nPacked into 2 bytes: 0x" << std::hex << packet.getRawData()
            << std::dec << std::endl;
  std::cout << "Binary: " << std::bitset<16>(packet.getRawData()) << std::endl;

  // Unpack and verify
  std::cout << "\nUnpack verification:" << std::endl;
  std::cout << "  Temp:  bits 0-4   = " << (int)packet.getTemperature()
            << std::endl;
  std::cout << "  Humid: bits 5-9   = " << (int)packet.getHumidity()
            << std::endl;
  std::cout << "  Light: bits 10-15 = " << (int)packet.getLight() << std::endl;

  std::cout << "\n💡 SAVINGS: 2 bytes instead of 6 = 67% reduction!"
            << std::endl;
  std::cout << "💡 REAL USE: LoRa, BLE, RF transmissions (every byte costs "
               "battery!)"
            << std::endl;
}

void gpio_demo() {
  std::cout << "\n=== SCENARIO 6: GPIO PORT CONTROL ===" << std::endl;
  std::cout << "PROBLEM: Control multiple pins simultaneously (atomic)"
            << std::endl;
  std::cout << "SOLUTION: Direct port manipulation (actual Arduino "
               "technique!)\n"
            << std::endl;

  GPIOPort portB;

  // Configure pins 3, 4, 5 as outputs (LED pins)
  uint8_t ledPins = (1 << 3) | (1 << 4) | (1 << 5); // 0b00111000
  portB.setOutputs(ledPins);
  std::cout << "Set pins 3,4,5 as OUTPUT:" << std::endl;
  std::cout << "  DDR:  " << std::bitset<8>(portB.getDDR()) << std::endl;

  // Turn all 3 LEDs on at once (atomic!)
  portB.setHigh(ledPins);
  std::cout << "Turn on all 3 LEDs at once:" << std::endl;
  std::cout << "  PORT: " << std::bitset<8>(portB.getPORT()) << std::endl;

  // Turn off just pin 4
  portB.setLow(1 << 4);
  std::cout << "Turn off pin 4:" << std::endl;
  std::cout << "  PORT: " << std::bitset<8>(portB.getPORT()) << std::endl;

  // Toggle all 3 at once
  portB.toggle(ledPins);
  std::cout << "Toggle all 3 LEDs:" << std::endl;
  std::cout << "  PORT: " << std::bitset<8>(portB.getPORT()) << std::endl;

  std::cout << "\n💡 WHY: Faster than digitalWrite() & truly atomic!"
            << std::endl;
  std::cout << "💡 REAL CODE: PORTB |= (1 << PB5);  // Arduino pin 13"
            << std::endl;
}

void status_flags_demo() {
  std::cout << "\n=== SCENARIO 7: DEVICE STATUS FLAGS ===" << std::endl;
  std::cout << "PROBLEM: Track multiple device states efficiently" << std::endl;
  std::cout << "SOLUTION: Pack 8 boolean states into 1 byte\n" << std::endl;

  DeviceStatus device;

  // Device startup sequence
  std::cout << "Device starting up:" << std::endl;
  device.set(DeviceStatus::POWERED_ON);
  std::cout << "  Status: " << std::bitset<8>(device.status) << " (powered on)"
            << std::endl;

  device.set(DeviceStatus::CALIBRATED);
  std::cout << "  Status: " << std::bitset<8>(device.status) << " (calibrated)"
            << std::endl;

  device.set(DeviceStatus::READY);
  std::cout << "  Status: " << std::bitset<8>(device.status) << " (ready)"
            << std::endl;

  // Check if operational
  bool operational = device.isOperational();
  std::cout << "Device operational? " << (operational ? "YES" : "NO")
            << std::endl;

  // Error condition
  device.set(DeviceStatus::ERROR);
  std::cout << "\nError occurred!" << std::endl;
  std::cout << "  Status: " << std::bitset<8>(device.status) << std::endl;
  std::cout << "  Operational? " << (device.isOperational() ? "YES" : "NO")
            << std::endl;

  // Low battery warning
  device.set(DeviceStatus::LOW_BATTERY);
  std::cout << "\nLow battery:" << std::endl;
  std::cout << "  Status: " << std::bitset<8>(device.status) << std::endl;
  std::cout << "  Multiple flags set: ERROR + LOW_BATTERY" << std::endl;

  std::cout << "\n💡 REAL USE: MCU status registers, device drivers, state "
               "machines"
            << std::endl;
}

void config_demo() {
  std::cout << "\n=== SCENARIO 8: CONFIGURATION PACKING ===" << std::endl;
  std::cout << "PROBLEM: Store serial port config (minimize EEPROM usage)"
            << std::endl;
  std::cout << "SOLUTION: Pack 5 settings into 1 byte!\n" << std::endl;

  DeviceConfig config;

  std::cout << "Configure serial port:" << std::endl;
  config.setBaudRate(3);     // 9600 baud
  config.setParity(1);       // Even parity
  config.setStopBits(false); // 1 stop bit
  config.setEcho(true);      // Echo on
  config.setFlowControl(false);

  std::cout << "Configuration byte: " << std::bitset<8>(config.data)
            << std::endl;
  std::cout << "\nBreakdown:" << std::endl;
  std::cout << "  Bits 0-2: Baud rate    = " << (int)config.getBaudRate()
            << std::endl;
  std::cout << "  Bits 3-4: Parity       = " << (int)config.getParity()
            << std::endl;
  std::cout << "  Bit  5:   Stop bits    = " << (config.getStopBits() ? 2 : 1)
            << std::endl;
  std::cout << "  Bit  6:   Echo         = "
            << (config.getEcho() ? "ON" : "OFF") << std::endl;
  std::cout << "  Bit  7:   Flow control = "
            << (config.getFlowControl() ? "ON" : "OFF") << std::endl;

  std::cout << "\n💡 SAVINGS: 1 byte instead of 5 = 80% reduction!"
            << std::endl;
  std::cout << "💡 REAL USE: EEPROM/Flash storage, config files, registers"
            << std::endl;
}

void real_world_demo() {
  std::cout
      << "\n\n╔═══════════════════════════════════════════════════════════╗"
      << std::endl;
  std::cout << "║       REAL-WORLD BITWISE OPERATIONS EXAMPLES          ║"
            << std::endl;
  std::cout << "╚═══════════════════════════════════════════════════════════╝"
            << std::endl;

  led_strip_demo();
  permissions_demo();
  network_demo();
  color_demo();
  sensor_packing_demo();
  gpio_demo();
  status_flags_demo();
  config_demo();

  std::cout
      << "\n\n╔═══════════════════════════════════════════════════════════╗"
      << std::endl;
  std::cout << "║                    KEY TAKEAWAYS                      ║"
            << std::endl;
  std::cout << "╚═══════════════════════════════════════════════════════════╝"
            << std::endl;
  std::cout << "\n1. MEMORY SAVINGS: Pack multiple values in fewer bytes"
            << std::endl;
  std::cout << "2. PERFORMANCE: Atomic operations (no race conditions)"
            << std::endl;
  std::cout << "3. BANDWIDTH: Send less data wirelessly (saves battery!)"
            << std::endl;
  std::cout << "4. HARDWARE: Direct register manipulation (Arduino, MCUs)"
            << std::endl;
  std::cout << "5. PROTOCOLS: TCP, HTTP, USB all use bit flags" << std::endl;
  std::cout << "6. EMBEDDED: Essential skill for microcontroller programming"
            << std::endl;
}
