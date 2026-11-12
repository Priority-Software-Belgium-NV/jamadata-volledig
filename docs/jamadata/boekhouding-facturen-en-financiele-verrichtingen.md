# Boekhouding in Jamadata: facturen inboeken, financiele en diverse verrichtingen, schrappen, openingsbalans en rekeningoverzicht

Gebruik dit document voor: vragen over het manueel inboeken van inkomende en uitgaande facturen en creditnota's (punt B.1), intracommunautaire en medecontractant-facturen, het inboeken van bank-, kas- en diverse uittreksels (punt B.2), het toewijzen van betalingen aan facturen en voorschotten, het afboeken van klantfacturen via een lijst (B.2.2), het schrappen van boekingen (verborgen punt U), de openingsbalans (F10, journaal 99), het rekeningoverzicht van klant/leverancier/grootboek (punt B.4) en het corrigeren van referenties. Ook de facturatie vanuit het boekhoudpakket (punt 8) is kort opgenomen.

Verwante documenten: `boekhouding-basis-en-dagboeken.md` (schermbediening, fiches, journalen), `boekhouding-coda-en-betalingen.md` (CODA, SEPA-betaalopdrachten en domicilieringen), `boekhouding-kasjournaal-en-kasverslag.md`, `boekhouding-archivering-en-foutenlijst.md`.

## 1. Algemene regels bij het boeken

- Er mag in elke periode geboekt worden die nog niet gearchiveerd is, ook al in het volgende boekjaar terwijl het vorige nog niet afgesloten is.
- Boeken in een gearchiveerde periode is onmogelijk (fout 37). Een boekdatum meer dan 500 dagen na de laatste archivering wordt geweigerd (fout 61).
- Per stuk moet debet = credit (fout 10).
- De **boekdatum** bepaalt in welke boekhoudperiode het stuk valt. De computer stelt de systeemdatum van het pakket voor (aan te passen per stuk of via `+.7`).

## 2. Punt 1 - Inbrengen facturen

| Punt | Functie |
|---|---|
| 1.1 | Inkomende facturen |
| 1.2 | Inkomende creditnota's |
| 1.3 | Facturen/creditnota's intracommunautair of medecontractant (1.3.1 facturen, 1.3.2 creditnota's) |
| 1.4 | Uitgaande facturen |
| 1.5 | Uitgaande creditnota's |
| U (verborgen, op het menu van punt 1) | Geboekte factuur opnieuw oproepen; met `F9` kunnen daar de Intrastat-gegevens aangepast worden (zie `boekhouding-btw-listing-ic-intrastat.md`) |

### 2.1 Inkomende facturen (1.1) - velden

| Veld | Uitleg |
|---|---|
| Journaalnummer | Automatisch het eerste aankoopjournaal uit de systeemparameters (`+.3`). |
| Factuurnummer | Automatische volgnummering binnen het journaal; aanpasbaar. Het ingegeven nummer wordt onthouden als laatst gebruikte stuknummer. Twee facturen onder hetzelfde nummer kan niet (fout 59). |
| Boekdatum | De cursor staat bij het openen op dit veld. Zie algemene regels. |
| Leverancier | Nummer of beginletters van de naam. |
| Opmerking | Vrije tekst; later zichtbaar op het rekeningoverzicht van de leverancier. |
| Mededeling | Mededeling bij betaling; wordt op overschrijvingslijsten/betaalopdrachten meegegeven. |
| Factuurdatum | Datum op de factuur van de leverancier. Niet ingevuld = boekdatum. Dient om de vervaldatum te berekenen. |
| Vervaldatum | Leeg laten = berekend uit factuurdatum + betalingstermijn op de leveranciersfiche. |
| Disconto bedrag / vervaldatum disconto | Leeg laten = berekend uit het disconto-% en de termijn op de leveranciersfiche. |
| Totaalbedrag (incl. BTW) | Het bedrag dat aan de leverancier betaald moet worden. Bij medecontractant of intracommunautair: enkel het effectief te betalen bedrag (zonder de verlegde BTW). |
| Munt | Enkel zichtbaar als met wisselkoersen gewerkt wordt; `EUR` vervangen door de afkorting van de vreemde munt (moet bestaan in punt 7). |
| Aftrekbare BTW | Bedrag aftrekbare BTW. |
| Niet aftrekbare BTW | Bv. bij aankoop van wagens. |
| BTW EU/medecontractant | Bedrag + de grootboekrekening (nummer of naam) waarop deze verlegde BTW geboekt wordt. |
| Uitsplitsing | Per lijn: bedrag (excl. BTW), grootboekrekening (nummer of beginletters), opmerking (komt op de grootboekfiche). Max. 10 uitsplitsingen per factuur. |

