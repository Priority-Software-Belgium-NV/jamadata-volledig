# Kassa (Key-Conen kassa): praktijkkennis uit de opleidingen juni–juli 2026

Gebruik dit document voor: helpdeskvragen over de dagelijkse bediening van de Jamadata-kassa (knoppen bovenaan, Diverse, bons/facturen op de kassa, cadeaubons, bewaarbons), dagtotalen (F9 Controle, Z-totaal), de communicatiefout bij facturatie op de kassa, het oude offline bonsysteem, barcodes die op de kassa werden toegevoegd, kassablokjes, de transfert kassa ↔ server (K en N), het verkoopbestand (KASLOK), het kasverslag, de verkooplijsten/controlelijsten, kassapromoties (o.a. Prik&Tik-folder) en enkele hardwareproblemen.

> **Let op – bron is gesproken opleiding.** Deze inhoud komt uit automatisch getranscribeerde (Whisper) opleidingssessies waarin een ervaren Jamadata-medewerker de helpdesk opleidt. Menupunten, toetsen en bestandsnamen zijn zo goed mogelijk gereconstrueerd, maar kunnen herkenningsfouten bevatten. Controleer bij twijfel tegen de handleiding (in het pakket: het vraagteken `?` rechtsboven bij het betreffende menupunt). Plaatsen die onzeker zijn, staan gemarkeerd met "te verifiëren".

Notatie: "2 > K" betekent: in het Hoofdmenu voorraad punt 2 (Beheer Icone-kassa) kiezen en daarna punt K.

---

## 1. Basisbediening en veelvoorkomende bedieningsfouten

### 1.1 Korting in procent
- Geef het percentage **zonder minteken** in en druk dan op de knop korting %: bv. `5` + korting %.
- Wie `-60` + korting % ingeeft, krijgt de korting **erbij geteld** in plaats van eraf. (opleiding 09-06-2026, ca. 00:01)

### 1.2 Onbekende barcode / foutlijn in het ticket
- Wordt een barcode gescand die de kassa niet kent, dan komt er een foutlijn in het ticket. Zolang die erin staat, **werkt Einde niet**.
- Is het de laatste lijn: druk op **Clear**. Zoek het artikel daarna via PLU of via de blokjes. (09-06-2026, ca. 00:03)

### 1.3 "Stoppen" werkt niet
De knop Stoppen (linksboven) werkt enkel als er nergens nog een open ticket staat. Controleer in deze volgorde:
1. Staan er nog artikels in het huidige ticket? → afrekenen of Clear ticket.
2. Staat er nog iets onder **Andere klant** (verkoper A1 ↔ A2)? De kassa kan per verkoper twee tickets tegelijk openhouden.
3. Staat er nog iets bij een **andere verkoper** (A, B en eventueel C – C heeft geen knop op het scherm maar kan bestaan)? In totaal kunnen er dus tot 6 tickets tegelijk openstaan.
4. Moet het ticket bewaard blijven (bv. klant komt later betalen)? → Diverse > Bewaar bon (zie 2.5), daarna lukt Stoppen wel.

(09-06-2026, ca. 00:14–00:16 en 00:49)

### 1.4 Lijn wissen of volledig ticket wissen
- Knop **Ticket**: ticket bekijken en één lijn wissen.
- Knop **Clear ticket**: het volledige ticket wissen (er komt een bevestigingsvraag). Handiger dan lijn per lijn wissen bij lange tickets. (09-06-2026, ca. 00:17)

### 1.5 Memo van de klant
Een memo op de klantfiche wordt **getoond** wanneer de klant op de kassa (of in het pakket) wordt gekozen, maar wordt **nooit afgedrukt**. (09-06-2026, ca. 00:21)

---

## 2. De knop Diverse

### 2.1 Aantal exemplaren ticket
- Bovenaan in Diverse: aantal exemplaren van het kasticket: 1, 2, 3, 4 of `-` (geen afdruk).
- Staat het op `-`, dan wordt er geen ticket gedrukt. Wil de klant er toch één: Diverse > **Druk af** (onderaan) = het laatste ticket. Een ouder ticket: telkens Diverse > "vorig ticket" en dan Druk af (je ziet het ticket niet vooraf op het scherm).
- **Gekend probleem:** soms staat hier plots een vreemd getal (bv. 98) en crasht de kassa bij het afdrukken. Oplossing: in Diverse op die knop blijven drukken; het getal telt af tot het terug op 1 staat, daarna kan je weer normaal 1–4 kiezen. Oorzaak onbekend. (09-06-2026, ca. 00:32)

### 2.2 Uitgaven en inkomsten (geldbewegingen in de lade)
Elke beweging in de geldlade moet geregistreerd worden.
- **Uitgave** (bv. geld uit de lade voor een aankoop): bedrag intikken > Diverse > Uitgaven > omschrijving > F8 > betaalwijze (meestal geld). Er komen twee ticketjes (één voor in de lade).
- **Inkomst**: zelfde werkwijze via Inkomsten.
- **Startgeld** 's morgens: bedrag > Diverse > Inkomsten > "startgeld" > geld.
- **Klant betaalt een factuur aan de kassa**: bedrag > Diverse > Inkomsten, en zet in de omschrijving zoveel mogelijk info (klantnummer + factuurnummer). Die tekst komt later terug op het kasverslag en helpt de boekhouding.
- **Leverancier wordt cash betaald uit de kassa**: Diverse > Uitgaven met vermelding van de leverancier; in het kasverslag kan dit op de leveranciersrekening geboekt worden.

