# Migratie van Jamadata naar een nieuwe server (of naar de cloud)

Gebruik dit document voor: het verhuizen van een bestaande Jamadata-installatie naar een nieuwe centrale computer of cloudserver: voorbereiding, nette stop van de oude server, kopiëren van de map `jamadata`, netwerk (IP-adres overnemen), installatie en opstart op de nieuwe server, PDA-service (Omnis), kassa's op afstand, printers, back-up en eindcontrole met de klant.

De procedure is samengesteld uit het hoofdstuk "Installatie nieuwe JamaData Server en overdracht gegevens van oude server" (Opleiding Helpdesk), de OneNote-notities en twee opgenomen migraties (uit opleiding, 01/06/2026 en 11/06/2026 – gesproken bronnen). Een migratie stopt services, wijzigt IP-adressen en verplaatst productiedata: enkel uit te voeren door een bevoegde medewerker, in afspraak met de klant en zijn IT-partner. Wachtwoorden en licentiecodes: zie interne bron.

## 0. Voorbereiding en afspraken

- Spreek een moment af waarop niemand werkt; verwittig de klant dat de migratie **gefactureerd** wordt (servicecall met de gepresteerde tijd aanmaken; reken op 1 tot 2,5 uur, vooral door het kopiëren).
- Inventariseer: versie (Mono/Light/Server – zie SVC kolom S of de JMT op de oude server), kassa's (lokaal of **op afstand**), PDA's (map `\jamadata\omnis` of Omnis-service aanwezig?), printers, back-upmedium, snelkoppelingen op het bureaublad van de oude server (bv. "Doorsturen kassa ...", "Herstarten Jamadata Server").
- Vraag de IT-partner/hardwareleverancier vooraf: nieuwe server **bekabeld** (geen wifi), printers geïnstalleerd, J-schijf of afgesproken dataschijf, back-upmedium (stick/partitie), virusscanner-uitsluiting voor de Jamadata-mappen, een Windows-account met **administratorrechten** voor de installatie.
- **Tijdwinst:** het kopiëren van de map `jamadata` duurt altijd lang (10+ GB via USB-stick: een uur of meer). Is er een handige IT-partner, laat hem dan de data vooraf kopiëren (bv. met robocopy/script) en op het moment van de migratie – na het stoppen van de database – enkel het verschil bijwerken (duurt dan enkele minuten). Jij controleert daarna of de bestanden in `Fas` de wijzigingsdatum/-tijd van zonet hebben.

## 1. Op de oude server

