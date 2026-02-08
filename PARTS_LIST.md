# Parts List / Teileliste

## Deutsch

### Benötigte Komponenten

#### Elektronik Hauptkomponenten

| Anzahl | Komponente | Beschreibung | Beispiel |
|--------|------------|--------------|----------|
| 1 | Arduino Mega 2560 | Mikrocontroller-Board (empfohlen) | Arduino Mega 2560 |
| 1 | USB Host Shield | Für Xbox Controller | USB Host Shield 2.0 für Arduino |
| 1 | Xbox Controller | USB oder Xbox 360 Controller | Xbox 360 Wired Controller |
| 12 | PWM MOSFET Module | Logic-level MOSFET (für 5V Gate-Ansteuerung) | z.B. IRLZ44N, IRF3205 (vermeiden Sie ältere Nicht-Logic-Level-Teile wie IRF520) |
| 4 | Digital MOSFET Module | Logic-level MOSFET (für 5V Gate-Ansteuerung) | z.B. IRLZ44N, IRF3205 |

#### Stromversorgung

| Anzahl | Komponente | Beschreibung | Spezifikation |
|--------|------------|--------------|---------------|
| 1 | Netzteil für Arduino | 7-12V DC | min. 500mA |
| 1 | Externe Stromversorgung | Für Hydraulikventile | Abhängig von Ventilen (12V/24V) |
| 1 | DC-DC Wandler (optional) | Wenn verschiedene Spannungen benötigt | Buck/Boost Converter |

#### Verkabelung

| Anzahl | Komponente | Beschreibung |
|--------|------------|--------------|
| 1 | USB A auf B Kabel | Für Arduino Programmierung | Standard USB Kabel |
| 1 | USB Verlängerung (optional) | Für Xbox Controller | USB A auf A |
| - | Schaltlitze | Verschiedene Farben | 0,5-1,0 mm² |
| - | Aderendhülsen | Für professionelle Verkabelung | Passend zur Litze |
| 1 | Kabelkanal / Gehäuse | Schutz und Organisation | IP54 oder höher empfohlen |

#### Sicherheit & Montage

| Anzahl | Komponente | Beschreibung |
|--------|------------|--------------|
| 1 | Not-Aus Schalter | Hardware Emergency Stop | 22mm Pilzdrucktaster |
| 1 | Sicherungen-Set | Für jeden Ausgangskanal | Abhängig von Laststrom |
| 1 | Relais (optional) | Master-Abschaltung | 12V/24V Relais mit Öffner |
| - | Schrauben / Distanzbolzen | Montage Arduino & Shield | M3 Schrauben-Set |
| 1 | Kühlkörper-Set | Für MOSFETs bei hoher Last | Abhängig von MOSFET-Typ |

### Optionale Komponenten

| Anzahl | Komponente | Zweck |
|--------|------------|-------|
| 1 | LCD Display | Status-Anzeige | 16x2 oder 20x4 LCD mit I2C |
| 1 | SD Card Shield | Datenaufzeichnung | SD Card Logger Shield |
| 1 | LED Status Anzeige | Visuelle Rückmeldung | RGB LED mit Vorwiderständen |
| 1 | Summer/Buzzer | Akustische Warnung | Aktiver Buzzer 5V |

### Hydraulik Komponenten (nicht enthalten)

Diese müssen entsprechend Ihrem Kran spezifiziert werden:

| Komponente | Beschreibung |
|------------|--------------|
| Proportionalventile | 12 Stück, PWM-gesteuert (200Hz) |
| Schaltventile | 4 Stück, Ein/Aus |
| Hydraulikpumpe | Ausreichend Leistung für alle Verbraucher |
| Hydraulikflüssigkeit | Nach Herstellervorgabe |
| Schläuche und Fittings | Druckfest, passende Größen |

### Werkzeug

- Lötkolben und Lötzinn
- Abisolierzange
- Crimpzange (für Aderendhülsen)
- Multimeter
- Seitenschneider
- Schraubendreher-Set

### Geschätzte Gesamtkosten

| Kategorie | Kosten (circa) |
|-----------|----------------|
| Elektronik Hauptkomponenten | 80-120 EUR |
| Stromversorgung | 30-50 EUR |
| Verkabelung und Montage | 40-60 EUR |
| Sicherheitskomponenten | 20-40 EUR |
| **Gesamt (ohne Hydraulik)** | **170-270 EUR** |

*Hinweis: Preise sind Schätzungen und können variieren*

---

## English

### Required Components