(09-06-2026, ca. 00:33–00:36; 11-06-2026, ca. 00:44 en 00:49)

### 2.3 Cadeaubons: artikel óf betaalmiddel
Er zijn twee manieren; de klant moet er één kiezen en die consequent gebruiken (verkoop én inname op dezelfde manier).

| Manier | Verkoop | Inname | Opmerking |
|---|---|---|---|
| Als **artikel** | cadeaubon als gewoon artikel verkopen | als artikel terugnemen (negatief) | Eenvoudig, kan op factuur. Nadeel: er wordt btw afgedragen bij verkoop (meestal hoogste tarief) terwijl niet elke bon terugkomt; de boekhouder moet dat rechtzetten. |
| Als **betaalmiddel** | bedrag > Diverse > Verkoop cadeaubon > Einde > betaalwijze | bij afrekenen: Einde > bedrag > Cadeaubon, rest met ander betaalmiddel | Fiscaal de correcte manier. **Kan niet op factuur**: de kassa geeft een melding dat een cadeaubon niet gefactureerd kan worden. |

De uitgegeven en ontvangen cadeaubons staan apart op het financieel overzicht van de dagtotalen. (09-06-2026, ca. 00:36–00:41)

### 2.4 Afdrukken kastoestand en Afdrukken controle
- **Afdrukken kastoestand**: toont wat er in kas is sinds de laatste keer dat hier op **Clear** is gedrukt. Clear zet enkel dit tellertje op nul; er worden geen verkopen gewist. Wordt bijna niet meer gebruikt (is van vóór de cadeaubons e.d.).
- **Afdrukken controle**: dagtotalen vanuit het kassaprogramma zelf. De opleider gebruikt dit nooit en gaat altijd via **Stoppen > F9 Controle** (zie hoofdstuk 4), omdat dat in een ander programmaonderdeel zit en hij ooit een verschil tussen beide heeft gezien. Advies aan klanten: gebruik F9 Controle.

(09-06-2026, ca. 00:41–00:43)

### 2.5 Bewaar bon / Oplaad bon (ticket parkeren)
- **Bewaren**: producten ingeven > Diverse > Bewaar bon > bonnummer kiezen > eventueel naam en telefoonnummer invullen. De kassa drukt een ticket met totaal, vermelding dat het niet betaald is en een **barcode**. Het ticket is uit het scherm weg, dus Stoppen werkt weer.
- **Terug opladen**: de barcode scannen, of Diverse > Oplaad bon > nummer kiezen (naam/telefoon/bedrag staan erbij). De producten komen terug in het ticket en er kan afgerekend worden.
- Typische toepassingen:
  - klant is portefeuille vergeten en komt later betalen;
  - **biermanden/geschenkmanden**: de inhoud één keer scannen (plus eventueel een bedrag voor mand/verpakking), bewaren, en het bonnetje met barcode aan de mand hangen; aan de kassa enkel de barcode scannen;
  - bij het afsluiten staat er nog een ticket dat later nodig is.
- **Inventaris:** als de klant voor biermanden een vaste reeks bonnummers gebruikt, kan de inhoud van die nog openstaande bons bij de stock geteld worden: Hoofdmenu voorraad > A (periodieke werkzaamheden) > 2 (opmaken jaarinventaris) > punt "verwerken van artikels op werkbons / kassa / biermanden", van bonnummer tot bonnummer. De volledige inventarisprocedure staat stap voor stap in de help van dat menupunt. Gebruik bonnummers voor "later betalen" en voor biermanden dus niet door elkaar.

(09-06-2026, ca. 00:49–00:55)

### 2.6 PDA-bons (leeggoed- en verkoopbons van de PDA)
- Normaal wordt het ticketje van de PDA (met barcode) aan de kassa gescand.
- Werkt de scanner niet, of is er geen ticket: Diverse > **PDA-bons** > bon kiezen > **Oplaad bon**. Het bonnummer staat op het PDA-ticket; in de lijst zie je per bon het totaalbedrag.
- Zonder afgedrukt ticket weet de kassier niet welke bon bij welke klant hoort; dan zit er niets anders op dan navragen/vergelijken. Daarom: altijd een ticket of nummerkaartje meegeven.
- Ruwe inschatting van de opleider: ca. 20 % van de klanten heeft een leeggoedautomaat (bon wordt gescand), 20–30 % werkt met PDA, de rest tikt leeggoed manueel in.

(09-06-2026, ca. 00:43–00:48) Zie ook `opleiding-zomer-pda.md`.

### 2.7 eID-lezer
Met een aangesloten eID-lezer kan de identiteitskaart op elk moment in het ticket ingelezen worden. De kassa vraagt dan:
- **Zet op ticket**: naam/adres (en rijksregisternummer) komen op het ticket of de factuur. Bedoeld voor verkoop op krediet aan onbekenden (bewijs bij niet-betaling).
- **Klantenkaart**: de kaart koppelen aan een bestaande klantenkaart of er een nieuwe mee aanmaken (gegevens worden ingelezen); punten worden bijgeteld.

De klantenkaart (manueel of via eID) moet altijd **vóór Einde** gekozen worden. (09-06-2026, ca. 01:10–01:14)

---

## 3. Factuur of bon maken op de kassa

