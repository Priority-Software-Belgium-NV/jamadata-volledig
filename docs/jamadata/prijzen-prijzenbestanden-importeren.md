# Artikelprijzen aanpassen aan de hand van een prijzenbestand (Prik&Tik, Districo, Belbev)

Gebruik dit document voor: vragen over het automatisch verwerken van een Excel-prijslijst van de aankoopcentrale (Prik&Tik, Districo of Belbev) in Jamadrink: waar het bestand moet staan, hoe artikels gekoppeld worden, hoe de prijzen (met ingangsdatum) verwerkt worden, wat er met vaste prijsafspraken, deelverpakkingen, handelingskost en accijnzen gebeurt, en waarom een prijslijst of artikel niet verschijnt of rood blijft.

## Waarvoor dient het

De prijslijst van de aankoopcentrale wordt als Excel-bestand ingelezen. Eén handeling past de aankoopprijs, de verkoopprijzen (horeca- en kassaprijzen) en de vaste prijsafspraken aan, met een ingangsdatum (onmiddellijk of in de toekomst). De prijzen worden verwerkt als **prijswijziging op datum** (zie `prijzen-prijswijzigingen-en-accijnzen.md`).

De werkwijze bestaat altijd uit drie stappen:
1. De prijslijst(en) in de juiste map op de computer zetten.
2. De eigen artikels koppelen aan die van de aankoopcentrale (eenmalig per artikel).
3. De prijzen van de gewenste artikels verwerken.

## Verschillen per aankoopcentrale

| | Prik&Tik | Districo | Belbev |
|---|---|---|---|
| Handleiding | 2291B | 2292A | 2293A |
| Menupunt | **V.2.P.2** | **V.3.D.2** | **V.3.D.2** |
| Hoe kom je aan het bestand | Downloaden van de website van Prik&Tik via de "PRIVATE LOGIN", menu "Downloads" (eventueel categorie "prijslijsten 20xx") | Bijlage (XLS) in de mail van Districo bij prijsverhogingen | Downloaden van de website van Belbev of bijlage (XLS) in de mail van Belbev |
| Handelingskost op artikelfiche | Veld **H.kost**; wordt volgens 2291B bijgerekend bij de Netto **VK**-prijs (zie opmerking) | Veld **Hkost %** (in %); bijgerekend bij de Netto **AK**-prijs | Veld **H.kost**; bijgerekend bij de Netto **AK**-prijs |
| F10 "pas ALLE prijzen aan" | Niet vermeld in de handleiding | Ja | Ja |
| Afwijkende accijnzen groen gemarkeerd | Niet vermeld in de handleiding | Ja | Ja |

Opmerking (onzeker / te verifiëren): de handleiding Prik&Tik (2291B) spreekt van bijrekenen bij de "Netto VK-prijs", de recentere handleidingen Districo/Belbev van de "Netto AK-prijs". Vermoedelijk gaat het telkens om de netto-aankoopprijs.

## Stap 1 – Prijslijst opslaan in de juiste map

- Het bestand moet de extensie **.xlsx of .xls** hebben. **PDF-bestanden kunnen niet verwerkt worden.**
- Juiste locatie op de hoofdcomputer: `j:\jamadata\share\prijslijsten` (in sommige gevallen een andere driveletter).
- Op een andere pc dan de hoofdcomputer is het zeker een andere driveletter, bijvoorbeeld `P:\share\prijslijsten` of `P:\jamadata\share\prijslijsten`.
- Prik&Tik: na het downloaden het bestand openen; nieuwere Excel-versies beschouwen bestanden van internet als onveilig, klik dus eerst bovenaan op **"Bewerken inschakelen"**. Daarna Bestand > Opslaan als > Bladeren en de map hierboven kiezen.
- Districo/Belbev: rechtsklik op de XLS-bijlage in de mail > "Opslaan als" > "Bladeren" en de map hierboven kiezen.
- Herhaal dit voor elke prijslijst die verwerkt moet worden.

## Stap 2 – Artikels koppelen

Enkel nodig als de artikels nog niet gekoppeld zijn (koppelen kan ook al gebeurd zijn via bestellingen of promotiefolders; de koppeling zit in de leverancierscode op de aankoopfiche, zie `prijzen-aankoopfiches-en-deelverpakkingen.md`).

1. Ga naar het menupunt (Prik&Tik: V.2.P.2, Districo/Belbev: V.3.D.2). Bij het opstarten verschijnt een overzicht van de prijslijsten die in de map staan.
2. Iconen per prijslijst:
   - icoon om de prijslijst te **verwerken**;
   - icoon om de Excel te downloaden en te **openen**;
   - **rode vuilbak**: de prijslijst uit Jamadata verwijderen.
3. Klik op de gewenste prijslijst. Je krijgt de artikellijnen:
   - **Volledig rood** = artikel nog niet gekoppeld.
   - **Gedeeltelijk rood** (enkel "Art.prijs" en "Art.datum") = gekoppeld, maar prijs nog niet verwerkt.
   - **Geen rood meer** = prijs verwerkt.
