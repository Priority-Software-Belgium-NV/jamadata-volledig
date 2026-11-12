# Praktijkkennis opleiding mei 2026: kassa

Gebruik dit document voor: vragen over de bediening van de Jamadata-kassa (opstarten, artikelen aanslaan, stuks/bakken, leeggoed, kortingen, prijsniveaus, betaalmiddelen, bon versus cadeaubon, klantenkaart), de gegevensuitwisseling met de hoofdcomputer, dagtotalen (F9 Controle), en het verkoopbestand van de kassa (wissen, inlezen in het pakket, maandbestanden, een vergeten afdruk alsnog maken).

> **Waarschuwing.** Deze inhoud komt uit gesproken opleidingssessies (automatische Whisper-transcriptie, mei 2026; de kassasessie is met een camera opgenomen en bevat veel ruis). Namen van knoppen, menuletters en bestandsnamen kunnen herkenningsfouten bevatten, en de knoppenindeling verschilt per klant (ze is instelbaar). Controleer bij twijfel tegen de kassahandleiding. Punten met *(te verifiëren)* waren niet eenduidig.

## 1. Hoe de kassa samenhangt met de hoofdcomputer

Bron: opleiding 28-05-2026 (ca. 00:00–00:06), 07-05-2026 (ca. 00:20).

- **De kassa werkt offline** met een eigen lokale database (artikelen, prijzen, knoppen). Verkopen worden lokaal bijgehouden in een verkoopbestand (zie § 7).
- Enkel voor **facturen maken op de kassa** en voor de **online klantenkaart** is een live verbinding met de server nodig. Daarvoor draait op de kassa op de achtergrond ook een Jamadata Desktop (JMD) met een eigen postnummer. Bij het opstarten van het kassaprogramma zit een korte ingebouwde wachttijd zodat die JMD eerst kan starten.
- Artikelen en groepen komen van de hoofdcomputer. Het artikelbestand voor de kassa wordt op de server weggeschreven en naar de kassa overgezet (bestandsnaam gehoord als `KASPLU.DAT`, *te verifiëren*). De artikelnummers op de kassa zijn dezelfde als in het pakket.
- **Dagelijkse transfer met de hoofdcomputer (JMS)**: punt `N` in het kassamenu. Werkt in twee richtingen: haalt artikelen/prijzen op van de server en stuurt alles uit de kassamap (verkopen) naar de server. ± 80 % van de klanten gebruikt deze gewone transfer.
- **Transfer via de server van Jamadata**: punt `K` in het kassamenu, voor kassa's die niet in hetzelfde netwerk zitten als de hoofdcomputer en geen VPN hebben. De kassa zipt haar gegevens en zet ze op de centrale communicatieserver; op de hoofdcomputer staat een icoon "doorsturen/ophalen gegevens kassa" om ze daar op te halen en nieuwe gegevens klaar te zetten. Afbreken van een wachtende verbinding: `Esc` of het kruisje.
- Verandert het IP-adres van de server, dan moet ook de communicatie-instelling op elke kassa aangepast worden (zie server-document).
- Bij klanten met de **Mono**-versie kan support niet via de eigen supportpost in het pakket van de klant kijken; daar is een gewone schermovername met medewerking van de klant nodig. (opleiding 19-05-2026, ca. 00:21)
- Voor problemen op de kassa heb je **het scherm van de kassa zelf** nodig; via een pc in een ander gebouw kan je niets zien. (opleiding 20-05-2026 voormiddag, ca. 00:06)

## 2. Opstarten en afsluiten

Bron: opleiding 28-05-2026 (ca. 00:00–00:03).

- Nieuwere kassa's draaien op Windows 10 IoT (uitgeklede Windows 10). De aan/uit-knop zit achteraan; het lampje is rood als de kassa uit staat en wordt blauw bij het opstarten.
- Op nieuwere kassa's (Windows 10 en later) staat een Windows-wachtwoord. Omdat er vaak geen toetsenbord aan hangt, is een **afbeeldingswachtwoord** ingesteld (drie aanrakingen op vaste plaatsen op de afbeelding); bij een fout moet het gewone wachtwoord ingetikt worden. (Wachtwoord en aanraakpunten: zie interne bron/handleiding.) Oudere kassa's (vóór Windows 10) hebben geen wachtwoord.
- Het kassaprogramma start normaal automatisch; anders via het icoon van de kassa op het bureaublad. Je komt in het **kassamenu**; van daaruit start je de kassafunctie met punt `1` "Opstarten kassa" (of `F8`).
- Afsluiten: bovenaan "Stoppen" tot in het kassamenu, daar stoppen tot in Windows, dan Windows afsluiten.
- **Sluit de kassa elke avond af**, zeker op de laatste dag van de maand (zie § 7.3).

