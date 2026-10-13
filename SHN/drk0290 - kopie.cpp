/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* DRK0290GetD() {return &zzvw;}
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" void ExecJmsCommand(char* buf, int buflen, char* pCommand);
extern "C" int CheckForFreeSpace(int StuNr, long MinFree);
extern "C" char *VarTextFmt(int len_,int update_);

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
 
static int16 ovlcall();
__declspec(dllimport) unsigned char PrintPaperNr;

extern "C" char DRK0290dat[] = "drk0290  00:22 21/10/10 (c) Jamadata"; // Beheer KeyConen kassa (V.2)

// STOCK : bij het inlezen van de verkopen (3) wordt ALLE stock bijgewerkt BEHALVE de DIRECTE leveringsbons (944)
// HISTORIEKEN : bij het inlezen van de verkopen (3) worden ENKEL de PARTICULIERE historieken bijgewerkt (de rest in facturatie op klantniveau)


     //  FLAGEET  : deault GRB-extentie op 1 vanuit kassa


#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DF_GRB          15
#define DIM_TB          200
#define MINFREE         200
#define MAXFLD          100
#define DIMBTW          8
#define DIM_FINNRS      17
#define DIM_BEWEGING    200
#define DIM_FINANCIEEL   50
    
extern int16 retcall,parmcall[8];
extern uint16 onext;
extern char info[];
extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d(),valu_cnv();
static char *p_data;
static long *pl_80_1;
static int16 stu=6,linfree;
static int16 lvcd,klcd;
static float btw_pct[DIMBTW],def_btw;
  
