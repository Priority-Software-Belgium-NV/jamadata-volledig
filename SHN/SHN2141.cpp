
/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "Shlobj.h"
#include <direct.h>
extern "C" char* SHN2141GetD() {return &zzvw;}

extern "C" void SvcErr(int nr, char *text);
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" int Fld2String(int stunr, int fldnr, char *OutBuffer, int MaxLen);
extern "C" void MakeStructMed(char *pd, uint16 refnr_); // 'kkk/kkff/fffcc'   K(lant) F(aktnr) C(heck) 

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

extern "C" char SHN2141dat[] = "SHN2141  00:01 08/10/20 (c) Jamadata"; // module om factuur uit te schrijven in UBL-formaat (formaat YUKI)


// FLAGBCC : Apart journaal voor kassafacturen !!!!


/* commando's mee te geven in j.bat

upsys32 sys.* s 19500 50 ..\share\yuki\fas\
md ..\share
md ..\share\Yuki
md ..\share\Yuki\fas

*/

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DIM8            100
#define DIM58           800
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

#undef  DOUBLE_FACT     
#define DOUBLE_FACT     2/* verdubbel-factor nodig voor grooth.factuur */

// h-file --------------------------------

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us62[]  = {7,0xC8,62,0,0,0,0};
static char fm_os56[]  = {7,0x88,56,0,0,0,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};

static void CalcFactuur(void);
static void ExportFactuur2XML(void); // UBL-formaat
static void InvLine2Xml(int lgmode_, int cn_flag_);
static void InitLoad(void);
static void InitConvertTab(void);  // komt uit JMS
static int LoadFactuur(char *ftfile_);// laden factuur van FtKopie  

static void ram2stu(int16 lin_);
static void stu2ram(int16 lin_);
static void init58(int16 start_,int16 mode_);
static int test_line(void);
static int16 btw_tab(double bd_);
static double round(double value_);
static long makegrb(void);

static CString arr2cstr(char *ps, int max_len);
static int bcopy0(char *ps_, char *pd_, int maxlen_);
static int copy0(char *ps,char *pd,int max);
static CString Bedrag2Cstring(double bd_, int decimals_);
static void Double2Text(double getal, char *s, int len, char points, int digits);
static void fileopen(int16 nr_);
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
static char *ram,def_inc,def_ext[2],fmt[40],OutputMapUbl[51],b3598[6];
static long ram_size,firmbtwnr;
static int16 stu58_len,max_line,def_qfact,lvcd,klcd,prxnr,journl,vm_munt;
static uint16 ft_date,ft_nr,sys3894,btw_kol,verv_dt,BetaaldViaBC;
static int LastKrtNr,  InvLineNr; 
static char ICSBTab[256];
static flag  disk_ei;
static float tot_kort,tot_leeg,tot_ex_btw;
static float def_btw,btw_glob,btw_pct[BTWDIM],max_btw;
static BEDRAG alg_tot,belastbt,btw_tot,btw_bas[BTWDIM],incl_bas[BTWDIM],disk_bd,kredietbp_bd,tot_subs;
static BEDRAG btw_bd[BTWDIM],semestbd,winst_bd,v_alg_tot,tot_promo,kort_btw[BTWDIM];
static double ealg_tot,ft_afrond,prx_afrond,klt_saldo,tot_accijns;
static double omzet,osalkas,tot_voors,trans_kost;
static char sortbuf[1000],def_munt[4],ft_munt[4],firma[350];
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


