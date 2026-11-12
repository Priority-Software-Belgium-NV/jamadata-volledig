# Kassa – Klantenkaarten, Freedelity, cadeaubons en tegoedbons

Gebruik dit document voor: vragen over het Jamadata-klantenkaartsysteem (punten sparen op de Key-Conen kassa, beheer onder V.2.9, puntenberekening, uitkeren van punten, klantenkaart voor verenigingen), de technische installatie van de klantenkaartenmodule op de kassa's (oud systeem en via JMD), de Freedelity-koppeling (klantenkaart Prik&Tik), het verkopen en ontvangen van eigen cadeaubons en het afdrukken/verwerken van tegoedbons.

## 1. Klantenkaarten – werking voor de gebruiker

### 1.1 Principe

- Er wordt een **apart klantenkaartenbestand** aangelegd (particuliere klanten). Er is **geen** koppeling met het gewone (facturatie)klantenbestand.
- De klant krijgt een kaart/badge met een unieke barcode die verwijst naar een fiche met persoonsgegevens en puntensaldo.
- De kaart wordt voor of tijdens de verkoop gescand op de kassa; de kassa verwerkt de punten.
- Het tegoed wordt uitgedrukt in **punten: 1 punt = 0,01 EUR**. Punten geven recht op promotiemateriaal (glazen, gadgets, …) of worden als korting verrekend bij een volgende aankoop.
- Punten worden berekend als een **percentage van het bedrag** of als een **vast aantal per bak**.
- Het totaal van de punten wordt steeds **afgekapt** (niet afgerond).

### 1.2 Beheer in Jamadrink – menu V.2.9

Bij de eerste start van dit programma worden **alle** klantenkaarten aangemaakt als "lege" kaarten: fiches met naam `XYZnnnnn` (nnnnn = kaartnummer). Voor een nieuwe klant **pas je dus een lege fiche aan** (niet toevoegen zoals bij facturatieklanten).

| Punt | Functie |
|---|---|
| V.2.9.1 | Aanpassen/bekijken klantenkaarten: kaartnummer of naam ingeven en de fiche aanpassen |
| V.2.9.2 | Afdrukken lijst klantenkaarten |
| V.2.9.3 | Afdrukken invulformulieren (halve A4 waarop de klant zijn gegevens invult; je geeft meteen de overeenkomstige kaart mee – op de kaart staan geen naamgegevens) |
| V.2.9.4 | Afdrukken klantenkaarten (kaartjes met unieke barcode en kaartnummer; knippen en eventueel plastificeren) |
| V.2.9.5 | Afdrukken lijst kaarten per groepering (leden van een vereniging) |
| V.2.9.6 | Afdrukken omzet/korting per groepering |
| V.2.9.7 | Afdrukken historieken/statistieken klantenkaarten (volgens handleiding 0294A). Volgens handleiding 0294B is V.2.9.7 "Wissen groepsomzet leden van vereniging" – de nummering verschilt tussen beide handleidingen: te verifiëren in het menu van de klant |
| V.2.9.E | Uitschrijven klantenkaarten naar Excel (adressenbestand voor mailing) |
| V.2.9.S | Schrappen van 1 klantenkaart |
| V.2.9.W | Wissen van verouderde verkopen/klantenkaarten (klanten die lang niet meer kochten schrappen; de vrijgekomen nummers zijn herbruikbaar) |
| V.2.9.+ | Aanpassen kaartparameters: 2 teksten die op de kaart gedrukt worden + het **identificatienummer** |

Velden op de fiche: kaartnummer, naam, adres, gemeente, telefoon, e-mailadres (mailings), promo-mailing (selectie voor mailing), geboortedatum en geslacht, klant vanaf, totaal aankopen, **kaartnummer groepering** (vereniging), datum/punten/bedrag van de laatste 10 aankopen.

