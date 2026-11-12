# Barcodescanners: programmeren, herstarten en storingen

Gebruik dit document voor: vragen over de handscanners aan de kassa (Zebra/Symbol/Motorola LI4278, DS2278, MT2090, Datalogic PowerScan PM9100): welk programmeerblad bij welk toestel hoort, in welke volgorde je programmeert, wat de bladen instellen, hoe je een scanner herstart of opnieuw koppelt, en hoe de functietoetsen van de PowerScan PM9100 werken. De programmeerbladen bestaan uit barcodes die je met de scanner zelf moet scannen; die barcodes staan enkel in de originele bestanden (map `kassa/scanners`).

## 1. Principe

- De scanners werken als **USB-toetsenbord** (HID Keyboard Emulation) met Belgisch/Frans (AZERTY) toetsenbordland en Caps Lock Override.
- Elke scan wordt naar de kassa gestuurd als `<prefix><data><suffix>`, met prefix **STX (Ctrl+B, ASCII 02)** en suffix **ETX (Ctrl+C, ASCII 03)**. Zo herkent de kassa scannerinvoer.
- Een scanner die "niets doet" of verkeerde tekens geeft in de kassa is dus meestal niet (meer) correct geprogrammeerd: scan het juiste programmeerblad opnieuw.

Algemene regels bij elk blad:
1. Scan de barcodes **in volgorde**, van de eerste tot de laatste, elk **één keer**.
2. **Wacht na elke barcode enkele seconden** tot de scanner klaar is met verwerken.
3. Krijg je een barcode niet gescand: houd de scanner iets verder van het blad.
4. Het blad begint steeds met **Set Defaults** (fabrieksinstellingen); daarna wordt alles opnieuw opgebouwd.

## 2. Overzicht bladen en bestanden (map `kassa/scanners`)

| Bestand | Toestel | Inhoud |
|---|---|---|
| `programmeerblad ZEBRA DS2278.docx/.pdf` | Zebra DS2278 | Programmeerblad 8 stappen, versie 1.0 (16/07/2026) |
| `Config File_DS2278_Test_2026.07.15.scncfg` | Zebra DS2278 | Configuratiebestand voor de Zebra-scannerutility (bron van het DS2278-blad); geen leesbare tekst |
| `programmeerblad TOMRA LI4278.docx/.pdf` | Zebra/Symbol LI4278 | Programmeerblad 8 stappen, inclusief TOMRA-barcodes |
| `Programming Barcode_LI4278_TOMRA barcode.pdf` | LI4278 (plug-in "LI4278-STANDARD SR MODELS-018") | Zelfde configuratie als hierboven, rechtstreekse export uit de utility ("TOMRA barcode", configuratiebestand `Config File_LI4278_TOMRA barcode_2020.12.23.scncfg`), "incl. TOMRA zonder beveiliging" |
| `Scanblad LI4278 Multiple standaard.pdf` | Motorola LI4278 | Ouder standaardblad 9 stappen (versie 22/03/2017), zonder TOMRA |
| `Scanblad MT2090 met EID Multiple.pdf` | Motorola/Symbol MT2090 (scanner met toetsenbord) | Blad 12 stappen met regels (ADF rules), versie 27/12/2012 |
| `Programmatieblad Datalogic Powerscan PM9100.docx/.pdf` | Datalogic PowerScan PM9100 | Programmatieblad versie 3.5 (07/08/2025), gemaakt met Datalogic Aladdin v3.3.0.10 |
| `SCANBLAD 1.0.pdf` | Datalogic PowerScan M9100 | Oudere versie (13/05/2025) van het PM9100-blad |
| `config_POWERSCAN-M9100_610102924.xml` | Datalogic PowerScan M9100 | Configuratie-export voor Datalogic Aladdin; geen procedure |
| `PowerScan PM9100 Handleiding.docx/.pdf` | Datalogic PowerScan PM9100 | Gebruikershandleiding (functietoetsen) |
| `Scanners.pdf` | MT2090, LI4278 | Herstartprocedures (zelfde inhoud als `Onenote/Scanners.pdf`) |

