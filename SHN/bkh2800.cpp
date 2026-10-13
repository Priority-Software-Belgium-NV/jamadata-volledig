#include "Std\OVLCpp.h"
#include "OvlShare.h"

extern "C" void CnvJamaChar(char *pString,int16 MaxLen,int16 CnvMode);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
extern "C" void AddTextKey(int16 Fld,int16 Hz,int16 Vt,int16 Xlen,int16 Ylen,int16 KeyNr,char *KeyText,long KleurRGB);
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" int GetFileFromSelection(char *ptitel_,char *pselection_); // result komt in SelectedFileName
extern "C" int SendMail(int send_mode);


extern "C" char* BKH2800GetD() {return &zzvw;}

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAX_TBSELECTIE  500


extern "C" char BKH2800dat[] = "bkh2800  00:01 07/02/11 (c) Jamadata"; // Aanpassen JMS-parameters (+.J)

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
static char fm_us5U[] = {7,0xC8,5,0,1,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us10[]  = {7,0xC8,10,0,0,0,0};
static char fm_us3[]   = {7,0xC8,3,0,0,0,0};
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
static char fm_uu1[]   = {6,0xD0,1,0,0x60,0};
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
static char fm_ugrb[]  = {2,0xE8};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_us8PW[] = {7,0xC8,8,0,5,0,0};
static char fm_us20PW[] = {7,0xC8,20,0,4,0,0};
static char fm_us40PW[] = {7,0xC8,40,0,4,0,0};
static char fm_uRKSLW[] = {17,0xC8,1,0,1,0,'R','R','K','K','L','L','S','S','W','W',0};
static char fm_uWHSNr[]= {9,0xC8,7,0,1,0,'0','9',0};

extern int16 retcall,parmcall[8];
extern char info[];

static double String2Getal(CString S,char decim_kar);
static double String2Double(CString S){return String2Getal(S,',');}
static double String2Double(CString S,char decim_kar){ return String2Getal(S,decim_kar);}
static int String2Int(CString S){return (int)(String2Getal(S,','));}
static CString Double2String(double getal,long mode); // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
static CString Int2String(int getal){return Double2String((double) getal,0); }
static int SpaceZeros(char* ps_,int max_len);

static void ExecuteBatchJob(void);
static void initload(void);
static void DeleteOldMail(void);
static void DisplayCstring(CString reply);
static void DocumentInstellingen(void);
static void DownloadFilesToPost(void);
static void FillInPostCodes(void);
static void PapierInstellingen(void);
static void AfdrukPostInstellingen(void);
static void WerkPostInstellingen(void);
static void UpdateDocumentSettings(int nr_);
static void UpdatePapierSoort(int nr_);
static void UpdateFmDetail(int nr_);
static void UpdateAfdrukPostSettings(int nr_);
static void UpdateWerkPost(int nr_);
static void UpdateWerkPostAfdrukSettings(int nr_);
static void MailSettings(void);
static void UpdateMailSettings(int16 profielnr_);
static void UpdateMailRelaySettings(int16 profielnr_);
static void UpdateDataMastersSettings(void);
static int ZCstr2Arr(CString cstr_, char *p_arr_, int max_len_);
static CString Rec_Ele(CString s, int kol_, char delim_kar_);
static int copy0(char *ps,char *pd,int max);
static void int2str(int d, char *s, int len);
static void DisplayMenuTitel(int ypos_,char* tekst_,char attrib_);
static int SelecteerDocument(char *ptitel_);
static int SelecteerPapier(char *ptitel_,int update_);
static int SelecteerAfdrukPost(char *ptitel_,int update_);
static int SelecteerWerkPost(char *ptitel_,int update_);
static void SendTestMail(void);
static void SetAllFormatsToPDF(void);
static void scrxfld(int16 z,char *pfmt_,char *pvar_,char attr_);
static int DisplayTbSelectie(int q_elem_,int max_h,char *ptitel);
static double round(double bd_,double bd_afr_);
static int16 dots2mm(int16 dots);
static int16 mm2dots(int16 mm);
static void fileopen(int16 nr_);
static int16 search(int16 stu_,int16 mod_);

static struct{
	int Nr;
	char Naam[80];
}	TbSelectie[MAX_TBSELECTIE];

#define Q_DEFAULT_FM  5
static struct{
	char Naam[30];
	int  Formaat[7];
	char Type;
} DefaultFm[Q_DEFAULT_FM]={"A4 blad op laserprinter",2480,3508,0,118,118,118,118,'W',
															"Kettingformulier",2850,3600,-200,200,50,240,50,'K',
								"Etikettenblad 24st (3x8)",3,8,70,34,118,248,0,'L',
								"Prijsaffiches",1500,450,-200,200,0,200,0,'K',
								"Kastickets op rol",1500,300,0,0,0,0,0,'K'};
 
#define Q_JAMOSDRIVERS 12
static struct{
	int Nr;
	char Naam[40];
} JamosDrivers[Q_JAMOSDRIVERS]={0,"Windows Printer Driver",
																	 1,"Simpele tekstprinter (zonder opmaak)",
				     											 2,"IBM-proprinter type A",
																	 3,"IBM-proprinter type B",
																	 4,"IBM-proprinter type C",
																	 5,"IBM-proprinter type D",
																	 6,"Epson FX",
																	 7,"Star-10",
																	 8,"Nec-Pxx",
																	11,"Ticketprinter CBM-720",
																	12,"Ticketprinter Epson",
																	13,"Ticketprinter iDP-560"};

#define DIM_WHSDOSSIERS     2
static struct _WHS_Settings {
	CString WHSInternalCompanyNr[DIM_WHSDOSSIERS];
	CString WHSDossierNr[DIM_WHSDOSSIERS];
	CString WHSCompanyName[DIM_WHSDOSSIERS];
	CString JamaDossierCode[DIM_WHSDOSSIERS];
	CString JamaSubDir[DIM_WHSDOSSIERS];
	CString JamaFacturenDir[DIM_WHSDOSSIERS];
	CString FWPPassword;
	unsigned JamaLeverancierRec[DIM_WHSDOSSIERS];
} WHS_Settings;
 

 
static struct{
	char  Naam[30]; // uit jms
	int16 PapierNr;
	int16 OverlayNr;
	char  Opties[16];
	char  MailTemplate[5];
	int16 DefaultAfdrukPostNr; // uit jms 
	int16 SpecialAfdrukPostNr; // uit sys.fas per dossier 
} TbDocument[31]; // 1 extra als werkelement
 
static struct{
	char  Naam[30];
  int   Formaat[7];
	char  Type;
	int   DefaultFm;
} TbPapier[21];// 1 extra als werkelement
  
static struct{
	char  Naam[30];
  char  NaamWindows[50];
	int   JmsPrinterNummer; // 1-100 lokaal, 101-130 via comfortlink op toestel op afstand
	int   BinRef;
	char  BinName[50];
	int   MediaRef;
	char  MediaName[50];
	int   PaperRef;
	char  PaperName[50];
	int   JamosDriver;
	char  JamosDriverName[50];
} TbAfdrukPost[31];// 1 extra als werkelement

static struct s_TbWerkPost {
	char  Naam[30]; 
	char  PrintLocal;
	char  HoldPrintJobsOnServer;
	char  AllowMasterFunctions;
	char  DisplayJamadataBrief;
	int   FiliaalNummer;
	char  ScreenBootDossier[4][4];
	char  ScreenBootSequence[4][21];
	int   ScreenColorNummer[4];
	bool  PostOpAfstand;
  char  SerialNummer[20]; 
	char  DisplayEmailAsEML;
} TbWerkPost[MAX_WERKPOST+1]; // 1 extra als werkelement

static struct {
	char ImapServer[51];
	char ImapUser[31];
	char ImapPassword[51];
	char ImapFolderConcepts[51];
	char ImapFolderToCheck[51];
	char ImapFolderToSend[51];
	char ImapFolderFault[51];
	char ImapFolderSent[51];
	char MailFromName[51];
	char MailFromAddress[51];
	char MailReplyTo[51];
	char MailConfirmReceiptTo[51];
	char MailConfirmReadTo[51];
	char MailBcc[51];
	char MailRelayserver[2];
	char Relay1Server[51];
	char Relay1Port[11];
	char Relay1UserName[51];
	char Relay1Password[51];
	char Relay1Security[21];
	char Relay2Server[51];
	char Relay2Port[11];
	char Relay2UserName[51];
	char Relay2Password[51];
	char Relay2Security[51];
} TbMailSettings;

static uint16 sys1788; 
  
extern "C" void BKH2800cod()
{
  int16 k,key;
  char choice;

  initload();
  FOREVER {
		redo:;
    scrget(3,1);fasunlck(0);
		scraddpicto(50,0,76,22,4,2,45,0,4,"Download bestanden"); 
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) {DownloadFilesToPost();goto redo;} // downloaden gewenste files
	  if(key==101) break;
		fasunlck(-1);
    switch (choice){
			case '1': AfdrukPostInstellingen(); break;
      case '2': DocumentInstellingen(); break;
	    case '3': PapierInstellingen(); break;
			case '4': WerkPostInstellingen(); break;
      case '5': MailSettings(); break;  
			case '6': if(ovltest(2500)) UpdateDataMastersSettings(); else errnum=12; break;  
			case 'D': if(ovltest(2802)) ovlexit(2802); else errnum=12; break; 
			case 'P': if(fldlen(29,1)) FillInPostCodes(); else errnum=12; break; 
			case 'S': ExecuteBatchJob(); break;
			case 'T': if(ovltest(2)) ovlcall(2,1); else errnum=12; break; 
			case 'X': SetAllFormatsToPDF(); break;
			default:  errnum=34; break;
    }
  }
	for(k=0;k<MAX_WERKPOST;k++) if(TbWerkPost[k].AllowMasterFunctions=='J') break; // er moet minstens 1 post MASTER zijn
	if(k>=MAX_WERKPOST) JmsCmd("SetIniKeyValue|Post-001_Settings|AllowMasterFunctions|1");
  ovlexit(-1);
}

static void DownloadFilesToPost(void)
{
	int key;
	char str_selectie_[100];


	zero(str_selectie_,sizeof str_selectie_); retcall=0;
	FOREVER{
		scrget(3,17);
		scrifld(1,fm_us50,str_selectie_);
		key=scrupd(1,0x81);
		if(key==101) break;
		GetFileFromSelection(" Downloaden bestanden ",str_selectie_);
	}
}



static void SetAllFormatsToPDF(void)
{
	int16 k;
	char kar_;

	kar_='\0';
	for(k=0;k<30;k++){
	  sysput(18000+k*16,1,&kar_);
  }
	initload(); // om alle juiste parameters opnieuw te laden 
}

