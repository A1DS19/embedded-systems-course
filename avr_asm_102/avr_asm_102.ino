uint8_t volatile numbers[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

extern "C" {
  uint16_t asm_add(uint16_t a, uint16_t b);
  uint16_t asm_mul(uint16_t a, uint16_t b);
  void asm_iterate_numbers(uint8_t *numbers);
}

void setup() {
  Serial.begin(115200);

  uint16_t result_add = asm_add(8, 8);
  Serial.println(result_add);

  uint16_t result_mul = asm_mul(10, 10);
  Serial.println(result_mul);

  asm_iterate_numbers(numbers);
  for (auto number : numbers) {
    Serial.println(number);
  }
}

void loop() {
}
