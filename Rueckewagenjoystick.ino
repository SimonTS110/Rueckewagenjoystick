/*
 * Rueckewagenjoystick - Hydraulic Crane Control with Xbox Controller
 *
 * This sketch controls a hydraulic crane using an Xbox Controller
 * connected via USB Host Shield to an Arduino Mega2560.
 *
 * Hardware Requirements:
 * - Arduino Mega2560
 * - USB Host Shield (for Xbox Controller)
 * - 12 PWM MOSFETs (200Hz)
 * - 4 Digital MOSFETs (On/Off)
 *
 * Required Libraries:
 * - USB Host Shield Library 2.0
 *   Install via Arduino Library Manager: "USB Host Shield Library 2.0"
 *
 * Pin Configuration (Mega2560 mapping used by this sketch):
 * PWM Outputs (12 channels): pins 22..33 (software PWM)
 * Digital Outputs (4 channels): pins 34..37
 *
 * USB Host Shield uses SPI pins available via the 6-pin ICSP header
 * on the Mega2560 (MOSI/MISO/SCK). Verify your shield wiring and
 * any SS/INT pin assignments for your specific shield.
 */

#include <XBOXUSB.h>

// USB and Xbox Controller
USB Usb;
XBOXUSB Xbox(&Usb);

// PWM Output Pins (12 channels) and digital outputs (4 channels)
// This sketch targets the Arduino Mega2560. All channels are driven
// with software PWM at 200Hz for consistent behaviour across boards.
const int PWM_PINS[12] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
const int DIGITAL_PINS[4] = {34, 35, 36, 37};
int pwmValues[12] = {0}; // PWM values 0-255

bool digitalStates[4] = {false};

// PWM Configuration
const int PWM_FREQUENCY = 200; // 200Hz as required
const unsigned long PWM_PERIOD_US = 1000000 / PWM_FREQUENCY; // 5000 microseconds

// Software PWM timing
unsigned long lastPWMUpdate = 0;
unsigned long pwmCycleStart = 0;
int pwmPhase = 0;

// Deadzone for analog sticks
const int DEADZONE = 7500; // Range is -32768 to 32767

void setup() {
  Serial.begin(115200);
  // Wait for serial port with timeout (max 3 seconds)
  // This allows operation without computer connection
  unsigned long serialTimeout = millis() + 3000;
  while (!Serial && millis() < serialTimeout);
  
  Serial.println(F("Hydraulic Crane Control - Rueckewagenjoystick"));
  Serial.println(F("Initializing..."));
  
  // Initialize PWM pins
  for (int i = 0; i < 12; i++) {
    pinMode(PWM_PINS[i], OUTPUT);
    digitalWrite(PWM_PINS[i], LOW);
  }
  
  // Initialize digital pins
  for (int i = 0; i < 4; i++) {
    pinMode(DIGITAL_PINS[i], OUTPUT);
    digitalWrite(DIGITAL_PINS[i], LOW);
  }
  
  // Using software PWM for all channels; timers are left unmodified.
  
  // Initialize USB Host Shield
  if (Usb.Init() == -1) {
    Serial.println(F("USB Host Shield initialization failed!"));
    while (1); // Halt
  }
  
  Serial.println(F("USB Host Shield initialized"));
  Serial.println(F("Waiting for Xbox Controller..."));
}

void loop() {
  Usb.Task();
  
  if (Xbox.Xbox360Connected) {
    // Read Xbox Controller inputs and map to crane controls
    readXboxController();
    
    // Update PWM outputs
    updatePWMOutputs();
    
    // Update digital outputs
    updateDigitalOutputs();
  } else {
    // No controller connected - set everything to safe state
    setSafeState();
  }
}

void readXboxController() {
  // Left Stick X & Y - Control channels 0 and 1
  int leftX = Xbox.getAnalogHat(LeftHatX);
  int leftY = Xbox.getAnalogHat(LeftHatY);
  pwmValues[0] = mapStickToPWM(leftX);
  pwmValues[1] = mapStickToPWM(leftY);
  
  // Right Stick X & Y - Control channels 2 and 3
  int rightX = Xbox.getAnalogHat(RightHatX);
  int rightY = Xbox.getAnalogHat(RightHatY);
  pwmValues[2] = mapStickToPWM(rightX);
  pwmValues[3] = mapStickToPWM(rightY);
  
  // Triggers - Control channels 4 and 5
  pwmValues[4] = Xbox.getButtonPress(L2);
  pwmValues[5] = Xbox.getButtonPress(R2);
  
  // D-Pad - Control channels 6, 7, 8, 9
  pwmValues[6] = Xbox.getButtonPress(UP) ? 255 : 0;
  pwmValues[7] = Xbox.getButtonPress(DOWN) ? 255 : 0;
  pwmValues[8] = Xbox.getButtonPress(LEFT) ? 255 : 0;
  pwmValues[9] = Xbox.getButtonPress(RIGHT) ? 255 : 0;
  
  // Shoulder buttons - Control channels 10 and 11
  pwmValues[10] = Xbox.getButtonPress(L1) ? 255 : 0;
  pwmValues[11] = Xbox.getButtonPress(R1) ? 255 : 0;
  
  // Face buttons - Control digital outputs
  digitalStates[0] = Xbox.getButtonPress(A);
  digitalStates[1] = Xbox.getButtonPress(B);
  digitalStates[2] = Xbox.getButtonPress(X);
  digitalStates[3] = Xbox.getButtonPress(Y);
  
  // Button press feedback
  if (Xbox.getButtonClick(START)) {
    Serial.println(F("START pressed - Emergency stop"));
    setSafeState();
  }
  
  if (Xbox.getButtonClick(BACK)) {
    Serial.println(F("BACK pressed - Reset"));
  }
}

int mapStickToPWM(int stickValue) {
  // Xbox stick range: -32768 to 32767
  // Apply deadzone
  if (abs(stickValue) < DEADZONE) {
    return 128; // Center position (50% PWM)
  }
  
  // Map to 0-255 PWM range
  // Negative values: 0-127, Positive values: 128-255
  int mapped = map(stickValue, -32768, 32767, 0, 255);
  return constrain(mapped, 0, 255);
}

void updatePWMOutputs() {
  // Software PWM for all 12 channels at PWM_FREQUENCY
  unsigned long currentMicros = micros();
  unsigned long elapsed = currentMicros - pwmCycleStart;

  if (elapsed >= PWM_PERIOD_US) {
    pwmCycleStart = currentMicros;
    elapsed = 0;
  }

  for (int i = 0; i < 12; i++) {
    unsigned long onTime = (PWM_PERIOD_US * (unsigned long)pwmValues[i]) / 255UL;
    digitalWrite(PWM_PINS[i], elapsed < onTime ? HIGH : LOW);
  }
}

void updateDigitalOutputs() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(DIGITAL_PINS[i], digitalStates[i] ? HIGH : LOW);
  }
}

void setSafeState() {
  // Set all outputs to safe state (all off or neutral)
  for (int i = 0; i < 12; i++) {
    pwmValues[i] = 0;
    digitalWrite(PWM_PINS[i], LOW);
  }
  
  for (int i = 0; i < 4; i++) {
    digitalStates[i] = false;
    digitalWrite(DIGITAL_PINS[i], LOW);
  }
}

