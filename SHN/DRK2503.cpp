
/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "Shlobj.h"
extern "C" char* DRK2503GetD() {return &zzvw;}


typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();
extern "C" char DRK2503dat[] = "drk2503  00:01 20/05/16 (c) Jamadata";  // Datamasters/COLDA module 2016


extern "C" int Fld2String(int stunr, int fldnr, char *OutBuffer, int MaxLen);
extern "C" char *VarTextFmt(int len_,int update_);

#define FOREVER         while(1)
#define YES             1
#define NO              0

#define DIM_KLANT			      20000
#define DIM_ARTIKEL				  20000
#define DIM_OMZETARTIKEL	  2000
#define DIM_POSTCODE			  650
#define DIM_WHSDOSSIERS     2
#define CSV_FIELDDELIM		  ";" // "\x09" // ","
#define MAX_SEARCH_KEYWORDS  10

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF


#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_RDWR         0x0002  /* open for reading and writing */
#define O_APPEND       0x0008  /* writes done at eof */
#define O_CREAT        0x0100  /* create and open file */
#define O_TRUNC        0x0200  /* open and truncate */
#define O_EXCL         0x0400  /* open only if file doesn't already exist */
#define O_TEXT         0x4000  /* file mode is text (translated) */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us60[]  = {7,0xC8,60,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us10[]  = {7,0xC8,10,0,0,0,0};
static char fm_us3[]   = {7,0xC8,3,0,0,0,0};
static char fm_us10U[] = {7,0xC8,10,0,1,0,0};
static char fm_us3_U[] = {7,0xC8,3,0,1,0,0};
static char fm_us2_U[] = {7,0xC8,2,0,1,0,0};
static char fm_us2[]   = {7,0xC8,2,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
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
static char fm_ud6_2[] = {6,0xD5,6,2,0x70,0};
static char fm_ud4_2[] = {6,0xD5,4,2,0x70,0};
static char fm_ud4_0[] = {6,0xD5,4,0,0x70,0};
static char fm_od4_2[] = {6,0x95,4,2,0x70,0};
static char fm_od4_0[] = {6,0x95,4,0,0x70,0};
static char fm_ugrb[]  = {2,0xE8};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_us02[]   = {11,0xC8,1,0,1,0,'0','2',0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uLP[]   = {11,0xC8,1,0,1,0,'L','L','P','P',0};
static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_us8PW[] = {7,0xC8,8,0,5,0,0};
static char fm_uRKSLW[] = {17,0xC8,1,0,1,0,'R','R','K','K','L','L','S','S','W','W',0};
static char fm_uWHSNr[]= {9,0xC8,7,0,1,0,'0','9',0};

// extern
extern "C" int CheckEmailAdres(char *email_, int len_,int internetcheck_); 
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" int16 Search(int stu_,int mod_);
extern "C" int SendMail(int send_mode);
extern "C" char *VarTextFmt(int len_,int update_);

static CString Cstring2CSV(CString string_fld_);
static bool AddFactuur2Xls(char *pfname_,uint16 inq_lev_,uint16 inq_fab_);
static int ArtUsedInHis(uint16 arec_, uint16 dt_beg_,uint16 dt_end_);
static void CheckInhoud(void);
static float  ExecOneVol(char* Name, char* Ean, float ArtVol, float ArtCnt);
static void InitLoad(void);
static void FillAdresFromFtKlant(void); // adres en btwnr aanvullen van factuurklant
static void Jama2Ascii(char *ps_,int len_);
static bool DetailedXlsFromHisData(void);
static bool PostCodeXlsFromHisData(void);
static void MakeDeHeer(int16 stu_,char *nm_dehr);
static void BlokkeerKlant(void);
static void MailDocument(int SendMode, int mode_);
static void ReadBasisFiches(void);
static void UpdateColdaSettings(void);
static void UpdateDMSettings(void);
static void UpdateSettings(void);

static void InitConvertTab(void);  // komt uit JMS
static void GetSearchKeyWords( char *s);
static int GetSearchText(char *s,char *d,int len);  // analoog aan JMS (composekey)
static int MakeFullRecDens(int stunr, char *FullRecDens);
static int AllKeywordsFound(char *FullRecDens, int FullRecDensLen);
static void DisplayLine(int16 z);

static CString arr2cstr(char *ps, int max_len);
static int copy0(char *ps,char *pd,int max);
static CString Date2String(unsigned int date_,int mode_);
static double Round(double getal, double round);
static double String2Getal(CString S,char decim_kar);

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

#include "Std\XlsFunc.CPP"
// ---------------------------------------

static unsigned SpoolFileNr,CntDispPos;
static char FileName[100],buf1000[1000],CntDispStr[5];
static int MaxKlt,MaxArtikel,MaxArtSelection,MaxPostCode,MaxOmzetArtikel,NrInternalCompany,ViaHistoriek;
static long RecCnt;
static uint16 DatBeg,DatEnd,MailDirect;   
static bool ReadEOFline,BasicsCollection,SilentMode;
static char SearchKeywords[MAX_SEARCH_KEYWORDS][100];
static char ICSBTab[256];

static int fas2sif[32]  = {160,133,131,132,135,130,138,136,137,161,141,140,
              		   139,162,149,147,148,163,151,150,129,154,248,21,
										 254,27,26,24,25,0,0,128};


static uint16 sys3000,sys3002;
static uint16 InqMaand,InqJaar,loc_klt[10],loc_kltIX[10];
static long TbDiversArtikel[10];
static char MailBodyText[5][80],MailTemplate[10],ConfirmKlant='J';

static int FtGood,FtSkipped;
static FILETIME FtFtimeBeg, FtFtimeEnd;

 
static struct _DM_Settings {
	char EmailAdres[60];
	uint16 DMSelectieLeverancier;
	uint16 LastMaand;
  uint16 LastJaar;
	char SoortExport; // 0= niet gedetailleerd, 1= gedetailleerd
	char ExportKlanten;
	char StrSpecKlantKol[15];
	int  SpecKlantKol[5];
	char DoExportDM;
	char DoExportColda;
	char ExportKassaVerkopen;
	char SelectPrijsType[5];
	char SelectSoortKlant[5];
	char ExportBlockedKlanten;
	char DefaultBlockNewKlanten;
} DM_Settings;

static int MaxDMCPostCode;
static char* DMCPostCode;
static struct _DMCPostCodeTable {
	short int PostCode;
	char* FilPos;
} DMCPostCodeTable[DIM_POSTCODE];

static struct _TbKlant {
	unsigned int RecordNr;
	short int     Used;
	short int     UsedPostCode;
	double  Omzet;
	double  OmzetVaten;
	short int     Ix_PostCode;
	char ArtUsed[(DIM_OMZETARTIKEL/8)+1]; // 1 bit per artikel
} *TbKlant=0; // TbKlant[DIM_KLANT];

static struct _TbArtikel {
	unsigned int RecordNr;
	double OldAantal;
	double OldInhoud;
	double NewAantal;
	double NewInhoud;
	long DmCode;
	double Inhoud;
	unsigned int updated;
} *TbArtikel=0; // TbArt[DIM_ARTIKEL];

static struct _tbpostcode{
	CString postcode;
} TbPostCode[DIM_POSTCODE];

static struct _OmzetArtikel {
//	unsigned int RecordNr;
	long   DmCode;
//	int     Used;
	double OmzetPerPostcode[DIM_POSTCODE+1];
	long KlantenPerPostcode[DIM_POSTCODE+1];
} *OmzetArtikel=0; // [DIM_OMZETARTIKEL+1];  DIM_OMZETARTIKEL= totaal

static struct _ft_stu {
  short unsigned ft_nr;
  short unsigned ft_date;
  short unsigned stu8len;
  short unsigned stu58len;
  double alg_tot;
  double belastbt;
  double btw_tot;
  double tot_leeg;
  char opm_foot[4][75];
  short int stu8[200][2];
  short int stu58[200][2];
} ft_stu;

static int InqLev;

static CString JamaCode;
static CString strArchivePath;
static CString strSourcePath;
static CString strNumber;
static CString strPassword;

extern "C" void DRK2503cod(int16 parmval)
{
	int z,key,curs=1;
	char choice='\0';


	// velden : klant   : DM_horecatype : 2,131 : 0=niet (geen omzet), 1-8, 9=blokkeer (manueel afzetten!)
	//          NIET GEBRUIKT : artikel : DM_CodeNr   : 6,140
	//                          artikel : DM_VKVolume : 6,141
	ViaHistoriek=YES; if(fldlen(16,1)==0) ViaHistoriek=NO; // indien geen HIS, dan altijd GEDETAILLEERD via FtKopie
	if(ViaHistoriek==NO && ovltest(234)==0) goto endsr; // geen herafdruk facturen

	if(fldlen(2,131)==0/* || fldlen(6,140)==0 || fldlen(6,141)==0*/) ovlexit(-1); // uit veiligheid
	if(FasFileOpen(1)==false) {DisplayWarning("Unable to open LEV-fasfile!",605,0); goto endsr;}
  if(FasFileOpen(2)==false) {DisplayWarning("Unable to open KLT-fasfile!",605,0); goto endsr;}
	if(FasFileOpen(6)==false) {DisplayWarning("Unable to open ART-fasfile!",605,0); goto endsr;}
  if(ViaHistoriek && FasFileOpen(13)==false) {DisplayWarning("Unable to open HIS-fasfile!",605,0);goto endsr;}
	InitLoad();
		// !!! worden gedelete in hoofdroutine OvlCod!!!
	InqMaand=0;InqJaar=DM_Settings.LastJaar;
	FOREVER{
redo:;
		scrget(3,3);z=1;
		scraddpicto(9,0,76,22,4,2,59,0,4,"Parameters");
		scraddpicto(1,0,35,5,6,3,573,0,0,"Maak XLS"); 
		scraddpicto(2,0,42,5,6,3,569,0,0,"Mail gegevens"); 
		scrifld(z++,fm_uu2,&InqMaand);
		scrifld(z++,fm_uu4,&InqJaar);
		if(ViaHistoriek==NO) {scrifld(z++,fm_os1,"-"); DM_Settings.DoExportDM='N';} 
		else scrifld(z++,fm_uJN,&DM_Settings.DoExportDM);
		scrifld(z++,fm_uJN,&DM_Settings.DoExportColda);
		scrifld(z++,fm_ou2,&DM_Settings.LastMaand);
		scrifld(z++,fm_ou4,&DM_Settings.LastJaar);
		key=scrupd(curs,0x381);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) goto endsr;
		if(key==5009){ UpdateSettings();goto redo;}
		if(InqMaand<1 || InqMaand>12) {curs=1;errnum=34; goto redo;}
		if(InqJaar<2010 || InqJaar>2030) {curs=2;errnum=34; goto redo;}
		MailDirect=NO; if(key==109 || key==5002){MailDirect=YES;key=108;}
		if(key==110) CheckInhoud();
		if(key==108 || key==5001) break;
	}
	DM_Settings.LastMaand=InqMaand;DM_Settings.LastJaar=InqJaar;
	sysput(3044,2,(char *)&DM_Settings.LastMaand); 
	sysput(3046,2,(char *)&DM_Settings.LastJaar);
	sysput(3048,1,(char *)&DM_Settings.ExportKlanten);	
	sysput(3111,1,(char *)&DM_Settings.SoortExport);	
	sysput(3137,1,(char *)&DM_Settings.DoExportDM);
	sysput(3138,1,(char *)&DM_Settings.DoExportColda);
	if(DM_Settings.DoExportDM=='J'){
		PostCodeXlsFromHisData();
		if (TbArtikel) {delete TbArtikel; TbArtikel=0;}
		if(TbKlant){ delete TbKlant; TbKlant=0;}
		if(OmzetArtikel) {delete OmzetArtikel;OmzetArtikel=0;}
		if(DMCPostCode) {delete DMCPostCode;DMCPostCode=0;} 
	}
	if(DM_Settings.DoExportColda=='J'){
		DetailedXlsFromHisData();
		if (TbArtikel) {delete TbArtikel; TbArtikel=0;}
		if(TbKlant){ delete TbKlant; TbKlant=0;}
		if(OmzetArtikel) {delete OmzetArtikel;OmzetArtikel=0;}
		if(DMCPostCode) {delete DMCPostCode;DMCPostCode=0;} 
	}

endsr:;
	if (TbArtikel) {delete TbArtikel; TbArtikel=0;}
	if(TbKlant){ delete TbKlant; TbKlant=0;}
	if(OmzetArtikel) {delete OmzetArtikel;OmzetArtikel=0;}
	if(DMCPostCode) {delete DMCPostCode;DMCPostCode=0;} 
	ovlexit(-1); 
}

static bool PostCodeXlsFromHisData(void) // export DataMasters
{
	int j,k,n,g,p_dcm_firma,tbpc[DIM_POSTCODE],mode16,sw,pos_,ix_omz_,nrpc_,q_postcodes_,len,pos,j1,j2,spec_kol_[5];
	char str_[40],kar_;
	short int JaarBeg,MaandBeg,JaarEnd,MaandEnd,act_maand,act_jaar,jj,mm,dd;
	long lbd_, tot_sku_, lijn_tot_;
	uint16 krec_,inq_lev_,inq_fab_,dt_beg_,dt_end_;
	int16 StylVolume;
	CString cstr_,dossier_,artnaam_,supnaam_;
	double omzet_,hl_factor_=100;
	CFile fil;
	  
	//if(FasFileOpen(1)==false) {DisplayWarning("Unable to open LEV-fasfile!",605,0); return false;}
 // if(FasFileOpen(2)==false) {DisplayWarning("Unable to open KLT-fasfile!",605,0); return false;}
	//if(FasFileOpen(6)==false) {DisplayWarning("Unable to open ART-fasfile!",605,0); return false;}
 // if(FasFileOpen(13)==false) {DisplayWarning("Unable to open HIS-fasfile!",605,0);return false;}

	// !!! worden gedelete in hoofdroutine OvlCod!!!
	if (!TbArtikel) TbArtikel = new _TbArtikel[DIM_ARTIKEL]; 
	if (!TbArtikel) return false;
	memset(TbArtikel,0,DIM_ARTIKEL * sizeof TbArtikel[0]);
	if(!TbKlant) TbKlant= new _TbKlant[DIM_KLANT];
	if(!TbKlant) return false;
	memset(TbKlant,0,DIM_KLANT * sizeof TbKlant[0]);
	if(!OmzetArtikel) OmzetArtikel = new _OmzetArtikel[DIM_OMZETARTIKEL+1];
	if(!OmzetArtikel) return false;
	memset(OmzetArtikel,0,(DIM_OMZETARTIKEL+1) * sizeof OmzetArtikel[0]);// DIM_OMZETARTIKEL= totaal

	if (!fil.Open(_T("PostCode.csv"),CFile::modeRead,0)) return false;
	len = (int)fil.GetLength();
	if(!DMCPostCode) DMCPostCode = new char[len+10];
	if (DMCPostCode==NULL) {
		fil.Close();
		return false;
	}
	memset(DMCPostCode,0,len+10);
	fil.Read(DMCPostCode,len);
 	fil.Close();
	MaxDMCPostCode=0;
	for (int i=0; i<len; ) {
    pos=i;
		while (DMCPostCode[pos]!=';') pos++;
		DMCPostCode[pos++]=0;
		int ix=atol(&DMCPostCode[i]);
		i=pos;
		while (DMCPostCode[pos]!=';' && DMCPostCode[pos]!='\r') pos++;
		DMCPostCode[pos++]=0;
		DMCPostCodeTable[MaxDMCPostCode].PostCode=ix;
		DMCPostCodeTable[MaxDMCPostCode].FilPos=&DMCPostCode[i];
		i=pos;
		while (DMCPostCode[pos]!=';' && DMCPostCode[pos]!='\r') pos++;
		DMCPostCode[pos++]=0;
		if(ix>=1000 && ix<=9999 && DMCPostCode[i]=='1') MaxDMCPostCode++;
		if(MaxDMCPostCode>=DIM_POSTCODE) break;
		while (DMCPostCode[pos++]!='\n');
		i=pos;
	}
	// postcode kassaklanten tussenvoegen
	n=0;// if(DM_Settings.ExportKassaVerkopen!='J') n=10; // GEEN kassaverkoop
	for(n=0;n<10;n++){
		if(loc_klt[n]==0) continue;
		fasinit(2);*u(2,1)=loc_klt[n];fasgeti(2);
//		if(*s(2,131)=='J') continue;
		if(*s(2,5)=='\0') sysget(91,4,s(2,5)); // indien niet ingevuld dan postcode van firma nemen 
		g=0;zero(str_,sizeof str_);
		for(k=0;k<fldlen(2,5);k++){ // enkel cijfers eruit halen
			kar_=*(s(2,5)+k);
			if(kar_=='\0') break;
			if(kar_>='0' && kar_<='9') str_[g++]=kar_;
			if(g>=4) break;
		}
		cstr_=arr2cstr(str_,4);cstr_.Trim();
		j1=atol(cstr_);
		for(k=0;k<MaxDMCPostCode;k++) if(j1==DMCPostCodeTable[k].PostCode) break;
		if(k>=MaxDMCPostCode){ // enkel de steden
			str_[3]='0';	cstr_=arr2cstr(str_,4);cstr_.Trim(); j1=atol(cstr_);
		}
		for(k=0;k<MaxDMCPostCode;k++) if(j1==DMCPostCodeTable[k].PostCode) break;

//    if(k<MaxDMCPostCode) k++;
		j1+=10000; if(j1==DMCPostCodeTable[k+1].PostCode) continue; // is al gemaakt
		MaxDMCPostCode++; 
		for(g=MaxDMCPostCode; g>k;g--) memcpy((char *)&DMCPostCodeTable[g].PostCode,(char *)&DMCPostCodeTable[g-1].PostCode,sizeof DMCPostCodeTable[0]);
		DMCPostCodeTable[k+1].PostCode=j1;
	}
	///

	p_dcm_firma=0;
	inq_lev_=0; inq_fab_=0;
//	if(DM_Settings.DMSelectieLeverancier>30000) inq_fab_=DM_Settings.DMSelectieLeverancier-30000;
//	else inq_lev_=DM_Settings.DMSelectieLeverancier;


	scrnum=0;scrget(1,170);scrifld(10,fm_os63,"Uitschrijven volumes naar XLS ....");scrupd(-3,0);				
	DatBeg=datejd(InqJaar,InqMaand,1);
	jj=InqJaar; mm=InqMaand+1; if(mm>12){mm=1;jj=InqJaar+1;} DatEnd=datejd(jj,mm,1)-1;
//	zero(datestr_,sizeof datestr_);stcli_d(datestr_,(long)InqJaar,4,0);stcli_d(&datestr_[4],(long)InqMaand,2,0);


	scrget(1,170);scrifld(10,fm_os63,"Berekenen basisfiches ....");scrupd(-3,0);
	ReadBasisFiches(); // klanten, postcodes, artikels
	scrget(1,170);scrifld(10,fm_os63,"Berekenen volumes ....");scrupd(-3,0);
	jddate(DatBeg,&JaarBeg,&MaandBeg,&dd);jddate(DatEnd,&JaarEnd,&MaandEnd,&dd);
	act_maand=MaandBeg; act_jaar=JaarBeg;
	dt_beg_=datejd(act_jaar,act_maand,1);RecCnt=0;CntDispPos=0;
	jj=act_jaar; mm=act_maand+1; if(mm>12){mm=1;jj=act_jaar+1;} dt_end_=datejd(jj,mm,1)-1;
	FOREVER{ // per maand uitschrijven 
		q_postcodes_=MaxPostCode;
		for(k=0;k<MaxKlt;k++) {TbKlant[k].Used=0;TbKlant[k].UsedPostCode=0;TbKlant[k].Omzet=0;TbKlant[k].OmzetVaten=0;}
    for(k=0;k<DIM_OMZETARTIKEL+1;k++){
			memset((char *)&OmzetArtikel[k].KlantenPerPostcode[0],0,sizeof OmzetArtikel[0].KlantenPerPostcode);
			memset((char *)&OmzetArtikel[k].OmzetPerPostcode[0],0,sizeof OmzetArtikel[0].OmzetPerPostcode);
		}
		for(k=0;k<MaxKlt;k++) memset((char *)&TbKlant[k].ArtUsed[0],0,sizeof TbKlant[0].ArtUsed);
		for(ix_omz_=0;ix_omz_<MaxOmzetArtikel;ix_omz_++){
			for(k=0;k<MaxKlt;k++) TbKlant[k].Used=0;
			for(n=0;n<MaxArtikel;n++){
				if(TbArtikel[n].DmCode!=OmzetArtikel[ix_omz_].DmCode) continue; // alle artikels met deze DmCode
        if((RecCnt++%100)==0){scrifld(20,fm_os1,&CntDispStr[CntDispPos++]);scrupd(-3,0); if(CntDispPos==4) CntDispPos=0;}				
				fasinit(16);*l(16,20)=TbArtikel[n].RecordNr;*l(16,10)=1;*u(16,3)=dt_beg_;mode16=1;
				FOREVER{
					redo16:;
					if(faskeyi(16,1,mode16)) break; mode16=2;
					if(*l(16,20)!=TbArtikel[n].RecordNr) break;
					if(*u(16,3)<dt_beg_) {*u(16,3)=dt_beg_;mode16=1;goto redo16;}
					if(*u(16,3)>dt_end_) {*u(16,3)=0xFFFF;mode16=1;goto redo16;}
					krec_=*l(16,10);// if(fldlen(16,12) && *l(16,12)) krec_=*l(16,12);
					if(krec_==0 || krec_>=MaxKlt || TbKlant[krec_].RecordNr==0) goto redo16;
					omzet_=*d(16,30); 
					omzet_*=TbArtikel[n].Inhoud; // omzet_=Round(omzet_,0.01);
					OmzetArtikel[ix_omz_].OmzetPerPostcode[TbKlant[krec_].Ix_PostCode]+=omzet_;
					OmzetArtikel[ix_omz_].OmzetPerPostcode[DIM_POSTCODE]+=omzet_;
					OmzetArtikel[DIM_OMZETARTIKEL].OmzetPerPostcode[TbKlant[krec_].Ix_PostCode]+=omzet_; // totaal per postcode
					OmzetArtikel[DIM_OMZETARTIKEL].OmzetPerPostcode[DIM_POSTCODE]+=omzet_;  // totale omzet
					TbKlant[krec_].Omzet+=omzet_;
					TbKlant[krec_].Used=YES;TbKlant[krec_].UsedPostCode=YES;
					j1=ix_omz_/8; j2=ix_omz_%8; TbKlant[krec_].ArtUsed[j1]|=1<<j2;
				}
			}
			for(k=1;k<MaxKlt;k++){ // aantal klanten toevoegen en klanten resetten 
				if(TbKlant[k].Used){
					OmzetArtikel[ix_omz_].KlantenPerPostcode[TbKlant[k].Ix_PostCode]++;
					OmzetArtikel[ix_omz_].KlantenPerPostcode[DIM_POSTCODE]++;
					TbKlant[k].Used=NO;
				}
			}
		}
		for(k=1;k<MaxKlt;k++){ // aantal klanten per postcode samentellen  
			if(TbKlant[k].UsedPostCode){
				OmzetArtikel[DIM_OMZETARTIKEL].KlantenPerPostcode[TbKlant[k].Ix_PostCode]++;
				OmzetArtikel[DIM_OMZETARTIKEL].KlantenPerPostcode[DIM_POSTCODE]++;
			}
		}
		j=0;
		for(k=0;k<q_postcodes_;k++){ // sorttabel invullen en de lege direct overslaan
			if(OmzetArtikel[DIM_OMZETARTIKEL].KlantenPerPostcode[k]) tbpc[j++]=k;
		}
		q_postcodes_=j;

		FOREVER{//  sorteren postcodes
			sw=NO;
			for(k=0;k<q_postcodes_-1;k++){
				j1=atol(TbPostCode[tbpc[k]].postcode); if(j1>9999) j1-=10000;
				j2=atol(TbPostCode[tbpc[k+1]].postcode); if(j2>9999) j2-=10000;
				if(j1>j2 /*TbPostCode[tbpc[k]].postcode>TbPostCode[tbpc[k+1]].postcode*/){
					j=tbpc[k];tbpc[k]=tbpc[k+1];tbpc[k+1]=j;sw=YES;
				}
			}
			if(sw==NO) break;
		}
		scrget(1,170);scrifld(10,fm_os63,"Uitschrijven volumes naar XLS ....");scrupd(-3,0);	
		zero(FileName,sizeof FileName);pos_=0;
		pos_+=copy0("ZipSales-",&FileName[pos_],10);
		j1=InqJaar%100; stcli_d(&FileName[pos_],(long)(j1),2,0);pos_+=2;
		stcli_d(&FileName[pos_],(long)InqMaand,2,0);pos_+=2;
		FileName[pos_++]='-'; 
	  pos_+=copy0(s(25,1),&FileName[pos_],30);
		pos_+=copy0(".XLSX",&FileName[pos_],5); // +++++
		XlsRef=XlsCreate(FileName);
		if(XlsRef<=0) {errnum=1;return false;}

		StylVolume=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,1,0,KLEUR_WIT,1,0,0,NO,NO);
		XlsSelectWorkSheet(XlsRef,1,"VOL");  // sheet VOL
		XlsRij=1;XlsKol=1; 
		XlsKol++;XlsKol++; XlsKol++;// vanaf kol D
		for(k=0;k<q_postcodes_;k++) { // namen gemeente
			nrpc_=atol(TbPostCode[tbpc[k]].postcode);

			for(j=0;j<MaxDMCPostCode;j++) if(nrpc_==DMCPostCodeTable[j].PostCode) break;
			if(j>=MaxDMCPostCode) cstr_="Onbekend";
			else cstr_=DMCPostCodeTable[j].FilPos;
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,(char *)(LPCTSTR)cstr_,0);
		}
		XlsRij++; XlsKol=1;
		zero(str_,sizeof str_);copy0(s(25,1),str_,20);XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"ZIP Code",0);	
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"TOTAL",0);	
		for(k=0;k<q_postcodes_;k++) { // postcodes
			j1=atol(TbPostCode[tbpc[k]].postcode); 
			if(j1>9999)	cstr_="D-"+ TbPostCode[tbpc[k]].postcode.Mid(1);
			else cstr_=TbPostCode[tbpc[k]].postcode;
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,(char *)(LPCTSTR)cstr_,0);
		}
		XlsRij++; XlsKol=1;
		lbd_=act_jaar; XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lbd_,0); // Jaartal

		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC Horeca Count",0);
		lbd_=0; for(k=0;k<q_postcodes_;k++) lbd_+=OmzetArtikel[DIM_OMZETARTIKEL].KlantenPerPostcode[tbpc[k]]; 
		XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lbd_,0);// totaal aantal klanten
		for(k=0;k<q_postcodes_;k++){// aantal klanten per postcode
			lbd_=OmzetArtikel[DIM_OMZETARTIKEL].KlantenPerPostcode[tbpc[k]];
			XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lbd_,0);
		}
		XlsRij++; XlsKol=1;
    lbd_=act_maand; XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lbd_,0); // maandnummer
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC Horeca Total Volume",0);
		omzet_=0; for(k=0;k<q_postcodes_;k++)	omzet_+=OmzetArtikel[DIM_OMZETARTIKEL].OmzetPerPostcode[tbpc[k]];
		omzet_/=hl_factor_;cstr_.Format("%.4f",omzet_);XlsWrite(XlsRef,XlsRij,XlsKol++,0,(char *)(LPCTSTR)cstr_,0); // TOTAALvolume 
		for(k=0;k<q_postcodes_;k++){// volume per postcode
			omzet_=OmzetArtikel[DIM_OMZETARTIKEL].OmzetPerPostcode[tbpc[k]];
			omzet_/=hl_factor_;cstr_.Format("%.4f",omzet_);
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,(char *)(LPCTSTR)cstr_,0);
		}
		XlsRij++; XlsKol=1;
		XlsRij++; // lege lijn 
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PRODUCT",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PRODUCT DESCRIPTION",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"HL",0);
		for(k=0;k<q_postcodes_;k++) XlsWrite(XlsRef,XlsRij,XlsKol++,0,"HL",0);
		XlsRij++; XlsKol=1;
		for(n=0;n<MaxOmzetArtikel;n++){
			if(OmzetArtikel[n].KlantenPerPostcode[DIM_POSTCODE]==0) continue;
			fasinit(6);*u(6,1)=TbArtikel[OmzetArtikel[n].DmCode].RecordNr; fasgeti(6);
			WriteFld2Xls(XlsRij,XlsKol++,6,2,0);
			WriteFld2Xls(XlsRij,XlsKol++,6,3,0);		
			omzet_=0;
			for(k=0;k<q_postcodes_;k++) omzet_+=OmzetArtikel[n].OmzetPerPostcode[tbpc[k]]; 
			omzet_/=hl_factor_;cstr_.Format("%.4f",omzet_);
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,(char *)(LPCTSTR)cstr_,0);
//			XlsWrite(XlsRef,XlsRij,XlsKol++,2,(char *)&omzet_,0);// totaal per artikel
			for(k=0;k<q_postcodes_;k++){
				if(OmzetArtikel[n].OmzetPerPostcode[tbpc[k]]){
					omzet_=OmzetArtikel[n].OmzetPerPostcode[tbpc[k]]/hl_factor_;cstr_.Format("%.4f",omzet_);
			    XlsWrite(XlsRef,XlsRij,XlsKol++,0,(char *)(LPCTSTR)cstr_,0);
//					XlsWrite(XlsRef,XlsRij,XlsKol++,2,(char *)&OmzetArtikel[n].OmzetPerPostcode[tbpc[k]],0);
				}
				else XlsKol++;
			}
			XlsRij++;XlsKol=1;
		}
