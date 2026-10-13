/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* DRK2241GetD() {return &zzvw;}
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

extern "C" char DRK2241dat[] = "drk2241  00:22 21/10/10 (c) Jamadata"; // Inlezen eigen bestelXLS 

// FLAGWYN : Bestelformulier/XLS klant : aantal in 1-ste kolom



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
#define DIMBTW          8
#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */
#define CSV_FIELDDELIM		  '\x09' // ","

#define KLEUR_WIT           0xFFFFFF

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

static int16 prt2pdf,BewCount,filiaal;
static char sys3896[6],fmt[40],ScheidingsTeken='\x09',SelectieEenheid[10],MapKlantBestelling[50];
static char filnam[100],def_munt[4],buf1000[1000],nm_loc[10][6];
static char lev_res[60],klt_res[60],art_res[60];
static uint16 dat_beg,dat_end,inq_lev=0,loc_klt[20],loc_nr[20];
static flag sys3894,sys2982;
static flag sear_stt,sys3876;

static struct {
	char Code[20];
	char Naam[40];
	float Aantal;
	char StuksKar;
} BewLijn[DIM_BEWLIJN];

/* --------------------------- Declaratie functies ---------------------- */

static void AddBestelling2Doc(char *bestelfilename_);
static int copy0(char *ps,char *pd,int max);
static double Round(double getal, double round);
static int DisplayBestelFile(char *bestelfilename_);
static int DisplayWarning(char *ptxt, int icoon);
static void fileopen(int16 nr_);
static int fmt_get(int16 stu_, int16 elet_);
static void initload(void);
static void nextline(void);
static int OpenXlsFile(char *text_,uint16 datum_);
static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_);
static bool ReadBestelFile(char *bestelfilename_);

static void ram2stu(int16 lin_);
static void stu2ram(int16 lin_);
static int test_line(void);

static char *ram;
static long ram_size;
static int16 stu58_len,max_line;

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

