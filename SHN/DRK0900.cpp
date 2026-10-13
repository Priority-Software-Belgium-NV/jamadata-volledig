
/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "Shlobj.h"
#include <direct.h>
#include <fstream>
extern "C" char* DRK0900GetD() {return &zzvw;}

extern "C" void SvcErr(int nr, char *text);
extern "C" int Fld2String(int stunr, int fldnr, char *OutBuffer, int MaxLen);
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

 


extern "C" char DRK0900dat[] = "drk0900  00:01 02/05/12 (c) Jamadata";
      // koppelingsmodule met kassa (facturatie/klantenkaarten)
      // PAS OP : indien facturatie, dan moet er ook de ovl0941 zijn (=ovl0240 met par0941) en upsys kassys.dat i 3612 8 !!
      // PAS OP : indien bons, dan moet er ook de ovl0944 zijn (=ovl0240 met par0944) !!
      // PAS OP : indien KLANTENKAARTEN : - verkopen inlezen tot zover mogelijk (=verkoop klantenkaart bijwerken)
      //                                  - SYS3772 aanpassen (bit 0 op 1 zetten=GEEN bijwerking klantenkaart in ovl0290) !!!
      //                                  - de punten van kassa inlezen in fas (punt V.2.9.+ en dan verborgen F10 nemen (=kassa 1!))
      //                                  - We voegen het blokje kltkrt toe.(via kaskeys)
      //                                  - upsys kassys.dat i 3280 0    	(dit zijn het aantal klanten, maar dat 							gaat nu via de JMD!)
			//				  													upsys kassys.dat s 3648 6 *****  (uniek IDnummer (zie V.2.9.+)
			//			  														upsys kassys.dat f 3636 100      (% punten)
			//		  															upsys kassys.dat f 3640 500      (punten volle kaart )
			//	  																upsys kassys.dat f 3644 5        (waarde volle kaart)
			//  																	upsys kassys.dat i 3654 8        (Dit is waar hij de file moet halen, 8 							is via JMD)

// Testen van deze module met kassa 
// eventueel kassa-data van klant nemen en kopieren in ..\kassa (kassys....)
// kassa-programma op ..\kassa starten met "kassa #" (echte windowsbox)
// project instellingen aanpassen : Properties --> debugging --> aruguments 1 1 in 1 4 aanpassen 
// programma opstarten : +t3900^6C (eventueel in werkpost scherm 4 zetten)

#define FOREVER         while(1)
#define YES             1
#define NO              0

extern char *s();
extern int16 *i();
extern float *f();
extern uint16 *u();
extern long *l();
extern double *d();
// h-file --------------------------------

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us62[]  = {7,0xC8,62,0,0,0,0};
static char fm_os56[]  = {7,0x88,56,0,0,0,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};


  
static void FillAndCalculate_Bon_Factuur(int doctype_,int execmode_);
static void SetExitFlag(int flag_);
static void ram2stu(int16 lin_);
static void stu2ram(int16 lin_);



static CString arr2cstr(char *ps, int max_len);
static int bcopy0(char *ps_, char *pd_, int maxlen_);
static int copy0(char *ps,char *pd,int max);
static void Double2Text(double getal, char *s, int len, char points, int digits);
static void EncryptStr(char *ps_,int maxlen_);
static void fileopen(int16 nr_);
static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_);
static CString Date2String(unsigned int date_,int mode_);
static int get_contr(int16 keynr_);
static void get_prx(void);
static double Round(double getal, double round);
static double str2dbl(char *s);
static double str2dbl(CString cstr) {return str2dbl((char *)(LPCTSTR)cstr);};
static CString Fld2CString(int stu_,int fld_);
static void GetKlantenkaartInfo(void);
static void GetArtPrijsVanKlant(void);
static void UpdateKlantenkaartPunten(void);

static unsigned char GetStringBuf[500]; // zie hieronder
static char* GetString(int stunr, int fldnr, bool JamasciDecodeFlag=false, int MaxLen=500);


static CMarkup KassaXml;
   
static bool ReadEOFline,SilentMode;
static char *ram,def_inc,def_ext[2],fmt[40],NaamVarBetWijze[3][20],GdateSexFromEid,CheckPeppolKlant;
static long ram_size;
static int16 stu58_len,max_line,def_qfact,lvcd,klcd,prxnr,sys4408;
static uint16 ft_date,sys3894;
static float def_btw;
static int LastKrtNr;

static float brij_tpct,brij_tbd;
static float calc_prx,calc_kort,calc_sem,hl_korting,hl_semkort,ft_hlkorting,ft_semhlkorting,directpc,semestpc;
static uint16 newkort,nokort,UseAKPrijs;
static double prx_afrond;
///////////////// stuk van Marc ///////////////////////////////



static void scraddkey(int fld,int h,int v, int xlen, int ylen, int keynumb, char *text, COLORREF rgb)
{
  char fmKey[]  = {11,0x09,30,0,0,0,0,0,0,0,0};
  scraddfield(fld,h,v,0);
  fmKey[4]=xlen; fmKey[5]=ylen;
  fmKey[6]=keynumb%256; fmKey[7]=keynumb/256;
  fmKey[8]=rgb%256; fmKey[9]=(rgb/256)%256; fmKey[10]=(rgb/65536)%256;
  scrifld(fld,fmKey,text);
}

static void scraddpanel(int fld,int h,int v, int xlen, int ylen, int style, COLORREF rgb)
{
  char fmPanel[]  = {10,0x0A,30,0,0,0,0,0,0,0};
  scraddfield(fld,h,v,0);
  fmPanel[4]=xlen; fmPanel[5]=ylen; fmPanel[6]=style;
  fmPanel[7]=rgb%256; fmPanel[8]=(rgb/256)%256; fmPanel[9]=(rgb/65536)%256;
  scrifld(fld,fmPanel,"");
}


#define KLEUR_FTOETS        RGB(0,127,0)
#define KLEUR_GRIJS         RGB(200,200,200)
#define KLEUR_TEDOEN        RGB(250,0,50)
#define KLEUR_VERWERKT      RGB(0,220,100)
#define KLEUR_PDA_ARTIKEL   RGB(250,100,100)
#define KLEUR_PDA_KLANT     RGB(50,175,150)
#define KLEUR_TITEL         RGB(255,200,100)
#define KLEUR_GROEN         RGB(0,220,100)
#define KLEUR_CYAAN         RGB(50,200,200)
#define KLEUR_ROOD          RGB(220,50,50)
#define KLEUR_OUDROOD       RGB(250,100,0)
#define KLEUR_GEEL          RGB(255,255,0)
#define KLEUR_LICHTBLAUW    RGB(200,250,225)

#define FACTUUR		0
#define LEV_BON		1

#define MAX_SEARCH_KEYWORDS  10
#define MAX_FIELDS     300/* maximum number of fields in 1 structure */
#define PROC_SEND2PEER WM_USER+2
#define MAX_FIND_PAGES 100
#define MAX_FIND_LINES 24

char SearchKeywords[MAX_SEARCH_KEYWORDS][100];
static char ICSBTab[256];
static char KasMsgData[1001],PrevKasMsgData[1001];
CString PathSpoolToPeer, PathSpoolReceived, Kas2JmcFilename, Jmc2KasFilename;



static void DispWaitScreen()
{
  scrnum=0;
  scrget(1,7);
  //scraddpanel(1,19,7,37,8,PANEL_WITH_EDGE,0xFFFFFF);
}

