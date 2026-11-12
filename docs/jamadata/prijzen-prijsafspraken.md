# Prijsafspraken en kortingen per klant (Jamadrink)

Gebruik dit document voor: vragen over hoe Jamadrink de korting of prijs van een klant bepaalt (groep, klantenfiche, artikelfiche, prijsafspraken), in welke volgorde kortingen voorrang hebben, hoe je prijsafspraken bekijkt, toevoegt, kopieert, afdrukt of schrapt, wat een uitgestelde ("semestriële") korting is en hoe daar creditnota's van gemaakt worden, en wat er met vaste prijsafspraken gebeurt bij een prijswijziging.

Belangrijk: het grootste deel van dit document komt uit een opgenomen interne opleiding (uit opleiding, 24-10-2025), aangevuld met de handleiding 0240B en de AI-gecureerde checkpoints 18 en 19. Exacte toetsen en schermnamen uit de opleiding zijn waar nodig gemarkeerd als "te verifiëren". Er is geen aparte modulehandleiding "prijsafspraken" in de map Handleidingen modules; de algemene gebruikershandleiding JAMADRINK 2.0 bevat wel een hoofdstuk (niet in dit document verwerkt).

## De opbouw van kortingen: vier niveaus

Een korting voor een klant wordt opgebouwd van algemeen naar specifiek. Alles zit onder hoofdmenu voorraadbeheer, punt 9 (basisbestanden), behalve de prijswijzigingen (punt 3).

### 1. Artikelgroep: mag er algemene korting op? (V.9, groepen)

- Op elke artikelgroep staat de vraag **"Algemene korting toegestaan op deze groep"** (in de groepenlijst de kolom korting J/N).
- Staat dit **uit** (N), dan krijgt een klant met een algemene korting op de klantenfiche **nooit** korting op artikels van die groep.
- Typische groepen zonder korting: leeggoed, tabakswaren, snoep (voorbeelden uit de opleiding).
- Uitzondering: een **prijsafspraak op een specifiek artikel** van zo'n groep overrulet dit wel.

### 2. Klantenfiche: algemene korting (V.9.2)

- **Kortingspercentage** op de klantenfiche = directe korting op alle groepen waar algemene korting toegestaan is.
- **Semestriële korting** = in werkelijkheid een **uitgestelde korting** (het label "semestrieel" is historisch). Zie de sectie "Uitgestelde korting" hieronder.
- **Periode semestriële korting**: maand, kwartaal, (halfjaar) of jaar (J = jaar); bepaalt voor welke klanten in één keer creditnota's gemaakt kunnen worden.

### 3. Artikelfiche: korting blokkeren voor iedereen (V.9.3)

- Op de artikelfiche staat een vinkje/knop **"Blokkeer korting"**; wanneer het aan staat, wordt het **rood**.
- Effect: op dit artikel wordt voor **alle klanten** geen korting gegeven, ook al krijgt de hele groep korting.
- Het is één klik om aan of uit te zetten, zonder bevestigingsvraag. **Veelvoorkomende supportvraag**: "op dit product werkt de korting niet" → controleer of "Blokkeer korting" per ongeluk aangeklikt is.

### 4. Prijsafspraken (V.9.5)

Een prijsafspraak is altijd een combinatie van **één klant** met één van:
- een **artikel**,
- een **artikelgroep**,
- een **leverancier** (bij wie je het artikel aankoopt),
- een **merk/fabrikant** (wie het produceert).

De meeste afspraken worden op groep of op artikel gemaakt; op leverancier of merk/fabrikant komt minder voor.

## Voorrangsvolgorde van kortingen

Van hoogste naar laagste voorrang:

1. Prijsafspraak op **artikel**
2. Prijsafspraak op **leverancier** (of merk/fabrikant)
3. Prijsafspraak op **groep**
4. **Algemene korting** op de klantenfiche

Regels:
- De meest specifieke afspraak **vervangt** de minder specifieke. Kortingen worden **niet opgeteld** en het is ook **niet "de hoogste wint"**. Voorbeeld uit de opleiding: klant heeft 22 % algemeen, groep "alcoholvrij" 10 % → voor die groep geldt 10 %. Groep "frisdrank in bak" 24 %, leverancier Coca-Cola 25 % → voor Coca-Cola-artikels geldt 25 %.
- Staat er op een artikellijn binnen een afspraak **niets** ingevuld, dan valt het artikel terug op het volgende niveau (groep/leverancier/algemene korting). Wil je echt géén korting, dan moet je **"geen korting"** zetten (F10, zie verder).
- Deze volgorde wordt bevestigd door zowel de gebruikershandleiding JAMADRINK 2.0 als een tweede opleiding (bron: checkpoint 18).
- Een actieve **factuurpromotie** (V.3.9) komt nog bovenop: een speciale promotieprijs gaat vóór een prijsafspraak met speciale prijs, en promotiekortingen worden ná de klantkortingen afgetrokken. Zie `promoties.md`.

