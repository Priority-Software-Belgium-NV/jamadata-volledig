# Jamadrink: offertes, verhuur/uitlenen van materialen en klantenrappels

Gebruik dit document voor: vragen over het maken, afdrukken, mailen en hergebruiken van prijsoffertes (V.5.6), het registreren en opvolgen van verhuurde of uitgeleende materialen (V.8.B) en het opmaken en afdrukken van klantenrappels met eigen brieven, intrest- en boeteberekening (B.5.3), inclusief alle codes die in rappelbrieven gebruikt kunnen worden.

## 1. Beheer offertes (V.5.6) – module 0266A

### Waarvoor

Prijsofferte maken voor bestaande of nieuwe klanten: een korte offerte met enkele artikels of een uitgebreid overzicht van geselecteerde artikels. Met één knop wordt een kant-en-klare offerte-mail aangemaakt.

### Voorbereiding: "offerte-klanten"

Maak per prijscategorie (café, frituur, feest, bedrijf...) eenmalig een klantenfiche aan via `V.9.2`, bv. "Offerte cafe", "Offerte feest". Koppel aan die fiche het juiste prijstype en de kortingen/prijsafspraken voor die categorie. Die fiche dient als prijsbron voor offertes aan nieuwe klanten.

### Stappen

1. `V.5.6`: kies tussen een **bestaande** offerte aanpassen of een **nieuwe** maken.
2. **Artikelscherm**:

| Veld | Uitleg |
|---|---|
| Prijzen van klant | Naam/code van een bestaande klantenfiche waarvan prijzen en kortingen genomen worden. Bestaande klant: zijn eigen fiche. Nieuwe klant: de passende "offerte-klant". **Wijzig deze klant niet tijdens het ingeven**: reeds ingegeven artikels behouden hun prijzen/kortingen |
| Datum v/d prijzen | Een latere datum geeft de toekomstige prijzen, op voorwaarde dat die vooraf zijn ingegeven via Prijswijzigingen op datum (`V.3.4`). Bruikbaar voor een feest over een maand of een prijslijst met de nieuwe prijzen |
| Aantal | Met het ene icoon wordt de kolom Aantal invulbaar en krijg je een **uitgerekende offerte**; met het andere icoon is de kolom niet aanpasbaar en krijg je enkel een **prijslijst** |
| Artnr / Omschrijving | Begint de omschrijving met `*`, dan wordt geen artikel gezocht: vrije tekstlijn of artikel dat nog niet bestaat |
| Normale prijs | Basisprijs voor deze klant, incl. of excl. btw volgens het prijstype (meestal excl.) |
| Kort% | Directe korting op factuur |
| Nettoprijs | Netto factuurprijs excl. btw. **Rood = negatieve winst** na verrekening van directe én uitgestelde korting |

| Toets | Functie op het artikelscherm |
|---|---|
| `F1`/`F6` | Stop |
| `F2` / `F3` | Scherm (16 lijnen) terug / vooruit |
| `F4 wis lijn` | Huidige lijn wissen |
| `F5 voeg in` | Lege lijn invoegen |
| `F7 herdisplay` | Prijzen herberekenen en artikels opzoeken |
| `F8 ga verder` | Naar het afsluitscherm |
| `F9 prijsdetail` | Detail van de huidige lijn: normale prijs, korting %, hectoliterkorting (EUR, al omgerekend naar de inhoud), totale factuurkorting, factuurprijs excl./incl. btw, prijs leeggoed, semestriële korting % en hectoliterkorting, totale semestriële korting, accijns, btw%, aankoopprijs, winst% |
| Icoon "selectie" | Automatisch artikels toevoegen via de uitgebreide artikelselectie (leverancier, groep, merk, artikelfiche, datum prijswijziging, bestelbon klant, klantenstatistiek max. 2 jaar, prijsafspraak) |
| Icoon "vernieuw prijzen" | Vernieuwt de prijzen van **alle** ingegeven artikels: kortingen blijven, **specifiek ingegeven prijzen gaan verloren**. Te gebruiken na een prijsopslag |

