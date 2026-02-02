const char NUMBER_1[] PROGMEM = "\n\rHello world";

void setup() {
  Serial.begin(115200);
  Serial.print(F("\n\rSetup"));
}

void loop() {
  Serial.print((__FlashStringHelper *)NUMBER_1);
  delay(1000);
}
