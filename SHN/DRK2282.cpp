/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* DRK2282GetD() {return &zzvw;}
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

extern "C" char DRK2282dat[] = "drk2282  00:22 02/06/17 (c) Jamadata"; // Inleesroutines leveringsbons Prik&Tik

// XML-bestanden moeten in ..\Share\PrikTik\   (Map leveranciersbestelling 19600 : parameters + 5)

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DF_GRB          15
#define DIM_BEWLIJN     500
#define DIM8            100
#define DIM58           800
#define MINFREE         200
#define MAXFLD          100
#define MAX_RECS        2500
#define DIMBTW          8
#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */
#define CSV_FIELDDELIM		  '\x09' // ","
 
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
static char fm_of5_0[] = {6,0x94,5,0,0x70,0};
static char fm_of50_[] = {6,0x94,5,0,0x60,0};
static char fm_of4_3[] = {6,0x94,4,3,0x60,0};
static char fm_of4_0[] = {6,0x94,4,0,0x70,0};
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

static int16 prt2pdf,BewCount,DRK0211Mode;
static char sys3896[6],fmt[40],ScheidingsTeken='\x09',SelectieEenheid[10],MapBestelling[51],BonNr[20];
static char filnam[100],def_munt[4],buf1000[1000], StrBonNr[10];
static char lev_res[60],klt_res[60],art_res[60],WarnBuf[200];
static uint16 dat_beg,dat_end,inq_lev=0,BonDate;
static flag sys3894,sys2982;
static flag sear_stt,sys3876;

static uint16 recs_used,RecLevPnT;
static uint16 recs[MAX_RECS];
static char recs_preferred[MAX_RECS];

static char ICSBTab[256];

static struct {
	char Code[25];
	char Naam[40];
	char Eenheid[10];
	char LotNr[30];
	uint16 VervDate;
	char EAN[15];
	float AfwijkendAantal;
	float Aantal;
	float KortPct;
	float Prijs;
	float Accijns;
	uint16 ArtRec;
	float ArtAantalBak;
	float ArtInhoud;
	uint16 Rec11;
} BewLijn[DIM_BEWLIJN];

/* --------------------------- Declaratie functies ---------------------- */

static int AKDataFromPrikTikXml(void);
static void AddBon2Doc(void);
static int CheckInhoud(int listnr_); // controleer inhoud
static int16 cmpstrU(char *p1,char *p2,int16 len);
static int copy0(char *ps,char *pd,int max);
static int16 Copy2ZoekStr(char *ps3_,char *zoekstr,uint16 len3_,uint16 lenz_);
static double Round(double getal, double round);
static bool DisplayLeverData(char *filename_);
static int DisplayWarning(char *ptxt, int icoon);
static int16 ExecSearch(int16 mode_);
static void fileopen(int16 nr_);
static int16 FindBewArt(int16 nr_, int16 OnlyThisArt); // zoek artikel op referentie leverancier of EAN
static int fmt_get(int16 stu_, int16 elet_);
static int GetSearchText(char *s,char *d, int len);  // analoog aan JMS (composekey)
static void InitConvertTab();  // komt uit JMS
static void initload(void);
static int KoppelArtikel(int listnr_,int DoSelect_); // zoek/koppel artikel 
static int NettoCompareStr(char *p1,char *p2,int16 len);
static void nextline(void);
static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_);
static bool ReadBestelFile(char *bestelfilename_);
static bool ReadPrikTikXml(char *filename_);
static uint16 String2Date(CString datestr_,CString format_);
static double String2Getal(CString S,char decim_kar);
static double String2Double(CString S){return String2Getal(S,',');}
static double String2Double(CString S,char decim_kar){ return String2Getal(S,decim_kar);}
static int String2Int(CString S){return (int)(String2Getal(S,','));}


static void ram2stu(int16 lin_);
static void stu2ram(int16 lin_);
static int test_line(void);

static char *ram;
static long ram_size;
static int16 stu58_len,max_line;

static struct{ // ZELFDE HOUDEN IN DRK2282, DRK2283 EN DRK2284!!!!
  uint16 rec;
  float qlv;
  char  stuks_fl;
  char  code[15];
	char  ref_lev[20];
	uint16 rec11;
  char  omschr[40];
  char  valuta[4];
  float tbprx[8];/* bruto, perc1, perc2, kortfr, apnet , afh.verg, losverg.*/
  float accijns;
  float btw;
  uint16 groep;
  float q_per_bak; // indien afwijkend
  uint16 rec_leeg;
  float q_leeg;
  float bd_leeg;
  float tot_akw;
  float calc_qlv;
  char  PlMag[10];
  uint16 hash;
}tblin;

static int16 len_tblin;
static char *p_tblin;

extern char SelectedFileName[];
extern char RamBon[];
extern int RamBonSize;

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

extern "C" void DRK2282cod(int parmval) // 0=read AK-xml PrikTik via stu58 vanuit 255/240, 1=read AK-xml PrikTik vanuit 211, 2=geen selectie, maar direct invullen voor 255
{
	int k,klt_empty_;
	char str_selectie_[100];


	DRK0211Mode=NO; if(parmval==1) DRK0211Mode=YES; // via stu58 of niet
	if(*u(1,1)==0) *u(1,1)=RecLevPnT; if(*u(1,1)) fasgeti(1);

  initload();

		switch(parmval){
		case 0  : AKDataFromPrikTikXml(); break;
    case 1  : AKDataFromPrikTikXml(); break;
    case 2  : DRK0211Mode=NO; 
							if(ReadPrikTikXml(BestelFileUsed[0])) AddBon2Doc();
						  break;
	  default : break;
	}
	ovlexit(-1);
}
 
