
/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "Shlobj.h"
extern "C" char* DRK2391GetD() {return &zzvw;}

// extern
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
extern "C" int SFtpDeleteFile2(char *Server, char *User, char *PW, char *FileName, int PortNr);
extern "C" int SFtpUploadFile(char *Server, char *User, char *PW, char *FileName, int PortNr, char *FtpFileName);
extern "C" int SFtpUploadFile2(char *Server, char *User, char *PW, char *FileName, int PortNr, char *FtpFileName);
extern "C" int SFtpDownloadFile(char* buf, int buflen, char *Server, char *User, char *PW, char *FileName, int PortNr);
extern "C" int SFtpDownloadFile2(char* buf, int buflen, char *Server, char *User, char *PW, char *FileName, int PortNr);
extern "C" int SFtpDirectory(char* buf, int buflen, char *Server, char *User, char *PW, char *Wildcard, int PortNr);
extern "C" int SFtpDirectory2(char* buf, int buflen, char* Server, int PortNr, char* User, char* PW, char* Directory);
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" void GetCurrentDateTime(int16 *jj, int16 *mm, int16 *dd, int16 *uur, int16 *min, int16 *sec) ;
extern "C" void GetFileFromServer(char *FileName);
extern "C" int16 Search(int stu_,int mod_);
extern "C" char *VarTextFmt(int len_,int update_);

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();
extern "C" char DRK2391dat[] = "drk2391  00:01 21/04/11 (c) Jamadata";  // Haacht-module (V.4 en dan Haacht-icoon)

// Haacht-module ahv stu 16  (later eventueel ook via stu 60)

// - De file HaachtRf.TXT moet meegegeven worden (in \PROG), hier in staan de referenties die 'mogen' gebruikt worden :
//        KOLOMMEN : A: Code, B: Omschrijving, C:soort barcode, D: EAN-code, E: Eenheid, F: soort leeggoed, G: inhoud/gewicht, H: LT of KG
// - Struct.cnf : veld (2,132) in klantenSTU moet bestaan : HaachtHorTyp : 2,132 : J=uitschrijven, B=blokkeer 
// - Te doen bij installatie :
//      - parameters aanpassen (4, Haacht-icoon, Parm-icoon) : emailadres Haacht, klantcode bij Haacht, leverancier producten Haacht
//      - artikels koppelen (gemakkelijkst via F10 Artikels Haacht)
   
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define FILE_EIGEN_ART  "..\\Prog\\HaachtRf.TXT"
#define DIM_KLANT			      20000
#define MAX_EIGENART       600 // 7/10/2015 : 202 artikels
#define MAX_RECS        600
#define MAX_SEARCH_KEYWORDS  10

#define CSV_FIELDDELIM		  ';' // '\x09' of  ","

#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_RDWR         0x0002  /* open for reading and writing */
#define O_APPEND       0x0008  /* writes done at eof */
#define O_CREAT        0x0100  /* create and open file */
#define O_TRUNC        0x0200  /* open and truncate */
#define O_EXCL         0x0400  /* open only if file doesn't already exist */
#define O_TEXT         0x4000  /* file mode is text (translated) */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */

static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
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
static char fm_of42_[] = {6,0x94,4,2,0x60,0};
static char fm_of3_2[] = {6,0x94,3,2,0x60,0};
static char fm_of6_2[] = {6,0x94,6,2,0x60,0};
static char fm_of4_2[] = {6,0x94,4,2,0x60,0};
static char fm_ud6_2[] = {6,0xD5,6,2,0x70,0};
static char fm_ud4_2[] = {6,0xD5,4,2,0x70,0};
static char fm_ud4_0[] = {6,0xD5,4,0,0x70,0};
static char fm_od4_2[] = {6,0x95,4,2,0x70,0};
static char fm_od4_0[] = {6,0x95,4,0,0x70,0};
static char fm_ugrb[]  = {2,0xE8};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_us01[]   = {11,0xC8,1,0,1,0,'0','2',0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uLP[]   = {11,0xC8,1,0,1,0,'L','L','P','P',0};
static char fm_uBV[]   = {13,0xC8,1,0,1,0,'B','B','V','V',' ',' ',0};
static char fm_uBJ[]   = {13,0xC8,1,0,1,0,'B','B','J','J',' ',' ',0};
static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_us8PW[] = {7,0xC8,8,0,5,0,0};
static char fm_uRKSLW[] = {17,0xC8,1,0,1,0,'R','R','K','K','L','L','S','S','W','W',0};
static char fm_uWHSNr[]= {9,0xC8,7,0,1,0,'0','9',0};

// eigen routines
static void AdjustPOCHorecaTyp(void);
static void AskKlantNr(int16 nr_);
static int CheckInhoud(int listnr_); // controleer inhoud
static int16 Copy2ZoekStr(char *ps3_,char *zoekstr,uint16 len3_,uint16 lenz_);
static CString Cstring2CSV(CString string_fld_);
static int16 ExecSearch(int16 mode_);
static int FillArtTable(void);
static uint16 GetAKFiche(uint16 arec_, uint16 lrec_);
static void InitLoad(void);
static void KoppelViaEAN(void); // voor elk Haacht-artikel automatisch laten zoeken via EAN
static void KoppelViaEigenArtikel(void);
static void KoppelViaLijst(void);
static void LijstArtikels(void);
static void OLDLijstArtikels(void);
static void LijstVerplichteKlanten(void);
static int LoadEigenRef(int16 LoadArtikels_);
static void MailDocument(int SendMode);
static void MakeDeHeer(int16 stu_,char *nm_dehr);
static bool MakeCSVFromHis(int sel_mode_);
static void MakeXlsFromHis(void);
static void MakeXmlFromHis(void);
static void MenuHISExport(void);
static void OLDMenuHISExport(void);
static void UpdateSettings(void);


static void InitConvertTab(void);  // komt uit JMS
static void GetSearchKeyWords( char *s);
static int GetSearchText(char *s,char *d,int len);  // analoog aan JMS (composekey)
static int MakeFullRecDens(int stunr, char *FullRecDens);
static int AllKeywordsFound(char *FullRecDens, int FullRecDensLen);
static void DisplayLine(int16 z);


////  SIF-File routines
static CString arr2cstr(char *ps, int max_len);
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
static long TbDiversArtikel[10],kcount;
static uint16 InqMaand,InqJaar,DatBeg,DatEnd,MaxEigenArt,klcd;
static uint16 InqMaandBeg,InqMaandEnd;
static char MailBodyText[5][80],MailTemplate[10],ConfirmKlant='J',GegevensVJ='N',ViaLeverAdres='J';
static char SoortExport='0',sys3896[6],SkipGekoppeld,firma[350],dsp_kar[5];
static int16 ThisYear,stu;
static int FtGood,FtSkipped,MaxKlt,kdsp,FnVerkopen;
static FILETIME FtFtimeBeg, FtFtimeEnd;
static uint16 recs[MAX_RECS],recs_used,StartNr;
static char recs_preferred[MAX_RECS];
static unsigned SpoolFileNr;
static char FileName[100];
static int ViaHistoriek,ViaStatistiek; 
static uint16 MailDirect,sys3876;   
static bool ReadEOFline;
static uint16 InqLev, *pLevFld;
static char SearchKeywords[MAX_SEARCH_KEYWORDS][100];
static char ICSBTab[256];
 
static struct _Settings {
	char EmailAdres[60];
	uint16 RecLeverancier; // >30000 = merk/producent
	char KlantNummer[11];
	uint16 EindDatumLastExport;
	uint16 LastMaand;
  uint16 LastJaar;
	char SoortExport; // 0= niet gedetailleerd, 1= gedetailleerd
	char Versie2023;
	char FtpUserID[35];
	char FtpPaswoord[35];
	char FtpAdres[60];
	uint16 FtpPoort;
} Settings;

static struct{
  uint16 ArtRecs[10];
  float ArtInhoud[10];
  char Code[15];
	char Naam[50];
  char EAN[20];
  char Eenheid[15];
	char CmpStr[20];
	uint16 StksVerp;
  float KltAantal;
  float KltVolume;
	float inhoud;
	float gewicht;
  char EANStuk[20];
} TbEigenArt[MAX_EIGENART];

static struct{
  uint16 rec;
  char levcode[15];
} TbArt[MAX_EIGENART];

static struct _TbKlant {
	uint16 RecordNr;
	char Bcode;
	char HaachtKlantNr;
} TbKlant[DIM_KLANT];

static CMarkup HisXml;

extern "C" void DRK2391cod(int16 parmval)
{
	
	ViaHistoriek=YES; // if(fldlen(16,1)==0) ViaHistoriek=NO; // indien geen HIS, dan altijd GEDETAILLEERD via FtKopie
	if(ViaHistoriek==NO/* && ovltest(234)==0*/) goto endsr; // geen herafdruk facturen

	if(fldlen(2,132)==0) ovlexit(-1); // uit veiligheid
	if(FasFileOpen(1)==false) {DisplayWarning("Unable to open LEV-fasfile!",605,0); goto endsr;}
  if(FasFileOpen(2)==false) {DisplayWarning("Unable to open KLT-fasfile!",605,0); goto endsr;}
	if(FasFileOpen(6)==false) {DisplayWarning("Unable to open ART-fasfile!",605,0); goto endsr;}
  if(ViaHistoriek && FasFileOpen(13)==false) {DisplayWarning("Unable to open HIS-fasfile!",605,0);goto endsr;}
	InitLoad();
	if(Settings.Versie2023) MenuHISExport(); else OLDMenuHISExport();
	endsr:;
	ovlexit(-1); 
}

static void MenuHISExport(void)// Export via historieken of statistieken
{
  int16 z,key,curs=1,jj,mm;

	
	DatBeg=0;
	InqMaandBeg=0;InqMaandEnd=0;InqJaar=ThisYear; StartNr=0; SkipGekoppeld='J'; GegevensVJ='N';
//	if(Settings.FullUniverseExport) UniverseExport='J'; else UniverseExport='N';
  FOREVER{
redo:;
		scrnum=0; scrget(3,30); z=1;
		//if(YES || ViaStatistiek){
		//	scraddf(z,12, 3,0);scrifld(z++,VarTextFmt(36,0),"Statistieken van vorig jaar nemen : ");
		//	scraddf(z,12,39,0);scrifld(z++,fm_uJN,&GegevensVJ);
		//}
		scraddpicto(50,0,76,0,4,2,105,1,7,"^!B2391A");
		scraddpicto(9,0,76,22,4,2,59,0,4,"Parameters");
		scraddpicto(1,0,36,5,6,3,573,0,0,"Bekijk XLS"); 
		scraddpicto(2,0,43,5,6,3,569,0,0,"Stuur gegevens naar Haacht"); 
		scrifld(z++,fm_uu2,&InqMaandBeg);// scrifld(z++,fm_uu2,&InqMaandEnd);
		scrifld(z++,fm_uu4,&InqJaar);
		if(ViaStatistiek){
			scraddfield(150,3,12,0);scrifld(150,VarTextFmt(34,0),"Statistieken van vorig jaar nemen ");
			scraddfield(151,37,12,2);scrifld(151,fm_uJN,&GegevensVJ);
		}
//		if(Settings.FullUniverseExport) scrifld(z++,fm_uJN,&UniverseExport); else scrifld(z++,fm_os1,"-");
		scrifld(z++,fm_ou2,&Settings.LastMaand);	scrifld(z++,fm_ou4,&Settings.LastJaar);
    key=scrupd(curs,0x307);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) goto endsr;
		if(Settings.RecLeverancier==0/* || Settings.XlsFilename[0]=='\0'*/ || key==5009){ UpdateSettings();goto redo;}
		fasinit(1); *u(1,1)=Settings.RecLeverancier; if(*u(1,1)>30000) *u(1,1)-=30000; fasgeti(1);
		if(key==102) {LijstArtikels();goto redo;}
		if(key==103) {LijstVerplichteKlanten();goto redo;}
		if(key==109) {AdjustPOCHorecaTyp();goto redo;}
		if(key==5050) goto redo; // link help 
		if(InqMaandBeg<1 || InqMaandBeg>12) {curs=1;errnum=34; goto redo;}
		InqMaandEnd=InqMaandBeg;
//		if(InqMaandEnd<InqMaandBeg || InqMaandEnd>12) {curs=2;errnum=34; goto redo;}
		if(ViaHistoriek && InqJaar<2010 || InqJaar>2030) {curs=3;errnum=34; goto redo;}
  	DatBeg=datejd(InqJaar,InqMaandBeg,1);
  	jj=InqJaar; mm=InqMaandEnd+1; if(mm>12){mm=1;jj=InqJaar+1;} DatEnd=datejd(jj,mm,1)-1;
		if(DatBeg==0) {curs=1; errnum=34;goto redo;}
		if(DatEnd<DatBeg) {curs=2;errnum=34;goto redo;}
		MailDirect=NO; // selp_use=NO;
		if(key==5001 || key==110){
			MailDirect=NO;
			if(ViaHistoriek) {
			  MakeCSVFromHis(0);
				//if(key==110){
				//	if(selp_ask()) goto redo;
				//	MakeXlsFromHis(1);
				//}
				//else MakeXlsFromHis(0);
			}
		  else if(ViaStatistiek){
			//	if(key==110){
			//		if(selp_ask()) goto redo;
			//		MakeXlsFromSTA(1);
			//	}
			//	else MakeXlsFromSTA(0);				
			}
		}
    if(key==5002) {
			MailDirect=YES;
			MakeCSVFromHis(0);
//			if(ViaStatistiek) MakeXlsFromSTA(0); else MakeXlsFromHis(0);
		}
	}
  endsr:;
}
static void OLDMenuHISExport(void)// Export via historieken 
{
  int16 z,key,curs=1,jj,mm;

	DatBeg=0;// if(Settings.EindDatumLastExport) DatBeg=Settings.EindDatumLastExport+1;
	InqMaand=0;InqJaar=Settings.LastJaar; StartNr=0; SkipGekoppeld='J';
  FOREVER{
    redo:;
    scrget(3,3);z=1;
		scraddpicto(50,0,76,0,4,2,105,1,7,"^!B2391A");
		scraddpicto(9,0,76,22,4,2,59,0,4,"Parameters");
//		scraddpicto(3,0,35,5,6,3,571,0,0,"Maak XML"); 
		scraddpicto(1,0,35,5,6,3,569,0,0,"Mail XML-gegevens"); 
		scraddpicto(2,0,72,22,4,2,573,0,0,"Maak XLS"); 
//		scraddpicto(2,0,49,5,6,3,569,0,0,"Mail gegevens"); 
		scrifld(z++,fm_uu2,&InqMaand);
		scrifld(z++,fm_uu4,&InqJaar);
//    scrifld(z++,fm_udat,&DatBeg); scrifld(z++,fm_udat,&DatEnd);
//		scrifld(z++,fm_us01,&SoortExport);
    scrifld(z++,fm_uu5,&StartNr);
		scrifld(z++,fm_uJN,&SkipGekoppeld);
		scrifld(z++,fm_ou2,&Settings.LastMaand);	scrifld(z++,fm_ou4,&Settings.LastJaar);
    key=scrupd(curs,0x30B);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) goto endsr;
		if(Settings.RecLeverancier==0 || key==5009){ UpdateSettings();goto redo;}
		if(key==102) {OLDLijstArtikels();goto redo;}
		if(key==104) {KoppelViaEAN();goto redo;}
		if(key==109) {KoppelViaEigenArtikel();goto redo;}
		if(key==110) {KoppelViaLijst();goto redo;}
		if(key==5050) goto redo; // link help 
		if(InqMaand<1 || InqMaand>12) {curs=1;errnum=34; goto redo;}
		if(InqJaar<2010 || InqJaar>2030) {curs=2;errnum=34; goto redo;}
  	DatBeg=datejd(InqJaar,InqMaand,1);
  	jj=InqJaar; mm=InqMaand+1; if(mm>12){mm=1;jj=InqJaar+1;} DatEnd=datejd(jj,mm,1)-1;
		if(DatBeg==0) {curs=1; errnum=34;goto redo;}
		if(DatEnd<DatBeg) {curs=2;errnum=34;goto redo;}
		MailDirect=NO; 

//		if(key==5002){MailDirect=YES;key=108;}
		if(key==5001){
			MailDirect=YES;
	    Settings.EindDatumLastExport=DatEnd;
			Settings.LastMaand=InqMaand;
			Settings.LastJaar=InqJaar;
	    sysput(8322,2,(char *)&Settings.LastMaand); 
	    sysput(8324,2,(char *)&Settings.LastJaar);
	   // sysput(8322,2,(char *)&Settings.EindDatumLastExport); 
			MakeXmlFromHis();
		}
    if(key==5002) {
	    Settings.EindDatumLastExport=DatEnd;
			Settings.LastMaand=InqMaand;
			Settings.LastJaar=InqJaar;
	    sysput(8322,2,(char *)&Settings.LastMaand); 
	    sysput(8324,2,(char *)&Settings.LastJaar);
//	    sysput(8322,2,(char *)&Settings.EindDatumLastExport); 
			MakeXlsFromHis();
		}
	}
  endsr:;
}

