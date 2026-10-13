// #define WINVER 0x0501  // was 500
// #define _WIN32_WINNT 0x0501  // was 500

#include "stdafx.h"


#if !defined(_WIN32_WCE)
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <share.h>
#endif

#if defined(_WIN32_WCE)

extern int _fmode;
extern int errno;

#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_RDWR         0x0002  /* open for reading and writing */
#define O_APPEND       0x0008  /* writes done at eof */
#define O_CREAT        0x0100  /* create and open file */
#define O_TRUNC        0x0200  /* open and truncate */
#define O_EXCL         0x0400  /* open only if file doesn't already exist */
#define O_TEXT         0x4000  /* file mode is text (translated) */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */

#define _S_IFMT         0170000         /* file type mask */
#define _S_IFDIR        0040000         /* directory */
#define _S_IFCHR        0020000         /* character special */
#define _S_IFIFO        0010000         /* pipe */
#define _S_IFREG        0100000         /* regular */
#define _S_IREAD        0000400         /* read permission, owner */
#define _S_IWRITE       0000200         /* write permission, owner */
#define _S_IEXEC        0000100         /* execute/search permission, owner */

#endif

//#include "kastype.def"

#pragma pack(1)

#define XP_KASSA        NO  // geen nieuwe EID-read routine omdat windows dit niet aankan
    // indien YES dan: 
    // in configuration -> link -> input de swelio32.lib VERVANGEN DOOR EIDRead.lib  (nadien terugzetten!!!)
    //    --> dit in DEBUG en RELEASE doen!



#define FOREVER         while(1)
#define YES             1
#define NO              0
#define GOOD            1
#define BAD             2
#define RDWRMODE        O_RDWR | O_BINARY
#define CREAMODE        _S_IWRITE | _S_IREAD

#define DEF_IR300PRT        0x3E8

#define BCPREFIXWERKBON	"283900198"
#define LOCKASKRTPT     "KASKRTPT.DAT"
#define SRVKASKRTPT     "\\\\keytouch-01\\hd-c\\kassa\\KASKRTPT.DAT"
#define SRVWKASKRTPT		"\\\\wintouch-01\\kassa\\KASKRTPT.DAT"
#define ZSHAREKRTPT	  	"Z:\\KASKRTPT.DAT"

#define CHAR_SEC       10/* snelheid voor display v/d reclame */

#define CBM720          0
#define TM88            1
#define HPLJ            2
#define VFD             3

#define DEMO_VERSION    NO
#define DEMO_EXPIRE     95,2,1
#define MAX_PAY_TIME	  60 // 180 Moest                                
#define PRT_FIL NO  // !!!!
#define CONTROL2PDF    YES
#define CTRLPDFSIZE    (long)(4000000) // was 200.000

// onderstaande tabel zit ook in DRK0290.cpp !

//////////////////////////////////// MOET NAAR DRK0290.cpp

// onderstaande tabel komt uit KASHEAD.H

#define STUKS           1
#define AUTO_LEEG       2
#define NEW_TICKET      0x40

#define flag            char

#define VRK_COUNT       3
#define KLT_COUNT       2
#define WRK_COUNT     100
#define WRK_BONHDR_LEN   329 // structuur WrkBonHdr moet ook die lengte hebben!

#define LIN_COUNT        500
#define MAX_KLANT      15000
#define CUMART_COUNT    7000
#define MAX_KEYS         500
#define MAXCLN           100
#define MAX_VRK_USR      500

#define LIN_MARGIN     15
#define PRX_COUNT       5
#define FLD_COUNT       8
#define MAX_LADE        8
#define LEN_SYSFILE 15000
#define VAL_COUNT      10
#define MIN_BTW_LEN    25
 
#define REG_DIGITS_AFTER 3
#define TEKST_COUNT     3
#define MAX_NIVEAU      4
#define ARTCODE_LEN     5  // winkassa op 10 zetten voor VAREY mvg
#define ARTNAAM_LEN     30
#define ARTEAN_LEN      20
                          
