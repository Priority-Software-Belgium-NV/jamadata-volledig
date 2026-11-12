# Boekhouding in Jamadata: jaarlijkse BTW-listing, intracommunautaire opgave en Intrastat-aangifte

Gebruik dit document voor: vragen over de jaarlijkse BTW-listing (klantenlisting) via Intervat (B.5.9.1 - B.5.9.3 en B.5.9.F), klanten met ontbrekend BTW-nummer of niet-BTW-plichtige klanten, de intracommunautaire opgave (B.5.9.4 - B.5.9.5), de bestandsnamen en mappen van de XML-bestanden, en de maandelijkse Intrastat-aangifte via OneGate (B.5.0.6) inclusief installatie-instellingen en de wijziging van de transactiecodes vanaf 1/1/2021.

## 1. Menu B.5.9

| Punt | Functie |
|---|---|
| 5.9.1 | Afdrukken lijst Belgische klanten met ontbrekende BTW-nummers |
| 5.9.2 | Afdrukken jaarlijkse BTW-listing op lijst (ter controle, te bewaren) |
| 5.9.3 | Uitschrijven jaarlijkse BTW-listing voor INTERVAT |
| 5.9.4 | Afdrukken intracommunautaire opgave op lijst |
| 5.9.5 | Uitschrijven intracommunautaire opgave voor INTERVAT |
| 5.9.F | Afdrukken facturenlijst ter controle van de listing |

## 2. Jaarlijkse BTW-listing

### 2.1 Wat en wanneer

Elk jaar, **voor 31 maart**, moet de BTW-listing ingediend worden: de lijst van BTW-plichtige klanten waaraan in het voorgaande jaar gefactureerd is. De aangifte gebeurt elektronisch via **Intervat** (FOD Financien). Afdrukken is niet meer nodig voor de fiscus, maar wel sterk aangeraden ter controle en om te bewaren.

### 2.2 Welke klanten komen op de listing

- De klant heeft een **Belgisch BTW-nummer en is BTW-plichtig**.
- De klant heeft in het aan te geven jaar voor **minstens 250 EUR** (excl. BTW) aangekocht.

**Ondernemingsnummer is niet hetzelfde als BTW-plichtig.** Een vzw heeft bv. een ondernemingsnummer maar is meestal niet BTW-plichtig en mag dus NIET op de listing staan. **Staan er niet-BTW-plichtige klanten op de listing, dan wordt ze geweigerd in Intervat.**

Hoe aanduiden op de klantenfiche (recente versies): klik op het **rode icoon achter het BTW-nummer**. Het BTW-nummer komt dan in het rood te staan = "enkel ondernemingsnummer, NIET BTW-plichtig".

Codes voor het BTW-nummer op de klantenfiche:

| Waarde | Betekenis | Op de listing |
|---|---|---|
| Geldig Belgisch BTW-nummer | BTW-plichtige klant | Ja (vanaf 250 EUR) |
| `999.999.999` (BE-0999.999.999) | Klant heeft een BTW-nummer, maar het is nog niet gekend | Verschijnt op de lijst ontbrekende nummers; in de oude papieren listing vervangen door de letter `N` |
| `000.000.000` (BE-0000.000.000) | Klant heeft geen BTW-nummer | Neen (oude lijst: `NB` als niet-BTW-plichtigen mee afgedrukt worden) |
| Nummer in het rood (rood icoon) | Ondernemingsnummer, niet BTW-plichtig | Neen |

Grootboekrekeningen die niet mogen meetellen in de omzet/BTW van de listing (bv. verkoop leeggoed, ontvangen huurgelden) worden opgegeven in de boekhoudparameters `+.3`.

### 2.3 Werk vanuit het HUIDIGE dossier

Voer alle stappen uit vanuit het **huidige** dossier (niet vanuit de interne kopie van vorig jaar). De listing moet gemaakt worden **voor de eerste archivering van het nieuwe boekjaar**; de computer waarschuwt hiervoor bij die archivering. Is toch al gearchiveerd zonder listing, dan zijn de bestanden `sal.fas` en `klt.fas` van voor de archivering nodig (zie `boekhouding-archivering-en-foutenlijst.md`).

Werden er na het indienen nog facturen voor dat jaar geboekt (jaar nog niet volledig gearchiveerd), dan wijkt een latere afdruk af van de ingediende listing; om discussie te vermijden wordt het jaartal op de lijst **onderlijnd** afgedrukt zolang het jaar niet volledig gearchiveerd is.

