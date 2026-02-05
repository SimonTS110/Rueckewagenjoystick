/*
 * Rueckewagenjoystick - Simple Test Example
 * 
 * This is a simplified version for testing the basic functionality
 * without requiring all hardware to be connected.
 * 
 * Use this to verify:
 * - USB Host Shield is working
 * - Xbox Controller connects properly
 * - Basic input reading is functional
 * 
 * Upload this sketch first to test your hardware setup before
 * using the full version.
 */

#include <XBOXUSB.h>

// USB and Xbox Controller
USB Usb;
XBOXUSB Xbox(&Usb);

// Test LED (built-in LED on pin 13)
const int LED_PIN = 13;

void setup() {
  Serial.begin(115200);
  // Wait for serial port with timeout (max 2 seconds)
  // This allows standalone operation without computer
  unsigned long serialTimeout = millis() + 2000;
  while (!Serial && millis() < serialTimeout);
  
  Serial.println(F("================================="));
  Serial.println(F("Rueckewagenjoystick - Test Mode"));
  Serial.println(F("================================="));
  Serial.println();
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Initialize USB Host Shield
  if (Usb.Init() == -1) {
    Serial.println(F("ERROR: USB Host Shield initialization failed!"));
    Serial.println(F("Please check:"));
    Serial.println(F("  1. Shield is properly seated on Arduino"));
    Serial.println(F("  2. Shield power connections are good"));
    Serial.println(F("  3. You have the correct USB Host Shield Library installed"));
    while (1) {
      // Blink LED rapidly to indicate error
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
  }
  
  Serial.println(F("USB Host Shield initialized successfully!"));
  Serial.println(F("Waiting for Xbox Controller..."));
  Serial.println(F("Please connect your Xbox Controller now."));
  Serial.println();
}

void loop() {
  Usb.Task();
  
  if (Xbox.Xbox360Connected) {
    // Blink LED slowly to show controller is connected
    static unsigned long lastBlink = 0;
    if (millis() - lastBlink > 1000) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      lastBlink = millis();
    }
    
    // Print controller status every 500ms
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 500) {
      printControllerStatus();
      lastPrint = millis();
    }
    
    // Check for button clicks
    if (Xbox.getButtonClick(A)) {
      Serial.println(F(">>> A Button Pressed"));
    }
    if (Xbox.getButtonClick(B)) {
      Serial.println(F(">>> B Button Pressed"));
    }
    if (Xbox.getButtonClick(X)) {
      Serial.println(F(">>> X Button Pressed"));
    }
    if (Xbox.getButtonClick(Y)) {
      Serial.println(F(">>> Y Button Pressed"));
    }
    if (Xbox.getButtonClick(START)) {
      Serial.println(F(">>> START Button Pressed - EMERGENCY STOP!"));
    }
    if (Xbox.getButtonClick(BACK)) {
      Serial.println(F(">>> BACK Button Pressed"));
    }
    if (Xbox.getButtonClick(L3)) {
      Serial.println(F(">>> L3 (Left Stick) Pressed"));
    }
    if (Xbox.getButtonClick(R3)) {
      Serial.println(F(">>> R3 (Right Stick) Pressed"));
    }
  } else {
    // No controller - turn off LED
    digitalWrite(LED_PIN, LOW);
    
    // Print waiting message every 2 seconds
    static unsigned long lastWait = 0;
    if (millis() - lastWait > 2000) {
      Serial.println(F("Still waiting for Xbox Controller..."));
      lastWait = millis();
    }
  }
}

void printControllerStatus() {
  // Read all analog values
  int leftX = Xbox.getAnalogHat(LeftHatX);
  int leftY = Xbox.getAnalogHat(LeftHatY);
  int rightX = Xbox.getAnalogHat(RightHatX);
  int rightY = Xbox.getAnalogHat(RightHatY);
  
  // Check if any stick is moved significantly
  const int threshold = 10000;
  bool leftStickMoved = (abs(leftX) > threshold || abs(leftY) > threshold);
  bool rightStickMoved = (abs(rightX) > threshold || abs(rightY) > threshold);
  
  // Only print if there's significant input
  if (leftStickMoved || rightStickMoved || 
      Xbox.getButtonPress(L2) > 0 || Xbox.getButtonPress(R2) > 0) {
    
    Serial.println(F("--- Controller Status ---"));
    
    if (leftStickMoved) {
      Serial.print(F("Left Stick:  X="));
      Serial.print(leftX);
      Serial.print(F("  Y="));
      Serial.println(leftY);
    }
    
    if (rightStickMoved) {
      Serial.print(F("Right Stick: X="));
      Serial.print(rightX);
      Serial.print(F("  Y="));
      Serial.println(rightY);
    }
    
    if (Xbox.getButtonPress(L2) > 0) {
      Serial.print(F("L2 Trigger: "));
      Serial.println(Xbox.getButtonPress(L2));
    }
    
    if (Xbox.getButtonPress(R2) > 0) {
      Serial.print(F("R2 Trigger: "));
      Serial.println(Xbox.getButtonPress(R2));
    }
    
    // Print D-Pad state
    if (Xbox.getButtonPress(UP) || Xbox.getButtonPress(DOWN) || 
        Xbox.getButtonPress(LEFT) || Xbox.getButtonPress(RIGHT)) {
      Serial.print(F("D-Pad: "));
      if (Xbox.getButtonPress(UP)) Serial.print(F("UP "));
      if (Xbox.getButtonPress(DOWN)) Serial.print(F("DOWN "));
      if (Xbox.getButtonPress(LEFT)) Serial.print(F("LEFT "));
      if (Xbox.getButtonPress(RIGHT)) Serial.print(F("RIGHT "));
      Serial.println();
    }
    
    // Print shoulder buttons
    if (Xbox.getButtonPress(L1) || Xbox.getButtonPress(R1)) {
      Serial.print(F("Shoulders: "));
      if (Xbox.getButtonPress(L1)) Serial.print(F("L1 "));
      if (Xbox.getButtonPress(R1)) Serial.print(F("R1 "));
      Serial.println();
    }
    
    Serial.println();
  }
}
