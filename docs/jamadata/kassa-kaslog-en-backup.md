# Kassa – Kaslog (verkoopgegevens), kaslog per maand en backup van kassagegevens

Gebruik dit document voor: vragen over waar de kassa haar verkoopgegevens bewaart (`kaslog.dat`, `kaslog.001`, maandelijkse `KLJJJJMM.dat`), het omschakelen van een kassa naar een kaslog per maand, het controleren/vergroten van het aantal records, het terugzetten van een oude kaslog om oude kasverslagen op te roepen, en het maken/terugladen van een kopie van de kassagegevens via het kassamenu (punten 4 en 5).

## 1. Hoe bewaart de kassa de verkopen?

| Bestand | Inhoud |
|---|---|
| `kaslog.dat` | Alle verkoopbewegingen sinds de laatste keer "wissen van de verkoopgegevens" (klassiek systeem). |
| `kaslog.001` | De vorige kaslog (van vóór het laatste wissen). |
| `KLJJJJMM.dat` (bv. `KL202510.dat`) | Kaslog per maand (nieuw systeem). Op de kassa tot 1 jaar terug, op de hoofdcomputer jaren terug. |
| `kasfac.dat` | Facturen/bons die op de kassa gemaakt zijn. |
| `*.wrk` | Bewaarde bons (werkbonnen). |

Bij de dagelijkse transfer (N/K) gaat een kopie van de verkoopgegevens naar de hoofdcomputer (`J:\Jamadata\Kassa\kassa-0x`), waar ze met V.2.3 ingelezen worden.

Het maximaal aantal records van de kaslog staat in `kassys.dat` positie 3588 (`rec_aantal`, standaard 70000, max. 150000). Je ziet de bezetting door in het kassamenu bovenaan op de rode titel "Menu: beheer key-conen kassa" te drukken.

**Klassiek systeem**: de klant moet af en toe via kassamenu **punt A "Wissen van de verkoopgegevens van de kassa"** de kaslog leegmaken (de oude wordt `kaslog.001`). **Kaslog per maand**: er hoeft niet meer manueel gewist te worden.

## 2. Kaslog per maand instellen (maandelijkse KL-bestanden)

### 2.1 Wat de klant moet weten

- Alles wordt nu bijgehouden: ook grote particuliere verkopen blijven zichtbaar (ook voor de fiscus bij een controle).
- **De kassa MOET altijd vóór de maandwissel uitgeschakeld worden.** Gebeurt dat niet, dan komen verkopen van de nieuwe maand in het bestand van de oude maand terecht.
- De aanpassing moet op **alle kassa's tegelijk** gebeuren, plus één wijziging op de server.

### 2.2 Vereisten

- Laatste versie van `KASSA.exe` en `KASMENU.exe` op **alle** kassa's (laatste `runonce.kas`).
- Laatste versie van de programma's op de pc/server (na 30/05/2018).
- De omschakeling moet **tegelijkertijd** gebeuren op kassa's en server.

### 2.3 Werkwijze

1. **Voorbereiden**: voer op elke kassa de laatste `runonce.kas` uit, stuur door met alle kassa's (N) en lees de verkopen zo ver mogelijk in (V.2.3).
2. **Op elke kassa – kassys.dat**: `upsys32 kassys.dat i 3656 2` (bit 1 = elke maand een ander bestand).
3. **Op elke kassa – bestaande kaslog hernoemen** naar het maandformaat. Kijk op de kassa wanneer er voor het laatst gewist is en maak het script daarop klaar. Er bestaat een hulpscript in de interne map `Kasmaand` (op de X-schijf); je past het aan met het commando `UPDauto` (editor; Ctrl X en Enter om te bewaren):

   ```
   Ren kaslog.dat KL2025XX.dat      (XX = de HUIDIGE/meest recente maand)
   Ren kaslog.001 KL2025YY.dat      (de vorige periode, maand min 1)
   ```

   Bevat `kaslog.dat` meerdere maanden, maak dan voor elke andere maand ook een KL-bestand door te kopiëren: `Copy KL2025XX.dat KL2025YY.dat`.

   Zet de update klaar met `dumpmod <klantcode>`; op de kassa ophalen via **T** in het kassamenu (bij een oude kassa na de T ook **M**).
4. **Op elke kassa – kasmenu.dat** (map kassa, openen met Kladblok):
   - voeg bij punt 1 (opstarten kassa) 2 lijnen toe:

     ```
     jdel kl20*.dat -b -o365
     jdel 20*.pdf -b -o31
     ```

   - zet menupunt **A** ("Wissen van de verkoopgegevens van de kassa") tussen commentaarlijnen (`/*` erboven, `*/` eronder) zodat het niet meer gekozen kan worden.
