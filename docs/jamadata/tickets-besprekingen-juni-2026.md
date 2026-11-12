# Opgeloste supporttickets uit de ticketbesprekingen (juni 2026)

Gebruik dit document voor: het herkennen van terugkerende supportvragen en de aanpak die helpdesk en expert er in de ticketbesprekingen van 17, 18, 23, 24 en 25 juni 2026 voor uitwerkten. Elke case geeft symptoom, oorzaak (indien gekend), controles, oplossing en status. Zoek op symptoom of trefwoord (Peppol, controleband, minimumstock, mailtemplate, DIGI, ...).

> **Waarschuwing: inhoud uit gesproken besprekingen.** Alles hieronder komt uit automatische (Whisper-)transcripties van mondelinge sessies. Die bevatten herkenningsfouten: toetsen, menunummers en bestandsnamen kunnen verkeerd verstaan zijn. Waar dat risico groot is, staat "(onzeker)" of "te verifiëren". Menunummers kunnen bovendien per klant verschillen: controleer altijd in het pakket van de klant zelf voor je een pad doorgeeft. Klant- en persoonsnamen, klantcodes en wachtwoorden zijn bewust weggelaten.

Gebruikte toetsbenamingen uit de besprekingen: F8 = bevestigen/verder, F9 Vervolg = vervolgscherm van een fiche, "Stoppen" = scherm verlaten, "+" op het hoofdmenu = extra/beheerfuncties.

---

## 1. Jamadrink / facturatie

### Oude boekjaren niet meer raadpleegbaar (facturen van vorige jaren herafdrukken lukt niet)
- **Symptoom:** de klant kan vorige boekjaren niet meer kiezen (bij "selecteer systeem", in de bespreking opgeroepen met F4, staat enkel het huidige jaar) of kan facturen van vorige jaren niet meer herafdrukken.
- **Oorzaak:** bij een opkuis zijn oude jaren verplaatst om de online back-up klein te houden (de back-up liep vast door de omvang; ook een grote mailmap speelde mee). De databestanden staan in een map `FAS_OLD` (naast `FAS`), de factuurkopieën in `FTCOPY_OLD` (naast `FTCOPY`). Er is niets weggegooid.
- **Controles / diagnose:**
  1. Vraag de klant per firma/dossier welk jaar hij echt nodig heeft. Een klant met meerdere dossiers heeft de oude jaren meestal maar voor een deel van de dossiers nodig.
  2. Kijk in de directory-overview van de klant (`dir.lst` in de `config`-map van de klant op de interne back-upschijf, zie case "Bestanden en instellingen van een klant bekijken zonder het scherm over te nemen") en zoek op `FAS_OLD` om te zien welke dossiers en jaren daar staan.
  3. Bestanden zijn herkenbaar aan de extensie: dossiercode + jaar (bv. alles wat eindigt op `D23` = dossier D, jaar 2023).
- **Oplossing:**
  1. Zet **selectief** terug: enkel het gevraagde jaar van het gevraagde dossier. Nooit "de laatste tien jaar" terugzetten, anders is de opkuis zinloos en loopt de back-up opnieuw vast.
  2. Verplaats (knippen en plakken, niet kopiëren) alle bestanden met de juiste jaarextensie van `FAS_OLD` naar `FAS`.
  3. Voor herafdrukken van facturen: verplaats de bestanden met de jaarextensie van `FTCOPY_OLD` naar `FTCOPY`.
  4. Werk altijd met **volledige jaren**. Bij een half jaar werkt een deel van de facturen wel en een deel niet, en dat geeft uren zoekwerk.
  5. Zet de "rest"-bestanden (kopieën die ontstaan bij aanpassingen aan de database door de programmeur) **nooit** terug.
  6. Laat dit door support doen, niet door de klant zelf.
- **Verschil FAS / FTCOPY:** `FAS` = de database; `FTCOPY` = enkel de factuurkopieën.
- **Status:** aanpak besproken, uitkomst onbekend (klant moest nog gecontacteerd worden).
- **Bron:** ticketbespreking 17-06-2026, ca. 00:02–00:14 en 00:18.

### Een gebruiker past prijzen aan en er wordt met verlies verkocht
- **Symptoom:** de zaakvoerder meldt dat een medewerker de prijs van een artikel heeft gewijzigd, waardoor verliesgevend verkocht werd. Hij wil dit afschermen, maar niet honderd keer per dag een lang wachtwoord intikken.
- **Controles / diagnose:** nagaan of de klant al met wachtwoorden in het pakket werkt (in dit geval wel).
- **Oplossing:**
  1. Zet een wachtwoord op de basisgegevens (hoofdmenu, punt basisgegevens). Het wachtwoordbeheer zit onder "+" op het hoofdmenu (exacte toetsvolgorde niet duidelijk in de transcriptie).
  2. Een korte code mag: een pincode van vier cijfers volstaat (volgens de expert vermoedelijk zelfs één teken).
  3. Wijs de klant op het vinkje **"Bewaar paswoord"** in het wachtwoordvenster: het wachtwoord blijft dan onthouden zolang de gebruiker in dat scherm blijft werken; de volgende dag moet het opnieuw ingegeven worden.
  4. Stuur een schermafdruk van het wachtwoordvenster met het vinkje aangeduid; de klant begreep de tekstuele uitleg niet.
- **Status:** aanpak besproken, antwoord aan klant werd verstuurd; uitkomst onbekend.
- **Bron:** ticketbespreking 17-06-2026, ca. 00:19–00:22.

### Hoe werkt minimumstock / normale stock (stockbeheer starten)
- **Symptoom:** de klant ziet op de artikelfiche de velden stock, normale stock en minimumstock en vraagt hoe dat werkt.
- **Uitleg:**
  - Artikelfiche (in de bespreking opgeroepen via het voorraadmenu met 9 – 3 – 1), daarna **F9 Vervolg**: bovenaan staan stock, normale stock en minimumstock. Let op: F9 op het zoekscherm maakt een nieuw artikel aan; gebruik F6 om terug te gaan.
  - Verkopen laten de stock dalen, aankopen laten ze stijgen. Zakt de stock onder de minimumstock, dan komt het artikel op de lijst "onder minimumstock" en kan er automatisch besteld worden tot de normale stock.
  - Is er geen minimumstock ingevuld (0), dan komt alles wat onder nul staat op de lijst.
