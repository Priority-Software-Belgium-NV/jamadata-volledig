# Kassa – FAQ en storingen (snelle diagnose)

Gebruik dit document voor: een eerste diagnose bij veelvoorkomende helpdeskvragen over de Key-Conen kassa: aanmelden, dagelijkse transfer lukt niet, artikels/barcodes/prijzen komen niet op de kassa, tickets, printer, geldlade, touchscreen, betaalterminal, klantendisplay, Freedelity, Tomra, kasverslagen en updates. Elk antwoord verwijst naar het detaildocument.

## 1. Opstarten en aanmelden

| Vraag / symptoom | Oplossing |
|---|---|
| Hoe zet ik de kassa aan? | Druk op het rode lampje onderaan het scherm; het wordt blauw en de kassa start op. |
| Hoe meld ik aan in Windows? | Met het afbeeldingswachtwoord (aanraken van de Jamadata-icoontjes; volgorde: zie interne bron "afbeeldingswachtwoord kassa.pdf"). |
| De kassa vraagt een getypt wachtwoord | Het afbeeldingswachtwoord is 3× fout ingegeven. Geef het gewone wachtwoord van de gebruiker `kassa` in (zie interne bron); daarna werkt het afbeeldingswachtwoord opnieuw. Zo niet: helpdesk. |
| "!!!Ongeldige serienummer!!!" bij het starten van het kassaprogramma | Overrulen met **F4** en dan **F10**. Komt voor na het overzetten van kassys.dat naar andere hardware en bij een mobiele kassa. |
| De kassa start op vanaf de USB-stick | USB-stick uittrekken, zo 2 keer opstarten, daarna de stick terug insteken. |
| BIOS of bootmenu nodig (PanelPos) | DEL/F2 = BIOS; F11/F12 = boot override. |
| Blue screen, Windows start niet, virus | Image restore volgens het type kassa – `kassa-image-restore.md`. Eerst de map `C:\KASSA` veiligstellen. |
| Ik kan het kassaprogramma niet stoppen | "Stoppen" werkt enkel als er geen enkel openstaand ticket meer is, bij geen enkele verkoper (A/B/C) of klant (1/2). |

## 2. Dagelijkse transfer met de hoofdcomputer (punt N)

**Symptoom**: bij N komt "File not found…" en na ongeveer een minuut "Are you connected to internet? (Y/N)" / "Bent u verbonden met internet? (Y/N)".

Controleer in deze volgorde:

1. Staat de hoofdcomputer aan (en draait de JMS)?
2. Heeft de kassa netwerk-/internetverbinding?
3. Staat het netwerk op de hoofdcomputer **en** op de kassa nog op **Privé/Particulier**? Vaak is het naar "Openbaar netwerk" gesprongen: terugzetten.
4. Een herstart van de JMS kan geen kwaad.
5. Is het IP-adres van de hoofdcomputer gewijzigd? Pas dan in `Jama.bat` op de kassa de lijn `set JMS=<IP>` aan.

Kassa op een andere locatie: gebruikt punt K (via de Jamadata-server) in plaats van N.

## 3. Artikels, prijzen, blokjes en barcodes komen niet op de kassa

