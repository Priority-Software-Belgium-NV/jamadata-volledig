# Server, IT en helpdeskwerkwijze: praktijkkennis uit de opleidingen juni–augustus 2026

Gebruik dit document voor: helpdeskvragen over de technische kant van Jamadata (JMS-server en JMD-werkpost, vastgelopen server, firewall en poorten, gekende installatiefouten, back-up op USB-stick), de interne hulpmiddelen waarmee de helpdesk een klant kan onderzoeken zonder hem te storen (klantgegevens, mappenlijst), de bewaking van de interne servicecomputer, en de aanbevolen manier om een supportvraag aan te pakken.

> **Let op – bron is gesproken opleiding.** Deze inhoud komt uit automatisch getranscribeerde (Whisper) opleidingssessies. Technische namen (programma's, bestanden, foutcodes) zijn zo goed mogelijk gereconstrueerd en kunnen herkenningsfouten bevatten. De exacte commando's, registersleutels en waarden staan in de interne FAQ/OneNote en in de IT-handleidingen; neem ze dáár over en niet uit dit document. Onzekere plaatsen zijn gemarkeerd met "te verifiëren". Wachtwoorden, adressen en inloggegevens zijn bewust weggelaten (zie interne bron).

---

## 1. JMS, JMD en "ik kan niet in het pakket"

- **JMS** = de Jamadata-server: draait op de hoofdcomputer en opent alle schermen.
- **JMD** = Jamadata Desktop: de viewer op de werkpost die verbinding maakt met de server en de schermen toont.
- Kan een gebruiker niet verbinden, dan ligt het **meestal aan de JMS** (vastgelopen of niet herstart), zelden aan de JMD. Klassieke oorzaak: er is een **update opgehaald en de server is daarna niet terug gestart**. Oplossing: de server stoppen/starten via het JMS-beheer op de hoofdcomputer. Enkel de JMD herstarten helpt alleen als de server zelf in orde is.
- In het interne overzicht van klantservers is te zien of een server op "gestopt" staat; dat is het eerste wat de opleider bekijkt wanneer een klant belt.
- Ervaringscijfers uit de opleiding: **20 à 30 % van de oproepen is opgelost met een herstart** (Jamadata-server, database of de pc zelf). Ruwweg 30 % van de vragen is inhoudelijk (Peppol, facturatie, statistieken), 70 % technisch: printerinstellingen, netwerk/firewall/poorten, back-up die niet loopt, nieuwe JMS-versie, melding "wacht op server".

(opleiding 11-06-2026, ca. 00:08–00:10; 16-06-2026, ca. 00:17–00:21)

### Netwerk van de klant gewijzigd
Is bij de klant het netwerk vervangen (nieuwe router/adressen) en had de server een **vast IP-adres**, dan kan niemand nog in het pakket. Het adres moet op de server aangepast worden zoals op elke Windows-pc; dat is geen Jamadata-instelling. Heeft de server daardoor ook geen internet, dan kan de helpdesk het scherm niet overnemen: de klant moet dan eerst (met zijn IT'er) zorgen dat de server weer op internet kan. Dat valt buiten de Jamadata-support. (16-06-2026, ca. 00:40–00:43)

---

## 2. Gekende technische fouten (uit de interne FAQ)

Deze gevallen werden in de opleiding overlopen aan de hand van het interne FAQ-document (ook in OneNote). De exacte instellingen staan daar.

| Symptoom | Oorzaak | Oplossing (hoofdlijn) | Bron |
|---|---|---|---|
| JMS crasht herhaaldelijk | ongewenst verkeer van buitenaf op de databasepoort (poort 5000) van de server | in de Windows-firewall bij de regel voor die poort het **bereik** beperken tot de interne IP-adressen | 11-06-2026, ca. 00:10–00:11 |
| Databasefout bij (her)installatie of migratie op een nieuwe pc: "… sector size not supported" | de schijf (moderne SSD) heeft een sectorgrootte die de database niet verwacht; komt voor bij ongeveer één op vijf nieuwe servers | een registerinstelling toevoegen via **PowerShell als administrator** (het commando staat in FAQ/OneNote; kopiëren en plakken), daarna de computer herstarten. Enkel nodig op de server. In twee jaar geen nadelige gevolgen vastgesteld. | 11-06-2026, ca. 00:11–00:17 |
| Schermen sluiten met een foutmelding ("exit of …") nadat er werkposten bijgekomen zijn (vanaf ± 10 posten) | te kleine "heap size" op de server | registerinstelling voor de heap size op de server verhogen (waarde en sleutel in de FAQ; een hogere waarde werd bij een klant zonder problemen ingesteld) | 11-06-2026, ca. 00:23–00:24 |
| Back-up meldt "last error 112" | de back-upstick is **vol** | stick leegmaken/vervangen | 11-06-2026, ca. 00:20 |
| Back-up op stick lukt niet | stick zit er niet in, is defect of heeft een andere stationsletter gekregen | zie hoofdstuk 3 | 11-06-2026, ca. 00:22; 07-07-2026, ca. 00:01 |
| Partitie moet vergroot/verschoven worden | – | Windows Schijfbeheer volstaat om in te delen; om een partitie te verschuiven is een hulpprogramma nodig (bv. een gratis partition manager) | 11-06-2026, ca. 00:19–00:20 |

Algemene regel van de opleider: **elk probleem dat je tegenkomt documenteren**, met de letterlijke foutmelding, zodat het later via de zoekfunctie teruggevonden wordt.

---

## 3. Back-up op USB-stick

- Waarheen de back-up geschreven wordt, staat in het configuratiebestand van de server (**jms.ini**): stationsletter + map.
- **Stick vervangen of stationsletter gewijzigd:** de stationsletter van de stick moet overeenkomen met jms.ini. Twee mogelijkheden:
  1. het pad in jms.ini aanpassen; of
  2. in Windows de letter van de stick wijzigen: rechtsklik op Start > **Schijfbeheer** > rechtsklik op de stick (staat als "verwisselbaar") > **Stationsletter en paden wijzigen** > de juiste letter kiezen. (Raak de vaste schijven niet aan.)
- Is er geen stick beschikbaar, dan houdt het pakket enkel een **lokale kopie** bij op de server. Dat is geen externe back-up; de klant moet de stick in orde brengen.
- Klanten bij wie de back-up of de "heartbeat" niet binnenkomt, zijn zichtbaar in het interne overzicht. Ze opbellen is eenvoudig werk waarmee een nieuwe medewerker de klanten leert kennen en vertrouwen opbouwt.
- **Bonbestand:** van het bestand met openstaande leveringsbons wordt maar één kopie bijgehouden. Bij een foute seriefacturatie de stick onmiddellijk uittrekken – zie `opleiding-zomer-jamadrink-prijzen-en-facturatie.md` (7.1).

(11-06-2026, ca. 00:20–00:23; 07-07-2026, ca. 00:01–00:03; 02-07-2026, ca. 00:19–00:21)

---

## 4. Wat de helpdesk van een klant kan zien zonder hem te storen

Jamadata ontvangt per klant dagelijks (meestal 's nachts) een pakket gegevens op een interne schijf. De opleider lost naar eigen zeggen bijna alle vragen op vanuit die gegevens. Per klant zijn o.a. beschikbaar:
- een **configuratiemap** met o.a. het configuratiebestand van de server (jms.ini) en de menu-instellingen van de kassa's;
- **`dir.lst`**: een volledige lijst van alle mappen en bestanden in de Jamadata-map van de klant, met datum en grootte. Openen in Kladblok en zoeken (Bewerken > Zoeken) op een bestands- of mapnaam;
- voor klanten met **online back-up**: de actuele kopie van de geback-upte mappen. Voor klanten zonder online back-up kan vanuit het interne beheerprogramma een back-up opgevraagd worden; die is dan enkele uren later beschikbaar. Kijk altijd naar de datum van de kopie voor je erop vertrouwt.

**Voorbeelden van gebruik:**
- nagaan of en wanneer het verkoopbestand van de kassa gewist/doorgestuurd is (zoeken op de bestandsnaam) – zie `opleiding-zomer-kassa.md`;
- nagaan of het Peppol-XML-bestand van een factuur bestaat (map `FACT\UBL`) – zie `opleiding-zomer-documenten-layouts-en-peppol.md`;
- nakijken naar welk pad de back-up geschreven wordt (jms.ini).

(23-06-2026, ca. 00:01–00:03; 06-08-2026, ca. 00:14–00:17 en 00:50–00:52)

### Mappen bij de klant die in de opleidingen genoemd werden
Onder de Jamadata-map op de server:

| Map | Inhoud |
|---|---|
| `PROG` | programma; ook de layoutbestanden (Word + PNG) |
| `KASSA` (+ submap per kassa, bv. `KASSA-01`) | klaargezette gegevens voor de kassa en de doorgestuurde bestanden van elke kassa (verkoopbestand, pdf's van dagtotalen, …) |
| `FACT\UBL` | Peppol-XML van verstuurde facturen |
| `MAIL\TEMPLATES` | e-mailtemplates (.eml) |

Op de kassa zelf: `C:\KASSA`.

---

## 5. Interne servicecomputer: dagelijkse controle

Op de interne servicecomputer van Jamadata draaien permanent:
- het venster van de **server voor werken op afstand** (klanten die van buitenaf op hun pakket werken verbinden hierlangs; rechtsonder staat wie verbonden is);
- **vijf vensters** die de synchronisatie van kassa's en PDA's verzorgen; die moeten openstaan en op "stand-by" staan.

Gevolgen als er iets misloopt: is het venster voor werken op afstand gesloten of bevroren, dan bellen binnen de tien minuten klanten dat ze niet meer op afstand kunnen werken of geen kassa's kunnen doorsturen. Bevroren venster: sluiten en via het icoon opnieuw starten. Na een update/herstart van die computer moeten alle vensters opnieuw geopend worden. Een synchronisatievenster dat op "connected" blijft hangen in plaats van stand-by: sluiten en opnieuw openen.

Afspraak: **één aangeduide persoon controleert dit elke ochtend** (met een vervanger bij afwezigheid). De servicecomputer is enkel bereikbaar vanop kantoor; van thuis uit via VPN en een tussencomputer op het kantoornetwerk, waarop maar één persoon tegelijk kan inloggen. De toegangsgegevens staan in de interne documentatie.

(04-08-2026, ca. 00:17–00:21; 06-08-2026, ca. 00:24–00:31)

---

## 6. Een supportvraag aanpakken: tips van de opleider

1. **Maak meteen een ticket** bij een telefoon, nog tijdens het gesprek. Zo weet je zeker over welke klant het gaat, zie je of hij een contract heeft en of er te veel facturen openstaan (het ticketsysteem waarschuwt daarvoor). Eens geholpen is het moeilijk om nog over betaling te beginnen. Blijf beleefd: het kan ook zijn dat de betalingen nog niet verwerkt zijn. (09-06-2026, ca. 00:29–00:31)
2. **Neem het scherm over** zodra de klant begint uit te leggen. Klanten beschrijven het probleem zelden precies; met het scherm erbij zie je vaak meteen waar het zit. Laat de klant het scherm al klaarzetten voor je doorverbindt naar een collega. (16-06-2026, ca. 00:15 en 00:27; 25-06-2026, ca. 00:33; 06-08-2026, ca. 01:11)
3. **Eén probleem per keer.** Begint de klant over een tweede en derde probleem: eerst het eerste laten tonen en afwerken. (06-08-2026, ca. 01:10)
4. **Zoek uit over welk scherm het gaat** en in welke firma (klanten met meerdere firma's). (30-06-2026, ca. 00:03)
5. **Probeer eerst de eenvoudige dingen**: herstart van server/pc lost een groot deel op (hoofdstuk 1).
6. **Onderzoek vooraf** in de klantgegevens (hoofdstuk 4) voor je terugbelt, zodat je met achtergrond belt.
7. **Maak het probleem klein**: één dag, één ticket, één bon met één artikel. Narekenen op een document met veel lijnen kost uren. (18-06-2026, ca. 00:05; 23-06-2026, ca. 00:40)
8. **Gebruik de help in het pakket** (`?` bij het menupunt): die handleidingen zijn gedetailleerd en bevatten tips die ook voor support bedoeld zijn. Ook ervaren medewerkers moeten ze raadplegen voor zelden gebruikte modules (klantenkaarten, promoties, inventaris, SEPA/CODA, koppelingen).
9. **Documenteer de oplossing** in het ticket én in de kennisbank (OneNote), in je eigen woorden en voldoende uitgeschreven voor iemand zonder voorkennis.
10. **Ken je grenzen**: is de server van de klant niet op internet, of gaat het om zijn netwerk/hardware, dan is dat werk voor de IT'er van de klant. Boekhoudkundige keuzes zijn voor de boekhouder. Vermoed je een programmafout, geef het dan met een reproduceerbaar voorbeeld door aan ontwikkeling.
11. **Hulp op afstand lukt niet met één programma?** Probeer een ander (bij een klant werkte alles behalve één hulpprogramma; de oorzaak zat op de pc van de klant). (18-06-2026, ca. 00:07)

**Tickets (interne werkwijze):**
- Een ticket dat je met de hand aanmaakt, heeft niet automatisch het e-mailadres van de klant: vul het bestemmingsadres in en verstuur de update expliciet naar de klant, anders krijgt hij nooit bericht, ook niet bij een statuswijziging.
- Staat een ticket bij een medewerker open in bewerkmodus, dan kan het antwoord van de klant er niet in verwerkt worden; sluit tickets na het bewerken. Controleer de gedeelde mailbox op antwoorden die niet in het ticket terechtkwamen.

(06-08-2026, ca. 00:20–00:24 en 00:39–00:40)

---

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):
- Kennisoverdracht Jamadata-20260609_100321-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260611_100339-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260616_151100-Opname van vergadering.txt (grotendeels coachinggesprek; enkel de algemene supportcijfers en het geval "vast IP-adres" gebruikt)
- Kennisoverdracht Jamadata-20260618_101035-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260623_100457-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260625_102119-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260630_102207-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260702_110347-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260707_100958-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260804_152719-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260806_103718-Opname van vergadering.txt