Bijzonderheden:
- **Standaard GRB**: de tot 10 rekeningen die via `F9` op de leveranciersfiche vastgelegd zijn, verschijnen automatisch; enkel de bedragen invullen.
- **Korting op factuur**: negatief bedrag op de rekening "bekomen korting".
- **Kostenplaatsen (analytisch)**: tik op het einde van de uitsplitsingslijn een `x`; de computer toont een scherm om het bedrag over kostenplaatsen te verdelen (een standaardverdeling op de rekening wordt voorgesteld). Zie fouten 67-70.
- **Controle**: Totaalbedrag + verlegde BTW = aftrekbare BTW + niet-aftrekbare BTW + som van de uitsplitsing. Klopt dit niet, dan wordt de boeking geweigerd met een melding onderaan.

Functietoetsen: `F8` boek, `F1` stop, `F2`/`F3` vorig/volgend scherm, `F6` annuleer, `F7` herdisplay (namen opzoeken).

### 2.2 Inkomende creditnota's (1.2)

Zelfde werking als 1.1 op een eigen scherm. Creditnota's komen op hetzelfde aankoopjournaal en de nummering loopt door. **Alle bedragen positief ingeven** (fout 80 bij negatief); de computer plaatst ze zelf op de juiste zijde. Wie een creditnota liever als negatieve factuur ingeeft, gebruikt het factuurscherm (1.1).

### 2.3 Intracommunautaire en medecontractant-stukken (1.3)

Het programma herkent deze stukken aan de gebruikte BTW-rekening: de rekening "BTW EEG" met **vak 86** = intracommunautair; de rekening "BTW medecontractant" met **vak 87** = medecontractant. Op basis daarvan worden ze speciaal uitgesplitst in de BTW-aangifte.

**Factuur (1.3.1)**: zelf de BTW berekenen en boeken enerzijds op "Aftrekbare BTW" en anderzijds op "BTW EEG" (vak 86) of "BTW medecontractant" (vak 87). Goederen/kosten op een rekening met vak 81, 82 of 83.

Voorbeeld: goederenfactuur van 100 EUR uit Nederland:
- 100 EUR totaal factuur
- 21 EUR aftrekbare BTW
- 21 EUR BTW EEG
- 100 EUR aankoop goederen (vak 81)

**Creditnota (1.3.2)**: GEEN BTW rekenen. Om het programma te laten weten dat het een speciale creditnota is: boek **+1 EUR en -1 EUR** op de rekening BTW EEG/medecontractant (nuloperatie).

Voorbeeld: creditnota van 100 EUR van een aannemer:
- 100 EUR totaalbedrag creditnota
- +1 EUR BTW medecontractant
- -1 EUR BTW medecontractant
- 100 EUR investeringen (vak 83)

### 2.4 Uitgaande facturen en creditnota's (1.4 en 1.5)

Zelfde principe als 1.1/1.2, maar op het verkoopjournaal, met "Te betalen BTW" in plaats van aftrekbare BTW. Niet-aftrekbare BTW en BTW EU/medecontractant zijn hier niet van toepassing. Creditnota's (1.5): positieve bedragen ingeven. Als in `+.3` de controle van het BTW-bedrag aanstaat, wordt het BTW-bedrag gecontroleerd tegen de BTW-vakken van de gebruikte rekeningen (fout 58).

Normaal worden verkoopfacturen niet hier maar automatisch vanuit de facturatie geboekt; 1.4/1.5 dient voor manuele verkoopboekingen.

### 2.5 Dubbele facturen

Het pakket herkent een dubbel ingevoerde factuur aan het factuurnummer binnen journaal en jaar en weigert dan het opslaan (fout 59). Dit is geen absolute garantie tegen dubbele boekingen: dezelfde leveranciersfactuur onder een ander intern stuknummer wordt niet tegengehouden (expertbevestiging: herkenning via factuurnummer, afhankelijk van versie/factuurtype). Dubbel geboekte nummers verschijnen ook op de fouten- en controlelijst (B.5.1).

## 3. Punt 2 - Inbrengen financiele & diverse verrichtingen