static void InitPath()
{
  char buf[MAX_PATH+10];

	_getcwd(buf,MAX_PATH);
	if (JMC4TEST) {
		PathSpoolReceived="..\\KASSA\\";
		PathSpoolToPeer="..\\KASSA\\";
	}
	else {
		PathSpoolToPeer=buf;
		PathSpoolToPeer=PathSpoolToPeer.Left(PathSpoolToPeer.GetLength()-4) + "Spool\\";  // strip prog of work
		CreateDirectory(PathSpoolToPeer,NULL);
		PathSpoolToPeer+="ToClient\\";
		CreateDirectory(PathSpoolToPeer,NULL);
		PathSpoolToPeer.Format("%sPOST-%03d\\",PathSpoolToPeer,1+(procid/5));
		CreateDirectory(PathSpoolToPeer,NULL);
   
		PathSpoolReceived=PathSpoolToPeer;
		PathSpoolReceived.Replace("ToClient","Received");
		CreateDirectory(PathSpoolReceived,NULL);
	}
		
  Kas2JmcFilename.Format("%sKas2Jmc%d.jam",PathSpoolReceived,procid%5); 
  Jmc2KasFilename=PathSpoolToPeer+"Jmc2Kas.jam";
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

static int MakeFullRecDens(int stunr, char* FullRecDens)
{
  unsigned char Desc[100]; // zeker genoeg nemen,
  unsigned char *p=0;
	char  *d;
  int len, outlen=0, lenadd,fldnr;
  d=FullRecDens;
	int SearchFldNrs[2][15]={1,2,3,4,5,6,7,8,9,10,21,22,68,0,0,   // 0 = stu2, 1=stu 92
	                         1,2,3,4,5,6,7,8,9,10,11,0,0,0,0};

  for (int snr_=0; snr_<15; snr_++) {
		if(stunr==92) fldnr=SearchFldNrs[1][snr_]; else fldnr=SearchFldNrs[0][snr_];
		if(fldnr==0) continue;
		if(fldnr==1 && fldlen(stunr,2)) continue; // indien code, dan geen recordnummer
    len=fieldspc(stunr,fldnr,&p,Desc);
    if (len==0) continue;
		GetString(stunr,fldnr,false);
		len= strlen((char *)GetStringBuf);
 		lenadd=GetSearchText((char *)GetStringBuf,d,len);
    if (lenadd>0) {
      d+=lenadd;
      *d++=0;
      outlen+=(lenadd+1);
    }
  }
  *d++=0;
  return outlen;
}

static bool AllKeywordsFound(char* FullRecDens, int FullRecDensLen)
{
  int i, j, k, KeyWordLen;
  
  for (i=0; i<MAX_SEARCH_KEYWORDS; i++) {
    KeyWordLen=strlen(SearchKeywords[i]);
    if (KeyWordLen==0) continue;
    if (FullRecDensLen<KeyWordLen) return false;

    for (j=0; j<FullRecDensLen-KeyWordLen; j++) {
      for (k=0; k<KeyWordLen; k++) {
        if (SearchKeywords[i][k]!=FullRecDens[j+k]) break;
      }
      if (k>=KeyWordLen) break;
    }
    if (j>=FullRecDensLen-KeyWordLen) return false;
  }
  return true;
}

static void GetSearchKeyWords(char* s)
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

static void NotifyJMH()
{
  CString Cmd;
  Cmd.Format("GetJmhWnd-%03d",1+(procid/5));
  CString Rep=JmsCmd(Cmd);
  if (Rep.GetLength()==8) {
    HWND JmhWnd;
    sscanf_s(Rep,"%x",&JmhWnd,sizeof(HWND));
    SendMessage(JmhWnd,PROC_SEND2PEER,0,0);
  }
}

//unsigned char GetStringBuf[500]; // zie hieronder
static char* GetString(int stunr, int fldnr, bool JamasciDecodeFlag, int MaxLen)
{
  int i;
  unsigned char Desc[100]; // zeker genoeg nemen,
  unsigned char *p, *b;
  int len=fieldspc(stunr,fldnr,&b,Desc);
	CString cstr_;
	  
  p=GetStringBuf;
  *p=0;
  if (len && (Desc[1]&0xC0)!=0) {
    switch (Desc[1]&0x38) {
      case 0x10: // getal
        frmtnum((char *)GetStringBuf,Desc[1],d(stunr,fldnr),Desc[2],Desc[3],*(UNALIGNED short int *)&Desc[4]);
        //len=strlen((char *)GetStringBuf);
        //while (len>0) {
        //  if (GetStringBuf[len-1]>' ') break;
        //  GetStringBuf[len-1]=0;
        //  len--;
        //}
        //for (i=0; i<len; i++) if (GetStringBuf[i]>' ') break;
        //if (i>0) memmove(GetStringBuf,&GetStringBuf[i],len-i+1);
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
	cstr_=CString(GetStringBuf);  cstr_.Trim(); zero((char *)GetStringBuf,sizeof GetStringBuf); for(i=0;i<cstr_.GetLength();i++) GetStringBuf[i]=cstr_.GetAt(i);
  return (char *)GetStringBuf;
}

static void ExportKlt2XML(int RecNr,int DocType) // 1=factuur, 2=leveringsbon
{
  CMarkup Klt;
  int k,stunr=2;
	char sys3896[6];
  unsigned char *p=0;
  CString FldNr;
  CString ExpFields="F1,F2,F3,F4,F5,F6,F8,F10,F26,F89,XX";

	if(DocType==1 && ovltest(941)==0) DocType=2; // indien enkel leveringsbons
  if (RecNr>0) {
    *u(2,1)=RecNr;
    fasgeti(2);
		if(DocType==FACTUUR && ovltest(2240) && CheckPeppolKlant=='J' && fldlen(2,128) && *s(2,128)!='P' && *l(2,10)!=999999999 && *l(2,10)!=0){ // automatisch versturen via pweppol indien geregistreerd
			if(ovlcall(2240,20)>0){*s(2,128)='P'; fasupd(2);}
		}
		Klt.AddElem("DocType",DocType);  // bon of factuur
    Klt.AddElem("Klant");
    Klt.IntoElem();
    for (int fldnr=1; fldnr<=MAX_FIELDS; fldnr++) {
      FldNr.Format("F%d,",fldnr);
      if (ExpFields.Find(FldNr)<0) continue;
			if(fldnr==3 && *(s(2,3)+fldlen(2,3)-1)=='!'){ // ! laten aansluiten op naam 
				for(k=0;k<fldlen(2,3);k++) if(*(s(2,3)+k)=='\0') break;
				if(k<fldlen(2,3)-1) {*(s(2,3)+k)='!';*(s(2,3)+k+1)=0;}
			}
			if(fldnr==26){ // prijstype converteren naar kassa-type
				sysget(3896,6,&sys3896[0]);
			  for(k=0;k<6;k++) if(*s(2,26)==sys3896[k] && sys3896[k]!='\0') break;
        if(k>=6) *s(2,26)='0'; else *s(2,26)=k+'0';
			}
      FldNr=FldNr.Left(FldNr.GetLength()-1);
      Klt.AddElem(FldNr,GetString(2,fldnr,false));
    }
  }
  else {
    Klt.AddElem("Dummy",0);
  }
  Klt.Save(Jmc2KasFilename);
  NotifyJMH();
}

static void KeyFindKlant()
{
  ConStyle(CON_STYLE_NOBACKGROUND); 
  scrget(1,7);
  char SearchField[200], SearchFieldPrev[200], SearchFieldDens[200], NameFieldDens[200],buf1000[1000];
  char FullRecDens[3000];
  int FullRecDensLen=0,groep_;
  memset(SearchField,0,sizeof SearchField); memset(SearchFieldPrev,0,sizeof SearchFieldPrev); // Jaak
  int j,k,z,doctype_,key,curs=1, is=0, errnr, mode, RecsOnScreen=0,RecNr=0;
  bool WildZoek=false;
  long RecNrPage[MAX_FIND_PAGES];
  long RecNrLine[MAX_FIND_LINES];
  long TbDiversArtikel[10]; // divers artikel per mogelijk BTW%

  memset(RecNrPage,0,sizeof(RecNrPage));
	sysget(1317, 1, &CheckPeppolKlant);
	// controle hier niet mogelijk omwille geen detail van ticket hier
	//sysget(2900,40,(char *)&TbDiversArtikel[0]); // zie parameters V.2.+
	//if(TbDiversArtikel[8]==0){
	//	KassaXml.ResetPos();
 // 	if(KassaXml.FindElem("Detail")==false) goto do_select;
 // 	KassaXml.IntoElem();
	//  KassaXml.ResetMainPos();j=0;
	//	FOREVER{
	//		if(KassaXml.FindElem("L")==false) break;
	//		KassaXml.IntoElem();
	//			KassaXml.ResetMainPos();groep_=atoi(KassaXml.FindGetData("G"));
	//			if(groep_==1040){// verkoop cadeaubon enkel als defaultrekening 8 is ingevuld
	//				DisplayWarning("Cadeaubonnen kunnen hier NIET gefactureerd worden, maak deze op PC",605,0);
	//				RecNr=0; doctype_=2;goto endsr;
	//			}
	//		KassaXml.OutOfElem();
	//	}
	//}

do_select:;
  FOREVER {
  redo:;
    scrget(1,7);
    cls();
    int fldnr=1;
    // eerst inputfield adden
    scraddfield(fldnr,8,0,0);   
    scrifld(fldnr++,fm_us62,SearchField);
    // dan resultlijnen added (allemaal met zelfde formaat en zelfde x-pos
    if (is==0 || RecNrPage[is]>0) {
      fasinit(2);
      if (RecNrPage[is]) {
        mode=-1; // fictief om te zeggen dat we fasgeti deden
        *u(2,1)=RecNrPage[is];
        errnr=fasgeti(2);
      }
      else if (WildZoek || SearchField[0]=='\0') {
        mode=1;
        *u(2,1)=0;
        sprintf_s(s(2,3),fldlen(2,3)," ");
        errnr=faskeyi(2,2,mode); // neem de eerste (alfabetisch)
      }
      else {
				if(SearchField[0]>='0' && SearchField[0]<='9'){ // zoek op code/record
  				if(fldlen(2,2)){
						copy(SearchField,s(2,2),fldlen(2,2)); mode=-2;
						errnr=faskeyi(2,1,0);
					}
					else{
						*u(2,1)=val(SearchField);mode=-2;
						errnr=fasgeti(2);
					}
				}
				else{
          mode=5;
          sprintf_s(s(2,3),fldlen(2,3),SearchField);
					FOREVER{
            errnr=faskeyi(2,2,mode);
						if(errnr) break;
						if(fldlen(2,200)==0 || *u(2,200)==0) break;
						mode=2;
					}
				}
      }
    }
    RecsOnScreen=0;
    memset(RecNrLine,0,sizeof(RecNrLine));
    for (int line=0; line<MAX_FIND_LINES; line++ ) {
      if (errnr) {
        if (mode==-1) {
          memset(RecNrPage,0,sizeof(RecNrPage));
          goto redo;
        }
        break;
      }
      if (WildZoek  || SearchField[0]=='\0') {
        FOREVER {
          FullRecDensLen=MakeFullRecDens(2,FullRecDens);
          if ((fldlen(2,200)==0 || *u(2,200)==0) && AllKeywordsFound(FullRecDens,FullRecDensLen)) break; // record voldoet
          mode=2;
          errnr=faskeyi(2,2,mode);
          if (errnr) break;
        }
        if (errnr) break;
      }
      else {
				if(mode==-2){ // via code of record
					if(errnr) break;
				}
				else { // via naam 
          GetSearchText(s(2,3),NameFieldDens,fldlen(2,3));
          NameFieldDens[strlen(SearchFieldDens)]=0;
          if (strcmp(NameFieldDens,SearchFieldDens)!=0) break;
				}
      }
      if (line==0) {
        RecNrPage[is]=*u(2,1);
        
        if (is<MAX_FIND_PAGES-1) RecNrPage[is+1]=0; // om gewoon verder te zoeken volgende keer !
      }
      RecNrLine[line]=*u(2,1);
      scraddfield(fldnr,8,1+line,0);
      char bufline[300]; bufline[0]=0;
      strcat(bufline,GetString(2,3)); strcat(bufline," - ");
      strcat(bufline,GetString(2,4)); strcat(bufline," - ");
      strcat(bufline,GetString(2,6));
      bufline[56]=0;
      scrifld(fldnr++,fm_os56,bufline);if(*(s(2,3)+fldlen(2,3)-1)=='!') scrchat(fldnr-1,0xB); else scrchat(fldnr-1,0xFF);
      RecsOnScreen++;
      mode=2;
			FOREVER{
        errnr=faskeyi(2,2,mode);
				if(errnr) break;
				if(fldlen(2,200)==0 || *u(2,200)==0) break;
			}
    }

    // dan rest adden
    // panel adden
    // keys adden (local werken)
    // functie toetsen (maar zonder F8 te tonen)

    char cb[2];
    cb[0]='A'; cb[1]=0;
    for (char c=0; c<28; c++) {
      if (c==27) {
        scraddkey(fldnr++,64+(c%4)*4,1+2*(c/4),4,2,2303,"Wis",KLEUR_FTOETS);
      }
      else {
        if (c==26) {
          cb[0]=' ';
          scraddkey(fldnr++,64+(c%4)*4,1+2*(c/4),8,2,2000+cb[0],"Spatie",0);
          break;
        }
        scraddkey(fldnr++,64+(c%4)*4,1+2*(c/4),4,2,2000+cb[0],cb,0);
        cb[0]++;
      }
    }
    scraddkey(fldnr++,64,15,4,2,2304,"INS",KLEUR_FTOETS);
    scraddkey(fldnr++,68,15,4,2,2305,"DEL",KLEUR_FTOETS);
    scraddkey(fldnr++,72,15,8,2,2303,"Wissen",KLEUR_FTOETS);
    cb[0]='0';
    for (char c=0; c<16; c++) {
      if (c==12) {
        cb[0]='0';
        scraddkey(fldnr++,64+(c%4)*4,17+2*(c/4),8,2,2000+cb[0],cb,0);      
        c++;
      }
      else {
        if (c==3) cb[0]='-';
        else if (c==7) cb[0]='+';
        else if (c==11) cb[0]='/';
        else if (c==14) cb[0]='.';
        else if (c==15) cb[0]='*';
        else cb[0]=0x31+c%4+(c/4)*3;
        scraddkey(fldnr++,64+(c%4)*4,17+2*(c/4),4,2,2000+cb[0],cb,0);
      }
    }

    scraddkey(fldnr++,72,0,8,1,22,"",0);

    scraddkey(fldnr++,0,0,8,3,10000+108,"Zoek\nop naam",0);
    //scraddkey(fldnr++,0,3,8,3,10000+108,"Naam",0);
		scraddpicto(9,0,0,3,8,3,112,0,4,"Uitgebreid zoeken"); 
		if(ovltest(941) && ovltest(944)){
	  	scraddkey(fldnr++,0,6,8,3,10000+107,"Maak\nFACTUUR",0);
	  	scraddkey(fldnr++,0,9,8,3,10000+106,"Maak\nBON",0);
		}
		else{
			if(ovltest(941))	scraddkey(fldnr++,0,6,8,3,10000+107,"Maak\nfactuur",0);
		  else scraddkey(fldnr++,0,6,8,3,10000+106,"Maak\nbon",0);
		}
		scraddkey(fldnr++,0,19,8,3,10000+110,"Bekijk",0);
    scraddkey(fldnr++,0,22,8,3,10000+105,"Nieuw",0);

    scraddpanel(fldnr++,8,1,56,24,PANEL_WITH_EDGE,RGB(255,200,100)); // PANEL_VER_SMALLER | PANEL_HOR_SMALLER |
    scraddpanel(fldnr++,70,0,2,1,0,RGB(255,255,255));
    if(SearchField[0]) scraddpicto(1,fldnr++,70,0,2,1,31,1,3,"Wis");
    if (is>0) scraddpicto(2,fldnr++,61,1,3,2,18,0,5,"");
    if (RecsOnScreen==MAX_FIND_LINES) scraddpicto(3,fldnr++,61,23,3,2,13,0,5,"");

    errnum=-6;
    memcpy(SearchFieldPrev,SearchField,sizeof(SearchFieldPrev));
    key=scrupd(curs,0x87FF);curs=1;
    if (key==0x00160000) break; // keyCoon 'TERUG'
    if (key==251 && fldcurs>1 && (ovltest(941)==0 || ovltest(944)==0)) break; // dubbelklik enkel indien factuur OF bon
    if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==112 && ovltest(941)){// printertest 
			memcpy(buf1000,s(2,1),fldlen(2,0)); 
			ovlcall(941,99);
			memcpy(s(2,1),buf1000,fldlen(2,0)); 
		}

		      // keys : 101 : 
			    // keys : 102 : PgUp
		      // keys : 103 : Pgdn
		      // keys : 104 : 
		      // keys : 105 : toevoegen klant
		      // keys : 106 : Bon-exit
		      // keys : 107 : Factuur-exit
		      // keys : 108 : NaamZoek
		      // keys : 109 : WildZoek
		      // keys : 110 : bekijk klant 
		      // keys : 111 : 
		      // keys : 112 : 

    if(key==5001) { // clear
      memset(SearchField,0,sizeof SearchField); memset(SearchFieldPrev,0,sizeof SearchFieldPrev);
			memset(RecNrPage,0,sizeof(RecNrPage)); is=0; WildZoek=false;
			GetSearchKeyWords(SearchField);
    }
    else if(key==5002 || key==102) { // PgUp
      is--;
      if (is<0) is=0;
    }
    else if (key==5003 || key==103) { // PgDn
      if(RecsOnScreen==MAX_FIND_LINES && is<MAX_FIND_PAGES-1) is++;
    }
		else if (key==5009) key=109; // wildzoek
    if (key==15) {
      if (WildZoek) key=109;
      else key=108;
    }
    if (strcmp(SearchField,SearchFieldPrev)!=0) { // om hem terug van voorafaan te laten zoeken
      memset(RecNrPage,0,sizeof(RecNrPage));
      is=0;
    }
    if (key==105) { // toevoegen
			fasinit(2); copy(SearchField,s(2,3),fldlen(2,3));
			ConStyle(0); cls();
			ovlcall(2921,12); // mode 12 : default kassaprijs zetten 
			ConStyle(CON_STYLE_NOBACKGROUND); cls();
      if(*u(2,1)) break;  // toevoegen gelukt
		}
    if (key==106 || key==107) {  // OK exit
      j=fldcurs;
      if (fldcurs>1 && (fldcurs-1)<=RecsOnScreen) break;
    }
    if (key==108) {  // zoek op naam
      GetSearchText(SearchField,SearchFieldDens,sizeof(SearchFieldDens));
      memset(RecNrPage,0,sizeof(RecNrPage));
      is=0;
      WildZoek=false;
    }
    if (key==109) { // wild-zoek
      GetSearchKeyWords(SearchField);
      memset(RecNrPage,0,sizeof(RecNrPage));
      is=0;
      WildZoek=true;
    }
    if (key==110) { // bekijken 
      j=fldcurs;
      if (fldcurs>1 && (fldcurs-1)<=RecsOnScreen){
				*u(2,1)=RecNrLine[fldcurs-2]; fasgeti(2);
				 ConStyle(0); cls();
			   ovlcall(2921,1);  
			   ConStyle(CON_STYLE_NOBACKGROUND); cls();
				 curs=j;
			}
	  }
  }
  RecNr=0;
	if(key==105) RecNr=*u(2,1); // klant toegevoegd
  else if (fldcurs>1 && (fldcurs-1)<=RecsOnScreen) RecNr=RecNrLine[fldcurs-2];
	doctype_=1; if(key==106 || ovltest(941)==0) doctype_=2;  // factuur=1, bon=2
	if(RecNr && fldlen(62,1)){ // klt_memo tonen indien ingevuld
	  *u(2,1)=RecNr; fasgeti(2);
    fasinit(62);*u(62,2)=RecNr;
    if(faskeyi(62,1,0)==0){
      for(k=0;k<5;k++) if(*s(62,5+k)) break;
      if(k<5){
				FOREVER{
					scrget(2,122); z=1;
					scrofld(z++,2,3,-1);
					for(k=5;k<10;k++) scrfld(z++,62,k);
					key=scrupd(2,0x80);
					if(key==108) break;
				}				
				fasupd(62);
			}
    }
  }
endsr:;
	ExportKlt2XML(RecNr,doctype_);
}

static void ProcTicket()
{
  CString cstr;

}

static void KeyFindKaart(long DefKaartNr)
{
  ConStyle(CON_STYLE_NOBACKGROUND); 
  scrget(1,7);
  char SearchField[200], SearchFieldPrev[200], SearchFieldDens[200], NameFieldDens[200];
  char FullRecDens[3000];
  int FullRecDensLen=0;
  memset(SearchField,0,sizeof SearchField); memset(SearchFieldPrev,0,sizeof SearchFieldPrev); // Jaak
  int i,key,curs=1, is=0, errnr, mode, RecsOnScreen=0;
  bool WildZoek=false;
  long RecNrPage[MAX_FIND_PAGES];
  long RecNrLine[MAX_FIND_LINES];

  memset(RecNrPage,0,sizeof(RecNrPage));
	RecNrPage[0]=DefKaartNr; if(DefKaartNr) curs=2;
  FOREVER {
  redo:;
    scrget(1,7);
    cls();
    int fldnr=1;
    // eerst inputfield adden
    scraddfield(fldnr,8,0,0);   
    scrifld(fldnr++,fm_us62,SearchField);
    // dan resultlijnen added (allemaal met zelfde formaat en zelfde x-pos
    if (is==0 || RecNrPage[is]>0) {
      fasinit(92);
      if (RecNrPage[is]) {
        mode=-1; // fictief om te zeggen dat we fasgeti deden
        if (fldlen(92,1)==4) *l(92,1)=RecNrPage[is];
        else *u(92,1)=RecNrPage[is];
        errnr=fasgeti(92);
      }
      else if (WildZoek || SearchField[0]=='\0') {
        mode=1;
        if (fldlen(92,1)==4) *l(92,1)=0;
        else *u(92,1)=0;
        sprintf_s(s(92,3),fldlen(92,3)," ");
        errnr=faskeyi(92,2,mode); // neem de eerste (alfabetisch)
      }
      else {
				if(SearchField[0]>='0' && SearchField[0]<='9'){ // zoek op code/record
          if(fldlen(92,2)){
            copy(SearchField,s(92,2),fldlen(92,2)); mode=-2;
            errnr=faskeyi(92,1,0);
          }
          else{
            *u(92,1)=val(SearchField);mode=-2;
            errnr=fasgeti(92);
          }
        }
        else{
          mode=5;
          sprintf_s(s(92,3),fldlen(92,3),SearchField);
          errnr=faskeyi(92,2,mode);
				}
      }
    }
    RecsOnScreen=0;
    memset(RecNrLine,0,sizeof(RecNrLine));
    for (int line=0; line<MAX_FIND_LINES; line++ ) {
      if (errnr) {
        if (mode==-1) {
          memset(RecNrPage,0,sizeof(RecNrPage));
          goto redo;
        }
        break;
      }
      if (WildZoek  || SearchField[0]=='\0') {
        FOREVER {
          FullRecDensLen=MakeFullRecDens(92,FullRecDens);
          if (AllKeywordsFound(FullRecDens,FullRecDensLen)) break; // record voldoet
          mode=2;
				  next_faskey92:;
          errnr=faskeyi(92,2,mode);
          if (errnr) break;
					if(cmpstr(s(92,3),"XYZ",3)==0) goto next_faskey92; // lege kaarten overslaan
        }
        if (errnr) break;
      }
      else {
				if(mode==-2){ // via code of record
          if(errnr) break;
				}
        else { // via naam 
          GetSearchText(s(92,3),NameFieldDens,fldlen(92,3));
          NameFieldDens[strlen(SearchFieldDens)]=0;
          if (strcmp(NameFieldDens,SearchFieldDens)!=0) break;
				}
      }
      if (line==0) {
        if (fldlen(92,1)==4) RecNrPage[is]=*l(92,1);
        else RecNrPage[is]=*u(92,1);
        
        if (is<MAX_FIND_PAGES-1) RecNrPage[is+1]=0; // om gewoon verder te zoeken volgende keer !
      }
      if (fldlen(92,1)==4) RecNrLine[line]=*l(92,1);
      else RecNrLine[line]=*u(92,1);
      scraddfield(fldnr,8,1+line,0);
      char bufline[300]; bufline[0]=0;
      strcat(bufline,GetString(92,3)); strcat(bufline,"-");
      strcat(bufline,GetString(92,4)); strcat(bufline,"-");
      strcat(bufline,GetString(92,6));
      bufline[56]=0;
      scrifld(fldnr++,fm_os56,bufline);
      RecsOnScreen++;
      mode=2;
      errnr=faskeyi(92,2,mode);
    }

    // dan rest adden
    // panel adden
    // keys adden (local werken)
    // functie toetsen (maar zonder F8 te tonen)

    char cb[2];
    cb[0]='A'; cb[1]=0;
    for (char c=0; c<28; c++) {
      if (c==27) {
        scraddkey(fldnr++,64+(c%4)*4,1+2*(c/4),4,2,2303,"Wis",KLEUR_FTOETS);
      }
      else {
        if (c==26) {
          cb[0]=' ';
          scraddkey(fldnr++,64+(c%4)*4,1+2*(c/4),8,2,2000+cb[0],"Spatie",0);
          break;
        }
        scraddkey(fldnr++,64+(c%4)*4,1+2*(c/4),4,2,2000+cb[0],cb,0);
        cb[0]++;
      }
    }
    scraddkey(fldnr++,64,15,4,2,2304,"INS",KLEUR_FTOETS);
    scraddkey(fldnr++,68,15,4,2,2305,"DEL",KLEUR_FTOETS);
    scraddkey(fldnr++,72,15,8,2,2303,"Wissen",KLEUR_FTOETS);
    cb[0]='0';
    for (char c=0; c<16; c++) {
      if (c==12) {
        cb[0]='0';
        scraddkey(fldnr++,64+(c%4)*4,17+2*(c/4),8,2,2000+cb[0],cb,0);      
        c++;
      }
      else {
        if (c==3) cb[0]='-';
        else if (c==7) cb[0]='+';
        else if (c==11) cb[0]='/';
        else if (c==14) cb[0]='.';
        else if (c==15) cb[0]='*';
        else cb[0]=0x31+c%4+(c/4)*3;
        scraddkey(fldnr++,64+(c%4)*4,17+2*(c/4),4,2,2000+cb[0],cb,0);
      }
    }

    scraddkey(fldnr++,72,0,8,1,22,"",0);

    scraddkey(fldnr++,0,0,8,3,10000+108,"Zoek\nop naam",0);
    //scraddkey(fldnr++,0,3,8,3,10000+108,"Naam",0);
    scraddkey(fldnr++,0,3,8,3,10000+107,"OK",0);
    scraddpicto(9,0,0,6,8,3,112,0,4,"Uitgebreid zoeken"); 
    scraddkey(fldnr++,0,19,8,3,10000+110,"Bekijk",0);
    scraddkey(fldnr++,0,22,8,3,10000+105,"Nieuw",0);

    scraddpanel(fldnr++,8,1,56,24,PANEL_WITH_EDGE,RGB(255,200,100)); // PANEL_VER_SMALLER | PANEL_HOR_SMALLER |
    scraddpanel(fldnr++,70,0,2,1,0,RGB(255,255,255));
    if(SearchField[0]) scraddpicto(1,fldnr++,70,0,2,1,31,1,3,"Wis");
    if (is>0) scraddpicto(2,fldnr++,61,1,3,2,18,0,5,"");
    if (RecsOnScreen==MAX_FIND_LINES) scraddpicto(3,fldnr++,61,23,3,2,13,0,5,"");

    errnum=-6;
    memcpy(SearchFieldPrev,SearchField,sizeof(SearchFieldPrev));
    key=scrupd(curs,0x87FF);curs=1;
    if (key==0x00160000) break; // keyCoon 'TERUG'
    if (key==251 && fldcurs>1) break;
    if ((key/0x100)==1) key=(key&0xFF)+5000;

			    // keys : 101 : 
			    // keys : 102 : PgUp
		      // keys : 103 : Pgdn
		      // keys : 104 : 
		      // keys : 105 : toevoegen klant
		      // keys : 106 : 
		      // keys : 107 : OK-exit
		      // keys : 108 : NaamZoek
		      // keys : 109 : WildZoek
		      // keys : 110 : bekijk klant 
		      // keys : 111 : 
		      // keys : 112 : 

    if(key==5001) {  // clear
      memset(SearchField,0,sizeof SearchField); memset(SearchFieldPrev,0,sizeof SearchFieldPrev);
			memset(RecNrPage,0,sizeof(RecNrPage)); is=0; WildZoek=false;
			GetSearchKeyWords(SearchField);
    }
    else if(key==5002 || key==102) { // PgUp
      is--;
      if (is<0) is=0;
    }
    else if (key==5003 || key==103) { // PgDn
      if(RecsOnScreen==MAX_FIND_LINES && is<MAX_FIND_PAGES-1) is++;
    }
		else if (key==5009) key=109; // wildzoek
    if (key==15) {
      if (WildZoek) key=109;
      else key=108;
    }
    if (key==18) {
      i=fldcurs;
      if (fldcurs>1 && (fldcurs-1)<=RecsOnScreen) break;
    }
    if (strcmp(SearchField,SearchFieldPrev)!=0) { // om hem terug van voorafaan te laten zoeken
      memset(RecNrPage,0,sizeof(RecNrPage));
      is=0;
    }
    if (key==105) { // toevoegen klantenkaart 
			fasinit(92); copy(SearchField,s(92,3),fldlen(92,3));
			ConStyle(0); cls();
			ovlcall(294,2); 
			ConStyle(CON_STYLE_NOBACKGROUND); cls();
      if(*u(92,1)) break;  // toevoegen gelukt
		}
    if (key==107) {  // OK exit
      i=fldcurs;
      if (fldcurs>1 && (fldcurs-1)<=RecsOnScreen) break;
    }
    if (key==108) { // zoek op naam
      GetSearchText(SearchField,SearchFieldDens,sizeof(SearchFieldDens));
      memset(RecNrPage,0,sizeof(RecNrPage));
      is=0;
      WildZoek=false;
    }
    if (key==109) {  // wild-zoek
      GetSearchKeyWords(SearchField);
      memset(RecNrPage,0,sizeof(RecNrPage));
      is=0;
      WildZoek=true;
    }
    if (key==110) { // bekijk kaart
      i=fldcurs;
      if (fldcurs>1 && (fldcurs-1)<=RecsOnScreen){
        *u(92,1)=RecNrLine[fldcurs-2]; fasgeti(92);
        ConStyle(0); cls();
        ovlcall(294,1);  
        ConStyle(CON_STYLE_NOBACKGROUND); cls();
        curs=i;
      }
    }
  }
  int RecNr=0;
	if(key==105) RecNr=*u(92,1); // Jaak klant toegevoegd
  else if (fldcurs>1 && (fldcurs-1)<=RecsOnScreen) RecNr=RecNrLine[fldcurs-2];
  if (RecNr) {
    if (fldlen(92,1)==4) *l(92,1)=RecNr;
    else *u(92,1)=RecNr;
    fasgeti(92);
  }
  else fasinit(92);
  ConStyle(0); cls();
}


////////////////////////////////////////////////////////////////


extern "C" void DRK0900cod(int16 parmval)
{
  CMarkup Xml;
  int j,k,Status;
	char *pdum_;
  CString cstr_;
	CFile cfile_;

	if(parmval==1) SilentMode=false;
	InitPath();
  InitConvertTab();
	fileopen(2);  fileopen(6); fileopen(9); fileopen(11);
	if(fldlen(22,1)) fileopen(15);
	sysget(4408,2,&sys4408);
  fieldspc(6,21,&pdum_,fmt);
  k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;
  FOREVER {
    DispWaitScreen();
    scrupd(-1,0xFFFF);
    if (GetFileAttributes(Kas2JmcFilename)==INVALID_FILE_ATTRIBUTES) continue;

    for (int i=0; i<5; i++) {
      if (KassaXml.Load(Kas2JmcFilename)) break;
      Sleep(100);
    }
    Status=atol(KassaXml.FindGetData("Status"));
		//if(Status==11){
		//	if(cfile_.Open(Kas2JmcFilename,CFile::modeRead,0)){
		//		cfile_.Seek(0L,CFile::begin); zero(KasMsgData,sizeof KasMsgData);
		//		cfile_.Read(KasMsgData,1000);cfile_.Close();
		//		for(k=0;k<1000;k++) if(KasMsgData[k]!=PrevKasMsgData[k]) break;
		//		if(k<1000) copy(KasMsgData,PrevKasMsgData,1000);
		//		else {
		//			SvcErr(0,"Dubbele kaart-update");
		//			KassaXml.ResetPos();
		//			KassaXml = CMarkup();
  //  			SetExitFlag(1);
  //    		KassaXml.Save(Jmc2KasFilename);
		//			NotifyJMH();
  //			}
		//	}
		//}
		 
    switch (Status) {
      case 1: 
        KeyFindKlant();
        break;
      case 2: // adjust price etc. and return ticket to the kassa
			  GetArtPrijsVanKlant(); 
        break;
      case 3: // Create Invoice, print and return the info to kassa
				FillAndCalculate_Bon_Factuur(FACTUUR,1); Sleep(500);
        break;
      case 4: // Create BON, print and return the info to kassa
				FillAndCalculate_Bon_Factuur(LEV_BON,1);
        break;
      case 10: // Klantenkaart : get naam/adres en punten 
				GetKlantenkaartInfo();
        break;
      case 11: // Klantenkaart : update punten op kaart
				UpdateKlantenkaartPunten();LastKrtNr=0;
        break;
			default : break;
    }
    if (GetFileAttributes(Jmc2KasFilename)!=INVALID_FILE_ATTRIBUTES) NotifyJMH();     
		_unlink(Kas2JmcFilename);
  }
}

static int MakeAdresCmpBuffer(char* adresbuffer_)
{
  char Desc[100]; // zeker genoeg nemen,
  char *p=0, *d, cbuf_[100];
  int len, outlen=0, lenadd,k,delete_;
  d=adresbuffer_;
  for (int fldnr=4; fldnr<=6; fldnr++) {
    len=fieldspc(92,fldnr,&p,Desc);
    if (len==0) continue;
		memset(cbuf_,0,sizeof cbuf_); copy(p,cbuf_,len);delete_=NO;
		if(fldnr==4){// bij straat wordt soms de deelgemeente tussen haakjes gezet ( vb (BEL)) en die moet eruit voor vergelijking
			for(k=0;k<len;k++){
				if(cbuf_[k]=='(') delete_=YES;
				if(cbuf_[k]==')') delete_=NO;
				if(delete_) cbuf_[k]=' ';
			}
		}
    switch (Desc[1]&0x38) {
      case 0x08:  // string
        lenadd=GetSearchText(cbuf_,d,len);
        if (lenadd>0) {
          d+=lenadd;
          *d++=0;
          outlen+=(lenadd+1);
        }
        break;
    }
  }
  *d++=0;
  return outlen;
}

static void GetArtPrijsVanKlant(void) // herbereken alle prijzen van ticket
{
  int16 j,k,pos_,inc_btw_,prx_chgd_=NO,stuksflag_=NO;
  float prx_,bd_accijn,prx_in,ft_kpct;
	double prxafrond_;
  char *pdum_,str_[5];
	CString cstr_;

  fieldspc(6,21,&pdum_,fmt);
  k=fmt[3];
  prxafrond_=1.; for(j=0;j<k;j++) prxafrond_/=10.;


  ConStyle(0); cls();
	KassaXml.ResetPos();

	fasinit(2);
	KassaXml.ResetPos();
  *u(2,1)=atol(KassaXml.FindGetData("/Ticket/Klant"));
  if(*u(2,1)) fasgeti(2);
	if(*u(2,1)==0 || fasgeti(2)){SetExitFlag(0); goto endsr;} // klant moet bestaan
	sysget(3894,2,&sys3894);
  pos_=0; if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(25,2)) pos_=10;

	UseAKPrijs=NO;prxnr=0;
 	if(*s(2,26)=='A') UseAKPrijs=YES; else{prxnr=*s(2,26); prxnr=prxnr-'0';}
  if(prxnr<0 || prxnr>9) prxnr=0;
  if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
  if(!UseAKPrijs && (sys3894 & (1<<prxnr))) inc_btw_=YES; 
	else inc_btw_=NO;

	if(fldlen(2,18)) ft_kpct=*f(2,18); else ft_kpct=0;

	KassaXml.ResetPos();
	if(KassaXml.FindElem("Detail")==false) goto endsr;
	KassaXml.IntoElem();
	  KassaXml.ResetMainPos();j=0;
		FOREVER{
			next_line:;
			if(KassaXml.FindElem("L")==false) break;
			KassaXml.IntoElem();
				// KassaXml.ResetMainPos();*f(58,7)=str2dbl(KassaXml.FindGetData("A"));
			  fasinit(6);
				if(sys4408){ // code langer dan 5, dan record#
					KassaXml.ResetMainPos();
					fasinit(6);*u(6,1)=atoi(KassaXml.FindGetData("C")); if(fasgeti(6)) fasinit(6);
				}
				else{
					KassaXml.ResetMainPos();cstr2arr(KassaXml.FindGetData("C"),s(6,2),fldlen(6,2)); 
					if(faskeyi(6,1,0)) fasinit(6);
				}
				if(*u(6,1) && *i(6,9)!=99){ // niet bij leeggoed owv Tomra automaat 
					zero(str_,sizeof str_);	KassaXml.ResetMainPos();cstr2arr(KassaXml.FindGetData("S"),str_,1); 
					stuksflag_=NO; if(str_[0]=='Y') stuksflag_=YES;
					if(*f(6,31)==0) *f(6,31)=1.;// uit veiligheid
					if(*f(6,31)<=1) stuksflag_=NO; // indien artikel=fles, dan toch als bak beschouwen owv EAN op stuk gezet
					if(fldlen(2,18)) ft_kpct=*f(2,18); else ft_kpct=0;
					if(UseAKPrijs){
						if(pos_==10) calc_prx=*f(6,18+94); else calc_prx=*f(6,18);
					}
					else calc_prx=*f(6,PrNrs[pos_+prxnr]);
  	  		get_prx();
					if(ft_kpct==0 || newkort) ft_kpct=calc_kort;
					if(nokort) ft_kpct=0;
					prx_=calc_prx;
					if(inc_btw_) prx_/=1.+*f(6,28)/100.;
					bd_accijn=*f(6,30+pos_);
					if(prx_>=0){/* bedrag accijns mag niet groter zijn de ehpr */
						if(bd_accijn>prx_) bd_accijn=prx_;
					}
					else {
						bd_accijn=-bd_accijn;
						if(bd_accijn<prx_) bd_accijn=prx_;
					}
					if(ft_kpct){
						prx_=(prx_-bd_accijn)*(100.- ft_kpct)/100.+bd_accijn;
					}
					prx_-=ft_hlkorting;
					prx_in=prx_* (1.+*f(6,28)/100.);
					prx_in=Round((double)prx_in,prx_afrond);
					prx_=Round((double)prx_,prx_afrond);
					if(stuksflag_){ // indien stuks, dan enkel korting% toepassen op kassaprijs
#if FLAGCRA
						prx_in=Round((double)(prx_in/ *f(6,31)),prx_afrond); // bakprijs / stuks nemen
#else
						KassaXml.ResetMainPos(); if(KassaXml.FindElem("P")) prx_in=(float)str2dbl(KassaXml.GetData());
						if(ft_kpct){
#if FLAGVOE  // ook korting op accijns (personeel)
							prx_in=Round((double)(prx_in*(100.- ft_kpct)/100.),prx_afrond);
#else
							if(*f(6,31)>1 && bd_accijn){
								bd_accijn/=*f(6,31); 
								prx_=prx_in/ (1.+*f(6,28)/100.);
								prx_=(prx_-bd_accijn)*(100.- ft_kpct)/100. + bd_accijn;
								prx_in=prx_* (1.+*f(6,28)/100.);
								prx_in=Round((double)(prx_in),prx_afrond);
							}
							else prx_in=Round((double)(prx_in*(100.- ft_kpct)/100.),prx_afrond);
#endif
						}
#endif
					}
					KassaXml.ResetMainPos(); if(KassaXml.FindElem("P")) KassaXml.RemoveElem(); // origineel deleten en nieuwe in de plaats zetten
				  KassaXml.ResetMainPos();*f(6,21)=prx_in; KassaXml.AddElem("P",Fld2CString(6,21));
				}
			KassaXml.OutOfElem();
		}
		SetExitFlag(1);


//  *u(2,1)=atol(KassaXml.FindGetData("K"));
//	if(*u(2,1)==0 || fasgeti(2)){fasinit(2); goto dump_prijs;} 
//	if(sys4408){ // code langer dan 5, dan record#
//		KassaXml.ResetMainPos();
//		fasinit(6);*u(6,1)=atoi(KassaXml.FindGetData("C")); if(fasgeti(6)){fasinit(6);goto dump_prijs;}
//	}
//	else{
//		fasinit(6);
//		KassaXml.ResetMainPos();cstr2arr(KassaXml.FindGetData("C"),s(6,2),fldlen(6,2)); 
//		if(faskeyi(6,1,0)) {fasinit(6);goto dump_prijs;}
//	}
//	sysget(3894,2,&sys3894);
//  pos_=0; if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(25,2)) pos_=94;
//  prxnr=*s(2,26)-'0';  if(prxnr<0 || prxnr>5) prxnr=0;
//  if(fldlen(6,21+prxnr)==0) prxnr=0;
//  if(sys3894 & (1<<prxnr)) inc_btw_=YES; else inc_btw_=NO;
//	if(fldlen(2,18)) ft_kpct=*f(2,18); else ft_kpct=0;
//	calc_prx=*f(6,21+pos_+prxnr); get_prx();
//  if(ft_kpct==0 || newkort) ft_kpct=calc_kort;
//  if(nokort) ft_kpct=0;
//  prx_=calc_prx;
//  if(inc_btw_) prx_/=1.+*f(6,28)/100.;
////  prx_=Round((double)prx_,(double)(0.01));
//  bd_accijn=*f(6,30+pos_);
//  if(prx_>=0){/* bedrag accijns mag niet groter zijn de ehpr */
//    if(bd_accijn>prx_) bd_accijn=prx_;
//  }
//  else {
//    bd_accijn=-bd_accijn;
//    if(bd_accijn<prx_) bd_accijn=prx_;
//  }
//  if(ft_kpct){
//    prx_=(prx_-bd_accijn)*(100.- ft_kpct)/100.+bd_accijn;
//  }
//  prx_-=ft_hlkorting;
//  prx_in=prx_* (1.+*f(6,28)/100.);
//  prx_in=Round((double)prx_in,(double)(0.01));
//  prx_=Round((double)prx_,(double)(0.01));
//
//dump_prijs:;
//	KassaXml = CMarkup();
//	if(*u(2,1)==0 || *u(6,1)==0){ // klant of artikel niet gevonden, dat kassaprijs nemen
//		SetExitFlag(0);
//	}
//	else{
//		*f(6,21)=prx_in; KassaXml.AddElem("P",Fld2CString(6,21));
//		SetExitFlag(1);
//	}
	endsr:;
  KassaXml.Save(Jmc2KasFilename);
  NotifyJMH();
}

static void get_prx(void)
{
  int16 m,pos_;
  float kort_=0,vp_=0,k_fr_=0,acc_;
  uint16 aant_flag;
  uint16 pr_klt_;
 
  pr_klt_=*u(2,1);
  pos_=0;
  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(25,2)) pos_=10;
  newkort=NO;nokort=NO;calc_kort=0;calc_sem=-99;brij_tpct=0;brij_tbd=0;
  hl_korting=0;hl_semkort=0;ft_hlkorting=0;ft_semhlkorting=0;
  *u(52,1)=*i(6,9);
  vp_=0;aant_flag=NO;kort_=0;

	if(UseAKPrijs){
		if(pos_==10) vp_=*f(6,18+94); else vp_=*f(6,18);
	}
	else if(fldlen(6,PrNrs[pos_])) vp_=*f(6,PrNrs[pos_]);
	if(fldlen(6,104) && *s(6,104)=='J') nokort=YES;
  if(fasgeti(52)==0){
/*
    for(j=0;j<5;j++){
      if(fldlen(52,15+j)>0){
	if(*s(52,15+j)=='>'){
	  if(*f(58,7)<val(s(52,15+j)+1)) break;
	  vp_=*f(6,22+pos_+j);aant_flag=YES;
	}
      }
    }
*/
    if(fldlen(52,21) && *s(52,21)=='N') nokort=YES;
    if(aant_flag) {newkort=YES;goto vp_ok;}
  }
	if(UseAKPrijs){
		if(pos_==10) vp_=*f(6,18+94); else vp_=*f(6,18);
	}
	else vp_=*f(6,PrNrs[pos_+prxnr]);
  vp_ok:
  if(fldlen(9,8)==0) goto endsr;
  fasinit(9);*u(9,2)=pr_klt_;*u(9,3)=*u(6,1);
  m=get_contr(1);if(m==0) nokort=NO;// wel korting indien expliciet 
  if(m && fldlen(9,18)){
    *u(9,18)=*u(6,7);*u(9,19)=*u(6,9);m=get_contr(2);
    if(m){
      *u(9,19)=0;m=get_contr(2);
    }
	  if(m && fldlen(6,101)){ // merk/ producent 
      *u(9,18)=*u(6,101)+30000;*u(9,19)=*u(6,9);m=get_contr(2);
      if(m){
        *u(9,19)=0;m=get_contr(2);
      }
    }
    if(m){
      *u(9,18)=0;*u(9,19)=*u(6,9);m=get_contr(2);
      if(m==0 && (fldlen(6,104)==0 || *s(6,104)!='J')) nokort=NO;/* wel korting indien expleciet contract op groep */
    }
  }
  if(m==0){
    if(fldlen(9,72) && *u(9,72) && *u(9,72)<=*u(25,2)){
      if(*f(9,75)) vp_=*f(9,75);
      if(*f(9,73)) kort_=*f(9,73);
      if(*f(9,74)) k_fr_=*f(9,74);
      if(fldlen(9,81)) hl_korting=*f(9,81);
      if(fldlen(9,82)) hl_semkort=*f(9,82);
      calc_sem=*f(9,76);
    }
    else{
      if(*f(9,8)) vp_=*f(9,8);
      if(*f(9,6)) kort_=*f(9,6);
      if(*f(9,7)) k_fr_=*f(9,7);
      if(fldlen(9,20)) hl_korting=*f(9,20);
      if(fldlen(9,21)) hl_semkort=*f(9,21);
      calc_sem=*f(9,22);
    }
    if(fldlen(9,23)) brij_tpct=*f(9,23);
    if(fldlen(9,24)) brij_tbd=*f(9,24);
    newkort=YES;
  }
  endsr:;
  if(fldlen(52,23) && *s(52,23)=='J' && kort_){
    acc_=*f(6,30);
    k_fr_+=(vp_-acc_) * kort_/100.; kort_=0;
  }
#if !FLAGEPD && !FLAGVDW // EUR korting als hl-korting gebruiken
  if(k_fr_) vp_-=k_fr_;
#endif
  calc_kort=kort_;
  calc_prx=Round((double)vp_,prx_afrond);
  if(fldlen(6,37)==0 || *f(6,37)==0){hl_korting=0;hl_semkort=0;ft_hlkorting=0;ft_semhlkorting=0;}
  else{/* omrekenen naar verpakking */
    ft_hlkorting=hl_korting* *f(6,37)/100;
    ft_semhlkorting=hl_semkort* *f(6,37)/100;
  }
#if FLAGEPD || FLAGVDW// EUR korting als hl-korting gebruiken
	ft_hlkorting+=k_fr_;
#endif
}
 
