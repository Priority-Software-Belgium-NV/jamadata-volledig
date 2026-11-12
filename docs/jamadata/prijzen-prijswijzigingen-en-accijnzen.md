# Prijswijzigingen en accijnsverhogingen (Jamadrink, menu V.3)

Gebruik dit document voor: vragen over het wijzigen van aankoop- en verkoopprijzen in Jamadrink, het verschil tussen een directe prijswijziging en een prijswijziging op datum, het definitief maken van nieuwe prijzen (V.3.5), accijnsverhogingen, wat de groene prijs en het kalendericoon op de artikelfiche betekenen, het meenemen van vaste prijsafspraken en deelverpakkingen, het afdrukken van prijslijsten en prijskaartjes met de nieuwe prijzen, en de controle van inhoud en aantal per bak.

Notatie: `V.3.4` betekent Hoofdmenu **V**oorraadbeheer, punt 3 (Beheer prijzen), punt 4.

## Overzicht van het menu Beheer prijzen (V.3)

| Menupunt | Functie |
|---|---|
| V.3.3 | Ingeven directe prijswijzigingen (prijs wijzigt onmiddellijk op de artikelfiche) |
| V.3.4 | Ingeven prijswijzigingen op datum (uitgestelde prijswijziging met ingangsdatum) |
| V.3.5 | Vervangen huidige prijzen door nieuwe (= prijswijzigingen op datum definitief maken) |
| V.3.6 | Lijst prijswijzigingen op datum |
| V.3.7 | Controleprogramma: aankoopprijs artikelfiche vergelijken met aankoopfiche (zie `prijzen-aankoopfiches-en-deelverpakkingen.md`) |
| V.3.9 | Factuurpromoties (zie `promoties.md`) |
| V.3.I | Controleren inhoud en aantal/bak op artikelfiches |
| V.3.D.2 | Prijzenbestand Districo / Belbev verwerken (zie `prijzen-prijzenbestanden-importeren.md`) |

In hetzelfde menu zitten volgens de opleiding ook (exacte menuletters niet in de bron, te verifiëren op het scherm van de klant):
- artikelprijzen aanpassen met een vaste factor (bv. alle horecaprijzen of alles van één leverancier x %): werkt **onmiddellijk**, niet op datum;
- artikelprijzen aanpassen volgens een winstmargetabel per groep;
- globaal aanpassen van het btw-percentage op artikelfiches (nieuw btw-% kiezen en aanduiden op welke prijstypes; prijzen inclusief btw moeten mee herrekend worden, prijzen exclusief btw niet);
- accijnzen verhogen met een vast bedrag per hectoliter of met een percentage.
(uit opleiding, 24-10-2025)

Verwante menupunten buiten V.3:
- V.5.4 Afdrukken prijslijsten
- V.5.9 Afdrukken prijskaartjes / prijsaffiches (V.5.9.1 = rayonkaartjes op rol)
- V.9.3.1 Artikelfiche aanpassen/bekijken
- V.2.K Uitschrijven prijzen voor de kassa (zie `prijzen-doorsturen-naar-kassa.md`)

## Directe prijswijziging of prijswijziging op datum?

| | Direct (V.3.3) | Op datum (V.3.4) |
|---|---|---|
| Wanneer actief | Onmiddellijk op de artikelfiche | Vanaf de ingegeven ingangsdatum |
| Gebruikt bij | Nieuwe bons en facturen, uitschrijven kassaprijzen: meteen | Bons/facturen en kassaprijzen nemen de nieuwe prijs zodra de (document)datum de ingangsdatum bereikt |
| Oude prijs | Meteen weg | Blijft bestaan tot V.3.5 wordt uitgevoerd |
| Vooraf prijslijsten/prijskaartjes drukken | Nee | Ja, via een prijsdatum |

De werkwijze op het scherm is identiek; bij de directe wijziging wordt alleen geen ingangsdatum gevraagd.

