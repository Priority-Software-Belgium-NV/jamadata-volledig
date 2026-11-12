# Boekhouding in Jamadata: basis, schermbediening, basisfiches en systeemparameters (dagboeken)

Gebruik dit document voor: vragen over de opbouw van het Jamadata-boekhoudpakket (hoofdmenu B), de bediening van de schermen en functietoetsen, het opzoeken van fiches, het beheer van leveranciers-, klanten- en grootboekfiches (punt 9), en de systeemparameters achter de verborgen toets `+` (boekhoudparameters, definitie van de journalen/dagboeken, paswoorden, papierformaten, wisselkoersen, bestandsgrootte). Voor het boeken zelf: zie `boekhouding-facturen-en-financiele-verrichtingen.md`. Voor lijsten: `boekhouding-openstaande-posten-en-rapporten.md`. Voor archiveren en foutnummers: `boekhouding-archivering-en-foutenlijst.md`.

> Opmerking over de bron: de gebruikershandleiding van het boekhoudpakket dateert van 2014 (versie V06) en beschrijft de klassieke tekstschermen (25 lijnen x 80 kolommen). In recentere versies zijn sommige J/N-velden vervangen door aanvinkvakjes en zijn er iconen bijgekomen (bv. Excel-icoon, groene Intervat-knop). De menunummers zijn dezelfde gebleven.

## 1. Opbouw van het hoofdmenu boekhouding (menu "B")

De hoofdstukken van de handleiding volgen de nummering van het hoofdmenu. In documentatie wordt een pad genoteerd als `B.5.9.2` = hoofdmenu Boekhouding, punt 5, punt 9, punt 2.

| Punt | Inhoud |
|---|---|
| 1 | Inbrengen facturen (1.1 inkomende facturen, 1.2 inkomende creditnota's, 1.3 intracommunautair/medecontractant, 1.4 uitgaande facturen, 1.5 uitgaande creditnota's) |
| 2 | Inbrengen financiele & diverse verrichtingen (2.1 manueel, 2.2 afboeken klantfacturen via lijst, 2.3 automatisch inboeken CODA, 2.4 OGM-verwerking, F10 openingsbalans) |
| 4 | Overzicht (rekeningoverzicht) leveranciers - klanten - grootboekrekeningen |
| 5 | Afprinten lijsten (5.1 periodelijsten, 5.2 rekeningen, 5.3 klantenrappels, 5.8 vervallen/openstaande facturen, 5.9 BTW-listing/IC-opgave, 5.0 menu lijsten in optie, 5.+ afdrukinstellingen BTW-formulieren) |
| 6 | Grootte van de gebruikte bestanden |
| 7 | Aanpassen wisselkoersen |
| 8 | Facturatie |
| 9 | Beheer van de basisgegevens (9.1 leveranciers, 9.2 klanten, 9.3 grootboekfiches/rekeningplan) |
| A | Archivering van verouderde verrichtingen (A.1 archivering, A.2 wissen jaararchief) |
| U | (verborgen toets) Schrappen van boekhoudbewegingen |
| + | (verborgen toets) Aanpassen systeemparameters |

De punten `U` en `+` staan niet op het hoofdmenu afgedrukt; ze worden opgeroepen door de toets zelf in te drukken op het hoofdmenu.

## 2. Bediening van de schermen

### 2.1 Algemeen

- Alle programma's zijn schermgeorienteerd: een scherm bevat vaste tekst en velden. Alleen velden kan de gebruiker wijzigen.
- De voorlaatste lijn van elk scherm toont de toegestane functietoetsen; de laatste lijn toont een eventuele foutmelding (met foutnummer, zie `boekhouding-archivering-en-foutenlijst.md`). De melding blijft staan tot er een ander scherm of een andere melding komt.

### 2.2 Veld-exit-toetsen (van veld naar veld)

| Toets | Werking |
|---|---|
| ENTER | Naar het volgende veld; na het laatste veld terug naar het eerste |
| HOME | Naar het eerste veld (linksboven) |
| Pijl omhoog / omlaag | Naar de vorige / volgende gebruikte lijn (zelfde kolom indien daar een veld staat) |
| SHIFT + pijl omhoog / omlaag | Naar het eerste veld van de vorige / volgende gebruikte lijn |
| ESC | Zolang het veld nog niet verlaten is: de oude inhoud terugzetten |
| INSERT / DELETE | Teken tussenvoegen / verwijderen in een veld |

### 2.3 Soorten velden

