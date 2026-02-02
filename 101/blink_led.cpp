#include "blink_led.h"

BlinkLed::BlinkLed(uint8_t pin)
    : pin_(pin), state_(false), last_toggle_time_(0) {}

void BlinkLed::begin() {
  pinMode(pin_, OUTPUT);
  off();
}

void BlinkLed::on() {
  state_ = true;
  digitalWrite(pin_, HIGH);
}

void BlinkLed::off() {
  state_ = false;
  digitalWrite(pin_, LOW);
}

void BlinkLed::toggle() {
  if (state_) {
    off();
  } else {
    on();
  }
}

bool BlinkLed::update(unsigned long interval_ms) {
  unsigned long now = millis();

  if (now - last_toggle_time_ >= interval_ms) {
    toggle();
    last_toggle_time_ = now;
    return true; // State changed
  }
  return false;
}

void BlinkLed::blink(unsigned long on_time_ms, unsigned long off_time_ms) {
  on();
  delay(on_time_ms);
  off();
  delay(off_time_ms);
}

bool BlinkLed::is_on() const { return state_; }
