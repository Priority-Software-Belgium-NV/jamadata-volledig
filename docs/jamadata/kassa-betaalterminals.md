# Kassa – Betaalterminals koppelen (Banksys/Worldline, Cardfon/CCV, Ingenico) en cashautomaat Antenor

Gebruik dit document voor: het koppelen van een betaalterminal (Bancontact) aan de Key-Conen kassa zodat het bedrag automatisch naar de terminal gaat, de instellingen op kassa en terminal per merk (Banksys/Atos Worldline, Cardfon/CCV, Ingenico), meerdere kassa's op één terminal, automatische extra kosten voor kredietkaarten, een knop "Variabele betaalwijze", de koppeling met een Antenor-cashautomaat, en de gekende storingen (transmissiefout, terminal blijft herstarten, WSA GET error, "Onverwacht bericht", COM-poortproblemen).

## 1. Principe (geldt voor alle merken)

De koppeling bestaat uit een klein koppelprogramma dat samen met de kassa opstart en met de terminal praat:

| Terminal | Koppelprogramma | Opstartlijn in `kasmenu.dat` (punt 1, net **boven** `kassa.exe`) |
|---|---|---|
| Banksys / Atos Worldline (ook Yomani, Keyware) | `banksys.exe` | `banksys.exe` |
| Cardfon / CCV | `cardfon.exe` | `cardfon.exe` |
| Ingenico | `ingenico.exe` (+ `IngenTlv.dll`, `IngenUti.dll`) | `start ingenico.exe` |
| Cashautomaat Antenor | `Antenor.exe` (+ `Antenor.cfg`, `AntenorD.dll`) | `start antenor.exe #s` boven en `start antenor.exe #c` onder `kassa.exe` |

Vaste stappen:

1. Haal `kassys.dat` en `kasmenu.dat` op van de kassa en maak er direct een kopie van (`*.old`).
2. In `kassys.dat`: `upsys kassys.dat` → `s 3368 len 32` zetten op **`localhost`** (kleine letters) – dit is de naam van de computer waarop de koppeling ("bancontact-server") draait.
3. In `kasmenu.dat` bij punt 1 de opstartlijn van het koppelprogramma toevoegen (zie tabel).
4. Stuur de aangepaste bestanden, het koppelprogramma en de laatste programmaversies (`KASSA.EXE`, `KASMENU.EXE`, `JAMACON.DLL`, `KEYCOONN.JAM`, `KASPARM.EXE`, `KASSCR.SCJ` – of gewoon de laatste `RUNONCE.KAS`) naar de kassa.
5. Start de kassa op en druk op de **Windows-toets** om het venster van het koppelprogramma te zien. Stel daar de juiste COM-poort (of TCP/IP) in.
6. Ontbreekt op de kassa een betaalknop voor de terminal, voeg die dan toe via KASKEYS (zie `kassa-configbestanden.md`).
7. **Vóór het testen: trek de terminal enkele seconden uit het stopcontact (reset).**

Voorbeeld van punt 1 in `kasmenu.dat` (Ingenico, met JMD):

```
start jmd.exe /min #A
jdel kl20*.dat -b -o365
ping 127.0.0.1 -n 5
start ingenico.exe
kassa.exe
start jmd.exe /min #C
ping 127.0.0.1 -n 2
```

### 1.1 Tweede of derde kassa op dezelfde terminal

