# Exportmodules brouwers en leveranciers: Haacht, AB InBev, Alken-Maes, Moët-Hennessy, Suntory

Gebruik dit document voor: vragen over het maandelijks doorgeven van verkoop- of omzetcijfers vanuit Jamadrink aan Haacht, AB InBev (KPMG), Alken-Maes, Moët-Hennessy en Suntory: waar de module staat, welke instellingen en klant-/artikelselecties nodig zijn, hoe het bestand aangemaakt en verstuurd wordt, en waarom klanten of artikels ontbreken. Voor Coca-Cola zie `modules-coca-cola.md`; voor Prik&Tik en Districo zie `modules-prik-en-tik-districo.md`.

## 1. Gemeenschappelijke principes

- Alle modules staan onder menu **V.4**; onderaan dat scherm staat per leverancier een icoon (Moët-Hennessy: menupunt **V.4.M**).
- De cijfers komen uit de uitgebreide statistieken/historieken (Suntory: de verkoopshistorieken) en zijn dus **per maand** beschikbaar.
- Artikels worden niet één voor één gekoppeld. De module neemt alle artikels waarvan op de artikelfiche de ingestelde **leverancier** of **merk/producent** staat. In de instellingen van elke module geef je aan welk van beide velden gebruikt wordt en welke naam.
- Vaste toetsen op het beginscherm van de meeste modules:
  - **F2 controlelijst artikels**: lijst van alle artikels van de ingestelde leverancier/producent. Ontbreekt een product, dan staat de leverancier/producent niet (juist) op de artikelfiche.
  - **F3 controlelijst klanten**: PDF-lijst van de klanten die doorgegeven worden.
  - **F9 instellen verplichte klanten**: klanten toelaten of blokkeren (Haacht: **F10** in het instellingenscherm).
- Kleuren in het klantenscherm: **rood** = omzet wordt niet doorgegeven. De betekenis van wit/groen verschilt per module (zie hieronder).

### Overzicht

| Module | Uitvoerformaat | Verzending | Periode | Klanten standaard |
|---|---|---|---|---|
| Haacht (versie 2023) | Excel ter controle; aantal liter per klant per product | Mail-knop in de module (naar het ingestelde adres) | Eén maand (mm/JJJJ) | In te stellen via F10 |
| AB InBev (versie 2021) | CSV-omzetbestand | Zelf uploaden op de site van AB InBev/KPMG | Januari t.e.m. de ingegeven maand (cumulatief) | Alle klanten AAN |
| Alken-Maes | Excel | Enveloppe-icoon in de module | Maand + jaar | Alle klanten AAN |
| Moët-Hennessy | Excel ter controle; XML bij verzending | Enveloppe-icoon in de module | Maand + jaar | Geen klantselectie beschreven |
| Suntory | Excel ter controle; CSV als mailbijlage | Mail-icoon in de module | Maanden van-tot + jaar | Zie paragraaf 6 |

## 2. Haacht module (versie 2023)

### Waar
**V.4**, onderaan het Haacht-icoon.

### Instellingen
Druk rechtsonder op de instellingen-knop. Vul in:

| Veld | Inhoud |
|---|---|
| Emailadres Haacht | Het ristorno-mailadres van Haacht (staat in de handleiding 2391A; zie interne bron) |
| Klantnummer | Het klantnummer van de drankenhandel bij Haacht |
| Leverancier Haacht-producten: Leverancier of merk/producent | In welk veld van de artikelfiche de naam van Haacht staat |
| Leverancier Haacht-producten: Naam | De naam van Haacht zoals op de artikelfiches |
| FTP-gegevens | De gegevens die de drankenhandel van Haacht krijgt (niet in deze documentatie opgenomen) |

**F10 Instellen klanten van Haacht**: hier worden klanten geblokkeerd of toegelaten.

