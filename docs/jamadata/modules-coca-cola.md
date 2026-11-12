# Coca-Cola modules: export verkoopcijfers en promo-orders

Gebruik dit document voor: vragen over het doorgeven van verkochte aantallen aan Coca-Cola vanuit Jamadrink (exportmodule versie 2020, de oudere "Model II"-variant met TG-code) en over het ophalen en verwerken van promo-orders die een Coca-Cola-vertegenwoordiger bij een eindklant heeft genoteerd.

## 1. Overzicht

| Module | Doel | Waar |
|---|---|---|
| Coca-Cola exportmodule (versie 2020) | Maandelijkse verkochte aantallen per klant in Excel uitschrijven en mailen naar Coca-Cola | V.4, onderaan het rode Coca-Cola-icoon |
| Coca-Cola module MODEL II (andere variant, vermoedelijk ouder) | Idem, maar met koppeling van eigen artikels aan een vaste lijst Coca-Cola-producten en selectie via het klantveld "Verplichting soft" | V.4, onderaan het rode Coca-Cola-icoon |
| Promo-orders Coca-Cola | Bestellingen die de Coca-Cola-vertegenwoordiger bij een eindklant opnam, ophalen en omzetten in leveringsbon/factuur, met terugmelding aan Coca-Cola | V.8, in het ingavescherm van leveringsbons/facturen, onderaan het rode Coca-Cola-icoon |

De exportmodules zijn gebaseerd op de uitgebreide statistieken/historieken. De cijfers zijn daardoor per maand beschikbaar, niet per dag.

## 2. Exportmodule Coca-Cola (versie 2020)

### Waar
Menu **V.4**, daarna onderaan op het rode Coca-Cola-icoon. Het scherm heet "Exporteren verkochte aantallen voor Coca-Cola".

### Eenmalige instellingen (parameters)
Bij het eerste gebruik moet op het parameterscherm van de module ingevuld worden:
- het **klantnummer** van de drankenhandel bij Coca-Cola;
- welke **leverancier of producent** op de artikelfiches gebruikt wordt voor de Coca-Cola-producten. De module neemt alle artikels van die leverancier/producent.

### Stap 1 - Klanten selecteren (eenmalig, daarna bijhouden)
1. Druk op **F9 instellen verplichte klanten**. Er verschijnt een selectiescherm voor klanten.
2. Druk op **F8 zoek**; de lijst met geselecteerde klanten wordt getoond.
3. Per klant:
   - links op het groene icoon drukken = omzet doorgeven (lijn wordt **wit**);
   - op het Coca-Cola-icoon drukken = omzet doorgeven als **verplichte klant** (lijn wordt **groen**);
   - rechts op het verbodsicoon drukken = omzet **niet** doorgeven (lijn wordt **rood**).
4. Klaar: **F1 stop**.
5. Controle: op het menu van de module geeft **F3 controlelijst klanten** een PDF-lijst van de geselecteerde klanten.

### Stap 2 - Artikels controleren
**F2 controlelijst artikels** drukt de lijst af van alle artikels van de ingestelde leverancier/producent. Controleer of alle Coca-Cola-producten erop staan. Ontbreekt een artikel, dan staat op de artikelfiche niet de juiste leverancier/producent ingevuld.

### Stap 3 - Uitschrijven in Excel
1. Vul de periode in maanden in ("Welke periode wenst U ... t.e.m.", bv. 1 - 12) en pas indien nodig het jaar aan.
2. Druk op het Excel-icoon. De spreadsheet wordt aangemaakt en getoond. Controleer de cijfers.

### Stap 4 - Mailen
Druk op het grote mail-icoon. Er wordt een mail aangemaakt met de Excel als bijlage; verstuur die mail.

### Optie "Export Full Universe data"
- Enkel aanvinken als de drankenhandel bij Coca-Cola aangesloten is voor "Full Universe Data".
- Met het vinkje worden ook de klanten uitgeschreven die in de periode geen Coca-Cola-producten kochten, maar wel producten uit dezelfde artikelgroepen.
- In de Excel komt dan een tweede tabblad met naam, adres en btw-nummer van die klanten.

