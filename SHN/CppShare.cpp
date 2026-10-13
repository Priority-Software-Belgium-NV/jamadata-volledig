#define _WIN32_WINNT 0x0501

#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include <fstream>

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;

#define YES             1
#define NO              0

extern int16 retcall,parmcall[8];
extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern float *f();
extern double *d(), valu_cnv();

// Kleuren attribuut (bg/txt) : 4/5: grijs/geel 6:grijs/wit 7:grijs/felrood 8:donkerblauw/wit, 9:groen/wit, A:paars/geel, B:rood/geel, 
//                     C:felblauw/wit D:felgroen/wit, E: roos/wit F donkergroen/wit

// FLAGFIS : ondanks light, toch >120000 records om kasverkopen >1 jaar te kunnen bijhouden

// Routines from Jaak
extern "C" void AddTextKey(int16 Fld,int16 Hz,int16 Vt,int16 Xlen,int16 Ylen,int16 KeyNr,char *KeyText,long KleurRGB);
extern "C" int CheckEmailAdres(char *email_, int len_,int internetcheck_); 
extern "C" int CheckForFreeSpace(int StuNr, long MinFree);
extern "C" int CheckForJamaDataUpdates(int SoortCheck); // 0=binnen kantooruren, 1=altijd
extern "C" int16 CheckPw(int16 type,int16 nr,int16 aard_);
extern "C" void CnvJamaChar(char *pString,int16 MaxLen,int16 CnvMode);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
extern "C" int CopyFas2Map(char *NaamFas,char *ToMap,int ShutDownSystem); // kopieren van fas(sen) naar andere map
extern "C" int CopyMoveFile(char *FromFile,char *ToFile,int DeleteOriginal); // kopieren van een file
extern "C" int CopySpoolNrToFile(int SpoolFileNr,char *ToFile); // kopieren van een spoolfile (pdf) naar file (ToFile=map+filenme vb ..\FactPDF\FAS-2022-00100.pdf)
extern "C" int DeleteAllPrintjobs(void); // alle jobs van deze werkpost
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" int DisplayVerzendStatus(int ViaStu,int Display); // alles moet in de STU 7 of 8 ingevuld zijn
extern "C" int ExecCopyDossier(char *FromCode,char *ToCode,char *ToNaam,int CopyMode,int ShutDownSystem); // CopyMode: 0= alles 1=boekhouding 2=alles excl. bon
extern "C" void ExecJmsCommand(char* buf, int buflen, char* pCommand);
extern "C" int Fld2String(int stunr, int fldnr, char *OutBuffer, int MaxLen);
extern "C" int FileExist(char *FileName);
extern "C" int FindTextInString(char *FText,int LenFtext,char *String,int LenString);
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
extern "C" void GetCurrentDateTime(int16 *jj, int16 *mm, int16 *dd, int16 *uur, int16 *min, int16 *sec);
extern "C" void GetFileFromServer(char *FileName);
extern "C" int GetPostName(char *Namestr_,uint16 pID_); // vul de naam van de post in de string, voorzie 15 karaketers voor string!
extern "C" int IbanTools(char *pIBAN,char *pBIC,char *pJamaRek,int16 ToolNr); // 0 = check iban/bic, 1=check+fill bic, 2=convert jamarek -> IBAN/BIC
extern "C" int JsonToXml(char *Outputbuf, int MaxOutputbufLen, char *JsonString);
extern "C" void MakeStructMed(char *pd, uint16 refnr_); // 'kkk/kkff/fffcc'   K(lant) F(aktnr) C(heck) 
extern "C" int CodaBoxShowLicence(char *Licence);
extern "C" int CodaBoxCheckVAT(long *BtwNrBE, char *BtwEU); // BtwEU wordt voorlopig niet gebruikt (22/10/20)
extern "C" int CodaBoxCheckGLN(char* glnNr); // Check of GLN Peppol kan ontvangen
extern "C" int CodaBoxCheckStatus(char *Licence, char *RefCodaBox, char *CNflag, int DisplayError);
extern "C" int16 Search(int stu_,int mod_);
extern "C" int GetFileFromSelection(char *ptitel_,char *pselection_); // result komt in SelectedFileName
extern "C" int SendMail(int send_mode);
extern "C" int ShowSavedDocument(int16 MastStuNr, long MastRecord, int16 SoortDocument, uint16 dat_beg, uint16 dat_end) ;
extern "C" int ShowGoogleMapsButton(int nr, int fld, int h, int v, int hlen, int vlen, int16 StuNr);
extern "C" void SvcErr(int nr, char *text);
extern "C" char *VarTextFmt(int len_,int update_);
extern "C" int WebrequestJson(char* Outputbuf, int MaxOutputbufLen, char *Url, char *Method, char *User, char *PW, char *HeaderKey, char *HeaderValue, char *Message, char *FileName, int ForceUnchangedInput, int ForceUnchangedOutput);
extern "C" int XmlToJson(char *Outputbuf, int MaxOutputbufLen, char *XmlString);

extern "C" const char* PeppolSendDocument(char btwNr[21], char cnFlag[4], char fileName[71]);
extern "C" const char* PeppolGetDocumentStatus(char documentId[51], char cnFlag[4], int DisplayError);
extern "C" const char* PeppolExportDocuments(bool markAsExported);
extern "C" const char* PeppolMarkDocumentAsExported(char documentId[51]);
extern "C" const char* PeppolLookup(char scheme[5], char lookupCode[21]);

extern "C" void AddTextKey(int16 Fld,int16 Hz,int16 Vt,int16 Xlen,int16 Ylen,int16 KeyNr,char *KeyText,long KleurRGB)
{ // Fld=fieldnr voor adden text, KeyNr : 10001 - 10099 (!)
  char fmKey[]  = {11,0x09,30,0,0,0,0,0,0,0,0};
  scraddfield(Fld,Hz,Vt,0);
  fmKey[2]=Xlen*Ylen; if(fmKey[2]>80) fmKey[2]=80;
  fmKey[4]=Xlen; fmKey[5]=Ylen;
  fmKey[6]=KeyNr%256; fmKey[7]=KeyNr/256;
  fmKey[8]=KleurRGB%256; fmKey[9]=(KleurRGB/256)%256; fmKey[10]=(KleurRGB/65536)%256;
  scrifld(Fld,fmKey,KeyText);
}

extern "C" int16 CheckPw(int16 PwType,int16 PwItemNr,int16 AskMode)// PwType: 0=bkh-pw,1=voo-pw, AskMode:0=normaal,1=altijd vragen
{																																		// PwItemNr : item 0-39 , 101-103 : direct paswoordniveau 1-3 
  int16 k,key,level,pw_offset_;
  uint16 plev_,pasw=0,niv_MPW=0, passwrds[6];
	char buf4[4],buf8[8],niveaus[2][10],SavePw='N',buf[100];

	char fm_us8PW[] = {7,0xC8,8,0,5,0,0};
  char fm_us8MP[] = {9,0xC8,8,0,5,0,'A','Z',0};
	static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
	sysget(1876,6,&passwrds[0]);
	sysget(3878,4,&passwrds[3]);
  sysget(1880,2,&passwrds[5]);
  sysget(1882,10,&niveaus[0][0]);
  
  sysget(3882,10,&niveaus[1][0]);


	if(fldlen(25,10) && PwItemNr==39) *u(25,10)=0; // bij opvragen masterpaswoord, altijd vorig wegvegen
	pw_offset_=0;if(PwType==1) pw_offset_=3; // 0-2 : BKH, 3-5 VOO
	if(PwItemNr>=0 && PwItemNr<=39){
    level=(int16)((niveaus[PwType][PwItemNr/4]>>(2*(PwItemNr%4))) &0x3);  
	}
	else if(PwItemNr>=101 && PwItemNr<=103){// echte level doorgegeven
    level=PwItemNr-100;
	}
	else level=0;
  if(level==0 || passwrds[2]==0) return YES; // geen paswoord nodig

  level--;
  if(fldlen(25,10) && *u(25,10) && AskMode==0){ 
    for(k=level+pw_offset_;k<3+pw_offset_;k++){ 
      if(passwrds[k]==*u(25,10)) return YES;
    }
  }
  zero(buf8,sizeof buf8);if(fldlen(25,10)) *u(25,10)=0;
	SavePw='N'; if(fldlen(25,10) && PwItemNr==39) SavePw='J';
  if(scrget(1,39)){
    scrifld(1,fm_us8PW,&buf8[0]);
		scrifld(2,fm_uJN,&SavePw);
  }
  key=scrupd(1,0x489);
	if(key==111 || key==101)goto endsr;
	if(key==104){
    sysget(1812,2,&niv_MPW); if(niv_MPW>1700) niv_MPW=0; // max 5 codes
    plev_=((niv_MPW+0x4A93)^0x139A);
    for(k=0;k<4;k++){buf4[k]=(plev_&0x0F)+'G'; plev_=plev_/16;}
		zero(buf8,sizeof buf8);
		scrget(1,176);
		scrifld(1,VarTextFmt(4,0),buf4);
		scrifld(2,fm_us8MP,buf8);
		key=scrupd(1,0x681);
		if(key==101 || key==111) goto endsr;
		if(key==110 && buf8[0]=='G' &&  buf8[1]=='E' && buf8[2]=='E' && buf8[3]=='L'){
      sprintf(buf,"Paswoord overruled : Proces : %d, Dossier : %s",procid,s(25,3));
      SvcErr(1,buf);
			return YES;
		}
    plev_=0;
    for(k=5;k>1;k--){ plev_=plev_*16+(buf8[k]-'B'); }
    plev_=plev_^0x72A4;
		if(niv_MPW!=plev_) goto endsr;
		niv_MPW+=0x15D;sysput(1812,2,&niv_MPW);
		return YES;
	}
	if(SavePw!='J' && fldlen(25,10)) *u(25,10)=0;
  if(buf8[0]=='\0') pasw=0;
  else{
		pasw=0;
		for(k=0;k<8;k++){
			if(buf8[k]=='\0' || buf8[k]=='~' || buf8[k]=='#') break;
			pasw=pasw*7+buf8[k] +1;
		}
		if(pasw==0) pasw++;
  }
	if(PwItemNr==39) pw_offset_=0; // master paswoord in bkh EN voo zoeken
  for(k=level+pw_offset_;k<3+pw_offset_;k++){
    if(passwrds[k]==pasw || (PwItemNr==39 && passwrds[k+3]==pasw)){
			if(SavePw=='J') *u(25,10)=pasw;
			return YES;
		}
  }
	endsr:;
  errnum=50; return NO;
}

extern "C" int CheckForFreeSpace(int StuNr, long MinFree)
{
	long max_aantal_, lines_used_,lines_tekort_;
	char buf1000_[1000];
	char fm_ol8[]   = {6,0x93,8,0,0x60,0};
	char fm_os20[]  = {7,0x88,20,0,0,0,0};

	if(fldlen(StuNr,1)==0) return 0; // uit veiligheid
	
	if((ServerVersion==SERVER_MONO && StdInMono==0) || fldlen(StuNr,1)<4) max_aantal_=60000;
#if !FLAGFIS // ondanks light toch onbeperkte grootte om kasverkopen >1 jaar te kunnen bijhouden
	else if(ServerVersion==SERVER_LIGHT || StdInMono){if(StuNr==16) max_aantal_=130000; else max_aantal_=120000;}
#endif
	else max_aantal_=10000000;// oneindig
	memcpy(buf1000_,s(StuNr,1),fldlen(StuNr,0));

  fasinfo(StuNr,6);
  if(fldlen(StuNr,1)==4) lines_used_=*l(StuNr,1); else lines_used_=*u(StuNr,1);
	errnum=0;
	max_aantal_-=lines_used_;	lines_tekort_=MinFree - max_aantal_;
	if(lines_tekort_>0){
		scrget(1,168);scraddpicto(1,0,32,1,12,6,61,0,3,"Opgelet!"); 
    fasinit(StuNr);fasinfo(StuNr,7);scrifld(1,fm_os20,s(StuNr,1));
		scrifld(2,fm_ol8,&MinFree);
		scrifld(3,fm_ol8,&max_aantal_);
		scrifld(4,fm_ol8,&lines_tekort_);
		scrupd(-1,0x1);
		errnum=64;
	}
	memcpy(s(StuNr,1),buf1000_,fldlen(StuNr,0));
	return errnum;
}