- `+` achter het kaartnummer: scherm met tot 10 **koppelingen**, o.a. om de kaart te koppelen aan één of meer identiteitskaarten. Door de eID in te lezen op de kassa wordt dan de juiste kaart opgeroepen.
- Groene `+` rechtsonder: totale aankopen per artikelgroep.

Het **identificatienummer** (meestal de eerste 5 cijfers van het btw-nummer) mag **niet** meer gewijzigd worden: het is ook zo geprogrammeerd in de kassa (kassys.dat positie 3648) en zit in de barcode van de kaarten.

### 1.3 Op de kassa

- Voor of tijdens het ingeven van de producten de kaart scannen, of manueel via de knop **KLT-KRT** de klant zoeken op naam of nummer.
- De punten voor dit ticket worden berekend en bij het saldo geteld. Op het kasticket staat de klantenkaart, het restant aan punten en een barcode die de volgende keer gescand kan worden in plaats van de kaart.
- Is de kaart **vol** (aantal punten bepaal je in de kassaparameters), dan wordt een speciaal ticket afgedrukt.
- **Puntentotaal** (menu Diversen, bij leeg ticket): drukt het puntentotaal van de laatst gekozen klant af.

### 1.4 Hoeveel punten? (bepaling)

**Op de hoofdcomputer – algemene regel**: parameters onder **V.2.+ "Bepaling promotie-punten per artikel"**:

```
BAK  : type (P,%,G) :   waarde :
STUK : type (P,%,G) :   waarde :
Afronding punten tot op :
```

- Type **P**: waarde = aantal punten per bak (prijs 13,57, waarde 1,00 → 1 punt).
- Type **%**: waarde = puntenpercentage (prijs 13,57, waarde 100,00 → 13 punten).
- Type **G**: geen punten.
- Is bij type P of % het aantal punten 0 voor een artikel, dan wordt het bedrag op de kassa samengeteld voor de algemene puntenkorting van de kassa (zie hieronder).

**Afwijkingen per artikel/groep/leverancier**: maak een promotiefiche onder **V.2.1** met een lange periode (bv. tot 31/12/2035), het gewenste artikel, groep of leverancier en het aantal punten zoals hierboven.

**Op de kassa** (enkel gebruikt als er op de hoofdcomputer voor het artikel geen punten bepaald zijn): stop de kassa tot op het menu, neem **punt 3 "Aanpassen parameters"**, sluit een toetsenbord aan en druk **F3 volgend** tot het juiste scherm:

| Parameter | Voorbeeld | Betekenis |
|---|---|---|
| Aantal punten per aankoopwaarde (%) | 100.00 Ptn/100 EUR | 1 punt per euro = 1 % korting |
| Aantal punten van een volle kaart | 500 | een volle kaart is dan 5 EUR waard |
| Waarde van een volle kaart | 5 EUR | dit bedrag komt als tegoed op het kasticket |

> Zeer belangrijk: het **aantal punten voor een volle kaart moet op de kassa ingevuld zijn**. Anders **blokkeert de kassa bij het afrekenen**.

### 1.5 Punten uitkeren

Punten uitkeren doe je door een speciaal artikel te verkopen:

1. **Korting in euro bij een volle kaart**: maak een artikel (bv. "Uitkering punten") met eenheidsprijs 5 EUR en geef in de promoties aan dat voor dit artikel 500 punten gerekend worden. Verkoop: **-1 ×** dit artikel.
2. **Punten inruilen tegen promotieartikels** (bv. glazen): maak voor die artikels fiches aan 0 EUR en geef in de promoties het aantal punten **negatief** in (bv. -100). Door het artikel te verkopen worden de punten verminderd.
3. **Vrij aantal punten uitkeren**: maak een artikel "Uitgekeerde punten" aan 0 EUR met in de promoties -1 punt. Om 250 punten uit te keren verkoop je 250 × dit artikel.

### 1.6 Omzet op de klantenkaart

