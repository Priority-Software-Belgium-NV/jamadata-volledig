/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* DRK2291GetD() {return &zzvw;}
extern "C" int BibiFileUpdated(char* System,char* UserName,char* PassWord,char* FileName,char* DestPath);
extern "C" int BibiDownload(char* System,char* UserName,char* PassWord,char* FileName,char* DestPath);
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" int DirCall_DRK2215_SelectArtikel(void);
extern "C" int Fld2String(int stunr, int fldnr, char *OutBuffer, int MaxLen);
extern "C" void ExecJmsCommand(char* buf, int buflen, char* pCommand);
extern "C" void GetFileFromServer(char *FileName);
extern "C" int GetFileFromSelection(char *ptitel_,char *pselection_); // result komt in SelectedFileName
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" void CnvJamaChar(char *pString,int16 MaxLen,int16 CnvMode);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
extern "C" int CheckForFreeSpace(int StuNr, long MinFree);
extern "C" int16 Search(int stu_,int mod_);
extern "C" char *VarTextFmt(int len_,int update_);

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
 
static int16 ovlcall();
__declspec(dllimport) unsigned char PrintPaperNr;

extern "C" char DRK2291dat[] = "drk2291  00:22 21/10/10 (c) Jamadata"; // Prik&tik modules (V.2.P)

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DF_GRB          15
#define DIM_BEWLIJN     750
#define DIM_TB          200
#define MAX_RECS        2500
#define MINFREE         200
#define MAXFLD          100
#define DIMBTW          8
#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */
#define CSV_FIELDDELIM		  '\x09' // ","

#define PROMO_PRX_FILE  "Folder.TXT"
#define PROMO_PRX_MAP   "..\\Div\\"
#define PROMO_BIBI_MAP  "PRIKTIK"


#define PT_PRX_FILE  "PnTartikel.TXT"
#define PT_PRX_MAP   "..\\Div\\"
#define PT_BIBI_MAP  "PRIKTIK"
    
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
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us10[]  = {7,0xC8,10,0,0,0,0};
static char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x91,5,0,0x60,0};
static char fm_ou3[]   = {6,0x91,3,0,0x60,0};
static char fm_ou2[]   = {6,0x91,2,0,0x60,0};
static char fm_uu5[]   = {6,0xD1,5,0,0x70,0};
static char fm_uu3[]   = {6,0xD1,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD1,2,0,0x60,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_of2_1[] = {6,0x94,2,1,0x70,0};
static char fm_uf42_[] = {6,0xD4,4,2,0x60,0};
static char fm_uf4_0[] = {6,0xD4,4,0,0x70,0};
static char fm_uf2_3[] = {6,0xD4,2,3,0x70,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_od21_[] = {6,0x95,2,1,0x20,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_od4_2[] = {6,0xD5,4,2,0x70,0};
static char fm_of5_3[] = {6,0x94,5,3,0x60,0};
static char fm_of4_2[] = {6,0x94,4,2,0x70,0};
static char fm_of4_0[] = {6,0x94,4,0,0x70,0};
static char fm_of4_3[] = {6,0x94,4,3,0x60,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_of42_[] = {6,0x94,4,2,0x60,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_obd[]   = {6,0x95,6,2,0x70,0};                             /* od6_2 */
static char fm_ubd[]   = {6,0xD5,6,2,0x70,0};                             /* ud6_2 */
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_uGNB[]= {13,0xC8,1,0,0x09,0,'G','G','N','N','B','B',0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ugrb[]  = {2,0xE8};
static char fm_us10PW[] = {7,0xC8,10,0,4,0,0};

static bool ReadEOFline;
static int16 prt2pdf,BewCount,tb_kprx[6],max_kprx;
static char seqo_str[500],sys3896[6],fmt[40],ScheidingsTeken='\x09',SelectieEenheid[10],DateLastDownload[20];
static char filnam[100],def_munt[4], JamaPromoFile[40];
static char dsp_kar[5],SkipGekoppeld,AdjustOnlyEmpty,AdjustAkPrijs;
static char lev_res[60],klt_res[60],art_res[60],FTPUsername[15],FTPPaswoord[15];
static long seqo_pos,value,ok_pos,dsp_count;
static int16 seqo_len,seqo_mode,pos,kdsp,AantalArtikelsInFile;
static uint16 dat_beg,dat_end,inq_lev=0,dt_NewPrijs,Accijnsverhoging;
static flag sys3894,sys2982;
static flag sear_stt,sys3876;
static uint16 recs_used,DateFolderBegin,DateFolderEnd;
static uint16 recs[MAX_RECS];
static char recs_preferred[MAX_RECS];
static float ItmVol, ItmCnt, HandlingKost;
static CString VolSearchString;

static struct{
	char code[20]; // A
	char omschrijving[50]; // B
	char verpakking[50]; // C
	char eenheid[10]; // D
	float btw_pct; // E
	float accijns; // F
	float ecotaks; // G
	float prijs; // H
	float leeggoed; // I
	char eanbak[20];  // J
	char eanstuk[20]; // K
} PnTlijn;

static struct{
	uint16 dt_beg;
	uint16 dt_end;
	float prijs;
	float kassaprijs[6];
	char promotekst[50];
	char ean[20];
	char promocode;
	uint16 promoformule;
} folderlijn;

static struct{
	char Omschrijving[25];
	char Formule;
	char SelBakFles;
	float Getallen[4];
	char dummy[2]; // totaal 45 bytes
} PromoFormule[20];

static struct _Settings {
	char MapPrijslijst[35];
	uint16 RecLeverancier; // >30000 = merk/producent
	char TariefPrijsAlsBasis;
	char MapLeverFiles[51];
} Settings;

static struct {
	char Code[25];
	char Naam[50];
	char Promotie[50];
	char Verpakking[40];
	char Eenheid[10];
  char EAN[20];
	char CmpStr[25];
  uint16 PrijsDatum;
  uint16 PromoStart;
  uint16 PromoStop;
	float AKprijs;
	float BTWpct;
	float VKprijs;
	float Accijns;
	char AccijnsGroep[10];
	float EcoTax;
	float ZwerfvuilTax;
	float FostPlus;
	char EcoGroep[10];
	float Leeggoed;
	float AantalBak;
	float AfwijkendAantal;
	float Inhoud;
	float Gewicht;
	float GradenPlato;
	float AlcoholGehalte;
  float HandlingKost;
  uint16 ArtRec;
  uint16 ArtDatum;
	float  ArtAKprijs;
	float ArtLevAKprijs;
	float ArtVKprijs;
	float ArtAantalBak;
	float ArtInhoud;
	float ArtGewicht;
  int16  Done;
  int16  UserChanged;
	uint16 PromoRec;
} BewLijn[DIM_BEWLIJN];

/* --------------------------- Declaratie functies ---------------------- */
static char *Asc2Jasc(char *ps_,int16 len_);
static int copy0(char *ps,char *pd,int max);
static int CheckInhoud(int listnr_); // controleer inhoud
static bool CheckKeyWord(char *keyword);
static int16 Copy2ZoekStr(char *ps3_,char *zoekstr, uint16 len3_,uint16 lenz_);
static int CopyOnlyChar(char *ps, char *pd, int16 len_);
static void ConvertKortingToHandlingkost(void); // eenmalig negatieve korting invullen als handlingkost en wissen
static int16 cmpstrU(char *p1,char *p2,int16 len);
static double Round(double getal, double round);
static int DisplayFolderFile(char *prijsfilename_);
static int DisplayPrijsFile(char *prijsfilename_);
static int DisplayWarning(char *ptxt, int icoon);
static int16 ele_len(int16 nr_);
static int16 ExecSearch(int16 mode_);
static void fileopen(int16 nr_);
static float FindVolAndCntFromName(char* Name, char* Ean, float ArtVol, float ArtCnt);  // return zit in globale float var ItmCnt en ItmVol
static void FillHandlingKost(void); // eenmalig invullen handlingkost
static int fmt_get(int16 stu_, int16 elet_);
static void FolderUpdateViaFile(void);
static uint16 GetAKFiche(uint16 arec_,uint16 lrec_,uint16 dt_beg_);
static uint16 get_date(int16 nr);              /* read date DD/MM/JJJJ starting at pos  */
static int GetFolderInfo(void);
static float get_num(int16 nr);
static void initload(void);
static int is_nul(double bd_);
static int KoppelArtikel(int listnr_,int DoSelect_); // zoek/koppel P&T-artikel 
static void nextline(void);
static void PdfPrijsFile(char *prijsfilename_);
static void PdfPromoFile(char *prijsfilename_, int16 soortlijst_); // soortlijst_ : 0=prijslijst, 1=kassafolder lijst 
static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_);
static void PrijsUpdateViaFile(void);
static bool ReadFolderFile(char *prijsfilename_) ;
static bool ReadPrijsFile(char *prijsfilename_);
static int16 read_rec(int16 mode_);
static char *rec_ele(int16 nr_);
static int16 SelectPromoFormule(void);
static int UpdateArtikel(int bew_nr_);
static int UpdateKassaPromo(int bew_nr_);
static void UpdateLoginInfo(void);
static void UpdateSettings(void);


////  SIF-File routines
static CString Fld2CString(int stu_,int fld_);
static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_);
static uint16 String2Date(CString S);  // date DD/MM/JJJJ 
static double String2Getal(CString S,char decim_kar);
static double String2Double(CString S){return String2Getal(S,',');}
static double String2Double(CString S,char decim_kar){ return String2Getal(S,decim_kar);}
static int String2Int(CString S){return (int)(String2Getal(S,','));}
static CString Double2String(double getal,long mode); // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
static CString Date2String(unsigned int date_,int mode_);
static CString Read_Rec(int f_nr_);
static CString Rec_Ele(CString s, int kol_, int maxlen_, char delim_kar_=CSV_FIELDDELIM);
//static CString Rec_Ele(CString s, int kol_, int maxlen_, char delim_kar_=CSV_FIELDDELIM);
//////////////////////////////////////

///// XLS-FUNC 
extern int16 ilength; // XLS
static int XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol,XlsMaxKol,XlsMaxRij;
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



/* ---------------------------------------------------------------------- */

extern "C" void DRK2291cod(void)
{
	int16 curs=1,key,z;
  char choice;
	  
  initload();
	if(sys2982==0 && ovltest(2397)==0){
		FolderUpdateViaFile();
		goto endsr;
	}

  FOREVER{
		redo:;
    scrnum=0;scrget(3,8);z=1;fasunlck(0);
		scraddpicto(50,0,78,11,2,1,105,1,7,"^!B2291B");
		scraddpicto(1,0,76,22,4,2,59,0,4,"Parameters");
		if(ovltest(2397)) scraddpicto(9,0,72,22,4,2,581,0,0,"Prik&Tik module");
	  scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x01);
   if(key==101) goto endsr;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(Settings.RecLeverancier==0 || key==5001){ UpdateSettings();goto redo;}
		if(key==5050) goto redo; // link help 
		fasunlck(-1);
		if(key==5009){ ovlcall(2397,0);goto redo;}
    switch(choice){
      case '1': FolderUpdateViaFile(); break; // kassapromo's
      case '2': if(sys2982) PrijsUpdateViaFile(); else errnum=34; break; // prijsupdates
      case 'X': FillHandlingKost(); break;
      case '%': ConvertKortingToHandlingkost(); break;
      default : errnum=34; break;
    }
  }

	endsr:;
  fasclos(-2);
  ovlexit(-1);
}




static void PrijsUpdateViaFile(void) 
{
	int k;
	char str_selectie_[100];

	zero(str_selectie_,sizeof str_selectie_);
	k=copy0(Settings.MapPrijslijst,str_selectie_,30); k+=copy0("*.XLS*",&str_selectie_[k],6);
	FOREVER{
  	if(GetFileFromSelection(" Prijslijsten van Prik&Tik ",str_selectie_)==0) break;
  	if(ReadPrijsFile(SelectedFileName)) DisplayPrijsFile(SelectedFileName);
	}
}
 
#include <iostream>
#include<Windows.h>
#include<string>
#include<Urlmon.h>


static void FolderUpdateViaFile(void)
{
  int16 key,k,len_,mode_,curs=1,z,fl_update=YES;
	int16 form_dat[8],pr_mode,prtnr;
  uint16 inq_lev=0,promo_nr_;
  HRESULT res;
	  
	// A=datum begin, B=datum einde, C=code, D=omschrijving, E=prijs, F=promotekst, G=promo-EAN
	DateFolderBegin=0;DateFolderEnd=0; zero(DateLastDownload, sizeof DateLastDownload);	pl_80_1=l(80,1);  p_data=s(80,1)+4;
	zero(JamaPromoFile,sizeof JamaPromoFile); 
	k=copy0(PROMO_PRX_MAP,JamaPromoFile,sizeof JamaPromoFile);copy0(PROMO_PRX_FILE,&JamaPromoFile[k],sizeof JamaPromoFile-k);
	CString dwnld_URL = "http://folderpnt.prsw.be/downloads/folder.txt";
	//CString dwnld_URL = "http://folderpnt.prsw.be";
  CString savepath = PROMO_PRX_MAP; savepath+= PROMO_PRX_FILE;   /// "C:\\tmp\\filename.txt";

	res=URLDownloadToFile(NULL, dwnld_URL, savepath, 0, NULL);
	GetFolderInfo();

	//fl_update = BibiFileUpdated(PROMO_BIBI_MAP,FTPUsername,FTPPaswoord,PROMO_PRX_FILE,PROMO_PRX_MAP);
  
	//fasclos(-2);fasinit(80);
	//fasopen(JamaPromoFile,102);/* eerste call voor dir */
	//fasinfo(80,204);/* ophalen antwoord van dir */
	//if(*s(80,1)){
	//	fasinit(80);fasinfo(80,205);/* get date  */
	//} else fasinit(80);
	//copy(s(80,1),date_last_download,20);
	//fasclos(-2);
	sysget(2942,2,(char *)&inq_lev); fasinit(1); if(inq_lev){*u(1,1)=inq_lev;fasgeti(1);}
  FOREVER{
		redo:;
    scrget(2,350);z=1;
		scraddpicto(1,0,65,9,4,2,60,0,4,"Ophalen folder"); // "^!PRIKENTIK");
		scraddpicto(2,0,76,22,4,2,59,0,4,"Parameters");
    scrfld(z++,1,3);
		scrifld(z++,VarTextFmt(20,0),DateLastDownload);
		scrifld(z++,fm_odat,&DateFolderBegin); scrifld(z++,fm_odat,&DateFolderEnd); 
    key=scrupd(curs,0x81);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){ // folder.txt downloaden 
			URLDownloadToFile(NULL, dwnld_URL, savepath, 0, NULL);
	    GetFolderInfo();
//		  k = BibiDownload(PROMO_BIBI_MAP,FTPUsername,FTPPaswoord,PROMO_PRX_FILE,PROMO_PRX_MAP);
//			if(k==1){
//        fl_update=NO;
//				fasclos(-2);fasinit(80);
//				fasopen(JamaPromoFile,102);/* eerste call voor dir */
//				fasinfo(80,204);/* ophalen antwoord van dir */
//				if(*s(80,1)){
//					fasinit(80);fasinfo(80,205);/* get date  */
//				} else fasinit(80);
//				copy(s(80,1),date_last_download,20);
//				fasclos(-2);
//			}
//			else{
//				 scrget(1,170);scrifld(10,fm_os63,"Ophalen folder NIET gelukt, druk op F8 om verder te gaan");scrchat(14,0x3);
//				 scrupd(-1,0x81); 
////				 con_derr("Hallo");
//			}
			goto redo; 
		}
		if(key==5002){UpdateLoginInfo(); goto redo;}
    if(key==101) goto endsr;
		if(JamaPromoFile[0]=='\0'){curs=1;errnum=38; goto redo;}
		fasclos(-2);if(fasopen(JamaPromoFile,1)!=0) {errnum=1;curs=1;goto redo;}
		if(Search(1,0)){curs=1;goto redo;}
		inq_lev=*u(1,1);
		if(key==108) break;
  }
	sysput(2942,2,(char *)&inq_lev);
	if(ReadFolderFile(JamaPromoFile)) DisplayFolderFile(JamaPromoFile);
	endsr:;
}

static int GetFolderInfo(void)
{
	int k,mode_;

	DateFolderBegin=0;DateFolderEnd=0; zero(DateLastDownload, sizeof DateLastDownload);

	fasclos(-2);fasinit(80);
	fasopen(JamaPromoFile,102);/* eerste call voor dir */
	fasinfo(80,204);/* ophalen antwoord van dir */
	if(*s(80,1)){
		fasinit(80);fasinfo(80,205);/* get date  */
	} else fasinit(80);
	copy(s(80,1),DateLastDownload,20);
	fasclos(-2);
	if(fasopen(JamaPromoFile,1)!=0) {errnum=1;return NO;}
	fasinit(80);mode_=0;

	for(k=0;k<5;k++){
	  next:;
    if(read_rec(mode_)) break; mode_=1;
		CnvJamaChar(p_data,256,1); // convert2 JamaAscii
		DateFolderBegin=get_date(0);if(DateFolderBegin==0) goto next; 
		DateFolderEnd=get_date(1);if(DateFolderEnd==0) goto next; 
		break;
	}
  fasclos(-2);
	return YES;
}

static int DisplayFolderFile(char *prijsfilename_) // promofolder P&T
{
  int16 nr_,ret_,k,key,z,start_,lijnpos,q_,ScreenLines=15,curs_=2;
	unsigned short mst_art_,pr_rec_,firsttime_,mode_,funckeys;
	char attrib_;
	CString cstr_;
	
	for(k=0;k<BewCount;k++){
		if(BewLijn[k].PromoRec) continue;
		if(BewLijn[k].ArtRec==0) continue;
		fasinit(93); *u(93,7)=BewLijn[k].PromoStart;*u(93,8)=BewLijn[k].PromoStop;*u(93,2)=BewLijn[k].ArtRec;
		if(faskeyi(93,7,0)==0) BewLijn[k].PromoRec=*u(93,1);
	}

	curs_=-1;
  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
		redo:;
    scrnum=0; scrget(3,14); z=1;q_=0; funckeys=0x60E1;
		scraddpicto(3,0,72,22,4,2,583,0,0,"Maak PDF"); 
		cstr_=CString(prijsfilename_); k=cstr_.ReverseFind('\\'); if(k>=0) cstr_=cstr_.Mid(k+1);scrifld(z++,VarTextFmt(35,0),(char *)((LPCTSTR)cstr_));
		z+=2; // {scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);}
	  start_++;scrifld(z++,fm_ou3,&start_);start_--;scrifld(z++,fm_ou3,&BewCount);
		if(start_>0){ funckeys+=2; scraddpicto(1,0,76,1,4,2,18,0,4,"up"); }
		if((start_+ScreenLines)<BewCount) {funckeys+=4;scraddpicto(2,0,76,22,4,2,13,0,4,"down"); }
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=BewCount) break;
			attrib_=0xFF; if(BewLijn[k].ArtRec==0) attrib_=0x0B;
			scrifld(z++,VarTextFmt(35,0),BewLijn[k].Naam); scrchat(z-1,attrib_);
			scrifld(z++,VarTextFmt(29,0),BewLijn[k].Promotie); if(BewLijn[k].PromoRec) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
			scrifld(z++,fm_of42_,&BewLijn[k].VKprijs); if(BewLijn[k].PromoRec) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
			if(BewLijn[k].ArtRec) scraddpicto(11+k-start_,z-1,1,0,2,1,112,0,4,"Pas promo aan"); 
			scraddpicto(11+ScreenLines+k-start_,z-1,3,0,2,1,69,0,4,"Koppel artikel"); 
	  }
//		if(soortlijst_==0) {scraddf(z,23,40,8);scrifld(z++,VarTextFmt(26,0)," F10 pas ALLE prijzen aan ");}
    key=scrupd(curs_,0x2FF); curs_=-1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;

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
			case 101     : return false; 
										 break;
			//case 106     : for(k=0;k<BewCount;k++) if(BewLijn[k].UserChanged) break;
			//							 if(k<BewCount){
			//								 if(DisplayWarning("Wenst u echt de ingebrachte wijzigingen te annuleren?",605,1)==NO) goto redo;
			//							 }
			//							 return false;
			//							 break;


//			case 18      :// ENTER 
//			case 15      : // TAB  
			//case 18     : if(nr_>BewCount) errnum=34;// neem aan en exit 
			//							else{
			//								if(nr_>0) DetailBeweging(p_tbcoda_,nr_-1); 
  	//								 }
			//							 break;
			default      : break;
    }
		if(key==110){ // manueel (groeps) promotie toevoegen 
			fasinit(93);
			*u(93,7)=BewLijn[0].PromoStart; *u(93,8)=BewLijn[0].PromoStop;
			ovlcall(295,2);
		}

		if(key>=5011 && key<5011+ScreenLines){
			nr_=key-5011+start_;
redo_updpromo:;
			fasinit(6); *u(6,1)=BewLijn[nr_].ArtRec;fasgeti(6);
			fasinit(93); *u(93,1)=BewLijn[nr_].PromoRec; if(*u(93,1)) fasgeti(93);
			ret_=UpdateKassaPromo(nr_);
			if(ret_){ // F2, F3 of F8 
				if(fldlen(6,102) && *u(6,102)==0){ // kijken naar deelverpakkingen
					mst_art_=*u(6,1); pr_rec_= BewLijn[nr_].PromoRec;
					fasinit(6);*u(6,102)=mst_art_;mode_=1; firsttime_=YES;
					FOREVER{
						next_clip:;
						if(faskeyi(6,15,mode_)) break; mode_=2;
						if(*u(6,102)!=mst_art_) break;
						if(firsttime_){
							if(DisplayWarning("Wenst U ook deze promo ook op de deelverpakkingen (clips) toe te passen?",605,1)==NO) break;
							firsttime_=NO;
						}
						fasinit(93); // zelf zoeken naar bestaande promo
						UpdateKassaPromo(nr_);
					}
					BewLijn[nr_].PromoRec=pr_rec_; // origineel terugzetten 
				}
				if(ret_==2){ // F2 vorig genomen 
					for(k=nr_-1;k>=0; k--) if(BewLijn[k].ArtRec) break;
					if(k>=0) nr_=k;
					goto redo_updpromo;
				}
				if(ret_==3){ // F2 volgend genomen 
					for(k=nr_+1;k<BewCount; k++) if(BewLijn[k].ArtRec) break;
					if(k<BewCount) nr_=k;
					goto redo_updpromo;
				}
			}
			if(nr_<start_ || nr_>=start_+ScreenLines){
				start_=nr_;
				lijnpos=0;scrnum=0;
			}
		}
		if(key>=5011+ScreenLines && key<5011+ScreenLines*2) KoppelArtikel(key-5011-ScreenLines+start_,YES);
		for(k=0;k<BewCount;k++){
			if(BewLijn[k].PromoRec) continue;
			if(BewLijn[k].ArtRec==0) continue;
			fasinit(93); *u(93,7)=BewLijn[k].PromoStart;*u(93,8)=BewLijn[k].PromoStop;*u(93,2)=BewLijn[k].ArtRec;
		  if(faskeyi(93,7,0)==0) BewLijn[k].PromoRec=*u(93,1);
		}
		if(key==5003) PdfPromoFile(prijsfilename_,1);
		//if(key==108){
		//	for(k=0;k<BewCount;k++) if(BewLijn[k].BkhOK==NO) break;
		//	if(k<BewCount)errnum=73;
		//	else break;
		//}
	}
	return true;
}

