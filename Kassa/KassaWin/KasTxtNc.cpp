// KasTxtNc.cpp: implementation of the CKasTxtN class.
//
//////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4996)
//#define WINVER 0x0501  // was 500
//#define _WIN32_WINNT 0x0501  // was 500

#include "p:\jamacon\library\JamaConL.h"
#include "kashead.h"
#include "KasTxtNc.h"

//#include "stdafx.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKasTxtN::CKasTxtN()
{

}

CKasTxtN::~CKasTxtN()
{

}

char txttxt[200][150] = {
  "",
  "Eerst selecteren (door aan te punten) a.u.b. ... ",
  "Bedrag :",
  "Stuks :",
  "Korting",
  "% Korting",
  "--> Subtotaal",
  "St",
  "   Controle-band",
  "Verkopen per artikel",
  " Verkopen per groep",/* 10 */
  "Verkopen per BTW-pct",
  "Aant.   E.P. Omschrijving         Totaal",
  "Groep       Aantal       Totaal   Pctage",
  "TOTAAL",
  "We :",
  " BTW-%        Basis       BTW     Totaal",
  "Code  Omschrijving         Aantal Totaal",
  " L:A ",
  " L:R ",
  " P:x ",/* 20 */
  "Leeggoed",
  "Financieel overzicht",
  " Kasticket ",
  "Aant.stuks",
  "T.Goederen",
  "T.Leeggoed",
  "Te Betalen",
  "Geld Terug",
  "Klantenfiche ",
  "Kodenummer  :",/* 30 */
  "Naam ...... :",
  "Straat + nr :",
  "Postnummer  :",
  "Gemeente .. :",
  "Telefoonnr. :",
  "BTW-nummer  :",
  "Horeca-type :",
  "Vrij 1 ......",
  "Vrij 2 ......",
  "ZOEK - veld :",/* 40 */
  "FACTUUR    Nr.:",
  "Betr. verkoop via ticket      -         ",
  "Klantnr.:               Datum :",
  "Tel.:                BTW BE-",
  "Facturatie op :",
  "Reden :",
  "Vrij ....",
  "Opnieuw afdrukken van een klant-ticket",
  "Laatst gebruikt ticket-nummer : xxxxx",
  "Selecteer de gewenste groepen",/* 50 */
  "(Geselecteerde groepen worden verlicht)",
  "Aantal klt",
  "in : %3s",
  "Ontvangen in %3s",
  "Verk/klt",
  "FACTUUR",
  "FACTUUR (pag  )",
  "Druk ESC om keyboard-input te stoppen en verder met pen te werken",
  "GELDLADE",
  "   Part. Verkoop   ",/* 60 */
  "Verk. via Bon/Fact.",
  "Scan KASSIER(ster)-ID met BARCODE-lezer ...",
  "Geld teruggeven",
  "Geheugen vol !",
  " t/m ",
  "xxx Saldo :         ",
  "Bedankt en tot ziens",
  "TOT.EURO",
  "KeyConen-WinTouch !!",
  "Punten op kaart", /* 70 */
  "Bijwerking kaart onmogelijk ...",
  "Bewaar dit ticket tot volgend bezoek,",
  "we zetten de punten dan op uw kaart !",
  "Toe te voegen",
  "Vorig saldo",
  "Deze aankoop",
  "Puntentotaal",
  "WAARDE",
  "Goederen worden meegenomen",
  "Maaltijd ter plaatse", /* 80 */
	"Ticket wordt NIET afgedrukt",
	"Ticket wordt WEL afgedrukt",
	"TOT.BESTELD",
	"GEEN voorschot",
	"VOORSCHOT",
  "Bedrag op klantenkaart",
	"Z-Totaal",
	"Eerste ticket :",
	"Laatste ticket:",
	"Afdrukken Z-Totaal", // 90
	"Is de afdruk in orde ?\r\n\r\nWanneer u ja antwoordt\r\ndan is opnieuw afdrukken onmogelijk!",
	"Gooi het afgedrukte ticket NU weg!!\r\nDeze periode wordt opgenomen in het volgend ticket!",
	"Om de rekening helemaal te betalen\r\nzijn %d van dezelfde maaltijdcheques nodig.\r\n\r\nTIP: Druk dan %d IDEM.\r\n",
  "Voldaan", //tekst voor op factuur
	"Wenst u de controleband voor dit Z-totaal\r\naf te drukken ?",
	"******** eID-Kaart van de koper ********",
	"* Naam :                               *",
	"* Adres:                               *",
	"*                                      *", 
	"* RR-Nr:                               *", // 100
	"****************************************",
  "Creditnota Nr.:",
  "CREDITNOTA",
  "CREDITNOTA (pag  )",
  "Gefactureerd op :", // 105
  "Leveringsbon op :",
  "Lees\nEid-kaart",
  "TOTAAL CASH"
};