### 2.4 Stappenplan

**Stap 1 - Ontbrekende BTW-nummers afdrukken (B.5.9.1)**
- Geef het juiste jaartal in en minimumbedrag `250`.
- De lijst toont alle klanten waarvan het BTW-nummer ontbreekt (`000.000.000` of `999.999.999`) of die als niet-BTW-plichtig staan, en die toch voor minstens 250 EUR afgenomen hebben. Het telefoonnummer van de klant staat op de lijst.
- Overloop de lijst. Staan er BTW-plichtigen op: nummer opvragen en invullen op de klantenfiche (`B.9.2.1`). Klanten zonder BTW-nummer mogen op `000.000.000` blijven.
- Tip: **rechts klikken op het BTW-nummer** in de klantenfiche geeft de optie "BTW-nummers opzoeken".

**Stap 2 - BTW-listing op lijst afdrukken ter controle (B.5.9.2)**
- Jaartal, opmaakdatum (standaard systeemdatum), minimumbedrag `250`.
- "Niet-BTW-plichtigen ook printen" mag **NIET** aangevinkt zijn (`N`).
- Op deze interne lijst staan klanten met **hetzelfde BTW-nummer in het vet**. In de officiele listing mag een BTW-nummer maar één keer voorkomen: de omzetten van die klanten worden samengeteld tot één totaal.
- Het volgnummer op de lijst is hetzelfde als in Intervat, zodat nakijken eenvoudig is. Bewaar deze lijst: in Intervat staan enkel BTW-nummers, met deze lijst is er de verwijzing naar de klant.

**Stap 3 - Omzet van enkele klanten controleren (B.5.9.F)**
Druk voor enkele klanten (steekproef) een facturenlijst af:

| Veld | Invullen |
|---|---|
| Periode facturen | 01/01/xx t.e.m. 31/12/xx |
| Afdrukken lijst leveranciersfacturen | `N` |
| Afdrukken lijst klantenfacturen | `J` (aanvinken) + de klant die u wil controleren (of algemene selectie) |
| Lijst van de facturen afdrukken (N = enkel totaal) | `J` |
| Nieuw blad per klant/leverancier | naar keuze |

Het scherm toont ook tot wanneer de boekhouding gearchiveerd is en tot wanneer het jaararchief gewist is. Bij klanten met een gedeeld BTW-nummer (vet op de lijst) de facturen van alle betrokken klanten samentellen.

**Stap 4 - Uitschrijven voor Intervat (B.5.9.3)**

| Veld | Waarde |
|---|---|
| Jaartal BTW-listing | het aan te geven jaar (automatisch ingevuld) |
| Opmaakdatum | systeemdatum |
| Minimumbedrag afname (excl. BTW) | `250` (niet vergeten!) |
| Niet-BTW-plichtigen ook uitschrijven | `N` / niet aangevinkt |

Druk `F8` "schrijf uit voor INTERVAT".

Bestandsnaam en locatie:

| Versie | Bestand | Map |
|---|---|---|
| Recent (handleiding 0059A) | `BTW-listing_???_20xx.xml` | `Documenten\JamaData\Diversen` ("Mijn documenten" > Jamadata > Diversen). Windows Verkenner opent automatisch in de juiste map. |
| Oud (handleiding 2014) | `BLST-???.xml` (bv. `BLST-FAS.XML`) | de map `jamadata` op `C:` (of `F:` vanaf een werkpost) |

`???` = dossiercode (vaak `FAS`).

**Stap 5 - Verzenden via Intervat**
1. Druk op de **groene knop** onderaan het scherm: de browser opent de juiste pagina van Intervat. Werkt de site niet goed in de huidige browser, probeer dan een andere (bv. Google Chrome) via `https://financien.belgium.be/nl/E-services/Intervat`.
2. Klik op het Intervat-icoon en meld aan (certificaat Isabel/Certipost of elektronische identiteitskaart, met paswoord). Beveiligingswaarschuwingen toelaten.
3. Kies op het scherm met de mogelijke aangiftes bij **Klantenlisting**: **via bestand**.
4. Klik **Bladeren**, ga naar `Documenten > JamaData > Diversen`, dubbelklik op `BTW-listing_???_20xx.xml`.
5. Klik **Openen** (gele knop, rechts op het scherm - wordt vaak over het hoofd gezien).
6. **Controleer de gegevens/bedragen op het scherm met de afgedrukte listing** (steekproeven + totaalbedrag).
7. Volg de instructies om te versturen (datum en handtekening invullen, Versturen).
8. Bij succes volgt een **ontvangstbevestiging**: opslaan en/of afdrukken via de link die eindigt op **PDF**. Bewaar ze bv. in Documenten (of in de Jamadata-map, dan gaat ze mee in de back-up).

