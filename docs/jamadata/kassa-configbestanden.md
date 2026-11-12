# Kassa – Configuratiebestanden en technische tools (KASSYS.DAT, KASMENU.DAT, JAMA.BAT, UPSYS, KASKEYS, RUNONCE)

Gebruik dit document voor: technische supportvragen over de instelbestanden van de Key-Conen kassa: welke bestanden in de map `KASSA` staan, hoe je een systeemwaarde in `KASSYS.DAT` wijzigt met `upsys`/`upsys32`, de volledige lijst van posities in `KASSYS.DAT`, de opbouw van `KASMENU.DAT` en `JAMA.BAT`, het aanpassen van de vaste systeemknoppen met `KASKEYS` en de lijst van knopcodes (KeyCoon-nummers). Dit is interne technische documentatie (voor Jamadata-support, niet voor eindgebruikers).

## 1. Overzicht bestanden op de kassa (map `C:\KASSA`, soms `Jamadata\Kassa`)

| Bestand | Functie |
|---|---|
| `KASSA.EXE` | Het kassaprogramma (Windows-versie). Oude DOS/Epson-versie: `KASSA32N.EXE`. |
| `KASMENU.EXE` / `KASMENU.DAT` | Het kassamenu ("Menu Beheer Key-conen Kassa") en de definitie van de menupunten (tekstbestand, aanpasbaar met Kladblok). |
| `KASPARM.EXE` | Parameterprogramma (menupunt 3 "Aanpassen parameters"): tickethoofding, reclameteksten, factuurhoofding, klantenkaartparameters, tekst tegoedbon, tekst variabele betaalwijzen, printer, … |
| `KASSYS.DAT` | Systeembestand met alle instellingen van deze kassa (15.000 bytes). Zie §3. |
| `KASPLU.DAT` | Artikelbestand (PLU's, prijzen) dat vanaf de hoofdcomputer wordt klaargezet (V.2.K) en met de transfer (N/K) op de kassa komt. Ook `KASPLUEX`, `KASPLUST`. |
| `KASLOG.DAT`, `KASLOG.001` | Verkoopgegevens (kaslog) van de kassa; `.001` is de vorige (gewiste) periode. Bij kaslog per maand: `KLJJJJMM.DAT`. Zie `kassa-kaslog-en-backup.md`. |
| `KASFAC.DAT`, `KASFACKLT` | Facturenbestand van de kassa en klanten voor facturatie. |
| `*.WRK` | Werkbonnen / bewaarde bons (Bewaren bon / Opladen bon). |
| `KASKRTNM.DAT`, `KASKRTPT` | Klantenkaarten: namen en punten (oud systeem, niet via JMD). |
| `KASUSR.DAT` | Gebruikers/kassiers. |
| `UCKASDAY.JAM` | Script van de dagelijkse transfer (welke bestanden van/naar de hoofdcomputer gaan). |
| `KEYCOONN.JAM`, `KASSCR.SCJ`, `JAMACON.DLL` | Programma-onderdelen van de kassa (meesturen bij een update). |
| `KEYFACT.JAM` / `KEYFACT.PNG`, `JAMAP.DLL` | Lay-out voor grote facturen op de kassa. |
| `LARGDISP.DLL`, `AFFICHE.JPG` | Grote klantendisplay en reclamebeeld. |
| `BANKSYS.EXE`, `CARDFON.EXE`, `INGENICO.EXE` (+ `IngenTlv.dll`, `IngenUti.dll`), `ANTENOR.EXE` (+ `Antenor.cfg`, `AntenorD.dll`) | Koppelprogramma's betaalterminal / cashautomaat. |
| `FREEDELITY.EXE`, `freedelity.ini` | Freedelity-koppeling (ini staat meestal in `C:\Users\Kassa\AppData\Local`). |
| `JAMA.BAT` | Opstartbatch met de instellingen van deze kassa (kassanummer, IP hoofdcomputer). Zie §5. |
| `RUNONCE.KAS` | Updatepakket: wordt bij het opstarten van de kassa één keer uitgevoerd. Zie `kassa-installatie-en-updates.md`. |
| `KASMODSV.EXE` | Nodig als de kassa via de Jamadata-server doorstuurt (kassa op afstand). |
| `20*.PDF` | Pdf's die de kassa aanmaakt (worden na 31 dagen opgeruimd met `jdel`). |

Op de hoofdcomputer staat de tegenhanger in `J:\Jamadata\Kassa\` met submappen `to\kassa-0x` (klaargezet voor kassa x) en `kassa-0x` (ontvangen van kassa x).

## 2. Een waarde in KASSYS.DAT wijzigen met UPSYS / UPSYS32

`upsys` (DOS) of `upsys32` wijzigt één positie in een systeembestand. Typen: `c` = char (1 byte), `i` = integer (2 bytes), `u` = unsigned integer, `l` = long (4 bytes), `f` = float (4 bytes), `s` = string (met lengte).

Schrijfwijzen zoals ze in de bronnen voorkomen:

```
upsys32 kassys.dat i 3656 2          (integer op positie 3656 op 2 zetten)
upsys kassys.dat f 3636 100          (float)
upsys kassys.dat s 3648 6 *****      (string van 6 tekens)
upsys kassys.dat c 4020 3            (char)
upsys kassys.dat                     (interactief; dan bv. "s 3368 len 32" en waarde "localhost")
UPSYS32 KASSYS.DAT → L 3588          (long)
```

Werkwijze support (uit OneNote "Knoppen aanpassen" / "Eigen tegoedbon"):

1. Haal de `kassys.dat` van de klant op en zet ze in een tijdelijke klantmap op de interne temp-share (X-schijf, `X:\Temp\XXX\kassys.dat`). Maak altijd eerst een kopie (`*.old`).
2. Open de 32-bit virtuele machine met DOSBox en ga naar die map.
3. Voer `getbeta` uit (haalt de laatste tools/programma's op); druk "Ctrl X" en daarna "Enter".
4. Voer de `upsys32`-aanpassing uit (of `kaskeys` / `kasparm`).
5. Zet de `kassys.dat` terug op de kassa van de klant (rechtstreeks, of via de update-/transfermap `\kassa\to\kassa-01`).

Systeemwaarden van de **server** (`sys.*`) kunnen ook in JMD aangepast worden: Hoofdmenu → `+` → `T` → `1` (Aanpassen systeemwaardes): plaats en soort invullen, Tab, waarde ingeven, F8. Fout invullen heeft grote gevolgen.

## 3. Posities in KASSYS.DAT

Nota uit de bron: alle "dummy"-zones staan op 0 tenzij anders vermeld. `*` = positie die bij installatie relevant is. Legacy-posities (Hercules-kaart, lichtpen, CBM-720) zijn enkel voor zeer oude kassa's.

### 3.1 Algemeen, groepen, ticket, lade, valuta

| Loc | Len | Type | Omschrijving |
|---|---|---|---|
| 0 | 1 | c | Herkenning systeemfile (`\xF2`) |
| 1–33 | | s | "Vers ", versienummer, datum laatste update, "(c) Jamadata" |
| 64 | 64 | s | Naam van `*.BPI`-file vanuit KASLAY. Niet ingevuld = affiche-functie niet voorzien |
| 512 | 2400 | s | grp_info: per groep naam [20] + btw % (float) |
| 2912 | 100 | s | grp_bits (100 × 8 bits): bit 0 = on-interessant J/N (0 = interessant); bit 1 = op klantenkaart of niet |
| 3072 | 2 | i | Nr. communicatiepoort voor bediening lade (als 3260 op 0 staat) |
| 3074 | 10×2 | i | Herculeskaart-nummer voor 0=Kassa, 1=Kaslay, 2=Kasparm, 3=Kasmenu (legacy) |
| 3094 | 2 | u | Kasticket-type: bit 1/0: 00 = leeggoed mee/goederen apart, 01 = TOTAAL, 10 = leeggoed mee/terug apart; bit 2: 1 = extra controle-printer |
| 3096 | 2 | i | Aantal lades (moet 11 × aantal verkopers zijn, normaal 33) |
| 3098 | 50 | s | Valuta's (5 × 10 bytes): naam [3], coëfficiënt t.o.v. default valuta (float), lade#, aantal digits na komma (bit 7 = nullen na komma tonen) |
| 3196 | 2 | i | NIET automatisch geld teruggeven indien bedrag negatief (cashautomaat) |
| 3198 | 2 | i | **TeGoed-bons afdrukken** (1 = ja, 0 = nee, d.w.z. geld teruggeven) |
| 3200 | 10×2 | i | Leeggoedsysteem: bit 0 = auto leeggoed, bit 1 = leeggoed terugnemen |
| 3220 | 10×2 | i | Prijstype per verkoper: 0 = normaal, 1 = horeca …; +10 = bij snelkiezen BAK i.p.v. FLES |
| 3240 | 10×2 | i | Lade per verkoper |
| 3260 | 2 | i | Ladetype: 0 = via RS-232, 1 = op 12 V via MIO |
| 3262 | 2 | i | Barcode-optie: 0 = geen, 1–4 = COM1–COM4, 99 = keyboard, 11–14 = COM1–COM4 met CR op einde zonder STX/ETX (2400 baud, 8 bits, no parity, 1 stopbit) |
| 3264 | 2 | i | ART_count: aantal artikelen te voorzien |
| 3266 | 2 | i | KEY_count: aantal beschreven toetsen (30 % meer dan ART's) |
| 3268 | 4 | l | WORKSPACE voor kaslay (0 = geen update van KASPLU.DAT; anders 45.000 per 1.000 in ART_count) |
| 3272 | 2 | i | pen_delay (legacy lichtpen) |
| 3274 | 2 | i | EXT_count: aantal extra barcodes die ingelezen kunnen worden |
| 3276 | 2 | i | Max. bedrag TEST-tickets |
| 3278 | 2 | i | LEEG_OK-type: bit 0 = leeggoed op 1 lijn in groep LEEGGOED; bit 1 = enkel AUTO-leeggoed corrigeren |
| 3280 | 2 | i | **KRT_count: aantal klantenkaarten** (0 als klantenkaarten via JMD) |
| 3282 | 2 | i | Euro-vermelding op ticket: 1 = totaal, 2 = lijn per lijn, 3 = beide |
| 3284 | 2 | i | Kortingstype: bit 0 = 1: korting op subtotaal (geeft problemen voor Jamadrink) |
| 3286 | 64 | s | **wrk_path**: prefix-pad voor WRK-bestanden (werkbonnen), bv. `\\wintouch-01\kassa` |
| 3350 | 2 | i | PLU-link met artikelen: 0 = 2× leeggoedcodes, 1 = 2× optie vragen |
| 3352 | 2 | i | Aantal tafels voor bons: 0 = klassiek, x = aantal tafels (max. 30) |
| 3354 | 2 | i | Uren na middernacht die bij de vorige dag horen |
| 3356 | 4 | f | BTW % voor maaltijden ter plaatse |
| 3360 | 2 | i | Print ticket bij uitschrijven naar WRK-bestand (1 = ja, 2 = ja met altijd datum) |
| 3362 | 2 | i | Groepnummer voor opties (0 = opties niet actief) |
| 3364 | 2 | i | Configuratie opties: 1 = artikelprijs incl. optie weergeven |
| 3366 | 2 | i | Aantal digits voor eenheidsprijs (0 = default van valuta) |

### 3.2 Betaalterminal, toetsenbord, btw, afronding

| Loc | Len | Type | Omschrijving |
|---|---|---|---|
| 3368 | 32 | s | **DNS-naam of IP van het toestel met de bancontact-server**: `localhost` (kleine letters, zonder aanhalingstekens) als de koppeling op deze kassa draait; anders de computernaam van kassa 1 (bv. `WINTOUCH-01`, zonder `\\`) |
| 3400 | 2 | i | Eurocheque vervangen door: 0 = niet, 1 = PIN (Nederlandse benaming) |
| 3402 | 2 | i | Keyboardlayout schermtoetsenbord: 0 = ABCD, 1 = AZERTY |
| 3404 | 2 | i | Z-Totaal-toets bij kastotalen weergeven |
| 3406 | 5 | s | **PLU-nummer om extra kost kredietkaart te boeken** (eenheidsprijs van dat artikel = kost-factor) |
| 3415 | 1 | c | Creditkaarten toelaten via de knop Betaalautomaat (ook in KASPARM, Diverse parameters) |
| 3416 | 1 | c | PDA-bons oproepen via Key-conen blokkeren (1 = ja) |
| 3417 | 2 | i | Bedrag waaronder extra kosten % kredietkaart aangerekend worden |
| 3419 | 1 | c | Promotoetsen andere kleur (1 = bruin, 2 = goud, 3 = bordeaux, 4 = paars) |
| 3420 | 2 | i | Groepnummer dranken (i.v.m. btw-verlaging frituur) |
| 3422 | 4 | f | BTW % voor dranken ter plaatse verbruikt bij eten |
| 3426 | 2 | i | Configuratievlaggen: bit 0 = punteninfo op controleband; bit 1 = toch 2 tickets drukken bij factuur via JMD |
| 3428 | 2 | i | WRK-bestanden 380–480 NIET wissen na opladen |
| 3430 | 2 | i | Promoties toch toelaten op stuks (0 = nooit op stuks) |
| 3432 | 2 | i | Taal ticket (1 = Frans) |
| 3470 | 4 | f | Default afronden bij btw-berekening tot veelvoud van … |
| 3474 | 4 | s | Naam default valuta |
| 3478 | 4 | f | Default afronden tot veelvoud van … (0 = geen afronding) |
| 3482 | 1 | c | Aantal cijfers na komma |
| 3483 | 1 | c | Menutoetsen andere kleur (1 = bruin, 2 = goud, 3 = bordeaux, 4 = paars) |
| 3484 | 50 | s | Valuta's (5 × 10 bytes): afronden tot veelvoud van … |
| 3534 | 1 | s | **Totaal ticket afronden op 5 cent** (J/N) – verplicht vanaf 1/12/2019 |
| 3535 | 1 | s | Kassapromo's NIET indien horecaprijs (J/N) |
| 3536 | 2 | i | Eigen prijs op kassa: bij stuks toch korting % van klant toepassen op kassaprijs (0/1) |
| 3550 | 20 | s | **Serienummer van de HDD** (`?` = vul nieuwe waarde in). Hangt samen met de melding "Ongeldige serienummer" bij opstart (te overrulen met F4 en dan F10) |

### 3.3 Kaslog, controleband, facturen, klantenkaarten

| Loc | Len | Type | Omschrijving |
|---|---|---|---|
| 3584 | 2 | i | Groepsnummer leeggoed |
| 3586 | 2 | i | dag_aantal |
| 3588 | 4 | l | **rec_aantal**: aantal records voor de kaslog (standaard 70000, max. 150000 – niet groter dan nodig) |
| 3592–3600 | 2 | i | Controleband-keuzes: cf_cont, cf_art, cf_groep, cf_btw, cf_financ |
| 3602 | 2 | i | cf_periode: 0 = allemaal, 1 = enkel selectie, 2 = van begin t/m einde |
| 3604 | 2 | i | cf_cumper: 0 = ganse periode, 1 = dag, 2 = week, 3 = maand |
| 3606 | 2 | i | Ticketnummer elke dag resetten (0/1) |
| 3608 | 2 | i | Aantal prijzen in KASPLU.DAT (zonder stukprijs, max. 4) |
| 3610 | 2 | i | Laatst gebruikt factuurnummer |
| 3612 | 2 | i | **Factuur toegelaten**: bit 0 = kleine factuur, bit 1 = grote factuur, bit 2 = leveringsbon, bit 3 = mag via JMD op JMC draaien. Voorbeelden: 4 = enkel leveringsbonnetjes (standaard), 2 = grote facturen, 12 = facturatie via JMD |
| 3614 | 2 | i | Delay screensaver in sec. (bij leeg scherm) |
| 3616 | 2 | i | Idem maar na verkoop |
| 3618 | 2 | i | Geldlade-opening loggen (1) of niet (0) |
| 3620 | 2 | i | cf_vkptype: 0 = allemaal, 1 = particulier, 2 = bons/facturen, 3 = apart |
| 3622 | 2 | i | Sortering klantenkaart (0 = naam, 1 = nr, 2 = tel.nr, 3 = recordnr) |
| 3624 | 2 | i | Gecontroleerde kassier(ster)s, omschakelen via barcodes |
| 3626 | 2 | i | Verhinderen dat kassier eigen kastotaal kan afdrukken |
| 3628 | 2 | i | cf_verknr: 0 = allemaal, 1 = A, 2 = B, 3 = C |
| 3630 | 2 | i | Btw-berekening op elk kasticket (0/1) |
| 3632 | 2 | i | Kastotalen: bit 0 = tijd & datum op elk totaal; bit 1 = geen klantstatistiek op financieel overzicht; bit 2 = op controleband laatste ticket vorige dag |
| 3634 | 2 | i | Controlevlaggen: bit 0 = geen controleband; bit 1 = steeds weekend + maandag |
| 3636 | 4 | f | **% punten** t.o.v. basisbedrag (klantenkaart) |
| 3640 | 4 | f | **Punten volle kaart** (0 = bedrag afdrukken voor extern systeem) |
| 3644 | 4 | f | **Waarde volle kaart** |
| 3648 | 6 | s | **Code klantenkaartsysteem** (uniek identificatienummer → in de EAN-code van de kaart) |
| 3654 | 2 | i | **KltKrt-puntenbits**: bit 0: 0 = eigen file op kassa, 1 = file op `\\keytouch-01`; bit 1 = file op `\\wintouch-01`; bit 2 = file op `z:\`; bit 3 = systeem via JMD (waarde 8). Let op: in `kassa32n.exe` hebben bit 1 en 2 een andere betekenis (bit 1 = file op `e:\kassa` resp. `z:\`, bit 2 ongebruikt) |
| 3656 | 2 | i | **Kaslog**: bit 0 = elke dag ander bestand (`klYYMMDD.dat`); bit 1 = elke maand ander bestand (`klYYYYMM.dat`) → waarde 2 voor kaslog per maand |
| 3658 | 2 | i | Specifieke instellingen: bit 0 = toets krediet altijd tonen; bit 1: 0 = niet bij speciale klant, 1 = enkel tonen bij speciale klant (met `!`) |
| 3660 | 2 | i | Numeriek paswoord om de lade te openen met "alarm" of "geldlade" |

### 3.4 Tomra, printers, tickets, weegschaal-EAN, Freedelity, type kassa

| Loc | Len | Type | Omschrijving |
|---|---|---|---|
| 3662 | 4 | s | **Tomra-prefix** (bv. "980") om EAN-code-tickets te herkennen. Lege string = niet geactiveerd |
| 3666 | 10 | s | **Artikelnummer Tomra leeggoed-terugname** |
| 3676 | 32 | s | **Tomra_path** (bv. `\\server\tomra`, `t:\tomra` of `t:`) – zonder `\` op het einde, ook bij `t:` |
| 3708 | 2 | i | PCL3-facturen (0 = nee, of aantal exemplaren) (KEYFACT.JAM) |
| 3710 | 2 | i | Nummer printerpoort voor brede printer (zie 3712) |
| 3712 | 2 | i | Nummer printerpoort ticketprinter: 0/1 = LPT1/LPT2 parallel CBM-720; 3 = ingebouwde seriële Epson IR300 19,2 kbps; 4 = idem 2,4 kbps; 11–14 = seriële Epson op COM1–4 (9,6 kbps); 21–24 = idem 2,4 kbps; 30/31 = LPT1/LPT2 parallel Epson; 51 = TicketShare (pad op 14073); 52 = LaserShare (pad op 14153); -1 = geen printer |
| 3714 | 2 | i | Gereserveerd voor printerpoort controle-printer |
| 3716 | 2 | i | Geen ticket cutten en hoofding bij ticket drukken (niet bij opstart of op einde ticket). Voor mobiele printer zonder cutter: op 1 zetten |
| 4016 | 2 | u | Aantal afdrukken van een ticket (-1 = geen; 0 of 1 = 1; of 2, 3, 4) |
| 4018 | 2 | i | Verkorte datum |
| 4020 | 1 | c | Type EAN via weegschalen (`x..x#..#P..Pc`): 1 = P is prijs van de colli; 2 = gewicht/aantal; 3 = als 1 maar bedrag negatief (leeggoed) |
| 4021 | 4 | s | De eerste codes (lead-in) voor EAN van weegschalen, bv. "27" (string van 3 tekens) |
| 4025 | 1 | c | Positie van het codenummer (vanaf 0) |
| 4026 | 1 | c | Lengte codenummer (max. 5, anders ongeldig PLU-nummer) |
| 4027 | 1 | c | Positie van de extra informatie (vanaf 0) |
| 4028 | 1 | c | Lengte extra informatie |
| 4029 | 1 | c | Aantal digits na komma in extra informatie (2: 001265 = 12,65; 1: 126,5) |
| 4030 | 2 | u | Lijn per lijn het totaalbedrag afronden (nieuwe klanten standaard op 1) |
| 4032 | 2 | u | Geen tickets met "Error on total checksum. Check this" (1 = geen) |
| 4034 | 2 | u | **Freedelity-systeem** van Prik&Tik (1 = actief) |
| 4036 | 2 | u | **Soort kassa / klantendisplay**: 1 = Glaive; 2 = Richpos (display op COM4); 3 = Aerpos (display op COM6); 4 = PanelPC (display op COM6, afkappen op 20 karakters); 5 = PanelPC (display op losse voet COM1); 6 = PanelPC (display op losse voet COM3) |
| 4040 | 3×10 | s | Tekst variabele betaalwijzen (3 knoppen) |
| 4096 | 10×41 | s | Firmanaam als hoofding ticket |
| 4506 | 2×41 | s | Footer voor ticket (2 lijnen) |

### 3.5 Schermlay-outs, reclame, promoties, factuurteksten

| Loc | Len | Omschrijving |
|---|---|---|
| 4608 | 420 | bet_layout: 30 knoppen van het betaalscherm (key_numb, x_pos, y_pos, x_len, y_len) |
| 5312 | 14 | bet_krediet |
| 5376 | 840 | keyb_layout: 60 knoppen van het schermtoetsenbord |
| 7168 | 1400 | key_layout: 100 knoppen van het kassascherm |
| 9216 | 1452 | Reclameteksten [6][11][22] |
| 10752 | 1000 | grp_extra info: 10 bytes per groep (promo, gratis, sorteernummer voor werkbon kassa) |
| 11776 | 500 | Promo-beschrijving: 25 bytes per promomodel (20 mogelijk): formule + 4 getallen |
| 12288 | 1020 | Factuurhoofding: 20 lijnen van 50 tekens |
| 13308 | 243 | Vaste teksten op factuur: 3 lijnen van 80 tekens |
| 13551 | 2 (i) | Afstand tussen 1e printbare lijn en blokje waar FACTUUR komt (in regels) |
| 13553 | 2 (i) | Aantal lijnen in facturenblok die bovenaan leeg moeten blijven |
| 13566 | 2 (i) | Aantal lijnen dat cutter boven de printkop snijdt (Epson) |
| 13568 | 30×10 | Printerattribuutcodes (Epson TM-88T) |
| 13868 | 5×41 | Tekst op volle klantenkaart (via kasparm.exe) |
| 14073 | 80 | Pad voor TicketShare |
| 14153 | 80 | Pad voor LaserShare (brede facturen) |
| 14233 | 80 | Pad voor controleprinter (nog niet gebruikt) |
| 14313 | 5×41 | Tekst op tegoedbon indien te betalen < 0 (zie 3198) (via kasparm.exe) |

De lay-outtabellen (4608–8568) worden niet met upsys maar met `KASKEYS` aangepast (§6).

## 4. KASMENU.DAT

Tekstbestand dat de punten van het kassamenu bepaalt (1, 3, 4, 5, 9, A, N/K, T, M, …) en per punt de commando's die uitgevoerd worden. Openen met Kladblok (stel Kladblok niet in als standaardprogramma voor `.dat`).

Punt 1 ("Opstarten kassa-functie") in een hedendaagse installatie met JMD, opruiming en een betaalterminal ziet er zo uit (voorbeeld uit de bronnen):

```
start jmd.exe /min #A
jdel kl20*.dat -b -o365
jdel 20*.pdf -b -o31
ping 127.0.0.1 -n 5
rem atosctp.exe
rem cardfon.exe
start ingenico.exe
kassa.exe
start jmd.exe /min #C
ping 127.0.0.1 -n 2
```

- `start jmd.exe /min #A` vóór en `start jmd.exe /min #C` na `kassa.exe`: start resp. sluit de JMD op de achtergrond (nodig voor klantenkaarten via JMD en facturatie via JMD). Variant met volledig pad (enkel 32-bit): `start C:\Progra~1\Jamadata\JMD\jmd.exe /min #A`.
- `ping 127.0.0.1 -n x`: wachttijd van enkele seconden.
- Betaalterminal: net boven `kassa.exe` één lijn `banksys.exe`, `cardfon.exe` of `start ingenico.exe`; cashautomaat: `start antenor.exe #s` boven en `start antenor.exe #c` onder `kassa.exe`.
- `jdel kl20*.dat -b -o365` en `jdel 20*.pdf -b -o31`: ruimt maandelijkse kaslogs ouder dan 365 dagen en pdf's ouder dan 31 dagen op (kaslog per maand).
- Een menupunt uitschakelen (bv. punt A "Wissen van de verkoopgegevens" bij kaslog per maand): zet `/*` boven en `*/` onder dat punt.
- Menupunt N (lokale transfer met de hoofdcomputer [JMS]) of K (kassa op andere locatie, via Jamadata-server) wordt per klant ingesteld.
- Oudere installaties bevatten opruimlijnen met `jamadel` (tmp-/log-/temp-bestanden). Staan die als `REM`, dan zijn ze uitgeschakeld (o.a. als oplossing wanneer het Freedelity-scherm niet verschijnt).

## 5. JAMA.BAT

Opstartbatch op de kassa met de klantspecifieke instellingen:

- het kassanummer (kassa-01, kassa-02, …; variabele `JAMA-KASSA`);
- `set JMS=<IP-adres hoofdcomputer>` – het IP-adres van de hoofdcomputer waarop de JMS draait. Wijzigt dat IP-adres, dan werkt de dagelijkse transfer niet meer ("File not found…" en daarna "Are you connected to internet? (Y/N)") en moet deze lijn aangepast worden;
- bij oude netwerkinstallaties: `set net-drive=J` (driveletter van de data op de hoofdcomputer) en eventueel `use f: \\keytouch-01\hd-c`.

## 6. KASKEYS – lay-out van de systeemknoppen wijzigen

`KASKEYS` wijzigt de lay-out van de **systeemtoetsen** (niet de artikel-Key-conen; die beheert de klant zelf via V.2.2). In `KASSYS.DAT` staan 3 blokken die je kan aanpassen:

1. het kassascherm zelf;
2. het schermtoetsenbord (namen ingeven e.d.);
3. het scherm voor de betalingen.

Bediening (originele documentatie):

| Toets | Functie |
|---|---|
| Spatiebalk | Volgende van de 3 tabellen selecteren (bv. 2× spatie = betaalscherm) |
| HOME / END | Mode: enkel de toets onder de cursor tonen (HOME) of alle toetsen tonen (END) |
| Pijltjes, PgUp, PgDn | Toets selecteren |
| CTRL + pijltjes | Knop verplaatsen |
| ALT + pijltjes | Knop groter/kleiner maken |
| ALT + PgUp / ALT + PgDn | Inhoud (functie) van de knop wijzigen |
| INSERT | Nieuwe knop toevoegen (komt linksboven; in HOME-mode zie je het teken onder de cursor niet) |
| DELETE | Knop verwijderen (mag; wordt hergebruikt bij een volgende insert) |
| ESC | Bewaren en afsluiten. Niet bewaren = computer uitzetten |

Recentere versie (OneNote, 2024): klik/druk op de knop die je wil wijzigen; opnieuw drukken wisselt de kleur: **blauw** = verplaatsen met de pijltjes, **geel** = verkleinen/vergroten met de pijltjes. **F7** = functie kiezen uit de lijst (PgUp/PgDn om te scrollen). **Insert** = nieuwe knop, daarna verplaatsen en functie toekennen met F7. **Esc** en dan opslaan.

Let op: voeg je op het betaalscherm een code toe die daar niet verwacht wordt (bv. CLEAR), dan wordt de knop wel getoond maar doet hij niets.

Veelgebruikte toepassingen: knop KLT-KRT toevoegen (van het blokje GROEP het blokje KLT-KRT maken), betaalknop "Eigen tegoedbon", knop "Variabele betaalwijze", knop voor betaalautomaat/cashautomaat.

## 7. Knopcodes (KeyCoon-nummers)

Codes die in de lay-outtabellen en in KASKEYS gebruikt worden (decimaal):

| Nr | Knop | Nr | Knop | Nr | Knop |
|---|---|---|---|---|---|
| 0–9 | cijfers 0–9 | 10 | . | 11 | + |
| 12 | - | 13 | CLEAR | 14 | PLU |
| 15 | IDEM | 16 | VISA/MC/EC | 17 | x |
| 18 | Stoppen | 19 | Ticket | 20 | Diversen |
| 21 | GROEP | 22 | Terug | 23/24 | << / >> |
| 25 | WIS | 26–28 | Verk A / B / C | 29 | A.klt. |
| 30 | Korting | 31 | Kort. % | 32 | SUBTOT |
| 33 | E.P. | 34 | EINDE | 35 | VOLLEDIG |
| 36 | GELD | 37 | MAALTIJDCHEQUE | 38 | BON |
| 39 | EIGEN TeGoed-BON | 40 | BANCONTACT | 41 | EUROCHEQUE |
| 42 | STUKS | 43 | ALARM | 44 | Druk af |
| 45 | Gewenste dagen | 46 | Controle-band | 47 | Cumul per artikel |
| 48 | Cumul per groep | 49 | Cumul per BTW-% | 50 | Keuze periode |
| 51 | Neem deze parameters als standaard aan | 52 | AUTO-LGG | 53 | LG-TERUG |
| 54 | Horeca | 55 | Financ. overzicht | 56 | Factuur |
| 57 | Spatiebalk | 58 | Wis | 59 | DEL |
| 60 | INS | 61/62 | <- / -> | 63 | Volgend |
| 64 | Nieuwe klant | 65 | Zoek vlgs NAAM | 66 | Zoek vlgs KODE |
| 67 | Kleine factuur | 68 | Volgende | 69 | Vorige |
| 70 | Pas aan | 71 | Annuleer | 72 | Zoek andere |
| 73 | Vorig | 74 | 00 | 75 | 000 |
| 76 | Grote factuur | 77 | Leveringsbon | 78 | KREDIET |
| 79 | STAND-BY | 80 | Controle | 81 | Selecteer gewenste groepen |
| 82 | Selectie artikelen | 83/84 | << / >> | 85 | Aant.ex.ticket |
| 86 | Vr.Valuta | 87 | Schakel over | 88 | BAK |
| 89 | SNELKIEZEN | 90 | HOOFDMENU | 91 | KEYB |
| 92 | Selectie der verkopen | 93 | LEEGG=OK | 94 | Afsluiten kassier(ster) |
| 95–97 | Kassier(ster) A / B / C | 98 | Afdrukken kastoestand | 99 | Bewaren bon |
| 100 | Opladen bon | 101 | EAN | 102 | UITGAVE |
| 103 | INKOMST | 104 | TEST | 105 | CLR_TICKT |
| 106 | Selectie der kassier | 107 | % Alles | 108 | ZEGELS |
| 109 | Voeg EAN-nr toe | 110 | PROTON | 111 | Selecteer ticketten |
| 112 | OK | 113 | KLT-KRT | 114 | Sort |
| 115 | PRO-FORMA | 116 | AANTAL | 117 | LIJST |
| 118 | DETAIL | 119 | MARKEER | 120 | EINDE Z/N TICKET |
| 121 | BESTEL | 122 | Afdrukken controleband | 123 | Afdrukken bestellingen |
| 124 | EINDE met BTW-rek | | | | |

(De bronlijst stopt bij 124; nieuwere knoppen zoals "Variabele betaalwijze", "Betaalautomaat", "Mobiel", "Loyalty card Freedelity" staan er niet in.)

## 8. Oude netwerkinstallaties (legacy)

### 8.1 Transfer Win95-kassa ↔ Vista-hoofdcomputer (UCwin over TCP/IP)

Enkel relevant voor zeer oude installaties. Omdat de standaard netwerkverbinding door de Vista-beveiliging niet werkt, wordt de hoofdcomputer "standby" gezet om daarna vanaf de kassa door te sturen:

- Op de hoofdcomputer een menupunt in `menujama.jam`: "D Klaarzetten computer voor TRANSFER met kassa. (NETWERK)" met `ucwin -nHoofdcomputer -t:5000 -x`. De firewall vraagt om de blokkering op te heffen: toestaan. De computernaam moet gekend zijn.
- Op de kassa in `kasmenu.dat` een punt "N Dagelijkse TRANSFER met de HOOFDCOMPUTER [NETWERK-VISTA]" met `set server_drive=%net-drive%:` en `UCwin -fUCKASDAY.jam -n%JAMA-KASSA% -ekasmenu.bat -tserver:5000` (waarbij `server` = computernaam van de hoofdcomputer).
- In `jama.bat` op de kassa: `set net-drive=J` (liefst J, anders F).
- Voorzie de submappen onder kassa (`to` en `kassa-0x`). De verbinding is trager dan een gewone netwerkverbinding.
- Staat de map `kassa` niet in de root van een drive (bv. onder `c:\data\kassa`): zet in `jama.bat` `set net-drive=c:\data` en laat in `kasmenu.dat` de `:` weg. In `uckasday.jam` staat immers `%kas_drive%\kassa\KASPLU.DAT from} %server_drive%\kassa\KASPLU.DAT`.

### 8.2 Aansluitingen lichtpen en voedingsschakelaar Flash-kassa (zeer oud)

- Lichtpen: 1 = groen, 3 = zwart, 4–7 = brug ertussen met gele draad, 5 = rood, massa = zilveren massadraad aan chassis.
- Voedingsschakelaar Flash-kassa: 1A = zwart, 1 = bruin, 2 = wit, 2A = blauw.

## Bronnen

- `kassa/KASSYS.docx` (lokaties in de systeemfile KASSYS.DAT)
- `kassa/KASKEYS.docx`
- `kassa/KeyCoon.docx`
- `kassa/KASVISTA.docx`
- `kassa/AANSLUIT.docx`
- `kassa/HOWTO-Instellen KASLOG per MAAND.docx`, `kassa/INSTELLEN MAANDELIJKSE KL FILES (KASLOG) OP KASSA’S.docx`
- `kassa/HOWTO-Instellen INGENICO.docx`, `kassa/HOWTO-INSTALLATIE CASHAUTOMAAT ANTENOR.docx`, `kassa/HOWTO-Instellen FACTURATIE op kassa .docx`
- `kassa/Kassa installeren.docx`
- `Onenote/KASSA.pdf` (02 Knoppen aanpassen Keyconen kassa; 10 IP adres van hoofdcomputer klopt niet meer; 12 Kassa leegmaken voor verkoop)
- `Jamadrink/HOWTO-Mobiele kassa met draagbare printer.docx`
