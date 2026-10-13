/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* BKH0073GetD() {return &zzvw;}
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" int16 Search(int stu_,int mod_);

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
static int16 ovlcall();
extern "C" char BKH0073dat[] = "bkh0073  00:03 05/08/10 (c) Jamadata";
/* CODA GESTR.MED verwerking versie 2.1.C Maart 2007 */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MINFREE         100
#define flag            uint16
 
extern char *s();
extern int16 *i();
extern uint16 *u(),dateadd(),datejd();
static uint16 cnv_dat();
extern long *l(),val();
static long num_get();
extern float *f();
extern double *d(),valu_cnv();
static double get_val();
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
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x70,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x70,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_od92_[] = {6,0x95,9,2,0x60,0};
static char fm_od9_2[] = {6,0x95,9,2,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};
static char fm_of8_0[] = {6,0x94,8,0,0x70,0};
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
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
  
static struct {
  uint16 nr;
  uint16 typ;
  char nm[16];
  uint16 lastnr;
  long fingrb;
  long saldo;
  double saldo_vm;
  char munt[4];
  uint16 blz_o;
  uint16 blz_n;
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

static struct {
	int16 VolgNr;
	double Bedrag;
  uint16 ValutaDatum;
	char VrijeMededeling[3][55];
	char GestrMededeling[20];
	char RekeningNr[40];
	char Naam[40];
  char KlantCode[10];
  char FactuurNr[10];
  uint16 KlantRec;
  int16  RefJaar;
  int16  RefJournaal;
  int16  RefVolgNr;
} BewLijn[500],PrintBewLijn;



static struct{
	char IBAN[5][30];
	int16 Jnl[5];
	long WachtRekening[5];
	char JnlNaam[5][25];
	char SubDir[50];
} CodaSettings;

static struct{
	char   IBAN[40];
	uint16 BkhJournaal;
	uint16 Datum;
	uint16 VolgNr;
	uint16 AantalBew;
	double VorigSaldo;
	double NieuwSaldo;
	char   FileNaam[100];
} TbCodaFiles[50];

static int16 form_dat[8],pr_mode,prtnr,LinFree;
static uint16 recnr_ogm,recnr_disk,rec_nr;
static uint16 journl,lastnr,last_adr=0,volgnr_ogm,recs_tot,recs_ok,recs_nok;
static long levcent,kltcent;
static char begunst[30],banknr[20],btwnr[20];
static char klt_nr[10],ogm_file[20],*i_80,pauze='J',filnam[100];
static uint16 dat_ogm,dat_bedrag,rec_cnt,sys1848;
static flag klcd,lvcd,geboekt,debit_allow,credt_allow;
static flag sear_stt,chk_btoeg;
static flag sys3876;
static char lkgkod[9],lkgnaam[51],lkg,opmerk[30];
static int16 q_uittrek,q_bew,q_error,q_done,stutyp,CntCodaFiles;
static char *p_data,*rec_type,*rec_deel;
static double bd_bkh,bd_bkh_t=0;
static double tot_deb,tot_cre,tot_bew,o_sal,n_sal,bd_ok,bd_nok;
static long fpos,*pl_80_1;

/* --------------------------- Declaratie functies ---------------------- */
static void boek_div(void);
static void boek_end(void);
static void boek_ogm(void);
static int chk_file(void);
static int cmp_str(char *p1, char *p2, int16 len);
static  uint16 cnv_dat(char *p);
static int copy0(char *ps,char *pd,int max);
static void corr_y2000(uint16 bstu_, uint16 searcnr_);
static void fileopen(int16 nr_);
static double get_val(char *pteken, char *pget, uint16 digits, uint16 decim);
static void initload(void);
static void insert(char *p, int16 pos, char byte);
static int is_nul(double bd_);
static int LoadCodaFiles(void);
static int next_bew(void);
static void nextline(void);
static long num_get(char *p, int16 count);
static void ovl_exit(int16 nr);
static void process(void);
static int read_rec(int16 mode_);
static int scr_ok(char *ptxt);
static int str_len(char *p, int16 len);
static void UpdateGrbTabel(void);
static void UpdateParameters(void);
/* ---------------------------------------------------------------------- */


extern "C" void BKH0073cod(void)
{
  int16 k,key,z,start_;

	initload();
	LoadCodaFiles();
	start_=0;
  FOREVER{
		redo:;
		scrget(1,266);z=1;scraddpicto(1,0,76,22,4,2,59,0,4,"Parameters");
		for(k=0;k<start_+15;k++){
			if(k>=CntCodaFiles) break;
			scrifld(z++,fm_os20,TbCodaFiles[start_+k].IBAN);
			scrifld(z++,fm_ou2,&TbCodaFiles[start_+k].BkhJournaal);
			scrifld(z++,fm_odat,&TbCodaFiles[start_+k].Datum);
			scrifld(z++,fm_ou5,&TbCodaFiles[start_+k].VolgNr);
			scrifld(z++,fm_od6_2,&TbCodaFiles[start_+k].VorigSaldo);
			scrifld(z++,fm_od6_2,&TbCodaFiles[start_+k].NieuwSaldo);
			scrifld(z++,fm_ou5,&TbCodaFiles[start_+k].AantalBew);
		}
		key=scrupd(-1,0x047);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){ UpdateParameters();goto redo;}
		if(key==101) break;
		if(key==107){LoadCodaFiles();start_=0;goto redo;}
		if(key==102) start_-=15;
		if(key==103) {start_+=15; if(start_>=CntCodaFiles) start_-=15;}
		if(start_<0) start_=0;
	}

