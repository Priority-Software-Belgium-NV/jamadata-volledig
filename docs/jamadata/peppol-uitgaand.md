# Peppol: uitgaande facturen versturen (klantenfiche, facturatie, status, herverzenden)

Gebruik dit document voor: vragen over het activeren van Peppol op een klantenfiche, het versturen van verkoopfacturen via Peppol (CodaBox of een ander access point), het opvragen van de verzendstatus, het opnieuw versturen van een factuur, de lijst van niet-verzonden Peppol-facturen, de Peppol-parameters en de hulpprogramma's om Peppol in bulk te activeren. Inkomende (aankoop)facturen staan in `peppol-inkomend.md`; veelgestelde vragen en storingen in `peppol-faq-en-problemen.md`.

## 1. Begrippen

- **E-factuur / Peppol**: een e-factuur is geen pdf maar een gestructureerd XML-bestand (UBL) volgens de Europese Peppol-norm. De pdf zit er als bijlage in. De ontvanger kan de factuur (semi)automatisch verwerken.
- **Access point**: de dienst die de factuur op het Peppol-netwerk zet. In de bronnen komen voor: **CodaBox** (onderdeel van Wolters Kluwer) en **Easy-Systems**. Welke van de twee gebruikt wordt, hangt af van de installatie/het contract van de klant. In de schermen van Jamadata staat nog de tekst "Facturen electronisch versturen via Codabox", ook als een ander access point gebruikt wordt (onzeker / te verifiëren per installatie).
- **Peppol-ID**: vier cijfers (schema) + dubbele punt + nummer. Zie `peppol-faq-en-problemen.md` voor de schema-codes (9925, 0208, 0088).
- Peppol wordt **enkel voor facturen** gebruikt. Leveringsbons worden verder verstuurd zoals vroeger.

## 2. Peppol activeren op de klantenfiche

Waar: Hoofdmenu voorraadbeheer → **9** (beheer basisgegevens) → **2** (beheer klanten) → **1** (aanpassen/bekijken van een bestaande fiche). Kort: **9.2.1**.

Stappen:

1. Geef de klant in.
2. Druk zo nodig op **TAB** om de fiche te kunnen aanpassen.
3. Controleer dat het **btw-nummer** is ingevuld. Peppol-facturen worden altijd verstuurd op basis van het btw-nummer, of op basis van het **GLN-nummer** (Global Location Number) als dat is ingevuld.
4. Klik op het **groene/rode plusje (+) achter het e-mailadres**. Dit opent de mailinstellingen van de klant.
5. Vul bij **"Facturen electronisch versturen via Codabox"** een **P** (van Peppol) in.
6. Klik op het **groene i-icoontje** achter deze optie: Jamadata haalt dan de status van de klant op.
   - **Groen** = klant is aangesloten op het Peppol-netwerk.
   - **Rood** = klant is niet aangesloten.
   - Je kan enkel Peppol-facturen sturen naar klanten die aangesloten zijn op het Peppol-netwerk.

Bijkomende punten op de klantenfiche:

- **Ondernemingsnummer i.p.v. btw-nummer** (vzw's, verenigingen): vul het ondernemingsnummer in het veld "BTW-nummer" in en klik op het icoontje rechts van dat veld om aan te geven dat het een ondernemingsnummer is en geen btw-nummer.
- **GLN-nummer** (bv. scholen zonder btw-/ondernemingsnummer): invullen in het daarvoor voorziene veld onder het **+-icoontje naast het e-mailadres**. Het GLN-nummer kan gecontroleerd worden met het controle-icoontje, net zoals het btw-nummer.
- **Volgorde van de registratiecontrole**: 1) GLN-nummer (indien ingevuld), 2) btw-nummer, 3) ondernemingsnummer. Het GLN-nummer heeft altijd voorrang; een ondernemingsnummer is niet nodig als het GLN gekend is.
- In hetzelfde mailinstellingen-scherm geeft het **mail-icoon rechtsonder** een lijst van de naar deze klant verzonden facturen. Voor gewone (niet-elektronische) facturen kan je daar de bijhorende mail oproepen; voor elektronische facturen kan je de verzendstatus opvragen (zie punt 4).
- **Automatisch mailen en Peppol kunnen samen actief zijn.** Het automatisch mailen van facturen staat per klant ingesteld en moet je daar zelf afzetten als de klant de factuur niet meer per mail wil. In de beginfase wordt aangeraden om te blijven mailen, omdat je niet altijd weet waar een Peppol-factuur bij de klant terechtkomt (bv. rechtstreeks bij de boekhouder).

## 3. Een factuur versturen via Peppol

De werkwijze is dezelfde als bij het automatisch mailen van facturen, met twee verschillen:

- Je bent **verplicht een referentie in te vullen** (verplichting van Peppol). Je kan hier bv. het ordernummer of het factuurnummer herhalen.
- Op het **laatste detailscherm (eindscherm van de facturatie)** verschijnt de boodschap dat de factuur via Peppol/CodaBox verstuurd wordt ("Factuur wordt verstuurd via Codabox!").

Peppol voor één factuur uitschakelen:

- Naast de boodschap staat een **rood kruisje**. Klik je daarop, dan wordt deze factuur **niet** via Peppol verstuurd en verwerk je ze op de klassieke manier (afdrukken/mailen).
- Terug activeren voor deze factuur: ga met **F2 terug naar detail** naar het vorige scherm en kies daar opnieuw **F8 neem aan**. De tekst "Factuur wordt verstuurd via Codabox!" staat er dan terug.

Opmerkingen:

- Bij het aanmaken van de factuur controleert het systeem of de klant op dat moment op Peppol geregistreerd is. Is de klant tijdelijk niet bereikbaar (wissel van provider, storing op het netwerk, probleem met de registratie), dan kan de factuur niet via Peppol vertrekken en kan er een foutmelding verschijnen zoals **"ongeldig btw-nummer"**. Oplossing: Peppol voor die factuur uitzetten via het kruisje en klassiek verder verwerken.
- **Facturen via de kassa**: de werkwijze aan de kassa verandert niet. Op de achtergrond wordt de factuur verwerkt zoals op de computer.
- **Facturatie in serie (batch)**: een gemaakte factuur is definitief en kan achteraf niet meer aangepast worden. Controleer dus eerst de leveringsbons en factureer pas daarna in serie.
- Verschijnt er bij het verzenden geen foutmelding, dan mag je ervan uitgaan dat de factuur correct verstuurd is.

## 4. Verzendstatus van een Peppol-factuur opvragen

Waar: Hoofdmenu voorraadbeheer → **8** (facturatie) → **H** (herafdrukken facturen) → **1** (bekijken/herafdrukken gemaakte facturen) → **1** (bekijken/herafdrukken van 1 factuur). Kort: **8.H.1.1**.

1. Geef de factuur in.
2. Rechts bovenaan staat een **blauwe knop met een wolkje**. Klik erop om de verzendstatus te raadplegen.
3. Standaard staat de laatste status op **"Niet verzonden"**. Klik rechts onderaan op de **groene knop** om te verversen; je krijgt dan de actuele status. Staat die op **"verzonden"**, dan is de factuur goed op het Peppol-netwerk gezet.
4. In hetzelfde statusscherm kan je ook het **xml-bestand downloaden**.

Andere plaatsen waar je de status kan opvragen:

- **8.H.1.1**: geef de klant in en klik rechtsonder op het mail-/lijst-icoon: lijst van de verzonden facturen voor deze klant, met per elektronische factuur de statusknop.
- **Klantenfiche 9.2.1** → + achter e-mailadres → icoon rechtsonder: zelfde lijst.
- **Boekhouding B.4** (raadplegen van een rekening): geef de klant in en klik linksonder op het icoon: zelfde lijst.

Lijst van niet-verzonden Peppol-facturen:

- **8 → H → C**, periode kiezen: lijst van **NIET verzonden Peppol-facturen** (enkel bekijken). Dit is iets anders dan de mail-icoontjes en dan de status van één factuur via 8.H.1.1. (Bron: expertbevestigde case in de eerdere AI-kennislaag; te verifiëren op de installatie of het menupunt aanwezig is.)
- De verzendstatus tonen voor een hele lijst facturen tegelijk is bewust niet voorzien: het systeem zou voor elke factuur online de status moeten opvragen, wat te veel vertraging geeft.

## 5. Een factuur opnieuw versturen via Peppol

1. **8 → H → 1 → 1** en geef de factuur in.
2. Ga helemaal door tot het **laatste detailscherm**.
3. Druk op **F5** (dit is een verborgen toets, staat niet op het scherm).
4. Er verschijnt een bevestigingsscherm. Druk op **F4**: de factuur wordt opnieuw via Peppol verstuurd.

Let op het verschil: de **groene knop** in het statusscherm **ververst enkel de status**; **F5 + F4** op het laatste scherm **verstuurt opnieuw**. Verstuur niet opnieuw zolang niet vaststaat dat de eerste verzending mislukt is (risico op dubbele factuur bij de klant). Herverzenden in bulk is geen standaardhandeling voor een junior.

## 6. Peppol-parameters

Waar: vanuit het hoofdmenu (voorraad) **+** → **5** (parameters voorraad) → met **F8 – Neem aan** doorbladeren tot het scherm met de **Peppol-parameters**.