extern "C" int DeleteAllPrintjobs(void) // alle jobs van deze werkpost
{
  CString fname_,ft_search_;
	SYSTEMTIME st_,fsystime_;
	WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile

	if(DisplayWarning("Wenst u echt alle afdruktaken te wissen van deze werkpost?",61,1)==NO) return NO;
    scrget(1,7);scrupd(-3,0);
		ft_search_.Format("%sPOST-%03d\\*.*","..\\Spool\\ToClient\\",1+(procid/5));
		hSearch = FindFirstFile (ft_search_, &FileData);
		FOREVER{
			if (hSearch == INVALID_HANDLE_VALUE) break;
			if ((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) goto nextfile;                      // geen directory 
	    fname_.Format("%sPOST-%03d\\%s","..\\Spool\\ToClient\\",1+(procid/5),FileData.cFileName);
			remove(fname_);
			nextfile:;
			if(FindNextFile (hSearch, &FileData)==false) break;
	  }
		FindClose(hSearch);

	return YES;
}

extern "C" int CheckForJamaDataUpdates(int SoortCheck) // 0=binnen kantooruren, 1=altijd
{
	bool JMSFlag=false,JMCFlag=false;
	   
  if ((SoortCheck==0 && ThisScreenNr!=1) || AllowMasterFunctions==NO) return NO;

  bool BuitenKantooruren=true;
	 
	if(SoortCheck==1) BuitenKantooruren=false; // geforceerd
  struct tm *t;
  time_t tt;
  tt = time(NULL);
  t = localtime(&tt);
  if (t->tm_wday>=1 && t->tm_wday<=5 && t->tm_hour>= 9 && (t->tm_hour<11 || (t->tm_hour==11 && t->tm_min<45))) BuitenKantooruren=false;
  if (t->tm_wday>=1 && t->tm_wday<=4 && t->tm_hour>=13 && (t->tm_hour<17 || (t->tm_hour==17 && t->tm_min<15))) BuitenKantooruren=false;
  if (t->tm_wday==5                  && t->tm_hour>=13 && (t->tm_hour<15 || (t->tm_hour==15 && t->tm_min<15))) BuitenKantooruren=false;
  if (!BuitenKantooruren) {
    CString strTime;
    strTime.Format("%4d%02d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour);
		CString n_update_=CString(NextUpdateCheck);
    if (n_update_.GetLength()!=10 || n_update_<=strTime || SoortCheck==1) { // we mogen nu testen
      int hournext=t->tm_hour;
      if (t->tm_hour<13) hournext=13;
      else hournext=24;
      strTime.Format("%4d%02d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,hournext);
			copy((char *)(LPCTSTR)strTime,NextUpdateCheck,10);
      if (GetFileAttributes("JMSUpdate.flg")!=INVALID_FILE_ATTRIBUTES) JMSFlag=true;
      if (GetFileAttributes("..\\Prog\\JamaMsg.JAM")!=INVALID_FILE_ATTRIBUTES) JMCFlag=true;
			if(JMCFlag==false) NextUpdateCheck[0]='\0';// blijven checken als er niets was
	  }
  }
	if(JMSFlag || JMCFlag){
		scrchat(-1,8);
		if(JMCFlag){
			if(ovlcall(95,1)){
				if(ovlcall(2,2)==0){
  				DisplayWarning("Kan systeem niet stoppen, probeer later opnieuw!",605,0); return false;
				}
  			CFile fil;
				fil.Remove("..\\Prog\\JamaMsg.JAM");
				JmsCmd("DownloadUpdate"); 
				return YES;
			}
		}
		if(JMSFlag){
		
			scrnum=0;scrget(1,261);
			scrifld(1,VarTextFmt(60,0),"Er is een nieuwe versie beschikbaar van de SERVER-software.");
			int key=scrupd(-1,0x201);
			if(key==110){
				if(ovlcall(2,2)==0){
  				DisplayWarning("Kan systeem niet stoppen, probeer later opnieuw!",605,0); return false;
				}
  			CFile fil;
				fil.Remove("JMSUpdate.flg");
				fil.Open("JMR.CMD",CFile::modeCreate|CFile::modeWrite,0);
				fil.Write("JMSUPDATE",9); // om de JMR te vragen de JMS te updaten ...
				fil.Close();
	   		return YES;
			}
		}
		scrchat(-1,DefaultBackGroundColor);
	}
	else{ // Bij geforceerde check, toch melding geven als er niks is 
		if(SoortCheck==1) DisplayWarning("Er zijn momenteel geen nieuwe updates, probeer later opnieuw!",0,0);
	}
	return NO;
}

extern "C" void CnvJamaChar(char *pString, int16 MaxLen,int16 CnvMode)// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
{
  int16 j,k;
	static char Fas2Sif[32]  = {0xE1, 0xE0, 0xE2, 0xE4, 0xE7, 0xE9, 0xE8, 0xEA, 0xEB, 0xED, 0xEC, 0xEE, 0xEF, 0xF3, 0xF2, 0xF4,
															0xF6, 0xFA, 0xF9, 0xFB, 0xFC, 0xDC, 0xB0, 0xA7, 0, 0, 0, 0, 0, 0, 0, 0x80};

  for(k=0;k<MaxLen;k++){
		if(*pString==0) break;
		if(CnvMode){
			if(*pString==0xA3) *pString=' ';
			if(*pString==0xC3) *pString='A';
			if(*pString==0xC2) *pString='A';
			if(*pString==0xA2) *pString='A';
			if(*pString==0xE3) *pString='a';
			if(*pString==0xD1) *pString='N';
			if(*pString==0xC9) *pString='E';
			if(*pString==0xCB) *pString='E';
			if(*pString==0xC4) *pString='A';
			if(*pString==0xD4) *pString='O';
//			if(*pString==0xE2) *pString=0x80;
			for(j=0;j<32;j++) 
				if(*pString==Fas2Sif[j]){*pString=0x80+j;break;}
		}
		else{
      if(*pString>=0x80 && *pString<0x80+32) if(Fas2Sif[*pString-0x80]) *pString=Fas2Sif[*pString-0x80]; else *pString=' ';
		}
		pString++;
  }
}

extern "C" void GetCurrentDateTime(int16 *jj, int16 *mm, int16 *dd, int16 *uur, int16 *min, int16 *sec) 
{
  struct tm *t;
  time_t tt;
  tt = time(NULL);
  t = localtime(&tt);
	*jj=t->tm_year+1900;*mm=t->tm_mon+1;*dd=t->tm_mday;
	*uur=t->tm_hour;*min=t->tm_min;*sec=t->tm_sec;
}

extern "C" int IbanTools(char *pIBAN,char *pBIC,char *pJamaRek,int16 ToolNr) // 0 = check iban/bic, 1=check+fill bic, 2=convert jamarek -> IBAN/BIC
{																										// return 0 : OK, 1=foute IBAN, 2= foute BIC			
	int16 j,k,bnr_,netlen_,CntSepaLand;
	char str_[50],JamaRek[50],IBANrekening[50],netto_iban[50],jamaBErek[5],wrk_iban[100];
	long lbd_,rest_;
  CFile cfile_;

// Vernieuwen van de file BicCodes.JAM (BIC0099.cpp : staat op s:\VS) : 
//  - ga naar volgendes site : http://www.nbb.be/pub/09_00_00_00_00/09_06_00_00_00/09_06_02_00_00.htm?l=nl  (Nationale bank, in google "bic codes" ingetikt en dan NBB)
//  - download de file : Full List of Current Codes (xlsx - Office2007) 
//     --> hierin staa de BIC-codes voor de 1000 mogelijkheden (000 -> 999) in kolom B
//  - save deze file in \prog als : BicCodesXls.txt   (TAB-delimited)
//  - als output krijgt ge een file BicCodes.JAM die ge overal kopieert waar nodig : 


	static char *SepaLand[43]={"BE","BG","CY","DK","DE","EE","FI","FR","GR","GB","HU","IE","IS","IT","LV","LI","LT","LU",
														 "MT","MC","NL","NO","AT","PL","PT","SK","RO","SI","ES","CZ","SE","CH","AD","BA","FO","GL",
														 "HR","MK","MU","SM","RS","TN","TR"};
  CntSepaLand=43;
	 
	errnum=0;
	if(cmpstr(BicCodes,"BPOT",4)){// checken of lijst Belgische BIC-codes geladen is
		memset(BicCodes,0,8000);
		if(cfile_.Open("BicCodes.JAM",CFile::modeRead,0)){
		  cfile_.Seek(0L,CFile::begin);
		  cfile_.Read(BicCodes,8000);
			cfile_.Close();
		} else {errnum=1; return 1;}
	} 
	zero(jamaBErek,sizeof jamaBErek); if(ToolNr==2) copy(pJamaRek,jamaBErek,5);
redo_tools:;
	zero(IBANrekening,sizeof IBANrekening);
	if(ToolNr==2){// Jamarekening invullen 
		for(k=0;k<5;k++) if(jamaBErek[k]!='\0') break; 
		if(k>=5){
			if(*pIBAN!='\0') {ToolNr=1; goto redo_tools;}// indien niet ingevuld, dan IBAN controleren
			else return 0;
		}
		zero(JamaRek,sizeof JamaRek);
		rek_deco(str_,(unsigned char *)jamaBErek,1);
		netlen_=0;
		for(k=0;k<20;k++){
			if(str_[k]=='\0') break;
			if(str_[k]>='0' && str_[k]<='9') wrk_iban[netlen_++]=str_[k];
		}
		if(netlen_!=12) {*pIBAN=0;*pBIC=0;return 1;} // ongeldige rekening
		copy("111400",&wrk_iban[netlen_],6);netlen_+=6;
		rest_=0;
		for(k=0;(k*6)<netlen_;k++){
			zero(str_,sizeof str_);stcli_d(str_,rest_,2,0);copy(&wrk_iban[k*6],&str_[2],6);lbd_=val(str_); rest_=lbd_%97;
		}
		rest_=98-rest_;
		copy("BE",IBANrekening,2);stcli_d(&IBANrekening[2],rest_,2,0);copy(wrk_iban,&IBANrekening[4],12);
		for(k=0;k<4;k++){copy(&IBANrekening[k*4],&pIBAN[k*5],4);if(k==3) pIBAN[k*5+4]=0; else pIBAN[k*5+4]=' ';}
		zero(str_,sizeof str_);copy(&IBANrekening[4],str_,3);k=val(str_);
		if(k>=0 && k<1000) {copy(&BicCodes[k*8],pBIC,8);pBIC[8]=0;}
		return 0;
	}
	else {
		netlen_=0;zero(netto_iban,sizeof netto_iban);
		for(k=0;k<34;k++){
			if(pIBAN[k]=='\0') break;
			if((pIBAN[k]>='0' && pIBAN[k]<='9') || (pIBAN[k]>='A' && pIBAN[k]<='Z')) netto_iban[netlen_++]=pIBAN[k];
		}
		if(netlen_==0){
			if(ToolNr==1){*pIBAN=0;*pBIC=0;}
			return 0;
		}
		if(cmpstr(netto_iban,"DOM",3)==0){ // indien men DOM invult, dan is dit domicliering (om automatische betalingen te blokkeren)
			if(ToolNr==1){
				copy("DOMICILIERING",pIBAN,14);*pBIC=0;
			}
			return 0;
		}
		if(ToolNr==1 && netlen_==12 && netto_iban[0]>='0' && netto_iban[0]<='9'){// BE rekening ingevuld in IBAN veld --> converteren
			if(rek_comp(netto_iban,(unsigned char *)jamaBErek)==0) {*pIBAN=0;ToolNr=2;goto redo_tools; }
			else{errnum=26;return 1;}
		}
    for(k=0;k<CntSepaLand;k++) if(cmpstr(netto_iban,SepaLand[k],2)==0) break;
		if(k>=CntSepaLand) {errnum=26;return 1;}
		j=0;zero(wrk_iban,sizeof wrk_iban);
		for(k=4;k<netlen_;k++){
			if(netto_iban[k]>='A' && netto_iban[k]<='Z') {stcli_d(&wrk_iban[j],(long)(10+netto_iban[k]-'A'),2,0);j+=2;}
			else wrk_iban[j++]=netto_iban[k];
		}
		stcli_d(&wrk_iban[j],(long)(10+netto_iban[0]-'A'),2,0);j+=2;
		stcli_d(&wrk_iban[j],(long)(10+netto_iban[1]-'A'),2,0);j+=2;
		copy("00",&wrk_iban[j],2);j+=2;

		rest_=0;
		for(k=0;(k*6)<j;k++){
			zero(str_,sizeof str_);stcli_d(str_,rest_,2,0);copy(&wrk_iban[k*6],&str_[2],6);lbd_=val(str_); rest_=lbd_%97;
		}
		rest_=98-rest_;
		copy(netto_iban,IBANrekening,2);stcli_d(&IBANrekening[2],rest_,2,0);copy(&netto_iban[4],&IBANrekening[4],netlen_-4);
		if(cmpstr(netto_iban,IBANrekening,4)){errnum=26;return 1;}
		if(cmpstr(IBANrekening,"BE",2)==0){
			zero(str_,sizeof str_);copy(&IBANrekening[4],str_,3);bnr_=val(str_);
			if(bnr_<0 || bnr_>999) bnr_=0;
			if(ToolNr==0){
				zero(str_,sizeof str_); k=0; 
				for(j=0;j<10;j++) if((pBIC[j]>='0' && pBIC[j]<='9') || (pBIC[j]>='A' && pBIC[j]<='Z')) str_[k++]=pBIC[j];
  		  if(cmpstr(&BicCodes[bnr_*8],str_,8)){errnum=26;return 2;}
			}
			else if(ToolNr==1){ // IBAN en BIC geformatteerd wegschrijven 
  		  copy(&BicCodes[bnr_*8],pBIC,8);pBIC[8]=0;
	  	  for(k=0;k<4;k++){copy(&IBANrekening[k*4],&pIBAN[k*5],4);if(k==3) pIBAN[k*5+4]=0; else pIBAN[k*5+4]=' ';}
			}
		}
		else{ // bij buitenlander moet bic 8 of 11 tekens zijn 
			zero(str_,sizeof str_); k=0; 
			for(j=0;j<11;j++){
				if((pBIC[j]>='0' && pBIC[j]<='9') || (pBIC[j]>='A' && pBIC[j]<='Z')) str_[k++]=pBIC[j];
				else if(pBIC[j]=='\0') break;
			}
  		if(k!=8 && k!=11){errnum=26;return 2;}
		}
	}
  return 0;
}



extern "C" int DisplayWarning(char *ptxt, int icoon,int mode) // mode : 0=OK, 1=JA/NEE, 2=enkel display van text, 3=JA/NEE/TERUG icoon : 605=!, 61=stop

{
  int16 key,color_,k,qkar_;
  int len_,beg_;
	char dsptekst_[100];
   

	for(qkar_=0;qkar_<640;qkar_++) if(ptxt[qkar_]=='\0') break;

  zero(dsptekst_,sizeof dsptekst_);dsptekst_[0]=' ';
	for(len_=0;len_<80;len_++){
		if(ptxt[len_]=='\0') break;
		dsptekst_[len_+1]=ptxt[len_];
	}
	len_+=1;dsptekst_[len_++]=' ';if(len_>80) len_=80;
	beg_=(80-len_)/2; if(beg_<1) beg_=1; 
	
	color_=0; if(icoon<500) color_=3;
  scrnum=0;scrget(1,170);
	if(mode==0){
	  scraddf(100,23,0,8); scrifld(100,VarTextFmt(7,0)," F4 OK ");
	}
	else if(mode==1) {
	  scraddf(100,23,0,8); scrifld(100,VarTextFmt(7,0)," F4 Ja ");
	  scraddf(101,23,8,8); scrifld(101,VarTextFmt(8,0)," F5 Nee ");
	}
	else if(mode==4) {
		scraddf(100,23,0,8); scrifld(100,VarTextFmt(10,0)," F1 Terug ");
	  scraddf(101,23,11,8); scrifld(101,VarTextFmt(7,0)," F4 Ja ");
	  scraddf(102,23,19,8); scrifld(102,VarTextFmt(8,0)," F5 Nee ");
	}
	if(icoon) scraddpicto(1,0,32,1,12,6,icoon,0,color_,"Opgelet!"); 
	if(qkar_<80){
    scraddfield(200,beg_,12,0x2);scrifld(200,VarTextFmt(len_,0),dsptekst_);
	}
	else {
		for(k=0;k<8;k++){
			if(k*80>=qkar_) break;
			scraddfield(200+k,0,12+k,0x2);scrifld(200+k,VarTextFmt(80,0),ptxt+k*80);
		}
	}
redo_upd:;
	if(mode==2) scrupd(-3,0);
  else{
		key=scrupd(-1,0x19);
		if(mode==4 && key==101) return -1;
    if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
    else if(key==105) return NO;
	  else goto redo_upd;
	}
	return YES;
}

extern "C" int ExecCopyDossier(char *FromCode,char *ToCode,char *ToNaam,int CopyMode,int ShutDownSystem) // CopyMode: 0= alles 1=boekhouding 2=alles excl. bon
{

  int j,k,n;
  char str_[20],sys_data[19000];
  int bkh_file_,bon_file_;
	CFileFind finder;
	CFile cfile_;
	BOOL bWorking;
  CString frfile_,tofile_,cfcode_;
	CString FasSubDir="..\\FAS\\";

	if(ShutDownSystem){
  	if(ovlcall(2,2)==0){
  		DisplayWarning("Kan systeem niet stoppen, probeer later opnieuw!",605,0); return NO;
	  }
	}
	scrnum=0;scrget(1,170);
	scrifld(10,VarTextFmt(75,0),"Bezig met kopieren van dossier. Even geduld ...."); scrupd(-3,0);
  cfcode_=CString(FromCode);zeros(str_,sizeof str_);
	bWorking = finder.FindFile(FasSubDir+CString("*.") + CString(FromCode));
	while (bWorking) {
		bWorking = finder.FindNextFile();
	  if (finder.IsDirectory()) continue;
		frfile_=finder.GetFileName();
		bkh_file_=NO;bon_file_=NO;
		if(CopyMode==1 || CopyMode==2){
			k=frfile_.Find('.');
			if(k>=3){
				if(frfile_.Mid(k-3,3).CompareNoCase("SYS")==0) bkh_file_=YES;
				if(frfile_.Mid(k-3,3).CompareNoCase("GRB")==0) bkh_file_=YES;
				if(frfile_.Mid(k-3,3).CompareNoCase("STK")==0) bkh_file_=YES;
				if(frfile_.Mid(k-3,3).CompareNoCase("SAL")==0) bkh_file_=YES;
				if(frfile_.Mid(k-3,3).CompareNoCase("BKA")==0) bkh_file_=YES;
				if(frfile_.Mid(k-3,3).CompareNoCase("BON")==0) bon_file_=YES;
			}
		}
		if(CopyMode==0 || (CopyMode==2 && !bon_file_) || bkh_file_){ 
			k=frfile_.Find('.');tofile_=frfile_.Left(k+1)+CString(ToCode);
			if(CopyFile(FasSubDir+frfile_,FasSubDir+tofile_,false)==0){
				DisplayWarning("Fout bij kopieren bestand. Controleer de kopie!!!",605,0);
			}
		}
  }
	finder.Close();
  
  frfile_=CString("SYS."); frfile_+=CString(ToCode); 
  if (GetFileAttributes(FasSubDir+frfile_)!=INVALID_FILE_ATTRIBUTES) {
	  cfile_.Open(FasSubDir+frfile_,CFile::modeReadWrite,0);
		cfile_.Seek(0L,CFile::begin);
		cfile_.Read(sys_data,19000);

    for(k=0;k<30;k++){
			if(ToNaam[k]=='\0') {sys_data[34+k]='\0'; break;}
			else sys_data[34+k]=ToNaam[k];
		}
    for(k=0;k<15;k++){
      if(sys_data[300+k*17]!='\0'){
				bcopy(&sys_data[300+k*17],str_,15);
        for(j=0;j<12;j++) if(str_[j]=='.') break;
        if(j<12){
					j++;
					if(cfcode_.CompareNoCase(&str_[j])!=0){ // gemeenschappelijke files ook kopieren 
						frfile_=CString(str_);
						n=frfile_.Find('.'); bkh_file_=NO;
						if(n>=3){
							if(frfile_.Mid(n-3,3).CompareNoCase("SYS")==0) bkh_file_=YES;
							if(frfile_.Mid(n-3,3).CompareNoCase("GRB")==0) bkh_file_=YES;
							if(frfile_.Mid(n-3,3).CompareNoCase("STK")==0) bkh_file_=YES;
							if(frfile_.Mid(n-3,3).CompareNoCase("SAL")==0) bkh_file_=YES;
							if(frfile_.Mid(n-3,3).CompareNoCase("BKA")==0) bkh_file_=YES;
				      if(frfile_.Mid(k-3,3).CompareNoCase("BON")==0) bon_file_=YES;
						}
						if(CopyMode==0 || (CopyMode==2 && !bon_file_) || bkh_file_){ 
							n=frfile_.Find('.');tofile_=frfile_.Left(n+1)+CString(ToCode);
							if(CopyFile(FasSubDir+frfile_,FasSubDir+tofile_,false)==0){
									DisplayWarning("Fout bij kopieren bestand. Controleer de kopie!!!",605,0);
							}
						}
					}
					bcopy(ToCode,&sys_data[300+k*17+j],3);
				}
			}
		}
		copy((char *)u(25,2),&sys_data[1766],2); // datum vandaag
		sys_data[18480]=7; // rode achtergrond
		cfile_.Seek(0L,CFile::begin);
    cfile_.Write(sys_data,19000);
    cfile_.Close();
  }
	if(ShutDownSystem) ovlcall(2,3); // DB heropstarten en posten vrijmaken 
  return YES;
}

extern "C" int CopyFas2Map(char *NaamFas,char *ToMap,int ShutDownSystem) // kopieren van fas(sen) naar andere map // art.fas kopieren naar ..\Div om te kunnen doorsturen naar kassa
{
  CString frfile_,tofile_;
	CString FasSubDir="..\\FAS\\";

	frfile_=FasSubDir+CString(NaamFas);
	tofile_=CString(ToMap); tofile_+=CString(NaamFas);

 	if(ShutDownSystem){
  	if(ovlcall(2,2)==0){
  		DisplayWarning("Kan systeem niet stoppen, probeer later opnieuw!",605,0); return NO;
	  }
	}
	scrnum=0;scrget(1,170);
	scrifld(10,VarTextFmt(75,0),"Bezig met kopieren van artikelbestand. Even geduld ...."); scrupd(-3,0);
	if(CopyFile(frfile_,tofile_,0)==0){
		DisplayWarning("Fout bij kopieren bestand. Controleer de kopie!!!",605,0);
	}

	if(ShutDownSystem) ovlcall(2,3); // DB heropstarten en posten vrijmaken 
  return YES;
}

extern "C" int CopyMoveFile(char *FromFile,char *ToFile,int DeleteOriginal) // kopieren van een file
{
	CString frfile_,tofile_;

	frfile_=CString(FromFile); tofile_=CString(ToFile);
	if(CopyFile(frfile_,tofile_,0)==0){
		DisplayWarning("Fout bij kopieren bestand. Controleer de kopie!!!",605,0); return 0;
	}
	else if(DeleteOriginal) remove(FromFile);
	return 1;
}

extern "C" int CopySpoolNrToFile(int SpoolFileNr,char *ToFile) // kopieren van een spoolfile (pdf) naar file (ToFile=volledig pad+naam)
{

  CString JamaFileName;
  JamaFileName.Format("..\\spool\\files\\%08X*.*",SpoolFileNr);
  bool filecopied_=false;
  for (int Retry=0; Retry<120; Retry++) {
    CFileFind AttFinder;
    BOOL bWorking = AttFinder.FindFile(JamaFileName);
	  while (bWorking) {
		  bWorking = AttFinder.FindNextFile();
		  CString FriendlyName = AttFinder.GetFilePath();
			CopyMoveFile((char *)(LPCTSTR)FriendlyName,ToFile,0);
			filecopied_=true;
			break;
    }
    AttFinder.Close();
    if (filecopied_) return YES;
    TRACE("Wait 500 msec for attachement ...\n");
    Sleep(500);  // wacht halve seconde
  }
	return NO;
}

extern "C" int FindTextInString(char *Ftext,int LenFtext,char *String,int LenString)
{
  int l1,l2,len;
	char *p1,*p2;

  if(LenString==0) return YES;
	p1=Ftext;for(l1=0;l1<LenFtext;l1++) if(*(p1++)=='\0') break;
	p2=String;for(l2=0;l2<LenString;l2++) if(*(p2++)=='\0') break;
	if(l1==0) return YES;
  if(l1>l2) return NO;
	FOREVER{
		p1=Ftext;p2=String;len=l1;
		while(len--){
     if(*p1++!=*p2++) goto next;
    }
    return YES;
		next:;
		l2--; if(l1>l2) break;
		String++;
	}
  return NO;
}
  
extern "C" int GetFileFromSelection(char *ptitel_,char *pselection_) // result komt in SelectedFileName
{
  int z,key,len_,k,q_files,nr_,start_,lijnpos,q_,retval_,ScreenLines=17;
	unsigned short funckeys;
	char str_[30],attrib_,choice='\0';
	CString cstr_,puntstr_,reply_,fname_;
  WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
	CString cfilenames[100],cfiledates[100];
  SYSTEMTIME stUTC, stLocal;
  DWORD dwRet;
	char fm_ou3[]   = {6,0x90,3,0,0x60,0};
  char fm_uu3[]   = {6,0xD0,3,0,0x60,0};

	redo_find:;
	for(k=0;k<100;k++) cfilenames[k]="";q_files=0;zero(SelectedFileName,100);
	hSearch = FindFirstFile (pselection_, &FileData);
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
	if(q_files==0){errnum=1; return 0;}
  retval_=0;

  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
    scrget(1,277);z=1;q_=0; funckeys=0x80E1;
    for(len_=0;len_<79;len_++) if(ptitel_[len_]=='\0') break;
	  scraddfield(200,(80-len_)/2,0,0xA);scrifld(200,VarTextFmt(len_,0),ptitel_);
	  start_++;scrifld(z++,fm_ou3,&start_);start_--;scrifld(z++,fm_ou3,&q_files);
		//if(start_>0){ funckeys+=2; scraddpicto(1,0,75,2,4,2,18,0,4,"up"); }
		//if((start_+ScreenLines)<q_files) {funckeys+=4;scraddpicto(2,0,75,22,4,2,13,0,4,"down"); }
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=q_files) break;
	    k++;scrifld(z++,fm_ou3,&k);k--;
	    scrifld(z++,VarTextFmt(48,0),(char *)(LPCTSTR)cfilenames[k]);
			scrifld(z++,VarTextFmt(17,0),(char *)(LPCTSTR)cfiledates[k]);
			scraddpicto(1+k-start_,z-1,0,0,2,1,102,0,4,"Selecteer"); 
			scraddpicto(1+ScreenLines+k-start_,z-1,3,0,2,1,45,0,4,"Download"); 
			scraddpicto(1+ScreenLines*2+k-start_,z-1,5,0,2,1,133,0,3,"Schrap"); 
    }
    scrifld(54,fm_uu3,&nr_);
    key=scrupd(54,0x87);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		retval_=0;zero(SelectedFileName,100);
		if(key>=5001 && key<5001+ScreenLines){
			retval_=key-5001+start_;
			cstr_=CString(pselection_);k=cstr_.ReverseFind('\\');
			if(k<0) k=cstr_.ReverseFind(':');
			if(k>0) cstr_=cstr_.Left(k+1); else cstr_=CString("");
			cstr_+=cfilenames[retval_];
			copy((char *)(LPCTSTR)cstr_,SelectedFileName,cstr_.GetLength());
			retval_=1;
			goto end;			
		}
		if(key>=5001+ScreenLines && key<5001+ScreenLines*2){
			retval_=key-5001-ScreenLines+start_;
			cstr_=CString(pselection_);k=cstr_.ReverseFind('\\');
			if(k<0) k=cstr_.ReverseFind(':');
			if(k>0) cstr_=cstr_.Left(k+1);cstr_+=cfilenames[retval_];
			copy((char *)(LPCTSTR)cstr_,SelectedFileName,cstr_.GetLength());
	    GetFileFromServer(SelectedFileName);			
			// goto redo_find;
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
			default      : break;
    }
	}
	end:;
	return retval_;
}