### 2.5 Boekhouder dient de listing in

Bezorgt de klant het bestand aan zijn boekhouder die het doorstuurt, dan moet er een **verantwoordelijke** in het bestand meegegeven worden:
1. Maak een leverancier aan voor de boekhouder.
2. Ga naar de parameters `+.3` en druk enkele keren `F8` tot het veld voor de verantwoordelijke; vul hem in. Is dit ingevuld, dan worden zijn gegevens als verantwoordelijke mee uitgeschreven in het bestand.

### 2.6 Opmerkingen en veelvoorkomende problemen

(De oorzaken/oplossingen in deze tabel zijn deels afgeleid uit de voorwaarden en instellingen die de bronnen beschrijven; het zijn geen letterlijk gedocumenteerde foutgevallen.)

| Probleem | Oorzaak / oplossing |
|---|---|
| Listing geweigerd in Intervat | Er staat een niet-BTW-plichtige klant op (bv. vzw met enkel ondernemingsnummer). Zet op de klantenfiche het nummer op "niet BTW-plichtig" (rood icoon), schrijf opnieuw uit. Controleer ook of "niet-BTW-plichtigen ook uitschrijven" uit staat. |
| Te veel klanten / kleine bedragen op de listing | Minimumbedrag stond niet op 250. |
| Bedrag van een klant klopt niet met zijn facturen | Meerdere klantenfiches met hetzelfde BTW-nummer worden samengeteld (vet op de lijst). Of: bepaalde grootboekrekeningen (leeggoed, huur) zijn in `+.3` uitgesloten van de listing. |
| Klant ontbreekt op de listing | BTW-nummer staat op 000.000.000/999.999.999 of op niet-BTW-plichtig; omzet onder 250 EUR; geen Belgisch nummer. |
| Bestand niet te vinden bij "Bladeren" | Recente versies: `Documenten\JamaData\Diversen`. Oude versies: map `jamadata` op C: (server) of F: (werkpost). |
| Klant opzoeken op BTW-nummer | In het zoekveld het BTW-nummer intikken (bv. 123456789 of 123.333.333) en het zoek-op-BTW-icoon gebruiken; in oude versies `$` + nummer. |
| Listing wijkt af van wat ingediend is | Na indienen zijn nog facturen voor dat jaar geboekt; het jaartal staat onderlijnd zolang het jaar niet volledig gearchiveerd is. |
| Fout 20 "Nog geen periode gearchiveerd" | Oude versies vereisten minstens één gearchiveerde periode voor de BTW-listing. |

Voor vragen over de Intervat-website zelf: zie de helpdesk van de FOD Financien (contactgegevens op de Intervat-site).

## 3. Intracommunautaire opgave (leveringen EU)

### 3.1 Wat en wanneer

Wie factureert aan **0 % BTW (vak 44 en/of 46)** aan klanten in andere EU-lidstaten, moet daarvan een opgave doen. Sinds 2010 gebeurt dit op **hetzelfde tijdstip als de BTW-aangifte** (maandelijks of per kwartaal), via Intervat.

### 3.2 Welke klanten worden opgenomen

- Het buitenlandse BTW-nummer moet **beginnen met een landcode** van een andere EU-lidstaat. De bron vermeldt: BG CY DK DE EE FI FR EL GB HU IE IT LV LT LU MT NL AT PL PT RO SI SK ES CZ SE (lijst uit de handleiding; de actuele lijst van lidstaten kan afwijken - GB staat er nog in, HR niet; te verifieren in de actuele programmaversie).
- De klant moet aangekocht hebben in de geselecteerde periode (maand/kwartaal).
- De verkopen moeten geboekt zijn op een verkooprekening met **BTW-vak 44 of 46** (vak op de grootboekfiche).

### 3.3 Stappen