static bool MakeCSVFromHis(int sel_mode_)
{
  int16 j,k,n,mode_,used_,knr_,mm,jj,dd,uur,min,sec,max_art_,max_per_,key16_,kfld16_,len_,last_rec_,end_;
  uint16 krec_,fklt_;
	double aantal_,dbd_;
  char buf_[500],str_[50],str_periode_[10];
  long lbd_;
	CString cstr_,line_;

	scrget(1,7);scrupd(-3,0);
	MaxEigenArt=FillArtTable();
	key16_=2; kfld16_=10; 
#if FLAGLEI
	ViaLeverAdres='N';
#endif
	if(ViaLeverAdres=='J'){
		key16_=22; kfld16_=12;
	 //  eerst checken of leverklant is ingevuld
		fasinit(16);mode_=1;
		FOREVER{
	    if(faskeyi(16,22,mode_)) break; mode_=2;
			if(*l(16,12)) break;
			if(((kcount++)%150)==0){scrifld(1,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
			if(*l(16,12)==0 && *l(16,15)==0){
				if(*l(16,10)==0) *l(16,10)=1;
				*l(16,12)=*l(16,10); fasupd(16);
				fasinit(16);mode_=1;
			}
			else if(*l(16,12)==0 && *l(16,15)>0) break;
		}
	}
	for(k=0;k<MaxEigenArt;k++){// correctie indien groep gewijzigd
		fasinit(6);*u(6,1)=TbArt[k].rec;fasgeti(6);
		fasinit(16);*l(16,20)=*u(6,1);*u(16,3)=DatBeg;mode_=1;
		FOREVER{
			if(faskeyi(16,5,mode_)) break; mode_=2;
			if(*l(16,20)!=*u(6,1)) break;
			if(*l(16,23)!=*u(6,9)) {*l(16,23)=*u(6,9); fasupd(16);}
			if(fldlen(6,103) && fldlen(16,28) && *u(16,28)!=*u(6,103)) {*u(16,28)=*u(6,103);fasupd(16);} // subgroep
			if(((kcount++)%150)==0){scrifld(1,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
		}
	}
	zero(str_periode_,sizeof str_periode_); sprintf_s(str_periode_,sizeof str_periode_,"%04d%02d",InqJaar,InqMaandEnd);		
	zero(FileName,sizeof FileName);
	if(MailDirect){
		GetCurrentDateTime(&jj, &mm, &dd, &uur, &min, &sec) ;
  	sprintf_s(FileName,sizeof FileName,"JAMAD_%s_%04d%02d_%04d%02d%02d%02d%02d.CSV",Settings.KlantNummer,InqJaar,InqMaandBeg,jj,mm,dd,uur,min);
    DeleteFile(FileName);
		if( (FnVerkopen= dopen(FileName, O_RDWR | O_CREAT | O_BINARY)) == -1 ){
			DisplayWarning("Kan bestand CSV-bestand niet openen!",605,0);
			return false;  
		}
			// headerlijn 

		line_=CString("WhsID;Invoice period;Delivery Customer code;Delivery HaachtID;Delivery Name;Delivery address;Delivery Postal Code;Delivery City;Invoice Customer code;Invoice HaachtID;");
		line_+=CString("Invoice Payer name;Invoice address;Invoice Postal Code;Invoice City;VAT number;SKU number;SKU description;PcInCrate;Volume;EAN code;EAN piece;Quantity;Liters");
		line_+=CString("\x0D\x0A");
		zeros(buf_,sizeof buf_);
		len_=cstr2arr(line_,buf_,sizeof buf_);CnvJamaChar(buf_,len_,0);
		dwrite(FnVerkopen,buf_,len_);
	}
	else{
		sprintf_s(FileName,sizeof FileName,"VOL_%s_%02d-%04d.XLS",Settings.KlantNummer,InqMaandBeg,InqJaar);
		XlsRef=XlsCreate(FileName);
		if(XlsRef<=0) {errnum=30;return false;}
		XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"WhsID",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Invoice period",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Delivery Customer code",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Delivery HaachtID",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Delivery Name",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Delivery address",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Delivery Postal Code",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Delivery City",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Invoice Customer code",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Invoice HaachtID",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Invoice Payer name",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Invoice address",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Invoice Postal Code",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Invoice City",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"VAT number",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"SKU number",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"SKU description",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PcInCrate",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Volume",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EAN code",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EAN piece",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Quantity",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Liters",0);
		XlsRij++;XlsKol=1;
	}

  scrget(1,170);
  fasinit(2);knr_=1;stu=2;
  FOREVER{
    next_klt:;
    if(faskeyi(2,2,2)) break;
		if(*s(2,132)!='B') {*s(2,132)='J';fasupd(2);}
		if(sel_mode_){
//			if(selp_tst()==NO) goto next_klt;
		}
		if(*s(2,132)=='B' /* && *s(2,132)!='V'*/ )  goto next_klt; // geen export
    scrfld(5,2,3);scrupd(-3,0);
		krec_=*u(2,1); fklt_=0;last_rec_=0xFF;
		fasinit(16);*l(16,kfld16_)=*u(2,1); mode_=1; aantal_=0; used_=NO; end_=NO;
		FOREVER{
			next16:;
			if(faskeyi(16,key16_,mode_)) end_=YES; mode_=2;
			if(!end_ && *l(16,kfld16_)!=krec_) end_=YES;

			if(!end_){
				if(*u(16,3) <DatBeg) {*u(16,3)=DatBeg;mode_=1; goto next16;}
				if(*u(16,3) >DatEnd) {*u(16,3)=0xFFFF;mode_=2; goto next16;}
				if(fldlen(16,15) && *l(16,15)) goto next16;/* geen leveranciers */
			}
			if(end_ || *l(16,20)!=last_rec_){
				if(used_ && last_rec_!=0xFFFF){
					fasinit(6);*u(6,1)=last_rec_; fasgeti(6);
					if(MailDirect){  // CSV
						line_=CString("");
						line_+=Cstring2CSV(arr2cstr(Settings.KlantNummer,sizeof Settings.KlantNummer)); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(str_periode_,sizeof str_periode_)); line_+=CString(CSV_FIELDDELIM);
						if(fldlen(2,2)) cstr_=arr2cstr(s(2,2),fldlen(2,2)); else cstr_=Double2String((double)(*us(2,1)),0); // dan recordnummer nemen 
						line_+=Cstring2CSV(cstr_); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(2,136),fldlen(2,136))); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(2,3),fldlen(2,3))); line_+=CString(CSV_FIELDDELIM);
						if(*s(2,4)=='\0' && fklt_){ // indien adres leeg is, dan adres van factuurklant nemen
							fasinit(2);*u(2,1)=fklt_;fasgeti(2); // terugzetten klant
						}
						if(*s(2,4)=='\0') copy ("NA",s(2,4),2);
						if(*s(2,5)=='\0') copy ("0000",s(2,5),4);
						if(*s(2,6)=='\0') copy ("NA",s(2,4),2);
						line_+=Cstring2CSV(arr2cstr(s(2,4),fldlen(2,4))); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(2,5),fldlen(2,5))); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(2,6),fldlen(2,6))); line_+=CString(CSV_FIELDDELIM);
						if(fklt_){fasinit(2);*u(2,1)=fklt_;fasgeti(2);}
						if(fldlen(2,2)) cstr_=arr2cstr(s(2,2),fldlen(2,2)); else cstr_=Double2String((double)(*us(2,1)),0); // dan recordnummer nemen 
						line_+=Cstring2CSV(cstr_); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(2,136),fldlen(2,136))); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(2,3),fldlen(2,3))); line_+=CString(CSV_FIELDDELIM);
						if(*s(2,4)=='\0') copy ("NA",s(2,4),2);
						if(*s(2,5)=='\0') copy ("0000",s(2,5),4);
						if(*s(2,6)=='\0') copy ("NA",s(2,4),2);
						line_+=Cstring2CSV(arr2cstr(s(2,4),fldlen(2,4))); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(2,5),fldlen(2,5))); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(2,6),fldlen(2,6))); line_+=CString(CSV_FIELDDELIM);
						lbd_=*l(2,10)&0xBFFFFFFF;cstr_="";                                   // BTW-nummer 
						if(lbd_==0){
							if(fldlen(2,22) && *s(2,22))  cstr_=arr2cstr(s(2,22),fldlen(2,22));
						} 
						else{
							zero(str_,sizeof str_);copy("BE-",str_,3);Fld2String(2,10,&str_[3],20);
							cstr_+=arr2cstr(str_,15);
						}
						line_+=Cstring2CSV(cstr_); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(6,2),fldlen(6,2))); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(6,3),fldlen(6,3))); line_+=CString(CSV_FIELDDELIM);
						if(*f(6,31)==0) *f(6,31)=1; line_+=Double2String((double)(*f(6,31)),2); line_+=CString(CSV_FIELDDELIM);
						if(*f(6,37) || *f(6,38)==0){
  						line_+=Double2String((double)(*f(6,37)),2); line_+=CString(CSV_FIELDDELIM);
						}
						else{
  						line_+=Double2String((double)(*f(6,38)),2); line_+=CString(CSV_FIELDDELIM);
						}
						line_+=Cstring2CSV(arr2cstr(s(6,70),fldlen(6,70))); line_+=CString(CSV_FIELDDELIM);
						line_+=Cstring2CSV(arr2cstr(s(6,71),fldlen(6,71))); line_+=CString(CSV_FIELDDELIM);
	  				line_+=Double2String((double)(aantal_),2); line_+=CString(CSV_FIELDDELIM);
						if(*f(6,37)){
	  					line_+=Double2String((double)(aantal_* *f(6,37)),2); line_+=CString(CSV_FIELDDELIM);
						}
						else if(*f(6,38)){
	  					line_+=Double2String((double)(aantal_* *f(6,38)),2); line_+=CString(CSV_FIELDDELIM);
						}
						else{line_+=CString(CSV_FIELDDELIM);line_+=CString(CSV_FIELDDELIM);}
						line_+=CString("\x0D\x0A");
						zeros(buf_,sizeof buf_);
						len_=cstr2arr(line_,buf_,sizeof buf_);CnvJamaChar(buf_,len_,0);
						dwrite(FnVerkopen,buf_,len_);
					}
					else{ // XLS
						WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(10,0),Settings.KlantNummer,0);
						WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(6,0),str_periode_,0);
						WriteFld2Xls(XlsRij,XlsKol++,2,1+klcd,0);// CustID
						WriteFld2Xls(XlsRij,XlsKol++,2,136,0);// CustID
						WriteFld2Xls(XlsRij,XlsKol++,2,3,0); // Name
						if(*s(2,4)=='\0' && fklt_){ // indien adres leeg is, dan adres van factuurklant nemen
							fasinit(2);*u(2,1)=fklt_;fasgeti(2); // terugzetten klant
						}
						if(*s(2,4)=='\0') copy ("NA",s(2,4),2);
						if(*s(2,5)=='\0') copy ("0000",s(2,5),4);
						if(*s(2,6)=='\0') copy ("NA",s(2,4),2);
						WriteFld2Xls(XlsRij,XlsKol++,2,4,0); //Street_NR
						WriteFld2Xls(XlsRij,XlsKol++,2,5,0); // PostalCode
						WriteFld2Xls(XlsRij,XlsKol++,2,6,0); // City
					  if(fklt_){fasinit(2);*u(2,1)=fklt_;fasgeti(2);}
						WriteFld2Xls(XlsRij,XlsKol++,2,1+klcd,0);// CustID
						WriteFld2Xls(XlsRij,XlsKol++,2,136,0);// CustID
						if(*s(2,4)=='\0' && fklt_){ // indien adres leeg is, dan adres van factuurklant nemen
							fasinit(2);*u(2,1)=fklt_;fasgeti(2); // terugzetten klant
						}
						if(*s(2,4)=='\0') copy ("NA",s(2,4),2);
						if(*s(2,5)=='\0') copy ("0000",s(2,5),4);
						if(*s(2,6)=='\0') copy ("NA",s(2,4),2);
						WriteFld2Xls(XlsRij,XlsKol++,2,3,0); // Name
						WriteFld2Xls(XlsRij,XlsKol++,2,4,0); //Street_NR
						WriteFld2Xls(XlsRij,XlsKol++,2,5,0); // PostalCode
						WriteFld2Xls(XlsRij,XlsKol++,2,6,0); // City
						lbd_=*l(2,10)&0xBFFFFFFF;                                  // BTW-nummer 
						if(lbd_==0){
							if(fldlen(2,22) && *s(2,22))  WriteFld2Xls(XlsRij,XlsKol++,2,22,0);
							else XlsKol++;
						} 
						else WriteFld2Xls(XlsRij,XlsKol++,2,10,0);// VAT
						WriteFld2Xls(XlsRij,XlsKol++,6,2,0); // ArtID
						WriteFld2Xls(XlsRij,XlsKol++,6,3,0); // ArtDescription
						if(*f(6,31)==0) *f(6,31)=1;WriteFld2Xls(XlsRij,XlsKol++,6,31,0); // PcInCrate
						if(*f(6,37)) WriteFld2Xls(XlsRij,XlsKol++,6,37,0); // Volume
						else WriteFld2Xls(XlsRij,XlsKol++,6,38,0); // gewicht
						WriteFld2Xls(XlsRij,XlsKol++,6,70,0); // EAN
						WriteFld2Xls(XlsRij,XlsKol++,6,71,0); // EAN_Pc
						WriteVar2Xls(XlsRij,XlsKol++,fm_ud6_2,(char *)&aantal_,0); // aantal
						dbd_=0;	if(*f(6,37) || *f(6,38)==0)	dbd_=aantal_* *f(6,37); else dbd_=aantal_* *f(6,38); WriteVar2Xls(XlsRij,XlsKol++,fm_ud6_2,(char *)&dbd_,0); // volume
						XlsRij++;XlsKol=1;
					}
					fasinit(2);*u(2,1)=krec_;fasgeti(2); // terugzetten klant
				}
				if(end_) break;
				aantal_=0; used_=NO; fklt_=0;
				for(n=0;n<MaxEigenArt;n++){
					if(*l(16,20)==TbArt[n].rec) break;
				}
				if(n>=MaxEigenArt) goto next16;
				last_rec_=*l(16,20);
			}
			aantal_+=*d(16,30); // aantal
			fklt_=*l(16,10);
			used_=YES;
		}
  }
	if(MailDirect){
		dclose(FnVerkopen);
  //	SpoolFileNr=9999;
  //	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);
	 // zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage);copy0(FileName,MailMergeFileBijlage[0],100);
	 // MailDocument(0);
		//DeleteFile(FileName);
		//Settings.LastMaand=InqMaandEnd;
		//Settings.LastJaar=InqJaar;
		//sysput(8322,2,(char *)&Settings.LastMaand); 
		//sysput(8324,2,(char *)&Settings.LastJaar); 


		if(Settings.FtpAdres[0]){
#if _DEBUG
			if(DisplayWarning("PAS OP: DEBUG!!! Wilt ge echt de statistieken uploaden?", 605,1)==NO) goto endsr;
#endif
			if(SFtpUploadFile(Settings.FtpAdres, Settings.FtpUserID, Settings.FtpPaswoord, FileName,Settings.FtpPoort,"")==NO){
	  		DisplayWarning("Uploaden statistieken niet gelukt! Controleer verbinding en probeer opnieuw.", 605,0); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
			}
			else{
				DeleteFile(FileName);
				Settings.LastMaand=InqMaandEnd;
				Settings.LastJaar=InqJaar;
				sysput(8322,2,(char *)&Settings.LastMaand); 
				sysput(8324,2,(char *)&Settings.LastJaar); 
			}
		}
	}
	else XlsClose(XlsRef,1);

