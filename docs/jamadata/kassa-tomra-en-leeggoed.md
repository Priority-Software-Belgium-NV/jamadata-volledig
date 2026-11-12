# Kassa – Tomra-leeggoedautomaat en leeggoed op de kassa

Gebruik dit document voor: de koppeling tussen een leeggoedautomaat (Tomra) en de Key-Conen kassa: het scannen van leeggoedtickets met of zonder controle van de bon, de instellingen in `kassys.dat`, de FTP-server/gedeelde map waar de automaat zijn ticketbestanden zet, het netwerkprobleem tussen oude XP-kassa's en Windows 10, en de leeggoedknoppen op de kassa (AUTO-LGG, LG-TERUG, LEEGG=OK). De programmeerbladen van de scanners (o.a. "TOMRA barcode" voor LI4278/DS2278) staan in de scannerdocumentatie.

## 1. Twee manieren om leeggoedtickets te verwerken

| | 1) ZONDER controle van de leeggoedbon | 2) MET controle van de leeggoedbon (Tomra ERS) |
|---|---|---|
| Principe | De barcode op het ticket bevat zelf het leeggoedbedrag; de kassa leest het bedrag uit de barcode (zoals een weegschaalbarcode). | De automaat schrijft per ticket een bestand (`*.TXT`) op een gedeelde map/FTP. De kassa zoekt bij het scannen het bestand op, boekt het bedrag en **wist het bestand**, zodat een ticket maar één keer gebruikt kan worden. |
| Beveiliging | Geen: een ticket kan meermaals gescand (of gekopieerd) worden. | Ja: een tweede keer scannen geeft een pop-up (bestand bestaat niet meer). |
| kassys.dat | posities 4020–4029 | posities 3662, 3666, 3676 |
| Barcode | begint met 99 (voorbeeld) | begint met de Tomra-prefix 980 |

## 2. Zonder controle – bedrag in de barcode

Vereist een kassaversie van na 05/12/2002 (elke huidige versie). Aanpassingen in `kassys.dat`:

```
upsys kassys.dat c 4020 3      (type 3: bedrag in barcode, negatief geteld = leeggoed)
upsys kassys.dat s 4021 4 99   (lead-in: barcodes die met 99 beginnen)
upsys kassys.dat c 4025 2      (positie van het codenummer)
upsys kassys.dat c 4026 5      (lengte codenummer)
upsys kassys.dat c 4027 7      (positie van het bedrag)
upsys kassys.dat c 4028 5      (lengte van het bedrag)
upsys kassys.dat c 4029 2      (aantal decimalen)
```

Opbouw van de barcode (EAN-13), voorbeelden:

| Barcode | Betekenis |
|---|---|
| `9999000000504` | leeggoed 0,50 EUR |
| `9999000000108` | leeggoed 0,10 EUR |
| `9999000004304` | leeggoed 4,30 EUR |

- De eerste `99` = herkenning leeggoedbarcode.
- De volgende `99000` = het codenummer (artikelnummer) van het leeggoed; dit nummer kan je kiezen.
- Dan de waarde van het leeggoed (5 cijfers, 2 decimalen); het laatste cijfer is de checksum.

Maak op de server zeker het artikel (bv. **99000**) aan: geen prijzen nodig, het moet in **groep 99 met 0 % btw** zitten. Daarna klaarzetten (V.2.K) en doorsturen (N).

## 3. Met controle – Tomra ERS (ticketbestanden via gedeelde map / FTP)

### 3.1 Instellingen op de kassa (`kassys.dat`)

