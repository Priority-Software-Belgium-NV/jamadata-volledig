# Aankoopfiches en deelverpakkingen (clips)

Gebruik dit document voor: vragen over aankoopfiches (aankoopprijs, kortingen en artikelcode per leverancier per artikel), hoe ze aangemaakt en gebruikt worden bij bestellingen/leveringen, het controleprogramma V.3.7, en over deelverpakkingen/clips (koppelen aan een hoofdartikel, effect op stock, inventaris en prijzen).

## Deel 1 – Aankoopfiches

### Waarvoor dient het

Een aankoopfiche houdt per **artikel per leverancier** de aankoopvoorwaarden bij: aankoopprijs, kortingen, artikelcode van de leverancier, verpakking. Nuttig wanneer:
- hetzelfde artikel bij meerdere leveranciers aangekocht wordt;
- de codenummers van de leverancier op de bestelbon moeten staan;
- artikels gekoppeld moeten worden met die van de leverancier voor automatische prijsaanpassing (prijzenbestanden) of het inlezen van promotiefolders van de aankoopvereniging.

### Aanmaken

- **Automatisch**: bij het ingeven van aankopen (V.1) wordt een aankoopfiche aangemaakt als ze nog niet bestond, met de prijs en kortingen van die aankoop.
- **Manueel**: artikelfiche oproepen (V.9.3.1) en **F2 "aankoopfiche"** drukken. Je ziet de lijst van bestaande fiches en kan er een toevoegen.

### Raadplegen

Via de artikelfiche (V.9.3, F2) of bij het ingeven van bestellingen/leveringen aan leveranciers (V.1). Het overzicht toont per leverancier de aankoopprijs, de laatste aankoopdatum en de aankoopvoorwaarden (bv. per pallet kopen).

Functietoetsen in het overzicht:
- **F4 "alles/actief"**: alle fiches of enkel de actieve tonen. Actief = huidige datum ligt na de startdatum van de prijs en vóór de einddatum (bij een tijdelijke promotie).
- **F9 "voeg nieuwe fiche toe"**.
- **F10 "historiek"**: aankoophistoriek van dit artikel van de laatste 2 jaar (alle leveranciers).
- **Vergrootglas** achter een lijn: de aankoopfiche openen.

### Velden van de aankoopfiche

In principe is er één fiche per artikel/leverancier. Voor een tijdelijke promotie (met tot-datum) kan hetzelfde artikel meerdere fiches van dezelfde leverancier hebben.

| Veld | Uitleg |
|---|---|
| Leverancier | De leverancier waarvoor de voorwaarden gelden |
| Code leverancier | Artikelcode bij de leverancier; gebruikt op de bestelbon en voor het automatisch inlezen van prijslijsten/promotiefolders |
| Aantal/verpakking | Enkel als de verpakking van de leverancier **afwijkt** van het artikel: aantal in de aankoopverpakking (bv. artikel = 1 fles wijn, aankoop per doos van 6 → 6) |
| Bruto-aankoopprijs | Basisprijs **van de verpakking van de leverancier** |
| Vanaf ../../.. t.e.m. ../../.. | Begindatum: prijs geldt enkel voor bestellingen vanaf die datum. Einddatum: meestal leeg; enkel invullen voor een tijdelijke promotie |
| Korting (tot 5) | Per korting: bedrag of percentage, plus de onderstaande kenmerken |
| – Soort | `%` = procentueel, `E` = vast bedrag in euro, `H` = bedrag per hectoliter (automatisch berekend op basis van het volume) |
| – Prijs | `N` = berekend op het bedrag na voorgaande kortingen (cascade), `B` = berekend op de bruto-aankoopprijs |
| – Accijns | `E` = berekend op het bedrag exclusief accijnzen, `I` = inclusief accijnzen |
| – Periode | `F` = direct verrekend op factuur, `S` = korting wordt achteraf uitbetaald (uitgesteld) |
| – Bedrag korting | Effectief bedrag, automatisch berekend |
| Aankoopprijs factuur | Nettoprijs die op de factuur betaald wordt |
| Statistische prijs | Nettoprijs waar ALLE kortingen (ook de uitgestelde) af zijn |
| Laatst aangekocht | Datum van de laatste aankoop bij deze leverancier |
| Leveringsvoorwaarden | Vrije tekst, bv. per pallet te kopen |

