# Boekhouding in Jamadata: praktijkkennis uit de opleidingen juni–juli 2026

Gebruik dit document voor: helpdeskvragen over het opzoeken van facturen en betalingen van klanten en leveranciers (boekhouding punt 4), journaalnummers, het manueel ingeven van betalingen (kas en bank), het afpunten/koppelen van betalingen aan facturen, het inboeken van aankoopfacturen, de melding dat niet meer geboekt kan worden vóór een bepaalde datum, en een overzicht van het boekhoudmenu. Bedoeld voor supportmedewerkers zonder boekhoudkundige achtergrond.

> **Let op – bron is gesproken opleiding.** Deze inhoud komt uit automatisch getranscribeerde (Whisper) opleidingssessies. Menupunten en toetsen zijn zo goed mogelijk gereconstrueerd en kunnen herkenningsfouten bevatten. Controleer bij twijfel tegen de handleidingen van de boekhouding (het vraagteken `?` bij het menupunt). Boekhoudkundige keuzes (welke grootboekrekening, btw-code, …) zijn de verantwoordelijkheid van de klant en zijn boekhouder.

**Boekhoudmenu openen:** Hoofdmenu voorraad > **B** (boekhoudmenu).

---

## 1. Basisbegrippen in één oogopslag

- De boekhouding dient om **facturen op te volgen**: verkoopfacturen (komen **automatisch** uit de facturatie), aankoopfacturen (manueel of via Peppol in te boeken) en betalingen. Al het andere (btw-aangifte, listings, balansen) zijn lijsten die daaruit volgen.
- **Klant = debiteur**: zijn facturen staan aan de **debetkant**. **Leverancier = crediteur**: zijn facturen staan aan de **creditkant**. Een creditnota staat aan de andere kant dan de factuur.
- **Grootboekrekening**: rekening waarop geboekt wordt (bv. verkopen = 7-rekeningen, btw = bepaalde 4-rekeningen).
- **Journaal** (dagboek): elk soort verrichting heeft een journaalnummer (zie hoofdstuk 3).
- **Referentie** van een factuur = **jaartal – journaalnummer – volgnummer**.

(opleiding 02-07-2026, ca. 00:45–00:52; 07-07-2026, ca. 00:03–00:05 en 00:28)

---

## 2. Punt 4: het belangrijkste scherm (opzoeken)

**Waar:** Boekhoudmenu > **4**. Hier vertrekt bijna elke boekhoudvraag: staat een factuur open, is ze betaald, hoe is ze geboekt, opnieuw afdrukken of opnieuw via Peppol versturen.

### 2.1 Opvragen
- Kies **K** (klant), **L** (leverancier) of **G** (grootboekrekening), geef de naam in en **F8**.
- Bestaat dezelfde naam als klant én als leverancier en krijg je niets te zien: controleer of K of L juist staat.
- Vanop de klantfiche (9 > 2 > 1 > `+`) kan ook "boekhoudrekening" of "openstaande facturen" gekozen worden, maar daar kan je **geen periode** opgeven. Voor een overzicht over oudere jaren moet je via punt 4.

### 2.2 Periode: waarom zie ik oude facturen niet?
Onderaan het beginscherm van punt 4 staan twee datums:
- **"boekhouding afgesloten tot en met …"**: betaalde/afgepunte verrichtingen van vóór die datum worden standaard niet getoond;
- **"gewist tot …"**: alles van vóór die datum is echt verwijderd (gearchiveerd) en kan niet meer opgevraagd worden.

Wil de klant ook de betaalde facturen van vroegere jaren zien: vul bij **periode** zelf een **begindatum** in (bv. de eerste dag na de wisdatum) en neem dan F8. Standaard start het overzicht vanaf de afsluitdatum. (30-06-2026, ca. 00:04–00:09)

### 2.3 Het overzicht lezen
Per lijn: journaal, volgnummer, datum, bedrag in debet of credit, referentie, eventuele opmerking.
- Journaal **13** = verkoopfactuur (of creditnota), **11** = aankoopfactuur, een bank- of kasjournaal = betaling.
- **Openstaande** posten staan in een andere kleur dan **afgepunte/betaalde** (in de demo: betaald in het blauw).
- **F4** = enkel openstaande posten tonen; er is ook een icoon voor de **vervallen** posten.

