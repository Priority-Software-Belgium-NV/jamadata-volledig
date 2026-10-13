#include "Std\OVLCpp.h"
#include "OvlShare.h"
extern "C" char* BKH2802GetD() {return &zzvw;}

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define   DIM_DOSSIER  200
#define   DIM_FACTUREN  36
#define   LEN_SYSDATA  5000


extern "C" char BKH2802dat[] = "bkh2802  00:01 12/07/11 (c) Jamadata"; // Beheer dossiers (+.J.D)
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" int ExecCopyDossier(char *FromCode,char *ToCode,char *ToNaam,int CopyMode,int ShutDownSystem); // CopyMode: 0= alles 1=boekhouding 2=alles excl. bon

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static unsigned char fm_us75[]  = {7,0xC8,75,0,0,0,0};
static unsigned char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static unsigned char fm_us6[]   = {7,0xC8,6,0,0,0,0};
static unsigned char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static unsigned char fm_us1U[]  = {7,0xC8,1,0,1,0,0};
static unsigned char fm_us2U[]  = {7,0xC8,2,0,1,0,0};
static unsigned char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
static unsigned char fm_os63[]  = {7,0x88,63,0,0,0,0};
static unsigned char fm_os60[]  = {7,0x88,60,0,0,0,0};
static unsigned char fm_os30[]  = {7,0x88,30,0,0,0,0};
static unsigned char fm_os20[]  = {7,0x88,20,0,0,0,0};
static unsigned char fm_os3[]   = {7,0x88,3,0,0,0,0};
static unsigned char fm_os2[]   = {7,0x88,2,0,0,0,0};
static unsigned char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static unsigned char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static unsigned char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static unsigned char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static unsigned char fm_of6_0[] = {6,0x94,6,0,0x70,0};
static unsigned char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static unsigned char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static unsigned char fm_ul8[]   = {6,0xD3,8,0,0x70,0};
static unsigned char fm_udat[]  = {4,0xC0,1,'/'};
static unsigned char fm_odat[]  = {4,0x80,1,'/'};
static unsigned char fm_ogrb[]  = {2,0xA8};
static unsigned char fm_menu[]  = {7,0x48,1,0,9,0,0};
static unsigned char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static unsigned char fm_uAT[]   = {9,0xC8,1,0,1,0,'A','T',0};
static unsigned char fm_uu03[]  = {10,0xD0,1,0,0x60,0xC0,0,0,3,0};
static char fm_osdum[] = {7,0x88,255,0,0,0,0};

static char sys_data[LEN_SYSDATA+10],FromCode[4],ToCode[4],InpJaartal[3],FirmaOpmerking[10],OpmerkingVoorbeeld[20];
static char NewFirmaName[40];
static int  AantalDossiers, AantalFacturen;
static uint16 FlagMultiCompany, DatumVandaag;
static CString FacturenDir,FasSubDir="..\\FAS\\";
   
static struct _dossier {
  char code[4];
  char naam[31];
  short unsigned dt_archiv;
  short unsigned dt_creatie;
  CString filename;
} TbDossiers[DIM_DOSSIER];


static struct _facturen {
  CString code;
  CString jaartal;
  int aantal;
} TbFacturen[DIM_FACTUREN];

static void CopyDossier(int mode_);
static void DeleteDossier(void);
static void DeleteFacturen(void);
static void fileopen(int16 nr_);
static bool ShowDossier(int mode_,char *ptitel_);
static int LoadDossiers(int no_fas);
static int LoadFacturenTabel(void);
static void RenameFacturen(void);
static bool ShowFacturen(int mode_,char *ptitel_);

static double String2Getal(CString S,char decim_kar);
static double String2Double(CString S){return String2Getal(S,',');}
static double String2Double(CString S,char decim_kar){ return String2Getal(S,decim_kar);}
static int String2Int(CString S){return (int)(String2Getal(S,','));}
static CString Double2String(double getal,long mode); // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
static CString Int2String(int getal){return Double2String((double) getal,0); }
static int SpaceZeros(char* ps_,int max_len);