static char fm_os80[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os22[]  = {7,0x88,22,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us6[]   = {7,0xC8,6,0,0,0,0};
static char fm_us5[]   = {7,0xC8,5,0,0,0,0};
static char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
static char fm_u6_09[] = {11,0xC8,6,0,1,0,'0','9',' ',' ',0};
static char fm_u_09[]  = {11,0xC8,1,0,1,0,'0','9',' ',' ',0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_uu3[]   = {6,0xD1,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD1,2,0,0x60,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_uf3_1[] = {6,0xD4,3,1,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_uf21_[] = {6,0xD4,2,1,0x20,0};
static char fm_of2_1[] = {6,0x94,2,1,0x70,0};
static char fm_of21_[] = {6,0x94,2,1,0x20,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_od21_[] = {6,0x95,2,1,0x20,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_od4_2[] = {6,0xD5,4,2,0x70,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_obd[]   = {6,0x95,6,2,0x70,0};                             /* od6_2 */
static char fm_ubd[]   = {6,0xD5,6,2,0x70,0};                             /* ud6_2 */
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,1,0,'A','A','N','N',0};
static char fm_uAVW[]  = {11,0xC8,1,0,1,0,'A','A','V','W',0};
static char fm_u_ALN[]= {13,0xC8,1,0,0x09,0,'A','A','L','L','N','N',0};
static char fm_uLKG[]  = {11,0xC8,1,0,1,0,'K','L','G','G',0};
static char fm_usP_G[]= {13,0xC8,1,0,0x09,0,'%','%','P','P','G','G',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ugrb[]  = {2,0xE8};
static char fm_uur[]   = {6,0xD1,2,0,0x40,0};
 
static int16 dag_nr[7] = {2,3,4,5,6,0,1};

static int16 prt2pdf;
static char seqo_str[500],sys3896[6],upd_veld[20],kas_munt[4],buf1000[1000],fmt[40],NaamVarBetWijze[3][20];
static char periodprt[3],filnam[40],oldnm[50],prx2kas,upd_stock,add_ftvk,def_munt[4];
static char btwhfd[6][7],dsp_kar[5],vptekst[100],PtypePerKassa[20][6];
static long seqo_pos,value,ok_pos,btw_nr,krtok_pos,dsp_count,TbDiversArtikel[10],ArtOnbekend;
static int16 stu6_len,seqo_len,seqo_mode,pos,first_prx,last_prx,len6_155,ft_off,z299,kdsp,j_tab[101],HisCheckKey;
static uint16 dat_beg,dat_end,dt_dag1,inq_kassa,prx_loff,max_kassa;
static uint16 sys3772; // B0 : GEEN kltkaart updaten, wel groepsverkopen en HIS (online kassa)
                       // B3 : lijst ft_tickets, b4 : sta/his bijhouden(particulier), B5 dummy, B6 ook facturen his/sta bijhouden indien B4
static uint16 InqLev,inq_groep,inq_disp,fkey,klt_div1,def_qfak,kaartnr,dt_last_krt_ak,sluitingsuur[10],inq_fil;
static flag sys3894,sys3618,sys3978,sys4400,sys4408,sys1790;
static flag chk_btoeg=NO,arcd=YES,use_kaart,wis_eerst,chk_dtkvk=YES;
static flag sear_stt,sys3876, sgrp_used,slev_used,p_max_grp,sys2727;
static float sys3614,pct1,pct2,winstpct,tot_qlv,*pf_6_28;
static double bd_tab[10],bd_tot[10],dagomzet,bd_Fondsoverdracht;
static double AW,VW,winst,tot_aw,tot_vw,qlv, TotaalBedragTickets=0;
static double EUR_munten[15] = {500,200,100,50,20,10,5,2,1,.5,.2,.1,.05,.02,.01};
static uint16 *pu_6_1, *pu_91_2, *pu_91_3,sys1804,InqArt;
static uint16 dt_kvk[20],loc_klt[20],loc_nr[20],dt_last,TotaalAantalTickets=0; 
static char nm_kassa[20][6],nm_loc[10][6], nm_fil[6],firma[256];
static int16 def_taal,VKjournl;
static int16 tb_ktypes[6],max_kprx;
static CStringList BonTickets,FactuurTickets,InkomstTickets,UitgaveTickets;
static long KV_GrbFinDet[20],KV_GrbFondsoverdracht,KV_GrbAfrondingsverschillen;
static char KV_ExtraScherm,KV_ToonBoekscherm,SoortDocument,KV_BoekVoldaneFactuurOpKlant,KV_AfwijkendeGrbPrefix[6];
static short int KV_KasJournaal[10];
static struct {
	double bedrag;
	char type; // l,k,g
	char naam[50];
	char opmerking[50];
	uint16 recnr;
	uint16 docnr;
	uint16 hashval;
} KVBoekTabel[DIM_BEWEGING+DIM_FINANCIEEL];

static uint16 df_recnr[DF_GRB],b3604,b3606;
static char df_grb[DF_GRB][4];
static long grb_notf,levcent,kltcent;
static char b3598[6];
 
//static struct _header {
//  char versie[32];
//  long lade_pos;
//  int16  lade_aantal;
//  int16  lade_len;
//  long dag_pos;
//  int16  dag_len;
//  int16  dag_aantal;
//  int16  dag_used;
//  long rec_pos;
//  long rec_len;
//  long rec_aantal;
//  long rec_used;
//  int16 ticketnr;
//} header;
//struct _dag {
//  uint16 datum;
//  long first_rec;
//};
static struct _fas_s_lijn{
  char bits;
  char code[5];
  float aantal;
  int16 groep;
  float btw;
  float prijs;
  double totaal;
} fas_s_lijn;
  
static struct{
  float omzet;
  float winst;
} dag_totl[31];
 
static struct{
  uint16 rec;
  char select;
} tbgr[100];
static struct {
  uint16 rec;
  float aantal;
  double AW;
  double VW;/* excl. btw */
} tb[DIM_TB+1];


/* --------------------------- Declaratie functies ---------------------- */
static void Aantal2Stuks(float aantal_,float qst_,float *bakken_,float *stuks_);
static char *Asc2Jasc(char *ps_,int16 len_);
static int copy0(char *ps,char *pd,int max);
static void BoekKasverslag(void);
static long GetRecNr(int16 stu_);
static double Round(double getal, double round);
static void SetRecNr(int16 stu_, long val_);
static void _his_upd(uint16 rec_, uint16 knr_, float *qlv_, float *bd_, uint16 dt_);
static void _kaart_his_upd(uint16 rec_, uint16 knr_, float *qlv_, float *bd_, uint16 dt_);
static void _sta_upd(uint16 rec_, uint16 knr_, float *qlv_, float *bd_, uint16 kol_);
static void add(void);
static int add_barcode(void);
static int add_klt(long pos_, int16 keep_klt_);
static int AddNewKlantFromKasticket(void);
static int ask_in_dt(char *ptxt, flag only1kas, flag ask_stock);
static int bit(char byte_, int16 bit_);
static void CheckForDeletedArt(void);
static int CheckKaslogDate(void);
static int chk_dates(void);
static int chk_fact(long r_beg, long r_end);
static int chk_kkaart(long r_beg, long r_end);
static int cmp_str(char *p1, char *p2, int16 len);
static void control(void);
static void CorrectHisFromVkp(void);
static void DisplayExtraFuncties(void);
static int DisplayWarning(char *ptxt, int icoon);
static void dsp_dagt(void);
static int ele_len(int16 nr_);
static void Execute1KassaDag(uint16 kassa_nr,uint16 dt, long r_beg, long r_end);
static void execfil(int16 kasnr);
static void execklt(int16 kasnr);
static int fichupd(int16 mode);
static void fileopen(int16 nr_);
static int fmt_get(int16 stu_, int16 elet_);
static long String2BtwNr(char *ps, int16 len_);
static uint16 getgrb(long lgrb);
static float get_num(int16 nr);
static uint16 hash(char *ps, int hash_len);
static void initload(void);
static int inp_1dag(void);
static int inp_klant(void);
static int is_nul(double bd_);
static void KasVerslag(void);
static void KasverslagParameters(void);
static void LijstVerkochtePromos(void);
static long makegrb(uint16 arec_,float btw_);
static void MakeKaslogName(int16 kasnr_,uint16 dt_);
static void MakeStksTxt(float aantal_,float qverp_,float *qbak_,char *st_txt_);
static void MoveForNewKassa(void);
static void mk_name(uint16 adr_pref, char *ps);
static int next_z(int16 z, int16 beg_, int16 qkol_, int16 qperlin_, int16 qlin_);
static void nextline(void);
static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_);
static void param(int mode);
static void PrijsControleKassaverkopen(void);
static int read_rec(int16 mode_);
static char *rec_ele(int16 nr_);
static int scr_ok(char *ptxt);
static int search(int16 stu_,int16 mod_);
static void streepje(int16 fldnr);
static void stu_add(int16 stu_, int16 elet_, float *pf1);
static void up_a_stock(uint16 arec_, uint16 knr_, uint16 dt_, float qlv_, float bedrag_);
static void update(void);
static void wis_fld(uint16 dt_, uint16 nr_, uint16 corr_stock_,uint16 disp_);
static int wissen(void);
/* ---------------------------------------------------------------------- */

////////// ROUTINES OM KASLOG TE LEZEN, AANPASSEN INDIE KASSA WIJZIGT ///////////////////////////////////

// onderstaande tabel komt uit KASHEAD.H

#define STUKS           1
#define AUTO_LEEG       2
#define NEW_TICKET      0x40



#define VRK_COUNT       3
#define KLT_COUNT       2
#define WRK_COUNT     100

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
#define SUBGRP_COUNT         30
#define FIN_COUNT       30

#define POS_AANTAL      0
#define POS_PRIJS       5
#define POS_NAAM       13
#define POS_TOTAAL     33

#define GRP_PKORT      -1                      // Korting in Procent
#define GRP_FKORT      -2                      // Korting in Geld (Frank, nu EURO)
/*
vrijhouden voor kortingen t/m -9
*/

#define GRP_SUBTOT   -100                      // informatieve lijn

#define GRP_TOTAAL      1000            // totaal MEE (zo men 1 bedrag voor goederen en leeggoed wenst)
#define GRP_TEGOED      1001            // men geeft geen geld terug, maar druk 'TEGOED-bon' af
#define GRP_TERUG       1002        // het teruggegeven geld (kan wisselgeld zijn, maar kan ook geld op bancontact zijn
#define GRP_GOEDEREN    1003            // totaalbedrag verkoop goederen
#define GRP_LGMEE       1004            // totaalbedrag leeggoed mee 
#define GRP_VOORSCHOT_B 1005            // ?? geen idee, is voorschot bij bakkerij-kassa (icoon ?) bij bestelling ?
#define GRP_VOORSCHOT   1006            // komt in dranken normaal ook niet voor (denk ik)
#define GRP_GELD        1010            // Bedrag betaald in GELD
#define GRP_ECHEQUE     1011            // Bedrag betaald met Eurocheques (vroeger) of electronische maaltijdcheques (wordt geventileerd in subgroepen)
#define GRP_BANCONT     1012            // Bedrag betaald via Bankcontact (kan ook maestro zijn !)
#define GRP_MAALTIJD    1013            // Bedrag betaald in papieren maaltijdcheques
#define GRP_TGBON       1014            // Bedrag betaald met vroegen afgedrukte eigen tegoedbons (zie GRP_TEGOED)
#define GRP_LEVERBON    1015            // Bedrag betaald met bonnetjes leverancier
#define GRP_CREDIT      1016            // Bedrag betaald via Creditcard
#define GRP_TBSALDO     1017            // Wordt later betaald (na ontvangst factuur), is dus KREDIET
#define GRP_MEETOTAAL   1018            // Goederen en leeggoed (totaal mee)
#define GRP_DIVUITGAVE  1019            // Bedrag voor diverse uitgave (moet nog uitgesplits worden)
#define GRP_DIVONTVANG  1020            // Bedrag voor diverse ontvangst (moet nog uitgesplits worden)
#define GRP_ZEGELS      1021    // Zegels van de Valois e.d. ???? 
#define GRP_LGTERUG     1022            // Leeggoed teruggenomen (weet niet of dit nog gebruikt wordt, staat meestal in de 'detaillijnen'), was bedoeld voor aanname leeggoed-tickets
#define GRP_PROTON      1023            // betaald met proton
#define GRP_VOORSCHOT_R    1024     // voorschot retourname (boekingstechnisch voor bakkerij)

static char *FinGroepNaam[40]={"Totaal MEE","Tegoedbon MEE","Geld terug","Goederen","Leegg.mee",
															 "5","6","7","8","9",
															 "Geld","E-cheques","Bancontact","Maaltijdcheques","Eigen tg-bon",
															 "Leveranciersbon","Creditcard","Part.NIET betaald","Goed.+lgg MEE","Diverse uitgave",
															 "Diverse inkomst","Zegels","Leeggoed terug","Mobiel","Vrschot retour",
															 "Afrondingsverschillen","26","27","28","29",
												       "Cadeaubon uitgegeven","Cadeaubon ontvangen","V.betwijze 1","V.betwijze 2","V.betwijze 3","MC Sodexo","MC Edenred","MC PayFair","38","39"};
static int FinNrs[DIM_FINNRS]={10,11,12,13,14,15,16,23,30,31,32,33,34,17,35,36,37}; // niet zomaar mixen, zie parameters grootboek!
static char *FinNrsCode[DIM_FINNRS]={"GE","EC","BC","MC","ET","LB","CC","MO","CU","CO","V1","V2","V3","NB","MC","MC","MC"};

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
#define GRP_AFRONDING    1045		// Afronding kasticket op 5 cent    ***!!! WORDT HIER OMGELEID NAAR FIN.GROEP 25 !!!!***

/*
vrijhouden voor fin.rekeningen  t/m 1049
*/

#define GRP_FAKT        1100
#define GRP_TERPLAATSE  1200 

#define GRP_ATTENTION             9900
#define GRP_T_RB        9995
#define GRP_T_R         9996
#define GRP_T_U         9997
#define GRP_TEXT        9998
#define GRP_TIJD        9999


#define DIM_FINTOT       41   // 1000-1030 + 1040-1049
#define MAX_LOGDAGUSED   1500 

static struct s_lijn{   // als we hier iets aan wijzigen, ook aanpassen in OVL290 
                 // is ook belangrijk bij adden in kaslog.dat (truuk voor textlijn)
  char text[41];                                            // ingevuld zo groep >= 9900, bv. GRP_TEXT of GRP_TIJD
  unsigned char bits;                                 // & STUKS om te weten of het stuksflag is of niet 
  char code[ARTCODE_LEN];  
  float aantal;
  short groep;
  float btw;
  float prijs;
  double totaal;
} *pLogLijn;

// volgende stuk komt uit KasCommn.cpp

static struct {
  char versie[32];
  long lade_pos;
  short lade_aantal;
  short lade_len;
  long dag_pos;
  short dag_len;
  short dag_aantal;
  short dag_used;
  long rec_pos;
  long rec_len;
  long rec_aantal;
  long rec_used;
  short ticketnr;
       long LastZTotaalPrintedRecords;
       long LastZTotaalPrintedSeqNr;
} LogHeader;


static struct s_LogLade {
  char valuta[3];
  long open_wissel;
  long open_bet;
  double bedrag[20];
} LogLade[10];
int LogLadeUsed;





static struct _LogDag { // Jaak
  unsigned short datum;
  long first_rec;
} LogDag[MAX_LOGDAGUSED];
static int LogDagUsed;

// tot hierboven uit KasCommn.cpp

static struct s_Kasticket {
  int TicketNr;   
  int KlantNr;  // klant waar bon of factuur op gemaakt wordt
  char KlantNaam[41]; // naam factuurklant
	char KlantNrString[10]; // nummer factuurklant als string, owv klantcode met letters (999999 = nieuwe klant)
	char KlantStraat[30];
	char KlantPostcode[10];
	char KlantGemeente[30];
	char KlantBTWString[20];
	int FactNr;   // Nummer factuur 
  int FactType; // 1 -> Kleine factuur (op kasticket),   2 -> Grote Factuur (met aparte printer, oud systeem),   3 -> leveringsbonnetje (op ticket, oud systeem)
                                                      // nieuw systeem moet nog toegevoegd worden.
  char VrijeTekst[4][41]; // vrije teksten bij in- of uitgave
	unsigned short FactDate;
  int KaartNr;
  int KaartPunten;
  double GroepTot[101];
  double FinTot[DIM_FINTOT];                      // Offset tov GRP_TOTAAL
  double FinSubGrpTot[DIM_FINTOT];  // zo GRP_ECHEQUE -> E-Cheques : 4 -> Sodexo, 5 -> Edenred, 6 -> PayFair, 7-> RES
  double BtwPerc[CUMBTW_COUNT];
  double BtwTot[CUMBTW_COUNT];
	double Goederen;
	double Leeggoed;
	double Totaal;
  int LijnUsed;
  struct s_lijn Lijn[LIN_COUNT];
} Kasticket;

static float SoortKorting[LIN_COUNT]; // om op lijst promo's het soort korting te kunnen geven per lijn

static double GroepTot[101][3];  // 0=totaal, 1=particulier, 2=bon/factuur
static double FinTot[DIM_FINTOT][3];
static double FinSubGrpTot[DIM_FINTOT][3];
static double BtwPerc[CUMBTW_COUNT][3];
static double BtwTot[CUMBTW_COUNT][3];
 
static CFile FilKaslog;
static double btw_bas[CUMBTW_COUNT+1],btw_bd[CUMBTW_COUNT+1];
   
static void ClearTicket()
{
	memset(&Kasticket,0,sizeof(Kasticket));
	zero((char *)&SoortKorting[0],sizeof SoortKorting);
}

static void ClearTotalSums()
{
	memset(GroepTot,0,sizeof(GroepTot));
	memset(FinTot,0,sizeof(FinTot));
	memset(FinSubGrpTot,0,sizeof(FinSubGrpTot));
	memset(BtwPerc,0,sizeof(BtwPerc));
	for(int k=0;k<DIMBTW;k++){for(int j=0;j<3;j++) BtwPerc[k][j]=btw_pct[k];} // default uit parameters invullen 
	memset(BtwTot,0,sizeof(BtwTot));
	memset(KVBoekTabel,0,sizeof KVBoekTabel);
  BonTickets.RemoveAll();	FactuurTickets.RemoveAll();
	InkomstTickets.RemoveAll(); UitgaveTickets.RemoveAll();
	TotaalAantalTickets=0; TotaalBedragTickets=0;
}

static int LogDagIx, LogRecIx;

static bool LogSetDag(int DagIx)
{
	if (DagIx>=0 && DagIx<LogDagUsed) {
		LogDagIx=DagIx;
		LogRecIx=LogDag[LogDagIx].first_rec;
		return true;
	}
	return false;
}

static int LogReadProcess()
{
  char bits;
  int groep, processed;
 
  FilKaslog.Read(&pLogLijn->bits,LogHeader.rec_len); processed=1;
  bits=pLogLijn->bits;
  if (bits & 0x80) {
    movmem(pLogLijn->code,pLogLijn->text,20);
    movmem(pLogLijn->code+20,&groep,sizeof(groep));
    FilKaslog.Read(&pLogLijn->bits,LogHeader.rec_len); processed++;
    movmem(pLogLijn->code,&pLogLijn->text[20],20);
    memset(pLogLijn->code,0,sizeof(struct s_lijn)-sizeof(pLogLijn->bits)-sizeof(pLogLijn->text));
    pLogLijn->groep=groep;
    pLogLijn->bits=bits;
  }
  return processed;
}

static bool LogReadNextTicket()
{
	ClearTicket();
	
  char buf[50],artcode_[ARTCODE_LEN+1];
  unsigned processed;
  long rec_ix, RecIxNextDay,rekenc;
	int i, j,k,g,off_0_=0, groep,LijnCommentRead=0, IxSoortVerkoop,rec_,fin_grp_nr_; // Ix : 1=verkoop, 2=bon, 3=factuur, 4=uitgave, 5=inkomst
  CString cstr_,betstring_;

  if (LogRecIx<LogDag[LogDagIx].first_rec) return false;

	RecIxNextDay=LogHeader.rec_used;
	if (LogDagIx<LogDagUsed-1) RecIxNextDay=LogDag[LogDagIx+1].first_rec;
	if (LogRecIx>=RecIxNextDay) return false;

	ClearTicket();IxSoortVerkoop=1; // default particulier
	FilKaslog.Seek(LogHeader.rec_pos+LogRecIx*LogHeader.rec_len,CFile::begin);

  rec_ix=LogRecIx; 
  FOREVER {
    if (Kasticket.LijnUsed==LIN_COUNT) {
      sprintf(buf,"Too many at rec_ix %6ld",rec_ix);
      // ConMessageBox(buf,"error",MB_OK);
      break;
    }
		if (rec_ix>=RecIxNextDay) break;

		pLogLijn = &Kasticket.Lijn[Kasticket.LijnUsed];
    processed=LogReadProcess();
    rec_ix+=processed;
    if (Kasticket.LijnUsed>0 && pLogLijn->bits&NEW_TICKET) {
      rec_ix-=processed; break;
    }
    Kasticket.LijnUsed++; 

		groep=pLogLijn->groep; off_0_=0;
		if(groep==GRP_TEGOED) groep=GRP_TGBON; /// aangemaakt tegoed ook onder tegoedbon zetten
		if (groep==GRP_FKORT || groep==GRP_PKORT) {
			if(Kasticket.LijnUsed>0) {
				SoortKorting[Kasticket.LijnUsed-1]=pLogLijn->prijs;
				if(groep==GRP_FKORT) SoortKorting[Kasticket.LijnUsed-1]+=1000.;// om verschil tussen % en EUR korting te maken
			}
			int j=Kasticket.LijnUsed-2; copy(pLogLijn->code,artcode_,ARTCODE_LEN);
			while(j>=0){ // zoeken naar laatste artikel
				if(cmpstr(Kasticket.Lijn[j].code,artcode_,ARTCODE_LEN)==0){
  				groep=Kasticket.Lijn[j].groep;
	  			if(groep>=1 && groep<=99)break;
				}
				j--;
			}
			if(j<0) groep=1; // zou niet mogen voorkomen !!!
			pLogLijn->groep=groep; // voor latere verwerking
		}
    if (groep==GRP_TIJD) stcd_i(&pLogLijn->text[8],&Kasticket.TicketNr);
		else if (groep==GRP_FAKT) {
			Kasticket.KlantNr=(int)(pLogLijn->aantal+.001);
			Kasticket.FactNr=(int)(pLogLijn->prijs+.001);
			Kasticket.FactType=(int)(pLogLijn->btw+.001);
			Kasticket.FactDate=(unsigned short int)(pLogLijn->totaal+.001);
			if(pLogLijn->code[0]=='F')  IxSoortVerkoop=3; else IxSoortVerkoop=2; // verschil tussen rechtstreekse factuur of (lever)bon
		}
		else if (groep==GRP_DIVUITGAVE) {
			Kasticket.FinTot[groep-GRP_TOTAAL]+=Round((double)(pLogLijn->totaal),(double)(0.01));
			Kasticket.Totaal+=Round((double)(pLogLijn->totaal),(double)(0.01));
			IxSoortVerkoop=4;
		}
		else if (groep==GRP_DIVONTVANG) {
			Kasticket.FinTot[groep-GRP_TOTAAL]+=Round((double)(pLogLijn->totaal),(double)(0.01));
			Kasticket.Totaal+=Round((double)(pLogLijn->totaal),(double)(0.01));
			IxSoortVerkoop=5;
		}
		else if (groep==GRP_PUNTEN) {
			Kasticket.KaartPunten=(int)(pLogLijn->aantal+.001);
			Kasticket.KaartNr=(int)(pLogLijn->btw+.001);
		}
		else if (groep>=0 && groep<=100) {
			off_0_=0;
			Kasticket.GroepTot[groep]+=Round((double)(pLogLijn->totaal),(double)(0.01));
			Kasticket.Totaal+=Round((double)(pLogLijn->totaal),(double)(0.01));
			if(groep==99) Kasticket.Leeggoed+=Round((double)(pLogLijn->totaal),(double)(0.01));
			else{
			  Kasticket.Goederen+=Round((double)(pLogLijn->totaal),(double)(0.01));
				if(pLogLijn->btw==0 && fldlen(6,39) && fldlen(6,40)){ // lotto apart zetten 
					fasinit(6);copy(pLogLijn->code,s(6,2),fldlen(6,2));
    			if(sys4408){*pu_6_1=val(s(6,2));g=fasgetu(6);} // record# is code op kassa
		    	else{g=faskeyu(6,1,0);}
			    if(g==0 && *l(6,40) && *s(6,40)!=0xFF) {
						off_0_=4;
					}
				}
				for (i=0+off_0_; i<CUMBTW_COUNT; i++) {
					if (pLogLijn->btw==Kasticket.BtwPerc[i]) {
						Kasticket.BtwTot[i]+=Round((double)(pLogLijn->totaal),(double)(0.01)); 
						break;
					}
				}
				if (i==CUMBTW_COUNT) {
					for (i=0+off_0_; i<CUMBTW_COUNT; i++) {
						if (Kasticket.BtwTot[i]==0. && Kasticket.BtwPerc[i]==0) {
							Kasticket.BtwPerc[i]=pLogLijn->btw;
							Kasticket.BtwTot[i]=Round((double)(pLogLijn->totaal),(double)(0.01));
							break;
						}
					}
				}
			}
		}
		else if (groep>=GRP_TOTAAL && groep<1050 && !(groep>=1030 && groep<=1039)) { // 1000-1029 en 1040-1049
			if(groep==1045) fin_grp_nr_=25; // WORDT OMGELEID NAAR 25 OMDAT SODEXO OP 35 ZIT !!!
			else if(groep>=1040 && groep<=1049) fin_grp_nr_=groep-1010; 
			else fin_grp_nr_=groep-GRP_TOTAAL; // gat tussen 1030-1039 overslaan
		  if (groep==GRP_CDBON_VRK || groep==GRP_CDBON_BET) { // teken omkeren
				Kasticket.FinTot[fin_grp_nr_]-=Round((double)(pLogLijn->totaal),(double)(0.01));
			}
			else if (groep==GRP_ECHEQUE) { //   Sodexo (Fg 35) , 5 -> Edenred (Fg 36), 6 -> PayFair (Fg 37) eventueel uitsplitsen, rest op E-cheques
				int subgroep=(int)(pLogLijn->aantal+.001);
				switch(subgroep){ //  E-Cheques : 4 -> Sodexo (Fg 35) , 5 -> Edenred (Fg 36), 6 -> PayFair (Fg 37), 7 -> RES (NIET apart)
				  case 4 : subgroep=35; break;
					case 5 : subgroep=36; break;
					case 6 : subgroep=37; break;
					default : subgroep=0; break;
				}
				if(subgroep){
					for(k=0;k<DIM_FINNRS;k++) if(FinNrs[k]==subgroep) break;
					if(k<DIM_FINNRS && (KV_GrbFinDet[k] || sys1804==0)) fin_grp_nr_=subgroep; // GRB rekening moet ook ingevuld zijn indien BKH
				}
				//if (subgroep>=0 && subgroep<=30) {
				//	Kasticket.FinSubGrpTot[subgroep]+=Round((double)(pLogLijn->totaal,(double)(0.01));
				//}
				//else Kasticket.FinTot[groep-GRP_TOTAAL]+=Round((double)(pLogLijn->totaal,(double)(0.01));
				Kasticket.FinTot[fin_grp_nr_]+=Round((double)(pLogLijn->totaal),(double)(0.01));
			}
			else Kasticket.FinTot[fin_grp_nr_]+=Round((double)(pLogLijn->totaal),(double)(0.01)); 
		}

		else if (groep==GRP_TEXT) {
			if(IxSoortVerkoop==2 || IxSoortVerkoop==3){ // bon / factuur
				if(LijnCommentRead==0){
					cstr_=CString(pLogLijn->text);cstr_=cstr_.Mid(10,10);cstr_.Trim();
		//			if(cstr_.Find("99999999")>=0) cstr_=""; // nieuwe klant, codenummer leeglaten
					copy0((char *)(LPCTSTR)cstr_,Kasticket.KlantNrString,10);
					cstr_=CString(pLogLijn->text);cstr_=cstr_.Mid(28,15);cstr_.Trim();
					copy0((char *)(LPCTSTR)cstr_,Kasticket.KlantBTWString,15);
				}
				else if(LijnCommentRead==1){
					cstr_=CString(pLogLijn->text);cstr_.Trim();
					copy0((char *)(LPCTSTR)cstr_,Kasticket.KlantNaam,40);
				}
				else if(LijnCommentRead==2){
					cstr_=CString(pLogLijn->text);cstr_.Trim();
					copy0((char *)(LPCTSTR)cstr_,Kasticket.KlantStraat,30);
			  }
				else if(LijnCommentRead==3){
					cstr_=CString(pLogLijn->text);cstr_=cstr_.Mid(0,7);cstr_.Trim();
					copy0((char *)(LPCTSTR)cstr_,Kasticket.KlantPostcode,7);
					cstr_=CString(pLogLijn->text);cstr_=cstr_.Mid(7,25);cstr_.Trim();
					copy0((char *)(LPCTSTR)cstr_,Kasticket.KlantGemeente,25);
				}
				LijnCommentRead++;
			}
			else if(IxSoortVerkoop==4 || IxSoortVerkoop==5){ // uitgave/ inkomst
				if(LijnCommentRead==0)copy0(pLogLijn->text,Kasticket.KlantNaam,40);
				else if(LijnCommentRead<5) copy0(pLogLijn->text,Kasticket.VrijeTekst[LijnCommentRead-1],40);
				LijnCommentRead++;
			}
		}
  }

	Kasticket.FinTot[4]=Kasticket.Leeggoed; Kasticket.FinTot[22]=0; // correctie indien geen totaal leeggoed op kasticket
	LogRecIx=rec_ix;
	for(int ivk_=0;ivk_<3;ivk_++){
		if(ivk_!=0 && ivk_!=IxSoortVerkoop) continue;
		for (i=0; i<=100; i++) GroepTot[i][ivk_]+=Kasticket.GroepTot[i];
		for (i=0; i<=40; i++)  if(i!=17 || !(IxSoortVerkoop==2 || IxSoortVerkoop==3)) FinTot[i][ivk_]+=Kasticket.FinTot[i]; // krediet enkel tellen indien part.verkoop
		for (i=0; i<=40; i++)  FinSubGrpTot[i][ivk_]+=Kasticket.FinSubGrpTot[i];
		for (i=0; i<CUMBTW_COUNT; i++) {
			if (Kasticket.BtwTot[i]==0.) continue;
			off_0_=0; 
			if(i>3 && Kasticket.BtwPerc[i]==0) {off_0_=4;}
			for (j=0+off_0_; j<CUMBTW_COUNT; j++) {
				if (Kasticket.BtwPerc[i]==BtwPerc[j][ivk_]) {
					BtwTot[j][ivk_]+=Kasticket.BtwTot[i];
					break;
				}
			}
			if (j==CUMBTW_COUNT) {
				for (j=0+off_0_; j<CUMBTW_COUNT; j++) {
					if (BtwTot[j][ivk_]==0.) {
						BtwPerc[j][ivk_]=Kasticket.BtwPerc[i];
						BtwTot[j][ivk_]=Kasticket.BtwTot[i];
						break;
					}
				}
			}
		}
	}
	if(Kasticket.KlantNaam[0]){  // text in Jascii zetten 
  	Asc2Jasc(Kasticket.KlantNaam,sizeof Kasticket.KlantNaam);
  	Asc2Jasc(Kasticket.KlantStraat,sizeof Kasticket.KlantStraat);
  	Asc2Jasc(Kasticket.KlantGemeente,sizeof Kasticket.KlantGemeente);
	}
	betstring_=CString("");
	for(k=0;k<DIM_FINNRS;k++){
		if(Kasticket.FinTot[FinNrs[k]]) {
			if(betstring_.GetLength()) betstring_=betstring_+",";
			betstring_=betstring_+CString(FinNrsCode[k]);
		}
	}
	if(IxSoortVerkoop>=1 && IxSoortVerkoop<=3){// totaal bijwerken van verkoop
		TotaalAantalTickets++; TotaalBedragTickets+=Kasticket.Totaal;
	}
	if(IxSoortVerkoop==1 && sys1804 && KV_ToonBoekscherm=='J'){// boekhoudgegevens bijwerken van particulier verkoop
		for(i=0;i<Kasticket.LijnUsed;i++){
  		pLogLijn = &Kasticket.Lijn[i];
			if (pLogLijn->groep<0 || pLogLijn->groep>100) continue;
			fasinit(6);copy(pLogLijn->code,s(6,2),fldlen(6,2));
			if(sys4408){*pu_6_1=val(s(6,2));g=fasgetu(6);} // record# is code op kassa
			else{g=faskeyu(6,1,0);}
			if(g){
				fasinit(6);
				if(pLogLijn->groep==99) *u(6,1)=TbDiversArtikel[9]; // leeggoed divers
  			else {
	  			for(j=0;j<8;j++) if(pLogLijn->btw==btw_pct[j]) break;
  				if(j<8) *u(6,1)=TbDiversArtikel[j];
				}
				if(*u(6,1)) fasgeti(6);
			}
			if(pLogLijn->groep!=99){// enkel goederen, leeggoed wordt als totaal genomen
				rekenc=makegrb(*u(6,1),pLogLijn->btw);
				rec_=getgrb(rekenc);
				for(k=0;k<DIM_BEWEGING;k++) if(KVBoekTabel[k].recnr==rec_ || KVBoekTabel[k].recnr==0) break;
				if(k<DIM_BEWEGING){
					KVBoekTabel[k].bedrag+=pLogLijn->totaal/(1.+pLogLijn->btw/100.);
					KVBoekTabel[k].type='G';KVBoekTabel[k].recnr=rec_;
					copy(s(3,3),KVBoekTabel[k].naam,fldlen(3,3));
				}
			}
		}
	}

	if(IxSoortVerkoop==2){// klanten bijhouden van bon
		if(cmpstr(Kasticket.KlantNrString,"99999999",8)==0) AddNewKlantFromKasticket(); // nieuwe klanten direct toevoegen
		BonTickets.AddTail(Kasticket.KlantNrString);
		BonTickets.AddTail(Kasticket.KlantNaam);
		cstr_.Format("%f",Kasticket.Totaal);BonTickets.AddTail(cstr_);//tickettotaal
		cstr_.Format("%f",Kasticket.FinTot[17]);BonTickets.AddTail(cstr_); // credit (niet betaald)
		if(Kasticket.FactNr>1) cstr_.Format("%d",Kasticket.FactNr); else cstr_.Format("%d",Kasticket.TicketNr); BonTickets.AddTail(cstr_); // bonnummer of ticketnummer bij oud systeem
		BonTickets.AddTail(betstring_);
	}
	else if(IxSoortVerkoop==3){// klanten bijhouden van factuur
		if(cmpstr(Kasticket.KlantNrString,"99999999",8)==0) AddNewKlantFromKasticket(); // nieuwe klanten direct toevoegen
		FactuurTickets.AddTail(Kasticket.KlantNrString);
		FactuurTickets.AddTail(Kasticket.KlantNaam);
		cstr_.Format("%f",Kasticket.Totaal);FactuurTickets.AddTail(cstr_);//tickettotaal
		cstr_.Format("%f",Kasticket.FinTot[17]);FactuurTickets.AddTail(cstr_); // credit (niet betaald)
		cstr_.Format("%d",Kasticket.FactNr);FactuurTickets.AddTail(cstr_); // factuurnummer
		FactuurTickets.AddTail(betstring_);
	}
	else 	if(IxSoortVerkoop==4){// tickets bijhouden van uitgave
		UitgaveTickets.AddTail(Kasticket.KlantNaam);
		cstr_.Format("%f",Kasticket.Totaal);UitgaveTickets.AddTail(cstr_);//tickettotaal
		cstr_.Format("%f",0);UitgaveTickets.AddTail(cstr_); // credit (niet betaald)
		for(k=0;k<4;k++) UitgaveTickets.AddTail(Kasticket.VrijeTekst[k]);
		UitgaveTickets.AddTail(betstring_);
	}
	else 	if(IxSoortVerkoop==5){// tickets bijhouden van inkomst
		InkomstTickets.AddTail(Kasticket.KlantNaam);
		cstr_.Format("%f",Kasticket.Totaal);InkomstTickets.AddTail(cstr_);//tickettotaal
		cstr_.Format("%f",0);InkomstTickets.AddTail(cstr_); // credit (niet betaald)
		for(k=0;k<4;k++) InkomstTickets.AddTail(Kasticket.VrijeTekst[k]);
		InkomstTickets.AddTail(betstring_);
	}
	return true;
}


static int AddNewKlantFromKasticket(void)
{
  int16 k;
  long min_kod_,max_kod_,lbd_;
 
  fasinit(2);
	copy0(Kasticket.KlantNaam,s(2,3),fldlen(2,3)); 
	if(faskeyi(2,2,0)==0){ // eerst kijken of hij er al in zit
		if(cmpstr(s(2,4),Kasticket.KlantStraat,5)==0) {k=0;goto added;} // dubbelcheck op stukje straat
	}
  fasinit(2);
  if(fldlen(2,2)){// automatisch codenummer zoeken 9xxxx 
    max_kod_=9;min_kod_=9; for(k=0;k<fldlen(2,2)-1;k++) {min_kod_*=10;max_kod_=max_kod_*10+9;}
    for(lbd_=min_kod_;lbd_<max_kod_;lbd_++){
      fasinit(2);
      stcli_d(s(2,2),lbd_,fldlen(2,2),0);
      if(faskeyi(2,1,0)) break;
    }
  }
	copy0(Kasticket.KlantNaam,s(2,3),fldlen(2,3));
	copy0(Kasticket.KlantStraat,s(2,4),fldlen(2,4));
	copy0(Kasticket.KlantPostcode,s(2,5),fldlen(2,5));
	copy0(Kasticket.KlantGemeente,s(2,6),fldlen(2,6));
	*l(2,10)=String2BtwNr(Kasticket.KlantBTWString,13);
  if(fldlen(2,36)) *u(2,36)=def_qfak;
  if(fldlen(2,25)) *s(2,25)='0';
#if FLAGEET
  if(fldlen(2,25)) *s(2,25)='1';
#endif
  *s(2,26)=sys3896[0];
  k=fasadd(2);
added:;
	if(k==0){ // kasticket updaten met nieuwe info
		memset(Kasticket.KlantNrString,0,sizeof Kasticket.KlantNrString);
		if(fldlen(2,2)) copy0(s(2,2),Kasticket.KlantNrString,fldlen(2,2));
		else sprintf_s(Kasticket.KlantNrString,6,"%05d",*u(2,1));
		Kasticket.KlantNr=*u(2,1);
	}
  return k;
}



static bool LogOpenKaslog(char *FileNameKasLog)
{
	if (!FilKaslog.Open(FileNameKasLog,CFile::modeRead)) return false; // file not found !

  if (FilKaslog.Read(&LogHeader,sizeof(LogHeader))!=sizeof(LogHeader)) {
		FilKaslog.Close();
		return false; // file not OK !
	}
  if (memcmp("KASLOG.DAT   Ver. 1.00\x1A",LogHeader.versie,20)) {
		FilKaslog.Close();
		return false; // file not OK !
	}

	// Lees de lade-info
	LogLadeUsed=LogHeader.lade_aantal;
  if (LogLadeUsed>10) LogLadeUsed=10;
  FilKaslog.Seek(LogHeader.lade_pos,CFile::begin);
  FilKaslog.Read(LogLade,sizeof(struct s_LogLade)*LogLadeUsed);

	// lees de dag-info
	LogDagUsed=LogHeader.dag_used;
	if (LogDagUsed>MAX_LOGDAGUSED) LogDagUsed=MAX_LOGDAGUSED;
	FilKaslog.Seek(LogHeader.dag_pos,CFile::begin);
	FilKaslog.Read(LogDag,LogHeader.dag_len*LogDagUsed);

	return true;
}


static void TestReadKaslog()
{
	if (!LogOpenKaslog("kaslog.dat")) return;

	for (int DagIx=0; DagIx<LogDagUsed; DagIx++) {
    ClearTotalSums();
		if (!LogSetDag(DagIx)) break;
		unsigned TicketDatum=LogDag[DagIx].datum;
	  int TicketCount=0;
		while (LogReadNextTicket()) {
			int lines = Kasticket.LijnUsed;
			TicketCount++;
		}
		double tot = FinTot[0][0];
		int i=0;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


extern "C" void DRK0290cod(void)
{
  int16 curs=1,key,z;
  char choice,buf_[10];
	  
  initload();
  FOREVER{
		redo:;
    scrnum=0;scrget(3,1);z=1;fasunlck(0);
	  scraddpicto(1,0,76,22,4,2,514,0,0,"Extra opties"); 
		scraddpicto(50,0,78,4,2,1,105,1,7,"^!B0290A");
		scraddpicto(51,0,78,15,2,1,105,1,7,"^!B0290C");
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);

    if(ovltest(2291)){
      scraddf(118,21,4,2);
      scrifld(118,VarTextFmt(79,0),"Beheer koppelingen Prik&Tik (prijslijsten, promofolder, ...) ...... : P ");
    }
    key=scrupd(curs,0x0681);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){DisplayExtraFuncties();goto redo;} // extra opties
		if(key==5050 || key==5051) goto redo; // link help 
    if(key==101) goto endsr;
		if(key==110){
			if(DisplayWarning("Wenst u echt de communicatieserver te resetten?",605,1)){
  			ExecJmsCommand(buf_,sizeof buf_,"RestartUcServer");
				goto redo;
			}
		}
    if(key==111) ovlexit(-1);
		fasunlck(-1);
    switch(choice){
      case '1': if(ovltest(295)) ovlexit(295); break;
      case '2': if(ovltest(292)) ovlexit(292); break;
      case '3': inp_1dag(); break;
      case '4': KasVerslag(); break;
      case '5': if(ovltest(2290)) ovlexit(2290); else errnum=12; break;
      case '6': dsp_dagt(); break;
      case '7': control(); break;
      case '9': if(ovltest(294)) ovlexit(294); else errnum=12; break;
			case '+': DisplayExtraFuncties(); break;
      case 'C': PrijsControleKassaverkopen(); break;
      case 'D': LijstVerkochtePromos(); break;
      case 'K': if(ovltest(293)) ovlexit(293); break;
      case 'P': if(ovltest(2291)) ovlexit(2291); break;
      default : errnum=34; break;
    }
  }
  endsr:;
  fasclos(-2);
  ovlexit(-1);
}

static void DisplayExtraFuncties(void)
{
	int16 curs=1,key,z;
  char choice;
 
  FOREVER{
    scrnum=0;scrget(3,2);z=1;fasunlck(0);
	  scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
		fasunlck(-1);
    switch(choice){
      case '1': inp_klant(); break;
      case '2': add_barcode(); break;
      case '4': update(); break;
      case 'A': wissen();  break;
      case 'B': add(); break;// voor test 
      case 'C': CheckForDeletedArt();  break;
			case 'X': MoveForNewKassa();  break;// verhuizen verkopen bij bijkomende kassa
			case 'Y': CorrectHisFromVkp();  break;// part.historieken bijwerken ahv vkp
      case '+': param(0); break;
      default : errnum=34; break;
    }
  }
  endsr:;
}

static void CheckForDeletedArt(void)
{
	uint16 j,def_art;
  long a,used;


	for(j=0;j<8;j++) if(def_btw==btw_pct[j]) break;
	if(j<8) def_art=TbDiversArtikel[j];
	  
	if(scr_ok("Wenst U echt de kassaverkopen te controleren op geschrapte artikels???")==NO) goto endsr;
  fasinfo(91,1);
  used=GetRecNr(91);
  for(a=1;a<=used;a++){
    fasinit(91); SetRecNr(91,a);
    if(fasgeti(91)) continue;
    fasinit(6);*u(6,1)=*u(91,2);
    if(fasgeti(6)){
			*u(91,2)=def_art; 
			if(fasupd(91)){
				j=3; // bij meerdere artikels op 1 dag loopt het fout (duplicated key)
			}
    }
	}
	endsr:;
}


static void CorrectHisFromVkp(void)
{
	uint16 mode_,last_dt_=0;
  float tot_exc_;
	  
  if(ask_in_dt("Historieken bijwerken a.h.v. kasverkopen",YES,NO)) goto endsr;
  if(scr_ok("Wenst U echt deze verkopen toe te voegen aan de historieken ???")==NO) goto endsr;

	fasinit(91);*pu_91_3=dat_beg;mode_=1;
  FOREVER{
    if(faskeyu(91,2,mode_)) break;mode_=2;
    if(*pu_91_3>dat_end) break;
		if(last_dt_!=*u(91,3)){
			last_dt_=*u(91,3);
			scrget(1,170);scrifld(10,fm_udat,&last_dt_);scrupd(-3,0);
		}
		fasinit(6);*u(6,1)=*u(91,2); fasgeti(6);
		tot_exc_=*f(91,13+(inq_kassa-1)*5)/(1.+ *f(6,28)/100.);
		_his_upd(*pu_6_1,inq_kassa,f(91,11+(inq_kassa-1)*5),&tot_exc_,*pu_91_3);
		if((sys3772 & 0x40) && ft_off && fldlen(91,13+(inq_kassa-1+ft_off)*5)){
      tot_exc_=*f(91,13+(inq_kassa-1+ft_off)*5)/(1.+ *f(6,28)/100.);
     _his_upd(*pu_6_1,inq_kassa,f(91,11+(inq_kassa-1+ft_off)*5),&tot_exc_,*pu_91_3);
		}
	}
endsr:;

}

static void PrijsControleKassaverkopen(void)
{
	int j,k,g,kasnr,max_,DagIx,z,key,curs=2,curspos_,vpos_=0,p_attr_;
	int16 form_dat[8],pr_mode,prtnr;
	short int jj,mm,dd;
	uint16 dt_,tikketnr_,pnr_;
	float prx_n_,prx_k_,aantal_,bd_dif_;
	char str_[100],st_txt_[3],type_prx_,prx_str_[10];
	CString cstr_,knaam_,kcode_;


	if(inq_kassa==0 && max_kassa==1) inq_kassa=1;
  if(dat_beg==0 && inq_kassa==1) dat_beg=dt_kvk[0]+1;
  if(dat_end==0) dat_end=dat_beg;

	type_prx_=sys3896[0]; if(type_prx_<'0' || type_prx_>'9') type_prx_='0';
	zero(prx_str_,sizeof prx_str_); j=type_prx_-'0'; copy(&vptekst[j*10],prx_str_,6);

  FOREVER{
    redo:;
    scrnum=0;scrget(3,6);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&inq_kassa);
    z++;
		scrifld(-z,fm_u_09,&type_prx_); z++;	scrifld(z++,fm_os6,prx_str_);

		for(k=0;k<10;k++) {
	  	if(nm_kassa[k][0]){
				scrifld(z++,fm_os6,&nm_kassa[k][0]);
				scrifld(z++,fm_odat,&dt_kvk[k]);
				fasclos(-2);fasinit(80);
				MakeKaslogName(k+1,dat_end);
				fasopen(filnam,102);/* eerste call voor dir */
				fasinfo(80,204);/* ophalen antwoord van dir */
				if(*s(80,1)){
					fasinit(80);fasinfo(80,205);/* get date  */
					scrifld(z++,fm_os20,s(80,1));
					fasclos(-2);
					if (LogOpenKaslog(filnam)){
					  scrifld(z++,fm_odat,&LogDag[0].datum);
						scrifld(z++,fm_odat,&LogDag[LogDagUsed-1].datum);
						FilKaslog.Close();
					} else z+=2;
				} else z+=3;
			} else z+=5;
    }
    key=scrupd(curs,0x181);curs=2; curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
	  prt2pdf=NO; if(key==5002){prt2pdf=YES; key=108;} // pdf
    if(key==111) ovlexit(-1);
    if(key==101) return;
    if(dat_beg==0){curs=3;errnum=38;goto redo;}
    if(dat_end==0 || dat_end<dat_beg){curs=3;errnum=38;goto redo;}
//    if(only1kas && inq_kassa==0){curs=4;errnum=38;goto redo;}
    if(inq_kassa && fldlen(91,11+(inq_kassa-1)*5)==0){
      curs=4;errnum=34;goto redo;
    }
		if(type_prx_<'0' || type_prx_>'9' || fldlen(6,PrNrs[type_prx_-'0'])==0){curs=5;errnum=34;goto redo;}
		j=type_prx_-'0'; copy(&vptekst[j*10],prx_str_,6);
    if(key==18){curs=curspos_+1; goto redo;}

    if(key==108 || key==109) break;
  }
  if(dat_end==0) dat_end=0xFFFF;
	fasunlck(-2);
  scrget(1,7); scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(YES /* prt2pdf*/ ) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,96,pr_mode,4))!=0) return;

  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,29);
	zero(str_,sizeof str_);k=copy0("Prijscontrole",str_,15); 	if(inq_kassa) {k+=copy0(" kassa",&str_[k],6);stcli_d(&str_[k],(long)(inq_kassa),3,1);}
	prttext("<t35b>");prttext(str_);
  prttext("<b><t65>");prtifld(fm_udat,&dat_beg,-1);
  prttext(" - ");prtifld(fm_udat,&dat_end,-1);
  prttext("<t88>");prttext("Blz.<ppp>.");
  prtbuf(1);z=1;
  prtitab(z,fm_ou2,&kasnr,1,-1); prttitle(z++,"K",0x13);
  prtitab(z,fm_odat,&dt_,1,-1); prttitle(z++,"Datum",0x43);
  prtitab(z,fm_ou5,&tikketnr_,2,-1); prttitle(z++,"TickNr",0x13);
	prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
	prttab(z,6,3,1,-1); prttitle(z++,"Omschrijving",3);
	prtitab(z,fm_uf5_0,&aantal_,1,-1); prttitle(z++,"Aantal",0x13);
	prtitab(z,fm_os2,st_txt_,1,-1); prttitle(z++,"",0x13);
	prtitab(z,fm_uf5_2,&prx_n_,1,-1); if(type_prx_==sys3896[0]) prttitle(z++,"Normaal",0x13); else prttitle(z++,prx_str_,0x13);
	prtitab(z,fm_uf5_2,&prx_k_,1,-1); prttitle(z++,"Kassa",0x13);
	prtitab(z,fm_uf5_2,&bd_dif_,1,-1); prttitle(z++,"Verschil",0x13);
  prtbuf(3);
	p_pdfname(str_,dat_beg,dat_end);
	ClearTotalSums();
  kasnr=1; max_=10; if(inq_kassa){kasnr=inq_kassa; max_=inq_kassa;}
  for(kasnr;kasnr<=max_;kasnr++){
    if(nm_kassa[kasnr-1][0]=='\0') continue;
	  for(dt_=dat_beg;dt_<=dat_end;dt_++){
			MakeKaslogName(kasnr,dt_);
			if(GetFileAttributes(filnam)==INVALID_FILE_ATTRIBUTES){
				if((sys4400 & 0x4)==0) errnum=1;
				continue;
			}
			if (!LogOpenKaslog(filnam)) continue;

			for (DagIx=0; DagIx<LogDagUsed; DagIx++) if(LogDag[DagIx].datum==dt_) break;
			if(DagIx>=LogDagUsed) {FilKaslog.Close();continue;}
			if (!LogSetDag(DagIx)) {FilKaslog.Close();continue;}
			unsigned TicketDatum=LogDag[DagIx].datum;
			int TicketCount=0; 
			while (LogReadNextTicket()) {
				int lines = Kasticket.LijnUsed;
				p_attr_=0; if(Kasticket.Totaal<0) p_attr_=2; // indien negatief ticket, dan steeds in bold afdrukken
				for(k=0;k<lines;k++){ // eerst kortingen % en EUR die op volgende lijn staan corrigeren op artkel
					if(k>0 && Kasticket.Lijn[k].code[0] && Kasticket.Lijn[k].aantal==0 && Kasticket.Lijn[k].totaal){
						j=-1;
						if(cmpstr(Kasticket.Lijn[k-1].code,Kasticket.Lijn[k].code,fldlen(6,2))==0 && Kasticket.Lijn[k-1].groep==Kasticket.Lijn[k].groep) j=k-1;
						else if(k>=2 && cmpstr(Kasticket.Lijn[k-2].code,Kasticket.Lijn[k].code,fldlen(6,2))==0 && Kasticket.Lijn[k-2].groep==Kasticket.Lijn[k].groep) j=k-2;
						if(j>=0){
							Kasticket.Lijn[j].totaal+=Kasticket.Lijn[k].totaal;
							if(Kasticket.Lijn[j].aantal) Kasticket.Lijn[j].prijs=Kasticket.Lijn[j].totaal/ Kasticket.Lijn[j].aantal;
							Kasticket.Lijn[k].code[0]='\0';
						}
					}
				}
				for(k=0;k<lines;k++){
					if(Kasticket.Lijn[k].code[0]){
						fasinit(6);copy(Kasticket.Lijn[k].code,s(6,2),fldlen(6,2));
						if(sys4408){*pu_6_1=val(s(6,2));g=fasgetu(6);} // record# is code op kassa
			      else{g=faskeyu(6,1,0);}
						if(g==0){
							st_txt_[0]='\0';vpos_=0; if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_) vpos_=10;
							pnr_=PrNrs[type_prx_-'0'+vpos_]; if(Kasticket.Lijn[k].bits&1) {pnr_=PrNrs[tb_ktypes[max_kprx-1]+vpos_];copy("St",st_txt_,3);}
							prx_n_=*f(6,pnr_);
              if(!(sys3894 & (1<<(type_prx_-'0')))) prx_n_=Round((double)(prx_n_*(1.+*f(6,28)/100)),(double)(0.01));
							bd_dif_=Round((double)(prx_n_-Kasticket.Lijn[k].prijs),(double)(0.01));
							if(p_attr_ || bd_dif_>0){ // verschillen + negatieve tickets
								tikketnr_=Kasticket.TicketNr; prx_k_=Kasticket.Lijn[k].prijs; aantal_=Kasticket.Lijn[k].aantal;
								for(j=1;j<20;j++) prtinfo(j,p_attr_); nextline();
							}
						}
					}
				}

				TicketCount++;
			}
			FilKaslog.Close();
		}
  }
 
	prtclose();
	fasunlck(-1);
}

static void LijstVerkochtePromos(void)
{
	int j,k,n,nr_select_,kasnr,max_,DagIx,z,key,curs=2,curspos_,start_,vpos_,sw;  
	int16 form_dat[8],pr_mode,prtnr,min_kortingpct_=0;
	short int jj,mm,dd;
	uint16 dt_,tikketnr_,pnr_,dt_log_be[20][2],max_art_,fl_select_=NO;
	float prx_n_,prx_k_,aantal_,bd_dif_,bd_korting_,tot_aantal_,tot_korting_,pctkorting_;
	char str_[100],st_txt_[10],type_prx_,prx_str_[10],promo_txt[30],OnlyPromo='J',PrintPromo='J',PrintTotaal='N';
	CString cstr_,knaam_,kcode_;


	if(inq_kassa==0 && max_kassa==1) inq_kassa=1;
  if(dat_beg==0 && inq_kassa==1) dat_beg=dt_kvk[0]+1;
  if(dat_end==0) dat_end=dat_beg;

	type_prx_=sys3896[0]; if(type_prx_<'0' || type_prx_>'5') type_prx_='0';
	zero(prx_str_,sizeof prx_str_); j=type_prx_-'0'; copy(&vptekst[j*10],prx_str_,6);
	zero(promo_txt,sizeof promo_txt); zero((char *)&dt_log_be[0][0],sizeof dt_log_be);
	zero(st_txt_,sizeof st_txt_);
	fasinit(6); if(InqArt){*u(6,1)=InqArt;fasgeti(6);}
	fasinit(1); if(InqLev){*u(1,1)=InqLev;fasgeti(1);}

  FOREVER{
    redo:;
    scrnum=0;scrget(3,7);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
		scrfld(z++,6,3);
		scrfld(z++,1,3);
		scrifld(z++,fm_uJN,&OnlyPromo);
		scrifld(z++,fm_uu3,&min_kortingpct_);
		scrifld(z++,fm_uJN,&PrintPromo);
		scrifld(z++,fm_uJN,&PrintTotaal);
    scrifld(z++,fm_uu2,&inq_kassa);


		for(k=0;k<10;k++) {
	  	if(nm_kassa[k][0]){
				scrifld(z++,fm_os6,&nm_kassa[k][0]);
				scrifld(z++,fm_odat,&dt_kvk[k]);
				fasclos(-2);fasinit(80);
				MakeKaslogName(k+1,dat_end);
				fasopen(filnam,102);/* eerste call voor dir */
				fasinfo(80,204);/* ophalen antwoord van dir */
				if(*s(80,1)){
					fasinit(80);fasinfo(80,205);/* get date  */
					scrifld(z++,fm_os20,s(80,1));
					fasclos(-2);
					if (LogOpenKaslog(filnam)){
					  scrifld(z++,fm_odat,&LogDag[0].datum);
						scrifld(z++,fm_odat,&LogDag[LogDagUsed-1].datum);
						FilKaslog.Close();
					} else z+=2;
				} else z+=3;
			} else z+=5;
    }
    key=scrupd(curs,0x181);curs=2; curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
	  prt2pdf=NO; if(key==5002){prt2pdf=YES; key=108;} // pdf
    if(key==111) ovlexit(-1);
    if(key==101) return;
    if(dat_beg==0){curs=3;errnum=38;goto redo;}
    if(dat_end==0 || dat_end<dat_beg){curs=3;errnum=38;goto redo;}
//    if(only1kas && inq_kassa==0){curs=4;errnum=38;goto redo;}
		if(*s(6,3)){
			if(search(6,0)){curs=4; goto redo;}
		} else fasinit(6);
		InqArt=*u(6,1);
		if(*s(1,3)){
			if(search(1,0)){curs=4; goto redo;}
		} else fasinit(1);
		InqLev=*u(1,1);
		if(OnlyPromo!='J' && InqArt==0 && InqLev==0){errnum=38;curs=4;goto redo;} // artikel moet dan ingevuld zijn
    if(inq_kassa && fldlen(91,11+(inq_kassa-1)*5)==0){
      curs=10;errnum=34;goto redo;
    }
    if(key==108) break;
		if(key==109) {fl_select_=YES;break;}
  }
  if(dat_end==0) dat_end=0xFFFF;
	fasunlck(-2);
  zero((char *)tb,sizeof tb); max_art_=0;
	if(fl_select_){
		kasnr=1; max_=10; if(inq_kassa){kasnr=inq_kassa; max_=inq_kassa;}
		for(kasnr;kasnr<=max_;kasnr++){
			if(nm_kassa[kasnr-1][0]=='\0') continue;
			for(dt_=dat_beg;dt_<=dat_end;dt_++){
				MakeKaslogName(kasnr,dt_);
				if(GetFileAttributes(filnam)==INVALID_FILE_ATTRIBUTES){
					if((sys4400 & 0x4)==0) errnum=1;
					continue;
				}
				if (!LogOpenKaslog(filnam)) continue;

				for (DagIx=0; DagIx<LogDagUsed; DagIx++) if(LogDag[DagIx].datum==dt_) break;
				if(DagIx>=LogDagUsed) {FilKaslog.Close();continue;}
				if (!LogSetDag(DagIx)) {FilKaslog.Close();continue;}
				unsigned TicketDatum=LogDag[DagIx].datum;
				int TicketCount=0; 
				while (LogReadNextTicket()) {
					int lines = Kasticket.LijnUsed;
					for(k=0;k<lines;k++){ // eerst kortingen % en EUR die op volgende lijn staan corrigeren op artkel
						if(k>0 && Kasticket.Lijn[k].code[0] && Kasticket.Lijn[k].aantal==0 && Kasticket.Lijn[k].totaal){
							for(j=1;j<=3;j++){ // tot 3 lijnen terug gaan om korting op juist artikel te zetten
								if((k-j)>=0 && cmpstr(Kasticket.Lijn[k-j].code,Kasticket.Lijn[k].code,fldlen(6,2))==0 && Kasticket.Lijn[k-j].groep==Kasticket.Lijn[k].groep) break;
							}
							if(j<=3) j=k-j; else j=-1;
							if(j>=0){
								Kasticket.Lijn[j].totaal+=Kasticket.Lijn[k].totaal;
								if(Kasticket.Lijn[j].aantal) Kasticket.Lijn[j].prijs=Kasticket.Lijn[j].totaal/ Kasticket.Lijn[j].aantal;
      					SoortKorting[j]=SoortKorting[k];
								Kasticket.Lijn[k].code[0]='\0';
							}
						}
					}
					for(k=0;k<lines;k++){
						if(Kasticket.Lijn[k].code[0]){
							fasinit(6);copy(Kasticket.Lijn[k].code,s(6,2),fldlen(6,2));
							if(sys4408){*u(6,1)=val(s(6,2));	j=fasgeti(6);}
							else j=faskeyi(6,1,0);
							if(j==0 && *i(6,9)!=99 && (InqArt==0 || *u(6,1)==InqArt) && (InqLev==0 || *u(6,7)==InqLev || *u(6,101)==InqLev)){
								st_txt_[0]='\0'; zero(promo_txt,sizeof promo_txt);
								vpos_=0; if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_) vpos_=10;
								pnr_=PrNrs[type_prx_-'0'+vpos_]; if(Kasticket.Lijn[k].bits&1) {pnr_=PrNrs[tb_ktypes[max_kprx-1]+vpos_];copy("St",st_txt_,3);}
							
								prx_n_=*f(6,pnr_);
								if(!(sys3894 & (1<<(type_prx_-'0')))) prx_n_=Round((double)(prx_n_*(1.+*f(6,28)/100)),(double)(0.01));
								bd_dif_=prx_n_-Kasticket.Lijn[k].prijs; 
								pctkorting_=0; 
								if(SoortKorting[k]>0 && SoortKorting[k]<1000 ) pctkorting_=SoortKorting[k];
								else if(prx_n_) pctkorting_=Round((double)((bd_dif_/prx_n_)*100.),(double)(1.0)); 
								if(OnlyPromo!='J' || (Kasticket.Lijn[k].prijs==0 || (!is_nul((double)(bd_dif_)) && bd_dif_>0 && pctkorting_>=min_kortingpct_))){
			  					for(n=0;n<max_art_;n++) if(*u(6,1)==tb[n].rec) break;
									if(n>=max_art_){
										tb[n].rec=*u(6,1); *(char *)&tb[n].aantal='J';
										if(max_art_<DIM_TB-1)  max_art_++;
										else {errnum=11; break;}
									}
								}
							}
						}
					}
					TicketCount++;
				}
				FilKaslog.Close();
			}
		}

		start_=0; curs=1;
		if(max_art_==0){errnum=14;goto endsr;}
		if(max_art_>=DIM_TB) errnum=11;
		fasinit(6);z=0;
		FOREVER{
			if(faskeyi(6,2,2)) break;
			for(k=0;k<max_art_;k++) if(tb[k].rec==*u(6,1)) {tb[k].AW=z++; break;}
		}
		FOREVER{// sorteren 
			sw=NO;
			for(k=0;k<max_art_-1;k++){
				if(tb[k+1].AW<tb[k].AW){
					copy((char *)&tb[k].rec,(char *)&tb[DIM_TB].rec,sizeof tb[0]);
					copy((char *)&tb[k+1].rec,(char *)&tb[k].rec,sizeof tb[0]);
					copy((char *)&tb[DIM_TB].rec,(char *)&tb[k+1].rec,sizeof tb[0]);
					sw=YES;
				}
			}
			if(sw==NO) break;
		}

		FOREVER{
			redosel:;
			scrnum=0;scrget(3,46);z=1;
			z++; // scrifld(z++,fm_os15,"artikels");
			for(k=start_;k<max_art_;k++){
				fasinit(6); *u(6,1)=tb[k].rec; fasgeti(6);
				scrofld(z,6,3,-1);
				if(*(char *)&tb[k].aantal=='J') scrchat(z++,0x08); else scrchat(z++,0x00);
				scrifld(z,fm_uJN,&tb[k].aantal);
				if(*(char *)&tb[k].aantal=='J') scrchat(z++,0x02); else scrchat(z++,0x00);
				if(k==start_+17) break;
			}
			key=scrupd(curs,0x40B7);curs=1;curspos_=fldcurs;
			if(key==18 || key==9){/* pijl dn */
				curs=curspos_+1;  
				j=(curs-1)/2-1;
				if(j>=0){
					if(*(char *)&tb[k].aantal=='J') *(char *)&tb[k].aantal='N'; else *(char *)&tb[k].aantal='J';
				}
				goto redosel;
			}
			if(key==8){/* pijl up */
				curs=curspos_-2; if(curs<=1) curs=1;  goto redosel;
			}
			if(key==101) goto endsr;
			if(key==105) {for(k=0;k<max_art_;k++) *(char *)&tb[k].aantal='J';}
			if(key==106) {for(k=0;k<max_art_;k++) *(char *)&tb[k].aantal='N';}
			if(key==108) break;
			if(key==102) start_-=18;
			if(key==103) {start_+=18;if(start_>=max_art_) start_=max_art_-18;}
			if(start_<0) start_=0;
		}
	}
	if(fl_select_==NO && InqArt){
		tb[0].rec=InqArt; fl_select_=YES;*(char *)&tb[0].aantal='J'; max_art_=1;
	}
  scrget(1,7); scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(YES /* prt2pdf*/ ) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,96,pr_mode,4))!=0) return;

  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,29);
	zero(str_,sizeof str_);k=copy0("Verkochte promoties",str_,15); 	if(inq_kassa) {k+=copy0(" kassa",&str_[k],6);stcli_d(&str_[k],(long)(inq_kassa),3,1);}
	prttext("<t35b>");prttext(str_);
  prttext("<b><t65>");prtifld(fm_udat,&dat_beg,-1);
  prttext(" - ");prtifld(fm_udat,&dat_end,-1);
  prttext("<t88>");prttext("Blz.<ppp>.");
  prtbuf(1);z=1;
	if(fl_select_==NO || PrintTotaal!='J'){
    prtitab(z,fm_ou2,&kasnr,1,-1); prttitle(z++,"K",0x13);
    prtitab(z,fm_odat,&dt_,1,-1); prttitle(z++,"Datum",0x43);
    prtitab(z,fm_ou5,&tikketnr_,2,-1); prttitle(z++,"TickNr",0x13);
	}
	prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
	prttab(z,6,3,1,-1); prttitle(z++,"Omschrijving",3);
	prtitab(z,fm_uf5_0,&aantal_,1,-1); prttitle(z++,"Aantal",0x13);
	prtitab(z,VarTextFmt(3,0),st_txt_,1,-1); prttitle(z++,"",0x13);
	//prtitab(z,fm_uf5_2,&prx_n_,1,-1); if(type_prx_==sys3896[0]) prttitle(z++,"Normaal",0x13); else prttitle(z++,prx_str_,0x13);
	//prtitab(z,fm_uf5_2,&prx_k_,1,-1); prttitle(z++,"Kassa",0x13);
	if((fl_select_==NO || PrintTotaal!='J') && PrintPromo=='J'){
  	prtitab(z,VarTextFmt(18,0),promo_txt,1,-1); prttitle(z++,"Soort korting",3);
	  prtitab(z,fm_uf5_2,&bd_korting_,1,-1); prttitle(z++,"Tot.kort",0x13);
	}

  prtbuf(3);
	p_pdfname(str_,dat_beg,dat_end);
	redo_fullprint:;
	ClearTotalSums();tot_aantal_=0;tot_korting_=0;
  kasnr=1; max_=10; if(inq_kassa){kasnr=inq_kassa; max_=inq_kassa;}
  for(kasnr;kasnr<=max_;kasnr++){
    if(nm_kassa[kasnr-1][0]=='\0') continue;
	  for(dt_=dat_beg;dt_<=dat_end;dt_++){
			MakeKaslogName(kasnr,dt_);
			if(GetFileAttributes(filnam)==INVALID_FILE_ATTRIBUTES){
				if((sys4400 & 0x4)==0) errnum=1;
				continue;
			}
			if (!LogOpenKaslog(filnam)) continue;

			for (DagIx=0; DagIx<LogDagUsed; DagIx++) if(LogDag[DagIx].datum==dt_) break;
			if(DagIx>=LogDagUsed) {FilKaslog.Close();continue;}
			if (!LogSetDag(DagIx)) {FilKaslog.Close();continue;}
			unsigned TicketDatum=LogDag[DagIx].datum;
			int TicketCount=0; 
			while (LogReadNextTicket()) {
				int lines = Kasticket.LijnUsed;
				for(k=0;k<lines;k++){ // eerst kortingen % en EUR die op volgende lijn staan corrigeren op artkel
					if(k>0 && Kasticket.Lijn[k].code[0] && Kasticket.Lijn[k].aantal==0 && Kasticket.Lijn[k].totaal){
						for(j=1;j<=3;j++){ // tot 3 lijnen terug gaan om korting op juist artikel te zetten
							if((k-j)>=0 && cmpstr(Kasticket.Lijn[k-j].code,Kasticket.Lijn[k].code,fldlen(6,2))==0 && Kasticket.Lijn[k-j].groep==Kasticket.Lijn[k].groep) break;
						}
						if(j<=3) j=k-j; else j=-1;
						if(j>=0){
							Kasticket.Lijn[j].totaal+=Kasticket.Lijn[k].totaal;
							if(Kasticket.Lijn[j].aantal) Kasticket.Lijn[j].prijs=Kasticket.Lijn[j].totaal/ Kasticket.Lijn[j].aantal;
      			  SoortKorting[j]=SoortKorting[k];
							Kasticket.Lijn[k].code[0]='\0';
						}
					}
				}
				for(k=0;k<lines;k++){
					if(Kasticket.Lijn[k].code[0]){
						fasinit(6);copy(Kasticket.Lijn[k].code,s(6,2),fldlen(6,2));
						if(sys4408){*u(6,1)=val(s(6,2));	j=fasgeti(6);}
						else j=faskeyi(6,1,0);
						if(j==0 && fl_select_){
							for(nr_select_=0;nr_select_<max_art_;nr_select_++) if(tb[nr_select_].rec==*u(6,1) && *(char *)&tb[nr_select_].aantal=='J') break;
							if(nr_select_>=max_art_) j=1;
						}
						if(j==0 && *i(6,9)!=99 && (InqArt==0 || *u(6,1)==InqArt) && (InqLev==0 || *u(6,7)==InqLev || *u(6,101)==InqLev)){
							st_txt_[0]='\0'; zero(promo_txt,sizeof promo_txt);
							vpos_=0; if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_) vpos_=10;
							pnr_=PrNrs[type_prx_-'0'+vpos_]; if(Kasticket.Lijn[k].bits&1) {pnr_=PrNrs[tb_ktypes[max_kprx-1]+vpos_];copy("St",st_txt_,3);}
							
							prx_n_=*f(6,pnr_);
              if(!(sys3894 & (1<<(type_prx_-'0')))) prx_n_=Round((double)(prx_n_*(1.+*f(6,28)/100)),(double)(0.01));
							bd_dif_=prx_n_-Kasticket.Lijn[k].prijs; 
							pctkorting_=0; 
							if(SoortKorting[k]>0 && SoortKorting[k]<1000 ) pctkorting_=SoortKorting[k];
							else if(prx_n_) pctkorting_=Round((double)((bd_dif_/prx_n_)*100.),(double)(1.0)); 
							if(OnlyPromo!='J' || (Kasticket.Lijn[k].prijs==0 || (!is_nul((double)(bd_dif_)) && bd_dif_>0 && pctkorting_>=min_kortingpct_))){
								bd_korting_=bd_dif_*Kasticket.Lijn[k].aantal; bd_korting_=Round((double)(bd_korting_),(double)(0.01));
								bd_dif_=Round((double)(bd_dif_),(double)(0.01));zero(promo_txt,sizeof promo_txt);
								if(SoortKorting[k]>1000) sprintf_s(promo_txt,20,"%3.2f EUR korting",SoortKorting[k]-1000);
								else if(SoortKorting[k]>0) sprintf_s(promo_txt,20,"%3.2f %% korting",SoortKorting[k]);
								else if(Kasticket.Lijn[k].prijs==0) copy("Gratis",promo_txt,10);
								else if(!is_nul((double)(bd_dif_))) sprintf_s(promo_txt,20,"%3.2f EUR korting",bd_dif_);
								tikketnr_=Kasticket.TicketNr; prx_k_=Kasticket.Lijn[k].prijs; aantal_=Kasticket.Lijn[k].aantal;
								if(/*InqArt &&*/ Kasticket.Lijn[k].bits&1 && *f(6,31)>1) tot_aantal_+=aantal_/ *f(6,31); // herleiden naar kommagetal bij stuks
								else tot_aantal_+=aantal_;
								if(fl_select_ && nr_select_>=0 && nr_select_<max_art_){
									if(/*InqArt &&*/ Kasticket.Lijn[k].bits&1 && *f(6,31)>1) tb[nr_select_].VW+=aantal_/ *f(6,31); // herleiden naar kommagetal bij stuks
								  else tb[nr_select_].VW+=aantal_;
								}
								tot_korting_+=bd_korting_;
								if(fl_select_==NO || PrintTotaal!='J'){
  								for(j=1;j<20;j++) prtinfo(j,0); nextline();
								}
							}
						}
					}
				}
				TicketCount++;
			}
			FilKaslog.Close();
		}
  }
  if(tot_aantal_ || tot_korting_){
		kasnr=0;tikketnr_=0;dt_=0;st_txt_[0]='\0'; zero(promo_txt,sizeof promo_txt);zero(st_txt_,sizeof st_txt_);
		if(fl_select_){
			for(k=0;k<max_art_;k++){
				fasinit(6);*u(6,1)=tb[k].rec;fasgeti(6);
				MakeStksTxt(tb[k].VW,*f(6,31),&aantal_,st_txt_);
	//			aantal_=tb[k].VW;
				for(j=1;j<20;j++) prtinfo(j,0); nextline();
			}
		}
		if(InqArt){
			fasinit(6);*u(6,1)=InqArt;fasgeti(6);
			MakeStksTxt(tot_aantal_,*f(6,31),&aantal_,st_txt_);
		}
		else aantal_=tot_aantal_;
		fasinit(6);copy("Totaal ==>",s(6,3),15);
		bd_korting_=tot_korting_; 
		nextline(); for(j=1;j<20;j++) prtinfo(j,2); nextline();
	}

	prtclose();
	endsr:;
	fasunlck(-1);
}





