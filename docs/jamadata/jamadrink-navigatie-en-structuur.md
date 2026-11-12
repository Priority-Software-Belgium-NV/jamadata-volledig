# Jamadrink: navigatie, menustructuur en programmaonderdelen

Gebruik dit document voor: vragen over hoe je in Jamadrink (Jamadata Desktop) navigeert, hoe menupaden zoals `V.9.2.1` gelezen worden, welke functietoetsen en knoppen overal terugkomen, hoe de zoek- en filterschermen werken, welke verborgen (support)menu's bestaan en uit welke programmaonderdelen (JMD, JMC, JMS, ...) het pakket bestaat.

## 1. Menupaden lezen

- Jamadrink werkt met genummerde menu's. Een menu-item kies je door erop te klikken of door de toetsenbordcode (cijfer of letter) in te tikken. Cijfers geef je in met `SHIFT` + cijfer op de bovenste rij (AZERTY) of via het numerieke klavier.
- Een pad zoals `V.9.1.2` betekent: hoofdmenu **V** (Voorraadbeheer) → **9** Beheer basisgegevens → **1** Beheer leveranciers → **2** Bijvoegen van een nieuwe fiche.
- `B` = Boekhoudmenu (bv. `B.5.3` = rappels, `B.5.7` = facturenlijst, `B.4` = raadplegen rekening).
- `+` is een (deels verborgen) parametertoets op het hoofdmenu. Voorbeelden: `+.4` = facturatieparameters, `V.5.6.+` = standaardinstellingen offertes, `+ J 1` = parametermenu printerinstellingen.
- Het pakket is modulair: niet elke klant heeft elk menu-item. Ontbreekt een punt, dan is de module waarschijnlijk niet geïnstalleerd (zie ook foutcode 12 in `jamadrink-foutcodes.md`).

### Hoofdmenu Voorraadbeheer (V)

| Code | Menu-item |
|---|---|
| 1 | Inbrengen bestellingen aan leveranciers |
| 2 | Beheer Key-conen kassa |
| 3 | Beheer prijzen |
| 4 | Raadplegen historieken/statistieken/prijzen |
| 5 | Afdrukken artikellijsten (o.a. `V.5.6` Beheer offertes) |
| 6 | Grootte van de gebruikte bestanden |
| 7 | Aanmaken rapporten |
| 8 | Facturatie |
| 9 | Beheer basisgegevens (leveranciers – klanten – artikelen) |
| A | Periodewerkzaamheden |
| B | Boekhoudmenu |
| W | Beheer webshop |

### Menu V.9 Beheer basisgegevens

| Code | Menu-item |
|---|---|
| 1 | Beheer leveranciers |
| 2 | Beheer klanten |
| 3 | Beheer artikelen |
| 4 | Beheer groepen |
| 5 | Beheer prijsafspraken |
| 7 | Beheer klantentoeren |
| 8 | Beheer omzetfiches (module niet overal beschikbaar) |

### Menu V.8 Facturatie

| Code | Menu-item |
|---|---|
| 1 | Beheer leveringsbons |
| 2 | Afdrukken facturen uit leveringsbons |
| 3 | Afdrukken facturen met rechtstreekse ingave |
| 4 | Afdrukken facturen uit bons van Key-conen kassa |
| 5 | Afdrukken facturen van verkopen uit Key-conen kassa |
| 6 | Afdrukken factuur groothandel → kleinhandel |
| 7 | Afdrukken creditnota's van semestriële kortingen |
| 8 | Afdrukken leveringslijsten per klantentoer |
| 9 | Beheer leveringen/mutaties aan filialen |
| A | Beheer leeggoed-retour met PDA |
| B | Beheer uitlenen/verhuren van materialen |
| C | Beheer uitschrijven artikels voor Beedrop |
| H | Herdrukken facturen |

Daarnaast bestaat een verborgen punt `U` (factuur schrappen met terugzetten van statistieken/voorraad); volgens de modulehandleiding 0234A zit dit op het menu Herdrukken facturen (`V.8.H`), zie `jamadrink-bons-en-facturen.md`.

In menu V.8 kan je met `F10 afhalingen/memo` ook de memo van een klantenfiche aanpassen.

## 2. Algemene toetsen

