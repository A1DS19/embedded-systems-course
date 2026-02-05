const int ANALOG_VRx = A0;
const int ANALOG_VRy = A1;
const int DIGITAL_SW = 11;
const int DELAY = 100;

void setup() {
  Serial.begin(115200);
  Serial.write("\n\rSetup\n\r");

  pinMode(ANALOG_VRx, INPUT);
  pinMode(ANALOG_VRy, INPUT);
  pinMode(DIGITAL_SW, INPUT_PULLUP);
}

void loop() {
  int joystick_x = analogRead(ANALOG_VRx);
  int joystick_y = analogRead(ANALOG_VRy);
  int joystick_sw = analogRead(DIGITAL_SW);

  static char msg_buffer[100];
  sprintf(msg_buffer, "\n\rX = %d | Y = %d | Button = %d", joystick_x, joystick_y, joystick_sw);

  Serial.write(msg_buffer);

  delay(DELAY);
}
