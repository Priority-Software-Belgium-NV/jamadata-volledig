# Prijzen klaarzetten en doorsturen naar de kassa

Gebruik dit document voor: vragen waarom een gewijzigde prijs, prijswijziging op datum of promotie (nog) niet op de kassa staat, hoe prijzen uitgeschreven worden in Jamadrink (V.2.K), hoe de kassa ze ophaalt (punt N of K), welke rol de prijsdatum speelt, en hoe de kassaverkopen terugkomen naar het voorraadpakket.

## Principe

- Artikels, prijzen, blokjes (Key-Conen) en klanten worden **volledig beheerd in het voorraadpakket** (Jamadrink), niet op de kassa.
- De kassa werkt **standalone**, los van de hoofdcomputer. Gevolg: een gewijzigde prijs is **niet onmiddellijk** actief op de kassa. De prijzen moeten eerst uitgeschreven en daarna door de kassa opgehaald worden.

## Waar kan een kassaprijs gewijzigd worden?

| Plaats | Menupunt |
|---|---|
| Op de artikelfiche zelf | V.9.3.1 |
| Via kassapromoties | V.2.1 (V.2.1.1) — zie `promoties.md` |
| Via prijswijzigingen op datum | V.3.4 — zie `prijzen-prijswijzigingen-en-accijnzen.md` |

Bij een foute kassaprijs moeten dus alle drie nagekeken worden.

## Stap 1 – Prijzen uitschrijven voor de kassa (V.2.K)

In het voorraadmenu, Beheer Key-Conen kassa, punt **K** (V.2.K) schrijf je de gegevens uit voor de kassa (en PDA).

Bovenaan staat een **datum promoties (en prijswijzigingen)**. Die bepaalt welke prijzen meegestuurd worden:
- Het is de prijs **op die datum** die wordt meegegeven (meestal vandaag).
- Bij promoties en prijswijzigingen op datum wordt **automatisch ook de eerstvolgende prijs op datum** al meegestuurd.

Voorbeeld uit de handleiding: op 11/09 kost een artikel 10 euro en op 20/09 gaat een promotie of prijsstijging in. Die nieuwe prijs wordt al meegegeven en gaat op de kassa automatisch in op 20/09, zonder tussentijdse synchronisatie. Stopt de promotie op 30/09, dan moet er **op of na 20/09 nog eens gesynchroniseerd** worden; dan stopt de promotie ook automatisch op 30/09.

Tip: door de datum op bv. morgen te zetten, kan je een folder al klaarzetten zodat de kassa's de nieuwe prijzen binnenkrijgen bij de ochtendverbinding.

## Stap 2 (en 3) – Doorsturen en ophalen

| Situatie | Werkwijze |
|---|---|
| Kassa in **dezelfde netwerkomgeving** als de hoofdcomputer (zelfde locatie of via VPN) | 2 stappen: (1) gegevens klaarzetten via V.2.K; (2) op de kassa ophalen via punt **"N"** op "Menu beheer Key-Conen kassa" (dagelijkse transfer). |
| Kassa op een **andere geografische locatie**, niet via VPN verbonden | 3 stappen via de centrale servers van Jamadata (cloud): (1) hoofdcomputer schrijft de prijzen lokaal uit (V.2.K); (2) doorsturen naar de Jamadata-servers via de snelkoppeling **"doorsturen prijzen"** op het bureaublad; (3) de kassa haalt de prijzen op via punt **"K"** op "Menu beheer Key-Conen kassa". |

## Kassaverkopen terug naar het voorraadpakket

- Bij elke N of K op de kassa gebeurt een **synchronisatie in twee richtingen**: prijzen gaan naar de kassa, verkopen komen terug richting voorraadpakket.
- De verkopen kunnen in het voorraadpakket ingelezen (verwerkt) worden via **V.2.3**. Zo bouw je een historiek van de kassaverkopen op over maanden/jaren en wordt de (filiaal)stock verminderd.
- Controleer vóór het inlezen of de dagen die je wil inlezen effectief doorgestuurd zijn: kijk naar **datum/uur van het verkopenbestand van de kassa**.
- Zodra een periode ingelezen is, kan je in het voorraadpakket verkooplijsten afdrukken (ook als PDF op scherm). Verschil met de lijsten op de kassa: hier zijn ook de aankoopprijzen gekend, dus **winst en winstpercentage** zijn beschikbaar.

## Veelvoorkomende problemen

| Probleem | Controle / oplossing |
|---|---|
| Nieuwe prijs staat niet op de kassa | Is V.2.K uitgevoerd na de wijziging? Heeft de kassa daarna N (of K) gedaan? Bij een kassa op afstand: is de snelkoppeling "doorsturen prijzen" uitgevoerd? |
| Promotie of prijs op datum is niet ingegaan | Welke datum stond bovenaan bij het uitschrijven? Enkel de prijs op die datum plus de eerstvolgende wijziging worden meegestuurd. Opnieuw uitschrijven en synchroniseren. |
| Promotie loopt door na de einddatum | Na de start van de promotie is niet opnieuw gesynchroniseerd, waardoor de einddatum (= volgende wijziging) niet meegegeven is. Opnieuw V.2.K en N/K. |
| Verkopen van een dag ontbreken in de historiek/statistiek | De kassa heeft die dag niet doorgestuurd of de verkopen zijn niet ingelezen via V.2.3. Controleer datum/uur van het verkopenbestand. |
| Prijs op de kassa wijkt af van de artikelfiche | Controleer of er een kassapromotie (V.2.1) of een prijs op datum (V.3.4, groene prijs op de fiche) actief is. |

## Bronnen

- `xxxxx - Klaarzetten - doorsturen prijzen.docx` — Jamadrink/Handleidingen modules
- `0295A - Uitgebreide Kassa-promoties.docx` (deel "Werking promotiefiches en synchronisatie naar de kassa") — Jamadrink/Handleidingen modules
- `0155A - Beheer stocklocaties.docx` (inlezen verkopen V.2.3) — Jamadrink/Handleidingen modules