## 3. Artikelen aanslaan

Bron: opleiding 28-05-2026 (ca. 00:06–00:17 en 00:36–00:38).

Het verkoopscherm: links het cijferblok, rechts de groepen (door de klant zelf in te stellen, met kleuren). Een groep openen toont de artikelen; een knop in een afwijkende kleur kan een promotie zijn of een subgroep waarin je verder kan. "Terug" gaat een scherm terug.

Drie manieren om een artikel aan te slaan:

1. **Knoppen**: groep kiezen → artikel aanraken.
2. **Scannen** van de barcode.
3. **PLU**: toont de alfabetische lijst van alle artikelen. Je kan beginletters intikken, of "zoek in naam" gebruiken (zoekt overal in de omschrijving, niet enkel aan het begin). De PLU-lijst blijft op de plaats staan, handig om verschillende smaken na elkaar te kiezen. Met een artikelnummer: nummer intikken + `PLU`.
   - Valkuil: heeft de klant per ongeluk een artikel aangemaakt met een code van één cijfer (bv. code 5), dan pakt "5 + PLU" meteen dat artikel in plaats van 5 stuks te zien als aantal.

Regels:

- **Eerst het aantal, dan het artikel.** Zonder aantal = 1.
- Standaard wordt een **bak** (de verpakkingseenheid) aangeslagen, mét het bijhorende leeggoed. Voor losse flessen: aantal → knop **Stuks** → artikel. Zolang Stuks actief is, staat "ST" op het scherm.
- **Idem**: herhaalt het laatste artikel. "4 + Idem" voegt er vier toe; "Idem" alleen voegt er één toe; "− 2 + Idem" haalt er twee af. Past ook het leeggoed mee aan. Werkt altijd op het **laatst aangeslagen** artikel.
- **Clear**: wist een ingetikt aantal (geen artikel).
- **Ticket**: toont het ticket; daar kan je een lijn aanraken om ze te verwijderen (het bijhorende leeggoed gaat mee weg).
- **Subtotaal**: zet een tussentotaal op het ticket (bv. aankopen voor twee personen op één ticket).
- **Maal / Min / Plus**: Maal is zelden nodig; Min maakt het volgende aantal negatief (teruggave); Plus heft een ingetikte Min weer op.
- **Einde**: ticket afsluiten en betaalmiddel kiezen (zie § 5).

## 4. Leeggoed, kortingen en prijzen

Bron: opleiding 28-05-2026 (ca. 00:38–00:51).

### 4.1 Leeggoed

- **Auto leeggoed (LA)**: staat standaard aan; bij elk artikel wordt het leeggoed automatisch meegeteld. De knop zet dit uit of aan. Bij elk nieuw ticket staat het weer op automatisch.
- **Leeggoed OK**: de klant brengt exact hetzelfde leeggoed terug als hij meeneemt. Eén druk op het einde van het ticket trekt al het aangerekende leeggoed van dit ticket weer af.
- **Leeggoed terug** (leeggoed retour): daarna neemt elk artikel dat je kiest **enkel zijn leeggoed** (negatief), niet het artikel zelf. Handig als je de leeggoedwaarde van een artikel niet kent (afwijkend leeggoed): kies gewoon het artikel waarvan de lege bak binnenkomt.
- **Zelf leeggoed ingeven**: `−` aantal → groep Leeggoed → de juiste waarde (bv. "− 5" + leeggoed van 5 euro; "− 3" + fles 0,20). Hier hoef je Stuks niet te gebruiken: elk leeggoedartikel heeft zijn eigen waarde.
- **Opbouw leeggoed van een bak**: bak + flessen. Voorbeeld uit de opleiding: lege bak 2,10 + 24 flesjes × 0,10 = 4,50. Een halfvolle bak retour: "− 1" lege bak (2,10) en "− 6" flesjes (0,10).
- Leeggoedwaarden verschillen per product (4,50 komt veel voor, maar bv. water is anders).
- Leeggoed kan ook met de PDA geteld worden.
- Aandachtspunt: de **stock van leeggoed** klopt bij klanten vaak niet. Losse flesjes worden vermoedelijk automatisch per 24 naar een bak omgerekend, terwijl losse flesjes (in een zak) geen bak zijn. Bij een stocktelling moeten ook de lege bakken en lege flessen geteld worden. *(werking omrekening te verifiëren bij ontwikkeling)*