4. Klik achter de lijn op het **koppelicoon**. Je krijgt een lijst van eigen artikels die overeenkomen met het eerste stuk van de omschrijving van de aankoopcentrale. Klik op het **vinkje** van het juiste artikel: het wordt gekoppeld.
5. Wijkt de **inhoud (of het gewicht)** af van die bij de aankoopcentrale, dan verschijnt een tussenscherm waar je dit kan corrigeren als het voor het eigen artikel niet juist is.
6. Wijkt het **aantal/verpakking** bij de aankoopcentrale af van het eigen artikel, vul dan het **afwijkend aantal/verpakking van de leverancier** in (bv. eigen artikel = fles, leverancier verkoopt per doos van 6).
7. Koppeling wissen: klik opnieuw op het koppelicoon en vervolgens op de knop om de koppeling te verbreken; daarna kan je opnieuw koppelen via het juiste vinkje.
8. Gekoppelde artikels herken je aan het **zwarte vinkje** nadat je eerst op het vergrootglas hebt gedrukt.

## Stap 3 – Prijzen verwerken

1. Vul bovenaan **"Ingangsdatum nieuwe prijzen"** in. De aankoopcentrale zet de ingangsdatum meestal in de bestandsnaam, maar het programma vraagt de datum voor de zekerheid; ze geldt voor de hele lijst.
2. Druk op het **vergrootglas** achter een gekoppeld artikel. Het prijsscherm is normaal meteen correct ingevuld: de gemarkeerde velden komen uit de prijslijst, de datum is de ingegeven ingangsdatum. Netto-aankoopprijs en verkoopprijzen worden automatisch berekend met behoud van de winstmarge (op afronding na).
3. **F8 Schrijf weg** bewaart de prijzen.
4. Zijn er **prijsafspraken met vaste prijs** voor dit artikel, dan worden ze klant per klant overlopen:
   - **F4 neem NIEUWE prijs aan**: de voorgestelde, verhoogde prijs overnemen;
   - **F9 herstel vaste prijs**: de afgesproken vaste prijs behouden.
5. Zijn er **deelverpakkingen** (clips), dan verschijnt daarna het scherm van elke deelverpakking; verwerk ze op dezelfde manier als het hoofdartikel.
6. Terug in de lijst is de rode markering van het verwerkte artikel weg.
7. Districo/Belbev: met **F10 "pas ALLE prijzen aan"** overloopt de computer automatisch alle gekoppelde artikels, zodat je niet per artikel op het vergrootglas moet drukken.

## Wat gebeurt er na de verwerking

- De nieuwe prijzen worden **automatisch gebruikt vanaf de opgegeven ingangsdatum** (bons, facturen, kassaprijzen).
- Ze zijn niet meteen zichtbaar als "de" prijs op de artikelfiche, omdat er na die datum nog bons/facturen met een vroegere datum gemaakt kunnen worden waarvoor de oude prijs moet gelden.
- Zodra dat niet meer nodig is: **V.3.5** uitvoeren om de prijzen definitief te wijzigen op de artikelfiche. Vanaf dan is de oude prijs verloren.
- Vergeet niet de prijzen opnieuw uit te schrijven voor de kassa (V.2.K), zie `prijzen-doorsturen-naar-kassa.md`.

## Handelingskost en accijnzen

- Op de artikelfiche staat een veld **H.kost / Hkost %**: de handelingskost die de aankoopcentrale voor dit artikel aanrekent. Die wordt standaard bijgerekend bij de netto-prijs.
- Vul je de handelingskost zelf in: maak de netto-prijs leeg en druk op **TAB** of **F7**; de netto-prijs wordt dan herberekend aan de hand van de kortingen en de handelingskost wordt erbij geteld.
- Districo/Belbev: verschillen de **accijnzen** in de prijslijst van die op de artikelfiche, dan worden ze **groen gemarkeerd**.

## Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Prijslijst verschijnt niet in het overzicht | Bestand staat niet in `...\share\prijslijsten` (verkeerde driveletter of map), of het is een PDF. Enkel .xls/.xlsx. |
| Excel-bestand kan niet opgeslagen worden | Bestand is geopend in "Beveiligde weergave": eerst "Bewerken inschakelen". |
| Alle lijnen staan in het rood | Artikels zijn nog niet gekoppeld (stap 2). |
| Lijn blijft gedeeltelijk rood | Artikel is gekoppeld maar de prijs is nog niet verwerkt (vergrootglas + F8, of F10 voor alles). |
| Voorgestelde prijs is een veelvoud/fractie van wat verwacht wordt | Aantal/verpakking van de leverancier wijkt af en is niet (juist) ingevuld bij het koppelen, of inhoud/aantal per bak op de artikelfiche is fout (controle via V.3.I). |
| Verkeerd artikel gekoppeld | Koppeling wissen via het koppelicoon en opnieuw koppelen. |
| Nieuwe prijs staat niet op de artikelfiche | Normaal: het is een prijs op datum. Ze wordt vanaf de ingangsdatum toegepast en in het groen getoond; definitief maken via V.3.5. |
| Vaste klantprijs werd ongewild verhoogd | Bij die afspraak is F4 gekozen i.p.v. F9. Corrigeer de prijsafspraak (zie `prijzen-prijsafspraken.md`). |

## Bronnen

- `2291B - Aanpassen artikelprijzen adhv prijzenbestand.docx` (Prik&Tik) — Jamadrink/Handleidingen modules
- `2292A - Aanpassen artikelprijzen ahv prijzenbestand DISTRICO.docx` — Jamadrink/Handleidingen modules
- `2293A - Aanpassen artikelprijzen ahv prijzenbestand Belbev.docx` — Jamadrink/Handleidingen modules