Functietoetsen op de fiche: **F4 "schrap"** (fiche verwijderen), **F10 "aankoophistoriek"** (aankopen van dit artikel bij deze leverancier, laatste 2 jaar).

### Belangrijk: verpakking van de leverancier vs. verpakking van het artikel

- Prijzen op de aankoopfiche zijn altijd die van de **verpakking bij de leverancier** (bv. doos).
- Bij het controleren/wijzigen van de aankoopprijs op de artikelfiche (V.3.7) wordt de prijs **automatisch omgerekend** naar het aantal/verpakking van het artikel (bv. delen door 6 voor een fles). Ook het overzicht (F2 op artikelfiche) toont de omgerekende prijs.
- Bij bestellingen/leveringen aan leveranciers (V.1) moet altijd in de verpakking (en prijs) van de **leverancier** ingegeven worden. Bij het bijwerken van stock en statistieken rekent de computer automatisch om naar de verpakking van het artikel (bv. x 6).

### Gedrag bij bestellingen/leveringen (V.1)

- Bestaat er een aankoopfiche voor artikel + leverancier en valt de datum in de prijsperiode → prijs en kortingen van de aankoopfiche worden voorgesteld.
- Bestaat er geen → prijs en kortingen van de artikelfiche worden genomen.
- Bij levering worden prijs en kortingen van de levering **weggeschreven op de aankoopfiche** (en de fiche wordt aangemaakt als ze nog niet bestond).
- Is de prijs van de levering **lager** dan op de aankoopfiche, dan komt er een waarschuwing; je beslist zelf of de aankoopfiche aangepast wordt (bv. niet bij een tijdelijke promotie).
- **De aankoopprijs op de ARTIKELfiche wordt hierbij NIET aangepast.** Reden: het prijsbeheer (V.3) berekent de verhoging van de verkoopprijzen uit de verhouding tussen "oude" en "nieuwe" aankoopprijs; als de artikelfiche al aangepast was, zou de oude prijs verloren zijn.

### Aankoop- en verkoopprijzen wijzigen

- **Manueel**: via prijsbeheer (V.3.3 en V.3.4) of op de artikelfiche (V.9.3.1) via het **telmachine-icoon**. De nieuwe aankoopprijs wordt gevraagd, de verkoopprijzen worden herberekend, daarna worden de prijsafspraken overlopen en desgewenst verhoogd. Deelverpakkingen (clips) worden in dezelfde verhouding verhoogd. De aankoopfiche van de **hoofdleverancier** (= leverancier op de artikelfiche) wordt mee aangepast, zodat bij de volgende levering de juiste prijs voorgesteld wordt.
- **Controleprogramma V.3.7**: vergelijkt de prijs van de aankoopfiche met de aankoopprijs op de artikelfiche. Is de prijs op de aankoopfiche **hoger en recenter** dan op de artikelfiche (= prijs is gestegen bij de laatste levering), dan stelt het programma voor de verkoopprijzen te verhogen en start het bovenstaande manuele scherm.

### Veelvoorkomende vragen (aankoopfiches)

| Vraag | Antwoord |
|---|---|
| "Na een levering met hogere prijs is mijn verkoopprijs niet aangepast" | Normaal. De levering past enkel de aankoopfiche aan. Start V.3.7 om de verschillen te overlopen en de verkoopprijzen te verhogen. |
| "Bij een bestelling wordt een verkeerde prijs voorgesteld" | Controleer de aankoopfiche van die leverancier: prijsperiode (vanaf/t.e.m.), aantal/verpakking, en of er meerdere fiches (promotie) zijn. Gebruik F4 om alle i.p.v. enkel actieve fiches te zien. |
| "Aankoopprijs lijkt 6x te hoog/laag" | Aantal/verpakking op de aankoopfiche wijkt af of is fout; prijzen op de aankoopfiche zijn per leveranciersverpakking. |
| "Leverancierscode staat niet op de bestelbon" | Veld "Code leverancier" op de aankoopfiche is leeg. |