- **Oplossing / stappen:**
  1. **Lijst artikelen onder minimumstock:** punt 5 (lijsten) → punt 2 afdrukken diverse stocklijsten / inventarislijst → punt 1 actuele stocklijst → bij "afdrukken onder minimumstock" de keuze **M** → depot kiezen → PDF en F8. De lijst toont actuele stock en minimumstock per artikel. Standaard worden de aantallen op openstaande leveringsbons afgetrokken (die zijn eigenlijk al verkocht).
  2. **Bestelling op basis van minimumstock:** "Inbrengen bestellingen aan leveranciers" → inbrengen nieuwe bon → punt 2 "toevoegen van een nieuwe bon aan de hand van de artikelen onder de minimumstock" → leverancier kiezen → F8 → bevestigen. Het pakket stelt per artikel het aantal voor dat nodig is om terug op de normale stock te komen.
  3. **Stocklocaties (bv. magazijn en winkel):** de stock op de artikelfiche is altijd die van het magazijn/depot. Via "Stocklocaties" op de artikelfiche geef je per locatie een eigen minimumstock en normale stock in; "geleverd" en "verkocht" vult het pakket zelf in. Op de stocklijst kies je dan in plaats van het depot de locatie (bv. 1 = winkel) en opnieuw M.
  4. **Handleiding meesturen:** er bestaat geen volledige handleiding "stock", wel over inventaris en over stocklocaties. Die laatste: hoofdmenu punt 8 (facturatie) → punt 9 (beheer leveringen / mutaties filialen) → vraagteken rechtsboven. Stuur de handleiding als bijlage en vraag de klant terug te komen met concrete vragen. Bellen is hier efficiënter dan schrijven.
- **Status:** opgelost in bespreking (handleiding verstuurd, ticket op "wachten op klant").
- **Bron:** ticketbespreking 17-06-2026, ca. 00:22–00:32; opvolging 18-06-2026, ca. 00:27.

### Stock daalt niet bij leveringsbon / hoe gaat de stock omhoog bij een levering
- **Symptoom:** de klant (met module aankoopbeheer) begrijpt niet waarom de stock niet klopt en hoe ontvangen goederen in stock komen.
- **Oorzaak / uitleg:** stock wordt bij nagenoeg alle klanten op **factuurniveau** bijgewerkt. Een leveringsbon verlaagt de stock op de artikelfiche niet. Het vergrootglas naast de stock toont wel "aantal op bons" en de netto stock, en met een verdere klik het detail per klant.
- **Oplossing:** de structuur van "Inbrengen bestellingen aan leveranciers" (voorraadmenu) uitleggen:
  1. Punten 1 t/m 4: bestelling bij de leverancier plaatsen, aanpassen, schrappen, lijst afdrukken.
  2. **Punt 5 "Leveren van bestelde goederen":** de goederen komen binnen (met leveringsnota, nog zonder factuur) → dit verhoogt de stock.
  3. Punt 6 "Inboeken van geleverde goederen": de factuur komt later; prijzen controleren, statistieken en boekhouding worden bijgewerkt.
  4. Punt 7: rechtstreekse ingave zonder voorafgaande bestelling (bv. telefonisch besteld): stock, statistiek en boekhouding in één keer.
  - Controleer in het pakket van de klant of de puntnummers dezelfde zijn; ze zijn niet overal identiek.
- **Bijkomende vraag in hetzelfde ticket (tablets):** Jamadata draait enkel op een toestel met **Windows** (bv. een Surface), niet op Android- of iOS-tablets.
- **Status:** opgelost in bespreking (antwoord: stock bijwerken gebeurt via punt 5).
- **Bron:** ticketbespreking 23-06-2026, ca. 00:38–00:45 en 00:52.

### Rechtstreekse aankoop (punt 7) per vergissing ingeboekt
- **Symptoom:** via de rechtstreekse ingave van een aankoop is iets foutief geboekt (in de bespreking gebeurde dit per ongeluk in het pakket van een klant in plaats van in de demo).
- **Controles / diagnose:** de boeking zit op drie plaatsen: stock, boekhouding en aankoophistoriek/-statistiek (voorraadmenu punt 4, aankoophistoriek over de betrokken periode en leverancier).
- **Oplossing:** de boekhoudkundige boeking kon verwijderd worden en het aankoopnummer teruggezet. Voor de aankoophistoriek is geen schrapfunctie gevonden (de bestaande correctietoets is voor klanten, niet voor leveranciers). Besproken alternatief: dezelfde aankoop **negatief inboeken**, zodat het saldo nul is (beide lijnen blijven wel zichtbaar). Anders door de programmeur laten rechtzetten.
- **Les:** controleer altijd in welk dossier/pakket je staat voor je iets test (demo vs. klant).
- **Status:** aanpak besproken, uitkomst onbekend.
- **Bron:** ticketbespreking 23-06-2026, ca. 00:45–00:54.

### Zwerfvuiltaks zit niet in het bedrag accijnzen na automatische prijswijziging (Prik&Tik)
- **Symptoom:** de klant vraagt waar de zwerfvuiltaks moet opgeteld worden; na het inlezen van de prijsbestanden van de groepering klopt het bedrag "accijnzen en ecotax" op de artikelfiche niet.
- **Oorzaak:** de Excel-prijsbestanden van de groepering bevatten sinds dit jaar een aparte kolom zwerfvuiltaks. Het inleesprogramma nam enkel de accijnskolom over. Op de artikelfiche (F9 Vervolg) is er maar één veld "accijnzen en ecotax", waarin alle taksen samen moeten staan.
- **Controles / diagnose:**
  1. Nagaan hoe de klant zijn prijzen wijzigt: manueel of automatisch via beheer prijzen → "aanpassen artikelprijzen aan de hand van prijsbestanden".
  2. In dat scherm (vraagteken = handleiding) de recente bestanden bekijken of downloaden en de kolommen controleren.
  3. Via het vergrootglas op een lijn vergelijken welk accijnsbedrag wordt overgenomen.
- **Oplossing:** programma-aanpassing door de programmeur: accijnzen + ecotax + zwerfvuiltaks + Fost Plus worden opgeteld en als één bedrag in het veld accijnzen gezet; ontbreekt een kolom in het bestand, dan telt ze gewoon niet mee. De klant hoeft daarna enkel F8 te doen en niets zelf te rekenen. Antwoord aan de klant: we zoeken de eenvoudigste oplossing; geen eigen workaround voorstellen.
- **Status:** aanpassing was deels uitgevoerd tijdens de bespreking; eindresultaat onbekend.
- **Bron:** ticketbespreking 17-06-2026, ca. 00:33–00:42.

