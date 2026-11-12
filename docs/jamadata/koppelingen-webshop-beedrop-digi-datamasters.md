# Webshop- en externe koppelingen: Beedrop, WeSolveIt, XML-webshopkoppeling, DIGI ESL, DataMasters, Intrastat-installatie

Gebruik dit document voor: vragen over de export van artikels naar een Beedrop-webshop, het beheer van klanttoegang tot de B2B-webshop/app van WeSolveIt, de technische XML-webshopkoppeling (mappen IN/UIT, velden), de koppeling met elektronische rayonkaartjes van DIGI ESL (ArticleData.dat), en de installatiestappen van de DataMasters-module en de Intrastat-module. De Intrastat-aangifte zelf (gebruik) staat in de boekhouddocumentatie.

## 1. Overzicht

| Koppeling | Doel | Waar | Uitwisseling |
|---|---|---|---|
| Beedrop | Artikels en prijzen aanleveren voor de webshop bij Beedrop | V.8, een van de laatste punten van het menu | Excel, door de gebruiker gemaild naar Beedrop |
| WeSolveIt | Klanten toegang geven tot de B2B-webshop (app) en leveranciers afschermen | Klantfiche, winkelmand-knop | Toegangsnummer per klant |
| Webshop-koppeling (XML) | Artikels naar een externe webshop, bestellingen terug als leveringsbon | Scherm 1: "Beheer webshop ... : W" | XML in `\\JamaShare\WebShop\UIT` en `\\JamaShare\WebShop\IN` |
| DIGI ESL | Prijzen naar digitale rayonkaartjes | V.2.9.K (uitschrijven prijzen voor de kassa) | `ArticleData.dat` + `ArticleData.FLG` in `JamaData\Share` |
| DataMasters | Exportmodule | V.4, icoon rechtsonder | Niet beschreven in de bron |
| Intrastat (installatie) | Module activeren | B.5.6 / B.5.0.6, parameters | - |

## 2. Koppeling Beedrop

### Doel
Artikelgegevens exporteren voor de webshop van de drankenhandel bij Beedrop.

### Waar
Menu **V.8**, een van de laatste punten op dat menu.

### Instelling op de artikelfiche
Op de artikelfiche, bij **F9 vervolg**, staat onderaan het veld **Webshop Beedrop**. Met een vinkje wordt het artikel uitgeschreven. Dit veld kan altijd rechtstreeks op de fiche aan- of afgevinkt worden.

### Eerste gebruik: artikels in bulk aanduiden
Een hulpprogramma stelt de best verkopende artikels op de kassa van het afgelopen jaar voor (standaard 250).
1. Druk op het Beedrop-scherm rechtsonder op het **groene tandwieltje**.
2. Druk **F10 instellen Beedrop op artikelfiches**.
3. Pas eventueel de periode en het maximaal aantal artikels aan.
4. **F8 ga verder**: bijkomende selectie, bv. om groepen uit te sluiten (rookwaren, diversen, verhuur ...).
5. Het scherm met voorgestelde artikels verschijnt:
   - **F4** wist een artikel dat niet gewenst is;
   - lijnen in het **groen** waren al aangevinkt; niet meer gewenst: druk op het rode kruisje ernaast;
   - **F5** voegt artikels toe die niet in de lijst staan.
6. **F8 neem aan**: alle overblijvende artikels worden geactiveerd voor de webshop.

### Artikels uitschrijven voor Beedrop
1. Neem op het Beedrop-menu **punt 1**. De lijst van te exporteren artikels verschijnt.
2. Ongewenste artikels: rode kruisje. De prijs kan hier aangepast worden, maar dat geldt **enkel voor deze export** en wordt niet opgeslagen.
3. Druk **F8 maak XLS**. De Excel wordt getoond; de gebruiker mailt die zelf naar Beedrop.

## 3. Beheer webshop WeSolveIt (B2B-webshop / app)

### Doel
Beheer van de B2B-webshop (app) van partner WeSolveIt: bepalen welke klanten mogen bestellen en welke leveranciers ze niet mogen zien. Geplaatste bestellingen kunnen omgezet worden naar een leveringsbon of factuur (dat deel is in de handleiding niet uitgewerkt).

### Klant toegang geven
1. Open de **klantfiche** van de klant.
2. Druk op de **rode winkelmand-knop**. De klant krijgt toegang om met zijn klantnummer te bestellen.
3. Bovenaan het scherm staat het **toegangsnummer** van de klant voor de webshop; dit is uniek per klant.