Iconen achter een lijn:
- **`+` (detail)**: hoe de verrichting geboekt is (grootboekrekeningen en bedragen).
- **Factuur-icoon** bij een verkoopfactuur: doorloopt de schermen van de factuur opnieuw; daar kan ze naar **pdf**, opnieuw **gemaild**, opnieuw **via Peppol verstuurd** of op Peppol **gecontroleerd** worden – alles wat via "herafdrukken facturen" kan. Klanten gebruiken dit vaak in plaats van het herafdrukmenu.
- **PDF-icoon** bij een aankoopfactuur: opent de originele factuur, maar **enkel voor facturen die via Peppol zijn binnengekomen**.

(02-07-2026, ca. 00:45–00:57; 07-07-2026, ca. 00:03–00:09 en 00:36)

---

## 3. Journaalnummers

**Waar ze staan:** Boekhoudmenu > **+** (parameters) > **3** (boekhoudparameters) > F8, F8: tabel met alle journalen en hun type.

| Nummer | Betekenis | Vast? |
|---|---|---|
| **11** | aankoopfacturen | bij (bijna) alle klanten |
| **13** | verkoopfacturen | bij (bijna) alle klanten |
| **17** | kas | bij bijna alle klanten; extra kassen/filialen kunnen eigen kasjournalen hebben |
| 15, 16, 18, 19 | meestal banken | verschilt per klant |
| 12 / 14 | soms apart journaal voor creditnota's aankoop / verkoop | uitzondering |
| 29 | meestal diverse verrichtingen (rechtzettingen) | meestal |
| 30-reeks | overschrijvingen / betalingen onderweg (bv. voor SEPA) | verschilt |
| 99 | openingsbalans | standaard aanwezig |

Type in de tabel: 1 = aankoop, 2 = verkoop, 3 = bank, 4 = kas. Onthoud vooral **11, 13 en 17**; de banknummers zie je in de tabel van de klant. Nieuwe journalen aanmaken is werk voor Jamadata/boekhouder; kijk bij twijfel hoe het bij een vergelijkbare klant of in de demo staat. (02-07-2026, ca. 00:46–00:51; 07-07-2026, ca. 00:22)

---

## 4. Betalingen manueel ingeven

**Waar:** Boekhoudmenu > **2** (inbrengen financiële en diverse verrichtingen) > **1** (manueel financieel). De andere punten onder 2 zijn automatische hulpmiddelen (zie hoofdstuk 7).

### 4.1 Algemene werkwijze
1. Journaal kiezen (17 = kas, of het journaal van de bank), F8.
2. **Bank**: uittrekselnummer en datum; het scherm toont het **vorige saldo**. Geef het **nieuwe saldo** van het uittreksel in.
   **Kas**: geen uittreksel; het nummer wordt automatisch de omgekeerde datum (maand + dag). Hier is het vaak handiger om met **Tab** naar "ingekomen bedrag" te gaan en het bedrag zelf in te geven in plaats van het nieuwe saldo.
3. F8 → verdeelscherm: het bedrag moet verdeeld worden over één of meer facturen/rekeningen. Bovenaan staat **"nog te verdelen"**.
4. Per lijn: bedrag + K/L/G + naam en de **referentie van de betaalde factuur**.
5. Is "nog te verdelen" = 0: **F8** en nog eens F8 om te boeken. Het saldo is bijgewerkt en het scherm gaat naar het volgende uittreksel.

### 4.2 De factuur laten zoeken
- **Eén factuur, exact bedrag**: bedrag ingeven, **geen klant invullen** en **F10 (zoek)**: het pakket zoekt de openstaande factuur met exact dat bedrag (zowel bij klanten als bij leveranciers). Lijnnummer kiezen, F8: klant en referentie worden automatisch ingevuld.
- **Meerdere facturen in één betaling**: de klant ingeven, F8 → zijn openstaande facturen; **F10 "zoek combinatie"** zoekt welke facturen samen het bedrag vormen (in het groen). Telkens een lijnnummer kiezen + F8 tot alles verdeeld is.

