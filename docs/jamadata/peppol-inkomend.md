# Peppol: inkomende (aankoop)facturen verwerken

Gebruik dit document voor: vragen over het ophalen en verwerken van inkomende Peppol-facturen van leveranciers in Jamadata: enkel boekhoudkundig inboeken (kostenfacturen), of via het voorraadbeheer (goederenfacturen met stock, prijzen en statistieken), het koppelen van leveranciers en artikels, de keuze van de grootboekrekening, en het verschil tussen de drie handleidingvarianten 0033A, 0211C en 0255C.

## 1. Waarvoor dient de module

Een Peppol-factuur bevat naast de pdf ook alle factuurgegevens in gestructureerde vorm (XML/UBL). Jamadata haalt deze facturen af van het Peppol-netwerk en laat toe ze (semi)automatisch in te boeken in de boekhouding en/of te verwerken in het voorraadbeheer. Je hoeft geen bedragen, referenties of vervaldagen meer in te tikken.

Twee soorten facturen:

- **Kostenfactuur** (elektriciteit, brandstof, boekhouder, leasing ...): enkel boekhoudkundig verwerken.
- **Goederenfactuur** (aankoopartikels): kan bijkomend de stock bijwerken, prijzen vergelijken/aanpassen en aankoopstatistieken bijwerken.

Wie de factuur verwerkt, kiest zelf per factuur of ze via de boekhouding of via het voorraadbeheer gaat; dat wordt niet vooraf vastgelegd.

## 2. Welke handleiding geldt voor welke installatie (0033A / 0211C / 0255C)

De drie handleidingen heten alle drie "Verwerken van inkomende peppol" en zijn tot en met het boekhoudkundig inboeken identiek. Het verschil zit in het deel voorraadbeheer:

| Handleiding | Voor welke installatie | Menupunt | Wat is anders |
|---|---|---|---|
| **0033A** | Enkel **boekhouding** (geen verwerking via voorraadbeheer) | **B.1** | Alleen F9 (boek volgens btw%) en F10 (boek in detail). Geen artikelkoppeling, geen F8. |
| **0211C** | Boekhouding + voorraad met **standaard aankoopbeheer** (leveringen rechtstreeks ingeven) | **B.1** en **V.1** | F8 "boek via artikels" brengt je rechtstreeks in het **leveringen-scherm**, waar alle artikels met aantallen en eenheidsprijzen al ingevuld zijn. Niet-gekoppelde artikels kan je nog "in de volgende stap" koppelen. |
| **0255C** | Boekhouding + voorraad met **uitgebreid aankoopbeheer** (bestelbons → geleverde bons → factuur) | **B.1** en **V.1** | F8 "boek via artikels" vraagt eerst over welke **geleverde bons** de factuur gaat (of **F9 nieuwe bon**). Niet-gekoppelde artikels kan je nog koppelen "op de bestelbon zelf". Bevat ook de prijsvergelijking met de aankoopfiche en de logica voor de aankooprekening. |

Toelichting bij deze indeling: de handleidingen zeggen zelf alleen "B.1 (= enkel boekhouding)" resp. "B.1 en V.1 (boekhouding + voorraad)". Dat 0211 bij het standaard aankoopbeheer hoort en 0255 bij het uitgebreid aankoopbeheer is afgeleid uit de nummering van de zustermodules (0211A/B "Uitschrijven bestellingen ..." tegenover 0255A/B "... met uitgebreid aankoopbeheer") en uit de inhoud (leveringen-scherm tegenover geleverde bons). Niet letterlijk zo in de bron vermeld.

Van 0033A en 0255C bestaan ook `_old`-versies ("Verwerken inkomende peppol-facturen_old"); die zijn vervangen door de versies hierboven.

## 3. Waar zit het

- **Boekhouding**: boekhoudmenu **B → 1**, daarna **P** (Peppol) voor de lijst met inkomende Peppol-facturen. Hier zit niets van voorraadbeheer in. (Menupunt B.1 uit de handleiding; de toets P uit opleiding, 03-07-2025.)
- **Voorraadbeheer**: **V → 1** (bestellingen aan leveranciers), daar het punt **Peppol-facturen** (in de opleiding van 03-07-2025 getoond als **punt 8**; nummer te verifiëren op de installatie). Hier kan je zowel boekhoudkundig boeken (F9/F10) als via artikels (F8).