### 3.1 Werkwijze (online systeem, blauwe knoppen)
1. Knop **Factuur** (mag bij het begin of op het einde van het ticket).
2. Klant zoeken: "zoek op naam" zoekt op het begin van de naam; het **vergrootglas** zoekt overal in de fiche (zoals in het pakket). Met **Nieuw** kan een nieuwe klant aangemaakt worden; je kan de klantfiche ook bekijken/aanpassen. Dit scherm is het pakket zelf: de kassa maakt op de achtergrond verbinding met de server.
3. Kies **Maak factuur** of **Maak bon** (leveringsbon).
4. Einde: er is nu een extra betaalknop **Krediet** (klant betaalt later).
5. Eindscherm facturatie (zoals op de server): referentie, afdruk, pdf, mailen, Peppol. Eenmaal op dit scherm kan je niet meer terug.

- Een **bon** van de kassa staat meteen in het pakket (Hoofdmenu > 8 Facturatie > Leveringsbons > aanpassen). Reden om een bon te maken i.p.v. een factuur: de klant komt meermaals per maand en wil één verzamelfactuur.
- Staat op de klantfiche **"eigen prijs op kassa" = ja**, dan vraagt de kassa of de specifieke prijzen van de klant geladen moeten worden; bij ja wordt het ticket herrekend van kassaprijs naar klantprijs.
- Staat op de klantfiche een **facturatieklant**, dan wordt de factuur op die andere klant gemaakt. Ook de Peppol-instelling van de facturatieklant geldt dan (verklaart waarom een factuur "onverwacht" niet via Peppol vertrekt).
- Zonder btw-nummer op de klant gaat Peppol niet. Zie `opleiding-zomer-documenten-layouts-en-peppol.md`.

(09-06-2026, ca. 00:17–00:27)

### 3.2 Hoe de kassa met de server praat
- Rechtsonder op de kassa draait een klein Jamadata-venster (een sessie naar de server). Elke knop in het factuurscherm stuurt een bestandje naar de server; de server antwoordt met een bestandje terug.
- **Blauwe knoppen** in het factuurscherm = online versie (verbinding met de server is er).
- **Groene knoppen** = de oude **offline** versie. De kassa valt hierop terug als de sessie naar de server er niet is. Vraag bij "factuur maken werkt niet" dus altijd: staan er blauwe of groene knoppen?

(09-06-2026, ca. 01:33 en 01:41–01:43)

### 3.3 Communicatiefout bij factuur/bon op de kassa
**Oorzaak:** de uitwisseling kassa ↔ server loopt mis (netwerk valt even weg, antwoord komt te laat). Sinds Peppol komt dit vaker voor: de kassa wacht op antwoord van het Peppol-netwerk en dat is een timingkwestie (te kort wachten of te lang wachten geeft beide de fout). (09-06-2026, ca. 01:33–01:38; 23-06-2026, ca. 00:14)

**Kernregel:** het ticket is nooit weg. Het staat óf bij de bons/facturen óf bij de particuliere verkopen. Staat het bij de particuliere verkopen, dan zit het **fout**: het telt mee in de dagontvangsten per btw-tarief, en als de factuur daarna opnieuw gemaakt wordt, wordt de omzet twee keer belast.

**Controle (altijd doen):**
1. Kassa: Stoppen > **F9 Controle**.
2. Juiste dag selecteren ("laatst gebruikte dag" als het vandaag gebeurde, anders "enkel geselecteerde" en de dag aanduiden).
3. Geselecteerde verkopen: **enkel bons/facturen**.
4. **Controleband: ja**; de overige afdrukken mogen op nee.
5. Druk af. Elk ticket op bon/factuur van die dag staat nu op de band.

**Conclusie:**
- Ticket staat **wel** op deze band → het staat correct bij bons/facturen; er is niets recht te zetten aan de totalen.
- Ticket staat er **niet** op → het zit bij de particuliere verkopen. Rechtzetten: hetzelfde ticket **negatief** ingeven als gewoon (particulier) ticket, daarna de factuur opnieuw maken.

**Nooit de datum van de kassa terugzetten** om iets van een vorige dag recht te zetten: het verkoopbestand is sequentieel en raakt dan in de war. Rechtzetten gebeurt op de datum van vandaag.

**Nieuwere kassaversie (rond mei 2026):** bij een time-out wordt het ticket niet meer als particuliere verkoop weggeschreven maar als **bon**; van die bon kan dan in het pakket een factuur gemaakt worden. Niet alle klanten hebben die versie al, dus de controle hierboven blijft nodig. Tip: geef bij het klaarzetten van een update ook de laatste kassaversie mee.

(09-06-2026, ca. 01:31–01:41; 23-06-2026, ca. 00:14–00:17)

Hulpmiddel in het pakket: 2 > punt E "Lijst kastickets" (pdf of Excel) toont per ticket o.a. de betaalwijze en waar communicatiefouten zaten. (11-06-2026, ca. 01:30)

### 3.4 Oud offline bonsysteem (groene knoppen, tekst "facturatie op")
**Herkennen:**
- groene knoppen i.p.v. blauwe in het factuurscherm;
- het bonnetje komt twee keer uit de printer;
- op het ticket staat **"facturatie op"** + klantgegevens (bij het online systeem staat er **"gefactureerd op"**).

Bij "facturatie op" is er dus **geen factuur gemaakt**: het is een offline leveringsbon die nog in het pakket gefactureerd moet worden. Het nummer bij de klant op zo'n ticket is het interne recordnummer (computernummer) van de klant, niet noodzakelijk het eigen klantnummer.

