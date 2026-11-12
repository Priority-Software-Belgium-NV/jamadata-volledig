# Jamadrink: leveringsbons en verkoopfacturen

Gebruik dit document voor: vragen over het aanmaken, aanpassen en schrappen van leveringsbons, het factureren uit bons (klant per klant of in serie), rechtstreekse facturen, de extra functies op het bon-/factuurscherm (historiek, artikels laden van laatste factuur/offerte/verhuurbon, leeggoed op 0, afhalingen), de vaste teksten 1–4 op bons en facturen, het herafdrukken of schrappen van facturen, mobiele leeggoedterugname op leveringsbons (verwerking in Jamadrink) en de lijsten van facturen en openstaande facturen. Peppol/mailinstellingen, prijzen en kassafacturatie in detail staan in andere documenten.

## 1. Menu Facturatie (V.8)

| Code | Menu-item |
|---|---|
| 1 | Beheer leveringsbons (1 aanpassen, 2 inbrengen, 3 schrappen) |
| 2 | Afdrukken facturen uit leveringsbons (1 klant per klant, S per serie) |
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
| U | (verborgen) Schrappen van een factuur |

`F10 afhalingen/memo` in dit menu: memo van een klantenfiche aanpassen.

## 2. Leveringsbon aanmaken (V.8.1.2)

1. **Hoofding**: klant is verplicht. Het bonnummer wordt opvolgend gegenereerd; wil je een ander nummer, pas het getal aan en kies `F9 neem deze nummer`. Hier staat ook het vinkje of van de bon **een factuur gemaakt mag worden** ("mag gefactureerd worden"). `F8 verdergaan`.
2. **Tussenschermen** (verschijnen enkel als de voorwaarde geldt):

| Voorwaarde | Scherm |
|---|---|
| Er is een melding (F12 info met alarm) en de datum is verstreken | De melding wordt getoond |
| De klant heeft een memo (`F10 memo` op klantenfiche) | De memo wordt getoond en kan aangepast worden |
| De klant huurt artikels | Lijst van verhuurde items; kan toegevoegd worden aan de bon |

3. **Facturatieadres**: kan hier aangepast worden (staat er bij de klant een ander facturatieadres, dan verschijnt dat).
4. **Artikellijnen**: heeft de klant een standaardbestelling (`F9 bestelbon` op klantenfiche), dan staan die artikels er al.

| Toets | Functie op het artikelscherm |
|---|---|
| `F4 wis` | Lijn wissen |
| `F5 voeg in` | Lege lijn invoegen boven de cursor |
| `F9 leeggoed` | Voegt de leeggoedlijnen toe die bij de artikels horen, met dezelfde aantallen **in het negatief** (bv. 7 flessen verkocht → -7 leeggoed terug) |
| `F11 historiek` | Na ingave van artikelnummer of -omschrijving: bewegingen van dit artikel over de laatste 2 jaar; via het icoon wordt de eenheidsprijs omgezet naar een totaalprijs |
| `F8 neem aan` | Naar het eindscherm |
| `+`-icoon rechtsonder | Extra opties (zie §5) |

5. **Eindscherm**: totaalprijs, vrije eindtekst (bv. bedrag in woorden), referentie; afdrukken met `F8`, of pdf / mail via de knoppen rechtsonder.

### Bon aanpassen (V.8.1.1) en schrappen (V.8.1.3)

- Zoekscherm: klant selecteren; optioneel datum van/tot en filter op "mag gefactureerd worden" (`J`a / `N`een / `A`lles). Kies de bon uit de lijst.
- Aanpassen verloopt verder zoals aanmaken.
- Schrappen: `F4 schrap`, `F5 behoud`, `F1 stop`, `F11 hoofdmenu`. Schrappen kan enkel via een back-up teruggedraaid worden.

## 3. Facturen uit leveringsbons (V.8.2)

### Klant per klant (V.8.2.1)

1. Klant selecteren (zelfde filters als bij bons).
2. Het systeem vult de datum van vandaag en het opvolgend factuurnummer in.
3. Scherm facturatieadres, en waar de omzet bijgehouden moet worden.
4. Afsluiting: referentienummer en vrije opmerking die op de factuur komt. Een **groene markering** boven de vrije opmerking betekent dat de factuur automatisch gemaild wordt.
5. `F8 neem aan` drukt af; knoppen rechtsonder: pdf maken, of factuur manueel mailen.

