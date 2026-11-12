# Documenten: factuur-/bonlayouts, mailtemplates en Peppol – praktijkkennis uit de opleidingen juni–augustus 2026

Gebruik dit document voor: helpdeskvragen en interne taken rond het aanpassen van de layout van facturen, leveringsbons en andere documenten (gegevens in de hoofding, teksten onderaan), het aanpassen van de e-mailtemplates waarmee Jamadata documenten mailt, en praktijkvragen over Peppol (status van een klant, btw- en GLN-nummer, factuur niet teruggevonden door de ontvanger, waar het XML-bestand staat).

> **Let op – bron is gesproken opleiding.** Deze inhoud komt uit automatisch getranscribeerde (Whisper) opleidingssessies. Menupunten, mapnamen en bestandsnamen zijn zo goed mogelijk gereconstrueerd en kunnen herkenningsfouten bevatten. Voor layouts en mailtemplates bestaan interne handleidingen (OneNote: "factuurlayout aanpassen", handleiding mailtemplates); controleer bij twijfel daar. Onzekere plaatsen zijn gemarkeerd met "te verifiëren".

---

## 1. Welke layout en welke mailtemplate hoort bij welk document?

**Waar:** Hoofdmenu voorraad > **+** (parameters) > **J** (JMS-instellingen) > **2 Documenteigenschappen**.

Per documenttype (o.a. 10 = leveringsbons, 11 = facturen, kopie factuur, kopie bon, offertes, rappels, …) staat hier:
- het **nummer van de layout** (achtergrond waarop het pakket de gegevens afdrukt);
- de naam van de **mailtemplate** (bv. `FACT1` → bestand `FACT1.eml`).

Noteer vóór je iets aanpast welke layoutnummers de klant gebruikt (bv. layout 1 voor facturen en factuurkopieën, layout 3 voor leveringsbons). Het is niet uitgesloten dat een nummer ontbreekt of dat de klant er meer heeft dan hij zelf weet. (opleiding 04-08-2026, ca. 00:27–00:28; 06-08-2026, ca. 01:01–01:02)

---

## 2. Layout van factuur of bon aanpassen

### 2.1 Eerst bepalen waar de gegevens vandaan komen
Een layout is een afbeelding (kaders, logo, vaste teksten) waarop het pakket de variabele gegevens in vakjes drukt. Er zijn twee gevallen:

| Situatie | Waar aanpassen |
|---|---|
| De layout heeft **geen hoofding** (bovenaan leeg): de firmagegevens worden door het pakket afgedrukt | Hoofdmenu > **+** > **1 Firmagegevens**. Bv. een faxnummer dat weg moet: daar het veld leegmaken. Geen layoutwerk nodig. Doe dit bij voorkeur samen met de klant (scherm overnemen), zodat hij ziet wat er in zijn pakket wijzigt. |
| De firmagegevens staan **in de layout zelf** (hoofding, logo, voetteksten zoals verkoopsvoorwaarden) | de layout aanpassen (2.2) |

Controleer dit per document: bij dezelfde klant kan de bon zonder hoofding zijn en de factuur met. Een proefafdruk naar pdf (bv. een bestaande bon openen via Facturatie > Leveringsbons > aanpassen en op het einde pdf kiezen, zonder iets te bewaren) toont meteen wat van het pakket komt en wat van de layout. (04-08-2026, ca. 00:29–00:33)

De **vaste teksten** die op bons/facturen gekozen kunnen worden (tekst 1–4) staan in Hoofdmenu > + > 4 Facturatieparameters – zie `opleiding-zomer-jamadrink-prijzen-en-facturatie.md`.

### 2.2 Werkwijze layout aanpassen (interne taak)
De bronbestanden van alle klanten staan centraal bij Jamadata in de layoutmap, per klant en per layoutnummer (bestandsnaam: "LT" + afkorting van de klant + nummer). Per layout zijn er **twee bestanden**: het **Word-document** (bron) en de **PNG** (wat het pakket gebruikt).

