/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* DRK2394GetD() {return &zzvw;}
extern "C" void AddTextKey(int16 Fld,int16 Hz,int16 Vt,int16 Xlen,int16 Ylen,int16 KeyNr,char *KeyText,long KleurRGB);
extern "C" int CopyMoveFile(char *FromFile,char *ToFile,int DeleteOriginal); // kopieren van een file
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
extern "C" int WebrequestJson(char* Outputbuf, int MaxOutputbufLen, char *Url, char *Method, char *User, char *PW, char *HeaderKey, char *HeaderValue, char *Message, char *FileName, int ForceUnchangedInput, int ForceUnchangedOutput);
extern "C" int JsonToXml(char *Outputbuf, int MaxOutputbufLen, char *JsonString);
extern "C" int XmlToJson(char *Outputbuf, int MaxOutputbufLen, char *XmlString);


typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
 
static int16 ovlcall();
__declspec(dllimport) unsigned char PrintPaperNr;

extern "C" char DRK2394dat[] = "drk2394  00:01 30/07/19 (c) Jamadata"; // Verwerken bestellingen Coca-Cola via PULL-transfer webservice

// XML-bestanden komen in  ..\Share\Coca-Cola\   (vast geprogrammeerd)

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

#define COCA_WEBURL "https://api.cokecce.com/Wholesaler/"
#define TESTCOCA_WEBURL "https://apiqa.cokecce.com/Wholesaler/"
//
//#if _DEBUG
//#define COCA_WEBURL "https://apiqa.cokecce.com/Wholesaler/"
//#else
//#define COCA_WEBURL "https://api.cokecce.com/Wholesaler/"
//#endif

#define COCA_SUBDIR "..\\share\\Coca-Cola\\"

 
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
static char fm_uLP[]   = {11,0xC8,1,0,1,0,'L','L','P','P',0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ugrb[]  = {2,0xE8};
static char fm_us10PW[] = {7,0xC8,10,0,4,0,0};

static int16 prt2pdf,BewCount,TestApiMode;
static char sys3896[6],fmt[40],ScheidingsTeken='\x09',SelectieEenheid[10],MapBestelling[51],BonNr[20];
static char filnam[100],def_munt[4],buf1000[1000], StrBonNr[10];
static char lev_res[60],klt_res[60],art_res[60],firma[350];
static uint16 dat_beg,dat_end,inq_lev=0,BonDate,*pLevFld,InqLev,OrigKltRec;
static flag sys3894,sys2982;
static flag sear_stt,sys3876;
uint16 RecCCEP; // >30000 = merk/producent
static int16 form_dat[8],prtnr,pr_mode,skip_off;

static uint16 recs_used,DeliveryDate;
static uint16 recs[MAX_RECS];
static char recs_preferred[MAX_RECS];

static char ICSBTab[256];
static char *OrderStatusTxt[3]={" *** NIEUW *** ","** INGEGEVEN **","** AFGEWERKT **"};

static struct {
	char Code[10];
	char ExtCode[10];
	char Naam[40];
	char EAN[15];
	char OrderLineNr[15];
	float Aantal;
	float Prijs;
	char Eenheid[5];
	float AfwijkendAantal;
	uint16 ArtRec;
	float ArtAantalBak;
	float ArtInhoud;
} BewLijn[DIM_BEWLIJN];

static struct {
	char OrderNr[15];
	uint16 Datum;
	uint16 LevDatum;
	char KlantNr[10];
	char ExtKlantNr[10];
	char Naam[40];
	char Adres[40];
	char Postcode[10];
	char Gemeente[30];
	uint16 RecNr;
	char Opmerking[100];
	char OrderFileName[100];
} BonHeader;

static struct _Settings {
	char EmailAdres[60];
	uint16 RecLeverancier; // >30000 = merk/producent
	char KlantNummer[11];
	uint16 LastMaand;
	char SoortExport; // 0= niet gedetailleerd, 1= gedetailleerd
	char API_key[51];
} Settings;
/* --------------------------- Declaratie functies ---------------------- */

static int AKDataFromCCEPXml(void);
static void AddBon2Doc(void);
static int AskLevDate(char *ptxt) ;
static int16 cmpstrU(char *p1,char *p2,int16 len);
static int copy0(char *ps,char *pd,int max);
static int16 Copy2ZoekStr(char *ps3_,char *zoekstr,uint16 len3_,uint16 lenz_);
static int CopyOnlyChar(char *ps, char *pd, int16 len_);
static double Round(double getal, double round);
static CString Date2String(unsigned int date_,int mode_);
static bool DisplayLeverData(char *filename_,int ordertype_);
static int DisplayExtraOrderFuncties(int ordertype_);
static int16 ExecSearch(int16 mode_);
static void fileopen(int16 nr_);
static int16 FindBewArt(int16 nr_); // zoek artikel op referentie leverancier of EAN
static int fmt_get(int16 stu_, int16 elet_);
static int GetOrdersFromCCEP(void);  // vraag orders en converteer naar aparte files in Share\Coca-Cola\Orders
static int GetOrderFromSelection(char *ptitel_,char *pselection_); // result komt in SelectedFileName
static int GetSearchText(char *s,char *d, int len);  // analoog aan JMS (composekey)
static void InitConvertTab();  // komt uit JMS
static void initload(void);
static int KoppelArtikel(int listnr_,int DoSelect_); // zoek/koppel artikel 
static int KoppelKlant(void);
static int NettoCompareStr(char *p1,char *p2,int16 len);
static void PrintOrder(void);
static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_);
static bool ReadCCEPXml(char *filename_);
static int SendOrderOK2CCEP(char *OrderNr, int16 OKmode);  // Order als verwerkt sturen naar CCEP : 0=verwerkt in bon, 1=gefactureerd/geleverd
static uint16 String2Date(CString datestr_,CString format_);
static double String2Getal(CString S,char decim_kar);
static double String2Double(CString S){return String2Getal(S,',');}
static double String2Double(CString S,char decim_kar){ return String2Getal(S,decim_kar);}
static int String2Int(CString S){return (int)(String2Getal(S,','));}
static void UpdateSettings(void);

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

extern "C" void DRK2394cod(int parmval) // 0=read xml CCEP via stu58 vanuit 240, 1=set status ingegeven en rename naar .OK, 2=send delevired to CCEP en rename naar .DONE
{
	int k,klt_empty_;
	char dsp_str_[100];


	  initload();
		OrigKltRec=*u(2,1);
#if _DEBUG // in test werken per default
		TestApiMode=YES;
#endif
	//SendOrderOK2CCEP(); ovlexit(-1);
	//GetOrdersFromCCEP();   ovlexit(-1);
		switch(parmval){
		case 0  : AKDataFromCCEPXml(); break;
    case 1  : DeliveryDate=*u(8,8);// ingegeven als bon
			        zero(dsp_str_,sizeof dsp_str_);
			        sprintf_s(dsp_str_,sizeof dsp_str_,"Mag dit Coca-Cola order %s als ingegeven gemarkeerd worden?",s(8,24));
			        if(AskLevDate(dsp_str_)==YES) { retcall=SendOrderOK2CCEP(s(8,24), 0);} 
							else retcall=NO;
			        break; 
    case 2  : DeliveryDate=*u(8,8); // verwerkt als factuur 
					    zero(dsp_str_,sizeof dsp_str_);
			        sprintf_s(dsp_str_,sizeof dsp_str_,"Wenst U aan Coca-Cola te melden dat order %s geleverd/gefactureerd is?",s(8,24));
			        if(AskLevDate(dsp_str_)==YES) { retcall=SendOrderOK2CCEP(s(8,24), 1);} 
							else retcall=NO;
			        break; 
	  default : break;
	}
	ovlexit(-1);
}
 