## Soorten korting in een prijsafspraak

| Soort | Uitleg |
|---|---|
| Korting in % | Directe procentuele korting op de factuur |
| Vaste verkoopprijs | Vaste prijs voor deze klant (bv. 150 euro voor een vat van 50 liter) |
| Korting per hectoliter | Bedrag in euro per hectoliter (bv. 10 euro/hl) |
| Uitgestelde korting in % | Niet op factuur; bijgehouden in statistieken en achteraf gecrediteerd |
| Uitgestelde korting per hectoliter | Idem, in euro per hectoliter |
| Tussenkomst leverancier (% of bedrag per vat/eenheid) | Het deel van de korting dat de leverancier/brouwer voor zijn rekening neemt. De klant ziet hier niets van; het wordt bijgehouden in een statistiek zodat de drankenhandel het bedrag op het einde van het jaar bij de leverancier kan terugvorderen. Enkel zichtbaar in het detailscherm (F9 detail). |

- Wat op het scherm niet invulbaar is, is voor dat type afspraak niet mogelijk. Bij een afspraak op groep/leverancier kan bijvoorbeeld geen speciale verkoopprijs en geen uitgestelde korting in geld ingegeven worden.
- **Combinatie vaste prijs + percentage** kan: de korting in % wordt dan nog toegepast op de vaste prijs (voorbeeld uit de opleiding: vaste prijs 3,30 met nog 5 % korting daarop). Tel dit dus niet blind op en sluit het ook niet uit; kijk wat er op de fiche staat.

### Detailscherm van een afspraak (F9 detail)

- Toont dezelfde gegevens onder elkaar (in plaats van in kolommen) plus de extra velden.
- **F7** (raadplegen/aanpassen): toont met welk kortingspercentage een vaste prijs overeenkomt (bv. "20 euro = 46,8 % korting"). Bedoeld om een vaste prijs om te zetten naar een percentage. In de opleiding werkte het terugrekenen niet zoals verwacht (onzeker / te verifiëren).
- **Prijs niet aanpassen via prijsbeheer tot [datum]**: vinkje + datum. Een vaste prijs met dit vinkje wordt bij een prijswijziging (V.3.3/V.3.4/prijzenbestand) niet aangepast tot die datum. Gebruikt voor raamovereenkomsten, bv. met gemeentes, die een jaar vaste prijs eisen.
- **Vrije opmerking** (kort veld): bv. nummer van de raamovereenkomst of het contract.
- **F8** = aannemen/wegschrijven (te verifiëren per scherm).

### Advies: percentage of vaste prijs?

- Met een **percentage** moet er bij een prijsverhoging niets aangepast worden: de korting volgt de nieuwe prijs.
- Een **vaste prijs** moet bij elke prijsverhoging overlopen worden, anders verkoopt de handelaar met te weinig marge of verlies. Daarom overloopt het prijsbeheer de vaste afspraken bij elke prijswijziging (zie `prijzen-prijswijzigingen-en-accijnzen.md`).
- Advies van de opleider aan klanten met veel vaste prijzen: zet ze om naar percentages.

## Menu Beheer prijsafspraken (V.9.5)

