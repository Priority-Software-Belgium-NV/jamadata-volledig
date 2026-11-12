# Jamadata Server (JMS): overzicht, onderdelen, licenties, mappenstructuur en systeemvereisten

Gebruik dit document voor: begrijpen hoe de Jamadata Server werkt (architectuur, processen JMS/JMD/JMT/JMR/JMH/JMC), welke licentieversies bestaan (Mono, Light, Server/Standaard), wat er in de map `J:\jamadata` staat, hoe `JMS.ini` is opgebouwd, welke poorten gebruikt worden en welke hardware/Windows-versie nodig is. Ook de veelgestelde vragen van klanten en IT-partners over de centrale computer staan hier.

## 1. Wat is de Jamadata Server?

- De Jamadata Server is het centrale pakket achter de Jamadata-werkschermen: een snelle database (omvang afhankelijk van de versie) plus modules voor het aanmaken van Excel-werkbladen, PDF-documenten en e-mails.
- De server doet **alle verwerking** voor de werkstations, vergelijkbaar met een Microsoft Terminal Server: de programma's draaien op de centrale computer, het werkstation toont enkel het resultaat. Daardoor werken alle gebruikers even snel als de server zelf; de snelheid van de centrale computer bepaalt het gebruikscomfort. Een werkpost van 5 jaar oud met 4 GB RAM en Windows 10 volstaat.
- De database is de **ESENT-database van Microsoft** (dezelfde technologie als Exchange en Active Directory). Daarom zijn snelle schijven (SSD) belangrijk, vooral bij het inboeken van data (bons, facturen, kassaverkopen): op SSD 5 à 10 keer sneller. Lezen (statistieken, grafieken) gaat op een gewone schijf met voldoende geheugen bijna even snel.
- Er is geen Windows Server, SQL Server of Office nodig. Voor Excel-export volstaat een gratis viewer of Google Apps.
- De **Jamadata Desktop (JMD)** is het "browser"-programma (viewer) op elke werkpost; er is dus altijd ergens in het netwerk (of op afstand) een Jamadata Server nodig die de database beheert.

### Extra mogelijkheden van de serverversie (gebruikerskant)
- Tot 4 werkschermen (sessies) tegelijk in Jamadata Desktop, instelbaar via menu **Scherm** links bovenaan; wisselen zonder gegevens te verliezen.
- Zoeken in volledige fiches (stuk van naam, straat, btw-nummer) via het zoek-icoon.
- Wereldbol-icoon naast het adres opent Google Maps.
- Rechtermuisklik: kalender op datumvelden, opzoeken van btw- of telefoonnummer, e-mail sturen/kopiëren op een e-mailadres, **"Schermafdruk naar PDF-document"** (meerdere schermen verzamelen) en daarna **"PDF-document aanmaken en openen"**.
- Kopiëren en plakken in aanpasbare velden, ook van/naar andere programma's.
- Mail-icoon: opent een e-mail met de juiste bijlage(n).
- Klant **markeren** (uitroepteken achter de naam: naam wordt rood op kassa, facturatie en bons; factureren blijft mogelijk) of fiche **blokkeren** (rood slotje achter het codenummer: scherm wordt zwart, fiche verschijnt niet meer op lijsten en kan niet meer gebruikt worden op bons/facturen, historiek blijft).
- Kassa: lege blokjes en menublokjes in een andere kleur (punt V.2.2); bij het uitschrijven van prijzen naar de kassa (punt V.2.K) gaat de eerstvolgende prijswijziging of promo automatisch mee.

## 2. Onderdelen en processen

