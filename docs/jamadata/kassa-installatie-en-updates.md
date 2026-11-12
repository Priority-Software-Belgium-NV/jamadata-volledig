# Kassa – Installatie, vervanging, updates (RUNONCE) en overname op afstand

Gebruik dit document voor: het installeren van een nieuwe Key-Conen kassa (ook ter vervanging van een bestaande kassa bij een bestaande klant), het updaten van de kassasoftware met `runonce.kas`, het aanmaken van een nieuwe RUNONCE, het aanmelden op de kassa (afbeeldingswachtwoord), het overnemen van een kassa met TeamViewer, facturen afdrukken op de kassa (grote printer of via JMD), een mobiele kassa met draagbare printer, werkbonnen delen tussen kassa's en het leegmaken van een kassa voor doorverkoop. Hoofdzakelijk interne procedures voor Jamadata-support/technici.

## 1. Nieuwe kassa installeren (checklist)

Volgorde uit "Kassa installeren" (versie 2025):

1. USB-stick in de kassa steken en de kassa klaarmaken (image; zie `kassa-image-restore.md`).
2. Klantendisplay installeren (zie `kassa-klantendisplay-en-hardware.md`).
3. Support-sticker op de voet bevestigen.
4. Zorgen dat TeamViewer, LogMeIn en Edge werken op de kassa (startpagina `kb.jamadata.be`; test ook een gewone website).
5. LogMeIn opstarten en de kassa overnemen.
6. Windows-updates uitvoeren.
7. Touch utility aanzetten bij startup.
8. Het blad met serienummers (hardwarefiche) invullen en nakijken dat alles aanwezig is.
9. Kassagegevens van de klant ophalen (`fromklt`).
10. `Jama.bat` aanpassen naar de instellingen van de klant: kassanummer + `set JMS=<IP hoofdcomputer>`.
11. `Kasmenu.dat` aanpassen naar de instellingen van de klant (punt 1 + punt N of K).
12. Kas-databestanden overzetten naar de kassa (`\jamadata\kassa\*.dat`).
13. `Kassys.dat` van de klant in de map kassa zetten.
14. Parameters in `kassys.dat` eventueel juist zetten (printer, nieuw adres, …).
15. Bij de melding **"Ongeldige serienummer"**: F4 en daarna F10.
16. `Freedelity.ini` + `freedelity.exe` overzetten indien nodig. In de ini de `~` vervangen door de juiste naam; de ini staat in `C:\Gebruikers\Kassa\AppData\Local` (AppData is een verborgen map). Freedelity testen.
17. `Setpp2` uitvoeren voor het klantendisplay als de kassys van een oude kassa is overgenomen.
18. Klantendisplay aanpassen met het juiste batchbestand: `setpp` / `setpp2` / `setrp` / `setap` (zet positie 4036 in kassys.dat; staat de parameter in dat bestand fout – te zien aan het type kassa – zet hem dan juist en hernoem het batchbestand).
19. `Kasmodsv.exe` overzetten als de kassa via de Jamadata-server doorstuurt (punt K).
20. `Runonce.kas` laten uitvoeren (laatste programmaversies).
21. Oude `kaslog.*` en oude `kl20xx*`-bestanden wegdoen.
22. Is het een kassa ter vervanging: `kaslog.dat` + `*.wrk` overzetten, eventueel `kasfac.dat`.
23. Jamadata Desktop instellen.
24. Altijd een backup nemen van de volledige map kassa van de oude kassa (op haar USB-stick) en die op de nieuwe kassa zetten in een map `kasold-0x`.
25. UPSYS32-aanpassingen doen:
    - Tomra: `S 3662 4 "980"`, `S 3666 10 <artikelnummer Tomra leeggoed-terugname>` (meestal 99000), `S 3676 32 "t:"` (Tomra-pad);
    - werkbonnen van een andere kassa halen: `S 3286 len 64: \\wintouch-01\kassa`.
26. Backup maken op de USB-stick (Veeam Agent – "Backup now").

### 1.1 Kassa vervangen bij een bestaande klant (aanvullend stappenplan)