### 4.2 Kortingen en prijswijziging

- **Korting in euro**: bedrag + kortingsknop. Geldt altijd voor het **laatst aangeslagen artikel**; geef ze dus meteen na het juiste artikel, anders kloppen de statistieken per artikel niet.
- **Korting in procent**: percentage + procentknop, ook op het laatste artikel. Er wordt **nooit procentkorting op leeggoed** gegeven.
- **EP (eenheidsprijs)**: nieuwe prijs + `EP` wijzigt de prijs van het laatste artikel (bv. als de prijs in de winkel anders geafficheerd stond).
- **Horeca**: schakelt naar een ander prijsniveau uit het pakket. Elke druk gaat een niveau verder (op het scherm P1, P2, P3) en daarna terug naar de gewone kassaprijs. In totaal zijn er dus de kassaprijs en drie andere prijzen mogelijk; welke prijs uit het pakket bij welk niveau hoort, is met parameters instelbaar. Gebruikt voor bv. horecaklanten die komen afhalen.
- Probleem gemeld bij klanten met mix-promoties: een bewaarde bon die later opnieuw wordt opgeroepen en aangevuld, kreeg een ander totaal. Vermoedelijk een fout bij het bewaren van bons met promoties; moet door ontwikkeling nagekeken worden met de gegevens van de klant. *(onzeker)* (opleiding 19-05-2026, ca. 00:20–00:28)

## 5. Betalen: betaalmiddelen, bon en cadeaubon

Bron: opleiding 28-05-2026 (ca. 00:09, 00:30 en 01:02–01:13).

- Na **Einde**: bedrag intikken + betaalmiddel (geld, betaalautomaat, maaltijdcheque, ecocheque, consumptiecheque, ...). Bij cash toont de kassa het terug te geven bedrag (ook op het klantendisplay en het ticket), gaat de geldlade open en wordt het ticket gedrukt.
- De meeste betaalknoppen zijn vaste knoppen (tekst niet aanpasbaar); er zijn enkele vrij instelbare betaalmiddelen waarvan tekst en parameters te kiezen zijn. Bij de klant worden enkel de gebruikte betaalmiddelen getoond.
- Een gekoppelde betaalterminal moet verbonden zijn; anders kan het betaalmiddel "betaalautomaat" niet afgewerkt worden.
- **Alarm/geldlade-knop**: opent de geldlade zonder verkoop. Volgens de opleiding kan er in de parameters een code aan gekoppeld worden *(te verifiëren)*.

### Kortingsbon van een fabrikant ("Bon")

- Een kortingsbon die aan een product hangt (bv. 1 euro korting, uitgegeven door de producent) verwerk je bij het afrekenen als **betaalmiddel "Bon"** (bedrag + Bon), niet als korting.
- Verschil: een korting gaat van de omzet/marge van de winkel af; een bon is een betaalmiddel dat de winkelier terugbetaald krijgt door de bonnen in te sturen naar de verwerker. Let op de geldigheidsdatum: te laat ingestuurde bonnen worden niet terugbetaald.

### Cadeaubon: twee systemen

1. **Als artikel**: een artikel "cadeaubon/geschenkbon" met vrije prijs verkopen (prijs zetten met EP) en bij het inleveren hetzelfde artikel negatief aanslaan (Min + bedrag via EP). Hierbij wordt btw aangerekend bij verkoop; zet het artikel dan op het hoogste btw-tarief (21 %) om discussie met de fiscus te vermijden. Nadeel: bonnen die nooit ingeleverd worden, vertekenen omzet en btw.
2. **Als betaalmiddel** (nieuwer systeem, zit ook in het pakket): via **Diverse → Verkoop cadeaubon** verkoop je een bon voor een bedrag (geen aantal, geen artikel – vergelijk met een betaalkaart met een tegoed). Bij het inleveren kies je bij het afrekenen het betaalmiddel **Cadeaubon**.

Welke methode de klant gebruikt, is een boekhoudkundige keuze van de klant en zijn boekhouder.

