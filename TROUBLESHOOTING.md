# Troubleshooting Guide / Fehlerbehebung

## Deutsch

### Häufige Probleme und Lösungen

#### 1. "USB Host Shield initialization failed!"

**Problem:** Das USB Host Shield wird nicht erkannt.

**Mögliche Ursachen und Lösungen:**

- ✅ **Shield nicht richtig aufgesteckt**
  - Lösung: Entfernen Sie das Shield und stecken Sie es erneut auf. Achten Sie darauf, dass alle Pins richtig in den Buchsen stecken.

- ✅ **Falsche Bibliothek installiert**
  - Lösung: Stellen Sie sicher, dass Sie "USB Host Shield Library 2.0" von Oleg Mazurov installiert haben, nicht eine andere USB-Bibliothek.
  - In Arduino IDE: Sketch → Bibliothek einbinden → Bibliotheken verwalten → "USB Host Shield Library 2.0" suchen

- ✅ **Stromversorgung unzureichend**
  - Lösung: Verwenden Sie eine externe Stromversorgung für den Arduino (7-12V, min. 500mA). USB-Stromversorgung vom PC kann für Shield + Controller unzureichend sein.

#### 2. "Waiting for Xbox Controller..." (Controller verbindet nicht)

**Problem:** Controller wird nicht erkannt.

**Mögliche Ursachen und Lösungen:**

- ✅ **Controller nicht eingeschaltet**
  - Lösung: Bei kabellosem Controller: Drücken Sie die Xbox-Taste zum Einschalten
  - Bei kabelgebundenem Controller: Sollte automatisch funktionieren

- ✅ **USB-Kabel defekt**
  - Lösung: Testen Sie das Kabel an einem PC. Verwenden Sie ein anderes Kabel.

- ✅ **Controller nicht kompatibel**
  - Lösung: Verwenden Sie einen originalen Xbox 360 oder Xbox One Controller
  - Getestete Controller: Xbox 360 wired, Xbox One wired
  - Nicht unterstützt: Drahtlose Controller ohne USB-Dongle

- ✅ **USB-Anschluss am Shield defekt**
  - Lösung: Überprüfen Sie die Lötstellen am USB-Anschluss des Shields

#### 3. PWM Ausgänge funktionieren nicht

**Problem:** MOSFETs schalten nicht oder zeigen falsches Verhalten.

**Mögliche Ursachen und Lösungen:**

- ✅ **Falsche Verkabelung**
  - Lösung: Überprüfen Sie die Verkabelung gemäß [WIRING.md](WIRING.md)
  - Signal-Pin → Arduino PWM Pin
  - GND → Arduino GND (gemeinsame Masse!)
  - VCC → Externe Versorgung (NICHT Arduino 5V)

- ✅ **MOSFET-Module nicht logic-level**
  - Lösung: Verwenden Sie logic-level MOSFETs (schalten bei 5V)
  - Empfohlen: IRF520, IRLZ44N, oder ähnliche

- ✅ **Keine gemeinsame Masse**
  - Lösung: Verbinden Sie GND vom Arduino mit GND der externen Stromversorgung

- ✅ **Überlast / Überhitzung**
  - Lösung: Fügen Sie Kühlkörper hinzu, reduzieren Sie die Last, oder verwenden Sie stärkere MOSFETs

#### 4. Digitale Ausgänge funktionieren nicht

**Problem:** Digitale MOSFETs schalten nicht.

**Lösungen:**
- Überprüfen Sie die Pin-Zuordnung in der config.h
- Testen Sie mit eingebautem LED (Pin 13) zur Diagnose
- Messen Sie Spannung am digitalen Ausgang (sollte 5V bei HIGH sein)
- Überprüfen Sie MOSFET-Verkabelung

#### 5. Controller-Eingaben sind ungenau oder springen

**Problem:** Hydraulik-Bewegungen sind ruckelig oder instabil.

**Lösungen:**

- ✅ **Deadzone anpassen**
  ```cpp
  #define STICK_DEADZONE 7500  // Erhöhen für größere Totzone
  ```

- ✅ **PWM-Frequenz zu niedrig**
  - Überprüfen Sie, dass Timer richtig konfiguriert sind
  - Software-PWM auf A0-A5 kann weniger stabil sein
  - **Wichtig:** Timer2 (Pins 3, 11) läuft bei ~244Hz, nicht 200Hz
  - Für exakt 200Hz verwenden Sie Timer1 (Pins 9, 10)

