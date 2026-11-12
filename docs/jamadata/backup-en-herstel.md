# Back-up en herstel van Jamadata

Gebruik dit document voor: uitleggen welke back-ups Jamadata maakt (permanente schaduwkopie op USB/NAS, manuele back-up, Jama360 online back-up, DVD-back-up), een klant begeleiden bij het maken van een volledige manuele back-up op USB-stick, back-upproblemen oplossen (stick niet herkend, stick vol, back-up komt niet door) en weten hoe een back-up teruggezet wordt.

## 1. Waarom een eigen back-upsysteem?

Op de harde schijf staan vier soorten gegevens: (1) Windows en meegeleverde programma's, (2) aangekochte programma's zoals Office, (3) eigen documenten/e-mails van de klant en (4) de Jamadata-programma's en -gegevens (artikelfiches, facturen, offertes, boekhouding, ...).

**Belangrijk:** het is **niet aan te raden** de Jamadata-gegevens met standaard back-upprogramma's te kopiëren of integraal naar een algemene online back-updienst te sturen. Die systemen kennen de transactietoestand van de database niet en kunnen onvolledige of foutieve back-ups maken (valse veiligheid). Gebruik de back-upmechanismen van Jamadata zelf. (Een image-back-up van de volledige server door de IT-partner komt in de praktijk wel voor als extra laag.)

De back-up van eigen documenten en e-mails (punt 3) is de verantwoordelijkheid van de klant.

## 2. Overzicht van de back-upsoorten

| Soort | Versie | Hoe | Opmerkingen |
|---|---|---|---|
| **Interne permanente back-up (schaduwkopie)** | Light en Server (niet bij Mono) | Automatisch en doorlopend naar het pad `CopyPath` uit `JMS.ini` (standaard `S:\jamadata\Copy`): USB-stick achteraan in de server, externe schijf, NAS, netwerkstation of aparte partitie | Stoort de gebruikers niet. Enkele keren per dag een "archief-foto" (snapshot) van de belangrijkste bestanden. |
| **Manuele back-up** | Alle versies (bij Mono de enige back-up) | Via de masterfuncties (tandwieltjes) punt 2; legt het systeem tijdelijk stil en maakt een gezipte back-up van alle gegevens- en werkbestanden | Naar een **aparte** USB-stick die buiten het bedrijf bewaard wordt. Verantwoordelijkheid van de klant, liefst dagelijks. |
| **Jama360 online back-up** | Light/Server met Jama360-contract (betalende optie) | Automatisch via internet naar de back-upserver van Jamadata; omvat data en programma's van het pakket, de kassa's en de PDA's | Zie §5. Klanten met online back-up hoeven geen manuele back-up te maken. |
| **DVD-back-up** | Aanvulling op de online back-up | Door Jamadata aangemaakt op basis van de online back-up | Zie §5. |

Samengevat: Mono-klanten moeten zelf manueel back-uppen. Serverklanten hebben de interne permanente back-up, maar moeten zich extra beveiligen tegen brand, diefstal of een defecte stick: ofwel dagelijks een manuele back-up buiten de kantooruren, ofwel de online back-up.

## 3. Interne permanente back-up (schaduwkopie)

### Werking
- Bestemming: `CopyPath=` in `[CopySettings]` van `\jamadata\prog\JMS.ini`; `CopyJamaSubDirs=PROG|KASSA|JamaPDA|FTKOPIE` bepaalt welke submappen naast de database mee gekopieerd worden.
- De server maakt op de bestemming automatisch de mappen `jamadata\Copy\Fas\...` aan en begint binnen enkele minuten bestanden te schrijven.
- Inhoud van `Copy` (uit opleiding "vid backup", gesproken bron):
  - de gewone bestanden/zipbestanden = de **laatste** back-up van elk bestandstype; ze worden telkens overschreven met de nieuwste versie;
  - daarnaast **snapshots** (`snapshot-fas-<datum>.zip`), meerdere per dag en per dossier. De server ruimt zelf op: van de laatste dagen blijven er meerdere per dag (om de paar uur), van oudere periodes nog één per maand, en van afgesloten jaren op termijn nog één per jaar.
  - De back-up groeit dus traag mee met de data (en met het aantal kopiedossiers, bv. de jaarlijkse interne kopie), maar explodeert niet.
  - Mappen die opzij gezet zijn als `..._old` worden niet mee geback-upt.
