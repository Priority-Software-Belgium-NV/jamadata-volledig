# Praktijkkennis opleiding mei 2026: server, installatie, migratie en netwerk

> **Waarschuwing.** Deze inhoud komt uit gesproken opleidingssessies (automatische Whisper-transcriptie, mei 2026). Productnamen en bestandsnamen zijn waar nodig gecorrigeerd, maar details (toetsen, mapnamen, poortnummers) kunnen herkenningsfouten bevatten. Controleer bij twijfel tegen de officiële handleiding (o.a. "Installatie nieuwe Jamadata-server en overzetten gegevens", "Voorbereiding nieuwe computer", "Installatie Jamadata Desktop"). Punten gemarkeerd met *(te verifiëren)* waren in de opname niet eenduidig.

Gebruik dit document voor: vragen over hoe een Jamadata-server technisch in elkaar zit (JMS, JMR, JMT, JMD, jms.ini, Windows-gebruiker), hoe je een server voorbereidt, installeert of migreert naar een nieuwe pc/cloudserver, welke poorten en netwerkinstellingen nodig zijn, en hoe programma-updates en nieuwe JMS-versies bij de klant terechtkomen.

## 1. Begrippen en onderdelen

In de transcripties worden de afkortingen door Whisper vaak verhaspeld (IMS/EMS/DMS, IMR/EMR/DMR, IMT/EMT, IMD/EMD). Bedoeld is telkens:

| Afkorting | Wat | Waar |
|---|---|---|
| **JMS** | De database(server) van Jamadata. | Draait als service op de server. |
| **JMR** | De "reporter": Windows-service die de toestand en fouten van de installatie doorstuurt naar de SVC (het interne opvolgscherm van support). | Windows-services, naam begint met J. |
| **JMT** | Beheertool om de database te stoppen, verwijderen (remove), met de hand te starten en opnieuw als service te installeren. Bevat onderaan ook een toolbox (firewall, Jamadata-map, USB, netwerk, opdrachtprompt in de juiste map). | `<schijf>:\Jamadata\JMT\bin\JMT.exe` |
| **JMD** | Jamadata Desktop: de "viewer" op elke werkpost. Alle schermen worden op de server geopend; JMD neemt die schermen over via het netwerk. | Op elke post, ook op de server zelf. |
| **jms.ini** | Parameterbestand van de installatie (serienummer, aantal posten, postdefinities, back-uppad, ...). | `<schijf>:\Jamadata\PROG\jms.ini` |
| **SVC** | Intern opvolgscherm bij support: per klant o.a. servernaam, IP-adres, versie (Mono/Light/Server), JMS-versie, laatste JMR-contact, heartbeat, status van USB-/image- en online back-up, foutenlog, klaarstaande updates. | Intern. |

Versies van het pakket: **Mono**, **Light** en **Server** (standaard). Welke versie een klant heeft, zie je in de SVC. (opleiding 07-05-2026, ca. 00:01; 12-05-2026 namiddag, ca. 00:48)

