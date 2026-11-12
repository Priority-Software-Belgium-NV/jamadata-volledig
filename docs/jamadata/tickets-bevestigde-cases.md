# Bevestigde supportcases en goedgekeurde kennisartikelen

Gebruik dit document voor: terugkerende supportmeldingen waarvan de aanpak door een Jamadata-expert is bevestigd of in een goedgekeurd kennisartikel staat. Elke case vermeldt zijn status; een case met status "open" beschrijft controles, geen bewezen oplossing.

Statussen:

- **Bevestigd door expert**: de aanpak is expliciet door een ervaren medewerker bevestigd.
- **Goedgekeurd kennisartikel**: inhoudelijk gevalideerd door de Jamadata-verantwoordelijke (14-10-2026).
- **Open**: controles zijn bekend, de definitieve oplossing niet.

Algemene regel bij elke case: begin met de eenvoudige, frequente oorzaak, stel één gerichte vraag tegelijk, en wijzig geen rechten, netwerkpaden of serverinstellingen op goed geluk.

## Peppol: niet-verzonden facturen in bulk verzenden

**Status:** bevestigd door expert.

**Symptoom:** facturen zijn nog niet via Peppol verzonden.

**Procedure:** ga naar **8 → H → C**, menu "Bekijken NIET verzonden facturen via Peppol". Geef een periode in. Er verschijnt een lijst van niet-verzonden Peppol-facturen die in één keer verzonden kan worden.

**Let op:**

- Dit is niet hetzelfde als de opvolging van één factuur via **8 → H → 1 → 1** (blauwe wolk, groene vernieuwknop). Die route haalt enkel de status op.
- Status raadplegen is niet opnieuw verzenden. Opnieuw verzenden gebeurt in hetzelfde scherm met F5/F4 (zie `peppol-`documenten). Controleer eerst of de factuur niet al verzonden is, om dubbele verzending te vermijden.

## Scanner Zebra/Symbol LI4278 piept, maar artikelen komen niet op de kassa

**Status:** bevestigd door expert; onderbouwd door opleiding (20-05-2026) en het programmeerblad.

**Eerste controle:** open Kladblok op de kassa-pc en scan een gekende barcode.

**Scenario A: vreemde tekens in Kladblok.** De scanner is waarschijnlijk verkeerd geprogrammeerd.

1. Neem het interne programmeerblad "TOMRA LI4278" (origineel, geen kopie van een scherm).
2. Scan de acht barcodes in volgorde, met enkele seconden pauze tussen elke barcode. De eerste barcode is "Set Defaults".
3. Blijft het probleem, scan dan barcode 2/8 opnieuw als laatste.
4. Test daarna zowel een gewoon artikel als een Tomra-bon.

**Scenario B: helemaal geen invoer in Kladblok, scanner piept wel.**

1. Trek eerst de **zwarte voedingskabel onderaan de cradle** uit. De scanner probeert dan opnieuw via USB te verbinden. Dit is niet hetzelfde als de USB-kabel uit de pc trekken.
2. Werkt de scanner weer, steek de voedingskabel terug in.
3. Scan indien nodig de koppelbarcode op de cradle.
4. Pas daarna escaleren.

**Grens:** dit geldt voor dit model. Vraag bij een ander toestel eerst merk en model.

## Kassa: blauwe knop voor online facturatie wordt groen

**Status:** controlepunten bevestigd door expert; concrete klantoplossing open.

**Symptoom:** na ongeveer vijf seconden verschijnt de groene knop, zonder foutmelding. Gewone verkopen blijven mogelijk en Jamadata op kantoor werkt.

**Betekenis:** blauw staat voor online facturatie, groen voor de oudere offline leveringsbonwerking. De kassa bereikt de server dus niet.

**Controles, in volgorde:**

1. Netwerkverbinding van de kassa.
2. De VPN, als die normaal nodig is tussen kassa en server.
3. Of het IP-adres van de server gewijzigd is.

Concludeer niet meteen dat een communicatiemodule gecrasht is.