- Onderaan: optie **"Facturatie: alle klanten controleren en versturen via Peppol"**. Staat deze aan, dan controleert het systeem bij elke factuur automatisch of de klant Peppol-actief is. Is de klant nog niet geactiveerd (geen P op de fiche) maar wel Peppol-compliant, dan wordt de klant automatisch geactiveerd en vertrekt de factuur via Peppol. Er verschijnt hierbij geen aparte melding.
- Op dit scherm staat een **i-knop** die de **licentiegegevens** van de Peppol-aansluiting toont. Volgens de opleiding van 24-06-2026 werkt deze i-knop enkel bij CodaBox (en een tweede provider waarvan de naam in de opname niet duidelijk verstaanbaar is), **niet bij Easy-Systems**. Als de i geen licentiegegevens toont, zie `peppol-faq-en-problemen.md` ("ongeldige licentie").
- Voor Easy-Systems worden in de parameters o.a. een client-ID en client-secret ingevuld die de klant van Easy-Systems ontvangt (uit opleiding, 03-07-2025; exacte schermopbouw niet gedocumenteerd). Deze gegevens nooit in tickets of documentatie noteren.

## 7. Hulpprogramma's (bulk)

Waar: vanaf het hoofdmenu **+** → **H** (hulpprogramma's onder Parameters). Eerst bevestigen dat er een **back-up** gemaakt is.

| Punt | Programma | Effect |
|---|---|---|
| **4** | "Controleren registratie klanten als Peppol-ontvanger" | Controleert welke klanten op Peppol geregistreerd zijn en vult automatisch de **P** in op hun klantenfiche. Bevestigen met **F4 – Ja**. |
| **5** | "Automatisch mailen afzetten voor alle Peppol-geregistreerde klanten" | Zet het automatisch mailen van facturen in één keer uit voor alle Peppol-klanten. Bevestigen met **F4 – Ja**. |

Beide programma's moeten **per firma (dossier)** apart uitgevoerd worden.

## 8. Oudere werkwijze: UBL-factuur mailen via CodaBox (historisch)

In een oudere HOWTO (UBL 2.1 via CodaBox, vóór de rechtstreekse Peppol-koppeling) werkte het zo:

- De klant moest via een aanvraagformulier (`PEPPOL_by_CodaBox_licence_request.xlsx`) een licentie aanvragen bij CodaBox; na validatie werd het test-afzenderadres vervangen door het productie-adres. (Adressen: zie interne bron.)
- In Jamadata moest de **share voor de XML/UBL-facturen** juist staan: hoofdmenu **"+.4"**; de map **`UBL` onder de map `Share`** (`..\share\UBL`) moest bestaan.
- Op het eindscherm van de facturatie klikte je op het icoon om de factuur via CodaBox te versturen; er opende dan automatisch een mail die je zelf moest verzenden.

Dit is enkel relevant voor oude installaties. Op huidige installaties gebeurt het versturen automatisch zoals in punt 3. Onder de Jamadata-map staat ook nu nog een map met de UBL-bestanden van facturen (in de opname klinkt de naam als "fact UBL"; exacte mapnaam te verifiëren); die moet bij een herinstallatie/verhuis volledig mee overgezet worden (uit opleiding, 24-06-2026).

## 9. Verschillen tussen handleiding V3 en V4/V4.3

- V3 vermeldt het opnieuw versturen enkel als één regel (F5 op het laatste scherm bij herafdrukken). V4/V4.3 beschrijft het als aparte procedure met de bevestiging via **F4**.
- V4.3 vermeldt een **groen/rood** plusje achter het e-mailadres (V3/V4: groen plusje) en "zo nodig" TAB.
- Inhoudelijk is de procedure voor het activeren en versturen gelijk gebleven.

## Bronnen

- `2240A - Jamadata Peppol Handleiding en automatisch mailen V4.3.docx` (Jamadrink/Handleidingen modules) – recentste versie
- `Jamadata Peppol Handleiding V4.docx` en `Jamadata Peppol Handleiding V3.pdf` (Jamadrink) – enkel voor verschillen
- `Elektronische facturen via CodaBox.docx` (Jamadrink/Handleidingen modules)
- `Jamadata Peppol FAQ.docx` (Jamadrink)
- `HOWTO-aanvragen en installeren elektronische facturatie_UBL2.1_PEPPOL_Codabox.docx` (Jamadrink) – historisch
- Transcripties opleidingen: `Peppol_20250703_090232.txt`, `JJD New installation = Peppol Fout onoplosbaar-20260624_135151-Opname van vergadering.txt`
- 00_START_CLAUDE / `09_SMTP_OVERDRACHT_20261110_c84a219d/ITERATIE_1_INSTRUCTIES.txt` (anker 8-H-C / 8-H-1-1) en `08_SMTP_INTAKE_20261110_b93e51c4/00_CHECKPOINT_SMTP_INTAKE.md`