## 6. Klantenkaart

Bron: opleiding 28-05-2026 (ca. 00:18–00:36).

- De knop **Klantenkaart** opent de online klantenkaart; hiervoor is de verbinding met de server nodig. Reageert het scherm niet, dan wacht de kassa op die verbinding (kan lang duren); zie de opmerking hieronder.
- Een klant wordt geïdentificeerd met zijn **identiteitskaart** (kaartlezer): bij een nieuwe klant worden naam, adres en geboortedatum van de kaart gelezen. Manueel een klant aanmaken kan ook, maar dan moet alles ingetikt worden. Zoeken kan op naam (zoekt op alle velden).
- **Punten**: het aantal punten per euro is instelbaar (in de demo 1 punt per euro). Boven een drempel (in de demo 500 punten) drukt de kassa automatisch een extra ticket met een waardebon (in de demo 5 euro) en worden de punten van het saldo afgetrokken.
- In de klantenkaartfiche: e-mailadres (staat niet op de identiteitskaart, zelf aan te vullen), codes voor promomailings, GDPR-akkoord (de klant hoort een toestemming te ondertekenen; daarna aanvinken), klant sinds, omzet, laatste aankopen met punten. Via `+`: extra opties, o.a. omzet per artikelgroep, GDPR-export, een tweede kaart koppelen aan dezelfde klant.
- **Verenigingskaarten**: leden van een vereniging sparen met hun kaart ook voor de vereniging (als vorm van sponsoring).
- Prik&Tik-winkels gebruiken een extern klantenkaartsysteem (Freedelity – *schrijfwijze te verifiëren*), waarbij de punten online bij die aanbieder bijgehouden worden en de klant ze via een webtoepassing kan raadplegen. Dat is niet het ingebouwde systeem.
- **Factuur- of klantenkaartscherm blijft hangen op de kassa**: het scherm van de bijhorende post op de server hangt vast. Oplossing: de werkposten herstarten (Help → alle posten herstarten) nadat gecontroleerd is dat niemand een bon of factuur aan het maken is.

## 7. Verkoopbestand van de kassa

Bron: opleiding 20-05-2026 voormiddag (ca. 00:38–01:01).

Er bestaan twee systemen; welk een kassa gebruikt, zie je aan de bestanden in de kassamap (`C:\Kassa`).

### 7.1 Oud systeem: KASLOG.DAT

- `KASLOG.DAT` = het huidige verkoopbestand. `KASLOG.001` = het vorige; het wordt aangemaakt op het moment dat de klant het verkoopbestand wist. De datum/tijd van het bestand toont wanneer de laatste verkoop erin geschreven is.
- Het bestand heeft een **maximum aantal records** (bv. 70.000 of 90.000; kan uitgebreid worden). Bedoeling is dat er ongeveer één maand in past. In het kassamenu toont de knop bovenaan hoeveel dagen en records gebruikt zijn. Is het bestand vol, dan krijgt de klant een melding.
- **Wissen**: kassamenu punt `A` "Wissen van de verkoopgegevens van de kassa". Dit wist **altijd het volledige bestand** (er kan geen periode gekozen worden).
  - Doe dit dus enkel **'s morgens vóór de eerste verkoop** of **'s avonds na de laatste verkoop**. Midden op de dag wissen = de verkopen van die dag zijn weg.
- **Volgorde vóór het wissen** (einde van de dag):
  1. Kassamenu → `F9` Controle → **Druk af** (controleband/totalen op ticket).
  2. Dagelijkse transfer met de hoofdcomputer (punt `N`), zodat de verkoopbestanden op de server staan.
  3. In het pakket: hoofdmenu Voorraad → `2` → **Inlezen van de verkopen** (zie § 7.2).
  4. In hetzelfde menu punt `4` **Kassaverslag** (van datum tot datum; pdf).
  5. Pas daarna punt `A` op de kassa.

### 7.2 Verkopen inlezen in het pakket – let op de datum