    //redo:
    //scrget(1,92);z=1;
    //scrfld(z++,25,1);
    //scrifld(z++,fm_us14,ogm_file);
    //scrifld(z++,fm_uu2,&journl);
    //scrifld(z++,fm_u_JN,&pauze);
    //key=scrupd(curs,0x0481);
    //if(key==101) goto endsr;
    //if(key==111) ovl_exit(-1);
  //  for(k=0;k<80;k++) if(j_tab[k].nr==journl) break;
  //  if(k==80) {errnum=7;curs=3;goto redo;}
  //  last_adr=10260+k*80;
  //  sysget(last_adr,2,&lastnr); volgnr_ogm=lastnr+1;
  //  if(volgnr_ogm>65000) volgnr_ogm=1;
  //  sysget(10262+k*80,4,&grb_);
  //  fasinit(3);*l(3,2)=grb_;
  //  if(faskeyi(3,1,0)) {errnum=28;goto redo;}
  //  recnr_ogm=*u(3,1)+60000;
  //  fasclos(-2);
		//zero(filnam,sizeof filnam);k=copy0("..\\CODA_IN\\",filnam,15);copy(ogm_file,&filnam[k],sizeof ogm_file);
  //  if(fasopen(filnam,1)){errnum=1;goto redo;}
  //  fasinit(80);
  //  if(chk_file()==NO) goto redo;
  //  if(key==108) break;
  //}
  //fasclos(-2);
  //errnum=fasopen(filnam,1); fasinit(80);
  //geboekt=NO;
  //process();
  //if(!errnum){
  //  if(geboekt) boek_end();
  //  sysput(last_adr,2,&volgnr_ogm);
  //  sysflush();
  //  goto endsr;
  //}
  //if(errnum=9999) errnum=0;
  endsr:;
  ovlexit(-1);
}
//
//void PrintCodaFile(int16 ptb_)
//{
//	getsysprNew(3,form_dat,&pr_mode,&prtnr); PrintPaperNr=0;
//  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
//
//	prtfld(25,1,25); 
//	prttext("  Rekening ");prtifld(fm_os20,&TbCodaFiles[ptb_].IBAN,-1); 
//	prttext(", afschrift ");prtifld(fm_ou5,&TbCodaFiles[ptb_].VolgNr,-1); 
//	prttext(" van ");prtifld(fm_odat,&TbCodaFiles[ptb_].Datum,-1);p
//  prttext("<t120>Blz.<ppp>.");
//  prtbuf(1);
//  //prttext("Begunstigde : ");prtifld(fm_os26,begunst,-1);
//  //prttext("  Rekeningnr.: ");prtifld(fm_os20,banknr,-1);
//  //prttext("  Ond.nummer. : ");prtifld(fm_os14,btwnr,-1);
//  //prtbuf(2);z=1;
//	z=1;
//  prtitab(z,fm_ou4,&st.volgnr,1,-1); prttitle(z++,"Nr.",0x13);
//  prtitab(z,fm_odat,&st.val_dat,1,-1); prttitle(z++,"Val.dat",0x13);
//  prtitab(z,fm_od6_2,&st.bedrag,1,-1); prttitle(z++,"Bedrag",0x13);
//  prtitab(z,fm_os26,rec23.naam,1,-1); prttitle(z++,"Opdrachtgever",3);
//  prtitab(z,fm_os14,st.g_med,1,-1); prttitle(z++,"Gestr.med.",3);
//  prtitab(z,fm_os5,st.fact_nr,3,-1); prttitle(z++,"Ft.nr.",0x13);
//  prtitab(z,fm_uLKG,&lkg,3,-1); prttitle(z++,"LKG",3);
//  prtitab(z,fm_us30,lkgnaam,1,-1); prttitle(z++,"Rekening",3);
//  prtitab(z,fm_us20,opmerk,1,-1); prttitle(z++,"Opmerking",3);
//  prtitab(z,fm_ou3,&st.rf_yy,1,-1); prttitle(z++,"",0x13);
//  prtitab(z,fm_ou2,&st.rf_jr,1,-1); prttitle(z++,"",0x13);
//  prtitab(z,fm_ou5,&st.rf_vl,1,-1); prttitle(z++,"",0x13);
//  prtbuf(4);
//	p_pdfname("Detail afschrift",TbCodaFiles[ptb_].Datum,0);
//
//}
//
//