static int AKDataFromPrikTikXml()
{
	int k;
	char str_selectie_[100];


	zero(str_selectie_,sizeof str_selectie_); retcall=0;
	k=copy0(MapBestelling,str_selectie_,50); k+=copy0("*.XML",&str_selectie_[k],6);
	FOREVER{
		if(GetFileFromSelection(" Verzendnota\'s Prik&Tik ",str_selectie_)==0){errnum=14; break;}
  	if(ReadPrikTikXml(SelectedFileName)){
			if(DisplayLeverData(SelectedFileName)) {
				AddBon2Doc();
				if(BestelFileUsed[0][0]=='\0') {copy0(SelectedFileName,BestelFileUsed[0],100); *(uint16 *)&BestelFileUsed[0][100]=2282;}
				else {copy0(SelectedFileName,BestelFileUsed[1],100); *(uint16 *)&BestelFileUsed[1][100]=2282;}
				retcall=YES; break;
			}
		}
	}
 // if(klt_empty_==NO || retcall==0) copy(buf1000,s(2,1),fldlen(2,0));
	return 1;
}

static bool ReadPrikTikXml(char *filename_)
{
  int16 jj_,mm_,dd_,pos1_,pos2_,k,fl_cmt_;
	CString cstr_,commentaar_;
  CMarkup bonxml_;

	scrget(1,7);scrupd(-3,0);
	for(k=0;k<DIM_BEWLIJN;k++) zero((char *)&BewLijn[k].Code,sizeof BewLijn[0]); // zeroL((char *)&BewLijn[0].Code,sizeof BewLijn);
	BewCount=0;BonDate=0; zero(StrBonNr,sizeof StrBonNr);
	if(bonxml_.Load(filename_)==false) return false;
	if(bonxml_.FindElem("Document")==false) {bonxml_.Close(); return false;}
	bonxml_.IntoElem();
	bonxml_.ResetMainPos();BonDate=String2Date(bonxml_.FindGetData("DocumentDate"),"JJJJMMDD");
	bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("DocumentNumber"); cstr2arr(cstr_,BonNr,sizeof BonNr); 
	bonxml_.ResetMainPos(); if(bonxml_.FindElem("Order")==false) {bonxml_.Close(); return false;}
	bonxml_.IntoElem();
	bonxml_.ResetMainPos(); if(bonxml_.FindElem("OrderDetail")==false) {bonxml_.Close(); return false;}
	bonxml_.IntoElem();
	bonxml_.ResetMainPos(); 
	commentaar_=CString("");
	FOREVER{
		if(bonxml_.FindElem("OrderItem")==false) break;
		bonxml_.IntoElem();
		  fl_cmt_=NO;
		  bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("LineType"); 
			if(cstr_=="TEKSTLIJN"){
				bonxml_.ResetMainPos(); commentaar_+=bonxml_.FindGetData("LineItemText"); 
				fl_cmt_=YES;
			}
			else{
  			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("InternalArticleNumberBuyer"); cstr2arr(cstr_,BewLijn[BewCount].Code,sizeof BewLijn[0].Code); 
				bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("GTINCode"); cstr2arr(cstr_,BewLijn[BewCount].EAN,sizeof BewLijn[0].EAN); 
				bonxml_.ResetMainPos();
				if(bonxml_.FindElem("Quantities")){
					bonxml_.IntoElem();
						bonxml_.ResetMainPos(); 
						if(bonxml_.FindElem("Quantity")){
							bonxml_.IntoElem();
							  bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("UnitOfMeasure"); cstr2arr(cstr_,BewLijn[BewCount].Eenheid,sizeof BewLijn[0].Eenheid); 
								bonxml_.ResetMainPos(); BewLijn[BewCount].Aantal=String2Double(bonxml_.FindGetData("QuantityAmount"),'.');
							bonxml_.OutOfElem();
						}
					bonxml_.OutOfElem();
				}
				bonxml_.ResetMainPos();
#if FLAGJAN  // geen prijzen overnemen
				goto no_prices;
#endif
				if(bonxml_.FindElem("Prices")){
					bonxml_.IntoElem();
						bonxml_.ResetMainPos(); 
						if(bonxml_.FindElem("Acc")){
							bonxml_.IntoElem();
								BewLijn[BewCount].Accijns=String2Double(bonxml_.FindGetData("PriceAmount"),'.');
							bonxml_.OutOfElem();
						}
						bonxml_.ResetMainPos(); 
						if(bonxml_.FindElem("Discount")){
							bonxml_.IntoElem();
							BewLijn[BewCount].KortPct=String2Double(bonxml_.FindGetData("PriceAmount"),'.');
							bonxml_.OutOfElem();
						}
						bonxml_.ResetMainPos(); 
						if(bonxml_.FindElem("Price")){
							bonxml_.IntoElem();
							BewLijn[BewCount].Prijs=String2Double(bonxml_.FindGetData("PriceAmount"),'.');
							bonxml_.OutOfElem();
						}
					bonxml_.OutOfElem();
				}
				no_prices:;
			}
		bonxml_.OutOfElem();
		if(fl_cmt_==NO){
			//if(FindBewArt(BewCount),YES) {
			//	BewLijn[BewCount].ArtRec=*u(6,1);BewLijn[BewCount].Rec11=*u(11,1);
			//	
			//	copy(s(6,3),BewLijn[BewCount].Naam,fldlen(6,3));
			//}
			BewCount++; if(BewCount>=DIM_BEWLIJN) break;
		}
	}
	bonxml_.Close();
	FindBewArt(BewCount,NO);

  return true;
}

