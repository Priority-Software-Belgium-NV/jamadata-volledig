
/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "Shlobj.h"
extern "C" char* DRK2397GetD() {return &zzvw;}

// extern
extern "C" int CheckEmailAdres(char *email_, int len_,int internetcheck_); 
extern "C" int Fld2String(int stunr, int fldnr, char *OutBuffer, int MaxLen);
extern "C" int SendMail(int send_mode);
extern "C" int CopyMoveFile(char *FromFile,char *ToFile,int DeleteOriginal); // kopieren van een file
extern "C" int DirCall_DRK2215_SelectArtikel(void);
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" int FileExist(char *FileName);
extern "C" int FtpDeleteFile(char *Server, char *User, char *PW, char *FileName);
extern "C" int FtpUploadFile(char *Server, char *User, char *PW, char *FileName);
extern "C" int FtpDownloadFile(char* buf, int buflen, char *Server, char *User, char *PW, char *FileName);
extern "C" int FtpDirectory(char* buf, int buflen, char *Server, char *User, char *PW, char *Wildcard);
extern "C" int SFtpDeleteFile(char *Server, char *User, char *PW, char *FileName, int PortNr);
extern "C" int SFtpUploadFile(char *Server, char *User, char *PW, char *FileName, int PortNr, char *FtpFileName);
extern "C" int SFtpDownloadFile(char* buf, int buflen, char *Server, char *User, char *PW, char *FileName, int PortNr);
extern "C" int SFtpDirectory(char* buf, int buflen, char *Server, char *User, char *PW, char *Wildcard, int PortNr);
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" void GetCurrentDateTime(int16 *jj, int16 *mm, int16 *dd, int16 *uur, int16 *min, int16 *sec) ;
extern "C" void GetFileFromServer(char *FileName);
extern "C" int16 Search(int stu_,int mod_);
extern "C" char *VarTextFmt(int len_,int update_);


typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();
extern "C" char DRK2397dat[] = "drk2397  00:01 01/03/23 (c) Jamadata";  // Prik&Tik export module
  
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXFLD          120
#define DIM_KLANT			      20000
#define MAX_EIGENART       1000 // 7/10/2015 : 202 artikels
#define MAX_RECS        500
#define MAX_SEARCH_KEYWORDS  10

#define KLEUR_WIT           0xFFFFFF

#define CSV_FIELDDELIM		  '\x09' // ","

#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_RDWR         0x0002  /* open for reading and writing */
#define O_APPEND       0x0008  /* writes done at eof */
#define O_CREAT        0x0100  /* create and open file */
#define O_TRUNC        0x0200  /* open and truncate */
#define O_EXCL         0x0400  /* open only if file doesn't already exist */
#define O_TEXT         0x4000  /* file mode is text (translated) */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */


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