extern "C" void DRK2241cod(int parmval)
{
	int k,n,klt_empty_;
	char str_selectie_[100];
	int16 StylHidden, StylNormal, StylNormalCt;
  char txt_[100];

  initload();

	if(parmval==0){ // laden bestelxls vanuit ovl0240/ovl0155
		copy(s(2,1),buf1000,fldlen(2,0));
		klt_empty_=YES; if(*s(2,3)) klt_empty_=NO; fasinit(2);
		zero(str_selectie_,sizeof str_selectie_); retcall=0;
		k=copy0(MapKlantBestelling,str_selectie_,50); k+=copy0("*.XLS*",&str_selectie_[k],6);
		FOREVER{
  		if(GetFileFromSelection(" Bestellingen van klanten ",str_selectie_)==0) break;
  		if(ReadBestelFile(SelectedFileName)){
				if(DisplayBestelFile(SelectedFileName)) {
					AddBestelling2Doc(SelectedFileName);
					if(BestelFileUsed[0][0]=='\0') {copy0(SelectedFileName,BestelFileUsed[0],100); *(uint16 *)&BestelFileUsed[0][100]=2241;}
					else {copy0(SelectedFileName,BestelFileUsed[1],100); *(uint16 *)&BestelFileUsed[1][100]=2241;}
					retcall=YES; break;
				}
			}
		}
		if(klt_empty_==NO || retcall==0) copy(buf1000,s(2,1),fldlen(2,0));
	}
	else if(parmval==1){ // aanmaken interne bestelxls voor filiaal vanuit ovl0255 (cfr CRA)
		scrget(1,7);scrupd(-3,0);
		sysget(2770,60,(char *)&nm_loc[0][0]);
		zero(txt_,sizeof txt_);
		k=copy0("Bestelling ",&txt_[0],30);
		if(fldlen(8,48)){
			if(*u(8,48)==99 || *u(8,48)==0) k+=copy0("DEPOT ",&txt_[k],6);
			else if(*u(8,48)>0 && *u(8,48)<=10 && fldlen(66,11+(*u(8,48)-1)*15) && nm_loc[*u(8,48)-1][0]){ k+=copy0(nm_loc[*u(8,48)-1],&txt_[k],6);txt_[k++]=' ';}
		}
		k+=copy0(s(1,3),&txt_[k],20); for(n=0;n<k;n++) if(txt_[n]=='/') txt_[n]=' ';
		fasinit(2);copy(txt_,s(2,3),fldlen(2,3));
		XlsRef=OpenXlsFile(txt_,*u(25,2));
    if(XlsRef<=0) {errnum=1;goto endsr;}
		zero(txt_,sizeof txt_);
		k=copy0("Bestelling",&txt_[0],30);
		XlsSelectWorkSheet(XlsRef,1,txt_); XlsStyle(XlsRef,"PORTRAIT",0,0,NO,NO,NO,0,0,0,0,0,0,NO,NO); // Afdruk in PORTRAIT mode (met JMS versie 53 of hoger
	  XlsColumnSize(XlsRef,1,8);
		XlsColumnSize(XlsRef,2,50);
		XlsColumnSize(XlsRef,3,10);
		XlsColumnSize(XlsRef,2,10);
		// Styles
		StylHidden=XlsStyle(XlsRef,"",5,KLEUR_WIT,YES,NO,NO,1,0,KLEUR_WIT,1,0,0,YES,YES);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,1,0,KLEUR_WIT,1,1,0,YES,NO);
		StylNormalCt=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,2,0,KLEUR_WIT,1,1,0,YES,NO);

		XlsRij=1;XlsKol=1;

		XlsStyle(XlsRef,"",5,KLEUR_WIT,YES,NO,NO,1,0,KLEUR_WIT,1,0,0,YES,YES);
		zero(txt_,sizeof txt_);copy("**0101",txt_,6);stcli_d(&txt_[6],(long)(*u(8,48)+30000),5,0);copy("**",&txt_[11],2); // >30000 = filiaalnummer
		XlsWrite(XlsRef,XlsRij,1,0,txt_,StylHidden); // soort document + klantrecord hidden
    
		WriteFld2Xls(XlsRij++,2,2,3,StylNormal);
		WriteFld2Xls(XlsRij++,2,2,4,StylNormal);
		zero(txt_,sizeof txt_);k=copy0(s(2,5),txt_,6);txt_[k++]=' ';copy0(s(2,6),&txt_[k],fldlen(2,6));
		XlsWrite(XlsRef,XlsRij++,2,0,txt_,StylNormal); 
			
	  for(n=0;n<max_line;n++){
			ram2stu(n);
			if(test_line()){
				XlsKol=1;
				WriteFld2Xls(XlsRij,XlsKol++,58,15,StylNormal); 
				WriteFld2Xls(XlsRij,XlsKol++,58,16,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,58,12,StylNormalCt);
				WriteFld2Xls(XlsRij,XlsKol++,58,7,StylNormalCt);
				WriteFld2Xls(XlsRij,XlsKol++,58,62,StylNormalCt);
				XlsRij++;
			}
	  }
		XlsRij++;//XlsRij++;
		for(k=0;k<5;k++){
			XlsWrite(XlsRef,XlsRij,2,0,"",StylNormal);
			XlsWrite(XlsRef,XlsRij,3,0,"",StylNormal);
			XlsWrite(XlsRef,XlsRij,4,0,"",StylNormal);
			XlsRij++;
		}
		XlsClose(XlsRef,1);
	  goto endsr;
	}
	endsr:;
  ovlexit(-1);
}
 
static int DisplayBestelFile(char *bestelfilename_)
{
  int16 nr_,k,key,z,start_,lijnpos,q_,ScreenLines=15;
	unsigned short funckeys;
	CString cstr_;
	
  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
    scrnum=0;scrget(3,10);z=1;q_=0; funckeys=0x60E1;
//		scraddpicto(3,0,72,22,4,2,583,0,0,"Maak PDF"); 
		cstr_=CString(bestelfilename_); k=cstr_.ReverseFind('\\'); if(k>=0) cstr_=cstr_.Mid(k+1);scrifld(z++,VarTextFmt(35,0),(char *)((LPCTSTR)cstr_));
		scrofld(z++,2,3,-1);
	  start_++;scrifld(z++,fm_ou3,&start_);start_--;scrifld(z++,fm_ou3,&BewCount);
		if(start_>0){ funckeys+=2; scraddpicto(1,0,76,1,4,2,18,0,4,"up"); }
		if((start_+ScreenLines)<BewCount) {funckeys+=4;scraddpicto(2,0,76,22,4,2,13,0,4,"down"); }
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=BewCount) break;
			scrifld(z++,VarTextFmt(8,0),BewLijn[k].Code);
			scrifld(z++,VarTextFmt(40,0),BewLijn[k].Naam);
			scrifld(z++,fm_of4_2,&BewLijn[k].Aantal);
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
	}
	return true;
}