static void MakeStksTxt(float aantal_,float qverp_,float *qbak_,char *st_txt_)
{
  long stk_;
	float add_;
						
  zero(st_txt_,5);
  if(qverp_<1) qverp_=1;
  *qbak_=(long)(aantal_); stk_=0;
	add_=0.49; if(aantal_<0) add_=-0.49;
  if(qverp_>1 && aantal_!=0){
    stk_=(long)(((aantal_- *qbak_) * qverp_)+add_);
  } else stk_=0;
  if(stk_>99) stk_/=10;
  if(stk_) *st_txt_='/'; stcli_d(st_txt_+1,stk_,2,1);
}




static void MakeKaslogName(int16 kasnr_,uint16 dt_)
{
	int16 pos_,jj,mm,dd;
	char fname_[20], str_[50];

	memset(str_,0,sizeof str_);pos_=0;
	if((sys4400 & 0x02)==0){ // jama-light op kassa
		copy("kassa-00",str_,8);stcli_d(&str_[6],(long)kasnr_,2,0);str_[8]=0x5C;pos_=9;
  }
	
  if((sys4400 & 0x01)){ // kaslog per dag
		if(dt_==0) dt_=*u(25,2);
		jddate(dt_,&jj,&mm,&dd); jj%=100;
		sprintf_s(&str_[pos_],15,"KL%02d%02d%02d.DAT",jj,mm,dd);
	}
	else if((sys4400 & 0x04)){// kaslog per maand
		if(dt_==0) dt_=*u(25,2);
		jddate(dt_,&jj,&mm,&dd); 
		sprintf_s(&str_[pos_],15,"KL%04d%02d.DAT",jj,mm);
	}
	else copy("kaslog.dat",&str_[pos_],10);
  mk_name(3936,str_);
}