///// DIS tabel
		scrget(1,170);scrifld(10,fm_os63,"Uitschrijven DIS-tabel naar XLS ....");scrupd(-3,0);	
		XlsSelectWorkSheet(XlsRef,2,"DIS");  // sheet VOL
		XlsRij=1;XlsKol=1; 
		XlsKol++;XlsKol++; XlsKol++;// vanaf kol D
		for(n=0;n<q_postcodes_;n++){// namen gemeente
			for(k=1;k<MaxKlt;k++){
// if(XlsKol>256) break;
				if(TbKlant[k].UsedPostCode==NO) continue;
				if(TbKlant[k].Ix_PostCode==tbpc[n]){
					nrpc_=atol(TbPostCode[tbpc[n]].postcode);
    			for(j=0;j<MaxDMCPostCode;j++) if(nrpc_==DMCPostCodeTable[j].PostCode) break;
		    	if(j>=MaxDMCPostCode) cstr_="Onbekend";
			    else cstr_=DMCPostCodeTable[j].FilPos;
			    XlsWrite(XlsRef,XlsRij,XlsKol++,0,(char *)(LPCTSTR)cstr_,0);
				}
			}
		}
		XlsRij++; XlsKol=1;
		zero(str_,sizeof str_);copy0(s(25,1),str_,20);XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"ZIP Code",0);	
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"TOTAL",0);	

		for(n=0;n<q_postcodes_;n++){// postcodes
			for(k=1;k<MaxKlt;k++){
// if(XlsKol>256) break;
				if(TbKlant[k].UsedPostCode==NO) continue;
				if(TbKlant[k].Ix_PostCode==tbpc[n]){
				  j1=atol(TbPostCode[tbpc[n]].postcode); 
			    if(j1>9999)	cstr_="D-"+ TbPostCode[tbpc[n]].postcode.Mid(1);
					else cstr_=TbPostCode[tbpc[n]].postcode;
					XlsWrite(XlsRef,XlsRij,XlsKol++,0,(char *)(LPCTSTR)cstr_,0);
				}
			}
		}
		XlsRij++; XlsKol=1;
		lbd_=act_jaar; XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lbd_,0); // Jaartal

		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Customer number of POC at wholesaler",0);
		XlsKol++;
		for(n=0;n<q_postcodes_;n++){ // klantenrecordnrs
			for(k=1;k<MaxKlt;k++){
// if(XlsKol>256) break;
				if(TbKlant[k].UsedPostCode==NO) continue;
				if(TbKlant[k].Ix_PostCode==tbpc[n]){
					XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&TbKlant[k].RecordNr,0);
				}
			}
		}

		XlsRij++; XlsKol=1;
    lbd_=act_maand; XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lbd_,0); // maandnummer
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Total number of SKUs in POC",0);
		lbd_=0;tot_sku_=0;
		XlsKol++; // totaal voorlopig overslaan 

		for(n=0;n<q_postcodes_;n++){
			for(j=1;j<MaxKlt;j++){
// if(XlsKol>256) break;
				if(TbKlant[j].UsedPostCode==NO) continue;
				if(TbKlant[j].Ix_PostCode==tbpc[n]){
					lijn_tot_=0;
					for(k=0;k<MaxOmzetArtikel;k++) if(TbKlant[j].ArtUsed[k/8]&(1<<(k%8))) lijn_tot_++;
					XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lijn_tot_,0);

					tot_sku_+=lijn_tot_;
				}
			}
		}
	  XlsWrite(XlsRef,XlsRij,3,1,(char *)&tot_sku_,0); // totaal
		XlsRij++; XlsKol=1;
		XlsRij++; // lege lijn 
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PRODUCT",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PRODUCT DESCRIPTION",0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"OK",0);
		for(n=0;n<q_postcodes_;n++){ // klantenrecordnrs
			for(k=1;k<MaxKlt;k++){
// if(XlsKol>256) break;
				if(TbKlant[k].UsedPostCode==NO) continue;
				if(TbKlant[k].Ix_PostCode==tbpc[n]) XlsWrite(XlsRef,XlsRij,XlsKol++,0,"OK",0);

			}
		}
		XlsRij++; XlsKol=1;
		for(k=0;k<MaxOmzetArtikel;k++){
			if(OmzetArtikel[k].KlantenPerPostcode[DIM_POSTCODE]==0) continue;
			fasinit(6);*u(6,1)=TbArtikel[OmzetArtikel[k].DmCode].RecordNr; fasgeti(6);
			WriteFld2Xls(XlsRij,XlsKol++,6,2,0);
			WriteFld2Xls(XlsRij,XlsKol++,6,3,0);			
			XlsKol++; // tijdelijk overslaan voor totaal
			lijn_tot_=0;
			for(n=0;n<q_postcodes_;n++){
				for(j=1;j<MaxKlt;j++){
// if(XlsKol>256) break;
					if(TbKlant[j].UsedPostCode==NO) continue;
					if(TbKlant[j].Ix_PostCode==tbpc[n]){
						if(TbKlant[j].ArtUsed[k/8]&(1<<(k%8))) {XlsWrite(XlsRef,XlsRij,XlsKol++,0,"1",0);lijn_tot_++;}
						else XlsKol++;

					}
				}

//				if(OmzetArtikel[n].OmzetPerPostcode[tbpc[k]]) XlsWrite(XlsRef,XlsRij,XlsKol++,2,(char *)&OmzetArtikel[n].OmzetPerPostcode[tbpc[k]],0);
//				else XlsKol++;
			}
			XlsWrite(XlsRef,XlsRij,3,1,(char *)&lijn_tot_,0); // lijntotaal
			XlsRij++;XlsKol=1;
		}



