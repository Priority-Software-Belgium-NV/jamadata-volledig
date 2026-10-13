/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* BKH0073GetD() {return &zzvw;}
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" int IbanTools(char *pIBAN,char *pBIC,char *pJamaRek,int16 ToolNr); // 0 = check iban/bic, 1=check+fill bic, 2=convert jamarek -> IBAN/BIC
extern "C" int16 Search(int stu_,int mod_);
extern "C" char *VarTextFmt(int len_,int update_);

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
static int16 ovlcall();
extern "C" char BKH0073dat[] = "BKH0073  00:03 23/04/15 (c) Jamadata";   // CODA-verwerking versie 2.3.A Juli 2012 
                                                                              
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define OPMLEN          20
#define flag            uint16
#define DIMAT           650
#define DIMA            5
#define DIM_TBCODAFILES 150
#define DIM_BEWLIJN     1000
#define DIM_DEFKOP      300
#define MAX_CNIV        5
#define MAXLEN          30
#define MAX_BDETAIL     30
#define MINFREE         200
#define DIM_OFIN        1000
#define DIM_OPEN        1000
#define SEARBFLEN       50
#define DIMZOEK         15
#define MAXFLD          120
 
extern char *s();
extern int16 *i();
extern uint16 *u(),dateadd(),datejd();
extern long *l(),val();
extern float *f();
extern double *d(),valu_cnv();
extern int16 retcall,parmcall[8];
extern uint16 onext;
extern char info[];