static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us70[]  = {7,0xC8,70,0,0,0,0};
static char fm_us55[]  = {7,0xC8,55,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us35[]  = {7,0xC8,35,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us10[]  = {7,0xC8,10,0,0,0,0};
static char fm_us3[]   = {7,0xC8,3,0,0,0,0};
static char fm_us10U[] = {7,0xC8,10,0,1,0,0};
static char fm_us3_U[] = {7,0xC8,3,0,1,0,0};
static char fm_us2_U[] = {7,0xC8,2,0,1,0,0};
static char fm_us2[]   = {7,0xC8,2,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf42_[] = {6,0xD4,4,2,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou2S[]   = {6,0x90,2,0,0x20,0};
static char fm_ou1[]   = {6,0x90,1,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2S[] = {6,0xD0,2,0,0x20,0};
static char fm_uu1_s[] = {6,0xD0,1,0,0x20,0};
static char fm_ui5[]   = {6,0xD1,5,0,0x60,0};
static char fm_ui4[]   = {6,0xD1,4,0,0x60,0};
static char fm_ui3[]   = {6,0xD1,3,0,0x60,0};
static char fm_ui2[]   = {6,0xD1,2,0,0x60,0};
static char fm_ui3_s[] = {6,0xD1,3,0,0x40,0};
static char fm_ui1[]   = {6,0xD1,1,0,0x60,0};
static char fm_ul8[]   = {6,0xD3,8,0,0x70,0};
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_ol6[]   = {6,0x93,6,0,0x70,0};
static char fm_of42_[] = {6,0x94,4,2,0x60,0};
static char fm_of3_2[] = {6,0x94,3,2,0x60,0};
static char fm_of6_2[] = {6,0x94,6,2,0x60,0};
static char fm_of4_2[] = {6,0x94,4,2,0x60,0};
static char fm_ud6_2[] = {6,0xD5,6,2,0x70,0};
static char fm_ud4_2[] = {6,0xD5,4,2,0x70,0};
static char fm_ud4_0[] = {6,0xD5,4,0,0x70,0};
static char fm_od4_2[] = {6,0x95,4,2,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_od4_0[] = {6,0x95,4,0,0x70,0};
static char fm_ugrb[]  = {2,0xE8};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_us01[]   = {11,0xC8,1,0,1,0,'0','2',0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uLP[]   = {11,0xC8,1,0,1,0,'L','L','P','P',0};
static char fm_uJNV[]   = {15,0xC8,1,0,1,0,'J','J','N','N','V','V',' ',' ',0};
static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_us8PW[] = {7,0xC8,8,0,5,0,0};
static char fm_uRKSLW[] = {17,0xC8,1,0,1,0,'R','R','K','K','L','L','S','S','W','W',0};
static char fm_uWHSNr[]= {9,0xC8,7,0,1,0,'0','9',0};

// eigen routines
static void AdjustPOCHorecaTyp(void);
static int copy0cijfers(char *ps,char *pd,int max_len_);
static int16 Copy2ZoekStr(char *ps3_,char *zoekstr,uint16 len3_,uint16 lenz_);
static CString Cstring2CSV(CString string_fld_);
static int16 ExecSearch(int16 mode_);
static int FillArtTable(void);
static uint16 GetAKFiche(uint16 arec_, uint16 lrec_);
static void InitLoad(void);
static void LijstArtikels(void);
static void LijstVerplichteKlanten(void);
static void MailDocument(int SendMode);
static void MakeDeHeer(int16 stu_,char *nm_dehr);
static void MakeXlsFromKas(int sel_mode_); // 0=via klantenveld, 1=met uitgebreide klantselectie
static void MakeXlsFromSTA(int sel_mode_); // 0=via klantenveld, 1=met uitgebreide klantselectie
static void MenuHISExport(void);
static void UpdateSettings(void);
static void WriteHisLine2Xls(uint16 datum_,float aantal_,uint16 hisklt_);


static void InitConvertTab(void);  // komt uit JMS
static void GetSearchKeyWords( char *s);
static int GetSearchText(char *s,char *d,int len);  // analoog aan JMS (composekey)
static int MakeFullRecDens(int stunr, char *FullRecDens);
static int AllKeywordsFound(char *FullRecDens, int FullRecDensLen);
static void DisplayLine(int16 z);


////  SIF-File routines
static CString Fld2CString(int stu_,int fld_);
static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_);
static double String2Getal(CString S,char decim_kar);
static double String2Double(CString S){return String2Getal(S,',');}
static double String2Double(CString S,char decim_kar){ return String2Getal(S,decim_kar);}
static int String2Int(CString S){return (int)(String2Getal(S,','));}
static CString Double2String(double getal,long mode); // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
static CString Date2String(unsigned int date_,int mode_);
static CString Read_Rec(int f_nr_);
static CString Rec_Ele(CString s, int kol_, int maxlen_, char delim_kar_);
//////////////////////////////////////


// standaard routines 
static int cmpstrU(char *p1, char *p2, int16 len);
static int copy0(char *ps,char *pd,int max);
static int CopyOnlyChar(char *ps, char *pd, int16 len_);
static void p_pdfname(char *naam_,uint16 dt_beg_,uint16 dt_end_);
static double Round(double getal, double round);
static bool FasFileOpen(int16 nr_);

///// XLS-FUNC 
extern int16 ilength; // XLS
static int XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi,prt2xls; // XLS

static int fas_ret(char *s);
static int XlsCreate(char *name);
static int XlsClose(int16 ref,int16 Action);
static int XlsSaveAsPdf(int16 ref);
static int XlsWrite(int16 ref,int16 rownr,int16 colnr,int16 type,char *val, int16 StyleIx);
static int XlsSelectWorkSheet(int16 ref,int16 WksNr,char *WksName); // WknNr = 1, 2, ... WksCount
static int XlsChart(int16 ref,int16 rowcnt,int16 colcnt,int16 chartType,char *title);
static int XlsGraf(int16 ref,int16 colnr,int16 chartType,long Color);
static int XlsRowSize(int16 ref,int16 rownr,int16 size);
static int XlsColumnSize(int16 ref,int16 rownr,int16 size);
static int XlsStyle(int16 ref, char *NumFormat,int16 Size,long Color,int16 BoldFlag,int16 ItalicFlag,int16 UnderlineFlag,int16 HorAlignment,int16 VerAlignment,long BackCol,int16 Pattern,int16 Kader,long KaderCol,int16 Lock,int16 Hide);
static int16 WriteVar2Xls(int16 rij_,int16 kol_,char *fmt_,char *pvar_,int16 StylIx);
static int16 WriteFld2Xls(int16 rij_,int16 kol_,int16 stu_,int16 fld_,int16 StylIx);

static int XlsOpen(char *name); // XLS open for read
static int XlsGetMaxKol(int16 ref);
static int XlsGetMaxRij(int16 ref);
static int XlsReadString(int16 ref,int16 rownr,int16 colnr,char *ret_string, int16 MaxLen);
static int XlsReadInt(int16 ref,int16 rownr,int16 colnr);
static double XlsReadDouble(int16 ref,int16 rownr,int16 colnr);
static short unsigned XlsReadDate(int16 ref,int16 rownr,int16 colnr);


#include "Std\XlsFunc.CPP"
// ---------------------------------------


// de variabelen
static long TbDiversArtikel[10];
static uint16 InqMaandBeg,InqMaandEnd,InqJaar,DatBeg,DatEnd,MaxEigenArt,klcd,stu=2;
static int16 StylDate,StylNormal,ft_off,max_kassa;
static char MailBodyText[5][80],MailTemplate[10],ConfirmKlant='J',ArtEANString[400];
static char UniverseExport='N',sys3896[6],SkipGekoppeld,firma[350],OrigKltBuf[1000];
static int FtGood,FtSkipped,MaxKlt;
static int16 ThisYear;
static FILETIME FtFtimeBeg, FtFtimeEnd;
static uint16 recs[MAX_RECS],recs_used,StartNr;
static char recs_preferred[MAX_RECS];
static unsigned SpoolFileNr,GegevensVJ;
static char FileName[100];
static int ViaHistoriek,ViaStatistiek; 
static uint16 MailDirect,sys3876;   
static bool ReadEOFline;
static uint16 InqLev, *pLevFld;
static char SearchKeywords[MAX_SEARCH_KEYWORDS][100];
static char ICSBTab[256];

static uint16 sys4400,sys4408,z299,dt_dag1,dsp_count;
static char nm_kassa[20][6],filnam[40];
static uint16 dt_kvk[20],loc_klt[20],loc_nr[20]; 
static char nm_loc[10][6], nm_fil[10];
 
static int fmt_get(int16 stu_, int16 elet_);
static void flt2str(float bd_);
static char seqo_str[1000],DelimKar=0x09,fmt[40];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;
static void char2str(char *ps_,int16 len_);
static void seqo_fld(int16 stu_, int16 fld_);
static void seqo_flush(void);
static void seqo_var(char *fm_,char *pvar_);
static void seqo_dumpline(int16 add_eor_);

static char *selp_txt[6]={"Ondergrens (>)","Ondergrens (> of =)",
		"Bovengrens (<)","Bovengrens (< of =)",
		"Gelijk","Niet gelijk"};
static int16 selp_stu=0;
static int16 prt2pdf;
static char selp_bf[4][1000],selp_des[40],*selp_fld,*calctype;
static uint16 selp_use,selp_ge,selp_le,sys3618;
static char taal_i,talen[4];

static int16 kdsp,kdsp_off=1;
static long rec_working;
static char disp_str[55];

static void dsp_working(void);

static int selp_tst(void);/* 00.04 */
static int comp_str(char *p1,char *p2,int16 len);
static int comp_byt(char *p1,char *p2,int16 len);
static int comp_taa(char *p1,char *p2,int16 len);
static int used(char *b,int16 len);
static int comp_num(char *p1,char *p2,int16 type);
static int selp_ask(void);
static void selp_wis(void);
static void selp_upd(int16 bfnr,char men_keuze);
static void taal_upd(int16 z,int16 fld_);
static int taal_chk(int16 fld_);


static struct _Settings {
	char FtpUserID[35];
	char FtpPaswoord[35];
	char XlsFilename[30];
	char FtpAdres[80];
	uint16 FtpPoort;
	uint16 RecLeverancier; // >30000 = merk/producent
	char KlantNummer[11];
	char EmailAdres[50]; // not used
	uint16 LastMaand;
  uint16 LastJaar;
	int16 WerkpostDisplayAlarm;
	char PnTKlantNr[10];
	char API_key[51];
} Settings;

static struct{
  uint16 rec;
  char artcode[15];
} TbArt[MAX_EIGENART];

static struct _TbKlant {
	uint16 RecordNr;
	char Bcode;
} TbKlant[DIM_KLANT];

static struct _FilData{
		double AW;
		double VW;
		double qlv;
	} FilData[20];

static char TbCocaGroepen[101];
static CMarkup HisXml;

extern "C" void DRK2397cod(int16 parmval)
{
	uint16 dt_;
	  
	if(FasFileOpen(1)==false) {DisplayWarning("Unable to open LEV-fasfile!",605,0); goto endsr;}
  if(FasFileOpen(2)==false) {DisplayWarning("Unable to open KLT-fasfile!",605,0); goto endsr;}
	if(FasFileOpen(6)==false) {DisplayWarning("Unable to open ART-fasfile!",605,0); goto endsr;}
  if(FasFileOpen(9)==false) {DisplayWarning("Unable to open VKP-fasfile!",605,0);goto endsr;}
	InitLoad();
	for(dt_=*u(25,2)-40;dt_<=*u(25,2); dt_++){ // datums laatste inlezen bepalen
    fasinit(91);*u(91,3)=dt_;
		if(faskeyi(91,2,1)) continue;
		if(*u(91,3)!=dt_) continue;
		if(*u(91,2)!=0) continue;
	}
	MenuHISExport();
	endsr:;
	ovlexit(-1); 
}

static void MenuHISExport(void)// Export via kassa-verkopen
{
  int16 k,z,key,curs=1,jj,mm;

	
	DatBeg=0;
	InqMaandBeg=0;InqMaandEnd=0;InqJaar=ThisYear; StartNr=0; SkipGekoppeld='J'; GegevensVJ='N';
  FOREVER{
redo:;
		scrnum=0; scrget(3,3); z=1;
		scraddpicto(50,0,76,0,4,2,105,1,7,"^!B2397A");
		scraddpicto(9,0,76,22,4,2,59,0,4,"Parameters");
		scraddpicto(1,0,36,3,6,3,573,0,0,"Bekijk XLS"); 
		scraddpicto(2,0,43,3,6,3,569,0,0,"Stuur gegevens naar Prik&Tik"); 
		scrifld(z++,fm_uu2,&InqMaandBeg);// scrifld(z++,fm_uu2,&InqMaandEnd);
		scrifld(z++,fm_uu4,&InqJaar);
		scrifld(z++,fm_ou2,&Settings.LastMaand);	scrifld(z++,fm_ou4,&Settings.LastJaar);
    for(k=0;k<10;k++) {
			if(nm_kassa[k][0]){
				scrifld(z++,fm_os6,&nm_kassa[k][0]);
				scrifld(z++,fm_odat,&dt_kvk[k]);
			} else z+=2;
    }
    key=scrupd(curs,0x307);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) goto endsr;
		if(Settings.RecLeverancier==0 || Settings.KlantNummer[0]=='\0' || key==5009){ UpdateSettings();goto redo;}
		fasinit(1); *u(1,1)=Settings.RecLeverancier; if(*u(1,1)>30000) *u(1,1)-=30000; fasgeti(1);
		if(key==5050) goto redo; // link help 
		if(InqMaandBeg<1 || InqMaandBeg>12) {curs=1;errnum=34; goto redo;}
		InqMaandEnd=InqMaandBeg;
//		if(InqMaandEnd<InqMaandBeg || InqMaandEnd>12) {curs=2;errnum=34; goto redo;}
		if(InqJaar<2010 || InqJaar>2030) {curs=3;errnum=34; goto redo;}
  	DatBeg=datejd(InqJaar,InqMaandBeg,1);
  	jj=InqJaar; mm=InqMaandEnd+1; if(mm>12){mm=1;jj=InqJaar+1;} DatEnd=datejd(jj,mm,1)-1;
		if(DatBeg==0) {curs=1; errnum=34;goto redo;}
		if(DatEnd<DatBeg) {curs=2;errnum=34;goto redo;}
		MailDirect=NO; selp_use=NO;
		if(key==5001 || key==110){
			MailDirect=NO;
			if(key==110){
				if(selp_ask()) goto redo;
				MakeXlsFromKas(1);
			}
			else MakeXlsFromKas(0);
		}
    if(key==5002) {
			MailDirect=YES;
	/*		Settings.LastMaand=InqMaandEnd;
			Settings.LastJaar=InqJaar;
			sysput(8742,2,(char *)&Settings.LastMaand); 
	    sysput(8744,2,(char *)&Settings.LastJaar); */
			MakeXlsFromKas(0);
		}
	}
  endsr:;
}

static void MakeXlsFromKas(int sel_mode_) // 0=via klantenveld, 1=met uitgebreide klantselectie
{
  int16 j,k,n,mode_,mode91_,used_,klt_used_,kltrec_,mm,jj,dd,max_art_,max_per_,hiskey_,kltfld_,len_,len1_,firsttime_;
	uint16 hisklt_,hkltrec_,datum_,last_dt_;
  char buf_[100],str_[150],frfile_[150],filnam_[150],ftpfile_[150];
	double AW,VW,winst,tot_aw,tot_vw,qlv,liters_;
	float aantal_,volume_;
  long lbd_;
	CString cstr_;
	struct {
		double AW;
		double VW;
		double qlv;
	} FilData[20];

// SFtpDownloadFile(buf_,sizeof buf_, Settings.FtpAdres, Settings.FtpUserID, Settings.FtpPaswoord,"DIR.LST",Settings.FtpPoort);
// SFtpDeleteFile( Settings.FtpAdres, Settings.FtpUserID, Settings.FtpPaswoord,"DIR.LST",Settings.FtpPoort);
//SFtpDirectory(buf_,sizeof buf_, Settings.FtpAdres, Settings.FtpUserID, Settings.FtpPaswoord,"*.xls",Settings.FtpPoort);
//goto endsr;

	scrget(1,7);scrupd(-3,0);
	if(MailDirect){
		zero(FileName,sizeof FileName);jddate(DatBeg,&jj,&mm,&dd);
	  sprintf_s(FileName,sizeof FileName,"%s_Products_%02d-%04d.CSV",Settings.KlantNummer,InqMaandBeg,InqJaar);
		fasclos(-2);fasunlck(-2);
    if(fasopen(FileName,2)) {errnum=9;goto endsr;}
    fasinit(80);seqo_pos=0;seqo_mode=2; DelimKar='\x09';
    zero(seqo_str,sizeof seqo_str);pos=0;
    cstr_=CString("PnT-lidNr;ArtikelCode;PnT-ArtCode;Omschrijving;Leverancier;Merk/producent;Groep;Eenheid;Aantal/bak;Inhoud;BTW%;EANbak;EANStuk");
    pos=cstr2arr(cstr_,seqo_str,sizeof seqo_str);for(k=0;k<pos;k++) if(seqo_str[k]==';') seqo_str[k]=0x09;
    seqo_dumpline(YES);
	}
	else{
		zero(FileName,sizeof FileName);jddate(DatBeg,&jj,&mm,&dd);
		sprintf_s(FileName,sizeof FileName,"%s_Products_%02d-%04d.XLS",Settings.KlantNummer,InqMaandBeg,InqJaar);
		XlsRef=XlsCreate(FileName);
		if(XlsRef<=0) {errnum=30;goto endsr;}
		XlsColumnSize(XlsRef,1,30);XlsColumnSize(XlsRef,4,30);XlsColumnSize(XlsRef,5,30);XlsColumnSize(XlsRef,6,30);XlsColumnSize(XlsRef,7,25);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		zero(buf_,sizeof buf_); sprintf_s(buf_,20,"Omzet_%02d-%02d-%04d",dd,mm,jj);
		XlsSelectWorkSheet(XlsRef,1,buf_); 
		XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PnT-lidNr",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"ArtikelCode",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PnT-ArtCode",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Leverancier",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Merk/producent",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Groep",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Eenheid",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal/bak",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Inhoud",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"BTW%",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EANbak",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EANStuk",StylNormal);
 		XlsRij++;XlsKol=1;
	}
  scrnum=0;scrget(1,170);scrifld(5,VarTextFmt(50,0),"Bezig met uitschrijven artikels ...");scrupd(-3,0);
  fasinit(6);
  FOREVER{
    next_art:;
    if(faskeyi(6,2,2)) break;
		dsp_working();
		if(*u(6,9)==99) goto next_art;
		if(sel_mode_){
			if(selp_tst()==NO) goto next_art;
		}
		fasinit(52);*u(52,1)=*u(6,9);fasgeti(52); 
		if(*s(52,24)=='J') goto next_art; // NIET op prijslijst
    fasinit(91);*u(91,2)=*u(6,1);*u(91,3)=DatBeg;mode91_=1;
    FOREVER{
      if(faskeyi(91,1,mode91_)) break;mode91_=2;
      if(*u(6,1)!=*u(91,2)) goto next_art;
      if(DatEnd && *u(91,3)>DatEnd) goto next_art;
			break;
		}
		fasinit(11);GetAKFiche(*u(6,1),Settings.RecLeverancier);
		zero(ArtEANString,sizeof ArtEANString);len_=0;len1_=0;
		if(*s(6,70)) len_+=copy0cijfers(s(6,70),&ArtEANString[len_],fldlen(6,70));
		if(*s(6,71)) len1_+=copy0cijfers(s(6,71),&ArtEANString[200+len1_],fldlen(6,71));
		if(fldlen(64,1)){
			fasinit(64);*u(64,3)=*u(6,1);mode_=1;
			for(k=0;k<10;k++){
				if(faskeyi(64,2,mode_)) break; mode_=2;
				dsp_working();
				if(*u(64,3)!=*u(6,1)) break;
				if(YES /* *u(64,5)==0 */){
					if(*u(64,3)){
  					if(len1_) ArtEANString[200+len1_++]='|';
	  				len1_+=copy0cijfers(s(64,2),&ArtEANString[200+len1_],fldlen(64,2));
					}
					else{
 						if(len_) ArtEANString[len_++]='|';
	  				len_+=copy0cijfers(s(64,2),&ArtEANString[len_],fldlen(64,2));
					}
				}
			}
		}
		if(MailDirect){
			XlsKol=1;
			seqo_var(VarTextFmt(10,0),(char *)&Settings.KlantNummer); // P&T klantcode
			seqo_fld(6,2);// code
			seqo_fld(11,5);//  P&T code
			seqo_fld(6,3);// omschrijving
			fasinit(1);*u(1,1)=*u(6,7);fasgeti(1);seqo_fld(1,3);// leverancier
			if(fldlen(6,101) && *u(6,101)){
				fasinit(1);*u(1,1)=*u(6,101);fasgeti(1);seqo_fld(1,3);// merk
			}
			else seqo_var(VarTextFmt(1,0),"");
			seqo_fld(52,14);// groep
			seqo_fld(6,10);// EH
			seqo_fld(6,31);// q_bak
			seqo_fld(6,37);// inhoud
			seqo_fld(6,28);// BTW%
			seqo_var(VarTextFmt(100,0),(char *)ArtEANString); // EAN bak
			seqo_var(VarTextFmt(100,0),(char *)&ArtEANString[200]); // EAN fles
			seqo_dumpline(YES);
		}
		else{
			XlsKol=1;
			WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(10,0),(char *)&Settings.KlantNummer,StylNormal); // P&T klantcode
			WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);// code
			WriteFld2Xls(XlsRij,XlsKol++,11,5,StylNormal);//  P&T code
			WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);// omschrijving
			fasinit(1);*u(1,1)=*u(6,7);fasgeti(1);WriteFld2Xls(XlsRij,XlsKol++,1,3,StylNormal);// leverancier
			if(fldlen(6,101) && *u(6,101)){
				fasinit(1);*u(1,1)=*u(6,101);fasgeti(1);WriteFld2Xls(XlsRij,XlsKol++,1,3,StylNormal);// merk
			}
			else XlsKol++;
			WriteFld2Xls(XlsRij,XlsKol++,52,14,StylNormal);// groep
			WriteFld2Xls(XlsRij,XlsKol++,6,10,StylNormal);// EH
			WriteFld2Xls(XlsRij,XlsKol++,6,31,StylNormal);// q_bak
			WriteFld2Xls(XlsRij,XlsKol++,6,37,StylNormal);// inhoud
			WriteFld2Xls(XlsRij,XlsKol++,6,28,StylNormal);// BTW%

			WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(100,0),(char *)ArtEANString,StylNormal); // EAN bak
			WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(100,0),(char *)&ArtEANString[200],StylNormal); // EAN fles
			XlsRij++;XlsKol=1;
		}
	}



	if(MailDirect){
		fasclos(-2);
		//sprintf_s(frfile_,100,"..\\Spool\\Files\\%08X-%03d-$%s",SpoolFileNr,procid,FileName); // dit is de gewenste naam		
		////cstr_=Settings.ArtikelDir; cstr_.TrimRight('\\'); cstr_+=CString("\\Articles.XLS");
		////zero(filnam_,sizeof filnam_); bcopy((char *)(LPCTSTR)cstr_,filnam_,cstr_.GetLength());
		//for(k=0;k<50;k++){
		//	if(FileExist(frfile_)){
		//		if(CopyMoveFile(frfile_,FileName,0)) break;
		//	}
		//}
		if(Settings.FtpAdres[0]){
#if _DEBUG
			if(DisplayWarning("PAS OP: DEBUG!!! Wilt ge echt de artikels uploaden?", 605,1)==NO) goto endsr;
#endif
//      cstr_=Settings.ArtikelDir; cstr_.TrimRight('\\'); cstr_+=CString("\\Articles.XLS");
			scrget(1,170);scrifld(6,VarTextFmt(50,0),"Bezig met uploaden artikels ...");scrupd(-3,0);
			zero(ftpfile_,sizeof ftpfile_); sprintf_s(ftpfile_,150,"artikels/%s",FileName);
			if(SFtpUploadFile(Settings.FtpAdres, Settings.FtpUserID, Settings.FtpPaswoord, FileName,Settings.FtpPoort, ftpfile_)==NO){
	  		DisplayWarning("Uploaden artikels niet gelukt! Controleer verbinding en probeer opnieuw.", 605,0); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
			}
			else{
				Settings.LastMaand=InqMaandEnd;
				Settings.LastJaar=InqJaar;
				sysput(8742,2,(char *)&Settings.LastMaand); 
				sysput(8744,2,(char *)&Settings.LastJaar); 
			}
		}

//	  MailDocument(0);
	}
	else XlsClose(XlsRef,1);

	scrnum=0;scrget(1,170);scrifld(5,VarTextFmt(50,0),"Bezig met uitschrijven omzetten ...");scrupd(-3,0);
	if(MailDirect){
		zero(FileName,sizeof FileName);jddate(DatBeg,&jj,&mm,&dd);
	  sprintf_s(FileName,sizeof FileName,"%s_Sales_%02d-%04d.CSV",Settings.KlantNummer,InqMaandBeg,InqJaar);
		fasclos(-2);fasunlck(-2);
    if(fasopen(FileName,2)) {errnum=9;goto endsr;}
    fasinit(80);seqo_pos=0;seqo_mode=2; DelimKar='\x09';
    zero(seqo_str,sizeof seqo_str);pos=0;
    cstr_=CString("PnT-lidNr;Winkel;Datum;ArtikelCode;PnT-ArtCode;Omschrijving;EANbak;EANStuk;Aantal;Volume (L);Bedrag ex.BTW");
    pos=cstr2arr(cstr_,seqo_str,sizeof seqo_str);for(k=0;k<pos;k++) if(seqo_str[k]==';') seqo_str[k]=0x09;
    seqo_dumpline(YES);
	}
	else{
		zero(FileName,sizeof FileName);jddate(DatBeg,&jj,&mm,&dd);
		sprintf_s(FileName,sizeof FileName,"%s_Sales_%02d-%04d.XLS",Settings.KlantNummer,InqMaandBeg,InqJaar);
		XlsRef=XlsCreate(FileName);
		if(XlsRef<=0) {errnum=30;goto endsr;}
	//	XlsColumnSize(XlsRef,1,30);XlsColumnSize(XlsRef,4,40);XlsColumnSize(XlsRef,5,40);XlsColumnSize(XlsRef,6,35);XlsColumnSize(XlsRef,8,25);
	//	XlsColumnSize(XlsRef,9,35);XlsColumnSize(XlsRef,12,15);XlsColumnSize(XlsRef,14,35);XlsColumnSize(XlsRef,15,20);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		zero(buf_,sizeof buf_); sprintf_s(buf_,20,"Omzet_%02d-%04d",InqMaandBeg,InqJaar);
		XlsSelectWorkSheet(XlsRef,1,buf_); 
		XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PnT-lidNr",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Winkel",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Datum",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"ArtikelCode",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PnT-ArtCode",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EANbak",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EANStuk",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Volume (L)",StylNormal);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Bedrag ex.BTW",StylNormal);
		XlsRij++;XlsKol=1;
	}
	scrnum=0;scrget(1,170);scrifld(5,VarTextFmt(50,0),"Bezig met uitschrijven omzetten ...");scrupd(-3,0);
  fasinit(91); *u(91,3)=DatBeg;mode91_=1;last_dt_=0;
  FOREVER{
    next_bew:;
    if(faskeyi(91,2,mode91_)) break;mode91_=2;
		dsp_working();
    if(DatBeg && *u(91,3)< DatBeg) goto next_bew;
    if(DatEnd && *u(91,3)>DatEnd) break;
		fasinit(6);*u(6,1)=*u(91,2);if(fasgeti(6)) goto next_bew;
		if(*u(6,9)==99) goto next_bew;
		fasinit(52);*u(52,1)=*u(6,9);fasgeti(52); if(*s(52,24)=='J') goto next_bew; // NIET op prijslijst
		if(*u(91,3)!=last_dt_){scrofld(15,91,3,-1);scrupd(-3,0);last_dt_=*u(91,3);}
		AW=0;VW=0;qlv=0;
		zero((char *)FilData,sizeof FilData);
   	for(k=0;k<max_kassa;k++){
	//		if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue; // hoort niet bij dit filiaal
			n=0; if(fldlen(66,1) && loc_nr[k]>=1 && loc_nr[k]<=10) n=loc_nr[k];
			if(fldlen(91,11+k*5)){
				qlv+=*f(91,11+k*5); FilData[n].qlv+=*f(91,11+k*5);
				AW+=*f(91,12+k*5); FilData[n].AW+=*f(91,12+k*5);
				VW+=*f(91,13+k*5); FilData[n].VW+=*f(91,13+k*5); // /(1.+*f(6,28)/100.);
				
			}
			if(ft_off /* && add_ftvk=='J'*/ && fldlen(91,11+(k+ft_off)*5)){
				qlv+=*f(91,11+(k+ft_off)*5); FilData[n].qlv+=*f(91,11+(k+ft_off)*5);
				AW+=*f(91,12+(k+ft_off)*5);FilData[n].AW+=*f(91,12+(k+ft_off)*5);
				VW+=*f(91,13+(k+ft_off)*5); FilData[n].VW+=*f(91,13+(k+ft_off)*5);// /(1.+*f(6,28)/100.);
			}
		}
		if(qlv || VW){
			
			fasinit(11);GetAKFiche(*u(6,1),Settings.RecLeverancier);
			zero(ArtEANString,sizeof ArtEANString);len_=0;len1_=0;
			if(*s(6,70)) len_+=copy0cijfers(s(6,70),&ArtEANString[len_],fldlen(6,70));
			if(*s(6,71)) len1_+=copy0cijfers(s(6,71),&ArtEANString[200+len1_],fldlen(6,71));
			if(fldlen(64,1)){
				fasinit(64);*u(64,3)=*u(6,1);mode_=1;
				for(k=0;k<10;k++){
					if(faskeyi(64,2,mode_)) break; mode_=2;
					dsp_working();
					if(*u(64,3)!=*u(6,1)) break;
					if(YES /* *u(64,5)==0 */){
						if(*u(64,3)){
  						if(len1_) ArtEANString[200+len1_++]='|';
	  					len1_+=copy0cijfers(s(64,2),&ArtEANString[200+len1_],fldlen(64,2));
						}
						else{
 							if(len_) ArtEANString[len_++]='|';
	  					len_+=copy0cijfers(s(64,2),&ArtEANString[len_],fldlen(64,2));
						}
					}
				}
			}
			for(k=0;k<=10;k++){
				if(FilData[k].qlv || FilData[k].VW){
					dsp_working();
					FilData[k].qlv=Round(FilData[k].qlv,(double)(0.01));
					FilData[k].AW=Round(FilData[k].AW,(double)(0.01));
					if(MailDirect){
						XlsKol=1;
						seqo_var(VarTextFmt(10,0),(char *)&Settings.KlantNummer); // P&T klantcode
						if(k==0) 			seqo_var(VarTextFmt(10,0),(char *)&Settings.KlantNummer); // eigen winkel dan p&T nummer
						else{
							copy(nm_loc[k-1],nm_fil,6);
							seqo_var(VarTextFmt(6,0),(char *)nm_fil); // naam filiaal
						}
						datum_=*u(91,3); seqo_var(fm_odat,(char *)&datum_); // delivery date
						seqo_fld(6,2);// code
						seqo_fld(11,5);//  P&T code
						seqo_fld(6,3);// omschrijving
						seqo_var(VarTextFmt(100,0),(char *)ArtEANString); // EAN bak
						seqo_var(VarTextFmt(100,0),(char *)&ArtEANString[200]); // EAN fles
						seqo_var(fm_od6_2,(char *)&FilData[k].qlv); // aantal
						liters_=Round((double)(FilData[k].qlv* *f(6,37)),(double)(0.01)); seqo_var(fm_od6_2,(char *)&liters_); // volume
						FilData[k].VW=Round((double)(FilData[k].VW /(1.+*f(6,28)/100.)),(double)(0.01));
						seqo_var(fm_od6_2,(char *)&FilData[k].VW); // omzet
						seqo_dumpline(YES);
					}
  				else{
					  XlsKol=1;
  					WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(10,0),(char *)&Settings.KlantNummer,StylNormal); // P&T klantcode
   					if(k==0) WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(10,0),(char *)&Settings.KlantNummer,StylNormal); // eigen winkel dan p&T nummer
						else{
							copy(nm_loc[k-1],nm_fil,6);
							WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(6,0),(char *)nm_fil,StylNormal); // naam filiaal
						}
						datum_=*u(91,3); WriteVar2Xls(XlsRij,XlsKol++,fm_odat,(char *)&datum_,StylDate); // delivery date
	  				WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);// code
  					WriteFld2Xls(XlsRij,XlsKol++,11,5,StylNormal);//  P&T code
						WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);// omschrijving
						WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(100,0),(char *)ArtEANString,StylNormal); // EAN bak
						WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(100,0),(char *)&ArtEANString[200],StylNormal); // EAN fles
						WriteVar2Xls(XlsRij,XlsKol++,fm_od6_2,(char *)&FilData[k].qlv,StylNormal); // aantal
						liters_=Round((double)(FilData[k].qlv* *f(6,37)),(double)(0.01)); WriteVar2Xls(XlsRij,XlsKol++,fm_od6_2,(char *)&liters_,StylNormal); // volume
						FilData[k].VW=Round((double)(FilData[k].VW /(1.+*f(6,28)/100.)),(double)(0.01));
						WriteVar2Xls(XlsRij,XlsKol++,fm_od6_2,(char *)&FilData[k].VW,StylNormal); // omzet
						XlsRij++;XlsKol=1;
					}
				}
			}
		}
	}

	if(MailDirect){
		fasclos(-2);
		//sprintf_s(frfile_,100,"..\\Spool\\Files\\%08X-%03d-$%s",SpoolFileNr,procid,FileName); // dit is de gewenste naam		
		////cstr_=Settings.ArtikelDir; cstr_.TrimRight('\\'); cstr_+=CString("\\Articles.XLS");
		////zero(filnam_,sizeof filnam_); bcopy((char *)(LPCTSTR)cstr_,filnam_,cstr_.GetLength());
		//for(k=0;k<50;k++){
		//	if(FileExist(frfile_)){
		//		if(CopyMoveFile(frfile_,FileName,0)) break;
		//	}
		//}
		if(Settings.FtpAdres[0]){
#if _DEBUG
			if(DisplayWarning("PAS OP: DEBUG!!! Wilt ge echt de omzetten uploaden?", 605,1)==NO) goto endsr;
#endif
//      cstr_=Settings.ArtikelDir; cstr_.TrimRight('\\'); cstr_+=CString("\\Articles.XLS");
			scrget(1,170);scrifld(6,VarTextFmt(50,0),"Bezig met uploaden omzetten ...");scrupd(-3,0);
			zero(ftpfile_,sizeof ftpfile_); sprintf_s(ftpfile_,150,"verkopen/%s",FileName);
			if(SFtpUploadFile(Settings.FtpAdres, Settings.FtpUserID, Settings.FtpPaswoord, FileName,Settings.FtpPoort, ftpfile_)==NO){
	  		DisplayWarning("Uploaden verkopen niet gelukt! Controleer verbinding en probeer opnieuw.", 605,0); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
			}
			else{
				Settings.LastMaand=InqMaandEnd;
				Settings.LastJaar=InqJaar;
				sysput(8742,2,(char *)&Settings.LastMaand); 
				sysput(8744,2,(char *)&Settings.LastJaar); 
			}
		}

//	  MailDocument(0);
	}
	else XlsClose(XlsRef,1);
 
  endsr:;
}

