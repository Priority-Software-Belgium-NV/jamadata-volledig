# Jamadrink: fiches van leveranciers, klanten, artikelen, groepen en klantentoeren

Gebruik dit document voor: vragen over het aanmaken, aanpassen, blokkeren, schrappen, afdrukken en exporteren van basisgegevens in Jamadrink (menu V.9): leveranciers, klanten, artikelen, artikelgroepen en klantentoeren; de extra opties op een fiche (F10 memo, F12 info, documenten, GDPR-export); massawijzigingen via lijst, Excel of het verborgen databaseveld-programma; en het verplicht maken van de TAB-toets voor wijzigingen. Prijsafspraken, prijzen en stock worden in andere documenten behandeld.

## 1. Overzicht en aanbevolen volgorde

Menu: `V.9` Beheer basisgegevens. Bij een eerste ingave is de aanbevolen volgorde: **Leveranciers → Groepen → Artikelen → Klanten** (een artikel heeft verplicht een leverancier en een groep nodig).

Standaardmenu per soort fiche (leveranciers `V.9.1`, klanten `V.9.2`, klantentoeren `V.9.7`):

| Code | Menu-item |
|---|---|
| 1 | Aanpassen/bekijken van een bestaande fiche |
| 2 | Bijvoegen van een nieuwe fiche |
| 3 | Schrappen van een bestaande fiche |
| 4 | Afdrukken lijst van de fiches |
| 6 | Afdrukken etiketten |
| 7 | Uitschrijven gegevens naar Excel |
| L | Aanpassen/schrappen van een reeks fiches |

Menu artikelen `V.9.3`:

| Code | Menu-item |
|---|---|
| 1 | Aanpassen/bekijken van een bestaande fiche |
| 2 | Bijvoegen van een nieuwe fiche |
| 3 | Schrappen van een bestaande fiche |
| 7 | Bijvoegen nieuwe fiche met informatie van een bestaande fiche |
| 8 | Aanpassen van een reeks van fiches |
| E | Exporteren artikels naar Excel |
| L | Raadplegen/aanpassen van een lijst artikels |

## 2. Een fiche openen en aanpassen (alle soorten)

1. Kies punt 1 van het betreffende menu; je krijgt het zoekscherm (code of naam, `F8 zoek op`, of lijst via het icoon).
2. De fiche opent in leesmodus. Druk **`TAB`** om in editeer-modus te gaan: velden worden aanpasbaar en er verschijnen extra knoppen.
3. `F8` schrijft weg.

### TAB verplicht maken (blokkeren inputschermen klant/leverancier/artikel)

- Doel: verhinderen dat fiches per ongeluk gewijzigd worden; de gebruiker moet eerst `TAB` nemen vooraleer iets aangepast kan worden op artikel-, leveranciers- en klantenfiche.
- Instelling: systeemparameter (integer) **2698** moet op **1** staan (standaard 0).
  - Handmatig: op het hoofdmenu `+` `T` `1`, parameter 2698 opzoeken en op 1 zetten.
  - Via commando (support): `Upsys32 sys.* i 2698 1`.

## 3. Leveranciers (V.9.1)

### Nieuwe leverancier (V.9.1.2)

- Geen btw-nummer: laat het veld op `BE-0000.000.000`.
- Btw-nummer nog niet gekend: vul `BE-0999.999.999` in (later corrigeren).
- Rekeningnummer nog niet gekend: laat `000-0000000-00` staan.

Functietoetsen op de fiche:

| Toets | Functie |
|---|---|
| `F9 Standaard GRB` | Standaard aankooprekeningen (grootboek) voor de leverancier |
| `F10 memo` | Memo van 3 lijnen |
| `F12 info` | Extra info (zie §8) |

Extra opties (grote `+`-knop) op een bestaande fiche: Bestelbonnen (zoeken tussen datums), Boekhoudrekening, Openstaande facturen, Historieken, GDPR-export fiche (Excel; de map met het bestand opent automatisch), Documenten (module, zie §9).

## 4. Klanten (V.9.2)

### Nieuwe klant (V.9.2.2)

- Btw-nummer: zelfde conventie als bij leveranciers (`BE-0000.000.000` = geen; `BE-0999.999.999` = nog onbekend).
- Velden die de facturatie sturen:

