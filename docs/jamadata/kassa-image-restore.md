# Kassa – Image restore van kassahardware (Glaive, Rich-Pos, PanelPC)

Gebruik dit document voor: het terugzetten van een Windows-image (backup) op een Jamadata-kassa wanneer Windows zelf niet meer werkt (blue screen, LSASS/ISASS.exe-fout, virus, kassa start niet meer op), per type kassahardware (Firich Glaive RT-560, Rich-Pos, PanelPC), en voor het veiligstellen en terugzetten van de kassagegevens (map `C:\KASSA`) voor en na de restore.

> Belangrijk: een image restore wist **alle** huidige gegevens op de kassa. Nieuwe prijzen kunnen achteraf opnieuw doorgestuurd worden vanaf de hoofdcomputer, **kassaverkopen niet**. Stel daarom altijd eerst de map `C:\KASSA` veilig als dat nog kan.

## 1. Welke procedure voor welke kassa?

| Type kassa | Windows | Backup staat op | Procedure |
|---|---|---|---|
| Firich Glaive RT-560 **met** Freedelity-koppeling | POSReady 2009 | 2e partitie (D:) | §3 |
| Glaive **zonder** Freedelity | XP embedded | USB-stick achteraan in de voet | §4 |
| Rich-Pos | POSReady 2009 | USB-stick / SATA-DOM in de voet | §5 |
| PanelPC (Panelpos) | Windows 10 IoT | USB-stick (opstartbaar), image in `c:\data\backup\images` | §6 |

## 2. Altijd eerst: kassagegevens veiligstellen

Doe, zolang de kassa nog opstart, zoveel mogelijk van het volgende:

1. Sluit een toetsenbord aan op de kassa (bij de Glaive met Freedelity moet dit een **PS/2-toetsenbord** zijn, geen USB).
2. Maak een backup via het kassamenu "Menu Beheer Key-conen Kassa", **punt 4** "Kopie maken van de kassagegevens".
3. Doe indien mogelijk ook een **N – Dagelijkse TRANSFER met de HOOFDCOMPUTER**, zodat de verkopen op de hoofdcomputer staan.
4. Lukt punt 2 niet: kopieer met Windows Verkenner de map `C:\KASSA` naar `D:` (2e partitie of USB-stick, afhankelijk van het type).

### Kassagegevens terugzetten na de restore (alle types)

- Via Verkenner: kopieer de map `D:\KASSA` (of de map KASSA op de USB-stick) terug naar `C:`; of
- via het kassamenu "Menu Beheer Key-conen Kassa":
  1. Kies **punt 5** "Terug opladen van oude kopie van kassagegevens" en druk [Enter].
  2. Druk [F4] – ja – [Enter].
  3. Druk [F5] – nee – [Enter].
  4. [Enter] [Enter].
- Is geen van beide mogelijk: haal de map kassa terug van de server (hoofdcomputer).

Controleer daarna de kassaverkopen en de prijzen. Controleer en stel zo nodig opnieuw in: JMD, Freedelity (artikelbestand volledig uitschrijven), doorsturen kassa (N/K), scanner, ticketprinter, koppeling Tomra, koppeling Bancontact (BC), koppeling Digi-weegschaal.

## 3. Glaive RT-560 met Freedelity (POSReady 2009) – IPL-backup van 2e partitie

Enkel gebruiken bij problemen met Windows zelf (blue screen, LSASS/ISASS.exe-fout) op een Firich Glaive RT-560 met Freedelity-koppeling.

1. Sluit een PS/2-toetsenbord aan (geen USB).
2. Stel de kassagegevens veilig (§2): kopie van `C:\KASSA` naar de 2e partitie (D:) of backup via punt 4, en indien mogelijk een N-transfer.
3. Zet de kassa aan. Zodra er tekst op het scherm verschijnt: druk enkele keren op pijl omhoog/omlaag [↑↓] om in het "Restore"-scherm te komen.
4. In het zwarte scherm: kies het onderste punt "[Press NO key but wait …]" en druk [Enter]. De kassa start nu op via de 2e partitie.
5. Kies in het Windows-scherm "IPL Backup Terugzetten" en bevestig nogmaals. Normaal wordt automatisch ook een backup van `c:\kassa` gemaakt.
6. De backup wordt automatisch teruggezet (± 20 minuten); het systeem herstart vanzelf.
7. Zet de kassagegevens terug (§2).

