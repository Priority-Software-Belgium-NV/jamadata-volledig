# Praktijkkennis opleiding mei 2026: werken in Jamadrink – navigatie, basisgegevens, facturen en boekhoudcontrole

Gebruik dit document voor: vragen over de algemene bediening van het pakket (hoofdmenu, functietoetsen, zoeken, selectieschermen, pdf/Excel), de basisgegevens (fiches van leveranciers, klanten, artikelen: velden, blokkeren, memo, extra info), het maken en boeken van een factuur, de klacht "dubbele/verdwenen facturen", het opnieuw afdrukken of versturen van facturen, en de controlelijst in de boekhouding om na te gaan welke facturen echt geboekt zijn.

> **Waarschuwing.** Deze inhoud komt uit gesproken opleidingssessies (automatische Whisper-transcriptie, mei 2026) en kan herkenningsfouten bevatten in menunummers en functietoetsen (bv. `F8` werd geregeld verkeerd herkend). De opleider gebruikte de leveranciersfiche als voorbeeld; klanten- en artikelfiches werken grotendeels hetzelfde maar kwamen in deze sessies nog niet in detail aan bod. Controleer bij twijfel tegen de handleiding: overal in het pakket opent het **vraagteken** de handleiding van het scherm waarin je staat. Punten met *(te verifiëren)* waren niet eenduidig.

## 1. Navigatie en vaste toetsen

Bron: opleiding 21-05-2026 (ca. 00:12–00:14 en 00:42–00:52), 13-05-2026 (ca. 00:15).

- Bij het opstarten komt het pakket op het brievenscherm; met `F1` (stoppen), eventueel herhaald, kom je altijd terug op het **hoofdmenu Voorraad**. Begin een uitleg aan een klant altijd vanaf het hoofdmenu, zodat hij weet hoe hij ergens geraakt is.
- De Jamadata Desktop toont vier schermen (sessies) waartussen je kan wisselen. Via het menu **Scherm** kan je twee schermen naast elkaar zetten: handig om rechts een bestaand voorbeeld (bv. een ingevulde fiche) te tonen en links een nieuwe in te vullen.
- De functietoetsen staan onderaan elk scherm en kunnen met de muis of het toetsenbord gebruikt worden:

| Toets | Betekenis (in fiches en de meeste schermen) |
|---|---|
| `F1` Stoppen | Stoppen **en wegschrijven** van wat je aan het aanpassen was. |
| `F8` Schrijf weg / bevestig | Wegschrijven en verdergaan (volgende fiche, volgend scherm). Algemene bevestigtoets. |
| `F6` Annuleren | Verlaten **zonder** de wijzigingen te bewaren. |
| `F7` | In zoekvelden: zoeken/invullen (zoals Tab); in selectieschermen: alle selectiecriteria wissen; in lijsten met actieve gebruikers/update: vernieuwen. |
| `F9` | Contextafhankelijk: in een selectiescherm "volledige lijst"; op de leveranciersfiche de standaard grootboekrekeningen; in lijsten markeren. |
| `F10` | Memo (op een fiche); relay-instellingen (in het mailscherm). |
| `F11` | Op een nieuwe fiche: de gegevens van de laatst bekeken fiche overnemen. |
| `F12` | Extra info (op een fiche). |
| `F4` | Bevestigen van een ingrijpende actie (schrappen, update installeren, waarschuwing negeren). |
| `Tab` | In een fiche: van kijkmodus naar aanpasmodus; in een zoekveld: zoeken/invullen. |

- **Rechtsklikken** op een veld geeft een contextmenu (kopiëren, e-mail versturen, btw-nummer opzoeken, ...).
- **Parameters**: op het hoofdmenu de toets `+`; daaronder `J` = JMS-instellingen (o.a. `1` afdrukposten, `2` documenteigenschappen, `4` servernaam, `5` mail, `T` actieve gebruikers).
- Het tandwielicoon rechts onderaan op het hoofdmenu geeft o.a. de manuele back-up.