static int LoadCodaFiles(void)
{
  int16 k,key,z,file_chk_,q_bew_;
	char CRecord[150];
	CFileFind finder;
	CFile cfile_;
	BOOL bWorking;
  CString filename_;
	long fpos_;

	zero(TbCodaFiles[0].IBAN,sizeof TbCodaFiles);
	bWorking = finder.FindFile(CString(CodaSettings.SubDir)+CString("*.*")); CntCodaFiles=0;
	while (bWorking) {
		bWorking = finder.FindNextFile();
	  if (finder.IsDirectory()) continue;
		if(finder.GetLength()<650 || (finder.GetLength()%130)) continue; // minstens 5 records en moet een veelvoud van 128+2 zijn 
		filename_=CString(CodaSettings.SubDir)+finder.GetFileName();
		if(cfile_.Open(filename_,CFile::modeRead,0)==false) continue;
		fpos_=0;file_chk_=0; q_bew_=0;
		copy0((char *)(LPCTSTR)filename_,TbCodaFiles[CntCodaFiles].FileNaam,100);
		FOREVER{
			cfile_.Seek(fpos_,CFile::begin); fpos_+=130;
	    if(cfile_.Read(CRecord,130)<128) break;
		  if(CRecord[0]=='0'){
				if(CRecord[126]=='X') break; // is al afgeboekt
				copy(CRecord,&rec0.rec_type,128);
				TbCodaFiles[CntCodaFiles].Datum=cnv_dat(rec0.datum);
				file_chk_++;
			}
			if(CRecord[0]=='1'){
				copy(CRecord,&rec1.rec_type,128);
				copy(rec1.reknr,TbCodaFiles[CntCodaFiles].IBAN,30);
				TbCodaFiles[CntCodaFiles].VolgNr=num_get(rec1.volgnr,3);
				TbCodaFiles[CntCodaFiles].VorigSaldo=get_val(&rec1.teken,rec1.o_saldo,12,3);
				file_chk_++;
			}
			if(CRecord[0]=='2'){
				if(CRecord[1]=='1') TbCodaFiles[CntCodaFiles].AantalBew++;
			}
			if(CRecord[0]=='8'){
				copy(CRecord,&rec8.rec_type,128);
				TbCodaFiles[CntCodaFiles].NieuwSaldo=get_val(&rec8.teken,rec8.n_saldo,12,3);
				file_chk_++;
			}
			if(CRecord[0]=='9'){
				file_chk_++;
			}
		}
		cfile_.Close();
		if(file_chk_!=4 || TbCodaFiles[CntCodaFiles].AantalBew==0){
			zero(TbCodaFiles[CntCodaFiles].IBAN,sizeof TbCodaFiles[0]);
		}
		else CntCodaFiles++;
	}
	finder.Close();
	return CntCodaFiles;
}

