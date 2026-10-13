
/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "Shlobj.h"
#include <direct.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

extern "C" char* DRK2240GetD() {return &zzvw;}

extern "C" void SvcErr(int nr, char *text);
extern "C" void CnvJamaChar(char *pString,int16 MaxLen,int16 CnvMode);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" int Fld2String(int stunr, int fldnr, char *OutBuffer, int MaxLen);
extern "C" void MakeStructMed(char *pd, uint16 refnr_); // 'kkk/kkff/fffcc'   K(lant) F(aktnr) C(heck) 
extern "C" int CodaBoxShowLicence(char *Licence);
extern "C" int CodaBoxCheckVAT(long *BtwNrBE, char *BtwEU); // BtwEU wordt voorlopig niet gebruikt (22/10/20)
extern "C" int CodaBoxCheckGLN(char* glnNr); // Check of GLN Peppol kan ontvangen
extern "C" int CodaBoxCheckStatus(char *Licence, char *RefCodaBox, char *CNflag, int DisplayError);
extern "C" int JsonToXml(char *Outputbuf, int MaxOutputbufLen, char *JsonString);
extern "C" int IbanTools(char *pIBAN,char *pBIC,char *pJamaRek,int16 ToolNr); // 0 = check iban/bic, 1=check+fill bic, 2=convert jamarek -> IBAN/BIC
extern "C" char *VarTextFmt(int len_,int update_);
extern "C" int SendMail(int send_mode);
extern "C" const char* PeppolSendDocument(char btwNr[21], char cnFlag[4], char fileName[71]);
extern "C" const char* PeppolGetDocumentStatus(char documentId[51], char cnFlag[4], int DisplayError);

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

// Historiek:
// 11/07/19 : aanpassing ivm BIS3 update 25/6/19 (endpoint)

      // FLAGSAS : YUKI-formaat 


extern "C" char DRK2240dat[] = "drk2240  00:01 22/10/20 (c) Jamadata"; // module om factuur uit te schrijven/versturen via CodaBox in UBL-formaat (eFFF of Peppol) 
                                                                       // testen kan via https://ecosio.com/en/peppol-and-xml-document-validator/

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DIM8            100
#define DIM58           800
#define DIM_EU          27/* excl. Belgie */
#define EL_BKH          80
#define DF_GRB          15
#define OPMLEN          20
#define BTWDIV          2
#define BTWDIM          8+BTWDIV
#define flag            uint16
#define BEDRAG          double

extern char *s();
extern int16 *i();
extern float *f();
extern uint16 *u();
extern long *l();
extern double *d(),valu_cnv();
extern int16 retcall,parmcall[8];


extern char SelectedFileName[];
extern char RamBon[];
extern int RamBonSize;
#include "par0240.c"

// h-file --------------------------------

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us62[]  = {7,0xC8,62,0,0,0,0};
static char fm_os56[]  = {7,0x88,56,0,0,0,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};

static void CalcFactuur(void);
// static void ExportFactuur2XML(void); // UBL-formaat
static void ExportFactuur2Peppol(void); // UBL-Peppol-formaat
static void InvLine2Xml(int lgmode_, int cn_flag_);
static void InvLine2PeppolXml(int lgmode_, int cn_flag_); // peppol
static void InitLoad(void);
static void InitConvertTab(void);  // komt uit JMS
static int LoadFactuur(char *ftfile_);// laden factuur van FtKopie  
static int SendDoc2Boekhouder(void); // UBL versturen naar extern boekhoudpakket
static int SendDoc2Peppol(); // UBL versturen naar Peppol

static void ram2stu(int16 lin_);
static void stu2ram(int16 lin_);
static void init58(int16 start_,int16 mode_);
static int test_line(void);
static int16 btw_tab(double bd_);
static BEDRAG round(double value_);

static CString arr2cstr(char *ps, int max_len);
static int copy0(char *ps_, char *pd_, int maxlen_);
static CString Bedrag2Cstring(double bd_, int decimals_);
static void Double2Text(double getal, char *s, int len, char points, int digits);
static void fileopen(int16 nr_);
static int FileExist(char *FileName);
static int is_nul(double bd_);
static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_);
static CString Date2String(unsigned int date_,int mode_);
static double Round(double getal, double round);
static double str2dbl(char *s);
static double str2dbl(CString cstr) {return str2dbl((char *)(LPCTSTR)cstr);};
static CString Fld2CString(int stu_,int fld_);

static unsigned char GetStringBuf[500]; // zie hieronder
static char* GetString(int stunr, int fldnr, bool JamasciDecodeFlag=false, int MaxLen=500);


static CMarkup InvXml,KassaXml;
   
static bool ReadEOFline,SilentMode;
static char *ram,def_inc,def_ext[2],fmt[40],OutputMapUbl[51],UidCodaBox[41],PwCodaBox[15],LicIDCodaBox[41],CodaBoxFileName[70];
static char btw_CategorieUsed[BTWDIM],PeppolUidOUT[40],PeppolPwOUT[15],PeppolLicOUT[60],PeppolFirmaNaam[50];
static long ram_size,firmbtwnr;
static int16 stu58_len,max_line,def_qfact,lvcd,klcd,prxnr,journl;
static uint16 ft_date,ft_nr,sys3894,btw_kol,verv_dt,disk_dt,KlantIDViaBtwNr,RecLevKostArt;
static int LastKrtNr,  InvLineNr,PeppolProviderOUT,FactuurMetCorrectie;
static char ICSBTab[256],ft_munt[3];
static flag  disk_ei;
static float tot_kort,tot_leeg,winst_pc,tot_gewicht;
static float def_btw,btw_glob,btw_pct[BTWDIM],max_btw,BtwLeveringskost;
static BEDRAG alg_tot,belastbt,btw_tot,btw_bas[BTWDIM],incl_bas[BTWDIM],disk_bd,kredietbp_bd,tot_subs;
static BEDRAG btw_bd[BTWDIM],semestbd,winst_bd,v_alg_tot,tot_promo,kort_btw[BTWDIM];
static double ealg_tot,ft_afrond,prx_afrond,klt_saldo,tot_accijns,tot_AKWgoed,KM_heffing;
static double omzet,osalkas,tot_voors,trans_kost,BdFactuurAfronding;
static char sortbuf[1000],def_munt[4],firma[350],buf1000[1000],ExtraBijlageFactuurmail[50];
static int16 b2228,b3604,b3606;

static int16 len2_14,len58_25,len58_15,len58_35,len8_23,len58_62,len2_3,len6_3;
static char *ps_2_3,*ps_58_15,*ps_58_16,*ps_58_25,*ps_8_23,*ps_58_62,*ps_6_3;
static uint16 *pu_8_28,*pu_2_1,*pu_58_1,*pu_6_1,*pu_58_14;
static float *pf_58_24;
static float *pf_58_20,*pf_58_21,*pf_58_31,calc_sem,calc_kort,calc_prx,calc_kfr;
static double *pd_58_35;
static long kltcent,grb_notf;
static char talen[4];
static uint16 rec_nr[EL_BKH],df_recnr[DF_GRB];
static long grb_tb[EL_BKH];
static BEDRAG bedrag[EL_BKH];
static char df_rek[DF_GRB][4];

#if FLAGALS
static float hk_pct[2][2];
static long hk_omzgrb[8],hk_kostgrb[2];
#endif

static struct{
  uint16 ft_nr;
  uint16 ft_date;
  uint16 stu8len;
  uint16 stu58len;
  double alg_tot;
  double belastbt;
  double btw_tot;
  double tot_leeg;
  char opm_foot[4][75];
  int16 stu8[200][2];
  int16 stu58[200][2];
} ft_stu;


static char *eu_land[DIM_EU]={"BG","CY","DK","DE","EE","FI","FR","EL","GB","HU","IE","IT","LV","LT","LU",
		       "MT","NL","AT","PL","PT","RO","SI","SK","ES","CZ","SE","HR"};
static int eu_agency[DIM_EU]={9926,9928,96,9930,9931,0,9957,9933,9932,9910,9935,97,9939,9937,9938,
		       9943,9944,9914,9945,9946,9947,9949,9950,9920,9929,9955,9935};

static unsigned char jamasci[80][2] = {
{ 225,   0},/* 128 */
{ 224,   0},
{ 226,   0},
{ 228,   0},
{ 231,   0},
{ 233,   0},
{ 232,   0},
{ 234,   0},
{ 235,   0},
{ 237,   0},
{ 236,   0},
{ 238,   0},
{ 239,   0},
{ 243,   0},
{ 242,   0},
{ 244,   0},
{ 246,   0},/* 144 */
{ 250,   0},
{ 249,   0},
{ 251,   0},
{ 252,   0},
{ 220,   0},
{ 176,   0},
{ 167,   0},
{ 190,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 128,   0},
{ 126,   1},/* 160 */
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 178,   1},/* 192 */
{ 186,   1},
{ 205,   1},
{ 200,   1},
{ 186,   1},
{ 186,   1},
{ 201,   1},
{ 204,   1},
{ 205,   1},
{ 188,   1},
{ 205,   1},
{ 202,   1},
{ 187,   1},
{ 185,   1},
{ 203,   1},
{ 206,   1},
{ 178,   1},/* 192 */
{ 179,   1},
{ 196,   1},
{ 192,   1},
{ 179,   1},
{ 179,   1},
{ 218,   1},
{ 195,   1},
{ 196,   1},
{ 217,   1},
{ 196,   1},
{ 193,   1},
{ 191,   1},
{ 180,   1},
{ 194,   1},
{ 197,   1}
};


extern "C" void DRK2240cod(int16 parmval) // 0=xml uitschrijven, 1=xml uitschrijven ahv ftkopie, 10=factuur verzenden, 11=mailen naar extern BKH-pakket
																					//	20=btwr checken, 21=status factuur opvragen, 99=eigen licentie tonen
{
	CMarkup Xml;
	int Status,ret_;
	int16 GEENdebug_;
	CString cstr_;
	CFile cfile_;

	// indien mailen naar online BKH-pakket: op 6500 mailadres zetten en EXBKH.eml meegeven uit MST en in templates zetten


	InitLoad();
	sysget(1284, 2, &GEENdebug_);
	KL_Stu2240=2; if(SelfBilling) KL_Stu2240=1;
	if(parmval==20) { // check BTW-nummer
		retcall=0;
		if (*l(KL_Stu2240,10)==999999999 || *l(KL_Stu2240,10)==0){
			if (fldlen(KL_Stu2240,137) && *s(KL_Stu2240,137)) retcall = CodaBoxCheckGLN(s(KL_Stu2240, 137));
			else errnum=29;
		}
		else {
			retcall = CodaBoxCheckVAT(l(KL_Stu2240,10), ""); // eerst proberen via KBO
			if (retcall < 1){
				retcall = CodaBoxCheckVAT(l(KL_Stu2240,10),"BE");
			}
		}
		ovlexit(-1);
	}

	if(parmval==21) { // check status van verzonden factuur 
		if(*(s(8,76)+49)==1) retcall=CodaBoxCheckStatus(LicIDCodaBox,s(8,76),"YES",YES); // op pos 49 CN of niet
		else retcall=CodaBoxCheckStatus(LicIDCodaBox,s(8,76),"NO",YES);
		//		retcall=CodaBoxCheckStatus(LicIDCodaBox,s(8,76)); 
		ovlexit(-1);
	}

	if(parmval==99) { // toon eigen gegevens ahv licentie
		retcall=CodaBoxShowLicence(LicIDCodaBox); 
		ovlexit(-1);
	}


	if(parmval==1){ // eerst factuur laden van FtKopie
		if(LoadFactuur(SelectedFileName)==NO){retcall=0; ovlexit(-1);}
	}
	if(fldlen(8,23)) copy(s(8,23),ft_munt,3);
	if(ft_munt[0]=='\0') copy(def_munt,ft_munt,3);
	CalcFactuur();
#if FLAGDEW
	if(*i(8,36)) SelfBilling=YES;
#endif
	KlantIDViaBtwNr=NO; // default via KBO
	if(parmval==10){
#if _DEBUG || FLAGDEM
    	if(GEENdebug_) ret_=0;
			else {ret_=1; goto no_controle;}
#else
	    ret_ = 0;
#endif
		ret_=0;
		if (*l(KL_Stu2240,10)==999999999 || *l(KL_Stu2240,10)==0){
			if (fldlen(KL_Stu2240,137) && *s(KL_Stu2240,137)) ret_ = CodaBoxCheckGLN(s(KL_Stu2240, 137));
			else errnum=29;
		}
		else {
			ret_ = CodaBoxCheckVAT(l(KL_Stu2240,10), ""); // eerst proberen via KBO
			if (ret_ < 1){
				ret_ = CodaBoxCheckVAT(l(KL_Stu2240,10),"BE");
  			KlantIDViaBtwNr=YES;
			}
		}


		//else {
		//	ret_=CodaBoxCheckVAT(l(KL_Stu2240,10),""); // Eerst op KBO-nr     BtwEU wordt voorlopig niet gebruikt (22/10/20)
		//	if(ret_<1){ KlantIDViaBtwNr=YES; ret_=CodaBoxCheckVAT(l(KL_Stu2240,10),"BE");} // daarna op BTW#
		//}
		no_controle:;
		if (ret_ != 1) {
			retcall = 0;
//			errnum = 29;
			ovlexit(-1);
		}
	}

	ExportFactuur2Peppol();	if(CodaboxUniqueID[0]=='\0') {retcall=0;ovlexit(-1);} // niet goed kunnen uitschrijven
	
	retcall=1;

	if (parmval == 10) {

#if _DEBUG
		if (UidCodaBox[0] != '!') {
			if (DisplayWarning("DEBUG MODE! Deze factuur in TESTomgeving versturen?", 61, 1) == NO) {
				if (DisplayWarning("Deze factuur toch als ECHTE factuur versturen? DEBUG MODE!", 61, 1) == NO) {
					retcall = 0;
					ovlexit(-1);
				}
			}
		}
#endif

		scrnum = 0;
		scrget(1,170); 
		scrifld(5, fm_os63, "Bezig met factuur te versturen via peppol...");
		scrupd(-3,0);
		retcall = SendDoc2Peppol();
	}

	if (parmval == 11) {

#if _DEBUG
  	if (DisplayWarning("DEBUG MODE! Deze factuur in TESTomgeving versturen?", 61, 1) == NO) {
	  	retcall = 0;
		  ovlexit(-1);
		}
#endif

		scrnum = 0;
		scrget(1,170); 
		scrifld(5, fm_os63, "Bezig met factuur te mailen naar boekhouder...");
		scrupd(-3,0);
		retcall = SendDoc2Boekhouder();
	}

	ovlexit(-1);
}