static int GetOrdersFromCCEP(void)  // vraag orders en converteer naar aparte files in Share\Coca-Cola\Orders
{
	int j,len,ordercount;
	char resultbuf[300000],ackresponse[1000],orderfname_[100]; // ,jstr_[50000];
	CString cstr_,cUrl,cApi,cOrderNr,cKlantNaam,cfileorder_;
	CMarkup OrderList,Order,OKOrder;

 //TEST

	//CFile fil;

	//if (!fil.Open(_T("..\\share\\coca-cola\\Official_Multiple_Order_Reception_Sample.json"),CFile::modeRead,0)) return NO;
	//// if (!fil.Open(_T("..\\share\\coca-cola\\Order_Confirmation_ACK_Multiple.json"),CFile::modeRead,0)) return NO;
	//len = (int)fil.GetLength();

	//memset(resultbuf,0,sizeof resultbuf); memset(jstr_,0,sizeof jstr_);if(len>sizeof jstr_) len=sizeof jstr_ -10;
	//fil.Read(jstr_,len);
 //	fil.Close();
	//j=JsonToXml(resultbuf,sizeof resultbuf, jstr_);
	//EINDE TEST
	if(Settings.API_key[0]=='\0' || Settings.RecLeverancier==0 || Settings.KlantNummer[0]==0){
		DisplayWarning("Parameters zijn niet ingevuld! Ga eerst naar punt V.4 en dan Coca-icoon.",605,0);
		return NO;
	}
	DisplayWarning("Controleren op nieuwe orders Coca-Cola....",0,2);
	if(TestApiMode) cUrl=CString(TESTCOCA_WEBURL); else cUrl=CString(COCA_WEBURL); 
	cUrl+=CString("orders?apiKey="); //  CString("https://apidev.cokecce.com/Wholesaler/orders?apiKey="); 
	cApi=CString(Settings.API_key); // test : 979d1949117d4987bd6db840260539e8
	cUrl=cUrl+cApi;
	memset(resultbuf,0,sizeof resultbuf);
	
	redoweb:;
	if(WebrequestJson(resultbuf,sizeof resultbuf, (char *)((LPCTSTR)cUrl),"GET","","","","","","",NO,NO)==NO){
		DisplayWarning(resultbuf,605,0);
		return NO;
	}		

	OrderList=CMarkup(); ordercount=0;
	OrderList.SetDoc(resultbuf);
	if(OrderList.IsWellFormed()!=1){
		return NO;
	}
	OrderList.ResetMainPos();
// TEST	OrderList.Save("Origineel.xml");
	if(OrderList.FindElem("Orders")==false) {OrderList.Close(); return false;}
	  
  // ACK-xml klaarmaken 
	OKOrder=CMarkup();
	OKOrder.SetDoc("");
	OKOrder.ResetMainPos();
	
	OrderList.IntoElem();
	  OrderList.ResetMainPos();
		FOREVER{
			next_order:;
		  if(OrderList.FindElem("Order")==false) break;
		  OrderList.IntoElem();
				if(OrderList.FindElem("Header")==false){OrderList.OutOfElem(); goto next_order;} // bad header
		    OrderList.IntoElem();
	        OrderList.ResetMainPos();cOrderNr=OrderList.FindGetData("Order_number");
				  OrderList.ResetMainPos();cKlantNaam=OrderList.FindGetData("Account_Name");
					cfileorder_=CString(COCA_SUBDIR); cfileorder_+=CString("Orders\\"); cfileorder_+=cOrderNr; cfileorder_+=" "; cfileorder_+=cKlantNaam; cfileorder_+=".XML";
					zero(orderfname_,sizeof orderfname_); copy((char *)((LPCTSTR)cfileorder_),orderfname_,cfileorder_.GetLength()); CnvJamaChar(orderfname_,sizeof orderfname_,1);
				OrderList.OutOfElem();
			OrderList.OutOfElem();
			Order=CMarkup();
			cstr_=OrderList.GetElemContent();
			Order.AddElem("Order"); Order.SetElemContent(cstr_);
			Order.Save(orderfname_);
			// ACK-xml bijwerken
			ordercount++;
			OKOrder.AddElem("Orders");
	    OKOrder.AddAttrib("xmlns:json", "http://james.newtonking.com/projects/json"); 
			OKOrder.IntoElem();
			OKOrder.AddElem("Order_number",cOrderNr); 
			OKOrder.OutOfElem();
	  }
  OrderList.OutOfElem();

	
	if(ordercount){ // send received OK
// TEST OKOrder.Save("TestAck.xml");
#if _DEBUG // in debug/test altijd vraag stellen
	if(YES){
#else
  if(TestApiMode){
#endif
		if(DisplayWarning("TEST VERSIE: Wenst U de ontvangst van dit order te bevestigen aan Coca-Cola?",61,1)==NO) return YES;
	}

		cstr_=OKOrder.GetDocFormatted();

//  TEST j=XmlToJson(resultbuf,sizeof resultbuf,  (char *)((LPCTSTR)cstr_));

		if(TestApiMode) cUrl=CString(TESTCOCA_WEBURL); else cUrl=CString(COCA_WEBURL); 
		cUrl+=CString("orders/confirmation?apiKey=");
		cApi=CString(Settings.API_key); // test : 979d1949117d4987bd6db840260539e8
		cUrl=cUrl+cApi;
		memset(ackresponse,0,sizeof ackresponse);
		if(WebrequestJson(ackresponse,sizeof ackresponse, (char *)((LPCTSTR)cUrl),"POST","","","","",(char *)((LPCTSTR)cstr_),"",NO,NO)==NO){
			DisplayWarning(ackresponse,605,0);
			return NO;
		}

	}
	return YES;
}

static int SendOrderOK2CCEP(char *OrderNr, int16 OKmode)  // Order als verwerkt sturen naar CCEP : 0=ingegeven, 1=gefactureerd/geleverd, 999 : orderontvangst bevestigen
{
	int j,len,qlv_;
	char resultbuf[75000]; 
	CString cstr_,cUrl,cApi,cOrderNr,cOrigOrderNr,cKlantNaam,cfileorder_,cfileorderOK_,cUpdated,selection_,o_suff_,n_suff_;
	CMarkup OrderList,bonxml_,OKOrder;



  WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
	CString cfilenames[100],cfiledates[100];
  SYSTEMTIME stUTC, stLocal;
  DWORD dwRet;
	char fm_ou3[]   = {6,0x90,3,0,0x60,0};
  char fm_uu3[]   = {6,0xD0,3,0,0x60,0};

	if(Settings.API_key[0]=='\0' || Settings.RecLeverancier==0 || Settings.KlantNummer[0]==0){
		DisplayWarning("Parameters zijn niet ingevuld! Ga eerst naar punt V.4 en dan Coca-icoon.",605,0);
		return NO;
	}

	cOrigOrderNr=CString(OrderNr);


	if(OKmode==999){ // versturen van confirmation 
	  OKOrder=CMarkup();
		OKOrder.SetDoc("");
		OKOrder.ResetMainPos();
		OKOrder.AddElem("Orders");
			OKOrder.AddAttrib("xmlns:json", "http://james.newtonking.com/projects/json"); 
			OKOrder.AddAttrib("json:Array","true"); 
		OKOrder.IntoElem();
		  cOrderNr=CString(OrderNr);OKOrder.AddElem("Order_number",cOrderNr); 
		OKOrder.OutOfElem();
//  TEST OKOrder.Save("TestAck.xml");

		cstr_=OKOrder.GetDocFormatted();

		if(TestApiMode) cUrl=CString(TESTCOCA_WEBURL); else cUrl=CString(COCA_WEBURL); 
		cUrl+=CString("orders/confirmation?apiKey=");
		cApi=CString(Settings.API_key); // test : 979d1949117d4987bd6db840260539e8
		cUrl=cUrl+cApi;
#if _DEBUG // in debug/test altijd vraag stellen
		if(DisplayWarning("TEST VERSIE: Wenst U echt te bevestigen aan Coca-Cola?  ",61,1)==NO) return YES;
#endif
		memset(resultbuf,0,sizeof resultbuf);
		if(WebrequestJson(resultbuf,sizeof resultbuf, (char *)((LPCTSTR)cUrl),"POST","","","","",(char *)((LPCTSTR)cstr_),"",NO,NO)==NO){
			DisplayWarning(resultbuf,605,0);
			return NO;
		} else return YES; 
	}


// Status van order versturen 
	if(DeliveryDate==0) DeliveryDate=*u(25,2);
	selection_=CString(COCA_SUBDIR); selection_+="Orders\\"; selection_+=CString(OrderNr); 
	selection_+="*.*"; 
	hSearch = FindFirstFile (selection_, &FileData); cfileorder_="";
  FOREVER{
    if (hSearch == INVALID_HANDLE_VALUE) break;
    if (!(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){                      // geen directory 
		  cfileorder_=CString(FileData.cFileName);
			if(cfileorder_.GetAt(0)!='~') break; // werkfiles xls/word skippen
		}
    if(FindNextFile (hSearch, &FileData)==false) break;
  }
  FindClose(hSearch);
	if(cfileorder_.GetLength()) cfileorder_=CString(COCA_SUBDIR) + "Orders\\" + cfileorder_; 

	if(bonxml_.Load(cfileorder_)==false) return false;
	if(bonxml_.FindElem("Order")==false) {bonxml_.Close(); return false;}
	bonxml_.IntoElem(); // into order
	retcall=0;
	if(OrderNr[0]=='\0') return NO;
	cOrigOrderNr=CString(OrderNr);

	OKOrder=CMarkup();
	OKOrder.SetDoc("");
	OKOrder.ResetMainPos();
	OKOrder.AddElem("Orders");OKOrder.AddAttrib("xmlns:json", "http://james.newtonking.com/projects/json"); OKOrder.IntoElem();
  	OKOrder.AddElem("Order");OKOrder.AddAttrib("json:Array","true"); OKOrder.IntoElem();
    	OKOrder.AddElem("OrderHeader"); OKOrder.IntoElem();
      	OKOrder.AddElem("OrderNumber",cOrigOrderNr);
        if(OKmode==0) OKOrder.AddElem("OrderHeaderStatus","00");
      	else if(OKmode==1) OKOrder.AddElem("OrderHeaderStatus","01");
			OKOrder.OutOfElem();
			OKOrder.AddElem("OrderLines"); OKOrder.IntoElem();


  		bonxml_.ResetMainPos(); if(bonxml_.FindElem("Lines")==false) {bonxml_.Close(); return false;}
  		bonxml_.IntoElem(); // lines
    		bonxml_.ResetMainPos(); 
				FOREVER{
					if(bonxml_.FindElem("Line")==false) break;
					bonxml_.IntoElem(); // line
					OKOrder.AddElem("OrderLineItem");OKOrder.AddAttrib("json:Array","true"); OKOrder.IntoElem();
						bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Order_Line_Item_Number"); OKOrder.AddElem("OrderLineItemNumber",cstr_);
						bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Material_EAN_Code"); 
						  if(cstr_.CompareNoCase("null")==0 || cstr_.GetLength()==0) cstr_="9999999999999";
						  cstr_.Truncate(13); OKOrder.AddElem("OrderMaterialEANCode",cstr_);
						bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Material_Description"); 
						cstr_=cstr_.Left(50);OKOrder.AddElem("OrderMaterialDescription",cstr_);
						bonxml_.ResetMainPos(); qlv_=String2Double(bonxml_.FindGetData("Quantity"),'.'); OKOrder.AddElem("OrderLineActualDeliveredQty",qlv_);
						if(OKmode==0) OKOrder.AddElem("OrderLineStatus","00");
      	    else if(OKmode==1) OKOrder.AddElem("OrderLineStatus","01");
	          cstr_=Date2String(DeliveryDate,3); 
						OKOrder.AddElem("OrderActualDeliveryDate",cstr_); // "10/08/2019");
          OKOrder.OutOfElem(); 
					bonxml_.OutOfElem();
				}
      OKOrder.OutOfElem(); 
			bonxml_.OutOfElem();
			OKOrder.AddElem("OrderFooter"); OKOrder.IntoElem();
			bonxml_.ResetMainPos(); if(bonxml_.FindElem("Header")==false) {bonxml_.Close(); return false;}
			bonxml_.IntoElem();  // header
			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Account_Number"); if(cstr_.GetLength()==0) cstr_="999999"; OKOrder.AddElem("OrderCCEPAccountNumber",cstr_);
				bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("External_Account_Id"); 
				  if(cstr_.CompareNoCase("null")==0 || cstr_.GetLength()==0) cstr_="99999";
				  OKOrder.AddElem("OrderWholesalerExternalAccountId",cstr_);
				bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Sales_Organization"); OKOrder.AddElem("OrderSalesOrganization",cstr_);
				OKOrder.AddElem("OrderComments"," ");
			bonxml_.OutOfElem();
	bonxml_.Close();

// TEST	OKOrder.Save("TestAck.xml");

	if(OKmode==0) {// Status ingegeven, enkel xml renamen naar .OK, niets sturen naar CCEP
		if(cfileorder_.GetLength()){  // orderfile renamen naar OK of DONE
			cfileorderOK_=cfileorder_; o_suff_=CString(""); n_suff_=CString("");
			if(cfileorder_.Find(".XML")>=0) o_suff_=CString(".XML");
			else if(cfileorder_.Find(".OK")>=0) o_suff_=CString(".OK");
			else if(cfileorder_.Find(".DONE")>=0) o_suff_=CString(".DONE");
			if(OKmode==0) n_suff_=CString(".OK"); else n_suff_=CString(".DONE");
			if(o_suff_.GetLength() && o_suff_!=n_suff_){
				cfileorderOK_.Replace(o_suff_,n_suff_);
				CopyMoveFile((char *)((LPCTSTR)cfileorder_),(char *)((LPCTSTR)cfileorderOK_),YES);
			}
			return YES;
		}	else return NO;
	}

	// Status 1: "geleverd" versturen naar CCEP en renamen naar .DONE

	cstr_=OKOrder.GetDocFormatted();
	if(TestApiMode) cUrl=CString(TESTCOCA_WEBURL); else cUrl=CString(COCA_WEBURL); 
	cUrl+=CString("OrderStatus?apiKey=");
  cApi=CString(Settings.API_key); // test : 979d1949117d4987bd6db840260539e8
	cUrl=cUrl+cApi;
	memset(resultbuf,0,sizeof resultbuf);
#if _DEBUG // in debug/test altijd vraag stellen
	if(DisplayWarning("TEST VERSIE: Wenst U echt te bevestigen aan Coca-Cola?  ",61,1)==YES) 
#endif
	if(WebrequestJson(resultbuf,sizeof resultbuf, (char *)((LPCTSTR)cUrl),"POST","","","","",(char *)((LPCTSTR)cstr_),"",NO,NO)==NO){
		DisplayWarning(resultbuf,605,0);
		return NO;
	}

	if(cfileorder_.GetLength()){  // orderfile renamen naar OK of DONE
		cfileorderOK_=cfileorder_; o_suff_=CString(""); n_suff_=CString("");
		if(cfileorder_.Find(".XML")>=0) o_suff_=CString(".XML");
		else if(cfileorder_.Find(".OK")>=0) o_suff_=CString(".OK");
		else if(cfileorder_.Find(".DONE")>=0) o_suff_=CString(".DONE");
		if(OKmode==0) n_suff_=CString(".OK"); else n_suff_=CString(".DONE");
		if(o_suff_.GetLength() && o_suff_!=n_suff_){
			cfileorderOK_.Replace(o_suff_,n_suff_);
			CopyMoveFile((char *)((LPCTSTR)cfileorder_),(char *)((LPCTSTR)cfileorderOK_),YES);
		}
	}				




	OrderList=CMarkup();
	OrderList.SetDoc(resultbuf);
	j=OrderList.IsWellFormed();
// TEST	OrderList.Save("testACKreturn.xml");

	OrderList.ResetMainPos();
  	if(OrderList.FindElem("OrderStatusResponse")==false) return 0;
	  OrderList.IntoElem();
	FOREVER{
		nextorder:;
  	if(OrderList.FindElem("OrderStatus")==false) break;
	  OrderList.IntoElem();
     	if(OrderList.FindElem("OrderHeaderStatus")==false){
	  		OrderList.OutOfElem(); goto nextorder;
			}
 	    OrderList.IntoElem();
	    OrderList.ResetMainPos();cOrderNr=OrderList.FindGetData("OrderNumber");
			OrderList.ResetMainPos();cUpdated=OrderList.FindGetData("Success");
			if(cOrderNr.CompareNoCase(cOrigOrderNr)==0 && cUpdated.CompareNoCase("TRUE")==0){
				//if(cfileorder_.GetLength()){  // orderfile renamen naar OK of DONE
				//	cfileorderOK_=cfileorder_; o_suff_=CString(""); n_suff_=CString("");
				//	if(cfileorder_.Find(".XML")>=0) o_suff_=CString(".XML");
				//	else if(cfileorder_.Find(".OK")>=0) o_suff_=CString(".OK");
				//	else if(cfileorder_.Find(".DONE")>=0) o_suff_=CString(".DONE");
				//	if(OKmode==0) n_suff_=CString(".OK"); else n_suff_=CString(".DONE");
				//	if(o_suff_.GetLength() && o_suff_!=n_suff_){
				//		cfileorderOK_.Replace(o_suff_,n_suff_);
				//		CopyMoveFile((char *)((LPCTSTR)cfileorder_),(char *)((LPCTSTR)cfileorderOK_),YES);
				//	}
				//}				
				return YES;
			}
	  	OrderList.OutOfElem(); // orderheaderstatus
		OrderList.OutOfElem(); // orderstatus
	}
	return 0;
}


static int AKDataFromCCEPXml()
{
	int k;
	char str_selectie_[100];

	
	zero(str_selectie_,sizeof str_selectie_); retcall=0;
	k=copy0(COCA_SUBDIR,str_selectie_,50); k+=copy0("Orders\\*.XML",&str_selectie_[k],17);
	FOREVER{
		if(GetOrderFromSelection(" Orders Coca-Cola ",str_selectie_)==0){errnum=14; break;}
  	if(ReadCCEPXml(SelectedFileName)){
			if(YES /* DisplayLeverData(SelectedFileName) */) {
				if(OrigKltRec && *u(2,1)!=OrigKltRec){
					if(DisplayWarning("De klant komt NIET overeen met deze van de bon. Toch verdergaan???",61,1)==NO) break;
				}
				AddBon2Doc();
				if(OrigKltRec && *u(8,1)){ // bij bestaande bon klant terugzetten uit veiligheid
					fasinit(2);*u(2,1)=OrigKltRec; fasgeti(2);
				}
				if(BestelFileUsed[0][0]=='\0') {copy0(SelectedFileName,BestelFileUsed[0],100); *(uint16 *)&BestelFileUsed[0][100]=2394;}
				else {copy0(SelectedFileName,BestelFileUsed[1],100); *(uint16 *)&BestelFileUsed[1][100]=2394;}
				retcall=YES; break;
			}
		}
	}
	return 1;
}

static bool ReadCCEPXml(char *filename_)
{
  int16 jj_,mm_,dd_,pos1_,pos2_,k,fl_cmt_;
	char buf_[50];
	CString cstr_,commentaar_;
  CMarkup bonxml_;

	scrget(1,7);scrupd(-3,0);
	zeroL((char *)BonHeader.OrderNr,sizeof BonHeader);
	zeroL((char *)&BewLijn[0].Code,sizeof BewLijn);BewCount=0;
	copy0(filename_,BonHeader.OrderFileName,sizeof BonHeader.OrderFileName);
	if(bonxml_.Load(filename_)==false) return false;
	if(bonxml_.FindElem("Order")==false) {bonxml_.Close(); return false;}
	bonxml_.IntoElem(); // order
	  bonxml_.ResetMainPos(); if(bonxml_.FindElem("Header")==false) {bonxml_.Close(); return false;}
		bonxml_.IntoElem();  // header
			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Order_number"); cstr2arr(cstr_,BonHeader.OrderNr,sizeof BonHeader.OrderNr); 
			bonxml_.ResetMainPos();BonHeader.Datum=String2Date(bonxml_.FindGetData("Order_Date").Left(10),"JJJJ-MM-DD");
			bonxml_.ResetMainPos();BonHeader.LevDatum=String2Date(bonxml_.FindGetData("Desired_Delivery_Date"),"JJJJ-MM-DD");
			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Account_Number"); cstr2arr(cstr_,BonHeader.KlantNr,sizeof BonHeader.KlantNr); 
			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("External_Account_Id"); cstr2arr(cstr_,BonHeader.ExtKlantNr,sizeof BonHeader.ExtKlantNr); 
			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Account_Name"); cstr2arr(cstr_,BonHeader.Naam,sizeof BonHeader.Naam); CnvJamaChar(BonHeader.Naam,sizeof BonHeader.Naam,1);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("ShippingStreet"); cstr2arr(cstr_,BonHeader.Adres,sizeof BonHeader.Adres); 
			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("ShippingPostalCode"); cstr2arr(cstr_,BonHeader.Postcode,sizeof BonHeader.Postcode); 
			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("ShippingCity"); cstr2arr(cstr_,BonHeader.Gemeente,sizeof BonHeader.Gemeente); 
			bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Comments"); cstr2arr(cstr_,BonHeader.Opmerking,sizeof BonHeader.Opmerking); 
		bonxml_.OutOfElem();
  	bonxml_.ResetMainPos(); if(bonxml_.FindElem("Lines")==false) {bonxml_.Close(); return false;}
  	bonxml_.IntoElem(); // lines
    	bonxml_.ResetMainPos(); 
			FOREVER{
				if(bonxml_.FindElem("Line")==false) break;
				bonxml_.IntoElem(); // line
				  bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Order_Line_Item_Number"); cstr2arr(cstr_,BewLijn[BewCount].OrderLineNr,sizeof BewLijn[0].OrderLineNr); 
					bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Material_Description"); cstr2arr(cstr_,BewLijn[BewCount].Naam,sizeof BewLijn[0].Naam); 
					bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Material_EAN_Code"); cstr2arr(cstr_,BewLijn[BewCount].EAN,sizeof BewLijn[0].EAN); 
					bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Product_Code"); cstr2arr(cstr_,BewLijn[BewCount].Code,sizeof BewLijn[0].Code); 
					bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("External_Product_ID"); cstr2arr(cstr_,BewLijn[BewCount].ExtCode,sizeof BewLijn[0].ExtCode); 
					bonxml_.ResetMainPos(); BewLijn[BewCount].Aantal=String2Double(bonxml_.FindGetData("Quantity"),'.');
					bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Unit_Of_Measure"); cstr2arr(cstr_,BewLijn[BewCount].Eenheid,sizeof BewLijn[0].Eenheid); 
					bonxml_.ResetMainPos(); cstr_=bonxml_.FindGetData("Free_of_Charge"); if(cstr_.CompareNoCase("true")==0) BewLijn[BewCount].Prijs=0.00001; // om gratis aan te duiden
					if(cmpstr(BewLijn[BewCount].Naam,"Free",4)==0) BewLijn[BewCount].Prijs=0.00001; // om gratis aan te duiden
					BewCount++; if(BewCount>=DIM_BEWLIJN) break;
				bonxml_.OutOfElem();
			}
    bonxml_.OutOfElem();
	bonxml_.Close();
	if(fldlen(2,80) && BonHeader.KlantNr[0] && BonHeader.RecNr==0) { // eerst zoeken op CCEP nummer
		fasinit(2);
  	FOREVER{
	  	if(faskeyi(2,2,2)) break;
			if(cmpstr(BonHeader.KlantNr,s(2,80),fldlen(2,80))==0){BonHeader.RecNr=*u(2,1);break;} // gevonden
  	}
	}
	if(BonHeader.ExtKlantNr[0] && BonHeader.RecNr==0) { // zoeken op ext. klantnummer
		fasinit(2);
		if(fldlen(2,2)){
			copy(BonHeader.ExtKlantNr,s(2,2),fldlen(2,2));
			if(faskeyi(2,1,0)==0) BonHeader.RecNr=*u(2,1);
		}
		else{
      *u(2,1)=val(BonHeader.ExtKlantNr); 
			if(*u(2,1) && fasgeti(2)==0) BonHeader.RecNr=*u(2,1);
		}
	}
	 
	fasinit(11);*u(11,2)=RecCCEP; 
	FOREVER{ // artikelgegevens aanviullen
		next11:;
		if(faskeyi(11,1,2)) break; 
		if(*u(11,2)!=RecCCEP) break;
		if(*s(11,5)=='\0') goto next11;
		zero(buf_,sizeof buf_);	CopyOnlyChar(s(11,5),buf_,fldlen(11,5));
		for(k=0;k<BewCount;k++){
			if(cmpstrU(BewLijn[k].Code,buf_,sizeof BewLijn[0].Code)==0){
				fasinit(6);*u(6,1)=*u(11,3);fasgeti(6);
				if(fldlen(11,68)) BewLijn[k].AfwijkendAantal=*f(11,68);
				BewLijn[k].ArtRec=*u(6,1);
				BewLijn[k].ArtInhoud=*f(6,37);
				BewLijn[k].ArtAantalBak=*f(6,31);
				float factor_=1.; if(BewLijn[k].AfwijkendAantal && BewLijn[k].ArtAantalBak) factor_= BewLijn[k].AfwijkendAantal/ BewLijn[k].ArtAantalBak;
			}
		}
	}
	for(k=0;k<BewCount;k++){ // zoeken op meegegeven eigen Art.code
		if(BewLijn[k].ArtRec==0 && BewLijn[k].ExtCode[0]){
			fasinit(6);copy(BewLijn[k].ExtCode,s(6,2),fldlen(6,2)); 
			if(faskeyi(6,1,0)==0){
        fasinit(11);*u(11,2)=	RecCCEP; *u(11,3)=*u(6,1); 
				if(faskeyi(11,1,1)==0){		
					if(*u(11,2)==RecCCEP && *u(11,3)==*u(6,1)){
  				  if(fldlen(11,68)) BewLijn[k].AfwijkendAantal=*f(11,68);
						if(BewLijn[k].Code[0]){
							copy(BewLijn[k].Code,s(11,5),fldlen(11,5)); fasupd(11);
						}
					} else fasinit(11);
				} else fasinit(11);
				if(*u(11,1)==0 && BewLijn[k].Code[0]){
					fasinit(11);*u(11,2)=	RecCCEP; *u(11,3)=*u(6,1); 
					copy(BewLijn[k].Code,s(11,5),fldlen(11,5)); 
					fasadd(11);
				}
				BewLijn[k].ArtRec=*u(6,1);
				BewLijn[k].ArtInhoud=*f(6,37);
				BewLijn[k].ArtAantalBak=*f(6,31);
				float factor_=1.; if(BewLijn[k].AfwijkendAantal && BewLijn[k].ArtAantalBak) factor_= BewLijn[k].AfwijkendAantal/ BewLijn[k].ArtAantalBak;
			}
		}
	}
	for(k=0;k<BewCount;k++){ // zoeken op EAN
		if(BewLijn[k].ArtRec==0 && BewLijn[k].EAN[0]){
			*u(1,1)=RecCCEP; 
			if(FindBewArt(k)){
				fasinit(11);*u(11,2)=	RecCCEP; *u(11,3)=*u(6,1); 
				if(faskeyi(11,1,1)==0){		
					if(*u(11,2)==RecCCEP && *u(11,3)==*u(6,1)){
  					if(fldlen(11,68)) BewLijn[k].AfwijkendAantal=*f(11,68);
						if(BewLijn[k].Code[0]){
							copy(BewLijn[k].Code,s(11,5),fldlen(11,5)); fasupd(11);
						}
					} else fasinit(11);
				} else fasinit(11);
				if(*u(11,1)==0 && BewLijn[k].Code[0]){
					fasinit(11);*u(11,2)=	RecCCEP; *u(11,3)=*u(6,1); 
					copy(BewLijn[k].Code,s(11,5),fldlen(11,5)); 
					fasadd(11);
				}
				BewLijn[k].ArtRec=*u(6,1);
				BewLijn[k].ArtInhoud=*f(6,37);
				BewLijn[k].ArtAantalBak=*f(6,31);
				float factor_=1.; if(BewLijn[k].AfwijkendAantal && BewLijn[k].ArtAantalBak) factor_= BewLijn[k].AfwijkendAantal/ BewLijn[k].ArtAantalBak;
			}
		}
	}
  return true;
}

static bool DisplayLeverData(char *filename_,int ordertype_)
{
  int16 nr_,k,key,z,start_,lijnpos,q_,ScreenLines=15;
	unsigned short funckeys,arec_;
	char attrib_,artcode_[25];
	CString cstr_;
	


	fasinit(2);
	if(BonHeader.RecNr){*u(2,1)=BonHeader.RecNr;fasgeti(2);}
  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
    scrnum=0;scrget(3,10);z=1;q_=0; funckeys=0x60E1;
		scraddpicto(9,0,76,22,4,2,514,0,0,"Extra opties"); 
		scraddpicto(3,0,72,22,4,2,583,0,0,"Maak PDF"); 
		scrifld(z++,VarTextFmt(40,0),BonHeader.Naam); 
		cstr_=CString(BonHeader.Adres); cstr_+=" -'"; cstr_+=BonHeader.Gemeente; scrifld(z++,VarTextFmt(50,0),(char *)((LPCTSTR)cstr_)); // straat +  gemeente
		scrofld(z++,2,3,-1); if(BonHeader.RecNr==0) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);scraddpicto(10,z-1,0,0,2,1,69,0,4,"Koppel klant"); 
	  start_++;scrifld(z++,fm_ou3,&start_);start_--;scrifld(z++,fm_ou3,&BewCount);
		if(start_>0){ funckeys+=2; scraddpicto(1,0,76,7,4,2,18,0,4,"up"); }
		if((start_+ScreenLines)<BewCount) {funckeys+=4;scraddpicto(2,0,76,20,4,2,13,0,4,"down"); }
		scrifld(z++,VarTextFmt(15,0),OrderStatusTxt[ordertype_]);
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=BewCount) break;
			attrib_=0xFF; if(BewLijn[k].ArtRec==0) attrib_=0x0B;
			scrifld(z++,VarTextFmt(14,0),BewLijn[k].Code);scrchat(z-1,attrib_);
			scrifld(z++,VarTextFmt(32,0),BewLijn[k].Naam);scrchat(z-1,attrib_);scraddpicto(11+k-start_,z-1,0,0,2,1,69,0,4,"Koppel artikel"); 
			if(BewLijn[k].Prijs && BewLijn[k].Prijs<0.001) {
				scrifld(z++,VarTextFmt(8,0),"*Gratis*"); scrchat(z-1,attrib_);
			}
			else z++; 
			
			scrifld(z++,fm_of50_,&BewLijn[k].Aantal);
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
			case 5003    : PrintOrder();break;
			case 5009    : if(DisplayExtraOrderFuncties(ordertype_)) return false; break;
			case 5010    : KoppelKlant();break;
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

static void PrintOrder(void)
{
  int16 j,k;
  char *ps, buf100_[100];
	CString cstr_;

	
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(YES /* prt2pdf */) PrintPaperNr=0;
  if (prtopen(prtnr,form_dat,6,80,pr_mode,0)!=0) {goto endsr;}
	zero(buf100_,sizeof buf100_);
	cstr_=CString("Coca-Cola Order "); cstr_+=BonHeader.OrderNr; cstr_+=" van "; cstr_+=Date2String(BonHeader.Datum,1); copy0((char *)((LPCTSTR)cstr_),buf100_,sizeof buf100_);
	p_pdfname(buf100_,0,0);
  scrget(1,6);scrupd(-3,0);

  prttext("<t1><eb>");prtifld(VarTextFmt(30,0),&firma[0],30);prttext("<eb>");prtline();
  prttext("<t1>");prtifld(VarTextFmt(25,0),&firma[31],25);prtline();
  prttext("<t1>");prtifld(VarTextFmt(5,0),&firma[57],7);prtblank(2);
  prtifld(VarTextFmt(20,0),&firma[65],20);prtline();
  prtline(); prtline();

	if(BonHeader.RecNr){
		prttext("<t47>");prtfld(2,3,-1);prtline();
		prttext("<t47>");prtfld(2,4,-1);prtline();
		prttext("<t47>");prtfld(2,5,-1);prttext(" ");prtfld(2,6,-1);prtline();
	}
	else{
		prttext("<t47>");prtifld(VarTextFmt(40,0),BonHeader.Naam,-1); prtline();
		prttext("<t47>");prtifld(VarTextFmt(40,0),BonHeader.Adres,-1); prtline();
		prttext("<t47>");prtifld(VarTextFmt(5,0),BonHeader.Postcode,-1); prttext("  ");prtifld(VarTextFmt(25,0),BonHeader.Gemeente,-1); prtline();
	}
	prtline();prtline();prtline();
  prttext("<b>");prttext(buf100_);prttext("<b>");
  prtline();prtline();
  prttext("<u>Art.<ut7u>Omschrijving<ut49u>Aantal<u>");prtline();
  prtline();
  for(k=0;k<BewCount;k++){
	  fasinit(6);
	  if(BewLijn[k].ArtRec) {*u(6,1)=BewLijn[k].ArtRec;fasgeti(6);}
		prttext("<t1>");prtfld(6,2,-1);
		prttext("<t7>");
		if(BewLijn[k].ArtRec) prtfld(6,3,-1);
		else prtifld(VarTextFmt(40,0),BewLijn[k].Naam,-1);
		prttext("<t48>"); prtifld(fm_of50_,&BewLijn[k].Aantal,-1);
		if(BewLijn[k].Prijs>0 && BewLijn[k].Prijs < 0.001) prttext("<t58>Gratis");
		prtline();
	}
	if(BonHeader.Opmerking[0]){
		prtline();prtline();
		prtifld(VarTextFmt(78,0),BonHeader.Opmerking,-1);prtline();
	}
  prtform(0);
  prtclose();
  endsr:;
}

static int DisplayExtraOrderFuncties(int ordertype_)
{
	int z,k,key,used_=0,vt_,hz_;
	char choice='\0',menu_punten[10],tb_actie[11],dsp_lijn[80],dsp_str_[100];
	CString ctofile_;

	DeliveryDate=*u(25,2);
	ctofile_=CString(BonHeader.OrderFileName); ctofile_.Replace(".XML",".OK");
	FOREVER{
		scrget(3,16);z=1;
		used_=0;
		z=20;hz_=20;vt_=3;
		AddTextKey(z++,hz_,vt_,40,2,10001,"Zend bericht 'Order ontvangen'",0xFF); vt_+=2;
		AddTextKey(z++,hz_,vt_,40,2,10002,"Zend bericht 'Order geleverd/gefactureerd'",0xFF);vt_+=2;
		AddTextKey(z++,hz_,vt_,40,2,10003,"Schrap dit order",0x00FF);vt_+=2;
		key=scrupd(-1,0x7FF);
		if((key/0x10000)>0) key/=0x10000;
		switch(key){
		  case 101 : return 0; break;
			case 10001 : if(DisplayWarning("Wenst U de ontvangst van dit order te bevestigen aan Coca-Cola?",61,1)==YES) {
				             if(SendOrderOK2CCEP(BonHeader.OrderNr,999)){return 1;}
										 else DisplayWarning("Ontvangst order melden NIET gelukt!",605,0);
									 }
									 break;
			case 10002 : zero(dsp_str_,sizeof dsp_str_);
			             sprintf_s(dsp_str_,sizeof dsp_str_,"Wenst U Coca-Cola te melden dat order %s geleverd/gefactureerd is?",BonHeader.OrderNr);
									 if(AskLevDate(dsp_str_)==YES) {
										 if(SendOrderOK2CCEP(BonHeader.OrderNr,1)){return 1;} 
										 else DisplayWarning("Levering van order melden NIET gelukt!",605,0);
									 }
									 break;
			case 10003 : if(DisplayWarning("Wenst U dit order echt te schrappen?",61,1)==YES) {
										 remove(BonHeader.OrderFileName); return 1;
									 }
									 break;
			default : break;
		}
	}
	return NO;
}



static void AddBon2Doc(void)
{
	int16 n,j,k,ok_,ramj;
	char artnm_[50];
	CString cstr_;

	scrget(1,7);scrupd(-3,0);


	for(ramj=max_line-1; ramj>=0;ramj--){ram2stu(ramj); if(test_line()) break;}; 
	ramj++;
	fasinit(2);
	if(BonHeader.RecNr){
		*u(2,1)=BonHeader.RecNr;fasgeti(2);
		if(fldlen(2,80) && *s(2,80)=='\0' && BonHeader.KlantNr[0]) {copy(BonHeader.KlantNr,s(2,80),fldlen(2,80));fasupd(2);} // indien gevonden via ext_kltnr
	}
	else copy(BonHeader.Naam,s(2,3),fldlen(2,3)); 
	copy(BonHeader.OrderNr,s(8,24),fldlen(8,24));*(s(8,24)+fldlen(8,24)-1)=1;
	if(ramj>0){
		ram2stu(ramj);copy("*------------------------------",s(58,16),30);
		if(fldlen(58,62)) *s(58,62)='S'; // om sortering tegen te gaan
		stu2ram(ramj++);
	}
	ram2stu(ramj);
	cstr_=CString("*Order "); cstr_+=BonHeader.OrderNr; cstr_+=" van "; cstr_+=Date2String(BonHeader.Datum,1); copy0((char *)((LPCTSTR)cstr_),s(58,16),fldlen(58,16));
	if(fldlen(58,62)) *s(58,62)='S'; // om sortering tegen te gaan
	stu2ram(ramj++);
	ram2stu(ramj);*s(58,16)='*'; stu2ram(ramj++);

	for(n=0;n<BewCount;n++){
		ram2stu(ramj);
		if(BewLijn[n].ArtRec /* FindBewArt(n) */){
			*u(6,1)=BewLijn[n].ArtRec; fasgeti(6);
			*u(58,14)=*u(6,1); copy(s(6,2),s(58,15),fldlen(58,15)); copy(s(6,3),s(58,16),fldlen(58,16));
		}
		else{
			copy0(BewLijn[n].Naam,s(58,16),fldlen(58,16)); 
		}
    *f(58,7)=BewLijn[n].Aantal; 
		*f(58,20)=BewLijn[n].Prijs;
		stu2ram(ramj++);
		if(ramj>=max_line) break;
	}
	if(ramj<max_line){
  	ram2stu(ramj);copy("*------------------------------",s(58,16),30);
		if(fldlen(58,62)) *s(58,62)='S'; // om sortering tegen te gaan
		stu2ram(ramj++);
	}
	endsr:;
}

static int GetOrderFromSelection(char *ptitel_,char *pselection_) // result komt in SelectedFileName
{
  int z,key,len_,k,q_files,nr_,start_,lijnpos,q_,retval_,ScreenLines=17,ordertype_=0,curs;
	unsigned short funckeys;
	char str_[30],attrib_,choice='\0';
	CString cstr_,puntstr_,reply_,fname_,cselection_;
  WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
	CString cfilenames[100],cfiledates[100];
  SYSTEMTIME stUTC, stLocal;
  DWORD dwRet;
	char fm_ou3[]   = {6,0x90,3,0,0x60,0};
  char fm_uu3[]   = {6,0xD0,3,0,0x60,0};

	cselection_=CString(pselection_);
	if(cselection_.Find(".XML")>=0) ordertype_=0;
	else if(cselection_.Find(".OK")>=0) ordertype_=1;
	else if(cselection_.Find(".DONE")>=0) ordertype_=2;


	redo_find:;
	for(k=0;k<100;k++) cfilenames[k]="";q_files=0;zero(SelectedFileName,100);
	hSearch = FindFirstFile ((char *)((LPCTSTR)cselection_), &FileData);
  FOREVER{
    if (hSearch == INVALID_HANDLE_VALUE) break;
    if (!(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){                      // geen directory 
		  fname_=CString(FileData.cFileName);
			if(fname_.GetAt(0)=='~') goto nextfile; // werkfiles xls/word skippen
			cfilenames[q_files]=fname_;
// Convert the last-write time to local time.
			FileTimeToSystemTime(&FileData.ftLastWriteTime, &stUTC);
      SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    // Build a string showing the date and time.
      sprintf_s(str_, sizeof str_,"%02d/%02d/%d  %02d:%02d", stLocal.wDay, stLocal.wMonth, stLocal.wYear,stLocal.wHour, stLocal.wMinute);
			cfiledates[q_files]=CString(str_);
			q_files++;
		}
		if(q_files>=100) break;
		nextfile:;
    if(FindNextFile (hSearch, &FileData)==false) break;
  }
  FindClose(hSearch);
  retval_=0;

  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
    scrget(3,17);z=1;q_=0; funckeys=0x80E1;
		scraddpicto(40,0,76,22,4,2,106,0,4,"Wijzig");
		scraddpicto(41,0,72,0,8,4,45,0,4,"Controleer op nieuwe orders");
    for(len_=0;len_<79;len_++) if(ptitel_[len_]=='\0') break;
	  scraddfield(200,(80-len_)/2,0,0xA);scrifld(200,VarTextFmt(len_,0),ptitel_); 
		scrifld(z++,VarTextFmt(15,0),OrderStatusTxt[ordertype_]); if(TestApiMode) scrchat(z-1,0x07);
		if(q_files){
  	  start_++;scrifld(z++,fm_ou2,&start_);start_--;scrifld(z++,fm_ou2,&q_files);
		} else z+=2;
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=q_files) break;
	    k++;scrifld(z++,fm_ou3,&k);k--;
	    scrifld(z++,VarTextFmt(48,0),(char *)(LPCTSTR)cfilenames[k]);
			scrifld(z++,VarTextFmt(17,0),(char *)(LPCTSTR)cfiledates[k]);
			scraddpicto(1+k-start_,z-1,0,0,2,1,102,0,4,"Selecteer"); 
			scraddpicto(1+ScreenLines+k-start_,z-1,3,0,2,1,45,0,4,"Download"); 
			if(ordertype_==2) scraddpicto(1+ScreenLines*2+k-start_,z-1,5,0,2,1,133,0,3,"Schrap"); 
    }
    key=scrupd(-1,0xA87);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		retval_=0;zero(SelectedFileName,100);
		if(key==5040){
			ordertype_++; if(ordertype_>2) ordertype_=0;
			if(ordertype_==0) cselection_.Replace(".DONE",".XML");
			if(ordertype_==1) cselection_.Replace(".XML",".OK");  
			if(ordertype_==2) cselection_.Replace(".OK",".DONE"); 
			goto redo_find;
		}
		if(key==5041){
			GetOrdersFromCCEP();
			ordertype_=0;
			goto redo_find;
		}

		if(key>=5001 && key<5001+ScreenLines){
			retval_=key-5001+start_;
			cstr_=CString(pselection_);k=cstr_.ReverseFind('\\');
			if(k<0) k=cstr_.ReverseFind(':');
			if(k>0) cstr_=cstr_.Left(k+1); else cstr_=CString("");
			cstr_+=cfilenames[retval_];
			copy((char *)(LPCTSTR)cstr_,SelectedFileName,cstr_.GetLength());
  	  if(ReadCCEPXml(SelectedFileName)){
				if(DisplayLeverData(SelectedFileName,ordertype_)) {retval_=1;	goto end;}
				goto redo_find;
			}
		}
		if(key>=5001+ScreenLines && key<5001+ScreenLines*2){
			retval_=key-5001-ScreenLines+start_;
			cstr_=CString(pselection_);k=cstr_.ReverseFind('\\');
			if(k<0) k=cstr_.ReverseFind(':');
			if(k>0) cstr_=cstr_.Left(k+1);cstr_+=cfilenames[retval_];
			copy((char *)(LPCTSTR)cstr_,SelectedFileName,cstr_.GetLength());
	    GetFileFromServer(SelectedFileName);			
			goto redo_find;
		}
		if(key>=5001+ScreenLines*2 && key<5001+ScreenLines*3){
			retval_=key-5001-ScreenLines*2+start_;
			cstr_.Format("Wenst u echt \"%s\" te SCHRAPPEN?",cfilenames[retval_]);
			if(DisplayWarning((char *)(LPCTSTR)cstr_,605,1)==YES){
 				cstr_=CString(pselection_);k=cstr_.ReverseFind('\\');
				if(k<0) k=cstr_.ReverseFind(':');
				if(k>0) cstr_=cstr_.Left(k+1);cstr_+=cfilenames[retval_];
				copy((char *)(LPCTSTR)cstr_,SelectedFileName,cstr_.GetLength());
	      remove(SelectedFileName);			
		  	goto redo_find;
			}
		}
    switch(key){
			case 12      :// PgUp 
	//		case 5001    :
			case 102     : if(start_>0){
											 start_-=ScreenLines; if(start_<0) start_=0;lijnpos=0;scrnum=0;
										 }
										 break;
			case 13      :// PgDn 
	//		case 5002      :// PgDn 
			case 103     : if((start_+ScreenLines)<q_files) {start_+=ScreenLines;lijnpos=0;scrnum=0;}
										 break;
			case 101     :
			case 106     : goto end;// annuleer 
										 break;
			case 18      :// ENTER 
			case 15      : // TAB  
			case 108     : if(nr_<1 || nr_>q_files) errnum=34;// neem aan en exit 
										 else{
											 retval_=nr_-1;
											 cstr_=CString(pselection_);k=cstr_.ReverseFind('\\');
											 if(k<0) k=cstr_.ReverseFind(':');
											 if(k>0) cstr_=cstr_.Left(k+1);cstr_+=cfilenames[retval_];
											 copy((char *)(LPCTSTR)cstr_,SelectedFileName,cstr_.GetLength());
											 retval_=1;
											 goto end;
										 }
										 break;
			case 110     : UpdateSettings(); break;
			case 112     : if(TestApiMode) TestApiMode=NO; else TestApiMode=YES; break;
			default      : break;
    }
	}
	end:;
	return retval_;
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