3. **Afsluiting offerte**:
   - Naam en adresgegevens: de echte klantgegevens die op de offerte komen.
   - Datum; **Referentie** (waaronder de offerte bewaard wordt, ook afgedrukt).
   - Teksten af te drukken op document: 6 vrije lijnen onderaan.
   - Af te drukken kolommen: Basis verkoopprijs, Accijns, Factuurkorting (%), Factuurkorting (EUR), Factuurprijs, Semestriële korting %, Semestriële korting (EUR), Netto verkoopprijs (factuurprijs min uitgestelde kortingen), Prijs leeggoed, Winst% (voor eigen gebruik).
   - Kies je enkel factuurprijs of nettoprijs, dan wordt ook de prijs incl. btw gedrukt. Bij een offerte met aantallen komen totalen per lijn in de kolommen "Goederen" en "Leeggoed".

| Toets / knop | Functie op het afsluitscherm |
|---|---|
| `F1 stop/nieuwe offerte` | Wist de huidige offerte; je kan een nieuwe maken |
| `F2 terug naar detail` | Terug naar het artikelscherm |
| `F8 druk af` | Afdrukken; daarna de vraag om de offerte op te slaan |
| Pdf-knop | Pdf van de offerte |
| Mail-knop | Voorgedefinieerde mail met de offerte in bijlage |

### Standaardinstellingen (V.5.6.+)

- Standaard af te drukken kolommen (zelfde lijst als hierboven).
- Instellingen die voor **alle** offertes gelden (niet per offerte te wijzigen):
  - Verkoopprijzen zonder accijns afdrukken.
  - Eigen firmagegevens afdrukken (aanvinken bij blanco papier).
  - Vaste teksten: 4 standaardlijnen (bv. "Offerte is 14 dagen geldig").

### Offerte hergebruiken

- **Op bon/factuur**: op het artikelscherm rechtsonder het `+`-icoon → knop "offerte" → offerte opzoeken; artikels én prijzen worden toegevoegd (zie `jamadrink-bons-en-facturen.md`).
- **Als prijsafspraken**: de gebruikershandleiding vermeldt onder `V.9.5.2` "Toevoegen reeks prijsafspraken via offerte" (zie documentatie prijzen).
- **Op de klantenfiche**: extra opties (`+`) → Offertes toont de offertes van die klant.

### Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Prijzen op de offerte kloppen niet met de klant | "Prijzen van klant" verwijst naar een andere fiche, of de klant werd gewijzigd nadat lijnen waren ingegeven (bestaande lijnen behouden hun prijs); `F7 herdisplay` of lijnen opnieuw ingeven |
| Na een prijsopslag staan oude prijzen in een bewaarde offerte | Icoon "vernieuw prijzen" (let op: handmatig ingegeven prijzen verdwijnen) |
| Toekomstige prijzen verschijnen niet | Prijswijziging op datum nog niet ingegeven in `V.3.4`, of "Datum v/d prijzen" niet aangepast |
| Offerte toont geen totalen | Kolom Aantal staat uit (prijslijstmodus) |
| Firmagegevens ontbreken op blanco papier | `V.5.6.+` → "Eigen firmagegevens afdrukken" |
| Nettoprijs staat rood | Verlieslatend na alle kortingen; controleer met `F9 prijsdetail` |

## 2. Verhuren/uitlenen van materialen (V.8.B) – module 0264A

### Waarvoor