static int PdfCodaFile(char *NmCodaFile)
{
  int16 k,key,z,file_chk_,q_bew_,pbew_;
	char CRecord[150];
	CFileFind finder;
	CFile cfile_;
	BOOL bWorking;
  CString filename_;
	long fpos_;

	if(cfile_.Open(NmCodaFile,CFile::modeRead,0)==false) {errnum=1; return false;}
	fpos_=0;file_chk_=0; q_bew_=0;
  getsysprNew(3,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) ovlexit(-1);
	LinFree=999;
  prtnew();
  prtfld(25,1,25); prttext("     Boekdatum : ");prtifld(fm_odat,&dat_ogm,-1);
  prttext("     journaal : ");prtifld(fm_ou2,&journl,-1);prttext("/");prtifld(fm_ou5,&volgnr_ogm,-1);
  prttext("<t92>");prtfld(25,2,-1);prttext("<t120>Blz.<ppp>.");
  prtbuf(1);
  prttext("Begunstigde : ");prtifld(fm_os26,begunst,-1);
  prttext("  Rekeningnr.: ");prtifld(fm_os20,banknr,-1);
  prttext("  Ond.nummer. : ");prtifld(fm_os14,btwnr,-1);
  prtbuf(2);z=1;
	prtitab(z,fm_ou4,&PrintBewLijn.VolgNr,1,-1); prttitle(z++,"Nr.",0x13);
	prtitab(z,fm_odat,&PrintBewLijn.ValutaDatum,1,-1); prttitle(z++,"Val.dat",0x13);
	prtitab(z,fm_od6_2,&PrintBewLijn.Bedrag,1,-1); prttitle(z++,"Bedrag",0x13);
	prtitab(z,fm_os26,PrintBewLijn.Naam,1,-1); prttitle(z++,"Opdrachtgever",3);
	prtitab(z,fm_os26,PrintBewLijn.RekeningNr,1,-1); prttitle(z++,"RekeningNr",3);
	prtitab(z,VarTextFmt(45,0),mededeling_,1,-1); prttitle(z++,"Mededeling",3);
  prtitab(z,fm_os5,st.fact_nr,3,-1); prttitle(z++,"Ft.nr.",0x13);
  prtitab(z,fm_uLKG,&lkg,3,-1); prttitle(z++,"LKG",3);
  prtitab(z,fm_us30,lkgnaam,1,-1); prttitle(z++,"Rekening",3);
  prtitab(z,fm_us20,opmerk,1,-1); prttitle(z++,"Opmerking",3);
  prtitab(z,fm_ou3,&st.rf_yy,1,-1); prttitle(z++,"",0x13);
  prtitab(z,fm_ou2,&st.rf_jr,1,-1); prttitle(z++,"",0x13);
  prtitab(z,fm_ou5,&st.rf_vl,1,-1); prttitle(z++,"",0x13);
  prtbuf(4);
	zero(BewLijn,sizeof BewLijn);pbew_=0;
	FOREVER{
		cfile_.Seek(fpos_,CFile::begin); fpos_+=130;
	  if(cfile_.Read(CRecord,130)<128) break;
		if(CRecord[0]=='0'){
//			if(CRecord[126]=='X') break; // is al afgeboekt
			copy(CRecord,&rec0.rec_type,128);
			TbCodaFiles[CntCodaFiles].Datum=cnv_dat(rec0.datum);
			file_chk_++;
		}
		if(CRecord[0]=='1'){
			copy(CRecord,&rec1.rec_type,128);
			copy(rec1.reknr,TbCodaFiles[CntCodaFiles].IBAN,30);
			TbCodaFiles[CntCodaFiles].VolgNr=num_get(rec1.volgnr,3);
			TbCodaFiles[CntCodaFiles].VorigSaldo=get_val(&rec1.teken,rec1.o_saldo,12,3);
			file_chk_++;
		}
		if(CRecord[0]=='2'){
			if(CRecord[1]=='1'){
				if(BewLijn[pbew_].VolgNr) pbew_++;
				copy(CRecord,&rec21.rec_type,128);
				BewLijn[pbew_].VolgNr=num_get(rec21.volgnr,4);
				BewLijn[pbew_].Bedrag=get_val((&rec21.teken,rec21.bedrag,12,3);
				BewLijn[pbew_].ValutaDatum=cnv_dat(rec21.val_dat);
				if(rec21.type_med=='1') copy(&rec21.mededel[3],BewLijn[pbew_].GestrMededeling,20);
				else copy(rec21.mededel,BewLijn[pbew_].VrijeMededeling[0],53);
				TbCodaFiles[CntCodaFiles].AantalBew++;
			}
			else if(CRecord[1]=='2'){
				copy(CRecord,&rec22.rec_type,128);
				copy(rec22.mededel,BewLijn[pbew_].VrijeMededeling[1],53);
			}
			else if(CRecord[1]=='3'){
				copy(CRecord,&rec23.rec_type,128);
				copy(rec23.naam,BewLijn[pbew_].Naam,35);
				copy(rec23.rek_tegen,BewLijn[pbew_].RekeningNr,37);
				copy(rec23.mededel,BewLijn[pbew_].VrijeMededeling[2],43);
			}
		}
		if(CRecord[0]=='8'){
			copy(CRecord,&rec8.rec_type,128);
			TbCodaFiles[CntCodaFiles].NieuwSaldo=get_val(&rec8.teken,rec8.n_saldo,12,3);
			file_chk_++;
		}
		if(CRecord[0]=='9'){
			file_chk_++;
		}
	}
	cfile_.Close();
	if(file_chk_!=4 || TbCodaFiles[CntCodaFiles].AantalBew==0){
		zero(TbCodaFiles[CntCodaFiles].IBAN,sizeof TbCodaFiles[0]);
	}
	else CntCodaFiles++;
	}
	finder.Close();
	return CntCodaFiles;
}



static void UpdateParameters(void)
{
  int curs,z,key,j,k;
 
	zero((char *)CodaSettings.IBAN, sizeof CodaSettings);
	for(k=0;k<5;k++){
		sysget(19000+k*50,30,(char *)CodaSettings.IBAN[k]);
		sysget(19030+k*50,2,(char *)&CodaSettings.Jnl[k]);
		sysget(19032+k*50,4,(char *)&CodaSettings.WachtRekening[k]);
		if(CodaSettings.Jnl[k]){
			for(j=0;j<80;j++) if(CodaSettings.Jnl[k]==j_tab[j].nr) break;
			if(j<80) copy(j_tab[j].nm,CodaSettings.JnlNaam[k],15);
		}
	}
	sysget(19250,50,(char *)CodaSettings.SubDir);

	curs=1;
  FOREVER {
		redo:; 
    scrnum=0;scrget(1,267);z=1;
		for(k=0;k<5;k++){
			scrifld(z++,fm_us25U,CodaSettings.IBAN[k]); 
			scrifld(z++,fm_uu2,&CodaSettings.Jnl[k]);
			scrifld(z++,fm_os20,CodaSettings.JnlNaam[k]);
			scrifld(z++,fm_ugrb,&CodaSettings.WachtRekening[k]);
		}
		scrifld(z++,fm_us50,CodaSettings.SubDir);
    key=scrupd(curs,0x2A0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106) goto endsr;
		if(key==110) UpdateGrbTabel();
		for(k=0;k<5;k++){
			zero(CodaSettings.JnlNaam[k],15);
			if(CodaSettings.IBAN[k][0]){
				if(CodaSettings.Jnl[k]==0){errnum=34; curs=2+k*4; goto redo;}
				for(j=0;j<80;j++) if(j_tab[j].nr==CodaSettings.Jnl[k]) break;
				if(j>=80 || !((j_tab[j].typ>=3 && j_tab[j].typ<=4) || (j_tab[j].typ>=9 && j_tab[j].typ<=10))){ 
					errnum=34; curs=2+k*4; goto redo;
				}
				copy(j_tab[j].nm,CodaSettings.JnlNaam[k],15);
				fasinit(3);*l(3,2)=CodaSettings.WachtRekening[k]; if(faskeyi(3,1,0)){errnum=34; curs=4+k*4; goto redo;}
			}
		}
    if(key==108) break;
  }
	for(k=0;k<5;k++){
		sysput(19000+k*50,30,(char *)CodaSettings.IBAN[k]);
		sysput(19030+k*50,2,(char *)&CodaSettings.Jnl[k]);
		sysput(19032+k*50,4,(char *)&CodaSettings.WachtRekening[k]);
	}
	sysput(19250,50,(char *)CodaSettings.SubDir);
endsr:;
}

