# Prik&Tik en Districo: bestellingen naar de bestelsite, export kassaverkopen, Freedelity, verzendnota's

Gebruik dit document voor: vragen van drankenhandels die lid zijn van Prik&Tik of Districo over (1) het uitschrijven van een leveranciersbestelling naar de bestelsite van Prik&Tik of Districo, met of zonder uitgebreid aankoopbeheer, (2) het koppelen van eigen artikels aan de artikelcodes van Prik&Tik/Districo, (3) de maandelijkse export van kassaverkopen naar Prik&Tik, (4) de Freedelity-klantenkaartkoppeling op de kassa en (5) het automatisch verwerken van verzendnota's van Prik&Tik.

## 1. Overzicht

| Onderwerp | Waar in Jamadrink | Resultaat |
|---|---|---|
| Standaardleverancier Prik&Tik instellen | V.2.P | Leverancier voor alle P&T-koppelingen |
| Standaardleverancier Districo instellen | V.3.D | Leverancier voor alle Districo-koppelingen |
| Bestelling uitschrijven voor bestelsite | Voorraadbeheer punt 1 (V.1), bestelling ingeven, daarna P&T-knop of bestelknop | Bestand "Bestelling..." in `(Mijn) Documenten\Jamadata\Diversen` (P&T: XML; Districo: CSV) |
| P&T-artikelcodes invullen op artikelfiches | V.2.P ("Invullen artikelcodes van leverancier op artikelfiches") | Code bij leverancier op de aankoopfiche |
| Export kassaverkopen Prik&Tik | V.4, icoon onderaan | Excel ter controle; verzending via enveloppe-icoon |
| Freedelity | Kassa, knop "Loyalty card Freedelity" na betaling | Verkoop wordt naar Freedelity gestuurd |

## 2. De artikelkoppeling: "Code bij leverancier" op de aankoopfiche

Alle Prik&Tik- en Districo-koppelingen (bestellingen, prijslijsten, promoties, Freedelity) steunen op dezelfde koppeling: op de **aankoopfiche** van het artikel voor de leverancier Prik&Tik of Districo staat het artikelnummer van die leverancier in het veld **Code bij leverancier**.

Velden op de aankoopfiche (bereikbaar via **F4 detail** op een bestellijn):
- **Code bij leverancier**: het codenummer van Prik&Tik/Districo. Eenmalig in te vullen.
- **Aantal/verpakking**: enkel invullen als de verpakking bij de leverancier afwijkt van het eigen artikel.

Voorbeeld aantal/verpakking: op de artikelfiche van een fles wijn staat bij zowel bak- als stuksprijs enkel de flesprijs, maar de wijn wordt per karton van 6 aangekocht. Vul dan `6` in. Op het ingavescherm van de bestelling is het aantal daarna steeds in de eenheid van de leverancier (2 = 2 kartons van 6 flessen). Bij de levering wordt automatisch omgerekend van karton naar fles (stock en prijs).

Bestelgegevens op de artikelfiche (V.9.3.1):
- **Aantal per pallet**: indien ingevuld kan op de PDA ook per pallet besteld worden.
- **Normale stock**: artikels met een negatief aantal (bv. `-1`) komen niet op de bestellijst. Zo kunnen eenmalige producten overgeslagen worden.

## 3. Bestelling uitschrijven voor de bestelsite van Prik&Tik of Districo

Er bestaan twee varianten van het aankoopscherm. Welke de klant heeft, hangt af van de module "uitgebreid aankoopbeheer". De stappen zijn gelijk; enkel de menubenamingen en enkele toetsen verschillen.

### 3.1 Eenmalige instelling: standaardleverancier
- **Prik&Tik**: punt **V.2.P**. Vul de leverancier "Prik en Tik" in en neem **F1 stop**.
- **Districo**: punt **V.3.D**. Vul de leverancier "Districo" in en neem **F8 neem aan**.

### 3.2 Bestelling opnemen
Drie manieren:
- met de **PDA** (optie; zie de PDA-documentatie);
- op een blanco blad: winkel/magazijn aflopen en product en aantal noteren;
- met de **Bestellijst leverancier**, punt **V.5.2.4**: met de lijst rondgaan en aantallen noteren.

### 3.3 Bestelling ingeven of inlezen

Start op het hoofdmenu voorraadbeheer punt 1 "Inbrengen bestellingen/leveringen aan leveranciers" (**V.1**).