## 3. Zebra DS2278 – programmeerblad

Scan in volgorde (8 barcodes):

| Nr | Wat de barcode instelt |
|---|---|
| 1/8 | **Set Defaults** |
| 2/8 | Kabelverbinding USB: USB Device Type **HID Keyboard Emulation**, **Caps Lock Override Enable** |
| 3/8 | Symbologie: Code 128 Length 1 = 2, Code 128 Length 2 = 20, Interleaved 2 of 5 Length 1 = 0, Length 2 = 0 |
| 4/8 | **UPC-E1** inschakelen |
| 5/8 | Data aanpassen: Prefix **START OF TEXT** (1,0,0,2), Suffix 1 **CTRL C / END OF TEXT** (1,0,0,3) |
| 6/8 | Suffix 2 **Enter** (7,0,1,3), Scan Data Transmission Format **`<Prefix><Data><Suffix 1>`** |
| 7/8 | Keyboard country type **Belgian French** |
| 8/8 | Configuration File "ZEBRA barcode" |

## 4. Zebra/Symbol LI4278 – programmeerblad met TOMRA

Dit is het actuele blad voor de LI4278 wanneer ook TOMRA-bonnen (leeggoedautomaat) gescand moeten worden.

| Nr | Wat de barcode instelt |
|---|---|
| 1/8 | **Set Defaults** |
| 2/8 | USB: USB Device Type **Default (HID Keyboard Emulation)**, USB Country Code **Windows French (International)** |
| 3/8 | **Caps Lock Override Enable** |
| 4/8 | Symbologie: Code 128 Length 1 = 2, Code 128 Length 2 = 20, **Interleaved 2 of 5** inschakelen, **UPC-E1** inschakelen |
| 5/8 | Bluetooth: HID Country Code **Windows French International**, Caps Lock Override Enable |
| 6/8 | Prefix **START OF TEXT** (1,0,0,2), Suffix 1 **CTRL C / END OF TEXT** (1,0,0,3) |
| 7/8 | Suffix 2 **Enter** (7,0,1,3), Scan Data Transmission Format **`<Prefix><Data><Suffix 1>`** |
| 8/8 | Configuration File "TOMRA barcode" |

**Bij problemen: scan barcode 2/8 nogmaals als laatste.**

Verschil met het oude standaardblad: het TOMRA-blad schakelt extra Interleaved 2 of 5 en UPC-E1 in en zet Code 128 lengte 2–20. Kan een LI4278 gewone artikels scannen maar geen TOMRA-bon, dan is hij waarschijnlijk nog met het oude standaardblad geprogrammeerd.

## 5. Motorola LI4278 – oud standaardblad (2017)

Begin bij 1/9 en eindig bij 9/9; wacht na elke barcode.

| Nr | Wat de barcode instelt |
|---|---|
| 1/9 | Set Defaults |
| 2/9 | USB Device Type HID Keyboard Emulation, USB Country Code Windows French International |
| 3/9 | Caps Lock Override Enable |
| 4/9 | Code 128 Length 2 = 20 |
| 5/9 | (tussenstap; geen tekst uitleesbaar op het blad) |
| 6/9 | Bluetooth: HID Country Code Windows French International, Enable Caps Lock Override |
| 7/9 | Prefix **CTRL B** (1,0,0,2), Suffix 1 **CTRL C** (1,0,0,3) |
| 8/9 | Scan Data Transmission Format `<Prefix><Data><Suffix 1>` |
| 9/9 | Caps Lock Override Enable |

Gebruik bij voorkeur het recentere blad uit punt 4.

## 6. Motorola/Symbol MT2090 (scanner met toetsenbord) – blad "met EID (Multiple)"

Begin bij nr. 1 en eindig bij nr. 12; wacht na elke barcode.

