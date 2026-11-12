# Door de expert bevestigde praktijk

Gebruik dit document voor: algemene vragen over hoe Jamadata in de praktijk bij klanten wordt gebruikt (wie doet wat, wat gebeurt automatisch en wat niet) en om te weten waar een antwoord per klant verschilt. De inhoud komt uit 45 vragen die rechtstreeks door een ervaren Jamadata-medewerker zijn beantwoord. Het zijn bevestigingen van de praktijk, geen test op elke installatie.

Veel antwoorden luiden "dit verschilt per klant of installatie". Vraag in die gevallen eerst naar de concrete installatie voor je stappen geeft.

## Back-ups en herstel

- Back-ups worden door Jamadata én door de klant of diens IT-partner geregeld; de afspraken verschillen per klant. Ga er nooit van uit dat er een actuele, bruikbare back-up is.
- De afspraken staan in het klantendossier; anders navragen bij een Jamadata-medewerker, de klant of de IT-partner.
- Een back-up terugzetten gebeurt door een ervaren Jamadata-medewerker. Een junior doet dit niet zelfstandig.
- Een leesbaar back-upbestand (bv. een zip die opent) bewijst niet dat de database herstelbaar is.
- Of gebruikers moeten stoppen tijdens een back-up hangt af van de methode: bij de handmatige USB-back-up wel (schermen afgesloten of op het hoofdmenu), bij de online back-up niet (achtergrondproces). Zie `backup-en-herstel.md`.

## Toegang en gebruikersrechten

- Gebruikersrechten worden beheerd door een Jamadata-medewerker of een verantwoordelijke bij de klant. Dat geldt ook voor het intrekken van toegang bij vertrek van een medewerker.
- Bij sommige klanten delen medewerkers één gebruikersnaam. Dat is een vaststelling, geen aanbeveling.
- Op een kassabon kunnen, afhankelijk van de instellingen, klantnaam, adres, klantenkaartnummer of spaarpunten en zelfs identiteitskaartgegevens staan. De klant beslist mee welke gegevens verschijnen; afspraken zijn soms schriftelijk, soms mondeling.

## Peppol en facturatie

- Jamadata kan via Peppol facturen versturen, facturen ontvangen en creditnota's versturen, via een externe dienst. De mogelijkheden verschillen per versie en klant.
- Ontvangen Peppol-facturen komen automatisch binnen, maar worden **niet automatisch geboekt**: een medewerker controleert en boekt zelf.
- Bij een fout in een ontvangen factuur: niet boeken zolang de fout er is. Afhankelijk van de situatie vraagt men de leverancier een correcte factuur of een creditnota, of past men handmatig aan in Jamadata.
- Dubbele facturen: Jamadata waarschuwt automatisch op basis van het factuurnummer en kan het opslaan blokkeren. Dit hangt af van versie en factuurtype en is geen absolute garantie.
- Mislukte verzending: eerst de status of foutmelding bekijken, dan opnieuw verzenden, zo nodig langs een andere weg bezorgen of Jamadata contacteren. Controleer altijd eerst of de factuur niet al verzonden is.
- De verzendstatus staat in Jamadata bij de factuur en in het overzicht van verzonden facturen.
- Peppol-facturen worden bewaard in Jamadata en in een map op de computer of server.
- Welke handleiding voor inkomende Peppol geldt, hangt af van de module: 0033A voor enkel boekhouding (menu B.1), 0255C voor boekhouding met voorraad (B.1 en V.1).

## Kassa en boekhouding

- Kassaverkopen komen in de boekhouding via handmatige overdracht of doordat een medewerker ze zelf boekt. Er is geen automatische synchronisatie; het verschilt per installatie.
- Het kasverslag (0290B) is gebaseerd op het echte verkopenbestand en staat los van "Inlezen verkopen".
- Foute kassaverkopen of retouren worden gecorrigeerd via een correctie in de kassa, een retourbon of een creditnota.
- Kascontrole: contant geld tellen en vergelijken met het kassarapport; kaartbetalingen vergelijken met het terminalrapport.