static void PdfPromoFile(char *prijsfilename_, int16 soortlijst_) // soortlijst_ : 0=prijslijst, 1=kassafolder lijst 
{
  int16 k,n,z,attr_;
	int16 form_dat[8],pr_mode,prtnr;
  char buf_[110];
	uint16 l_dt_,a_dt_;
  float inhoud_,gewicht_,l_ap_,a_ap_,verschil_;
	CString cstr_;
	
	fasinit(6);
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,150,pr_mode,4))!=0) goto endsr;
	prtfld(25,1,25); prttext("  Prijzenbestand : ");
	cstr_=CString(prijsfilename_); k=cstr_.ReverseFind('\\'); if(k>=0) cstr_=cstr_.Mid(k+1);
	prtifld(VarTextFmt(35,0),(char *)((LPCTSTR)cstr_),-1);
  prttext("<t92>");prtfld(25,2,-1);prttext("<t120>Blz.<ppp>.");
  prtbuf(1);
	if(soortlijst_==0){
	  prttext("<t28>Ingangsdatum : ");prtifld(fm_udat,&dt_NewPrijs,-1);prtbuf(2);
	}
	//else{
	//	prttext("<t28>Promoperiode : ");prtifld(fm_udat,&dat_beg,-1); prttext(" - ");prtifld(fm_udat,&dat_end,-1);prtbuf(2);
	//}
	z=1;

	//prtitab(z,VarTextFmt(14,0),&buf_[50],1,-1);prttitle(z++,"Verpakking",3);

	if(soortlijst_==0){
		prtitab(z,VarTextFmt(7,0),buf_,1,-1);prttitle(z++,"Code",3);
		prtitab(z,VarTextFmt(35,0),&buf_[10],1,-1);prttitle(z++,"Omschrijving Prik&Tik",3);
	  prttab(z,6,3,1,-1); prttitle(z++,"Artikel",3);
		prtitab(z,fm_of5_3,&l_ap_,1,-1);prttitle(z++,"Lid-prijs",0x13);
		prtitab(z,fm_of5_3,&a_ap_,2,-1);prttitle(z++,"Art.prijs",0x13);
		prtitab(z,fm_udat,&a_dt_,2,-1);prttitle(z++,"ArtDatum",0x43);
		prtitab(z,fm_of5_3,&verschil_,1,-1);prttitle(z++,"Verschil",0x13);
	}
	else{
		prtitab(z,VarTextFmt(9,0),buf_,1,-1);prttitle(z++,"Code",3);
		prtitab(z,VarTextFmt(35,0),&buf_[10],1,-1);prttitle(z++,"Omschrijving Prik&Tik",3);
		prttab(z,93,7,1,-1); prttitle(z++,"Dt.begin",3);
		prttab(z,93,8,1,-1); prttitle(z++,"Dt.stop",3);
	  prtitab(z,VarTextFmt(30,0),&buf_[55],1,-1);prttitle(z++,"Promotie",3);
	  prttab(z,6,3,1,25); prttitle(z++,"Artikel",3);
		prttab(z,93,30,1,-1); prttitle(z++,"PromoTekst",3);
		prttab(z,93,11,1,-1); prttitle(z++,"Prijs",0x13);
		prttab(z,93,25,1,-1); prttitle(z++,"P",3);
	}
  prtbuf(4);
	if(soortlijst_==0) p_pdfname("Lijst prijswijzigingen",*u(25,2),0); else p_pdfname("Lijst promoties",*u(25,2),0);
	for(k=0;k<BewCount;k++){
		zero(buf_,sizeof buf_);
		copy(BewLijn[k].Code,buf_,10);
//		cstr_=BewLijn[k].Naam; // cstr_+=" "; cstr_+=BewLijn[k].Verpakking; cstr_=cstr_.Left(50);
//		copy((char *)((LPCTSTR)cstr_),&buf_[10],cstr_.GetLength());
		copy(BewLijn[k].Naam,&buf_[10],45);
		copy(BewLijn[k].Promotie,&buf_[55],40);
		inhoud_=BewLijn[k].Inhoud;
		gewicht_=BewLijn[k].Gewicht;
		fasinit(6); if(BewLijn[k].ArtRec){*u(6,1)=BewLijn[k].ArtRec; fasgeti(6);}
		l_ap_=BewLijn[k].AKprijs; l_dt_=BewLijn[k].PrijsDatum; a_ap_=BewLijn[k].ArtLevAKprijs; a_dt_=BewLijn[k].ArtDatum; 
		if(*u(6,1)) verschil_=l_ap_-a_ap_; else verschil_=0;
		fasinit(93);
		if(soortlijst_==1){
			if(BewLijn[k].PromoRec){ *u(93,1)=BewLijn[k].PromoRec;fasgeti(93);}
		}
		attr_=0; if(verschil_ || *u(93,1)) attr_=2; for(n=1;n<20;n++) prtinfo(n,attr_);
		prtline();
	}
	prtform(0);prtclose();
	endsr:;
}