Bij het **inlezen van de verkopen (V.2.3)** wordt de omzet op de klantenkaart bijgeschreven: bedrag + datum van de laatste 10 aankopen, en per artikelgroep de aankopen met de laatste aankoopdatum. Dit dient voor selecties (mailings, verouderde klanten schrappen) en voor het uitschrijven van adressen naar een bestand.

### 1.7 Klantenkaart VERENIGING

Uitbreiding: bovenop de individuele klantenkaartkorting een extra korting voor de vereniging waarvan men lid is.

- Iedereen (lid of niet) heeft een individuele kaart met dezelfde puntenwerking.
- **Vereniging aanmaken**: maak een klantenkaart voor de vereniging. Op die kaart geef je via de `+`-knop en dan punt 2 "Toon alle groepen/groepskorting" de extra kortingen per artikelgroep in. Deze kaart mag ook aan de kassa gebruikt worden als men echt voor de vereniging koopt.
- Bij de **leden** vul je in "Kaart groepering" het kaartnummer van de vereniging in.
- **V.2.9.5**: lijst van de leden van de vereniging.
- **V.2.9.6**: lijst met omzet/korting per lid en totaal van de vereniging (periodiek, bv. per kwartaal). Op basis hiervan maak je een creditnota aan de vereniging.
- **Wissen groepsomzet leden van vereniging** (V.2.9.7 volgens deze handleiding): na het uitkeren van de korting de groepsomzetten wissen. Enkel het bedrag wordt gewist, niet de laatste aankoopdatum (mailingselecties blijven mogelijk).

## 2. Klantenkaartenmodule installeren op de kassa (technisch)

Betrokken posities in `kassys.dat`: 3280 (aantal kaarten), 3636 (% punten), 3640 (punten volle kaart), 3644 (waarde volle kaart), 3648 (identificatienummer, 6 tekens), 3654 (waar staat het puntenbestand).

### 2.1 Nieuw systeem: klantenkaarten via JMD (huidige werkwijze)

Voorbereiding (ontwikkeling): klant opladen, DRK0900 incompileren, `struct.cnf` aanpassen (structuur 92 Klantenkaarten vergelijken en eventueel refreshen; 94 Kaart-groepsomzet volledig vervangen; 96 KltKaartKoppelingen toevoegen), update klaarzetten.

Installatie – **nog geen klantenkaarten**:

1. Noteer als identificatienummer de eerste 5 cijfers van het btw-nummer.
2. Laat doorsturen met de kassa's (punt N) en forceer zo nodig een online backup.
3. Voor **elke** kassa de `kassys.dat` uit de fromklt nemen en aanpassen:
   - `upsys kassys.dat i 3280 0` (aantal klanten op 0 omdat het via JMD gaat)
   - `upsys kassys.dat i 3654 8` (puntenbestand via JMD)
   - `upsys kassys.dat s 3648 6 *****` (identificatienummer)
   - `upsys kassys.dat f 3636 100` (% punten, klantafhankelijk)
   - `upsys kassys.dat f 3640 500` (punten volle kaart, klantafhankelijk)
   - `upsys kassys.dat f 3644 5` (waarde volle kaart, klantafhankelijk)
   - het blokje **KLT-KRT** toevoegen via `kaskeys`.
4. `kassys.dat` klaarzetten als `kassys.001` met in `j.bat`: `COPY KASSYS.001 ..\KASSA\TO\KASSA-01\KASSYS.DAT`.
5. Als er nog geen directe facturatie op de kassa (= JMD op de kassa) is: de JMD laten meestarten in `kasmenu.dat` punt 1 (`start jmd.exe /min #A` … `kassa.exe` … `start jmd.exe /min #C`, met `ping 127.0.0.1 -n 4` / `-n 2` als wachttijd), `kasmenu.dat` klaarzetten als `kasmenu.001`, een kassapost toevoegen in `jms.ini` (zie `kassa-installatie-en-updates.md` §5.1) en de `runonce.kas` meegeven.