#define EXTRA_OPTIES_COUNT 100                                                                        
#define CUMGRP_COUNT    100
#define CUMBTW_COUNT    10
#define SUBGRP_COUNT	  30
#define FIN_COUNT       40
 
#define POS_AANTAL      0
#define POS_PRIJS       5
#define POS_NAAM       13
#define POS_TOTAAL     33
 
#define GRP_PKORT      -1				// Korting in Procent
#define GRP_FKORT      -2				// Korting in Geld (Frank, nu EURO)
/*
vrijhouden voor kortingen t/m -9
*/
 
#define GRP_SUBTOT   -100				// informatieve lijn
 
#define GRP_TOTAAL      1000		// totaal (zo men 1 bedrag voor goederen en leeggoed wenst)
#define GRP_TEGOED      1001		// men geeft geen geld terug, maar druk 'TEGOED-bon' af
#define GRP_TERUG       1002	  // het teruggegeven geld (kan wisselgeld zijn, maar kan ook geld op bancontact zijn
#define GRP_GOEDEREN    1003		// totaalbedrag verkoop goederen
#define GRP_LGMEE       1004		// totaalbedrag leeggoed mee 
#define GRP_VOORSCHOT_B 1005		// ?? geen idee, is voorschot bij bakkerij-kassa (icoon ?) bij bestelling ?
#define GRP_VOORSCHOT		1006    // komt in dranken normaal ook niet voor (denk ik)
#define GRP_GELD        1010    // Bedrag betaald in GELD
#define GRP_ECHEQUE     1011		// Bedrag betaald met Eurocheques (vroeger) of electronische maaltijdcheques (wordt geventileerd in subgroepen)
#define GRP_BANCONT     1012		// Bedrag betaald via Bankcontact (kan ook maestro zijn !)
#define GRP_MAALTIJD    1013		// Bedrag betaald in PAPIEREN maaltijdcheques
#define GRP_TGBON       1014		// Bedrag betaald met vroegen afgedrukte eigen tegoedbons (zie GRP_TEGOED)
#define GRP_LEVERBON    1015		// Bedrag betaald met bonnetjes leverancier
#define GRP_CREDIT      1016		// Bedrag betaald via Creditcard
#define GRP_TBSALDO     1017		// Wordt later betaald (na ontvangst factuur), is dus KREDIET
#define GRP_MEETOTAAL   1018		// Goederen en leeggoed (totaal mee)
#define GRP_DIVUITGAVE  1019		// Bedrag voor diverse uitgave (moet nog uitgesplits worden)
#define GRP_DIVONTVANG  1020		// Bedrag voor diverse ontvangst (moet nog uitgesplits worden)
#define GRP_ZEGELS      1021    // Zegels van de Valois e.d. ???? 
#define GRP_LGTERUG     1022		// Leeggoed teruggenomen (weet niet of dit nog gebruikt wordt, staat meestal in de 'detaillijnen'), was bedoeld voor aanname leeggoed-tickets
#define GRP_MOBIEL      1023		// betaald met Mobiel
#define GRP_VOORSCHOT_R	1024	  // voorschot retourname (boekingstechnisch voor bakkerij)
#define GRP_CASHAUT     1025    // Bedrag betaald via CashAut (cash automaat)
/*
vrijhouden voor totaal rekeningen t/m 1029
*/
#define GRP_CONVERT     1030
#define GRP_OPENLADE    1031
#define GRP_EURO        1032
#define GRP_PUNTEN      1033
#define GRP_PUNTEXTRA   1034