#### Main Electronic Components

| Quantity | Component | Description | Example |
|----------|-----------|-------------|---------|
| 1 | Arduino Uno | Microcontroller Board | Arduino Uno R3 |
| 1 | USB Host Shield | For Xbox Controller | USB Host Shield 2.0 for Arduino |
| 1 | Xbox Controller | USB or Xbox 360 Controller | Xbox 360 Wired Controller |
| 12 | PWM MOSFET Modules | Logic Level MOSFET | IRF520 or IRLZ44N Modules |
| 4 | Digital MOSFET Modules | Logic Level MOSFET | IRF520 or IRLZ44N Modules |

#### Power Supply

| Quantity | Component | Description | Specification |
|----------|-----------|-------------|---------------|
| 1 | Arduino Power Supply | 7-12V DC | min. 500mA |
| 1 | External Power Supply | For hydraulic valves | Depending on valves (12V/24V) |
| 1 | DC-DC Converter (optional) | If different voltages needed | Buck/Boost Converter |

#### Wiring

| Quantity | Component | Description |
|----------|-----------|-------------|
| 1 | USB A to B Cable | For Arduino programming | Standard USB Cable |
| 1 | USB Extension (optional) | For Xbox Controller | USB A to A |
| - | Wire | Various colors | 18-22 AWG |
| - | Wire Ferrules | For professional wiring | Matching wire gauge |
| 1 | Cable Management / Enclosure | Protection and organization | IP54 or higher recommended |

#### Safety & Mounting

| Quantity | Component | Description |
|----------|-----------|-------------|
| 1 | Emergency Stop Switch | Hardware Emergency Stop | 22mm Mushroom Push Button |
| 1 | Fuse Set | For each output channel | Based on load current |
| 1 | Relay (optional) | Master shutdown | 12V/24V Relay with NC contact |
| - | Screws / Standoffs | Mount Arduino & Shield | M3 Screw Set |
| 1 | Heat Sink Set | For MOSFETs under high load | Based on MOSFET type |

### Optional Components

| Quantity | Component | Purpose |
|----------|-----------|---------|
| 1 | LCD Display | Status display | 16x2 or 20x4 LCD with I2C |
| 1 | SD Card Shield | Data logging | SD Card Logger Shield |
| 1 | LED Status Indicator | Visual feedback | RGB LED with resistors |
| 1 | Buzzer | Acoustic warning | Active Buzzer 5V |

### Hydraulic Components (not included)

These must be specified according to your crane:

| Component | Description |
|-----------|-------------|
| Proportional Valves | 12 pieces, PWM-controlled (200Hz) |
| Switching Valves | 4 pieces, On/Off |
| Hydraulic Pump | Sufficient power for all consumers |
| Hydraulic Fluid | According to manufacturer specifications |
| Hoses and Fittings | Pressure-rated, appropriate sizes |

### Tools

- Soldering iron and solder
- Wire stripper
- Crimping tool (for ferrules)
- Multimeter
- Side cutters
- Screwdriver set

### Estimated Total Cost

| Category | Cost (approx.) |
|----------|----------------|
| Main Electronic Components | $90-130 |
| Power Supply | $35-55 |
| Wiring and Mounting | $45-65 |
| Safety Components | $25-45 |
| **Total (without hydraulics)** | **$195-295** |

*Note: Prices are estimates and may vary*

### Where to Buy

- **Arduino and Shields**: Arduino.cc, SparkFun, Adafruit, Amazon
- **MOSFET Modules**: eBay, AliExpress, Amazon, local electronics suppliers
- **Cables and Connectors**: Mouser, DigiKey, local electronics stores
- **Hydraulic Components**: Specialized hydraulic suppliers

### Compatibility Notes

**Supported board:**
- Arduino Mega 2560 (Projekt ist für Mega 2560 ausgelegt)

**USB Host Shield Alternatives:**
- Any Arduino-compatible USB Host Shield 2.0

**Xbox Controller Alternatives:**
- Xbox One Controller (wired)
- Xbox 360 Wireless Controller (requires wireless receiver)
- Generic USB game controllers (may require code modifications)

**MOSFET Module Requirements:**
- Logic level (triggered by 5V)
- Appropriate current rating for your load
- Consider continuous vs. peak current ratings
- Add heat sinks if continuous high current operation

### Safety Certifications

When building for commercial or professional use, consider:
- CE marking compliance
- Electrical safety standards (IEC, UL)
- Machinery directive compliance
- Risk assessment and documentation