| Veld | Effect |
|---|---|
| Betalingstermijn | Bepaalt de vervaldatum op de factuur; die wordt afgedrukt en in de boekhouding bewaard voor rappels. **Leeg = contant te betalen op factuurdatum** |
| Korting % | Algemeen kortingspercentage voor de klant. Wordt niet toegekend op groepen waar "toegestane korting" op Nee staat |
| Omzet | Door het systeem opgeteld bedrag (excl. btw) van elke factuur |
| Tijdstip facturatie | Lettercode (dagelijks / wekelijks / maandelijks / halfjaarlijks) die bij facturatie per serie (`V.8.2.S`) gebruikt wordt als "Facturatietijdstip" |
| Facturatieadres / facturatieklant | Ander facturatieadres, bv. voor filialen waarvan de facturen naar het moederbedrijf gaan |
| `F10 Memo` | Memo van enkele lijnen; **wordt getoond bij het maken van een bon/factuur** voor deze klant |
| `F9 bestelbon` | Standaardbestelling van de klant: deze artikels komen automatisch op een nieuwe leveringsbon |

- Markering (knop naast Naam): markeert de klant in het rood; zichtbaar bij het aanmaken van een bon of factuur (bv. slechte betaler).
- Knop naast Btw-nummer: klant wel/niet btw-plichtig (niet btw-plichtig = rood).

Extra opties (`+`-knop) op een bestaande klantenfiche: Leveringsbons, Verhuringen, Offertes, Prijsafspraken, Boekhoudrekening, Openstaande facturen, Historieken, GDPR-export fiche, Documenten (module).

## 5. Artikelgroepen (V.9.4)

| Code | Menu-item |
|---|---|
| 1 | Aanpassen/bekijken gegevens voor één bepaalde groep |
| 4 | Afdrukken van een lijst volgens groepsnummer (pdf) |

- Groepen sturen lijsten en kortingen.
- **Groep 99 is uitsluitend voor leeggoed**; de korting van groep 99 moet op **Nee** staan.
- Nieuwe groep: in `V.9.4.1` een nog niet bestaand groepsnummer intikken. Per groep kan je standaard verkoopprijzen instellen.
- Bestaande groep opent meteen in editeer-modus.
- Groep schrappen: groep openen via `V.9.4.1`, de **groepsnaam leegmaken** en `F8 schrijf weg`.

## 6. Artikelen (V.9.3)

### Nieuw artikel (V.9.3.2)

Verplicht voor je naar het tweede deel van de fiche kan: **Codenummer, Omschrijving, Leverancier, Artikelgroep**.

Aanbevolen codenummer (als de klant nog geen eigen systeem heeft): 5 cijfers = groepsnummer + volgnummer; voor leeggoed groepsnummer + prijs. `F4 code` genereert het volgnummer.

| Voorbeeld | Code |
|---|---|
| 1e artikel in groep 1 | 01001 |
| 25e artikel in groep 17 | 17025 |
| Leeggoed (groep 99) van 4,50 EUR | 99450 |

Tweede scherm:

- Btw staat standaard op 21%.
- **Aantal leeggoed** staat op 1: laat dit op 1 staan zodat het leeggoed juist berekend wordt.
- **Inhoud (liters)** invullen maakt literrapporten (aankoop/verkoop) mogelijk.
- **EAN-nummer bak** zelf samenstellen: vrij beginnummer (bv. 27) + eigen code (bv. het artikelnummer) + nullen tot het voorlaatste teken; `F10 controle EAN` vult het controlecijfer in.
- **Max. verhuuraantal**: maximaal aantal stuks dat verhuurd kan worden (module verhuur, zie `jamadrink-offertes-verhuur-rappels.md`).

### Nieuw artikel uit bestaand artikel (V.9.3.7)

Zoek het bronartikel; je krijgt een nieuwe fiche waarin alles is overgenomen behalve o.a. het codenummer.

### Functietoetsen op de artikelfiche

| Toets | Functie |
|---|---|
| `F2 aankoopfiche` | Aankoopfiches bekijken, bewerken, toevoegen |
| `F9 vervolg` / `F9 terug` | Volgend / vorig deel van de fiche |
| `F10 prijs via winst%` | Verkoopprijs ingeven als winstpercentage (rechts) of als prijs (links); de andere waarde wordt berekend |
| `F5 stocklocaties` | Stocklocaties tonen (aanpassen met TAB) |
| `F7 herdisplay` | Fiche verversen na wijzigingen door andere acties |
| `F12 info` | Extra info |

Extra opties: Prijsafspraken (lijst voor dit artikel), Historieken.

### Reeks artikels één voor één aanpassen (V.9.3.8)

Kies volgorde (codenummer/alfabetisch), startartikel, leverancier en/of groep, verfijn in het selectiescherm. Elke fiche die voldoet opent achtereenvolgens; na opslaan komt de volgende, tot de laatste.