static void ExecuteBatchJob(void)
{
  int z,key,k,q_batchjobs;
	char str_[30],attrib_,choice='\0';
	CString cstr_,puntstr_,reply_,fname_;
  WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
	CString batchfiles[20];

	for(k=0;k<20;k++) batchfiles[k]="";q_batchjobs=0;
	hSearch = FindFirstFile ("..\\batch\\#*.bat", &FileData);
  FOREVER{
    if (hSearch == INVALID_HANDLE_VALUE) break;
    if (!(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){                      // geen directory 
		  fname_=CString(FileData.cFileName);batchfiles[q_batchjobs++]=fname_;
		}
		if(q_batchjobs>=10) break;
    if(FindNextFile (hSearch, &FileData)==false) break;
  }
  FindClose(hSearch);

	hSearch = FindFirstFile ("..\\batch\\!*.bat", &FileData);
  FOREVER{
    if (hSearch == INVALID_HANDLE_VALUE) break;
    if (!(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){                      // geen directory 
		  fname_=CString(FileData.cFileName);batchfiles[q_batchjobs++]=fname_;
		}
		if(q_batchjobs>=10) break;
    if(FindNextFile (hSearch, &FileData)==false) break;
  }
  FindClose(hSearch);
  if(q_batchjobs==0) goto endsr;
	puntstr_="............................................................";
  FOREVER{
		redo:;
		scraddf(-1,0,0,0);z=1;
		DisplayMenuTitel(1,"Uitvoeren specifiek batch-programma",0xA);
		for(k=0;k<q_batchjobs;k++){
			attrib_=0;if(batchfiles[k].GetAt(0)=='!') attrib_=0xB;
		  scraddfield(z,3,4+k,attrib_);
			cstr_=batchfiles[k]; cstr_=cstr_.Mid(1,cstr_.GetLength()-5);cstr_+=" ";
			cstr_+=puntstr_.Mid(0,59-cstr_.GetLength());
			cstr_+=CString(" : ");
			zero(str_,sizeof str_);str_[0]='1'+k;cstr_+=CString(str_); 
			scrifld(z++,fm_os63,(char *)(LPCTSTR)cstr_);
		}
		scraddfield(z,56,4+k+2,0);scrifld(z++,fm_os10,"U kiest?");
		scraddfield(z,65,4+k+2,0); scrifld(z++,fm_menu,&choice);
		scraddfield(z,1,23,8);scrifld(z++,fm_os10,"  F1 Stop ");
    key=scrupd(80,0x1);
	  if(key==101) break;
		k=choice-'1'; if(k<0 || k>q_batchjobs){ errnum=34;goto redo;}
		scrget(1,7);scrupd(-3,0);
		if(batchfiles[k].GetAt(0)=='!'){
			if(ovlcall(2,2)==0) goto redo; // stoppen server
		}
		cstr_="ExecBatch|";cstr_+=batchfiles[k];
		reply_=JmsCmd(cstr_);
		DisplayCstring(reply_);
		if(batchfiles[k].GetAt(0)=='!'){
			ovlcall(2,3); // herstarten server
			ovlexit(1); // reboot 
		}
	}
	
	endsr:;
}

static void DisplayCstring(CString reply)
{
	int z,key,ix,bpos_,len_;

  ix=0;bpos_=0;
	scrnum=0;scrget(1,170);z=1;
  while (ix>=0) {
    ix = reply.Find("\r\n",ix);
    if (ix<0){
			len_=reply.GetLength()-bpos_; if(len_<=0) break;
		}
		else len_=ix-bpos_;
		scrifld(z++,fm_os63,(char *)(LPCTSTR)reply.Mid(bpos_,len_));
		if(ix>=0) {ix += 2;bpos_=ix;}
		else break;
		if(z==20){
			scraddfield(z,1,23,8);scrifld(z++,fm_os10,"F1 stop");
			scraddfield(z,20,23,8);scrifld(z++,fm_os10,"F8 volgend");
			key=scrupd(-1,81);
			if(key==101) goto endsr;
			else {scrnum=0;scrget(1,170);z=1;}
		}
	}
	scraddfield(z,1,23,8);scrifld(z++,fm_os10,"F1 stop");
	key=scrupd(-1,81);
endsr:;
}
 
static void DocumentInstellingen(void)
{
	int k;

	FOREVER{
		k=SelecteerDocument("Afdrukinstellingen van een document");
		if(k<0) break;
		UpdateDocumentSettings(k);
	}
}
 
static int SelecteerDocument(char *ptitel_)
{
  int16 k,key,z,nr_;

  FOREVER{
	redo:;
  	scrget(3,2);z=1;nr_=0;
		DisplayMenuTitel(0,ptitel_,0xA);
  	for(k=0;k<15;k++){
	    k++;scrifld(z++,fm_ou2,&k);k--;
	  	scrifld(z++,fm_os30,&TbDocument[k].Naam);
      k+=16;scrifld(z++,fm_ou2,&k);k-=16;
		  scrifld(z++,fm_os30,&TbDocument[k+15].Naam);
  	}
	  scrifld(z++,fm_uu2,&nr_);
	  nr_=0;
	  key=scrupd(1,0x81);
	  if(key==101) return -1;
	  if(nr_<1 || nr_>30) {errnum=34;goto redo;}
	  return nr_-1;
  }
	return -1;
}

static void UpdateDocumentSettings(int nr_)
{
	int j,k,z,key,curs=1,curspos_,fl_updnaam_=NO;
	char papiernaam_[30],buf_[20],def_afdrukpostnaam_[30],spec_afdrukpostnaam_[30];
	CString keystr_,cstr_;
	  
	copy(TbDocument[nr_].Naam,TbDocument[30].Naam,sizeof TbDocument[0]); // voor te annuleren 
	zeros(papiernaam_,sizeof papiernaam_);
	if(TbDocument[nr_].PapierNr>0 && TbDocument[nr_].PapierNr<=20)copy(TbPapier[TbDocument[nr_].PapierNr-1].Naam,papiernaam_,30);
	else copy0("Afdruk naar PDF",papiernaam_,30);
	zeros(def_afdrukpostnaam_,sizeof def_afdrukpostnaam_);
	k=TbDocument[nr_].DefaultAfdrukPostNr;
	if(k>0 && k<=20)copy(TbAfdrukPost[k-1].Naam,def_afdrukpostnaam_,30);
	else if(k>100){
		for(j=20;j<30;j++) if(TbAfdrukPost[j].JmsPrinterNummer==k) break;
		if(j<30)copy(TbAfdrukPost[j].Naam,def_afdrukpostnaam_,30);
	}
	zeros(spec_afdrukpostnaam_,sizeof spec_afdrukpostnaam_);
	k=TbDocument[nr_].SpecialAfdrukPostNr;
	if(k>0 && k<=20)copy(TbAfdrukPost[k-1].Naam,spec_afdrukpostnaam_,30);
	else if(k>100){
		for(j=20;j<30;j++) if(TbAfdrukPost[j].JmsPrinterNummer==k) break;
		if(j<30)copy(TbAfdrukPost[j].Naam,spec_afdrukpostnaam_,30);
	}
 
  FOREVER{
		redo:
	  scrget(3,3);z=1;
		DisplayMenuTitel(0,"Afdrukinstellingen van een document",0xA);
	 	if(fl_updnaam_) scrifld(z++,fm_us30,TbDocument[nr_].Naam); else scrifld(z++,fm_os30,TbDocument[nr_].Naam);
		scrifld(-z,fm_uu2,&TbDocument[nr_].PapierNr);z++;
		scraddpicto(1,z-1,0,0,2,1,112,0,4,"zoek");scraddpicto(2,z-1,4,0,2,1,583,0,0,"PDF");
		scrifld(z++,fm_os30,papiernaam_);
		scrifld(z++,fm_uu2,&TbDocument[nr_].OverlayNr);
		scrifld(z++,fm_us5U,&TbDocument[nr_].MailTemplate);
		scrifld(-z,fm_uu3,&TbDocument[nr_].DefaultAfdrukPostNr);z++;
		scraddpicto(11,z-1,1,0,2,1,112,0,4,"zoek"); scrifld(z++,fm_os30,def_afdrukpostnaam_);
		if(TbDocument[nr_].DefaultAfdrukPostNr && def_afdrukpostnaam_[0]) {scraddpicto(21,z-1,0,0,2,1,64,0,5,"info"); }
		scrifld(-z,fm_uu3,&TbDocument[nr_].SpecialAfdrukPostNr);z++;
		scraddpicto(12,z-1,1,0,2,1,112,0,4,"zoek"); 	scrifld(z++,fm_os30,spec_afdrukpostnaam_);
		if(TbDocument[nr_].SpecialAfdrukPostNr && spec_afdrukpostnaam_[0]) {
			scraddpicto(22,z-1,0,0,2,1,64,0,5,"info"); scraddpicto(32,z-1,2,0,2,1,31,0,3,"wis");
		}
		for(k=0;k<6;k++) scrifld(z++,fm_uJN,&TbDocument[nr_].Opties[k]);
		key=scrupd(curs,0x3E0);curs=1;curspos_=fldcurs;
	  if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==106){
			copy(TbDocument[30].Naam,TbDocument[nr_].Naam,sizeof TbDocument[0]); // terugzetten  
			break;
		}
		if(key==110){if(fl_updnaam_) fl_updnaam_=NO; else fl_updnaam_=YES; goto redo;}
		if(key==5001){
			k=SelecteerPapier("Selectie papiersoort",NO);
			if(k>=0) TbDocument[nr_].PapierNr=k+1;
		}
		if(key==5002) TbDocument[nr_].PapierNr=0;// pdf
		zero(papiernaam_,sizeof papiernaam_);
		if(TbDocument[nr_].PapierNr==0) copy0("Afdruk naar PDF",papiernaam_,30);
		else{
		  if(TbDocument[nr_].PapierNr>20){errnum=34;curs=2;goto redo;}
      if(TbPapier[TbDocument[nr_].PapierNr-1].Naam[0]=='\0'){errnum=34;curs=2;goto redo;}
		  else copy(TbPapier[TbDocument[nr_].PapierNr-1].Naam,papiernaam_,30);
		}
		if(key==5021 || key==5022){
			k=0;
			if(key==5021) k=TbDocument[nr_].DefaultAfdrukPostNr;
			if(key==5022) k=TbDocument[nr_].SpecialAfdrukPostNr;
			for(j=0;j<30;j++) if(TbAfdrukPost[j].JmsPrinterNummer==k) break;
			if(k && j<30) UpdateAfdrukPostSettings(j);
		}
		if(key==5011 || key==5012){
			k=SelecteerAfdrukPost("Selectie afdrukpost",NO);
			if(k>=0) {
				if(key==5011) TbDocument[nr_].DefaultAfdrukPostNr=TbAfdrukPost[k].JmsPrinterNummer;
				if(key==5012) TbDocument[nr_].SpecialAfdrukPostNr=TbAfdrukPost[k].JmsPrinterNummer;
			}
 		}
		if(key==5032){ // delete speciale afdrukpost 
			TbDocument[nr_].SpecialAfdrukPostNr=0;
		}
		zeros(def_afdrukpostnaam_,sizeof def_afdrukpostnaam_);
		k=TbDocument[nr_].DefaultAfdrukPostNr;if(k==0){errnum=34;curs=6;goto redo;}//default moet ingevuld zijn 
	  if(k>0 && k<=20)copy(TbAfdrukPost[k-1].Naam,def_afdrukpostnaam_,30);
	  else if(k>100){
			for(j=20;j<30;j++) if(TbAfdrukPost[j].JmsPrinterNummer==k) break;
			if(j<30)copy(TbAfdrukPost[j].Naam,def_afdrukpostnaam_,30);
		}
		if(k && def_afdrukpostnaam_[0]=='\0') {errnum=34;curs=6;goto redo;}
		zeros(spec_afdrukpostnaam_,sizeof spec_afdrukpostnaam_);
		k=TbDocument[nr_].SpecialAfdrukPostNr;
		if(k>0 && k<=20)copy(TbAfdrukPost[k-1].Naam,spec_afdrukpostnaam_,30);
		else if(k>100){
			for(j=20;j<30;j++) if(TbAfdrukPost[j].JmsPrinterNummer==k) break;
			if(j<30)copy(TbAfdrukPost[j].Naam,spec_afdrukpostnaam_,30);
		}
		if(k && spec_afdrukpostnaam_[0]=='\0') {errnum=34;curs=8;goto redo;}
		if(key==18){ // autoenter
			if(curspos_==2) {curs=3;goto redo;}
			if(curspos_==6) {curs=7;goto redo;}
			if(curspos_==8) {curs=9;goto redo;}
		}
		if(key==108){
		  sysget(18000+nr_*16,16,buf_);
	    buf_[0]=TbDocument[nr_].PapierNr;
	    buf_[1]=TbDocument[nr_].OverlayNr;
			buf_[2]=0;buf_[3]=0;
	    for(k=0;k<8;k++){
				if(TbDocument[nr_].Opties[k]=='J') buf_[2]|=(1<<k);
				if(TbDocument[nr_].Opties[k+8]=='J') buf_[3]|=(1<<k);
	    }
	    copy(TbDocument[nr_].MailTemplate,&buf_[4],5);
			buf_[9]=TbDocument[nr_].SpecialAfdrukPostNr;
			sysput(18000+nr_*16,16,buf_);
			keystr_="SetIniKeyValue|Document-"; 
	    zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(nr_+1),3,0); keystr_+=CString(buf_);
	    keystr_+="_Settings|Name|";keystr_+=CString(TbDocument[nr_].Naam);
			cstr_=JmsCmd(keystr_); // wegschrijven in jms 
			keystr_="SetIniKeyValue|Document-"; 
	    zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(nr_+1),3,0); keystr_+=CString(buf_);
	    keystr_+="_Settings|Printer|";
			if(TbDocument[nr_].DefaultAfdrukPostNr){
	 	    zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(TbDocument[nr_].DefaultAfdrukPostNr),3,0); keystr_+=CString(buf_);
			} else keystr_+=" ";
		  cstr_=JmsCmd(keystr_); // wegschrijven in jms 
			break;
    }
	}
}


  
static void PapierInstellingen(void)
{
	int k;

	FOREVER{
		k=SelecteerPapier("Aanpassen papiersoorten",YES);
		if(k<0) break;
		UpdatePapierSoort(k);
	}
}