static int AskLevDate(char *ptxt) 

{
  int16 key,color_,k,icoon=61;
  int len_,beg_;
	char dsptekst_[100];
   

  zero(dsptekst_,sizeof dsptekst_);dsptekst_[0]=' ';
	for(len_=0;len_<80;len_++){
		if(ptxt[len_]=='\0') break;
		dsptekst_[len_+1]=ptxt[len_];
	}
	len_+=1;dsptekst_[len_++]=' ';if(len_>80) len_=80;
	beg_=(80-len_)/2; if(beg_<1) beg_=1; 
	FOREVER{
		redo:;
		color_=0; if(icoon<500) color_=3;
		scrnum=0; scrget(1,170);
		scraddf(100,23,0,8); scrifld(100,VarTextFmt(7,0)," F4 Ja ");
		scraddf(101,23,8,8); scrifld(101,VarTextFmt(8,0)," F5 Nee ");

		if(icoon) scraddpicto(1,0,32,1,12,6,icoon,0,color_,"Opgelet!"); 
		scraddfield(200,beg_,12,0x2);scrifld(200,VarTextFmt(len_,0),dsptekst_);
		scraddfield(201,4,16,0x2);scrifld(201,VarTextFmt(80,0),"Datum levering: ");
		scraddfield(202,20,16,0x2);scrifld(202,fm_udat,&DeliveryDate);
	redo_upd:;
		key=scrupd(202,0x18);
		if(key==105) return NO;
		if(DeliveryDate==0){errnum=38; goto redo;}
		if(key==104){scrget(1,7);scrupd(-3,0);break;}
	}
	return YES;
}