**Factureren in het pakket:**
1. Kassa: Stoppen > transfert naar de server (N). Pas daarna staat de bon op de server.
2. Controle: 2 > 5 (afdrukken diverse verkooplijsten) > 1 "nog te factureren tickets", periode 01-01-01 tot vandaag, pdf.
3. Hoofdmenu voorraad > 8 Facturatie > 4 "Afdrukken facturen uit bons van de Icone-kassa" (het puntnummer kan per klant verschillen naargelang de modules). Kies de juiste kassa, klant per klant of per serie, F8.
4. Onderaan dat scherm staat een **tabel met per kassa de datum en het uur van het bonbestand** op de server. Staat daar geen recente datum (die van de bon), dan is er nog niet doorgestuurd en vind je niets.
5. Bij meerdere kassa's kunnen de bonbestanden eerst samengevoegd worden (punt in hetzelfde scherm).

Het bonbestand is één bestand per kassa in de kassamap (naam in de transcriptie onduidelijk – KASFACT/KASKLT, te verifiëren); het is met Kladblok leesbaar om te controleren of de bon er inderdaad in zit.

Enkele klanten werken nog bewust met dit offline systeem (voordeel: alle tickets van een maand op één factuur).

(09-06-2026, ca. 01:41–01:47; 11-06-2026, ca. 01:11; 09-07-2026, ca. 00:01–00:08)

---

## 4. Dagtotalen: F9 Controle en Z-totaal

### 4.1 F9 Controle openen en dagen kiezen
Kassa: Stoppen > **F9 Controle**.
- Kalender: gekleurde dagen = dagen met verkoop. **Rood** = de dagen die afgedrukt worden.
- Gewenste dagen: "laatst gebruikte dag" (standaard), "allemaal", "enkel geselecteerde" (zelf dag aanklikken) of een periode "eerste t.e.m. laatste" (eerste en laatste dag aanduiden). Er kan naar vorige maanden gebladerd worden.
- **Neem als standaard** bewaart de gekozen parameters. Wie eruit gaat zonder dit, krijgt de volgende keer weer de oude standaard.

(09-06-2026, ca. 01:15–01:20)

### 4.2 Parameter "geselecteerde verkopen" – belangrijk
| Keuze | Wat komt eruit |
|---|---|
| Enkel particulieren | tickets zonder klant (contante verkoop) |
| Enkel bons/facturen | tickets op bon of factuur |
| **Apart en totaal** | drie reeksen: particulieren, bons/facturen, en totaal (een ticket zonder titel erboven is het totaal) |
| Allemaal | alles samen op één reeks tickets |

**Laat dit nooit op "allemaal" staan.** Het ticket "per btw-percentage" bevat dan ook de facturen. Wie dat bedrag in het kasboek/dagontvangstenboek schrijft, geeft de factuuromzet twee keer aan (facturen zitten al in de factuuromzet). Dit is bij klanten al een jaar lang fout gelopen. Advies van de opleider bij elke installatie: **"apart en totaal"** (meeste detail) of "enkel particulieren". In het kasboek horen enkel de particuliere verkopen. (09-06-2026, ca. 01:18–01:25)

### 4.3 Welke tickets komen eruit
Elk onderdeel kan aan/uit gezet worden:
- **Omzet per artikel** (alfabetisch; bakken en stuks apart).
- **Omzet per groep** (meestal uit; opties: enkel cijfers / met naam / met blanco lijn / met btw-gegevens).
- **Per btw-percentage**: basis, btw en totaal per tarief + leeggoed + algemeen totaal. Dit is wat in het kasboek hoort (enkel particulieren!).
- **Financieel overzicht**: verkochte goederen, leeggoed mee/terug, ontvangen en teruggegeven geld, alle betaalmiddelen apart (Bancontact, Payconiq, maaltijdcheques, Prik&Tik-bons, webshop, …), uitgegeven/ontvangen cadeaubons, afronding, uitgaven, inkomsten (startgeld, betaalde facturen), aantal klanten en gemiddelde verkoop per klant.
- **Controleband** (ja/nee): alle tickets opnieuw in één lange band.

Afronding: contant betaalde tickets worden op 5 cent afgerond; bij Bancontact gebeurt dat in de praktijk niet. Het totaal van de afrondingen staat op het financieel overzicht. (09-06-2026, ca. 01:20–01:28)

### 4.4 PDF van de dagtotalen
- Knop **Maak PDF**: de pdf komt in de map `C:\KASSA` op de kassa. Op de nieuwere Windows 10-kassa's kan je die daar openen, op oudere kassa's niet.
- Na de transfert staan alle bestanden van die map op de server in de map van die kassa (bv. `KASSA-01` voor kassa 1) en kan de pdf op de hoofdcomputer geopend worden.
- Na Maak PDF verandert een icoontje van kleur; dat herstelt zich door F9 Controle te sluiten en opnieuw te openen.

(09-06-2026, ca. 01:28–01:29)

### 4.5 Z-totaal
- Zelfde afdruk als F9 Controle, maar het **sluit de periode af**: onderaan staat het Z-totaalnummer, de kassa, eerste en laatste ticketnummer en begin-/einddatum en uur.
- Na de afdruk vraagt de kassa "afdruk in orde?": **ja** = teller op nul; **nee** = opnieuw kunnen afdrukken. Ook de controleband van het Z-totaal kan mee afgedrukt worden.
- Twee keer per dag een Z-totaal nemen geeft twee totalen voor die dag.
- Wordt nog door heel weinig klanten gebruikt (meestal opgelegd na een fiscale controle).