Dient voor: betalingen van inkomende en uitgaande facturen, transfers tussen banken of tussen bank en kas, kasstukken, correctieboekingen en openingen. Alles wordt ingebracht per **uittreksel** op een **journaal**. Voor de kas en het diversenjournaal maakt men zelf "fictieve uittreksels" (bv. alle kasstukken van één dag op één genummerd blad; één uittreksel per reeks correctieboekingen) - zo is achteraf terug te vinden waarom iets geboekt werd.

| Punt | Functie |
|---|---|
| 2.1 | Manueel inbrengen financieel/diversen/openingsbalans |
| 2.2 | Afboeken openstaande klantfacturen via lijst facturen |
| 2.3 / 2.4 | Automatisch inboeken bankuittreksels (CODA) en OGM-verwerking - opties; het exacte menunummer verschilt per versie, zie `boekhouding-coda-en-betalingen.md` |
| U | Schrappen van boekhoudbewegingen (verborgen toets op het hoofdmenu) |
| F10 | Menu openingsbalans (op het scherm van punt 2 / 2.1) |

### 3.1 Uittreksel openen (2.1)

1. De computer toont alle journalen met hun nummer. Geef het journaalnummer in en druk `F8`.
2. Hoofding van het uittreksel:

| Veld | Uitleg |
|---|---|
| Journaal | Reeds ingevuld. |
| Uittrekselnummer | Vorig nummer + 1. Bij journalen met automatische dagnummering (type 4, 6, 10) niet invulbaar: het nummer is `MMDD` van de boekdatum. |
| Boekdatum | Datum van het uittreksel. |
| Saldo op boekdatum | Informatief. |
| Vorig saldo | (enkel financiele journalen) Eindsaldo van het vorige uittreksel, door de computer onthouden. Mag negatief zijn (`-`). |
| Nieuw saldo | Stand na alle verrichtingen; wordt het beginsaldo van het volgende uittreksel. |
| Ingekomen bedrag | Alternatief voor het nieuwe saldo: de netto wijziging (positief als het saldo stijgt, negatief als het daalt). **Geef ofwel het nieuwe saldo ofwel het ingekomen bedrag in, niet allebei.** |

Het "vorig saldo" is het onthouden eindsaldo van het vorige uittreksel, niet het boekhoudkundige saldo van de rekening. In theorie zijn beide gelijk; een verschil wijst op een foute opening of een vergeten uittreksel. Eenmalig corrigeren kan in dit scherm; structureel via `+.3` (kolom Saldo van het journaal).

Functietoetsen: `F1` stop, `F7` bereken boekhoudsaldo, `F8` naar het detailscherm, `F11` hoofdmenu.

### 3.2 Detaillijnen ingeven (2.1.1)

Bovenaan: "Totaal te verdelen", reeds verdeeld en "Nog te verdelen". Boeken kan normaal pas als "Nog te verdelen" = 0.

Per lijn:

| Veld | Uitleg |
|---|---|
| Bedrag | Met teken: `+` verhoogt het saldo van bank/kas, `-` verlaagt het. Betaling aan een leverancier = `-` (creditnota-terugbetaling = `+`). Betaling van een klant = `+`. |
| Type | `L` = leverancier, `K` = klant, `G` = grootboekrekening (transfers, kleine kasaankopen, bankkosten, correcties). |
| Naam/nr | Naam (beginletters) of nummer van de klant, leverancier of rekening. |
| Opmerking | Komt op het rekeningoverzicht. Max. 127 opmerkingen per uittreksel. |
| Referentie (bij L of K) | De factuur waarop de betaling slaat: **nummer** (factuurnummer in de boekhouding), **journaalnummer** (aankoop- of verkoopjournaal) en **jaartal** van de factuur. Bij type G leeg laten. |

Bevestig de lijn met `TAB`. De lijn verschijnt dan in het venster met achteraan `D` (debet) of `C` (credit).

**Let op bij type G**: een **negatief** bedrag komt aan de **debetzijde** van de grootboekrekening, een **positief** bedrag aan de **creditzijde** - het omgekeerde van wat men intuitief verwacht. Controleer de `D`/`C` achteraan de lijn.

**Automatische tegenboeking**: bij een bank- of kasjournaal maakt de computer zelf de boeking op de financiele rekening van het journaal; die krijgt lijnnummer 1 en telt mee voor het maximum.

**Maximum 100 boekingen per uittreksel** (fout 11). Een langer uittreksel opsplitsen in meerdere delen met **hetzelfde nummer en dezelfde boekdatum** (bv. 150 lijnen = 2 x 75). Een andere boekdatum voor het tweede deel is niet toegelaten en verschijnt op de foutenlijst.