static bool DisplayLeverData(char *filename_)
{
  int16 nr_,k,key,z,start_,lijnpos,q_,ScreenLines=15;
	unsigned short funckeys,arec_;
	char attrib_,artcode_[25];
	CString cstr_;
	
  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
    scrnum=0;scrget(3,10);z=1;q_=0; funckeys=0x60E1;
//		scraddpicto(3,0,72,22,4,2,583,0,0,"Maak PDF"); 
		cstr_=CString(filename_); k=cstr_.ReverseFind('\\'); if(k>=0) cstr_=cstr_.Mid(k+1);scrifld(z++,VarTextFmt(35,0),(char *)((LPCTSTR)cstr_));
//		scrofld(z++,2,3,-1);
	  start_++;scrifld(z++,fm_ou3,&start_);start_--;scrifld(z++,fm_ou3,&BewCount);
		if(start_>0){ funckeys+=2; scraddpicto(1,0,76,1,4,2,18,0,4,"up"); }
		if((start_+ScreenLines)<BewCount) {funckeys+=4;scraddpicto(2,0,76,22,4,2,13,0,4,"down"); }
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=BewCount) break;
			attrib_=0xFF; if(BewLijn[k].ArtRec==0) attrib_=0x0B;
			scrifld(z++,VarTextFmt(14,0),BewLijn[k].Code);scrchat(z-1,attrib_);
			scrifld(z++,VarTextFmt(32,0),BewLijn[k].Naam);scrchat(z-1,attrib_);scraddpicto(11+k-start_,z-1,0,0,2,1,69,0,4,"Koppel artikel"); 
			scrifld(z++,fm_of50_,&BewLijn[k].Aantal);
			//scrifld(z++,VarTextFmt(10,0),BewLijn[k].LotNr);
			//scrifld(z++,fm_odat,&BewLijn[k].VervDate);
			z+=2;
	  }
    key=scrupd(-1,funckeys);
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
			case 108     : return true; 
										 break;

			default      : break;
    }
		if(key>=5011 && key<5011+ScreenLines) { // Koppel artikel
			KoppelArtikel(key-5011+start_,YES);
			copy(BewLijn[key-5011+start_].Code,artcode_,sizeof BewLijn[0].Code); arec_=BewLijn[key-5011+start_].ArtRec;
			for(k=0;k<BewCount;k++) if(cmpstr(BewLijn[k].Code,artcode_,sizeof BewLijn[0].Code)==0){ // hele lijst overlopen met zelfde artikel
				copy(artcode_,BewLijn[k].Code,sizeof BewLijn[0].Code); BewLijn[k].ArtRec=arec_; 
			}
		}
	}
	return true;
}

