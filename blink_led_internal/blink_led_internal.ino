
#define LED_PORT PORTB
#define LED_PIN 13
#define DELAY 250

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // LED_PORT |= (1 << PB5); — Turn LED
  //     - (1 << PB5) shifts a 1 left by 5 positions, creating binary 00100000
  //     - |= performs a bitwise OR, setting bit 5 of PORTB to 1 without affecting other bits
  //     - PB5 corresponds to digital pin 13 on Arduino Uno
  LED_PORT |= (1 << PB5);
  delay(DELAY);
  // LED_PORT &= ~(1 << PB5); — Turn LED OFF
  //  - ~(1 << PB5) creates the inverse: 11011111
  //  - &= performs a bitwise AND, clearing only bit 5 while preserving other bits
  LED_PORT &= ~(1 << PB5);
  delay(DELAY);
}