| Nr | Wat de barcode instelt |
|---|---|
| 1 | Defaults |
| 2 | **Let op: de tweede te scannen barcode staat op de cradle (houder) van de scanner** (koppelen met de houder) |
| 3 | USB Device Type Default (HID Keyboard Emulation), USB Country Code Windows French International |
| 4 | Caps Lock Override Enable |
| 5 | Erase All Rules |
| 6 | Begin New Rule: Code 39, EAN-13 |
| 7 | EAN-8, UPC-A, UPC-E |
| 8 | UPC-E1; actie 1: Send ASCII Key `<CTRL B>`; actie 2: Send All that remains |
| 9 | Actie 3: Send ASCII Key `<CTRL C>`; Save Rule |
| 10 | Begin New Rule: Code 128, Code Length 20 |
| 11 | Send ASCII Key `<CTRL B>`, Send All that remains, Send ASCII Key `<CTRL C>` |
| 12 | Save Rule |

## 7. Datalogic PowerScan PM9100

### 7.1 Programmatieblad (versie 3.5, 07/08/2025)
- Scan **van boven naar onder elke barcode één keer**; wacht telkens enkele tellen.
- Functioneert de scanner na het scannen niet correct: scan de barcode bovenaan het blad om hem terug op **fabrieksinstellingen** te zetten en scan het blad daarna opnieuw.

| Volgorde | Instelling | Programmeercommando |
|---|---|---|
| 1 | Communication Interface: **USB-KBD** | `$P,HA35,P` |
| 2 | Keyboard Country Mode: **Belgium** | `$P,CKBCO01,P` |
| 3 | Global Suffix (leeg gemaakt) | `$P,CLFSU03…,P` |
| 4 | Action Config F1 = String 2 | `$P,CPWEV0300,P` |
| 5 | Action Config F2 = String 1 | `$P,CPWET0200,P` |
| 6 | Action Config F3 = String 3 | `$P,CPWEU0400,P` |
| 7 | Action Config F4 = String 4 | `$P,CPWES0500,P` |
| 8 | Set String 1 | `$P,CPWEP0224302430030…,P` |
| 9 | Set String 2 | `$P,CPWEO0224312431030…,P` |
| 10 | Set String 3 | `$P,CPWEA02383032313030303030303030370300,P` |
| 11 | Set String 4 | `$P,CPWEM0225304403…,P` |
| 12 | Keypad Data Format: Enable | `$P,CPWDF01,P` |
| 13 | Set Barcode Header: 02 (STX) | `$P,CPWBH02…,P` |
| 14 | Set Barcode Terminator: 03 (ETX) | `$P,CPWBT03…,P` |

Betekenis van de strings (hexadecimaal gedecodeerd; afleiding uit het blad, niet letterlijk zo in de bron beschreven):
- String 1 = STX `$0$0` ETX → gekoppeld aan **F2 (Bak)**
- String 2 = STX `$1$1` ETX → gekoppeld aan **F1 (Fles)**
- String 3 = STX `8021000000007` ETX → gekoppeld aan **F3 (Leeggoed lege bak)**
- String 4 = STX `%0D` ETX → gekoppeld aan **F4 (Clear)**

De oudere versie `SCANBLAD 1.0.pdf` (13/05/2025) stelt een globale prefix 02 en suffix 03 in en bevat de strings zonder STX/ETX; versie 3.5 vervangt dit door barcode header/terminator en strings mét STX/ETX. Gebruik versie 3.5.

### 7.2 Gebruik van de scanner (gebruikershandleiding)
- **Scanner kwijt**: druk op de **zwarte knop op het laadstation** (scanner-zoekknop); de scanner geeft pieptonen.
- Onderdelen: functietoetsen, numeriek klavier, Enter-toets (groen, linksonder); op het station: stroomindicatie, zoekknop, batterij-oplaadstatus, signaalindicatie.

Functietoetsen (ingesteld voor de Jamadata-kassa):