static void UpdateSettings(void)
{
  int curs,z,key;
  char lev_prod_;

	sysget(8326,10,Settings.KlantNummer);
	sysget(8336,2,(char *)&Settings.RecLeverancier);
	sysget(8400,50,Settings.API_key);
	// sysget(8260,60,Settings.EmailAdres);
//	sysget(8322,2,(char *)&Settings.EindDatumLastExport);
	fasinit(1);
	lev_prod_='L'; *u(1,1)=Settings.RecLeverancier;
	if(*u(1,1)>30000){lev_prod_='P';*u(1,1)=*u(1,1)-30000;}
	if(*u(1,1)) fasgeti(1);

	curs=1;
  FOREVER {
		redo:; 
    scrnum=0;scrget(3,18);z=1;
		scraddpicto(1,0,1,22,4,2,595,0,0,"annuleer"); scraddpicto(2,0,7,22,4,2,578,0,0,"OK"); scraddpicto(7,0,13,22,4,2,107,0,4,"Herdisplay"); 
//		scrifld(z++,fm_us55,Settings.EmailAdres);
		scrifld(z++,fm_us10,Settings.KlantNummer);
		scrifld(z++,fm_uLP,&lev_prod_);
		scrfld(z++,1,3);
		scrifld(z++,fm_us50,Settings.API_key);
    key=scrupd(curs,0x2A0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106 || key==5001) goto endsr;
//		if(CheckEmailAdres(Settings.EmailAdres,60,0)==NO){errnum=34;curs=1; goto redo;}
		if(Search(1,0)){curs=3; goto redo;}; // moet ingevuld zijn
    if(key==108 || key==5002) break;
  }
	if(lev_prod_=='P' && *u(1,1)) *u(1,1)+=30000;
	Settings.RecLeverancier=*u(1,1);
	sysput(8326,10,Settings.KlantNummer);
	sysput(8336,2,(char *)&Settings.RecLeverancier);
	sysput(8400,50,Settings.API_key);
//	sysput(8260,60,Settings.EmailAdres);
	pLevFld=u(6,7); InqLev=Settings.RecLeverancier;
	if(fldlen(6,101) && InqLev>30000){pLevFld=u(6,101);InqLev-=30000;} // merk/producent
endsr:;
	sysget(8326,10,Settings.KlantNummer);
	sysget(8336,2,(char *)&Settings.RecLeverancier);
	sysget(8400,50,Settings.API_key);
	pLevFld=u(6,7); InqLev=Settings.RecLeverancier;
	if(fldlen(6,101) && InqLev>30000){pLevFld=u(6,101);InqLev-=30000;} // merk/producent
}