**Zonder uitgebreid aankoopbeheer** (handleidingen 0211A/0211B) - punt "Inbrengen bestellingen":

| Punt | Werking |
|---|---|
| 1 Manuele methode | Geef de leverancier in en daarna de artikels. Met PDA: **F11 lees PDA-gegevens**, daarna F8 |
| 2 Via lijst leveranciers van PDA-opnames (optie) | Periode en eventueel PDA-nummer ingeven; in de lijst op de lijn van de leverancier gaan staan en **F8 neem aan** |

**Met uitgebreid aankoopbeheer** (handleidingen 0255A/0255B) - punt "Inbrengen nieuwe bons":

| Punt | Werking |
|---|---|
| 1 Toevoegen van een nieuwe bon | Leverancier ingeven, **F8 verdergaan**, daarna artikels ingeven. Met PDA: **F11 lees PDA-gegevens**, daarna F8 |
| 2 Nieuwe bon a.h.v. artikelen onder minimum stock | Leverancier ingeven, **F8 zoek op**; op het vervolgscherm eventueel instellingen wijzigen, **F8 verdergaan**. De artikels onder minimumstock komen op het scherm; toevoegen en verwijderen kan |
| 3 Nieuwe bon a.h.v. lijst leveranciers van PDA (optie) | Periode en PDA-nummer; op de lijn van de leverancier **F8 neem aan**; vervolgscherm, **F8 verdergaan** |

Vragen bij het inlezen van PDA-gegevens (beide varianten):
- periode waarin de bestelling is opgenomen;
- PDA-nummer, bij meerdere PDA's of PDA op afstand;
- **Opgenomen aantallen converteren naar verpakkingen leverancier: JA/NEE** (zie aantal/verpakking in paragraaf 2);
- **F8** = enkel de artikels van deze leverancier; **F9** = alle artikels.

Na het inlezen kunnen nog artikels toegevoegd worden.

### 3.4 Niet-gekoppelde artikels koppelen
Bij artikels zonder leverancierscode staat het codenummer in het **rood**. Ga op die lijn staan, druk **F4 detail**, vul **Code bij leverancier** (en eventueel **aantal/verpakking**) in en keer terug met **F8 neem aan**.

Bevestig de volledige bestelling met **F8 afdrukken/boeken**.

### 3.5 Bestand uitschrijven
- Prik&Tik: klik op de **Prik&Tik-knop**.
- Districo: klik op de **bestelknop** (met uitgebreid aankoopbeheer staat die op het **eindscherm**).

Windows Verkenner opent automatisch in de exportmap. Het bestand heet "Bestelling..." en staat in `(Mijn) Documenten\Jamadata\Diversen`.

### 3.6 Uploaden op de bestelsite
1. Meld aan op de bestelsite van de leverancier (Prik&Tik: `webshop.prikentik.com/bestellen`).
2. Blader naar `(Mijn) Documenten\Jamadata\Diversen`, kies het **recentste** bestand en klik "openen". Prik&Tik verwacht het XML-bestand; Districo (handleiding 0255B) een CSV-bestand via een upload-knop.
3. Klik "uploaden".
4. Prik&Tik: de site meldt dat de instellingen zijn opgeslagen en toont de producten die momenteel niet besteld kunnen worden of niet goed gekoppeld zijn. Via "Mijn bestelling" (rechtsboven) staat het overzicht.
5. Manueel artikels toevoegen, aantallen wijzigen of verwijderen kan nog. Klaar: "bestelling doorsturen".

### 3.7 Tip: alle artikels van de leverancier in één keer koppelen
1. Ga naar bestellingen via **V.1.2.1**. Met uitgebreid aankoopbeheer: geef eerst de leverancier in en neem **F8 verdergaan**.
2. Druk onderaan op het groene icoon **A+** (met uitgebreid aankoopbeheer: het grote groene icoon "+", daarna de knop om artikels te laden).
3. Kies "selecteer op leverancier" (of druk `1`) en selecteer **enkel** de leverancier Prik&Tik of Districo.
4. Druk 2x **F8 ga verder**. Alle artikels van die leverancier staan alfabetisch op het scherm.
5. Koppel elk artikel met **F4 detail**. Klaar: gewoon stoppen tot op het hoofdmenu (de bestelling wordt niet geboekt).