### 3.3 Betaling toewijzen zonder de referentie te kennen (2.1.2)

1. Geef enkel bedrag, type en naam in en druk `TAB` (referentie leeg).
2. De computer toont de boekingen van die klant/leverancier. Niet-voldane facturen staan in een andere kleur; het lijnnummer van een factuur met exact het gezochte bedrag knippert. Bladeren met `F2`/`F3`.
3. Geef bij "Lijn" het lijnnummer van de factuur in.
   - "Voor deze lijn (of blanco)" leeg laten = het volledige factuurbedrag wordt toegewezen.
   - Een bedrag invullen = **voorschot op een bestaande factuur** (gedeeltelijke betaling).
4. `TAB`: het bedrag gaat af van "Nog te verdelen"; de rest kan aan andere facturen toegewezen worden (één betaling voor meerdere facturen).
5. Factuur nog niet geboekt? Met `F9` wordt het bedrag zonder referentie geboekt = **voorschot op een toekomstige factuur**. De referentie wordt later rechtgezet via het rekeningoverzicht (punt 4).
6. Bij `F1` (stop) met een restbedrag vraagt de computer waarop het **verschil** geboekt moet worden: voordelige/nadelige betalingsverschillen, betalingskorting, bankkosten of een andere grootboekrekening. Het verschil kan over meerdere posten verdeeld worden.

De zoektolerantie (bv. 1 EUR afwijking) en of in debet en credit tegelijk gezocht wordt, staat in `+.3` ("opzoeken van een bedrag in een financieel journaal").

### 3.4 Uittreksel wegboeken (2.1.3)

| Toets | Werking |
|---|---|
| F2 / F3 | Vorig / volgend |
| F4 | Boek zoals F8 maar **zonder controle debet = credit**. Enkel gebruiken als men precies weet wat men doet: "doet gewoonlijk meer kwaad dan goed". |
| F6 | Annuleer: dit uittreksel niet boeken |
| F7 / TAB | Herdisplay |
| F8 | Boek en klaar voor het volgende uittreksel |
| F9 | Overzicht van de lijnen: opmerkingen aanvullen/corrigeren, een foutieve lijn schrappen en opnieuw ingeven |
| F10 | Zoek een bedrag |

### 3.5 Afboeken openstaande klantfacturen via lijst (2.2)

Bedoeld voor wie geen volledige boekhouding voert maar enkel de klanten opvolgt (aankopen zitten niet in het pakket, dus volledige bankuittreksels ingeven is moeilijk). De computer overloopt de vervallen facturen, de gebruiker beslist welke betaald zijn, de facturen worden meteen afgeboekt op de klant en er wordt een betaallijst afgedrukt.

**Eenmalige instelling** (max. 3 banken/kassen):
1. `B.9.3.2`: maak grootboekrekening 5810 (of 58100, 581000, ...) "Betalingen bank"; eventueel 5811 en 5812 voor een tweede en derde bank/kas.
2. `+.3`, enkele keren `F8` tot het scherm met de journalen: voeg een lijn toe met Nr `35`, Type `7`, benaming "Betaling bank", Fin. reken. `5810`. Eventueel 36 en 37 voor de andere banken/kassen.

**Uitvoeren (B.2.2)**:

| Veld | Uitleg |
|---|---|
| Overschrijvingsdatum | Datum waarop de betaling geboekt wordt. |
| Vervallen facturen overlopen J/N + periode | Bij `J` toont de computer de onbetaalde facturen die in de periode vervallen. Begindatum best leeg laten zodat lang vervallen facturen ook getoond worden. |
| Discontofacturen overlopen J/N | Idem voor facturen met disconto. |
| Selectie te gebruiken bankrekening (1-3) | Langs welke rekening geboekt wordt. |
| Klanten afboeken in boekhouding J/N | Of de betaalde facturen effectief afgeboekt worden. |
| Selectie 1 klant | Leeg = alle klanten alfabetisch. |

Een lijst van de betalingen opnieuw afdrukken: druk het journaal (bv. 35) af. **Een geboekte lijst als geheel schrappen**: ga naar het rekeningoverzicht (B.4), roep een klant op die op de lijst staat, noteer journaal (35) en volgnummer van de betaling, en schrap de volledige boeking via punt `U`.

## 4. Punt U - Schrappen van boekhoudbewegingen

Oproepen: verborgen toets `U` op het hoofdmenu boekhouding. Schrapt **alle** boekingen van één stuknummer (factuur of uittreksel) in één keer, zodat debet/credit in evenwicht blijft. Daarna kan het stuk correct opnieuw ingegeven worden.