### Leveranciers blokkeren voor de klant
Op hetzelfde scherm staat een lijst waarin leveranciers toegevoegd kunnen worden. Producten van die leveranciers ziet de klant niet in de webshop.

### Controle
Terug naar de fiche met **F8 klantenfiche**. De winkelmand is nu **groen** = klant heeft toegang.

## 4. Webshop-koppeling via XML (technische installatienota)

De bron is een installatie- en analysenota voor technici. Ze beschrijft de opzet van de koppeling; niet alle onderdelen zijn bevestigd als opgeleverd. Behandel details als "volgens ontwerp".

### Installatie
- `struct.cnf`: bij ARTIKEL de velden **195** (webshop) en **199** (datum laatste aanpassing) toevoegen.
- **OVL2295** incompileren.
- Scherm 1 aanpassen: de regel "Beheer webshop ... : W" toevoegen.

### Mappen
- Standaard: `\\JamaShare\WebShop\UIT` (artikels naar de webshop) en `\\JamaShare\WebShop\IN` (bestellingen van de webshop). `\\JamaShare` is de gedeelde map op de Jamadata-server.
- De locatie is parametreerbaar.
- Een extern programma zorgt voor de periodieke uitwisseling met een FTP-server; dat is geen onderdeel van Jamadrink.

### Artikels klaarzetten (export)
- Velden op de artikelfiche: **Webshop-artikel** (aan/uit via een knop op de fiche) en **Datum laatste aanpassing** (wordt bijgewerkt bij leveringen, prijzenbeheer, bons/facturatie, aanpassen fiches ...).
- De prijzentabel is uitgebreid van 6 naar 10 verkoopprijzen, zodat voor de webshop een andere prijs dan de kassaprijs mogelijk is (bak/fles).
- De export schrijft de geselecteerde artikels in **XML** in de UIT-map. Ze loopt automatisch mee wanneer de artikels voor de kassa uitgeschreven worden (punt 2.K) en kan ook afzonderlijk gestart worden.
- Enkel webshop-artikels die gewijzigd zijn sinds de vorige export worden uitgeschreven. Bij handmatig starten kan de periode "laatste aanpassing" gewijzigd worden om een volledige export te maken. Op dat scherm staat ook een knop voor de parameters (o.a. prijstypes, plaats bestanden).

XML-velden per artikel:

| Veld | Inhoud |
|---|---|
| ArticleID | Codenummer |
| Description | Omschrijving |
| ExtraInfo | Extra omschrijving |
| Price | Eenheidsprijs van 1 eenheid (bak), incl. btw |
| PricePc | Eenheidsprijs van 1 fles/stuk, incl. btw |
| Empties | Leeggoed van 1 eenheid (bak) |
| EmptiesPc | Leeggoed van 1 fles |
| VatPct | Btw-percentage |
| PcInCrate | Aantal flessen in 1 bak (stuk/karton) |
| GroupNr / GroupName | Nummer en omschrijving artikelgroep |
| Volume / Weight | Inhoud en gewicht |
| Stock | Actuele stock, met aftrek van de niet-gefactureerde leveringsbons |
| NormalStock | Normale stock |
| Ean / EanPc | Barcode bak en barcode fles/stuk |

### Bestellingen inlezen
- Voor elke online bestelling maakt de webshop een XML-bestand dat in de **IN**-map terechtkomt.
- De module toont bij opstarten (of vernieuwen) de lijst van hangende bestellingen op basis van de XML-bestanden in IN. Op dat scherm staat ook een knop om de artikelexport direct te starten.
- Een bestelling aanduiden start het programma leveringsbons met klant en artikels al ingevuld. Corrigeren blijft mogelijk.
- Klantbeheer: bestaat de klant al, dan worden gewijzigde gegevens bijgewerkt. Bestaat hij niet, dan kan hij aangemaakt worden (verplicht als er een btw-nummer is doorgegeven) of komt de bestelling op een globale klant "webshopklanten" (gangbaar voor particulieren, om het klantenbestand niet te vervuilen).
- Na het maken van de leveringsbon wordt het XML-bestand uit de IN-map verwijderd.