static void KasVerslag(void)
{
	int j,k,kasnr,max_,DagIx,z,first_,key,curs=2,journl;
	int16 form_dat[8],pr_mode,prtnr;
	short int jj,mm,dd;
	uint16 dt_,ptd_,nummer_;
	char str_[100],TextOmschrijving[50],txt_div_[5][41];
	double bd_kol_[10],tot_kol_[10],bedrag_,btw_tot_,belastbt_,tot_leeg_,tot_bew_,tot_geld_;
	CString cstr_,knaam_,kcode_,betstring_;
	POSITION ix_tickets_;

	if(inq_kassa==0 && max_kassa==1) inq_kassa=1;
  if(dat_beg==0 && inq_kassa==1) dat_beg=dt_kvk[0]+1;
  if(dat_end==0) dat_end=dat_beg;
	bd_Fondsoverdracht=0;
	if(fldlen(66,11)){
		if(inq_fil==99) copy("DEPOT",nm_fil,6);
		else if(inq_fil>0 && inq_fil<=10 && fldlen(66,11+(inq_fil-1)*15) && nm_loc[inq_fil-1][0]) copy(nm_loc[inq_fil-1],nm_fil,6);
		else zero(nm_fil,sizeof nm_fil);
	}
  FOREVER{
    redo:;
    scrnum=0;scrget(3,3);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0290B");
		scraddpicto(1,0,76,22,4,2,514,0,0,"Extra opties"); 
		scraddpicto(2,0,72,22,4,2,583,0,0,"Maak PDF"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&inq_kassa);
		if(fldlen(66,11)){scrifld(-z,fm_uu2,&inq_fil);z++; scrifld(z++,fm_os6,nm_fil);}
		else z+=2;
		scrifld(z++,fm_ubd,&bd_Fondsoverdracht);
		for(k=0;k<10;k++) {
	  	if(nm_kassa[k][0]){
				scrifld(z++,fm_os6,&nm_kassa[k][0]);
				scrifld(z++,fm_odat,&dt_kvk[k]);
				fasclos(-2);fasinit(80);
				MakeKaslogName(k+1,dat_end);
				fasopen(filnam,102);/* eerste call voor dir */
				fasinfo(80,204);/* ophalen antwoord van dir */
				if(*s(80,1)){
					fasinit(80);fasinfo(80,205);/* get date  */
					scrifld(z++,fm_os20,s(80,1));
					fasclos(-2);
					if (LogOpenKaslog(filnam)){
					  scrifld(z++,fm_odat,&LogDag[0].datum);
						scrifld(z++,fm_odat,&LogDag[LogDagUsed-1].datum);
						FilKaslog.Close();
					} else z+=2;
				} else z+=3;
			} else z+=5;
    }
    key=scrupd(curs,0x181);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){KasverslagParameters();goto redo;} // extra opties
		if(key==5050) goto redo; // link help 
    if(inq_fil<0 || (inq_fil>10 && inq_fil!=99)) {zero(nm_fil,sizeof nm_fil);curs=5; errnum=34;goto redo;}
		if(inq_fil && inq_fil<=10){
			if(fldlen(66,11+(inq_fil-1)*15)==0) {errnum=34;curs=5; goto redo;}
			copy(nm_loc[inq_fil-1],nm_fil,6);
		}
		else if(inq_fil==99) copy("DEPOT",nm_fil,6);
		else zero(nm_fil,sizeof nm_fil);
    if(key==18){curs=fldcurs+1;goto redo;}
	  prt2pdf=NO; if(key==5002){prt2pdf=YES; key=108;} // pdf
    if(key==111) ovlexit(-1);
    if(key==101) return;
    if(dat_beg==0){curs=3;errnum=38;goto redo;}
    if(dat_end==0 || dat_end<dat_beg){curs=3;errnum=38;goto redo;}
//    if(only1kas && inq_kassa==0){curs=4;errnum=38;goto redo;}
    if(inq_kassa && fldlen(91,11+(inq_kassa-1)*5)==0){
      curs=4;errnum=34;goto redo;
    }
    if(key==108 || key==109) break;
  }
  if(dat_end==0) dat_end=0xFFFF;
	fasunlck(-2);
  scrget(1,7);
	ClearTotalSums();
  kasnr=1; max_=10; if(inq_kassa){kasnr=inq_kassa; max_=inq_kassa;}
  for(kasnr;kasnr<=max_;kasnr++){
    if(nm_kassa[kasnr-1][0]=='\0') continue;
		if(inq_kassa==0 && inq_fil){ // hoort ze bij dit filiaal
			if(loc_nr[kasnr-1]!=inq_fil) continue;
		}
	  for(dt_=dat_beg;dt_<=dat_end;dt_++){
			MakeKaslogName(kasnr,dt_);
			if(GetFileAttributes(filnam)==INVALID_FILE_ATTRIBUTES){continue;}
			if (!LogOpenKaslog(filnam)) continue;
			int TicketCount=0;DagIx=0;
			FOREVER{
				for (DagIx; DagIx<LogDagUsed; DagIx++) if(LogDag[DagIx].datum==dt_) break;
				if(DagIx>=LogDagUsed) {FilKaslog.Close();goto next_kas;}
				if (!LogSetDag(DagIx)) {FilKaslog.Close(); goto next_kas;}
				unsigned TicketDatum=LogDag[DagIx].datum;
				
				while (LogReadNextTicket()) {
					int lines = Kasticket.LijnUsed;
					TicketCount++;
				}
				DagIx++;
			}
			FilKaslog.Close();
			next_kas:;
		}
		
  }
  
  tot_bew_=0;tot_geld_=0;
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,96,pr_mode,2))!=0) return;

  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,29);
	zero(str_,sizeof str_);copy("Kasverslag",str_,10); 	
	if(inq_kassa) sprintf_s(&str_[10],30," kassa %02d %.6s",inq_kassa,nm_kassa[inq_kassa-1]);
	else if(inq_fil){sprintf_s(&str_[10],30," filiaal %02d %.6s",inq_fil,nm_fil);}
	prttext("<t35b>");prttext(str_);
  prttext("<b><t65>");prtifld(fm_udat,&dat_beg,-1);
  prttext(" - ");prtifld(fm_udat,&dat_end,-1);
  prttext("<t88>");prttext("Blz.<ppp>.");
  prtbuf(1);
	p_pdfname(str_,dat_beg,dat_end);
	prttext("<eub>Contante verkopen<eub>");nextline();nextline();
  memset(btw_bd,0,sizeof btw_bd);memset(btw_bas,0,sizeof btw_bas); btw_tot_=0; belastbt_=0;
  for(k=0;k<CUMBTW_COUNT;k++){ 
    if(BtwTot[k][1]){
			btw_bas[k]=Round((double)(BtwTot[k][1]/(1.+BtwPerc[k][1]/100.)),(double)(0.01));belastbt_+=btw_bas[k];
			btw_bd[k]=Round((double)(BtwTot[k][1]-btw_bas[k]),(double)(0.01));btw_tot_+=btw_bd[k];
    }
  }
	tot_leeg_=FinTot[4][1]-FinTot[22][1];
  for(j=0;j<4;j++){
    switch(j){
      case 0 : prttext("       "); break;
      case 1 : prttext("Basis  "); break;
      case 2 : prttext("Btw    "); break;
      default: prttext("<b>Totaal "); break;
    }
    for(k=0;k<CUMBTW_COUNT;k++){
      if(BtwTot[k][1]){
				if(j==0){
					if(k>3 && BtwPerc[k][1]==0){
				  	prttext("    <u>ex.BTW<u>");
					}
					else{
  					prttext("    <u>");prtifld(fm_od21_,&BtwPerc[k][1],-1);prttext(" %<u> ");
	    		}
				}
				else{
					if(j==1) bedrag_=btw_bas[k];
					if(j==2) bedrag_=btw_bd[k];
					if(j==3) bedrag_=BtwTot[k][1];
					prtifld(fm_obd,&bedrag_,-1);prtblank(1);
				}
      }
    }
    if(j==0){
      prttext("<t68>Leeggoed:");
      bedrag_=tot_leeg_;
    }
    else if(j==1){
      prttext("<t68>Goederen:");
      bedrag_=belastbt_;
    }
    else if(j==2){
      prttext("<t70>B.T.W.:");
      bedrag_=btw_tot_;
    }
    else {
      prttext("<t70>TOTAAL:");
      bedrag_=btw_tot_+belastbt_+tot_leeg_;tot_bew_+=bedrag_;
    }
    prttext("<t81>");prtifld(fm_obd,&bedrag_,-1);
    nextline();
  }
	nextline();

	ix_tickets_=FactuurTickets.GetHeadPosition();memset(tot_kol_,0,sizeof tot_kol_);first_=YES;
	for(k=0;k<FactuurTickets.GetCount()-5;k+=6){
		betstring_=CString("");
		for(j=0;j<6;j++){
			switch(j){
				case 0 : kcode_=FactuurTickets.GetAt(ix_tickets_); break;
				case 1 : knaam_=FactuurTickets.GetAt(ix_tickets_); break;
				case 2 : bd_kol_[0]=atof(FactuurTickets.GetAt(ix_tickets_)); break;
				case 3 : bd_kol_[1]=atof(FactuurTickets.GetAt(ix_tickets_)); break;
				case 4 : nummer_=atoi(FactuurTickets.GetAt(ix_tickets_)); break;
				case 5 : betstring_=FactuurTickets.GetAt(ix_tickets_); break;
				default : break;
			}
			FactuurTickets.GetNext(ix_tickets_);
		}
		if(bd_kol_[1]==0){
			if(first_){
				prttext("<eub>Voldane facturen<eub>");nextline();nextline();
				prttext("<bu>Klant<bu><t48bu>Ft.Nr.<bu><t62bu>Bedrag<bu><t84bu>Betaald<bu>");nextline();
				first_=NO;
			}
			prttext("<t1>");prtifld(fm_os40,(char *)(LPCTSTR)kcode_,6);
			prttext("<t8>");prtifld(fm_os40,(char *)(LPCTSTR)knaam_,40);
			prttext("<t48>");prtifld(fm_ou5,&nummer_,-1);
		  prttext("<t58>");prtifld(fm_obd,&bd_kol_[0],-1);
		  prttext("<t70>");prtifld(fm_obd,&bd_kol_[1],-1);
			prttext("<t81>");prtifld(fm_obd,&bd_kol_[0],-1);
			prttext("  ");prtifld(VarTextFmt(6,0),(char *)(LPCTSTR)betstring_,-1);
  		nextline();
			tot_kol_[0]+=bd_kol_[0];tot_kol_[1]+=bd_kol_[1];
		}
	}
	if(!first_){
		if(tot_kol_[0]){
			prttext("<b>Totaal ==>");
			prttext("<t58>");prtifld(fm_obd,&tot_kol_[0],-1);
			prttext("<t70>");prtifld(fm_obd,&tot_kol_[1],-1);
			prttext("<t81>");prtifld(fm_obd,&tot_kol_[0],-1);tot_bew_+=tot_kol_[0];
  		nextline();
		}
		nextline();
	}

	ix_tickets_=FactuurTickets.GetHeadPosition();memset(tot_kol_,0,sizeof tot_kol_);first_=YES;
	for(k=0;k<FactuurTickets.GetCount()-5;k+=6){
		betstring_=CString("");
		for(j=0;j<6;j++){
			switch(j){
				case 0 : kcode_=FactuurTickets.GetAt(ix_tickets_); break;
				case 1 : knaam_=FactuurTickets.GetAt(ix_tickets_); break;
				case 2 : bd_kol_[0]=atof(FactuurTickets.GetAt(ix_tickets_)); break;
				case 3 : bd_kol_[1]=atof(FactuurTickets.GetAt(ix_tickets_)); break;
				case 4 : nummer_=atoi(FactuurTickets.GetAt(ix_tickets_)); break;
        case 5 : betstring_=FactuurTickets.GetAt(ix_tickets_); break;
				default : break;
			}
			FactuurTickets.GetNext(ix_tickets_);
		}
		if(bd_kol_[1]!=0){
			if(first_){
				prttext("<eub>NIET-voldane facturen<eub>");nextline();nextline();
				prttext("<bu>Klant<bu><t48bu>Ft.Nr.<bu><t62bu>Bedrag<bu><t70bu>Te betalen<bu><t84bu>Betaald<bu>");nextline();
				first_=NO;
			}
			prttext("<t1>");prtifld(fm_os40,(char *)(LPCTSTR)kcode_,6);
			prttext("<t8>");prtifld(fm_os40,(char *)(LPCTSTR)knaam_,40);
			prttext("<t48>");prtifld(fm_ou5,&nummer_,-1);
		  prttext("<t58>");prtifld(fm_obd,&bd_kol_[0],-1);
		  prttext("<t70>");prtifld(fm_obd,&bd_kol_[1],-1);
			prttext("<t81>");bedrag_=bd_kol_[0]-bd_kol_[1];prtifld(fm_obd,&bedrag_,-1);
			prttext("  ");prtifld(VarTextFmt(6,0),(char *)(LPCTSTR)betstring_,-1);
  		nextline();
			tot_kol_[0]+=bd_kol_[0];tot_kol_[1]+=bd_kol_[1];
		}
	}
	if(!first_){
		if(tot_kol_[0]){
			prttext("<b>Totaal ==>");
			prttext("<t58>");prtifld(fm_obd,&tot_kol_[0],-1);
			prttext("<t70>");prtifld(fm_obd,&tot_kol_[1],-1);
			prttext("<t81>");bedrag_=tot_kol_[0]-tot_kol_[1];prtifld(fm_obd,&bedrag_,-1);tot_bew_+=bedrag_;
  		nextline();
		}
		nextline();
	}
	
	ix_tickets_=BonTickets.GetHeadPosition();memset(tot_kol_,0,sizeof tot_kol_);first_=YES;
	for(k=0;k<BonTickets.GetCount()-5;k+=6){
		betstring_=CString("");
		for(j=0;j<6;j++){
			switch(j){
				case 0 : kcode_=BonTickets.GetAt(ix_tickets_); break;
				case 1 : knaam_=BonTickets.GetAt(ix_tickets_); break;
				case 2 : bd_kol_[0]=atof(BonTickets.GetAt(ix_tickets_)); break;
				case 3 : bd_kol_[1]=atof(BonTickets.GetAt(ix_tickets_)); break;
				case 4 : nummer_=atoi(BonTickets.GetAt(ix_tickets_)); break;
				case 5 : betstring_=BonTickets.GetAt(ix_tickets_); break;
				default : break;
			}
			BonTickets.GetNext(ix_tickets_);
		}
		if(bd_kol_[1]==0){
			if(first_){
				prttext("<eub>Voldane bons<eub>");nextline();nextline();
				prttext("<bu>Klant<bu><t48bu>BonNr.<bu><t62bu>Bedrag<bu><t84bu>Betaald<bu>");nextline();
				first_=NO;
			}
			prttext("<t1>");prtifld(fm_os40,(char *)(LPCTSTR)kcode_,6);
			prttext("<t8>");prtifld(fm_os40,(char *)(LPCTSTR)knaam_,40);
			prttext("<t48>");prtifld(fm_ou5,&nummer_,-1);
		  prttext("<t58>");prtifld(fm_obd,&bd_kol_[0],-1);
		  prttext("<t70>");prtifld(fm_obd,&bd_kol_[1],-1);
			prttext("<t81>");prtifld(fm_obd,&bd_kol_[0],-1);
			prttext("  ");prtifld(VarTextFmt(6,0),(char *)(LPCTSTR)betstring_,-1);
  		nextline();
			tot_kol_[0]+=bd_kol_[0];tot_kol_[1]+=bd_kol_[1];
		}
	}
	if(!first_){
		if(tot_kol_[0]){
			prttext("<b>Totaal ==>");
			prttext("<t58>");prtifld(fm_obd,&tot_kol_[0],-1);
			prttext("<t70>");prtifld(fm_obd,&tot_kol_[1],-1);
			prttext("<t81>");prtifld(fm_obd,&tot_kol_[0],-1);tot_bew_+=tot_kol_[0];
  		nextline();
		}
		nextline();
	}

	ix_tickets_=BonTickets.GetHeadPosition();memset(tot_kol_,0,sizeof tot_kol_);first_=YES;
	for(k=0;k<BonTickets.GetCount()-5;k+=6){
		betstring_=CString("");
		for(j=0;j<6;j++){
			switch(j){
				case 0 : kcode_=BonTickets.GetAt(ix_tickets_); break;
				case 1 : knaam_=BonTickets.GetAt(ix_tickets_); break;
				case 2 : bd_kol_[0]=atof(BonTickets.GetAt(ix_tickets_)); break;
				case 3 : bd_kol_[1]=atof(BonTickets.GetAt(ix_tickets_)); break;
				case 4 : nummer_=atoi(BonTickets.GetAt(ix_tickets_)); break;
				case 5 : betstring_=BonTickets.GetAt(ix_tickets_); break;
				default : break;
			}
			BonTickets.GetNext(ix_tickets_);
		}
		if(bd_kol_[1]!=0){
			if(first_){
				prttext("<eub>NIET-voldane bons<eub>");nextline();nextline();
				prttext("<bu>Klant<bu><t48bu>BonNr.<bu><t62bu>Bedrag<bu><t70bu>Te betalen<bu><t84bu>Betaald<bu>");nextline();
				first_=NO;
			}
			prttext("<t1>");prtifld(fm_os40,(char *)(LPCTSTR)kcode_,6);
			prttext("<t8>");prtifld(fm_os40,(char *)(LPCTSTR)knaam_,40);
			prttext("<t48>");prtifld(fm_ou5,&nummer_,-1);
		  prttext("<t58>");prtifld(fm_obd,&bd_kol_[0],-1);
		  prttext("<t70>");prtifld(fm_obd,&bd_kol_[1],-1);
			prttext("<t81>");bedrag_=bd_kol_[0]-bd_kol_[1];prtifld(fm_obd,&bedrag_,-1);
			prttext("  ");prtifld(VarTextFmt(6,0),(char *)(LPCTSTR)betstring_,-1);
  		nextline();
			tot_kol_[0]+=bd_kol_[0];tot_kol_[1]+=bd_kol_[1];
		}
	}
	if(!first_){
		if(tot_kol_[0]){
			prttext("<b>Totaal ==>");
			prttext("<t58>");prtifld(fm_obd,&tot_kol_[0],-1);
			prttext("<t70>");prtifld(fm_obd,&tot_kol_[1],-1);
			prttext("<t81>");bedrag_=tot_kol_[0]-tot_kol_[1];prtifld(fm_obd,&bedrag_,-1);tot_bew_+=bedrag_;
  		nextline();
		}
		nextline();
	}

	if(FinTot[19][0]){
		prttext("<eub>Diverse uitgaven<eub>");nextline();nextline();
		prttext("<bu>Omschrijving<bu><t62bu>Bedrag<bu><t84bu>Betaald<bu>");nextline();
	  ix_tickets_=UitgaveTickets.GetHeadPosition();memset(tot_kol_,0,sizeof tot_kol_);first_=YES;
		for(k=0;k<UitgaveTickets.GetCount()-7;k+=8){
			memset(txt_div_,0,sizeof txt_div_);ptd_=0; betstring_=CString("");
			for(j=0;j<8;j++){
				switch(j){
					case 0 : cstr_=UitgaveTickets.GetAt(ix_tickets_); cstr_.Trim(); if(cstr_=="Reden :") cstr_="";
						       if(cstr_.GetLength()) sprintf_s(txt_div_[ptd_++],sizeof txt_div_[0],cstr_.Left(40)); 
					         break;
					case 1 : bd_kol_[0]=atof(UitgaveTickets.GetAt(ix_tickets_)); break;
					case 2 : bd_kol_[1]=atof(UitgaveTickets.GetAt(ix_tickets_)); break;
					case 3 :
					case 4 :
					case 5 :
					case 6 : cstr_=UitgaveTickets.GetAt(ix_tickets_); cstr_.Trim();
						       if(cstr_.GetLength()) sprintf_s(txt_div_[ptd_++],sizeof txt_div_[0],cstr_.Left(40)); 
						       break;
					case 7 : betstring_=UitgaveTickets.GetAt(ix_tickets_); break;
					default : break;
				}
				UitgaveTickets.GetNext(ix_tickets_);
			}
			memset(TextOmschrijving,0,sizeof TextOmschrijving);sprintf_s(TextOmschrijving,sizeof TextOmschrijving,cstr_);
			prttext(txt_div_[0]);// prttext(TextOmschrijving);
			prttext("<t58>");prtifld(fm_obd,&bd_kol_[0],-1);
			prttext("<t70>");prtifld(fm_obd,&bd_kol_[1],-1);
			prttext("<t81>");prtifld(fm_obd,&bd_kol_[0],-1);
			prttext("  ");prtifld(VarTextFmt(6,0),(char *)(LPCTSTR)betstring_,-1);
 			nextline();
			tot_kol_[0]+=bd_kol_[0];tot_kol_[1]+=bd_kol_[1];
			for(j=1;j<ptd_;j++){
				if(txt_div_[j][0]) { prttext(txt_div_[j]);nextline();}
			}
		}
		if(tot_kol_[0]){
			prttext("<b>Totaal ==>");
			prttext("<t58>");prtifld(fm_obd,&tot_kol_[0],-1);
			prttext("<t70>");prtifld(fm_obd,&tot_kol_[1],-1);
			prttext("<t81>");prtifld(fm_obd,&tot_kol_[0],-1);tot_bew_+=tot_kol_[0];
 			nextline();
		}
		nextline();
	}

	if(FinTot[20][0]){
		prttext("<eub>Diverse inkomsten<eub>");nextline();nextline();
		prttext("<bu>Omschrijving<bu><t62bu>Bedrag<bu><t84bu>Betaald<bu>");nextline();
	  ix_tickets_=InkomstTickets.GetHeadPosition();memset(tot_kol_,0,sizeof tot_kol_);first_=YES;
		for(k=0;k<InkomstTickets.GetCount()-7;k+=8){
			memset(txt_div_,0,sizeof txt_div_);ptd_=0; betstring_=CString(""); memset(bd_kol_,0,sizeof bd_kol_);
			for(j=0;j<8;j++){
				switch(j){
	  			case 0 : cstr_=InkomstTickets.GetAt(ix_tickets_);cstr_.Trim(); if(cstr_=="Reden :") cstr_="";
						       if(cstr_.GetLength()) sprintf_s(txt_div_[ptd_++],sizeof txt_div_[0],cstr_.Left(40)); 
						       break;
					case 1 : bd_kol_[0]=atof(InkomstTickets.GetAt(ix_tickets_)); break;
					case 2 : bd_kol_[1]=atof(InkomstTickets.GetAt(ix_tickets_)); break;
					case 3 :
					case 4 :
					case 5 :
					case 6 : cstr_=InkomstTickets.GetAt(ix_tickets_); cstr_.Trim();
						       if(cstr_.GetLength()) sprintf_s(txt_div_[ptd_++],sizeof txt_div_[0],cstr_.Left(40)); 
									 break;
					case 7 : betstring_=InkomstTickets.GetAt(ix_tickets_); break;
					default : break;
				}
				InkomstTickets.GetNext(ix_tickets_);
			}
			memset(TextOmschrijving,0,sizeof TextOmschrijving);sprintf_s(TextOmschrijving,sizeof TextOmschrijving,cstr_);
			prttext(txt_div_[0]);//prttext(TextOmschrijving);
			prttext("<t58>");prtifld(fm_obd,&bd_kol_[0],-1);
			prttext("<t70>");prtifld(fm_obd,&bd_kol_[1],-1);
			prttext("<t81>");prtifld(fm_obd,&bd_kol_[0],-1);
			prttext("  ");prtifld(VarTextFmt(6,0),(char *)(LPCTSTR)betstring_,-1);
 			nextline();
			for(j=1;j<ptd_;j++){
				if(txt_div_[j][0]) { prttext(txt_div_[j]);nextline();}
			}
			tot_kol_[0]+=bd_kol_[0];tot_kol_[1]+=bd_kol_[1];
		}
		if(tot_kol_[0]){
			prttext("<b>Totaal ==>");
			prttext("<t58>");prtifld(fm_obd,&tot_kol_[0],-1);
			prttext("<t70>");prtifld(fm_obd,&tot_kol_[1],-1);
			prttext("<t81>");prtifld(fm_obd,&tot_kol_[0],-1);tot_bew_+=tot_kol_[0];
 			nextline();
		}
		nextline();
	}
	if(bd_Fondsoverdracht){
		prttext("<eub>Storting bank<eub><t81b>");
		bedrag_=-bd_Fondsoverdracht;prtifld(fm_obd,&bedrag_,-1);tot_bew_+=bedrag_;
 		nextline();nextline();
	}

	memset(str_,'-',96);str_[96]=0;
	prttext(str_);nextline();
	prttext("<eb>Totaal bewegingen<eb><t81b>");prtifld(fm_obd,&tot_bew_,-1);nextline();
	prttext(str_);nextline();nextline();


	memset(tot_kol_,0,sizeof tot_kol_);
  prttext("<eub>Overzicht betaalmiddelen<eub>");nextline();nextline();
	prttext("<bu>Omschrijving<bu><t62bu>Bedrag<bu>");nextline();
	if(bd_Fondsoverdracht){
		prttext("Geld (storting bank)<t58>");
		bedrag_=-bd_Fondsoverdracht;prtifld(fm_obd,&bedrag_,-1);tot_geld_+=bedrag_;
 		nextline();
	}
 
  for(int Nr=0;Nr<40;Nr++){
		for(j=0;j<DIM_FINNRS;j++) if(Nr==FinNrs[j]) break; 
		if(j>=DIM_FINNRS && Nr!=25) continue; // uitzondering afronding
		if(Nr==10){ for(k=0;k<3;k++) bd_kol_[k]=FinTot[Nr][k]-FinTot[2][k];} // geld - geld terug
		else if(Nr==14){ for(k=0;k<3;k++) bd_kol_[k]=-FinTot[Nr][k];} // eigen tegoedbon=negatief
		else if(Nr==15){ for(k=0;k<3;k++) bd_kol_[k]=-FinTot[Nr][k];} // leveranciersbon=negatief
		else{for(k=0;k<3;k++) bd_kol_[k]=FinTot[Nr][k];}
		if(bd_kol_[0]==0) continue;
		memset(TextOmschrijving,0,sizeof TextOmschrijving);
		prtifld(fm_us30,FinGroepNaam[Nr],-1);
		//prttext("<t55>");prtifld(fm_obd,&bd_kol_[1],-1);
		//prttext("<t65>");prtifld(fm_obd,&bd_kol_[2],-1);
		prttext("<t58>");prtifld(fm_obd,&bd_kol_[0],-1);
    nextline();
		for(k=0;k<3;k++) tot_kol_[k]+=bd_kol_[k];
		tot_geld_+=bd_kol_[0];
	}
  nextline();

	memset(str_,'-',96);str_[96]=0;
	prttext(str_);nextline();
	prttext("<eb>Totaal ontvangsten<eb><t81b>");prtifld(fm_obd,&tot_geld_,-1);nextline();
	prttext(str_);nextline();

	nextline();
	prttext("<b>Aantal klanten:");prtifld(fm_ou4,&TotaalAantalTickets,-1); 
	if(TotaalAantalTickets) bedrag_=TotaalBedragTickets/TotaalAantalTickets; else bedrag_=0;
	prttext("    Gem.bedrag/klant:");prtifld(fm_od4_2,&bedrag_,-1); prttext(" EUR");
	nextline();
	
	prtclose();
	//if(inq_kassa) journl=KV_KasJournaal[inq_kassa-1]; 
	//else{
	kasnr=1; max_=10; journl=0; if(inq_kassa){kasnr=inq_kassa; max_=inq_kassa;}
	for(kasnr;kasnr<=max_;kasnr++){
		if(nm_kassa[kasnr-1][0]=='\0') continue;
		if(inq_kassa==0 && inq_fil){ // hoort ze bij dit filiaal
			if(loc_nr[kasnr-1]!=inq_fil) continue;
		}	
  	journl=KV_KasJournaal[kasnr-1]; 
		break;
	}
	if(KV_ToonBoekscherm=='J' && journl) BoekKasverslag();
	fasunlck(-1);
}