## 4. Glaive zonder Freedelity – "start"-backup (IPL) van USB-stick

De USB-stick moet achteraan in de voet van de kassa zitten (meestal is dat zo).

1. Sluit het toetsenbord aan.
2. Zet de kassa aan en druk zodra er tekst verschijnt (meermaals) op [DEL] om in de BIOS-setup te komen.
3. Blauw scherm: kies het derde punt "Advanced Chipset Setup" [Enter] (scherm "AMIBIOS SETUP – Advanced Chipset Setup").
4. Ga met de pijltjes naar "USB Device Legacy Support" en zet dit met [Page Up]/[Page Down] op "All Device". [Esc], dan [F10], bevestig "Save current settings and exit?" met Y [Enter].
5. De kassa herstart. Zodra er tekst verschijnt: druk [F11] voor het "Boot Menu". Normaal staat "USB RMD-FDD" gemarkeerd: druk [Enter].
6. Kassagegevens eerst naar de USB-stick kopiëren (indien nog mogelijk):
   - Kies met de pijltjes het menu "JAMADATA UTILITIES" [Enter]; geef het wachtwoord in (zie interne bron) en [Enter].
   - Kies "EXIT TO DOS" [Enter]; je komt op de prompt `A:\PC menu >`.
   - Typ, telkens gevolgd door [Enter]: `cd..`, `md kassa`, `cd kassa`, `c:`, `cd kassa`, `copy *.* a:` (vraagt hij "Overwrite": antwoord A = All).
   - Typ daarna: `a:`, `cd..`, `cd pcmenu`, `pcmenu`.
7. In het rode menuscherm: kies opnieuw "JAMADATA UTILITIES" (wachtwoord: zie interne bron) en dan "IPL-RESTORE USB STICK".
8. De backup wordt automatisch teruggezet (± 15 minuten); het systeem herstart vanzelf.
9. Zodra er tekst verschijnt opnieuw [DEL] → derde punt → "USB Device Legacy Support" terug op "disabled" zetten → [Esc] → [F10] bewaren.
10. Zet de kassagegevens terug: map KASSA handmatig van de USB-stick naar `C:` kopiëren, of via punt 5 in het kassamenu (§2).

## 5. Rich-Pos – backup van USB-stick/SATA-DOM

De USB-stick moet achteraan in de voet van de kassa zitten.

1. Sluit het toetsenbord aan.
2. Stel indien mogelijk de map `C:\KASSA` veilig op de USB-stick (D:) en doe een N-transfer.
3. Zet de kassa aan; zodra er tekst verschijnt enkele keren [↑↓] drukken om in het restore-scherm te komen.
4. Zwart scherm: kies het onderste punt "[Press NO key but wait …]" en druk [Enter]. De kassa start op via de USB-stick.
5. Kies in Windows "Jongste Backup Terugzetten". Dit duurt ± 15 minuten. Werkt dit niet, probeer dan "IPL Backup terugzetten".
6. Het systeem herstart automatisch.
7. Zet de kassagegevens terug (map KASSA van de USB-stick naar `C:`, of punt 5 in het kassamenu – §2) en controleer verkopen en prijzen.

## 6. PanelPC (Windows 10 IoT) – image restore van de SSD vanop USB-stick

Enkel gebruiken bij problemen met Windows (blue screen, virus) op een PanelPC.

### 6.1 Automatische werkwijze

1. Sluit een toetsenbord aan op de kassa.
2. Stel de kassagegevens veilig (§2): punt 4 in "Menu Beheer Key-conen Kassa" + indien mogelijk N-transfer; lukt dat niet, kopieer `C:\KASSA` naar `D:` via Verkenner.
3. Zet de kassa uit en terug aan; zodra er tekst verschijnt druk op **F12** (boot-keuzemenu).
4. Kies met de pijltjes de USB-stick ("Sandisk" of ander merk) en druk [Enter]. De kassa start op vanaf de USB-stick en toont het grijze Windows-aanmeldscherm.
5. Meld aan met het afbeeldingswachtwoord (volgorde: zie interne bron "afbeeldingswachtwoord kassa.pdf").
6. Windows start (Engelstalig, grijze "Jamadata"-achtergrond) en opent automatisch de Jamadata TeamViewer. Support neemt over met de TeamViewer-code van de klant (wachtwoord: zie interne bron).
7. Tip: hernoem eerst de huidige map `c:\kassa` (op de stick) naar `c:\kassa_USB`, zodat je een werkende map kassa behoudt bij problemen met de SSD.
8. Dubbelklik op het icoon "SSD Restore menu".
9. Klik **binnen de minuut** op "Laatste Backup terugzetten" en bevestig met "Yes" (100 % zeker?).
10. Er wordt automatisch eerst een backup gemaakt van de kassagegevens van `d:\kassa` naar `c:\kassa`. Druk [Enter] als dit gebeurd is, en klik "OK" bij de waarschuwing.
11. Het scherm lijkt stil te staan: gewoon wachten. Terugzetten duurt 4 à 8 minuten. Druk op het einde op [Enter] om te herstarten.
12. De kassa start weer normaal op vanaf de SSD. Zet de kassagegevens terug (§2).