- Geen aanpassing in `kasmenu.dat` op de extra kassa's (het koppelprogramma draait enkel op kassa 1).
- Wel in `kassys.dat` van de extra kassa: `s 3368 len 32` zetten op de **computernaam van de kassa waar de terminal aan hangt** (bv. `wintouch-01`, zonder `\\`).
- Op kassa 1: de Windows-firewall afzetten of **inkomende TCP-poort 4999 openen** (nodig vanaf de "AP"-kassa's, vermoedelijk Aerpos).

### 1.2 Algemene foutmeldingen van de koppeling

| Melding / symptoom | Oorzaak en oplossing |
|---|---|
| `WSA GET error = 11002` | Het bestand `hosts` bestaat niet of bevat geen verwijzing van localhost naar 127.0.0.1. Kopieer `hosts.sam` naar `hosts`. |
| `WSA GET error = 11001` | Meestal op een tweede kassa die naar de eerste kassa gekoppeld is: de computernaam (positie 3368) wordt niet gevonden of is fout. |
| COM-poort bezet | Als ActiveSync op de kassa staat, kan die de COM-poort bezet houden: bij de instellingen van ActiveSync deze COM-poort uitzetten. |
| "Onverwacht bericht" van de terminal | De terminal is nog niet volledig opgestart. Werkt het na enkele minuten nog niet: de betaalterminal en/of de kassa herstarten. |
| Firewall-melding bij TCP-koppeling | "Toestaan" kiezen. |

## 2. Banksys / Atos Worldline

Kan op alle kassa's met de Windows-versie van het kassaprogramma. Bestanden kunnen klaargezet worden met `getbs.bat`.

### 2.1 COM-poort op de kassa (venster van banksys.exe)

| Kassa | COM-poort |
|---|---|
| Glaive | liefst COM2 |
| Rich-Pos | COM5 (COM2 werkt daar niet) |
| PanelPos / PanelPC | COM4 |

### 2.2 Instellingen op de terminal

De terminal moet op het kassaprotocol **VIC** staan ("VIC ticket ECR": de terminal heeft zelf geen printer; het ticket komt uit de kassa).

Kassaprotocol **aanzetten** (terminal waarop men voordien zelf het bedrag intikte):

1. STOP – OK – MENU – 3 – 0 – 9 – (wachtwoord: zie interne bron) – OK – 4 – 2 – "wijzigen"
2. Kies **8 = NVIC (new VIC)**
3. OK – OK – OK
4. Enkele keren STOP. De terminal herstart automatisch.

Kassaprotocol **afzetten** (terug zelf het bedrag intikken):

1. STOP – OK – MENU – 3 – 0 – 9 – (wachtwoord) – OK – 4 – 2 – "wijzigen"
2. Kies **1 = None** (geen verbinding met kassa)
3. OK – OK, dan enkele keren STOP.

Ticket van de terminal afzetten (apart voor Bancontact en Proton): STOP – OK – MENU – 1 (Worldline) – 4 (Parameters) – 4 (Kaartparameters) – wachtwoord van de terminal (zie interne bron) – 1 (Bancontact) – 7 Ticket – "GEEN"; idem 2 (Proton) – 7 Ticket – "GEEN".

Krijg je enkel een toon als je op MENU drukt: als "Types" en "Manueel" niet op het scherm staan, druk dan eerst STOP en daarna OK om ze weer te geven; pas dan MENU. (Komt meestal voor als er maar één toestel is.)

### 2.3 Gekende problemen

- **"Transmissiefout" zodra de klant zijn kaart insteekt, terwijl het bedrag wel doorkomt** (en het wél werkt als de kaart ingestoken wordt vóór het bedrag op de terminal staat, of bij contactloos betalen):
  - de parameter **"State Information"** staat fout: moet op **"By ECR"** staan, niet op "Always ECR". Dit is één van de parameters die je tegenkomt tussen de OK's na het instellen van het protocol op NVIC; of
  - de koppelingskabel zit in de verkeerde aansluiting van de terminal (de internetaansluiting).
- Terminal van **Keyware**: zou moeten lukken met een Yomani met dezelfde instellingen als bij Atos/Worldline zelf.
- **Manueel verrichtingen doen terwijl de terminal gekoppeld is**: de bron vermeldt de vraag maar geeft geen procedure (onzeker / te verifiëren).

## 3. Cardfon / CCV

Bestanden kunnen klaargezet worden met `getcard.bat`. Algemene stappen zie §1; COM-poort in het cardfon-venster instellen (liefst COM2 op oude kassa's).

- Het kan zijn dat de klant op het keypad van de terminal nog steeds de knop "transactie" moet nemen.
- **Compatibele toestellen** (info CCV, februari 2025): koppelbaar via het 2-step-protocol zijn de **A80-A35** en **A80-P400**; CCV ondersteunt dit protocol nog enige tijd. De **A77** is **niet** koppelbaar met een kassa.
- De **A80** werkt serieel (getest op COM4, zonder omzetting); via USB is niet getest. Op XP-kassa's werkte hetzelfde toestel niet serieel.
- **USB-toestel van CCV (VX 520)**:
  1. Download de driver op de supportpagina van CCV (ccv.eu → service → support → drivers).
  2. Pak uit en voer de setup uit; die installeert de USB-driver die USB omzet naar **COM9**.
  3. Sluit pas daarna het toestel via USB aan.
  4. Zet in het venster van de koppeling de poort op COM9 en test (controleer in Apparaatbeheer).
- **Probleem met de seriële koppeling**: ga in Apparaatbeheer naar de COM-poort waar de terminal aan hangt en zet **databits op 7** en **pariteit op even**.

## 4. Ingenico

Kan op alle Aerpos-kassa's en nieuwere met de laatste kassaversie. Bestanden kunnen klaargezet worden met `geting.bat` (`IngenTlv.dll`, `IngenUti.dll`, `INGENICO.EXE`, `RUNONCE.KAS`, `KASMENU.DAT`, `KASSYS.DAT`).

- Op Aerpos-kassa's moet **.NET Framework 4** geïnstalleerd zijn.
- **Vanaf 1/7/2022: enkel nog TCP/IP-verbindingen** (geen seriële of USB-koppeling meer).

### 4.1 Instellingen op de kassa (venster van ingenico.exe, via Windows-toets)

1. `Ingenico.exe`, `IngenTlv.dll` en `IngenUti.dll` in de map kassa zetten.
2. Start `Ingenico.exe`.
3. Verbinding instellen: normaal **TCP/IP**. (Historisch: serieel liefst COM5 op Aerpos, COM4 op PanelPos/PanelPC; USB: in Apparaatbeheer kijken welke COM-poort, op PanelPC meestal COM7. Verschijnt de COM-poort niet: de Ingenico-USB-driver installeren.)
4. Manager-wachtwoord instellen (zie interne bron).
5. Zijn de settings "gelocked": ontgrendelen door de unlock-code in het tekstvakje rechtsboven in te vullen (code: zie interne bron; kopiëren/plakken is het eenvoudigst).
6. Bij TCP: bij de melding van de firewall "toestaan" kiezen.

### 4.2 Instellingen op de terminal

1. Druk op het toetsenbord van de terminal op **F**.
2. Geef het "settings"-wachtwoord in (zie interne bron).
3. Kies het icoon **"Kassa Menu"** (linksonder) → **"Settings Menu"** → **"Change connection"** (bevestigen met het gele pijltje rechts of de groene OK-knop).
4. Instellen op:
   - **TCP**: het IP-adres van de kassa en poort **10000** (standaard);
   - (historisch) USB: Serial – USB – 9600 – 8 – None – 2 – rts;
   - (historisch) COM-poort: Serial – COM0 – 9600 – 8 – None – 2 – rts.
5. De terminal vraagt om te herstarten: bevestigen.

### 4.3 Maaltijdcheques (Sodexo, Edenred, Monizze) toevoegen op de terminal

1. Eerst de UID van de uitgever (bv. Sodexo) doorgeven aan Ingenico.
2. TMS-call: F → wachtwoord → "Tech Menu" → "TMS Session". Antwoord normaal "TMS session OK".
3. Acquirer-parameters: F → wachtwoord → "C-TAP" → "Acquirer Menu" → "Parameter Download" → bv. "Sodexo", "Edenred" of "Monizze" kiezen → OK.

UID vervangen (eerst Ingenico verwittigen van de nieuwe UID): F → CTAP → Service Menu → wachtwoord + groen → "Wissen C-TAP DB" + groen → bevestigen met groen → de terminal herstart → TMS-sessie starten → parameters downloaden in het Acquirer Menu.

Opmerking: via de koppeling is enkel de elektronische maaltijdcheque (lunch pass) voorzien, geen ecocheques of cadeaucheques. Moeten die aanvaard worden, dan zijn daar aparte betaalmiddelen (knoppen) voor nodig op de kassa.

### 4.4 Gekende problemen

**Terminal blijft herstarten** (komt meestal voor na een foute verrichting):

Oplossing A:
1. De koppeling uitzetten op de terminal (TCP/IP).
2. Eventueel de koppeling op de kassa afsluiten (niet strikt nodig).
3. Eén **manuele verrichting** uitvoeren op de terminal.
4. De koppeling terug aanzetten op de terminal (en op de kassa indien afgesloten).

Oplossing B (als A niet helpt; meermaals de oplossing gebleken):
1. Stop het kassaprogramma en ingenico.exe zodat de terminal zich niet meer reset.
2. Op de terminal: F → CTEP/C-TAP → Acquirer Menu → wachtwoord (zie interne bron).
3. Kies de 3e lijn "Parameters download"; je krijgt meerdere items (bv. 2 acquirers).
4. Kies ze één na één en druk telkens op download (na elke download gaat hij een niveau hoger).
5. STOP op de terminal zodat hij weer klaarstaat.
6. Kassaprogramma opstarten en testen.

Andere pistes: het IP-adres van de kassa wijzigen (bij TCP/IP) en eventueel IPv6 uitzetten; lukt het niet, de support van Ingenico contacteren. In hetzelfde incident gaven de terminals ook de melding "TDR database vol" (betekenis onbekend).

**Seriële problemen** (historisch): een storend apparaat in Apparaatbeheer uitschakelen en de kassa herstarten (het betrokken apparaat staat enkel als afbeelding in de bron – te verifiëren); ActiveSync kan de COM-poort bezet houden.

## 5. Automatisch extra kosten aanrekenen voor kredietkaarten (VISA)

1. Maak een artikel aan, bv. PLU 98999, omschrijving "Kost% kredietkaart", met als **eenheidsprijs de factor** (bv. 0,02 = 2 %). De btw-code overlegt de klant met zijn boekhouder; de groep maakt niet uit.
2. Zet in `kassys.dat` op positie **3406** (string) het PLU-nummer (5 tekens) van dat artikel.
3. In de kassaparameters (kasparm) staat ook een **bedrag waaronder de extra kosten aangerekend worden** (positie 3417); 0 = uitgeschakeld.

Werking: bij betaling met kredietkaart zoekt de kassa het artikel van positie 3406 op en voegt de kost toe volgens de factor. Voorbeeld uit de bron: verkoop 3,20 EUR, de klant betaalt 50 EUR met VISA → te betalen 4,20 EUR; er gaat 50 EUR van de kaart en hij krijgt 45,80 EUR terug.

**Kredietkaarten via de knop "Betaalautomaat" toelaten**: `kassys.dat` positie 3415 (c), in te stellen via KASPARM bij Diverse parameters: "CREDIT-kaarten toelaten via de knop Betaalautomaat".

## 6. Knop "Variabele betaalwijze" (bv. gemeentecheques)

Voor een betaalmiddel waarvoor geen standaardknop bestaat (max. 3 variabele betaalwijzen):

1. Voeg met **KASKEYS** op het betaalscherm een knop "Variabele betaalwijze" toe (F7 = functie kiezen) en sla op (zie `kassa-configbestanden.md` §6).
2. Start **Kasparm** en druk F8 tot je de "tekst variabele betaalwijze" kan aanpassen; vul de tekst van de knop in (bv. "gemeente cheques").
3. Zet de benaming ook juist in de JMD: vanuit het voorraadmenu **2, +, +, F8, F8** → benaming invullen → F8.
4. Zet de boekhoudrekening juist (indien de klant het kasverslag inboekt): **2, 4, +** → rekening invullen → F8. Weet je de rekening niet, vraag ze aan de klant.

## 7. Cashautomaat Antenor

1. Vraag aan Antenor het IP-adres van de machine bij de klant.
2. Open `Antenor.cfg` met Kladblok en pas de communicatie-instellingen aan (IP-adres). **Het poortnummer moet op 4998 blijven.**
3. Mee te geven bestanden: `KASSA.EXE`, `Antenor.exe`, `Antenor.cfg`, `AntenorD.dll`, `Kassys.dat`, `Kasmenu.dat`.
4. Haal `kassys.dat` en `kasmenu.dat` op van de klant (map `fromKLT\<klantcode>`, submap config; hernoem ze terug naar de naam zonder voorvoegsel) en maak een kopie (`*.old`).
5. `Upsys32 kassys.dat` → `s 3368 len 32` op `localhost`.
6. Voorzie een betaaltoets via KASKEYS.
7. `kasmenu.dat` aanpassen met Kladblok: net boven `kassa.exe` de lijn `start Antenor.exe #s`, net onder `kassa.exe` de lijn `start Antenor.exe #c`:

   ```
   start jmd.exe /min #A
   jdel kl20*.dat -b -o365
   ping 127.0.0.1 -n 5
   start antenor.exe #s
   kassa.exe
   start jmd.exe /min #C
   start antenor.exe #c
   ping 127.0.0.1 -n 2
   ```

8. Na de installatie de config-file aanpassen met de juiste gegevens voor de communicatie.

Verwante instelling: `kassys.dat` positie 3196 (i) "NIET automatisch geld teruggeven indien bedrag negatief (cashautomaat)".

## Bronnen

- `kassa/HOW TO instellen Bancontact.docx` (samenvatting Banksys/Cardfon/Ingenico)
- `kassa/HOWTO-Instellen BANKSYS.docx`
- `kassa/HOWTO-Instellen CARDFON.docx`
- `kassa/HOWTO-Instellen INGENICO.docx`
- `kassa/HOWTO-INSTALLATIE CASHAUTOMAAT ANTENOR.docx`
- `kassa/KASSYS.docx` (posities 3196, 3368, 3406, 3415, 3417)
- `Onenote/KASSA.pdf` (03 Variabel betaalwijze knop; 13 COM instellingen CCV; Foutmelding "Onverwacht Bericht" van Terminal)