static int ZCstr2Arr(CString cstr_, char *p_arr_, int max_len_);
static int copy0(char *ps,char *pd,int max);
static void int2str(int d, char *s, int len);
static void DeleteOldMail(void);
static void DisplayBezig(char* tekst_, char attrib_);
static void DisplayMenuTitel(int ypos_,char* tekst_,char attrib_);
//static int DisplayWarning(char *ptxt, int icoon,int mode);
static double round(double bd_,double bd_afr_);
static int16 funkdsp(int16 z,int16 h,char *ptxt,int16 lin_);

  
extern "C" void BKH2802cod()
{
	int16 key,dd,mm,jaartal;
  char choice,str_[30];


	fasunlck(-2);

	if(ovlcall(2,2)==0) goto endsr; // stop server

  DatumVandaag=*u(25,2); jddate(DatumVandaag,&jaartal,&mm,&dd);
  jaartal--;copy("Voorbeeld : (",OpmerkingVoorbeeld,13);sprintf(&OpmerkingVoorbeeld[13],"%4d",jaartal);bcopy(")",&OpmerkingVoorbeeld[17],2);
  sysget(1788,2,&FlagMultiCompany);
  zero(str_,sizeof str_);sysget(4704,25,str_); FacturenDir=CString(str_);FacturenDir.TrimRight();
  LoadDossiers(NO);
  FOREVER {
    scrget(3,1);
    scrifld(1,fm_menu,&choice);
    key=scrupd(1,0x401);
    if(key==101) break;
    switch(choice){
      case '1' : CopyDossier(0); break;
      case '2' : CopyDossier(1); break;
      case '3' : DeleteDossier(); break;
      case '5' : if(FlagMultiCompany==YES && FacturenDir.GetLength()>0) RenameFacturen(); break;
      case '6' : if(FacturenDir.GetLength()>0) DeleteFacturen(); break;
      case '7' : DeleteOldMail(); break;
      default : errnum=34; break;
    }
  }
	ovlcall(2,3); // DB heropstarten en posten vrijmaken 
	endsr:;
  ovlexit(-1);
}

static void CopyDossier(int mode_) // 0 = alles, 1=boekhouding 
{
	int len_,k;
  char *ptitel_,*ptekst_;

  if(mode_==0){
    ptekst_= "Wenst U echt dit VOLLEDIG dossier te kopieren ???";
    ptitel_= "Volledige interne kopie maken van een bestaand dossier";
  }
  else{
    ptekst_= "Wenst U echt de BOEKHOUDING naar dit dossier te kopieren ???";
    ptitel_="Overbrengen boekhouding van een dossier naar zijn kopie";
  }
  
  zeros(FromCode,sizeof FromCode);zeros(ToCode,sizeof ToCode);zeros(FirmaOpmerking,sizeof FirmaOpmerking);
  if(FlagMultiCompany==NO){bcopy("FAS",FromCode,3);bcopy("COP",ToCode,3);}
  LoadDossiers(NO);
  FOREVER{
    if(ShowDossier(mode_,ptitel_)==false) break;
		if(DisplayWarning(ptekst_,605,YES)==YES){
      scrget(1,7);scrupd(-3,0);
			for(len_=0;len_,10;len_++) if(FirmaOpmerking[len_]=='\0') break;
			for(k=0;k<30;k++) if(NewFirmaName[k]=='\0') break;
      k++;if((k+len_)>30) k-=k+len_-30;
      NewFirmaName[k-1]=' ';bcopy(FirmaOpmerking,&NewFirmaName[k],len_);
    	if(ExecCopyDossier(FromCode,ToCode,NewFirmaName,mode_,NO)==NO){
    		DisplayWarning("Het aanmaken van de kopie is mislukt! Gelieve opnieuw te proberen.",605,0);
  	  }
      if(FlagMultiCompany){zeros(FromCode,sizeof FromCode);zeros(ToCode,sizeof ToCode);}
      LoadDossiers(NO);
    }
  }
}