1. **Is iedereen uit Jamadata?** Voorraadmenu **+ > J > T**. Gebeurt er niets bij T, dan werkt er niemand meer. (Vraagt het scherm een wachtwoord: interne procedure, niet aan de klant meedelen.)
2. Sluit Jamadata Desktop af.
3. **JMT stoppen en verwijderen:** `J:\jamadata\JMT\Bin\jmt.exe` als administrator starten (selecteren, **Ctrl+Shift+Enter**) > **STOP** > **REMOVE** (even wachten). Het bovenste blok is voor de Server-versie, het middelste voor Light, het onderste voor Mono: onthoud welk blok geïnstalleerd stond.
4. **JMS één keer manueel starten en weer stoppen** (knop **JMS** in het JMT-venster of `\jamadata\prog\JMS.exe`): zo zie je of er fouten in de database zitten, en wordt `Fas\log` leeggemaakt.
5. **Controleer dat `J:\jamadata\Fas\log` leeg is** (bevat nog niet verwerkte gegevens).
6. **JMR-service stoppen en uitschakelen:** Start > "Services" > typ J > JMR > **Stoppen** > opstarttype **Uitgeschakeld**.
7. **PDA's (Omnis):** bestaat er een map `\jamadata\omnis` of een Omnis-service, stop dan ook die service(s). Hernoem de map `omnis` naar bv. `omnis_old` vóór het kopiëren: bij de herinstallatie op de nieuwe server wordt een nieuwe map gemaakt en worden je configuratiebestanden niet overschreven; je haalt ze nadien uit de oude map.
8. **Opruimen vóór het kopiëren:** `J:\jamadata\CopyAlt` en `J:\jamadata\Dump` leegmaken (overbodige data, kost kopieertijd). **Uitzondering:** staat in `CopyAlt` een recentere back-up dan op de USB-stick, laat dan alles staan.
9. **Kopiëren:** de volledige map `J:\jamadata` naar een USB-stick (min. 16 GB, beter 32 GB; best eerst formatteren – niet de enige back-upstick wissen), naar een NAS, of via het netwerk/de IT-partner rechtstreeks naar de nieuwe server. Start het kopiëren zo vroeg mogelijk; ondertussen kan je de nieuwe server voorbereiden. Meldingen over ontbrekende bestanden uit `CopyAlt`/`Dump` tijdens het kopiëren mag je overslaan.
10. **Netwerkgegevens noteren** (screenshot): netwerkicoon > Netwerk- en internetinstellingen > Netwerkcentrum > verbinding > **Details...**: IP-adres, subnetmasker, standaardgateway, DNS-servers. (Het IP-adres staat ook in de SVC.)
11. **Oude server op DHCP zetten** zodat er geen IP-conflict ontstaat: Eigenschappen > Internet Protocol versie 4 > **Automatisch een IP-adres laten toewijzen** (ook DNS op automatisch). Doe dit pas wanneer het kopiëren niet (meer) via het netwerk loopt; je remote verbinding kan even wegvallen.
12. **Na de migratie:** hernoem op de oude server de map `jamadata` naar `jamadata_old` (of `old`), zodat niemand later per ongeluk de oude server opstart en er twee databases naast elkaar draaien.

## 2. Op de nieuwe server

### 2.1 Basis
1. Voorbereiding volgens `installatie-desktop-en-draaiboek.md` §2: PDF-reader als standaard, J-schijf (of de schijf die de IT-partner koos), virusscanner-uitsluiting, printers met correcte drivers.
2. **Vast IP-adres:** neem bij voorkeur het **IP-adres van de oude server** over (subnetmasker, gateway en DNS identiek). Dan moet er niets wijzigen aan werkposten en kassa's. Controleer alle velden: bij een tikfout ben je de verbinding kwijt en moet de klant het terug op automatisch zetten.
3. **Firewallregel "Jamadata Server"** (inkomend TCP `5000-5005, 5100-5130`, alle profielen). Kopieer en plak de poorten. Bij kassa's: regel splitsen volgens `server-jms-storingen.md` §3.
4. **Runtimes** uit `\jamadata\prog\tools` (of de interne kopie van die tools): .NET 4 / 4.5 (meestal al aanwezig), Visual C++ 2010 en 2017 redistributables. "Al geïnstalleerd" = sluiten.
5. Bij overgang van Windows 7 naar Windows 10: bepaalde DLL's moeten in `J:\jamadata\prog` staan, anders maakt het systeem dummy-bestanden aan in `FAS` (welke DLL's: niet uitleesbaar in de bron – te verifiëren).

### 2.2 Data en software
6. Kopieer de map `jamadata` naar de dataschijf (van de stick naar de schijf gaat sneller dan omgekeerd). Controleer in `Fas` de wijzigingsdatums.
7. Download `jmdn.prsw.be` (Desktop) en `jmsn.prsw.be` (Server). De **JMD** mag meteen geïnstalleerd worden: IP-adres `127.0.0.1`, **Post-01**, standaard postlicentie. Zonder draaiende database toont hij nog lege schermen.
8. Installeer de **JMS pas wanneer alles gekopieerd is**, **als administrator**, op de **juiste schijf** (niet de standaard C:). De melding dat de map al bestaat hoort te verschijnen.
9. Start `\jamadata\prog\JMS.exe` **één keer manueel**: laadt de database zonder fouten, dan zit het goed. Sluit het venster.
10. Start `\jamadata\JMT\Bin\jmt.exe` als administrator (Ctrl+Shift+Enter) en kies **INSTALL** in hetzelfde blok als op de oude server (Server = Windows-service, Light = OnLogon, Mono). Wacht even en controleer dat de status "running" wordt.
11. Controle in Taakbeheer > Details: `JMT`, `JMR`, `JMS` en `JMC`'s draaien. Start Jamadata Desktop: je komt in het pakket.

