# PDA: installatie, licentie, synchronisatie en storingen

Gebruik dit document voor: het klaarmaken van een nieuwe PDA (HERA, RANGER2) met JamaMobi, het opnieuw inzetten van een tweedehands/oude PDA, de JamaMobi-licentie verwijderen of opnieuw ingeven, problemen met synchronisatie (wifi, cradle, JamaSpda, Windows Mobile Device Center), de draadloze ticketprinter voor leeggoedbonnen en leeggoedbonnen zonder barcode. Het dagelijks gebruik (bestellingen, barcodes) staat in `pda-gebruik-en-bestellingen.md`.

## 1. Overzicht toestellen en software

| Onderdeel | Uitleg |
|---|---|
| **JamaMobi** | De applicatie op de PDA (bij Android-toestellen geïnstalleerd als `.apk`, in de bron `jamaMobi-111.apk`) |
| **JamaSpda** | Communicatieprogramma op de pc met de PDA-houder, enkel voor de oude PDA's (rode icoon op het bureaublad) |
| **WMDC** | Windows Mobile Device Center ("Windows mobiel apparaatcentrum"), nodig om oude PDA's via de cradle met de pc te verbinden |
| **JamaMobi server** | Servercomponent voor de nieuwe PDA; draait via de **Omnis Service** |
| **Jamamobi.dat** | Licentiebestand van JamaMobi op de hoofdcomputer van de klant |
| **JamaPDA.reg** | Registerbestand in de PDA-map. Klein registerbestand voor de pc waaraan de PDA gekoppeld wordt. De inhoud is niet uitleesbaar via de bronkoppeling en hier niet overgenomen. Vermoedelijk is dit "de regedit" uit de notitie over USB-geluidjes (zie 6.4) – onzeker / te verifiëren |
| `F:\JamaPDA\Install\` | Interne map met handleidingen voor de oudere PDA-types |
| `F:\jamapda\jamaspda\RegASYNC.bat` | Batchbestand met de registerfix voor WMDC (zie 6.3) |

Toesteltypes in de bronnen: Zebra MC55, MC9000-reeks, Dolphin, oudere Symbol/M3/Honeywell (oude generatie); **HERA** (wordt niet meer geleverd) en **RANGER2** (actueel, notitie december 2025) als Android-toestellen.

## 2. RANGER2 installeren en configureren (actueel toestel)

1. Start de RANGER2 op; kies taal **Nederlands**, regio **België**.
2. **Starten → Overslaan → Offline instellen**.
3. Tijd en datum instellen.
4. Google-services: **alles deselecteren → Accepteren**.
5. Schermvergrendeling: **Overslaan → Toch overslaan**.
6. Open de app **Barcode Utility**.
   - Submenu **Function settings**:
     - *Control options*: **Barcode data output mode** op **"to keyboard"**; **Pass Scan Key Value** uitzetten.
     - *Letter spell option (CASE)*: **Lower Case**.
     - *Format output options*: **prefix 1** op `/`, **suffix** op `*`.
   - Submenu **Barcode settings**:
     - **EAN 8**: 2 Digit Addenda uitzetten.
     - **EAN 13**: 2 en 5 Digit Addenda uitzetten.
7. JamaMobi installeren:
   - Verbind de PDA met de computer via de **mobiele laadkabel** (niet via het station).
   - Zet op de PDA bij de meldingen de USB-voorkeur op **gegevensoverdracht**.
   - Sleep de 2 apk-bestanden (JamaMobi en TeamViewer QuickSupport) naar **Downloads** op de PDA en verbreek de verbinding.
   - Open op de PDA onder **Files** de apk's; kies telkens **Continue** en **Install**.
8. Noteer het serienummer (S/N, op de achterkant van de doos) en geef dit door in het order.
9. Open JamaMobi → **Settings → PDA instellingen → Priority/Jamadata server adres** en vul het serveradres in (adres en poort: zie interne bron).

## 3. HERA installeren en configureren (wordt niet meer geleverd)

Voorbereiding: PDA uitpakken, batterij plaatsen, pistolgrip monteren, opladen via de cradle.

Eerste opstart:
1. Taal Nederlands, regio België.
2. Starten → Overslaan → Offline instellen.
3. Datum en tijd instellen.
4. Google services → alles deselecteren → Accepteren.
5. Schermvergrendeling → Overslaan → Toch overslaan.
6. Versnelde locatiebepaling → deselecteren → Volgende. De PDA herstart automatisch.
7. Vraagt het toestel een Home App: **Quickstep – Always**.

**BCR Settings**:

| Onderdeel | Instelling |
|---|---|
| Decoder | Label op **Both** |
| Format | Prefix `/` ; Suffix `*` ; Case conversion **To lower case** ; Replace GS **Spatie** ; Replace non-printable **Spatie** |
| Output | Method **Simulate keyboard event** |
| Symbology | Alles uit, behalve: Code 39, EAN-8, EAN-13, UPC-A, UPC-E0, UPC-E1, QR-Code |
| EAN-8 (ingedrukt houden) | **Addon 5** aanzetten, **Transmit check characters** aanzetten |
| EAN-13 (ingedrukt houden) | **Transmit check characters** aanzetten |
| Onderaan, onder OCR | Mode **Both** ; Template **MICR E-13B** |

Apps installeren:
1. PDA via USB met de computer verbinden; USB preferences bij de meldingen op **File Transfer**.
2. `jamaMobi-111.apk` en `TeamViewerQS.apk` naar de PDA slepen (Download); verbinding verbreken.
3. Op de PDA beide apk's aantikken om te installeren.
4. Optioneel: overtollige widgets op het homescherm ingedrukt houden en op **Remove** slepen.

Configuratie deel 2:
- **Settings → System → Languages**: Nederlands/België toevoegen, Engels verwijderen.
- Toetsenbord nog QWERTY? Tik op de Google-zoekbalk om het toetsenbord op te roepen → tandwiel → **Languages** → QWERTY deselecteren, naar rechts vegen, **AZERTY** selecteren.

Afwerking: PDA volledig opladen, de interne checklist "Jamadata PDA" invullen en het serienummer in het order noteren.

Opmerking: op beide toestellen is de scanner zo ingesteld dat een barcode als toetsenbordinvoer binnenkomt, in kleine letters, met prefix `/` en suffix `*`. Reageert JamaMobi niet (meer) op scans, controleer dan eerst deze instellingen.

## 4. JamaMobi-server (nieuwe PDA)

- De installatie gebeurt met een interne installatiegids (JamaMobi installer; de pagina in OneNote bevat enkel een bijlage/schermafdrukken).
- Als de **Omnis Service** niet automatisch is geïnstalleerd, moet die manueel geïnstalleerd worden volgens de Omnis-technote *TNWI0002* (omnis.net, developers/resources/technotes).
- De PDA bereikt de server via het adres dat in JamaMobi staat onder **Settings → PDA instellingen → Priority/Jamadata server adres**.

## 5. Licentie van JamaMobi verwijderen / opnieuw ingeven (nieuwe PDA)

Wanneer: een toestel moet uit de licentielijst (vervanging, defect, verkeerd toestel geregistreerd).

1. Ga op de **hoofdcomputer van de klant** naar `J:\Jamadata\Omnis\Startup\Jamamobi.dat`.
2. **Kopieer het bestand eerst naar je eigen pc** en bewerk het daar, zodat de klant niet ziet hoe de licenties beheerd worden. De licenties staan in leesbare tekst in dit bestand.
3. Open in Kladblok en verwijder het/de gewenste toestel(len) uit de lijst; zet het aangepaste bestand terug.
4. Herstart het toestel: JamaMobi vraagt opnieuw om de licentie.
5. Licentie opnieuw ingeven:
   - de klant zoekt in zijn mails de **QR-code** die hij bij levering kreeg (bevat serienummer/licentiecode), of
   - intern opzoeken in de SharePoint-map met JamaMobi-licenties (als de licentie bij aanmaak correct is opgeslagen staat daar de QR-code of een txt-bestand).

Deel de inhoud van het licentiebestand nooit met de klant.

## 6. Synchronisatieproblemen

### 6.1 Nieuwe PDA: fout tijdens SYNC
1. Controleer het **server-IP/adres** via de instellingen van JamaMobi.
2. Controleer of de PDA **verbonden is met wifi**.
3. Blijft het probleem: escaleren naar Jamadata-support.

### 6.2 Oude PDA stuurt niet meer door via wifi na eenmalig gebruik van de cradle
Als een oude PDA (Zebra of ouder) normaal via wifi doorstuurt en één keer via de cradle is doorgestuurd, verwacht de PDA daarna altijd de cradle. Oplossing: de PDA **volledig herstarten**:

| Toestel | Herstart |
|---|---|
| MC55 (Zebra) | Rode knop op het toetsenbord |
| Dolphin | Stylus in het reset-gaatje aan de rechterkant |
| HERA / RANGER2 | Android opnieuw opstarten |
| Oudere modellen | Rode knop op het toetsenbord |

### 6.3 Windows mobiel apparaatcentrum (WMDC) start niet
Komt voor op Windows 10 met de laatste updates.
1. Open een opdrachtprompt **als administrator**.
2. Voer uit:
   ```
   REG ADD HKLM\SYSTEM\CurrentControlSet\Services\RapiMgr /v SvcHostSplitDisable /t REG_DWORD /d 1 /f
   REG ADD HKLM\SYSTEM\CurrentControlSet\Services\WcesComm /v SvcHostSplitDisable /t REG_DWORD /d 1 /f
   ```
   Dezelfde regels staan in `RegASYNC.bat` in `F:\jamapda\jamaspda\` (als administrator uitvoeren).
3. Herstart de computer.

### 6.4 Pc geeft constant "USB aangesloten / verwijderd"-geluidjes
Kan te maken hebben met de Zebra PDA in de houder.
1. Voer "de regedit" uit en voer eventueel ook de **WMDC-update** uit. De notitie zegt niet welk registerbestand bedoeld is; vermoedelijk `JamaPDA.reg` en/of de registerfix uit 6.3 (onzeker / te verifiëren).
2. Nog steeds? Pc herstarten.
3. Nog steeds? Alles opnieuw installeren.

### 6.5 Geen netwerk met MC55 of MC9000-reeks
De FAQ verwijst naar een scherm met wifi-parameters dat enkel als afbeelding bestaat; de waarden zijn niet uitleesbaar. Onzeker / te verifiëren in de originele `FAQ PanelPC PDA.docx`.

### 6.6 Oude PDA: algemeen
- PDA moet uit de programma's zijn en in de houder zitten.
- JamaSpda moet actief zijn op de pc met de houder tijdens de overdracht (rode balk **ZEND : Doorsturen gegevens**).
- PDA voldoende opgeladen.

## 7. Tweedehands (oude) PDA opnieuw in gebruik nemen bij een andere klant

Stappenplan uit de interne notitie (april 2026); oude en nieuwe PDA's werken volgens hetzelfde principe, het verschil zit in communicatie en configuratie:
1. **Basisconfiguratie**: het correcte configuratiebestand **SYS.fas** op de PDA plaatsen (via de programmeur).
2. **Verbinding met pc**: PDA verbinden via WMDC; connectieparameters controleren en correct instellen.
3. **Netwerk**: wifi instellen en testen op de PDA.
4. **Printer**: IP-adres van de ticketprinter vast instellen; printerconfiguratie ingeven op de PDA.
5. **Functionele test**: een leeggoedticket testen via de hoofdkassa.
6. **Tweede kassa** (indien van toepassing): configureren zodat ook deze kassa leeggoedtickets kan scannen.

Detailhandleidingen voor de oudere types: `F:\JamaPDA\Install\` en OneNote.

## 8. Ticketprinter voor leeggoedbonnen (Epson, netwerk/wifi)

### 8.1 Draadloze ticketprinter opnieuw instellen (bv. na nieuwe wifi/router)
1. Installeer **EpsonNet Config** op een computer.
2. Sluit de ticketprinter aan op die computer met een printerkabel (USB-B naar USB-A).
3. Open EpsonNet Config en klik op **Vernieuwen** tot de printer gevonden is.
4. Dubbelklik op de printer om de instellingen te openen.
5. Pas de **wifi-SSID** aan.
6. Zet het **vast IP-adres** opnieuw juist.
7. Stel de **DNS** in: primair het IP van de router, secundair een publieke DNS-server.
8. Test met de PDA of leeggoedbonnetjes afgedrukt worden.
9. OK: printer terugplaatsen. **Niet OK: controleer de DNS** — een niet-ingestelde DNS was in de praktijk de oorzaak dat het niet werkte.

### 8.2 Aanmelden op de webpagina van een Epson LAN-printer
- De printer drukt standaard een ticket af wanneer je hem op het netwerk aansluit en dan aanzet; daarop staat het IP-adres dat hij gekregen heeft.
- Surf naar dat IP-adres en meld aan (login: zie interne bron `FAQ PanelPC PDA.docx`). Sinds 2020 is het wachtwoord het **serienummer van de printer**.

### 8.3 Geen barcode op leeggoedbonnetjes
- Oorzaak: vanaf ongeveer **200 bewaarde PDA-bonnen** worden geen barcodes meer afgedrukt.
- De klant kan het aantal bestanden controleren op de kassa via **Diversen → PDA bons**.
- Wil de klant niet dat oude leeggoedbonnen blijven staan: voeg in `kasmenu.dat` bij puntje **1** de opdracht `jdel vkpda*.dat -b -o5` toe (opkuis van de `vkpda*.dat`-bestanden). Onzeker / te verifiëren: de exacte betekenis van de opties `-b -o5` staat niet in de bron.

### 8.4 Voedingsadapter monteren
Er bestaat enkel een interne video ("PDA_montage voedingsadapter"); geen tekstuele procedure.

## Bronnen
- `Onenote/PDA.pdf` (volledigste versie; pagina's HERA, RANGER2, licentie, JamaMobi server, wireless ticketprinter, USB-geluidjes, geen barcode op leeggoedbonnetjes, 2e-hands PDA, doorsturen via wifi i.p.v. cradle)
- `PDA/PDA.pdf` (oudere, minder volledige export van dezelfde OneNote-sectie)
- `PDA/Licentie verwijderen van nieuwe PDA.pdf` = `Jamadrink/HOWTO - Licentie verwijderen van nieuwe PDA.docx`
- `PDA/Barcodes toevoegen met de nieuwe PDA.docx` (sync-fouten)
- `PDA/JamaPDA.reg` (enkel vermeld)
- `Jamadrink/HOWTO-Installeren JamaSpda.docx`
- `FAQ/FAQ PanelPC PDA.docx`
- `Markdown kennisbank/Jamadata_Kennisbank_PDA.md` (ruwe extractie, ter controle)