1. Kopie maken van de oude kassa naar de stick – best van de volledige map `Kassa`.
2. `Kassys.dat`, `kaslog.dat`, `kaslog.001`, `kasfac.dat` en alle `*.wrk`-bestanden overzetten naar de nieuwe kassa (in speciale gevallen ook de `kl20JJMM`-bestanden).
3. Computernaam van de kassa wijzigen (eigenschappen pc).
4. `Jama.bat` aanpassen naar het juiste kassanummer.
5. `Kasmenu.dat` van de oude kassa openen (Kladblok niet als standaardprogramma instellen) en de klantspecifieke lijnen overnemen in de kasmenu.dat van de nieuwe kassa. Is er op de nieuwe kassa geen betaalterminal gekoppeld: de lijn die de koppeling opent verwijderen.
6. Klantendisplay juist zetten (`setpp`/`setpp2`/`setrp`/`setap`, positie 4036).
7. In de JMD de post juist zetten en de documenten/printers juist zetten.
8. Printer controleren: kassa openen → punt 3 → F8 → F8.
9. **Alles testen**: ticketprinter, scanner, Freedelity, Bancontact, geldlade, eID-lezer, afdrukken van facturen, bonnen.
   - Werken de bonnen niet: verbinding maken met de andere kassa (werkbonnenpad, §7).
   - Werkt de geldlade niet: de ladecode controleren via punt 3.
10. Teamviewer/LogMeIn + backup op de USB-stick.

### 1.2 Hardwarefiche Key-Conen Win Touch kassa

Bij levering wordt per kassa genoteerd: datum, klant, kassa (PanelPos) + serienummer, thermische seriële ticketprinter + serienummer, klantendisplay + serienummer, scanner (types MT2090, DS9208 USB, LS2208 USB, LI4278 USB) + serienummer, eID-reader, toetsenbord, geldlade (klaplade of schuiflade), stroom- en printerkabel, COM-adapterkabel, 2 stiftjes, scannerblad, blokjes- en kassadocumentatie, eventuele 2e ticketprinter/2e geldlade, aantal netwerkkabels, SSD 128 GB, USB-stick 64 GB, sticker Jamadata, licentie Windows 10 IoT, geleverd door.

## 2. Aanmelden op de kassa (Windows)

- De kassa gebruikt een **afbeeldingswachtwoord** (aanmelden door op de Jamadata-icoontjes te drukken; volgorde: zie interne bron "afbeeldingswachtwoord kassa.pdf"). Dit werkt zonder toetsenbord.
- Vraagt de kassa bij het opstarten om een gewoon (getypt) wachtwoord, dan is het afbeeldingswachtwoord waarschijnlijk 3 keer fout ingegeven. Geef dan het gewone wachtwoord van de gebruiker `kassa` in (wachtwoord: zie interne bron; met hoofdletter, cijfer en uitroepteken). Daarna werkt het afbeeldingswachtwoord opnieuw; zo niet, contacteer de helpdesk.
- Wijzigt de klant het wachtwoord zonder dit aan Jamadata mee te delen, dan vervalt de support op die kassa.
- Melding **"!!!Ongeldige serienummer!!!"** bij het starten van het kassaprogramma: overrulen met **F4 en dan F10** (komt voor na het overzetten van een kassys.dat naar andere hardware, en bij een mobiele kassa).

## 3. Kassa overnemen op afstand

### 3.1 TeamViewer (o.a. Glaive-kassa)

1. Support start TeamViewer op de eigen pc.
2. De klant opent op de kassa de browser en gaat naar `kb.jamadata.be`.
3. Onderaan in het midden (naar beneden scrollen met de scrollbalk rechts) staat in de rode balk "Remote support": daarop drukken.
4. De kassa geeft een foutmelding: gewoon op OK drukken.
5. De klant krijgt een code en geeft die door.
6. Support geeft de code in en drukt op verbinden. De klant krijgt opnieuw een foutmelding: OK.
7. Support geeft het wachtwoord in (zie interne bron).

### 3.2 LogMeIn