static void AddBon2Doc(void)
{
	int16 n,j,k,ok_;
	char artnm_[50];
	float factor_,acc_factor_;

	if(DRK0211Mode){ // via structuur van 211, zelfde houden als in ovl0211 !!!
		scrget(1,7);scrupd(-3,0);
		for(j=0;j<max_line;j++){ram2stu(j); tblin.calc_qlv=tblin.qlv; tblin.qlv=0;tblin.stuks_fl='\0'; stu2ram(j);}
		for(n=0;n<BewCount;n++){
			if(BewLijn[n].ArtRec){
				*u(6,1)=BewLijn[n].ArtRec; fasgeti(6);
				factor_=1.;// if(BewLijn[n].AfwijkendAantal && *f(6,31)) factor_= BewLijn[n].AfwijkendAantal/ *f(6,31);
				acc_factor_=1.; if(BewLijn[n].AfwijkendAantal && *f(6,31)) acc_factor_= BewLijn[n].AfwijkendAantal/ *f(6,31); // accijns moet volgens artikel zijn
				for(j=0;j<max_line;j++){
					ram2stu(j);
					if(tblin.rec==*u(6,1)){
						tblin.qlv+=BewLijn[n].Aantal*factor_;copy0(BewLijn[n].Code,tblin.ref_lev,15); 
						if(BewLijn[n].Prijs) tblin.tbprx[0]=Round((double)(BewLijn[n].Prijs/factor_),(double)(0.001));
						if(BewLijn[n].Accijns) tblin.accijns=Round((double)(BewLijn[n].Accijns/acc_factor_),(double)(0.001));
						tblin.rec11=BewLijn[n].Rec11;
					  stu2ram(j);
						break;
					}
				}
				if(j>=max_line){
					for(j=max_line-1;j>=0;j--){
						ram2stu(j);
						if(test_line()) break;
					}
					j++;
					if(j>=0  && j<max_line){
						ram2stu(j);
						tblin.rec=*u(6,1); copy(s(6,2),tblin.code,fldlen(6,2)); copy(s(6,3),tblin.omschr,fldlen(6,3)); tblin.qlv=BewLijn[n].Aantal*factor_;
						copy(s(6,29),tblin.PlMag,fldlen(6,29));
						copy0(BewLijn[n].Code,tblin.ref_lev,15);
						if(BewLijn[n].Prijs) tblin.tbprx[0]=Round((double)(BewLijn[n].Prijs/factor_),(double)(0.001));
						if(BewLijn[n].Accijns) tblin.accijns=Round((double)(BewLijn[n].Accijns/acc_factor_),(double)(0.001));
						tblin.rec11=BewLijn[n].Rec11;
						stu2ram(j); 
					}
				}
			}
			else{
				zero(artnm_,sizeof artnm_); artnm_[0]='+'; copy0(BewLijn[n].Code,&artnm_[1],fldlen(6,3)-1); 
				for(j=0;j<max_line;j++){
					ram2stu(j);
					if(tblin.rec==0 && cmpstr(artnm_,tblin.omschr,fldlen(6,3))==0){
						tblin.qlv+=BewLijn[n].Aantal; copy0(BewLijn[n].Code,tblin.ref_lev,15);
						if(BewLijn[n].Prijs) tblin.tbprx[0]=BewLijn[n].Prijs;
						if(BewLijn[n].Accijns) tblin.accijns=BewLijn[n].Accijns;
						stu2ram(j);break;
					}
				}
				if(j>=max_line){
					for(j=max_line-1;j>=0;j--){
						ram2stu(j);
						if(test_line()) break;
					}
					j++;
					if(j>=0 && j<max_line){
						ram2stu(j);
						copy(artnm_,tblin.omschr,fldlen(6,3));copy0(BewLijn[n].Code,tblin.ref_lev,15);
						tblin.qlv=BewLijn[n].Aantal;
						if(BewLijn[n].Prijs) tblin.tbprx[0]=BewLijn[n].Prijs;
						if(BewLijn[n].Accijns) tblin.accijns=BewLijn[n].Accijns;
						stu2ram(j); 
					}
				}
			}
		}
	}
	else{ // via stu 58
		scrget(1,7);scrupd(-3,0);
		for(j=0;j<max_line;j++){ram2stu(j); *f(58,61)=*f(58,31); *f(58,7)=0; *s(58,62)='\0';stu2ram(j);}
		for(n=0;n<BewCount;n++){
			if(BewLijn[n].ArtRec){
				*u(6,1)=BewLijn[n].ArtRec; fasgeti(6);
				factor_=1.;// if(BewLijn[n].AfwijkendAantal && *f(6,31)) factor_= BewLijn[n].AfwijkendAantal/ *f(6,31);
				acc_factor_=1.; if(BewLijn[n].AfwijkendAantal && *f(6,31)) acc_factor_= BewLijn[n].AfwijkendAantal/ *f(6,31); // accijns moet volgens artikel zijn
				for(j=0;j<max_line;j++){
					ram2stu(j);
					if(*u(58,14)==*u(6,1) && *f(58,73)>=0.001){
						*f(58,7)+=BewLijn[n].Aantal*factor_; 
						if(BewLijn[n].Prijs) *f(58,73)=Round((double)(BewLijn[n].Prijs/factor_),(double)(0.001));
						else if(BewLijn[n].KortPct==100.) *f(58,73)=0.0001;
						if(BewLijn[n].Accijns) *f(58,38)=Round((double)(BewLijn[n].Accijns/acc_factor_),(double)(0.001));
						stu2ram(j);
						break;
					}
				}
				if(j>=max_line){
					for(j=max_line-1;j>=0;j--){
						ram2stu(j);
						if(test_line()) break;
					}
					j++;
					if(j>=0 && j<max_line){
						ram2stu(j);
						*u(58,14)=*u(6,1); copy(s(6,2),s(58,15),fldlen(58,15)); copy(s(6,3),s(58,16),fldlen(58,16)); *f(58,7)=BewLijn[n].Aantal*factor_;
						if(BewLijn[n].Prijs) *f(58,73)=Round((double)(BewLijn[n].Prijs/factor_),(double)(0.001));
						if(BewLijn[n].Accijns) *f(58,38)=Round((double)(BewLijn[n].Accijns/acc_factor_),(double)(0.001));
						if(BewLijn[n].KortPct==100.) *f(58,73)=0.0001;
						stu2ram(j); 
					}
				}
			}
			else{
				zero(artnm_,sizeof artnm_); artnm_[0]='+'; copy0(BewLijn[n].Code,&artnm_[1],fldlen(58,16)-1); 
				factor_=1.;// if(BewLijn[n].AfwijkendAantal && *f(6,31)) factor_= BewLijn[n].AfwijkendAantal/ *f(6,31);
				for(j=0;j<max_line;j++){
					ram2stu(j);
					if(*u(58,14)==0 && cmpstr(artnm_,s(58,16),fldlen(58,16))==0 && *f(58,73)>=0.001){
						*f(58,7)+=BewLijn[n].Aantal; 
						if(BewLijn[n].Prijs) *f(58,73)=BewLijn[n].Prijs;
						if(BewLijn[n].Accijns) *f(58,38)=BewLijn[n].Accijns;
						if(BewLijn[n].KortPct==100.) *f(58,73)=0.0001;
						stu2ram(j);break;
					}
				}
				if(j>=max_line){
					for(j=max_line-1;j>=0;j--){
						ram2stu(j);
						if(test_line()) break;
					}
					j++;
					if(j>=0 && j<max_line){
						ram2stu(j);
						copy(artnm_,s(58,16),fldlen(58,16));
						*f(58,7)=BewLijn[n].Aantal;
						if(BewLijn[n].Prijs) *f(58,73)=BewLijn[n].Prijs;
						if(BewLijn[n].Accijns) *f(58,38)=BewLijn[n].Accijns;
						if(BewLijn[n].KortPct==100.) *f(58,73)=0.0001;
						stu2ram(j); 
					}
				}
			}
		}
	}
	endsr:;
}

