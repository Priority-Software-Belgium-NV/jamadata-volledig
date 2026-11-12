# Jamadrink – kortingen, prijsafspraken, prijswijzigingen, bons en facturen: praktijkkennis uit de opleidingen juni–juli 2026

Gebruik dit document voor: helpdeskvragen over de kortingsstructuur in Jamadrink (klantfiche, prijsafspraken, voorrangsregels, accijns), prijswijzigingen op datum, het aanmaken van artikels, leveringsbons en facturen (maken, aanpassen, factureren, apart of samen factureren), Coca-Cola-orders, offertes, omzetfiches, klantentoeren, statistieken doorsturen naar leveranciers (Haacht, Coca-Cola, AB InBev), de jaarafsluiting en een overzicht van waar wat zit in het hoofdmenu.

> **Let op – bron is gesproken opleiding.** Deze inhoud komt uit automatisch getranscribeerde (Whisper) opleidingssessies. Menupunten en toetsen zijn zo goed mogelijk gereconstrueerd, maar kunnen herkenningsfouten bevatten, en de punten in een menu verschillen per klant naargelang de aangekochte modules. Controleer bij twijfel tegen de handleiding (het vraagteken `?` rechtsboven bij het menupunt). Onzekere plaatsen zijn gemarkeerd met "te verifiëren".

---

## 1. Waar zit wat? Hoofdmenu voorraad

| Punt | Inhoud | Opmerking |
|---|---|---|
| 1 | Bestellingen aan leveranciers | ook inlezen van PDA-bestellingen |
| 2 | Beheer Icone-kassa | zie `opleiding-zomer-kassa.md` |
| 3 | Beheer prijzen | prijswijzigingen (hoofdstuk 4), accijnsverhogingen, promoties horeca (weinig gebruikt) |
| 4 | Statistieken en historiek | onderaan iconen voor leverancierskoppelingen (hoofdstuk 10) |
| 5 | Lijsten | alle afdruklijsten (pdf, vaak ook Excel); **offertes zitten hier: 5 > 6** |
| 6 | Grootte van de gebruikte bestanden | aantal lijnen per databasebestand |
| 7 | Rapport per klant | prijsafspraken + statistiek + facturen + vervallen facturen in één rapport over een periode |
| 8 | Facturatie | bons, facturen, herafdrukken (hoofdstukken 6–8) |
| 9 | Basisgegevens | leveranciers, klanten (2), artikels (3), groepen, prijsafspraken (5), omzetfiches, klantentoeren |
| A | Periodieke werkzaamheden | jaarafsluiting (1), jaarinventaris (2), mobiele scanners (M) |
| B | Boekhoudmenu | zie `opleiding-zomer-boekhouding.md` |
| + | Parameters (verborgen toets) | 1 firmagegevens, 3 o.a. boekingsdatum, 4 facturatieparameters, 5 paden, J JMS-instellingen/documenteigenschappen |

- Bij de meeste menupunten staat rechtsboven een **`?`**: dat is de handleiding van precies dat punt. Het nadeel: je moet het punt eerst weten staan om de handleiding te vinden. Klassiek voorbeeld: **offertes** zoekt men onder 8 Facturatie, maar ze staan onder **5 Lijsten > 6 Offertes**.
- **Punt 6 – bestandsgrootte**: de zwaarste pakketversie heeft een onbeperkte database; lagere versies zijn beperkt (genoemd: 60.000 of 120.000 lijnen). Een bestand kan dus vol raken; dan moet opgekuist worden (boekhouding archiveren, statistieken opkuisen).
- Welke velden op een scherm getoond of verborgen worden per klant, kan enkel Jamadata instellen (programmatie), niet de klant zelf.
- Aanpassingen aan lijsten (extra kolom e.d.) zijn standaard niet mogelijk: lijsten zijn voor iedereen gelijk; elke wijziging gaat via ontwikkeling.

(opleiding 25-06-2026, ca. 00:02–00:10; 02-07-2026, ca. 00:41–00:44)