Minimale inhoud van de bestel-XML: datum, totaalbedrag, totaal portokosten, betaald bedrag, betaalwijze, opmerking van de klant, klantgegevens ((code), naam, adres, telefoon, e-mailadres, btw-nummer), afleveradres, en per artikel: aantal, PcOfCrate (= fles/stuk), artikelcode, omschrijving, eenheidsprijs, totaal goederen, totaal leeggoed.

Onzeker in de bron: of de portokosten inclusief 21% btw doorgegeven worden.

## 5. DIGI ESL-koppeling (digitale rayonkaartjes)

### Werking
- Bij het uitschrijven van de prijzen voor de kassa (punt **V.2.9.K**) komt een extra item dat het bestand **ArticleData.dat** uitschrijft in de map `JamaData\Share`. Bij een kassa op afstand zoekt DIGI in de map `\Kassa`.
- Na het uitschrijven wordt **ArticleData.FLG** aangemaakt.
- Het DIGI-systeem kijkt elke minuut of `ArticleData.FLG` bestaat. Zo ja, dan werkt het de prijzen op de kaartjes bij en verwijdert het het FLG-bestand.

### Installatie
1. Laatste programmaversies incompileren.
2. `Upsys32 sys.* i 2974 1` uitvoeren.
3. Bij **kassa op afstand**: `ZIP_KAS.BAT` aanpassen zodat ArticleData meegestuurd wordt:
   `%jama-dir%\zip -j DEP2KAS.zip ..\..\Share\ArticleData.*`
4. JamaShare instellen (zie de handleiding over de Jamadata Share).

### Bestandsoverdracht
- DIGI haalt het bestand op uit de gedeelde map **JamaShare** op de Jamadata-server (gebruiker en wachtwoord van de share: zie interne bron).
- Bestandsnaam: `Articledata.dat`; controlebestand: `Articledata.flg`.

### Bestandsformaat ArticleData.dat
- Velden gescheiden door een **pipe** (`|`). Het pipe-teken mag dus niet voorkomen in de gegevens en wordt uitgefilterd.
- Decimalen: 2 cijfers na een decimale **punt**, maximaal 5 cijfers ervoor (bv. `999.99`).
- EAN-lijsten: codes of PLU-nummers gescheiden door `;`, maximaal 5 per lijst.

| Nr | Veld | Opmerking |
|---|---|---|
| 1 | Artikelcode | Unieke code |
| 2 | Omschrijving | |
| 3 | EAN-codes bakken | Lijst EAN-13, gescheiden door `;` |
| 4 | EAN-codes flessen | Lijst EAN-13, gescheiden door `;` |
| 5 | Extra omschrijving | Vrije tekst, bv. jaartal |
| 6 | Promotekst | |
| 7 | Prijs | |
| 8 | Prijs per stuk | |
| 9 | Speciale prijs | Leeg of 0.00 indien niet van toepassing |
| 10 | Speciale prijs per stuk | Leeg of 0.00 indien niet van toepassing |
| 11 | Inhoud | In liter |
| 12 | Gewicht | In kg |
| 13 | Leeggoed per bak | |
| 14 | Leeggoed per stuk | |

Voorbeeldlijn:
`abc132456|OMSCHRIJVING|1234567890123;1234567890124;1324|2234567890123;2234567890123;|EXTRA OMSCHRIJVING|PROMO TEKST|999.99|9.99|0.00|0.00|0.35|0.00|4.35|0.30`

### Gekende problemen DIGI
De eerste twee rijen staan als nota in de bron.

| Probleem | Oorzaak / oplossing |
|---|---|
| Kaartjes worden niet bijgewerkt na doorsturen via UCWIN naar de kassa's | UCWIN zet de bestandsnamen in hoofdletters (`ARTICLEDATA`); DIGI leest die niet. De bestanden moeten gekopieerd of hernoemd worden naar `ArticleData` (bv. via een regel in `kasmenu.dat` op de kassa) |
| DIGI krijgt geen toegang tot de map | Het DIGI-systeem moet aanloggen met de gebruiker administrator of guest; met de gebruiker "kassa" lukt het niet (nota van 01/12/2021) |
| Bij kassa op afstand komt er geen ArticleData aan | Nakijken of `ZIP_KAS.BAT` aangepast is (installatiestap 3) |

## 6. DataMasters module (installatie)

De bron is een korte installatienota; het gebruik van de module is er niet in beschreven.