static int KoppelArtikel(int listnr_,int DoSelect_) // zoek/koppel Districo-artikel, bij DoSelect_ YES, altijd laten selecteren
{
	int16 k,q_,n,z,key,curs=6,start_,mode6_,mode11_,found_=NO,retval_=0,MaxScrLines=12;
	uint16 nr_,orig_rec11=0,orig_rec6=0;
	int kleur_;
	char SearchText[50],lijn_attrib_,str_[50];
	CString cstr_;

	fasinit(6);
	redo_listnr:;
	zero((char *)&recs[0],sizeof recs);zero((char *)&recs_preferred[0],sizeof recs_preferred);recs_used=0;nr_=0;
	for(k=0;k<fldlen(6,3);k++) if(BewLijn[listnr_].Naam[k]==' ' || BewLijn[listnr_].Naam[k]=='\0') break;
	cstr_=CString(BewLijn[listnr_].Naam,k);cstr_.Trim(); cstr_.MakeUpper();k=cstr_.GetLength();
	zero(SearchText,sizeof SearchText);copy((char *)(LPCTSTR)cstr_,SearchText,k);
	found_=NO;orig_rec11=0;orig_rec6=0;
	fasinit(11); *u(11,2)=*u(1,1); mode11_=1;
	FOREVER{
		next11:;
		if(faskeyi(11,1,mode11_)) break; mode11_=2;
		if(*u(11,2)!=*u(1,1)) break;
		if(*s(11,5)=='\0') goto next11;
		if(NettoCompareStr(BewLijn[listnr_].Code,s(11,5),fldlen(11,5))==0){
			recs[recs_used]=*u(11,3); recs_preferred[recs_used]=2; orig_rec11=*u(11,1);orig_rec6=*u(11,3);recs_used++;
			found_=YES;
 		}
	}
	if(found_){// al gekoppeld
		if(DoSelect_==NO) return YES;
		else goto display; 
	}


	fasinit(6);mode6_=1;
	scrget(1,7);scrupd(-3,0);
	FOREVER{
next_a:;
		if(recs_used>=MAX_RECS) break;
		if(faskeyi(6,2,mode6_)) break; mode6_=2;
		fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);mode11_=1;
		FOREVER{ // controleren of artikel al een code heeft voor deze leverancier 
			if(faskeyi(11,1,mode11_)) break; mode11_=2;
			if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) break;
			if(*s(11,5)) goto next_a; // artikel heeft al een code ingevuld
		}
		cstr_=CString(s(6,3),fldlen(6,3));cstr_.MakeUpper();
		if(cstr_.Find(_T(SearchText),0)>=0) {recs[recs_used++]=*u(6,1);goto next_a;}
		if(recs_used>=MAX_RECS) break;
	}
	display:;
	fasinit(6); start_=0; nr_=0; scrnum=0; 
	FOREVER{
		redo_art:;
		scrnum=0;scrget(3,14);z=1;q_=0;
		if(start_>0) {scraddpicto(1,0,76,2,4,2,18,0,4,"up"); }
		if((start_+MaxScrLines)<recs_used) {scraddpicto(2,0,76,21,4,2,13,0,4,"down");}
//		scraddpicto(5,0,0,0,4,1,16,0,4,"Vorig"); 
//		scraddpicto(6,0,76,0,4,1,17,0,4,"Volgend"); 
		listnr_++;scrifld(z++,fm_ou5,&listnr_);listnr_--;scrifld(z++,fm_ou5,&BewCount);
		scrifld(z++,VarTextFmt(10,0),BewLijn[listnr_].Code);
//		scrifld(z++,VarTextFmt(15,0),BewLijn[listnr_].EAN);
//		scrifld(z++,VarTextFmt(10,0),BewLijn[listnr_].Eenheid);
		scrifld(z++,VarTextFmt(40,0),BewLijn[listnr_].Naam);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
		z++; // scrifld(z++,fm_of42_,&BewLijn[listnr_].Inhoud);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
		z++; // scrifld(z++,fm_of4_0,&BewLijn[listnr_].AantalBak);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
		z++; // scrifld(z++,VarTextFmt(30,0),BewLijn[listnr_].Verpakking);if(found_) scrchat(z-1,0xFF); else scrchat(z-1,0x0B);
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
												BewLijn[listnr_].AfwijkendAantal=0;
												BewLijn[listnr_].ArtRec=0;
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
												fasinit(11); *u(11,2)=*u(1,1); *u(11,3)=recs[n]; mode11_=1;
												FOREVER{
												if(faskeyi(11,1,mode11_)) break; mode11_=2;
												if(*u(11,2)!=*u(1,1) || *u(11,3)!=recs[n]) break;
												if(*s(11,5)){
  												if(NettoCompareStr(BewLijn[listnr_].Code,s(11,5),fldlen(11,5))==0) recs_preferred[n]=2; 
			  									else if(*s(11,5)) recs_preferred[n]=0xFF;
												}
												}
											}
											start_=0;goto redo_art;
											break;
			case 5004    : fasinit(6);copy(SearchText,s(6,3),fldlen(6,3));  // normale zoek
											ExecSearch(0);
											for(n=0;n<recs_used;n++){
												fasinit(11); *u(11,2)=*u(1,1); *u(11,3)=recs[n]; mode11_=1;
												FOREVER{
													if(faskeyi(11,1,mode11_)) break; mode11_=2;
													if(*u(11,2)!=*u(1,1) || *u(11,3)!=recs[n]) break;
													if(*s(11,5)){
														if(NettoCompareStr(BewLijn[listnr_].Code,s(11,5),fldlen(11,5))==0) recs_preferred[n]=2; 
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
		fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);mode11_=1;found_=NO;
		FOREVER{ // zoeken naar record met lege code voor deze leverancier 
			if(faskeyi(11,1,mode11_)) break; mode11_=2;
			if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) break;
			if(*s(11,5) && cmpstr(s(11,5),BewLijn[listnr_].Code,fldlen(11,5))) {found_=YES;break;} // heeft al een code 
		}
		if(found_){
			zero(WarnBuf,sizeof WarnBuf);
			sprintf_s(WarnBuf,100,"Dit artikel is al gekoppeld met ANDERE code %s! Toch doorgaan?",s(11,5));
      if(DisplayWarning(WarnBuf,605,1)==NO) goto redo_listnr;
			zero(s(11,5),fldlen(11,5)); // deze code wegvegen
			if(fldlen(11,68)) *f(11,68)=0;
			fasupd(11);
		}
		if(orig_rec11){ // bij wijziging het origineel wissen
			fasinit(11);*u(11,1)=orig_rec11;fasgeti(11);
			zero(s(11,5),fldlen(11,5));
			if(fldlen(11,68)) *f(11,68)=0;
			fasupd(11);
		}
		fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);mode11_=1;found_=NO;
		FOREVER{ // zoeken naar record met lege code voor deze leverancier 
			if(faskeyi(11,1,mode11_)) break; mode11_=2;
			if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) break;
