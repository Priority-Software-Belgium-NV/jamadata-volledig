# Kassa – Klantendisplay en kassahardware (Glaive, Rich-Pos, Aerpos, PanelPC)

Gebruik dit document voor: het aansluiten en instellen van een klantendisplay op de kassa (losse display op een COM-poort per type kassa, grote klantendisplay/tweede scherm met reclamebeeld), de instelling "soort kassa" in `kassys.dat` (positie 4036), COM-poorten per type kassa, BIOS-/boot-toetsen, het herkalibreren van het touchscreen en een overzicht van de hardware die bij een Key-Conen Win Touch kassa hoort.

## 1. Types kassahardware

| Type | Windows | Opmerkingen |
|---|---|---|
| Epson IR / "keytouch" (oud) | DOS / Win95 | `kassa32n.exe`; computernaam `keytouch-01`. Wordt niet meer vernieuwd. |
| Firich Glaive RT-560 | XP embedded / POSReady 2009 | "XP-kassa": krijgt geen nieuwe kassaversies meer (XP-suffix in de runonce). |
| Rich-Pos | POSReady 2009 | Idem XP-kassa. Restore via USB-stick/SATA-DOM. |
| Aerpos | Windows 7-generatie | .NET 4 nodig voor Ingenico. |
| PanelPC / PanelPos | Windows 10 IoT | Huidige kassa: SSD 128 GB + USB-stick 64 GB (backup/restore). |

