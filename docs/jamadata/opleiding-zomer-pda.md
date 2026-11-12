# PDA (nieuwe Android-PDA): praktijkkennis uit de opleiding van juli 2026

Gebruik dit document voor: helpdeskvragen over de bediening van de nieuwe Jamadata-PDA (stock tellen, bestellingen, barcodes toevoegen, kassaverkoop, leeggoed), de verwerking van PDA-gegevens in Jamadrink en op de kassa, de instellingen van de PDA en gekende beperkingen/bugs.

> **Let op – bron is gesproken opleiding.** Deze inhoud komt uit een automatisch getranscribeerde (Whisper) demo van de PDA. Knopnamen en menupunten zijn zo goed mogelijk gereconstrueerd en kunnen afwijken van wat letterlijk op het scherm staat. Controleer bij twijfel tegen de PDA-handleidingen (map PDA) en de help (`?`) bij het menupunt in het pakket.

Alle kennispunten komen uit de opleiding van 09-07-2026 (tijdstip telkens vermeld), tenzij anders aangegeven.

---

## 1. Overzicht

| Knop op de PDA | Soort | Verwerking |
|---|---|---|
| Stock | basis (op elke PDA) | Jamadrink: jaarinventaris |
| Bestelling | basis | Jamadrink: bestelling aan leverancier |
| Barcodes | basis | Jamadrink: barcodes op artikelfiche |
| Kassaverkoop | bij te kopen module | kassa: PDA-bon opladen |
| Leeggoed | bij te kopen module | kassa: leeggoedticket scannen |
| Sync | synchroniseren (aparte knoppen per soort) | – |
| Wissen | opnames op de PDA wissen | – |

De PDA werkt via wifi rechtstreeks met de server (hoofdcomputer) en, voor kassaverkoop en leeggoed, met de kassa. Niet alles wat op de oude PDA bestond is al op de nieuwe ontwikkeld (bv. tonen van prijzen bij productinfo). (ca. 00:42–00:43, 01:04)

---

## 2. Artikels ingeven: overal dezelfde werkwijze

In Stock, Bestelling, Kassaverkoop en Leeggoed kies je een artikel op drie manieren:
1. **Scannen** met de ingebouwde scanner.
2. **Vergrootglas**: zoeken op naam. Nieuw t.o.v. de oude PDA: er wordt ook op een **deel van de tekst** gezocht. Dubbeltikken op het artikel.
3. **Blokjes**: dezelfde blokjes als op de kassa. Het scherm is kleiner dan de kassa; met de pijltjes of door te vegen ga je naar rechts/onder. Blokjes verplaatsen kan niet op de PDA.

Daarna de aantallen invullen en bevestigen met het **vinkje** rechtsonder:
- **Paletten** – het veld verschijnt enkel als op de artikelfiche "aantal per palet" is ingevuld;
- **Bakken** (standaardeenheid);
- **Stuks**.

In de lijst staat achter het aantal: **P** = palet, **S** = stuk, **niets** = bak (ook bij artikels die per fles verkocht worden, bv. wijn, staat er dan niets).

- Hetzelfde artikel opnieuw ingeven **telt bij** (cumuleert); handig als een artikel op meerdere plaatsen staat.
- **Vuilbak**: lijn aanduiden en wissen (zonder bevestigingsvraag).
- **Pijl naar links**: een scherm terug; de laatst ingegeven lijn staat bovenaan.
- Het barcode-icoon linksonder schakelt naar scannen met de **camera**; dat werkt, maar veel trager dan de ingebouwde scanner.
- Scannen op het **hoofdscherm** toont productinfo (huidige stock; prijzen worden op de nieuwe PDA nog niet getoond). (ca. 01:23)

(ca. 00:44–00:51)

---

## 3. Stock tellen

1. PDA: **Stock** > artikels ingeven (zie 2).
2. PDA: **Sync** > "stock toevoegen aan bestand" (stuurt de telling naar de server). Daarna is de stock op de PDA automatisch leeg.
3. Jamadrink: Hoofdmenu voorraad > **A** (periodieke werkzaamheden) > **2** (jaarinventaris) > **3** "inlezen van de aantallen geteld met de PDA". Met **F9** zie je wat er binnengekomen is, per PDA-naam; paletten zijn omgerekend naar bakken.
4. De verdere verwerking is de gewone inventarisprocedure (zie de help bij dat menupunt).