static int SelecteerPapier(char *ptitel_,int update_)
{
  int16 k,key,z,nr_;
 
	
  FOREVER{
	redo:;
  	scrget(3,16);z=1;nr_=0;
		DisplayMenuTitel(0,ptitel_,0xA);
		
	  for(k=0;k<10;k++){// vanaf 1 laten tellen !!
		  k++;scrifld(z++,fm_ou2S,&k);k--;
			scrifld(z++,fm_os30,&TbPapier[k].Naam);
      k+=11;scrifld(z++,fm_ou2S,&k);k-=11;
		  scrifld(z++,fm_os30,&TbPapier[k+10].Naam);
	  }
	  scrifld(z++,fm_uu2,&nr_);
		key=scrupd(1,0x181);
	  if(key==101) break;
	  if(nr_<1 || nr_>20) {errnum=34;goto redo;}
  	if(update_ || TbPapier[nr_-1].Naam[0]) return nr_-1;
  }
	return -1;
}
  
static void UpdatePapierSoort(int nr_)
{
	int j,k,z,n,key,curs=1,last_fm_,curspos_;
	char papiernaam_[30],buf_[20];
	CString keystr_,cstr_,cstr1_;

	copy(TbPapier[nr_].Naam,TbPapier[20].Naam,sizeof TbPapier[0]); // om bij F6 gemakkelijk terug te zetten
	zeros(papiernaam_,sizeof papiernaam_);k=TbPapier[nr_].DefaultFm-1;
	if(k>=0 && k<Q_DEFAULT_FM) copy(DefaultFm[k].Naam,papiernaam_,30);
	else {copy0("AFWIJKENDE FORMAAT",papiernaam_,30);}
	last_fm_=TbPapier[nr_].DefaultFm;
  FOREVER{
		redo:
	  scrnum=0;scrget(3,4);z=1;
		DisplayMenuTitel(0,"Instellingen papiersoort",0xA);
	  scrifld(z++,fm_us30,TbPapier[nr_].Naam);
		scrifld(-z,fm_uu2,&TbPapier[nr_].DefaultFm);z++;
		scraddpicto(1,z-1,1,0,2,1,112,0,4,"zoek");
		scrifld(z++,fm_os30,papiernaam_);
		key=scrupd(curs,0x2E0);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==106){
			copy(TbPapier[20].Naam,TbPapier[nr_].Naam,sizeof TbPapier[0]); 
			break;
		}
		if(key==5001){
			zeros(TbSelectie,sizeof TbSelectie);
			for(k=0;k<Q_DEFAULT_FM;k++){
				copy(DefaultFm[k].Naam,TbSelectie[k].Naam,30); 
			}
			k=DisplayTbSelectie(k,50,"Selectie standaard papiersoort");
			if(k>=0) TbPapier[nr_].DefaultFm=k+1;
		}
		k=TbPapier[nr_].DefaultFm;
		if(last_fm_!=k){
			if(k>0 && k<=Q_DEFAULT_FM){
				copy((char *)&DefaultFm[k-1].Formaat[0],(char *)&TbPapier[nr_].Formaat[0], sizeof TbPapier[nr_].Formaat);
				TbPapier[nr_].Type=DefaultFm[k-1].Type;
			}
			else if(k!=99){errnum=34;curs=2; goto redo;}
		}
		
		if(key==110) UpdateFmDetail(nr_);
		for(n=0;n<Q_DEFAULT_FM;n++){
			for(j=0;j<7;j++) if(DefaultFm[n].Formaat[j]!=TbPapier[nr_].Formaat[j]) break;
			if(j<7) continue;
			if(DefaultFm[n].Type==TbPapier[nr_].Type) break;
		}
		if(n<Q_DEFAULT_FM) TbPapier[nr_].DefaultFm=n+1; 
		else{
			for(j=0;j<7;j++) if(TbPapier[nr_].Formaat[j]!=0) break;
			if(j==7){// lege format, default A4 laser invullen 
				copy((char *)&DefaultFm[0].Formaat[0],(char *)&TbPapier[nr_].Formaat[0], sizeof TbPapier[nr_].Formaat);
				TbPapier[nr_].Type=DefaultFm[0].Type;
				TbPapier[nr_].DefaultFm=1;
			}
			else TbPapier[nr_].DefaultFm=99;
		}
		zeros(papiernaam_,sizeof papiernaam_);k=TbPapier[nr_].DefaultFm;
	  if(k>0 && k<=Q_DEFAULT_FM) copy(DefaultFm[k-1].Naam,papiernaam_,30);
	  else if(k==99) {copy0("AFWIJKENDE FORMAAT",papiernaam_,30);}
		else {errnum=34;curs=2; goto redo;}
		last_fm_=TbPapier[nr_].DefaultFm;
		if(key==18){ // autoenter
		  goto redo;
		}
		if(key==108){			
			keystr_="SetIniKeyValue|Paper-"; j=0;
	    zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(nr_+1),3,0); keystr_+=CString(buf_);
	    keystr_+="_Settings|";
	   
	    cstr_=JmsCmd(keystr_+CString("Name| ")+CString(TbPapier[nr_].Naam));
		
		  cstr1_=" ";
			for(j=0;j<7;j++){
				cstr1_+=Int2String(TbPapier[nr_].Formaat[j]);cstr1_+="|";
			}
			cstr1_+=CString(TbPapier[nr_].Type);
			ZCstr2Arr(Rec_Ele(cstr_,7,'|'),buf_,2);TbPapier[nr_].Type=buf_[0];
			cstr_=JmsCmd(keystr_+CString("LayoutData|")+cstr1_);
			break;
		}
  }
} 
  
static void UpdateFmDetail(int nr_)
{
	int16 k,z,key,curs=1,attr_,formaat_[7],curspos_;
	char type_;
	
	for(k=0;k<7;k++) formaat_[k]=TbPapier[nr_].Formaat[k];type_=TbPapier[nr_].Type;
	if(type_=='W'){
      for(k=0;k<7;k++) formaat_[k]=dots2mm(formaat_[k]);
  }
	else if(type_=='L'){
		formaat_[4]=dots2mm(formaat_[4]);
    formaat_[5]=dots2mm(formaat_[5]);
	}
  
  FOREVER{
		redo:
	  scrget(3,5);z=1;
		DisplayMenuTitel(0,"Detail papierformaat",0xA);
	  scrifld(z++,fm_us30,TbPapier[nr_].Naam);
		
	  attr_=0x02;
    if(type_=='S') attr_=0x09;
    else if(type_=='L') attr_=0x0A;
    else if(type_=='W') attr_=0x0B;
		for(k=0;k<7;k++) scrxfld(z++,fm_ui4,(char *)&formaat_[k],attr_);
    scrxfld(-z,fm_uRKSLW,&type_,attr_);z++;
    key=scrupd(curs,0xE0);curspos_=fldcurs;
		if(key==106) break;
		if(key==18){curs=curspos_+1; goto redo;}
		if(key==108){	
			if(type_=='W'){
        for(k=0;k<7;k++) formaat_[k]=mm2dots(formaat_[k]);
			}
			else if(type_=='L'){
		   formaat_[4]=mm2dots(formaat_[4]);
			 formaat_[5]=mm2dots(formaat_[5]);
			}
			for(k=0;k<7;k++) TbPapier[nr_].Formaat[k]=formaat_[k];
			TbPapier[nr_].Type=type_;
			break;
		}
	}
}

static int16 dots2mm(int16 dots)
{
  float qlv_;

  qlv_=dots; qlv_/=300.; qlv_*=254.;
  qlv_=round((double)(qlv_),(double)1.);
  return (int16)(qlv_);
}
 
static int16 mm2dots(int16 mm)
{
  float qlv_;
					
  qlv_=mm; qlv_*=300.; qlv_/=254.;
  qlv_=round((double)(qlv_),(double)1.);
  return (int16)(qlv_);
}


static void AfdrukPostInstellingen(void)
{
	int k;

	FOREVER{
		k=SelecteerAfdrukPost("AfdrukPosten",YES);
		if(k<0) break;
		UpdateAfdrukPostSettings(k);
	}
}

static int SelecteerAfdrukPost(char *ptitel_,int update_)
{
  int16 k,key,z,nr_;

  FOREVER{
	redo:;
  	scrget(3,2);z=1;nr_=0;
		DisplayMenuTitel(0,ptitel_,0xA);
  	for(k=0;k<15;k++){
			if(update_ || TbAfdrukPost[k].Naam[0]){ 
	      k++;scrifld(z++,fm_ou2,&k);k--;
	  	  scrifld(z++,fm_os30,&TbAfdrukPost[k].Naam);
			} else z+=2;
			if(update_ || TbAfdrukPost[k+15].Naam[0]){ 
        k+=16;scrifld(z++,fm_ou2,&k);k-=16;
		    scrifld(z++,fm_os30,&TbAfdrukPost[k+15].Naam);
			} else z+=2;
  	}
	  scrifld(z++,fm_uu2,&nr_);
	  key=scrupd(1,0x181);
	  if(key==101) return -1;
	  if(nr_<1 || nr_>30) {errnum=34;goto redo;}
		if(update_ || TbAfdrukPost[nr_-1].Naam[0]) return nr_-1;
  }
	return -1;
}

