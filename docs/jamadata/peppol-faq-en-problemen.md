# Peppol: veelgestelde vragen en problemen

Gebruik dit document voor: snelle antwoorden op klantvragen over Peppol in Jamadata (Peppol-ID, GLN, vzw's en scholen, automatisch mailen naast Peppol, dubbele aankoopfacturen, btw 6%, kassa ...) en voor het onderzoeken van storingen (factuur vertrekt niet, "ongeldig btw-nummer", status blijft "Niet verzonden", "ongeldige licentie" / JMS die vastloopt na een update). De volledige procedures staan in `peppol-uitgaand.md` en `peppol-inkomend.md`.

## 1. Snelzoeker

| Vraag | Kort antwoord | Waar |
|---|---|---|
| Peppol aanzetten voor één klant | **P** bij "Facturen electronisch versturen via Codabox" | 9.2.1 → + achter e-mailadres |
| Is de klant op Peppol? | Groen/rood via het **i**-icoon | zelfde scherm |
| Peppol aanzetten voor alle geregistreerde klanten | Hulpprogramma punt **4** | **+ → H** (per firma) |
| Automatisch mailen uit voor alle Peppol-klanten | Hulpprogramma punt **5** | **+ → H** (per firma) |
| Automatisch elke klant controleren bij facturatie | Optie "Facturatie: alle klanten controleren en versturen via Peppol" | **+ → 5**, F8 tot scherm Peppol-parameters |
| Status van één factuur | Blauwe wolk, groene knop = verversen | **8.H.1.1** |
| Lijst niet-verzonden Peppol-facturen | Periode kiezen, enkel bekijken | **8.H.C** (te verifiëren) |
| Factuur opnieuw sturen | Laatste scherm → **F5** (verborgen) → **F4** | 8.H.1.1 |
| Eén factuur níet via Peppol sturen | Rood kruisje naast de Peppol-melding op het eindscherm | facturatie |
| Inkomende Peppol-facturen | Boekhouding **B.1** / voorraad **V.1** | zie `peppol-inkomend.md` |
| Bewaarde pdf's raadplegen (zonder boekhouding) | | **V.8.H.P.1** |

## 2. Peppol-ID en identificatienummers

- Een Peppol-ID opzoeken: via de publieke **Peppol Directory** (`https://directory.peppol.eu`), zoeken op bedrijfsnaam, btw-nummer of GLN. Let op: sommige bedrijven zijn afgeschermd en verschijnen niet, ook al zijn ze Peppol-actief.
- Opbouw: **vier cijfers : nummer**. De vier cijfers zijn geen klantnummer maar het identificatieschema:

| Schema | Betekenis | Voorbeeld |
|---|---|---|
| **9925** | Belgisch btw-nummer | `9925:BE0123456789` |
| **0208** | Belgisch ondernemingsnummer (KBO) | `0208:0123456789` |
| **0088** | GLN-nummer (GS1, 13 cijfers) | `0088:1234567890123` |

- Het Peppol-ID moet altijd volledig vermeld worden, inclusief de vier cijfers.
- **GLN** wordt vooral gebruikt door bedrijven die met GS1-standaarden werken (retail, logistiek, FMCG) en door scholen. In Jamadata vul je het in op de klantenfiche (onder het + naast het e-mailadres). Bij de registratiecontrole heeft GLN altijd voorrang op btw- en ondernemingsnummer.
- **Vzw's/verenigingen** met enkel een ondernemingsnummer: nummer invullen in het veld "BTW-nummer" en met het icoontje rechts van het veld aanduiden dat het een ondernemingsnummer is.
- **Scholen**: meestal geen btw-/ondernemingsnummer maar wel een GLN.
- Is een organisatie geregistreerd met een geldig nummer (GLN, btw of ondernemingsnummer), dan moeten de facturen via Peppol verstuurd worden. Controlevolgorde: GLN → btw-nummer → ondernemingsnummer.

## 3. Veelgestelde vragen – uitgaand

- **Krijg ik een melding wanneer een klant zich op Peppol registreert?** Nee. Met de parameter "alle klanten controleren en versturen via Peppol" controleert het systeem bij elke factuur automatisch en verstuurt het via Peppol zodra de klant geregistreerd is.
- **Kan het automatisch mailen uit als de factuur via Peppol gaat?** Ja, per klant op de klantenfiche (sommige klanten willen de factuur nog per mail, bv. voor de boekhouder), of in één keer via hulpprogramma + → H → 5.
- **Klanten zijn nog niet klaar voor Peppol?** Aangeraden om in het begin te blijven mailen naast Peppol; beide verzendmethodes kunnen tegelijk.
- **Facturen via de kassa?** Werkwijze ongewijzigd; op de achtergrond wordt de factuur verwerkt zoals op de pc.
- **Leveringsbons?** Ongewijzigd; Peppol is enkel voor facturen.
- **Facturen in batch?** Een gemaakte factuur is definitief. Controleer eerst de leveringsbons, factureer daarna in serie.
- **Kan ik de verzendstatus van een hele reeks zien?** Niet per lijst (elke status vraagt een online opvraging). Geen foutmelding bij verzenden = correct verstuurd. Voor één factuur: 8.H.1.1.
- **Vraag over het access point van Easy-Systems zelf?** Die moet naar de supportdienst van het access point (ticket via hun support-mailadres; adres: zie interne bron / de FAQ zelf).

## 4. Veelgestelde vragen – inkomend en boekhouding

- **Aankoopfacturen komen binnen via mail, post én Peppol: controle op dubbel inboeken?** Kan via de boekhoudparameters: hoofdmenu **+** → **3** (Boekhoudparameters) → **2e scherm "Afdrukken documenten einde periode"**; daar staat de parameter die deze controle activeert. De exacte naam/waarde van de parameter staat enkel als schermafdruk in de FAQ (niet uitleesbaar; te verifiëren op het scherm).
- **Peppol-factuur is al manueel geboekt**: verwijderen via het **– icoon rechts onderaan** in "Overzicht factuur" → **"Schrap deze factuur"**. Daar kan je ook het Peppol-bestand downloaden.
- **Standaard kostenfactuur inboeken**: rechtstreeks via de boekhouding met **F9 – Boek BHK-BTW%**; bij de eerste keer de juiste kostenrekening invullen en **F10 – Maak GRB standaard** kiezen.
- **Artikel verkeerd gekoppeld**: aankoopfiche (F2) op de artikelfiche openen en het artikelnummer van de leverancier aanpassen of verwijderen.
- **Enkel pdf bewaren zonder boeking/stock/prijzen**: alleen voor klanten zonder Jamadata-boekhouding, met **"F10 – Boek factuur"**; raadplegen via **V.8.H.P.1**.
- **Aankopen aan 6% opsplitsen (voeding/dranken)**: kan niet via de boekhouding; wel via voorraadbeheer met een aankooprekening per artikel (als dat veld op de artikelfiche voorzien is).
- **Btw medecontractant**: boeken blijft zoals vroeger.
- **Twee aankoopdagboeken**: geen probleem, het systeem vraagt vóór het boeken het dagboek.
- **Factuur bekijken tijdens/na verwerking**: pdf-icoon achter elke factuurlijn in het overzicht; na verwerking via het pdf-icoon bij de leveranciersrekening.
- **Leveranciers zonder btw-nummer, kassabonnen, aangetekende zendingen**: komen nooit via Peppol; manueel inboeken.
- **Leveringen die al via leveringsbonnen verwerkt worden**: bestel- en leveringsprocedure blijft; de Peppol-factuur vervangt het manueel inboeken van de factuur.

## 5. Problemen en oplossingen

### 5.1 Factuur kan niet via Peppol verstuurd worden / melding "ongeldig btw-nummer"

Oorzaak: bij het aanmaken van de factuur wordt gecontroleerd of de klant op dat moment op Peppol geregistreerd is. Bij een wissel van provider bij de klant, een tijdelijke storing op het Peppol-netwerk of een registratieprobleem lukt dat niet.

Aanpak:

1. Controleer op de klantenfiche (9.2.1 → +) het btw-nummer / ondernemingsnummer / GLN en klik op het **i**-icoon: groen of rood?
2. Controleer eventueel in de Peppol Directory of de klant (nog) geregistreerd is.
3. Moet de klant nu gefactureerd worden: schakel Peppol **voor die ene factuur** uit met het kruisje op het eindscherm en verwerk de factuur klassiek (afdruk/mail). Zo kan de klant blijven factureren.
4. Later, als de registratie weer in orde is, kan de factuur opnieuw via Peppol verstuurd worden (8.H.1.1 → laatste scherm → F5 → F4).

### 5.2 Status blijft "Niet verzonden"

- De status in 8.H.1.1 (blauwe wolk) toont standaard de **laatst gekende** status. Klik eerst op de **groene knop rechtsonder** om te verversen.
- Blijft de status na verversen "Niet verzonden": kijk in de lijst niet-verzonden facturen (8.H.C) of het om één factuur of om een reeks gaat. Eén factuur: zie 5.1. Een hele reeks: wijst op een probleem met de aansluiting/licentie of de JMS (zie 5.3); niet in bulk herverzenden zonder beoordeling door een senior.

### 5.3 "Ongeldige licentie" bij Peppol / i-knop bij Peppol-parameters geeft geen licentiegegevens (CodaBox)

Context (uit opleidingen van 24-06-2026): CodaBox is voor Peppol overgegaan naar een nieuwe omgeving bij Wolters Kluwer. Een recente JMS-versie spreekt dat nieuwe endpoint aan (zelfde poort, andere URL). Bij enkele klanten gaf dit na de update een **ongeldige licentie** of liep de **JMS vast/crashte** zodra de Peppol-controle werd uitgevoerd, terwijl het met de oude JMS + bijhorende DLL's wel werkte.

Controle of de aansluiting werkt:

1. Hoofdmenu voorraad → **+ → 5** → **F8, F8 ...** tot het scherm met de Peppol-parameters → klik op de **i**: er moeten licentiegegevens verschijnen. (Werkt niet bij Easy-Systems; daar is de i niet bruikbaar.)
2. Roep een klant op via **9.2.1** → **+** → **i** bij de Peppol-optie: de registratiecontrole moet een resultaat (groen/rood) geven zonder dat het programma blijft hangen.

Wat bij één klant het probleem oploste (uit opleiding, 24-06-2026): een **volledig nieuwe ("clean") installatie van de Jamadata-server in een nieuwe map/op een andere schijfletter**, waarbij enkel de data wordt overgezet en de programmamap (`prog`) vers geleverd wordt door de ontwikkelaar. Dit is een **seniorhandeling** (services stoppen, schijf/partitie, shares, werkposten herkoppelen); de volledige stappen horen bij de installatie-/migratiedocumentatie. Hoofdlijnen zoals getoond:

- Iedereen uit het pakket; via de JMT alles stoppen (stop + remove), JMS één keer manueel starten en weer stoppen zodat de database proper afgesloten is (map `log` onder `fas` moet leeg zijn); de bijhorende Windows-service stoppen en uitschakelen.
- Nieuwe map `Jamadata` op een andere schijf/letter (in het voorbeeld een nieuwe J-partitie i.p.v. T).
- **Selectief** overzetten: de database (`fas`, zonder de oude dossiers – die kunnen in een aparte `fas old`), de map met UBL-facturen, de map met documentkopieën (in de opname "FT copy" genoemd; exacte mapnaam te verifiëren), `mail\sent` (enkel recent jaar is voldoende) en `mail\templates`, `offerte`, `share`, de PDA- en kassamappen. **Niet** overzetten: `prog`, `spool`, `updates`, `work`, `restore`, logmappen (worden opnieuw aangemaakt).
- JMS-installatie als administrator uitvoeren en het **doelpad aanpassen** naar de nieuwe map; daarna de bestaande `jms.ini` terugzetten (staan er twee, neem de grootste; de kleine bevat enkel het server-adres) en nakijken op overbodige werkposten; de klantspecifieke lay-outbestanden terugzetten; de laatste programma-update in `prog` kopiëren.
- Foutmelding bij het starten van de JMS rond **database page size / "instance name already used"** (Windows 10/11): JMS stoppen, de **`.jfm`-bestanden** verwijderen uit `fas` en uit `fas\log`, en de drie database-bestanden uit **`prog\tools\win7`** naar `prog` kopiëren; daarna JMS twee keer starten/stoppen ter controle.
- Oude map hernoemen (bv. `... old`) zodat niemand nog in de oude data werkt; share opnieuw delen en de netwerkkoppeling op de werkposten herleggen.
- Testen met de twee controles hierboven.

Bij een tweede klant gaf dezelfde aanpak op dezelfde dag **geen** oplossing (JMS bleef crashen met de nieuwe versie; de oude versie werd teruggezet zodat de klant kon verder werken, maar die praat nog met het oude endpoint). De oorzaak was op het moment van de opname **niet gekend**. Behandel dit dus als een bekend, niet volledig opgelost probleem en escaleer naar een senior/ontwikkeling; verzin geen oorzaak.

### 5.4 Artikels van een leverancier moeten telkens opnieuw gekoppeld worden

De leverancier geeft geen artikelnummers mee in het Peppol-bestand (XML), of maar één samenvattende lijn. Jamadata kan dan niet blijvend koppelen. Enkel de leverancier kan dit oplossen; de klant moet dat bij zijn leverancier aankaarten. (Uit opleiding, 03-07-2025.)

### 5.5 Pdf-icoon bij inkomende factuur doet niets

Het pdf-icoon wordt altijd getoond. Zit er geen pdf in het Peppol-bestand van de leverancier, dan gebeurt er niets bij klikken. (Uit opleiding, 03-07-2025.)

## 6. Niet van toepassing op Jamadata

Het document `Codabox Peppol.pdf` (OneNote-export "Peppol aanmaken") beschrijft de onboarding van Peppol via CodaBox voor het pakket **DAVE** (interne firma/vestiging in DAVE, onboarding-tool, CodaBox-ID bij de vestiging). Het bevat geen Jamadata-procedure en is hier niet uitgewerkt.

## Bronnen

- `Jamadata Peppol FAQ.docx` (Jamadrink)
- `2240A - Jamadata Peppol Handleiding en automatisch mailen V4.3.docx` (Jamadrink/Handleidingen modules)
- `Elektronische facturen via CodaBox.docx` (Jamadrink/Handleidingen modules)
- `Codabox Peppol.pdf` (Jamadrink) – enkel vermeld als niet van toepassing
- Transcripties opleidingen: `Peppol_20250703_090232.txt`; `JJD New installation = Peppol Fout onoplosbaar-20260624_135151-Opname van vergadering.txt`; `COR New installation omwille van Peppol problemen.-20260624_155118-Opname van vergadering.txt`
- 00_START_CLAUDE / `09_SMTP_OVERDRACHT_20261110_c84a219d/ITERATIE_1_INSTRUCTIES.txt` (CASE-001: 8-H-C en 8-H-1-1)