- **Numerieke velden**: decimalen mogen met `.` of `,` ingetikt worden (het scherm toont `.`); punten tussen duizendtallen nooit intikken. Negatief maken met `-` (voor of tijdens het intikken), terug positief met `+`. Als een waarde buiten een ingebouwde grens valt (bv. korting > 100 %), weigert de cursor het veld te verlaten en geeft de computer een beep.
- **Tekstvelden**: sommige velden zetten alles automatisch om in hoofdletters (of kleine letters). Als het veld vol is, geeft invoegen een beep. Paswoordvelden tonen `*` per ingetikt teken.
- **Datumvelden**: steeds dag, maand, jaar, met 6 cijfers en met de nullen (6 december 2010 = `061210`). De scheidingstekens worden automatisch geplaatst. Een ongeldige datum (ook rekening houdend met schrikkeljaren) wordt geweigerd (fout 6).
- **BTW-nummer**: voorgeformatteerd en gecontroleerd op controlecijfer (fout 29). Onbekend BTW-nummer van iemand die er wel een heeft: `999.999.999`. Zeker geen BTW-nummer: `000.000.000`.
- **Bankrekeningnummer**: voorgeformatteerd en gecontroleerd (fout 26). Wordt een nummer niet aanvaard: tijdelijk `000-0000000-00` invullen (wordt altijd aanvaard) en het juiste nummer navragen. Er zijn aparte velden voor IBAN en BIC.

### 2.4 Functietoetsen (scherm-exit)

In theorie is `TAB` de algemene scherm-exit-toets ("doe verder"). De functietoetsen geven een specifiek commando; de exacte betekenis verschilt per scherm en staat op de voorlaatste lijn.

| Toets | Standaardbetekenis |
|---|---|
| F1 | Stop (terug naar bovenliggend menu) |
| F2 | Vorige (scherm/pagina terug) - let op: de handleiding noemt F2/F3 op sommige plaatsen omgekeerd; kijk naar de lijn onderaan het scherm |
| F3 | Volgende |
| F4 | Ja |
| F5 | Nee |
| F6 | Annuleer (niets wegschrijven) |
| F7 | Herdisplay (herberekenen / naam opzoeken) |
| F8 | Einde / Boek / Zoek op / Schrijf weg |
| F9 | Afhankelijk van de toepassing (vaak: afdrukken, volledige lijst, standaard GRB) |
| F10 | Afhankelijk van de toepassing (bv. memo, openingsbalans, jaararchief) |
| F11 | Hoofdmenu |
| F12 | Voorbehouden (extra info-module, PDF) |

Op sommige beveiligde schermen is `TAB` niet toegestaan en moet een specifieke functietoets gebruikt worden (fout 21).

## 3. Opzoeken van fiches (klant, leverancier, grootboekrekening)

In elk zoekveld kan op vier manieren gezocht worden:

| Manier | Hoe intikken | Opmerkingen |
|---|---|---|
| Per naam/omschrijving | Eerste letter(s) van de naam, dan `F8` | Eén letter volstaat. Bij meerdere resultaten toont de computer een lijst (max. 50 fiches); bladeren met F2/F3, kiezen met het lijnnummer + TAB/F8 of met de pijltjes + ENTER. `F6` = niet gevonden. Staat de fiche niet bij de eerste 50: meer beginletters ingeven. |
| Per codenummer | Het volledige codenummer | De computer herkent een code aan het eerste teken (cijfer). Begint een code met een letter: een `.` (punt) voor de code tikken. Bij grootboekrekeningen geeft een `.` een lijst. |
| Per recordnummer | `?` gevolgd door het recordnummer | Zelden nodig; het recordnummer is de fysieke plaats in het bestand. |
| Per BTW-nummer (klanten) | `$` gevolgd door het BTW-nummer, dan `F8` | Bv. `$be123456789`, `$be123.333.333` of `$123456789`. In recentere versies is hiervoor een icoon naast het zoekveld voorzien. |

Afspraken bij het aanmaken van fiches:
- Een naam/omschrijving moet met een letter beginnen (geen cijfer) en mag niet blanco zijn (fout 30).
- Een codenummer begint normaal met een cijfer.
- Codenummers en recordnummers moeten juist en volledig ingegeven worden; bij namen volstaan de beginletters.

## 4. Punt 9 - Beheer van de basisgegevens

De hele boekhouding steunt op drie basisbestanden: leveranciers (9.1), klanten (9.2) en grootboekfiches/rekeningplan (9.3). De submenu's zijn voor elk type nagenoeg gelijk:

| Subpunt | Functie |
|---|---|
| 9.x.1 | Aanpassen/bekijken van een bestaande fiche |
| 9.x.2 | Bijvoegen van een nieuwe fiche |
| 9.x.3 | Schrappen van een bestaande fiche |
| 9.x.4 | Afdrukken lijst van de fiches (bij grootboek: lijst per codenummer) |
| 9.3.5 | (grootboek) Afdrukken alfabetische lijst |
| 9.x.6 | Afdrukken etiketten (niet voor grootboek) |
| 9.x.7 | Uitschrijven gegevens naar file (diskbestand, met selectiecriteria) |
| 9.x.L | Aanpassen/schrappen van een reeks van fiches |

### 4.1 Leveranciersfiche (9.1)

Belangrijke velden:
- **Bankrekeningnummer / IBAN / BIC**: zie controle hierboven.
- **BTW-nummer**: enkel de cijfers intikken, zonder puntjes of streepjes. Onbekend = `999.999.999`, geen = `000.000.000`. Voor een BTW-nummer met egalisatie een `E` toevoegen op de 12de positie (verwijderen met DELETE op die letter).
- **Betalingstermijn**: aantal dagen (bv. `30`) of `E1` = 30 dagen einde maand, `E2` = 60 dagen einde maand, enz. Wordt bij het boeken van inkomende facturen bij de factuurdatum geteld om de vervaldatum te bepalen.
- **Betalingskorting (disconto)**: percentage + termijn waarbinnen de korting geldt (ook hier kan `E1` enz.). Wordt gebruikt om discontobedrag en discontovervaldag op inkomende facturen voor te stellen.
- De gegevens worden later afgedrukt zoals ze ingebracht zijn (hoofd-/kleine letters).

Functietoetsen op de fiche:

| Toets | Werking |
|---|---|
| F1 | Stop en naar bovenliggend menu |
| F6 | Annuleer, gegevens worden NIET weggeschreven |
| F8 | Schrijf weg (bij bijvoegen: onmiddellijk een nieuwe lege fiche) |
| F9 | Standaard GRB: tot 10 meest gebruikte grootboekrekeningen voor deze leverancier. Bij het inboeken van een factuur van deze leverancier verschijnen deze rekeningen, zodat enkel de bedragen moeten ingevuld worden. |
| F12 | Extra informatie (module in optie): ca. 100 tekstlijnen per klant/leverancier/artikel, met datum en type per lijn |

In het F12-infoscherm: F1/F6 = niet wegschrijven en stoppen; F2/F3 = scherm omhoog/omlaag; F4 = lege lijn invoegen; F5 = lijn wissen; F8 = wegschrijven en stoppen; F9 = schakelen tussen alles aanpassen of enkel tekst; F10 = informatie van een andere klant overnemen. De datum en het type per lijn dienen om bij het afdrukken te kunnen selecteren (bv. type A = afspraken, type B = bezoek, in combinatie met een periode).

### 4.2 Klantenfiche (9.2)

Zelfde werking als de leveranciersfiche. Specifiek:
- **Aanspreektitel**: `Janssens*Garage` wordt op documenten die naar de klant gaan (etiketten, rappels) afgedrukt als "Garage Janssens": de tekst na de `*` komt voor de naam.
- **Betalingstermijn**: bepaalt de vervaldatum van de factuur. Niet ingevuld = contant (vervaldatum = factuurdatum).
- **BTW-nummer**: zelfde regels als bij leveranciers. In recentere versies staat achter het BTW-nummer een rood icoon om een klant als "NIET BTW-plichtig" aan te duiden (ondernemingsnummer zonder BTW-plicht, bv. een vzw); het nummer komt dan in het rood te staan. Rechts klikken op het BTW-nummer geeft de optie "BTW-nummers opzoeken". Zie `boekhouding-btw-listing-ic-intrastat.md`.
- **Kortings%**: standaardkorting bij facturatie (per lijn aanpasbaar).
- **Omzet**: hier wordt het bedrag excl. BTW van elke factuur opgeteld.
- **Memo (F10)**: een 5-tal lijnen; wordt getoond tijdens het opmaken van bons/facturen.
- **Bijkomende KL-info (F12)**: 100 extra lijnen (module in optie).

### 4.3 Schrappen van een fiche (9.x.3)

- Het schrappen is onherroepelijk; de computer vraagt een bevestiging.
- Een fiche waarop boekingen staan of waarvan het saldo niet 0 is, kan niet geschrapt worden: **fout 25**. Het saldo valt pas weg na de laatste archivering van het lopende boekjaar.
- Vanuit sommige menu's kan niet geschrapt worden (**fout 65**): ga naar hoofdmenu B (of V), punt 9.

### 4.4 Lijsten en etiketten van fiches (9.x.4 en 9.x.6)