| Toets | Functie | Uitleg |
|---|---|---|
| **F1 – Fles** | Scant de volgende barcode als fles/stuk | Voor als de barcode in het systeem aan een **bak** gekoppeld is maar de klant losse flessen neemt; de stuk-/flesprijs wordt toegepast. Op het scherm verschijnt "ST" |
| **F2 – Bak** | Scant de volgende barcode als bak | Voor als de barcode als **flesbarcode** is ingesteld: eerst F2, dan de flesbarcode scannen → volledige bak op het ticket |
| **F3 – Leeggoed € 2,10** | Voegt 1 lege bak leeggoed toe à € 2,10 | Handig bij een bak gevuld met losse flessen van verschillende soorten: leeggoed van de flessen apart, de lege bak via F3 |
| **F4 – Clear** | Wist het laatst ingegeven aantal | Bv. 55 getikt i.p.v. 5: F4 en opnieuw ingeven |

Werkvolgorde met aantallen:
1. Tik het aantal op het klavier van de scanner (bv. 5).
2. Druk op de **groene Enter-toets**.
3. Controleer dat het aantal op het kassascherm verschijnt.
4. Druk **F2** (bak) of **F1** (fles).
5. Scan de barcode.
6. Voorbeeld: flesbarcode + 5 + Enter + F2 → 5 bakken op het ticket. Bakbarcode + 3 + Enter + F1 → 3 losse flessen.

Aandachtspunt support: F3 stuurt een vaste code voor leeggoed à € 2,10. Wijzigt het leeggoedbedrag of de code van de lege bak bij een klant, dan moet String 3 in het programmatieblad aangepast worden (onzeker / te verifiëren hoe de code in de kassa gekoppeld is).

## 8. Herstarten en koppelen

### 8.1 Scanner met toetsenbord (MT2090)
- **Herstarten**: houd cijfer **2** ingedrukt en houd tegelijk de **scantoets (onderaan)** ingedrukt.
- Druk daarna één keer op de scantoets om opnieuw beeld te krijgen.
- Kies in het menu optie **1 – SCAN ITEM** met **ENT**.
- **Bluetooth-verbinding**: scan de **PAIR**-barcode op de scannerhouder (werkt enkel als de houder aangesloten is).

### 8.2 Scanner zonder toetsenbord (LI4278)
- **Herstarten**: leg de scanner op de houder en houd de scantoets **± 20 seconden** ingedrukt; de scanner geeft dan een signaal dat hij herstart is.

## 9. Veelvoorkomende problemen

| Probleem | Aanpak |
|---|---|
| Scanner reageert niet / geen verbinding met houder | Herstarten (punt 8); bij MT2090 opnieuw de PAIR-barcode op de houder scannen; controleer of de houder aangesloten is |
| Scans komen niet of met vreemde tekens in de kassa | Juiste programmeerblad opnieuw scannen, in volgorde, met wachttijd tussen de barcodes |
| LI4278 werkt niet goed na programmeren | Barcode **2/8** nogmaals als laatste scannen |
| Programmeerbarcode wil niet scannen | Scanner iets verder van het blad houden |
| PM9100 werkt niet correct na programmeren | Fabrieksinstellingen-barcode bovenaan het blad scannen en het blad opnieuw scannen |
| TOMRA-bon scant niet met LI4278 | Programmeren met het blad "TOMRA LI4278" (punt 4) |
| PM9100 kwijt | Zwarte zoekknop op het laadstation |
| Verkeerd aantal getikt op PM9100 | F4 (Clear) |

## Bronnen
- `kassa/scanners/programmeerblad ZEBRA DS2278.docx` (+ pdf, + `Config File_DS2278_Test_2026.07.15.scncfg`)
- `kassa/scanners/programmeerblad TOMRA LI4278.docx` (+ pdf)
- `kassa/scanners/Programming Barcode_LI4278_TOMRA barcode.pdf`
- `kassa/scanners/Scanblad LI4278 Multiple standaard.pdf`
- `kassa/scanners/Scanblad MT2090 met EID Multiple.pdf`
- `kassa/scanners/Programmatieblad Datalogic Powerscan PM9100.docx` (+ pdf)
- `kassa/scanners/SCANBLAD 1.0.pdf`
- `kassa/scanners/config_POWERSCAN-M9100_610102924.xml` (enkel vermeld)
- `kassa/scanners/PowerScan PM9100 Handleiding.docx` (+ pdf)
- `kassa/scanners/Scanners.pdf` en `Onenote/Scanners.pdf`