---

## 2. Kortingen op de klantfiche

Klantfiche: Hoofdmenu voorraad > 9 > 2 > 1 (aanpassen/bekijken).

- **Directe korting (%)**: wordt meteen op bon/factuur toegepast op alle artikels, behalve op groepen "zonder korting" en behalve waar een prijsafspraak iets anders zegt.
- **Periodieke korting** (op het scherm ook "semestriële korting" genoemd) = **uitgestelde korting**: komt niet op de factuur, wordt bijgehouden in de statistieken en per maand, kwartaal of jaar uitbetaald via een creditnota (Facturatie: punt creditnota's uitgestelde korting, met handleiding van één pagina achter `?`). Staat volledig los van de directe korting; beide kunnen samen bestaan.
- Bij de uitgestelde korting hoort een **bedragveld**. Praktijkvoorbeeld: een nieuw café krijgt geen directe korting maar 10 % uitgesteld, waarmee een investering (tapinstallatie, koelkast) wordt afbetaald. Zet het geïnvesteerde bedrag **negatief** in dat veld; bij elke factuur loopt het op richting nul. Is het afbetaald, dan wordt de uitgestelde korting weggehaald en krijgt de klant een directe korting.
- **Eigen prijs op kassa**, **facturatieklant**, **prijs op bon**, **memo** en **afhaling** staan ook op de klantfiche en beïnvloeden kassa en bons (zie hoofdstuk 6).

(18-06-2026, ca. 00:13–00:16; 23-06-2026, ca. 00:54)

---

## 3. Prijsafspraken

**Waar:** Hoofdmenu voorraad > 9 Basisgegevens > 5 Prijsafspraken. Opbouw zoals bij klanten/artikels: nieuwe fiche, aanpassen/bekijken, schrappen, afdrukken.

### 3.1 Bekijken: lees de lijst van onder naar boven
Aanpassen/bekijken > **2 (via lijst)** > klant ingeven > F8. De lijst toont alles wat voor die klant geldt. **Onderaan staat het laagste niveau, hoe hoger in de lijst hoe meer voorrang**:

1. (onderaan) algemene korting van de klantfiche – direct % en uitgesteld %;
2. afspraak op **groep** – heeft voorrang op de algemene korting;
3. afspraak op **leverancier** – heeft voorrang op de groep (in het scherm kan ook op merk/producent gewerkt worden);
4. (bovenaan) afspraak op **artikel** – hoogste niveau, alles eronder vervalt.

Voorbeeld: klant heeft 22 % algemeen; groep frisdrank in glas 24 %; leverancier Coca-Cola 25 %; één specifiek sixpack 10 % → voor dat sixpack geldt 10 %, voor andere Coca-Cola-artikels 25 %, voor andere frisdrank in glas 24 %, voor al de rest 22 %.

Per afspraak kunnen bestaan: **korting in %**, **vaste verkoopprijs**, **korting per hectoliter** (weinig gebruikt) en een **uitgestelde** variant. Op de klantfiche zelf kan enkel een percentage.

**"Geen korting"**: de waarde 0 kan niet ingegeven worden; daarvoor dient de toets **F10 = geen korting**. Zo kan een groep of artikel uitgesloten worden van de algemene korting.

De voorrangsregels zijn nergens op het scherm uitgelegd; de eenvoudigste manier om ze aan iemand te tonen is in het demopakket van elk type een afspraak te maken en de lijst te bekijken.

(18-06-2026, ca. 00:16–00:21 en 00:43–00:44)

### 3.2 Ingeven
Nieuwe fiche, keuze uit:
1. **Afspraak per afspraak**: klant + één artikel, leverancier of groep. Omslachtig (één per keer).
2. **Via lijst van artikels**: klant (en eventueel leverancier) ingeven; je krijgt alle artikels met de reeds bestaande afspraken en vult korting % en/of vaste prijs in. Meest overzichtelijk.
3. **Via lijst van groepen**: per groep een percentage invullen.
4. **Op basis van een gemaakte offerte**: neemt de prijzen/kortingen van een offerte over als prijsafspraken op artikelniveau. Dit is een **terugkerende vraag** ("ik heb een offerte gemaakt, hoe krijg ik die in de prijsafspraken?"): klanten vinden dit punt niet.

Combineren kan: bv. een vaste verkoopprijs die hoger ligt dan de normale prijs, met daarop een percentage korting (de klant "krijgt korting" maar betaalt netto ongeveer hetzelfde). Of álle combinaties (met korting per hectoliter) samen werken is niet uitgeklaard (te verifiëren).

(18-06-2026, ca. 00:33–00:39)

### 3.3 Schrappen en kopiëren
- Schrappen per combinatie (klant-artikel, klant-leverancier, klant-merk, klant-groep).
- **Alle prijsafspraken van één klant of van één artikel schrappen**: apart punt (A); keuze bevestigen met F8, daarna F4 = schrappen.
- **Kopiëren van één artikel naar een ander** (bv. product wordt vervangen door een opvolger): maakt voor artikel 2 dezelfde individuele afspraken aan als voor artikel 1; het pakket vraagt of afspraken met een **vaste prijs** ook mee moeten of overgeslagen worden.
- **Kopiëren van één klant naar een andere** (bv. overname van een zaak, nieuw klantnummer): keuze tussen enkel de ontbrekende afspraken kopiëren of volledig gelijk maken.
- **Afdrukken van de lijst**: zonder selectie = alle prijsafspraken van alle klanten.

(18-06-2026, ca. 00:39–00:43)

### 3.4 Klacht "de korting op mijn factuur klopt niet"
Twee dingen controleren:
1. **Accijns**: op accijnzen wordt nooit korting gegeven. De berekening is: prijs − accijns → korting op de rest → accijns er weer bij. 22 % korting op een artikel met accijns is dus minder dan 22 % van de bruto prijs. Dit is typisch voor de drankensector en moeilijk uit te leggen aan (de klant van) de klant.
2. **Voorrangsregels** (3.1): geldt er een afspraak op groep/leverancier/artikel die de algemene korting overschrijft?

Tip om het uit te leggen: begin niet te rekenen op een factuur met veel lijnen. Maak een **testbon met één artikel, aantal 1** en reken daarop voor; de klant kan de rest dan zelf narekenen. Klopt het dan nog niet, geef het door aan ontwikkeling. (18-06-2026, ca. 00:46–00:47; 23-06-2026, ca. 00:39–00:41)

Op de afgedrukte bon/factuur heeft de kolom met de korting **bewust geen titel** (klanten zonder korting zien zo niet dat er een kortingskolom bestaat). (23-06-2026, ca. 00:41)

---

## 4. Prijswijzigingen (Hoofdmenu voorraad > 3 Beheer prijzen)

| Punt | Functie |
|---|---|
| 3 | **Directe** prijswijziging: past de prijs onmiddellijk aan op de artikelfiche. De vorige prijs is dan weg. Afgeraden als punt 4 beschikbaar is; lagere pakketversies hebben enkel dit punt. |
| 4 | **Uitgestelde** prijswijziging (op datum) – de aanbevolen werkwijze. Handleiding achter `?`. |
| 5 | Vervangen van de huidige prijzen door de nieuwe (definitief maken). |
| 6 | Afdrukken van de uitgestelde prijswijzigingen. |

### 4.1 Uitgestelde prijswijziging ingeven (punt 4)
1. Meestal per leverancier: leverancier ingeven, F8 → lijst van zijn artikels.
2. Artikel kiezen. Het scherm is de artikelfiche met extra velden: huidige prijzen links, nieuwe prijzen rechts.
3. **Ingangsdatum** en de **nieuwe aankoopprijs** invullen. (De datum blijft onthouden voor de volgende artikels in dezelfde sessie.)
4. **F7 "herbereken nieuwe prijzen"**: het pakket berekent alle verkoopprijzen opnieuw met **behoud van het winstpercentage**. Prijzen exclusief btw worden op de cent afgerond, de kassaprijzen (bak en stuk) op 5 cent – daardoor kan de winst licht afwijken. De nettoprijs is gelijk aan de aankoopprijs tenzij er een korting in %, korting in bedrag of handelingskost op het artikel staat.
5. Het voorstel mag manueel aangepast worden.
6. **F8** wegschrijven.
7. Bestaan er voor dat artikel **prijsafspraken met een vaste prijs**, dan toont het pakket die per klant met de winst of het verlies bij de nieuwe aankoopprijs. Pas de vaste prijs aan waar nodig en bevestig met **F4 "neem nieuwe prijs aan"** (bewust geen F8, om per ongeluk doorklikken te vermijden). Verlies kan soms bewust zijn (tussenkomst van de brouwerij).
8. Daarna vraagt het pakket of ook de **deelverpakkingen** aangepast moeten worden en overloopt die één voor één (geblokkeerde artikels – in het zwart – kan je overslaan).

Resultaat: op de artikelfiche blijven de huidige prijzen staan en verschijnt een kalender-icoon "prijs op datum" met de nieuwe prijzen. Vanaf de ingangsdatum gebruikt het pakket automatisch de nieuwe prijs. Voor de kassa: **2 > K** nemen; de toekomstige prijs gaat mee en de kassa schakelt zelf om.

(25-06-2026, ca. 00:12–00:24)

### 4.2 Controleren (punt 6)
Lijst van alle wijzigingen die op een datum ingaan: per artikel oude en nieuwe prijs per prijscategorie met de opslag, en de betrokken prijsafspraken per klant. **Negatieve opslag** op de lijst = nakijken, daar klopt waarschijnlijk iets niet. (25-06-2026, ca. 00:24)

### 4.3 Definitief maken (punt 5) – opletten
- Vervangt op de artikelfiche de oude prijs door de nieuwe; de oude prijs is daarna niet meer bruikbaar.
- Selectie "tot en met datum" (zonder begindatum = alles tot die datum).
- **Geef hier nooit een datum in de toekomst in.** Alle wijzigingen tot die datum worden dan meteen doorgevoerd en dat is niet terug te draaien; de enige oplossing is het artikelbestand terugzetten uit een back-up van vóór de handeling. Dit is bij een klant al gebeurd.
- Beste moment: **na de 20e van de maand die volgt** op de ingangsdatum. Tot dan worden nog facturen gemaakt in de vorige periode en heeft men de oude prijs nog nodig.
- Wie in punt 3 of 4 komt terwijl er nog wijzigingen van **meer dan een maand oud** openstaan, krijgt daar een melding van: eerst punt 5 uitvoeren tot en met vandaag.

(25-06-2026, ca. 00:24–00:29)

---

## 5. Artikels aanmaken: eenheden en verplichte velden

- De basiseenheid van een artikel in Jamadrink is de **bak** (de hoogste verkoopeenheid onder het palet). Alle prijzen op de artikelfiche zijn **bakprijzen**; de fles is een deelhoeveelheid ("aantal per bak"). Een vat is de eenheid zelf (aantal per bak = 1; bak en stuk zijn dan hetzelfde). Wijn kan per fles of per karton aangemaakt worden; karton + fles als stuk is het meest logisch omdat ook per karton aangekocht wordt.
- Artikelfiche > **F9 vervolg**: o.a. barcodes, "aantal per bak", "aantal per palet". Dat laatste bepaalt de omrekening van paletten op bons en op de PDA.
- **Verplichte velden** bij een nieuw artikel: code, naam, **leverancier** en **groep**. De leverancier moet een bestaande leverancier zijn (naam intikken + Tab of F7 om te zoeken). **Merk/producent** is niet verplicht en is iets anders: de leverancier is waar je aankoopt, de producent wie het maakt.
- Krijgt iemand een nieuw artikel niet bewaard, kijk dan eerst of de leverancier (en groep) correct zijn ingevuld.
- In de artikellijnen staat een kolom **i** (prijs inclusief btw j/n): op bons en facturen zijn prijzen exclusief, op de kassa inclusief.
- Gekende hinder bij zoeken: als een zoekterm zowel exact als als deel van andere namen voorkomt, moet je de keuze twee keer bevestigen.

(02-07-2026, ca. 00:00–00:09 en 00:29–00:31; 23-06-2026, ca. 00:34–00:37)

---

## 6. Leveringsbons (Hoofdmenu voorraad > 8 Facturatie > 1)

Welke punten onder 8 staan, hangt af van de modules van de klant. Bijna iedereen heeft: leveringsbons, facturen uit leveringsbons en factuur met rechtstreekse ingave.

**Verschil bon ↔ factuur:** een bon kan aangepast en geschrapt worden; een factuur is definitief zodra ze geboekt is (wettelijk mag een factuur die aan de klant bezorgd is niet meer gewijzigd worden). Het maken van een bon en van een factuur verloopt identiek.

### 6.1 Nieuwe bon – kopscherm
Klant ingeven (naam + **Tab** of **F7** zoekt), **F8**. In de praktijk: klant ingeven en F8, F8; de rest staat standaard goed.

| Veld | Betekenis |
|---|---|
| Bonnummer, datum | automatisch |
| **Mag gefactureerd worden** | staat dit uit, dan wordt de bon nog niet meegenomen bij het factureren. Grotere klanten laten dit standaard uit staan en zetten het aan zodra het leeggoed verwerkt is. |
| Afdrukken j/n | |
| Vaste teksten | nummers van maximaal twee teksten (uit 1–4) die op het document komen. De teksten zelf: Hoofdmenu > **+** (parameters) > **4** facturatieparameters. Tekst 3 en 4 kunnen door Jamadata vast op alle documenten gezet zijn (enkel in de programmatie te zien). |
| Aantal exemplaren | |
| Globale btw | 99 = btw volgens artikelfiche (normale waarde) |
| Exportfactuur | aangevinkt = geen btw |
| Ontvangen voorschot | wordt enkel afgedrukt |
| Voldaan j/n | drukt "voldaan" af |
| Prijs op bon j/n | komt van de klantfiche |
| Klantentoer | enkel zichtbaar als toeren gebruikt worden |

### 6.2 Tussenscherm
- De **memo** van de klant wordt getoond (nooit afgedrukt; ook de interne tekst "afhaling" – bv. waar de sleutel ligt – wordt enkel op het scherm getoond, tenzij je kiest "voeg afhaling toe").
- Het **leveradres** kan hier voor dit ene document gewijzigd worden; de klantfiche verandert niet.
- **Referentie** (bv. bestelnummer van de klant), **leveringskost**, **filiaal/depot** waaruit de stock genomen wordt (standaard depot; per werkpost instelbaar), **chauffeur** (afkorting, wordt afgedrukt).

### 6.3 Artikellijnen
- Lijn: **aantal** | **eenheid** (leeg = bak, **S** = stuk, **P** = palet) | **artikelcode**, of (deel van) de naam + Enter om te zoeken.
- Een palet wordt omgerekend naar bakken volgens "aantal per palet" op de artikelfiche.
- Bij stuks rekent het pakket de stukprijs en het leeggoed per stuk.
- **F9** in het lijnenscherm: bestelbon/leeggoed (zie 6.5). **Tab, dan `+`** opent extra functies:
  - artikels laden uit de **historiek** van de klant (handig bij telefonische bestellingen die elke week gelijkaardig zijn), uit een vorige factuur, een offerte, een verhuurbon of een Excel-bestand;
  - **sorteren** op code, omschrijving, groep, plaats magazijn, leverancier, producent;
  - **vernieuw alle prijzen/kortingen van deze bon** (voor een oude bon waarvan de prijzen ondertussen gewijzigd zijn);
  - memo/afhaling/historiek van de klant tonen.
- Lijnen die met een sterretje beginnen zijn tekstlijnen. Een lijn met een onbestaand artikel blokkeert: het artikel opzoeken of de lijn wissen met **F4**.

### 6.4 Afwerken
- **F8** → eindscherm (referentie, voldaan, datum) → **F8 neem aan**.
- Afhankelijk van de instelling drukt het pakket eerst een **laadbon** (om te picken in het magazijn, gesorteerd volgens plaats magazijn als dat is ingevuld) en daarna de **leveringsbon** voor de klant (met onderaan de leeggoedtabel waarop de chauffeur het teruggenomen leeggoed noteert).
- Na de afdruk: "opnieuw aanpassen", of opslaan zonder herafdruk (F5; let op de toetsen onderaan het scherm). **F6 = weggooien**: de bon is dan niet bewaard, ook al ligt de afdruk al op de printer – typische bron van "ik heb een papier maar de bon staat niet in het systeem".
- Wijzigingen aan de vaste teksten in de parameters worden pas gebruikt in een nieuw gestarte bon.

### 6.5 Bon aanpassen (leeggoed terug) en schrappen
- Facturatie > Leveringsbons > aanpassen: klant ingeven, of **geen klant + F8 = lijst van alle klanten met openstaande bons**.
- Teruggebracht leeggoed: een lijn met **negatief aantal** op het leeggoedartikel, of **F9 leeggoed**: zet het leeggoed van de bon automatisch negatief; de aantallen kunnen dan nog aangepast worden.
- Bij het bewaren van een aangepaste bon wordt standaard **niet** afgedrukt (er volgt toch een factuur); F9 drukt de bon wel af, F5 de laadbon.
- Schrappen: apart punt onder Leveringsbons.

(23-06-2026, ca. 00:23–00:49; 02-07-2026, ca. 00:33–00:38)

---

## 7. Factureren

### 7.1 Facturen uit leveringsbons
Facturatie > "Afdrukken facturen uit leveringsbons": **klant per klant (1)** of **per serie (S)**.
- Klant per klant: klant kiezen; het pakket neemt **alle bons van die klant tot en met de einddatum** samen op **één factuur**.
- Staat op de klantfiche een **facturatieklant**, dan wordt de factuur automatisch op die klant gemaakt.
- De factuur past de stock aan en wordt geboekt.
- Selecties voor seriefacturatie: periode bons, facturatietijdstip van de klant (direct, wekelijks, halfmaandelijks, maandelijks), enkel voldane bons, enkel bons van de kassa.
- **Een gefactureerde bon verdwijnt uit het systeem.**

**Vraag: "ik wil niet alle bons op dezelfde factuur".** Twee oplossingen:
1. Op de bons die nog niet mee mogen **"mag gefactureerd worden" uitzetten** (via bon aanpassen).
2. Bij het factureren de **periode van de bons** (van–tot datum) beperken.

Een scherm waarin de bons één voor één aangevinkt worden bestaat als maatwerk bij sommige klanten, niet standaard. (02-07-2026, ca. 00:10–00:18)

**Seriefacturatie per ongeluk gestart – wat kan nog?**
Van het bonbestand wordt in de back-up **maar één kopie** bijgehouden (van al het andere meerdere). Belt de klant onmiddellijk: laat de **back-up-USB-stick meteen uittrekken**, vóór de volgende back-up de kopie overschrijft, en controleer de datum van het bonbestand op de stick (of in de online back-up bij Jamadata). Is dat bestand van vóór de facturatie, dan kan het teruggezet worden; anders niet. Komt ongeveer één keer per jaar voor. (02-07-2026, ca. 00:19–00:21)

### 7.2 Factuur met rechtstreekse ingave (Facturatie > 3)
Zelfde schermen als een bon, maar het resultaat is meteen een factuur (niet aanpasbaar). Klant, F8, F8, artikels, F8, F8; na de afdruk is ze geboekt.

**Creditnota** = een factuur met een **negatief eindbedrag**: gewoon een factuur maken met negatieve aantallen; de titel van het document wordt automatisch "Creditnota". (23-06-2026, ca. 00:52–00:53; 02-07-2026, ca. 00:56)

### 7.3 Herafdrukken van facturen
Facturatie > **H** (herafdrukken facturen) > 1 > 1 > klant, F8 > factuur kiezen > F8. Wis met F6 een nog ingevuld nummer om de volledige lijst te zien. Vanuit de herafdruk kan de factuur opnieuw naar pdf, mail of Peppol. Hetzelfde kan vanuit de boekhouding (punt 4, icoon bij de factuur) – zie `opleiding-zomer-boekhouding.md`. (02-07-2026, ca. 00:11)

### 7.4 Overige punten onder Facturatie
- Facturen uit bons van de Icone-kassa (oud offline systeem): zie `opleiding-zomer-kassa.md`.
- **Kredietbeperking**: tekst op de factuur dat bij betaling vóór de vervaldag een bedrag afgetrokken mag worden; bij een klein aantal (grotere) klanten in gebruik.
- Creditnota's van de uitgestelde korting, facturen van groothandel naar kleinhandel, toeren met PDA: optionele modules bij een handvol klanten; lees de handleiding achter `?` wanneer er een vraag over komt.

(23-06-2026, ca. 00:52–00:56)

---

## 8. Coca-Cola-orders (koppeling via API)

**Wat:** vertegenwoordigers van Coca-Cola noteren bij horecaklanten bestellingen en delen kortingsbons uit. Die orders worden bij Coca-Cola geregistreerd en door Jamadrink via een API opgehaald, zodat de drankenhandel er een leveringsbon van maakt.

**Waar:** Facturatie > 1 Leveringsbons > inbrengen van een nieuwe bon > **Coca-Cola-icoon rechtsonder**. Handleiding achter `?`.
1. Lijst met openstaande orders per klant. Het **download-icoon rechtsboven** controleert opnieuw via de API of er nieuwe orders zijn.
2. Wat in het **rood** staat moet nog gekoppeld worden (koppel-icoon): eerst de **klant** (naam bij Coca-Cola ↔ klant in het pakket), dan de **artikels**. De koppeling wordt onthouden; het is eenmalig werk per klant en per artikel.
3. **F8 verwerken**: het pakket maakt een bon voor de gekoppelde klant en doorloopt de gewone bonschermen. De orderlijnen staan erin (kortingsbons als lijn met negatief bedrag, tekstlijnen met sterretje). Een lijn waarvan het artikel niet gekoppeld is, blokkeert: artikel zoeken of lijn wissen (F4).
4. Na het bewaren vraagt het pakket of het order **als ingegeven gemarkeerd** mag worden; dat wordt teruggemeld aan Coca-Cola.

**Meest gestelde vraag:** een order blijft in de lijst staan terwijl de bon al gemaakt/gefactureerd is. Oplossing: het order openen > **`+` rechtsonder** > onderste punt **"Schrap dit order"**.

Let op: twee keer op het Coca-Cola-icoon drukken binnen dezelfde bon laadt het order twee keer in.

(02-07-2026, ca. 00:21–00:40)

---

## 9. Omzetfiches en klantentoeren (Basisgegevens)

- **Klantomzetfiches**: bestaan in de laagste pakketversie (ca. 10 % van de klanten; de meesten hebben statistieken en historiek). Houden per klant en per artikel de omzet bij over een periode die de klant **zelf bepaalt door de fiches te wissen** (meestal per jaar). Te vroeg of te laat wissen geeft verkeerde cijfers. Gebruik: afdrukken van de lijst voor een klant (bruto prijs, accijns, korting, netto, uitgestelde korting).
  - Probleem "omzetfiche is leeg": per ongeluk gewist. Jamadata kan de fiches **opnieuw laten opbouwen uit de facturen** via een verborgen functie bij het herafdrukken van facturen (interne handeling; exacte toets te verifiëren).
- **Klantentoeren**: een toer krijgt een vrije naam (dag, dagdeel, vrachtwagen, …) en bevat klanten (toevoegen met Tab). Afdruk met postcode en gemeente. Als de optie in de facturatie aanstaat, vraagt een nieuwe bon naar de toer en toont het pakket de klanten van die toer om er één voor één bons voor te maken. Weinig gebruikt, vooral bij grotere klanten. De volgorde binnen een toer bepaalt de gebruiker zelf.

(23-06-2026, ca. 00:18–00:23)

---

## 10. Statistieken doorsturen naar leveranciers

**Waar:** Hoofdmenu voorraad > 4 (statistieken/historiek): onderaan het scherm staan iconen voor **Prik&Tik, Haacht, Coca-Cola en AB InBev**. Elke leverancier wil de verkoopcijfers in zijn eigen formaat. Per koppeling: `?` = handleiding, **tandwiel = parameters**, een knop om het Excel/CSV-bestand te maken en te bekijken, en een knop om door te sturen.

| Leverancier | Hoe het vertrekt |
|---|---|
| Haacht | via SFTP: adres, poort (22), gebruikersnaam en wachtwoord staan in de parameters (tandwiel) en in de handleiding |
| Coca-Cola | via API; periode van maand tot maand |
| AB InBev | het pakket schrijft een CSV weg; de klant uploadt die zelf op het platform dat de cijfers voor AB InBev verzamelt |

**Fout "doorsturen van de statistieken niet gelukt" (Haacht), bv. na verhuis van de server naar een cloudomgeving:**
1. De parameters staan in het pakket; die veranderen niet door een verhuis. Verdacht is de nieuwe omgeving (uitgaand verkeer op poort 22 geblokkeerd).
2. Geef de IT'er van de klant het protocol (SFTP) en de gegevens uit de parameters.
3. Test op de server met een SFTP-programma (bv. FileZilla) met dezelfde gegevens. Lukt het daar wel maar vanuit het pakket niet → probleem in het programma, doorgeven aan ontwikkeling. Lukt het daar ook niet → netwerk/firewall van de klant.
4. Dezelfde maand opnieuw doorsturen kan geen kwaad. Het aanmaken duurt lang (alle klanten worden doorlopen).

(30-06-2026, ca. 00:13–00:22)

---

## 11. Jaarafsluiting

**Waar:** Hoofdmenu voorraad > A (periodieke werkzaamheden) > 1; achter het `?` staat de volledige tekst die ook als brief naar de klanten gaat. Inventaris: A > 2 (met eigen `?`). Deze vragen komen vanaf half december en bij klanten met een gebroken boekjaar op het einde van een kwartaal.

- Voorwaarde: **alle facturen en alle bons van het oude jaar moeten gemaakt zijn.**
- Het punt vraagt o.a. een kopie (bij klanten met online back-up waarvan de back-up binnen is, is die eerste stap in principe niet nodig) en of het **nummer van de verkoopfacturen en van de bons op nul** gezet moet worden; de overige vinkjes blijven aan.
- Het uitvoeren zelf gaat snel; het werk zit in het overlopen met de klant of alles gedaan is.
- Controle nadien, samen met de klant: is de jaarkopie gemaakt (map met het jaartal), en staan de nummers op nul? Dat laatste toon je door een nieuwe factuur (rechtstreekse ingave) en een nieuwe bon te starten en naar het nummer te kijken, zonder ze te bewaren.

(09-07-2026, ca. 00:13–00:16; 25-06-2026, ca. 00:09; 09-06-2026, ca. 00:55)

---

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):
- Kennisoverdracht Jamadata-20260609_100321-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260618_101035-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260623_100457-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260625_102119-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260630_102207-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260702_110347-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260709_150648-Opname van vergadering.txt