### Verschil met "versie 2017 - Old layout"
De handleiding van 2017 beschrijft dezelfde werkwijze en dezelfde toetsen (F9, F8, F3, F2, Excel-icoon, mail-icoon, Full Universe). Enkel de schermlayout verschilt. Voor support maakt het inhoudelijk geen verschil.

## 3. Coca-Cola module MODEL II

De handleiding is niet gedateerd. De werkwijze (letter op de klantfiche, mailen vanuit Excel) wijst op een oudere of alternatieve variant; of een klant deze variant of versie 2020 heeft, moet op het scherm van de klant nagekeken worden (te verifiëren). Kenmerkend: artikels worden één voor één gekoppeld aan een vaste lijst van een 60-tal horecaproducten van Coca-Cola, en de klantselectie gebeurt met een letter op de klantfiche.

### Waar
Menu **V.4**, onderaan het rode Coca-Cola-icoon.

### Stap 1 - Artikels koppelen aan de Coca-Cola-productlijst
1. Druk op **F10 controle artikels**. De eigen artikels van leverancier/merk Coca-Cola worden één voor één getoond, met daaronder de lijst van mogelijke Coca-Cola-producten.
2. Duid in de lijst het juiste Coca-Cola-product aan en druk op **F8 neem aan**.
3. Staat het artikel niet in de lijst, dan hoort het niet bij de selectie horecaproducten waarvan omzet doorgegeven moet worden. Het mag dan niet gekoppeld worden: druk op **F10 wis referentie**.
4. Is er al een correcte referentie ingevuld op de artikelfiche, dan staat het artikel in het groen in de lijst. Druk gewoon **F8 neem aan** om naar het volgende te gaan.
5. Druk daarna ter controle op **F9 artikellijst**: de lijst toont de 60 toegelaten Coca-Cola-producten met daarachter de eigen artikels die eraan gekoppeld zijn. Corrigeer waar nodig.

### Stap 2 - Klantenfiches aanpassen (V.9.2)
Onderaan de klantfiche staat het veld **Verplichting soft**. Vul voor alle klanten waarvoor statistieken nodig zijn dezelfde letter in (bv. `J`). Bij het uitschrijven kan op die letter geselecteerd worden.

### Stap 3 - Uitschrijven in Excel
Vul het selectiescherm in en druk **F8 neem aan**:

| Veld | Betekenis |
|---|---|
| Welke periode wenst U ... t.e.m. | Gewenste periode |
| Selectie Verplichting soft | De letter van de klantfiches (bv. `J`). Blanco = alle klanten |
| Leverancier Coca-Cola | De leverancier zoals gebruikt op de artikelfiches. Wordt onthouden |
| Leverancier of fabrikant (L/F) | Op welk veld van de artikelfiche gekeken wordt |
| TG-code Coca-Cola | De 4-cijferige TG-code van de drankenhandel bij Coca-Cola. Onbekend? Opvragen bij de vertegenwoordiger van Coca-Cola. Wordt onthouden |
| Gegevens vorig jaar nemen (J/N) | Wordt enkel gevraagd als er maandstatistieken zijn. `J` = aantallen van vorig jaar |

De spreadsheet wordt aangemaakt en getoond: een kolom per Coca-Cola-product, een lijn per klant.

### Stap 4 - Controleren en mailen
In deze variant gebeurt het mailen vanuit Excel zelf:
1. **Bestand > Opslaan als**, kies een map (bv. Mijn Documenten), **Opslaan**.
2. **Bestand > Opslaan en verzenden** (of **Exporteren**) > **Per e-mail verzenden** > **Als bijlage**.
3. Vul de mail aan en verzend naar Coca-Cola.

## 4. Promo-orders van Coca-Cola verwerken

### Doel
Een vertegenwoordiger van Coca-Cola noteert bij een eindklant van de drankenhandel een (promo)bestelling in het ERP-pakket van Coca-Cola. Jamadrink haalt die bestelling op, maakt er een leveringsbon of factuur van en meldt aan Coca-Cola terug dat het order geleverd of gefactureerd is.

### Waar
Menu **V.8**, bij het ingeven van leveringsbons of facturen: op het scherm waar de klant ingegeven wordt, onderaan op het rode Coca-Cola-icoon drukken.

