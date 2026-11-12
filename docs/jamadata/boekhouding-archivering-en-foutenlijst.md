# Boekhouding in Jamadata: archivering (afsluiten), jaararchief, spanningsuitval en foutenlijst

Gebruik dit document voor: vragen over het archiveren/afsluiten van een boekhoudperiode (punt A), wat er daarbij geschrapt wordt, het jaararchief, wat te doen na een stroomonderbreking of crash tijdens het boeken, het herstelprogramma FASREP, en de betekenis en oplossing van de genummerde foutmeldingen (1 t/m 82) die onderaan de schermen van het boekhoudpakket verschijnen.

## 1. Punt A - Archivering van verouderde verrichtingen

### 1.1 Waarvoor dient het

Alle boekingen komen in één groot bewegingenbestand terecht (theoretisch max. 65.000 boekingen). De archivering sluit een periode af en ruimt dat bestand op, zodat er opnieuw plaats is. Het is het "gevaarlijkste" punt van het hoofdmenu:

- Wat gearchiveerd is, kan niet meer gewijzigd of aangevuld worden. Boeken of factureren met een datum in een gearchiveerde periode is onmogelijk (fout 37).
- Betaalde facturen en hun betalingen worden uit de lopende boekhouding geschrapt; er blijft enkel een saldo over. **Openstaande facturen worden nooit geschrapt.**
- Stukken uit een gearchiveerde periode kunnen niet meer geschrapt worden via punt U.

### 1.2 Voor u archiveert (checklist)

1. Druk de fouten- en controlelijst af (B.5.1) en los de fouten op.
2. Druk alle periodedocumenten af over de te archiveren periode: journalen, centralisatiejournalen, rekeningen (leveranciers, klanten, grootboek), balansen, BTW-aangifte. Vooral de klanten- en leveranciersrekeningen volledig afdrukken: betaalde facturen verdwijnen na archivering.
3. Laat de boekhouder of uzelf verifieren dat er geen fouten meer in zitten.
4. **Neem net voor de archivering een back-up** van de volledige boekhouding. Blijkt er achteraf een zware fout, dan kan de back-up teruggezet worden.
5. Bij de **eerste archivering van een nieuw boekjaar**: druk eerst de jaarlijkse BTW-listing af (de computer geeft hiervoor een waarschuwing). Is dat niet gebeurd, kopieer dan eerst de bestanden `sal.fas` en `klt.fas` naar een aparte drager, zodat de listing naderhand nog gemaakt kan worden. (`fas` is hier de dossiercode; in een dossier met een andere code heet de extensie anders.)

### 1.3 A.1 Archivering van de boekhouding - velden

Het keuzescherm toont vooraf: de datum van de vorige archivering en het aantal vrije/gebruikte lijnen in de huidige boekhouding en in het jaararchief. De start is beveiligd met een J/N-vraag.

| Veld | Uitleg |
|---|---|
| Boekhouding is reeds gearchiveerd tot | Informatief: datum van de laatste archivering. |
| BTW-periode die u wenst te archiveren: van ... t.e.m. ... | De **begindatum** moet de eerste dag na de vorige archivering zijn (en de eerste dag van een maand). Bij de allereerste archivering: de eerste dag van de maand/het kwartaal waarin met de boekhouding gestart is. De **einddatum** is bij maandverwerking (`M` in `+.3`) de laatste dag van dezelfde maand (let op 29 februari), bij kwartaalverwerking (`K`) de laatste dag van het kwartaal. |
| Enkel correct afgeboekte facturen schrappen (J/N) | `J` (standaard): enkel facturen waarvoor betalingen met de juiste referentie geboekt zijn die samen precies het factuurbedrag vormen, worden geschrapt. `N`: op rekeningen waarvan het **eindsaldo 0** is, worden alle facturen/betalingen van de periode geschrapt zonder rekening te houden met referenties. Zo worden rekeningen aangezuiverd waarop foutieve referenties geboekt zijn of waarop een voorschot zonder factuurreferentie staat, op voorwaarde dat de rekening geen openstaand saldo heeft. |

Foutmeldingen bij verkeerde datums: 27, 32, 33, 35, 36, 62 (zie foutenlijst).

### 1.4 Na de archivering: herschikken (FASREP)