static void WriteHisLine2Xls(uint16 datum_,float aantal_,uint16 hisklt_)
{
	int len_,fld_;
	char str_[150];
  float volume_;

  WriteFld2Xls(XlsRij,XlsKol++,25,1,StylNormal);// WHS name
	WriteVar2Xls(XlsRij,XlsKol++,fm_odat,(char *)&datum_,StylDate); // invoice date
	WriteFld2Xls(XlsRij,XlsKol++,2,1+klcd,StylNormal);// CustID
	WriteFld2Xls(XlsRij,XlsKol++,2,3,StylNormal); // Name
	if(fldlen(2,143) && *s(2,143)) fld_=143; else fld_=3; WriteFld2Xls(XlsRij,XlsKol++,2,fld_,StylNormal); // uithangbord
	if(fldlen(2,144) && *s(2,144)) fld_=144; else fld_=4; WriteFld2Xls(XlsRij,XlsKol++,2,fld_,StylNormal); //Street_NR
	if(fldlen(2,145) && *s(2,145)) fld_=145; else fld_=5; WriteFld2Xls(XlsRij,XlsKol++,2,fld_,StylNormal); // PostalCode
	if(fldlen(2,146) && *s(2,146)) fld_=146; else fld_=6; WriteFld2Xls(XlsRij,XlsKol++,2,fld_,StylNormal); // City
	if(hisklt_ && hisklt_!=*u(2,1)){
		*u(2,1)=hisklt_;fasgeti(2);
	}
	WriteFld2Xls(XlsRij,XlsKol++,2,3,StylNormal); // Payer Name
	WriteVar2Xls(XlsRij,XlsKol++,fm_odat,(char *)&datum_,StylDate); // delivery date
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylNormal); // Invoice number
	zero(str_,sizeof str_);	
	if(*l(2,10)){
		copy("BE",str_,2);btw_deco(&str_[2],l(2,10),0);
		if(str_[11]=='\0'){copy("BE0",str_,3);btw_deco(&str_[3],l(2,10),0);}
  }
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,StylNormal);// VAT
	WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal); // ArtID
	WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal); // ArtDescription
	for(len_=0;len_<400;len_++) if(ArtEANString[len_]=='\0') break;
	if(len_) WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(len_,0),ArtEANString,StylNormal); // EAN 
	else XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylNormal);
	WriteVar2Xls(XlsRij,XlsKol++,fm_of6_2,(char *)&aantal_,StylNormal); // aantal
	volume_=aantal_* *f(6,37);WriteVar2Xls(XlsRij,XlsKol++,fm_of6_2,(char *)&volume_,StylNormal); // Volume

  XlsRij++;XlsKol=1;

}