static int KoppelKlant(void) // zoek/koppel CCEP-klant, bij DoSelect_ YES, altijd laten selecteren
{
	int16 k,z,key,curs=1,smode_;
	char oldnm_[50];
	CString cstr_;

	fasinit(2); memset(oldnm_,0,sizeof oldnm_);
	if(BonHeader.RecNr){
		*u(2,1)=BonHeader.RecNr;fasgeti(2);
		copy(s(2,3),oldnm_,sizeof oldnm_);
	}
	else{
	  for(k=0;k<fldlen(2,3);k++) if(BonHeader.Naam[k]==' ' || BonHeader.Naam[k]=='\0') break;
	  cstr_=CString(BonHeader.Naam,k);cstr_.Trim(); cstr_.MakeUpper();k=cstr_.GetLength();
	  copy((char *)(LPCTSTR)cstr_,s(2,3),k);		
	}
	FOREVER{
		redo:;
		scrnum=0;scrget(3,15); z=1;
		scrifld(z++,VarTextFmt(10,0),BonHeader.KlantNr);
		scrifld(z++,VarTextFmt(40,0),BonHeader.Naam);
		scrifld(z++,VarTextFmt(40,0),BonHeader.Adres);
		scrifld(z++,VarTextFmt(7,0),BonHeader.Postcode);scrifld(z++,VarTextFmt(30,0),BonHeader.Gemeente);
		scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		key=scrupd(1,0x2E0);
		if(key==106){
			fasinit(2);
			if(BonHeader.RecNr){*u(2,1)=BonHeader.RecNr;fasgeti(2);}
			return NO;
		}
		if(key==110){
			fasinit(2);
			copy(BonHeader.Naam,s(2,3),fldlen(2,3));
			copy(BonHeader.Adres,s(2,4),fldlen(2,4));
			copy(BonHeader.Postcode,s(2,5),fldlen(2,5));
			copy(BonHeader.Gemeente,s(2,6),fldlen(2,6));
			copy(BonHeader.KlantNr,s(2,80),fldlen(2,80));
			*s(2,26)='0';
			if(ovlcall(2921,2)){BonHeader.RecNr=*u(2,1); break;}
		}
		if(*s(2,3)=='\0' || cmpstr(s(2,3),oldnm_,fldlen(2,3))){
			smode_=98; if((*s(2,3)>='0' && *s(2,3)<='9') || *s(2,3)=='?' || *s(2,3)=='.') smode_=0;
			if(Search(2,smode_)) goto redo;
		}
		if(key==108){
			copy(BonHeader.KlantNr,s(2,80),fldlen(2,80)); BonHeader.RecNr=*u(2,1);fasupd(2);
			break;
		}

	}
	return YES;
}