extern "C" int MakeFullExternalBackup(int IncludeWorkfiles,int ShutDownSystem) 
{
  int16 dd,mm,jj;
	char datestr_[12];
	
	bool backup_ok_=false;
	CString reply,status_,cstr_;

	if(ShutDownSystem){
  	if(ovlcall(2,2)==0){
  		DisplayWarning("Kan systeem niet stoppen, probeer later opnieuw!",605,0); return NO;
	  }
	}
	scrnum=0;scrget(1,170);
	memset(BackupFile2Receive,0,sizeof BackupFile2Receive);
  reply=JmsCmd("CreateFullJamadataBackup|w"); // inclusief werkbestanden !
  FOREVER { 
    Sleep(600);
    status_=JmsCmd("ControlDBSessions|GetFullBackupStatus");
		if (status_.Left(4).CompareNoCase("DONE")==0) {backup_ok_=true;break;} // backup is OK
    if (status_.Left(3).CompareNoCase("BAD")==0) break; // backup is mislukt
    scrnum=0;scrget(1,7);
    scraddfield(1,10,18,0);
    scrifld(1,VarTextFmt(60,0),(char *)(LPCTSTR)status_);
    scrupd(-3,0);
	}
	if(backup_ok_){ // eerst datums in jms.ini bijwerken

		reply=JmsCmd("GetIniKeyValue|CopySettings|UsbDate-1");
		cstr_="SetIniKeyValue|CopySettings|UsbDate-2|"; cstr_+=reply;JmsCmd(cstr_);
		reply=JmsCmd("GetIniKeyValue|CopySettings|UsbDate");
		cstr_="SetIniKeyValue|CopySettings|UsbDate-1|"; cstr_+=reply;JmsCmd(cstr_);
    jddate(*u(25,2),&jj,&mm,&dd);zero(datestr_,sizeof datestr_);
    stcli_d(&datestr_[0],(long)dd,2,0);datestr_[2]='/';
    stcli_d(&datestr_[3],(long)mm,2,0);datestr_[5]='/';
    stcli_d(&datestr_[6],(long)jj,4,0);
		cstr_="SetIniKeyValue|CopySettings|UsbDate|"; cstr_+=CString(datestr_);reply;JmsCmd(cstr_);
		
		Sleep(5000); // om hem de tijd te geven om de ZIP-file af te sluiten
		int k=status_.Find('|');
		if(k) copy((char *)(LPCTSTR)status_.Mid(k+1),BackupFile2Receive,status_.GetLength()-k);
		if(ServerVersion==SERVER_MONO){ // bij MONO moet men wachten tot file is verstuurd
			FOREVER{
				Sleep(600);
				if (GetFileAttributes(BackupFile2Receive)==INVALID_FILE_ATTRIBUTES) break;
				scrnum=0;scrget(1,170);
				scraddfield(1,8,10,0);
				scrifld(1,VarTextFmt(65,0),"Bezig met klaarzetten backup voor USB-stick. Even geduld aub...");
				scrupd(-3,0);
			}
		}
	}

	if(ShutDownSystem) ovlcall(2,3); // DB heropstarten en posten vrijmaken 
	if (backup_ok_==false){
		DisplayWarning("De backup is NIET gelukt, probeer later opnieuw!",605,0); // backup is mislukt
		return NO;
	}
	return YES;
}

extern "C" void MakeStructMed(char *pd, uint16 refnr_) // 'kkk/kkff/fffcc'   K(lant) F(aktnr) C(heck) 
{
  int16 k,g=0,d=0,sys1848;
  char resul[15];
  long lan1=0,lan2,rest;
  double doub;

  sysget(1848,2,&sys1848);
  if(fldlen(2,2) && sys1848==0){
    copy(s(2,2),&resul[0],5);
    for(k=0;k<5;k++) if(resul[k]<'0' || resul[k]>'9') resul[k]='0';
    for(k=0;k<5;k++) lan1=lan1*10+resul[k]-'0';
  }
  else{
    stcli_d(resul,(long)*u(2,1),5,0);lan1=*u(2,1);
  }
//  stcli_d(resul,(long)*u(2,1),5,0);lan1=*u(2,1);
  lan2=refnr_;stcli_d(&resul[5],lan2,5,0);
  doub=( ((double)lan1)*100000E0+lan2 );
  rest = doub - ((long)(doub/97E0)) * 97E0; if(rest==0) rest=97;
  stcli_d(&resul[10],rest,2,0);

  for(k=0;k<3;k++) *(pd+d++)=resul[g++];
  *(pd+d++)='/';
  for(k=0;k<4;k++) *(pd+d++)=resul[g++];
  *(pd+d++)='/';
  for(k=0;k<5;k++) *(pd+d++)=resul[g++];
  *(pd+d)='\0';
}



extern "C" int Fld2String(int stunr, int fldnr, char *OutBuffer, int MaxLen)
{
  int i,len;
  unsigned char Desc[100]; // zeker genoeg nemen,
  unsigned char *p, *b;
	unsigned char GetStringBuf[500]; 
	
	len=fieldspc(stunr,fldnr,&b,Desc);memset(GetStringBuf,0,sizeof GetStringBuf);
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
 /*         if (JamasciDecodeFlag) {
            if (b[i]>=0x80 && b[i]<0xD0) {
              p--;
              if (!jamasci[b[i]-0x80][1]) *p++=jamasci[b[i]-0x80][0];
            }
          }*/
        }
        *p=0;
        break;
      case 0x18: // BTw-nummer
				btw_deco((char *)GetStringBuf,l(stunr,fldnr),YES);
        break;
			case 0x00: // date
				if(*u(stunr,fldnr)) datefm((char *)GetStringBuf,*u(stunr,fldnr),3);
				break;
			case 0x28: // grb 
				if(*l(stunr,fldnr)) grb_deco((char *)GetStringBuf,l(stunr,fldnr));
				break;
			case 0x20: // rekening 
				rek_deco((char *)GetStringBuf,(unsigned char *)s(stunr,fldnr),1);
				break;
    }
  }
	len=strlen((char *)GetStringBuf);if(len>MaxLen) len=MaxLen;
	copy((char *)GetStringBuf,OutBuffer,len);
	return len;
}

extern "C" int FileExist(char *FileName)
{
  if (GetFileAttributes(FileName)!=INVALID_FILE_ATTRIBUTES) return 1; else return 0;
}

extern "C" int GetPostName(char *Namestr_,uint16 pID_)
{
	int16 len_;
	CString keystr_,cstr_;

	if(pID_==0) {Namestr_[0]='\0';return 0; }
	else{
  	keystr_.Format("GetIniKeyValue|Post-%03d_Settings|Name",1+pID_/5); 
	  cstr_=JmsCmd(keystr_);
		len_=cstr_.GetLength();if(len_>15) len_=15;
	  copy((char *)(LPCTSTR)cstr_,Namestr_,len_);
		if(len_<15) Namestr_[len_]='\0';
	}
	return len_;
}

extern "C" void GetFileFromServer(char *FileName)
{
	
	CString cmd_,result_;
	
	cmd_=CString("GetFileFromServer|"); cmd_+=CString(FileName);
	result_=JmsCmd(cmd_);
	if(result_.CompareNoCase("OK")!=0) errnum=39;
}