Extra bij uitgebreid aankoopbeheer:
- Een controlelijst van gekoppelde, niet-gekoppelde of alle artikels: punt **V.2.P**, functietoets **F10 druk controlelijst**. (De Districo-handleiding 0255B verwijst hier eveneens naar V.2.P; onzeker of dit voor Districo V.3.D moet zijn.)
- Een artikel opzoeken op het artikelnummer van de leverancier: typ in het omschrijvingsveld het nummer met een **+**-teken ervoor.

## 4. P&T-artikelcodes in bulk invullen (programma bij Freedelity, punt 2.P)

### Doel
Elk Prik&Tik-lid heeft eigen codenummers en omschrijvingen. Om op groepsniveau acties te plannen en te evalueren moet het P&T-codenummer met elk kasticket meegestuurd worden. Dit programma vult de P&T-codes in zonder elke artikelfiche manueel op te roepen. De code komt op de aankoopfiche van het artikel voor leverancier Prik&Tik.

### Scherm "Invullen artikelcodes van leverancier op artikelfiches" (punt 2.P)

| Element | Werking |
|---|---|
| Knop "Controleren op nieuwe lijst" | Downloadt de meest recente artikellijst van Prik&Tik. Is de knop zwart, dan is de lijst al de recentste |
| Datum artikelbestand | Datum en uur van de P&T-artikellijst op de pc |
| Beginnen vanaf | Lijnnummer van het eerste P&T-artikel. Handig om verder te gaan waar vorige keer gestopt is |
| Gekoppelde artikels overslaan | Aangevinkt = reeds gekoppelde P&T-artikels worden niet getoond |
| Leverancier | De eigen leverancier "Prik&Tik" |
| F8 begin invullen | Start het koppelen |
| F10 druk controlelijst | Controlelijst in PDF |

### Koppelen
- De P&T-artikels worden één voor één getoond. Het programma zoekt meteen op het **eerste woord** van de P&T-omschrijving en toont de eigen artikels die voldoen en nog **niet** gekoppeld zijn.
- Staat het artikel er niet bij: druk opnieuw op het vergrootglas om ook reeds gekoppelde artikels te tonen, of wijzig de zoektekst en zoek opnieuw.
- Geeft Prik&Tik een barcode (EAN) mee, dan wordt eerst op barcode gezocht en het artikel direct getoond.
- Selecteer het juiste artikel, of druk **F6** als het artikel niet gevolgd wordt.

Toetsen: **F2 vorig / F3 volgend** scherm met gevonden artikels; **F6** sla dit artikel over; **F7 zoek** op naam; groene pijlen bovenaan = vorig/volgend P&T-artikel. Rechtsboven staat het lijnnummer in het P&T-bestand (bv. 80/8751); noteer dit om later bij "Beginnen vanaf" verder te gaan. Bij het stoppen wordt een PDF gemaakt met de overlopen artikels.

## 5. Freedelity op de kassa

### Doel
Koppeling van de Jamadata-software (artikelbeheer en kassa) met het klantenkaartensysteem van Freedelity, gebruikt door Prik&Tik.

### Werkwijze
1. Na het afsluiten van de verkoop en de betaling verschijnt een scherm met de grote knop **Loyalty card Freedelity**.
2. Druk op de knop; het programma van Freedelity start.
3. Kies de klant:
   - **Lees een identiteitskaart**;
   - **Zoek op naam**;
   - **Handmatige inschrijving**: nieuwe klant zonder identiteitskaart (bv. buitenlander);
   - **Annuleren**: deze verkoop niet registreren voor Freedelity.
4. Bij een nieuwe klant worden e-mailadres en telefoonnummer gevraagd.
5. De verkoop wordt naar Freedelity gestuurd en de kassa keert terug naar het verkoopscherm.

Opmerking: is het goederentotaal 0 of negatief, dan verschijnt een grote terug-knop in plaats van de Freedelity-knop; de Freedelity-knop staat dan klein onderaan.

## 6. Export kassaverkopen naar Prik&Tik

### Doel
Maandelijks de kassaverkopen doorsturen naar Prik&Tik. Dit gebeurt in het begin van de maand voor de afgelopen maand, **nadat de kassaverkopen van die maand zijn ingelezen (V.2.3)**.

### Waar
**V.4**, onderaan het Prik&Tik-icoon.