static int FillArtTable(void)
{
	uint16 *p_lev_,inq_lev_,mode_,len_;	
	int n;

	p_lev_=u(6,7); inq_lev_=Settings.RecLeverancier;
	if(fldlen(6,101) && Settings.RecLeverancier>30000){inq_lev_=Settings.RecLeverancier-30000; p_lev_=u(6,101);}
	len_=fldlen(11,5); if(len_>15) len_=15;
	fasinit(6);mode_=1;n=0;
	FOREVER{
		next:;
		if(faskeyi(6,2,mode_)) break; mode_=2;
		if(*p_lev_==inq_lev_){
	//		GetAKFiche(*u(6,1),inq_lev_);
			// if(*s(11,5)=='\0') goto next;
			TbArt[n].rec=*u(6,1); copy(s(6,2),TbArt[n].artcode,fldlen(6,2));
			if(*u(6,9)>=1 && *u(6,9)<99) TbCocaGroepen[*u(6,9)]=1;
			n++; if(n>=MAX_EIGENART) break;
		}
	}
	return n;
}

static void LijstArtikels(void)/* lijst van de gekoppelde artikels */
{
  int16 k,n,z,mode_;
	int16 form_dat[8],pr_mode,prtnr;
	uint16 inq_lev_,*p_lev_;
  char buf_[100];
  float inhoud_,gewicht_;
     
	p_lev_=u(6,7); inq_lev_=Settings.RecLeverancier;
	if(fldlen(6,101) && Settings.RecLeverancier>30000){inq_lev_=Settings.RecLeverancier-30000; p_lev_=u(6,101);}
	fasinit(1);*u(1,1)=inq_lev_; fasgeti(1);
	fasinit(6);
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  prtfld(25,1,-1);prttext("<t33b>");
  prttext("Lijst artikels ");prtfld(1,3,30);
  prttext("<b>");
  prttext("<t122>Blz.<ppp>.");
  prtbuf(1);z=1;
	prttab(z,11,5,1,-1); prttitle(z++,"Ref.lev.",3);
  prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
	prttab(z,6,3,1,-1); prttitle(z++,"Omschrijving",3);
	prttab(z,6,31,1,-1);prttitle(z++,"A/vp",0x13);
	prttab(z,6,37,1,-1);prttitle(z++,"Inhoud",0x13);
	prttab(z,6,71,1,-1);prttitle(z++,"EAN",3);
	prttab(z,6,71,1,-1);prttitle(z++,"EAN stuk",3);
  prtbuf(3);
	p_pdfname("Lijst te exporteren artikels",*u(25,2),0);
	fasinit(6);mode_=1;
	FOREVER{
		if(faskeyi(6,2,mode_)) break; mode_=2;
		if(*p_lev_==inq_lev_){
			GetAKFiche(*u(6,1),inq_lev_);
			for(k=1;k<10;k++) prtinfo(k,0); prtline();
		}
	}
	prtform(0);prtclose();
	endsr:;
}

static void MakeDeHeer(int16 stu_,char *nm_dehr)
{
  int16 max_,xpos_,j,k;

	zero(nm_dehr,40);xpos_=0; 
  for(max_=0;max_<40;max_++){
		if(*(s(stu_,3)+max_)=='\0') break;
		if(*(s(stu_,3)+max_)=='*') xpos_=max_;
	}
	if(max_==40 && *(s(stu_,3)+39)=='!') max_--;
	if(xpos_ && xpos_>=max_-1) xpos_=0;
	if(xpos_==0){copy(s(stu_,3),nm_dehr,max_);goto endsr;}

	for(k=xpos_+1;k<max_;k++) if(*(s(stu_,3)+k)!=' ') break;
	j=copy0(s(stu_,3)+k,nm_dehr,max_-k);
	nm_dehr[j++]=' ';copy(s(stu_,3),&nm_dehr[j],xpos_);
endsr:;
}

static uint16 GetAKFiche(uint16 arec_, uint16 lrec_)
{
	int16 mode_;
	uint16 verv_rec11_=0,rec11_=0;
	   
	fasinit(11);*u(11,3)=arec_;*u(11,2)=lrec_;mode_=1;
	FOREVER{
		next:;
		if(faskeyi(11,2,mode_)) break; mode_=2;
		if(*u(11,3)!=arec_) break;
		if(*u(11,2)!=lrec_) break;
		if(*u(11,9) && *u(11,9)<*u(25,2)) verv_rec11_=*u(11,1); // verlopen promotie
		else rec11_=*u(11,1);
	}
  if(rec11_==0) rec11_=verv_rec11_;
	fasinit(11);if(rec11_) {*u(11,1)=rec11_,fasgeti(11);}
	return rec11_;
}

static void UpdateSettings(void)
{
  int curs,z,key;
  char lev_prod_;

	sysget(8670,35,Settings.FtpUserID);
	sysget(8705,35,Settings.FtpPaswoord);
	sysget(8740,2,(char *)&Settings.RecLeverancier);
	sysget(8742,2,(char *)&Settings.LastMaand); 
	sysget(8744,2,(char *)&Settings.LastJaar); 
	sysget(8746,2,(char *)&Settings.WerkpostDisplayAlarm); if(Settings.WerkpostDisplayAlarm==0) Settings.WerkpostDisplayAlarm=1; 
	sysget(8750,10,Settings.KlantNummer);
	sysget(8760,70,Settings.FtpAdres);
	sysget(8830,2,(char *)&Settings.FtpPoort);
//	sysget(8400,50,Settings.API_key);
	fasinit(1);
	lev_prod_='L'; *u(1,1)=Settings.RecLeverancier;
	if(*u(1,1)>30000){lev_prod_='P';*u(1,1)=*u(1,1)-30000;}
	if(*u(1,1)) fasgeti(1);

	curs=1;
  FOREVER {
		redo:; 
    scrnum=0;scrget(3,4);z=1;
		scraddpicto(1,0,1,22,4,2,595,0,0,"annuleer"); scraddpicto(2,0,7,22,4,2,578,0,0,"OK"); scraddpicto(7,0,13,22,4,2,107,0,4,"Herdisplay"); 

		
//		scrifld(z++,fm_uLP,&lev_prod_);
		z++;
		scrfld(z++,1,3);
		scrifld(z++,fm_us70,Settings.FtpAdres);
		scrifld(z++,fm_uu4,&Settings.FtpPoort);
		scrifld(z++,fm_us35,Settings.FtpUserID);
		scrifld(z++,fm_us35,Settings.FtpPaswoord);
		scrifld(z++,fm_us10,Settings.KlantNummer);
		scrifld(z++,fm_ui2,&Settings.WerkpostDisplayAlarm);
//		scrifld(z++,fm_us50,Settings.API_key);
    key=scrupd(curs,0x2A0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106 || key==5001) goto endsr;
//		if(CheckEmailAdres(Settings.EmailAdres,60,0)==NO){errnum=34;curs=1; goto redo;}
		if(Search(1,0)){curs=2; goto redo;}; // moet ingevuld zijn
		if(Settings.KlantNummer[0]=='\0'){curs=7;errnum=38;goto redo;}
    if(key==108 || key==5002) break;
  }
//	if(lev_prod_=='P' && *u(1,1)) *u(1,1)+=30000;
	Settings.RecLeverancier=*u(1,1);

	sysput(8670,35,Settings.FtpUserID);
	sysput(8705,35,Settings.FtpPaswoord);
	sysput(8740,2,(char *)&Settings.RecLeverancier);
	sysput(8742,2,(char *)&Settings.LastMaand); 
	sysput(8744,2,(char *)&Settings.LastJaar); 
	if(Settings.WerkpostDisplayAlarm==0) Settings.WerkpostDisplayAlarm=1; sysput(8746,2,(char *)&Settings.WerkpostDisplayAlarm); 
	sysput(8750,10,Settings.KlantNummer);
	sysput(8760,70,Settings.FtpAdres);
	sysput(8830,2,(char *)&Settings.FtpPoort);
//	sysput(8400,50,Settings.API_key);
//	sysput(8260,60,Settings.EmailAdres);
	pLevFld=u(6,7); InqLev=Settings.RecLeverancier;
	if(fldlen(6,101) && InqLev>30000){pLevFld=u(6,101);InqLev-=30000;} // merk/producent
endsr:;
	sysget(8670,35,Settings.FtpUserID);
	sysget(8705,35,Settings.FtpPaswoord);
	sysget(8740,2,(char *)&Settings.RecLeverancier);
	sysget(8742,2,(char *)&Settings.LastMaand); 
	sysget(8744,2,(char *)&Settings.LastJaar); 
	sysget(8746,2,(char *)&Settings.WerkpostDisplayAlarm); 
	sysget(8750,10,Settings.KlantNummer);
	sysget(8760,70,Settings.FtpAdres);
	sysget(8830,2,(char *)&Settings.FtpPoort);
//	sysget(8400,50,Settings.API_key);
	pLevFld=u(6,7); InqLev=Settings.RecLeverancier;
	if(fldlen(6,101) && InqLev>30000){pLevFld=u(6,101);InqLev-=30000;} // merk/producent
}