static int KoppelArtikel(int listnr_,int DoSelect_) // zoek/koppel CCEP-artikel, bij DoSelect_ YES, altijd laten selecteren
{
	int16 k,q_,n,z,key,curs=6,start_,mode6_,mode11_,found_=NO,retval_=0,MaxScrLines=12;
	uint16 nr_,orig_rec11=0,orig_rec6=0;
	int kleur_;
	char SearchText[50],lijn_attrib_,buf_[50];
	CString cstr_;


	fasinit(1);*u(1,1)=RecCCEP; fasgeti(1);
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
		listnr_++;scrifld(z++,fm_ou5,&listnr_);listnr_--;scrifld(z++,fm_ou5,&BewCount);
		scrifld(z++,VarTextFmt(10,0),BewLijn[listnr_].Code);
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
//		if(CheckInhoud(listnr_)==NO)  goto redo_listnr;
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
			if(*s(11,5)=='\0') {found_=YES;break;} // rec11 zonder code 
		}
		if(found_){
			copy(BewLijn[listnr_].Code,s(11,5),fldlen(11,5));
			if(fldlen(11,68)) *f(11,68)=BewLijn[listnr_].AfwijkendAantal;
			errnum=fasupd(11);
		}
		else{
			fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);
			copy(BewLijn[listnr_].Code,s(11,5),fldlen(11,5));
			if(fldlen(11,68)) *f(11,68)=BewLijn[listnr_].AfwijkendAantal;
			errnum=fasadd(11);
		}
