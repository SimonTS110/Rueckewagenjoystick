/*
 * Configuration File for Rueckewagenjoystick
 * 
 * This file allows easy customization of the crane control system
 * without modifying the main sketch code.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ========================================
// PWM Configuration
// ========================================

// PWM frequency for hydraulic valves (Hz)
#define PWM_FREQUENCY 200

// Dead zone for analog sticks (0-32767)
// Values below this threshold are treated as center position
#define STICK_DEADZONE 7500

// ========================================
// Pin Assignments
// ========================================

// PWM Output Pins (12 channels)
// Change these if you need different pin assignments
// WARNING: Pins 5 and 6 use Timer0, which is also used by millis() and delay()
// Using PWM on these pins may affect timing functions
// For critical applications, consider using only Timer1 (pins 9, 10) and Timer2 (pins 3, 11)
const int PWM_PIN_0 = 3;   // Timer2 (~244Hz, not exact 200Hz)
const int PWM_PIN_1 = 5;   // Timer0 (Warning: affects millis/delay)
const int PWM_PIN_2 = 6;   // Timer0 (Warning: affects millis/delay)
const int PWM_PIN_3 = 9;   // Timer1 (200Hz exact)
const int PWM_PIN_4 = 10;  // Timer1 (200Hz exact)
const int PWM_PIN_5 = 11;  // Timer2 (~244Hz, not exact 200Hz)
const int PWM_PIN_6 = A0;  // Software PWM (200Hz)
const int PWM_PIN_7 = A1;  // Software PWM (200Hz)
const int PWM_PIN_8 = A2;  // Software PWM (200Hz)
const int PWM_PIN_9 = A3;  // Software PWM (200Hz)
const int PWM_PIN_10 = A4; // Software PWM (200Hz)
const int PWM_PIN_11 = A5; // Software PWM (200Hz)

// Digital Output Pins (4 channels)
const int DIGITAL_PIN_0 = 2;
const int DIGITAL_PIN_1 = 4;
const int DIGITAL_PIN_2 = 7;
const int DIGITAL_PIN_3 = 8;

// ========================================
// Function Mapping
// ========================================

// Customize the mapping of crane functions to output channels
// These are just labels for documentation purposes

// PWM Channel Functions (Examples - customize as needed)
#define FUNCTION_PWM_0  "Crane Arm Left/Right"
#define FUNCTION_PWM_1  "Crane Arm Up/Down"
#define FUNCTION_PWM_2  "Turret Rotation"
#define FUNCTION_PWM_3  "Boom Extend/Retract"
#define FUNCTION_PWM_4  "Gripper Control"
#define FUNCTION_PWM_5  "Auxiliary 1"
#define FUNCTION_PWM_6  "Auxiliary 2"
#define FUNCTION_PWM_7  "Auxiliary 3"
#define FUNCTION_PWM_8  "Auxiliary 4"
#define FUNCTION_PWM_9  "Auxiliary 5"
#define FUNCTION_PWM_10 "Auxiliary 6"
#define FUNCTION_PWM_11 "Auxiliary 7"

// Digital Channel Functions (Examples - customize as needed)
#define FUNCTION_DIGITAL_0 "Work Lights"
#define FUNCTION_DIGITAL_1 "Hazard Lights"
#define FUNCTION_DIGITAL_2 "Horn"
#define FUNCTION_DIGITAL_3 "Auxiliary Switch"

// ========================================
// Controller Settings
// ========================================

// Invert axis if needed (true = inverted, false = normal)
#define INVERT_LEFT_STICK_X   false
#define INVERT_LEFT_STICK_Y   false
#define INVERT_RIGHT_STICK_X  false
#define INVERT_RIGHT_STICK_Y  false

// ========================================
// Safety Settings
// ========================================

// Enable serial output for debugging (true/false)
#define ENABLE_SERIAL_DEBUG true

// Serial baud rate
#define SERIAL_BAUD_RATE 115200

// Timeout for controller disconnection (milliseconds)
// After this time without controller, system goes to safe state
#define CONTROLLER_TIMEOUT_MS 1000

// ========================================
// Advanced Settings
// ========================================

// Minimum PWM value (0-255)
// Some valves need a minimum signal to operate
#define MIN_PWM_VALUE 0

// Maximum PWM value (0-255)
// Limit maximum output if needed
#define MAX_PWM_VALUE 255

// PWM filter constant (0.0-1.0)
// Smooth PWM changes: 1.0 = no smoothing, lower values = more smoothing
#define PWM_FILTER_ALPHA 0.8

#endif // CONFIG_H