Als laatste stap wordt het bestand terug op orde gezet. Bij de volgende start van het programma vraagt **FASREP** of het bestand herschikt mag worden (sorteren en klasseren van de fiches; kan even duren). Wordt dit geweigerd, dan komt de vraag bij elke start terug tot het herschikken gebeurd is.

### 1.5 Onderbreking tijdens het archiveren

Valt de spanning uit of loopt er iets mis tijdens het archiveren, dan komt de computer bij het heropstarten **niet** in het hoofdmenu maar gaat hij onmiddellijk verder met archiveren vanaf de stap waar hij onderbroken werd. Laat dit uitlopen.

### 1.6 Fouten ontdekt na een archivering

Een fout in een gearchiveerde periode wordt rechtgezet met een correctieboeking via het diversenjournaal in een volgende (niet-gearchiveerde) periode. Alternatief, als er nog een back-up is van net voor de archivering: back-up terugzetten, fout corrigeren, opnieuw archiveren.

### 1.7 A.2 Wissen verouderde bewegingen in jaararchief

- Het **jaararchief** (optie) bewaart de bewegingen per rekening ook na de archivering, zodat rekeningen over oude periodes nog geraadpleegd en afgedrukt kunnen worden (in het rekeningoverzicht via `F10`; staat `F10` op dat scherm, dan is de optie geinstalleerd).
- Het jaararchief is niet oneindig groot: best jaarlijks opkuisen via A.2.
- Vul per soort (Leveranciers, Klanten, Grootboek) de datum in tot wanneer gewist mag worden. Waar niet gewist mag worden: geen datum invullen. Zet de vraag "echt wegvagen" op `J` (standaard `N`) en start met `F8`.
- Grootboekrekeningen met "Centralisatie = J" worden bij archivering zonder detail in het jaararchief opgenomen; dat detail is nadien niet meer terug te halen.

## 2. Wat te doen bij spanningsuitval of crash tijdens het boeken

1. Start de computer en het pakket opnieuw. Het programma FASREP zet de bestanden op orde.
2. Was u een factuur of uittreksel aan het ingeven (nog niet geboekt), dan is wat op het scherm stond **niet** geboekt: opnieuw ingeven.
3. Was de computer net bezig met wegboeken, dan kunnen sommige boekingen al weggeschreven zijn en andere niet. Controleer dit door een deel van het journaal af te drukken (B.5.1).
4. Is een factuur of uittreksel onvolledig geboekt: het hele stuk schrappen (punt U) en opnieuw ingeven.
5. Controleer bij de parameters van het journaal waarop geboekt werd (`+.3`, scherm met de journalen) het **laatst gebruikte nummer** en het **saldo**; deze zijn na een onderbreking vaak verkeerd. Pas ze aan.

## 3. Foutenlijst met verklaring

De foutnummers verschijnen samen met een korte boodschap op de laatste lijn van het scherm.