- Het scherm toont per kassa tot welke datum er al **ingelezen** is, en van wanneer (datum én uur) het verkoopbestand is dat op de server staat.
- Lees in **vanaf de dag na de laatst ingelezen dag tot en met de laatste volledige dag**. Voorbeeld uit de opleiding: ingelezen tot de 16e; het bestand op de server is van de 18e om 09.46 u → lees in van de 17e t/m de 17e. De 18e is nog niet volledig; lees je die toch in, dan zit er maar een stukje van die dag in. Dit gaat bij klanten heel vaak fout.
- Het pakket waarschuwt als het verkoopbestand niet recent is (ouder dan 18 uur) of als er in de periode al verkopen ingelezen zijn. Een waarschuwing kan met `F4` genegeerd worden, maar doe dat enkel bewust.
- **Een al ingelezen dag opnieuw inlezen** (omdat hij onvolledig was): zelfde scherm, datum van–tot die dag, kassanummer, en dan `F9` (opnieuw inlezen); bevestig de vraag om te overschrijven met ja. Je kan hier in principe niets stukmaken, want opnieuw inlezen blijft mogelijk zolang het bestand er is.

### 7.3 Nieuw systeem (sinds ± 2019): één bestand per maand

- In plaats van `KASLOG.DAT` maakt de kassa een bestand **per maand**: `KL` + jaar + maand (bv. `KL202605`). De bestanden blijven bewaard, zodat verkopen van maanden terug beschikbaar blijven (ook ingevoerd met het oog op fiscale controles) en de klant niets meer zelf moet wissen.
- **Het nieuwe maandbestand wordt aangemaakt op het moment dat de kassa(functie) opstart.** De klant moet dus zijn kassa afsluiten op de laatste dag van de maand.
- Vergeet de klant dat (gebeurt bijna elke maand ergens), dan blijft de kassa op de 1e in het bestand van de vorige maand schrijven:
  - stopt hij de kassa op het einde van die dag, dan zit één volledige dag in het "verkeerde" maandbestand. Is dat een probleem, dan kan je door **tijdelijk hernoemen** van de bestanden de kassa naar het juiste bestand laten kijken (de kassa kijkt enkel naar de bestandsnaam);
  - stopt hij de kassa **midden op de dag**, dan zit die dag verdeeld over twee bestanden. Daarvoor bestaan hulpprogramma's (een deel uit het ene en een deel uit het andere bestand inlezen), maar dit is complex → escaleren.

### 7.4 Een vergeten afdruk van de vorige periode alsnog maken (oud systeem)

Situatie: de klant heeft het verkoopbestand gewist zonder de controleband/totalen af te drukken.

1. Hernoem het huidige `KASLOG.DAT` naar een tijdelijke naam (bv. `KASLOG.NEW`).
2. Hernoem `KASLOG.001` naar `KASLOG.DAT`. De kassa werkt nu met het oude bestand.
3. Maak de nodige afdrukken (F9 Controle → Druk af).
4. Zet de namen exact terug zoals ze waren (`.DAT` → `.001`, tijdelijke naam → `.DAT`).

Belangrijk:

- **Verwijder nooit verkoopbestanden**; enkel hernoemen. Weg is weg, en als er geen transfer gebeurd is, bestaat er buiten de kassa geen kopie.
- Open de bestanden niet door te dubbelklikken (Windows opent ze in Kladblok).
- Doe geen verkopen terwijl de bestanden omgewisseld zijn.

## 8. Dagtotalen: F9 Controle

Bron: opleiding 20-05-2026 voormiddag (ca. 00:03–00:07).

- Pad: kassamenu → `F9` Controle → **Druk af**.
- In dit scherm staan parameters die bepalen wát afgedrukt wordt:
  - enkel **particuliere verkopen** (alle gewone tickets, zonder de bons/facturen) – de normale standaard;
  - enkel **bons/facturen**;
  - **apart en totaal** (strook particulieren, strook bons en een totaal);
  - **allemaal** samengeteld – normaal niet gebruiken.
- Wijzigingen gelden enkel voor die ene keer, tenzij onderaan **"Neem deze parameters als standaard"** gekozen wordt; dan blijven ze bewaard, ook na een herstart van de kassa.
- **Typische klacht: "mijn dagtotaal klopt niet / er staan maar 8 tickets op terwijl er 50 klanten waren".** Oorzaak: iemand heeft per ongeluk "enkel bons/facturen" gekozen en als standaard bewaard. Oplossing: terugzetten op "enkel particuliere verkopen", "Neem deze parameters als standaard", opnieuw afdrukken. De verkopen zelf zijn niet weg.

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):

- gedocumenteerde kennisoverdracht VI-20260507_141735-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260519_140734-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260520_100445-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260528_100522-Opname van vergadering.txt