static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30U[] = {7,0xC8,30,0,1,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us25U[] = {7,0xC8,25,0,1,0,0};
static char fm_us25[]  = {7,0xC8,25,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os51[]  = {7,0x88,51,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os14[]  = {7,0x88,14,0,0,0,0};
static char fm_os26[]  = {7,0x88,26,0,0,0,0};
static char fm_os9[]   = {7,0x88, 9,0,0,0,0};
static char fm_os8[]   = {7,0x88, 8,0,0,0,0};
static char fm_os5[]   = {7,0x88, 5,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x70,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x70,0};
static char fm_ou4_[]   = {6,0x90,4,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou2_[]  = {6,0x90,2,0,0x00,0};
static char fm_od92_[] = {6,0x95,9,2,0x60,0};
static char fm_od9_2[] = {6,0x95,9,2,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_od7_2[] = {6,0x95,7,2,0x70,0};
static char fm_ud6_2[] = {6,0xD5,6,2,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_of8_0[] = {6,0x94,8,0,0x70,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_uf8_2[] = {6,0xD4,8,2,0x70,0};
static char fm_ol9[]   = {6,0x93,9,0,0x70,0};
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_ogrb[]  = {2,0xA8};
static char fm_ugrb[]  = {2,0xE8};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_udatw[] = {4,0xC0,0xE,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uLKG[]  = {11,0xC8,1,0,0x09,0,'K','L','G','G',0};
static char fm_us10FK[] = {11,0xC8,10,0,0x09,0,'F','F','K','K',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
 
static struct{
  long rec;
  double bedrag;
} open_recs[DIM_OPEN];

static struct {
  uint16 nr;
  uint16 typ;
  char nm[16];
  uint16 lastnr;
  long fingrb;
  long saldo;
  double saldo_vm;
  char munt[4];
  double e_saldo;
} j_tab[80];
  
static struct mask0 {// beginopname
  char rec_type;/* steeds 0 */
  char nul1[4];/* dummy */
  char datum[6];/* datum aanmaak : ddmmjj */
  char cod_fin[3];/* bankidentificatie of 0 */
  char toep_cod[2];/* steeds 05 */
  char duplic; /* D of blanc */
  char dummy1[7];/* dummy */
  char inschrnr[10];/* referte v/h bestand door de bank */
  char naam[26];/* naam geadresseerde */
  char bic[11];/* BIC v/d bank + 3 blanco's (8+3) */
  char btwnr[11];/* btw-nummer houder of nullen */
  char dummy2; // dummy 
  char afz_toep[5];/* code afz. toepassing */
  char tr_ref[16];/* transaction reference of blanco */
  char re_ref[16];/* related reference of blanco */
  char dummy3[7];/* blanco */
  char versiecode;/* steeds 2 */
} rec0;
 
static struct mask1 {/* oud saldo */
  char rec_type;/* steeds 1 */
  char soort_rek;/* 0=belg.nr, 1=buitenl.nr, 2=belg.IBAN, 3=buitenl.IBAN */
  char volgnr[3];/* volgnr pap. afschrift of julian date of nullen */
  char reknr[37];/* rekeningnummer en muntcode */
  char teken;/* teken oud saldo 0=+, 1=- */
  char o_saldo[15];/* oud saldo formaat EEEEEEEEEEEEddd 12,3 */
  char datum[6];/* datum oud saldo ddmmjj */
  char naam[26];/* naam rekeninghouder */
  char omsch[35];/* omschrijving rekening */
  char volgnr1[3];/* volgnr gecod. afschrift */
} rec1;

static struct mask21 {/* bewegingsrecord DEEL 1 */
  char rec_type;/* steeds 2 */
  char art_code;/* DEEL 1 (steeds 1)  */
  char volgnr[4];/* volgnr beweging beginnend vanaf 1 */
  char detailnr[4];/* nummer detailrecord van beweging beginnend vanaf 0 */
  char referte[21];/* refertenr. van de bank (informatief) */
  char teken;/* teken beweging 0=+, 1=- */
  char bedrag[15];/* bedrag, formaat EEEEEEEEEEEEDDD 12,3 */
  char val_dat[6];/* valuta-datum ddmmjj */
  char ver_code[8];/* TFFVVRRR : type, familie, verrichting, rubriek */
  char type_med;/* soort mededeling : 0=geen of niet gestructureerd, 1=gestructureerd */
  char mededel[53];/* vrije mededeling : volledig, gestruct : gestruct.type (3) + mededeling (50) */
  char boek_dat[6];/* boekingsdatum ddmmjj */
  char pap_nr[3];/* volgnr papieren afschrift */
  char code_glob;/* code globalisatie */
  char code_verv;/* 0=geen bis-record, 1=nog bis-record (type 2 of 3) */
  char dummy;/* dummy blanco */
  char code_bind;/* 0: geen info-artikel, 1:info-artikel, 2=vrij bericht */
} rec21;

static struct mask22 {/* bewegingsrecord DEEL 2 */
  char rec_type;                                                /* steeds 2 */
  char art_code;/* DEEL 2 (steeds 2)  */
  char volgnr[4];                      /* volgnr beweging beginnend vanaf 1 */
  char detailnr[4];   /* nummer detailrecord van beweging beginnend vanaf 0 */
  char mededel[53];/* vervolg mededeling  */
  char klt_ref[35];/* referte klant of blanco (2x13 pos) */
  char bic_tegen[11];/* BIC v/d tegenpartij */
  char dummy1[8];/* blanco */
	char doelcategorie[4];  // purpose categorie
	char doel[4]; // doel
  char code_verv;/* vervolg : 0=geen type 2.3, 1=er volgt type 2.3 */
  char dummy2;/* blanco */
  char code_bind;/* 0: geen info-artikel 3, 1:info-artikel 3 */
} rec22;

static struct mask23 {/* bewegingsrecord DEEL 3 */
  char rec_type;                                                /* steeds 2 */
  char art_code;/* DEEL 3 (steeds 3)  */
  char volgnr[4];                      /* volgnr beweging beginnend vanaf 1 */
  char detailnr[4];   /* nummer detailrecord van beweging beginnend vanaf 0 */
  char rek_tegen[37];/* rekeningnummer tegenpartij en munt */
  char naam[35];/* naam tegenpartij  */
  char mededel[43];/* mededeling vervolg */
  char code_verv;/* steeds 0 */
  char dummy[1];
  char code_bind;/* 0: geen info-artikel 3, 1:info-artikel 3 volgt */
} rec23;

static struct mask31 {/* informatierecord DEEL 1 */
  char rec_type;/* steeds 3 */
  char art_code;/* DEEL 1 (steeds 1)  */
  char volgnr[4];/* zelfde volgnr als bewegingsartikel waarop betrekking */
  char detailnr[4];   /* nummer detailrecord van beweging beginnend vanaf 0 */
  char bank_ref[21];/* zelfde referte als record 2  */
  char ver_code[8];       /* TFFVVRRR : type, familie, verrichting, rubriek */
  char type_med;     /* type mededeling : 0=niet gestruct, 1=gestructureerd */
  char mededel[73];/* vrije mededeling of gestruct.type (3) + mededeling  */
  char dummy1[12];
  char code_verv;/* 0 = geen deel 3.2, 1=deel 3.2 */
  char dummy2;
  char code_bind;/* 0: geen info-artikel 3, 1:info-artikel 3 volgt */
} rec31;

static struct mask32 {/* informatierecord DEEL 2 */
  char rec_type;                                                /* steeds 3 */
  char art_code;/* DEEL 2 (steeds 2)  */
  char volgnr[4];   /* zelfde volgnr als bewegingsartikel waarop betrekking */
  char detailnr[4];   /* nummer detailrecord van beweging beginnend vanaf 0 */
  char mededel[105];/* vervolg mededeling  */
  char dummy1[10];
  char code_verv;/* 0 = geen deel 3, 1=deel 3 */
  char dummy2;
  char code_bind;/* 0: geen info-artikel, 1:info-artikel */
} rec32;

static struct mask33 {/* informatierecord DEEL 3 */
  char rec_type;                                                /* steeds 3 */
  char art_code;/* DEEL 3 (steeds 3)  */
  char volgnr[4];   /* zelfde volgnr als bewegingsartikel waarop betrekking */
  char detailnr[4];   /* nummer detailrecord van beweging beginnend vanaf 0 */
  char mededel[90];/* vervolg mededeling  */
  char dummy1[25]; // blanco
  char code_verv;/* steeds 0 (geen vervolg) */
  char dummy2[1]; // blanco
  char code_bind;/* 0: geen info-artikel 3, 1:info-artikel 3 */
} rec33;

static struct mask4 {/* vrij bericht */
  char rec_type;                                                /* steeds 4 */
  char dummy1;  /* blanco  */
  char volgnr[4];   /* volgnr begint met 1 */
  char detailnr[4];   /* nummer detailrecord van beweging beginnend vanaf 0 */
  char dummy2[22]; // blanco
	char mededel[80];/* tekst van bericht  */
  char dummy3[15]; // blanco
  char code_bind;/* 0: geen vrij bericht, 1:nog vrij bericht */
} rec4;

static struct mask8 {/* nieuw saldo */
  char rec_type;/* steeds 8 */
  char pap_volgnr[3];/* volgnr papieren afschrift  */
  char rekening[37];/* rekeningnummer en muntcode */
  char teken;/* teken oud saldo 0=+, 1=- */
  char n_saldo[15];/* new saldo formaat EEEEEEEEEEEEddd 12,3 */
  char datum[6];/* datum nieuw saldo ddmmjj */
  char dummy[64];
  char code_bind;/* 0: geen info-artikel, 1:info-artikel type 4 volgt */
} rec8;

static struct mask9 {/* footer */
  char rec_type;/* steeds 9 */
  char dummy[15];
  char q_lijnen[6];/* aantal artikels 1,2,3, en 8 */
  char deb_omzet[15];/* debet omzet (record 2 met detailnr =0 */
  char cre_omzet[15];/* credit omzet (record 2 met detailnr=0 */
  char dummy1[75];
  char meerv_bst;/* 1=er volgt nog een bestand, 2=laatste bestand */
} rec9;

static struct {
  char klt_nr[10];
  char fact_nr[10];
  char g_med[20];
  int16 volgnr;
  double bedrag;
  int16  rf_yy;
  int16  rf_jr;
  int16  rf_vl;
  uint16 val_dat;
} st;

static struct _tb12 {
  char begin;
  uint16 rec_nr;
  long recft;
  long grb_tb;
  double bedrag;
  char opm_bkh[OPMLEN];
  uint16 vl_tb;
  char jr_tb;
  char yy_tb;
	long GRBwacht;
	long GRBoverb;
} tb[DIM_BEWLIJN*MAX_BDETAIL+MAX_BDETAIL];

static struct {
	int16 VolgNr;
	int16 DetailNr;
	char CodeVerrichting[8];
	double Bedrag;
	double SubBedrag;
  uint16 ValutaDatum;
	char VrijeMededeling[150];
	char GestrMededeling[20];
	char VrijeMededeling1[150];
	char GestrMededeling1[20];
	char KlantRef[35];
	char RekeningNr[40];
	char Naam[40];
  char KlantCode[10];
  char FactuurNr[10];
	int16 GroepBetaling;
  uint16 KlantRec;
  int16  RefJaar;
  int16  RefJournaal;
  int16  RefVolgNr;
  int16  BkhOK;
  int16  UserChanged;
} BewLijn[DIM_BEWLIJN],PrintBewLijn;

static struct {
	char CodeVerrichting[8];
	char RekeningNr[40];
	char Naam[40];
  uint16 LKGRec;
	char dummy[10];
} DefaultKoppelingen[DIM_DEFKOP];

static struct{
	char IBAN[5][40];
	uint16 Jnl[5];
	long RekeningBetLijst[5];
	long RekeningStorting[5];
	char JnlNaam[5][25];
	char SubDir[50];
	char LayoutStructMed[10];
	char SkipGroepsDetail;
	char BetaalterminalApart;
	long WachtRekeningBetalingen;
} CodaSettings;

static struct{
	char   IBAN[40];
	uint16 BkhJournaal;
	long OvrRekening;
	long StortingRekening;
	uint16 Datum;
	uint16 VolgNr;
	uint16 AantalBew;
	double VorigSaldo;
	double NieuwSaldo;
	char   Naam[40];
	char   FileNaam[255];
	long   FilePosInFile;
} TbCodaFiles[DIM_TBCODAFILES],CodaFileHdr;

static struct{
	long rec4;
	char fullmatch;
	} TbZoekFactuur[200];

static int16 form_dat[8],pr_mode,prtnr,LinFree,BewCount,scrcount,notfound;
static int16 mcnt,stutyp,ref_jr,ref_yy,zoek_op_bd,DefAkJournaal, DefVkJournaal,MaxDefKop,PandJournaal;
static uint16 recnr_ogm,recnr_disk,rec_nr,dat_beg,dat_end;
static uint16 df_recnr[15];
static uint16 last_arc,MinBkhDatum,ref_ft,jaartal,mnd_strt,bkh_dt,searcnr;
static uint16 journl,lastnr,last_adr=0,volgnr_ogm,recs_tot,recs_ok,recs_nok,sysdiff=0;
static uint16 sys1818, sys1840, sys1850,sys1862,max_orec,combi_nr[MAX_CNIV+1],loc_klt[20];
static long levcent,kltcent,df_grb[15],grb_d_ak, grb_d_vk,grb_d_fi,tb_grbnotfound[50];
static char begunst[30],banknr[20],btwnr[20],searbuf[SEARBFLEN+1];
static char klt_nr[10],ogm_file[20],*i_80,pauze='J',filnam[100];
static char munt[4],def_munt[4],lkg,lkglet[3]={'L','K','G'};
static char opmer[OPMLEN],gnm_diff[6][20],buf1000[1000],buf500[500];
static uint16 dat_ogm,dat_bedrag,rec_cnt,sys1848,volgnr;
static flag klcd,lvcd,geboekt,debit_allow,credt_allow;
static flag sear_stt,chk_btoeg;
static flag sys3876;
static char lkgkod[9],lkgnaam[51],opmerk[30];
static int16 q_uittrek,q_bew,q_error,q_done,CntCodaFiles;
static char *p_data,*rec_type,*rec_deel;
static double bd_bkh,bd_bkh_t=0,bd_tot,bd_inp;
static double tot_deb,tot_cre,tot_bew,o_sal,n_sal,bd_ok,bd_nok;
static long fpos,*pl_80_1,afw_long;
static uint16 zoekscr[DIMZOEK],pzoekscr;
static long tb_ofin[DIM_OFIN],zk_rec[20];

static int16 analyt,ny;
static struct _tba {
  char begin;
  double a_bedrag;
  uint16 a_rec_nr;
  long a_elem;
  long a_grbrek;
  long mast_grbrek;
} tba[DIMAT];
static float anal_pct[DIMA];
static char anal_nm[DIMA][MAXLEN],anal_onm[DIMA][MAXLEN],anal_ask;

/* --------------------------- Declaratie functies ---------------------- */
static double absdoubl(double bd_);
static void anal_det(int16 bew_nr_,int16 nr_);
static bool BoekCodaFile(int p_tbcoda_);
static  uint16 cnv_dat(char *p);
static int copy0(char *ps,char *pd,int max);
static void fileopen(int16 nr_);
static void DeleteLijst(void);
static void DetailBeweging(int p_tbcoda_, int nr_);
static long FindFactuurOpBedrag(uint16 lk_rec_, double ftbedrag_);
static int g_anal_tst(void);
static double get_val(char *pteken, char *pget, uint16 digits, uint16 decim);
static uint16 get_4lkg(void);
static uint16 getgrb(long lgrb);
static void initload(void);
static int is_nul(double bd_);
static int16 is_voldaan(long rec4_);
static int LoadCodaFiles(int lst_geboekt_, int deletemode_);
static void LoadDefaultKoppelingen(void);
static void DisplayDefaultKoppelingen(void);
static void DumpDefaultKoppelingen(void);
static void makename(char *pd);
static int16 make_otab(void);
static void nextline(void);
static long num_get(char *p, int16 count);
static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_);
static bool PdfCodaFile(int p_tbcoda_,int BkhDetail);
static bool ReadCodaFile(int p_tbcoda_);
static int scr_ok(char *ptxt);
static void tab_add(double *pdbl_,uint16 ref_yy_,uint16 ref_jr_,uint16 ref_ft_,long ft_rec_);
static void UpdateParameters(void);
static long ZoekFactuur(char *pnaam_,uint16 ft_nummer_,double bedrag_);  // zoek AK/VK factuur ahv nummer of bedrag
static int16 zoeklk_r(void);
static uint16 zk_combi(int16 beg_,int16 niv_,double *pbd_beg_,double *ptotaal_);
static void ZoekBewegingen(int p_tbcoda_);
/* ---------------------------------------------------------------------- */


extern "C" void BKH0073cod(void)
{
  int16 j,k,key,z,start_,len_,lst_geboekt_=NO;
	char titel_[35];

	initload();
	LoadCodaFiles(lst_geboekt_,NO);
	start_=0;
  FOREVER{
		redo:;
		scrnum=0;scrget(1,266);z=1; scraddpicto(3,0,76,0,4,2,105,1,7,"^!B0073A");
		if(lst_geboekt_) len_=copy0(" Lijst geboekte CODA-bestanden ",titel_,34);
		else len_=copy0(" Lijst te boeken CODA-bestanden ",titel_,34);
	  if(lst_geboekt_){
		  scraddfield(200,(80-len_)/2,1,0xB);
		  scraddpicto(2,0,74,22,4,2,589,0,0,"Toon niet geboekte lijst");
			scraddpicto(4,0,70,22,4,2,133,0,3,"Schrap deze geboekte lijst");
		}
		else{
		  scraddfield(200,(80-len_)/2,1,0x9);
			scraddpicto(2,0,74,22,4,2,600,0,0,"Toon geboekte lijst");
		}
		scrifld(200,VarTextFmt(32,0),titel_);		
		scraddpicto(1,0,78,23,2,1,59,0,4,"Parameters");
		k=start_+1; if(k>=CntCodaFiles) k=CntCodaFiles; scrifld(z++,fm_ou3,&k);
		k+=14; if(k>=CntCodaFiles) k=CntCodaFiles; scrifld(z++,fm_ou3,&k);
		for(k=0;k<15;k++){
			if((k+start_)>=CntCodaFiles) break;
			for(j=0;j<80;j++) if(TbCodaFiles[start_+k].BkhJournaal==j_tab[j].nr) break;
			if(j<80) scrifld(z++,VarTextFmt(16,0),j_tab[j].nm); else z++;
//			scrifld(z++,fm_os20,TbCodaFiles[start_+k].Naam);
			scrifld(z++,fm_ou2,&TbCodaFiles[start_+k].BkhJournaal);
			scrifld(z++,fm_odat,&TbCodaFiles[start_+k].Datum);
			scrifld(z++,fm_ou5,&TbCodaFiles[start_+k].VolgNr);
			scrifld(z++,fm_od6_2,&TbCodaFiles[start_+k].VorigSaldo);
			scrifld(z++,fm_od6_2,&TbCodaFiles[start_+k].NieuwSaldo);
			scrifld(z++,fm_ou5,&TbCodaFiles[start_+k].AantalBew);
			scraddpicto(5+k,z-1,7,0,2,1,583,0,0,"Bekijk"); 
			scraddpicto(20+k,z-1,10,0,2,1,125,0,4,"Boek"); 
			scraddpicto(35+k,z-1,13,0,2,1,133,0,3,"Schrap"); 
		}
		key=scrupd(-1,0x047);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){ UpdateParameters();goto redo;}
		if(key==5002){
			if(lst_geboekt_) lst_geboekt_=NO; else lst_geboekt_=YES;
			start_=0;key=107;
		}
		if(key==5003) goto redo; // link help 
		if(key==5004){
			DeleteLijst(); // schrap geboekte lijst
			LoadCodaFiles(lst_geboekt_,NO);start_=0;goto redo;
		}
		if(key>=5005 && key<5005+15){
			j=key-5005+start_;ReadCodaFile(j);PdfCodaFile(j,NO);
		}
		if(key>=5020 && key<5020+15){
			j=key-5020+start_;BoekCodaFile(j);key=107;
		}
		if(key>=5035 && key<5035+15){
			if(lst_geboekt_ || DisplayWarning("CODA-bestand is nog niet geboekt! Wenst U dit echt te schrappen?",605,1)==YES){
  			j=key-5035+start_;
	      remove(TbCodaFiles[j].FileNaam);			
		  	key=107;
			}
		}
		if(key==101) break;
		if(key==107){LoadCodaFiles(lst_geboekt_,NO);start_=0;goto redo;}
		if(key==102) start_-=15;
		if(key==103) {start_+=15; if(start_>=CntCodaFiles) start_-=15;}
		if(start_<0) start_=0;
	}
	DumpDefaultKoppelingen();
  ovlexit(-1);
}

static void DeleteLijst(void)
{
  int16 key,z,curs=1,k;
  

  dat_beg=0; dat_end=*u(25,2);
  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,4,25,3);
    scraddf(z++,8,5,0);scraddf(z++,8,15,2);
    scraddf(z++,8,24,0);scraddf(z++,8,31,2);
    scraddf(z++,23,1,8);scraddf(z++,23,11,8);

    z=1;
    scrifld(z++,VarTextFmt(30,0),"Schrappen geboekte uittreksels");
    scrifld(z++,VarTextFmt(9,0),"Periode :");
    scrifld(z++,fm_udat,&dat_beg);
    scrifld(z++,VarTextFmt(6,0),"t.e.m.");
    scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,VarTextFmt(9,0)," F1 stop ");scrifld(z++,VarTextFmt(11,0)," F4 schrap ");
    key=scrupd(curs,0x9);curs=1;
    if(key==101) goto endsr;
		if(dat_end==0){errnum=38; curs=6;goto redo;}
    if(key==104){
      if(DisplayWarning("Wenst u echt deze lijst te schrappen?",605,1)==YES) break;
    }
  }
	scrnum=0;scrget(1,7);scrupd(-3,0);
	LoadCodaFiles(YES,YES);
endsr:;
}


static void LoadDefaultKoppelingen(void)
{
	int linelen_=100;
	CFile cfile_;
	CString filename_;
	long fpos_;

  zeroL(DefaultKoppelingen[0].CodeVerrichting,sizeof DefaultKoppelingen); MaxDefKop=0;
	filename_=CString("CodaDefaults_");filename_+=CString(s(25,3),3);filename_+=CString(".jam");
	if(cfile_.Open(filename_,CFile::modeRead,0)==false) goto endsr;
	fpos_=0;
	for(MaxDefKop=0;MaxDefKop<DIM_DEFKOP;MaxDefKop++){
		cfile_.Seek(fpos_,CFile::begin); fpos_+=linelen_;
	  if(cfile_.Read(DefaultKoppelingen[MaxDefKop].CodeVerrichting,linelen_)<linelen_) break;
	}
	cfile_.Close();
	endsr:;
}

static void DumpDefaultKoppelingen(void)
{
	int linelen_=100,k;
	CFile cfile_;
	CString filename_;

	filename_=CString("CodaDefaults_");filename_+=CString(s(25,3),3);filename_+=CString(".jam");
	if(cfile_.Open(filename_,CFile::modeCreate|CFile::modeWrite,0)==false) goto endsr;
	for(k=0;k<MaxDefKop;k++){
		cfile_.Write(DefaultKoppelingen[k].CodeVerrichting,linelen_);
	}
	cfile_.Close();
	endsr:;
}


static void DisplayDefaultKoppelingen(void)
{
  int16 j,k,key,z,start_,q_lines_=18,max_orig_,stu_;
	char type_;


	DumpDefaultKoppelingen();
	start_=0;max_orig_=MaxDefKop;
  FOREVER{
		redo:;
		scrnum=0;scrget(1,278);z=1; //scraddpicto(3,0,76,0,4,2,105,1,7,"^!B0073A");
		k=start_+1; if(k>=MaxDefKop) k=MaxDefKop; scrifld(z++,fm_ou3,&k);
		k+=q_lines_-1; if(k>=MaxDefKop) k=MaxDefKop; scrifld(z++,fm_ou3,&k);
		for(k=start_;k<start_+q_lines_;k++){
			if((k)>=MaxDefKop) break;
			if(DefaultKoppelingen[k].LKGRec>60000) {stu_=3;type_='G';}
			else if(DefaultKoppelingen[k].LKGRec>30000) {stu_=2;type_='K';}
			else {stu_=1; type_='L';}
			fasinit(stu_); *u(stu_,1)=DefaultKoppelingen[k].LKGRec-(stu_-1)*30000; fasgeti(stu_);
			scrifld(z++,VarTextFmt(20,0),DefaultKoppelingen[k].RekeningNr);
			scrifld(z++,VarTextFmt(25,0),DefaultKoppelingen[k].Naam);
			scrifld(z++,fm_os1,&type_);
			scrofld(z++,stu_,3,25);
			scraddpicto(10+(k-start_),0,77,(k-start_)+4,2,1,133,0,3,"Schrap"); 
		}
		key=scrupd(-1,0x047);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5003) goto redo; // link help 
		if(key>=5010 && key<5010+q_lines_){
			j=key-5010+start_;
			for(k=j+1;k<MaxDefKop;k++) copy(DefaultKoppelingen[k].CodeVerrichting,DefaultKoppelingen[k-1].CodeVerrichting,sizeof DefaultKoppelingen[0]);
			zero(DefaultKoppelingen[MaxDefKop-1].CodeVerrichting,sizeof DefaultKoppelingen[0]); MaxDefKop--; if(MaxDefKop<0) MaxDefKop=0;
		}
		if(key==101) break;
		if(key==102) start_-=15;
		if(key==103) {start_+=15; if(start_>=MaxDefKop) start_-=15;}
		if(start_<0) start_=0;
	}
	if(MaxDefKop!=max_orig_){
		if(DisplayWarning("Wenst u echt de wijzigingen door te voeren?",605,1)==YES) DumpDefaultKoppelingen();
		else LoadDefaultKoppelingen();
	}
}


static int LoadCodaFiles(int lst_geboekt_,int deletemode_)
{
  uint16 k,file_chk_,q_bew_,linelen_=130;
	long len_;
	char CRecord[150],biccode_[20],dummy5_[5];
	CFileFind finder;
	CFile cfile_;
	BOOL bWorking;
  CString filename_,cstr1_,cstr2_;
	long fpos_;

	zeroL(TbCodaFiles[0].IBAN,sizeof TbCodaFiles);
	bWorking = finder.FindFile(CString(CodaSettings.SubDir)+CString("*.*")); CntCodaFiles=0;
	while (bWorking) {
		nextfile:;
		bWorking = finder.FindNextFile();
	  if (finder.IsDirectory()) continue;
	  len_=finder.GetLength();
  	if(len_%130==0 || (len_+2)%130==0) linelen_=130; // minstens 5 records en moet een veelvoud van 128+2 zijn, kan zijn de laatste niet
	  else if(len_%129==0 || (len_+1)%129==0) linelen_=129; // enkel x0A, kan zijn laatste niet
		else continue;
		if(finder.GetLength()<(5*linelen_)) continue; // minstens 5 records en moet een veelvoud van 128+2 zijn 
		filename_=CString(CodaSettings.SubDir)+finder.GetFileName();
		if(cfile_.Open(filename_,CFile::modeRead,0)==false) continue;
		fpos_=0;file_chk_=0; q_bew_=0;
		copy0((char *)(LPCTSTR)filename_,TbCodaFiles[CntCodaFiles].FileNaam,255);
		FOREVER{
			next_rec:;
			cfile_.Seek(fpos_,CFile::begin); fpos_+=linelen_;
	    if(cfile_.Read(CRecord,linelen_)<128) break;
		  if(CRecord[0]=='0'){
				if(file_chk_==4){
					file_chk_=0;q_bew_=0;
					CntCodaFiles++;if(CntCodaFiles>=DIM_TBCODAFILES) break;
					copy0((char *)(LPCTSTR)filename_,TbCodaFiles[CntCodaFiles].FileNaam,255);
				}
				if(lst_geboekt_) {if(CRecord[126]!='X') goto next_rec;} // enkel afgeboekte
				else {if(CRecord[126]=='X') goto next_rec;} // is al afgeboekt
				copy(CRecord,&rec0.rec_type,128);

				TbCodaFiles[CntCodaFiles].Datum=cnv_dat(rec0.datum);
				TbCodaFiles[CntCodaFiles].FilePosInFile=fpos_-linelen_;
				if(deletemode_){
					if(TbCodaFiles[CntCodaFiles].Datum>=dat_beg && TbCodaFiles[CntCodaFiles].Datum<=dat_end) {
						cfile_.Close();
						remove(TbCodaFiles[CntCodaFiles].FileNaam); 
						CntCodaFiles=0; zero(TbCodaFiles[CntCodaFiles].IBAN,sizeof TbCodaFiles[0]);
						goto nextfile;
					}
				}
				file_chk_++;
			}
			if(CRecord[0]=='1' && file_chk_){
				copy(CRecord,&rec1.rec_type,128);
				if(rec1.soort_rek=='0'){// belg. nummer --> converteren naar IBAN
					copy(rec1.reknr,TbCodaFiles[CntCodaFiles].IBAN,12); zero(biccode_,sizeof biccode_); zero(dummy5_,sizeof dummy5_);
          IbanTools(TbCodaFiles[CntCodaFiles].IBAN,biccode_,dummy5_,1);
				}
				else if(rec1.soort_rek=='1') copy(rec1.reknr,TbCodaFiles[CntCodaFiles].IBAN,30); // buitenl. nummer BBAN
				else if(rec1.soort_rek=='2') copy(rec1.reknr,TbCodaFiles[CntCodaFiles].IBAN,30); // belg. IBAN
				else copy(rec1.reknr,TbCodaFiles[CntCodaFiles].IBAN,30); // buitenl.IBAN
				TbCodaFiles[CntCodaFiles].VolgNr=num_get(rec1.volgnr,3); // papieren volgnummer
				if(TbCodaFiles[CntCodaFiles].VolgNr==0) TbCodaFiles[CntCodaFiles].VolgNr=num_get(rec1.volgnr1,3); // indien geen pap.nr dan coda.nr
				TbCodaFiles[CntCodaFiles].VorigSaldo=get_val(&rec1.teken,rec1.o_saldo,12,3);
				cstr1_=TbCodaFiles[CntCodaFiles].IBAN;cstr1_.Replace(" ","");
				for(k=0;k<5;k++){
					cstr2_=CodaSettings.IBAN[k];cstr2_.Replace(" ","");
					if(cstr1_==cstr2_) break;
				}
				if(k<5){
					TbCodaFiles[CntCodaFiles].BkhJournaal=CodaSettings.Jnl[k];
					TbCodaFiles[CntCodaFiles].OvrRekening=CodaSettings.RekeningBetLijst[k];
					TbCodaFiles[CntCodaFiles].StortingRekening=CodaSettings.RekeningStorting[k];
				}
				else{ // geen rekening die moet opgenomen worden 
					zero(TbCodaFiles[CntCodaFiles].IBAN,sizeof TbCodaFiles[0]);file_chk_=0;
					goto next_rec;
				}

				copy(rec1.naam,TbCodaFiles[CntCodaFiles].Naam,26);
				file_chk_++;
			}
			if(CRecord[0]=='2' && file_chk_){
				if(CRecord[1]=='1'){
					copy(CRecord,&rec21.rec_type,128);
					if(CodaSettings.SkipGroepsDetail!='J' || rec21.ver_code[0]<'5') TbCodaFiles[CntCodaFiles].AantalBew++;
				}				
			}
			if(CRecord[0]=='8' && file_chk_){
				copy(CRecord,&rec8.rec_type,128);
				TbCodaFiles[CntCodaFiles].NieuwSaldo=get_val(&rec8.teken,rec8.n_saldo,12,3);
				file_chk_++;
			}
			if(CRecord[0]=='9' && file_chk_){
				file_chk_++;
			}
		}
		cfile_.Close();
		if(file_chk_!=4 || TbCodaFiles[CntCodaFiles].AantalBew==0){
			zero(TbCodaFiles[CntCodaFiles].IBAN,sizeof TbCodaFiles[0]);
		}
		else CntCodaFiles++;
		if(CntCodaFiles>=DIM_TBCODAFILES) break;
	}
	finder.Close();
	return CntCodaFiles;
}

static bool BoekCodaFile(int p_tbcoda_)
{
  int16 nr_,j,k,g,key,z,start_,lijnpos,jj_,mm_,dd_,q_,ScreenLines=15;
	unsigned short funckeys;
	char mededeling_[60],attrib_,CRecord[150];
	double bd_,tot_boeking;
	CFile cfile_;
	CString cstr_;
	
	if(ReadCodaFile(p_tbcoda_)==false) return false;
//	for(k=0;k<DIM_BEWLIJN*MAX_BDETAIL+MAX_BDETAIL; k++) zero((char *)&tb[0].begin,sizeof tb[0]);
	zeroL((char *)&tb[0].begin,sizeof tb); 
	zeroL((char *)&tba[0].begin,sizeof tba);
	ZoekBewegingen(p_tbcoda_);

  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
		redo:;
    scrget(1,269);z=1;q_=0; funckeys=0x60E1;
		scraddpicto(3,0,72,22,4,2,583,0,0,"Maak PDF"); 
  	scrifld(z++,fm_odat,&TbCodaFiles[p_tbcoda_].Datum);scrifld(z++,fm_ou5,&TbCodaFiles[p_tbcoda_].VolgNr);scrifld(z++,fm_ou2,&TbCodaFiles[p_tbcoda_].BkhJournaal);
	  start_++;scrifld(z++,fm_ou3,&start_);start_--;scrifld(z++,fm_ou3,&TbCodaFiles[p_tbcoda_].AantalBew);
//		DisplayMenuTitel(0,ptitel,0xA);
		if(start_>0){ funckeys+=2; scraddpicto(1,0,76,1,4,2,18,0,4,"up"); }
		if((start_+ScreenLines)<BewCount) {funckeys+=4;scraddpicto(2,0,76,22,4,2,13,0,4,"down"); }
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=BewCount) break;
			k++;scrifld(z++,fm_ou3,&k);k--;
			scrifld(z++,fm_od6_2,&BewLijn[k].Bedrag);
	    scrifld(z++,VarTextFmt(25,0),BewLijn[k].Naam); 
			zero(mededeling_,sizeof mededeling_);
			if(BewLijn[k].GestrMededeling[0]){
			  cstr_="+++"+ CString(BewLijn[k].GestrMededeling,12)+"+++";cstr_.Insert(6,'/');cstr_.Insert(11,'/');
			  copy((char *)(LPCTSTR)cstr_,mededeling_,20);				
			}				
			else if(BewLijn[k].KlantRef[0] && BewLijn[k].GroepBetaling) copy(BewLijn[k].KlantRef,mededeling_,35);
			else copy(BewLijn[k].VrijeMededeling,mededeling_,45);
			scrifld(z++,VarTextFmt(33,0),mededeling_); q_++;
			if(BewLijn[k].Bedrag) scraddpicto(11+k-start_,z-1,1,0,2,1,64,0,4,"Bekijk"); 
			if(BewLijn[k].BkhOK!=YES) attrib_=0xA; else attrib_=0xFF;
			for(j=0;j<4;j++)scrchat(z-1-j,attrib_);
//  			if(q_==(lijnpos+1)) scrchat(z-1-j,0xA); else scrchat(z-1-j,0xFF);
	
    }
    scrifld(66,fm_uu3,&nr_);
    key=scrupd(61,funckeys);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5011 && key<=5011+15) DetailBeweging(p_tbcoda_,key-5011+start_);
		if(key==5003) PdfCodaFile(p_tbcoda_,YES);
    switch(key){
			case 8       : lijnpos--;// pijl opmhoog 
										 if(lijnpos<0) lijnpos=q_-1;
										 break;
			case 9       : lijnpos++;// pijl omlaag 
										 if(lijnpos>=q_) lijnpos=0;
									   break;
			case 12      :// PgUp 
			case 5001    :
			case 102     : if(start_>0){
											 start_-=ScreenLines; if(start_<0) start_=0;lijnpos=0;scrnum=0;
										 }
										 break;
			case 13      :// PgDn 
			case 5002      :// PgDn 
			case 103     : if((start_+ScreenLines)<BewCount) {start_+=ScreenLines;lijnpos=0;scrnum=0;}
										 break;
			case 10      : start_=0;lijnpos=0;scrnum=0;// HOME 
										 break;
			case 11      : start_=BewCount-ScreenLines;if(start_<0) start_=0;// END 
										 lijnpos=0;scrnum=0;
										 break;
			case 101     :
			case 106     : for(k=0;k<BewCount;k++) if(BewLijn[k].UserChanged) break;
										 if(k<BewCount){
											 if(DisplayWarning("Wenst u echt de ingebrachte wijzigingen te annuleren?",605,1)==NO) goto redo;
										 }
										 return false;
										 break;


//			case 18      :// ENTER 
//			case 15      : // TAB  
			case 18     : if(nr_>BewCount) errnum=34;// neem aan en exit 
										else{
											if(nr_>0) DetailBeweging(p_tbcoda_,nr_-1); 
  									 }
										 break;
			default      : break;
    }
		if(key==108){
			for(k=0;k<BewCount;k++) if(BewLijn[k].BkhOK==NO) break;
			if(k<BewCount)errnum=73;
			else break;
		}
	}
	if(CodaFileHdr.NieuwSaldo==0 && CodaFileHdr.VorigSaldo==0){ // gedeeltelijke coda
		for(j=0;j<80;j++) if(TbCodaFiles[p_tbcoda_].BkhJournaal==j_tab[j].nr) break;
		sysget(10240+20+j*80,2,(char *)&j_tab[j].lastnr);
		TbCodaFiles[p_tbcoda_].VolgNr=j_tab[j].lastnr+1;
	}
	PdfCodaFile(p_tbcoda_,YES);
  if(DisplayWarning("Wenst u dit CODA-bestand in te boeken?",605,1)==NO) return false;
	if(CodaFileHdr.NieuwSaldo==0 && CodaFileHdr.VorigSaldo==0){ // gedeeltelijke coda
		for(j=0;j<80;j++) if(TbCodaFiles[p_tbcoda_].BkhJournaal==j_tab[j].nr) break;
		sysget(10240+20+j*80,2,(char *)&j_tab[j].lastnr);
		TbCodaFiles[p_tbcoda_].VolgNr=j_tab[j].lastnr+1;
	}
	tot_boeking=0;
	for(k=0;k<BewCount;k++){
		for(j=k*MAX_BDETAIL;j<k*MAX_BDETAIL+MAX_BDETAIL;j++){
			if(!is_nul(tb[j].bedrag)){
				fasinit(4);
				*s(4,2)=TbCodaFiles[p_tbcoda_].BkhJournaal;
				*u(4,3)=TbCodaFiles[p_tbcoda_].VolgNr;
				*u(4,4)=TbCodaFiles[p_tbcoda_].Datum;
				*l(4,7)=-tb[j].bedrag;
				*d(4,32)=-tb[j].bedrag; *s(4,31)='E'; tot_boeking+=tb[j].bedrag;
				*u(4,5)=tb[j].rec_nr;
				if(*u(4,5)<30000) *l(4,6)=levcent;
				else if(*u(4,5)<60000) *l(4,6)=kltcent;
				else {*u(3,1)=*u(4,5)-60000;fasgeti(3);*l(4,6)=*l(3,2);}
				*s(4,8)=tb[j].yy_tb; if(*s(4,8)<50) *s(4,8)+=100;/* y2000 */
				*s(4,9)=tb[j].jr_tb;
				*u(4,10)=tb[j].vl_tb;
				if(*s(4,9)==0 && *u(4,10)==0 && *s(4,8)==100) *s(4,8)=0;/* correctie y2000 */
				*s(4,12)=0;
				if(fldlen(4,28) && tb[j].opm_bkh[0]) copy(tb[j].opm_bkh,s(4,28),20);
				if(fldlen(4,60)) *u(4,60)=procid;
				fasadd(4);
				if(tb[j].GRBwacht && tb[j].GRBoverb){ // huurbetalingen overboeken van 4-wachtrekening naar 7-rekening
					fasinit(3);*l(3,2)=tb[j].GRBwacht; g=faskeyi(3,1,0);
					if(g==0){fasinit(3);*l(3,2)=tb[j].GRBoverb; g=faskeyi(3,1,0);}
					if(g==0){
						fasinit(3);*l(3,2)=tb[j].GRBoverb; faskeyi(3,1,0);
						*u(4,5)=*u(3,1)+60000; *l(4,6)=*l(3,2);
						*l(4,7)=-tb[j].bedrag; *d(4,32)=-tb[j].bedrag;
						errnum=fasadd(4);
						fasinit(3);*l(3,2)=tb[j].GRBwacht; faskeyi(3,1,0);
						*u(4,5)=*u(3,1)+60000; *l(4,6)=*l(3,2);
						*l(4,7)=tb[j].bedrag; *d(4,32)=tb[j].bedrag;
						errnum=fasadd(4);
					}
				}
			}
		}
	}
	fasinit(4);
  *s(4,2)=TbCodaFiles[p_tbcoda_].BkhJournaal;
	*u(4,3)=TbCodaFiles[p_tbcoda_].VolgNr;
	*u(4,4)=TbCodaFiles[p_tbcoda_].Datum;
	if(CodaFileHdr.NieuwSaldo==0 && CodaFileHdr.VorigSaldo==0) bd_=tot_boeking; // gedeeltelijke coda
	else bd_=TbCodaFiles[p_tbcoda_].NieuwSaldo-TbCodaFiles[p_tbcoda_].VorigSaldo;
	*l(4,7)=bd_;	*d(4,32)=bd_; *s(4,31)='E';
	for(j=0;j<80;j++) if(TbCodaFiles[p_tbcoda_].BkhJournaal==j_tab[j].nr) break;
	*u(4,5)=getgrb(j_tab[j].fingrb);*l(4,6)=j_tab[j].fingrb;
	*s(4,12)=0;
	jddate(TbCodaFiles[p_tbcoda_].Datum,&jj_,&mm_,&dd_);jj_%=100;
	sprintf(mededeling_,"Coda %d  %d/%d/%d",TbCodaFiles[p_tbcoda_].VolgNr,dd_,mm_,jj_); 
	copy(mededeling_,s(4,28),20);
	if(fldlen(4,60)) *u(4,60)=procid;
	fasadd(4);
  if(analyt){
    for(g=0;g<DIMAT;g++){
      if(tba[g].a_bedrag){
				fasinit(4);
				*s(4,2)=TbCodaFiles[p_tbcoda_].BkhJournaal;
				*u(4,3)=TbCodaFiles[p_tbcoda_].VolgNr;
				*u(4,4)=TbCodaFiles[p_tbcoda_].Datum;
				*u(4,5)=tba[g].a_rec_nr;
				*l(4,6)=tba[g].a_grbrek;
				bd_=valu_cnv(munt,"EUR",tba[g].a_bedrag,(double)0.01);
				*l(4,7)=-bd_; *d(4,32)=-bd_;
				*s(4,31)='E';
				*l(4,11)=tba[g].mast_grbrek; //*l(4,11)=tb[tba[g].a_elem].grb_tb;
				if(fldlen(4,60)) *u(4,60)=procid;
				errnum=fasadd(4);
      }
    }
  }
  sysget(10240+20+j*80,2,(char *)&j_tab[j].lastnr);
  sysget(10287+j*80,8,&j_tab[j].e_saldo);
	if(j_tab[j].lastnr==TbCodaFiles[p_tbcoda_].VolgNr-1) {
		j_tab[j].lastnr++; j_tab[j].e_saldo=TbCodaFiles[p_tbcoda_].NieuwSaldo;
		sysput(10240+20+j*80,2,&j_tab[j].lastnr);
    sysput(10287+j*80,8,&j_tab[j].e_saldo);
	}

	// remove(TbCodaFiles[p_tbcoda_].FileNaam);
	if(cfile_.Open(TbCodaFiles[p_tbcoda_].FileNaam,CFile::modeReadWrite,0)) {
		cfile_.Seek(TbCodaFiles[p_tbcoda_].FilePosInFile,CFile::begin);
	  if(cfile_.Read(CRecord,128)==128){
			CRecord[126]='X'; // als afgeboekt markeren
			cfile_.Seek(TbCodaFiles[p_tbcoda_].FilePosInFile,CFile::begin); 
      cfile_.Write(CRecord,128);
		}
    cfile_.Close();
	} else errnum=1; 
	return true;
}