### Controleren in Excel
1. Geef de gewenste maand in als **mm/JJJJ**.
2. Druk op de Excel-knop rechtsonder. De klanten lopen over het scherm; daarna opent de Excel.
3. Rijen = klanten, kolommen = Haacht-producten, waarden = **aantal liter** per klant.

### Doorsturen
1. Geef de maand in (mm/JJJJ).
2. Druk op de mail-knop naast de periode. De klanten lopen over het scherm en de gegevens worden verzonden.

### Aandachtspunt: liters
De doorgegeven liters zijn berekend uit de **inhoud** die op de artikelfiches is ingevuld. Foute of ontbrekende inhoud geeft foute liters. Controleren en corrigeren kan via menupunt **V.3.I** (controle inhoud en aantal per bak op artikelfiches; die handleiding valt buiten dit document).

### Oudere versies
Er bestaan nog handleidingen "Haacht module", "_old" en "_voor2023". Die zijn vervangen door versie 2023 en zijn hier niet uitgewerkt. Bij een installatie waar het scherm afwijkt van bovenstaande beschrijving: eerst nagaan of de klant de versie 2023 heeft.

## 3. AB InBev module (versie 2021)

### Waar
**V.4**, onderaan het AB InBev-icoon. Scherm: "Exporteren verkochte aantallen voor AB Inbev".

### Parameters (eerste gebruik)
- Welke **leverancier of producent** gebruikt wordt voor de AB InBev-producten.
- Het **klantennummer** van de drankenhandel bij AB InBev.

### Stap 1 - Klanten
- Standaard worden **alle** klanten doorgegeven; voor nieuwe klanten staat de export standaard AAN. De drankenhandel duidt zelf aan welke klanten niet doorgegeven mogen worden.
- **F9 instellen verplichte klanten** > selectie ingeven > **F8 zoek**.
- Links op het groene icoon = doorgeven (lijn **groen**). Rechts op het verbodsicoon = niet doorgeven (lijn **rood**).
- Het groene of rode icoon **rechtsonder** past de keuze toe op **alle klanten op dat scherm**.
- **F1 stop** als klaar. **F3 controlelijst klanten** geeft een PDF.

### Stap 2 - Artikels
**F2 controlelijst artikels**: controleer of alle AB InBev-producten op de lijst staan.

### Stap 3 - Uitschrijven in CSV
- Geef maand en jaar in. Let op: de aantallen/volumes zijn steeds het **totaal van januari t.e.m. de ingegeven maand**, niet enkel die maand.
- **Uitschrijven op leveringsadres**: standaard aangevinkt; de gegevens worden dan per leveringsadres uitgeschreven.
- Druk op het export-icoon. Het omzetbestand komt in **Mijn Documenten > Jamadata > Diversen** en die map opent automatisch.

### Stap 4 - Versturen
Het bestand wordt niet door Jamadrink verstuurd. De drankenhandel uploadt het zelf op de site van **AB InBev/KPMG**.

## 4. Alken-Maes module

### Waar
**V.4**, onderaan het Alken-Maes-icoon. Scherm: "Exporteren verkochte aantallen voor Alken-Maes".

### Stappen
1. **Klanten**: standaard worden alle klanten doorgegeven (nieuwe klanten staan standaard AAN). Via **F9 instellen verplichte klanten** > **F8 zoek op**: groen icoon links = doorgeven (lijn groen), verbodsicoon rechts = niet doorgeven (lijn rood). Het groene/rode icoon rechtsonder geldt voor alle klanten op het scherm. **F1 stop**. Controle met **F3 controlelijst klanten** (PDF).
2. **Artikels**: **F2 controlelijst artikels**.
3. **Excel**: geef maand en jaar in en druk op het **XLS-icoon**. Controleer de Excel.
4. **Doorsturen**: geef maand en jaar in en druk op het **enveloppe-icoon**. De Excel wordt aangemaakt en doorgestuurd naar Alken-Maes.

## 5. Moët-Hennessy module

### Waar
Menupunt **V.4.M**.