**Als de JMT niet opent of de JMS niet start na INSTALL:** onvoldoende rechten van de aangemelde gebruiker. Meld aan als Windows-gebruiker `jamadataserver` (zichtbaar maken met het registerbestand "user unhide" in `\jamadata\prog\tools`; wachtwoord via interne bron), installeer de JMS opnieuw als administrator en doe opnieuw INSTALL. Installeer onder die gebruiker ook even de JMD om te testen; sluit daarna alles, meld af en laat de klant onder zijn eigen gebruiker aanmelden. Zie `installatie-desktop-en-draaiboek.md` §3.3.

### 2.3 Instellingen nalopen
12. **Printers:** hoofdmenu **+ > J > 1** (afdrukposten). Klik per lijn (lijsten, bons/facturen, ...) op het vergrootglas en kies de overeenkomstige printer die nu op deze server geïnstalleerd is (let op: niet de fax-variant van de driver). Bewaar met F8. Printers die enkel aan een andere pc hangen (bv. kaartjesprinter) stel je hier niet in.
13. **Back-up:** controleer `CopyPath=` in `\jamadata\prog\JMS.ini` (klopt de stationsletter met de stick/partitie op de nieuwe server?). Pas zo nodig aan en controleer dat `<medium>:\jamadata\Copy\Fas` aangemaakt wordt. Eventueel de Jamadata Server herstarten. Zie `backup-en-herstel.md` §3.
14. **Kassa's op afstand / PDA's op afstand:** zet de snelkoppelingen terug op het bureaublad: in `J:\jamadata\kassa` rechtermuisklik op `sendkas` > snelkoppeling naar bureaublad en hernoem betekenisvol (bv. "Doorsturen kassa <locatie>" / "Update kassa's op afstand"); idem `J:\jamadata\JamaPDA\sendpda` voor de oude PDA's. Controleer dat in de batch de afkorting van de klant staat (niet "xx"). Dubbelklik om te testen (zwart venster dat doorstuurt).
15. **PDA's met Omnis/JamaMobi:** installeer de Omnis-runtime en service volgens de "Installatie guide JamaMobi server" (PDA-documentatie). Bij een migratie kopieer je de twee configuratiebestanden uit de oude (hernoemde) Omnis-map – het JamaMobi-API-bestand (`.lbs`) en `JamaMobi.dat` – zodat de PDA's niet opnieuw gekoppeld moeten worden (geen nieuwe QR-code). Zet de service op automatisch, maak een inkomende firewallregel **"JamaMobi"** voor TCP-poort **60000** en test de API-URL op de server zelf (`http://localhost:60000/...`, http en niet https): na ± 20-30 seconden moet een lijst artikelen verschijnen. Dit werkt pas wanneer de Jamadata-database draait.
16. Op alle werkposten: enkel nodig als het IP-adres van de server gewijzigd is (Configuratie > Instellingen > IP-adres server). Kassa's: `set JMS=` in `jama.bat` als het adres wijzigde.

### 2.4 Afronden
17. Sluit Jamadata Desktop en meld je eigen/admin-gebruiker af (anders blijft Post 1 bezet onder jouw gebruiker). Sluit geen sessies van de IT-partner.
18. **Bel de klant** en laat testen: bon maken, factuur maken en afdrukken, lijst afdrukken, kassa doorsturen, PDA.
19. Controleer in de SVC dat de installatie online is (heartbeat, USB/back-up, geen fouten).
20. Servicecall aanmaken en uren registreren.

## 3. Varianten

