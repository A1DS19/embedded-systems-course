/*
Real-World Bitwise Operations Examples
Actual scenarios from embedded systems and microcontrollers
*/

#pragma once

#include <cstdint>

// ===== SCENARIO 1: LED STRIP CONTROL =====
// Control 8 LEDs with a single byte (save GPIO pins!)
class LEDStrip {
private:
  uint8_t ledState = 0x00; // Each bit = one LED (0=OFF, 1=ON)

public:
  // Turn on specific LED (0-7)
  void turnOn(uint8_t led) { ledState |= (1 << led); }

  // Turn off specific LED
  void turnOff(uint8_t led) { ledState &= ~(1 << led); }

  // Toggle LED (flip state)
  void toggle(uint8_t led) { ledState ^= (1 << led); }

  // Check if LED is on
  bool isOn(uint8_t led) const { return (ledState & (1 << led)) != 0; }

  // Turn on all LEDs
  void allOn() { ledState = 0xFF; }

  // Turn off all LEDs
  void allOff() { ledState = 0x00; }

  // Turn on multiple LEDs at once
  void setPattern(uint8_t pattern) { ledState = pattern; }

  // Get current state
  uint8_t getState() const { return ledState; }

  // Shift pattern left (chase effect)
  void shiftLeft() {
    ledState = (ledState << 1) | (ledState >> 7); // Circular shift
  }
};

// ===== SCENARIO 2: PERMISSION SYSTEM =====
// User permissions stored in single byte (like file permissions)
class Permissions {
public:
  // Permission flags
  static constexpr uint8_t READ = (1 << 0);    // 0b00000001
  static constexpr uint8_t WRITE = (1 << 1);   // 0b00000010
  static constexpr uint8_t EXECUTE = (1 << 2); // 0b00000100
  static constexpr uint8_t DELETE = (1 << 3);  // 0b00001000
  static constexpr uint8_t ADMIN = (1 << 4);   // 0b00010000

  uint8_t flags = 0;

  // Grant permission
  void grant(uint8_t permission) { flags |= permission; }

  // Revoke permission
  void revoke(uint8_t permission) { flags &= ~permission; }

  // Check if has permission
  bool has(uint8_t permission) const { return (flags & permission) != 0; }

  // Check multiple permissions at once
  bool hasAll(uint8_t permissions) const {
    return (flags & permissions) == permissions;
  }

  bool hasAny(uint8_t permissions) const { return (flags & permissions) != 0; }
};

// ===== SCENARIO 3: NETWORK PROTOCOL =====
// Pack/unpack TCP flags (like real TCP headers!)
class TCPFlags {
public:
  // TCP Control flags
  static constexpr uint8_t FIN = (1 << 0); // Finish
  static constexpr uint8_t SYN = (1 << 1); // Synchronize
  static constexpr uint8_t RST = (1 << 2); // Reset
  static constexpr uint8_t PSH = (1 << 3); // Push
  static constexpr uint8_t ACK = (1 << 4); // Acknowledgment
  static constexpr uint8_t URG = (1 << 5); // Urgent

  uint8_t flags = 0;

  void setFlag(uint8_t flag) { flags |= flag; }
  void clearFlag(uint8_t flag) { flags &= ~flag; }
  bool isSet(uint8_t flag) const { return (flags & flag) != 0; }

  // Common combinations
  bool isSYNACK() const { return (flags & (SYN | ACK)) == (SYN | ACK); }
  bool isFINACK() const { return (flags & (FIN | ACK)) == (FIN | ACK); }
};

// ===== SCENARIO 4: RGB COLOR MANIPULATION =====
// Work with 24-bit RGB colors (like in displays, LEDs)
class RGBColor {
private:
  uint32_t color = 0x000000; // 0xRRGGBB

public:
  RGBColor(uint8_t r, uint8_t g, uint8_t b) {
    color = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  }

  // Extract individual color channels
  uint8_t getRed() const { return (color >> 16) & 0xFF; }
  uint8_t getGreen() const { return (color >> 8) & 0xFF; }
  uint8_t getBlue() const { return color & 0xFF; }

  // Set individual channels
  void setRed(uint8_t r) { color = (color & 0x00FFFF) | ((uint32_t)r << 16); }
  void setGreen(uint8_t g) { color = (color & 0xFF00FF) | ((uint32_t)g << 8); }
  void setBlue(uint8_t b) { color = (color & 0xFFFF00) | b; }

  // Dim by dividing by 2 (fast!)
  void dim() { color = (color >> 1) & 0x7F7F7F; }

  // Brighten by multiplying by 2 (with clamping)
  void brighten() {
    uint8_t r = getRed();
    uint8_t g = getGreen();
    uint8_t b = getBlue();
    r = (r << 1) > 255 ? 255 : (r << 1);
    g = (g << 1) > 255 ? 255 : (g << 1);
    b = (b << 1) > 255 ? 255 : (b << 1);
    color = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  }

  uint32_t getValue() const { return color; }
};