static void DeleteDossier(void)  
{
	CFileFind finder;
	BOOL bWorking;
  char *ptitel_;

  ptitel_= "Schrappen van verouderde dossiers";
  
  zeros(FromCode,sizeof FromCode);zeros(ToCode,sizeof ToCode);zeros(FirmaOpmerking,sizeof FirmaOpmerking);
  if(LoadDossiers(YES)==0) goto endsr;
  FOREVER{
    if(ShowDossier(2,ptitel_)==false) break;
    if(DisplayWarning("Wenst U echt dit dossier te SCHRAPPEN ???",605,YES)){
      DisplayBezig("Bezig met verwijderen dossier. Even geduld ....",0xA); 
			bWorking = finder.FindFile(FasSubDir+CString("*.") + CString(FromCode));
			while (bWorking) {
					bWorking = finder.FindNextFile();
					if (finder.IsDirectory()) continue;
					remove(finder.GetFilePath());
			}
			finder.Close();
      zeros(FromCode,sizeof FromCode);
      if(LoadDossiers(YES)==0) break;
    } 
  }

endsr:;
}

static bool ShowDossier(int mode_,char *ptitel_) // 0 = alles, 1=boekhouding 2=delete
{

  int k,z,key,start_,curs=1,z_dossier_;

	zero(NewFirmaName,sizeof NewFirmaName);
  start_=0;curs=1;
  FOREVER{
redo:;
    scrnum=0;scrget(3,2);z=1;
    DisplayMenuTitel(0,ptitel_,0xA);
    k=start_+1;scrifld(z++,fm_ou2,&k);
    k+=11; if(k>AantalDossiers) k=AantalDossiers;scrifld(z++,fm_ou2,&k);
    for(k=start_;k<start_+12;k++){
      if(k<AantalDossiers && TbDossiers[k].code[0]){
        scrifld(z++,fm_os3,TbDossiers[k].code);if(TbDossiers[k].dt_creatie==DatumVandaag) scrchat(z-1,0x07);
        scrifld(z++,fm_os30,TbDossiers[k].naam);if(TbDossiers[k].dt_creatie==DatumVandaag) scrchat(z-1,0x07);
	scrifld(z++,fm_odat,&TbDossiers[k].dt_creatie);if(TbDossiers[k].dt_creatie==DatumVandaag) scrchat(z-1,0x07);
        scrifld(z++,fm_odat,&TbDossiers[k].dt_archiv);if(TbDossiers[k].dt_creatie==DatumVandaag) scrchat(z-1,0x07);
       
      } else z+=4;
    }
    z_dossier_=z;
    if(mode_==0 || mode_==1){// interne kopie 
      if(FlagMultiCompany){
        scrifld(z++,fm_us3U,FromCode);
        scrifld(z++,fm_us3U,ToCode);
      }
      else{
        scrifld(z++,fm_os3,FromCode);
        scrifld(z++,fm_os3,ToCode);
      }
      scrifld(z++,fm_us6,FirmaOpmerking);
      scrifld(z++,fm_os20,OpmerkingVoorbeeld);
    }
    else if(mode_==2){
      scrifld(z++,fm_us3U,FromCode);
      scrifld(z++,fm_os3,"---");
      scrifld(z++,fm_os3,"---");
    }
    key=scrupd(curs,0xC7);curs=1;
    if(key==101) break;
    if(key==102){start_-=12; if(start_<0) start_=0;}
    if(key==103 && start_+12<AantalDossiers){start_+=12;/* if((start_+12)>AantalDossiers) start_=AantalDossiers-12;*/}
    if(start_<0) start_=0;
    if(key==102 || key==103) goto redo;
    if(FromCode[0]=='\0') {errnum=38; curs=z_dossier_;goto redo;}
    for(k=0;k<AantalDossiers;k++) if(CString(TbDossiers[k].code).CompareNoCase(FromCode)==0) break;
    if(k>=AantalDossiers) {
      errnum=34;curs=z_dossier_;goto redo;// MOET bestaan
    } 
		copy(TbDossiers[k].naam,NewFirmaName,30);
    if(mode_==0 || mode_==1){// interne kopie
      if(ToCode[0]=='\0') {errnum=38; curs=z_dossier_+1;goto redo;}
      for(k=0;k<AantalDossiers;k++) if(CString(TbDossiers[k].code).CompareNoCase(ToCode)==0) break;
      if(k>=AantalDossiers){ // bestaat niet 
        if(mode_==1){// interne kopie boekhouding 
          errnum=34;curs=z_dossier_+1;goto redo;// MOET bestaan
				}
      }
      else{
				if(mode_==0){errnum=34;curs=z_dossier_+1;goto redo;}// mag niet bestaan 
				else if(cmpstr(ToCode,FromCode,3)==0){errnum=34;curs=z_dossier_+1;goto redo;}// mag niet hetzelfde zijn
			}
      if(FirmaOpmerking[0]=='\0') {errnum=38; curs=z_dossier_+2;goto redo;}
    }
    if(key==108) return true;
  }
  return false;
}
  