| Nr | Melding | Oorzaak / oplossing |
|---|---|---|
| 1 | Bestand is niet te vinden op deze schijven | Juiste schijven/USB in gebruik? Externe schijf ingeschakeld? Controleer in `+.2` de bestandsnamen en schijfletters. |
| 2 | Grootboekrekening bestaat (nog) niet | Rekening aanmaken via 9.3.2 of juiste nummer ingeven. |
| 3 | Grootboekrekening mag enkel bij financieel journaal (type 3 of 4) | In de journaaldefinitie (`+.3`) mag enkel bij een financieel journaal een corresponderende grootboekrekening staan. |
| 4 | Er is geen journaaltype voor deze bewerking | Er is in `+.3` geen aankoopjournaal (bij inboeken aankoopfactuur) of geen verkoopjournaal (bij verkoopfactuur) gedefinieerd. |
| 5 | Programma(onderdeel) werd niet gevonden | Programmabestand ontbreekt; contacteer Jamadata. |
| 6 | Ongeldige datum | Verkeerd ingetikt of onbestaande datum (32/01, 29/02 in niet-schrikkeljaar). Altijd 6 cijfers, met de nullen. |
| 7 | Foutief journaalnummer | Nummer 0, onbestaand journaal, of journaal dat op deze plaats niet toegestaan is. |
| 8 | Checkdigit klopt niet | Het controlecijfer in het ingegeven nummer is fout. |
| 9 | Bestand is vol | Terug naar hoofdmenu en opnieuw proberen. Nog vol: computer herstarten en het herstelprogramma FASREP laten lopen voor het pakket gestart wordt. Nog steeds vol: contacteer Jamadata. |
| 10 | Debet is niet gelijk aan credit | De som van de debetboekingen verschilt van de som van de creditboekingen; de boeking wordt geweigerd. Controleer totaal, BTW en uitsplitsing. |
| 11 | Voorziene lijnen voor document zijn vol | Er kunnen geen lijnen meer bij. Uittreksel opsplitsen in meerdere uittreksels met hetzelfde nummer en dezelfde boekdatum. |
| 12 | De gekozen optie werd niet geinstalleerd | Het onderdeel is een apart aan te kopen module die niet op dit systeem staat. |
| 13 | Het afprinten werd afgebroken | Na een printerfout heeft de gebruiker gekozen om te stoppen. |
| 14 | Geen bewegingen voor de gevraagde rekening | Er staan geen boekingen op deze klant, leverancier of grootboekrekening. |
| 15 | Factuur is niet van de opgegeven klant of leverancier | Klopt het factuurnummer? Juiste klant/leverancier? Geen vergissing tussen type `L` en `K`? |
| 16 | Er ontbreekt een noodzakelijke grootboekrekening bij de parameters | Voor aankoopfacturen moeten "Aftrekbare BTW" en "Niet-aftrekbare BTW" ingevuld zijn in `+.3`; voor verkoopfacturen "BTW verkopen". |
| 17 | Printer error | Printer aan? Online? Inkt/toner? Deksel dicht? Correct aangesloten? De computer vraagt Abort (`A`) of Retry (`R`), zonder ENTER. |
| 18 | Printer is bezet door een andere gebruiker | Wachten tot de andere gebruiker klaar is. |
| 19 | (niet gebruikt) | |
| 20 | Nog geen periode gearchiveerd | Voor deze bewerking moet minstens één periode gearchiveerd zijn (in de oude handleiding: bv. BTW-listing). |
| 21 | TAB is hier niet toegestaan. Neem een functietoets | Om veiligheidsredenen is hier een specifieke functietoets vereist. |
| 22 | Totalisatieniveau moet 0 zijn | Voor een rekening waarop geboekt mag worden, moet het totalisatieniveau 0 zijn. |
| 23 | Niveau totaalrekening moet 1 t/m 8 zijn | Vuistregel: aantal cijfers van het rekeningnummer van de subtotaalrekening. |
| 24 | Grootboekrekening bestaat, maar er mag niet op geboekt worden | Rekening heeft "boeken toegestaan = N" (totaalrekening). Zo'n rekening kan ook niet op een rekeningoverzicht bekeken worden. |
| 25 | Rekening waarop geboekt is, kan niet geschrapt worden | Er staat een boeking op de fiche of het saldo is niet 0. Het saldo valt weg na de laatste archivering van het lopende boekjaar. |
| 26 | Ongeldig bankrekeningnummer | Controlecijfers kloppen niet. Nakijken; desnoods tijdelijk `000-0000000-00` en het juiste nummer opvragen. |
| 27 | Periode mag geen jaarovergang overkoepelen | Begin- en einddatum vallen in een verschillend kalenderjaar of in een verschillend boekjaar. |
| 28 | Parameter grootboekrekening is niet te vinden | Een rekening uit `+.3` bestaat niet in het rekeningplan; de ontbrekende rekeningen worden op het scherm getoond. Nummer corrigeren in `+.3` of rekening aanmaken via 9.3. Bij overschrijvingen aan leveranciers zijn verplicht: "centralisatierekening leveranciers" en "bekomen disconto". |
| 29 | Ongeldig BTW-nummer | Controlecijfers kloppen niet. Nakijken of navragen bij de houder. |
| 30 | Omschrijving of naam is ongeldig | Moet met een letter beginnen en mag niet blanco zijn. |
| 31 | Fiche bestaat reeds | Naam, codenummer of een ander sorteerveld bestaat al. |
| 32 | Einddatum is niet de laatste dag van de maand | Kies de laatste dag van de maand. |
| 33 | Einddatum stemt niet overeen met de begindatum | Maandverwerking: einddatum = laatste dag van de maand van de begindatum. Kwartaalverwerking: laatste dag van het kwartaal dat met de begindatum begint. |
| 34 | Ongeldige keuzemogelijkheid | Niets ingetikt bij een verplichte vraag, of een antwoord buiten de toegelaten keuzes. |
| 35 | Begindatum sluit niet aan bij de vorige archiveringsperiode | Begindatum moet de 1e dag van de maand zijn en de dag na de vorige archiveringsdatum (staat onderaan het scherm). Geldt bij archiveren en bij afdrukken van rekeningen en balansen; voor journalen en centralisatiejournalen is de begindatum vrij. |
| 36 | Einddatum is kleiner dan de begindatum | Bij lijsten mag begin = eind, maar eind mag niet voor begin vallen. Bij archiveren: einddatum = laatste dag van de maand. |
| 37 | Datum valt in een reeds gearchiveerde periode | Boeken/factureren voor de archiveringsdatum kan niet (verkeerde, oude datum ingetikt?). Bij lijsten: datum moet na de laatste archivering vallen. Bij schrappen: er zit een beweging in een gearchiveerde periode. |
| 38 | Er ontbreekt hier een noodzakelijk gegeven | Verplicht veld invullen. |
| 39 | De gewenste fiche bestaat (nog) niet | |
| 40 | Het nummer van de grootboekrekening is niet ingevuld | |
| 41 | Een factuur is geen creditnota en omgekeerd | Men probeert via een factuurscherm een creditnota aan te passen of omgekeerd. |
| 42 | Rekeningnummer bestaat niet | De rekening bestaat niet, of het is een rekening waarop niet geboekt mag worden. |
| 43 | Bestand wordt niet door database beheerd | Bestand kan beschadigd zijn; eventueel terugzetten vanaf een back-up. |
| 44 | Bestandsstructuur is van een foutieve versie | De bestanden passen niet (meer) bij de versie van het databaseprogramma. |
| 45 | Opzoeksleutel in bestand is niet gegenereerd | Indexprobleem; bestanden laten herschikken / contacteer Jamadata. |
| 46 | Geschrapt gegevensrecord | |
| 47 | Ongeldig gegevensrecord | |
| 48 | Gegevensbestand is vol | De voorziene ruimte is opgebruikt (zie punt 6 hoofdmenu); bestand laten vergroten. |
| 49 | Opzoeksleutelbestand is vol | Bestanden op orde laten zetten. |
| 50 | Foutief paswoord. Gebruik van programma geweigerd | Paswoord van het juiste niveau of hoger ingeven. |
| 51 | Foutief paswoord. Geef paswoord van niveau 3 | Voor dit onderdeel is het hoogste paswoord nodig. |
| 52 | De ingebrachte gegevens stemmen niet overeen | Sommige waarden zijn ongeldig in combinatie met andere ingegeven gegevens. |
| 53 | De ingegeven naam voor het bestand is ongeldig | Vorm `d:ffffffff.exe`: optionele schijfletter met dubbelpunt, naam van 1-8 letters/cijfers (eerste teken een letter), extensie 1-3 tekens. |
| 54 | Poging tot lezen in sequentieel bestand voorbij einde van bestand | |
| 55 | Datum valt voor de vorige datum | Bij vervaldaglijsten moeten de datums in de tabel in stijgende volgorde staan. |
| 56 | Waarschuwing bij verandering van filename | |
| 57 | Opgegeven valuta bestaat (nog) niet | Valuta toevoegen via punt 7. |
| 58 | Controle op BTW-bedrag klopt niet | Het BTW-bedrag berekend uit de rekeningen (volgens hun BTW-vak) stemt niet overeen met het ingevulde BTW-bedrag. Zie controle-instelling en toegestane afwijking in `+.3`. |
| 59 | Er is reeds een factuur of creditnota geboekt onder dit nummer | Fout factuurnummer ingebracht; of de teller van het laatst gebruikte factuurnummer staat fout; of eerst de vroeger geboekte factuur met dat nummer schrappen. |
| 60 | Rekeningnummer waarop geboekt is, mag niet veranderd worden | Omschrijving en andere gegevens mogen wel gewijzigd worden; maak desnoods een nieuwe rekening met het gewenste nummer. |
| 61 | Boekdatum valt meer dan 500 dagen na laatste archiveringsdatum | Verkeerd jaartal ingetikt, of er is al zeer lang niet meer gearchiveerd: archiveren. |
| 62 | Datum valt na de einddatum van de archivering | Bij archivering moet de ingegeven datum blanco zijn of kleiner dan/gelijk aan de einddatum van de archivering. |
| 63 | De gevraagde gegevens zijn geblokkeerd | Fiche is in gebruik door een andere gebruiker/sessie. |
| 64 | Onvoldoende vrije plaats in bestand om verder te mogen gaan | Zie punt 6 hoofdmenu; archiveren of bestand laten vergroten. |
| 65 | Hier kan men geen fiches schrappen. Neem een ander hoofdmenu | Ga naar hoofdmenu B of V, punt 9, en schrap daar. |
| 66 | Fiche met actuele gegevens kan niet geschrapt worden | |
| 67 | Geventileerd bedrag is groter dan het te ventileren bedrag | Analytisch: het over kostenplaatsen verdeelde bedrag is groter dan het geboekte bedrag, of de som van de percentages is groter dan 100 %. |
| 68 | Grootboekrekening is geen analytische rekening | Bij ventilatie moet de kostenplaatsrekening analytisch zijn (begint met een 9). |
| 69 | Analytische bewegingen zijn enkel bij grootboekrekeningen toegestaan | Geen analytische ventilatie op klanten of leveranciers. |
| 70 | Analytisch bedrag moet volledig uitgesplitst worden | Som van de geventileerde bedragen moet gelijk zijn aan het te verdelen bedrag. |
| 71 | Ongeldige munteenheid | |
| 72 | U mag slechts een beperkte keuze van de velden intikken | |
| 73 | Ingegeven totaal stemt niet overeen met de som van de details | |
| 74 | Getal mag niet ingevuld worden | |
| 75 | Hoeveelheid stemt niet overeen met het bedrag | |
| 76 | Onmogelijke datum in de context van andere ingevulde gegevens | Bv. datum ouder dan een begindatum, of een datum in de toekomst waar dat niet mag. |
| 77 | Ongeldige samenhang van de ingebrachte gegevens | |
| 78 | (niet gedocumenteerd) | |
| 79 | Er is een andere gebruiker bezig met dit programma | Wachten tot de andere gebruiker het onderdeel verlaten heeft. |
| 80 | Hier moet het bedrag positief ingegeven worden | Bij creditnota's (1.2 en 1.5) worden bedragen positief ingegeven. Wie creditnota's als negatieve facturen wil ingeven, moet de factuurschermen (1.1 / 1.4) gebruiken. |
| 81 | Statistiek kan niet bijgewerkt worden: jaartal is niet geopend | Het jaar van de boekdatum stemt niet overeen met het huidige of vorige jaar op de statistiekfiches. |
| 82 | Grootboekrekening voor leeggoed ontbreekt bij de parameters | Leeggoedrekening invullen bij de parameters. |