### Per serie (V.8.2.S)

1. Bevestig de vraag (`F4 Ja` / `F5 Nee`).
2. **Begindatum van de serie bonnen**: leeg laten = alle openstaande bonnen.
3. **Facturatietijdstip**: lettercode (dagelijkse, wekelijkse, maandelijkse, halfjaarlijkse factuur), dezelfde als het veld "Tijdstip facturatie" op de klantenfiche. Leeg = alle klanten; ingevuld = enkel klanten met die code.
4. De verwerking is zwaar en kan enkele minuten duren; het systeem lijkt ondertussen soms niet te reageren. Niet afbreken.

Veelvoorkomende vraag: "Een bon komt niet mee in de facturatie" → nakijken of op de bon "mag gefactureerd worden" aanstaat, of de bondatum binnen de gekozen serie valt en of het facturatietijdstip van de klant overeenkomt met de gekozen lettercode.

## 4. Factuur rechtstreeks ingeven (V.8.3)

Zelfde schermen als een leveringsbon: klant verplicht, factuurnummer opvolgend (`F9 neem deze nummer` om af te wijken), melding/memo-schermen, facturatieadres, artikellijnen (`F4 wis`, `F5 voeg in`, `F9 leeggoed`), eindscherm met eindtekst, `F8 neem aan`.

Foutmeldingen die hierbij kunnen opduiken: code 59 (er is reeds een factuur of creditnota geboekt onder dit nummer), code 41 (een factuur is geen creditnota en omgekeerd), code 82 (grootboekrekening voor leeggoed ontbreekt bij de parameters); zie `jamadrink-foutcodes.md`.

### Facturen uit de kassa (kort)

- `V.8.4` Facturen uit bons van de Key-conen kassa: periode kiezen, `F8 ga verder` maakt de facturen, `F9 maak pdf` geeft een pdf.
- `V.8.5` Facturen van kassaverkopen.
- Details: zie de kassadocumentatie.

## 5. Extra opties op het bon-/factuurscherm (`+`-icoon rechtsonder)

Bron: module 0240A. Sommige punten zijn opties (offerte, verhuur) en bestaan enkel als de module aanwezig is.

| Optie | Werking |
|---|---|
| Artikels sorteren | Lijnen op verschillende manieren sorteren |
| Laad artikels van de laatste factuur | Neemt alle artikels over van de laatst gemaakte factuur van deze klant |
| Laad artikels van offerte | Geef de volledige referentie + `F8 zoek op`, of enkele letters + het zoekicoon (niets ingeven + icoon = alle offertes). Klik de offerte aan of geef het nummer + Enter. Artikels én prijzen van de offerte worden overgenomen |
| Laad artikels van verhuurbon | Kies de verhuurbon en vink de lijnen aan die je wil overnemen |
| 1 – Maak leeggoed op 0 voor deze bon/factuur | Zet voor alle artikels op dit document het automatisch gerekende leeggoed op 0 |
| 2 – Afhaling/klantenmemo | Toont de klantenmemo en ingegeven afhalingen; `F10 voeg afhaling toe aan bon/factuur` laadt de afhaling met referentie in het document |
| 3 – Toon historieken van deze klant | Alle artikels die de klant de laatste 2 jaar afnam, factuur per factuur. Het getal bij de rode pijl is het aantal schermen dat je kan teruggaan; via de iconen krijg je het lijntotaal (aantal × factuurprijs) of de detailfiche van het artikel. Afdrukbaar of als pdf; `F1` keert terug |
| 4 – Toon statistieken van deze klant | Enkel voor pakketten zonder historieken (minder uitgebreid). Kan niet gekozen worden als de historieken aanwezig zijn |

## 6. Vaste teksten 1–4 op bons en facturen

Wat de bronnen zeggen:

- Er zijn **maximaal 4 vaste teksten**. Ze worden ingegeven in de **facturatieparameters: `+` (verborgen parametertoets) → punt `4`** ("+.4"). Ze kunnen op elk moment aangepast worden.
- Op het document (leveringsbon §8.1.2 / rechtstreekse factuur §8.4 van de boekhoudhandleiding) staat het veld **"Vaste teksten (nr.)"**: daar kan je **2 teksten** laten afdrukken door hun nummer (1–4) in te tikken. Er kunnen dus per document maar twee nummers gekozen worden.
- (uit opleiding, 23/06/2026) In de praktijk worden bij de bon doorgaans tekst **1 en 2** manueel ingevuld. Er werd gezegd dat teksten die in **3 en 4** zijn ingevuld "altijd getoond worden" op een bon of factuur, maar dat gedrag zit in klantspecifieke programmatie en is niet af te leiden uit de tekstvelden zelf.
- (uit opleiding, 23/06/2026) Tijdens de demonstratie werden de teksten pas correct opgehaald nadat de bon opnieuw werd aangemaakt (parameters waren bij de eerste aanmaak nog niet opgehaald). Dat is een observatie uit één demo, geen bevestigde algemene oplossing.

Onzeker / te verifiëren:

- Of teksten 3 en 4 bij een bepaalde klant automatisch op elk document komen, hangt af van de programmatie van die klant. Niet beloven dat het kopiëren van een tekst naar 3 of 4 hem automatisch laat afdrukken.
- De geschreven handleiding laat toe om ook 3 en 4 manueel te kiezen; er is dus geen vaste regel "1/2 manueel, 3/4 automatisch".

Aanpak bij een supportvraag ("de tekst staat niet / wel op mijn factuur"):

1. Vraag eerst wat de klant wil: de tekst automatisch op elk document, of bewust per document kiezen?
2. Bekijk (alleen lezen) op een bestaande bon/factuur welke tekstnummers ingevuld zijn en in `+` → `4` wat er in teksten 1–4 staat.
3. Per document kiezen: de juiste nummers invullen in "Vaste teksten (nr.)".
4. Automatisch op alles: laten nakijken door tweede lijn (programmatie). Maak geen echte bon of factuur als proef.

## 7. Herafdrukken van facturen (V.8.H) – module 0234A

- Tijdens het factureren, net voor het boeken, wordt het detail van elke factuur weggeschreven in de map **`FTKOPIE`**: één bestand per factuur met naam `DDDNNNNN.JJ` (DDD = dossier, NNNNN = factuurnummer, JJ = jaartal).