extern "C" int ShowSavedDocument(int16 MastStuNr, long MastRecord, int16 SoortDocument, uint16 dat_beg, uint16 dat_end) 
{
	int16 z,key,j,start,max_,mode_,sort_key,curs,mstu_;
	long recs_[5000],mrec_;
	char buf_[100],mtype_,OutputMapUbl[50],docOK_[5000]; 
	CString cstr_, cmd_, filename_[5000];
	char fm_udat[]  = {4,0xC0,1,'/'};
	char fm_uLK[]  = {11,0xC8,1,0,0x09,0,'K','K','L','L',0};

	if(fldlen(7,0)==0) {errnum=12; return NO;}
	sysget(19500,50,OutputMapUbl); 
	mstu_=MastStuNr;mrec_=MastRecord;
	FOREVER{
		redo_select:;
	  if(MastStuNr==0 || MastRecord==0){
			if(mstu_==1) mtype_='L'; else mtype_='K';
			fasinit(2);curs=2;
			FOREVER{
				redo:
				scrget(1,256); z=1;
				scrifld(z++,fm_uLK,&mtype_);
				scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
				scrifld(z++,fm_udat,&dat_beg); scrifld(z++,fm_udat,&dat_end);
				key=scrupd(curs,0x81);curs=2;
				if ((key/0x100)==1) key=(key&0xFF)+5000;
				if(key==101 || key==111) {return NO;}
				if(mtype_=='L') mstu_=1; else mstu_=2;
				if(mstu_!=2)copy(s(2,3),s(mstu_,3),fldlen(mstu_,3));
				if(key==5001){
					Search(mstu_,98);curs=2; goto redo;
				}
				if(*s(mstu_,3)){
					if(Search(mstu_,0)) goto redo;
				}
				else fasinit(mstu_);
				mrec_=*u(mstu_,1);
				if(SoortDocument==1 && key==112 && (dat_beg==0 || dat_end==0)){curs=3; errnum=38; goto redo;}
				if(key==108 || (SoortDocument==1 && key==112)) break;
				if(mstu_!=2)copy(s(mstu_,3),s(2,3),fldlen(mstu_,3));
			}
		}

		scrget(1,7);scrupd(-3,0);
		fasinit(7); *u(7,10)=mstu_; *l(7,11)=mrec_;*i(7,15)=SoortDocument;
		zero((char *)recs_,sizeof recs_);if(mrec_) sort_key=2; else sort_key=3;
		start=0;max_=0;mode_=1;
		FOREVER{
			next7:;
			if(faskeyi(7,sort_key,mode_)) break; mode_=2;
			if(mstu_!=*u(7,10)) break;
			if(mrec_ && *l(7,11)!=mrec_) break;
			if(SoortDocument && *u(7,15)!=SoortDocument) goto next7;
			if(dat_beg && *u(7,4)<dat_beg) goto next7;
			if(dat_end && *u(7,4)>dat_end) goto next7;
			docOK_[max_]=1;

			if (fldlen(7,5) == 0 || *u(7, 5) != 1)
			{
				CString file_ = s(7, 2);
				cstr_.Format("..\\Mail\\Sent\\%s.EML", file_);
				
				if (!FileExist((char*)(LPCTSTR)cstr_)) {
					char buf_[20];

					for (int iA = 1; iA <= 5; iA++) {
						file_.Format("%d-%s", iA, s(7, 2));
						cstr_.Format("..\\Mail\\Sent\\%s.EML", file_);

						if (FileExist((char*)(LPCTSTR)cstr_))
							break;
					}
				}

				if (!FileExist((char *)(LPCTSTR)cstr_))
					docOK_[max_]=0;
				else
					filename_[max_] = file_;
			}

			recs_[max_++]=*l(7,1);
			if(max_>=5000) break;
		}
		if(max_==0) {
			errnum=14;
			if(MastStuNr && MastRecord) return NO;
			else goto redo_select;
		}
		if(SoortDocument==1 && key==112){
			if(DisplayWarning("Wenst u echt de geselecteerde documenten te schrappen???",61,1)==YES){
				for(j=0;j<max_;j++){
					fasinit(7); *l(7,1)=recs_[j];fasgeti(7);
					cstr_.Format("..\\Mail\\Sent\\%s.EML",s(7,2));
					remove(cstr_);
				}
			}
			goto redo_select;
		}

		start=0;curs=2;
		FOREVER{
			scrnum=0; scrget(1,257);z=1;
			for(j=start;j<start+18;j++){
    		if(recs_[j]==0) break;
				fasinit(7); *l(7,1)=recs_[j];fasgeti(7);
				*u(mstu_,1)=*l(7,11);fasgeti(mstu_);
				scrofld(z++,mstu_,3,33);scrofld(z++,7,4,-1);
				if(fldlen(7,5) && *u(7,5)==1) scraddpicto(j-start+1,z-1,2,0,2,1,112,0,4,"Bekijk status"); 
				else if(docOK_[j]) scraddpicto(j-start+1,z-1,2,0,2,1,45,0,4,"Download"); 
				scrofld(z++,7,17,30);
			}
			key=scrupd(-1,0x7);
			if(key==101) break;
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key>=5001 && key<=5018){
				fasinit(7);*l(7,1)=recs_[key-5001+start]; fasgeti(7);
				if(fldlen(7,5) && *u(7,5)==1) DisplayVerzendStatus(7,1);
				else{
  				zero(buf_,sizeof buf_);copy(s(7,2),buf_,12);
	  			cstr_.Format("GetIniKeyValue|Post-%03d_Settings|DisplayEmailAsEML",ThisPostNr); 
		  		if(atoi(JmsCmd(cstr_))==1) cmd_= "ViewMail|EML|";  else cmd_= "ViewMail|MSG|";     
			  	cmd_+=filename_[key - 5001 + start];
				  cstr_=JmsCmd(cmd_);
				}
			}
			if(key==102) start-=18;
			if(key==103) {start+=18;if(start>=max_-18) start=max_-18;}
			if(start<0) start=0;
		}
		if(MastStuNr && MastRecord) break;
	}
	return YES;
}

extern "C" int DisplayVerzendStatus(int ViaStu, int Display) // alles moet in de STU 7 of 8 ingevuld zijn, Display==0, return OK of niet)
{
	int z,key;
	uint16 *p_status_,*p_dtstatus_,stu_lk=2;
	char buf_[100],OutputMapUbl[50],stattxt_[20],*p_ref_;
	int16 peppolProviderOUT_ = 0,GEENdebug_;
	CString status_;

	sysget(1282,2,&peppolProviderOUT_);
	sysget(1284, 2, &GEENdebug_);
	stu_lk=2; if(SelfBilling) stu_lk=1;

	if(ViaStu!=7 && ViaStu!=8) {errnum=12; return NO;}
	if(ViaStu==7){
		if(fldlen(7,6)==0) {errnum=12; return NO;}
		p_ref_=s(7,6); p_status_=u(7,7);  p_dtstatus_=u(7,8);
	}
	else{
		if(fldlen(8,76)==0) {errnum=12; return NO;}
		p_ref_=s(8,76); p_status_=u(8,77);  p_dtstatus_=u(8,78);
	}

	sysget(19500,50,OutputMapUbl); *p_status_=0;

	switch(peppolProviderOUT_) {
		case 0:
			if (*(p_ref_ + 49) == 1)
				z = CodaBoxCheckStatus("", p_ref_, "YES",Display);  // Op pos 49 CN of niet
			else
				z = CodaBoxCheckStatus("", p_ref_, "NO",Display);

			if (z >= 0 && *p_status_ != 1) {
				*p_status_ = z;
				*p_dtstatus_ = *u(25,2);
				
				if (ViaStu == 7)
					fasupd(7);
			}

			zero(stattxt_, sizeof stattxt_);

			switch (*p_status_) {
				case 0 : copy("Niet verzonden",stattxt_,15); break;
				case 1 : copy("Verzonden",stattxt_,10); break;
				case 2 : copy("Aangemaakt",stattxt_,10); break;
				case 10 : copy("MISLUKT!",stattxt_,10); break;
//				case 99 : copy("In behandeling",stattxt_,14); break;
				default : copy("Onbekend",stattxt_,10); break;
			}

			break;
		case 1:
			status_ = PeppolGetDocumentStatus(p_ref_, "", Display);
			strcpy_s(stattxt_, sizeof stattxt_, status_);
			if(status_==CString("DELIVERED") || status_==CString("EXPORTED")) *p_status_=1;
			break;
	}
	if(Display==0) return (int)(*p_status_);

	if(ViaStu==7) *u(stu_lk,1)=*l(7,11); else  *u(stu_lk,1)=*u(8,3);    
	fasgeti(stu_lk);

	FOREVER{
		if(ViaStu==7){
			scrget(1,280); z=1; scraddpicto(1,0,66,21,6,3,45,0,4,"Download XML"); scraddpicto(2,0,72,21,6,3,107,0,4,"Vraag verzendstatus op");
			scrfld(z++,stu_lk,3);
			scrfld(z++,7,17);
			scrfld(z++,7,4);

			scrfld(z++,7,2);
			scrfld(z++,7,6);
			scrifld(z++,VarTextFmt(20,0),stattxt_);
			scrfld(z++,7,8);
		}
		else{
			scrget(1,281); z=1; 
			scraddpicto(2,0,66,21,6,3,107,0,4,"Vraag verzendstatus op");
//			scraddpicto(1,0,66,21,6,3,45,0,4,"Download XML");
			if(*p_status_!=1) scraddpicto(3,0,72,21,6,3,569,0,0,"Verstuur opnieuw");
			scrfld(z++,stu_lk,3);
			scrfld(z++,8,2);
			scrfld(z++,8,8);

			scrfld(z++,8,76);
			scrifld(z++,VarTextFmt(20,0),stattxt_);
			scrfld(z++,8,78);
		}
		key=scrupd(-1,0x1);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
		if(key==5001){
			zero(buf_,sizeof buf_);sprintf_s(buf_,75,"%s%s",OutputMapUbl,s(7,2));
			GetFileFromServer(buf_);
		}

		if (key == 5002) {
			switch(peppolProviderOUT_) {
				case 0:
					if (*(p_ref_ + 49) == 1)
						z = CodaBoxCheckStatus("", p_ref_, "YES",Display);  // Op pos 49 CN of niet
					else
						z = CodaBoxCheckStatus("", p_ref_, "NO",Display);

					if (z >= 0 && *p_status_ != 1) {
						*p_status_ = z;
						*p_dtstatus_ = *u(25,2);
				
						if (ViaStu == 7)
							fasupd(7);
					}

					zero(stattxt_, sizeof stattxt_);

					switch (*p_status_) {
						case 0 : copy("Niet verzonden",stattxt_,15); break;
						case 1 : copy("Verzonden",stattxt_,10); break;
						case 2 : copy("Aangemaakt",stattxt_,10); break;
						case 10 : copy("MISLUKT!",stattxt_,10); break;
//						case 99 : copy("In behandeling",stattxt_,14); break;
						default : copy("Onbekend",stattxt_,10); break;
					}

					break;
				case 1:
					status_ = PeppolGetDocumentStatus(p_ref_, "",Display);
					strcpy_s(stattxt_, sizeof stattxt_, status_);
					if(status_==CString("DELIVERED") || status_==CString("EXPORTED")) *p_status_=1;
					break;
			}
		}
		if (key == 5003) return 99;
	}
	return 1;
}

extern "C" int SendMail(int send_mode)  // send_mode : 0=mail tonen en lokaal versturen, 1= in serie zonder tussenkomst 2= zonder tussenkomst in TOCheck, dan MANUEEL in ToSend zetten!
{  // in MailMergeData eerst de data invullen, indien OK, dan staat in MailUniqueID de referentie om in stu(7,2) in te vullen
  int z,k,key,pos_,pos1_,adres_ok_,CCadres_ok_,curs;
	char buf_[20],mailprofiel_,cmdbuf_[750];
  CString cstr_,cstr1_,keystr_,template_,mergefields_,cmd_;
 
	char fm_os50[]  = {7,0x88,50,0,0,0,0};
  char fm_os30[]  = {7,0x88,30,0,0,0,0};
  char fm_os6[]   = {7,0x88,6,0,0,0,0};
  char fm_us60[]  = {7,0xC8,60,0,0,0,0};
  char fm_uJN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};

	sysget(18481,1,&mailprofiel_);if(mailprofiel_>9) mailprofiel_=0;
	// emailadres checken en eventueel opvragen
	adres_ok_=CheckEmailAdres(MailMergeData[5],sizeof MailMergeData[5],NO);
	if(MailMergeData[10][0]) CCadres_ok_=CheckEmailAdres(MailMergeData[10],sizeof MailMergeData[10],NO); else CCadres_ok_=YES;
	if(send_mode==0 || !adres_ok_){
		if(!adres_ok_) curs=5; else curs=-1;
		FOREVER{
			redo:;
			scrnum=0;scrget(1,249);z=1; 
			if(send_mode==0){
				AddTextKey(50,46,22,16,2,10001,"Bekijk mail",0x21A72B);
				if(ServerVersion>=SERVER_LIGHT) // SERVER_STANDAARD
					AddTextKey(51,63,22,16,2,10002,"Verstuur direct",0xFF);
			}
			scrifld(z++,fm_os50,MailMergeData[0]);
			scrifld(z++,fm_os50,MailMergeData[1]);
			scrifld(z++,fm_os6,MailMergeData[2]);scrifld(z++,fm_os30,MailMergeData[3]);
			scrifld(z++,fm_us60,MailMergeData[5]);if(!adres_ok_) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);
			scrifld(z++,fm_us60,MailMergeData[10]);if(!CCadres_ok_) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);
			scrifld(z++,fm_uJN,&MailSaveAdres);
			if(curs==-1){scraddfield(z,4,22,8);scrifld(z++,VarTextFmt(12,0)," F4 pas aan ");}
			key=scrupd(curs,0x89);
		  if((key/0x10000)>0) key/=0x10000;
		  else if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key==101) return 0;
			if(key==104) {curs=5;goto redo;}
			adres_ok_=CheckEmailAdres(MailMergeData[5],sizeof MailMergeData[5],NO);
			if(!adres_ok_){curs=5; errnum=34; goto redo;}
	    if(MailMergeData[10][0]) CCadres_ok_=CheckEmailAdres(MailMergeData[10],sizeof MailMergeData[10],NO); else CCadres_ok_=YES;
			if(!CCadres_ok_){curs=6; errnum=34; goto redo;}
			if(key==10002) {send_mode=1; break;} // toch via server versturen
			if(key==10001 || key==108) break;
		}
	}

	// template checken en erbij halen met de mergefields
	scrget(1,7);scrupd(-3,0);
	zeros(buf_,sizeof buf_);template_="";mergefields_="";
	if(MailMergeSpecialTemplate[0]){
		template_=CString(MailMergeSpecialTemplate);if(MailMergeTaal) template_+=CString(MailMergeTaal);
	}
	else if(MailMergeFormaat>0 && MailMergeFormaat<=30){
		sysget(18004+(MailMergeFormaat-1)*16,5,buf_); template_=CString(buf_);
		if(MailMergeTaal) template_+=CString(MailMergeTaal);
	}
	mergefields_=CString("");
	if(template_.GetLength()!=0){ // indien ingevuld dan ophalen, anders lege mail
  	cstr_="[";cstr_+=template_+"]"; cstr_.MakeUpper();
		cstr1_=JmsCmd("GetMailTemplates");cstr1_.MakeUpper();
	  if(cstr1_.Find(cstr_)>=0){// zoeken of [xxxx] ergens ertussen staat
	    mergefields_=JmsCmd("GetTemplateMergeFields|"+template_);
	  } 
	}

	CString prop_ = "MailRelayserver";

	if (mailprofiel_)
	{
		zeros(buf_, sizeof buf_);
		buf_[0] = '0' + mailprofiel_;
		prop_ += CString(buf_);
	}

	CString relayServer_ = JmsCmd("GetIniKeyValue|MailSettings|" + prop_);

	if (relayServer_ != "1" && relayServer_ != "2")
		relayServer_ = "1";

	// versturen van de mail 
	cmd_  = "MergeTemplateAndMail\r\n";
	cmd_ += "Template|" + template_ + "\r\n";
	cmd_ += "RelayServer|" + relayServer_ + "\r\n";

	if(send_mode==1){ // in serie zonder tussenkomst
		cmd_+= "Action|ToSend\r\n";    
	}
	else if(send_mode==2){ // in serie zonder tussenkomst, maar dan in tocheck en MANUEEL in tosend zetten!
		cmd_+= "Action|ToCheck\r\n";    
	}
	else{ // mail tonen om te versturen              UserEML, UserMSG, PreviewEML, PreviewMSG, ToSend, ToCheck 
		keystr_.Format("GetIniKeyValue|Post-%03d_Settings|DisplayEmailAsEML",ThisPostNr); 
    if(atoi(JmsCmd(keystr_))==1) cmd_+= "Action|UserEML\r\n"; // UserEML
	  else cmd_+= "Action|UserMSG\r\n";     
	}
	if(CString(MailMergeData[5]).Find(';')>0){
    cmd_+= "To|"+CString(MailMergeData[5])+"|"+"\r\n"; // enkel email bij meerdere adressen To|email|\r\n
	} else 	cmd_+= "To|"+CString(MailMergeData[5])+"|"+CString(MailMergeData[0])+"\r\n"; //  To|email|naam\r\n
	if(MailMergeData[10][0]){ // CC adres
    cmd_+= "CC|"+CString(MailMergeData[10])+"|"+"\r\n"; // enkel emailadres
	}
	if(mailprofiel_){ // afwijkend mailprofiel
		zeros(buf_,sizeof buf_); buf_[0]='0'+mailprofiel_;
    cmd_+= "MailProfile|"+CString(buf_)+"\r\n"; 
	}

   //    cmd_+= "CC|jan@jamadata.be|Jan Van Gestel\r\n";
  //     cmd_+= "BCC|marc_vg@hotmail.com\r\n";
	for(k=0;k<10;k++){
		if(MailMergeBijlage[k]==0) continue;
		sprintf_s(buf_,20,"%d\r\n",MailMergeBijlage[k]);
		cmd_+= "AttachJamaFileRef|"+CString(buf_);  // JamaFileRef die ge terugkrijgt bij PrtClose()  of XlsSave()
	}
	for(k=0;k<10;k++){
		if(MailMergeFileBijlage[k][0]=='\0') continue;
//		sprintf_s(buf_,20,"%d\r\n",MailMergeBijlage[k]);
		cmd_+= "AttachThisFile|"+CString(MailMergeFileBijlage[k])+"|"+"\r\n";  // specifieke file (file+path)
	}
	
	if(mergefields_.GetLength()){ // keywords vervangen 
		pos_=0;pos1_=0;
		FOREVER{
			pos1_=mergefields_.Find('\n',pos_+1); if(pos1_<0) break;
			cstr_=mergefields_.Mid(pos_,pos1_-pos_-1);
			if(cstr_.CompareNoCase("TEXTINMAIL")==0){
				cmd_+= "Replace|"+CString("TEXTINMAIL")+"|"+CString(MailMergeBodyText)+"\r\n";   // aparte variabele 
			}
			else{
				for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
					if(cstr_.CompareNoCase(MailMergeKeywords[k])==0){ // indien keyword begint met lowercase, dan heel de tekst in lowercase zetten
						if(cstr_.GetAt(0)>='a' && cstr_.GetAt(0)<='z') cmd_+= "Replace|"+cstr_+"|"+CString(MailMergeData[k]).MakeLower()+"\r\n";
						else cmd_+= "Replace|"+CString(MailMergeKeywords[k])+"|"+CString(MailMergeData[k])+"\r\n";   // hier een lijst opgeven van alle 'merge-fields' (zie hoger)
					}
				}
			}
			pos_=pos1_+1;
		}
	}
	zero(cmdbuf_,sizeof cmdbuf_); 
	z=cmd_.GetLength(); 
	copy((char *)(LPCTSTR)cmd_,cmdbuf_,cmd_.GetLength());
	CnvJamaChar(cmdbuf_,cmd_.GetLength(),0);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
	cmd_=CString(cmdbuf_);
  cstr_=JmsCmd(cmd_); // de mail versturen 
	zero(MailUniqueID,sizeof MailUniqueID);
  if(cstr_.CompareNoCase("OK")<0) return 0;    // OK als het gelukt is !
	if(cstr_.GetLength()>=15) sprintf_s(MailUniqueID,sizeof(MailUniqueID),"%s",cstr_.Mid(3,12));
	return 1;
}