static void UpdateGrbTabel(void)
{

}


static int chk_file(void)
{
  int16 key,detnr_,z,mode_;
  double bd_;
  bd_ok=0; bd_nok=0;recs_ok=0;recs_nok=0;
  tot_bew=0;tot_cre=0;tot_deb=0; q_uittrek=0; o_sal=0;n_sal=0;
  q_error=0; q_bew=0; fasinit(80); mode_=0;
  FOREVER{
    if(read_rec(mode_)) break; mode_=1;
    if(cmp_str(p_data+1,"OK",2)==0){
      if(scr_ok("Dit bestand is reeds ingeboekt !!! Toch verdergaan ?")==NO) return NO;
    }
    switch(*p_data){
      case '0' : break;
      case '1' : q_uittrek++; o_sal=get_val(p_data+42,p_data+43,12,3); break;
      case '2' : detnr_=num_get(p_data+6,4);
								 if(detnr_!=0) break;/* is detail van betaling */
								 if(*(p_data+1)=='1'){/* echte beweging */
									 q_bew++; bd_=get_val(p_data+31,p_data+32,12,3);
									 detnr_=num_get(p_data+62,3);
									 if(*(p_data+61)=='1' && (detnr_>=101 && detnr_<=102)){
										 bd_ok+=bd_;recs_ok++;
									 }
									 else{bd_nok+=bd_;recs_nok++;}
									 tot_bew+=bd_;
								 }
								 break;
      case '3' : break;
      case '4' : break;
      case '8' : n_sal=get_val(p_data+41,p_data+42,12,3); break;
      case '9' : tot_deb=get_val("1",p_data+22,12,3);
		 tot_cre=get_val("0",p_data+37,12,3);
		 break;
      default  : q_error++; break;
    }
  }
  scrget(1,93); z=1;
  scrifld(z++,fm_ou5,&recs_ok);scrifld(z++,fm_od6_2,&bd_ok);
  scrifld(z++,fm_ou5,&recs_nok);scrifld(z++,fm_od6_2,&bd_nok);
  scrifld(z++,fm_ou5,&q_bew);scrifld(z++,fm_od6_2,&tot_bew);
  scrifld(z++,fm_ou5,&q_error);
  scrifld(z++,fm_ou5,&q_uittrek);
  scrifld(z++,fm_od6_2,&tot_cre);
  scrifld(z++,fm_od6_2,&tot_deb);
  bd_=tot_bew-tot_cre+tot_deb;
  if(!is_nul(bd_)/*tot_bew != (tot_cre-tot_deb)*/) errnum=73;
  key=scrupd(-1,0x81);
  if(key==108 && q_bew) return YES; else return NO;
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
  bd_=valu_cnv("EUR","EUR",bd_,(double)0.01);/* vieze cijfers na komma wegdoen */
  return (double)bd_;
}