static void DetailBeweging(int p_tbcoda_, int nr_)
{
  int16 j,k,h,n,key,z,z_base,curs=0,stu_dsp_,his_start_=0,ptb_,first_=YES,F8_OK_cnt_=YES;
  uint16 rec_dsp_,last_r_;
  double bd_,bd_yetdiv=0;
  char dum[2],dsp_buf_[50],*fmt_;
	CString cstr_;



redo_full:;
  bd_tot=BewLijn[nr_].Bedrag;  
	bkh_dt=TbCodaFiles[p_tbcoda_].Datum;
	for(k=0;k<MAX_BDETAIL;k++) copy(&tb[nr_*MAX_BDETAIL+k].begin,&tb[DIM_BEWLIJN*MAX_BDETAIL+k].begin,sizeof tb[0]);	
	mcnt=0;his_start_=0;curs=0;his_start_=0;first_=YES;F8_OK_cnt_=YES;
  lkg=lkglet[debit_allow];
	bd_inp=0; bd_yetdiv=0; last_r_=0;
	for(k=0;k<MAX_BDETAIL;k++){
		bd_yetdiv+=tb[DIM_BEWLIJN*MAX_BDETAIL+k].bedrag;
		if(tb[DIM_BEWLIJN*MAX_BDETAIL+k].bedrag) mcnt++;
	}
  anal_ask='\0';
  for(ny=DIMAT-1;ny>=0;ny--) if(tba[ny].a_rec_nr) break;
  ny++;
	bd_inp=bd_tot-bd_yetdiv;
	if(bd_tot<0) lkg='L'; else lkg='K';
  fasinit(1);fasinit(3);
  jddate(bkh_dt,&ref_yy,(int16 *)&dum[0],(int16 *)&dum[0]);ref_yy=ref_yy%100;
  ref_jr=0;ref_ft=0;
  zeros(opmer,sizeof opmer);
  zeros(lkgkod,sizeof lkgkod);
	zeros(lkgnaam,sizeof lkgnaam); if(!is_nul(bd_inp)) copy(BewLijn[nr_].Naam,lkgnaam,30);
  if(BewLijn[nr_].CodeVerrichting[0]=='0' && cmpstr(&BewLijn[nr_].CodeVerrichting[1],"01",2)!=0 && cmpstr(&BewLijn[nr_].CodeVerrichting[1],"02",2)!=0
		&& cmpstr(&BewLijn[nr_].CodeVerrichting[1],"05",2)!=0){ // cheques, kosten, loketverrichting...
	  lkg='G';zeros(lkgnaam,sizeof lkgnaam);
  }
  his_start_=mcnt-4;if(his_start_<0) his_start_=0;
  errnum=0;
	if(!BewLijn[nr_].BkhOK && BewLijn[nr_].Bedrag>0 && BewLijn[nr_].GestrMededeling[0] && (cmpstr(&BewLijn[nr_].CodeVerrichting[1],"01",2)==0 || cmpstr(&BewLijn[nr_].CodeVerrichting[1],"02",2)==0)){// enkel bij overschrijvingen
		*u(2,1)=BewLijn[nr_].KlantRec; fasgeti(2);copy(s(2,3),lkgnaam,fldlen(2,3)); lkg='K';
    ref_yy=BewLijn[nr_].RefJaar;
    ref_ft=BewLijn[nr_].RefVolgNr;
		ref_jr=BewLijn[nr_].RefJournaal;
	}
  FOREVER{
    if(!errnum && !first_){
      redo_0:
      fasinit(1);fasinit(3);
      jddate(bkh_dt,&ref_yy,(int16 *)&dum[0],(int16 *)&dum[0]);ref_yy=ref_yy%100;
      ref_jr=0;ref_ft=0;bd_inp=0;
      zeros(opmer,sizeof opmer);
      zeros(lkgkod,sizeof lkgkod);
      zeros(lkgnaam,sizeof lkgnaam);
      his_start_=mcnt-4;if(his_start_<0) his_start_=0;
			last_r_=0;
    }
redo:
    scrnum=0;scrget(1,270);z=1; first_=NO;
		if(his_start_>0){scraddpicto(10,0,76,11,3,1,18,0,4,"up"); }
		if((his_start_+4)<mcnt) {scraddpicto(11,0,76,16,3,1,13,0,4,"down"); }
		if(nr_>0){scraddpicto(12,0,0,22,4,2,93,0,4,"vorig"); }
		if(nr_<(TbCodaFiles[p_tbcoda_].AantalBew-1)) {scraddpicto(13,0,76,22,4,2,92,0,4,"volgend"); }
		nr_++;scrifld(z++,fm_ou2,&nr_);nr_--;scrifld(z++,fm_ou3,&TbCodaFiles[p_tbcoda_].AantalBew);
  	scrifld(z++,VarTextFmt(20,0),TbCodaFiles[p_tbcoda_].Naam);
		scrifld(z++,fm_odat,&TbCodaFiles[p_tbcoda_].Datum);scrifld(z++,fm_ou2,&TbCodaFiles[p_tbcoda_].BkhJournaal);scrifld(z++,fm_ou5,&TbCodaFiles[p_tbcoda_].VolgNr);
		volgnr=TbCodaFiles[p_tbcoda_].VolgNr; journl=TbCodaFiles[p_tbcoda_].BkhJournaal;
//		if(start_>0){ funckeys+=2; scraddpicto(1,0,76,1,4,2,18,0,4,"up"); }
//		if((start_+ScreenLines)<BewCount) {funckeys+=4;scraddpicto(2,0,76,22,4,2,13,0,4,"down"); }
		scrifld(z++,VarTextFmt(30,0),BewLijn[nr_].Naam); 
		if(is_nul((double)(bd_tot-bd_yetdiv)))scraddpicto(14,0,75,3,4,2,69,0,4,"bewaar combinatie");
		scrifld(z++,VarTextFmt(25,0),BewLijn[nr_].RekeningNr); 
		scrifld(z++,VarTextFmt(60,0),BewLijn[nr_].VrijeMededeling1); 
		if(BewLijn[nr_].GestrMededeling[0]){
			cstr_="+++"+ CString(BewLijn[nr_].GestrMededeling,12)+"+++";cstr_.Insert(6,'/');cstr_.Insert(11,'/');
			scrifld(z++,VarTextFmt(25,0),(char *)(LPCTSTR)cstr_); 
		}
		else scrifld(z++,VarTextFmt(25,0),BewLijn[nr_].KlantRef); 
		scrifld(z++,VarTextFmt(70,0),BewLijn[nr_].VrijeMededeling); 
		scrifld(z++,VarTextFmt(70,0),&BewLijn[nr_].VrijeMededeling[71]); 
    for(k=0;k<4;k++){/* display vorige boekingen */
      if((k+his_start_)>=mcnt) z+=9;
      else{
				n=his_start_+k;	n++;scrifld(z++,fm_ou2,&n);n--;
				ptb_=DIM_BEWLIJN*MAX_BDETAIL+his_start_+k;
				scrifld(z++,fm_od6_2,&tb[ptb_].bedrag);
				stu_dsp_=0; rec_dsp_=0;
				if(tb[ptb_].rec_nr>60000){stu_dsp_=3;rec_dsp_=tb[ptb_].rec_nr-60000;}
				else if(tb[ptb_].rec_nr<30001){stu_dsp_=1;rec_dsp_=tb[ptb_].rec_nr;}
				else{stu_dsp_=2;rec_dsp_=tb[ptb_].rec_nr-30000;}
				
				copy(s(stu_dsp_,1),buf1000,fldlen(stu_dsp_,0));
				fasinit(stu_dsp_);*u(stu_dsp_,1)=rec_dsp_;fasgeti(stu_dsp_);

				if(stu_dsp_==3){scrifld(z++,fm_os1,"G");scrifld(z++,fm_ogrb,&tb[ptb_].grb_tb);}
				else{
					if(stu_dsp_==1) scrifld(z++,fm_os1,"L");
					else scrifld(z++,fm_os1,"K");
					if(fldlen(stu_dsp_,2)) scrofld(z++,stu_dsp_,2,-1);
					else scrifld(z++,fm_ou5,&rec_dsp_);
				}
				zero(dsp_buf_,sizeof dsp_buf_);
				copy(s(stu_dsp_,3),dsp_buf_,fldlen(stu_dsp_,3)); scrifld(z++,VarTextFmt(28,0),dsp_buf_);
				copy(buf1000,s(stu_dsp_,1),fldlen(stu_dsp_,0));
				fasinit(4);*l(4,1)=tb[ptb_].recft; if(*l(4,1)) fasgeti(4);
				if(*u(4,20)) scrofld(z++,4,20,-1); else z++;
				fmt_=fm_ou2; if(tb[ptb_].jr_tb || tb[ptb_].vl_tb) fmt_=fm_ou2_;
				h=tb[ptb_].yy_tb;if(h>=100) h-=100; scrifld(z++,fmt_,&h);
				h=tb[ptb_].jr_tb;scrifld(z++,fm_ou2,&h);
				scrifld(z++,fm_ou5,&tb[ptb_].vl_tb);
				scraddpicto(20+k,z-1,1,0,2,1,540,0,0,"schrap"); 
		//		if(tb[ptb_].bedrag<0) dum[0]='D'; else dum[0]='C';	scrifld(20+n*10,fm_os1,dum);
      }
    }

		scrifld(z++,fm_od7_2,&bd_tot); 
		scrifld(z++,fm_od7_2,&bd_yetdiv);
    bd_=bd_tot-bd_yetdiv;	if(!is_nul(bd_)){scrifld(z++,fm_od7_2,&bd_);}  else z++;
		z_base=z;
    scrifld(z++,fm_ud7_2,&bd_inp); scrifld(z++,fm_uu5,&ref_ft);
    scrifld(z++,fm_uLKG,&lkg);
    scrifld(z++,fm_os8,lkgkod);
    scrifld(z++,fm_us30,lkgnaam);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_us20,opmer);
    if(analyt){
			k=3; if(anal_ask=='X') k=4;
			scraddpicto(15,z-1,4,0,2,1,130,0,k,"Analytische uitsplitsing"); 
		}
    //scrifld(z++,fm_uu2,&ref_jr);
    ref_yy=ref_yy%100;// scrifld(z++,fm_uu2_,&ref_yy);
		if(curs==0){
			curs=z_base+1;
			if(BewLijn[nr_].CodeVerrichting[0]=='0' && cmpstr(&BewLijn[nr_].CodeVerrichting[1],"01",2)!=0 && cmpstr(&BewLijn[nr_].CodeVerrichting[1],"02",2)!=0 && 
				cmpstr(&BewLijn[nr_].CodeVerrichting[1],"05",2)!=0) curs=z_base+3; // cheques, kosten, loketverrichting...
		}
		if(is_nul(BewLijn[nr_].Bedrag)) curs=-1;
    key=scrupd(curs,0x2E1);curs=z_base;F8_OK_cnt_=YES;
		if ((key/0x100)==1) key=(key&0xFF)+5000;

    if(key==106){
			for(k=0;k<MAX_BDETAIL;k++) if(cmpstr(&tb[nr_*MAX_BDETAIL+k].begin,&tb[DIM_BEWLIJN*MAX_BDETAIL+k].begin,sizeof tb[0])) break;	
			if(k>=MAX_BDETAIL) goto endsr;
      if(scr_ok("Wenst U echt deze boeking te annuleren ?")) goto endsr;
      goto redo;
    }
		if(key==5010 || key==5011){
  		if(key==5010) his_start_-=4;
	  	if(key==5011) {his_start_+=4; if(his_start_>mcnt) his_start_=mcnt-4;}
		  if(his_start_<0) his_start_=0;
		  goto redo;
		}
		if(key==5012 || key==5013){
      bd_=bd_tot;
      for(k=0;k<mcnt;k++){
				bd_-=tb[DIM_BEWLIJN*MAX_BDETAIL+k].bedrag;
      }
      if(!is_nul(bd_)) {errnum=10;goto redo;}			
  	  for(k=0;k<MAX_BDETAIL;k++) copy(&tb[DIM_BEWLIJN*MAX_BDETAIL+k].begin,&tb[nr_*MAX_BDETAIL+k].begin,sizeof tb[0]);	
	  	BewLijn[nr_].BkhOK=YES;
			if(key==5012) nr_--; else nr_++;
			goto redo_full;
		}
		if(key>=5020 && key<=5023){ // deleten van 1 lijn
      if(analyt){
				for(k=0;k<DIMAT;k+=DIMA)	if(tba[k].a_elem==MAX_BDETAIL*nr_+(his_start_+key-5020)*DIMA) break;
				if(k<DIMAT){
					for(j=k+DIMA;j<DIMAT;j+=DIMA) copy((char *)&tba[j].begin,(char *)&tba[j-DIMA].begin,sizeof tba[0]*DIMA);
					zero((char *)&tba[DIMAT-DIMA].begin,sizeof tba[0]*DIMA);
				}
      }
			bd_yetdiv-=tb[DIM_BEWLIJN*MAX_BDETAIL+his_start_+key-5020].bedrag;
			for(k=his_start_+key-5020+1;k<MAX_BDETAIL;k++){
				copy((char *)&tb[DIM_BEWLIJN*MAX_BDETAIL+k].begin,(char *)&tb[DIM_BEWLIJN*MAX_BDETAIL+k-1].begin,sizeof tb[0]);
				if(analyt) { // analytisch ook opschuiven
					for(j=0;j<DIMAT;j++) if(tba[j].a_elem==MAX_BDETAIL*nr_+k*DIMA) tba[j].a_elem-=DIMA;
				}
			}
			zero((char *)&tb[DIM_BEWLIJN*MAX_BDETAIL+k-1].begin,sizeof tb[0]);mcnt--;
      goto redo;

		}
 
    if(lkg=='L'){
      if(credt_allow) stutyp=1;
      else {errnum=34;curs=z_base+2;goto redo;}
    }
    else if(lkg=='K'){
      if(debit_allow) stutyp=2;
      else {errnum=34;curs=z_base+2;goto redo;}
    }
    else stutyp=3;
	  if(key==5001){
			copy(lkgnaam,s(stutyp,3),fldlen(stutyp,3));
			if(Search(stutyp,98)==0){copy(s(stutyp,3),lkgnaam,fldlen(stutyp,3));lkgnaam[fldlen(stutyp,3)]='\0';}
			else{curs=z_base+3; goto redo;}
			if(stutyp==3) last_r_=0;
	  }
		if(stutyp==3 && g_anal_tst()) {errnum=24;curs=z_base+3;goto redo;}
		zoek_op_bd=NO;
		if(key==110) {
			zoek_op_bd=YES; searbuf[SEARBFLEN]='\0';
			if(ref_ft && ref_jr==0){
				if(stutyp==1) ref_jr=DefAkJournaal;
				if(stutyp==2) ref_jr=DefVkJournaal;
			}
			if(ref_ft || !is_nul(bd_inp)){
				fasinit(4); *l(4,1)=ZoekFactuur(BewLijn[nr_].Naam,ref_ft,bd_inp);
				if(*l(4,1)){
					fasgeti(4);get_4lkg();
					copy(s(stutyp,3),lkgnaam,fldlen(stutyp,3));lkgnaam[fldlen(stutyp,3)]='\0';
          if((is_nul(bd_inp) || bd_inp==*d(4,32)) && !is_voldaan(*l(4,1))){
						bd_inp=*d(4,32);
						tab_add(d(4,32),(int16)*s(4,8),(int16)*s(4,9),*u(4,10),*l(4,1));
						bd_yetdiv+=bd_inp;BewLijn[nr_].UserChanged=YES;
						goto redo_0;
					}
				} else goto redo;
			}
			else{
				copy(lkgnaam,s(stutyp,3),fldlen(stutyp,3));
				if(*s(stutyp,3) && Search(stutyp,98)==0){
					copy(s(stutyp,3),lkgnaam,fldlen(stutyp,3));lkgnaam[fldlen(stutyp,3)]='\0';
					if(is_nul(bd_inp)) bd_inp=bd_tot-bd_yetdiv;
				}
				else{errnum=39;curs=z_base+3; goto redo;}
			}
    }
		if(!is_nul(bd_inp) || !is_nul(bd_tot-bd_yetdiv)){
			copy(lkgnaam,s(stutyp,3),fldlen(stutyp,3));
			if(Search(stutyp,0)==0){copy(s(stutyp,3),lkgnaam,fldlen(stutyp,3));lkgnaam[fldlen(stutyp,3)]='\0';}
			else{errnum=39;curs=z_base+3; goto redo;}
		}

		if(analyt && stutyp==3 && *u(stutyp,1)){/* default analytische uitsplitingen */
			for(ny=0;ny<DIMAT; ny+=DIMA) if(tba[ny].a_elem==MAX_BDETAIL*nr_+mcnt) break;
			if(ny>=DIMAT) for(ny=0;ny<DIMAT; ny+=DIMA) if(tba[ny].a_elem==0 && tba[ny].a_bedrag==0) break;
			if(ny>=DIMAT) ny=DIMAT-DIMA;
			if(fldlen(3,32) && last_r_!=*u(3,1)){/* default analytische uitsplitingen */
				for(k=0;k<DIMA;k++){
					if(fldlen(3,33+k*2) && *l(3,33+k*2)){
						if(ny<DIMAT-DIMA)	zero((char *)&tba[ny].begin,sizeof tba[0] *DIMA);
						anal_ask='J';break;
					}
				}
				last_r_=*u(3,1);
			}
		}
    if(key==5015){
      if(stutyp==3) anal_det(nr_,mcnt-1);
			key=107;
    }
    if(key==107) goto redo;

    if(!is_nul(bd_inp)){
			F8_OK_cnt_=0;
			if(stutyp!=3){
				if(zoeklk_r()==NO) goto redo;
				bd_yetdiv+=bd_inp;
				bd_inp=0;
			}
 			else{
        tab_add(&bd_inp,ref_yy,ref_jr,ref_ft,0);
        bd_yetdiv+=bd_inp;BewLijn[nr_].UserChanged=YES;

        if(errnum) goto redo;
      }
		}
    if(anal_ask=='J'){
      if(stutyp!=3) {errnum=69;curs=90;goto redo;}
      anal_det(nr_,mcnt-1);anal_ask='\0';
    }
		if(key==5014){
      for(k=0;k<MaxDefKop;k++){
				if(cmpstr(BewLijn[nr_].CodeVerrichting,DefaultKoppelingen[k].CodeVerrichting,8)==0 &&
			    cmpstr(BewLijn[nr_].RekeningNr,DefaultKoppelingen[k].RekeningNr,40)==0 &&
			    cmpstr(BewLijn[nr_].Naam,DefaultKoppelingen[k].Naam,40)==0) break;
			}
			copy(BewLijn[nr_].CodeVerrichting,DefaultKoppelingen[k].CodeVerrichting,8);
			copy(BewLijn[nr_].RekeningNr,DefaultKoppelingen[k].RekeningNr,40);
			copy(BewLijn[nr_].Naam,DefaultKoppelingen[k].Naam,40);
			DefaultKoppelingen[k].LKGRec=tb[DIM_BEWLIJN*MAX_BDETAIL].rec_nr;
			if(k==MaxDefKop && MaxDefKop<DIM_DEFKOP-1) MaxDefKop++;
			else if(MaxDefKop>=DIM_DEFKOP) errnum=64;
		}
		if(key==101 || key==108){
      bd_inp=bd_tot;
      for(k=0;k<mcnt;k++){
				bd_inp-=tb[DIM_BEWLIJN*MAX_BDETAIL+k].bedrag;
      }
      if(!is_nul(bd_inp)) {errnum=10;bd_inp=0;goto redo_0;}
			if(F8_OK_cnt_){
  	    for(k=0;k<MAX_BDETAIL;k++) copy(&tb[DIM_BEWLIJN*MAX_BDETAIL+k].begin,&tb[nr_*MAX_BDETAIL+k].begin,sizeof tb[0]);	
	  		BewLijn[nr_].BkhOK=YES;
				break;
			}
    }
  }
  endsr:;
}


