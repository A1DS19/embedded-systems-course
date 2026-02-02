static auto NUMBER_1 = "\n\r" + String(1, BIN);

void setup() {
  Serial.begin(115200);
  Serial.write("\n\rSetup");
}

void loop() {
  Serial.write(NUMBER_1.c_str());
  delay(1000);
}