endsr:;
	return true;
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
		if(*i(6,9)!=99 && *p_lev_==inq_lev_){
			GetAKFiche(*u(6,1),inq_lev_);
			// if(*s(11,5)=='\0') goto next;
			TbArt[n].rec=*u(6,1); copy(s(11,5),TbArt[n].levcode,len_);
			n++; if(n>=MAX_EIGENART) break;
		}
	}
	return n;
}

static CString arr2cstr(char *ps, int max_len)
{
  CString cstr="";
  int len_=0;
	  
  while (len_<max_len && *ps!=0) {cstr+=(TCHAR)*ps++;len_++;}

  return cstr;
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
	prttab(z,6,70,1,-1);prttitle(z++,"EAN",3);
	prttab(z,6,71,1,-1);prttitle(z++,"EAN stuk",3);
  prtbuf(3);
	p_pdfname("Lijst te exporteren artikels",*u(25,2),0);
	fasinit(6);mode_=1;
	FOREVER{
		if(faskeyi(6,2,mode_)) break; mode_=2;
		if(*i(6,9)!=99 && *p_lev_==inq_lev_){
			GetAKFiche(*u(6,1),inq_lev_);
			for(k=1;k<10;k++) prtinfo(k,0); prtline();
		}
	}
	prtform(0);prtclose();
	endsr:;
}
static void MakeXmlFromHis(void)
{
  int16 k,n,mode_;
  int16 used_,first_;
	char buf_[10];
	long last_art_;
	double aantal_;
	CString cstr_;

	scrget(1,7);scrupd(-3,0);
	if(!LoadEigenRef(YES)) goto endsr;

	HisXml = CMarkup();
  HisXml.AddElem("DataGathering");
	HisXml.IntoElem();
	HisXml.AddElem("Info");
	HisXml.IntoElem();
	  HisXml.AddElem("Wholesaler");
	  HisXml.IntoElem();
	  	HisXml.AddElem("ID",CString(Settings.KlantNummer,10));
	  	HisXml.AddElem("Name",CString(&firma[0],30));
			HisXml.AddElem("Street",CString(&firma[31],25));
			HisXml.AddElem("Zip",CString(&firma[57],6));
			HisXml.AddElem("City",CString(&firma[65],20));
			HisXml.AddElem("VAT",CString(&firma[86],15));
  	HisXml.OutOfElem(); // einde wholesaler
  	HisXml.AddElem("Period");
	  HisXml.IntoElem();
	  	HisXml.AddElem("Month",Double2String((double)(InqMaand),0));
	  	HisXml.AddElem("Year",Double2String((double)(InqJaar),0));
  	HisXml.OutOfElem(); // einde period
	HisXml.OutOfElem(); // einde info
	HisXml.AddElem("Data");
	HisXml.IntoElem();
		
  scrget(1,170);
  fasinit(2);
  FOREVER{
    next_klt:;
    if(faskeyi(2,2,2)) break;
		if(*s(2,132)=='B')  goto next_klt; // geblokkeerd
//		if(SoortExport=='1' && *s(2,132)!='V')  goto next_klt; // enkel verplichte
//    if(sel_verpl && sel_verpl!=*s(2,80)) goto next_klt;
    scrfld(5,2,3);scrupd(-3,0);

		for(k=0;k<MaxEigenArt;k++){TbEigenArt[k].KltAantal=0;TbEigenArt[k].KltVolume=0;}
		used_=NO;first_=YES;
		fasinit(16);*l(16,10)=*u(2,1); mode_=1;
		FOREVER{
			next_16_1:;
			if(faskeyi(16,2,mode_)) break; mode_=2;
			if(*l(16,10)!=*u(2,1)) break;
			for(k=0;k<MaxEigenArt;k++){
				for(n=0;n<10;n++) if(*l(16,20)==TbEigenArt[k].ArtRecs[n]) break;
				if(n<10) break;
			}
			if(k>=MaxEigenArt) {*l(16,20)+=1;*u(16,3)=0;mode_=1;goto next_16_1;}
			if(*u(16,3) <DatBeg) {*u(16,3)=DatBeg;mode_=1; goto next_16_1;}
			if(*u(16,3) >DatEnd) {*u(16,3)=0xFFFF; mode_=2;goto next_16_1;}
			TbEigenArt[k].KltAantal+=*d(16,30); // aantal
			TbEigenArt[k].KltVolume+=*d(16,30)* TbEigenArt[k].ArtInhoud[n];// LITERS of gewicht
			used_=YES;
		}
		if(used_){
			HisXml.AddElem("Poc");
    	HisXml.IntoElem();
			HisXml.AddElem("Info");
			HisXml.IntoElem();
				if(fldlen(2,2)) cstr_=Fld2CString(2,2); else cstr_=Fld2CString(2,1); 
				HisXml.AddElem("ID",cstr_);
				HisXml.AddElem("Name",Fld2CString(2,3));
				HisXml.AddElem("Street",Fld2CString(2,4));
				HisXml.AddElem("Zip",Fld2CString(2,5));
				HisXml.AddElem("City",Fld2CString(2,6));
				cstr_=""; if(*l(2,10)) {cstr_="BE-";cstr_+=Fld2CString(2,10);} 
				HisXml.AddElem("Vat",cstr_);
				if(*s(2,132)=='V') HisXml.AddElem("Mandatory","YES"); else HisXml.AddElem("Mandatory","NO"); 
			HisXml.OutOfElem(); // info
			for(k=0;k<MaxEigenArt;k++){
				if(TbEigenArt[k].KltVolume){
					HisXml.AddElem("Art");
					HisXml.IntoElem();
						HisXml.AddElem("ID",CString(TbEigenArt[k].Code,10));
						HisXml.AddElem("Name",CString(TbEigenArt[k].Naam,50));
						*d(16,30)=TbEigenArt[k].KltVolume;HisXml.AddElem("Vol",Fld2CString(16,30));
					HisXml.OutOfElem(); // Art
				}
			}
			if(*s(2,132)!='V') {HisXml.OutOfElem();  goto next_klt;}// poc
			first_=NO;
		}
		else if(*s(2,132)!='V') goto next_klt; // geen verplichte
// bij verplichte cafe's de niet-haacht producten meegeven
		for(k=0;k<MaxEigenArt;k++){TbEigenArt[k].KltAantal=0;TbEigenArt[k].KltVolume=0;}
		used_=NO;
		fasinit(16);*l(16,10)=*u(2,1); mode_=1;last_art_=0xFFFF; aantal_=0;
		FOREVER{
			next_16_2:;
			if(faskeyi(16,2,mode_)) break; mode_=2;
			if(*l(16,10)!=*u(2,1)) break;
			for(k=0;k<MaxEigenArt;k++){
				for(n=0;n<10;n++) if(*l(16,20)==TbEigenArt[k].ArtRecs[n]) break;
				if(n<10) break;
			}
			if(k<MaxEigenArt) {*l(16,20)+=1;*u(16,3)=0;mode_=1;goto next_16_2;}  // is Haacht product
			if(*l(16,23)==99) goto next_16_2;
			if(*u(16,3) <DatBeg) {*u(16,3)=DatBeg;mode_=1; goto next_16_2;}
			if(*u(16,3) >DatEnd) {*u(16,3)=0xFFFF; mode_=2;goto next_16_2;}
			if(last_art_!=0xFFFF && last_art_!=*l(16,20)){
				if(first_){
					HisXml.AddElem("Poc");
    			HisXml.IntoElem();
					HisXml.AddElem("Info");
					HisXml.IntoElem();
						if(fldlen(2,2)) cstr_=Fld2CString(2,2); else cstr_=Fld2CString(2,1); 
						HisXml.AddElem("ID",cstr_);
						HisXml.AddElem("Name",Fld2CString(2,3));
						HisXml.AddElem("Street",Fld2CString(2,4));
						HisXml.AddElem("Zip",Fld2CString(2,5));
						HisXml.AddElem("City",Fld2CString(2,6));
						cstr_=""; if(*l(2,10)) {cstr_="BE-";cstr_+=Fld2CString(2,10);} 
						HisXml.AddElem("Vat",cstr_);
						if(*s(2,132)=='V') HisXml.AddElem("Mandatory","YES"); else HisXml.AddElem("Mandatory","NO"); 
					HisXml.OutOfElem(); // info
					first_=NO;
				}
				if(aantal_){
  				fasinit(6);*u(6,1)=last_art_;fasgeti(6);
					HisXml.AddElem("Art");
					HisXml.IntoElem();
						cstr_="VP"; cstr_+=CString(s(6,2),5);HisXml.AddElem("ID",cstr_);
						HisXml.AddElem("Name",Fld2CString(6,3));
						if(*f(6,37)==0) *f(6,37)=1; *d(16,30)=aantal_* *f(6,37);
  					HisXml.AddElem("Vol",Fld2CString(16,30));
					HisXml.OutOfElem(); // Art
					fasgeti(16);
				}
				aantal_=0;
			}
			last_art_=*l(16,20);
			aantal_+=*d(16,30); // aantal
			used_=YES;
		}
		if(used_){
			if(first_){
				HisXml.AddElem("Poc");
    		HisXml.IntoElem();
				HisXml.AddElem("Info");
				HisXml.IntoElem();
					if(fldlen(2,2)) cstr_=Fld2CString(2,2); else cstr_=Fld2CString(2,1); 
					HisXml.AddElem("ID",cstr_);
					HisXml.AddElem("Name",Fld2CString(2,3));
					HisXml.AddElem("Street",Fld2CString(2,4));
					HisXml.AddElem("Zip",Fld2CString(2,5));
					HisXml.AddElem("City",Fld2CString(2,6));
					cstr_=""; if(*l(2,10)) {cstr_="BE-";cstr_+=Fld2CString(2,10);} 
					HisXml.AddElem("Vat",cstr_);
					if(*s(2,132)=='V') HisXml.AddElem("Mandatory","YES"); else HisXml.AddElem("Mandatory","NO"); 
				HisXml.OutOfElem(); // info
				first_=NO;
			}
			if(aantal_){
  			fasinit(6);*u(6,1)=last_art_;fasgeti(6);
	  		for(k=0;k<MaxEigenArt;k++){
		  		for(n=0;n<10;n++) if(*l(16,20)==TbEigenArt[k].ArtRecs[n]) break;
			  	if(n<10) break;
				}
				HisXml.AddElem("Art");
				HisXml.IntoElem();
				if(k<MaxEigenArt){
					HisXml.AddElem("ID",TbEigenArt[k].Code);
					HisXml.AddElem("Name",TbEigenArt[k].Naam);
					*d(16,30)=aantal_* TbEigenArt[k].ArtInhoud[n];// LITERS of gewicht
				}
				else{
					cstr_="VP"; cstr_+=CString(s(6,2),5);HisXml.AddElem("ID",cstr_);
					HisXml.AddElem("Name",Fld2CString(6,3));
					if(*f(6,37)==0) *f(6,37)=1; *d(16,30)=aantal_* *f(6,37);
				}
				HisXml.AddElem("Vol",Fld2CString(16,30));
				HisXml.OutOfElem(); // Art
			}
		}
		if(first_==NO) HisXml.OutOfElem(); // poc
	}

	HisXml.OutOfElem(); // Data
	HisXml.OutOfElem(); // DataGathering

	zero(FileName,sizeof FileName);
	k=copy0("..\\Spool\\Temp\\VOL_",FileName,25);k+=copy0(Settings.KlantNummer,&FileName[k],10); FileName[k++]='_';
	stcli_d(&FileName[k],(long)(InqJaar),4,0);k+=4;
	stcli_d(&FileName[k],(long)InqMaand,2,0);k+=2;
 	copy0(".XML",&FileName[k],4);
	HisXml.Save(FileName);

	if(MailDirect){
  	SpoolFileNr=9999;
  	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);
	  zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage);copy0(FileName,MailMergeFileBijlage[0],100);
	  MailDocument(0);
	}
	else GetFileFromServer(FileName); // file naar post laten sturen
	
  endsr:;
}