static int LoadDossiers(int no_fas) 
{
 
  int j,k,n;
  CString fname_,cstr_,keystr_,skip_dos_[5];
	CFileFind finder;
	CFile cfile_;
	BOOL bWorking;
 
	for(k=0;k<5;k++) skip_dos_[k]="";
	 if(no_fas){
		 skip_dos_[0]=CString(s(25,3));
		 for(k=1;k<5;k++){
			 keystr_.Format("GetIniKeyValue|DataBaseSettings|StdDossier%d",k);
       skip_dos_[k]=JmsCmd(keystr_);
		 }
	 }
	
	for(k=0;k<DIM_DOSSIER;k++){
    zeros(TbDossiers[k].code,sizeof TbDossiers[k].code);
    zeros(TbDossiers[k].naam,sizeof TbDossiers[k].naam);
    TbDossiers[k].dt_archiv=0;
    TbDossiers[k].dt_creatie=0;
    TbDossiers[k].filename=CString("");
  }

  AantalDossiers=0;


	bWorking = finder.FindFile(FasSubDir+"SYS.*");
	while (bWorking) {
		bWorking = finder.FindNextFile();
	  if (finder.IsDirectory()) continue;
		fname_=finder.GetFileName();fname_.TrimRight();
		for(k=0;k<5;k++){
				if(skip_dos_[k].GetLength() && fname_.Right(3).CompareNoCase(skip_dos_[k])==0) break;
		}
    if(no_fas==NO || k>=5){ 
      TbDossiers[AantalDossiers++].filename=fname_;
    }
    if(AantalDossiers>=DIM_DOSSIER) break;
  }
	finder.Close();
  for(k=0;k<AantalDossiers;k++){
    j=TbDossiers[k].filename.Find('.');j++;n=0;
    for(j;j<TbDossiers[k].filename.GetLength();j++){
      TbDossiers[k].code[n++]=TbDossiers[k].filename.GetAt(j);
      if(n>3) break;
    }
		fname_=FasSubDir;fname_+=TbDossiers[k].filename;
		if(cfile_.Open(fname_,CFile::modeRead,0)){
		  cfile_.Seek(0L,CFile::begin); zeros(sys_data,sizeof sys_data);
		  cfile_.Read(sys_data,LEN_SYSDATA);
		  bcopy(&sys_data[34],TbDossiers[k].naam,30);
      TbDossiers[k].dt_creatie=*(short unsigned *)&sys_data[1766];
      TbDossiers[k].dt_archiv=*(short unsigned *)&sys_data[1858];
			cfile_.Close();
    }
  }

  return AantalDossiers;

}

static void RenameFacturen(void)  
{

  CString fname_,ft_search_,fromfile_,tofile_;
 	CFileFind finder;
	BOOL bWorking;
 
  char *ptitel_;

  ptitel_= "Hernoemen facturen naar nieuwe naam van dossier";
  
  zeros(FromCode,sizeof FromCode);zeros(ToCode,sizeof ToCode);zeros(InpJaartal,sizeof InpJaartal);
  if(LoadFacturenTabel()==0) goto endsr;
  FOREVER{
    if(ShowFacturen(0,ptitel_)==false) break;
    if(DisplayWarning("Wenst U deze facturen te hernoemen  ???",605,YES)){
      DisplayBezig("Bezig met hernoemen. Even geduld ....",0xA);
      ft_search_="";ft_search_+=FacturenDir; ft_search_+=CString(FromCode)+"*."+CString(InpJaartal)+"*";
			bWorking = finder.FindFile(ft_search_);
    	while (bWorking) {
		    bWorking = finder.FindNextFile();
	      if (finder.IsDirectory()) continue;
				fname_=finder.GetFileName();fname_.TrimRight();
        if((fname_.GetLength()==11 || fname_.GetLength()==12)  && fname_.Find('.')==8){
	        fromfile_=FacturenDir+fname_;
	        tofile_=FacturenDir+CString(ToCode)+fname_.Mid(3);
          rename(fromfile_,tofile_);
	      }
	    }
			finder.Close();
      zeros(FromCode,sizeof FromCode);zeros(ToCode,sizeof ToCode);
      if(LoadFacturenTabel()==0) break;
    } 
  }

endsr:;
}