- ✅ **Mechanisches Problem**
  - Überprüfen Sie Hydraulik-Ventile auf korrekte Funktion
  - Stellen Sie sicher, dass Ventile für 200Hz PWM geeignet sind

#### 6. Sketch kompiliert nicht

**Problem:** Fehler beim Kompilieren.

**Häufige Fehler:**

- ❌ `XBOXUSB.h: No such file or directory`
  - Lösung: Installieren Sie "USB Host Shield Library 2.0"

- ❌ `'Xbox' was not declared in this scope`
  - Lösung: Überprüfen Sie include-Anweisungen am Anfang der Datei

- ❌ Timer-bezogene Fehler
  - Lösung: Code ist für Arduino Uno optimiert. Für andere Boards müssen Timer-Einstellungen angepasst werden.

#### 7. Serielle Ausgabe zeigt Müll / unleserliche Zeichen

**Problem:** Serial Monitor zeigt falsche Zeichen.

**Lösung:**
- Stellen Sie die Baudrate auf 115200 ein
- In Arduino IDE: Serial Monitor → Dropdown unten rechts → 115200 baud

#### 8. System geht in Sicherheitsmodus (alle Ausgänge aus)

**Problem:** Ausgänge schalten spontan ab.

**Mögliche Ursachen:**

- ✅ **Controller-Timeout**
  - Controller verliert Verbindung
  - Lösung: Überprüfen Sie USB-Kabel und Stromversorgung

- ✅ **START-Taste gedrückt**
  - Dies ist gewünschtes Verhalten (Not-Aus)
  - Lösung: Nicht START drücken während des Betriebs

- ✅ **Stromunterbrechung**
  - Lösung: Stabilere Stromversorgung verwenden

### Erweiterte Diagnose

#### Serial Monitor verwenden

Öffnen Sie den Serial Monitor (Strg+Shift+M) bei 115200 baud für detaillierte Diagnose:

```
Erwartete Ausgabe beim Start:
Hydraulic Crane Control - Rueckewagenjoystick
Initializing...
USB Host Shield initialized
Waiting for Xbox Controller...
```

Bei verbundenem Controller sollten Sie Echtzeitwerte sehen.

#### LED-Diagnose

Das SimpleTest Beispiel verwendet die eingebaute LED (Pin 13):
- **Schnelles Blinken (5Hz)**: USB Host Shield Fehler
- **Langsames Blinken (1Hz)**: Controller verbunden, alles OK
- **Aus**: Wartet auf Controller

#### Multimeter-Tests

1. **Arduino Spannung testen:**
   - Zwischen 5V und GND: sollte ~5V sein
   - Zwischen VIN und GND: sollte 7-12V sein (wenn extern versorgt)

2. **PWM Signal testen:**
   - Zwischen PWM Pin und GND
   - Sollte variierende Spannung 0-5V zeigen

3. **MOSFET Ausgang testen:**
   - Zwischen Last+ und Last- am MOSFET
   - Sollte Lastspannung zeigen wenn aktiviert

---

## English

### Common Problems and Solutions

#### 1. "USB Host Shield initialization failed!"

**Problem:** USB Host Shield is not detected.

**Possible Causes and Solutions:**

- ✅ **Shield not properly seated**
  - Solution: Remove and reseat the shield. Ensure all pins are properly inserted.

- ✅ **Wrong library installed**
  - Solution: Make sure you have "USB Host Shield Library 2.0" by Oleg Mazurov installed, not another USB library.
  - In Arduino IDE: Sketch → Include Library → Manage Libraries → Search "USB Host Shield Library 2.0"

- ✅ **Insufficient power supply**
  - Solution: Use external power supply for Arduino (7-12V, min. 500mA). USB power from PC may be insufficient for Shield + Controller.

#### 2. "Waiting for Xbox Controller..." (Controller not connecting)

**Problem:** Controller is not recognized.

**Possible Causes and Solutions:**

- ✅ **Controller not turned on**
  - Solution: For wireless controller: Press Xbox button to turn on
  - For wired controller: Should work automatically

- ✅ **USB cable defective**
  - Solution: Test cable on PC. Try different cable.

- ✅ **Controller not compatible**
  - Solution: Use original Xbox 360 or Xbox One controller
  - Tested controllers: Xbox 360 wired, Xbox One wired
  - Not supported: Wireless controllers without USB dongle