static long ZoekFactuur(char *pnaam_,uint16 ft_nummer_,double bedrag_)  // zoek AK/VK factuur ahv nummer of bedrag
{
  int16 j,k,z,stu_,key,start_=0,mode_,only_facturen_=YES,max_ft_,max_ft_OK_,max_,d_lin_scr_=14,tb_off_;
  long used,retval_;
  double bd4_,bd_i_;
 

	scrget(1,7);scrupd(-3,0);
	fasinfo(4,1); used=*l(4,1);
	zero((char *)&TbZoekFactuur[0].rec4,sizeof TbZoekFactuur);max_ft_=0; max_ft_OK_=0;tb_off_=0;

  if(ft_nummer_){/* geldige facturen opzoeken via keys (snelheid) */
    for(k=0;k<40;k++){
      if(j_tab[k].nr && ((stutyp==1 && j_tab[k].typ==1) || (stutyp==2 && j_tab[k].typ==2))) { // echt zoeken naar AK of VK factuur
				fasinit(4);*s(4,2)=j_tab[k].nr;*u(4,3)=ft_nummer_;mode_=0;
				FOREVER{
					if(faskeyi(4,1,mode_)) break; mode_=2;
					if(*s(4,2)!=j_tab[k].nr || *u(4,3)!=ft_nummer_) break;
					if(*u(4,5)<60000){// alleen klt/lev
						TbZoekFactuur[max_ft_].rec4=*l(4,1);
						if(!is_voldaan(*l(4,1))){
							TbZoekFactuur[max_ft_].fullmatch=YES;
							copy((char *)&TbZoekFactuur[max_ft_].rec4,(char *)&TbZoekFactuur[100+max_ft_OK_].rec4,sizeof TbZoekFactuur[0]);
							max_ft_OK_++;
						}
						else if(*u(4,4)<=MinBkhDatum) {max_ft_--;}
						max_ft_++; if(max_ft_>=100) break;
					}
				}
      }
    }
  }
	else{
	  fasinit(4);*u(4,5)=1+(stutyp-1)*30000; mode_=1; //j_tab[k].nr;*u(4,3)=ft_nummer_;mode_=0;
		FOREVER{
			next4:;
			if(faskeyi(4,4,mode_)) break; mode_=2;
//		for(a=1;a<=used;a++){
//			*l(4,1)=a; if(fasgeti(4)) continue;
			if(*u(4,5)>(30000+(stutyp-1)*30000)) break;
			if(only_facturen_ && ((stutyp==1 && *s(4,2)!=DefAkJournaal) || (stutyp==2 && *s(4,2)!=DefVkJournaal))) goto next4;
			bd4_=*d(4,32);
			if(sys1840==NO && ((bedrag_<0 && bd4_>0) || (bedrag_>0 && bd4_<0))) goto next4;
			if(bd4_<0) bd4_=-bd4_;
			bd_i_=bedrag_;if(bd_i_<0) bd_i_=-bd_i_;
			if(bd4_>(bd_i_+afw_long+.005) || bd4_<(bd_i_-afw_long-.005)) goto next4;
			if(*u(4,5)<60000){ // alleen klt/lev
				TbZoekFactuur[max_ft_].rec4=*l(4,1);
				if(!is_voldaan(*l(4,1))){
					TbZoekFactuur[max_ft_].fullmatch=YES;
					copy((char *)&TbZoekFactuur[max_ft_].rec4,(char *)&TbZoekFactuur[100+max_ft_OK_].rec4,sizeof TbZoekFactuur[0]);
					max_ft_OK_++;
				} 
				else if(*u(4,4)<=MinBkhDatum) {max_ft_--;}
				max_ft_++; if(max_ft_>=100) break;
			}
		}
	}
	if(max_ft_==0) {errnum=14; return 0L;}
  start_=0;max_=max_ft_OK_; tb_off_=100;
  FOREVER{
    scrnum=0; scrget(1,271);z=1;
		scrifld(z++,VarTextFmt(30,0),pnaam_);
  	if(ft_nummer_){scrifld(z++,VarTextFmt(7,0),"FACTUUR");scrifld(z++,fm_ou5,&ft_nummer_);}
		else {scrifld(z++,VarTextFmt(7,0),"BEDRAG");scrifld(z++,fm_od7_2,&bedrag_);}
		for(k=start_;k<start_+d_lin_scr_;k++){
		  if(k>=max_) break;
			*l(4,1)=TbZoekFactuur[k+tb_off_].rec4;fasgeti(4);
			k++; scrifld(z++,fm_ou3,&k); k--; if(TbZoekFactuur[k+tb_off_].fullmatch) scrchat(z-1,0x8); else scrchat(z-1,0xFF);
			j=*s(4,2);scrifld(z++,fm_ou3,&j);
			scrofld(z++,4,3,-1);
			scrofld(z++,4,4,-1);
			scrifld(z++,fm_od7_2,d(4,32));
			if(*d(4,32)<0) scrifld(z++,fm_os1,"C"); else scrifld(z++,fm_os1,"D");
			stu_=get_4lkg();scrifld(z++,fm_os1,&lkglet[stu_-1]);
			scrofld(z++,stu_,3,30);
    }
    j=0;scrifld(116,fm_uu3,&j);
		if(tb_off_==0) scrifld(117,VarTextFmt(26,0)," F10 OPENSTAANDE facturen ");
		else scrifld(117,VarTextFmt(19,0)," F10 ALLE facturen ");
    key=scrupd(1,0x2A7);
		if(key==101 || key==106) {retval_=0; break;}
    if(key==102) start_-=d_lin_scr_;
    if(key==103) {start_+=d_lin_scr_;if(start_>max_ft_-d_lin_scr_) start_=max_ft_-d_lin_scr_;}
    if(start_<0) start_=0;
		if(j>0 && j<=max_) {retval_=TbZoekFactuur[tb_off_+j-1].rec4;break;}
		if(key==110){
			if(tb_off_==0){tb_off_=100;max_=max_ft_OK_;}
			else {tb_off_=0;max_=max_ft_;}
			start_=0;
		}
  }
  for(k=1;k<=3;k++) fasinit(k);
	return retval_;
}