char Ftxttxt[200][150] = {
  "",
  "Eerst selecteren (door aan te punten) a.u.b. ... ",
  "Montant :",
  "Pi�ces:",
  "R�duction",
  "% r�duction",
  "--> Sous-total",
  "Pc",
  "   Controle-band",
  "Verkopen per artikel",
  " Verkopen per groep",/* 10 */
  "Verkopen per BTW-pct",
  "Quant   Prix Description           Total",
  "Groep       Aantal       Totaal   Pctage",
  "TOTAL",
  "We :",
  " BTW-%        Basis       BTW     Totaal",
  "Code  Omschrijving         Aantal Totaal",
  " L:A ",
  " L:R ",
  " P:x ",/* 20 */
  "Vidange",
  "Financieel overzicht",
  " Kasticket ",
  "Aant.stuks",
  "T.Goederen",
  "T.Leeggoed",
  "Te Betalen",
  "Geld Terug",
  "Klantenfiche ",
  "Kodenummer  :",/* 30 */
  "Naam ...... :",
  "Straat + nr :",
  "Postnummer  :",
  "Gemeente .. :",
  "Telefoonnr. :",
  "BTW-nummer  :",
  "Horeca-type :",
  "Vrij 1 ......",
  "Vrij 2 ......",
  "ZOEK - veld :",/* 40 */
  "FACTUUR    Nr.:",
  "Betr. verkoop via ticket      -         ",
  "Klantnr.:               Datum :",
  "Tel.:                BTW BE-",
  "Facturatie op :",
  "Reden :",
  "Vrij ....",
  "Opnieuw afdrukken van een klant-ticket",
  "Laatst gebruikt ticket-nummer : xxxxx",
  "Selecteer de gewenste groepen",/* 50 */
  "(Geselecteerde groepen worden verlicht)",
  "Aantal klt",
  "in : %3s",
  "Ontvangen in %3s",
  "Verk/klt",
  "FACTUUR",
  "FACTUUR (pag  )",
  "Druk ESC om keyboard-input te stoppen en verder met pen te werken",
  "GELDLADE",
  "   Part. Verkoop   ",/* 60 */
  "Verk. via Bon/Fact.",
  "Scan KASSIER(ster)-ID met BARCODE-lezer ...",
  "Geld teruggeven",
  "Geheugen vol !",
  " t/m ",
  "xxx Saldo :         ",
  "Merci et � bient�t!",
  "TOT.EURO",
  "KeyConen-WinTouch !!",
  "Punten op kaart", /* 70 */
  "Bijwerking kaart onmogelijk ...",
  "Bewaar dit ticket tot volgend bezoek,",
  "we zetten de punten dan op uw kaart !",
  "Toe te voegen",
  "Vorig saldo",
  "Deze aankoop",
  "Puntentotaal",
  "WAARDE",
  "Goederen worden meegenomen",
  "Maaltijd ter plaatse", /* 80 */
	"Ticket wordt NIET afgedrukt",
	"Ticket wordt WEL afgedrukt",
	"TOT.BESTELD",
	"GEEN voorschot",
	"VOORSCHOT",
  "Bedrag op klantenkaart",
	"Z-Totaal",
	"Eerste ticket :",
	"Laatste ticket:",
	"Afdrukken Z-Totaal", // 90
	"Is de afdruk in orde ?\r\n\r\nWanneer u ja antwoordt\r\ndan is opnieuw afdrukken onmogelijk!",
	"Gooi het afgedrukte ticket NU weg!!\r\nDeze periode wordt opgenomen in het volgend ticket!",
	"Om de rekening helemaal te betalen\r\nzijn %d van dezelfde maaltijdcheques nodig.\r\n\r\nTIP: Druk dan %d IDEM.\r\n",
  "Voldaan", //tekst voor op factuur
	"Wenst u de controleband voor dit Z-totaal\r\naf te drukken ?",
	"******** eID-Kaart van de koper ********",
	"* Naam :                               *",
	"* Adres:                               *",
	"*                                      *", 
	"* RR-Nr:                               *", // 100
	"****************************************",
  "Creditnota Nr.:",
  "CREDITNOTA",
  "CREDITNOTA (pag  )",
  "Factur� � :", // 105
  "Bon de livraison � :",
  "Lees\nEid-kaart",
  "TOTAL CASH"
};


