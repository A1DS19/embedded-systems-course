uint8_t volatile counter = 0;
uint8_t delay_ms = 250;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Increment counter using inline assembly:
  // - lds: load counter from RAM into r16
  // - inc: increment r16
  // - sts: store r16 back to counter in RAM
  // The clobber list ("r16") tells GCC we modify r16, so it won't use
  // that register for other values across this asm block.
  asm volatile(
    "lds r16, counter \n\t"
    "inc r16          \n\t"
    "sts counter, r16" ::: "r16");
  delay(delay_ms);

  char msg_buffer[sizeof(uint8_t)];
  sprintf(msg_buffer, "\n\r%d", counter);

  // Reset program when counter reaches 255:
  // - lds: load counter from RAM into r16
  // - cpi: compare r16 with immediate value 255 (sets zero flag if equal)
  // - breq: branch to "reset" label if zero flag is set (values were equal)
  // - rjmp: skip over reset code if not equal
  // - jmp 0: jump to address 0 (program start) to restart
  asm volatile(
    "lds r16, counter \n\t"
    "cpi r16, 255     \n\t"
    "breq reset       \n\t"
    "rjmp done        \n\t"
    "reset: jmp 0     \n\t"
    "done:" ::: "r16");

  Serial.print(msg_buffer);
}