| Symptoom | Oorzaak / oplossing |
|---|---|
| Nieuwe artikels/prijzen/blokjes staan niet op de kassa | Eerst op de hoofdcomputer **V.2.K** (klaarzetten, F8), daarna op de kassa **N** (of K). Beide stappen zijn nodig. Prijzen: zie ook `prijzen-doorsturen-naar-kassa.md`. |
| Barcodes ingevuld op de artikelfiche worden niet zichtbaar op de kassa | Als de N tegelijk met of kort na de K genomen wordt, kan `KASPLU.DAT` niet correct bijgewerkt zijn. Controleer op de hoofdcomputer in `J:\Jamadata\Kassa\` de datum van `KASPLU.DAT`: is die ouder dan de andere bestanden, dan is het niet geüpdatet. Oplossing: hoofdcomputer herstarten → opnieuw K → controleren dat KASPLU.DAT nu recent is → pas dan N op de kassa. |
| Onbekende barcode bij het scannen (alarm, ticket kleurt roze) | Artikel kiezen → Diversen → "Voeg EAN-nr. toe". Daarna N en in JMD V, 2, +, 2, F8 om de barcodes op de hoofdcomputer te zetten. Zie `kassa-gebruik-en-keycoons.md` §7. |
| Foutief gescande barcode wissen | CLEAR. |
| De kassa rekent een andere prijs aan dan verwacht bij een factuurklant | Klant gekozen vóór de artikels = prijstype van de klant; artikels eerst = kassaprijs. De kassa houdt geen rekening met prijsafspraken; bij "eigen prijzen op de kassa" vraagt de kassa bij Einde of de klantprijzen ingeladen moeten worden. |
| Controle op afwijkende prijzen | V.2.C Prijscontrole kassaverkopen (pdf). |
| Promoties/klantenkaartpunten | Zie `promoties.md` en `kassa-klantenkaarten-cadeaubons-tegoedbons.md`. |

## 4. Tickets, printer en geldlade

| Symptoom | Oplossing |
|---|---|
| Er komen te veel tickets uit de printer | Diversen → "Aant.ex.ticket" op 1 zetten (of `-`/0 voor geen ticket). |
| Er komt geen ticket | Zelfde knop: het aantal staat waarschijnlijk op `-`. |
| Ticket opnieuw afdrukken | Diversen → met << en >> het ticketnummer kiezen → "Druk af". Enkel tickets van vandaag. |
| Eén lijn van het ticket verwijderen | Knop Ticket → lijn selecteren → WIS (bijhorend leeggoed gaat mee weg). Volledig ticket: CLR_TICKT. Laatste artikel één minder: `-` en dan IDEM. |
| Lege regel in de tickethoofding | Kassamenu punt 3: zet enkel een `*` op die lijn. |
| Ticketprinter controleren | Kassamenu punt 3 → F8 → F8 (printerinstelling; kassys.dat positie 3712). |
| Geldlade gaat niet open | Controleer de ladecode via punt 3. Knop "Alarm" opent de lade (eventueel met 4-cijferige code). |
| Factuur afdrukken testen | F12 = testfactuur/testpagina op de kassa. Te hoog/te laag: marges in kasparm – `kassa-installatie-en-updates.md` §5. |
| Kasverslag/controleband | Diversen → "Afdrukken kastoestand" (tussendoor) of "Afdrukken controleband" (einde dag); of F9 Controle in het kassamenu. |

## 5. Scherm, touchscreen en klantendisplay

| Symptoom | Oplossing |
|---|---|
| Touchscreen reageert verkeerd | Folie verwijderen; `msdt.exe -id DeviceDiagnostic` (Advanced → Auto apply); in Apparaatbeheer het HID-touchscreen uit- en inschakelen; kassa uit, stekker uit, scherm proper en droog maken, terug opstarten. Scherm **niet aanraken tijdens het opstarten**. |
| Klantendisplay werkt niet na vervanging/overzetten van kassys.dat | Positie 4036 (soort kassa) staat fout: `setpp`/`setpp2`/`setrp`/`setap` uitvoeren. Bij PanelPC met losse display: COM1 Power Control in de BIOS op 5 V. |
| Kassa (Aerpos) blijft herstarten na aansluiten van een display | De display wordt extern gevoed; voeding moet via de COM-poort (jumper op het moederbord). |
| Kassascherm valt onderaan/rechts weg bij een tweede (groot) klantenscherm | Prestatie-instelling van Windows op "Laat Windows kiezen wat het beste is". |

Details: `kassa-klantendisplay-en-hardware.md`.

## 6. Betaalterminal

| Symptoom | Oplossing |
|---|---|
| "Onverwacht bericht" van de terminal | De terminal is nog niet volledig opgestart; wacht enkele minuten. Blijft het: terminal en/of kassa herstarten. |
| `WSA GET error = 11002` | Bestand `hosts` ontbreekt of bevat geen localhost → 127.0.0.1: kopieer `hosts.sam` naar `hosts`. |
| `WSA GET error = 11001` | 2e kassa vindt de computernaam van kassa 1 niet (kassys.dat positie 3368); ook firewall/poort 4999 op kassa 1 nakijken. |
| "Transmissiefout" bij insteken van de kaart (Worldline) | Parameter "State Information" moet op "By ECR"; of de kabel zit in de verkeerde aansluiting. |
| Ingenico-terminal blijft herstarten | Koppeling uitzetten, één manuele verrichting doen, koppeling terug aanzetten; of parameters download via het Acquirer Menu. |
| CCV serieel werkt niet | COM-poort: databits 7, pariteit even. |
| Na een test nooit vergeten | Terminal enkele seconden van de stroom halen vóór het testen van een nieuwe koppeling. |

Details: `kassa-betaalterminals.md`.

## 7. Freedelity, klantenkaarten, tegoedbons

| Symptoom | Oplossing |
|---|---|
| Freedelity komt niet naar voren / start niet op de achtergrond | Kassa herstarten. Blijft het: vertraging/opruimlijnen in `kasmenu.dat` uitschakelen. |
| Kassa blokkeert bij afrekenen na activeren van klantenkaarten | Het aantal punten voor een volle kaart is niet ingevuld op de kassa (punt 3, F3 volgend). |
| Punten geven zonder verkoop (Freedelity) | Einde → 0.01 → Geld → knop Freedelity → aantal punten ingeven. |
| Tegoedbon groter dan het te betalen bedrag | Bedrag van de bon ingeven → "Eigen tegoedbon" → nogmaals "Eigen tegoedbon" of "Geld": de kassa drukt een ticket met het restant-tegoed af. |

Details: `kassa-klantenkaarten-cadeaubons-tegoedbons.md`.

## 8. Tomra / leeggoed

| Symptoom | Oplossing |
|---|---|
| Tomra-ticket geeft een pop-up | Het ticketbestand is al gebruikt (gewist na het eerste scannen) of niet bereikbaar. |
| T-schijf maakt geen verbinding (kassa/scanner) | Scherm overnemen en de T-schijf in Verkenner aanklikken: de verbinding komt terug. |
| Jamadata blijft bij het opstarten hangen op de T-schijf | Overbodige/onbereikbare netwerkschijf verwijderen als dezelfde share via een andere letter beschikbaar is. |
| Geen leeggoed bij een artikel op een (lever)bon | Veld "aantal leeggoed" op de artikelfiche moet op 1 staan. |

Details: `kassa-tomra-en-leeggoed.md`.

## 9. Verkopen, kasverslagen en omzet

| Vraag | Antwoord |
|---|---|
| Omzet van de kassa opvragen | Hoofdmenu → 2 → 5 (verkooplijsten) → 6 (dagtotalen) → periode en kassa. Of V.2.6 Dagtotalen bekijken. |
| Verkopen inlezen in Jamadrink | Eerst N op de kassa, dan V.2.3 (stock & statistieken bijwerken: ja). |
| Waarschuwing bij V.2.3 dat het verkopenbestand niet recent is | De kassa heeft (nog) niet doorgestuurd of het bestand komt niet overeen met het sluitingsuur; je kan toch inlezen, maar doe beter eerst de N. |
| Oud kasverslag nodig dat niet meer in de kaslog zit | Oude `kaslog.dat` uit de backup (USB-stick of `Copy.alt`-snapshot) tijdelijk terugzetten – `kassa-kaslog-en-backup.md` §3. |
| Kassaverslag kan niet ingeboekt worden | Bij elk item moet het Type grootboekrekening ingevuld zijn (V.2.4). Opgelet: twee keer inboeken wordt niet tegengehouden. |
| Kaslog vol / moet ik nog wissen? | Klassiek: punt A in het kassamenu. Bij kaslog per maand niet meer; wel de kassa vóór elke maandwissel uitschakelen. |
| Kassa uit bij maandwissel vergeten (kaslog per maand) | Verkopen van de nieuwe maand komen in het bestand van de oude maand terecht. |

## 10. Update en ondersteuning

| Vraag | Antwoord |
|---|---|
| Hoe update ik de kassa? | Kassa afsluiten tot op het bureaublad, laatste `runonce.kas` in de map kassa plaatsen, kassa opnieuw starten. |
| Kassa overnemen | Klant gaat op de kassa naar `kb.jamadata.be` → "Remote support" (TeamViewer); foutmeldingen op de kassa wegklikken met OK; code doorgeven. |
| Jamadata "bevriest" even; in de SVC-log staat `ERROR #0109 … hWnd for JMH not filled in, so Txmit of file slow for PostNr=x` | Werkpost x heeft een groter bestand opgevraagd, waardoor het systeem kort trager reageerde. Eenmalig: geen actie nodig; meld de klant dat het een tijdelijke vertraging was. Bij herhaling: scherm overnemen, nagaan of het weer dezelfde werkpost is, de betrokken Jamadata-mappen opruimen volgens de gekende procedure en zo nodig de Jamadata Server herstarten; daarna samen testen. |

## Bronnen

- `Onenote/KASSA.pdf` (alle FAQ-pagina's; vollediger dan `kassa/KASSA.pdf`)
- `kassa/FAQ PanelPC kassa.docx`, `kassa/HOWTO-Kassa Paswoord .docx`, `kassa/afbeeldingswachtwoord kassa.pdf`
- `kassa/gebruikershandleiding keyConen KASSA 2.0.docx`
- `Jamadrink/gebruikershandleiding JAMADRINK 2.0.docx` (hoofdstukken V.2 en K)
- `kassa/HOWTO-Instellen BANKSYS.docx`, `kassa/HOWTO-Instellen CARDFON.docx`, `kassa/HOWTO-Instellen INGENICO.docx`
- `kassa/HOWTO-Freedelity-koppeling.docx`, `kassa/HOWTO-Instellen KLANTENKAARTEN.docx`, `kassa/HOWTO-Kassa TeGoed bons afdrukken.docx`
- `kassa/Installatie_losse klantendisplay Panelpos.docx`, `kassa/Installatie_losse klantendisplay aerpos.docx`, `kassa/Installatie grote klantendisplay.docx`
- `kassa/INSTELLEN MAANDELIJKSE KL FILES (KASLOG) OP KASSA’S.docx`