static void BoekKasverslag(void)
{
  int16 curs=1,j,key,k,n,ix_,rec_,z,start_=0,z_base,err_pos_=0,curspos_,stu_,jj,mm,dd,dsp_start_,dsp_end_,kasnr,max_;
	uint16 bkh_dt,volgnr,journl,nummer_;
	long rekenc;
	double belastbt_=0,btw_tot_=0,tot_leeg_=0,bd_,tot_saldo,tot_bew,tot_geld,bd_tot_,bd_open_,tot_vfacturen_=0,tot_vbons_=0;
  char *pdum,dumm_[10];
	int d_lin_scr=15;
	CString kcode_,knaam_,cstr_,betstring_;
	POSITION ix_tickets_;
	
	uint16 kastype,osalkasa;
	long grb_kas;
	double osalkas;
	
	bkh_dt=dat_end;jddate(bkh_dt,&jj,&mm,&dd);
  volgnr=mm*100+dd;
	volgnr*=10; if(inq_kassa<10) volgnr+=inq_kassa; //mmddk (k=kassaNr, 0 indien geen selectie)
	kasnr=1; max_=10; journl=0; if(inq_kassa){kasnr=inq_kassa; max_=inq_kassa;}
	for(kasnr;kasnr<=max_;kasnr++){
		if(nm_kassa[kasnr-1][0]=='\0') continue;
		if(inq_kassa==0 && inq_fil){ // hoort ze bij dit filiaal
			if(loc_nr[kasnr-1]!=inq_fil) continue;
		}	
  	journl=KV_KasJournaal[kasnr-1]; 
		break;
	}



	//if(inq_kassa) journl=KV_KasJournaal[inq_kassa-1]; 
	//else if(inq_fil){
	//	for(k=0;k<10;k++) if(loc_nr[k]==inq_fil) break;
	//	if(k<10) journl=KV_KasJournaal[k]; 
	//	else journl=KV_KasJournaal[0]; 
	//}
	//else journl=KV_KasJournaal[0]; 
	
  for(k=0;k<80;k++){
    sysget(10240+k*80,2,&j); if(j==journl)break;
  }
	if(k==80){errnum=7;return;}
  sysget(10242+k*80,2,&kastype);if(kastype<3 && kastype>4){errnum=7;return;}
  osalkasa=10287+k*80; sysget(osalkasa,8,&osalkas);
  sysget(10262+k*80,4,&grb_kas);
	
  pdum=&dumm_[0];ix_=0;

  for(k=0;k<CUMBTW_COUNT;k++){ 
    if(BtwTot[k][1]){
			btw_bas[k]=Round((double)(BtwTot[k][1]/(1.+BtwPerc[k][1]/100.)),(double)(0.01));belastbt_+=btw_bas[k];
			btw_bd[k]=BtwTot[k][1]-btw_bas[k];btw_tot_+=btw_bd[k];
    }
  }
	tot_leeg_=Round(FinTot[4][1]-FinTot[22][1],(double)(0.01));
	bd_=0;
	for(k=0;k<DIM_BEWEGING;k++){
		if(KVBoekTabel[ix_].recnr==0) break;
		KVBoekTabel[ix_].bedrag=Round((double)(KVBoekTabel[ix_].bedrag),(double)(0.01));
		bd_+=KVBoekTabel[ix_].bedrag;ix_++;
	}
	if(!is_nul(bd_-belastbt_)) KVBoekTabel[0].bedrag+=bd_-belastbt_; // verschil op 1-ste boeking zetten
	if(tot_leeg_){
	  rekenc=*(long *)&df_grb[12][0];rec_=getgrb(rekenc);
		if(ix_<DIM_BEWEGING){
			KVBoekTabel[ix_].bedrag=tot_leeg_;
			KVBoekTabel[ix_].type='G';if(rec_!=60000) KVBoekTabel[ix_].recnr=rec_;
			copy(s(3,3),KVBoekTabel[ix_].naam,fldlen(3,3));
		}
		ix_++;
	}
	if(btw_tot_){
	  rekenc=*(long *)&df_grb[1][0];rec_=getgrb(rekenc);
		if(ix_<DIM_BEWEGING){
			KVBoekTabel[ix_].bedrag=btw_tot_;
			KVBoekTabel[ix_].type='G';if(rec_!=60000) KVBoekTabel[ix_].recnr=rec_;
			copy(s(3,3),KVBoekTabel[ix_].naam,fldlen(3,3));

		}
		ix_++;
	}
  // totaal voldane facturen apart bijhouden (zijn al afgeboekt op klant)
	ix_tickets_=FactuurTickets.GetHeadPosition();
	for(k=0;k<FactuurTickets.GetCount()-5;k+=6){
		bd_tot_=0;bd_open_=0;nummer_=0; betstring_=CString("");
		for(j=0;j<6;j++){
			switch(j){
				case 0 : kcode_=FactuurTickets.GetAt(ix_tickets_); break;
				case 1 : knaam_=FactuurTickets.GetAt(ix_tickets_); break;
				case 2 : bd_tot_=atof(FactuurTickets.GetAt(ix_tickets_)); break;
				case 3 : bd_open_=atof(FactuurTickets.GetAt(ix_tickets_)); break;
				case 4 : nummer_=atoi(FactuurTickets.GetAt(ix_tickets_)); break;
				case 5 : betstring_=FactuurTickets.GetAt(ix_tickets_); break;
				default : break;
			}

			FactuurTickets.GetNext(ix_tickets_);
		}
		if(KV_BoekVoldaneFactuurOpKlant!='J'){
			bd_=bd_tot_-bd_open_;
		  if(!is_nul(bd_)) tot_vfacturen_+=bd_; // betaalde bedragen aftrekken
		}
		else{ // individueel op klant boeken
			bd_=bd_tot_-bd_open_;if(is_nul(bd_)) continue; // niets betaald
			fasinit(2);
			if(kcode_.GetLength()) {*s(2,3)='.';copy0((char *)(LPCTSTR)kcode_,s(2,3)+1,10);}
			else copy0((char *)(LPCTSTR)knaam_,s(2,3),fldlen(2,3));
			search(2,0);
			if(ix_<DIM_BEWEGING){
				KVBoekTabel[ix_].bedrag=bd_;
				KVBoekTabel[ix_].type='K';if(*u(2,1)) KVBoekTabel[ix_].recnr=*u(2,1)+30000;
				copy(s(2,3),KVBoekTabel[ix_].naam,fldlen(2,3));
				KVBoekTabel[ix_].docnr=nummer_;
			}
			ix_++;
		}
	}

	// betalingen bons 

	ix_tickets_=BonTickets.GetHeadPosition();
	for(k=0;k<BonTickets.GetCount()-5;k+=6){
		bd_tot_=0;bd_open_=0; betstring_=CString("");
		for(j=0;j<6;j++){
			switch(j){
				case 0 : kcode_=BonTickets.GetAt(ix_tickets_); break;
				case 1 : knaam_=BonTickets.GetAt(ix_tickets_); break;
				case 2 : bd_tot_=atof(BonTickets.GetAt(ix_tickets_)); break;
				case 3 : bd_open_=atof(BonTickets.GetAt(ix_tickets_)); break;
				case 4 : nummer_=atoi(BonTickets.GetAt(ix_tickets_)); break;
				case 5 : betstring_=BonTickets.GetAt(ix_tickets_); break;
				default : break;
			}
			BonTickets.GetNext(ix_tickets_);
		}
		if(KV_BoekVoldaneFactuurOpKlant!='J'){
			bd_=bd_tot_-bd_open_;
		  if(!is_nul(bd_)) tot_vbons_+=bd_; // betaalde bedragen aftrekken
		}
		else{ // individueel op klant boeken
			bd_=bd_tot_-bd_open_;if(is_nul(bd_)) continue; // niets betaald
			fasinit(2);
			if(kcode_.GetLength()) copy0((char *)(LPCTSTR)kcode_,s(2,3),10);
			else copy0((char *)(LPCTSTR)knaam_,s(2,3),fldlen(2,3));
			search(2,0);
			if(ix_<DIM_BEWEGING){
				KVBoekTabel[ix_].bedrag=bd_;
				KVBoekTabel[ix_].type='K';if(*u(2,1)) KVBoekTabel[ix_].recnr=*u(2,1)+30000;
				copy(s(2,3),KVBoekTabel[ix_].naam,fldlen(2,3));
				sprintf(KVBoekTabel[ix_].opmerking,"Bon %d",nummer_);
			}
			ix_++;
		}
	}
	if(FinTot[19][0]){ // diverse uitgaven 
	  ix_tickets_=UitgaveTickets.GetHeadPosition();
		for(k=0;k<UitgaveTickets.GetCount()-7;k+=8){
			knaam_=""; betstring_=CString("");
			for(j=0;j<8;j++){
				switch(j){
					case 0 : cstr_=UitgaveTickets.GetAt(ix_tickets_); cstr_.Trim(); if(cstr_=="Reden :") cstr_="";
						       if(cstr_.GetLength()) knaam_+=cstr_;
					         break;
					case 1 : bd_tot_=atof(UitgaveTickets.GetAt(ix_tickets_)); break;
					case 2 : bd_open_=atof(UitgaveTickets.GetAt(ix_tickets_)); break;
					case 3 :
					case 4 :
					case 5 :
					case 6 : cstr_=UitgaveTickets.GetAt(ix_tickets_); cstr_.Trim();
						       if(cstr_.GetLength()) knaam_+=" "+cstr_;
						       break;
					case 7 : betstring_=UitgaveTickets.GetAt(ix_tickets_); break;
					default : break;
				}
				UitgaveTickets.GetNext(ix_tickets_);
			}
			if(is_nul(bd_tot_)) continue;
			if(ix_<DIM_BEWEGING){
			  KVBoekTabel[ix_].bedrag=bd_tot_;
				copy0("Uitgave",KVBoekTabel[ix_].naam,sizeof KVBoekTabel[0].naam);
				copy0((char *)(LPCTSTR)knaam_,KVBoekTabel[ix_].opmerking,sizeof KVBoekTabel[0].opmerking);
  		}
	  	ix_++;
		}
	}
	if(FinTot[20][0]){ // diverse inkomsten 
	  ix_tickets_=InkomstTickets.GetHeadPosition();
		for(k=0;k<InkomstTickets.GetCount()-7;k+=8){
			knaam_=""; betstring_=CString("");
			for(j=0;j<8;j++){
				switch(j){
					case 0 : cstr_=InkomstTickets.GetAt(ix_tickets_); cstr_.Trim(); if(cstr_=="Reden :") cstr_="";
									 if(cstr_.GetLength()) knaam_+=cstr_;
									 break;
					case 1 : bd_tot_=atof(InkomstTickets.GetAt(ix_tickets_)); break;
					case 2 : bd_open_=atof(InkomstTickets.GetAt(ix_tickets_)); break;
					case 3 :
					case 4 :
					case 5 :
					case 6 : cstr_=InkomstTickets.GetAt(ix_tickets_); cstr_.Trim();
						       if(cstr_.GetLength()) knaam_+=" "+cstr_;
						       break;						
					case 7 : betstring_=InkomstTickets.GetAt(ix_tickets_); break;

					default : break;
				}
				InkomstTickets.GetNext(ix_tickets_);
			}
			if(is_nul(bd_tot_)) continue;
			if(ix_<DIM_BEWEGING){
			  KVBoekTabel[ix_].bedrag=bd_tot_;
				copy0("Inkomst",KVBoekTabel[ix_].naam,sizeof KVBoekTabel[0].naam);
				copy0((char *)(LPCTSTR)knaam_,KVBoekTabel[ix_].opmerking,sizeof KVBoekTabel[0].opmerking);
  		}
	  	ix_++;
		}
	}
	if(bd_Fondsoverdracht){
    fasinit(3);*l(3,2)=KV_GrbFondsoverdracht;faskeyi(3,1,0);
		if(ix_<DIM_BEWEGING){
		  KVBoekTabel[ix_].bedrag=-bd_Fondsoverdracht;
  		KVBoekTabel[ix_].type='G';if(*u(3,1)) KVBoekTabel[ix_].recnr=*u(3,1)+60000;
		  copy(s(3,3),KVBoekTabel[ix_].naam,fldlen(3,3));
			copy("Fondsoverdracht",KVBoekTabel[ix_].opmerking,20);
		}
		ix_++;
	}

	ix_=DIM_BEWEGING; // geld zit op +200

	if(bd_Fondsoverdracht){ // dit gedeelte geld apart zetten
		fasinit(3);*l(3,2)=grb_kas;faskeyi(3,1,0); // geld direct op kasrekening zetten
		if(ix_<DIM_BEWEGING+DIM_FINANCIEEL){
		  KVBoekTabel[ix_].bedrag=-bd_Fondsoverdracht;
  		KVBoekTabel[ix_].type='G';if(*u(3,1)) KVBoekTabel[ix_].recnr=*u(3,1)+60000;
		  copy(s(3,3),KVBoekTabel[ix_].naam,fldlen(3,3));
			copy("Fondsoverdracht",KVBoekTabel[ix_].opmerking,20);
		}
		ix_++;
	}
	for(int Nr=0;Nr<40;Nr++){ // geldbewegingen 
		for(j=0;j<DIM_FINNRS;j++) if(Nr==FinNrs[j]) break; if(j>=DIM_FINNRS && Nr!=25) continue;
		if(Nr==10){ bd_=FinTot[Nr][0]-FinTot[2][0];} // geld - geld terug
		else if(Nr==14 || Nr==15){ bd_=-FinTot[Nr][0];} // eigen tegoedbon en leveranciersbon   = negatief
		else bd_=FinTot[Nr][0];
		if(!is_nul(bd_)){
			fasinit(3);
			if(Nr==10) *l(3,2)=grb_kas; 
			else if(Nr==25) *l(3,2)=KV_GrbAfrondingsverschillen; 
			else *l(3,2)=KV_GrbFinDet[j];
			faskeyi(3,1,0); // geld direct op kasrekening zetten
			if(ix_<DIM_BEWEGING+DIM_FINANCIEEL){
				KVBoekTabel[ix_].bedrag=bd_;
  			KVBoekTabel[ix_].type='G';if(*u(3,1)) KVBoekTabel[ix_].recnr=*u(3,1)+60000;
				copy(s(3,3),KVBoekTabel[ix_].naam,fldlen(3,3));
			}
			ix_++;
		}
		if(Nr==10 && KV_BoekVoldaneFactuurOpKlant!='J' && (!is_nul(tot_vfacturen_) || !is_nul(tot_vbons_))){ // het totaal van de voldane facturen negatief zetten omdat deze al afgeboekt zijn
      if(!is_nul(tot_vfacturen_)){
				fasinit(3); *l(3,2)=grb_kas;faskeyi(3,1,0); // direct van kasrekening aftrekken
				if(ix_<DIM_BEWEGING+DIM_FINANCIEEL){
					KVBoekTabel[ix_].bedrag=-tot_vfacturen_;
  				KVBoekTabel[ix_].type='G';if(*u(3,1)) KVBoekTabel[ix_].recnr=*u(3,1)+60000;
					copy(s(3,3),KVBoekTabel[ix_].naam,fldlen(3,3));
					copy("Voldane facturen",KVBoekTabel[ix_].opmerking,20);
				}
				ix_++;
			}
      if(!is_nul(tot_vbons_)){
				fasinit(3); *l(3,2)=grb_kas;faskeyi(3,1,0); // direct van kasrekening aftrekken
				if(ix_<DIM_BEWEGING+DIM_FINANCIEEL){
					KVBoekTabel[ix_].bedrag=-tot_vbons_;
  				KVBoekTabel[ix_].type='G';if(*u(3,1)) KVBoekTabel[ix_].recnr=*u(3,1)+60000;
					copy(s(3,3),KVBoekTabel[ix_].naam,fldlen(3,3));
					copy("Voldane lev.bons",KVBoekTabel[ix_].opmerking,20);
				}
				ix_++;
			}
		}
	}

	tot_saldo=0;tot_bew=0;tot_geld=0;
	for(k=0;k<DIM_BEWEGING+DIM_FINANCIEEL;k++) {
		if(KVBoekTabel[k].recnr) KVBoekTabel[k].hashval=hash(&KVBoekTabel[k].type,sizeof KVBoekTabel[0].naam);
		if(k<DIM_BEWEGING) tot_bew+=KVBoekTabel[k].bedrag; else tot_geld+=KVBoekTabel[k].bedrag;
	}
	tot_saldo=tot_bew-tot_geld;
  if(tot_saldo>=-0.1 && tot_saldo<=0.1){// klein afrondingsverschil op 1-ste boeking zetten
		KVBoekTabel[0].bedrag-=tot_saldo; tot_bew-=tot_saldo; tot_saldo=0;
	}
  scrnum=0;dsp_start_=0;dsp_end_=DIM_BEWEGING;start_=dsp_start_;
  FOREVER{
    redo:
    scrget(3,5);z=1;
    scrifld(z++,fm_odat,&dat_beg);scrifld(z++,fm_odat,&dat_end);
    scrifld(z++,fm_odat,&bkh_dt);  
		scrifld(z++,fm_ou2,&journl);scrifld(z++,fm_ou5,&volgnr);
    scrifld(z++,fm_obd,&tot_bew);scrifld(z++,fm_obd,&tot_geld);scrifld(z++,fm_obd,&tot_saldo);
    if(dsp_start_==0) scrifld(z++,fm_os11,"Bewegingen"); else scrifld(z++,fm_os11,"Ontvangsten");
    z_base=z;
    for(j=start_;j<(start_+d_lin_scr);j++){
      n=j-dsp_start_+1; scrifld(z++,fm_ou3,&n); 
			scrifld(z++,fm_ubd,&KVBoekTabel[j].bedrag);
			scrifld(z++,fm_uLKG,&KVBoekTabel[j].type);
			scrifld(z++,fm_us40,KVBoekTabel[j].naam);
			scrifld(z++,fm_os20,KVBoekTabel[j].opmerking);
    }
    key=scrupd(curs,0xFE);curs=1;curspos_=fldcurs;
    if(key==106){
      if(scr_ok("Wenst U echt de boeking te annuleren ???")==YES) goto endsr;
    }
    for(k=start_;k<(start_+d_lin_scr);k++){
			if(KVBoekTabel[k].bedrag==0){
				memset((char *)&KVBoekTabel[k].bedrag,0,sizeof KVBoekTabel[0]);
				continue;
			}
			if(KVBoekTabel[k].recnr==0 || KVBoekTabel[k].type=='\0' || KVBoekTabel[k].naam[0]=='\0'
				|| KVBoekTabel[k].hashval!=hash(&KVBoekTabel[k].type,sizeof KVBoekTabel[0].naam)){
				switch(KVBoekTabel[k].type){
					case 'L' : stu_=1;break;
					case 'K' : stu_=2;break;
					case 'G' : stu_=3;break;
					default  : stu_=0;break;
				}
				if(stu_==0){errnum=34;curs=z_base+2+(k-start_)*5;goto redo;}

				fasinit(stu_);copy(KVBoekTabel[k].naam,s(stu_,3),fldlen(stu_,3));
				if(search(stu_,0)){errnum=39;curs=z_base+3+(k-start_)*5;goto redo;}
				copy(s(stu_,3),KVBoekTabel[k].naam,fldlen(stu_,3));KVBoekTabel[k].recnr=(stu_-1)*30000+*u(stu_,1);
				KVBoekTabel[k].hashval=hash(&KVBoekTabel[k].type,sizeof KVBoekTabel[0].naam);
			}
    }
		tot_saldo=0;tot_bew=0;tot_geld=0;
	  for(k=0;k<DIM_BEWEGING+DIM_FINANCIEEL;k++) {
  		if(KVBoekTabel[k].recnr) KVBoekTabel[k].hashval=hash(&KVBoekTabel[k].type,sizeof KVBoekTabel[0].naam);
  		if(k<DIM_BEWEGING) tot_bew+=KVBoekTabel[k].bedrag; else tot_geld+=KVBoekTabel[k].bedrag;
  	}
		tot_saldo=tot_bew-tot_geld;
    if(key==108){
      for(k=0;k<DIM_BEWEGING+DIM_FINANCIEEL;k++){ // totale controle doen 
				if(KVBoekTabel[k].bedrag==0){
					memset((char *)&KVBoekTabel[k].bedrag,0,sizeof KVBoekTabel[0]);
					continue;
				}
				if(KVBoekTabel[k].recnr==0 || KVBoekTabel[k].type=='\0' || KVBoekTabel[k].naam[0]=='\0'
					|| KVBoekTabel[k].hashval!=hash(&KVBoekTabel[k].type,sizeof KVBoekTabel[0].naam)){
					switch(KVBoekTabel[k].type){
						case 'L' : stu_=1;break;
						case 'K' : stu_=2;break;
						case 'G' : stu_=3;break;
						default  : stu_=0;break;
					}
					start_=k/d_lin_scr;// scherm juistzetten op foute lijn
					if(start_<DIM_BEWEGING ){dsp_start_=0;dsp_end_=DIM_BEWEGING;}
					else {dsp_start_=DIM_BEWEGING;dsp_end_=DIM_BEWEGING+DIM_FINANCIEEL;}
          if(start_>(dsp_end_-d_lin_scr)) start_=dsp_end_-d_lin_scr;
					if(stu_==0){errnum=34;curs=z_base+2+(k-start_)*5;goto redo;}

					fasinit(stu_);copy(KVBoekTabel[k].naam,s(stu_,3),fldlen(stu_,3));
					if(search(stu_,0)){errnum=39;curs=z_base+3+(k-start_)*5;goto redo;}
					copy(s(stu_,3),KVBoekTabel[k].naam,fldlen(stu_,3));KVBoekTabel[k].recnr=(stu_-1)*30000+*u(stu_,1);
					KVBoekTabel[k].hashval=hash(&KVBoekTabel[k].type,sizeof KVBoekTabel[0].naam);
				}
			}

      if(!is_nul(tot_saldo)) errnum=10;
      else{
      	if(scr_ok("Wenst U echt dit kasverslag te boeken ???")==YES) break;
				else goto endsr;
      }
    }
		if(key==104){
			if(dsp_start_==0){dsp_start_=DIM_BEWEGING;dsp_end_=DIM_BEWEGING+DIM_FINANCIEEL;start_=dsp_start_;}
			else{dsp_start_=0;dsp_end_=DIM_BEWEGING;start_=dsp_start_;}
		}
    if(key==102) {start_-=d_lin_scr; if(start_<dsp_start_) start_=dsp_start_;}
    if(key==103) start_+=d_lin_scr;
    if(start_>(dsp_end_-d_lin_scr)) start_=dsp_end_-d_lin_scr;
    j=0;
		for(k=0;k<d_lin_scr;k++){if(KVBoekTabel[k+start_].bedrag==0) {j=k;break;}}
    curs=z_base+j*4;
  }

	fasinit(4);*s(4,2)=journl;*u(4,3)=volgnr;j=1;k=0;
  FOREVER{
    if(faskeyi(4,1,j)) break; j=2;
		if(*s(4,2)!=journl || *u(4,3)!=volgnr) break;
		if(*u(4,4)==bkh_dt) {k=1;break;}
	}
	if(k){
		if(DisplayWarning("Deze lijst is al geboekt! Wenst U deze te vervangen?",605)!=YES) goto endsr;
	}
	// eerst oude boeking schrappen 

 
	fasunlck(-2);
  scrget(1,7);scrupd(-3,0);
	jddate(bkh_dt,&jj,&mm,&dd);
  fasinit(4);*s(4,2)=journl;*u(4,3)=volgnr;j=1;bd_=0;
  FOREVER{
    if(faskeyi(4,1,j)) break; j=2;
		if(*s(4,2)!=journl || *u(4,3)!=volgnr) break;
		if(*u(4,4)==bkh_dt){
			if(*l(4,6)==grb_kas) bd_+=*d(4,32); // kasbedrag bijhouden om saldo te corrigeren 
			faskill(4);
		}
	}
  if(bd_){
		sysget(osalkasa,8,&osalkas);osalkas-=bd_;	sysput(osalkasa,8,&osalkas); // kassaldo bijwerken
	}
	sysget(osalkasa,8,&osalkas);
	for(k=0;k<DIM_BEWEGING+DIM_FINANCIEEL;k++){
		if(is_nul(KVBoekTabel[k].bedrag)) continue;
    fasinit(4); *s(4,2)=journl;*u(4,3)=volgnr;*u(4,4)=bkh_dt;
		*u(4,5)=KVBoekTabel[k].recnr;
		switch(KVBoekTabel[k].type){
			case 'L' : *l(4,6)=levcent;break;
			case 'K' : *l(4,6)=kltcent;
									if(KVBoekTabel[k].docnr){
										*s(4,8)=jj%100; if(*s(4,8)<50) *s(4,8)+=100;           /* y2000 */
										*s(4,9)=VKjournl;
										*u(4,10)=KVBoekTabel[k].docnr;
									}
									break;
			default  : fasinit(3);*u(3,1)=*u(4,5)-60000; fasgeti(3); *l(4,6)=*l(3,2);break;
		}
		bd_=KVBoekTabel[k].bedrag; if(k<DIM_BEWEGING) bd_=-bd_; // geld debet boeken
		*l(4,7)=bd_; *d(4,32)=bd_;
		if(*l(4,6)==grb_kas) osalkas+=bd_;
		*s(4,31)='E';
		copy(KVBoekTabel[k].opmerking,s(4,28),fldlen(4,28));
    errnum=fasadd(4);
  }
	sysput(osalkasa,8,&osalkas); // kassaldo bijwerken
  fasflush(0);fasunlck(-1);
  endsr:;
}

 
static void KasverslagParameters(void)
{
  int16 curs=1,k,key,z,start_;
  char nm_grb[20][30],nm_fogrb[30],nm_rndgrb[30];
	
	if(sys1804==0) return; // voorlopig enkel bkh-parameters

  sysget(18500,1,&KV_ExtraScherm); // voorlopig niet gebruikt
	sysget(18501,1,&KV_ToonBoekscherm);
	sysget(18502,1,&KV_BoekVoldaneFactuurOpKlant);
	sysget(18503,6,KV_AfwijkendeGrbPrefix);
	sysget(18510,20,KV_KasJournaal);
  sysget(18530,80,KV_GrbFinDet);
	sysget(18610,4,&KV_GrbFondsoverdracht);
	sysget(18614,4,&KV_GrbAfrondingsverschillen);
  memset(nm_grb,0,sizeof nm_grb);memset(nm_fogrb,0,sizeof nm_fogrb);memset(nm_rndgrb,0,sizeof nm_rndgrb);
	if(fldlen(3,0)){
		if(KV_GrbFondsoverdracht){
			fasinit(3);*l(3,2)=KV_GrbFondsoverdracht;faskeyi(3,1,0);
			copy(s(3,3),nm_fogrb,fldlen(3,3));
		}
		if(KV_GrbAfrondingsverschillen){
			fasinit(3);*l(3,2)=KV_GrbAfrondingsverschillen;faskeyi(3,1,0);
			copy(s(3,3),nm_rndgrb,fldlen(3,3));
		}
		for(k=0;k<20;k++){
			if(KV_GrbFinDet[k]){
				fasinit(3);*l(3,2)=KV_GrbFinDet[k];faskeyi(3,1,0);
				copy(s(3,3),nm_grb[k],fldlen(3,3));
			}
		}
	}
	start_=0;
	FOREVER{
    redo:;
    scrnum=0;scrget(3,4);z=1;
		z++; // scrifld(z++,fm_uJN,&KV_ExtraScherm); // voorlopig niet gebruikt
		if(sys1804){ // enkel indien boekhouding 
			scrifld(z++,fm_uJN,&KV_ToonBoekscherm);
			for(k=0;k<10;k++){
				if(nm_kassa[k][0]) scrifld(z++,fm_uu2,&KV_KasJournaal[k]); else z++;
			}
			scrifld(z++,fm_uJN,&KV_BoekVoldaneFactuurOpKlant);
			scrifld(z++,fm_ugrb,&KV_GrbFondsoverdracht);scrifld(z++,fm_us30,&nm_fogrb);
			scrifld(z++,fm_ugrb,&KV_GrbAfrondingsverschillen);scrifld(z++,fm_us30,&nm_rndgrb);
			scrifld(z++,fm_u6_09,KV_AfwijkendeGrbPrefix);
			for(k=start_;k<start_+11;k++){
				if(k>=DIM_FINNRS) break;
				if(FinNrs[k]<0) z+=3;
				else{
					scrifld(z++,fm_os20,FinGroepNaam[FinNrs[k]]);
					if(FinNrs[k]==10){
					  scrifld(z++,fm_os1,"-");
					  scrifld(z++,fm_os30,"Rekening v/h kasjournaal");
					}
					else{
						scrifld(z++,fm_ugrb,&KV_GrbFinDet[k]);
  					scrifld(z++,fm_us30,&nm_grb[k]);
					}
				}
			}
		}
		if(start_>0) scraddpicto(1,0,73,10,4,2,18,0,4,"vorig"); 
		else scraddpicto(2,0,73,20,4,2,13,0,4,"volgend"); 
    key=scrupd(curs,0x00E1);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101 || key==106) break;
		for(k=0;k<10;k++){
			if(KV_KasJournaal[k]==0 || nm_kassa[k][0]=='\0') continue;
			if(j_tab[KV_KasJournaal[k]]!=3 && j_tab[KV_KasJournaal[k]]!=4) {errnum=7;curs=3+k;goto redo;}
		}
		fasinit(3);	*l(3,2)=KV_GrbFondsoverdracht;copy(nm_fogrb,s(3,3),fldlen(3,3));
		if(*l(3,2)){if(faskeyi(3,1,0)){curs=14;errnum=39;goto redo;}}
		else{if(search(3,0)){curs=14;goto redo;}}
		KV_GrbFondsoverdracht=*l(3,2);copy(s(3,3),nm_fogrb,fldlen(3,3));
		
		fasinit(3);	*l(3,2)=KV_GrbAfrondingsverschillen;copy(nm_rndgrb,s(3,3),fldlen(3,3));
		if(*l(3,2)){if(faskeyi(3,1,0)){curs=14;errnum=39;goto redo;}}
		else{if(search(3,0)){curs=16;goto redo;}}
		KV_GrbAfrondingsverschillen=*l(3,2);copy(s(3,3),nm_rndgrb,fldlen(3,3));

		for(k=start_;k<start_+11;k++){
			if(k>=DIM_FINNRS) break;
			if(FinNrs[k]<0 || FinNrs[k]==10) continue;
			fasinit(3);	*l(3,2)=KV_GrbFinDet[k];copy(nm_grb[k],s(3,3),fldlen(3,3));
			if(*l(3,2) && *l(3,2)!=0xFFFFFFFF){
				if(faskeyi(3,1,0)){curs=20+(k-start_)*3;errnum=39;goto redo;}
			}
			else{
				if(search(3,0)){curs=19+(k-start_)*3;goto redo;}
			}
			KV_GrbFinDet[k]=*l(3,2);copy(s(3,3),nm_grb[k],fldlen(3,3));
		}
		if(key==5001) start_=0;
		if(key==5002) start_=11;
		if(key==108){
			sysput(18500,1,&KV_ExtraScherm);
			sysput(18501,1,&KV_ToonBoekscherm);
			sysput(18502,1,&KV_BoekVoldaneFactuurOpKlant);
			sysput(18503,6,KV_AfwijkendeGrbPrefix);
			sysput(18510,20,KV_KasJournaal);
			sysput(18530,80,KV_GrbFinDet);
			sysput(18610,4,&KV_GrbFondsoverdracht);
			sysput(18614,4,&KV_GrbAfrondingsverschillen);
			break;
		}
	}

	sysget(18500,1,&KV_ExtraScherm);
	sysget(18501,1,&KV_ToonBoekscherm);
	sysget(18502,1,&KV_BoekVoldaneFactuurOpKlant);
	sysget(18503,6,KV_AfwijkendeGrbPrefix);
	sysget(18510,20,KV_KasJournaal);
  sysget(18530,80,KV_GrbFinDet);
	sysget(18610,4,&KV_GrbFondsoverdracht);
	sysget(18614,4,&KV_GrbAfrondingsverschillen);
}

static long makegrb(uint16 arec_,float btw_)
{
  int16 g,gg,kk;
  long rekenc;
  char reken[10];
 
  if(fldlen(6,40) && *l(6,40) && *s(6,40)!=0xFF){
		rekenc=*l(6,40);
	  if(getgrb(rekenc)==0) rekenc=grb_notf;
	  return (long)(rekenc);
	}
  else{
    zero(reken,sizeof reken);
    if(KV_AfwijkendeGrbPrefix[0]) copy(KV_AfwijkendeGrbPrefix,reken,6); else copy(b3598,reken,6);
    for(g=0;g<10;g++) if(reken[g]=='\0') break;
#if FLAGDU4
		if(inq_fil>=1 && inq_fil<=9) reken[g-1]='0'+inq_fil;  // verkopen apart per filiaal 700xxxx 701xxxx, ....
#endif
    //if(fldlen(2,25)){
    //  copy(s(2,25),&reken[g],fldlen(2,25));
    //  for(g=0;g<10;g++) if(reken[g]=='\0') break;
    //}
    if(fldlen(6,39)){
      copy(s(6,39),&reken[g],fldlen(6,39));
      for(g=0;g<10;g++) if(reken[g]=='\0') break;
    }
    if(b3604){
      stcli_d(&reken[g],(long)*i(6,9),b3604,0);
      g+=b3604;
    }
    if(b3606){
      kk=btw_;gg=btw_*10 - kk*10;/* gg = decimaal */
      stcli_d(&reken[g],(long)kk,2,0);
      if(gg && b3606==2) stcli_d(&reken[g]+2,(long)gg,1,0);/* decimaal */
    }
	}
#if FLAGSHN
		if(btw_==0 && *s(6,39)=='9') copy("460000",reken,7); // eigen cadeaubon
#endif
	fasinit(3); grb_comp(reken,&rekenc);
	if(getgrb(rekenc)==0) rekenc=grb_notf;
	return (long)(rekenc);
}

static int DisplayWarning(char *ptxt, int icoon)
{
  int16 key,color_;

	color_=0; if(icoon<500) color_=3;
  scrget(1,169);
	if(icoon) scraddpicto(1,0,32,1,12,6,icoon,0,color_,"Opgelet!"); 
  scrifld(12,fm_os80,ptxt);
redo_upd:;
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  else if(key==105) return NO;
	else goto redo_upd;
	return NO;
}