static void UpdateAfdrukPostSettings(int nr_)
{
	int k,z,key,curs=1,curspos_,kol_,len_,pos_,pos1_;
	char buf_[20];
	CString keystr_,cstr_,cstr1_,findstr_;
	 

	if(nr_>=20) goto endsr; // posten op afstand via JMM
	copy(TbAfdrukPost[nr_].Naam,TbAfdrukPost[30].Naam,sizeof TbAfdrukPost[0]); // voor te annuleren 
 
	FOREVER{
		redo:
	  scrnum=0;scrget(3,6);z=1;
		DisplayMenuTitel(0,"Afdrukpost-instellingen",0xA);
	 	scrifld(z++,fm_us30,TbAfdrukPost[nr_].Naam);
		scrifld(z++,fm_us50,TbAfdrukPost[nr_].NaamWindows);scraddpicto(1,z-1,1,0,2,1,112,0,4,"zoek"); 
		scrifld(z++,fm_us50,TbAfdrukPost[nr_].BinName);scraddpicto(2,z-1,1,0,2,1,112,0,4,"zoek"); 
		scrifld(z++,fm_us50,TbAfdrukPost[nr_].MediaName);scraddpicto(3,z-1,1,0,2,1,112,0,4,"zoek"); 
		scrifld(z++,fm_us50,TbAfdrukPost[nr_].PaperName);scraddpicto(4,z-1,1,0,2,1,112,0,4,"zoek"); 
		scrifld(z++,fm_us50,TbAfdrukPost[nr_].JamosDriverName);scraddpicto(5,z-1,1,0,2,1,112,0,4,"zoek"); 
  	key=scrupd(curs,0x3E0);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==106){
			copy(TbAfdrukPost[30].Naam,TbAfdrukPost[nr_].Naam,sizeof TbAfdrukPost[0]); // terugzetten  
			break;
		}
		if(TbAfdrukPost[nr_].Naam[0]=='\0'){errnum=38;curs=1;/* goto redo;*/}
	  if(key==5001){
			cstr_=JmsCmd("GetAllPrinters");
			zeros(TbSelectie,sizeof TbSelectie);kol_=0;pos_=0;pos1_=0;
			for(k=0;k<MAX_TBSELECTIE;k++){
				pos1_=cstr_.Find('\n',pos_+1); if(pos1_<0) break;
				findstr_=cstr_.Mid(pos_,pos1_-pos_);
				cstr1_=Rec_Ele(findstr_,0,'|');
			  len_=ZCstr2Arr(cstr1_,TbSelectie[k].Naam,50); 
				pos_=pos1_+1;
			}
			k=DisplayTbSelectie(k,50,"Selectie Windowsprinter");
			if(k<0) goto redo;
			copy(TbSelectie[k].Naam,TbAfdrukPost[nr_].NaamWindows,sizeof TbAfdrukPost[0].NaamWindows);
			zeros(TbAfdrukPost[nr_].BinName,sizeof TbAfdrukPost[0].BinName);TbAfdrukPost[nr_].BinRef=0;
			zeros(TbAfdrukPost[nr_].MediaName,sizeof TbAfdrukPost[0].MediaName);TbAfdrukPost[nr_].MediaRef=0;
			zeros(TbAfdrukPost[nr_].PaperName,sizeof TbAfdrukPost[0].PaperName);TbAfdrukPost[nr_].PaperRef=0;
		}
	  if(key==5002){
			cstr_="GetAllPrinterBins|";cstr_+=TbAfdrukPost[nr_].NaamWindows;
			cstr_=JmsCmd(cstr_);
			zeros(TbSelectie,sizeof TbSelectie);kol_=0;pos_=0;pos1_=0;
			for(k=0;k<MAX_TBSELECTIE;k++){
				pos1_=cstr_.Find('\n',pos_+1); if(pos1_<0) break;
				findstr_=cstr_.Mid(pos_,pos1_-pos_);
				z=String2Int(Rec_Ele(findstr_,0,'|'));if(z==0) break;TbSelectie[k].Nr=z;
				cstr1_=Rec_Ele(findstr_,1,'|');
			  len_=ZCstr2Arr(cstr1_,TbSelectie[k].Naam,50); 
				pos_=pos1_+1;
			}
			k=DisplayTbSelectie(k,50,"Selectie lade");
			if(k<0) goto redo;
			copy(TbSelectie[k].Naam,TbAfdrukPost[nr_].BinName,sizeof TbAfdrukPost[0].BinName);
			TbAfdrukPost[nr_].BinRef=TbSelectie[k].Nr;
		}
 	  if(key==5003){
			cstr_="GetAllPrinterMedia|";cstr_+=TbAfdrukPost[nr_].NaamWindows;
			cstr_=JmsCmd(cstr_);
			zeros(TbSelectie,sizeof TbSelectie);kol_=0;pos_=0;pos1_=0;
			for(k=0;k<MAX_TBSELECTIE;k++){
				pos1_=cstr_.Find('\n',pos_+1); if(pos1_<0) break;
				findstr_=cstr_.Mid(pos_,pos1_-pos_);
				z=String2Int(Rec_Ele(findstr_,0,'|'));if(z==0) break;TbSelectie[k].Nr=z;
				cstr1_=Rec_Ele(findstr_,1,'|');
			  len_=ZCstr2Arr(cstr1_,TbSelectie[k].Naam,50); 
				pos_=pos1_+1;
			}
			k=DisplayTbSelectie(k,50,"Selectie media");
			if(k<0) goto redo;
			copy(TbSelectie[k].Naam,TbAfdrukPost[nr_].MediaName,sizeof TbAfdrukPost[0].MediaName);
			TbAfdrukPost[nr_].MediaRef=TbSelectie[k].Nr;
		}
	  if(key==5004){
			cstr_="GetAllPrinterPapers|";cstr_+=TbAfdrukPost[nr_].NaamWindows;
			cstr_=JmsCmd(cstr_);
			zeros(TbSelectie,sizeof TbSelectie);kol_=0;pos_=0;pos1_=0;
			for(k=0;k<MAX_TBSELECTIE;k++){
				pos1_=cstr_.Find('\n',pos_+1); if(pos1_<0) break;
				findstr_=cstr_.Mid(pos_,pos1_-pos_);
				z=String2Int(Rec_Ele(findstr_,0,'|'));if(z==0) break;TbSelectie[k].Nr=z;
				cstr1_=Rec_Ele(findstr_,1,'|');
			  len_=ZCstr2Arr(cstr1_,TbSelectie[k].Naam,50); 
				pos_=pos1_+1;
			}
			k=DisplayTbSelectie(k,50,"Selectie papier");
			if(k<0) goto redo;
			copy(TbSelectie[k].Naam,TbAfdrukPost[nr_].PaperName,sizeof TbAfdrukPost[0].PaperName);
			TbAfdrukPost[nr_].PaperRef=TbSelectie[k].Nr;
		}
		if(key==5005){
			zeros(TbSelectie,sizeof TbSelectie);
			for(k=0;k<Q_JAMOSDRIVERS;k++){
				TbSelectie[k].Nr=k+1;copy0(JamosDrivers[k].Naam,TbSelectie[k].Naam,50);
			}
			k=DisplayTbSelectie(k,50,"Selectie printerdriver");
			if(k<0) goto redo;
			copy(TbSelectie[k].Naam,TbAfdrukPost[nr_].JamosDriverName,30);
			TbAfdrukPost[nr_].JamosDriver=JamosDrivers[k].Nr;
		}
	  if(key==108){
    	keystr_="SetIniKeyValue|Printer-"; 
  	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(nr_+1),3,0); keystr_+=CString(buf_);
  	  keystr_+="_Settings|";
	   
    	cstr_=CString("Name| ");cstr_+=CString(TbAfdrukPost[nr_].Naam);JmsCmd(keystr_+cstr_);
	    cstr_=CString("NamePrinter| ");cstr_+=CString(TbAfdrukPost[nr_].NaamWindows);JmsCmd(keystr_+cstr_);
  		cstr_=CString("BinName| ");cstr_+=CString(TbAfdrukPost[nr_].BinName);JmsCmd(keystr_+cstr_);
  		cstr_=CString("BinRef| ");cstr_+=Int2String(TbAfdrukPost[nr_].BinRef);JmsCmd(keystr_+cstr_);
  		cstr_=CString("MediaName| ");cstr_+=CString(TbAfdrukPost[nr_].MediaName);JmsCmd(keystr_+cstr_);
    	cstr_=CString("MediaRef| ");cstr_+=Int2String(TbAfdrukPost[nr_].MediaRef);JmsCmd(keystr_+cstr_);
  		cstr_=CString("PaperName| ");cstr_+=CString(TbAfdrukPost[nr_].PaperName);JmsCmd(keystr_+cstr_);
	  	cstr_=CString("PaperRef| ");cstr_+=Int2String(TbAfdrukPost[nr_].PaperRef);JmsCmd(keystr_+cstr_);
			cstr_=CString("JamosDriver| ");cstr_+=Int2String(TbAfdrukPost[nr_].JamosDriver);JmsCmd(keystr_+cstr_);
     	break;
		}
	}
	endsr:;
}
static void WerkPostInstellingen(void)
{
	int k;

	if(ServerVersion==SERVER_MONO) UpdateWerkPost(0);
	else{
		FOREVER{
			k=SelecteerWerkPost("Aanpassen instellingen werkpost",YES);
			if(k<0) break;
			UpdateWerkPost(k);
		}
	}
}

static int SelecteerWerkPost(char *ptitel_,int update_)
{
  int16 k,key,z,nr_,start_=0;
 
	
  FOREVER{
	redo:;
  	scrget(3,10);z=1;nr_=0;
		DisplayMenuTitel(0,ptitel_,0xA);
		
	  for(k=start_;k<start_+15;k++){// vanaf 1 laten tellen !!
			if(k>=MAX_WERKPOST) z+=4;
			else{
				k++;scrifld(z++,fm_ou2S,&k);k--;
				scrifld(z++,fm_os30,&TbWerkPost[k].Naam);
				if((k+15)<MAX_WERKPOST){
					k+=16;scrifld(z++,fm_ou2S,&k);k-=16;
	  			scrifld(z++,fm_os30,&TbWerkPost[k+15].Naam);
				} else z+=2;
			}
	  }
	  scrifld(z++,fm_uu2,&nr_);
		key=scrupd(1,0x187);
	  if(key==101) break;
		if(key==102){ start_-=30; if(start_<0) start_=0; goto redo;}
		if(key==103){ start_+=30; if(start_>=MAX_WERKPOST) start_-=30; goto redo;}
	  if(nr_<1 || nr_>MAX_WERKPOST) {errnum=34;goto redo;}
	  if(update_ || TbWerkPost[nr_-1].Naam[0]) return nr_-1;
  }
	return -1;
} 


