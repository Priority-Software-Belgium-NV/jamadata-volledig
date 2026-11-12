# Installatie: Jamadata Desktop (JMD) en installatiedraaiboek Jamadata Server

Gebruik dit document voor: het installeren en instellen van Jamadata Desktop op een werkpost (verbinding met de server, ComfortLink, lokale printers), het voorbereiden van een centrale computer (vast IP, firewall, J-schijf, virusscanner, USB-stick) en het stap-voor-stap installatiedraaiboek van de Jamadata Server (JMS, JMT, JMR) met nacontroles. Voor het verhuizen van een bestaande installatie naar een nieuwe server: zie `installatie-migratie-naar-nieuwe-server.md`.

Licentiecodes, serienummers en wachtwoorden staan bewust niet in dit document (zie interne bron).

## 1. Jamadata Desktop (JMD) installeren op een werkpost

**Waarvoor:** de Jamadata Desktop is het viewer-programma waarmee in het Jamadata-pakket gewerkt wordt. Er is altijd een Jamadata Server nodig (in het netwerk of op afstand).

### Stappen
1. Download het installatiebestand via `www.fl.be/jmdn`; werkt dat niet (o.a. Telenet-klanten), gebruik `jmdn.prsw.be`.
2. Kies **uitvoeren** en doorloop de wizard (Volgende ... Voltooien); er hoeft niets aangepast te worden.
3. Na **Voltooien** start Jamadata Desktop automatisch. Soms start hij de eerste keer niet goed: sluit en start opnieuw via het bureaubladicoon.
4. Stel de verbinding in via menu **Configuratie** (bovenaan) > **Instellingen** (links).

### Instellingen wanneer de server in hetzelfde netwerk staat
| Veld | Waarde |
|---|---|
| **IP-adres server** | Het (vaste) IP-adres van de Jamadata Server. Onbekend? Navragen bij de hardwareleverancier. Als het adres juist is en de server bereikbaar, verschijnt er een groen vinkje (uit opleiding, 01/06/2026). Op de server zelf: `127.0.0.1`. |
| **Postnummer** | Het nummer van deze werkpost. Opzoeken in een andere Jamadata Desktop: **+ (Aanpassen parameters) > J (JMS-instellingen) > 4 (Instellingen werkposten)**; daar staan de postnummers per gebruiker. Anders navragen bij Jamadata. Elk postnummer mag maar één keer tegelijk in gebruik zijn. |
| **Post-licentie** | De standaard postlicentiecode (zie interne bron / installatiehandleiding). |

### Instellingen voor werken buiten het bedrijf (ComfortLink)
- Vink aan: **"Zet vinkje wanneer u buiten het bedrijf wenst te werken."**
- **Dossiernummer:** het dossiernummer dat de klant van een Jamadata-medewerker kreeg.
- Zie `it-remote-support-vpn-shares.md` voor poort 5006 en de VPN-omweg in het buitenland.

### Meerdere Windows-gebruikers
Jamadata Desktop moet onder **elke Windows-gebruiker** die ermee werkt geïnstalleerd/ingesteld worden (uit opleiding, 11/06/2026).

### Printers op de werkpost
- Zonder wijziging wordt afgedrukt zoals standaard ingesteld op de server (hoofdmenu **+ . J . 1**, afdrukposten).
- Eigen of afwijkende printer op deze pc: menu **Configuratie** > **Documenten**. Bovenaan staan tabs per document. Per document: vink het **onderscheppen** van dat document aan, kies onderaan **"Afprinten op onderstaande lokale printer"** en selecteer de lokaal geïnstalleerde printer. Herhaal voor de andere documenten, bevestig met **OK** en test.
- Deze werkpostinstellingen "overrulen" de serverinstelling. Op de server zelf hoeven de vinkjes niet aan te staan.

### Na een update
Na het installeren van een programma-update ook de viewer bijwerken: Jamadata Desktop > **Configuratie** > **Nieuwe versie installeren**.