**Stap 1 - Afdrukken op lijst (B.5.9.4)**: geef maand (of kwartaal) en jaartal in. De interne lijst toont alle gegevens met de naam van de klant; klanten met hetzelfde BTW-nummer staan in het vet (in de officiele opgave één totaal per BTW-nummer). Het volgnummer is hetzelfde als in Intervat. Bewaar deze lijst.

**Stap 2 - Uitschrijven voor Intervat (B.5.9.5)**: geef maand (of kwartaal) en jaartal in (opmaakdatum = systeemdatum) en druk `F8`.

| Versie | Bestand | Map |
|---|---|---|
| Recent (handleiding 0059B) | `Intr_Opgave_???_20xx-pp.xml` (`pp` = periode; bv. `Intr_Opgave_FAS_2013-08.xml`) | `Documenten\JamaData\Diversen`; Verkenner opent automatisch |
| Oud (handleiding 2014) | `IOPG-???.XML` | map `Jamadata` op C: (of F: op een werkpost) |

**Stap 3 - Verzenden via Intervat**: groene knop onderaan het scherm opent Intervat. Aanmelden (certificaat/eID), kies **Intracommunautaire opgave** en **via bestand**, **Bladeren** naar `Documenten > JamaData > Diversen`, dubbelklik op het bestand, klik **Openen** (gele knop rechts), controleer de bedragen met de afgedrukte lijst en verstuur. Bewaar de ontvangstbevestiging (link die eindigt op PDF).

Benodigdheden: internettoegang op de hoofdcomputer of een werkpost en een aanmeldmiddel (elektronische identiteitskaart met kaartlezer of een commercieel certificaat zoals Isabel).

### 3.4 Veelvoorkomende problemen

(De oorzaken/oplossingen in deze tabel zijn deels afgeleid uit de voorwaarden en instellingen die de bronnen beschrijven; het zijn geen letterlijk gedocumenteerde foutgevallen.)

| Probleem | Oorzaak / oplossing |
|---|---|
| Buitenlandse klant ontbreekt in de opgave | BTW-nummer op de klantenfiche begint niet met de landcode; of de verkoop is niet geboekt op een rekening met vak 44/46; of geen aankopen in de periode. |
| Bedragen kloppen niet | Meerdere klantenfiches met hetzelfde BTW-nummer worden samengeteld. |
| Leeg bestand / lege lijst | Verkeerde periode (maand vs. kwartaal) of geen 0 %-verkopen op vak 44/46. |

## 4. Intrastat-aangifte (B.5.0.6) - module in optie

### 4.1 Wat

De Intrastat-aangifte (statistiek van het goederenverkeer met andere EU-landen) wordt **maandelijks elektronisch** verstuurd via **OneGate** (Nationale Bank). De module houdt bij elke factuur automatisch de Intrastat-gegevens bij: goederencode, gewicht en aanvullende eenheden (inhoud). Die vormen de basis van de aangifte.

### 4.2 Basisgegevens instellen

1. **Standaardparameters**: hoofdmenu boekhouding > `5.0.6` > parameter-icoon (tandwiel) onderaan. Geef de standaard **landcode, vervoer en transactiecode** voor nieuwe klanten in (standaard `BE`, `3`, `1` - sinds 2021 transactie `11`, zie 4.5) en duid aan voor welke handelingen een aangifte ingediend moet worden: **aankoop, verkoop of beide**.
2. **Klanten- en leveranciersfiches** (`9.2.1` / `9.1.1`): controleer onderaan de fiche de Intrastat-gegevens (land, vervoer, transactie).
3. **Artikelfiches** van de exportartikels (`V.9.3.1`): vul **goederencode, gewicht en inhoud** in.
4. Grootboekfiche: veld "Goederencode (Intrastat)" (zie grootboekfiches).

### 4.3 De aangifte maken (B.5.0.6)

**a) Afdrukken detail- en controlelijst**
Geeft per factuur het detail van de Intrastat-gegevens, ter controle of alles ingevuld is. Geef de periode in (eventueel een selectie van journalen) en druk af.

Fouten corrigeren op een reeds geboekte factuur: hoofdmenu boekhouding > punt `1` > druk op **`U`** (staat niet op het scherm). De boekhoudkundige factuur verschijnt; met **`F9`** kunnen de Intrastat-gegevens aangepast worden.