- Lijsten kunnen op **N**ummer of **A**lfabetisch.
- Vragen bij klanten/leveranciers: volledige fiches afdrukken (J/N), apart blad per fiche (J/N), klanten-memo afdrukken (J/N), enkel klanten met memo (J/N), extra informatie afdrukken (J/N) met selectie op periode, facturatieklant en type.
- Selectiecriteria (blijven in het geheugen tot ze gewist worden of tot een ander basistype gekozen wordt):
  1. groter dan, 2. groter dan of gelijk aan (ondergrens)
  3. kleiner dan, 4. kleiner of gelijk aan (bovengrens)
  5. gelijk aan, 6. niet gelijk aan
  7. uitwissen selectiecriteria (best doen voor een nieuwe selectie)
- `F8` = afdrukken volgens selectie, `F9` = volledige lijst zonder selectie, `F1` = terug.
- Het fysieke formaat van de etiketten hangt af van `+.F`, papierformaat 5.
- Tip: druk eerst een lijst met de selectie af en gebruik dan dezelfde selectie voor de etiketten.

### 4.5 Reeks fiches aanpassen/schrappen (9.x.L)

Kies eerst A/K (alfabetisch of per codenummer), vul het selectiescherm in; daarna worden de fiches één voor één getoond: `F8` = fiche aanpassen, `F9` = markeren om te schrappen.

### 4.6 Grootboekfiches / rekeningplan (9.3)

Velden van een grootboekfiche (9.3.2 bijvoegen, 9.3.1 aanpassen):

| Veld | Uitleg |
|---|---|
| Rekeningnummer | Max. 8 cijfers, uitsluitend cijfers. Totaalrekeningen niet aanvullen met nullen (rekening `1` mag geen `1000` worden). Rekeningen die beginnen met **8, 9 of 0 mogen niet gebruikt worden**: voorbehouden voor analytische boekhouding. |
| Omschrijving | Kort houden (komt op journalen en balans). Gelijkaardige rekeningen met hetzelfde woord laten beginnen (bv. alle BTW-rekeningen met "BTW") zodat ze samen opgezocht kunnen worden. |
| Centralisatie J/N | `N` = alle individuele bewegingen in detail op rekeningoverzicht/afdruk. `J` = enkel totaal debet/credit van de periode. Let op: bij `J` wordt het detail bij archivering NIET in het jaararchief opgenomen. |
| Boeken toegestaan J/N | `N` voor subtotaalrekeningen of rekeningen die nog niet gebruikt mogen worden. Boeken op zo'n rekening geeft fout 24. |
| Aankoopkolom | Kolom in het aankoopjournaal: `1` = goederen, `2` = BTW op aankopen, `0` = alle andere rekeningen (kosten, investeringen, ...). |
| Verkoopkolom | BTW-groep/kolom in het verkoopjournaal; de mogelijke keuzes staan op het scherm en hangen af van de systeemparameters (`+.3`). Eerst de parameters invullen. |
| Vak BTW-aangifte | Vak van de BTW-aangifte waarin de rekening getotaliseerd wordt (uitleg van de meest gebruikte vakken staat onderaan het scherm). |
| Totalisatieniveau | 1 (hoogste) tot 9. Vuistregel: aantal cijfers van het nummer van de totaalrekening (780 = niveau 3, 78 = niveau 2, 7 = niveau 1). Voor een rekening waarop geboekt mag worden moet het niveau 0 zijn (fout 22); een totaalrekening heeft niveau 1 t/m 8 (fout 23). |
| Printen totaal J/N | Of het subtotaal van dit niveau op de proef- en saldibalans gedrukt wordt (standaard `J`). |
| Goederencode | Intrastat-goederencode. |

"Fiche bestaat reeds" (fout 31) kan twee oorzaken hebben: het nummer bestaat al, of de omschrijving bestaat al. Voor de vergelijking van omschrijvingen negeert de computer spaties en leestekens en zet alles in hoofdletters ("VORDERINGEN >1 jaar" = "Vorderingen >1jaar").

Het rekeningnummer van een rekening waarop geboekt is, kan niet gewijzigd worden (fout 60); de omschrijving en de andere velden wel.

**Subtotalen op de proef- en saldibalans corrigeren.** Een subtotaalteller van een niveau wordt pas op nul gezet bij het afdrukken van een subtotaal van dat niveau of een hoger niveau. Voorbeeld: rekeningen 6200, 6201, 6210, 6211 en dan totaalrekening 621 (niveau 3). Het totaal 621 zou dan ook 6200 en 6201 bevatten. Oplossing: maak een hulprekening die net voor de eerste gewenste rekening komt, bv. `62999999` (omschrijving REK62999999) met totalisatieniveau 3 en "printen totaal" = `N`. Die zet de teller van niveau 3 op nul zonder een (nietszeggend) totaal af te drukken.

