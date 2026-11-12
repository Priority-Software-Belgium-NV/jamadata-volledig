# Boekhouding in Jamadata: CODA-bestanden automatisch inboeken, automatische betaalopdrachten (SEPA) aan leveranciers en domicilieringen van klanten

Gebruik dit document voor: vragen over de module "Automatisch inboeken CODA-bestanden" (bankafschriften inlezen en toewijzen), de module "Automatische betaalopdrachten leveranciers" (SEPA Credit Transfer, XML-bestand voor de bank/Isabel) en de module "Automatische domicilieringsopdrachten klanten" (SEPA Direct Debit): eerste instelling (grootboekrekeningen 5810xx, journaal type 7, IBAN/BIC), dagelijkse werking, het schrappen van een geboekte betaallijst en veelvoorkomende problemen (leverancier wordt overgeslagen, betaling niet automatisch toegewezen, CODA-bestand niet zichtbaar).

Alle drie zijn modules **in optie**. Is de module niet geinstalleerd, dan verschijnt fout 12.

## 0. Menunummers verschillen per versie

De bronnen spreken elkaar tegen over de menunummers; kijk altijd naar de omschrijving op het scherm van de klant.

| Module | Volgens modulehandleiding | Volgens gebruikershandleiding 2014 / andere vermelding |
|---|---|---|
| CODA inboeken | Hoofdmenu boekhouding, punt 2 en dan 4 (`B.2.4`) | `2.3` "Automatisch inboeken bankuittreksels (CODA-Isabel)"; `2.4` heet daar "OGM-verwerking" |
| Betaalopdrachten leveranciers | `B.5.0.2` | de CODA-handleiding verwijst naar de betaallijsten als "punt B.2.3" |
| Domicilieringen klanten | `B.5.0.1` | in de eigendommen-handleiding staat "Beheer eigendommen - huren" ook onder B.5.0.1 |

## 1. Hoe de drie modules samenwerken

1. Met de **betaalopdrachten** (of domicilieringen) kiest u welke facturen betaald/geind worden. De gekozen facturen worden **meteen afgeboekt** op de leverancier/klant via een **overschrijvingsjournaal** (type 7, bv. journaal 35) met als tegenrekening een **tussenrekening 5810xx**. Het XML-bestand gaat naar de bank.
2. De bank voert de lijst uit als **één totaalbedrag**. Op het bankuittreksel moet u dus enkel dat totaal tegenboeken op de rekening 5810xx - niet de afzonderlijke leveranciers/klanten.
3. Met de **CODA-module** worden de bankafschriften ingelezen. Klantbetalingen met gestructureerde mededeling worden automatisch aan de factuur toegewezen; de totalen van de betaallijsten worden automatisch op de 5810xx-rekening geboekt. Alleen de uitzonderingen blijven manueel.

Het saldo van een rekening 5810xx is dus het bedrag van de betaallijsten die al in Jamadata geboekt zijn maar nog niet op een bankuittreksel verschenen.

## 2. Automatische betaalopdrachten leveranciers (SEPA)

### 2.1 Waarvoor

Betalingen aan leveranciers uitschrijven en als één betaalopdracht naar de bank sturen. Standaard: Europese overschrijving **SCT - SEPA Credit Transfer, pain.001.001.03**. De computer toont de vervallen facturen (en facturen waarop nog disconto kan; het disconto wordt meteen verrekend); u beslist per factuur. De betalingen komen in een **XML-bestand** dat via het bankprogramma of Isabel doorgestuurd wordt.

### 2.2 Instellen voor eerste gebruik

Maximaal **3 bankrekeningen**; per bankrekening best een apart journaal.

Per bankrekening:
1. **Grootboekrekening** (`B.9.3.2`): bv. nummer `581000`, omschrijving "Betalingen <bank>". Eventueel `581100` en `581200` voor de 2de en 3de bankrekening.
2. **Journaal** (`+.3`, enkele keren `F8` tot het scherm met de journalen): op een vrije lijn
   - Nr: `35`
   - Type: `7` (overschrijvingsjournaal)
   - Benaming: bv. "Uitg.Bet.<bank>"
   - Fin.Reken: `581000`
   - Eventueel journaal 36 en 37 voor de andere bankrekeningen.
3. In `+.3` moeten ook de "centralisatierekening leveranciers" en de rekening "bekomen disconto" ingevuld zijn (anders fout 28).