static int UpdateKassaPromo(int bew_nr_)
{
	int16 k,z,key,curs=11,DoSelect_,retval_=0;
	float factor_,nm_vp[6];
	char str_[50],nm_formule[30];

   // artikel en stu93 moeten geladen zijn

	if(fldlen(93,35)){ // nieuwe methode via ovl0295
		if(*u(93,1)==0){ // zit er al een op die dag
			fasinit(93); *u(93,7)=BewLijn[bew_nr_].PromoStart;*u(93,8)=BewLijn[bew_nr_].PromoStop; *u(93,2)=*u(6,1);
			if(faskeyi(93,7,0)){
				fasinit(93); *u(93,7)=BewLijn[bew_nr_].PromoStart;*u(93,8)=BewLijn[bew_nr_].PromoStop; *u(93,2)=*u(6,1);
				copy(BewLijn[bew_nr_].Promotie,s(93,30),fldlen(93,30));
				
				*f(93,11)=BewLijn[bew_nr_].VKprijs;
				if(*f(6,31)<=1) *f(93,11+max_kprx-1)=BewLijn[bew_nr_].VKprijs;
			}
		}
		zero(GlobalTextBuffer,sizeof GlobalTextBuffer); copy(BewLijn[bew_nr_].Promotie,GlobalTextBuffer, sizeof BewLijn[0].Promotie);
		return ovlcall(295,3);
	}




	zero((char *)&folderlijn.dt_beg,sizeof folderlijn);
	folderlijn.dt_beg=BewLijn[bew_nr_].PromoStart; *u(93,7)=folderlijn.dt_beg;
	folderlijn.dt_end=BewLijn[bew_nr_].PromoStop; *u(93,8)=folderlijn.dt_end;
	copy(BewLijn[bew_nr_].Promotie,folderlijn.promotekst,40);
	folderlijn.prijs=BewLijn[bew_nr_].VKprijs;
	if(*u(93,1)==0) copy(folderlijn.promotekst,s(93,30),fldlen(93,30));
	for(k=0;k<max_kprx;k++){
		nm_vp[k]=*f(6,tb_kprx[k]);
		if(!(sys3894 & (1<<(tb_kprx[k]-21)))) nm_vp[k]*=1.+ *f(6,28)/100.;
		if(nm_vp[k]!=*f(6,tb_kprx[k])) nm_vp[k]=valu_cnv("EUR","EUR",(double)nm_vp[k],(double)0.01);
		if(*u(93,1)==0){ // enkel bij nieuwe
		  if(k==0) *f(93,11+k)=BewLijn[bew_nr_].VKprijs;
		  else if(k==max_kprx-1 && *f(6,31)<=1) *f(93,11+k)=BewLijn[bew_nr_].VKprijs;
		  else *f(93,11+k)=0;
		}
	}
	if(fldlen(93,26)){
  	zero(nm_formule,sizeof nm_formule);
  	if(*u(93,26)>=1 && *u(93,26)<=20) copy(PromoFormule[*u(93,26)-1].Omschrijving,nm_formule,25);
	}
	FOREVER{
		redo_art:;
		scrget(3,15);z=1;
		k=bew_nr_+1;scrifld(z++,fm_ou3,&k);scrifld(z++,fm_ou3,&BewCount);
		scrifld(z++,VarTextFmt(10,0),BewLijn[bew_nr_].Code);
		scrifld(z++,VarTextFmt(50,0),BewLijn[bew_nr_].Naam);
		scrifld(z++,fm_of4_2,&folderlijn.prijs);
		scrifld(z++,fm_os40,folderlijn.promotekst);
		scrifld(z++,VarTextFmt(20,0),folderlijn.ean);
		scrifld(z++,fm_udat,&folderlijn.dt_beg);scrifld(z++,fm_udat,&folderlijn.dt_end);
		scrofld(z++,6,3,-1); 
		for(k=0;k<max_kprx;k++){
			zero(str_,sizeof str_);
      if(k==0) scrifld(z++,VarTextFmt(10,0),"Kassa bak");
      else if(k==max_kprx-1) scrifld(z++,VarTextFmt(10,0),"Kassa stuk");
      else {copy("Horeca",str_,6);stcli_d(&str_[6],(long)k,2,1);scrifld(z++,VarTextFmt(10,0),str_);}
      scrfld(z++,93,11+k); 
      scrifld(z++,fm_of4_2,&nm_vp[k]);
    }
    for(k=max_kprx;k<6;k++) z+=3;
		scrfld(z++,93,30);
		if(fldlen(93,26)){
  		scrfld(-z,93,26);scraddpicto(3,z++,0,0,2,1,112,0,4,"Uitgebreid zoeken");scrifld(z++,VarTextFmt(25,0),nm_formule); 
		} else z+=2;
		scrfld(z++,93,25);
		scrfld(z++,93,31);
		key=scrupd(curs,0x2E7);curs=11;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101 || key==106) return NO; // stop
		if(key==104){ // schrap
			if(*u(93,1)) faskill(93);
			BewLijn[bew_nr_].PromoRec=0;
			break;
		}
		if(folderlijn.dt_beg==0 || folderlijn.dt_end==0){curs=8;errnum=38;goto redo_art;}
		if(fldlen(93,26)){
			if(key==5003){
				k=SelectPromoFormule();
				if(k) *u(93,26)=k;
			}
			zero(nm_formule,sizeof nm_formule);
			if(*u(93,26)){
				if(*u(93,26)<1 || *u(93,26)>20 || PromoFormule[*u(93,26)-1].Omschrijving[0]=='\0'){errnum=39; curs=60;goto redo_art;}
				if(*u(93,26) && *s(93,25)){errnum=72; curs=60;goto redo_art;}
				copy(PromoFormule[*u(93,26)-1].Omschrijving,nm_formule,25);
			}
		}
		if(key==108 || key==102 || key==103){
			for(k=0;k<max_kprx;k++) folderlijn.kassaprijs[k]=*f(93,11+k);
			copy(s(93,30),folderlijn.promotekst,fldlen(93,30));
			copy(s(93,31),folderlijn.ean,fldlen(93,31));
			copy(s(93,25),&folderlijn.promocode,fldlen(93,25));
			if(fldlen(93,26)) folderlijn.promoformule=*u(93,26);
			*u(93,2)=*u(6,1);
			if(faskeyi(93,7,0)==0) faskill(93);
			fasinit(93);
			*u(93,7)=folderlijn.dt_beg;*u(93,8)=folderlijn.dt_end;*u(93,2)=*u(6,1);
			for(k=0;k<max_kprx;k++) *f(93,11+k)=folderlijn.kassaprijs[k];
			copy(folderlijn.promotekst,s(93,30),fldlen(93,30));
			copy(folderlijn.ean,s(93,31),fldlen(93,31));
			copy(&folderlijn.promocode,s(93,25),fldlen(93,25));
			if(fldlen(93,26)) *u(93,26)=folderlijn.promoformule;
			errnum=fasadd(93);
			BewLijn[bew_nr_].PromoRec=*u(93,1);
			if(key==102) return 2; 
			else if(key==103) return 3;
			else return 1;
			break;
		}
	}
	return YES;
}

static int16 SelectPromoFormule(void)
{
  int16 k,z,key,start;
	uint16 nr_=0;


	start=0;scrnum=0;scrget(1,6);scrupd(-3,0);
	FOREVER{
		redo:;
		scrget(3,16); z=1;
		for(k=start;k<start+17;k++){
			k++; scrifld(z++,fm_ou2,&k); k--;
			scrifld(z++,VarTextFmt(25,0),PromoFormule[k].Omschrijving);
		}
		nr_=0; scrifld(35,fm_uu2,&nr_);
		key=scrupd(1,0xA7);
		if(key==101 || key==106) return 0;
		if(key==102){start=0; goto redo;}
		if(key==103){start=3;	goto redo;}
		if(nr_<1 || nr_>20 || PromoFormule[nr_-1].Omschrijving[0]=='\0') errnum=39;
		else break;
	}
	return nr_;
  endsr:;
}



static bool ReadFolderFile(char *prijsfilename_) 
{
	char buf_[100];
  CString line_,cstr_;
  int j,k,KolNrs[12],mode_,len_;
	double bd_;

	zeroL((char *)&BewLijn[0].Code,sizeof BewLijn);BewCount=0;
	fasinit(80);mode_=0;

	for(BewCount=0;BewCount<DIM_BEWLIJN;BewCount++){
	  next:;
    if(read_rec(mode_)) break; mode_=1;
		CnvJamaChar(p_data,256,1); // convert2 JamaAscii
		fasinit(93);zero((char *)&folderlijn.dt_beg,sizeof folderlijn);
		BewLijn[BewCount].PromoStart=get_date(0);if(BewLijn[BewCount].PromoStart==0) goto next; 
		BewLijn[BewCount].PromoStop=get_date(1);if(BewLijn[BewCount].PromoStop==0) goto next; 
		len_=ele_len(2); if(len_>fldlen(11,5)) len_=fldlen(11,5);copy(rec_ele(2),BewLijn[BewCount].Code,len_);
		len_=ele_len(3); if(len_>50) len_=50;copy(rec_ele(3),BewLijn[BewCount].Naam,len_);
		BewLijn[BewCount].VKprijs=get_num(4);
		len_=ele_len(5);if(len_>50) len_=50;copy(rec_ele(5),BewLijn[BewCount].Promotie,len_);
//		len_=ele_len(6);if(len_>20) len_=20;copy(rec_ele(6),folderlijn.ean,len_);copy(folderlijn.ean,s(93,31),fldlen(93,31));
		if(BewLijn[BewCount].Naam[0]=='\0'){zeroL((char *)&BewLijn[BewCount].Code,sizeof BewLijn[0]);BewCount--;} // lege lijnen skippen
		else{
  		CopyOnlyChar(BewLijn[BewCount].Code,BewLijn[BewCount].CmpStr,fldlen(11,5));
  		if(BewLijn[BewCount].Inhoud==0 && BewLijn[BewCount].AantalBak==0){ // proberen in te vullen ahv naam
  			FindVolAndCntFromName(BewLijn[BewCount].Naam, BewLijn[BewCount].EAN,BewLijn[BewCount].Inhoud,BewLijn[BewCount].AantalBak);  // return zit in globale float var ItmCnt en ItmVol
  			BewLijn[BewCount].Inhoud=ItmVol; BewLijn[BewCount].AantalBak=ItmCnt;
  		}
		}
	}
	fasinit(11);*u(11,2)=Settings.RecLeverancier;
	FOREVER{ // artikelgegevens aanviullen
		next11:;
		if(faskeyi(11,1,2)) break; 
		if(*u(11,2)!=Settings.RecLeverancier) break;
		if(*s(11,5)=='\0') goto next11;
		zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
		for(k=0;k<BewCount;k++){
			if(cmpstrU(BewLijn[k].CmpStr,buf_,sizeof BewLijn[0].CmpStr)==0){
				fasinit(6);*u(6,1)=*u(11,3);fasgeti(6);
				if(fldlen(11,68)) BewLijn[k].AfwijkendAantal=*f(11,68);
				BewLijn[k].ArtRec=*u(6,1);
				if(fldlen(6,105) && *u(6,105)){
					BewLijn[k].ArtAKprijs=*f(6,106);
				  BewLijn[k].ArtDatum=*u(6,105);
				}
				else{
  				BewLijn[k].ArtAKprijs=*f(6,12);
	  			BewLijn[k].ArtDatum=*u(6,11);
				}
				BewLijn[k].ArtGewicht=*f(6,38);
				BewLijn[k].ArtInhoud=*f(6,37);
				BewLijn[k].ArtAantalBak=*f(6,31);
				float factor_=1.; if(BewLijn[k].AfwijkendAantal && BewLijn[k].ArtAantalBak) factor_= BewLijn[k].AfwijkendAantal/ BewLijn[k].ArtAantalBak;
				BewLijn[k].ArtLevAKprijs=Round((double)(BewLijn[k].ArtAKprijs*factor_),(double)(0.001));

			}
		}
	}
	fasclos(-2);
  return true;
}