static uint16 get_4lkg(void)
{
  int16 stu_;
  uint16 rec_;

  if(*u(4,5)<30000){rec_=*u(4,5);stu_=1;}
  else if(*u(4,5)<60000){rec_=*u(4,5)-30000;stu_=2;}
  else{rec_=*u(4,5)-60000;stu_=3;}
  fasinit(stu_);*u(stu_,1)=rec_;fasgeti(stu_);
  return stu_;
}

static int16 is_voldaan(long rec4_)
{
  int16 mode_,ret_val_;
  uint16 lkg_rec_,ref_jr_,ref_jn_,ref_vl_;
  double bd_;

  ret_val_=NO;
  copy(s(4,1),buf1000,fldlen(4,0));
  fasinit(4);*l(4,1)=rec4_;fasgeti(4);
  if(*u(4,5)>=60000) {ret_val_=YES;goto endsr;}/* GRB's steeds voldaan */
  if(*s(4,8)==0 && *s(4,9)==0 && *u(4,10)==0) goto endsr;
  ref_jr_=*s(4,8);ref_jn_=*s(4,9);ref_vl_=*u(4,10);lkg_rec_=*u(4,5);
  fasinit(4);*u(4,5)=lkg_rec_;*s(4,8)=ref_jr_;*s(4,9)=ref_jn_;*u(4,10)=ref_vl_;
  bd_=0;mode_=1;
  FOREVER{
    if(faskeyi(4,4,mode_)) break; mode_=2;
    if(*u(4,5)!=lkg_rec_) break;
    if(*s(4,8)!=ref_jr_ || *s(4,9)!=ref_jn_ || *u(4,10)!=ref_vl_) break;
    if(is_nul(*d(4,32))){
      *d(4,32)=valu_cnv(def_munt,"EUR",(double)(*l(4,7)),(double)0.01);
    }
    bd_+=*d(4,32);
  }
  if(is_nul(bd_)) ret_val_=YES;
  endsr:;
  copy(buf1000,s(4,1),fldlen(4,0));
  return ret_val_;
}
 
static void tab_add(double *pdbl_,uint16 ref_yy_,uint16 ref_jr_,uint16 ref_ft_,long ft_rec_)
{
  if(mcnt>=MAX_BDETAIL) {errnum=11;goto endsr;}
  tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].rec_nr=*u(stutyp,1)+30000*(stutyp-1);
  if(stutyp==3){
    tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].grb_tb=*l(stutyp,2);
    ref_yy_=0;
  }
  tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].bedrag=*pdbl_;
//  copy(buff7[1],buff7[0],6*sizeof buff7[0]);
//  copy(s(stutyp,3),buff7[6],20);buff7[6][20]='\0';
  tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].yy_tb=ref_yy_;tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].jr_tb=ref_jr_;tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].vl_tb=ref_ft_;
  copy(opmer,tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].opm_bkh,OPMLEN);
  tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].recft=ft_rec_;
	if(stutyp==2 && PandJournaal && ft_rec_ && *s(4,2)==PandJournaal){  // overboeking huur 
		if(*l(4,40) && *l(4,41) && *l(4,40)!=*l(4,41)){
			tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].GRBwacht=*l(4,40);tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].GRBoverb=*l(4,41);
		} else{tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].GRBwacht=0;tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].GRBoverb=0;}
	}
  mcnt++;
  if(mcnt==MAX_BDETAIL) errnum=11;
  endsr:;
}


static int16 zoeklk_r(void)
{
  int16 byte,curs,key,j,k,start_,lin,z,mcnt_res,stutyp_o;
  uint16 dt_bew,linenr;
  double bd_line_,bd_irest,bd_x,bd_thiskl=0,bd_,bd_fact=0,bd_disc=0,bd_df_;
  flag scrdata,found;
  char df_munt_[4],attr_;
				
  copy(def_munt,df_munt_,3);
 
  mcnt_res=mcnt;
//  copy(buff7[0],buff7res[0],sizeof buff7);
  copy(s(4,1),buf500,fldlen(4,0));

  zero((char *)&combi_nr[0],sizeof combi_nr);bd_=0;
  bd_irest=valu_cnv("EUR","EUR",bd_inp,(double)0.01);
  make_otab();
  begin:
  FOREVER{
    linenr=0;bd_line_=0;
    start_=0;
    curs=6;
    FOREVER{
      redo:
      scrnum=0; scrget(1,272);z=1;
      if((stutyp==1&&lvcd) || (stutyp==2&&klcd)) scrofld(z++,stutyp,2,6);
      else scrofld(z++,stutyp,1,-1);
      scrofld(z++,stutyp,3,-1);
			scrifld(z++,fm_us20,opmer);
      scrifld(z++,fm_od7_2,&bd_inp);
      scrifld(z++,fm_od7_2,&bd_irest);
      scrifld(z++,fm_uu3,&linenr);
      scrifld(z++,fm_ud7_2,&bd_line_);
      scrifld(z++,fm_os3,munt);
      scrifld(z++,VarTextFmt(10,0),"Opmerking");
      for(k=start_;k<start_+12;k++){
				if(k>=max_orec) break;
				*l(4,1)=open_recs[k].rec;
				if(fasgeti(4)) break;
				attr_=0xFF;
				for(j=0;j<MAX_CNIV;j++) if(combi_nr[j] && (combi_nr[j]-1)==k) break;
				if(j<MAX_CNIV) attr_=0x9;
				if(is_nul((double)(*d(4,32)-bd_irest))) attr_=8;
				for(j=0;j<DIM_BEWLIJN*MAX_BDETAIL+MAX_BDETAIL;j++) if(*l(4,1)==tb[j].recft) break;
				if(j<DIM_BEWLIJN*MAX_BDETAIL+MAX_BDETAIL) attr_=0;
				bd_x=*d(4,32);
				bd_df_=*d(4,32);
				lin=k+1;scrifld(z++,fm_ou3,&lin);scrchat(z-1,attr_);
				dt_bew=*u(4,4);found=NO;
				if((sys1862 &2) || (sys1862 &4)){
					if(*u(4,20)){dt_bew=*u(4,20);found=YES;}
				}
				byte=*s(4,2);scrifld(z++,fm_ou2,&byte);scrchat(z-1,attr_);
				scrofld(z++,4,3,-1); scrchat(z-1,attr_);
				scrifld(z++,fm_odat,&dt_bew);scrchat(z-1,attr_);
				if(bd_x>=0) scrifld(z++,fm_os1,"D");
				else scrifld(z++,fm_os1,"C");
				scrchat(z-1,attr_);
				scrifld(z++,fm_od7_2,&bd_x); scrchat(z-1,attr_);
				scrofld(z++,4,28,12);	scrchat(z-1,attr_);
				if(sys1818 & 1){
					scrofld(z++,4,28,10);scrchat(z-1,attr_);
					z+=2;
				}
				else if((sys1862 &4) && (sys1862 &1)){
					scrofld(z++,4,25,-1);scrchat(z-1,attr_);
					z+=2;
				}
				else{
					byte=*s(4,8); if(*s(4,9) || *u(4,10)) byte+=1900;
					scrifld(z++,fm_ou4_,&byte);scrchat(z-1,attr_);
					byte=*s(4,9); scrifld(z++,fm_ou2,&byte);scrchat(z-1,attr_);
					scrofld(z++,4,10,-1);scrchat(z-1,attr_);
				}
      }
      key=scrupd(curs,0x3A7);curs=6;
      if(key==103){
				if((start_+12)<max_orec) start_+=12;
				goto redo;
      }
      if(key==101 && linenr==0) break;
      if(key==102){
				start_-=12; if(start_<0) start_=0;
				goto redo;
      }
			if(key==106) {
				for(k=mcnt_res;k<MAX_BDETAIL;k++) zero(&tb[DIM_BEWLIJN*MAX_BDETAIL+k].begin,sizeof tb[0]);	
				goto return_;
			}
      if(key==106) goto return_;
      if(key==109){
				if(is_nul(bd_line_)) bd_line_=bd_irest;
				bd_fact+=bd_line_;
				fasinit(4);/* zonder referentie */
				break;
      }
      if(key==110){
				zero((char *)&combi_nr[0],sizeof combi_nr);bd_=0;
				if(zk_combi(0,0,&bd_,&bd_irest)){
					if((start_+12)<combi_nr[0]) start_=combi_nr[0]-1;
				}
				goto redo;
      }
      if(linenr==0 || linenr>max_orec) {errnum=34;goto redo;}
			*l(4,1)=open_recs[linenr-1].rec;
			if(fasgeti(4)) {errnum=39;goto redo;}
			if(is_nul(bd_line_)){
				bd_line_=valu_cnv("EUR",munt,*d(4,32),(double)0.01);
			}
	    bd_fact+=bd_line_;bd_disc+=*d(4,34);
		  break;
    }
    if(bd_line_){
      tab_add(&bd_line_,(int16)*s(4,8),(int16)*s(4,9),*u(4,10),*l(4,1));
      bd_thiskl-=bd_line_;
      bd_irest-=bd_line_;
      if(errnum) goto redo;
    }
    if(is_nul(bd_irest)) break;
    if(key==101) break;
  }
  
  FOREVER{
    if(is_nul(bd_irest)) break;
    if(sysdiff==0){
      for(k=0;k<6;k++){
				*u(3,1)=df_recnr[k+5]-60000;
				fasgeti(3);
				copy(s(3,3),gnm_diff[k],20);
      }
      sysdiff=1;
    }

    bd_=-bd_thiskl;
    linenr=0;
    fasinit(3);
    bd_line_=bd_irest;curs=5;
    redo_31:
    scrnum=0;scrget(1,273); z=1;
    scrifld(z++,fm_od7_2,&bd_fact);
    bd_=-bd_thiskl+bd_irest;scrifld(z++,fm_od7_2,&bd_);
    scrifld(z++,fm_ud7_2,&bd_line_); scrifld(z++,fm_od7_2,&bd_disc);
    scrifld(z++,fm_uu2,&linenr);
    scrfld(z++,3,3);
    for(k=0;k<6;k++){
			if(gnm_diff[k][0]){
				lin=k+1;scrifld(z,fm_ou2,&lin);
				if(bd_irest<0 && k%2) scrchat(z,6);
				if(bd_irest>0 && (k+1)%2) scrchat(z,6);
				z++;
				scrifld(z++,fm_ogrb,&df_grb[k+5]);
				scrifld(z++,fm_os20,gnm_diff[k]);
			}
    }
    key=scrupd(curs,0x0E0);curs=5;
    if(key==106) {
			for(k=mcnt_res;k<MAX_BDETAIL;k++) zero(&tb[DIM_BEWLIJN*MAX_BDETAIL+k].begin,sizeof tb[0]);	
			goto return_;
		}
    if(key==107) goto begin;
    if(is_nul(bd_line_)) goto redo_31;
    if(linenr){
      if(linenr>6) {curs=5;errnum=34;goto redo_31;}
      *l(3,2)=df_grb[linenr-1+5];
      if(faskeyi(3,1,0)) {curs=5;errnum=39;goto redo_31;}
    }
    else{
      if(Search(3,0)) {curs=6;errnum=39;goto redo_31;}
    }
    stutyp_o=stutyp;stutyp=3;
    tab_add(&bd_line_,0,0,0,0);
    stutyp=stutyp_o;
    if(errnum) goto redo;
		bd_thiskl-=bd_line_;
    bd_irest-=bd_line_;
    scrdata=YES;
  }
  copy(buf500,s(4,1),fldlen(4,0));
  return YES;
 
  return_:
  mcnt=mcnt_res;
//  copy(buff7res[0],buff7[0],sizeof buff7);
  copy(buf500,s(4,1),fldlen(4,0));
  return NO;
}

static uint16 zk_combi(int16 beg_,int16 niv_,double *pbd_beg_,double *ptotaal_)
{
  int16 j,k;
  double bd_;

  if(niv_>=MAX_CNIV) return NO;
  for(k=beg_;k<max_orec;k++){
    for(j=0;j<mcnt;j++) if(open_recs[k].rec==tb[j].recft) break;
    if(j<mcnt) continue;
    bd_=*pbd_beg_+open_recs[k].bedrag;
    if(is_nul(bd_-*ptotaal_)) break;
    if(zk_combi(k+1,niv_+1,&bd_,ptotaal_))break;
  }
  if(k<max_orec){combi_nr[niv_]=k+1; return YES; }
  return NO;
}



static int16 make_otab(void)
{
  int16 k,pos_,posr_,end_;
  uint16 first, r_yy,r_jr,r_nr;
  double ebd_;

  fasinit(4);
  searcnr=*u(stutyp,1)+(stutyp-1)*30000;
  *u(4,5)=searcnr;

  first=YES; end_=NO; posr_=0; pos_=0; ebd_=0; max_orec=0;
  FOREVER{
    if(faskeyi(4,4,2)) end_=YES;
    if(!end_ && *u(4,5)!=searcnr) end_=YES;
    if(!end_ && first){
      r_yy=*s(4,8); r_jr=*s(4,9); r_nr=*u(4,10);
      first=NO;
    }
    if(end_ || *s(4,8)!=r_yy || r_jr!=*s(4,9) || r_nr!=*u(4,10)){
      if(is_nul(ebd_)){
	for(k=posr_;k<pos_;k++) zero((char *)&open_recs[k].rec,sizeof open_recs[0]);
	pos_=posr_;
      }
      ebd_=0;posr_=pos_;
      r_yy=*s(4,8); r_jr=*s(4,9); r_nr=*u(4,10);
      if(end_) break;
    }
    open_recs[pos_].bedrag=*d(4,32);
    open_recs[pos_++].rec=*l(4,1);
    ebd_+=*d(4,32);
    if(pos_>=DIM_OPEN) break;
  }
  max_orec=pos_;
  return pos_;
}