Materialen (tafels, stoelen, frigo's...) die uitgeleend of verhuurd worden registreren en opvolgen: zien of er voldoende stuks zijn in een periode en waar het materiaal zich bevindt.

### Voorbereiding

- Maak voor elk te verhuren artikel een artikelfiche. In de prijzen staat de verhuurprijs (bij het uitlenen nog te wijzigen).
- Vul op de artikelfiche **Max. verhuuraantal** in: het maximale aantal stuks dat je kan verhuren.

### Menu "Beheer verhuur" (hoofdmenu → 8 Facturatie → Beheer uitlenen/verhuren van materialen)

| Punt | Functie |
|---|---|
| 1 | **Uitlenen artikelen**: klant, periode van de verhuur, artikels met aantal. Een nieuwe klant kan hier toegevoegd worden. Zijn er in de periode te weinig stuks, dan volgt een foutmelding met gewenst en voorradig aantal. Daarna wordt een bon afgedrukt die de klant kan tekenen voor ontvangst |
| 2 | **Binnenbrengen van uitgeleende artikelen**: klantnaam of bonnummer ingeven; in de lijst de teruggebrachte artikels aanduiden met J/N. `F8` maakt een **leveringsbon** (later te factureren) en schrapt de geselecteerde uitleningen. `F10` schrapt de geselecteerde uitleningen zonder bon |
| 3 | **Raadplegen**: zonder klant en artikel (bv. enkel periode) = lijst van alle verhuurartikels met stuks; `F8` op een artikel geeft het detail. Met klant = wat hij huurt. Met artikel = welke klanten het in huur hebben |
| 4 | **Aanpassen**: klant ingeven, `F8`, bon kiezen; aanpassen en opnieuw afdrukken |
| 5 | **Afdrukken lijst uitleningen** |

### Koppeling met bons en facturen

- Bij het maken van een bon/factuur voor een klant die artikels huurt, verschijnt de lijst van verhuurde items en kan je ze toevoegen.
- Manueel: op het artikelscherm rechtsonder de groene `+` → knop "verhuurbon" → gewenste artikels selecteren.
- Bij het binnenbrengen (punt 2) kan meteen een leveringsbon gemaakt worden.
- Op de klantenfiche: extra opties (`+`) → Verhuringen.

### Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Melding "onvoldoende stuks" bij uitlenen | In de periode is het Max. verhuuraantal bereikt; kijk via punt 3 wie het materiaal heeft of pas Max. verhuuraantal op de artikelfiche aan |
| Materiaal blijft als uitgeleend staan | Het is nooit binnengebracht via punt 2; binnenbrengen met `F8` (met bon) of `F10` (zonder bon) |
| Verhuur wordt niet gefactureerd | Bij binnenbrengen `F8` gebruiken (maakt leveringsbon) en die bon daarna factureren via `V.8.2` |

## 3. Klantenrappels (B.5.3) – module 0023A

### Waarvoor

Rekeninguittreksels/aanmaningen voor klanten afdrukken of mailen, met zelf opgestelde brieven. (Instellingen voor het mailen zelf: zie documentatie mail.)

### Werking

Bij het afdrukken geef je bovenaan de **Einddatum vervallen** in; daarmee wordt het aantal dagen vervallen berekend. Je kan 3 basisteksten met een periode opgeven:

- normale rappel: oudste factuur is maximaal X dagen vervallen;
- 2de rappel: oudste factuur is maximaal Y dagen vervallen;
- 3de rappel: oudste factuur is langer vervallen dan het voorgaande.

Dezelfde brief mag voor de drie situaties gebruikt worden. De vervaldatum van een factuur komt van de betalingstermijn op de klantenfiche.

### Meegeleverde voorbeeldbrieven

| Naam | Inhoud |
|---|---|
| rap1 | Normale rappel |
| rap2 | 2de herinnering |
| rap3 | Rappel met intrestberekening |
| rap4 | Rappel met intrest- en boeteberekening |
| rap6 | Normale rappel, andere bewoordingen |
| rap9 | Rappel met intrestberekening (eigen gebruik) |

### Brieftekst aanpassen

1. Ga naar het rappelprogramma `B.5.3` en druk `F10`.
2. Geef de naam van de brief. Geen naam of een onbestaande naam geeft een lege brief.
3. `F8` opent de tekst.

| Toets | Functie in de teksteditor |
|---|---|
| `F2` / `F3` | Scherm omhoog / omlaag |
| `F4` | Huidige lijn schrappen |
| `F5` | Lege lijn invoegen |
| `F6` | Wijzigingen annuleren |
| `F8` | Wegschrijven; je kan een nieuwe naam geven om een nieuwe brief te maken |
| `F9` | 50 tekens naar rechts / terug naar links schuiven |
| `F12` | Brief afdrukken als proef |

### Tekstcontroletekens

| Code | Betekenis |
|---|---|
| `@@` | Drukt het teken @ af (bv. in een e-mailadres) |
| `@!xx` | Blad doordraaien tot er nog xx lijnen vrij zijn (bv. `@!23`: het volgende komt op de 23e laatste regel) |
| `<?>...<?>` | Tekst tussen de tekens in een bepaalde stijl; vervang `?` door: `b` vet, `e` brede letters, `u` onderlijnd, `c` gecentreerd, `t` tabulatie (gevolgd door getal). Combinaties mogen, bv. `<be>` |

### Gegevenscodes

Hou bij het schikken rekening met de veldlengte (bv. klantnaam minstens 30 tekens).

Klant en boeking:

| Code | Gegeven |
|---|---|
| `@2,2` | Code of volgnummer klant |
| `@2,3` | Naam klant |
| `@2,4` | Straat klant |
| `@2,5` | Postnummer klant |
| `@2,6` | Gemeente klant |
| `@2,7` | Land klant |
| `@4,2` | Journaalnummer boeking |
| `@4,3` | Volgnummer binnen journaal (factuurnr of uittrekselnr) |
| `@4,4` | Datum boeking |
| `@4,21` | Vervaldatum |
| `@4,24` | Factuurmunt |
| `@26,3` | Verzendingsdatum rappel |

Bedragen (EUR):

| Code | Gegeven |
|---|---|
| `@80,7` | Totaalbedrag (+ of -) |
| `@80,10` | Type beweging (Fact/Bet...) |
| `@80,11` / `@80,12` | Debetbedrag / creditbedrag |
| `@80,21` / `@80,22` | Totaal debet / totaal credit |
| `@80,23` | Totaalbedrag inclusief boete en verwijlintresten |
| `@80,24` | Totaalbedrag boete |
| `@80,25` | Totaalbedrag verwijlintresten |
| `@80,26` | Aantal dagen dat deze factuur vervallen is |
| `@80,27` | Bedrag verwijlintresten voor deze factuur |
| `@80,28` / `@80,29` | Totaalbedrag vervallen / niet vervallen (+ of -) |
| `@80,39` | Gestructureerde mededeling (klantcode + factuurnummer + checkdigits) |
| `@80,40` | Veld 80,39 dubbel geprint |
| `@80,41` | Veld 80,7 dubbel geprint |
| `@80,42` | Veld 80,7 dubbel geprint, met spatie voor de komma (voor afdruk op overschrijving) |

Bedragen in vreemde munt (VM):

| Code | Gegeven |
|---|---|
| `@80,51` / `@80,52` | Debet / credit (EUR of vreemde munt) |
| `@80,53` / `@80,54` | Totaal debet / credit (VM) |
| `@80,55` / `@80,56` | Bedrag vervallen / niet vervallen (VM) |
| `@80,57` | Totaal inclusief boete en verwijlintresten (VM) |
| `@80,58` | Totaal boete (VM) |
| `@80,59` | Totaal verwijlintresten (VM) |

Boete en intrest (instelcodes, best bovenaan in de tekst):

| Code | Betekenis |
|---|---|
| `@*xx,xx` | Percentage van de boete |
| `@Bxxxx,xx` | Minimumbedrag van de boete; is de berekende boete lager, dan geldt dit bedrag (bv. `@B0060,00`) |
| `@Ixx,xx` | Percentage verwijlintresten **per maand** (bv. `@I01,25`) |

Eigen firmagegevens:

| Code | Gegeven | Code | Gegeven |
|---|---|---|---|
| `@80,80` | Firmanaam | `@80,87` | Bankrekening |
| `@80,81` | Straat | `@80,88` | RPR |
| `@80,82` | Postcode | `@80,89` | Erkenningsnummer |
| `@80,83` | Gemeente | `@80,90` | Website |
| `@80,84` | Telefoon | `@80,91` | E-mail |
| `@80,85` | Telefax | `@80,92` | IBAN |
| `@80,86` | Btw-nummer | `@80,93` | BIC |

### Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Het @-teken in een e-mailadres verdwijnt of geeft rare tekst | Schrijf `@@` |
| Geen intrest of boete op de rappel | De brief bevat geen `@I..` / `@*..` / `@B..` regel, of de gebruikte brief is rap1/rap2 in plaats van rap3/rap4 |
| Kolommen verspringen | Veldlengtes: reserveer genoeg ruimte na een code (klantnaam min. 30 tekens); gebruik `F12` voor een proefafdruk |
| Verkeerde brief wordt gebruikt | De drie basisteksten en hun dagengrenzen in het afdrukscherm nakijken |
| Klant krijgt rappel voor niet-vervallen factuur | Einddatum vervallen en betalingstermijn op klantenfiche controleren |
| Welke facturen staan open? | Lijst openstaande/vervallen facturen `B.5.8` (zie `jamadrink-bons-en-facturen.md`) |

## Bronnen

- `0266A - Beheer offertes.docx` (map Jamadrink/Handleidingen modules)
- `0264A - Beheer verhuur-uitlenen van materialen.docx` (map Jamadrink/Handleidingen modules)
- `0023A - Klantenrappels.docx` (map Jamadrink/Handleidingen modules)
- `0240A - Extra functies bij aanmaken van een bon-factuur.docx` (map Jamadrink/Handleidingen modules)
- `gebruikershandleiding JAMADRINK 2.0.docx` (map Jamadrink): V.8, V.9.2.1, V.9.5.2
