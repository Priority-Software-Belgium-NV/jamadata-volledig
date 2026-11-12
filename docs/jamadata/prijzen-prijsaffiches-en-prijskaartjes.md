# Prijsaffiches, rayonkaartjes en etiketten afdrukken (V.5.9)

Gebruik dit document voor: vragen over het afdrukken van prijsetiketten, rayonkaartjes en prijsaffiches vanuit Jamadrink: welke formaten bestaan, welke velden op de artikelfiche de afdruk bepalen (inhoud, gewicht, aantal etiketten, tekst op etiket), hoe je artikels selecteert (promoties, datum laatste prijswijziging), welk prijstype en welke prijsdatum gebruikt worden, hoe je de afdrukpositie verschuift, en hoe je een eigen barcode aanmaakt voor een product zonder barcode.

## Formaten

De module drukt etiketten/kaartjes/affiches van artikels voor in de drankenwinkel. Beste resultaat met een laserprinter. Standaard drie formaten:

| Formaat | Gebruik |
|---|---|
| Rayonkaartjes | Prijsetiket voor de rekken (niet elk product apart etiketteren). Afdrukken op dikker papier en uitknippen voor in de plastic prijshouders; voorgeperforeerde bladen zijn verkrijgbaar bij Jamadata. V.5.9.1 = rayonkaartjes op rol. |
| Prijsaffiche halve A4 | Om op te hangen in de winkel |
| Prijsaffiche A4 | Om op te hangen in de winkel (bv. bij de bakken) |

## Velden op de artikelfiche (V.9.3.1, achterkant via F9)

| Veld | Betekenis voor de afdruk |
|---|---|
| **Inhoud** en **gewicht** | Bepalen de prijs per liter of per kg. Inhoud ingevuld → prijs per liter. Geen inhoud maar wel gewicht → prijs per kg. Geen van beide → niets afgedrukt. |
| | Inhoud/gewicht moeten overeenkomen met de **normale kassaprijs**: is de kassaprijs de prijs van 1 bak, dan de inhoud van 1 bak; is het de prijs van 1 fles, dan de inhoud van 1 fles. |
| **Aantal etiketten** | Aantal dat bij het afdrukken gebruikt kan worden (keuze F hieronder). Wordt automatisch op 0 gezet zodra de etiketten afgedrukt zijn. |
| **Tekst op etiket** | Extra tekst die mee afgedrukt wordt, bv. jaartal en château van een wijn. |

Controle van inhoud en aantal/bak voor veel artikels tegelijk: V.3.I (zie `prijzen-prijswijzigingen-en-accijnzen.md`).

## Afdrukken (V.5.9)

1. Kies het formaat (etiket, rayon, affiche).
2. **Print geselecteerde artikels volgens Nummer, Alfabetisch, Plaats magazijn of zelf Ingeven (N/A/P/I)**:
   - **I**: zelf de artikels ingeven waarvoor je een kaartje wil (invulscherm, zie verder).
   - **N, A of P**: kaartjes voor een reeks artikels die je daarna selecteert, gesorteerd op nummer, alfabetisch of plaats in het magazijn.
3. Selectie (enkel bij N, A of P):
   - **Enkel artikels in promotie op kassa (J/N)**: indien aangevinkt worden enkel artikels genomen waarvoor een kassapromotiefiche bestaat (V.2.1); als datum geldt de ingevulde "Prijsdatum".
4. **Aantal etiketten/affiches per artikel: F/S/V**
   - **F**: aantal van de artikelfiche (wordt na afdrukken op 0 gezet);
   - **S**: zoveel etiketten als er in stock zijn;
   - **V**: vast aantal, dat je in het volgende veld ingeeft (standaard 1).