### Lijst artikels raadplegen/aanpassen/schrappen (V.9.3.L)

1. **Volgorde en kolommen**: toon volgens `A` alfabetisch, `K` kodenummer of `P` plaats magazijn. Kies in "Gegevens kolom 1" en "kolom 2" het nummer van de twee velden die je direct wil zien/aanpassen (genummerde lijst onderaan; via de kolommenknop rechtsonder kan je uit alle databasekolommen kiezen, bevestigen met `F8 neem aan`). De laatste keuze wordt onthouden.
2. `F8` = aanpasmode, `F10 schrap` = schrapmode.
3. **Selecteer artikels** (uitgebreide selectie, zie navigatiedocument).
4. **Lijst**:
   - Aanpasmode: de twee gekozen kolommen zijn direct aanpasbaar; een wijziging is opgeslagen zodra je het veld verlaat / een functietoets neemt.
   - Schrapmode: de kolommen tonen datum laatste prijswijziging en of er omzet/statistieken bestaan. Staat dat op NEE, dan gaat er geen historiek verloren.
   - Selectieveld (klik of `HOME`): tik bv. `b` + ENTER om naar artikels beginnend met b te springen.

| Toets | Functie in de lijst |
|---|---|
| `F1` | Wijzigingen wegschrijven en terug; in schrapmode volgt de vraag of de aangeduide artikels echt geschrapt moeten worden (`F4 Ja` / `F5 Neen`) |
| `F2` / `F3` | Wegschrijven en scherm omhoog / omlaag |
| `F6` | Originele waarden herstellen (enkel als nog geen andere functietoets gebruikt werd) |
| `F8` | Wegschrijven en de artikelfiche van de huidige lijn tonen |
| `F9` | Artikel aan-/afvinken om te schrappen (lijn kleurt blauw) |
| `F10 SCHRAP reeks artikels` | Naar schrapmode; eerst de vraag of je enkel geblokkeerde artikels wil selecteren |

## 7. Schrappen, blokkeren, lijsten, etiketten, Excel

### Schrappen versus blokkeren

- **Schrappen kan enkel ongedaan gemaakt worden door een back-up terug te zetten.** Historiek van de fiche gaat verloren.
- Alternatief: de **Lock-knop** op de fiche. Een geblokkeerde fiche kan nergens meer gekozen worden maar de historiek blijft. Unlock maakt ze opnieuw bruikbaar.
- Individueel schrappen (`V.9.1.3`, `V.9.2.3`, `V.9.3.3`, `V.9.7.3`): fiche zoeken, daarna `F1 stop`, `F4 schrap`, `F5 behoud`, `F11 hoofdmenu`.
- Reeks schrappen klanten/leveranciers (`V.9.1.L`, `V.9.2.L`): kies sortering (nummer/naam) en of geblokkeerde fiches getoond worden, `F8 selecteer` → filterscherm. De lijst toont Naam en de kolommen **Boekh** en **Stat**: staan beide op "Nee", dan verlies je geen historiek. `F8 pas aan` opent de fiche, `F9 markeer om te schrappen` markeert. `F1 Stop` vraagt bevestiging (`F4 Ja` / `F5 Neen`).
- Foutcodes die hierbij kunnen opduiken: 25 (rekening waarop geboekt is kan niet geschrapt worden), 65 (hier kan men geen fiches schrappen), 66 (fiche met actuele gegevens kan niet geschrapt worden); zie `jamadrink-foutcodes.md`.

### Lijst afdrukken (V.9.1.4 / V.9.2.4)

Parameters: volgorde `N` nummer of `A` alfabetisch; memo afdrukken J/N; enkel fiches met memo J/N; geblokkeerde overslaan J/N. `F8 selecteer fiches en druk af` drukt af; de pdf-knop rechtsonder maakt een pdf. Voor de lijst komt een bijkomend selectiescherm voor extra informatie (zie §8).

### Etiketten (V.9.1.6 / V.9.2.6)

Filterscherm; `F8 selecteer` drukt af op de ingestelde printer (lege filters = `F9 volledig`); pdf-knop rechtsonder voor pdf.

### Exporteren naar Excel (V.9.1.7, V.9.2.7, V.9.3.E)

Vink de velden aan, bevestig met `F8`, kies daarna de fiches in het filterscherm. Het resultaat is een Excel met de aangevinkte kolommen.

Let op: in de gebruikershandleiding staat de export bij leveranciers afwisselend als V.9.1.6 en V.9.1.7 genummerd; volgens het menu-overzicht is **6 = etiketten** en **7 = Excel**.

