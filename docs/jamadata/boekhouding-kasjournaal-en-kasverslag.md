# Boekhouding in Jamadata: kasjournaal manueel inboeken en kasverslag afdrukken/inboeken

Gebruik dit document voor: vragen over hoe kassaverkopen in de boekhouding komen: het manueel inboeken van de dagelijkse kasboeking in het kasjournaal (aan de hand van de kastickets van de KeyConen-kassa), de benodigde klant- en grootboekfiches (klant "Kassaverkopen", wachtrekeningen Bancontact/kredietkaart), en de module Kasverslag (V.2.4) die de kassaverrichtingen centraliseert en optioneel rechtstreeks in de boekhouding boekt, met de betaalcodes, parameters en de grenzen van wat de bronnen garanderen (dubbel boeken, verschil met "Inlezen verkopen").

## 1. Overzicht: twee manieren

| Manier | Wanneer | Waar |
|---|---|---|
| **Manuele kasboeking** | Geen kasverslag-boeking ingesteld; de gebruiker boekt zelf dagelijks de totalen van de kastickets | Hoofdmenu boekhouding, punt 2, kasjournaal |
| **Kasverslag afdrukken/inboeken** | Module kasverslag + boekhoudmodule; het verslag kan na het afdrukken rechtstreeks geboekt worden in een kasjournaal | Punt V.2.4 (menu Voorraad/kassa) |

Hoe kassaverkopen in de boekhouding komen **verschilt per installatie**: via manuele overdracht of doordat een medewerker de verkopen zelf boekt. Er is geen automatische synchronisatie; het boeken is altijd een handeling van een gebruiker (expertbevestiging HUMAN-Q013).

## 2. Manueel het kasjournaal inboeken

### 2.1 Benodigde fiches

| Fiche | Doel |
|---|---|
| Klantenfiche **"Kassaverkopen"** | Op deze klant wordt (dagelijks, wekelijks of maandelijks) een factuur gemaakt van de **particuliere** kassaverkopen. Dat kan automatisch via "Facturatie van de particuliere kassaverkopen" of manueel a.h.v. de kassastrook met de particuliere dagontvangsten. Deze factuur wordt afgeboekt (betaald) via de kasboeking hieronder. |
| Grootboekfiche **Bancontact** (voorbeeld: 598020) | Dagelijks wordt het totaal Bancontact hierop geboekt; bij het inboeken van de bankuittreksels wordt het weer afgeboekt vanuit de bank. Het saldo = het bedrag dat nog onderweg is. |
| Grootboekfiche **Proton** (voorbeeld: 598030) | Zelfde principe (Proton bestaat niet meer; historisch). |
| Grootboekfiche **Visa/kredietkaart** (voorbeeld: 598040) | Zelfde principe voor kredietkaarten. |

De rekeningnummers zijn voorbeelden uit de handleiding; de werkelijke nummers hangen af van het rekeningplan van de klant.

### 2.2 Instelling van de kassa: de juiste tickets

De kassa moet zo ingesteld zijn dat 's avonds de nodige totalen afgedrukt worden:

1. Ga naar "Menu Beheer KeyConen kassa".
2. Druk op `F9` Controle.
3. Druk op "Selectie der verkopen" tot er **"Apart en totaal"** verschijnt.
4. Druk op "Neem deze als standaard".

Bij het afdrukken van het kasverslag op de kassa komen er dan **3 tickets**:
1. het totaal van de **particuliere verkopen**;
2. het totaal van de verkopen die **per klant gefactureerd** moeten worden;
3. de **som** van beide (de totale verkoop van de kassa), met de totalen per betaalwijze.

### 2.3 De kasboeking stap voor stap