Op nieuwe kassa's wordt naast TeamViewer ook LogMeIn geïnstalleerd; bij installatie wordt de kassa hiermee overgenomen.

## 4. Kassasoftware updaten met RUNONCE.KAS

`runonce.kas` is een updatepakket dat de kassa bij het opstarten van het kassaprogramma **één keer** automatisch uitvoert.

### 4.1 Manueel plaatsen (meest gebruikte werkwijze)

1. Sluit de Key-Conen kassa volledig af tot op het bureaublad van de kassa.
2. Haal de laatste `runonce.kas` op van de interne Jamadata-fileshare (map `Jamadata\Kassa\runonce.kas\`).
3. Plaats het bestand op de kassa van de klant in de map `Jamadata\Kassa\` (`C:\KASSA`).
4. Start de Key-Conen kassa opnieuw op: de update wordt automatisch uitgevoerd.
5. Laat de kassa voor de veiligheid nog eens herstarten.

### 4.2 Klaarzetten via "binnenbellen" (T en M)

1. Laat de klant met de kassa binnenbellen via **T** en **M** in het kassamenu (bij recente kassa's volstaat T; bij oude kassa's na de T ook de M).
2. Kijk op de SC-server onder welke code de klant heeft binnengebeld (meestal de 3-lettercode van de klant, "XYZ").
3. Maak een tijdelijke map met die code.
4. Kopieer de laatste `runonce.kas` (interne map `runonce.kas`) in die map.
5. Voer `Dumpmod XYZ` uit (met de code van de klant).
6. Bij de volgende keer binnenbellen installeert het programma zichzelf op de kassa. Laat de kassa daarna eens herstarten.

### 4.3 Meesturen met de dagelijkse transfer (oudere werkwijze, "updauto")

Bestanden die naar de kassa moeten worden op de hoofdcomputer in `\kassa\to\kassa-01\` gezet via een batch (`updauto` / `j.bat`), bv.:

```
copy kassa.exe \kassa\to\kassa-01\*.*
copy kasmenu.exe \kassa\to\kassa-01\*.*
copy kassys.dat \kassa\to\kassa-01\*.*
copy kasmenu.dat \kassa\to\kassa-01\*.*
```

Daarna op het werkstation `go` (als iedereen uit het programma is mag het `go x` zijn) en op de kassa doorsturen met **N**. Varianten: `kassys.dat` meegeven als `kassys.001` met in `j.bat`: `COPY KASSYS.001 ..\KASSA\TO\KASSA-01\KASSYS.DAT` (idem `kasmenu.001`).

Programmabestanden die samen up-to-date moeten zijn: `KASSA.EXE`, `KASMENU.EXE`, `KASPARM.EXE`, `KASSCR.SCJ`, `KEYCOONN.JAM`, `JAMACON.DLL` (+ het koppelprogramma van de betaalterminal).

### 4.4 Een nieuwe RUNONCE.KAS aanmaken (ontwikkeling/support)

1. Ga met Verkenner naar de interne map `F:\KASSA\RUNONCE.KAS`.
2. Kopieer het bestaande `runonce.kas` weg naar een andere map (bv. `old`).
3. Kopieer de bestanden die je wil wijzigen (meestal uit de submap `beta`) in deze map.
4. Pas eventueel `run.bat` aan (als je nieuwe bestanden selectief wil installeren).
5. Ga naar de submap `util` en dubbelklik op `mkonce.bat`.

Let op – **XP-kassa's (Glaive / Rich-Pos)**: op deze kassa's wordt het kassaprogramma niet meer vernieuwd. De "oude" programma's hebben het suffix `XP` en worden op zulke kassa's geïnstalleerd in plaats van de nieuwe. Wijzig je bestanden die mogelijk niet werken met die oude versie, kopieer dan eerst de oude naar XP en pas `run.bat` aan zodat op een XP-kassa de XP-bestanden geïnstalleerd worden.

Er bestaat een aparte runonce voor de Freedelity-installatie (`runonce.P&T`), zie `kassa-klantenkaarten-cadeaubons-tegoedbons.md`.

## 5. Facturen afdrukken op de kassa

De knop **Factuur** op de kassa kan een kleine factuur (op de ticketprinter), een leveringsbon of een grote (A4-)factuur afdrukken. Welke types toegelaten zijn staat in `kassys.dat` positie **3612** (bit 0 = kleine factuur, bit 1 = grote factuur, bit 2 = leveringsbon, bit 3 = via JMD). Standaardwaarde 4 = enkel leveringsbonnetjes.

### 5.1 Via JMD (huidige werkwijze)

1. Maak eerst een kopie van de map kassa.
2. Haal `kassys.dat` en `kasmenu.dat` op.
3. `upsys kassys.dat i 3612 12` (i.p.v. standaard 4).
4. Pas in `kasmenu.dat` punt 1 aan zodat de JMD mee start en stopt:

   ```
   start jmd.exe /min #A
   ping 127.0.0.1 -n 4
   kassa.exe
   start jmd.exe /min #C
   ping 127.0.0.1 -n 2
   ```

   Nieuwere variant (werkt enkel op 32-bit, wegens "(x86)" in Program Files): `start C:\Progra~1\Jamadata\JMD\jmd.exe /min #A` … `start C:\Progra~1\Jamadata\JMD\jmd.exe /min #C`.
5. Geef `kassys.dat` en `kasmenu.dat` terug, samen met de laatste `RUNONCE.KAS`.
6. Zorg dat de JMD kan opstarten op de kassa: in `jms.ini` op de server een post toevoegen (postcount bovenaan verhogen; kopie van een post als voorlaatste zetten; `Name=KASSA`; `Scherm-004_BootSequence=` met de opstarttoetsen voor de kassapost – waarde: zie interne bron).
7. Test het afdrukken: **F12 = testpagina/testfactuur** op de kassa.
8. Wis de gemaakte testfacturen en zet `kaslog.dat` en eventueel `kasfac.dat` terug uit de kopie.

Aandachtspunten:

- Glaive: de printer moet HP PCL5-compatibel zijn, liefst een netwerkprinter (aansluiten via netwerk en een TCP/IP-poort toevoegen op het juiste IP-adres).
- Verkeerd lettertype: voeg het font `cour.ttf` toe op de kassa (bestand in de map kassa zetten, dan Configuratiescherm → Lettertypen → toevoegen).

### 5.2 Variabele factuurlay-out (Windows-versie, kassa.exe na 08/10/2013)

Printer via USB aansluiten, drivers installeren, als standaardprinter instellen en een testpagina drukken. De lay-out heet `keyfact.png`. Stuur `kassys.dat`, `keyfact.png`, `jamap.dll` en de nieuwste `kassa.exe` naar de kassa. In kasparm: onderaan normaal **16 en 0** voor de extra bovenmarges en het aantal facturen op 2 of 3.

### 5.3 Glaive met PCL3-laserprinter (oudere Windows-versie)

Laserprinter met HP PCL3-emulatie (zeker geen GDI-printer) via USB aansluiten **zonder** drivers te installeren; wel de juiste USB-poort selecteren en een testpagina drukken. `kassys.dat` positie **3708** (i) op 2 = aantal facturen. Standaardlay-out: `keyfact.jam`. In kasparm: factuurhoofding invullen en onderaan normaal **15 en 0**.

### 5.4 Epson-kassa (DOS-versie) met matrixprinter

OKI Microline 380 met IBM PPR-emulatie; `kassa32n.exe` van min. 20/01/2003; `kassys.dat` 3612 (i) op 2. In kasparm de factuurhoofding invullen en onderaan 2 × 0 voor de extra bovenmarges. Printer: tegelijk "Font" + "Pitch" drukken voor het menu; "Group" = volgend item, "Set" = wijzigen (emulatie op IBM PPR), "Item" om dieper te gaan tot "Form Tear-off" → 300 ms; "Exit" om het menu te verlaten.

### 5.5 Factuur staat te hoog of te laag

1. Steek het papier zoals gewenst en druk een factuur af.
2. Kijk hoeveel lijnen het woord FACTUUR te hoog of te laag staat t.o.v. het voorgedrukte blokje.
3. Corrigeer dit in `kasparm.exe` (scherm "grote facturen") en druk opnieuw af; herhaal tot het klopt.
4. Staat FACTUUR juist maar de hoofding te hoog: tik de lijnen van de factuurhoofding lager (bovenaan lege lijnen laten).

## 6. Mobiele kassa met draagbare printer

- Melding "Ongeldige serienummer" bij het opstarten: F4 en dan F10.
- Gebruikte mobiele printer: Sewoo LK-P30II (wifi, met ingebouwd access point). Standaard IP-adres van de printer 192.168.100.1, poort 6001.
- Papier: thermisch (ticket/label), breedte 25,5–79,5 mm, rol max. Ø 56 mm, kern 12,5 mm.
- De driver is te downloaden op de site van de fabrikant (miniprinter.com).
- Aanpassing in kassys.dat: `upsys32 i 3716 1` (was 17) – niet meer cutten (de printer heeft geen cutter) en eerst de hoofding printen en dan direct de rest.

## 7. Werkbonnen (bewaarde bons / leeggoedbons) delen tussen meerdere kassa's

Doel: een bon opmaken op kassa 3 (bv. leeggoed aan de ingang) en oproepen op kassa 1 of 2. Alle werkbonnen (`*.wrk`) worden dan op kassa 1 bewaard; kassa 2, 3, … hebben geen eigen werkbonnen meer.

- Op de **hoofdkassa (kassa-01)**: geen aanpassing.
- Op **alle andere kassa's**: `upsys kassys.dat` → `s 3286 len 64` zetten op `\\wintouch-01\kassa` (huidige kassa's). Bij de oude keytouch-kassa's was dit `\\keytouch-01\hd-c\kassa`.
- Software: op alle kassa's de versie van na 13/12/2006.
- Oude ATA-/flash-kassa: het UNC-pad werkt daar niet; voeg in `jama.bat` de lijn `use f: \\keytouch-01\hd-c` toe en zet in upsys `f:\kassa`.