5. **Op de server – systeemwaarde 4400**: bit 2 moet op 1, d.w.z. waarde **4** (`upsys32 sys.* i 4400 4`). Dit kan ook vanaf de kassa via de JMD: start het kassaprogramma (F8), ga naar de JMD → Hoofdmenu → `+` → `T` → `1` (Aanpassen systeemwaardes) → plaats systeembestand 4400, soort `I` → Tab (de waarde staat op 0) → waarde **4** → F8. Dit hoeft maar één keer voor alle kassa's. **Opgelet: foutief invullen heeft grote gevolgen.**
6. Stuur opnieuw door met de kassa's (N) en controleer of het `KLxxxxxx.dat`-bestand goed aankomt op de server.
7. **Aantal records controleren**: druk in het kassamenu op de rode titel. Is er ruimte voor meer dan 30 dagen, dan is het in orde. Is er niet genoeg ruimte voor een volledige maand: `UPSYS32 KASSYS.DAT` → `L 3588` verhogen (standaard 70000, max. 150000; niet groter dan noodzakelijk).
8. **Eindcontrole**: in de JMD punt 2 → kassaverkopen inlezen (V.2.3). Zie je daar de datum/het uur van het verkopenbestand, dan is het gelukt. Zo niet, dan is er iets fout gegaan.

Bij een nieuwe kassa-installatie: oude `kaslog.*` en oude `kl20xx*`-bestanden van de voorbeeldinstallatie wegdoen.

## 3. Oude kasverslagen terug oproepen (backup van kaslog.dat terugzetten)

Voor kasverslagen die niet meer in `kaslog.dat` of `kaslog.001` zitten:

1. Zoek een oudere `kaslog.dat`:
   - op de USB-stick van de kassa (normaal de F:-schijf); of
   - als die al lang niet meer insteekt: op de hoofdcomputer in `J:\Jamadata\Copy.alt\snapshot-$$$-<datum>.zip\Kassa.zip\Kassa-01`. Neem altijd de snapshot met de `$$$`-tekens en kijk naar de juiste datum (gewijzigd op).
2. Hernoem de huidige `kaslog.dat` (onder `J:\Jamadata\kassa`) naar `kaslog.new`.
3. Kopieer de oude `kaslog.dat` op die plaats.
4. Roep nu de gewenste kassaverslagen op.
5. Is de klant klaar: zet manueel het originele bestand terug (`kaslog.new` → `kaslog.dat`).

## 4. Kopie maken en terugladen van de kassagegevens (kassamenu)

- **Punt 4 "Kopie maken van de kassagegevens"**: maakt een backup van de kassagegevens. Doe dit (plus een N-transfer) vóór elke ingreep op de kassa (image restore, vervanging).
- **Punt 5 "Terug opladen van oude kopie van kassagegevens"**: kies punt 5 [Enter] → [F4] – ja – [Enter] → [F5] – nee – [Enter] → [Enter] [Enter].
- **Punt 9 "Wissen van het facturen-bestand: KASFAC.DAT"**.
- Alternatief: de volledige map `C:\KASSA` met Verkenner kopiëren naar de USB-stick/2e partitie.

Controleer na het terugladen altijd de kassaverkopen en de prijzen. Prijzen kunnen opnieuw doorgestuurd worden; kassaverkopen niet.

Voor de volledige systeembackup (image) en de restore per type kassa: zie `kassa-image-restore.md`.

## 5. Opruimen van tijdelijke bestanden bij het opstarten (oudere installaties)

In `kasmenu.dat` van oudere kassa's staan opruimlijnen die bij elke start tijdelijke bestanden wissen, bv.:

```
jamadel c:\*.tmp /s /all
jamadel c:\*.log /s /all
jamadel c:\windows\temp\*.* /s /all
jamadel c:\windows\tmp\*.* /s /all
```

(plus de Temp- en Temporary Internet Files-mappen van de gebruikers Kassa en Administrator). Deze lijnen vertragen het opstarten; ze kunnen met `REM` uitgeschakeld worden als ze problemen geven (zie Freedelity in `kassa-klantenkaarten-cadeaubons-tegoedbons.md`).

## Bronnen

- `kassa/INSTELLEN MAANDELIJKSE KL FILES (KASLOG) OP KASSA’S.docx` (en `.pdf`)
- `kassa/HOWTO-Instellen KASLOG per MAAND.docx`
- `kassa/KASSYS.docx` (posities 3588, 3656)
- `kassa/gebruikershandleiding keyConen KASSA 2.0.docx` (kassamenu punten 4, 5, 9, A)
- `kassa/Kassa installeren.docx`
- `Onenote/KASSA.pdf` (04 Backup Kaslog.dat terugzetten op kassa)
- `kassa/RPrestor.docx`, `kassa/PanelPC_image_restore_SSD vanop USB-stick.docx` (punt 4/5 van het kassamenu)