5. **Prijsbepaling**
   - **Prijstype (0-5)** voor BAK (standaard 4 KASSA) en voor FLES (standaard 5 K.STUK). De juiste kassaprijstypes staan al ingevuld; enkel wijzigen als je bewust een andere prijs wil afdrukken.
   - **Prijsdatum (promotie/prijswijziging op datum)**: bij het bepalen van de verkoopprijs wordt rekening gehouden met prijswijzigingen op datum (V.3.4) en kassapromoties (V.2.1) op die datum. Staat het artikel dan in promotie en is er een promotietekst ingevuld, dan komt die tekst in de bijkomende omschrijving.
   - **Standaard af te drukken prijs/barcode (Fles/Bak)**: met **F** wordt op een rayonetiket enkel de flesprijs gedrukt (bv. losse flessen in het rek) en de prijs per liter t.o.v. de flesprijs berekend.
6. **F8 selecteer artikels**: bij keuze I geef je zelf de artikels in; bij A, N of P kan je op allerlei manieren selecteren.

### Invulscherm bij keuze I

- **Leeg**: aantal kaartjes dat op het blad overgeslagen wordt vóór het drukken begint (om een deels gebruikt etikettenblad verder op te gebruiken).
- **Aantal**: aantal kaartjes voor dit artikel.
- **F8 Print**: drukt de kaartjes voor de ingegeven artikels.
- **F9 laad promoties**: laadt alle artikels met een geldige KASSA-promotie in het scherm (handig bij een nieuwe promofolder). Met **F5 (wis)** schrap je de lijnen waarvoor geen kaartje nodig is.
- **F10 laad laatste ingave**: laadt de artikels die je de vorige keer hebt ingegeven.
- **Icoon A+**: een selectie artikels laden, bv. alle producten die de laatste 2 weken van prijs veranderd zijn (selectie "Artikels met selectie" → "Datum laatste prijswijziging").

### Kaartjes voor artikels met een nieuwe prijs

Zie het stappenplan in `prijzen-prijswijzigingen-en-accijnzen.md` (V.5.9.1, prijsdatum invullen, A+, datum laatste prijswijziging, F8).

## Afdruk verschuiven op het papier (V.5.9.+)

Staat de afdruk niet mooi in het midden, wijzig dan de horizontale en verticale instellingen. Voorbeeldwaarden uit de handleiding:
- artikel-etiketten: horizontaal 110, verticaal 100
- rayon-etiketten: horizontaal 110, verticaal 100

## Eigen barcode aanmaken voor een product zonder barcode (V.9.3.1)

EAN-barcodes moeten aan regels voldoen; tik dus niet zomaar een nummer in. Methode:

1. `27` = prefix voor een eigen barcode
2. het artikelnummer (enkel cijfers)
3. `0` of `1` om bak of fles aan te duiden; wordt het artikel enkel per stuk verkocht, altijd `0`
4. aanvullen met nullen tot op de voorlaatste positie (de **laatste positie NIET invullen**)
5. druk **F10**: het laatste cijfer (controlecijfer) wordt berekend.

Voorbeeld: voor artikel 21024 tik je `272102400000` gevolgd door een lege laatste positie (in de handleiding genoteerd als `2721024000000_`); na F10 wordt het `2721024000002`.

## Veelvoorkomende problemen

| Probleem | Oorzaak / oplossing |
|---|---|
| Geen prijs per liter/kg op het kaartje | Inhoud én gewicht zijn leeg op de artikelfiche. |
| Foute prijs per liter | Inhoud komt niet overeen met de eenheid van de kassaprijs (bak vs. fles), of aantal/bak is fout. Controleer via V.3.I. |
| Kaartje toont nog de oude prijs / niet de promoprijs | Prijsdatum niet (juist) ingevuld; de prijs wordt bepaald op die datum. |
| Afdruk staat verschoven | Horizontale/verticale instelling aanpassen via V.5.9.+. |
| Er komen geen kaartjes bij keuze F | "Aantal etiketten" op de artikelfiche staat op 0 (wordt na elke afdruk terug op 0 gezet). |
| Eigen barcode wordt geweigerd of scant niet | Laatste positie was ingevuld of F10 niet gebruikt om het controlecijfer te berekenen. |

## Bronnen

- `0261A - Prijsaffiches.docx` — Jamadrink/Handleidingen modules
- `0213B - Inbrengen uitgestelde prijswijzigingen op datum.docx` en `0213C - Inbrengen accijnsverhogingen.docx` (kaartjes met prijsdatum) — Jamadrink/Handleidingen modules