Computernaam van de (hoofd)kassa is standaard `wintouch-01` (verdere kassa's -02, -03 …).

## 2. Instelling "soort kassa" – kassys.dat positie 4036

Bepaalt via welke COM-poort de gegevens naar het klantendisplay gestuurd worden:

| Waarde 4036 | Kassa / display |
|---|---|
| 1 | Glaive |
| 2 | Rich-Pos (klantendisplay op COM4) |
| 3 | Aerpos (klantendisplay op COM6) |
| 4 | PanelPC (klantendisplay op COM6, tekst afgekapt op 20 karakters) |
| 5 | PanelPC (klantendisplay op losse voet, COM1) |
| 6 | PanelPC (klantendisplay op losse voet, COM3) |

Instellen: `upsys32 kassys.dat` → positie 4036 (unsigned integer), of met de kant-en-klare batchbestanden op de kassa: **`setpp`**, **`setpp2`** (PanelPC), **`setrp`** (Rich-Pos), **`setap`** (Aerpos). Staat de parameter in zo'n batchbestand fout (te zien aan het type kassa), zet hem dan juist en hernoem het batchbestand.

Typisch probleem: na het overnemen van een `kassys.dat` van een oude kassa op nieuwe hardware **werkt het klantendisplay niet** of toont het rommel → positie 4036 staat nog op het oude type. Voer `setpp2` (of de juiste variant) uit.

## 3. Losse klantendisplay aansluiten

### 3.1 PanelPos / PanelPC

De display heeft **5 volt** nodig, te leveren via de COM-poort waarop hij aangesloten is. Dit stel je in de BIOS in:

1. Druk bij het opstarten op **DEL** om in de BIOS te gaan.
2. Kies "Advanced" → "Product settings" → **"COM1 Power Control"**.
3. Wijzig `[RI]` naar **`[5v]`**. **Zeker geen 12 V, want dan is de display defect!**
4. "Save & Exit".
5. Vanaf nu brandt er een groen lampje bij COM1 (5 V).
6. Sluit op deze poort **enkel de klantendisplay** aan, zeker niet de printer of een betaalterminal. Zet de printer eventueel op een andere poort, of sluit hem aan via USB of netwerk.
7. Software: zet `kassys.dat` positie 4036 op de juiste waarde (display op losse voet op COM1 = **5**; op COM3 = 6).

### 3.2 Aerpos

De display heeft stroom nodig. Voed je hem met een externe voeding, dan **blijft de kassa herstarten**. De stroom moet daarom via de COM-poort komen waarop de display hangt; dat kan enkel door een **jumper te verzetten op het moederbord** (foto's in het brondocument). Software: `kassys.dat` positie 4036 (Aerpos = 3, display op COM6; hangt de display op COM4, dan waarde 2).

### 3.3 Teksten op de klantendisplay

De boodschappen die op de klantendisplay verschijnen wanneer er geen ticket bezig is (reclameteksten), stel je in via het kassamenu punt 3 "Aanpassen parameters".

## 4. Grote klantendisplay (tweede scherm met ticket + reclame)

### 4.1 Huidige kassa's

1. Sluit een HD-scherm aan via de VGA-aansluiting van de kassa en **breid het bureaublad uit** naar dit scherm.
2. Zet de laatste versie van **`largdisp.dll`** in `c:\kassa`.
3. Maak een **`affiche.jpg`** aan (in `c:\kassa`) die als reclamescherm dient. Aanbevolen grootte 1206 × 828 (of 1984 × 1240); verhouding ongeveer 4:3.

Problemen:

- **Het kassascherm valt onderaan en rechts weg** na het aansluiten van het tweede scherm: dit komt door de grafische instellingen. Zet bij Systeemeigenschappen → Geavanceerd → Prestaties de instelling op **"Laat Windows kiezen wat het beste is voor deze computer"** in plaats van "Beste prestaties".
- **Windows 10**: de taakbalk blijft zichtbaar op het tweede scherm. Je kan wel de open programma's verbergen via de instellingen van de taakbalk.

### 4.2 Oudere kassa's (kassa.exe van minstens november 2009)

- **Glaive**: via een USB2VGA-adapter vooraan op een USB-poort; het scherm op de adapter (enkel VGA). Activeer de USB2VGA-adapter in Apparaatbeheer (2×). Staat hij er niet tussen, dan is een nieuwe load op het CF-kaartje nodig. Zet de nieuwe `kassa.exe` en `largedisp.dll` in de map kassa. Stel het 2e scherm in op een 4:3-resolutie (bv. 800 × 600) of bij breedbeeld exact 1920 × 1080.
- **Rich-Pos**: scherm rechtstreeks met een VGA-kabel; nieuwe `kassa.exe` en `largedisp.dll` in de map kassa; 2e scherm exact 1920 × 1080 (breedbeeld).

## 5. COM-poorten per type kassa (overzicht uit de bronnen)

| Toestel | Glaive | Rich-Pos | Aerpos | PanelPC / PanelPos |
|---|---|---|---|---|
| Klantendisplay | – | COM4 | COM6 | COM6 (ingebouwd), COM1 of COM3 (losse voet) |
| Betaalterminal Banksys/Worldline (serieel) | COM2 | COM5 (COM2 werkt niet) | – | COM4 |
| Betaalterminal Ingenico (historisch serieel/USB) | – | – | COM5 | COM4 serieel, meestal COM7 via USB |
| CCV via USB-driver | COM9 (alle types) | | | |

Ingenico werkt sinds 1/7/2022 enkel nog via TCP/IP. Details: `kassa-betaalterminals.md`.

Ticketprinter: de poort staat in `kassys.dat` positie 3712 en is te controleren via kassamenu punt 3 → F8 → F8. De geldlade hangt aan de ticketprinter of een eigen poort (3072/3260); werkt ze niet, controleer dan de ladecode via punt 3.

## 6. BIOS, boot en USB-stick (PanelPC)

- **DEL / F2** = BIOS; **F11 / F12** = boot override (kiezen van welk medium opgestart wordt).
- De USB-stick (64 GB) in de kassa dient voor de backup (Veeam Agent) en de restore.
- Start de kassa ongewild op vanaf de USB-stick: stick uittrekken, 2 keer zo opstarten, stick terug insteken.
- Restore-procedures per type: `kassa-image-restore.md`.

## 7. Touchscreen reageert verkeerd / niet goed gekalibreerd (nieuwe Wintouch-kassa)

Mogelijke oplossingen, in deze volgorde:

1. Haal de beschermfolie (plastiek) van het scherm.
2. Voer in een opdrachtprompt `msdt.exe -id DeviceDiagnostic` uit → Advanced → "Auto apply" (automatisch herstellen).
3. Apparaatbeheer → Human Interface Devices (HID) → het touchscreen **uitschakelen en weer inschakelen**.
4. Kassa uitschakelen, stekker uittrekken, scherm proper maken en zo nodig afdrogen, stekker terug insteken en de kassa opstarten.

**Let op: raak het scherm NIET aan tijdens het opstarten** (het touchscreen kalibreert zich dan).

Bij installatie van een nieuwe kassa wordt de "Touch utility" ingesteld om mee op te starten.

## 8. Wat hoort bij een Key-Conen Win Touch kassa (hardwarefiche)

Kassa (PanelPos), thermische seriële ticketprinter, klantendisplay, scanner (MT2090 met toetsenbord, DS9208 USB, LS2208 USB of LI4278 USB draadloos), eID-reader, toetsenbord, geldlade (klap- of schuiflade), stroom- en printerkabel, COM-adapterkabel, 2 stiftjes voor het touchscreen, scannerblad (programmeerblad), blokjes- en kassadocumentatie, SSD 128 GB, USB-stick 64 GB, licentie Windows 10 IoT, support-sticker. Optioneel: 2e ticketprinter, 2e geldlade. Van elk toestel wordt het serienummer genoteerd bij levering.

## Bronnen

- `kassa/Installatie_losse klantendisplay Panelpos.docx`
- `kassa/Installatie_losse klantendisplay aerpos.docx`
- `kassa/Installatie grote klantendisplay.docx`
- `kassa/gdisplay.docx`
- `kassa/Kassa installeren.docx`
- `kassa/KASSYS.docx` (positie 4036, 3712)
- `kassa/Hadware touchkassa.docx`, `kassa/Hardware touchkassa.pdf`
- `kassa/HOWTO-Instellen BANKSYS.docx`, `kassa/HOWTO-Instellen INGENICO.docx`, `kassa/HOWTO-Instellen CARDFON.docx` (COM-poorten)
- `kassa/FAQ PanelPC kassa.docx`
- `Onenote/KASSA.pdf` (06 Nieuwe wintouch-kassa touch screen kalibreren; 08 BIOS en BOOT; Stappenplan kassa installeren)