#define GRP_CDBON_VRK   1040		// Bedrag cadeaubon verkocht
#define GRP_CDBON_BET   1041		// Bedrag betaald met cadeaubon
#define GRP_VAR_BET1    1042		// Bedrag betaald met variabele betaalwijze 1
#define GRP_VAR_BET2    1043		// Bedrag betaald met variabele betaalwijze 2
#define GRP_VAR_BET3    1044		// Bedrag betaald met variabele betaalwijze 3
#define GRP_AFRONDING   1045		// Afrondingsverschil bij afronding tot op 5 cent
#define GRP_EMAALTIJD   1046		// Bedrag betaald met elec. maaltijdcheques
#define GRP_EECOCHEQUE  1047		// Bedrag betaald met elec. ECOcheques
#define GRP_ECADEAUBON  1048		// Bedrag betaald met elec. CADEAUbons
#define GRP_ECONSUMBON  1049		// Bedrag betaald met elec. CONSUMPTIEbons

#define GRP_FAKT        1100
#define GRP_TERPLAATSE  1200 

#define GRP_ATTENTION		9900
#define GRP_T_RB        9995
#define GRP_T_R         9996
#define GRP_T_U         9997
#define GRP_TEXT        9998
#define GRP_TIJD        9999
 
struct s_lijn{   // als we hier iets aan wijzigen, ook aanpassen in OVL290 
                 // is ook belangrijk bij adden in kaslog.dat (truuk voor textlijn)
  char text[41];							// ingevuld zo groep >= 9900, bv. GRP_TEXT of GRP_TIJD
  unsigned char bits;					// & STUKS om te weten of het stuksflag is of niet 
  char code[ARTCODE_LEN];	
  float aantal;
  short groep;
  float btw;
  float prijs;
  double totaal;
  char  EindeReclenKaslog; // vanaf hier UITKIJKEN met wegschrijven in kaslog/WRK-bons owv ovl0290 en compatibiliteit !!!!
  short fl_promoLijn;
  int PromoFormule;
  int  MaxPromoPerTicket;
  long PromoGroepsCode;
  float PromoBasisAantal;
  char  EindeWRKReclen; // tot hier wordt uitgeschreven in WRK-bons, kijk uit dat hier geen vitale velden staan!!!!
  float PromoAantalUsed;
};

// TOT HIERBOVEN IN DRK0290.CPP

struct s_verkopen {
  int used;
  char leeg_flag;
  char stuks_flag;
  char kort_flag;
  char bak_flag;
  char TERPLAATSE_flag;
	char AttentionFlag;
	char btw_holland;
	char ExtraTicket;
	bool CreditNotaFlag;
	bool JmcFactuurFlag;
	bool PrijsViaJmcFlag;
	unsigned char JmcDocType;
  int prx_ix;
  int klant_nr;
	int krtflag;
  int krtnr;
  int krtPunten;
  char krtNaam[50];
	char EidNaam[40];
	char EidStraat[40];
	char EidPostCode[10];
	char EidGemeente[30];
	char EidRRN[20];
	int BestelKrtNr;
  int fakt_type;
  float alg_korting;
  int dummy[3];
  float t_punten;
  float t_bdr2punt;
  double aantal[3];/* 0 -> totaal, 1 -> leeggoed */
  double totaal[3];
  double subaantal[3];
  double subtotaal[3];
	double BdrAfronding;
	double totvoorschot_r;
  float punten[LIN_COUNT];
  float bdr2punt[LIN_COUNT];
  struct s_lijn lijn[LIN_COUNT];
};/* verkopen[vrk][klt].lijn[lin].text .... */

struct art_line {
  char  code[ARTCODE_LEN];
  char  naam[ARTNAAM_LEN];
  int   groep;
  float btw;
  float prijs[PRX_COUNT];
  float st_prijs;
  char code_l[ARTCODE_LEN];
  char code_lst[ARTCODE_LEN];
  int st_verp;
  char promo;
  char ean[ARTEAN_LEN];
  char ean_st[ARTEAN_LEN];
  float punten;
  float punten_st;
  char ex_text[20];
  char alt_code[20]; // voor Freedelity (Prik&Tik)
  char naamnetto[ARTNAAM_LEN];
  int PromoFormule;
  char PromoBakFles;
  int  MaxPromoPerTicket;
  float PromoFormuleGetallen[4];
  char PromoGratisArtCode[ARTCODE_LEN];
  char PromoGratisTekst[ARTNAAM_LEN];
  long PromoGroepsCode;
};