| Afkorting | Wat | Opmerkingen |
|---|---|---|
| **JMS** | Jamadata Server: het databaseproces (`\jamadata\prog\JMS.exe`) | Kan ter controle manueel gestart worden; schrijft per dag één logbestand. Instellingen in `\jamadata\prog\JMS.ini`. |
| **JMD** | Jamadata Desktop: viewer op de werkpost | Installer via `jmdn.prsw.be`. Verbindt met IP-adres van de server, postnummer en post-licentie. |
| **JMT** | Beheer-/bewakingsprogramma (`\jamadata\JMT\Bin\jmt.exe`) | Installeert en start de server als Windows-service (Server), bij aanmelden (Light) of als Mono; herstart gecrashte processen (meldingen "[JMT] Exit of ... and restarted process"). Knoppen STOP / REMOVE / INSTALL / JMS. |
| **JMR** | Windows-service "reporter" | Maakt voortdurend verbinding met de servicecomputer van Jamadata (SVC): heartbeat, foutmeldingen, controle op updates. Zichtbaar in `services.msc`. |
| **JMH** | Proces per werkpost (post) | Foutmeldingen in de vorm "Exit of JMH for Post-10 [...]". |
| **JMC** | Proces per werkscherm van een post | Foutmeldingen in de vorm "Exit of JMC for Screen-2 of Post-13". Elke open sessie in Jamadata Desktop heeft een JMC. |
| **UC-Server** | Communicatieserver in de JMS voor kassa's (UCWIN) op poort 5000 e.v. | Foutmeldingen "#0058 UC-Server = Status : -1 ..." wijzen op vreemd verkeer op de Jamadata-poorten. |
| **SVC** | Servicecomputer / monitoringwebsite van Jamadata (`svc.jamadata360.be`) | Overzicht per klant van heartbeat, back-up en fouten. Zie `server-jms-storingen.md`. |
| **Jama360** | Onderhoudscontract met o.a. online back-up en monitoring | Vereist permanente internetverbinding. |
| **ComfortLink** | Werken op afstand via de verbindingsserver van Jamadata | Uitgaande poort 5006. Zie `it-remote-support-vpn-shares.md`. |
| **Omnis-service** | Aparte service voor de nieuwe PDA's (JamaMobi) in `\jamadata\omnis`, poort 60000 | Enkel bij klanten met PDA's; zie PDA-documentatie en `installatie-migratie-naar-nieuwe-server.md`. |

Controleren of alles draait: Taakbeheer > Details: `JMT`, `JMR`, `JMS` en per open scherm een `JMC` moeten aanwezig zijn. In `services.msc` kan je zien of de JMT-/JMR-service gestart is en ze eventueel met de hand starten.

## 3. Licentieversies

| | MONO | LIGHT | SERVER (Standaard) |
|---|---|---|---|
| Gebruikers | 1 gebruiker op 1 computer | Meerdere gebruikers | Meerdere gebruikers (meer dan 5 gebruikers hebben meestal Server wegens de datahoeveelheid) |
| Database | max. 60.000 records per bestand | max. 120.000 records per bestand | in principe onbeperkt (max. 2.000.000) |
| Opstarten database | Dubbelklik op het Jamadata Desktop-icoon, of herstart van de pc | **User mode**: start zodra de gebruiker op de hoofdcomputer aangemeld is; stopt bij afmelden. Dubbelklik op het Jamadata Server-icoon toont het databasescherm en herstart de database | **Service mode**: start zodra de computer opstart, niemand hoeft aangemeld te zijn (er wordt een Windows-gebruiker `JamadataServer` aangemaakt). User mode is ook mogelijk als de klant de pc 's avonds afzet |
| Back-up | Manuele kopie naar stick en/of online back-up | Automatische kopie naar stick | Automatische kopie naar stick + automatische online back-up (Jama360) |
| Andere | Beperkingen in boekhouding en historieken; geen automatische beveiliging | Geen mailserver; minder opties dan Server | Mogelijkheid tot mailserver (automatisch mailen) |
| JMT-installatie | "JMT MONO" | "JMT OnLogon (Manual Mode)" | "JMT as Windows-Service" |

Bij een Light-installatie moet de gebruiker dus aangemeld zijn op de hoofdcomputer voor de anderen kunnen werken.

**Posten en licenties:** in `JMS.ini` staat `PostCount=` (aantal posten) en per post een `SerialNr_Post-00x=`. Post-001 is normaal de server; de laatste post is steeds een DEMO-post. Het postnummer van een werkpost vind je in Jamadata via **+ (Aanpassen parameters) > J (JMS-instellingen) > 4 (Instellingen werkposten)**.

## 4. Mappenstructuur `J:\jamadata`

De map `jamadata` staat bij de klant meestal op de J-schijf (soms een andere letter, bv. D: als de IT-partner dat zo koos; in cloudomgevingen bv. E:).