//////////////////
		//if(DM_Settings.ExportKlanten!='J') goto end_xls_out;
		//cstr_=CString(DM_Settings.StrSpecKlantKol,15);
		//j1=0;j2=0; for(k=0;k<5;k++) spec_kol_[k]=0;
		//for(k=0;k<5;k++){
		//	j2=cstr_.Find(',',j1);
		//	if(j2<0){
		//		if(j1<cstr_.GetLength()) spec_kol_[k]=String2Getal(cstr_.Mid(j1),',');
		//		if(spec_kol_[k] && fldlen(2,spec_kol_[k])==0) spec_kol_[k]=0;
		//		break;
		//	}
		//	spec_kol_[k]=String2Getal(cstr_.Mid(j1,j2-j1),','); j1=j2+1;
		//	if(spec_kol_[k]<1 || fldlen(2,spec_kol_[k])==0) k--;
		//}
		//XlsSelectWorkSheet(XlsRef,3,"POC"); // sheet 2 POC
		//scrget(1,170);scrifld(10,fm_os63,"Uitschrijven POC's naar XLS ....");scrupd(-3,0);		

		//XlsRij=1;XlsKol=1;

	 // XlsWrite(XlsRef,XlsRij,XlsKol++,0,"YEAR",0);	lbd_=act_jaar; XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lbd_,0);
		//XlsRij++; XlsKol=1;
  //  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"MONTH",0);	lbd_=act_maand; XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&lbd_,0);
		//XlsRij++; XlsKol=1;
		//XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC Count",0);
		//XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&OmzetArtikel[DIM_OMZETARTIKEL].KlantenPerPostcode[DIM_POSTCODE],0);
		//XlsRij++;XlsRij++;XlsKol=1;
		//XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC ID",0);
		//XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC ZIP",0);
		//XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC Name",0);
		//XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC Street",0);
		//XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC City",0);
	 // XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC Vat",0);
	 // XlsWrite(XlsRef,XlsRij,XlsKol++,0,"POC Tel",0); 
		//for(k=0;k<5;k++){
		//	if(spec_kol_[k]==0) break;
		//	zero(str_,sizeof str_);
		//	sprintf(str_,"%d:%s",spec_kol_[k],s(2,-spec_kol_[k])); XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
		//}
		//XlsRij++;XlsKol=1;
		//for(n=0;n<q_postcodes_;n++){
		//	for(k=1;k<MaxKlt;k++){
		//		if(TbKlant[k].UsedPostCode==NO) continue;
		//		if(TbKlant[k].Ix_PostCode==tbpc[n]){
		//			XlsWrite(XlsRef,XlsRij,XlsKol++,1,(char *)&TbKlant[k].RecordNr,0);
		//			XlsWrite(XlsRef,XlsRij,XlsKol++,0,(char *)(LPCTSTR)TbPostCode[tbpc[n]].postcode,0);
		//			if(DM_Settings.ExportKlanten=='J'){
		//				fasinit(2);*u(2,1)=TbKlant[k].RecordNr; fasgeti(2);
		//				if(fldlen(2,51) && *u(2,51) && (*s(2,5)=='\0' || *l(2,10)==0)) FillAdresFromFtKlant();
		//				*(s(2,3)+fldlen(2,3)-1)=0;XlsWrite(XlsRef,XlsRij,XlsKol++,0,s(2,3),0);
		//				*(s(2,4)+fldlen(2,4)-1)=0;XlsWrite(XlsRef,XlsRij,XlsKol++,0,s(2,4),0);
		//				*(s(2,6)+fldlen(2,6)-1)=0;XlsWrite(XlsRef,XlsRij,XlsKol++,0,s(2,6),0);
		//	    	WriteFld2Xls(XlsRij,XlsKol++,2,10,0); // CusVAT
		//      	if(*s(2,8)) WriteFld2Xls(XlsRij,XlsKol++,2,8,0); else WriteFld2Xls(XlsRij,XlsKol++,2,20,0);  // CusTel
		//				for(j=0;j<5;j++){
		//					if(spec_kol_[j]==0) break;
		//					WriteFld2Xls(XlsRij,XlsKol++,2,spec_kol_[j],0); // speciale kollommen
		//				}
		//			}
		//			XlsRij++;XlsKol=1;
		//		}
		//	}
		//}
