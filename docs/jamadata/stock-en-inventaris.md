# Stock, stocklocaties en inventaris (Jamadrink)

Gebruik dit document voor: vragen over hoe de stock in Jamadrink werkt (depot en stocklocaties/filialen, wat de stock verhoogt of verlaagt, leeggoedstock), leveringen en mutaties tussen filialen, en het opmaken van de inventaris: manueel met tellijsten of met een PDA (menu V.A.2 en V.A.M), het vastleggen van de inventaris op 1/1, het afdrukken en corrigeren van de eindejaarsinventaris.

Voor de jaarafsluiting zelf (backup, klaarmaken dossier voor nieuw jaar): zie `stock-jaareinde-31-12.md`.

## Deel 1 – Werking van de stock

### Depot en stocklocaties (module Beheer stocklocaties)

Met de module stocklocaties wordt de stock van de eigen winkels (filialen) apart bijgehouden. Het beheer gebeurt op het centrale systeem, waar alle in- en uitbewegingen verwerkt worden. Er zijn twee soorten stock:

| Stock | Wordt verhoogd door | Wordt verlaagd door |
|---|---|---|
| **DEPOT** (stock van de groothandel = de stock op de artikelfiche) | Ingeven van leveringen van leveranciers; retours van klanten en filialen | Facturatie; leveringen aan filialen; retours aan leveranciers |
| **STOCKLOCATIE** (individuele stock per filiaal) | Leveringen aan dit filiaal; levering van een andere winkel (mutatie) | Verwerken (inlezen) van de kassaverkopen; retours aan depot; levering aan een andere winkel (mutatie) |

De **totale stock** van de firma is de som van alle individuele stocks.

### Instellen kassa's en stocklocaties (V.2.+)

| Veld | Uitleg |
|---|---|
| Kassa-naam | Korte benaming per kassa. Elke BESTAANDE kassa moet een naam hebben; niet-gebruikte kassa's GEEN naam geven (de controle op een juiste kassakeuze steunt hierop). |
| Laatste verkoop | Datum van de laatst ingelezen verkoop voor deze kassa. Toont tot wanneer de verkopen verwerkt zijn en dient als beveiliging: **de computer leest geen verkopen meer in met een datum kleiner dan deze** (vermijdt dubbele verkopen). |
| Klant | Een bestaande klant koppelen aan elke kassa: gebruikt voor de verkoopstatistieken en voor de factuur van de contante verkopen. Meerdere kassa's in één filiaal: best dezelfde klant. |
| Sluitingsuur | Normaal sluitingsuur van de kassa. Bij het inlezen van de kassaverkopen (V.2.3) wordt gecontroleerd of het verkopenbestand recent genoeg is (= niet vergeten door te sturen met de kassa). |
| Stocklocatie | Per kassa de stocklocatie waar ze staat; bepaalt uit welke stock de verkochte goederen genomen worden. **1 tot 10** = aparte locatie, **99** = stock van het depot (= die van de artikelfiche). |
| Naam stocklocatie | Onderaan: korte naam per filiaal. Elk bestaand filiaal moet een naam hebben; niet-gebruikte geen naam. |

### Stock op de artikelfiche

- De stock op de achterkant van de artikelfiche (**F9**) is de **DEPOT-stock**.
- **F5 stocklocaties** toont de gegevens per locatie onder elkaar (de depotlijn herhaalt de artikelfiche):

| Veld | Uitleg |
|---|---|
| Stock | Actuele stock van de locatie, **zonder** rekening te houden met niet-gefactureerde leveringen/verkopen |
| Min.stock | Minimumstock; gebruikt voor de lijst van te bestellen artikels |
| Norm.stock | Normale stock; gebruikt om automatisch een bestelling te genereren voor artikels onder minimumstock |
| Geleverd | Aantal geleverd aan dit filiaal; verhoogt bij elke levering aan het filiaal (V.8.x) |
| Verkocht | Aantal verkocht in dit filiaal; verhoogt bij het inlezen van de kassaverkopen (V.2.3). Kan via "periodewerkzaamheden" op 0 gezet worden. |
| VK-datum | Laatste datum waarvoor een verkoop geregistreerd werd bij het inlezen |

### Andere punten met filiaalselectie