static int LoadFactuur(char *ftfile_)// laden factuur van FtKopie
{
  int16 j,k,len_,pos_,len1_;
	CFile cfile_;
	 
	if(cfile_.Open(ftfile_,CFile::modeRead,0)==0) return NO;
	cfile_.Seek(0L,CFile::begin);zero((char *)&ft_stu.ft_nr,sizeof ft_stu);
	if(cfile_.Read((char *)&ft_stu.ft_nr,sizeof ft_stu)!=sizeof ft_stu){
		cfile_.Close(); return NO;
	}
  ft_nr=ft_stu.ft_nr;ft_date=ft_stu.ft_date;

	if(cfile_.Read(sortbuf,ft_stu.stu8len)<ft_stu.stu8len){cfile_.Close(); return NO;}
  pos_=0;
  for(k=0;k<200;k++){
    len_=fldlen(8,k+1);
    len1_=ft_stu.stu8[k][0];
    if(len_){
      if(len1_){
				if(len1_<len_) len_=len1_;
				copy(&sortbuf[pos_],s(8,k+1),len_);
      }
    }
    pos_+=len1_;
  }
  for(j=0;j<max_line;j++){
    ram2stu(j);
    if(cfile_.Read(sortbuf,ft_stu.stu58len)<ft_stu.stu58len) break;
    pos_=0;
    for(k=0;k<200;k++){
      len_=fldlen(58,k+1);
      len1_=ft_stu.stu58[k][0];
      if(len_){
				if(len1_){
					if(len1_<len_) len_=len1_;
					copy(&sortbuf[pos_],s(58,k+1),len_);
				}
      }
      pos_+=len1_;
    }
    stu2ram(j);
  }
  endsr:;
  *pu_2_1=*u(8,3);fasgeti(2);
	cfile_.Close();
  fasflush(0);
  return YES;
}

