# Boekhouding in Jamadata: periodelijsten, balansen, rekeningen, rappels, openstaande posten, vervaldagbalans en maandtotalen

Gebruik dit document voor: vragen over het afdrukken van lijsten uit de boekhouding (punt B.5): fouten- en controlelijst, journalen, BTW-aangifte, centralisatiejournalen, rekeningen en balansen (B.5.1), rekeningen van klanten/leveranciers/grootboek (B.5.2), klantenrappels (B.5.3), lijst vervallen/openstaande facturen (B.5.8), de vervaldagbalans/aging list, maandtotalen klant/leverancier/grootboek en de overige lijsten in optie (B.5.0). De BTW-listing, intracommunautaire opgave en Intrastat staan in `boekhouding-btw-listing-ic-intrastat.md`.

## 1. Overzicht punt 5 - Afprinten lijsten

| Punt | Lijst |
|---|---|
| 5.1 | Periodelijsten: fouten- en controlelijst, journalen, BTW-aangifte, centralisatiejournalen, rekeningen, balansen |
| 5.2 | Rekeningen van klanten, leveranciers en grootboek (vrije periode, ook uit jaararchief; ook naar TXT) |
| 5.3 | Klantenrappels |
| 5.8 | Lijst vervallen/openstaande facturen |
| 5.9 | Jaarlijkse BTW-listing / intracommunautaire opgave |
| 5.0 | Menu lijsten in optie |
| 5.+ | Afdrukinstellingen BTW-formulieren |

Papierformaat, afdrukkwaliteit en printer per lijst worden ingesteld in `+.6`; de fysische formaten in `+.F` (zie `boekhouding-basis-en-dagboeken.md`).

## 2. B.5.1 - Periodelijsten

### 2.1 Selectiescherm

Eén scherm waarop meerdere lijsten tegelijk aangevraagd kunnen worden (de computer drukt ze na elkaar af). Journalen en balansen kunnen niet op het scherm bekeken worden.

**Periode van ... tot en met ...**
- Voor **rekeningen en balansen** is de begindatum verplicht de dag na de laatste archiveringsdatum (staat onderaan het scherm). Voorbeeld: gearchiveerd tot 31/03 -> begindatum 01/04. Een andere datum geeft fout 35. Nog nooit gearchiveerd: elke datum mag, neem bij voorkeur de eerste dag van de maand waarin met de boekhouding gestart is.
- Voor **journalen en centralisatiejournalen** mag de begindatum vrij gekozen worden, zolang ze na de archiveringsdatum valt (ook midden in een maand; het journaal begint dan pas vanaf die datum).
- Einddatum: normaal het einde van de maand of het kwartaal. Moet na de begindatum vallen en in hetzelfde kalenderjaar (en hetzelfde boekjaar als dat niet op 1 januari begint) - anders fout 27/36.

**Selectie voor foutenlijst, journalen en centralisatiejournalen**: van journaal/volgnummer tot journaal/volgnummer. Alles op 0 = alle journalen. Enkel het aankoopjournaal: zelfde journaalnummer als begin en einde. Facturen 10 t/m 20: zelfde journaalnummer + beginvolgnummer 10 en eindvolgnummer 20.

Daarna per lijst `J` of `N`. Rekeningen en balansen kunnen apart gevraagd worden voor leveranciers, klanten en grootboek. Bij de balansen vraagt de computer nog of de lijst in een bestand bewaard moet worden (`F4` = nee, `F5` = ja).

### 2.2 Fouten- en controlelijst van de journalen

Analyseert de boekingen binnen de opgegeven grenzen. **Druk deze lijst altijd eerst af**, los de fouten op en druk dan pas de officiele documenten. Ze meldt:

| Controle | Betekenis / oplossing |
|---|---|
| Eerste en laatste volgnummer per journaal | Controle welke stukken geboekt zijn. |
| Ontbrekende stuknummers | Vergeten facturen/uittreksels; kunnen nog ingebracht worden. |
| Dubbel geboekte factuurnummers | Schrappen via "Schrappen boekhoudbewegingen" (punt U). Let op: men schrapt dan **beide** stukken met dat nummer; de juiste factuur moet opnieuw ingebracht worden. De controle loopt over het hele jaar. Facturen van een vorig boekjaar mogen hetzelfde nummer hebben. |
| Verschillende boekdatums binnen één uittreksel | Meerdere uittreksels met hetzelfde nummer mogen (opsplitsing van lange uittreksels), maar enkel op dezelfde boekdatum. |
| Stijgend nummer met dalende boekdatum | Volgnummer en boekdatum moeten in dezelfde volgorde staan (factuur 1 op 02/01 en factuur 2 op 01/01 is fout). Oplossen door één stuk te schrappen en met een andere boekdatum te boeken. |
| Debet <> credit per stuk | Wordt gemeld met journaal en volgnummer. |

### 2.3 Journalen

Types: aankoopjournaal, verkoopjournaal, financieel journaal (bank), kasjournaal, diversenjournaal, overschrijvingsjournaal. Van elk type kunnen meerdere journalen bestaan (bv. apart journaal voor goederen- en onkostenfacturen, of voor creditnota's). De definitie staat in `+.3`.

- Aankoopjournaal: 3 kolommen voor de uitsplitsing (goederen, BTW, alle andere rekeningen), bepaald door de "aankoopkolom" op de grootboekfiche.
- Verkoopjournaal: kolommen per BTW-groep (de 4 meest gebruikte percentages uit `+.3`, de rest in een losse kolom), bepaald door de "verkoopkolom" op de grootboekfiche.

Een journaal afdrukken is ook de manier om te zien wat er op een overschrijvings-/betaaljournaal (bv. 35), het afschrijvingsjournaal of een kasjournaal geboekt is, en om na een stroomuitval te controleren welke boekingen weggeschreven zijn.

### 2.4 BTW-aangifte (5.1.3)

De papieren aangifte bestaat niet meer; de aangifte gaat elektronisch via Intervat. De afdruk gebeurt als lijst.

1. Kies de BTW-aangifte op het scherm van 5.1. U krijgt een scherm met de getallen (vakken); druk `F8`.
2. Beantwoord de vragen op het volgende scherm en druk opnieuw `F8`.
3. De aangifte wordt opgeslagen als XML-bestand met de naam `BTW-???.xml`, waarbij `???` de dossiercode is (meestal `FAS`, dus `BTW-FAS.xml`). In recentere versies komen Intervat-bestanden in `Documenten\JamaData\Diversen` (zie het BTW-listing-document); de exacte naam en map van het aangiftebestand in recente versies is in de bronnen niet beschreven (te verifieren).

De vakken worden gevuld op basis van het "Vak BTW-aangifte" op elke grootboekfiche. Intracommunautaire en medecontractant-stukken worden herkend aan de rekeningen met vak 86 en 87 (zie `boekhouding-facturen-en-financiele-verrichtingen.md`).

**5.+ Aanpassen afdrukinstellingen BTW-formulieren**: keuze van de afdrukvorm (`O` = oud formulier, `L` = lijst, `D` = BTW-document), offsetwaarden horizontaal/verticaal voor het officiele document (een waarde van 11 komt ongeveer overeen met 1 mm) en naam, hoedanigheid en telefoonnummer van de ondertekenaar.

### 2.5 Centralisatiejournalen

Per journaal een totaal debet en credit per grootboekrekening. De individuele leveranciers en klanten worden gecentraliseerd op de centralisatierekening leveranciers/klanten uit `+.3`. Bruikbaar ter controle van de BTW-aangifte (bv. verkoop per BTW-tarief en teruggenomen via creditnota's).

### 2.6 Rekeningen

- **Leveranciers- en klantenrekeningen**: alfabetisch op naam. Per rekening: alle nog openstaande bewegingen uit vorige periodes + alle bewegingen van de huidige periode = nieuw saldo op de afsluitdatum. Facturen die samen met hun betaling in evenwicht zijn, verdwijnen na de archivering; enkel onbetaalde stukken komen in de volgende periode terug. **Daarom deze lijsten volledig afdrukken voor de archivering.**
- **Grootboekrekeningen**: vertrekt van het eindsaldo na de vorige afsluiting, gevolgd door de bewegingen in detail of enkel een gecentraliseerd totaal, afhankelijk van "Centralisatie J/N" op de grootboekfiche.

### 2.7 Balansen

Drie delen: leveranciersbalans, klantenbalans, proef- en saldibalans van het grootboek. Per rekening één lijn:

| Kolom | Inhoud |
|---|---|
| Nr | Codenummer |
| Omschrijving | Naam van de rekening |
| Nieuw saldo | Saldo op het einde van de periode |
| Vorig saldo | Saldo bij het begin van de periode |
| D-periode / C-periode | Totaal debet / credit in de opgegeven periode |
| D-jaar / C-jaar | Totaal debet / credit over het hele boekjaar |

Rekeningen waarop nog niet geboekt is, worden niet afgedrukt. De subtotalen op de proef- en saldibalans volgen de totalisatieniveaus van de grootboekfiches (zie `boekhouding-basis-en-dagboeken.md`, 4.6 voor het corrigeren van foute subtotalen).

## 3. B.5.2 - Rekeningen van klanten, leveranciers en grootboek

Rekeningen afdrukken over een **vrije periode**, eventueel uitschrijven naar een TXT-bestand. De computer zoekt zowel in het jaararchief (indien gearchiveerd en indien de optie aanwezig is) als in de lopende boekingen.

| Veld | Uitleg |
|---|---|
| Periode ... t.e.m. ... | Gewenste periode van de boekingen. |
| Leveranciersrekeningen J/N, vanaf / tot en met | Geen van/tot = allemaal. Geen "van" = vanaf de eerste in het alfabet; geen "tot" = tot de laatste. "Tot" moet alfabetisch na of gelijk aan "van" liggen. |
| Klantenrekeningen J/N | Zelfde werkwijze. |
| Grootboekrekeningen J/N | Zelfde, maar met rekeningnummers. |

Onderaan staan informatief de archiveringsdatum en de datums tot wanneer het jaararchief gewist is (leveranciers/klanten/grootboek). Start met `F8`.

Opmerking over "Centralisatie J/N": rekeningen met zeer veel bewegingen (bv. BTW-rekeningen, één boeking per factuur) kunnen op `J` gezet worden zodat enkel een totaal bijgehouden wordt. Gevolg: het detail wordt bij archivering niet in het jaararchief opgenomen en is later niet meer op te vragen; terug op `N` zetten geldt enkel voor boekingen die nog niet gearchiveerd zijn.

## 4. B.5.3 - Klantenrappels

### 4.1 Waarvoor

Rekeninguittreksels/aanmaningen voor klanten met vervallen onbetaalde facturen (of ter herinnering aan facturen die binnenkort vervallen). Er zijn 3 basisteksten: rappel, 2de aanmaning en 3de aanmaning. Papiertype rappel: `+.3` (0 = blanco, 1 = briefhoofd, 8/9 = met overschrijvingsborderel, 10/18/19/20 = voorgedrukte formulieren); fysisch formaat: `+.6` rubriek klantenrappels. Het adres van de afzender komt uit de firmagegevens (`+.1`).

### 4.2 Selectiescherm

| Veld | Uitleg |
|---|---|
| Verzendingsdatum van de rappel | Standaard de systeemdatum; geeft aan tot wanneer de rekeningen bijgewerkt zijn. |
| Toon klant alvorens te drukken (J/N) | Bij `J` wordt per klant eerst het overzicht getoond (facturen met vervaldatum, rappelnummer, datum laatste rappel) en beslist de gebruiker of er gedrukt wordt. |
| **Selecties waaraan minstens 1 factuur moet voldoen** | |
| Factuur is vervallen tussen ... t.e.m. ... | Begindatum meestal blanco (= alles wat vervallen is tot de einddatum). Einddatum standaard de systeemdatum; mag ook in de toekomst liggen. |
| Laatste keer op rappel geweest tussen ... t.e.m. ... | Selecteert klanten die al een rappel kregen en nog niet betaald hebben. Blanco = niet controleren. |
| Minimum aantal keren op rappel geweest | Blanco = niet controleren. |
| **Selecties waaraan de rappel moet voldoen** | |
| Selectie klant | Eén klant. Blanco = alle klanten. |
| Vanaf deze klant verdergaan (J/N) | Vanaf de gekozen klant alfabetisch verder. |
| Minimum bedrag dat vervallen is | Geen rappel voor kleine saldi. Blanco = niet controleren. |
| **Indien een rappel wordt afgedrukt** | |
| Betaalde facturen ook afdrukken (J/N) | Standaard `N`. |
| Niet vervallen facturen ook afdrukken (J/N) | Standaard `N`. |
| Aantal rappels te drukken per klant | Aantal kopieen. |
| Naam rappelbestand | t.e.m. 30 dagen vervallen: `RAP1`; t.e.m. 60 dagen vervallen: `RAP2`; meer dagen vervallen: `RAP3F`. De termijnen en de naam van de te gebruiken rappelbrief zijn aanpasbaar. |

Een rappel wordt enkel gedrukt als er minstens één vervallen factuur is die aan de criteria voldoet. Het overlopen van alle klanten met hun facturen en betalingen kan even duren.

### 4.3 Rappeltekst aanpassen

Druk in het rappelscherm op `F10`, vul de naam van de rappelbrief in (bv. `RAP1`) en druk `F8`. Pas de tekst aan, bewaar met `F8` en druk eventueel af met `F10`.

### 4.4 PDF / mailen

Met de PDF-optie kan de rappel via `F9` in PDF gemaakt worden (bv. om te mailen). Op de naam van de klant wordt de `*`-regel toegepast ("Janssens*Garage" -> "Garage Janssens").

### 4.5 Veelvoorkomende vragen

(Onderstaande antwoorden zijn afgeleid uit de werking die de handleiding beschrijft; het zijn geen letterlijke procedures uit de bron.)

- *Klant krijgt een rappel voor een betaalde factuur*: de betaling is geboekt zonder of met een foute referentie (staat als voorschot op de rekening). Referentie rechtzetten in het rekeningoverzicht (punt 4).
- *Klant komt niet op de rappels*: controleer de periode "vervallen tussen", het minimumbedrag, de selectie "laatste keer op rappel" en of de factuur wel een vervaldatum in het verleden heeft (betalingstermijn op de klantenfiche).
- *Betalingen van gisteren staan er niet op*: de rappel toont de stand van de boekhouding; eerst de bankuittreksels inboeken.

## 5. B.5.8 - Lijst vervallen/openstaande facturen

Lijst van alle vervallen of openstaande facturen van klanten of leveranciers.

| Veld | Uitleg |
|---|---|
| Openstaande of Vervallen facturen (O/V) | `V`: de vervaldatum moet kleiner zijn dan de einddatum. `O`: de factuur wordt afgedrukt als ze op de einddatum nog niet betaald is, vervallen of niet. |
| Einddatum vervallen/openstaand | Facturen na deze datum worden overgeslagen. Mag voor de archiveringsdatum liggen, maar dan verschijnen enkel de facturen die bij de archivering nog niet betaald waren. |
| Einddatum betalingen | Tot welke datum betalingen meegeteld worden. Voorbeeld: lijst van wat vorige maand vervallen was maar zonder wat intussen betaald is -> einddatum facturen = einde vorige maand, einddatum betalingen = vandaag. |
| Selectie klanten of leveranciers (K/L) | `K` = verkoopfacturen, `L` = aankoopfacturen. |
| Selectie 1 klant/leverancier | Optioneel. |
| Einddatum boekdatum (blanco = niet controleren) | Extra selectie op de datum van inboeken; dient om de lijst te laten **aansluiten met de balans**. Voorbeeld: een laattijdig ontvangen factuur met factuurdatum in de vorige maand die in de huidige maand geboekt is, staat wel op de lijst openstaande facturen van vorige maand (factuurdatum) maar niet op de leveranciersbalans van vorige maand (boekdatum). |

`F8` = printen; daarna nog een selectiescherm: `F8` volgens selectie of `F9` volledige lijst.

Per factuur op de lijst: code en naam klant/leverancier, normale betalingscondities, type boeking (factuur/creditnota, betaling), factuurnummer, factuurdatum, vervaldatum, bedrag, opmerking. Totaal per klant/leverancier en algemeen totaal.

**Lijst sluit niet aan met de balans?** (controlepunten afgeleid uit de beschreven werking, geen letterlijke bronprocedure) Controleer: (1) "einddatum boekdatum" invullen met dezelfde einddatum als de balans; (2) "einddatum betalingen" gelijk aan de balansdatum; (3) betalingen zonder referentie (voorschotten) en verzamelklanten; (4) of de openingsbalans klanten/leveranciers klopt (zie openingsbalans, keuze 5).

## 6. Vervaldagbalans en vervaldaglijst (aging list) - optie, B.5.0.5

### 6.1 Waarvoor

Financiele planning op basis van de openstaande facturen in de boekhouding. Twee lijsten, elk voor klanten en/of leveranciers:

- **Vervaldagbalans**: de openstaande facturen verdeeld over maximaal **8 kolommen** volgens vervaldatum.
- **Vervaldaglijst**: chronologisch per dag het totaalbedrag dat die dag vervalt, met daarnaast het cumulatief totaal.

### 6.2 Werkwijze

1. Op het selectiescherm kiezen: klanten en/of leveranciers, en welke lijst(en).
2. Startdatum: standaard vandaag, aanpasbaar.
3. Kolommen definieren t.o.v. de startdatum, ofwel in aantal dagen ofwel met vervaldagcodes:
   - in dagen: bv. `-60`, `-30`, `+30`
   - met codes: `-E3` (-90 dagen einde maand), `-E2`, ... `E1` (30 dagen einde maand), `E2`
   - de laatste kolommen mogen leeg blijven als niet alle 8 nodig zijn.
   - de datums moeten in stijgende volgorde staan (anders fout 55).

| Toets | Werking |
|---|---|
| F7 | Bereken datums: herberekent de kolomdatums na wijziging van termijnen of startdatum |
| F8 | Druk af |
| PDF-icoon | Lijsten in PDF tonen |

## 7. Maandtotalen klant/leverancier/grootboek (0067A)

### 7.1 Waarvoor

Een jaaroverzicht per maand (12 kolommen) van klanten, leveranciers en grootboekrekeningen: handig om het betalingsgedrag van klanten of het verloop van kosten te volgen. Het menupad staat niet in de bron (module met code 0067; te verifieren in het menu lijsten in optie).

### 7.2 Velden

| Veld | Uitleg |
|---|---|
| Maand/jaar eerste maand | Maandnummer en jaartal van de eerste kolom; de 11 volgende kolommen zijn de 11 daaropvolgende maanden. |
| Klanten / Leveranciers / Grootboek | Van welke rekeningen het overzicht gemaakt wordt. |
| Keuze gegevens: **Omzet** | Klanten/leveranciers: de gefactureerde bedragen. Grootboek: de som van alle boekingen op de rekening. |
| Keuze gegevens: **Saldo** | Klanten/leveranciers: openstaand saldo op het einde van de maand. |
| Keuze gegevens: **Vervallen saldo** | Klanten/leveranciers: vervallen saldo op het einde van de maand. |

Met het **Excel-icoon** rechtsonder wordt de lijst uitgeschreven naar Excel.

## 8. B.5.0 - Menu lijsten in optie

Volgens de gebruikershandleiding (2014) bevat dit menu onderstaande modules. **De nummering in dit optiemenu is niet in elke versie/installatie gelijk**: recentere modulehandleidingen plaatsen bv. "Beheer eigendommen - huren" ook onder B.5.0.1 en de afschrijvingen onder "B.5.6". Lees daarom altijd de omschrijving op het scherm van de klant.

| Punt (handleiding 2014) | Module | Meer info |
|---|---|---|
| 5.0.1 | Afprinten/inboeken/uitschrijven domicilieringslijsten (klanten) | `boekhouding-coda-en-betalingen.md` |
| 5.0.2 | Afprinten/inboeken/uitschrijven overschrijvingslijsten (leveranciers) | `boekhouding-coda-en-betalingen.md` |
| 5.0.3 | Automatisch inboeken bankuittreksels voor inkomende betalingen (gestructureerde klantbetalingen) | `boekhouding-coda-en-betalingen.md` |
| 5.0.4 | Berekening nalatigheidsintresten klanten: berekent enkel de intrest over de opgegeven periode (bv. 1 maand), zodat die periodiek doorgefactureerd kan worden | geen aparte handleiding in de bronnen |
| 5.0.5 | Afprinten vervaldagbalans/vervaldaglijst | hoofdstuk 6 |
| 5.0.6 | Beheer maandelijkse Intrastat-aangifte | `boekhouding-btw-listing-ic-intrastat.md` |
| 5.0.7 | Uitschrijven rekeningen naar diskbestand: boekingen op grootboekrekeningen in TXT-formaat voor Excel of een extern programma | |
| 5.0.9 | Afprinten jaarlijks overzicht inkomende/uitgaande facturen (per leverancier en/of klant) | |
| 5.0.A | Afprinten overschrijvingsborderellen bij uitgaande facturen | |

Wordt een punt gekozen waarvan de module niet aangekocht is, dan verschijnt fout 12 ("De gekozen optie werd niet geinstalleerd").

## 9. Controlevolgorde bij een periodeafsluiting (samenvatting)

Samenvatting van de volgorde die de handleiding verspreid over punt 5 en punt A aanbeveelt; stap 4 bundelt de controles die in de bronnen op verschillende plaatsen genoemd worden.

1. Alle stukken van de periode inboeken (facturen, bank, kas, diversen).
2. B.5.1: fouten- en controlelijst afdrukken en fouten oplossen.
3. B.5.1: journalen, centralisatiejournalen, BTW-aangifte, rekeningen en balansen afdrukken (begindatum = dag na vorige archivering).
4. Controleren: saldo financiele journalen = bankuittreksel; klanten-/leveranciersbalans = centralisatierekening op de proef- en saldibalans; lijst openstaande facturen = balans.
5. BTW-aangifte (en eventueel intracommunautaire opgave) indienen via Intervat.
6. Back-up nemen en archiveren (punt A) - zie `boekhouding-archivering-en-foutenlijst.md`.

## Bronnen

- `Gebruikerhandleiding BOEKHOUDPAKKET.docx` (map boekhouding) - versie V06, 12-8-2014: punt 5 (5.1, 5.2, 5.3, 5.8, 5.0, 5.+).
- `0075A - Vervaldagbalans.docx` (map Jamadrink/Handleidingen modules).
- `0067A - Afdrukken maandtotalen KLG.docx` (map Jamadrink/Handleidingen modules).