- **De back-up kan niet uitgezet worden.** Bestaat het ingestelde pad niet (stick weg, verkeerde stationsletter), dan schrijft de server de kopie naar **`\jamadata\CopyAlt`** op de dataschijf zelf. Staat er in `CopyAlt` recente data, dan wijst dat op een probleem met het back-upmedium.
- Volgens de helpdeskopleiding (2020) wordt de kopie naar de stick ongeveer om de 5 minuten bijgewerkt.

### Medium
- USB-stick van min. 32 GB (USB 3.0), **achteraan** in de computer zodat hij niet per ongeluk verwijderd wordt, liefst NTFS, liefst stationsletter S:.
- In een datacenter/cloudomgeving of wanneer de IT-partner dat verkiest: een aparte partitie of schijf (bv. `E:\jamadata\Copy`). Hou er rekening mee dat dit dan vaak fysiek dezelfde schijf is; de online back-up en/of een image-back-up van de IT-partner blijft nodig.

### Back-upbestemming wijzigen
1. Open `\jamadata\prog\JMS.ini` (op afstand: via bestandsoverdracht naar je eigen pc halen, aanpassen en terugzetten).
2. Pas `CopyPath=` aan naar de juiste schijf (bv. `S:\jamadata\Copy`). Een oude regel kan je uitschakelen door er een teken (bv. `*`) voor te zetten of ze te verwijderen.
3. Bewaar. Controleer in Verkenner of op de nieuwe bestemming de map `jamadata\Copy` verschijnt (F5). Gebeurt dat niet meteen: herstart de Jamadata Server (icoon "Herstarten Jamadata Server"); in het uiterste geval de computer herstarten.
4. Controleer in de SVC dat er geen USB-/back-upfout meer staat.

Alternatief: geef het medium de stationsletter die in `CopyPath` staat (zie `it-remote-support-vpn-shares.md` §9).

## 4. Manuele (volledige) back-up op USB-stick

**Wie/waar:** op elk scherm waar de **masterfuncties** geactiveerd zijn (groen icoon met tandwieltjes rechts onderaan het hoofdmenu). Dat is zeker de hoofdcomputer, meestal ook enkele werkposten; activeren kan per werkpost via **+ > J > 4** (Instellingen werkposten). Ontbreekt het icoon: Jamadata contacteren. De back-up gaat het best en het snelst **op de hoofdcomputer**. Support start een manuele back-up nooit via een remote sessie op een werkpost op afstand (het zipbestand moet dan over de lijn; > 2,5 GB loopt vast, zie `server-jms-storingen.md`).

**Nodig:** een aparte USB-stick (min. 2 GB; op 8-16 GB passen tientallen back-ups). Label hem "Manuele Jamadata Backup". Gebruik **niet** de stick van de permanente back-up.

### Stappen
1. Ga naar het **hoofdmenu Voorraadbeheer of Boekhouding**.
2. Klik rechts onderaan op het **groene icoon met de tandwieltjes** > "Menu masterfuncties".
3. Kies **2. Volledige backup nemen van het systeem op USB-stick**.
4. Waarschuwing: alle schermen/werkposten moeten uit het programma zijn of op het hoofdmenu staan. Verwittig de gebruikers en bevestig met **F4**. Tijdens de back-up kan niemand werken (doe het voor of na de kantooruren).
5. De server stopt en maakt de back-up; het scherm toont de voortgang. Daarna wordt het back-upbestand naar de werkpost gestuurd waar de back-up aangevraagd is (voortgangsbalk links onderaan).
6. Het venster **"Beheren backup-bestanden Jamadata systeem"** opent. Het bestand staat nu op de lokale computer maar **moet** nog naar een externe schijf/stick.
7. Steek de stick in. Eerste keer: klik op **Aanmaken** bij de stationsletter van de stick (maakt de map `Jamadata\Backup` aan; maar één keer nodig per stick).
8. Klik bovenaan op **"Kopieer backup(s) nu naar de hieronder geselecteerde schijf"**.
9. Het venster toont hoeveel back-ups op de stick staan en hoeveel er nog bij kunnen. Oude back-ups kan je hier selecteren en verwijderen (of openen).
10. Sluit het venster, verwijder de stick veilig en bewaar hem **buiten het bedrijf** (privé, kluis).

