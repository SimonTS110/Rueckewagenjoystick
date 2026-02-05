/*
 * Rueckewagenjoystick - Hydraulic Crane Control with Xbox Controller
 * 
 * This sketch controls a hydraulic crane using an Xbox Controller
 * connected via USB Host Shield to an Arduino Uno.
 * 
 * Hardware Requirements:
 * - Arduino Uno
 * - USB Host Shield (for Xbox Controller)
 * - 12 PWM MOSFETs (200Hz)
 * - 4 Digital MOSFETs (On/Off)
 * 
 * Required Libraries:
 * - USB Host Shield Library 2.0
 *   Install via Arduino Library Manager: "USB Host Shield Library 2.0"
 * 
 * Pin Configuration:
 * PWM Outputs (200Hz, ~5ms period):
 *   - Pin 3, 5, 6, 9, 10, 11 (Hardware PWM on Timer1 and Timer2)
 *   - Pin A0-A5 (Software PWM for remaining channels)
 * Digital Outputs:
 *   - Pin 2, 4, 7, 8
 * 
 * USB Host Shield uses:
 *   - Pin 13 (SCK)
 *   - Pin 12 (MISO)
 *   - Pin 11 (MOSI) - shared with PWM
 *   - Pin 10 (SS) - shared with PWM
 *   - Pin 9 (INT) - shared with PWM
 */

#include <XBOXUSB.h>

// USB and Xbox Controller
USB Usb;
XBOXUSB Xbox(&Usb);

// PWM Output Pins (12 channels)
// Using Timer1 (pins 9, 10) and Timer2 (pins 3, 11) for hardware PWM
// Remaining channels use software PWM
const int PWM_PINS[12] = {3, 5, 6, 9, 10, 11, A0, A1, A2, A3, A4, A5};
int pwmValues[12] = {0}; // PWM values 0-255

// Digital Output Pins (4 channels)
const int DIGITAL_PINS[4] = {2, 4, 7, 8};
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
    analogWrite(PWM_PINS[i], 0);
  }
  
  // Initialize digital pins
  for (int i = 0; i < 4; i++) {
    pinMode(DIGITAL_PINS[i], OUTPUT);
    digitalWrite(DIGITAL_PINS[i], LOW);
  }
  
  // Setup Timer1 for 200Hz PWM on pins 9 and 10
  setupTimer1PWM();
  
  // Setup Timer2 for 200Hz PWM on pins 3 and 11
  setupTimer2PWM();
  
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
  // Update hardware PWM pins with configured timers
  // Only pins 3, 9, 10, 11 have hardware PWM configured
  // Pins 5 and 6 use default Timer0 (not ideal but functional)
  analogWrite(PWM_PINS[0], pwmValues[0]); // Pin 3 - Timer2
  analogWrite(PWM_PINS[1], pwmValues[1]); // Pin 5 - Timer0 (millis() may be affected)
  analogWrite(PWM_PINS[2], pwmValues[2]); // Pin 6 - Timer0 (millis() may be affected)
  analogWrite(PWM_PINS[3], pwmValues[3]); // Pin 9 - Timer1
  analogWrite(PWM_PINS[4], pwmValues[4]); // Pin 10 - Timer1
  analogWrite(PWM_PINS[5], pwmValues[5]); // Pin 11 - Timer2
  
  // Software PWM for analog pins (A0-A5)
  // This is a simple software PWM implementation at 200Hz
  unsigned long currentMicros = micros();
  unsigned long elapsed = currentMicros - pwmCycleStart;
  
  if (elapsed >= PWM_PERIOD_US) {
    pwmCycleStart = currentMicros;
    elapsed = 0;
  }
  
  // Calculate duty cycle position
  for (int i = 6; i < 12; i++) {
    unsigned long onTime = (PWM_PERIOD_US * pwmValues[i]) / 255;
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
    analogWrite(PWM_PINS[i], 0);
    if (PWM_PINS[i] >= A0) {
      digitalWrite(PWM_PINS[i], LOW);
    }
  }
  
  for (int i = 0; i < 4; i++) {
    digitalStates[i] = false;
    digitalWrite(DIGITAL_PINS[i], LOW);
  }
}

void setupTimer1PWM() {
  // Timer1 controls pins 9 and 10
  // Set Timer1 for 200Hz PWM (5ms period)
  // Prescaler = 64, TOP = 1249 gives 200Hz on 16MHz Arduino
  
  TCCR1A = 0;
  TCCR1B = 0;
  
  // Set non-inverting mode for OC1A (pin 9) and OC1B (pin 10)
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
  
  // Set Fast PWM mode with ICR1 as TOP
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  
  // Set prescaler to 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  
  // Set TOP value for 200Hz
  // 16MHz / (64 * 200Hz) - 1 = 1249
  ICR1 = 1249;
  
  // Initialize duty cycle to 0
  OCR1A = 0;
  OCR1B = 0;
}

void setupTimer2PWM() {
  // Timer2 controls pins 3 and 11
  // Set Timer2 for approximately 200Hz PWM
  // Note: Timer2 is 8-bit, so exact 200Hz is challenging
  // Using prescaler 64, gives ~244Hz (22% faster than target)
  // This deviation may affect hydraulic valve performance
  // If 200Hz is critical, consider using only Timer1 pins (9, 10)
  // or implement additional timer configuration
  
  TCCR2A = 0;
  TCCR2B = 0;
  
  // Set non-inverting mode for OC2A (pin 11) and OC2B (pin 3)
  TCCR2A |= (1 << COM2A1) | (1 << COM2B1);
  
  // Set Fast PWM mode
  TCCR2A |= (1 << WGM20) | (1 << WGM21);
  
  // Set prescaler to 64
  TCCR2B |= (1 << CS22);
  
  // Initialize duty cycle to 0
  OCR2A = 0;
  OCR2B = 0;
}
