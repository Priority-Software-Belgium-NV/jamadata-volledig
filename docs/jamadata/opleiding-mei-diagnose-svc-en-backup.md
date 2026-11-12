# Praktijkkennis opleiding mei 2026: diagnose, SVC en back-up

> **Waarschuwing.** Deze inhoud komt uit gesproken opleidingssessies (automatische Whisper-transcriptie, mei 2026). Het is ervaringskennis van een expert, deels "trial and error", en kan herkenningsfouten bevatten in map- en bestandsnamen. Controleer bij twijfel tegen de handleiding en overleg met tweede lijn/ontwikkeling vóór ingrepen op de database. Punten met *(te verifiëren)* waren niet eenduidig.

Gebruik dit document voor: de diagnosevolgorde bij de meest voorkomende telefonische problemen ("Jamadata Desktop wacht op serversessie", pakket start niet na update, database blokkeert of herstart telkens, back-up werkt niet), het lezen van de SVC, en hoe de verschillende back-ups (automatische kopie op stick/NAS, manuele back-up, online back-up) werken.

Voor de betekenis van JMS, JMR, JMT, JMD, jms.ini en SVC: zie `opleiding-mei-server-installatie-en-migratie.md`.

## 1. Algemene werkwijze

- **Kijk eerst in de SVC** vóór je de klant belt of terwijl je hem aan de lijn hebt: IP-adres van de server, laatste JMR-contact, foutenlog met tijdstippen, status back-ups, klaarstaande update, JMS-versie. (opleiding 13-05-2026, ca. 00:51)
- **Kijk na elke ingreep opnieuw in de SVC** of alles groen is (online back-up, USB/image-back-up). Sommige oplossingen kan je pas de volgende dag bevestigen (blijven de fouten weg?).
- **Herstarten is in veel gevallen de oplossing** bij onverklaarbare blokkeringen of vreemde meldingen (bv. een melding over een maximum aantal records alsof het een Mono-versie is, op een installatie zonder beperking): eerst nagaan wie werkt (`+` → `J` → `T`), iedereen laten stoppen, dan Help → "Alle posten herstarten". Alles waar gebruikers op dat moment mee bezig zijn (bon, factuur, half ingevulde fiche) gaat verloren. (opleiding 28-05-2026, ca. 00:22–00:28)
- Leg de klant niet uit welke knoppen support op afstand heeft (herstart vanuit de SVC, toegang tot het pakket). (opleiding 12-05-2026 namiddag, ca. 01:11)
- Documenteer een oplossing die je door ervaring vindt meteen (ticket/OneNote); veel van deze kennis staat nergens beschreven.

## 2. "Jamadata Desktop wacht op serversessie"

Betekenis: de Jamadata Desktop (JMD) op de werkpost kan geen verbinding maken met de sessie van zijn post op de server. Bron: opleiding 12-05-2026 namiddag (ca. 00:06–00:12), 13-05-2026 (ca. 00:20–00:37).

### Diagnosevolgorde

1. **Eén post of alle posten?** Alle posten tegelijk → serverkant (IP-adres gewijzigd, database gestopt, server uit). Eén post → instellingen of netwerk van die post, of post dubbel in gebruik.
2. **SVC-fiche van de klant: welk IP-adres heeft de server nu?**
   - Rond getal (.50/.100/.150/.200) = bewust ingesteld vast adres.
   - "Raar" eindcijfer (bv. .34, .137) = de server heeft vermoedelijk een **DHCP-adres** gekregen. Dit is bij kleine klanten veruit de meest voorkomende oorzaak: het internet viel even weg, iemand klikte in Windows op "Problemen oplossen", en Windows zette de netwerkkaart op automatisch.