#if FLAGGBL
		  if(*s(11,5)=='\0' && *s(11,75)=='\0'){found_=YES;break;} // rec11 zonder code -indien opmerking deze nooit kiezen want dit is een manuele prijsopmerking
#else
			if(*s(11,5)=='\0'){found_=YES;break;} // rec11 zonder code 
#endif
		}
		if(found_){ // lege gevonden en invullen
			copy(BewLijn[listnr_].Code,s(11,5),fldlen(11,5));
			if(fldlen(11,68)) *f(11,68)=BewLijn[listnr_].AfwijkendAantal;
			errnum=fasupd(11);
		}
		else{ 
			//fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);mode11_=1;found_=NO;
			//FOREVER{ // zoeken naar record met lege code voor deze leverancier 
			//	if(faskeyi(11,1,mode11_)) break; mode11_=2;
			//	if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) break;
			//	if(*s(11,5)) {found_=YES;break;} // rec11 met code 
			//}
			//zero(WarnBuf,sizeof WarnBuf);zero(str_,sizeof str_); copy0(s(6,3),str_,fldlen(6,3));
			//if(found_){
			//	zero(WarnBuf,sizeof WarnBuf);zero(str_,sizeof str_); copy0(s(6,3),str_,fldlen(6,3));
			//	sprintf_s(WarnBuf,sizeof WarnBuf,"Wenst U deze aankoopfiche te wijzigen: %s ?",str_);
			//	if(DisplayWarning(WarnBuf,605,1)){
			//		copy(BewLijn[listnr_].Code,s(11,5),fldlen(11,5));
			//		if(fldlen(11,68)) *f(11,68)=BewLijn[listnr_].AfwijkendAantal;
			//		errnum=fasupd(11);
			//	}
			//	else{
			zero(WarnBuf,sizeof WarnBuf);zero(str_,sizeof str_); copy0(s(6,3),str_,fldlen(6,3));
			sprintf_s(WarnBuf,sizeof WarnBuf,"Wenst U een aankoopfiche aan te maken voor: %s ?",str_);
			if(DisplayWarning(WarnBuf,605,1)){
				fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);
				copy(BewLijn[listnr_].Code,s(11,5),fldlen(11,5));
				if(fldlen(11,68)) *f(11,68)=BewLijn[listnr_].AfwijkendAantal;
				errnum=fasadd(11);
			}
		}

		
		if(*s(6,71)=='\0' && cmpstr(BewLijn[listnr_].EAN,s(6,70),fldlen(6,70))) copy(BewLijn[listnr_].EAN,s(6,71),fldlen(6,71)); // stuks invullen 
// GEEN BAK 		else if(*s(6,70)=='\0' && cmpstr(BewLijn[listnr_].EAN,s(6,71),fldlen(6,71))) copy(BewLijn[listnr_].EAN,s(6,70),fldlen(6,70));
		fasupd(6);
		BewLijn[listnr_].ArtRec=*u(6,1);
		copy(s(6,3),BewLijn[listnr_].Naam,fldlen(6,3)); // geen naam meegegeven, dus art.naam maar invullen
		BewLijn[listnr_].ArtInhoud=*f(6,37);
		BewLijn[listnr_].ArtAantalBak=*f(6,31);
		BewLijn[listnr_].Rec11=*u(11,1);
		if(fldlen(11,68)) BewLijn[listnr_].AfwijkendAantal=*f(11,68);
//		float factor_=1.; if(BewLijn[listnr_].AfwijkendAantal && BewLijn[listnr_].ArtAantalBak) factor_= BewLijn[listnr_].AfwijkendAantal/ BewLijn[listnr_].ArtAantalBak;
//		BewLijn[listnr_].ArtLevAKprijs=BewLijn[listnr_].ArtAKprijs*factor_;
		return YES;
	}
endsr:;
	return NO;
}

static int CheckInhoud(int listnr_) // controleer inhoud
{
  int16 z,key;
   
//	if(*f(6,37)==BewLijn[listnr_].Inhoud && *f(6,31)==BewLijn[listnr_].AantalBak) return YES; // is OK

  FOREVER{
	redo:;
		scrnum=0;scrget(3,12);z=1;
		scrifld(z++,VarTextFmt(10,0),BewLijn[listnr_].Code);
		scrifld(z++,VarTextFmt(15,0),BewLijn[listnr_].EAN);
		scrifld(z++,VarTextFmt(10,0),BewLijn[listnr_].Eenheid);
		scrifld(z++,VarTextFmt(40,0),BewLijn[listnr_].Naam);
		//scrifld(z++,fm_of42_,&BewLijn[listnr_].Inhoud);
		//scrifld(z++,fm_of4_0,&BewLijn[listnr_].AantalBak);
		//scrifld(z++,VarTextFmt(30,0),BewLijn[listnr_].Verpakking);
		z+=3;
		scrofld(z++,6,2,-1); scrofld(z++,6,3,-1);
		scrifld(z++,fm_uf42_,f(6,37)); scrifld(z++,fm_uf4_0,f(6,31));
		if(fldlen(11,68)) scrifld(z++,fm_uf4_0,&BewLijn[listnr_].AfwijkendAantal);
		key=scrupd(1,0x2A0);
		if(key==106) return NO;

		//if(key==110){
		//	*f(6,37)=BewLijn[listnr_].Inhoud; *f(6,31)=BewLijn[listnr_].AantalBak;
		//	if(fldlen(6,198)) *u(6,198)=procid;
		//	if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
		//}
		if(*f(6,37)==0 && *f(6,38)==0){errnum=38; goto redo;}
		if(key==108) break;
  }
	fasupd(6);
//	float factor_=1.; if(BewLijn[listnr_].AfwijkendAantal && BewLijn[listnr_].ArtAantalBak) factor_= BewLijn[listnr_].AfwijkendAantal/ BewLijn[listnr_].ArtAantalBak;
//	BewLijn[listnr_].ArtLevAKprijs=BewLijn[listnr_].ArtAKprijs*factor_;
  return YES;
}