### E-mailadressen van klanten die dit jaar gekocht hebben naar Excel
- **Symptoom:** de klant wil een Excel met e-mailadressen van enkel de actieve klanten (bv. afname in de laatste zes maanden), eventueel per soort klant. Een eerder antwoord was dat enkel álle e-mailadressen geëxporteerd kunnen worden.
- **Controles / diagnose:** de gewone Excel-export van klanten (velden aanvinken zoals naam, adres, e-mail, soort klant) kan niet filteren op afname. Het omzetveld op de klantfiche wordt jaarlijks gewist en is dus geen betrouwbare filter voor "laatste zes maanden".
- **Oplossing:** via de uitgebreide statistieken.
  1. Hoofdmenu → punt 4 "Raadpleging historiek, statistieken, prijzen" → punt 3 "Uitgebreide statistieken" (punt 1 en 2 zijn voor één klant of één artikel).
  2. Eerst **berekenen** (F9): kies statistiek **5 = klantenomzet** (alles berekenen kan ook, duurt langer), geef de periode in (bv. 01-01-26 tot 30-06-26). Optioneel: selectie op soort klant (bv. C = café, R = restaurant), op voorwaarde dat dit op de klantfiches is ingevuld. Bevestig met F8. Achter de statistiek verschijnen berekeningsdatum en periode.
  3. Blijf op het overzichtsscherm, **tik het nummer van de statistiek in (5)** en kies afdrukken (F10 / printericoon).
  4. Vink in het keuzescherm enkel aan wat nodig is: klant, adres, postcode, plaats, **e-mail**. Vink groepen, artikelen, facturen en liters uit. Bedragen aanzetten kan nuttig zijn om kleine klanten uit een mailing te weren.
  5. Kies Excel: het bestand verschijnt onderaan.
- **Opmerking:** het e-mailadres in deze statistiek is een relatief recente toevoeging (circa twee jaar oud); bij een zeer oude programmaversie eerst updaten.
- **Status:** opgelost in bespreking.
- **Bron:** ticketbespreking 23-06-2026, ca. 00:04–00:17 en 00:26.

### Statistiek afdrukken geeft maar één klant (of geen totaal)
- **Symptoom:** de klant wil een statistiek van al zijn klanten afdrukken, maar krijgt telkens maar één klant, zonder algemeen totaal. Komt volgens de expert elke maand voor.
- **Oorzaak:** de gebruiker heeft op de statistiek geklikt en staat dus al een niveau dieper; het printericoon drukt dan enkel de aangeduide klant af.
- **Oplossing:** terug naar het overzicht van de uitgebreide statistieken (kruisje), daar het **nummer van de statistiek intikken** in plaats van erop te klikken, en dan afdrukken (F10). Dan verschijnt ook de optie "totaal" en komen alle klanten op de lijst. Standaard staan de meest gebruikte kolommen aangevinkt; zet uit wat niet nodig is en kies PDF of Excel.
- **Nuttig om te weten (zelfde scherm):** met "+" ga je telkens een niveau dieper (klant → groep → artikel → factuur), met "-" terug. Beschikbare statistieken o.a.: evolutie klanten/artikelen (vergelijking met dezelfde periode vorig jaar), rendement klanten/artikelen (verkoopwaarde, aankoopwaarde, winst in euro en %; rendement klanten = nummer 3), klantenomzet, artikelomzet, omzet per leverancier, klantenkortingen (nummer 8: factuurkorting en uitgestelde korting), omzet per maand, aankopen per leverancier/artikel. Altijd eerst laten berekenen.
- **Status:** opgelost in bespreking.
- **Bron:** ticketbespreking 23-06-2026, ca. 00:15 en 00:28–00:30.

### Facturen worden op één pc niet meer afgedrukt
- **Symptoom:** op één bepaalde werkpost komen facturen niet meer uit de printer; op andere posten wel.
- **Oorzaak:** op die post staat een verkeerde of niet meer bestaande printer ingesteld (bv. nadat een printer is toegevoegd of een nieuwe standaardprinter is gekozen).
- **Controles / diagnose:**
  1. Neem het scherm van die post over en open bovenaan **Configuratie → Documenten**.
  2. Bepaal onder welk documenttype de facturen vallen: drukt de klant facturen op A4, dan vallen ze onder **Lijsten** (het type "Matrix" is voor de vroegere naaldprinters). In de parameters (via "+") is na te kijken dat facturen op A4/als lijst worden gedrukt.
  3. Vergelijk met de instelling op een pc waar het wel werkt.
- **Oplossing:** kies bij Lijsten de juiste, werkende printer. Lukt het nog niet: druk in Windows een testpagina af op die printer; komt die eruit, dan moet het ook vanuit Jamadata werken.
- **Status:** aanpak besproken, uitkomst onbekend.
- **Bron:** ticketbespreking 25-06-2026, ca. 00:02–00:04.

---

## 2. Peppol / mail

### Pakket meldt dat een klant niet op Peppol zit (of "fout btw-nummer"), terwijl er vroeger wel via Peppol gefactureerd werd
- **Symptoom:** bij het versturen van een factuur naar een bepaalde afnemer komt een melding over het btw-nummer / "niet op het Peppol-netwerk". Vroeger lukte verzenden naar die afnemer wel.
- **Controles / diagnose (in volgorde):**
  1. Open de klantfiche en controleer het btw-nummer: rechtsklik → **btw-nummer opzoeken**. Het nummer moet actief zijn en de officiële naam (KBO) tonen.
  2. Zoek de afnemer op in de publieke Peppol Directory. Zoeken op naam geeft bij korte namen te veel resultaten; zoek op identificatie:
     - `0208:` + ondernemingsnummer **zonder** "BE";
     - `9925:` + btw-nummer **met** "BE" (in de transcriptie één keer als "9955" verstaan; te verifiëren in de Peppol-FAQ);
     - `0088:` + GLN-nummer.
     Het zoekveld is gevoelig: verwijder punten, spaties en overbodige tekens. Een afnemer hoort normaal op beide manieren (0208 en 9925) vindbaar te zijn.
  3. Controleer eventueel in een tweede publieke Peppol-zoeksite.
  4. Controleer in het pakket de Peppol-status van de klant (klantfiche, via "+"; toets onzeker) en bij welke provider de eigen klant zit (hoofdmenu "+" → 5 → meermaals F8, onzeker). De infoknop met providergegevens werkt bij CodaBox, niet bij de andere provider.