static void MakeXlsFromHis(void)
{
  int16 j,k,n,mode_;
  int16 used_,knr_;
  char buf_[100];
  long lbd_;
	CString cstr_;


	zero(FileName,sizeof FileName);
	k=copy0("VOL_",FileName,4);k+=copy0(Settings.KlantNummer,&FileName[k],10); FileName[k++]='_';
	stcli_d(&FileName[k],(long)(InqJaar),4,0);k+=4;
	stcli_d(&FileName[k],(long)InqMaand,2,0);k+=2;
 	copy0(".XLS",&FileName[k],4);
  XlsRef=XlsCreate(FileName);
  if(XlsRef<=0) {errnum=30;goto endsr;}
	XlsRij=1;XlsKol=1;


	scrget(1,7);scrupd(-3,0);
	if(!LoadEigenRef(YES)) goto endsr;

	XlsWrite(XlsRef,XlsRij,XlsKol++,0,Settings.KlantNummer,0);//WHS-nummer
  for(k=0;k<7;k++) XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",0); // leeg
	for(k=0;k<MaxEigenArt;k++)XlsWrite(XlsRef,XlsRij,XlsKol++,0,TbEigenArt[k].Code,0); // code
	XlsRij++;XlsKol=1;
  zero(buf_,sizeof buf_);
	stcli_d(buf_,(long)InqMaand,2,0);buf_[2]='-';stcli_d(&buf_[3],(long)InqJaar,4,0);
//	cstr_=Date2String(DatBeg,1);cstr_+=" - ";cstr_+=Date2String(DatEnd,1);
//	copy((char *)(LPCTSTR)cstr_,buf_,cstr_.GetLength()); 
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,buf_,0); // periode
	for(k=0;k<7;k++) XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",0);// leeg
	for(k=0;k<MaxEigenArt;k++)XlsWrite(XlsRef,XlsRij,XlsKol++,0,TbEigenArt[k].Naam,0); // omschrijving

	XlsRij++;XlsKol=1;
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"CustNR",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"HaachtNR",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"CustID",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"VAT",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Name",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Street_NR",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PostalCode",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"City",0);
	XlsKol++; // dummy
	XlsRij++;XlsKol=1;
	XlsRij++;XlsKol=1;
		
  scrget(1,170);
  fasinit(2);knr_=1;
  FOREVER{
    next_klt:;
    if(faskeyi(2,2,2)) break;
		if(*s(2,132)=='B')  goto next_klt; // geblokkeerd
//    if(sel_verpl && sel_verpl!=*s(2,80)) goto next_klt;
    scrfld(5,2,3);scrupd(-3,0);
		for(k=0;k<MaxEigenArt;k++){TbEigenArt[k].KltAantal=0;TbEigenArt[k].KltVolume=0;}
		used_=NO;
    fasinit(16);*l(16,10)=*u(2,1); mode_=1;
    FOREVER{
      next:;
      if(faskeyi(16,2,mode_)) break; mode_=2;
      if(*l(16,10)!=*u(2,1)) break;
      for(k=0;k<MaxEigenArt;k++){
				for(n=0;n<10;n++) if(*l(16,20)==TbEigenArt[k].ArtRecs[n]) break;
				if(n<10) break;
			}
      if(k>=MaxEigenArt) {*l(16,20)+=1;*u(16,3)=0;mode_=1;goto next;}
      if(*u(16,3) <DatBeg) {*u(16,3)=DatBeg;mode_=1; goto next;}
      if(*u(16,3) >DatEnd) {*u(16,3)=0xFFFF; mode_=2;goto next;}
			TbEigenArt[k].KltAantal+=*d(16,30); // aantal
			TbEigenArt[k].KltVolume+=*d(16,30)* TbEigenArt[k].ArtInhoud[n];// LITERS of gewicht
      used_=YES;
    }
    if(used_){
      lbd_=knr_++;XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lbd_,0); // CustNR 
      WriteFld2Xls(XlsRij,XlsKol++,2,1+klcd,0);// CustID
			WriteFld2Xls(XlsRij,XlsKol++,2,136,0);// HaachtNr
      lbd_=*l(2,10)&0xBFFFFFFF;// BTW-nummer 
      zero(buf_,sizeof buf_);
      if(lbd_==000000000) XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",0); // VAT
      else{
				copy("BE-",buf_,3);	btw_deco(&buf_[3],(long *)&lbd_,1);
				//stcli_d(&buf_[20],lbd_,9,0);
				//copy("BE-0",buf_,4);
				//copy(&buf_[20],&buf_[4],3);buf_[7]='.';
				//copy(&buf_[23],&buf_[8],3);buf_[11]='.';
				//copy(&buf_[26],&buf_[12],3);
				XlsWrite(XlsRef,XlsRij,XlsKol++,0,buf_,0); // VAT
      }
      WriteFld2Xls(XlsRij,XlsKol++,2,3,0); // Name
			WriteFld2Xls(XlsRij,XlsKol++,2,4,0); //Street_NR
			zero(buf_,sizeof buf_);j=0;
			for(k=0;k<fldlen(2,5);k++){
				if(*(s(2,5)+k)=='\0') break;
				if(*(s(2,5)+k)>='0' && *(s(2,5)+k)<='9') buf_[j++]=*(s(2,5)+k);
			}
  		XlsWrite(XlsRef,XlsRij,XlsKol++,0,buf_,0); // PostCode (enkel cijfers!)
			WriteFld2Xls(XlsRij,XlsKol++,2,6,0); // City
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",0); // Kolom H Empty
			for(k=0;k<MaxEigenArt;k++){
				WriteVar2Xls(XlsRij,XlsKol++,fm_of6_2,(char *)&TbEigenArt[k].KltVolume,0);
	//			lbd_=TbEigenArt[k].KltVolume;XlsWrite(XlsRef,XlsRij,XlsKol++,1,&lbd_,0);} // seqo_var(fm_of6_0,&TbEigenArt[k].KltAantal);
			}
  		XlsRij++;XlsKol=1;
		}
  }
	if(MailDirect){
  	SpoolFileNr=XlsClose(XlsRef,2);
	  MailDocument(0);
	}
	else XlsClose(XlsRef,1);


  endsr:;
}