extern "C" void SHN2141cod(int16 parmval)
{
  CMarkup Xml;
  int Status;
  CString cstr_;
	CFile cfile_;

	InitLoad();
	if(parmval==1){ // eerst factuur laden van FtKopie
  	if(LoadFactuur(SelectedFileName)==NO){retcall=0; ovlexit(-1);}
	}
	CalcFactuur();
	ExportFactuur2XML();
	retcall=1; ovlexit(-1);
	 
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

static void ExportFactuur2XML(void) // UBL-formaat
{
  CMarkup Klt;
  int j,k,lgmode_,cn_flag_;
	double bd_,factor_,tot_lgpl_;
	long lbd_;
	short mm,dd,jaartal;
	char sys3896[6],str_[100],code_journaal_[3];
  unsigned char *p=0;
  CString PdfName,cstr_,strBase64;
	CFile cfile_;

	zero(code_journaal_,3);
#if FLAGBCC
	copy("VF",code_journaal_,2);
	fasinit(4);*s(4,2)=14; *u(4,4)=ft_date; *u(4,3)=ft_nr;
	if(faskeyi(4,5,0)==0) copy("KF",code_journaal_,2);
#endif


	scrget(1,6);scrupd(-3,0);
	cn_flag_=NO; factor_=1.0; if(alg_tot /* belastbt*/<0){cn_flag_=YES; factor_=-1.0;}
	InvXml = CMarkup(); // uit veiligheid om te clearen na lange factuur
	InvXml = CMarkup("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\x0D\x0A");
	
  if(cn_flag_){
		InvXml.AddElem("inv:CreditNote");
	  InvXml.SetAttrib("xmlns:inv","urn:oasis:names:specification:ubl:schema:xsd:CreditNote-2");
	}
	else{
		InvXml.AddElem("inv:Invoice");
		InvXml.SetAttrib("xmlns:inv","urn:oasis:names:specification:ubl:schema:xsd:Invoice-2");
	}
	InvXml.SetAttrib("xmlns:ccts","urn:oasis:names:specification:ubl:schema:xsd:CoreComponentParameters-2");
	InvXml.SetAttrib("xmlns:stat","urn:oasis:names:specification:ubl:schema:xsd:DocumentStatusCode-1.0");
	InvXml.SetAttrib("xmlns:cbc","urn:oasis:names:specification:ubl:schema:xsd:CommonBasicComponents-2");
	InvXml.SetAttrib("xmlns:cac","urn:oasis:names:specification:ubl:schema:xsd:CommonAggregateComponents-2");	
  InvXml.SetAttrib("xmlns:udt","urn:un:unece:uncefact:data:specification:UnqualifiedDataTypesSchemaModule:2");
	InvXml.SetAttrib("xmlns:ext","urn:oasis:names:specification:ubl:schema:xsd:CommonExtensionComponents-2");
	InvXml.SetAttrib("xmlns:qdt","urn:oasis:names:specification:ubl:schema:xsd:QualifiedDatatypes-2");
	// InvXml.SetAttrib("xmlns:xsd","http://www.w3.org/2001/XMLSchema");
  // InvXml.SetAttrib("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");


	InvXml.IntoElem();
//		InvXml.AddElem("cbc:CustomizationID","Yuki-UBL 1.0");
	  InvXml.AddElem("cbc:UBLVersionID","2.1");
		if(cn_flag_){
		  InvXml.AddElem("cbc:CustomizationID","urn:www.cenbii.eu:transaction:biitrns014:ver2.0:extended:urn:www.peppol.eu:bis:peppol5a:ver2.0");
		}
		else{
		  InvXml.AddElem("cbc:CustomizationID","urn:www.cenbii.eu:transaction:biitrns010:ver2.0:extended:urn:www.peppol.eu:bis:peppol5a:ver2.0");
		}
	//	InvXml.AddElem("cbc:CustomizationID","urn:www.cenbii.eu:transaction:biitrns010:ver2.0:partly:urn:www.e-fff.be:peppol:bis:peppol4a:ver2.0");
//		InvXml.AddElem("cbc:ProfileID","urn:www.cenbii.eu:profile:bii04:ver1.0");
		InvXml.AddElem("cbc:ProfileID","E-FFF.BE urn:www.cenbii.eu:profile:bii04:ver2.0");
    jddate(ft_date,&jaartal,&mm,&dd);// factuurdatum
  	cstr_.Format("%d-%s%05d",jaartal,code_journaal_,ft_nr); InvXml.AddElem("cbc:ID",cstr_);
		cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:IssueDate",cstr_);
//		jddate(verv_dt,&jaartal,&mm,&dd);// vervaldatum 
//		cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:DueDate",cstr_);
		if(cn_flag_) InvXml.AddElem("cbc:CreditNoteTypeCode",381);	else InvXml.AddElem("cbc:InvoiceTypeCode",380);	InvXml.SetAttrib("listID","UNCL1001");
		if(*s(8,25)){zero(str_,sizeof str_); copy(s(8,25),str_,fldlen(8,25));InvXml.AddElem("cbc:Note",str_);}
    jddate(ft_date,&jaartal,&mm,&dd);// factuurdatum
		if(!cn_flag_){cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:TaxPointDate",cstr_);}
		InvXml.AddElem("cbc:DocumentCurrencyCode","EUR");	InvXml.SetAttrib("listID","ISO4217");
		InvLineNr=0; tot_lgpl_=0;
		for(k=0;k<max_line;k++){ // aantal lijnen bepalen
      ram2stu(k);
      if(test_line()){
#if DEF_INPUT | SPLITS_BON
        if(*pu_58_14 && *f(58,31)==0) continue;/* niet gebruikte lijnen skippen */
#endif
				if(*f(58,47)>0) tot_lgpl_+=*f(58,47);
				if(*i(58,34)==99) continue; // geen leeggoed
				InvLineNr++;
  		}
		}
    if(tot_leeg){
			InvLineNr++;
			if(tot_leeg!=tot_lgpl_) InvLineNr++;
		}
		InvXml.AddElem("cbc:LineCountNumeric",InvLineNr);

		InvXml.AddElem("cac:AdditionalDocumentReference");InvXml.IntoElem();
		  jddate(ft_date,&jaartal,&mm,&dd);// factuurdatum
		  zero(str_,sizeof str_); copy(s(25,3),str_,3); cstr_.Format("%s-%d-%s%05d",str_,jaartal,code_journaal_,ft_nr);InvXml.AddElem("cbc:ID",cstr_);
      InvXml.AddElem("cbc:DocumentType","CommercialInvoice");
      InvXml.AddElem("cac:Attachment");InvXml.IntoElem();

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
				InvXml.SetAttrib("encodingCode","Base64");
			}
			else{
				cstr_.Format("Probleem met uitschrijven factuur %d (geen PDF). Schrijf deze opnieuw uit!",ft_nr);
				DisplayWarning((char *)(LPCTSTR)(cstr_),605,0);
			}
			InvXml.OutOfElem();
		InvXml.OutOfElem();

		InvXml.AddElem("cac:AccountingSupplierParty");InvXml.IntoElem();
// niet gebruikt      InvXml.AddElem("cbc:CustomerAssignedAccountID","");
      InvXml.AddElem("cac:Party");InvXml.IntoElem();
			zero(str_,sizeof str_); if(firmbtwnr){copy("BE",str_,2);btw_deco(&str_[2],&firmbtwnr,0);}
        InvXml.AddElem("cbc:EndpointID",str_);	InvXml.AddAttrib("schemeID","BE:VAT");
				InvXml.AddElem("cac:PartyIdentification"); InvXml.IntoElem();
				zero(str_,sizeof str_); if(firmbtwnr){btw_deco(&str_[0],&firmbtwnr,0);}
          InvXml.AddElem("cbc:ID",str_);
					InvXml.AddAttrib("schemeAgencyID","BE");
					InvXml.AddAttrib("schemeAgencyName","KBO");
					InvXml.AddAttrib("schemeURI","http://www.e-FFF.be/KBO");
				InvXml.OutOfElem(); // PartyIdentification
				InvXml.AddElem("cac:PartyName");InvXml.IntoElem();
          InvXml.AddElem("cbc:Name",&firma[0]);
				InvXml.OutOfElem(); // Partyname
				InvXml.AddElem("cac:PostalAddress");InvXml.IntoElem();
          InvXml.AddElem("cbc:StreetName",&firma[31]);
          InvXml.AddElem("cbc:CityName",&firma[65]);
          InvXml.AddElem("cbc:PostalZone",&firma[57]);
					InvXml.AddElem("cac:Country"); InvXml.IntoElem();
            InvXml.AddElem("cbc:IdentificationCode","BE");
						InvXml.AddAttrib("listID","ISO3166-1:Alpha2");
					InvXml.OutOfElem(); // Country
				InvXml.OutOfElem(); // Postaladdres
				InvXml.AddElem("cac:PartyTaxScheme"); InvXml.IntoElem();
		  		zero(str_,sizeof str_); if(firmbtwnr){copy("BE",str_,2);btw_deco(&str_[2],&firmbtwnr,0);}
          InvXml.AddElem("cbc:CompanyID",str_);
					InvXml.AddAttrib("schemeID","BE:VAT");
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
          InvXml.AddElem("cbc:RegistrationName",&firma[0]);
					zero(str_,sizeof str_); if(firmbtwnr){copy("BE",str_,2);btw_deco(&str_[2],&firmbtwnr,0);}
          InvXml.AddElem("cbc:CompanyID",str_);	InvXml.AddAttrib("schemeID","BE:VAT"); InvXml.AddAttrib("schemeName","KBO");
					InvXml.AddElem("cac:RegistrationAddress"); InvXml.IntoElem();
	// NIET					InvXml.AddElem("cbc:StreetName",&firma[31]);
						InvXml.AddElem("cbc:CityName",&firma[65]);
						InvXml.AddElem("cbc:PostalZone",&firma[57]);
						InvXml.AddElem("cac:Country"); InvXml.IntoElem();
							InvXml.AddElem("cbc:IdentificationCode","BE");
							InvXml.AddAttrib("listID","ISO3166-1:Alpha2");
						InvXml.OutOfElem(); // Country
					InvXml.OutOfElem(); // RegistrationAdres
				InvXml.OutOfElem(); // PartyLegalEntity
			InvXml.OutOfElem(); // Party
		InvXml.OutOfElem(); // AccountingSupplierParty

		InvXml.AddElem("cac:AccountingCustomerParty");InvXml.IntoElem();
		  if(fldlen(2,2)){zero(str_,sizeof str_); copy(s(2,2),str_,fldlen(2,2));InvXml.AddElem("cbc:CustomerAssignedAccountID",str_);}
		  else {lbd_=*u(2,1);InvXml.AddElem("cbc:CustomerAssignedAccountID",lbd_);}
      InvXml.AddElem("cac:Party");InvXml.IntoElem();
			  zero(str_,sizeof str_); if(firmbtwnr){copy("BE",str_,2);btw_deco(&str_[2],l(2,10),0);}
        InvXml.AddElem("cbc:EndpointID",str_);	InvXml.AddAttrib("schemeID","BE:VAT");
				InvXml.AddElem("cac:PartyIdentification"); InvXml.IntoElem();
				  zero(str_,sizeof str_); if(*l(2,10)){btw_deco(&str_[0],l(2,10),0);}
          InvXml.AddElem("cbc:ID",str_);
					InvXml.AddAttrib("schemeAgencyID","BE");
					InvXml.AddAttrib("schemeAgencyName","KBO");
					InvXml.AddAttrib("schemeURI","http://www.e-FFF.be/KBO");
				InvXml.OutOfElem(); // PartyIdentification
				InvXml.AddElem("cac:PartyName");InvXml.IntoElem();
				  zero(str_,sizeof str_); copy(s(2,3),str_,fldlen(2,3)); InvXml.AddElem("cbc:Name",str_);
				InvXml.OutOfElem(); // Partyname
				InvXml.AddElem("cac:PostalAddress");InvXml.IntoElem();
          zero(str_,sizeof str_); copy(s(2,4),str_,fldlen(2,4));InvXml.AddElem("cbc:StreetName",str_);
          zero(str_,sizeof str_); copy(s(2,6),str_,fldlen(2,6));InvXml.AddElem("cbc:CityName",str_);
          zero(str_,sizeof str_); copy(s(2,5),str_,fldlen(2,5));InvXml.AddElem("cbc:PostalZone",str_);
					InvXml.AddElem("cac:Country"); InvXml.IntoElem();
					  zero(str_,sizeof str_);
					  if(*l(2,10)==0 && (fldlen(2,22) && *s(2,22))) copy(s(2,22),str_,2); else copy("BE",str_,2);
            InvXml.AddElem("cbc:IdentificationCode",str_);
						InvXml.AddAttrib("listID","ISO3166-1:Alpha2");
					InvXml.OutOfElem(); // Country
				InvXml.OutOfElem(); // Postaladdres
				InvXml.AddElem("cac:PartyTaxScheme"); InvXml.IntoElem();
				  if(fldlen(2,22)==0 || *s(2,22)=='\0'){ // belgisch
		  			zero(str_,sizeof str_); copy("BE",str_,2);btw_deco(&str_[2],l(2,10),0);
						InvXml.AddElem("cbc:CompanyID",str_);
						InvXml.AddAttrib("schemeID","BE:VAT");
					}
					else{ // buitenlander
	  			  zero(str_,sizeof str_); copy(s(2,22),str_,fldlen(2,22));
						InvXml.AddElem("cbc:CompanyID",str_);
						InvXml.AddAttrib("schemeID","ZZZ");
					}
					InvXml.AddElem("cac:TaxScheme"); InvXml.IntoElem();
						InvXml.AddElem("cbc:ID","VAT");
					InvXml.OutOfElem(); // TaxScheme
				InvXml.OutOfElem(); // PartyTaxScheme
				//InvXml.AddElem("cac:Contact"); InvXml.IntoElem();
    //      // InvXml.AddElem("cbc:Name",Name);
				//  if(fldlen(2,129) && *s(2,129)){zero(str_,sizeof str_);copy(s(2,129),str_,fldlen(2,129)); InvXml.AddElem("cbc:ElectronicMail",str_);} // boekhouderadres eerst
				//  else if(fldlen(2,21) && *s(2,21)){zero(str_,sizeof str_);copy(s(2,21),str_,fldlen(2,21)); InvXml.AddElem("cbc:ElectronicMail",str_);}
				//	if(fldlen(2,8) && *s(2,8)){zero(str_,sizeof str_);copy(s(2,8),str_,15); InvXml.AddElem("cbc:Telephone",str_);}
    //    InvXml.OutOfElem(); // Contact
				InvXml.AddElem("cac:PartyLegalEntity"); InvXml.IntoElem();
          zero(str_,sizeof str_); copy(s(2,3),str_,fldlen(2,3));InvXml.AddElem("cbc:RegistrationName",str_);
					zero(str_,sizeof str_);
					if(*l(2,10)){copy("BE",str_,2);btw_deco(&str_[2],l(2,10),0);}
          InvXml.AddElem("cbc:CompanyID",str_);	InvXml.AddAttrib("schemeID","BE:VAT"); InvXml.AddAttrib("schemeName","KBO");
					InvXml.AddElem("cac:RegistrationAddress"); InvXml.IntoElem();
	// NIET					InvXml.AddElem("cbc:StreetName",&firma[31]);
						zero(str_,sizeof str_); copy(s(2,6),str_,fldlen(2,6));InvXml.AddElem("cbc:CityName",str_);
						zero(str_,sizeof str_); copy(s(2,5),str_,fldlen(2,5));InvXml.AddElem("cbc:PostalZone",str_);
						InvXml.AddElem("cac:Country"); InvXml.IntoElem();
							InvXml.AddElem("cbc:IdentificationCode","BE");
							InvXml.AddAttrib("listID","ISO3166-1:Alpha2");
						InvXml.OutOfElem(); // Country
					InvXml.OutOfElem(); // RegistrationAdres
				InvXml.OutOfElem(); // PartyLegalEntity
			InvXml.OutOfElem(); // Party
		InvXml.OutOfElem(); // AccountingCustomerParty
    InvXml.AddElem("cac:PaymentMeans"); InvXml.IntoElem();
		  if(alg_tot<0) InvXml.AddElem("cbc:PaymentMeansCode",97); // CN : Te verrekenen 
		  else if(*s(8,22)=='J' || (alg_tot-*f(8,21))==0) {
				if(BetaaldViaBC) InvXml.AddElem("cbc:PaymentMeansCode",55); // betaald, BC  // 48 kwam uit op Ideal
			  else InvXml.AddElem("cbc:PaymentMeansCode",10); // betaald, anders cash nemen 
			}
			else if(fldlen(2,85) && *s(2,85)) InvXml.AddElem("cbc:PaymentMeansCode",49); // niet betaald en DOM-nummer ingevuld, dan via domiciliering 
			else InvXml.AddElem("cbc:PaymentMeansCode",31); // indien niet betaald, dan overschrijving
			InvXml.AddAttrib("listID","UN/ECE 4461");
			InvXml.AddAttrib("listAgencyID","6");
//			InvXml.AddAttrib("listURI","http://docs.oasis-open.org/ubl/os-UBL-2.0-update/cl/gc/default/PaymentMeansCode-2.0.gc");
//			InvXml.AddAttrib("listName","Payment Means");
			jddate(verv_dt,&jaartal,&mm,&dd); cstr_.Format("%04d-%02d-%02d",jaartal,mm,dd); InvXml.AddElem("cbc:PaymentDueDate",cstr_);
      zero(str_,sizeof str_);MakeStructMed(str_,ft_nr); cstr_=CString(str_); cstr_.Replace("/",""); // 'kkk/kkff/fffcc'   K(lant) F(aktnr) C(heck) 
			InvXml.AddElem("cbc:PaymentID",cstr_);
    InvXml.OutOfElem(); // PaymentMeans
// niet gebruikt    InvXml.AddElem("cac:PaymentTerms","");

		InvXml.AddElem("cac:TaxTotal");InvXml.IntoElem();
		  InvXml.AddElem("cbc:TaxAmount",Bedrag2Cstring((double)(btw_tot*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
      for(k=0;k<BTWDIM-BTWDIV+1;k++){
				if(btw_bas[k]){
					InvXml.AddElem("cac:TaxSubtotal"); InvXml.IntoElem();
						InvXml.AddElem("cbc:TaxableAmount",Bedrag2Cstring((double)(btw_bas[k]*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
						InvXml.AddElem("cbc:TaxAmount",Bedrag2Cstring((double)(btw_bd[k]*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
						InvXml.AddElem("cbc:Percent",Bedrag2Cstring((double)(btw_pct[k]),2));
						InvXml.AddElem("cac:TaxCategory");InvXml.IntoElem();
							if(btw_pct[k]==def_btw) cstr_="S"; else cstr_="AA";
							InvXml.AddElem("cbc:ID",cstr_); InvXml.AddAttrib("schemeID","UNCL5305");
	//						cstr_.Format("%02d",(int)(btw_pct[k])); InvXml.AddElem("cbc:Name",cstr_);
							InvXml.AddElem("cac:TaxScheme");InvXml.IntoElem();
								InvXml.AddElem("cbc:ID","VAT");
							InvXml.OutOfElem(); // TaxScheme
						InvXml.OutOfElem(); // TaxCategory
					InvXml.OutOfElem(); // TaxSubtotal
				}
			}
			if(tot_leeg+tot_ex_btw){
				InvXml.AddElem("cac:TaxSubtotal"); InvXml.IntoElem();
					InvXml.AddElem("cbc:TaxableAmount",Bedrag2Cstring((double)((tot_leeg+tot_ex_btw)*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
					InvXml.AddElem("cbc:TaxAmount","0.00"); InvXml.AddAttrib("currencyID","EUR");
					InvXml.AddElem("cbc:Percent","0.00");
					InvXml.AddElem("cac:TaxCategory");InvXml.IntoElem();
						InvXml.AddElem("cbc:ID","E"); InvXml.AddAttrib("schemeID","UNCL5305");
//						cstr_.Format("%02d",(int)(btw_pct[k])); InvXml.AddElem("cbc:Name",cstr_);
						InvXml.AddElem("cac:TaxScheme");InvXml.IntoElem();
							InvXml.AddElem("cbc:ID","VAT");
						InvXml.OutOfElem(); // TaxScheme
					InvXml.OutOfElem(); // TaxCategory
				InvXml.OutOfElem(); // TaxSubtotal
			}
		InvXml.OutOfElem(); // TaxTotal
		InvXml.AddElem("cac:LegalMonetaryTotal"); InvXml.IntoElem();
			InvXml.AddElem("cbc:LineExtensionAmount",Bedrag2Cstring((double)((belastbt+tot_leeg+tot_ex_btw)*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
			InvXml.AddElem("cbc:TaxExclusiveAmount",Bedrag2Cstring((double)((belastbt+tot_leeg+tot_ex_btw)*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
			InvXml.AddElem("cbc:TaxInclusiveAmount",Bedrag2Cstring((double)(alg_tot*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
			bd_=0; if(!cn_flag_ && fldlen(8,21) && *f(8,21)) bd_=*f(8,21);
			if(bd_) {InvXml.AddElem("cbc:PrepaidAmount",Bedrag2Cstring((double)(*f(8,21)),2)); InvXml.AddAttrib("currencyID","EUR");}
			InvXml.AddElem("cbc:PayableAmount",Bedrag2Cstring((double)((alg_tot-bd_)*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
		InvXml.OutOfElem(); // LegalMonetaryTotal
		InvLineNr=1; tot_lgpl_=0;
		for(k=0;k<max_line;k++){
      ram2stu(k);
      if(test_line()){
#if DEF_INPUT | SPLITS_BON
        if(*pu_58_14 && *f(58,31)==0) continue;/* niet gebruikte lijnen skippen */
#endif
				if(*f(58,47)>0) tot_lgpl_+=*f(58,47);
				if(*i(58,34)==99) continue; // geen leeggoed
				lgmode_=NO;// if(*i(58,34)==99) lgmode_=YES;
				InvLine2Xml(NO,cn_flag_);
  		}
		}
    if(tot_leeg){
			if(tot_lgpl_){
				fasinit(58);copy("LEEGG",s(58,15),4); copy("Leeggoed geleverd",s(58,16),20); *f(58,47)=tot_lgpl_; *f(58,31)=1;
				InvLine2Xml(YES,cn_flag_);
			}
			bd_=tot_leeg-tot_lgpl_; 
			if(bd_){
				fasinit(58);copy("LEEGG",s(58,15),4); copy("Leeggoed terug",s(58,16),20); *f(58,47)=bd_; *f(58,31)=1;
				InvLine2Xml(YES,cn_flag_);
			}
		}
  InvXml.OutOfElem(); // inv:Invoice EINDE
  zero(str_,sizeof str_); copy(s(25,3),str_,3);cstr_.Format("%s%s-%d-%s%05d.xml",OutputMapUbl,str_,jaartal,code_journaal_,ft_nr);
	if(InvXml.Save(cstr_)==false) errnum=1;
}

static void InvLine2Xml(int lgmode_, int cn_flag_)
{
  int j,k,fl_ex_btw_=NO;
	double bd_,factor_;
	long lbd_,lgrb_;
	short mm,dd,jaartal;
	char str_[100];
	CString cstr_;

  factor_=1.0; if(cn_flag_) factor_=-1.0;

	if(cn_flag_) InvXml.AddElem("cac:CreditNoteLine"); else InvXml.AddElem("cac:InvoiceLine"); InvXml.IntoElem();
    InvXml.AddElem("cbc:ID",InvLineNr);
		if(cn_flag_) InvXml.AddElem("cbc:CreditedQuantity",Bedrag2Cstring((double)(*f(58,31)*factor_),2)); 
		else InvXml.AddElem("cbc:InvoicedQuantity",Bedrag2Cstring((double)(*f(58,31)*factor_),2));
		InvXml.AddAttrib("unitCodeListID","UNECERec20"); InvXml.AddAttrib("unitCode","ZZ");
		if(lgmode_) cstr_=Bedrag2Cstring((double)(*f(58,47)*factor_),2); else cstr_=Bedrag2Cstring((double)(*d(58,35)*factor_),2);
		//	cstr_.Format("%.02f",(double)(*f(58,47)*factor_)); else cstr_.Format("%.02f",(double)(*d(58,35)*factor_)); 
		InvXml.AddElem("cbc:LineExtensionAmount",cstr_); InvXml.AddAttrib("currencyID","EUR");
		InvXml.AddElem("cac:TaxTotal"); InvXml.IntoElem();
			if(lgmode_) bd_=0; 
			else{bd_=*d(58,35) * *f(58,24) / 100.; bd_=Round(bd_,(double)(0.01));}
			if(*i(58,34)!=99 && *f(58,24)==0 && *d(58,35)){
				lgrb_=makegrb();
				fasinit(3); *l(3,2)=lgrb_; faskeyi(3,1,0);
				if(*i(3,8)==0) fl_ex_btw_=YES;
			}
			InvXml.AddElem("cbc:TaxAmount",Bedrag2Cstring((double)(bd_*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
			InvXml.AddElem("cac:TaxSubtotal"); InvXml.IntoElem();
				if(lgmode_) cstr_=Bedrag2Cstring((double)(*f(58,47)*factor_),2); else cstr_=Bedrag2Cstring((double)(*d(58,35)*factor_),2); 
				InvXml.AddElem("cbc:TaxableAmount",cstr_); InvXml.AddAttrib("currencyID","EUR");
				if(lgmode_) bd_=0; 
				else{bd_=*d(58,35) * *f(58,24) / 100.; bd_=Round(bd_,(double)(0.01));}
				InvXml.AddElem("cbc:TaxAmount",Bedrag2Cstring((double)(bd_*factor_),2)); InvXml.AddAttrib("currencyID","EUR");
				if(lgmode_) bd_=0; else bd_=*f(58,24); 
				InvXml.AddElem("cbc:Percent",Bedrag2Cstring((double)(bd_),2));
				InvXml.AddElem("cac:TaxCategory");InvXml.IntoElem();
				  if(lgmode_ || fl_ex_btw_) cstr_="E";
					else{
  					if(bd_==def_btw) cstr_="S"; else cstr_="AA";
					}
					InvXml.AddElem("cbc:ID",cstr_); InvXml.AddAttrib("schemeID","UNCL5305");
					InvXml.AddElem("cac:TaxScheme");InvXml.IntoElem();
						InvXml.AddElem("cbc:ID","VAT");
					InvXml.OutOfElem(); // TaxScheme
				InvXml.OutOfElem(); // TaxCategory
			InvXml.OutOfElem(); // TaxSubtotal
		InvXml.OutOfElem(); // TaxTotal
		InvXml.AddElem("cac:Item"); InvXml.IntoElem();
//			  if(lgmode_==NO){ // artikel
			zero(str_,sizeof str_);copy(s(58,16),str_,fldlen(58,16)); InvXml.AddElem("cbc:Description",str_);
			zero(str_,sizeof str_);copy(s(58,16),str_,fldlen(58,16)); InvXml.AddElem("cbc:Name",str_);
			InvXml.AddElem("cac:SellersItemIdentification"); InvXml.IntoElem();
				zero(str_,sizeof str_);
// GRB-nummer meegeven ipv artikelcode
  			if(lgmode_) lgrb_=*(long *)&df_rek[12][0]; // copy("489000",str_,6);
				else lgrb_=makegrb();
				grb_deco(str_,&lgrb_);
				// else copy("700999",str_,6);
  			//else if(*f(58,24)==0 && *s(2,22)) copy("700001",str_,6);
  			//else if(*f(58,24)==0 && *s(2,22)=='\0') copy("700000",str_,6);
  			//else if(*f(58,24)==6) copy("700100",str_,6);
  			//else if(*f(58,24)==12) copy("700200",str_,6);
  			//else copy("700300",str_,6);

//#else
//				copy(s(58,15),str_,fldlen(58,15)); 
//#endif
				InvXml.AddElem("cbc:ID",str_);
			InvXml.OutOfElem(); //SellersItemIdentification
			InvXml.AddElem("cac:ClassifiedTaxCategory"); InvXml.IntoElem();
				if(lgmode_){
					InvXml.AddElem("cbc:ID","E"); InvXml.AddAttrib("schemeID","UNCL5305");
					InvXml.AddElem("cbc:Percent","0.00");
				}
				else {
					if(*f(58,24)==def_btw) cstr_="S"; else cstr_="AA";
					InvXml.AddElem("cbc:ID",cstr_); InvXml.AddAttrib("schemeID","UNCL5305");
					InvXml.AddElem("cbc:Percent",Bedrag2Cstring((double)(*f(58,24)),2));
				}
				InvXml.AddElem("cac:TaxScheme");InvXml.IntoElem();
					InvXml.AddElem("cbc:ID","VAT");
				InvXml.OutOfElem(); // TaxScheme
			InvXml.OutOfElem(); // ClassifiedTaxCategory
    InvXml.OutOfElem(); // Item
		InvXml.AddElem("cac:Price"); InvXml.IntoElem();
      if(lgmode_) bd_=*f(58,47); 
			else{bd_=*d(58,35); if(*f(58,31)) bd_=*d(58,35)/ *f(58,31);}
			bd_=Round(bd_,(double)(0.001));
			InvXml.AddElem("cbc:PriceAmount",Bedrag2Cstring((double)(bd_),3)); InvXml.AddAttrib("currencyID","EUR");
//      InvXml.AddElem("cbc:BaseQuantity","1.00");
		InvXml.OutOfElem(); // Price
  InvXml.OutOfElem(); // InvoiceLine
  InvLineNr++; // lijnnummer verhogen
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

static void CalcFactuur(void)
{
  int16 j,k;
	char verv_term[5];
  BEDRAG belastb_,tot_incl=0,tot_dif,lin_incl,kort_;
  float prx_,prx1_,bdf_,bd_accijn=0,prx_r,tot_afh_los,tot_akw=0,lg_btw_=0;
  flag tot_chk=YES;
  uint16 rec_,rec_lg_=0;
	long lgrb_;

  if(fldlen(8,23)) copy(s(8,23),ft_munt,3);
  if(ft_munt[0]=='\0') copy(def_munt,ft_munt,3);
  errnum=0;
  valu_cnv(ft_munt,def_munt,1.,1.);
  if(errnum) copy(def_munt,ft_munt,3);
  ft_afrond=(double)(0.01); vm_munt=YES;

  ft_date=*u(8,8); ft_nr=*u(8,2);
	copy(s(2,13),verv_term,3); verv_term[3]='\0';
  k=0; if(verv_term[0]=='E') k=val(&verv_term[1]);
  if(k>5){/* DSB : einde maand + x dagen */
     verv_dt=dateadd(ft_date,"E0"); verv_dt+=k;
  }
  else verv_dt=dateadd(ft_date,verv_term);
  
  tot_kort=0;tot_leeg=0;tot_ex_btw=0;semestbd=0;tot_subs=0;tot_akw=0;BetaaldViaBC=NO;
  trans_kost=0;
  zero((char *)btw_bas,sizeof btw_bas);winst_bd=0;
  zero((char *)incl_bas,sizeof incl_bas);winst_bd=0;

  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(test_line()==NO){
      rec_=*pu_58_1;init58(k,YES);ram2stu(k);*pu_58_1=rec_;
    }
		if(cmpstr("*Betaald BC",s(58,16),11)==0 || cmpstr("*        BC",s(58,16),11)==0) BetaaldViaBC=YES;
    if(fldlen(58,47)){
      tot_leeg+=*f(58,47);/* NIET uitrekenen, maar totaal nemen */
    }
		if(*i(58,34)!=99 && *f(58,24)==0 && *d(58,35)){  // kortingsbonnen ex.BTW
			lgrb_=makegrb();
			fasinit(3); *l(3,2)=lgrb_; faskeyi(3,1,0);
			if(*i(3,8)==0){
				tot_ex_btw+=*d(58,35);
				goto next_lin;
			}
		}
#if PALET_KORTING
#if FLAGPED
    if(fldlen(58,68) && *i(58,34)!=99) tot_afh_los+=*f(58,68);
#else
    if(fldlen(58,69)) tot_afh_los+=*f(58,68);
#endif
#endif
    prx_=*pf_58_20;
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
#endif
#if FLAGDU3 /* gratis artikels de accijns toch rekenen */
    if(prx_==0 && *i(58,34)!=99) prx_=*f(58,38);
#endif
    prx_r=prx_;
    semestbd+=*f(58,53);
		belastb_=*d(58,35);
    j=btw_tab((BEDRAG)belastb_);
    btw_bas[j]+=*d(58,35);
#if BTWINCL
    incl_bas[j]+=lin_incl;
#endif

#if TRANS_KOST
#if FLAGALS
    if(*l(58,26)){
      for(j=0;j<8;j++) if(*l(58,26)==hk_omzgrb[j]) break;
      if(j<8){
	j=0;if(*s(2,26)!='0') j=1;
	if(*s(8,31)=='N') bdf_=hk_pct[j][1]; else bdf_=hk_pct[j][0];
	trans_kost+=*pd_58_35 * bdf_/100.;
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
		next_lin:;
    stu2ram(k);
  }

#if TRANS_KOST/* transactie-kost aan 21% goederen tellen */
  if(trans_kost){
    trans_kost=round((double)trans_kost);
    fasinit(58); belastb_=trans_kost;
    *pf_58_24=def_btw;
    if(*s(8,26)=='J') *pf_58_24=0;
    j=btw_tab((BEDRAG)belastb_);
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
    btw_bas[j]+=belastb_;
    tot_chk=NO;
  }
#endif
  belastbt=0;
  for(k=0;k<BTWDIM-BTWDIV;k++){
#if BTWINCL
    if(tot_chk){
      btw_bas[k]=round((double)(incl_bas[k]/(1.+btw_pct[k]/100.)));
    }
#endif
    belastbt+=btw_bas[k];
  }
  btw_tot=0;
  for(k=0;k<BTWDIM;k++){
    btw_bd[k]=round((double)((btw_bas[k]*btw_pct[k])/100.));
    btw_tot+=btw_bd[k];
  }
  tot_leeg=round((double)tot_leeg);
	tot_ex_btw=round((double)tot_ex_btw);
  tot_accijns=round((double)tot_accijns);
  tot_subs=round((double)tot_subs);
  tot_incl+=tot_leeg+tot_ex_btw-tot_subs;
  alg_tot=belastbt+btw_tot+tot_leeg+tot_ex_btw-tot_subs;
#if DRI_flag/* verpakking zit al in belastbaar */
  alg_tot-=tot_leeg;
#endif
#if BTWINCL
  if(tot_chk){
    tot_dif=tot_incl-alg_tot;
		tot_dif=round(tot_dif);
    if(tot_dif){/* eerst proberen op default btw % */
      for(k=0;k<BTWDIM;k++) if(btw_bd[k] && btw_pct[k]==def_btw) break;
      if(k>=BTWDIM){
	for(k=0;k<BTWDIM;k++) if(btw_bd[k] && btw_pct[k]!=0) break;
      }
      if(k<BTWDIM) btw_bd[k]+=tot_dif;
      btw_tot+=tot_dif;
      alg_tot+=tot_dif;
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


//static void CalcFactuur(void)
//{
//  int16 j,k;
//	char verv_term[5];
//  BEDRAG belastb_,tot_incl=0,tot_dif,lin_incl,kort_;
//  float prx_,prx1_,bdf_,bd_accijn=0,prx_r,tot_afh_los,tot_akw=0,lg_btw_=0;
//  flag tot_chk=YES;
//  uint16 rec_,rec_lg_=0;
//
//  ft_date=*u(8,8); ft_nr=*u(8,2);
//	copy(s(2,13),verv_term,3); verv_term[3]='\0';
//  k=0; if(verv_term[0]=='E') k=val(&verv_term[1]);
//  if(k>5){/* DSB : einde maand + x dagen */
//     verv_dt=dateadd(ft_date,"E0"); verv_dt+=k;
//  }
//  else verv_dt=dateadd(ft_date,verv_term);
//  
//  tot_kort=0;tot_leeg=0;semestbd=0;tot_subs=0;tot_akw=0;
//  trans_kost=0;
//  zero((char *)btw_bas,sizeof btw_bas);winst_bd=0;
//  zero((char *)incl_bas,sizeof incl_bas);winst_bd=0;
//
//  for(k=0;k<max_line;k++){
//    ram2stu(k);
//    if(test_line()==NO){
//      rec_=*pu_58_1;init58(k,YES);ram2stu(k);*pu_58_1=rec_;
//    }
//#if KORTTOT/* correctie bij kassa-facturen */
//    if(*d(58,42)==0 && *pd_58_35) *d(58,42)=*pd_58_35;
//#endif
//
//#if QNUL
//    if(*pf_58_31==0) *pf_58_31=1;
//#endif
//    if(fldlen(58,47)){
//      tot_leeg+=*f(58,47);/* NIET uitrekenen, maar totaal nemen */
//    }
//    tot_afh_los=0;
//#if AFHAALVERG
//    if(fldlen(58,56)) tot_afh_los+=*f(58,56);
//#endif
//#if LOSVERGOED
//    if(fldlen(58,59) && *f(58,20))	tot_afh_los+=*f(58,59);
//#endif
//
//#if PALET_KORTING
//#if FLAGPED
//    if(fldlen(58,68) && *i(58,34)!=99) tot_afh_los+=*f(58,68);
//#else
//    if(fldlen(58,69)) tot_afh_los+=*f(58,68);
//#endif
//#endif
//    prx_=*pf_58_20;
//#if FLAGDUB  || FLAGSEG || FLAGFLI
//    if(fldlen(58,60) && *s(58,60)=='J' && *pf_58_31){/* ehprijs = totaal bedrag */
//      prx_/= *pf_58_31;
//    }
//#endif
//    if(*i(58,34)==99) prx_=0;
//#if BTWINCL
//    lin_incl=round((double)(prx_* *pf_58_31)); tot_incl+=lin_incl;
//    if(fldlen(58,27)){
//      if(*s(58,27)=='J') prx_/=1.+*pf_58_24/100.;
//      else if(test_line() && lin_incl) tot_chk=NO; // indien excl. lijn MET bedrag dan controle stoppen 
//    }
//#endif
//#if FLAGDU3 /* gratis artikels de accijns toch rekenen */
//    if(prx_==0 && *i(58,34)!=99) prx_=*f(58,38);
//#endif
//    bd_accijn=*f(58,38);
//    if(prx_>=0){/* bedrag accijns mag niet groter zijn de ehpr */
//      if(bd_accijn>prx_) bd_accijn=prx_;
//    }
//    else {
//      bd_accijn=-bd_accijn;
//      if(bd_accijn<prx_) bd_accijn=prx_;
//    }
//#if FLAGPED
//    prx_=prx_-*f(58,70) + *f(58,71);          /* paletkorting + toeslag bak */
//    if(*f(58,70)!=0 || *f(58,71)!=0) tot_chk=NO;
//#endif
//    prx_r=prx_;
//    if(fldlen(58,21)){
//      if(*pf_58_21){
//#ifdef ALB_flag
//	if(*s(2,71)=='J') prx_=prx_ * (100.- *pf_58_21)/100.;
//	else
//#endif
//#if FLAGDSV
//	bdf_=1. + *pf_58_21/100.;
//	if(bdf_) prx_=(prx_-bd_accijn)/bdf_+bd_accijn;
//#else
//	prx_=(prx_-bd_accijn)*(100.- *pf_58_21)/100.+bd_accijn;
//#endif
//#if FLAGVVL
//	prx_=(long)(prx_*100+.5)/100.;
//#endif
//#if BTWINCL
//	if(prx_)tot_chk=NO;
//#endif
//      }
//#if EXTEND_KORT
//      for(j=0;j<10;j++){
//				if(prx_ && *(s(8,53)+j)=='J') tot_afh_los+=*f(58,103+j*3);
//      }
//#endif
//      if(fldlen(58,36) && prx_>0){
//				bdf_=*f(58,36);
//				if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
//				prx_-=bdf_;
//      }
//no_k_perc:;
//#if FACT_PROMO
//      bdf_=prx_;
//      if(*f(58,91)){
//				prx_=(prx_-bd_accijn)*(100.- *f(58,91))/100.+bd_accijn;
//      }
//      if(prx_>0) prx_-=*f(58,92); // niet bij gratis 
//      *f(58,94)=(bdf_-prx_)* *pf_58_31;
//      tot_promo+=*f(58,94);
//#if BTWINCL
//      if(*f(58,94)) tot_chk=NO;
//#endif
//#endif
//#if !FLAGSEG
//      if(fldlen(58,22)){
//	*f(58,22)=prx_r-prx_;
//#if FLAGVVL
//	*f(58,22)=(long)(*f(58,22)*100+.5)/100.;
//#endif
//      }
//#endif
//    }
//    *f(58,52)=(prx_r-prx_)* *pf_58_31;
//#ifdef ALB_flag
//    if(*s(2,71)=='J') *f(58,53)=(prx_r * *pf_58_31)* *f(58,43)/100.;
//    else
//#endif
//    *f(58,53)=((tot_afh_los+((prx_-bd_accijn)* *pf_58_31)))* *f(58,43)/100.;
//    *f(58,53)=round((double)(*f(58,53)));
//    semestbd+=*f(58,53);
//    bdf_=0.00001; if((prx_* *pf_58_31)<0) bdf_=-bdf_;/* correct afronding */
//    belastb_=round((double)((prx_* *pf_58_31+bdf_)+tot_afh_los));
//    tot_accijns+=bd_accijn* *pf_58_31;
//    if(fldlen(58,41)){
//      bdf_=*f(58,41) * *pf_58_31;
//      if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
//#if KAS2GROOTH
//      if(*i(58,34)!=99)
//#endif
//	tot_akw+=bdf_;
//    }
//#if DISKIMME
//    if(fldlen(2,14)==4) bdf_=*f(2,14); else bdf_=*i(2,14);
//    if(bdf_){
//      belastb_=round((double)belastb_*(1.-bdf_/100.));
//    }
//#endif
//    j=btw_tab((BEDRAG)belastb_);
//    btw_bas[j]+=belastb_;
//#if BTWINCL
//    incl_bas[j]+=lin_incl;
//#endif
//		*pd_58_35=belastb_;
//#if TRANS_KOST
//#if FLAGALS
//    if(*l(58,26)){
//      for(j=0;j<8;j++) if(*l(58,26)==hk_omzgrb[j]) break;
//      if(j<8){
//	j=0;if(*s(2,26)!='0') j=1;
//	if(*s(8,31)=='N') bdf_=hk_pct[j][1]; else bdf_=hk_pct[j][0];
//	trans_kost+=*pd_58_35 * bdf_/100.;
//      }
//    }
//#else
//    if((*pd_58_35 || *i(58,34)==99) && *ps_58_16!='*' && *pu_58_14 && *ps_58_62!='P'){
//      fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
//      bdf_=*pf_58_31* *f(6,84);
//      if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
//      trans_kost+=bdf_;
//      if(fldlen(8,31) && *s(8,31)!='J') trans_kost=0;/* geen rekenen */
//    }
//#endif
//#endif
//#if KORTTOT
//    j=btw_tab((BEDRAG)belastb_);
//		kort_=*d(58,42)-*pd_58_35; kort_=round(kort_);
//    kort_btw[j]+=kort_; //*d(58,42)-*pd_58_35;
//    tot_kort+=kort_; // *d(58,42)-*pd_58_35;
//#endif
//#if SUBSIDIE
//		tot_subs+=*f(58,29);
//#endif
//    stu2ram(k);
//  }
//
//#if TRANS_KOST/* transactie-kost aan 21% goederen tellen */
//  if(trans_kost){
//    trans_kost=round((double)trans_kost);
//    fasinit(58); belastb_=trans_kost;
//    *pf_58_24=def_btw;
//    if(*s(8,26)=='J') *pf_58_24=0;
//    j=btw_tab((BEDRAG)belastb_);
//    btw_bas[j]+=belastb_;
//    tot_chk=NO;
//  }
//#endif
//
//#if DRI_flag/* verpakking 21% als goederen tellen */
//  if(tot_leeg){
//    tot_leeg=round((double)tot_leeg);
//    fasinit(58);*f(58,24)=lg_btw_; belastb_=tot_leeg;
//    j=btw_tab((BEDRAG)belastb_);
//    if(fldlen(58,33)) *s(58,33)=j+btw_kol;
//    btw_bas[j]+=belastb_;
//    tot_chk=NO;
//  }
//#endif
//  belastbt=0;
//  for(k=0;k<BTWDIM-BTWDIV;k++){
//#if BTWINCL
//    if(tot_chk){
//      btw_bas[k]=round((double)(incl_bas[k]/(1.+btw_pct[k]/100.)));
//    }
//#endif
//    belastbt+=btw_bas[k];
//  }
//  btw_tot=0;
//  for(k=0;k<BTWDIM;k++){
//    btw_bd[k]=round((double)(btw_bas[k]*btw_pct[k])/100.);
//    btw_tot+=btw_bd[k];
//  }
//  tot_leeg=round((double)tot_leeg);
//  tot_accijns=round((double)tot_accijns);
//  tot_subs=round((double)tot_subs);
//  tot_incl+=tot_leeg-tot_subs;
//  alg_tot=belastbt+btw_tot+tot_leeg-tot_subs;
//#if DRI_flag/* verpakking zit al in belastbaar */
//  alg_tot-=tot_leeg;
//#endif
//#if BTWINCL
//  if(tot_chk){
//    tot_dif=tot_incl-alg_tot;
//		tot_dif=round(tot_dif);
//    if(tot_dif){/* eerst proberen op default btw % */
//      for(k=0;k<BTWDIM;k++) if(btw_bd[k] && btw_pct[k]==def_btw) break;
//      if(k>=BTWDIM){
//	for(k=0;k<BTWDIM;k++) if(btw_bd[k] && btw_pct[k]!=0) break;
//      }
//      if(k<BTWDIM) btw_bd[k]+=tot_dif;
//      btw_tot+=tot_dif;
//      alg_tot+=tot_dif;
//    }
//  }
//#endif
//  kredietbp_bd=0; 
//#if KREDIETBEPERK
//	bdf_=0;
//  if(alg_tot>0 &&  *s(8,22)!='J' && (fldlen(8,21)==0 || *f(8,21)<alg_tot)){
//#ifdef KREDIETBP_PCT
//		bdf_=KREDIETBP_PCT;
//#else 
//		if(fldlen(2,14)){
//			 if(fldlen(2,14)==4) bdf_=*f(2,14); else bdf_=*i(2,14);
//		}
//#endif
//#if FLAGPWH
//		if(*s(2,44)=='J') bdf_=0; // GEEN kredietbeperking
//#endif
//		kredietbp_bd=round((double)(alg_tot* bdf_)/100.);
//	}
//#endif
//  disk_bd=0;
//#if DISCONTO
//  if(len2_14 && (alg_tot>0)){
//    if(fldlen(2,14)==4) bdf_=*f(2,14); else bdf_=*i(2,14);
//#if FLAGPMC
//		bdf_=4.; // VAST 4% kredietbeperking 
//#endif
//    disk_bd=alg_tot;
//    if(disk_ei) disk_bd-=(btw_tot + tot_leeg);
//#if DISC_NOACC
//    disk_bd-=tot_accijns;
//#endif
//    disk_bd=round((double)(disk_bd* bdf_)/100.);
//    if(disk_bd<0) disk_bd=0;
//  }
//#endif
//}

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



static int bcopy0(char *ps_, char *pd_, int maxlen_)
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
  char *pdum_;

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
	sysget(3598,6,b3598);
  sysget(3604,2,&b3604);
  sysget(3606,2,&b3606);
  sysget(3608,2,def_ext);
  sysget(3894,2,&sys3894);def_inc='N';
  sysget(19500,50,OutputMapUbl); 

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
      if(k>j || z<=9){/* enkel laatste 9 cijfers nemen */
	firmbtwnr=(firmbtwnr*10) + (firma[86+k]-'0');
      }
    }
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

static double round(double value_)
{
  double bd_;
						
  bd_=valu_cnv(def_munt,def_munt,value_,ft_afrond);
  return (double)(bd_);
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

static long makegrb(void)
{
  int16 g,gg,kk;
  long rekenc;
  char reken[10];
 
  if(fldlen(58,26) && *l(58,26)) rekenc=*l(58,26);
  else{
    zero(reken,sizeof reken);
    copy(b3598,reken,6);

    for(g=0;g<10;g++) if(reken[g]=='\0') break;
#if EXPBTW01 // bij exportfactuur prefix 70, 700,... vervangen door 71, 701, ... 
		if((*s(8,26)=='J' || btw_glob==0) && g) reken[g-1]='1';
#endif
    if(fldlen(2,25)){
      copy(s(2,25),&reken[g],fldlen(2,25));
      for(g=0;g<10;g++) if(reken[g]=='\0') break;
    }
    if(len58_25){
			if(*ps_58_25=='\0') *ps_58_25='0';
      copy(ps_58_25,&reken[g],len58_25);
      for(g=0;g<10;g++) if(reken[g]=='\0') break;
    }
    if(b3604){
      stcli_d(&reken[g],(long)*i(58,34),b3604,0);
      g+=b3604;
    }
    if(b3606){
      kk=*pf_58_24;gg=*pf_58_24*10 - kk*10;/* gg = decimaal */
      stcli_d(&reken[g],(long)kk,2,0);
      if(gg && b3606==2) stcli_d(&reken[g]+2,(long)gg,1,0);/* decimaal */
    }
    grb_comp(reken,&rekenc);
  }
  return (long)rekenc;
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