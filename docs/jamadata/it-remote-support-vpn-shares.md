# Remote support, VPN, Jamadata Share en netwerkschijven

Gebruik dit document voor: het overnemen van het scherm van een klant (LogMeIn Rescue, TeamViewer, oudere kassa's), de supportwebsites en downloadlocaties, onbeheerde toegang, werken op afstand via ComfortLink en de VPN-omweg in het buitenland, de Jamadata Share, het opnieuw koppelen van een netwerkschijf (T-schijf) en het wijzigen van de stationsletter van een USB-apparaat.

Wachtwoorden, logins, dossiernummers en VPN-adressen staan bewust niet in dit document (zie interne bron).

## 1. Supportwebsites en downloadlocaties

| Adres | Waarvoor |
|---|---|
| `kb.jamadata.be` | Servicepagina voor de klant: TeamViewer starten, LogMeIn, WMDC (driver Windows Mobile Apparaatcentrum voor PDA's), "Support oude kassa's". Vanuit de Jamadata-vestiging zelf oproepen als `kb.jamadata.be:81`. |
| `help.prsw.be` | Nieuwste TeamViewer starten voor schermovername. |
| `www.logmein123.com` | LogMeIn Rescue: de klant geeft hier de zescijferige pincode in. |
| `fl.prsw.be` | Zelfde resultaat als de knop "Verbinden met technicus" in Jamadata Desktop (ingave pincode). |
| `jmdn.prsw.be` (ook `www.fl.be/jmdn`) | Installatiebestand Jamadata Desktop (JMD). Gebruik `jmdn.prsw.be` als de andere link niet werkt (o.a. bij Telenet-klanten). |
| `jmsn.prsw.be` | Installatiebestand Jamadata Server (JMS). |
| `svc.jamadata360.be` | Interne monitoring (SVC) van alle klantinstallaties: heartbeat, backup, fouten. Login: zie interne bron. Zie `server-jms-storingen.md`. |

WMDC (Windows Mobile Apparaatcentrum) verzorgt de verbinding tussen PDA en de lokale computer. Het geeft regelmatig problemen; als er geen verbinding is, moet de software opnieuw geïnstalleerd worden (details: PDA-documentatie).

## 2. Welke overnametool voor welk toestel

| Toestel | Besturingssysteem | Overnemen met |
|---|---|---|
| Werkpost / server | Windows 10/11 | LogMeIn Rescue (of TeamViewer) |
| Kassa PANELPOS | Windows 10 IoT | LogMeIn |
| Kassa AIRPOS | POSReady 7 (Windows 7) | LogMeIn |
| Kassa RICHPOS | POSReady 2009 (Windows XP SP3) | TeamViewer |
| Kassa GLAIVE (oude kassa's) | Windows Embedded XP SP1 | AMMYY |

Oude kassa's (GLAIVE): open op de kassa zelf `kb.jamadata.be` in de webbrowser en kies "Support oude kassa's". Niet via Google Chrome openen, wel via de Windows-browser (Internet Explorer).

## 3. LogMeIn Rescue Technician Console

### Schermindeling
- Bovenaan: lijst van de geopende sessies.
- Infovak: allerlei info, o.a. de pincode die aan de klant moet worden doorgegeven.
- Linksonder: chatvenster met de klant.

### Nieuwe sessie starten
1. Klik op **Nieuwe sessie**.
2. Vul in het veld **Name** een betekenisvolle omschrijving in (klantcode van 3 letters of naam van de klant). Belangrijk wanneer meerdere sessies tegelijk openstaan.
3. Klik op **Pincode creëren**. De pincode verschijnt ook linksboven in het infovak.
4. Geef de pincode door aan de klant. De pincode is **20 minuten** geldig. Daarna mag het venster "Nieuwe sessie maken" gesloten worden.

### Wat de klant doet
- In Jamadata Desktop: tabblad **Configuratie** > **Verbinden met technicus** (opent de juiste website).
- Lukt dat niet: `fl.prsw.be` (zelfde scherm) of `kb.jamadata.be` (keuzepagina met TeamViewer / LogMeIn / WMDC / Support oude kassa's).
- De klant geeft de code in en moet het **gedownloade .exe-bestand uitvoeren**. Klanten merken de download vaak niet op (afhankelijk van de browser staat het bestand bv. onderaan het browservenster).

### Sessie activeren en rechten verkrijgen
1. Na ingave van de code verschijnt een sessielijn met status **Bezig met wachten**.
2. Activeer de sessie: dubbelklik op de lijn, of selecteer ze en klik op **Start Session**. Status wordt **Geactiveerd**.
3. Klik **eerst** op de knop om alle machtigingen (beheerdersrechten) te verkrijgen. De klant krijgt de Windows-vraag "Do you want to allow this app to make changes to your device?" en moet **Yes** antwoorden.
4. Klik pas **daarna** op de knop om het scherm over te nemen. De klant krijgt nog een vraag en moet op **OK** klikken.

**Veelgemaakte fout:** meteen het scherm overnemen zonder eerst de machtigingen te vragen. Dan heb je niet altijd de nodige rechten op de pc van de klant. Oplossing: zet de sessie op pauze (status **Onderbroken**), dubbelklik opnieuw op de sessielijn, klik eerst op de machtigingenknop en dan opnieuw op de knop voor schermovername.

### Sessie delen of overdragen
- Rechtermuisklik op de sessielijn > **Technicus uitnodigen** > kies de medewerker > OK: de collega kijkt mee.
- Rechtermuisklik > **Overdragen**: de sessie volledig overdragen (in plaats van meekijken).

### Mogelijke acties in een sessie
| Actie | Uitleg |
|---|---|
| Bestandsbeheer | Links de mappen van de technicus, rechts die van de klant (bestanden overzetten). |
| Systeeminfo | Systeeminformatie van de pc van de klant. |
| Scripts | Wordt (nog) niet gebruikt. |
| Onbeheerde toegang | De klant geeft toegang voor een (bepaalde) periode; je hoeft dan niet telkens met codes te werken en de klant te storen. |
| Calling card | Wordt niet gebruikt. |
| Geschiedenis en notities | Duur van de sessies; eigen notities toevoegen. |

### Probleem: onbeheerde toegang activeren mislukt
Als onbeheerde toegang (Unattended Access) vroeger al eens ingesteld was op die computer maar mislukt is, moet eerst de oude service verwijderd worden:
1. Open `services.msc`.
2. Zoek de oude Rescue-service, naam in de vorm `LMIRescueUA_<nummer>` (kijk in de **details/eigenschappen** voor de exacte servicenaam).
3. Kopieer de servicenaam.
4. Open een opdrachtprompt (als administrator) en voer uit: `sc delete LMIRescueUA_<nummer>`.
5. Stel de onbeheerde toegang opnieuw in; nu zou de activatie moeten lukken.

### Probleem: LogMeIn valt steeds weg
De SSL-filter op de hardware-firewall van de klant moet uitgezet worden.

### Remote Desktop gebruiken om LogMeIn te installeren
Log via Remote Desktop aan met de console-/adminsessie zodat LogMeIn nadien werkt zonder dat de RDP-sessie aangemeld moet blijven: start met `mstsc /admin`.

## 4. Aandachtspunten bij werken op het systeem van de klant

- Zie `server-jms-overzicht-en-vereisten.md` voor de mappenstructuur `J:\jamadata`.
- De map `Restore` **nooit zomaar gebruiken**: die dient om een back-up terug te zetten.
- Een manuele back-up vanuit Jamadata Desktop **nooit remote starten**; altijd lokaal, liefst op de server van de klant.
- Sluit op de server de Jamadata Desktop af vóór je afmeldt of van Windows-gebruiker wisselt. Blijft Post 1 open onder jouw gebruiker, dan kan de klant die post onder zijn eigen gebruiker niet meer openen (uit opleiding, 01/06/2026).
- Sluit geen vensters of verbindingen die de klant of zijn IT-partner had openstaan (bv. hun eigen remote-sessie).
- Er bestaat een interne map met kassabeschrijvingen per klant (technische fiche: kassasysteem, hardware, installatiedatum, onderhoudscontract, aangesloten printers en scanners). Raadpleeg die vóór een interventie op een kassa en wijzig ze niet onzorgvuldig.

## 5. Werken op afstand: ComfortLink

**Waarvoor:** met Jamadata Desktop van buiten het bedrijf werken (thuis, tweede locatie) via de verbindingsserver van Jamadata.

**Instellen op de werkpost:** Jamadata Desktop > menu **Configuratie** > **Instellingen**:
- Vink aan: "Zet vinkje wanneer u buiten het bedrijf wenst te werken."
- Vul bij **Dossiernummer** het dossiernummer in dat de klant van een Jamadata-medewerker gekregen heeft.

**Waar vindt support het dossiernummer / de ComfortLink-code?** In het `JMS.ini`-bestand van de klant (lokaal `J:\jamadata\prog\jms.ini`; intern in de kopie van de klantconfiguratie op de back-upserver, map `FromKLT\<klantcode>\...`). Behandel dit bestand vertrouwelijk: het bevat ook serienummers en wachtwoorden.

**Netwerkvoorwaarde:** uitgaande TCP-poort **5006** moet open staan op de pc die op afstand werkt. Standaard staat die open, tenzij een hardware-firewall ze blokkeert.
- Test: `telnet jmm1.jamadata.be 5006` moet een streepje (leeg scherm met cursor) geven.
- Maakt "werken op afstand" geen verbinding: uitgaande poort 5006 openzetten op die pc / in de hardware-firewall.

**Afdrukken en grote bestanden op afstand:** een zeer groot bestand (bv. een statistiek van enkele GB) wordt op afstand niet doorgestuurd/afgedrukt. Het blijft dan staan in `J:\jamadata\Spool\ToClient\Post-xxx\` en moet daar verwijderd worden (zie `server-jms-storingen.md`).

## 6. ComfortLink werkt niet in het buitenland: VPN

**Probleem:** de firewall van Jamadata blokkeert alle buitenlandse IP-adressen, waardoor de ComfortLink in het buitenland niet werkt.

**Oplossing:** een VPN-verbinding leggen met de Jamadata-server.
1. Vraag bij de interne IT-dienst een gebruiker en wachtwoord aan voor de VPN (WatchGuard).
2. Log in op het VPN-portaal (adres en domein: zie interne bron). Let op: bij het inloggen moet het juiste authenticatiedomein gekozen worden.
3. Na het inloggen: **Download client voor Windows**.
4. Installeer de client (Next, Next, ... Finish) en kies **Install** voor de TAP-driver.
5. Open de Mobile VPN-client en log in met de gekregen gegevens. Vergeet niet het domeinvoorvoegsel vóór de gebruikersnaam te zetten (`<domein>\<gebruiker>`).
6. Start daarna Jamadata Desktop met de ComfortLink-instellingen.

Bron: "HOWTO- JMD-VPN Login buitenland.docx" (map Jamadrink; "JMD-VPN Login buitenland.docx" is een dubbel).

## 7. Jamadata Share

**Wat:** een Windows-share op de computer waar de Jamadata Server draait, waar externe pakketten of apparaten hun data kunnen ophalen of wegschrijven. Op schijf is dit de map `J:\jamadata\Share`. Ze wordt ook gebruikt om bestanden over het hele netwerk te delen (bv. Excel-documenten die door meerdere personen ingevuld worden).

**Verbinden:** ga in Windows Verkenner naar de pc van de Jamadata Server; de share is daar zichtbaar. Om te verbinden is bijna altijd een gebruikersnaam en wachtwoord nodig: gebruik de vaste Jamadata Share-gebruiker (gebruikersnaam en wachtwoord: zie interne bron; let op hoofdlettergevoeligheid van het wachtwoord).

Bron: "HOWTO-Jamadata Share aanmaken.pdf" (map Jamadrink). Het document beschrijft enkel het verbinden, niet het aanmaken van de share zelf.

## 8. Netwerkschijf (T-schijf, Tomra) is verdwenen

(uit opleiding, opname "Terug een t schijf aanmaken"; gesproken bron)

**Symptoom:** op een kassa werkt het inlezen van tickets van de flessenautomaat (Tomra) niet meer; in "Deze computer" is de T-schijf weg. Typisch na een stroomonderbreking: de netwerkverbinding is verbroken.

**Oplossing:**
1. Open Verkenner > **Deze computer** > **Netwerkverbinding maken**.
2. Kies stationsletter **T** (de T van Tomra).
3. Kies als map de share van de flessenautomaat. Weet je het pad niet: kijk op een andere kassa of pc waar de T-schijf nog bestaat welk netwerkpad daar gebruikt wordt.
4. Laat **Opnieuw verbinden bij aanmelden** aangevinkt en klik **Voltooien**.
5. Controleer dat de bestanden zichtbaar zijn op T: en test opnieuw met een ticket.

## 9. Stationsletter van een USB-stick of externe schijf wijzigen

**Wanneer:** Windows herkent de (back-up-)USB-stick niet meer, soms zelfs dezelfde stick op dezelfde pc een dag later. Oorzaak: de stick wordt als harde schijf gezien en krijgt een stationsletter die al in gebruik is. Voor Jamadata is dit belangrijk omdat het back-uppad (`CopyPath` in `JMS.ini`, meestal `S:\jamadata\Copy`) naar een vaste letter verwijst.

**Stappen:**
1. Configuratiescherm > **Systeembeheer** > **Computerbeheer**.
2. Onder **Opslag** kies **Schijfbeheer**.
3. De USB-stick staat als volume in de lijst. Rechtermuisklik op het volume > **Stationsletter en paden wijzigen**.
4. Geef het volume de stationsletter die voorheen gebruikt werd.
5. Normaal herkent de computer de stick nu weer en kan de back-up opnieuw lopen.

Bron: "Veranderen driveletter USB-apparaat.pdf" (map IT; de .docx bevat enkel afbeeldingen).

## 10. Hulpmiddelen bij Windows-accounts op klantsystemen

- **User `jamadataserver`:** bij elke serverinstallatie wordt een Windows-gebruiker `jamadataserver` aangemaakt. Het wachtwoord is af te leiden uit `JMS.ini` (zie interne bron). Hiermee kan support aanmelden op de server ook als de wachtwoorden van de gewone gebruikers niet gekend zijn. Dit wordt niet aan de klant meegedeeld.
- **Administratorwachtwoord vervalt (Windows Home):** bij een klant had de administrator geen wachtwoord, maar het account stond op "expires". Op Windows Home (Premium) is dat enkel aan te passen vanuit een opdrachtprompt of PowerShell met administratorrechten.
- **Administrator verdwenen op het aanmeldscherm (Windows XP):** wordt een gebruiker met beheerdersrechten toegevoegd, dan toont XP de Administrator-account niet meer. Op te lossen met een autologon-/registertweak (oude installaties).

## Bronnen
- IT: "LogMeIn Rescue Technician Console.docx"
- IT: "logmein_activeren onbeheerde toegang mislukt .docx"
- IT: "Veranderen driveletter USB-apparaat.pdf" (en .docx)
- FAQ: "Opleiding Helpdesk Jamadata.docx"
- FAQ / Jamadrink: "FAQ Jamadata SERVER.docx"
- Jamadrink: "HOWTO- JMD-VPN Login buitenland.docx", "JMD-VPN Login buitenland.docx"
- Jamadrink: "HOWTO-Jamadata Share aanmaken.pdf"
- Jamadrink: "Installatie jamadata Dektop 2.0.docx"
- Jamadrink: "Jamadata FAQ's.pdf"; Onenote/FAQ: "Support.pdf"
- Transcripties opleidingen: "Terug een t schijf aanmaken.txt", "[klant]_Migratie_20260601_162649.txt"