end_xls_out:;
		if(MailDirect){
  		SpoolFileNr=XlsClose(XlsRef,2);
			
			MailDocument(0,0);
		}
		else XlsClose(XlsRef,1);
		break; //  maar 1 maand
	}

	return true;	
}

static void ReadBasisFiches(void)
{

	CString ptekst_;
	int n,k,g,sw,nrcode_,dklant_;
	uint16 inq_lev_,inq_fab_;
	char str_[20],kar_;  
  CString cstr_;
	long dmcode_;

	inq_lev_=0;inq_fab_=0;
	if(DM_Settings.DMSelectieLeverancier>30000) inq_fab_=DM_Settings.DMSelectieLeverancier-30000;
	else inq_lev_=DM_Settings.DMSelectieLeverancier;


  scrnum=0;scrget(1,7);
  scraddfield(1,10,18,0);scraddfield(20,78,21,0);
  scrifld(1,fm_os63,"Reading customers and products ...");
  scrupd(-3,0);
  MaxKlt=1;
	fasinit(2);n=0;MaxPostCode=0;RecCnt=0;CntDispPos=0;
	FOREVER{
		*u(2,1)=++n;
		g=fasgeti(2);
		if(g==47) break;
		if(g!=46){  // niet gedelete record 
			if((RecCnt++%100)==0){scrifld(20,fm_os1,&CntDispStr[CntDispPos++]);scrupd(-3,0); if(CntDispPos==4) CntDispPos=0;}
//			if(fldlen(2,131) && *s(2,131)=='J') goto next_klt; // geblokkeerd

			dklant_=NO;
			for(k=0;k<10;k++) if(n==loc_klt[k]) break;
			if(k<10){ // kassaklant 
				if(DM_Settings.ExportKassaVerkopen!='J') goto next_klt; // kassaverkopen
				dklant_=YES;
				if(*s(2,5)=='\0') sysget(91,4,s(2,5)); // indien niet ingevuld dan postcode van firma nemen 
			}
			if(dklant_==NO){ // bij niet kassaklanten checken op selecties
				if(*s(2,26)=='\0') *s(2,26)='0';
				for(k=0;k<5;k++) if(*s(2,26)==DM_Settings.SelectPrijsType[k]) break; // controle op prijstype
				if(k>=5) goto next_klt;
				for(k=0;k<5;k++) if(DM_Settings.SelectSoortKlant[k]) break; // controle op soort klant
				if(k<5){ // er moet gechecked worden
					for(k=0;k<5;k++) if(DM_Settings.SelectSoortKlant[k] && *s(2,54)==DM_Settings.SelectSoortKlant[k]) break;
					if(k>=5) goto next_klt;
				}
			}
			TbKlant[MaxKlt].RecordNr=n;
			g=0;zero(str_,sizeof str_);
			for(k=0;k<fldlen(2,5);k++){ // enkel cijfers eruit halen
				kar_=*(s(2,5)+k);
				if(kar_=='\0') break;
				if(kar_>='0' && kar_<='9') str_[g++]=kar_;
				if(g>=4) break;
			}
			if(g<4){ // kijken op factuurklant
				if(fldlen(2,51) && *u(2,51)){
					*u(2,1)=*u(2,51);fasgeti(2);
					g=0;zero(str_,sizeof str_);
					for(k=0;k<fldlen(2,5);k++){ // enkel cijfers eruit halen
						kar_=*(s(2,5)+k);
						if(kar_=='\0') break;
						if(kar_>='0' && kar_<='9') str_[g++]=kar_;
						if(g>=4) break;
					}
					if(g<4) copy("0000",s(2,5),4); // ongeldig 
				}
				else copy("0000",s(2,5),4); // ongeldig 
			}
			cstr_=arr2cstr(str_,4);cstr_.Trim();
			nrcode_=atol(cstr_);if(dklant_) nrcode_+=10000;
			for(k=0;k<MaxDMCPostCode;k++) if(nrcode_==DMCPostCodeTable[k].PostCode) break;
			if(k>=MaxDMCPostCode){ // enkel de steden
				str_[3]='0';
				cstr_=arr2cstr(str_,4);cstr_.Trim();
			}
			if(dklant_) cstr_="1" + cstr_;
			for(k=0;k<MaxPostCode;k++){
				if(TbPostCode[k].postcode.CompareNoCase(cstr_)==0) break;
			}
			if(k<DIM_POSTCODE){
				TbPostCode[k].postcode=cstr_;if(k==MaxPostCode) MaxPostCode=k+1;
				TbKlant[MaxKlt].Ix_PostCode=k;
			}
		}
next_klt:;
		MaxKlt++; if(MaxKlt>=DIM_KLANT) break;
	}

  scrifld(1,fm_os63,"Reading products ...");  scrupd(-3,0);
	MaxOmzetArtikel=0; MaxArtikel=0; fasinit(6);n=0;RecCnt=0;CntDispPos=0;
	FOREVER{
		next_art:;
		if(faskeyi(6,2,2)) break;
//		if(inq_lev_ && *u(6,7)!=inq_lev_) goto next_art;
//		if(inq_fab_ && *u(6,101)!=inq_fab_) goto next_art;
		if(*u(6,9)==99) goto next_art;
    if((RecCnt++%25)==0){scrifld(20,fm_os1,&CntDispStr[CntDispPos++]);scrupd(-3,0); if(CntDispPos==4) CntDispPos=0;}
    if(ArtUsedInHis(*u(6,1),DatBeg,DatEnd)==NO) goto next_art;
		TbArtikel[MaxArtikel].RecordNr=*u(6,1);
    TbArtikel[MaxArtikel].DmCode=MaxArtikel;
		//TbArtikel[MaxArtikel].DmCode=*l(6,140);
  	TbArtikel[MaxArtikel].Inhoud=*f(6,37);
		for(k=0;k<MaxOmzetArtikel;k++) if(TbArtikel[MaxArtikel].DmCode==OmzetArtikel[k].DmCode) break;
		OmzetArtikel[k].DmCode=TbArtikel[MaxArtikel].DmCode;
		MaxArtikel++; if(MaxArtikel>=DIM_ARTIKEL) break;
		if(k>=MaxOmzetArtikel){ MaxOmzetArtikel++; if(MaxOmzetArtikel>=DIM_OMZETARTIKEL) break;}
	}
	FOREVER{//  sorteren op DmCode
		sw=NO;
		for(k=0;k<MaxOmzetArtikel-1;k++){
			if(OmzetArtikel[k].DmCode>OmzetArtikel[k+1].DmCode){
				dmcode_=OmzetArtikel[k].DmCode; 
				OmzetArtikel[k].DmCode=OmzetArtikel[k+1].DmCode;OmzetArtikel[k+1].DmCode=dmcode_;
				sw=YES;
			}
		}
		if(sw==NO) break;
	}
}