### Inhoud
Een volledige back-up van het hele Jamadata-systeem: alle gegevensbestanden en programma's, plus werkbestanden (gegenereerde statistieken, tijdelijke bestanden).

### Tips en problemen
| Probleem | Oplossing |
|---|---|
| Het pakket herkent de USB-stick niet | Maak op de stick manueel een map `Jamadata` met daaronder een map `backup`, start Jamadata Desktop opnieuw en probeer opnieuw. |
| Windows herkent de stick niet | Stationsletter wijzigen via Schijfbeheer (`it-remote-support-vpn-shares.md` §9). |
| Stick vol | Oude back-ups wissen in het beheervenster, of een nieuwe stick. |
| Foutmelding JMH/"Exit of JMH for Post-x" na een manuele back-up op afstand | Te groot back-upbestand in `\jamadata\spool\toclient\post-x\`: verwijderen. |

Gebruik meerdere sticks afwisselend om het risico te spreiden.

### Bewaarplicht (ter info voor de klant)
Boekhoudkundige documenten (papieren controlebanden van de kassa, facturen, bankuittreksels, grootboeken, bestel- en leveringsbonnen) moeten zeven jaar bewaard worden (tot het verstrijken van het zevende boekjaar), en leesbaar blijven. Documenten met handgeschreven aanvullingen (bv. leeggoedverrekening) bewaar je best ook op papier.

## 5. Jama360 online back-up en DVD-back-up (optie)

- Betalende service bij het Jama360-onderhoudscontract; vereist een permanente breedbandverbinding. Uitgaand verkeer via poort 80 (geen echt HTTP; zie firewallopmerkingen in `server-jms-storingen.md`).
- Wijzigingen worden doorlopend naar de back-upserver van Jamadata gestuurd, zonder de gebruikers te storen. Een controlealgoritme vergelijkt de gegevens; bij een verschil herstart de back-up automatisch.
- Eén keer per dag (meestal 's nachts tussen 1u en 2u) wordt een gecontroleerde kopie van de actuele gegevens gemaakt, die minstens 60 dagen bewaard blijft.
- **Frequentie – bronnen spreken elkaar tegen:** de Backup-FAQ (2.02, 2013) zegt "minstens één keer per uur" (max. 1 uur vertraging); de helpdeskopleiding (2020) zegt "4 x per dag". Het actuele schema per klant is te verifiëren; kijk voor de werkelijke toestand naar **BackupUpdated** in de SVC.
- Op de server van de klant bevat de map `\jamadata\Dump` de bestanden die naar Jamadata gestuurd zijn/worden.
- **DVD-back-up:** door Jamadata gemaakt op basis van de online back-up (historisch: jaarlijks de toestand eind kalenderjaar; maandelijks bij een Butler-contract), beveiligd met een uniek wachtwoord. Bevat de bestanden van facturatie en boekhouding, artikelen, verkoophistorieken, kopie van elke factuur en via de server verstuurde e-mails; **geen** werkbestanden, afsluitdocumenten, gegenereerde statistieken of bewaarde Excel-/PDF-bestanden. Of deze dienst vandaag nog zo geleverd wordt: te verifiëren.
- Intern: de online back-ups staan per klantcode op de back-upserver van Jamadata; daar is ook de actuele `JMS.ini` van de klant terug te vinden.

## 6. Back-upproblemen: controlelijst

1. Welke back-up is het: permanente kopie (USB/NAS/partitie), manuele back-up of online back-up? Een werkende online back-up bewijst niet dat de USB-kopie werkt, en omgekeerd.
2. SVC: kolommen **USB**, **BackupUpdated** (rood = komt niet door), **Err** (dubbelklik voor detail).
3. Medium aanwezig en leesbaar? Stationsletter nog dezelfde als in `CopyPath`? Staat er recente data in `\jamadata\CopyAlt` (= bestemming niet gevonden)?
4. Schijfruimte: `LastError=112` = medium vol.
5. Recente datums in `<medium>\jamadata\Copy\Fas`? (Een bestand met recente datum is een goede aanwijzing, geen bewijs van herstelbaarheid.)
6. Geen heartbeat/online back-up: `Dump` leegmaken en JMS herstarten; firewall/IPS op poort 80 nakijken (zie `server-jms-storingen.md`).

| Melding | Betekenis | Actie |
|---|---|---|
| USB uit/rood in SVC | Stick ontbreekt, is defect of heeft een andere letter | Stick/letter herstellen; anders vervangen |
| `Cannot copy ... snapshot-fas-....zip to s:\jamadata\Copy\..., LastError=112` | Back-upmedium vol | Groter medium / partitie vergroten |
| `[JMT] Exit of JMS and restarted process` | Probleem met online back-up of USB-stick | Stick formatteren/vervangen of (intern) back-upmap van de klant op de server hernoemen |
| Server herstart niet meer | Online back-up komt niet tijdig binnen | Oude dossiers opzij zetten |

**Waarschuwing rond formatteren:** de oude server-FAQ noemt "USB-stick formatteren" als oplossing. Het voorlopige kennisartikel KA-004 waarschuwt terecht: formatteer een onleesbare back-upstick **niet als eerste stap**; het kan de enige resterende herstelkopie zijn. Controleer eerst of er een andere bruikbare back-up is (online back-up, `CopyAlt`, manuele back-up) en formatteer of vervang pas daarna.

## 7. Back-up terugzetten (restore)

Een restore op een productiesysteem gebeurt enkel door een bevoegde Jamadata-medewerker, met akkoord van de klant over het herstelpunt (alles wat na dat punt ingegeven is, gaat verloren).

Beschreven werkwijze (Onenote "Jamadata Server", notitie 18/11/2024):
1. Kopieer de back-upbestanden naar de map **`\jamadata\Restore`**.
2. Start de JMS **handmatig**: `\jamadata\Prog\JMS.exe`.
3. De JMS doet dan automatisch een restore van de database.

Aandachtspunten:
- De map `Restore` dient uitsluitend hiervoor: zet er nooit zomaar bestanden in.
- Stop eerst de normale werking (JMT stop/remove, zie `server-jms-storingen.md` §4.2) zodat de database niet in gebruik is – volgorde niet expliciet in de bron, te verifiëren.
- Er bestaat in de bronnen geen uitgeschreven, gevalideerde restore-testprocedure.
- Bij een defecte server: de gegevens van de schaduwkopie (stick) kunnen op een andere pc ingelezen worden via een nieuwe installatie (zie `installatie-migratie-naar-nieuwe-server.md`).

## Bronnen
- Jamadrink/Handleidingen modules: "0005A - Backup maken op USB-stick.docx"
- Jamadrink/Handleidingen modules: "1 - Jamadata backup Faq 2.x.docx" (Backup FAQ 2.02)
- Jamadrink: "Jamadata Server systeemvereisten.docx" (vragen over interne en online kopie)
- FAQ: "Opleiding Helpdesk Jamadata.docx"
- FAQ / Jamadrink: "FAQ Jamadata SERVER.docx"; Onenote: "Jamadata Server.pdf" (restore-notitie)
- FAQ/Kennisartikelen: "KA-004_Backups_en_herstel.md" (gedeeltelijk gevalideerd)
- Transcripties opleidingen: "vid backup.txt", "[klant]_Migratie_20260601_162649.txt", "[klant] Migratie Server-20260611_132355-Opname van vergadering.txt" (gesproken bronnen)