Bij het starten van het programma wordt automatisch verbinding gemaakt met het Peppol-netwerk en worden nieuwe facturen meteen gedownload.

## 4. Het overzichtsscherm

Je krijgt de lijst van alle **nog te verwerken** facturen.

- **Groene knop** naast een factuur: factuur openen om te verwerken.
- **Pdf-knop** naast een factuur: het originele document bekijken/afdrukken. Het pdf-icoon staat er altijd; zit er geen pdf in het Peppol-bestand, dan gebeurt er niets als je erop klikt (uit opleiding, 03-07-2025).
- **Groene downloadknop rechtsonder**: opnieuw controleren op nieuwe facturen.
- **– icoon rechts onderaan** in het scherm "Overzicht factuur": **"Schrap deze factuur"** om een factuur die al manueel geboekt is definitief uit de lijst te verwijderen. In hetzelfde scherm kan je ook het Peppol-bestand downloaden.

## 5. Een factuur openen

Eerst wordt de inhoud (de lijnen) van de factuur getoond.

**F7 – Toon factuurtotalen**: overzicht van de factuur per btw% (met factuurdatum, vervaldatum, referentie/betalingsmededeling).

- **Groen vergrootglas** bij een btw%: toont de lijnen die onder dat btw% vallen.
- **Koppelicoon** bij een btw%: voor **deze leverancier en deze btw-categorie** een andere grootboekrekening koppelen dan de standaardrekening. Eén keer instellen; de volgende keer is dit gekend. (Voorbeeld uit de opleiding: bij een leverancier van sterke drank de 21% koppelen aan "aankoop sterke dranken"; bij een waterleverancier de 6% aan "aankoop water".)

### Leverancier koppelen (eenmalig)

1. Klik op het **groene koppelicoon** naast de leverancier.
2. Kies via het **vergrootglas** de bestaande leverancier in Jamadata.
3. Bestaat de leverancier nog niet: druk **F10 – nieuwe leverancier**. Je komt in een leveranciersfiche waar alle gegevens uit de Peppol-factuur (adres, btw-nummer, rekeningnummer, e-mail ...) al ingevuld zijn; je kan meteen wegschrijven (F8).

De volgende keer wordt de juiste leverancier automatisch getoond.

## 6. Boekhoudkundig inboeken (alle varianten)

Twee methodes:

### F9 – Boek bkh btw%

Er wordt enkel opgesplitst per btw%. De rekening wordt zo bepaald:

1. Heeft de leverancier een **standaard grootboekrekening** (via **F9 op de leveranciersfiche**)? Dan gaat alles op die rekening.
2. Zo niet: is er voor deze leverancier een **afwijkende rekening gekoppeld aan dit btw%** (zie koppelicoon bij F7)? Dan wordt die gebruikt.
3. Zo niet: de **standaardrekeningen uit de parameters** (per btw-percentage 0/6/12/21 kan in de parameters een aankooprekening ingesteld worden).

Tip voor terugkerende kostenfacturen: vul bij de eerste boeking de juiste kostenrekening in en kies dan **F10 – Maak GRB standaard** (bevestigen met F4). Vanaf dan wordt die rekening voor deze leverancier automatisch voorgesteld en volstaat F8 om te boeken.

### F10 – Boek bkh-detail

Elke factuurlijn wordt apart geboekt (op dezelfde of een andere rekening), met de omschrijving van de lijn als opmerking. Handig als je in de boekhouding het detail wil terugvinden, bv. leasingfacturen per fiets of kilometerheffing per vrachtwagen.

### Na het boeken

