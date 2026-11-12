# Praktijkkennis opleiding mei 2026: printers, mailen vanuit het pakket, scanners, PDA en digitale prijskaartjes

Gebruik dit document voor: vragen over hoe printers in Jamadata ingesteld worden (afdrukposten op de server versus lokale printer per werkpost, Zebra-etikettenprinter), waarom mails/facturen vanuit het pakket niet vertrekken en hoe je de ingebouwde mailserver instelt en controleert, eerste hulp bij handscanners, de verbinding van oude en nieuwe PDA's, en de koppeling met digitale prijskaartjes.

> **Waarschuwing.** Deze inhoud komt uit gesproken opleidingssessies (automatische Whisper-transcriptie, mei 2026) en kan herkenningsfouten bevatten (menuletters, functietoetsen, bestandsnamen). Controleer bij twijfel tegen de handleiding (o.a. "Installatie Jamadata Desktop", de Zebra-handleiding, het document met de automatische mailinstellingen, de PDA-handleiding). Punten met *(te verifiëren)* waren niet eenduidig.

## 1. Printers

Bron: opleiding 13-05-2026 (ca. 00:02–00:19); aanvullend 12-05-2026 namiddag (ca. 00:32).

### 1.1 Principe

Alle schermen draaien op de server; afdrukken gebeurt dus standaard **vanaf de server**. Het pakket werkt met twee lagen:

1. **Afdrukposten** (logische printers), centraal ingesteld en gekoppeld aan Windows-printers die **op de server** geïnstalleerd zijn.
2. **Uitzonderingen per werkpost**, ingesteld in de Jamadata Desktop (JMD) van die post.

Daarom: bij een installatie of migratie best **alle printers van de klant op de server installeren**. Dan kan je ze als standaard instellen voor alle gebruikers, en bij een defecte printer hoef je enkel op de server iets te wijzigen in plaats van op elke post of kassa.

### 1.2 Afdrukposten (centraal)

- Pad: hoofdmenu Voorraad → `+` → `J` (JMS-instellingen: printers, papier, werkstations, e-mail) → `1` **Afdrukposten**.
- Bij bestaande klanten staan de afdrukposten al ingevuld. Typisch: "Lijsten/facturen" en "Bonnen" als aparte afdrukposten (historisch: bonnen op een matrixprinter, lijsten en facturen op een A4-printer). Er kunnen er extra zijn, bv. "Facturen kassa's" voor een printer in de buurt van de kassa's.
- Per afdrukpost geef je een naam en kies je de **Windows-printer**. Enkel printers die op de server geïnstalleerd zijn, zijn kiesbaar.
- De Windows-printer moet beschikbaar zijn **voor de Windows-gebruiker waaronder Jamadata draait**. Een netwerkprinter is meestal meteen in orde; een printer die per gebruiker geïnstalleerd wordt, moet ook onder die gebruiker geïnstalleerd worden (aanmelden als die gebruiker), anders ziet het pakket hem niet.

### 1.3 Documenteigenschappen (wat gaat naar printer, wat naar pdf)

- Pad: hoofdmenu → `+` → `J` → `2` **Documenteigenschappen**.
- Per documentsoort (facturen, bonnen, voorraadlijsten, ...) bepaal je het papier/formaat en de afdrukpost. **Leeg = altijd naar pdf.**
- Lijsten staan standaard op pdf. Facturen staan normaal op printen (bv. "A4 wit blanco" naar de afdrukpost lijsten/facturen). Komt een factuur onverwacht als pdf, kijk dan hier of iemand de factuur op pdf heeft gezet.

### 1.4 Uitzonderingen per werkpost (JMD)

- Pad: in de Jamadata Desktop van de post → **Configuratie → Documenten**.
- Je ziet dezelfde soorten (lijsten/bonnen/facturen, kaartjes/etiketten, ...). Per soort kan je "afdrukken van dit werkstation onderscheppen" aanvinken en kiezen:
  - **er een pdf van maken**;
  - **verwerken zoals op een ander werkstation**: de afdruk gebeurt met de instellingen van een andere post. Die post moet dan aanstaan en in het pakket zitten. Enkel gebruiken als het niet anders kan (bv. een USB-etikettenprinter die aan één bepaalde pc hangt);
  - **afdrukken op een andere afdrukpost** (bv. op de kassa: facturen naar de afdrukpost "Facturen kassa's");
  - **afdrukken op een lokale printer**: onderaan kies je een printer die op déze pc geïnstalleerd is. Dit is de meest gebruikte uitzondering.
- Een instelling hier overschrijft wat centraal is ingesteld.
- Vuistregel: eerst centraal op de server instellen; enkel wat niet via de server kan, per post instellen.

