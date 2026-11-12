# Mail: instellingen, SMTP (automatisch mailen) en mailproblemen

Gebruik dit document voor: vragen over hoe Jamadata mails verstuurt (via het mailprogramma van de werkpost of automatisch via SMTP door de JMS), waar de e-mail- en SMTP/relay-instellingen staan, welke providerinstellingen gangbaar zijn (Proximus, Telenet, Office 365, Gmail), hoe je een testmail stuurt en controleert, het standaard mailprogramma in Windows (EML/MSG), en bekende mailproblemen (winmail.dat, verkeerde mail op iPhone, nieuwe Outlook). Wat er per klant automatisch gemaild wordt en de mailsjablonen staan in `mail-automatisch-mailen-en-sjablonen.md`.

## 1. Twee manieren van mailen

| | Manueel (mail-icoontje) | Automatisch mailen |
|---|---|---|
| Hoe | Klik op het mail-icoon bij een bon, factuur, rappel ...; er opent een nieuwe mail in **het mailprogramma van de werkpost** met de juiste bijlage; de gebruiker verstuurt zelf. | De mail wordt **achter de schermen door de Jamadata-server (JMS)** verstuurd via **SMTP/relay**; de gebruiker ziet de mail niet. |
| Afhankelijk van | Standaard mailprogramma in Windows + bestandsformaat EML/MSG (punt 2 en 3) | E-mail-/relay-instellingen in de JMS (punt 4 en 5) |
| Instellen | per werkpost | op de server (kan vanop eender welke werkpost) |

## 2. Standaard mailprogramma op de werkpost (Windows)

Jamadata maakt de mail aan als een bestand **.eml** of **.msg**. Windows moet weten welk programma die bestanden opent.

1. **Start → Instellingen → Apps → Standaard-apps**.
2. Zoek het bestandstype **.msg** en kies het gewenste mailprogramma (Outlook, Windows Live Mail, ...).
3. Doe hetzelfde voor **.eml**.

**Nieuwe Outlook**: de nieuwe versie van Outlook kon (stand 04/2024) niet gebruikt worden met Jamadata. Het schuifje **"De nieuwe versie van Outlook uitproberen / Try the new Outlook"** (rechtsboven in Outlook) mag **niet** aanstaan. Huidige stand te verifiëren.

## 3. Mailformaat per werkpost: EML of MSG

Waar: **Hoofdmenu → + → J** (JMS-instellingen: printers, papier, werkstations, e-mail ...) → **4** (instellingen werkposten).

Optie **"Gebruik EML als Emailstandaard"** (staat bij de meeste klanten uit):

- **Aangevinkt**: Jamadata maakt berichten in **EML**-formaat.
- **Uitgevinkt**: Jamadata maakt berichten in **MSG**-formaat; dit opent Outlook om de mail te sturen.

Oudere mailprogramma's (enkel nog relevant op oude werkposten):

- **Outlook Express**: heeft een registerinstelling nodig om een .eml als "te verzenden" mail te openen (`FEATURE_HONOR_XUNSENT_IN_FILE` voor `msimn.exe` onder `HKLM\SOFTWARE\Microsoft\Internet Explorer\Main\FeatureControl`) en alle Windows-updates.
- **Outlook 2003/2007**: kan standaard geen .eml openen; er bestaan registeraanpassingen voor. **Outlook 2010 en later** verwerkt .eml zonder probleem.
- Geen mailprogramma (Vista/Win7): Windows Live Mail werkte met .eml.

Symptoom "mail-icoon opent niets of het verkeerde programma": controleer punt 2 (standaard-app voor .eml/.msg) en of het formaat in punt 3 past bij het mailprogramma van de werkpost. Volgens de HOWTO: is het e-mailformaat in het pakket niet juist, dan moet het **EML** zijn.

## 4. SMTP/relay-instellingen voor automatisch mailen

Waar (bevestigde route): **Hoofdmenu voorraad → + → J** (JMS-instellingen) → **5** (E-mail-instellingen).