static int get_contr(int16 keynr_)
{
  int16 k;
						
  if(faskeyi(9,keynr_,0)) return YES;
  for(k=0;k<3;k++) if(*f(9,6+k)) return NO;
  for(k=20;k<=24;k++){
    if(fldlen(9,k) && *f(9,k)) return NO;
  }
  if(fldlen(9,16) && *i(9,16)) return NO;
  return YES;
}


static void GetKlantenkaartInfo(void)
{
  CMarkup Klt;
  int k,z, g,KrtNr,found_,len_,len1_,key;
	int16 jj_,dd_,mm_,leeftijd_=0;
	uint16 dt_bday_;
  CString FldNr, RRNr,cstr_;
	char newadres_[100],thisadres_[100];
	int ExpFields[10]={1,2,3,4,5,6,30,33,0,0};

  ConStyle(0); cls();
	KassaXml.ResetPos();
  KrtNr=atol(KassaXml.FindGetData("KrtNr"));
	RRNr=KassaXml.FindGetData("RRNr"); RRNr=RRNr.Left(11);
	fasinit(92);
	if(KrtNr==0 && RRNr.GetLength()==0){KeyFindKaart(KrtNr); goto dump_kaart;} // geen data : zoek kaart via naam
	if (KrtNr) {
		*u(92,1)=KrtNr; if(*u(92,1)) fasgeti(92);
		if(KrtNr==LastKrtNr && RRNr.GetLength()==0){KeyFindKaart(KrtNr); goto dump_kaart;}
	}
	if (RRNr.GetLength() && fldlen(96,2)){ // zoeken op RRNr of RRNr adden op kaart
		fasinit(96);	cstr2arr(RRNr,s(96,2),fldlen(96,2)); EncryptStr(s(96,2),fldlen(96,2)); 
		g=faskeyi(96,1,0); // zoek 
		if(g){
			fasinit(96);	cstr2arr(RRNr,s(96,2),fldlen(96,2)); // zoek naturel
		  g=faskeyi(96,1,0); // zoek 
		}
		if(g==0){// kaart gevonden
			*u(92,1)=*u(96,3);
			if(*u(92,1) && fasgeti(92)==0){
				zero(s(96,2),fldlen(96,2));cstr2arr(RRNr,s(96,2),fldlen(96,2)); EncryptStr(s(96,2),fldlen(96,2)); fasupd(96); //om oude rr te encrypteren
				goto dump_kaart;
			}
			else faskill(96); // slechte koppeling 
		} 
  	if(*u(92,1) && cmpstr(s(92,3),"XYZ",3)!=0){ // bestaande kaart : RRNr koppelen 
			EncryptStr(s(96,2),fldlen(96,2));  
			scrnum=0;scrget(2,365);z=1;
			scrofld(z++,96,2,-1);
			for(k=1;k<=6;k++) scrofld(z++,92,k,-1);
			scraddkey(z++,2,22,10,3,10000+105,"Terug",KLEUR_FTOETS);
			scraddkey(z++,14,22,25,3,10000+104,"Koppel eID aan deze kaart",KLEUR_FTOETS);
			key=scrupd(-1,0x18);
			if ((key/0x100)==1) key=(key&0xFF);
			if(key!=104) fasinit(92);
			else{
				fasinit(96);cstr2arr(RRNr,s(96,2),fldlen(96,2));EncryptStr(s(96,2),fldlen(96,2));  
				*u(96,3)=*u(92,1);fasadd(96);
			}
			goto dump_kaart;
		}
	}
	
	if(*u(92,1) && memcmp(s(92,3),"XYZ",3)!=0) goto dump_kaart; // gevonden via kaartnummer 
	KassaXml.ResetPos();cstr_=KassaXml.FindGetData("Naam");
	if(cstr_.GetLength()){ // zijn EID gegevens meegegeven, dan al invullen op de lege kaart of koppelein aan bestaande kaart
		fasinit(92); found_=NO;
		KassaXml.ResetPos();
		cstr_=KassaXml.FindGetData("Naam");cstr_+=" "; cstr_+=KassaXml.FindGetData("VNaam");cstr2arr(cstr_,s(92,3),fldlen(92,3));
		cstr_=KassaXml.FindGetData("Straat"); cstr2arr(cstr_,s(92,4),fldlen(92,4)); 
		memset(newadres_,0,sizeof newadres_);len_=MakeAdresCmpBuffer(newadres_);copy(newadres_,s(92,4),fldlen(92,4)); // om (XXX) eruit te halen
		if(faskeyi(92,2,0)==0) found_=YES; // iemand gevonden met zelfde naam en straat
		else{ // zoeken op iemand op zelfde adres
			fasinit(92);
			KassaXml.ResetPos();
			cstr_=KassaXml.FindGetData("Straat"); cstr2arr(cstr_,s(92,4),fldlen(92,4)); 
			cstr_=KassaXml.FindGetData("PostNr"); cstr2arr(cstr_,s(92,5),fldlen(92,5)); 
			cstr_=KassaXml.FindGetData("Stad"); cstr2arr(cstr_,s(92,6),fldlen(92,6)); 
			memset(newadres_,0,sizeof newadres_);len_=MakeAdresCmpBuffer(newadres_);
  		cstr_=KassaXml.FindGetData("GebDat");
			leeftijd_=0;
	  	if(cstr_.GetLength()==8 && fldlen(92,14)){
				*u(92,14)=datejd(atol(cstr_.Mid(0,4)),atol(cstr_.Mid(4,2)),atol(cstr_.Mid(6,2)));
 				if(*u(92,14)){
					jddate(*u(25,2),&jj_,&mm_,&dd_);jddate(*u(92,14),&leeftijd_,&mm_,&dd_);	leeftijd_=jj_-leeftijd_;
					dt_bday_=datejd(jj_,mm_,dd_);	if(leeftijd_ && dt_bday_>*u(25,2)) leeftijd_--;
				}
  		}
 			fasinit(92); found_=NO;
			FOREVER{ // eerst kijken of er al een zelfde adres in zit, zo ja, vragen om RRNr toe te voegen op deze kaart
				if(faskeyi(92,2,2)) break;
				len1_=MakeAdresCmpBuffer(thisadres_);
				if(len_==len1_ && memcmp(newadres_,thisadres_,len_)==0){found_=YES;break;}
			}
		}
		if(found_){
			scrnum=0;scrget(2,363);z=1;scraddpicto(1,0,32,1,12,6,605,0,0,"Opgelet!"); 
			for(k=3;k<=6;k++) scrofld(z++,92,k,-1);
			scrifld(z++,fm_ou2,&leeftijd_);if(leeftijd_ && leeftijd_<18) scrchat(z-1,0xB);
 			scraddkey(z++,2,22,10,3,10000+103,"Terug",KLEUR_FTOETS);
			scraddkey(z++,14,22,25,3,10000+104,"koppel eID aan deze kaart",KLEUR_FTOETS);
			scraddkey(z++,41,22,20,3,10000+105,"maak NIEUWE kaart",KLEUR_FTOETS);
			int key=scrupd(-1,0x1C);
      if(key==103){ // doe niets !
        fasinit(92);
        goto dump_kaart;
      }
			if(key==104){ // koppel maar aan deze kaart
        if(RRNr.GetLength() && fldlen(96,2)){ // RRNr koppelen aan deze kaart 
					fasinit(96);cstr2arr(RRNr,s(96,2),fldlen(96,2));EncryptStr(s(96,2),fldlen(96,2));  *u(96,3)=*u(92,1);fasadd(96);
				}
				goto dump_kaart;
			}
		}
    fasinit(92); 
		if (KrtNr) {*u(92,1)=KrtNr; if(*u(92,1)) fasgeti(92);} // kaart terug resetten 
		else { // klant toevoegen
			copy("XYZ",s(92,3),3);
			if(faskeyi(92,2,1)) fasinit(92); // geen lege XYZ-klant gevonden
			else{
				if(cmpstr(s(92,3),"XYZ",3)) fasinit(92); // geen lege XYZ-klant gevonden
			}
		}
		sysget(4435,1,&GdateSexFromEid);
		KassaXml.ResetPos();
		cstr_=KassaXml.FindGetData("Naam");cstr_+=" "; cstr_+=KassaXml.FindGetData("VNaam");cstr2arr(cstr_,s(92,3),fldlen(92,3));
		cstr_=KassaXml.FindGetData("Straat"); cstr2arr(cstr_,s(92,4),fldlen(92,4)); 
		cstr_=KassaXml.FindGetData("PostNr"); cstr2arr(cstr_,s(92,5),fldlen(92,5)); 
		cstr_=KassaXml.FindGetData("Stad"); cstr2arr(cstr_,s(92,6),fldlen(92,6)); 
		if(GdateSexFromEid!='N'){
  		cstr_=KassaXml.FindGetData("GebDat");
	  	if(cstr_.GetLength()==8 && fldlen(92,14)){
		  	*u(92,14)=datejd(atol(cstr_.Mid(0,4)),atol(cstr_.Mid(4,2)),atol(cstr_.Mid(6,2)));
  		}
  		cstr_=KassaXml.FindGetData("Sex"); cstr2arr(cstr_,s(92,15),fldlen(92,15)); 
		}
	}
	else if(*u(92,1)==0 && RRNr.GetLength()) goto dump_kaart; // kaart niet gevonden via RRNr en geen EID-gegevens meegegeven
	if(*u(92,1)) ovlcall(294,1); // kaart aanpassen 
	else ovlcall(294,2); // kaart toevoegen
  if(*u(92,1) && fldlen(96,2) && RRNr.GetLength()){ // RRNr voor de zekerheid nog eens toevoegen
    fasinit(96);cstr2arr(RRNr,s(96,2),fldlen(96,2));EncryptStr(s(96,2),fldlen(96,2));
		g=faskeyi(96,1,0);
		if(g){fasinit(96);cstr2arr(RRNr,s(96,2),fldlen(96,2));}
		if(g) fasinit(96);
	  zero(s(96,2),fldlen(96,2));cstr2arr(RRNr,s(96,2),fldlen(96,2));EncryptStr(s(96,2),fldlen(96,2));  *u(96,3)=*u(92,1);
	  if(*l(96,1)) fasupd(96); else fasadd(96);
	}
	dump_kaart:;
	if(*u(92,1)){
    Klt.AddElem("Kaart");
    Klt.IntoElem();
    for (int i=0; i<10; i++) {
			if(ExpFields[i]==0 || fldlen(92,ExpFields[i])==0) continue;
      FldNr.Format("F%d",ExpFields[i]);
      Klt.AddElem(FldNr,GetString(92,ExpFields[i],false));
    }
  }
  else {
    Klt.AddElem("Dummy",0);
  }
  Klt.Save(Jmc2KasFilename);
	LastKrtNr=*u(92,1);
  NotifyJMH();
}