| Veld | Uitleg |
|---|---|
| Jaartal van de boekdatum | Stuknummers herbeginnen elk jaar; het jaartal maakt het stuk uniek. |
| Journaalnummer | Elk journaal kan: aankoop, verkoop, financieel, diversen, overschrijvingsjournaal. |
| Volgnummer | Factuurnummer, uittrekselnummer, of volgnummer van kas/diversen. Bij een overschrijvingsjournaal: te vinden op het rekeningoverzicht van een leverancier/klant die op de lijst stond. |
| Boekdatum (of blanco) | Blanco = alle boekingen met dat jaar/journaal/volgnummer. Met datum = enkel de boekingen met die boekdatum (nodig als twee stukken hetzelfde nummer kregen). |

Bevestigen: `F4`, en nogmaals `F4`.

Regels en valkuilen:
- Alleen stukken die volledig **na de laatste archiveringsdatum** vallen, kunnen geschrapt worden (fout 37). Staat één boeking van het stuknummer in een gearchiveerde periode, dan lukt het niet - tenzij via het veld boekdatum enkel het niet-gearchiveerde stuk geselecteerd wordt.
- Het schrappen van een factuur schrapt **niet** de betaling ervan. Moet die ook weg, schrap dan ook het uittreksel waarop de betaling staat.
- Een uittreksel schrappen verwijdert **alle** verrichtingen van dat uittreksel.
- Werd het **laatst ingeboekte stuk** geschrapt, pas dan in `+.3` het laatst gebruikte stuknummer en (bij financiele journalen) het eindsaldo van het journaal aan.
- **Verkoopfacturen die uit de facturatie komen** schrapt men best via het facturatiemenu `8.H.U` (Schrappen verkoopfacturen): daar kunnen ook statistieken en voorraad teruggezet worden.

## 5. Openingsbalans (punt 2, F10) - journaal 99

### 5.1 Waarom

Het pakket neemt **geen grootboeksaldi over** van het vorige boekjaar: elk boekjaar begint met een "propere lei". De beginsaldi moeten dus ingegeven worden (a.h.v. de eindbalans van de boekhouder). Zolang dat niet gebeurd is, kloppen lijsten zoals de grootboekbalans en het bankjournaal niet (bv. geen beginsaldo van de bank op 1/1).

### 5.2 Waar

Hoofdmenu boekhouding > punt `2` (Inbrengen financieel en diversen) > functietoets `F10` Menu openingsbalans. Kies indien gevraagd het juiste boekjaar. De openingsbalans komt in het vaste journaal **99**, met één boeking per boekjaar; dit journaal is enkel via dit programma toegankelijk. Het scherm toont het boekjaar waarvoor de balans geldt (met "Geen balans gevonden" als er nog geen is) en onderaan de datum tot wanneer gearchiveerd is.

### 5.3 Menukeuzes

| Nr | Keuze | Wanneer |
|---|---|---|
| 1 | Ingeven nieuwe openingsbalans a.h.v. eigen gegevens van vorig jaar | Enkel als er nog geen openingsbalans is EN er in dit boekjaar nog niet gearchiveerd is. De balans wordt automatisch opgebouwd uit de saldi van vorig boekjaar. Er blijft meestal een restsaldo = winst of verlies; dit boekt u onderaan de lijst op een rekening "winst/verlies" of op een wachtrekening. **Te boeken saldo negatief = winst (credit boeken); positief = verlies (debet boeken).** Dit is een voorlopige balans. |
| 2 | Ingeven nieuwe openingsbalans (bv. van boekhouder) | Als er nog geen balans is: alle rekeningen en bedragen zelf ingeven. |
| 3 | Aanpassen bestaande (voorlopige) openingsbalans | De periode waarin de balans staat, mag niet gearchiveerd zijn. Na wijziging de journalen en balansen opnieuw afdrukken. |
| 4 | Schrappen bestaande (voorlopige) openingsbalans | Nodig voor men de balans volledig opnieuw ingeeft. Periode mag niet gearchiveerd zijn. |
| 5 | Controleren openingsbalans met gegevens vorig boekjaar | Toont per centralisatie-/journaalrekening het saldo op 31/12 (= klanten-/leveranciersbalans), het bedrag dat op 1/1 geopend is en het huidige saldo. Start met `F8`. Er mag nog niet gearchiveerd zijn in het te controleren boekjaar. |