static int DisplayPrijsFile(char *prijsfilename_)
{
  int16 nr_,k,key,z,start_,lijnpos,q_,ScreenLines=15;
	unsigned short funckeys;
	char attrib_;
	CString cstr_;
	
  start_=0; nr_=0; lijnpos=0; scrnum=0; Accijnsverhoging=NO;
  FOREVER{
		redo:;
    scrnum=0;scrget(3,10);z=1;q_=0; funckeys=0x76E1;
		scraddpicto(3,0,72,22,4,2,583,0,0,"Maak PDF"); 
		cstr_=CString(prijsfilename_); k=cstr_.ReverseFind('\\'); if(k>=0) cstr_=cstr_.Mid(k+1);scrifld(z++,VarTextFmt(35,0),(char *)((LPCTSTR)cstr_));
		scrifld(z++,fm_udat,&dt_NewPrijs); 
		if(Accijnsverhoging) scrifld(z++,VarTextFmt(18,0)," Accijnsverhoging "); else z++;
	  start_++;scrifld(z++,fm_ou3,&start_);start_--;scrifld(z++,fm_ou3,&BewCount);
		if(start_>0){ funckeys+=2; scraddpicto(1,0,76,1,4,2,18,0,4,"up"); }
		if((start_+ScreenLines)<BewCount) {funckeys+=4;scraddpicto(2,0,76,22,4,2,13,0,4,"down"); }
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=BewCount) break;
			attrib_=0xFF; if(BewLijn[k].Done==YES) attrib_=0xA; else if(BewLijn[k].ArtRec==0) attrib_=0x0B;
			cstr_=BewLijn[k].Naam; cstr_+=" "; cstr_+=BewLijn[k].Verpakking; cstr_=cstr_.Left(40);
			scrifld(z++,VarTextFmt(40,0),(char *)((LPCTSTR)cstr_)); scrchat(z-1,attrib_);
			//scrifld(z++,VarTextFmt(12,0),BewLijn[k].Verpakking); 
			scrifld(z++,fm_of4_3,&BewLijn[k].AKprijs); scrchat(z-1,attrib_);
			scrifld(z++,fm_of4_3,&BewLijn[k].ArtLevAKprijs); if(is_nul((double)(BewLijn[k].AKprijs-BewLijn[k].ArtLevAKprijs))) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
			scrifld(z++,fm_odat,&BewLijn[k].ArtDatum); if(is_nul((double)(BewLijn[k].AKprijs-BewLijn[k].ArtLevAKprijs))) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
			if(BewLijn[k].ArtRec) scraddpicto(11+k-start_,z-1,2,0,2,1,112,0,4,"Pas prijs aan"); 
			scraddpicto(11+ScreenLines+k-start_,z-1,4,0,2,1,69,0,4,"Koppel artikel"); 
	  }
    key=scrupd(1,funckeys);
		if ((key/0x100)==1) key=(key&0xFF)+5000;

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
			case 101     : return false; 
										 break;
			case 111     : if(Accijnsverhoging) Accijnsverhoging=NO; else Accijnsverhoging=YES;
										 break;
			//case 106     : for(k=0;k<BewCount;k++) if(BewLijn[k].UserChanged) break;
			//							 if(k<BewCount){
			//								 if(DisplayWarning("Wenst u echt de ingebrachte wijzigingen te annuleren?",605,1)==NO) goto redo;
			//							 }
			//							 return false;
			//							 break;


//			case 18      :// ENTER 
//			case 15      : // TAB  
			//case 18     : if(nr_>BewCount) errnum=34;// neem aan en exit 
			//							else{
			//								if(nr_>0) DetailBeweging(p_tbcoda_,nr_-1); 
  	//								 }
			//							 break;
			default      : break;
    }
//		if(dt_NewPrijs==0) errnum=38;
		if(key==110){ // alle artikels aanpassen
			if(dt_NewPrijs==0){errnum=38;goto redo;}
			for(k=0;k<BewCount;k++){
				if(BewLijn[k].ArtRec && !is_nul((double)(BewLijn[k].AKprijs-BewLijn[k].ArtLevAKprijs))) {
					if(UpdateArtikel(k)==0) break; 
				}
			}
		}
		if(key>=5011 && key<5011+ScreenLines) UpdateArtikel(key-5011+start_);
		if(key>=5011+ScreenLines && key<5011+ScreenLines*2) KoppelArtikel(key-5011-ScreenLines+start_,YES);
		if(key==5003) PdfPrijsFile(prijsfilename_);
		//if(key==108){
		//	for(k=0;k<BewCount;k++) if(BewLijn[k].BkhOK==NO) break;
		//	if(k<BewCount)errnum=73;
		//	else break;
		//}
	}
	return true;
}

static int UpdateArtikel(int bew_nr_)
{
// static int16 FindArtikel(uint16 lev_rec_,char *lev_code_,char *art_naam_,uint16 nr_in_lijst_,uint16 NO_skip_artikel_, uint16 OnlySearch_)

	int16 DoSelect_,retval_=0,pmode_;
	float factor_;

	DoSelect_=NO;
	fasinit(6); *u(6,1)=BewLijn[bew_nr_].ArtRec;fasgeti(6);
	fasinit(26);
	if(dt_NewPrijs) *u(26,2)=dt_NewPrijs; else *u(26,2)=*u(25,2);
	factor_=1.; if(BewLijn[bew_nr_].AfwijkendAantal && BewLijn[bew_nr_].ArtAantalBak) factor_= BewLijn[bew_nr_].AfwijkendAantal/ BewLijn[bew_nr_].ArtAantalBak;
	*d(26,18)=BewLijn[bew_nr_].AKprijs/factor_;
	*d(26,19)=BewLijn[bew_nr_].Accijns/factor_;
	*d(26,20)=BewLijn[bew_nr_].EcoTax/factor_;
	*d(26,21)=BewLijn[bew_nr_].Leeggoed/factor_;
	*d(26,22)=BewLijn[bew_nr_].ZwerfvuilTax/factor_+BewLijn[bew_nr_].FostPlus/factor_; // de 2 tesamen
	pmode_=1; if(Accijnsverhoging) pmode_=3;
	retval_=ovlcall(213,pmode_);
	fasinit(1);*u(1,1)=Settings.RecLeverancier;fasgeti(1);
	fasinit(6);*u(6,1)=BewLijn[bew_nr_].ArtRec;fasgeti(6);
	if(retval_==1){
		if(fldlen(6,105) && *u(6,105)){
			BewLijn[bew_nr_].ArtAKprijs=*f(6,106);
		  BewLijn[bew_nr_].ArtDatum=*u(6,105);
		}
		else{
			BewLijn[bew_nr_].ArtAKprijs=*f(6,12);
 			BewLijn[bew_nr_].ArtDatum=*u(6,11);
		}
		BewLijn[bew_nr_].ArtLevAKprijs=Round((double)(BewLijn[bew_nr_].ArtAKprijs*factor_),(double)0.001);
	}
	//if(*u(6,7)!=*u(1,1)){
	//	if(scr_ok("Wenst U van deze leverancier de HOOFDleverancier te maken?")==YES) {
	//		*u(6,7)=*u(1,1);
	//		if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
	//		fasupd(6);
	//	}
	//}

	return retval_;
}

static void PdfPrijsFile(char *prijsfilename_)
{
  int16 k,n,z,attr_;
	int16 form_dat[8],pr_mode,prtnr;
  char buf_[100];
	uint16 l_dt_,a_dt_;
  float inhoud_,gewicht_,l_ap_,a_ap_,verschil_;
	CString cstr_;
	
	fasinit(6);
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
	prtfld(25,1,25); prttext("  Prijzenbestand : ");
	cstr_=CString(prijsfilename_); k=cstr_.ReverseFind('\\'); if(k>=0) cstr_=cstr_.Mid(k+1);
	prtifld(VarTextFmt(35,0),(char *)((LPCTSTR)cstr_),-1);
  prttext("<t92>");prtfld(25,2,-1);prttext("<t120>Blz.<ppp>.");
  prtbuf(1);
	prttext("<t28>Ingangsdatum : ");prtifld(fm_udat,&dt_NewPrijs,-1);prtbuf(2);
	z=1;
  prtitab(z,VarTextFmt(7,0),buf_,1,-1);prttitle(z++,"Code",3);
	prtitab(z,VarTextFmt(45,0),&buf_[10],1,-1);prttitle(z++,"Omschrijving P&T",3);
	//prtitab(z,VarTextFmt(14,0),&buf_[50],1,-1);prttitle(z++,"Verpakking",3);
	prttab(z,6,3,1,-1); prttitle(z++,"Artikel",3);
//	prtitab(z,fm_of4_2,&inhoud_,1,-1);prttitle(z++,"Inhoud",0x13);
//	prtitab(z,fm_udat,&l_dt_,1,-1);prttitle(z++,"Datum",0x43);
	prtitab(z,fm_of5_3,&l_ap_,1,-1);prttitle(z++,"P&T-Prijs",0x13);
//	prttab(z,6,37,1,-1);prttitle(z++,"Inhoud",0x13);
	prtitab(z,fm_of5_3,&a_ap_,2,-1);prttitle(z++,"Art.prijs",0x13);
	prtitab(z,fm_udat,&a_dt_,2,-1);prttitle(z++,"ArtDatum",0x43);
	prtitab(z,fm_of5_3,&verschil_,1,-1);prttitle(z++,"Verschil",0x13);

  prtbuf(4);
	p_pdfname("Lijst prijswijzigingen",*u(25,2),0);
	for(k=0;k<BewCount;k++){
		zero(buf_,sizeof buf_);
		copy(BewLijn[k].Code,buf_,10);
		cstr_=BewLijn[k].Naam; cstr_+=" "; cstr_+=BewLijn[k].Verpakking; cstr_=cstr_.Left(50);
		copy((char *)((LPCTSTR)cstr_),&buf_[10],cstr_.GetLength());
//		copy(BewLijn[k].Naam,&buf_[10],40);
//		copy(BewLijn[k].Verpakking,&buf_[50],15);
		inhoud_=BewLijn[k].Inhoud;
		gewicht_=BewLijn[k].Gewicht;
		fasinit(6); if(BewLijn[k].ArtRec){*u(6,1)=BewLijn[k].ArtRec; fasgeti(6);}
		l_ap_=BewLijn[k].AKprijs; l_dt_=BewLijn[k].PrijsDatum; a_ap_=BewLijn[k].ArtLevAKprijs; a_dt_=BewLijn[k].ArtDatum; 
		if(*u(6,1)) verschil_=l_ap_-a_ap_; else verschil_=0;
		attr_=0; if(verschil_) attr_=2; for(n=1;n<20;n++) prtinfo(n,attr_);
		prtline();
	}
	prtform(0);prtclose();
	endsr:;
}