static void UpdateWerkPost(int nr_)
{
	int k,z,key,curs=1;
	char buf_[20],tbnewafdrukpost[10][30];
	CString keystr_,cstr_,cstr1_;
	struct s_TbWerkPost tmp_post_;
	  
	copy(TbWerkPost[nr_].Naam,tmp_post_.Naam,sizeof TbWerkPost[0]); // voor te annuleren 
  zero(tbnewafdrukpost[0],sizeof tbnewafdrukpost);

	FOREVER{

	  scrnum=0;scrget(3,7);z=1;
		DisplayMenuTitel(0,"Instellingen werkpost",0xA);
	 	scrifld(z++,fm_us30,TbWerkPost[nr_].Naam);
		scrifld(z++,fm_uJN,&TbWerkPost[nr_].DisplayJamadataBrief);
		scrifld(z++,fm_uJN,&TbWerkPost[nr_].DisplayEmailAsEML);
		scrifld(z++,fm_uJN,&TbWerkPost[nr_].AllowMasterFunctions);
		scrifld(z++,fm_uu2,&TbWerkPost[nr_].FiliaalNummer);
		for(k=0;k<4;k++){
			if(sys1788) scrifld(z++,fm_us3_U,&TbWerkPost[nr_].ScreenBootDossier[k]); else scrifld(z++,fm_os3,"---");
			scrifld(z++,fm_us20,&TbWerkPost[nr_].ScreenBootSequence[k]);
			scrifld(z++,fm_uu2,&TbWerkPost[nr_].ScreenColorNummer[k]);
		}
	  key=scrupd(curs,0x3E0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==106){
			copy(tmp_post_.Naam,TbWerkPost[nr_].Naam,sizeof TbWerkPost[0]); // terugzetten    
			break;
		}
		if(TbWerkPost[nr_].Naam[0]=='\0'){TbWerkPost[nr_].Naam[0]=' ';errnum=38;curs=1; }
	  if(key==108){
    	keystr_="SetIniKeyValue|Post-"; 
  	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(nr_+1),3,0); keystr_+=CString(buf_);
  	  keystr_+="_Settings|";
	    
    	cstr_=CString("Name|");cstr_+=CString(TbWerkPost[nr_].Naam);JmsCmd(keystr_+cstr_);
	    cstr_=CString("SendAllPrintToPost| ");if(TbWerkPost[nr_].PrintLocal=='J') cstr_+=CString("1");JmsCmd(keystr_+cstr_);
			cstr_=CString("HoldPrintJobsOnServer| ");if(TbWerkPost[nr_].HoldPrintJobsOnServer=='J') cstr_+=CString("1");JmsCmd(keystr_+cstr_);
  		cstr_=CString("DisplayJamadataBrief| ");if(TbWerkPost[nr_].DisplayJamadataBrief=='J') cstr_+=CString("1");JmsCmd(keystr_+cstr_);
			cstr_=CString("DisplayEmailAsEML| ");if(TbWerkPost[nr_].DisplayEmailAsEML=='J') cstr_+=CString("1");JmsCmd(keystr_+cstr_);
			cstr_=CString("AllowMasterFunctions| ");if(TbWerkPost[nr_].AllowMasterFunctions=='J') cstr_+=CString("1");JmsCmd(keystr_+cstr_);
			cstr_=CString("MemberOfFiliaal| ");sprintf_s(buf_,sizeof buf_,"%02d",TbWerkPost[nr_].FiliaalNummer); cstr_+=CString(buf_);JmsCmd(keystr_+cstr_);
			for(k=1;k<=4;k++){
				cstr1_.Format("Scherm-%03d",k); 
	  		cstr_=CString("_BootDossier| "); cstr_+=CString(TbWerkPost[nr_].ScreenBootDossier[k-1]);JmsCmd(keystr_+cstr1_+cstr_);
	  		cstr_=CString("_BootSequence| "); cstr_+=CString(TbWerkPost[nr_].ScreenBootSequence[k-1]);JmsCmd(keystr_+cstr1_+cstr_);
				cstr_=CString("_BackGroundColor| ");
				zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(TbWerkPost[nr_].ScreenColorNummer[k-1]),2,0); cstr_+=CString(buf_);
        JmsCmd(keystr_+cstr1_+cstr_);
			}
	  	break;
		}
	}
}

 
static int DisplayTbSelectie(int q_elem_,int max_h,char *ptitel)
{
  int16 nr_,k,key,z,start_,lijnpos,q_,retval_,ScreenLines=17;
	unsigned short funckeys;
 
	if(q_elem_<=0) {errnum=38;return -1;}
	if(q_elem_==1) return 0;
  retval_=-1;

  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
    scrget(3,11);z=1;q_=0; funckeys=0x80E1;
		DisplayMenuTitel(0,ptitel,0xA);
		if(start_>0){ funckeys+=2; scraddpicto(1,0,74,2,4,2,18,0,4,"up"); }
		if((start_+ScreenLines)<q_elem_) {funckeys+=4;scraddpicto(2,0,74,21,4,2,13,0,4,"down"); }
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=q_elem_) break;
	    k++;scrifld(z++,fm_ou4,&k);k--;
	    scrifld(z++,fm_os63,TbSelectie[k].Naam); q_++;
			if(q_==(lijnpos+1)) scrchat(z-1,0x8); else scrchat(z-1,0xFF);
    }
    scrifld(35,fm_uu4,&nr_);
    key=scrupd(36,funckeys);
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
			case 103     : if((start_+ScreenLines)<q_elem_) {start_+=ScreenLines;lijnpos=0;scrnum=0;}
										 break;
			case 10      : start_=0;lijnpos=0;scrnum=0;// HOME 
										 break;
			case 11      : start_=q_elem_-ScreenLines;if(start_<0) start_=0;// END 
										 lijnpos=0;scrnum=0;
										 break;
			case 101     :
			case 106     : goto end;// annuleer 
										 break;
			case 18      :// ENTER 
			case 15      : // TAB  
			case 108     : if(nr_>q_elem_) errnum=34;// neem aan en exit 
										 else{
											 if(nr_>0) retval_=nr_-1;
											 else retval_=start_+lijnpos;
											 goto end;
										 }
										 break;
			default      : break;
    }
	}
	end:;
	return retval_;
}

static void MailSettings(void)
{
	int16 key,profielnr_=0;

	FOREVER{
		scrget(3,14);
		scraddpicto(1,0,76,22,4,2,133,0,3,"Schrap verouderde mails");
		scrifld(1,fm_uu1,&profielnr_);
		key=scrupd(1,0x81);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
    if(key==5001) DeleteOldMail();
		if(key==108) UpdateMailSettings(profielnr_);
	}
}



static void UpdateMailSettings(int16 profielnr_)
{
	int z_, key_, curs_ = 1;
	CString keystr_, cstr_, cnr_;
	char profieltxt_[25];

	cnr_ = CString("");
	memset(profieltxt_, 0, sizeof profieltxt_);

	if (profielnr_)
	{
		cnr_.Format("%d", profielnr_);
		sprintf_s(profieltxt_, 20, "Profiel %d", profielnr_);
	}
	else bcopy("Standaard", profieltxt_, 9);

	zero(TbMailSettings.ImapServer, sizeof TbMailSettings);
	keystr_ = "GetIniKeyValue|MailSettings|";

	cstr_ = JmsCmd(keystr_ + CString("ImapServer") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.ImapServer, sizeof TbMailSettings.ImapServer);
	cstr_ = JmsCmd(keystr_ + CString("ImapUser") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.ImapUser, sizeof TbMailSettings.ImapUser);
	cstr_ = JmsCmd(keystr_ + CString("ImapPassword") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.ImapPassword, sizeof TbMailSettings.ImapPassword);
	cstr_ = JmsCmd(keystr_ + CString("ImapFolderConcepts") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.ImapFolderConcepts, sizeof TbMailSettings.ImapFolderConcepts);
	cstr_ = JmsCmd(keystr_ + CString("ImapFolderToCheck") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.ImapFolderToCheck, sizeof TbMailSettings.ImapFolderToCheck);
	cstr_ = JmsCmd(keystr_ + CString("ImapFolderToSend") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.ImapFolderToSend, sizeof TbMailSettings.ImapFolderToSend);
	cstr_ = JmsCmd(keystr_ + CString("ImapFolderFault") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.ImapFolderFault, sizeof TbMailSettings.ImapFolderFault);
	cstr_ = JmsCmd(keystr_ + CString("ImapFolderSent") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.ImapFolderSent, sizeof TbMailSettings.ImapFolderSent);
	cstr_ = JmsCmd(keystr_ + CString("MailFromName") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.MailFromName, sizeof TbMailSettings.MailFromName);
	cstr_ = JmsCmd(keystr_ + CString("MailFromAddress") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.MailFromAddress, sizeof TbMailSettings.MailFromAddress);
	cstr_ = JmsCmd(keystr_ + CString("MailReplyTo") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.MailReplyTo, sizeof TbMailSettings.MailReplyTo);
	cstr_ = JmsCmd(keystr_ + CString("MailConfirmReceiptTo") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.MailConfirmReceiptTo, sizeof TbMailSettings.MailConfirmReceiptTo);
	cstr_ = JmsCmd(keystr_ + CString("MailConfirmReadTo") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.MailConfirmReadTo, sizeof TbMailSettings.MailConfirmReadTo);
	cstr_ = JmsCmd(keystr_ + CString("MailBcc") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.MailBcc, sizeof TbMailSettings.MailBcc);
	cstr_ = JmsCmd(keystr_ + CString("MailRelayserver") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.MailRelayserver, sizeof TbMailSettings.MailRelayserver);
	cstr_ = JmsCmd(keystr_ + CString("Relay1Server") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay1Server, sizeof TbMailSettings.Relay1Server);
	cstr_ = JmsCmd(keystr_ + CString("Relay1Port") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay1Port, sizeof TbMailSettings.Relay1Port);
	cstr_ = JmsCmd(keystr_ + CString("Relay1UserName") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay1UserName, sizeof TbMailSettings.Relay1UserName);
	cstr_ = JmsCmd(keystr_ + CString("Relay1Password") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay1Password, sizeof TbMailSettings.Relay1Password);
	cstr_ = JmsCmd(keystr_ + CString("Relay1Security") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay1Security, sizeof TbMailSettings.Relay1Security);
	cstr_ = JmsCmd(keystr_ + CString("Relay2Server") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay2Server, sizeof TbMailSettings.Relay2Server);
	cstr_ = JmsCmd(keystr_ + CString("Relay2Port") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay2Port, sizeof TbMailSettings.Relay2Port);
	cstr_ = JmsCmd(keystr_ + CString("Relay2UserName") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay2UserName, sizeof TbMailSettings.Relay2UserName);
	cstr_ = JmsCmd(keystr_ + CString("Relay2Password") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay2Password, sizeof TbMailSettings.Relay2Password);
	cstr_ = JmsCmd(keystr_ + CString("Relay2Security") + cnr_); ZCstr2Arr(cstr_, TbMailSettings.Relay2Security, sizeof TbMailSettings.Relay2Security);

	FOREVER
	{
		scrget(3, 8); z_ = 1; scraddpicto(50, 0, 76, 0, 4, 2, 105, 1, 7, "^!B2800A");
		AddTextKey(20, 60, 22, 20, 2, 5001, "Stuur testmail", 0x007FFF);
		scrifld(z_++, fm_os10, profieltxt_);
		scrifld(z_++, fm_us50, TbMailSettings.MailFromName);
		scrifld(z_++, fm_us50, TbMailSettings.MailFromAddress);
		scrifld(z_++, fm_us50, TbMailSettings.MailReplyTo);
		scrifld(z_++, fm_us50, TbMailSettings.MailBcc); 
		scrifld(z_++, fm_us50, TbMailSettings.MailConfirmReceiptTo);
		scrifld(z_++, fm_us50, TbMailSettings.MailConfirmReadTo);
		scrifld(z_++, fm_us1,  TbMailSettings.MailRelayserver);

		scrifld(z_++, fm_us50,   TbMailSettings.ImapServer);
		scrifld(z_++, fm_us30,   TbMailSettings.ImapUser);
		scrifld(z_++, fm_us40PW, TbMailSettings.ImapPassword);
		scrifld(z_++, fm_us40,   TbMailSettings.ImapFolderConcepts);
		scrifld(z_++, fm_us40,   TbMailSettings.ImapFolderToCheck);
		scrifld(z_++, fm_us40,   TbMailSettings.ImapFolderToSend);
		scrifld(z_++, fm_us40,   TbMailSettings.ImapFolderFault);
		scrifld(z_++, fm_us40,   TbMailSettings.ImapFolderSent);
		key_ = scrupd(curs_, 0x2E0); curs_ = 1;

		if ((key_ / 0x10000) > 0)
			key_ /= 0x10000;

		if ((key_ / 0x100) == 1)
			key_ = (key_ & 0xFF) + 5000;

		if (key_ == 5050)
			continue; // link help

		if (key_ == 106)
			break;

		if (key_ == 110 && profielnr_ == 0)
			UpdateMailRelaySettings(profielnr_); // relayservers enkel toelaten op default omdat andere niet kunnen gebruikt worden

		if (key_ == 108 || key_ == 5001)
		{
			keystr_ = "SetIniKeyValue|MailSettings|";

			cstr_ = CString("ImapServer"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.ImapServer); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("ImapUser"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.ImapUser); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("ImapPassword"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.ImapPassword); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("ImapFolderConcepts"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.ImapFolderConcepts); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("ImapFolderToCheck"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.ImapFolderToCheck); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("ImapFolderToSend"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.ImapFolderToSend); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("ImapFolderFault"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.ImapFolderFault); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("ImapFolderSent"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.ImapFolderSent); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("MailFromName"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.MailFromName); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("MailFromAddress"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.MailFromAddress); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("MailReplyTo"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.MailReplyTo); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("MailConfirmReceiptTo"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.MailConfirmReceiptTo); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("MailConfirmReadTo"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.MailConfirmReadTo); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("MailBcc"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.MailBcc); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("MailRelayserver"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.MailRelayserver); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay1Server"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.Relay1Server); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay1Port"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.Relay1Port); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay1UserName"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.Relay1UserName); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay1Password"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.Relay1Password); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay1Security"); cstr_ += cnr_; cstr_ += CString("| ");; cstr_ += CString(TbMailSettings.Relay1Security); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay2Server"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.Relay2Server); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay2Port"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.Relay2Port); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay2UserName"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.Relay2UserName); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay2Password"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.Relay2Password); cstr_ = JmsCmd(keystr_ + cstr_);
			cstr_ = CString("Relay2Security"); cstr_ += cnr_; cstr_ += CString("| "); cstr_ += CString(TbMailSettings.Relay2Security); cstr_ = JmsCmd(keystr_ + cstr_);

			if (key_ == 5001)
				SendTestMail();

			break;
		}
	}
}