De balans kan aangepast of geschrapt worden **zolang de eerste periode van het boekjaar niet gearchiveerd is**.

### 5.4 Meest voorkomende fout: opening klanten/leveranciers klopt niet

Het bedrag dat op 1/1 geopend wordt op de centralisatierekening klanten of leveranciers komt niet overeen met het werkelijke totaal van de openstaande klanten/leveranciers. Twee mogelijke oorzaken:

1. Er zijn op het einde van vorig boekjaar klanten/leveranciers gecorrigeerd (dubieuze klanten, foute betalingen) op de **interne kopie** van het vorige jaar, maar niet in het huidige dossier. Oplossing: voer dezelfde correcties ook in het huidige dossier uit.
2. Het bedrag in de openingsbalans is fout. Oplossing: corrigeer de openingsbalans (keuze 3).

Corrigeer dit meteen, anders blijft er een verschil tussen de klanten-/leveranciersbalans en de grootboekbalans.

**Is het vorige boekjaar al volledig gearchiveerd** en ontbreken er correcties op klanten/leveranciers: boek de correctie in het **diversenjournaal**, liefst op 1/1:
- xxx EUR op de klant/leverancier
- -xxx EUR op rekening 400000 (klanten) / 440000 (leveranciers)

Door de centralisatierekening zelf als tegenrekening te nemen is dit voor die rekening een nuloperatie (boeken op een klant is ook boeken op 400000), maar het saldo van de individuele klant/leverancier wordt wel rechtgezet.

## 6. Punt 4 - Overzicht (rekeningoverzicht) leveranciers, klanten, grootboekrekeningen

### 6.1 Waarvoor

Onmiddellijk op het scherm de toestand van één rekening: wat een klant nog verschuldigd is, wat men een leverancier nog moet, het saldo van een grootboekrekening. De rekeningen worden na elke boeking meteen bijgewerkt (ook boekingen van andere gebruikers). Bij klanten en leveranciers staan factuur en bijhorende betalingen bij elkaar gegroepeerd.

Dit scherm is een **leesscherm**: `F8` betekent hier "zoek op" en boekt niets. (In andere schermen, bv. het kasverslag, betekent F8 afdrukken/boeken - niet verwarren.)

### 6.2 Werkwijze

1. Kies het type: `K` (klant), `L` (leverancier) of `G` (grootboek).
2. Geef de fiche in (naam of nummer).
3. Optioneel een periode van/tot. Valt de begindatum **voor** de archiveringsdatum, dan wordt automatisch in het jaararchief gezocht; valt ze **na** de archiveringsdatum, dan wordt een beginsaldo getoond van de boekingen tot die datum.

| Toets (selectiescherm) | Werking |
|---|---|
| F1 | Stop |
| F2 | Openstaande facturen van de fiche |
| F3 | Vervallen facturen van de fiche |
| F4 | Alle facturen van de fiche |
| F8 | Zoek op volgens de selectie |
| F10 | Zoek op in het jaaroverzicht/jaararchief (enkel als de optie jaararchief geinstalleerd is) |

Kolommen van het overzicht: **Jnl** (journaal), **Volgnr** (nummer van factuur of uittreksel), **Datum** (boekdatum), **Debet/Credit**, **Referentie**, **Opmerking** (eerste letters).

| Toets (overzicht) | Werking |
|---|---|
| F3 | Volgend scherm |
| F5 | Detail van een geboekte lijn bekijken |
| F9 | Rekeningoverzicht afdrukken (volledig, met volledige opmerking/mededeling) |
| F10 | De factuur bekijken |
| F12 | Afdrukken in PDF (module in optie), bv. om naar een klant te mailen |

Aandachtspunten:
- Het **saldo onderaan** is het saldo van de boekingen tot en met het getoonde scherm. Voor het totale saldo moet men tot het laatste scherm bladeren (`F3` ingedrukt houden tot het scherm niet meer verandert).
- **Totaalrekeningen** en de **centralisatierekeningen** klanten/leveranciers kunnen hier niet opgevraagd worden; gebruik daarvoor de balansen (B.5.1).
- Een grootboekrekening met "Centralisatie = J" toont enkel totalen. De handleiding vermeldt dat men de parameter op de grootboekfiche tijdelijk op `N` kan zetten om detail te zien; dit is een wijziging van een instelling (met gevolgen voor het jaararchief) en geen leeshandeling - niet zomaar laten doen door een junior.
- Eén teruggevonden lijn (bv. één klantbetaling) bewijst niet dat een volledig stuk zoals een kasverslag geboekt is; kijk dan naar het volledige stuk via journaal + volgnummer + boekdatum, of druk het journaal af (B.5.1).