## 8. Extra informatie (F12 info) en herinneringen

Waarvoor: een centraal dossier van een 200-tal tekstlijnen per klant, leverancier of artikel (afspraken, bezoekinfo, contactnummers, aankoopgegevens). Kan als agenda dienen en kan een **alarm** tonen bij het maken van een bon/factuur.

Waar: fiche oproepen via `V.9`, dan `F12`. Staat er al info, dan toont de knop F12 een icoon.

Kolommen: **Datum**, **alarmvinkje**, **Type** (vrije lettercode, bv. A = afspraken, B = bezoek, T = telefoon, G = gsm), **Omschrijving**.

| Toets | Functie |
|---|---|
| `F1` / `F6` | Stop zonder wegschrijven |
| `F2` / `F3` | Scherm omhoog / omlaag |
| `F4` | Lege lijn toevoegen op de huidige lijn |
| `F5` | Huidige lijn wissen |
| `F8` | Wegschrijven en stop |
| `F9` | Schakelen tussen "alles aanpassen" (ook datum, alarm, type) en "enkel tekst aanpassen" |
| `F10` | Extra informatie van een andere fiche overnemen |

Herinnering instellen:

1. `F9` (alles) zodat datum-, alarm- en typeveld invulbaar zijn.
2. Vul de datum in vanaf wanneer de herinnering moet verschijnen.
3. Vink het alarm aan.
4. Vul de omschrijving in.

De lijn verschijnt wanneer een bon of factuur gemaakt wordt voor die fiche **en de datum overschreden is**. Is de datum leeg, dan vult het systeem bij wegschrijven de datum van vandaag in.

Afdrukken: bij het afdrukken van een klanten-/leverancierslijst komt een selectiescherm:

- Extra informatie afdrukken op lijst (J/N): info komt direct onder de klant/leverancier.
- Selectie: periode (info-lijnen binnen een periode), facturatieklant, type.
- Enkel fiches met informatie afdrukken (J/N).

Voorbeeld: bezoekplanning = alle klanten met type B tussen twee datums.

Veelvoorkomende vraag: "Bij elke factuur voor klant X verschijnt een melding." → Er staat een F12-lijn met alarm en een verstreken datum; open F12 op de fiche, `F9`, en vink het alarm af of wis de lijn. Een tweede mogelijke oorzaak is de `F10 memo` van de klant, die ook getoond wordt.

## 9. Documenten van klanten en leveranciers (module 2923A)

- Waarvoor: documenten zoals huurcontracten en overeenkomsten per klant/leverancier raadplegen vanaf elk werkstation.
- Opzet: op de server (of bij voorkeur op een OneDrive) bestaat één "Documentenmap" met daarin per klant/leverancier een eigen map. De te bewaren documenten plaats je in de map van de overeenkomstige klant/leverancier.
- Gebruik: fiche oproepen (`V.9.1` of `V.9.2`), grote `+`-knop rechtsboven, knop **Documenten**. Bestaat er nog geen map, dan vraagt het programma om er een aan te maken. Daarna toont het scherm alle documenten van die fiche.
- De bron vermeldt niet waar het pad van de Documentenmap wordt ingesteld (te verifiëren).

## 10. Fiches massaal aanpassen via Excel (0093A)

Waarvoor: veel klanten-, leveranciers- of artikelfiches in één keer wijzigen. Er is **geen controle** op de juistheid van wat in Excel staat; een back-up vooraf is absoluut noodzakelijk.