static int KoppelArtikel(int listnr_,int DoSelect_) // zoek/koppel P&T-artikel, bij DoSelect_ YES, altijd laten selecteren
{
	int16 k,q_,n,z,key,curs=6,start_,mode6_,mode11_,found_=NO,retval_=0,MaxScrLines=12;
	uint16 nr_,orig_rec11=0,orig_rec6=0;
	int kleur_;
	char SearchText[50],lijn_attrib_,buf_[100];
	CString cstr_;

	fasinit(6);
	redo_listnr:;
	zero((char *)&recs[0],sizeof recs);zero((char *)&recs_preferred[0],sizeof recs_preferred);recs_used=0;nr_=0;
	for(k=0;k<fldlen(6,3);k++) if(BewLijn[listnr_].Naam[k]==' ' || BewLijn[listnr_].Naam[k]=='\0') break;
	cstr_=CString(BewLijn[listnr_].Naam,k);cstr_.Trim(); cstr_.MakeUpper();k=cstr_.GetLength();
	zero(SearchText,sizeof SearchText);copy((char *)(LPCTSTR)cstr_,SearchText,k);
	found_=NO;orig_rec11=0;orig_rec6=0;
	fasinit(11); *u(11,2)=Settings.RecLeverancier; mode11_=1;
	FOREVER{
		next11:;
		if(faskeyi(11,1,mode11_)) break; mode11_=2;
		if(*u(11,2)!=Settings.RecLeverancier) break;
		if(*s(11,5)=='\0') goto next11;
		zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
		for(k=0;k<sizeof buf_;k++) if(buf_[k]=='.') buf_[k]=',';
		if(cmpstrU(BewLijn[listnr_].CmpStr,buf_,sizeof BewLijn[0].CmpStr)==0){
			recs[recs_used]=*u(11,3); recs_preferred[recs_used]=2; orig_rec11=*u(11,1);orig_rec6=*u(11,3);recs_used++;
			found_=YES;
 		}
	}
	if(found_){// al gekoppeld
		if(DoSelect_==NO) return YES;
		else goto display; 
	}


	fasinit(6);mode6_=1;
	FOREVER{
next_a:;
		if(recs_used>=MAX_RECS) break;
		if(faskeyi(6,2,mode6_)) break; mode6_=2;
		fasinit(11);*u(11,2)=Settings.RecLeverancier;*u(11,3)=*u(6,1);mode11_=1;
		FOREVER{ // controleren of artikel al een code heeft voor deze leverancier 
			if(faskeyi(11,1,mode11_)) break; mode11_=2;
			if(*u(11,2)!=Settings.RecLeverancier || *u(11,3)!=*u(6,1)) break;
			if(*s(11,5)) goto next_a; // artikel heeft al een code ingevuld
		}
		if(BewLijn[listnr_].EAN[0]){
			if(cmpstr(BewLijn[listnr_].EAN,s(6,70),fldlen(6,70))==0) {recs[recs_used]=*u(6,1); recs_preferred[recs_used]=1; recs_used++;goto next_a;}
			if(cmpstr(BewLijn[listnr_].EAN,s(6,71),fldlen(6,71))==0) {recs[recs_used]=*u(6,1); recs_preferred[recs_used]=1; recs_used++;goto next_a;}
		}
		cstr_=CString(s(6,3),fldlen(6,3));cstr_.MakeUpper();
		if(cstr_.Find(_T(SearchText),0)>=0) {recs[recs_used++]=*u(6,1);goto next_a;}
		if(recs_used>=MAX_RECS) break;
	}
	display:;
	fasinit(6); start_=0; nr_=0; scrnum=0; 
	FOREVER{
		redo_art:;
		scrnum=0;scrget(3,11);z=1;q_=0;
		if(start_>0) {scraddpicto(1,0,76,2,4,2,18,0,4,"up"); }
		if((start_+MaxScrLines)<recs_used) {scraddpicto(2,0,76,21,4,2,13,0,4,"down");}
//		scraddpicto(5,0,0,0,4,1,16,0,4,"Vorig"); 
//		scraddpicto(6,0,76,0,4,1,17,0,4,"Volgend"); 
		listnr_++;scrifld(z++,fm_ou5,&listnr_);listnr_--;scrifld(z++,fm_ou5,&BewCount);
		scrifld(z++,VarTextFmt(10,0),BewLijn[listnr_].Code);
		scrifld(z++,VarTextFmt(15,0),BewLijn[listnr_].EAN);
		scrifld(z++,VarTextFmt(10,0),BewLijn[listnr_].Eenheid);
		scrifld(z++,VarTextFmt(40,0),BewLijn[listnr_].Naam);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
		scrifld(z++,fm_of42_,&BewLijn[listnr_].Inhoud);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
		scrifld(z++,fm_of4_0,&BewLijn[listnr_].AantalBak);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
		scrifld(z++,VarTextFmt(30,0),BewLijn[listnr_].Verpakking);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
		scrifld(-z,fm_us30,SearchText);z++; scraddpicto(3,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); scraddpicto(4,z-1,2,0,2,1,107,0,4,"Zoeken"); 
		if(found_){scraddfield(150,4,22,8);scrifld(150,VarTextFmt(18,0)," F4 wis koppeling ");}


		for(n=start_;n<start_+MaxScrLines;n++){
			if(n>=recs_used) break;
			fasinit(6);*u(6,1)=recs[n]; fasgeti(6);
			lijn_attrib_=0xFF; 
			if(recs_preferred[n]==1) lijn_attrib_=0x08;
			else if(recs_preferred[n]==2) lijn_attrib_=0x09;
      if(fldlen(6,200) && *i(6,200)) lijn_attrib_=0xB;
			k=n+1; scrifld(z++,fm_ou3,&k);scrchat(z-1,lijn_attrib_);
			scrofld(z++,6,2,-1);scrchat(z-1,lijn_attrib_);
			scrofld(z++,6,3,-1);scrchat(z-1,lijn_attrib_);
			kleur_=4; if(recs_preferred[n]==0xFF) kleur_=0;
			scraddpicto(10+n-start_,0,18,10+n-start_,2,1,86,0,kleur_,"Selecteer"); 
			scrifld(z++,fm_of42_,f(6,37));scrchat(z-1,lijn_attrib_);
			scrifld(z++,fm_of4_0,f(6,31));scrchat(z-1,lijn_attrib_);
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
												orig_rec11=0;orig_rec6=0; found_=NO;
												zero((char *)&recs[0],sizeof recs);zero((char *)&recs_preferred[0],sizeof recs_preferred);recs_used=0;
												BewLijn[listnr_].ArtRec=0;
												BewLijn[listnr_].ArtAKprijs=0;
												BewLijn[listnr_].ArtDatum=0;
												BewLijn[listnr_].ArtGewicht=0;
												BewLijn[listnr_].ArtInhoud=0;
												BewLijn[listnr_].ArtAantalBak=0;
												BewLijn[listnr_].AfwijkendAantal=0;
												BewLijn[listnr_].ArtLevAKprijs=0;
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
												fasinit(11); *u(11,2)=Settings.RecLeverancier; *u(11,3)=recs[n]; mode11_=1;
												FOREVER{
												if(faskeyi(11,1,mode11_)) break; mode11_=2;
												if(*u(11,2)!=Settings.RecLeverancier || *u(11,3)!=recs[n]) break;
												if(*s(11,5)){
  												zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
	  											for(k=0;k<sizeof buf_;k++) if(buf_[k]=='.') buf_[k]=',';
		  										if(cmpstrU(BewLijn[listnr_].CmpStr,buf_,sizeof BewLijn[0].CmpStr)==0)	recs_preferred[n]=2; 
			  									else if(*s(11,5)) recs_preferred[n]=0xFF;
												}
												}
											}
											start_=0;goto redo_art;
											break;
			case 5004    : fasinit(6);copy(SearchText,s(6,3),fldlen(6,3));  // normale zoek
											ExecSearch(0);
											for(n=0;n<recs_used;n++){
												fasinit(11); *u(11,2)=Settings.RecLeverancier; *u(11,3)=recs[n]; mode11_=1;
												FOREVER{
												if(faskeyi(11,1,mode11_)) break; mode11_=2;
												if(*u(11,2)!=Settings.RecLeverancier || *u(11,3)!=recs[n]) break;
												if(*s(11,5)){
  												zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
	  											for(k=0;k<sizeof buf_;k++) if(buf_[k]=='.') buf_[k]=',';
		  										if(cmpstrU(BewLijn[listnr_].CmpStr,buf_,sizeof BewLijn[0].CmpStr)==0)	recs_preferred[n]=2; 
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
		fasinit(11);*u(11,2)=Settings.RecLeverancier;*u(11,3)=*u(6,1);mode11_=1;found_=NO;
		FOREVER{ // zoeken naar record met lege code voor deze leverancier 
			if(faskeyi(11,1,mode11_)) break; mode11_=2;
			if(*u(11,2)!=Settings.RecLeverancier || *u(11,3)!=*u(6,1)) break;
			if(*s(11,5) && cmpstr(s(11,5),BewLijn[listnr_].Code,fldlen(11,5))) {found_=YES;break;} // heeft al een code 
		}
		if(found_){
			zero(buf_,sizeof buf_);
			sprintf_s(buf_,85,"Dit artikel is al gekoppeld met ANDERE code %s! Toch doorgaan?",s(11,5));
      if(DisplayWarning(buf_,605,1)==NO) goto redo_listnr;
		}
		if(orig_rec11){ // bij wijziging het origineel wissen
			fasinit(11);*u(11,1)=orig_rec11;fasgeti(11);
			zero(s(11,5),fldlen(11,5));
			if(fldlen(11,68)) *f(11,68)=0;
			fasupd(11);
		}
		fasinit(11);*u(11,2)=Settings.RecLeverancier;*u(11,3)=*u(6,1);mode11_=1;found_=NO;
		FOREVER{ // zoeken naar record met lege code voor deze leverancier 
			if(faskeyi(11,1,mode11_)) break; mode11_=2;
			if(*u(11,2)!=Settings.RecLeverancier || *u(11,3)!=*u(6,1)) break;
			if(*s(11,5)=='\0') {found_=YES;break;} // rec11 zonder code 
		}
		if(found_){
			copy(BewLijn[listnr_].Code,s(11,5),fldlen(11,5));
			if(fldlen(11,68)) *f(11,68)=BewLijn[listnr_].AfwijkendAantal;
			errnum=fasupd(11);}
		else{
			fasinit(11);*u(11,2)=Settings.RecLeverancier;*u(11,3)=*u(6,1);
			copy(BewLijn[listnr_].Code,s(11,5),fldlen(11,5));
			if(fldlen(11,68)) *f(11,68)=BewLijn[listnr_].AfwijkendAantal;
			*u(11,9)=*u(25,2); // om promo-artikels (-1) te skippen bij bestellen
			errnum=fasadd(11);
		}
//			if(*f(6,37)<=0) *f(6,37)=BewLijn[listnr_].inhoud;
//			if(*f(6,38)<=0) *f(6,38)=BewLijn[listnr_].gewicht;
		if(*s(6,71)=='\0' && cmpstr(BewLijn[listnr_].EAN,s(6,70),fldlen(6,70))) copy(BewLijn[listnr_].EAN,s(6,71),fldlen(6,71)); // stuks invullen 
// GEEN BAK 		else if(*s(6,70)=='\0' && cmpstr(BewLijn[listnr_].EAN,s(6,71),fldlen(6,71))) copy(BewLijn[listnr_].EAN,s(6,70),fldlen(6,70));
		//if(*s(6,70)=='\0' && *s(6,71) && cmpstr(BewLijn[listnr_].EAN,s(6,71),fldlen(6,71))) copy(BewLijn[listnr_].EAN,s(6,70),fldlen(6,70));
		//else if(*s(6,71)=='\0' && cmpstr(BewLijn[listnr_].EAN,s(6,70),fldlen(6,70))) copy(BewLijn[listnr_].EAN,s(6,71),fldlen(6,71));
		fasupd(6);
		BewLijn[listnr_].ArtRec=*u(6,1);
		BewLijn[listnr_].ArtAKprijs=*f(6,12);
		BewLijn[listnr_].ArtDatum=*u(6,11);
		BewLijn[listnr_].ArtGewicht=*f(6,38);
		BewLijn[listnr_].ArtInhoud=*f(6,37);
		BewLijn[listnr_].ArtAantalBak=*f(6,31);
		float factor_=1.; if(BewLijn[listnr_].AfwijkendAantal && BewLijn[listnr_].ArtAantalBak) factor_= BewLijn[listnr_].AfwijkendAantal/ BewLijn[listnr_].ArtAantalBak;
		BewLijn[listnr_].ArtLevAKprijs=Round((double)(BewLijn[listnr_].ArtAKprijs*factor_),(double)0.001);
		return YES;
	}
endsr:;
	return NO;
}

static int CheckInhoud(int listnr_) // controleer inhoud
{
  int16 z,key;
   
	if(*f(6,37)==BewLijn[listnr_].Inhoud && *f(6,31)==BewLijn[listnr_].AantalBak) return YES; // is OK

  FOREVER{
	redo:;
		scrnum=0;scrget(3,12);z=1;
		scrifld(z++,VarTextFmt(10,0),BewLijn[listnr_].Code);
		scrifld(z++,VarTextFmt(15,0),BewLijn[listnr_].EAN);
		scrifld(z++,VarTextFmt(10,0),BewLijn[listnr_].Eenheid);
		scrifld(z++,VarTextFmt(40,0),BewLijn[listnr_].Naam);
		scrifld(z++,fm_of42_,&BewLijn[listnr_].Inhoud);
		scrifld(z++,fm_of4_0,&BewLijn[listnr_].AantalBak);
		scrifld(z++,VarTextFmt(30,0),BewLijn[listnr_].Verpakking);
		scrofld(z++,6,2,-1); scrofld(z++,6,3,-1);
		scrifld(z++,fm_uf42_,f(6,37)); scrifld(z++,fm_uf4_0,f(6,31));
		if(fldlen(11,68)) scrifld(z++,fm_uf4_0,&BewLijn[listnr_].AfwijkendAantal);
		key=scrupd(1,0x2A0);
		if(key==106) return NO;

		if(key==110){
			*f(6,37)=BewLijn[listnr_].Inhoud; *f(6,31)=BewLijn[listnr_].AantalBak;
			if(fldlen(6,198)) *u(6,198)=procid;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
		}
		if(*f(6,37)==0 && *f(6,38)==0){errnum=38; goto redo;}
		if(key==108) break;
  }
	fasupd(6);
	float factor_=1.; if(BewLijn[listnr_].AfwijkendAantal && BewLijn[listnr_].ArtAantalBak) factor_= BewLijn[listnr_].AfwijkendAantal/ BewLijn[listnr_].ArtAantalBak;
	BewLijn[listnr_].ArtLevAKprijs=Round((double)(BewLijn[listnr_].ArtAKprijs*factor_),(double)0.001);
  return YES;
}

static bool ReadPrijsFile(char *prijsfilename_)
{
	char buf_[100];
  CString line_,cstr_;
  int k,KolNrs[12],chgd_;
	char delim_kar_;
	double bd_;

	zero(buf_,sizeof buf_);chgd_=NO;
	for(k=0;k<100;k++) {
		if(prijsfilename_[k]=='\0') break;
		if(prijsfilename_[k]>=0x80){buf_[k]=' '; chgd_=YES;}
		else buf_[k]=prijsfilename_[k];
	}
	if(chgd_){// probleem met spec.karakters!
		rename(prijsfilename_,buf_);
		copy(buf_,prijsfilename_,100);
	}

	for(k=0;k<12;k++) KolNrs[k]=-1;
  delim_kar_=CSV_FIELDDELIM;
	scrget(1,7);scrupd(-3,0);
  if( (XlsRef=XlsOpen(prijsfilename_))<=0){
		sprintf(buf_,"Kan prijzenbestand \'%s\' niet openen!",prijsfilename_);
		DisplayWarning(buf_,605,0);
 		return 0;
	}
	XlsMaxKol=XlsGetMaxKol(XlsRef); XlsMaxRij=XlsGetMaxRij(XlsRef);
	zeroL((char *)&BewLijn[0].Code,sizeof BewLijn);BewCount=0;
	XlsKol=1;XlsRij=1;
  XlsRij++; // headerlijn met leverancier
  zero(buf_,sizeof buf_); XlsReadString(XlsRef,XlsRij,4,buf_,10); // testen op datum prijs
	if(buf_[0]=='\0') XlsRij++;  // 2 headerlijnen 
    
	for(k=0;k<XlsMaxKol;k++){
		zero(buf_,sizeof buf_); XlsReadString(XlsRef,XlsRij,k+1,buf_,50); cstr_=CString(buf_);
		if(cstr_.CompareNoCase("Nr.")==0) KolNrs[0]=k;
		else if(cstr_.CompareNoCase("Omschrijving 1")==0) KolNrs[1]=k;
		else if(cstr_.CompareNoCase("Omschrijving 2")==0) KolNrs[2]=k;
		else if(cstr_.CompareNoCase("BTW%")==0) KolNrs[3]=k;
		else if(cstr_.CompareNoCase("Tarief excl acc/eco")==0) KolNrs[4]=k;
		else if(cstr_.CompareNoCase("Accijns")==0) KolNrs[5]=k;
		else if(cstr_.CompareNoCase("Verp.")==0) KolNrs[6]=k;
		else if(cstr_.CompareNoCase("Factuur-prijs")==0) KolNrs[7]=k;
		else if(cstr_.CompareNoCase("Leegg.")==0) KolNrs[8]=k;
		else if(cstr_.CompareNoCase("Zwerfvuiltaks")==0) KolNrs[9]=k;
		else if(cstr_.CompareNoCase("Fostplus")==0) KolNrs[10]=k;
	}
	if(Settings.TariefPrijsAlsBasis=='J' && KolNrs[4]<0){
		DisplayWarning("Tariefprijs niet gevonden... geen kolom 'Tarief excl acc/eco' in prijslijst",605,0);
		XlsClose(XlsRef,1);
 		return 0;
	}

	for(BewCount=0;BewCount<DIM_BEWLIJN;BewCount++){
		XlsRij++; if(XlsRij>XlsMaxRij) break;
    
		for(k=0;k<12;k++){
			if(KolNrs[k]<0 || KolNrs[k]>11) continue;
			switch(k){
			  case 0 : XlsReadString(XlsRef,XlsRij,KolNrs[k]+1,BewLijn[BewCount].Code,sizeof BewLijn[0].Code); break;  // code
				case 1 : XlsReadString(XlsRef,XlsRij,KolNrs[k]+1,BewLijn[BewCount].Naam,sizeof BewLijn[0].Naam); break; // omschrijving1
				case 2 : XlsReadString(XlsRef,XlsRij,KolNrs[k]+1,BewLijn[BewCount].Verpakking,sizeof BewLijn[0].Verpakking); break; // omschrijving2 = verpakking
				case 3 : BewLijn[BewCount].BTWpct=XlsReadDouble(XlsRef,XlsRij,KolNrs[k]+1);  break;// BTW%
				case 4 : BewLijn[BewCount].AKprijs=Round(XlsReadDouble(XlsRef,XlsRij,KolNrs[k]+1),(double)0.001); break; // ak excl acc + eco
				case 5 : BewLijn[BewCount].Accijns=Round(XlsReadDouble(XlsRef,XlsRij,KolNrs[k]+1),(double)0.001); break; // accijns
				case 6 : BewLijn[BewCount].EcoTax=Round(XlsReadDouble(XlsRef,XlsRij,KolNrs[k]+1),(double)0.001); break; // ecotax
				case 7 : if(Settings.TariefPrijsAlsBasis!='J') BewLijn[BewCount].AKprijs=Round(XlsReadDouble(XlsRef,XlsRij,KolNrs[k]+1),(double)0.001); break; // factuurprijs
				case 8 : BewLijn[BewCount].Leeggoed=Round(XlsReadDouble(XlsRef,XlsRij,KolNrs[k]+1),(double)0.001); break; // leeggoed
				case 9 : BewLijn[BewCount].ZwerfvuilTax=Round(XlsReadDouble(XlsRef,XlsRij,KolNrs[k]+1),(double)0.001); break; // zwerfvuiltax
				case 10 : BewLijn[BewCount].FostPlus=Round(XlsReadDouble(XlsRef,XlsRij,KolNrs[k]+1),(double)0.001); break; // Fostplus
				default : break;
			}
		}
		if(Settings.TariefPrijsAlsBasis=='J' || KolNrs[7]==-1){
			BewLijn[BewCount].AKprijs+=BewLijn[BewCount].Accijns+BewLijn[BewCount].EcoTax+BewLijn[BewCount].ZwerfvuilTax+BewLijn[BewCount].FostPlus; // tariefprijs of omdat kol H niet altijd bestaat, dan AKex + acc+eco
		}
		if(BewLijn[BewCount].Naam[0]=='\0'){zeroL((char *)&BewLijn[BewCount].Code,sizeof BewLijn[0]);BewCount--;} // lege lijnen skippen
		CopyOnlyChar(BewLijn[BewCount].Code,BewLijn[BewCount].CmpStr,fldlen(11,5));
		if(BewLijn[BewCount].Inhoud==0 && BewLijn[BewCount].AantalBak==0){ // proberen in te vullen ahv verpakking 
			FindVolAndCntFromName(BewLijn[BewCount].Verpakking, BewLijn[BewCount].EAN,BewLijn[BewCount].Inhoud,BewLijn[BewCount].AantalBak);  // return zit in globale float var ItmCnt en ItmVol
			BewLijn[BewCount].Inhoud=ItmVol; BewLijn[BewCount].AantalBak=ItmCnt;
		}
// ORIGINELE FILE VAN NADINE HIERONDER
  //  line_=Read_Rec(fn_prijs_); if(ReadEOFline) break;
		//cstr_=Rec_Ele(line_,0,sizeof BewLijn[0].Code);copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].Code,cstr_.GetLength()); 
		//cstr_=Rec_Ele(line_,1,sizeof BewLijn[0].Naam);copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].Naam,cstr_.GetLength()); 
		//cstr_=Rec_Ele(line_,2,sizeof BewLijn[0].Verpakking);copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].Verpakking,cstr_.GetLength()); 
		//cstr_=Rec_Ele(line_,3,-1,delim_kar_);BewLijn[BewCount].PrijsDatum=String2Date(cstr_);
		//cstr_=Rec_Ele(line_,4,sizeof BewLijn[0].Eenheid);copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].Eenheid,cstr_.GetLength()); 
		//cstr_=Rec_Ele(line_,5,-1,delim_kar_);BewLijn[BewCount].AKprijs=Round(String2Double(cstr_,','),(double)0.001);
		//cstr_=Rec_Ele(line_,6,-1,delim_kar_);BewLijn[BewCount].BTWpct=String2Double(cstr_,',');
		//cstr_=Rec_Ele(line_,7,-1,delim_kar_);BewLijn[BewCount].VKprijs=Round(String2Double(cstr_,','),(double)0.001);
		//cstr_=Rec_Ele(line_,8,-1,delim_kar_);BewLijn[BewCount].Accijns=Round(String2Double(cstr_,','),(double)0.0001);
		//cstr_=Rec_Ele(line_,9,sizeof BewLijn[0].AccijnsGroep);copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].AccijnsGroep,cstr_.GetLength()); 
		//cstr_=Rec_Ele(line_,10,-1,delim_kar_);BewLijn[BewCount].EcoTax=Round(String2Double(cstr_,','),(double)0.0001);
		//cstr_=Rec_Ele(line_,11,sizeof BewLijn[0].EcoGroep);copy((char *)(LPCTSTR)cstr_,BewLijn[BewCount].EcoGroep,cstr_.GetLength()); 
		//cstr_=Rec_Ele(line_,12,-1,delim_kar_);BewLijn[BewCount].Inhoud=Round(String2Double(cstr_,','),(double)0.001);
		//cstr_=Rec_Ele(line_,13,-1,delim_kar_);BewLijn[BewCount].Gewicht=Round(String2Double(cstr_,','),(double)0.001);
		//cstr_=Rec_Ele(line_,14,-1,delim_kar_);BewLijn[BewCount].GradenPlato=Round(String2Double(cstr_,','),(double)0.01);
		//cstr_=Rec_Ele(line_,15,-1,delim_kar_);BewLijn[BewCount].AlcoholGehalte=Round(String2Double(cstr_,','),(double)0.01);
		//CopyOnlyChar(BewLijn[BewCount].Code,BewLijn[BewCount].CmpStr,fldlen(11,5));
	}
	fasinit(11);*u(11,2)=Settings.RecLeverancier;
	FOREVER{ // artikelgegevens aanviullen
		next11:;
		if(faskeyi(11,1,2)) break; 
		if(*u(11,2)!=Settings.RecLeverancier) break;
		if(*s(11,5)=='\0') goto next11;
		zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
		for(k=0;k<sizeof buf_;k++) if(buf_[k]=='.') buf_[k]=',';
		for(k=0;k<BewCount;k++){
			if(cmpstrU(BewLijn[k].CmpStr,buf_,sizeof BewLijn[0].CmpStr)==0){
				fasinit(6);*u(6,1)=*u(11,3);fasgeti(6);
				if(fldlen(11,68)) BewLijn[k].AfwijkendAantal=*f(11,68);
				BewLijn[k].ArtRec=*u(6,1);
				if(fldlen(6,105) && *u(6,105)){
					BewLijn[k].ArtAKprijs=*f(6,106);
				  BewLijn[k].ArtDatum=*u(6,105);
				}
				else{
  				BewLijn[k].ArtAKprijs=*f(6,12);
	  			BewLijn[k].ArtDatum=*u(6,11);
				}
				BewLijn[k].ArtGewicht=*f(6,38);
				BewLijn[k].ArtInhoud=*f(6,37);
				BewLijn[k].ArtAantalBak=*f(6,31);
				float factor_=1.; if(BewLijn[k].AfwijkendAantal && BewLijn[k].ArtAantalBak) factor_= BewLijn[k].AfwijkendAantal/ BewLijn[k].ArtAantalBak;
				BewLijn[k].ArtLevAKprijs=Round((double)(BewLijn[k].ArtAKprijs*factor_),(double)0.001);
				break;
			}
		}
	}
	XlsClose(XlsRef,1);
  return true;
}

static void FillHandlingKost(void) // eenmalig invullen handlingkost
{
  int16 z,key,curs=1;
   
  if(HandlingKost==0) HandlingKost=.215;
	if(AdjustAkPrijs=='\0') AdjustAkPrijs='J';
	if(AdjustOnlyEmpty=='\0') AdjustOnlyEmpty='J';

  FOREVER{
	redo:;
		scrnum=0;scrget(3,13);z=1;
		scrifld(z++,fm_uf2_3,&HandlingKost);
		scrifld(z++,fm_us3U,SelectieEenheid);
		scrifld(z++,fm_uJN,&AdjustOnlyEmpty);
		scrifld(z++,fm_uJN,&AdjustAkPrijs);
		key=scrupd(curs,0x81);curs=1;
		if(key==101) goto endsr;
		if(HandlingKost==0) {errnum=38;goto redo;}
		if(key==108){
			seldata.prx_klt=0;
			seldata.selp_use=NO;
			if(ovlcall(2215,2)) goto endsr;
			break;
		}
  }
  scrget(1,7);scrupd(-3,0);
	fasinit(6);
	FOREVER{
		next_art:;
		if(faskeyi(6,2,2)) break;
		if(AdjustOnlyEmpty=='J' && *f(6,19)) goto next_art;
		if(SelectieEenheid[0] && cmpstrU(SelectieEenheid,s(6,10),fldlen(6,10))) goto next_art;
		if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
		*f(6,19)=HandlingKost;
		if(AdjustAkPrijs=='J') *f(6,18)+=HandlingKost;
		if(fldlen(6,105) && *u(6,105)){
  		*f(6,113)=HandlingKost;
  		if(AdjustAkPrijs=='J') *f(6,112)+=HandlingKost;
		}
		fasupd(6);
	}
  endsr:;
}

static void ConvertKortingToHandlingkost(void) // eenmalig negatieve korting invullen als handlingkost en wissen
{
 
	if(DisplayWarning("Wenst u echt de negatieve korting als handlingkost in te vullen?",605)!=YES) goto endsr;
	seldata.prx_klt=0;
	seldata.selp_use=NO;
	if(ovlcall(2215,2)) goto endsr;
  scrget(1,7);scrupd(-3,0);
	fasinit(6);
	FOREVER{
		next_art:;
		if(faskeyi(6,2,2)) break;
		if(*f(6,17)>=0 || *f(6,19)) goto next_art;
		if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
		*f(6,19)=-*f(6,17); *f(6,17)=0; fasupd(6);
	}
  endsr:;
}
static void UpdateSettings(void)
{
  int curs=1,z,key;

	sysget(2944,30,Settings.MapPrijslijst);
	sysget(2976,2,(char *)&Settings.RecLeverancier);
	sysget(2984,1,(char *)&Settings.TariefPrijsAlsBasis);
	sysget(3142,50,Settings.MapLeverFiles);
//	sysget(8322,2,(char *)&Settings.EindDatumLastExport);
	fasinit(1); *u(1,1)=Settings.RecLeverancier;
	if(*u(1,1)) fasgeti(1); else curs=2;
  FOREVER {
		redo:; 
    scrnum=0;scrget(3,9);z=1;
		scrifld(z++,fm_us30,Settings.MapPrijslijst);
		scrfld(z++,1,3);
		scrifld(z++,fm_uJN,&Settings.TariefPrijsAlsBasis);
		scrifld(z++,fm_us50,Settings.MapLeverFiles);
    key=scrupd(curs,0xE0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106) goto endsr;
		if(Search(1,0)){curs=2; goto redo;}; // moet ingevuld zijn
    if(key==108) break;
  }
	Settings.RecLeverancier=*u(1,1);
	sysput(2944,30,Settings.MapPrijslijst);
	sysput(2976,2,(char *)&Settings.RecLeverancier);
	sysput(2984,1,(char *)&Settings.TariefPrijsAlsBasis);
	sysput(3142,50,Settings.MapLeverFiles);
endsr:;
	sysget(2944,30,Settings.MapPrijslijst);
	sysget(2976,2,(char *)&Settings.RecLeverancier);
	sysget(2984,1,(char *)&Settings.TariefPrijsAlsBasis);
	sysget(3142,50,Settings.MapLeverFiles);
}

static uint16 GetAKFiche(uint16 arec_,uint16 lrec_,uint16 dt_beg_)
{
	int16 mode_;
	uint16 verv_rec11_=0,rec11_=0;
	
	if(fldlen(11,1)==0) return (uint16)0;   

	fasinit(11);*u(11,3)=arec_;*u(11,2)=lrec_;mode_=1;
	FOREVER{
		if(faskeyi(11,2,mode_)) break; mode_=2;
		if(*u(11,3)!=arec_) break;
		if(*u(11,2)!=lrec_) break;
		if(*u(11,9) && *u(11,9)<dt_beg_) verv_rec11_=*u(11,1); // verlopen promotie
		else rec11_=*u(11,1);
	}
  if(rec11_==0) rec11_=verv_rec11_;
	fasinit(11);if(rec11_) {*u(11,1)=rec11_,fasgeti(11);}
	return rec11_;
}

static void UpdateLoginInfo(void)
{
  int16 z,key,curs=1;
 
  sysget(3004,10,FTPUsername);
	sysget(3014,10,FTPPaswoord);
  FOREVER{
    scrget(3,3);z=1;
		scrifld(z++,fm_us10,FTPUsername);
		scrifld(z++,fm_us10PW,FTPPaswoord);
    key=scrupd(curs,0xE0);curs=1;
    if(key==106) break;
    if(key==108){
			sysput(3004,10,FTPUsername);
      sysput(3014,10,FTPPaswoord);
      break;
    }
  }
	sysget(3004,10,FTPUsername);
	sysget(3014,10,FTPPaswoord);
	if(FTPUsername[0]=='\0' && FTPPaswoord[0]=='\0'){//serial en PW uit jms.ini nemen
    ExecJmsCommand(FTPUsername,sizeof FTPUsername,"GetIniKeyValue|JamaSettings|SerialNr");
    ExecJmsCommand(FTPPaswoord,sizeof FTPPaswoord,"GetIniKeyValue|JamaSettings|Password");
		if(FTPUsername[0]=='\0'){ copy("jmsD01abcd",FTPUsername,10); copy("123456789",FTPPaswoord,10);}
	}
}




static int16 read_rec(int16 mode_)
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

static int16 ele_len(int16 nr_)
{
  int16 k=0;
  char *p;
								
  p=rec_ele(nr_);
  FOREVER{
    if(*p==ScheidingsTeken || *p==0x0D || *p==0x0A || *p=='\0') return k;
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
      if(*p==ScheidingsTeken || *p==0xD || *p=='\0') break;
      p++;
    }
    if(!(*p==0xD || *p=='\0')) p++;
  }
  return p;
}

static float get_num(int16 nr)                           /* read number starting at pos  */
{
  int16 j=0,k=0,n;
  float val_=0,val1_;
  flag na_komma=NO,neg_get=NO;
  char *pos;
									
  pos=rec_ele(nr);
  FOREVER{
    if(*(pos+k)==ScheidingsTeken || *(pos+k)==0x0D) break;
    if(*(pos+k)==',') na_komma=YES;
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

static uint16 get_date(int16 nr)              /* read date DD/MM/JJJJ starting at pos  */
{
  int16 k=0,getal_[3],p_getal_;
  uint16 dt_=0;
  char *pos;
									
  zero((char *)&getal_[0],sizeof getal_);p_getal_=0;
  dt_=0; pos=rec_ele(nr); 
	if(ele_len(nr)==0) goto endsr;
	if(*pos<'0' || *pos>'9') goto endsr; // geen geldige datum
  FOREVER{
    if(*(pos+k)==ScheidingsTeken || *(pos+k)==0x0D) break;
    if(*(pos+k)=='/'){p_getal_++;if(p_getal_>2) break;}
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
	getal_[p_getal_]=getal_[p_getal_]*10 + (*(pos+k)-'0');
      }
    }
    k++;
  }
  getal_[2]%=100;
  dt_=datejd(getal_[2],getal_[1],getal_[0]);
  endsr:;
  return (uint16) dt_;
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

static void initload(void)
{
  int16 k,nr_;
	  
  fasunlck(0);
  for(k=1;k<=6;k++) fileopen(k);
  fileopen(9);
  if(fldlen(66,1)) fileopen(12);
  if(fldlen(92,1)) fileopen(11);
	if(fldlen(16,1)) fileopen(13);		
  sysget(294,4,def_munt);
  sysget(1048,32,&btw_pct[0]);
	sysget(1084,4,&def_btw);
  sysget(2982,2,&sys2982);
	sysget(3004,10,FTPUsername);
	sysget(3014,10,FTPPaswoord);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,sys3896);

	sysget(2944,30,Settings.MapPrijslijst);
	sysget(2976,2,(char *)&Settings.RecLeverancier);
	sysget(2984,1,(char *)&Settings.TariefPrijsAlsBasis);
  sysget(3142,50,Settings.MapLeverFiles);
	for(k=0;k<20;k++) sysget(20500+k*45,45,&PromoFormule[k].Omschrijving[0]);
	 
	zero((char *)&tb_kprx[0],sizeof tb_kprx); max_kprx=0;
  for(k=0;k<6;k++){
    if(sys3896[k]){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
				tb_kprx[max_kprx++]=PrNrs[nr_];
      }
    }
  }

  pl_80_1=l(80,1);
  p_data=s(80,1)+4;
	copy("-X|/",dsp_kar,4);dsp_kar[1]=0x5C;
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

static float FindVolAndCntFromName(char* Name, char* Ean, float ArtVol, float ArtCnt)  // return zit in globale float var ItmCnt en ItmVol
{
	float DMVol=0;
	
	
	ItmVol=0.; ItmCnt=0;
	
	CString N=Name;

	N.Replace("O","0");
	N.Replace("1664","    ");
	N.Replace(" 2.4 X","");
	N.Replace(" 1X6LT "," 6X1LT ");
	N.Replace("(","");
	N.Replace(")","");
	VolSearchString=N;


	
	//if (CheckKeyWord(" 5 C")) ItmVol=0.05;
	//else if (CheckKeyWord("5 CL")) ItmVol=0.05;
	//else if (CheckKeyWord("5CL")) ItmVol=0.05;
	if (CheckKeyWord("0,05 L")) ItmVol=0.05;
  else if (CheckKeyWord("0,05L")) ItmVol=0.05;
	else if (CheckKeyWord("0.05 L")) ItmVol=0.05;
	else if (CheckKeyWord("0.05L")) ItmVol=0.05;
	else if (CheckKeyWord("0,050 L")) ItmVol=0.05;
	else if (CheckKeyWord("0,050L")) ItmVol=0.05;
	else if (CheckKeyWord("0.050 L")) ItmVol=0.05;
	else if (CheckKeyWord("0.050L")) ItmVol=0.05;

	else if (CheckKeyWord(" 15 C")) ItmVol=0.15;
	else if (CheckKeyWord("15 CL")) ItmVol=0.15;
	else if (CheckKeyWord("15CL")) ItmVol=0.15;
	else if (CheckKeyWord("0,15 L")) ItmVol=0.15;
	else if (CheckKeyWord("0,15L")) ItmVol=0.15;
	else if (CheckKeyWord("0.15 L")) ItmVol=0.15;
	else if (CheckKeyWord("0.15L")) ItmVol=0.15;
	else if (CheckKeyWord("0,150 L")) ItmVol=0.15;
	else if (CheckKeyWord("0,150L")) ItmVol=0.15;
	else if (CheckKeyWord("0.150 L")) ItmVol=0.15;
	else if (CheckKeyWord("0.150L")) ItmVol=0.15;


	else if (CheckKeyWord(" 20 C")) ItmVol=0.20;
	else if (CheckKeyWord("20 CL")) ItmVol=0.20;
	else if (CheckKeyWord("20CL")) ItmVol=0.20;
	else if (CheckKeyWord("1/5")) ItmVol=0.20;
	else if (CheckKeyWord("0,20 L")) ItmVol=0.2;
	else if (CheckKeyWord("0,20L")) ItmVol=0.2;
	else if (CheckKeyWord("0.20 L")) ItmVol=0.2;
	else if (CheckKeyWord("0.20L")) ItmVol=0.2;
	else if (CheckKeyWord("0,2 L")) ItmVol=0.2;
	else if (CheckKeyWord("0,2L")) ItmVol=0.2;
	else if (CheckKeyWord("0.2 L")) ItmVol=0.2;
	else if (CheckKeyWord("0.2L")) ItmVol=0.2;
	else if (CheckKeyWord("24x20")) ItmVol=0.2;

	else if (CheckKeyWord(" 25 C")) ItmVol=0.25;
	else if (CheckKeyWord("25 CL")) ItmVol=0.25;
	else if (CheckKeyWord("25CL")) ItmVol=0.25;
	else if (CheckKeyWord("1/4")) ItmVol=0.25;
	else if (CheckKeyWord("0,25 L")) ItmVol=0.25;
	else if (CheckKeyWord("0,25L")) ItmVol=0.25;
	else if (CheckKeyWord("0.25 L")) ItmVol=0.25;
	else if (CheckKeyWord("0.25L")) ItmVol=0.25;
	else if (CheckKeyWord("0,250 L")) ItmVol=0.25;
	else if (CheckKeyWord("0,250L")) ItmVol=0.25;
	else if (CheckKeyWord("0.250 L")) ItmVol=0.25;
	else if (CheckKeyWord("0.250L")) ItmVol=0.25;
	else if (CheckKeyWord("X25L")) ItmVol=0.25;
	else if (CheckKeyWord("X25 L")) ItmVol=0.25;
	else if (CheckKeyWord("X025L")) ItmVol=0.25;
	else if (CheckKeyWord("X025 L")) ItmVol=0.25;

	else if (CheckKeyWord("0,275 L")) ItmVol=0.275;
	else if (CheckKeyWord("0,275L")) ItmVol=0.275;
	else if (CheckKeyWord("0.275 L")) ItmVol=0.275;
	else if (CheckKeyWord("0.275L")) ItmVol=0.275;

	else if (CheckKeyWord(" 33 C")) ItmVol=0.33;
	else if (CheckKeyWord("33 CL")) ItmVol=0.33;
	else if (CheckKeyWord("33CL")) ItmVol=0.33;
	else if (CheckKeyWord("1/3")) ItmVol=0.33;
	else if (CheckKeyWord("0,33 L")) ItmVol=0.33;
	else if (CheckKeyWord("0,33L")) ItmVol=0.33;
	else if (CheckKeyWord("0.33 L")) ItmVol=0.33;
	else if (CheckKeyWord("0.33L")) ItmVol=0.33;
	else if (CheckKeyWord("0.33 CL")) ItmVol=0.33;
	else if (CheckKeyWord("0.33CL")) ItmVol=0.33;
	else if (CheckKeyWord("0,33 CL")) ItmVol=0.33;
	else if (CheckKeyWord("0,33CL")) ItmVol=0.33;
	else if (CheckKeyWord("24X33")) ItmVol=0.33;

	else if (CheckKeyWord(" 35 C")) ItmVol=0.35;
	else if (CheckKeyWord("0,35 L")) ItmVol=0.35;
	else if (CheckKeyWord("0,35L")) ItmVol=0.35;
	else if (CheckKeyWord("0.35 L")) ItmVol=0.35;
	else if (CheckKeyWord("0.35L")) ItmVol=0.35;
	else if (CheckKeyWord("0,350 L")) ItmVol=0.35;
	else if (CheckKeyWord("0,350L")) ItmVol=0.35;
	else if (CheckKeyWord("0.350 L")) ItmVol=0.35;
	else if (CheckKeyWord("0.350L")) ItmVol=0.35;
	else if (CheckKeyWord("X35L")) ItmVol=0.35;
	else if (CheckKeyWord("X35 L")) ItmVol=0.35;      

	else if (CheckKeyWord("37,5 CL")) ItmVol=0.375;
	else if (CheckKeyWord("37,5CL")) ItmVol=0.375;
	else if (CheckKeyWord("37.5 CL")) ItmVol=0.375;
	else if (CheckKeyWord("37.5CL")) ItmVol=0.375;
	else if (CheckKeyWord("375CL")) ItmVol=0.375;
	else if (CheckKeyWord("37,5L")) ItmVol=0.375;
	else if (CheckKeyWord("37.5L")) ItmVol=0.375;
	else if (CheckKeyWord("0,375 L")) ItmVol=0.375;
	else if (CheckKeyWord("0,375L")) ItmVol=0.375;
	else if (CheckKeyWord("0.375 L")) ItmVol=0.375;
	else if (CheckKeyWord("0.375L")) ItmVol=0.375;

	else if (CheckKeyWord(" 30 C")) ItmVol=0.3;
	else if (CheckKeyWord("0,30 L")) ItmVol=0.3;
	else if (CheckKeyWord("0,30L")) ItmVol=0.3;
	else if (CheckKeyWord("0.30 L")) ItmVol=0.3;
	else if (CheckKeyWord("0.30L")) ItmVol=0.3;
	else if (CheckKeyWord("0,3 L")) ItmVol=0.3;
	else if (CheckKeyWord("0,3L")) ItmVol=0.3;
	else if (CheckKeyWord("0.3 L")) ItmVol=0.3;
	else if (CheckKeyWord("0.3L")) ItmVol=0.3;

	else if (CheckKeyWord(" 50 C")) ItmVol=0.5;
	else if (CheckKeyWord("50 CL")) ItmVol=0.5;
	else if (CheckKeyWord("50CL")) ItmVol=0.5;
	else if (CheckKeyWord("1/2")) ItmVol=0.5;
	else if (CheckKeyWord("0,50 L")) ItmVol=0.5;
	else if (CheckKeyWord("0,50L")) ItmVol=0.5;
	else if (CheckKeyWord("0.50 L")) ItmVol=0.5;
	else if (CheckKeyWord("0.50L")) ItmVol=0.5;
	else if (CheckKeyWord("0,5 L")) ItmVol=0.5;
	else if (CheckKeyWord("0,5L")) ItmVol=0.5;
	else if (CheckKeyWord("0.5 L")) ItmVol=0.5;
	else if (CheckKeyWord("0.5L")) ItmVol=0.5;

	else if (CheckKeyWord(" 70 C")) ItmVol=0.70;
	else if (CheckKeyWord("70 CL")) ItmVol=0.70;
	else if (CheckKeyWord("70CL")) ItmVol=0.70;
	else if (CheckKeyWord("0,70 L")) ItmVol=0.70;
	else if (CheckKeyWord("0,70L")) ItmVol=0.70;
	else if (CheckKeyWord("0.70 L")) ItmVol=0.70;
	else if (CheckKeyWord("0.70L")) ItmVol=0.70;

	if (ItmVol>0.01) goto GetCount; // om de compiler blocks nested too deeply op te lossen

	else if (CheckKeyWord(" 75 C")) ItmVol=0.75;
	else if (CheckKeyWord("75CL")) ItmVol=0.75;
	else if (CheckKeyWord("75 CL")) ItmVol=0.75;
	else if (CheckKeyWord("75CL")) ItmVol=0.75;
	else if (CheckKeyWord("X75C")) ItmVol=0.75;
	else if (CheckKeyWord("X 75C")) ItmVol=0.75;
	else if (CheckKeyWord("3/4")) ItmVol=0.75;
	else if (CheckKeyWord("0,75 L")) ItmVol=0.75;
	else if (CheckKeyWord("0,75L")) ItmVol=0.75;
	else if (CheckKeyWord("0.75 L")) ItmVol=0.75;
	else if (CheckKeyWord("0.75L")) ItmVol=0.75;
	else if (CheckKeyWord("0.75 CL")) ItmVol=0.75;
	else if (CheckKeyWord("0.75CL")) ItmVol=0.75;
	else if (CheckKeyWord("0,750 L")) ItmVol=0.75;
	else if (CheckKeyWord("0,750L")) ItmVol=0.75;
	else if (CheckKeyWord("0.750 L")) ItmVol=0.75;
	else if (CheckKeyWord("0.750L")) ItmVol=0.75;
	else if (CheckKeyWord("X,75L")) ItmVol=0.75;
	else if (CheckKeyWord("X.75L")) ItmVol=0.75;
	else if (CheckKeyWord("X,75 L")) ItmVol=0.75;
	else if (CheckKeyWord("X.75 L")) ItmVol=0.75;

	else if (CheckKeyWord(" 100 C")) ItmVol=1.;
	else if (CheckKeyWord("1 L")) ItmVol=1.;
	else if (CheckKeyWord("1L")) ItmVol=1.;
	else if (CheckKeyWord("1/1")) ItmVol=1.;
	else if (CheckKeyWord("100 CL")) ItmVol=1.;
	else if (CheckKeyWord("100CL")) ItmVol=1.;
	else if (CheckKeyWord("1,00 L")) ItmVol=1.;
	else if (CheckKeyWord("1,00L")) ItmVol=1.;
	else if (CheckKeyWord("1.00 L")) ItmVol=1.;
	else if (CheckKeyWord("1.00L")) ItmVol=1.;

	else if (CheckKeyWord("1.5 L")) ItmVol=1.5;
  else if (CheckKeyWord("1.5L")) ItmVol=1.5;
	else if (CheckKeyWord("1,5 L")) ItmVol=1.5;
  else if (CheckKeyWord("1,5L")) ItmVol=1.5;
	else if (CheckKeyWord("1.50 L")) ItmVol=1.5;
  else if (CheckKeyWord("1.50L")) ItmVol=1.5;
	else if (CheckKeyWord("1,50 L")) ItmVol=1.5;
  else if (CheckKeyWord("1,50L")) ItmVol=1.5;
  else if (CheckKeyWord(" 150 C")) ItmVol=1.5;
	else if (CheckKeyWord("6x1.5")) ItmVol=1.5;
	else if (CheckKeyWord("6x150")) ItmVol=1.5;

	else if (CheckKeyWord("6X1")) ItmVol=1.;
	else if (CheckKeyWord("12X1")) ItmVol=1.;

	else if (CheckKeyWord(" 125 C")) ItmVol=1.25;
	else if (CheckKeyWord("1,25 L")) ItmVol=1.25;
	else if (CheckKeyWord("1,25L")) ItmVol=1.25;
	else if (CheckKeyWord("1.25 L")) ItmVol=1.25;
	else if (CheckKeyWord("1.25L")) ItmVol=1.25;
	else if (CheckKeyWord("1,250 L")) ItmVol=1.25;
	else if (CheckKeyWord("1,250L")) ItmVol=1.25;
	else if (CheckKeyWord("1.250 L")) ItmVol=1.25;
	else if (CheckKeyWord("1.250L")) ItmVol=1.25;
	
	else if (CheckKeyWord("2.0 L")) ItmVol=2.0;
  else if (CheckKeyWord("2.0L")) ItmVol=2.0;
	else if (CheckKeyWord("2,0 L")) ItmVol=2.0;
  else if (CheckKeyWord("2,0L")) ItmVol=2.0;
	else if (CheckKeyWord("2.00 L")) ItmVol=2.0;
  else if (CheckKeyWord("2.00L")) ItmVol=2.0;
	else if (CheckKeyWord("2,00 L")) ItmVol=2.0;
  else if (CheckKeyWord("2,00L")) ItmVol=2.0;

  else if (CheckKeyWord("15 L")) ItmVol=15.;
	else if (CheckKeyWord("15L")) ItmVol=15.;
  else if (CheckKeyWord("18 L")) ItmVol=18.;
	else if (CheckKeyWord("18L")) ItmVol=18.;
	else if (CheckKeyWord("25 L")) ItmVol=25.;
	else if (CheckKeyWord("25L")) ItmVol=25.;
	else if (CheckKeyWord("20 L")) ItmVol=20.;
	else if (CheckKeyWord("20L")) ItmVol=20.;
	else if (CheckKeyWord("30 L")) ItmVol=30.;
	else if (CheckKeyWord("30L")) ItmVol=30.;
	else if (CheckKeyWord("50 L")) ItmVol=50.;
	else if (CheckKeyWord("50L")) ItmVol=50.;
	else if (CheckKeyWord("5 L")) ItmVol=5.;
	else if (CheckKeyWord("5L")) ItmVol=5.;
	else if (CheckKeyWord("6 L")) ItmVol=6.;
	else if (CheckKeyWord("6L")) ItmVol=6.;


GetCount:;
	if (CheckKeyWord("2X12X")) ItmCnt=24;
	else if (CheckKeyWord("12 X")) ItmCnt=12;
	else if (CheckKeyWord("12X")) ItmCnt=12;
	else if (CheckKeyWord("18X")) ItmCnt=18;
	else if (CheckKeyWord("18 X")) ItmCnt=18;
	else if (CheckKeyWord("20 X")) ItmCnt=20;
	else if (CheckKeyWord("20X")) ItmCnt=20;
	else if (CheckKeyWord("24 X")) ItmCnt=24;
	else if (CheckKeyWord("24X")) ItmCnt=24;
	else if (CheckKeyWord("30 X")) ItmCnt=30;
	else if (CheckKeyWord("30X")) ItmCnt=30;
	
	else if (CheckKeyWord("X 12")) ItmCnt=12;
	else if (CheckKeyWord("X12")) ItmCnt=12;
	else if (CheckKeyWord("X18") && ItmVol<1) ItmCnt=18;
	else if (CheckKeyWord("X 18") && ItmVol<1) ItmCnt=18;
	else if (CheckKeyWord("X 20") && ItmVol<1) ItmCnt=20;
	else if (CheckKeyWord("X20") && ItmVol<1) ItmCnt=20;
	else if (CheckKeyWord("X 24") && ItmVol<1) ItmCnt=24;
	else if (CheckKeyWord("X24") && ItmVol<1) ItmCnt=24;
	else if (CheckKeyWord("28X") && ItmVol<1) ItmCnt=28;
	else if (CheckKeyWord("X28") && ItmVol<1) ItmCnt=28;
	else if (CheckKeyWord("X 30") && ItmVol<1) ItmCnt=30;
	else if (CheckKeyWord("X30") && ItmVol<1) ItmCnt=30;
	else if (CheckKeyWord("6X4X")) ItmCnt=24;
	else if (CheckKeyWord("4X6X")) ItmCnt=24;
	else if (CheckKeyWord("3X8X")) ItmCnt=24;
	else if (CheckKeyWord("8X3X")) ItmCnt=24;
	else if (CheckKeyWord("X 6")) ItmCnt=6;
	else if (CheckKeyWord("X6")) ItmCnt=6;
	else if (CheckKeyWord("X 8")) ItmCnt=8;
	else if (CheckKeyWord("X8")) ItmCnt=8;

	else if (CheckKeyWord("3+1")) ItmCnt=4;

	else if (CheckKeyWord("4+2")) ItmCnt=6;
	else if (CheckKeyWord("5+1")) ItmCnt=6;

	else if (CheckKeyWord("CL4")) ItmCnt=4;
	else if (CheckKeyWord("CL8")) ItmCnt=8;


	else if (CheckKeyWord("4 X")) ItmCnt=4;
	else if (CheckKeyWord("4X")) ItmCnt=4;
	else if (CheckKeyWord("6 X")) ItmCnt=6;
	else if (CheckKeyWord("6X")) ItmCnt=6;
	else if (CheckKeyWord("8 X")) ItmCnt=8;
	else if (CheckKeyWord("8X")) ItmCnt=8;
	else if (CheckKeyWord("5X6X")) ItmCnt=30;
		 
	else if (CheckKeyWord("24 BTL")) ItmCnt=24;
	else if (CheckKeyWord("24BTL")) ItmCnt=24;
	else if (CheckKeyWord("24 ST")) ItmCnt=24;
	else if (CheckKeyWord("24ST")) ItmCnt=24;
	else if (CheckKeyWord("24 FL")) ItmCnt=24;
	else if (CheckKeyWord("24FL")) ItmCnt=24;
	else if (CheckKeyWord("18+6")) ItmCnt=24;
	else if (CheckKeyWord("19+5")) ItmCnt=24;
	else if (CheckKeyWord("20+4")) ItmCnt=24;
	else if (CheckKeyWord("21+3")) ItmCnt=24;
	else if (CheckKeyWord("22+2")) ItmCnt=24;
	else if (CheckKeyWord("23+1")) ItmCnt=24;

	else if (CheckKeyWord("12 BTL")) ItmCnt=12;
	else if (CheckKeyWord("12BTL")) ItmCnt=12;
	else if (CheckKeyWord("12 ST")) ItmCnt=12;
	else if (CheckKeyWord("12ST")) ItmCnt=12;
	else if (CheckKeyWord("12 FL")) ItmCnt=12;
	else if (CheckKeyWord("12FL")) ItmCnt=12;

	else if (CheckKeyWord("6 BTL")) ItmCnt=6;
	else if (CheckKeyWord("6BTL")) ItmCnt=6;
	else if (CheckKeyWord("6 ST")) ItmCnt=6;
	else if (CheckKeyWord("6ST")) ItmCnt=6;
	else if (CheckKeyWord("6 FL")) ItmCnt=6;
	else if (CheckKeyWord("6FL")) ItmCnt=6;

  else if (CheckKeyWord("4 BTL")) ItmCnt=4;
	else if (CheckKeyWord("4BTL")) ItmCnt=4;
	else if (CheckKeyWord("4 ST")) ItmCnt=4;
	else if (CheckKeyWord("4ST")) ItmCnt=4;
	else if (CheckKeyWord("4 FL")) ItmCnt=4;
	else if (CheckKeyWord("4FL")) ItmCnt=4;

  else if (CheckKeyWord("CLIP12")) ItmCnt=12;
	else if (CheckKeyWord("12 BTL")) ItmCnt=12;
	else if (CheckKeyWord("12BTL")) ItmCnt=12;
	else if (CheckKeyWord("6 BTL")) ItmCnt=6;
	else if (CheckKeyWord("6BTL")) ItmCnt=6;
	else if (CheckKeyWord("4 BTL")) ItmCnt=4;
	else if (CheckKeyWord("4BTL")) ItmCnt=4;
	else if (CheckKeyWord("3X1,5")) ItmCnt=3;

	ItmVol=Round((double)(ItmVol),0.001);ItmCnt=Round((double)(ItmCnt),1);
	ArtVol=Round((double)(ArtVol),0.001);ArtCnt=Round((double)(ArtCnt),1);

	if(ItmVol==0 || ItmCnt==0){ 
		if(ItmVol==0 && ItmCnt==0){// als niks gevonden en fiche is goed ingevuld, dan data van fiche nemen
			if(ArtVol && ArtCnt){ItmVol=ArtVol/ArtCnt; ItmCnt=ArtCnt;}
		}
		else if(ItmVol){
			if(ItmVol>=5) ItmCnt=1;  // vat of zo
			else if(ArtVol){
				int count_=Round((double)(ArtVol/ItmVol),1);
				if(count_==Round((double)(ArtVol/ItmVol),0.01)) ItmCnt=count_;
			}
			else if(ArtCnt) ItmCnt=ArtCnt;
  		if(ItmCnt==0) ItmCnt=1;
		}
		else if(ItmCnt && ArtVol){
			ItmVol=ArtVol/ItmCnt;
		}
	}


	// let op : hieronder zijn alle O vervangen door 0 ! (zie bovenaan)
	if (N.Find("G0BELET")>=0) ItmVol=0;
	else if (N.Find("TASSES")==0) ItmVol=0;
	else if (N.Find("EC0TAX")==0) ItmVol=0;
	else if (N.Find("BIERGLAS")==0) ItmVol=0;
	else if (N.Find("K00LZUUR")>=0) ItmVol=0;
	else if (N.Find("VERRE")==0) ItmVol=0;
	else if (N.Find("GLAS")==0) ItmVol=0;
	else if (N.Find("BEKER")==0) ItmVol=0;
	else if (N.Find("DRINKBEKER")==0) ItmVol=0;

	ItmVol=ItmVol*ItmCnt;

 // if (MaxArtikel<DIM_ARTIKEL && !(ArtVol>(DMVol*0.95) || DMVol<0.001)){ // gewijzigd !
	//	TbArtikel[MaxArtikel].RecordNr=*u(6,1);
	//	TbArtikel[MaxArtikel].OldAantal=ArtCnt;
	//	TbArtikel[MaxArtikel].OldInhoud=ArtVol;
	//	TbArtikel[MaxArtikel].NewAantal=ItmCnt;
	//	TbArtikel[MaxArtikel].NewInhoud=DMVol;
	//	MaxArtikel++;
	//}

	return ItmVol;
}


static bool CheckKeyWord(char *keyword)
{
	int k;
	char kar_;
	  
	if((k=VolSearchString.Find(keyword))>0){
		kar_=VolSearchString.GetAt(k-1);
		if(keyword[0]>='0' && keyword[0]<='9' && ((kar_>='0' && kar_<='9') || kar_==',' || kar_=='.' || kar_=='+')){
			return false;
		} 
		else return true;
	}
	return false;
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

static int16 cmpstrU(char *p1,char *p2,int16 len)
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


//// SIF routines op basis van cstring en dopen 



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

static uint16 String2Date(CString S)  // date DD/MM/JJJJ 
{
  int16 dd_=0,mm_=0,jj_=0,pos1_,pos2_;
  uint16 dt_=0;
	CString cstr_;

  dt_=0; 
	if(S.GetLength()<=0) goto endsr;

	pos1_=S.Find('/',0); if(pos1_<=0) goto endsr;
	pos2_=S.Find('/',pos1_+1); if(pos2_<=0) goto endsr;
	dd_=String2Int(S.Mid(0,pos1_));
	mm_=String2Int(S.Mid(pos1_+1,pos2_-pos1_));
	jj_=String2Int(S.Mid(pos2_+1,4)); jj_%=100;
  dt_=datejd(jj_,mm_,dd_);
  endsr:;
  return (uint16) dt_;
}

static short unsigned XlsReadDateFromText(int16 ref,int16 rownr,int16 colnr) 
{
	char buf_[20];
	CString datestr_;

	zero(buf_,sizeof buf_);
	XlsReadString(ref,rownr,colnr,buf_,sizeof buf_);
	datestr_=CString(buf_); datestr_.Trim();
	return (uint16) String2Date(datestr_);
}

static CString Date2String(unsigned int date_,int mode_)
{
   char txtbuffer_[100];

   zeros(txtbuffer_,sizeof txtbuffer_);
   if(date_) datefm(txtbuffer_,date_,mode_);

   return CString(txtbuffer_);
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

static int is_nul(double bd_)
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.0009) return YES;
  else return NO;
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