static void control(void)
{
  int16 k,key,z,q_mnt_,curs=2,okey_=0;
	int16 form_dat[8],pr_mode,prtnr;
  long aant_[15];
	float kas_sal;
  double obdg_[10],bd_1,*p_mnt,bd_tot_;
	double bdg_=0,tot_chq_=0,bdn_=0,bd_uit_=0,nsal_=0,osal_;


  p_mnt=EUR_munten;q_mnt_=(sizeof EUR_munten)/8;
  bd_tot_=0; for(k=0;k<10;k++) obdg_[k]=0;
  for(k=0;k<15;k++) aant_[k]=0; bdg_=0;tot_chq_=0;
	sysget(3836,4,&kas_sal);osal_=kas_sal;
  FOREVER{
redo:;
#if FLAGDOM
		scrget(3,242);
#else
    scrget(3,241);
#endif		
		z=1;scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrifld(z++,fm_ubd,&tot_chq_);
    for(k=0;k<q_mnt_;k++){
      bd_1=aant_[k]*p_mnt[k];
      scrifld(z++,fm_ul9,&aant_[k]);
/*    scrifld(z++,fm_obd,&p_mnt[k]); */
      scrifld(z++,fm_obd,&bd_1);
    }
    scrifld(z++,fm_obd,&bdg_);
#if FLAGDOM
    scrifld(z++,fm_ubd,&osal_);
    scrifld(z++,fm_obd,&bdn_);
    scrifld(z++,fm_ubd,&bd_uit_);
    scrifld(z++,fm_ubd,&nsal_);
#else
    for(k=0;k<10;k++) scrifld(z++,fm_ubd,&obdg_[k]);
    scrifld(z++,fm_obd,&bd_tot_);
#endif
    if(okey_!=109) key=scrupd(curs,0x1E1); curs=2;
		prt2pdf=NO;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){prt2pdf=YES; key=109;} // pdf
    if(key==101) break;
    if(key==106){
      for(k=0;k<15;k++) aant_[k]=0; bdg_=0;tot_chq_=0;
			sysget(3836,4,&kas_sal);
    }
    bdg_=tot_chq_;
    for(k=0;k<q_mnt_;k++){
      bdg_+=aant_[k]*p_mnt[k];
    }
    bdn_=bdg_-osal_;
    nsal_=bdg_-bd_uit_;
    bd_tot_=bdg_;
    for(k=0;k<10;k++) bd_tot_+=obdg_[k];
    if(key==108 && bdg_) {
#if FLAGDOM
      if(nsal_>0) {kas_sal=nsal_;sysput(3836,4,&kas_sal);break;}
#endif
      obdg_[8]+=obdg_[9];/* indien vol, dan in laatste blijven bijtellen */
      for(k=9;k>0;k--) obdg_[k]=obdg_[k-1];
      obdg_[0]=bdg_;
      for(k=0;k<15;k++) aant_[k]=0; bdg_=0;tot_chq_=0;
    }
    if(okey_==109 && key==109){
	
      getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
      if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,0))!=0) goto redo;
      p_pdfname("Geldcontrole",*u(25,2),0);
			prttext("<t5><eb>");prtifld(fm_os63,&firma[0],30);prttext("<eb>");nextline();
			prttext("<t5>");prtifld(fm_os63,&firma[31],25);nextline();
			prttext("<t5>");prtifld(fm_os63,&firma[57],7);prtblank(2);
			prtifld(fm_os63,&firma[65],20);nextline();nextline();
			prttext("<t5>Telefoon : ");prtifld(fm_os63,&firma[116],15);nextline();
			prttext("<t5>Rekening : ");prtifld(fm_os63,&firma[101],14);nextline();
			nextline();nextline();
			prttext("<t5>Datum : ");prtfld(25,2,-1);nextline();
			nextline();nextline();
			prttext("<t10>Totaal cheques"); prtifld(fm_ubd,&tot_chq_,-1); nextline();
			for(k=0;k<q_mnt_;k++){
				bd_1=aant_[k]*p_mnt[k];
				prtifld(fm_ul9,&aant_[k],-1); prttext(" X");
				prtifld(fm_od4_2,&p_mnt[k],-1); prttext(" =");
				prtifld(fm_obd,&bd_1,-1);
				nextline();
			}
			prttext("<t24>-----------");nextline();
			prttext("<t10b>   Totaal geld");prtifld(fm_obd,&bdg_,-1);nextline();nextline();
			prttext("Laatste totalen :");nextline();
			for(k=0;k<5;k++) prtifld(fm_ubd,&obdg_[k],-1);nextline();
			for(k=5;k<10;k++) prtifld(fm_ubd,&obdg_[k],-1);nextline();
			nextline();
			prttext("<t7b>Algemeen totaal :");prtifld(fm_obd,&bd_tot_,-1);nextline();
			prtclose();
   		key=0;
		}
    okey_=key;
  }
}

static int add_barcode(void)
{
  int16 mode_=0,len_,pean_;
  long pos_;
  char str_[50];
								
  if(ask_in_dt("Toevoegen barcodes van kassa",YES,NO)) return NO;
  fasclos(-2);
  scrget(1,170);
  copy("kassa-00",str_,8);stcli_d(&str_[6],(long)inq_kassa,2,0);str_[8]=0x5C;
  copy("kasEXT.dat",&str_[9],11);
  if((sys4400 & 0x02)==0){
    mk_name(3936,str_);if(fasopen(filnam,1)){errnum=1;goto endsr;}
  }
  else {/* jama-light op kassa */
    mk_name(3936,"kasEXT.dat");if(fasopen(filnam,1)){errnum=1;goto endsr;}
  }
  fasunlck(-2);
  scrget(1,7);scrupd(-3,0);fasinit(1);
  fasinit(80);*l(80,1)=0;
  pos_=*l(80,1);
  FOREVER{
    next:;
    fasinit(6);
    if(read_rec(mode_)) break; mode_=1;
    len_=ele_len(0);if(len_>fldlen(6,2)) len_=fldlen(6,2);
    copy(rec_ele(0),s(6,2),len_);
    if(sys4408){
      *pu_6_1=val(s(6,2));
      if(fasgeti(6)) goto next;
    }
    else if(faskeyi(6,1,0)) goto next;
    pean_=70; if(ele_len(1) && *rec_ele(1)=='1') pean_=71;
    len_=ele_len(2);if(len_>fldlen(6,pean_)) len_=fldlen(6,pean_);
    if(len_==0) goto next;
		memset(str_,0,sizeof str_);copy(rec_ele(2),str_,len_);
		if(fldlen(64,3)){
			fasinit(64);copy(str_,s(64,2),len_);
			if(faskeyi(64,1,1)==0){
				if(cmpstr(str_,s(64,2),fldlen(64,2))==0) faskill(64);
			}
		}
		if(fldlen(64,3)==0 || *s(6,pean_)=='\0' || cmpstr(str_,s(6,pean_),fldlen(6,pean_))==0){
      zero(s(6,pean_),fldlen(6,pean_)); copy(rec_ele(2),s(6,pean_),len_); 
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			fasupd(6);
		}
		else if(fldlen(64,3)){
			fasinit(64);copy(str_,s(64,2),len_);*u(64,3)=*u(6,1);if(pean_==71) *u(64,5)=1; fasadd(64);
		}
    scrnum=0;scrget(1,170);
    scrfld(1,6,2);
    scrfld(2,6,3);
    if(pean_==70) {
      scrifld(6,fm_os20,"EAN-bak");
      scrfld(7,6,pean_);
    }
    else{
      scrifld(8,fm_os20,"EAN stuk");
      scrfld(9,6,pean_);
    }
		scrupd(-3,0);
  }
	fasclos(-2); 
	memset(str_,0,sizeof str_);// file op kassa deleten door een lege klaar te zetten in to\kassa
  copy("to\\kassa-00",str_,11);stcli_d(&str_[9],(long)inq_kassa,2,0);str_[11]=0x5C;
  copy("kasEXT.dat",&str_[12],11);
  if((sys4400 & 0x02)==0){
    mk_name(3936,str_);if(fasopen(filnam,2)){errnum=1;goto endsr;}
  }
  else{/* jama-light op kassa */
    mk_name(3936,"kasEXT.dat");if(fasopen(filnam,2)){errnum=1;goto endsr;}
  }
	fasclos(-2);
	fasunlck(-1);
	return YES;
endsr:;
	fasunlck(-1);
	return NO;
}

static void param(int mode) // 1=ga direct naar default artikels 
{
  int16 curs=1,j,k,key,z,sl_uur[10],sl_min[10];
  char prx_str[6],subart[20],subvkp[20],filfac[32],df_bpmode,df_fpmode;
	char nm_fiche[10][50];
  float df_bpval,df_fpval,df_pafr;
  char *pdum,dumm_[10];
	
  if(mode==1) goto defaultartikels;
	// kassabenaming en klant

  sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4254,40,(char *)&dt_kvk[0]);
  sysget(4294,40,(char *)&loc_klt[0]);
  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);
	sysget(3024,20,(char *)&sluitingsuur[0]);

  pdum=&dumm_[0];fieldspc(2,3,&pdum,fmt);
  memset(nm_fiche,0,sizeof nm_fiche);
  for(k=0;k<10;k++){
    fasinit(2);*u(2,1)=loc_klt[k];fasgeti(2);
		copy(s(2,3),nm_fiche[k],fldlen(2,3));
		sl_uur[k]=sluitingsuur[k]/60; sl_min[k]=sluitingsuur[k]%60;
    if(loc_nr[k]==0){
      if(fldlen(66,11+k*15)>0) loc_nr[k]=k+1;
      else loc_nr[k]=99;
    }
  }

  FOREVER{
    redo231:;
    scrget(3,231);z=1;
    for(k=0;k<10;k++){
      scrifld(z++,fm_us6,nm_kassa[k]);
      scrifld(z++,fm_udat,&dt_kvk[k]);
    	scrifld(z++,fmt,nm_fiche[k]);
			scrifld(z++,fm_uur,&sl_uur[k]); scrifld(z++,fm_uur,&sl_min[k]); 
      if(fldlen(66,1)) scrifld(z++,fm_uu2,&loc_nr[k]);
      else scrifld(z++,fm_os2,"99");
    }
    for(k=0;k<10;k++){
      if(fldlen(66,11+k*15))	scrifld(z++,fm_us6,nm_loc[k]);
      else z++;
    }
    key=scrupd(curs,0x1A1);curs=1;
    if(key==106) break;
    for(k=0;k<10;k++){
      if(nm_kassa[k][0]!='\0'){// indien kassa, dan moet er ook een klant aan gekoppeld zijn
				fasinit(2);copy(nm_fiche[k],s(2,3),fldlen(2,3));
				if(search(2,0)){ errnum=39;curs=3+k*6;goto redo231;}
			  if(sl_uur[k]==0 || sl_uur[k]>23){errnum=34;curs=4+k*6; goto redo231;}
			  if(sl_min[k]>59){errnum=34;curs=5+k*6; goto redo231;}
     	}
			else {
				if(nm_fiche[k][0]){
					fasinit(2);copy(nm_fiche[k],s(2,3),fldlen(2,3));
				  if(search(2,0)){ errnum=39;curs=3+k*6;goto redo231;}
				}
				else{fasinit(2);sl_uur[k]=0;sl_min[k]=0;}
			}
      loc_klt[k]=*u(2,1);copy(s(2,3),nm_fiche[k],fldlen(2,3));
      if(fldlen(66,1)==0) loc_nr[k]=99;
      else{
				if(loc_nr[k]>=1 && loc_nr[k]<=10){
					z=loc_nr[k]-1;
					if(fldlen(66,11+z*15)==0) {errnum=34;curs=6+k*6; goto redo231;}
				}
				else loc_nr[k]=99;
      }
    }

    if(key==101 || key==108){
      sysput(4134,120,(char *)&nm_kassa[0][0]);
      sysput(4254,40,(char *)&dt_kvk[0]);
      sysput(4294,40,(char *)&loc_klt[0]);
      sysput(2730,40,(char *)&loc_nr[0]);
      sysput(2770,60,(char *)&nm_loc[0][0]);
      for(k=0;k<10;k++) sluitingsuur[k]=sl_uur[k]*60+sl_min[k];
			sysput(3024,20,(char *)&sluitingsuur[0]);
			if(key==101) goto endsr;
      break;
    }
  }
	
	sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4254,40,(char *)&dt_kvk[0]);
  sysget(4294,40,(char *)&loc_klt[0]);
  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);
	sysget(3024,20,(char *)&sluitingsuur[0]);

	defaultartikels:;
	// tabel onbekende artikels 

  sysget(2900,40,(char *)&TbDiversArtikel[0]);
	pdum=&dumm_[0];fieldspc(2,3,&pdum,fmt);
  memset(nm_fiche,0,sizeof nm_fiche);

  for(k=0;k<10;k++){
    fasinit(6);*u(6,1)=TbDiversArtikel[k];if(*u(6,1)) fasgeti(6);
		copy(s(6,3),nm_fiche[k],fldlen(6,3));
	}
  FOREVER{
    redo322:;
    scrget(3,322);z=1;
    for(k=0;k<10;k++){
			if((k>0 && k<8 && btw_pct[k]==0) || k==8) {z+=2;continue;}  // wordt niet gebruikt
			if(k==9) scrifld(z++,fm_os8,"Leeggoed");
      else if(k==0) scrifld(z++,fm_of21_,&btw_pct[k]);
			else scrifld(z++,fm_of2_1,&btw_pct[k]);
			scrifld(z++,fmt,nm_fiche[k]);
    }
    key=scrupd(curs,0xE1);curs=1;
    if(key==106) break;
    for(k=0;k<10;k++){
			if(k==8) continue;
      if(k==0 || k==9 || btw_pct[k]){
				fasinit(6);copy(nm_fiche[k],s(6,3),fldlen(6,3));
				if(search(6,0)){ errnum=39;curs=2+k*2;goto redo322;}
     	}
			else fasinit(6);
      TbDiversArtikel[k]=*u(6,1);copy(s(6,3),nm_fiche[k],fldlen(6,3));
    }
    if(key==101 || key==108){
      sysput(2900,40,(char *)&TbDiversArtikel[0]);
			if(key==101) goto endsr;
      break;
    }
  }
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
	if(mode) goto endsr;

	// subdirectories en default punten 


  copy(sys3896,prx_str,6);
  sysget(3902,16,subart);
  sysget(3936,16,subvkp);
  sysget(4572,32,filfac);
  sysget(3982,1,&df_bpmode);
  sysget(3983,4,&df_bpval);
  sysget(3987,1,&df_fpmode);
  sysget(3988,4,&df_fpval);
  sysget(3992,4,&df_pafr);
  sysget(4338,3,kas_munt);
  FOREVER{
		redo200:;
    scrget(3,200);z=1;
    for(k=0;k<6;k++) scrifld(z++,fm_u_09,&prx_str[k]);
    scrifld(z++,fm_us15,subart);
    scrifld(z++,fm_us15,subvkp);
    scrifld(z++,fm_us30,filfac);
    scrifld(z++,fm_usP_G,&df_bpmode);
    scrifld(z++,fm_uf6_2,&df_bpval);
    scrifld(z++,fm_usP_G,&df_fpmode);
    scrifld(z++,fm_uf6_2,&df_fpval);
    scrifld(z++,fm_uf3_2,&df_pafr);
    key=scrupd(curs,0x00A1);curs=1;
    if(key==106) break;
		for(k=0;k<6;k++){
  		if(prx_str[k] && (prx_str[k]<'0' || prx_str[k]>'9' || fldlen(6,PrNrs[prx_str[k]-'0'])==0)){curs=1+k;errnum=34;goto redo200;}
		}
		if(key==101 || key==108){
      copy(prx_str,sys3896,6);
      sysput(3896,6,&sys3896[0]);
      sysput(3902,16,subart);
      sysput(3936,16,subvkp);
      sysput(4572,32,filfac);
      sysput(3982,1,&df_bpmode);
      sysput(3983,4,&df_bpval);
      sysput(3987,1,&df_fpmode);
      sysput(3988,4,&df_fpval);
      sysput(3992,4,&df_pafr);
			if(key==101) goto endsr;
      break;
    }
  }
	sysget(3896,6,&sys3896[0]);
  sysget(3902,16,subart);
  sysget(3936,16,subvkp);
  sysget(4572,32,filfac);
  sysget(3982,1,&df_bpmode);
  sysget(3983,4,&df_bpval);
  sysget(3987,1,&df_fpmode);
  sysget(3988,4,&df_fpval);
  sysget(3992,4,&df_pafr);
  sysget(4338,3,kas_munt);

	sysget(8000,60,NaamVarBetWijze); 
	for(k=0;k<3;k++) {
		if(NaamVarBetWijze[k][0]=='\0') copy("Var.Bet.wijze",NaamVarBetWijze[k],15);
		FinGroepNaam[32+k]=NaamVarBetWijze[k];
	}
	FOREVER{
    scrget(3,201);z=1;
		for(k=0;k<3;k++) scrifld(z++,fm_us20,NaamVarBetWijze[k]);
    key=scrupd(curs,0x00A1);curs=1;
    if(key==106) break;
    if(key==101 || key==108){
      sysput(8000,60,NaamVarBetWijze); 
			if(key==101) goto endsr;
      break;
		}
	}
	sysget(8000,60,NaamVarBetWijze); 
	for(k=0;k<3;k++) {
		if(NaamVarBetWijze[k][0]=='\0') copy("Var.Bet.wijze",NaamVarBetWijze[k],15);
		FinGroepNaam[32+k]=NaamVarBetWijze[k];
	}

	
	sysget(19380,120,PtypePerKassa); curs=0;
	FOREVER{ // afwijkende prijstypes
    redo202:;
    scrget(3,202);z=1;
    for(k=0;k<10;k++){
      scrifld(z++,fm_os6,nm_kassa[k]);
			if(nm_kassa[k][0] && fldlen(91,11+k*5)) {
				for(j=0;j<6;j++) scrifld(z++,fm_u_09,&PtypePerKassa[k][j]);
				curs++;
			}
			else z+=6;
    }
		if(curs>0) curs=1; else curs=-1;
    key=scrupd(curs,0x1A1);curs=1;
    if(key==106) break;
    for(k=0;k<10;k++){
			for(j=0;j<6;j++){
				if(PtypePerKassa[k][j]=='\0') break;
				if(PtypePerKassa[k][j]<'0' || PtypePerKassa[k][j]>'9' || fldlen(6,PrNrs[PtypePerKassa[k][j]-'0'])==0){curs=1+k*7+j;errnum=34;goto redo202;}
			}
		}
    if(key==101 || key==108){
      sysput(19380,120,PtypePerKassa); 
			if(key==101) goto endsr;
      break;
		}
	}
	endsr:;
}

static void dsp_dagt(void)
{
  int16 k,z,key,mode,end;
  uint16 last_dt,last_dg_;
  double omzet,winst,tot_vw,tot_evw,tot_w,qlv,vw_ex;
									
  if(ask_in_dt("Bekijken dagtotalen",NO,NO)) goto endsr;
  scrget(1,7);scrupd(-3,0);
  scrnum=0;scrget(3,222);z=1;
  if(inq_kassa) scrifld(z++,fm_uu2,&inq_kassa);
  else scrifld(z++,fm_os11,"Allemaal");
  scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
  scrifld(118,fm_os11,"Opzoeken...");scrupd(-3,0);
  tot_vw=0;tot_w=0; tot_evw=0; last_dt=0xFFFF;end=NO;last_dg_=0;
  fasinit(91);*pu_91_3=dat_beg;mode=1;AW=0;VW=0;qlv=0;omzet=0;winst=0;vw_ex=0;
  FOREVER{
    next_bew:;
    if(faskeyi(91,2,mode)) end=YES;mode=2;
    if(dat_beg && *pu_91_3< dat_beg) goto next_bew;
    if(dat_end && *pu_91_3>dat_end) end=YES;
    if(end || (*pu_91_3!=0xFFFF && *pu_91_3!=last_dt)){
      winst=vw_ex-AW;omzet=VW;
      tot_w+=winst;tot_vw+=VW; tot_evw+=vw_ex;
      if(VW){
				scrifld(z++,fm_udat,&last_dt);scrifld(z++,fm_od8_2,&omzet);
			/* nieuwe week markeren */
				k=last_dt%7;if(k>=0 && k<=6) k=dag_nr[k];
				if(k<=last_dg_){scrchat(z-2,0x9);scrchat(z-1,0x09);}
				last_dg_=k;scrupd(-3,0);
				z=next_z(z-1,4,3,2,19);/*  z, begin, q_kol, q_per_len, q_lin */
      }
      if(end || z==-1){
				FOREVER{
					if(end){scrifld(118,fm_os11," Klaar");scrchat(118,0x8);}
					else scrifld(118,fm_os11,"");
					key=scrupd(-1,0x81);
					if(end || key==101) goto endsr;
					if(key==108){
						scrnum=0;scrget(3,222);z=1;
						if(inq_kassa) scrifld(z++,fm_uu2,&inq_kassa);
						else scrifld(z++,fm_os11,"Allemaal");
						scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
						scrifld(118,fm_os11,"Opzoeken...");scrupd(-3,0);
						break;
					}
				}
      }
      omzet=0; VW=0;AW=0;vw_ex=0;
    }
    last_dt=*pu_91_3;
    fasinit(6);*pu_6_1=*pu_91_2;fasgeti(6);
    if(inq_kassa){
      AW+=*f(91,12+(inq_kassa-1)*5);
      VW+=*f(91,13+(inq_kassa-1)*5);
      vw_ex+=*f(91,13+(inq_kassa-1)*5)/(1.+*pf_6_28/100.);
      if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
				AW+=*f(91,12+(inq_kassa-1+ft_off)*5);
				VW+=*f(91,13+(inq_kassa-1+ft_off)*5);
				vw_ex+=*f(91,13+(inq_kassa-1+ft_off)*5)/(1.+*pf_6_28/100.);
      }
    }
    else{
      for(k=0;k<max_kassa;k++){
				if(fldlen(91,11+k*5)){
					AW+=*f(91,12+k*5);
					VW+=*f(91,13+k*5);
					vw_ex+=*f(91,13+k*5)/(1.+*pf_6_28/100.);
				}
				if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
					AW+=*f(91,12+(k+ft_off)*5);
					VW+=*f(91,13+(k+ft_off)*5);
					vw_ex+=*f(91,13+(k+ft_off)*5)/(1.+*pf_6_28/100.);
				}
      }
    }
  }
  endsr:;
}
 

static int next_z(int16 z, int16 beg_, int16 qkol_, int16 qperlin_, int16 qlin_)
{
   int16 k,lin_,kol_;
   k=z-beg_;
   lin_=k/(qkol_*qperlin_); kol_=(k-(lin_*qkol_*qperlin_))/qperlin_;
   lin_++;
   if(lin_>=qlin_){
     kol_++;
     if(kol_>=qkol_) return -1;/* scherm vol */
     lin_=0;
   }
   z=beg_ + kol_*qperlin_+ (lin_*qkol_*qperlin_);
   return z;
}
 

static int inp_klant(void)
{
  int16 k;
  uint16 knr_,max_,dt_beg_, dt_end_;
  char str_[20];
								
  if(ask_in_dt("Toevoegen klanten",NO,NO)) return NO;
	fasunlck(-2);
  fasclos(-2);
  scrget(1,7);scrupd(-3,0);
  knr_=inq_kassa; dt_beg_=dat_beg;dt_end_=dat_end;
  k=1; max_=10; if(inq_kassa){k=inq_kassa; max_=inq_kassa;}
  for(k;k<=max_;k++){
    if(nm_kassa[k-1][0]=='\0') continue;
    inq_kassa=k; dat_beg=dt_beg_;dat_end=dt_end_;
    if(dt_kvk[k-1]+1 >= dat_beg) dat_beg=dt_kvk[k-1]+1;
    if(dat_beg>dat_end) continue;
    fasclos(-2);
    scrget(1,170);
		MakeKaslogName(k,dat_end);
    dt_last=dt_kvk[k-1];
    scrget(1,7);scrupd(-3,0);
    execklt(inq_kassa-1);
#if 0
    if(dt_kvk[k-1]<dt_last){
      dt_kvk[k-1]=dt_last;sysput(4254+(k-1)*2,2,&dt_kvk[k-1]);
    }
#endif
  }
  inq_kassa=knr_; dat_beg=dt_beg_;dat_end=dt_end_;
	fasunlck(-1);
	return YES;
}

static void execklt(int16 kasnr)
{
  int16 k;
  uint16 z_klt_=6;
  long a,r_beg_,r_end_;
  struct _LogDag *dg_1,*dg_2;
  struct _fas_s_lijn *pslin;


  scrget(1,170);fasclos(-2);
  errnum=fasopen(filnam,1);if(errnum==1){errnum=0;goto endsr;}
  fasinit(80);seqo_pos=0;seqo_mode=2;
  scrget(1,170); scrifld(4,fm_os30,"Toevoegen van klant : ");
  fasseqi(80,1,sizeof LogHeader+4);
  copy(s(80,1)+4,(char *)&LogHeader.versie[0],sizeof LogHeader);
  for(k=0;k<LogHeader.dag_used;k++){
    *l(80,1)=LogHeader.dag_pos+k*LogHeader.dag_len;
    fasseqi(80,1,LogHeader.dag_len*2+4);
    dg_1=(struct _LogDag *)(s(80,1)+4);dg_2=dg_1+1;
    if(k==(LogHeader.dag_used-1)) dg_2->first_rec=LogHeader.rec_used;
    if(dg_1->datum>=dat_beg && dg_1->datum<=dat_end){
/*    exec_1dg(dg_1->datum,dg_1->first_rec,dg_2->first_rec-1); */
      r_beg_=dg_1->first_rec;r_end_=dg_2->first_rec-1;
      for(a=r_beg_;a<=r_end_;a++){/* NIEUWE klant 99999999 toevoegen */
	*l(80,1)=LogHeader.rec_pos+a*LogHeader.rec_len;
	pslin=(struct _fas_s_lijn *)(s(80,1)+4);
	fasseqi(80,1,sizeof *pslin+4);
	if(bit(pslin->bits,7)){
	  if(cmpstr(s(80,1)+5,"Klantnr.: 99999999",18)==0){
			if(add_klt(a+1,NO)==0) {scrfld(z_klt_++,2,3);scrupd(-3,0);}
	    if(z_klt_>=19) z_klt_=6;
	  }
	}
      }
    }
  }
  fasclos(-2);
  scrifld(19,fm_os63,"Druk op F8 om verder te gaan ...");scrupd(-1,0x81);
  endsr:;
}

static int inp_1dag(void)
{
  int16 k;
  uint16 knr_,max_,dt_beg_, dt_end_,dt_;
  char str_[20],nmkaslog_[15];

	if(CheckForFreeSpace(91,MINFREE)) return YES;/* onvoldoende vrije records */
	if(fldlen(60,1) && CheckForFreeSpace(60,200)) return YES;/* onvoldoende vrije records */
	if(fldlen(16,1) && CheckForFreeSpace(16,500)) return YES;/* onvoldoende vrije records */
	for(k=0;k<10;k++) if(TbDiversArtikel[k]!=0) break;	if(k>=10) param(1); // eerst diverse artikels invullen 
  if(ask_in_dt("Inlezen verkopen",NO,YES)) return NO;
	fasunlck(-2);
  fasclos(-2);
  scrget(1,7);
  knr_=inq_kassa; dt_beg_=dat_beg;dt_end_=dat_end;
  k=1; max_=10; if(inq_kassa){k=inq_kassa; max_=inq_kassa;}
  scrnum=0;scrget(3,299);z299=1;scraddf(200,23,78,0);
  scrifld(z299++,fm_udat,&dat_beg);scrifld(z299++,fm_udat,&dat_end);
  scrifld(174,fm_os30," Bezig met inlezen ....");scrupd(-3,0);
  for(k;k<=max_;k++){
    if(nm_kassa[k-1][0]=='\0') continue;
    inq_kassa=k; dat_beg=dt_beg_;dat_end=dt_end_;
    if(chk_dtkvk && dt_kvk[k-1]+1 >= dat_beg) dat_beg=dt_kvk[k-1]+1;
    if(dat_beg>dat_end) continue;
		if(sys4400 & 0x04){ // bij kaslog per maand, checken of er een kaslog van die maand inzit
			for(dt_=dat_beg; dt_<=dat_end;dt_++){
				MakeKaslogName(k,dt_); 
		    if(GetFileAttributes(filnam)!=INVALID_FILE_ATTRIBUTES) break;
				if(dt_>dat_beg) continue;
			}
		}
		else{
  		MakeKaslogName(k,dat_end); 
	  	if(GetFileAttributes(filnam)==INVALID_FILE_ATTRIBUTES){errnum=1;continue;}
		}
    dt_last=dt_kvk[k-1];
    execfil(inq_kassa-1);
#if 0
    if(dt_kvk[k-1]<dt_last){
      dt_kvk[k-1]=dt_last;sysput(4254+(k-1)*2,2,&dt_kvk[k-1]);
    }
#endif
  }
  inq_kassa=knr_; dat_beg=dt_beg_;dat_end=dt_end_;
  if(z299>1) {
    scrifld(174,fm_os30," F8 Klaar! Keer terug.");
    scrupd(-1,0x81);
  }
	fasunlck(-1);
	return YES;
}