static void AddBestelling2Doc(char *bestelfilename_)
{
	int16 n,k,sys3894;
	char def_inc;
	SYSTEMTIME fsystime_;
	WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
  FILETIME loc_ftime_;

	sysget(3894,2,&sys3894);
  k=*s(2,26)-'0'; if(k<0 || k>9) k=0; 
  def_inc='N';if(sys3894 & (1<<k)) def_inc='J';

//	if(fldlen(8,48) && filiaal) *u(8,48)=filiaal;

  for(k=max_line-1;k>=0;k--){
    ram2stu(k);
    if(test_line()) break;
  }
  k++; if(k>=max_line-2) goto endsr;
  ram2stu(k); copy("*Bestelling ",s(58,16),12); 
  hSearch = FindFirstFile (bestelfilename_, &FileData);
  if (hSearch != INVALID_HANDLE_VALUE){
		FindClose(hSearch);
		FileTimeToLocalFileTime(&FileData.ftLastWriteTime,&loc_ftime_); // eerst in locale tijd zetten 
		FileTimeToSystemTime(&loc_ftime_,&fsystime_); 
		sprintf(s(58,16)+12," %d/%d/%d %d:%d ",(int)fsystime_.wDay,(int)fsystime_.wMonth,(int)fsystime_.wYear,(int)fsystime_.wHour,(int)fsystime_.wMinute);
	}
  if(fldlen(58,62)) *s(58,62)='S';
  if(k) stu2ram(k++);
  for(n=0;n<BewCount;n++){
		if(k>=max_line) break;
		ram2stu(k);
		copy(BewLijn[n].Code,s(58,15),fldlen(58,15));
#if FLAGAST
		if(BewLijn[n].Naam[0]!='*'){
  		fasinit(6);copy(s(58,15),s(6,2),fldlen(6,2));
	  	if(faskeyi(6,1,0)==0) copy(s(6,3),s(58,16),fldlen(58,16));
		}
#endif
		if(*s(58,16)=='\0') copy(BewLijn[n].Naam,s(58,16),fldlen(58,16));
		*f(58,7)=BewLijn[n].Aantal;
		if(fldlen(58,62)) *s(58,62)=BewLijn[n].StuksKar;
    *f(58,21)=*f(2,18);
#if EET_RIST
    if(fldlen(2,56)) *f(58,21)=*f(2,56);
#endif
    if(fldlen(58,27)) *s(58,27)=def_inc;
		stu2ram(k++);
	}
	endsr:;
}