//			if(*f(6,37)<=0) *f(6,37)=BewLijn[listnr_].inhoud;
//			if(*f(6,38)<=0) *f(6,38)=BewLijn[listnr_].gewicht;
		if(*s(6,70)=='\0' && cmpstr(BewLijn[listnr_].EAN,s(6,71),fldlen(6,71))) copy(BewLijn[listnr_].EAN,s(6,70),fldlen(6,70));
		else if(*s(6,71)=='\0' && cmpstr(BewLijn[listnr_].EAN,s(6,70),fldlen(6,70))) copy(BewLijn[listnr_].EAN,s(6,71),fldlen(6,71));
		fasupd(6);
		BewLijn[listnr_].ArtRec=*u(6,1);
		if(BewLijn[listnr_].Naam[0]=='\0') copy(s(6,3),BewLijn[listnr_].Naam,fldlen(6,3)); // geen naam meegegeven, dus art.naam maar invullen
		BewLijn[listnr_].ArtInhoud=*f(6,37);
		BewLijn[listnr_].ArtAantalBak=*f(6,31);
		float factor_=1.; if(BewLijn[listnr_].AfwijkendAantal && BewLijn[listnr_].ArtAantalBak) factor_= BewLijn[listnr_].AfwijkendAantal/ BewLijn[listnr_].ArtAantalBak;