static void execfil(int16 kasnr)
{
  int16 k,jj,mm,dd,nr_,ori_wis_eerst_;
  uint16 dt_,last_dt_;
  char str_[25];
  struct _LogDag *dg_1,*dg_2;
	   
	dsp_count=0; ori_wis_eerst_=wis_eerst;
  if((sys4400 & 0x01) || (sys4400 & 0x04)){// kaslog per dag : KLyymmdd.DAT  of per maand KLyyyymm.DAT
	  for(dt_=dat_beg;dt_<=dat_end;dt_++){
			MakeKaslogName(kasnr+1,dt_); fasclos(-2);if(fasopen(filnam,1)){continue;}
      fasinit(80);seqo_pos=0;seqo_mode=2;
      fasseqi(80,1,sizeof LogHeader+4);
      copy(s(80,1)+4,(char *)&LogHeader.versie[0],sizeof LogHeader);
      for(k=0;k<LogHeader.dag_used;k++){
				*l(80,1)=LogHeader.dag_pos+k*LogHeader.dag_len;
				fasseqi(80,1,LogHeader.dag_len*2+4);
				dg_1=(struct _LogDag *)(s(80,1)+4);dg_2=dg_1+1;
				if(k==(LogHeader.dag_used-1)) dg_2->first_rec=LogHeader.rec_used;
				if(dg_1->datum==dt_){ //if(dg_1->datum>=dat_beg && dg_1->datum<=dat_end){
					dt_dag1=dg_1->datum;
					jddate(dt_dag1,&jj,&mm,&dd);
					if(CheckForFreeSpace(91,MINFREE)) {z299=1; break;}
				  if(fldlen(60,1) && CheckForFreeSpace(60,200)) {z299=1; break;}/* onvoldoende vrije records */
	        if(fldlen(16,1) && CheckForFreeSpace(16,500)) {z299=1; break;}/* onvoldoende vrije records */
					nr_=kasnr+1;
					scrifld(z299++,fm_ou2,&nr_);scrifld(z299++,fm_udat,&dt_dag1);scrupd(-3,0);
					Execute1KassaDag(nr_,dt_dag1,dg_1->first_rec,dg_2->first_rec-1);
					scrifld(z299++,fm_od6_2,&dagomzet);scrupd(-3,0);
					z299=next_z(z299-1,3,3,3,19);/*  z, begin, q_kol, q_per_len, q_lin */
					if(z299<3) z299=3;/* scherm vol */
					if(dt_kvk[kasnr]<dt_dag1){
						dt_kvk[kasnr]=dt_dag1;sysput(4254+(kasnr)*2,2,&dt_kvk[kasnr]);
					}
					break; // voor iedere dag de kaslog openen 
				}
      }
      fasclos(-2);
    }
  }
  else {
    fasclos(-2);
    errnum=fasopen(filnam,1);if(errnum==1){errnum=0;goto endsr;}
    fasinit(80);seqo_pos=0;seqo_mode=2; last_dt_=0;
    fasseqi(80,1,sizeof LogHeader+4);
    copy(s(80,1)+4,(char *)&LogHeader.versie[0],sizeof LogHeader);
    for(k=0;k<LogHeader.dag_used;k++){
			wis_eerst=ori_wis_eerst_;
      *l(80,1)=LogHeader.dag_pos+k*LogHeader.dag_len;
      fasseqi(80,1,LogHeader.dag_len*2+4);
      dg_1=(struct _LogDag *)(s(80,1)+4);dg_2=dg_1+1;

      if(k==(LogHeader.dag_used-1)) dg_2->first_rec=LogHeader.rec_used;
      if(dg_1->datum>=dat_beg && dg_1->datum<=dat_end){
				dt_dag1=dg_1->datum;
				if(wis_eerst && last_dt_ && dt_dag1==last_dt_){
					wis_eerst=NO; // goto next_dag;  // uit veiligheid als men de datum van de kassa heeft teruggezet
				}
				last_dt_=dt_dag1; jddate(dt_dag1,&jj,&mm,&dd);
				if(CheckForFreeSpace(91,MINFREE)) {z299=1; break;}
				if(fldlen(60,1) && CheckForFreeSpace(60,200)) {z299=1; break;}/* onvoldoende vrije records */
	      if(fldlen(16,1) && CheckForFreeSpace(16,500)) {z299=1; break;}/* onvoldoende vrije records */
				nr_=kasnr+1;
				scrifld(z299++,fm_ou2,&nr_);scrifld(z299++,fm_udat,&dt_dag1);scrupd(-3,0);
				Execute1KassaDag(nr_,dt_dag1,dg_1->first_rec,dg_2->first_rec-1);
				scrifld(z299++,fm_od6_2,&dagomzet);scrupd(-3,0);
				z299=next_z(z299-1,3,3,3,19);/*  z, begin, q_kol, q_per_len, q_lin */
				if(z299<3) z299=3;/* scherm vol */
				if(dt_kvk[kasnr]<dt_dag1){
					dt_kvk[kasnr]=dt_dag1;sysput(4254+(kasnr)*2,2,&dt_kvk[kasnr]);
				}
      }
			next_dag:;
    }
    fasclos(-2);
  }
  endsr:;
}

static void Execute1KassaDag(uint16 kassa_nr, uint16 dt, long r_beg, long r_end)
{
  int16 len_,g,j,add_rec_,via_groep,dd=0,mm=0,jj=0,kas_off_,qtickets_,qFTtickets_,off_tick_;
  char last_art[15];
  long a;
  float qlv_,tot_exc_,bd_ticket_;
  struct _fas_s_lijn *pslin;
	   
  if(wis_eerst) wis_fld(dt,kassa_nr,YES,NO);dagomzet=0;
/*  scrifld(11,fm_udat,&dt); */
  jddate(dt,&jj,&mm,&dd);mm--;
  len_=fldlen(6,2);if(len_>5) len_=5; zero(last_art,sizeof last_art);
  ok_pos=0; kas_off_=0;krtok_pos=0;
	bd_ticket_=0;qtickets_=0;qFTtickets_=0; off_tick_=0;
  for(a=r_beg;a<=r_end;a++){
    if(ft_off && ok_pos<=a){
      kas_off_=chk_fact(a,r_end);
    }
    if(use_kaart && krtok_pos<=a){
      chk_kkaart(a,r_end);/* kaart erbij nemen en punten al invullen */
    }
    *l(80,1)=LogHeader.rec_pos+a*LogHeader.rec_len;
    pslin=(struct _fas_s_lijn *)(s(80,1)+4);
    fasseqi(80,1,sizeof *pslin+4);
		if(pslin->bits&NEW_TICKET /* bit(pslin->bits,6)*/ ){ // begin nieuw ticket (x40) : aantal tickets verhogen
			if(bd_ticket_){
				if(off_tick_) qFTtickets_++; else qtickets_++;
			}
			bd_ticket_=0; off_tick_=0;
		}
		else {
			bd_ticket_+=1;//off_tick_=kas_off_;
		}
    if(bit(pslin->bits,7)==NO && pslin->groep>=-9 && pslin->groep<=999){
			
      fasinit(6); via_groep=YES;
      if(pslin->code[0]){
				via_groep=NO;
				copy(pslin->code,s(6,2),len_);
				if(sys4408){
					*pu_6_1=val(s(6,2));
					g=fasgetu(6);
				}
				else{
					g=faskeyu(6,1,0);
				}
				if(g){
					fasinit(6);
			  	if(pslin->groep==99) *u(6,1)=TbDiversArtikel[9]; // leeggoed divers
  			  else {
						for(j=0;j<8;j++) if(pslin->btw==btw_pct[j]) break;
  			  	if(j<8) *u(6,1)=TbDiversArtikel[j];
				  }
				  if(*u(6,1)) fasgeti(6);
					else via_groep=YES;
				}
      }
      if(via_groep){
				if(pslin->groep>=1){/* verkoop op groep */
					*s(6,2)='G';stcli_d(s(6,2)+1,(long)pslin->groep,2,0);
					if(faskeyu(6,1,0)){
						fasinit(6);
				  	if(pslin->groep==99) *u(6,1)=TbDiversArtikel[9]; // leeggoed divers
  				  else {
							for(j=0;j<8;j++) if(pslin->btw==btw_pct[j]) break;
  				  	if(j<8) *u(6,1)=TbDiversArtikel[j];
						}
						if(*u(6,1)) fasgeti(6);						
					}
				}
				else{
					copy(last_art,s(6,2),fldlen(6,2));/* korting op groep */
				}
      }
      copy(s(6,2),last_art,fldlen(6,2));
			if((dsp_count%50)==0){scrifld(200,fm_os1,&dsp_kar[kdsp++]);scrupd(-3,0); if(kdsp==4) kdsp=0;} dsp_count++;
      if(faskeyu(6,1,0)==0){
				if(pslin->groep<0) pslin->aantal=0;/* kassa-fout ivm korting op artikel */
				tot_exc_=pslin->totaal/(1.+ *f(6,28)/100.);
				fasinit(91);*pu_91_3=dt;*pu_91_2=*pu_6_1;
				add_rec_=NO;if(faskeyi(91,1,0)) add_rec_=YES;
				if((pslin->bits & 1) && *f(6,31)) pslin->aantal/=*f(6,31);
				if(kas_off_>=10 && fldlen(91,11+(inq_kassa+kas_off_-1)*5)==0) continue;/* fact.verkopen NIET bijhouden */
				*f(91,11+(inq_kassa+kas_off_-1)*5)+=pslin->aantal;
				if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt) *f(91,12+(inq_kassa+kas_off_-1)*5)+=pslin->aantal* *f(6,112);
				else *f(91,12+(inq_kassa+kas_off_-1)*5)+=pslin->aantal* *f(6,18);
				*f(91,13+(inq_kassa+kas_off_-1)*5)+=pslin->totaal;
				bd_ticket_+=1; off_tick_=kas_off_;// pslin->totaal;
				dagomzet+=pslin->totaal;
				if(add_rec_) fasadd(91); else fasupd(91);
				if(upd_stock=='J' && sys3978==0){
					if(pslin->groep!=99 || !(pslin->bits&AUTO_LEEG)){ 	// leeggoed van VOLgoed NIET bijhouden 
						if(kas_off_==0 || SoortDocument!='L') up_a_stock(*pu_6_1,inq_kassa,dt,pslin->aantal,tot_exc_); // ALTIJD behalve rechtstreekse leveringsbon (wordt later gefactureerd)
					}
					if(fldlen(60,1) && (sys3772 & 0x10) && ((sys3772 & 0x40) || kas_off_==0)){ // enkel particuliere verkoop (en facturen via bit B6)
						qlv_=pslin->aantal;
						_sta_upd(*pu_6_1,inq_kassa,&qlv_,&tot_exc_,mm);
					}
					if(fldlen(16,1) && (sys3772 & 0x10) && ((sys3772 & 0x40) || kas_off_==0)){ // enkel particuliere verkoop (en facturen via bit B6)
						qlv_=pslin->aantal;
						_his_upd(*pu_6_1,inq_kassa,&qlv_,&tot_exc_,dt);
					}
				}
				if(use_kaart && kaartnr>0){
					if((sys3772&0x1)==0 && dt_last_krt_ak<=dt_dag1 ){// niet opnieuw aanpassen bij herinlezen 
						*u(92,30)=dt;*f(92,32)+=tot_exc_; *f(92,21)+=tot_exc_;
						if(*u(92,20)==0) *u(92,20)=dt;
						fasupd(92);
					}
					
					if(pslin->groep>=1 && pslin->groep<=99){
						fasinit(94);*u(94,2)=kaartnr; *u(94,3)=pslin->groep;
						if(faskeyi(94,1,0)) fasadd(94);
						if(*u(94,6)<=dt_dag1 ){// niet opnieuw aanpassen bij herinlezen 
						  *u(94,6)=dt;*f(94,7)+=tot_exc_;fasupd(94);
						}
					}
					if(fldlen(97,1)){// kaarthistorieken altijd bijhouden
						qlv_=pslin->aantal;
		  			_kaart_his_upd(*pu_6_1,inq_kassa,&qlv_,&tot_exc_,dt);
					}
				}
      }
    }
  }
	if(bd_ticket_){
		if(off_tick_) qFTtickets_++; else qtickets_++;
	}
	dt_last=dt;
  fasinit(91);*pu_91_3=dt;add_rec_=NO;if(faskeyi(91,1,0)) add_rec_=YES;
  *f(91,11+(inq_kassa-1)*5)=qtickets_; 
	if(ft_off) *f(91,11+(inq_kassa+ft_off-1)*5)=qFTtickets_; 
	if(add_rec_) fasadd(91); else fasupd(91);
}


static void up_a_stock(uint16 arec_, uint16 knr_, uint16 dt_, float qlv_, float bedrag_)
{
  int16 p_stloc_,clip_;
	float factor_;
 
  p_stloc_=knr_-1;
  if(fldlen(66,1)==0) p_stloc_=-1;
  else{
    if(loc_nr[knr_-1]==0) loc_nr[knr_-1]=knr_;/* overgang */
    if(loc_nr[knr_-1]==99) p_stloc_=-1;
    else{
      p_stloc_=loc_nr[knr_-1]-1;
      if(fldlen(66,11+p_stloc_*15)==0) p_stloc_=-1;
    }
  }
	clip_=NO;
	if(fldlen(6,102) && *u(6,102)){// is dit een clip?
		factor_=*f(6,31);
		*u(6,1)=*u(6,102);fasgeti(6);
#if FLAGSAS | FLAGGRS  | FLAGALB
		clip_=YES; // gekoppeld, altijd moederfiche bijwerken
#else
		if(*f(6,31)!=factor_) clip_=YES;
#endif
		fasinit(6);*u(6,1)=arec_;fasgeti(6);
	}
  if(p_stloc_<0){/* op artikelfiche bijwerken */
		factor_=1.;
		if(clip_){// stock/omzet op moederfiche bijwerken
			factor_=*f(6,31);
			*u(6,1)=*u(6,102);fasgeti(6);
			if(*f(6,31)) factor_/=*f(6,31); else factor_=1.;
		}
    if(fldlen(6,33)) *f(6,33)-=qlv_*factor_;
    if(fldlen(6,57)) *f(6,57)+=qlv_*factor_;
    if(fldlen(6,59)) *f(6,59)+=qlv_*factor_;
    if(fldlen(6,58)) *f(6,58)+=bedrag_;
    if(fldlen(6,60)) *f(6,60)+=bedrag_;
    if(fldlen(6,48) && dt_) *u(6,48)=dt_;
		if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
    fasupd(6);
		
  }
  else{/* per filiaal bijwerken */
		factor_=1.;
		if(clip_){// stock/omzet op moederfiche bijwerken
			factor_=*f(6,31);
			*u(6,1)=*u(6,102);fasgeti(6);
			if(*f(6,31)) factor_/=*f(6,31); else factor_=1.;
		}
    fasinit(66);*u(66,2)=*pu_6_1;
    if(faskeyi(66,1,0)){ fasinit(66);*u(66,2)=*pu_6_1;}
    *f(66,11+p_stloc_*15)-=qlv_*factor_;
    if(fldlen(66,17+p_stloc_*15)) *f(66,17+p_stloc_*15)+=qlv_*factor_;
    if(fldlen(66,18+p_stloc_*15)) *f(66,18+p_stloc_*15)+=qlv_*factor_;
    if(fldlen(66,19+p_stloc_*15) && dt_) *u(66,19+p_stloc_*15)=dt_;
    if(*u(66,1)) fasupd(66);
    else{*u(66,2)=*pu_6_1;fasadd(66);}
  }
	*u(6,1)=arec_;fasgeti(6);
}
 

static int chk_kkaart(long r_beg, long r_end)
{
  int16 k,len_;
  long a;
  struct _fas_s_lijn *pslin;
									
  kaartnr=0;dt_last_krt_ak=0;
  if(use_kaart==NO) return NO;
 
  for(a=r_beg;a<=r_end;a++){
    *l(80,1)=LogHeader.rec_pos+a*LogHeader.rec_len;
    pslin=(struct _fas_s_lijn *)(s(80,1)+4);
    fasseqi(80,1,sizeof *pslin+4);
    if(bit(pslin->bits,7)==NO || bit(pslin->bits,6)){
      if(bit(pslin->bits,6) && a!=r_beg) break; /* begin nieuw ticket (x40) */
      if(pslin->groep==1033) {
				fasinit(92);*u(92,1)=(uint16)(pslin->btw);
				if(*u(92,1) && fasgeti(92)==0){
					kaartnr=*u(92,1);dt_last_krt_ak=*u(92,30);
					if(dt_last_krt_ak<=dt_dag1){// niet opnieuw aanpassen bij herinlezen 
						len_=s(92,35)-s(92,30);
						for(k=9;k>0;k--){
							if(fldlen(92,30+k*5)) copy(s(92,30+(k-1)*5),s(92,30+k*5),len_);
						}
						zero(s(92,30),len_);
						*u(92,31)=pslin->aantal;*u(92,33)=pslin->totaal;
					}
				}
	// laten doorgaan tot einde ticket			break;
      }
    }
  }
  krtok_pos=a;
  return YES;

}

static int chk_fact(long r_beg, long r_end)
{
  int16 off_=0;
  long a;
  struct _fas_s_lijn *pslin;

	SoortDocument='\0';
  for(a=r_beg;a<=r_end;a++){
    *l(80,1)=LogHeader.rec_pos+a*LogHeader.rec_len;
    pslin=(struct _fas_s_lijn *)(s(80,1)+4);
    fasseqi(80,1,sizeof *pslin+4);
    if(bit(pslin->bits,7)==NO || bit(pslin->bits,6)){
      if(bit(pslin->bits,6) && a!=r_beg) break;/* begin nieuw ticket (x40) */
      if(pslin->groep==1100) {
				off_=ft_off;
				if(pslin->code[0]=='L') SoortDocument='L';
				else if(pslin->code[0]=='F') SoortDocument='F'; 
				break;
			}
    }
  }
  ok_pos=a;
  if(off_!=ft_off) return off_;/* contant ticket */
 
  for(a=ok_pos;a<=r_end;a++){/* NIEUWE klant 99999999 toevoegen */
    *l(80,1)=LogHeader.rec_pos+a*LogHeader.rec_len;
    pslin=(struct _fas_s_lijn *)(s(80,1)+4);
    fasseqi(80,1,sizeof *pslin+4);
    if(bit(pslin->bits,7)==NO || bit(pslin->bits,6)){
      if(bit(pslin->bits,6) && a!=r_beg) break;/* begin nieuw ticket (x40) */
    }
    if(bit(pslin->bits,7)){
      if(cmpstr(s(80,1)+5,"Klantnr.: 99999999",18)==0){add_klt(a+1,YES);break;}
    }
  }
  return off_;
}
 

static int add_klt(long pos_, int16 keep_klt_)
{
  int16 k;
  long min_kod_,max_kod_,lbd_;
 
  copy(s(2,1),buf1000,fldlen(2,0));
  fasinit(2);
  if(fldlen(2,2)){/* automatisch codenummer zoeken 9xxxx */
    max_kod_=9;min_kod_=9; for(k=0;k<fldlen(2,2)-1;k++) {min_kod_*=10;max_kod_=max_kod_*10+9;}
    for(lbd_=min_kod_;lbd_<max_kod_;lbd_++){
      fasinit(2);
      stcli_d(s(2,2),lbd_,fldlen(2,2),0);
      if(faskeyi(2,1,0)) break;
    }
  }
  fasinit(80);
  for(k=0;k<6;k++){/* NIEUWE klant 99999999 toevoegen */
    *l(80,1)=LogHeader.rec_pos+(pos_+k)*LogHeader.rec_len;
    fasseqi(80,1,21+4);
    switch(k){
      case 0 : *l(2,10)=String2BtwNr(s(80,1)+5+9,11); break;
      case 1 : copy(s(80,1)+5,s(2,3),20); break;
      case 2 : copy(s(80,1)+5,s(2,3)+20,20); break;
      case 3 : copy(s(80,1)+5,s(2,4),20); break;
      case 4 : copy(s(80,1)+5,s(2,4)+20,10); break;
      case 5 : copy(s(80,1)+5,s(2,5),7);
	       copy(s(80,1)+5+8,s(2,6),12); break;
      case 6 : copy(s(80,1)+5,s(2,6)+12,8); break;
      default : break;
    }
  }
  if(fldlen(2,36)) *u(2,36)=def_qfak;
  if(fldlen(2,25)) *s(2,25)='0';
  *s(2,26)=sys3896[0];
  k=fasadd(2);
  if(keep_klt_==YES) copy(buf1000,s(2,1),fldlen(2,0));
  return k;
}

static long String2BtwNr(char *ps, int16 len_)
{
  int16 k;
  long btw_nr;
						
  if(len_>13) len_=11; 
	btw_nr=0;
  for(k=0;k<len_;k++) {
    if(*ps>='0' && *ps<='9') btw_nr=btw_nr*10+*ps-'0';
    ps++;
  }
  return (long)btw_nr;
}

static int bit(char byte_, int16 bit_)
{
  if(byte_ & 1<<bit_) return YES;
  return NO;
}

static void _sta_upd(uint16 rec_, uint16 knr_, float *qlv_, float *bd_, uint16 kol_)
{
  flag add_rec_;
  float bda_;
  fasinit(6);*pu_6_1=rec_;fasgeti(6);
  if(fldlen(6,76) && *s(6,76)!='J') goto endsr;
  fasinit(60);*l(60,22)=rec_;*l(60,2)=loc_klt[knr_-1];
  if(*l(60,2)==0 || knr_<1) *l(60,2)=klt_div1;
  if(faskeyu(60,1,0)) add_rec_=YES;
  else add_rec_=NO;
  if(fldlen(60,24)) *i(60,24)=*i(6,9);
  if(fldlen(60,25)) *u(60,25)=*u(6,7);
  copy(s(6,2),s(60,23),fldlen(6,2));
  bda_=*qlv_* *f(6,18);
  stu_add(60,52+kol_,&bda_);/* ak-waarde */
  stu_add(60,82+kol_,bd_);/* vk-waarde */
  stu_add(60,112+kol_,qlv_);/* aantal */
  if(add_rec_) errnum=fasadd(60);
  else errnum=fasupd(60);
  if(errnum){
    if(errnum==48||errnum==49)errnum=9;
    scrget(1,170);
    scrifld(5,fm_os63,"    Fout tijdens het bijwerken van de statistieken.");
    scrifld(10,fm_os63,"Druk F8 om verder te gaan");
    scrupd(-1,0x80);
    scrget(1,7);scrupd(-3,0);
  }
  endsr:;
}

static void _his_upd(uint16 rec_, uint16 knr_, float *qlv_, float *bd_, uint16 dt_)
{
  int16 jj,mm,dd;
  flag add_rec_;
  long ft_nr_;

  if(fldlen(16,1)==0) goto endsr;

  jddate(dt_,&jj,&mm,&dd);
	ft_nr_=knr_*1000000L;
  ft_nr_+=(long)(jj%100)*10000+mm*100+dd;
  fasinit(6);*pu_6_1=rec_;if(fasgeti(6)) goto endsr;
  if(fldlen(6,76) && *s(6,76)!='J') goto endsr;
 
  fasinit(16);*l(16,20)=rec_;*l(16,10)=loc_klt[knr_-1];*l(16,2)=ft_nr_;*u(16,3)=dt_;
  if(*l(16,10)==0 || knr_<1) goto endsr;/* klant MOET ingevuld zijn */
  if(faskeyu(16,HisCheckKey,0)) add_rec_=YES;
  else add_rec_=NO;
  *l(16,2)=ft_nr_;
  *u(16,3)=dt_;
  if(fldlen(16,8)) *u(16,8)=loc_nr[knr_-1]; // filiaalnr
  *l(16,10)=loc_klt[knr_-1]; if(fldlen(16,12)) *l(16,12)=*l(16,10);
  *l(16,20)=*pu_6_1;
  copy(s(6,2),s(16,21),fldlen(16,21));
  copy(s(6,3),s(16,22),fldlen(16,22));
  *l(16,23)=*u(6,9);/* groep */
	if(fldlen(6,103) && fldlen(16,28)) *u(16,28)=*u(6,103); // subgroep
  *f(16,24)=*f(6,28);/* BTW% */
  copy(s(6,10),s(16,25),fldlen(16,25));/* eenheid */
  if(fldlen(6,31)) *f(16,26)=*f(6,31);/* q_bak */
  if(fldlen(6,30)) *f(16,27)=*f(6,30);/* accijns */
  *d(16,30)+=*qlv_;
  *d(16,31)+=*bd_;
  *d(16,32)+=Round((double)(*qlv_* *f(6,18)),(double)(0.01));
  if(add_rec_) errnum=fasadd(16);
  else errnum=fasupd(16);
  if(errnum){
    if(errnum==48||errnum==49)errnum=9;
    scrget(1,170);
    scrifld(5,fm_os63,"    Fout tijdens het bijwerken van de historieken.");
    scrifld(10,fm_os63,"Druk F8 om verder te gaan");
    scrupd(-1,0x80);
    scrget(1,7);scrupd(-3,0);
  }
  endsr:;
}

static void _kaart_his_upd(uint16 rec_, uint16 knr_, float *qlv_, float *bd_, uint16 dt_)
{
  int16 jj,mm,dd;
  flag add_rec_;
  long ft_nr_;

  jddate(dt_,&jj,&mm,&dd);
	ft_nr_=knr_*1000000L;
  ft_nr_+=(long)(jj%100)*10000+mm*100+dd;
  fasinit(6);*pu_6_1=rec_;if(fasgeti(6)) goto endsr;
 
  fasinit(97);*l(97,20)=rec_;*l(97,10)=kaartnr;*l(97,2)=ft_nr_;*u(97,3)=dt_;
  if(*l(97,10)==0) goto endsr;/* klant MOET ingevuld zijn */
  if(faskeyu(97,1,0)) add_rec_=YES;
  else add_rec_=NO;
  *l(97,2)=ft_nr_;
  *u(97,3)=dt_;
  *l(97,10)=kaartnr;
  *l(97,20)=*pu_6_1;
  copy(s(6,2),s(97,21),fldlen(97,21));
  copy(s(6,3),s(97,22),fldlen(97,22));
  *l(97,23)=*u(6,9);/* groep */
  *f(97,24)=*f(6,28);/* BTW% */
  copy(s(6,10),s(97,25),fldlen(97,25));/* eenheid */
  if(fldlen(6,31)) *f(97,26)=*f(6,31);/* q_bak */
  if(fldlen(97,27) && fldlen(6,30)) *f(97,27)=*f(6,30);/* accijns */
  *d(97,30)+=*qlv_;
  *d(97,31)+=Round((double)(*bd_),(double)(0.01));
  *d(97,32)+=Round((double)(*qlv_* *f(6,18)),(double)(0.01));
  if(add_rec_) errnum=fasadd(97);
  else errnum=fasupd(97);
  if(errnum){
    if(errnum==48||errnum==49)errnum=9;
    scrget(1,170);
    scrifld(5,fm_os63,"    Fout tijdens het bijwerken van de historieken.");
    scrifld(10,fm_os63,"Druk F8 om verder te gaan");
    scrupd(-1,0x80);
    scrget(1,7);scrupd(-3,0);
  }
  endsr:;
}

static void stu_add(int16 stu_, int16 elet_, float *pf1)
{
  if(fldlen(stu_,elet_)){
    *f(stu_,elet_)+=*pf1;
  }
}

static int ask_in_dt(char *ptxt, flag only1kas, flag ask_stock)
{
  int16 z,j,k,key,curs=3,keymask_;
  char str_[50];
	uint16 dt_;
								
  upd_stock='J'; if(add_ftvk=='\0') add_ftvk='J';wis_eerst=YES;
  chk_dtkvk=YES;
  keymask_=0x681; if(ask_stock) keymask_=0x781;
  if(sys3978) upd_stock='N';
							
	for(k=0;k<10;k++) if(nm_kassa[k][0]) break;  if(k>=10) k=0;
	inq_kassa=0;if(max_kassa==1) inq_kassa=k+1;
  if(ask_stock && dat_beg==0 && inq_kassa==k+1) dat_beg=dt_kvk[k]+1;
  if(dat_beg==0 && ask_stock==NO) dat_beg=*u(25,2);
  if(dat_end==0) dat_end=dat_beg;
  FOREVER{
    redo:;
    if(ask_stock) scrget(3,308); else scrget(3,94);z=1;
    scrifld(z++,fm_os38,ptxt);
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&inq_kassa);
    if(ask_stock){
      z++;
      scrifld(z++,fm_uJN,&upd_stock);
			for(k=0;k<10;k++) {
	  		if(nm_kassa[k][0]){
					scrifld(z++,fm_os6,&nm_kassa[k][0]);
					scrifld(z++,fm_odat,&dt_kvk[k]);
					fasclos(-2);fasinit(80);
					MakeKaslogName(k+1,dat_end);
					fasopen(filnam,102);/* eerste call voor dir */
					fasinfo(80,204);/* ophalen antwoord van dir */
					if(*s(80,1)){
						fasinit(80);fasinfo(80,205);/* get date  */
						scrifld(z++,fm_os20,s(80,1));
						fasclos(-2);
						if (LogOpenKaslog(filnam)){
							scrifld(z++,fm_odat,&LogDag[0].datum);
							scrifld(z++,fm_odat,&LogDag[LogDagUsed-1].datum);
							FilKaslog.Close();
						} else z+=2;
					} else z+=3;
				} else z+=5;
			}
    }
    else{
      if(only1kas==NO && ft_off>0) scrifld(z++,fm_uJN,&add_ftvk);
      else z++;
      z++;
      for(k=0;k<5;k++) {
				scrifld(z++,fm_os6,&nm_kassa[k][0]);
				scrifld(z++,fm_odat,&dt_kvk[k]);
				scrifld(z++,fm_os6,&nm_kassa[k+5][0]);
				scrifld(z++,fm_odat,&dt_kvk[k+5]);
      }
    }
    key=scrupd(curs,keymask_);curs=3;
    chk_dtkvk=YES;
    if(key==111) ovlexit(-1);
    if(key==101) return YES;
    if(dat_beg==0 && ask_stock){curs=3;errnum=38;goto redo;}
    if(dat_end==0 || dat_end<dat_beg){curs=4;errnum=38;goto redo;}
    if(only1kas && inq_kassa==0){curs=5;errnum=38;goto redo;}
    if(inq_kassa && (fldlen(91,11+(inq_kassa-1)*5)==0 || nm_kassa[inq_kassa-1][0]=='\0')){
      curs=5;errnum=34;goto redo;
    }
    if(ask_stock){ // inlezen verkopen
      if(key==109){
				if(inq_kassa==0){curs=5;errnum=38;goto redo;}
				chk_dtkvk=NO;
      }
      if(chk_dates()) {curs=3;goto redo;}
			if(CheckKaslogDate()) {curs=4;goto redo;} // is er een recente kaslog?
    }
    wis_eerst=YES;
    if(key==108 || key==109) break;
    if(key==110) {wis_eerst=NO;break;}
  }
  if(dat_end==0) dat_end=0xFFFF;
  return NO;
}