struct s_klant {
  char code[10+1];
  char naam[40+1];
  char straat[30+1];
  char postnr[7+1];
  char gemeente[25+1];
  char telefoon[15+1];
  char btwnummer[12+1];
  char type[1+1];
  char PrijsViaJmd[1+1];
  char dummy[10];/* lengte fixed op 160 tekens */
};

struct s_kaskrtnm {
  char code[10+1];
  char naam[40+1];
  char straat[30+1];
  char postnr[7+1];
  char gemeente[25+1];
  char telefoon[15+1];
  char dummy[27];/* lengte fixed op 160 tekens */
};

struct s_krtinfo {
  short unsigned nr;
  char code[10];
  char naam[60];
  char telefoon[12];
};

struct _extra {
  int plu_ix;
  char stuks_fl;
  char ean[ARTEAN_LEN];
};

struct s_cln {
  long pos;
  int  unit;
  float prx;
};

struct layout {
  short key_numb;
  short x_pos;
  short y_pos;
  short x_len;
  short y_len;
};

//////////// DECLARATIES

/* ---------------- Headerfile voor : KASCONT1.CPP --------------- */

void clnrec(long recix);
void controle(int PdfAllowed);
void get_memcumul(void);
void rls_memcumul(void);
void prt_art(void);
void prt_financ(void);
void prt_groep(void);
void prt_gtot(int last_grp);
void upd_eti(void);
void upd_grp(void);
void readEID(int dum);
/* ---------------- Headerfile voor : KASCONT2.CPP --------------- */

void add_btw(void);
void calc_btw(void);
void clr_btw(void);
void print_footer(double getal);
void prt_btw(char statist);
void prt_time(void);
void prt_titel(char *s, char *s2);
void sum_btw(void);

/* ---------------- Headerfile voor : kasean.CPP --------------- */

int add_ean(char *ean);
void anew_ean(void);
int bc_get(void);
int bc_process(int exec_rout);
void debug(void);
int hex2dec(char byte);
void mk_eantab(int line);
void cl_eantab();

/* ---------------- Headerfile voor : KASEINDE.CPP --------------- */

void add_einde(int groep, double bedrag, int subgroep=0);
void cl_gr_line(void);
void close_bon(char save_fl, bool DoOpenGeldlade);
void gr_footer(char datum[9], int lincnt, bool betaald);
void gr_header(char datum[9], char first_fl);
void gr_skip(int count);
int iabs(float getal);
int lincheck(int lincnt, char datum[9]);
void mk_btw(void);
void prt_gr_faktuur(char datum[9]);
void prt_kl_faktuur(char datum[9]);
void val_lades(void);

/* ---------------- Headerfile voor : KASFAC.CPP --------------- */

void add_kasfac(char *type, char datum[], unsigned volgnr);
void op_kasfac(int line);

/* ---------------- Headerfile voor : KASFUNC1.CPP --------------- */

void joutp(int port, int data);
int jinp(int port);
int jamint(void);

void mous_en_curs();
void mous_di_curs();

int compare(char *s1, char *s2, int len);
void copynaam(char *s, char *d, int len);
void cursor(int x, int y);
void disp_init(void);
int  disp_exit(char *s);
void disp_num(int x_pos, int y_pos, double *pd, int dig, int dig_aft, int disp_punt);
void flush(void);
void get_cursor(void);
void get_memory(long needed);
void int2str(int d, char *s, int len);
void pen_check(int line_nr, char must);
int pen_depressed(char bc_check);
int pen_scan(char text_fl);
void restore_cursor(void);
double round_it(double getal, double round);
void scr_clr(void);
void ss_rest(void);
void wait_depressed(void);
void wait_released(void);
void zeroes(char *s, unsigned len);

/* ---------------- Headerfile voor : KASFUNC2.CPP --------------- */

void disp_user(int x_pos, int y_pos, int key_numb);

/* ---------------- Headerfile voor : KASFUNC3.CPP --------------- */