- Het boekscherm is volledig ingevuld (opmerking, betalingsmededeling, vervaldag); in principe enkel nog **F8**.
- Werk je met **twee aankoopdagboeken**: het systeem vraagt vóór het boeken in welk dagboek je wil boeken en neemt het volgende factuurnummer van dat dagboek.
- De Peppol-factuur wordt verplaatst naar de map **"kopie facturen"**, zodat ze mee geback-upt wordt, en verdwijnt uit de lijst "nog te verwerken facturen".
- De factuur blijft opvraagbaar via de **leveranciersrekening in de boekhouding (B.4)**: klik op het **pdf-icoon** bij de factuur.
- Btw **medecontractant**: boeken blijft identiek aan de bestaande werkwijze.
- Bij boeken via de boekhouding kan binnen 6% geen onderscheid gemaakt worden (bv. voeding/dranken): alles komt op dezelfde 6%-rekening. Wil je dat onderscheid, werk dan via het voorraadbeheer met een aankooprekening per artikel.

### Enkel de pdf bewaren, zonder boeking (klanten zonder Jamadata-boekhouding)

Alleen voor klanten **zonder Jamadata Account (boekhoudpakket)**: kies bij het verwerken **"F10 – Boek factuur"**. Dan gebeurt er geen boeking, geen stockverwerking en geen prijsverwerking; de pdf wordt geopend en automatisch opgeslagen in het Jamadrink-pakket. Later opnieuw raadplegen via **V.8.H.P.1**.

## 7. Goederenfactuur verwerken via het voorraadbeheer (0211C en 0255C)

### Artikels koppelen (eenmalig per leverancier/artikel)

1. Klik bij een factuurlijn op het koppelicoon. Je krijgt een lijst van artikels; het programma zoekt al op het eerste woord van de omschrijving.
2. Druk op de **groene knop** bij het juiste Jamadata-artikel.
3. Bestaat er nog geen **aankoopfiche** voor dit artikel bij deze leverancier, dan wordt gevraagd die aan te maken. In die aankoopfiche (**F2 op de artikelfiche**) wordt het **artikelnummer van de leverancier** bewaard.
4. In de lijst staan **grijze** artikels = al gekoppeld bij deze leverancier (niet opnieuw kiezen); **groene** = nog beschikbaar. (Uit opleiding, 03-07-2025.)

Ook het leeggoed moet gekoppeld worden. Bij een volgende factuur zijn de koppelingen gekend. Een artikel dat je nu niet koppelt, kan je nog koppelen in de volgende stap (0211C) of op de bestelbon zelf (0255C).

**Verkeerd gekoppeld?** Open de aankoopfiche (F2) op de artikelfiche en pas bij de juiste leverancier het veld met het artikelnummer van de leverancier aan of maak het leeg.

**Leverancier geeft geen artikelnummer mee in het Peppol-bestand**: dan kan Jamadata het artikel niet blijvend koppelen; je moet het bij elke factuur opnieuw aanduiden. Het nummer staat soms wel op de pdf maar niet in de XML. Dit kan enkel de leverancier oplossen: de klant moet zijn leverancier vragen de artikelnummers in het Peppol-bestand mee te geven. Idem als een leverancier in de XML maar één samenvattende lijn zet terwijl de pdf meerdere lijnen heeft. (Uit opleiding, 03-07-2025.)

### F8 – Boek via artikels

Zodra de koppelingen in orde zijn, druk **F8 boek via artikels**. Daarna volgen dezelfde schermen als bij het manueel inboeken van een aankoopfactuur, maar volledig vooraf ingevuld.

**Variant 0255C (uitgebreid aankoopbeheer):**