- **Oplossing:**
  - Is de afnemer nergens te vinden: hij is (tijdelijk) niet meer geregistreerd, bv. door een wissel van provider. Dat moet de afnemer zelf met zijn provider regelen.
  - Is de afnemer wél vindbaar op het netwerk maar blijft het pakket hem weigeren: zelf niets forceren. Documenteer alle uitgevoerde controles en gebruikte links in de interne dialoog en zet het ticket door naar de programmeur (derde lijn), die het zo nodig aan de Peppol-provider voorlegt.
- **Status:** aanpak besproken, uitkomst onbekend (resultaten van de zoeksites waren tegenstrijdig; vermoeden dat de oorzaak bij de afnemer ligt).
- **Bron:** ticketbespreking 18-06-2026, ca. 00:08–00:22.

### Afnemer zegt een Peppol-factuur niet ontvangen te hebben
- **Symptoom:** de klant meldt dat facturen naar een bepaalde afnemer "niet meer via Peppol lukken" of dat de afnemer ze niet krijgt.
- **Controles / diagnose:**
  1. Ga in het pakket van de klant naar het herafdrukken/raadplegen van facturen (in de bespreking: 8 → H → 1, onzeker), zoek de afnemer en open de laatste factuur.
  2. Klik op het **wolkje** bij de factuur: dat toont de Peppol-status. Controleer ook de voorlaatste factuur.
- **Oplossing:**
  - Status **Delivered**: de factuur is afgeleverd op het Peppol-netwerk. Het probleem ligt dan bij de ontvanger (zijn boekhoudpakket of provider). Meld dit zo aan de klant.
  - Vraagt de klant om opnieuw te sturen: vanuit hetzelfde scherm Stoppen → F8, F8 → **F5** (opnieuw verzenden).
- **Status:** opgelost in bespreking (facturen stonden op Delivered).
- **Bron:** ticketbespreking 17-06-2026, ca. 01:01–01:03.

### Peppol: "certificaatbestand bestaat niet" / "ongeldig certificaat" na een programma-update
- **Symptoom:** versturen via Peppol is geblokkeerd; het programma meldt dat het certificaatbestand niet bestaat of ongeldig is. Trad die week bij drie klanten op nadat nieuwe programma's waren geplaatst.
- **Oorzaak:** niet met zekerheid vastgesteld; vermoeden dat de Jamadata-installatie ooit op een andere schijf stond en dat het bij de installatie misliep. Terugzetten van een oude `ems.ini` hielp niet.
- **Oplossing:** de installatie volledig opnieuw opbouwen "zoals bij een nieuwe klant":
  1. Nieuwe map Jamadata aanmaken (eventueel op een andere schijf).
  2. Enkel de **datamappen** manueel overzetten (o.a. `FAS`, `FTCOPY`); geen oude rommel meenemen.
  3. De programmamap (`PROG`) wordt door de programmeur opnieuw klaargezet.
  4. Daarna alles controleren wat naar het oude pad of de oude share verwijst (zie case "Digitale prijskaartjes werken niet meer na verhuis").
  - Doe dit samen met de programmeur. Ervaring uit een vergelijkbaar geval: na een half uur tot drie kwartier draaide de klant opnieuw.
- **Status:** opgelost (herinstallatie in een andere map uitgevoerd tussen 24 en 25 juni); neveneffect op de koppeling met de digitale prijskaartjes apart behandeld.
- **Bron:** ticketbespreking 24-06-2026, ca. 00:05–00:09; 25-06-2026, ca. 00:06 en 00:10.

### Pakket crasht bij het maken van een factuur (kassa en Peppol op de hoofdcomputer)
- **Symptoom:** telkens bij het maken van een factuur aan de kassa verschijnt een fout / crasht het pakket; later bleek hetzelfde bij een factuur via Peppol op de hoofdcomputer. Ook de infoknop met de providergegevens deed het pakket crashen.
- **Oorzaak:** vermoedelijk de virusscanner die de communicatie blokkeert.
- **Oplossing:** de virusscanner uitschakelen (of Jamadata erin uitsluiten) en de dag nadien navragen of de fout wegblijft.
- **Status:** aanpak besproken; na het uitzetten van de virusscanner was er die dag nog geen fout gemeld, definitieve uitkomst onbekend.
- **Bron:** ticketbespreking 18-06-2026, ca. 00:23–00:24.

### Bestelbonnummer van de afnemer staat niet in de juiste XML-tag van de Peppol-factuur
- **Symptoom:** een afnemer weigert of bemerkt Peppol-facturen omdat zijn bestelbonnummer niet in het juiste veld van het XML-bestand staat. De klant vraagt in welk veld hij dat nummer moet ingeven.
- **Oplossing:** alles wat specifiek voor de afnemer in het Peppol-bestand moet meekomen (bestelbonnummer, PO-nummer) hoort in het veld **Referentie** bij het maken van de factuur (facturatie → factuur maken → klant kiezen → F8: daar staat het veld Referentie).
  - Sommige klanten hebben op maat twee referentievelden; gebruik standaard het eerste. Het tweede is dan afgesproken maatwerk waarvan de klant zelf weet waarvoor het dient.
  - Stuur een schermafdruk met het veld aangeduid, genomen in het pakket van de klant zelf (de layout kan verschillen) en zonder klantgegevens in beeld.
- **Status:** opgelost in bespreking (antwoord met schermafdruk klaargezet).
- **Bron:** ticketbespreking 24-06-2026, ca. 00:50–00:54.

### Klant vraagt self-billing (bv. creditnota's van energieleverancier of loterij via Peppol)
- **Symptoom:** de klant ontvangt via inkomende Peppol documenten die een leverancier in zijn naam opmaakt (bv. vergoeding voor teruggeleverde stroom) en vraagt om "self-billing".
- **Uitleg:** de leverancier stuurt in plaats van een eigen creditnota een document dat bij de klant als **verkoopfactuur** moet geboekt worden.
- **Oplossing:** self-billing staat standaard niet aan; het moet door de programmeur/tweede lijn geactiveerd worden, zowel in het pakket als bij de Peppol-provider (CodaBox of de andere provider). Zet het ticket op de juiste klant en schuif het door naar de derde lijn.
- **Status:** aanpak besproken, uitkomst onbekend.
- **Bron:** ticketbespreking 17-06-2026, ca. 00:46–00:48.