### Stappen
1. **Artikels**: **F2 controlelijst artikels** toont de artikels van de ingestelde leverancier/producent Moët-Hennessy.
2. **Excel**: geef maand en jaar in en druk op het **XLS-icoon**; controleer de inhoud.
3. **Doorsturen**: geef maand en jaar in en druk op het **enveloppe-icoon**. Er wordt een **XML-bestand** aangemaakt en doorgestuurd.

Opmerking: de handleiding vermeldt bij stap 3 letterlijk "doorgestuurd naar Alken-Maes". Dat is vrijwel zeker een kopieerfout in de bron; bedoeld is Moët-Hennessy (te verifiëren). De handleiding beschrijft geen klantselectie voor deze module.

## 6. Suntory exportmodule

### Waar
**V.4**, onderaan het Suntory-icoon. Scherm: "Exporteren verkochte aantallen voor Suntory". De instellingen zitten achter het **tandwieltje**.

Er bestaan twee versies van de handleiding die een verschillend instellingenmenu tonen. Welke op een installatie van toepassing is, hangt af van de programmaversie; de bronnen zeggen niet welke de recentste is (zie "Onzeker" onderaan). Beide worden hier beschreven.

### Instellingen exportmodule (beide versies)
| Instelling | Uitleg |
|---|---|
| Klantnummer Suntory | Staat op de laatste factuur van Suntory |
| Leverancier of producent | Hoe Suntory ingesteld staat. Tip: roep een artikel op en kijk in welk veld Suntory is ingevuld |
| Leveranciersnaam | Deel van de naam typen en zoeken met de **Tab-toets** of het ververs-knopje, of het codenummer invullen; Jamadata vult de naam aan |
| E-mailadres | Het adres dat de drankenhandel van Suntory ontving; daarheen worden de gegevens gestuurd |
| Groepstotalen meesturen (ja/nee) | Standaard **ja** |

### Artikelgroepen selecteren
Selecteer alle artikelgroepen waarin producten zitten die **gelijkaardig** zijn aan die van Suntory (softdrinks e.d.). Andere groepen niet aanvinken. Deze groepen dienen voor de groepstotalen/marktanalyse.
- Variant A: onderaan het instellingenscherm via **F9 - Selecteer artikelgroepen**.
- Variant B: punt **1** "Artikelgroepen instellen voor marktanalyse" in het tandwielmenu.

### Klanten selecteren
- Variant A: **F9 instellen verplichte klanten** > selectie > **F8 zoek**.
- Variant B: punt **5** in het tandwielmenu. Standaard worden alle klanten doorgegeven als "gewone" klant.
- Per klant (beide varianten):
  - groen icoon links = omzet doorgeven als gewone klant, lijn **wit**;
  - Suntory-icoon = omzet doorgeven als **verplichte klant**, lijn **groen**;
  - verbodsicoon rechts = omzet niet doorgeven, lijn **rood**.
- **F1 stop** als klaar.

### Enkel in variant B: "Custom Total SOFT" (marktanalyse per artikel)
Van bepaalde artikels uit de geselecteerde groepen moet een totaal doorgegeven worden als "Custom Total SOFT". Suntory bepaalt zelf welke artikels dat zijn:
1. **Punt 2 - Mailen softdrinks-artikels naar Suntory**: schrijft een Excel uit met alle artikels van de geselecteerde groepen en mailt die naar Suntory. Suntory vinkt de gewenste artikels aan en stuurt het bestand terug.
2. **Punt 3 - Inlezen XLS met gemarkeerde artikels van Suntory**: sla het teruggekregen bestand eerst op in de map `\Jamadata\share` of `\JamaShare`. Neem punt 3 en geef de bestandsnaam in; de juiste naam staat standaard al ingevuld zolang de originele naam niet gewijzigd is. De markeringen worden op de artikelfiches gezet.
3. **Punt 4 - Manueel markeren van artikels voor marktanalyse**: nakijken welke artikels aangevinkt zijn en zelf aan- of afvinken.
4. **Punt +** - Instellingen exportmodule (zie tabel hierboven).

