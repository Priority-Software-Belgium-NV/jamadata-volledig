# FAQ: server, werkposten en algemene helpdeskvragen

Gebruik dit document voor: snelle antwoorden op terugkerende helpdeskvragen rond de Jamadata Server en werkposten (verbinding, "wachten op serversessie", FOUT 01, geblokkeerd bon-/factuurnummer, afdrukken via netwerkprinter, updates, licentie-/registratiecodes) en voor de algemene werkwijze van de helpdesk (ticketintake, wat je nooit doet). Elke rubriek verwijst naar het detaildocument.

Niet in dit document: Peppol, e-mail/SMTP, kassa-installatie, PDA/scanners/printers-installatie en boekhouding (zie de documenten met die prefixen).

## 1. Wegwijzer

| Vraag | Document |
|---|---|
| Jamadata Desktop installeren, serverinstallatie, firewallregel | `installatie-desktop-en-draaiboek.md` |
| Verhuizen naar nieuwe server / cloud | `installatie-migratie-naar-nieuwe-server.md` |
| Wat is JMS/JMT/JMR, mappen, `JMS.ini`, poorten, systeemvereisten, Mono/Light/Server | `server-jms-overzicht-en-vereisten.md` |
| SVC, foutmeldingen, crashes, JMS herstarten, updates | `server-jms-storingen.md` |
| Back-up maken, back-up komt niet door, restore | `backup-en-herstel.md` |
| Scherm overnemen, ComfortLink, VPN, Share, T-schijf, USB-letter | `it-remote-support-vpn-shares.md` |
| GDPR: inzage, export, schrappen | `it-gdpr-richtlijnen.md` |

## 2. Verbinding en opstarten