static void AdjustPOCHorecaTyp(void)
{
	int16 key,z,start_;
	char SearchField[200];
  char FullRecDens[3000],sel_prijstype_='\0',sel_soortklant_='\0',sel_export_='\0';
  int k,FullRecDensLen=0,check_actief_,fkey_=2;

	memset(SearchField,0,sizeof SearchField);  
	fasinit(2);
	FOREVER{
		redo:;
		scrnum=0;scrget(3,10);z=1;
		scrifld(z++,VarTextFmt(40,1),SearchField);
		scrifld(z++,fm_us1_U,&sel_prijstype_);
		if(fldlen(2,54)) scrifld(z++,fm_us1_U,&sel_soortklant_); else z++;
		if(fldlen(2,135)) scrifld(z++,fm_uJN,&sel_export_); else z++;
		key=scrupd(1,0x81);
	  if(key==101) break;
		scrget(1,6);scrupd(-3,0);
		memset(TbKlant,0,sizeof TbKlant); MaxKlt=0;
		GetSearchKeyWords(SearchField);
		fasinit(2);   selp_use=NO;
		if(SearchField[0]=='\0') {
      if(selp_ask()) goto endsr;
		}
		FOREVER {
			nextklt:;
			if(faskeyi(2,2,2)) break;
			if(sel_prijstype_ && *s(2,26)!=sel_prijstype_) goto nextklt;
			if(sel_soortklant_ && *s(2,54)!=sel_soortklant_) goto nextklt;
			if(sel_export_ && !(sel_export_=='N' && *s(2,135)=='\0') && *s(2,135)!=sel_export_) goto nextklt;
			if(selp_tst()==NO) goto nextklt;
			FullRecDensLen=MakeFullRecDens(2,FullRecDens);
			if (AllKeywordsFound(FullRecDens,FullRecDensLen)==NO) goto nextklt;
			if(fldlen(16,1)){ // minstens laatste jaar afgenomen hebben
				fasinit(16);*l(16,12)=*u(2,1); *u(16,3)=*u(25,2)-600;  // op leveringsklant
				if(faskeyi(16,22,1)) goto nextklt;
				if(*l(16,12)!=*u(2,1)) goto nextklt;
			}
			else if(ViaStatistiek && fldlen(60,1)){
				fasinit(60);*l(60,2)=*u(2,1);
				if(faskeyi(60,2,1)) goto nextklt;
				if(*l(60,2)!=*u(2,1)) goto nextklt;
			}

			TbKlant[MaxKlt].RecordNr=*u(2,1);// record voldoet
			TbKlant[MaxKlt].Bcode=*s(2,135); 
			MaxKlt++;
			if(MaxKlt>=DIM_KLANT) break; // tabel vol
		}
		if(MaxKlt==0) {errnum=39;goto redo;}
		start_=0;
		FOREVER{  // .used wil hier zeggen geblokkeerd!
			scrnum=0;scrget(3,11);z=1;
			start_++;scrifld(z++,fm_ou4,&start_);start_--; scrifld(z++,fm_ou4,&MaxKlt);
			scraddpicto(5,0,76,22,4,2,593,0,0,"Blokkeer allen op dit scherm");
		  scraddpicto(6,0,72,22,4,2,578,0,0,"Deblokkeer allen op dit scherm");
			for(k=start_;k<start_+20;k++){
				if(k>=MaxKlt) break;
				fasinit(2);*u(2,1)=TbKlant[k].RecordNr; fasgeti(2);
				DisplayLine(z++);
				if(TbKlant[k].Bcode!='N' && TbKlant[k].Bcode!='\0') {scraddpicto(10+k-start_,0,77,2+k-start_,2,1,593,0,0,"Blokkeer");}
				else {scraddpicto(10+k-start_,0,1,2+k-start_,2,1,578,0,0,"Deblokkeer");}
				//if(TbKlant[k].Bcode!='V') {scraddpicto(30+k-start_,0,3,2+k-start_,2,1,610,0,0,"Verplicht CocaCola");}
				//else {scraddpicto(30+k-start_,0,1,2+k-start_,2,1,578,0,0,"Deblokkeer");}
				if(TbKlant[k].Bcode=='N' || TbKlant[k].Bcode=='\0') scrchat(z-1,0xB);
				else if(TbKlant[k].Bcode=='V') scrchat(z-1,0x9);
				else scrchat(z-1,0xFF);
			}
			key=scrupd(-1,0x07);
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key>=5010 && key<5050){
			  if(key>=5010 && key<5030){ // blokkeer / deblokkeer
				  k=start_+key-5010;
					if(TbKlant[k].Bcode=='N' || TbKlant[k].Bcode=='\0') TbKlant[k].Bcode='J'; else TbKlant[k].Bcode='N';
				}
			 // else if(key>=5030 && key<5050){ // verplicht Haacht
				//  k=start_+key-5030;
				//	if(TbKlant[k].Bcode=='V') TbKlant[k].Bcode='J'; else TbKlant[k].Bcode='V';
				//}
				fasinit(2);*u(2,1)=TbKlant[k].RecordNr;fasgeti(2);
				*s(2,135)=TbKlant[k].Bcode; fasupd(2);
			}
      if(key==5005 || key==5006){
				for(k=start_;k<start_+20;k++){
					if(k>=MaxKlt) break;
					if(key==5005) TbKlant[k].Bcode='N';
					else{
						if(TbKlant[k].Bcode!='V') TbKlant[k].Bcode='J';
					}
					fasinit(2);*u(2,1)=TbKlant[k].RecordNr;fasgeti(2);
					*s(2,135)=TbKlant[k].Bcode;	fasupd(2);
				}
			}
			if(key==101) break;
			if(key==102) start_-=20;
			if(key==103) {start_+=20; if(start_>=MaxKlt) start_-=20;}
			if(start_<0) start_=0;
		}
	}
endsr:;
}

static int copy0cijfers(char *ps,char *pd,int max_len_)
{
  int fuval=0;
			
  while(*ps && max_len_--){
		if(*ps>='0' && *ps<='9'){*pd++=*ps++; fuval++;}
		else ps++; // geen cijfer
  }
  *pd='\0';
  return fuval;
}

static void dsp_working(void)
{
  rec_working++;
  if((rec_working%1000)==0){
    if(kdsp_off==-1){if((kdsp%10)!=9) disp_str[kdsp]=' ';}
    else {if((kdsp%10)==9) disp_str[kdsp]='|'; else disp_str[kdsp]='*';}
    scrifld(22,fm_os63,disp_str);
    kdsp+=kdsp_off;
    if(kdsp>=50){kdsp--;kdsp_off=-1;}
    else if(kdsp<0) {kdsp=0;kdsp_off=1;}
		scrupd(-3,0);
  }
}


static void DisplayLine(int16 z)
{
  char *pd,buf1_[20],buf_[121];
  int16 g,len2,len3;
  long lbd_;
	CString cstr_;
	  
	len2=fldlen(2,2); len3=fldlen(2,3);
  zero(buf_,sizeof buf_);  pd=&buf_[0];

	if(len2==0){stcli_d(pd,(long)(*u(2,1)),5,1);pd+=5;}
	else copy(s(2,2),pd,len2);
	for(g=0;g<len2;g++){if(*pd=='\0') *pd=' ';pd++;}
  *pd++=' ';	
	cstr_=CString(s(2,3),len3).Trim();	g=copy0((char *)(LPCTSTR)cstr_,pd,cstr_.GetLength());	pd+=g;
	if(g>=30) *(pd++)='-';
	else{
  	for(g;g<30;g++){if(*pd=='\0') *pd=' ';pd++;}
	}
	cstr_=CString(s(2,4),fldlen(2,4)).Trim();	g=copy0((char *)(LPCTSTR)cstr_,pd,cstr_.GetLength());	pd+=g;
	*(pd++)='-';
	cstr_=CString(s(2,6),fldlen(2,6)).Trim();	g=copy0((char *)(LPCTSTR)cstr_,pd,cstr_.GetLength());	pd+=g;
  scrifld(z,VarTextFmt(72,0),buf_);
}

static void GetSearchKeyWords( char *s)
{
  int i, len, keyix;
  char buf[100];

  for (i=0; i<MAX_SEARCH_KEYWORDS; i++) SearchKeywords[i][0]=0; 
  keyix=0;
  while (keyix<MAX_SEARCH_KEYWORDS) {
    while (*s==' ') s++;
    len=0;
    while (*s && *s!=' ') {
      if (len>=sizeof(buf)) return;
      buf[len++]=*s++;
    }
    buf[len++]=0;
    if (len>0) GetSearchText(buf,SearchKeywords[keyix++],len); // om de 0 achteraan toe te voegen !
    if (!*s) break;
  }
}
  
static int GetSearchText(char *s,char *d,int len)  // analoog aan JMS (composekey)
{
  char c;
  int l=len, outlen=0;

  while (l-->0) {
    if (!*s) break;
	  c=ICSBTab[*(unsigned char *)s++];
  	if (c) {
      *d++=c;
      outlen++;
    }
	}
  if (outlen<len) *d=0;
  return outlen;
}

static int MakeFullRecDens(int stunr, char *FullRecDens)
{
  unsigned char Desc[100]; // zeker genoeg nemen,
  unsigned char *p=0;
	char  *d,buf750[750];
  int tbnr_,snr_,len, outlen=0, lenadd,fldnr;
	int sfldnrs[15]={1,2,3,4,5,6,7,8,9,10,21,22,68,69,0};   // klant
  d=FullRecDens;

 for (snr_=0; snr_<15; snr_++) {
		fldnr=sfldnrs[snr_];
		if(fldnr==0) continue;
		if(fldnr==1 && fldlen(stunr,2)) continue; // indien code, dan geen recordnummer
    len=fieldspc(stunr,fldnr,&p,Desc);
    if (len==0) continue;
		len=Fld2String(stunr,fldnr,buf750,500);
 		lenadd=GetSearchText(buf750,d,len);
    if (lenadd>0) {
      d+=lenadd;
      *d++=0;
      outlen+=(lenadd+1);
    }
  }
  *d++=0;
  return outlen;
}

