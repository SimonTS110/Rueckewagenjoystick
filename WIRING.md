# Verkabelung / Wiring Diagram

## Deutsch

### Hardware-Anforderungen

1. **Arduino Uno** - Mikrocontroller-Board
2. **USB Host Shield** - Für Xbox Controller Verbindung
3. **12x PWM MOSFET Module** - Für proportionale Steuerung (200Hz)
4. **4x Digital MOSFET Module** - Für Ein/Aus-Steuerung
5. **Xbox Controller** - Mit USB-Kabel
6. **Externe Stromversorgung** - Für MOSFETs und Hydraulikventile

### Pin-Belegung Arduino Uno

#### PWM Ausgänge (12 Kanäle, 200Hz)

| Kanal | Arduino Pin | Timer | Funktion (Beispiel) |
|-------|-------------|-------|---------------------|
| 0 | D3 | Timer2 | Kranarm Heben/Senken |
| 1 | D5 | Timer0 | Kranarm Schwenken Links/Rechts |
| 2 | D6 | Timer0 | Ausleger Ein/Aus |
| 3 | D9 | Timer1 | Greifer Öffnen/Schließen |
| 4 | D10 | Timer1 | Drehkranz Links/Rechts |
| 5 | D11 | Timer2 | Reserve 1 |
| 6 | A0 | Software | Reserve 2 |
| 7 | A1 | Software | Reserve 3 |
| 8 | A2 | Software | Reserve 4 |
| 9 | A3 | Software | Reserve 5 |
| 10 | A4 | Software | Reserve 6 |
| 11 | A5 | Software | Reserve 7 |

#### Digitale Ausgänge (4 Kanäle)

| Kanal | Arduino Pin | Funktion (Beispiel) |
|-------|-------------|---------------------|
| 0 | D2 | Arbeitsscheinwerfer |
| 1 | D4 | Warnblinkanlage |
| 2 | D7 | Zusatzfunktion 1 |
| 3 | D8 | Zusatzfunktion 2 |

#### USB Host Shield Pins (reserviert)

| Signal | Arduino Pin |
|--------|-------------|
| SCK | D13 |
| MISO | D12 |
| MOSI | D11 (geteilt mit PWM) |
| SS | D10 (geteilt mit PWM) |
| INT | D9 (geteilt mit PWM) |

### Xbox Controller Mapping

#### Analoge Eingänge

| Xbox Eingabe | PWM Kanal | Funktion |
|--------------|-----------|----------|
| Linker Stick X-Achse | 0 | Kranarm Links/Rechts |
| Linker Stick Y-Achse | 1 | Kranarm Heben/Senken |
| Rechter Stick X-Achse | 2 | Drehkranz Links/Rechts |
| Rechter Stick Y-Achse | 3 | Ausleger Ein/Aus |
| L2 Trigger | 4 | Zusatzfunktion PWM 1 |
| R2 Trigger | 5 | Zusatzfunktion PWM 2 |

#### Digitale Eingänge

| Xbox Taste | PWM Kanal | Funktion |
|------------|-----------|----------|
| D-Pad Oben | 6 | PWM Kanal 6 |
| D-Pad Unten | 7 | PWM Kanal 7 |
| D-Pad Links | 8 | PWM Kanal 8 |
| D-Pad Rechts | 9 | PWM Kanal 9 |
| L1 (LB) | 10 | PWM Kanal 10 |
| R1 (RB) | 11 | PWM Kanal 11 |
| A Taste | Digital 0 | Ein/Aus Funktion 1 |
| B Taste | Digital 1 | Ein/Aus Funktion 2 |
| X Taste | Digital 2 | Ein/Aus Funktion 3 |
| Y Taste | Digital 3 | Ein/Aus Funktion 4 |
| START Taste | - | Not-Aus (alle Ausgänge aus) |
| BACK Taste | - | Reset |

### Verkabelungsschema