static int ArtUsedInHis(uint16 arec_, uint16 dt_beg_,uint16 dt_end_)
{
	fasinit(16);*l(16,20)=arec_;
	FOREVER{
		if(faskeyi(16,1,2)) return NO;
		if(*l(16,20) !=arec_) return NO;
		if(*u(16,3)>=dt_beg_ && *u(16,3)<=dt_end_) return YES;
	}
	return YES;
}


static bool DetailedXlsFromHisData(void) // ColDa export
{
	int j,k,curs=1,pos_,j1,j2,spec_kol_[5];
	short int jj,mm,dd,blk_pos_;
	//int dt_beg_,dt_end_;
	uint16 inq_lev_,inq_fab_;
	long cnt_,blk_cnt_;
	char datestr_[50],naam_[50],disp_str[100];
	CString cstr_,dossier_,artnaam_,supnaam_;

  char ft_file_[100],str_[30];
	long count_=0;
	CString ft_filestring,ft_dir;
	SYSTEMTIME st_;
  WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile	  


	// !!! worden gedelete in hoofdroutine OvlCod!!!
	if(!TbKlant) TbKlant= new _TbKlant[DIM_KLANT];
	if(!TbKlant) return false;
	memset(TbKlant,0,DIM_KLANT * sizeof TbKlant[0]);
	inq_lev_=0;inq_fab_=0;
	if(DM_Settings.DMSelectieLeverancier>30000) inq_fab_=DM_Settings.DMSelectieLeverancier-30000;
	else inq_lev_=DM_Settings.DMSelectieLeverancier;


	scrnum=0;scrget(1,170);scrifld(10,fm_os63,"Uitschrijven volumes naar XLS ....");scrupd(-3,0);				
	DatBeg=datejd(InqJaar,InqMaand,1);
	jj=InqJaar; mm=InqMaand+1; if(mm>12){mm=1;jj=InqJaar+1;} DatEnd=datejd(jj,mm,1)-1;
	zero(datestr_,sizeof datestr_);stcli_d(datestr_,(long)InqJaar,4,0);stcli_d(&datestr_[4],(long)InqMaand,2,0);


	zero(FileName,sizeof FileName);pos_=0;
	pos_+=copy0("ColDa-",&FileName[pos_],10);
	j1=InqJaar%100; stcli_d(&FileName[pos_],(long)(j1),2,0);pos_+=2;
	stcli_d(&FileName[pos_],(long)InqMaand,2,0);pos_+=2;
	FileName[pos_++]='-'; 
	pos_+=copy0(s(25,1),&FileName[pos_],30);
	pos_+=copy0(".XLSX",&FileName[pos_],5);
	XlsRef=XlsCreate(FileName);
	if(XlsRef<=0) {errnum=1;return false;}

	XlsSelectWorkSheet(XlsRef,1,"VOL");  // sheet VOL
	XlsRij=1;XlsKol=1; 
  XlsWrite(XlsRef,1,XlsKol++,0,"Date",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"Product",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"Volume",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"CusRef",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"CusZip",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"InvRef",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"EANBAK",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"EANFLES",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"Aantal/Bak",0);

	blk_cnt_=0;if(fldlen(16,1)){fasinfo(16,6);blk_cnt_=*l(16,1)/79;} if(blk_cnt_==0) blk_cnt_=1; 
	cnt_=0;blk_pos_=0;zero(disp_str,sizeof disp_str);
	XlsRij=2;XlsKol=1; 
	if(ViaHistoriek){
		fasinit(16);
		FOREVER{
			next16:;
			if(faskeyi(16,3,2)) break;
			cnt_++; 
			if((cnt_%blk_cnt_)==0){
				disp_str[blk_pos_++]='*';scrifld(22,fm_titel,&disp_str);scrupd(-3,0);
				if(blk_pos_>=80){blk_pos_=0;zero(disp_str,sizeof disp_str);}
			}
			if(*u(16,3)<DatBeg || *u(16,3)>DatEnd) goto next16;
			if(*l(16,23)==99) goto next16;  // geen leeggoed
			fasinit(2);if(fldlen(16,12)) *u(2,1)=*l(16,12); // eerst via lever-klant proberen
			if(*u(2,1)==0 || fasgeti(2)){
				fasinit(2);*u(2,1)=*l(16,10);
				if(*u(2,1)==0 || fasgeti(2)) goto next16; // slechte klant
			}
			if(DM_Settings.ExportBlockedKlanten!='J' && fldlen(2,131) && *s(2,131)=='J') goto next16; // geblokkeerd
			for(k=0;k<10;k++) if(*l(16,20)==TbDiversArtikel[k]) break;
			if(k<10) goto next16; // geen diversen
			fasinit(6);*u(6,1)=*l(16,20); if(fasgeti(6)) goto next16; // slecht artikel
			if(inq_lev_ && *u(6,7)!=inq_lev_) goto next16;
			if(inq_fab_ && *u(6,101)!=inq_fab_) goto next16;
		
			if(*f(6,37)) *d(16,30)*=*f(6,37); // inhoud
	//		else if(*f(6,38)) *d(16,30)*=*f(6,38); // gewicht
			else goto next16; // geen volume artikel
			if(fldlen(2,51) && *u(2,51) && (*s(2,5)=='\0' || *l(2,10)==0)) FillAdresFromFtKlant();
			XlsKol=1;
			jddate(*u(16,3),&jj,&mm,&dd);stcli_d(&datestr_[6],(long)dd,2,0);
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,datestr_,0); // datum
			WriteFld2Xls(XlsRij,XlsKol++,16,22,0); // originele omschrijving 
			WriteVar2Xls(XlsRij,XlsKol++,fm_ud6_2,(char *)d(16,30),0); // volume 
			WriteFld2Xls(XlsRij,XlsKol++,2,1,0); // cusref
			WriteFld2Xls(XlsRij,XlsKol++,2,5,0); // cuszip
			WriteFld2Xls(XlsRij,XlsKol++,16,2,0); // cuszip
			WriteFld2Xls(XlsRij,XlsKol++,6,70,0); // EANbak
			WriteFld2Xls(XlsRij,XlsKol++,6,71,0); // EANfles
			WriteFld2Xls(XlsRij,XlsKol++,6,31,0); // aantal/bak
			TbKlant[*u(2,1)].Used=YES;
			XlsRij++;
		}
	}
	else{
		zeros((char *)&st_,sizeof st_);
		SystemTimeToFileTime(&st_,&FtFtimeBeg);SystemTimeToFileTime(&st_,&FtFtimeEnd);
    
		k=0; if(DatBeg>10) k=10; // filedatum 10 dagen ervoor nemen voor geval men facturen in de toekomst heeft gemaakt
		jddate((int)(DatBeg-k),&jj,&mm,&dd);
		st_.wDay=dd;st_.wMonth=mm;st_.wYear=jj;SystemTimeToFileTime(&st_,&FtFtimeBeg);
		jddate((int)DatEnd,&jj,&mm,&dd);
		st_.wDay=dd;st_.wMonth=mm;st_.wYear=jj;SystemTimeToFileTime(&st_,&FtFtimeEnd);
		ft_dir=CString("");
		zero(str_,sizeof str_);sysget(4704,25,str_);ft_dir+=CString(str_);
		ft_filestring=ft_dir;
		zero(str_,sizeof str_);copy(s(25,3),str_,3);ft_filestring+=CString(str_);ft_filestring+="*.*";
//		ft_filestring+=WHS_Settings.JamaDossierCode[NrInternalCompany];

		hSearch = FindFirstFile (ft_filestring, &FileData);
		FOREVER{
			if (hSearch == INVALID_HANDLE_VALUE) break;
			if ((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) goto nextfile;                      // geen directory 
			if (CompareFileTime(&FileData.ftLastWriteTime,&FtFtimeBeg)<0) {FtSkipped++;goto nextfile;} // voor de gewenste periode 
	/*    if (CompareFileTime(&FileData.ftLastWriteTime,&FtFtimeEnd)>0) {FtSkipped++;goto nextfile;} // na de gewenste periode  */

			cstr_=ft_dir;cstr_+=CString(FileData.cFileName);
  		zeros(ft_file_,sizeof ft_file_); copy((char *)(LPCTSTR)cstr_,ft_file_,cstr_.GetLength());
			if(AddFactuur2Xls(ft_file_,inq_lev_,inq_fab_)==false) FtSkipped++; else FtGood++;
  
	nextfile:;
			if((count_%500)==0) {scrifld(18,fm_ol8,&count_);scrupd(-3,0);}
			if(FindNextFile (hSearch, &FileData)==false) break;
			count_++;
		}
		FindClose(hSearch);
	}
// ALTIJD UITSCHRIJVEN   if(DM_Settings.ExportKlanten!='J') goto end_xls_out;
	cstr_=CString(DM_Settings.StrSpecKlantKol,15);
	j1=0;j2=0; for(k=0;k<5;k++) spec_kol_[k]=0;
	for(k=0;k<5;k++){
		j2=cstr_.Find(',',j1);
		if(j2<0){
			if(j1<cstr_.GetLength()) spec_kol_[k]=String2Getal(cstr_.Mid(j1),',');
			if(spec_kol_[k] && fldlen(2,spec_kol_[k])==0) spec_kol_[k]=0;
			break;
		}
		spec_kol_[k]=String2Getal(cstr_.Mid(j1,j2-j1),','); j1=j2+1;
		if(spec_kol_[k]<1 || fldlen(2,spec_kol_[k])==0) k--;
	}
	XlsSelectWorkSheet(XlsRef,2,"POC"); // sheet 2 POC
	scrnum=0;scrget(1,170);scrifld(10,fm_os63,"Uitschrijven POC's naar XLS ....");scrupd(-3,0);		
	XlsRij=1;XlsKol=1; 
  XlsWrite(XlsRef,1,XlsKol++,0,"CusRef",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"CusPoc",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"CusName",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"CusStreet",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"CusZip",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"CusCity",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"CusVat",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"CusTel",0);
	XlsWrite(XlsRef,1,XlsKol++,0,"BLOCK",0);
	for(j=0;j<5;j++){
		if(spec_kol_[j]==0) break;
		zero(str_,sizeof str_);
		sprintf(str_,"%d:%s",spec_kol_[j],s(2,-spec_kol_[j])); XlsWrite(XlsRef,1,XlsKol++,0,str_,0);
	}


	XlsRij=2;
	cnt_=0;
	for(k=1;k<DIM_KLANT;k++){
		if(TbKlant[k].Used){
		  cnt_++; if((cnt_%100)==0){ scrifld(12,fm_ol8,&cnt_);scrupd(-3,0);}
			XlsKol=1;
			fasinit(2);*u(2,1)=k;fasgeti(2);
			if(fldlen(2,51) && *u(2,51) && (*s(2,5)=='\0' || *l(2,10)==0)) FillAdresFromFtKlant();
			zero(naam_,sizeof naam_);MakeDeHeer(2,naam_);
		  WriteFld2Xls(XlsRij,XlsKol++,2,1,0); // CusRef
			WriteVar2Xls(XlsRij,XlsKol++,fm_os50,naam_,0); // CusPoc
			WriteVar2Xls(XlsRij,XlsKol++,fm_os50,naam_,0); // CusName
			WriteFld2Xls(XlsRij,XlsKol++,2,4,0); // CusStreet
			WriteFld2Xls(XlsRij,XlsKol++,2,5,0); // CusZip
			WriteFld2Xls(XlsRij,XlsKol++,2,6,0); // CusCity
			WriteFld2Xls(XlsRij,XlsKol++,2,10,0); // CusVAT
			if(*s(2,8)) WriteFld2Xls(XlsRij,XlsKol++,2,8,0); else WriteFld2Xls(XlsRij,XlsKol++,2,20,0);  // CusTel
			if(*s(2,131)=='J') XlsWrite(XlsRef,XlsRij,XlsKol++,0,"1",0); else  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"0",0); // geblokkeerd
			for(j=0;j<5;j++){
				if(spec_kol_[j]==0) break;
				WriteFld2Xls(XlsRij,XlsKol++,2,spec_kol_[j],0); // speciale kollommen
			}

			XlsRij++;
		}
	}
	scrget(1,7);scrupd(-3,0);