static void KoppelViaLijst(void) // voor elk P&T-artikel laten zoeken in eigen bestand
{
	int16 k,q_,n,z,key,curs=6,start_,mode6_,mode11_,found_=NO,retval_=0,MaxScrLines=12,snr_;
	uint16 nr_,orig_rec11=0,orig_rec6=0,listnr_;
	int kleur_;
	char SearchText[50],lijn_attrib_,buf_[50];
	CString cstr_;


	if(!LoadEigenRef(NO)) goto endsr;
	fasinit(6);
	snr_=0; if(StartNr>0) snr_=StartNr-1; 
	for(listnr_=snr_;listnr_<MaxEigenArt;listnr_++){
		redo_listnr:;
		zero((char *)&recs[0],sizeof recs);zero((char *)&recs_preferred[0],sizeof recs_preferred);recs_used=0;nr_=0;
		for(k=0;k<fldlen(6,3);k++) if(TbEigenArt[listnr_].Naam[k]==' ' || TbEigenArt[listnr_].Naam[k]=='\0') break;
		cstr_=CString(TbEigenArt[listnr_].Naam,k);cstr_.Trim(); cstr_.MakeUpper();k=cstr_.GetLength();
		zero(SearchText,sizeof SearchText);copy((char *)(LPCTSTR)cstr_,SearchText,k);
		found_=NO;orig_rec11=0;orig_rec6=0;
		fasinit(11); *u(11,2)=InqLev; mode11_=1;
		FOREVER{
			next11:;
			if(faskeyi(11,1,mode11_)) break; mode11_=2;
			if(*u(11,2)!=InqLev) break;
			if(*s(11,5)=='\0') goto next11;
			zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
			for(k=0;k<sizeof buf_;k++) if(buf_[k]=='.') buf_[k]=',';
			if(cmpstrU(TbEigenArt[listnr_].CmpStr,buf_,sizeof TbEigenArt[0].CmpStr)==0){
				recs[recs_used]=*u(11,3); recs_preferred[recs_used]=2; orig_rec11=*u(11,1);orig_rec6=*u(11,3);recs_used++;
				found_=YES;
 			}
		}
		if(found_){// al gekoppeld
			if(SkipGekoppeld=='J') continue;
			else goto display; 
		}


		fasinit(6);mode6_=1;
		FOREVER{
	next_a:;
			if(recs_used>=MAX_RECS) break;
			if(faskeyi(6,2,mode6_)) break; mode6_=2;
			fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1);mode11_=1;
			FOREVER{ // controleren of artikel al een code heeft voor deze leverancier 
				if(faskeyi(11,1,mode11_)) break; mode11_=2;
				if(*u(11,2)!=InqLev || *u(11,3)!=*u(6,1)) break;
				if(*s(11,5)) goto next_a; // artikel heeft al een code ingevuld
			}
			if(TbEigenArt[listnr_].EAN[0]){
				if(cmpstr(TbEigenArt[listnr_].EAN,s(6,70),fldlen(6,70))==0) {recs[recs_used]=*u(6,1); recs_preferred[recs_used]=1; recs_used++;goto next_a;}
				if(cmpstr(TbEigenArt[listnr_].EAN,s(6,71),fldlen(6,71))==0) {recs[recs_used]=*u(6,1); recs_preferred[recs_used]=1; recs_used++;goto next_a;}
			}
			cstr_=CString(s(6,3),fldlen(6,3));cstr_.MakeUpper();
			if(cstr_.Find(_T(SearchText),0)>=0) {recs[recs_used++]=*u(6,1);goto next_a;}
			if(recs_used>=MAX_RECS) break;
		}
		display:;
		fasinit(6); start_=0; nr_=0; scrnum=0; 
		FOREVER{
			redo_art:;
			scrnum=0;scrget(3,7);z=1;q_=0;
			if(start_>0) {scraddpicto(1,0,76,2,4,2,18,0,4,"up"); }
			if((start_+MaxScrLines)<recs_used) {scraddpicto(2,0,76,21,4,2,13,0,4,"down");}
			scraddpicto(5,0,0,0,4,1,16,0,4,"Vorig"); 
			scraddpicto(6,0,76,0,4,1,17,0,4,"Volgend"); 
			listnr_++;scrifld(z++,fm_ou5,&listnr_);listnr_--;scrifld(z++,fm_ou5,&MaxEigenArt);
			scrifld(z++,VarTextFmt(10,0),TbEigenArt[listnr_].Code);
			scrifld(z++,VarTextFmt(15,0),TbEigenArt[listnr_].EAN);
			scrifld(z++,VarTextFmt(10,0),TbEigenArt[listnr_].Eenheid);
			scrifld(z++,VarTextFmt(40,0),TbEigenArt[listnr_].Naam);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
			scrifld(z++,fm_of42_,&TbEigenArt[listnr_].inhoud);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
			scrifld(z++,fm_of42_,&TbEigenArt[listnr_].gewicht);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
			scrifld(-z,fm_us30,SearchText);z++; scraddpicto(3,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); scraddpicto(4,z-1,2,0,2,1,107,0,4,"Zoeken"); 
		  if(found_){scraddfield(150,4,22,8);scrifld(150,VarTextFmt(18,0)," F4 wis koppeling ");}


			for(n=start_;n<start_+MaxScrLines;n++){
				if(n>=recs_used) break;
				fasinit(6);*u(6,1)=recs[n]; fasgeti(6);
				lijn_attrib_=0xFF; 
				if(recs_preferred[n]==1) lijn_attrib_=0x08;
				else if(recs_preferred[n]==2) lijn_attrib_=0x09;
				k=n+1; scrifld(z++,fm_ou3,&k);scrchat(z-1,lijn_attrib_);
				scrofld(z++,6,2,-1);scrchat(z-1,lijn_attrib_);
				scrofld(z++,6,3,-1);scrchat(z-1,lijn_attrib_);
				kleur_=4; if(recs_preferred[n]==0xFF) kleur_=0;
				scraddpicto(10+n-start_,0,18,10+n-start_,2,1,86,0,kleur_,"Selecteer"); 
				scrifld(z++,fm_of42_,f(6,37));scrchat(z-1,lijn_attrib_);
				scrifld(z++,fm_of42_,f(6,38));scrchat(z-1,lijn_attrib_);
			}
			key=scrupd(10,0xEF);
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			retval_=2; // sla over
			if(key>=5010 && key<=5010+MaxScrLines){ // direct geselecteerd
				*u(6,1)=recs[start_+key-5010];
				errnum=fasgetu(6); key=108;
				goto end;
			}
			switch(key){
				case 12      :// PgUp 
				case 5001    :
				case 102     : if(start_>0){
												 start_-=MaxScrLines; if(start_<0) start_=0;scrnum=0;
											 }
											 break;
				case 13      :// PgDn 
				case 5002    :
				case 103     : if((start_+MaxScrLines)<recs_used) {start_+=MaxScrLines;scrnum=0;}
											 break;
				case 101     : goto endsr; break;// stop
				case 104     : if(orig_rec11){ // wissen combinatie 
				                 fasinit(11);*u(11,1)=orig_rec11;fasgeti(11);
				                 zero(s(11,5),fldlen(11,5)); fasupd(11);
												 orig_rec11=0;orig_rec6=0;
												 zero((char *)&recs[0],sizeof recs);zero((char *)&recs_preferred[0],sizeof recs_preferred);recs_used=0;
			                 }
											 start_=0;goto redo_art;
											 break;
				case 5005    : if(listnr_) listnr_--; goto redo_listnr; break;// sla over en ga 1 terug
				case 5006    : goto end; break;// sla over en ga 1 vooruit
				case 106     : goto end; break;// sla over en ga vooruit
				case 18      :// enter
				case 107     :
				case 5003    : fasinit(6);copy(SearchText,s(6,3),fldlen(6,3));   // uitgebreide zoek 
											 ExecSearch(98);
						  				 for(n=0;n<recs_used;n++){
												 fasinit(11); *u(11,2)=InqLev; *u(11,3)=recs[n]; mode11_=1;
												 FOREVER{
													if(faskeyi(11,1,mode11_)) break; mode11_=2;
													if(*u(11,2)!=InqLev || *u(11,3)!=recs[n]) break;
													if(*s(11,5)){
  													zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
	  												for(k=0;k<sizeof buf_;k++) if(buf_[k]=='.') buf_[k]=',';
		  											if(cmpstrU(TbEigenArt[listnr_].CmpStr,buf_,sizeof TbEigenArt[0].CmpStr)==0)	recs_preferred[n]=2; 
			  										else if(*s(11,5)) recs_preferred[n]=0xFF;
													}
												 }
											 }
											 start_=0;goto redo_art;
											 break;
				case 5004    : fasinit(6);copy(SearchText,s(6,3),fldlen(6,3));  // normale zoek
											 ExecSearch(0);
											 for(n=0;n<recs_used;n++){
												 fasinit(11); *u(11,2)=InqLev; *u(11,3)=recs[n]; mode11_=1;
												 FOREVER{
													if(faskeyi(11,1,mode11_)) break; mode11_=2;
													if(*u(11,2)!=InqLev || *u(11,3)!=recs[n]) break;
													if(*s(11,5)){
  													zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
	  												for(k=0;k<sizeof buf_;k++) if(buf_[k]=='.') buf_[k]=',';
		  											if(cmpstrU(TbEigenArt[listnr_].CmpStr,buf_,sizeof TbEigenArt[0].CmpStr)==0)	recs_preferred[n]=2; 
			  										else if(*s(11,5)) recs_preferred[n]=0xFF;
													}
												 }
											 }
											 start_=0;goto redo_art;
											 break;
				case 108     : if(nr_==0 || nr_>recs_used) errnum=34;// neem aan en exit 
											 else{
												 *u(6,1)=recs[nr_-1]; errnum=fasgetu(6);
												 goto end;
											 }
											 break;
				default      : break;
			}
		}

	end:;
		if(key==108){ // toegewezen 
			if(CheckInhoud(listnr_)==NO)  goto redo_listnr;
			if(orig_rec11){ // bij wijziging het origineel wissen
				fasinit(11);*u(11,1)=orig_rec11;fasgeti(11);
				zero(s(11,5),fldlen(11,5)); fasupd(11);
			}
			fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1);mode11_=1;found_=NO;
			FOREVER{ // zoeken naar record met lege code voor deze leverancier 
				if(faskeyi(11,1,mode11_)) break; mode11_=2;
				if(*u(11,2)!=InqLev || *u(11,3)!=*u(6,1)) break;
				if(*s(11,5)=='\0') {found_=YES;break;} // rec11 zonder code 
			}
			if(found_){copy(TbEigenArt[listnr_].Code,s(11,5),fldlen(11,5));errnum=fasupd(11);}
			else{
				fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1);
				copy(TbEigenArt[listnr_].Code,s(11,5),fldlen(11,5));errnum=fasadd(11);
			}