### 6.2 Manuele werkwijze (Macrium Reflect)

1. Stappen 1 t/m 6 zoals hierboven (toetsenbord, backup map KASSA, F12, opstarten van USB-stick, aanmelden, TeamViewer).
2. Is de backup van `\KASSA` nog niet genomen: kopieer nu via Verkenner `D:\KASSA` naar `C:` (tip: hernoem eerst `c:\kassa` naar `c:\kassa_USB`).
3. Start het backupprogramma "Macrium Reflect".
4. Klik "Restore" → "Browse for an image or backup file to restore" → kies `c:\data\backup\images\C-00-00` → "Open".
5. Klik "Restore Image" → "Copy selected Partitions" → "Next" → op "Restore Summary" klik "Finish" → bevestig met "Continue..".
6. Terugzetten duurt 4 à 8 minuten. Klik op het einde "OK" en "Close", sluit Macrium Reflect en herstart de kassa.
7. Zodra er tekst verschijnt: druk [DEL] (BIOS). Ga naar "Boot" (4× pijl rechts) → "Hard Drive BBS Priorities" (5× pijl omlaag) [Enter] → [Enter] op "Boot Option #1" en selecteer de interne SSD (de `P0:`-schijf, bv. een ADATA 128 GB) [Enter]. Bewaar met [F10].
8. De kassa start weer op vanaf de SSD. Zet de kassagegevens terug (§2).

### 6.3 Sneltoetsen BIOS/boot op de nieuwe PanelPos

- **F11 / F12**: boot override (opstartmedium kiezen).
- **DEL / F2**: BIOS.

### 6.4 Kassa start (ongewild) op vanaf de USB-stick

Trek de USB-stick uit, start de kassa zo 2 keer op en steek de USB-stick daarna terug in.

## 7. Nieuwe image zetten lukt niet: "schijven kunnen niet automatisch toegewezen worden"

Symptoom: bij het installeren van de Jamadata-kassa-image verschijnt een foutmelding dat de schijven niet automatisch geselecteerd/toegewezen kunnen worden. Oorzaak: er staat al een image van de hardwareleverancier op de schijf.

Oplossing:

1. Haal de schijf uit de kassa en sluit ze via een cradle aan op je eigen computer.
2. Open `diskpart` (via CMD of Windows-zoeken). De "System Reserved"-partitie kan je niet via Schijfbeheer verwijderen, wel via diskpart.
3. `list disk` – bepaal de juiste schijf. Leg Schijfbeheer ernaast en vergelijk de grootte, zodat je niet per ongeluk je eigen Windows-schijf selecteert.
4. `select disk X`
5. `list partition`
6. Verwijder elke partitie: `select partition 1` → `delete partition override`; herhaal voor partitie 2, 3, 4, …
7. Plaats de schijf terug en zet de image opnieuw.

## 8. Backup maken na installatie

Na een (her)installatie van een kassa wordt een backup op de USB-stick gemaakt (Veeam Agent – "Backup now"). Zie ook `kassa-installatie-en-updates.md`.

## Bronnen

- `kassa/glaive_image_restore_freedelity.docx`
- `kassa/GLAIVE_IPL_restore_zonder_freedelity.docx`
- `kassa/RPrestor.docx`
- `kassa/PanelPC_image_restore_SSD vanop USB-stick.docx`
- `kassa/FAQ PanelPC kassa.docx`
- `kassa/KASSA.pdf` (OneNote-export: "08 BIOS en BOOT", "Automatisch toewijzen schijven werkt niet voor image kassa installatie")
- `kassa/Kassa installeren.docx`