static void ZoekBewegingen(int p_tbcoda_)
{
  int16 j,k,nr_,len_,yy_,dum1,dum2,stu_;
  flag found,boekalsvoorschot_;
	uint16 rf_vl=0,rf_yy=0,rf_jr=0;
	double bd_disc_;
	char klantnr_[10],ftnr_[10];
	CString cstr_;
	
		
  for(nr_=0;nr_<BewCount;nr_++){
		if(BewLijn[nr_].Bedrag==0) continue;
		fasinit(2);
		if(BewLijn[nr_].Bedrag>0 && BewLijn[nr_].GestrMededeling[0]  && (cmpstr(&BewLijn[nr_].CodeVerrichting[1],"01",2)==0 || cmpstr(&BewLijn[nr_].CodeVerrichting[1],"02",2)==0)){ // klant betaalt met gestructureerde mededeling 
			zero(klantnr_,sizeof klantnr_);zero(ftnr_,sizeof ftnr_);
			copy(&BewLijn[nr_].GestrMededeling[0],klantnr_,5);
			copy(&BewLijn[nr_].GestrMededeling[5],ftnr_,5);
			if(klcd==NO || (sys1848 & 1)){
				*u(2,1)=val(klantnr_);errnum=fasgeti(2);
			}
			else{
				len_=fldlen(2,2); if(len_>5) len_=5;
				copy(klantnr_,s(2,2),len_);
				if(klcd) errnum=faskeyi(2,1,0);
			}
			if(errnum)  continue; // foute klant
			BewLijn[nr_].KlantRec=*u(2,1);
			stutyp=2; lkg='K'; rec_nr=*u(2,1)+30000; rf_vl=val(ftnr_);
			jddate(bkh_dt=TbCodaFiles[p_tbcoda_].Datum,&yy_,&dum1,&dum2);yy_%=100;
    	if(yy_<50) yy_+=100; else if(yy_>=150) yy_-=100; // correctie y2000 
			found=NO;
			for(j=0;j<5;j++){/* probeer 5 laatste jaren */
				for(k=0;k<80;k++){/* probeer alle verkoopjournalen */
					if(j_tab[k].typ==2){
						fasinit(4);*u(4,5)=rec_nr;*s(4,8)=yy_-j;*s(4,9)=j_tab[k].nr;*u(4,10)=rf_vl;
						if(faskeyi(4,4,1)==0){
							if(*u(4,5)==rec_nr && *s(4,8)==yy_-j && *s(4,9)==j_tab[k].nr && *u(4,10)==rf_vl){
								rf_yy=yy_-j;rf_jr=j_tab[k].nr;found=YES;break;
							}
						}
					}
				}
				if(found) break;
			}
			if(found && !is_voldaan(*l(4,1)) && (is_nul((double)(*d(4,32)-BewLijn[nr_].Bedrag)) || (df_recnr[6] && is_nul((double)(*d(4,32)-(BewLijn[nr_].Bedrag+*d(4,34))))))){// ook eventueel rekening houden met disconto of kredietbeperking
				bd_disc_=0; if(*d(4,32)!=BewLijn[nr_].Bedrag && df_recnr[6] && is_nul((double)(*d(4,32)-(BewLijn[nr_].Bedrag+*d(4,34))))) bd_disc_=*d(4,34); // disconto / kredietbeperking
				tb[nr_*MAX_BDETAIL].rec_nr=*u(2,1)+30000;
				tb[nr_*MAX_BDETAIL].bedrag=BewLijn[nr_].Bedrag+bd_disc_;
				tb[nr_*MAX_BDETAIL].yy_tb=*s(4,8);tb[nr_*MAX_BDETAIL].jr_tb=*s(4,9);tb[nr_*MAX_BDETAIL].vl_tb=rf_vl;
//				tb[nr_*MAX_BDETAIL].yy_tb=ref_yy;tb[nr_*MAX_BDETAIL].jr_tb=ref_jr;tb[nr_*MAX_BDETAIL].vl_tb=rf_vl;
//				copy(opmer,tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].opm_bkh,OPMLEN);
				tb[nr_*MAX_BDETAIL].recft=*l(4,1);
				BewLijn[nr_].KlantRec=*u(2,1);
        BewLijn[nr_].RefJaar=rf_yy;
        BewLijn[nr_].RefJournaal=rf_jr;
        BewLijn[nr_].RefVolgNr=rf_vl;
				BewLijn[nr_].BkhOK=YES;
        if(bd_disc_){ // disconto/kredietbeperking afboeken op rekening
					tb[nr_*MAX_BDETAIL+1].rec_nr=df_recnr[6];
					tb[nr_*MAX_BDETAIL+1].bedrag=-bd_disc_;
					tb[nr_*MAX_BDETAIL+1].yy_tb=*s(4,8);tb[nr_*MAX_BDETAIL+1].jr_tb=*s(4,9);tb[nr_*MAX_BDETAIL+1].vl_tb=rf_vl;
					tb[nr_*MAX_BDETAIL+1].recft=*l(4,1);
				}
			}
			else{
				BewLijn[nr_].KlantRec=*u(2,1);
        BewLijn[nr_].RefJaar=yy_;
        BewLijn[nr_].RefVolgNr=rf_vl;
				for(k=0;k<80;k++) if(j_tab[k].typ==2) break;
				BewLijn[nr_].RefJournaal=j_tab[k].nr;
			}
			goto next_bew;
		}
		for(k=0;k<MaxDefKop;k++){ // probeer defaults
			if(cmpstr(DefaultKoppelingen[k].CodeVerrichting,BewLijn[nr_].CodeVerrichting,sizeof BewLijn[nr_].CodeVerrichting)) continue;
			if(cmpstr(&DefaultKoppelingen[k].CodeVerrichting[1],"0450",4)==0 && DefaultKoppelingen[k].RekeningNr[0]){ // als rekening is ingevuld, dan ook bij BC hierop checken 
				if(cmpstr(DefaultKoppelingen[k].RekeningNr,BewLijn[nr_].RekeningNr,sizeof BewLijn[nr_].RekeningNr)) continue;
			}
			else if(cmpstr(&DefaultKoppelingen[k].CodeVerrichting[1],"0450",4) && DefaultKoppelingen[k].RekeningNr[0]){ // als rekening is ingevuld, dan hierop checken 
				if(cmpstr(DefaultKoppelingen[k].RekeningNr,BewLijn[nr_].RekeningNr,sizeof BewLijn[nr_].RekeningNr)) continue;
			}
			else if(cmpstr(DefaultKoppelingen[k].Naam,BewLijn[nr_].Naam,sizeof BewLijn[nr_].Naam)) continue; // anders moet naam gelijk zijn 
			if(DefaultKoppelingen[k].LKGRec>60000){ // grb
				fasinit(3);*u(3,1)=DefaultKoppelingen[k].LKGRec-60000;
				if(fasgeti(3)==0){
					tb[nr_*MAX_BDETAIL].rec_nr=*u(3,1)+60000;
					tb[nr_*MAX_BDETAIL].grb_tb=*l(3,2);
					tb[nr_*MAX_BDETAIL].bedrag=BewLijn[nr_].Bedrag;
					BewLijn[nr_].BkhOK=YES;
					goto next_bew;
				}
			}
			else{ // klant/leverancier
				stu_=1; if(DefaultKoppelingen[k].LKGRec>30000) stu_=2;
				fasinit(stu_);*u(stu_,1)=DefaultKoppelingen[k].LKGRec-(stu_-1)*30000;
				boekalsvoorschot_=NO;
				if(fasgeti(stu_)==0){
					if(stu_==2){
						for(j=0;j<20;j++) if(*u(2,1)==loc_klt[j]) break;
						if(j<20) boekalsvoorschot_=YES;
					}
					if(boekalsvoorschot_){
						tb[nr_*MAX_BDETAIL].rec_nr=*u(stu_,1)+(stu_-1)*30000;
						tb[nr_*MAX_BDETAIL].bedrag=BewLijn[nr_].Bedrag;
						tb[nr_*MAX_BDETAIL].yy_tb=0;tb[nr_*MAX_BDETAIL].jr_tb=0;tb[nr_*MAX_BDETAIL].vl_tb=0;
						tb[nr_*MAX_BDETAIL].recft=0;
						BewLijn[nr_].KlantRec=*u(2,1);
						BewLijn[nr_].RefJaar=0;
						BewLijn[nr_].RefJournaal=0;
						BewLijn[nr_].RefVolgNr=0;
						BewLijn[nr_].BkhOK=YES;
					}
					else if(FindFactuurOpBedrag(DefaultKoppelingen[k].LKGRec, BewLijn[nr_].Bedrag)){
						bd_disc_=0; if(*d(4,32)!=BewLijn[nr_].Bedrag && (df_recnr[6] && *d(4,32)==(BewLijn[nr_].Bedrag+*d(4,34)))) bd_disc_=*d(4,34); // disconto / kredietbeperking
						rf_yy=*s(4,8); rf_jr=*s(4,9);rf_vl=*u(4,10);
						tb[nr_*MAX_BDETAIL].rec_nr=*u(stu_,1)+(stu_-1)*30000;
						tb[nr_*MAX_BDETAIL].bedrag=BewLijn[nr_].Bedrag+bd_disc_;
						tb[nr_*MAX_BDETAIL].yy_tb=*s(4,8);tb[nr_*MAX_BDETAIL].jr_tb=*s(4,9);tb[nr_*MAX_BDETAIL].vl_tb=rf_vl;
		//				tb[nr_*MAX_BDETAIL].yy_tb=ref_yy;tb[nr_*MAX_BDETAIL].jr_tb=ref_jr;tb[nr_*MAX_BDETAIL].vl_tb=rf_vl;
		//				copy(opmer,tb[DIM_BEWLIJN*MAX_BDETAIL+mcnt].opm_bkh,OPMLEN);
						tb[nr_*MAX_BDETAIL].recft=*l(4,1);
						if(stu_==2) BewLijn[nr_].KlantRec=*u(2,1);
						BewLijn[nr_].RefJaar=rf_yy;
						BewLijn[nr_].RefJournaal=rf_jr;
						BewLijn[nr_].RefVolgNr=rf_vl;
						BewLijn[nr_].BkhOK=YES;
						if(bd_disc_){ // disconto/kredietbeperking afboeken op rekening
							tb[nr_*MAX_BDETAIL+1].rec_nr=df_recnr[6];
							tb[nr_*MAX_BDETAIL+1].bedrag=-bd_disc_;
							tb[nr_*MAX_BDETAIL+1].yy_tb=*s(4,8);tb[nr_*MAX_BDETAIL+1].jr_tb=*s(4,9);tb[nr_*MAX_BDETAIL+1].vl_tb=rf_vl;
							tb[nr_*MAX_BDETAIL+1].recft=*l(4,1);
						}
					}
					else{
						if(stu_==2) BewLijn[nr_].KlantRec=*u(2,1);
						BewLijn[nr_].RefJaar=yy_;
						BewLijn[nr_].RefVolgNr=rf_vl;
						for(k=0;k<80;k++) if(j_tab[k].typ==2) break;
						BewLijn[nr_].RefJournaal=j_tab[k].nr;
					}
					goto next_bew;
				}
			}
		}

		if(BewLijn[nr_].Bedrag<0 && CodaSettings.WachtRekeningBetalingen){
			fasinit(3);*l(3,2)=CodaSettings.WachtRekeningBetalingen;
			if(faskeyi(3,1,0)==0){
				tb[nr_*MAX_BDETAIL].rec_nr=*u(3,1)+60000;
				tb[nr_*MAX_BDETAIL].grb_tb=*l(3,2);
				tb[nr_*MAX_BDETAIL].bedrag=BewLijn[nr_].Bedrag;
				copy(BewLijn[nr_].Naam,tb[nr_*MAX_BDETAIL].opm_bkh,20);
				BewLijn[nr_].BkhOK=YES;
			}
		}
		else if(BewLijn[nr_].CodeVerrichting[0]=='1'){
			fasinit(3);*l(3,2)=TbCodaFiles[p_tbcoda_].OvrRekening;
			if(faskeyi(3,1,0)==0){
				tb[nr_*MAX_BDETAIL].rec_nr=*u(3,1)+60000;
				tb[nr_*MAX_BDETAIL].grb_tb=*l(3,2);
				tb[nr_*MAX_BDETAIL].bedrag=BewLijn[nr_].Bedrag;
				BewLijn[nr_].BkhOK=YES;
			}
		}
		else if(cmpstr(&BewLijn[nr_].CodeVerrichting[1],"0453",4)==0){ // storting
			fasinit(3);*l(3,2)=TbCodaFiles[p_tbcoda_].StortingRekening;
			if(faskeyi(3,1,0)==0){
				tb[nr_*MAX_BDETAIL].rec_nr=*u(3,1)+60000;
				tb[nr_*MAX_BDETAIL].grb_tb=*l(3,2);
				tb[nr_*MAX_BDETAIL].bedrag=BewLijn[nr_].Bedrag;
				BewLijn[nr_].BkhOK=YES;
			}
		}
		next_bew:;
	}
}

static long FindFactuurOpBedrag(uint16 lk_rec_, double ftbedrag_)
{
	int stu_,mode_;

	stu_=1; if(lk_rec_>30000) stu_=2;

	fasinit(4);*u(4,5)=lk_rec_; mode_=1; //j_tab[k].nr;*u(4,3)=ft_nummer_;mode_=0;
	FOREVER{
		next4:;
		if(faskeyi(4,4,mode_)) break; mode_=2;
		if(*u(4,5)>(30000+(stu_-1)*30000)) break;
		if(*u(4,5)!=lk_rec_) goto next4;
		if((stu_==1 && *s(4,2)!=DefAkJournaal) || (stu_==2 && *s(4,2)!=DefVkJournaal)) goto next4;
		if(!is_voldaan(*l(4,1)) && (*d(4,32)==ftbedrag_ || (df_recnr[6] && *d(4,32)==(ftbedrag_+*d(4,34))))) return (long)(*l(4,1)); // ook eventueel rekening houden met disconto of kredietbeperking
	}
  return 0L;
}


static bool PdfCodaFile(int p_tbcoda_,int BkhDetail)
{
  int16 j,k,n,z,p_med_,flg_grp_blok_;
	char mededeling_[60];
	CString cstr_;
	double bd_,tot_booked_;
	
//	if(ReadCodaFile(p_tbcoda_)==false) return false;
  getsysprNew(3,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) return false;
	LinFree=999;
  prtnew();
	prtfld(25,1,25); prttext("  Rekening : ");prtifld(VarTextFmt(20,0),TbCodaFiles[p_tbcoda_].IBAN,-1);prtifld(VarTextFmt(25,0),TbCodaFiles[p_tbcoda_].Naam,-1);
  prttext("<t92>");prtfld(25,2,-1);prttext("<t120>Blz.<ppp>.");
  prtbuf(1);
	prttext("<t25>Boekdatum : ");prtifld(fm_odat,&TbCodaFiles[p_tbcoda_].Datum,-1);
	prttext("     journaal : ");prtifld(fm_ou2,&TbCodaFiles[p_tbcoda_].BkhJournaal,-1);prttext("/");prtifld(fm_ou5,&TbCodaFiles[p_tbcoda_].VolgNr,-1);
  prtbuf(2);
  z=1;
	prtitab(z,fm_ou4_,&PrintBewLijn.VolgNr,1,-1); prttitle(z++,"Nr.",0x13);
	prtitab(z,fm_odat,&PrintBewLijn.ValutaDatum,1,-1); prttitle(z++,"Val.dat",0x13);
	prtitab(z,fm_od7_2,&PrintBewLijn.Bedrag,1,-1); prttitle(z++,"Bedrag",0x13);
	prtitab(z,fm_od7_2,&PrintBewLijn.SubBedrag,1,-1); prttitle(z++,"SubBedrag",0x13);
	prtitab(z,fm_os26,PrintBewLijn.Naam,1,-1); prttitle(z++,"Opdrachtgever",3);
	prtitab(z,fm_os26,PrintBewLijn.RekeningNr,1,-1); prttitle(z++,"RekeningNr",3);
	prtitab(z,VarTextFmt(45,0),mededeling_,1,-1); prttitle(z++,"Mededeling",3);
  //prtitab(z,fm_os5,st.fact_nr,3,-1); prttitle(z++,"Ft.nr.",0x13);
  //prtitab(z,fm_uLKG,&lkg,3,-1); prttitle(z++,"LKG",3);
  //prtitab(z,fm_us30,lkgnaam,1,-1); prttitle(z++,"Rekening",3);
  //prtitab(z,fm_us20,opmerk,1,-1); prttitle(z++,"Opmerking",3);
  //prtitab(z,fm_ou3,&st.rf_yy,1,-1); prttitle(z++,"",0x13);
  //prtitab(z,fm_ou2,&st.rf_jr,1,-1); prttitle(z++,"",0x13);
  //prtitab(z,fm_ou5,&st.rf_vl,1,-1); prttitle(z++,"",0x13);
  prtbuf(3);

	p_pdfname(TbCodaFiles[p_tbcoda_].IBAN,TbCodaFiles[p_tbcoda_].Datum,0);
	if(CodaFileHdr.NieuwSaldo || CodaFileHdr.VorigSaldo){
	  zeroL((char *)&PrintBewLijn.VolgNr,sizeof PrintBewLijn);zero(mededeling_,sizeof mededeling_);
	  PrintBewLijn.Bedrag=CodaFileHdr.VorigSaldo;
	  copy("<-- Vorig saldo",mededeling_,16);
	  for(j=0;j<20;j++) prtinfo(j,2);nextline();
	}
	flg_grp_blok_=NO;tot_booked_=0;
  for(k=0;k<BewCount;k++){
		copy((char *)&BewLijn[k].VolgNr,(char *)&PrintBewLijn.VolgNr,sizeof BewLijn[0]);p_med_=0;
	  zero(mededeling_,sizeof mededeling_);
		if(PrintBewLijn.GestrMededeling[0]){
			cstr_="+++"+ CString(PrintBewLijn.GestrMededeling,12)+"+++";cstr_.Insert(6,'/');cstr_.Insert(11,'/');
			copy((char *)(LPCTSTR)cstr_,mededeling_,20);
		}
		else if(PrintBewLijn.KlantRef[0] && PrintBewLijn.GroepBetaling) copy(PrintBewLijn.KlantRef,mededeling_,35);
		else{
			for(p_med_;p_med_<3;p_med_++) if(PrintBewLijn.VrijeMededeling[p_med_*45]) break;
			if(p_med_<3) copy(&PrintBewLijn.VrijeMededeling[p_med_*45],mededeling_,45);
			p_med_++;
		}
		if(flg_grp_blok_ && PrintBewLijn.Bedrag){ // einde groepsbetaling 
			prttext("               -----------------------------------------------------------------------");nextline();flg_grp_blok_=NO;
		}
		j=0; if(PrintBewLijn.SubBedrag) j=4;
		for(j;j<20;j++) prtinfo(j,0);nextline();
		for(p_med_;p_med_<3;p_med_++){
			if(PrintBewLijn.VrijeMededeling[p_med_*45]){
				copy(&PrintBewLijn.VrijeMededeling[p_med_*45],mededeling_,45);
				prtinfo(7,0);nextline();
			} else break;
		}
		if(PrintBewLijn.GroepBetaling && CodaSettings.SkipGroepsDetail!='J'){ // begin groepsbetaling 
			prttext("               -----------------------------------------------------------------------");nextline();flg_grp_blok_=YES;
		}
		if(BkhDetail){
			bd_=PrintBewLijn.Bedrag;
		  for(j=0;j<MAX_BDETAIL;j++){
			  n=k*MAX_BDETAIL+j;
				if(!is_nul(tb[n].bedrag)){
					bd_-=tb[n].bedrag; tot_booked_+=tb[n].bedrag;
					prttext("<t10b>"); 
					//prtifld(fm_uu2,&TbCodaFiles[p_tbcoda_].BkhJournaal,-1); prttext(" ");
					//prtifld(fm_uu5,&TbCodaFiles[p_tbcoda_].VolgNr,-1); prttext(" ");
					//prtifld(fm_udat,&TbCodaFiles[p_tbcoda_].Datum,-1); prttext(" ");
					prtifld(fm_od6_2,&tb[n].bedrag,-1); prttext(" ");
					if(tb[n].rec_nr<30000){fasinit(1);*u(1,1)=tb[n].rec_nr;fasgeti(1);prtfld(1,3,-1);}
					else if(tb[n].rec_nr<60000) {fasinit(2);*u(2,1)=tb[n].rec_nr-30000;fasgeti(2);prtfld(2,3,-1);}
					else {fasinit(3);*u(3,1)=tb[n].rec_nr-60000;fasgeti(3);prtfld(3,3,-1); prttext(" "); prtfld(3,2,-1);}
					prttext("<t65>");
					z=tb[n].yy_tb; if(z>100) z-=100; prtifld(fm_uu2,&z,-1); prttext(" ");
					z=tb[n].jr_tb;prtifld(fm_uu2,&z,-1); prttext(" ");
					prtifld(fm_uu5,&tb[n].vl_tb,-1); prttext(" ");
					prtifld(VarTextFmt(20,0),tb[n].opm_bkh,-1);
					nextline();
				}
			}
			if(!is_nul(bd_)){prttext("<eb>*** FOUT verschil : ");prtifld(fm_od6_2,&bd_,-1); nextline();}
		}
	}
	zeroL((char *)&PrintBewLijn.VolgNr,sizeof PrintBewLijn);zero(mededeling_,sizeof mededeling_);
  if(CodaFileHdr.NieuwSaldo || CodaFileHdr.VorigSaldo){
	  PrintBewLijn.Bedrag=CodaFileHdr.NieuwSaldo;
	  copy("<-- Nieuw saldo",mededeling_,16);
	  for(j=0;j<20;j++) prtinfo(j,2);nextline();
	}
	if(BkhDetail){
  	bd_=CodaFileHdr.NieuwSaldo-CodaFileHdr.VorigSaldo-tot_booked_;
	  if(!is_nul(bd_)){
			nextline();
			if(CodaFileHdr.NieuwSaldo==0 && CodaFileHdr.VorigSaldo==0 && tot_booked_){ // gedeeltelijke coda
				prttext("<eb>*** Totaal bewegingen : ");prtifld(fm_od6_2,&tot_booked_,-1); 
			}
			else{
			  prttext("<eb>*** FOUT verschil : ");prtifld(fm_od6_2,&bd_,-1); 
			}
		}
    nextline();
	}
	prtclose();

	return true;
}

