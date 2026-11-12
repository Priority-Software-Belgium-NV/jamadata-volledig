# Mail: automatisch mailen per klant (facturen, rappels, prijslijsten) en mailsjablonen

Gebruik dit document voor: vragen over welke documenten Jamadata automatisch naar een klant mailt en waar je dat per klant instelt, hoe rappels en prijslijsten gemaild worden, waar je de verzonden mails terugvindt, en hoe je de mailsjablonen (templates) personaliseert. De technische kant (SMTP/relay, testmail, mailprogramma, bekende problemen) staat in `mail-instellingen-en-smtp.md`.

## 1. Manueel mailen via het mail-icoontje

Bij verschillende documenten (bons, facturen, rappels ...) staat een **mail-icoontje**. Klik erop en er opent automatisch een nieuwe mail in het mailprogramma van de werkpost met het document in bijlage; je hoeft enkel nog te verzenden. Dit zit in de standaardversie.

## 2. Automatisch mailen instellen op de klantenfiche

Waar: klantenfiche (**9.2.1**) → klik op het **rode of groene + -teken achter het e-mailadres**. Dit opent de mailinstellingen van de klant, waar je aanduidt welke documenten automatisch gemaild worden.

Bij automatisch mailen krijg je de mail **niet** te zien; hij wordt achter de schermen verstuurd (via de SMTP-instellingen van de server).

In hetzelfde scherm staan ook de Peppol-optie ("Facturen electronisch versturen via Codabox" = P) en het GLN-nummer; zie `peppol-uitgaand.md`.

### Facturen

- Bij het opmaken van de factuur wordt automatisch **één exemplaar minder afgedrukt** en één factuur als bijlage gemaild.
- Je kan onderscheid maken tussen **voldane** en **niet-voldane** facturen.
- Automatisch mailen en Peppol kunnen tegelijk actief zijn voor dezelfde klant. Automatisch mailen uitzetten: per klant in dit scherm, of voor alle Peppol-klanten tegelijk via het hulpprogramma **+ → H → 5** (per firma; eerst back-up).

### Rappels

Is bij de klant ingesteld dat rappels automatisch gemaild worden, dan zal **"F8 druk af"** of **"F4 druk af/mail"** in het rappelprogramma de rappel voor die klant(en) **niet afdrukken maar automatisch mailen**.

### Prijslijsten

Via het menu printen van lijsten (**V.5.4**): rechts onderaan het scherm staat een gekleurd mail-icoon. In een volgend scherm kan je nog een speciale vermelding voor je klanten meegeven.

## 3. Verzonden mails terugvinden

- **Klantenfiche → + achter e-mailadres → mail-icoon rechtsonder**: overzicht van alle automatisch verzonden mails voor deze klant. Per regel kan je de mail opnieuw bekijken via het e-mail-icoon. Voor elektronische (Peppol-)facturen staat daar de knop om de verzendstatus op te vragen.
- **Herdrukken facturen 8.H.1.1**: klant ingeven en rechtsonder op het icoon klikken geeft dezelfde lijst.
- **Boekhouding B.4** (raadplegen rekening): klant ingeven en linksonder op het icoon klikken geeft dezelfde lijst.
- Op de server worden de verzonden mails bewaard in de map **`mail\sent`** onder de Jamadata-map.

## 4. Mailsjablonen (templates) personaliseren

De mails die Jamadata verstuurt hebben een standaardopmaak die de klant zelf kan aanpassen.

Waar staan ze: op de **Jamadata-server**, op het station waar Jamadata staat (meestal **J:**, kan een andere letter zijn): map **`Jamadata\mail\templates`**. Er is één sjabloon per documenttype. Pas de sjablonen bij voorkeur aan **op de server zelf**.

Vereisten:

- De sjablonen zijn **.EML**-bestanden. Je hebt een mailprogramma nodig dat in EML kan opslaan, of je moet achteraf converteren.
- De **bestandsnaam moet exact dezelfde blijven en in HOOFDLETTERS** staan. Anders worden de veldnamen (samenvoegvelden) niet ingevuld door het pakket.

### Werkwijze met MS Outlook

Outlook bewaart als **.MSG**; die moet je nadien omzetten naar **.EML**, bv. met het gratis hulpprogramma **"MSG to EML"** (jitbit, `https://www.jitbit.com/msg2eml/`).

1. Download het programma "MSG to EML".
2. Ga op de server naar `Jamadata\mail\templates`. **Maak eerst een kopie van de map `templates`.**
3. Klik met de rechtermuisknop op het gewenste sjabloon en open het met Outlook (desktop) ("Outlook (desktop) blijven gebruiken").
4. Pas het sjabloon aan. Is het niet aanpasbaar (bv. bij Office 365), kies dan eerst **"Beantwoorden"** en verwijder alle tekst die door het antwoord is toegevoegd, zodat enkel de oorspronkelijke mail overblijft.
5. Afbeelding (logo) toevoegen: via **Invoegen → Afbeeldingen**. Zo staat de afbeelding zichtbaar in de mail en niet als bijlage.
6. **Opslaan als**: onder **dezelfde naam, in HOOFDLETTERS**, in een nieuwe werkmap (bv. `MSG2EML`).
7. Open "MSG to EML", kies met **Browse** de werkmap en klik **"Convert *.msg to *.eml"**.
8. Verwijder in `templates` de originele sjablonen die je vervangt en zet de geconverteerde .EML-bestanden in de plaats.
9. Open het nieuwe sjabloon ter controle met Outlook en test daarna in het pakket.

### Aandachtspunten bij sjablonen

- Komt de pdf-bijlage bij ontvangers aan als **`winmail.dat`**, of tonen iPhone/iPad/Mac de inhoud van een oudere mail: zet het sjabloon om naar **tekst zonder opmaak** (geen HTML). Zie `mail-instellingen-en-smtp.md`.
- Worden velden niet ingevuld: controleer de bestandsnaam (HOOFDLETTERS, ongewijzigd) en dat het bestand echt .EML is.
- Bij een herinstallatie of verhuis van de server moet de map `mail\templates` van de klant mee overgezet worden; anders vallen de mails terug op de standaardsjablonen.

Er bestaat een oudere handleiding `OUD2800A - Mailsjablonen aanpassen.docx`; die is vervangen door 2800A en is hier niet gebruikt.

## Bronnen

- `0X19A - Mailen van prijslijsten, rappels, facturen.docx` (Jamadrink/Handleidingen modules)
- `2800A - E-Mail templates personaliseren.docx` (Jamadrink/Handleidingen modules)
- `Elektronische facturen via CodaBox.docx` (Jamadrink/Handleidingen modules) – lijst verzonden facturen/mails
- `Jamadata Peppol FAQ.docx` (Jamadrink) – automatisch mailen naast Peppol
- `HOWTO-MAIL instellingen.docx` (Jamadrink) – sjabloon zonder opmaak
- Transcripties `[klant] New installation = Peppol Fout onoplosbaar-20260624_135151-...txt` en `[klant] New installation omwille van Peppol problemen.-20260624_155118-...txt` (mappen `mail\sent` en `mail\templates`)