1. Profiel: standaard geen profiel ingeven (= basisprofiel) en **F8**.
2. Je ziet het afzenderadres. Kies **relay-instellingen**.
3. Bij **relay-server 1** staan: **SMTP-server**, **poort**, **e-mailadres/gebruiker (userID)**, **paswoord**, **beveiliging**.
4. **Beveiliging**: werk je met gebruikersnaam en wachtwoord, dan staat dit altijd op **auto**; zonder aanmelding (relay van de internetprovider) op **none**.
5. Bewaren met **F8**.

Belangrijk:

- De instellingen gelden voor de **server**; je kan ze vanop eender welke werkpost (ook op afstand) aanpassen.
- De instellingen worden bewaard in **`jms.ini`** (in de opname klinkt dit als "IMS.ini"; in andere opnames staat het bestand in de `prog`-map van de server). Dit bestand bevat het mailwachtwoord in leesbare tekst: nooit in tickets, mails of documentatie kopiëren. Een kopie zit ook in de online back-up van de klant (map `config`), wat handig is om oude instellingen terug te vinden.
- Server, poort, account, authenticatie en beveiliging zijn **klantafhankelijk**. Gebruik enkel de waarden die de klant of zijn IT-beheerder voor deze installatie heeft doorgegeven (meestal in het ticket). Leg vóór een wijziging de bestaande waarden veilig vast om te kunnen terugdraaien.
- Wijzigen van authenticatie/TLS/account is geen juniorhandeling zonder goedgekeurde waarden en toestemming; enkel bekijken mag altijd.

### Gangbare providerinstellingen (uit HOWTO-MAIL instellingen)

| Provider | Server | Poort | Aanmelding | Beveiliging |
|---|---|---|---|---|
| Proximus – relay via internetabonnement (zonder beveiliging) | `relay.skynet.be` | 25 | geen userID/paswoord | none |
| Telenet – relay via internetabonnement (zonder beveiliging) | `uit.telenet.be` | 25 | geen userID/paswoord | none |
| Skynet/Proximus met account | `relay.proximus.be` | 587 | e-mailadres + paswoord | auto |
| Office 365 | waarden enkel als schermafdruk in de bron (niet uitleesbaar) | | e-mailadres + paswoord | auto |
| Gmail | waarden enkel als schermafdruk in de bron | | | |
| Outlook/Hotmail | waarden enkel als schermafdruk in de bron | | | |

De relay-instellingen zonder aanmelding werken enkel als de server via het internetabonnement van die provider naar buiten gaat. De HOWTO is niet gedateerd; providers wijzigen deze gegevens, dus bij twijfel verifiëren bij de provider/IT van de klant.

**Office 365 – aandachtspunten:**

- Installeer de **laatste versie van de JMS**.
- In Microsoft 365 moet voor het gebruikte account **"Geverifieerde SMTP" (Authenticated SMTP)** ingeschakeld zijn. Dit moet de **beheerder van het mailadres/de tenant** doen; Jamadata-support kan dit niet.
- Het **primaire domein** moet op het mailadres zelf staan en zeker niet op `...onmicrosoft.com`; anders kan het versturen geweigerd worden (failed).

**Gmail – aandachtspunt:** er moet een instelling gewijzigd worden in de **accountinstellingen** van Google (niet in de mailinstellingen). Welke instelling staat enkel als schermafdruk in de bron; te verifiëren.

## 5. Testmail sturen en controleren (uit opleiding "SMTP automatisch mailen", bevestigd artikel 14-10-2026)

