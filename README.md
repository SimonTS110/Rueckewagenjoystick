# Rueckewagenjoystick
Hydraulischer Kran Steuerung mit Xbox Controller / Hydraulic Crane Control with Xbox Controller

_Last updated: 2026-02-05_

## Deutsch

### Übersicht
Dieses Projekt ermöglicht die Steuerung eines hydraulischen Krans mit einem Xbox Controller, der über ein USB Host Shield an einen Arduino Uno angeschlossen ist.

**Features:**
- 12 PWM Ausgänge (200Hz) für proportionale Hydrauliksteuerung
- 4 digitale Ausgänge für Ein/Aus-Funktionen
- Xbox Controller Unterstützung via USB Host Shield
- Not-Aus Funktion (START-Taste)
- Totzone für Analog-Sticks
- Detaillierte Dokumentation und Beispiele

### Hardware-Anforderungen
- Arduino Uno
- USB Host Shield 2.0
- Xbox Controller (USB)
- 12x PWM MOSFET Module für Proportionalventile
- 4x Digitale MOSFET Module für Schaltfunktionen
- Externe Stromversorgung für MOSFETs

### Software-Anforderungen
- Arduino IDE (1.8.x oder höher) oder alternative: PlatformIO / Arduino CLI
- USB Host Shield Library 2.0 (über Library Manager) oder passende PlatformIO-Bibliothek

### Installation

#### 1. Arduino IDE installieren
Laden Sie die Arduino IDE von [arduino.cc](https://www.arduino.cc/en/software) herunter und installieren Sie sie.

#### 2. USB Host Shield Library installieren
1. Öffnen Sie Arduino IDE (oder nutzen Sie PlatformIO)
2. In Arduino IDE: `Sketch → Bibliothek einbinden → Bibliotheken verwalten`
3. Suchen Sie nach "USB Host Shield Library 2.0" und installieren Sie sie (Autor: Oleg Mazurov)
4. Bei PlatformIO: fügen Sie die entsprechende Library in `platformio.ini` hinzu

#### 3. Sketch hochladen
1. Öffnen Sie `Rueckewagenjoystick.ino` in Arduino IDE oder in Ihrem PlatformIO-Projekt
2. Wählen Sie Board: `Arduino Uno`
3. Wählen Sie den richtigen COM-Port
4. Klicken Sie auf "Hochladen"

### Verkabelung
Detaillierte Verkabelungsanweisungen finden Sie in [WIRING.md](WIRING.md). Beispiele finden Sie auch unter [examples/SimpleTest](examples/SimpleTest).

### Verwendung
1. Schließen Sie das USB Host Shield an den Arduino Uno an
2. Laden Sie den Sketch hoch
3. Verbinden Sie den Xbox Controller mit dem USB Host Shield
4. Öffnen Sie den Seriellen Monitor (115200 Baud) zur Diagnose
5. Warten Sie auf "Xbox Controller Connected"
6. Steuern Sie den Kran mit dem Controller

**Controller Layout:**
- **Linker Stick**: Kranarm Position (X/Y)
- **Rechter Stick**: Drehkranz und Ausleger
- **L2/R2 Trigger**: Zusatzfunktionen PWM
- **D-Pad**: Zusätzliche PWM Kanäle
- **L1/R1**: Weitere PWM Kanäle
- **A/B/X/Y Tasten**: Digitale Ein/Aus Funktionen
- **START**: Not-Aus (alle Ausgänge werden deaktiviert)
- **BACK**: Reset

### Sicherheitshinweise
⚠️ **WICHTIG:**
- Testen Sie das System ohne Last, bevor Sie es mit Hydraulik verbinden
- Implementieren Sie zusätzliche Hardware-Sicherungen
- Die START-Taste dient als Software-Not-Aus
- Verwenden Sie immer eine separate Stromversorgung für MOSFETs
- Stellen Sie sicher, dass alle Massen verbunden sind

### Konfiguration
Die Pin-Belegung und Funktionszuordnung können im Sketch angepasst werden:
- `PWM_PINS[]` - PWM Ausgangspins
- `DIGITAL_PINS[]` - Digitale Ausgangspins
- `DEADZONE` - Totzone für Analog-Sticks (Standard: 7500)
- `PWM_FREQUENCY` - PWM Frequenz (Standard: 200Hz)

### Fehlerbehebung
- **"USB Host Shield initialization failed"**: Überprüfen Sie USB Host Shield Verbindung
- **"Waiting for Xbox Controller"**: Controller anschließen und einschalten
- **Keine Ausgaben**: Überprüfen Sie MOSFET Verkabelung und Stromversorgung

---

## English

### Overview
This project enables control of a hydraulic crane using an Xbox Controller connected to an Arduino Uno via a USB Host Shield.

**Features:**
- 12 PWM outputs (200Hz) for proportional hydraulic control
- 4 digital outputs for on/off functions
- Xbox Controller support via USB Host Shield
- Emergency stop function (START button)
- Dead zone for analog sticks
- Detailed documentation and examples

### Hardware Requirements
- Arduino Uno
- USB Host Shield 2.0
- Xbox Controller (USB)
- 12x PWM MOSFET Modules for proportional valves
- 4x Digital MOSFET Modules for switching functions
- External power supply for MOSFETs

### Software Requirements
- Arduino IDE (1.8.x or higher)
- USB Host Shield Library 2.0

### Installation

#### 1. Install Arduino IDE
Download and install Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software).

#### 2. Install USB Host Shield Library
1. Open Arduino IDE
2. Go to: `Sketch → Include Library → Manage Libraries`
3. Search for "USB Host Shield Library 2.0"
4. Install the library by Oleg Mazurov

#### 3. Upload Sketch
1. Open `Rueckewagenjoystick.ino` in Arduino IDE
2. Select Board: `Arduino Uno`
3. Select the correct COM port
4. Click "Upload"

### Wiring
See [WIRING.md](WIRING.md) for detailed wiring instructions.

### Usage
1. Connect USB Host Shield to Arduino Uno
2. Upload the sketch
3. Connect Xbox Controller to USB Host Shield
4. Open Serial Monitor (115200 baud) for diagnostics
5. Wait for "Xbox Controller Connected"
6. Control the crane with the controller

**Controller Layout:**
- **Left Stick**: Crane arm position (X/Y)
- **Right Stick**: Turret and boom
- **L2/R2 Triggers**: Auxiliary PWM functions
- **D-Pad**: Additional PWM channels
- **L1/R1**: More PWM channels
- **A/B/X/Y Buttons**: Digital on/off functions
- **START**: Emergency stop (all outputs disabled)
- **BACK**: Reset

### Safety Notes
⚠️ **IMPORTANT:**
- Test the system without load before connecting to hydraulics
- Implement additional hardware safety measures
- START button serves as software emergency stop
- Always use separate power supply for MOSFETs
- Ensure all grounds are connected

### Configuration
Pin assignments and function mappings can be customized in the sketch:
- `PWM_PINS[]` - PWM output pins
- `DIGITAL_PINS[]` - Digital output pins
- `DEADZONE` - Dead zone for analog sticks (default: 7500)
- `PWM_FREQUENCY` - PWM frequency (default: 200Hz)

### Troubleshooting
- **"USB Host Shield initialization failed"**: Check USB Host Shield connection
- **"Waiting for Xbox Controller"**: Connect and turn on controller
- **No outputs**: Check MOSFET wiring and power supply

### License
This project is open source. Use at your own risk.

### Contributing
Contributions are welcome! Please open an issue or pull request.

### Author
SimonTS110
