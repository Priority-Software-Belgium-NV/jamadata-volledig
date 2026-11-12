# Kassa – Gebruik van de Key-Conen kassa en beheer van de Key-conen (blokjes)

Gebruik dit document voor: vragen van gebruikers over het dagelijks werken met de Jamadata Key-Conen (touch)kassa: het kassamenu, de knoppen op het kassascherm, het kasticket, het menu Diversen, de kassaparameters, het indelen en aanpassen van de Key-conen (blokjes) op de hoofdcomputer (V.2.2), het klaarzetten en synchroniseren van gegevens (V.2.K en punt N/K op de kassa), het inlezen van de verkopen, dagtotalen, kasverslag, verkooplijsten, barcodes toevoegen via de kassa, functiebarcodes en lotto-artikels.

## 1. Begrippen

- **Key-coon / blokje**: een toets op het touchscreen van de kassa. Een blokje is ofwel een **menu** (opent een nieuw scherm met blokjes) ofwel een **artikel** (verkoopt dat artikel).
- **Hoofdcomputer / JMS**: de pc/server waarop Jamadrink draait. De kassa wisselt gegevens uit met de hoofdcomputer via de "dagelijkse transfer".
- **Menu V.2**: in Jamadrink, Hoofdmenu voorraadbeheer (V) → punt 2 "Beheer Key-Conen kassa". Hier beheer je Key-conen, promoties, klantenkaarten, kasverslagen enz.

Overzicht van het menu V.2 (voor zover in de bronnen vermeld):

| Punt | Functie |
|---|---|
| V.2.1 | Promoties (promotiefiches; ook afwijkende klantenkaartpunten per artikel/groep) |
| V.2.2 | Aanpassen/bekijken blokjes (Key-conen) |
| V.2.3 | Verkopen van de kassa inlezen |
| V.2.4 | Afdrukken/inboeken kassaverslag |
| V.2.5 | Afdrukken verkooplijsten |
| V.2.6 | Dagtotalen bekijken |
| V.2.7 | Ontvangen geld tellen |
| V.2.9 | Beheer klantenkaarten (zie `kassa-klantenkaarten-cadeaubons-tegoedbons.md`) |
| V.2.C | Prijscontrole kassaverkopen |
| V.2.K | Klaarzetten alle gegevens voor kassa |
| V.2.P | Beheer koppeling Prik & Tik (enkel als titel vermeld in de Jamadrink-handleiding; zie Freedelity in `kassa-klantenkaarten-cadeaubons-tegoedbons.md`) |
| V.2.+ | Parameters (o.a. bepaling promotiepunten, benaming variabele betaalwijzen, kasverslag-parameters) |

## 2. Het kassamenu (bij het opstarten van de kassasoftware)

De kassa zelf aanzetten: onderaan het scherm zit een rood lampje; druk dit in. Het lampje kleurt blauw en de kassa start op.

Bij het opstarten van de kassasoftware verschijnt eerst het "Menu Beheer Key-conen Kassa". Het kan volgende punten bevatten (per klant instelbaar via `kasmenu.dat`):