### Problemen
| Symptoom | Controle / oplossing |
|---|---|
| "Wachten op serversessie" | Zie `faq-server-en-algemeen.md`: IP-adres server, dubbel postnummer, firewallpoorten, draait de JMS? |
| JMD komt niet online, virusscanner met eigen firewall (bv. Avast) | Het firewall-schild van de virusscanner houdt de communicatie JMS-JMD tegen. Regel toevoegen voor IN/UIT TCP-poorten 5000-5006 en 5100-5130, best bovenaan de regels. |
| Op alle werkposten staan maar stukken tekst van het menu | Bij één klant opgelost door de Jamadata Server als Light (user mode) te installeren; de Windows-gebruiker op de server had daar geen wachtwoord. |
| Werken op afstand maakt geen verbinding | Uitgaande poort 5006 openzetten op die pc / hardware-firewall. |

## 2. Centrale computer voorbereiden (eventueel door de hardwareleverancier)

Doe je het zelf, dan moet je achteraf niet zoeken wat de installateur vergeten is.

1. **Software:** een Excel-viewer (als er geen Excel geïnstalleerd is) en Acrobat Reader of een andere PDF-reader; stel de PDF-reader in als standaard.
2. **Schijf:** maak de map `jamadata` aan op een schijf waarop geen systeemherstel gebeurt. Bestaat zo'n schijf niet: verklein de C-schijf en maak een **J-schijf** (min. 15 GB, liefst ± 50 GB).
   - Rechtermuisklik op **Deze pc** > (Meer opties) > **Beheren** > **Schijfbeheer**.
   - Rechtermuisklik op C: > **Volume verkleinen**; geef de grootte in MB (50000 = ± 50 GB).
   - Rechtermuisklik op de nieuwe niet-toegewezen ruimte > **Nieuw eenvoudig volume** > stationsletter **J** > volumenaam bv. "Jamadata" > Voltooien (wordt geformatteerd).
   - Niet vergeten de letter J te geven. Koos de IT-partner zelf een andere letter (bv. D:) en zit die in zijn back-upplan, laat het dan zo (uit opleiding, 01/06/2026).
3. **Virusscanner:** `J:\jamadata` en `S:\jamadata` (back-upmedium) uitsluiten van controle. Niet alle scanners laten dat lokaal toe; vraag het dan aan de hardwareleverancier/IT-partner van de klant.
4. **Vast IP-adres** op de centrale computer (bij voorkeur bekabeld, geen wifi). Bij 1 pc zonder kassa's volstaat `127.0.0.1` in de Desktop.
   - Rechtermuisklik op het netwerkicoon > **Netwerk- en internetinstellingen openen** > **Netwerkcentrum** > klik op de verbinding > **Details...** (huidige waarden noteren of screenshot nemen: IP-adres, subnetmasker, standaardgateway, DNS-servers).
   - **Eigenschappen** > dubbelklik **Internet Protocol versie 4 (TCP/IPv4)** > **Het volgende IP-adres gebruiken** en vul alle velden in.
   - Vrij adres controleren: `ping <adres>` in de opdrachtprompt; geen antwoord = vrij.
   - Een tikfout hier betekent dat je de verbinding (remote sessie) kwijt bent; de klant moet het dan terug op automatisch zetten.