## 2. Basisgegevens: fiches

Bron: opleiding 21-05-2026 (ca. 00:12–01:06).

Pad: hoofdmenu Voorraad → `9` **Basisgegevens** → leveranciers, klanten, artikelen, groepen (en prijsafspraken). Voor leveranciers, klanten en artikelen is het submenu telkens hetzelfde:

1. Aanpassen/bekijken
2. Bijvoegen (nieuwe fiche)
3. Schrappen
4. Afdrukken van de lijst van fiches
5. Etiketten afdrukken (adresetiketten)
6. Uitschrijven naar Excel (in de opleiding punt `7`)
7. Aanpassen/schrappen van een reeks fiches (opkuis)

(Exacte nummering van de onderste punten: *te verifiëren* op het scherm. Groepen heeft maar twee punten.)

### 2.1 Een fiche zoeken

- Tik het **begin van de naam** en bevestig met `F8`.
- Niet gevonden? Gebruik het **vergrootglas** = uitgebreid zoeken: zoekt de ingetikte tekst in **alle velden** van de fiche (naam, adres, gemeente, vertegenwoordiger, opmerkingen, ...). Zo kan je bv. alle fiches uit een bepaalde gemeente of van een bepaalde vertegenwoordiger vinden.
- `F6` annuleert de zoekopdracht.
- Met de pijltjes vorige/volgende blader je door de fiches. **Let op: wijzigingen worden bewaard zodra je doorbladert.**

### 2.2 Kijkmodus en aanpasmodus

- Bij veel (vooral grotere) klanten opent een fiche in **kijkmodus**: je kan niets wijzigen. Dat is bewust, om te vermijden dat twee gebruikers dezelfde fiche tegelijk aanpassen en elkaars wijzigingen overschrijven (wie het laatst wegschrijft, wint).
- Druk op **`Tab`** om naar aanpasmodus te gaan.
- Typische vraag van klanten: "ik kan de fiche niet aanpassen" → Tab.

### 2.3 Velden en knoppen (voorbeeld leveranciersfiche)