### Mails vanuit Jamadata vertrekken niet (SMTP)
- **Symptoom:** e-mails vanuit het pakket komen niet aan; in de log staat `smtpmailer failed`.
- **Controles / diagnose:**
  1. In de `config`-map van de klant op de interne back-upschijf komen elke avond de mislukte mails terug als **EML-logbestanden** (EML = maillog).
  2. Open het recentste logbestand: het toont de dialoog met de mailserver; onderaan staat de eigenlijke **foutmelding** (error).
  3. In dezelfde config-map staat ook een kopie van de actuele `ems.ini` met de mailinstellingen van de klant.
- **Oplossing:** support lost de mailserver zelf niet op; bezorg de exacte foutmelding uit het logbestand aan de IT'er van de klant, die de SMTP-instellingen of het account moet rechtzetten.
- **Status:** aanpak besproken, uitkomst onbekend.
- **Bron:** ticketbespreking 17-06-2026, ca. 00:14–00:17.

### Begeleidende tekst in de e-mail bij een factuur aanpassen (mailtemplate)
- **Symptoom:** de klant wil een extra zin in de e-mail waarmee facturen verstuurd worden (in dit geval een verwijzing naar Peppol). In de bestaande mail stonden ook storende haakjes/tekens sinds een programma-update.
- **Controles / diagnose:**
  1. Het gaat om de tekst van de **e-mail**, niet om tekst op de factuur zelf.
  2. Bekijk de huidige mail: herafdrukken facturen → factuur kiezen (F8 …) → **Mailen** → **Bekijk mail**.
  3. De templates staan in de map `Jamadata\mail\templates`. Factuurtemplates beginnen met `fact` (bv. `fact1`); bij een tweetalig pakket bestaan `fact1N` en `fact1F` (Nederlands/Frans). De wijzigingsdatum verraadt welk bestand echt gebruikt wordt.
  4. Heeft de klant geen online back-up bij Jamadata, dan staan de templates niet op de interne schijf. Via de klantinstellingen kan tijdelijk "Today backup" geactiveerd worden om de bestanden eenmalig binnen te halen; anders het scherm overnemen.
- **Oplossing:**
  1. Handleiding: hoofdmenu "+" → JMS-/EMS-instellingen → mail → F8 → **vraagteken** bovenaan. In principe past de klant zijn template zelf aan met die handleiding.
  2. Doet support het: dat is maatwerk en gebeurt in regie (betalend), net als aanpassingen aan factuurlayouts of het overzetten van data naar een nieuwe server. Voor iets van enkele minuten wordt in de praktijk niets aangerekend.
  3. Snelle methode: open het templatebestand in een teksteditor (Kladblok), voeg de zin toe op de juiste plaats en bewaar. Tekst tussen vierkante haken komt uit de database en blijft staan. Overbodige codes (zoals `=20`) mogen weg.
  4. Bevat de template zowel een platte-tekstdeel als een HTML-deel (bv. bij een logo), dan moet de zin in **beide** delen komen; in het HTML-deel zit de tekst tussen opmaakcodes (font/span). Bij zo'n template is de handleiding/Outlook-methode veiliger.
  5. Test daarna opnieuw via Mailen → Bekijk mail.
  6. Denk mee met de klant: de template geldt voor **alle** gemailde facturen, ook naar afnemers zonder Peppol. Een zin die enkel voor Peppol-afnemers klopt, kan dus verwarrend zijn; meld dat in het antwoord.
- **Status:** opgelost in bespreking (aanpak getest in de demo; antwoord met handleiding en regiemelding naar de klant).
- **Bron:** ticketbespreking 25-06-2026, ca. 00:36–00:58.

---

## 3. Kassa / hardware