Belangrijk onderscheid in drie stappen (vaak verward bij supportvragen):
1. **Plannen**: de nieuwe prijs ingeven met ingangsdatum (V.3.4).
2. **Toepassen**: het systeem neemt automatisch de juiste prijs (oud of nieuw) op basis van de datum van de bon/factuur. Hiervoor is V.3.5 **niet** nodig.
3. **Overschrijven**: V.3.5 vervangt de oude prijs definitief door de nieuwe; daarna is de oude prijs niet meer oproepbaar.

## Directe prijswijziging ingeven (V.3.3)

1. Hoofdmenu voorraadbeheer, punt 3 (Beheer prijzen), punt 3.
2. Maak een selectie van de aan te passen artikels, bijvoorbeeld de leverancier (of merk/producent) van wie de nieuwe prijslijst komt. Zo krijg je alle artikels van die leverancier in één lijst en ben je zeker dat je niets overslaat.
3. Beantwoord de vraag of de **prijsafspraken met VASTE PRIJS** mee aangepast moeten worden. Zo ja, dan worden alle vaste prijsafspraken van elk gewijzigd artikel getoond en mee aangepast.
4. Gaat het om een accijnsverhoging: zie de sectie "Accijnsverhoging" hieronder (vinkjes "accijnzen verhogen" en "verhoging netto doorrekenen").
5. **F8** toont de lijst van geselecteerde artikels. Reeds behandelde artikels worden gemarkeerd (blauw), zodat je ziet tot waar je gekomen bent.
6. Ga met de pijltjestoetsen op het artikel staan en druk **F8**. Je krijgt het scherm met oude en nieuwe aankoop- en verkoopprijzen.
7. Vul enkel de nieuwe **BRUTO-aankoopprijs** in en druk **F7** (herbereken prijzen). De nieuwe verkoopprijzen worden berekend op basis van het prijsverschil tussen huidige en nieuwe aankoopprijs; de winstmarge per prijs blijft behouden (op afronding na), dus een evenredige prijsverhoging.
8. Pas eventueel verkoopprijzen manueel aan en druk **TAB**: dan worden alleen de winstmarges herberekend.
9. **F8** maakt de wijziging definitief (schrijft weg).
10. Bestaan er deelverpakkingen (clips) voor het artikel, dan vraagt het programma of die mee gewijzigd moeten worden; bij "ja" verschijnt elke deelverpakking in hetzelfde scherm en bevestig je telkens met F8 (uit opleiding, 24-10-2025; zie ook 0219C).
11. Zijn er prijsafspraken met vaste prijs, dan worden die nu één voor één getoond met een automatisch berekende nieuwe prijs (zie verder).
12. Je komt terug in de artikellijst; het behandelde artikel is blauw gemarkeerd.

### Toetsen in het prijswijzigingsscherm

| Toets | Betekenis |
|---|---|
| F7 | Herbereken ALLE nieuwe verkoopprijzen op basis van de nieuwe bruto-aankoopprijs. **Let op: manuele aanpassingen aan verkoopprijzen gaan hierdoor verloren.** |
| TAB (op een nieuwe verkoopprijs) | Enkel de bijhorende winstmarge herberekenen; manuele prijs blijft staan |
| F10 | Winst-% manueel aanpassen (vermeld in 0213B) |
| F12 | De huidige prijzen aanpassen (vermeld in 0213B) |
| F6 | Aanpassing annuleren (vermeld in 0213B) |
| F8 | Aanpassing wegschrijven |

Vuistregel uit de handleiding: **TAB = enkel winstmarges berekenen, F7 = alles berekenen.**

Let op: de betekenis van F8 verschilt per scherm (lijst tonen, artikel openen, wegschrijven). Vraag bij support altijd op welk scherm de klant staat.

### Vaste prijsafspraken tijdens een prijswijziging

