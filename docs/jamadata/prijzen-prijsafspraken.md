# Prijsafspraken en kortingen per klant (Jamadrink)

Gebruik dit document voor: vragen over hoe Jamadrink de korting of prijs van een klant bepaalt (groep, klantenfiche, artikelfiche, prijsafspraken), in welke volgorde kortingen voorrang hebben, hoe je prijsafspraken bekijkt, toevoegt, kopieert, afdrukt of schrapt, wat een uitgestelde ("semestriële") korting is en hoe daar creditnota's van gemaakt worden, en wat er met vaste prijsafspraken gebeurt bij een prijswijziging.

Herkomst: dit document combineert de geschreven gebruikershandleiding JAMADRINK 2.0 (hoofdstuk V.9.5 "Beheer prijsafspraken" en de extra nota's "Werking van kortingen" en "Vaste prijs omzetten naar percentage korting"), een opgenomen interne opleiding (uit opleiding, 24-10-2025) en de handleiding 0240B. Menunummers en toetsen in de sectie "Menu Beheer prijsafspraken" komen uit de geschreven handleiding. Wat enkel uit de opleiding komt, is zo gemarkeerd. Waar handleiding en opleiding elkaar tegenspreken, staat dat uitdrukkelijk vermeld (zie ook de sectie "Tegenstrijdigheden tussen de bronnen").

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
- een **merk/fabrikant** (wie het produceert),
- of een **combinatie** van bovenstaande (volgens de handleiding).

"Klant" is altijd een verplicht veld. Een korting kan meteen gelden of pas **vanaf een bepaalde datum** (handleiding, V.9.5.2.1).

De prijsafspraken van een klant zijn ook te openen vanuit de klantenfiche (V.9.2.1): bij de extra opties van de detailfiche staat **Prijsafspraken** (overzicht van alle prijsafspraken van deze klant).

De meeste afspraken worden op groep of op artikel gemaakt; op leverancier of merk/fabrikant komt minder voor.

## Voorrangsvolgorde van kortingen

Van hoogste naar laagste voorrang:

1. Prijsafspraak op **artikel**
2. Prijsafspraak op **leverancier** (of merk/fabrikant)
3. Prijsafspraak op **groep**
4. **Algemene korting** op de klantenfiche

Deze volgorde staat letterlijk in de gebruikershandleiding JAMADRINK 2.0 ("Werking van kortingen": 1 artikel, 2 leverancier, 3 groep, 4 klant; 1 heeft de hoogste prioriteit) en komt overeen met de opleiding.

Regels:
- De meest specifieke afspraak **vervangt** de minder specifieke. Kortingen **stapelen niet op** (handleiding: "behalve bij enkele uitzonderingen", zie de combinatie vaste prijs + percentage en acties hieronder) en het is ook **niet "de hoogste wint"**. Een korting op het artikel zorgt dat alle andere kortingen genegeerd worden.
- Voorbeelden uit de handleiding (bak bier van 10 euro):

  | Situatie | Klant betaalt | Toegepast |
  |---|---|---|
  | Geen korting | 10,00 | – |
  | Klant 10 % | 9,00 | 10 % |
  | Klant 10 %, leverancier 12 % | 8,80 | 12 % |
  | Klant 10 %, groep 15 %, vaste prijs 8,50 op het artikel | 8,50 | vaste prijs |
  | Klant 10 %, vaste prijs 8,50 op het artikel, actie met 20 % korting op deze bak | 6,80 | vaste prijs met 20 % korting |

- Voorbeeld uit de opleiding: klant heeft 22 % algemeen, groep "alcoholvrij" 10 % → voor die groep geldt 10 %. Groep "frisdrank in bak" 24 %, leverancier Coca-Cola 25 % → voor Coca-Cola-artikels geldt 25 %.
- **Inconsistentie in de handleiding zelf (te verifiëren)**: één voorbeeldrij geeft bij "klant 10 %, groep 15 %, leverancier 12 %" als resultaat 7,50 euro met "15 % korting". Dat klopt niet met de opgegeven volgorde (leverancier vóór groep → 12 % = 8,80 euro) en ook niet rekenkundig (15 % van 10 euro = 8,50). Volg de genummerde volgorde, die ook door de opleiding bevestigd wordt; test bij twijfel op een proefbon.
- Staat er op een artikellijn binnen een afspraak **niets** ingevuld, dan valt het artikel terug op het volgende niveau (groep/leverancier/algemene korting). Wil je echt géén korting, dan moet je **"geen korting"** zetten (F10, zie verder).
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
- **Combinatie vaste prijs + percentage** kan (bevestigd door handleiding en opleiding): heeft een artikel een percentage én een vaste prijs, dan wordt het percentage gegeven **op de vaste prijs** (opleiding: vaste prijs 3,30 met nog 5 % korting daarop). Enkel een percentage → korting op de normale standaardprijs. Enkel een vaste prijs → de klant betaalt de vaste prijs, los van de standaardprijs.

Kolomnamen in de lijsten: **Kort%** = korting in percentage, **Vaste VP** = vaste verkoopprijs, **Kort/hl** = korting per hectoliter.

### Detailscherm van een afspraak (F9 detail)

- Toont dezelfde gegevens onder elkaar (in plaats van in kolommen) plus de extra velden. De vaste prijs heet hier **"Speciale verkoopprijs"**, het percentage **"Korting in percentage"**.
- **F7 aanpassen/raadplegen**: wisselt tussen raadplegen en aanpassen en toont met welk kortingspercentage een vaste prijs overeenkomt (bv. "20 euro = 46,8 % korting").
- **F10 korting**: heft een eerder gezette "GEEN korting" weer op.
- **F8 schrijf weg**: de fiche opslaan en terug naar de lijst.
- **Prijs niet aanpassen via prijsbeheer tot [datum]**: vinkje + datum. Een vaste prijs met dit vinkje wordt bij een prijswijziging (V.3.3/V.3.4/prijzenbestand) niet aangepast tot die datum. Gebruikt voor raamovereenkomsten, bv. met gemeentes, die een jaar vaste prijs eisen (uit opleiding, 24-10-2025).
- **Vrije opmerking** (kort veld): bv. nummer van de raamovereenkomst of het contract (uit opleiding).

### Vaste prijs omzetten naar een percentage (prijs voor de klant blijft gelijk)

Procedure uit de gebruikershandleiding:

1. Selecteer de prijsafspraaklijn in de lijst.
2. Kies **F9 detail**; de detailfiche opent.
3. Kies **F7 aanpassen/raadplegen**. "Speciale verkoopprijs" toont het vaste bedrag.
4. Noteer de waarde bij **"Korting in percentage"**.
5. Kies opnieuw **F7 aanpassen/raadplegen**.
6. Wis de inhoud van "Speciale verkoopprijs".
7. Vul bij "Korting in percentage" de genoteerde waarde in.
8. Kies **F7 aanpassen/raadplegen**.
9. **Controleer** of "Speciale verkoopprijs" nu dezelfde waarde toont als oorspronkelijk.
10. Kies **F8 schrijf weg**. In de lijst is het percentage ingevuld en de vaste prijs leeg.

Let op: in de opleiding (24-10-2025) gaf deze terugrekening in de live demo **niet** dezelfde prijs terug; de oorzaak is niet achterhaald. Stap 9 (controle) is dus essentieel: klopt de prijs niet, schrijf dan niet weg.

### Advies: percentage of vaste prijs?

- Met een **percentage** moet er bij een prijsverhoging niets aangepast worden: de korting volgt de nieuwe prijs.
- Een **vaste prijs** moet bij elke prijsverhoging overlopen worden, anders verkoopt de handelaar met te weinig marge of verlies. Daarom overloopt het prijsbeheer de vaste afspraken bij elke prijswijziging (zie `prijzen-prijswijzigingen-en-accijnzen.md`).
- Advies van de opleider aan klanten met veel vaste prijzen: zet ze om naar percentages.

## Menu Beheer prijsafspraken (V.9.5)

Hoofdmenu V.9.5 volgens de gebruikershandleiding JAMADRINK 2.0 (het menu "kan volgende items bevatten"; niet elke installatie toont alles):

| Toets | Menu-item |
|---|---|
| 1 | Aanpassen/bekijken van een bestaande fiche |
| 2 | Bijvoegen van een nieuwe fiche |
| 3 | Schrappen van een bestaande fiche |
| 4 | Afdrukken van een lijst |
| 9 | Globaal aanpassen van de prijsafspraken |
| A | Schrappen van ALLE prijsafspraken van één klant en/of artikel |
| K | Kopiëren van ALLE prijsafspraken van één klant naar een andere |
| L | Kopiëren van ALLE prijsafspraken van één artikel naar een ander |

Opmerking over de handleiding: de twee submenu-tabellen staan er **verwisseld** in (de tabel onder "V.9.5.2 Toevoegen" toont de keuzes van bewerken en omgekeerd). De genummerde paragraaftitels (V.9.5.1.1–3 en V.9.5.2.1–4) zijn wel consistent en komen overeen met de opleiding; die zijn hieronder gevolgd.

### V.9.5.2 – Bijvoegen van een nieuwe fiche

| Menupunt | Werking |
|---|---|
| **V.9.5.2.1** Afspraak per afspraak | Individuele prijsafspraak: klant (verplicht) + artikel, leverancier, merk, productgroep of een combinatie; kortingen invullen; geldig meteen of vanaf een datum. |
| **V.9.5.2.2** Via een lijst van artikels | Zoekscherm waarin minimaal de klant ingevuld wordt; optioneel beperken tot één groep, leverancier of merk. Je krijgt alle producten die aan de filter voldoen, **inclusief de reeds bestaande afspraken**, en vult per artikel Kort%, Vaste VP of Kort/hl in. |
| **V.9.5.2.3** Via een lijst van groepen | Klant kiezen; je krijgt alle productgroepen (bestaande groepsafspraken inbegrepen) en vult per groep de korting in. Aanbevolen als de groepen goed ingedeeld zijn: één lijn i.p.v. honderd artikels apart (advies uit opleiding). |
| **V.9.5.2.4** Alle artikels van een gemaakte offerte | Klant kiezen, daarna de offerte. Je krijgt de lijst van alle producten uit de offerte en kan ze nog aanpassen voor ze prijsafspraken worden. De handleiding verwijst voor offertes naar punt **V.5.6**. In de opleiding kwam eerst nog een bevestigingsvraag om de offerte aan de prijsafspraken toe te voegen. |

### V.9.5.1 – Aanpassen/bekijken van een bestaande fiche

| Menupunt | Werking |
|---|---|
| **V.9.5.1.1** Afspraak per afspraak | Zoekvelden met "Klant" verplicht (automatisch aanvullen met TAB mogelijk); uit de resultaatlijst een fiche aanklikken en bewerken. Weinig gebruikt. |
| **V.9.5.1.2** Via een lijst van de afspraken van 1 klant | **De aanbevolen manier om prijsafspraken te bekijken.** Enkel op klant zoeken. De lijst is alfabetisch gesorteerd op artikelomschrijving en is meteen aanpasbaar. |
| **V.9.5.1.3** Via een lijst van de afspraken van 1 artikel | Enkel op artikel zoeken; toont welke klanten een afspraak hebben op dat artikel. Ook meteen aanpasbaar. |

Hoe de lijst (V.9.5.1.2) te lezen:
- Kolommen: Kort%, Vaste VP, Kort/hl, en volgens de opleiding ook de uitgestelde korting (% of per hectoliter).
- **Lees van onderaan (achteraan) naar bovenaan (vooraan)**: de korting met de laagste voorrang staat helemaal onderaan (meestal de standaardkorting van de klant: direct + uitgesteld), daarboven de afspraken op **groep**, daarboven op **leverancier**, bovenaan de individuele **artikels**. Dit staat zo in de handleiding en in de opleiding.

Toetsen in de lijsten V.9.5.1.2 en V.9.5.1.3 (uit de handleiding):

| Toets | Werking |
|---|---|
| **F10 GEEN korting** | Markeert dat op dit artikel geen korting gegeven wordt. |
| **F9 detail** | Opent de detailfiche van de geselecteerde lijn. |
| **F8 neem aan en stop** | Slaat de gegevens op en verlaat het scherm. |
| **F6 annuleer** | Zet de lijst terug op de waarden van bij het openen. **Sluit het venster niet**; daarna kies je F8 neem aan en stop om het scherm te verlaten. |
| **F2 vorig / F3 volgend** | Bladeren. **Het wisselen van pagina slaat de gegevens die je in de lijst ingaf al op.** |

"GEEN korting" terug ongedaan maken: lijn selecteren → **F9 detail** → **F10 korting** → **F8 schrijf weg**; terug in de lijst is de markering weg.

Let op bij support:
- Deze lijsten zijn **bewerkbaar**; er is geen leesmodus. Laat een klant die enkel wil kijken niets intypen.
- Heeft de klant mogelijk per ongeluk iets ingetypt: **F6 annuleer** herstelt volgens de handleiding de waarden van bij het openen, maar wat vóór een paginawissel (F2/F3) werd ingetypt, is toen al opgeslagen. Of F6 ook dat nog terugdraait, staat niet in de bron (te verifiëren). Laat de klant in dat geval niet verder bladeren en vergelijk met een eerder afgedrukte lijst of een backup.
- Voor enkel raadplegen zonder risico: de afdruk naar PDF (V.9.5.4), of de knop Prijsafspraken op de klantenfiche.

### Schrappen (V.9.5.3 en V.9.5.A)

Schrappen kan **enkel ongedaan gemaakt worden door een back-up terug te zetten**.

- **V.9.5.3 Individueel schrappen**: zoekscherm; een item in de lijst kiezen (of F8 zoek op) geeft de bevestigingsvraag.
- **V.9.5.A Schrappen van alle prijsafspraken van één klant en/of artikel**: zoekscherm met filter op klant en/of artikel; daarna een bevestigingsscherm met de ingevulde zoektermen.
- Toetsen in het bevestigingsscherm: **F1 stop** (terug naar het menu, niets schrappen), **F4 schrap** (schrappen), **F5 behoud** (niet schrappen), **F11 hoofdmenu**.

### Afdrukken van een lijst (V.9.5.4)

- Zoekscherm om te filteren welke gegevens op de lijst komen (opleiding: klant is de meest gebruikte selectie; ook artikel, groep of leverancier).
- Opties voor de afdruk, bv. **voor elke klant een aparte pagina**.
- **F8 begin** drukt af; het PDF-icoon rechtsonder maakt een **PDF** en opent die. Volgens de opleiding kan de lijst ook naar **Excel** (niet vermeld in de handleiding).
- Zelfde opbouw: algemene korting van de klant, verder van onder naar boven groep → leverancier → artikel.

### Kopiëren (V.9.5.K en V.9.5.L)

- **V.9.5.K – van één klant naar een andere**: bronklant en doelklant selecteren. Keuze tussen enkel de **ontbrekende** prijsafspraken kopiëren of de prijsafspraken van beide klanten **volledig gelijkstellen**. Voorbeeld: een nieuwe school binnen een scholengroep.
- **V.9.5.L – van één artikel naar een ander**: bronartikel en doelartikel selecteren; optie om de afspraken met **vaste prijs over te slaan** (enkel de percentuele kopiëren). Gebeurt enkel voor wie op het doelartikel nog **geen** prijsafspraak heeft. Ook hier vermeldt de handleiding de keuze ontbrekende kopiëren / volledig gelijkstellen. Voorbeeld: een product dat vervangen wordt door een opvolger.
- Na het kopiëren kom je terug in het menu. Volgens de opleiding toont het programma vooraf wat het gaat doen.

### Globaal aanpassen van de prijsafspraken (V.9.5.9)

Past de bedragen in de prijsafspraken globaal aan met een **Factor** en/of een **Offset**:

`Nieuwe waarde = (Oude waarde x Factor) + Offset`

Voorbeeld uit de handleiding: oude waarde 200, factor 1,01, offset 50 → (200 x 1,01) + 50 = 252. Een factor 1,10 is dus +10 %; de offset is een vast bedrag dat erbij komt (de handleiding noemt de offset in de tekst een "percentage", maar de formule en het voorbeeld tonen een opgeteld bedrag; de opleiding spreekt van een bedrag in euro).

Volgens de opleider wordt dit punt in de praktijk al jaren niet meer gebruikt. Er is geen voorbeeldweergave vooraf beschreven; neem eerst een backup.

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
| Waar bekijk ik alle afspraken van een klant? | V.9.5.1.2 (Aanpassen/bekijken → Via een lijst van de afspraken van 1 klant), de lijst afdrukken naar PDF (V.9.5.4), of de knop Prijsafspraken op de klantenfiche. |
| Uitgestelde korting te laag | Zie hierboven: afspraak is later ingegeven; herbereken a.d.h.v. huidige prijsafspraken. |
| Prijsafspraken per ongeluk geschrapt | Niet herstelbaar in het programma; enkel via backup. |
| Nieuwe klant moet dezelfde afspraken krijgen als een bestaande | V.9.5.K, kopiëren van klant naar klant. |
| "GEEN korting" staat verkeerdelijk op een artikel | Lijn selecteren → F9 detail → F10 korting → F8 schrijf weg. |
| Welke klanten hebben meer dan x % algemene korting? | Klanten uitschrijven naar Excel (V.9.2.7) met filter "Ondergrens (groter dan)" op het veld "Kortings %" (voorbeeld uit de handleiding). |

## Tegenstrijdigheden tussen de bronnen

| Onderwerp | Gebruikershandleiding JAMADRINK 2.0 | Opleiding 24-10-2025 | Hoe mee omgaan |
|---|---|---|---|
| Voorrangsvolgorde | Genummerd: artikel, leverancier, groep, klant. Maar één voorbeeldrij laat groep 15 % winnen van leverancier 12 % en rekent 7,50 i.p.v. 8,50. | Artikel, leverancier, groep, klant. | Genummerde volgorde volgen; het voorbeeld is vermoedelijk een fout in de handleiding. |
| Submenu's van V.9.5.1 en V.9.5.2 | Tabellen staan verwisseld; paragraaftitels zijn correct. | Komt overeen met de paragraaftitels. | Paragraafnummers volgen (zoals in dit document). |
| Vaste prijs omzetten naar percentage (F7) | Stappenplan waarbij de prijs gelijk blijft. | Live demo gaf niet dezelfde prijs terug; oorzaak onbekend. | Altijd de controlestap uitvoeren vóór F8 schrijf weg. |
| Offset bij globaal aanpassen | Tekst zegt "percentage", formule en voorbeeld tonen een opgeteld bedrag. | Bedrag in euro (bv. 20 cent). | Formule volgen: bedrag. |
| Kopiëren | Keuze "ontbrekende kopiëren" of "volledig gelijkstellen". | Zegt enkel dat alles gekopieerd wordt en dat vooraf getoond wordt wat er gebeurt. | Geen echte tegenspraak; handleiding is vollediger. |
| Uitvoer van de lijst | Afdrukken of PDF. | Ook Excel. | Excel-optie te verifiëren op het scherm. |
| Creditnota's uitgestelde korting | 0240B: punt onder V.8 "Aanmaken creditnota's van uitgestelde kortingen" (geen nummer). | Punt 7 onder facturatie, benaming "kredietnota's van semestriële kortingen". | Menunummer te verifiëren; de gebruikershandleiding behandelt dit punt niet in het gelezen deel. |

Niet in de geschreven handleiding (gelezen deel), dus enkel uit de opleiding: "algemene korting toegestaan" op de groep, "Blokkeer korting" op de artikelfiche, tussenkomst leverancier, "prijs niet aanpassen via prijsbeheer tot datum", het negatieve investeringsbedrag bij uitgestelde korting.

## Bronnen

- `gebruikershandleiding JAMADRINK 2.0.docx` — Jamadrink (hoofdstuk V.9.5 Beheer prijsafspraken, p. 23–29; extra nota's "Werking van kortingen" en "Vaste prijs omzetten naar percentage korting", p. 75–76; klantenfiche V.9.2.1 en filtervoorbeelden, p. 20 en 71)
- `Prijsafspraken-20251024_131949-Opname van vergadering.txt` — Claude/Transcripties opleidingen (uit opleiding, 24-10-2025; volledig gelezen)
- `0240B - Aanmaken creditnota's van uitgestelde kortingen.docx` — Jamadrink/Handleidingen modules
- `00_CHECKPOINT_UITLEG_EN_PRIJSAFSPRAKEN.md` — 00_START_CLAUDE/18_UITLEG_EN_PRIJSAFSPRAKEN (aandachtspunt F2/F3; nu rechtstreeks bevestigd in de handleiding)
- `00_CHECKPOINT_BEKIJKROUTE.md` — 00_START_CLAUDE/19_PRIJSAFSPRAKEN_BEKIJKROUTE (bekijkroute, lijst is bewerkbaar)
- `0296A - Factuurpromoties.docx` — Jamadrink/Handleidingen modules (voorrang promotieprijs)