| Positie | Type | Waarde |
|---|---|---|
| 3662 | s 4 | Tomra-prefix om de EAN-code van tickets te herkennen: **"980"**. Lege string = niet geactiveerd. |
| 3666 | s 10 | Artikelnummer (PLU) "Tomra leeggoed-terugname" (in Jamadata meestal 99000). |
| 3676 | s 32 | Tomra-pad waar de `*.TXT`-bestanden staan, bv. `\\server\tomra`, `t:\tomra` of `t:` – **zonder `\` op het einde**, ook bij `t:`. |

Stappen:

1. Zet op 3662 de tekst "980".
2. Laat een artikel "Leeggoed automaat" toevoegen met de juiste btw-code en groep; de prijs mag op 0 staan.
3. Zet op 3666 het PLU-nummer van dit artikel.
4. Zet op 3676 het pad naar de ticketbestanden. Meestal wordt op de kassa een netwerkschijf **T:** gekoppeld aan de gedeelde map `tomra` op de hoofdcomputer (aanmelden met de daarvoor aangemaakte gebruiker; gegevens: zie interne bron).

Werking: na het scannen van het ticket wordt het bijhorende bestand gewist. Een volgende keer hetzelfde ticket scannen geeft een pop-up. Op het kasticket komt onder de leeggoedlijn ook info over het Tomra-ticket: referentienummer, aantal artikelen, datum en uur van afdruk.

### 3.2 Instellingen aan de kant van Tomra (ERS via FTP)

Uit te voeren door de Tomra-technicus, in overleg met Jamadata. Benodigd: het barcodebestand `ersjama.cfg`, een intern IP-adres voor de automaat, en de locatie van de hoofd-pc waarop de FTP-server komt.

**FTP-server op de hoofd-pc (Windows, IIS):**

1. Maak op de C-schijf van de hoofd-pc een map `C:\tomra`; deel deze map met iedereen met lees- en schrijfrechten.
2. Configuratiescherm → Programma's en onderdelen → Windows-onderdelen in- of uitschakelen → **Internet Information Services** inschakelen, inclusief FTP-server (alle onderliggende vakjes).
3. Systeembeheer → **IIS-beheer** → pc-naam uitvouwen → rechtermuisklik op Sites → **FTP-site toevoegen**:
   - FTP site name: `tomra`; Physical path: `C:\tomra`;
   - IP-adres = IP van deze pc; **No SSL**;
   - Authentication = Basic; Allow access to = Specified users → de FTP-gebruiker; Permissions = Read en Write.
4. Firewall: "FTP Server" toelaten (alle vakjes aanvinken). Eventueel moet de firewall van het privénetwerk uitgezet worden.
5. Maak in Windows een lokale gebruiker aan voor de automaat (gebruikersnaam/wachtwoord: zie interne bron).
6. In IIS op de FTP-site: "FTP Authorization Rules" → Allow-regel voor de specified user met Read en Write.
7. Testen vanaf de automaat/een pc: in de browser `ftp://<IP van de hoofd-pc>` en aanmelden met die gebruiker.

**Op de automaat (ERS):**

- De automaat een intern IP-adres geven.
- "Online refund" op **2** zetten.
- Als barcodebestand `ersjama.cfg` laden.
- De regel `elrcptd` toevoegen aan `inetd.cmd` en in `inetd.ini` het blok `[elrcptd]` instellen:

  ```
  [elrcptd]
  Enabled=1
  Host=<IP-adres van de hoofd-pc>
  Protocol=ftp
  User=<FTP-gebruiker>
  Password=<wachtwoord: zie interne bron>
  Passive=1
  Detail=0
  Dir=//wpram/elrcpt
  RefMin=000000000
  RefMax=999999999
  FilePrefix=ER
  FileExt=txt
  FileName=7
  BarcodeFormat=980
  ```

De automaat zet dus per ticket een bestand `ER…​.txt` in de map `tomra`; de barcode op het ticket begint met 980.

### 3.3 Scanner

De handscanner moet de (Code 128/Interleaved 2 of 5) Tomra-barcode kunnen lezen. Daarvoor bestaat een apart programmeerblad "TOMRA barcode" (o.a. voor de LI4278 en de Zebra DS2278) – zie de scannerdocumentatie.

### 3.4 Problemen

| Symptoom | Oorzaak / oplossing |
|---|---|
| Pop-up bij het scannen van een Tomra-ticket | Het ticketbestand bestaat niet (meer): het ticket is al eens gescand/verzilverd, of het bestand is (nog) niet in de map aangekomen, of de kassa kan de map niet bereiken. |
| Geen enkel ticket wordt gevonden; "T-drive maakt geen connectie met de kassa/scanner" | De netwerkschijf T: is niet verbonden. Scherm overnemen en in Verkenner op de T-schijf klikken: de verbinding komt dan meestal terug. Controleer ook of de hoofd-pc aanstaat en het netwerk daar op "Privé" staat. |
| Jamadata blijft bij het opstarten hangen op de T-schijf | De T-schijf was overbodig/onbereikbaar (dezelfde share was ook beschikbaar via een andere driveletter, P:). De T-schijf verwijderd, waarna Jamadata vlot opstartte. Kijk dus na welke netwerkschijven echt nodig zijn. |
| Na vervanging/restore van de kassa werkt Tomra niet meer | Posities 3662/3666/3676 opnieuw zetten en de netwerkschijf T: opnieuw koppelen. |
| Oude XP-/POSReady-kassa kan de share op een Windows 10-pc niet meer koppelen | Zie §3.5. |