static bool ReadCodaFile(int p_tbcoda_)
{
  uint16 k,nr_,file_chk_,last_bew0_,volgnr_,linelen_=130;
	long len_;
	char CRecord[150],subgr_[3],buf_[100];
	CFile cfile_;
	long fpos_;
	CString cstr_,cstr1_,cmed2_,cmed3_;

	copy((char *)TbCodaFiles[p_tbcoda_].IBAN,(char *)CodaFileHdr.IBAN,sizeof TbCodaFiles[0]);
	if(cfile_.Open(TbCodaFiles[p_tbcoda_].FileNaam,CFile::modeRead,0)==false) {errnum=1; return false;}
	len_=cfile_.GetLength();
	if(len_%130==0 || (len_+2)%130==0) linelen_=130; // minstens 5 records en moet een veelvoud van 128+2 zijn, kan zijn de laatste niet
	else if(len_%129==0 || (len_+1)%129==0) linelen_=129; // enkel x0A, kan zijn laatste niet
	else{cfile_.Close();errnum=1; return false;}
	fpos_=TbCodaFiles[p_tbcoda_].FilePosInFile;file_chk_=0;volgnr_=0;
	zeroL((char *)&BewLijn[0].VolgNr,sizeof BewLijn);BewCount=0;cmed2_="";cmed3_="";last_bew0_=0;zero(CRecord,sizeof CRecord);
	FOREVER{
next_rec:;
		cfile_.Seek(fpos_,CFile::begin); fpos_+=linelen_;
	  if(cfile_.Read(CRecord,linelen_)<128) break;
		if(CRecord[0]=='0'){
			file_chk_++;
		}
		if(CRecord[0]=='1'){
			file_chk_++;
		}
		if(CRecord[0]=='2'){
			if(CRecord[1]=='1'){
				copy(CRecord,&rec21.rec_type,128);
				if(CodaSettings.SkipGroepsDetail=='J' && rec21.ver_code[0]>='5'){ // geen detail van groepsbetalingen
					if(BewLijn[BewCount].VolgNr){
						cmed2_.Trim();len_=cmed2_.GetLength();if(len_>sizeof BewLijn[0].VrijeMededeling) len_=sizeof BewLijn[0].VrijeMededeling;
						if(len_ && BewLijn[BewCount].VrijeMededeling[0]=='\0') copy((char *)(LPCTSTR)cmed2_,BewLijn[BewCount].VrijeMededeling,len_);
						cmed3_.Replace("      ","  ");cmed3_.Trim();len_=cmed3_.GetLength();if(len_>sizeof BewLijn[0].VrijeMededeling1) len_=sizeof BewLijn[0].VrijeMededeling1;
						if(len_ && BewLijn[BewCount].VrijeMededeling1[0]=='\0') copy((char *)(LPCTSTR)cmed3_,BewLijn[BewCount].VrijeMededeling1,len_);	
						if(BewLijn[BewCount].DetailNr==0) last_bew0_=BewCount;BewLijn[BewCount].GroepBetaling=1;
						BewCount++;
						if(rec21.type_med=='1'){
							cstr_=CString(&rec21.mededel[3],20);cstr_.Trim();
							if(BewLijn[last_bew0_].GestrMededeling[0]=='\0') copy((char *)(LPCTSTR)cstr_,BewLijn[last_bew0_].GestrMededeling,cstr_.GetLength());
						}
						else{
							cstr_=CString(rec21.mededel,53);cstr_.Trim();
							if(BewLijn[last_bew0_].VrijeMededeling[0]=='\0') copy((char *)(LPCTSTR)cstr_,BewLijn[last_bew0_].VrijeMededeling,cstr_.GetLength());
						}
						if(rec21.type_med=='1' && BewLijn[last_bew0_].RekeningNr[0]=='\0'){
							len_=cstr_.GetLength();if(len_>sizeof BewLijn[0].RekeningNr) len_=sizeof BewLijn[0].RekeningNr;
							if(len_==12) copy((char *)(LPCTSTR)cstr_,BewLijn[last_bew0_].RekeningNr,len_);
						}
						//cstr1_=CString(BewLijn[last_bew0_].Naam);cstr1_+=" "; cstr1_+=cstr_; len_=cstr1_.GetLength();
						//if(len_>sizeof BewLijn[0].Naam) len_=sizeof BewLijn[0].Naam;
						//copy((char *)(LPCTSTR)cstr1_,BewLijn[last_bew0_].Naam,len_);
						cmed2_="";cmed3_="";						
					}
					else if(last_bew0_>=0 && last_bew0_<=BewCount && cmpstr(&BewLijn[last_bew0_].CodeVerrichting[1],"13",2)==0){ // detail krediet op 2-de lijn 
						if(rec21.type_med=='1'){
							cstr_=CString(&rec21.mededel[3],20);cstr_.Trim();
							if(BewLijn[last_bew0_].GestrMededeling[0]=='\0') copy((char *)(LPCTSTR)cstr_,BewLijn[last_bew0_].GestrMededeling,cstr_.GetLength());

						}
						else{
							cstr_=CString(rec21.mededel,53);cstr_.Trim();
							if(BewLijn[last_bew0_].VrijeMededeling[0]=='\0') copy((char *)(LPCTSTR)cstr_,BewLijn[last_bew0_].VrijeMededeling,cstr_.GetLength());
						}
						cstr1_=CString(BewLijn[last_bew0_].Naam);cstr1_+=" "; cstr1_+=cstr_; len_=cstr1_.GetLength();
						if(len_>sizeof BewLijn[0].Naam) len_=sizeof BewLijn[0].Naam;
						copy((char *)(LPCTSTR)cstr1_,BewLijn[last_bew0_].Naam,len_);
					}
					goto next_rec;
				}
				volgnr_=num_get(rec21.volgnr,4);
				if(BewLijn[BewCount].VolgNr){
					cmed2_.Trim();len_=cmed2_.GetLength();if(len_>sizeof BewLijn[0].VrijeMededeling) len_=sizeof BewLijn[0].VrijeMededeling;
					copy((char *)(LPCTSTR)cmed2_,BewLijn[BewCount].VrijeMededeling,len_);
					cmed3_.Replace("      ","  ");len_=cmed3_.GetLength();if(len_>sizeof BewLijn[0].VrijeMededeling1) len_=sizeof BewLijn[0].VrijeMededeling1;
					copy((char *)(LPCTSTR)cmed3_,BewLijn[BewCount].VrijeMededeling1,len_);	
					if(BewLijn[BewCount].DetailNr==0) last_bew0_=BewCount;
					BewCount++;
					cmed2_="";cmed3_="";
				}
				if(BewCount>=DIM_BEWLIJN) break;
				BewLijn[BewCount].VolgNr=num_get(rec21.volgnr,4);
				copy(rec21.ver_code,BewLijn[BewCount].CodeVerrichting,8);
				if(BewLijn[BewCount].CodeVerrichting[0]=='1') copy("Betaling via bestand",BewLijn[BewCount].Naam,25);
				else if(/* BewLijn[BewCount].CodeVerrichting[0]=='0' && */ BewLijn[BewCount].Naam[0]=='\0'){
					if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"01",2)==0 || cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"02",2)==0) copy0("Overschrijving",BewLijn[BewCount].Naam,25);
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"03",2)==0) copy0("Cheques",BewLijn[BewCount].Naam,25);
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"04",2)==0){
						copy0(&BewLijn[BewCount].CodeVerrichting[3],subgr_,2);subgr_[2]=0;nr_=val(subgr_);
						switch(nr_){
						  case  1  : copy0("Opladen GSM kaart",BewLijn[BewCount].Naam,25); break;
						  case  2  : copy0("Betaling met debetkaart (EU)",BewLijn[BewCount].Naam,40); break;
						  case  3  : copy0("Afrekening kredietkaart",BewLijn[BewCount].Naam,40); break;
						  case  4  : copy0("Geldopneming via automaat",BewLijn[BewCount].Naam,40); break;
						  case  6  : copy0("Betaling met tankkaart",BewLijn[BewCount].Naam,40); break;
							case  7  : copy0("Betaling met GSM",BewLijn[BewCount].Naam,40); break;
							case  8  : copy0("Betaling met debetkaart (buiten EU)",BewLijn[BewCount].Naam,40); break;
							case 37  : copy0("Kosten kaart",BewLijn[BewCount].Naam,40); break;
							case 50  : copy0("Credit van betaling via terminal",BewLijn[BewCount].Naam,40); break;
							case 52  : copy0("Opladen GSM-kaart",BewLijn[BewCount].Naam,40); break;
							case 53  : copy0("Geldstorting aan automaat",BewLijn[BewCount].Naam,40); break;
							case 55  : copy0("Ontvangst betaling met GSM",BewLijn[BewCount].Naam,40); break;
							case 87  : copy0("Terugstorting kosten kaart",BewLijn[BewCount].Naam,40); break;
							default  : copy0("Kaarten",BewLijn[BewCount].Naam,40); break;
						}
					}
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"05",2)==0) copy0("Domiciliering",BewLijn[BewCount].Naam,25);
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"07",2)==0) copy0("Binnenl.handelspapier",BewLijn[BewCount].Naam,25);
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"09",2)==0){
						copy0(&BewLijn[BewCount].CodeVerrichting[3],subgr_,2);subgr_[2]=0;nr_=val(subgr_);
						switch(nr_){
						  case  1  : copy0("Geldopneming loket",BewLijn[BewCount].Naam,25); break;
						  case  5  : copy0("Aankoop deviezen",BewLijn[BewCount].Naam,40); break;
						  case  9  : copy0("Aankoop benzinebons",BewLijn[BewCount].Naam,40); break;
						  case 13  : copy0("Geldopneming door uw bijhuis",BewLijn[BewCount].Naam,40); break;
						  case 17  : copy0("Aankoop fiscale zegels",BewLijn[BewCount].Naam,40); break;
							case 19  : copy0("Verschil in storting loket",BewLijn[BewCount].Naam,40); break;
							case 25  : copy0("Aankoop reischeque",BewLijn[BewCount].Naam,40); break;
							case 37  : copy0("Kosten loket",BewLijn[BewCount].Naam,40); break;
							case 50  : copy0("Storting in contanten aan loket",BewLijn[BewCount].Naam,40); break;
							case 52  : copy0("Storting nachtkluis",BewLijn[BewCount].Naam,40); break;
							case 58  : copy0("Storting door uw bijhuis",BewLijn[BewCount].Naam,40); break;
							case 60  : copy0("Verkoop deviezen",BewLijn[BewCount].Naam,40); break;
							case 68  : copy0("Verschil in storting",BewLijn[BewCount].Naam,40); break;
							case 70  : copy0("Verkoop reischeque",BewLijn[BewCount].Naam,40); break;
							case 87  : copy0("Terugstorting kosten",BewLijn[BewCount].Naam,40); break;
							default  : copy0("Loketverrichting",BewLijn[BewCount].Naam,40); break;
						}
					}
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"11",2)==0) copy0("Effecten",BewLijn[BewCount].Naam,25);
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"13",2)==0) copy0("Kredieten",BewLijn[BewCount].Naam,25);
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"30",2)==0) copy0("Diverse verrichting",BewLijn[BewCount].Naam,25);
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"35",2)==0) copy0("Intresten,kosten...",BewLijn[BewCount].Naam,25);
					else if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"80",2)==0) copy0("Kosten/provisies",BewLijn[BewCount].Naam,25);
				}

				BewLijn[BewCount].DetailNr=num_get(rec21.detailnr,4); if(BewLijn[BewCount].DetailNr>0) BewLijn[last_bew0_].GroepBetaling=1;
				if(BewLijn[BewCount].DetailNr>0){// is detail van globale overschrijving
					BewLijn[BewCount].SubBedrag=get_val(&rec21.teken,rec21.bedrag,12,3);  
					BewLijn[BewCount].BkhOK=YES;
				}
				else  BewLijn[BewCount].Bedrag=get_val(&rec21.teken,rec21.bedrag,12,3);
				BewLijn[BewCount].ValutaDatum=cnv_dat(rec21.val_dat);
				if(rec21.type_med=='1'){
					cstr_=CString(&rec21.mededel[3],20);cstr_.Trim();copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].GestrMededeling,cstr_.GetLength());
					if(cmpstr(&BewLijn[BewCount].CodeVerrichting[1],"0450",4)==0 && CodaSettings.BetaalterminalApart=='J'){
						copy0(&BewLijn[BewCount].GestrMededeling[0],BewLijn[BewCount].RekeningNr,7); // hier wordt de terminalnr in gezet, om zo op aparte GRB te kunnen zetten
					}
				}
				else{
					cstr_=CString(rec21.mededel,53);cstr_.Trim();cmed2_+=cstr_;
				}
			}
			else if(CRecord[1]=='2'){
			  if(BewLijn[BewCount].VolgNr==0) goto next_rec; // er is geen bijhorende betaling , detail betaaldocument
				copy(CRecord,&rec22.rec_type,128);
				cstr_=CString(rec22.mededel,53);cstr_.Trim();cmed2_+=cstr_;
				cstr_=CString(rec22.klt_ref,35);cstr_.Trim();copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].KlantRef,cstr_.GetLength());	
			}
			else if(CRecord[1]=='3'){
			  if(BewLijn[BewCount].VolgNr==0) goto next_rec; // er is geen bijhorende betaling , detail betaaldocument
				copy(CRecord,&rec23.rec_type,128);
				zero(buf_,sizeof buf_); copy(rec23.naam,buf_,35); cstr_=CString(buf_); cstr_.Trim(); // kijken voor lege omschrijving
				if(cstr_.GetLength()) copy(rec23.naam,BewLijn[BewCount].Naam,35);
				cstr_=CString(rec23.rek_tegen,37); cstr_.Trim(); copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].RekeningNr,cstr_.GetLength());	
				cstr_=CString(rec23.mededel,43);cstr_.Trim();cmed2_+=cstr_;
			}
		}
		if(CRecord[0]=='3'){
			if(BewLijn[BewCount].VolgNr==0) goto next_rec; // er is geen bijhorende betaling
			if(CRecord[1]=='1'){
				if(BewCount>=DIM_BEWLIJN) break;
				copy(CRecord,&rec31.rec_type,128);
				if(rec31.type_med=='1'){
					cstr_=CString(&rec31.mededel[3],20);cstr_.Trim();copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].GestrMededeling1,cstr_.GetLength());
				}
				else{
					cstr_=CString(rec31.mededel,73);cstr_.Trim();cmed3_+=cstr_;
				}
			}
			else if(CRecord[1]=='2'){
				copy(CRecord,&rec32.rec_type,128);
				cstr_=CString(rec32.mededel,105);cstr_.Trim();cmed3_+=cstr_;
			}
			else if(CRecord[1]=='3'){
				copy(CRecord,&rec33.rec_type,128);
				cstr_=CString(rec33.mededel,90);cstr_.Trim();cmed3_+=cstr_;
			}
		}
		if(CRecord[0]=='8'){
			copy(CRecord,&rec8.rec_type,128);
			if(BewLijn[BewCount].VolgNr){
				len_=cmed2_.GetLength();if(len_>sizeof BewLijn[0].VrijeMededeling) len_=sizeof BewLijn[0].VrijeMededeling;
				copy((char *)(LPCTSTR)cmed2_,BewLijn[BewCount].VrijeMededeling,len_);
				len_=cmed3_.GetLength();if(len_>sizeof BewLijn[0].VrijeMededeling1) len_=sizeof BewLijn[0].VrijeMededeling1;
				copy((char *)(LPCTSTR)cmed3_,BewLijn[BewCount].VrijeMededeling1,len_);					
				BewCount++;
				cmed2_="";cmed3_="";				
			}
			file_chk_++;
		}
		if(CRecord[0]=='9'){
			if(BewLijn[BewCount].VolgNr){
				len_=cmed2_.GetLength();if(len_>sizeof BewLijn[0].VrijeMededeling) len_=sizeof BewLijn[0].VrijeMededeling;
				copy((char *)(LPCTSTR)cmed2_,BewLijn[BewCount].VrijeMededeling,len_);
				len_=cmed3_.GetLength();if(len_>sizeof BewLijn[0].VrijeMededeling1) len_=sizeof BewLijn[0].VrijeMededeling1;
				copy((char *)(LPCTSTR)cmed3_,BewLijn[BewCount].VrijeMededeling1,len_);					
				BewCount++;
				cmed2_="";cmed3_="";				
			}
			file_chk_++; break;
		}
	}
	cfile_.Close();
	for(k=0;k<BewCount;k++){ // bij kredieten is rekening leeg, daarom medeling inzetten om onderscheid te kunnen maken
		if(BewLijn[k].RekeningNr[0]=='\0') copy(BewLijn[k].VrijeMededeling,BewLijn[k].RekeningNr, sizeof BewLijn[k].RekeningNr);
	}
  return true;
}