### Stappen
1. **Nieuwste promo's ophalen**: klik in het orderscherm op het download-icoon. De lijst met orders verschijnt. Achter elk order staat een vergrootglas (bekijken) en een download (XML). De XML downloaden is enkel nuttig bij onduidelijkheden.
2. **Order bekijken**: klik op het vergrootglas. Lijnen in het **rood** zijn nog niet gekoppeld aan een klant of artikel in Jamadrink.
3. **Koppelen (eenmalig per klant en per artikel)**: klik op het groene link-icoon achter de klant of het artikel.
   - Klant: geef een deel van de naam in, zoek met het vergrootglas, kies de klant en druk **F8 neem aan**. Een nieuwe klant aanmaken kan met **F10 nieuwe klant**.
   - Artikel: kies het juiste artikel met het groene vinkje ervoor.
   - Een gekoppelde lijn staat niet meer in het rood en blijft gekoppeld voor alle volgende orders.
   - Met het PDF-symbool rechtsonder kan het order afgedrukt worden.
4. **Leveringsbon/factuur maken**: druk **F8 verwerk deze gegevens**. De klant wordt automatisch ingevuld op het beginscherm van de leveringsbon/factuur. Werk het document af met **F8 verdergaan / F8 neem aan**. Lijnen toevoegen of wijzigen is nog mogelijk.
5. **Bevestigen aan Coca-Cola**: na het eindscherm (afdrukken/mailen) verschijnt een bevestigingsscherm. Na een leveringsbon gaat het om "geleverd (ingegeven)", na een factuur (of factuur uit leveringsbon) om "gefactureerd (afgewerkt)". Vul eventueel de juiste datum in en bevestig met **F4 Ja**. Coca-Cola krijgt de bevestiging in zijn ERP-pakket.

### Extra mogelijkheden
- **Status manueel doorgeven**: ga op een order staan en klik rechtsonder op het groene plusteken. Keuzes: "Order ontvangen", "Order geleverd/gefactureerd", of het order schrappen.
- **Overzicht ingegeven/afgewerkte orders**: klik in het overzichtsscherm rechtsonder op het groene overzichtsicoon. Eerst verschijnt het scherm "Ingegeven", daarna "Afgewerkte" orders.

## 5. Gekende problemen en controlepunten

De controlepunten hieronder zijn afgeleid uit de werking die de handleidingen beschrijven; de handleidingen bevatten zelf geen aparte probleemlijst, tenzij uitdrukkelijk vermeld.

| Probleem | Oorzaak / oplossing |
|---|---|
| Artikel ontbreekt in de export of op de controlelijst (F2) | Op de artikelfiche staat niet de leverancier/producent die in de parameters van de module is ingesteld. Controleer ook of in de parameters "leverancier" dan wel "producent" correct gekozen is |
| Klant ontbreekt in de export | Klant staat op rood (niet doorgeven) in F9, of (Model II) de letter in "Verplichting soft" ontbreekt of wijkt af van de selectie |
| Model II: artikel staat niet in de Coca-Cola-lijst | Het hoort niet bij de 60 horecaproducten; niet koppelen, F10 wis referentie |
| Model II: TG-code onbekend | Opvragen bij de vertegenwoordiger van Coca-Cola |
| Promo-orders: na het download-icoon verschijnt een ander scherm (melding) in plaats van de orderlijst | Vermeld in de handleiding: de parameters zijn niet juist ingevuld. Een Jamadata-medewerker moet de juiste parameters invullen (gegevens: zie interne bron) |
| Promo-orders: lijnen blijven rood | Klant of artikel is nog niet gekoppeld; koppel via het groene link-icoon |
| Excel bevat een tweede tabblad met klanten zonder Coca-Cola-omzet | De optie "Export Full Universe data" staat aangevinkt |

## Bronnen
- `2392A - Coca-Cola module (versie 2020).docx` (Jamadrink/Handleidingen modules)
- `2392A - Coca-Cola module (versie 2017) - Old layout.docx` (Jamadrink/Handleidingen modules) - enkel vergeleken
- `2390A - Coca-Cola module MODEL II.docx` (Jamadrink/Handleidingen modules)
- `2394A - Verwerken van de promo orders van Coca-Cola.docx` (Jamadrink/Handleidingen modules)
