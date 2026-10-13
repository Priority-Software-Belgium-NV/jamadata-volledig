/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* shn */
#define ADDLIN          NO/* indien YES dan QNUL op NO !!! */
#define ADDORSEP        NO/* samenvoegen of niet afh. 2,37 (ADDLIN dan NO */
#define AFHAALVERG      NO
#define ALARM_WINST     YES/* prijs in reversed indien NETTO-prijs < AK-prijs */
#define ANAL_ASK        NO            /* analytische bkh, op 1 kostenplaats */
#define ARTEXIST        YES
#define ARTSEARCHICOON  YES /* zoeker na elk artikel. Scherm 2,27 nakijken!*/
#define BACKORDER       YES
#define BARC_USED       NO/* gebruik van barcode-scanner */
#define BARC_KEY        11          /* key-nr bak (70) , stuk (71) = key+1  */
#define BLOK_ART        NO/* waarschuwen indien artikel nog niet afgenomen */
#define BOEKALLO        YES
#define BOEK_EXTERN     NO
      /*  #define BOEK_JOURNL      14       afwijkend journaal voor boeking */
#define BOEK_LOCATIE    NO/* kasVK op aparte GRB per locatie 701xx,702xx */
#define BON2HTML        NO/* bons mogen toch naar HTML geschreven worden */
#define BONFILE         YES 
#define BONR2BKH        NO/* bonnr's in bkh-opmerking klant zetten */
#define BONSEQNR        NO/* volgnr update bons via 8,52 */
#define BONSORT         NO/* sorteer artikels op bon cfr SORT_FLD */
#define BTWINCL         YES
#define B_LST_BON       NO
#define B_LST_ART       NO
#define CHK_STOCK       NO/* alarmeer indien aantal > stock */
#define CENT_BEDR       NO/* Centralistie artikels ook bedragen drukken */
#define COPY_FACT       NO/* parlay.c hiervoor aanpassen cfr STO */
#define CODERIGHT       NO
#define DATUMKOL        NO
#define DEF_INPUT       YES
#define DISKIMME        NO
#define DISCONTO        NO
#define DISC_NOACC      NO/* geen disconto op accijns */
#define DISC244         NO/* disconto op bon */
#define DISP_WI_FR      YES
#define DOUBLE_RAM      NO/* verdubbel aantal lijnen via wrk-manager */
#define DOUBLE_FACT     1                              /* verdubbel-factor  */
#define DUMP_CFT        YES/* dump copie van factuur in aparte file */
#define EMPTYBLAD       NO
#define EXPBTW01        NO
#define EXTEND_KORT     NO/* Abts : 2,81-82, 6,90-99, 8,53-54 en 58,102-132 */
#define FACT2CODABOX    YES /* factuur uitschrijven in UBL en versturen via CodaBox, DRK2240 moet bestaan! */
#define FACT2XML        YES /* factuur uitschrijven in UBL, DRK2240 moet bestaan! */
#define FACT2XMLSPECIAL YES /* klantspecifieke factuur uitschrijven in UBL (vb Yuki), kkk2141 moet bestaan en FACT2XML op YES! */
#define FACT_PROMO      YES /* V.3.9 : ovl296 en 58,90-94 en 6,150-184 */
#define FILETXT         NO
#define FIRMAPRT        NO
#define HISTORIEK       YES
#define INTRASTAT       NO
#define CONTRACT        YES
#define KORTBKH         NO
#define KORT_DELAYED    NO/* korting van factuur op volgende bon verrekenen */
#define KORTTOT         YES
#define CREDITBP        NO
#define LASTPRX         NO
#define LAYOUT          YES
#define LBONS_PR        NO/* prijs afdrukken op toerlijst bons (252) */
#define LBONS_WINST     NO/* winst afdrukken op lijst bons (ovl252) */
#define LEEG_APART      NO/* F10 om saldo leeggoed apart op bon te zetten */
#define LETTERSC        NO
#define LEV_OMZET       NO/* omzet op leveringsadres bijhouden */
#define LOSVERGOED      NO
#define MAIL_ALLOW      NO/* document mailen toegestaan */
#define MAILREST        NO/* mail gesplitst gedeelte naar klant (=tekort) */
#define MULTIBON        YES/* meerdere bons samen op 1 factuur */
#define MULTI_PER_KLT   NO/* afh. van 2,37 apart of samen op factuur */
#define NO_ADDBNR       NO
#define NO_ART_SORT     NO
#define NO_ART_DSP      NO/* geen artikel tonen bij search */
#define NO_ART_UPD      NO/* GEEN artikelfiche updaten (stock, omzet..) */
#define NO_BONKORT      NO/* GEEN korting rekenen op lev.bons */
#define NO_FT_SER       NO/* bons steeds klant per klant factureren */
#define NO_KASKLTADR    NO/* facturatie kassa-bons : altijd klantdata uit fas */
#define PALET_KORTING   NO
#define PALET_PRO       NO/* artikel op s(6,82) invoegen */
#define PR_CLOSED       YES/* indien YES, dan in parlay.c openen */
#define PRTBON2X        YES          /* bon aantal keren printen als factuur */
#define PRTBON_Q        2/* neem dit aantal voor PRTBON2X ipv q_fact */
#define PRTBONRET       YES/* enkel vraag F4/F5 na afdrukken bon */
#define PUNTENPROMO     NO/* puntensysteem Westmalle */
#define QNUL            NO
#define SELECT_PRTNR    NO/* indien YES dan in parlay.c openen */
#define SORT_FLD        15/* BONSORT op s(58,xx) 15=code,16=omsch,101=magaz */
#define SORT_KBON       YES/* facturatie kassa-bons : sorteer klanten alfa  */
#define SPLITS_BON      YES
#define SPLITS_KAS_PR   YES/* YES = kassaprijs nemen voor gesplitste bon */
#define SPLITS_OMZET    NO/* YES = gesplitste omzet onmiddelijk bijwerken */
#define SPLITS_TICKET   NO/* YES = ticket afdrukken van gespliste (parlay.c!) */
#define SPLITS_UPNR     NO/* update bonnr in sys.fas */
#define STATISTIEK      NO
#define STOCK244        NO/* stock aanpassen op bon-niveau */
#define STOCK_OP_LOCATIE NO/* stock op locatie vast = sys2854, of via *U(8,43) */
#define SUBSIDIE        NO/* subsidieregeling scholen (cfr DCN ook parlay !)*/
#define TOER_UPD        NO/* klantentoer per bon kunnen aanpassen */
/*  #define STRAATKEY       (uint16)12 */
#define TRANS_KOST      NO/* transportkosten rekenen */
#define UPD_PRTBON      NO
#define USE_2ADR        YES
#define USE_FTAFSPR     NO/* gebruik prijsafspraken van facturatieklant */
#define VOLD2KAS        NO
#define VOLD_BONDAT     NO/* bon-datum nemen voor betaling in kas */
#define VREEMMUN        NO
#define WINSTBLAD       NO/* indien YES dan printer openen in parlay.c */
#define WISSEL          NO

#if FLAG240E
extern int16 ovl_tabel[];
#else
static int16 ovl_tabel[] = {244,248,249,254,252,155,264,160};/* in volgorde van menu */
#endif
/* special effects */
#define D_LIN_SCR       17
#define DEF_VOLD        'N'
#define DEFLVPRT        'J'
#define MAG_GEFACT      'J'