1. Zoek alle layouts van de klant op en **open ze allemaal**, ook de nummers waar niet om gevraagd is: ze kunnen van een andere firma van de klant zijn (niets doen), maar ook van dezelfde firma (bv. een winkel, offertes, een ouder model) en dan moet dezelfde wijziging daar meestal ook gebeuren. Vraag het de klant; dat komt goed over.
2. Bij een grotere wijziging: eerst een **kopie** van het Word-document maken (opslaan als … "old").
3. Pas het Word-document aan. **Let op dat er niets verschuift**: de kaders en vakjes moeten exact op hun plaats blijven, anders drukt het pakket naast de vakjes of over andere tekst. Verwijder je een regel in de hoofding en schuift daardoor bv. het vak van het leveradres op, laat dan een lege regel staan. Kijk ook of tekst onderaan niet buiten de afdrukmarge valt.
4. Word-document opslaan.
5. **Afdrukken naar de virtuele printer FinePrint** (moet geïnstalleerd zijn; installatie staat in de OneNote-handleiding). Controleer in het voorbeeld – inzoomen – de boven- en onderkant.
6. In FinePrint **opslaan als PNG**, in dezelfde map en met exact dezelfde naam als de bestaande PNG (overschrijven). Instellingen: **kleurdiepte 8 bit, resolutie 300 dpi**; "view output file" aanzetten om het resultaat meteen te controleren. Deze instellingen blijven daarna bewaard.
7. **Sluit FinePrint na elk document.** Blijft het openstaan, dan wordt het volgende document als tweede pagina toegevoegd en bewaar je de verkeerde afbeelding.
8. Zet **beide bestanden** (Word + PNG) bij de klant in de map **`PROG`** onder de Jamadata-map op de server. Dat kan door het scherm van de server over te nemen en de bestanden te kopiëren, of via de interne klaarzet-procedure waarbij de bestanden met een begeleidend bericht voor de klant klaargezet worden en hij ze ophaalt zoals een update.

**Afspraken:**
- Bij veel wijzigingen (logo, kleuren, lettertype, nieuwe firma): eerst een **pdf ter goedkeuring** naar de klant sturen; anders blijf je aanpassen.
- Lees het ticket nauwkeurig en doe precies wat gevraagd is; twijfel je, vraag het na.
- Een layoutaanpassing is **betalend maatwerk** (regie); meld dat vooraf en geef een tijdsinschatting. Een kleinigheid van vijf minuten wordt niet aangerekend. Richtwaarde uit de opleiding: twee eenvoudige layouts ≈ een half uur voor een ervaren medewerker; een uur aanrekenen is redelijk.
- De klant kan dit niet zelf (hij heeft het hulpprogramma niet en de bronbestanden worden bij Jamadata beheerd).

(04-08-2026, ca. 00:25–00:59; 06-08-2026, ca. 00:20–00:24)

---

## 3. E-mailtemplates aanpassen

**Wat:** de tekst (en opmaak, logo, handtekening, eventuele vaste bijlage) van de e-mail waarmee Jamadata een factuur, bon, rappel, … verstuurt. Per documenttype is er een template; de naam staat in de documenteigenschappen (hoofdstuk 1).

**Waar staan ze:** bij de klant op de server in de Jamadata-map: `MAIL\TEMPLATES`, als **.eml**-bestanden (bv. `FACT1.eml` voor facturen, een template voor rappels, een voor bons).

Er bestaat een **handleiding voor de klant** om dit zelf te doen. Vindt de klant het te ingewikkeld, dan doet Jamadata het in regie (zoals een layout).

### 3.1 Werkwijze voor een echte aanpassing (opmaak, logo, bijlage)
Outlook kan een .eml openen maar niet als .eml bewaren (enkel als .msg). Daarom:
1. Neem een **kopie** van de originele .eml (werk bij voorkeur op een recente kopie van de klantbestanden; controleer eerst of er een recente back-up van de klant binnen is, anders eerst een back-up laten ophalen).
2. Open de .eml in (klassieke) Outlook. Ze is niet bewerkbaar: kies **Doorsturen**; nu kan je de inhoud aanpassen.
3. Verwijder alles wat door het doorsturen is toegevoegd: de doorstuur-kop en **je eigen handtekening**.
4. Pas de tekst/opmaak/bijlage aan.
5. **Bestand > Opslaan als** in dezelfde map, met **exact dezelfde naam** als de template (zelfde hoofdletters); Outlook maakt een **.msg**.
6. **Converteer .msg naar .eml** met een conversieprogramma of een online converter (in de opleiding gebeurde dit online; er staat normaal geen gevoelige bedrijfsinformatie in een template).
7. Geef het resultaat exact de juiste naam (bv. `FACT1.eml`) en zet het in `MAIL\TEMPLATES` bij de klant.

### 3.2 Snelle tekstcorrectie
Voor een kleine tekstwijziging (naam, tikfout) kan de .eml rechtstreeks in **Kladblok** geopend en bewaard worden:
- de tekst staat er **twee keer** in (platte tekst en HTML): pas beide aan (zoeken/vervangen, maar controleer elke vervanging);
- kom niet aan het lange blok onleesbare tekens: dat is de ingesloten bijlage (bv. een pdf);
- een bijlage toevoegen of vervangen kan zo niet: dat moet via Outlook (3.1).