### 1.5 Bijzondere gevallen

- **Posten/kassa's op afstand** (andere locatie, geen printer bereikbaar vanaf de server): printer lokaal installeren op die pc/kassa en in JMD → Configuratie → Documenten als lokale printer kiezen.
- **Oude kassa's met kleine schijf**: geen vrije schijfruimte veroorzaakt printproblemen en maakt het installeren van een driver (± 100 MB) onmogelijk. Controleer de schijfruimte.
- **Zebra-/etikettenprinter (rayonkaartjes)**: wordt altijd **lokaal** (USB) aangesloten en in Windows geïnstalleerd op de pc waar hij staat; daarna in JMD → Configuratie → Documenten bij kaartjes/etiketten het vinkje zetten, onderaan "lokale printer" aanvinken en de Zebra kiezen. Op de server installeren heeft geen zin. Volg de uitgebreide Zebra-handleiding.
- **Zebra opsturen voor herstelling**: zonder toebehoren (geen voeding, kabels, lint of rolletjes) – die komen niet altijd terug. De printer heeft een lege kartonnen kern nodig waarop het gebruikte lint wordt opgerold; ontbreekt die, dan kan de klant de kern van een opgebruikt lint hergebruiken. (opleiding 20-05-2026 namiddag, ca. 00:11–00:15)

### 1.6 Een printer testen

- Een lijst (bv. lijst `944`, de groepenlijst, snel op te roepen) komt als pdf en test dus de printer niet.
- Gebruik het herafdrukken van een factuur: hoofdmenu → `8` Facturatie → `H` Herafdrukken facturen → `1` Bekijken/herafdrukken van gemaakte facturen → factuurnummer of klant ingeven → factuur kiezen → de schermen bevestigen met `F8` → afdrukken (in de opname `F5`; *toetsen te verifiëren*).

## 2. Mailen vanuit het pakket (ingebouwde mailserver)

Bron: opleiding 20-05-2026 namiddag (ca. 00:37–01:13).

### 2.1 Wat en voor wie

- Het pakket heeft een ingebouwde mailfunctie (SMTP-client) om facturen, bonnen e.d. te mailen, ook automatisch achter de schermen (bv. facturen naar een extern boekhoudpakket). Dit loopt **niet** via Outlook.
- Beschikbaar in **Light** en **Server**, niet in Mono. In Light kan je mailen maar wordt er geen detail bijgehouden; in Server zie je de verzonden mails ook terug in o.a. de klantenfiche.
- Schatting van de opleider: op twintig tickets gaan er één à twee over mailen.

### 2.2 Instellingen

- Pad: hoofdmenu Voorraad → `+` → `J` (JMS-instellingen) → `5` **Mail**.
- **Profiel**: bij ± 95 % van de klanten leeg laten (profiel 0). Meerdere profielen zijn enkel nodig als de klant met meerdere afzenders wil werken.
- Bevestigen met `F8`; daarna het scherm met:
  - naam van de afzender (zoals de ontvanger die ziet);
  - e-mailadres van de verzender;
  - antwoordadres (leeg = zelfde als verzender);
  - BCC: elk verzonden bericht gaat ook in kopie naar dit adres (handig als controle voor de klant);
  - ontvangst-/leesbevestiging (meestal niet gebruikt).
- Het vraagteken rechtsboven opent de handleiding over het aanpassen van de mailtemplates (bv. eigen ondertekening). Templates moeten als `.eml` aangeleverd worden (omzetten van `.msg` naar `.eml`).
- **`F10` Relay-instellingen**: uitgaande mailserver, poort, gebruikersnaam, wachtwoord, beveiliging.
  - Met gebruikersnaam en wachtwoord → beveiliging op **auto**.
  - Zonder gebruikersnaam/wachtwoord (onbeveiligd) → beveiliging op **none**.
- **Testmail**: op het instellingenscherm de knop "Stuur testmail", adres ingeven, bevestigen met `F8`.
- Het afzenderadres mag verschillen van het adres waarmee ingelogd wordt op de mailserver, maar niet elke provider laat dat toe.

### 2.3 Welke mailproviders werken (stand mei 2026)