Opmerking: in de bron staat bij fout 80 letterlijk "1.1 en 1.3" voor negatieve facturen; uitgaande facturen zijn punt 1.4. Bij fout 63 en 5 geeft de bron geen verklaring; de oplossing hierboven is de voor de hand liggende interpretatie (te verifieren).

## 4. Veelgestelde vragen

- **"Ik kan niet boeken op een datum van vorig kwartaal."** De periode is gearchiveerd (fout 37). Boek de correctie in de lopende periode via het diversenjournaal.
- **"De begindatum wordt geweigerd bij het afdrukken van balansen."** Voor rekeningen en balansen moet de begindatum de dag na de laatste archiveringsdatum zijn (fout 35). Die datum staat onderaan het scherm.
- **"Na archiveren staan er nog altijd oude facturen open op een klant die alles betaald heeft."** De betalingen hebben een foute of geen referentie. Corrigeer de referenties in het rekeningoverzicht (punt 4), of archiveer met "Enkel correct afgeboekte facturen schrappen = N" (werkt enkel als het saldo van de rekening 0 is), of gebruik het hulpprogramma `+.D` (optie).
- **"Kan een archivering ongedaan gemaakt worden?"** Neen, enkel door de back-up van voor de archivering terug te zetten.
- **"Bij het opstarten vraagt het programma of het bestand herschikt mag worden."** Dit is FASREP na een archivering; toestaan.

## Bronnen

- `Gebruikerhandleiding BOEKHOUDPAKKET.docx` (map boekhouding) - versie V06, 12-8-2014: "Punt A. Archivering van verouderde verrichtingen", "Foutenlijst en verklaring", "Wat te doen bij spanningsuitval", "Enkele raadgevingen".