### 4.3 Plus en min – denk aan je eigen bankrekening
- Geld dat **binnenkomt** (klant betaalt): nieuw saldo = vorig saldo **+** bedrag; bedrag positief verdelen.
- Geld dat **buitengaat** (leverancier betalen): nieuw saldo = vorig saldo **−** bedrag (staat de rekening al negatief, dan wordt ze nog negatiever), en bij het verdelen moet het bedrag **ook negatief** ingegeven worden. Dat minteken vergeten is een veelgemaakte fout.
- Klopt het saldo niet tot op de cent, dan blijft er een bedrag "nog te verdelen" en kan er niet geboekt worden.

(07-07-2026, ca. 00:10–00:28 en 00:37–00:40)

---

## 5. Afpunten: wanneer staat een factuur als betaald?

Een factuur valt weg uit de openstaande posten als twee voorwaarden voldaan zijn:
1. **debet = credit** (factuur en betaling(en) heffen elkaar op), én
2. de **referenties zijn gelijk** (de betaling draagt de referentie jaar-journaal-volgnummer van de factuur).

De referentie is nodig omdat het pakket anders niet weet welke betaling bij welke factuur hoort (bv. tien facturen van hetzelfde bedrag).

**Symptoom:** de betaling staat bij de klant/leverancier, het bedrag klopt, maar de factuur blijft openstaan → de referentie van de betaling is leeg of anders. Oplossingen in punt 4:
- de referentie van de betalingslijn manueel gelijk zetten aan die van de factuur; of
- het **koppel-icoon** bovenaan: bij de niet-gekoppelde lijnen verschijnen groene icoontjes; klik de lijnen aan die bij elkaar horen (het getoonde saldo moet 0 worden) en bevestig het koppelen. Het pakket zet dan de referenties gelijk. Zo kunnen ook meerdere betalingen aan één factuur gehangen worden.

(07-07-2026, ca. 00:06–00:08 en 00:40–00:42)

---

## 6. Aankoopfacturen inboeken

**Waar:** Boekhoudmenu > **1** (inbrengen facturen):

| Punt | Gebruik |
|---|---|
| 1 inkomende facturen | **dit punt gebruik je**; een creditnota geef je hier **negatief** in |
| 2 inkomende creditnota's | enkel als de klant een apart journaal voor aankoopcreditnota's heeft (bv. 12) |
| 3 / 4 uitgaande facturen / creditnota's | normaal nooit: verkoopfacturen komen automatisch uit de facturatie |
| P | inboeken van **inkomende Peppol-facturen** |

**Werkwijze punt 1:**
1. Volgnummer (stelt het pakket voor) en **leverancier**; een eventuele memo van de leverancier wordt getoond (bv. "boek op rekening …").
2. **Totaalbedrag inclusief btw** (wat aan de leverancier betaald moet worden).
3. Btw-bedragen: **aftrekbare btw** (normaal geval), niet-aftrekbare btw, btw EU/medecontractant (bijzondere gevallen).
4. Onderaan de lijnen: bedrag exclusief btw + **grootboekrekening** (de eerste letters intikken en zoeken, Tab of F7) + eventuele opmerking.
5. **Controle:** rechtsonder toont het scherm het verschil tussen debet en credit; dat moet nul zijn (bv. 1000 goederen + 106 btw = 1106 totaal), anders kan niet geboekt worden.
6. Datums: de **boekdatum** mag afwijken van de factuurdatum (bv. factuur nog in de vorige periode boeken; ze verschijnt dan ook in de journalen van die periode en niet in die van de huidige). De **vervaldatum** wordt berekend met de betalingstermijn van de leveranciersfiche; staat daar een **disconto contant** (x % binnen y dagen), dan toont het scherm het discontobedrag en de uiterste datum.
7. **F8** = boeken; het scherm staat klaar voor de volgende factuur.

(07-07-2026, ca. 00:29–00:37 en 00:49)