Na het wegschrijven van een artikel worden de prijsafspraken met vaste prijs één voor één getoond. De nieuwe vaste prijs wordt automatisch voorgesteld op basis van de prijsstijging van het artikel (zodat de winst behouden blijft).

| Toets | Betekenis |
|---|---|
| F4 | De (nieuwe) prijs aannemen / aanpassen; je kan de voorgestelde prijs eerst overtypen |
| F6 | Deze prijsafspraak NIET aanpassen |

In het scherm van de prijzenbestanden (2291B/2292A/2293A) heten de toetsen "F4 neem NIEUWE prijs aan" en "F9 herstel vaste prijs". In de opleiding worden onderaan ook de functies "herbereken nieuwe prijs via winst" en "herstel vaste prijs" getoond (uit opleiding, 24-10-2025).

Op de fiche van een prijsafspraak kan "prijs niet aanpassen via prijsbeheer tot datum" aangevinkt zijn (bv. raamovereenkomst met een gemeente); zie `prijzen-prijsafspraken.md`.

## Prijswijziging op datum ingeven (V.3.4)

Bedoeling: de prijswijziging al ingeven zodra de nieuwe prijslijst van de leverancier binnen is, met een zelfgekozen ingangsdatum.

1. Hoofdmenu voorraadbeheer, punt 3, punt 4.
2. Selecteer de artikels (bv. op leverancier) en kies of vaste prijsafspraken mee aangepast worden.
3. **Periode ingangsdatum Van/Tot**: dient enkel om **bestaande** prijswijzigingen te raadplegen. Voor **NIEUWE** prijswijzigingen moet deze periode **leeg** blijven.
4. **F8** toont de lijst; kies het artikel en druk **F8**.
5. Vul de **Startdatum nieuwe prijzen** (ingangsdatum) in.
   - Vul je de datum NIET in (of wis je ze), dan wordt de prijswijziging niet opgenomen.
   - **Een bestaande prijswijziging schrappen** doe je dus door ze op te roepen en de startdatum te verwijderen.
6. Vul de nieuwe bruto-aankoopprijs in, **F7**, eventueel manueel bijsturen met TAB, **F8** om weg te schrijven. Daarna volgen de deelverpakkingen en de vaste prijsafspraken zoals bij de directe wijziging.

Bij het openen van V.3.4 kan de melding verschijnen dat sommige artikels een prijswijziging van meer dan 1 maand oud hebben en dat het aangeraden is die definitief te maken via punt 5 (uit opleiding, 24-10-2025).

### Wat toont de artikelfiche (V.9.3.1) na een prijswijziging op datum?

| Situatie | Wat zie je |
|---|---|
| Ingangsdatum nog niet bereikt | De oude prijzen worden getoond. Een (kalender)icoontje geeft aan dat er een nieuwe prijs bestaat; klik erop om de nieuwe prijssituatie **in het groen** te zien. Met het icoontje wissel je tussen oud en nieuw. |
| Ingangsdatum verstreken, nog niet overschreven via V.3.5 | Standaard worden eerst de **nieuwe** prijzen getoond, **in het groen**. Via het kalendericoontje kan je de oude prijs nog raadplegen. |
| Overschreven via V.3.5 | Enkel de nieuwe prijs, niet meer in het groen. Het icoontje is weg; de oude prijs is niet meer oproepbaar. |

Aandachtspunten voor support:
- Een groene prijs betekent enkel dat er een prijs op datum bestaat die nog niet definitief gemaakt is. Het bewijst **niet** dat de datum, de prijssoort, de vaste klantafspraken of de prijzen op de kassa correct zijn. Controleer die apart.
- Het systeem neemt automatisch de juiste prijs volgens de "Vanaf"-datum: een nieuwe bon of factuur met een datum vanaf de ingangsdatum krijgt de nieuwe prijs; een bon/factuur met een vroegere datum de oude.
- Oudere handleidingen (0213C, 02xxB) stellen het eenvoudiger voor ("op de artikelfiche blijft de oude prijs staan tot u de nieuwe prijzen definitief maakt"). De recentere handleiding 0213B beschrijft de weergave zoals in bovenstaande tabel; volg die.