void cust_init(void);
void chk_copy(void);
void cust_disp(char *s);
long get_hun(void);
void get_tijd(void);
void lade_init(void);
void o_lade(int byte);
void prt_char(char val);
void prt_ean(char *s);
void prt_init(void);
void cust_prt_cod(int nr);
void cust_prt_lin(char *s);
void prt_cod(int nr);
void prt_lin(char *s);
void prt_close(void);
void prt_nl(char *s);
void prt_nlu(char *s);
void wait_hun(int hundred);
int bcopy0(char *pfrom_,char *pto_,int len_);
extern int PrtNr;

/* ---------------- Headerfile voor : KASKLT.CPP --------------- */

void cop_txt(char *s, int pos);
void get_klant(void);
void gt_txtklt(char *s, int type);
void index_klant(void);
void leg_txt(void);
void op_kasklt(int line);
void cl_kasklt();
void txt_aklt(char add_fl);
void txt_klt(char *datum);
int upd_klt(char *s);

/* ---------------- Headerfile voor : KASKRT.CPP --------------- */

void dsp_krtinfo(int type);
void op_kaskrt(int line);
void cl_kaskrt();
void prtkrtfull(int count);
void sel_kltkrt(int dum);
int updkltkrt(void);

/* ---------------- Headerfile voor : KASLARGE.CPP --------------- */

void largecom(int x, int y, int f, unsigned attr);
void largeini(void);
void largevid(int x, int y, char *s, unsigned attr);

/* ---------------- Headerfile voor : KASLOG.CPP --------------- */

void debdump(char *s);
void log_add(char incnrflag);
void log_close(void);
void log_copy(char file[]);
int log_getdag(int nr);
long log_getrec(long nr);
void log_getstatist(long *p_dagused, long *p_dagtot, long *p_recused, long *p_rectot);
int log_getticket(void);
void log_loadticket(int nr);
void log_open(int line,unsigned date_);
void logheadcheck(int nr);
void logdump(long pos, char *s, int size);
int next_ticketnr(void);
void prt_kas(int dum);
void prtlstnr(int _recix);
void wis_kas(void);

/* ---------------- Headerfile voor : kasplu.CPP --------------- */

int plu_brws(void);
int plu_req(char *ss, int len);
void plu_upd(int ix);
void rd_kasplu(int line);
void cl_kasplu();

/* ---------------- Headerfile voor : KASPROMO.CPP --------------- */

void calc_promo(int art_ptr);
void CalcArtikelPromo(int art_ptr);

/* ---------------- Headerfile voor : KASRECLA.CPP --------------- */

void stand_by(void);
void start_saver(void);
void watch_saver(void);
static void disp_reclame(void);

/* ---------------- Headerfile voor : KASSYS.CPP --------------- */

void adj_pcod(void);
void rd_kassys(int line);
void upd_sys(void);
void writmem(long lpos, void *p, unsigned len);

/* ---------------- Headerfile voor : KASTICKE.CPP --------------- */

void _clr_text(char *p);
void _clr_ticket(void);
void add_etext(char *s);
void add_text(char *s);
void add_ix_text(int index, char *s);
void adj_text(int index);
void prt_body(char controle);
int prt_cut(int line);
void prt_hoofd(char kasticket);

/* ---------------- Headerfile voor : KASUSR.CPP --------------- */

int find_niveau(char *p_niveau);
void get_work(char *p_niveau, char erase);
void key_calc(void);
void put_work(char *p_niveau);
void rd_kasusr(int line);
void cl_kasusr();

/* ---------------- Headerfile voor : KASWRK.CPP --------------- */

void mkfilnam(char *s);
void op_kaswrk(int line);
void wrk_close(int fref);
void wrk_del(int nr);
void wrk_get(int nr);
int wrk_open(int nr);
void wrk_put(int nr);
void vkpda_disp();

// voor kascomn 

double str2dbl(char *s);
double str2dbl(CString cstr);
extern int ConTempRef;