# Zebra-kaartjesprinter (rayonkaartjes / prijskaartjes)

Gebruik dit document voor: installatie en controle van de Zebra-labelprinter (ZDesigner GK420t, ook GX-type) waarmee Jamadata rayonkaartjes/prijskaartjes afdrukt: Windows-driver, voorkeursinstellingen, kalibratie, de instellingen in Jamadata (afdrukpost, papiersoort, documenteigenschappen, positie/offset) en de aanpak wanneer er niets of verkeerd gepositioneerd wordt afgedrukt. Het document maakt onderscheid tussen bevestigde procedure (interne HOWTO), informatie uit een opleiding en zaken die slechts een hypothese zijn.

## 1. Driver installeren (Windows)

1. De driver installeert normaal vanzelf. Lukt dat niet: download de **GK420t**-driver van de Zebra-supportsite (support-downloads → desktop → gk420t → drivers).
2. **Ook de nieuwe printer moet met deze (GK420t-)driver geïnstalleerd worden.**
3. Sluit de printer aan en zet hem aan. Bij manuele installatie: doorloop de wizard, kies printer **ZDesigner GK420t**, kies de juiste **USB-poort**, zet de aanvullende opties uit en kies Voltooien.

(Uit opleiding, 28/05/2026) Een GX-printer met de GK-driver "print hetzelfde"; het typeverschil GK/GX is op zich geen oorzaak van niet-afdrukken.

## 2. Voorkeursinstellingen van de driver

Windows → Printers en scanners → de ZDesigner-printer → **Eigenschappen van printer** → tab Algemeen → **Voorkeursinstellingen**:

| Tab / onderdeel | Instelling |
|---|---|
| Geavanceerde instelling | Traceringsmodus van "Webdetectie" naar **Markeringsdetectie** |
| Etik. type | Een **nieuw etiket** aanmaken (waarden volgens schermafdruk in de HOWTO) |
| Opties – papierformaat | Eenheid **mm** (niet cm) |
| Opties – afdrukstand | **Liggend** (niet Staand) en **Draaien 180°** |
| Opties – grootte | Breedte **37 mm**, hoogte **80 mm** |

(Uit opleiding, 28/05/2026) Controlevolgorde bij nakijken: mm → liggend → 37 x 80 → Geavanceerd op markering → etikettype → Wijzigen. Daar staat ook de **intensiteit (darkness)**: de waarde bepaalt hoe donker er gedrukt wordt en hoeveel lint verbruikt wordt. In de opname stond ze op 30 en werd 50 "meestal voldoende" genoemd; welke kant donkerder is, is in de transcriptie tegenstrijdig – onzeker / te verifiëren.

## 3. Kaartjes laden en kalibreren

Volgens de interne HOWTO:
1. Steek de kaartjes in de printer: de **rol tussen de 2 geleiders** en het **papier onder de andere geleider**.
2. Monteer een **lint**. De handleiding daarvoor zit in de printer zelf.
3. Een Windows-testpagina kan je afdrukken, maar die komt er volgens de HOWTO slechts **gedeeltelijk** op door het draaien in de driver.
4. Klik in de driver op **Kalibreren** (Voorkeursinstellingen → Geavanceerd).
5. Knippert het groene lampje: kalibreer met de knop op de printer. Er hoort dan **één ticket** uit te komen; vanaf dan zijn de etiketten goed gepositioneerd.

Belangrijke grenzen (uit de eerdere AI-gecureerde laag, mappen 11/12 "Zebra"):
- De HOWTO zegt enkel "met de knop kalibreren" en geeft **geen volledige knoppenreeks**. De FEED-knop van de GK420t heeft volgens de fabrikant (Zebra GK420t User Guide, P1131978, "FEED Button Modes") **meerdere modi, waaronder fabrieksherstel**. Geef daarom nooit een losse instructie "houd de knop ingedrukt" zonder de volledige procedure: beginvoorwaarde, moment van loslaten, verwacht resultaat en wanneer te stoppen.
- Vraag vóór een kalibratie-advies eerst: **model**, **materiaal** (kaartjes/lint), en het **lampje** (kleur, knipperpatroon). Bij een onbekend knipperpatroon: geen korte of lange FEED-druk laten uitvoeren; escaleren naar een senior.
- Eén doorgeschoven etiket bewijst niet dat rol of papier juist ligt.
- De rol (op de rolhouder) en het uitlopende papier (door de geleiding) zijn twee verschillende delen van de papierroute (fabrikantgids "Loading Roll Media"). Laat de klant niets "op gok" herleggen op basis van de verkorte beschrijving in de HOWTO.
- Veilige lees-/afdrukcontroles (instellingen bekijken, testafdruk) mogen zonder escalatie; onzekere toestelbediening of reset niet.

**Hypothese, niet bevestigd:** dat een gedeeltelijke Windows-testpagina "normaal" is door de 180°-draaiing. De HOWTO vermeldt dit, maar het is niet onafhankelijk getest; behandel het als mogelijke verklaring, niet als bewijs dat de printer in orde is. Ook een bevestigde 180°-draaiing is geen bewezen oorzaak van een afdrukprobleem.

