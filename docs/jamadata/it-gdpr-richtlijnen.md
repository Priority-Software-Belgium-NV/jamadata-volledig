# GDPR-richtlijnen in Jamadata (persoonsgegevens van klanten en klantenkaarten)

Gebruik dit document voor: vragen van klanten over GDPR/AVG in Jamadata: welke persoonsgegevens het pakket bewaart en waar, en hoe je een betrokkene inzage geeft, gegevens aanpast, schrapt, blokkeert of exporteert (klantenfiche en klantenkaartfiche), met de exacte menupunten.

Bron is de Jamadata-handleiding 0005B (versie 1.0, mei 2018). Het is een praktische handleiding, geen juridisch advies.

## 1. Kader

- GDPR/AVG is van toepassing sinds 25 mei 2018 op elke organisatie die persoonsgegevens gebruikt, opslaat of verwerkt (ook vzw's en feitelijke verenigingen, commercieel of niet).
- Niet van toepassing bij uitsluitend persoonlijk/huiselijk gebruik, of wanneer gegevens enkel van een papieren drager afgelezen worden die nadien niet bijgehouden wordt.
- Elk verzoek van een betrokkene moet **binnen 30 dagen** verwerkt worden. Bij een verzoek tot inzage moet je ook de bewaartermijn meedelen; onnauwkeurige gegevens moet je op vraag verbeteren.

## 2. Waar staan de gegevens van Jamadata?

- In het Jamadata-pakket zelf.
- Op de hoofdcomputer in de map `\jamadata\fas\`.
- Op de automatische back-up (meestal een USB-stick in de hoofdcomputer).
- Op zelfgemaakte back-ups en/of de online back-up.
- Op afdrukken.

## 3. Welke persoonsgegevens?

- **Klantenfiche:** o.a. klantnummer, naam, adres, postcode, gemeente, telefoon, fax, gsm, btw-nummer, buitenlands btw-nummer, e-mail, CC-e-mail, boekhoud-e-mailadres en opmerkingen.
- **Klantenkaartfiche:** o.a. klantenkaartnummer, naam, adres, postcode, gemeente, telefoon, e-mail, geboortedatum, geslacht, klant sinds, en aankoopgegevens (datum, bedrag, punten).

Deze gegevens kunnen ook op de **kassa** bekeken en aangepast worden. Het is daarom aan te raden de kassa met een wachtwoord te beveiligen.

## 4. Rechten van de betrokkene en hun vertaling in Jamadata

| Recht | In Jamadata |
|---|---|
| Recht om geïnformeerd te worden | Buiten het pakket: informeer klanten dat en waarom je welke gegevens bijhoudt. |
| Recht op toegang (inzage) | PDF van de fiche bezorgen (§5). |
| Recht op rechtzetting | Fiche aanpassen (§6). |
| Recht op verzet (bv. geen direct marketing) | Klant **blokkeren**: klik op het rode slotje achter het codenummer; de fiche wordt geblokkeerd en het scherm wordt zwart. Bij klantenkaarten: het e-mailveld leegmaken zodat de klant niet in volgende mailings opgenomen wordt. |
| Recht om vergeten te worden | Fiche schrappen (§7). |
| Recht op beperking van verwerking | Tegemoetkomen aan de wens van de klant om bepaalde gegevens niet bij te houden (bv. wel klantenkaart, geen promotiemails). |
| Recht op verzet tegen profiling | Rekening mee houden bij gebruik van de gegevens. |
| Recht op dataportabiliteit | Export van de fiche naar CSV (§8). |

## 5. Inzage geven: PDF van een fiche

Algemeen: op elk scherm kan je met de **rechtermuisknop** kiezen voor **"Schermafdruk naar PDF-document"**. Dit kan voor meerdere schermen na elkaar; daarna kies je (rechtermuisknop) **"PDF-document aanmaken en openen"**. Het geopende document kan je afdrukken of doormailen.

- **Klantenfiche:** punt **V.9.2.1** (of **B.9.2.1**), klant oproepen, rechtermuisklik in het venster > "Schermafdruk naar PDF-document", daarna opnieuw rechtermuisklik > "PDF-document aanmaken en openen".
- **Klantenkaartfiche:** punt **V.2.9.1**, klantenkaart oproepen, zelfde twee stappen.

## 6. Gegevens aanpassen

- **Klantenfiche:** punt **V.9.2.1** (of **B.9.2.1**), klant oproepen. Staat de fiche in "view"-mode (niets wijzigbaar), druk eerst op **TAB**. Pas aan en bewaar met de bewaarknop of **F8**.
- **Klantenkaartfiche:** punt **V.2.9.1**, klantenkaart oproepen, aanpassen en bewaren met de bewaarknop of **F8**.

## 7. Gegevens schrappen

- **Klantenfiche:** punt **V.9.2.3** (of **B.9.2.3**), klant oproepen en schrappen met de schrapknop of **F4**. Heeft de klant nog statistieken, dan volgt de vraag om ook die te schrappen: bevestigen. Daarna verschijnt een scherm dat alle aanverwante fiches schrapt: **F8** om door te gaan.
- **Klantenkaartfiche:** punt **V.2.9.S**, klantenkaart oproepen en schrappen met de schrapknop of **F4**.

Let op (afgeleid uit §2, niet letterlijk in de bron): de handleiding beschrijft enkel het schrappen in het pakket zelf; de gegevens staan volgens §2 ook op back-ups en afdrukken. Blokkeren (§4) is het alternatief wanneer de historiek moet blijven.

## 8. Gegevens exporteren (dataportabiliteit)

- **Klantenfiche:** punt **V.9.2.1** (of **B.9.2.1**), klant oproepen. Klik rechts onderaan op het **groene ronde icoon met wit kruis** voor extra opties en kies **"GDPR export fiche"**.
- **Klantenkaartfiche:** punt **V.2.9.1**, klantenkaartfiche oproepen, zelfde icoon > **"GDPR export fiche"**.

Er wordt automatisch een **CSV-bestand** bewaard in `C:\Users\<gebruikersnaam>\Mijn Documenten\Jamadata\Diversen\`; die map wordt automatisch geopend op de taakbalk.

Inhoud van de export:
- Klantenfiche: klantnr., naam, adres, postcode, gemeente, telefoon, fax, gsm, btw-nummer, buitenlands btw-nummer, e-mail, CC-e-mail, boekhoud-e-mailadres en eventuele opmerkingen.
- Klantenkaartfiche: klantenkaartnr., naam, adres, postcode, gemeente, telefoon, e-mail, geboortedatum, geslacht, klant sinds, en de laatste 10 aankopen met telkens datum, bedrag en punten.

Dit bestand kan je de klant bezorgen zodat hij de info aan derden kan doorgeven.

## 9. Veelgestelde vragen

| Vraag | Antwoord |
|---|---|
| De knop "GDPR export fiche" staat er niet | Klik eerst op het groene ronde icoon met wit kruis rechts onderaan de fiche; de knop zit bij de extra opties. |
| Waar staat het exportbestand? | `Mijn Documenten\Jamadata\Diversen` van de Windows-gebruiker op de werkpost. |
| Kan ik een klant "verbergen" zonder te schrappen? | Ja, blokkeren via het rode slotje: de fiche verdwijnt van lijsten en kan niet meer gebruikt worden op bons/facturen, de historiek blijft. |
## Bronnen
- Jamadrink/Handleidingen modules: "0005B - Jamadata_GDPR_Richtlijnen_v.1.0.docx"
- Jamadrink: "Jamadata-Server_overzicht_enkele_mogelijkheden 2.0.docx" (blokkeren/markeren, schermafdruk naar PDF)