**Leveranciers controleren**
- Op elke leveranciersfiche moeten **IBAN** en **BIC** ingevuld zijn. Ontbreken ze of zijn ze fout, dan wordt die leverancier **overgeslagen**.
- Leveranciers die via **domiciliering** betaald worden: vul als IBAN `DOMICILIERING` in (of gewoon `DOM`, de computer vult aan). Deze leverancier wordt dan bewust overgeslagen in het betaalprogramma.
- Oude Belgische rekeningnummers in bulk omzetten naar IBAN/BIC: neem eerst een back-up, neem dan op het hoofdmenu **`+.H.2`** (Invullen Iban/Bic op leveranciersfiches). Het programma controleert alle leveranciers: is IBAN/BIC niet ingevuld, dan wordt hij berekend uit het Belgische rekeningnummer en ingevuld.

### 2.3 Werking (B.5.0.2)

| Veld | Uitleg |
|---|---|
| Overschrijvingsdatum | Datum waarop de bank de betaling moet uitvoeren. |
| Vervallen facturen overlopen (J/N) + periode | Bij `J` worden de onbetaalde facturen voorgesteld die in de periode vervallen. Begindatum best openlaten zodat lang vervallen facturen ook verschijnen. |
| Discontofacturen overlopen (J/N) + periode | Bij `J` worden onbetaalde facturen voorgesteld waarop disconto afgetrokken mag worden. Bedrag en vervaldatum disconto worden bepaald bij het inboeken van de aankoopfactuur; de vervaldatum disconto moet tussen de twee datums van de periode liggen. |
| Selectie te gebruiken bankrekening (1-3) | Langs welke van de (onderaan ingestelde) bankrekeningen betaald wordt. |
| Leveranciers afboeken in boekhouding | Of de betaalde facturen ook afgeboekt worden. |
| Betalingen uitschrijven voor bankprogramma | Of het XML-bestand aangemaakt wordt (bv. voor Isabel). |
| Selectie 1 leverancier | Leeg = alle leveranciers alfabetisch overlopen. |

Tabel onderaan het scherm (per bankrekening 1-3):

| Kolom | Uitleg |
|---|---|
| Journl | Journaal waarop de betalingen tegengeboekt worden (35, 36, 37) |
| IBAN-rekening / BIC-code | Eigen rekeningnummer en BIC |
| Naam XML-bestand | Naam waaronder het bestand uitgeschreven wordt en die in het bankprogramma gekozen wordt om te importeren. Zonder ".XML" ingeven; **enkel letters en cijfers** (geen `. , ; "`). |

Bij het verdergaan worden de leveranciers alfabetisch overlopen; per leverancier met vervallen facturen worden die getoond. U kan facturen **afvinken** (niet betalen) of een **ander te betalen bedrag** intikken (= voorschot/gedeeltelijke betaling).

### 2.4 Tips en regels

- Controleer **bij het inboeken van de aankoopfactuur**: de mededeling (zoals op de factuur; gaat mee naar de bank), het disconto (bedrag + vervaldatum) en de vervaldatum. Disconto en betalingstermijn kunnen op de leveranciersfiche ingesteld worden, maar controleer per factuur.
- **Creditnota's**: het programma zoekt de gunstigste combinatie (facturen samennemen zodat de volledige creditnota afgetrokken kan worden).
- **Lijst van de geboekte betalingen** opnieuw afdrukken: druk het betreffende journaal af (bv. 35) via B.5.1.
- **Een geboekte betaallijst als geheel schrappen**:
  1. Ga naar het rekeningoverzicht (`B.4`).
  2. Roep een leverancier op die op de lijst staat.
  3. Noteer het **journaal** (bv. 35) en het **volgnummer** van de betaling.
  4. Schrap via punt **`U`** (verborgen toets hoofdmenu) de volledige boeking: **alle** betalingen van die betaallijst worden geschrapt.
- **Bankuittreksel inboeken**: enkel het **totaalbedrag** van de lijst tegenboeken op grootboekrekening 581000 (581100, ...); de bank geeft maar één betaling.

### 2.5 Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Leverancier verschijnt niet in het betaalvoorstel | IBAN/BIC ontbreekt of is fout op de leveranciersfiche; of IBAN staat op DOMICILIERING; of de factuur vervalt buiten de opgegeven periode; of er is een selectie op 1 leverancier. |
| Factuur met disconto wordt niet voorgesteld | "Discontofacturen overlopen" staat op N of de vervaldatum disconto valt buiten de periode; disconto niet ingevuld bij het inboeken. |
| Bankprogramma vindt/aanvaardt het bestand niet | Controleer de naam van het XML-bestand (enkel letters/cijfers, zonder extensie ingegeven) en of "uitschrijven voor bankprogramma" aanstond. Waar het bestand precies terechtkomt, staat niet in de bron (te verifieren per installatie). |
| Fout 28 bij het starten | "Centralisatierekening leveranciers" of "bekomen disconto" ontbreekt in `+.3` of bestaat niet in het rekeningplan. |
| Lijst is fout geboekt (verkeerde datum/bank) | Volledige lijst schrappen via B.4 + `U` en opnieuw maken. Is het bestand al naar de bank gestuurd, dan eerst nagaan wat de bank uitgevoerd heeft. |
| Saldo op 5810xx loopt niet leeg | Het totaal van de betaallijst is op het bankuittreksel niet (of per leverancier in plaats van als totaal) tegengeboekt op 5810xx. |