1. Hoofdmenu boekhouding, punt **2**. Kies het **kasjournaal** (in het voorbeeld van de handleiding journaal 17; het nummer verschilt per klant - kijk in de journalenlijst op het scherm of in `+.3`). Zet de datum juist.
2. Geef als **ingekomen bedrag** het totaal **GELD** van het 3de kasticket (= totaal cash ontvangen). Druk `F8`.
3. Geef het totaal **VERKOCHT** van het **eerste ticket** (particuliere verkopen) in en boek dit op de klant **KASSAVERKOPEN** (type K).
4. Geef het bedrag in van elk **VOLDAAN** kasticket dat gefactureerd moet worden en boek het op de **respectievelijke klant**. Herhaal voor ALLE voldane tickets die gefactureerd worden.
5. Bij "Nog te verdelen" bovenaan staat nu (negatief) het totaal van Bancontact/Proton/Visa.
6. Geef het totaal **BANCONTACT** van ticket 3 **negatief** in en boek het op de grootboekrekening Bancontact (type G).
7. Idem **PROTON** negatief op de juiste grootboekrekening.
8. Idem **VISA** negatief op de juiste grootboekrekening.
9. Als alles juist is, is er geen verschil meer ("Nog te verdelen" = 0) en kan de boeking geboekt worden (`F8`).

Waarom negatief: bij type G komt een negatief bedrag aan de debetzijde van de grootboekrekening; de elektronische betalingen staan dus als vordering op de wachtrekening tot de bank ze stort.

### 2.4 Opmerkingen

- Bij het inboeken van de **bankuittreksels** moeten de gestorte bedragen Bancontact/kredietkaart op hun respectievelijke wachtrekening geboekt worden; zo loopt het saldo daar weer naar nul.
- **Boek het kasjournaal best NADAT alle facturen gemaakt zijn** (de kasfactuur op "Kassaverkopen" en de individuele klantfacturen). Dan kan elke betaling direct aan haar factuur toegewezen worden.
- Zijn de facturen nog niet gemaakt, dan boekt u de bedragen als **voorschot** (met `F9`) op de klantrekening en moet u achteraf de voorschotten aan de facturen koppelen: referenties juist zetten op de klantenrekening via punt 4. Dat is veel extra werk dat vermeden wordt door eerst te factureren.
- In de facturatieparameters (`+.4`) kan ingesteld worden dat **voldane facturen automatisch in het kasjournaal geboekt** worden (met het nummer van het kasjournaal). Is dat actief, let dan op dat dezelfde betaling niet nog eens manueel geboekt wordt (te verifieren per installatie).

### 2.5 Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Er blijft een verschil in "Nog te verdelen" | Een voldaan klantticket vergeten, een betaalwijze niet geboekt (bv. maaltijdcheques, cadeaubons), of een bedrag met verkeerd teken. Vergelijk met ticket 3. |
| Klantrekening "Kassaverkopen" toont veel losse voorschotten | Kasboekingen gebeurden voor de factuur gemaakt was. Referenties koppelen via punt 4; bij zeer lange rekeningen bestaat het hulpprogramma `+.D` (optie). |
| Saldo op de Bancontact-rekening blijft groeien | Stortingen van de bank worden bij het inboeken van de bankuittreksels niet op deze rekening geboekt, of kosten/commissies worden niet apart weggeboekt. |
| Er komen geen 3 tickets uit de kassa | "Selectie der verkopen" staat niet op "Apart en totaal" (zie 2.2). |

(Oorzaken afgeleid uit de beschreven werkwijze.)

## 3. Kasverslag afdrukken/inboeken (V.2.4)

### 3.1 Waarvoor