Lijsten: 9.3.4 (per codenummer) en 9.3.5 (alfabetisch) starten onmiddellijk met printen en tonen per rekening: centraliseren, boeken toegestaan, aankoopkolom, verkoopkolom, BTW-vak, niveau totalisatie, afprinten totaal, Intrastat J/N.

## 5. Punt + - Aanpassen systeemparameters

Oproepen: op het hoofdmenu boekhouding de verborgen toets `+` indrukken.

**Waarschuwing**: wijzigingen gelden meteen voor alle gebruikers; bij sommige punten (vooral `+.2`) worden bestanden gesloten, wat problemen kan geven voor andere actieve gebruikers. Voer dit enkel uit als er geen andere gebruikers actief zijn. Zolang niets weggeschreven is, kan met `F6` geannuleerd worden.

| Punt | Inhoud |
|---|---|
| +.1 | Firmagegevens |
| +.2 | Naam en plaatsing van de bestanden |
| +.3 | Boekhoudparameters (meerdere schermen, o.a. journalen) |
| +.4 | Facturatieparameters |
| +.5 | Voorraadbeheerparameters (in optie) |
| +.6 | Papier-, lettertype en printer |
| +.7 | Systeemdatum |
| +.8 | Paswoorden |
| +.9 | Uitschrijven sequentiele bestanden (in optie) |
| +.F | Papierformaten |
| +.B | Bekijken/afdrukken brieven van laatste modem-update |
| +.C | Conversie data-bestanden (in optie) |
| +.D | Boekhouding: diverse hulpprogramma's (in optie) |

### 5.1 +.1 Firmagegevens

Naam, adres, bankrekeningnummer (ook IBAN/BIC), BTW-nummer, website/e-mail van de eigen firma. De naam staat op de meeste menu's; het adres wordt gebruikt op rappels; het bankrekeningnummer op overschrijvingslijsten (daar nog overtikbaar). Op deze velden gebeurt geen controle; scheidingstekens (`.` en `-`) zelf intikken.

### 5.2 +.2 Naam en plaatsing van de bestanden

Per bestand de naam in de vorm `[x:]naam.ext` (x: = optionele schijfaanduiding; niets = interne harde schijf). Bestanden kunnen zo naar een andere schijf verhuisd worden (ze moeten dan ook effectief gekopieerd worden). Normaal eenmalig ingesteld bij installatie. Enkel openen als er geen andere gebruikers actief zijn. Zie ook fout 1 (bestand niet te vinden) en fout 53 (ongeldige bestandsnaam: max. 8 tekens, eerste teken een letter, extensie max. 3 tekens).

### 5.3 +.3 Boekhoudparameters

Meerdere schermen; met `F8` of `TAB` naar het volgende scherm, na het laatste scherm terug in het menu. In te vullen voor het rekeningplan ingebracht wordt en voor er geboekt wordt.

**Scherm 1 - algemeen**
- Verwerking per **M**aand, per **K**wartaal (of jaarlijks): kies in functie van de BTW-aangifte. Bepaalt ook de verplichte periodes bij archivering.
- Maandnummer van de eerste periode van het boekjaar (normaal 1; vennootschappen kunnen een andere maand kiezen).
- De 4 meest gebruikte BTW-percentages bij verkoop (liefst in stijgende volgorde): krijgen een eigen kolom in het verkoopjournaal; andere BTW-groepen komen in een losse kolom.
- Werken met wisselkoersen J/N (bij `N` verschijnt nergens een valuta-aanduiding).
- Controle van het BTW-bedrag bij manueel inboeken van verkoopfacturen J/N (bij `J` volgt een scherm met het verband BTW-vak / BTW-%; zie fout 58).
- Grootboekrekeningen die niet meegerekend worden in omzet of BTW op de BTW-listing (bv. verkoop leeggoed, ontvangen huurgelden).
- Papiertype overschrijvingslijsten: `0` = lijst (fysisch formaat via `+.6`, rubriek overschrijvingslijsten), `10` = roze overschrijvingen op kettingformulier (formaat 4), `11` = idem met voorgedrukt rekeningnummer en naam opdrachtgever.
- Papiertype rappels: `0` = blanco papier (computer drukt firmagegevens), `1` = papier met briefhoofd, `8`/`9` = idem 0/1 met overschrijvingsborderel onderaan, `10`, `18`, `19`, `20` = voorgedrukte rappelformulieren (formaat 6).

**Scherm 2 - controle BTW-bedrag** (enkel als controle gevraagd): verband BTW-vaknummers / BTW-% en maximaal toegestane afwijking (aanbevolen: 1 EUR, wegens afrondingsverschillen).