- **Beheer Key-Conen kassa (V.2)**: in alle punten is een selectie op kassa ingebouwd. Bij het inlezen van de verkopen (V.2.3) wordt de overeenstemmende (filiaal)stock verminderd.
- **Afdrukken stocklijsten (V.5.2)**: alle lijsten hebben een selectie op filiaal (individueel of samen). **V.5.2.1** = actuele stocklijst.
- **Periodewerkzaamheden (V.A.3 t.e.m. 5)**: stock/inventaris ingeven, met selectie per filiaal.

### Leveringen en mutaties aan filialen (V.8.x)

Registreert leveringen van DEPOT naar een filiaal en stockmutaties tussen filialen.

1. Er wordt een bestelling ingegeven; eerst wordt het filiaal gevraagd waarnaar geleverd wordt.
2. In het detailscherm geef je de artikels in. Voor een **mutatie** tussen filialen kan je hier een ander (vertrek)filiaal ingeven.
3. De bon wordt afgedrukt en opgeslagen (zoals een bon vóór facturatie). Via een icoon kan een bestelling voorgesteld worden op basis van de verkopen in die winkel.
4. Na de levering wordt de bon **ingeboekt** (zoals bon → factuur): de levering wordt opnieuw getoond en afgedrukt met de vermelding "Geboekt op xx/xx/xx". De stock van het DEPOT daalt, die van het filiaal stijgt, de bon wordt geschrapt.
5. Er is ook een punt om een levering **direct in te boeken** (zonder bon).

### Werking stock leeggoed

- **Totale stockwaarde leeggoed** = leeggoedwaarde van de goederen met leeggoed (volle bakken) + stock van de leeggoedartikels (lege bakken). Dit totaal kan enkel berekend worden door de **actuele stocklijst (V.5.2.1)** af te drukken.
- Leeggoedwaarde van het **volgoed**: waarde van het leeggoed van dat artikel (bv. een bak cola 6x1L) x aantal in stock van dat artikel.
- Waarde van de **lege bakken**: stock van het leeggoedartikel x prijs van dat leeggoedartikel. **De stock van een leeggoedartikel = het aantal LEGE bakken.**
- Bij verkoop (kassa of facturatie) wordt **enkel de stock van het verkochte artikel** gewijzigd:
  - verkoop van een product: enkel de stock van dat product daalt, **niet** die van het bijhorende leeggoedartikel (de leeggoedwaarde van het volgoed daalt vanzelf mee);
  - een leeggoedartikel (meestal terugname): de stock van dat leeggoedartikel wordt **wel** aangepast (terugname verhoogt de stock lege bakken).
- Lege bakken teruggeven aan de leverancier (aankoopbeheer) verlaagt de stock (en waarde) van het lege leeggoed.
- Mutaties naar andere filialen: zelfde redenering, enkel de stock van het ingegeven artikel wijzigt.

### Deelverpakkingen (clips)

De stock van een clip wordt bijgehouden op het hoofdartikel (bak), volgens de verhouding van het aantal stuks. Zie `prijzen-aankoopfiches-en-deelverpakkingen.md`.

## Deel 2 – Inventaris: algemene regels

Alles voor de inventaris staat in het menu **V.A.2**; de PDA-punten in **V.A.M** (Mobiele stockopname).

De werkwijze is ook bruikbaar voor wie **geen stock bijhoudt** in de computer (aankopen niet ingeeft): ideaal voor de jaarlijkse inventaris op 31/12.

**Wanneer ingeven?**
- Je houdt **geen** stock bij: mag uitgesteld worden tot het rustiger is.
- Je houdt **wel** stock bij: de getelde stock moet ingegeven zijn **VOOR je opnieuw facturen maakt**.

Opmerking: in handleiding 0220B staat bij het eerste punt per vergissing "u houdt stock bij"; 0220C heeft de correcte formulering ("u houdt geen stock bij").

**In welk dossier?**
- Je houdt stock bij: **MOET in het huidige dossier**.
- Je houdt geen stock bij: liefst in het huidige dossier; zijn er intussen veel prijzen gewijzigd, ga dan naar het **vorige dossier**, omdat daar nog de oude prijzen staan.

**Niet onderbreken**: tijdens het ingeven van de getelde stock tot en met het overkopiëren naar inventaris 1/1 mag er **NIET gefactureerd** worden en mogen er **geen kassaverkopen ingelezen** worden. Werk die stappen in één keer af.

Prijswijzigingen op datum die ingaan bij het nieuwe boekjaar: zolang ze niet definitief gemaakt zijn (V.3.5), kan de inventaris nog aan de oude prijzen gemaakt worden.

### Overzicht menupunten inventaris

