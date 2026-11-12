# Jamadata Server (JMS): monitoring (SVC), foutmeldingen, crashes en herstarten

Gebruik dit document voor: het lezen van de monitoringwebsite SVC (heartbeat, back-up, fouten per klant), het interpreteren van JMS/JMT-foutmeldingen, het oplossen van een crashende JMS (firewallregel splitsen, poortconflicten, virusscanner), het manueel herstarten van de JMS via de JMT, en het klaarzetten/installeren van updates.

## 1. Monitoring via de SVC (`svc.jamadata360.be`)

Interne website (login: zie interne bron) met één lijn per klantinstallatie. Ze beantwoordt de vragen: krijgt de klant veel fouten? Zit de back-upstick erin? Heeft de klant contact met ons / internet? Is de back-up gelukt?

| Kolom | Betekenis |
|---|---|
| **CUS** | 3-letterige klantcode. Klik erop voor het detailscherm van de klant. |
| **S** | Versie van de klant: Light, Mono of Server. |
| **JMS** | Versie van de **database** (niet van de programma's). Sorteer op deze kolom om de laatste versie te zien. |
| **LastHeartBeat** | De JMR (reporter) meldt zich voortdurend bij Jamadata; dit is het laatste moment waarop er bij de klant met het pakket gewerkt werd. |
| **BackupUpdated** | Online back-up. "No backup" = klant heeft geen online back-up bij Jamadata. Een datum = laatste online back-up. **Datum in rood** = klant heeft online back-up, maar ze komt niet door. |
| **DailyBackup** | Dagelijkse back-up (betekenis in de bron niet toegelicht; vermoedelijk de dagelijkse gecontroleerde kopie van de online back-up – te verifiëren). |
| **Err** | Aantal fouten. Sorteer hierop om klanten met fouten te zien; dubbelklik op de lijn voor het detail. |
| **dE** | Delta error. |
| **USB** | Zit de back-upstick erin of niet (vinkje uit en rood = stick ontbreekt of is defect). |
| **LastJMRContact** | Laatste contact van de JMR: zodra de computer van de klant internet heeft, verschijnt dit. |

In het detailscherm kan de JMS ook op afstand herstart worden.

## 2. Foutmeldingen en oplossingen

| Melding / symptoom | Oorzaak | Oplossing |
|---|---|---|
| Kolom **USB** uit/rood | USB-stick of ander back-upmedium niet aanwezig of defect. | Stick terug insteken, stationsletter controleren (zie `it-remote-support-vpn-shares.md` §9), anders stick vernieuwen/formatteren of ander medium gebruiken. Zie de waarschuwing over formatteren in `backup-en-herstel.md`. |
| `#0117 *** ERROR : Cannot copy J:\jamadata\Spool\Temp\snapshot-fas-....zip to s:\jamadata\Copy\snapshot-fas-....zip, LastError=112` | **LastError=112** = geen schijfruimte meer op het back-upmedium. | Grotere/nieuwe stick of partitie vergroten; oude overbodige bestanden op het medium opruimen. |
| `[JMT] Exit of JMS and restarted process` (zonder UC-fouten ervoor) | Probleem met de online back-up of met de USB-stick. | USB-stick formatteren of vervangen, of (intern) de back-upmap van de klant op de Jamadata-server hernoemen zodat de online back-up opnieuw start. |
| `#0058 *** ERROR : UC-Server = Status : -1. Expecting CMD: 1 but received CMD: 0` (of `CMD:47`), gevolgd door `#0065 UCServer watchdog timed out, so killed and restarted` en `[JMT] Exit of JMS and restarted process`, soms ± elke 30 minuten | Ander verkeer komt binnen op de Jamadata-poorten (vooral 5000-5005): VPN, cloud-back-up, camera's, updates van virusscanners, poortscans. In de JMS-log zie je dan bv. `Connected to KeyConenKassa = webman/pingpong.cgi?action=cors`. | Zorg dat geen andere software poorten 5000-5005 gebruikt (voorbeeld: een cloud-back-upprogramma dat poort 5000 gebruikte, werd door de leverancier naar poort 7000 verplaatst). Firewallregel splitsen en beperken tot de kassa's (§3). Bij enkele klanten loste het **verwijderen van Norton 360** het probleem op (oorzaak niet uitgezocht). |
| `#0056 *** ERROR : Upload failed: Jama360 did not confirm the new SpilDateTime` | Online back-up/upload naar Jama360 wordt niet bevestigd. | Zie "geen heartbeat of back-up" hieronder; controleer internet/firewall (poort 80, IPS). |
| **Er komt geen heartbeat of back-up binnen** | Vastgelopen upload of volgelopen mappen. | Map `Dump` leegmaken en de JMS herstarten. Helpt dat niet: map `Fas\log` leegmaken en de JMS herstarten (enkel door een bevoegde medewerker; `Fas\log` bevat onverwerkte transacties). Bij één klant werden tegelijk oude dossiers, mail en ftkopie opzij gezet. Ook map `ToGeel` controleren (stond ooit 30 GB in). |
| **Back-up of logging komt niet binnen op de SVC** | Firewall/IPS van de klant blokkeert het verkeer op uitgaande poort 80 (geen echt HTTP-verkeer, hoge trafiek). | IPS afzetten voor dit verkeer, niet-HTTP-verkeer via poort 80 toelaten of alle filters naar het Jamadata-adres uitschakelen (adres: zie interne bron). |
| `[JMT] Exit of JMH for Post-10 [...] and restarted process`, `Watchdog for JMH-10 [...], killed and restarted !`, `[JMT] Exit of JMH but could not locate process !!!` | Probleem met het oversturen van een bestand van de server naar die werkpost; meestal een manuele back-up (of ander bestand) die te groot is (meestal > 2,5 GB), vaak op een post op afstand. | Het bestand staat in `\jamadata\spool\toclient\post-x\`. Verwijder het; de fout is dan weg. Manuele back-ups en zeer grote afdrukken niet op afstand starten. |
| `[JMT] Exit of JMC for Screen-n of Post-nn` en `Exit of JMH for Post-nn`, bij installaties met **10 of meer werkposten** | Beperking van de **Desktop Heap size** voor interactieve services in Windows. | Registerwaarde `HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\SubSystems\Windows`: het **derde getal** in die waarde verhogen (de bron toont dit enkel als schermafdruk; in Windows is dit normaal de reeks `SharedSection=x,y,z` – te verifiëren) (standaard 512 of 768; in de praktijk naar 1024, bij grote klanten 2048). Daarna de computer herstarten. Niet zomaar veel hoger zetten: kan andere vervelende gevolgen hebben. |
| **Server herstart niet meer** (JMS blijft hangen bij herstart) | Meestal komt de online back-up niet tijdig binnen (te veel data). | Enkele oude dossiers opzij zetten (bv. naar `fas_old`). Zodra de back-up binnen is, herstart hij weer. |
| SVC-fout **"Out of memory"** | – | De JMS herstarten, via de SVC of op de server zelf. |
| `#0001 *** ERROR : JetCall(411,...) = JET_errSectorSizeNotSupported` | Sectorgrootte van nieuwe (NVMe-)schijven wordt niet ondersteund door ESE. | Registerinstelling `ForcedPhysicalSectorSizeInBytes`, zie `installatie-desktop-en-draaiboek.md` §3.3. |
| **JMR komt niet online op de SVC** | Gebruiker `jamadataserver` niet aangemaakt (Windows 10 / domein). | Zie `installatie-desktop-en-draaiboek.md` §3.3. |
| In het pakket: **"FOUT 01 bestand niet gevonden op deze computer"** | Hoofdmenu punt **6** toont per bestand de status. | Staat er **één lijn** op "FOUT": de klant heeft waarschijnlijk per ongeluk een parameter aangepast; controleer via **+ > 2** of alle parameters juist staan. Staan **alle lijnen** op "FOUT": de JMS moet herstart worden, best via de JMT (§4). |

## 3. JMS crasht geregeld: firewallregel splitsen

**Vaststelling:** staat de firewallregel voor poorten 5000-5005 volledig open, dan crasht de JMS bij heel wat klanten geregeld, omdat een andere toepassing (bv. back-upsoftware) dezelfde poort aanspreekt. De regel voor 5000-5005 hoort enkel voor de **kassa's** te gelden.

### 3.1 Regel splitsen
1. Open de Windows-firewall (geavanceerde instellingen) > Regels voor binnenkomende verbindingen.
2. Rechtermuisklik op de regel **Jamadata Server** > Eigenschappen > **Protocollen en poorten**: haal `5000-5005` eruit (laat `5100-5130` staan).
3. Maak een nieuwe regel, identiek aan de oude, maar enkel voor poorten **5000-5005**.
4. Resultaat: één regel voor 5100-5130 (werkposten) en een aparte regel voor 5000-5005 (kassa's).

### 3.2 Kassa's met vast IP-adres
1. Stel op de kassa('s) een vast IP-adres in **buiten** de DHCP-range.
2. Rechtermuisklik op de nieuwe regel 5000-5005 > Eigenschappen > tabblad **Bereik** > bij **Externe IP-adressen** de adressen van de kassa('s) ingeven.
3. Test: kan de kassa nog doorsturen naar de hoofdcomputer, en raakt ze nog in het nieuwe facturatiescherm?

### 3.3 Kassa's op DHCP
Wil je de kassa niet op een vast IP zetten, vraag dan bij welke provider de klant zit en geef bij **Externe IP-adressen** de DHCP-range in:
- Telenet: `192.168.X.100-254`
- Proximus: `192.168.X.2-63`

Zo kunnen de kassa's verbinden met 5000-5005, maar blijft het geblokkeerd voor andere toestellen zoals de modem. Ook hier testen (doorsturen + nieuw facturatiescherm).

### 3.4 Kassa kan niet doorsturen: "Bent u verbonden met het internet? Retry? (Y/N)"
Mogelijke oorzaak: het netwerkprofiel van de server staat op **Publiek/Openbaar**, waardoor de firewallregel niet geldt. Zet het netwerkprofiel op **Privé** (via de Windows-netwerkinstellingen of via PowerShell; exacte stappen staan in de bron enkel als schermafdruk).

## 4. JMS herstarten

### 4.1 Gewone herstart
- Op de server staat op het bureaublad een icoon **"Herstarten Jamadata Server"**: dubbelklikken en bevestigen met Ja (uit opleiding, 11/06/2026).
- Light: dubbelklik op het Jamadata Server-icoon toont het databasescherm en herstart de database.
- Via de SVC (detailscherm van de klant).
- Controleer eerst of er nog iemand werkt: hoofdmenu **+ > J > T** (toont de actieve gebruikers; vernieuwen met **F7**). Gebeurt er niets bij **T**, dan is er niemand meer bezig. Een herstart verbreekt alle sessies; niet-bewaard werk gaat verloren.

### 4.2 JMS herstarten via de JMT (grondige procedure)
Gebruik dit wanneer het pakket niet meer start of alle bestanden op "FOUT" staan.
1. Start `\jamadata\JMT\Bin\jmt.exe` **als administrator** (selecteer het bestand, houd Shift + Ctrl ingedrukt en druk Enter).
2. **STOP** (JMT stoppen).
3. **REMOVE** (JMT verwijderen als service; even wachten).
4. Start de **JMS manueel** (`\jamadata\prog\JMS.exe`). Lukt dit zonder fouten, sluit het venster dan.
5. Start de JMS **nogmaals manueel**.
6. Start de **JMC** (een werkscherm; volgens de opleiding van 11/06/2026 rechts onderaan in het JMS-venster) en test of het pakket weer werkt (bv. hoofdmenu punt 6).
7. Stop de JMS (venster sluiten).
8. **JMT terug installeren** (INSTALL in het juiste blok: Server = service, Light = OnLogon, Mono).
9. **JMT starten** en controleren dat de processen draaien.

De knop **JMS** in het JMT-venster start en stopt de database; na een nette start/stop is `\jamadata\Fas\log` leeg.

### 4.3 Na een stroomonderbreking (voorlopig kennisartikel KA-017, niet volledig gevalideerd)
1. Noteer het tijdstip, welke toestellen herstart zijn en of één of meerdere werkposten getroffen zijn.
2. Kan de gebruiker nog andere netwerkbronnen/internet bereiken?
3. Draaien de Jamadata-services op de server en is de server bereikbaar? (Een draaiende service sluit een netwerkprobleem niet uit.)
4. Lukt remote support niet, laat dan eerst de lokale IT-partner het netwerk nakijken.
5. Een gewijzigd IP-adres na een routerreset is een mogelijke oorzaak (hypothese): laat de IP-/gateway-/DHCP-configuratie vergelijken met de gedocumenteerde configuratie; wijzig geen IP-adressen op basis van een vermoeden.
6. Controleer ook verbroken netwerkschijven (bv. T-schijf van de flessenautomaat, zie `it-remote-support-vpn-shares.md` §8).

## 5. Updates

### 5.1 Update installeren bij de klant
- Wanneer een update klaarstaat, krijgt de klant bij het opstarten een **geel scherm**; van daaruit kan de update geïnstalleerd worden.
- Later kan het ook vanuit het hoofdmenu: **tandwieltjes** (masterfuncties) > **5 – Controleer op nieuwe update**.
- Na de update ook de viewer bijwerken: Jamadata Desktop > **Configuratie** > **Nieuwe versie installeren**.
- Werkt de klant met een kassa, dan zit de extra kassa-update mee in de gewone update.
- Een update kan actieve gebruikers ontkoppelen: controleer via **+ > J > T** (F7 vernieuwen) of er nog iemand werkt en spreek het moment af met de klant (voorlopig kennisartikel KA-003).

### 5.2 Update klaarzetten / opnieuw pushen (intern)
1. Zet de bijgewerkte bestanden klaar in de `ToKlt`-map van de juiste klant op de interne update-schijf.
2. Open de DOS-box op de interne 32-bit machine en ga naar die klantmap.
3. Geef het commando `msg` in en typ een korte beschrijving van wat er aangepast is; sluit af met **Ctrl+X** en **Enter**.
4. Geef het commando `go` om de update te pushen.
5. Werkt `go` niet: wees eerst zeker dat er bij de klant niemand meer in Jamadata werkt en geef dan `go x`; dit **forceert** de update.

Een aangepaste factuurlay-out (PNG + Word-bestand) wordt op dezelfde manier naar de klant gestuurd (details lay-out: zie lay-outdocumentatie).

### 5.3 Mededelingen in het pakket
**+ (Aanpassen systeemparameters) > B (Bekijken/afdrukken brieven)** geeft een overzicht van de boodschappen (updateberichten) in JMD; met **F8** op een boodschap lees je de inhoud.

## Bronnen
- FAQ / Jamadrink: "FAQ Jamadata SERVER.docx" (de .doc en het exemplaar in Jamadrink zijn dubbels)
- Onenote: "Jamadata Server.pdf" (volledigste versie van dezelfde FAQ, met Norton-vermelding)
- Jamadrink: "HOWTO - Problemen met crashen JMS.docx" (de .pdf is een dubbel)
- FAQ: "Opleiding Helpdesk Jamadata.docx" (SVC-kolommen)
- Jamadrink: "Jamadata FAQ's.pdf" (JMS herstarten via de JMT, FOUT 01, kassa kan niet doorsturen)
- Onenote: "Support.pdf" (volledigste exemplaar; FAQ/"Support.pdf" is een oudere export): updates, Out of memory, DHCP-ranges
- FAQ/Kennisartikelen: "KA-003_Serverupdates.md", "KA-017_Stroomonderbreking_en_verbindingsproblemen.md" (gedeeltelijk gevalideerd)
- Transcripties opleidingen: "Dranken BAETS Migratie Server-20260611...txt"