5. **Firewall:** inkomende TCP-poorten `5000-5005, 5100-5130` openen, regelnaam **"Jamadata Server"** (zie hieronder). Bij een hardware-firewall dezelfde poorten naar de server openzetten. Geen andere software op deze poorten.
6. **Printers:** alle printers die in Jamadata gebruikt worden op de centrale computer installeren met de correcte driver; de printernaam moet duidelijk naar merk en type verwijzen. Netwerkprinters toevoegen via **TCP/IP-poort (IP-adres)**, niet via WSD (zie `faq-server-en-algemeen.md`).
7. **USB-stick:** lege stick van min. 32 GB achteraan in de centrale computer (liefst letter S:). NAS mag ook.
8. Bij overname van een oud systeem: back-up maken van de mappen `\jamadata`, `\kassa` (indien Jamadata-kassa's) en `\ftkopie` (indien facturen herafgedrukt worden). `\ftkopie` kopiëren kan zeer lang duren: apart kopiëren.

### Firewallregel "Jamadata Server" aanmaken (Windows)
1. Start > typ "Windows Defender" > open **Windows Defender Firewall met geavanceerde beveiliging**. Alternatief: rechtermuisklik netwerkicoon > Netwerk- en internetinstellingen > **Windows Firewall** > **Geavanceerde instellingen** > Ja. (Het venster verstopt zich soms achter andere vensters.)
2. Klik op **Regels voor binnenkomende verbindingen**. Staat "Jamadata Server" niet in de lijst: rechtermuisklik > **Nieuwe regel**.
3. Kies **Poort** > Volgende.
4. **Specifieke lokale poorten:** `5000-5005, 5100-5130` (kopieer en plak om tikfouten te vermijden) > Volgende.
5. **De verbinding toestaan** > Volgende.
6. Laat alle profielen (domein, privé, openbaar) aangevinkt > Volgende.
7. Naam: **Jamadata Server** > Voltooien.

Uitgaande regels zijn normaal niet nodig (uitgaand staat standaard open). Bij klanten met kassa's wordt aangeraden de regel te splitsen zodat 5000-5005 enkel openstaat voor de kassa's: zie `server-jms-storingen.md`.

## 3. Installatiedraaiboek Jamadata Server (Windows)

### 3.1 Voorbereiding door de programmeur (intern, bij conversie van een oud systeem)
- `Struct.cnf`, `jamosys.cnf` en `code.ovl` aanpassen.
- Installatiemap voor de klant klaarmaken op de interne installatieschijf (kopie van de template), `old2new.bat` aanpassen, software in `prog` zetten.

### 3.2 Eigenlijke installatie op de server
1. Aanmelden op de server van de klant (LogMeIn, bij voorkeur met onbeheerde toegang).
2. Via bestandsoverdracht de voorbereide `Jamadata`-map naar `J:\` overzetten.
3. **`J:\jamadata\prog\JMS.ini`** aanpassen: `[JamaSettings]` (serienummer, wachtwoord, `PostCount`, `SerialNr_Post-00x`), `[CopySettings]` (`CopyPath=S:\jamadata\Copy`, `CopyJamaSubDirs=PROG|KASSA|JamaPDA|FTKOPIE`), `[DataBaseSettings]` (`StdDossier1=001` ...), `[MailSettings]`. Zie `server-jms-overzicht-en-vereisten.md`.
4. Vanuit `\jamadata\prog\tools` de runtimes installeren:
   - Microsoft .NET Framework 4 (en 4.5) – op recente Windows-versies zit dit al in het besturingssysteem;
   - Visual C++ 2010 Redistributable (x86);
   - Visual C++ 2017 runtime (x86) – nieuwe versie; in de praktijk worden de oude én de nieuwe uitgevoerd. Meldt de installer dat de runtime al aanwezig is: sluiten, niet "repareren".
5. Enkel bij conversie: opdrachtprompt **als administrator**, ga in de map `jamadata` staan en voer `old2new` uit (converteert de data).
6. **JMS installeren:** `\jamadata\prog\tools\JMS-inst` uitvoeren, of de installer downloaden via `jmsn.prsw.be`. **Altijd "Als administrator uitvoeren".** Kies in de wizard de **juiste schijf** (J:, niet de standaard C:). De melding dat de map al bestaat is normaal en moet bevestigd worden; krijg je die melding niet, dan installeer je op de verkeerde plaats.
7. Eventueel ook JMD installeren op de server (`jmdn.prsw.be`): IP-adres server `127.0.0.1` (blijft werken als het IP-adres ooit wijzigt), **Post-01**, standaard postlicentie.
8. Enkel bij Windows XP: ESENT-bestanden van `\jamadata\prog\tools\xp` naar `\jamadata\prog` kopiëren. Bij **Light**: `administrator.reg` aanpassen naar de juiste user/wachtwoord/domein en uitvoeren.
9. `\jamadata\jamadata\jamapda` verhuizen naar `\jamadata\jamapda` (indien van toepassing).
10. **JMS één keer manueel starten ter controle** vanuit `\jamadata\prog\` (`JMS.exe`, gewoon uitvoeren). Laadt de database zonder fouten, sluit het venster dan weer.
11. **JMT installeren:** ga naar `\jamadata\JMT\Bin`, selecteer `jmt.exe` en start het als administrator (linker-Shift + linker-Ctrl ingedrukt houden terwijl je start, of selecteren en **Ctrl+Shift+Enter**, of rechtermuisklik > Als administrator uitvoeren). Kies dan:
    - **Server-versie:** bovenste blok "JMT as Windows-Service" > **INSTALL**; kijk of de processen starten (status running).
    - **Light-versie (of soms XP):** middelste blok "JMT OnLogon (Manual Mode)" > **INSTALL**; kijk of de snelkoppelingen gemaakt worden en de JMS start. (Snelkoppeling `\jamadata\JMT\Bin\jmt.exe --start` voorzien bij "Opstarten", voor alle gebruikers.)
    - **Mono-versie:** onderste blok "JMT MONO" > **INSTALL**; kijk of de JMD opstart met database.
    - Welke versie de klant heeft, zie je in de SVC (kolom S) of aan hoe de JMT op de oude server geïnstalleerd stond.
12. `jmdn.prsw.be` uitvoeren op alle posten die moeten kunnen opstarten.
13. Controleren of de grootte van de gebruikte bestanden dezelfde is als voordien; fouten- en controlelijst nakijken.
14. Diverse artikelen 0 %, 6 %, 12 %, 21 % en leeggoed bijmaken (bv. in groep 98 en 99) en invullen op "4+".
15. Een factuur oproepen om te zien of de instellingen (`ftkopie`) in orde zijn.
16. In Verkenner in `FtKopie` het **hoogste factuurnummer** opzoeken.
17. De facturen inlezen **jaar per jaar** via punt **8.H.D**: laatste 6 jaren voor de standaardversie, laatste 2 jaren voor Light; beginfactuur 1 tot hoogste + 100.
18. Alle oude Jamadata-iconen verwijderen.
19. Printerinstellingen doen in Jamadata (**+ . J . 1** afdrukposten; via het vergrootglas kies je een printer die op de server geïnstalleerd is) en testen.
20. Brieven meegeven van de geïnstalleerde opties (`*.jam`): `Brief00.jam` = F12-info, `Brief01.jam` = verhuurmodule, `Brief02.jam` = offertebeheer, `Brief03.jam` = variabele rappels.
21. Kassa's eventueel al op het nieuwe systeem zetten (`kasmenu.dat` en `jama.bat` aanpassen, nieuwe `UCWIN.exe` op de kassa) en testen. In `jama.bat` moet `set JMS=<IP-adres of computernaam van de JMS-server>` staan. In `kasmenu.dat` verwijzen de punten "Dagelijkse TRANSFER met de HOOFDCOMPUTER [JMS]" (`UCWIN -fUCKASDAY.jam -n%JAMA-KASSA% -ekasmenub.bat -t%JMS%:5000`) en "Updaten ALLE bestanden en programma's van de HOOFDCOMPUTER [JMS]" (`UCWIN -fUCKASUPD.jam ... -t%JMS%:5000`) naar de server op poort 5000. Voor 64-bit en kassa's op afstand: `sendkas` aanpassen en op het bureaublad zetten. (Details: kassadocumentatie.)
22. Bij PDA's: Windows Mobile Apparaatcentrum installeren, `jamaspda` op het bureaublad zetten en testen; voor PDA's op afstand `sendpda` aanpassen en op het bureaublad zetten. (Details: PDA-documentatie.)
23. (Automatisch) mailen testen (facturen, prijslijsten of rappels).
24. Het interne adresbestand bijwerken (installatiedatum, drive, Windows-versie, ...).

### 3.3 Veelvoorkomende problemen tijdens de installatie

| Probleem | Oorzaak / oplossing |
|---|---|
| **JMR komt niet online op de SVC** (vooral Windows 10 of domeincomputers) | De Windows-gebruiker `jamadataserver` is niet automatisch aangemaakt. Maak hem manueel aan, meld aan met die gebruiker en voer `JMS-inst` opnieuw uit onder die gebruiker. Daarna komt de JMR online en staan er geen fouten meer in het logboek. |
| **JMT opent niet of INSTALL start de processen niet** (JMT en JMR draaien, JMS niet) | De aangemelde Windows-gebruiker heeft onvoldoende rechten. Maak de gebruiker `jamadataserver` zichtbaar op het aanmeldscherm via het registerbestand in `\jamadata\prog\tools` ("Jamadata server user unhide"), meld aan als `jamadataserver` (wachtwoord: zie interne bron), installeer de **JMS opnieuw als administrator** (JMT eerst sluiten) en doe daarna opnieuw **INSTALL** in de JMT. Controleer in Taakbeheer > Details dat `JMS` en de `JMC`'s draaien. Meld daarna af en laat de klant met zijn eigen gebruiker aanmelden. (uit opleiding, 11/06/2026) |
| JMS per ongeluk op C: geïnstalleerd | Installer opnieuw uitvoeren als administrator en de juiste schijf kiezen; controleer dat de service daarna naar de juiste map verwijst en herstart. (uit opleiding, 11/06/2026) |
| **`JET_errSectorSizeNotSupported`** ("The physical sector size reported by the disk subsystem, is unsupported by ESE for a specific file type") bij nieuwe pc's (Windows 11, NVMe) | Registerinstelling zetten in PowerShell als administrator en daarna herstarten: `New-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Services\stornvme\Parameters\Device" -Name "ForcedPhysicalSectorSizeInBytes" -PropertyType MultiString -Force -Value "* 4095"` |
| Dummy-bestanden in de map `FAS` na overgang van Windows 7 naar Windows 10 | Bepaalde DLL's moeten naar `\jamadata\prog` gekopieerd worden (welke precies: niet uitleesbaar in de bron – te verifiëren). |
| Partitie kan niet bijgemaakt/verkleind worden | Gebruik een partitietool (bv. MiniTool Partition Wizard). |
| Jamadata Desktop start niet op de server na wisselen van Windows-gebruiker | De post (meestal Post 1) staat nog open onder de andere gebruiker. Sluit de Desktop daar, of gebruik tijdelijk een ander postnummer. |
| Remote sessie kwijt na herstart onder een andere gebruiker | TeamViewer/LogMeIn start pas wanneer de gebruiker aangemeld is; laat de klant de tool opnieuw openen (`help.prsw.be`). |

### 3.4 Afsluiten
- Printers instellen en laten testen; back-up controleren (zie `backup-en-herstel.md`: verschijnen de mappen `jamadata\Copy\Fas` op de back-upschijf?).
- Bel de klant: laat een bon en een factuur maken, een lijst afdrukken, eventueel kassa doorsturen en PDA testen.
- Registreer de gepresteerde tijd (servicecall): een installatie/migratie wordt aan de klant gefactureerd.

## Bronnen
- Jamadrink: "Installatie jamadata Dektop 2.0.docx"
- Jamadrink: "Installatiedraaiboek Jamadata 1.docx" (de .doc is een dubbel)
- Onenote: "Jamadata Server.pdf" (zelfde draaiboek, aangevuld; volledigste exemplaar)
- FAQ: "Opleiding Helpdesk Jamadata.docx" (hoofdstuk installatie nieuwe server)
- FAQ / Jamadrink: "FAQ Jamadata SERVER.docx"
- Onenote/FAQ: "Support.pdf"
- Transcripties opleidingen: "[klant]_Migratie_20260601_162649.txt", "[klant] Migratie Server-20260611_132355-Opname van vergadering.txt"