static void UpdateParameters(void)
{
  int curs,z,key,j,k;
 
	zeroL((char *)CodaSettings.IBAN, sizeof CodaSettings);
	for(k=0;k<5;k++){
		sysget(19000+k*50,30,(char *)CodaSettings.IBAN[k]);
		sysget(19030+k*50,2,(char *)&CodaSettings.Jnl[k]);
		sysget(19032+k*50,4,(char *)&CodaSettings.RekeningBetLijst[k]);
		sysget(19036+k*50,4,(char *)&CodaSettings.RekeningStorting[k]);
		if(CodaSettings.Jnl[k]){
			for(j=0;j<80;j++) if(CodaSettings.Jnl[k]==j_tab[j].nr) break;
			if(j<80) copy(j_tab[j].nm,CodaSettings.JnlNaam[k],15);
		}
	}
	sysget(19250,50,(char *)CodaSettings.SubDir);
	sysget(19300,10,(char *)CodaSettings.LayoutStructMed); if(CodaSettings.LayoutStructMed[0]=='\0') copy("KKKKKFFFFF",CodaSettings.LayoutStructMed,10);
	sysget(19310,1,(char *)&CodaSettings.SkipGroepsDetail); if(CodaSettings.SkipGroepsDetail!='J') CodaSettings.SkipGroepsDetail='N';
	sysget(19311,4,(char *)&CodaSettings.WachtRekeningBetalingen);
	sysget(19315,1,(char *)&CodaSettings.BetaalterminalApart); if(CodaSettings.BetaalterminalApart!='J') CodaSettings.BetaalterminalApart='N';
	curs=1;
  FOREVER {
		redo:; 
    scrnum=0;scrget(1,267);z=1;

		for(k=0;k<5;k++){
			scrifld(z++,fm_us25U,CodaSettings.IBAN[k]); 
			scrifld(z++,fm_uu2,&CodaSettings.Jnl[k]);
			scrifld(z++,fm_os20,CodaSettings.JnlNaam[k]);
			scrifld(z++,fm_ugrb,&CodaSettings.RekeningBetLijst[k]);
			scrifld(z++,fm_ugrb,&CodaSettings.RekeningStorting[k]);
		}
		scrifld(z++,fm_us50,CodaSettings.SubDir);
		scrifld(z++,fm_us10FK,CodaSettings.LayoutStructMed);
		scrifld(z++,fm_u_JN,&CodaSettings.SkipGroepsDetail);
		scrifld(z++,fm_u_JN,&CodaSettings.BetaalterminalApart);
		scrifld(z++,fm_ugrb,&CodaSettings.WachtRekeningBetalingen);
    key=scrupd(curs,0x2A0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106) goto endsr;
		if(key==110) DisplayDefaultKoppelingen();
		for(k=0;k<5;k++){
			zero(CodaSettings.JnlNaam[k],15);
			if(CodaSettings.IBAN[k][0]){
				if(CodaSettings.Jnl[k]==0){errnum=34; curs=2+k*5; goto redo;}
				for(j=0;j<80;j++) if(j_tab[j].nr==CodaSettings.Jnl[k]) break;
				if(j>=80 || !((j_tab[j].typ>=3 && j_tab[j].typ<=4) || (j_tab[j].typ>=9 && j_tab[j].typ<=10))){ 
					errnum=34; curs=2+k*5; goto redo;
				}
				copy(j_tab[j].nm,CodaSettings.JnlNaam[k],15);
				fasinit(3);*l(3,2)=CodaSettings.RekeningBetLijst[k]; if(faskeyi(3,1,0)){errnum=34; curs=4+k*5; goto redo;}
				fasinit(3);*l(3,2)=CodaSettings.RekeningStorting[k]; if(faskeyi(3,1,0)){errnum=34; curs=5+k*5; goto redo;}
			}
		}
    if(key==108) break;
  }
	for(k=0;k<5;k++){
		sysput(19000+k*50,30,(char *)CodaSettings.IBAN[k]);
		sysput(19030+k*50,2,(char *)&CodaSettings.Jnl[k]);
		sysput(19032+k*50,4,(char *)&CodaSettings.RekeningBetLijst[k]);
		sysput(19036+k*50,4,(char *)&CodaSettings.RekeningStorting[k]);
	}
	sysput(19250,50,(char *)CodaSettings.SubDir);
	sysput(19300,10,(char *)CodaSettings.LayoutStructMed);
	sysput(19310,1,(char *)&CodaSettings.SkipGroepsDetail);
	sysput(19311,4,(char *)&CodaSettings.WachtRekeningBetalingen);
	sysput(19315,1,(char *)&CodaSettings.BetaalterminalApart);
endsr:;
}

static double get_val(char *pteken, char *pget, uint16 digits, uint16 decim)
{
  int16 k;
  double bd_,bd1_;
  char str_[20];
  zero(str_,sizeof str_);
  copy(pget,str_,digits); bd_=val(str_);
  if(decim){
    zero(str_,sizeof str_);
    copy(pget+digits,str_,decim);
    bd1_=val(str_); for(k=0;k<decim;k++) bd1_/=10.;
    bd_+=bd1_;
  }
	if(*pteken=='1') bd_=-bd_;
  bd_=valu_cnv("EUR","EUR",bd_,(double)0.01);/* vieze cijfers na komma wegdoen */
  return (double)bd_;
}

static  uint16 cnv_dat(char *p)
{
  int16 jj,mm,dd;
  dd=num_get(p,2); mm=num_get(p+2,2); jj=num_get(p+4,2);
  return datejd(jj,mm,dd);
}

static long num_get(char *p, int16 count)
{
  char buf[30];
 
  copy(p,buf,count);
  *(buf+count)='\0';
  return val(buf);
}
 
static void initload(void)
{
  int16 j,k;


  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(3);
  fileopen(4);
  sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);
  sysget(1848,2,&sys1848);
  sysget(1918,2,&sear_stt);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;
  for(k=0;k<80;k++){
    sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
    sysget(10240+20+k*80,22,(char *)&j_tab[k].lastnr);
    sysget(10287+k*80,8,&j_tab[k].e_saldo);
  }
	for(k=0;k<80;k++){
		if(DefAkJournaal==0 && j_tab[k].typ==1) DefAkJournaal=j_tab[k].nr;
		if(DefVkJournaal==0 && j_tab[k].typ==2) DefVkJournaal=j_tab[k].nr;
		if(DefAkJournaal && DefVkJournaal) break;
  }
  sysget(2544,14,ogm_file); ogm_file[14]='\0';
  sysget(2558,2,&journl);
  for(k=0;k<15;k++){
    sysget(788+k*4,4,&df_grb[k]);
    df_recnr[k]=getgrb(df_grb[k]);
  }
	sysget( 294,4,def_munt); copy(def_munt,munt,sizeof munt);
	sysget(1727,2,&PandJournaal); if(ovltest(71)==0 || fldlen(4,40)==0 || fldlen(4,41)==0) PandJournaal=0;
  sysget(1818,2,&sys1818);
  sysget(1836,4,&afw_long);
  sysget(1840,2,&sys1840);
  sysget(1850,2,&sys1850);
  sysget(1862,2,&sys1862);
  sysget(1858,2,&last_arc);
  sysget(1866,2,&mnd_strt);
  sysget(1918,2,&sear_stt);
	sysget(2300,2,&MinBkhDatum);if(MinBkhDatum<last_arc) MinBkhDatum=last_arc;
	sysget(4294,40,(char *)&loc_klt[0]);
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;
  rec_type=s(80,1)+4;
  rec_deel=s(80,1)+5;
	analyt=fldlen(4,11);
	
	zero((char *)CodaSettings.IBAN, sizeof CodaSettings);
	for(k=0;k<5;k++){
		sysget(19000+k*50,30,(char *)CodaSettings.IBAN[k]);
		sysget(19030+k*50,2,(char *)&CodaSettings.Jnl[k]);
		sysget(19032+k*50,4,(char *)&CodaSettings.RekeningBetLijst[k]);
		sysget(19036+k*50,4,(char *)&CodaSettings.RekeningStorting[k]);
		if(CodaSettings.Jnl[k]){
			for(j=0;j<80;j++) if(CodaSettings.Jnl[k]==j_tab[j].nr) break;
			if(j<80) copy(j_tab[j].nm,CodaSettings.JnlNaam[k],15);
		}
	}
	sysget(19250,50,(char *)CodaSettings.SubDir);
	sysget(19300,10,(char *)CodaSettings.LayoutStructMed); if(CodaSettings.LayoutStructMed[0]=='\0') copy("KKKKKFFFFF",CodaSettings.LayoutStructMed,10);
	sysget(19310,1,(char *)&CodaSettings.SkipGroepsDetail); if(CodaSettings.SkipGroepsDetail!='J') CodaSettings.SkipGroepsDetail='N';
	sysget(19315,1,(char *)&CodaSettings.BetaalterminalApart); if(CodaSettings.BetaalterminalApart!='J') CodaSettings.BetaalterminalApart='N';
	sysget(19311,4,(char *)&CodaSettings.WachtRekeningBetalingen);
	LoadDefaultKoppelingen();
}

static void anal_det(int16 bew_nr_,int16 nr_)
{
  int16 k,z,key,curs=1;
  uint16 rec_;
	long m_grb_;
  double bd_,afrond_;

  rec_=*u(3,1); m_grb_=*l(3,2);

  zeros((char *)anal_pct,sizeof anal_pct);
  zeros(&anal_onm[0][0],sizeof anal_onm);
  if(fldlen(3,33)){                /* 1-ste keer default percentages zetten */
    for(k=0;k<DIMA;k++){
      if(fldlen(3,33+k*2) && *l(3,33+k*2) && tba[ny+k].a_rec_nr==0){
				anal_pct[k]=*f(3,32+k*2);tba[ny+k].a_grbrek=*l(3,33+k*2);
      }
    }
    for(k=0;k<DIMA;k++){
      if(tba[ny+k].a_grbrek && tba[ny+k].a_rec_nr==0){
				fasinit(3);*l(3,2)=tba[ny+k].a_grbrek;
				if(faskeyi(3,1,0)==0) tba[ny+k].a_rec_nr=*u(3,1)+60000;
				else tba[ny+k].a_grbrek=0;
      }
    }
  }
									
  for(k=0;k<DIMA;k++){
    if(tba[ny+k].a_rec_nr){
      fasinit(3);*u(3,1)=tba[ny+k].a_rec_nr-60000;fasgeti(3);
			tba[ny+k].a_grbrek=*l(3,2);
      makename(anal_nm[k]);
    }
    else zeros(anal_nm[k],sizeof anal_nm[0]);
		copy(anal_nm[k],anal_onm[k],sizeof anal_nm[0]);
  }
  FOREVER{
    redo:
    scrget(1,44);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_ou2,&journl);
    scrifld(z++,fm_ou5,&volgnr);
    scrifld(z++,fm_odat,&bkh_dt);
    scrifld(z++,fm_os38,lkgnaam);
    scrifld(z++,fm_od9_2,&bd_inp);
    for(k=0;k<DIMA;k++){
      scrifld(z++,fm_ud7_2,&tba[ny+k].a_bedrag);
      scrifld(z++,fm_uf3_2,&anal_pct[k]);
      scrifld(z++,fm_us30,anal_nm[k]);
    }
    key=scrupd(curs,0x4C1);curs=1;
    if(key==111) ovlexit(-1);
/* bedragen */
    bd_=0; afrond_=0.01; 
    for(k=0;k<DIMA;k++){
      if(tba[ny+k].a_bedrag==0) tba[ny+k].a_bedrag=bd_inp*anal_pct[k]/100.;
      tba[ny+k].a_bedrag=valu_cnv(munt,munt,tba[ny+k].a_bedrag,afrond_);
      bd_+=tba[ny+k].a_bedrag;
    }
    if((bd_-bd_inp)>=-5 && (bd_-bd_inp)<=5){
      for(k=0;k<DIMA;k++) if(tba[ny+k].a_bedrag) break;
      if(k!=DIMA) tba[ny+k].a_bedrag-=bd_-bd_inp;
    }
    else{
      if(absdoubl(bd_)>absdoubl(bd_inp)){errnum=67;goto redo;}
      if(sys1850){
	if(absdoubl(bd_)<absdoubl(bd_inp)){errnum=70;goto redo;}
      }
    }
/* controle grb rekeningnamen */
    for(k=0;k<DIMA;k++){
      if(tba[ny+k].a_bedrag && anal_nm[k][0]=='\0'){
				errnum=38;curs=9+k*3;goto redo;
      }
      if(cmpstr(anal_onm[k],anal_nm[k],sizeof anal_nm[0])){
				if(anal_nm[k][0]){
					copy(anal_nm[k],s(3,3),fldlen(3,3));
					if(Search(3,0) && errnum==0)errnum=39;
					if(errnum){curs=9+k*3;goto redo;}
					makename(anal_nm[k]);
					if(g_anal_tst()==NO) {errnum=68;curs=9+k*3;goto redo;}
					tba[ny+k].a_grbrek=*l(3,2);
					tba[ny+k].a_rec_nr=*u(3,1)+60000;
				}
				copy(anal_nm[k],anal_onm[k],sizeof anal_nm[0]);
      }
			tba[ny+k].mast_grbrek=m_grb_;
			tba[ny+k].a_elem=bew_nr_*MAX_BDETAIL+nr_*DIMA;
    }
    if(key==101 || key==108) break;
  }
	for(k=0;k<DIMA;k++) if(tba[ny+k].a_bedrag) break;
	if(k<DIMA) anal_ask='X'; else anal_ask='\0';
  *u(3,1)=rec_;fasgeti(3);
}

static int g_anal_tst(void)
{
  if(!analyt || ((*s(3,2) &0xF0)>>4)!=9) return NO;
  return YES;
}

static void makename(char *pd)
{
  int16 g,h;
  char *ps;
  g=fldlen(3,3);if(g>MAXLEN-1)g=MAXLEN-1;
  h=MAXLEN-1;
  ps=s(3,3);
  while(g--){
    if(*ps==0)break;
    *pd++=*ps++;
    h--;
  }
  while(h--){
    *pd++=' ';
  }
  *pd='\0';
  pd=pd-8;
  grb_deco(pd,l(3,2));
}

static double absdoubl(double bd_)
{
  if(bd_>=0) return bd_;
  else return -bd_;
}

static uint16 getgrb(long lgrb)
{
  uint16 retcd=0;

  if(*(char *)&lgrb!=0xFF && *(char *)&lgrb!=0x00 && scrcount<23){
    *l(3,2)=lgrb;
    *u(3,1)=0;
    Search(3,2);
    if(errnum) tb_grbnotfound[notfound++]=lgrb;
    else{
      retcd=*u(3,1)+60000;
    }
  }
  return retcd;
}


static int copy0(char *ps,char *pd,int max)
{
  int16 k;
  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
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

static void nextline(void)
{
  LinFree=prtline();
}

static int is_nul(double bd_)
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static int scr_ok(char *ptxt)
{
  int16 key;
  scrget(1,169);
  scrifld(12,fm_os79,ptxt);
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