char *txterr[] = {
  "Hier ontbreekt een noodzakelijk gegeven !",
  "BTW-nummer is niet in orde !",
  "Fiche met dit kodenummer bestaat reeds !"
};

char txtvrk[10] = "v: / ";

char *txtmenu[20] =
{
  "Menu : Beheer Key-Conen kassa",
  "F1 Stop",
  "F8 Kassa",
  " U kiest ? ",
  "F9 Controle",
  "Gebruikte dagen   : %5ld van de %6ld",
  "Gebruikte records :%6ld van de %6ld",
  "Aantal gebruikte records per dag :%6ld records/dag",
  "Normaal is er dus ruimte voor    :%6.1f dagen",
  "Controleer of er nog voldoende ruimte is om veilig te kunnen werken.",
  "Zo er onvoldoende records vrij zijn, kan U de KASLOG.DAT-file wissen.",
  "--> Zorg ervoor dat U dan alle noodzakelijke overzichten afgedrukt heeft !",
  "F4 Ja",
  "F5 Nee",
  "HET KASLOG.DAT BESTAND IS VOL !!!! DE REGISTRATIE VAN UW VERKOPEN WORDT",
  "DUS NIET MEER GEGARANDEERD. MAAK ZO SNEL MOGELIJK UW KASLOG.DAT LEEG.",
  "--> ZORG ERVOOR DAT U DAN ALLE NOODZAKELIJKE OVERZICHTEN AFGEDRUKT HEEFT !",
};
 
char *txtjn[3] = {"Nee","Ja"};
 
char *txtper[11] = {
  "Allemaal",
  "Enkel geselecteerde",
  "Eerste t/m laatste",
  "Laatste gebr. dag",
};

char *txtcont[11] = {
  "Nee",
  "Ja",
  "Retouren",
};

char *txtcumper[11] = {
  "Globaal",
  "Dag",
  "Week",
  "Maand"
};

char *txtgroep[11] = {
  "Nee",
  "Enkel cijfers",
  "Met naam",
  "Met naam & bl.lijn",
  "Met BTW-gegevens"
};
 
char *txtart[11] = {
  "Nee",
  "Volgens PLU-nr.",
  "Alfabetisch",
  "Per groep, PLU-nr.",
  "Per groep, alfabet."
};

char *txtsel[11] = {
  "Allemaal",
  "Geselect. groepen",
};

char *txtvkp[11] = {
  "Allemaal",
  "Enkel partik. verk.",
  "Enkel bons of fact.",
  "Apart afdrukken",
  "Apart & totaal afdr.",
};

char *txtverk[11] = {
  "Allemaal",
  "Verkoper A",
  "Verkoper B",
  "Verkoper C",
};
 