static void UpdateMailRelaySettings(int16 profielnr_)
{
	int z,key,curs=1;
	CString keystr_,cstr_,cnr_;

	cnr_=CString(""); 	if(profielnr_) cnr_.Format("%d",profielnr_);

  FOREVER{
	  scrget(3,9);z=1;

		scrifld(z++,fm_us50,TbMailSettings.Relay1Server);
    scrifld(z++,fm_us10,TbMailSettings.Relay1Port);
		scrifld(z++,fm_us50,TbMailSettings.Relay1UserName);
		scrifld(z++,fm_us40PW,TbMailSettings.Relay1Password);
    scrifld(z++,fm_us20,TbMailSettings.Relay1Security);

		scrifld(z++,fm_us50,TbMailSettings.Relay2Server);
    scrifld(z++,fm_us10,TbMailSettings.Relay2Port);
		scrifld(z++,fm_us50,TbMailSettings.Relay2UserName);
		scrifld(z++,fm_us40PW,TbMailSettings.Relay2Password);
    scrifld(z++,fm_us20,TbMailSettings.Relay2Security);
		key=scrupd(curs,0xE0);curs=1;
		if (key&0xFFFF0000) key/=0x10000;
		if(key==106){  // terugzetten 
      keystr_="GetIniKeyValue|MailSettings|"; 
  
			cstr_=JmsCmd(keystr_+CString("Relay1Server")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay1Server,sizeof TbMailSettings.Relay1Server);
			cstr_=JmsCmd(keystr_+CString("Relay1Port")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay1Port,sizeof TbMailSettings.Relay1Port);
			cstr_=JmsCmd(keystr_+CString("Relay1UserName")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay1UserName,sizeof TbMailSettings.Relay1UserName);
			cstr_=JmsCmd(keystr_+CString("Relay1Password")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay1Password,sizeof TbMailSettings.Relay1Password);
			cstr_=JmsCmd(keystr_+CString("Relay1Security")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay1Security,sizeof TbMailSettings.Relay1Security);
			cstr_=JmsCmd(keystr_+CString("Relay2Server")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay2Server,sizeof TbMailSettings.Relay2Server);
			cstr_=JmsCmd(keystr_+CString("Relay2Port")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay2Port,sizeof TbMailSettings.Relay2Port);
			cstr_=JmsCmd(keystr_+CString("Relay2UserName")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay2UserName,sizeof TbMailSettings.Relay2UserName);
			cstr_=JmsCmd(keystr_+CString("Relay2Password")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay2Password,sizeof TbMailSettings.Relay2Password);
			cstr_=JmsCmd(keystr_+CString("Relay2Security")+cnr_);ZCstr2Arr(cstr_,TbMailSettings.Relay2Security,sizeof TbMailSettings.Relay2Security);
			break;
		}
		if(key==108) break;
	}
}

static void SendTestMail(void)
{

  int k,p_adr_=0;
	short int yy,mm,dd;
	uint16 dt_,nr_;


		// keywords invullen 
	zero(MailMergeData[0],sizeof MailMergeData);MailSaveAdres='N';
	dt_=*u(25,2); nr_=0; 
  fasinit(2);	copy("TestMail",s(2,3),10);
	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy(s(2,3),MailMergeData[k],fldlen(2,3)); continue;}
		if(cmpstr(MailMergeKeywords[k],"ADRES",5)==0){copy(s(2,4),MailMergeData[k],fldlen(2,4)); continue;}
		if(cmpstr(MailMergeKeywords[k],"POSTCODE",8)==0){copy(s(2,5),MailMergeData[k],fldlen(2,5)); continue;}
		if(cmpstr(MailMergeKeywords[k],"GEMEENTE",8)==0){copy(s(2,6),MailMergeData[k],fldlen(2,6)); continue;}
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){p_adr_=k;copy(s(2,21),MailMergeData[k],fldlen(2,21)); continue;}
		if(fldlen(2,130) && cmpstr(MailMergeKeywords[k],"CC_EMAILADRES",13)==0){copy(s(2,130),MailMergeData[k],fldlen(2,130)); continue;}
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNAAM",12)==0){copy0("*** TESTMAIL ***",MailMergeData[k],50); continue;}
//		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNUMMER",13)==0){stcli_d(MailMergeData[k],(long)nr_,5,1); continue;}
		if(cmpstr(MailMergeKeywords[k],"DATUM",5)==0){
			jddate(dt_,&yy,&mm,&dd);
      stcli_d(&MailMergeData[k][0],(long)dd,2,0);MailMergeData[k][2]='/';
      stcli_d(&MailMergeData[k][3],(long)mm,2,0);MailMergeData[k][5]='/';
      stcli_d(&MailMergeData[k][6],(long)yy,4,0);
			continue;
		}
//		if(cmpstr(MailMergeKeywords[k],"TOTAALBEDRAG",12)==0){double2str(MailMergeData[k],(double)(bd_)); continue;}
	}
	zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage); // voor de veiligheid
	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);// MailMergeBijlage[0]=SpoolFileNr;
	zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate);
	MailMergeFormaat=11; // factuurtemplate
  MailMergeTaal='\0';
	if(SendMail(1)<1) DisplayWarning("Versturen van de mail is niet gelukt!",605,0);
//	if(k && MailSaveAdres=='J'){copy(MailMergeData[p_adr_],s(2,21),fldlen(2,21));fasupd(2);} // email adres bewaren
}