static void EncryptStr(char *ps_,int maxlen_)
{
	int16 len_,j,k,kar_used_;
	char str_[40],kar_;

	zero(str_,sizeof str_);kar_used_=NO;
	for(len_=0;len_<maxlen_;len_++) {
		kar_=*(ps_+len_);
		if(kar_=='\0') break;
		str_[len_]=kar_;
		if(kar_<'0' || kar_>'9') kar_used_=YES;
	}
	if(len_==0 || len_!=11 || kar_used_) goto endsr; // enkel 11 cijfers encrypteren
	for(k=0;k<11;k++){
		j=(str_[k]-'0')*3; if(k<10) j+=str_[k+1]-'0'; // laatste cijfer enkel *3
		if(j<26) str_[k]='A'+j;
		else if(j<36) str_[k]='0'+j-26;
		else str_[k]='a'+j-36;
	}
	*ps_='X'; copy(str_,ps_+1,11);
	endsr:;
}



static void UpdateKlantenkaartPunten(void)
{
  CMarkup Klt;
  int punten_,saldo_,k,len_;
	double bedrag_;

  fasinit(92);
	KassaXml.ResetPos();
  if (fldlen(92,1)==4) *l(92,1)=atol(KassaXml.FindGetData("KrtNr"));
  else *u(92,1)=atol(KassaXml.FindGetData("KrtNr"));
	punten_=atol(KassaXml.FindGetData("Punten"));
  saldo_=atol(KassaXml.FindGetData("Saldo"));
	bedrag_=str2dbl(KassaXml.FindGetData("Bedrag"));
  KassaXml = CMarkup();
  if(*u(92,1)){
		fasgeti(92);
		if(punten_ || bedrag_){
			if(*u(92,30)!=*u(25,2) || *u(92,31)!=punten_ || *f(92,32)!=bedrag_ || *u(92,33)!=saldo_){// er moet iets gewijzigd zijn
  			len_=s(92,35)-s(92,30);
				for(k=9;k>0;k--){
					if(fldlen(92,30+k*5)) copy(s(92,30+(k-1)*5),s(92,30+k*5),len_);
				}
				memset(s(92,30),0,len_);
				*u(92,30)=*u(25,2);*u(92,31)=punten_;*f(92,32)=bedrag_;*u(92,33)=saldo_;
				*f(92,21)+=bedrag_;if(*u(92,20)==0) *u(92,20)=*u(25,2);
				fasupd(92);
			}
		}
		SetExitFlag(1);
	} else SetExitFlag(0);
	KassaXml.Save(Jmc2KasFilename);
  NotifyJMH();
}