## Betaalterminals en terugbetalingen

- Er bestaan gekoppelde en losstaande terminals. Bij een gekoppelde terminal gaat het bedrag automatisch naar de terminal en komt het resultaat terug naar de kassa; bij een losstaande voert de medewerker het bedrag zelf in. Vraag eerst welk type de klant heeft.
- Een kaartbetaling wordt in de praktijk niet via de terminal terugbetaald. De klant krijgt contant geld, een tegoedbon, of een verrekening bij een volgende aankoop.

## Cadeau- en tegoedbonnen

- Een aankoop kan volledig of gedeeltelijk met een bon betaald worden; meerdere bonnen per aankoop kan.
- Is de bon meer waard dan de aankoop, dan blijft het restbedrag op de bon, wordt het contant teruggegeven of komt er een nieuwe tegoedbon. Dat hangt af van het type bon en de klant.
- De medewerker controleert de waarde van een bon handmatig; er is geen automatische saldocontrole.
- Wanneer btw wordt berekend (bij verkoop of bij gebruik) hangt af van het type bon; de boekhouder van de klant bepaalt de verwerking.

## Klantenkaarten en spaarpunten

- Punten worden automatisch toegekend bij een gekoppelde kaart, door de kaart te scannen of het kaartnummer in te voeren; een medewerker kan ook handmatig punten toevoegen.
- Klant- en verenigingspunten kunnen bij sommige installaties tegelijk gespaard worden. Niet elke klant gebruikt verenigingspunten.
- Kassamedewerkers, winkelverantwoordelijken en Jamadata-medewerkers kunnen punten handmatig aanpassen.
- Van een handmatige aanpassing is zichtbaar wanneer en hoeveel, maar niet wie ze deed.
- Bij overstap naar een nieuw spaarsysteem worden bestaande punten handmatig overgezet.

## Scanners en PDA's

- Scanners dienen voor artikelen scannen aan de kassa, voorraad tellen en prijzen controleren of aanpassen.
- Gegevens gaan naar Jamadata via wifi, kabel of het laad-/aansluitstation, afhankelijk van het toestel.
- Een doorgestuurde voorraadtelling verschijnt in Jamadata, waarna een medewerker ze controleert en bevestigt. De voorraad wijzigt niet zonder die bevestiging.
- Bij problemen: batterij en verbinding controleren, toestel herstarten, daarna Jamadata contacteren. Niet blind opnieuw doorsturen.

## Promoties en kortingen

- Kortingen kunnen automatisch op artikelen of artikelgroepen, via de klantenkaart, tijdens een promotieperiode, of handmatig door de kassamedewerker.
- Afzonderlijke artikelen en volledige artikelgroepen kunnen van kortingen worden uitgesloten (bv. tabak).
- Een klantenkorting en een promotiekorting kunnen op dezelfde aankoop samen gelden.
- Wie kortingen mag instellen hangt af van de toegangsrechten.

## Afspraken voor het beantwoorden van vragen

- Bij twijfel: de beschikbare uitleg geven en duidelijk zeggen wat onzeker is.
- Begin met een kort antwoord en een praktijkvoorbeeld; details, bron en technische achtergrond volgen daarna.
- Bij tegenstrijdige handleidingen geldt de nieuwste; leg het verschil met de oudere versie uit.
- De documentatie is enkel voor intern gebruik door Jamadata-medewerkers.

## Bronnen

- `00_START_CLAUDE/01_NAAR_CLAUDE/01_EXPERTANTWOORDEN_45.md` (HUMAN-Q001 t.e.m. Q045)
- `00_START_CLAUDE/01_NAAR_CLAUDE/06_GERICHTE_HANDLEIDINGCONTROLES.md`