Geef elke PDA een eigen naam (zie 8): zo is zichtbaar welke PDA wat geteld heeft. (ca. 00:51–00:52, 01:15)

---

## 4. Bestelling aan leverancier

1. PDA: **Bestelling** > artikels en aantallen ingeven (paletten, losse bakken, eventueel stuks).
2. PDA: **Sync** > bestelling verzenden.
3. Jamadrink: Hoofdmenu voorraad > **1** (bestellingen aan leveranciers) > inbrengen van een nieuwe bestelbon (punt 1; punt 3 start vanuit een lijst van leveranciers met PDA-opnames) > leverancier kiezen, F8 > onderaan **+** > **"opnames van PDA"** > periode (bv. alles van vandaag) > "lees opnames van deze leverancier". De lijnen komen in de bestelbon met omgerekende aantallen.
4. F8 om af te werken: doorsturen (bv. naar Prik&Tik), pdf of mail.

De bestelling **blijft op de PDA staan** na het verzenden. Wissen: knop **Wissen** > bestelling > bevestigen. (Stock wordt wél automatisch gewist bij het doorsturen.) (ca. 00:52–00:57, 01:12–01:13, 01:22)

---

## 5. Barcodes toevoegen met de PDA

1. PDA: **Barcodes** > onbekende barcode scannen. De PDA vraagt aan welk artikel de barcode toegevoegd moet worden.
2. Artikel opzoeken en **dubbeltikken**. Controleer goed dat het het juiste artikel is: een foute koppeling zit daarna overal fout (pakket, kassa, PDA).
3. Onderaan kiezen of de barcode voor het **stuk** of de **bak** geldt. Standaard staat **stuk** (de meeste barcodes zijn van een stuk).
4. Vinkje.
5. PDA: **Sync** > barcodes verzenden.
6. Jamadrink: Hoofdmenu voorraad > **A** > **M** "beheer stock/controle/barcodes d.m.v. mobiele scanners" > **2** "verwerken barcodes van mobiel apparaat op artikelfiche" (handleiding achter `?`). Het bestand staat al ingevuld; **F4** = begin inlezen; bevestigen dat de barcodes op de artikelfiche ingevuld mogen worden. Het pakket meldt het aantal goed en niet verwerkte artikels.
7. Controle: Hoofdmenu voorraad > 9 > 3 (artikels) > artikel > **F9 vervolg**: de barcode staat erbij.
8. Naar de kassa: Hoofdmenu voorraad > 2 > **K** (klaarzetten) en op de kassa na Stoppen de gegevens ophalen.

- De nieuwe PDA kan een pas toegevoegde barcode **meteen** gebruiken (bv. in Stock); op de oude PDA kon dat pas na een nieuwe synchronisatie.
- **Wissen > barcodes** op de PDA wist enkel de lijst met toegevoegde barcodes op de PDA, niets in het pakket.

(ca. 00:58–01:04, 01:24–01:25)

---

## 6. Kassaverkoop (klanten vooraf scannen in de rij)

Bedoeld voor klanten met veel producten: een medewerker scant de kar met de PDA, aan de kassa moet enkel nog betaald worden. Afrekenen op de PDA zelf kan niet (geen lade, geen Bancontact).

1. PDA: **Kassaverkoop** > een **nummerkaartje** scannen (kaartje met barcode = bonnummer) of het nummer intikken. Het kaartje gaat mee met de klant.
2. Artikels scannen/kiezen met aantallen.
3. Leeggoed dat de klant terugbrengt kan meteen mee: knop **leeggoed** (tweede van links) > leeggoedsoort > aantal; het wordt in mindering gebracht.
4. Pijl naar links > "kassaverkoop verzenden aan de kassa?" > **Yes**. De PDA meldt dat de kassaverkoop is opgeslagen.
5. Kassa: het kaartje scannen, of Diverse > **PDA-bons** > het nummer kiezen > **Oplaad bon**. De artikels staan in het ticket; overlopen met de klant en afrekenen via Einde.
6. Na het afrekenen is het nummer weer vrij en kan het kaartje opnieuw gebruikt worden.

(ca. 00:16–00:18, 01:04–01:09)

---

## 7. Leeggoed terugnemen met de PDA

