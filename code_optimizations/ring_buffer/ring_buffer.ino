// ============================================================
// Ring Buffer — Practical Example: UART Command Parser
// ============================================================
// Real-world problem:
//   Serial bytes arrive byte-by-byte at any time.
//   You can't block loop() waiting for a full command.
//   You can't afford to miss bytes while processing.
//
// Solution: ring buffer between the receiver and the processor.
//   → Receiver pushes bytes in  (could be an ISR in real firmware)
//   → loop() pops bytes out and assembles commands
//   → They run at different speeds — the buffer absorbs the gap
//
// Commands arrive as: "LED:ON\n", "LED:OFF\n", "READ:TEMP\n"
// ============================================================

// ---- Ring Buffer ----------------------------------------

const int BUF_SIZE = 64;

struct RingBuffer {
  char data[BUF_SIZE];
  volatile int head  0;  // volatile: written by ISR in real firmware
  volatile int tail  0;
  volatile int count = 0;
};

bool push(RingBuffer& rb, char c) {
  if (rb.count == BUF_SIZE) return false;  // full — byte dropped
  rb.data[rb.head] = c;
  rb.head = (rb.head + 1) % BUF_SIZE;
  rb.count++;
  return true;
}

bool pop(RingBuffer& rb, char& out) {
  if (rb.count == 0) return false;
  out = rb.data[rb.tail];
  rb.tail = (rb.tail + 1) % BUF_SIZE;
  rb.count--;
  return true;
}

bool isEmpty(RingBuffer& rb) {
  
  return rb.count == 0;
}

// ---- Command processor ----------------------------------

RingBuffer rxBuf;

// Called when a complete command (terminated by '\n') is ready
void handleCommand(const char* cmd) {
  Serial.print("[CMD] received: \"");
  Serial.print(cmd);
  Serial.println("\"");

  if (strcmp(cmd, "LED:ON") == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("  → LED turned ON");

  } else if (strcmp(cmd, "LED:OFF") == 0) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("  → LED turned OFF");

  } else if (strcmp(cmd, "READ:TEMP") == 0) {
    int raw = a ogRead(A0);
    float voltage = raw * (5.0 / 1023.0);
    float tempC = (voltage - 0.5) * 100.0;  // TMP36 formula
    Serial.print("  → Temperature: ");
    Serial.print(tempC);
    Serial.println(" °C");

  } else {
    Serial.println("  → Unknown command");
  }
}

// Reads bytes from the ring buffer, builds a command, fires handleCommand()
// when '\n' is found. Non-blocking — exits immediately if buffer is empty.
void process ffer() {
  static char cmdBuf[32];  // assembles the current command
  static int cmdLen = 0;

  char c;
  while (pop(rxBuf, c)) {
    if (c == '\n' || c == '\r') {
      if (cmdLen > 0) {
        cmdBuf[cmdL  // null-terminate
        handleCommand(cmdBuf);
        cmdLen = 0;  // reset for next command
      }
    } else if (cmdLen < (int)sizeof(cmdBuf) - 1) {
      cmdBuf[cmdLen++] = c;
    }
    // else: command too long — silently discard overflow
  }
}

// ---- Setup & Loop ---------------------------------------

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Ready. Send: LED:ON  LED:OFF  READ:TEMP");
  Serial.println("(or watch the simulation below)\n");

  // --- Simulation: push a sequence of commands into the buffer
  //     as if they arrived byte-by-byte over UART ---
  const char* incoming = "LED:ON\nREAD:TEMP\nLED:OFF\nBAD:CMD\n";
  for (int i = 0; incoming[i] != '\0'; i++) {
    push(rxBuf, incoming[i]);
  }
}

void loop() {
  // In real firmware: Serial bytes come in via interrupt → push into rxBuf
  // Here we also accept live Serial input so you can test interactively
  while (Serial.available()) {
    push(rxBuf, (char)Serial.read());
  }

 
}