---

## 7. Overige punten van het boekhoudmenu

- **2 > openstaande klantfacturen via lijst betalen**: overloopt alle onbetaalde (vervallen) klantfacturen en laat ze in één beweging betaald zetten op een gekozen rekening. Bedoeld om een achterstand weg te werken (bv. klant die pas later met de boekhouding start). Gebruikt een ander journaal.
- **SEPA**: maakt van de openstaande leveranciersfacturen één betalingsbestand voor de bank.
- **CODA**: leest de bankuittreksels elektronisch in en verwerkt ze automatisch (wat in hoofdstuk 4 met de hand gebeurt).
- Domiciliëringsopdrachten: bestaat, maar wordt nauwelijks gebruikt.
- Voor SEPA en CODA staan aparte handleidingen achter het `?`.
- **5 Lijsten** > 1 periodieke lijsten: journalen, btw-aangifte, balansen; selectie van–tot datum, van–tot journaal, factuur- of uittrekselnummer (niets invullen = alles). Begint met een fouten- en controlelijst. Lijsten afdrukken wijzigt niets.
- **6** grootte van de gebruikte bestanden; **8** facturatie (hetzelfde als in het voorraadmenu).
- **9 Basisgegevens**: leveranciers en klanten (dezelfde als in de voorraad) + **grootboekrekeningen** (aanpassen/bekijken; lijst van het rekeningenplan afdrukken via 9 > 3). De instellingen van een rekening (btw-vak, aankoop/verkoop, …) bepaalt de boekhouder; kijk voor een voorbeeld naar een gelijkaardige rekening.
- **Archiveren** (onderste punt): verwijdert betaalde/afgepunte verrichtingen. Niet zomaar uitvoeren; dit is de "gewist tot"-datum uit 2.2.

(07-07-2026, ca. 00:43–00:49; 11-06-2026, ca. 00:54–00:56)

---

## 8. Veelvoorkomende vragen

| Vraag / melding | Antwoord |
|---|---|
| "Ik kan niet meer boeken" / melding over datum te ver vóór of na de laatste archiverings-/afsluitdatum | De datum **"boeken enkel toegestaan na …"** staat in **Hoofdmenu > + > 3** (onderaan). Het is een beveiliging zodat er niets meer geboekt wordt in een afgesloten periode (anders kloppen de btw-aangiftes niet meer). Typische vraag rond de wissel van boekjaar; overleg met de klant/boekhouder vóór de datum gewijzigd wordt. (30-06-2026, ca. 00:09) |
| "Ik zie enkel de facturen van dit en vorig jaar" | Begindatum van de periode aanpassen in punt 4 (zie 2.2). (30-06-2026, ca. 00:07) |
| "Factuur is betaald maar blijft openstaan" | Referenties niet gelijk → koppelen (hoofdstuk 5). |
| "Ik vind de klant niet in de boekhouding" (klant met meerdere firma's) | Eerst nagaan in welke firma de klant zit; een klant bestaat maar in één firma. (30-06-2026, ca. 00:03) |
| "Hoe stuur ik een factuur opnieuw via Peppol / mail?" | Punt 4 > klant > factuur-icoon, of Facturatie > herafdrukken facturen. |
| "Het kasverslag wil niet boeken" | Per betaalmiddel en voor uitgaven/inkomsten moet een grootboekrekening ingevuld zijn; zie het hoofdstuk Kasverslag in `opleiding-zomer-kassa.md`. |
| Vraag over welke rekening/btw-code te gebruiken | Dat is boekhoudadvies: doorverwijzen naar de boekhouder van de klant. Is er een vermoeden van een programmafout, dan doorgeven aan ontwikkeling. (11-06-2026, ca. 00:56) |

---

## Bronnen

Map "Claude/Transcripties opleidingen" (SharePoint, Jamadata ChatBot):
- Kennisoverdracht Jamadata-20260611_100339-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260625_102119-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260630_102207-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260702_110347-Opname van vergadering.txt
- Kennisoverdracht Jamadata-20260707_100958-Opname van vergadering.txt