### 3.5 Oude kassa's (XP embedded Glaive, POSReady 2009 Rich-Pos) en een Windows 10-hoofd-pc

Met recente Windows 10-updates kan je vanaf de oudere kassa's geen drive meer mappen naar een Windows 10-pc. Oplossing: SMB 1.0 (en onveilige gasttoegang) terug toelaten op de pc/NAS waar de tickets toekomen. Dit verlaagt de beveiliging – enkel doen als het echt nodig is.

Op de Windows 10-pc:

1. Netwerkcentrum → Geavanceerde instellingen voor delen: bij Privé "Netwerkdetectie inschakelen" en "Bestands- en printerdeling inschakelen"; bij Alle netwerken "Delen van openbare mappen uitschakelen", "Bestandsdeling inschakelen voor apparaten met 40- of 56-bits versleuteling" en "Met wachtwoord beveiligd delen uitschakelen".
2. Zo nodig een lokale gebruiker en een gedeelde map aanmaken.
3. Register: in `HKLM\SYSTEM\CurrentControlSet\Services\LanmanWorkstation\Parameters` een DWORD `AllowInsecureGuestAuth` = 1 aanmaken.
4. `OptionalFeatures.exe` → "SMB 1.0/CIFS File Sharing Support" aanvinken → herstarten.

Op de XP-kassa: de netwerkschijf normaal koppelen. Lukt "opnieuw verbinden bij aanmelden" niet, zet dan een batchbestand in de map Opstarten:

```
ping 127.0.0.1 -n 11 >NUL
net use * /delete /yes
net use x: \\WIN10PC\shared
```

Verschillen gebruikersnaam/wachtwoord tussen beide toestellen: bewaar de aanmeldgegevens in XP via `rundll32.exe keymgr.dll, KRShowKeyMgr`, of geef de gebruiker mee in het script (`net use x: \\WIN10PC\shared /user:<gebruiker> *`).

## 4. Leeggoed op de kassa (gebruik)

- **AUTO-LGG**: schakelt automatisch leeggoed aanrekenen aan/uit. Op het display staat `L: A` als leeggoed automatisch geteld wordt.
- **LG-TERUG**: rekent enkel het leeggoed van het ingevoerde artikel (zonder het artikel) – voor teruggebracht leeggoed van een bepaald product.
- **LEEGG=OK**: zet hetzelfde leeggoed dat bij de verkochte producten werd aangerekend ook als teruggegeven leeggoed op het ticket (klant koopt 2 bakken en brengt 2 lege bakken van hetzelfde mee).
- **Blokje "Leeggoed"** in het hoofdmenu van de Key-conen: bevat alle leeggoedartikels in oplopende volgorde van bedrag (0,10 – 0,20 – 3,50 – 4,50 …).
- **Leeggoedbon op een andere kassa opmaken** (bv. aan de leeggoedinname) en afrekenen op de hoofdkassa: via Bewaren bon / Opladen bon met een gedeeld werkbonnenpad (kassys.dat positie 3286) – zie `kassa-installatie-en-updates.md` §7.
- Verwante instellingen in `kassys.dat`: 3200 (leeggoedsysteem per verkoper: auto leeggoed / leeggoed terugnemen), 3278 (LEEG_OK-type), 3584 (groepsnummer leeggoed), 3094 (tickettype: leeggoed mee of apart).

### Artikel op een bon zonder leeggoed

Wordt bij een artikel op een (lever)bon geen leeggoed meegeteld: op de artikelfiche moet het veld **"aantal leeggoed"** ingevuld zijn met 1. Staat daar niets, dan komt het leeggoed niet op de leverbon.

Het document `leeggoed_aanpassen.pdf` bevat enkel een afbeelding zonder uitleesbare tekst en is niet verwerkt.

## Bronnen

- `kassa/HOWTO-Installeren TOMRA op kassa.docx`
- `kassa/ERS jamadata_Tomra_FTP.docx`
- `kassa/Kassa installeren.docx` (Tomra-instellingen bij installatie)
- `kassa/KASSYS.docx` (posities 3662–3676, 4020–4029)
- `kassa/IRLEEGG.docx`
- `kassa/gebruikershandleiding keyConen KASSA 2.0.docx` (leeggoedknoppen)
- `Onenote/KASSA.pdf` ("T drive maakt geen connectie met de kassa/scanner", "Jamadata blijft hangen op T schijf bij opstart", "In een Bon een artikel geen leeggoed erbij geteld")