char *txtfin[FIN_COUNT] = {
  "Goederen verkocht",/* 0 */
  "  Leeggoed mee",		// 1
  "  Leeggoed terug", // 2
  "Leeggoed totaal",	// 3
  "VERKOCHT",					// 4
  "  Geld ontvangen",	// 5
  "  Geld teruggegeven",// 6
  "Geld totaal",			// 7
  "E-Cheques",				// 8
  "Bancontact",				// 9
  "Visa/MC/Mstro/VPay",/* 10 */
  "Maaltijdcheque",		// 11
  "Leverancierbons",	// 12
  "  Eigen TG-bons aangen.",// 13
  "  Eigen TG-bons gemaakt",// 14
  "Saldo eigen TG-bons",// 15
  "ONTVANGEN",// 16
  "Gemiddelde waarde",// 17
  "Totaal omgerekend in",// 18
  "Krediet",// 19
  "Div.Uitgaven",/* 20 */
  "Div.Ontvangst",// 21
  "Zegels",					// 22
  "Mobiel",					// 23
	"  Voorschot ontvangen",// 24
	"  Voorschot afgerekend",// 25
	"Saldo voorschotten",// 26
	"GELDBEWEGING",		// 27
  "Cadeaubon uitgegeven",// 28
  "Cadeaubon ontvangen",	// 29
  "Var.betaalwijze 1",	// 30
  "Var.betaalwijze 2",	// 31
  "Var.betaalwijze 3",	// 32
  "Afronding ticket",	// 33
  "Maaltijdcheques",	// 34 via kaart 
  "Ecocheques",	// 35 via kaart
  "Cadeaucheques",	// 36 via kaart
  "Consumptiebons",	// 37 via kaart
  "CashAut", 	// 38
  "" 	// 39
};
 
char *txtbet[35] =
{
  "",
  "TE BETALEN",
  "Contant",
  "Maaltijdcheq.",
  "Bon",
  "Eigen TG-bon",
  "Bancontact",
  "E-Cheques",
  "Visa/MC/Mstr",
  "GELD TERUG",
  "TEGOED SALDO",/* 10 */
  "GOEDEREN",
  "LGGD MEE",
  "T.B.SALDO",
  "TOTAAL",
  "Div.Uitgave",
  "Div.Ontvangst",
  "Zegels",
  "LGGD TERUG",
  "Mobiel",
  "VOORSCHOT",/* 20 */
  "Voorschot betaald",
  "Cadeaubon", // mee
  "Cadeaubon",  // betaling
  "Var.betaalwijze 1",
  "Var.betaalwijze 2",
  "Var.betaalwijze 3",
  "Ecocheques",
  "Cadeaucheque",
  "Consumptiebon",
  "Omzetten in %%%", /* 30 */
  "LGGD SALDO", 
	"REEDS BETAALD",
  "Afronding ticket",
  ""
};

char *Ftxtbet[35] =
{
  "",
  "A PAYER",
  "Cash",
  "Ch�que-repas",
  "Bon",
  "Propre bon",
  "Bancontact",
  "E-Ch�ques",
  "Visa/MC/Mstr",
  "CASH RETOUR",
  "SOLDE CREDIT",/* 10 */
  "MARCHANDISES",
  "VIDANGE +",
  "SOLDE A PAYER",
  "TOTAL",
  "D�penses Divers",
  "Re�us divers",
  "Zegels",
  "VIDANGE -",
  "Mobile",
  "AVANCE",/* 20 */
  "Avance pay�e",
  "Ch�que cadeau", // mee
  "Ch�que cadeau",  // betaling
  "Var.betaalwijze 1",
  "Var.betaalwijze 2",
  "Var.betaalwijze 3",
  "Ecocheques",
  "Cadeaucheque",
  "Consumptiebon",
  "Omzetten in %%%", /* 30 */
  "SOLDE VIDANGE", 
	"D�J� PAY�",
  "Arrond.ticket",
  ""
};

char *txtdag[7] = {"Zo","Ma","Di","Wo","Do","Vr","Za"};
char *Ftxtdag[7] = {"Di","Lu","Ma","Me","Je","Ve","Sa"};
 
char *txtmnd[12] = {"Jan","Feb","Mrt","Apr","Mei","Jun","Jul","Aug","Sep",
                   "Okt","Nov","Dec"};
char *Ftxtmnd[12] = {"Jan","Fev","Mar","Avr","Mai","Jun","Jul","Aot","Sep",
                   "Oct","Nov","Dec"};