static void process(void)
{
  char *p;
  int16 key,curs=1;
  uint16 z,z_base,err_code,err_;
 
  recs_tot=0; err_code=0;  bd_bkh_t=0;q_done=0;
  fasinit(80);
 
  if(read_rec(NO)) goto close;
  if(*rec_type!='0'){errnum=63;goto close;}
  copy(p_data,(char *)&rec0.rec_type,128);
  if(read_rec(YES)) goto close;
  if(*rec_type!='1'){errnum=63;goto close;}
  copy(p_data,(char *)&rec1.rec_type,128);
  dat_ogm=cnv_dat(rec0.datum);
  copy(rec1.naam,begunst,26);
  copy(rec0.btwnr,btwnr,11);
  copy(rec1.reknr,banknr,20);
/*  insert(banknr,10,'-'); insert(banknr,3,'-'); */
/*  if(rec0.vers>'1') {errnum=44; goto close;} */
	
  
	getsysprNew(3,form_dat,&pr_mode,&prtnr);
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) ovlexit(-1);
	LinFree=999;
  prtnew();
  prtfld(25,1,25); prttext("     Boekdatum : ");prtifld(fm_odat,&dat_ogm,-1);
  prttext("     journaal : ");prtifld(fm_ou2,&journl,-1);prttext("/");prtifld(fm_ou5,&volgnr_ogm,-1);
  prttext("<t92>");prtfld(25,2,-1);prttext("<t120>Blz.<ppp>.");
  prtbuf(1);
  prttext("Begunstigde : ");prtifld(fm_os26,begunst,-1);
  prttext("  Rekeningnr.: ");prtifld(fm_os20,banknr,-1);
  prttext("  Ond.nummer. : ");prtifld(fm_os14,btwnr,-1);
  prtbuf(2);z=1;
  prtitab(z,fm_ou4,&st.volgnr,1,-1); prttitle(z++,"Nr.",0x13);
  prtitab(z,fm_odat,&st.val_dat,1,-1); prttitle(z++,"Val.dat",0x13);
  prtitab(z,fm_od6_2,&st.bedrag,1,-1); prttitle(z++,"Bedrag",0x13);
  prtitab(z,fm_os26,rec23.naam,1,-1); prttitle(z++,"Opdrachtgever",3);
  prtitab(z,fm_os14,st.g_med,1,-1); prttitle(z++,"Gestr.med.",3);
  prtitab(z,fm_os5,st.fact_nr,3,-1); prttitle(z++,"Ft.nr.",0x13);
  prtitab(z,fm_uLKG,&lkg,3,-1); prttitle(z++,"LKG",3);
  prtitab(z,fm_us30,lkgnaam,1,-1); prttitle(z++,"Rekening",3);
  prtitab(z,fm_us20,opmerk,1,-1); prttitle(z++,"Opmerking",3);
  prtitab(z,fm_ou3,&st.rf_yy,1,-1); prttitle(z++,"",0x13);
  prtitab(z,fm_ou2,&st.rf_jr,1,-1); prttitle(z++,"",0x13);
  prtitab(z,fm_ou5,&st.rf_vl,1,-1); prttitle(z++,"",0x13);
  prtbuf(4);
	
  FOREVER{
    zero((char *)st.klt_nr,sizeof st); fasinit(2);
    lkg='K';zero(lkgkod,sizeof lkgkod);zero(lkgnaam,sizeof lkgnaam);
    zero(opmerk,sizeof opmerk);
    zero((char *)&rec21.rec_type,sizeof rec21);
    zero((char *)&rec22.rec_type,sizeof rec22);
    zero((char *)&rec23.rec_type,sizeof rec23);
    err_=next_bew(); if(err_==99) break;
    redo:;
    scrget(1,94); z=1;
    scrifld(z++,fm_odat,&dat_ogm);
    scrifld(z++,fm_ou2,&journl); scrifld(z++,fm_ou5,&volgnr_ogm);
    scrifld(z++,fm_ou5,&q_bew);
    scrifld(z++,fm_od6_2,&tot_bew);
    scrifld(z++,fm_os26,begunst);
    scrifld(z++,fm_os20,banknr);  scrifld(z++,fm_ou5,&q_done);
    scrifld(z++,fm_os14,btwnr); scrifld(z++,fm_od6_2,&bd_bkh_t);
    scrifld(z++,fm_os26,rec23.naam);
    scrifld(z++,fm_os26,rec23.rek_tegen);
    scrifld(z++,fm_os26,rec22.bic_tegen);
    scrifld(z++,fm_ou4,&st.volgnr);
    scrifld(z++,fm_odat,&st.val_dat);
    scrifld(z++,fm_os14,st.g_med);
    scrifld(z++,fm_os5,st.fact_nr);
    scrifld(z++,fm_od6_2,&st.bedrag);
    z_base=z;
    scrifld(z++,fm_uLKG,&lkg);
    scrifld(z++,fm_os8,lkgkod);
    scrifld(z++,fm_us30,lkgnaam);
    scrifld(z++,fm_us20,opmerk);
    scrifld(z++,fm_uu5,&st.rf_vl);scrifld(z++,fm_uu2,&st.rf_jr);
    st.rf_yy=st.rf_yy%100;scrifld(z++,fm_uu2_,&st.rf_yy);
    if(err_==0 && pauze=='N') {key=108; goto no_stop; }
    key=scrupd(curs,0xE0); curs=z_base;
    no_stop:;
    if(key==106){/* bedrag tegenboeken op OGM-rekening */
      lkg='G'; *u(3,1)=recnr_ogm-60000;  errnum=fasgeti(3);
      copy(s(3,3),lkgnaam,fldlen(3,3)); lkgnaam[fldlen(3,3)]='\0';
      if(st.g_med[0]) copy(st.g_med,opmerk,20);
      else copy(rec23.naam,opmerk,20);
      key=108;
    }
    if(lkg=='L'){
      if(credt_allow) stutyp=1;
      else {err_=1;errnum=34;curs=z_base; goto redo;}
    }
    else if(lkg=='K'){
      if(debit_allow) stutyp=2;
      else {err_=1;errnum=34;curs=z_base; goto redo;}
    }
    else stutyp=3;
    copy(lkgnaam,s(stutyp,3),fldlen(stutyp,3));
    if(Search(stutyp,0)) {err_=1;curs=z_base+1;goto redo;}
    copy(s(stutyp,3),lkgnaam,fldlen(stutyp,3));lkgnaam[fldlen(stutyp,3)]='\0';
    rec_nr=*u(stutyp,1)+30000*(stutyp-1);
    if(stutyp==3) grb_deco(lkgkod,l(3,2));
    if(key==108){
      boek_ogm(); q_done=st.volgnr;
    } else {err_=1;goto redo;}
  }
  fasclos(-2);
  errnum=fasopen(filnam,3); fasinit(80);
  *pl_80_1=0; fasseqi(80,3,9);
  p=s(80,1)+5;
  *p++='O'; *p++='K'; *(uint16 *)p=*u(25,2);
  *pl_80_1=0; fasseqo(80,3,9);
  close:
  fasclos(-2);
  endsr:;
}