### Controlelijsten
Op het eerste scherm: **F3 controlelijst klanten** (PDF) en **F2 controlelijst artikels**.

### Uitschrijven in Excel (controle)
Vul de periode in maanden in (bv. 1 - 12) en eventueel het jaar. Druk op het Excel-icoon; de spreadsheet wordt aangemaakt en getoond. Dit dient om na te kijken wat doorgegeven zal worden.

### Mailen naar Suntory
Is de Excel in orde, druk dan op het grote mail-icoon. Er wordt een mail aangemaakt met als bijlage een **CSV-bestand** met dezelfde gegevens als de Excel. Verstuur de mail.

## 7. Gekende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Product ontbreekt in de export | Op de artikelfiche staat de ingestelde leverancier/producent niet, of in de instellingen is het verkeerde veld (leverancier i.p.v. merk/producent) of een andere naam gekozen. Controleer met F2 |
| Klant ontbreekt | Klant staat op rood in het klantenscherm (F9; Haacht F10; Suntory variant B punt 5). Controleer met F3 |
| Klant wordt doorgegeven terwijl dat niet mag | AB InBev, Alken-Maes en Suntory geven standaard alle (ook nieuwe) klanten door; zet de klant op rood |
| Haacht: liters kloppen niet | Inhoud op de artikelfiche is fout of leeg; corrigeer via V.3.I |
| AB InBev: cijfers veel hoger dan de maandomzet | Normaal: het bestand bevat het cumulatief van januari t.e.m. de gekozen maand |
| AB InBev: waar staat het bestand? | Mijn Documenten > Jamadata > Diversen. Het moet manueel geüpload worden bij AB InBev/KPMG |
| Suntory: XLS met markeringen wordt niet gevonden | Bestand staat niet in `\Jamadata\share` of `\JamaShare`, of de bestandsnaam is gewijzigd |
| Suntory: mail gaat naar het verkeerde adres | E-mailadres in de instellingen (tandwieltje) aanpassen |
| Mail of verzending start niet | Valt buiten deze handleidingen; controleer de algemene mailinstellingen van Jamadata |
| Cijfers van de lopende maand zijn onvolledig | De modules steunen op maandstatistieken/historieken |

## 8. Onzeker / te verifiëren
- **Suntory**: `2398A - Suntory export-module NEW NEW.docx` en `Suntory export-module.pdf` (Jamadrink-map) beschrijven variant A (instellingen + F9 artikelgroepen + F9 verplichte klanten). `2398A - Suntory export-module.docx` beschrijft variant B (tandwielmenu met punten 1 t/m 5 en +, inclusief "Custom Total SOFT"). De bestandsnaam suggereert dat "NEW NEW" de recentste is, maar variant B is inhoudelijk uitgebreider. Welke versie een klant heeft, moet op het scherm van de klant nagekeken worden.
- **Moët-Hennessy**: bestemming van de verzending staat in de bron foutief als "Alken-Maes".
- **Haacht**: de handleiding vermeldt zowel een mailadres als FTP-gegevens; welke van de twee de mail-knop effectief gebruikt, staat niet in de bron.

## Bronnen
- `2391A - Haacht module versie 2023.docx` (Jamadrink/Handleidingen modules)
- `2393A - AB Inbev module (versie 2021).docx` (Jamadrink/Handleidingen modules)
- `2395A - Alken-Maes module .docx` (Jamadrink/Handleidingen modules)
- `2396A - Moet-Hennessy module.docx` (Jamadrink/Handleidingen modules)
- `2398A - Suntory export-module NEW NEW.docx` (Jamadrink/Handleidingen modules)
- `2398A - Suntory export-module.docx` (Jamadrink/Handleidingen modules)
- `Suntory export-module.pdf` (Jamadrink)
