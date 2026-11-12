# PDA: gebruik, modules, bestellingen en barcodes

Gebruik dit document voor: vragen over wat de PDA (JamaMobi) binnen Jamadata doet, het verschil tussen de oude PDA (met houder/cradle en JamaSpda) en de nieuwe PDA (synchronisatie via wifi), het opnemen en verwerken van leveranciersbestellingen met de PDA, het koppelen van barcodes aan artikels met de PDA, en het bekijken/inlezen van stockopnames. Installatie, licentie en storingen staan in `pda-installatie-licentie-en-synchronisatie.md`. De volledige inventarisprocedure met PDA (handleiding 0220C) staat in `stock-en-inventaris.md`.

## 1. Wat is de PDA

- Een PDA is een toestel met ingebouwde scanner waarop het programma **JamaMobi** geïnstalleerd is. De handleidingen noemen als merken Symbol, M3 en Honeywell; in de interne notities komen ook Zebra MC55, MC9000-reeks, Dolphin, HERA en RANGER2 voor.
- Er bestaan twee generaties:

| | Oude PDA | Nieuwe PDA (JamaMobi-app, Android) |
|---|---|---|
| Communicatie | Via houder (cradle) aan een computer, met het beheerprogramma **JamaSpda**; eventueel via wifi | Via **wifi** rechtstreeks met de hoofdcomputer/server |
| Knoppen | **ZEND: Doorsturen gegevens** (rode balk in JamaSpda) | **Sync** op de PDA |
| Voorwaarde | PDA uit de programma's, in de houder, JamaSpda actief op de pc met de houder | PDA verbonden met wifi, serveradres correct in JamaMobi-instellingen |

- In beide gevallen moet de PDA voldoende opgeladen zijn.

## 2. Modules op de PDA

| Module | Doel | Werking in het kort |
|---|---|---|
| **Bestellingen (Orders)** | Leveranciersbestellingen mobiel opnemen in het magazijn | Artikelgegevens naar de PDA sturen, in het magazijn scannen / opzoeken / per leverancier werken, aantallen ingeven, terugsturen en op de computer verwerken tot bestelbon |
| **Stock (Inventaris)** | (Eindejaars)inventaris of tussentijdse voorraadcontrole | Artikelgegevens klaarzetten, producten scannen, getelde aantallen ingeven per bak of per fles, daarna inlezen in Jamadata om de theoretische stock te overschrijven/aan te passen. Aanbevolen: regelmatig tussentijds synchroniseren om gegevens veilig te stellen |
| **Barcodes** | Barcodes (EAN) controleren of aan het juiste artikel koppelen | Barcode scannen; onbekend = artikellijst verschijnt, juiste artikel kiezen, aanduiden of het een bak- of fles/stuk-barcode is; na synchronisatie worden de barcodes ingevuld op de artikelfiches |
| **Leeggoed (mobiele retour op leveringsbon)** | Leeggoedterugname bij de klant registreren en verrekenen | Chauffeur scant de barcode op de papieren leveringsbon, scant of selecteert het teruggenomen leeggoed; de PDA berekent het nieuwe totaal (volgoed min leeggoed). Op kantoor worden de wijzigingen semi-automatisch verwerkt op de originele bons |
| **Camion** | Toegang tot de chauffeursfuncties | Knop op het hoofdscherm, o.a. naar de leeggoedretour |

Synchronisatie-principe:
- Oude PDA: **ZEND** = gegevens (prijzen, nieuwe artikels) van computer naar PDA; **ONTVANG/TOEVOEGEN** = opnames van de PDA naar de computer.
- Nieuwe PDA: beide richtingen heten **SYNC** en lopen over wifi.

## 3. Bestelling opnemen met de PDA (handleiding 0297A, oude PDA met JamaSpda)

### Stap 1 – Artikelgegevens klaarzetten en naar de PDA sturen
1. In Jamadata: menu "Inbrengen leveringen/bestelling" (**V.1**), punt **K**, daarna **F8**.
   - Kies de volgorde: alfabetisch of magazijnplaats.
   - Kies eventueel de gewenste leverancier(s).
2. Op de PDA: verlaat de programma's en steek de PDA in de houder.
3. Op de computer met de houder: start **JamaSpda** (rode icoon "JamaSpda" op het bureaublad).
4. Klik op de rode balk **ZEND : Doorsturen gegevens**.

Bestelgegevens op de artikelfiche (**V.9.3.1**) die de PDA-lijst beïnvloeden:
- **Aantal per pallet**: indien ingevuld kan je op de PDA ook per pallet bestellen.
- **Normale stock**: artikels met een **negatief** aantal (bv. -1) komen **niet** op de bestellijst (handig voor eenmalige producten).

### Stap 2 – Opnemen op de PDA
1. Eerst de vorige bestelling wissen: knop **Wissen**, daarna knop **Bestelling**.
2. Druk op **Bestelling** en daarna op **Zoek**.
3. Kies de methode:
   - **Scannen**: scan het artikel (of het rayonkaartje).
   - **Artikel**: naam of code ingeven (of scannen), daarna de aantallen.
   - **Blokjes kassa**: artikel opzoeken via de kassablokjes (of scannen), daarna de aantallen.
   - **Leverancier**: leverancier kiezen; je krijgt zijn producten in alfabetische volgorde of volgens magazijnplaats; product aanduiden of scannen en aantallen ingeven.
4. **OK** slaat de opname op; het toestel staat klaar voor het volgende artikel. Reeds ingegeven artikels krijgen een andere kleur in de lijst.
5. Na de opname: PDA uit de programma's, in de houder, JamaSpda starten, **ZEND : Doorsturen gegevens**.