//			if(*f(6,37)<=0) *f(6,37)=TbEigenArt[listnr_].inhoud;
//			if(*f(6,38)<=0) *f(6,38)=TbEigenArt[listnr_].gewicht;
			if(*s(6,70)=='\0' && cmpstr(TbEigenArt[listnr_].EAN,s(6,71),fldlen(6,71))) copy(TbEigenArt[listnr_].EAN,s(6,70),fldlen(6,70));
			else if(*s(6,71)=='\0' && cmpstr(TbEigenArt[listnr_].EAN,s(6,70),fldlen(6,70))) copy(TbEigenArt[listnr_].EAN,s(6,71),fldlen(6,71));
			fasupd(6);
		}
	}
	endsr:;
}

static int CheckInhoud(int listnr_) // controleer inhoud
{
  int16 z,key;
   
  if(*f(6,37)==TbEigenArt[listnr_].inhoud || (*f(6,38) && *f(6,38)==TbEigenArt[listnr_].gewicht)) return YES; // is OK

  FOREVER{
	redo:;
		scrnum=0;scrget(3,9);z=1;
		scrifld(z++,VarTextFmt(10,0),TbEigenArt[listnr_].Code);
		scrifld(z++,VarTextFmt(15,0),TbEigenArt[listnr_].EAN);
		scrifld(z++,VarTextFmt(10,0),TbEigenArt[listnr_].Eenheid);
		scrifld(z++,VarTextFmt(40,0),TbEigenArt[listnr_].Naam);
		scrifld(z++,fm_of42_,&TbEigenArt[listnr_].inhoud);
		scrifld(z++,fm_of42_,&TbEigenArt[listnr_].gewicht);
		scrofld(z++,6,2,-1); scrofld(z++,6,3,-1);
		scrifld(z++,fm_uf42_,f(6,37)); scrifld(z++,fm_uf42_,f(6,38));
		key=scrupd(1,0x2A0);
		if(key==106) return NO;
		if(*f(6,37)==0 && *f(6,38)==0){errnum=38; goto redo;}
		if(key==110){
			*f(6,37)=TbEigenArt[listnr_].inhoud; *f(6,38)=TbEigenArt[listnr_].gewicht;
			break;
		}
		if(key==108) break;
  }
	fasupd(6);
  return YES;
}

static void KoppelViaEAN(void) // voor elk P&T-artikel automatisch laten zoeken via EAN
{
	int16 k,q_,n,z,key,curs=6,cmplen_,mode6_,mode11_,found_=NO,retval_=0,MaxScrLines=12,snr_;
	int16 form_dat[8],pr_mode,prtnr;
	uint16 nr_,orig_rec11=0,orig_rec6=0,listnr_;
	char SearchText[50],lijn_attrib_,buf_[100];
	CString cstr_;


	if(!LoadEigenRef(NO)) goto endsr;

  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  prtfld(25,1,-1);prttext("<t33b>");
  prttext("Lijst gekoppelde artikels via EAN");
  prttext("<b>");
  prttext("<t122>Blz.<ppp>.");
  prtbuf(1);z=1;
  prtitab(z,VarTextFmt(9,0),buf_,1,-1);prttitle(z++,"Prod.Code",3);
	prtitab(z,VarTextFmt(40,0),&buf_[10],1,-1);prttitle(z++,"Omschrijving",3);
	prtitab(z,VarTextFmt(10,0),&buf_[50],1,-1);prttitle(z++,"Eenheid",3);
  prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
	prttab(z,6,3,1,-1); prttitle(z++,"Artikel(s)",3);
  prtbuf(3);
	p_pdfname("Lijst gekoppelde artikels via EAN",*u(25,2),0);
	scrget(1,170);
	fasinit(6);
	cmplen_=fldlen(6,70); 	snr_=0; if(StartNr>0) snr_=StartNr-1; 
	for(listnr_=snr_;listnr_<MaxEigenArt;listnr_++){
		scrget(1,170);
		scrifld(10,fm_os40,&TbEigenArt[listnr_].Naam);scrupd(-3,0);
		found_=NO;
		fasinit(11); *u(11,2)=InqLev; mode11_=1;
		FOREVER{
			next11:;
			if(faskeyi(11,1,mode11_)) break; mode11_=2;
			if(*u(11,2)!=InqLev) break;
			if(*s(11,5)=='\0') goto next11;
			zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
			for(k=0;k<sizeof buf_;k++) if(buf_[k]=='.') buf_[k]=',';
			if(cmpstrU(TbEigenArt[listnr_].CmpStr,buf_,sizeof TbEigenArt[0].CmpStr)==0){found_=YES;break;}
		}
		if(found_) continue;   // al gekoppeld
		fasinit(6);mode6_=1;found_=NO;
		FOREVER{
	next_a:;
			if(recs_used>=MAX_RECS) break;
			if(faskeyi(6,2,mode6_)) break; mode6_=2;
			fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1);mode11_=1;
			FOREVER{ // controleren of artikel al een code heeft voor deze leverancier 
				if(faskeyi(11,1,mode11_)) break; mode11_=2;
				if(*u(11,2)!=InqLev || *u(11,3)!=*u(6,1)) break;
				if(*s(11,5)) goto next_a; // artikel heeft al een code ingevuld
			}
			if(TbEigenArt[listnr_].EAN[0]){
				if(cmpstr(TbEigenArt[listnr_].EAN,s(6,70),cmplen_)==0) {found_=YES;break;}
				if(cmpstr(TbEigenArt[listnr_].EAN,s(6,71),cmplen_)==0) {found_=YES;break;}
			}
			if(TbEigenArt[listnr_].EANStuk[0]){
				if(cmpstr(TbEigenArt[listnr_].EANStuk,s(6,70),cmplen_)==0) {found_=YES;break;}
				if(cmpstr(TbEigenArt[listnr_].EANStuk,s(6,71),cmplen_)==0) {found_=YES;break;}
			}
		}
		if(found_){
			if(CheckInhoud(listnr_)==NO)  goto next_a;
			fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1);mode11_=1;found_=NO;
			FOREVER{ // zoeken naar record met lege code voor deze leverancier 
				if(faskeyi(11,1,mode11_)) break; mode11_=2;
				if(*u(11,2)!=InqLev || *u(11,3)!=*u(6,1)) break;
				if(*s(11,5)=='\0') {found_=YES;break;} // rec11 zonder code 
			}
			if(found_){copy(TbEigenArt[listnr_].Code,s(11,5),fldlen(11,5));errnum=fasupd(11);}
			else{
				fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1);
				copy(TbEigenArt[listnr_].Code,s(11,5),fldlen(11,5));errnum=fasadd(11);
			}
			zero(buf_,sizeof buf_);
			copy(TbEigenArt[listnr_].Code,buf_,10);
			copy(TbEigenArt[listnr_].Naam,&buf_[10],40);
			copy(TbEigenArt[listnr_].Eenheid,&buf_[50],10);
			for(k=1;k<20;k++) prtinfo(k,0);prtline();
		}
	}
	prtclose();
	endsr:;
}