```
Arduino Uno + USB Host Shield
├── PWM Ausgänge → MOSFET Module → Hydraulik Proportionalventile
│   ├── D3 → PWM MOSFET 0 → Ventil 0
│   ├── D5 → PWM MOSFET 1 → Ventil 1
│   ├── D6 → PWM MOSFET 2 → Ventil 2
│   ├── D9 → PWM MOSFET 3 → Ventil 3
│   ├── D10 → PWM MOSFET 4 → Ventil 4
│   ├── D11 → PWM MOSFET 5 → Ventil 5
│   ├── A0 → PWM MOSFET 6 → Ventil 6
│   ├── A1 → PWM MOSFET 7 → Ventil 7
│   ├── A2 → PWM MOSFET 8 → Ventil 8
│   ├── A3 → PWM MOSFET 9 → Ventil 9
│   ├── A4 → PWM MOSFET 10 → Ventil 10
│   └── A5 → PWM MOSFET 11 → Ventil 11
│
├── Digitale Ausgänge → MOSFET Module → Schaltventile/Relais
│   ├── D2 → Digital MOSFET 0 → Funktion 0
│   ├── D4 → Digital MOSFET 1 → Funktion 1
│   ├── D7 → Digital MOSFET 2 → Funktion 2
│   └── D8 → Digital MOSFET 3 → Funktion 3
│
└── USB Host Shield → Xbox Controller (USB)
```

### MOSFET Modul Verkabelung

#### Für jedes PWM MOSFET Modul:
- **Signal (PWM)** ← Arduino PWM Pin
- **GND** ← Arduino GND (gemeinsame Masse)
- **VCC** ← Externe Versorgung (z.B. 12V/24V für Hydraulikventile)
- **Last+** → Hydraulik Proportionalventil
- **Last-** → GND (Versorgung)

#### Für jedes digitale MOSFET Modul:
- **Signal (Digital)** ← Arduino Digital Pin
- **GND** ← Arduino GND (gemeinsame Masse)
- **VCC** ← Externe Versorgung
- **Last+** → Schaltventil/Relais
- **Last-** → GND (Versorgung)

### Wichtige Hinweise

⚠️ **Sicherheit:**
1. Verwenden Sie eine separate Stromversorgung für die MOSFETs
2. Niemals Arduino-Pins direkt mit Hochstromlasten verbinden
3. Implementieren Sie einen Not-Aus-Schalter (START-Taste)
4. Testen Sie die Steuerung ohne Last, bevor Sie sie mit Hydraulik verbinden
5. Stellen Sie sicher, dass alle Massen (GND) miteinander verbunden sind

⚠️ **PWM Frequenz:**
- Hardware PWM (Pins 3, 5, 6, 9, 10, 11): ~200Hz via Timer
- Software PWM (Pins A0-A5): 200Hz in Software implementiert

---

## English

### Hardware Requirements

1. **Arduino Uno** - Microcontroller board
2. **USB Host Shield** - For Xbox Controller connection
3. **12x PWM MOSFET Modules** - For proportional control (200Hz)
4. **4x Digital MOSFET Modules** - For On/Off control
5. **Xbox Controller** - With USB cable
6. **External Power Supply** - For MOSFETs and hydraulic valves

### Arduino Uno Pin Assignment

#### PWM Outputs (12 channels, 200Hz)

| Channel | Arduino Pin | Timer | Function (Example) |
|---------|-------------|-------|-------------------|
| 0 | D3 | Timer2 | Crane Arm Up/Down |
| 1 | D5 | Timer0 | Crane Arm Swing Left/Right |
| 2 | D6 | Timer0 | Boom Extend/Retract |
| 3 | D9 | Timer1 | Gripper Open/Close |
| 4 | D10 | Timer1 | Turret Left/Right |
| 5 | D11 | Timer2 | Reserve 1 |
| 6 | A0 | Software | Reserve 2 |
| 7 | A1 | Software | Reserve 3 |
| 8 | A2 | Software | Reserve 4 |
| 9 | A3 | Software | Reserve 5 |
| 10 | A4 | Software | Reserve 6 |
| 11 | A5 | Software | Reserve 7 |

#### Digital Outputs (4 channels)

| Channel | Arduino Pin | Function (Example) |
|---------|-------------|-------------------|
| 0 | D2 | Work Lights |
| 1 | D4 | Hazard Lights |
| 2 | D7 | Auxiliary Function 1 |
| 3 | D8 | Auxiliary Function 2 |