### Stap 3 – Verwerken op de hoofdcomputer
Menu "Inbrengen leveringen/bestellingen" (**V.1**), punt "Inbrengen bestellingen".

- **Manuele methode (punt 1)**
  1. Geef de leverancier in.
  2. Druk **F11** "lees PDA-gegevens" en daarna **F8**.
  3. Geef de periode in waarin de bestelling is opgenomen.
  4. Bij meerdere PDA's (of op afstand): geef het PDA-nummer in.
  5. **F8** = enkel de artikels van deze leverancier; **F9** = alle artikels.
  6. De artikels komen op het scherm; werk de bestelling af en druk af.
- **Via lijst leveranciers (punt 2)**
  1. Periode ingeven, eventueel PDA-nummer.
  2. Je krijgt de lijst van leveranciers waarvoor artikels zijn opgenomen; duid een leverancier aan en de bestelling komt op het scherm. Herhaal voor de andere leveranciers.

## 4. Barcodes opnemen/controleren met de PDA

### 4.1 Oude PDA met JamaSpda (handleiding 0297B)
1. **Klaarzetten**: menu "Mobiele stockopname" (**V.A.M** of **V.2**), punt **K**, **F8**.
2. PDA in de houder, **JamaSpda** starten, **ZEND : Doorsturen gegevens**.
3. Op de PDA eerst de vorige opnames wissen: **Wissen** → **Barcode**.
4. Druk op **Barcode** en scan de barcode van het product.
   - Barcode al gekend: het artikel wordt getoond; druk **Neem aan** en scan het volgende.
   - Barcode niet gekend: de artikellijst verschijnt; kies het product, de barcode wordt getoond; indien juist: **Neem aan**.
   - Alternatief: eerst het artikel zoeken met **Zoek**, dan op het gewenste barcodeveld (**bak** of **stuk**) drukken en dan scannen.
5. Na afloop: PDA in de houder, JamaSpda, **ZEND : Doorsturen gegevens**.
6. **Verwerken**: menu "Mobiele stockopname" (**V.A.M**), punt **2** "Verwerken barcodes", **F4**. De barcodes worden ingevuld op de artikelfiches.

### 4.2 Nieuwe PDA (JamaMobi via wifi)
1. Maak indien nodig eerst de nieuwe artikels aan in Jamadata.
2. Op de PDA: **Sync** van alle producten.
3. Knop **Barcodes**: scan de barcode en kies het product waar ze bij hoort.
4. Kies of het een barcode voor **bak** of **fles** is.
5. Bevestig met het **vinkje**.
6. Als alle barcodes zijn toegevoegd: terug naar het beginscherm → **Sync** → sync van de **barcodes**.
7. In Jamadata: **V, A, M, 2**. Nu staan de barcodes ook in Jamadata.
8. Barcodes ook op de kassa nodig? Vanuit het hoofdmenu voorraadbeheer: punt **2**, dan **K** "Klaarzetten gegevens kassa"; op de kassa punt **N** "Dagelijkse transfer met hoofdcomputer".

Fouten tijdens de sync op de nieuwe PDA: zie `pda-installatie-licentie-en-synchronisatie.md` (serveradres in JamaMobi-instellingen en wifi-verbinding nakijken).

## 5. Gegevens klaarzetten voor de mobiele app (oude PDA)

Interne notitie "Klaarzetten geg mobiel app": via punt **A – M – K**; daarna op de oude PDA de gegevens inlezen via JamaMobi → **Zenden en ontvangen gegevens**.

Onzeker / te verifiëren: de notitie vermeldt enkel dit pad zonder verdere context (welke gegevens precies worden klaargezet).

## 6. Stockopnames met de PDA bekijken / inlezen

Om de stockopnames van de PDA te controleren, vanuit het hoofdmenu:
1. **A** – Periodewerkzaamheden
2. **2** – Opmaken van eindejaarsinventaris
3. **3** – Verwerken/inlezen van de aantallen, geteld met de PDA (optie)
4. **F9** om de opnames te bekijken.

Stockwijzigingen effectief inlezen (oudere notitie): zelfde pad **A → 2 → 3**, datum ingeven voor de selectie van de opnameperiode, dan **F4** (begin inlezen).

De volledige inventarisprocedure staat in `stock-en-inventaris.md`.

## Bronnen
- `Jamadrink/Handleidingen modules/0297A - PDA_bestelling.docx`
- `Jamadrink/Handleidingen modules/0297A - PDA_bestelling_barcode.docx`
- `Jamadrink/Handleidingen modules/0297B - PDA_barcodes.docx`
- `Onenote/PDA.pdf` (pagina's "Werking modules oude PDA", "Werking modules nieuwe PDA", "Klaarzetten geg mobiel app", "Barcodes toevoegen met de nieuwe PDA", "Bekijken stock opnamen met PDA")
- `Onenote/Scanners.pdf` en `kassa/scanners/Scanners.pdf` (pagina "PDA": inlezen stockwijzigingen)
- `PDA/Barcodes toevoegen met de nieuwe PDA.docx` = `Jamadrink/HOWTO - Barcodes toevoegen met de nieuwe PDA.docx`
- `PDA/Bekijken stock opnamen met PDA.pdf` = `Jamadrink/HOWTO - Bekijken stock opnamen met PDA.docx`
- `Markdown kennisbank/Jamadata_Kennisbank_PDA.md` (ruwe extractie, ter controle)