### Kassaverslag: bedrag bij btw 0 % klopt niet met de verkochte cadeaubon
- **Symptoom:** op het kassaverslag van een dag staat bij "verkopen per btw-percentage" een ander bedrag aan 0 % dan de waarde van de cadeaubon die die dag verkocht is (verschil van enkele euro's).
- **Controles / diagnose:**
  1. Controleer op de artikelfiche (F9 Vervolg) het btw-percentage van de cadeaubon. Hier stond het op 0 %, dus dat verklaart waarom het onder 0 % verschijnt. (De expert zou een cadeaubon zelf op 21 % zetten, maar dat is een keuze van de klant.)
  2. Controleer dat alle documenten over dezelfde dag en dezelfde kassa gaan. Behandel één dag/kassa per keer; meng geen twee dagen in één onderzoek.
  3. Bereken het verschil en zoek artikelen aan 0 % voor dat bedrag. Het bedrag aan 0 % kan lager uitvallen door negatieve lijnen (retours, bons) of hoger door andere 0 %-artikelen. Is het verschil de som van meerdere artikelen, dan vind je het niet door op het bedrag te zoeken.
  4. Hulplijsten in Jamadrink:
     - verkooplijsten kassa → verkopen per artikel (datum, kassa, bonverkopen uit, detail aan) naar Excel. Nadeel: geen btw-kolom.
     - artikellijst naar Excel met o.a. code, omschrijving, groep, prijs en **btw-percentage**; in Excel filteren op 0 % (bij deze klant 182 artikelen) en vergelijken met de verkopen van die dag.
     - "prijscontrole kassaverkopen" (datum, kassa, PDF): alle verkopen waar de verkoopprijs afwijkt van de normale kassaprijs.
  5. Beste bron: de **volledige controleband van die dag als PDF** (zie volgende case), waarin elk ticket staat.
  6. Typische 0 %-artikelen: tabak, loterijproducten, eventueel cadeaubons.
- **Oplossing:** PDF van de controleband van de betrokken kassa en dag laten maken en ophalen, daarin ticket per ticket naar de 0 %-lijnen zoeken. Bij klanten die dagelijks zulke verschillen melden: hen leren de PDF zelf te maken en erin te zoeken.
- **Status:** aanpak besproken, uitkomst onbekend (PDF was opgehaald, analyse nog niet gedaan).
- **Bron:** ticketbespreking 24-06-2026, ca. 00:10–00:48; opvolging 25-06-2026, ca. 00:05.

### Controleband van een kassadag als PDF maken en ophalen
- **Symptoom / nood:** support of de klant heeft alle tickets van één dag nodig om een kasverschil uit te zoeken; de klant scant losse tickets in plaats van een PDF te maken.
- **Oplossing (op de kassa):**
  1. Eerste scherm van de kassa → **F9 Controle**.
  2. "Gewenste dagen" op **enkel geselecteerde** zetten en de dag aanduiden (wordt rood).
  3. Selectie verkopen: **apart en in totaal**; alle kassiers; keuze periode: dag.
  4. **Controleband: ja**; "volgens PLU" mag op ja.
  5. Kies bovenaan **Maak PDF** (naast Druk af).
  6. De PDF komt in de map `kassa` op de kassa, met de datum als bestandsnaam (bv. `20260619.pdf`). Ze bevat de controleband (elk ticket), verkopen per artikel, verkopen per btw-percentage, het financieel overzicht en de particuliere verkopen. Bij een drukke winkel al snel 50 pagina's.
- **Ophalen:**
  - Scherm van de kassa overnemen en het bestand rechtstreeks naar je toe slepen; of
  - wachten op de online back-up: na het doorsturen van de kassa naar de hoofdcomputer komt de PDF in de map van die kassa terecht en met de back-up (meermaals per dag) ook op de interne back-upschijf onder de klant, `actual\kassa\kassa-NN`.
  - Zet opgehaalde bestanden in de klantmap op de gedeelde interne schijf, zodat collega's eraan kunnen.
- **Tip:** grotere klanten maken deze PDF elke dag en zoeken zelf bij een verschil. Oefen de procedure eerst op een testkassa.
- **Status:** opgelost in bespreking (procedure gedemonstreerd).
- **Bron:** ticketbespreking 24-06-2026, ca. 00:31–00:44.

### Bewaarde kassabon geeft na terug oproepen een ander totaal (promotie/mixpromo)
- **Symptoom:** een ticket met promotieartikelen wordt tijdelijk bewaard op een bonnummer. Meteen terug oproepen en afdrukken geeft het juiste totaal; wordt de bon na het oproepen nog aangepast, dan verandert de korting en dus het totaal (in het voorbeeld verdubbelde de korting).
- **Oorzaak:** vermoedelijk een programmafout bij (mix)promoties op bewaarde bons; de klant kon het reproduceren en heeft de laatste versie.
- **Controles / diagnose:**
  1. Een programmeur kan pas iets doen als support het zelf kan **reproduceren**. Daarvoor moet je weten welke promotie precies is ingegeven.
  2. Bij een klant waarvan het scherm niet op afstand over te nemen is (zelfstandige kassa zonder hoofdcomputer): de klant laten tonen of een lijst laten sturen via kassa aanpassen → **aanpassen/bekijken bestaande promoties**, met als periode de datum van het ticket (van = tot = die datum) → oproepen of **lijst promoties afdrukken** naar PDF. Promoties kunnen jaren doorlopen.
  3. In die lijst de promotie op de betrokken artikelen opzoeken.
  4. Dezelfde promotie in de demo op een willekeurig (vergelijkbaar) artikel ingeven en het scenario naspelen: ticket maken, bewaren, oproepen, aanpassen.
- **Achtergrond promotiefiche (kort):** periode van–tot; op artikel, leverancier of groep; toepassen op bak of fles; "vanaf aantal". Daarna precies **één** type voordeel: nieuwe promotieprijs, aantal stuks gratis (bv. 5+1: vanaf 6, 1 stuk gratis), percentage korting op een aantal stuks (100 % op 1 stuk kan ook), bedrag korting, gratis ander artikel, gestaffelde korting (bv. 5 % vanaf 6, 10 % vanaf 12) of een totaalprijs voor het aantal. **Mixpromo:** meerdere artikelen (niet tweemaal hetzelfde) tellen samen voor het aantal. Optie: maximaal één promotie per kasticket.
- **Oplossing:** ticket op "wachten op klant" met de vraag welke promotie is ingegeven; na reproductie in de demo doorgeven aan de programmeur.
- **Status:** aanpak besproken, uitkomst onbekend.
- **Bron:** ticketbespreking 18-06-2026, ca. 00:28–00:45.

### Koppeling met de geldautomaat (cash-automaat) wordt meerdere keren opgestart aan de kassa
- **Symptoom:** de klant ziet achter het kassascherm een hele reeks vensters; de koppeling met de geldautomaat staat drie keer open.
- **Oorzaak:** in `kasmenu.dat` wordt de koppeling bij het starten van de kassa opgestart, maar bij het afsluiten niet gestopt; de installatiehandleiding was op dat punt onvolledig. De klant had ook nog een oudere versie van de koppelingsbestanden.
- **Achtergrond:** `kasmenu.dat` bepaalt wat er rond de kassa gebeurt: oude logbestanden en PDF's opruimen, oude bons schrappen, Jamadata-desktop op de achtergrond starten (nodig voor facturen), bankterminalkoppeling starten, daarna `kassa.exe`; na het stoppen van de kassa wordt de desktop weer gesloten.
- **Oplossing:**
  1. Kassa overnemen (TeamViewer).
  2. De drie recente bestanden van de koppeling (uit de interne map met kassa-installatiebestanden) in de map `kassa` van de klant vervangen.
  3. `kasmenu.dat` in een teksteditor aanpassen: de startregel van de koppeling net **boven** `kassa.exe` moet met de **start-parameter** staan (in de transcriptie "#S", onzeker) en **na** `kassa.exe` moet een regel met de **stop-parameter** ("#C", onzeker) toegevoegd worden. Neem de exacte regels over uit de bijgewerkte installatiehandleiding van de geldautomaat-koppeling in de interne kassadocumentatie.
- **Status:** oorzaak en oplossing vastgesteld in bespreking; uitvoering bij de klant was nog gepland.
- **Bron:** ticketbespreking 18-06-2026, ca. 00:47–00:55.

### Digitale prijskaartjes (DIGI-koppeling) krijgen geen prijsupdates meer
- **Symptoom:** de leverancier van de elektronische schapetiketten meldt dat een winkel geen nieuwe artikeldata meer ontvangt; de laatste prijsupdate is weken oud. Aan Jamadata-zijde is niets gewijzigd.
- **Controles / diagnose:**
  1. Bepaal over welk dossier/filiaal en welke kassa's het gaat (klantinstellingen → kassa; in het dossier: voorraadmenu punt 2 → 3 toont de kassanummers).
  2. Kijk zonder de klant te storen in de directory-overview (`dir.lst`) van de klant en zoek op de kassamap (bv. `kassa-07`). Daar hoort het artikeldatabestand voor de etiketten te staan (naam begint met `art…`, zie volgende case).
  3. Controleer in dezelfde map de datum van het bestand waarin de uitwisseling hoofdcomputer ↔ kassa wordt bijgehouden (in de transcriptie "uckasd", onzeker). Een oude datum betekent dat er niets meer naar die kassa gaat.
- **Oplossing:** ontbreekt het artikeldatabestand, dan moeten in het instellingenbestand van de kassa twee regels voor de DIGI-export (opnieuw) toegevoegd worden. Dit is werk voor de tweede/derde lijn: kassa overnemen, bestand aanpassen en controleren dat het bestand opnieuw binnenkomt.
- **Status:** aanpak besproken, uitkomst onbekend.
- **Bron:** ticketbespreking 17-06-2026, ca. 00:55–01:01.

### Digitale prijskaartjes werken niet meer na verhuis van de Jamadata-map (nieuwe share)
- **Symptoom:** na een herinstallatie van Jamadata in een andere map/op een andere schijf (zie Peppol-certificaatcase) werken de digitale prijskaartjes niet meer.
- **Oorzaak:** de software van de etikettenleverancier leest het artikeldatabestand via een **netwerkshare** op de hoofdcomputer. Door de verhuis staat het bestand op een andere plaats en is de naam van de share gewijzigd (de oude share bestond nog, de installatie maakte een nieuwe aan).
- **Controles / diagnose:**
  1. Zoek in `dir.lst` van de klant waar de exportbestanden staan: een databestand `.dat` met een bijhorend `.vlag`-bestand (in de transcriptie "artikeldata.dat / .vlag", in de kassamap ook "digi-art.dat / .vlag"; exacte namen te verifiëren). Bij de meeste klanten staan ze in de **share-map** van Jamadata op de hoofdcomputer; staat de kassa op een andere locatie, dan op de kassa zelf.
  2. Neem de hoofdcomputer over (bovenaan Configuratie → verbinden via TeamViewer). Open Windows Verkenner en ga via Netwerk of `\\computernaam` naar de gedeelde mappen; controleer in welke share de bestanden met de datum van vandaag staan.
  3. Krijg je "geen rechten" op de share: rechtsklik op de map → delen met specifieke personen → opnieuw delen met de juiste rechten.
- **Oplossing:** bezorg de etikettenleverancier het nieuwe netwerkpad in de vorm `\\computernaam\sharenaam` (twee backslashes voor de computer, één voor de map), met de vermelding dat gebruikersnaam en wachtwoord ongewijzigd zijn (de standaard share-gebruiker die de Jamadata-installatie aanmaakt; gegevens: zie interne bron). De leverancier past de koppeling dan zelf op afstand aan. Mail dit rechtstreeks naar de contactpersoon van de leverancier, want een antwoord in het ticket bereikt hem niet.
- **Les:** bij elke verhuis van de Jamadata-map alle externe koppelingen nalopen die naar het oude pad of de oude share wijzen.
- **Status:** opgelost in bespreking wat Jamadata betreft (nieuw pad doorgegeven); bevestiging van de leverancier nog niet binnen.
- **Bron:** ticketbespreking 25-06-2026, ca. 00:06–00:34.

---

## 4. PDA / scanners

In de vijf besprekingen is geen PDA- of scannerprobleem inhoudelijk behandeld. Er werd enkel een openstaand ticket voor de installatie van een nieuwe PDA van eigenaar gewisseld, zonder technische inhoud (24-06-2026, ca. 00:03).

---

## 5. Server / IT

### PDF's uit Jamadata openen of drukken niet meer af; mails (.eml/.msg) kunnen niet meer verzonden worden
- **Symptoom:** (a) de klant krijgt geen PDF's meer geopend/afgedrukt vanuit Jamadata; of (b) mails die Jamadata klaarzet openen wel, maar kunnen niet verzonden worden. Komt volgens de expert bijna wekelijks voor.
- **Oorzaak:** de Windows-standaardapp voor het bestandstype is gewijzigd (vaak door een Windows- of Office-update): `.pdf` staat op een programma dat geen PDF kan openen, of `.eml`/`.msg` staat op het nieuwe Outlook in plaats van het klassieke.
- **Oplossing:**
  1. Windows → **Standaard-apps** → bovenaan het bestandstype intikken (`.pdf`) en Enter.
  2. Kies het gewenste programma: Acrobat Reader of Edge. Veel gebruikers verkiezen Acrobat Reader omdat afdrukken vanuit Edge anders werkt dan ze gewoon zijn.
  3. Voor `.eml` en `.msg`: beide instellen op **Outlook (klassiek)**. Met het nieuwe Outlook openen de mails wel, maar kunnen ze niet verzonden worden.
- **Status:** opgelost in bespreking (ticket afgesloten).
- **Bron:** ticketbespreking 18-06-2026, ca. 00:01–00:05.

### Kassa/pc onbereikbaar na een stroompanne
- **Symptoom:** na een stroomonderbreking werkt de communicatie niet meer; de klant denkt dat de Jamadata-server (JMS) niet gestart is.
- **Controles / diagnose:** in het interne beheeroverzicht van de klant staat de dienst wel op "gestart", maar de **last heartbeat** is blijven steken op het tijdstip van de panne. Dat betekent dat de computer geen verbinding meer maakt met de Jamadata-servers: hij heeft geen internet.
- **Oorzaak:** vermoedelijk heeft de pc een vast IP-adres dat na de herstart/reset van de router niet meer past, of de router is niet correct heropgestart.
- **Oplossing:** de klant (of zijn IT'er) moet eerst de internetverbinding van die pc herstellen: router en netwerkinstellingen nakijken. Overnemen op afstand lukt niet zolang er geen internet is. Tijdelijk kan een IT'er de pc op DHCP zetten (in de transcriptie onduidelijk, te verifiëren).
- **Status:** aanpak besproken, uitkomst onbekend.
- **Bron:** ticketbespreking 23-06-2026, ca. 00:02–00:03.

### Scherm van Jamadata zit vast (verbinding herstellen) versus werkpost resetten
- **Symptoom:** een Jamadata-scherm reageert niet meer.
- **Oplossing:**
  - **Verbinding herstellen (ongevaarlijk):** via de functie bovenaan het venster (scherm op afstand / verbinding) wordt de verbinding met de communicatieserver verbroken en opnieuw opgezet. Alle schermen blijven staan waar ze waren en het geldt enkel voor deze werkpost. Dit mag zo vaak als nodig; er kan niets mee misgaan.
  - **Deze werkpost resetten** (via Help/Configuratie → deze werkpost): zet alle (vier) schermen van die werkpost terug op het hoofdmenu. Gebruik dit pas als het herstellen van de verbinding niet helpt. Het uitvoeren van systeemfuncties vereist dat op de werkpost de optie "mag systeemprogramma's uitvoeren" aanstaat; een wijziging daarvan is pas actief na de nachtelijke herstart van de database.
- **Status:** opgelost in bespreking (verbinding herstellen toegepast).
- **Bron:** ticketbespreking 23-06-2026, ca. 00:47–00:49; 17-06-2026, ca. 00:07–00:08.

### Bestanden en instellingen van een klant bekijken zonder het scherm over te nemen
- **Nood:** snel nagaan welke bestanden bij een klant staan of welke instellingen hij gebruikt, zonder de klant te bellen.
- **Oplossing:** van klanten met online back-up staat op de interne back-upschijf per klantcode een map (structuur `…\FromKLT\<klantcode>\`):
  - `config\dir.lst`: volledige directorylijst van de Jamadata-map van de klant (groot bestand, tot ca. 20 MB; gebruik Bewerken → Zoeken, bv. op `FAS_OLD`, `kassa-07` of een bestandsnaam).
  - `config\`: kopie van de actuele `ems.ini` (werkposten, e-mailinstellingen, ...) en de EML-logbestanden van mislukte mails.
  - `actual\kassa\kassa-NN\`: alles wat van elke kassa terugkomt, inclusief controleband-PDF's.
  - `mail\templates` en andere mappen, voor zover ze in de back-up zitten. `FTCOPY` komt standaard niet mee.
  - Staat er bij een klant "no online backup", dan kan via de klantinstellingen tijdelijk **Today backup** aangezet worden: de bestanden worden dan eenmalig opgehaald en blijven enkele dagen staan.
- **Status:** werkwijze gedemonstreerd.
- **Bron:** ticketbespreking 17-06-2026, ca. 00:09–00:15 en 00:57; 24-06-2026, ca. 00:29 en 00:37–00:41; 25-06-2026, ca. 00:40–00:42.

### Oude programmaversie zonder TeamViewer-knop
- **Symptoom:** de klant heeft een zeer oude versie; onder Configuratie ontbreekt "verbinden via TeamViewer" en de klant krijgt de download niet zelf voor elkaar.
- **Oplossing:** de klant begeleiden om de ondersteuningstool manueel te downloaden en uit te voeren, daarna de post updaten zodat de knop voortaan beschikbaar is. Normale werkwijze bij recente versies: bovenaan Configuratie → verbinden via TeamViewer → het gedownloade bestand uitvoeren → ID (en wachtwoord) doorgeven.
- **Status:** opgelost (update uitgevoerd), details beperkt.
- **Bron:** ticketbespreking 23-06-2026, ca. 00:03–00:04; 25-06-2026, ca. 00:23–00:24.

---

## 6. Boekhouding

In deze besprekingen kwam geen ticket over de boekhoudmodule zelf aan bod. Raakpunten met boekhouding:
- het terugdraaien van een foutief ingeboekte rechtstreekse aankoop (zie "Rechtstreekse aankoop (punt 7) per vergissing ingeboekt" onder Jamadrink / facturatie);
- self-billing: document van de leverancier dat als verkoopfactuur geboekt moet worden (zie Peppol / mail).

---

## 7. Werkafspraken voor ticketbehandeling (uit dezelfde besprekingen)

Geen ticketcases, wel terugkerende afspraken die het antwoord aan de klant beïnvloeden:
- **Eerst analyseren en reproduceren.** De analyse duurt vaak langer dan de oplossing. Een ticket zonder uitleg doorschuiven naar de programmeurs komt gewoon terug; noteer in de interne dialoog wat je al controleerde en wat je niet begrijpt.
- **Interne opmerkingen horen in de interne dialoog**, niet in het antwoord dat de klant ziet.
- **Bijlagen in een ticketantwoord** ziet de klant enkel via het klantenportaal, niet in de e-mail. Heeft de klant geen portaalaccount, maak er dan een aan of mail de bijlage apart.
- **Koppel het ticket aan de juiste klant.** Een contactpersoon van een externe leverancier (die voor tientallen klanten werkt) niet als contact aan één klant hangen: zijn tickets komen dan automatisch bij de verkeerde klant terecht.
- **Laat een ticket nooit op "updated" staan**: zet het terug op een lijn of op "wachten op klant", anders wordt een volgende reactie van de klant niet opgemerkt.
- **Oude tickets zonder reactie**: eerst melden dat het ticket wordt afgesloten als er binnen twee weken geen reactie komt, dan sluiten; bij terugkeer van het probleem maakt de klant een nieuw ticket.
- **Schermafdrukken voor klanten**: neem ze in het pakket van de klant zelf (layouts verschillen) en zorg dat er geen gegevens van andere klanten op staan.
- **Regie**: alles wat maatwerk is (layouts, mailtemplates, data overzetten naar een nieuwe server) is betalend; standaardfunctionaliteit uitleggen niet.
- **Bellen is vaak sneller** dan een lang ticketantwoord, zeker bij uitlegvragen.

Bron: ticketbesprekingen 17-06-2026 (ca. 00:17, 00:48–00:55), 18-06-2026 (ca. 00:25–00:28), 23-06-2026 (ca. 00:35–00:37), 24-06-2026 (ca. 00:02, 00:06, 00:49, 00:55), 25-06-2026 (ca. 00:44–00:45).

---

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot), Whisper-transcripties:
- Tickets bespreken-20260617_135947-Opname van vergadering.txt
- Tickets bespreken-20260618_110044-Opname van vergadering.txt
- Tickets bespreken-20260623_140554-Opname van vergadering.txt
- Tickets bespreken-20260624_100303-Opname van vergadering.txt
- Tickets bespreken-20260625_140516-Opname van vergadering.txt