| Toets | Werking |
|---|---|
| `ENTER` | Eén veld vooruit |
| `ALT`+`ENTER` | Eén veld terug (werkt overal in het pakket, niet alleen bij facturatie) |
| `TAB` op een geopende fiche | Zet de fiche in editeer-modus: velden worden aanpasbaar en er verschijnen extra knoppen |
| `TAB` in een invulveld | Automatisch aanvullen op wat **begint met** de ingetikte tekst (1 resultaat: direct ingevuld; meerdere: keuzelijst) |
| `F7` in een invulveld | Automatisch aanvullen op wat de ingetikte tekst **bevat** (enkel als F7 op dat scherm geen andere functie heeft) |
| `F1` / `F6` | Stop / terug naar vorig scherm (F6 is op lijsten vaak "annuleer wijzigingen") |
| `F2` / `F3` | Scherm omhoog / omlaag (vorig / volgend) |
| `F8` | Bevestigen: neem aan / schrijf weg / ga verder / zoek op |
| `F11` | Terug naar hoofdmenu (in schrapschermen); in bon/factuur: historiek artikel |
| `F12` | Extra info bij fiche (zie fiches-document); elders soms Help |
| `HOME` | Sprong naar het selectieveld in lijsten (bv. artikellijst V.9.3.L) |

Opmerking: als bij een scherm de melding komt dat TAB of BREAK niet toegestaan is (foutcode 21), moet je een functietoets gebruiken.

Onderaan de meeste schermen staat de lijst van functietoetsen die op dat scherm gelden; die lijst is leidend, want de betekenis van F4/F5/F9/F10 verschilt per scherm.

## 3. Knoppen (iconen) die op veel schermen terugkomen

De handleiding toont de iconen als afbeelding; hieronder de functies per plaats.

| Plaats | Functie van de knop |
|---|---|
| Fiche (algemeen) | Pijlen: vorige / volgende fiche in de zoekresultaten |
| Fiche (algemeen) | Grote `+`-knop (rechtsboven): scherm met **extra opties**, afhankelijk van het soort fiche (bons, boekhoudrekening, openstaande facturen, historieken, documenten, GDPR-export...) |
| Naast een adres | Opent het adres in Google Maps in de standaardbrowser |
| Fiche | **Lock**: blokkeert de fiche; ze kan nergens meer gekozen worden, maar historiek blijft bewaard (in tegenstelling tot schrappen). **Unlock** maakt de fiche weer bruikbaar |
| Naast zoek-/codeveld | Vergrootglas/lijstknop: toont een keuzelijst (bv. alle fiches die bij de zoekterm passen, of gemeenten bij een postcode) |
| Artikel: Stock | Berekening netto-stock (stock op fiche, aantallen op bons, aantallen in bestelling) |
| Naast te controleren veld | Controleknop: valideert bv. een bankrekeningnummer |
| Klant / leverancier: e-mail | Opent extra e-mailinstellingen; bij klant ook lijst van alle door het systeem verzonden mails (per lijn te downloaden) |
| Factuur (afsluitscherm) | Factuur manueel mailen naar de ingestelde ontvangers. Wordt de factuur ook automatisch gemaild, dan vraagt het systeem of je ze tweemaal wil verzenden |
| Artikel: Omschrijving | Instellingen verpakkingen (bv. verpakking "bak" van 12 stuks met prijs) |
| Artikel: EAN-nummer bak | Berekent het controlecijfer van een zelf ingegeven barcode |
| Klant: Naam | Klant markeren (rode markeringskleur). De markering is zichtbaar bij het aanmaken van een bon of factuur, bv. om een slechte betaler aan te duiden |
| Rechtsonder op lijst-/afdrukschermen | PDF-knop: maakt een pdf van het resultaat en opent die, in plaats van af te drukken |
| Artikel: Codenummer | Artikel in / uit de webshop zetten |
| Artikel: Verkoopprijzen | Artikel mag wel / geen korting krijgen |
| Artikel: Aankoopprijs | Scherm om meerdere verkoopprijzen meteen aan te passen |
| Nieuwe fiche | Kopieert de gegevens van de laatst geopende fiche van hetzelfde type |
| Scherm (vraagteken) | Opent de deelhandleiding (pdf) voor het scherm waarin je zit |
| Artikel: Grootboekrekening | Toont info van de grootboekrekening |
| Klant: Btw-nummer | Klant wel / niet btw-plichtig (niet btw-plichtig = rode markering) |
| Lijstschermen (V.9.3.L, export) | Lijst van alle databasekolommen om aan te vinken |
| Leveringsbon: Klant | Opent de klantenfiche van de ingevulde klant |
| Leveringsbon | Klantenbestelling inladen in de leveringsbon |
| Bestelbon/offerte-aanvraag: afsluiting | Bestelling direct bij Prik & Tik plaatsen |