**b) Afdrukken/uitschrijven Intrastat-aangifte**
Geef de gewenste maand in en bepaal of de aangifte ook uitgeschreven moet worden als **XML-bestand** voor OneGate. Met `F8`/`F9` wordt de aangifte afgedrukt en opent de Verkenner met het XML-bestand. Controleer de aangifte en verstuur ze via OneGate.

### 4.4 Installatie van de module (intern, voor technici)

Uit de interne installatienota (termen zoals in de bron; enkel uit te voeren door wie de structuur-/configuratiebestanden van Jamadata beheert):

- `Struct.cnf` aanpassen - velden toevoegen:
  - Leverancier: velden 1,35-38
  - Klant: velden 2,74-77
  - GRB (grootboek): veld 3,14
  - STK: velden 48-58 + key 20
  - BKA: velden 48-58
  - ART: veld 6,86 (goederencode); indien geen gewicht/inhoud (37 + 38): velden 87 en 88 toevoegen
  - BON: veld 58,30
- Schermen 6 en 7 aanpassen voor de nieuwe velden (zie BSA).
- `Ovl0076` incompileren.
- Parameter `PAR0240`: `INTRASTAT` op `YES` zetten.
- Bij de installatie bij de klant: ga naar het Intrastat-menu, parameters rechtsonder: defaults instellen (`BE`, `3`, `1`) en de **verborgen `F10`** nemen: die vult de defaults in op alle klanten/leveranciers; is er een buitenlands BTW-nummer ingevuld, dan wordt de landcode daarvan genomen.
- De klant moet daarna zelf nog de goederencodes invullen op de artikelfiches.

Onzeker: de installatienota noemt het menupunt "B.5.6", de gebruikershandleiding 0076A en het aanpassingsblok van 2021 in dezelfde nota noemen "B.5.0.6". Ga uit van B.5.0.6 en controleer op het scherm van de klant.

### 4.5 Wijziging vanaf 1/1/2021: transactiecodes 11 en 22

Vanaf 1/1/2021 is de transactiecode gewijzigd van **1 naar 11** en van **2 naar 22**.

Te doen door de technicus:
- Structuur aanpassen: veld Transactie op lengte 2 zetten (l=2) op de velden 1,38 - 2,77 - 4,53 - 86,53.
- Laatste programmaversies installeren.

Te doen bij de klant (belangrijk):
1. Ga naar `B.5.0.6` en open de tandwiel-parameters.
2. Wijzig de transactie van `1` naar `11`.
3. Druk op de **verborgen `F10`**: de parameters worden weggeschreven en op de klanten-, leveranciers-, STK- en BKA-bestanden wordt de nieuwe code ingevuld.

### 4.6 Veelvoorkomende problemen

(De oorzaken/oplossingen in deze tabel zijn deels afgeleid uit de voorwaarden en instellingen die de bronnen beschrijven; het zijn geen letterlijk gedocumenteerde foutgevallen.)

| Probleem | Oorzaak / oplossing |
|---|---|
| Artikel zonder goederencode/gewicht op de controlelijst | Goederencode, gewicht en inhoud invullen op de artikelfiche (V.9.3.1); voor al geboekte facturen corrigeren via B.1 > `U` > `F9`. |
| Aangifte geweigerd wegens transactiecode | Installatie staat nog op de oude code 1/2: voer de aanpassing van 1/1/2021 uit (4.5). |
| Klant heeft verkeerde landcode | Intrastat-gegevens onderaan de klantenfiche corrigeren; bij installatie neemt F10 de landcode over uit het buitenlandse BTW-nummer. |
| Menupunt 5.0.6 geeft "optie niet geinstalleerd" (fout 12) | Module niet aangekocht/geactiveerd (`PAR0240` INTRASTAT). |

## Bronnen

- `0059A - BTW-listing.docx` (map boekhouding) - recentste werkwijze BTW-listing.
- `0059B - Intracommunautaire opgave.docx` (map Jamadrink/Handleidingen modules).
- `0076A - Intrastat-aangifte.docx` (map Jamadrink/Handleidingen modules).
- `HOWTO-installeren INTRASTAT.docx` (map boekhouding) - interne installatienota incl. aanpassing 1/1/2021.
- `Gebruikerhandleiding BOEKHOUDPAKKET.docx` (map boekhouding) - versie V06, 2014: punt 5.9 (oudere bestandsnamen `BLST-???.xml`, `IOPG-???.xml`, betekenis van N/NB, onderlijnd jaartal).
