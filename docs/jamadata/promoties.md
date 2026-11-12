# Promoties: kassapromoties, factuurpromoties en lijst verkochte artikels in promotie

Gebruik dit document voor: vragen over tijdelijke acties in Jamadrink: kassapromoties (folderprijzen, 5+1, x % korting, mixed promo's, klantenkaartpunten, promo-EAN) via V.2.1, het automatisch inladen van de promofolder van de aankoopvereniging (V.2.1.5.1), factuurpromoties op bons/facturen (V.3.9), waarom een promotie niet werkt of niet stopt op de kassa, en de lijst van verkochte artikels in promotie (V.2.D).

## Welke promotie waarvoor?

| | Kassapromotie | Factuurpromotie |
|---|---|---|
| Menupunt | V.2.1 (Beheer Key-Conen kassa → promoties) | V.3.9 (Beheer prijzen → Factuur-promoties) |
| Werkt op | Enkel de **kassa** (winkelverkoop) | Enkel **bons/facturen** (facturatie), NIET op de kassa |
| Per artikel | Eén artikel, of selectie op groep/leverancier | Per artikel 1 promotiefiche (1 periode), per prijstype (0-5) een eigen promotie |
| Handleiding | 0295A | 0296A |

Een actie die zowel in de winkel als op factuur moet gelden, moet dus **op beide plaatsen** ingegeven worden.

## Deel 1 – Uitgebreide kassapromoties (V.2.1)

### Waarvoor dient het

Tijdelijke acties (folder) die de kassa automatisch toepast zonder tussenkomst van de winkelbediende. Promoties zijn altijd beperkt in tijd (van/tot) en hebben enkel invloed op de kassa. Mogelijk: speciale prijs, gratis producten (bv. 5+1), kortingen, extra klantenkaartpunten.

De promoties worden volledig beheerd in het Jamadrink-pakket (pc in het bureel); op de kassa zelf moeten geen instellingen gewijzigd worden.

Is de **promotietekst op kasticket** ingevuld, dan:
- wordt die tekst onder het artikel op het kasticket gedrukt wanneer de promotie van toepassing is;
- krijgt het blokje (Key-Con) van het artikel op de kassa een **andere kleur**, zodat de bediende ziet dat het in promotie staat.

### Soorten: één artikel of een selectie

- **Eén artikel**: de promotie geldt voor het ingegeven artikel (de meest gebruikte vorm: de artikels van de folder met hun folderpromotie). Gelijkaardige artikels kunnen bijgekoppeld worden voor dezelfde promotie (**mixed promo**, bv. verschillende smaken combineren).
- **Selectie van artikels**: de promotie geldt voor een artikelgroep en/of leverancier. Vooral gebruikt met klantenkaarten, om punten per groep te bepalen (bv. bieren 5 % punten, waters 2 %, zuivel geen punten).
  - Enkel leverancier ingeven = alle artikels van die leverancier.
  - Enkel groepsnummer = alle artikels van die groep.
  - Leverancier + groep = artikels van die groep van die leverancier.
  - **Een individuele promotiefiche van een artikel heeft altijd voorrang** op een selectie-promotie.

### De promotiefiche: velden

| Veld | Uitleg |
|---|---|
| Periode | Geldigheidsperiode van de promotie |
| Artikel / Leverancier / Groep | Waarop de promotie slaat (combinatie leverancier + groep toegelaten) |
| Kassa-prijzen | Bij één artikel: de promotieprijzen. **F7** toont de normale prijzen ernaast ter vergelijking. |
| Promotietekst op kasticket | Tekst op het ticket + andere kleur van het blokje op de kassa |
| Promotie toepassen op Bak of Fles | **B** of **F**. Bij BAK worden losse flesjes of clips meegeteld om tot het aantal te komen (24 flesjes = 1 bak; promo op clip van 4 en klant koopt een bak = 6 clips). Bij FLES worden bakken/clips omgerekend naar losse flessen. |
| Promotie: xxx stuks kopen, dan ... | Het aantal (bak of fles, zie vorig veld) vanaf wanneer de promotie toegepast wordt. **Gratis artikels of artikels met korting tellen mee in dit aantal**: 2+1 gratis → 3; "2e aan 40 %" → 2. |
| Type promotie (één kiezen) | Zie lijst hieronder |
| Max. aantal promo's per ticket | Hoe vaak de promotie op één ticket mag voorkomen |
| Rood koppelsymbool | Meerdere artikels (meestal smaken) opgeven die voor deze promotie gemixt mogen worden |
| Kassa-formule toepassen | **Oud systeem, beter niet meer gebruiken.** Op de kassa konden tot 20 formules (A t.e.m. T) ingesteld worden via "kassaparameters" (bv. 10 % korting, 5+1 gratis); een letter op de promotiefiche past die formule toe. |

Type promotie (na "xxx stuks kopen, dan"):
- **xx % korting op xx stuk(s)**
- **xxx EUR korting op xx stuk(s)**
- **gratis artikel** (artikel opzoeken dat gratis gegeven wordt)
- **gratis (tekst)**: vrije tekst als je geen artikel wil voorzien (bv. gratis bal, gratis pet)
- **xx % korting, vanaf xx stuks xx % korting** (staffel, bv. 6 flessen wijn 5 %, 12 flessen 10 %)
- **voor een totaalprijs van xxx EUR** (bv. 2 zakken chips voor 2 euro)

Via **F9 vervolg**:
- **Promotiepunten** (module klantenkaarten): punten per bak of stuk voor de geselecteerde artikels.
  - Type **P** = vast aantal punten (waarde = aantal punten)
  - Type **%** = punten als percentage van het bedrag (waarde = %)
  - Type **G** = GEEN punten
  - Deze instelling heeft voorrang op de algemene puntenregeling van de kassa.
- **Promotie-EAN**: tijdelijke barcode van een promoverpakking; hier ingeven (en dus niet op de artikelfiche).

### Synchronisatie naar de kassa

- Een promotie wordt pas actief op de kassa nadat de prijzen **uitgeschreven** zijn (V.2.K) en de kassa ze **opgehaald** heeft (punt N, dagelijkse transfer; of K voor een kassa op afstand). Zie `prijzen-doorsturen-naar-kassa.md`.
- Bij het uitschrijven (K) staat bovenaan een **datum**: is er op die datum een promotie, dan wordt ze toegepast in de prijslijst van de kassa (net zoals prijswijzigingen op datum). Door de datum op bv. morgen te zetten, kan je de folder de avond voordien klaarzetten; de kassa's krijgen hem binnen bij de ochtendverbinding.
- Bij het **einde** van de promotie: opnieuw K en N.
- Verstreken promotiefiches moeten niet meteen geschrapt worden; ze worden niet meer toegepast. Opkuisen kan via punt **A (Schrappen verouderde promoties)** in het promotiemenu.

Tegenstrijdigheid tussen bronnen (te verifiëren per installatie/versie):
- Handleiding 0295A zegt dat de **periode niet aan de kassa wordt meegegeven**: zowel vóór de start als bij het einde van een promotie moet opnieuw uitgeschreven en gesynchroniseerd worden.
- De handleiding "Klaarzetten - doorsturen prijzen" zegt dat bij het uitschrijven **automatisch ook de eerstvolgende prijs op datum** wordt meegegeven: een promotie die later start, gaat dan vanzelf in; voor het einde is nog één synchronisatie op of na de startdatum nodig.
- Veilig advies aan de klant: **synchroniseer (K + N) op de dag dat een promotie start en op de dag dat ze stopt**, en controleer een artikel op de kassa.

### Promofolder van de aankoopvereniging automatisch inladen (V.2.1.5.1)

Voorwaarde: de aankoopvereniging bezorgt de folder in XLS aan Jamadata (in overleg), zodat hij op de servers van Jamadata staat.

1. Ga naar V.2.1.5.1 ("Bijvoegen promoties a.h.v. folderbestand").
2. Geef de **leverancier** in = de aankoopvereniging. Die leverancier dient om artikels te koppelen (leveranciersnummer ↔ eigen artikel). Eenmaal gekoppeld herkent het programma het artikel bij een volgende folder.
3. Druk op de **groene knop met wereldbol** om de recentste folder te downloaden. Is de knop **zwart**, dan heb je de recentste folder al. Onderaan staan datum en uur van het folderbestand.
4. Druk **"F8 verwerk promoties van deze leverancier"**. Je krijgt een overzicht van alle promoties:
   - volledig **rood** = artikel nog niet gekoppeld;
   - gedeeltelijk rood (enkel Promotie + Prijs) = gekoppeld maar nog niet verwerkt.
5. Koppelen: klik op het **koppelicoon** achter de lijn, kies het juiste eigen artikel met het **vinkje**. Bij afwijkende inhoud/gewicht verschijnt een tussenscherm; bij afwijkend aantal/verpakking vul je het aantal/verpakking van de leverancier in. Koppeling wissen: opnieuw koppelicoon en de wis-knop. Gekoppelde artikels hebben een zwart vinkje (na klik op het vergrootglas).
6. Klik op het **vergrootglas** achter een gekoppeld artikel om de gewenste promotie te kiezen en vul de promotiefiche in zoals hierboven.

De koppeling is dezelfde als bij de prijzenbestanden (zie `prijzen-prijzenbestanden-importeren.md`).

### Prijskaartjes voor de promotie

Via V.5.9: "enkel artikels in promotie op kassa", of F9 "laad promoties" in het invulscherm, met de juiste prijsdatum. Zie `prijzen-prijsaffiches-en-prijskaartjes.md`.

### Oud systeem: kassa-formules (enkel voor oude installaties)

De gebruikershandleiding JAMADRINK 2.0 ("Promoties op de kassa") beschrijft de vier formuletypes van het oude systeem. Elke formule wordt ingegeven met maximaal vier getallen:

| Formule | Betekenis | Getallen | Voorbeeld |
|---|---|---|---|
| 1 – % korting | Een procentuele korting | Getal 1 = % korting | 5 % korting → `5` |
| 2 – Aantal gratis | Bij een aantal, een aantal gratis | Getal 1 = minimumaantal, Getal 2 = aantal gratis vanaf het minimum | 10 + 2 gratis → `10`, `2` |
| 3 – % korting OF gratis | % korting vanaf een aantal | Getal 1 = minimumaantal, Getal 2 = % korting vanaf het minimum | Vanaf 10, rest aan 5 % → `10`, `5` |
| | Aantal gratis vanaf een aantal | Getal 3 = minimumaantal, Getal 4 = aantal gratis | Vanaf 10, 3 gratis → getal 3 `10`, getal 4 `3` |
| | Beide gecombineerd | Getal 1/2 voor de korting, Getal 3/4 voor gratis | Vanaf 5 rest aan 10 %, vanaf 10 3 gratis → `5`, `10`, `10`, `3` |
| 4 – Aantal met korting | Een aantal stuks met % korting vanaf een aantal | Getal 1 = minimumaantal, Getal 2 = aantal dat korting krijgt, Getal 3 = % korting | 2e aan halve prijs → `1`, `1`, `50` |

Handleiding 0295A raadt aan dit oude systeem niet meer te gebruiken en de promotietypes op de promotiefiche te kiezen.

`0295A - Kassa-promoties_old.docx` beschrijft het vroegere systeem (o.a. kassa-formules A-T) en is niet apart verwerkt.

## Deel 2 – Factuurpromoties (V.3.9)

### Waarvoor dient het

Periodieke promoties die gebruikt worden in facturatie/bons. Ze komen **bovenop** de gewone kortingen van de klant: de promotiekorting wordt **na** de eigen kortingen afgetrokken. Per prijstype (0-5) kan een andere (of geen) promotie gegeven worden.

Waar: hoofdmenu voorraadbeheer, punt 3 (Beheer prijzen), punt 9 (Factuur-promoties).

### 1. Toevoegen/aanpassen van 1 promotie

Geef het artikel in; de promotiefiche verschijnt.

| Veld | Uitleg |
|---|---|
| Promotie-periode | Periode waarin de promotie verrekend wordt. Bij het ingeven/opzoeken van het artikel op een bon/factuur wordt gekeken of de **bon-/factuurdatum** in deze periode valt. |
| Promotie-tekst | Tekst die onder het artikel verschijnt bij het ingeven, of afgedrukt wordt op de bon/factuur (afhankelijk van "Toon"). Formuleer ze zo dat de klant weet welke kortingen gelden. |
| Spec.prijs | Speciale prijs. Wordt genomen **ook al heeft de klant een prijsafspraak met speciale prijs**. |
| Kort.% | Korting in %, afgetrokken NADAT alle normale kortingen van de klant verrekend zijn. |
| Kort.bdr | Korting in EUR, wordt als ALLERLAATSTE afgetrokken. |
| Toon | Bepaalt of bij het ingeven van de bon/factuur automatisch een **extra lijn met de promotietekst** wordt bijgevoegd. Aanbevolen bij gratis producten: zo weet men wat er meegegeven moet worden. Is de lijn niet van toepassing, wis ze tijdens het ingeven met **F4**. |

Opmerking (onzeker / te verifiëren): de handleiding is tegenstrijdig over de exacte stand van "Toon" (ze noemt zowel "Toon = J/N" als "het vinkje uitvinken" en "op AAN zetten"). Test de gewenste stand op een proefbon.

Verdere regels:
- Per prijstype kan een andere promotie ingegeven worden. Niets ingevuld voor een prijstype = geen promotie voor klanten met dat prijstype.
- Enkel voor bons/facturen, niet voor de kassa (daarvoor V.2.1).
- Per artikel kan slechts **1 promotiefiche (periode)** bestaan.

### 2. Aanpassen/bekijken lijst bestaande promoties

De promotieperiode wordt gevraagd; je krijgt de artikels die in die periode in promotie zijn. Met **F8** pas je er een aan.

### 3. Afdrukken lijst bestaande promoties

Periode ingeven; de lijst van artikels in promotie wordt afgedrukt.

### 4. Schrappen verouderde promoties

Periode ingeven; de promoties worden geschrapt. **De promotie moet volledig binnen de ingegeven periode vallen**, anders wordt ze niet geschrapt.

## Deel 3 – Lijst verkochte artikels in promotie (V.2.D)

### Waarvoor dient het

Gedetailleerde winkelverkoop van artikels in promotie, om een promotie te evalueren of cijfers door te geven aan leverancier/producent.

Waar: Hoofdmenu Voorraadbeheer → punt 2 "Beheer Key-Conen kassa" → punt **D** "Lijst verkochte artikels in promotie".

### Stappen

1. Neem V.2.D.
2. Vul de **periode**, eventueel het **artikel** en een selectie op **leverancier/fabrikant** in.
3. Kies of je **enkel verkopen met korting** wil, eventueel met een **minimum % korting**. De korting (en %) wordt berekend als het verschil tussen de werkelijk betaalde kassaprijs en de normale kassaprijs.
4. **Selectie kassa**: leeg laten bij meerdere kassa's, tenzij je de cijfers van één specifieke kassa wil (dan het kassanummer invullen).
5. **F8 maak PDF**: de lijst wordt aangemaakt en geopend. Of **F9 selecteer artikels en maak PDF** om eerst een artikelselectie te maken.

### Weetjes

- De lijst wordt gemaakt op basis van de **werkelijke verkopenbestanden van de kassa**, niet op basis van de in Jamadata ingelezen gegevens. Een oudere periode kan dus niet meer beschikbaar zijn; Jamadata-support kan nakijken of er van die periode nog een verkopenbestand aanwezig is.
- Vul je geen artikel in, dan krijg je alle artikels die in de periode aan een verlaagde prijs (of gratis) verkocht zijn.

## Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Promotie werkt niet op de kassa | Prijzen niet uitgeschreven (V.2.K) of kassa heeft niet gesynchroniseerd (N/K); datum bij het uitschrijven lag vóór de startdatum; periode op de fiche fout. |
| Promotie loopt door na de einddatum | Na het einde niet opnieuw K + N gedaan. |
| 2+1 gratis wordt niet toegepast bij 3 stuks | In "xxx stuks kopen" moet het totaal **inclusief** het gratis stuk staan (3, niet 2). |
| Promo telt flesjes/clips niet mee | Veld "Bak of Fles" verkeerd; of aantal per bak/clip-koppeling fout op de artikelfiches. |
| Verschillende smaken tellen niet samen | Artikels niet gekoppeld via het rode koppelsymbool (mixed promo). |
| Groepspromotie werkt niet op één artikel | Dat artikel heeft een eigen promotiefiche; die heeft voorrang. |
| Blokje op de kassa verandert niet van kleur | "Promotietekst op kasticket" is niet ingevuld. |
| Promoverpakking scant niet | Promotie-EAN niet ingevuld op de promotiefiche (F9 vervolg). |
| Promotie staat op de kassa maar niet op de factuur (of omgekeerd) | Kassapromoties (V.2.1) en factuurpromoties (V.3.9) zijn gescheiden; beide ingeven. |
| Factuurpromotie werkt niet voor een bepaalde klant | Voor het prijstype van die klant is niets ingevuld, of de bon-/factuurdatum valt buiten de periode. |
| Verouderde factuurpromotie wordt niet geschrapt | Ze valt niet volledig binnen de opgegeven periode. |
| Lijst verkochte promo-artikels is leeg voor een oude periode | Verkopenbestanden van de kassa uit die periode zijn niet meer aanwezig. |

## Bronnen

- `0295A - Uitgebreide Kassa-promoties.docx` — Jamadrink/Handleidingen modules
- `0296A - Factuurpromoties.docx` — Jamadrink/Handleidingen modules
- `0290C - Lijst verkochte artikels in promotie.docx` — Jamadrink/Handleidingen modules
- `xxxxx - Klaarzetten - doorsturen prijzen.docx` — Jamadrink/Handleidingen modules
- `0261A - Prijsaffiches.docx` — Jamadrink/Handleidingen modules
- `gebruikershandleiding JAMADRINK 2.0.docx` (extra nota "Promoties op de kassa", p. 77) — Jamadrink