// Groepinfo uit kassa /////////////////////////////////////////
//#define GRP_TOTAAL      1000
//#define GRP_TEGOED      1001
//#define GRP_TERUG       1002
//#define GRP_GOEDEREN    1003
//#define GRP_LGMEE       1004
//#define GRP_VOORSCHOT_B 1005
//#define GRP_VOORSCHOT             1006
//#define GRP_GELD        1010/* alle betaalmiddelen */
//#define GRP_CHEQUE      1011
//#define GRP_BANCONT     1012
//#define GRP_MAALTIJD    1013
//#define GRP_TGBON       1014
//#define GRP_LEVERBON    1015
//#define GRP_CREDIT      1016
//#define GRP_TBSALDO     1017
//#define GRP_MEETOTAAL   1018
//#define GRP_DIVUITGAVE  1019
//#define GRP_DIVONTVANG  1020
//#define GRP_ZEGELS      1021
//#define GRP_LGTERUG     1022
//#define GRP_PROTON      1023
//#define GRP_VOORSCHOT_R    1024
////////////////////////////////////////////////////////////////


static void GetTimestamp(char* buffer_)
{
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer_, 80, "%Y%m%d%H%M%S", timeinfo);
}

static void FillAndCalculate_Bon_Factuur(int doctype_,int execmode_)
{
	int j,k,n,first_,groep_,ret240_;
	double bd_,tot_voorschot_,tot_bons_,totaal_,tb_betwijze_[15];
	float last_lgaantal_;
	long TbDiversArtikel[10]; // divers artikel per mogelijk BTW%
	char buf20_[20],last_lgcode_[15];
	char logfilename_[255];
	CFile clogfile_; 
	std::ofstream logfile_;
	CString cstr_,cstuksstr_;
    char buffer_[80];
	int16 success_ = NO;

	if (doctype_ == FACTUUR) {

		//zero(buffer_, sizeof buffer_);
		//GetTimestamp(&buffer_[0]);
		//zero(logfilename_, sizeof logfilename_);
		//copy("..\\ToGeel\\FactUitKas", logfilename_, 20);
		//copy(buffer_, &logfilename_[strlen(logfilename_)], strlen(buffer_));
		//copy(".log", &logfilename_[strlen(logfilename_)], 4);
	 // if(clogfile_.Open(logfilename_,CFile::modeCreate|CFile::modeWrite,0)!=false){
		//	clogfile_.Write(" Start aanmaak factuur\n\n",24);
		//	cstr_=KassaXml.GetDocFormatted(4) ;
		//	clogfile_.Write(cstr_,cstr_.GetLength());
		//	clogfile_.Close();
		//}

		//logfile_.open(logfilename_);

		//if (logfile_) {
		//	logfile_ << buffer_ << " Start aanmaak factuur\n\n" << KassaXml.GetDocFormatted(4) << "\n\n";
		//	logfile_.close();
		//}
	}

	fasinit(2);
	KassaXml.ResetPos();
	*u(2,1)=atol(KassaXml.FindGetData("/Ticket/Klant"));
	if(*u(2,1)) fasgeti(2);

	// Klant moet bestaan
	if (*u(2,1) == 0) {
		//if (doctype_ == FACTUUR) {
		//	zero(buffer_, sizeof buffer_);
		//	GetTimestamp(&buffer_[0]);
		//	if(clogfile_.Open(logfilename_,CFile::modeReadWrite,0)!=false){
		//		clogfile_.SeekToEnd();
		//		clogfile_.Write(buffer_,strlen(buffer_));
		//		cstr_=KassaXml.GetDocFormatted(4) ;
		//		clogfile_.Write("\nKlant bestaat niet\n",20);
		//		clogfile_.Close();
		//	}

		//	//logfile_.open(logfilename_, std::ios::app);

		//	//if (logfile_) {
		//	//	logfile_ << buffer_ << " Klant bestaat niet\n";
		//	//	logfile_.close();
		//	//}
		//}

		SetExitFlag(0);
		goto endsr;
	}

	ram=RamBon; ram_size=125000;
	if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;memset(ram,0,ram_size);
	stu58_len=fldlen(58,0);max_line=ram_size/stu58_len;
	sysget(1084,4,&def_btw);
	sysget(2222,2,&def_qfact);
	sysget(3608,2,def_ext);
	sysget(3894,2,&sys3894);
	sysget(8000,60,NaamVarBetWijze);
	sysget(2900,40,(char *)&TbDiversArtikel[0]); // zie parameters V.2.+
	UseAKPrijs=NO;prxnr=0;
	prxnr=*s(2,26);
	if(prxnr=='A') UseAKPrijs=YES; else prxnr=prxnr-'0';
	if(prxnr<0 || prxnr>9) prxnr=0;
	if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
	//if(!UseAKPrijs && (sys3894 & (1<<prxnr))) def_inc='J';
	//else def_inc='N';
	def_inc='J'; //voorlopig enkel kassa-prijs 
	fasinfo(80,201);*u(25,2)=*l(80,1); // om meest recente datum te krijgen indien men kassa laat aanstaan.
	fasinit(8); ft_date=*u(25,2);
	*u(8,3)=*u(2,1);*u(8,8)=ft_date;
	*s(8,22)='J';//DEF_VOLD;
	*s(8,26)='N';
	if(fldlen(8,23)) copy("EUR",s(8,23),3);
	*u(8,28)=def_qfact;

	if(fldlen(8,48)){
		sysget(2854,2,u(8,48)); if(*u(8,48)<1 || *u(8,48)>10) *u(8,48)=99; // firma in apart journaal
		if(WerkpostFiliaalNr>=1 && WerkpostFiliaalNr<=10){
			sysget(2770+(WerkpostFiliaalNr-1)*6,6,buf20_);
			if(buf20_[0]) *u(8,48)=WerkpostFiliaalNr;
		}
	}
	//if(fldlen(8,48)) *u(8,48)=WerkpostFiliaalNr;


	fasinit(58);
	*f(58,24)=def_btw;
	if(fldlen(58,27)) *s(58,27)=def_inc;
	if(fldlen(58,25)) copy(def_ext,s(58,25),fldlen(58,25));
	//voorlopig enkel kassa-prijs   *f(58,21)=*f(2,18);
	for(j=0;j<max_line;j++){
		copy(s(58,1),ram+(j*stu58_len),stu58_len);
	}
	tot_voorschot_=0;	tot_bons_=0;memset(tb_betwijze_,0,sizeof tb_betwijze_);memset(last_lgcode_,0,sizeof last_lgcode_); last_lgaantal_=0;
	KassaXml.ResetPos();

	if (KassaXml.FindElem("Detail") == false) {
		//if (doctype_ == FACTUUR) {
		//	zero(buffer_, sizeof buffer_);
		//	GetTimestamp(&buffer_[0]);
		//	if(clogfile_.Open(logfilename_,CFile::modeReadWrite,0)!=false){
		//		clogfile_.SeekToEnd();
		//		clogfile_.Write(buffer_,strlen(buffer_));
		//		cstr_=KassaXml.GetDocFormatted(4) ;
		//		clogfile_.Write(" Geen detail gevonden in kassabestand\n",38);
		//		clogfile_.Close();
		//	}

		//	//logfile_.open(logfilename_, std::ios::app);

		//	//if (logfile_) {
		//	//	logfile_ << buffer_ << " Geen detail gevonden in kassabestand\n";
		//	//	logfile_.close();
		//	//}
		//}

		goto endsr;
	}

	KassaXml.IntoElem();
	KassaXml.ResetMainPos();j=0;
	FOREVER{
		if(KassaXml.FindElem("L")==false) break;
		KassaXml.IntoElem();
		KassaXml.ResetMainPos();groep_=atoi(KassaXml.FindGetData("G"));
		if(groep_==9998){ // losse tekst  
			ram2stu(j);
			KassaXml.ResetMainPos();cstr2arr(KassaXml.FindGetData("X"),s(58,16),fldlen(58,16)); 
			if(*s(58,16)=='*') stu2ram(j++); // enkel Eid tekst
		}
		else if(groep_>=1 && groep_<=99){// artikel 
			ram2stu(j);
			KassaXml.ResetMainPos();*f(58,7)=str2dbl(KassaXml.FindGetData("A"));
			if(sys4408){ // code langer dan 5, dan record#
				KassaXml.ResetMainPos();
				fasinit(6);*u(6,1)=atoi(KassaXml.FindGetData("C")); fasgeti(6);
				copy(s(6,2),s(58,15),fldlen(58,15));
			}
			else{
				KassaXml.ResetMainPos();cstr2arr(KassaXml.FindGetData("C"),s(58,15),fldlen(58,15)); 
				fasinit(6);copy(s(58,15),s(6,2),fldlen(58,15)); faskeyi(6,1,0);
			}
			KassaXml.ResetMainPos();*f(58,20)=str2dbl(KassaXml.FindGetData("P"));
			KassaXml.ResetMainPos();*f(58,24)=str2dbl(KassaXml.FindGetData("W"));
			*i(58,34)=groep_;
			KassaXml.ResetMainPos();cstuksstr_=KassaXml.FindGetData("B");
			if(fldlen(58,62)){
				if(cstuksstr_.GetLength()==1){
					buf20_[0]=cstuksstr_.GetAt(0)-'0';
					if(buf20_[0]&0x01) *s(58,62)='S';
				}
				else if(cstuksstr_=="1") *s(58,62)='S';
			}
			if(groep_>=1 && groep_<=98){
				zero(last_lgcode_,sizeof last_lgcode_);last_lgaantal_=0;
				if(*s(58,62)=='S') copy(s(6,44),last_lgcode_,fldlen(6,44)); else copy(s(6,41),last_lgcode_,fldlen(6,41)); 
				last_lgaantal_=*f(58,7);
				stu2ram(j++);
			}
			else { // automatisch leeggoed bij leveringsbon overslaan
				if(doctype_!=LEV_BON || cstuksstr_!="2" /* *f(58,7)!=last_lgaantal_ || cmpstr(last_lgcode_,s(6,2),fldlen(6,2)) */) stu2ram(j++);
				memset(last_lgcode_,0,sizeof last_lgcode_); last_lgaantal_=0;
			}

		}
		else if(groep_==-1){// % korting op laatste artikel
			ram2stu(j);
			*f(58,7)=1;
			KassaXml.ResetMainPos();bd_=str2dbl(KassaXml.FindGetData("P"));
			sprintf(s(58,16),"+Korting %2.2f %%",bd_);
			if(sys4408){ // code langer dan 5, dan record#
				KassaXml.ResetMainPos();
				fasinit(6);*u(6,1)=atoi(KassaXml.FindGetData("C")); fasgeti(6);
				copy(s(6,2),s(58,15),fldlen(58,15));
			}
			else{
				KassaXml.ResetMainPos();cstr2arr(KassaXml.FindGetData("C"),s(58,15),fldlen(58,15)); 
			}
			KassaXml.ResetMainPos();*f(58,20)=str2dbl(KassaXml.FindGetData("T"));
			KassaXml.ResetMainPos();*f(58,24)=str2dbl(KassaXml.FindGetData("W"));
			*i(58,34)=groep_;
			stu2ram(j++);
		}
		else if(groep_==-2){// EUR korting op laatste artikel
			ram2stu(j);
			*f(58,7)=1;
			KassaXml.ResetMainPos();bd_=str2dbl(KassaXml.FindGetData("P"));
			copy("+Korting",s(58,16),10);//sprintf(s(58,16),"+Korting",bd_);
			if(sys4408){ // code langer dan 5, dan record#
				KassaXml.ResetMainPos();
				fasinit(6);*u(6,1)=atoi(KassaXml.FindGetData("C")); fasgeti(6);
				copy(s(6,2),s(58,15),fldlen(58,15));
			}
			else{
				KassaXml.ResetMainPos();cstr2arr(KassaXml.FindGetData("C"),s(58,15),fldlen(58,15)); 
			}
			KassaXml.ResetMainPos();*f(58,20)=str2dbl(KassaXml.FindGetData("T"));
			KassaXml.ResetMainPos();*f(58,24)=str2dbl(KassaXml.FindGetData("W"));
			*i(58,34)=groep_;
			stu2ram(j++);
		}
		else if(groep_==1040){// verkoop cadeaubon op defaultrekening 8 zetten als artikel
			ram2stu(j);
			KassaXml.ResetMainPos();*f(58,7)=1;
			if(TbDiversArtikel[8]==0){
				DisplayWarning("Cadeaubonnen kunnen hier NIET gefactureerd worden, maak deze op PC",605,0);

				//if (doctype_ == FACTUUR) {
				//	zero(buffer_, sizeof buffer_);
				//	GetTimestamp(&buffer_[0]);
				//	logfile_.open(logfilename_, std::ios::app);

				//	if (logfile_) {
				//		logfile_ << buffer_ << " Cadeaubonnen kunnen hier NIET gefactureerd worden, maak deze op PC\n";
				//		logfile_.close();
				//	}
				//}

				SetExitFlag(0);
				goto endsr;
			}
			if(TbDiversArtikel[8]) *u(58,14)=TbDiversArtikel[8]; else *u(58,14)=TbDiversArtikel[0];
			fasinit(6); *u(6,1)=*u(58,14); if(*u(6,1)) fasgeti(6);
			copy(s(6,2),s(58,15),fldlen(58,15));
			KassaXml.ResetMainPos();*f(58,20)=str2dbl(KassaXml.FindGetData("T"));
			KassaXml.ResetMainPos();*f(58,24)=*f(6,28);
			*i(58,34)=*i(6,9);
			stu2ram(j++);
		}
		else{ // hou hier rekening met het kassa-programma voor nieuwe mogelijkheden
			KassaXml.ResetMainPos();totaal_=str2dbl(KassaXml.FindGetData("T"));
			switch(groep_){
			case 1017 : if(totaal_) *s(8,22)='N'; break; // krediet 
			case 1002 : tot_voorschot_-=totaal_;tb_betwijze_[0]-=totaal_; break; // geld terug
			case 1010 : tot_voorschot_+=totaal_; tb_betwijze_[0]+=totaal_; break;// cash
			case 1011 : tot_voorschot_+=totaal_; tb_betwijze_[1]+=totaal_;break; // cheque
			case 1012 : tot_voorschot_+=totaal_; tb_betwijze_[2]+=totaal_;break; // bancontact
			case 1013 : tot_voorschot_+=totaal_; tb_betwijze_[3]+=totaal_;break; // maaltijdcheque
			case 1014 : tot_voorschot_+=totaal_; tb_betwijze_[4]+=totaal_;break; // tegoedbon
			case 1015 : tot_voorschot_-=totaal_; tot_bons_-=totaal_; tb_betwijze_[5]-=totaal_;break; // leveranciersbon (NEGATIEF!)
			case 1016 : tot_voorschot_+=totaal_; tb_betwijze_[6]+=totaal_;break; // creditcard
				// WORDT OP ARTIKEL GEZET						case 1040 : tot_voorschot_-=totaal_; tb_betwijze_[7]-=totaal_;break; // VK cadeaubon
			case 1041 : tot_voorschot_-=totaal_; tb_betwijze_[8]-=totaal_;break; // Betaling cadeaubon
			case 1023 : tot_voorschot_+=totaal_;tb_betwijze_[9]+=totaal_; break; // mobiel
			case 1042 : tot_voorschot_+=totaal_;tb_betwijze_[10]+=totaal_; break; // var.betaalwijze 1
			case 1043 : tot_voorschot_+=totaal_;tb_betwijze_[11]+=totaal_; break; // var.betaalwijze 2
			case 1044 : tot_voorschot_+=totaal_;tb_betwijze_[12]+=totaal_; break; // var.betaalwijze 3
			default   : break;
			}
		}
		KassaXml.OutOfElem();
	}
	KassaXml.OutOfElem();
	if(fldlen(8,21)){
		if(*s(8,22)!='J' && tot_voorschot_) *f(8,21)=tot_voorschot_;
		else *f(8,21)=tot_bons_;
	}
	if(fldlen(8,73) && tb_betwijze_[2]) *s(8,73)='B'; // bancontact
#if FLAGD4U
	if(*s(8,22)=='J' && tb_betwijze_[2]) *s(8,22)='B'; // bancontact apart
#endif
	if(j==0){
		if (execmode_ == 1) SetExitFlag(0); else SetExitFlag(1); // geen lege factuur maken!
		goto endsr;
	}
	if(doctype_==FACTUUR || doctype_==LEV_BON){
		first_=YES;
		for(k=0;k<13;k++){
			if(tb_betwijze_[k]==0) continue;
			if(first_){
				ram2stu(j); *s(58,16)='*';stu2ram(j++);
				ram2stu(j); 
#if FLAGSTN
				copy("*Paiement ",s(58,16),11);
				first_=NO;
			}
			else{
				ram2stu(j); copy("*         ",s(58,16),10);
			}
			switch(k){
			case 0 : copy("Cash       ",s(58,16)+10,11); break;
			case 1 : copy("E-Ch†ques  ",s(58,16)+10,11); break;
			case 2 : copy("BC/Maestro ",s(58,16)+10,11); break;
			case 3 : copy("M-cheque   ",s(58,16)+10,11); break;
			case 4 : copy("Propre bon ",s(58,16)+10,11); break;
			case 5 : copy("Bon R…duct.",s(58,16)+10,11); break;
			case 6 : copy("Carte cr…d.",s(58,16)+10,11); break;
			case 7 : copy("Ch†que cad.",s(58,16)+10,11); break;
			case 8 : copy("Ch†que cad.",s(58,16)+10,11); break;
			case 9 : copy("Mobile     ",s(58,16)+10,11); break;
			case 10 : copy(NaamVarBetWijze[0],s(58,16)+10,11); break;
			case 11 : copy(NaamVarBetWijze[1],s(58,16)+10,11); break;
			case 12 : copy(NaamVarBetWijze[2],s(58,16)+10,11); break;
			default: copy("Div†rs     ",s(58,16)+10,11); break;
			}
			Double2Text(tb_betwijze_[k],s(58,16)+21,8,3,0x82);
#else
				copy("*Betaald  ",s(58,16),10);
				first_=NO;
			}
			else{
				ram2stu(j); copy("*         ",s(58,16),10);
			}
			switch(k){
			case 0 : copy("Geld       ",s(58,16)+9,11); break;
			case 1 : copy("E-Cheque   ",s(58,16)+9,11); break;
			case 2 : copy("BC/Maestro ",s(58,16)+9,11); break;
			case 3 : copy("M-cheque   ",s(58,16)+9,11); break;
			case 4 : copy("Tegoedbon  ",s(58,16)+9,11); break;
			case 5 : copy("Kortingsbon",s(58,16)+9,11); break;
			case 6 : copy("Creditkaart",s(58,16)+9,11); break;
			case 7 : copy("V.Cadeaubon",s(58,16)+9,11); break;
			case 8 : copy("Cadeaubon  ",s(58,16)+9,11); break;
			case 9 : copy("Mobiel     ",s(58,16)+9,11); break;
			case 10 : copy(NaamVarBetWijze[0],s(58,16)+9,11); break;
			case 11 : copy(NaamVarBetWijze[1],s(58,16)+9,11); break;
			case 12 : copy(NaamVarBetWijze[2],s(58,16)+9,11); break;
			default: copy("Divers     ",s(58,16)+9,11); break;
			}
			Double2Text(tb_betwijze_[k],s(58,16)+20,8,3,0x82);
#endif
			for(n=0;n<21;n++) if(*(s(58,16)+n)=='\0') *(s(58,16)+n)=' '; // probleem lengte var.betaalwijzen
			stu2ram(j++);
		}
	}
	if(doctype_==LEV_BON){
		ret240_=ovlcall(944,execmode_);
		if(ret240_==0) {SetExitFlag(0); goto endsr;} // berekenen en/of drukken leveringsbon 
	}
	else{
		//zero(buffer_, sizeof buffer_);
		//GetTimestamp(&buffer_[0]);
		//logfile_.open(logfilename_, std::ios::app);

		//if (logfile_) {
		//	logfile_ << buffer_ << " Ga nu ovl 941 oproepen om factuur te maken\n";
		//	logfile_.close();
		//}

		ret240_=ovlcall(941,execmode_);
		_unlink(Kas2JmcFilename); // uit veiligheid voor dubbele facturen owv communicatieproblemen

		if (ret240_ == 0) {
			//zero(buffer_, sizeof buffer_);
			//GetTimestamp(&buffer_[0]);
			//logfile_.open(logfilename_, std::ios::app);

			//if (logfile_) {
			//	logfile_ << buffer_ << " Return value 0 van ovl 941\n";
			//	logfile_.close();
			//}

			SetExitFlag(0);
			goto endsr;
		} // berekenen en/of drukken factuur

		//zero(buffer_, sizeof buffer_);
		//GetTimestamp(&buffer_[0]);
		//logfile_.open(logfilename_, std::ios::app);

		//if (logfile_) {
		//	logfile_ << buffer_ << " Terug van ovl 941\n";
		//	logfile_.close();
		//}
	}
	if(execmode_==0){// bij berekenen prijs alles terug dumpen
		KassaXml.ResetPos();
		if(KassaXml.FindElem("Detail")) KassaXml.RemoveElem(); // origineel deleten en nieuwe in de plaats zetten
		KassaXml.ResetMainPos();KassaXml.AddElem("Detail");
		KassaXml.IntoElem();
		KassaXml.ResetMainPos();
		for(j=0;j<max_line;j++){
			ram2stu(j);
			if(*s(58,15) || *s(58,16)){
				KassaXml.AddElem("L"); 
				KassaXml.IntoElem();
				if(sys4408){ // code langer dan 5, dan record# in code zetten
					zero(s(58,15),fldlen(58,15));sprintf_s(s(58,15),fldlen(58,15),"%05d",*u(58,14));
				}
				KassaXml.AddElem("C",arr2cstr(s(58,15),fldlen(58,15)));
				KassaXml.AddElem("A",Fld2CString(58,31));
				cstr_=""; if(fldlen(58,62) && *s(58,62)=='S') cstr_="1";KassaXml.AddElem("B",cstr_);
				if(*i(58,34)==99){// leeggoed 
					KassaXml.AddElem("P",Fld2CString(58,20));
					KassaXml.AddElem("T",Fld2CString(58,47));
				}
				else{
					bd_=*d(58,35)* (1. + *f(58,24)/100.); // incl BTW
					*d(58,35)=Round(bd_,(double)(0.01));KassaXml.AddElem("T",Fld2CString(58,35));
					if(*f(58,31)) bd_=*d(58,35)/ *f(58,31); else bd_=0;
					*f(58,20)=Round(bd_,prx_afrond);KassaXml.AddElem("P",Fld2CString(58,20));
				}		
				KassaXml.OutOfElem();
			}
		}
		KassaXml.OutOfElem();
	}
	else{
		KassaXml = CMarkup();
		KassaXml.AddElem("Ticket");
		KassaXml.IntoElem();
		KassaXml.AddElem("FaktNr",FactuurTotalen.ft_nr);
		KassaXml.AddElem("Klant",*u(2,1));
		cstr_="KlantNr : "; if(fldlen(2,2)) cstr_+=Fld2CString(2,2); else cstr_+=Fld2CString(2,1);
		if(*l(2,10)) {cstr_+="       BTW BE-";cstr_+=Fld2CString(2,10);}
		KassaXml.AddElem("KltInfo",cstr_);
		KassaXml.AddElem("KltInfo",Fld2CString(2,3));
		KassaXml.AddElem("KltInfo",Fld2CString(2,4));
		cstr_=Fld2CString(2,5);cstr_+="  ";cstr_=Fld2CString(2,6);KassaXml.AddElem("KltInfo",cstr_);
//scrnum=0;scrget(1,170); // tijdelijk
//scrifld(5,fm_os63,"jmc2kas wordt aangemaakt, ret240_= (2=mail, 3=peppol)");
//scrifld(7,fm_ou2,&ret240_);
// scrupd(-1,0);
		if(doctype_==FACTUUR && (ret240_==2 || ret240_==3)){ // factuur werd gemaild : doorgeven op kasticket
			KassaXml.AddElem("KltInfo","----------------------------------------");
			if(ret240_==2){
				//if(fldlen(2,128) && *s(2,128)=='P') {
				//	KassaXml.AddElem("KltInfo","Versturen via peppol NIET gelukt!");
				//}
  				KassaXml.AddElem("KltInfo","De factuur werd GEMAILD naar :");
	  			j=21; if(fldlen(2,129) && *s(2,129))  j=129; // mail boekhouder 
		  		k=Fld2CString(2,j).GetLength();
		  		if(k>0 && k<38) k=(38-k)/2; else k=0;
		  		cstr_="                    "; cstr_=cstr_.Left(k)+Fld2CString(2,j);
		  		KassaXml.AddElem("KltInfo",cstr_);
			}
			else{
				KassaXml.AddElem("KltInfo","De factuur werd verstuurd via peppol");
			}
			KassaXml.AddElem("KltInfo","----------------------------------------");
		}

		KassaXml.OutOfElem();
	}

	// if (doctype_ == FACTUUR) {
	//	zero(buffer_, sizeof buffer_);
	//	GetTimestamp(&buffer_[0]);
	//	logfile_.open(logfilename_, std::ios::app);

	//	if (logfile_) {
	//		logfile_ << buffer_ << " Dit gaat terug naar de kassa\n\n" << KassaXml.GetDocFormatted(4) << "\n";
	//		logfile_.close();
	//	}
	//}

	success_ = YES;
	SetExitFlag(1);
endsr:;
	KassaXml.Save(Jmc2KasFilename);

	//if (success_ && doctype_ == FACTUUR) {
	//	remove(logfilename_);
	//}
}

static void SetExitFlag(int flag_)
{
	KassaXml.ResetPos();
	if(KassaXml.FindElem("RetValue")==false) KassaXml.AddElem("RetValue"); 
	if(flag_==0) KassaXml.SetData("0"); else KassaXml.SetData("1");
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