### Artikel dupliceren (V.9.3.7) met een openstaande prijs op datum

Bij het dupliceren van een artikel wordt **niet** de groene (nieuwe) prijs overgenomen, maar de prijs die **niet** in het groen staat, ongeacht de "Vanaf"-datum. Wil je dat het duplicaat de nieuwe prijs krijgt, voer dan eerst (indien dat past) V.3.5 uit.

### Inventaris en prijswijziging bij nieuw boekjaar

Gaan prijswijzigingen in bij het begin van het nieuwe boekjaar, dan kan de inventaris nog aan de "oude" prijzen (vorig boekjaar) gemaakt worden zolang de nieuwe prijzen niet definitief zijn gemaakt. Zie ook `stock-en-inventaris.md`.

## Prijswijzigingen op datum definitief maken (V.3.5)

Waarvoor: de prijzen werkelijk overschrijven op de artikelfiche (en de prijsafspraken) zodra er geen NIEUWE bons/facturen meer aan de oude prijs gemaakt moeten worden.

1. Hoofdmenu voorraadbeheer, punt 3, punt 5 (Vervangen huidige prijzen door nieuwe).
2. Geef de periode ingangsdatum in waarop de prijsstijging betrekking heeft.
3. Druk **F8**. De prijzen op artikelfiche en prijsafspraken worden gewijzigd.

Waarschuwingen:
- Na V.3.5 is de oude prijs **definitief verloren**. Voer dit pas uit als er zeker geen documenten met een vroegere datum meer aan de oude prijs gemaakt moeten worden.
- V.3.5 is geen "snelle oplossing" voor een weergaveprobleem: de nieuwe prijs wordt ook zonder V.3.5 correct toegepast vanaf de ingangsdatum.
- Voer V.3.5 wel uit zodra de nieuwe prijs een tijdje geldig is; het programma waarschuwt bij prijswijzigingen ouder dan 1 maand.

## Lijst prijswijzigingen op datum (V.3.6)

Drukt een lijst (kan in PDF) van de ingebrachte wijzigingen die van kracht worden binnen de gekozen van-tot ingangsdatum. Oude en nieuwe prijzen staan er telkens naast elkaar. Handig om te controleren wat er gepland staat.

## Accijnsverhoging

Zelfde schermen als een gewone prijswijziging (V.3.3 direct of V.3.4 op datum), met twee extra vragen op het selectiescherm:

| Vraag | Effect |
|---|---|
| **Accijnzen verhogen** (vinkje) | Het bedrag accijnzen op de artikelfiche wordt verhoogd met het prijsverschil tussen oude en nieuwe aankoopprijs. Zonder verdere vinkjes blijft de winstmarge van voorheen behouden. |
| **Verhoging netto doorrekenen** (vinkje) | De accijnsverhoging wordt netto in de verkoopprijzen doorgerekend = er wordt **geen winst** genomen op de accijnzen. Niet aanvinken als je de winstmarge wil behouden. |

Stappen (voorbeeld uit de handleiding: accijnsverhoging met ingang op 1/11):
1. V.3.4, vul de leverancier in, vink "accijnzen verhogen" aan; "verhoging netto doorrekenen" enkel als je geen winst op de verhoging wil.
2. F8 voor de lijst, F8 op het artikel.
3. Vul bovenaan de startdatum en de nieuwe bruto-aankoopprijs in, druk F7. De verkoopprijzen worden herberekend en het veld accijnzen (onderaan) wordt verhoogd met het verschil.
4. TAB/F7/F8 en vaste prijsafspraken (F4/F6) zoals bij een gewone prijswijziging.
5. Controleer via V.3.6, druk prijslijsten (V.5.4) en prijskaartjes (V.5.9.1) met prijsdatum 1/11.