static int next_bew(void)
{
  int16 j,k,len_,yy_,dum1,dum2,detnr_;
  flag found;
  FOREVER{
    next:;
    if(read_rec(YES)) return 99;
    switch(*rec_type){
      case '0' : break;
      case '1' : break;
      case '2' : detnr_=num_get(p_data+6,4);
		 if(*rec_deel=='1'){
		   if(detnr_!=0) goto next;/* is detail van betaling */
		   copy(p_data,(char *)&rec21.rec_type,128);
		   if(rec21.code_verv=='0') goto bew_found;
		 }
		 else if(*rec_deel=='2'){
		   if(rec22.rec_type=='2') break;
		   copy(p_data,(char *)&rec22.rec_type,128);
		   if(rec22.code_verv=='0') goto bew_found;
		 }
		 else if(*rec_deel=='3'){
		   if(rec23.rec_type=='2') break;
		   copy(p_data,(char *)&rec23.rec_type,128);
		   if(rec23.code_verv=='0') goto bew_found;
		 }
		 break;
      case '3' : break;
      case '4' : break;
      case '8' : n_sal=get_val(p_data+41,p_data+42,12,3); break;
      case '9' : tot_deb=get_val("1",p_data+22,12,3);
		 tot_cre=get_val("0",p_data+37,12,3);
		 return 99; break;
      default  : break;
    }
  }
  bew_found:;
  st.volgnr=num_get(&rec21.volgnr[0],4);
  st.val_dat=cnv_dat(&rec21.val_dat[0]);
  st.bedrag=get_val(&rec21.teken,rec21.bedrag,12,3);
  if(rec21.type_med=='1'){
    k=num_get(rec21.mededel,3);
    if(k>=101 && k<=102) copy(&rec21.mededel[3],st.g_med,12);
    else {/* GEEN geldige mededeling */
      copy(&rec21.mededel[3],st.g_med,12);
      copy(st.g_med,opmerk,20);
      goto endsr;
    }
    copy(st.g_med,st.klt_nr,5); st.klt_nr[5]='\0';
    copy(&st.g_med[5],st.fact_nr,5); st.fact_nr[5]='\0';
    insert(st.g_med,7,'/'); insert(st.g_med,3,'/');
    if(klcd==NO || (sys1848 & 1)){
      *u(2,1)=val(st.klt_nr);errnum=fasgeti(2);
    }
    else{
      len_=fldlen(2,2); if(len_>5) len_=5;
      copy(st.klt_nr,s(2,2),len_);
      if(klcd) errnum=faskeyi(2,1,0);
    }
    if(errnum)  fasinit(2);
    stutyp=2; lkg='K'; rec_nr=*u(2,1)+30000; st.rf_vl=val(st.fact_nr);
    if(rec_nr>30000) corr_y2000(4,rec_nr);
    copy(s(2,3),lkgnaam,fldlen(2,3));
    jddate(dat_ogm,&yy_,&dum1,&dum2);
    if(yy_<2000) yy_=yy_%100; else yy_=(yy_%100)+100;/* y2000 */
    found=NO;
    for(j=0;j<5;j++){/* probeer 5 laatste jaren */
      for(k=0;k<80;k++){/* probeer alle verkoopjournalen */
	if(j_tab[k].typ==2){
	  fasinit(4);*u(4,5)=rec_nr;*s(4,8)=yy_-j;*s(4,9)=j_tab[k].nr;*u(4,10)=st.rf_vl;
	  if(faskeyi(4,4,1)==0){
	    if(*u(4,5)==rec_nr && *s(4,8)==yy_-j && *s(4,9)==j_tab[k].nr &&
	       *u(4,10)==st.rf_vl){
	      st.rf_yy=yy_-j;st.rf_jr=j_tab[k].nr;found=YES;break;
	    }
	  }
	}
      }
      if(found) break;
    }
    if(found==NO){
      st.rf_yy=yy_;
      for(k=0;k<80;k++) if(j_tab[k].typ==2) break;
      st.rf_jr=j_tab[k].nr;
    }
  }
  else{
    copy(rec21.mededel,st.g_med,30);
    copy(st.g_med,opmerk,20);
  }
  endsr:;
  return 0;
}
 

static void insert(char *p, int16 pos, char byte)
{
  int16 j;
 
  j=20;
  while(j-->pos)
    *(p+j) = *(p+j-1);
  *(p+pos)=byte;
}
 