### Jamadata Desktop blijft staan op "Wachten op serversessie"
(kennisartikel KA-002, gedeeltelijk gevalideerd)
1. Controleer in Jamadata Desktop (**Configuratie > Instellingen**) het ingestelde **IP-adres van de server** en vergelijk met het vaste IP-adres van de server. Pas enkel aan als het aantoonbaar fout is.
2. Controleer netwerk en bereikbaarheid. Een geslaagde ping bewijst niet dat de Jamadata-verbinding werkt.
3. Controleer op **dubbele postnummers** (twee pc's of twee Windows-gebruikers met hetzelfde postnummer; een post die nog openstaat onder een andere gebruiker op de server).
4. Draait de server? (SVC: heartbeat; op de server: Taakbeheer `JMS`, services JMT/JMR.) Zo nodig JMS herstarten (`server-jms-storingen.md` §4).
5. Firewall op de server: inkomend TCP 5000-5005 en 5100-5130, regel "Jamadata Server"; eventueel ook op de hardware-firewall. Virusscanner met eigen firewall (bv. Avast): regel toevoegen voor 5000-5006 en 5100-5130.
6. Na een stroomonderbreking of routerreset: mogelijk gewijzigd IP-adres van de server (hoort vast te zijn).

### Bij Light kan niemand werken
De Light-versie draait in user mode: op de hoofdcomputer moet de Windows-gebruiker **aangemeld** zijn. Aanmelden en zo nodig het Jamadata Server-icoon dubbelklikken.

### "FOUT 01 bestand niet gevonden op deze computer"
Hoofdmenu punt **6** bekijken:
- één lijn op "FOUT": de klant heeft waarschijnlijk per ongeluk een parameter gewijzigd; nakijken via **+ > 2**;
- alle lijnen op "FOUT": JMS herstarten via de JMT (`server-jms-storingen.md` §4.2).

### Op alle werkposten staan maar stukken tekst van het menu
Bij één klant opgelost door de Jamadata Server als Light te installeren; de server had daar geen Windows-wachtwoord.

### Werken op afstand (ComfortLink) lukt niet
Uitgaande poort 5006; test `telnet jmm1.jamadata.be 5006`. In het buitenland: VPN. Zie `it-remote-support-vpn-shares.md` §5-6.

### Kassa kan niet doorsturen naar de hoofdcomputer ("Bent u verbonden met het internet? Retry? (Y/N)")
Mogelijke oorzaak: netwerkprofiel van de server staat op Publiek; op Privé zetten. Controleer ook de firewallregel 5000-5005 (bereik/IP van de kassa). Zie `server-jms-storingen.md` §3.

## 3. Dagelijks gebruik

### Wie is er nog aan het werken?
Hoofdmenu **+ > J > T** toont de actieve gebruikers (F7 = vernieuwen). Gebeurt er niets bij T, dan is er niemand meer bezig. Nodig vóór een update, herstart, manuele back-up of migratie.

### Bon- of factuurnummer is geblokkeerd
Hoofdmenu > **tandwiel** (masterfuncties) > punt **3** > **F10 "Wis blokkage bon/factuurnummer"**.

### Masterfuncties (groen tandwiel-icoon rechts onderaan het hoofdmenu)
Bekende punten: **2** = volledige back-up op USB-stick, **3** (met F10) = blokkage bon-/factuurnummer wissen, **5** = controleer op nieuwe update. De masterfuncties worden per werkpost geactiveerd via **+ > J > 4** (Instellingen werkposten).

### Instellingen onder + > J (JMS-instellingen)
| Punt | Inhoud |
|---|---|
| **+ . J . 1** | Afdrukposten / printers (printer moet op de server geïnstalleerd zijn; kies via het vergrootglas) |
| **+ . J . 2** | Document-eigenschappen (lay-out, papiersoort en standaard afdrukpost per document) |
| **+ . J . 3** | Papiersoorten (F10 voor de papierinstellingen) |
| **+ . J . 4** | Instellingen werkposten (postnummers, masterfuncties, "Gebruik EML als e-mailstandaard") |
| **+ . J . 5** | E-mailinstellingen (F8; F10 = relay-instellingen) |
| **+ . J . T** | Actieve gebruikers |

### Mededelingen / updateberichten lezen
**+ > B (Bekijken/afdrukken brieven)**; F8 op een boodschap toont de inhoud.

### Update installeren
Geel scherm bij het opstarten, of **tandwieltjes > 5**. Daarna in Jamadata Desktop: **Configuratie > Nieuwe versie installeren**. Zie `server-jms-storingen.md` §5.

### PDF van meerdere schermen maken
Rechtermuisklik > "Schermafdruk naar PDF-document" (herhalen per scherm) > "PDF-document aanmaken en openen".

### Lijst van alle geblokkeerde artikels in Excel
Hoofdmenu voorraadbeheer **9 > 3 > E (exporteer naar Excel)**: velden aanduiden (bv. code, omschr_1) > **F8** > filter **4 (selecteer op artikelfiche)** > **5 (gelijk aan)** > op de lege artikelfiche het hangslotje aanklikken tot het rood is (= geblokkeerd) > **F8, F8, F8**.

## 4. Afdrukken vanaf de server

### Netwerkprinter drukt geen prijsaffiches of etiketten af
Vastgesteld bij een HP LaserJet Pro: de netwerkprinter moet op de server toegevoegd worden via een **TCP/IP-poort op IP-adres**, niet via de standaard HP-/WSD-poort. Oorzaak: de WSD-ondersteuning in Windows 10 werkt niet goed samen met Jamadata; via TCP/IP werkt het wel. (Een andere driver alleen loste het niet op.)

### Lokale printer voor één werkpost
Jamadata Desktop > Configuratie > Documenten > document onderscheppen en lokale printer kiezen (`installatie-desktop-en-draaiboek.md` §1).

### Afdruk komt niet aan op een post op afstand / veel te groot bestand
Bestand blijft staan in `\jamadata\Spool\ToClient\Post-xxx\`: verwijderen. Lokaal afdrukken van zo'n groot bestand kan wel.

### Afdruk ziet er anders uit na nieuwe server of nieuwe printer
Driverinstelling (grijswaarden/lettertypes), niet het pakket. Zie `installatie-migratie-naar-nieuwe-server.md` §4.

## 5. Windows- en hardwarekwesties

| Probleem | Oplossing |
|---|---|
| Windows Mobile Apparaatcentrum (WMDC) start niet | Opdrachtprompt als administrator: `REG ADD HKLM\SYSTEM\CurrentControlSet\Services\RapiMgr /v SvcHostSplitDisable /t REG_DWORD /d 1 /f` en `REG ADD HKLM\SYSTEM\CurrentControlSet\Services\WcesComm /v SvcHostSplitDisable /t REG_DWORD /d 1 /f`, daarna herstarten. (Verdere PDA-uitleg: PDA-documentatie.) |
| `JET_errSectorSizeNotSupported` op nieuwe pc | Registerinstelling `ForcedPhysicalSectorSizeInBytes` (`installatie-desktop-en-draaiboek.md` §3.3). |
| 10 of meer werkposten: JMC/JMH-processen vallen uit | Desktop Heap-registerwaarde verhogen (`server-jms-storingen.md` §2). |
| USB-back-upstick niet meer herkend | Stationsletter herstellen (`it-remote-support-vpn-shares.md` §9). |
| T-schijf (flessenautomaat) weg na stroomuitval | Netwerkverbinding opnieuw maken (`it-remote-support-vpn-shares.md` §8). |
| LogMeIn valt telkens weg | SSL-filter op de hardware-firewall uitzetten. |
| Geen ruimte voor een J-schijf / partitie niet te verkleinen | Partitietool gebruiken (bv. MiniTool Partition Wizard). |
| Programma 2500 (DCM/DataMasters) laten lopen | Hoofdmenu **+ > T > 3**, programma **2500** ingeven zonder parameters, **F8**. |

## 6. Licenties en registratiecodes

- **Postlicenties / ComfortLink-codes / dossiernummers:** staan in `JMS.ini` van de klant (zie `server-jms-overzicht-en-vereisten.md` §5); intern terug te vinden in de kopie van de klantconfiguratie op de back-upserver. Nooit in tickets of mails naar derden zetten.
- **Registratiecodes Jamadata DOS (oude installaties):** worden intern gegenereerd op de 32-bit omgeving (DOS-box, commando `protmake`) op basis van de huidige code van de klant (bij de klant zichtbaar via hoofdmenu punt **6**, **F4**): codes ingeven, **F7**, nieuwe vervaldatum ingeven, **F7**; de groene cijfercode voorlezen aan de klant, die ze in zijn systeem ingeeft. **Nooit codes geven die langer dan een half jaar geldig zijn.**
- **Wachtwoordschermen in het pakket:** er bestaat een interne manier om een gevraagd wachtwoord te omzeilen; die wordt nooit aan de klant meegedeeld (zie interne bron).

## 7. Varia uit de supportnotities

- **Export voor DAVE:** **+ (aanpassen systeemparameters) > T (speciale hulpprogramma's) > Exporteer data voor DAVE**; interne firmanaam (in DAVE) ingeven, **F8**, tabellen kiezen (bv. algemene rekeningen, klanten, leveranciers). Klanten en leveranciers bestaan uit telkens twee bestanden: eerst `Kcontacten`/`Lcontacten` importeren in CONTACTEN, daarna `Klanten`/`Leveranciers` in KLANTEN/LEVERANCIERS.
- **Inventaris retroactief:** de stock kan op een datum in het verleden herberekend worden op basis van de aankoop- en verkoopstatistieken.
- **Wero:** het genereren van een Wero-QR-code op de betaalterminals wordt pas begin 2027 toegevoegd (notitie 31/08/2026).
- **Handleidingen in het pakket:** het vraagteken op een scherm (bv. **+ > J > 5 > F8**) opent de bijhorende PDF-handleiding.

## 8. Werkwijze helpdesk

### Intake en reproduceren (concept KA-036 – niet gevalideerd, als richtlijn)
1. Leg vast: symptoom, module/menupunt, verwachte uitkomst, feitelijk resultaat, tijdstip, impact, aantal getroffen posten.
2. Vraag één concreet, reproduceerbaar voorbeeld (bon-/factuurnummer, schermafdruk van de foutmelding).
3. Onderzoek in veilige volgorde: bereikbaarheid/verbinding > rechten/configuratie > invoer > logs > reproduceren. Voer geen onomkeerbare wijziging uit zonder akkoord.
4. Noteer wat je getest hebt en het resultaat; escaleer met een bruikbare samenvatting.
5. Een oplossing voor één klantcase is niet automatisch een algemene werkinstructie.

### Wat je nooit doet
- Wachtwoorden, serienummers of de interne "achterdeur"-procedures aan de klant meedelen.
- Een manuele back-up remote starten vanop een werkpost op afstand.
- Bestanden in `\jamadata\Restore` zetten zonder dat een restore bedoeld is.
- Een back-upstick formatteren zonder eerst te controleren dat er een andere bruikbare back-up bestaat.
- De JMS herstarten of een update forceren (`go x`) terwijl er nog gebruikers werken, zonder akkoord van de klant.
- IP-adressen of firewallregels wijzigen op basis van een vermoeden.
- De oude en de nieuwe server tegelijk laten draaien na een migratie (oude map hernoemen naar `jamadata_old`).

### Na elke interventie
- Sluit Jamadata Desktop op de server en meld je af (post vrijgeven).
- Laat de klant zelf testen (bon, factuur, afdruk) en bevestigen.
- Registreer de tijd (servicecall) wanneer het om factureerbaar werk gaat (installatie, migratie).

## Bronnen
- FAQ / Jamadrink: "FAQ Jamadata SERVER.docx"
- FAQ: "Opleiding Helpdesk Jamadata.docx"
- Onenote: "Support.pdf" (volledigste exemplaar; FAQ/"Support.pdf" is ouder), "Jamadata Server.pdf"
- Jamadrink: "Jamadata FAQ's.pdf"
- FAQ/Kennisartikelen: "KA-002_Wachten_op_serversessie.md", "KA-003_Serverupdates.md", "KA-017_Stroomonderbreking_en_verbindingsproblemen.md" (gedeeltelijk gevalideerd)
- FAQ/Concepten: "KA-036_Supporttickets_reproduceren_documenteren_CONCEPT.md" (concept)
- Transcripties opleidingen: "[klant]_Migratie_20260601_162649.txt", "[klant] Migratie Server-20260611_132355-Opname van vergadering.txt"