(09-06-2026, ca. 01:29–01:31)

---

## 5. Barcodes die op de kassa zelf werden toegevoegd

### 5.1 Barcode toevoegen op de kassa (noodoplossing)
Volgorde: **eerst de barcode scannen, dan het artikel kiezen.**
1. Gaat het om een fles/stuk: eerst op **Stuk** drukken.
2. Barcode scannen (kassa kent hem niet).
3. Artikel opzoeken via PLU/blokjes.
4. **Controleren**: staat het juiste artikel en de juiste prijs op het scherm?
5. Diverse > "voeg toe" (koppelt de barcode aan het artikel).

**Meest gemaakte fout:** Stuk vergeten. De barcode van een flesje wordt dan aan de **bak** gekoppeld en de kassa rekent bij elke scan een volledige bak aan.

(09-06-2026, ca. 00:05–00:09 en 00:13)

### 5.2 Waar zit zo'n barcode?
- Enkel **lokaal op die kassa**, in een .dat-bestand in `C:\KASSA` (in de opleiding uitgesproken als "kas-X .dat"; vermoedelijk `KASX.DAT`, te verifiëren). De barcode staat **niet** op de artikelfiche in het pakket, niet op andere kassa's en niet op de PDA.
- Opbouw van een lijn: artikelnummer – `0` of `1` (1 = stuk) – barcode.
- Controle in het pakket: Hoofdmenu voorraad > 9 > 3 > 1 (artikel aanpassen/bekijken) > artikel > **F9 vervolg** toont de barcodes van het artikel.

### 5.3 Verkeerde koppeling verwijderen op de kassa
1. Kassaprogramma stoppen.
2. Het bestand in `C:\KASSA` openen met Kladblok: rechtsklik > Openen met > Kladblok, en het vinkje **"altijd met deze app openen" uitzetten** (anders openen voortaan alle .dat-bestanden in Kladblok).
3. De foute lijn verwijderen, opslaan, sluiten.
4. Kassa opnieuw starten. Blijft de oude koppeling werken, dan zat ze nog in het geheugen: programma volledig afsluiten en opnieuw starten.

(09-06-2026, ca. 00:07–00:09)

### 5.4 De goede oplossing: overnemen in het pakket
1. Kassa: Stoppen > transfert (het lokale barcodebestand gaat mee naar de server).
2. Pakket: Hoofdmenu voorraad > 2 (Icone-kassa) > **+** (extra punten) > **2 "Toevoegen nieuwe artikel-barcodes gescand op de kassa"**: kassanummer en datum ingeven (datum 01-01-01 = alles), F8. De barcodes komen op de artikelfiche (bij het artikel verschijnt een groen plusje = extra barcode), het bestand wordt geleegd en er wordt een leeg bestand klaargezet voor de kassa.
3. 2 > **K** (alles klaarzetten voor de kassa).
4. Kassa: gegevens ophalen (N).

Voordeel: de barcode werkt nu op alle kassa's én op de PDA (bv. voor stocktelling). Leg klanten met een winkel op afstand uit dat toevoegen op de kassa slechts een tijdelijke oplossing is. (09-06-2026, ca. 00:09–00:13)

Controlelijst in het pakket: 2 > 5 > "controlelijst dubbele EAN-nummers" toont barcodes die aan meer dan één artikel hangen (duurt lang; alle artikels worden doorlopen). (11-06-2026, ca. 01:17 en 01:23)

---

## 6. Kassablokjes (iconen) beheren

**Waar:** Hoofdmenu voorraad > 2 Beheer Icone-kassa > 2 (blokjes aanpassen). Het `?` opent de (oudere maar correcte) handleiding; **F12** toont een overzicht van de functietoetsen.

| Toets | Functie |
|---|---|
| F1 | stoppen |
| F3 / F4 | blokje kopiëren / plakken (verplaatsen naar andere plaats) |
| F6 | blokje schrappen |
| F7 | naar de artikelfiche van het blokje |
| F8 | een scherm dieper (in de groep) |
| F10 | een scherm hoger |
| PgUp / PgDn | vorig / volgend blokje |
| F12 | hulpscherm met toetsen |

- **Sterretje** boven een blokje = groep (je kan er met F8 in); een **code** boven een blokje = artikel.
- Maximaal **4 niveaus** diep; 48 blokjes per scherm.
- Artikel invullen: artikelcode intikken, of het begin van de naam + Enter en uit de lijst kiezen.
- De **tekst in het blokje is enkel visueel** (wat de kassier ziet). Op het kasticket komt de **omschrijving van de artikelfiche**, beperkt tot **20 karakters** (facturen: 30). Is op een ticket het einde van de naam (bv. de inhoud) weggevallen, dan moet de omschrijving op de artikelfiche ingekort worden; de breedte/het lettertype van het ticket kan niet aangepast worden. Op de artikelfiche kan (door Jamadata te activeren) een verticale streep op 20 karakters getoond worden als hulp.
- Een artikel mag op meerdere plaatsen staan (bv. veelverkochte artikels ook op het eerste scherm).
- Vergeet het **leeggoed** niet: dat heeft ook blokjes nodig. Artikels die gescand worden, hebben geen blokje nodig.
- De indeling is de keuze van de klant; Jamadata maakt ze niet, maar geeft voorbeelden. Vuistregel: logisch genoeg dat iemand zonder voorkennis de producten vindt.
- Na aanpassen: **2 > K** en op de kassa gegevens ophalen.