Opmerkingen:
- Daarnaast bestaat in het menu Beheer prijzen een apart punt om accijnzen te verhogen met een vast bedrag per hectoliter of een percentage (uit opleiding, 24-10-2025; geen aparte handleiding gevonden).
- De handleidingen bevatten enkel een werkwijze, geen actuele accijnstarieven. Het voorbeeld (0,14 euro op wijnen) is historisch.
- Bij het verwerken van een prijzenbestand (Districo/Belbev) worden accijnzen die afwijken van de artikelfiche groen gemarkeerd; zie `prijzen-prijzenbestanden-importeren.md`.

## Prijslijsten afdrukken met nieuwe prijzen (V.5.4)

- Veld **Datum prijswijzigingen**: bepaalt welke prijs op de lijst komt, namelijk de prijs die geldig is vanaf die datum. Zo kan je vooraf prijslijsten drukken die later in voege treden.
- Je kan aanvinken of de gewijzigde (nieuwe) prijzen in het **vet** afgedrukt worden.
- Je kan één specifieke klant selecteren (klantspecifieke prijslijst). Artikelselectie kan dan beperkt worden tot:
  - de artikels van het bestelformulier van de klant (F9 op klantenfiche),
  - de artikels die de klant al heeft afgenomen (klantenstatistiek),
  - enkel de artikels waarvoor de klant een prijsafspraak heeft.
- Met F8 naar het volgende scherm met selecties. Selectie **V.5.4.5 "Selecteer op datum laatste prijswijziging"**: enkel artikels waarvan de prijs gewijzigd is binnen een op te geven periode.

## Prijskaartjes / rayonkaartjes met nieuwe prijzen (V.5.9.1)

1. Neem V.5.9.1 (rayonkaartjes op rol).
2. Vul onderaan **Prijsdatum (promotie/prijswijziging op datum)** in, bv. 01/11: de kaartjes tonen de prijs die geldig is vanaf die datum.
3. **F8 selecteer artikels**, klik op het icoon **A+** om artikels te selecteren.
4. Kies **Artikels met selectie** en selecteer op **Datum laatste prijswijziging**; geef de periode in (bv. 01/11 – 01/11).
5. Bevestig met **F8 ga verder** en daarna **F8 print / druk af**.

Meer over kaartjes en affiches: `prijzen-prijsaffiches-en-prijskaartjes.md`.

## Controleren inhoud en aantal per bak op artikelfiches (V.3.I)

Waarvoor: correcte statistieken/historieken (liters, hectoliters), correcte prijs per liter op prijskaartjes en juiste winstmarges per stuk vereisen dat **inhoud** en **aantal/bak** juist ingevuld zijn op de artikelfiche.

1. Ga naar V.3.I (Controleren inhoud en aantal/bak op artikelfiches).
2. Geef een leverancier, merk/producent of groep in (of een combinatie) en neem **F8 begin controle**.
3. Je krijgt de artikels die niet of niet correct zijn ingevuld volgens wat het programma uit de **omschrijving** van het artikel kan afleiden: de huidige waarde staat naast de voorgestelde waarde.
4. Pas het voorstel eventueel aan en bevestig per artikel met het **groene vinkje**; bevestigde artikels krijgen een **zwart vinkje**.
5. Zijn alle vinkjes zwart: **F1 stop**. Dezelfde selectie zou daarna geen artikels meer mogen opleveren.

Ook foutief ingevulde waarden (niet alleen lege) worden zo opgespoord.

## Veelvoorkomende vragen en problemen