De opbouw volgens de opleiding (nummers van submenu's waar genoemd):

### Bijvoegen van een nieuwe fiche

| Keuze | Werking |
|---|---|
| 1. Afspraak per afspraak | Klant + artikel (of leverancier, merk of groep) ingeven en de kortingen invullen. |
| 2. Via de lijst van de artikels | Klant ingeven; zonder verdere selectie worden alle artikels getoond, of beperk tot één groep, leverancier of merk. Je vult de korting per artikel in de lijst in. |
| 3. Op groepen | Klant ingeven; je ziet alle groepen en zet per groep de korting in één lijn. Aanbevolen als de groepen goed ingedeeld zijn: één lijn i.p.v. honderd artikels apart. |
| 4. Alle artikels van een gemaakte offerte inladen in prijsafspraken | Klant ingeven, offerte kiezen (vergrootglas), bevestigen "wenst u deze offerte toe te voegen aan de prijsafspraken". De kortingen uit de offerte worden automatisch prijsafspraken. (Beheer offertes: zie handleiding 0266A.) |

### Aanpassen/bekijken van een bestaande fiche

| Keuze | Werking |
|---|---|
| 1. Afspraak per afspraak | Klant + artikel/leverancier/groep ingeven. Weinig gebruikt. |
| 2. Via een lijst van de afspraken van 1 klant | **De aanbevolen manier om prijsafspraken te bekijken.** Klant ingeven; je krijgt alle afspraken van die klant. |
| Via een lijst van de afspraken van 1 artikel | Toont welke klanten een afspraak hebben op dat artikel. |

Hoe de lijst van één klant te lezen:
- Kolommen: korting in %, vaste verkoopprijs, korting per hectoliter, uitgestelde korting (% of per hectoliter).
- **Lees van onder naar boven**: helemaal onderaan staat de algemene korting van de klantenfiche (direct + uitgesteld), daarboven de afspraken op **groep**, daarboven op **leverancier**, bovenaan de individuele **artikels**. Wat hoger staat, heeft voorrang.
- **F10 "geen korting"** op een lijn: zet uitdrukkelijk "geen korting" voor dat artikel.
- **F9 detail**: detailscherm van de lijn (zie hoger).

Let op bij support:
- Deze lijst is **bewerkbaar**; er is geen afgedwongen leesmodus. Laat een klant die enkel wil kijken niets intypen.
- Volgens de gebruikershandleiding kan bladeren met **F2/F3** in zo'n invoerlijst reeds ingevoerde gegevens opslaan. Adviseer dus geen blind bladeren, bewaren (F8) of annuleren (F6) als de klant mogelijk per ongeluk iets heeft ingetypt en niet duidelijk is op welk scherm hij staat; laat dit beoordelen door een ervaren collega (bron: checkpoints 18 en 19).
- Voor enkel raadplegen zonder risico: gebruik de afdruk naar PDF (zie hieronder).

### Schrappen

- **Schrappen van één fiche**: klant + artikel/leverancier/groep ingeven; verwijdert één lijn. Weinig gebruikt.
- **Schrappen van alle prijsafspraken van één klant of één artikel**: verwijdert in één keer alle afspraken van die klant, of alle afspraken van alle klanten op dat artikel. **Onherroepelijk: weg is weg** (enkel te herstellen via een backup).

### Afdrukken van de lijst

- Selectie op klant (meest gebruikt), artikel, groep of leverancier.
- Uitvoer naar **PDF** of **Excel**.
- Zelfde opbouw: bovenaan de algemene korting van de klant; verder van onder naar boven groep → leverancier → artikel.

### Kopiëren

- **Van klant naar klant**: alle prijsafspraken van een klant kopiëren naar een andere klant (bv. een nieuwe school binnen een scholengroep).
- **Van artikel naar artikel**: alle afspraken van een artikel kopiëren naar een ander artikel (bv. een product dat vervangen wordt door een opvolger).
- Het programma toont vooraf wat het gaat doen.

### Globaal aanpassen van prijsafspraken

Prijzen in afspraken verhogen met een **factor** (1,10 = +10 %) of een **offset** in euro (bv. +0,20). Volgens de opleider al jaren niet meer gebruikt; onzeker of dit nog correct werkt (te verifiëren vóór gebruik, altijd eerst backup).

## Uitgestelde ("semestriële") korting

- Wordt **niet op de factuur** getoond; de klant ziet er niets van. Wordt bijgehouden in de **statistieken**.
- Kan staan op de klantenfiche (algemeen) of in een prijsafspraak (per artikel, groep, leverancier).
- De handelaar kiest de afrekenperiode: per maand, kwartaal, halfjaar of (meestal) jaar. Op het einde trekt hij een statistiek, maakt een creditnota voor het bedrag en betaalt het terug.
- Op de klantenfiche wordt het **opgebouwde bedrag** uitgestelde korting ook bijgehouden. Na het maken van de creditnota hoort dit veld terug **op nul** gezet te worden.
- Praktijk in de sector: bij een **investering** van de drankenhandel bij de klant (frigo's, toog, meubilair) wordt het veld op een **negatief bedrag** gezet (bv. -10.000). Elke factuur telt de uitgestelde korting erbij; als het bedrag op nul komt, is de investering terugbetaald via de uitgestelde kortingen. Zolang krijgt de klant geen creditnota.

### Creditnota's van uitgestelde kortingen aanmaken (aparte, optionele module)

Waar: hoofdmenu voorraadbeheer, punt **8 "Facturatie"**, punt **"Aanmaken creditnota's van uitgestelde kortingen"** (in de opleiding getoond als punt 7 onder facturatie, met de oudere benaming "afdrukken kredietnota's van semestriële kortingen"; menunummer te verifiëren op het scherm).

Stappen:
1. Vul de gewenste **periode** in (bv. 01/01 t.e.m. 31/12).
2. Vul een **klant** in, of laat de klant leeg en kies bij **"Selectie periode korting"** de periode die op de klantenfiches is aangeduid (maand/kwartaal/jaar) om het voor alle klanten met die periode te doen.
3. Optie **"Korting herberekenen aan de hand van de huidige prijsafspraken"**: zie hieronder.
4. Bevestig enkele keren met **F8**. Je komt op het artikelscherm met de kortingen per artikel ("afrekening periodieke korting": per product het verkochte aantal en het overeenkomstige kortingsbedrag).
5. Bevestig; de creditnota kan op het scherm bekeken, afgedrukt of gemaild worden. Elk product staat apart op de creditnota, wat controle door de klant eenvoudig maakt.
6. Zet daarna het opgebouwde bedrag op de klantenfiche terug op nul.

### "De uitgestelde korting klopt niet / is te laag"

Veelvoorkomende discussie. Oorzaak: de uitgestelde korting wordt per factuur berekend met de afspraak **zoals die op dat moment gold**. Is de korting pas op bv. 1 maart op de klantenfiche of in de prijsafspraken gezet, dan is er enkel korting opgebouwd vanaf 1 maart. Het pakket houdt geen logging bij van wanneer een afspraak gewijzigd is, dus dit valt achteraf niet te bewijzen.

Oplossing: vink bij het aanmaken van de creditnota **"korting herberekenen a.d.h.v. de huidige prijsafspraken"** aan. Dan wordt voor de hele periode gerekend met wat er **nu** op de klantenfiche en in de prijsafspraken staat. Dezelfde optie bestaat bij de statistieken (V.4.2 en V.4.3), zie `statistieken-en-historieken.md`.

## Prijsafspraken en prijswijzigingen

- Bij een prijswijziging via V.3.3, V.3.4 of een prijzenbestand worden vaste prijsafspraken één voor één getoond met een voorgestelde nieuwe prijs (winst behouden). F4 = nieuwe prijs aannemen (eventueel eerst overtypen), F6 = afspraak niet aanpassen; in het prijzenbestand-scherm F9 = vaste prijs herstellen.
- Afspraken met "prijs niet aanpassen via prijsbeheer tot [datum]" blijven ongewijzigd tot die datum.
- V.3.5 (definitief maken) wijzigt de prijzen op artikelfiche **en** prijsafspraken.
- Percentages hoeven nooit aangepast te worden.

## Veelvoorkomende vragen

| Vraag | Antwoord / controle |
|---|---|
| Klant krijgt geen korting op één artikel | 1) Staat "Blokkeer korting" aan (rood) op de artikelfiche? 2) Staat "algemene korting toegestaan" uit op de groep? 3) Staat er een afspraak "geen korting" (F10) of een specifiekere afspraak op artikel/leverancier/groep? |
| Klant krijgt een lagere korting dan zijn algemene korting | Een specifiekere prijsafspraak (groep, leverancier, artikel) vervangt de algemene korting, ook als ze lager is. |
| Welke korting geldt: 10 % op artikel of 22 % algemeen? | De artikelafspraak: 10 %. Niet optellen, niet de hoogste nemen. |
| Factuurprijs wijkt af van de prijsafspraak | Controleer of er een factuurpromotie (V.3.9) actief is op de factuurdatum, of er een prijs op datum geldt, en welk prijstype de klant heeft. |
| Waar bekijk ik alle afspraken van een klant? | V.9.5 → Aanpassen/bekijken van een bestaande fiche → Via een lijst van de afspraken van 1 klant (keuze 2), of de lijst afdrukken naar PDF. |
| Uitgestelde korting te laag | Zie hierboven: afspraak is later ingegeven; herbereken a.d.h.v. huidige prijsafspraken. |
| Prijsafspraken per ongeluk geschrapt | Niet herstelbaar in het programma; enkel via backup. |
| Nieuwe klant moet dezelfde afspraken krijgen als een bestaande | Kopiëren van klant naar klant. |

## Bronnen

- `Prijsafspraken-20251024_131949-Opname van vergadering.txt` — Claude/Transcripties opleidingen (uit opleiding, 24-10-2025; volledig gelezen)
- `0240B - Aanmaken creditnota's van uitgestelde kortingen.docx` — Jamadrink/Handleidingen modules
- `00_CHECKPOINT_UITLEG_EN_PRIJSAFSPRAKEN.md` — 00_START_CLAUDE/18_UITLEG_EN_PRIJSAFSPRAKEN (kortingsvolgorde, waarschuwing F2/F3)
- `00_CHECKPOINT_BEKIJKROUTE.md` — 00_START_CLAUDE/19_PRIJSAFSPRAKEN_BEKIJKROUTE (bekijkroute keuze 2, lijst is bewerkbaar)
- `0296A - Factuurpromoties.docx` — Jamadrink/Handleidingen modules (voorrang promotieprijs)