| Menupunt | Functie |
|---|---|
| V.A.2.T | Lijst "Stockopname/controle" (tellijst) drukken |
| V.A.2.1 | Op nul zetten actuele stock |
| V.A.2.2 | Verwerken van de artikels op werkbons kassa's (= biermanden) |
| V.A.2.3 | Verwerken van de aantallen, geteld met PDA |
| V.A.2.4 | Ingeven van de manueel getelde aantallen |
| V.A.2.5 | Overkopiëren huidige stock naar inventaris 1/1 |
| V.A.2.6 | Afdrukken eindejaarsinventaris |
| V.A.2.C | Inventaris corrigeren |
| V.A.M | Menu Mobiele stockopname (PDA): K = artikels klaarzetten/uitschrijven voor PDA, A = wissen vorige stockopnames |

## Deel 3 – Manuele inventaris (0220B)

Vier stappen: (1) tellijsten drukken en tellen, (2) stock ingeven, (3) inventarislijst afdrukken, (4) fouten corrigeren en opnieuw afdrukken.

### Stap 1 – Tellen in winkel/magazijn

1. Druk de lijst "Stockopname/controle" via **V.A.2.T**. Druk zoveel lijsten als er tellers zijn; elke lijst wordt later apart ingegeven en de computer telt de aantallen op.
   - **Print volgens Nummer, Alfabetisch, per Leverancier of per Groep**: meestal A. Aparte lijsten per groep: sortering alfabetisch + "Selectie op groep"; herhaal voor alle groepen.
   - **Selectie stocklocatie (1-10, 99 = DEPOT, blanco = allemaal)**: lijsten per filiaal.
   - **Huidige stock afdrukken op lijst**: N; op J zetten voor een tussentijdse stockcontrole (enkel nuttig bij echt stockbeheer).
   - **Extra spatie tussen iedere lijn (J/N)**: J geeft meer schrijfruimte, maar een veel langere lijst.
2. Noteer de getelde stuks op de lijst. Voor **leeggoed** tel je enkel de **lege** bakken/vaten; het leeggoed van de volle bakken wordt automatisch berekend.

### Stap 2 – Stock ingeven in de computer

**2.1 De huidige stock wissen – V.A.2.1 "Op nul zetten actuele stock"**

Enkel als je geen volledig stockbeheer doet (de computerstock klopt dan niet, bv. negatieve getallen). **NIET doen bij een stockcontrole!**

- "Weet U heel zeker dat U op de artikelfiche het aantal in stock op nul wilt gaan zetten?" → standaard N; vul **J** in, anders gebeurt er niets.
- "Welke groep (blanco = alle artikelen)" → leeg laten om alles te wissen.
- "Welke stocklocatie (blanco = alles, 1-10 = stocklocatie, 99 = depot)" → enkel invullen om één filiaal te wissen.
- **F4** wist de stock.

**2.2 Werkbonnen van de kassa inlezen (biermanden) – V.A.2.2**

Enkel als de werkbonnen op de kassa gebruikt worden om klaargemaakte biermanden bij te houden; zo hoeft de inhoud niet met de hand geteld te worden.