- **Codenummer**: wordt automatisch toegekend, of is vrij in te vullen. Vrij invullen wordt gebruikt bij klanten met een koppeling naar een extern boekhoudpakket, waar de code moet overeenkomen met de code in dat pakket. Dit verschilt per klant (instelling).
- **Blokkeren** (slotje naast de code): een geblokkeerde leverancier, klant of artikel blijft oproepbaar maar kan niet meer gebruikt worden – voor een geblokkeerde klant kan je geen bon of factuur maken, een geblokkeerd artikel kan niet op een bon of factuur. Nogmaals klikken deblokkeert.
- **Naam, adres**: de schrijfwijze (hoofdletters/kleine letters) wordt exact zo overgenomen op lijsten en afdrukken. Naam en code moeten **uniek** zijn; een tweede fiche met dezelfde naam geeft de melding dat ze al bestaat.
- **Postcode**: het vergrootglas erachter zoekt de gemeente(n) bij de postcode en vult ze in.
- **Wereldbol**: opent het adres in Google Maps (route/afstand, o.a. gebruikt voor het inschatten van transportkosten). Werkt niet voor elk adres; dat ligt aan de kaartdienst.
- **Telefoon/gsm/fax**: vrij veld; gebruik overal dezelfde notatie, anders zijn Excel-exports moeilijk bruikbaar. "Telefoonnummer opzoeken" (rechtsklik) werkt niet meer (de achterliggende website bestaat niet meer).
- **Btw-nummer**: het landvoorvoegsel staat vast; het nummer wordt op het controlegetal gecontroleerd. Uitzonderingen die aanvaard worden: **allemaal nullen** = heeft geen btw-nummer; **allemaal negens** = btw-nummer nog niet gekend (later via een selectie op te lijsten en aan te vullen). Rechtsklik → **btw-nummer opzoeken** opent de Kruispuntbank van Ondernemingen (status van de onderneming, bv. stopgezet). Voor buitenlandse relaties is er een apart veld voor het buitenlandse btw-nummer.
- **Rekeningnummer / IBAN / BIC**: ook hier een controle op het controlegetal (nullen mogen). Het **vraagteken "controleer IBAN/BIC"** vult de BIC aan op basis van de IBAN; plak je een oud Belgisch rekeningnummer in het IBAN-veld en klik je op het vraagteken, dan wordt het omgezet naar IBAN + BIC.
- **Betalingstermijn**: in dagen. Speciale codes: **E1** = 30 dagen einde maand, **E2** = 60 dagen einde maand. Geldt voor leveranciers en klanten.
- **Korting bij contante/snelle betaling** (bv. 2 % binnen 8 dagen): bij een leverancier louter informatief (de leverancier vermeldt het op zijn factuur); is het bij een klant ingesteld, dan wordt het op de verkoopfactuur vermeld.
- **E-mailadres**: rechtsklik → e-mail versturen opent een nieuw bericht. Het `+` achter het e-mailveld laat een bijkomend (kopie)adres toe.
- **`+` rechtsboven op de fiche** = extra opties: openstaande bestelbons, boekhoudrekening/openstaande facturen, historiek, gekoppelde documenten, en de **GDPR-export** (schrijft alle bijgehouden velden van de fiche weg in een csv-bestand; nodig als een relatie zijn gegevens opvraagt).
- **`F9` Standaard grootboekrekeningen** (leverancier): de rekeningen die voorgesteld worden bij het inboeken van een aankoopfactuur van deze leverancier (bv. een 6-rekening voor handelsgoederen en een rekening voor leeggoed). Ze kunnen hier ingevuld worden of worden onthouden bij het inboeken.
- **`F10` Memo**: vrij notitieveld. Bij een **klant** verschijnt de memo op het scherm bij het maken van een bon of factuur (bv. "opgelet, slechte betaler"). De memo wordt nooit afgedrukt.
- **`F12` Extra info**: ± 200 vrije regels voor wat nergens anders past (extra contactpersonen, contractgegevens, ...). Via `F9` (alles) kan je per regel een datum en een type (zelf te kiezen letter, bv. C voor contract) meegeven en bij klanten een alarm vanaf een bepaalde datum bij het maken van een bon/factuur. De extra info kan per type en per periode afgedrukt worden. De knop kleurt rood als er iets ingevuld is. In dit scherm: `F2`/`F3` scherm omlaag/omhoog, lijn invoegen, lijn wissen (zie de handleiding via het vraagteken).

### 2.4 Nieuwe fiche en schrappen

- **Bijvoegen**: lege fiche invullen. Met `F11` neem je de gegevens over van de fiche die je net bekeken hebt – vooral handig om een gelijkaardig **artikel** aan te maken (bv. een nieuwe smaak).
- **Schrappen**: fiche oproepen, de vraag "wenst u werkelijk te schrappen" bevestigen met `F4`. Het pakket verwijdert dan ook alles wat aan de fiche hangt (documenten, historiek, statistieken, koppelingen).
- **Reeks fiches aanpassen/schrappen** (opkuis): toont de fiches met twee extra kolommen: komt de fiche voor **in de boekhouding** en **in de statistieken**. Fiches met tweemaal "nee" zijn nooit gebruikt en kunnen met `F9` gemarkeerd worden; bij het stoppen vraagt het pakket bevestiging om de gemarkeerde fiches te schrappen. Je kan vooraf filteren op enkel geblokkeerde fiches of fiches zonder boekhouding/omzet.

## 3. Lijsten, selectieschermen, pdf en Excel

Bron: opleiding 21-05-2026 (ca. 00:54–01:03).

- **Kies bij lijsten altijd de knop PDF.** Lijsten staan standaard op pdf, maar als een klant een lijst op printen heeft staan, kan `F8` een afdruk van honderden pagina's starten (bv. een volledige artikellijst).
- **Selectiescherm** – komt terug bij bijna alle lijsten en statistieken. Na het kiezen van de lijst krijg je een lege fiche waarop je per veld criteria kan zetten, telkens via een van de knoppen:
  - gelijk aan / niet gelijk aan
  - groter dan / groter dan of gelijk aan
  - kleiner dan / kleiner dan of gelijk aan