(De oorzaken in deze tabel zijn afgeleid uit de regels die de handleiding beschrijft.)

## 3. Automatische domicilieringsopdrachten klanten (SEPA)

### 3.1 Waarvoor

Vervallen klantfacturen via domiciliering innen en als één bestand naar de bank sturen. Standaard: Europese domiciliering **pain.008.001.02**. Werking spiegelbeeldig aan de betaalopdrachten: de computer stelt de vervallen facturen (en discontofacturen) voor, u beslist; de aangeboden facturen worden direct tegengeboekt op de klant zodat achteraf enkel het totaal van de lijst afgeboekt moet worden. Het XML-bestand gaat via het bankprogramma of Isabel naar de bank.

### 3.2 Instellen voor eerste gebruik

Maximaal 3 bankrekeningen. Per bankrekening:
1. Grootboekrekening via `9.3.2`: bv. `581000` "Domicilieringen Bank1" (eventueel 581100, 581200).
2. Journaal via `+.3` (enkele keren `F8`): Nr `35`, Type `7`, benaming bv. "Dom.Bet. Bank1", Fin.Reken `581000` (eventueel 36 en 37).

Let op: de voorbeelden gebruiken dezelfde nummers (journaal 35, rekening 581000) als bij de leveranciersbetalingen. Wie beide modules gebruikt, kiest best verschillende journalen/rekeningen voor uitgaande betalingen en voor domicilieringen (aanbeveling, niet letterlijk in de bron).

**Domicilieringsklanten controleren** - op de klantenfiche moeten correct ingevuld zijn:
- IBAN-rekening
- BIC-code
- **mandaat**, **datum** van het mandaat en **selectie bank** (1-3, zie de tabel onderaan het programmascherm)

### 3.3 Werking (B.5.0.1)

| Veld | Uitleg |
|---|---|
| Overschrijvingsdatum | Datum waarop de bank de inning moet uitvoeren. |
| Vervallen facturen overlopen (J/N) + periode | Begindatum best openlaten. |
| Discontofacturen overlopen (J/N) + periode | Vervaldatum disconto moet in de periode liggen; disconto wordt bepaald bij het ingeven van de verkoopfactuur. |
| Selectie te gebruiken bankrekening (1-3) | Langs welke bankrekening geind wordt. **Enkel klanten met deze bankselectie op hun fiche worden genomen.** |
| Klanten afboeken in boekhouding (J/N) | Of de facturen afgeboekt worden. |
| Domicilieringen uitschrijven voor bankprogramma (J/N) | XML-bestand aanmaken. |
| Selectie 1 klant | Leeg = alle klanten alfabetisch. |

Tabel onderaan: per bankrekening het journaal, eigen IBAN/BIC en de naam van het XML-bestand (zonder ".XML", enkel letters en cijfers).

Per klant met vervallen facturen kan u facturen afvinken of een ander bedrag intikken (= voorschot).

### 3.4 Tips

- Controleer bij het maken van de factuur het disconto (bedrag + vervaldatum) en de vervaldatum; instelbaar op de klantenfiche.
- Creditnota's: het programma zoekt de gunstigste combinatie.
- Lijst van geboekte inningen: het betreffende journaal afdrukken (bv. 35).
- Een geboekte lijst als geheel schrappen: via punt **`U`**; journaal en volgnummer staan op de afgedrukte lijst.
- Bankuittreksel: enkel het totaalbedrag tegenboeken op 581000 (581100, ...).

### 3.5 Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Klant met domiciliering wordt niet voorgesteld | IBAN, BIC, mandaat of mandaatdatum ontbreekt; "selectie bank" op de klantenfiche verschilt van de gekozen bankrekening; factuur vervalt buiten de periode. |
| Geweigerde/teruggekeerde inning | Niet beschreven in de bron. De factuur is in Jamadata al afgeboekt; de afboeking moet rechtgezet worden (te bespreken met een senior). |