static void KoppelViaEigenArtikel(void)
{

	int16 j,k,z,key,act_nr_,start_=0,nr_,mode_;
	char astr_[20],attr_;
	uint16 via_AKfiche_,add_;


	if(!LoadEigenRef(NO)) goto endsr;
	fasinit(6);

	FOREVER{
    next6:;
    if(faskeyi(6,2,2)) break; 
    if(*pLevFld!=InqLev) goto next6;
		act_nr_=-1; via_AKfiche_=NO;
		if(act_nr_<0 && fldlen(11,5)){// via AK-fiches
			fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1); mode_=1;
			FOREVER{
				if(faskeyi(11,1,mode_)) break; mode_=2;
				if(*u(11,2)!=InqLev) break;
				if(*u(11,3)!=*u(6,1)) break;
				if(*s(11,5)){
					zero(astr_,sizeof astr_);CopyOnlyChar(s(11,5),astr_,fldlen(11,5));
					for(k=0;k<MaxEigenArt;k++){
						if(cmpstrU(TbEigenArt[k].CmpStr,astr_,15)==0) break;
					}
					if(k<MaxEigenArt){
						act_nr_=k; via_AKfiche_=YES;
						break;
					}
				}
			}
		}

		if(act_nr_<0){ // voorstel op EAN
			for(k=0;k<MaxEigenArt;k++){
				if(*s(6,70)){
					if(cmpstr(TbEigenArt[k].EAN,s(6,70),fldlen(6,70))==0) break;
				}
				else if(*s(6,71)){
					if(cmpstr(TbEigenArt[k].EAN,s(6,70),fldlen(6,70))==0) break;
				}
			}
      if(k<MaxEigenArt) act_nr_=k;
		}
		if(via_AKfiche_==NO){
      fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1); 
    	if(faskeyi(11,1,1)==0){
  	 		if(*u(11,2)!=InqLev || *u(11,3)!=*u(6,1)) fasinit(11);
			}
		}

		nr_=0;
		if(act_nr_>=0){
			nr_=act_nr_+1;
		  if(act_nr_<start_ || act_nr_>=(start_+15)) start_=act_nr_;
		}
		FOREVER{
			redo:;
			scrnum=0;scrget(3,6);z=1;
			scrofld(z++,6,3,-1);
			scrofld(z++,11,5,-1);
			scrofld(z++,6,31,-1); scrofld(z++,6,37,-1);
			for(j=start_;j<start_+15;j++){
				if(j>MaxEigenArt) break;
				if((nr_-1)==j) attr_=9; else attr_=0xFF;
				j++;scrifld(z++,fm_ou3,&j);j--;scrchat(z-1,attr_);
				scrifld(z++,VarTextFmt(7,0),TbEigenArt[j].Code);scrchat(z-1,attr_);
				scrifld(z++,VarTextFmt(38,0),TbEigenArt[j].Naam);scrchat(z-1,attr_);
				scrifld(z++,VarTextFmt(7,0),TbEigenArt[j].Eenheid);scrchat(z-1,attr_);
				scrifld(z++,fm_of3_2,&TbEigenArt[j].inhoud);scrchat(z-1,attr_);
				scrifld(z++,fm_of3_2,&TbEigenArt[j].gewicht);scrchat(z-1,attr_);
			}
			scrifld(95,fm_uu3,&nr_);
			key=scrupd(54,0x2A7);
			if(key==101) goto endsr;
			if(key==106) break;
			if(key==110){
				if(via_AKfiche_){zero(s(11,5),fldlen(11,5)); fasupd(11);}
	//			else{zero(s(6,8),fldlen(6,8));	fasupd(6);}
				break;
			}
			if(key==108){
				if(nr_ && nr_<=MaxEigenArt){ // steeds op AKfiche zetten
					if(CheckInhoud(nr_-1)==NO)  goto redo;
					add_=YES;
					if(via_AKfiche_) add_=NO;
					else{
  					fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1); 
    				if(faskeyi(11,1,1)==0){
  		    		if(*u(11,2)==InqLev && *u(11,3)==*u(6,1)) add_=NO;
						}
					}
					if(add_) {fasinit(11);*u(11,2)=InqLev;*u(11,3)=*u(6,1); }
					zero(s(11,5),fldlen(11,5));
					copy0(TbEigenArt[nr_-1].Code,s(11,5),10);
					if(add_) fasadd(11); else fasupd(11);
					 // artikelfiche updaten 
	//				if(*f(6,37)<=0) *f(6,37)=TbEigenArt[nr_-1].inhoud;
	//				if(*f(6,38)<=0) *f(6,38)=TbEigenArt[nr_-1].gewicht;
					if(*s(6,70)=='\0' && cmpstr(TbEigenArt[nr_-1].EAN,s(6,71),fldlen(6,71))) copy(TbEigenArt[nr_-1].EAN,s(6,70),fldlen(6,70));
					else if(*s(6,71)=='\0' && cmpstr(TbEigenArt[nr_-1].EAN,s(6,70),fldlen(6,70))) copy(TbEigenArt[nr_-1].EAN,s(6,71),fldlen(6,71));
					fasupd(6);
					break;
				}
				errnum=38; goto redo;
			}
			if(key==102) start_-=15;
			if(key==103 ) start_+=15;
			if((start_+15)>MaxEigenArt) start_=MaxEigenArt-15;
			if(start_<0) start_=0;
		}
	}
	endsr:;
}

static int LoadEigenRef(int16 LoadArtikels_)
{
	int16 k,n,mode_=0;
	char buf_[100];
  CString line_,cstr_;
  int fn_prod_;
	float hoev_;
	char delim_kar_;


  delim_kar_=CSV_FIELDDELIM;

  if( (fn_prod_= dopen(FILE_EIGEN_ART, O_RDONLY|O_BINARY )) == -1 ){
		sprintf(buf_,"Kan bestand met eigen artikels \'%s\' niet openen!",FILE_EIGEN_ART);
		DisplayWarning(buf_,605,0);
 		return 0;
	}
	zeroL((char *)&TbEigenArt[0].ArtRecs[0],sizeof TbEigenArt);
	line_=Read_Rec(fn_prod_); if(ReadEOFline) goto endsr; // headerlijn
	for(MaxEigenArt=0;MaxEigenArt<MAX_EIGENART;MaxEigenArt++){
    line_=Read_Rec(fn_prod_); if(ReadEOFline) break;
		cstr_=Rec_Ele(line_,0,sizeof TbEigenArt[0].Code,delim_kar_);copy((char *)(LPCTSTR)cstr_,TbEigenArt[MaxEigenArt].Code,cstr_.GetLength()); 
		cstr_=Rec_Ele(line_,1,sizeof TbEigenArt[0].Naam,delim_kar_);cstr_.Replace("'"," ");cstr_.Trim();
		copy((char *)(LPCTSTR)cstr_,TbEigenArt[MaxEigenArt].Naam,cstr_.GetLength()); 
		cstr_=Rec_Ele(line_,3,sizeof TbEigenArt[0].EAN,delim_kar_);copy((char *)(LPCTSTR)cstr_,TbEigenArt[MaxEigenArt].EAN,cstr_.GetLength()); 
		cstr_=Rec_Ele(line_,4,sizeof TbEigenArt[0].Eenheid,delim_kar_);copy((char *)(LPCTSTR)cstr_,TbEigenArt[MaxEigenArt].Eenheid,cstr_.GetLength()); 
		cstr_=Rec_Ele(line_,6,-1,delim_kar_);hoev_=String2Double(cstr_,',');
		cstr_=Rec_Ele(line_,7,2,delim_kar_);
		if(cstr_.CompareNoCase("KG")==0) TbEigenArt[MaxEigenArt].gewicht=hoev_; else TbEigenArt[MaxEigenArt].inhoud=hoev_;
		cstr_=Rec_Ele(line_,8,sizeof TbEigenArt[0].EANStuk,delim_kar_);
		if(cstr_.GetLength()==8 || cstr_.GetLength()==13) copy((char *)(LPCTSTR)cstr_,TbEigenArt[MaxEigenArt].EANStuk,cstr_.GetLength()); 
		CopyOnlyChar(TbEigenArt[MaxEigenArt].Code,TbEigenArt[MaxEigenArt].CmpStr,fldlen(11,5));
	}
endsr:;
  dclose(fn_prod_);

	if(LoadArtikels_){
		fasinit(11); *u(11,2)=InqLev; mode_=1;
		FOREVER{
			next11:;
			if(faskeyi(11,1,mode_)) break; mode_=2;
			if(*u(11,2)!=InqLev) break;
			if(*s(11,5)=='\0') goto next11;
			zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
			for(k=0;k<sizeof buf_;k++) if(buf_[k]=='.') buf_[k]=',';
			for(k=0;k<MaxEigenArt;k++){
				if(cmpstrU(TbEigenArt[k].CmpStr,buf_,sizeof TbEigenArt[0].CmpStr)==0) break;
			}
			if(k>=MaxEigenArt) goto next11; // alleen maar de voorgedefinieerde artikels
			for(n=0;n<10;n++){
				if(TbEigenArt[k].ArtRecs[n]==0){
					TbEigenArt[k].ArtRecs[n]=*u(11,3);
					fasinit(6);*u(6,1)=*u(11,3);fasgeti(6); 
					if(TbEigenArt[k].gewicht && fldlen(6,38)){
						if(*f(6,38)) TbEigenArt[k].ArtInhoud[n]=*f(6,38);
						else TbEigenArt[k].ArtInhoud[n]=TbEigenArt[k].gewicht; // indien gewicht niet ingevuld, dan default Haacht nemen
					}
					else TbEigenArt[k].ArtInhoud[n]=*f(6,37); // inhoud per artikel bijhouden
					break;
				}
			}
		}
	}
	return 1;
}