| Map | Inhoud / gebruik |
|---|---|
| `Batch` | Commando's die bij een update uitgevoerd worden. |
| `Copy` | Staat normaal **op de stick** (`S:\jamadata\Copy`): automatische back-up (schaduwkopie). |
| `CopyAlt` | Alternatieve kopie op de dataschijf zelf wanneer de stick/back-upschijf er niet is. |
| `Dump` | Bestanden waarvan een back-up gemaakt is naar de server van Jamadata (online back-up). |
| `Fas` | De databasebestanden (o.a. demobestanden `ART.DEM`, `KLT.DEM`, `LEV.DEM`). `Fas\log` bevat nog niet verwerkte transacties en moet leeg zijn na een nette stop. |
| `Ftkopie` | Kopie van de originele facturen, zodat steeds een afdruk van de originele factuur kan geleverd worden. |
| `Imap` | Mails die nog door een verantwoordelijke gecontroleerd moeten worden (wordt (nog) niet gebruikt). |
| `JamaPDA` | Uitwisselmap voor de (oude) PDA's; wordt gesynchroniseerd met het pakket. Bevat ook `sendpda` (batch, PDA's op afstand). |
| `JMT` | Tools, o.a. `JMT\Bin\jmt.exe`. |
| `Kassa` | Uitwisseling met de kassa's (offline toestellen). Bevat bestanden die **naar** de kassa gaan (bv. `KasPlu` met nieuwe artikelen, aangemaakt via V.2.K "Beheer Key-Conen kassa": uitschrijven blokjes, gegevens voor mobiele stockcontrole/PDA, DIGI ESL) en per kassa een map `KASSA-01`, `KASSA-02`, ... met `kaslog.dat`, `kaslog.001` en de verkoopbestanden per maand (inlezen verkopen / kasontvangsten inboeken). Bevat ook `sendkas` (batch, kassa's op afstand). |
| `Lastgood` | Laatste goede updateversie van de mappen `JMT` en `PROG`. |
| `Log` | Logging van alles rond de database (update, start, stop, ...). JMS: één bestand per dag; ook JMH-logs. |
| `Mail` | Automatisch verstuurde mails: `Sent` (verzonden), `Failed` (mislukt; mailbestanden kunnen van `Failed` naar `Outbox` verplaatst worden om opnieuw te verzenden), `Outbox`, `Templates` (per documenttype en taal, bv. `FACT1F`, `FACT1N`), `Tocheck` (niet gebruikt). |
| `Offerte` | Offertes uit Jamadrink, in Excel. |
| `Omnis` | (indien PDA's) Omnis-service voor JamaMobi. |
| `Pdf` | Bewaarde PDF-documenten (bv. afsluitdocumenten). |
| `Prog` | Programma's: schermen, brieven, lay-outs, ... en **`JMS.ini`**. Submap `Prog\Tools` met installers (o.a. .NET, VC++-runtimes, `JMS-inst`). |
| `Restore` | **Niet gebruiken tenzij bewust**: dient om een back-up terug te zetten (zie `backup-en-herstel.md`). |
| `Share` | Gedeelde map over het netwerk (Jamadata Share). |
| `Spool` | `Print`: afdrukbestanden (`.SPO` = afgedrukt, `.SPL` = nog te printen). `ToClient\Post-001`, `Post-002`, ...: bestanden die naar die werkpost gestuurd worden (afdrukken, back-upzip, ...). `Temp`: tijdelijke bestanden (o.a. snapshots). |
| `ToGeel` | Bestanden die hier gezet worden, worden automatisch naar de server van Jamadata overgezet. Bijna niet meer gebruikt (nu via LogMeIn/TeamViewer). Kan veel schijfruimte innemen: leegmaken bij problemen. |
| `Updates` | Niet gebruikt. |
| `Work` | De "live" programma's: bij het opstarten van de database worden alle bestanden uit `Prog` naar `Work` gekopieerd en daar wordt mee gewerkt. |

**Kassa's en PDA's op afstand:** staan kassa's/PDA's op dezelfde locatie als de server, dan verloopt de uitwisseling via het lokale netwerk. Staan ze op een andere locatie (zonder VPN), dan dient de server van Jamadata als tussenstation: de kassa stuurt door naar de Jamadata-server en op de hoofdcomputer van de klant moet men via een snelkoppeling op het bureaublad (bv. "Doorsturen kassa ..." / "Update kassa's op afstand" = `\jamadata\kassa\sendkas`) de bestanden ophalen. Synchronisatie in twee stappen dus.

## 5. `JMS.ini` (in `\jamadata\prog\`)

Vertrouwelijk bestand: bevat serienummer, wachtwoord, postlicenties en mailinstellingen. Nooit doorsturen of tonen aan derden. Een regel uitschakelen kan door er een teken voor te zetten (bv. `x` of `*` vóór de sleutelnaam).

| Sectie | Sleutels | Betekenis |
|---|---|---|
| `[JamaSettings]` | `SerialNr=`, `Password=`, `PostCount=`, `SerialNr_Post-001=` ... | Licentie van de server en van elke post. De laatste post is een DEMO-post (`JMM:DEMO-<klantcode>...`) of de ComfortLink-code vanop de servicecomputer. |
| `[CopySettings]` | `CopyPath=S:\jamadata\Copy`, `CopyJamaSubDirs=PROG|KASSA|JamaPDA|FTKOPIE` | Bestemming van de schaduwkopie (stick/NAS/partitie) en welke submappen mee gekopieerd worden. |
| `[DataBaseSettings]` | `StdDossier1=001`, `StdDossier2=002`, `xStdDossier3=003`, `WorkFiles=BON|BON|` | Gebruikte dossiers; een `x` ervoor = niet meer gebruikt. |
| `[MailSettings]` | `MailFromName=`, `MailFromAddress=`, `Relay1Server=`, `Relay1Port=`, `MailBcc=` | Afzender en SMTP-relay voor automatisch mailen (details: maildocumentatie). |

Aandachtspunt: de JMC-versie moet recenter zijn dan 28/09/2016, anders worden wachtwoorden in `JMS.ini` naar hoofdletters omgezet (relevant bij Office 365-mailinstellingen).

## 6. Netwerkpoorten

| Poort(en) | Richting | Waarvoor |
|---|---|---|
| TCP 5000-5005 | Inkomend op de server | Kassa's (UC-Server). Best enkel toelaten vanaf de IP-adressen van de kassa's (zie `server-jms-storingen.md`). |
| TCP 5100-5130 | Inkomend op de server | Werkposten (Jamadata Desktop). |
| TCP 5006 | Uitgaand | Werken op afstand (ComfortLink). Standaard open, tenzij hardware-firewall. Test: `telnet jmm1.jamadata.be 5006`. |
| TCP 80 | Uitgaand | Online back-up en logging naar Jamadata. Het is **geen echt HTTP-verkeer** en kan door de hoge trafiek als denial-of-service gezien worden: IPS best afzetten en niet-HTTP-verkeer op poort 80 toelaten, of alle filters naar het Jamadata-adres uitschakelen. |
| TCP 60000 | Inkomend op de server | Omnis/JamaMobi (nieuwe PDA's), firewallregel "JamaMobi". |

Windows-firewallregel: naam **"Jamadata Server"**, inkomend, TCP, poorten `5000-5005, 5100-5130`. Staat er een hardware-firewall tussen, dan daar dezelfde poorten openzetten naar de server. **Geen andere software mag deze poorten gebruiken** (VPN, cloud-back-up, camera's, virusscanner-updates): dat veroorzaakt crashes van de JMS.

Virusscanner: de mappen `J:\jamadata` en de back-upbestemming (`S:\jamadata`) uitsluiten van scanning. Alle communicatie tussen server en werkposten (printopdrachten, bestanden, mails) loopt via de map `Spool`; een scanner ertussen vertraagt sterk of houdt bestanden tegen (uit opleiding, 01/06/2026).

## 7. Systeemvereisten

### Centrale computer (server)
Permanente aansluiting op een snelle internetverbinding (voor de Jama360-service). Windows Server is **niet nodig**.

| | Minimaal | Aanbevolen bij nieuwe aankoop |
|---|---|---|
| Windows | Windows 10 / Windows Server 2012 | Windows 10 (alle types; Pro als er een domeincontroller in het netwerk is) |
| Processor | Pentium of AMD | Intel Core i7 of AMD quad-/hexacore |
| RAM | 4 GB (op Windows Server: 8 GB) | min. 8 GB (minder dan 5 gebruikers) of 16 GB (meer dan 5 gebruikers) |
| Schijf | 50 GB vrij | min. 50 GB vrij, liefst SSD |
| Back-up | | USB 3.0-stick van 32 GB voor de schaduwbestanden (of NAS) |

"Supersysteem": recente i7 (8 cores/16 threads), USB 3.1-poort en -stick (of NAS), SSD of M.2 (PCIe): 512 GB als enkel Windows 10 en Jamadata Server erop staan; anders een extra snelle SSD van 256 GB enkel voor Jamadata.

Vuistregels geheugen: de Jamadata Server zelf ± 750 MB RAM, plus ± 125 MB per werkstation. Schijfruimte programma + gegevens: 50-100 GB.

**Windows Server (Essentials) of virtualisatie:** kan (Windows Server 2016/2019/2019 Essentials, SBS), maar er is vaak te weinig vrije capaciteit, zeker met Exchange en virusscanner. Wordt toch een Windows Server gekozen: voorzie **een aparte virtuele machine met Windows 10** enkel voor Jamadata, met min. 8 GB RAM, 4 cores/8 threads en 50-100 GB vrije ruimte op SSD of M.2. Een extra Windows 10-pc enkel voor Jamadata is vaak de eenvoudigste, goedkoopste en performantste oplossing.

**Veel gebruikers:** voor 20 gebruikers of meer is een server met dual CPU (elk 8 kernen) interessant; zowel aantal kernen als kloksnelheid tellen. RAID-1 kan vertragen; een caching-controller helpt maar enkel veilig met UPS. Een standaard SSD is sowieso sneller en minder gevoelig voor dataverlies.

### Werkpost
- Windows 10.
- Liefst Full-HD-scherm van 22" of meer (verticale resolutie 1080 pixels of hoger); breedbeeld is ideaal voor meerdere sessies.

### Schijfindeling en back-upmedium
- Map `jamadata` op een schijf **zonder systeemherstel**; bestaat die niet, verklein dan de C-schijf en maak van de vrije ruimte een **J-schijf** (min. 15 GB, liefst ± 50 GB).
- Lege USB-stick van min. 32 GB, onopvallend **achteraan** in de centrale computer (liefst stationsletter **S:**), zo mogelijk **NTFS** geformatteerd (sneller, meer bestanden). Een NAS mag ook.
- De data kan niet zomaar op een externe (USB-)harddisk staan; een NAS via **iSCSI** kan wel (Windows ziet die als echte schijf).

## 8. Veelgestelde vragen over de centrale computer

| Vraag | Antwoord |
|---|---|
| Vanaf wanneer een aparte centrale computer? | Aanbevolen vanaf meer dan 3 werkstations. |
| Mag er op de centrale computer gewerkt worden? | Technisch ja. Bij grotere configuraties wordt een aparte centrale computer aangeraden waarop **niet gesurft of gemaild** wordt en liefst geen Office staat (modules kunnen de server storen). |
| Moet de centrale computer altijd aan staan? | Aanbevolen (24/24 controle en beveiliging van de data). Wel bv. maandelijks herstarten voor updates. Het scherm mag uit. Bij Light moet een gebruiker aangemeld blijven. |
| Moeten alle pc's vernieuwd worden? Nieuwe monitors? | Neen. De snelheid wordt bepaald door de centrale computer. |
| Waarom moeten alle printerdrivers op de centrale computer staan? | De programma's draaien op de server en sturen de printers van daaruit aan. Printers hoeven niet fysiek aan de server te hangen (TCP/IP-poort volstaat). Een printer die enkel op één werkpost gebruikt wordt, hoeft niet op de server: de gebruiker kiest zelf via Jamadata Desktop (Configuratie > Documenten) om lokaal af te drukken. |
| Kan de server-pc mee naar een tweede locatie? | Kan, maar vraagt telkens aanpassingen voor schermen en printers. Beter: ComfortLink (werken op afstand). |
| Wordt er een interne kopie gemaakt? | Ja, Light en Standaard maken permanent een schaduwkopie zonder de gebruikers te storen; best op een USB-stick achteraan. Zie `backup-en-herstel.md`. |
| Is er een online kopie buiten het bedrijf? | Ja, de online back-up, enkel met het Jamadata 360-onderhoudscontract; omvat data en programma's van het pakket, de kassa's en de PDA's. |

## Bronnen
- Jamadrink: "Jamadata Server systeemvereisten.docx" (FAQ Jamadata Server 2.05 + systeemvereisten)
- Jamadrink: "Jamadata-Server_overzicht_enkele_mogelijkheden 2.0.docx"
- Jamadrink: "Installatiedraaiboek Jamadata 1.docx"; Onenote: "Jamadata Server.pdf" (volledigste exemplaar; "Jamadrink/Jamadata Server.pdf" is een ouder exemplaar)
- FAQ: "Opleiding Helpdesk Jamadata.docx" (mappenstructuur, licenties)
- FAQ / Jamadrink: "FAQ Jamadata SERVER.docx"
- Jamadrink: "HOWTO - Problemen met crashen JMS.docx"
- Transcripties opleidingen: "[klant]_Migratie_20260601_162649.txt", "[klant] Migratie Server-20260611_132355-Opname van vergadering.txt", "vid backup.txt" (aanvullende details, gesproken bron)