### 3.3 Gekende aandachtspunten
- **Nieuwe Outlook**: bij sommige klanten werkt "mail openen via Outlook" vanuit het pakket niet met de nieuwe Outlook-app; met de klassieke Outlook wel. De opleider vermoedt een beperking aan Microsoft-zijde; een oplossing was er op het moment van de opleiding niet (te verifiëren/op te volgen).
- Oefen aanpassingen eerst in de demo-omgeving.

(06-08-2026, ca. 00:47–01:08)

---

## 4. Peppol in de praktijk

### 4.1 Staat de klant op Peppol? (melding "Peppol niet toegelaten")
- Klantfiche: Hoofdmenu voorraad > 9 > 2 > 1 > klant > **`+`** > het **i-knopje** bij Peppol toont de status. Gebruikers melden vaak "het pakket zegt Peppol niet toegelaten, maar de klant zegt dat hij op Peppol zit": via dit knopje wordt de klant opgezocht en zie je meteen wat het antwoord is.
- Zonder **btw-nummer** op de klantfiche kan er niet via Peppol verstuurd worden.
- **GLN-nummer** (Global Location Number) en btw-nummer: in een concreet ticket stond enkel een GLN-nummer ingevuld en geen btw-nummer; het resultaat was "Peppol niet toegelaten". Na het invullen van het btw-nummer (het GLN-nummer mocht blijven staan) werkte het. Uitleg van ontwikkeling: normaal wordt op het btw-nummer geadresseerd; het GLN-nummer duidt een locatie aan (bv. scholengroep met één btw-nummer en meerdere vestigingen) en volstaat enkel op zichzelf als het als zodanig geregistreerd is. De interne FAQ vermeldde nog dat een GLN-nummer alleen voldoende is – **tegenstrijdig, te verifiëren**.
- Heeft de klant een **facturatieklant** op zijn fiche, dan gelden de Peppol-gegevens van die facturatieklant.

(09-06-2026, ca. 00:23–00:27; 25-06-2026, ca. 00:35–00:38)

### 4.2 Factuur opnieuw via Peppol versturen
- Facturatie > herafdrukken facturen, of Boekhoudmenu > 4 > klant > factuur-icoon: daar kan de factuur opnieuw via Peppol verstuurd en op Peppol gecontroleerd worden. (25-06-2026, ca. 00:11; 02-07-2026, ca. 00:52)

### 4.3 "De ontvanger vindt de Peppol-factuur niet" / vraag om het XML-bestand te mailen
- Peppol is de officiële weg. Eerste antwoord: de factuur **opnieuw via Peppol versturen** (4.2).
- Het XML-bestand (UBL) van elke verstuurde factuur wordt bewaard op de server van de klant: Jamadata-map > **`FACT\UBL`**. De bestandsnaam bevat de dossier-/klantcode, het jaartal en het factuurnummer. Het bestand kan desnoods gemaild worden, maar dat is geen officiële verzending.
- De paden waar kopieën van facturen en Peppol-bestanden bewaard worden, staan in Hoofdmenu > **+** > **5** (F8 doorlopen). Een pad dat begint met `..\` vertrekt vanuit de map `PROG` en gaat één niveau omhoog (naar de Jamadata-map).
- Zonder de klant te storen kan je in de dagelijks binnenkomende mappenlijst van de klant (`dir.lst`, zie `opleiding-zomer-server-it-en-helpdeskwerkwijze.md`) nagaan of het bestand bestaat.
- Controleer het factuurnummer in de vraag: in het behandelde ticket stond een tikfout in het nummer.

(06-08-2026, ca. 00:09–00:16)

### 4.4 Peppol en de kassa
- Bij het maken van een factuur op de kassa wacht de kassa op antwoord van het Peppol-netwerk; duurt dat te lang, dan volgt een **communicatiefout**. Zie `opleiding-zomer-kassa.md` (hoofdstuk 3.3) voor de controle en rechtzetting.
- Werkt het i-knopje of Peppol bij één gebruiker telkens tot het programma vastloopt, terwijl het bij anderen werkt, dan is de oorzaak vaak lokaal (pc/netwerk/beveiliging van die klant); dat is moeilijk aan te tonen en vraagt uitsluiting stap voor stap. (18-06-2026, ca. 00:06–00:08)

### 4.5 Inkomende Peppol-facturen
Inboeken via Boekhoudmenu > 1 > P; de originele factuur is daarna als pdf te openen vanuit boekhouding punt 4. Zie `opleiding-zomer-boekhouding.md`. (07-07-2026, ca. 00:29 en 00:36)

---

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):
- Kennisoverdracht Jamadata-20260609_100321-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260618_101035-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260625_102119-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260702_110347-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260707_100958-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260804_152719-Opname van vergadering.txt
- Kennisoverdracht Jamadata (Willow)-20260806_103718-Opname van vergadering.txt
