# Jamadata supportdocumentatie: index

Deze map bevat de supportdocumentatie over Jamadata (Jamadrink, kassa, PDA, boekhouding, Jamadata Server), opgebouwd uit de handleidingen, HOWTO's, OneNote-notities, opleidingsopnames en ticketbesprekingen in SharePoint (`Jamadata team / General / Jamadata ChatBot`). Ze is bedoeld om helpdesk- en supportvragen te beantwoorden en is enkel voor intern gebruik.

## Hoe deze documentatie te gebruiken

1. **Kies het onderwerp** in de tabellen hieronder en lees eerst het handleidingdocument (zonder prefix `opleiding-` of `tickets-`).
2. **Praktijkkennis aanvullen:** de `opleiding-`documenten bevatten wat een expert mondeling uitlegde (waar zit wat, diagnosevolgorde, valkuilen). Ze komen uit automatische transcripties: bij twijfel geldt de handleiding.
3. **Gelijkaardig ticket?** Kijk in `tickets-bevestigde-cases.md` (bevestigde aanpak) en `tickets-besprekingen-juni-2026.md` (besproken tickets).
4. **Antwoordt de vraag "hoe gaat dat bij klanten?"**, kijk dan in `expert-bevestigde-praktijk.md`. Veel antwoorden verschillen per klant of installatie: vraag de concrete situatie na voor je stappen geeft.

## Betrouwbaarheid, van hoog naar laag

| Bron | Waar | Opmerking |
|---|---|---|
| Door de expert bevestigd | `tickets-bevestigde-cases.md`, `expert-bevestigde-praktijk.md` | Rechtstreeks bevestigd door een ervaren Jamadata-medewerker. |
| Geschreven handleiding | alle documenten zonder prefix `opleiding-` / `tickets-` | Bij versies geldt de recentste. Oudere handleidingen (bv. boekhouding uit 2014) kunnen afwijken van het scherm. |
| Opleidingsopname | `opleiding-mei-*`, `opleiding-zomer-*` | Gesproken uitleg; menunummers en bestandsnamen kunnen door de spraakherkenning verminkt zijn. |
| Ticketbespreking | `tickets-besprekingen-juni-2026.md` | Vaak "aanpak besproken, uitkomst onbekend". |

Overal waar de bronnen onduidelijk zijn of elkaar tegenspreken, staat **"te verifiëren"** of **"onzeker"**. Geef in dat geval geen stellige procedure.

## Gevoelige gegevens

Wachtwoorden, licentiecodes, serienummers, klantnamen, persoonsnamen, e-mailadressen en IP-adressen van klanten zijn bewust weggelaten. Waar ze nodig zijn staat **"zie interne bron"**: zoek ze op in het oorspronkelijke SharePoint-document en deel ze nooit met de klant of in een ticket. Bestanden als `JMS.ini` bevatten wachtwoorden in leesbare tekst.

## Documenten per onderwerp

### Algemeen en supportcases

| Document | Inhoud |
|---|---|
| [expert-bevestigde-praktijk.md](expert-bevestigde-praktijk.md) | 45 door de expert bevestigde antwoorden: back-ups, rechten, Peppol, kassa/boekhouding, terminals, bonnen, klantenkaarten, scanners, kortingen. |
| [tickets-bevestigde-cases.md](tickets-bevestigde-cases.md) | Bevestigde cases (Peppol bulkverzending, LI4278-scanner, blauwe/groene facturatieknop, Zebra, PDA-sync, Tomra/T-schijf, teksten op leverbon, verkoop onbekende samenstelling, SMTP). |
| [tickets-besprekingen-juni-2026.md](tickets-besprekingen-juni-2026.md) | 28 tickets uit de ticketbesprekingen, per domein, met werkafspraken voor ticketbehandeling. |
| [faq-server-en-algemeen.md](faq-server-en-algemeen.md) | Wegwijzer en korte antwoorden op algemene helpdeskvragen. |

### Jamadrink (verkoop, fiches, documenten)