| Toets | Menupunt |
|---|---|
| 1 | Opstarten kassa-functie (klantenverkoop e.d.) |
| 3 | Aanpassen parameters (reclameteksten, tickethoofding e.d.) |
| 4 | Kopie maken van de kassagegevens |
| 5 | Terug opladen van oude kopie van kassagegevens |
| 9 | Wissen van het facturen-bestand: KASFAC.DAT |
| A | Wissen van de verkoopgegevens van de kassa (niet aanwezig bij kaslog per maand) |
| N | Dagelijkse TRANSFER met de HOOFDCOMPUTER [JMS] (kassa in hetzelfde netwerk) |
| K | Transfer voor een kassa op een andere locatie (via de servers van Jamadata) |
| T (en bij oude kassa's daarna M) | Update ophalen bij Jamadata ("binnenbellen") – op vraag van support |
| F1 Stop | Verlaat het menu |
| F8 Kassa | Opent de kassa, idem punt 1 |
| F9 Controle | Opent het menu om de kassa-controleband / kasverslag af te drukken |

Bovenaan in het rood staat "Menu: beheer key-conen kassa"; als je daarop drukt zie je o.a. het aantal (vrije) records van de kaslog.

## 3. Het kassascherm

Na punt 1 of F8 zie je links het standaard kassascherm en rechts de zelf ingestelde Key-conen. Het standaardscherm kan per klant verschillen (Jamadata kan knoppen aanpassen, zie KASKEYS in `kassa-configbestanden.md`).

### 3.1 Het gele ticket-display (linksboven)

Toont het laatst toegevoegde artikel en het totaal van het ticket, met een statusregel:

- `V: A/1` = verkoper A, klant 1;
- `L: A` = leeggoed wordt automatisch geteld;
- `0 -->` = met welke prijs gerekend wordt (0 = kassaprijs);
- `0,00 EUR` = totaalbedrag.

Kleurt het gele ticket **roze** en hoor je een alarm, dan is een onbekende barcode gescand (zie "Voeg EAN-nr. toe").

### 3.2 Het kasticket

Bovenaan de tickethoofding (zelf in te stellen via de parameters), daaronder: de artikels (aantal, eenheidsprijs, totaal), subtotalen, totaal leeggoed, betalingswijze(n) met bedrag(en) en een statusregel, bv. `V: A/1 T: 0023 A: 0015 Ma 4 Mrt 2019` = verkoper A, klant 1, ticketnummer 23, 15 artikels, datum (tijdstip optioneel). Het ticketnummer loopt door; via de parameters kan je het elke dag opnieuw vanaf 1 laten beginnen.

### 3.3 Knoppen op het kassascherm

| Knop | Werking |
|---|---|
| 0–9 | Aantallen of bedragen ingeven. Bv. 2 artikels: druk 2 en dan de artikelknop of scan de barcode. |
| X, +, -, . | Rekentoetsen; `-` gevolgd door IDEM verwijdert één stuk (zie IDEM). |
| CLEAR | Wis het ingevoerde getal, of wis de foutief gescande barcode. |
| CLR_TICKT | Wis het volledige huidige ticket. |
| PLU | Opent de productlijst van alle artikels. |
| EAN | Geef een EAN-nummer/barcode manueel in en zoek hierop. |
| IDEM | Voegt hetzelfde artikel nog eens toe (bv. 1 bak gescand maar het zijn er 2). `-` en dan IDEM: verwijdert één keer het zopas ingevoerde artikel (3 bakken ingegeven, het zijn er 2). |
| STUKS | Stuks i.p.v. bakken: druk bv. 4, dan STUKS en kies/scan het artikel (4 losse flesjes). |
| E.P. | Eenheidsprijs wijzigen: geef het bedrag in en druk E.P.; de prijs van het laatste artikel wordt aangepast. Dit heeft enkel invloed op het huidige ticket. |
| Korting | Korting in euro op het laatste artikel: eerst bedrag, dan Korting. |
| Kort. % | Korting in % op het laatste artikel: eerst percentage, dan Kort. %. |
| % Alles | % korting op het hele ticket. Moet aan het **begin** van het ticket gebeuren, anders wordt de korting niet geregistreerd. |
| SUBTOT | Maakt een subtotaal (rekening opsplitsen): scan de artikels die samen horen, druk SUBTOT, scan de volgende groep, opnieuw SUBTOT, … |
| AUTO-LGG | Wissel tussen wel/niet automatisch leeggoed aanrekenen. |
| LG-TERUG | Reken enkel het leeggoed van het ingevoerde artikel aan (dus zonder het artikel zelf). |
| LEEGG=OK | Zet hetzelfde leeggoed dat bij de producten werd aangerekend ook als teruggegeven leeggoed op het ticket (klant koopt 2 bakken en brengt 2 lege bakken van hetzelfde mee). |
| Horeca | Reken horecaprijzen aan i.p.v. kassaprijzen. |
| KLT-KRT | Klantenkaart: klant kiezen uit de lijst; de punten worden berekend op het totaal van het ticket. |
| Factuur | Maak een factuur of bon voor een klant: klant uit de lijst kiezen en artikels invoeren. Zie §3.3.1 voor de prijsbepaling. |
| A.klt. | Andere klant: wissel tussen klant 1 en klant 2 (twee tickets tegelijk open per verkoper). |
| Verk A / Verk B / Verk C | Open de kassa van verkoper A, B of C. |
| Ticket | Open het huidige ticketoverzicht, met de knoppen Terug, <, > en WIS. Met de pijltjes loop je door de lijnen (of tik een lijn aan); **WIS** verwijdert de geselecteerde lijn van het ticket, samen met het leeggoed dat bij dat artikel hoorde. |
| Diversen | Open het menu met diverse acties (§3.5). |
| Alarm | Opent de geldlade (het label "Alarm" dient om gauwdieven te misleiden). Er kan een 4-cijferige code ingesteld worden als extra beveiliging. |
| Einde | Beëindig het ticket en ga naar het afrekenscherm (§3.4). |
| Stoppen | Stop het kassaprogramma. Kan enkel als er geen enkel openstaand ticket meer is, bij geen enkele verkoper/klant. |
| Terug | Ga terug naar het kassamenu. |
| Ingestelde Key-conen | Openen de mappen (menu's) of kiezen het artikel dat achter de knop zit (beheer via V.2.2). |

#### 3.3.1 Factuur op de kassa: welke prijs?

- Kies je de klant **vóór** het ingeven van de artikels, dan rekent de kassa het **prijstype van de klant** aan. De kassa houdt **geen** rekening met prijsafspraken.
- Geef je eerst de artikels in en kies je **daarna** de klant, dan wordt de **kassaprijs** aangerekend.
- Staat op de klantenfiche in Jamadrink dat de klant eigen prijzen heeft op de kassa, dan vraagt de kassa bij "Einde" of de prijzen voor de klant ingeladen moeten worden.
- Bij het afronden worden 2 tickets afgedrukt: één voor de klant en één voor de handelaar.

Voorbeeld LEEGG=OK op het ticket:

```
Aant.  E.P.   Omschrijving   Totaal
  5    28,50  BIER – BAK     142,50
  5     4,50  LEEGGOED        22,50
 -5     4,50  LEEGGOED       -22,50
              TE BETALEN     142,50
```

### 3.4 Afrekenen (na Einde)

Na "Einde" worden de Key-conen vervangen door de betaalknoppen:

| Knop | Werking |
|---|---|
| Geld | Betaal met cash. |
| Betaalautomaat | Betaal via de gekoppelde betaalterminal (Bancontact, digitale maaltijdcheque e.d.). |
| Krediet | Betaal met kredietkaart (de Jamadrink-handleiding omschrijft deze knop als "betaal met factuurkaart" – de betekenis verschilt tussen de twee handleidingen; te verifiëren). |
| Maaltijdcheque | Betaal met maaltijdcheques. |
| Mobiel | Betaal met mobiel (bv. Payconiq; vroeger Proton). |
| Bon | Geef het bedrag in en druk Bon om dat bedrag af te trekken van het totaal. |
| Eigen tegoedbon | Geef het bedrag in en druk op deze knop om een eigen tegoedbon te verrekenen. |
| Cadeaubon | Ontvangen eigen cadeaubon verrekenen (bedrag ingeven, dan de knop). |
| Variabele betaalwijzen (1–3) | 3 betaalwijzen met zelf te kiezen label (bv. gemeentecheques); eerst te configureren door Jamadata. |
| Volledig | "Volledig" + een betaalwijze rekent het volledige bedrag af met die betaalwijze (bv. Volledig + Maaltijdcheques). |
| Terug | Ga terug naar het ticket. |

### 3.5 Menu Diversen

| Knop | Werking |
|---|---|
| UITGAVE | Bedrag ingeven en op deze knop drukken = uitgave uit de kassa. |
| INKOMST | Bedrag ingeven en op deze knop drukken = inkomst in de kassa. |
| Verkoop cadeaubon | Bedrag ingeven en op deze knop drukken = verkoop van een cadeaubon (i.p.v. een artikel "cadeaubon"). |
| Aant.ex.ticket: # | Aantal exemplaren van het ticket dat afgedrukt wordt: 1, 2, 3, … of `-` (geen ticket). Standaard 1. |
| Afdrukken kastoestand | Druk de kastoestand af. Dit kan ook doorheen de dag. |
| Afdrukken controleband | Druk de controleband van de kassa af. Dit doe je aan het einde van de dag. |
| Bewaren bon | Bewaar het huidige ticket als bon zonder af te rekenen. Zolang de bon niet is afgerekend, blijft hij bewaard. |
| Opladen bon | Laad een bewaarde bon terug in om aan te passen of af te rekenen. |
| PDA-Bons | Laad een bon in van een PDA (eerst de PDA connecteren). |
| Opnieuw afdrukken van een klant-ticket: `<<` `#` `>>` + Druk af | Blader met << en >> naar het gewenste ticketnummer en druk "Druk af" om het opnieuw af te drukken. **Enkel tickets van vandaag** kunnen opnieuw afgedrukt worden. |
| Lees Eid-kaart | Met een kaartlezer de gegevens van een identiteitskaart inlezen in het klantenbestand. De klant moet (GDPR) met een handtekening akkoord gaan met opslag/gebruik van zijn gegevens. |
| Zet op ticket | Na het inlezen van de eID: de eID-gegevens op het ticket afdrukken. |
| Loyalty card Freedelity | Punten geven op de Freedelity-klantenkaart (Prik&Tik). |
| Puntentotaal | Bij een leeg ticket: drukt het puntentotaal af van de laatst gekozen klant. |
| Voeg EAN-nr. toe | Verschijnt enkel na het scannen van een onbekende barcode (zie §7). |
| Terug | Terug naar het kassascherm. |

### 3.6 Aanpassen parameters (kassamenu punt 3)

Sluit een toetsenbord aan; blader met **F3 volgend** / F8 door de schermen. Je kan o.a. instellen:

- hoofding en afsluiting (footer) van het kassaticket; een lege regel in de hoofding krijg je door enkel een `*` op die lijn te zetten;
- de boodschappen op het klantendisplay wanneer er geen ticket bezig is (reclameteksten); lege vakken worden niet getoond;
- instellingen i.v.m. (vreemde) munteenheden;
- diverse parameters: btw-afronding, speciale toetskleuren, dagelijkse reset van ticketnummers (J/N), teksten van de variabele betaalwijzen, indeling schermtoetsenbord (AZERTY/ABC), creditkaarten toelaten via de knop "Betaalautomaat", …;
- instellingen i.v.m. klantenkaarten (aantal punten per aankoopwaarde, punten volle kaart, waarde volle kaart);
- promoties (er zijn 4 promotieformules – niet uitgewerkt in de bron);
- artikelgroepen;
- printer (controle via punt 3, F8, F8), tekst op de tegoedbon, factuurhoofding en marges voor grote facturen.

## 4. Key-conen (blokjes) beheren op de hoofdcomputer – V.2.2

Menupad: Hoofdmenu voorraadbeheer → 2 (Beheer Key-Conen kassa) → 2 "Aanpassen/bekijken blokjes (Key-conen)". De artikels moeten eerst aangemaakt zijn in Jamadrink.

### 4.1 Opbouw

- Het **hoofdmenu** bevat **18 blokjes** (6 rijen van 3). Hier zet je de hoofdindeling (groepen/categorieën): pilsbieren, speciale bieren, limonades, waters, cola's, sterke dranken, wijnen, snoep, zuivel, promotiefolder, …
- Elk **onderliggend menu** heeft **48 blokjes** (6 rijen van 8).
- Maximaal 3 geneste submenu's: Hoofdmenu → Submenu 1 → Submenu 2 → Submenu 3. Een Submenu 4 kan niet.
- Je hoeft de artikelgroepen van Jamadrink niet te volgen; kies wat het meest gebruiksvriendelijk is (bv. groep "Frisdranken" splitsen in "limonades" en "waters").
- De onderste 3 hoofdblokjes krijgen meestal: **Diversen 21 %** (artikel "diversen" met prijs 1 euro), **Diversen 6 %** (snoep, zuivel) en **Leeggoed** (alle leeggoedartikels, liefst in oplopende volgorde 0,10 – 0,20 – 3,50 – 4,50 …).
- Laat enkele hoofdblokjes vrij voor latere uitbreiding.

Geen blokje nodig voor: losse flessen uit een bak (gebruik STUKS) en producten die je scant met de barcodescanner.

Tip: druk eerst een prijslijst af van alle artikels, gesorteerd per groep, als basis voor de indeling.

### 4.2 Soorten blokjes (kleurcode in dit beheerscherm, verschilt van de kleuren op de kassa)

- **Leeg blokje**: laat een lege plaats op de kassa. Je kan er tekst op zetten (grijze velden); die verschijnt op de kassa maar het blokje doet niets (bv. als titel of placeholder, of een lege rij voor de leesbaarheid).
- **Menublokje**: codenummer = `*`; de knopnaam vul je zelf in. Opent een submenu.
- **Artikelblokje**: codenummer = artikelcode. De omschrijving wordt automatisch ingevuld als het blokje nog leeg is; anders blijft de bestaande tekst staan. Je kan de tekst altijd aanpassen.

### 4.3 Een artikel op een blokje zetten

1. Ga op het blokje staan en vul **boven het blokje** (witte balk) de artikelnummer of een stuk van de omschrijving in en druk Enter/Tab.
2. Bij meerdere resultaten toont het systeem een lijst waaruit je kiest; bij 1 resultaat wordt het direct ingevuld.
3. Pas de tekst op het blokje aan tot een korte, duidelijke naam (de ruimte is zeer beperkt). Bv. onder "Leeggoed" enkel het bedrag laten staan.

Tip: begint je artikelcode met een letter, zet er dan een punt `.` voor, zodat het systeem weet dat het een codenummer is en geen omschrijving.

### 4.4 Meer dan 48 artikels in één groep

1. Zet de meest courante artikels op de 5 bovenste rijen (40 stuks) en maak op de onderste rij menublokjes voor de verdere uitsplitsing (bv. bij "Sterke dranken": jenevers, likeuren, whisky …). Courante artikels mag je daar herhalen; of
2. Vul het scherm volledig en maak rechts onderaan een menublokje "VERVOLG".

Zorg dat de meeste producten met 2 keer drukken bereikbaar zijn (bv. "Waters" + "Spa reine").

### 4.5 Functietoetsen in V.2.2 (niet op het scherm getoond; F12 toont de lijst)

| Toets | Functie |
|---|---|
| F1 Stop | Terug naar het vorige menu. |
| F3 Markeer | Markeer het blokje onder de cursor om het te verplaatsen (het gemarkeerde blokje wordt visueel aangeduid/flikkert). |
| F4 Verplaats | Verplaats het gemarkeerde blokje naar de plaats van de cursor. Het blijft gemarkeerd en kan opnieuw verplaatst worden. |
| F6 Wis | Wis het blokje. Een menublokje kan niet gewist worden zolang er blokjes onder zitten: wis eerst alle onderliggende blokjes. |
| F7 Raadpleeg | Raadpleeg de artikelfiche van dit blokje. |
| F8 Ga in MENU | Ga naar het onderliggende menu (enkel als het codenummer `*` is). |
| F10 Keer terug | Een niveau hoger. |
| F12 Help | Hulpscherm. |
| PgUp / PgDn | Volgende / vorige blokje. |

Na het wijzigen van blokjes moet je de gegevens **klaarzetten (V.2.K)** en op de kassa de **transfer (N of K)** doen voordat de kassa ze toont.

De vaste systeemknoppen (Einde, Korting, betaalknoppen, …) kan de klant niet zelf wijzigen; dat doet Jamadata met KASKEYS (zie `kassa-configbestanden.md`).

## 5. Gegevens klaarzetten en de kassa synchroniseren

### 5.1 Klaarzetten op de hoofdcomputer – V.2.K

Na elke wijziging aan artikels, prijzen, klanten, blokjes enz. moeten de gegevens klaargezet worden: **V.2.K "Klaarzetten alle gegevens voor kassa"**. Het scherm toont "Datum promoties" (standaard vandaag) en een lijst van gegevens die gesynchroniseerd kunnen worden; standaard is alles aangevinkt. **F8 neem aan** zet de gegevens klaar.

### 5.2 Transfer op de kassa – punt N of K

- Kassa in hetzelfde netwerk: stop de kassa tot op het kassamenu en kies **N "Dagelijkse TRANSFER met de HOOFDCOMPUTER [JMS]"**.
- Kassa op een andere locatie: punt **K** (via de servers van Jamadata); op de hoofdlocatie moet dan ook een snelkoppeling genomen worden.

De transfer haalt de klaargezette gegevens op (artikels, prijzen, blokjes, …) en stuurt een kopie van de verkoopgegevens naar de hoofdcomputer (de kassa houdt zelf een kopie bij tot die handmatig gewist wordt).

Het doorsturen van prijzen/prijswijzigingen naar de kassa is apart beschreven in `prijzen-doorsturen-naar-kassa.md`.

Let op: neem de N niet tegelijk met of vlak na de K; anders kan `KASPLU.DAT` nog niet bijgewerkt zijn (zie `kassa-faq-en-storingen.md`).

### 5.3 Verkopen van de kassa inlezen – V.2.3

Kies de periode en de kassa (leeg = alle kassa's) en of Stock & Statistieken bijgewerkt moeten worden (aangeraden: ja). Is het verkopenbestand van de kassa niet recent of komt het niet overeen met het sluitingsuur van de winkel, dan krijg je een waarschuwing; je kan toch inlezen. Tijdens het inlezen wordt ook de omzet op de klantenkaarten bijgewerkt.

Controle: als je bij het inlezen de datum/uur van het verkopenbestand ziet, is de transfer goed aangekomen.

### 5.4 Dagtotalen bekijken – V.2.6

Kies de periode (en eventueel één kassa); je krijgt een lijst van de dagtotalen, gesorteerd op datum.

### 5.5 Kassaverslag afdrukken en inboeken – V.2.4

1. Zoekscherm: periode, kassa en/of filiaal.
2. F8 neem aan maakt een pdf van het kassaverslag (en opent die) en gaat verder naar het inboekscherm. Je kan ingeven hoeveel geld uit de kassa naar de bank gaat.
3. Je ziet een lijst van alle bewegingen; corrigeren kan nog.
4. Inboeken kan enkel als bij elk item het **Type grootboekrekening** is ingevuld. Zoeken: bij Type `G` en bij Omschrijving bv. `.6` (alle rekeningen die met 6 beginnen), dan **F7 herdisplay** en kiezen.
5. **F8 boek** boekt het kassaverslag in.

Let op: het systeem verhindert niet dat een reeds ingeboekt kassaverslag nogmaals wordt ingeboekt.

(De boekhoudkundige kant – kasjournaal – staat in de boekhouddocumentatie.)

### 5.6 Verkooplijsten – V.2.5

| Toets | Lijst |
|---|---|
| 1 | Afdrukken nog te factureren tickets |
| 2 | Afdrukken verkopen per artikelgroep |
| 3 | Afdrukken verkopen per artikel |
| 4 | Afdrukken top 200 van de bestverkochte artikels |
| 5 | Afdrukken top 200 van de slechtst verkochte artikels |
| 6 | Afdrukken dagtotalen |
| 7 | Afdrukken bestellijst/laadbon winkel |
| C | Afdrukken controlelijst dubbele EAN-nummers |
| F | Uitschrijven verkopen naar Txt-bestand |

**Omzet van de kassa opvragen**: Hoofdmenu → 2 (Beheer Key-Conen kassa) → 5 (Afdrukken diverse verkooplijsten) → 6 (Afdrukken dagtotalen) → periode en kassa kiezen.

### 5.7 Ontvangen geld tellen – V.2.7

Hulpscherm om de kassa te tellen: geef per biljet/munt het aantal in; het systeem berekent het totaal. F8 neem aan zet het totaal bij de "Laatste totalen" (laatste 5 berekeningen); TOTAAL rechtsonder telt alle berekeningen op. Er wordt niets in de database weggeschreven.

### 5.8 Prijscontrole kassaverkopen – V.2.C

Zoekscherm met periode, kassa en prijstype; **F8 maak PDF** geeft een lijst van alle bewegingen op de kassa met een afwijkende prijs.

## 6. Kasverslag / controleband op de kassa zelf (F9 Controle)

In het kassamenu opent **F9 Controle** het scherm om de controleband/kastotalen af te drukken. Met "Selectie der verkopen" kies je welke verkopen: allemaal, particulier, bons/facturen of "Apart en totaal". Met "Neem deze als standaard" wordt de keuze bewaard. Bij "Apart en totaal" komen er 3 tickets: (1) totaal particuliere verkopen, (2) totaal van de verkopen die per klant gefactureerd moeten worden, (3) de som van beide.

## 7. Barcodes (EAN) toevoegen via de kassa

### 7.1 Onbekende barcode tijdens de verkoop

1. Je scant een code die het systeem niet kent: alarm, en het gele ticket kleurt roze.
2. Kies (via PLU of de blokjes) het artikel dat bij deze barcode hoort.
3. Druk op **Diversen**; daar is nu de knop **Voeg EAN-nr. toe** verschenen.
4. Druk op "Voeg EAN-nr. toe": de barcode is aan het artikel gekoppeld.

### 7.2 Barcodes via de kassa naar de hoofdcomputer en andere kassa's brengen

1. Maak het artikel aan in JMD (indien nog niet gebeurd).
2. Hoofdcomputer: punt 2 → **K** (klaarzetten gegevens voor de kassa).
3. Kassa: **N** (dagelijkse transfer). De nieuwe artikels staan nu op de kassa.
4. Scan de barcode met de handscanner, zoek het artikel via PLU, kies Diversen → Voeg EAN-nr. toe. Herhaal voor alle artikels.
5. Kassa: opnieuw **N**.
6. In JMD: **V, 2, +, 2, F8**. Nu staan de barcodes op de hoofdcomputer.
7. Voor een tweede kassa: opnieuw punt 2 → K, en op de 2e kassa de N.

## 8. Functiebarcodes voor de Key-Conen kassa

Jamadata heeft een scanblad "Functie-barcodes voor KeyConenkassa" (Code 39) waarmee je zonder het scherm aan te raken functies kan scannen:

| Barcode-inhoud | Functie |
|---|---|
| `$1$1` | FLES (stuk) |
| `$0$0` | BAK |
| `$6$6` | BAK VAN 6 |
| `$7$7` | BAK VAN 12 |
| `$8$8` | BAK VAN 24 |
| `%0D` | CLEAR |
| `%00` … `%09` | cijfers 0 … 9 (aantal) |

De precieze scanvolgorde staat niet in de bron; naar analogie met de scanner-functietoetsen: eerst aantal en/of functie (bv. FLES), daarna de productbarcode (te verifiëren).

## 9. Lotto-artikels op de kassa

Lottoverkoop gebeurt op commissie en is boekhoudkundig 0 % btw / buiten btw (zoals leeggoed). De verkoop mag daarom niet op een 7-rekening komen maar op een 5-rekening (bv. 580200).

Werkwijze:

1. Maak een grootboekrekening (bv. 580200); het vak btw-aangifte mag niet ingevuld zijn.
2. Maak voor elk lottoproduct een artikel met zijn prijs (of zonder prijs als die niet vast is = prijs ingeven op de kassa) en vul op de artikelfiche bij **GRB-rekening** 580200 in.
3. Maak een artikel "Uitbetaling lotto" zonder prijs (bedrag ingeven op de kassa), ook met GRB-rekening 580200.
4. Op het kasverslag (V.2.4) komt onderaan bij de totalen een aparte kolom (excl. btw) voor artikels met 0 % btw waarbij een GRB-rekening is ingevuld. Bij het boeken van het kasverslag komt de lotto op 580200; de commissienota van de Lotto kan je daar tegen afpunten.

Het veld "GRB-rekening" op de artikelfiche en bij bons/facturatie moet door Jamadata voorzien worden (aanpassing struct.cnf: artikel veld `grootb_rek`, bon veld `grb_rek`; schermen 2,20 en 2,27).

## Bronnen

- `kassa/gebruikershandleiding keyConen KASSA 2.0.docx`
- `Jamadrink/gebruikershandleiding JAMADRINK 2.0.docx` (hoofdstukken V.2 Beheer Key-conen kassa en K Werking Kassa, handleidingpagina's 50–62)
- `Jamadrink/Handleidingen modules/0290A - Ingeven blokjes (KeyConen).docx`
- `kassa/FunctieBarcodesKassa.pdf`
- `Onenote/KASSA.pdf` (05 Omzet van de Kassa genereren; 09 Barcodes toevoegen aan artikels via de Kassa; 14 Lotto installeren) – vollediger dan `kassa/KASSA.pdf`
- `kassa/Hoe het kasjournaal inboeken.docx` (enkel het deel "Instelling kassa" – F9 Controle)
- `kassa/Hoe eigen cadeaubons verwerken.docx` (knop Cadeaubon)