### Stappen
1. **Controle**: geef maand en jaar in en druk op het **XLS-icoon**. De Excel wordt aangemaakt en getoond; kijk na of alles erin staat.
2. **Doorsturen**: geef maand en jaar in en druk op het **enveloppe-icoon**. De verkoopsgegevens worden aangemaakt en doorgestuurd naar Prik&Tik.

## 7. Automatisch verwerken van verzendnota's Prik&Tik

### Wat de bron zegt
Bedoeling van de module: de gemailde verzendnota (leveringsbon) van Prik&Tik bewaren in een vaste map; bij het opstarten toont het programma de bewaarde verzendnota's; na keuze van een verzendnota worden alle artikels getoond om de levering te vergelijken met de bestelling, de stock te verwerken en eventueel de factuur in te boeken. Ook hier moeten de artikels gekoppeld zijn met die van Prik&Tik (paragraaf 2).

### Onzeker / te verifiëren
De handleiding `XXXXB - Automatisch verwerken verzendnota's Prik&Tik.docx` is een **onafgewerkt ontwerp**: de mapnaam staat als `xxxxxxxx`, er is geen menupunt vermeld en de uitgewerkte stappen zijn gekopieerd uit de handleiding "Aanpassen artikelprijzen a.d.h.v. prijzenbestand" (2291B, punt V.2.P.2, map `j:\jamadata\share\prijslijsten`). Gebruik dit dus niet als procedure. Vraagt een klant naar deze module, verwijs dan door naar een Jamadata-medewerker.

## 8. Gekende problemen en controlepunten

De controlepunten hieronder zijn afgeleid uit de werking die de handleidingen beschrijven; de handleidingen bevatten zelf geen aparte probleemlijst, tenzij uitdrukkelijk vermeld.

| Probleem | Oorzaak / oplossing |
|---|---|
| Codenummer staat rood op de bestellijn | Artikel is niet gekoppeld; F4 detail, "Code bij leverancier" invullen |
| Bestelsite meldt producten als niet bestelbaar of niet goed gekoppeld | Foute of verouderde code bij leverancier op de aankoopfiche, of het product is tijdelijk niet leverbaar. Corrigeer de code via F4 detail |
| Aantallen op de bestelsite kloppen niet (factor 6, 12, 24 ...) | "Aantal/verpakking" op de aankoopfiche ontbreekt of is fout, of bij het inlezen van de PDA is "converteren naar verpakkingen leverancier" verkeerd beantwoord |
| Bestand niet te vinden bij het uploaden | Staat in `(Mijn) Documenten\Jamadata\Diversen`, naam begint met "Bestelling"; kies het recentste |
| Koppeling nog nooit gebruikt | Eerst de standaardleverancier instellen (P&T: V.2.P; Districo: V.3.D) |
| Artikel komt nooit op de bestellijst | "Normale stock" op de artikelfiche is negatief (bv. -1) |
| Per pallet bestellen kan niet op de PDA | "Aantal per pallet" op de artikelfiche is niet ingevuld |
| Export kassaverkopen is leeg of onvolledig | Kassaverkopen van die maand zijn nog niet ingelezen (V.2.3) |
| Knop "Controleren op nieuwe lijst" is zwart | Geen fout: de recentste P&T-artikellijst staat al op de pc |
| Freedelity-knop niet zichtbaar na de verkoop | Goederentotaal is 0 of negatief; de knop staat dan klein onderaan |

## Bronnen
- `0211A - Uitschrijven bestellingen voor de P&T website.docx` (Jamadrink/Handleidingen modules)
- `0211B - Uitschrijven bestellingen voor de Districo website.docx` (Jamadrink/Handleidingen modules)
- `0255A - Uitschrijven bestellingen voor de P&T website met uitgebreid aankoopbeheer.docx` (Jamadrink/Handleidingen modules)
- `0255B - Uitschrijven bestellingen voor de Districo website met uitgebreid aankoopbeheer.docx` (Jamadrink/Handleidingen modules)
- `2291A - PrikTik Freedelity.docx` (Jamadrink/Handleidingen modules)
- `2397A - Prik & Tik export kassaverkopen.docx` (Jamadrink/Handleidingen modules)
- `XXXXB - Automatisch verwerken verzendnota's Prik&Tik.docx` (Jamadrink/Handleidingen modules) - onafgewerkt ontwerp, enkel de inleiding gebruikt