#### USB Host Shield Pins (Reserved)

| Signal | Arduino Pin |
|--------|-------------|
| SCK | D13 |
| MISO | D12 |
| MOSI | D11 (shared with PWM) |
| SS | D10 (shared with PWM) |
| INT | D9 (shared with PWM) |

### Xbox Controller Mapping

#### Analog Inputs

| Xbox Input | PWM Channel | Function |
|------------|-------------|----------|
| Left Stick X-Axis | 0 | Crane Arm Left/Right |
| Left Stick Y-Axis | 1 | Crane Arm Up/Down |
| Right Stick X-Axis | 2 | Turret Left/Right |
| Right Stick Y-Axis | 3 | Boom Extend/Retract |
| L2 Trigger | 4 | Auxiliary PWM Function 1 |
| R2 Trigger | 5 | Auxiliary PWM Function 2 |

#### Digital Inputs

| Xbox Button | PWM Channel | Function |
|-------------|-------------|----------|
| D-Pad Up | 6 | PWM Channel 6 |
| D-Pad Down | 7 | PWM Channel 7 |
| D-Pad Left | 8 | PWM Channel 8 |
| D-Pad Right | 9 | PWM Channel 9 |
| L1 (LB) | 10 | PWM Channel 10 |
| R1 (RB) | 11 | PWM Channel 11 |
| A Button | Digital 0 | On/Off Function 1 |
| B Button | Digital 1 | On/Off Function 2 |
| X Button | Digital 2 | On/Off Function 3 |
| Y Button | Digital 3 | On/Off Function 4 |
| START Button | - | Emergency Stop (all outputs off) |
| BACK Button | - | Reset |

### Wiring Diagram

```
Arduino Uno + USB Host Shield
├── PWM Outputs → MOSFET Modules → Hydraulic Proportional Valves
│   ├── D3 → PWM MOSFET 0 → Valve 0
│   ├── D5 → PWM MOSFET 1 → Valve 1
│   ├── D6 → PWM MOSFET 2 → Valve 2
│   ├── D9 → PWM MOSFET 3 → Valve 3
│   ├── D10 → PWM MOSFET 4 → Valve 4
│   ├── D11 → PWM MOSFET 5 → Valve 5
│   ├── A0 → PWM MOSFET 6 → Valve 6
│   ├── A1 → PWM MOSFET 7 → Valve 7
│   ├── A2 → PWM MOSFET 8 → Valve 8
│   ├── A3 → PWM MOSFET 9 → Valve 9
│   ├── A4 → PWM MOSFET 10 → Valve 10
│   └── A5 → PWM MOSFET 11 → Valve 11
│
├── Digital Outputs → MOSFET Modules → Switching Valves/Relays
│   ├── D2 → Digital MOSFET 0 → Function 0
│   ├── D4 → Digital MOSFET 1 → Function 1
│   ├── D7 → Digital MOSFET 2 → Function 2
│   └── D8 → Digital MOSFET 3 → Function 3
│
└── USB Host Shield → Xbox Controller (USB)
```

### MOSFET Module Wiring

#### For each PWM MOSFET Module:
- **Signal (PWM)** ← Arduino PWM Pin
- **GND** ← Arduino GND (common ground)
- **VCC** ← External Supply (e.g., 12V/24V for hydraulic valves)
- **Load+** → Hydraulic Proportional Valve
- **Load-** → GND (Supply)

#### For each Digital MOSFET Module:
- **Signal (Digital)** ← Arduino Digital Pin
- **GND** ← Arduino GND (common ground)
- **VCC** ← External Supply
- **Load+** → Switching Valve/Relay
- **Load-** → GND (Supply)

### Important Notes

⚠️ **Safety:**
1. Use separate power supply for MOSFETs
2. Never connect Arduino pins directly to high-current loads
3. Implement an emergency stop switch (START button)
4. Test the control without load before connecting to hydraulics
5. Ensure all grounds (GND) are connected together

⚠️ **PWM Frequency:**
- Hardware PWM (Pins 3, 5, 6, 9, 10, 11): ~200Hz via Timer
- Software PWM (Pins A0-A5): 200Hz implemented in software