extern "C" int CheckEmailAdres(char *email_, int len_,int internetcheck_) // 1=OK
{
  int k,at_fnd_,punt_fnd_;
 	CString keystr_,cstr_;


  if(internetcheck_){		// emailadres checken via internet  ... duurt wel 1 min
		keystr_="CheckEmailAddress|";keystr_+=CString(email_);
    cstr_=JmsCmd(keystr_);  // duurt wel lang voor respons 
    if(cstr_.CompareNoCase("OK")!=0) return 0; 
	}
	else{ // korte test op @ en .
		if(!(*email_>='a' && *email_<='z') && !(*email_>='A' && *email_<='Z') && !(*email_>='0' && *email_<='9')) return 0;
    at_fnd_=0; punt_fnd_=0;
    for(k=0;k<len_;k++){
			if(*(email_+k)=='\0') break;
			if(*(email_+k)==';'){
			  if(at_fnd_!=1 || punt_fnd_==0 || k<4) return 0; 
				at_fnd_=0; punt_fnd_=0;
			}
			if(*(email_+k)==' ' && (at_fnd_ || punt_fnd_)) break;
      if(*(email_+k)=='@') at_fnd_++;
      if(*(email_+k)=='.' && at_fnd_) punt_fnd_++;
    }
    if(at_fnd_!=1 || punt_fnd_==0 || k<4) return 0; 
	}
	return 1;
}

extern "C" int16 Search(int stu_,int mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
  //if(stu_<=2) parmcall[1]=7; // bits : 0 = display, 1=update, 2=add
  //else parmcall[1]=3; // GEEN ADD
  if(stu_==6) parmcall[1]=0;
  parmcall[2]=0;
  parmcall[3]=0;
//#ifdef STRAATKEY
//  if(stu_==2) parmcall[4]=STRAATKEY;
//#endif
  parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}


char VarTextFmt_Format[10];
extern "C" char *VarTextFmt(int len_,int update_)
{
	zero(VarTextFmt_Format,sizeof VarTextFmt_Format);
	VarTextFmt_Format[0]=7; VarTextFmt_Format[2]=len_; if(update_) VarTextFmt_Format[1]=0xC8; else VarTextFmt_Format[1]=0x88;
	return VarTextFmt_Format;
}

extern "C" int ShowGoogleMapsButton(int nr, int fld, int h, int v, int hlen, int vlen, int16 StuNr) 
{
	CString adres_;
	int first_=YES;

	adres_=CString("^*www.google.be/maps/place/");
	if(*s(StuNr,4)){adres_+=CString(s(StuNr,4),30); first_=NO;}
  if(*s(StuNr,5)){
		if(first_==NO) adres_+="+";
		adres_+=CString(s(StuNr,5),6);first_=NO;
	}
  if(*s(StuNr,6)){
		if(first_==NO) adres_+="+";
		adres_+=CString(s(StuNr,6),25);first_=NO;
	}
	if(first_==NO) {scraddpicto(nr,fld,h,v,hlen,vlen,544,0,0,(char *)(LPCTSTR)adres_);return YES;}
	return NO;
}

// Routines from Marc

#include "Urlmon.h"

extern "C" void ExecJmsCommand(char* buf, int buflen, char* pCommand)
{
  CString strResult = JmsCmd(pCommand);
	strResult=strResult.Mid(0,buflen-1); // bufferoverflow voorkomen owv afsluit-0
  sprintf_s(buf, buflen, strResult);
}

extern "C" int FtpDeleteFile(char *Server, char *User, char *PW, char *FileName)
{
	CString cmd_, result_;

	cmd_ = "FtpDelete|"; cmd_+=Server; cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; cmd_+="|";
	cmd_+=FileName;
	result_=JmsCmd(cmd_);

	if(result_.CompareNoCase("Deleted")==0) return 1;
	return 0;
}

extern "C" int FtpUploadFile(char *Server, char *User, char *PW, char *FileName)
{
	CString cmd_, result_;

	cmd_ = "FtpUpload|"; cmd_+=Server; cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; cmd_+="|";
	cmd_+=FileName;
	result_=JmsCmd(cmd_);

	if(result_.CompareNoCase("Uploaded")==0) return 1;
	return 0;
}

extern "C" int FtpDownloadFile(char* buf, int buflen, char *Server, char *User, char *PW, char *FileName)
{
	CString cmd_, result_;

	cmd_ = "FtpDownload|"; cmd_+=Server; cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; cmd_+="|";
	cmd_+=FileName;
	result_=JmsCmd(cmd_);
	if(result_.GetLength()){
		result_=result_.Mid(0,buflen-1); // bufferoverflow voorkomen owv afsluit-0
    sprintf_s(buf, buflen, result_);
		return 1;
	}
	buf[0]='\0'; return 0;
}

extern "C" int FtpDirectory(char* buf, int buflen, char *Server, char *User, char *PW, char *Wildcard)
{
	CString cmd_, result_;

	cmd_ = "FtpDirectory|"; cmd_+=Server; {if(Wildcard[0]) cmd_+="/"; cmd_+=Wildcard;}
	cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; 
	result_=JmsCmd(cmd_);
	if(result_.GetLength()){
		result_=result_.Mid(0,buflen-1); // bufferoverflow voorkomen owv afsluit-0
    sprintf_s(buf, buflen, result_);
		return 1;
	}
	buf[0]='\0'; return 0;
}

extern "C" int SFtpUploadFile(char *Server, char *User, char *PW, char *FileName, int PortNr, char *FtpFileName)
{
	CString cmd_, result_,cstr_;

	cmd_ = "SFtpUpload|"; cmd_+=Server; cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; cmd_+="|";
	cmd_+=FileName; cmd_+="|";
	result_.Format("%d",PortNr);
	if(PortNr) cmd_ += result_;
	cmd_+="|";
	cmd_+=FtpFileName;
	result_=JmsCmd(cmd_);

	if(result_.CompareNoCase("Uploaded")==0) return 1;
	return 0;
}

extern "C" int SFtpUploadFile2(char *Server, char *User, char *PW, char *FileName, int PortNr, char *FtpFileName)
{
	CString cmd_, result_,cstr_;

	cmd_ = "SFtpUpload2|"; cmd_+=Server; cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; cmd_+="|";
	cmd_+=FileName; cmd_+="|";
	result_.Format("%d",PortNr);
	if(PortNr) cmd_ += result_;
	cmd_+="|";
	cmd_+=FtpFileName;
	result_=JmsCmd(cmd_);

	if(result_.CompareNoCase("Uploaded")==0) return 1;
	return 0;
}

extern "C" int SFtpDownloadFile(char* buf, int buflen, char *Server, char *User, char *PW, char *FileName, int PortNr)
{
	CString cmd_, result_;

	cmd_ = "SFtpDownload|"; cmd_+=Server; cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; cmd_+="|";
	cmd_+=FileName; cmd_+="|";
	result_.Format("%d",PortNr);
	if(PortNr) cmd_ += result_;
	result_=JmsCmd(cmd_);
	if(result_.GetLength()){
		result_=result_.Mid(0,buflen-1); // bufferoverflow voorkomen owv afsluit-0
    sprintf_s(buf, buflen, result_);
		return 1;
	}
	buf[0]='\0'; return 0;
}

extern "C" int SFtpDownloadFile2(char* buf, int buflen, char *Server, char *User, char *PW, char *FileName, int PortNr)
{
	CString cmd_, result_;

	cmd_ = "SFtpDownload2|"; cmd_+=Server; cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; cmd_+="|";
	cmd_+=FileName; cmd_+="|";
	result_.Format("%d",PortNr);
	if(PortNr) cmd_ += result_;
	result_=JmsCmd(cmd_);
	if(result_.GetLength()){
		if(result_.Mid(0,5).CompareNoCase("ERROR")==0){ // dan is het een errorboodschap
			buf[0]='\0'; return 0;
		}
		result_=result_.Mid(0,buflen-1); // bufferoverflow voorkomen owv afsluit-0
    sprintf_s(buf, buflen, result_);
		return 1;
	}
	buf[0]='\0'; return 0;
}

extern "C" int SFtpDirectory(char* buf, int buflen, char *Server, char *User, char *PW, char *Wildcard, int PortNr)
{
	CString cmd_, result_;

	cmd_ = "SFtpDirectory|"; cmd_+=Server; {if(Wildcard[0]) cmd_+="/"; cmd_+=Wildcard;}
	cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; 
	cmd_+="|";
	result_.Format("%d",PortNr);
	if(PortNr) cmd_ += result_;
	result_=JmsCmd(cmd_);
	if(result_.GetLength()){
		result_=result_.Mid(0,buflen-1); // bufferoverflow voorkomen owv afsluit-0
    sprintf_s(buf, buflen, result_);
		return 1;
	}
	buf[0]='\0'; return 0;
}

extern "C" int SFtpDirectory2(char* buf, int buflen, char* Server, int PortNr, char* User, char* PW, char* Directory)
{
	CString cmd_, result_;

	cmd_ = "SFtpDirectory2|";
	cmd_ += Server;
	cmd_ += "|";
	result_.Format("%d",PortNr);
	if(PortNr) cmd_ += result_;
	cmd_ += "|";
	cmd_ += User;
	cmd_ += "|";
	cmd_ += PW; 
	cmd_ += "|";
	cmd_ += Directory;
	result_ = JmsCmd(cmd_);

	if (result_.GetLength()) {
		result_ = result_.Mid(0, buflen - 1); // Bufferoverflow voorkomen owv afsluit-0

	    sprintf_s(buf, buflen, result_);
		return 1;
	}

	buf[0] = '\0';
	return 0;
}

extern "C" int SFtpDeleteFile(char *Server, char *User, char *PW, char *FileName, int PortNr)
{
	CString cmd_, result_;

	cmd_ = "SFtpDelete|"; cmd_+=Server; cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; cmd_+="|";
	cmd_+=FileName; cmd_+="|";
	result_.Format("%d",PortNr);
	if(PortNr) cmd_ += result_;
	result_=JmsCmd(cmd_);

	if(result_.CompareNoCase("Deleted")==0) return 1;
	return 0;
}
 
extern "C" int SFtpDeleteFile2(char *Server, char *User, char *PW, char *FileName, int PortNr)
{
	CString cmd_, result_;

	cmd_ = "SFtpDelete2|"; cmd_+=Server; cmd_+="|";
	cmd_+=User; cmd_+="|"; cmd_+=PW; cmd_+="|";
	cmd_+=FileName; cmd_+="|";
	result_.Format("%d",PortNr);
	if(PortNr) cmd_ += result_;
	result_=JmsCmd(cmd_);

	if(result_.CompareNoCase("Deleted")==0) return 1;
	return 0;
}

extern "C" const char* PeppolSendDocument(char btwNr[21], char cnFlag[4], char fileName[71]) // Returns the document ID
{
	char peppolUserUitgaand_[40], peppolPasswordUitgaand_[15], peppolApiKeyUitgaand_[60], xml_[2000];
	int j;
	int16 peppolProviderUitgaand_,GEENdebug_;
	CMarkup retXml_;
	CString cmd_, peppolProviderUitgaandStr_, retVal_, cstr_, id_, toReturn_;

	__declspec(thread) static char outbuf_[2000];

	sysget(1282, 2, &peppolProviderUitgaand_);
	sysget(1284, 2, &GEENdebug_);
	zero(peppolUserUitgaand_, sizeof peppolUserUitgaand_);
	sysget(20306, 40, peppolUserUitgaand_);
	zero(peppolPasswordUitgaand_, sizeof peppolPasswordUitgaand_);
	sysget(20346, 15, peppolPasswordUitgaand_);
	zero(peppolApiKeyUitgaand_, sizeof peppolApiKeyUitgaand_);
	sysget(20361, 60, peppolApiKeyUitgaand_);

	cmd_ = "PeppolSendDocument|";
	peppolProviderUitgaandStr_.Format(_T("%d|"), peppolProviderUitgaand_);
	cmd_ += peppolProviderUitgaandStr_;
	cmd_ += peppolUserUitgaand_;
	cmd_ += "|";
	cmd_ += peppolPasswordUitgaand_;
	cmd_ += "|";
	cmd_ += peppolApiKeyUitgaand_;
	cmd_ += "|";
	cmd_ += btwNr;
	cmd_ += "|";
	cmd_ += cnFlag;
	cmd_ += "|";
	cmd_ += fileName;
	cmd_ += "|";

#if _DEBUG || FLAGDEM
	if(GEENdebug_) cmd_+= "NO"; else cmd_ += "YES"; 
#else
	cmd_ += "NO";
#endif

	retVal_ = JmsCmd(cmd_);
	zero(outbuf_, sizeof outbuf_);

	switch(peppolProviderUitgaand_) {
		case 0:
			JsonToXml(xml_, 2000, (char*)(LPCTSTR)retVal_);
			cstr_ = "<Response> " + CString(xml_) + " </Response> ";
			retXml_ = CMarkup();
			retXml_.SetDoc(cstr_);
			id_ = retXml_.FindGetData("id");

			if (id_.GetLength()) {
				strcpy_s(outbuf_, sizeof outbuf_, (LPCTSTR)id_);
				return outbuf_;
			}

			break;
		case 1:
			if (retVal_.Left(5) == "OK - ") {
				strcpy_s(outbuf_, sizeof outbuf_, (LPCTSTR)retVal_);
				return outbuf_;
			}

			break;
	}

	scrnum = 0;
	scrget(1,170);

	for (j = 0; j < 10; j++) {
		if (retVal_.GetLength() > j * 80 + 80)
			scrifld(j + 1, VarTextFmt(80, 0), (void*)(LPCTSTR)retVal_.Mid(j * 80, 80));
		else {
			scrifld(5, VarTextFmt(80, 0), (void*)(LPCTSTR)retVal_);
			break;
		}
	}

	scrifld(15, VarTextFmt(80, 0), "Druk op F8 om verder te gaan");
	scrupd(-1, 0x81);
	return outbuf_;
}