static  uint16 cnv_dat(char *p)
{
  int16 jj,mm,dd;
  dd=num_get(p,2); mm=num_get(p+2,2); jj=num_get(p+4,2);
  return datejd(jj,mm,dd);
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
  if(eof_ && *p_data=='\0' || *p_data==0x1A) return YES;
  else{/* positioneer terug op eerste karakter */
    *pl_80_1=pos_;
    return NO;
  }
}

static long num_get(char *p, int16 count)
{
  char buf[30];
 
  copy(p,buf,count);
  *(buf+count)='\0';
  return val(buf);
}
 

static void boek_ogm(void)
{
  bd_bkh=-st.bedrag;
  rec_nr=*u(stutyp,1)+30000*(stutyp-1);
  bd_bkh_t+=st.bedrag;
  boek_div();
}

static void boek_end(void)
{
  st.rf_yy=0;st.rf_jr=0;st.rf_vl=0;
  bd_bkh=bd_bkh_t;
  rec_nr=recnr_ogm;
  st.bedrag=tot_bew; copy("   <== T O T A A L",rec23.naam,18);
  lkg='\0';
  nextline();
  boek_div();
  bd_bkh_t=0;
}
 

static void boek_div(void)
{
  int16 k;
  long grbveld;
  for(k=1;k<20;k++) prtinfo(k,0); nextline();
  *s(4,2)=journl;
  *u(4,3)=volgnr_ogm;
  *u(4,4)=dat_ogm;
  if(bd_bkh){
    *l(4,7)=bd_bkh;
    *d(4,32)=bd_bkh; *s(4,31)='E';
    *u(4,5)=rec_nr;
    if(rec_nr<30000) grbveld=levcent;
    else if(rec_nr<60000) grbveld=kltcent;
    else {*u(3,1)=rec_nr-60000;fasgeti(3);grbveld=*l(3,2);}
    *l(4,6)=grbveld;
    *s(4,8)=st.rf_yy%100; if(*s(4,8)<50) *s(4,8)+=100;/* y2000 */
    *s(4,9)=st.rf_jr;
    *u(4,10)=st.rf_vl;
    if(*s(4,9)==0 && *u(4,10)==0 && *s(4,8)==100) *s(4,8)=0;/* correctie y2000 */
    *s(4,12)=0;
    if(fldlen(4,28) && opmerk[0]) copy(opmerk,s(4,28),20);
    fasadd(4);
  }
  fasflush(0);
  geboekt=YES;
}

static void corr_y2000(uint16 bstu_, uint16 searcnr_)/* Y2000 probleem oplossen tijdelijk tot 2005 */
{
  char *ry_,*rjn_,ly_;
  uint16 *prec_,*rvl_,mode_,len_stu_;
									
  scrget(1,7);
  prec_=u(bstu_,5);ry_=s(bstu_,8);
  rjn_=s(bstu_,9); rvl_=u(bstu_,10); len_stu_=fldlen(bstu_,0);
  fasinit(bstu_); *prec_=searcnr_; mode_=1; ly_=*ry_;
  FOREVER{
    if(faskeyi(bstu_,4,mode_)) break; mode_=2;
    if(*prec_!=searcnr_) break;
    ly_=*ry_;
    if(*rjn_ || *rvl_){
      if(*ry_<50) *ry_+=100;
    } else if(*ry_==100) *ry_=0;
    if(*ry_!=ly_) fasupd(bstu_);               /* indien gewijzigd, updaten */
    *ry_=ly_;                                      /* key-volgorde behouden */
  }
}

static int cmp_str(char *p1, char *p2, int16 len)
{
  while(len--){
    if(*p1++!=*p2++)return 1;
  }
  return 0;
}

static int str_len(char *p, int16 len)
{
  int16 k=0;
  while(len--){
    if(*p++=='\0') return k;
    k++;
  }
  return k;
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
  for(k=0;k<80;k++) sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
  sysget(2544,14,ogm_file); ogm_file[14]='\0';
  sysget(2558,2,&journl);
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;
  rec_type=s(80,1)+4;
  rec_deel=s(80,1)+5;
	
	zero((char *)CodaSettings.IBAN, sizeof CodaSettings);
	for(k=0;k<5;k++){
		sysget(19000+k*50,30,(char *)CodaSettings.IBAN[k]);
		sysget(19030+k*50,2,(char *)&CodaSettings.Jnl[k]);
		sysget(19032+k*50,4,(char *)&CodaSettings.WachtRekening[k]);
		if(CodaSettings.Jnl[k]){
			for(j=0;j<80;j++) if(CodaSettings.Jnl[k]==j_tab[j].nr) break;
			if(j<80) copy(j_tab[j].nm,CodaSettings.JnlNaam[k],15);
		}
	}
	sysget(19250,50,(char *)CodaSettings.SubDir);
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

static void ovl_exit(int16 nr)
{
  sysput(2544,14,ogm_file);
  sysput(2558,2,&journl);
  sysflush();
  prtclose();
  ovlexit(nr);
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
  if(key==104){scrget(1,7);return YES;}
  return NO;
}
 