| Document | Inhoud |
|---|---|
| [jamadrink-navigatie-en-structuur.md](jamadrink-navigatie-en-structuur.md) | Menupaden lezen, hoofdmenu's, toetsen, verborgen supportmenu's, programmaonderdelen. |
| [jamadrink-fiches-klanten-leveranciers-artikelen.md](jamadrink-fiches-klanten-leveranciers-artikelen.md) | Klant-, leveranciers-, artikel- en groepsfiches, klantentoeren, F12 info, documentenmodule, massawijziging via Excel. |
| [jamadrink-bons-en-facturen.md](jamadrink-bons-en-facturen.md) | Leveringsbons, facturatie, vaste teksten 1–4, herafdrukken en schrappen, mobiele leeggoedterugname. |
| [jamadrink-offertes-verhuur-rappels.md](jamadrink-offertes-verhuur-rappels.md) | Offertes (V.5.6), verhuur/uitlenen (V.8.B), klantenrappels (B.5.3). |
| [jamadrink-layouts-en-afdrukken.md](jamadrink-layouts-en-afdrukken.md) | Afdrukken, pdf, PNG-factuurlay-out, strepen in pdf. |
| [jamadrink-foutcodes.md](jamadrink-foutcodes.md) | Foutcodes 1–82. |

### Prijzen, promoties, stock en statistieken

| Document | Inhoud |
|---|---|
| [prijzen-prijswijzigingen-en-accijnzen.md](prijzen-prijswijzigingen-en-accijnzen.md) | Menu V.3: directe en uitgestelde prijswijzigingen, accijnsverhogingen, inhoud/aantal per bak. |
| [prijzen-prijzenbestanden-importeren.md](prijzen-prijzenbestanden-importeren.md) | Prijzenbestanden van Prik&Tik, Districo en Belbev inlezen. |
| [prijzen-doorsturen-naar-kassa.md](prijzen-doorsturen-naar-kassa.md) | Prijzen klaarzetten en naar de kassa sturen. |
| [prijzen-prijsafspraken.md](prijzen-prijsafspraken.md) | Prijsafspraken en kortingen per klant (V.9.5), voorrangsvolgorde, uitgestelde korting. |
| [prijzen-prijsaffiches-en-prijskaartjes.md](prijzen-prijsaffiches-en-prijskaartjes.md) | Prijsaffiches, rayonkaartjes, etiketten (V.5.9). |
| [prijzen-aankoopfiches-en-deelverpakkingen.md](prijzen-aankoopfiches-en-deelverpakkingen.md) | Aankoopfiches en clips. |
| [promoties.md](promoties.md) | Kassapromoties (V.2.1), factuurpromoties (V.3.9), lijst verkochte promo-artikels. |
| [stock-en-inventaris.md](stock-en-inventaris.md) | Stocklocaties, leeggoedstock, manuele en PDA-inventaris. |
| [stock-jaareinde-31-12.md](stock-jaareinde-31-12.md) | Wat te doen op 31/12. |
| [statistieken-en-historieken.md](statistieken-en-historieken.md) | Statistieken, historieken en grafieken (V.4). |

### Peppol en mail

| Document | Inhoud |
|---|---|
| [peppol-uitgaand.md](peppol-uitgaand.md) | Peppol activeren, factuur versturen, status (8.H.1.1), niet-verzonden facturen (8.H.C), herverzenden. |
| [peppol-inkomend.md](peppol-inkomend.md) | Inkomende Peppol-facturen verwerken; verschil 0033A / 0211C / 0255C. |
| [peppol-faq-en-problemen.md](peppol-faq-en-problemen.md) | Peppol-ID's, FAQ en storingen (ongeldig btw-nummer, licentiefout, crash). |
| [mail-instellingen-en-smtp.md](mail-instellingen-en-smtp.md) | Mailinstellingen, SMTP/relay, providers, mailproblemen. |
| [mail-automatisch-mailen-en-sjablonen.md](mail-automatisch-mailen-en-sjablonen.md) | Automatisch mailen per klant, mailsjablonen. |

### Leveranciersmodules en koppelingen

| Document | Inhoud |
|---|---|
| [modules-coca-cola.md](modules-coca-cola.md) | Coca-Cola export en promo-orders. |
| [modules-haacht-abinbev-alkenmaes-moet-suntory.md](modules-haacht-abinbev-alkenmaes-moet-suntory.md) | Exportmodules Haacht, AB InBev, Alken-Maes, Moët-Hennessy, Suntory. |
| [modules-prik-en-tik-districo.md](modules-prik-en-tik-districo.md) | Bestellingen naar Prik&Tik en Districo, export kassaverkopen, Freedelity. |
| [koppelingen-bestellingen-import-export.md](koppelingen-bestellingen-import-export.md) | Klant- en leveranciersbestellingen via Excel. |
| [koppelingen-webshop-beedrop-digi-datamasters.md](koppelingen-webshop-beedrop-digi-datamasters.md) | Beedrop, WeSolveIt, XML-webshop, DIGI-prijskaartjes, DataMasters, Intrastat-installatie. |