extern "C" const char* PeppolGetDocumentStatus(char documentId[50], char cnFlag[3], int DisplayError) // Returns the status for the document ID
{
	char peppolUserUitgaand_[40], peppolPasswordUitgaand_[15], peppolApiKeyUitgaand_[60], xml_[2000];
	int j;
	int16 peppolProviderUitgaand_,GEENdebug_;
	CMarkup retXml_;
	CString cmd_, peppolProviderUitgaandStr_, retVal_, cstr_, status_;

	__declspec(thread) static char outbuf2_[2000];

	sysget(1282, 2, &peppolProviderUitgaand_);
	sysget(1284, 2, &GEENdebug_);
	zero(peppolUserUitgaand_, sizeof peppolUserUitgaand_);
	sysget(20306, 40, peppolUserUitgaand_);
	zero(peppolPasswordUitgaand_, sizeof peppolPasswordUitgaand_);
	sysget(20346, 15, peppolPasswordUitgaand_);
	zero(peppolApiKeyUitgaand_, sizeof peppolApiKeyUitgaand_);
	sysget(20361, 60, peppolApiKeyUitgaand_);

	cmd_ = "PeppolGetDocumentStatus|";
	peppolProviderUitgaandStr_.Format(_T("%d|"), peppolProviderUitgaand_);
	cmd_ += peppolProviderUitgaandStr_;
	cmd_ += peppolUserUitgaand_;
	cmd_ += "|";
	cmd_ += peppolPasswordUitgaand_;
	cmd_ += "|";
	cmd_ += peppolApiKeyUitgaand_;
	cmd_ += "|";
	cmd_ += documentId;
	cmd_ += "|";
	cmd_ += cnFlag;
	cmd_ += "|";

#if _DEBUG || FLAGDEM
	if(GEENdebug_) cmd_+= "NO"; else cmd_ += "YES"; 
#else
	cmd_ += "NO";
#endif

	retVal_ = JmsCmd(cmd_);
	zero(outbuf2_, sizeof outbuf2_);

	switch(peppolProviderUitgaand_) {
		case 0:
			JsonToXml(xml_, 2000, (char*)(LPCTSTR)retVal_);
			cstr_ = "<Response> " + CString(xml_) + " </Response> ";
			retXml_ = CMarkup();
			retXml_.SetDoc(cstr_);
			status_ = retXml_.FindGetData("status");

			if (status_.GetLength()) {
				strcpy_s(outbuf2_, sizeof outbuf2_, (LPCTSTR)status_);
				return outbuf2_;
			}

			break;
		case 1:
			if (retVal_.Left(5) == "OK - ") {
				strcpy_s(outbuf2_, sizeof outbuf2_, (LPCTSTR)retVal_.Right(retVal_.GetLength() - 5));
				return outbuf2_;
			}

			break;
	}

	scrnum = 0;
	scrget(1,170);

	for (j = 0; j < 10; j++) {
		if (retVal_.GetLength() > j * 80 + 80)
			scrifld(j + 1, VarTextFmt(80, 0), (void*)(LPCTSTR)retVal_.Mid(j * 80, 80));
		else {
			scrifld(5, VarTextFmt(80, 0), (void*)(LPCTSTR)retVal_);
			break;
		}
	}

	scrifld(15, VarTextFmt(80, 0), "Druk op F8 om verder te gaan");
	if(DisplayError) scrupd(-1, 0x81);
	return outbuf2_;
}

extern "C" const char* PeppolExportDocuments(bool markAsExported) {
	char peppolUserInkomend_[40], peppolPasswordInkomend_[15], peppolApiKeyInkomend_[60], exportMap_[50];
	int j;
	int16 peppolProviderInkomend_,GEENdebug_,jj_,mm_,dd_,hh_,min_,ss_;
	uint16 dt_lastcheck_,DatumThisExport_;
	long uur_lastcheck_,UurThisExport_;
	CMarkup retXml_;
	CString cmd_, peppolProviderInkomendStr_, retVal_, cstr_, status_,fromdatestr_;

	sysget(1280, 2, &peppolProviderInkomend_);
	sysget(1284, 2, &GEENdebug_);
	sysget(1311, 2, &dt_lastcheck_);
	sysget(1313, 4, &uur_lastcheck_);
	zero(peppolUserInkomend_, sizeof peppolUserInkomend_);
	sysget(21850, 40, peppolUserInkomend_);
	zero(peppolPasswordInkomend_, sizeof peppolPasswordInkomend_);
	sysget(21890, 15, peppolPasswordInkomend_);
	zero(peppolApiKeyInkomend_, sizeof peppolApiKeyInkomend_);
	sysget(21905, 60, peppolApiKeyInkomend_);
	zero(exportMap_, sizeof exportMap_);
	sysget(1366, 50, exportMap_);

	if(peppolProviderInkomend_<0 || peppolApiKeyInkomend_[0]=='\0') return "";

	GetCurrentDateTime(&jj_,&mm_,&dd_,&hh_,&min_,&ss_); // datum en uur ophalen
	UurThisExport_=hh_*10000+min_*100+ss_;DatumThisExport_=datejd(jj_,mm_,dd_);
	hh_=0;min_=0;ss_=0; // altijd vanaf middernacht checken
	//hh_=uur_lastcheck_/10000;min_=(uur_lastcheck_-hh_*10000)/100;ss_=uur_lastcheck_-hh_*10000-min_*100;
	//if(hh_<0 || hh_>24) hh_=0; 
	//if(min_<0 || min_>60) min_=0;
	//if(ss_<0 || ss_>60) ss_=0;
	//min_-=5; // uit veiligheid 5 min teruggaan
	//if(min_<0){
	//	if(hh_>0){hh_--;min_+=60;} 
	//	else min_=0;
	//}
	if(dt_lastcheck_==0) dt_lastcheck_=*u(25,2)-30;jddate(dt_lastcheck_,&jj_,&mm_,&dd_);
	fromdatestr_.Format("%04d-%02d-%02dT%02d:%02d:%02d.000Z",jj_,mm_,dd_,hh_,min_,ss_);
	scrnum = 0;
	scrget(1,170);
	scrifld(10, VarTextFmt(40, 0), "Controleren op nieuwe Peppol facturen...");
	scrupd(-3,0);

	cmd_ = "PeppolExportDocuments|";
	peppolProviderInkomendStr_.Format(_T("%d|"), peppolProviderInkomend_);
	cmd_ += peppolProviderInkomendStr_;
	cmd_ += peppolUserInkomend_;
	cmd_ += "|";
	cmd_ += peppolPasswordInkomend_;
	cmd_ += "|";
	cmd_ += peppolApiKeyInkomend_;
	cmd_ += "|";
	cmd_ += exportMap_;
	cmd_ += "|";
	cmd_ += markAsExported ? "YES" : "NO";
	cmd_ += "|";

#if _DEBUG || FLAGDEM
	if(GEENdebug_) cmd_+= "NO"; else cmd_ += "YES"; 
#else
	cmd_ += "NO";
#endif
	cmd_ += "|";
	cmd_ += fromdatestr_;

	retVal_ = JmsCmd(cmd_);
	std::ofstream out("debugin.txt");
	out << "retVal_: " << retVal_ << "\n";

	switch(peppolProviderInkomend_) {
		case 0:
			if (retVal_.Left(2) == "OK"){
				sysput(1311, 2, &DatumThisExport_);
				sysput(1313, 4, &UurThisExport_);
				return "OK";
			}
			break;
		case 1:
			if (retVal_.Left(2) == "OK"){
				sysput(1311, 2, &DatumThisExport_);
				sysput(1313, 4, &UurThisExport_);
				return "OK";
			}
			break;
	}

	scrnum = 0;
	scrget(1,170);

	for (j = 0; j < 15; j++) {
		if (retVal_.GetLength() > j * 80 + 80)
			scrifld(j + 1, VarTextFmt(80, 1), (void*)(LPCTSTR)retVal_.Mid(j * 80, 80));
		else {
			scrifld(5, VarTextFmt(80, 1), (void*)(LPCTSTR)retVal_);
			break;
		}
	}

	scrifld(18, VarTextFmt(80, 0), "Druk op F8 om verder te gaan");
	scrupd(1, 0x81);
	return "";
}

extern "C" const char* PeppolMarkDocumentAsExported(char documentId[50]) {
	char peppolUserInkomend_[40], peppolPasswordInkomend_[15], peppolApiKeyInkomend_[60], exportMap_[50];
	int j;
	int16 peppolProviderInkomend_,GEENdebug_;
	CMarkup retXml_;
	CString cmd_, peppolProviderInkomendStr_, retVal_, cstr_, status_;

	sysget(1280, 2, &peppolProviderInkomend_);
	sysget(1284, 2, &GEENdebug_);
	zero(peppolUserInkomend_, sizeof peppolUserInkomend_);
	sysget(21850, 40, peppolUserInkomend_);
	zero(peppolPasswordInkomend_, sizeof peppolPasswordInkomend_);
	sysget(21890, 15, peppolPasswordInkomend_);
	zero(peppolApiKeyInkomend_, sizeof peppolApiKeyInkomend_);
	sysget(21905, 60, peppolApiKeyInkomend_);

	cmd_ = "PeppolMarkDocumentAsExported|";
	peppolProviderInkomendStr_.Format(_T("%d|"), peppolProviderInkomend_);
	cmd_ += peppolProviderInkomendStr_;
	cmd_ += peppolUserInkomend_;
	cmd_ += "|";
	cmd_ += peppolPasswordInkomend_;
	cmd_ += "|";
	cmd_ += peppolApiKeyInkomend_;
	cmd_ += "|";
	cmd_ += documentId;
	cmd_ += "|";

#if _DEBUG || FLAGDEM
	if(GEENdebug_) cmd_+= "NO"; else cmd_ += "YES"; 
#else
	cmd_ += "NO";
#endif

	retVal_ = JmsCmd(cmd_);

	switch(peppolProviderInkomend_) {
		case 1:
			if (retVal_.Left(2) == "OK")
				return "OK";

			break;
	}

	scrnum = 0;
	scrget(1,170);

	for (j = 0; j < 10; j++) {
		if (retVal_.GetLength() > j * 80 + 80)
			scrifld(j + 1, VarTextFmt(80, 0), (void*)(LPCTSTR)retVal_.Mid(j * 80, 80));
		else {
			scrifld(5, VarTextFmt(80, 0), (void*)(LPCTSTR)retVal_);
			break;
		}
	}

	scrifld(15, VarTextFmt(80, 0), "Druk op F8 om verder te gaan");
	scrupd(-1, 0x81);
	return "";
}

extern "C" const char* PeppolLookup(char scheme[5], char lookupCode[20]) {
	char peppolUserUitgaand_[40], peppolPasswordUitgaand_[15], peppolApiKeyUitgaand_[60], xml_[2000];
	int j;
	int16 peppolProviderUitgaand_,GEENdebug_;
	CMarkup retXml_;
	CString cmd_, peppolProviderUitgaandStr_, retVal_, cstr_, id_;

	__declspec(thread) static char outbuf3_[2000];

	sysget(1282, 2, &peppolProviderUitgaand_);
	sysget(1284, 2, &GEENdebug_);
	zero(peppolUserUitgaand_, sizeof peppolUserUitgaand_);
	sysget(20306, 40, peppolUserUitgaand_);
	zero(peppolPasswordUitgaand_, sizeof peppolPasswordUitgaand_);
	sysget(20346, 15, peppolPasswordUitgaand_);
	zero(peppolApiKeyUitgaand_, sizeof peppolApiKeyUitgaand_);
	sysget(20361, 60, peppolApiKeyUitgaand_);

	cmd_ = "PeppolLookup|";
	peppolProviderUitgaandStr_.Format(_T("%d|"), peppolProviderUitgaand_);
	cmd_ += peppolProviderUitgaandStr_;
	cmd_ += peppolUserUitgaand_;
	cmd_ += "|";
	cmd_ += peppolPasswordUitgaand_;
	cmd_ += "|";
	cmd_ += peppolApiKeyUitgaand_;
	cmd_ += "|";
	cmd_ += scheme;
	cmd_ += "|";
	cmd_ += lookupCode;
	cmd_ += "|";


#if _DEBUG || FLAGDEM
	if(GEENdebug_) cmd_+= "NO"; else cmd_ += "YES"; 
#else
	cmd_ += "NO";
#endif

	retVal_ = JmsCmd(cmd_);
	zero(outbuf3_, sizeof outbuf3_);

	switch(peppolProviderUitgaand_) {
		case 0:
			JsonToXml(xml_, 2000, (char*)(LPCTSTR)retVal_);
			cstr_ = "<Response> " + CString(xml_) + " </Response> ";
			retXml_ = CMarkup();
			retXml_.SetDoc(cstr_);
			id_ = retXml_.FindGetData("id");

			if (id_.GetLength()) {
				strcpy_s(outbuf3_, sizeof outbuf3_, (LPCTSTR)id_);
				return outbuf3_;
			}

			break;
		case 1:
			if (retVal_.Left(5) == "OK - " || retVal_.Left(6) == "NOK - ") {
				strcpy_s(outbuf3_, sizeof outbuf3_, (LPCTSTR)retVal_);
				return outbuf3_;
			}

			break;
	}

	scrnum = 0;
	scrget(1,170);

	for (j = 0; j < 10; j++) {
		if (retVal_.GetLength() > j * 80 + 80)
			scrifld(j + 1, VarTextFmt(80, 0), (void*)(LPCTSTR)retVal_.Mid(j * 80, 80));
		else {
			scrifld(5, VarTextFmt(80, 0), (void*)(LPCTSTR)retVal_);
			break;
		}
	}

	scrifld(15, VarTextFmt(80, 0), "Druk op F8 om verder te gaan");
	scrupd(-1, 0x81);
	return outbuf3_;
}