| Provider | Instelling | Opmerking |
|---|---|---|
| Telenet | `smtp.telenet.be`, poort 587, login met het Telenet-adres en wachtwoord, beveiliging auto | Werkt. |
| Proximus | relayserver van Proximus (zoek de actuele servernaam en poort op bij de provider), poort 587 met login | Werkt. |
| Microsoft 365 (bedrijfsadres) | `smtp.office365.com`, poort 587, login met het mailadres en wachtwoord, auto | Werkt **enkel** als de IT'er van de klant voor die mailbox "geverifieerde SMTP" (SMTP AUTH) inschakelt; standaard staat dat uit en met tweestapsverificatie werkt het nooit. Geschat ± 75 % van de klanten gebruikt dit. IT'ers merken op dat dit niet meer de voorkeursmethode is. |
| Onbeveiligd via de internetprovider (zonder login) | – | Niet meer aanraden: werkt soms voor enkele mails, maar een deel komt niet aan. |
| Hotmail/Outlook.com, Gmail | – | Werken niet meer met gewone SMTP-login. OAuth wordt door de mailfunctie niet ondersteund. |

Er wordt gewerkt aan een alternatief via een externe SMTP-relaydienst (zou een instelling in jms.ini vragen en, bij een eigen domein, extra DNS-records via de IT'er van de klant). Dat was in mei 2026 nog niet uitgerold: *toekomstig, te verifiëren*.

Voor Microsoft 365 bestaat een standaardmail met schermafdruk die je naar de IT'er van de klant stuurt (instelling "geverifieerde SMTP" aanzetten voor het account; het primaire adres van de mailbox moet het gebruikte adres zijn). Dit is geen ingreep die support zelf doet.

### 2.4 Diagnose: "mijn mails/facturen vertrekken niet"

1. **Is het wachtwoord nog juist?** Meest voorkomende oorzaak: de klant heeft zijn mailwachtwoord gewijzigd (in Outlook/webmail) maar niet in het pakket. Laat de klant zelf inloggen op de **webmail** van zijn provider met exact hetzelfde adres en wachtwoord; lukt dat niet, dan is het wachtwoord fout. Klanten denken vaak dat ze het wachtwoord kennen.
2. **SVC**: verzonden mails en mailfouten zijn zichtbaar in het log van de klant.
3. **Maillog**: het pakket houdt een log bij van de dialoog met de mailserver; die komt ook mee naar de interne back-up-/uitwisselschijf (map van de klant, submap config, e-maillogbestanden – *exacte bestandsnaam te verifiëren*). Kijk naar de laatste regels: bv. "authentication unsuccessful" of "invalid login" wijst op foute logingegevens of op een mailbox waar SMTP-login niet toegelaten is. Bij een moeilijk geval: stuur de gebruikte instellingen en deze logregels naar de IT'er van de klant; die ziet meestal meteen wat er moet gebeuren.
4. **Niet-verzonden facturen in het pakket**: hoofdmenu → `8` Facturatie → `H` Herafdrukken facturen: rechts onderaan staan twee icoontjes, **niet-verzonden** en **wel verzonden**. In de lijst niet-verzonden kan je een mail bekijken, **opnieuw versturen** of verwijderen. (Let op: opnieuw versturen op het systeem van de klant verstuurt echt.)
5. **Mailmappen op de server**: `Jamadata\Mail` werkt zoals een mailprogramma met de mappen **Outbox** (wordt voortdurend uitgelezen; een bericht is binnen de minuut weg), **Sent** (verzonden) en **Failed** (mislukt). Berichten zijn gewone `.eml`-bestanden die je kan openen. Een bericht uit Failed terug in Outbox plaatsen (knippen/plakken) = opnieuw proberen. Komt het meteen terug in Failed, dan is de oorzaak niet opgelost. Staat er in Sent al lang niets recents, dan vertrekt er al lang niets.
6. **Mails komen bij de ontvanger in spam**: daar kan support niets aan doen; eventueel een ander afzenderadres gebruiken.

Het verkrijgen van de juiste logingegevens bij de provider is de taak van de klant en kan lang duren; verwittig de klant daarvan.

## 3. Handscanners (kassa)

Bron: opleiding 19-05-2026 (ca. 00:01–00:06), 20-05-2026 namiddag (ca. 00:34–00:36).

- Er zijn modellen mét en zonder toetsenbordje. Welk toestel een klant heeft, staat in de kassadocumentatie per klant; controleer ook de klantorders, want de documentatie is niet altijd bijgewerkt na een latere aankoop.
- **Scanner (zonder toetsenbordje, met laadstation) werkt niet meer**: trek onderaan het laadstation het zwarte stroomkabeltje uit; het station maakt dan opnieuw verbinding via USB. Werkt het weer, steek het kabeltje terug in. Dit lost het heel vaak op.
- **Scannen geeft vreemde tekens** (test in Kladblok): de scanner is niet (meer) juist geprogrammeerd. Laat het **programmatieblad** van dat scannermodel opnieuw scannen (barcodes 1 t/m 9 in volgorde); de opleider scant daarna de tweede barcode nog eens, omdat die de verbinding met de pc opnieuw legt. De programmatiebladen staan bij de supporthandleidingen; vindt de klant zijn blad niet meer, mail het dan.
- **Scanner piept voortdurend of is meteen leeg na het uitnemen**: bijna zeker de batterij (zeker bij een toestel van enkele jaren oud). Het batterijpakje zit achter een dekseltje met een kruisschroef en is met een klein stekkertje aangesloten; het kan vervangen worden. Voor een nieuwe batterij of een nieuw toestel moet een offerte via sales gemaakt worden. Voor zeer oude modellen zijn er geen batterijen meer.
- **PDA of scanner herkent een artikel niet**: zie § 4.3.

## 4. PDA's

Bron: opleiding 20-05-2026 namiddag (ca. 00:09 en 00:20–00:31). De volledige PDA-uitleg (installatie, leeggoed, stock, bestellingen) kwam in deze sessies nog niet aan bod.

### 4.1 Oude PDA's (via de pc)

- Maken geen rechtstreekse draadloze verbinding met de database, maar verbinden via een pc met **Windows Mobile Device Center** (WMDC).
- Het installatiebestand (een "drvupdate"-installer) staat in de map Windows Mobile Device Center bij de supporthandleidingen; de installatie duurt ± 10 minuten. Voor mailen is er ook een zip-versie (een .exe wordt vaak geweigerd).
- WMDC dateert uit de tijd van Windows Vista. Op Windows 10 **start het na installatie vaak niet op** (in de ervaring van de opleider in negen op de tien gevallen). Oplossing: open een opdrachtprompt **als administrator** en plak de twee registercommando's uit het bijgeleverde batch-/tekstbestand (zie de handleiding); elke regel moet "De bewerking is voltooid" geven. Herstart daarna de pc; WMDC start dan wel.
- Oefen dit eerst op een eigen pc met een PDA vóór je het bij een klant doet.

### 4.2 Nieuwe PDA's (Jamamobi, via wifi)

- Verbinden rechtstreeks via wifi: de PDA moet op **hetzelfde netwerk** zitten als de server en verbindt met het IP-adres van de server op poort 60000 (*exact poortnummer: zie PDA-handleiding*). Op de server moet daarvoor een inkomende firewallregel bestaan.
- Verandert het IP-adres van de server, dan kunnen ook de PDA's niet meer verbinden.

### 4.3 "PDA herkent een artikel niet bij het scannen"

1. Meest waarschijnlijk: de PDA is niet (recent) gesynchroniseerd en kent het nieuwe artikel nog niet.
2. Anders: verschil in hoe de barcode gelezen wordt tussen de kassascanner en de PDA (bv. een voorloopnul). Op de PDA is dat niet zomaar aan te passen; als de PDA's het "juist" doen en de kassascanner afwijkt, pas dan de programmatie van de kassascanner aan.
3. Vraag altijd door (welk toestel, welk artikel, welke barcode); met de eerste melding heb je meestal te weinig informatie.

## 5. Digitale prijskaartjes (koppeling met Digi)

Bron: opleiding 20-05-2026 namiddag (ca. 00:04–00:09).

- Jamadata schrijft twee bestanden weg in een gedeelde map `KASSA`: een **databestand met de artikelgegevens** (gehoord als `ARTIKELDATA.DAT`) en een **flag-bestand** dat aangeeft dat er nieuwe gegevens klaarstaan. Het systeem van Digi haalt het databestand op en verwijdert daarna het flag-bestand.
- De bestanden kunnen opgehaald worden van de server of van de kassa. Staat de server in de cloud, dan gebeurt het **vanaf de kassa in elke winkel** (share `\\<naam-kassa>\KASSA`).
- Digi heeft de sharenaam, de bestandsnamen en de Windows-gebruiker/het wachtwoord van de kassa nodig (wachtwoord: zie interne bron; oudere kassa's van vóór Windows 10 hebben geen wachtwoord).
- **Meldt Digi dat de import niet meer werkt terwijl aan Jamadata-kant alles klopt**: neem het scherm van de kassa over, maak een **schermafdruk van de map met de exacte bestandsnamen en het exacte pad** en stuur die door. Het Digi-systeem draait op Linux en is hoofdlettergevoelig; Jamadata schrijft de namen in hoofdletters. In het besproken geval loste dat het op.
- Let er bij tickets op dat je ze op de juiste klant zet; antwoorden van zo'n leverancier gaan anders naar de verkeerde klant.

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):

- Kennisoverdracht Jamadata-20260512_150237-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260513_094305-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260519_140734-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260520_143704-Opname van vergadering.txt