## Zebra GK420t: etiketten fout na Windows-update

**Status:** aanpak besproken; uitkomst bij de klant niet vastgelegd.

**Symptoom:** etiketten worden verkeerd georiënteerd of uitgelijnd na een Windows-update.

**Controles:**

1. Driver **ZDesigner GK420t** nog correct ingesteld?
2. Etiketformaat **37 × 80 mm**, liggend, met **180° rotatie**.
3. Sensorinstelling controleren en indien nodig de markerdetectie kalibreren.

Zie ook `printers-zebra.md`.

## Oude PDA met USB-cradle synchroniseert niet

**Status:** aanpak besproken; uitkomst niet bevestigd.

**Controles:** verbinding en werking van **Windows Mobile Device Center (WMDC)**. Herinstallatie van WMDC is een gekende herstelstap. Vraag vooraf of er nog niet-doorgestuurde tellingen of bestellingen op het toestel staan, en wis of reset niets zonder controle op verlies en dubbels.

## Tomra: alle bonnen geven "ticket niet gevonden"

**Status:** escalatie-aanpak bevestigd; definitieve oplossing afhankelijk van de installatie.

**Eerste vraag:** gebeurt het bij één bon of bij alle bonnen?

**Bij alle bonnen:** controleer of de **T:-schijf** zichtbaar en bereikbaar is op de kassa. Een rechtenfout wijst op Windows-netwerktoegangsrechten: vraag een screenshot en de exacte foutmelding, wijzig zelf geen beveiligingsrechten en escaleer voor controle van de toegangsrechten.

**Ontbreekt de T:-schijf volledig:** volg de procedure hieronder.

## Tomra: T-schijf opnieuw koppelen op een kassa

**Status:** goedgekeurd kennisartikel (14-10-2026).

De netwerkstationsletter `T:` wordt gebruikt voor de koppeling met de Tomra-flessenautomaat. Het concrete netwerkpad verschilt per installatie.

1. Controleer in Windows Verkenner → Deze computer of `T:` ontbreekt.
2. Zoek het juiste UNC-netwerkpad in de installatiegegevens of klantdocumentatie. Het verwijst naar een gedeelde map op de server of een NAS. Neem niet standaard het pad van een andere kassa over.
3. Controleer of die share bereikbaar is. Ontbreekt de documentatie, stop dan en vraag de bevoegde beheerder; gis geen servernaam of pad.
4. Kies in Windows "Netwerkverbinding maken" en selecteer `T:`.
5. Geef het pad op en gebruik de bestaande, bevoegde Windows-aanmeldgegevens.
6. Vink **Opnieuw verbinden bij aanmelden** aan en voltooi.
7. Controleer of `T:` en de bestanden weer toegankelijk zijn.
8. Doe een functionele test van de Tomra-koppeling op die kassa. Sluit het ticket pas af als zowel de schijf als de Tomra-werking bevestigd is.

Een stroomonderbreking wordt als mogelijke oorzaak genoemd, niet als bewezen diagnose.

## Tekst 1 en 2 ontbreken op de leverbon, tekst 3 verschijnt wel

**Status:** open; werking gedocumenteerd, klantwens niet bevestigd.

**Werking:** Jamadata heeft vier teksten bij de facturatieparameters (**Hoofdmenu → verborgen plus-parameters → 4, facturatieparameters**).

- **Tekst 1 en 2** worden bij het opmaken van een bon gekozen of ingevoerd.
- **Tekst 3 en 4** kunnen via programmatie automatisch op bons en facturen verschijnen.

**Eerste vraag aan de klant:** moeten tekst 1 en 2 automatisch op elke leverbon komen, of wil de klant ze bij het opmaken kiezen? Besluit niet vooraf dat de afdruk fout is of dat programmatie gewijzigd moet worden.

(uit opleiding 23-06-2026, vanaf ca. 00:27)

## Boeking komt op "verkoop onbekende samenstelling"

**Status:** uit opleiding van 06-11-2026; niet afzonderlijk getest. De toepassing hangt af van firma, rekeningplan en versie.