**Scherm 3 - belangrijkste grootboekrekeningen**. Verplicht in te vullen:
- Centralisatierekening leveranciers
- Centralisatierekening klanten
- Aftrekbare BTW op aankopen
- Af te dragen BTW op verkopen
- Niet-aftrekbare BTW op aankopen

De andere rekeningen mogen open blijven (maar: voor automatische betaalopdrachten is ook "bekomen disconto" nodig, en voor leeggoed een leeggoedrekening - zie fout 28 en 82). De rekeningen moeten bestaan in het rekeningplan, anders volgt bij het opstarten van punt 1 een foutmelding (fout 16 / 28).

**Volgende schermen - definitie van de journalen (dagboeken)**. Elke boeking staat op een journaal. Per journaal:

| Kolom | Uitleg |
|---|---|
| Nr | Referentienummer 1 t/m 99, vrij te kiezen, hoeft niet opeenvolgend te zijn. |
| TP (type) | 1 = aankoopjournaal; 2 = verkoopjournaal; 3 = financieel journaal; 4 = financieel journaal met automatische dagnummering; 5 = diversenjournaal; 6 = diversenjournaal met automatische dagnummering; 7 = overschrijvingsjournaal; 9 en 10 = zoals 3 en 4, maar onbetaalde boekingen op klantenrekeningen geven aanleiding tot het afdrukken van rekeninguittreksels. |
| Benaming | Tekst die overal afgedrukt wordt (bv. "Aankoopjournaal", naam van de bank). |
| Laatst | Laatst gebruikte stuknummer. De computer stelt als volgend stuk dit nummer + 1 voor. Hier manueel aan te passen. |
| Fin. reken | Grootboekrekening van het journaal; enkel (en verplicht) bij financiele journalen. Op deze rekening wordt de saldowijziging van elk uittreksel geboekt. Opgeven bij een niet-financieel journaal geeft fout 3. |
| Saldo | Enkel financiele journalen: eindsaldo van het laatst ingebrachte uittreksel. Moet in theorie overeenkomen met het boekhoudkundig saldo van de rekening; regelmatig controleren. |
| Bl.o / Bl.n | Begin-bladzijdenummer per journaal. |

Automatische dagnummering: het uittrekselnummer is `MMDD` van de boekdatum (12/01 = 0112, 20/12 = 1220; loopt van 0101 tot 1231).

Vaste afspraken rond journaalnummers die in de modules terugkomen:
- Het eerste aankoopjournaal in de lijst wordt automatisch gebruikt bij punt 1.1.
- Journaal **99** = openingsbalans (wordt aangemaakt door de module openingsbalans, 1 boeking per boekjaar).
- Journaal **35** (36, 37) type 7 met fin. rekening 5810 (5811, 5812): gebruikt voor "afboeken klantfacturen via lijst" (B.2.2) en bij automatische betaalopdrachten.

**Laatste schermen**
- "Afprinten documenten einde periode": J/N per optioneel gegeven op de periodedocumenten.
- Opzoeken van een bedrag in een financieel journaal: maximaal toegestane afwijking (bv. 1 EUR = zoekt bedragen die max. 1 EUR afwijken) en of tegelijk in debet en credit gezocht moet worden. Wordt gebruikt bij het inbrengen van betalingen zonder referentie (2.1.2).
- Rekeningen voor omrekenverschillen per aankoop-/verkoop-/financieel journaal.
- In recentere versies: na enkele keren `F8` kan hier ook de **verantwoordelijke** (bv. de boekhouder, aangemaakt als leverancier) ingegeven worden die als verantwoordelijke in het Intervat-bestand van de BTW-listing wordt uitgeschreven.

**Na spanningsuitval of na het schrappen van het laatst geboekte stuk**: controleer in dit scherm het laatst gebruikte stuknummer ("Laatst") en het saldo van het betrokken journaal en corrigeer ze.

### 5.4 +.4 Facturatieparameters

- 4 vaste teksten die op de factuur geplaatst kunnen worden (bij het factureren aanduiden met nummer 1-4).
- Journaalnummer van de verkoopfacturen en het nummer van de laatst gemaakte factuur.
- Voldane facturen automatisch inboeken in het kasjournaal J/N, met het nummer van het kasjournaal.
- Tot 8 BTW-percentages (BTW-groepen), per groep een egalisatiepercentage.
- BTW% op port- en administratiekosten; `-1` = neem het laagste BTW-percentage dat op de factuur voorkomt.
- Keuzes voor het afdrukken van facturen en parameters voor de samenstelling van de grootboekrekeningen (verkooprekening = `70` + G-code + BTW%, bv. 70021, 7012, 70106; deze rekeningen moeten bestaan in het rekeningplan).