extern "C" int CodaBoxShowLicence(char *Licence)
{
	char LicCodaBox[50];
	int ret_,j,key,z,lenResult,len_,MaxOutputbufLen=2000;
	int16 GEENdebug_;
	char Outputbuf[2000],outxml_[2000];
	CString cmd_, strResult,naam_="ONGELDIGE LICENTIE",btwnr_="",iban1_="",iban2_="",iban3_="",cstr_,peppol_in_="",street_="",zip_="",city_="",dt_created_="",email_="";
	CMarkup respxml_;

	sysget(1284, 2, &GEENdebug_);
//	zero(peppol_in_,sizeof peppol_in_);
	zero(LicCodaBox,sizeof LicCodaBox); // indien niet meegegeven, dan default uit sys.fas nemen
	if(*Licence) sprintf_s(LicCodaBox, sizeof LicCodaBox,"%s",Licence); else sysget(20361,40,LicCodaBox); 

	cmd_ = "IbanityShowLicence|"; cmd_+=LicCodaBox;
#if _DEBUG || FLAGDEM
	if(GEENdebug_==0) {cmd_ += "|"; cmd_ += "YES"; }
#endif
	strResult=JmsCmd(cmd_);
	lenResult=strResult.GetLength();if(lenResult>MaxOutputbufLen) lenResult=MaxOutputbufLen; // bufferoverflow voorkomen 
	zero(Outputbuf,MaxOutputbufLen); zero(outxml_,sizeof outxml_);
	if(lenResult==0 || strResult.Left(3).Compare("@%!")==0){
		strResult=strResult.Mid(3,MaxOutputbufLen-1); // bufferoverflow voorkomen owv afsluit-0
		lenResult=strResult.GetLength();if(lenResult>MaxOutputbufLen) lenResult=MaxOutputbufLen; // bufferoverflow voorkomen 
	}
	memcpy(Outputbuf,(char *)(LPCTSTR)strResult,lenResult); 
	CnvJamaChar(Outputbuf,lenResult,1);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
	j=JsonToXml(outxml_,sizeof outxml_, Outputbuf);
	cstr_="<Response> " + CString(outxml_) + " </Response> "; // begin en einde toevoegen
	len_=cstr_.GetLength(); if(len_>sizeof outxml_) len_=sizeof outxml_; copy((char *)(LPCTSTR)cstr_,outxml_,len_);
	respxml_=CMarkup(); 
	respxml_.SetDoc(outxml_);
	if(respxml_.IsWellFormed()!=1)	goto DisplayResult;
	respxml_.ResetMainPos();
 	if(respxml_.FindElem("Response")==false) goto DisplayResult;
	respxml_.IntoElem();
 	if(respxml_.FindElem("data")==false) goto DisplayResult;
	respxml_.IntoElem();
 	if(respxml_.FindElem("attributes")==false) goto DisplayResult;
	respxml_.IntoElem();
	respxml_.ResetMainPos();
	if(respxml_.FindElem("names")){
  	respxml_.IntoElem();
		respxml_.ResetMainPos();naam_=respxml_.FindGetData("value");
		respxml_.OutOfElem();
	}
	respxml_.ResetMainPos();btwnr_=respxml_.FindGetData("companyNumber");
	respxml_.ResetMainPos();street_=respxml_.FindGetData("street");
	respxml_.ResetMainPos();cstr_=respxml_.FindGetData("streetNumber"); street_=street_+" "+cstr_;
	respxml_.ResetMainPos();zip_=respxml_.FindGetData("zip");
	respxml_.ResetMainPos();city_=respxml_.FindGetData("city");
	respxml_.ResetMainPos();email_=respxml_.FindGetData("email");
	respxml_.ResetMainPos();dt_created_=respxml_.FindGetData("createdAt");
	respxml_.ResetMainPos();peppol_in_=respxml_.FindGetData("peppolReceiver"); 
	if(peppol_in_==CString("true")) peppol_in_="JA"; else peppol_in_="Nee";
	if(dt_created_.GetLength()>=10){
  	cstr_=dt_created_.Mid(8,2)+ "/" + dt_created_.Mid(5,2) + "/" + dt_created_.Mid(0,4);dt_created_=cstr_;
	}

	respxml_.ResetMainPos();
	if(respxml_.FindElem("ibans")){
  	respxml_.IntoElem();
		respxml_.ResetMainPos();iban1_=respxml_.FindGetData("value");
		respxml_.OutOfElem();
	}
	if(respxml_.FindElem("ibans")){
  	respxml_.IntoElem();
		respxml_.ResetMainPos();iban2_=respxml_.FindGetData("value");
		respxml_.OutOfElem();
	}
	if(respxml_.FindElem("ibans")){
  	respxml_.IntoElem();
		respxml_.ResetMainPos();iban3_=respxml_.FindGetData("value");
		respxml_.OutOfElem();
	}
	DisplayResult:;
	scraddf(-1,0,0,0);z=1;
	scraddf(z++,1,32,0x3);
  scraddf(z++,3,10,0);scraddf(z++,3,24,2);
	                    scraddf(z++,4,24,2);
	                    scraddf(z++,5,24,2);	scraddf(z++,5,31,2);
	scraddf(z++,7,10,0);scraddf(z++,7,24,2);
	scraddf(z++,8,10,0);scraddf(z++,8,24,2);
	scraddf(z++,9,10,0);scraddf(z++,9,24,2);
	scraddf(z++,10,10,0);scraddf(z++,10,24,2);
	scraddf(z++,11,10,0);scraddf(z++,11,24,2);
	scraddf(z++,13,10,0);scraddf(z++,13,31,2);
	scraddf(z++,14,10,0);scraddf(z++,14,31,2);
	scraddf(z++,16,1,2);
	scraddf(z++,17,1,2);
	scraddf(z++,18,1,2);
	scraddf(z++,19,1,2);
	scraddf(z++,20,1,2);
	scraddf(z++,21,1,2);
  scraddf(z++,23,1,8);
  z=1;
  scrifld(z++,VarTextFmt(16,0),"Licentiegegevens");
  scrifld(z++,VarTextFmt(12,0),"Naam .... : ");  scrifld(z++,VarTextFmt(40,0),(char *)(LPCTSTR)naam_);
	scrifld(z++,VarTextFmt(40,0),(char *)(LPCTSTR)street_);
	scrifld(z++,VarTextFmt(6,0),(char *)(LPCTSTR)zip_);scrifld(z++,VarTextFmt(30,0),(char *)(LPCTSTR)city_);
  scrifld(z++,VarTextFmt(12,0),"BTW-nummer:");scrifld(z++,VarTextFmt(20,0),(char *)(LPCTSTR)btwnr_);
	scrifld(z++,VarTextFmt(12,0),"IBAN1 ... :"); scrifld(z++,VarTextFmt(40,0),(char *)(LPCTSTR)iban1_);
	scrifld(z++,VarTextFmt(12,0),"IBAN2 ... :"); scrifld(z++,VarTextFmt(40,0),(char *)(LPCTSTR)iban2_);
	scrifld(z++,VarTextFmt(12,0),"IBAN3 ... :"); scrifld(z++,VarTextFmt(40,0),(char *)(LPCTSTR)iban3_);
	scrifld(z++,VarTextFmt(12,0),"Email ... :"); scrifld(z++,VarTextFmt(40,0),(char *)(LPCTSTR)email_);
	scrifld(z++,VarTextFmt(21,0),"Geregistreerd sinds:"); scrifld(z++,VarTextFmt(40,0),(char *)(LPCTSTR)dt_created_);
	scrifld(z++,VarTextFmt(21,0),"Ontvangen facturen :"); scrifld(z++,VarTextFmt(4,0),(char *)(LPCTSTR)peppol_in_);

//	scrifld(z++,VarTextFmt(12,0),"Inkomende peppol actief :"); scrifld(z++,VarTextFmt(3,0),(char *)(LPCTSTR)peppol_in_);
	if(btwnr_.IsEmpty()){
		scrifld(z++,VarTextFmt(78,0),Outputbuf);
	  scrifld(z++,VarTextFmt(78,0),&Outputbuf[78]);
	  scrifld(z++,VarTextFmt(78,0),&Outputbuf[156]);
		scrifld(z++,VarTextFmt(78,0),&Outputbuf[234]);
		scrifld(z++,VarTextFmt(78,0),&Outputbuf[312]);
		scrifld(z++,VarTextFmt(78,0),&Outputbuf[390]);
	}
	else z+=6;
  scrifld(z++,VarTextFmt(10,0)," F1 terug ");
  key=scrupd(-1,0x81);
	return -1;
}

bool StartsWith(const char* str, const char* prefix) {
    if (!str || !prefix) return false; 

    size_t lenpre = strlen(prefix);
    return strncmp(str, prefix, lenpre) == 0;
}

extern "C" int CodaBoxCheckVAT(long *BtwNrBE, char *BtwEU)
{
	char str_[15], UidCodaBox[40],PwCodaBox[15],flag_1=0;
	CString cmd_, result_;
	int off_;
	long btwnr_;
	int16 peppolProviderOUT_ = 0,GEENdebug_;
	char scheme_[5];
	const char* retVal_;

	sysget(1282,2,&peppolProviderOUT_);
	sysget(1284, 2, &GEENdebug_);

	btwnr_=*BtwNrBE;
	if(btwnr_==0) return -1; // enkel Belgische BTWnrs checken voorlopig

	copy((char *)BtwNrBE,str_,4);
	if (str_[3] & 0x40) {str_[3] &= 0xBF;}
	copy(str_,(char *)&btwnr_, 4);

//	if(btwnr_>=BTWNR_OFFSET) btwnr_-=BTWNR_OFFSET;


	//if(*(long *)BtwNrBE==0) return -1; // enkel Belgische BTWnrs checken voorlopig
	zero(str_,sizeof str_);off_=0; btw_deco(str_,(long *)&btwnr_,0); if(str_[9]>='0' && str_[9]<='9') off_=1; // nieuwe jamacon
	zero(str_,sizeof str_);
	if(cmpstr(BtwEU,"BE",2)==0){copy("BE0",str_,3);btw_deco(&str_[3-off_],(long *)&btwnr_,0);} // via BTW-nr
	else {str_[0]='0';btw_deco(&str_[1-off_],(long *)&btwnr_,0);} // via KBO-nr

	switch(peppolProviderOUT_) {
		case 0:
			cmd_ = "IbanityCheckVAT|"; cmd_+=CString(str_);
#if _DEBUG || FLAGDEM
			if(GEENdebug_==0) {cmd_ += "|"; cmd_ += "YES"; }
#endif
			result_=JmsCmd(cmd_);
			result_.MakeLower(); 
			if(result_.Find("not found")>=0) return 0; // niet ingeschreven om XML te ontvangen
			if(result_.Find("urn:cen.eu:en16931:2017#compliant#urn:fdc:peppol.eu:2017:poacc:billing:")>=0) return 1; // peppol
			if(result_.Find("urn:cen.eu:en16931:2017#conformant#urn:ubl.be:1.0.0.20180214::2.1")>=0) return 2; // UBL
			break;
		case 1:
			zero(scheme_, sizeof scheme_);
			
			if (cmpstr(str_, "BE", 2) == 0){
				off_=2; copy("9925", scheme_, 4);
			}
			else{
				off_=0;copy("0208", scheme_, 4);
			}

			retVal_ = PeppolLookup(scheme_, &str_[off_]);

			if (StartsWith(retVal_, "NOK"))
				return 0;

			if (StartsWith(retVal_, "OK"))
				return 1;

			break;
	}

	return -1;
}

extern "C" int CodaBoxCheckGLN(char* glnNr)
{
	const char* retVal_;
	char scheme_[5];
	int16 peppolProviderOUT_ = 0,GEENdebug_;
	CString cmd_;
	CString result_;

	sysget(1282,2,&peppolProviderOUT_);
	sysget(1284, 2, &GEENdebug_);

	switch(peppolProviderOUT_) {
		case 0:
			cmd_ = "IbanityCheckGLN|" + CString(glnNr);
#if _DEBUG || FLAGDEM
	if(GEENdebug_==0) {cmd_ += "|"; cmd_ += "YES"; }
#endif
			result_ = JmsCmd(cmd_);
			result_.MakeLower();

			if (result_.Find("not found") >= 0)
				return 0; // niet ingeschreven om XML te ontvangen

			if (result_.Find("urn:cen.eu:en16931:2017#compliant#urn:fdc:peppol.eu:2017:poacc:billing:") >= 0)
				return 1; // peppol

			if (result_.Find("urn:cen.eu:en16931:2017#conformant#urn:ubl.be:1.0.0.20180214::2.1") >= 0)
				return 2; // UBL

			break;
		case 1:
			zero(scheme_, sizeof scheme_);
			copy("0088", scheme_, 4);
			retVal_ = PeppolLookup(scheme_, glnNr);

			if (StartsWith(retVal_, "NOK"))
				return 0;

			if (StartsWith(retVal_, "OK"))
				return 1;

			break;
	}

	return -1;
}

extern "C" int CodaBoxCheckStatus(char *Licence, char *RefCodaBox, char *CNflag, int DisplayError)
{
	char LicCodaBox[50];
	int ret_,j,lenResult,len_,MaxOutputbufLen=2000;
	int16 GEENdebug_;
	char Outputbuf[2000],outxml_[2000];
	CString cmd_, strResult,FactuurID,SentState,cstr_,errormsg;
	CMarkup respxml_;

	if(*RefCodaBox=='\0') return 99; // geen referentie meegegeven
	sysget(1284, 2, &GEENdebug_);
	zero(LicCodaBox,sizeof LicCodaBox); // indien niet meegegeven, dan default uit sys.fas nemen
	if(*Licence) sprintf_s(LicCodaBox, sizeof LicCodaBox,"%s",Licence); else sysget(20361,40,LicCodaBox); 

	cmd_ = "IbanityUBLStatus|"; cmd_+=LicCodaBox; cmd_+="|"; cmd_+=RefCodaBox; cmd_+="|"; cmd_+=CNflag;
#if _DEBUG || FLAGDEM
	if(GEENdebug_==0) {cmd_ += "|"; cmd_ += "YES"; }
#endif
	strResult=JmsCmd(cmd_);
	lenResult=strResult.GetLength();if(lenResult>MaxOutputbufLen) lenResult=MaxOutputbufLen; // bufferoverflow voorkomen 
	zero(Outputbuf,MaxOutputbufLen);
	if(lenResult==0 || strResult.Left(3).Compare("@%!")==0){
		strResult=strResult.Mid(3,MaxOutputbufLen-1); // bufferoverflow voorkomen owv afsluit-0
		lenResult=strResult.GetLength();if(lenResult>MaxOutputbufLen) lenResult=MaxOutputbufLen; // bufferoverflow voorkomen 
	}
	memcpy(Outputbuf,(char *)(LPCTSTR)strResult,lenResult); 
	CnvJamaChar(Outputbuf,lenResult,1);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
	j=JsonToXml(outxml_,sizeof outxml_, Outputbuf);
	cstr_="<Response> " + CString(outxml_) + " </Response> "; // begin en einde toevoegen
	len_=cstr_.GetLength(); if(len_>sizeof outxml_) len_=sizeof outxml_; copy((char *)(LPCTSTR)cstr_,outxml_,len_);
	respxml_=CMarkup(); 
	respxml_.SetDoc(outxml_);
	if(respxml_.IsWellFormed()!=1)	return 99;
	respxml_.ResetMainPos();
 	if(respxml_.FindElem("Response")==false) return -1;
	respxml_.IntoElem();
	if(respxml_.FindElem("data")==false) return -1;
	respxml_.IntoElem();
	if(respxml_.FindElem("attributes")==false) return -1;
	respxml_.IntoElem();
	respxml_.ResetMainPos();FactuurID=respxml_.FindGetData("transmissionId");
	respxml_.ResetMainPos();SentState=respxml_.FindGetData("status");
	if(SentState.CompareNoCase("failed")==0 || SentState.CompareNoCase("invalid")==0){
	  respxml_.ResetMainPos();
 	  if(respxml_.FindElem("errors")){
		  respxml_.IntoElem();
	    respxml_.ResetMainPos();errormsg=respxml_.FindGetData("detail");
			zero(Outputbuf,sizeof Outputbuf); 
			lenResult=errormsg.GetLength();if(lenResult>MaxOutputbufLen) lenResult=MaxOutputbufLen; // bufferoverflow voorkomen 
			memcpy(Outputbuf,(char *)(LPCTSTR)errormsg,lenResult); 
		}
		scrnum=0;scrget(1,170);
		for(j=0;j<20;j++) scrifld(j+1,VarTextFmt(80,0),&Outputbuf[j*80]);
		scrifld(23,VarTextFmt(80,0),"Druk op F8 om verder te gaan");
		if(DisplayError) scrupd(-1,0x81);
		return 10;
	}
	else if(SentState.CompareNoCase("Created")==0) return 2;
	else if(SentState.CompareNoCase("Sent")==0) return 1;
	else if(SentState.CompareNoCase("Not Sent")==0 || SentState.CompareNoCase("not-sent")==0) return 0;
	return 99;
}





extern "C" int WebrequestJson(char *Outputbuf, int MaxOutputbufLen, char *Url, char *Method, char *User, char *PW, char *HeaderKey, char *HeaderValue, char *Message, char *FileName, int ForceUnchangedInput, int ForceUnchangedOutput)
{
	int lenResult=0;
	CString cmd_;
	
//	CString CJMSDlg::CmdWebrequestJson(CString Cmd){ // WebrequestJson url|Method|User|PW|HeaderKey|HeaderValue|Body|FilePath|Boundary|forceUnchangedInput|forceUnchangedOutput
//	Cmd = "https://sandbox-api.codabox.com/v2/peppol/receiver/check-presence/|POST|PL-3fdaead4-82ab-4f31-bb0e-2fd|BYUzx86Dw4|X-Software-Company|8ce88971-32b0-433c-a080-17ee2710baa9|{\"scheme_id\":\"BE:CBE\",\"value\":\"0886886638\"}|||false|false"; //teststring for PeppolCheckVAT with json

	cmd_=CString("WebrequestJson|");
	cmd_+=CString(Url) + "|";
	cmd_+=CString(Method) + "|";
	cmd_+=CString(User) + "|";
	cmd_+=CString(PW) + "|";
	cmd_+=CString(HeaderKey) + "|";
	cmd_+=CString(HeaderValue) + "|";
	cmd_+=CString(Message) + "|";
	cmd_+=CString(FileName) + "|";
	if(ForceUnchangedInput) cmd_+="true|"; else cmd_+="false|";
	if(ForceUnchangedOutput) cmd_+="true|"; else cmd_+="false|";

	CString strResult = JmsCmd(cmd_);
	lenResult=strResult.GetLength();if(lenResult>MaxOutputbufLen) lenResult=MaxOutputbufLen; // bufferoverflow voorkomen 
	memset(Outputbuf,0,MaxOutputbufLen);
	// if(strResult.GetLength()==0) return 0;
	if(lenResult==0 || strResult.Left(3).Compare("@%!")==0){
		strResult=strResult.Mid(3,MaxOutputbufLen-1); // bufferoverflow voorkomen owv afsluit-0
		lenResult=strResult.GetLength();if(lenResult>MaxOutputbufLen) lenResult=MaxOutputbufLen; // bufferoverflow voorkomen 
		memcpy(Outputbuf,(char *)(LPCTSTR)strResult,lenResult); 
    // sprintf_s(Outputbuf, MaxOutputbufLen, strResult);
		return 0;
	}

//	strResult=strResult.Left(MaxOutputbufLen-1); //.lef.Mid(0,MaxOutputbufLen-1); // bufferoverflow voorkomen owv afsluit-0
	memcpy(Outputbuf,(char *)(LPCTSTR)strResult,lenResult);
	CnvJamaChar(Outputbuf,lenResult,1);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
//  sprintf_s(Outputbuf, MaxOutputbufLen, strResult);
	return 1;
}