**Verklaring:** de boeking verwijst naar een grootboekrekening die voor de gekozen grootboekextensie en het btw-percentage niet bestaat in die firma. Het bedrag komt daardoor op een verzamelrekening. Een grootboekextensie is een code waarmee Jamadata de boekhoudrekening bepaalt; het is geen universeel rekeningnummer.

**Onderzoeksvolgorde (enkel bekijken, niets opslaan):**

1. Vraag de exacte melding en controleer in welke **firma** de medewerker werkt. In de verkeerde firma zoek je de verkeerde gegevens.
2. Zoek de factuur op via bekijken/herafdrukken (**8 → H → 1 → 1**) en bekijk de betrokken regel.
3. Staat er een artikel op de regel, bekijk dan de artikelfiche en het vervolgscherm met de grootboekextensie.
4. Controleer of de rekening die bij die extensie en dat btw-percentage hoort werkelijk bestaat in deze firma.
5. Staat er geen artikel op een kassaverzamelregel, zoek dan de dag en de controleband op. Het bedrag kan uit meerdere kleinere verkopen bestaan.
6. Een export van artikelen met artikelcode, omschrijving en grootboekextensie helpt om afwijkingen te vinden. Dit is enkel analyse: niet terug importeren of in bulk aanpassen.

**Oplossingsrichtingen:** een passende bestaande extensie kiezen, of de ontbrekende grootboekrekening laten aanmaken. Die keuze, en wat er met reeds geboekte bedragen moet gebeuren, is aan de boekhoudverantwoordelijke van de firma. Extensie 0, 5 of 8 is op zich niet goed of fout.

## Automatisch mailen via SMTP instellen en controleren

**Status:** goedgekeurd kennisartikel (14-10-2026).

SMTP-server, poort, account, TLS en authenticatie zijn afhankelijk van de klantconfiguratie.

1. Raadpleeg het ticket en de goedgekeurde configuratie van deze installatie. Het bestand `IMS.ini` dient als referentie; het kan wachtwoorden bevatten en hoort niet in tickets of documentatie.
2. Open in Jamadata: **+ → J (IMS-instellingen) → 5 (E-mail-instellingen)**, kies het profiel en gebruik **F8**.
3. Bekijk de relay-/SMTP-instellingen: server, poort, account, authenticatiemethode en beveiliging/TLS. Neem enkel waarden over die voor deze klant gelden.
4. Leg de bestaande instellingen vast voor je iets wijzigt, zodat je kan terugkeren. De instellingen gelden voor de server en kunnen vanaf een werkpost worden ingesteld.
5. Bewaar en gebruik **Stuur testmail**.
6. Controleer de logging op fouten en bevestig dat de testmail werkelijk is aangekomen (ook in ongewenste e-mail kijken). Eén geslaagde test garandeert geen blijvende bezorging.
7. Noteer de uitkomst in het ticket; herstel bij problemen de vorige instellingen of escaleer.

Zie ook `mail-`documenten voor de volledige mailinstellingen.

## Overdracht aan een senior

Noteer bij escalatie: het probleem, installatie/toestel en versie, de exacte foutmelding, het tijdstip, welke controles al zijn uitgevoerd met hun resultaat, en wat nog niet gedaan is. Geen wachtwoorden of onnodige persoonsgegevens.

## Bronnen

- `Jamadata ChatBot/Jamadata_Ticket_Cases.md` (cases 001–007, bijgewerkt 30-10-2026)
- `00_START_CLAUDE/01_NAAR_CLAUDE/02_GOEDGEKEURDE_ARTIKELEN.md` (Tomra T-schijf, SMTP)
- `00_START_CLAUDE/01_NAAR_CLAUDE/03_JUNIOR_PRAKTIJKKAARTEN.md`
- `00_START_CLAUDE/01_NAAR_CLAUDE/05_VERKOOP_ONBEKENDE_SAMENSTELLING.md`
- `00_START_CLAUDE/01_NAAR_CLAUDE/06_GERICHTE_HANDLEIDINGCONTROLES.md`