### 5.5 +.6 Papier-, lettertype en printer

Ongeveer 15 vaste documenttypes. Per document:
- **Papnr**: nummer van de fysische papiersoort (1-10, zie `+.F`); bepaalt smal/breed, de pitch past zich aan.
- **Mode**: `D` = dataprocessing (snel), `W` = wordprocessing (mooi).
- **Prtnr**: printer 1, 2 of 3.

### 5.6 +.7 Systeemdatum

De systeemdatum wordt bij het opstarten overgenomen van de computer en wordt voorgesteld als boekdatum, afdrukdatum enz. Wie veel stukken op een andere datum wil boeken, kan hier de systeemdatum van het pakket tijdelijk aanpassen. Dit verandert de Windows-datum niet.

### 5.7 +.8 Paswoorden

- 3 paswoorden = 4 gebruikersniveaus: niveau 0 (geen paswoord, vrij toegankelijk), niveau 1, 2 en 3. Wie het paswoord van een niveau kent, kan alle onderdelen van dat niveau en lager uitvoeren. Niveau 3 is nodig om de paswoorden zelf te wijzigen (bedrijfsleider).
- Werden nog geen paswoorden gebruikt, dan vraagt de computer of men ze wil gebruiken (`F4` = ja, `F5` = nee). Anders wordt eerst het paswoord van niveau 3 gevraagd.
- Bestaande paswoorden worden nooit getoond: `~` = nog geen paswoord op dat niveau, `#` = er is een paswoord ingesteld. `F8` stelt de paswoorden in.
- Daarna per module het beveiligingsniveau kiezen, en op een volgend scherm per individuele lijst.
- Foutmeldingen: 50 (foutief paswoord, gebruik geweigerd) en 51 (paswoord van niveau 3 vereist).
- **Paswoord van niveau 3 vergeten**: ga naar `+.8`, druk bij de vraag naar het paswoord op `F4`. De computer toont een code. De bedrijfsleider neemt met die code contact op met Jamadata en krijgt (enkel telefonisch) een eenmalig paswoord waarmee alle paswoorden aangepast kunnen worden.

### 5.8 +.F Papierformaten

Maximaal 10 papierformaten, elk beschreven door 7 afmetingen in 1/300 inch (300 = 1 inch = 2,54 cm; waarden kunnen negatief zijn) en een aanduiding kettingpapier:

| Parameter | Betekenis | Voorbeeld |
|---|---|---|
| d1 | Breedte fysisch blad (pinfeed inbegrepen) | 2850 (24,1 cm) |
| d2 | Hoogte fysisch blad | 3600 (30,5 cm) |
| d3 | Afstand 0-positie printer tot linkerrand fysisch papier | -300 |
| d4 | Linkermarge | 300 |
| d5 | Ruimte bovenaan | 200 |
| d6 | Rechtermarge | 240 |
| d7 | Ruimte onderaan | 200 |
| Kettingpapier | J / N / S (S = sheet, losse bladen) | |

Door d3 te verhogen schuift de afdruk naar rechts. Vaste betekenis van de formaatnummers: 1 = smal papier, 2 = breed papier, 3 = factuurdocumenten, 4 = roze overschrijvingsformulieren, 5 = etiketten, 6 = voorgedrukte rappelformulieren.

### 5.9 Overige punten

- **+.9** (optie): basisgegevens (klanten, leveranciers, artikelen) uitschrijven in ASCII-tekstformaat voor import in spreadsheet of mailing.
- **+.B**: brieven (nieuwsbrieven) van de laatste update bekijken. `F4`/`F5` = volgende/vorige brief, `F2`/`F3` = bladeren in de brief, `F1` = lijst van brieven, `F8` = brief kiezen, `F9` = afdrukken, `F6` = schrappen.
- **+.C** (optie): alle gegevens van het pakket uitschrijven naar leesbaar TXT-formaat.
- **+.D** (optie): hulpprogramma om lange klant-/leveranciersrekeningen op te kuisen. Typisch voor verzamelrekeningen zoals "Particuliere klanten" of "Bancontact" met zeer veel facturen en betalingen: betalingen die niet overeenkomen met een factuurbedrag worden als voorschot geboekt, waardoor de lijst openstaande posten blijft groeien. Archiveren lost dit niet op (openstaande facturen worden nooit geschrapt) en manueel opkuisen via punt 4 is zwaar; daarvoor dient dit hulpprogramma.

## 6. Punt 6 - Grootte van de gebruikte bestanden

