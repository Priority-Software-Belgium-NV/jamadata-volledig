
/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "Shlobj.h"
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" char* DRK2501GetD() {return &zzvw;}
extern "C" int DirCall_DRK2215_SelectArtikel(void);
extern "C" int FtpDeleteFile(char *Server, char *User, char *PW, char *FileName);
extern "C" int FtpUploadFile(char *Server, char *User, char *PW, char *FileName);
extern "C" int FtpDownloadFile(char* buf, int buflen, char *Server, char *User, char *PW, char *FileName);
extern "C" int FtpDirectory(char* buf, int buflen, char *Server, char *User, char *PW, char *Wildcard);
extern "C" int16 Search(int stu_,int mod_);

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();
extern "C" char DRK2501dat[] = "drk2501  00:01 21/04/11 (c) Jamadata"; // programma om historieken te controleren bij installatie (+.T.4)
      // controle inlezen historiek 
#define FOREVER         while(1)
#define YES             1
#define NO              0



// h-file --------------------------------

#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_RDWR         0x0002  /* open for reading and writing */
#define O_APPEND       0x0008  /* writes done at eof */
#define O_CREAT        0x0100  /* create and open file */
#define O_TRUNC        0x0200  /* open and truncate */
#define O_EXCL         0x0400  /* open only if file doesn't already exist */
#define O_TEXT         0x4000  /* file mode is text (translated) */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */


static CString Cstring2CSV(CString string_fld_);
static void ExportArtikels2Xml(void);


static CString arr2cstr(char *ps, int max_len);
static int bcopy0(char *ps_, char *pd_, int maxlen_);
static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_);
static double String2Getal(CString S,char decim_kar);
static double String2Double(CString S){return String2Getal(S,',');}
static double String2Double(CString S,char decim_kar){ return String2Getal(S,decim_kar);}
static int String2Int(CString S){return (int)(String2Getal(S,','));}
static CString Double2String(double getal,long mode); // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
static CString Date2String(unsigned int date_,int mode_);
static double Round(double getal, double round);
static CString Read_Rec(int f_nr_);
static CString Rec_Ele(CString s, int kol_, char delim_kar_);


static void ConvertSta2His(void);
static bool FasFileOpen(int16 nr_);
static void GetBeginEnEindFacturen(void);
static void HistoriekJournaal(void);


// testroutines
//static void DownloadFromFtp(void);
//static void UploadToFtp(void);



