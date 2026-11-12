# Jamadrink: lay-outs, afdrukken, pdf en handleidingen

Gebruik dit document voor: vragen over de vereisten voor een factuurlay-out (achtergrond in PNG), afdrukken versus pdf versus mailen vanuit lijsten en documenten, het probleem dat een gemailde pdf enkel strepen toont, waar mail-/documentsjablonen en printerparameters te vinden zijn, en hoe de klantenhandleidingen (pdf achter de vraagtekenknop) beheerd worden. De bronnen over lay-outs zijn beperkt: dit document bevat alleen wat er effectief in staat.

## 1. Afdrukken, pdf en mail: algemene werking

Op vrijwel elk afdruk- of lijstscherm in Jamadrink gelden dezelfde keuzes:

| Actie | Resultaat |
|---|---|
| `F8` (neem aan / druk af / begin / selecteer fiches en druk af) | Afdrukken op de ingestelde printer |
| Pdf-knop rechtsonder (of `F9 maak PDF` op sommige schermen) | Maakt een pdf en opent die op de computer; daarna zelf te bewaren, af te drukken of te mailen |
| Mail-knop rechtsonder (facturen, offertes, bestelbons) | Verstuurt het document per e-mail naar de ingestelde ontvangers |

- Facturen: een groene markering op het afsluitscherm betekent dat de factuur automatisch gemaild wordt; manueel mailen geeft dan de vraag of je tweemaal wil verzenden.
- Etiketten (`V.9.1.6`, `V.9.2.6`): `F8 selecteer` drukt af op de ingestelde printer; pdf-knop voor een pdf.
- Printerinstellingen: parametermenu via hoofdmenu `+` `J` `1` (bron: Navigeren binnen Jamadata). Details over printers staan in de documentatie printers/installatie.
- Foutcodes bij afdrukken: 13 (afprinten afgebroken), 17 (printer error), 18 (printer bezet door andere gebruiker); zie `jamadrink-foutcodes.md`.

## 2. Factuurlay-out: specificaties achtergrond in PNG

Wanneer een klant zijn eigen factuurpapier/huisstijl als achtergrond wil (bv. aangeleverd door de drukkerij), moet het bestand aan deze eisen voldoen:

| Eigenschap | Waarde |
|---|---|
| Formaat | PNG |
| Kleurdiepte | 8-bit |
| Resolutie | 300 dpi |
| Afmetingen | 2480 x 3507 pixels (A4) |

De bron beschrijft niet waar het bestand geplaatst wordt of hoe het aan de lay-out gekoppeld wordt; dat gebeurt door Jamadata zelf (te verifiëren bij tweede lijn).

## 3. Wat er op het document komt (instelbaar door de gebruiker)

| Onderdeel | Waar instellen |
|---|---|
| Vaste teksten 1–4 op bon/factuur | Facturatieparameters `+` → `4`; per document twee nummers kiezen. Zie `jamadrink-bons-en-facturen.md` §6 |
| Vrije eindtekst / opmerking op bon of factuur | Eindscherm van het document |
| Offerte: kolommen, 6 vrije tekstlijnen, 4 vaste lijnen, eigen firmagegevens (blanco papier), prijzen zonder accijns | Afsluitscherm offerte en `V.5.6.+`. Zie `jamadrink-offertes-verhuur-rappels.md` |
| Rappelbrieven (tekst, vet/breed/onderlijnd/gecentreerd, positie op blad) | `B.5.3` → `F10`. Zie `jamadrink-offertes-verhuur-rappels.md` |
| Klantenmemo en extra info op lijsten | Opties bij het afdrukken van klanten-/leverancierslijsten |
| Prijzen op bestelbon aan leverancier | Vinkje op de hoofding van de bestelbon |

## 4. Mailsjablonen en de handleiding achter het vraagteken

Bron: OneNote-notitie "Aanpassen Lay-outs" (kort, deels in steekwoorden).