(Uit opleiding, 28/05/2026) Na het corrigeren van de driverinstellingen kwam de Windows-testpagina wel goed uit. Kijk na het kalibreren naar de **scheurlijn**: bij de nieuwere printers wordt het etiket enkele mm (in de opname 4 mm) verder uitgevoerd zodat het kaartje afgescheurd kan worden; bij de oude printer is dat niet nodig. De precieze instelling is uit de opname niet af te leiden – onzeker / te verifiëren.

## 4. Instellingen in Jamadata

Alle paden vanaf het hoofdmenu; **+** is het parametermenu, **J** de printerinstellingen.

| Stap | Pad | Wat doen |
|---|---|---|
| 1. Afdrukpost aanmaken | **+.J.1** | Klik op de eerstvolgende lege lijn, geef de printer een naam en kies de juiste driver. Is de printer **niet op de server** aangesloten, dan moet de driver hier **niet** ingevuld worden |
| 2. Printer op de werkpost | Jamadata DESKTOP → **Configuratie** → **Documenten** | Kies op de juiste werkpost dezelfde printer. (Uit opleiding) het papierformaat hier op automatisch/leeg laten |
| 3. Papiersoort aanmaken | **+.J.3** | Eerstvolgende lege lijn, naam geven (bv. rayonkaartjes), **F10** voor de papierinstellingen (waarden volgens schermafdruk in de HOWTO). (Uit opleiding, 28/05/2026) in het detail horen de waarden **1500**, **300** en **0** te staan; welke velden dit precies zijn is in de opname niet duidelijk – te verifiëren in de HOWTO |
| 4. Documenteigenschappen | **+.J.2** | Pas **formaat 17** aan: klik achter het nummer op de lege lijn en kies de juiste papiersoort en de standaard afdrukpost. (Uit opleiding) dit is de lijn "rayonkaartjes"; in de besproken installatie ontbrak daar de papiersoort, wat mee de oorzaak was |
| 5. Positie van de kaartjes | **5.9.+** | Positie/offset corrigeren (waarden volgens schermafdruk in de HOWTO; verticaal standaard **410**) |
| 6. Test | **5.9** (afdrukken prijskaartjes/affiches) | Druk 1 TEST-etiket af vanuit het pakket. De handleiding staat rechts bovenaan in het menu afdrukken prijskaartjes/affiches |

## 5. Problemen en oplossingen

| Symptoom | Controle / oplossing | Status |
|---|---|---|
| Ticket komt uit de printer maar er **staat niets op** | De **offset** is verkeerd ingevuld. Verticaal hoort **410**; bij een nieuwere printer is **440** gebruikt | Bevestigd (HOWTO) |
| Afdruk staat **te hoog** op het kaartje | Parameter bij **5.9.+** verhogen, bv. naar **460** | Bevestigd (HOWTO) |
| Etiketten verschuiven / groen lampje knippert | Kalibreren (driver → Kalibreren); knopkalibratie enkel met volledige procedure, zie punt 3 | HOWTO + fabrikantgrens |
| Windows-testpagina komt gedeeltelijk | Mogelijk door de 180°-draaiing in de driver | **Hypothese** |
| Afdruk te licht/te donker | Intensiteit in etikettype → Wijzigen aanpassen | Uit opleiding 28/05/2026 |
| Printen lukt onder Windows maar **niet vanuit Jamadata** | Loop +.J.1, +.J.2 (formaat 17: papiersoort + afdrukpost), +.J.3 (papiersoort-detail) en 5.9.+ (offset) na, en de printerkeuze op de werkpost. Als alles juist staat en het nog niet werkt: test de printer op een andere werkpost/de server | Uit opleiding 28/05/2026 |
| Idem, alles lijkt juist | Mogelijk is `gms.ini` op de pc beschadigd: het pakket schrijft er automatisch in en de printersectie kan corrupt raken. Vergelijk met de `gms.ini` van een werkende pc | **Hypothese** (uit opleiding, niet bevestigd als oorzaak) |

Instellingen uit de HOWTO beschrijven één installatie; ze bewijzen niet dat dezelfde waarden bij elke klant gelden. Lees eerst de bestaande waarden bij de klant af voor je iets wijzigt.

## Bronnen
- `Jamadrink/HOWTO-Installatie_ZEBRA_Kaartjesprinter.docx` (de `.doc` is een dubbel)
- `Claude/Transcripties opleidingen/ZEBRA-Printer Settings nakijken.-20260528_093739-Opname van vergadering.txt` (gesproken bron, herkenningsfouten mogelijk)
- `00_START_CLAUDE/11_ZEBRA_PROCEDURE_20261110_4a92e7c1/00_CHECKPOINT_ZEBRA_PROCEDURE.md`
- `00_START_CLAUDE/12_ZEBRA_HYPOTHESE_20261110_6be52d90/00_CHECKPOINT_ZEBRA_HYPOTHESE.md`
- Daarin aangehaalde fabrikantbron: Zebra GK420t Desktop Thermal Printer User Guide (P1131978), secties FEED Button Modes en Loading Roll Media