// ---------------------------------------
extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();
extern uint16 datejd();

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os7[]   = {7,0x88,7,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
static char fm_us1U[]  = {7,0xC8,1,0,1,0,0};
static char fm_ul8_[]   = {6,0xD3,8,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_od7_2[]  = {6,0x95,7,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_uWHSNr[]= {9,0xC8,7,0,1,0,'0','9',0};

static int16 form_dat[8],prtnr,prmode;
static int prt2pdf;

extern "C" void DRK2501cod()
{
	int z,key;
	char choice='\0';

//	InitLoad();
	if(FasFileOpen(1)==false) goto endsr;
	if(FasFileOpen(2)==false) goto endsr;
  if(FasFileOpen(6)==false) goto endsr;
	if(FasFileOpen(13)==false) goto endsr;
  FOREVER{
    scrget(3,1);z=1;fasunlck(0);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(1,0x0401);
    if(key==101 || key==111) break;
		fasunlck(-1);
    switch(choice){
      case '1': GetBeginEnEindFacturen();break;
      case '2': HistoriekJournaal(); break;
			case 'C': if(fldlen(60,1)) ConvertSta2His(); break;
			case 'X': ExportArtikels2Xml(); break;
			//case 'D': DownloadFromFtp(); break;
			//case 'U': UploadToFtp(); break;
      default : errnum=34; break;
    }
  }
	endsr:;
  ovlexit(-1); 
}

//static void DownloadFromFtp(void)
//{
//	int k;
//	CString cmd_,cstr_;
//	char buf_[2000],server_[20],user_[10],pw_[10];
//
//	//cmd_ = "FtpDirectory|"; cmd_+="users.telenet.be/setup*.*"; cmd_+="|";
//	//cmd_+="w486229"; cmd_+="|"; cmd_+="PnSU94";
//	//cstr_=JmsCmd(cmd_);
//	//sprintf_s(buf_,sizeof buf_,"%s",cstr_);
//
//	//cmd_ = "FtpDelete|"; cmd_+="users.telenet.be"; cmd_+="|";
//	//cmd_+="w486229"; cmd_+="|"; cmd_+="PnSU94"; cmd_+="|";
//	//cmd_+="Articles.xml";
//	//cstr_=JmsCmd(cmd_);
//
//	//cmd_ = "FtpDownload|"; cmd_+="users.telenet.be"; cmd_+="|";
//	//cmd_+="w486229"; cmd_+="|"; cmd_+="PnSU94"; cmd_+="|";
//	//cmd_+="petitie.gif";
//	//cstr_=JmsCmd(cmd_);
//
//	k=FtpDeleteFile("users.telenet.be", "w486229", "PnSU94", "CocaCola.txt");
//  k=FtpUploadFile("users.telenet.be", "w486229", "PnSU94", "CocaCola.txt");
//  k=FtpDownloadFile(buf_,sizeof buf_, "users.telenet.be", "w486229", "PnSU94", "CocaCola.txt");
//  k=FtpDirectory(buf_,sizeof buf_, "users.telenet.be", "w486229", "PnSU94", "*.*");
//
//
//
//}
//
//static void UploadToFtp(void)
//{
//	CString cmd_,cstr_;
//
//	cmd_ = "FtpUpload|"; cmd_+="users.telenet.be"; cmd_+="|";
//	cmd_+="w486229"; cmd_+="|"; cmd_+="PnSU94"; cmd_+="|";
//	cmd_+="Articles.xml";
//	cstr_=JmsCmd(cmd_);
//}


static void ExportArtikels2Xml(void)
{
  char buf_[100];
  int i;
	uint16 rec6_;
	double prx_[4]; 
	CString cstr;
	CMarkup ArtXml;
	 
	seldata.prx_klt=0;
	seldata.selp_use=NO;
	if(ovlcall(2215,2)) goto endsr;

	ArtXml.AddElem("Articles");
  ArtXml.IntoElem();
	fasinit(6);
	FOREVER{
next6:;
		if(faskeyi(6,2,2)) break;
		if(DirCall_DRK2215_SelectArtikel()==NO) goto next6;
		rec6_=*u(6,1);zero((char *)&prx_[0],sizeof prx_);
		prx_[0]=*f(6,25);prx_[1]=*f(6,26);
    if(*s(6,41)){
      *u(6,1)=0;
      copy(s(6,41),s(6,2),fldlen(6,2));
      faskeyi(6,1,0); prx_[2]=*f(6,25);
      *u(6,1)=rec6_;fasgeti(6);
    }
    if(*s(6,44)){
      *u(6,1)=0;
      copy(s(6,44),s(6,2),fldlen(6,2));
      faskeyi(6,1,0);prx_[3]=*f(6,25);
      *u(6,1)=rec6_;fasgeti(6);
    }
		fasinit(52);*u(52,1)=*u(6,9);fasgeti(52);
		ArtXml.AddElem("Art"); // in artikel
			ArtXml.IntoElem();
			zero(buf_,sizeof buf_);copy(s(6,2),buf_,fldlen(6,2)); ArtXml.AddElem("ArticleID",buf_);
			zero(buf_,sizeof buf_);copy(s(6,3),buf_,fldlen(6,3)); ArtXml.AddElem("Description",buf_);
			zero(buf_,sizeof buf_);copy(s(6,73),buf_,fldlen(6,73)); ArtXml.AddElem("ExtraInfo",buf_);
  		cstr.Format("%.2f",prx_[0]); ArtXml.AddElem("Price",cstr);
  		cstr.Format("%.2f",prx_[1]); ArtXml.AddElem("PricePc",cstr);
  		cstr.Format("%.2f",prx_[2]); ArtXml.AddElem("Empties",cstr);
  		cstr.Format("%.2f",prx_[3]); ArtXml.AddElem("EmptiesPc",cstr);
			cstr.Format("%.2f",*f(6,28)); ArtXml.AddElem("VatPct",cstr);
			cstr.Format("%.2f",*f(6,31)); ArtXml.AddElem("PcInCrate",cstr);
			cstr.Format("%02i",*u(52,1)); ArtXml.AddElem("GroupNr",cstr);
			zero(buf_,sizeof buf_);copy(s(52,14),buf_,fldlen(52,14)); ArtXml.AddElem("GroupName",buf_);
			cstr.Format("%.2f",*f(6,37)); ArtXml.AddElem("Volume",cstr);
			cstr.Format("%.2f",*f(6,38)); ArtXml.AddElem("Weight",cstr);
			cstr.Format("%.2f",*f(6,33)); ArtXml.AddElem("Stock",cstr);
			cstr.Format("%.2f",*f(6,35)); ArtXml.AddElem("NormalStock",cstr);
			zero(buf_,sizeof buf_);copy(s(6,70),buf_,fldlen(6,70)); ArtXml.AddElem("Ean",buf_);
			zero(buf_,sizeof buf_);copy(s(6,71),buf_,fldlen(6,71)); ArtXml.AddElem("EanPc",buf_);
		ArtXml.OutOfElem(); // uit artikel
	}
	ArtXml.OutOfElem(); // Articles
  i=ArtXml.Save("Articles.XML");
endsr:;
}

static void ConvertSta2His(void)
{
	uint16 n,g,k,key,dt_;
	int16 jaartal,dd,mm;  
	long lbd_;
	  
	if(fldlen(60,1)==0) goto endsr;
	if(FasFileOpen(14)==false) goto endsr;

	dt_=*u(25,2);
	jddate(dt_,&jaartal,&mm,&dd);
	FOREVER{
		redo:;
		scrget(3,4);
		scrifld(1,fm_uu4,&jaartal);
		key=scrupd(1,0x9);
		if(key==101) goto endsr;
		if(jaartal==0) {errnum=38;goto redo;}
		if(key==104) break;
	}
  fasunlck(-2);
	fasinit(60);
  n=0;scrget(1,7);scrupd(-3,0);
  FOREVER{
		next:;
    *u(60,1)=++n;
    g=fasgetu(60);
    if(g==47)break;
    if(g!=46){
#if FLAGDU3
			if(*l(60,2)) goto next; // enkel AK
			fasinit(1);*u(1,1)=*l(60,12);if(fasgeti(1)) goto next;
#else
			fasinit(2);*u(2,1)=*l(60,2); if(fasgeti(2)) goto next;
#endif
			fasinit(6);*u(6,1)=*l(60,22); if(fasgeti(6)) goto next;
			for(k=0;k<24;k++){
				if(*f(60,82+k) || *f(60,112+k)){
		    	fasinit(16);
					if(k<12){
            *l(16,2)=(long)(jaartal)*10000+(k+1)*100+1; *u(16,3)= datejd(jaartal,k+1,1); 
						lbd_=*l(16,2);
						lbd_=*u(16,3);
					}
					else{
						*l(16,2)=(long)(jaartal-1)*10000+(k-12+1)*100+1; *u(16,3)= datejd(jaartal-1,k-12+1,1); // vorig jaar 
						lbd_=*l(16,2);
						lbd_=*u(16,3);
					}
#if FLAGDU3
			    *l(16,15)=*u(1,1);		// enkel AK
#else
					*l(16,10)=*u(2,1); if(fldlen(16,12)) *l(16,12)=*l(16,10);
#endif
					*l(16,20)=*u(6,1);
					copy(s(6,2),s(16,21),fldlen(16,21));
					copy(s(6,3),s(16,22),fldlen(16,22));
					*l(16,23)=*u(6,9);
					*f(16,24)=*f(6,28);
					copy(s(6,10),s(16,25),fldlen(16,25));
					if(fldlen(6,31)) *f(16,26)=*f(6,31); if(*f(16,26)==0) *f(16,26)=1;
					*f(16,27)=*f(6,30);
					*d(16,30)=*f(60,112+k);
					*d(16,31)=*f(60,82+k);
					*d(16,32)=*f(60,52+k);
					fasadd(16);
				}
			}
		}
	} 
endsr:;
	fasunlck(-1);
}
 

static void GetBeginEnEindFacturen(void)
{
  int z,key,k;
	uint16 jaar_;
	char str_[30];
	long ft_nr_;
	CString cstr_,line_,fname_;
  CString ft_filestring,ft_dir;
  WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
	struct{
		uint16 jaar;
		long ft_beg;
		long ft_end;
	} ft_[25];

	zero((char *)&ft_[0].jaar,sizeof ft_);
	FOREVER{
		scrget(3,2);z=1;
		for(k=0;k<20;k++){
			scrifld(z++,fm_ou2,&ft_[k].jaar);
			scrifld(z++,fm_ul8_,&ft_[k].ft_beg);
			scrifld(z++,fm_ul8_,&ft_[k].ft_end);
		}
		key=scrupd(-1,0x81);
		if(key==101) goto endsr;
		if(key==108) break;
	}
	scrget(1,7);scrupd(-3,0);
  ft_dir=CString("");
	zero(str_,sizeof str_);sysget(4704,25,str_);ft_dir+=CString(str_);
  ft_filestring=ft_dir;
	zeros(str_,sizeof str_);copy(s(25,3),str_,3);	ft_filestring+=CString(str_);ft_filestring+="*.*";

  hSearch = FindFirstFile (ft_filestring, &FileData);
  FOREVER{
    if (hSearch == INVALID_HANDLE_VALUE) break;
    if ((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) goto nextfile;                      // geen directory 
		fname_=CString(FileData.cFileName);
		if(fname_.GetLength()<11) goto nextfile;

		ft_nr_=String2Int(fname_.Mid(3,5));jaar_=String2Int(fname_.Mid(9,2));
		for(k=0;k<20;k++) if(ft_[k].jaar==jaar_ || ft_[k].jaar==0) break;
		if(k<20){
			if(ft_nr_<ft_[k].ft_beg || ft_[k].ft_beg==0) ft_[k].ft_beg=ft_nr_; 
			if(ft_nr_>ft_[k].ft_end || ft_[k].ft_end==0) ft_[k].ft_end=ft_nr_; 
			ft_[k].jaar=jaar_;
		}
nextfile:;
    if(FindNextFile (hSearch, &FileData)==false) break;
  }
  FindClose(hSearch);
	FOREVER{
		scrget(3,2);z=1;
		for(k=0;k<20;k++){
			scrifld(z++,fm_ou2,&ft_[k].jaar);
			scrifld(z++,fm_ul8_,&ft_[k].ft_beg);
			scrifld(z++,fm_ul8_,&ft_[k].ft_end);
		}
		key=scrupd(-1,0x81);
		if(key==101) goto endsr;
		if(key==108) break;
	}
		
  endsr:;
}


static void HistoriekJournaal(void)
{
  int k,z,key,mode_;
	uint16 dt_beg,dt_end,ft_date_,inq_klt=0;;
  long ft_nr_,ft_beg,ft_end;
	double ft_goed_,tot_goed_,ft_leegg_,tot_leegg_;

  ft_beg=0;dt_beg=0;ft_end=0;dt_end=0; inq_klt=0; fasinit(2);
	FOREVER{
		redo:;
		scrget(3,3);z=1;
		scrifld(z++,fm_udat,&dt_beg);scrifld(z++,fm_udat,&dt_end);
		scrifld(z++,fm_ul8_,&ft_beg);scrifld(z++,fm_ul8_,&ft_end);
		scrfld(z++,2,3);
		key=scrupd(1,0x181);
		if(key==101) goto endsr;
		if(*s(2,3)){ 
			if(Search(2,0)) goto redo;
			inq_klt=*u(2,1);
		} else inq_klt=0;
	//	prt2pdf=0; if(key==109) {prt2pdf=1;key=108;}
		if(key==108) break;
	}
	getsysprNew(5,form_dat,&prmode,&prtnr); PrintPaperNr=0; // pdf
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,96,prmode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prttext("<b>Historiekenjournaal<b>");
  prttext("   Periode : ");
  prtifld(fm_udat,&dt_beg,-1);prttext(" t.e.m. ");prtifld(fm_udat,&dt_end,-1);
  prttext("<t72>");prttext("Blz.<ppp>.");
  prtbuf(1);z=1;
  prtitab(z,fm_ul8_,&ft_nr_,1,-1); prttitle(z++,"Factuur",3);
	prtitab(z,fm_udat,&ft_date_,1,-1); prttitle(z++,"Datum",3);
  prttab(z,2,3,1,-1); prttitle(z++,"Klant",3);
  prtitab(z,fm_od7_2,&ft_goed_,1,-1); prttitle(z++,"Goederen",0x13);
  prtitab(z,fm_od7_2,&ft_leegg_,1,-1); prttitle(z++,"Leeggoed",0x13);
  prtbuf(3);

  scrget(1,7);scrupd(-3,0);
	ft_nr_=0;ft_goed_=0;ft_leegg_=0;tot_goed_=0;tot_leegg_=0;fasinit(2);ft_date_=0;
	fasinit(16);*l(16,2)=ft_beg;mode_=1;
	FOREVER{
		next:;
		if(faskeyi(16,3,mode_)) break; mode_=2;
		if(ft_end && *l(16,3)>ft_end) break;
		if(*u(16,3) <dt_beg) {*u(16,3)=dt_beg;mode_=1; goto next;}
    if(*u(16,3) >dt_end) {*u(16,3)=0xFFFF; mode_=2;goto next;}
		if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
		if(inq_klt && *l(16,10)!=inq_klt) goto next;
		if(*l(16,2)!=ft_nr_){
			if(ft_nr_!=0) {for(k=1;k<20;k++) prtinfo(k,0);prtline();}
			ft_goed_=0;ft_leegg_=0;ft_nr_=*l(16,2);ft_date_=*u(16,3);
			fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
		}
		if(*l(16,23)==99){tot_leegg_+=*d(16,31); ft_leegg_+=*d(16,31);}
		else {tot_goed_+=*d(16,31); ft_goed_+=*d(16,31);}
	}
	if(ft_goed_ || ft_leegg_){
		if(ft_nr_!=0) {for(k=1;k<20;k++) prtinfo(k,0);prtline();}
	}
	fasinit(2);copy("Totaal",s(2,3),10);ft_nr_=0;ft_date_=0;ft_goed_=tot_goed_;ft_leegg_=tot_leegg_;
	prtline();for(k=1;k<20;k++) prtinfo(k,2);prtline();
	prtclose();

endsr:;
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

static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_)
{
  int len_;

  if(cstr_.GetLength()) len_=cstr2arr(cstr_,pbuf_,maxlen_);
  else len_=0;
  if(len_>=maxlen_) len_--; pbuf_[len_]='\0'; 

  return pbuf_;
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
 