Installatie – **al klantenkaarten via het oude systeem**: zelfde stappen maar enkel `3280 → 0` en `3654 → 8` (de overige waarden staan al goed).

Afwerking op de server:

1. Verkopen inlezen tot zover mogelijk (V.2.3) – verkoop klantenkaart bijwerken.
2. De punten van de kassa inlezen (V.2.9.+ en dan de verborgen F10 = kassa 1).
3. Systeemwaarde SYS 3772 (H, 2): bit 0 op 1 zetten ("geen bijwerking klantenkaart in OVL0290").
4. De klaargezette update laten ophalen.

### 2.2 Oud systeem (puntenbestand op de kassa of op kassa 1)

**Eén kassa**:

1. Haal `kassys.dat` en `uckasday.jam` op (`\kassa\kassa-01\`). Vraag het identificatienummer op (V.2.9.+; indien leeg: bv. de eerste 5 cijfers van het btw-nummer).
2. Pas `uckasday.jam` aan zodat `kaskrtnm.dat` mee doorgestuurd wordt (kopieer 1 lijn en verander de bestandsnaam).
3. Voeg het blokje KLT-KRT toe met `kaskeys` (van het blokje GROEP het blokje KLT-KRT maken).
4. `kassys.dat` aanpassen:
   - `upsys kassys.dat i 3280 10000` (aantal klanten)
   - `upsys kassys.dat f 3636 100`, `f 3640 500`, `f 3644 5`
   - `upsys kassys.dat s 3648 6 *****` (uniek identificatienummer)
   - `upsys kassys.dat i 3654 0` (puntenbestand op de eigen kassa)
5. Stuur beide bestanden (en indien nodig een nieuwere kassa.exe/kassa32n.exe) terug en laat doorsturen.
6. Vul in kasparm de puntenparameters in (zie §1.4) en test.

**Tweede of derde kassa in het netwerk**: eerst kassa 1 volledig laten werken; daarna identiek, behalve positie 3654:

- `3654 i 1`: puntenbestand op `\\keytouch-01` (Epson-kassa);
- `3654 i 2`: puntenbestand op `\\wintouch-01` (Glaive en later).

Kassa 1 moet altijd opgestart zijn in Windows.

**Tweede of derde kassa op afstand**: de klant heeft een internetabonnement met vast IP-adres nodig zodat de punten op een pc in het netwerk bewaard worden: `3654 i 4` (kassa.exe; bestand op `z:\`) of `3654 i 2` (kassa32n.exe).

## 3. Freedelity-koppeling (klantenkaart Prik&Tik)

### 3.1 Wat is het

Koppeling met het klantenkaartsysteem van Freedelity, gebruikt bij de leden van Prik&Tik. Na elke verkoop schrijft de kassa het kasticket uit in een XML-bestand en roept `Freedelity.exe` op. Dat leest de identiteitskaart en verwerkt de verkoop in het Freedelity-systeem. De eigen kaartlezer en eigen klantenkaartfuncties van Jamadata worden in het kassaprogramma afgekoppeld; de reader van Freedelity wordt enkel voor deze toepassing gebruikt.

De aanpassing bestaat uit 2 delen:

- een koppelingsmodule om de artikelnummers van Prik&Tik op het veld "Referentie leverancier" van de aankoopfiche te zetten (module 2291, artikelbestand `PnTArtikel.TXT` in de map `..\DIV` bij de klant; de klant moet toegang krijgen tot het downloaden van het artikelbestand van Prik&Tik);
- de kassa moet `Freedelity.exe` oproepen en afhandelen.

### 3.2 Installatie op de kassa

1. Zet de speciale runonce voor Prik&Tik (`runonce.P&T`) klaar als `runonce.kas` en laat de kassa binnenbellen met T en M. Deze runonce doet:
   - `upsys32 kassys.dat i 4034 1` (Freedelity-systeem activeren);
   - de laatste versies van de kassa installeren;
   - `Freedelity.exe` doorsturen (als `fdelity.exe` meegegeven en op de kassa hernoemd naar `freedelity.exe`).
2. Start de kassa: de Freedelity-knop moet er staan: **Diversen → rechts onderaan "Loyalty card Freedelity"**.
3. De eerste keer dat je erop drukt moet je de **USERID en het PASWOORD** van de klant ingeven en **PRODUCTION** kiezen. De klant krijgt deze gegevens van Freedelity.
4. Werkt alles: de laatste gewone `runonce.kas` klaarzetten en laten ophalen voor de laatste exe's.

Locatie van `freedelity.ini`: in `c:\kassa`, maar meestal in `C:\Users\Kassa\AppData\Local` (Windows 7/10; AppData is verborgen) of `C:\Documents and Settings\kassa\Local Settings\Application Data` (XP). Bij een nieuwe/vervangen kassa moeten `freedelity.ini` en `freedelity.exe` mee overgezet worden (in de ini de `~` vervangen door de juiste naam).

### 3.3 Extra punten geven zonder verkoop (Freedelity)

1. Geef geen artikel in.
2. Druk op **Einde**.
3. Tik als bedrag **0.01** in.
4. Druk op **Geld**.
5. Het scherm met de grote knop Freedelity verschijnt: druk erop.
6. Freedelity ziet dat er geen verkoop was en vraagt "bedrag = punten" in te geven.
7. Geef het aantal punten in.

### 3.4 Problemen

- **Freedelity-scherm komt niet (meer) naar voren / start niet op in de achtergrond**: herstart de kassa; dat lost het normaal op.
- **Freedelity-scherm verschijnt plots niet meer**: haal in `kasmenu.dat` (punt 1) de vertraging/opruimlijnen vóór de start weg door ze in `REM` te zetten (de `jamadel …`-lijnen en de `ping 127.0.0.1 -n 4`). Het resultaat ziet er zo uit:

  ```
  start jmd.exe /min #A
  banksys.exe
  REM jamadel c:\users\*.tmp /s /all
  REM jamadel c:\windows\*.log /s /all
  REM jamadel c:\windows\temp\*.* /s /all
  rem ping 127.0.0.1 -n 4
  kassa.exe
  start jmd.exe /min #C
  ping 127.0.0.1 -n 2
  ```

- Na een image restore: Freedelity opnieuw instellen en het artikelbestand volledig uitschrijven.

## 4. Eigen cadeaubons

### 4.1 Wettelijk/boekhoudkundig

De "verkoop" van een cadeaubon is een **voorafbetaling** van een klant voor goederen die later gekocht worden. Er is dus niets verkocht en er mag **geen btw** geheven worden. Boek dit op een aparte rekening, liefst een 4-rekening (bv. 460000 Voorafbetaling klanten, **zonder btw-vak**); het mag niet in de btw-aangifte komen. Wanneer de bon later gebruikt wordt, komt het bedrag in mindering van deze rekening; het saldo is dus het totaal van de uitstaande cadeaubons.

### 4.2 Werking op de kassa (huidige manier)

- **Verkoop cadeaubon**: geef het bedrag in, druk op **Diversen** en dan op **"Verkoop cadeaubon"**.
- **Ontvangen cadeaubon**: op het eindscherm van de verkoop (na Einde) het bedrag ingeven en op **Cadeaubon** drukken, zoals bij andere betaalmiddelen.
- De bewegingen van cadeaubons staan in het financiële luik van de controleband.

### 4.3 Kasverslag op de pc

Geef eenmalig in de **kasverslag-parameters** de juiste grootboekrekening in voor "verkoop cadeaubons" en "ontvangen cadeaubons". De bewegingen komen in het financiële luik, zoals op de kassa.

### 4.4 Oude manier (via een artikel) – enkel nog bij oude installaties

- Artikelfiche: groep Cadeaubons (bv. 97), btw 0 %, grootboekextensie 9 (mag niet door andere artikels gebruikt worden); blokje op de kassa met dit artikel. Boekhouding: rekening bv. 700900 Cadeaubons, **geen** vak btw-aangifte.
- Uitgeven: op het artikelblokje drukken, bedrag intikken, dan EH-PRIJS (E.P.).
- Ontvangen: op het artikelblokje drukken, bedrag **negatief** intikken, dan EH-PRIJS.

## 5. Tegoedbons (TeGoed-bons)

### 5.1 Werking

- Bij een **negatief ticket** (bv. enkel leeggoed terug) vraagt de kassa of er een tegoedbon afgedrukt moet worden. Zo ja, dan wordt die afgedrukt in plaats van geld terug te geven.
- De tekst op de tegoedbon is aan te passen via kasparm (kassamenu punt 3, parameter "tekst eigen tegoedbon").
- Een ingeleverde tegoedbon wordt verwerkt met de betaalknop **"Eigen tegoedbon"** (na Einde): bedrag ingeven en op de knop drukken.

**Tegoedbon is meer waard dan het te betalen bedrag** – 2 mogelijkheden:

1. Geef het **te betalen bedrag** in en druk op "Eigen tegoedbon". Schrijf het betaalde bedrag op de tegoedbon van de klant en geef hem die terug.
2. Geef het **bedrag van de tegoedbon** in en druk op "Eigen tegoedbon". De kassa meldt dat je nog xxx EUR moet teruggeven. Druk nu nogmaals op "Eigen tegoedbon" (of op "Geld"): de kassa sluit de verkoop af en drukt een **ticket met het restant-tegoed** af. Geef dit ticket aan de klant voor de volgende keer en hou de originele tegoedbon bij. (Werkt enkel met kassaversie vanaf 01/11/2022.)

### 5.2 Instellen (technisch)

1. Haal `kassys.dat` van de kassa naar de temp-map, open de virtuele machine/DOSBox, `getbeta` (Ctrl X, Enter).
2. `upsys32 kassys.dat` → integer op positie **3198**: "TeGoed bons afdrukken (1 = JA, 0 = nee, d.w.z. geld teruggeven)". Zet op 1 om tegoedbons te activeren. (De OneNote-notitie "Eigen tegoedbon toevoegen" vermeldt hier "deze moet 0? worden" met vraagteken – tegenstrijdig met de beschrijving van de positie; volg de KASSYS-beschrijving en test.)
3. Voeg met KASKEYS het blokje **"Eigen tegoedbon"** toe als betaalmiddel (zie `kassa-configbestanden.md` §6).
4. Zet `kassys.dat` terug op de kassa.
5. Op de kassa: punt 3 Parameters → de tekst voor de eigen tegoedbon invullen.
6. Plaats de meest recente `runonce.kas` (kassa.exe en kasparm.exe moeten recent genoeg zijn).

## Bronnen

- `Jamadrink/Handleidingen modules/0294A - Klantenkaarten.docx`
- `Jamadrink/Handleidingen modules/0294B - Klantenkaart VERENIGING.docx`
- `kassa/HOWTO-Instellen KLANTENKAARTEN.docx`, `kassa/KLTKRT.docx`
- `Jamadrink/HOWTO - Klantenkaarten via JMD installeren.docx`
- `kassa/HOWTO-Freedelity-koppeling.docx`
- `kassa/Hoe eigen cadeaubons verwerken.docx`
- `kassa/HOWTO-Kassa TeGoed bons afdrukken.docx`
- `kassa/gebruikershandleiding keyConen KASSA 2.0.docx` (knoppen KLT-KRT, Puntentotaal, Loyalty card Freedelity, Verkoop cadeaubon, Eigen tegoedbon)
- `kassa/KASSYS.docx` (posities 3198, 3280, 3636–3654, 4034)
- `Onenote/KASSA.pdf` (11 Eigen tegoedbon toevoegen aan kassa; Freedelity start niet op in achtergrond)
