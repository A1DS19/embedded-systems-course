#include "blink_led.h"

// Built-in LED on most Arduinos (pin 13)
constexpr uint8_t LED_PIN = LED_BUILTIN;
constexpr unsigned long BLINK_INTERVAL_MS = 500;

// Create LED instance
BlinkLed led(LED_PIN);

void setup() {
  Serial.begin(115200);
  Serial.print(F("\n\rBlink LED Demo"));

  led.begin();
}

void loop() {
  // Non-blocking blink - doesn't use delay()
  if (led.update(BLINK_INTERVAL_MS)) {
    // Print state when it changes
    if (led.is_on()) {
      Serial.print(F("\n\rLED ON"));
    } else {
      Serial.print(F("\n\rLED OFF"));
    }
  }

  // Can do other stuff here without blocking
}
