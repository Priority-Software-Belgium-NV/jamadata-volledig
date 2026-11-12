# Bestellingen in- en uitvoeren via Excel (klantbestellingen en leveranciersbestellingen)

Gebruik dit document voor: vragen over (1) het uitschrijven van een Excel-bestelformulier voor een klant en het inlezen van de ingevulde bestelling in een leveringsbon of factuur, en (2) het uitschrijven van een Excel-opnamelijst voor een bestelling aan een leverancier, het invullen ervan op tablet of pc en het inlezen als leveranciersbestelling. Voor het uitschrijven van bestellingen naar de bestelsites van Prik&Tik en Districo zie `modules-prik-en-tik-districo.md`; voor webshopbestellingen zie `koppelingen-webshop-beedrop-digi-datamasters.md`.

## 1. Overzicht

| | Bestellingen van klanten (0215A) | Bestelling aan leverancier (2283A) |
|---|---|---|
| Excel aanmaken | Hoofdmenu punt 5 "Afdrukken artikellijsten" > punt 5 "Afdrukken bestelformulier klant" | Hoofdmenu punt 1 "Inbrengen bestellingen aan leveranciers" > punt B "Uitschrijven excel voor opname bestelling" |
| Map | `j:\jamadata\share\bestellingen\` | `j:\jamadata\share\AKbestellingen\` (of OneDrive/Dropbox-map op de server) |
| Parameter voor de map | Parameters onder punt **+4** | Parameters onder punt **+4** vanaf het hoofdmenu |
| Inlezen | V.8 Facturatie, leveringsbon of factuur, icoon rechtsonder na ingave klant | V.1.2.1, icoon rechtsonder na ingave leverancier |

Aandachtspunten voor beide:
- De driveletter `j:` geldt op de hoofdcomputer en kan afwijken. Op een andere pc is het zeker een andere letter (bv. `P:\share\...` of `P:\jamadata\share\...`).
- Het pad in de parameters moet eindigen op een **backslash** (`\`). Ontbreekt die, dan worden de bestanden niet gevonden.
- Het plusteken van punt **+4** is een verborgen menupunt (niet zichtbaar op het menu).

## 2. Bestellingen van klanten importeren

### Doel
Alternatief voor een eigen webshop: de drankenhandel bezorgt de klant een Excel-bestelformulier, de klant vult aantallen in en stuurt het terug, en de bestelling wordt semi-automatisch ingelezen in een leveringsbon of factuur.

### Stap 1 - Bestelformulier uitschrijven
1. Hoofdmenu punt **5 Afdrukken artikellijsten**, daarna punt **5 Afdrukken bestelformulier klant**.
2. Kies de opmaak, de extra vermeldingen en de klant voor wie de lijst bedoeld is.
3. Druk op het **Excel-icoon**.
4. Kies welke artikels op de lijst komen:

| Selectie | Werking |
|---|---|
| 1 Leverancier | Lijst van alle leveranciers, standaard allemaal aangevinkt. **F5** vinkt alles af; duid daarna de gewenste aan |
| 2 Artikelgroep | Idem voor artikelgroepen (F5 = alles afvinken) |
| 3 Merk/fabrikant | Artikels van één merk/fabrikant |
| 4 Artikelfiche | Selectie op elk veld van de artikelfiche met gelijk / groter dan / kleiner dan. Tekstvelden afsluiten met `*` (bv. `coca*`) |
| 5 Datum laatste prijswijziging | Periode waarin de prijs gewijzigd is (datum "Vanaf" op de artikelfiche of datum prijswijziging op datum) |
| 6 Bestelbon klant | Artikels die via **F9 bestelbon** op de klantfiche zijn ingegeven |
| 7 Klantenstatistiek | Artikels die de klant ooit afnam (vereist statistieken/historieken) |
| 8 Prijsafspraak | Artikels met een individuele prijsafspraak voor de klant |

   Selecties 6, 7 en 8 werken enkel als er een klant gekozen is. Staat er "Geen klant" achter, druk dan **F4** (klant <-> selectie), zoek de klant op en druk opnieuw **F4** om verder te selecteren.
5. Bevestig met **F8 ga verder**. De Excel verschijnt op het scherm. Bezorg hem aan de klant, bijvoorbeeld per e-mail.

### Stap 2 - Ontvangen bestellingen opslaan
Sla elke ingevulde Excel op in de bestellingenmap: `j:\jamadata\share\bestellingen\` (of het overeenkomstige pad op een andere pc). Deze locatie moet eenmalig ingevuld zijn in de parameters onder punt **+4**, met afsluitende `\`.

### Stap 3 - Verwerken in leveringsbon of factuur
1. Ga naar **V.8 Facturatie** en kies leveringsbon of factuur.
2. Geef de klant in.
3. Klik op het icoon **rechtsonder** om de bestellingen te tonen. Per bestand zijn er drie iconen:
   - verwerken van de bestelling;
   - Excel downloaden en openen (om te bekijken);
   - rode vuilbak: de bestelling verwijderen uit de Jamadata-map.
4. Klik op de gewenste bestelling. De bestelde artikels verschijnen op het scherm.
5. Druk **F8 verwerk deze bestelling**. Je komt op de vervolgschermen van de standaard facturatie of bons.

### Lijnen zonder artikelnummer
Artikels die de klant los (vrije tekst) heeft bijgeschreven, verschijnen zonder artikelnummer. Bij verdergaan volgt een foutmelding. Oplossing:
- het juiste artikel opzoeken, of
- als het een opmerking is: een `*` voor de omschrijving zetten; de lijn wordt dan gewone commentaar op de bon/factuur.

### Bestelling laden vanuit het artikelscherm
Staat men al op het scherm waar de artikels van de bon/factuur ingegeven worden, dan kan een bestelling nog geladen worden via het icoon rechtsonder op het artikelscherm en daarna de keuze bij "laad artikels van".

## 3. Bestelling aan leverancier via Excel

### Doel
In plaats van bestellingen manueel te noteren, een Excel uit het pakket schrijven, die op een tablet of laptop openen en in het magazijn de aantallen invullen, en daarna de Excel inlezen als bestelling aan de leverancier.

### Stap 1 - Parameters (eenmalig, best samen met een Jamadata-medewerker)

**Optie a - gedeelde map**
- Eenvoudigste locatie: `j:\jamadata\share\AKbestellingen\`, omdat `share` al gedeeld is op de Jamadata-server. (In de bron staat de mapnaam zowel als "AK bestellingen" als "AKbestelling"; gebruik de naam zoals die op de server bestaat.)
- Verkorte, driveletter-onafhankelijke notatie: `..\share\AKbestelling\`. Die blijft werken als het pakket van computer of driveletter verandert.

**Optie b - OneDrive, Dropbox of gelijkaardig**
- Doel: bestanden synchroniseren tussen de server en het toestel waarop geteld wordt.
- Geef het pad van de gesynchroniseerde map in. Let op: het gaat om de locatie **op de Jamadata-server**. Een gedeelde netwerkmap is hier mogelijk maar te vermijden.

In beide gevallen: vul de locatie in bij de parameters onder punt **+4** vanaf het hoofdmenu (plusteken is verborgen), met afsluitende `\`. Het pad kan in het veld geplakt worden met de rechtermuisknop.

### Stap 2 - Opnamelijst uitschrijven
1. Hoofdmenu punt **1 Inbrengen bestellingen aan leveranciers**, daarna punt **B Uitschrijven excel voor opname bestelling**.
2. Kies een leverancier (bij één leverancier best hier al invullen), wat er met de bons moet gebeuren, de opmaak en de extra vermeldingen.
3. Druk **F8 selecteer artikels en maak XLS**.
4. Kies de artikels met dezelfde selecties als bij het klantformulier: leverancier (1), artikelgroep (2), merk/fabrikant (3), artikelfiche (4), datum laatste prijswijziging (5).
5. Bevestig met **F8 ga verder**. De Excel wordt automatisch opgeslagen in de ingestelde map. Hij wordt **niet geopend** op dit toestel. Met het PDF-symbool kan wel een PDF gemaakt en geopend worden.

### Stap 3 - Bestelling opnemen in de Excel
- Open de Excel vanuit de gedeelde map of de gesynchroniseerde map op tablet/pc.
- Enkel de kolommen **Aantal**, **P/S** en **Opmerking** zijn aanpasbaar; de rest is beveiligd.
- **Aantal** = aantal bakken, tenzij in de kolom **P/S** een `P` (paletten) of `S` (stuks) staat. Hoofd- of kleine letter maakt niet uit.
- **Opmerking** wordt niet verwerkt; dient voor eigen notities (bv. getelde locaties).
- Staat het veld **Stock** in het rood, dan zit de stock onder de minimumstock.
- Bewaar de Excel en **sluit hem af** voor het verwerken.

### Stap 4 - Verwerken in Jamadata
1. Ga naar **V.1.2.1** en geef de leverancier in.
2. Klik op het icoon rechtsonder om de bestellingen te tonen. Per Excel-bestand:
   - icoon verwerken;
   - icoon Excel downloaden en openen;
   - rode vuilbak: bestand definitief verwijderen van de computer (niet terug te halen).
3. Klik op de gewenste bestelling; de genoteerde artikels verschijnen.
4. Kies:
   - **F8 alle artikels toevoegen**, of
   - **F10 enkel artikels van deze leveranciers toevoegen**.
5. Je komt op de vervolgschermen van de standaard bestellingen/leveringen aan leverancier.
6. Na het verwerken vraagt het programma of het Excel-bestand gewist mag worden.

Ook hier kan een bestelling geladen worden vanuit het artikelscherm via het icoon rechtsonder en "laad artikels van".

## 4. Gekende problemen en controlepunten

De controlepunten hieronder zijn afgeleid uit de werking die de handleidingen beschrijven; de handleidingen bevatten zelf geen aparte probleemlijst, tenzij uitdrukkelijk vermeld.

| Probleem | Oorzaak / oplossing |
|---|---|
| Er verschijnen geen bestellingen na het icoon rechtsonder | Pad in parameters +4 fout of zonder afsluitende `\`; bestand staat in een andere map of onder een andere driveletter |
| Foutmelding bij verdergaan na inlezen klantbestelling | Lijn zonder artikelnummer (vrije tekst van de klant): artikel opzoeken of `*` voor de omschrijving zetten |
| Selectie 6, 7 of 8 geeft niets | Er staat "Geen klant": kies een klant met F4 |
| Selectie op omschrijving vindt niets | Tekst niet afgesloten met `*` |
| Excel van leveranciersbestelling opent niet na het uitschrijven | Normaal: het bestand wordt enkel opgeslagen, niet geopend. Gebruik het PDF-symbool of open het op de tablet |
| Aantallen worden verkeerd verwerkt | Kolom P/S: leeg = bakken, P = paletten, S = stuks |
| Ingevulde aantallen ontbreken bij het inlezen | De handleiding vraagt de Excel te bewaren en af te sluiten voor het verwerken |
| Bestand per ongeluk gewist met de rode vuilbak | Bij leveranciersbestellingen is dit definitief |
| Werkt niet meer na verhuis naar andere pc/driveletter | Gebruik de relatieve notatie `..\share\...\` in parameters +4 |

## Bronnen
- `0215A - Importeren bestellingen van klanten.docx` (Jamadrink/Handleidingen modules)
- `2283A - Bestelling leverancier via Excel.docx` (Jamadrink/Handleidingen modules)