- ✅ **USB port on shield defective**
  - Solution: Check solder joints on shield's USB connector

#### 3. PWM outputs not working

**Problem:** MOSFETs not switching or showing incorrect behavior.

**Possible Causes and Solutions:**

- ✅ **Incorrect wiring**
  - Solution: Check wiring according to [WIRING.md](WIRING.md)
  - Signal Pin → Arduino PWM Pin
  - GND → Arduino GND (common ground!)
  - VCC → External supply (NOT Arduino 5V)

- ✅ **MOSFET modules not logic-level**
  - Solution: Use logic-level MOSFETs (switch at 5V)
  - Recommended: IRF520, IRLZ44N, or similar

- ✅ **No common ground**
  - Solution: Connect GND from Arduino to GND of external power supply

- ✅ **Overload / Overheating**
  - Solution: Add heat sinks, reduce load, or use stronger MOSFETs

#### 4. Digital outputs not working

**Problem:** Digital MOSFETs not switching.

**Solutions:**
- Check pin assignment in config.h
- Test with built-in LED (pin 13) for diagnosis
- Measure voltage at digital output (should be 5V at HIGH)
- Check MOSFET wiring

#### 5. Controller inputs are inaccurate or jumpy

**Problem:** Hydraulic movements are jerky or unstable.

**Solutions:**

- ✅ **Adjust deadzone**
  ```cpp
  #define STICK_DEADZONE 7500  // Increase for larger dead zone
  ```

- ✅ **PWM frequency too low**
  - Verify timers are configured correctly
  - Software PWM on A0-A5 may be less stable
  - **Important:** Timer2 (pins 3, 11) runs at ~244Hz, not 200Hz
  - For exactly 200Hz, use Timer1 (pins 9, 10)

- ✅ **Mechanical problem**
  - Check hydraulic valves for correct function
  - Ensure valves are suitable for 200Hz PWM

#### 6. Sketch does not compile

**Problem:** Compilation errors.

**Common Errors:**

- ❌ `XBOXUSB.h: No such file or directory`
  - Solution: Install "USB Host Shield Library 2.0"

- ❌ `'Xbox' was not declared in this scope`
  - Solution: Check include statements at beginning of file

- ❌ Timer-related errors
  - Solution: Code is optimized for Arduino Uno. For other boards, timer settings must be adjusted.

#### 7. Serial output shows garbage / unreadable characters

**Problem:** Serial Monitor shows wrong characters.

**Solution:**
- Set baud rate to 115200
- In Arduino IDE: Serial Monitor → Dropdown bottom right → 115200 baud

#### 8. System goes to safe mode (all outputs off)

**Problem:** Outputs spontaneously turn off.

**Possible Causes:**

- ✅ **Controller timeout**
  - Controller loses connection
  - Solution: Check USB cable and power supply

- ✅ **START button pressed**
  - This is intended behavior (emergency stop)
  - Solution: Don't press START during operation

- ✅ **Power interruption**
  - Solution: Use more stable power supply

### Advanced Diagnostics

#### Using Serial Monitor

Open Serial Monitor (Ctrl+Shift+M) at 115200 baud for detailed diagnosis:

```
Expected output on startup:
Hydraulic Crane Control - Rueckewagenjoystick
Initializing...
USB Host Shield initialized
Waiting for Xbox Controller...
```

With controller connected, you should see real-time values.

#### LED Diagnostics

The SimpleTest example uses built-in LED (pin 13):
- **Fast blinking (5Hz)**: USB Host Shield error
- **Slow blinking (1Hz)**: Controller connected, all OK
- **Off**: Waiting for controller

#### Multimeter Tests

1. **Test Arduino voltage:**
   - Between 5V and GND: should be ~5V
   - Between VIN and GND: should be 7-12V (if externally powered)

2. **Test PWM signal:**
   - Between PWM pin and GND
   - Should show varying voltage 0-5V

3. **Test MOSFET output:**
   - Between Load+ and Load- on MOSFET
   - Should show load voltage when activated

### Getting Help

If problems persist:
1. Check all connections according to wiring diagram
2. Test with SimpleTest example first
3. Check Serial Monitor output for error messages
4. Open an issue on GitHub with:
   - Hardware used
   - Error messages
   - Serial Monitor output
   - Photos of wiring (if relevant)