1. **Hoofdmenu → + → J → 5 → F8**.
2. Onderaan: **"Stuur testmail"**. Vul een testontvanger in (bv. je eigen adres, of een met de klant afgesproken adres) en **F8**.
3. Controleer onmiddellijk de **logging van de JMS-service** van die klant (in de opname "de SVC" genoemd, logging van de laatste dag): als de mail niet vertrekt, staat daar een foutboodschap. Exacte naam/locatie van deze log is niet onafhankelijk gedocumenteerd.
4. Controleer of de testmail werkelijk aankomt. Dat kan een minuut duren; kijk ook in **spam/ongewenste mail**.
5. Gelukt: bevestig aan de klant/IT'er (bv. door de ontvangen testmail door te sturen) en beantwoord het ticket. Mislukt: meestal een verkeerd doorgegeven wachtwoord of serverinstelling; vraag de gegevens opnieuw na of zet de vorige waarden terug.

"Bewaren" (F8 in de relay-instellingen) en "Stuur testmail" zijn twee aparte handelingen: bewaren verstuurt niet vanzelf een testmail. Een geslaagde testmail garandeert geen blijvende bezorging.

## 6. Bekende mailproblemen

| Symptoom | Oorzaak / oplossing |
|---|---|
| De pdf-bijlage komt bij de ontvanger aan als **`winmail.dat`** | Het mailsjabloon (template) bevat opmaak. Zet het sjabloon om naar **tekst zonder opmaak** (zeker geen HTML). Testen met Thunderbird. |
| Automatische mail komt aan met de juiste referentie, maar bij openen op **iPhone/iPad/Mac** verschijnt de inhoud en pdf van een **oudere mail** (via webmail op pc is de mail wel correct) | Probleem aan de kant van iOS-mail. Oplossing: mailsjabloon omzetten naar **tekst zonder opmaak**. |
| Office 365 weigert de automatische mails (failed) | Geverifieerde SMTP niet ingeschakeld op het account, primair domein staat op onmicrosoft.com, of verouderde JMS. Zie punt 4. |
| Testmail vertrekt niet | Foutboodschap in de JMS-logging lezen; server/poort/gebruiker/wachtwoord/beveiliging nakijken met de door de klant geleverde waarden. |
| Mail-icoon opent geen (of een leeg/verkeerd) mailvenster | Standaard-app voor .eml/.msg (punt 2), formaat EML/MSG (punt 3), "nieuwe Outlook" staat aan. |
| Velden in de mail (naam, nummer ...) worden niet ingevuld | Bestandsnaam van het sjabloon staat niet in HOOFDLETTERS; zie `mail-automatisch-mailen-en-sjablonen.md`. |

## 7. Mappen op de server (uit opleiding, 24-06-2026)

Onder de Jamadata-map staat de map **`mail`** met o.a.:

- **`sent`**: kopie van alle automatisch verzonden mails (kan duizenden bestanden bevatten; bij een verhuis volstaat het recentste jaar, liefst een jaar extra zodat geen factuurmail ontbreekt);
- **`templates`**: de mailsjablonen van de klant (altijd mee overzetten);
- `outbox`, `failed` en andere werkmappen (worden door de JMS-installatie automatisch aangemaakt; normaal leeg).

## Bronnen

- `HOWTO-MAIL instellingen.docx` (Jamadrink)
- `Handleidingen JAMADATA Standaard Email programma.docx` (Jamadrink/Handleidingen modules)
- Transcriptie `SMTP AUTO MATISCH MAILEN JAMADATA.txt` (Transcripties opleidingen)
- `KA_JAMADATA_SMTP_AUTOMATISCH_MAILEN_B3_20261014.md` (Claude/JAMADATA_KENNISBANK_CLAUDE_20261029) – goedgekeurd artikel op basis van bovenstaande opname
- 00_START_CLAUDE: `08_SMTP_INTAKE_20261110_b93e51c4/00_CHECKPOINT_SMTP_INTAKE.md`, `09_SMTP_OVERDRACHT_20261110_c84a219d/ITERATIE_1_INSTRUCTIES.txt` (SMTP-anker: route + → J → 5 → F8, bewaren en testmail zijn aparte handelingen)
- Transcripties `[klant] New installation = Peppol Fout onoplosbaar-20260624_135151-...txt` en `[klant] New installation omwille van Peppol problemen.-20260624_155118-...txt` (mappenstructuur `mail`, `jms.ini`)