### 6.3 Referenties corrigeren (afpunten rechtzetten)

Staan factuur en betaling niet onder elkaar, dan heeft de betaling een foute of geen referentie (bv. een voorschot op een toekomstige factuur). De referentie van een boeking kan in het rekeningoverzicht aangepast worden. Ze bestaat uit **jaartal** van de factuur, **journaal** (aankoop- of verkoopjournaal) en **volgnummer** (factuurnummer) en moet altijd naar de factuur (of creditnota) verwijzen.

Let op: na het wijzigen van een referentie "verhuist" de boeking op het overzicht pas bij het opvragen van een volgend scherm; daardoor kan ze twee keer in het getoonde saldo zitten. Roep na het wijzigen van referenties het rekeningoverzicht **opnieuw** op om het juiste saldo te zien.

Voor zeer lange rekeningen (verzamelklanten zoals "Particuliere klanten", "Bancontact") bestaat het hulpprogramma `+.D` (optie).

## 7. Punt 8 - Facturatie vanuit het boekhoudpakket (kort)

De uitgebreide facturatie zit in Jamadrink; de boekhoudhandleiding beschrijft deze punten:

| Punt | Functie |
|---|---|
| 8.1 | Beheer leveringsbons (8.1.1 aanpassen, 8.1.2 inbrengen, 8.1.3 schrappen) |
| 8.2 | Afprinten leveringslijsten per klantentoer |
| 8.3 | Afprinten facturen uit leveringsbons (8.3.1 klant per klant, 8.3.S per serie) |
| 8.4 | Afprinten facturen met rechtstreekse ingave |
| 8.5 / 8.6 | Facturen uit bons / van verkopen van de KeyConen-kassa (optie) |
| 8.7 | Factuur groothandel naar kleinhandel (optie) |
| 8.8 | Aanpassen leeggoed van geboekte facturen (optie) |
| 8.9 | Beheer leveringen/mutaties aan filialen (optie) |
| 8.A | Beheer leeggoed-retour met PDA (optie) |
| 8.B | Beheer uitleningen/verhuur van goederen (optie) |
| 8.H | Herafdrukken van facturen (optie): 8.H.1 bekijken/herafdrukken, 8.H.2 detail uitschrijven in TXT, 8.H.U schrappen verkoopfacturen |

### 7.1 Factuur met rechtstreekse ingave (8.4)

Hoofding:
- **Klant**: stukje naam of nummer; `F7` zoekt op; bestaat de klant niet, dan nogmaals `F7` om hem bij te maken.
- **Factuurdatum** (= boekdatum) en **factuurnummer**: automatisch.
- **Vaste teksten (nr.)**: 2 van de 4 vaste teksten uit `+.4` kiezen via hun nummer.
- **Aantal facturen**: aantal exemplaren.
- **Globaal BTW% (99 = normaal)**: afwijkend BTW-% voor de hele factuur (bv. 6).
- **Exportfactuur J/N**: `J` zet de BTW op 0 %.
- **Munt**: EUR, of een andere valuta als met wisselkoersen gewerkt wordt.
- **Ontvangen voorschot**: informatief afgedrukt.
- **Voldaan factuur J/N**: bij `J` staat "VOLDAAN" op de factuur in plaats van de vervaldatum.
- **Stockaanpassing J/N**: volgens de bron wordt bij `J` de omzet bijgeteld op de klantenfiche.
- **Boeken J/N**: bij `J` wordt de factuur direct doorgeboekt in de boekhouding.
- **Opmerking boekhouding**: tekst op de klantenrekening.
- **Vervaldatum**: berekend uit de betalingstermijn van de klant. **Disconto (%)**: optioneel.

Dan `F8` (memo van de klant), `F8` (facturatie-/leveringsadres), `F8` (detailscherm). Per lijn: aantal (leeg bij een tekstlijn), omschrijving, eenheidsprijs (dan is een aantal verplicht), korting (voorgesteld uit de klantenfiche), BTW%, en **G** (grootboekcode). De verkooprekening wordt samengesteld als `70` + G + BTW% (bv. 70021, 7012, 70106) en **moet bestaan in het rekeningplan**. `F7` herberekent het totaal. **Negatieve aantallen maken er automatisch een creditnota van.** `F8`: totaal incl. BTW + algemene teksten; `F8`: afdrukken; daarna kan opnieuw afgedrukt worden; `F5` als alle documenten er zijn: de factuur wordt geboekt.