//		BewLijn[listnr_].ArtLevAKprijs=BewLijn[listnr_].ArtAKprijs*factor_;
		return YES;
	}
endsr:;
	return NO;
}

static int16 FindBewArt(int16 nr_) // zoek artikel op referentie leverancier of EAN
{
	int16 codelen_;

	codelen_=sizeof BewLijn[0].Code; if(codelen_>fldlen(11,5)) codelen_=fldlen(11,5);
	fasinit(11);*u(11,2)=*u(1,1); fasinit(6);
	FOREVER{
		if(faskeyi(11,1,2)) break; 
		if(*u(11,2)!=*u(1,1)) break;
		if(NettoCompareStr(BewLijn[nr_].Code,s(11,5),codelen_)==0){*u(6,1)=*u(11,3);fasgeti(6); return YES;}
	}
	if(BewLijn[nr_].EAN[0]){
		if(fldlen(64,1)){ // eerst zoeken in extra barcodes
			fasinit(64); copy(BewLijn[nr_].EAN,s(64,2),fldlen(64,2));
			if(faskeyi(64,1,0)==0){
				fasinit(6);*u(6,1)=*u(64,3); fasgeti(6);
				return YES;
			}
		}

		fasinit(6);*u(6,7)=*u(1,1);
		FOREVER{
			if(faskeyi(6,4,2)) break; 
			if(*u(6,7)!=*u(1,1)) break;
			if(cmpstr(BewLijn[nr_].EAN,s(6,70),fldlen(6,70))==0) return YES;
			if(cmpstr(BewLijn[nr_].EAN,s(6,71),fldlen(6,71))==0) return YES;

		}
	}
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

static CString Date2String(unsigned int date_,int mode_)
{
   char txtbuffer_[100];

   zeros(txtbuffer_,sizeof txtbuffer_);
   if(date_) datefm(txtbuffer_,date_,mode_);

   return CString(txtbuffer_);
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
  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);
  sysget(294,4,def_munt);
  sysget(1048,32,&btw_pct[0]);
	sysget(1084,4,&def_btw);
  sysget(2982,2,&sys2982);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,sys3896);
  sysget(3142,50,MapBestelling); 

	sysget(8326,10,Settings.KlantNummer);
	sysget(8336,2,(char *)&Settings.RecLeverancier);
	//sysget(8260,60,Settings.EmailAdres);
	sysget(8338,2,(char *)&Settings.LastMaand); 
	sysget(8400,50,Settings.API_key);
	pLevFld=u(6,7); RecCCEP=Settings.RecLeverancier;
	if(fldlen(6,101) && RecCCEP>30000){pLevFld=u(6,101);RecCCEP-=30000;} // merk/producent

	ram=RamBon;
	ram_size=125000;
	if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;
	// ZEKER NIET HIER	zeroL(ram,ram_size);
	stu58_len=fldlen(58,0);max_line=ram_size/stu58_len;
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