static int16 FindBewArt(int16 nr_, int16 OnlyThisArt) // zoek artikel op referentie leverancier of EAN
{
	int16 j,k,codelen_,found_=NO,mode_=1;
	char str_[50];
	codelen_=sizeof BewLijn[0].Code; if(codelen_>fldlen(11,5)) codelen_=fldlen(11,5);
	fasinit(11);*u(11,2)=*u(1,1); fasinit(6);
	FOREVER{
		if(faskeyi(11,1,2)) break; 
		if(*u(11,2)!=*u(1,1)) break;
		if(OnlyThisArt){
  		if(NettoCompareStr(BewLijn[nr_].Code,s(11,5),codelen_)==0){*u(6,1)=*u(11,3);fasgeti(6); return YES;}
		}
		else{
			for(k=0;k<nr_;k++){
				if(BewLijn[k].ArtRec) continue;
				if(NettoCompareStr(BewLijn[k].Code,s(11,5),codelen_)==0){
					*u(6,1)=*u(11,3);fasgeti(6);
				  BewLijn[k].ArtRec=*u(6,1);BewLijn[k].Rec11=*u(11,1);
					if(fldlen(11,68)) BewLijn[k].AfwijkendAantal=*f(11,68);
  				copy(s(6,3),BewLijn[k].Naam,fldlen(6,3));
//					break;
  			}
			}
		}
	}
	k=nr_;
	if(OnlyThisArt==NO){
		for(k=0;k<nr_;k++) if(BewLijn[k].ArtRec==0 && BewLijn[k].EAN[0]) break;
	}
	if(k<nr_ || (OnlyThisArt && BewLijn[nr_].EAN[0])){
		fasinit(6);*u(6,7)=*u(1,1);
		FOREVER{
			if(faskeyi(6,4,2)) break; 
			if(*u(6,7)!=*u(1,1)) break;
			if(OnlyThisArt){
				found_=NO;
				if(cmpstr(BewLijn[nr_].EAN,s(6,70),fldlen(6,70))==0) found_=YES;
				if(!found_ && cmpstr(BewLijn[nr_].EAN,s(6,71),fldlen(6,71))==0) found_=YES;
				zero(str_,sizeof str_); copy0(s(6,3),str_,fldlen(6,3));
				zero(WarnBuf,sizeof WarnBuf);	sprintf_s(WarnBuf,sizeof WarnBuf,"Wenst U de aankoopfiche te koppelen aan: %s ?",str_);
#if FLAGGBL // nooit automatiasch koppelen
				if(NO){
#else 
				if(found_ && DisplayWarning(WarnBuf,605,1)){
#endif
					fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);mode_=1;
					FOREVER{
						if(faskeyi(11,1,mode_)) break; mode_=2;
						if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) {fasinit(11);break;}
#if FLAGGBL
		        if(*s(11,5)=='\0' && *s(11,75)=='\0'){ // indien opmerking deze nooit kiezen want dit is een manuele prijsopmerking
#else
						if(*s(11,5)=='\0'){
#endif
							copy(BewLijn[nr_].Code,s(11,5),fldlen(11,5)); 
						  fasupd(11);
							break;
						}
					}
					if(*u(11,1)==0){ // indien nog geen fiche, dan bijmaken
						fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);
						copy(BewLijn[nr_].Code,s(11,5),fldlen(11,5)); 
						fasadd(11);
					}
					return YES;
				}
			}
			else{
				for(k=0;k<nr_;k++){
					if(BewLijn[k].ArtRec==0 && BewLijn[k].EAN[0]){
						found_=NO;
						if(cmpstr(BewLijn[k].EAN,s(6,70),fldlen(6,70))==0) found_=YES;
						if(!found_ && cmpstr(BewLijn[k].EAN,s(6,71),fldlen(6,71))==0) found_=YES;
						zero(str_,sizeof str_); copy0(s(6,3),str_,fldlen(6,3));
						zero(WarnBuf,sizeof WarnBuf);	sprintf_s(WarnBuf,sizeof WarnBuf,"Wenst U de aankoopfiche te koppelen aan: %s ?",str_);
#if FLAGGBL // nooit automatiasch koppelen
						if(NO){
#else 
						if(found_ && DisplayWarning(WarnBuf,605,1)){
#endif
							fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);mode_=1;
							FOREVER{
								if(faskeyi(11,1,mode_)) break; mode_=2;
								if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) {fasinit(11);break;}
#if FLAGGBL
		            if(*s(11,5)=='\0' && *s(11,75)=='\0'){ // indien opmerking deze nooit kiezen want dit is een manuele prijsopmerking
#else
								if(*s(11,5)=='\0'){
#endif
								  copy(BewLijn[k].Code,s(11,5),fldlen(11,5)); 
								  fasupd(11);
									break;
								}
							}
							if(*u(11,1)==0){ // indien nog geen fiche, dan bijmaken
								fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);
								copy(BewLijn[k].Code,s(11,5),fldlen(11,5)); 
								fasadd(11);
							}
							BewLijn[k].ArtRec=*u(6,1);BewLijn[k].Rec11=*u(11,1);
  				    copy(s(6,3),BewLijn[k].Naam,fldlen(6,3));
							if(fldlen(11,68)) BewLijn[k].AfwijkendAantal=*f(11,68);
							for(j=k+1;j<nr_;j++){ // voor de rest ook al invullen
								if(cmpstr(BewLijn[j].Code,BewLijn[k].Code,fldlen(11,5))==0){
							    BewLijn[j].ArtRec=*u(6,1);BewLijn[j].Rec11=*u(11,1);
  				        copy(s(6,3),BewLijn[j].Naam,fldlen(6,3));
							    if(fldlen(11,68)) BewLijn[j].AfwijkendAantal=*f(11,68);
								}
							}
							break;
						}
					}
				}
			}
		}
	}
	for(k=0;k<nr_;k++){ // om lege 11-records toch op de juiste te zetten
		if(BewLijn[k].ArtRec==0) continue;
		if(BewLijn[k].Rec11==0) continue;
		fasinit(11);*u(11,1)=BewLijn[k].Rec11; fasgeti(11); if(*u(11,8)) continue; // er is al een begindatum, dus OK
		fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=BewLijn[k].ArtRec;
		FOREVER{
			next:;
			if(faskeyi(11,2,mode_)) break; mode_=2;
			if(*u(11,3)!=BewLijn[k].ArtRec) break;
			if(*u(11,2)!=*u(1,1)) break;
			if(*u(11,8) && *u(25,2)>=*u(11,8)) {
				BewLijn[k].Rec11=*u(11,1);
				if(fldlen(11,68)) BewLijn[k].AfwijkendAantal=*f(11,68);
			}
		}
	}
	return NO;
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