static void DeleteOldMail(void)  
{

  CString fname_,ft_search_,cstr_;
 	int16 k,jj,mm,dd,max_,key;
	uint16 dat_end=0;
	SYSTEMTIME st_,fsystime_;
	WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
  FILETIME FtimeEnd,loc_ftime_;
	 

	if(fldlen(7,1)) fileopen(7);
	redo_scr:;
	scrnum=0;scrget(3,15);
	scrifld(1,fm_udat,&dat_end);
	key=scrupd(1,0x101);
	if(key!=109) goto endsr;
	if(dat_end==0) {errnum=34;goto redo_scr;}
  if(DisplayWarning("Wenst U deze mails weg te vegen (ONHERROEPELIJK!!!) ???",605,YES)){
    scrget(1,7);scrupd(-3,0);
		GetLocalTime(&st_);
	  jddate((int)(dat_end),&jj,&mm,&dd);
	  st_.wDay=dd;st_.wMonth=mm;st_.wYear=jj;st_.wHour=17;st_.wMinute=50;SystemTimeToFileTime(&st_,&FtimeEnd);
		ft_search_=CString("..\\Mail\\Sent\\*.*");
		hSearch = FindFirstFile (ft_search_, &FileData);
		FOREVER{

			if (hSearch == INVALID_HANDLE_VALUE) break;
			if ((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) goto nextfile;                      // geen directory 
			if (CompareFileTime(&FileData.ftLastWriteTime,&FtimeEnd)>0) {
				if(fldlen(7,1)){ // toch nog echt checken omdat datum niet altijd correct is
					cstr_=CString(FileData.cFileName); k=cstr_.Find('.'); if(k!=12) goto nextfile;
				  fasinit(7);copy((char *)(LPCTSTR)cstr_,s(7,2),12);
		      if(faskeyi(7,1,0))	goto nextfile;
				  if(*u(7,4)>dat_end) goto nextfile;
				}
			  else goto nextfile; // na de gewenste periode 
			}
			fname_=CString("..\\Mail\\Sent\\");fname_+=CString(FileData.cFileName);
			remove(fname_);
			//fname_=CString(FileData.cFileName); k=fname_.Find('.'); if(k!=12) goto nextfile;
			//fasinit(7);copy((char *)(LPCTSTR)fname_,s(7,2),12);
			//if(faskeyu(7,1,0)==0) faskill(7);
			nextfile:;
			if(FindNextFile (hSearch, &FileData)==false) break;
	  }
		FindClose(hSearch);
  }

endsr:;
}

static void initload(void)
{
	int j,k,n,p_tb_printers_;
	CString keystr_,cstr_,cstr1_;
	char buf_[50];
	
	sysget(1788,2,&sys1788);
	// Jamadata-afdrukposten laden uit JMS
	zero((char *)TbAfdrukPost[0].Naam,sizeof TbAfdrukPost);  
	for(k=0;k<20;k++){
		TbAfdrukPost[k].JmsPrinterNummer=k+1;
	  keystr_="GetIniKeyValue|Printer-"; 
	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(k+1),3,0); keystr_+=CString(buf_);
	  keystr_+="_Settings|";
	   
	  cstr_=JmsCmd(keystr_+CString("Name"));ZCstr2Arr(cstr_,TbAfdrukPost[k].Naam,30);
		cstr_=JmsCmd(keystr_+CString("NamePrinter"));ZCstr2Arr(cstr_,TbAfdrukPost[k].NaamWindows,50);
		cstr_=JmsCmd(keystr_+CString("BinRef"));TbAfdrukPost[k].BinRef=String2Int(cstr_);
		cstr_=JmsCmd(keystr_+CString("BinName"));ZCstr2Arr(cstr_,TbAfdrukPost[k].BinName,30);
		cstr_=JmsCmd(keystr_+CString("MediaRef"));TbAfdrukPost[k].MediaRef=String2Int(cstr_);
		cstr_=JmsCmd(keystr_+CString("MediaName"));ZCstr2Arr(cstr_,TbAfdrukPost[k].MediaName,30);
		cstr_=JmsCmd(keystr_+CString("PaperRef"));TbAfdrukPost[k].PaperRef=String2Int(cstr_);
		cstr_=JmsCmd(keystr_+CString("PaperName"));ZCstr2Arr(cstr_,TbAfdrukPost[k].PaperName,30);
		cstr_=JmsCmd(keystr_+CString("JamosDriver"));TbAfdrukPost[k].JamosDriver=String2Int(cstr_);
		for(n=0;n<Q_JAMOSDRIVERS;n++) if(TbAfdrukPost[k].JamosDriver==JamosDrivers[n].Nr) break;
		if(n>=Q_JAMOSDRIVERS) n=0; copy0(JamosDrivers[n].Naam,TbAfdrukPost[k].JamosDriverName,30);
	};
	
	// papierformaten laden 
	zero((char *)TbPapier[0].Naam,sizeof TbPapier);  
	for(k=0;k<20;k++){
	  keystr_="GetIniKeyValue|Paper-"; 
	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(k+1),3,0); keystr_+=CString(buf_);
	  keystr_+="_Settings|";
	   
	  cstr_=JmsCmd(keystr_+CString("Name"));ZCstr2Arr(cstr_,TbPapier[k].Naam,30);
		cstr_=JmsCmd(keystr_+CString("LayoutData"));
		if(cstr_.GetLength()){
			for(j=0;j<7;j++) TbPapier[k].Formaat[j]=String2Int(Rec_Ele(cstr_,j,'|'));
			ZCstr2Arr(Rec_Ele(cstr_,7,'|'),buf_,2);TbPapier[k].Type=buf_[0];
		}
		for(n=0;n<Q_DEFAULT_FM;n++){
			for(j=0;j<7;j++) if(DefaultFm[n].Formaat[j]!=TbPapier[k].Formaat[j]) break;
			if(j<7) continue;
			if(DefaultFm[n].Type==TbPapier[k].Type) break;
		}
		if(n<Q_DEFAULT_FM) TbPapier[k].DefaultFm=n+1; 
		else{
			for(j=0;j<7;j++) if(TbPapier[k].Formaat[j]!=0) break;
			if(j==7){// lege format, default A4 laser invullen 
				copy((char *)&DefaultFm[0].Formaat[0],(char *)&TbPapier[k].Formaat[0], sizeof TbPapier[k].Formaat);
				TbPapier[k].Type=DefaultFm[0].Type;
				TbPapier[k].DefaultFm=1;
			}
			else TbPapier[k].DefaultFm=99;
		}
  }
  // documentparameters laden 
  zero((char *)TbDocument[0].Naam,sizeof TbDocument);  
  
	for(k=0;k<30;k++){// eerst sys.fas gedeelte invullen 
	  sysget(18000+k*16,16,buf_);
	  TbDocument[k].PapierNr=buf_[0];
	  TbDocument[k].OverlayNr=buf_[1];
	  for(j=0;j<8;j++){
		  if(buf_[2] &(1<<j)) TbDocument[k].Opties[j]='J'; else TbDocument[k].Opties[j]='N'; // deel 1
	 	  if(buf_[3] &(1<<j)) TbDocument[k].Opties[j+8]='J'; else TbDocument[k].Opties[j+8]='N'; // deel 2
	  }
	  copy(&buf_[4],TbDocument[k].MailTemplate,5);
		TbDocument[k].SpecialAfdrukPostNr=buf_[9];
  }
	for(k=0;k<30;k++){ // per echt document de JMS data inlezen 
	  keystr_="GetIniKeyValue|Document-"; 
	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(k+1),3,0); keystr_+=CString(buf_);
	  keystr_+="_Settings|";
	   
	  cstr_=JmsCmd(keystr_+CString("Name"));ZCstr2Arr(cstr_,TbDocument[k].Naam,30);
		cstr_=JmsCmd(keystr_+CString("Printer"));TbDocument[k].DefaultAfdrukPostNr=String2Int(cstr_);
  }
	// werkpost-info laden 
	p_tb_printers_=20;
	zero((char *)TbWerkPost[0].Naam,sizeof TbWerkPost);  
	for(k=0;k<MAX_WERKPOST;k++){
		keystr_="GetIniKeyValue|JamaSettings|SerialNr_Post-"; 
	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(k+1),3,0); keystr_+=CString(buf_);
		cstr_=JmsCmd(keystr_);ZCstr2Arr(cstr_,TbWerkPost[k].SerialNummer,20);
		if(cstr_.Find("JMM:")>=0){
			TbWerkPost[k].PostOpAfstand=true; 
			if(p_tb_printers_<30){
			  TbAfdrukPost[p_tb_printers_].JmsPrinterNummer=100+k+1;
	      cstr_="ComfortLink post ";
			  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(k+1),2,1); cstr_+=CString(buf_);
			  ZCstr2Arr(cstr_,TbAfdrukPost[p_tb_printers_].Naam,30);
			  p_tb_printers_++;
			}
		}
		else TbWerkPost[k].PostOpAfstand=false;
	
	  keystr_="GetIniKeyValue|Post-"; 
	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(k+1),3,0); keystr_+=CString(buf_);
	  keystr_+="_Settings|";
	   
	  cstr_=JmsCmd(keystr_+CString("Name"));ZCstr2Arr(cstr_,TbWerkPost[k].Naam,30);
		cstr_=JmsCmd(keystr_+CString("SendAllPrintToPost"));
		if(String2Int(cstr_)==1) TbWerkPost[k].PrintLocal='J'; else TbWerkPost[k].PrintLocal='N';
		cstr_=JmsCmd(keystr_+CString("HoldPrintJobsOnServer"));
		if(String2Int(cstr_)==1) TbWerkPost[k].HoldPrintJobsOnServer='J'; else TbWerkPost[k].HoldPrintJobsOnServer='N';
		cstr_=JmsCmd(keystr_+CString("DisplayJamadataBrief"));
		if(String2Int(cstr_)==1) TbWerkPost[k].DisplayJamadataBrief='J'; else TbWerkPost[k].DisplayJamadataBrief='N';
		cstr_=JmsCmd(keystr_+CString("DisplayEmailAsEML"));
		if(String2Int(cstr_)==1) TbWerkPost[k].DisplayEmailAsEML='J'; else TbWerkPost[k].DisplayEmailAsEML='N';
		cstr_=JmsCmd(keystr_+CString("AllowMasterFunctions"));
		if(String2Int(cstr_)==1) TbWerkPost[k].AllowMasterFunctions='J'; else TbWerkPost[k].AllowMasterFunctions='N';
		cstr_=JmsCmd(keystr_+CString("MemberOfFiliaal")); TbWerkPost[k].FiliaalNummer=String2Int(cstr_);
		for(j=1;j<=4;j++){
			cstr1_.Format("Scherm-%03d",j); 
	  	cstr_=JmsCmd(keystr_+cstr1_+CString("_BootDossier"));ZCstr2Arr(cstr_,TbWerkPost[k].ScreenBootDossier[j-1],4);
			cstr_=JmsCmd(keystr_+cstr1_+CString("_BootSequence"));ZCstr2Arr(cstr_,TbWerkPost[k].ScreenBootSequence[j-1],21);
			cstr_=JmsCmd(keystr_+cstr1_+CString("_BackGroundColor"));TbWerkPost[k].ScreenColorNummer[j-1]=String2Int(cstr_);
		}
	}
}

static void UpdateDataMastersSettings(void)
{
  int curs,z,g,k,key;
  char dsp_buf[1500],buf_[20],old_lev_naam[DIM_WHSDOSSIERS][50],lev_naam[DIM_WHSDOSSIERS][50],orig_dossier[5];
	CString cstr_,keystr_;

		// DataMasters 
	copy(s(25,3),orig_dossier,fldlen(25,3));
	for(k=0;k<DIM_WHSDOSSIERS;k++){
		keystr_="GetIniKeyValue|DataMastersSettings|WHS-"; 
	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(k+1),1,0); keystr_+=CString(buf_);
		WHS_Settings.WHSInternalCompanyNr[k]=JmsCmd(keystr_+CString("_InternalCompanyNr"));
		WHS_Settings.WHSDossierNr[k]=JmsCmd(keystr_+CString("_DossierNr"));
		WHS_Settings.WHSCompanyName[k]=JmsCmd(keystr_+CString("_CompanyName"));
		WHS_Settings.JamaDossierCode[k]=JmsCmd(keystr_+CString("_FasCode"));
		WHS_Settings.JamaSubDir[k]=JmsCmd(keystr_+CString("_JamaDataSubDir"));
		WHS_Settings.JamaFacturenDir[k]=JmsCmd(keystr_+CString("_FacturenSubDir"));
		WHS_Settings.JamaLeverancierRec[k]=atol(JmsCmd(keystr_+CString("_LeverancierNr")));
	}
	keystr_="GetIniKeyValue|DataMastersSettings|FWPPassword"; 
	WHS_Settings.FWPPassword=JmsCmd(keystr_);
	zeros(dsp_buf,sizeof dsp_buf);z=0;
	for(k=0;k<2;k++){
    cstr2arr(WHS_Settings.WHSInternalCompanyNr[k],&dsp_buf[z*50],30);z++;
    cstr2arr(WHS_Settings.WHSDossierNr[k],&dsp_buf[z*50],30);z++;
    cstr2arr(WHS_Settings.WHSCompanyName[k],&dsp_buf[z*50],30);z++;
    cstr2arr(WHS_Settings.JamaDossierCode[k],&dsp_buf[z*50],30);z++;
    cstr2arr(WHS_Settings.JamaSubDir[k],&dsp_buf[z*50],30);z++;
	  cstr2arr(WHS_Settings.JamaFacturenDir[k],&dsp_buf[z*50],30);z++;
		zero(lev_naam[k],sizeof lev_naam[0]);
		if(WHS_Settings.JamaLeverancierRec[k]){
			copy(&dsp_buf[(3+k*6)*50],s(25,3),fldlen(25,3));
			if(sysopen(s(25,3),"")==0){
				fileopen(1);
				fasinit(1);*u(1,1)=WHS_Settings.JamaLeverancierRec[k];fasgeti(1);
				copy(s(1,3),lev_naam[k],fldlen(1,3));
			}
		  copy(orig_dossier,s(25,3),fldlen(25,3));sysopen(s(25,3),"");
		}
		copy(lev_naam[k],old_lev_naam[k],sizeof lev_naam[0]);
	}

	cstr2arr(WHS_Settings.FWPPassword,&dsp_buf[1000],30);z++;
	curs=1;
  FOREVER {
		redo:; 
    scrnum=0;scrget(3,13);z=1;
		scraddpicto(1,0,1,22,4,2,595,0,0,"annuleer"); scraddpicto(2,0,7,22,4,2,578,0,0,"OK"); scraddpicto(7,0,13,22,4,2,107,0,4,"Herdisplay"); 
		for(k=0;k<2;k++){
			scrifld(z++,fm_us1_U,&dsp_buf[(k*6+0)*50]);
			scrifld(z++,fm_uWHSNr,&dsp_buf[(k*6+1)*50]);
			scrifld(z++,fm_us30,&dsp_buf[(k*6+2)*50]);
      scrifld(z++,fm_us3_U,&dsp_buf[(k*6+3)*50]);
      scrifld(z++,fm_us30,&dsp_buf[(k*6+4)*50]);
      scrifld(z++,fm_us30,&dsp_buf[(k*6+5)*50]);
			scrifld(z++,fm_us40,&lev_naam[k]);
		}
		scrifld(z++,fm_us30,&dsp_buf[1000]);
    key=scrupd(curs,0xA0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106 || key==5001) goto endsr;
		if(dsp_buf[0]=='\0'){ errnum=34; curs=1; goto redo;}
    for(k=0;k<6;k++) if(k!=4 && dsp_buf[k*50]=='\0') {curs=k+1; errnum=38; goto redo;}
		if(dsp_buf[0]==dsp_buf[6*50]){errnum=34; curs=8; goto redo;}
    if(dsp_buf[6*50]){
      for(k=6;k<12;k++) if(k!=10 && dsp_buf[k*50]=='\0') {curs=k+2; errnum=38; goto redo;}
		}
		for(k=0;k<2;k++){
			if(dsp_buf[(k*6)*50] && lev_naam[k][0] && cmpstr(lev_naam[k],old_lev_naam[k],sizeof lev_naam[0])){
				copy(&dsp_buf[(3+k*6)*50],s(25,3),fldlen(25,3));
				if(sysopen(s(25,3),"")){
					errnum=1; copy(orig_dossier,s(25,3),fldlen(25,3));sysopen(s(25,3),"");
					curs=4+k*7; goto redo;
				}
				fileopen(1);
				fasinit(1); copy(lev_naam[k],s(1,3),fldlen(1,3));
				g=search(1,0);
				copy(orig_dossier,s(25,3),fldlen(25,3));sysopen(s(25,3),"");
				if(g){curs=7+k*7; goto redo;}
				copy(s(1,3),lev_naam[k],fldlen(1,3));copy(lev_naam[k],old_lev_naam[k],sizeof lev_naam[0]);WHS_Settings.JamaLeverancierRec[k]=*u(1,1);
			}
			else if(lev_naam[k][0]=='\0'){
				zero(lev_naam[k],sizeof lev_naam[0]);zero(old_lev_naam[k],sizeof old_lev_naam[0]);WHS_Settings.JamaLeverancierRec[k]=0;
			}
		}
    if(key==108 || key==5002) break;
  }

  z=0;
	for(k=0;k<DIM_WHSDOSSIERS;k++){
		keystr_="SetIniKeyValue|DataMastersSettings|WHS-"; 
	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(k+1),1,0); keystr_+=CString(buf_);
		cstr_=CString("_InternalCompanyNr| ");cstr_+=CString(&dsp_buf[(z++)*50]); cstr_=JmsCmd(keystr_+cstr_);
		cstr_=CString("_DossierNr| ");cstr_+=CString(&dsp_buf[(z++)*50]); cstr_=JmsCmd(keystr_+cstr_);
		cstr_=CString("_CompanyName| ");cstr_+=CString(&dsp_buf[(z++)*50]); cstr_=JmsCmd(keystr_+cstr_);
		cstr_=CString("_FasCode| ");cstr_+=CString(&dsp_buf[(z++)*50]); cstr_=JmsCmd(keystr_+cstr_);
		cstr_=CString("_JamaDataSubDir| ");cstr_+=CString(&dsp_buf[(z++)*50]); cstr_=JmsCmd(keystr_+cstr_);
		cstr_=CString("_FacturenSubDir| ");cstr_+=CString(&dsp_buf[(z++)*50]); cstr_=JmsCmd(keystr_+cstr_);
		zero(buf_,sizeof buf_);sprintf(buf_,"%05d",WHS_Settings.JamaLeverancierRec[k]);cstr_=CString("_LeverancierNr| ");cstr_+=CString(buf_); cstr_=JmsCmd(keystr_+cstr_);
	}
	keystr_="SetIniKeyValue|DataMastersSettings|FWPPassword| "; cstr_=CString(&dsp_buf[1000]); cstr_=JmsCmd(keystr_+cstr_);