(De eerste rij is afgeleid uit de voorwaarden in de handleiding.)

## 4. Automatisch inboeken CODA-bestanden

### 4.1 Waarvoor

Het inboeken van bankafschriften automatiseren. Via het bankprogramma worden de afschriften als **CODA-bestand** opgeslagen; de module leest ze in en boekt ze. Ondersteunt **CODA-standaard versie 2.3.A**.

- Op de verkoopfacturen staat een **gestructureerde mededeling**. Geeft de klant die mee bij zijn betaling, dan wijst de computer de betaling automatisch toe aan de juiste factuur.
- Met de module betaalopdrachten worden ook de uitgaande betaallijsten automatisch toegewezen.
- Alleen de "speciallekes" blijven manueel.

Start: hoofdmenu boekhouding, punt 2 en dan 4 (zie hoofdstuk 0 voor afwijkende nummering).

### 4.2 Instellen voor eerste gebruik

Maximaal **5 bankrekeningen**; voor elke rekening moet een **financieel journaal** bestaan. Start het programma en druk op het **groene wieltje** rechtsonder.

| Parameter | Uitleg |
|---|---|
| IBAN rekeningnummer | Het eigen bankrekeningnummer. |
| Journaal | Het overeenkomstige financiele journaal waarlangs geboekt wordt. |
| Omschrijving journaal | Wordt automatisch ingevuld. |
| Rekeningnummer betaallijsten | De grootboekrekening van het journaal dat gebruikt wordt bij de automatische betaallijsten (SEPA) voor deze bankrekening (bv. 581000). |
| Rekeningnummer stortingen | De grootboekrekening waarop stortingen van geld geboekt worden (wachtrekening geldbewegingen) voor deze bankrekening. |
| Map CODA-bestanden | De plaats **op de hoofdcomputer (server)** waar de CODA-bestanden opgeslagen worden. Meestal de map `Share` die al in de map Jamadata bestaat, dus doorgaans `..\share\coda\`. **De afsluitende `\` niet vergeten.** De computer die de CODA-bestanden met het bankprogramma afhaalt, moet **volledige toegang** tot deze map hebben. |
| Samenstelling eigen gestructureerde mededeling | Standaard vast geprogrammeerd: meestal **klantnummer (5 cijfers) + factuurnummer (5 cijfers) + 2 controlecijfers**. Wijkt de installatie af, dan kan de juiste samenstelling hier ingegeven worden. |
| Detail van groepsoverschrijvingen NIET tonen | Aangevinkt = de individuele betalingen van een betaallijst worden niet getoond/afgedrukt. |
| Wachtrekening voor alle betalingen | Indien ingevuld worden **alle** uitgaande betalingen (negatieve bedragen) op deze rekening geboekt. Enkel invullen als de aankoopfacturen NIET in Jamadata ingegeven worden (= enkel debiteurenbeheer). |

De juiste journalen en rekeningnummers vindt u in `+.3` (enkele keren `F8` tot het scherm met de journalen).

In de parameters toont **`F10` "toon gekoppelde rekeningen"** het overzicht van de bankrekeningnummers die aan een klant, leverancier of grootboekrekening gekoppeld zijn (max. 250), zie 4.4.

### 4.3 Lijst te verwerken CODA-bestanden

Bij het openen verschijnt meteen het overzicht van de nog te verwerken bestanden (opgeslagen met het bankprogramma in de CODA-map). Per bestand zijn er iconen om:
- een **PDF-lijst** te maken met alle verrichtingen van het bestand;
- het bestand te **openen om te boeken**;
- het bestand te **verwijderen** als het niet geboekt moet worden.

Een verwerkt (geboekt) bestand verdwijnt uit de lijst en komt in de "vuilbak"; via het vuilbak-icoon kunnen verwerkte bestanden nog geraadpleegd of definitief geschrapt worden.

**Werk meerdere CODA-bestanden in volgorde af**: als het volgnummer aansluit op het laatst ingegeven uittreksel, wordt ook het eindsaldo van de bank (journaal) bijgewerkt.

### 4.4 Een CODA-bestand inboeken

Het overzicht toont alle bewegingen van het uittreksel. **Lijnen in het rood** kon de computer niet eenduidig toewijzen; die moeten manueel behandeld worden.

1. Klik op het **groene icoon** naast de lijn: het boekscherm opent. Bovenaan staan de naam van de opdrachtgever en de meegegeven mededeling. Is de toewijzing gelukt, dan staat de boeking in het midden van het scherm. Zo niet, dan zijn bedrag en naam van de opdrachtgever al ingevuld; bij een **negatief bedrag** wordt verondersteld dat het om een **leverancier** gaat.
2. **`F10` ZOEK** - de belangrijkste zoektoets:
   - is het **factuurnummer** ingevuld, dan wordt op factuurnummer gezocht (snel);
   - zo niet, dan wordt de boekhouding doorzocht op het **bedrag** (iets trager);
   - is geen van beide ingevuld, dan wordt op **naam** gezocht;
   - gevonden boeklijnen worden getoond.
3. `F8` neem aan: opent de rekening van de klant/leverancier om de factuur te kiezen. `F1` stop: terug naar het overzicht. Met de **groene pijlen** bladert u vooruit/achteruit in het bestand.
4. Het selectiescherm toont de overeenkomstige lijnen die nog **niet voldaan** zijn. Is het scherm leeg, dan zijn er enkel voldane facturen gevonden: druk `F10` "Alle facturen" om ze te tonen. Is er geen overeenstemming, dan volgt een foutboodschap en wordt het scherm niet getoond.

**Vaste koppeling van een bankrekeningnummer**: zodra een betaling toegewezen is, wordt een icoon zichtbaar waarmee het rekeningnummer van de tegenpartij vast gekoppeld kan worden aan een klant, leverancier of grootboekrekening. Vooral nuttig voor terugkerende verrichtingen zoals huurgelden, geldstortingen, verzekeringen. Overzicht (max. 250 koppelingen): parameters > `F10` toon gekoppelde rekeningen.

### 4.5 Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Geen bestanden in de lijst | Het bankprogramma heeft de CODA-bestanden niet in de ingestelde map opgeslagen; pad in de parameters fout (ontbrekende afsluitende `\`); de pc die de bestanden afhaalt heeft geen (volledige) toegang tot de map op de server; of de bestanden zijn al verwerkt (kijk in de vuilbak). |
| Klant gaf de gestructureerde mededeling mee, maar de betaling is toch niet automatisch toegewezen (rode lijn) | Het **bedrag stemt niet overeen** met de factuur. In het detailscherm zijn alle gegevens al ingevuld; met `F8` komt u direct op de juiste rekening. |
| Gestructureerde mededelingen worden nooit herkend | De samenstelling van de eigen gestructureerde mededeling wijkt af van de standaard (klantnr 5 + factuurnr 5 + 2 controlecijfers): juiste samenstelling instellen in de parameters. |
| Totaal van een betaallijst wordt niet herkend | "Rekeningnummer betaallijsten" niet (juist) ingevuld voor deze bankrekening. |
| Eindsaldo van het bankjournaal klopt niet na het inboeken | Bestanden niet in volgorde verwerkt, of een uittreksel ontbreekt. Saldo nakijken in `+.3` (journalen). |
| Alle uitgaande betalingen komen op één wachtrekening | "Wachtrekening voor alle betalingen" is ingevuld; enkel bedoeld voor klanten die geen aankoopfacturen inboeken. |
| Leverancier wordt voorgesteld bij een negatieve lijn die geen leverancier is | Standaardgedrag: negatief bedrag = leverancier verondersteld. Type/rekening manueel aanpassen of het rekeningnummer vast koppelen aan een grootboekrekening. |

(De oorzaken zijn afgeleid uit de parameters en tips in de handleiding; enkel de tweede rij staat letterlijk als tip in de bron.)

### 4.6 Zonder CODA-module

- Bankuittreksels worden manueel ingeboekt via `B.2.1` (zie `boekhouding-facturen-en-financiele-verrichtingen.md`).
- Wie enkel klanten opvolgt, kan `B.2.2` "Afboeken openstaande klantfacturen via lijst" gebruiken.
- De oude gebruikershandleiding vermeldt daarnaast een optie "Automatisch inboeken bankuittreksels voor inkomende betalingen" (gestructureerde klantbetalingen, B.5.0.3) en "OGM-verwerking via diskette" (2.4); daarvoor is geen aparte handleiding in de bronnen (vermoedelijk oudere varianten van de CODA-verwerking, te verifieren).

## Bronnen

- `0073A - Automatisch inboeken CODA-bestanden.docx` (map Jamadrink/Handleidingen modules).
- `0072A - Automatische betaalopdrachten leveranciers.docx` (map Jamadrink/Handleidingen modules).
- `0077A - Automatische domicilieringsopdrachten klanten.docx` (map Jamadrink/Handleidingen modules).
- `Gebruikerhandleiding BOEKHOUDPAKKET.docx` (map boekhouding) - versie V06, 2014: punten 2.2, 2.3, 2.4, 5.0.1-5.0.3, foutenlijst (28).