Goedkoop alternatief voor een leeggoedautomaat.
1. PDA: **Leeggoed**. Op het scherm staan blokjes met de meest voorkomende leeggoedwaarden; je kan ook gewoon een **product scannen**, dan stelt de PDA het bijhorende leeggoed (bak en fles) voor.
2. Aantal **bakken** en **losse flessen** ingeven. Ontbreken er flessen in een bak: het aantal stuks **negatief** ingeven (bv. 6 bakken en −2 stuks). Vinkje.
3. Het lijst-icoon (helemaal rechts) toont wat er al opgenomen is, met de waarden.
4. **Printer-icoon**: drukt een ticket met barcode af voor de klant.
5. Kassa: het ticket scannen **vóór het ticket afgesloten wordt** (begin, midden of einde maakt technisch niet uit; het leeggoed komt in het ticket op de plaats waar gescand wordt – best bij het begin of het einde, niet middenin). Zonder scanner: Diverse > PDA-bons > Oplaad bon.

(ca. 00:16, 01:10–01:12; kassa-zijde: opleiding 09-06-2026, ca. 00:43–00:46)

---

## 8. Sync, Wissen en instellingen

### Sync
Er zijn aparte knoppen per soort (producten laden, stock toevoegen aan bestand, bestelling verzenden, barcodes verzenden, …) en één knop **alles verzenden/ontvangen**. De aparte knoppen bestaan omdat "alles" lang duurt, zeker de eerste keer op een nieuwe PDA; wie enkel stock wil doorsturen, gebruikt beter de aparte knop. "Producten laden" haalt artikels, blokjes enz. van de server. (ca. 00:16, 01:13–01:14)

### Instellingen (tandwiel)
- **Serverinstellingen**: IP-adres van de server, **poort 60000**, en de **PDA-naam**. Geef elke PDA een andere naam/nummer (PDA 1, PDA 2, …).
- **Kassa-instellingen**: IP-adres van de kassa en het procesnummer (in de demo 1001).
- **Leeggoedblokjes**: per blokje een naam, de **artikelcode van het leeggoed**, de benaming voor bak en stuk en de waarde. Er zijn 4 pagina's blokjes (de oude PDA had er meer).

(ca. 01:14–01:16)

### Menu (drie puntjes)
- **Update application**: haalt de nieuwste versie van de PDA-app op bij Jamadata.
- **Settings**: o.a. het adres vanwaar de update gehaald wordt.

(ca. 01:17–01:20)

### Overnemen op afstand
Op de PDA staat een hulp-op-afstand-app (TeamViewer QuickSupport); daarmee kan de helpdesk het scherm van de PDA zien en bedienen. Het helpt om bij PDA-vragen zelf een toestel bij de hand te hebben. (ca. 00:42, 01:25–01:26)

---

## 9. Gekende problemen en beperkingen

| Symptoom | Uitleg / oplossing | Bron |
|---|---|---|
| Aangepast leeggoedblokje wordt niet getoond in Leeggoed | Gekende bug: de wijziging wordt soms pas zichtbaar nadat de app volledig gesloten en opnieuw gestart is (soms meerdere keren proberen). | ca. 01:16–01:17 |
| "Update application" lukt niet | In de demo lukte de update niet zolang de PDA op hetzelfde (interne) netwerk zat als de updateserver, en wel via een mobiel netwerk/hotspot. Bij een klant dus eerst een andere internetverbinding proberen. Te verifiëren of dit ook buiten het kantoornetwerk speelt. | ca. 01:18–01:21 |
| Barcode wordt niet gevonden op de PDA | De barcode zit niet in het artikelbestand (bv. enkel lokaal op de kassa toegevoegd). Toevoegen via Barcodes (hoofdstuk 5) of via het pakket, daarna producten laden. | ca. 00:45, 00:58 |
| Geen geluid bij scannen | In de demo gaf de PDA geen scangeluid; het resultaat moet op het scherm gecontroleerd worden. | ca. 01:23 |
| Prijs wordt niet getoond bij productinfo | Nog niet ontwikkeld op de nieuwe PDA (bestond op de oude). | ca. 01:24 |
| Camera-scan is traag | Gebruik de ingebouwde scanner. | ca. 00:49–00:50 |
| Bestelling staat er na verzenden nog | Normaal: bestellingen worden niet automatisch gewist; gebruik Wissen. | ca. 01:12 |

---

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):
- Kennisoverdracht Jamadata-20260709_150648-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260609_100321-Opname van vergadering.txt (PDA-bons op de kassa)