### Boekhouding

| Document | Inhoud |
|---|---|
| [boekhouding-basis-en-dagboeken.md](boekhouding-basis-en-dagboeken.md) | Hoofdmenu B, bediening, fiches, systeemparameters en dagboeken, paswoordniveaus. |
| [boekhouding-facturen-en-financiele-verrichtingen.md](boekhouding-facturen-en-financiele-verrichtingen.md) | Facturen inboeken, financiële verrichtingen, schrappen, openingsbalans. |
| [boekhouding-openstaande-posten-en-rapporten.md](boekhouding-openstaande-posten-en-rapporten.md) | Controlelijst, journalen, btw-aangifte, balansen, rappels, vervaldagbalans. |
| [boekhouding-btw-listing-ic-intrastat.md](boekhouding-btw-listing-ic-intrastat.md) | BTW-listing, IC-opgave, Intrastat. |
| [boekhouding-coda-en-betalingen.md](boekhouding-coda-en-betalingen.md) | CODA, SEPA-betaalopdrachten, domicilieringen. |
| [boekhouding-afschrijvingen-en-eigendommen.md](boekhouding-afschrijvingen-en-eigendommen.md) | Afschrijvingen, beheer eigendommen/huren. |
| [boekhouding-kasjournaal-en-kasverslag.md](boekhouding-kasjournaal-en-kasverslag.md) | Kasjournaal en kasverslag. |
| [boekhouding-archivering-en-foutenlijst.md](boekhouding-archivering-en-foutenlijst.md) | Archivering, jaararchief, foutenlijst 1–82. |

### Kassa

| Document | Inhoud |
|---|---|
| [kassa-gebruik-en-keycoons.md](kassa-gebruik-en-keycoons.md) | Kassascherm, afrekenen, Key-conen beheren, klaarzetten en transfer. |
| [kassa-installatie-en-updates.md](kassa-installatie-en-updates.md) | Nieuwe of vervangende kassa, RUNONCE-updates, overname op afstand, mobiele kassa. |
| [kassa-betaalterminals.md](kassa-betaalterminals.md) | Banksys/Worldline, Cardfon/CCV, Ingenico, cashautomaat. |
| [kassa-klantenkaarten-cadeaubons-tegoedbons.md](kassa-klantenkaarten-cadeaubons-tegoedbons.md) | Klantenkaarten, Freedelity, cadeau- en tegoedbons. |
| [kassa-tomra-en-leeggoed.md](kassa-tomra-en-leeggoed.md) | Tomra-koppeling, T-schijf, leeggoed. |
| [kassa-kaslog-en-backup.md](kassa-kaslog-en-backup.md) | Kaslog en kaslog per maand, back-up van kassagegevens. |
| [kassa-klantendisplay-en-hardware.md](kassa-klantendisplay-en-hardware.md) | Klantendisplays en kassahardware. |
| [kassa-image-restore.md](kassa-image-restore.md) | Image restore per kassatype. |
| [kassa-configbestanden.md](kassa-configbestanden.md) | KASSYS.DAT, KASMENU.DAT, JAMA.BAT, KASKEYS, knopcodes. |
| [kassa-faq-en-storingen.md](kassa-faq-en-storingen.md) | Snelle diagnose van kassastoringen. |

### PDA, scanners en printers

| Document | Inhoud |
|---|---|
| [pda-gebruik-en-bestellingen.md](pda-gebruik-en-bestellingen.md) | Oude en nieuwe PDA, bestellingen, barcodes, stockopnames. |
| [pda-installatie-licentie-en-synchronisatie.md](pda-installatie-licentie-en-synchronisatie.md) | Installatie, licentie, synchronisatie, WMDC, storingen. |
| [scanners-programmeren-en-storingen.md](scanners-programmeren-en-storingen.md) | Programmeerbladen per scanner, herstarten, storingen. |
| [printers-zebra.md](printers-zebra.md) | Zebra-kaartjesprinter: driver, kalibratie, instellingen. |
| [printers-dymo-en-etiketten.md](printers-dymo-en-etiketten.md) | Dymo pallet-etiketten (beperkte bron). |

### Server, installatie en IT

