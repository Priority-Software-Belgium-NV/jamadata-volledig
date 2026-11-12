# Boekhouding in Jamadata: module afschrijvingen en module beheer eigendommen (huren)

Gebruik dit document voor: vragen over de module afschrijvingen (afschrijvingsfiches per investering, lineair/degressief, afschrijvingstabel afdrukken en automatisch inboeken, afschrijvingsjournaal instellen) en over de module "Beheer eigendommen - huren" (eigendomsfiches, maandelijkse debetnota's voor huur, doorrekenen van kosten, indexatie van huren, boeking op wachtrekening en omzetrekening).

Beide zijn modules in optie binnen de boekhouding.

## Deel A - Module afschrijvingen

### A.1 Waarvoor

Beheer van de boekhoudkundige afschrijvingen van investeringen. Per investering wordt een **afschrijvingsfiche** aangemaakt met alle informatie over hoe ze afgeschreven wordt. Periodiek wordt een **afschrijvingstabel** gegenereerd met de afschrijvingsbedragen over de periode en de nieuwe boekwaarde. De afschrijvingen kunnen automatisch geboekt worden.

### A.2 Waar

Volgens de modulehandleiding: **onder punt B.5.6**. Opmerking: de gebruikershandleiding van 2014 kent geen punt 5.6 (optiemodules staan daar onder B.5.0.x) en de Intrastat-nota gebruikt "B.5.6" ook voor een ander menu. Het nummer kan dus per versie verschillen: zoek op het scherm naar "afschrijvingen" (onzeker / te verifieren).

Het modulemenu heeft twee punten:
1. Beheer afschrijvingsfiches
2. Afdrukken/inboeken afschrijvingstabel

### A.3 Instellen voor eerste gebruik: afschrijvingsjournaal

1. Maak een journaal aan: hoofdmenu > `+` (aanpassen systeemparameters) > punt 3 "boekhoudparameters" > `F8` tot het scherm met de journalen.
2. Vul op een vrije lijn een ongebruikt journaalnummer in (in het voorbeeld van de handleiding: journaal **30**), Type (Tp) **6** en een benaming. De rest hoeft niet ingevuld te worden.
   - Het journaal moet van het type **"diversen"** zijn.
   - Type **6** = nummering op omgekeerde datum (`mmdd`); type **5** = gewone volgnummering.
3. Open de module en klik op het **groene tandwieltje** rechts onderaan: geef het journaal in waarin de afschrijvingen geboekt moeten worden.

**Wordt geen journaalnummer ingevuld, dan worden de afschrijvingen niet geboekt**; enkel de afschrijvingsfiches worden dan bijgewerkt.

### A.4 Beheer afschrijvingsfiches (punt 1)

| Toets / icoon | Werking |
|---|---|
| F8 zoek op | Toont de lijst met de geselecteerde fiches; daarna een fiche bekijken/aanpassen |
| F9 nieuwe fiche | Nieuwe afschrijvingsfiche toevoegen |
| PDF-icoon (rechtsonder) | PDF met de lijst van de geselecteerde fiches |

Velden van de afschrijvingsfiche:

| Veld | Uitleg |
|---|---|
| Omschrijving | Beschrijving van de investering. |
| GRB investering | Grootboekrekening waarop de investering geboekt werd (klasse 2, bv. 240100). |
| GRB afschrijving | Grootboekrekening waarop de afschrijving geboekt wordt (de afschrijvingsrekening bij het actief). |
| GRB kost afschrijving | Kostenrekening waarop de afschrijvingen tegengeboekt worden. |
| Factuurnummer | Factuurnummer waarmee de investering geboekt werd (manueel in te geven, informatief). |
| Datum aankoop | Datum van de investering. |
| Afschrijven met/over | Percentage (indien `%`) of aantal jaren (indien `J`). |
| Methode afschrijven | **L**ineair of **D**egressief. |
| Begin eerste afschr. | Begindatum van de eerste afschrijving (bv. begin boekjaar). |
| Reeds afgeschreven / Datum laatste afschrijving | Wordt bijgehouden bij het inboeken van de afschrijvingstabel: het reeds afgeschreven bedrag en de tot-datum. |
| Afgesloten | Aanvinken als de fiche afgesloten is en niet meer op de lijsten mag komen. Staat het vinkje aan, dan verschijnt rechtsboven een icoon (rode vuilbak) waarmee de fiche ook echt geschrapt kan worden. Schrappen is niet verplicht. |
| Reden afsluiting / verkoopprijs | Informatief. |
| Berekenen tot | Datum invullen en `F7` herbereken: toont een simulatie in de velden pro rata, bedrag afschrijving en nieuwe boekwaarde. |
| PDF-icoon op de fiche | Simulatie van de volledige afschrijving van deze investering. |

**Methodes**
- **Lineair** (meest gebruikt): het af te schrijven bedrag wordt gelijk verdeeld over het aantal jaren. Voorbeeld: 1.000 EUR op 5 jaar = 20 % = 200 EUR per jaar.
- **Degressief**: het tarief wordt verdubbeld t.o.v. lineair en elk jaar toegepast op het nog af te schrijven saldo. Voorbeeld: 1.000 EUR op 5 jaar: tarief 40 %; jaar 1 = 400 EUR, jaar 2 = 240 EUR (40 % van 600). Wordt enkel voor bepaalde goederen en in een bepaalde context toegepast (te bepalen door de boekhouder).

**Opmerkingen**
- Alles in één keer afschrijven kan door **100 %** in te geven.
- De **aankoopfactuur** van een investering boekt u op een **2-rekening** (bv. 240100) en niet op een 6-rekening (bv. 610210). De kost komt via de afschrijving op de 6-rekening.

### A.5 Afdrukken/inboeken afschrijvingstabel (punt 2)

| Veld | Uitleg |
|---|---|
| Afschrijven tot | Einddatum (bv. einde boekjaar) tot wanneer de fiches afgeschreven worden. |
| Afschrijvingstabel inboeken | Aangevinkt: na het afdrukken van de tabel worden de afschrijvingsfiches bijgewerkt. Is in de parameters een afschrijvingsjournaal ingegeven, dan worden de afschrijvingen ook geboekt op de grootboekrekeningen van de fiches. |

Verloop: eerst verschijnt de afschrijvingstabel in PDF, daarna de vraag om de tabel in te boeken. Op de lijst staat per fiche het **bedrag** dat afgeschreven wordt; **Pro rata** is het aantal dagen waarover in dat jaar afgeschreven wordt.

Controleren wat geboekt is: druk het afschrijvingsjournaal af (in het voorbeeld journaal 30) via B.5.1.

Meestal wordt per jaar afgeschreven, maar per maand kan ook.

### A.6 Veelvoorkomende vragen

| Vraag / probleem | Antwoord |
|---|---|
| De tabel is afgedrukt maar er is niets geboekt | "Afschrijvingstabel inboeken" stond niet aan, of er is geen afschrijvingsjournaal ingevuld bij het tandwieltje (dan worden enkel de fiches bijgewerkt). |
| Welk journaaltype? | Diversen: type 5 (volgnummer) of 6 (dagnummering mmdd). |
| Fiche mag niet meer op de lijst | "Afgesloten" aanvinken (eventueel reden/verkoopprijs invullen); schrappen kan met het vuilbak-icoon maar hoeft niet. |
| Eerst zien wat de afschrijving wordt | Op de fiche "Berekenen tot" invullen + `F7`, of het PDF-icoon op de fiche voor de volledige simulatie. |
| Afschrijving is fout geboekt | Niet beschreven in de bron. Algemene regel van het pakket: een stuk op een journaal kan geschrapt worden via punt `U` zolang de periode niet gearchiveerd is; het veld "Reeds afgeschreven / datum laatste afschrijving" op de fiches wordt daardoor niet vanzelf teruggezet (te verifieren met een senior). |

## Deel B - Module beheer eigendommen / huren

### B.1 Waarvoor

Opvolgen en innen van de huren van eigendommen (panden). Per eigendom wordt een fiche aangemaakt. Maandelijks worden **debetnota's** aangemaakt/verstuurd met de te ontvangen huren. Die worden op **wachtrekeningen (4xxx)** geboekt; wanneer de huurder effectief betaalt, worden de bedragen overgeheveld naar **omzet (7xxx)**. De module kan ook vaste kosten doorrekenen, huren indexeren en de huurders opvolgen.

Standaard wordt **geen BTW** gerekend. BTW rekenen is mogelijk mits een aanpassing door een programmeur van Jamadata.

### B.2 Waar

Volgens de modulehandleiding: onder punt **B.5.0.1** ("Menu beheer eigendommen / huren"). Let op: in de gebruikershandleiding van 2014 en in de handleiding domicilieringen is B.5.0.1 het punt van de domicilieringslijsten; het optiemenu is dus niet in elke installatie gelijk genummerd (te verifieren op het scherm van de klant).

Modulemenu:
1. Beheer eigendomsfiches
2. Afdrukken/inboeken debetnota's te ontvangen huur
3. Afdrukken/inboeken debetnota's doorrekening kosten
4. Beheer indexatie huren (4.1 huren indexeren, 4.2 huurindexen ingeven)

### B.3 Instellen voor eerste gebruik: journaal huren

1. Maak een journaal voor de huren: hoofdmenu > `+` > `3` (boekhoudparameters) > `F8` (neem aan) tot het scherm met de journalen.
2. Kies een vrij nummer (in het voorbeeld journaal **80**), Type **2** (verkopen) en een benaming.
3. Open "Menu beheer eigendommen / huren" en klik op het icoon met de **groene tandwieltjes** rechts onderaan: geef het journaal in waarin de huren geboekt moeten worden.

### B.4 Beheer eigendomsfiches (punt 1)

| Toets / icoon | Werking |
|---|---|
| F8 zoek op | Lijst van de geselecteerde fiches; niets invullen = alle panden. Selectie mogelijk op beginletters of periode. |
| F9 nieuwe fiche | Nieuwe eigendomsfiche |
| PDF-icoon (rechtsonder) | PDF met de lijst van de geselecteerde fiches |
| F12 (op de fiche) | Afspraken e.d. bijhouden bij de fiche |

Velden die uitleg vragen:

| Veld | Uitleg |
|---|---|
| Huurder | Verwijzing naar een bestaande **klant** (klantenfiche). |
| Datum laatste huur | Datum van de laatste debetnota. |
| Huidig huurbedrag / huidige index | Moeten bij het aanmaken ingevuld worden; daarna worden ze automatisch berekend door het pakket (bij indexatie). |
| GRB te betalen bedrag | Meestal een **wachtrekening** waarop de debetnota's geboekt worden. Is ze ingevuld, dan worden de debetnota's standaard op deze wachtrekening geboekt. Er kan ook direct op een verkooprekening (7xxxxx) geboekt worden. |
| GRB betaalde bedragen | Rekening waarop de **betaalde** debetnota's geboekt worden (omzet). |
| Extra kosten | Worden extra op de debetnota afgedrukt. |
| Velden over de aankoop van het pand (onder de scheidingslijn) | Louter informatief. |
| Analytische rekening | Indien ingevuld wordt er ook analytisch geboekt. |

### B.5 Debetnota's te ontvangen huur (punt 2)

Stelt de debetnota's voor de te ontvangen huren op. Ze worden geboekt op de **klantenrekening** van de huurder en kunnen daar opgevolgd worden. Een debetnota is vergelijkbaar met een factuur, maar wordt meestal op een (wacht)rekening geboekt zodat ze geen invloed heeft op de BTW-aangifte.

1. Geef de juiste **maand** in; de computer overloopt alle panden die nog een debetnota nodig hebben.
2. **Zorg dat de index van die maand/jaar ingegeven is** (punt 4.2), anders kan niet correct geindexeerd worden.
3. Per pand: `F8` afdrukken/boeken, of `F6` annuleer om deze huurder over te slaan.
4. Na `F8` kiest u hoe de debetnota verzonden wordt. Er kan automatisch gemaild worden als dat op de klantenfiche aangeduid is.

### B.6 Debetnota's doorrekening kosten (punt 3)

Debetnota's voor kosten die de huurder moet betalen (bv. kadastraal inkomen, onderhoudskosten). Ook deze worden op de klantenrekening geboekt en daar opgevolgd.

### B.7 Indexatie huren (punt 4)

1. **Punt 4.2 - huurindexen ingeven**: geef maandelijks het nieuwe, wettelijk geldende indexcijfer in (gezondheidsindex, te raadplegen bij Statbel).
2. **Punt 4.1 - huren indexeren**: geef maand en jaar in; de computer toont de panden die geindexeerd moeten worden. Met `F4` of `F5` (ja/nee) kiest u per pand of de huur geindexeerd wordt.

### B.8 Opvolging en betalingen

- De huren en kosten van een huurder opvolgen: roep de huurder (klant) op via **punt 4** van de boekhouding (rekeningoverzicht).
- De **betalingen** ingeven via **punt 2** van de boekhouding (financiele verrichtingen), zoals elke klantbetaling. Terugkerende huurbetalingen kunnen in de CODA-module vast gekoppeld worden via het bankrekeningnummer van de huurder (zie `boekhouding-coda-en-betalingen.md`).

### B.9 Veelvoorkomende vragen

| Vraag / probleem | Antwoord |
|---|---|
| Pand komt niet in de maandelijkse run | Er is voor die maand al een debetnota gemaakt (zie "Datum laatste huur"), of de fiche is niet volledig (huurder, huurbedrag). (afgeleid) |
| Huur wordt niet geindexeerd | Index van de betreffende maand/jaar is niet ingegeven in punt 4.2, of bij 4.1 is voor dat pand "nee" gekozen. |
| Kan er BTW op de huur? | Standaard niet; enkel na aanpassing door een Jamadata-programmeur. |
| Waar wordt geboekt? | Debetnota: op de klant, met als tegenrekening "GRB te betalen bedrag" (wachtrekening 4xxx) of rechtstreeks een 7-rekening; bij betaling overheveling naar "GRB betaalde bedragen" (7xxx). Journaal = het verkoopjournaal (type 2) uit de tandwiel-parameters. |
| Debetnota mailen | Kan automatisch als mailen op de klantenfiche aangeduid is; anders afdrukken. |

## Bronnen

- `0070A - Module afschrijvingen.docx` (map Jamadrink/Handleidingen modules).
- `0071A - Beheer eigendommen - huren.docx` (map Jamadrink/Handleidingen modules).