static int AllKeywordsFound(char *FullRecDens, int FullRecDensLen)
{
  int i, j, k, KeyWordLen;
  
  for (i=0; i<MAX_SEARCH_KEYWORDS; i++) {
    KeyWordLen=strlen(SearchKeywords[i]);
    if (KeyWordLen==0) continue;
    if (FullRecDensLen<KeyWordLen) return NO;

    for (j=0; j<FullRecDensLen-KeyWordLen; j++) {
      for (k=0; k<KeyWordLen; k++) {
        if (SearchKeywords[i][k]!=FullRecDens[j+k]) break;
      }
      if (k>=KeyWordLen) break;
    }
    if (j>=FullRecDensLen-KeyWordLen) return NO;
  }
  return YES;
}

// SEQO-routines
static void seqo_fld(int16 stu_,int16 fld_)
{
  if(fldlen(stu_,fld_)){
    fmt_get(stu_,fld_);
    seqo_var(fmt,s(stu_,fld_));
  }
}

static void seqo_var(char *fm_,char *pvar_)
{
  int16 yy,mm,dd,len_;
  float fbd_;
  char str_[20];
 
  if(fm_[1]==0xC8 || fm_[1]==0x88){/* string */
    len_=fm_[2];
    char2str(pvar_,len_);
  }
  else if(fm_[1]==0xD0 || fm_[1]==0x90){/* uint16 */
    fbd_=*(uint16 *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xD1 || fm_[1]==0x91){/* integer */
    fbd_=*(int16 *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xD3 || fm_[1]==0x93){/* long */
    fbd_=*(long *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xD4 || fm_[1]==0x94){/* float */
    fbd_=*(float *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xD5 || fm_[1]==0x95){/* double */
    fbd_=*(double *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xC0 || fm_[1]==0x80){/* date */
    if(*(uint16 *)pvar_==0) seqo_str[pos++]=DelimKar;
    else{
      jddate(*(uint16 *)pvar_,&yy,&mm,&dd);
      stcli_d(str_,(long)dd,2,0);str_[2]='/';
      stcli_d(&str_[3],(long)mm,2,0);str_[5]='/';
      stcli_d(&str_[6],(long)yy,4,0);
      char2str(str_,10);
    }
  }
  else if(fm_[1]==0xA8 || fm_[1]==0xE8){/* grb */
    zero(str_,sizeof str_);
    grb_deco(str_,(long *)pvar_);
    char2str(str_,10);
  }
	else if(fm_[1]==0x98 || fm_[1]==0xD8){// btw
		zero(str_,sizeof str_);
		if(*(long *)pvar_){
			copy("BE-",str_,3);btw_deco(&str_[3],(long *)pvar_,1);
			if(str_[12]=='\0'){copy("BE-0",str_,4);btw_deco(&str_[4],(long *)pvar_,1);}
		}
		char2str(str_,15);
	}
  endsr:;
}
 
static void char2str(char *ps_,int16 len_)
{
  int16 k,orig_pos_;
 
  orig_pos_=pos;
  if(len_){
    copy(ps_,&seqo_str[pos],len_);while(seqo_str[pos]) pos++;
    for(k=orig_pos_;k<pos;k++){
      if(seqo_str[k]==DelimKar) seqo_str[k]='.';// delete | 
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;// delete trailing blanks 
    pos++;
  }
  seqo_str[pos++]=DelimKar;
}

static void flt2str(float bd_)
{
  int16 k,dlen_;
  char buff[15];
  double bedrag_,add_=0,dfactor_;
  long val_,value;
							
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  dfactor_=10000.;dlen_=4; if(bedrag_<-10000 || bedrag_>10000){dfactor_=100.;dlen_=2;}
  val_=bedrag_*dfactor_+add_;value=val_/dfactor_;
 
  zero(buff,sizeof buff);
  stcli_d(&buff[0],value,10,1);
  for(k=0;k<10;k++){
    if(buff[k]=='\0') break;
    if(buff[k]!=' ') seqo_str[pos++]=buff[k];
  }
  value=val_-value*dfactor_;
  if(value){
    seqo_str[pos++]=',';
    if(value<0) value=-value;
    zero(buff,sizeof buff);
    stcli_d(&buff[0],value,dlen_,0);
    for(k=dlen_;k>=0;k--) if(buff[k]!='0') break;
    copy(&buff[0],&seqo_str[pos],k+1);pos+=k+1;
  }
}
 

static void seqo_dumpline(int16 add_eor_)
{
	int k;
	  
  CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
	if(add_eor_){seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;}
  seqo_len=0;
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
    if(seqo_len){
      fasseqo(80,seqo_mode,seqo_len+4);
      seqo_pos+=seqo_len;
      *l(80,1)=seqo_pos;
      seqo_len=0;
		}
  }
	zero(seqo_str,sizeof seqo_str);pos=0;
}
/////
 

static void seqo_flush(void)
{
  if(seqo_len){
    *l(80,1)=seqo_pos;
    fasseqo(80,seqo_mode,seqo_len+4);
    seqo_pos+=seqo_len;
    seqo_len=0;
  }
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


//

static void InitConvertTab(void)  // komt uit JMS
{
  int i;

	for (i=0; i<256; i++) {
		ICSBTab[i]=i;
	}
  ICSBTab[128]='A';
  ICSBTab[129]='A';
  ICSBTab[130]='A';
  ICSBTab[131]='A';
  ICSBTab[132]='C';
  ICSBTab[133]='E';
  ICSBTab[134]='E';
  ICSBTab[135]='E';
  ICSBTab[136]='E';
  ICSBTab[137]='I';
  ICSBTab[138]='I';
  ICSBTab[139]='I';
  ICSBTab[140]='I';
  ICSBTab[141]='O';
  ICSBTab[142]='O';
  ICSBTab[143]='O';
  ICSBTab[144]='O';
  ICSBTab[145]='U';
  ICSBTab[146]='U';
  ICSBTab[147]='U';
  ICSBTab[148]='U';
  ICSBTab[149]='U';
  ICSBTab[159]='E'; // euro teken

  for (i='a'; i<='z'; i++) {
		ICSBTab[i]=i-'a'+'A';
	}

	for (i=' '; i<'0'; i++) ICSBTab[i]=0;
	for (i='9'+1; i<'A'; i++) ICSBTab[i]=0;
	for (i='Z'+1; i<'a'; i++) ICSBTab[i]=0;
	for (i='z'+1; i<128; i++) ICSBTab[i]=0;
  for (i=150; i<255; i++) ICSBTab[i]=0;
}

static void LijstVerplichteKlanten(void)
{
  int16 k,z,key,bold_;
	int16 form_dat[8],pr_mode,prtnr;
  char inq_type_='J',*ptitel_;

	//FOREVER{
	//	redo:;
	//	scrnum=0; scrget(3,8);z=1;
	//	scrifld(z++,fm_uJN,&inq_type_); 
	//	key=scrupd(1,0x2C1);
	//  if(key==101) goto endsr;
	//	if(inq_type_!='J' && inq_type_!='V') {errnum=34; goto redo;}
	//	if(key==108) break;
	//}
	if(inq_type_=='J') ptitel_="Lijst te exporteren klanten"; else ptitel_="Lijst verplichte klanten";
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  prtfld(25,1,-1);prttext("<t33b>");prttext(ptitel_);  prttext("<b>");  prttext("<t122>Blz.<ppp>.");
  prtbuf(1);z=1;
  prttab(z,2,1+klcd,1,-1); prttitle(z++,"Code",3);
  prttab(z,2,3,1,-1); prttitle(z++,"Naam",3);
  prttab(z,2,4,1,-1); prttitle(z++,"Straat",3);
  prttab(z,2,5,1,-1); prttitle(z++,"Postnr.",3);
  prttab(z,2,6,1,-1); prttitle(z++,"Gemeente",3);
  prtbuf(3);
	p_pdfname(ptitel_,*u(25,2),0);
	fasinit(2);
	FOREVER{
		if(faskeyi(2,2,2)) break;
		if(*s(2,135)==inq_type_ || (inq_type_=='J' && *s(2,135)=='V')){
			bold_=0; // if(*s(2,135)=='V') bold_=2;
			for(k=1;k<10;k++) prtinfo(k,bold_);prtline();
		}
	}
	prtform(0);prtclose();
	endsr:;
}




static CString SearchString;
  
static bool CheckKeyWord(char *keyword)
{
	int k;
	char kar_;
	  
	if((k=SearchString.Find(keyword))>0){
		kar_=SearchString.GetAt(k-1);
		if(keyword[0]>='0' && keyword[0]<='9' && ((kar_>='0' && kar_<='9') || kar_==',' || kar_=='.' || kar_=='+')){
			return false;
		} 
		else return true;
	}
	return false;
}

static void InitLoad(void)
{
	int16 j,mm,dd;
	 
	sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);
  sysget(2212,4,talen);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
	sysget(3876,2,&sys3876);
	sysget(3896,6,sys3896);
  sysget(3974,2,&ft_off);
  sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4254,40,(char *)&dt_kvk[0]);
  sysget(4294,40,(char *)&loc_klt[0]);
  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);

	sysget(8670,35,Settings.FtpUserID);
	sysget(8705,35,Settings.FtpPaswoord);
	sysget(8740,2,(char *)&Settings.RecLeverancier);
	sysget(8742,2,(char *)&Settings.LastMaand); 
	sysget(8744,2,(char *)&Settings.LastJaar); 
	sysget(8746,2,(char *)&Settings.WerkpostDisplayAlarm); if(Settings.WerkpostDisplayAlarm==0) Settings.WerkpostDisplayAlarm=1; 
	sysget(8750,10,Settings.KlantNummer);
	sysget(8760,70,Settings.FtpAdres);
	sysget(8830,2,(char *)&Settings.FtpPoort);
//	sysget(8400,50,Settings.API_key);
	if(Settings.RecLeverancier==0){
		sysget(2976,2,(char *)&Settings.RecLeverancier);
		sysput(8740,2,(char *)&Settings.RecLeverancier);
	}
	pLevFld=u(6,7); InqLev=Settings.RecLeverancier;
	if(fldlen(6,101) && InqLev>30000){pLevFld=u(6,101);InqLev-=30000;} // merk/producent

	if(ft_off && fldlen(91,11+(ft_off*5))==0) ft_off=0;
	j=0;
  for(max_kassa=0;max_kassa<10;max_kassa++){
    if(fldlen(91,11+(max_kassa*5))==0) break;
    if(fldlen(91,11+((max_kassa+ft_off)*5))==0) break;
		if(nm_kassa[max_kassa][0]) j++;
  }
	if(ft_off && max_kassa>ft_off) max_kassa=ft_off; // veiligheid voor ft_offset
	if(j<1) max_kassa=1; // meer velden, maar geen naam ingevuld



	jddate(*u(25,2),&ThisYear,&mm,&dd);
	klcd=0;if(fldlen(2,2)) klcd=1;
	InitConvertTab();
}

static int CopyOnlyChar(char *ps, char *pd, int16 len_)
{
  int k,fuval=0;

	zero(pd,len_);
	for(k=0;k<len_;k++){
		if(*ps=='\0') break;
		if(*ps!=' '){*pd++=*ps;fuval++;}
		ps++;
	}
  return fuval;
}

static CString Cstring2CSV(CString string_fld_)
{
	CString cstr_,ret_string_;

	
	cstr_=string_fld_;cstr_.TrimLeft();cstr_.TrimRight();
	cstr_.Replace("\"","\"\"");
	ret_string_=CString("\"");
  ret_string_+=cstr_;
	ret_string_+="\"";

	return ret_string_;
}





// STANDAARD routines


static double Round(double getal, double round)
{
  long lbd_;
                                
  if (round==0) round=0.0001; // om vieze dinges ver na komma weg te doen 
  if (getal<0.) getal-=(round/2.);
  else getal+=(round/2.);
  getal/=round;
  lbd_=(long)getal;
  return (double) (lbd_*round);
}



static bool FasFileOpen(int16 nr_)
{
  int16 stu_,k;
  char filename[15];
							
  k=300+17*(nr_-1);
  sysget(k,15,filename);
  sysget(k+15,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(fasopen(filename,0)) return false;
		else return true;
	}
  return false;
}
 
static int cmpstrU(char *p1, char *p2, int16 len)
{
  char b1,b2;
					
  while(len--){
    b1=*p1++;b2=*p2++;
    if(b1>='a' && b1<='z') b1=b1-'a'+'A';
    if(b2>='a' && b2<='z') b2=b2-'a'+'A';
    if(b1!=b2)return 1;
  }
  return 0;
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}

static void p_pdfname(char *naam_,uint16 dt_beg_,uint16 dt_end_)
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


//////// SIF-file inleesroutines /////////////////////////////

static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_)
{
  int len_;

  if(cstr_.GetLength()) len_=cstr2arr(cstr_,pbuf_,maxlen_);
  else len_=0;
  if(len_>=maxlen_) len_--; pbuf_[len_]='\0'; 

  return pbuf_;
}

static CString Double2String(double getal,long mode)  // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
{                                      // . is decimal karakter !
  int k;
  CString fuval,S;
  double afrond_;

	if(mode<0) afrond_=0;
	else{
		afrond_=1.;
		for(k=0;k<mode;k++) afrond_/=10.;
	}
	getal=Round(getal,afrond_);


  if(mode<0){
    fuval.Format(TEXT("%lf"),getal);
    if(fuval.Find(TEXT("."))>=0){
      while(1){
        if(fuval.Right(1)=="0") fuval=fuval.Left(fuval.GetLength()-1);
        else break;
      }
      if(fuval.Right(1)==".") fuval=fuval.Left(fuval.GetLength()-1);
    }
  }
  else{
    S="%8."+CString((char)('0'+mode))+"lf";
    fuval.Format(S,getal);
  }
  fuval.TrimLeft();
//  fuval.Replace('.',',');
  return fuval;
}
  

static double String2Getal(CString S,char decim_kar)
{
  unsigned short byte;
  bool negative=false,decim=false;
  double fuval=0,coef=1.;

  while(1){
    if(S.GetLength()<=0) break;
    byte=S.GetAt(0);
    S=S.Mid(1);
    if(byte==' ');
    else if(byte=='-') negative=true;
    else if(byte>='0' && byte<='9'){
      if(decim){
        coef=coef/(float)10.;
        fuval+=(byte-'0')*coef;
      }
      else fuval=fuval*10+byte-'0';
    }
    else if(byte==decim_kar) decim=true;
    else if(byte=='.' || byte==','); // skip
    else break;
  }
  if(negative) fuval=-fuval;
  return fuval;
}

static CString Date2String(unsigned int date_,int mode_)
{
   char txtbuffer_[100];

   zeros(txtbuffer_,sizeof txtbuffer_);
   if(date_) datefm(txtbuffer_,date_,mode_);

   return CString(txtbuffer_);
}

static CString Read_Rec(int f_nr_)

{
  int k,len_;
  char buf_[4100];
  CString fuval="";
  long pos_;   

  ReadEOFline=false;
  pos_ = dseek(f_nr_,0L,1);
	if (pos_<0) {ReadEOFline=true;goto endsr;}
    
  len_=dread(f_nr_, buf_, 4096);
  if(len_==0) {ReadEOFline=true;goto endsr;}
  for(k=0;k<len_;k++){
    if(buf_[k]==0x0d || buf_[k]==0x00) break;
  }
  if(k<len_) {
    buf_[k]='\0';pos_+=k+2;
    pos_=dseek(f_nr_,(long)pos_,0);
		CnvJamaChar(buf_,k,1);
    fuval=CString(buf_);
  }
  else fuval=CString(buf_,len_);
  endsr:;
  return fuval;
}


static CString Rec_Ele(CString s, int kol_, int maxlen_, char delim_kar_)
{
  CString fuval="";
  int len_,pos_;
    
  while(kol_>0){
    if((len_=s.GetLength())==0) break;
    if((pos_=s.Find(delim_kar_))<0) break;
    s=s.Right(len_-pos_-1);
    kol_--;
  }
  if(kol_==0 && (len_=s.GetLength())>0){
    if((pos_=s.Find(delim_kar_))>=0) s=s.Left(pos_);
    fuval=s;
  }
  fuval.TrimLeft();fuval.TrimRight();
	fuval.TrimLeft("\"");fuval.TrimRight("\"");
	fuval.Replace("\"\"","\"");
	if(maxlen_>0 && fuval.GetLength()>maxlen_) fuval.Left(maxlen_);
  return fuval;
}


static CString Fld2CString(int stu_,int fld_)
{
  int len, i;
  unsigned char Desc[100]; // zeker genoeg nemen,
  unsigned char b[300];
  unsigned char *p=0;
  CString result_;


  result_=CString("");memset(b,0,sizeof b);
	len=fieldspc(stu_,fld_,&p,Desc);
  if (len==0) goto endsr;
  if ((Desc[1]&0xC0)==0) goto endsr;
  switch (Desc[1]&0x38) {
    case 0x10: // getal
      frmtnum((char *)b,Desc[1],d(stu_,fld_),Desc[2],Desc[3],*(UNALIGNED short int *)&Desc[4]);
      len=strlen((char *)b);
      while (len>0) {
        if (b[len-1]>' ') break;
        b[len-1]=0;
        len--;
      }
      for (i=0; i<strlen((char *)b); i++) if (b[i]>' ') break;
      break;
    case 0x08:  // string
      len=fldlen(stu_,fld_);
      memcpy(b,s(stu_,fld_),len);
      b[len]=0; // om zeker een 0 achter te zetten
 /*     p=b;
      for (i=0; i<len; i++) {
        if (b[i]>=' ' && b[i]<0x80) *p++=b[i];
        else if (b[i]>=0x80 && b[i]<0xD0) {
          *p++=jamasci[b[i]-0x80][0];
          if (jamasci[b[i]-0x80][1]>0) p--;
        }
      }
      *p=0;*/
      break;
    case 0x18: // BTw-nummer
      btw_deco((char *)b,(long*)p,YES);
      break;
		case 0x00: // date
		  if(*u(stu_,fld_)) datefm((char *)b,*u(stu_,fld_),3);
			break;
		case 0x20: // grb 
			if(*l(stu_,fld_)) grb_deco(b,l(stu_,fld_));
		  break;
		case 0x28: // rekening 
			rek_deco((char *)b,(unsigned char *)s(stu_,fld_),1);
		  break;
  }
len=sizeof b;
	CnvJamaChar((char *)b,sizeof b,0);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
	result_=CString(b); result_.TrimLeft();
endsr:;
	return result_;
}


///////////////////////////////////////////////////

static void MailDocument(int SendMode)
{
  int j,k,pos_,p_adr_=0;
	CString cstr_;
	  
		// keywords invullen 
	zero(MailMergeData[0],sizeof MailMergeData);MailSaveAdres='N';

	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy(s(1,3),MailMergeData[k],25); continue;}
		if(cmpstr(MailMergeKeywords[k],"CONTACTPERSOON",14)==0){copy(s(25,1),MailMergeData[k],fldlen(25,1)); continue;}
		if(cmpstr(MailMergeKeywords[k],"KLANTID",7)==0){copy(Settings.KlantNummer,MailMergeData[k],10); continue;}
		if(cmpstr(MailMergeKeywords[k],"PERIODE",7)==0){sprintf_s(MailMergeData[k],50,"%02d-%02d/%04d",InqMaandBeg,InqMaandEnd,InqJaar);continue;}
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){p_adr_=k;copy(Settings.EmailAdres,MailMergeData[k],60); continue;}
	}
	for(j=4;j>=0;j--) if(MailBodyText[j][0]) break;
	zero(MailMergeBodyText,sizeof MailMergeBodyText);pos_=0;
	if(j>=0){
		for(k=0;k<=j;k++) {
			pos_+=copy0(MailBodyText[k],&MailMergeBodyText[pos_],75);
			if(k<j) MailMergeBodyText[pos_++]=' '; // '\n';
		}
	}
	if(SpoolFileNr!=9999){ // anders bij call de juiste bijlage invullen
  	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);MailMergeBijlage[0]=SpoolFileNr;
	  zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage);
	}
	zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate);
	copy("DATAG",MailMergeSpecialTemplate,5); // vaste template 

	MailMergeFormaat=5; 
	k=SendMail(SendMode); 
	//if(k && MailSaveAdres=='J'){
	//	copy0(MailMergeData[p_adr_],(char *)&Settings.EmailAdres,60); // email adres bewaren
	//  sysput(8260,60,(char *)&Settings.EmailAdres);
 // }
}