| Punt | Functie |
|---|---|
| `V.8.H.1` → 1 | Bekijken/afdrukken van 1 factuur: geef het **factuurnummer**, of de **klant** (dan volgt een lijst van zijn facturen). **Jaartal** staat op het huidige jaar; wijzigen voor facturen van vorig jaar. **Subdirectory** staat op `\FTKOPIE\`; tijdelijk te wijzigen als oude facturen in een andere map bewaard worden |
| `V.8.H.1` → 2 | Herafdrukken van alle facturen van 1 klant (bv. kopie voor de brouwerij) |
| `V.8.H.2` | Uitschrijven detail van facturen naar TXT (voor Excel, bv. traceerbaarheid van een product) |
| `V.8.U` (verborgen) | Schrappen van een factuur, met de mogelijkheid statistieken/voorraad terug te zetten |

Uitschrijven naar TXT, velden:

- Naam TXT-bestand (standaard `FACTUREN.TXT`): moet eindigen op `.TXT`, max. 8 tekens voor de punt.
- Selectie facturen van … t.e.m. …: **begin- en eindfactuur zijn verplicht**.
- Selectie factuurdatum, selectie code artikel (optioneel).
- Selectie detail: `H` = enkel hoeveelheden (+ lotnummer), `V` = volledig (aantallen + bedragen).
- Jaartal facturen.
- Per factuurlijn worden o.a. uitgeschreven: factuurnummer, -datum, klantnummer en -naam, chauffeur, lijnnummer, artikel; bij H: aantallen, eenheid, gewicht, lotnummer; bij V bovendien eenheidsprijs, kortings%, nettototaal, leeggoed, munt, btw%, groep, accijns, aankoopwaarde, directe en semestriële korting. Velden die niet in het pakket bestaan, worden niet uitgeschreven.

Vanuit de boekhouding: rekening van de klant oproepen via `B.4`, op de factuur gaan staan en op het icoon klikken om de factuur te bekijken/herafdrukken.

Veelvoorkomende problemen:

| Probleem | Oorzaak / oplossing |
|---|---|
| Factuur van vorig jaar niet gevonden | Jaartal aanpassen in het selectiescherm |
| Oude facturen niet gevonden | Ze zijn verplaatst: Subdirectory tijdelijk naar die map zetten |
| Foute factuur moet weg | Gebruik `V.8.U` zodat statistieken en voorraad teruggezet kunnen worden; niet enkel in de boekhouding corrigeren |
| Ontvanger ziet enkel strepen in de gemailde pdf | Zie `jamadrink-layouts-en-afdrukken.md` |

## 8. Mobiele leeggoedterugname op leveringsbons (module 0240C) – verwerking in Jamadrink

Waarvoor: de chauffeur registreert met de PDA het leeggoed dat hij bij de klant terugneemt; op kantoor wordt dat automatisch aan de leveringsbon toegevoegd. PDA-installatie en -bediening in detail horen bij de PDA-documentatie; hieronder de keten voor zover die de bons raakt.

1. **Instellen (eenmalig)**: PDA in de houder, programma `Jamaspda` → "Aanpassen PDA-parameters" → "Algemene instellingen" → "Soort PDA-toepassing": `1` = enkel leeggoedterugname, `0` = ook stock/bestelling/barcodes. Map voor de aanpassingen van de bons: meestal `\jamapda\LGG-RETOUR\`; die map moet op de computer bestaan.
2. **Bij de klant**: op de PDA `JAMAMOBI` → (eventueel eerst "Camion") → "Ingeven retourleeggoed" → barcode van de leveringsbon scannen, of bonnummer en/of klantnummer manueel ingeven. Leeggoed scannen of manueel aanduiden en aantallen ingeven. "Opnames" toont wat al ingegeven is (daar kan je een lijn schrappen of een aantal aanpassen; een bon kan opnieuw gescand worden om te corrigeren). "Stop" toont het totaal per bedrag om op de bon over te schrijven.
3. **Terug op kantoor**: PDA in de houder, `Jamaspda` → "ZEND: Doorsturen alle gegevens en programma's naar PDA".
4. **Verwerken in Jamadata Desktop**: `V.8` → "Beheer leeggoed-retour met PDA" (`V.8.A`) → punt 1 "Aanpassen leeggoed op leveringsbons a.h.v. PDA-retourbon". Je krijgt de lijst van bons met te verwerken leeggoed; het groene icoon opent de bon, het teruggenomen leeggoed is onderaan toegevoegd.
5. Na verwerking verdwijnt de retourbon uit de lijst en staat hij in de **vuilbak** (rechtsonder) onder "verwerkte retourbons". Een per vergissing geschrapte retourbon kan daar teruggehaald worden. Het rode vuilbak-icoon verwijdert een retourbon definitief uit de Jamadata-map.

Opmerking uit de bron over de map voor PDA-bons: `j:\jamadata\jamapda\pdabon\` op de hoofdcomputer (driveletter kan verschillen); op een andere werkpost is het een andere letter (bv. `P:\jamapda\pdabon`).

## 9. Lijsten rond facturen

### Lijst openstaande / vervallen facturen (B.5.8) – module 0058A

Hoofdmenu boekhouding → punt 5 "Afdrukken lijsten" → punt 8.

| Veld | Betekenis |
|---|---|
| Openstaande of vervallen (O/V) | `V`: enkel facturen waarvan de vervaldatum vóór de einddatum ligt. `O`: alle facturen die op de einddatum nog niet betaald zijn, vervallen of niet |
| Einddatum vervallen/openstaand | Facturen na deze datum worden overgeslagen. Ligt de datum vóór de archiveringsdatum, dan zie je enkel facturen die bij archivering nog niet betaald waren |
| Einddatum betalingen | Tot welke datum betalingen meegeteld worden. Voorbeeld: facturen die vorige maand vervallen waren maar ondertussen niet betaald zijn → einddatum facturen = vorige maand, einddatum betalingen = vandaag |
| Selectie klanten of leveranciers (K/L) | Verkoop- (K) of aankoopfacturen (L) |
| Selectie 1 klant/leverancier | Optioneel |
| Einddatum boekdatum | Extra selectie op boekdatum (blanco = geen controle); gebruik dit om de lijst te laten aansluiten met de balans (laattijdig ingeboekte facturen met oudere factuurdatum) |

Per factuur: code en naam, betalingscondities, type boeking, factuurnummer, factuurdatum, vervaldatum, bedrag, opmerking; totaal per klant/leverancier en algemeen totaal.

### Facturenlijst klant/leverancier (B.5.7) – module 0079A

Lijst van facturen over een periode; bruikbaar om facturen op te zoeken of als controle voor de btw-listing.

| Veld | Betekenis |
|---|---|
| Periode facturen | Mag (gedeeltelijk) gearchiveerd zijn; het jaararchief mag nog niet gewist zijn |
| Afdrukken lijst leveranciersfacturen (J/N) + selectie 1 leverancier | Leeg = alle leveranciers |
| Afdrukken lijst klantenfacturen (J/N) + selectie 1 klant | Leeg = alle klanten |
| Lijst van de facturen afdrukken (J/N) | `J` = facturenlijst (elke factuur + totaal per klant); `N` = omzetlijst (enkel totaal per klant/leverancier) |
| Verkorte lijst afdrukken (J/N) | `J` = geen subtotalen per klant/leverancier; `N` = totaal per klant/leverancier |

Facturenlijst toont: code en naam, journaal en factuurnummer, factuurdatum, totaal, belastbaar bedrag, btw-bedrag, divers-bedrag (leeggoed), voldaan (JA of blanco). Omzetlijst toont de totalen per klant/leverancier.

## 10. Veelvoorkomende problemen (samenvatting)

| Probleem | Oorzaak / oplossing |
|---|---|
| Bij het maken van een bon verschijnt telkens een melding | F12 info met alarm en verstreken datum, of klantenmemo (F10) |
| Leeggoed komt dubbel of ongewenst op de factuur | `F9 leeggoed` voegt negatieve lijnen toe; automatisch leeggoed uitschakelen voor dit document via extra opties → 1 "Maak leeggoed op 0" |
| Factuur is "contant" | Betalingstermijn leeg op klantenfiche |
| Factuurnummer bestaat al (code 59) | Volgend vrij nummer nemen; niet handmatig een bestaand nummer kiezen met `F9 neem deze nummer` |
| Vaste tekst ontbreekt of staat ongewenst op document | Zie §6 |
| Factuur automatisch én manueel gemaild | Bij manueel mailen van een factuur die ook automatisch verstuurd wordt, vraagt het systeem of je tweemaal wil verzenden; kies Nee |
| Retourbon van PDA verdwenen | Kijk in de vuilbak rechtsonder bij "Beheer leeggoed-retour met PDA" |

## Bronnen

- `gebruikershandleiding JAMADRINK 2.0.docx` (map Jamadrink): V.8, V.8.1–V.8.5
- `0240A - Extra functies bij aanmaken van een bon-factuur.docx` (map Jamadrink/Handleidingen modules)
- `0240C - Mobiele leeggoedterugname op leveringsbons..docx` (map Jamadrink/Handleidingen modules; `0XXXA - Mobiele leeggoedterugname op leveringsbons..docx` is een dubbel)
- `0234A - Herafdrukken facturen.docx` (map Jamadrink/Handleidingen modules)
- `0058A - Lijst openstaande facturen.docx` (map Jamadrink/Handleidingen modules)
- `0079A - Facturenlijst klant-leverancier.docx` (map Jamadrink/Handleidingen modules)
- `00_CHECKPOINT_TEKSTEN_SCOPE.md` en de daarin geciteerde passages uit `Gebruikerhandleiding BOEKHOUDPAKKET.docx` (§8.1.2, §8.4) en de opleiding van 23/06/2026 (map 00_START_CLAUDE/13_TEKSTEN_SCOPE)
