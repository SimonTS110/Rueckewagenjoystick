## Digitale Ausgänge (4 Kanäle)
| Kanal | Arduino Pin | Funktion |
|-------|-------------|----------|
| 0 | D2 | Stütze Links Einfahren |
| 1 | D4 | Stütze Links Ausfahren |
| 2 | D7 | Stütze Rechts Einfahren |
| 3 | D8 | Stütze Rechts Ausfahren |

## Digitale Eingänge
| Xbox Taste | Digital Kanal | Funktion |
|------------|---------------|----------|
| A Taste | Digital 0 | Stütze Links Einfahren |
| B Taste | Digital 1 | Stütze Links Ausfahren |
| X Taste | Digital 2 | Stütze Rechts Einfahren |
| Y Taste | Digital 3 | Stütze Rechts Ausfahren |
| START Taste | - | Not-Aus (alle Ausgänge aus) |
| BACK Taste | - | Reset |

## Digital Outputs (4 channels)
| Channel | Arduino Pin | Function |
|---------|-------------|----------|
| 0 | D2 | Support Left Retract |
| 1 | D4 | Support Left Extend |
| 2 | D7 | Support Right Retract |
| 3 | D8 | Support Right Extend |

## Digital Inputs
| Xbox Button | Digital Channel | Function |
|-------------|-----------------|----------|
| A Button | Digital 0 | Support Left Retract |
| B Button | Digital 1 | Support Left Extend |
| X Button | Digital 2 | Support Right Retract |
| Y Button | Digital 3 | Support Right Extend |
| START Button | - | Emergency Stop (all outputs off) |
| BACK Button | - | Reset |

## Wiring Diagram
├── Digitale Ausgänge → MOSFET Module → Stützen
│   ├── D2 → Digital MOSFET 0 → Stütze Links Einfahren
│   ├── D4 → Digital MOSFET 1 → Stütze Links Ausfahren
│   ├── D7 → Digital MOSFET 2 → Stütze Rechts Einfahren
│   └── D8 → Digital MOSFET 3 → Stütze Rechts Ausfahren

├── Digital Outputs → MOSFET Modules → Support Legs
│   ├── D2 → Digital MOSFET 0 → Support Left Retract
│   ├── D4 → Digital MOSFET 1 → Support Left Extend
│   ├── D7 → Digital MOSFET 2 → Support Right Retract
│   └── D8 → Digital MOSFET 3 → Support Right Extend

## Mega2560 Hinweis
Auf dem Arduino Mega2560 stehen mehr Pins zur Verfügung. Wichtige Hinweise:

- Die Bezeichnungen `A0`..`A5` funktionieren in Sketches plattformübergreifend.
	Auf dem Mega entsprechen diese jedoch den digitalen Pin-Nummern `54`..`59`.
- SPI für das USB Host Shield läuft auf dem Mega über den ICSP-Header
	(MOSI/MISO/SCK). Viele Shields verwenden weiterhin D10 als `SS` und D9 als `INT`.
- Digitale Ausgänge (D2, D4, D7, D8) bleiben gleich und benötigen keine Anpassung.

Empfehlung: Verwende in Code die Symbole `A0`..`A5` und `D2`..`D8`,
damit der Sketch auf Uno und Mega ohne weitere Änderungen läuft.

## Nutzung der unteren Pinleiste (22–53)
Der Sketch unterstützt jetzt eine alternative Belegung für den Mega2560,
bei der die Ausgänge auf der unteren Pinleiste (D22..D53) liegen. Standardvorschlag:

- PWM-Kanäle 0–11: D22..D33
- Digitale Ausgänge 0–3: D34..D37

Hinweis: Die meisten dieser Pins sind keine hardware-gesteuerten PWM-Pins.
Der Sketch nutzt daher Software-PWM mit 200Hz für alle 12 Kanäle. Wenn du
eine andere Pinbelegung bevorzugst, sag mir welche Kanalnummer auf welchen
physikalischen Pin gelegt werden soll.