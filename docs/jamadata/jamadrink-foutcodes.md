# Jamadrink: lijst foutcodes (error-codes 1–82)

Gebruik dit document voor: het opzoeken van de betekenis van een genummerde foutmelding (error-code) die Jamadrink of het boekhoudpakket toont, met waar mogelijk een eerste denkrichting voor support. De omschrijvingen zijn letterlijk uit de bron; de kolom "Eerste controle" is een afleiding uit die omschrijving en geen gedocumenteerde oplossing.

## Lijst

| Code | Melding (bron) | Eerste controle (afgeleid) |
|---|---|---|
| 1 | Bestand is niet te vinden op deze computer. | Pad/bestandsnaam, netwerkschijf, juiste werkpost |
| 2 | Grootboekrekening bestaat nog niet. | Rekening eerst aanmaken |
| 3 | Grootboekrekening mag enkel bij financieel journaal type 3 of 4. | Journaaltype nakijken |
| 4 | Er is geen journaaltype voor de gevraagde bewerking. | Journalen/parameters boekhouding |
| 5 | Programma niet gevonden. | Module/installatie |
| 6 | Ongeldige datum. | Datumingave |
| 7 | Foutief journaalnummer. | |
| 8 | Checkdigit klopt niet. | Controlecijfer rekening-/btw-/EAN-nummer |
| 9 | Het bestand is vol. Wis oude gegevens of bel Jamadata! | Oude gegevens wissen/archiveren; anders escaleren |
| 10 | DEBET is niet gelijk aan CREDIT. | Boeking in evenwicht brengen |
| 11 | Voorziene lijnen voor document zijn vol. | Document splitsen |
| 12 | De gekozen optie werd niet geïnstalleerd op dit systeem. | Module zit niet in het pakket van de klant |
| 13 | Het afprinten werd afgebroken. | |
| 14 | Geen bewegingen voor de gevraagde rekening. | Periode/rekening |
| 15 | Factuur is niet van de opgegeven klant of leverancier. | Klant/leverancier of factuurnummer |
| 16 | Er ontbreekt een noodzakelijke grootboekrekening bij parameters. | Parameters boekhouding aanvullen |
| 17 | Printer error. | Printer/driver |
| 18 | Printer bezet door andere gebruiker. | Wachten of andere werkpost nakijken |
| 19 | (leeg in bron) | |
| 20 | Om verder te gaan, moet er minstens 1 periode gearchiveerd zijn. | Archivering |
| 21 | TAB of BREAK toets is niet toegestaan. Neem een functietoets. | Functietoets onderaan scherm gebruiken |
| 22 | 'Totalisatieniveau' moet 0 zijn als boeken toegestaan 'J' is. | Instelling grootboekrekening |
| 23 | 'Niveau Totaalrekening' moet 1 tot 8 zijn voor totaalrekeningen. | Instelling grootboekrekening |
| 24 | Grootboekrekening bestaat, maar er mag niet op geboekt worden. | Totaalrekening; andere rekening kiezen |
| 25 | Rekening, waarop geboekt is, kan niet geschrapt worden. | |
| 26 | Ongeldig rekeningnummer (of BIC). | IBAN/BIC |
| 27 | Periode mag geen boekhoudjaar-overgang overkoepelen. | Periode opsplitsen |
| 28 | Parametergrootboekrekening is niet te vinden. | Parameters boekhouding |
| 29 | Ongeldig BTW nummer. | Zie fiches: `BE-0000.000.000` (geen btw-nr) / `BE-0999.999.999` (nog onbekend) |
| 30 | Omschrijving of naam is ongeldig. | |
| 31 | Fiche bestaat reeds. | Ander nummer/code |
| 32 | Einddatum is niet de laatste dag van de maand. | |
| 33 | Einddatum stemt niet overeen met begindatum. | |
| 34 | Ongeldige keuzemogelijkheid, of U heeft niets ingetikt. | |
| 35 | Begindatum sluit niet aan bij de vorige archiveringsdatum. | |
| 36 | Einddatum is kleiner dan begindatum. | |
| 37 | Datum valt in de reeds gearchiveerde periode. | Datum na laatste archivering nemen |
| 38 | Er ontbreekt hier een noodzakelijk gegeven. | Verplicht veld invullen |
| 39 | De gewenste fiche bestaat (nog) niet. | |
| 40 | Het nummer van de grootboekrekening is niet ingevuld. | |
| 41 | Een factuur is geen credietnota en omgekeerd! | Teken van het bedrag / documenttype |
| 42 | Rekeningnummer bestaat niet. | |
| 43 | Bestand wordt niet door database beheerd. | Escaleren |
| 44 | Bestandsstructuur is van foutieve versie. | Versie/update; escaleren |
| 45 | Opzoeksleutel in bestand is niet gegenereerd. | Escaleren (index) |
| 46 | Geschrapt gegevensrecord. | Fiche is geschrapt |
| 47 | Ongeldig gegevensrecordnummer. | |
| 48 | Gegevensbestand is vol. Schrap oude gegevens of bel Jamadata! | Oude gegevens wissen; anders escaleren |
| 49 | Opzoeksleutelbestand is vol. | Escaleren |
| 50 | Foutief paswoord. Gebruik van het programma wordt geweigerd. | |
| 51 | Foutief paswoord. Paswoord moet van hoogste niveau (3) zijn. | Gebruiker met niveau 3 nodig |
| 52 | De ingebrachte gegevens stemmen niet overeen. | |
| 53 | De ingegeven naam voor het bestand is ongeldig. | Bestandsnaam (bv. max. 8 tekens voor de punt, zie herafdrukken facturen) |
| 54 | Poging tot lezen in seq. bestand voorbij einde van bestand. | Escaleren |
| 55 | Datum valt vóór de vorige datum. | |
| 56 | *** Waarschuwing *** Wenst U werkelijk de namen te veranderen. | Bevestigingsvraag |
| 57 | Opgegeven valuta bestaat (nog) niet. | |
| 58 | Controle op BTW bedrag klopt niet! | Btw-bedrag versus basis nakijken |
| 59 | Er is reeds een factuur of creditnota geboekt onder dit nummer. | Volgend factuurnummer nemen |
| 60 | Rekeningnummer, waarop geboekt is, mag niet veranderd worden. | |
| 61 | Boekdatum valt te ver na laatste archiveringsdatum. | Eerst archiveren |
| 62 | Datum valt na de einddatum van de archivatie. | |
| 63 | De gevraagde gegevens zijn geblokkeerd. | Fiche is "gelocked" of in gebruik op een andere werkpost |
| 64 | Onvoldoende vrije plaats in bestand om verder te mogen gaan. | Oude gegevens wissen; escaleren |
| 65 | Hier kan men geen fiches schrappen. Neem een andere hoofdmenu. | Schrappen via het juiste menu (bv. V.9.x.3) |
| 66 | Fiche met actuele gegevens kan niet geschrapt worden. | Fiche heeft nog bewegingen; blokkeren i.p.v. schrappen |
| 67 | Geventileerd bedrag is groter dan het te ventileren bedrag. | |
| 68 | Grootboekrekening is geen analytische rekening. | |
| 69 | Analytische bewegingen zijn enkel bij grootboekrek. toegestaan. | |
| 70 | Analytisch bedrag moet volledig uitgesplitst worden. | |
| 71 | Ongeldige munteenheid. | |
| 72 | U mag slechts een beperkte keuze van de velden intikken. | |
| 73 | Ingegeven totaal stemt niet overeen met de som van de details. | |
| 74 | Getal mag niet ingevuld worden (geen spec). | |
| 75 | Hoeveelheid stemt niet overeen met het bedrag. | |
| 76 | Onmogelijke datum in de context van andere ingevulde gegevens. | |
| 77 | Ongeldige samenhang van de ingebrachte gegevens. | |
| 78 | U heeft ooit een illegale kopie gemaakt van Jamadata-software! | Licentie; escaleren |
| 79 | Er is een andere gebruiker bezig met dit programma. | Andere werkpost laten afsluiten; lijst actieve werkposten via hoofdmenu `+ J T` |
| 80 | Hier moet het bedrag positief ingegeven worden. | |
| 81 | Statistiek kan niet bijgewerkt worden: jaartal is niet geopend. | Nieuw jaar openen (periodewerkzaamheden) |
| 82 | Grootboekrekening voor leeggoed ontbreekt bij de parameters. | Parameter leeggoedrekening invullen |
| 83–100 | (leeg in bron) | |

## Opmerkingen

- Code 19 en 83–100 zijn in de bron niet ingevuld.
- De bron bevat enkel de omschrijvingen, geen oplossingen. Voor codes rond volle bestanden (9, 48, 49, 64), bestandsstructuur (43–45, 54) en licentie (78) is escaleren naar tweede lijn aangewezen.

## Bronnen

- `Lijst errorcodes.pdf` (map Jamadrink)
- `Navigeren binnnen Jamadata.pdf` (map Onenote): enkel voor de verwijzing `+ J T`