- Criteria zijn **combineerbaar**. Voorbeeld: postcode "groter dan of gelijk aan" 2800 én "kleiner dan" 3000 geeft alle fiches met een postcode van 2800 tot 2999.
- **Jokerteken**: `B*` bij "gelijk aan" op de naam = alles wat met B begint (zonder sterretje zoekt het pakket letterlijk "B").
- "Niet gelijk aan" werkt op elk veld, bv. alle klanten die niet op maandag beleverd worden als de leverdag in een veld is ingevuld.
- **Criteria blijven staan** voor de volgende keer. Met **`F7`** wis je alle selectiecriteria in één keer; doe dat als een lijst onverwacht weinig of niets toont.
- **`F9`** in het selectiescherm = volledige lijst, zonder selectie.
- **Uitschrijven naar Excel** (in het menu van de basisgegevens): vink de gewenste velden aan (de veldnamen zijn de afkortingen uit de database), kies een selectie of alles; het resultaat opent in Excel. Dit wordt ook door support gebruikt om fouten in gegevens (vooral artikelen) snel op te sporen.
- Tijdens het installeren van een programma-update kunnen lijsten/pdf's even niet gemaakt worden; het pakket meldt dan dat de update bezig is.

## 4. Een factuur maken – en wanneer ze echt geboekt is

Bron: opleiding 20-05-2026 voormiddag (ca. 00:09–00:14).

Pad: hoofdmenu → `8` **Facturatie** → **Facturen met rechtstreekse ingave**.

1. Klant ingeven (begin van de naam + `Tab` of `F7` om op te zoeken/in te vullen). De parameters staan standaard goed.
2. Met `F8` door de schermen: eventuele info/memo van de klant, factuurgegevens (adres aanpasbaar), dan het artikelscherm.
3. Artikellijnen ingeven: aantal, artikel (bij de omschrijving zoeken met `Tab`/`F7`).
4. `F8`: het pakket toont hoe de factuur verstuurd wordt (mailen en/of via Peppol, volgens de instellingen van de klant); dat kan je per factuur afzetten.
5. `F8` drukt de factuur af; de knop PDF toont ze op het scherm.
6. Daarna komt het **eindscherm met de vraag of je het blad nogmaals wil afdrukken**, met de mogelijkheden opnieuw afdrukken, aanpassen of annuleren. **Pas wanneer dit eindscherm bevestigd wordt (in de opleiding met `F5`), is de factuur geboekt.**

**Valkuil ("dubbele facturen", "mijn factuur is weg").** Op het eindscherm ligt de factuur al op de printer (of is ze al als pdf getoond), maar ze is nog **niet geboekt**. Wordt op dat moment geannuleerd, of crasht/herstart de database terwijl de gebruiker op dit scherm staat, dan bestaat de factuur enkel op papier: het factuurnummer wordt bij de volgende factuur opnieuw voorgesteld. De klant heeft dan twee papieren facturen met hetzelfde nummer, of een papieren factuur die niet in het pakket zit. Bij klanten waar de database geregeld vastloopt (zie document diagnose) komt dit voor.

- Het **papier is nooit het bewijs**; enkel wat in het verkoopjournaal staat, is geboekt (zie § 6).
- Facturen die op papier of per mail bij een klant terechtkwamen maar niet geboekt zijn, moeten opnieuw gemaakt worden.

## 5. Facturen opnieuw afdrukken of opnieuw versturen

Bron: opleiding 13-05-2026 (ca. 00:13–00:16), 20-05-2026 namiddag (ca. 00:59–01:00), 12-05-2026 namiddag (ca. 00:01), 19-05-2026 (ca. 00:14 en 00:42).