Werken de bonnen niet op een 2e kassa: controleer de verbinding met de andere kassa (het werkbonnenpad op positie 3286).

## 8. Kassa leegmaken voor (door)verkoop

Checklist van te verwijderen/leeg te maken gegevens:

- `Kasfac`, `Kaslog`, alle `KL`-bestanden, alle `WRK`-bestanden, alle `res`-bestanden, alle pdf's
- Freedelity (exe/ini)
- `Kasfacklt`, `Kaskrtnm`, `Kaskrtpt`
- `Kaspluex` en `Kasplust`
- `Kasusr.dat` leegmaken, `Kasplu.dat` leegmaken
- Parameters in de kassa leegmaken (tickethoofding e.d.)
- Eventuele Digi-bestanden verwijderen

## Bronnen

- `kassa/Kassa installeren.docx` (en `.pdf`)
- `kassa/HOWTO-Kassa installeren bij bestaande klant.docx`
- `kassa/HOWTO-Kassa laatste versies klaarzetten en installeren.docx`
- `kassa/HOWTO Aanmaken nieuwe RUNONCE.docx`
- `kassa/HOWTO-Kassa overnemen met TEAMVIEWER.docx`
- `kassa/HOWTO-Kassa Paswoord .docx`, `kassa/afbeeldingswachtwoord kassa.pdf`, `kassa/FAQ PanelPC kassa.docx`
- `kassa/HOWTO-Instellen FACTURATIE op kassa .docx`
- `kassa/IRLEEGG.docx`
- `kassa/Hadware touchkassa.docx`, `kassa/Hardware touchkassa.pdf`
- `kassa/HOWTO-Instellen BANKSYS.docx` (updauto-voorbeeld)
- `Onenote/KASSA.pdf` (01 Keyconen Kassa Updaten; 12 Kassa leegmaken voor verkoop; Stappenplan kassa installeren; "F12 is een testfactuur maken op de kassa")
- `Jamadrink/HOWTO-Mobiele kassa met draagbare printer.docx`
- `Jamadrink/HOWTO - Klantenkaarten via JMD installeren.docx` (jms.ini-post voor de kassa)