Het kasverslag centraliseert de verrichtingen van de KeyConen-kassa('s) (verkopen en betalingen) in één document. Het kan dienen als hulp/bijlage voor het **dagontvangstenboek** en kan desgewenst **direct geboekt** worden in de boekhouding.

Belangrijk:
- De berekening gebeurt op basis van het **echte verkopenbestand van de kassa** en heeft **geen verband met punt 3 "Inlezen verkopen"**. Kasverslag en "Inlezen verkopen" zijn twee verschillende verwerkingen (het inlezen verwerkt de verkopen voor stock/statistieken - uit opleiding, 11 juni 2026).
- De verkopen mogen dus **nog niet gewist** zijn op de kassa en moeten **doorgestuurd** zijn naar de hoofdcomputer (punt `N` dagelijkse transfert op de kassa).

### 3.2 Afdrukken

1. Ga naar punt **V.2.4**. (Controleer of versie/module van de klant overeenkomt voor u een menu aanwijst.)
2. Geef de **periode** in waarover het verslag moet gaan.
3. Controleer in de **tabel met de kassa('s)** of **datum en uur van het verkopenbestand** van de gewenste kassa in orde is. Zo niet: de verkopen opnieuw doorsturen vanaf de kassa (punt N).
4. Geef het gewenste **kassanummer** in (zie tabel) of laat leeg voor alle kassa's samen.
5. Wilt u het **geld (cheques) dat naar de bank gebracht is** in het verslag opnemen, vul dat bedrag dan in.
6. Druk **`F8`** om het verslag af te drukken. **Let op: als het boeken geactiveerd is in de parameters, volgt het boeken onmiddellijk na het afdrukken** (zie 3.4).

### 3.3 Inhoud van het verslag

| Rubriek | Inhoud |
|---|---|
| Contante verkopen | Verkopen aan particuliere klanten, uitgesplitst volgens BTW. |
| Voldane bons/facturen | Voldane verkopen waarvan individueel een factuur gemaakt is (of wordt) op de betreffende klant. Niet uitgesplitst volgens BTW (dat gebeurt bij het maken van de factuur). |
| NIET voldane bons/facturen | Niet-voldane verkopen waarvan individueel een factuur gemaakt is (of wordt). Niet uitgesplitst volgens BTW. |
| Storting bank | Het bedrag dat naar de bank gebracht is (indien ingevuld). |
| **Totaal bewegingen** | Totaal van de rubrieken hierboven. |
| Opsomming betaalmiddelen | Alle gebruikte betaalmiddelen. |
| **Totaal ontvangsten** | Totaal van de betaalmiddelen. |

**"Totaal bewegingen" en "Totaal ontvangsten" moeten gelijk zijn.**

Betaalcodes op het verslag:

| Code | Betekenis |
|---|---|
| GE | Geld |
| BC | Bancontact |
| MC | Maaltijdcheques |
| ET | Eigen tegoedbon |
| LB | Leveranciersbon |
| CC | Creditcard |
| MO | Mobiel |
| CU | Cadeaubon uitgegeven |
| CO | Cadeaubon ontvangen |
| V1 - V3 | Variabele betaalwijze 1-3 |
| NB | Niet betaald |

### 3.4 Inboeken in de boekhouding

Met de boekhoudmodule kan het kasverslag direct ingeboekt worden; dit gebeurt **onmiddellijk na het afdrukken**. Het verslag wordt geboekt in een **kasjournaal**:
- de **contante verkopen** op de juiste omzetrekeningen;
- de klanten met **voldane facturen/bons** worden afgeboekt;
- de diverse **betaalmiddelen** op hun respectievelijke rekening.

**Parameters** (activeren van het boeken): op het scherm van V.2.4 rechtsonder op de **groene `+`** drukken.

| Parameter | Uitleg |
|---|---|
| Boekscherm tonen na afdrukken | Aangevinkt: de boeking wordt eerst **getoond** voor er geboekt wordt. Best aanvinken. Dit vinkje schakelt het boeken **niet** uit; het voegt enkel een controlescherm toe. |
| Kasjournaal (per kassa) | Elke kassa kan in een ander kasjournaal geboekt worden. **Niets ingevuld = deze kassa wordt niet geboekt.** |
| Rekening fondsoverdracht | Grootboekrekening die gebruikt wordt wanneer geld naar de bank gebracht wordt ("storting bank"). |
| Grootboekrekening per betaalmiddel | Voor elk mogelijk betaalmiddel (GE, BC, MC, ...) de juiste grootboekrekening. |

### 3.5 Grenzen en voorzichtigheid (belangrijk voor support)

- **F8 in V.2.4 = afdrukken en mogelijk boeken.** Dit is niet hetzelfde als F8 in het rekeningoverzicht (punt B.4), waar F8 enkel "zoek op" is.
- De bronnen bewijzen **niet** dat het systeem een tweede boeking van hetzelfde kasverslag tegenhoudt, en ook niet dat het dat niet doet. Beloof dus geen automatische blokkade tegen dubbel boeken, maar beweer ook niet dat ze ontbreekt. Bij twijfel of een verslag al geboekt is: **eerst kijken, niet opnieuw afdrukken/boeken**.
- Laat bij onbekende parameters geen "proef" met F8 of PDF doen en wis geen parameters; bekijk enkel de bestaande parameters.
- **Nagaan of een kasverslag al geboekt is (leesroute, niets wijzigen)**:
  1. Punt B.4 (rekeningoverzicht): kies het juiste type (G voor de kas- of omzetrekening, K voor een klant), de rekening en de periode; `F8` = zoek op.
  2. Kijk naar de kolommen journaal, volgnummer, boekdatum en referentie; `F5` toont het detail van een geboekte lijn.
  3. Of druk het betrokken kasjournaal af voor de periode (B.5.1).
  4. Eén gevonden lijn (bv. één klantbetaling van gisteren) bewijst niet dat het hele kasverslag geboekt is; vergelijk het volledige stuk (journaal + volgnummer + datum) met het verslag.
- Bij een onvolledig verslag: eerst **periode, kassa en tijdstip van het verkopenbestand** vaststellen. Niet als eerste reactie opnieuw laten inlezen/transfereren en niets wissen op de kassa.
- Een fout geboekt kasverslag corrigeren (schrappen via punt `U`, opnieuw boeken) is een boekhoudkundige ingreep: laten beoordelen door een ervaren medewerker.

### 3.6 Kassabedragen controleren (praktijk)

Bevestigde praktijk (HUMAN-Q015): het contante geld tellen, de ontvangsten vergelijken met het kassarapport/kasverslag, en de kaartbetalingen vergelijken met het rapport van de betaalterminal. Dit bewijst nog geen volledige afstemming met bank of grootboek. Bij een kasverschil: vaststellen of het bij cash, kaart of beide zit; niet opnieuw afrekenen om te testen en niet boeken of wissen om een verschil weg te werken.

Foute kassaverkopen of retouren worden behandeld via een correctie in de kassa, een retourbon of een creditnota (HUMAN-Q014); welke fiscaal juist is, hangt af van het type verrichting.

### 3.7 Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Verslag is leeg of onvolledig | Verkopen van de kassa zijn niet (recent) doorgestuurd: controleer datum/uur van het verkopenbestand in de tabel en laat punt N (dagelijkse transfert) op de kassa uitvoeren. Of de verkopen zijn al gewist op de kassa. Of verkeerde periode/kassanummer. |
| "Totaal bewegingen" is niet gelijk aan "Totaal ontvangsten" | Zou gelijk moeten zijn; nakijken of "storting bank" correct ingevuld is en of alle kassa's/periodes volledig zijn. Verdere oorzaak niet beschreven in de bron: escaleren. |
| Er wordt niets geboekt na het afdrukken | Geen kasjournaal ingevuld voor deze kassa in de parameters (groene `+`), of geen boekhoudmodule. |
| Een betaalmiddel komt op een verkeerde of geen rekening | Grootboekrekening voor dat betaalmiddel niet (juist) ingevuld in de parameters. |
| Kasverslag komt niet overeen met de stock/statistieken | Dat zijn gegevens van "Inlezen verkopen" (punt 3), een aparte verwerking. |
| Klant vraagt of het verslag "veilig" opnieuw afgedrukt kan worden | Enkel als zeker is dat boeken niet actief is voor die kassa of als het boekscherm getoond wordt en geannuleerd kan worden; anders eerst nagaan of er al geboekt is (3.5). |

(Oorzaken deels afgeleid uit de parameters en voorwaarden in de handleiding.)

## Bronnen

- `Hoe het kasjournaal inboeken.docx` (map kassa).
- `0290B - Kasverslag.docx` (map Jamadrink/Handleidingen modules).
- `00_CHECKPOINT_KASVERSLAG.md` (00_START_CLAUDE/15_KASVERSLAG) - enkel de inhoudelijke grenzen: geen bewezen blokkade tegen dubbel boeken, betekenis van "Boekscherm tonen na afdrukken", journaal 17 is geen universele instelling, opleiding van 11 juni 2026 over het verschil met "Inlezen verkopen".
- `00_CHECKPOINT_BOEKING_LEESROUTE.md` (00_START_CLAUDE/16_BOEKING_LEESROUTE) - leesroute via het rekeningoverzicht (punt 4).
- `06_GERICHTE_HANDLEIDINGCONTROLES.md`, `01_EXPERTANTWOORDEN_45.md` (HUMAN-Q013, Q014, Q015) en `03_JUNIOR_PRAKTIJKKAARTEN.md` (J04) (00_START_CLAUDE/01_NAAR_CLAUDE).
- `Gebruikerhandleiding BOEKHOUDPAKKET.docx` (map boekhouding) - `+.4` (voldane facturen automatisch in kasjournaal), punt 2.1 (teken bij type G).