end_xls_out:;
	if(MailDirect){
  	SpoolFileNr=XlsClose(XlsRef,2);
	  MailDocument(0,1);
	}
	else XlsClose(XlsRef,1);
	return true;	
}

static void FillAdresFromFtKlant(void) // adres en btwnr aanvullen van factuurklant
{
	int16 k;
	uint16 rec_;

	rec_=*u(2,1);
	  
	copy(s(2,1),buf1000,fldlen(2,0));
	*u(2,1)=*u(2,51);
	if(fasgeti(2)){*u(2,1)=rec_;fasgeti(2);}
	else{		
		copy(s(2,1),buf1000,fldlen(2,0));
		*u(2,1)=rec_;fasgeti(2);
    for(k=4;k<10;k++){
      if(*s(2,k)=='\0') copy(&buf1000[s(2,k)-s(2,1)],s(2,k),fldlen(2,k));
		}
		if(*l(2,10)==0) copy(&buf1000[s(2,k)-s(2,1)],s(2,k),fldlen(2,k));
	}
}



static bool AddFactuur2Xls(char *pfname_,uint16 inq_lev_,uint16 inq_fab_)
{
 	int len_,len1_,pos_;
	bool retval_=false;
	uint16 krec_;
  int j,k;
	short int jj,mm,dd;
	char buf_[1000], datestr_[50];
	UINT fpos_;
	double omzet_;
  CFile FtFile_;

	if (!FtFile_.Open(pfname_,CFile::modeRead,NULL,NULL)) return false; // file not found !
	FtFile_.Seek(0L,CFile::begin);
 
  zeros((char *)&ft_stu.ft_nr,sizeof ft_stu);fpos_=0;
	if (FtFile_.Read(&ft_stu.ft_nr,sizeof(ft_stu))!=sizeof(ft_stu)) goto endsr; // file not OK !
	fpos_+=sizeof(ft_stu);
	if(DatBeg && ft_stu.ft_date<DatBeg) goto endsr; // factuurdatum moet ook binnen de periode zitten 
	if(DatEnd && ft_stu.ft_date>DatEnd) goto endsr; // factuurdatum moet ook binnen de periode zitten 
  
	fasinit(8);FtFile_.Seek(fpos_,CFile::begin);
  len_=FtFile_.Read(buf_,ft_stu.stu8len);fpos_+=len_;
  if(len_<ft_stu.stu8len) goto endsr;
  pos_=0;
  for(k=0;k<200;k++){
    len_=fldlen(8,k+1);
    len1_=ft_stu.stu8[k][0];
    if(len_){
      if(len1_){
		  	if(len1_<len_) len_=len1_;
	      bcopy(&buf_[pos_],s(8,k+1),len_); pos_+=len1_;
      }
    } else pos_+=len1_;
  }

	*us(8,2)=ft_stu.ft_nr;*us(8,8)=ft_stu.ft_date;krec_=*us(8,3);
	fasinit(2);
	bcopy(s(8,14),s(2,3),fldlen(8,14));
	bcopy(s(8,15),s(2,4),fldlen(8,15));
	if(faskeyi(2,2,0)==0) krec_=*us(2,1); // recordnummer van leveradres zetten 
	else{
    *us(2,1)=*us(8,3); if(fasgeti(2)) krec_=0; else krec_=*us(2,1);
	}

	if(DM_Settings.ExportBlockedKlanten!='J' && fldlen(2,131) && *s(2,131)=='J'){FtFile_.Close();return false;} // geblokkeerd
  zero(datestr_,sizeof datestr_);stcli_d(datestr_,(long)InqJaar,4,0);stcli_d(&datestr_[4],(long)InqMaand,2,0);
  for(j=0;j<1000;j++){
    fasinit(58);FtFile_.Seek(fpos_,CFile::begin);
		len_=FtFile_.Read(buf_,ft_stu.stu58len);fpos_+=len_;
		if(len_<ft_stu.stu58len) break;
    pos_=0;
    for(k=0;k<200;k++){
      len_=fldlen(58,k+1);
      len1_=ft_stu.stu58[k][0];
      if(len_){
      	if(len1_){
	        if(len1_<len_) len_=len1_;
	        bcopy(&buf_[pos_],s(58,k+1),len_); pos_+=len1_;
				}
      } else pos_+=len1_;
    }

		if(*us(58,14)==0) continue;
		if(*us(58,34)==99) continue; // geen leeggoed 
		for(k=0;k<10;k++) if(*u(58,14)==TbDiversArtikel[k]) break;
		if(k<10) continue; // geen diversen
		fasinit(6);*u(6,1)=*u(58,14); if(fasgeti(6)) continue; // slecht artikel
		if(inq_lev_ && *u(6,7)!=inq_lev_) continue;
		if(inq_fab_ && *u(6,101)!=inq_fab_) continue;
		omzet_=*f(58,31);	if(fldlen(58,62) && *s(58,62)=='S' && fldlen(58,63) && *f(58,63)>0) omzet_/=*f(58,63); // flessen		
		if(*f(6,37)) omzet_*=*f(6,37); // inhoud
	//		else if(*f(6,38)) omzet_*=*f(6,38); // gewicht
		else continue; // geen volume artikel
		XlsKol=1;
		jddate(*u(8,8),&jj,&mm,&dd);stcli_d(&datestr_[6],(long)dd,2,0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,datestr_,0); // datum
		WriteFld2Xls(XlsRij,XlsKol++,58,16,0); // originele omschrijving 
		WriteVar2Xls(XlsRij,XlsKol++,fm_ud6_2,(char *)(&omzet_),0); // volume 
		WriteFld2Xls(XlsRij,XlsKol++,2,1,0); // cusref
		WriteFld2Xls(XlsRij,XlsKol++,2,5,0); // cuszip
		WriteFld2Xls(XlsRij,XlsKol++,8,2,0); // cuszip
		TbKlant[*u(2,1)].Used=YES;
		XlsRij++;
	}
	retval_=true;
endsr:;
	FtFile_.Close();
  return retval_;
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
  int z,key;
  char choice='\0';

  FOREVER{
		redo:;
    scrnum=0;scrget(3,7);z=1;fasunlck(0);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(1,0x81);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) goto endsr;
    switch(choice){
      case '1': UpdateDMSettings(); break;
      case '2': UpdateColdaSettings(); break;
      default : errnum=34; break;
    }
  }
