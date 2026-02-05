# Quick Start Guide / Schnellstart-Anleitung

## Deutsch - Schnellstart

### Schritt 1: Hardware vorbereiten
1. ✅ Arduino Uno
2. ✅ USB Host Shield aufgesteckt
3. ✅ Xbox Controller bereit
4. ✅ 12 PWM MOSFET Module
5. ✅ 4 Digital MOSFET Module

### Schritt 2: Software installieren
1. Arduino IDE herunterladen und installieren
2. In Arduino IDE: `Sketch → Bibliothek einbinden → Bibliotheken verwalten`
3. Suchen: "USB Host Shield Library 2.0"
4. Installieren: Bibliothek von Oleg Mazurov

### Schritt 3: Test ohne Last
1. Öffnen Sie `examples/SimpleTest/SimpleTest.ino`
2. Wählen Sie Board: `Tools → Board → Arduino Uno`
3. Wählen Sie Port: `Tools → Port → [Ihr COM Port]`
4. Hochladen: Klicken Sie auf den Upload-Button
5. Öffnen Sie Serial Monitor (Strg+Shift+M)
6. Stellen Sie Baudrate auf 115200
7. Schließen Sie Xbox Controller an
8. Überprüfen Sie, dass Controller erkannt wird

### Schritt 4: Verkabelung (siehe WIRING.md für Details)
⚠️ **WICHTIG: Externe Stromversorgung für MOSFETs verwenden!**

**Für jedes MOSFET Modul:**
- Signal → Arduino Pin (siehe Tabelle unten)
- GND → Arduino GND + Externe GND (gemeinsame Masse!)
- VCC → Externe Versorgung (12V oder 24V)
- Last+ → Hydraulikventil
- Last- → GND Versorgung

**PWM Pins (empfohlen für beste Leistung):**
- Pin 9, 10 → Primäre Ventile (exakt 200Hz, Timer1)
- Pin 3, 11 → Sekundäre Ventile (~244Hz, Timer2)
- Pin 5, 6 → Zusätzliche Ventile (Standard PWM)
- Pin A0-A5 → Weitere Ventile (Software PWM)

**Digital Pins:**
- Pin 2, 4, 7, 8 → Ein/Aus Funktionen

### Schritt 5: Hauptprogramm hochladen
1. Öffnen Sie `Rueckewagenjoystick.ino`
2. Laden Sie es hoch
3. Öffnen Sie Serial Monitor
4. Überprüfen Sie Status-Meldungen

### Schritt 6: Konfiguration anpassen
1. Öffnen Sie `config.h`
2. Passen Sie Pin-Zuordnungen an Ihre Hardware an
3. Passen Sie Totzone an: `#define STICK_DEADZONE 7500`
4. Speichern und erneut hochladen

### Schritt 7: Testen mit Last
1. ⚠️ **Sicherstellen, dass Not-Aus verfügbar ist**
2. Verbinden Sie ein Ventil als Test
3. Testen Sie langsam mit kleinen Bewegungen
4. Überprüfen Sie Reaktion und Richtung
5. Bei Bedarf invertieren Sie Achsen in config.h

### Controller-Layout (Beispiel)
```
    [LB]  Kanal 10              Kanal 11  [RB]
    [LT]  Kanal 4                Kanal 5  [RT]
    
     ╔═══╗                              ╔═╗
     ║ ↑ ║ Kanal 6                [Y] 3 ║X║ 2
   ╔═╬═══╬═╗                        ╔═══╬═╬═╗
   ║←║ ↓ ║→║ K7,8,9          [X] 2 ║   ║B║ 1 [A] 0
   ╚═╩═══╩═╝                        ╚═══╩═╩═╝
   
   [LS]                                    [RS]
   Kanal 0,1                               Kanal 2,3
   
   [BACK]  Reset      [START]  Not-Aus
```

### Troubleshooting
Siehe [TROUBLESHOOTING.md](TROUBLESHOOTING.md) für häufige Probleme

---

## English - Quick Start

### Step 1: Prepare Hardware
1. ✅ Arduino Uno
2. ✅ USB Host Shield mounted
3. ✅ Xbox Controller ready
4. ✅ 12 PWM MOSFET Modules
5. ✅ 4 Digital MOSFET Modules