1. **F4**: alle bons op de server wissen.
2. Stuur door met de kassa('s) (dagelijkse transfer, punt **N** op de kassa).
3. **F9**: lijst van de artikels/bonnen; controleer ze.
4. Indien in orde: **F8** past de stock aan voor deze artikels.

**2.3 De getelde stock ingeven – V.A.2.4 "Ingeven van de manueel getelde aantallen"**

Herhaal voor elke tellijst.

- **Toon artikels volgens Kodenummer of Alfabetisch (A/K)**: meestal A, zoals de lijst.
- **Selectie 1 groep**: enkel de artikels van één artikelgroep.
- **Selectie stocklocatie (99 = Depot, 1-10 = filiaal)**: om de stock van een filiaal in te geven.
- **F8**: (eventueel bijkomende selectie op artikelgroepen, daarna) het invulscherm met de artikels in dezelfde volgorde als de lijst.
- **F10**: artikel per artikel ingeven (als men zelf de artikels genoteerd heeft).

In het invulscherm:
- Geef het aantal in de juiste kolom (bak/fles), in de kolommen **WIJZIGING**: het aantal wordt dan **bij de stock opgeteld** (belangrijk bij meerdere tellijsten).
- Gebruik de kolommen **STOCK** enkel om te corrigeren (overschrijft de stock).
- **F9** schakelt tussen de kolommen "wijzigen" en "stock".
- **F3** = volgend scherm. **HOME** = helemaal naar boven; tik daar enkele letters om naar die plaats in de lijst te springen.

**2.4 Overkopiëren huidige stock naar inventaris 1/1 – V.A.2.5**

Legt de ingegeven stock vast, zodat de inventaris niet meer wijzigt wanneer er opnieuw gefactureerd wordt.

- "Datum van de vorige inventarisgegevens": ter informatie.
- "Mag ik de vorige inventarisgegevens overschrijven (J/N)": standaard N; vul **J** in, anders gebeurt er niets.
- "Datum van de nieuwe inventaris": bv. 01/01/xx. Deze datum komt op de lijst en **kan achteraf NIET meer gewijzigd worden**.
- "De stock van de filialen ook meetellen (J/N)": bij filiaalbeheer ook de aparte filiaalstock meetellen.
- **F8** kopieert de stock.
- De **huidige NETTO-aankoopprijs** wordt genomen als inventarisprijs.
- Vanaf nu is de inventaris vastgezet en mag er verder gefactureerd worden.

### Stap 3 – Inventaris afdrukken – V.A.2.6 "Afdrukken eindejaarsinventaris"

De vragen staan al juist ingevuld voor een correcte inventaris:
- **Print volgens Nummer, Alfabetisch, per Leverancier of per Groep**: vaak per groep (geeft subtotaal per groep).
- **Leeggoed-waarde naast ieder artikel drukken**: J als je ook het leeggoed van de volle bakken wil kennen.
- **Enkel artikels met stock drukken**: meestal J.
- **Normale verkoopprijs afdrukken**: N.
- **Totaal goederen per BTW% drukken**: bij J komt onderaan een totaal per btw-percentage.

Dit is de definitieve inventaris; hij mag zo vaak afgedrukt worden als nodig.

### Stap 4 – Fouten corrigeren

- Via **V.A.2.C**, of
- via de artikelfiche (V.9.3.1): **F9 "Vervolg"**, helemaal onderaan de velden **Inventaris 1/1** (= aantal) en **Inventarisprijs** (= aankoopprijs) aanpassen.

Daarna de lijst opnieuw afdrukken (V.A.2.6).

## Deel 4 – Inventaris met PDA (0220C)

Voor PDA's van het type Symbol/M3/Honeywell met **JamaMobi** (op de PDA) en het beheerprogramma **JamaSpda** (op de pc met de PDA-houder). Negen stappen.

### Stap 1 – PDA klaarmaken

- PDA volledig opladen (liefst een nacht in de houder), ook de reservebatterij.
- Start **JamaMobi**, druk op **Wissen** en daarna op **Stock**: eventuele oude opnames op het toestel worden gewist.

### Stap 2 – Recentste artikelgegevens naar de PDA

1. Menu "Mobiele stockopname" (**V.A.M**), punt **K**, druk **F8**: de artikelgegevens worden klaargezet voor de PDA.
2. Ga op de PDA uit de programma's en steek hem in de houder.
3. Start **JamaSpda** op de pc waar de PDA op aangesloten is (dubbelklik op het rode icoon "JamaSpda" op het bureaublad).
4. Klik op de rode balk **ZEND: Doorsturen gegevens**.

### Stap 3 – Vorige stockopnames op de server wissen

Menu V.A.M, punt **A (wissen)**; geef indien nodig (PDA op afstand) het PDA-nummer in en druk **F4**.

### Stap 4 – Scannen/tellen

- Laat JamaSpda open staan op de pc zolang er geteld wordt.
- Op de PDA: start **JamaMobi** → knop **Stock** → scan het product → aantal ingeven met **+**/**-** of het toetsenbord → **OK**. De opname is opgeslagen en het toestel is klaar voor het volgende artikel.
- **Stuur regelmatig door** (bv. na elk rek):
  - PDA: enkele keren op **Stop** tot op het Windows-bureaublad; PDA in de houder.
  - PC: klik op de rode balk **Toevoegen stockopnames PDA**. De opnames worden toegevoegd aan het grote stockbestand op de computer en gewist op de PDA.
  - Neem de PDA uit de houder, start JamaMobi en scan verder.
- Verwissel tijdig de batterij (bv. om de 30 minuten).

### Stap 5 – PDA-gegevens verwerken op de computer

Zelfde regels over tijdstip, dossier en niet factureren als bij de manuele inventaris (zie Deel 2).

1. **Stock wissen** via V.A.2.1 (zoals bij manueel; niet bij een stockcontrole).
2. **Werkbonnen biermanden** via V.A.2.2 (zoals bij manueel).
3. **V.A.2.3 "Verwerken van de aantallen, geteld met PDA"**:
   - Controleer eerst met **F9** of dit de gescande producten zijn.
   - Naam van het STOCK-bestand: **`mobstock.dat`**; datum/uur van de laatste opname wordt getoond.
   - "Selectie periode opname" (blanco = alles): eventueel de periode waarin gescand is.
   - "Selectie 1 pda" (1-10 of blanco): bij meerdere PDA's (of op afstand) het PDA-nummer, anders blanco.
   - "Wenst U eerst de stock te wissen vooraleer in te lezen (A,S,N)": laat op **N** (is al gebeurd via V.A.2.1).
   - **F4** verwerkt de gescande stock.

### Stap 6 – Manueel getelde artikels bijgeven

Via **V.A.2.4**, zoals bij de manuele inventaris (kolommen WIJZIGING tellen op bij wat de PDA al inbracht).

### Stap 7, 8 en 9

Identiek aan de manuele inventaris: **V.A.2.5** overkopiëren naar inventaris 1/1, **V.A.2.6** afdrukken, corrigeren via **V.A.2.C** of de artikelfiche (F9 Vervolg: Inventaris 1/1 en Inventarisprijs).

## Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Stock staat negatief | Er worden geen (of niet alle) aankopen/leveringen ingegeven; de stock wordt enkel verlaagd door verkopen. Bij de inventaris eerst op nul zetten (V.A.2.1) en dan tellen. |
| Inventaris wijzigt nog na het tellen | Er is niet overgekopieerd naar inventaris 1/1 (V.A.2.5), of er is gefactureerd/ingelezen tussen het ingeven en het overkopiëren. |
| "Op nul zetten" of "overkopiëren" doet niets | De bevestigingsvraag stond nog op N; J invullen. |
| Aantallen van de tweede tellijst overschrijven de eerste | Er is in de kolom STOCK ingegeven in plaats van WIJZIGING (F9 om te wisselen). |
| Datum van de inventaris is fout | Volgens de handleiding kan de datum na V.A.2.5 niet meer gewijzigd worden. Opnieuw overkopiëren overschrijft de vorige inventarisgegevens met de stock van dat moment; of dat nog verantwoord is, hangt af van wat er intussen gefactureerd is (te beoordelen door support). |
| Inventariswaarde lijkt fout | Inventarisprijs = netto-aankoopprijs op het moment van V.A.2.5. Corrigeer per artikel via V.A.2.C of de artikelfiche. Bij veel prijswijzigingen sinds 31/12: inventaris in het vorige dossier maken. |
| Clip staat niet op de inventaris | Normaal: clips worden bij het hoofdartikel geteld. |
| Leeggoedwaarde volle bakken ontbreekt | "Leeggoed-waarde naast ieder artikel drukken" op J zetten. |
| PDA-telling wordt niet (volledig) verwerkt | Niet alle opnames doorgestuurd ("Toevoegen stockopnames PDA"); verkeerde periode of PDA-nummer bij V.A.2.3; controleer met F9 en datum/uur laatste opname van `mobstock.dat`. |
| Oude PDA-tellingen komen mee | Vorige opnames niet gewist (JamaMobi Wissen → Stock, en V.A.M punt A). |
| Kassaverkopen worden niet ingelezen | Datum ligt vóór "Laatste verkoop" van die kassa (beveiliging tegen dubbel inlezen), of verkopenbestand is niet recent (sluitingsuur-controle). |
| Stock van filiaal daalt niet bij verkoop | Kassa heeft verkeerde stocklocatie (V.2.+) of verkopen zijn niet ingelezen (V.2.3). |

## Bronnen

- `0155A - Beheer stocklocaties.docx` — Jamadrink/Handleidingen modules
- `0220B - Werkwijze MANUELE inventaris.docx` — Jamadrink/Handleidingen modules
- `0220C - Werkwijze inventaris met PDA.docx` — Jamadrink/Handleidingen modules
- `HOWTO-Werking stock.docx` (deel "Werking stock leeggoed") — Jamadrink
- `0219C - Deelverpakkingen (Clips).docx` — Jamadrink/Handleidingen modules
- `0213B - Inbrengen uitgestelde prijswijzigingen op datum.docx` (inventaris aan oude prijzen) — Jamadrink/Handleidingen modules