extern "C" int JsonToXml(char *Outputbuf, int MaxOutputbufLen, char *JsonString)
{
	CString cmd_;
	
	cmd_=CString("JsonToXml|");
	cmd_+=CString(JsonString);

	CString strResult = JmsCmd(cmd_);
	memset(Outputbuf,0,MaxOutputbufLen);
	if(strResult.GetLength()==0) return 0;
	strResult=strResult.Mid(0,MaxOutputbufLen-1); // bufferoverflow voorkomen owv afsluit-0
  sprintf_s(Outputbuf, MaxOutputbufLen, strResult);
	return 1;
}

extern "C" int XmlToJson(char *Outputbuf, int MaxOutputbufLen, char *XmlString)
{
	CString cmd_;
	
	cmd_=CString("XmlToJson|");
	cmd_+=CString(XmlString);

	CString strResult = JmsCmd(cmd_);
	memset(Outputbuf,0,MaxOutputbufLen);
	if(strResult.GetLength()==0) return 0;
	strResult=strResult.Mid(0,MaxOutputbufLen-1); // bufferoverflow voorkomen owv afsluit-0
  sprintf_s(Outputbuf, MaxOutputbufLen, strResult);
	return 1;
}


// utilitys for web-service

static int GetIntFromResponse(int pos, int len);
static void InitHeaderStrings();
static bool GetASPNetParameters();
static CString InternetErrNum;
static CString strResponse;
static CString strEventValidation;
static CString strViewState;
static CString strReference;
static CString strHTTPBoundary;
static CString strFileName;
static CString strPreFileData;
static CString strPostButtonData;
static CString strPostFieldData;
static CString strSoftwareSupplier;

static DWORD SendHTTPPost();
static void UploadDone();
static void UploadResults(CString SourcePath, CString ArchivePath);
static void UploadFile(char* FileName,CString SourcePath, CString ArchivePath);
static CString MakeStateData(CString& strViewState, CString& strEventValidation);
static CString MakeRequestHeaders();
static CString MakePreFileData();
static CString MakePostButtonData(char *Button, char *Value);
static CString AddField(char *FieldName, CString Value);

////////////////////////////////////////////////

#include <afxinet.h>
#include <ATLComTime.h>

#define		SERVERNAME "svc.bibi.be"
#define   OBJECTNAME "svc.aspx" // let op : maar 1 /
#define   HTTPS_Flag	false

static bool GetASPNetParameters()
{
  int i,j;
	
	InitHeaderStrings();

	int ret=SendHTTPPost();

	if (ret == -1) {  // no internetconnection
    TRACE("No connection to the Internet !");
		return false;
	}
	
	else if (ret == HTTP_STATUS_OK) {
		i=strResponse.Find("__EVENTVALIDATION",0);
		if (i>=0) {
      i=strResponse.Find("value=",i);
		  j=strResponse.Find("\" />",i+8);
		  strEventValidation=strResponse.Mid(i+7,j-i-7);
    }

		i=strResponse.Find("__VIEWSTATE",0);
		i=strResponse.Find("value=",i);
		j=strResponse.Find("\" />",i+8);
		strViewState=strResponse.Mid(i+7,j-i-7);
  }

  if (strViewState.GetLength()>0) return true;
  TRACE("No ASP-parameters found in reply !");
	return false;
}

static CString MakeRequestHeaders()
{
  CString strFormat;
  CString strData;

  strFormat = _T("Content-Type: multipart/form-data; boundary=%s\r\n");
  strData.Format(strFormat, strHTTPBoundary);
  return strData;
}

static CString MakePreFileData()
{
	CString strFormat;
	CString strData;

	strFormat = _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"filUpload\"; filename=\"%s\"");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Type: image/gif");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Transfer-Encoding: binary");
	strFormat += _T("\r\n\r\n");
	strData.Format(strFormat, strHTTPBoundary, strFileName);
	return strData;
}

static CString AddField(char *FieldName, CString Value)
{
	CString strFormat;
	CString strData;

	strFormat = _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"");
	strFormat += FieldName;
	strFormat += _T("\"");
	strFormat += _T("\r\n\r\n");
	strFormat += Value;
	strFormat += _T("\r\n");
	strData.Format(strFormat, strHTTPBoundary);
	strPostFieldData+=strData;
	return strData;
}

static CString MakePostButtonData(char *Button, char *Value)
{
	CString strFormat;
	CString strData;

	strFormat =  _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"");
	strFormat += Button;
	strFormat += _T("\"");
	strFormat += _T("\r\n\r\n");
	strFormat += _T("\"");
	strFormat += Value;
	strFormat += _T("\"");
	strFormat += _T("\r\n");
	strFormat += _T("--%s--");
	strFormat += _T("\r\n");
	strData.Format(strFormat, strHTTPBoundary, strHTTPBoundary);
	return strData;
}

static DWORD SendHTTPPost()
{
	CFile fTrack;
	DWORD dwTotalRequestLength;
	DWORD dwChunkLength;
	DWORD dwReadLength, dwRet;
	void* pBuffer;
	BOOL bSuccess = TRUE;
	int FileLen;

	CInternetSession session("The FWP-system");
	CHttpConnection* pServer = NULL;
	CHttpFile* pHTTP = NULL;

  if (strFileName.GetLength()==0 || (FALSE == fTrack.Open(strFileName, CFile::modeRead | CFile::shareDenyWrite)))
	{
		FileLen=0;
	}
  else FileLen=fTrack.GetLength();

	try
	{
		char szBuff[10000];
		INTERNET_PORT nPort;
		DWORD dwFlags=0;
    CString strServerName=SERVERNAME;
    CString strObject=OBJECTNAME;

		if (FileLen) strPreFileData = MakePreFileData();
			
		dwTotalRequestLength = strPostFieldData.GetLength()+strPreFileData.GetLength() + strPostButtonData.GetLength();
		if (FileLen) dwTotalRequestLength+=(FileLen+2);
		dwChunkLength = 64 * 1024;
		pBuffer = malloc(dwChunkLength);

		if (NULL == pBuffer) return -1;
	
		
		dwFlags=INTERNET_FLAG_RELOAD;
		if (HTTPS_Flag) {
		  nPort=INTERNET_DEFAULT_HTTPS_PORT;
			dwFlags|=INTERNET_FLAG_SECURE;
		}
		else nPort=INTERNET_DEFAULT_HTTP_PORT;
		pServer = session.GetHttpConnection(strServerName, nPort);
		pHTTP = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject,NULL,1,NULL,NULL,dwFlags);

		pHTTP->AddRequestHeaders(MakeRequestHeaders());
		pHTTP->SendRequestEx(dwTotalRequestLength, HSR_SYNC | HSR_INITIATE);

		if (strPostFieldData.GetLength()>0) pHTTP->Write(strPostFieldData, strPostFieldData.GetLength());
		
		if (FileLen) {
			pHTTP->Write(strPreFileData, strPreFileData.GetLength());
			dwReadLength = -1;
			while (0 != dwReadLength) {
				dwReadLength = fTrack.Read(pBuffer, dwChunkLength);
				if (0 != dwReadLength) {
					pHTTP->Write(pBuffer, dwReadLength);
				}
			}
			pHTTP->Write("\r\n",2);
		}
		if (strPostButtonData.GetLength()>0) pHTTP->Write(strPostButtonData, strPostButtonData.GetLength());
		pHTTP->EndRequest(HSR_SYNC);

	 
		pHTTP->QueryInfoStatusCode(dwRet);

		if (dwRet == HTTP_STATUS_OK)
		{
      strResponse=""; 
			bool filefound=false;
			long pos=0L;
			int nRead;
			CFile RecFile;
			while (true) {
				nRead = pHTTP->Read(szBuff, sizeof(szBuff)-10);
				if (nRead <= 0)  break;
				szBuff[nRead]=0;
				strResponse+=szBuff;
				pos+=nRead;
			}
 		}
    else {
      CString Rep;
      Rep.Format("HTTP post failed, status was not [200] but %d !",dwRet);
      TRACE(Rep);
    }
	}

	catch (CInternetException* pEx)
	{
  	InternetErrNum.Format("Internet error : (0x%08X)",pEx->m_dwError);
    TRACE(InternetErrNum);			
		dwRet=-1;
		pEx->Delete();
	}
	if (pHTTP) {
	  pHTTP->Close();
		delete pHTTP;
	}
	if (pServer) {
	  pServer->Close();
		delete pServer;
	}
	if (pBuffer) free(pBuffer);
	session.Close();
	return dwRet;
}


static void UploadFile(char* FileName,CString SourcePath)
{
	CString SourceFileName=SourcePath+"\\"+FileName;

	if (GetFileAttributes(SourceFileName)==INVALID_FILE_ATTRIBUTES) return;
	InitHeaderStrings();
	strFileName=SourceFileName;
	MakePreFileData();
	strPostButtonData+=MakePostButtonData("BtnUpload","Upload");
	//DisplayStatus(FileName,": transmitting ...");
  DWORD dwRet=SendHTTPPost();   
  //DisplayStatus(FileName," : Transmitted\r\n");
	if (dwRet == HTTP_STATUS_OK) {
    int i=strResponse.Find("\r",0);
		//if (i > 0) DisplayStatus("  Answer= ",(char *)(LPCTSTR)strResponse.Left(i+2));
	}

}

static void InitHeaderStrings()
{
  strPostFieldData = "\r\n";
	strPreFileData = "";
	strFileName = "";
	strPostButtonData = "";
	strHTTPBoundary = _T("-------------------IllBeVerySurprisedIfThisTurnsUp.");
	if (strViewState.GetLength()>0) {
	  AddField("__VIEWSTATE",strViewState);
		if (strEventValidation.GetLength()>0) AddField("__EVENTVALIDATION",strEventValidation);
	}
}

static int GetIntFromResponse(int pos, int len)
{
	int ret=0;
	int i;

	for (i=0; i<len; i++) {
	  ret *=10;
		ret += (strResponse.GetAt(pos+i)-'0');
	}
	return ret;
}

extern "C" int BibiDownload(char* System,char* UserName,char* PassWord,char* FileName,char* DestPath)
{
  if (!GetASPNetParameters()) return false;

  InitHeaderStrings();
	CString DownloadFileName=DestPath;
  if (DownloadFileName.Right(1).Compare("\\")!=0) DownloadFileName+="\\";
  DownloadFileName+=FileName;

  AddField("boxUserName",UserName);
  AddField("boxPassword",PassWord);
  AddField("boxSystem",System);
  AddField("boxFileName",FileName);
  AddField("boxExtra","FileTime");
	strPostButtonData+=MakePostButtonData("BtnDownload","Download");
	int ret = SendHTTPPost();   
  if (ret != HTTP_STATUS_OK) return NO;

  int i=strResponse.Find("#FileTime="); // #FileTime=40628.0796758912##
  if (i<0) return NO; // geen file gevonden !

  int j=strResponse.Find("#",i+1);
  int len = j - i - 10;
  CString strFileDateTime=strResponse.Mid(i+10,len);
  // normaal geeft de SVC datum terug in 40628.0796758912 vorm (de SVC.aspx zet een , om in een .) en 10cijfers na komma
  double FileDateTime=atof(strFileDateTime.Left(5))+atof(strFileDateTime.Mid(6).Left(10))/10000000000.;
  TRACE("FileDateTime=%17.10f   StringReceived=%s\n",FileDateTime,strFileDateTime.Left(16));
 
  COleDateTime dt((DATE)FileDateTime); 
  SYSTEMTIME sysTime;
  dt.GetAsSystemTime(sysTime);
  // Get the timezone info.
  TIME_ZONE_INFORMATION TimeZoneInfo;
  GetTimeZoneInformation( &TimeZoneInfo );
  // Convert local time to UTC.
  SYSTEMTIME GmtTime = { 0 };
  TzSpecificLocalTimeToSystemTime( &TimeZoneInfo,
                                  &sysTime,
                                  &GmtTime );
  //FileTime must be in UTC format (therfor convertion)
  FILETIME WebFileLastWriteTime;
  SystemTimeToFileTime(&GmtTime,&WebFileLastWriteTime);

  InitHeaderStrings();
  AddField("boxUserName",UserName);
  AddField("boxPassword",PassWord);
  AddField("boxSystem",System);
  AddField("boxFileName",FileName);
	strPostButtonData+=MakePostButtonData("BtnDownload","Download");
	ret = SendHTTPPost();   
  if (ret != HTTP_STATUS_OK) return NO;

  if (GetFileAttributes(DownloadFileName)!=INVALID_FILE_ATTRIBUTES) _unlink(DownloadFileName);
  CFile dlFile;
  dlFile.Open(DownloadFileName,CFile::modeCreate|CFile::modeWrite,NULL,NULL);
	dlFile.Write(strResponse,strResponse.GetLength());
  SetFileTime(dlFile.m_hFile,NULL, NULL, &WebFileLastWriteTime);
  dlFile.Close();

  return YES;
}


extern "C" int BibiFileUpdated(char* System,char* UserName,char* PassWord,char* FileName,char* DestPath)
{
  if (!GetASPNetParameters()) return NO;

  InitHeaderStrings();
	CString DownloadFileName=DestPath;
  if (DownloadFileName.Right(1).Compare("\\")!=0) DownloadFileName+="\\";
  DownloadFileName+=FileName;
  //if (GetFileAttributes(DownloadFileName)!=INVALID_FILE_ATTRIBUTES) _unlink(DownloadFileName);

  AddField("boxUserName",UserName);
  AddField("boxPassword",PassWord);
  AddField("boxSystem",System);
  AddField("boxFileName",FileName);
  AddField("boxExtra","FileTime");
	strPostButtonData+=MakePostButtonData("BtnDownload","Download");
	SendHTTPPost();   

  int i=strResponse.Find("#FileTime="); // #FileTime=40628.0796758912##
  if (i<0) return NO; // geen file gevonden !

  if (GetFileAttributes(DownloadFileName)==INVALID_FILE_ATTRIBUTES) return YES; // lokaal geen file te vinden !

  CFile dlFile;
  dlFile.Open(DownloadFileName,CFile::modeRead,NULL,NULL);

  int j=strResponse.Find("#",i+1);
  int len = j - i - 10;
  CString strFileDateTime=strResponse.Mid(i+10,len);
  // normaal geeft de SVC datum terug in 40628.0796758912 vorm (de SVC.aspx zet een , om in een .) en 10cijfers na komma
  double FileDateTime=atof(strFileDateTime.Left(5))+atof(strFileDateTime.Mid(6).Left(10))/10000000000.;
  TRACE("FileDateTime=%17.10f   StringReceived=%s\n",FileDateTime,strFileDateTime.Left(16));
 
  COleDateTime dt((DATE)FileDateTime); 
  SYSTEMTIME sysTime;
  dt.GetAsSystemTime(sysTime);
  // Get the timezone info.
  TIME_ZONE_INFORMATION TimeZoneInfo;
  GetTimeZoneInformation( &TimeZoneInfo );
  // Convert local time to UTC.
  SYSTEMTIME GmtTime = { 0 };
  TzSpecificLocalTimeToSystemTime( &TimeZoneInfo,
                                  &sysTime,
                                  &GmtTime );
  //FileTime must be in UTC format (therfor convertion)
  FILETIME WebFileLastWriteTime;
  SystemTimeToFileTime(&GmtTime,&WebFileLastWriteTime);

  FILETIME LocalFileLastWriteTime;
  GetFileTime(dlFile.m_hFile, NULL, NULL, &LocalFileLastWriteTime);
  SetFileTime(dlFile.m_hFile,NULL, NULL, &LocalFileLastWriteTime); // om die ongewijzigd te houden !
  dlFile.Close();

  if (LocalFileLastWriteTime.dwHighDateTime != WebFileLastWriteTime.dwHighDateTime || LocalFileLastWriteTime.dwLowDateTime != WebFileLastWriteTime.dwLowDateTime) return YES;
  
  return NO;
}

extern "C" bool BibiUpload(char* System, char* UserName, char* PassWord, char* FileName)
{
  return false;
}