(11-06-2026, ca. 00:25–00:36)

---

## 7. Transfert kassa ↔ server: K en N

- **K (in het pakket, 2 > K "klaarzetten alle gegevens voor de kassa")**: nodig na élke wijziging die naar de kassa moet (prijzen, blokjes, promoties, klanten, barcodes). Op het scherm staan vinkjes per onderdeel dat de klant heeft; gewoon F8 en wachten. De bestanden worden klaargezet in de map `KASSA` onder de Jamadata-map op de server (bij klanten met meerdere vestigingen kunnen er aparte mappen per vestiging zijn).
- Zowel de **huidige prijzen als de prijzen met een toekomstige ingangsdatum** gaan mee: een prijswijziging voor de 1e van de maand mag dus vooraf klaargezet worden; de kassa schakelt zelf om.
- **N (op de kassa, na Stoppen: gegevens ophalen/dagelijks transfert)** werkt in **twee richtingen**: haalt de klaargezette gegevens op (bv. het artikelbestand) én stuurt de verkopen en alle bestanden van `C:\KASSA` naar de server.
- K is bewust een manuele stap: een prijs die midden op de dag wijzigt voor morgen mag vandaag nog niet op de kassa staan.
- K mag zo vaak genomen worden als men wil.

(09-06-2026, ca. 00:11–00:13; 11-06-2026, ca. 00:36–00:40; 25-06-2026, ca. 00:19)

---

## 8. Verkopen inlezen (stock en statistieken)

**Waar:** Hoofdmenu voorraad > 2 > 3 "Inlezen verkopen van de Icone-kassa".
- Het inlezen werkt **stock en statistieken** bij. Het is geen wettelijke verplichting, maar zonder inlezen zijn er geen kassastatistieken in het pakket (op de kassa zelf kan je maar beperkt terugkijken).
- **Kijk altijd eerst naar de tabel onderaan het scherm**: per kassa "ingelezen tot" en de datum/het uur van het verkoopbestand **op de server** (niet op de kassa).
- Inlezen vanaf de dag na "ingelezen tot" tot en met de **laatste volledige dag**. Is het bestand van vandaag vóór sluitingstijd doorgestuurd, lees dan maar in tot en met gisteren; het pakket waarschuwt als het bestand van vóór ca. 18 uur is.
- Veelgemaakte fout: een halve dag inlezen of een kasverslag van een halve dag nemen.
- Nakijken wat ingelezen is: 2 > "Bekijken ingelezen dagtotalen" (op scherm; groen = eerste dag van de week) of 2 > 5 > 6 (afdruk dagtotalen).

(09-06-2026, ca. 01:48–01:50; 11-06-2026, ca. 01:09–01:11 en 01:18–01:19)

---

## 9. Het verkoopbestand van de kassa (KASLOK) en wissen

> Bestandsnamen in dit hoofdstuk zijn gereconstrueerd uit de transcriptie ("kaslok.dat", "KL + jaar + maand"); te verifiëren in de handleiding.

- De verkopen staan op de kassa in één verkoopbestand (**KASLOK.DAT**), of – bij de instelling "verkoopfile per maand" – in één bestand per maand (**KL + jaartal + maand**).
- Op de server staat de kopie in de Jamadata-kassamap, submap per kassa (bv. `KASSA\KASSA-01`).
- Het ene grote bestand heeft een ingestelde maximumgrootte (bv. 20.000 records). De kassa meldt wanneer het vol is. Doorwerken kan, maar als de kassa uitvalt terwijl het bestand boven zijn grootte zit, kan alles verloren zijn; de kassa wordt ook trager.
- Advies: **elke maand wissen** op de kassa, maar pas nadat (1) de verkopen zijn ingelezen én (2) het kasverslag is afgedrukt/ingeboekt. Het kasverslag leest immers rechtstreeks uit dit bestand (zie 10).
- Bij wissen op de kassa blijft één kopie bewaard (extensie **.001**); die gaat mee naar de server.
- Alternatief: omschakelen naar **verkoopfile per maand**. Dan blijft elke maand bewaard en kan men maanden terug kasverslagen en dagtotalen opvragen (let wel: ook bij een controle is dat zichtbaar; het is een keuze van de klant). Omschakelen gebeurt volgens de handleiding: op de kassa wijzigt de F9 Controle-indeling en in het pakket hoort een parameter mee aangepast te worden (in de opleiding genoemd als "44.0 op 4" – te verifiëren). Enkel doen op vraag van de klant.

### Klant heeft gewist vóór het kasverslag was afgedrukt/ingeboekt
Het pakket kijkt altijd naar het bestand met extensie .DAT. Werkwijze (scherm van de hoofdcomputer overnemen):
1. In de servermap van die kassa: het huidige `KASLOK.DAT` hernoemen (bv. extensie `.JOR`).
2. `KASLOK.001` hernoemen naar `KASLOK.DAT`.
3. De klant drukt het kasverslag af of boekt het in (2 > 4).
4. Daarna de namen terugzetten (`.DAT` → `.001`, tijdelijke naam → `.DAT`).

Hernoemen kan geen kwaad (er wordt niets gewist); bij de volgende transfert van de kassa worden de bestanden toch opnieuw overschreven.