3. **JMD → Configuratie → Instellingen**: vergelijk het ingevulde IP-adres met dat van de server. Na het invullen in een ander veld klikken: het veld wordt groen als het adres bereikbaar is; onderaan komt "lokale server verbonden" en JMD gaat vanzelf terug in het pakket.
4. Klopt het adres niet meer: **neem het scherm van de server over** en zet de server terug op zijn oorspronkelijke vaste IP-adres (procedure: zie server-document § 5.2). Pas niet alle posten aan naar het nieuwe DHCP-adres – dat verandert opnieuw.
5. **Werkpost op een verkeerd netwerk?** Bv. de netwerkkabel is los en de pc is automatisch op (gasten-)wifi gegaan → andere IP-reeks. Test in een opdrachtprompt: `ping <IP-adres van de server>`.
6. **Poorten** (5100–5130 voor JMD, 5000–5005 voor kassa's). Eenmaal opengezet in de Windows-firewall gaan ze niet vanzelf dicht. Wel verdacht: er is recent een andere virusscanner/firewall geïnstalleerd, of andere software (cloudback-up, camera, virusscanner) gebruikt dezelfde poort. → IT'er van de klant.
7. **Postnummer al in gebruik.** Een post kan maar één keer open zijn. Mogelijkheden: een collega gebruikt hetzelfde postnummer, dezelfde pc heeft een tweede Windows-gebruiker met een JMD op een ander/zelfde postnummer, of de post staat open op de server zelf. Dit is moeilijk te achterhalen: alle posten laten aflopen en kijken waar dat postnummer nog ingevuld staat, of de IT'er laten nagaan (bv. met `netstat`) welke pc verbinding maakt op de poort van die post (post 14 ≈ poort 5114 of 5113).

Op de server zelf gebruik je in JMD altijd 127.0.0.1; dan heeft de server-post zelf nooit last van een gewijzigd IP-adres.

## 3. Klant komt niet online in de SVC (JMR)

- Laatste JMR-contact is uren of dagen oud terwijl de heartbeat doorloopt → de service JMR draait niet.
- Meest voorkomende reden bij een nieuwe installatie: de Windows-gebruiker voor Jamadata kon niet aangemaakt worden (domein, geen beheerdersrechten), waardoor de service niet start. Oplossing: zie server-document § 3.
- Na een migratie: nagaan dat JMR op de **oude** server gestopt en uitgeschakeld is, anders rapporteren beide.

(opleiding 12-05-2026 namiddag, ca. 00:34–00:39)

## 4. Pakket start niet na het ophalen van een update

Zie server-document § 8.2. Kort: een update duurt 1–2 minuten; na 10 minuten wachten → icoon "Jamadata server herstarten" op de server, of in JMD Help → "Alle posten herstarten".

## 5. Fouten in de SVC herkennen

| Wat je ziet in de SVC | Waarschijnlijke oorzaak | Actie | Bron |
|---|---|---|---|
| Fout die **ongeveer elk half uur** terugkomt | Defecte of slecht werkende USB-back-upstick | Stick eruit laten nemen of meteen een nieuwe laten insteken; de volgende dag de SVC opnieuw bekijken. Zonder stick moet er wel snel een nieuwe komen. | 20-05-2026 vm, ca. 00:01 |
| Herhaalde fout rond **poort 5000–5005** / "UC server error" | Vreemde verbindingspogingen van buitenaf op openstaande poorten (cloudserver), of Norton op de pc | Poorten enkel laten openzetten voor toestellen van de klant (IT); Norton verwijderen lost het vaak op. | 20-05-2026 vm ca. 00:00; nm ca. 00:00 |
| Kolom USB/kopie in het **rood** | Back-upstick ontbreekt, is defect of heeft een andere stationsletter gekregen | Zie § 7.2. | 13-05-2026, ca. 00:45 |
| Database stopt en start telkens opnieuw; meldingen dat een dump/verzending naar de server mislukt, daarna "kill thread" en herstart (bv. om het anderhalf uur) | Online back-up kan niet gemaakt worden (corrupte of vervuilde databestanden) | Zie § 6. | 20-05-2026 vm ca. 00:14; 21-05-2026 ca. 00:01 |
| "Read/verify fail"-meldingen in bulk | Database ernstig in de problemen; niemand kan nog werken | Vragen of iedereen eruit is, herstart van de JMS; bij herhaling escaleren. | 12-05-2026 nm, ca. 01:11 |
| Mailfouten | Zie document printers/mail/randapparatuur. | | |

## 6. Database blokkeert, crasht of de online back-up komt niet binnen

Dit is een gevorderde ingreep op de server van de klant. De opleider benadrukt dat het telkens zoeken is en dat geen enkele stap gegarandeerd de oplossing is. Voer dit enkel uit als je de procedure beheerst, buiten de werkuren van de klant of met iedereen uit het pakket, en overleg bij twijfel. Bron: opleiding 20-05-2026 voormiddag (ca. 00:14–00:18), 21-05-2026 (ca. 00:01–00:11).

**Symptomen:** gebruikers lopen om de zoveel tijd vast; in de SVC herstart de database telkens; de laatste online back-up die binnenkwam is weken oud; klant klaagt over "dubbele facturen" (zie document Jamadrink-basis, § factuur boeken).

**Stap 1 – Opkuisen**

1. Iedereen uit het pakket.
2. JMT als administrator: Stop + Remove.
3. JMS met de hand starten en sluiten (eventueel herhalen) tot `Jamadata\FAS\LOG` leeg is.
4. De mappen `Jamadata\FAS\SHA` en `Jamadata\FAS\FSD` leegmaken.
   - `SHA`: controlebestanden die gebruikt worden om na te gaan of het doorsturen van de back-up goed verlopen is.
   - `FSD`: structuurbestanden van de database; ze worden bij het starten van de database opnieuw aangemaakt op basis van de structuurdefinitie. De eerstvolgende start duurt daardoor langer. Enkel voor de bestanden die effectief geopend worden, worden ze opnieuw aangemaakt – resten van oude dossiers verdwijnen zo.
5. JMS met de hand starten (kijken of ze proper opstart), sluiten, daarna Install.

**Stap 2 – Test of de bestanden te zippen zijn**

De online back-up werkt door de databestanden te zippen en door te sturen. Lukt zippen niet, dan lukt de back-up niet.

1. Bekijk de map `Jamadata\FAS` in Verkenner. **Bestanden zonder datum (of zonder grootte) zijn corrupt.**
2. Selecteer de bestanden van één dossier, of de hele map `FAS` (duurt ± 1 minuut), of desnoods de hele map Jamadata (5–10 minuten of langer): rechtsklik → Kopiëren naar → Gecomprimeerde (gezipte) map.
3. Lukt het, verwijder dan het testzipbestand. Geeft het een fout, dan weet je welk bestand het probleem is.

**Stap 3 – Corrupte bestanden van een oud dossier uit de weg zetten**

Gaat het om bestanden van een oud dossier dat niet meer gebruikt wordt (de overige bestanden van dat dossier hebben een datum van jaren geleden), **knip** ze dan uit `FAS` en plak ze in een aparte map (in de opleiding `FAS-OLD` genoemd). Niet verwijderen. Het systeembestand `sys.fas` heeft altijd een recente datum (wordt bij elke update bijgewerkt); dat is normaal.

**Opvolging:** in de SVC nagaan of de online back-up opnieuw binnenkomt (na lange onderbreking moet alles in één keer doorgestuurd worden, dat kan even duren) en of de herstarts stoppen. Blijft het crashen, dan is er nog een andere oorzaak → ontwikkeling.

## 7. Back-ups

Bron: opleiding 12-05-2026 namiddag (ca. 00:26–00:30 en 01:00–01:07), 13-05-2026 (ca. 00:45–01:02).

### 7.1 Drie soorten

| Soort | Voor wie | Hoe | Opmerkingen |
|---|---|---|---|
| **Automatische kopie** (in de SVC "USB" of image-back-up genoemd) | Light en Server | Het pakket schrijft elke wijziging automatisch weg naar een ingesteld medium: USB-stick, externe schijf, NAS of een andere map/schijf. Een nieuwe factuur staat binnen ± 5 minuten op het medium. | Dit is **de eerste back-up waar support naar kijkt** bij problemen. De klant moet er niets voor doen. |
| **Manuele volledige back-up** | Iedereen; in Mono de enige lokale mogelijkheid | Via de tandwieltjes rechts onderaan op het hoofdmenu → back-up maken → volledige back-up. Het vraagteken opent een gedetailleerde handleiding met schermafdrukken. | Wordt op een aparte stick gezet die de klant weglegt. Veel gevraagd rond het jaareinde. |
| **Online back-up** | Betalende optie | Het pakket zipt de databestanden en stuurt ze enkele keren per dag (± 4×) door naar Jamadata. | Wordt door de ontwikkelaars geactiveerd; kan niet zomaar door support aangezet worden. Werkt geregeld even niet; daarom is de lokale kopie de eerste referentie. |

### 7.2 Automatische kopie: werking en problemen

- **Medium en stationsletter.** Klassiek een USB-stick (min. 32 GB) op een vaste letter achteraan in het alfabet (S:). Een stick insteken die de juiste letter krijgt, volstaat: niet formatteren, niets instellen – het pakket begint vanzelf te kopiëren.
- **Sticks slijten.** Door het zeer grote aantal schrijfbewegingen is een stick bij sommige klanten na een half jaar tot een jaar defect. Alternatieven: externe harde schijf, NAS (duurder; IT moet de Jamadata-gebruiker toegang geven) of een map op een andere schijf.
- **Valmap als het medium ontbreekt.** Is de stick weg of defect, dan schrijft het pakket de kopie tijdelijk in een alternatieve map binnen `Jamadata` op de server (gehoord als "kopie-alt"; *exacte mapnaam te verifiëren*). Zodra de echte back-up weer werkt, wordt die map leeggemaakt. Gevolg: op een server met weinig schijfruimte kan de schijf hierdoor vollopen.
- **Rood in de SVC** betekent: klant loopt risico, zeker als hij ook geen online back-up heeft. Bel de klant op. Typische oorzaken: stick eruit getrokken, stick defect, stick in een andere USB-poort gestoken waardoor hij een andere letter kreeg.
- **Oplossen:**
  1. Eenvoudigst: in Windows de stationsletter van de stick terugzetten naar de verwachte letter (Schijfbeheer → rechtsklik op het volume → Stationsletter en paden wijzigen). Dan hoef je jms.ini niet te openen.
  2. Anders: het back-uppad in jms.ini aanpassen (zie server-document § 2); enkel de schijf/het voorvoegsel wijzigen, `Jamadata\Copy` laten staan.
  3. Controleer in Verkenner dat op de doelschijf de map wordt aangemaakt en gevuld, en in de SVC dat de status goed wordt.
- **Voorzichtig met Schijfbeheer.** Wijzig nooit de letter van C: of van een schijf met programma's. Moet een defecte stick geformatteerd worden, controleer dan twee-drie keer dat je de juiste schijf hebt (kijk naar de grootte: sticks zijn meestal 32/64/128 GB).

### 7.3 Back-ups door de IT'er van de klant

- Een kopie of image van een **draaiende** `J:\Jamadata` is **geen betrouwbare back-up**: de recentste wijzigingen zitten nog in `FAS\LOG`, en het is voorgekomen dat bij het terugzetten van zo'n "volledige image" de map `FAS` gewoon leeg was.
- Advies aan IT'ers: maak je eigen (cloud)back-up van de **map waarin Jamadata zijn automatische kopie zet**, niet van de live-map. De live-map erbij nemen mag, maar reken er niet op.
- Grote klanten en cloudservers: geen stick. Spreek met de IT'er een locatie af (andere schijf, andere server, NAS) waar Jamadata zijn kopie schrijft en waarvan de IT'er verder een back-up neemt.

### 7.4 Manuele volledige back-up: verloop en valkuilen

1. Start de back-up **op de server**, niet op een bijpost. Op een bijpost wordt het zipbestand eerst op de server gemaakt en moet het daarna naar de post overgezet worden; bij grotere klanten (zip van 2–4 GB) duurt dat zeer lang of loopt het vast, waarna het bestand met de hand verwijderd moet worden.
2. Het pakket controleert of iedereen uit de schermen is en begint de bestanden te kopiëren en te zippen. Je ziet de voortgang (bestandsnaam, aantal bestanden; de grootste bestanden duren het langst, de rest gaat snel).
3. **Tijdens deze fase kan niemand werken**: de andere posten tonen dat de server bezig is met onderhoudswerkzaamheden.
4. Daarna verschijnt "Het back-upbestand wordt nu ontvangen, wacht tot het helemaal ontvangen is en sluit dan pas af": vanaf dan kunnen de andere posten weer werken.
5. Tot slot toont het pakket het scherm om de back-up op een stick te zetten.
6. Zit er geen stick in, dan blijft het pakket **bij elke opstart** melden dat de back-up nog niet op een stick gezet is, tot dat gebeurd is of de melding verwijderd wordt.

## 8. Checklist "wat vraag/controleer ik eerst"

| Klacht | Eerst controleren |
|---|---|
| "Wacht op serversessie" op alle posten | SVC: IP-adres server (DHCP?); server aan? database gestart? |
| "Wacht op serversessie" op één post | IP in JMD-instellingen; netwerk van die pc (ping); postnummer dubbel in gebruik |
| Pakket blijft hangen na update | Hoe lang al? > 10 min → Jamadata server herstarten |
| Iedereen zit vast / rare melding | Wie werkt er (`+` `J` `T`)? → alle posten herstarten |
| Telkens kort vastlopen, SVC toont herstarts | Online back-up/dump lukt niet → § 6 |
| Fout elk half uur in SVC | USB-stick defect |
| Back-up rood in SVC | Stick aanwezig? letter? defect? |
| Klant vraagt jaareindeback-up | Op de server uitvoeren, stick klaar, iedereen eruit |
| Trager sinds verhuis naar cloudserver | Capaciteit van de virtuele server (aantal cores, RAM, schijfsnelheid) is zaak van de hardwareleverancier; zelfde software is niet automatisch sneller in de cloud (opleiding 20-05-2026 nm, ca. 00:01) |

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):

- gedocumenteerde kennisoverdracht VI-20260507_141735-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260512_150237-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260513_094305-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260520_100445-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260520_143704-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260521_101124-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260528_100522-Opname van vergadering.txt
