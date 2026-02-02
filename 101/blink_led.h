#ifndef BLINK_LED_H
#define BLINK_LED_H

#include <Arduino.h>

// ============================================================================
// BlinkLed - Simple LED controller
// ============================================================================

class BlinkLed {
public:
  // Constructor - specify pin
  explicit BlinkLed(uint8_t pin);

  // Initialize the pin (call in setup())
  void begin();

  // Turn LED on/off
  void on();
  void off();
  void toggle();

  // Non-blocking blink (call in loop())
  // Returns true when state changes
  bool update(unsigned long interval_ms);

  // Blocking blink
  void blink(unsigned long on_time_ms, unsigned long off_time_ms);

  // Getters
  bool is_on() const;

private:
  uint8_t pin_;
  bool state_;
  unsigned long last_toggle_time_;
};

#endif // BLINK_LED_H