### Step 2: Install Software
1. Download and install Arduino IDE
2. In Arduino IDE: `Sketch → Include Library → Manage Libraries`
3. Search: "USB Host Shield Library 2.0"
4. Install: Library by Oleg Mazurov

### Step 3: Test Without Load
1. Open `examples/SimpleTest/SimpleTest.ino`
2. Select Board: `Tools → Board → Arduino Uno`
3. Select Port: `Tools → Port → [Your COM Port]`
4. Upload: Click the Upload button
5. Open Serial Monitor (Ctrl+Shift+M)
6. Set baud rate to 115200
7. Connect Xbox Controller
8. Verify controller is detected

### Step 4: Wiring (see WIRING.md for details)
⚠️ **IMPORTANT: Use external power supply for MOSFETs!**

**For each MOSFET Module:**
- Signal → Arduino Pin (see table below)
- GND → Arduino GND + External GND (common ground!)
- VCC → External supply (12V or 24V)
- Load+ → Hydraulic valve
- Load- → GND supply

**PWM Pins (recommended for best performance):**
- Pins 9, 10 → Primary valves (exactly 200Hz, Timer1)
- Pins 3, 11 → Secondary valves (~244Hz, Timer2)
- Pins 5, 6 → Additional valves (standard PWM)
- Pins A0-A5 → More valves (software PWM)

**Digital Pins:**
- Pins 2, 4, 7, 8 → On/Off functions

### Step 5: Upload Main Program
1. Open `Rueckewagenjoystick.ino`
2. Upload it
3. Open Serial Monitor
4. Check status messages

### Step 6: Customize Configuration
1. Open `config.h`
2. Adjust pin assignments to your hardware
3. Adjust dead zone: `#define STICK_DEADZONE 7500`
4. Save and re-upload

### Step 7: Test With Load
1. ⚠️ **Ensure emergency stop is available**
2. Connect one valve for testing
3. Test slowly with small movements
4. Check response and direction
5. Invert axes in config.h if needed

### Controller Layout (Example)
```
    [LB]  Channel 10           Channel 11  [RB]
    [LT]  Channel 4             Channel 5  [RT]
    
     ╔═══╗                              ╔═╗
     ║ ↑ ║ Channel 6              [Y] 3 ║X║ 2
   ╔═╬═══╬═╗                        ╔═══╬═╬═╗
   ║←║ ↓ ║→║ Ch7,8,9        [X] 2 ║   ║B║ 1 [A] 0
   ╚═╩═══╩═╝                        ╚═══╩═╩═╝
   
   [LS]                                    [RS]
   Channel 0,1                             Channel 2,3
   
   [BACK]  Reset      [START]  E-Stop
```

### Troubleshooting
See [TROUBLESHOOTING.md](TROUBLESHOOTING.md) for common issues

---

## Safety Checklist / Sicherheits-Checkliste

### Vor dem ersten Betrieb / Before First Operation
- [ ] Hardware-Not-Aus installiert / Hardware E-Stop installed
- [ ] Alle Massen verbunden / All grounds connected
- [ ] Separate Stromversorgung für MOSFETs / Separate power for MOSFETs
- [ ] Sicherungen für alle Ausgänge / Fuses for all outputs
- [ ] Test ohne Last erfolgreich / Test without load successful
- [ ] Ventile richtig verkabelt / Valves correctly wired
- [ ] Controller-Eingaben überprüft / Controller inputs verified
- [ ] Dokumentation gelesen / Documentation read

### Während des Betriebs / During Operation
- ⚠️ START-Taste = Not-Aus / E-Stop
- ⚠️ Controller im Blick behalten / Keep controller in sight
- ⚠️ Bei Problemen sofort stoppen / Stop immediately if issues
- ⚠️ Hydraulikdruck überwachen / Monitor hydraulic pressure

---

## Support

**Dokumentation:**
- [README.md](README.md) - Hauptdokumentation / Main documentation
- [WIRING.md](WIRING.md) - Verkabelung / Wiring
- [PARTS_LIST.md](PARTS_LIST.md) - Teileliste / Parts list
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) - Fehlerbehebung / Troubleshooting
- [config.h](config.h) - Konfiguration / Configuration

**Bei Problemen:**
1. Lesen Sie TROUBLESHOOTING.md
2. Überprüfen Sie Serial Monitor Ausgabe
3. Testen Sie mit SimpleTest Beispiel
4. Öffnen Sie Issue auf GitHub