- Plaats in het programma: **V.4**, icoon rechtsonder (punt "V.4 DM").
- Installatiestappen:
  1. Laatste programmaversies incompileren.
  2. **DRK 2503** incompileren.
  3. `struct.cnf`: op het bestand Klant (veld 2,131), op update, toevoegen: `DM_HorecaTyp: upd, str, l=1;` (commentaar: DataMasters, type horeca).
  4. Punt V.4 DM uittesten.
  5. De begeleidende brief voor de klant meegeven (interne map, zie interne bron).
- Gevolg voor de klantfiche: er komt een veld van 1 teken voor het **type horeca** (DM_HorecaTyp). Welke waarden toegelaten zijn staat niet in de bron (te verifiëren).

## 7. Intrastat installeren (enkel installatie)

### Basisinstallatie
`struct.cnf` aanpassen:
- Leverancier: velden 1,35-38 toevoegen
- Klant: velden 2,74-77 toevoegen
- GRB: veld 3,14
- STK: velden 48-58 toevoegen + key 20
- BKA: velden 48-58 toevoegen
- ART: veld 6,86 (goederencode); als er geen gewicht/inhoud is (37 + 38), ook velden 87 en 88 toevoegen
- BON: veld 58,30 toevoegen

Verder:
- Schermen 6 en 7 aanpassen voor de nieuwe velden.
- **Ovl0076** incompileren.
- **PAR0240**: INTRASTAT op **YES** zetten.

Bij de installatie bij de klant:
1. Ga naar **B.5.6** en dan parameters (rechtsonder).
2. Stel de defaults in (BE, 3, 1).
3. Neem de **verborgen F10**: de defaults worden ingevuld op klanten en leveranciers. Is er een buitenlands btw-nummer ingevuld, dan wordt de landcode daaruit genomen.
4. De klant moet zelf nog de **goederencode** invullen op de artikelfiches.

### Aanpassing vanaf 1/1/2021: transactiecode
De transactiecode wijzigde van **1 naar 11** en van **2 naar 22**.
- Structuur: het veld Transactie op lengte 2 zetten (`l=2`) op de velden 1,38 / 2,77 / 4,53 / 86,53.
- Laatste versies installeren.
- Bij de klant: ga naar **B.5.0.6**, tandwiel (parameters), wijzig de transactie van 1 naar 11 en druk op de **verborgen F10**. De parameters worden weggeschreven en de nieuwe code wordt ingevuld op klant/leverancier/STK/BKA.

Opmerking: de bron vermeldt het menupunt eenmaal als B.5.6 en eenmaal als B.5.0.6; vermoedelijk hetzelfde scherm (te verifiëren).

## 8. Controlepunten webshops

De controlepunten hieronder zijn afgeleid uit de werking die de handleidingen beschrijven; de handleidingen bevatten zelf geen aparte probleemlijst, tenzij uitdrukkelijk vermeld.

| Probleem | Oorzaak / oplossing |
|---|---|
| Artikel ontbreekt in de Beedrop-export | Veld "Webshop Beedrop" (artikelfiche, F9 vervolg) staat niet aangevinkt |
| In de Beedrop-export aangepaste prijs is de volgende keer weg | Normaal: de aanpassing geldt enkel voor die ene export; pas de prijs aan op de artikelfiche |
| Klant kan niet bestellen in de WeSolveIt-webshop | Nakijken of de winkelmand op de klantfiche groen is; zo niet, activeren. Het toegangsnummer staat bovenaan het webshopscherm van de klant |
| Klant ziet bepaalde producten niet in de WeSolveIt-webshop | De leverancier staat in de lijst geblokkeerde leveranciers van die klant |
| XML-webshop: artikel komt niet door | Artikel is geen webshop-artikel, of is niet gewijzigd sinds de vorige export; start de export handmatig met een ruimere periode "laatste aanpassing" |

## Bronnen
- `0160A - Koppeling BEEDROP.docx` (Jamadrink/Handleidingen modules)
- `2296A - Beheer webshop WeSolveIt.docx` (Jamadrink/Handleidingen modules)
- `HOWTO-Webshop-koppeling.docx` (Jamadrink)
- `HOWTO-DIGI-koppeling.docx` (Jamadrink)
- `HOWTO-Installeren DataMasters module.docx` (Jamadrink)
- `HOWTO-installeren INTRASTAT.docx` (Jamadrink)