endsr:;
	sysget(3049,60,(char *)DM_Settings.EmailAdres);
	sysget(3109,2,(char *)&DM_Settings.DMSelectieLeverancier);
	sysget(3112,15,(char *)DM_Settings.StrSpecKlantKol);
	sysget(3127,5,(char *)DM_Settings.SelectPrijsType);
	sysget(3132,5,(char *)DM_Settings.SelectSoortKlant);
	sysget(3139,1,(char *)&DM_Settings.ExportKassaVerkopen);
	sysget(3140,1,(char *)&DM_Settings.ExportBlockedKlanten);
	sysget(3141,1,(char *)&DM_Settings.DefaultBlockNewKlanten);
	
}

static void UpdateDMSettings(void)
{
  int curs,z,key,k;

	sysget(3127,5,(char *)DM_Settings.SelectPrijsType);
	sysget(3132,5,(char *)DM_Settings.SelectSoortKlant);
	sysget(3139,1,(char *)&DM_Settings.ExportKassaVerkopen);

	curs=1;
  FOREVER {
		redo:; 
    scrnum=0;scrget(3,8);z=1;
//		scraddpicto(1,0,1,22,4,2,595,0,0,"annuleer"); scraddpicto(2,0,7,22,4,2,578,0,0,"OK"); 
		scrifld(z++,fm_uJN,&DM_Settings.ExportKassaVerkopen);
		for(k=0;k<5;k++) scrifld(z++,fm_u_05,&DM_Settings.SelectPrijsType[k]);
		for(k=0;k<5;k++) scrifld(z++,fm_us1_U,&DM_Settings.SelectSoortKlant[k]);
    key=scrupd(curs,0xA0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106 || key==5001) goto endsr;
	  if(key==108 || key==5002) break;
  }
	sysput(3127,5,(char *)DM_Settings.SelectPrijsType);
	sysput(3132,5,(char *)DM_Settings.SelectSoortKlant);
	sysput(3139,1,(char *)&DM_Settings.ExportKassaVerkopen);
endsr:;
}

static void UpdateColdaSettings(void)
{
  int curs,z,key,k,j1,j2;
  char lev_prod_;
	CString cstr_;

	sysget(3049,60,(char *)DM_Settings.EmailAdres);
	sysget(3109,2,(char *)&DM_Settings.DMSelectieLeverancier);
	sysget(3112,15,(char *)DM_Settings.StrSpecKlantKol);
	sysget(3140,1,(char *)&DM_Settings.ExportBlockedKlanten);
	sysget(3141,1,(char *)&DM_Settings.DefaultBlockNewKlanten);

	fasinit(1);
	lev_prod_='L'; *u(1,1)=DM_Settings.DMSelectieLeverancier;
	if(*u(1,1)>30000){lev_prod_='P';*u(1,1)=*u(1,1)-30000;}
	if(*u(1,1)) fasgeti(1);

	curs=1;
  FOREVER {
		redo:; 
    scrnum=0;scrget(3,4);z=1;
//		scraddpicto(1,0,1,22,4,2,595,0,0,"annuleer"); scraddpicto(2,0,7,22,4,2,578,0,0,"OK"); scraddpicto(7,0,13,22,4,2,107,0,4,"Herdisplay"); 
		scrifld(z++,fm_us60,DM_Settings.EmailAdres);
		scrifld(z++,fm_uLP,&lev_prod_);
		scrfld(z++,1,3);
		scrifld(z++,VarTextFmt(15,1),DM_Settings.StrSpecKlantKol);
		scrifld(z++,fm_uJN,&DM_Settings.DefaultBlockNewKlanten);
		scrifld(z++,fm_uJN,&DM_Settings.ExportBlockedKlanten);
    key=scrupd(curs,0x2E1);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101 || key==106 || key==5001) goto endsr;
		if(key==110 && fldlen(2,131)) BlokkeerKlant();
		if(CheckEmailAdres(DM_Settings.EmailAdres,60,0)==NO){errnum=34;curs=1; goto redo;}
		if(*s(1,3)){
			if(Search(1,0)){curs=3; goto redo;};
		} else fasinit(1);
    if(key==108 || key==5002) break;
  }
	sysput(3049,60,(char *)DM_Settings.EmailAdres);
	if(lev_prod_=='P' && *u(1,1)) *u(1,1)+=30000;
	DM_Settings.DMSelectieLeverancier=*u(1,1);
	sysput(3109,2,(char *)&DM_Settings.DMSelectieLeverancier);
	sysput(3112,15,(char *)DM_Settings.StrSpecKlantKol);
	sysput(3140,1,(char *)&DM_Settings.ExportBlockedKlanten);
	sysput(3141,1,(char *)&DM_Settings.DefaultBlockNewKlanten);
	cstr_=CString(DM_Settings.StrSpecKlantKol,15);
	j1=0;j2=0; for(k=0;k<5;k++) DM_Settings.SpecKlantKol[k]=0;
	for(k=0;k<5;k++){
		j2=cstr_.Find(',',j1);
		if(j2<0){
			if(j1<cstr_.GetLength()) DM_Settings.SpecKlantKol[k]=String2Getal(cstr_.Mid(j1+1),',');
			break;
		}
		DM_Settings.SpecKlantKol[k]=String2Getal(cstr_.Mid(j1+1,j2-j1-1),','); j1=j2;
	}
endsr:;
}


static void BlokkeerKlant(void)
{
	int16 key,z,start_;
	char SearchField[200];
  char FullRecDens[3000],sel_prijstype_='\0',sel_soortklant_='\0',sel_geblokkeerd_='N';
  int k,FullRecDensLen=0,fkey_=2;

	if(!TbKlant) TbKlant= new _TbKlant[DIM_KLANT];
	if(!TbKlant) goto endsr;
	memset(SearchField,0,sizeof SearchField);  
	fasinit(2);
	FOREVER{
		redo:;
		scrnum=0;scrget(3,2);z=1;
		scrifld(z++,VarTextFmt(40,1),SearchField);
		scrifld(z++,fm_us1_U,&sel_prijstype_);
		if(fldlen(2,54)) scrifld(z++,fm_us1_U,&sel_soortklant_); else z++;
		if(fldlen(2,131)) scrifld(z++,fm_uJN,&sel_geblokkeerd_); else z++;
		key=scrupd(1,0x81);
	  if(key==101) break;
		scrget(1,7);scrupd(-3,0);
		memset(TbKlant,0,DIM_KLANT * sizeof TbKlant[0]); MaxKlt=0;
		GetSearchKeyWords(SearchField);
		fasinit(2);
		FOREVER {
			nextklt:;
			if(faskeyi(2,2,2)) break;
			if(sel_prijstype_ && *s(2,26)!=sel_prijstype_) goto nextklt;
			if(sel_soortklant_ && *s(2,54)!=sel_soortklant_) goto nextklt;
			if(sel_geblokkeerd_=='J' && *s(2,131)!='J') goto nextklt;
			FullRecDensLen=MakeFullRecDens(2,FullRecDens);
			if (AllKeywordsFound(FullRecDens,FullRecDensLen)==NO) goto nextklt;
			if(fldlen(16,1)){ // minstens laatste jaar afgenomen hebben
				fasinit(16);*l(16,10)=*u(2,1); *u(16,3)=*u(25,2)-365;
				if(faskeyi(16,4,1)) goto nextklt;
				if(*l(16,10)!=*u(2,1)) goto nextklt;
			}
			TbKlant[MaxKlt].RecordNr=*u(2,1);// record voldoet
			if(*s(2,131)=='J') TbKlant[MaxKlt].Used=1; 
			MaxKlt++;
			if(MaxKlt>=DIM_KLANT) break; // tabel vol
		}
		if(MaxKlt==0) {errnum=39;goto redo;}
		start_=0;
		FOREVER{  // .used wil hier zeggen geblokkeerd!
			scrnum=0;scrget(3,6);z=1;
			start_++;scrifld(z++,fm_ou4,&start_);start_--; scrifld(z++,fm_ou4,&MaxKlt);
			scraddpicto(5,0,76,22,4,2,593,0,0,"Blokkeer allen");
		  scraddpicto(6,0,72,22,4,2,578,0,0,"Deblokkeer allen");
			for(k=start_;k<start_+20;k++){
				if(k>=MaxKlt) break;
				fasinit(2);*u(2,1)=TbKlant[k].RecordNr; fasgeti(2);
				DisplayLine(z++);
				if(TbKlant[k].Used==0) {scrchat(z-1,0xFF);scraddpicto(10+k-start_,0,77,1+k-start_,2,1,593,0,0,"Blokkeer");}
				else {scrchat(z-1,0xB);scraddpicto(10+k-start_,0,1,1+k-start_,2,1,578,0,0,"Deblokkeer");}
			}
			key=scrupd(-1,0x87);
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key>=5010 && key<5030){
				k=start_+key-5010;
				if(TbKlant[k].Used) TbKlant[k].Used=0; else TbKlant[k].Used=1;
				fasinit(2);*u(2,1)=TbKlant[k].RecordNr;fasgeti(2);
				if(TbKlant[k].Used) *s(2,131)='J'; else *s(2,131)='N';
				fasupd(2);
			}
      if(key==5005 || key==5006){
				for(k=start_;k<start_+20;k++){
					if(k>=MaxKlt) break;
					if(key==5005) TbKlant[k].Used=1; else TbKlant[k].Used=0;
					fasinit(2);*u(2,1)=TbKlant[k].RecordNr;fasgeti(2);
					if(TbKlant[k].Used) *s(2,131)='J'; else *s(2,131)='N';
					fasupd(2);
				}
			}
			if(key==101 || key==108) break;
			if(key==102) start_-=20;
			if(key==103) {start_+=20; if(start_>=MaxKlt) start_-=20;}
			if(start_<0) start_=0;
		}
	}
endsr:;
	if (TbKlant) {delete TbKlant; TbKlant=0;}
}

//////////////////////

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
  scrifld(z,VarTextFmt(74,0),buf_);
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


/////////////////////////
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