Toont per bestand: naam, in gebruik, vrij, totaal. Een bestand met minder dan 5 % vrije plaats wordt in het **rood** gemarkeerd: neem dan contact op met Jamadata (bestand laten vergroten). Voor sommige bestanden (lev, klt, art, ...) kan de teller afwijken; met `F7` (niet vermeld op het scherm) telt de computer de fiches effectief na. Verwante foutmeldingen: 9, 48, 49, 64.

## 7. Punt 7 - Wisselkoersen

- Enkel relevant als in `+.3` "werken met wisselkoersen" op `J` staat. Dan verschijnt bij het inboeken van inkomende facturen een valutaveld (standaard EUR) dat vervangen kan worden door de afkorting van een vreemde munt (bv. USD). Alle bedragen van die factuur, ook de uitsplitsing, mogen dan in die munt ingegeven worden; de computer rekent om naar EUR.
- De koers wordt ingegeven via punt 7: de waarde van de vreemde munt die overeenkomt met 1 EUR. Het scherm heeft een vast deel (oude EMU-koersen) en een kader voor 12 eigen koersen; daarin mogen enkel niet-EMU-munten staan.
- Na het wijzigen van koersen het programma afsluiten en opnieuw starten, zodat de nieuwe koersen voor elke gebruiker gelden.
- Het verschil tussen omgerekend en werkelijk betaald bedrag wordt bij de betaling weggeboekt als voordelig of nadelig koersverschil.
- Een niet-bestaande valuta geeft fout 57 / 71.

## 8. Technische limieten (theoretische capaciteit)

| Gegeven | Maximum |
|---|---|
| Klanten | 30.000 |
| Leveranciers | 30.000 |
| Grootboekrekeningen | 5.000 |
| Journalen | 40 |
| Boekingen (niet-gearchiveerd) | 65.000 |
| Tekens per grootboekrekeningnummer | 8 |
| Totalisatieniveaus | 9 |
| Types journalen | 7 |
| Papierformaten | 10 |
| Uitsplitsingen per factuur | 10 |
| Boekingen per uittreksel | 100 |
| Opmerkingen per uittreksel | 127 |
| Archivering | per maand of per kwartaal |

De werkelijke maxima in een concrete installatie kunnen lager liggen (zie punt 6).

## 9. Algemene raadgevingen uit de handleiding (relevant voor support)

- **Back-up**: regelmatig een kopie nemen op wisselende dragers (bv. een USB-stick per weekdag). Zeker een back-up nemen net voor een archivering.
- **Gegevensbeschadiging** treedt op in drie gevallen: de computer uitzetten terwijl Windows niet volledig afgesloten is (ook als het Jamadata-programma al gesloten is), een slechte back-up terugzetten, of defecte hardware (geheugen, harde schijf). Altijd Windows afsluiten via Start; bij een blokkering eerst CTRL-ALT-DEL proberen.
- Na een onderbreking zet het programma **FASREP** bij het heropstarten de bestanden terug op orde (zie `boekhouding-archivering-en-foutenlijst.md`).

## 10. Koppeling met externe boekhoudpakketten

Klanten die hun boekhouding niet in Jamadata voeren maar bij een boekhouder of in een ander pakket, kunnen gegevens laten uitschrijven naar een extern pakket. Volgens de interne lijst bestaan er exports/koppelingen voor onder meer: TopAccount/Toppower, Exact, Exact Online (XML of UBL via mail), Venice (UBL), ZEN-boekhouding (UBL), Pro-acc/Prolink, Winbooks, Winbooks for Web, PingWin, Accoms, Calculo, C-Logic/Venice, Expert/M (ook in XML), Octopus (ook in XML), CashFlowByWeb, VERO, Adsolut (ook UBL, uitgeschreven in de map `\factubl`), BOB (Sage), Integral, Yuki, Briljant, WinAudit, Popsy, Horus (UBL), WingsOnline, Billit, Zenvoices en Clearfacts. Welke klant welk pakket gebruikt, staat in de interne bron (niet opgenomen). De concrete instelling per pakket staat niet in de bronnen: te verifieren bij een ontwikkelaar/senior.

## Bronnen

- `Gebruikerhandleiding BOEKHOUDPAKKET.docx` (map boekhouding) - versie V06, 12-8-2014: hoofdstukken "Enkele raadgevingen", "Gebruik en werken met de schermen", punt 9, punt 6, punt 7, punt +, "Opzoeking van gegevens", "Technische gegevens".
- `0059A - BTW-listing.docx` (map boekhouding) - voor de recentere schermelementen (icoon niet-BTW-plichtig, verantwoordelijke in +.3).
- `EXT_BKH.docx` (map boekhouding) - lijst externe boekhoudpakketten (klantcodes weggelaten).