### 7.2 Herafdrukken en kopies van facturen (8.H)

- Tijdens het factureren wordt het detail van elke factuur weggeschreven in de map **`FTKOPIE`**, één bestand per factuur met de naam `DDDNNNNN.JJ` (DDD = dossiercode, NNNNN = factuurnummer, JJ = jaartal; bv. `FAS00123.08`).
- Van deze map moet regelmatig (minstens maandelijks) een aparte kopie genomen worden; hiervoor is een punt voorzien op het menu "Beheer Computersysteem - Jamadata" (meestal punt 8).
- **8.H.1**: factuur oproepen op factuurnummer, of op klant (lijst van zijn facturen; zonder boekhoudpakket kan dit lang duren). Jaartal aanpassen voor facturen van vorig jaar. Het veld "Subdirectory: \FTKOPIE\" kan tijdelijk gewijzigd worden als oude facturen in een andere map bewaard worden.
- **8.H.2**: detail van facturen uitschrijven naar een TXT-bestand (standaard `FACTUREN.TXT` in de Jamadata-map; naam max. 8 tekens + `.TXT`). Verplicht begin- en eindfactuur; optioneel factuurdatum, artikelcode; detail `H` (hoeveelheden + lotnummer) of `V` (volledig, met bedragen). Bruikbaar voor traceerbaarheid en verwerking in Excel.
- **8.H.U**: verkoopfactuur schrappen met de mogelijkheid om statistieken/voorraad terug te zetten.

## 8. Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Boeking geweigerd: "Debet is niet gelijk aan credit" (10) | Totaal, BTW en uitsplitsing sluiten niet. Bij verlegde BTW: totaalbedrag = enkel het aan de leverancier te betalen bedrag. |
| "Er is reeds een factuur geboekt onder dit nummer" (59) | Fout nummer, of de teller "Laatst" van het journaal in `+.3` staat verkeerd, of eerst het oude stuk schrappen via `U`. |
| Beginsaldo van het bankuittreksel klopt niet | Uittreksel overgeslagen of in verkeerde volgorde ingegeven, of laatste stuk geschrapt. Corrigeer in de hoofding of in `+.3` (kolom Saldo). |
| Grootboekbedrag staat aan de verkeerde zijde | Bij type G is negatief = debet en positief = credit. Lijn schrappen via `F9` (overzicht) en opnieuw ingeven. |
| Betaling staat los van de factuur op de klantenrekening | Referentie fout of leeg (voorschot). Rechtzetten in punt 4. |
| Betaling geboekt voor de factuur bestond | Geboekt als voorschot op toekomstige factuur (`F9`); nadien referentie koppelen in punt 4. |
| "Er ontbreekt een noodzakelijke grootboekrekening bij de parameters" (16) / "Parameter grootboekrekening is niet te vinden" (28) | Vul in `+.3` de verplichte rekeningen in (aftrekbare BTW, niet-aftrekbare BTW, BTW verkopen, centralisatierekeningen) en zorg dat ze bestaan in het rekeningplan. |
| Factuur van 2 jaar geleden staat nog open, 100 komt twee keer voor | Stuknummers herbeginnen per jaar; gebruik het jaartal in de referentie en bij het schrappen. |
| Grootboekbalans/bankjournaal begin van het jaar fout | Openingsbalans nog niet ingegeven (zie hoofdstuk 5). |
| Na stroomuitval tijdens het boeken | Zie `boekhouding-archivering-en-foutenlijst.md`, hoofdstuk 2. |

## Bronnen

- `Gebruikerhandleiding BOEKHOUDPAKKET.docx` (map boekhouding) - versie V06, 12-8-2014: punt 1, punt 2, "2.U Schrappen van boekhoudbewegingen", "Functietoets F10", punt 4, punt 8.
- `0032A - Ingeven openingsbalans.docx` (map Jamadrink/Handleidingen modules).
- `01_EXPERTANTWOORDEN_45.md` (00_START_CLAUDE/01_NAAR_CLAUDE) - HUMAN-Q035/Q036 (herkenning dubbele facturen).
- `00_CHECKPOINT_BOEKING_LEESROUTE.md` (00_START_CLAUDE/16_BOEKING_LEESROUTE) - enkel de inhoudelijke punten over het lezen van het rekeningoverzicht (F8 = zoek op, F5 = detail, voorzichtigheid met "Centraliseren").
