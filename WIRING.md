# Wiring / Verkabelung

Kurze Hinweise zur Verkabelung (Arduino Mega 2560):
- Verwenden Sie für MOSFET-Module eine getrennte Versorgung (z.B. 12V/24V) und verbinden Sie immer die Massen (GND) mit dem Arduino-GND.
- Signalleitungen vom Arduino zu MOSFETs sind 5V-Steuersignale. Verwenden Sie logic-level MOSFETs.
- Dieses Projekt unterstützt nur den Arduino Mega 2560; alle Pin-Empfehlungen beziehen sich auf den Mega.

## Digitale Ausgänge (4 Kanäle)
| Kanal | Arduino Pin (Mega) | Funktion |
|-------|---------------------|----------|
| 0 | D34 | Stütze Links Einfahren |
| 1 | D35 | Stütze Links Ausfahren |
| 2 | D36 | Stütze Rechts Einfahren |
| 3 | D37 | Stütze Rechts Ausfahren |

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
| Channel | Arduino Pin (Mega) | Function |
|---------|---------------------|----------|
| 0 | D34 | Support Left Retract |
| 1 | D35 | Support Left Extend |
| 2 | D36 | Support Right Retract |
| 3 | D37 | Support Right Extend |

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
- Digitale Ausgänge → Digital MOSFET Module → Stützen
	- D34 → Digital MOSFET 0 → Stütze Links Einfahren
	- D35 → Digital MOSFET 1 → Stütze Links Ausfahren
	- D36 → Digital MOSFET 2 → Stütze Rechts Einfahren
	- D37 → Digital MOSFET 3 → Stütze Rechts Ausfahren

- PWM-Ausgänge → PWM MOSFET Module → Proportionalventile
	- Verwenden Sie für PWM-Kanäle die im Sketch definierten `PWM_PINS[]` (siehe `config.h`).
	- Empfohlene Standardbelegung für Mega (PWM-Kanäle 0–11): Pins `2,3,4,5,6,7,8,9,10,11,12,13`.

## Mega2560 Hinweis
Dieses Projekt ist für den `Arduino Mega 2560` ausgelegt. Wichtige Hinweise:

- Hardware-PWM auf Mega: Pins `2..13` und `44..46` sind hardware-gesteuerte PWM-Pins. Für 12 Kanäle eignen sich `2..13` sehr gut.
- SPI für das USB Host Shield läuft auf dem Mega über den ICSP-Header (MOSI/MISO/SCK). Viele Shields verwenden weiterhin D10 als `SS` und D9 als `INT`.
- Analoge Pins `A0..A15` sind als `A0..A15` nutzbar; bei Bedarf entsprechen sie auch digitalen Pin-Nummern (z.B. `A0` = `54`).

Empfehlung: Verwenden Sie in Code die symbolischen Bezeichner (`2`, `A0`, `D34` etc.) wie in `config.h` definiert; `PWM_PINS[]` und `DIGITAL_PINS[]` sollten an Ihre physikalische Verkabelung angepasst werden.

## Nutzung der unteren Pinleiste (22–53)
Der Sketch unterstützt jetzt eine alternative Belegung für den Mega2560,
bei der die Ausgänge auf der unteren Pinleiste (D22..D53) liegen. Standardvorschlag:

Hinweis: Wenn Sie andere Pins verwenden möchten, passen Sie bitte `PWM_PINS[]` und `DIGITAL_PINS[]` in `config.h` an. Der Sketch verwendet auf dem Mega vorzugsweise Hardware-PWM-Pins; Software-PWM ist nur für alternative Belegungen vorgesehen.