static void DeleteOldMail(void)  
{

  CString fname_,ft_search_;
 	int16 k,jj,mm,dd,max_,key;
	uint16 dat_end=0;
	SYSTEMTIME st_,fsystime_;
	WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
  FILETIME FtimeEnd,loc_ftime_;
	 
//	FASSEN ZIJN GESLOTEN HIER !!! fileopen(7);
	scrnum=0;scrget(3,5);
	scrifld(1,fm_udat,&dat_end);
	key=scrupd(1,0x101);
	if(key!=109) goto endsr;
  if(DisplayWarning("Wenst U deze mails weg te vegen (ONHERROEPELIJK!!!) ???",605,YES)){
    DisplayBezig("Bezig met verwijderen. Even geduld ....",0xA);
		GetLocalTime(&st_);
	  jddate((int)(dat_end),&jj,&mm,&dd);
	  st_.wDay=dd;st_.wMonth=mm;st_.wYear=jj;st_.wHour=17;st_.wMinute=50;SystemTimeToFileTime(&st_,&FtimeEnd);
		ft_search_=CString("..\\Mail\\Sent\\*.*");
		hSearch = FindFirstFile (ft_search_, &FileData);
		FOREVER{

			if (hSearch == INVALID_HANDLE_VALUE) break;
			if ((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) goto nextfile;                      // geen directory 
			if (CompareFileTime(&FileData.ftLastWriteTime,&FtimeEnd)>0) {goto nextfile;} // na de gewenste periode 
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


static void DeleteFacturen(void)  
{

  CString fname_,ft_search_,fromfile_;
  CFileFind finder;
	BOOL bWorking;
 
 
  char *ptitel_;

  ptitel_= "Wegvegen verouderde facturen van computer";
  
  zeros(FromCode,sizeof FromCode);zeros(ToCode,sizeof ToCode);zeros(InpJaartal,sizeof InpJaartal);
  if(LoadFacturenTabel()==0) goto endsr;
  FOREVER{
    if(ShowFacturen(1,ptitel_)==false) break;
		if(DisplayWarning("Wenst U deze facturen weg te vegen (ONHERROEPELIJK!!!) ???",605,YES)){
      DisplayBezig("Bezig met verwijderen. Even geduld ....",0xA);
      ft_search_="";ft_search_+=FacturenDir; ft_search_+=CString(FromCode)+"*."+CString(InpJaartal)+"*";
			bWorking = finder.FindFile(ft_search_);
    	while (bWorking) {
		    bWorking = finder.FindNextFile();
	      if (finder.IsDirectory()) continue;
				fname_=finder.GetFileName();fname_.TrimRight();
        if((fname_.GetLength()==11 || fname_.GetLength()==12)  && fname_.Find('.')==8){
	        fromfile_=FacturenDir+fname_;
	        remove(fromfile_);
	      }
	    }
			finder.Close();
      zeros(FromCode,sizeof FromCode);zeros(ToCode,sizeof ToCode);
      if(LoadFacturenTabel()==0) break;
    } 
  }

endsr:;
}

static int LoadFacturenTabel(void) 
{

  int k;
  CString fname_,ft_search_,dossier_,jaartal_;
  CFileFind finder;
	BOOL bWorking;
 
  for(k=0;k<DIM_FACTUREN;k++){
    TbFacturen[k].code="";
    TbFacturen[k].jaartal="";
    TbFacturen[k].aantal=0;
  }
  AantalFacturen=0;
  if(FacturenDir.GetLength()==0) return AantalFacturen;
  k=FacturenDir.GetLength();
  ft_search_="";ft_search_+=FacturenDir; ft_search_+="*.*";
	bWorking = finder.FindFile(ft_search_);
 	while (bWorking) {
	  bWorking = finder.FindNextFile();
	  if (finder.IsDirectory()) continue;
		fname_=finder.GetFileName();fname_.TrimRight();
		if((fname_.GetLength()==11 || fname_.GetLength()==12)  && fname_.Find('.')==8){
      dossier_=fname_.Left(3);jaartal_=fname_.Mid(9,2);
      for(k=0;k<DIM_FACTUREN;k++){
  	    if((TbFacturen[k].code.CompareNoCase(dossier_)==0 && TbFacturen[k].jaartal.CompareNoCase(jaartal_)==0) || TbFacturen[k].aantal==0) break;
	    }
	    if(k<DIM_FACTUREN){
	      TbFacturen[k].code=dossier_;TbFacturen[k].jaartal=jaartal_;TbFacturen[k].aantal++;AantalFacturen++;
	    }
    }
  }
	finder.Close();
  return AantalFacturen;
}

static bool ShowFacturen(int mode_,char *ptitel_) // 0 = renamen, 1=deleten  
{

  int j,k,n,z,key,start_,curs=1,z_dossier_;
  char dossier_code_[4],jaartal_[4];


  start_=0;curs=1;
  FOREVER{
redo:;
    scrnum=0;scrget(3,4);z=1;
    DisplayMenuTitel(0,ptitel_,0xA);
    for(k=0;k<12;k++){
      for(j=0;j<3;j++){
	n=k+j*12;
        if(TbFacturen[n].aantal){
	  ZCstr2Arr(TbFacturen[n].code,dossier_code_,4);scrifld(z++,fm_os3,&dossier_code_);
	  ZCstr2Arr(TbFacturen[n].jaartal,jaartal_,3);scrifld(z++,fm_os2,&jaartal_);
	  scrifld(z++,fm_ou5,&TbFacturen[k].aantal);
	} else z+=3;
      }
    }
    z_dossier_=z;
    scrifld(z++,fm_us2U,InpJaartal);
    if(mode_==0){// renamen  
      scrifld(z++,fm_us3U,FromCode);
      scrifld(z++,fm_us3U,ToCode);
    }
    else{
      scrifld(z++,fm_us3U,FromCode);
      scrifld(z++,fm_os3,"---");
    }
    
    key=scrupd(curs,0x81);curs=1;
    if(key==101) break;
    if(InpJaartal[0]=='\0'){errnum=38;curs=z_dossier_;goto redo;}
    if(FromCode[0]=='\0') {errnum=38; curs=z_dossier_;goto redo;}
    for(k=0;k<DIM_FACTUREN;k++) {
      if(TbFacturen[k].code.CompareNoCase(FromCode)==0 && TbFacturen[k].jaartal.CompareNoCase(InpJaartal)==0) break;
    }
    if(k>=DIM_FACTUREN) {
      errnum=34;curs=z_dossier_+1;goto redo;// MOET bestaan
    } 
    if(mode_==0){// interne kopie
      if(ToCode[0]=='\0') {errnum=38; curs=z_dossier_+1;goto redo;}
      for(k=0;k<DIM_FACTUREN;k++) {
        if(TbFacturen[k].code.CompareNoCase(ToCode)==0 && TbFacturen[k].jaartal.CompareNoCase(InpJaartal)==0) break;
      }
      if(k<DIM_FACTUREN) {
        errnum=34;curs=z_dossier_+2;goto redo;// mag niet bestaan
      } 
    }
    if(key==108) return true;
  }
  return false;
}

static int16 funkdsp(int16 z,int16 h,char *ptxt,int16 lin_)
{
  int16 k;

  for(k=0;;) if(*(ptxt+k++)=='\0') break;
  fm_osdum[2]=k;
  scraddf(z,lin_,h,8); scrifld(z,fm_osdum,ptxt);
  return h+k+1;
}

static void DisplayBezig(char* tekst_, char attrib_)
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
	scrnum=0;scrget(1,170);
	scraddfield(200,beg_,12,attrib_);scrifld(200,fmt_,dsptekst_);
	scrupd(-3,0);
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