## Deel 2 – Deelverpakkingen (clips)

### Waarvoor dient het

Een deelverpakking (clip) is een deel van een hoofdartikel (bak) dat apart verkocht wordt. **Elke deelverpakking wordt als een apart artikel aangemaakt** en daarna aan het hoofdartikel gekoppeld.

Basis van alle berekeningen: het **aantal stuks per verpakking** op beide artikelfiches.

Voorbeeld: hoofdartikel = bak van 24 flesjes, deelverpakking = clip van 6 flesjes.
- 1 clip = 6/24 = 1/4 bak
- bij verkoop van 1 clip daalt de stock van de bak met 0,25
- aankoopprijs van 1 clip = 1/4 x aankoopprijs van de bak

### Wat verandert er zodra een artikel aan een hoofdartikel gekoppeld is

- De **stock** wordt niet meer bijgewerkt op de clip, maar op het hoofdartikel.
- Bij de **inventaris** worden de getelde clips bij het hoofdartikel geteld; enkel het hoofdartikel komt op de inventarislijst.
- Bij een **prijswijziging** van het hoofdartikel (via V.3) wordt automatisch ook de prijs van de clip(s) gewijzigd (het programma vraagt het en toont elke clip).

**Uiterst belangrijk**: het **aantal per bak** moet correct ingevuld zijn op de artikelfiche van de bak **én** van de clip. Een fout aantal veroorzaakt een **foute stockbijwerking én een foute prijsberekening**.

### Op de artikelfiche

Naast de omschrijving staat een icoon:

| Icoon | Betekenis |
|---|---|
| **+ rood** | Het artikel heeft geen deelverpakking(en). Klik om andere artikels (clips) te koppelen. |
| **+ groen** | Het artikel heeft deelverpakking(en). Klik om ze te zien en te wijzigen. |
| **Koppeling-icoon** | Dit artikel is zelf een deelverpakking. Klik om de koppeling te verbreken. |

### Scherm deelverpakkingen

- Er kunnen tot **10** artikels gekoppeld worden.
- Knoppen bij een **lege lijn**:
  - vergrootglas: het artikel zoeken dat je wil koppelen;
  - nieuw artikel: een nieuw artikel (clip) aanmaken — **eerst het juiste aantal stuks ingeven!**
- Knoppen bij een **gekoppeld artikel**:
  - `i`: de artikelfiche oproepen/aanpassen;
  - `X`: de koppeling met dit artikel verbreken.

### Deelverpakkingen en kassapromoties

Bij een kassapromotie "toepassen op Bak" worden losse flesjes en clips meegerekend om tot het aantal bakken te komen (24 flesjes = 1 bak); is de promotie op de clip (bv. clip van 4) en koopt de klant een bak, dan telt dat als 6 clips. Zie `promoties.md`.

### Veelvoorkomende problemen (clips)

| Probleem | Oorzaak / oplossing |
|---|---|
| Stock van de bak daalt te veel of te weinig bij verkoop van clips | Aantal per bak fout op bak of clip. |
| Clip heeft zelf geen stock / staat niet op de inventarislijst | Normaal: stock en inventaris zitten op het hoofdartikel. |
| Prijs van de clip klopt niet na prijswijziging | Aantal per verpakking fout, of clip niet gekoppeld (icoon + rood op de bak), of bij de prijswijziging is de clip niet bevestigd. |
| Clip moet opnieuw een zelfstandig artikel worden | Op de clip het koppeling-icoon aanklikken, of op het hoofdartikel `X` naast de clip. |

## Bronnen

- `0268A - Aankoopfiches.docx` — Jamadrink/Handleidingen modules
- `0219C - Deelverpakkingen (Clips).docx` — Jamadrink/Handleidingen modules
- `0295A - Uitgebreide Kassa-promoties.docx` (bak/fles/clip in promoties) — Jamadrink/Handleidingen modules