- Pad: hoofdmenu → `8` Facturatie → `H` **Herafdrukken facturen**.
  - `1` Bekijken/herafdrukken van gemaakte facturen (op factuurnummer of op klant; factuur kiezen en bevestigen met `F8`). Er zijn ook keuzes voor alle facturen en voor een reeks facturen.
  - Rechts onderaan in dit menu staan twee icoontjes: **niet-verzonden facturen** en **verzonden facturen** (mail). Bij de niet-verzonden kan je een factuur bekijken, opnieuw versturen of uit de lijst verwijderen.
- Waar de afdruk uitkomt (printer of pdf) hangt af van de documenteigenschappen en van de instellingen van de werkpost; zie het document over printers.
- **Een factuur opnieuw via Peppol versturen**: komt zeer vaak als vraag binnen. De werkwijze staat letterlijk in de Peppol-handleiding en in de Peppol-FAQ; verwijs daarnaar of kopieer de passage voor de klant.
- **Inkomende Peppol-facturen** bekijkt de klant via het hoofdmenu Boekhouding → Inbrengen facturen → inkomende Peppol-facturen. Meldt een klant dat er niets meer binnenkomt, kijk daar eerst of er recent nog documenten zijn toegekomen.

## 6. Boekhouding: controleren welke facturen geboekt zijn

Bron: opleiding 20-05-2026 voormiddag (ca. 00:18–00:22).

Pad: **hoofdmenu Boekhouding** → `5` **Afdrukken** → `1` **Afdrukken periodelijsten** (journalen, btw-aangifte, balansen).

1. Kies de periode (één maand volstaat; voor de zekerheid van het begin van het boekjaar tot en met de lopende maand).
2. Vink **"Fouten in controlelijst"** aan en kies PDF.
   - De lijst toont per journaal (bv. het verkoopjournaal) de reeks factuurnummers (van–tot) en meldt **dubbele nummers**, ontbrekende nummers en facturen die **niet chronologisch** zijn (een factuur met een vroegere datum na een latere).
   - Geen fouten = er zitten geen dubbele facturen in de boekhouding.
3. Vink daarnaast **"Journalen"** aan om ook het journaal zelf te krijgen: één regel per factuur met nummer, klant, bedrag, btw-opsplitsing, totaal en het bedrag op de bijzondere rekening (meestal leeggoed). **Dit is de lijst van wat echt geboekt is.**

Heeft de klant meerdere firma's/dossiers (bv. groothandel en winkel), doe de controle dan in elk dossier apart.

Gebruik: bij de klacht "dubbele facturen" eerst vragen **welke** facturen (nummers), dan deze lijst trekken. Staat een nummer maar één keer in het journaal, dan is de andere papieren versie nooit geboekt (zie § 4).

## 7. Enkele losse punten uit de ticketbesprekingen

- **Peppol-problemen** die niet in de handleiding/FAQ staan, en **boekhoudkundige vragen** (openingsbalans, balansverschillen) gaan naar tweede lijn/ontwikkeling; de helpdesk had in mei 2026 nog geen boekhoudopleiding gekregen. (opleiding 12-05-2026 voormiddag, ca. 00:02; 19-05-2026, ca. 00:07)
- Vraagt een klant een **aanpassing aan het pakket** (bv. promoties per kassa), dan is dat een ontwikkelvraag en geen supportticket. (opleiding 19-05-2026, ca. 00:52)
- Zet bij een ticket altijd de **juiste klant en contactpersoon**; zonder contact komt het antwoord niet bij de klant terecht. (opleiding 19-05-2026, ca. 00:49)
- Een leverancier die tegelijk klant is (bv. een brouwerij) kan in het ticketsysteem als "billable klant" staan zonder dat er onderhoud aangerekend wordt. (opleiding 19-05-2026, ca. 00:45)

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):

- gedocumenteerde kennisoverdracht V-20260512_101045-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260512_150237-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260513_094305-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260519_140734-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260520_100445-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260520_143704-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260521_101124-Opname van vergadering.txt