Standaardlocatie: bij de meeste klanten staat alles in `J:\Jamadata` (aparte partitie, zie § 5.3). Belangrijke submappen: `PROG` (programma's, jms.ini, submap `Tools`), `FAS` (databasebestanden, met submappen `LOG`, `SHA`, `FSD`), `JMT`, `Kassa`, `Mail`, `Dump`, de back-upmappen (zie document diagnose/back-up).

**Hoe herken je de actieve Jamadata-map** als er meerdere kopieën op een pc staan: in de map `FAS` van de actieve installatie staan bestanden met de datum van vandaag. (opleiding 07-05-2026, ca. 00:31; 12-05-2026 voormiddag, ca. 00:13)

## 2. jms.ini

Bron: opleiding 07-05-2026 (ca. 00:01–00:21), 13-05-2026 (ca. 00:38–00:40 en 00:48–00:50).

- Staat in de map `PROG`. Bevat bovenaan o.a. het serienummer en `PostCount`, daarna per post een blok (pc-naam, werkgroep, ...), en verder o.a. de kopie-/back-upinstellingen.
- **Bijna alles wordt automatisch door het pakket ingevuld.** Je past jms.ini zelden met de hand aan.
- **PostCount** = aantal posten van de klant **plus één**. De laatste post is de post waarmee support op afstand in het pakket van de klant kan werken. Dit wordt niet aan de klant meegedeeld.
- Een postregel zonder voorvoegsel is een **lokale post** (zelfde netwerk of via VPN). Een post met voorvoegsel `JMM:` is een **post op afstand**, die verbinding maakt via de centrale remote-server van Jamadata (het verbindingsprogramma heet ook JMM/JMM-client). Post 1 is meestal de server zelf.
- Posten op afstand werken niet vanuit elk land: sommige landen/firewalls blokkeren de verbinding; een specifiek IP-adres kan intern als veilig worden toegevoegd.
- **Servernaam wijzigen**: doe dit in het pakket, niet in het bestand: hoofdmenu Voorraad → `+` (parameters) → `J` (JMS-instellingen) → `4`. jms.ini wordt dan automatisch aangepast. Dit moet op het systeem van de klant gebeuren (dus via de post op afstand of via schermovername).
- **Extra post toevoegen**: de ontwikkelaar past jms.ini aan (extra post, PostCount) en geeft dat mee; daarna moet support enkel nog JMD installeren op de nieuwe pc en het postnummer invullen.
- **Open jms.ini niet zichtbaar in het bijzijn van de klant.** Er zit geen beveiliging op het aantal posten; wie ziet hoe het werkt, kan zelf posten bijmaken. Veiligste werkwijze: bestand naar je eigen pc halen (bv. via bestandsoverdracht van de schermovername), daar aanpassen en terugzetten.
- **Back-uppad**: sectie met de kopie-instellingen (gehoord als "copy settings" / "copy pad"). Wijzig enkel de schijf of het voorvoegsel; laat de mapnaam `Jamadata\Copy` altijd staan, zodat de back-up later terug te vinden is door op die mapnaam te zoeken. Na het wijzigen maakt het pakket de map zelf aan en begint het te kopiëren. *(exacte sleutelnaam te verifiëren)*

## 3. Windows-gebruiker "Jamadata-server"

Bron: opleiding 07-05-2026 (ca. 00:02–00:10), 12-05-2026 namiddag (ca. 00:34–00:40), 13-05-2026 (ca. 00:17).

- Bij elke installatie van de JMS-setup wordt op de server automatisch een lokale Windows-gebruiker voor Jamadata aangemaakt (in de opleiding "Jamadata-server" genoemd; exacte schrijfwijze: zie handleiding). De naam is altijd dezelfde en kan niet gewijzigd worden.
- Het wachtwoord ligt vast per installatie en mag **nooit gewijzigd** worden (het is ook geregistreerd in de SVC; wijzigen kan enkel door de ontwikkelaars). (Wachtwoord: zie interne bron / SVC-fiche van de klant.)
- De services van Jamadata (o.a. JMR) worden onder deze gebruiker gestart. **Kan de gebruiker niet aangemaakt worden, dan start de JMR-service niet** en komt de klant niet "online" in de SVC.
- Waarvoor heb je deze gebruiker nog nodig:
  - aanmelden op de server van de klant zonder de klant om een account te moeten vragen;
  - toegang geven tot een NAS/netwerkshare voor de automatische back-up (de IT'er moet déze gebruiker rechten geven);
  - in de instellingen van (oudere) PDA's voor draadloos synchroniseren;
  - Windows-printers moeten zichtbaar zijn voor deze gebruiker (zie document printers).
- De gebruiker is standaard **verborgen** op het Windows-aanmeldscherm. In `<schijf>:\Jamadata\PROG\Tools` staan twee registerbestanden om de gebruiker te verbergen (hide) of zichtbaar te maken (unhide): dubbelklikken, tweemaal bevestigen. Op een echte server (waar enkel beheerders aanmelden) mag hij zichtbaar blijven; bij een kleine klant zet je hem na gebruik terug op verborgen.
- Geef naam en wachtwoord in principe niet aan de klant; enkel in uiterste nood (bv. aan de IT'er voor de NAS).

### Gebruiker werd niet aangemaakt (vooral in domeinen of zonder beheerdersrechten)

1. Controleer in de SVC: staat het laatste **JMR-contact** uren/dagen oud terwijl de heartbeat wel loopt, dan draait de JMR-service niet.
2. Controleer in Windows: Services → sorteer op naam / typ `J` → JMR: moet "Wordt uitgevoerd" en opstarttype "Automatisch" zijn.
3. Kijk in het Windows-logboek: Logboeken → Windows-logboeken → **Toepassing**. Alle fouten die de SVC toont, worden door Jamadata ook hier geschreven (bv. "gebruiker niet kunnen aanmaken, onvoldoende rechten").
4. Maak de gebruiker manueel aan (als administrator, of laat de IT'er het doen): rechtsklik "Deze pc" → Meer opties → Beheren → Lokale gebruikers en groepen → Gebruikers → Nieuwe gebruiker. Wachtwoord zoals in de SVC. Vinkje "Gebruiker moet wachtwoord bij volgende aanmelding wijzigen" **uit**; "Gebruiker kan wachtwoord niet wijzigen" en "Wachtwoord verloopt nooit" **aan**.
5. Start daarna de JMR-service en ververs de SVC: het JMR-contact moet weer actueel zijn.

## 4. Controleren of er nog iemand in het pakket werkt

Altijd doen vóór je de database stopt, een JMS-setup uitvoert, een update forceert of alle posten herstart. Bron: opleiding 07-05-2026 (ca. 00:25–00:28), 13-05-2026 (ca. 00:42–00:44), 28-05-2026 (ca. 00:22–00:26).

- Hoofdmenu Voorraad → `+` → `J` (JMS-instellingen) → `T` "Controleer op actieve gebruikers".
- Gebeurt er niets, dan is niemand bezig. (Je eigen post telt niet mee zolang je in dit instellingenscherm staat.)
- Anders verschijnt een lijst met gebruikers:
  - **rood** = zit in een kritiek stuk (zeker bij het maken van een bon of factuur) – nu de database herstarten betekent dat die bon/factuur verloren kan gaan;
  - andere kleur (in de opleiding wit/blauw genoemd) = zit gewoon ergens in een scherm.
- `F7` ververst de lijst (je ziet mensen verdwijnen/bijkomen).
- Een lege regel zonder naam onderaan mag je negeren (kan o.a. de supportpost zijn).
- Vraag daarnaast altijd expliciet aan de klant of iedereen uit het pakket is. Kassa's: laten stoppen tot op het Windows-bureaublad.
- Ook wie "maar" in een klantenfiche iets aan het invullen is, verliest dat werk bij een herstart.

**Wachtwoordscherm in het pakket.** Bij sommige klanten vraagt het pakket een wachtwoord bij het openen van parameters, facturatie of boekhouding. Support beschikt over een vaste procedure om dat scherm te passeren (functietoets + codewoord; details: zie interne bron / handleiding migratie). Die procedure mag nooit aan de klant verteld of voorgedaan worden op een manier dat hij ze kan nadoen: de persoon aan de lijn kan een bediende zijn die net géén toegang mag hebben. (opleiding 07-05-2026, ca. 00:28; 12-05-2026 namiddag, ca. 00:55)

## 5. Nieuwe server voorbereiden

Bron: opleiding 12-05-2026 voormiddag (ca. 00:08–00:31) en namiddag (ca. 00:06–00:34). Het interne document "Voorbereiding nieuwe computer / klaarmaken centrale computer voor Jamadata" bevat dezelfde stappen en mag ook naar de klant of zijn IT'er. Ervaring van de opleider: laat je de IT'er dit doen, dan wordt geregeld één stap vergeten (een download, een firewallregel) en zoek je daar achteraf lang naar; zelf doen is vaak sneller. Bij grote klanten/cloudservers gebeurt het wel in overleg met de IT'er.

### 5.1 Vereiste Microsoft-onderdelen

In `Jamadata\PROG\Tools` (en via de links in het voorbereidingsdocument) staan vier installatiebestanden die op een nieuwe server uitgevoerd moeten worden:

- .NET Framework 4
- .NET Framework 4.5
- Visual C++ Redistributable 2010 (de oudste)
- Visual C++ Redistributable 2017 (de versie 2015 is hetzelfde pakket)

Gewoon alle vier uitvoeren; is een onderdeel al aanwezig, dan meldt de installer dat ("maakt al deel uit van het besturingssysteem" / reeds geïnstalleerd / repair) en kan je annuleren. **Ontbreekt er één, dan krijg je DLL-fouten bij het starten van de JMS en start het pakket niet** (fouten ook zichtbaar in de logging/SVC).

Enkel voor Windows 7: drie DLL-bestanden uit `Jamadata\PROG\Tools\Win7` kopiëren naar `PROG`. Vanaf Windows 10 is dat niet nodig. Ontbreken ze, dan geeft de SVC een foutmelding.

Acrobat Reader is niet meer nodig (Edge/Chrome openen pdf's). Een Excel-viewer op de server is optioneel (handig als support op de server een Excel-export wil bekijken).

### 5.2 Vast IP-adres

- **Elke server krijgt een vast IP-adres.** Staat de server op DHCP, dan werkt alles tot de router een ander adres uitdeelt; daarna kan geen enkele post nog verbinden.
- Veelvoorkomende oorzaak van storingen bij kleine klanten: het internet valt even weg, Windows stelt "Problemen oplossen" voor, en die probleemoplosser zet de netwerkkaart op DHCP. Gevolg: ander IP-adres, alle posten tonen "wacht op serversessie" (zie document diagnose).
- Werkwijze (klassiek): Configuratiescherm → Netwerkcentrum → klik op de verbinding (Ethernet/LAN) → **Details**: noteer of maak een screenshot van IPv4-adres, subnetmasker (bijna altijd 255.255.255.0), standaardgateway en DNS-server(s) → Sluiten → **Eigenschappen** → dubbelklik "Internet Protocol versie 4 (TCP/IPv4)" → "Het volgende IP-adres gebruiken" en "De volgende DNS-serveradressen gebruiken" → waarden invullen.
- Werkwijze (Windows 11-stijl): rechtsklik netwerkicoon → Netwerk- en internetinstellingen → adapter → Eigenschappen → IP-toewijzing **Bewerken** → Handmatig.
- IPv6 wordt door Jamadata niet gebruikt.
- **Kies een adres buiten het DHCP-bereik van de router** (een router deelt bv. .100–.200 of .100–.254 uit; een adres in dat bereik kan later ook aan een ander toestel gegeven worden → IP-conflict). Afspraak van de opleider: kies een **rond getal** (bv. .50, .100, .150, .200). Dat helpt later ook bij de diagnose: staat er in de SVC een "raar" eindcijfer (bv. .34 of .137), dan heeft de server vermoedelijk een DHCP-adres gekregen.
- Controleer of het adres vrij is: opdrachtprompt → `ping <adres>`. "Reply from ..." = adres is in gebruik; "Destination host unreachable" = vrij. Een IP-scanner toont alle gebruikte adressen in het netwerk.
- **Let op bij werken op afstand:** één tikfout in IP/gateway en de klant heeft geen netwerk meer – je bent je schermovername kwijt en moet de klant blind laten terugzetten naar automatisch. Drie keer nakijken vóór OK.
- Het IP-adres van de server staat ook in de SVC-fiche van de klant.

### 5.3 Aparte schijf/partitie zonder systeemherstel

- De map Jamadata moet op een schijf staan **waar geen Windows-systeemherstel actief is**. Op C: staat systeemherstel standaard aan; wordt de pc ooit teruggezet naar een herstelpunt, dan gaat de Jamadata-data mee terug en is de klant gegevens kwijt.
- Standaard: aparte partitie **J:**. Minimum 15 GB, liefst ± 50 GB; vuistregel: ongeveer het dubbele van de huidige map Jamadata op de oude server (kijk daar via rechtsklik → Eigenschappen), maar laat C: genoeg vrije ruimte.
- Aanmaken: rechtsklik "Deze pc" → Meer opties → **Beheren** → Schijfbeheer → rechtsklik op C: → **Volume verkleinen** → hoeveelheid in MB (50000 ≈ 50 GB) → in de vrijgekomen ruimte een nieuw volume maken met stationsletter J.
- Een nieuw aangemaakte partitie heeft systeemherstel standaard uit. Controleren kan via Geavanceerde systeeminstellingen → tabblad Systeembeveiliging.
- Een verkleining ongedaan maken kan niet met standaard-Windows; daarvoor is een partitietool nodig.
- Cloud- of door IT beheerde servers: daar wordt geen systeemherstel "zomaar" uitgevoerd; in overleg mag Jamadata op C: of op een aparte D:.

### 5.4 Firewall: poorten openzetten

| Poorten (TCP, inkomend op de server) | Waarvoor |
|---|---|
| **5000–5005** | Kassa's (en toestellen op afstand) die verbinding maken met de server, lokaal of via de centrale communicatieserver. |
| **5100–5130** | Jamadata Desktop: elke post gebruikt één poort (post N gebruikt ongeveer poort 5100+N; of de telling bij 0 of 1 begint is *te verifiëren*). In JMD zijn 50 postnummers kiesbaar, maar er zijn maximaal 30 bruikbaar. |
| **60000** (in één passage 60001 genoemd) | Nieuwe PDA's (Jamamobi) die via wifi rechtstreeks met de server verbinden. *(exact poortnummer: zie PDA-handleiding)* |

Werkwijze: Windows Defender Firewall → Geavanceerde instellingen → Regels voor binnenkomende verbindingen → **Nieuwe regel** → Poort → poortbereik plakken (kopieer uit het voorbereidingsdocument om tikfouten te vermijden) → Verbinding toestaan → Domein, Privé én Openbaar aanvinken → naam geven.

- Geef regels altijd een naam die begint met "Jamadata" (bv. "Jamadata server", "Jamadata kassa"; voor de PDA "Jamamobi"), zodat collega's ze terugvinden.
- Een regel dubbel toevoegen kan geen kwaad.
- Op deze poorten mag **geen andere software** luisteren (meegemaakt: cloudback-up, camerasoftware, virusscanner die bv. poort 5114 gebruikt → die post kan nooit verbinden). Dat is een zaak voor de IT'er van de klant.
- Wordt later een andere virusscanner/firewall geïnstalleerd, dan moeten de poorten ook dáár opengezet worden (verschilt per product; vaak enkel door de IT'er aanpasbaar).
- Cloudserver: de poorten 5000–5005 mogen enkel openstaan voor de toestellen van de klant, niet voor het hele internet. Staan ze volledig open, dan verschijnen er in de SVC herhaaldelijk "UC server error"-meldingen door vreemde verbindingspogingen. (opleiding 20-05-2026 namiddag, ca. 00:00)

### 5.5 Virusscanner

- Standaard Windows Defender: uitsluitingen zijn in de praktijk niet nodig.
- Andere scanners (Norton, NOD32, McAfee, ...): sluit de map Jamadata (bv. `J:\Jamadata`) en de back-uplocatie (bv. `S:\Jamadata`) uit van de realtime-controle. Anders wordt Jamadata traag of werkt het in sommige gevallen niet. Vaak kan enkel de IT'er dit instellen (wachtwoordbeveiligde scanner).
- Norton op de server is een bekende oorzaak van terugkerende fouten rond poort 5000–5005 in de SVC; verwijderen lost het vaak op. (opleiding 20-05-2026 voormiddag, ca. 00:01)

### 5.6 Back-upmedium en printers

- Back-upstick: lege USB-stick van minimum 32 GB, op een onopvallende plaats (achterkant pc), met een **vaste stationsletter achteraan in het alfabet** (traditioneel S:). Stationsletter toewijzen: Schijfbeheer → rechtsklik op het volume → "Stationsletter en paden wijzigen". Zie het document over diagnose/back-up voor alternatieven (NAS, externe schijf, andere map).
- Installeer **alle printers van de klant op de server**; zie document printers.

## 6. Installatie van JMS, JMT en JMD

Bron: opleiding 12-05-2026 namiddag (ca. 00:40–00:50), 13-05-2026 (ca. 00:37–00:44).

### 6.1 JMS-setup (database) – enkel op de server

1. Download de JMS-setup (via de Jamadata-downloadsite met nieuwe versies, of de rechtstreekse downloadlink voor de JMS; in de opleiding gehoord als `jmsn.prsw.be` – *adres te verifiëren in de installatiehandleiding*).
2. **Niet in de browser op het bestand klikken** (dan loopt het als gewone gebruiker). Open de map Downloads → rechtsklik → **Als administrator uitvoeren**.
3. De setup stelt als map `C:\Jamadata` voor. **Pas dit aan naar de juiste schijf** (meestal `J:\Jamadata`). Een verkeerd pad is ernstig: de installatie wijst dan naar de verkeerde map. Na een eerste installatie onthoudt de setup het pad.
4. Volgende → Installeren. De setup controleert/maakt ook de Windows-gebruiker (zie § 3).
5. **De setup herstart de database: iedereen die in het pakket zit, vliegt eruit.** Eerst § 4 uitvoeren.
6. Foutmelding dat JMT nog openstaat: Taakbeheer → tabblad Details → proces JMT beëindigen → setup opnieuw.

Nooit uitvoeren op een bijstation; dat heeft geen nut.

### 6.2 Database stoppen, met de hand starten en installeren met JMT

1. Ga naar `<schijf>:\Jamadata\JMT\bin`, selecteer `JMT.exe` en start als administrator (rechtsklik, of `Ctrl`+`Shift`+`Enter`).
2. Het venster heeft drie delen: bovenaan **Server** (standaard), midden **Light**, onderaan **Mono**. Werk in het deel van de versie van de klant.
3. **Stop** stopt de database. **Remove** verwijdert de service-installatie; zonder Remove start de database bij een herstart van de pc gewoon weer op.
4. Start daarna de JMS **met de hand** (knop in JMT): je ziet of de database proper opstart zonder fouten. Sluit met het kruisje en wacht even.
5. Klik **Install** in het juiste deel (Server/Light/Mono). De database draait weer als service.
6. Open je JMD te snel na Install, dan krijg je een zwart scherm: sluiten, even wachten, opnieuw openen.

### 6.3 Jamadata Desktop (JMD) op elke post

1. Download de JMD-setup (in de opleiding gehoord als `jmdn.prsw.be` – *te verifiëren*). Deze mag je gewoon aanklikken en de wizard doorlopen; JMD herstart zichzelf.
2. JMD → Configuratie → Instellingen: **IP-adres van de server**, het **postnummer** en de **postlicentie** (cijfer 0–9) invullen. Het naamveld hoeft niet ingevuld te zijn; het IP-adres volstaat. Klik in een ander veld: bij een geldig, bereikbaar adres kleurt het veld groen. Onderaan verschijnt "lokale server verbonden".
3. **Op de server zelf**: installeer ook JMD, post 1, en gebruik als IP-adres **127.0.0.1**. Dat blijft werken, ook als het IP-adres van de server ooit wijzigt.

### 6.4 Kassa of PDA op afstand (zonder VPN)

- Voor kassa's/PDA's die niet in hetzelfde netwerk zitten, loopt de gegevensuitwisseling via de centrale communicatieserver van Jamadata als tussenstation (in twee richtingen: artikelen/prijzen heen, verkopen/tellingen terug).
- Op de server staan daarvoor twee batchbestanden in `Jamadata\PROG` (gehoord als "SendKas" en "SendPDA"); zet een kopie/snelkoppeling op het bureaublad zodat de klant erop kan dubbelklikken.
- In het batchbestand moet bij "filiaal" de **klantcode** (de drieletterige afkorting van de klant) staan, niet de placeholder `XX`. Staat er een verkeerde code, dan komen de gegevens in de verkeerde map op de communicatieserver terecht. De rest van het bestand niet aanpassen.
- Dit komt maar bij een minderheid van de klanten voor. (opleiding 12-05-2026 namiddag, ca. 00:50–00:55)

## 7. Migratie van een oude naar een nieuwe server

Bron: opleiding 07-05-2026 (ca. 00:22–00:52), 12-05-2026 voormiddag (ca. 00:26) en namiddag.

### 7.1 Op de oude server

1. **Iedereen uit het pakket** (§ 4).
2. **Database stoppen** met JMT: Stop + Remove (§ 6.2).
3. **Controleer `Jamadata\FAS\LOG`: die map moet leeg zijn.** Zolang de database draait, staan daar bestanden (nog niet in de database verwerkte wijzigingen). Staan er na het stoppen nog bestanden:
   - start de JMS nog eens met de hand via JMT en sluit ze met het kruisje; herhaal dit desnoods drie-vier keer;
   - blijven er bestanden staan (dan zie je ook fouten in de SVC), dan is het een afweging: de bestanden weggooien betekent dat die wijzigingen verloren zijn. Bij een oud, niet meer gebruikt dossier (bv. van jaren geleden) wordt dat aanvaard; anders escaleren.
   - **Vóór een migratie moet deze map leeg zijn.**
4. **Service JMR stoppen en uitschakelen**: Services → JMR → Stoppen → opstarttype **Uitgeschakeld**. Anders blijven oude en nieuwe server beide naar de SVC rapporteren.
5. **Overbodige data verwijderen** vóór het kopiëren: de lokale kopie-/back-upmap (in de opname "copy-out"/"kopie-alt" genoemd) en de map `Dump` leegmaken – dat is een kopie van een kopie.
6. **Netwerkgegevens noteren** (IP, subnetmasker, gateway, DNS) en de oude server daarna **op DHCP zetten** ("Automatisch een IP-adres laten toewijzen"), zodat de nieuwe server hetzelfde vaste IP-adres kan krijgen zonder conflict.
7. Na een geslaagde migratie: de oude map hernoemen (bv. `Jamadata_old`) zodat niemand per ongeluk de oude installatie start. Hernoemen lukt pas als de JMR-service gestopt is.

### 7.2 Data overzetten

- De **volledige map Jamadata** moet naar de nieuwe server: via USB-stick of externe schijf (fysiek, het eenvoudigst om mee te beginnen; kies een stick groter dan de map), via het netwerk, of via de bestandsoverdracht van de schermovername (twee sessies open). Zippen kan, maar duurt lang door de vele kleine bestanden.
- Bij cloudservers kan het enkel via het netwerk.
- Tip voor grote klanten: vraag de IT'er om de map **vooraf te spiegelen met robocopy** en op het moment van de migratie, na het stoppen van de database, enkel de gewijzigde bestanden nog eens te synchroniseren. Voorbeeld uit de praktijk: eerste kopie 4,5 uur (trage upload naar de cloud), de delta op de migratieavond nog 40 minuten.
- Kopiëren is altijd het zwaarste/langste deel van een migratie; plan het buiten de openingsuren.

### 7.3 Op de nieuwe server

1. Voorbereiding volgens § 5 (onderdelen, partitie J:, firewall, virusscanner, printers, back-upmedium).
2. **Geef de nieuwe server hetzelfde vaste IP-adres als de oude.** Dan moet je niets aanpassen aan de werkposten, de kassa's en de communicatie-instellingen. Krijgt de server een ander adres, dan moet je op **alle** posten de JMD-instellingen aanpassen, en ook op elke kassa (o.a. het batchbestand voor de communicatie, in de opname "jama.bat" genoemd – *te verifiëren*).
3. Map Jamadata op de juiste schijf plaatsen.
4. JMS-setup als administrator uitvoeren met het juiste pad (§ 6.1).
5. Met JMT: JMS eerst met de hand starten en controleren, dan Install (§ 6.2).
6. JMD op de server installeren (127.0.0.1, post 1) en testen.
7. In de SVC controleren: JMR-contact actueel, juiste JMS-versie, back-upstatus in orde.
8. Bij grote klanten: eerst een testmigratie doen en enkele dagen later de definitieve (met een nieuwe spiegeling).

## 8. Programma-updates en nieuwe JMS-versies

Bron: opleiding 12-05-2026 namiddag (ca. 01:08–01:12), 13-05-2026 (ca. 00:37–00:44), 20-05-2026 voormiddag (ca. 00:25–00:38).

### 8.1 Wat de klant ziet

- Staat er een update klaar, dan verschijnt een **geel scherm**: "Er staat een update van het programma klaar", met de tekst die de ontwikkelaar/support heeft meegegeven. Het scherm komt enkele keren per dag (ochtend, middag, avond) en ook via het brievenscherm bij het opstarten.
- **Installeer update** = `F4`. Op de andere posten verschijnt de melding dat de update bezig is.
- Meldt het pakket dat er nog gebruikers bezig zijn: met `F7` vernieuwen tot de lijst leeg is; kassa's laten stoppen tot op het bureaublad. Is iedereen er zeker uit en blijft de melding staan, dan kan met `F4` toch doorgegaan worden.
- Een update duurt normaal **1 à 2 minuten** (uitzonderlijk langer als databestanden omgezet moeten worden). In de SVC-log zie je: update opgehaald → update verwijderd → stop → start.
- Kassa-updates worden door de server per kassa klaargezet in `Jamadata\Kassa\TO\<kassa>` en bij de volgende transfer door de kassa opgehaald en uitgevoerd.

### 8.2 "Ik heb de update opgehaald en nu start het pakket niet meer"

- Bekend probleem: bij een deel van de klanten (geschat ± 30 %, vooral grote installaties) herstart de database na het ophalen van de update niet automatisch. De oorzaak is niet bekend.
- Richtlijn voor de klant: **na 10 minuten wachten zonder resultaat** het icoon "Jamadata server herstarten" op de server gebruiken.
- Kan de klant niet aan de server: in JMD → menu **Help** → "Alle posten herstarten" (bevestigen dat je de volledige Jamadata-server wil herstarten en dat geen andere gebruikers meer bezig zijn). Daarna komen alle schermen weer online.
- Support kan vanuit de SVC ook zelf een herstart van de JMS geven. Doe dat enkel nadat de klant bevestigd heeft dat niemand meer werkt, en vertel de klant niet in detail welke knoppen support heeft.

### 8.3 Bij elk klantcontact even meenemen

- Kijk in de SVC of er een update klaarstaat (klant staat in het oranje) en laat ze meteen ophalen.
- Kijk naar de JMS-versie; is die oud, werk ze meteen bij (met akkoord van de klant, iedereen eruit).

### 8.4 Nieuwe versie van de JMS

- Een nieuwe JMS-versie is af en toe nodig voor nieuwe functionaliteit (bv. Peppol).
- Sinds kort kan de JMS **meegeleverd worden in een gewone programma-update**, zodat de setup niet meer bij elke klant manueel uitgevoerd moet worden.
- De setup (§ 6.1) blijft nodig bij een nieuwe serverinstallatie/migratie, omdat alleen de setup de Windows-gebruiker aanmaakt.
- jms.ini wordt door een update nooit aangepast, tenzij het bestand uitdrukkelijk wordt meegegeven.

### 8.5 Een update klaarzetten (intern, tweede lijn/ontwikkeling)

Ter info, zodat je begrijpt wat je in de SVC ziet; dit is geen eerstelijnstaak. *(Map- en bestandsnamen zoals gehoord; te verifiëren.)*

- Bestanden voor een klant worden op de interne back-up-/uitwisselschijf geplaatst in de map "naar klant" onder de klantcode (gehoord als `TOKLT\<klantcode>`); wat van klanten binnenkomt (back-ups, logs) staat onder "van klant" (`FROMKLT\<klantcode>`).
- Voor een kassa-update wordt het eenmalig uit te voeren kassabestand (gehoord als "run-once"-bestand met extensie `.KAS`) in die map gezet.
- Klaarzetten gebeurt vanuit een DOS-prompt op een 32-bit Windows-omgeving: in de klantmap het commando voor de boodschap (`MSG`, tekst die de klant op het gele scherm ziet) en daarna `GO` (klaarzetten). `GO X` zet klaar én voert meteen uit – dat herstart de database bij de klant en mag dus enkel als iedereen eruit is.
- In de SVC wordt de klant eerst groen en binnen de minuut oranje: de update staat klaar.

## 9. Interne infrastructuur waar klanten van afhangen (ter info)

Bron: opleiding 12-05-2026 voormiddag (ca. 00:31–00:36, 00:46).

- Kassa's en PDA's op afstand, en klanten die op afstand werken, verbinden via een centrale service-/communicatieserver van Jamadata (poorten 5000–5005).
- Op die server staan vijf verbindingsvensters (UC1 t/m UC5) die op **stand-by** moeten staan. Blijft er één op "connected" hangen (langer dan enkele seconden zonder activiteit), dan is die sessie dood: venster sluiten en via de snelkoppeling opnieuw starten. Zijn alle vijf bezet, dan kan geen enkele kassa/PDA nog verbinden (bv. om prijzen op te halen). Dit wordt elke ochtend gecontroleerd.
- Het venster van de JMM-client (met rechts onderaan de lijst van klanten die op dat moment op afstand werken) mag **nooit gesloten** worden en moet na een herstart/update van die server opnieuw gestart worden; anders kan geen enkele klant nog op afstand werken.
- Symptoom voor de helpdesk: meerdere klanten bellen tegelijk dat werken op afstand of de kassacommunicatie via de cloud niet lukt → eerst deze server laten nakijken.

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):

- gedocumenteerde kennisoverdracht VI-20260507_141735-Opname van vergadering.txt
- gedocumenteerde kennisoverdracht V-20260512_101045-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260512_150237-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260513_094305-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260520_100445-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260520_143704-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260528_100522-Opname van vergadering.txt