(18-06-2026, ca. 00:01; 23-06-2026, ca. 00:00–00:11)

Diagnosetip: in de interne klantgegevens die Jamadata dagelijks binnenkrijgt, zit een volledige mappenlijst van de klant (`dir.lst`). Daarin zoeken op de bestandsnaam toont datum en grootte zonder de klant te storen. Zie `opleiding-zomer-server-it-en-helpdeskwerkwijze.md`.

---

## 10. Kasverslag afdrukken en inboeken

**Waar:** Hoofdmenu voorraad > 2 > 4 "Afdrukken/inboeken kasverslag" (`?` = uitgebreide handleiding; `+` = boekhoudkundige parameters).

- Het kasverslag is de A4-versie van wat op de kassa op kleine tickets uitkomt, en nog uitgebreider.
- Het leest **rechtstreeks uit het verkoopbestand op de server**; de verkopen hoeven daarvoor niet ingelezen te zijn. Controleer ook hier de tabel met datum/uur van het bestand (geen halve dag nemen).
- Selectie: van datum tot datum; per kassa of per **filiaal** (kassa's kunnen in filialen gegroepeerd worden; bij ca. 95 % van de klanten gewoon geen kassanummer invullen). Optioneel: bedrag dat naar de bank gestort wordt (komt mee op het verslag en in de boeking).
- Inhoud:
  - contante (particuliere) verkopen per btw-tarief + leeggoed;
  - voldane en niet-voldane **facturen** en **bons**, per klant, met betaalwijze (afkortingen zoals GE = geld, NB = niet betaald);
  - diverse uitgaven en inkomsten **met de ingetikte omschrijving** (dus ook de klant-/factuurnummers van punt 2.2);
  - totaal geldbewegingen, storting bank, overzicht van alle betaalmiddelen, afrondingsverschillen, cadeaubons, aantal klanten en gemiddelde.

**Inboeken in de boekhouding** (enkel met boekhoudmodule):
- Boekt in het **kasjournaal** – bij bijna alle klanten **journaal 17**; per kassa/filiaal kan een eigen kasjournaal ingesteld worden. Het volgnummer is vaak de omgekeerde datum.
- Via `+` (parameters) moet **per betaalmiddel een grootboekrekening** ingevuld zijn (eventueel wachtrekeningen). Welke rekeningen: dat bepaalt de boekhouder van de klant.
- Voor elke diverse uitgave/inkomst vraagt het boekingsscherm een tegenrekening: **G** (grootboekrekening), **K** (klant) of **L** (leverancier) + nummer/naam. Een aan de kassa betaalde factuur boek je dus op K + die klant.
- Zonder ingevulde rekeningen geeft het boeken een fout; niet boeken = annuleren.

(11-06-2026, ca. 00:40–00:54 en 01:09)

---

## 11. Lijsten en controles rond de kassa (Hoofdmenu voorraad > 2)

| Punt | Wat | Opmerking |
|---|---|---|
| 5 > 1 | Nog te factureren tickets | bons uit het oude offline systeem (zie 3.4) |
| 5 > (per artikelgroep / per artikel) | Verkopen per groep of artikel over een periode | aankoopwaarde, verkoopwaarde, winst in euro en %, aandeel in totaal; ook lijsten best/slechtst verkochte artikels; selectie op groep/leverancier, F8 = alles |
| 5 > 6 | Dagtotalen | per dag per btw-tarief + leeggoed + aantal klanten; pdf of Excel; **vinkje "bons/facturen meetellen"** verandert de totalen sterk |
| 5 > bestellijst winkel | Lijst verkochte artikels om de winkel bij te vullen | als laadbon (volgens plaats magazijn) of als bestellijst; weinig gebruikt |
| 5 > controlelijst dubbele EAN | barcodes die dubbel voorkomen | duurt lang |
| Bekijken ingelezen dagtotalen | op scherm | zie 8 |
| Tellen van ontvangen geld | hulpscherm om de lade te tellen (aantal per biljet/munt), pdf mogelijk | optioneel |
| Beheer klantenkaarten (punt 9) | klantenkaarten en punten | uitgebreide handleiding achter `?` |
| Verenigingskaarten / omzet per vereniging | klantenkaarten waarbij ook een vereniging punten krijgt (sponsoring naar rato van aankopen van de leden) | handleiding achter `?` |
| C | **Prijscontrole kassaverkopen**: tickets waar de verkoopprijs afwijkt van de artikelfiche | bedoeld voor fraudecontrole (prijs gewijzigd op ticket, veel terugnames). Vergelijkt met de **huidige** prijs: over een lange periode geven promoties en prijswijzigingen ook verschillen. Waarom sommige lijnen in het vet staan is niet gedocumenteerd (te verifiëren bij ontwikkeling). |
| T | **Lijst verkochte artikels in promotie** per leverancier ("enkel verkopen met korting") | met kassa, datum en ticketnummer + totaal dat de leverancier moet terugbetalen; vervangt het bijhouden van dubbele tickets. Handleiding met tips achter `?`. |
| E | Lijst kastickets (pdf/Excel) | per ticket, incl. betaalwijze en communicatiefouten |

Over de inhoud van lijsten komen weinig vragen; de meest gestelde vraag is "kan dat ook in Excel?" (bij steeds meer lijsten staat een Excel-symbool) of "kan er een kolom bij?" (= aanpassing, in overleg met ontwikkeling).

(11-06-2026, ca. 01:11–01:31)

---

## 12. Kassapromoties en de Prik&Tik-folder

- Promoties manueel ingeven: 2 > 1 (aanpassen/bekijken promoties). De handleiding achter het `?` is zeer volledig (met schermafdrukken) en is verplichte lectuur: over promoties komen veel vragen. (11-06-2026, ca. 00:26; 18-06-2026, ca. 00:04)
- **Mixpromoties** komen veel voor (bv. "tweede bak aan 40 %" of "11+1" waarbij verschillende smaken gemengd mogen worden): meerdere artikels worden aan dezelfde promotie gekoppeld.

### Folder van Prik&Tik verwerken
Prik&Tik levert de folderpromoties als bestand aan; Jamadata zet dat om en zet het centraal klaar voor alle Prik&Tik-leden.
1. 2 > onderste punt (koppeling Prik&Tik-folder; is hetzelfde als 2 > 1 > 5 "folderbestanden"): lijst van folders met looptijd. "Verwerk de promoties van deze leverancier", F8.
2. De lijst toont de artikels uit de folder en de promotie. **Wit = al gekoppeld/verwerkt.**
3. **Artikel koppelen** (eenmalig per artikel; de koppeling blijft voor volgende folders): het folderartikel koppelen aan het eigen artikel. Verschilt de verpakkingseenheid (leverancier per 24, klant per stuk of omgekeerd), dan vraagt het pakket naar het "afwijkend aantal in de verpakking bij de leverancier". Is het artikel al aan iets anders gekoppeld, dan komt daar een melding van.
4. **Promotie verwerken**: de promotie wordt voorgesteld (bv. −1 euro bij aankoop van 1 fles); kiezen of ze op de bak of op de fles geldt; van/tot-datum is ingevuld; F8.
5. Bij "X+1 gratis": het **totaal aantal** dat gekocht moet worden ingeven (11+1 → 12).
6. Mixpromo: de andere artikels aan dezelfde promotie koppelen. Dit geeft een foutmelding als op zo'n artikel **al een andere promotie loopt**; koppelen kan pas als er geen lopende promotie op zit.
7. Is de hele lijn wit, dan is het artikel gekoppeld én zit de promotie erin. Daarna 2 > K en gegevens ophalen op de kassa.

De koppeling met een afwijkende hoeveelheid is ook van belang voor bestellingen bij de leverancier (anders wordt te veel of te weinig besteld). Het omgekeerde geval (leverancier verkoopt per stuk, klant per bak) is zeldzaam en de juiste invulling is niet uitgeklaard (te verifiëren). (11-06-2026, ca. 01:31–01:43)

### Fout in promotie/btw op tickets onderzoeken
Is een probleem niet eenvoudig na te bootsen (bv. korting die bij 0 % btw terechtkomt in de dagtotalen), haal dan de gegevens en het verkoopbestand van de kassa van de klant op, beperk je tot **één dag waarop de fout voorkomt**, zet alle tickets van die dag in één pdf en zoek daarin het ticket. Dat is meestal sneller dan in de demo promoties proberen na te bouwen. (18-06-2026, ca. 00:04–00:06)

---

## 13. Hardware en Windows op de kassa

- **Klantendisplay** hoort standaard bij de kassa. Een los display (op een andere plaats) moet op een eigen COM-poort; de nieuwere kassa's hebben maar twee COM-poorten (bezet door Bancontact en ticketprinter). De ticketprinter moet dan via USB of netwerk aangesloten worden, met aanpassing van de instellingen (BIOS/printer). Er bestaat een interne handleiding; reken op meerwerk. (09-06-2026, ca. 01:06)
- **Taakbalk flikkert / kassa start niet meer op** (explorer.exe crasht): Windows zelf is defect. Noodoplossing: via Taakbeheer > "Nieuwe taak uitvoeren" de nodige programma's starten (hulp-op-afstand-programma, kassa), zodat de klant kan voortwerken. De kassa's draaien Windows 10 IoT zonder installatiebestanden, waardoor een herstel via Windows-tools niet lukt. Definitieve oplossing: nieuwe schijf met Windows (via de hardwareleverancier) of terugzetten vanaf de **herstel-USB-stick** die bij elke kassa geleverd wordt (volledige kopie van Windows), en daarna de map `KASSA` terugzetten uit de laatste kopie. Zorg dus dat er een recente kopie van de kassa is vóór de schijf vervangen wordt. (30-06-2026, ca. 00:22–00:31)
- Type schijf verschilt per kassamodel: oudere modellen hebben een SSD achter een klepje aan de zijkant (eenvoudig te wisselen), nieuwere een M.2-kaartje op het moederbord. Intern wordt per klant bijgehouden welk kassatype er staat en wanneer het geïnstalleerd is. De garantie bij de hardwareleverancier telt vanaf de aankoop door Jamadata, niet vanaf de installatie bij de klant. (30-06-2026, ca. 00:26–00:30)
- **Bancontact-koppeling**: bij een wissel van betaalprovider/protocol moet eerst de leverancier van de terminal die installeren en activeren; pas daarna kan Jamadata de koppeling met de kassa omzetten. (04-08-2026, ca. 00:00–00:05)

---

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):
- Kennisoverdracht Jamadata-20260609_100321-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260611_100339-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260618_101035-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260623_100457-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260625_102119-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260630_102207-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260709_150648-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260804_152719-Opname van vergadering.txt