static void CheckInhoud(void)
{
	char anm_[50],ean_[15],sys3896[6];
	int16 cnt_,start_,k,z,key,pkasprx_,skip_art_;
	uint16 dt_beg_,dt_end_,jj,mm;
	float NewVol_;
	CString cstr_,artnaam_;

	if (!TbArtikel) TbArtikel = new _TbArtikel[DIM_ARTIKEL]; 
	if (!TbArtikel) goto endsr;
	memset(TbArtikel,0,DIM_ARTIKEL * sizeof TbArtikel[0]);
	dt_beg_=datejd(InqJaar,InqMaand,1);
	jj=InqJaar; mm=InqMaand+1; if(mm>12){mm=1;jj=InqJaar+1;} dt_end_=datejd(jj,mm,1)-1;
	
	MaxArtikel=0;
	sysget(3896,6,sys3896);
	pkasprx_=sys3896[0]-'0'; if(pkasprx_<0 || pkasprx_>9) pkasprx_=0;
	pkasprx_+=21;
	fasinit(6);cnt_=0;scrget(1,7);scrupd(-3,0);
	FOREVER{
		next_art:;
		if(faskeyi(6,2,2)) break;
		if(ViaHistoriek){
			fasinit(16);*l(16,20)=*u(6,1);skip_art_=YES;
			FOREVER{
				if(faskeyi(16,1,2)) break;
				if(*l(16,20)!=*u(6,1)) break;
				if(*u(16,3)>=dt_beg_ && *u(16,3)<=dt_end_){skip_art_=NO;break;}
			}
			if(skip_art_) goto next_art;
		}
		cnt_++;if((cnt_%1000)==0){scrnum=0;scrget(1,7);scrupd(-3,0);}
		if(*u(6,9)!=99){
			zero(anm_,sizeof anm_);	copy0(s(6,3),anm_,fldlen(6,3));
			cstr_=CString(anm_);cstr_.MakeUpper(); copy((char *)(LPCTSTR)cstr_,anm_,cstr_.GetLength());// uppercase
			zero(ean_,sizeof ean_); if(*s(6,71)) copy0(s(6,71),ean_,fldlen(6,71)); else copy0(s(6,70),ean_,fldlen(6,70)); 
			NewVol_=ExecOneVol(anm_,ean_,*f(6,37),*f(6,31));
		}
	}
	if(MaxArtikel==0) goto endsr;
	start_=0;
	FOREVER{
		scrnum=0;scrget(3,5);z=1;
		for(k=start_;k<start_+20;k++){
			if(k>=MaxArtikel) break;
			fasinit(6);*u(6,1)=TbArtikel[k].RecordNr; fasgeti(6);
			scrofld(z++,6,3,-1);

			scrifld(z++,fm_od4_0,&TbArtikel[k].OldAantal);
			scrifld(z++,fm_ud4_0,&TbArtikel[k].NewAantal); 
			scrifld(z++,fm_od4_2,&TbArtikel[k].OldInhoud);
			scrifld(z++,fm_ud4_2,&TbArtikel[k].NewInhoud);
			scrofld(z++,6,pkasprx_,-1);
			if(TbArtikel[k].updated) scraddpicto(10+k-start_,0,66,2+k-start_,2,1,86,1034,0,"Pas artikel aan");
			else scraddpicto(10+k-start_,0,66,2+k-start_,2,1,578,0,0,"Pas artikel aan");
		}
		key=scrupd(1,0x7);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5010 && key<5030){
			k=start_+key-5010;
			fasinit(6);*u(6,1)=TbArtikel[k].RecordNr; fasgeti(6);
			*f(6,31)=TbArtikel[k].NewAantal;*f(6,37)=TbArtikel[k].NewInhoud;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			fasupd(6);
			TbArtikel[k].OldAantal=TbArtikel[k].NewAantal;
			TbArtikel[k].OldInhoud=TbArtikel[k].NewInhoud;
			TbArtikel[k].updated=YES;
		}


		if(key==101) break;
		if(key==102) start_-=20;
		if(key==103) {start_+=20; if(start_>=MaxArtikel) start_-=20;}
		if(start_<0) start_=0;
	}
	endsr:;
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


static float  ExecOneVol(char* Name, char* Ean, float ArtVol, float ArtCnt)
{
	float DMVol=0;
	float ItmVol=0.;
	float ItmCnt=0;

	CString N=Name;
	N.Replace("O","0");
	N.Replace("1664","    ");
	N.Replace(" 2.4 X","");
	N.Replace(" 1X6LT "," 6X1LT ");
	SearchString=N;


	
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
	if (CheckKeyWord("12 X")) ItmCnt=12;
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

	DMVol=ItmVol*ItmCnt;
  if (!(ArtVol>(DMVol*0.95) || DMVol<0.001)){ // gewijzigd !
		TbArtikel[MaxArtikel].RecordNr=*u(6,1);
		TbArtikel[MaxArtikel].OldAantal=ArtCnt;
		TbArtikel[MaxArtikel].OldInhoud=ArtVol;
		TbArtikel[MaxArtikel].NewAantal=ItmCnt;
		TbArtikel[MaxArtikel].NewInhoud=DMVol;
		MaxArtikel++;
	}

//	TRACE("Vol=%.2f ipv %f (%s %s %f)\r\n",DMVol,ArtVol,Name,Ean,ArtVol,ArtCnt);
//
//	CString cstr;
//	cstr.Format(_T("%.2f;%.2f;\"%s\";\"'%s\";%.2f;%.2f\r\n"),ItmCnt,DMVol,Name,Ean,ArtCnt,ArtVol);
//	CFile filspec;
//	CString FileNam;
//	FileNam.Format(_T("..\\DMC\\VOL-%06.2f.csv"),DMVol);
//	if (filspec.Open(FileNam,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite,NULL)) {
//		filspec.SeekToEnd();
//		filspec.Write(cstr,cstr.GetLength());
//		filspec.Close();
//	}
//
//	if (ArtVol>(DMVol*0.95) || DMVol<0.001) return ArtVol; // ongewijzigd !
//
//	if (filspec.Open("..\\DMC\\VOL-CORR.csv",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite,NULL)) {
//		filspec.SeekToEnd();
//		filspec.Write(cstr,cstr.GetLength());
//		filspec.Close();
//	}

	return DMVol;
}
static void InitLoad(void)
{
	uint16 n,g;
  CString cstr_,keystr_;
   
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
	sysget(3000,2,(char *)&sys3000); // 1= XLS uitschrijven
  sysget(3002,2,(char *)&sys3002); // 1= GEEN adresinfo klant uitschrijven
	sysget(3044,2,(char *)&DM_Settings.LastMaand); 
	sysget(3046,2,(char *)&DM_Settings.LastJaar);
	sysget(3048,1,(char *)&DM_Settings.ExportKlanten);
	sysget(3049,60,(char *)&DM_Settings.EmailAdres);
	sysget(3109,2,(char *)&DM_Settings.DMSelectieLeverancier);
	sysget(3111,1,(char *)&DM_Settings.SoortExport);	
	sysget(3112,15,(char *)DM_Settings.StrSpecKlantKol);
	sysget(3127,5,(char *)DM_Settings.SelectPrijsType);
	sysget(3132,5,(char *)DM_Settings.SelectSoortKlant);
	sysget(3137,1,(char *)&DM_Settings.DoExportDM);
	sysget(3138,1,(char *)&DM_Settings.DoExportColda);
	sysget(3139,1,(char *)&DM_Settings.ExportKassaVerkopen);
	sysget(3140,1,(char *)&DM_Settings.ExportBlockedKlanten);
	sysget(3141,1,(char *)&DM_Settings.DefaultBlockNewKlanten);
  sysget(4294,20,(char *)&loc_klt[0]); // maar 10 klanten hier!

	memcpy(CntDispStr,"-X|/",4);CntDispStr[1]=0x5C;

	InitConvertTab();

	if(fldlen(2,131) && DM_Settings.DefaultBlockNewKlanten=='J'){ // default blokkeren van nieuwe klanten
    fasinit(2);n=0;
	  FOREVER{
		  *u(2,1)=++n;
		  g=fasgeti(2);
		  if(g==47) break;
		  if(g!=46){  // niet gedelete record 
				if(*s(2,131)!='J' && *s(2,131)!='N') {*s(2,131)='J'; fasupd(2);}
			}
		}
	}

}

   

static void Jama2Ascii(char *ps_,int len_)
{
  int k,cnt_fas2sif_;
  int kar_;

	cnt_fas2sif_=(sizeof fas2sif)/(sizeof fas2sif[0]);
  for(k=0;k<len_;k++){
		kar_=*ps_;
    if(kar_>='\x80' && kar_<'\x80'+cnt_fas2sif_){
      *ps_=fas2sif[*ps_-'\x80'];
    }
		ps_++;
  }
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


static CString Date2String(unsigned int date_,int mode_)
{
   char txtbuffer_[100];

   zeros(txtbuffer_,sizeof txtbuffer_);
   if(date_) datefm(txtbuffer_,date_,mode_);

   return CString(txtbuffer_);
}


// STANDAARD routines


static CString arr2cstr(char *ps, int max_len)
{
  CString cstr="";
  int len_=0;
	  
  while (len_<max_len && *ps!=0) {cstr+=(TCHAR)*ps++;len_++;}

  return cstr;
}

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
 


static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}

static void MailDocument(int SendMode, int mode_) // SPECIFIEK
{
  int j,k,pos_,p_adr_=0;
	  
		// keywords invullen 
	zero(MailMergeData[0],sizeof MailMergeData);MailSaveAdres='N';

	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){
			if(mode_==0) copy("DataMasters",MailMergeData[k],11);
			else copy("ColDa",MailMergeData[k],11);
			continue;
		}
		if(cmpstr(MailMergeKeywords[k],"CONTACTPERSOON",14)==0){copy(s(25,1),MailMergeData[k],fldlen(25,1)); continue;}
		if(cmpstr(MailMergeKeywords[k],"PERIODE",7)==0){
			stcli_d(&MailMergeData[k][0],(long)InqMaand,2,0);MailMergeData[k][2]='/';
			stcli_d(&MailMergeData[k][3],(long)InqJaar,4,0);
			continue;
		}
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){
			p_adr_=k;
			if(mode_==0) copy("zipsales@datamasters.be",MailMergeData[k],25);
			else copy(DM_Settings.EmailAdres,MailMergeData[k],60);
			continue;
		} 
	}
	for(j=4;j>=0;j--) if(MailBodyText[j][0]) break;
	zero(MailMergeBodyText,sizeof MailMergeBodyText);pos_=0;
	if(j>=0){
		for(k=0;k<=j;k++) {
			pos_+=copy0(MailBodyText[k],&MailMergeBodyText[pos_],75);
			if(k<j) MailMergeBodyText[pos_++]=' '; // '\n';
		}
	}
	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);MailMergeBijlage[0]=SpoolFileNr;
	zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate);
	copy("DATAM",MailMergeSpecialTemplate,5); // vaste template 

	MailMergeFormaat=5; 
//	if(fldlen(2,24)) MailMergeTaal=talen[taaltxt]; else MailMergeTaal='\0';
	k=SendMail(SendMode); 
	if(k && MailSaveAdres=='J'){
		copy0(MailMergeData[p_adr_],(char *)&DM_Settings.EmailAdres,60); // email adres bewaren
	  sysput(3049,60,(char *)&DM_Settings.EmailAdres);
  }
}