static void OLDLijstArtikels(void)/* lijst van de gekoppelde artikels */
{
  int16 k,n,z;
	int16 form_dat[8],pr_mode,prtnr;
  char buf_[100];
  float inhoud_,gewicht_;
     
	if(!LoadEigenRef(YES)) goto endsr;

	fasinit(6);
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  prtfld(25,1,-1);prttext("<t33b>");
  prttext("Lijst gekoppelde artikels");
  prttext("<b>");
  prttext("<t122>Blz.<ppp>.");
  prtbuf(1);z=1;
  prtitab(z,VarTextFmt(9,0),buf_,1,-1);prttitle(z++,"Prod.Code",3);
	prtitab(z,VarTextFmt(40,0),&buf_[10],1,-1);prttitle(z++,"Omschrijving",3);
	prtitab(z,VarTextFmt(10,0),&buf_[50],1,-1);prttitle(z++,"Eenheid",3);
	prtitab(z,fm_of4_2,&inhoud_,1,-1);prttitle(z++,"Inhoud",0x13);
	prtitab(z,fm_of4_2,&gewicht_,1,-1);prttitle(z++,"Gewicht",0x13);
  prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
	prttab(z,6,3,1,-1); prttitle(z++,"Artikel(s)",3);
	prttab(z,6,37,1,-1);prttitle(z++,"Inhoud",0x13);
	prttab(z,6,38,1,-1);prttitle(z++,"Gewicht",0x13);
  prtbuf(3);
	p_pdfname("Lijst gekoppelde artikels",*u(25,2),0);
	for(k=0;k<MaxEigenArt;k++){
		zero(buf_,sizeof buf_);
		copy(TbEigenArt[k].Code,buf_,10);
		copy(TbEigenArt[k].Naam,&buf_[10],40);
		copy(TbEigenArt[k].Eenheid,&buf_[50],10);
		inhoud_=TbEigenArt[k].inhoud;
		gewicht_=TbEigenArt[k].gewicht;
		for(n=1;n<6;n++) prtinfo(n,0);
    for(n=0;n<10;n++){
			if(TbEigenArt[k].ArtRecs[n]==0) break;
			fasinit(6);*u(6,1)=TbEigenArt[k].ArtRecs[n]; fasgeti(6);
			prtinfo(6,0);prtinfo(7,0);
			if(*f(6,37)!=inhoud_) prtinfo(8,3); else prtinfo(8,0);
			prtinfo(9,0);
			prtline();
		}
		if(n==0) prtline();
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


static void UpdateSettings(void)
{
  int curs,z,key;
  char lev_prod_;

	sysget(8250,10,Settings.KlantNummer);
	sysget(8260,50,Settings.EmailAdres);
	sysget(8320,2,(char *)&Settings.RecLeverancier);
	sysget(9100,35,Settings.FtpUserID);
	sysget(9135,35,Settings.FtpPaswoord);
	sysget(9170,50,Settings.FtpAdres);
	sysget(9220,2,(char *)&Settings.FtpPoort);
//	sysget(8322,2,(char *)&Settings.EindDatumLastExport);
	fasinit(1);
	lev_prod_='L'; *u(1,1)=Settings.RecLeverancier;
	if(*u(1,1)>30000){lev_prod_='P';*u(1,1)=*u(1,1)-30000;}
	if(*u(1,1)) fasgeti(1);

	curs=1;
  FOREVER {
		redo:; 
    scrnum=0;scrget(3,4);z=1;
		scraddpicto(1,0,1,22,4,2,595,0,0,"annuleer"); scraddpicto(2,0,7,22,4,2,578,0,0,"OK"); scraddpicto(7,0,13,22,4,2,107,0,4,"Herdisplay"); 
		scrifld(z++,fm_us50,Settings.EmailAdres);
		scrifld(z++,fm_us10,Settings.KlantNummer);
		scrifld(z++,fm_uLP,&lev_prod_);
		scrfld(z++,1,3);
		scrifld(z++,fm_us50,Settings.FtpAdres);
		scrifld(z++,fm_uu5,&Settings.FtpPoort);
		scrifld(z++,fm_us35,Settings.FtpUserID);
		scrifld(z++,fm_us35,Settings.FtpPaswoord);
    key=scrupd(curs,0x2A0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106 || key==5001) goto endsr;
		if(key==110) AdjustPOCHorecaTyp();
		if(CheckEmailAdres(Settings.EmailAdres,60,0)==NO){errnum=34;curs=1; goto redo;}
		if(Search(1,0)){curs=4; goto redo;}; // moet ingevuld zijn
    if(key==108 || key==5002) break;
  }
	if(lev_prod_=='P' && *u(1,1)) *u(1,1)+=30000;
	Settings.RecLeverancier=*u(1,1);
	sysput(8250,10,Settings.KlantNummer);
	sysput(8260,50,Settings.EmailAdres);
	sysput(8320,2,(char *)&Settings.RecLeverancier);
	sysput(9100,35,Settings.FtpUserID);
	sysput(9135,35,Settings.FtpPaswoord);
	sysput(9170,50,Settings.FtpAdres);
	sysput(9220,2,(char *)&Settings.FtpPoort);
endsr:;
	sysget(8250,10,Settings.KlantNummer);
	sysget(8260,50,Settings.EmailAdres);
	sysget(8320,2,(char *)&Settings.RecLeverancier);
	sysget(9100,35,Settings.FtpUserID);
	sysget(9135,35,Settings.FtpPaswoord);
	sysget(9170,50,Settings.FtpAdres);
	sysget(9220,2,(char *)&Settings.FtpPoort);
//	sysget(8322,2,(char *)&Settings.EindDatumLastExport);
	pLevFld=u(6,7); InqLev=Settings.RecLeverancier;
	if(fldlen(6,101) && InqLev>30000){pLevFld=u(6,101);InqLev-=30000;} // merk/producent
}

//static void AdjustPOCHorecaTyp(void)
//{
//	int z,key;
//	char type_;
//
//	fasinit(2);
//	FOREVER{
//		redo:;
//		scrnum=0; scrget(3,2);z=1;
//		scrfld(z++,2,3);
//		if(*u(2,1)) scrifld(z++,fm_uBV,s(2,132)); else scrofld(z++,2,132,-1);
//		key=scrupd(1,0x2C1);
//	  if(key==101) break;
//		if(key==110){LijstVerplichteKlanten(); fasinit(2);goto redo;}
//		type_=*s(2,132);
//		if(key==108 && *u(2,1)){
//   		fasgeti(2);*s(2,132)=type_;fasupd(2);
//			fasinit(2);
//			goto redo;
//		}
//		errnum=Search(2,0);
//	}
//}

static void AdjustPOCHorecaTyp(void)
{
	int16 key,z,start_;
	char SearchField[200];
  char FullRecDens[3000],sel_prijstype_='\0',sel_soortklant_='\0',sel_geblokkeerd_='\0';
  int k,FullRecDensLen=0,check_actief_,fkey_=2;

	memset(SearchField,0,sizeof SearchField);  
	fasinit(2);
	FOREVER{
		redo:;
		scrnum=0;scrget(3,10);z=1;
		scrifld(z++,VarTextFmt(40,1),SearchField);
		scrifld(z++,fm_us1_U,&sel_prijstype_);
		if(fldlen(2,54)) scrifld(z++,fm_us1_U,&sel_soortklant_); else z++;
		if(fldlen(2,132)) scrifld(z++,fm_uBJ,&sel_geblokkeerd_); else z++;
		key=scrupd(1,0x81);
	  if(key==101) break;
		scrget(1,7);scrupd(-3,0);
		memset(TbKlant,0,sizeof TbKlant); MaxKlt=0;
		GetSearchKeyWords(SearchField);
		fasinit(2);
		FOREVER {
			nextklt:;
			if(faskeyi(2,2,2)) break;
			if(sel_prijstype_ && *s(2,26)!=sel_prijstype_) goto nextklt;
			if(sel_soortklant_ && *s(2,54)!=sel_soortklant_) goto nextklt;
			if(*s(2,132)!='B') {*s(2,132)='J'; fasupd(2);}
			if(sel_geblokkeerd_ && *s(2,132)!=sel_geblokkeerd_) goto nextklt;
			FullRecDensLen=MakeFullRecDens(2,FullRecDens);
			if (AllKeywordsFound(FullRecDens,FullRecDensLen)==NO) goto nextklt;
			if(fldlen(16,1)){ // minstens laatste jaar afgenomen hebben
				fasinit(16);*l(16,10)=*u(2,1); *u(16,3)=*u(25,2)-365;
				if(faskeyi(16,4,1)) goto nextklt;
				if(*l(16,10)!=*u(2,1)) goto nextklt;
			}
			TbKlant[MaxKlt].RecordNr=*u(2,1);// record voldoet
			TbKlant[MaxKlt].Bcode=*s(2,132); 
			if(fldlen(2,136)) TbKlant[MaxKlt].HaachtKlantNr=*s(2,136); 
			MaxKlt++;
			if(MaxKlt>=DIM_KLANT) break; // tabel vol
		}
		if(MaxKlt==0) {errnum=39;goto redo;}
		start_=0;
		FOREVER{  // .used wil hier zeggen geblokkeerd!
			scrnum=0;scrget(3,11);z=1;
			start_++;scrifld(z++,fm_ou4,&start_);start_--; scrifld(z++,fm_ou4,&MaxKlt);
			scraddpicto(5,0,76,22,4,2,593,0,0,"Blokkeer allen");
		  scraddpicto(6,0,72,22,4,2,578,0,0,"Deblokkeer allen");
			for(k=start_;k<start_+20;k++){
				if(k>=MaxKlt) break;
				fasinit(2);*u(2,1)=TbKlant[k].RecordNr; fasgeti(2);
				DisplayLine(z++);
				if(TbKlant[k].Bcode!='B') {scraddpicto(10+k-start_,0,77,2+k-start_,2,1,593,0,0,"Blokkeer");}
				else {scraddpicto(10+k-start_,0,1,2+k-start_,2,1,578,0,0,"Deblokkeer");}
				if(fldlen(2,136)){
					if(TbKlant[k].HaachtKlantNr) {scraddpicto(30+k-start_,0,3,2+k-start_,2,1,64,0,4,"KlantNr Haacht");}
				  else {scraddpicto(30+k-start_,0,3,2+k-start_,2,1,64,0,0,"KlantNr Haacht");}
				}
				if(TbKlant[k].Bcode=='B') scrchat(z-1,0xB);
				else if(TbKlant[k].Bcode=='V') scrchat(z-1,0x9);
				else scrchat(z-1,0xFF);
			}
			key=scrupd(-1,0x07);
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key>=5010 && key<5050){
			  if(key>=5010 && key<5030){ // blokkeer / deblokkeer
				  k=start_+key-5010;
					if(TbKlant[k].Bcode=='B') TbKlant[k].Bcode='J'; else TbKlant[k].Bcode='B';
				}
			  else if(key>=5030 && key<5050){ // verplicht Haacht
				  k=start_+key-5030;
					AskKlantNr(k);
				}
				fasinit(2);*u(2,1)=TbKlant[k].RecordNr;fasgeti(2);
				*s(2,132)=TbKlant[k].Bcode; fasupd(2);
			}
      if(key==5005 || key==5006){
				for(k=start_;k<start_+20;k++){
					if(k>=MaxKlt) break;
					if(key==5005) TbKlant[k].Bcode='B'; else TbKlant[k].Bcode='J';
					fasinit(2);*u(2,1)=TbKlant[k].RecordNr;fasgeti(2);
					*s(2,132)=TbKlant[k].Bcode;	fasupd(2);
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

static void AskKlantNr(int16 nr_)
{
	int16 z,key;

	fasinit(2);*u(2,1)=TbKlant[nr_].RecordNr; fasgeti(2);
	FOREVER{
		redo:;
		scrnum=0;scrget(3,31);z=1;
		scrofld(z++,2,3,-1);
		scrofld(z++,2,4,-1);
		scrofld(z++,2,5,-1); scrofld(z++,2,6,-1);
		scrfld(z++,2,136);
		key=scrupd(5,0xA0);
		if(key==108){
			fasupd(2);
			TbKlant[nr_].HaachtKlantNr=*s(2,136);
		}
		if(key==106 || key==108) break;
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
  int16 k,z,key;
	int16 form_dat[8],pr_mode,prtnr;
  char inq_type_='J',*ptitel_,kar_;

	FOREVER{
		redo:;
		scrnum=0; scrget(3,8);z=1;
		scrifld(z++,fm_uBJ,&inq_type_); 
		key=scrupd(1,0x2C1);
	  if(key==101) goto endsr;
		if(inq_type_!='B' && inq_type_!='J') {errnum=34; goto redo;}
		if(key==108) break;
	}
	if(inq_type_=='B') ptitel_="Lijst geblokkeerde POC's"; else ptitel_="Lijst te exporteren POC's";
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  prtfld(25,1,-1);prttext("<t33b>");prttext(ptitel_);  prttext("<b>");  prttext("<t122>Blz.<ppp>.");
  prtbuf(1);z=1;
  prttab(z,2,1+klcd,1,-1); prttitle(z++,"Code",3);
	prttab(z,2,136,3,-1); prttitle(z++,"HaachtNr",3);
  prttab(z,2,3,2,-1); prttitle(z++,"Naam",3);
  prttab(z,2,4,1,-1); prttitle(z++,"Straat",3);
  prttab(z,2,5,1,-1); prttitle(z++,"Postnr.",3);
  prttab(z,2,6,1,-1); prttitle(z++,"Gemeente",3);
  prtbuf(3);
	p_pdfname(ptitel_,*u(25,2),0);
	fasinit(2);
	FOREVER{
		nextklt:;
		if(faskeyi(2,2,2)) break;
		if(*s(2,132)!='B'){
			kar_=*s(2,132);
			*s(2,132)='J';
		}
		if(*s(2,132)==inq_type_){
			if(fldlen(16,1)){ // minstens laatste jaar afgenomen hebben
				fasinit(16);*l(16,10)=*u(2,1); *u(16,3)=*u(25,2)-365;
				if(faskeyi(16,4,1)) goto nextklt;
				if(*l(16,10)!=*u(2,1)) goto nextklt;
			}
			for(k=1;k<10;k++) prtinfo(k,0);prtline();
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
	int16 mm,dd;
	  
	sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
	sysget(3876,2,&sys3876);
	sysget(3896,6,sys3896);

	sysget(8250,10,Settings.KlantNummer);
	sysget(8260,50,Settings.EmailAdres);
	sysget(8310,1,&Settings.Versie2023);
	sysget(8320,2,(char *)&Settings.RecLeverancier);
	sysget(8322,2,(char *)&Settings.LastMaand); 
	sysget(8324,2,(char *)&Settings.LastJaar);
	sysget(9100,35,Settings.FtpUserID);
	sysget(9135,35,Settings.FtpPaswoord);
	sysget(9170,50,Settings.FtpAdres);
	sysget(9220,2,(char *)&Settings.FtpPoort);

	jddate(*u(25,2),&ThisYear,&mm,&dd);


	pLevFld=u(6,7); InqLev=Settings.RecLeverancier;
	if(fldlen(6,101) && InqLev>30000){pLevFld=u(6,101);InqLev-=30000;} // merk/producent
//	sysget(8322,2,(char *)&Settings.EindDatumLastExport);

	klcd=0;if(fldlen(2,2)) klcd=1;
	InitConvertTab();
	copy("-X|/",dsp_kar,4);dsp_kar[1]=0x5C;
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
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy("Haacht Datagathering",MailMergeData[k],20); continue;}
		if(cmpstr(MailMergeKeywords[k],"CONTACTPERSOON",14)==0){copy(s(25,1),MailMergeData[k],fldlen(25,1)); continue;}
		if(cmpstr(MailMergeKeywords[k],"PERIODE",7)==0){
//			cstr_=Date2String(DatBeg,0);cstr_+=" - ";cstr_+=Date2String(DatEnd,0);
//			copy((char *)(LPCTSTR)cstr_,&MailMergeData[k][0],cstr_.GetLength()); 
			stcli_d(&MailMergeData[k][0],(long)InqMaandBeg,2,0);MailMergeData[k][2]='/';
			stcli_d(&MailMergeData[k][3],(long)InqJaar,4,0);
			continue;
		}
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
	copy("HAACH",MailMergeSpecialTemplate,5); // vaste template 

	MailMergeFormaat=5; 
	k=SendMail(SendMode); 
	if(k && MailSaveAdres=='J'){
		copy0(MailMergeData[p_adr_],(char *)&Settings.EmailAdres,60); // email adres bewaren
	  sysput(8260,50,(char *)&Settings.EmailAdres);
  }
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