static int16 ExecSearch(int16 mode_)
{
  int16 byte,mode6_,stu=6;
  char zoek_arg[51],*pzoek;
	int16 zoekkey,zoekwijze,zoeklen,filtermode_=NO;;
  long last_rec_;
	int16 len2,len3;
  uint16 *pu_s_1;
  char *ps_s_2,*ps_s_3;
	char zoekstr[100];
	CString cstr_;

  scrget(1,7);scrupd(-3,0);
	ps_s_2=s(stu,2);ps_s_3=s(stu,3);pu_s_1=u(stu,1);
  len3=fldlen(stu,3);
  len2=fldlen(stu,2);//if(len2 && faskeyi(stu,1,0)==45) len2=0; // indien geen key, dan ook geen code 
  
	if(*s(stu,3)=='\0'){errnum=38;goto end;}
  zero((char *)&recs[0],sizeof recs);zero((char *)&recs_preferred[0],sizeof recs_preferred);recs_used=0;
	
	if(mode_==98){
		zero(zoekstr,sizeof zoekstr);copy0(s(6,3),zoekstr,fldlen(6,3));
		cstr_=CString(zoekstr);cstr_.Trim();cstr_.MakeUpper();
		zoeklen=cstr_.GetLength();zero(zoekstr,sizeof zoekstr);copy((char *)(LPCTSTR)cstr_,zoekstr,zoeklen);
		fasinit(6);mode6_=1;
		FOREVER{
			if(faskeyi(6,2,mode6_)) break; mode6_=2;
			cstr_=CString(s(6,3),fldlen(6,3));cstr_.MakeUpper();
			if(cstr_.Find(_T(zoekstr),0)>=0) {recs[recs_used++]=*u(6,1);}
			if(recs_used>=MAX_RECS) break;
		}
		goto end;
	}

  copy(ps_s_3,zoek_arg,len3);zoek_arg[len3]='\0';
  zoekkey=2;zoekwijze=0;  // gewoon op naam zoeken als default nemen
  zoeklen=Copy2ZoekStr(&zoek_arg[0],zoekstr,len3,len3);pzoek=ps_s_3;
  byte=zoek_arg[0];
  if(filtermode_==NO && byte=='\0') {errnum=38;goto end;}
  if(byte=='.'){//  zoek op codenummer 
		if(len2 && zoek_arg[1]=='.'){ // .. is zoeken op stuk codenummer 
			zoekwijze=1; zoekkey=1;
			zoeklen=Copy2ZoekStr(&zoek_arg[2],zoekstr,len3-2,len2);
			fasinit(stu);pzoek=ps_s_2;
			goto fill_tabel;
		}
    if(len2==0) byte='?';
    else {mode_=2;copy(&zoek_arg[1],ps_s_2,len2);}
  }
  if(byte=='?'){ // zoek op recordnummer 
    *pu_s_1=val(&zoek_arg[1]);mode_=1;
  }
  if(byte>='0' && byte<='9'){ // codenummer
		mode_=2;
    if(stu==3) grb_comp(&zoek_arg[0],ps_s_2);
    else{
			if(len2 && stu!=92) {copy(&zoek_arg[0],ps_s_2,len2);}
			else{
				if(stu!=6 || (sys3876&0x01) ){*pu_s_1=val(&zoek_arg[0]);mode_=1;}
				else mode_=3;
			}
    }
  }
  zoekkey=2;zoekwijze=0;  // gewoon op naam zoeken als default nemen
  zoeklen=Copy2ZoekStr(&zoek_arg[0],zoekstr,len3,len3);pzoek=ps_s_3;

  if(mode_==1){
		errnum=fasgeti(stu);
		if(errnum) errnum=39; 
		else recs[recs_used++]=*pu_s_1;
		goto end;
	}// op record
  if(mode_==2){
		if(stu==6 && (sys3876&2)){// zoek op stuk van artikelcode 
			zoekkey=1; zoekwijze=1;  // artikelreferentie met directe key
			zoeklen=Copy2ZoekStr(s(6,2),zoekstr,len2,len2); pzoek=s(6,2);
			goto fill_tabel;
		}
		else{
			errnum=faskeyi(stu,1,0);
		  if(errnum) errnum=39; 
		  else recs[recs_used++]=*pu_s_1;
			goto end;// direct zoeken 
		}
  }   
  // speciale zoekmethodes definieren 
	

fill_tabel:;
  mode_=1;if(!(filtermode_ && *pzoek==0) && (zoekwijze==0 || zoekwijze==4)) mode_=5;last_rec_=*u(stu,1);
  FOREVER{
next:;
		if(recs_used>=MAX_RECS) break;
		if(mode_==5){
			fasinit(stu);*u(stu,1)=last_rec_;
		  copy(zoekstr,pzoek,len3);
		  if(faskeyi(stu,zoekkey,5)) break;	
		}
		else{
			if(faskeyi(stu,zoekkey,mode_)) break; mode_=2;
		}
		last_rec_=*u(stu,1);
		if((stu==2 || stu==6) && (parmcall[7] & 0x08) && fldlen(stu,200) && *u(stu,200)) goto next;// check op NIET actief
		switch(zoekwijze){
			case 1 : if(cmpstrU(pzoek,zoekstr,zoeklen)==0){recs[recs_used++]=*pu_s_1;}// stuk codenummer 
					     else goto next; //end_fill_tabel;
						   break;
      default : recs[recs_used++]=*pu_s_1; break;
		}
  }
end:;
  if(recs_used==0){errnum=39;return 1;}
	return 0;
}