// ===== SCENARIO 5: SENSOR DATA PACKING =====
// Pack multiple sensor readings into minimal bytes (save memory/bandwidth)
class SensorPacket {
private:
  // Pack 3 sensors into 2 bytes instead of 6!
  uint16_t data = 0;
  // Bits 0-4:   Temperature (0-31)  → 5 bits
  // Bits 5-9:   Humidity (0-31)     → 5 bits
  // Bits 10-15: Light (0-63)        → 6 bits

public:
  void setTemperature(uint8_t temp) {
    temp &= 0x1F; // Mask to 5 bits (0-31)
    data = (data & 0xFFE0) | temp;
  }

  void setHumidity(uint8_t humid) {
    humid &= 0x1F; // Mask to 5 bits
    data = (data & 0xFC1F) | (humid << 5);
  }

  void setLight(uint8_t light) {
    light &= 0x3F; // Mask to 6 bits (0-63)
    data = (data & 0x03FF) | (light << 10);
  }

  uint8_t getTemperature() const { return data & 0x1F; }
  uint8_t getHumidity() const { return (data >> 5) & 0x1F; }
  uint8_t getLight() const { return (data >> 10) & 0x3F; }

  uint16_t getRawData() const { return data; }
};

// ===== SCENARIO 6: GPIO PORT CONFIGURATION =====
// Configure multiple pins at once (like real Arduino registers)
class GPIOPort {
private:
  uint8_t PORT = 0x00; // Output values
  uint8_t DDR = 0x00;  // Data direction (0=input, 1=output)
  uint8_t PIN = 0x00;  // Input values (simulated)

public:
  // Configure multiple pins as output at once
  void setOutputs(uint8_t pinMask) { DDR |= pinMask; }

  // Configure multiple pins as input at once
  void setInputs(uint8_t pinMask) { DDR &= ~pinMask; }

  // Set multiple pins HIGH at once (atomic operation!)
  void setHigh(uint8_t pinMask) { PORT |= pinMask; }

  // Set multiple pins LOW at once
  void setLow(uint8_t pinMask) { PORT &= ~pinMask; }

  // Toggle multiple pins at once
  void toggle(uint8_t pinMask) { PORT ^= pinMask; }

  // Write pattern to port
  void write(uint8_t value) { PORT = value; }

  // Read entire port
  uint8_t read() const { return PIN; }

  uint8_t getPORT() const { return PORT; }
  uint8_t getDDR() const { return DDR; }
};

// ===== SCENARIO 7: STATUS FLAGS =====
// Device status with multiple flags (like in real hardware)
class DeviceStatus {
public:
  static constexpr uint8_t POWERED_ON = (1 << 0);
  static constexpr uint8_t CONNECTED = (1 << 1);
  static constexpr uint8_t ERROR = (1 << 2);
  static constexpr uint8_t BUSY = (1 << 3);
  static constexpr uint8_t READY = (1 << 4);
  static constexpr uint8_t CALIBRATED = (1 << 5);
  static constexpr uint8_t LOW_BATTERY = (1 << 6);
  static constexpr uint8_t OVERHEATING = (1 << 7);

  uint8_t status = 0;

  void set(uint8_t flag) { status |= flag; }
  void clear(uint8_t flag) { status &= ~flag; }
  bool isSet(uint8_t flag) const { return (status & flag) != 0; }

  // Check if device is operational
  bool isOperational() const {
    return (status & (POWERED_ON | READY | CALIBRATED)) ==
               (POWERED_ON | READY | CALIBRATED) &&
           (status & (ERROR | OVERHEATING)) == 0;
  }
};

// ===== SCENARIO 8: BIT FIELDS (Struct Packing) =====
// Pack configuration into minimal space
struct DeviceConfig {
  uint8_t data = 0;
  // Bit 0-2: Baud rate (0-7)
  // Bit 3-4: Parity (0-3)
  // Bit 5:   Stop bits (0=1 bit, 1=2 bits)
  // Bit 6:   Echo (0=off, 1=on)
  // Bit 7:   Flow control (0=off, 1=on)

  void setBaudRate(uint8_t rate) {
    data = (data & 0xF8) | (rate & 0x07); // Keep upper 5 bits, set lower 3
  }
  void setParity(uint8_t parity) {
    data = (data & 0xE7) | ((parity & 0x03) << 3);
  }
  void setStopBits(bool two) { data = two ? (data | 0x20) : (data & ~0x20); }
  void setEcho(bool on) { data = on ? (data | 0x40) : (data & ~0x40); }
  void setFlowControl(bool on) { data = on ? (data | 0x80) : (data & ~0x80); }

  uint8_t getBaudRate() const { return data & 0x07; }
  uint8_t getParity() const { return (data >> 3) & 0x03; }
  bool getStopBits() const { return (data & 0x20) != 0; }
  bool getEcho() const { return (data & 0x40) != 0; }
  bool getFlowControl() const { return (data & 0x80) != 0; }
};

// Demo functions
void real_world_demo();
void led_strip_demo();
void permissions_demo();
void network_demo();
void color_demo();
void sensor_packing_demo();
void gpio_demo();
void status_flags_demo();
void config_demo();