endsr:;
}

static void FillInPostCodes(void)
{
  int n,g,len_,flen_,pos;
  char *cpc_,str_[50];
	CString cstr_;
	CFile fil;
 
  if(fldlen(29,1)==0) goto endsr;
	if (!fil.Open(_T("PostCode.csv"),CFile::modeRead,0)) goto endsr;
	scrget(1,7);scrupd(-3,0);
	fileopen(15);
	fasinit(29); n=0; // eerst alle records deleten
  FOREVER{
    *u(29,1)=++n;
    g=fasgetu(29);
    if(g==47)break;
    if(g!=46) faskill(29);/* deleted record */
  }
	flen_ = (int)fil.GetLength();
	cpc_ = RamBon;
	fil.Read(cpc_,flen_);
 	fil.Close();
	for (int k=0; k<flen_; ) {
		fasinit(29);
		pos=k;while (cpc_[pos]!=';') pos++;
		len_=pos-k; if(len_>fldlen(29,2)) len_=fldlen(29,2); copy(&cpc_[k],s(29,2),len_);
		k=++pos;
		while (cpc_[pos]!=';' && cpc_[pos]!='\r') pos++;
		len_=pos-k; if(len_>fldlen(29,3)) len_=fldlen(29,3); 
		zero(str_,sizeof str_); copy(&cpc_[k],str_,len_); CnvJamaChar(str_,len_,1);
    for(n=0;n<len_;n++) if(str_[n]>=0x80 && str_[n]<0xA0) break;
		if(n<len_) memcpy(s(29,3),str_,len_); // indien speciale karakters dan niet in hoofdletters zetten
		else{
  		cstr_=CString(str_);cstr_.MakeUpper();memcpy(s(29,3),(char *)(LPCTSTR)cstr_,len_);
		}
		
		k=++pos;
		if(cpc_[pos]=='1') *s(29,4)=1;
		fasadd(29);
		while (cpc_[pos++]!='\n'){if(pos>=flen_) break;}
		k=pos++;
	}
endsr:;
}

/*

 voorbeelden JMS-commando's 

  int16 k;
  CString cstr, MergeCmd;

  cstr=JmsCmd("GetMailTemplates");

  cstr=JmsCmd("GetAllPrinters");

  cstr=JmsCmd("GetIniSections");
  cstr=JmsCmd("GetIniSectionData|Printersettings");
  cstr=JmsCmd("GetIniKeyValue|Printersettings|JamaPrinter1");
  cstr=JmsCmd("SetInikeyValue|Printersettings|JamaPrinter9|Samsung SCX-4x24 Series PCL 6");
  
  cstr=JmsCmd("GetTemplateMergeFields|FAK1");
  
  cstr=JmsCmd("CheckEmailAddress|marc vg@hotmail.com");
  cstr=JmsCmd("CheckEmailAddress|Wim.VanGestel@econ.kuleuven.be");

  MergeCmd = "MergeTemplateAndMail\r\n";
  MergeCmd+= "Template|FAK1\r\n";  
  MergeCmd+= "Action|ToCheck\r\n"; // UserEML, UserMSG, PreviewEML, PreviewMSG, ToSend, ToCheck 
  MergeCmd+= "To|marc@jamadata.be|Marc Van Gestel\r\n";
  MergeCmd+= "To|hilde@vangestel.be|Hilde Jutten\r\n";
  MergeCmd+= "CC|jan@jamadata.be|Jan Van Gestel\r\n";
  MergeCmd+= "BCC|marc_vg@hotmail.com\r\n";
  MergeCmd+= "AttachJamaFileRef|51\r\n";
  MergeCmd+= "AttachJamaFileRef|55\r\n";
  MergeCmd+= "Replace|KlantNaam|De Plezante Hoek\r\n";
  MergeCmd+= "Replace|SaldoVervallen|233,10\r\n";
  cstr=JmsCmd(MergeCmd);
									
  int i=RamBonSize;
  ovlexit(-1);
}
*/
static void scrxfld(int16 z,char *pfmt_,char *pvar_,char attr_)
{
  scrifld(z,pfmt_,pvar_); if(z<0) z=-z; scrchat(z,attr_);
}
  
static void DisplayMenuTitel(int ypos_,char* tekst_, char attrib_)
{
  int len_,beg_;
	char fmt_[40],dsptekst_[100];
   
	zero(dsptekst_,sizeof dsptekst_);dsptekst_[0]=' ';
  for(len_=0;len_<80;len_++){
		if(tekst_[len_]=='\0') break;
		dsptekst_[len_+1]=tekst_[len_];
	}
	len_+=1;dsptekst_[len_++]=' ';if(len_>80) len_=80;
  beg_=(80-len_)/2; if(beg_<1) beg_=1; 
	copy(fm_titel,fmt_,sizeof fm_titel);fmt_[2]=len_;
	scraddfield(200,beg_,ypos_,attrib_);scrifld(200,fmt_,dsptekst_);
}
 
static int ZCstr2Arr(CString cstr_, char *p_arr_, int max_len_)
{

  int k,len_;
  
  if(cstr_.GetLength()==0) return 0;
  
  len_=max_len_;
  if(len_==-1 || len_>cstr_.GetLength()) len_=cstr_.GetLength();
  for(k=0;k<len_;k++)  *(p_arr_+k)=cstr_.GetAt(k);
  if(len_>=max_len_) len_--; *(p_arr_+len_)='\0'; 

  return len_;
}

static CString Rec_Ele(CString s, int kol_, char delim_kar_)
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
  return fuval;
}
     
static CString CurrentTime2String(void)

{

  SYSTEMTIME st;
  char buf_[20];
  int pos_;
     
  zeros(buf_,sizeof buf_);pos_=0;
  GetLocalTime(&st);
  int2str((int)st.wDay,&buf_[pos_],-2);pos_+=2;buf_[pos_++]='/'; // datum
  int2str((int)st.wMonth,&buf_[pos_],-2);pos_+=2;buf_[pos_++]='/';
  int2str((int)st.wYear,&buf_[pos_],-4);pos_+=4;buf_[pos_++]='-'; // uur
  int2str((int)st.wHour,&buf_[pos_],-2);pos_+=2;buf_[pos_++]=':';  
  int2str((int)st.wMinute,&buf_[pos_],-2);
  return CString(buf_);
}
  

static void int2str(int d, char *s, int len) // len negatief geeft leadind zeros, anders spaces 
{
  int j;
  char buf[10], l_zero, leader;
 
  l_zero=NO;
  if (len<0) {len=-len; l_zero=YES;}
  if (d==0) {
    buf[0]='0';
    j=1;
  }
  else {
    j=stci_d(buf,d,sizeof(buf));
  }
  movmem(buf,s+len-j,j);
  if (l_zero) leader='0'; else leader=' ';
  for (j=len-j; j>0; j--) *(s+j-1)=leader;
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}



static CString Double2String(double getal,long mode)  // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
{ 
 
  CString fuval,S;

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
  fuval.Replace('.',',');
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

static int SpaceZeros(char* ps_,int max_len)
{
  int k;

  for(k=0;k<max_len;k++){
    if(*(ps_+k)=='\0') *(ps_+k)=' ';
    else if(*(ps_+k)=='&') *(ps_+k)='+';
  }
  return k;
}

static double round(double bd_,double bd_afr_)
{
  double wrk1_,wrk2_,wrk3_,add_,result_;
 
  result_=bd_;
  add_=0.500001;
  if(result_<0) add_=-add_;
  if(bd_afr_>0.00001){
    if(bd_afr_<=1.){
      wrk1_=(long int)result_;
      wrk2_=result_-wrk1_;
    } else{wrk1_=0.;wrk2_=result_;}
    wrk3_=wrk2_/bd_afr_;
    wrk2_=(double)((long)((wrk2_/bd_afr_)+add_)) * bd_afr_;
    result_=wrk1_+wrk2_;
  }
  return (double)(result_);
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
  }
}

static int16 search(int16 stu_,int16 mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)&parmcall[0],(char *)&parmbak[0],sizeof parmcall);
  zero((char *)&parmcall[0],sizeof parmcall);
  parmcall[0]=mod_;
#if 0
  if(stu_<=2) parmcall[1]=7; // bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3; // GEEN ADD
#endif
  if(stu_==6) parmcall[1]=0;
  parmcall[2]=0;
  parmcall[3]=0;
#ifdef STRAATKEY
  if(stu_==2) parmcall[4]=STRAATKEY;
#endif
  parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)&parmbak[0],(char *)&parmcall[0],sizeof parmcall);
  return fuval;
}