### Overzetten van een oude pc via Jamadata (zonder IT-partner)
1. JMR-service stoppen via Services; Jamadata Desktop afsluiten.
2. JMT als administrator (Shift+Ctrl+Enter) > remove.
3. JMS starten en weer stoppen zodat `Fas\log` leeg is.
4. De volledige map `jamadata` ophalen (naar Jamadata of rechtstreeks), op de nieuwe pc/server plaatsen en het installatiedraaiboek volgen.

### Overzetten naar een cloudserver
Zelfde stappen: controleren dat niemand werkt (**+ > J > T**), JMR stoppen, Desktop sluiten, JMT remove, JMS starten/stoppen, `Fas\log` leeg, `CopyAlt` verwijderen (tenzij recenter dan de stick), map `jamadata` naar de cloudserver overzetten en het installatiedraaiboek volgen. Aandachtspunten (uit opleiding "vid backup"):
- Geen USB-stick mogelijk: de schaduwkopie gaat naar een aparte schijf/partitie; voorzie daar voldoende ruimte (ze loopt anders vol, zie `LastError=112`).
- Lokale printers en poorten/toegang vragen extra werk van de cloud-/IT-partner (redirected versus rechtstreeks aangestuurde printers).

## 4. Veelvoorkomende problemen bij een migratie

| Probleem | Oplossing |
|---|---|
| Kopiëren duurt zeer lang | Vooraf laten kopiëren door de IT-partner en enkel het verschil bijwerken; `CopyAlt`/`Dump` vooraf leegmaken. |
| Nieuwe server staat op wifi | Laat de netwerkkabel van de oude server in de nieuwe steken; stel het vaste IP in op de bekabelde adapter. |
| Verbinding kwijt na IP-wijziging | Klant/IT-partner laten terugzetten op automatisch en opnieuw beginnen. |
| JMS op C: geïnstalleerd | Opnieuw installeren als administrator op de juiste schijf. |
| JMT start niet / JMS start niet als service | Aanmelden als `jamadataserver`, JMS en JMT opnieuw installeren. |
| JMR komt niet online op de SVC | Gebruiker `jamadataserver` manueel aanmaken, daaronder `JMS-inst` uitvoeren. |
| Database geeft fouten op nieuwe schijf (`JET_errSectorSizeNotSupported`) | Registerinstelling sectorgrootte, zie `installatie-desktop-en-draaiboek.md` §3.3. |
| Virusscanner houdt bestanden tegen of maakt alles traag | Jamadata-mappen laten uitsluiten door de IT-partner. |
| Afdruk is lichter/grijzer dan vroeger | Data en pakket zijn één-op-één overgezet; dit is een instelling van de opnieuw geïnstalleerde printerdriver (grijswaarden, lettertypes). De hardwareleverancier vergelijkt de driverinstellingen met de oude server. Bewijzen kan door op de oude pc als Post 2 via Configuratie > Documenten lokaal af te drukken. |
| Back-upmap verschijnt niet op het nieuwe medium | `CopyPath` controleren, Jamadata Server herstarten, eventueel pc herstarten; SVC nakijken. |
| Bestanden in `Fas` zonder datum na het kopiëren | Eenmalig vastgesteld; de database startte wel zonder fouten. Geen conclusie in de bron – bij twijfel escaleren. |

## Bronnen
- FAQ: "Opleiding Helpdesk Jamadata.docx" (hoofdstuk "Installatie nieuwe JamaData Server en overdracht gegevens van oude server")
- Onenote: "Jamadata Server.pdf" (notities "Back-up ophalen en overzetten van oude PC", "Jamadata Server overzetten naar cloud", 18/11/2024)
- Jamadrink: "Installatiedraaiboek Jamadata 1.docx"
- FAQ/Kennisartikelen: "KA-009_Servermigratie_controle_en_overdracht.md" (voorlopig, niet technisch gevalideerd)
- Transcripties opleidingen: "[klant]_Migratie_20260601_162649.txt", "[klant] Migratie Server-20260611_132355-Opname van vergadering.txt", "vid backup.txt"