| Document | Inhoud |
|---|---|
| [server-jms-overzicht-en-vereisten.md](server-jms-overzicht-en-vereisten.md) | Architectuur, processen, mappen, `JMS.ini`, poorten, systeemvereisten. |
| [server-jms-storingen.md](server-jms-storingen.md) | SVC-monitoring, foutmeldingen, herstarten, updates pushen. |
| [installatie-desktop-en-draaiboek.md](installatie-desktop-en-draaiboek.md) | JMD installeren, installatiedraaiboek server. |
| [installatie-migratie-naar-nieuwe-server.md](installatie-migratie-naar-nieuwe-server.md) | Migratie naar een nieuwe server of de cloud. |
| [backup-en-herstel.md](backup-en-herstel.md) | Back-upsoorten, schaduwkopie, manuele back-up, online back-up, restore. |
| [it-remote-support-vpn-shares.md](it-remote-support-vpn-shares.md) | LogMeIn, ComfortLink, VPN, Jamadata Share, T-schijf, USB-stationsletter. |
| [it-gdpr-richtlijnen.md](it-gdpr-richtlijnen.md) | GDPR: inzage, aanpassen, schrappen, export van persoonsgegevens. |

### Praktijkkennis uit opleidingen

| Document | Inhoud |
|---|---|
| [opleiding-mei-jamadrink-basis-facturatie-en-boekhoudcontrole.md](opleiding-mei-jamadrink-basis-facturatie-en-boekhoudcontrole.md) | Navigatie, fiches, facturen, boekhoudcontrolelijst. |
| [opleiding-mei-kassa.md](opleiding-mei-kassa.md) | Samenhang kassa en hoofdcomputer, verkoopbestand, F9 Controle. |
| [opleiding-mei-printers-mail-en-randapparatuur.md](opleiding-mei-printers-mail-en-randapparatuur.md) | Afdrukposten, ingebouwde mailserver en providers, scanners, PDA, DIGI. |
| [opleiding-mei-server-installatie-en-migratie.md](opleiding-mei-server-installatie-en-migratie.md) | JMS/JMR/JMT/JMD, voorbereiding en installatie server, migratie, updates. |
| [opleiding-mei-diagnose-svc-en-backup.md](opleiding-mei-diagnose-svc-en-backup.md) | Diagnosevolgorde, SVC-fouten, opkuis bij crashende database, back-upproblemen. |
| [opleiding-zomer-jamadrink-prijzen-en-facturatie.md](opleiding-zomer-jamadrink-prijzen-en-facturatie.md) | Kortingen, prijsafspraken, prijswijzigingen, bons, facturen, jaarafsluiting. |
| [opleiding-zomer-kassa.md](opleiding-zomer-kassa.md) | Bediening, communicatiefout, Z-totaal, transfer, verkoopbestand, kasverslag. |
| [opleiding-zomer-boekhouding.md](opleiding-zomer-boekhouding.md) | Opzoeken, journalen, betalingen, afpunten, aankoopfacturen. |
| [opleiding-zomer-pda.md](opleiding-zomer-pda.md) | Nieuwe Android-PDA: stock, bestelling, barcodes, gekende bugs. |
| [opleiding-zomer-documenten-layouts-en-peppol.md](opleiding-zomer-documenten-layouts-en-peppol.md) | Lay-outs aanpassen, mailtemplates, Peppol in de praktijk. |
| [opleiding-zomer-server-it-en-helpdeskwerkwijze.md](opleiding-zomer-server-it-en-helpdeskwerkwijze.md) | Server, gekende technische fouten, helpdeskwerkwijze. |

## Wat niet is opgenomen

- Lege documenten, sjablonen en documenten die enkel uit schermafdrukken bestaan (bv. `leeggoed_aanpassen.pdf`). Waar de tekst in een bron grotendeels in afbeeldingen zit, vermeldt het document dat.
- Dubbels (`.doc` naast `.docx`, kopieën, pdf-exports) en oudere versies; verschillen met oude versies staan enkel vermeld als ze relevant zijn.
- `Jamadata.pdf`: een bundeling van handleidingen die al apart bestaan.
- `Codabox Peppol.pdf`: gaat over het pakket DAVE, niet over Jamadata.
- Beheersdocumenten van het eerdere AI-project (claimregisters, manifesten, voortgang), de niet-gevalideerde opleidingsconcepten (`20_OPLEIDINGSCONCEPTEN_*`) en de ruwe Markdown-kennisbank (die is enkel als leeshulp gebruikt).