1. Het programma vraagt over welke **"geleverde bons"** de factuur gaat. Duid één of meerdere bons aan (een factuur kan over meerdere bons gaan), of kies **F9 – nieuwe bon** als het een rechtstreekse factuur is zonder voorafgaande bestelbon.
2. De aantallen en eenheidsprijzen worden overgenomen **van de factuur**. Artikels die wel op de geleverde bon staan maar niet op de factuur, krijgen aantal 0 (de bon wordt dus gecorrigeerd naar wat gefactureerd is). (Uit opleiding, 03-07-2025.)
3. Pas je aantallen aan en komt het totaal van je detail niet meer overeen met het totaal van de Peppol-factuur, dan krijg je een melding met het verschil. Je kan teruggaan of toch doorgaan; het boekscherm houdt het totaal van de Peppol-factuur aan en je moet het verschil dan zelf rechtzetten. De boeking moet exact overeenkomen met de factuur.
4. **Prijsverschil**: wijkt de eenheidsprijs af van de laatste aankoopprijs bij deze leverancier (aankoopfiche), dan krijg je een scherm met de keuzes: niet aanpassen (bv. eenmalige promo), enkel de prijs op de aankoopfiche van deze leverancier aanpassen, of de aankoopprijs van het artikel aanpassen. Bij een prijsverschil worden twee lijnen getoond om duidelijk te maken dat de bestelprijs afwijkt van de factuurprijs. Prijzen van artikels die nog nooit bij deze leverancier gekocht zijn, staan in een afwijkende kleur.
5. Het boekscherm is volledig ingevuld. Daarna worden de statistieken bijgewerkt. Was er geen bestelbon (nieuwe bon), dan wordt ook de **stock** bijgewerkt (bij een geleverde bon was de stock al bijgewerkt bij de levering).

**Variant 0211C (standaard aankoopbeheer):**

1. Na F8 kom je in het **leveringen-scherm** waar alle artikels al ingevuld zijn met de juiste aantallen en eenheidsprijzen.
2. De verdere verwerking verloopt zoals je het manueel zou doen.

### Op welke rekening wordt geboekt bij verwerking via artikels

1. Bestaat op de **artikelfiche** het veld **"aankooprekening"** en is het ingevuld? Dan heeft dat altijd voorrang (gebruikt om aankopen per categorie uit te splitsen: vaten, bakken, speciale bieren, frisdranken ...).
2. Zo niet: heeft de leverancier een afwijkende rekening gekoppeld aan dit btw%? (zo in handleiding 0255C)
3. Zo niet: de standaardrekening uit de parameters.

Opmerking: in de opleiding van 03-07-2025 wordt gezegd dat de koppeling leverancier/btw-categorie enkel bij het boeken via de boekhouding (F9/F10) meespeelt en dat via de voorraad enkel artikelfiche → standaardrekening geldt. Dit is tegenstrijdig met de handleiding 0255C; onzeker / te verifiëren.

### Na het verwerken

Zoals bij de boekhouding: de Peppol-factuur gaat naar de map "kopie facturen", verdwijnt uit de lijst en blijft opvraagbaar via het pdf-icoon op de leveranciersrekening (B.4).

## 8. Samenhang met de bestaande aankoopflow

- De bestel- en leveringsprocedure blijft dezelfde (bestelbon maken manueel, via bestelvoorstel of met PDA; leveren van bestelde goederen via V.1 punt 5 met F8/F8). Het verwerken van de Peppol-factuur vervangt enkel het manueel inboeken van de aankoopfactuur.
- Aankoopfacturen afdrukken en manueel inboeken kan nog steeds.
- Het afpunten/betalen van leveranciersfacturen (o.a. via SEPA-betaalopdrachten) blijft ongewijzigd.
- Wil de boekhouding controleren of een factuur die ook per mail/post binnenkwam al ingeboekt is: zie `peppol-faq-en-problemen.md`.

## 9. Wat nooit via Peppol binnenkomt

- Facturen van leveranciers zonder btw- of ondernemingsnummer (bepaalde verenigingen).
- Kasstukken, kassabonnen, ticket van een aangetekende zending e.d.

Deze blijven op papier/mail komen en moeten manueel ingeboekt worden zoals voorheen.

## Bronnen

- `0033A - Verwerken van inkomende peppol.docx` (Jamadrink en Jamadrink/Handleidingen modules)
- `0211C - Verwerken van inkomende peppol.docx` (Jamadrink/Handleidingen modules)
- `0255C - Verwerken van inkomende peppol.docx` (Jamadrink en Jamadrink/Handleidingen modules)
- `Jamadata Peppol FAQ.docx` (Jamadrink)
- Transcriptie opleiding `Peppol_20250703_090232.txt` (demo inkomende Peppol, 03-07-2025)