static bool ReadBestelFile(char *bestelfilename_)
{
	char buf_[100];
  CString line_,cstr_;
  int k,KolNrs[10],kol_aantal_,kol_code_;

	kol_code_=1; kol_aantal_=4;
#if FLAGWYN // aantal op kolom 1
	kol_code_=4; kol_aantal_=1;
#endif
	filiaal=0;
	for(k=0;k<10;k++) KolNrs[k]=-1;
	scrget(1,7);scrupd(-3,0);
  if( (XlsRef=XlsOpen(bestelfilename_))<=0){
		sprintf(buf_,"Kan bestelling \'%s\' niet openen!",bestelfilename_);
		DisplayWarning(buf_,605,0);
 		return 0;
	}
	XlsMaxKol=XlsGetMaxKol(XlsRef); XlsMaxRij=XlsGetMaxRij(XlsRef);
	if(XlsMaxKol<4 || XlsMaxRij<3){
		XlsClose(XlsRef,1);
		sprintf(buf_,"Ongeldig bestand \'%s\' niet openen!",bestelfilename_);
		DisplayWarning(buf_,605,0);
 		return 0;
	}

	zeroL((char *)&BewLijn[0].Code,sizeof BewLijn);BewCount=0;
	XlsKol=1;XlsRij=1;
	zero(buf_,sizeof buf_); 
	XlsReadString(XlsRef,1,1,buf_,50); cstr_=CString(buf_); // verborgen recordnummer
	fasinit(2);
	if(cmpstr("**0101",buf_,6)==0){ // verborgen recordnummer
		fasinit(2);*u(2,1)=val(&buf_[6]); if(*u(2,1)) fasgeti(2);
		if(*u(2,1)>=30000 && fldlen(8,48)){
      filiaal=*u(2,1)-30000;
			if(filiaal<1 || filiaal>10) filiaal=99;
			for(k=0;k<10;k++) if(loc_nr[k]==filiaal && loc_klt[k]) break;
			if(k<10){*u(2,1)=loc_klt[k];fasgeti(2);}
		}
	}
	if(*u(2,1)==0){ // dan op naam proberen
    XlsReadString(XlsRef,1,2,s(2,3),fldlen(2,3)); 
		if(faskeyi(2,2,0)) fasinit(2);
	}
	XlsRij=2;BewCount=0;
	for(XlsRij;XlsRij<XlsMaxRij+1;XlsRij++){
		if(XlsRij>XlsMaxRij-5){ // losse artikels 
  		zero(buf_,sizeof buf_); XlsReadString(XlsRef,XlsRij,2,buf_,50); cstr_=CString(buf_);
		  cstr_.Trim(); if(cstr_.GetLength()==0) continue; // geen tekst ingevuld
			BewLijn[BewCount].Aantal=XlsReadDouble(XlsRef,XlsRij,kol_aantal_);  // aantal
			XlsReadString(XlsRef,XlsRij,5,&BewLijn[BewCount].StuksKar,1); 
		}
		else{
			zero(buf_,sizeof buf_); XlsReadString(XlsRef,XlsRij,kol_code_,buf_,50); cstr_=CString(buf_);
			cstr_.Trim(); if(cstr_.GetLength()==0) continue; // geen code ingevuld
			BewLijn[BewCount].Aantal=XlsReadDouble(XlsRef,XlsRij,kol_aantal_);  // aantal
			if(BewLijn[BewCount].Aantal==0) continue;
			XlsReadString(XlsRef,XlsRij,5,&BewLijn[BewCount].StuksKar,1); 
		}
		XlsReadString(XlsRef,XlsRij,kol_code_,BewLijn[BewCount].Code,sizeof BewLijn[0].Code);  // code
		XlsReadString(XlsRef,XlsRij,2,BewLijn[BewCount].Naam,sizeof BewLijn[0].Naam);  // omschrijving
		BewCount++;
    if(BewCount>=DIM_BEWLIJN) break;
	}
	XlsClose(XlsRef,1);
  return true;
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
	sysget(19550,50,MapKlantBestelling); 

  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);
  sysget(4294,40,(char *)&loc_klt[0]);


	ram=RamBon;
  ram_size=125000;
  if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;
// ZEKER NIET HIER	zeroL(ram,ram_size);
  stu58_len=fldlen(58,0);max_line=ram_size/stu58_len;
}

static void ram2stu(int16 lin_)
{
  copy(ram+(lin_*stu58_len),s(58,1),stu58_len);
}
						
static void stu2ram(int16 lin_)
{
  copy(s(58,1),ram+(lin_*stu58_len),stu58_len);
}

static int test_line(void)
{
  if(*s(58,15) || *s(58,16) || *f(58,20)) return YES;
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

static int OpenXlsFile(char *text_,uint16 datum_)
{
	int16 pos_,dd,mm,yy;
  char string[100];
				
  zero(string,sizeof string);
	pos_=copy0(text_,&string[0],30);
  if(datum_){
    string[pos_++]=' ';
    jddate(datum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
	pos_+=copy0(".XLS",&string[pos_],4);
	
  pos_=XlsCreate(string);
	return pos_;
}