static int16 Copy2ZoekStr(char *ps3_,char *zoekstr,uint16 len3_,uint16 lenz_)
{
  uint16 k;
  for(k=0;k<len3_ && k<lenz_;k++){
	if(*(ps3_+k)=='\0') break;
	zoekstr[k]=*(ps3_+k);
  }
  zoekstr[k]='\0';
  return k;
}


static int selp_ask(void)
{
  int16 key;
  char choice;

  if(selp_stu!=stu) selp_wis();
  selp_stu=stu;


  FOREVER{
    scrget(1,46);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(1,0x0581);
    if(key==101) return YES;
    if(key==111) ovlexit(-1);
    if(key==108) {selp_use=YES;break;}
    if(key==109) {selp_use=NO;break;}
    switch(choice){
      case '1': selp_ge=NO;selp_upd(0,choice);break;
      case '2': selp_ge=YES;selp_upd(0,choice);break;
      case '3': selp_le=NO;selp_upd(1,choice);break;
      case '4': selp_le=YES;selp_upd(1,choice);break;
      case '5': selp_upd(2,choice);break;
      case '6': selp_upd(3,choice);break;
      case '7': selp_wis();scrget(1,7);scrupd(-3,0);break;
      default : errnum=34; break;
    }
  }
  return NO;
}

static void taal_upd(int16 z,int16 fld_)
{
  if(fldlen(stu,fld_)!=1) scrfld(z,stu,fld_);
  else{
    if(taal_i=='\0' && *s(stu,fld_)!=0xFE){
      if(*s(stu,fld_)>=4) *s(stu,fld_)=0;
      taal_i=talen[*s(stu,fld_)];
    }
    scrifld(z,fm_us1_U,&taal_i);
  }
}

static int taal_chk(int16 fld_)
{
  int16 k;
									
  if(fldlen(stu,fld_)==1){
    for(k=0;k<4;k++) if(taal_i==talen[k]) {*s(stu,fld_)=k;break;}
    if(k==4 && taal_i!='\0') {errnum=34;return YES;}
  }
  return NO;
}

static void selp_upd(int16 bfnr,char men_keuze)
{
  int16 k,curs,z,curs_taal,key;
 
  men_keuze=men_keuze-'1'; taal_i='\0';
  copy(selp_bf[bfnr],s(stu,1),fldlen(stu,0));
  if(stu==1){/* leveranciers */
    curs=2;
    redo_l:;
    scrget(2,6); z=1;
    scrinq(0);
    z=1;
    scrifld(z++,fm_os20,selp_txt[men_keuze]);
    if(fldlen(stu,2)) scrfld(z++,stu,2); else scrofld(z++,stu,1,-1);
		if(bfnr==2){
			if(fldlen(stu,200)){
				if(*u(stu,200)==1){
					scrchat(z-1,0xB); 
					scraddpicto(7,z-1,0,0,2,1,70,0,3,"Maak actief");
				}
				else{
					scrchat(z-1,0xFF);
					if(*u(stu,200)==0) scraddpicto(7,z-1,0,0,2,1,71,0,4,"Blokkeer");
					else scraddpicto(7,z-1,0,0,2,1,71,0,0,"Blokkeer");
				}
			}
		}
    for(k=3;k<16;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,16);
    for(k=17;k<MAXFLD;k++) scrfld(z++,stu,k);
    key=scrupd(curs,0x0080);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5007 && fldlen(stu,200)){ // blokkeer
			if(*u(stu,200)==0) *u(stu,200)=1; else *u(stu,200)=0;
			goto redo_l;
		}
    if(taal_chk(16)) {curs=curs_taal;goto redo_l;}
  }

  else if(stu==2){/* klanten */
    curs=2;
    redo_k:;
    scrget(2,7);  scrinq(0);
    z=1;
    scrifld(z++,fm_os20,selp_txt[men_keuze]);
    if(klcd) scrfld(z++,stu,2); else scrofld(z++,stu,1,-1);
		if(bfnr==2){
			if(fldlen(stu,200)){
				if(*u(stu,200)==1){
					scrchat(z-1,0xB); 
					scraddpicto(7,z-1,0,0,2,1,70,0,3,"Maak actief");
				}
				else{
					scrchat(z-1,0xFF);
					if(*u(stu,200)==0) scraddpicto(7,z-1,0,0,2,1,71,0,4,"Blokkeer");
					else scraddpicto(7,z-1,0,0,2,1,71,0,0,"Blokkeer");
				}
			}
		}
    for(k=3;k<24;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,24);
    for(k=25;k<MAXFLD;k++) scrfld(z++,stu,k);
    key=scrupd(curs,0x0080);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5007 && fldlen(stu,200)){ // blokkeer
			if(*u(stu,200)==0) *u(stu,200)=1; else *u(stu,200)=0;
			goto redo_k;
		}
    if(taal_chk(24)) {curs=curs_taal;goto redo_k;}
  }
  copy(s(stu,1),selp_bf[bfnr],fldlen(stu,0));
}


static int selp_tst(void)/* 00.04 */
{
  int16 g,k,type,parm,f_len,index;
  char fldtype,*stu_base,*adres,ret;

  if(selp_use==NO) return YES;
  stu_base=s(stu,1);

  for(k=2;k<201;k++){
    f_len=fieldspc(stu,k,&selp_fld,selp_des);
    if(f_len>0){
      fldtype=(selp_des[1] & 0x38)/8;
      if((stu==2 && k==24) || (stu==1 && k==16)) fldtype=6;
      switch(fldtype){
	case 0:/* date */
	  type=1;parm=11;
	  break;
	case 1:/*string*/
	  type=2;
	  break;
	case 2:/*num*/
	  type=1;parm=selp_des[1]&7;
	  break;
	case 3:/*bt#*/
	  type=1;parm=3;
	  break;
	case 4:/* rek# */
	  type=3;parm=5;
	  break;
	case 5:/* grb */
	  type=1;parm=3;
	  break;
	case 6:
	  type=4;
	  break;
	default: type=0;break;
      }
      index=selp_fld-stu_base;
      for(g=0;g<4;g++){
	adres=&selp_bf[g][index];
	if(used(adres,f_len)){
	  ret=3;
	  switch(type){
	    case 1: ret=comp_num(adres,selp_fld,parm); break;
	    case 2: ret=comp_str(adres,selp_fld,f_len); break;
	    case 3: ret=comp_byt(adres,selp_fld,f_len); break;
	    case 4: ret=comp_taa(adres,selp_fld,f_len); break;
	  }
	  if(ret==3) goto next;
	  if(g==0 && (ret==1 || (selp_ge && ret==0))) goto next;
	  if(g==1 && (ret==2 || (selp_le && ret==0))) goto next;
	  if(g==2 && ret==0) goto next;
	  if(g==3 && ret!=0) goto next;
	  return NO;
	}
	next:;
      }
    }
  }
  return YES;
}

static int comp_taa(char *p1, char *p2, int16 len)
{
  if(*p1==*p2) return 0;
  if(*p1<*p2) return 1;
  if(*p1>*p2) return 2;
	return 0;
}

static int used(char *b,int16 len)
{
  while(len-->0)
    if(*b++!=0xFE) return YES;
  return NO;
}
 
static int comp_num(char *p1, char *p2, int16 type)
{
  int16 ret;
  short int jj,mm,dd, oldp2;
 
  if(type==11){
    oldp2=*(uint16 *)p2;
    if(*(uint16 *)p1>=44 && *(uint16 *)p1<=409){
      jddate(*(uint16 *)p2,&jj,&mm,&dd);
      *(uint16 *)p2=datejd(1892,mm,dd);
    }
  }
  switch(type){
    case 0:
      if(*(int16 *)p1 < *(int16 *)p2) ret=1;
      else if(*(int16 *)p1 > *(int16 *)p2) ret=2;
      else ret=0;
      break;
    case 1:
    case 11:
      if(*(uint16 *)p1 < *(uint16 *)p2) ret=1;
      else if(*(uint16 *)p1 > *(uint16 *)p2) ret=2;
      else ret=0;
      if(type==11) *(uint16 *)p2=oldp2;
      break;
    case 3:
      if(*(long *)p1 < *(long *)p2) ret=1;
      else if(*(long *)p1 > *(long *)p2) ret=2;
      else ret=0;
      break;
    case 4:
      if(*(float *)p1 < *(float *)p2) ret=1;
      else if(*(float *)p1 > *(float *)p2) ret=2;
      else ret=0;
      break;
    case 5:
      if(*(double *)p1 < *(double *)p2) ret=1;
      else if(*(double *)p1 > *(double *)p2) ret=2;
      else ret=0;
      break;
    default:
      ret=3;
      break;
  }
  return ret;
}
 
static int comp_str(char *p1,char *p2,int16 len)
{
  char b1,b2;
  int16 len1,len2;

  len1=len;len2=len;
  FOREVER{
    FOREVER{
      if(!(b1=*p1++)){len1=-1; break;}/* 0-byte found */
      if(!len1--) break;
      if(b1>='a' && b1<='z') b1=b1-'a'+'A';
      if((b1>='A' && b1<='Z') || (b1>='0' && b1<='9') || (b1=='?')) break;
      if(b1=='*') return 0;
    }
    FOREVER{
      if(!(b2=*p2++)){len2=-1; break;}/* 0-byte found */
      if(!len2--) break;
      if(b2>='a' && b2<='z') b2=b2-'a'+'A';
      if((b2>='A' && b2<='Z') || (b2>='0' && b2<='9')) break;
    }
    if(len1<0 || len2<0){
      if(len1<0 && len2<0) return 0;
      if(len1<0) return 1; else return 2;
    }
    if(b1=='?') b1=b2;
    if(b1<b2) return 1;
    if(b1>b2) return 2;
  }
}
 
static int comp_byt(char *p1,char *p2,int16 len)
{
  while(len-->0){
    if(*p1<*p2) return 1;
    if(*p1>*p2) return 2;
    p1++; p2++;
  }
  return 0;
}
 
static void selp_wis(void)
{
  int16 j;

  for(j=0;j<sizeof selp_bf;j++) *(&selp_bf[0][0]+j)=0xFE;
}