| Vraag / probleem | Oorzaak en oplossing |
|---|---|
| "Mijn manueel aangepaste verkoopprijzen zijn weg" | Er is na de manuele aanpassing opnieuw op F7 gedrukt. F7 herberekent alles vanaf de bruto-aankoopprijs. Gebruik TAB om enkel de marge te herberekenen. |
| "Ik wil een geplande prijswijziging verwijderen" | V.3.4, vul de periode ingangsdatum Van/Tot in om de bestaande wijziging op te roepen, open het artikel en maak de startdatum leeg. |
| "Ik vind mijn ingegeven prijswijziging niet terug / ik kan geen nieuwe ingeven" | Bij V.3.4 dient de periode Van/Tot enkel om bestaande wijzigingen te raadplegen. Voor nieuwe wijzigingen moet ze leeg zijn; om bestaande te zien moet ze ingevuld zijn. Controleer ook met de lijst V.3.6. |
| "De artikelfiche toont de prijs in het groen" | Er is een prijs op datum die nog niet definitief gemaakt is via V.3.5. Met het kalendericoon wissel je tussen oud en nieuw. |
| "Factuur met oude datum krijgt oude prijs" | Correct gedrag zolang V.3.5 niet is uitgevoerd: de prijs volgt de documentdatum. |
| "Gedupliceerd artikel heeft de oude prijs" | Dupliceren (V.9.3.7) neemt de niet-groene prijs over. Eerst V.3.5 uitvoeren indien gepast, of de prijs op het duplicaat aanpassen. |
| "De kassa heeft de nieuwe prijs niet" | Prijzen moeten uitgeschreven (V.2.K) en door de kassa opgehaald worden; zie `prijzen-doorsturen-naar-kassa.md`. |
| "Vaste prijs van een klant is niet mee gestegen" | Bij de selectie is niet gekozen om vaste prijsafspraken mee aan te passen, er is F6 gedrukt bij die afspraak, of op de afspraak staat "prijs niet aanpassen via prijsbeheer tot ..." (zie `prijzen-prijsafspraken.md`). |
| "Clip/deelverpakking heeft nog de oude prijs" | Deelverpakking is niet (correct) gekoppeld aan het hoofdartikel, of bij de vraag om deelverpakkingen mee te wijzigen is "nee" geantwoord. Zie `prijzen-aankoopfiches-en-deelverpakkingen.md`. |
| "De oude prijs is weg na V.3.5" | Niet terug te halen binnen het programma (enkel via het terugzetten van een backup). |
| "Kan ik prijswijzigingen uit Excel importeren?" | Standaard niet door de klant zelf, behalve via de prijzenbestanden van Prik&Tik, Districo en Belbev. Voor andere leveranciers kan Jamadata maatwerk voorzien (uit opleiding, 24-10-2025). |

## Bronnen

- `02xxB - Inbrengen directe prijswijzigingen.docx` (interne titel "0213A - Inbrengen prijswijzigingen - Accijnsverhogingen", 8 p.; volledigste versie) — Jamadrink/Handleidingen modules
- `0213A - Inbrengen directe prijswijzigingen.docx` — Jamadrink/Handleidingen modules
- `0213B - Inbrengen uitgestelde prijswijzigingen op datum.docx` (recentste beschrijving van de artikelfiche-weergave) — Jamadrink/Handleidingen modules
- `0213C - Inbrengen accijnsverhogingen.docx` — Jamadrink/Handleidingen modules
- `xxxxx - Accijnsverhoging.docx` (inhoud identiek aan het algemene deel van 02xxB) — Jamadrink/Handleidingen modules
- `0213D - Controleren inhoud en aantal per bak op artikelfiches.docx` — Jamadrink/Handleidingen modules
- `0219C - Deelverpakkingen (Clips).docx` — Jamadrink/Handleidingen modules
- `Mario S Prijsafspraken-20251024_131949-Opname van vergadering.txt` — Claude/Transcripties opleidingen (uit opleiding, 24-10-2025)
- `00_CHECKPOINT_PRIJSDATUM.md` — 00_START_CLAUDE/17_PRIJSDATUM (enkel de inhoudelijke nuance over groene prijs en V.3.5)