## 4. Zoekscherm

- In het zoekveld tik je (een deel van) de code of de naam.
- Het icoon naast het veld geeft een lijst van alle fiches die bij de zoekterm passen.
- `F8 Zoek op`: toont direct de details van de eerste match.
- `F9 NIEUWE [fiche]`: opent een nieuwe invulfiche met de zoekterm al ingevuld.
- `F1`/`F6`: terug.

## 5. Filterscherm fiches (klanten, leveranciers)

Verschijnt bij lijsten, etiketten, Excel-export en reeksbewerkingen.

| Code | Filter |
|---|---|
| 1 | Ondergrens (groter dan) |
| 2 | (Groter dan of gelijk aan) |
| 3 | Bovengrens (kleiner dan) |
| 4 | (Kleiner dan of gelijk aan) |
| 5 | Gelijk aan |
| 6 | Niet gelijk aan |
| 7 | Uitwissen selectiecriteria |

- Per filter krijg je een invulfiche waarin je op bijna elk veld van de fiche kan filteren.
- In tekstvelden werkt de wildcard `*`: `A*` onder "Gelijk aan" bij Naam = alle fiches die met A beginnen; `Stationsstraat*` bij "Straat + nummer" = alle klanten in die straat.
- `F8 schrijf weg` bewaart het criterium, `F8 selecteer` voert de filter uit, `F9 volledig` neemt alle fiches (zelfde resultaat als lege filters).
- Voorbeeld "klanten met meer dan 10% korting": `V.9.2.7` → kolommen aanvinken → filter 1 (ondergrens) → `10` bij Kortings% → `F8 schrijf weg` → `F8 selecteer`. Voor "10% of meer": filter 2.

## 6. Filterscherm artikels (uitgebreide selectie artikels)

Verschijnt bij artikellijsten, prijslijsten, offertes, reeksbewerkingen.

| Code | Selectie | Toelichting |
|---|---|---|
| 1 | Op leverancier | Lijst van alle leveranciers, standaard allemaal aangevinkt; `F5` vinkt alles af, daarna de gewenste aanduiden |
| 2 | Op artikelgroep | Zelfde werking als leverancier (`F5` = alles afvinken) |
| 3 | Op merk/fabrikant | Enkel artikels van 1 merk/fabrikant |
| 4 | Op artikelfiche | Menu om op elk veld van de artikelfiche te selecteren (gelijk / groter dan / kleiner dan). Tekstvelden altijd afsluiten met `*` (bv. `coca*`) |
| 5 | Op datum laatste prijswijziging | Periode waarin de prijs wijzigde (datum "Vanaf" op artikelfiche of datum van prijswijziging op datum). Handig voor rayonkaartjes van recent gewijzigde artikels |
| 6 | Artikels bestelbon klant | Artikels die op de klantenfiche via `F9 bestelbon` zijn ingegeven |
| 7 | Artikels van klantenstatistiek | Artikels die de klant ooit afnam (vereist statistieken/historieken; max. 2 jaar) |
| 8 | Artikels met prijsafspraak | Artikels met een individuele prijsafspraak voor de klant |

- Selecties 6, 7 en 8 werken enkel als er een klant gekozen is. Staat er **"Geen klant"** achter, druk dan `F4 klant <-> selectie`, zoek de klant op (eerste letters + TAB vult aan) en druk opnieuw `F4` om verder te selecteren.
- `F8 ga verder` voert de selectie uit, `F9 wis selecties` maakt alles leeg.

## 7. Verborgen support-/parametermenu's

Deze punten zijn bedoeld voor supportmedewerkers. **Neem altijd eerst een back-up** voor je iets wijzigt.