1. **Uitschrijven**: leveranciers `V.9.1.7`, klanten `V.9.2.7`, artikels `V.9.3.E`. Vink de te wijzigen velden aan en **altijd het eerste veld `recordnr`** (het interne nummer waarmee de fiche later teruggevonden wordt). Selecteer daarna de fiches.
2. **Aanpassen in Excel**:
   - Niet doen: de eerste lijn (veldnamen) verplaatsen of hernoemen; de kolom `recordnr` wijzigen.
   - Wel toegelaten: ongebruikte kolommen (behalve recordnr) verwijderen of verplaatsen; ongebruikte rijen (behalve de titellijn) verwijderen; sorteren, mits "de selectie uitbreiden" aangevinkt is zodat hele rijen samen blijven.
   - Zorg dat waarden voldoen aan het veld (geldig btw-nummer, maximale lengte...).
   - Opslaan in de map `\Jamadata\Share` op de hoofdcomputer; vanaf een andere werkpost via de share `\\JamaShare\`.
3. **Back-up**: op het hoofdmenu het groene icoon rechtsonder → punt 2 "Volledige backup nemen van het systeem".
4. **Inlezen**: hoofdmenu `+` `H` (bevestig back-up) → punt `3`. Geef het type fiche (`K`lant, `L`everancier, `A`rtikel), de naam van het Excel-bestand, `F8`; duid de velden aan die echt gewijzigd moeten worden, `F8`.
5. Controleer enkele fiches: de gewenste wijzigingen moeten erin staan en niets meer.

## 11. Eén databaseveld invullen of wissen voor veel fiches (support)

Enkel voor supportmedewerkers, via schermovername. **Altijd eerst een back-up.**

1. Zoek de veldcode: open in de map `Jamadata > Prog` het bestand **`Struct.map`**. De velden staan in dezelfde volgorde als op de fiche. Staat er achter een lijn een nul, dan wordt dat veld niet getoond op de fiche (bv. Land). Noteer de code van het veld, bv. `6, 52` voor de grootboekrekening op een artikel.
2. In Jamadata: Hoofdmenu voorraadbeheer → `+` → optie `T` (verborgen) → optie `2` "Invullen/wissen van een veld in de database".
3. Vul bovenaan de veldcode in, `F7 Herdisplay` en controleer dat het juiste veld getoond wordt, dan `F8`.
4. Nieuwe waarde: blanco laten om te wissen, een waarde invullen, of de inhoud van een ander veld overnemen.
5. In deel 2 van het scherm: uitvoeren op alle fiches (JA/NEE) of opgeven welke bestaande waarde vervangen moet worden door de nieuwe.
6. Soms volgt nog een selectiescherm (bv. bij artikels) om de records verder te beperken.

## 12. Klantentoeren (V.9.7)

- Nieuwe toer (`V.9.7.2`): vul eerst een **naam** in; zonder naam werkt het automatisch aanvullen op de lijnen niet. Voer de klanten in de gewenste volgorde in.
- `F4 invoegen lijn` (boven de cursor), `F5 wis lijn`, `F8 neem aan` (opslaan), `F10 druk toer` (afdrukken).
- `V.9.7.4` drukt meteen een lijst van alle toeren af; `V.9.7.6` drukt meteen etiketten af (geen tussenscherm).
- Leveringslijsten per klantentoer: `V.8.8`.

## 13. Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Velden op de fiche zijn niet aanpasbaar | Eerst `TAB` drukken (editeer-modus) |
| Klant wil dat fiches niet "per ongeluk" wijzigen | Parameter 2698 op 1 zetten (§2) |
| Fiche kan niet gekozen worden op bon/bestelling | Fiche is geblokkeerd (Lock); unlock op de fiche. Zie ook foutcode 63 |
| Fiche kan niet geschrapt worden | Er zijn boekingen/actuele gegevens (foutcodes 25, 66); gebruik blokkeren |
| Factuur staat "contant" terwijl klant betalingstermijn heeft | Veld Betalingstermijn op klantenfiche is leeg |
| Klant krijgt geen korting op bepaalde artikels | Groep staat op "toegestane korting = Nee", of het artikel is ingesteld op "geen korting" |
| Leeggoed wordt fout berekend | "Aantal leeggoed" op artikelfiche moet 1 zijn; leeggoedartikel in groep 99 |
| Ongeldig btw-nummer (foutcode 29) | Juist formaat of tijdelijk `BE-0999.999.999` |
| Na Excel-import staan verkeerde waarden in fiches | Back-up terugzetten; controleer of `recordnr` en titellijn onaangeroerd waren en rijen correct gesorteerd werden |

## Bronnen

- `gebruikershandleiding JAMADRINK 2.0.docx` (map Jamadrink): V.9.1–V.9.4, V.9.7, Extra notities
- `0x19B - Extra informatie - F12 info.docx` (map Jamadrink/Handleidingen modules)
- `0093A - Aanpassen fiches ahv excel-bestand.docx` (map Jamadrink/Handleidingen modules)
- `0229A - Aanpassen lijst artikels.docx` (map Jamadrink/Handleidingen modules)
- `2215A - Uitgebreide selectie artikels.docx` (map Jamadrink/Handleidingen modules)
- `2923A - Beheer documenten van klanten en leveranciers.docx` (map Jamadrink/Handleidingen modules; identiek aan `Beheren raadplegen documenten klanten leveranciers.pdf` in map Jamadrink)
- `0264A - Beheer verhuur-uitlenen van materialen.docx` (enkel veld Max. verhuuraantal)
- `Handleiding invullen veld database.docx` (map Jamadrink)
- `HOWTO-Blokkeren inputscherm klt_lev_art.docx` (map Jamadrink)