- Pad in het programma: **Hoofdmenu Jamadata → `+` → `J` → `5` → `F8`**, daar staat een **vraagteken**. Dat opent het pdf-handleidingbestand, met daarin de link naar een **.msg-naar-.eml-convertor** (vermoedelijk om een in Outlook bewaard .msg-bericht om te zetten naar .eml voor de sjablonen; de bron licht dit niet toe).
- Locatie van de sjablonen bij de klant: **Deze computer > Jamadata (meestal de J-schijf) > Mail > Template**.
- De notitie is getiteld "Aanpassen van mail template"; het gaat dus om de lay-out van mails, niet van de factuur zelf. Het inhoudelijk personaliseren van mailsjablonen staat in de documentatie mail (module 2800A).

Onzeker / te verifiëren: de precieze benaming van menupunt `+ J 5` staat niet in de bron.

## 5. Probleem: ontvanger ziet enkel strepen in de gemailde pdf

- Symptoom: een klant mailt een factuur (pdf) en de ontvanger ziet in de pdf alleen strepen, of de afdruk bij de ontvanger toont strepen.
- Oorzaak: een instelling van Adobe Acrobat Reader bij de **ontvanger**, niet een fout in Jamadata.
- Oplossing bij de ontvanger: in Acrobat Reader op **Afdrukken** klikken → **Geavanceerd** → onderaan **"Afdrukken als afbeelding"** aanvinken. Adobe beschrijft dit in zijn kennisbank ("quick fix: print PDF as image").

## 6. Klantenhandleidingen (pdf) aanpassen en klaarzetten – intern

Enkel voor Jamadata-medewerkers. De vraagtekenknop op een scherm opent een deelhandleiding (pdf) per module.

1. De bronbestanden van de handleidingen worden aangepast in de interne map `V:\pdf\sourcen`.
2. Na het aanpassen opslaan als pdf in `\pdfs`, waarbij de tekst achter het nummer uit de bestandsnaam wordt verwijderd (de pdf heet enkel het modulenummer, bv. `0266A`).
3. De pdf kopiëren naar de webserver met de handleidingen (map `...\Jamadata\handleidingen` op de webserver) via extern bureaublad. (serveradres en aanmeldgegevens: zie interne bron)

De nummering van de modulehandleidingen (bv. 0023A Klantenrappels, 0234A Herafdrukken facturen, 0266A Beheer offertes) komt overeen met de bestandsnamen in de map "Handleidingen modules".

## 7. Veelvoorkomende vragen

| Vraag | Antwoord |
|---|---|
| "Kan mijn drukkerij de factuurlay-out aanleveren?" | Ja, als PNG, 8-bit, 300 dpi, 2480 x 3507 px (A4) |
| "Ik wil een pdf in plaats van papier" | Pdf-knop rechtsonder op het afdrukscherm |
| "Mijn klant ziet strepen in de factuur-pdf" | Instelling Acrobat Reader bij de ontvanger: afdrukken als afbeelding (§5) |
| "Op blanco papier staat mijn firmanaam niet op de offerte" | `V.5.6.+` → Eigen firmagegevens afdrukken |
| "Waar staan de mailsjablonen?" | Jamadata-schijf (meestal J:) > Mail > Template |
| "De printer is bezet / print niet" | Foutcodes 17/18; printerparameters via `+ J 1`; verder zie documentatie printers |

## Bronnen

- `HOWTO-Specificaties factuurlayout in PNG.docx` (map Jamadrink)
- `HOWTO-Probleem strepen bij PDF.docx` (map Jamadrink)
- `HOWTO-Aanpassen HANDLEIDINGEN Jamadata.docx` (map Jamadrink; aanmeldgegevens weggelaten)
- `Aanpassen Lay-outs.pdf` (map Onenote; dubbel in map Jamadrink)
- `Navigeren binnnen Jamadata.pdf` (map Onenote)
- `gebruikershandleiding JAMADRINK 2.0.docx` (map Jamadrink): afdruk-/pdf-/mailknoppen
- `0266A - Beheer offertes.docx`, `0023A - Klantenrappels.docx` (map Jamadrink/Handleidingen modules): verwijzingen