| Pad | Functie | Bron |
|---|---|---|
| Hoofdmenu `+` `J` `1` | Parametermenu (printerinstellingen) | Navigeren binnnen Jamadata |
| Hoofdmenu `+` `J` `T` | Lijst werkposten die nog bezig zijn | Navigeren binnnen Jamadata |
| Hoofdmenu `+` `J` `5`, dan `F8` | Mail/handleiding-instellingen; het vraagteken opent de pdf-handleiding (zie `jamadrink-layouts-en-afdrukken.md`) | Aanpassen Lay-outs |
| Hoofdmenu `+` `T` `1` | Systeemparameters (integers) bekijken/wijzigen, bv. parameter 2698 (blokkeren inputschermen) | HOWTO-Blokkeren inputscherm |
| Hoofdmenu voorraadbeheer `+` → optie `T` (verborgen) → `2` | Invullen/wissen van een veld in de database | Handleiding invullen veld database |
| Hoofdmenu `+` `H` (bevestig back-up) → `3` | Fiches aanpassen a.h.v. Excel-bestand | 0093A |
| `+.4` | Facturatieparameters (o.a. vaste teksten 1–4) | Boekhoudhandleiding via 13_TEKSTEN_SCOPE |
| `V.8.H` → `U` (verborgen) | Factuur schrappen met herstel statistieken/voorraad | 0234A |

### Scherm van een klant overnemen via JMD (Jamadata Desktop)

- In JMD: **Configuratie > Instellingen > Dossiernummer klant ingeven**. Daarna `F4`, wachtwoord ingeven en `F10` (wachtwoord: zie interne bron).
- Voor light- en standaardklanten is een aparte demo-aanlogcode voorzien om op afstand aan te loggen; de code die in JMD moet worden ingevuld staat in de interne bron (HOWTO-DEMOscherm klant overnemen). (code: zie interne bron)

## 8. Programmaonderdelen (Program structure)

De bron is een schema zonder begeleidende tekst; onderstaande is wat uit de labels af te leiden valt.

| Afkorting | Onderdeel | Rol |
|---|---|---|
| JMD | Jamadata **Desktop** | De viewer waarin de gebruiker werkt |
| JMC | Jamadata **Client** | Elk scherm in de viewer is een JMC-proces (meerdere per desktop) |
| JMS | Jamadata **Server** | Database-server |
| JMH | (in het schema tussen JMD en JMC getekend) | Betekenis niet uitgeschreven in de bron: onzeker / te verifiëren |
| JMT | Installeren + controle | Installatie- en controletool |
| JMR | Jamadata **Reporter** | Error reporting, naar een centrale Jamadata-dienst |

Meer over JMS, installatie en back-up staat in de documenten van de andere onderwerpen (server/installatie).

## 9. Veelvoorkomende vragen

| Vraag / probleem | Antwoord |
|---|---|
| "Ik kan niets wijzigen op de fiche" | Druk eerst `TAB` om in editeer-modus te gaan. Bij sommige klanten is dat verplicht gemaakt via parameter 2698 (zie fiches-document). |
| "Ik vind een leverancier/klant niet terug op naam" | Gebruik `F7` (bevat) in plaats van `TAB` (begint met), of exporteer naar Excel met een filter op een ander veld (bv. vertegenwoordiger). |
| "Selectie 6/7/8 bij artikels doet niets" | Er staat "Geen klant": eerst `F4` en een klant kiezen. |
| "Menu-item uit de handleiding bestaat bij mij niet" | Module niet in het pakket; menu's verschillen per installatie. |
| "Waar open ik de handleiding van een scherm?" | Vraagteken-knop op het scherm opent de deelhandleiding (pdf). |

## Bronnen

- `gebruikershandleiding JAMADRINK 2.0.docx` (map Jamadrink): hoofdstukken V, V.8, V.9 en "Extra notities" (knoppen, tips, zoeken, filteren)
- `Navigeren binnnen Jamadata.pdf` (map Onenote; dubbel in map Jamadrink)
- `Aanpassen Lay-outs.pdf` (map Onenote; dubbel in map Jamadrink)
- `Program structure.docx` (map Jamadrink)
- `2215A - Uitgebreide selectie artikels.docx` (map Jamadrink/Handleidingen modules)
- `0240A - Extra functies bij aanmaken van een bon-factuur.docx` (map Jamadrink/Handleidingen modules)
- `HOWTO-DEMOscherm klant overnemen.docx`, `HOWTO-Blokkeren inputscherm klt_lev_art.docx`, `Handleiding invullen veld database.docx` (map Jamadrink)