static void initload() 
{
  int16 k;
	  
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
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,sys3896);
  sysget(3142,50,MapBestelling); 
	sysget(8740,2,(char *)&RecLevPnT);

	ram=RamBon;
	if(DRK0211Mode){ // zelfde houden als ovl211 !!!
		ram_size=75000;
		if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;zero(ram,ram_size);
		len_tblin=sizeof tblin;max_line=ram_size/len_tblin;
		p_tblin=(char *)&tblin.rec;
	}
	else{
		ram_size=125000;
#if FLAGDAL || FLAGJAN //DOUBLE_FACT
    ram_size*=2;
#endif
		if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;
	// ZEKER NIET HIER	zeroL(ram,ram_size);
		stu58_len=fldlen(58,0);max_line=ram_size/stu58_len;
	}
	InitConvertTab();  // komt uit JMS
}

static void InitConvertTab()  // komt uit JMS
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


static void ram2stu(int16 lin_)
{
	if(DRK0211Mode) copy(ram+(lin_*len_tblin),p_tblin,len_tblin);
  else copy(ram+(lin_*stu58_len),s(58,1),stu58_len);
}
						
static void stu2ram(int16 lin_)
{
	if(DRK0211Mode) copy(p_tblin,ram+(lin_*len_tblin),len_tblin);
  else copy(s(58,1),ram+(lin_*stu58_len),stu58_len);
}

static int test_line(void)
{
	if(DRK0211Mode){
		if(tblin.code[0] || tblin.omschr[0]) return YES;
	}
	else{
    if(*s(58,15) || *s(58,16) || *f(58,20)) return YES;
	}
  return NO;
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
 
static uint16 String2Date(CString datestr_,CString format_)

{
 
  unsigned dt_;
  int dd_,mm_,jj_,posd_,posm_,posj_,lenj_,len_,lenfm_;
  CString fm_date_;
   
  fm_date_=format_; 
  lenfm_=fm_date_.GetLength();  len_=datestr_.GetLength();
  if(lenfm_!=len_){
    if(lenfm_==len_+2 && fm_date_.Find("JJJJ")>=0){
      fm_date_.Replace("JJJJ","JJ");lenfm_-=2;
    }
    else if(lenfm_==len_-2 && fm_date_.Find("JJJJ")<0 && fm_date_.Find("JJ")>=0){
      fm_date_.Replace("JJ","JJJJ");lenfm_+=2;
    }
    else return 0;
  }

  posd_=fm_date_.Find("DD"); if(posd_<0) return 0;
  posm_=fm_date_.Find("MM"); if(posm_<0) return 0;
  posj_=fm_date_.Find("JJJJ"); 
  if(posj_>=0){lenj_=4;}
  else {
    posj_=fm_date_.Find("JJ"); 
    if(posj_<0) return 0;
    else lenj_=2;
  }
  dd_=String2Int(datestr_.Mid(posd_,2));
  mm_=String2Int(datestr_.Mid(posm_,2));
  jj_=String2Int(datestr_.Mid(posj_,lenj_)); if(lenj_==2) jj_+=2000;
  dt_=datejd(jj_,mm_,dd_);
  return dt_;
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
 

static int copy0(char *ps_, char *pd_, int maxlen_)
{
  int k;

  for(k=0;k<maxlen_;k++){
    if(*ps_=='\0') break;
    *pd_++=*ps_++;
  }
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

static int NettoCompareStr(char *p1,char *p2,int16 len)
{
  char buf1_[100],buf2_[100];
	int16 len1_,len2_;
					
	
	len1_=GetSearchText(p1,buf1_,len);buf1_[len1_]=0;
	len2_=GetSearchText(p2,buf2_,len);buf2_[len2_]=0;
//	len1_=strcmp(buf1_,buf2_);
	return strcmp(buf1_,buf2_);
}

static int GetSearchText(char *s,char *d, int len)  // analoog aan JMS (composekey)
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