static void ExportFactuur2Peppol(void) // UBL-Peppol-formaat
{
  CMarkup Klt;
  int j,k,lgmode_,cn_flag_;
	double bd_,factor_,tot_lgpl_,bd_betaald_,tot_0pct_;
	long lbd_,btwnr_;
	short mm,dd,jaartal;
	char sys3896[6],str_[100],kar_;
  unsigned char *p=0;
  CString PdfName,cstr_,strBase64,cstr1_;
	CFile cfile_;

	scrnum=0;scrget(1,7);scrifld(1,VarTextFmt(26,0),"Aanmaken peppoldocument...");scrupd(-3,0);

	if(*s(8,25)=='\0'){
		if(SelfBilling) sprintf_s(s(8,25),fldlen(8,25), "%s-%05d","SB-Peppol",ft_nr);
		else sprintf_s(s(8,25),fldlen(8,25), "%s-%05d","Peppol",ft_nr);
	}
	zero(CodaBoxFileName,sizeof CodaBoxFileName);
	cn_flag_=NO; factor_=1.0; if(alg_tot /* belastbt*/<0){cn_flag_=YES; factor_=-1.0;}
	bd_betaald_=0; 
	if(!cn_flag_){
		if(*s(8,22)=='J') bd_betaald_=alg_tot;
		else if(fldlen(8,21) && *f(8,21)) bd_betaald_=*f(8,21);
	}

	InvXml = CMarkup(); // uit veiligheid om te clearen na lange factuur
	InvXml = CMarkup("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\x0D\x0A");
  if(cn_flag_) InvXml.AddElem("CreditNote"); else		InvXml.AddElem("Invoice");
	InvXml.SetAttrib("xmlns:cac","urn:oasis:names:specification:ubl:schema:xsd:CommonAggregateComponents-2");	
	InvXml.SetAttrib("xmlns:cbc","urn:oasis:names:specification:ubl:schema:xsd:CommonBasicComponents-2");	
  if(cn_flag_){
	  InvXml.SetAttrib("xmlns","urn:oasis:names:specification:ubl:schema:xsd:CreditNote-2");
	}
	else{
		InvXml.SetAttrib("xmlns","urn:oasis:names:specification:ubl:schema:xsd:Invoice-2");
	}	

	InvXml.IntoElem();
	  if(SelfBilling){
			InvXml.AddElem("cbc:CustomizationID","urn:cen.eu:en16931:2017#compliant#urn:fdc:peppol.eu:2017:poacc:selfbilling:3.0");
			InvXml.AddElem("cbc:ProfileID","urn:fdc:peppol.eu:2017:poacc:selfbilling:01:1.0");
		}

		else if(cn_flag_){
		  InvXml.AddElem("cbc:CustomizationID","urn:cen.eu:en16931:2017#compliant#urn:fdc:peppol.eu:2017:poacc:billing:3.0");
			InvXml.AddElem("cbc:ProfileID","urn:fdc:peppol.eu:2017:poacc:billing:01:1.0");
		}
		else{
		  InvXml.AddElem("cbc:CustomizationID","urn:cen.eu:en16931:2017#compliant#urn:fdc:peppol.eu:2017:poacc:billing:3.0");
			InvXml.AddElem("cbc:ProfileID","urn:fdc:peppol.eu:2017:poacc:billing:01:1.0");
		}
		
    jddate(ft_date,&jaartal,&mm,&dd);// factuurdatum
  	cstr_.Format("%d-%05d",jaartal,ft_nr); InvXml.AddElem("cbc:ID",cstr_);
		cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:IssueDate",cstr_);
		if(cn_flag_==NO && (alg_tot-bd_betaald_)>0.006){
			jddate(verv_dt,&jaartal,&mm,&dd); cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:DueDate",cstr_);
		}
		if(SelfBilling){
			if(cn_flag_) InvXml.AddElem("cbc:CreditNoteTypeCode",396);	else InvXml.AddElem("cbc:InvoiceTypeCode",389);	// selfbilling
			InvXml.AddElem("cbc:DocumentCurrencyCode","EUR");	// InvXml.SetAttrib("listID","ISO4217");
			cstr_.Format("SELF-BILLING-%04d",jaartal);
			InvXml.AddElem("cbc:BuyerReference",cstr_);
//			InvXml.AddElem("cbc:Note","Factuur uitgereikt door de afnemer");
			//InvXml.AddElem("cac:ContractDocumentReference");InvXml.IntoElem();
			//  cstr_.Format("SELF-BILLING-%04d",jaartal);
			//  InvXml.AddElem("cbc:ID",cstr_);
	 	//  InvXml.OutOfElem();

		}
		else{
		  if(cn_flag_) InvXml.AddElem("cbc:CreditNoteTypeCode",381);	else InvXml.AddElem("cbc:InvoiceTypeCode",380);	// InvXml.SetAttrib("listID","UNCL1001");
			jddate(ft_date,&jaartal,&mm,&dd);// factuurdatum
			if(*s(8,25)){
				cstr_=CString(s(8,25),fldlen(8,25));cstr_.Trim(); if(cstr_.GetLength()==0) cstr_=CString("ORDER");
				InvXml.AddElem("cbc:Note",cstr_);
			}
			else{
				if(cn_flag_) cstr_.Format("CN %d-%05d",jaartal,ft_nr); 
				else cstr_.Format("FT %d-%05d",jaartal,ft_nr);
				InvXml.AddElem("cbc:Note",cstr_);
			}
			InvXml.AddElem("cbc:DocumentCurrencyCode","EUR");	// InvXml.SetAttrib("listID","ISO4217");
		}
//		if(!cn_flag_){cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:TaxPointDate",cstr_);}

	  if(SelfBilling==NO){
			if(*s(8,25)){
				if(cmpstr(s(8,25),"Peppol",6) && cmpstr(s(8,25),"Kasticket",9)){ // niet bij default (=men heeft geen referentie meegegeven)
			    cstr_=CString(s(8,25),fldlen(8,25)); cstr_.Trim();
  		    InvXml.AddElem("cbc:BuyerReference",cstr_);
				}
			}
  		InvXml.AddElem("cac:OrderReference");InvXml.IntoElem();
	  	  cstr_=CString(s(8,25),fldlen(8,25)); cstr_.Trim(); if(cstr_.GetLength()==0) cstr_=CString("ORDER");
		  	InvXml.AddElem("cbc:ID",cstr_);
	 	  InvXml.OutOfElem();
			if(fldlen(8,61) && *u(8,61)){
				InvXml.AddElem("cac:DespatchDocumentReference"); // gefactureerde bonnr
				InvXml.IntoElem();
					cstr_.Format("%d",*u(8,61)); InvXml.AddElem("cbc:ID",cstr_);
				InvXml.OutOfElem(); // DespatchDocumentReference
			}
			else if(*u(8,2)){
				InvXml.AddElem("cac:DespatchDocumentReference"); // gefactureerde bonnr
				InvXml.IntoElem();
					cstr_.Format("%d",*u(8,2)); InvXml.AddElem("cbc:ID",cstr_);
				InvXml.OutOfElem(); // DespatchDocumentReference
			}
  		//InvXml.AddElem("cac:DespatchDocumentReference");InvXml.IntoElem();
	  	//  cstr_=CString(s(8,25),fldlen(8,25)); cstr_.Trim(); if(cstr_.GetLength()==0) cstr_=CString("ORDER");
		  //	InvXml.AddElem("cbc:ID",cstr_);
	 	 // InvXml.OutOfElem();
		}
		InvLineNr=0; tot_lgpl_=0;
		if(fldlen(8,60) && *s(8,60)){// globale kassafaCTUUR
			InvLineNr=1; 
			for(k=0;k<BTWDIM-BTWDIV+1;k++){
				if(btw_bas[k]) InvLineNr++;
			}
			if(tot_leeg) InvLineNr++;
		}
		else{
			for(k=0;k<max_line;k++){ // aantal lijnen bepalen
				ram2stu(k);
				if(test_line() && (*s(58,16)!='*'|| !is_nul((double)(*d(58,35))) || *f(58,7) || is_nul(alg_tot))){ // bij 0-factuurwel commentaarlijnen meegeven
	#if DEF_INPUT | SPLITS_BON
					if(*pu_58_14 && *f(58,31)==0) continue;/* niet gebruikte lijnen skippen */
	#endif
					if(is_nul(alg_tot)){
				    j=btw_tab((BEDRAG)(*d(58,35)));
		        btw_CategorieUsed[j]=1;
					}
					if(*i(58,34)==99) continue; // geen leeggoed
					InvLineNr++;
  			}
			}
#if TRANS_KOST
      if(trans_kost) InvLineNr++;
#endif

			if(tot_leeg){
				InvLineNr++;
				if(tot_leeg!=tot_lgpl_) InvLineNr++;
			}
		}
		//if(*s(8,25)){
		//	if(cn_flag_){ // voor overheid moet bij CN originele factuurnummer megegeven worden
		//		InvXml.AddElem("cac:BillingReference");InvXml.IntoElem(); // factuurnummer  meegeven waarover CN gaat
		//			InvXml.AddElem("cac:InvoiceDocumentReference");InvXml.IntoElem();
	 // 				zero(str_,sizeof str_); copy(s(8,25),str_,fldlen(8,25)); cstr_=CString(str_); cstr_.Trim(); InvXml.AddElem("cbc:ID",cstr_);
		//			InvXml.OutOfElem(); //	InvoicelDocumentReference
 	//			InvXml.OutOfElem(); // BillingReference
		//	}
		//	else{
		//	  InvXml.AddElem("cac:OrderReference");InvXml.IntoElem(); // referentie bon/factuur meegeven (PO-nummer voor overheid)
		//		  zero(str_,sizeof str_); copy(s(8,25),str_,fldlen(8,25)); cstr_=CString(str_); cstr_.Trim(); InvXml.AddElem("cbc:ID",cstr_);
		//	  InvXml.OutOfElem();
		//	}
		//}
		InvXml.AddElem("cac:AdditionalDocumentReference");InvXml.IntoElem();
		  jddate(ft_date,&jaartal,&mm,&dd);// factuurdatum
		  zero(str_,sizeof str_); copy(s(25,3),str_,3); cstr_.Format("%s-%d-%05d",str_,jaartal,ft_nr);InvXml.AddElem("cbc:ID",cstr_);
			if(SelfBilling) InvXml.AddElem("cbc:DocumentDescription","Selfbilling Invoice");
			else InvXml.AddElem("cbc:DocumentDescription","CommercialInvoice");
// blijkbaar niet als ge pdf meegeeft      if(cn_flag_) InvXml.AddElem("cbc:DocumentTypeCode","130"); else InvXml.AddElem("cbc:DocumentTypeCode","130");
      InvXml.AddElem("cac:Attachment");
  		InvXml.IntoElem();

// EncodeBase64
      CString JamaFileName;

			JamaFileName.Format("%s%08X*.*","..\\Spool\\Files\\",MailMergeBijlage[0]);
      bool AttachmentAddedFlag=false;
      for (int Retry=0; Retry<120; Retry++) {
        CFileFind AttFinder;
        BOOL bWorking = AttFinder.FindFile(JamaFileName);
	      while (bWorking) {
		      bWorking = AttFinder.FindNextFile();
		      PdfName = AttFinder.GetFilePath();
					if(cfile_.Open(PdfName,CFile::modeRead,0)){
						int nFileLen = cfile_.GetLength();
						unsigned char* pBuffer = new unsigned char[nFileLen];
						cfile_.Seek(0L,CFile::begin);
						nFileLen = cfile_.Read( pBuffer, nFileLen );
						cfile_.Close();
						strBase64 = CMarkup::EncodeBase64( pBuffer, nFileLen );
						delete pBuffer;
						AttachmentAddedFlag=true;
					}
        }
        AttFinder.Close();
        if (AttachmentAddedFlag) break;
        TRACE("Wait 500 msec for attachement ...\n");
        Sleep(500);  // wacht halve seconde
      }
			if (AttachmentAddedFlag){
        int l=PdfName.Find("$");
        if (l>=0) PdfName=PdfName.Mid(l+1);
        InvXml.AddElem("cbc:EmbeddedDocumentBinaryObject",strBase64);
				InvXml.SetAttrib("filename",PdfName);
				InvXml.SetAttrib("mimeCode","application/pdf");
//				InvXml.SetAttrib("encodingCode","Base64");
			}
			else{
				cstr_.Format("Probleem met uitschrijven factuur %d (geen PDF). Schrijf deze opnieuw uit!",ft_nr);
				DisplayWarning((char *)(LPCTSTR)(cstr_),605,0);
			}
			InvXml.OutOfElem(); // Attachment
		InvXml.OutOfElem(); // AdditionalDocumentReference

		if(ExtraBijlageFactuurmail[0] && FileExist(ExtraBijlageFactuurmail)){
			InvXml.AddElem("cac:AdditionalDocumentReference");InvXml.IntoElem();
				InvXml.AddElem("cbc:ID","Attachment");
				InvXml.AddElem("cbc:DocumentDescription","Verkoopsvoorwaarden");
				InvXml.AddElem("cac:Attachment");
  			InvXml.IntoElem();

	// EncodeBase64
				bool AttachmentAddedFlag=false;
				if(cfile_.Open(ExtraBijlageFactuurmail,CFile::modeRead,0)){
					int nFileLen = cfile_.GetLength();
					unsigned char* pBuffer = new unsigned char[nFileLen];
					cfile_.Seek(0L,CFile::begin);
					nFileLen = cfile_.Read( pBuffer, nFileLen );
					cfile_.Close();
					strBase64 = CMarkup::EncodeBase64( pBuffer, nFileLen );
					delete pBuffer;
					AttachmentAddedFlag=true;
				}
				if (AttachmentAddedFlag){
					InvXml.AddElem("cbc:EmbeddedDocumentBinaryObject",strBase64);
					InvXml.SetAttrib("filename",ExtraBijlageFactuurmail);
					InvXml.SetAttrib("mimeCode","application/pdf");
				}
				InvXml.OutOfElem(); // Attachment
			InvXml.OutOfElem(); // AdditionalDocumentReference			
		}

		//InvXml.AddElem("cac:AdditionalDocumentReference");InvXml.IntoElem();
  //    InvXml.AddElem("cbc:ID","eFFF");
		//	InvXml.AddElem("cbc:DocumentType","JamaData urn:www.cenbii.eu:profile:bii05:ver2.0");
  //  InvXml.OutOfElem(); // AdditionalDocumentReference
		if(SelfBilling) goto selfsupplier;
selfcustomer:;
		if(SelfBilling){
			InvXml.AddElem("cac:AccountingCustomerParty");InvXml.IntoElem();
		}
		else{
  		InvXml.AddElem("cac:AccountingSupplierParty");InvXml.IntoElem();
		}
      InvXml.AddElem("cac:Party");InvXml.IntoElem();
			zero(str_,sizeof str_);copy("BE",str_,2);btw_deco(&str_[2],&firmbtwnr,0); 
        InvXml.AddElem("cbc:EndpointID",str_);	InvXml.AddAttrib("schemeID","9925"); // werkt niet InvXml.AddAttrib("schemeID","9956"); // BIS3 update 25/6/19, was voorheen InvXml.AddAttrib("schemeID","BE:VAT");
				InvXml.AddElem("cac:PartyIdentification");InvXml.IntoElem();
				  zero(str_,sizeof str_);btw_deco(&str_[0],&firmbtwnr,0); 
				  InvXml.AddElem("cbc:ID",str_);	InvXml.AddAttrib("schemeID","0208"); 
				InvXml.OutOfElem(); // PartyIdentification
				InvXml.AddElem("cac:PartyName");InvXml.IntoElem();
				  if(PeppolFirmaNaam[0]) InvXml.AddElem("cbc:Name",&PeppolFirmaNaam[0]);
          else InvXml.AddElem("cbc:Name",&firma[0]);
				InvXml.OutOfElem(); // Partyname
				InvXml.AddElem("cac:PostalAddress");InvXml.IntoElem();
          if(firma[31]) InvXml.AddElem("cbc:StreetName",&firma[31]);
          if(firma[65]) InvXml.AddElem("cbc:CityName",&firma[65]);
          if(firma[57]) InvXml.AddElem("cbc:PostalZone",&firma[57]);
					InvXml.AddElem("cac:Country"); InvXml.IntoElem();
            InvXml.AddElem("cbc:IdentificationCode","BE");
						// InvXml.AddAttrib("listID","ISO3166-1:Alpha2");
					InvXml.OutOfElem(); // Country
				InvXml.OutOfElem(); // Postaladdres
				InvXml.AddElem("cac:PartyTaxScheme"); InvXml.IntoElem();
		  		zero(str_,sizeof str_); if(firmbtwnr){
						copy("BE",str_,2);btw_deco(&str_[2],&firmbtwnr,0);
						if(str_[11]=='\0') {copy("BE0",str_,3);btw_deco(&str_[3],&firmbtwnr,0);}
					}
          InvXml.AddElem("cbc:CompanyID",str_); // InvXml.AddAttrib("schemeID","BE:VAT");
					InvXml.AddElem("cac:TaxScheme"); InvXml.IntoElem();
            InvXml.AddElem("cbc:ID","VAT");
					InvXml.OutOfElem(); // TaxScheme
				InvXml.OutOfElem(); // PartyTaxScheme
				//InvXml.AddElem("cac:Contact"); InvXml.IntoElem();
    //      // InvXml.AddElem("cbc:Name",Name);
				//  if(firma[222]){zero(str_,sizeof str_);copy(&firma[222],str_,30); InvXml.AddElem("cbc:ElectronicMail",str_);}
				//	if(firma[116]){zero(str_,sizeof str_);copy(&firma[116],str_,15); InvXml.AddElem("cbc:Telephone",str_);}
    //    InvXml.OutOfElem(); // Contact

				InvXml.AddElem("cac:PartyLegalEntity"); InvXml.IntoElem();
				  if(PeppolFirmaNaam[0]) InvXml.AddElem("cbc:RegistrationName",&PeppolFirmaNaam[0]);
				  else InvXml.AddElem("cbc:RegistrationName",&firma[0]);
					zero(str_,sizeof str_); btw_deco(&str_[0],&firmbtwnr,0); if(str_[9]=='\0'){copy("0",str_,1);btw_deco(&str_[1],&firmbtwnr,0);}
          InvXml.AddElem("cbc:CompanyID",str_);	InvXml.AddAttrib("schemeID","0208"); // InvXml.AddAttrib("schemeName","KBO");
				InvXml.OutOfElem(); // PartyLegalEntity
				if(firma[116] || firma[222]){
					InvXml.AddElem("cac:Contact"); InvXml.IntoElem();
				  	if(firma[116]){zero(str_,sizeof str_); copy(&firma[116],str_,15);InvXml.AddElem("cbc:Telephone",str_);}
				  	if(firma[222]){zero(str_,sizeof str_); copy(&firma[222],str_,30);InvXml.AddElem("cbc:ElectronicMail",str_);}
					InvXml.OutOfElem(); // contact
				}
			InvXml.OutOfElem(); // Party
		InvXml.OutOfElem(); // AccountingSupplierParty

    if(SelfBilling) goto payment;
selfsupplier:;
		if(SelfBilling){
  		InvXml.AddElem("cac:AccountingSupplierParty");InvXml.IntoElem();
		}
		else{
		  InvXml.AddElem("cac:AccountingCustomerParty");InvXml.IntoElem();
		}
#if FLAGEET
		if(SelfBilling==NO){
 		  zero(str_,sizeof str_); stcli_d(str_,(long)(*u(KL_Stu2240,1)),5,0); // if(fldlen(KL_Stu2240,2)) copy(s(KL_Stu2240,2),str_,fldlen(KL_Stu2240,2)); else stcli_d(str_,(long)(*u(KL_Stu2240,1)),5,0); 
			InvXml.AddElem("cbc:SupplierAssignedAccountID",str_);
		}
#endif

      InvXml.AddElem("cac:Party");InvXml.IntoElem(); // als endpoint, altijd BTW-nummer voorrang geven
				if((*l(KL_Stu2240,10)==999999999 || *l(KL_Stu2240,10)==0) && fldlen(KL_Stu2240,137) && *s(KL_Stu2240,137) && SelfBilling==NO) { // selfbilling altijd via 0208
					zero(str_, sizeof str_);
					copy0(s(KL_Stu2240,137), str_, fldlen(KL_Stu2240,137));
					InvXml.AddElem("cbc:EndpointID", str_);
					InvXml.AddAttrib("schemeID", "0088"); // GLN Nummer
				}
				else if(KlantIDViaBtwNr  && SelfBilling==NO){
					if (*(s(KL_Stu2240,10)+3) & 0x40) *(s(KL_Stu2240,10)+3)  &= 0xBF; btwnr_=*l(KL_Stu2240,10);  //if(btwnr_>=BTWNR_OFFSET) btwnr_-=BTWNR_OFFSET;
					zero(str_,sizeof str_); 
					copy("BE",str_,2);btw_deco(&str_[2],&btwnr_,0);
					InvXml.AddElem("cbc:EndpointID",str_);	InvXml.AddAttrib("schemeID","9925"); // BTW
				}
				else{
					if (*(s(KL_Stu2240,10)+3) & 0x40) *(s(KL_Stu2240,10)+3)  &= 0xBF; btwnr_=*l(KL_Stu2240,10); // if(btwnr_>=BTWNR_OFFSET) btwnr_-=BTWNR_OFFSET;
					zero(str_,sizeof str_); btw_deco(&str_[0],&btwnr_,0); if(str_[9]=='\0'){copy("0",str_,1);btw_deco(&str_[1],&btwnr_,0);}
					InvXml.AddElem("cbc:EndpointID",str_);	InvXml.AddAttrib("schemeID","0208"); // KBO Jaak 27/5/21: Was 9956
				}
				InvXml.AddElem("cac:PartyIdentification");InvXml.IntoElem(); // factuurklant
					if(fldlen(KL_Stu2240,137) && *s(KL_Stu2240,137)) { // als ID, GLN voorrang geven
						zero(str_, sizeof str_);
						copy0(s(KL_Stu2240,137), str_, fldlen(KL_Stu2240,137));
						InvXml.AddElem("cbc:ID", str_);
						InvXml.AddAttrib("schemeID", "0088"); // GLN Nummer
					}
					else{ // altijd via ondernemingsnummer KBO
						if (*(s(KL_Stu2240,10)+3) & 0x40) *(s(KL_Stu2240,10)+3)  &= 0xBF; btwnr_=*l(KL_Stu2240,10); // if(btwnr_>=BTWNR_OFFSET) btwnr_-=BTWNR_OFFSET;
						zero(str_,sizeof str_); btw_deco(&str_[0],&btwnr_,0); if(str_[9]=='\0'){copy("0",str_,1);btw_deco(&str_[1],&btwnr_,0);}
						InvXml.AddElem("cbc:ID",str_);	InvXml.AddAttrib("schemeID","0208"); // KBO Jaak 27/5/21: Was 9956
					}
				InvXml.OutOfElem(); // PartyIdentification
				InvXml.AddElem("cac:PartyName");InvXml.IntoElem();
				  zero(str_,sizeof str_); copy(s(KL_Stu2240,3),str_,fldlen(KL_Stu2240,3)); CnvJamaChar(str_, sizeof str_,0);InvXml.AddElem("cbc:Name",str_);
				InvXml.OutOfElem(); // Partyname

				InvXml.AddElem("cac:PostalAddress");InvXml.IntoElem();
				if(*s(KL_Stu2240,4)){zero(str_,sizeof str_); copy(s(KL_Stu2240,4),str_,fldlen(KL_Stu2240,4));CnvJamaChar(str_, sizeof str_,0);InvXml.AddElem("cbc:StreetName",str_);}
				if(*s(KL_Stu2240,6)){zero(str_,sizeof str_); copy(s(KL_Stu2240,6),str_,fldlen(KL_Stu2240,6));CnvJamaChar(str_, sizeof str_,0);InvXml.AddElem("cbc:CityName",str_);}
				if(*s(KL_Stu2240,5)){zero(str_,sizeof str_); copy(s(KL_Stu2240,5),str_,fldlen(KL_Stu2240,5));CnvJamaChar(str_, sizeof str_,0);InvXml.AddElem("cbc:PostalZone",str_);}
				InvXml.AddElem("cac:Country"); InvXml.IntoElem();
				zero(str_,sizeof str_);
				if(*l(KL_Stu2240,10)==0 && (fldlen(KL_Stu2240,22) && *s(KL_Stu2240,22))) copy(s(KL_Stu2240,22),str_,2); else copy("BE",str_,2);
				InvXml.AddElem("cbc:IdentificationCode",str_);
				// InvXml.AddAttrib("listID","ISO3166-1:Alpha2");
				InvXml.OutOfElem(); // Country
				InvXml.OutOfElem(); // Postaladdres


				if(*l(KL_Stu2240,10) || (fldlen(KL_Stu2240,22) && *s(KL_Stu2240,22))){ // enkel indien BTW-nummer
					InvXml.AddElem("cac:PartyTaxScheme"); InvXml.IntoElem();
						if(*l(KL_Stu2240,10) || fldlen(KL_Stu2240,22)==0 || *s(KL_Stu2240,22)=='\0'){ // belgisch
							if (*(s(KL_Stu2240,10)+3) & 0x40) *(s(KL_Stu2240,10)+3)  &= 0xBF; btwnr_=*l(KL_Stu2240,10); // if(btwnr_>=BTWNR_OFFSET) btwnr_-=BTWNR_OFFSET;
		  				zero(str_,sizeof str_); 
							copy("BE",str_,2);btw_deco(&str_[2],&btwnr_,0);
							if(str_[11]=='\0') {copy("BE0",str_,3);btw_deco(&str_[3],&btwnr_,0);}
							InvXml.AddElem("cbc:CompanyID",str_); 
						}
						else{ // buitenlander
	  					zero(str_,sizeof str_);
							copy(s(KL_Stu2240,22),str_,2);k=2;
							for(j=2;j<fldlen(KL_Stu2240,22);j++){
								kar_=*(s(KL_Stu2240,22)+j); if(kar_=='\0') break;
								if((kar_>='0' && kar_<='9') || (kar_>='a' && kar_<='z') || (kar_>='A' && kar_<='Z')){
									str_[k++]=kar_; if(k>=12) break;
								}
							}
							InvXml.AddElem("cbc:CompanyID",str_);
							zero(str_,sizeof str_);copy(s(KL_Stu2240,22),str_,2); copy(":VAT",&str_[2],4);
						}
						InvXml.AddElem("cac:TaxScheme"); InvXml.IntoElem();
							InvXml.AddElem("cbc:ID","VAT");
						InvXml.OutOfElem(); // TaxScheme
					InvXml.OutOfElem(); // PartyTaxScheme
				}
				InvXml.AddElem("cac:PartyLegalEntity");
				InvXml.IntoElem();
				zero(str_, sizeof str_);
				copy(s(KL_Stu2240,3), str_, fldlen(KL_Stu2240,3));
				CnvJamaChar(str_, sizeof str_, 0);
				InvXml.AddElem("cbc:RegistrationName", str_);
				zero(str_, sizeof str_);


				if(*l(KL_Stu2240,10)){ // Belgisch als ondernemingsnummer of BTW# doorgeven
					if(KlantIDViaBtwNr){
						if (*(s(KL_Stu2240,10)+3) & 0x40) *(s(KL_Stu2240,10)+3)  &= 0xBF; btwnr_=*l(KL_Stu2240,10); // if(btwnr_>=BTWNR_OFFSET) btwnr_-=BTWNR_OFFSET;
						zero(str_,sizeof str_); 
						copy("BE",str_,2);btw_deco(&str_[2],&btwnr_,0);
						if(str_[11]=='\0') {copy("BE0",str_,3);btw_deco(&str_[3],&btwnr_,0);}
						InvXml.AddElem("cbc:CompanyID",str_);  // BTW
					}
					else{
						zero(str_,sizeof str_); 
						if (*(s(KL_Stu2240,10)+3) & 0x40) *(s(KL_Stu2240,10)+3)  &= 0xBF; btwnr_=*l(KL_Stu2240,10); // if(btwnr_>=BTWNR_OFFSET) btwnr_-=BTWNR_OFFSET;
						btw_deco(&str_[0],&btwnr_,0); if(str_[9]=='\0'){copy("0",str_,1);btw_deco(&str_[1],&btwnr_,0); }
						InvXml.AddElem("cbc:CompanyID",str_);	InvXml.AddAttrib("schemeID","0208");  //KBO 
					}
				}
				else if(fldlen(KL_Stu2240,137) && *s(KL_Stu2240,137)) { // anders GLN
					zero(str_, sizeof str_);
					copy0(s(KL_Stu2240,137), str_, fldlen(KL_Stu2240,137));
					InvXml.AddElem("cbc:CompanyID", str_);
					InvXml.AddAttrib("schemeID", "0088"); // GLN Nummer
				}
				else{ // buitenlander
					zero(str_,sizeof str_);k=0;
					for(j=2;j<fldlen(KL_Stu2240,22);j++){
						kar_=*(s(KL_Stu2240,22)+j); if(kar_=='\0') break;
						if((kar_>='0' && kar_<='9') || (kar_>='a' && kar_<='z') || (kar_>='A' && kar_<='Z')){
							str_[k++]=kar_; if(k>=12) break;
						}
					}
					InvXml.AddElem("cbc:CompanyID",str_);	InvXml.AddAttrib("schemeID","0189"); // EUROPEAN BUSINESS IDENTIFIER (ebid) for use in EDI en andere B2B
				}
				InvXml.OutOfElem(); // PartyLegalEntity

				
				InvXml.AddElem("cac:Contact"); InvXml.IntoElem();
				  zero(str_,sizeof str_); copy(s(KL_Stu2240,3),str_,fldlen(KL_Stu2240,3)); CnvJamaChar(str_, sizeof str_,0);InvXml.AddElem("cbc:Name",str_);
					zero(str_,sizeof str_); copy(s(KL_Stu2240,21),str_,fldlen(KL_Stu2240,21)); 
					if(str_[0]=='\0')  str_[0]='X';CnvJamaChar(str_, sizeof str_,0);InvXml.AddElem("cbc:ElectronicMail",str_);
				InvXml.OutOfElem(); // Contact
			InvXml.OutOfElem(); // Party
		InvXml.OutOfElem(); // AccountingCustomerParty
    if(SelfBilling) goto selfcustomer;

		InvXml.AddElem("cac:Delivery");
		InvXml.IntoElem();
			if(fldlen(8,62) && *u(8,62)){
       jddate(*u(8,62),&jaartal,&mm,&dd);// factuurdatum
   		 cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:ActualDeliveryDate",cstr_);
			}
			else if (fldlen(8,8) && *u(8,8)) {
				if(fldlen(8,10) && *u(8,10)) jddate(*u(8,8), &jaartal, &mm, &dd);
				else jddate(*u(8,8), &jaartal, &mm, &dd);
				cstr_.Format("%04d-%02d-%02d", jaartal, mm, dd);
				InvXml.AddElem("cbc:ActualDeliveryDate", cstr_);
			}
			InvXml.AddElem("cac:DeliveryLocation");
			InvXml.IntoElem();
			if(fldlen(KL_Stu2240,137)) {// GLN leverklant, en anders GLN van factuurklant
				zero(str_,sizeof str_);
				if(*s(KL_Stu2240,137)) copy0(s(KL_Stu2240,137), str_, fldlen(KL_Stu2240,137));
				if(fldlen(8,12) && *u(8,12)){ // gln nummer van lev.adres nemen
			    copy(s(KL_Stu2240,1),buf1000,fldlen(KL_Stu2240,0));
					*u(KL_Stu2240,1)=*u(8,12);
					if(fasgeti(KL_Stu2240)==0){
						if(*s(KL_Stu2240,137)) copy0(s(KL_Stu2240,137), str_, fldlen(KL_Stu2240,137));
					}
					copy(buf1000,s(KL_Stu2240,1),fldlen(KL_Stu2240,0));
				}
				if(str_[0]) {
					InvXml.AddElem("cbc:ID", str_);
					InvXml.AddAttrib("schemeID", "0088"); // GLN Nummer
				}
			}
			InvXml.AddElem("cac:Address");
			InvXml.IntoElem();

			cstr_=""; zero(str_, sizeof str_);
			if(fldlen(8,15) && *s(8,15)){
				cstr_=CString(s(8,15),fldlen(8,15));cstr_.Trim();
				if(cstr_.GetLength()==0){
					cstr_=CString(s(KL_Stu2240,4),fldlen(KL_Stu2240,4));cstr_.Trim();
				}
			}
//				copy(s(8,15), str_, fldlen(8,15)); else copy(s(KL_Stu2240,4), str_, fldlen(KL_Stu2240,4));
//			CnvJamaChar(str_, sizeof str_, 0);

			if (cstr_.GetLength()) InvXml.AddElem("cbc:StreetName", cstr_);

			cstr_=""; zero(str_, sizeof str_);
			if(fldlen(8,17) && *s(8,17)){
				cstr_=CString(s(8,17),fldlen(8,17));cstr_.Trim();
				if(cstr_.GetLength()==0){
					cstr_=CString(s(KL_Stu2240,6),fldlen(KL_Stu2240,6));cstr_.Trim();
				}
			}
//			if(fldlen(8,17) && *s(8,17)) copy(s(8,17), str_, fldlen(8,17)); else copy(s(KL_Stu2240,6), str_, fldlen(KL_Stu2240,6));
//			CnvJamaChar(str_, sizeof str_, 0);

			if (cstr_.GetLength()) InvXml.AddElem("cbc:CityName", cstr_);

			cstr_=""; zero(str_, sizeof str_);
			if(fldlen(8,16) && *s(8,16)){
				cstr_=CString(s(8,16),fldlen(8,16));cstr_.Trim();
				if(cstr_.GetLength()==0){
					cstr_=CString(s(KL_Stu2240,5),fldlen(KL_Stu2240,5));cstr_.Trim();
				}
			}
//			if(fldlen(8,16) && *s(8,16)) copy(s(8,16), str_, fldlen(8,16)); else copy(s(KL_Stu2240,5), str_, fldlen(KL_Stu2240,5));
//			CnvJamaChar(str_, sizeof str_, 0);

			if (cstr_.GetLength()) InvXml.AddElem("cbc:PostalZone", cstr_);

			InvXml.AddElem("cac:Country"); InvXml.IntoElem();
			zero(str_,sizeof str_);
			if(*l(KL_Stu2240,10)==0 && (fldlen(KL_Stu2240,22) && *s(KL_Stu2240,22))) copy(s(KL_Stu2240,22),str_,2); else copy("BE",str_,2);
			InvXml.AddElem("cbc:IdentificationCode",str_);
			InvXml.OutOfElem(); // Country
			InvXml.OutOfElem(); // Address
			InvXml.OutOfElem(); // DeliveryLocation

			InvXml.AddElem("cac:DeliveryParty");
			InvXml.IntoElem();
				InvXml.AddElem("cac:PartyName");
				InvXml.IntoElem();
					zero(str_, sizeof str_);
					if(fldlen(8,14) && *s(8,14)) copy(s(8,14), str_, fldlen(8,14)); else copy(s(KL_Stu2240,3), str_, fldlen(KL_Stu2240,3));
					CnvJamaChar(str_, sizeof str_, 0);
					InvXml.AddElem("cbc:Name", str_);
				InvXml.OutOfElem(); // partyname
			InvXml.OutOfElem(); // deleveryparty


		InvXml.OutOfElem(); // Delivery

payment:;


    InvXml.AddElem("cac:PaymentMeans"); InvXml.IntoElem();
		  if(is_nul(alg_tot-bd_betaald_)){
				if(fldlen(8,73) && *s(8,73)=='B') InvXml.AddElem("cbc:PaymentMeansCode",55); // betaald, debetcard
				else InvXml.AddElem("cbc:PaymentMeansCode",10); // betaald, dan cash nemen 
			}
			else InvXml.AddElem("cbc:PaymentMeansCode",31); // 31=overschrijving 1=onbekend
			// InvXml.AddAttrib("listID","UNCL4461");

		// Dit geeft validatie warning A UBL invoice should not include the PaymentMeans PaymentDueDate, dus halen we het weg.
  		//if(cn_flag_ || (alg_tot-bd_betaald_)<=0.006){
  		//	jddate(verv_dt,&jaartal,&mm,&dd); cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:PaymentDueDate",cstr_);
  		//}
			if((alg_tot-bd_betaald_)>0.006){
				zero(str_,sizeof str_);MakeStructMed(str_,ft_nr); cstr_=CString(str_); cstr_.Replace("/",""); // 'kkk/kkff/fffcc'   K(lant) F(aktnr) C(heck) 
//				InvXml.AddElem("cbc:InstructionID",cstr_);
				InvXml.AddElem("cbc:PaymentID",cstr_);
				if(firma[256]){
					if(firma[298]=='\0'){
						IbanTools(&firma[256],&firma[298],"",1); // BIC
						sysput(1261,11,&firma[298]);
					}	
					InvXml.AddElem("cac:PayeeFinancialAccount"); InvXml.IntoElem();
						zero(str_,sizeof str_);j=0;
						for(k=0;k<25;k++){ // IBAN
							kar_=firma[256+k];
							if(kar_=='\0') break;
		 					if((kar_>='0' && kar_<='9') || (kar_>='A' && kar_<='Z')) str_[j++]=kar_;
						}
						InvXml.AddElem("cbc:ID",str_);	//InvXml.AddAttrib("schemeID","IBAN");
						InvXml.AddElem("cbc:Name","Payment account");
						InvXml.AddElem("cac:FinancialInstitutionBranch"); InvXml.IntoElem();
							zero(str_,sizeof str_);j=0;
  						for(k=0;k<11;k++){ //  BIC
								kar_=firma[298+k];
								if(kar_=='\0') break;
	 							if((kar_>='0' && kar_<='9') || (kar_>='A' && kar_<='Z')) str_[j++]=kar_;
							}				
							InvXml.AddElem("cbc:ID",str_);//	InvXml.AddAttrib("schemeID","BIC");
						InvXml.OutOfElem(); // FinancialInstitutionBranch
					InvXml.OutOfElem(); //PayeeFinancialAccount
				}
			}

    InvXml.OutOfElem(); // PaymentMeans

		if((alg_tot-bd_betaald_)>0.006 && (!is_nul(kredietbp_bd)) || !is_nul(disk_bd)){
		  InvXml.AddElem("cac:PaymentTerms"); InvXml.IntoElem();
			if(kredietbp_bd){
				cstr1_=Bedrag2Cstring((double)(kredietbp_bd),2);
				jddate(verv_dt, &jaartal, &mm, &dd);
				cstr_.Format("Kredietbeperking: bij betaling later dan %02d-%02d-%04d wordt %s EUR extra in rekening gebracht", dd,mm,jaartal,cstr1_);
				InvXml.AddElem("cbc:Note", cstr_);
   		}
			if(disk_bd && fldlen(KL_Stu2240,14)){
				cstr1_=Bedrag2Cstring((double)(disk_bd),2);
				jddate(disk_dt, &jaartal, &mm, &dd);
				cstr_.Format("%d%% disconto zijnde %s EUR af te trekken, mits betaling voor %02d-%02d-%04d", *i(KL_Stu2240,14), cstr1_,dd,mm,jaartal);
				InvXml.AddElem("cbc:Note", cstr_);
  		}
			InvXml.OutOfElem(); // PaymentTerms
		}
		if(FactuurMetCorrectie){
			InvXml.AddElem("cac:AllowanceCharge");InvXml.IntoElem();
				InvXml.AddElem("cbc:ChargeIndicator","false");
				InvXml.AddElem("cbc:AllowanceChargeReason","Afronding");
				InvXml.AddElem("cbc:Amount",Bedrag2Cstring((double)(-BdFactuurAfronding*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
				InvXml.AddElem("cac:TaxCategory");InvXml.IntoElem();
					InvXml.AddElem("cbc:ID","Z"); 
					InvXml.AddElem("cbc:Percent",Bedrag2Cstring((double)(0.),2));
					InvXml.AddElem("cac:TaxScheme");InvXml.IntoElem();
						InvXml.AddElem("cbc:ID","VAT");
					InvXml.OutOfElem(); // TaxScheme
				InvXml.OutOfElem(); // TaxCategory
			InvXml.OutOfElem(); // AllowanceCharge 
		}
		InvXml.AddElem("cac:TaxTotal");InvXml.IntoElem();
		  tot_0pct_=0;
			if(FactuurMetCorrectie) tot_0pct_+=BdFactuurAfronding;
		  InvXml.AddElem("cbc:TaxAmount",Bedrag2Cstring((double)(btw_tot*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
			zero((char *)btw_CategorieUsed,sizeof btw_CategorieUsed); // nog eens extra controleren op totalen per BTW%
			if(fldlen(8,60) && *s(8,60)){// bij globaalfactuur enkel categorien meegeven dire gebruikt worden
				for(k=0;k<BTWDIM-BTWDIV+1;k++){
					if(btw_bas[k]){
						if(j==0){
							fasinit(58); // eerste keer de speciale tekst zetten
							btw_CategorieUsed[k]=YES;
						}
						btw_CategorieUsed[k]=YES;
					}
				}
				if(tot_leeg) btw_CategorieUsed[0]=YES;
			}
			else {
				for(k=0;k<max_line;k++){
					ram2stu(k);
					if(test_line()  && (*s(58,16)!='*'|| !is_nul((double)(*d(58,35))) || *f(58,7) || is_nul(alg_tot))){
#if DEF_INPUT | SPLITS_BON
						if(*pu_58_14 && *f(58,31)==0) continue;/* niet gebruikte lijnen skippen */
#endif
						if((*s(58,16)=='*' && *d(58,35)==0 && *f(58,7)==0) && !is_nul(alg_tot)) continue; // geen commentaarlijnen meegeven behalve bij 0-factuur
						if(*s(58,16)=='*' && *f(58,31)==0) *f(58,31)=1;
						if(*f(58,47)>0) tot_lgpl_+=*f(58,47);
						if(*i(58,34)==99) continue; // geen leeggoed
						j=btw_tab((BEDRAG)(*d(58,35))); btw_CategorieUsed[j]=1;
  				}
				}
				if(tot_leeg) btw_CategorieUsed[0]=YES;
			}
      for(k=0;k<BTWDIM-BTWDIV+1;k++){
				if(btw_bas[k] || btw_CategorieUsed[k]){
	//				if(btw_pct[k]==0){tot_0pct_+=btw_bas[k]; continue;} // zero-rated goods mag maar 1 keer voorkomen (cfr leeggoed)
					InvXml.AddElem("cac:TaxSubtotal"); InvXml.IntoElem();
						InvXml.AddElem("cbc:TaxableAmount",Bedrag2Cstring((double)(btw_bas[k]*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
						InvXml.AddElem("cbc:TaxAmount",Bedrag2Cstring((double)(btw_bd[k]*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
						InvXml.AddElem("cac:TaxCategory");InvXml.IntoElem();
							if(btw_pct[k]==def_btw) cstr_="S"; 
							else if(btw_pct[k]) cstr_="S";  // ???? in UBL is dit AA
							else cstr_="Z";
							InvXml.AddElem("cbc:ID",cstr_); // InvXml.AddAttrib("schemeID","UNCL5305");
							InvXml.AddElem("cbc:Percent",Bedrag2Cstring((double)(btw_pct[k]),2));
							InvXml.AddElem("cac:TaxScheme");InvXml.IntoElem();
								InvXml.AddElem("cbc:ID","VAT");
							InvXml.OutOfElem(); // TaxScheme
						InvXml.OutOfElem(); // TaxCategory
					InvXml.OutOfElem(); // TaxSubtotal
				}
			}
			tot_0pct_+=tot_leeg; // leeggoed bij de 0% tellen
			if(!is_nul((double)(tot_leeg))){
				InvXml.AddElem("cac:TaxSubtotal"); InvXml.IntoElem();
					InvXml.AddElem("cbc:TaxableAmount",Bedrag2Cstring((double)(tot_leeg*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
					InvXml.AddElem("cbc:TaxAmount","0.00"); InvXml.AddAttrib("currencyID","EUR");
					InvXml.AddElem("cac:TaxCategory");InvXml.IntoElem();
						InvXml.AddElem("cbc:ID","E"); // InvXml.AddAttrib("schemeID","UNCL5305");  // leeggoed ook als 0% beschouwen
						InvXml.AddElem("cbc:Percent","0.00");
						InvXml.AddElem("cbc:TaxExemptionReason","Leeggoed/Vidange");
						InvXml.AddElem("cac:TaxScheme");InvXml.IntoElem();
							InvXml.AddElem("cbc:ID","VAT");
						InvXml.OutOfElem(); // TaxScheme
					InvXml.OutOfElem(); // TaxCategory
				InvXml.OutOfElem(); // TaxSubtotal
			}
		InvXml.OutOfElem(); // TaxTotal
		InvXml.AddElem("cac:LegalMonetaryTotal"); InvXml.IntoElem();
			InvXml.AddElem("cbc:LineExtensionAmount",Bedrag2Cstring((double)((belastbt+tot_leeg)*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
			InvXml.AddElem("cbc:TaxExclusiveAmount",Bedrag2Cstring((double)((belastbt+tot_leeg+BdFactuurAfronding)*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
			InvXml.AddElem("cbc:TaxInclusiveAmount",Bedrag2Cstring((double)((alg_tot+BdFactuurAfronding)*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
			if(FactuurMetCorrectie){
			  InvXml.AddElem("cbc:AllowanceTotalAmount",Bedrag2Cstring((double)(-BdFactuurAfronding*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
			}
			bd_=0; 
			if(!cn_flag_){
				if(*s(8,22)=='J') bd_=alg_tot+BdFactuurAfronding;
				else if(fldlen(8,21) && *f(8,21)) bd_=*f(8,21);
			}
			if(bd_) {InvXml.AddElem("cbc:PrepaidAmount",Bedrag2Cstring((double)(bd_),2)); InvXml.AddAttrib("currencyID","EUR");}
			InvXml.AddElem("cbc:PayableAmount",Bedrag2Cstring((double)((alg_tot-bd_+BdFactuurAfronding)*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
		InvXml.OutOfElem(); // LegalMonetaryTotal
		//InvXml.AddElem("cac:PaymenttermsLegalMonetaryTotal"); InvXml.IntoElem();
  //    jddate(verv_dt,&jaartal,&mm,&dd); cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:PaymentDueDate",cstr_);
		//InvXml.OutOfElem(); // PaymenttermsLegalMonetaryTotal

		InvLineNr=1; tot_lgpl_=0;
		if(fldlen(8,60) && *s(8,60)){// bij kassafactuur of gecorrigeerde inclusief factuur enkel totalen meegeven
			//ram2stu(0);	if(*s(58,16)=='*' && *d(58,35)==0) InvLine2PeppolXml(NO,cn_flag_);
			//ram2stu(1);	if(*s(58,16)=='*' && *d(58,35)==0) InvLine2PeppolXml(NO,cn_flag_);
			j=0;
			for(k=0;k<BTWDIM-BTWDIV+1;k++){
				if(btw_bas[k]){
					if(j==0){
						fasinit(58); // eerste keer de speciale tekst zetten
						copy(s(8,60),s(58,16),30);
						*f(58,31)=1; *f(58,24)=btw_pct[k];
						InvLine2PeppolXml(NO,cn_flag_);
						j=1;
					}
					fasinit(58);
					sprintf_s(s(58,15),5,"VK%2.0f",btw_pct[k]);
					sprintf_s(s(58,16),30,"Verkopen %2.2f %%",btw_pct[k]);
					*d(58,35)=btw_bas[k]; *f(58,31)=1; *f(58,24)=btw_pct[k];
					InvLine2PeppolXml(NO,cn_flag_);
				}
			}
			if(tot_leeg){
				fasinit(58);
				copy("LEEGG",s(58,15),5); copy("Leeggoed",s(58,16),8); *f(58,47)=tot_leeg; *f(58,31)=1;
				InvLine2PeppolXml(YES,cn_flag_);
			}
		}
		else{
			for(k=0;k<max_line;k++){
				ram2stu(k);
				if(test_line()  && (*s(58,16)!='*'|| !is_nul((double)(*d(58,35))) || *f(58,7) || is_nul(alg_tot))){
	#if DEF_INPUT | SPLITS_BON
					if(*pu_58_14 && *f(58,31)==0) continue;/* niet gebruikte lijnen skippen */
	#endif
					if((*s(58,16)=='*' && *d(58,35)==0 && *f(58,7)==0) && !is_nul(alg_tot)) continue; // geen commentaarlijnen meegeven behalve bij 0-factuur
					if(*s(58,16)=='*' && *f(58,31)==0) *f(58,31)=1;
					if(*f(58,47)>0) tot_lgpl_+=*f(58,47);
					if(*i(58,34)==99) continue; // geen leeggoed
					lgmode_=NO;
					InvLine2PeppolXml(NO,cn_flag_);
  			}
			}
#if LEVERINGSKOST
		if(KM_heffing){
			fasinit(58);
			fasinit(6);*u(6,1)=RecLevKostArt; fasgeti(6);
			copy(s(6,2),s(58,15),fldlen(58,15));
			copy(s(6,3),s(58,16),fldlen(58,16));
			*pf_58_24=BtwLeveringskost;*f(58,20)=KM_heffing;*f(58,31)=1;
			*d(58,35)=KM_heffing; if(fldlen(58,42)) *d(58,42)=KM_heffing;
			lgmode_=NO;
			InvLine2PeppolXml(NO,cn_flag_);
		}
#endif
    if(tot_leeg){
			if(!is_nul(tot_lgpl_)){
				fasinit(58);copy("LEEGG",s(58,15),5); copy("Leeggoed geleverd",s(58,16),20); *f(58,47)=tot_lgpl_; *f(58,31)=1;
				InvLine2PeppolXml(YES,cn_flag_);
			}
			bd_=tot_leeg-tot_lgpl_; 
			if(!is_nul(bd_)){
				fasinit(58);copy("LEEGG",s(58,15),5); copy("Leeggoed terug",s(58,16),20); *f(58,47)=bd_; *f(58,31)=1;
				InvLine2PeppolXml(YES,cn_flag_);
			}
		}

#if TRANS_KOST
 		if(trans_kost){
			fasinit(58);
			copy("HKOST",s(58,15),5);
			copy("Handling kosten",ps_58_16,30);
			*pf_58_24=def_btw;*f(58,20)=trans_kost;*f(58,31)=1;
			*d(58,35)=trans_kost; if(fldlen(58,42)) *d(58,42)=trans_kost;
			lgmode_=NO;
			InvLine2PeppolXml(NO,cn_flag_);
		}
#endif
	}
  InvXml.OutOfElem(); // inv:Invoice EINDE
  zero(str_,sizeof str_); copy(s(25,3),str_,3); jddate(ft_date,&jaartal,&mm,&dd);// factuurdatum
	zero(CodaboxUniqueID,sizeof CodaboxUniqueID); sprintf_s(CodaboxUniqueID,20,"%s-%d-%05d.xml",str_,jaartal,ft_nr);
	cstr_.Format("%s%s-%d-%05d.xml",OutputMapUbl,str_,jaartal,ft_nr);
	zero(CodaBoxFileName,sizeof CodaBoxFileName); copy0((char *)(LPCTSTR)(cstr_),CodaBoxFileName,sizeof CodaBoxFileName);
	if(InvXml.Save(CodaBoxFileName)==false) {
		errnum=1;zero(CodaboxUniqueID,sizeof CodaboxUniqueID);
		zero(CodaBoxFileName,sizeof CodaBoxFileName);
	}
}

static void InvLine2PeppolXml(int lgmode_, int cn_flag_)
{
  int j,k,qlv_dec_=2,afrondingsfout_;
	double bd_,bd1_,factor_,qlv_,afrond_;
	long lbd_;
	short mm,dd,jaartal;
	char str_[100];
	CString cstr_;

	afrondingsfout_=NO;
	if(lgmode_) {if(*f(58,47)<0 && *f(58,31)>0) *f(58,31)=-*f(58,31);} // om negatieve ehprijs te voorkomen 
	else{ // om negatieve ehprijs te voorkomen : ehprijs = totaal/aantal
		if(*d(58,35)<0 && *f(58,31)>0) *f(58,31)=-*f(58,31); // 1 x -10 = -10
		if(*d(58,35)>0 && *f(58,31)<0) *f(58,31)=-*f(58,31); // -1 x -10 = 10

		afrond_=1;	for(j=0;j<qlv_dec_;j++) afrond_/=10.;
		qlv_=Round((double)(*f(58,31)),afrond_);
		bd_=*d(58,35); if(qlv_) bd_=*d(58,35)/ qlv_;
		bd_=Round(bd_,(double)(0.0001));
		bd1_=*d(58,35)-(bd_*qlv_); if(bd1_<-0.011 || bd1_>0.011) afrondingsfout_=YES; // mag niet meer afwijken dan 0.02 EUR
//		if(!is_nul((double)(*d(58,35)-(bd_*qlv_)))) afrondingsfout_=YES;
	} 


  factor_=1.0; if(cn_flag_) factor_=-1.0;
	fasinit(6);if(*u(58,14) && *s(58,16)!='*') {*u(6,1)=*u(58,14);fasgeti(6);}

	if(cn_flag_) InvXml.AddElem("cac:CreditNoteLine"); else InvXml.AddElem("cac:InvoiceLine"); InvXml.IntoElem();
    InvXml.AddElem("cbc:ID",InvLineNr);
    qlv_dec_=2;
#if FLAGGOU
		qlv_dec_=4;
#endif
		if(cn_flag_) InvXml.AddElem("cbc:CreditedQuantity",Bedrag2Cstring((double)(*f(58,31)*factor_),qlv_dec_)); 
		else InvXml.AddElem("cbc:InvoicedQuantity",Bedrag2Cstring((double)(*f(58,31)*factor_),qlv_dec_));
#if FLAGDEW
		if(*f(58,8)) InvXml.AddAttrib("unitCode","KGM");
		else InvXml.AddAttrib("unitCode","ZZ"); // InvXml.AddAttrib("unitCodeListID","UNECERec20"); 
#else
		InvXml.AddAttrib("unitCode","ZZ"); // InvXml.AddAttrib("unitCodeListID","UNECERec20"); 
#endif
		if(lgmode_) cstr_=Bedrag2Cstring((double)(*f(58,47)*factor_),2); else cstr_=Bedrag2Cstring((double)(*d(58,35)*factor_),2);
		InvXml.AddElem("cbc:LineExtensionAmount",cstr_); InvXml.AddAttrib("currencyID","EUR");
		InvXml.AddElem("cac:Item"); InvXml.IntoElem();
			zero(str_,sizeof str_);copy(s(58,16),str_,fldlen(58,16)); CnvJamaChar(str_, sizeof str_,0);InvXml.AddElem("cbc:Description",str_);
			zero(str_,sizeof str_);copy(s(58,16),str_,fldlen(58,16)); CnvJamaChar(str_, sizeof str_,0);InvXml.AddElem("cbc:Name",str_);
			if(*s(58,15)){
				InvXml.AddElem("cac:SellersItemIdentification"); InvXml.IntoElem();
					zero(str_,sizeof str_);
#if FLAGSAS  // GRB-nummer meegeven ipv artikelcode
  				if(lgmode_) copy("746000",str_,6);
  				else if(*f(58,24)==0 && *s(2,22)) copy("700001",str_,6);
  				else if(*f(58,24)==0 && *s(2,22)=='\0') copy("700000",str_,6);
  				else if(*f(58,24)==6) copy("700100",str_,6);
  				else if(*f(58,24)==12) copy("700200",str_,6);
  				else copy("700300",str_,6);
#else
					copy(s(58,15),str_,fldlen(58,15)); 
#endif
					InvXml.AddElem("cbc:ID",str_);
				InvXml.OutOfElem(); //SellersItemIdentification
			}
			if((fldlen(6,70) && *s(6,70)>='0' && *s(6,70)<='9') || (fldlen(6,71) && *s(6,71)>='0' && *s(6,71)<='9')){ // EAN
				if(*s(6,70) && *s(6,70)>='0' && *s(6,70)<='9') j=70; else j=71;
				for(k=0;k<13;k++) if(*(s(6,j)+k)=='\0') break;

				InvXml.AddElem("cac:StandardItemIdentification"); InvXml.IntoElem();
					zero(str_,sizeof str_);copy(s(6,j),str_,fldlen(6,j)); CnvJamaChar(str_, sizeof str_,0);	
					InvXml.AddElem("cbc:ID",str_); InvXml.AddAttrib("schemeID","0160");
				InvXml.OutOfElem(); //StandardItemIdentification
			}
			InvXml.AddElem("cac:ClassifiedTaxCategory"); InvXml.IntoElem();
				if(lgmode_){
					InvXml.AddElem("cbc:ID","E");//  InvXml.AddAttrib("schemeID","UNCL5305");
					InvXml.AddElem("cbc:Percent","0.00");
				}
				else {
					if(*f(58,24)==def_btw) cstr_="S"; 
					else if(*f(58,24)) cstr_="S"; // AA in UBL
					else cstr_="Z";
					InvXml.AddElem("cbc:ID",cstr_); // InvXml.AddAttrib("schemeID","UNCL5305");
					InvXml.AddElem("cbc:Percent",Bedrag2Cstring((double)(*f(58,24)),2));
				}
				InvXml.AddElem("cac:TaxScheme");InvXml.IntoElem();
					InvXml.AddElem("cbc:ID","VAT");
				InvXml.OutOfElem(); // TaxScheme
			InvXml.OutOfElem(); // ClassifiedTaxCategory

    InvXml.OutOfElem(); // Item
		InvXml.AddElem("cac:Price"); InvXml.IntoElem();
		  if(lgmode_) {bd_=*f(58,47); if(bd_<0) bd_=-bd_;qlv_=1;} // geen negatieve ehprijs
			else{
				afrond_=1;	for(j=0;j<qlv_dec_;j++) afrond_/=10.;
				if(afrondingsfout_){ // BaseQuantity==aantal en PriceAmount == lijntotaal
					qlv_=Round((double)(*f(58,31)*factor_),afrond_);
					bd_=*d(58,35)*factor_;
					if(bd_<0){bd_=-bd_;qlv_=-qlv_;}
				}
				else{
				  qlv_=Round((double)(*f(58,31)),afrond_);
				  bd_=*d(58,35); if(qlv_) bd_=*d(58,35)/ qlv_;
					qlv_=1;
				}
			}
			bd_=Round(bd_,(double)(0.0001));
			InvXml.AddElem("cbc:PriceAmount",Bedrag2Cstring((double)(bd_),4)); InvXml.AddAttrib("currencyID","EUR");
      InvXml.AddElem("cbc:BaseQuantity",Bedrag2Cstring((double)(qlv_),2));
#if FLAGDEW
		  if(*f(58,8)) InvXml.AddAttrib("unitCode","KGM");
		  else InvXml.AddAttrib("unitCode","ZZ"); // InvXml.AddAttrib("unitCodeListID","UNECERec20"); 
#else
		  InvXml.AddAttrib("unitCode","ZZ"); // InvXml.AddAttrib("unitCodeListID","UNECERec20"); 
#endif
		InvXml.OutOfElem(); // Price
  InvXml.OutOfElem(); // InvoiceLine
  InvLineNr++; // lijnnummer verhogen
}





bool starts_with(const char* str, const char* prefix) {
    if (!str || !prefix) return false; 

    size_t lenpre = strlen(prefix);
    return strncmp(str, prefix, lenpre) == 0;
}

static int SendDoc2Peppol()
{
	const char* retVal_;
	const char* offset_;
	char btwstr_[21], outputbuf_[2000], outxml_[2000], cnflag_[4], filename_[71];
	int lenResult_, maxOutputbufLen_ = 2000, j, len_, k;
	int16 GEENdebug_;
	long btwnr_;
	CMarkup respxml_;
	CString cmd_, strResult_, errormsg_, cstr_, factuurId_, sentState_, scheme_, btwStr_, status_;

	zero(CodaboxRefID, sizeof CodaboxRefID);
	sysget(1284, 2, &GEENdebug_);
	if ((PeppolProviderOUT!=0 && *PeppolUidOUT == '\0') || *PeppolLicOUT == '\0') return -1; // Geen referentie meegegeven

	if (*CodaBoxFileName == '\0')
		return -1; // Geen filename, niet kunnen uitschrijven

	if (*l(KL_Stu2240,10)==999999999 || *l(KL_Stu2240,10)==0){
		if (fldlen(KL_Stu2240,137) && *s(KL_Stu2240,137)){
			zero(btwstr_, sizeof btwstr_);
		  copy("GLN", btwstr_, 3);
		  copy0(s(KL_Stu2240,137), &btwstr_[3], fldlen(KL_Stu2240,137));
		} 
		else return -1; // Enkel Belgische BTWnrs checken voorlopig
	}
	else {
		if (*(s(KL_Stu2240,10) + 3) & 0x40)
			*(s(KL_Stu2240,10) + 3)  &= 0xBF;
		
		btwnr_ = *l(KL_Stu2240,10);

		if (btwnr_ == 0)
			return -1; // Enkel Belgische BTWnrs checken voorlopig

		zero(btwstr_, sizeof btwstr_);

		if (KlantIDViaBtwNr) { // Via BTW-nr
			copy("BE", btwstr_, 2);
			btw_deco(&btwstr_[2], (long *)&btwnr_, 0);
		}
		else { // Via KBO-nr
			btw_deco(&btwstr_[0], &btwnr_, 0);

			if (btwstr_[9] == '\0') {
				btwstr_[0] = '0';
				btw_deco(&btwstr_[1], (long *)&btwnr_, 0);
			}
		}
	}

	switch(PeppolProviderOUT) {
		case 0:
			cmd_ = "IbanityUBLUpload|";
			cmd_ += LicIDCodaBox;
			cmd_ += "|";
			cmd_ += btwstr_;
			cmd_ += "|";

			if (alg_tot < 0)
				cmd_ += "YES";

			cmd_ += "|";
			cmd_ += CodaBoxFileName;
#if _DEBUG || FLAGDEM
			if(GEENdebug_==NO){cmd_ += "|"; cmd_ += "YES"; }
#endif
			strResult_ = JmsCmd(cmd_);
			lenResult_ = strResult_.GetLength();
			
			if (lenResult_ > maxOutputbufLen_)
				lenResult_ = maxOutputbufLen_; // Buffer overflow voorkomen

			zero(outputbuf_, maxOutputbufLen_);

			if (lenResult_ == 0 || strResult_.Left(3).Compare("@%!") == 0) {
				strResult_ = strResult_.Mid(3, maxOutputbufLen_ - 1); // Buffer overflow voorkomen owv afsluit-0
				lenResult_ = strResult_.GetLength();
				
				if (lenResult_ > maxOutputbufLen_)
					lenResult_ = maxOutputbufLen_; // Buffer overflow voorkomen
			}

			memcpy (outputbuf_, (char *)(LPCTSTR)strResult_, lenResult_);
			CnvJamaChar(outputbuf_, lenResult_, 1); // CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
			errormsg_ = CString(outputbuf_);
			j = JsonToXml(outxml_, sizeof outxml_, outputbuf_);
			cstr_ = "<Response> " + CString(outxml_) + " </Response> "; // Begin en einde toevoegen
			len_ = cstr_.GetLength();
			
			if (len_ > sizeof outxml_)
				len_ = sizeof outxml_;
			
			copy((char *)(LPCTSTR)cstr_, outxml_, len_);
			respxml_ = CMarkup(); 
			respxml_.SetDoc(outxml_);

			if (respxml_.IsWellFormed() != 1)
				goto bad_response;

			respxml_.ResetMainPos();

			if (respxml_.FindElem("Response") == false)
				goto bad_response;

			respxml_.IntoElem();
			respxml_.ResetMainPos();

			if (respxml_.FindElem("data") == false)
				goto bad_response;

			respxml_.IntoElem();
			respxml_.ResetMainPos();
			factuurId_ = respxml_.FindGetData("id");factuurId_.Trim();
			respxml_.ResetMainPos();

			if (respxml_.FindElem("attributes") == false)
				goto bad_response;

			respxml_.IntoElem();
			respxml_.ResetMainPos();
			sentState_ = respxml_.FindGetData("status");

			zero(s(8,76),fldlen(8,76));
			if (factuurId_.GetLength()) {
				len_ = factuurId_.GetLength();
				
				if (len_ > fldlen(8,76))
					len_ = fldlen(8,76);

				copy((char *)(LPCTSTR)factuurId_, CodaboxRefID, len_);

				if (alg_tot < 0)
					CodaboxRefID[49] = 1;
				else
					CodaboxRefID[49] = 0; // Markering CN of niet

				copy(CodaboxRefID, s(8,76), fldlen(8,76));
				*u(8,77) = 0;
				*u(8,78) = *u(25,2);

				if (sentState_.CompareNoCase("invalid") == 0) {
					*u(8,77) = 0;
					*u(8,78) = *u(25,2);
					respxml_.ResetMainPos();

					if (respxml_.FindElem("errors")) {
						respxml_.IntoElem();
						respxml_.ResetMainPos();
						errormsg_ = respxml_.FindGetData("detail");
						zero(outputbuf_, sizeof outputbuf_);
						lenResult_ = errormsg_.GetLength();
						
						if (lenResult_ > maxOutputbufLen_)
							lenResult_ = maxOutputbufLen_; // Buffer overflow voorkomen

						memcpy(outputbuf_, (char *)(LPCTSTR)errormsg_, lenResult_);
					}
				}
				else{
					if(*s(8,76)) {
						for(k = 0; k < 1; k++) { // voorlopig maar 1X checken... bij veel vertraging bij Codabox heeft het toch geen zin om te wachten
							Sleep(1000);

							if (*(s(8,76) + 49) == 1)
								j = CodaBoxCheckStatus(LicIDCodaBox, s(8,76), "YES",YES); // Op pos 49 CN of niet
							else
								j = CodaBoxCheckStatus(LicIDCodaBox, s(8,76), "NO",YES);

							if (j >= 0 && j <= 2)
								return 1;
						}
						return 1; // er vanuit gaan dat als je een referentie hebt gekregen, die wel verstuurd is of zal worden
					}

					return 0;
				}
			}

			break;

		case 1:
			zero(btwstr_, sizeof btwstr_);
			zero(cnflag_, sizeof cnflag_);
			zero(filename_, sizeof filename_);
			strcpy_s(filename_, sizeof filename_, CodaBoxFileName);
			retVal_ = PeppolSendDocument(btwstr_, cnflag_, filename_);

			std::ofstream out("debug.txt");
			out << "retVal_: " << retVal_ << "\n";
			lenResult_ = strlen(retVal_);
			
			if (lenResult_ > maxOutputbufLen_)
				lenResult_ = maxOutputbufLen_; // Buffer overflow voorkomen

			zero(outputbuf_, maxOutputbufLen_);
			memcpy (outputbuf_, (char *)(LPCTSTR)retVal_, lenResult_);
			CnvJamaChar(outputbuf_, lenResult_, 1); // CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
			out << "outputbuf_: " << outputbuf_ << "\n";

			if (!starts_with(retVal_, "OK - "))
				goto bad_response;

			offset_ = retVal_ + 5;
			strcpy_s(CodaboxRefID, sizeof CodaboxRefID, offset_);
			out << "CodaboxRefID: " << CodaboxRefID << "\n";
			out.close();
			copy(CodaboxRefID, s(8,76), fldlen(8,76));
			*u(8,77) = 0;
			*u(8,78) = *u(25,2);
			return 1;

			//if(*s(8,76)) {
			//	for(k = 0; k < 5; k++) {
			//		Sleep(1000);
			//		status_ = PeppolGetDocumentStatus(CodaboxRefID, "");

			//		if (status_ != "")
			//			return 1;
			//	}
			//}

			//return 0;
			break;
	}

bad_response:;
	scrnum=0;scrget(1,170);
	for(j=0;j<10;j++) scrifld(j+1,VarTextFmt(80,0),&outputbuf_[j*80]);
	scrifld(15,VarTextFmt(80,0),"Druk op F8 om verder te gaan");
	if(CallingOvl!=941)	scrupd(-1,0x81);
	else scrupd(-3,0); // vanuit kassa NIET stoppen om fout te tonen
	return 0;


}

static void InvLine2Xml(int lgmode_, int cn_flag_)
{
	int j,k;
	double bd_,factor_;
	long lbd_;
	short mm,dd,jaartal;
	char str_[100];
	CString cstr_;

	if(lgmode_) {if(*f(58,47)<0 && *f(58,31)>0) *f(58,31)=-*f(58,31);} // om negatieve ehprijs te voorkomen 
	else{ if(*d(58,35)<0 && *f(58,31)>0) *f(58,31)=-*f(58,31);} // om negatieve ehprijs te voorkomen 


	factor_=1.0; if(cn_flag_) factor_=-1.0;

	if(cn_flag_) InvXml.AddElem("cac:CreditNoteLine"); else InvXml.AddElem("cac:InvoiceLine"); InvXml.IntoElem();
	InvXml.AddElem("cbc:ID",InvLineNr);
	if(cn_flag_) InvXml.AddElem("cbc:CreditedQuantity",Bedrag2Cstring((double)(*f(58,31)*factor_),2)); 
	else InvXml.AddElem("cbc:InvoicedQuantity",Bedrag2Cstring((double)(*f(58,31)*factor_),2));
	InvXml.AddAttrib("unitCodeListID","UNECERec20"); InvXml.AddAttrib("unitCode","ZZ");
	if(lgmode_) cstr_=Bedrag2Cstring((double)(*f(58,47)*factor_),2); else cstr_=Bedrag2Cstring((double)(*d(58,35)*factor_),2);
	//	cstr_.Format("%.02f",(double)(*f(58,47)*factor_)); else cstr_.Format("%.02f",(double)(*d(58,35)*factor_)); 
	InvXml.AddElem("cbc:LineExtensionAmount",cstr_); InvXml.AddAttrib("currencyID","EUR");
	InvXml.AddElem("cac:Item"); InvXml.IntoElem();
	zero(str_,sizeof str_);copy(s(58,16),str_,fldlen(58,16)); InvXml.AddElem("cbc:Description",str_);
	zero(str_,sizeof str_);copy(s(58,16),str_,fldlen(58,16)); InvXml.AddElem("cbc:Name",str_);
	InvXml.AddElem("cac:SellersItemIdentification"); InvXml.IntoElem();
	zero(str_,sizeof str_);
#if FLAGSAS  // GRB-nummer meegeven ipv artikelcode
	if(lgmode_) copy("746000",str_,6);
	else if(*f(58,24)==0 && *s(KL_Stu2240,22)) copy("700001",str_,6);
	else if(*f(58,24)==0 && *s(KL_Stu2240,22)=='\0') copy("700000",str_,6);
	else if(*f(58,24)==6) copy("700100",str_,6);
	else if(*f(58,24)==12) copy("700200",str_,6);
	else copy("700300",str_,6);
#else
	copy(s(58,15),str_,fldlen(58,15)); 
#endif
	InvXml.AddElem("cbc:ID",str_);
	InvXml.OutOfElem(); //SellersItemIdentification
	InvXml.AddElem("cac:ClassifiedTaxCategory"); InvXml.IntoElem();
	if(lgmode_){
		InvXml.AddElem("cbc:ID","E"); InvXml.AddAttrib("schemeID","UNCL5305");
		InvXml.AddElem("cbc:Percent","0.00");
		InvXml.AddElem("cbc:Name","E");
	}
	else {
		if(*f(58,24)==def_btw) cstr_="S"; 
		else if(*f(58,24)) cstr_="AA"; 
		else cstr_="Z";
		if(*f(58,24)==def_btw) cstr_="S"; else cstr_="AA";
		InvXml.AddElem("cbc:ID",cstr_); InvXml.AddAttrib("schemeID","UNCL5305");
		InvXml.AddElem("cbc:Percent",Bedrag2Cstring((double)(*f(58,24)),2));
		for(k=0;k<BTWDIM-BTWDIV+1;k++) if(btw_pct[k]==*f(58,24)) break;
		cstr_.Format("%02d",(int)(k)); InvXml.AddElem("cbc:Name",cstr_);
	}
	InvXml.AddElem("cac:TaxScheme");InvXml.IntoElem();
	InvXml.AddElem("cbc:ID","VAT");
	InvXml.OutOfElem(); // TaxScheme
	InvXml.OutOfElem(); // ClassifiedTaxCategory
	InvXml.OutOfElem(); // Item
	InvXml.AddElem("cac:Price"); InvXml.IntoElem();
	if(lgmode_) {bd_=*f(58,47); if(bd_<0) bd_=-bd_;} // geen negatieve ehprijs
	else{bd_=*d(58,35); if(*f(58,31)) bd_=*d(58,35)/ *f(58,31);}
	bd_=Round(bd_,(double)(0.001));
	InvXml.AddElem("cbc:PriceAmount",Bedrag2Cstring((double)(bd_),3)); InvXml.AddAttrib("currencyID","EUR");
	//      InvXml.AddElem("cbc:BaseQuantity","1.00");
	InvXml.OutOfElem(); // Price
	InvXml.OutOfElem(); // InvoiceLine
	InvLineNr++; // lijnnummer verhogen
}


static int SendDoc2Boekhouder(void)
{
	int k;
	short mm,dd,jaartal;
	char mailadres_[51],str_[100];
	CString cstr_;

	zero(MailMergeData[0],sizeof MailMergeData); MailSaveAdres='N';
	zero(mailadres_,sizeof mailadres_); sysget(6500,50,mailadres_); if(mailadres_[0]=='\0') return 0;
	if(CodaBoxFileName[0]=='\0') return 0;
	jddate(ft_date,&jaartal,&mm,&dd);// factuurdatum
	zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage); // voor de veiligheid
	copy(CodaBoxFileName,MailMergeFileBijlage[0],sizeof CodaBoxFileName);
	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);
	zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate); copy("EXBKH",MailMergeSpecialTemplate,5);
	MailMergeFormaat=10; MailMergeTaal='\0';
	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){
			copy(mailadres_,MailMergeData[k],50); continue;
			}
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNAAM",12)==0) {
			zero(str_,sizeof str_); copy(s(25,3),str_,3);cstr_.Format("%s-%d-%05d.xml",str_,jaartal,ft_nr);
			copy((char *)(LPCTSTR)cstr_,MailMergeData[k],cstr_.GetLength());	continue;
		}
	}
#if _DEBUG
  k=SendMail(0); 
#endif

	k=SendMail(1); 
  return k;
}


static CString Bedrag2Cstring(double bd_, int decimals_)
{
	CString cstr_;
	int k;
	double afrond_=1;

	for(k=0;k<decimals_;k++) afrond_/=10.;
	cstr_=CString("");
	bd_=Round(bd_,afrond_);
	switch(decimals_){
	  case 1 :	cstr_.Format("%.01f",bd_); break;
		case 2 :	cstr_.Format("%.02f",bd_); break;
		case 3 :	cstr_.Format("%.03f",bd_); break;
		case 4 :	cstr_.Format("%.04f",bd_); break;
		default :	cstr_.Format("%f",bd_); break;
	}
	cstr_.Replace(",",".");
	return cstr_;
}



static int FileExist(char *FileName)
{
  if (GetFileAttributes(FileName)!=INVALID_FILE_ATTRIBUTES) return 1; else return 0;
}

static void CalcFactuur(void)
{
  int16 j,k;
  BEDRAG belastb_,tot_incl=0,tot_dif,lin_incl,kort_;
  float prx_,prx1_,bdf_,bd_accijn=0,prx_r,tot_afh_los,tot_akw,lg_btw_=0;
  flag tot_chk=YES;
  uint16 rec_,rec_lg_=0;
	char verv_term[5];
	  
//	if(fldlen(2,128) && *s(2,128)=='P' && *s(2,21)) tot_chk=NO;// niet bij electronische facturatie, want dan kan UBL fout zijn
	
  ft_afrond=(double)(0.01); FactuurMetCorrectie=NO;BdFactuurAfronding=0.;
  ft_date=*u(8,8); ft_nr=*u(8,2);
	copy(s(KL_Stu2240,13),verv_term,3); verv_term[3]='\0';
  k=0; if(verv_term[0]=='E') k=val(&verv_term[1]);
  if(k>5){/* DSB : einde maand + x dagen */
     verv_dt=dateadd(ft_date,"E0"); verv_dt+=k;
  }
  else verv_dt=dateadd(ft_date,verv_term);

  tot_kort=0;tot_leeg=0;semestbd=0;tot_akw=0;tot_subs=0;KM_heffing=0;
  tot_promo=0;trans_kost=0;tot_accijns=0;
	zero((char *)btw_CategorieUsed,sizeof btw_CategorieUsed);
  zero((char *)btw_bas,sizeof btw_bas);winst_bd=0;
  zero((char *)incl_bas,sizeof incl_bas);winst_bd=0;
  zero((char *)&kort_btw[0],sizeof kort_btw);
#if SUBSIDIE 
	copy(s(2,1),buf1000,fldlen(2,0));
#if !FLAG248 // controleren op subsidieadres bij bons als het bestaat 
	if(fldlen(2,52)==2 && *u(2,52) && *u(2,52)!=*u(2,1)){
		rec_=*u(2,1);
		*u(2,1)=*u(2,52);fasgeti(2);
		copy(s(2,1),buf1000,fldlen(2,0));
		fasinit(2); *u(2,1)=rec_;fasgeti(2);
	}
#endif
#if FLAG248 && !FT_HERAFDRUK & !FACT_RISTOURNO
	if(orig_klt && orig_klt!=*u(2,1)) {// controleren op originele klant
		rec_=*u(2,1);
		fasinit(2); *u(2,1)=orig_klt;fasgeti(2);
	  if(fldlen(2,52)==2 && *u(2,52) && *u(2,52)!=*u(2,1)){ // op subsidieklant van origineel als ie bestaat
		  *u(2,1)=*u(2,52);fasgeti(2);
		}
		copy(s(2,1),buf1000,fldlen(2,0));
		fasinit(2); *u(2,1)=rec_;fasgeti(2);
	}
#endif
#endif
#if KM_HEFFING || LEVERINGSKOST
	if(fldlen(8,46)) KM_heffing=*f(8,46);
#endif
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(test_line()==NO){
      rec_=*pu_58_1;init58(k,YES);ram2stu(k);*pu_58_1=rec_;
	  continue;
    }
#if FLAGGOU
	*f(58,31)=*f(58,13); // gewicht als aantal nemen
#endif
#if KORTTOT/* correctie bij kassa-facturen */
    if(*d(58,42)==0 && *pd_58_35) *d(58,42)=*pd_58_35;
#endif
    if(fldlen(58,47)) tot_leeg+=*f(58,47);/* NIET uitrekenen, maar totaal nemen */
		if(*f(58,47)) btw_CategorieUsed[0]=1;
    tot_afh_los=0;
#if AFHAALVERG
    if(fldlen(58,56))  tot_afh_los+=*f(58,56);
#endif
#if LOSVERGOED
    if(fldlen(58,59) && *f(58,20)) tot_afh_los+=*f(58,59);
#endif

#if PALET_KORTING
    if(fldlen(58,69)) tot_afh_los+=*f(58,68);
#endif
    prx_=*pf_58_20;
#if FLAGSEG
    prx_-=*f(58,22);/* korting in geld */
#endif
#if FLAGDUB  || FLAGSEG || FLAGFLI
    if(fldlen(58,60) && *s(58,60)=='J' && *pf_58_31){/* ehprijs = totaal bedrag */
      prx_/= *pf_58_31;
    }
#endif
    if(*i(58,34)==99) prx_=0;
#if BTWINCL
    lin_incl=round((double)(prx_* *pf_58_31)); tot_incl+=lin_incl;
    if(fldlen(58,27)){
      if(*s(58,27)=='J') prx_/=1.+*pf_58_24/100.;
      else if(test_line() && lin_incl) tot_chk=NO; // indien excl. lijn MET bedrag dan controle stoppen 
    }
	if(*f(58,21) && lin_incl) tot_chk=NO;
/* tot_chk=NO;    anders wordt leeggoed afgerond ! */
#endif
#if FLAGDU3 /* gratis artikels de accijns toch rekenen */
    if(prx_==0 && *i(58,34)!=99) prx_=*f(58,38);
#endif
    bd_accijn=*f(58,38);
    if(prx_>=0){/* bedrag accijns mag niet groter zijn de ehpr */
      if(bd_accijn>prx_) bd_accijn=prx_;
    }
    else {
      bd_accijn=-bd_accijn;
      if(bd_accijn<prx_) bd_accijn=prx_;
    }
#if FLAGPED
    prx_=prx_-*f(58,70) + *f(58,71);          /* paletkorting + toeslag bak */
    if(*f(58,70)!=0 || *f(58,71)!=0) tot_chk=NO;
#endif
    prx_r=prx_;
    if(fldlen(58,21)){
      if(*pf_58_21){
#ifdef ALB_flag
	if(*s(2,71)=='J') prx_=prx_ * (100.- *pf_58_21)/100.;
	else
#endif
#if FLAGDSV
	bdf_=1. + *pf_58_21/100.;
	if(bdf_) prx_=(prx_-bd_accijn)/bdf_+bd_accijn;
#else
	prx_=(prx_-bd_accijn)*(100.- *pf_58_21)/100.+bd_accijn;
#endif
#if FLAGVVL
	prx_=(long)(prx_*100+.5)/100.;
#endif
#if BTWINCL
	if(prx_)tot_chk=NO;
#endif
      }
#if EXTEND_KORT
      for(j=0;j<10;j++){
				if(prx_ && *(s(8,53)+j)=='J'){/* 53+54 als 1 string genomen */
        	  tot_afh_los+=*f(58,103+j*3);
	      }
      }
#endif
      if(fldlen(58,36) && prx_>0){
				bdf_=*f(58,36);
				if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
				prx_-=bdf_;
      }
      no_k_perc:;
#if FACT_PROMO
      tot_promo+=*f(58,94);
#if BTWINCL
      if(*f(58,94)) tot_chk=NO;
#endif
#endif
    }
    semestbd+=*f(58,53);
		belastb_=*pd_58_35;
    tot_accijns+=bd_accijn* *pf_58_31;
    if(fldlen(58,41)){
      bdf_=*f(58,41) * *pf_58_31;
      if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
#if KAS2GROOTH
      if(*i(58,34)!=99)
#endif
    	tot_akw+=bdf_;
    }
    j=btw_tab((BEDRAG)belastb_);
    btw_bas[j]+=round((double)(belastb_)); 
		if(*i(58,34)!=99  && (*s(58,16)!='*'|| !is_nul((double)(belastb_)) || *f(58,7))) btw_CategorieUsed[j]=1;
#if DEF_INPUT | SPLITS_BON
    if(*i(58,34)!=99 && (*s(58,16)!='*'|| !is_nul((double)(belastb_)) || *f(58,7)) && !(*pu_58_14 && *f(58,31)==0)) btw_CategorieUsed[j]=1; /* niet gebruikte lijnen skippen */
#endif
#if BTWINCL
    incl_bas[j]+=lin_incl;
#endif
//    *pd_58_35=belastb_;
#if TRANS_KOST
#if FLAGALS
   if(*l(58,26) && (fldlen(2,49)==0 || *s(2,49)!='J')){ // vraag GEEN handlingkost tellen
      for(j=0;j<8;j++) if(*l(58,26)==hk_omzgrb[j]) break;
      if(j<8){
	       j=0; if(*s(2,48)!='A') j=1; // if(*s(2,26)!='0') j=1;
				 if(*s(8,31)=='N') bdf_=hk_pct[j][1]; else bdf_=hk_pct[j][0];
	       if(*f(58,31)<0) trans_kost-=*pd_58_35 * bdf_/100.; else trans_kost+=*pd_58_35 * bdf_/100.; // bij terugname ook handlingkost tellen
      }
    }
#else
    if((*pd_58_35 || *i(58,34)==99) && *ps_58_16!='*' && *pu_58_14 && *ps_58_62!='P'){
      fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
      bdf_=*pf_58_31* *f(6,84);
      if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
      trans_kost+=bdf_;
      if(fldlen(8,31) && *s(8,31)!='J') trans_kost=0;/* geen rekenen */
    }
#endif
#endif
#if KORTTOT
    j=btw_tab((BEDRAG)belastb_);
		kort_=*d(58,42)-*pd_58_35; kort_=round(kort_);
    kort_btw[j]+=kort_; //*d(58,42)-*pd_58_35;
    tot_kort+=kort_; // *d(58,42)-*pd_58_35;
#endif
#if SUBSIDIE
		tot_subs+=*f(58,29);
#endif
    stu2ram(k);
  }

#if TRANS_KOST/* transactie-kost aan 21% goederen tellen */
  if(trans_kost){
    trans_kost=round((double)trans_kost);
    fasinit(58); belastb_=trans_kost;
    *pf_58_24=def_btw;
    if(*s(8,26)=='J') *pf_58_24=0;
    j=btw_tab((BEDRAG)belastb_);
    btw_bas[j]+=belastb_; btw_CategorieUsed[j]=1;
    tot_chk=NO;
  }
#endif
#if LEVERINGSKOST/* transactie-kost aan 21% goederen tellen */
  if(KM_heffing){
    KM_heffing=round((double)KM_heffing);
		fasinit(6);*u(6,1)=RecLevKostArt; 
		if(fasgeti(6)==0) BtwLeveringskost=*f(6,28);
    fasinit(58); belastb_=KM_heffing;
    *pf_58_24=BtwLeveringskost;
    j=btw_tab((BEDRAG)belastb_);btw_CategorieUsed[j]=1; 
    btw_bas[j]+=belastb_;
    tot_chk=NO;
  }
#endif
#if DRI_flag/* verpakking 21% als goederen tellen */
  if(tot_leeg){
    tot_leeg=round((double)tot_leeg);
    fasinit(58);*f(58,24)=lg_btw_; belastb_=tot_leeg;
    j=btw_tab((BEDRAG)belastb_);
    if(fldlen(58,33)) *s(58,33)=j+btw_kol;
    btw_bas[j]+=belastb_;btw_CategorieUsed[j]=1;
    tot_chk=NO;
  }
#endif
  belastbt=0;
  for(k=0;k<BTWDIM-BTWDIV;k++){
#if BTWINCL
    if(tot_chk){
//      btw_bas[k]=round((double)(incl_bas[k]/(1.+btw_pct[k]/100.)));
    }
#endif
    belastbt+=btw_bas[k];
  }
  belastbt=round((double)(belastbt));
  btw_tot=0;
  for(k=0;k<BTWDIM;k++){
    btw_bd[k]=round((double)(btw_bas[k]*btw_pct[k])/100.);
    btw_tot+=btw_bd[k];
  }
  tot_leeg=round((double)tot_leeg); if(tot_leeg) btw_CategorieUsed[0]=1;
  tot_accijns=round((double)tot_accijns);
  tot_subs=round((double)tot_subs);
  tot_incl+=round((double)(tot_leeg-tot_subs));
  alg_tot=belastbt+btw_tot+tot_leeg-tot_subs;

#if DRI_flag/* verpakking zit al in belastbaar */
  alg_tot-=tot_leeg;
#endif
#if BTWINCL
  if(tot_chk){
    tot_dif=tot_incl-alg_tot;
		tot_dif=round(tot_dif);
    if(tot_dif){/* eerst proberen op default btw % */
			FactuurMetCorrectie=YES;BdFactuurAfronding=tot_dif;
	
			for(k=0;k<BTWDIM;k++) if(!is_nul(round((double)(incl_bas[k]-btw_bd[k]-btw_bas[k]))))  break;
  //    for(k=0;k<BTWDIM;k++) if(btw_bd[k] && btw_pct[k]==def_btw) break; //  hier niet wordt in header xml verrekent
      if(k>=BTWDIM){
				for(k=0;k<BTWDIM;k++) if(btw_bd[k] && btw_pct[k]!=0) break;
      }
      if(k<BTWDIM){
        int kk_,bestidx_; double bestres_,res_,linc_,factor_;
        btw_bas[k]+=tot_dif;
        /* lijnniveau-correctie: cent op de lijn met de grootste afrondingsrest.
           Voor verse facturen heeft DRK0240 de lijnen al gecorrigeerd (tot_dif==0,
           dit blok draait dan niet). Voor legacy/herafdruk lijnen corrigeren we hier
           dezelfde manier, zodat de "Afronding"-AllowanceCharge niet meer nodig is. */
        bestidx_=-1; bestres_=-1.e9;
        for(kk_=0;kk_<max_line;kk_++){
          ram2stu(kk_);
          if(test_line()==NO) continue;
          if(*i(58,34)==99 || is_nul((double)(*d(58,35)))) continue;
          if(btw_tab((BEDRAG)(*d(58,35)))!=k) continue;
					factor_=1.; if(*d(58,35)<0) factor_=-1.;
          linc_=round((double)(*f(58,20) * *f(58,31)))*factor_;
          res_=linc_/(1.+ *f(58,24)/100.) - *d(58,35)*factor_;
          if(res_>bestres_){bestres_=res_; bestidx_=kk_;}
        }
        if(bestidx_>=0){/* echte lijn gevonden -> geen afronding-AllowanceCharge */
          belastbt+=tot_dif; alg_tot+=tot_dif;
          ram2stu(bestidx_); 
					*d(58,35)+=tot_dif; 
					if(*f(58,31) && *f(58,21)==0) *f(58,23)=valu_cnv(def_munt,def_munt,(double)(*d(58,35)/ *f(58,31)),prx_afrond); // ehprijs ook corrigeren
					stu2ram(bestidx_);
          FactuurMetCorrectie=NO; BdFactuurAfronding=0.;
        }
      }
    }
  }
#endif
  kredietbp_bd=0; 
#if KREDIETBEPERK
	bdf_=0;
  if(alg_tot>0 &&  *s(8,22)!='J' && (fldlen(8,21)==0 || *f(8,21)<alg_tot)){
#ifdef KREDIETBP_PCT
		bdf_=KREDIETBP_PCT;
#else 
		if(fldlen(2,14)){
			 if(fldlen(2,14)==4) bdf_=*f(2,14); else bdf_=*i(2,14);
		}
#endif
#if FLAGPWH
		if(*s(2,44)=='J') bdf_=0; // GEEN kredietbeperking
#endif
		kredietbp_bd=round((double)(alg_tot* bdf_)/100.);
	}
#endif
  disk_bd=0;
#if DISCONTO
  if(disk_dt==0 && len2_14){
    copy(s(2,15),verv_term,3);
    disk_dt=dateadd(ft_date,verv_term);
  }
  if(len2_14 && (alg_tot>0)){
    if(fldlen(2,14)==4) bdf_=*f(2,14); else bdf_=*i(2,14);
#if FLAGPMC
		bdf_=4.; // VAST 4% kredietbeperking 
#endif
    disk_bd=alg_tot;
    if(disk_ei) disk_bd-=(btw_tot + tot_leeg);
#if DISC_NOACC
    disk_bd-=tot_accijns;
#endif
    disk_bd=round((double)(disk_bd* bdf_)/100.);
    if(disk_bd<0) disk_bd=0;
  }
#endif
}

static BEDRAG round(double value_) // zelfde round nemen als ovl240 owv verschillen
{
  double bd_;
						
  bd_=valu_cnv(def_munt,def_munt,value_,ft_afrond);
  return (BEDRAG)(bd_);
}

static void ram2stu(int16 lin_)
{
  copy(ram+(lin_*stu58_len),s(58,1),stu58_len);
}
						
static void stu2ram(int16 lin_)
{
  copy(s(58,1),ram+(lin_*stu58_len),stu58_len);
}


static CString Date2String(unsigned int date_,int mode_)
{
   char txtbuffer_[100];

   memset(txtbuffer_,0,sizeof txtbuffer_);
   if(date_) datefm(txtbuffer_,date_,mode_);

   return CString(txtbuffer_);
}

static void Double2Text(double getal, char *s, int len, char points, int digits) // conv_getal uit kassa
{
  char j,started,sign,show0ap;
  int dig_count;
  long l;
  float scale;
 
  sign=' '; show0ap=NO;
  if (digits & 0x80) {
    show0ap=YES;
    digits&=0x7F;
    if (digits && (len-digits<=5)) points&=0xFE;
  }
  if (getal<0) {sign='-'; getal=-getal;}
  scale=1.;
  for (j=0; j<digits; j++) scale*=10.;
  getal*=scale; l=(long)(getal+.5);
  if (l==0 && (points&2)) goto zero_sup;
  if (show0ap && digits>0) started=YES;
  else started=NO;
  dig_count=0;
  while (len>0) {
    j=(char)(l%10); l/=10;
    if (started && dig_count==digits) {
      *(s+len-1)=','; len--;
    }
    if (dig_count==digits) started=YES;
    if ((points & 1) && (dig_count==digits+3 || dig_count==digits+6)) {
      *(s+len-1)='.'; len--;
      if (len==0) break;
    }
    if (!started && j) started=YES;
    if (started) {
      *(s+len-1)='0'+j; len--;
    }
    if (l==0 && dig_count>=digits) break;
    dig_count++;
  }
 zero_sup:;
  if ((len>0) && (sign>' ')) *(s-1+len--)=sign;
  if (!(points&4)) while (len-->0) *(s+len)=' ';
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
      p=b;
      for (i=0; i<len; i++) {
        if (b[i]>=' ' && b[i]<0x80) *p++=b[i];
        else if (b[i]>=0x80 && b[i]<0xD0) {
          *p++=jamasci[b[i]-0x80][0];
          if (jamasci[b[i]-0x80][1]>0) p--;
        }
      }
      *p=0;
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
	result_=CString(b); result_.TrimLeft();
endsr:;
	return result_;
}



// STANDAARD routines


static CString arr2cstr(char *ps, int max_len)
{
  CString cstr="";
  int len_=0;
	  
  while (len_<max_len && *ps!=0) {cstr+=(TCHAR)*ps++;len_++;}

  return cstr;
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


static double Round(double getal, double round)
{
  long lbd_;
                                
  if (round==0) round=0.0001; // om vieze dinges ver na komma weg te doen 
	if((getal>=100000 || getal<=-100000) && round<0.01) round=0.01;
  if (getal<0.) getal-=(round/2.);
  else getal+=(round/2.);
  getal/=round;
  lbd_=(long)getal;
  return (double) (lbd_*round);
}
 
static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_)
{
  int len_;

  if(cstr_.GetLength()) len_=cstr2arr(cstr_,pbuf_,maxlen_);
  else len_=0;
  if(len_>=maxlen_) len_--; pbuf_[len_]='\0'; 

  return pbuf_;
}

static int is_nul(double bd_)
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static void fileopen(int16 nr_)
{
  int16 stu_;
  char filename[15];
								
  nr_--;
  sysget(300+17*nr_,15,filename);
  sysget(315+17*nr_,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(errnum=fasopen(filename,0)) ovlexit(-1);
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  }
}
 
static double str2dbl(char *s)
{
  bool negative=false,decim=false;
  double fuval=0,coef=1.;

  while(1){
    if(*s==' ');
		else if(*s=='+') negative=false;
    else if(*s=='-') negative=true;
    else if(*s>='0' && *s<='9'){
      if(decim){
        coef=coef/(float)10.;
        fuval+=(*s-'0')*coef;
      }
      else fuval=fuval*10+*s-'0';
    }
    else if(*s=='.' || *s==',') decim=true; 
    else break;
		s++;
  }
  if(negative) fuval=-fuval;
  return fuval;
}

static void InitLoad(void)
{
  int16 j,k,z;
  char *pdum_,str_[10];

  InitConvertTab();

  fasunlck(0);
  fileopen(1);
  fileopen(2); 
  fileopen(3);
  fileopen(4);
  fileopen(6); 
	fileopen(8);
#if CONTRACT | HISTOR
  fileopen(9);
#endif
  ram=RamBon;
  ram_size=125000;
#ifdef DOUBLE_FACT
  ram_size*=DOUBLE_FACT;
#endif
  if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;
// ZEKER NIET HIER	zeroL(ram,ram_size);
  stu58_len=fldlen(58,0);max_line=ram_size/stu58_len;
  sysget(3636,4,&grb_notf);

  sysget(784,4,&kltcent);
  for(k=0;k<DF_GRB;k++) sysget(788+k*4,4,&df_rek[k][0]);
  sysget( 294,4,def_munt);
  sysget(2166,2,&journl);
#if KN_JOURNL/* apart credietnota journaal */
  journl++;
#endif

#ifdef BOEK_JOURNL/* afwijkend journaal */
  journl=BOEK_JOURNL;
#endif
  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);



  sysget(2164,2,&disk_ei);
  sysget(2172,2,&btw_kol);
  sysget(1048,32,&btw_pct[0]);
  sysget(1080,4,&max_btw);
  sysget(2228,2,&b2228);
  sysget(1084,4,&def_btw);
  sysget(2991,2,&RecLevKostArt);
	sysget(3192,50,ExtraBijlageFactuurmail);
  sysget(3604,2,&b3604);
  sysget(3606,2,&b3606);
  sysget(3608,2,def_ext);
  sysget(3894,2,&sys3894);def_inc='N';
#if FLAGALS
  sysget(5350,32,(char *)&hk_omzgrb[0]);
  sysget(5382,8,(char *)&hk_kostgrb[0]);
  sysget(5390,16,(char *)&hk_pct[0][0]);
#endif
#if FLAGSAS // om te vermijden dat die 2x in de bkh-map komt owv ovl2141
	copy("..\\factubl\\",OutputMapUbl,11);
#else
  sysget(19500,50,OutputMapUbl); 
#endif
	sysget(20306,40,UidCodaBox); 


	sysget(20346,15,PwCodaBox); 
	sysget(20361,40,LicIDCodaBox);

	sysget(1282,2,&PeppolProviderOUT);
	sysget(20306,40,PeppolUidOUT); 
	sysget(20346,15,PeppolPwOUT); 
	sysget(20361,60,PeppolLicOUT); 
	sysget(21965,40,PeppolFirmaNaam);

	firmbtwnr=0;z=0;j=-1;
  for(k=0;k<15;k++){
    if(firma[86+k]=='\0') break;
    if(firma[86+k]>='0' && firma[86+k]<='9'){
      z++;if(j==-1) j=k;
    }
  }
  for(k=0;k<15;k++){
    if(firma[86+k]=='\0') break;
    if(firma[86+k]>='0' && firma[86+k]<='9'){
      if(k>j || z<=10){/* enkel laatste 10 cijfers nemen */
	firmbtwnr=(firmbtwnr*10) + (firma[86+k]-'0');
      }
    }
  }
	if(firmbtwnr>1000000000) {
    firmbtwnr-= 1000000000L;
  	copy((char *)(&firmbtwnr), str_, 4);
	  str_[3] |= 0x80; copy(str_, (char *)(&firmbtwnr), 4);
	}

  fieldspc(58,20,&pdum_,fmt);
  k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;

  ps_2_3=s(2,3);len2_3=fldlen(2,3);
  len2_14=fldlen(2,14);
  pu_2_1=u(2,1);
  pu_6_1=u(6,1);
  ps_6_3=s(6,3);len6_3=fldlen(6,3);
  ps_8_23=s(8,23); len8_23=fldlen(8,23);
  pu_8_28=u(8,28);
  pu_58_1=u(58,1);
  pu_58_14=u(58,14);
  len58_15=fldlen(58,15);
  ps_58_15=s(58,15);
  ps_58_16=s(58,16);
  pf_58_20=f(58,20);
  pf_58_21=f(58,21);
  pf_58_24=f(58,24);
  ps_58_25=s(58,25);len58_25=fldlen(58,25);
  pf_58_31=f(58,31);
  len58_35=fldlen(58,35); pd_58_35=d(58,35);
  ps_58_62=s(58,62);len58_62=fldlen(58,62);
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

static char* GetString(int stunr, int fldnr, bool JamasciDecodeFlag, int MaxLen)
{
  int i;
  unsigned char Desc[100]; // zeker genoeg nemen,
  unsigned char *p, *b;
  int len=fieldspc(stunr,fldnr,&b,Desc);
  p=GetStringBuf;
  *p=0;
  if (len && (Desc[1]&0xC0)!=0) {
    switch (Desc[1]&0x38) {
      case 0x10: // getal
        frmtnum((char *)GetStringBuf,Desc[1],d(stunr,fldnr),Desc[2],Desc[3],*(UNALIGNED short int *)&Desc[4]);
        len=strlen((char *)GetStringBuf);
        while (len>0) {
          if (GetStringBuf[len-1]>' ') break;
          GetStringBuf[len-1]=0;
          len--;
        }
        for (i=0; i<len; i++) if (GetStringBuf[i]>' ') break;
        if (i>0) memmove(GetStringBuf,&GetStringBuf[i],len-i+1);
        break;
      case 0x08:  // string
        b=(unsigned char *)s(stunr,fldnr);
        for (int i=0; i<len; i++) {
          if (!b[i]) break;
          *p++=b[i];
          if (JamasciDecodeFlag) {
            if (b[i]>=0x80 && b[i]<0xD0) {
              p--;
              if (!jamasci[b[i]-0x80][1]) *p++=jamasci[b[i]-0x80][0];
            }
          }
        }
        *p=0;
        break;
      case 0x18:
				btw_deco((char *)GetStringBuf,l(stunr,fldnr),YES);
        break;
    }
  }
  return (char *)GetStringBuf;
}


static int test_line(void)
{
  if(*ps_58_15 || *ps_58_16 || *pf_58_20) return YES;
  return NO;
}

static int16 btw_tab(double bd_)
{
  int16 k;
  float btw_;

  btw_=Round((double)(*pf_58_24),ft_afrond);
  for(k=0;k<BTWDIM-BTWDIV;k++){
    if(btw_==btw_pct[k]) break;
  }
  return k;
}

static void init58(int16 start_,int16 mode_)
{
  int16 k;

  fasinit(58);
  *pf_58_24=def_btw;
  if(fldlen(58,27)) *s(58,27)=def_inc;
  if(len58_25) copy(def_ext,ps_58_25,len58_25);
  *pf_58_21=*f(2,18);
  for(k=start_;k<max_line;k++) {stu2ram(k);if(mode_) break;}
}