static int CheckKaslogDate(void)
{
	int16 k,jj,mm,dd,max_,key;
	char str_[80];
	SYSTEMTIME st_,fsystime_;
	WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
  FILETIME MinFtimeEnd,loc_ftime_;
	 
	GetLocalTime(&st_);
	jddate((int)(dat_end),&jj,&mm,&dd);
	st_.wDay=dd;st_.wMonth=mm;st_.wYear=jj;st_.wHour=17;st_.wMinute=50;SystemTimeToFileTime(&st_,&MinFtimeEnd);
	
	k=1; max_=10; if(inq_kassa){k=inq_kassa; max_=inq_kassa;}
  for(k;k<=max_;k++){
    if(nm_kassa[k-1][0]=='\0') continue;
		if(inq_kassa && k!=inq_kassa) break;
		if(sluitingsuur[k-1]==0) continue;
		st_.wHour=sluitingsuur[k-1]/60;st_.wMinute=sluitingsuur[k-1]%60;st_.wSecond=0;SystemTimeToFileTime(&st_,&MinFtimeEnd);
		MakeKaslogName(k,dat_end);
    hSearch = FindFirstFile (filnam, &FileData);
    if (hSearch != INVALID_HANDLE_VALUE){
			FindClose(hSearch);
			FileTimeToLocalFileTime(&FileData.ftLastWriteTime,&loc_ftime_); // eerst in locale tijd zetten 
			if (CompareFileTime(&loc_ftime_,&MinFtimeEnd)<0) { // voor de gewenste periode 
				FileTimeToSystemTime(&loc_ftime_,&fsystime_); 
				zero(str_,sizeof str_);
				sprintf(str_," %d/%d/%d %d:%d ",(int)fsystime_.wDay,(int)fsystime_.wMonth,(int)fsystime_.wYear,(int)fsystime_.wHour,(int)fsystime_.wMinute);
				scrget(1,170);
  			scraddf(100,23,0,8); scrifld(100,VarTextFmt(7,0)," F4 Ja ");
				scraddf(101,23,8,8); scrifld(101,VarTextFmt(8,0)," F5 Nee ");
    		scraddpicto(1,0,32,1,12,6,605,0,0,"Opgelet!"); 
				scraddfield(150,20,8,0x3);scrifld(150,VarTextFmt(23,0),"Datum verkopenbestand :");
				scraddfield(151,43,8,0xC);scrifld(151,VarTextFmt(17,0),str_);
				sprintf(str_,"Het verkopenbestand van de kassa is NIET recent! (ouder dan %d:%02d)!",(int)sluitingsuur[k-1]/60,(int)sluitingsuur[k-1]%60);
				scraddfield(152,1,10,0x2);scrifld(152,VarTextFmt(79,0),str_);
				scraddfield(153,1,12,0x2);scrifld(153,VarTextFmt(79,0),"Indien U hier verder gaat, kunnen sommige verkopen ONTBREKEN.");
				scraddfield(154,1,14,0x2);scrifld(154,VarTextFmt(79,0),"Bij twijfel, neem F5, stuur opnieuw door met de kassa en lees opnieuw in.");
				scraddfield(155,1,17,0x2);scrifld(155,VarTextFmt(79,0),"Wenst U toch deze periode in te lezen?");
				key=scrupd(-1,0x18);
				if(key!=104) return YES;
			}
		}
	}
  return NO;
}

static int chk_dates(void)
{
  int16 k,max_;
  uint16 dt_,dt_beg_,dt_end_;
  scrget(1,7);scrupd(-3,0);
  dt_beg_=dat_beg;dt_end_=dat_end;
  k=1; max_=10; if(inq_kassa){k=inq_kassa; max_=inq_kassa;}
								
  for(k;k<=max_;k++){
    if(nm_kassa[k-1][0]=='\0') continue;
    dt_beg_=dat_beg;dt_end_=dat_end;
    if(chk_dtkvk && dt_kvk[k-1]+1 > dt_beg_){
      if(inq_kassa) {errnum=34;return YES;}
      else  dt_beg_=dt_kvk[k-1]+1;
    }
    if(dt_beg_>dt_end_) continue;
    for(dt_=dt_beg_;dt_<=dt_end_;dt_++){
      fasinit(91);*pu_91_3=dt_;
      if(faskeyi(91,1,0)==0){
	if(*f(91,11+(k-1)*5)) break;
      }
    }
    if(dt_<=dt_end_){
      if(scr_ok("U heeft reeds verkopen ingelezen in deze periode ... overschrijven ???")==NO) return YES;
      else return NO;
    }
  }
  return NO;
}

static void update(void)
{
  int16 key;
  uint16 dt_;
  dt_=0;
  FOREVER{
    if(!errnum){fasinit(6);fasinit(91);}
    *pu_91_3=dt_;
    redo:;
    scrget(3,142);
    scrfld(1,25,1);
    scrfld(2,6,3);
    scrfld(3,91,3);
    key=scrupd(2,0x0481);
    if(key==101) break;
    if(key==111) ovlexit(-1);
    if(search(6,0)) goto redo;
    *pu_91_2=*pu_6_1;if(faskeyi(91,1,0)){errnum=39;goto redo;}
    dt_=*pu_91_3;
    if(!fichupd(1)) break;/* fasupd */
  }
}

static void add(void)
{
  int16 key;
  uint16 dt_;
									
  dt_=0;
  FOREVER{
    if(!errnum){fasinit(6);fasinit(91);}
    *pu_91_3=dt_;
    redo:;
    scrget(3,142);
    scrfld(1,25,1);
    scrfld(2,6,3);
    scrfld(3,91,3);
    key=scrupd(2,0x0481);
    if(key==101) break;
    if(key==111) ovlexit(-1);
    if(search(6,0)) goto redo;
    *pu_91_2=*pu_6_1;if(fasadd(91)){errnum=39;goto redo;}
    dt_=*pu_91_3;
    if(!fichupd(1)) break;                                        /* fasupd */
  }
}

static int wissen(void)
{
  uint16 dt_;
  if(ask_in_dt("Wissen van de verkopen",NO,NO)) return NO;
  if(scr_ok("Wenst U echt de verkopen te wissen ???")==NO) return NO;
  for(dt_=dat_beg; dt_<=dat_end;dt_++) wis_fld(dt_,inq_kassa,NO,YES);
	return YES;
}

static void wis_fld(uint16 dt_, uint16 nr_, uint16 corr_stock_,uint16 disp_)
{
  int16 mode,j,k,kill_,jj,mm,dd;
  float bdf_,qlv_,qbak_,q_stk_;
  long ft_nr_;
 
 
	if(disp_){
    scrget(1,170);
    if(corr_stock_ && upd_stock=='J') scrifld(5,fm_os63,"Controleren/rechtzetten bestaande verkopen :");
    else scrifld(5,fm_os63,"Wissen bestaande verkopen :");
    scrifld(6,fm_udat,&dt_);scrupd(-3,0);
  }
  j=0;for(k=0;k<10;k++) if(fldlen(91,11+k*5)) j++;
  if(ft_off) j--;
  kill_=NO; if(j<=1 || nr_==0) kill_=YES;
  fasinit(91);*pu_91_3=dt_;mode=1;
  jddate(dt_,&jj,&mm,&dd);
  FOREVER{
    if(faskeyu(91,2,mode)) break;mode=2;
    if(dt_!=*pu_91_3) break;
    if(corr_stock_ && upd_stock=='J' && nr_){
      fasinit(6);*pu_6_1=*pu_91_2;fasgeti(6);
      if(*f(91,11+(nr_-1)*5)){															// correctie contante verkopen 
				bdf_=*f(91,13+(nr_-1)*5); bdf_=bdf_ / (1.+ *f(6,28)/100.);
				qlv_=*f(91,11+(nr_-1)*5);
				qlv_=-qlv_;bdf_=-bdf_;
				up_a_stock(*pu_6_1,nr_,0,qlv_,bdf_);
				if(fldlen(60,1) && (sys3772 & 0x10)){
					_sta_upd(*pu_6_1,nr_,&qlv_,&bdf_,mm); // particuliere verkoop corrigeren
				}
				// niet doen, want leeggoed van volgoed wordt niet weggeschreven
				//if(fldlen(6,41) && *s(6,41)){ // automatisch leeggoed positief terugcorrigeren owv negatief via fiches
				//	qlv_=*f(91,11+(nr_-1)*5);
				//	Aantal2Stuks(qlv_,*f(6,31),&qbak_,&q_stk_);
				//	if(qbak_){
				//		copy(s(6,41),s(6,2),fldlen(6,2));
				//		if(faskeyi(6,1,0)==0){
				//			up_a_stock(*pu_6_1,nr_,0,qbak_,*f(6,25)*qbak_);
				//		}
				//		fasinit(6);*pu_6_1=*pu_91_2;fasgeti(6);
				//	}
				//	if(q_stk_){
				//		copy(s(6,44),s(6,2),fldlen(6,2));
				//		if(faskeyi(6,1,0)==0){
				//			up_a_stock(*pu_6_1,nr_,0,q_stk_,*f(6,25)*q_stk_);
				//		}
				//		fasinit(6);*pu_6_1=*pu_91_2;fasgeti(6);
				//	}
				//}
      }
      if(ft_off && fldlen(91,11+(nr_-1+ft_off)*5)) {				// correctie te factureren verkopen 
				bdf_=*f(91,13+(nr_-1+ft_off)*5); bdf_=bdf_ / (1.+ *f(6,28)/100.);
				qlv_=*f(91,11+(nr_-1+ft_off)*5);
				qlv_=-qlv_;bdf_=-bdf_;
				up_a_stock(*pu_6_1,nr_,0,qlv_,bdf_);
				// NIET doen, want leeggoed van volgoed wordt niet bijgewerkt
				//if(fldlen(6,41) && *s(6,41)){ // automatisch leeggoed positief terugcorrigeren owv negatief via fiches
				//	qlv_=*f(91,11+(nr_-1+ft_off)*5);
				//	Aantal2Stuks(qlv_,*f(6,31),&qbak_,&q_stk_);
				//	if(qbak_){
				//		copy(s(6,41),s(6,2),fldlen(6,2));
				//		if(faskeyi(6,1,0)==0){
				//			up_a_stock(*pu_6_1,nr_,0,qbak_,*f(6,25)*qbak_);
				//		}
				//		fasinit(6);*pu_6_1=*pu_91_2;fasgeti(6);
				//	}
				//	if(q_stk_){
				//		copy(s(6,44),s(6,2),fldlen(6,2));
				//		if(faskeyi(6,1,0)==0){
				//			up_a_stock(*pu_6_1,nr_,0,q_stk_,*f(6,25)*q_stk_);
				//		}
				//		fasinit(6);*pu_6_1=*pu_91_2;fasgeti(6);
				//	}
				//}
				// factuurverkoop wordt normaal niet opgenomen, enkel met B6 corrigeren 
       	if(fldlen(60,1) && (sys3772 & 0x10) && (sys3772 & 0x60)){
					_sta_upd(*pu_6_1,nr_,&qlv_,&bdf_,mm);
				}
      }
    }
    if(kill_==NO){
      *f(91,11+(nr_-1)*5)=0;
      *f(91,12+(nr_-1)*5)=0;
      *f(91,13+(nr_-1)*5)=0;
      if(ft_off && fldlen(91,11+(nr_-1+ft_off)*5)) {
				*f(91,11+(nr_-1+ft_off)*5)=0;
				*f(91,12+(nr_-1+ft_off)*5)=0;
				*f(91,13+(nr_-1+ft_off)*5)=0;
      }
      fasupd(91);
    }
    else faskill(91);
  }
	if(fldlen(16,1) && corr_stock_ && upd_stock=='J' && nr_){ // historiek  deleten 
    jddate(dt_,&jj,&mm,&dd);ft_nr_=nr_*1000000L; ft_nr_+=(long)(jj%100)*10000+mm*100+dd;
    fasinit(16);*l(16,2)=ft_nr_;*u(16,3)=dt_;mode=1;
		FOREVER{
			if(faskeyi(16,3,mode)) break; mode=2;
			if(*l(16,2)!=ft_nr_) break;
			faskill(16);
		}
	}
	if(fldlen(97,1) && corr_stock_ && upd_stock=='J' && nr_){ // historiek klantenkaarten deleten 
    jddate(dt_,&jj,&mm,&dd);ft_nr_=nr_*1000000L; ft_nr_+=(long)(jj%100)*10000+mm*100+dd;
    fasinit(97);*l(97,2)=ft_nr_;*u(97,3)=dt_;mode=1;
		FOREVER{
			if(faskeyi(97,3,mode)) break; mode=2;
			if(*l(97,2)!=ft_nr_) break;
			faskill(97);
		}
	}
  fasflush(0);
}

static void MoveForNewKassa(void)
{
	int16 max_off_,mov_off_,k,g,len_;
	char buf_[100];
	long n;

  sysget(3974,2,&ft_off);
	for(max_off_=0;max_off_<20;max_off_++) if(fldlen(91,11+max_off_*5)==0) break;
	max_off_/=2;
  if(max_off_<=ft_off) goto endsr;
	sprintf(buf_,"Wenst U echt de kassa's uit te breiden van %d --> %d ?",ft_off,max_off_);
	if(DisplayWarning(buf_,605)!=YES) goto endsr;
	len_=s(91,16)-s(91,11);mov_off_=max_off_-ft_off;
	fasinit(91);n=0;kdsp=0;
	scrget(1,7);scraddf(200,23,78,0);
	FOREVER{
    *l(91,1)=++n;
		if((n%500)==0){scrifld(200,fm_os1,&dsp_kar[kdsp++]);scrupd(-3,0); if(kdsp==4) kdsp=0;} 
    g=fasgeti(91);
    if(g==47)break;
    if(g!=46){        
  		for(k=ft_off-1;k>=0;k--){
	  		copy(s(91,11+(k+ft_off)*5),s(91,11+(k+max_off_)*5),len_); zero(s(91,11+(k+ft_off)*5),len_);
	  	}
	  	fasupd(91);
		}
	}
  ft_off=max_off_;sysput(3974,2,&ft_off);
	endsr:;
}

static void Aantal2Stuks(float aantal_,float qst_,float *bakken_,float *stuks_)
{
	int neg_=NO;

	if(aantal_<0){aantal_=-aantal_;neg_=YES;}
  if(qst_<1) qst_=1;
  *bakken_=(long)(aantal_); *stuks_=0;
  if(qst_>1 && aantal_>0){
    *stuks_=(long)(((aantal_- *bakken_) * qst_)+0.49);
  } else *stuks_=0;
	if(neg_){*bakken_=-*bakken_;*stuks_=-*stuks_;}
}



static int fichupd(int16 mode)
{
  int16 k,curs=2,key,z;
  char *p_stu_3;
 
  p_stu_3=s(6,3);
  FOREVER{
    scrget(3,129);z=1;
    scrfld(z++,25,1);
    scrofld(z++,6,2,-1);
    scrofld(z++,6,3,-1);
    scrofld(z++,91,3,-1);
    for(k=0;k<10;k++){
      scrfld(z++,91,11+k*5);
      scrfld(z++,91,12+k*5);
      scrfld(z++,91,13+k*5);
    }
    key=scrupd(curs,0x00A1);curs=2;
    if(key==106) return YES;
    errnum=fasupd(91);fasflush(0);
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
  return YES;
}

static int cmp_str(char *p1, char *p2, int16 len)
{
  while(len--){
    if(*p1++!=*p2++)return 1;
  }
  return 0;
}

static void nextline(void)
{
  linfree=prtline();
}

static double Round(double getal, double bd_afr_)
{
 double wrk1_,wrk2_,add_,result_;
 
	add_=(double)(0.5);result_=getal;
  if(result_<0) add_=-add_;
  if(bd_afr_>0.00001){
    if(bd_afr_<=1.){
      wrk1_=(long int)result_;
      wrk2_=result_-wrk1_;
    } else{wrk1_=0.;wrk2_=result_;}
    wrk2_=(double)((int)((wrk2_/bd_afr_)+add_)) * bd_afr_;
    result_=wrk1_+wrk2_;
  }
  return (double)(result_);
}

static int is_nul(double bd_)
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return 1;
  else return 0;
}



static void streepje(int16 fldnr)
{
  scrifld(fldnr,fm_os1,"-");
}
 

static void initload(void)
{
  int16 g,j,k,nr_;
	  
  fasunlck(0);
  for(k=1;k<=6;k++) fileopen(k);
  fileopen(9);
  if(fldlen(66,1)) fileopen(12);
  if(fldlen(92,1)) fileopen(11);
	if(fldlen(16,1)) fileopen(13);		
  sysget(  34,256,firma);
  sysget(294,4,def_munt);
	sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);
  sysget(1048,32,&btw_pct[0]);
	sysget(1084,4,&def_btw);
  sysget(1790,2,&sys1790);
	sysget(1804,2,&sys1804);
  sysget(1918,2,&sear_stt);
  sysget(2166,2,&VKjournl);
  sysget(2216,2,&klt_div1); if(klt_div1==0) klt_div1=1;
  sysget(2222,2,&def_qfak);
  sysget(2727,2,&sys2727);
  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
	for(j=0;j<8;j++) if(def_btw==btw_pct[j]) break;
	if(j<8) ArtOnbekend=TbDiversArtikel[j];
  sysget(3024,20,(char *)&sluitingsuur[0]);
	sysget(3598,6,b3598);
  sysget(3604,2,&b3604);
  sysget(3606,2,&b3606);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
	sysget(3636,4,&grb_notf);
  sysget(3772,2,&sys3772);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,&sys3896[0]);
  sysget(3974,2,&ft_off);
  sysget(4338,3,kas_munt);
  sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4254,40,(char *)&dt_kvk[0]);
  sysget(4294,40,(char *)&loc_klt[0]);
  sysget(4400,2,&sys4400);
  sysget(4408,2,&sys4408);
	sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  sysget(8000,60,NaamVarBetWijze); 
	for(k=0;k<3;k++) {
		if(NaamVarBetWijze[k][0]=='\0') copy("Var.Bet.wijze",NaamVarBetWijze[k],15);
		FinGroepNaam[32+k]=NaamVarBetWijze[k];
	}
		
	for(k=0;k<80;k++){
    sysget(10240+k*80,2,&g);
    sysget(10242+k*80,2,&j_tab[g]);
  }
	sysget(18500,1,&KV_ExtraScherm);
	sysget(18501,1,&KV_ToonBoekscherm);
	sysget(18502,1,&KV_BoekVoldaneFactuurOpKlant);
	sysget(18503,6,KV_AfwijkendeGrbPrefix);
	sysget(18510,20,KV_KasJournaal);
  sysget(18530,80,KV_GrbFinDet);
	sysget(18610,4,&KV_GrbFondsoverdracht);
	sysget(18614,4,&KV_GrbAfrondingsverschillen);
	if(sys1804){
		for(k=0;k<15;k++){
			sysget(788+k*4,4,&df_grb[k]);
			df_recnr[k]=getgrb(*(long *)&df_grb[k]);
		}
	}
  sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);

  if(ft_off && fldlen(91,11+(ft_off*5))==0) ft_off=0;
	j=0;
  for(max_kassa=0;max_kassa<10;max_kassa++){
    if(fldlen(91,11+(max_kassa*5))==0) break;
    if(fldlen(91,11+((max_kassa+ft_off)*5))==0) break;
		if(nm_kassa[max_kassa][0]) j++;
  }
	if(ft_off && max_kassa>ft_off) max_kassa=ft_off; // veiligheid voor ft_offset
	if(j<=1) max_kassa=1; // meer velden, maar geen naam ingevuld
  sysget(3978,2,&sys3978);/* geen artikelfiche updaten */
  zero((char *)&tb_ktypes[0],sizeof tb_ktypes); max_kprx=0;
  for(k=0;k<6;k++){
    if(sys3896[k]){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
				tb_ktypes[max_kprx++]=nr_;
      }
    }
  }



  len6_155=fldlen(6,155);
  use_kaart=NO; if(fldlen(92,30) && ovltest(294)) use_kaart=YES;
  if(fldlen(6,130) && fldlen(25,8) && *u(25,8)) prx_loff=*u(25,8);
  else prx_loff=0;
  if(fldlen(16,1)){
		fileopen(13);
		HisCheckKey=5; if(faskeyi(16,5,1)==45) HisCheckKey=1;
	}
  if(fldlen(60,1)) fileopen(14);
  sysget(3678,2,&def_taal);
  pu_6_1=u(6,1);
  pf_6_28=f(6,28);
  pu_91_2=u(91,2);
  pu_91_3=u(91,3);
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;
  zero((char *)&tbgr[0].rec,sizeof tbgr);
  p_max_grp=0;sgrp_used=NO;
  for(k=1;k<100;k++){
    fasinit(52);*u(52,1)=k;
    g=fasgeti(52);
    if(g==0 && *s(52,14)) tbgr[p_max_grp++].rec=k;
  }
  for(k=0;k<100;k++) tbgr[k].select='J';
  for(k=0;k<6;k++){
    if(k==0 || btw_pct[k]){
      j=btw_pct[k];g=btw_pct[k]*10-j*10;
      stcli_d(&btwhfd[k][0],(long)j,2,1);
      copy(",",&btwhfd[k][2],1);
      stcli_d(&btwhfd[k][3],(long)g,1,0);
      copy(" %",&btwhfd[k][4],3);
    }
  }
	copy("-X|/",dsp_kar,4);dsp_kar[1]=0x5C;
}

static uint16 getgrb(long lgrb)
{
  uint16 retcd=0;

  if(*(char *)&lgrb!=0xFF && *(char *)&lgrb!=0x00){
    *l(3,2)=lgrb;
    *u(3,1)=0;
		if(faskeyi(3,1,0)) fasinit(3);
    else retcd=*u(3,1)+60000;
  }
  return retcd;
}

static uint16 hash(char *ps, int hash_len)
{
  int16 k;
  uint16 fuval=0;
					
  k=hash_len;
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
}


static long GetRecNr(int16 stu_)
{
	 
	if(fldlen(stu_,1)==2) return (long)(*u(stu_,1));
	else return (long)(*l(stu_,1));
}

static void SetRecNr(int16 stu_, long val_)
{
	if(fldlen(stu_,1)==2) *u(stu_,1)=val_;
	else *l(stu_,1)=val_;
}

static char *Asc2Jasc(char *ps_,int16 len_)/* convert KASSA-ascii to jama-ascii */
{
  int j,k;
  char kar_;

  for(k=0;k<len_;k++){
    kar_=*(ps_+k);  j=kar_;
    switch(j){
      case 176 : kar_=150; break;
      case 224 : kar_=133; break;
      case 232 : kar_=134; break;
      case 233 : kar_=133; break;
      case 231 : kar_=132; break;
			case 234 : kar_=138; break;
      case 244 : kar_=143; break;
      case 235 : kar_=136; break;
      case 214 : kar_=142; break;
      case 163 : kar_=150; break;
			case 128 : kar_=159; break; // eur teken
      default  : break;
    }
    *(ps_+k)=kar_;
  }
	return ps_;
}

static int fmt_get(int16 stu_, int16 elet_)
{
  int16 k;
  char *pdum,dummy_[10];
					
  pdum=&dummy_[0];
  k=fieldspc(stu_,elet_,&pdum,fmt);
  if(k>0) return k;
  return 0;
}
 

static int ele_len(int16 nr_)
{
  int16 k=0;
  char *p;
  p=rec_ele(nr_);
  FOREVER{
    if(*p=='|' || *p==0x0D || *p==0x0A || *p=='\0') return k;
    p++;k++;
  }
}
 

static char *rec_ele(int16 nr_)
{
  int16 k;
  char *p;
  p=p_data;
  for(k=0;k<nr_;k++){
    FOREVER{
      if(*p=='|' || *p==0xD || *p=='\0') break;
      p++;
    }
    p++;
  }
  return p;
}
 

static int read_rec(int16 mode_)
{
  int16 j;
  flag eof_=NO;
  long pos_;
  if(mode_){
    for(j=0;j<256;j++) if(*(p_data+j)==0x0A || *(p_data+j)=='\0') break;
    if(*(p_data+j)==0x0A || *(p_data+j)=='\0') *pl_80_1+=(j+1);
    zero(p_data,256);
  }
  pos_=*pl_80_1;
  if(fasseqi(80,1,256)) {eof_=YES;}
  if(eof_ && *p_data=='\0') return YES;
  else{/* positioneer terug op eerste karakter */
    *pl_80_1=pos_;
    return NO;
  }
}
 

static float get_num(int16 nr)/* read number starting at pos  */
{
  int16 j=0,k=0,n;
  float val_=0,val1_;
  flag na_komma=NO,neg_get=NO;
  char *pos;
 
  pos=rec_ele(nr);
  FOREVER{
    if(*(pos+k)=='|' || *(pos+k)==0x0D) break;
    if(*(pos+k)=='.') na_komma=YES;
    else if(*(pos+k)=='-') neg_get=YES;
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
	if(na_komma==NO){
	  val_=val_*10 + (*(pos+k)-'0');
	}
	else{
	  j++;
	  val1_=*(pos+k)-'0';
	  for(n=0;n<j;n++) val1_=val1_/10;
	  val_+= val1_;
	}
      }
    }
    k++;
  }
  if(neg_get) return (float) -val_;
  else return (float) val_;
}

static void mk_name(uint16 adr_pref, char *ps)
{
  char *pd;
  zero(filnam,sizeof filnam); pd=filnam;
  sysget(adr_pref,16,pd);
  while(*pd) pd++;
  while(*ps!='\0') *pd++=*ps++;
}

static void fileopen(int16 nr_)
{
  int16 stu_,k;
  char filename[15];
  k=300+17*(nr_-1);
  sysget(k,15,filename);
  sysget(k+15,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(errnum=fasopen(filename,0)) ovlexit(-1);
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  }
}
 

static int scr_ok(char *ptxt)
{
  int16 key;
  scrget(1,169);
  scrifld(12,fm_os80,ptxt);
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  return NO;
}
 

static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_)
{
  int16 pos_,slen_,len_,dd,mm,yy;
  char buf_[30],string[100];
				
  zero(string,sizeof string);
  for(slen_=0;slen_<50;slen_++){
    if(naam_[slen_]=='\0') break;
    string[slen_]=naam_[slen_];
  }
  if(dt_beg_){
    string[slen_++]=' ';
    jddate(dt_beg_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[slen_],(long)dd,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)mm,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)yy,2,0);slen_+=2;
  }
  if(dt_end_){
    if(dt_beg_){copy(" - ",&string[slen_],3);slen_+=3;}
    jddate(dt_end_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[slen_],(long)dd,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)mm,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)yy,2,0);slen_+=2;
  }
  for(dd=0;dd<slen_;dd++) if(string[dd]=='\\' || string[dd]=='/') string[dd]='-';
  pos_=0;
  FOREVER{
    if(slen_<=0) break;
    zero(buf_,sizeof buf_);
    copy("\xD0\xCF",buf_,2);
    if(slen_>25) len_=25; else len_=slen_;
    copy(&string[pos_],&buf_[2],len_);
    buf_[2+len_]=0xD0;
    prttext(buf_);
    slen_-=len_;pos_+=len_;
  }
}
 
static int copy0(char *ps_, char *pd_, int maxlen_)
{
  int k;

  for(k=0;k<maxlen_;k++){
    if(*ps_=='\0') break;
    *pd_++=*ps_++;
  }
  return k;
}
 
static int search(int16 stu_,int16 mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
#if 0
  if(stu_<=2) parmcall[1]=7;            bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3;                                              GEEN ADD
#endif
  if(stu_==6) parmcall[1]=0;
  parmcall[2]=0;
  parmcall[3]=0;
#ifdef STRAATKEY
  if(stu_==2) parmcall[4]=STRAATKEY;
#endif
  parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}
 

