/*

{
  int i;
  CString str;

  moinit(0,1);
//  PlatformType(2);

  CKasPLU::prx_ix=0;
  kasusr.pKasPLU=&kasplu;

  CKasSYS::rd_kassys(1);
  kasplu.rd_kasplu(2);
  kasusr.rd_kasusr(6);

  screen_save();
  kasusr.aantal=3;
  kasusr.xpos=20;
  kasusr.ypos=1;
  kasusr.stuks_fl=YES;
  kasusr.SelKeyConen(0,""); // (1,1017,20,1);
  screen_restore();

  vdposp(10,0);
  for (i=0; i<kasusr.vrkused; i++) {
    kasplu.get_plu(kasusr.vrk[i].plu_ix);
    str.Format("%5.0f %s",kasusr.vrk[i].aantal,kasplu.art_info.naam);
    tkdspnl((char *)(LPCTSTR)str);
  }
  kbchar();

*/

// #define WINVER 0x0501  // was 500
// #define _WIN32_WINNT 0x0501  // was 500

#include "StdAfx.h"

#pragma warning(disable: 4996)
#pragma pack(1)

char version[] = "kassa    00.01 08/03/21 (c) Priority Software";

#include <iostream>
#include <direct.h>
#include <process.h>

#include "P:\JamaCon\library\JamaConL.h"
#include "kashead.h"
#if XP_KASSA
#include "EIDNative.h"  // in configuration -> link -> input de Swelio32.lib  door EIDRead.lib vervangen 
#else
#include "Swelio.h"   // in configuration -> link -> input de EIDRead.lib vervangen door Swelio32.lib 
#endif

#include "windows.h"
#include "locale.h"
#include "picture.h"
#include "Markup.h"
#include "label.h"

#include "kaspluc.h"
#include "kassysc.h"
#include "kastxtnc.h"
#include "kasusrc.h"
#include "kaskrtc.h"
#include "kaskltc.h"
#include "CustDisplay.h"
#include "AffDisplay.h"
#include "JmuDoc.h"


#define KLEUR_FTOETS        RGB(0,127,0)


CKasPLU kasplu;
CKasSYS kassys;
CKasUSR kasusr;
CKasKRT kaskrt;
CKasKLT	kasklt;

static unsigned char fm_os25[]  = {7,0x88,25,0,0,0,0};
static unsigned char fm_os40[]  = {7,0x88,40,0,0,0,0};
static unsigned char fm_os20[]  = {7,0x88,20,0,0,0,0};
static unsigned char fm_os7[]  = {7,0x88,7,0,0,0,0};
static unsigned char fm_us20[] = { 7,0xC8,20,0,0,0,0 };
static unsigned char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static unsigned char fm_os10[]  = {7,0x88,10,0,0,0,0};
static unsigned char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static unsigned char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static unsigned char fm_od6_2[] = {6,0x95,6,2,0x70,0}; 


#if XP_KASSA
TEIDIdentity eID;
TEIDAddress eIDaddr;
#else 
tagEidIdentityA eID;
tagEidAddressA eIDaddr;
#endif

extern bool KassaTestConfigFlag;
extern int KeyboardType;
extern int prtnum, prtbnum, NoPrtCut,DefNoPrtCut;

CString m_strExtraDisplayName;
CRect ExtraDisplaySize, rtCust, rtAff, rtLarge;

struct s_lijn *p_lin;
struct s_verkopen *verkopen, *p_vrk;
struct art_line art_promo;
                        
extern struct s_user_work {
  char key[MAX_NIVEAU];
  char tekst[TEKST_COUNT][8];
  char artcode[ARTCODE_LEN];
} user_work [6][8];
 
extern struct s_grp_info {
  char naam[20];
  float btw;
} grp_info[100];

extern struct {
  char promo;
  char gratis;
  char sortnr;
  char dummy[7];
} grp_extra[100];

extern struct s_valuta {
  char naam[4];
  float coeff;
  char lade;
  char digits;
} valuta[10];
  
extern struct s_valuta2 {
  float round;
  char dummy[6];
} valuta2[10];

struct {
	char DateTimeStr[20];
  int KlantNr;
  int KaartNr;
	double TotTicket;
	double TotLeeggoed;
	double TotBetaald;
	char VervangText[22]; // 70
  char BonText[2][50];
  char code[10];
  char naam[40];
  char straat[30];
  char postnr[7];
  char gemeente[25];
  char EIDnr[30];
  char dummy2[17]; // 259
} WrkBonHdr; // lengte moet in totaal gelijk zijn aan WRK_BONHDR_LEN = 329 !!!!

struct {
  float btw_perc;
  double basis;
  double btw;
  double totaal;
} btw_cumul[CUMBTW_COUNT];
int btw_used;
int FactPageNr;
double TicketTotalen[3]; // 0=totaal, 1=goederen, 2=leeggoed

static struct layout *p_lay;
extern struct layout key_layout[], bet_layout[], bet_krediet;

extern int PrintControl2PDF;
extern char txt_tegoedbon[5][41];
extern unsigned reg_ds, mulfunok;
extern int tafel_cnt, pcl3flag, VKPDADisplayBlockedFlag, PWOpenLade;
#if _DEBUG
long HeapUsed();
#endif

COLORREF VerkoperKleur=RGB(255,255,0);

static double String2Getal(CString S,char decim_kar);
static double String2Double(CString S){return String2Getal(S,',');}
static double String2Double(CString S,char decim_kar){ return String2Getal(S,decim_kar);}
static int String2Int(CString S){return (int)(String2Getal(S,','));}


 
void _disp_vid(int x, int y, char *s, int attr)
{
  char buf[500], *p;

  disp_vid(x,y,s,attr);
  return;

  p=buf;
  while (*s==' ') {x++; s++;}
  while (*s) *p++=*s++;
  if (p!=buf) {
    while (*--p==' ') p--;
    *++p=0;
    disp_vid(x,y,buf,attr);
  }
}

extern char *txtfin[], *txtbet[], txtvrk[], txttxt[200][150], PayCardServer[], PluCreditCost[], HDDSerialNr[],CreditCardViaBetaalterminal;

extern int key_count, art_count, no_prtkas, fl_freedelity ,fl_KasCtrl, back_time, ext_count, MinFreeCreditCost,SoortKassa;
extern char prt_fil, prt_trans, back_file[];
extern char fakt_head[20][51], fakt_vtekst[3][81];
extern int fakt_dist, teg_allow;
char ss_enable;
extern int prt_cut_count, krt_bits, groep_leeg;
extern short int vrk_lade[VRK_COUNT], prx_sys[VRK_COUNT], leeg_sys[VRK_COUNT], ex_ticket;
extern int prx_count, bc_allowed, bc_option, chk_kassier, btw_holland;
extern int klant_nr, fakt_allow, fl_open_lade, leegok, testmax;
extern int fref_sys, lijn_round, sprook, PrtOnWRKPutFlag, KeepWRKBon420,specialfl, ConfigFlag,PromoOpStuksAllowed;
extern char tijd[];
extern int def_digits, plulink, EigenPrijsOpStuksAllowed;
extern char def_valuta[], PrtSuspended,TotaalOp5CentAfronden, PromoNotOnHorecaPrice;
extern double BedragTotaalafronding;
extern float def_round,krtperc,krtfull;
extern unsigned jddatum, faktnr, tick_type;
extern int optiesgroep, optiestype;

extern struct s_klant klant;
extern int klant_nr;

CCustDisplay *pCustDisplay;
CAffDisplay *pAffDisplay; 
int ConLargeIx=0, ConCustIx=0;
static char sear_niv[MAX_NIVEAU];
int reg_db, reg_da, reg_kom, regix;
 
static int klt_ix[VRK_COUNT];
int lade_used[MAX_LADE+1];
static int key_touched, larg_len, larg_last, regalffl=YES;
static char digits, chk_overflow=YES;
char regalfa[16];
char einde_fl, val_inuse=NO, val_used=NO, val_ix, prevcust[41];
char PrevAttentionFlag=FALSE;
int val_einde=-1, val_wlast=-1, val_llast=-1, larg_next;
int bak_fles=-1;
int CntFlesInBak=-1;
int plu_ix, ticketnr;
char beep_fl, disp_fl; // config[10], 
bool BestelButtonDisplay=false;
char *getml();
long get_hun();
double round_it();
int vrk_ix;
long mem_needed, back_doit;
extern float BTWBONPercentage, BTWBONDrankPercentage;
extern int DrankGroep;
 
int reg_sign;
double reg,reg_aantal;

int model=2; // win-kassa GLAIVE
int ConRef, ConJMC, ConTempRef, ConWrkPut, ConWrkGet;
 
/* --------------------------- Declaratie functies ---------------------- */
#include "KASSA.H"
/* ---------------------------------------------------------------------- */

CString PathSpoolToServer, JmcCmdFilepath, KasCmdFilepath;

CJmuDoc *pDoc=NULL,*pDocControle=NULL;
char* JMU_s;

void ReleaseEverything(void)
{
 
#if XP_KASSA
  DoneReaderEx();
#else
  if (IsEngineActive()) {
	RemoveCallback();
	StopEngine();
  }
#endif
  if (pAffDisplay) {
		//pAffDisplay->~CAffDisplay();
		delete pAffDisplay;
		pAffDisplay=NULL;
	}
	if (pCustDisplay) {
		//pCustDisplay->~CCustDisplay();
		delete pCustDisplay;
		pCustDisplay=NULL;
	}
	if (pDoc) {
		// pDoc->~CJmuDoc();
		delete pDoc;
		pDoc=NULL;
	};
	kasplu.~CKasPLU();
  kassys.~CKasSYS();
  kasusr.~CKasUSR();
  kaskrt.~CKasKRT();
  kasklt.~CKasKLT();
}

void ReaderCardActive()
{
  unkbchar(125*0x10000);
}

void prt_gr_windows_faktuur(char datum[9]);

int main(int argc, char *argv[])
{
  //AfxInitCommonControls();
  int z;
	TouchPanelFlag=true;
#if _DEBUG
  TouchPanelFlag=false;
#endif
  setlocale(LC_ALL, ""); // nodig voor CMarkup voor conversie UTF2A e.d. 
  
	//AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
	//AfxSocketInit(); IsOk=true;
	//AfxEnableControlContainer();
	//AfxInitRichEdit();

#ifndef _DEBUG
  SplashShow();  // show splash screen
#endif
  moinit(0,-1);
  SetProgramName("KeyConenTouch");
  ConStyle(CON_STYLE_NOBACKGROUND);
  cls();

   char buf[MAX_PATH];
  _getcwd(buf,MAX_PATH);
  PathSpoolToServer=buf;
	if (PathSpoolToServer.Right(1)!="\\") PathSpoolToServer+="\\";
  KasCmdFilepath = PathSpoolToServer+"Jmc2Kas.jam";

	if (!KassaTestConfigFlag) {
	  if (SUCCEEDED(SHGetFolderPath( NULL, CSIDL_COMMON_APPDATA, NULL, 0, buf ))) {
		  PathSpoolToServer = buf;
		}
		PathSpoolToServer += "\\Jamadata\\";
		CreateDirectory(PathSpoolToServer,NULL);
		PathSpoolToServer += "Spool\\";
		CreateDirectory(PathSpoolToServer,NULL);
		PathSpoolToServer += "ToServer\\";
		CreateDirectory(PathSpoolToServer,NULL);
	}
  JmcCmdFilepath=PathSpoolToServer+"Kas2Jmc4.Jam";  // 4-de JMC gebruiken van deze post

  ConRef=ConSelect(-1);
  ConTempRef=ConSelect(-1);
  ConWrkPut=ConSelect(-1);
  ConJMC=ConSelect(-1);
	ConWrkGet=ConSelect(ConRef);

  kasusr.pKasPLU=&kasplu;
  //if (argc>=2) movmem(argv[1],config,10);
  kassys.rd_kassys(0); 
  if (fref_sys<0) {printf("KASSYS.DAT -> File not found"); exit(1);}

 DWORD VolumeSerialNumber = 0;
  char txtbuf_[20];
  zeroes(txtbuf_, sizeof txtbuf_);
  GetVolumeInformation(NULL, NULL, NULL, &VolumeSerialNumber, NULL, NULL, NULL, NULL);
  sprintf_s(txtbuf_, 20, "%04X-%04X", HIWORD(VolumeSerialNumber), LOWORD(VolumeSerialNumber));
  int k;
  for (k = 0; k < 10; k++) if (txtbuf_[k]) txtbuf_[k] += k; // beetje vervormen
  if (txtbuf_[0]) {
	if (HDDSerialNr[0] == '?' || HDDSerialNr[0] == '\0') {
	  movmem(txtbuf_, HDDSerialNr, 10); kassys.upd_sys();
	}
	else {
	  int orig_key = 0;
	  if (cmpstr(txtbuf_, HDDSerialNr, 10)) {
		SplashText("!!!ONGELDIGE SERIENUMMER!!!   Druk op een toets...");
		redo_inp:;
		int key = kbchar();
		if (key & 0xFFFF0000) {
		  key /= 0x10000;
		  if (key >= 0 && key <= 9) key = '0' + key;
		  else key = -key; // keycoon = negatieve key
		}

		if (key > 255) key = key / 256;
		if (key == 104 && orig_key == 0) {
		  orig_key = key; goto redo_inp;
		}
		if (key == 110 && orig_key == 104){ // F4 + F10 overruled
		  movmem(txtbuf_, HDDSerialNr, 10); kassys.upd_sys();
		}
		else exit(1);
	  }
	}
  }


  disp_init(); disp_clr(0,0,80,25);
  lade_init(); 
  larg_init(); 
  scropen(2,"KasScr.scj");  
  mem_needed=0L;
  mem_needed+= art_count * (long)kasplu.art_size;
  if (bc_option>0) mem_needed+= (2*art_count) * (long)sizeof(int);/* ean-tab */
  mem_needed+= ext_count * sizeof(struct _extra);
  mem_needed+= key_count * (long)kasusr.key_size;
  mem_needed+= (VRK_COUNT * KLT_COUNT) * (long)sizeof(verkopen[0]);
  if (prx_count>PRX_COUNT) prx_count=PRX_COUNT;
  else if (prx_count<1) prx_count=1;
  kasklt.op_kasklt(1); 
  op_kasfac(3); 
  log_open(4,0); 
  kasusr.rd_kasusr(5); 
  kasplu.rd_kasplu(6); 

  mk_verkopen();
  op_kaswrk(10);
	kaskrt.op_kaskrt(11);
  SplashText("Initialising PRINTER ...");




	IsOk=true;
  if (!prt_fil) {
    prt_init();
    if (NoPrtCut==NO && ex_ticket!=-1) prt_hoofd(YES);/* om proper te beginnen */
    prt_close();
    if (model==1 || model==2) cust_init();
  }
  
  if (bc_option>=1 && bc_option<=4) UseSerialScanner(bc_option,2400,'N',8,1);
#if XP_KASSA
  MANAGER_DATA ManData; // eID reader
  memset(&ManData, 0, sizeof(MANAGER_DATA));
  if (fl_freedelity == NO) {  // eID NIET aankoppelen indien Freedelity 
	ManData.CardActive = (TManagerProc)&ReaderCardActive;
	InitReaderEx(&ManData); // eID native init
  }
#else
  if (fl_freedelity == NO) {  // eID NIET aankoppelen indien Freedelity
	StartEngine();
	for (z = 0; z < 5; z++) {// kaart mag er niet inzitten bij callback, want dan blokkeert het helemaal
	  if (IsCardPresent()) break;
	  Sleep(100);
	}
	if (z >= 5) SetCallback((CALLBACK_HANDLER)*readEID, "");
  }
#endif
//  pen_check(13,YES);
  exec_pen();
  disp_exit("");
	ReleaseEverything();
  _moexit(0);
	return 0;
}

static int copystring(char *buf, int pos, int buflen, char *s, int len)
{
  int i;

  while (len>0) {
    if (s[len-1]>' ') break;
    len--;
  }
  if (len<0) len=-len;
  for (i=0; i<len; i++) {
    if (pos>=buflen) break;
    if (*s==0) break;
    buf[pos++]=*s++;
  }
  return pos;
}
 
#define PROC_SEND2PEER (WM_USER + 2)
#define WM_JAMASHOW WM_USER+2
#define WM_ATTACH_NEW_JMDH (WM_USER + 20)

HWND JMD;

void UpdateOnJMC()
{
	_unlink(KasCmdFilepath);
	if (KassaTestConfigFlag) {
		int old_screen=ConSelect(ConJMC);
		cls();
		vdposp(12,20);
		tkdsp("Wacht nu op antwoord van JMC ...");
		kbcharnw();
		HWND JMChWnd=FindWindow(NULL,"JMC FOR KASSA");
		if (JMChWnd) PostMessage(JMChWnd,WM_KEYDOWN,VK_TAB,0);
		if (JMChWnd) PostMessage(JMChWnd,WM_KEYUP,VK_TAB,0);
		while (GetFileAttributes(KasCmdFilepath)==INVALID_FILE_ATTRIBUTES) {
			kbcharnw();
			Sleep(100);
		}
		Sleep(50);
	  cls(); // om de panels e.d. te clearen ....
		ConSelect(old_screen);
	}
	else {
		PostMessage(JMD,PROC_SEND2PEER,0,0);
	  int old_screen=ConSelect(ConJMC);
		ExecJamaLink("Terminal","",100+5,"THE_JMD"); // wacht 5 seconden op reactie van JMC, zo dan geen screen received, gewoon return doen !
	  cls(); // om de panels e.d. te clearen ....
		ConSelect(old_screen);
	}
}

void Ansi2JamaAsc(char *ps_,int len_)
{
	// voor ANSI
	static int outtab[] = { /* output convert table JAMASCII -> intern'l video */ // deze tabel komt uit JamaCon (ConScr.cpp)
	 /*  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F  */
		 126,126,126,126,126,126,126,  7,  8,126, 10,126,126, 13,126,126, /* 0X */
		 126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* 1X */
			32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, /* 2X */
			48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, /* 3X */
			64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, /* 4X */
			80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, /* 5X */
			96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111, /* 6X */
		 112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127, /* 7X */
		 0xE1,0xE0,0xE2,0xE4,0xE7,0xE9,0xE8,0xEA,0xEB,0xED,0xEC,0xEE,0xEF,0xF3,0xF2,0xF4,  // 8x 
		 0xF6,0xFA,0xF9,0xFB,0xFC,0xDC,176,0xA7,0x2588,0x2190,0x2192,0x2191,0x2193,0x20,0x20,0x20AC,  // 9X
		 126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* AX */
		 0x2592,0x2551,0x2550,0x255a,0x2551,0x2551,0x2554,0x2560,0x2550,0x255D,0x2550,0x2569,0x2557,0x2563,0x2566,0x256C, //BX
		 0x2592,0x2551,0x2550,0x255a,0x2551,0x2551,0x2554,0x2560,0x2550,0x255D,0x2550,0x2569,0x2557,0x2563,0x2566,0x256C, //BC
		 126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* DX */
		 126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* EX */
		 126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126};/* FX */

	int i;
  unsigned char u;

  for (i=0; i<len_; i++) {
    u=(unsigned char)ps_[i];
		if (!u) break;
    if (u>=128) {
			for (int j=1; j<255; j++) {
				if (u==outtab[j]) {
					u=j;
					break;
				}
			}
    }
    ps_[i]=u;
  }
}

#include "KasCommn.cpp"

void readEID(int dum)
{
  int z, key, save_screen,pos_;
	short int jj_,dd_,mm_,leeftijd_=0;
	short unsigned dt_bday_;
	CString cstr;


#if XP_KASSA
  WaitForCard(1);
#else
  for (z = 0; z < 15; z++) {
	if (IsCardPresent()) break;
	Sleep(100);
  }
  if (z >= 15) return;
#endif
 

  if (IsEIDCard()) {
	save_screen = ConSelect(ConTempRef);
	cls();
	ConSizeWindow(63, 18);
	ConStyle(0); // grijze achtergrond

	key = 0; // voor geval geen card gevonden wordt binnen de tijd (20 x 100 msec)
	while (true) {
	  scrnum = 0; scrget(2, 1504);
	  for (z = 0; z < 20; z++) {
		try {
#if XP_KASSA
		  ReadIDData(&eID);
		  ReadAddress(&eIDaddr);
#else
		  ReadIdentityA(&eID); // Jaak 10/2/22 was ReadIDData(&eID);
		  ReadAddressA(&eIDaddr);//  Jaak 10/2/22 was ReadAddress(&eIDaddr);
#endif
		}
		catch (...) {}
		if (eID.name[0] > ' ' && eIDaddr.municipality[0] > ' ') break;
		Sleep(100);
	  }
	  if (z == 20) break;
	  z = 1;
	  disp_key(55, 0, 8, 3, 22);
	  disp_key(5, 13, 10, 3, 119);
	  if (krt_bits) disp_key(17, 13, 10, 3, 113);
	  z++; // GDPR scrifld(z++,fm_os40,eID.nationalNumber);
	  Ansi2JamaAsc(eID.name, sizeof(eID.name)); // naar Jama-ascii
	  scrifld(z++, fm_os40, eID.name);
	  Ansi2JamaAsc(eID.firstName1, sizeof(eID.firstName1)); // naar Jama-ascii
	  scrifld(z++, fm_os40, eID.firstName1);
	  Ansi2JamaAsc(eIDaddr.street, sizeof(eIDaddr.street)); // naar Jama-ascii
	  scrifld(z++, fm_os40, eIDaddr.street);
	  scrifld(z++, fm_os7, eIDaddr.zip);
	  Ansi2JamaAsc(eIDaddr.municipality, sizeof(eIDaddr.municipality)); // naar Jama-ascii
	  scrifld(z++, fm_os25, eIDaddr.municipality);
	  cstr = eID.birthDate;	leeftijd_ = 0;
	  if (cstr.GetLength() == 8) {
		leeftijd_ = (short int)(atol(cstr.Mid(0, 4)));
		if (leeftijd_ > 1900) {
		  jddate(dateget(), &jj_, &mm_, &dd_); leeftijd_ = jj_ - leeftijd_;
		  mm_ = (short int)(atol(cstr.Mid(4, 2))); dd_ = atol(cstr.Mid(6, 2)); dt_bday_ = datejd(jj_, mm_, dd_);	if (leeftijd_ && dt_bday_ > dateget()) leeftijd_--;
		}
	  }
	  scrifld(z++, fm_ou2, &leeftijd_); if (leeftijd_ && leeftijd_ < 18) scrchat(z - 1, 0xB);  // GDPR scrifld(z++,fm_os25,(char *)(LPCTSTR)cstr);
	  key = scrupd(-1, 0xA0);
	  if (key & 0xFFFF0000) key /= 0x10000;
	  if (key == 22 || key == 119 || key == 113) break;
	}
	cls();
	ConSizeWindow(vdlen_h, vdlen_v);

	if (key == 113) kaskrt.dsp_krtinfo(2);

	if (key == 119) {
	  char buf[50];
	  p_lin = &p_vrk->lijn[p_vrk->used];
	  add_text(txttxt[96]);
	  strcpy(buf, txttxt[97]);
	  pos_ = copystring(buf, 2, 40, eID.name, 37);
	  if (pos_ < 35) { buf[pos_++] = ' '; copystring(buf, pos_, 40, eID.firstName1, 37); }
	  copystring(p_vrk->EidNaam, 0, 40, &buf[2], 37);
	  add_text(buf);
	  strcpy(buf, txttxt[98]);
	  copystring(buf, 2, 40, eIDaddr.street, 37);
	  copystring(p_vrk->EidStraat, 0, 40, &buf[2], 37);
	  add_text(buf);
	  strcpy(buf, txttxt[99]);
	  copystring(buf, 2, 40, eIDaddr.zip, 7);
	  copystring(p_vrk->EidPostCode, 0, 10, eIDaddr.zip, 7);
	  copystring(buf, 7, 40, eIDaddr.municipality, 25);
	  copystring(p_vrk->EidGemeente, 0, 25, eIDaddr.municipality, 25);
	  add_text(buf);
	  strcpy(buf, txttxt[100]);
	  copystring(buf, 8, 40, eID.nationalNumber, 20);
	  copystring(p_vrk->EidRRN, 0, 20, eID.nationalNumber, 20);
	  add_text(buf);
	  strcpy(buf, txttxt[101]);
	  add_text(buf);
	  disp_window();
	  p_vrk->ExtraTicket = true;
	}
	cls();
	ConSizeWindow(vdlen_h, vdlen_v);
	ConSelect(save_screen); disp_fl = YES;
#if !XP_KASSA
	DeactivateCard();
	kbtest(false); // om display-update te krijgen
	if (disp_fl) { disp_window(); disp_fl = NO; }
#endif
  }
}

void mk_verkopen(void)
{
  char *p;
  long len, needed;
 
  needed= (VRK_COUNT * KLT_COUNT) * (long)sizeof(verkopen[0]);
  verkopen=(struct s_verkopen *)getml(needed);
  if ((long)verkopen == 0L) disp_exit("GETML voor VERKOPEN werkt niet");
  p=(char *)verkopen; len=needed;
  while (len--) *p++=0;
}
 
void adj_verkopen(int vrk)
{
 /* opletten als we bij chk_kassier alles in 1 blok laten komen, dan problemen
    met leeg_sys e.d. */
 
  if (vrk>=0 && vrk<VRK_COUNT) vrk_ix=vrk;
  p_vrk = (struct s_verkopen *) &verkopen[vrk_ix*KLT_COUNT + klt_ix[vrk_ix]].used;
  *(txtvrk+2)='A'+vrk_ix;
  *(txtvrk+4)='1'+klt_ix[vrk_ix];
  disp_fl=YES; larg_next=10000;
}
 
void dup_nul(int count)
{
  while (count-->0) numkey(0);
}
 
void numkey(int toets)
{
  int j, fract;

//char buf_[25]; 
//bcopy("���������������", buf_,15);
//Ansi2JamaAsc(buf_,15);


  if (reg<0) reg=-reg;
  if (toets>=0 && toets<=9) {
    if (regix<(sizeof(regalfa)-1)) regalfa[regix++]=toets+'0';
    if (!reg_kom && reg_db<7) {
      reg*=10.; reg+=toets; reg_db++;
    }
    else if (reg_kom && reg_da<REG_DIGITS_AFTER) {
      j=reg_da; fract=10; while (j--) fract*=10;
      reg+=(double)toets/fract;
      reg_da++;
    }
    else if (!regalffl) beep_fl=BAD;
  }
  if (toets==10) {reg_kom=1; regalffl=NO;}
  if (toets==11) {reg_sign=0; regalffl=NO;}
  if (toets==12) {reg_sign=-1; regalffl=NO;}
  if (reg_sign<0) {
    reg=-reg;
  }
  disp_fl=YES;
}

void clr_ticket(int dum)
{
	if (p_vrk->used>0 && ConMessageBox("Bent U zeker dat het ganse ticket gewist mag worden ?","Wissen ticket",MB_YESNO | MB_ICONQUESTION)==IDNO) {
		return;
	}
	
	IsOk=true;
	if(fl_KasCtrl) LogThisAction(0,0,1);
	_clr_ticket();
	clear(0);
}

void pro_forma(int dum)
{
	double totaal,leeggoed, goederen;

	totaal=round_it(p_vrk->totaal[0],def_round);
  leeggoed=round_it(p_vrk->totaal[1],def_round);
  goederen=round_it(totaal-leeggoed-p_vrk->totvoorschot_r,def_round);

  if (goederen) add_einde(GRP_GOEDEREN,goederen);
  if (leeggoed) add_einde(GRP_LGMEE,leeggoed);
  add_einde(GRP_MEETOTAAL,p_vrk->totaal[0]);
  close_bon(NO,true);
}
 
void clear(int dum)
{
	if (regix==0 && p_vrk->used>0 && p_vrk->lijn[p_vrk->used-1].groep==GRP_ATTENTION) {
    _del_line(p_vrk->used-1);
	}
  clr_line(); beep_fl=GOOD;

#if _DEBUG
/*
	unkbchar(0x03);
	unkbchar('1');
	unkbchar('6');
	unkbchar('4');
	unkbchar('0');
	unkbchar('0');
	unkbchar('0');
	unkbchar('0');
	unkbchar('1');
	unkbchar('3');
	unkbchar('6');
	unkbchar('0');
	unkbchar('8');
	unkbchar('9');
	unkbchar(0x02);
*/
#endif

}

void clr_line(void)
{
  reg_aantal=0.;
  clr_reg();
  p_vrk->stuks_flag=NO;
}
 
void clr_reg(void)
{
  reg=0.; regalffl=YES; regix=0;
  reg_db=0; reg_da=0; reg_kom=0; reg_sign=0;
  disp_fl=YES;
}

int add_ean(char *ean)
{
  char FlesScanned, stuks_fl, PrevStuksFlag;
  int ix, idem_fl;
	char buf[1000];
 
  PrevStuksFlag=p_vrk->stuks_flag;
	ix=kasplu.find_ean(ean,CntFlesInBak);
  if (ix>=0) {
    FlesScanned=NO;
    if (ix>=1000000) {
      FlesScanned=YES;
      ix-=1000000;
    }
    plu_ix=ix;
    idem_fl=NO;
    if (bak_fles>=0) p_vrk->stuks_flag=bak_fles;
		else if (!p_vrk->stuks_flag) p_vrk->stuks_flag=FlesScanned;
    if (p_vrk->used>0) {
      ix=p_vrk->used-1;
      while (ix>0) {
			  if (p_vrk->lijn[ix].groep!=GRP_PKORT && p_vrk->lijn[ix].groep!=GRP_FKORT && !(p_vrk->lijn[ix].bits & AUTO_LEEG)) break;
        ix--;
      }
      if (compare(kasplu.art_info.code,p_vrk->lijn[ix].code,ARTCODE_LEN)==0) {
        stuks_fl = p_vrk->lijn[ix].bits & STUKS;
        if ((stuks_fl && p_vrk->stuks_flag) || (!stuks_fl && !p_vrk->stuks_flag)) {
          idem_fl=YES;
        }
      }
    }
    if (add_art(idem_fl)) beep_bad(); else beep_ok();
    bak_fles=-1; CntFlesInBak=-1;
    clr_line();
  }
  else {
    beep_fl=BAD;
		p_lin=(struct s_lijn *) p_vrk->lijn[p_vrk->used].text;
		p_lin->groep=GRP_ATTENTION;	
	  _clr_text(p_lin->text);
		sprintf(buf,"*** BARCODE: %s ***",ean);
		copynaam(buf,p_lin->text,40);
		p_lin++; p_vrk->used++; disp_fl=YES;
		p_vrk->AttentionFlag=TRUE;
		p_vrk->stuks_flag=PrevStuksFlag;
		bak_fles=-1; CntFlesInBak=-1;
		clr_line();
    return YES;
  }
  return NO;
}
    
void faktuur(int dum)
{
  char type;

  if (fakt_allow) {
    klant_nr=p_vrk->klant_nr;
    type=kasklt.SelectKlant(0);
    p_vrk->klant_nr=klant_nr;
    if (klant_nr) {
      type-='0';
      if (type<0) type=0;
      if (type<prx_count) {
        p_vrk->prx_ix=type;
        disp_fl=YES;
      }
    }
    if(p_vrk->klant_nr) kasklt.dsp_klantinfo();
  }
  else beep_fl=BAD;
}
 
void prx_upd(int dum)
{
  if(++p_vrk->prx_ix>=prx_count) p_vrk->prx_ix=0;
  disp_fl=YES;
}
 
void auto_leeg(int dum)
{
  p_vrk->leeg_flag^=1; disp_fl=YES;
}

void terug_leeg(int dum)
{
  p_vrk->leeg_flag^=2; disp_fl=YES;
}
 
void leeg_ok(int dum)
{
  int j, ix, end, first;
 
  if (leegok&1) {
    reg_aantal=-p_vrk->totaal[1];
    reg=groep_leeg;
    groep(0);
    goto endit;
  }
  first=p_vrk->used; end=first;
  for (ix=0; ix<first; ix++) {
    if ((p_vrk->lijn[ix].groep==groep_leeg) &&
           (!(leegok&2) || (p_vrk->lijn[ix].bits & AUTO_LEEG))) {
      for (j=first; j<end; j++) {
        if (!compare(p_vrk->lijn[j].code,p_vrk->lijn[ix].code,ARTCODE_LEN)) {
          p_vrk->lijn[j].aantal-=p_vrk->lijn[ix].aantal;
          break;
        }
      }
      if (j==end) {/* not found, add at tail */
        end++; p_vrk->used++;
        movmem(p_vrk->lijn[ix].text,p_vrk->lijn[j].text,sizeof(struct s_lijn));
        p_vrk->lijn[j].aantal = -p_vrk->lijn[j].aantal;
        if (p_vrk->lijn[j].bits && AUTO_LEEG) {
          p_vrk->lijn[j].bits ^= AUTO_LEEG;
        }
      }
      adj_lijn(j);
    }
  }
  for (j=first; j<=end; j++) {
    if (p_vrk->lijn[j].aantal==0.) {
      _del_line(j);
      end--;
      j--;
    }
  }
 endit:;
  art_calc(YES); beep_fl=GOOD;
}
 
void eenh_prijs(int dum)
{
  int ix;
  double new_price, old_price;
 
  beep_fl=BAD; ix=1;
  new_price=reg;
  if(new_price==0 && regalfa[0]=='\0') beep_fl = BAD; // men MOET iets (0) hebben ingevuld om hen 0 te maken
  else {
	while (p_vrk->used - ix >= 0) {
	  p_lin = (struct s_lijn *) p_vrk->lijn[p_vrk->used - ix].text;
	  if (p_lin->bits & AUTO_LEEG) {
		ix++;
	  }
	  else {
		if (p_lin->groep >= 0) {
		  old_price = p_lin->prijs;
		  p_lin->prijs = (float)new_price;
		  if (old_price && p_lin->prijs <= 0 && p_vrk->punten[p_vrk->used - ix] > 0) p_vrk->punten[p_vrk->used - ix] = 0; // bij gratis artikel ook punten op 0 zetten
  /* if (p_vrk->bdr2punt[p_vrk->used-ix]>0.) p_vrk->bdr2punt[p_vrk->used-ix]=p_lin->prijs;
  else */
		  if (p_lin->groep != 99 && p_vrk->punten[p_vrk->used - ix] == 0) p_vrk->bdr2punt[p_vrk->used - ix] = p_lin->prijs;
		  beep_fl = GOOD;
		  adj_lijn(p_vrk->used - ix); art_calc(YES); larg_next -= ix;
		}
		break;
	  }
	}
  }
  clr_line();
}
 
void maal(int dum)
{
  reg_aantal=reg; clr_reg();
}

void alg_korting(int dum)
{
  float getal;

  if ((getal=(float)reg)==0.) getal=(float)reg_aantal;
  p_vrk->alg_korting=getal;
  disp_fl=YES; clr_line();
}

void korting(int type)
{
  int groep, art_ptr;
  double getal;
 
  if ((p_vrk->used>=(LIN_COUNT-LIN_MARGIN)) || (reg==0. && reg_aantal==0.)) {beep_fl=BAD; goto end;}
  art_ptr=p_vrk->used-1;
  while (art_ptr>=0) {
    if (((p_vrk->lijn[art_ptr].bits & 0x82)==0) && (p_vrk->lijn[art_ptr].groep!=groep_leeg)) {
      if (p_vrk->lijn[art_ptr].groep < 0 || p_vrk->lijn[art_ptr].groep>999) {
        if (p_vrk->kort_flag==1 && p_vrk->lijn[art_ptr].groep==GRP_SUBTOT) {
          /* OK mag dus wel korting op subtotaal */
        }
        else {
          beep_fl=BAD; goto end;
        }
      }
      break;
    }
    art_ptr--;
  }
  if (art_ptr<0) {beep_fl=BAD; goto end;}
  if ((getal=reg)==0.) getal=reg_aantal;
  if (type==0) groep=GRP_FKORT;
  else if (type==1 || type==2) groep=GRP_PKORT;
  else goto end;
  p_lin=(struct s_lijn *) p_vrk->lijn[p_vrk->used].text;
  movmem(p_vrk->lijn[art_ptr].code,p_lin->code,sizeof(p_lin->code));
  p_lin->bits=p_vrk->lijn[art_ptr].bits & STUKS;
  if (type==2) p_lin->bits |= AUTO_LEEG;
  p_lin->btw=p_vrk->lijn[art_ptr].btw;
  p_lin->aantal=0.;
  p_lin->prijs=(float)getal;
  p_lin->groep=groep;
  adj_lijn(p_vrk->used);
  p_vrk->used++; art_calc(NO); disp_fl=YES; clr_line(); plu_ix=-1;
 end:;
}

void adj_lijn(int index)
{
  struct s_lijn *p_lin;
  double bedrag=0;
  int groep, prev;

  p_lin=(struct s_lijn *) p_vrk->lijn[index].text;
  groep=p_lin->groep;
  if (groep>=0 && groep<1000) {
    bedrag=p_lin->aantal * p_lin->prijs;
    if (lijn_round) bedrag=round_it(bedrag,def_round);
  }
  else if (groep>=1000 && groep<2000) bedrag=p_lin->totaal;
  else if (groep==GRP_FKORT) bedrag=-p_lin->prijs;
  else if (groep==GRP_PKORT) {
    if (index==0) {
      bedrag=0;
    }
    else {
      prev=index-1;
      while (p_vrk->lijn[prev].bits & AUTO_LEEG) prev--;
      bedrag = (p_lin->prijs/100.) * p_vrk->lijn[prev].totaal;
      bedrag=-round_it(bedrag,def_round);
    }
  }
  else if (groep==GRP_SUBTOT) bedrag=p_lin->totaal;
  else if (groep==GRP_TEXT) {
    p_lin->aantal=0;
    p_lin->prijs=0.;
    bedrag=0.;
  }

  p_lin->totaal=bedrag;
  if (p_lin->groep!=GRP_ATTENTION) adj_text(index);
  beep_fl=GOOD;
}
 
void stuks(int dum)
{
  p_vrk->stuks_flag^=1; disp_fl=YES;
}
 
void verkoper(int nr)
{
  if (!chk_kassier) {
    if(nr==2) VerkoperKleur=RGB(200,250,225); //blauw
    else if(nr==3) VerkoperKleur=RGB(255,150,100); // groen
    else VerkoperKleur=RGB(255,255,0); // geel
		disp_panel(0,1,50,4,0,VerkoperKleur);
 	  adj_verkopen(nr-1);
	}
}
 
void and_klant(int dum)
{
  klt_ix[vrk_ix]++;
  if (klt_ix[vrk_ix]>=KLT_COUNT) klt_ix[vrk_ix]=0;
  adj_verkopen(vrk_ix);
}
 
void plu(int type)
{
  int i, _ix;
 
/*
  if (type==1) {  veranderd op 13/06/2007
    i=regix;
    if (i>ARTCODE_LEN) i=ARTCODE_LEN;
    regalfa[i]=0; reg=0.;
    _ix=kasplu.plu_req(regalfa,ARTCODE_LEN);
  }
  else _ix=kasplu.search("",1);
*/
  i=regix;
  if (i>ARTCODE_LEN) i=ARTCODE_LEN;
  regalfa[i]=0;
  _ix=-1;
	if (i>0) {
	  _ix=kasplu.plu_req(regalfa,ARTCODE_LEN);
		if (_ix>=0) reg=0.;
	}
	CKasPLU::prx_ix=p_vrk->prx_ix;
	if (_ix<0 && type!=1) _ix=kasplu.search("",1);

  if (_ix>=0) {
    plu_ix=_ix;
    if (add_art(NO)) beep_fl=BAD; else beep_fl=GOOD;
    clr_line();
    clr_reg();
  }
  else beep_fl=BAD;
/*  clr_reg(); */
}

void test(int dum)
{
  char executed, printed=NO, buf[100], neg_fl;
  int aantal, len, i, testref, j, maxaant, leeg_save;
  long pos, testfilet;
 
/*
  if (sprook==3) {
    beep_fl=BAD;
    return;
  }
*/

  leeg_save=p_vrk->leeg_flag;
  if (testmax==0) testmax=1750/40;
  if (in_use(NO)) {beep_fl=BAD; goto end;}
  testref=dopen("KASTEST.DAT",RDWRMODE);
  if (testref<0) {beep_fl=BAD; goto end;}
	testfilet=getft(testref);
  FOREVER {
    pos=0L; executed=NO;
    FOREVER {
      dseek(testref,pos,0);
      len=dread(testref,buf,80);
      if (len<2) break;
      for (i=0; i<len; i++) {
        if (buf[i]<' ') break;   // bepaald einde lijn, is \r teken 
      }
      len=i;
 
      regix=0;
      for (j=0; j<len; j++) {
        if (buf[j]=='|') {			// zoek eerste delimiter en zet tekens ervoor in PLU
          regalfa[regix]='\0'; break;
        }
        regalfa[regix++]=buf[j];
      }
 
      reg_aantal=0.; neg_fl=NO;
      for (j+=1; j<len; j++) {
        if (buf[j]=='|') break;			// zoek tweede delimiter en zet tekens ervoor in AANTAL
        if (buf[j]=='-') neg_fl=YES;
        else reg_aantal=reg_aantal*10.+buf[j]-'0';
      }
      if (neg_fl) {
        reg_aantal= -reg_aantal;
        aantal=(int)(reg_aantal-.1);
      }
      else aantal=(int)(reg_aantal+.1);

      p_vrk->stuks_flag=NO; maxaant=3;
      if (buf[j+1]=='S' || buf[j+1]=='s') {p_vrk->stuks_flag=YES; maxaant=6;}

      if (reg_aantal>maxaant) {
        reg_aantal=1+rand()%maxaant;
        if (reg_aantal<1.) reg_aantal=1.;
      }
      else if (reg_aantal<-maxaant) {
        reg_aantal=(-1)-rand()%maxaant;
        if (reg_aantal>-1.) reg_aantal=-1.;
      }
      if (reg_aantal>=1. || reg_aantal<=-1.) {
        aantal-=(int)reg_aantal;
        beep_fl=GOOD;
        plu(1);
        if (beep_fl!=BAD) {
          executed=YES;
          j--;
          neg_fl=NO;
          if (aantal<0) {
            neg_fl=YES;
            aantal= -aantal;
          }

					if (aantal==0) {  // als het aantal 0 is, dan verander de hele lijn in ||| en spaties ...
					  for (j=0; j<len; j++) {
						  if (j<3) buf[j]='|';
							else buf[j]=' ';
						}
					}
					else {
						FOREVER {
							if (j<0 || buf[j]=='|') break;
							buf[j]='0'+aantal%10;
							aantal/=10;
							j--;
						}
						if (neg_fl && buf[j]=='|') buf[j+1]='-';
					}

          dseek(testref,pos,0L);
          dwrite(testref,buf,len);
          dflush(testref);
        }
      }
      else clr_line();
      pos+=(len+2);
      if (p_vrk->totaal[0]>testmax || p_vrk->used>30 || p_vrk->totaal[0]<(-testmax)) {
			  printed=YES;
        _testeinde();
      }
    }
    if (!executed) break;
    if (p_vrk->used) {printed=YES; _testeinde();}
  }
	chgft(testref,testfilet);
  dclose(testref);

  if (p_vrk->used) _testeinde();
  clr_line();
  beep_fl=GOOD;
 end:;
  if (!printed) {
	  prt_nl("");
	  prt_cod(2); prt_cod(3);
    prt_lin("*** TEST STATUS=");
		prt_char('A'+rand()%26);
		prt_nl(" ***");
		prt_cod(4);
		prt_hoofd(YES);
		prt_close();
	}

  p_vrk->leeg_flag=leeg_save;
}
 
void _testeinde(void)
{
  leeg_ok(0);
  einde(YES);
  p_vrk->leeg_flag=(p_vrk->leeg_flag&0xFE)|(rand()&1);
}
 
static void DisplayKeyboard(int x, int y, int x_adjust_,int y_adjust_, int soort_kb_) // soort_kb_ :0=ABCD, 1=AZERTY
{
  int xpos_,ypos_,xkeylen_,ykeylen_,k;
  char txt_[20],keytxt_[20];



  xkeylen_=5+x_adjust_; if(xkeylen_<1 || xkeylen_>8) xkeylen_=5;
  ykeylen_=2+y_adjust_;if(ykeylen_<1 || ykeylen_>5) ykeylen_=2;
  disp_panel(x,y,16*xkeylen_,4*ykeylen_,0,RGB(255,255,200)); 
  zeros(txt_,sizeof txt_);
  if(soort_kb_==1) bcopy("AZERTYUIOP",txt_,10);
  else bcopy("ABCDEFGHIJ",txt_,10);
  for(k=0;k<20;k++){  
    if(txt_[k]==0) break;
    zeros(keytxt_,sizeof keytxt_);
    keytxt_[0]=txt_[k]; xpos_=x+k*xkeylen_; ypos_=y; disp_ikey(xpos_,ypos_,xkeylen_,ykeylen_,2000+txt_[k],keytxt_,RGB(220,50,50));
  }
  zeros(txt_,sizeof txt_);
  if(soort_kb_==1) bcopy("QSDFGHJKLM",txt_,10);
  else bcopy("KLMNOPQRST",txt_,10);
  for(k=0;k<20;k++){  
    if(txt_[k]==0) break;
    zeros(keytxt_,sizeof keytxt_);
    keytxt_[0]=txt_[k]; xpos_=x+k*xkeylen_; ypos_=y+ykeylen_; disp_ikey(xpos_,ypos_,xkeylen_,ykeylen_,2000+txt_[k],keytxt_,RGB(220,50,50));
  }
  zeros(txt_,sizeof txt_);
  if(soort_kb_==1) bcopy("WXCVBN/@*,",txt_,10);
  else bcopy("UVWXYZ/@*,",txt_,10);
  for(k=0;k<20;k++){  
    if(txt_[k]==0) break;
    zeros(keytxt_,sizeof keytxt_);
    keytxt_[0]=txt_[k]; xpos_=x+k*xkeylen_; ypos_=y+ykeylen_*2; disp_ikey(xpos_,ypos_,xkeylen_,ykeylen_,2000+txt_[k],keytxt_,RGB(220,50,50));
  }
  disp_ikey(x,y+ykeylen_*3,xkeylen_*6,ykeylen_,2000+' '," ",RGB(220,50,50));
  zeros(txt_,sizeof txt_);bcopy("+-",txt_,2);
  for(k=0;k<20;k++){  
    if(txt_[k]==0) break;
    zeros(keytxt_,sizeof keytxt_);
    keytxt_[0]=txt_[k]; xpos_=x+6*xkeylen_+k*xkeylen_; ypos_=y+ykeylen_*3; disp_ikey(xpos_,ypos_,xkeylen_,ykeylen_,2000+txt_[k],keytxt_,RGB(220,50,50));
  }
  
  disp_ikey(x+xkeylen_*8,y+ykeylen_*3,xkeylen_*2,ykeylen_,2303,"WIS",RGB(0,127,0));
  
  disp_ikey(x+xkeylen_*10,y,xkeylen_,ykeylen_,2305,"DEL",RGB(0,127,0));
  disp_ikey(x+xkeylen_*11,y,xkeylen_,ykeylen_,2308,"\x9B",RGB(0,127,0));
  disp_ikey(x+xkeylen_*12,y,xkeylen_,ykeylen_,2304,"INS",RGB(0,127,0));
  disp_ikey(x+xkeylen_*10,y+ykeylen_,xkeylen_,ykeylen_,2306,"\x99",RGB(0,127,0));
  disp_ikey(x+xkeylen_*11,y+ykeylen_,xkeylen_,ykeylen_,2309,"\x9C",RGB(0,127,0));
  disp_ikey(x+xkeylen_*12,y+ykeylen_,xkeylen_,ykeylen_,2307,"\x9A",RGB(0,127,0));
  disp_ikey(x+xkeylen_*10,y+ykeylen_*2,xkeylen_*3,ykeylen_*2,2318,"ENTER",RGB(0,127,0));
  zeros(txt_,sizeof txt_);bcopy("789",txt_,3);
  for(k=0;k<20;k++){  
    if(txt_[k]==0) break;
    zeros(keytxt_,sizeof keytxt_);
    keytxt_[0]=txt_[k]; xpos_=x+xkeylen_*13+k*xkeylen_; ypos_=y; disp_ikey(xpos_,ypos_,xkeylen_,ykeylen_,2000+txt_[k],keytxt_,RGB(220,50,50));
  }
  zeros(txt_,sizeof txt_);bcopy("456",txt_,3);
  for(k=0;k<20;k++){  
    if(txt_[k]==0) break;
    zeros(keytxt_,sizeof keytxt_);
    keytxt_[0]=txt_[k]; xpos_=x+xkeylen_*13+xkeylen_*k; ypos_=y+ykeylen_; disp_ikey(xpos_,ypos_,xkeylen_,ykeylen_,2000+txt_[k],keytxt_,RGB(220,50,50));
  }
  zeros(txt_,sizeof txt_);bcopy("123",txt_,3);
  for(k=0;k<20;k++){  
    if(txt_[k]==0) break;
    zeros(keytxt_,sizeof keytxt_);
    keytxt_[0]=txt_[k]; xpos_=x+xkeylen_*13+xkeylen_*k; ypos_=y+ykeylen_*2; disp_ikey(xpos_,ypos_,xkeylen_,ykeylen_,2000+txt_[k],keytxt_,RGB(220,50,50));
  }
  disp_ikey(x+xkeylen_*13,y+ykeylen_*3,xkeylen_*2,ykeylen_,2000+'0',"0",RGB(220,50,50));
  disp_ikey(x+xkeylen_*15,y+ykeylen_*3,xkeylen_,ykeylen_,2000+'.',".",RGB(220,50,50));
}

void VKCadeauBon(void)
{

  p_lin=&p_vrk->lijn[p_vrk->used];
  p_lin->groep=GRP_CDBON_VRK; p_lin->totaal=reg;

  adj_lijn(p_vrk->used++); art_calc(NO);
  clr_line();
}

void uitgave(int direction)
{
  int save_ex_ticket,old_screen;
	char txt_reden[4][40];
  int k,key,z,curs=3;


  for(k=0;k<p_vrk->used;k++){ // moet leeg zijn behalve EID 
		if(p_vrk->lijn[k].aantal || p_vrk->lijn[k].code[0] || p_vrk->lijn[k].prijs || p_vrk->lijn[k].totaal) break; 
	}
	if(k<p_vrk->used) {beep_fl=BAD; goto skip;}
//  if (in_use(NO)) {beep_fl=BAD; goto skip;}
  p_lin=&p_vrk->lijn[p_vrk->used];
  if (direction>0) {p_lin->groep=GRP_DIVUITGAVE; p_lin->totaal=-reg;}
  else {p_lin->groep=GRP_DIVONTVANG; p_lin->totaal=reg;}

	zeros(txt_reden,sizeof txt_reden);
	////////////////

  old_screen=ConSelect(ConTempRef);

  ConStyle(0); // grijze achtergrond
  while(true){
    scrnum=0;scrget(2,1505); z=1;
		if(direction>0) scrifld(z++,fm_os10,"Uitgave");
		else scrifld(z++,fm_os10,"Inkomst");
		scrifld(z++,fm_od6_2,&reg);
		for(k=0;k<4;k++) scrifld(z++,fm_us40,txt_reden[k]);
    disp_ikey(2,10,20,2,106,"annuleer",KLEUR_FTOETS);
    disp_ikey(22,10,20,2,108,"neem aan",KLEUR_FTOETS);
    DisplayKeyboard(0,13,0,1,KeyboardType);
    key=scrupd(curs,0xA0); curs=3;
    if (key&0xFFFF0000) key/=0x10000;
		if(key==106) { ConSelect(old_screen); disp_fl=YES; goto skip;}
    if(key==108) break;
  }

  ConSelect(old_screen); disp_fl=YES;



	/////////////

  adj_lijn(p_vrk->used++); art_calc(NO);
  clr_line();
  p_lin=&p_vrk->lijn[p_vrk->used];
  add_text(txttxt[46]);
  for(k=0;k<4;k++) add_text(txt_reden[k]);
  //add_text("");
  //add_text("");
  //add_text("");
  add_text("");
  save_ex_ticket=ex_ticket;
  ex_ticket=2;
  einde(NO);
  _clr_ticket();
  disp_fl=YES;
  ex_ticket=save_ex_ticket;
 skip:;
}


void PrintLastFreedelityCard(void)
{
	char buf[50];
	CMarkup FredXml;
	CString cstr_;
 
  if (in_use(NO)) {beep_fl=BAD; goto skip;}

  if(FredXml.Load("Ticket.Out.xml")==false) goto skip;
    if (NoPrtCut == YES) prt_hoofd(NO);
	FredXml.ResetPos();
	FredXml.FindElem(_T("response"));
	  FredXml.IntoElem();
    FredXml.FindElem(_T("customer"));
		p_lin=&p_vrk->lijn[p_vrk->used];
		cstr_=""; cstr_+=FredXml.GetAttrib(_T("name"));cstr_+=" "; cstr_+=FredXml.GetAttrib(_T("firstname"));
		add_text(txttxt[96]);
		strcpy(buf,txttxt[97]);
		copystring(buf,2,40,(char *)(LPCTSTR)cstr_,37);
		add_text(buf);
		cstr_=""; cstr_+=FredXml.GetAttrib(_T("streetname"));cstr_+=" "; cstr_+=FredXml.GetAttrib(_T("number"));
		strcpy(buf,txttxt[98]);
		copystring(buf,2,40,(char *)(LPCTSTR)cstr_,37);
		add_text(buf);
		strcpy(buf,txttxt[99]);
		cstr_=""; cstr_+=FredXml.GetAttrib(_T("postal"));cstr_+=" "; cstr_+=FredXml.GetAttrib(_T("city"));
		copystring(buf,2,40,(char *)(LPCTSTR)cstr_,37);
		add_text(buf);
		strcpy(buf,txttxt[100]);memcpy(&buf[2],"          ",10);	add_text(buf);
		cstr_=""; cstr_+=FredXml.GetAttrib(_T("points"));
		copystring(buf,2,40,txttxt[77],15);copystring(buf,18,40,(char *)(LPCTSTR)cstr_,10);
		add_text(buf);
		strcpy(buf,txttxt[101]);
		add_text(buf);
    prt_body(2);
	if (NoPrtCut == NO) prt_hoofd(YES); 
	else { prt_nl(" ");	prt_nl(" "); }
    _clr_ticket();
    prt_close();
    disp_fl=YES;
skip:;
}

void geldlade(int dum)
{
  int j;
  unsigned byte;
 
  if (PWOpenLade) {
	  if (PWOpenLade==reg) {
  	  clr_line(); 
		}
		else return;
	}
	if(fl_KasCtrl) LogThisAction(0,0,3);
	if (fl_open_lade) {
    if (in_use(NO)) {beep_fl=BAD; goto skip;}
    add_einde(GRP_OPENLADE,0.);
    close_bon(YES,true);
  }
  byte= 1<<(vrk_lade[vrk_ix]-1);
  for (j=0; j<10; j++) {
    if (valuta[j].lade>0 && valuta[j].lade<=MAX_LADE) {
      byte|=(1<<(valuta[j].lade-1));
    }
  }
  o_lade(byte);
  prt_close();
/**** mag weg als alles goed werkt
  if (mulfunok) comm8751(0x47,byte);
  else {
    for (j=1; j<=MAX_LADE; j++) {
      if (lade_used[j]) {
        lade_open(j);
        wait=get_hun()+140;
        while (wait>get_hun());
        lade_dicht(j);
        wait=get_hun()+10;
        while (wait>get_hun());
      }
    }
  }
*****   tot hier ***********/
 skip:;
}
 
void groep(int dum)
{
  long groep;
 
  groep=(long)reg; beep_fl=BAD;
  if (reg_aantal==0. || groep<1 || groep>99) goto end;
  p_lin=(struct s_lijn *) p_vrk->lijn[p_vrk->used].text;
  p_lin->aantal=1.;
  p_lin->prijs=(float)reg_aantal;
  p_lin->groep=(short)groep;
  p_lin->btw=grp_info[groep].btw;
  adj_lijn(p_vrk->used++);
  art_calc(NO); disp_fl=YES; plu_ix=-1;
  beep_fl=GOOD;
 end:;
  clr_line();
}
 
void ean(int dum)
{
  regalfa[regix]=0; reg=0.;
  add_ean(regalfa);
  disp_fl=YES;
  clr_line();
  clr_reg();
}
 
void idem(int dum)
{
/*  if (plu_ix>=0) { */
    if (add_art(YES)) beep_fl=BAD; else beep_fl=GOOD;
    clr_line();
    /*
  }
  else beep_fl=BAD;
  */
}
 
//void subtotaal(int dum)
//{
//  if (p_vrk->used>0 && p_vrk->lijn[p_vrk->used-1].groep!=GRP_SUBTOT) {
//    p_lin=&p_vrk->lijn[p_vrk->used];
//    p_lin->groep=GRP_SUBTOT; p_vrk->used++;
//    art_calc(NO); disp_fl=YES; clr_line(); plu_ix=-1;
//  }
//  else beep_fl=BAD;
//}
 
void subtotaal(int dum)
{
  int key, z, old_screen;
  char verv_tekst_[40];

  zeros(verv_tekst_, sizeof verv_tekst_);
  if (p_vrk->used > 0 && p_vrk->lijn[p_vrk->used - 1].groep != GRP_SUBTOT) {
	p_lin = &p_vrk->lijn[p_vrk->used];
	p_lin->groep = GRP_SUBTOT; p_vrk->used++;
	art_calc(NO); disp_fl = YES; clr_line(); plu_ix = -1;
	   	 
	// JAAK 12/05/2023: AANPASSING OM EEN TEKST AF TE DRUKKEN IPV DE DETAIL, NOG PROBLEEM BIJ OPLADEN BON, DUS VOORLOPI NIET ACTIEF

	//old_screen = ConSelect(ConTempRef);
	//cls();
	//ConStyle(0); // grijze achtergrond
	//while (true) {
	//  scrnum = 0; scrget(2, 1507); z = 1;
	//  scrifld(z++, fm_od6_2, &p_lin->totaal);
	//  scrifld(z++, fm_us20, verv_tekst_);
	//  disp_ikey(2, 10, 20, 2, 106, "annuleer", KLEUR_FTOETS);
	//  disp_ikey(22, 10, 20, 2, 108, "neem aan", KLEUR_FTOETS);
	//  DisplayKeyboard(0, 13, 0, 1, KeyboardType);
	//  key = scrupd(2, 0xA0);
	//  if (key & 0xFFFF0000) key /= 0x10000;
	//  if (key == 106) break;
	//  if (key == 108) {
	//	if (verv_tekst_[0]) {
	//	  _clr_text(p_lin->text);
	//	  copynaam(verv_tekst_, p_lin->text + POS_NAAM, POS_TOTAAL - POS_NAAM);
	//	  p_lin->bits = 1;

	//	}
	//	else p_lin->bits = 0;
	//	break;
	//  }
	//}
	//ConStyle(CON_STYLE_NOBACKGROUND);
	//cls();
	//ConSelect(old_screen);
	//if (key == 106) beep_fl = BAD;
	//else {
	//  p_lin->groep = GRP_SUBTOT; p_vrk->used++;
	//  art_calc(NO); disp_fl = YES; clr_line(); plu_ix = -1;
	//}
  }
  else beep_fl = BAD;
}



void sel_kassier(int dum)
{
  int key, old_screen;
 
  if (in_use(YES)) beep_fl=BAD;
  else {
    FOREVER {
      old_screen=ConSelect(ConTempRef);
      ConStyle(CON_STYLE_NOBACKGROUND);
      cls();
      disp_vid(19, 4,txttxt[62],0);
      disp_key(30, 9,20,6,18);
      ss_enable=YES;
      bc_allowed=bc_option;
      key=kbchar();
      if (key==251*256) key=-1;
      else key/=0x10000;
      bc_allowed=NO;
      ss_enable=NO;
      ConSelect(old_screen);
      if (key==-2) {
// winkassa nog op te lossen mvg
//        key=bc_process(NO);/* do not execute the rout() */
        if (key<=0) goto next;
      }
      if (key==18) swap(0);
      else {
        if (key>=95 && key<=97) {adj_verkopen(key-95); break;}
      }
     next:;
    }
  }
}
 

void swap(int dum)
{
  long needed;

  if (in_use(YES)) beep_fl=BAD;
  else {
    cust_init();
    needed= (VRK_COUNT * KLT_COUNT) * (long)sizeof(verkopen[0]);
    rlsml((char *)verkopen,needed);
  	ReleaseEverything();
		disp_exit("");
	}
}

int in_use(char all)
{
  int j;

  if (all) {
    for (j=0; j<VRK_COUNT*KLT_COUNT; j++) {
      if (verkopen[j].used>0) return YES;
    }
  }
  else if (p_vrk->used>0) return YES;
  return NO;
}

void _controle(int dum)
{
  if (in_use(NO)) beep_fl=BAD;
	else {
		get_memcumul();
		controle(NO);
		rls_memcumul();
	}
}

void _menu_bestel(int dum)
{
  kaskrt.MenuBestelLijsten();
}



void diversen(int dum)
{
  char sc_flag, buf[6], opnieuw, datum[9], ean[25];
	bool stuksfl;
  int _nr, key, k,art_ptr, old_screen;
	short int jj, mm, dd;
  unsigned _faktnr, _jddatum;
  char nm_pdffile[20];
  CFile fil;
  CString cstr_;
     
	old_screen=ConSelect(ConTempRef);
	ConStyle(CON_STYLE_NOBACKGROUND);
  cls();

  opnieuw=YES;
  ticketnr=log_getticket() - 1; _nr=ticketnr;
  if (!ex_ticket) ex_ticket=1;
  sc_flag=NO; /* DOS EXTENDER SC_TEST(); */
  FOREVER {
    if (opnieuw) {
      disp_clr(0,0,80,25);
			art_ptr=-1;
      if (ext_count && p_vrk->AttentionFlag && p_vrk->used>0) {
        for (art_ptr=p_vrk->used-1; art_ptr>0; art_ptr--) {
					if ((p_vrk->lijn[art_ptr].bits & 0x82)==0) break;
				}
				if (art_ptr>0) {
  				if (compare(p_vrk->lijn[art_ptr-1].text,"*** BARCODE: ",13)==0) {
						disp_key( 0, 0,18,1,109);
						for (k=0; k<sizeof(ean); k++) {
							ean[k]=p_vrk->lijn[art_ptr-1].text[13+k];
							if (ean[k]<'0' || ean[k]>'9') break;
						}
						ean[k]=0;
					}
					else art_ptr=-1;
				}
			}
			disp_key(21, 0,8,3,22);
      disp_key(21, 3,18,3,85);
      disp_key(0 , 3,18,3,102);
      disp_key(0 , 6,18,3,103);
      if(p_vrk->fakt_type==0) disp_key(0 , 9,18,3,128); // cadeaubon enkel tonen indien partickuler
      if (sc_flag) disp_key(21, 6,16,3,87);
      if (!no_prtkas) disp_key(45,9,23,3,98);
			disp_key(45,12,23,3,122);
			if (BestelButtonDisplay) disp_key(45,15,23,3,123);
			disp_key(21, 9,14,3,126);
      disp_key(21,12,14,3,99);
      disp_key(21,15,14,3,100);
      disp_vid(21,19,txttxt[48],1);
                                           // int2str(ticketnr,txttxt[49]+32,5);
 //     int2str(ticketnr,buf,5);cstr_=CString(txttxt[49]); cstr_.Replace("xxxxx",buf);
  //    disp_vid(21,20,cstr_.GetBuffer(100),0);
			disp_key(34,21,11,2,44); 
			disp_ikey(0,21,18,3,198,txttxt[107],RGB(0,127,0)); // lees Eid-kaart
			if(fl_freedelity){
			  disp_key(46,21,14,2,127);  // loyalty card Freedelity
              disp_ikey(60,21,14,2,199,txttxt[77],RGB(0,127,0)); // punten totaal
			}
      disp_key(29,23,6,2,83);
      disp_key(44,23,6,2,84);
      disp_key(75,24,4,1,104);
      beep_fl=GOOD;
      opnieuw=NO;
    }
    buf[5]=0; int2str(_nr,buf,5); disp_vid(37,24,buf,0);
    if (ex_ticket==-1) {
      sprintf(buf," - ");
    }
    else {
      buf[2]=0; int2str(ex_ticket,buf,2);
    }
    disp_vid(39,3,buf,0);
    key=kbchar();
    if (key==251*256) key=-1;
    else key/=0x10000;
    beep_fl=GOOD;
    if (key==22) break;
    switch (key) {
      case 44:
        if (in_use(NO)) beep_fl=BAD;
        else {
          log_loadticket(_nr);
#if CONTROL2PDF
		  char *b;
		  b = new char[CTRLPDFSIZE];
		  unsigned short int *w = (unsigned short int *)b;

		  w[0] = 0x09B0;
		  w[1] = 0x0DB4;
		  w[2] = 0x0000;
		  w[3] = 0x0056;
		  w[4] = 0x0076;
		  w[5] = 0x0076;
		  w[6] = 0x0000;
		  w[7] = 0x0304; /// was 0x0304;
		  w[8] = 0x0B06;
		  w[9] = 0x0450;
		  w[10] = 0x0100;
		  w[11] = 0x0000;
		  JMU_s = (char *)&w[12];
		  JMU_s = CopyString(JMU_s, "\xE0\xD4[landscape;]|\xF0");
		  TotSpoolBytes = 50;
			//		  PrintControl2PDF = NO;

#endif
		  if (NoPrtCut == YES) prt_hoofd(YES);
          prt_body(2);
		  if (NoPrtCut == NO) prt_hoofd(YES); 
		  else { prt_nl(" ");	prt_nl(" "); }
          for (k=0; k<p_vrk->used; k++) {
            if (p_vrk->lijn[k].groep==GRP_FAKT) {
              if (p_vrk->lijn[k].btw==2) {
                _jddatum=jddatum; _faktnr=faktnr;
                klant_nr=(int)p_vrk->lijn[k].aantal;
                kasklt.get_klant();
                faktnr=(unsigned int)p_vrk->lijn[k].prijs;
                jddatum=(unsigned int)p_vrk->lijn[k].totaal;
                jddate(jddatum,&jj,&mm,&dd);
                int2str(jj,&datum[6], 2);
                int2str(mm,&datum[3],-2); datum[5]='/';
                int2str(dd,&datum[0],-2); datum[2]='/';
                datum[8]=0;
                prt_gr_faktuur(datum);
                jddatum=_jddatum; faktnr=_faktnr;
              }
            }
          }
          _clr_ticket();
#if CONTROL2PDF
		  if (PrintControl2PDF) {
			int len = (JMU_s - b);

			fil.Open("Ticket.spl", CFile::modeCreate | CFile::modeWrite);
			fil.Write(b, len);
			fil.Close();

			//		if(pDocControle==NULL){
			pDocControle = new CJmuDoc();

			pDocControle->ReadDocument("Ticket.spl", 0, true);
			for (int j = 0; j < 4; j++) {
			  pDocControle->BedrukkingFlag[j] = false;
			}
			memset(nm_pdffile, 0, sizeof nm_pdffile);
			jddate(lst_dag, &jj, &mm, &dd);
			sprintf_s(nm_pdffile, 20, "Ticket %05d.pdf", _nr);
			pDocControle->Convert2Pdf("Ticket.spl", nm_pdffile); // "Controle.pdf");
			CFile::Remove("Ticket.spl");
			//if (pDocControle) {
			//	delete pDocControle;
			//	pDocControle=NULL;
			//};
			::ShellExecute(NULL, "OPEN", nm_pdffile, NULL, NULL, SW_SHOW);
			//	KASSA LOOPT VAST (CONSELECT) ALS IK DIT DOE : 	::ShellExecute(NULL,"OPEN","Controle.pdf",NULL,NULL,SW_SHOW);
			// Jaak 23/03/22  	PrintControl2PDF = NO; // uit veiligheid
		  }
#endif

#if CONTROL2PDF
		  delete[] b;
#endif
		  prt_close();
          goto end;
        }
        break;
      case 83:
        if (_nr>1) _nr--; else beep_fl=BAD;
        break;
      case 84:
        if (_nr<ticketnr) _nr++; else beep_fl=BAD;
        break;
      case 85 :
        ex_ticket++;
        if (ex_ticket>=5) ex_ticket=-1;
        if (ex_ticket==0) ex_ticket=1;
        kassys.upd_sys();
        break;
      case 87: /* DOS EXTENDER SC_SWITCH(0);*/ break;
      case 98:
        prt_kas(0);
        disp_key(72,9,8,3,13);
        break;
			case 126: vkpda_disp(); goto end;
      case 99:  wrk_put(-1); goto end;
      case 100: wrk_get(-1); goto end;
      case 102: ConSelect(old_screen); uitgave( 1); goto ret;
      case 103: ConSelect(old_screen); uitgave(-1); goto ret;
      case 104: ConSelect(old_screen); test(0); goto ret;
      case  13: wis_kas(); goto end;
      case 109: 
				stuksfl=false;
				if (p_vrk->lijn[art_ptr].bits&STUKS) stuksfl=true;
				kasplu.anew_ean(p_vrk->lijn[art_ptr].code,ean,stuksfl);
				_del_line(art_ptr-1);
				disp_fl=YES;
				goto end;
	  case 122: _controle(0); goto end; 
	  case 123: _menu_bestel(0); goto end;
	  case 127 : // call freedelity voor geselecteerd ticket
        if (in_use(NO)) beep_fl=BAD;
        else {
 		  if(DumpTicketToFreedelityXml(_nr)) CallFreedelityExe();
          goto end;
        }		
		break;
      case 128: ConSelect(old_screen); VKCadeauBon(); goto ret;
	  case 198 : // Eid lezen voor klanten met Freedelity
		 if(fl_freedelity){  // eID tijdelijk aankoppelen en dan direct closen voor Freedelity 
			ConSelect(old_screen);
#if XP_KASSA
            MANAGER_DATA ManData; // eID reader
			memset(&ManData,0,sizeof(MANAGER_DATA));
			ManData.CardActive=(TManagerProc)&ReaderCardActive;
			InitReaderEx(&ManData); // eID native init
			readEID(0);
			DoneReaderEx();
#else
		    if (!IsEngineActive()) StartEngine();
			readEID(0);
			StopEngine();
#endif
			goto ret;
		 }
		 else {
		   ConSelect(old_screen);
//		   SetCallback((CALLBACK_HANDLER)*readEID, "");
		   readEID(0);
		   goto ret;
		 }
  		break;
	  case 199 : // druk puntentotaal van laatste klant
		PrintLastFreedelityCard(); goto end;
  		break;
      default: beep_fl=BAD; break;
    }
  }
 end:;
  ConSelect(old_screen);
 ret:;
}

void ticket(int onlydisplay)
{
  char buf[55];
  int j, key, first, nr_, aantal, used, x, y, attr, selected, old_screen;
  long mixpromo_nr_;
  double aantgoed;
 
  old_screen=ConSelect(ConTempRef); 
  ConStyle(CON_STYLE_NOBACKGROUND);
  cls();

  disp_panel(15, 0, 50,  3, PANEL_VER_SMALLER | PANEL_WITH_EDGE, RGB(255,255,0));
  disp_panel(15, 2, 50, 23, PANEL_VER_SMALLER | PANEL_WITH_EDGE, RGB(255,255,0));
 
  disp_key(71, 0,8,1,22);
  disp_key(71, 2,8,3,23);
  disp_key(71,22,8,3,24);
  if(onlydisplay==0) disp_key( 0, 2,8,3,25);
  beep_fl=NO;
  first=0; used=p_vrk->used; selected=-1;
  disp_vid(16,1,txttxt[3],0); disp_vid(44,1,txttxt[2],0);
  FOREVER {
    aantgoed=p_vrk->aantal[0] - p_vrk->aantal[1];
    conv_getal(aantgoed        ,buf,8,0,2); buf[8]=0; disp_vid(23,1,buf,2);
    conv_getal(p_vrk->totaal[0],buf,10,0,def_digits);buf[10]=0;disp_vid(52,1,buf,2);
    aantal=21;
    if ((first+aantal)>used) aantal=used-first;
    for (j=0; j<aantal; j++) {
      if (j+first==selected) attr=8; else attr=2;
      sprintf(buf,"[%3d]",first+j+1); 
      if (!(p_vrk->lijn[first+j].bits & AUTO_LEEG)) disp_vid(16,3+j,buf,attr);
	  else  disp_vid(16, 3 + j, "     ", attr);
      disp_vid(22,3+j,p_vrk->lijn[first+j].text,attr);
    }
    for (j=aantal; j<21; j++) {
      disp_vid(16,3+j,"                                              ",2);
    }
    key=kbchar();
    if (key==0x02) {
		  unkbchar(0x02);
			break;
		}
    if (key==251*256) key=-1;
    else key/=0x10000;
    //disp_vid(15,0,scr2[0],0);
    if (onlydisplay==0 && key==25) {
      if (selected>=0) {
        FOREVER {
		  if(fl_KasCtrl) LogThisAction(0,selected,2);
		  if (!(p_vrk->lijn[selected].bits & AUTO_LEEG)) mixpromo_nr_ = p_vrk->lijn[selected].PromoGroepsCode;
          _del_line(selected); used=p_vrk->used;
          if (!(p_vrk->lijn[selected].bits & AUTO_LEEG)) break;
        }
		  if (mixpromo_nr_) { // promo herberekenen functie van nieuwe aantallen  
			nr_ = -1;
			for (j = 0; j < p_vrk->used; j++) {
			  if (!(p_vrk->lijn[j].bits & AUTO_LEEG) && mixpromo_nr_ == p_vrk->lijn[j].PromoGroepsCode) nr_ = j;
			}
			if (nr_ >= 0) {
			  int pluix = kasplu.plu_req(p_vrk->lijn[nr_].code, ARTCODE_LEN);
			  CalcArtikelPromo(nr_);
			  used = p_vrk->used; first = 0;
			}
		  }
        art_calc(YES);
        disp_large();
        beep_fl=GOOD;
      }
      else {
        ConMessageBox(txttxt[1],"Wissen lijnen",MB_ICONEXCLAMATION|MB_OK);
        beep_fl=BAD;
      }
    }
    selected=-1;
    if (onlydisplay==0 && key==-1) {
      x=mspos_h; y=mspos_v;
      beep_fl=BAD;
      if (y>=3 && y<=23 && x>=16 && x<=62) {
        selected=first+y-3; beep_fl=GOOD;
        if (p_vrk->lijn[selected].bits & AUTO_LEEG) {
          selected=-1; beep_fl=BAD;
        }
      }
    }
    if (key==22) break;
		else if (key==23) {first-=21; beep_fl=GOOD;}
    else if (key==24) {first+=21; beep_fl=GOOD;}
    if (first > used) first-=21;
    if (first<0) first=0;
  }
  beep_fl=GOOD; cls();
  ConSelect(old_screen);
}

void einde_zn_ticket(int dummy)
{
  char suspendedsave=PrtSuspended;
  PrtSuspended=2;  // als dit op YES staat, dan wordt hij terug gereset in closebon
  einde(false);
  PrtSuspended=suspendedsave;
}

void einde_met_btwtab(int dummy)
{
  char btw_holland_save = p_vrk->btw_holland;
	p_vrk->btw_holland=YES;
	einde(false);
	p_vrk->btw_holland=btw_holland_save;

}

/* socket modules */

WSADATA WSAData;
SOCKET sock=INVALID_SOCKET;

void SocketClose(SOCKET sock)
{
  try {
   closesocket(sock);
   // WSACleanup();
  }
	catch(...) {
  }
}

SOCKET SocketOpen(const char *hostname, unsigned short portnum)
{ 
	struct sockaddr_in sa;
  struct hostent     *hp;
  SOCKET s;
	unsigned long parm;
	long ret, err;


  try {
		hp = gethostbyname(hostname);
		if (hp == NULL) { //7 we don't know who this host is 
		  ret=WSAGetLastError();
			char buf[100];
			sprintf(buf,"WSAGetError = %6d\r\n",ret);
			tkdspnl(buf); kbcharnw();
			return INVALID_SOCKET;
		}

		memset(&sa,0,sizeof(sa));
		memcpy((char *)&sa.sin_addr, hp->h_addr, hp->h_length);   // set address
		sa.sin_family = hp->h_addrtype;
		sa.sin_port = htons((u_short)portnum);

		s = socket(hp->h_addrtype, SOCK_STREAM, 0);
		if (s == INVALID_SOCKET)
			return INVALID_SOCKET;

		// set to non-blocking mode 
		parm=1;
		ret=ioctlsocket(s,FIONBIO,&parm);
		ret=GetLastError();
		
		// try to connect to the specified socket 

		ret=connect(s, (struct sockaddr *)&sa, sizeof sa);
		err=WSAGetLastError();
		Sleep(500);
		ret=send(s,"?\r\n",3,0); // om te zien of het kanaal open is, zo ja dan ontvangen we info over betaalterminal !
  	err=WSAGetLastError();
		if (ret==SOCKET_ERROR) {
			closesocket(s);
			Sleep(500);
			s=INVALID_SOCKET;
		}

		return s;
  }
  catch(...) {
  }

	return INVALID_SOCKET;
}

void SocketSend(SOCKET sock, int size, char *s)
{
  int i;
  
  try {
		i=send(sock, s, size,0);
		if (i!=size) {
			//printf("Problems with send through socket !\r\n");
		}
  }
  catch(...) {
  }
}

int SocketRecv(SOCKET sock)
{
  unsigned char byte;
	int ret;
  unsigned long l;

  ret=-1;
	try {
		if (ioctlsocket(sock,FIONREAD,&l)) l=0;
		if (sock!=INVALID_SOCKET && l) {
      ret=recv(sock,(char *)&byte,1,0);
 		  if (ret==SOCKET_ERROR) ret=-1;
			else ret=byte;
		}
  }
  catch(...) {
  }
  return ret;
}

int DoPayCard(int groep)  // return : 0 -> Niet-Betaald,  1 -> Bankcontact, 2 -> Kredietkaart, 3 -> Mobiel, 4 -> Sodexo, 5 -> Edenred, 6 -> PayFair/Monizze, 7 -> RES
{
  int old_screen, i, key, byte, answerlen, TypeKaart=0;
	char buf[100], paybuf[100],answer[100], *BetType, state;
	bool errflag=false, waitflag=false;
	time_t PayStartTim=0, tim;
  SOCKET ComSock;

	old_screen=ConSelect(ConTempRef); 
  ConStyle(CON_STYLE_NOBACKGROUND);
retry:;
	cls();
	ConSizeWindow(25,7);
  disp_panel(0,0,40,12,0,RGB(255,255,0));
  disp_ikey(19,0,6,1,22,"STOP",RGB(255,0,0));
	 
	sprintf(buf,"%12.2f",reg);
	for (i=0; i<12; i++) {      // de setlocale zorgt voor , ipv .
		if (buf[i]==',') {
			buf[i]='.';
			break;
		}
	}

	for (i=0; i<12; i++) {
		if (buf[i]>' ') {
			tkdsp(&buf[i]);
			break;
		}
	}
	if (groep == GRP_EMAALTIJD) BetType = "M"; // elec. maaltijdcheques
	else if (groep == GRP_EECOCHEQUE) BetType = "E"; // elec. ECOcheques
	else if (groep == GRP_ECADEAUBON) BetType = "K"; // elec. CADEAUbons
	else if (groep == GRP_ECONSUMBON) BetType = "U"; // elec. CONSUMPTIEbons
	else if (groep==GRP_MOBIEL) BetType="P";
	else if (groep==GRP_CREDIT) BetType="C";
	else if(CreditCardViaBetaalterminal=='J') BetType="A"; // creditkaarten ook toelaten via betaalautomaat
	else BetType="B";
	if (Windows95) tkdspnl("EUR");
	else tkdspnl("\x9F");
  tkdspnl("Betaalterminal?...");
  state=0; answerlen=0; PayStartTim=0;
	int cnt=0;
	while (true) {
  	key=kbcharnw();
		if (key==999*0x10000) goto retry;
		if (key==0x0100 || key==0x1200 || key==0x160000) break;
    if (state==0) {
  		ComSock=SocketOpen(PayCardServer, groep==GRP_CASHAUT ? 4998 : 4999);
			cnt++;
			if (ComSock!=INVALID_SOCKET) {
				vdchar(0xEF);
				tkdsp("Betaalterminal: OK!\r\n");
				state=1;
			}
		}
		if (state==1) {
			sprintf(paybuf,"*%1s%s\r\n",buf,BetType);
  		SocketSend(ComSock,16,paybuf);
			state=2;
		}
    byte=SocketRecv(ComSock);
  	if (byte!=-1) {
		  answer[answerlen++]=byte;
			if (byte=='\n' || answerlen==40) {
				answer[answerlen]=0;
				if (answer[0]=='!') {
				  if (compare(answer,"!LOCK",5)==0) {
					  disp_ikey(19,0,6,1,1,"STOP",RGB(250,250,250));
						time(&PayStartTim);
					}
					if (compare(answer,"!UNLOCK",7)==0) {
					  disp_key(19,0,6,1,22);
					  PayStartTim=0; 
					}
					if (compare(answer,"!BUSY",5)==0) {
						tkdspnl("Reeds in gebruik!");
						SocketClose(ComSock);
					  disp_ikey(0,4,20,2,999,"Probeer opnieuw",RGB(0,127,0));
						continue;
					}
					if (compare(answer,"!CHECK",6)==0) {
					  tkdspnl("Betaling niet gegarandeerd!");
						tkdspnl("Controleer afgedrukt ticket");
						waitflag=true;
						continue;
					}
/*
					if (compare(answer,"!TIMEOUT",8)==0) {  // wordt nu in dit programma gedaan !
						vdchar(0xEF);
						tkdspnl("Geen info betaling! ");
					}
					if (compare(answer,"!MANUAL",7)==0) {
						SocketClose(ComSock);
					  disp_ikey(0,4,20,2,998,"Druk hier als\rbetaling OK is",RGB(0,127,0));
						continue;
					}
*/
				}
				else {
				  if (answer[0]=='%') {
					  for (i=0; i<answerlen; i++) {
						  if (answer[i]<' ') {
						    answer[i]=0;
							  break;
							}
						}
					  add_text(&answer[1]);
					}
					else if (answer[0]=='-') {
						curs_up();
						tkdsp("                                          \r");
						tkdsp(&answer[1]);
					}
					else tkdsp(answer);
					answerlen=0;
					if (compare(answer,"***",3)==0) disp_panel(0,0,40,12,0,RGB(255,0,0));
					if (compare(answer,"#",1)==0) {
						disp_panel(0,0,40,12,0,RGB(0,255,0));
						disp_ikey(19,0,6,1,22," OK ",RGB(0,127,0));
						TypeKaart=answer[1]-'0';
						if (!waitflag) break; // betaald ... spring er uit !
					}
				}
				answerlen=0;
			}
		}
		else Sleep(500);
		if (PayStartTim) {
  		time(&tim);
      if (difftime(tim,PayStartTim)>MAX_PAY_TIME) {
				SocketClose(ComSock);
				disp_ikey(19,0,6,1,22,"STOP",RGB(255,0,0));
			  disp_ikey(0,5,25,2,998,"Druk hier als\rbetaling OK is",RGB(0,127,0));
				while (true) {
  				key=kbcharnw();
					if (key==998*0x10000) {
						TypeKaart=1;
						break;
					}
					if (key==0x0100 || key==0x1200 || key==0x160000) break;
				}
				break;
			}
		}
  }

	SocketClose(ComSock);

	cls();
  ConSizeWindow(vdlen_h, vdlen_v);
	ConSelect(old_screen);
  return TypeKaart;
}

void einde(int auto_fl)
{
  char wait, show_fl, betfl, noaccept0_fl, voorschot_fl, TochTickFl;
  int key,i,j,groep,used_onentry,KeyCntUpper=0,ex_ticket_save,bc_scanned_=NO,fl_divuitgave_=NO;
  int _unkbchar=0x7FFFFFFE, aantal, PayCostIx=0;
	double regsave;
	double tot0_save, tot1_save, totaal, leeggoed, leeg_terug, goederen, ep_maaltijd=0.,tot_elec_betaald=0,tot_div_betaald=0,tmp_afr_,tmp_tot_;
  CString cstr,cstr1;
	int ia;
 
	BedragTotaalafronding=0;
  if (p_vrk->AttentionFlag) {
		beep_fl=BAD;
		return;
	}

	if (p_vrk->fakt_type && p_vrk->PrijsViaJmcFlag && p_vrk->JmcFactuurFlag && (KassaTestConfigFlag || (JMD=::FindWindow("THE_JMD",NULL))!=NULL)) { //_T("THE_JMD")
		if(ConMessageBox("Wenst u de specifieke prijzen van de klant te laden?","Specifieke prijzen",MB_YESNO | MB_ICONQUESTION)==IDYES) {
			CMarkup Ticket;
			Ticket.AddElem("Status",2);
			Ticket.AddElem("Ticket");
			Ticket.IntoElem();
			Ticket.AddElem("Klant",klant_nr);
			Ticket.OutOfElem();

			Ticket.AddElem("Detail");
			Ticket.IntoElem();
				for (i=0; i<p_vrk->used; i++) {
					struct s_lijn* pl=&p_vrk->lijn[i];
					if(pl->groep>=1 && pl->groep<=99 && (EigenPrijsOpStuksAllowed || !(pl->bits&STUKS))){ // enkel artikels, stuks via bit (enkel korting in %)
						Ticket.AddElem("L");
						Ticket.IntoElem();
							cstr.Format("%.5s",pl->code);
							Ticket.AddElem("C",cstr);
							cstr.Format("%.3f",pl->prijs);
							Ticket.AddElem("P",cstr);
							if(pl->bits&STUKS) Ticket.AddElem("S", "Y"); else Ticket.AddElem("S", "N");
						Ticket.OutOfElem();
					}
				}
			Ticket.OutOfElem();

			Ticket.Save(JmcCmdFilepath);
			UpdateOnJMC();
  	
			for (j=0; j<15; j++) {
				Ticket.Load(KasCmdFilepath);
	  		if (Ticket.GetDoc().GetLength()>0) break;
				Sleep(100);
			}
			if(j<15){
				Ticket.ResetMainPos();
				j=atol(Ticket.FindGetData("RetValue")); // op hoogste niveau
				if(j==1){
					Ticket.ResetPos();
					Ticket.FindElem("Detail");
					Ticket.IntoElem();
					for (i=0; i<p_vrk->used; i++) {
						struct s_lijn* pl=&p_vrk->lijn[i];
						if(pl->groep>=1 && pl->groep<=99 && (EigenPrijsOpStuksAllowed || !(pl->bits&STUKS))){ // enkel artikels, geen stuks
							if(Ticket.FindElem("L")){
								Ticket.IntoElem();
									cstr.Format("%.5s",pl->code);
									Ticket.ResetMainPos();cstr1=Ticket.FindGetData("C");
									if(cstr==cstr1){
										Ticket.ResetMainPos(); if(Ticket.FindElem("P")) pl->prijs=(float)String2Double(Ticket.GetData());
										if (pl->groep!=99 && p_vrk->punten[i]==0) p_vrk->bdr2punt[i]=pl->prijs;
										adj_lijn(i); 
									}
								Ticket.OutOfElem();
							}
						}
					}
					Ticket.OutOfElem();
					art_calc(YES);
				}
			}
		}
	}

redo_full_betaling:;
	IsOk=true;
	used_onentry=p_vrk->used;
  val_einde=-1;
  einde_fl=YES; for (j=1; j<=MAX_LADE; j++) lade_used[j]=NO;
  lade_used[1]=YES;
  totaal=p_vrk->totaal[0];
  leeggoed=p_vrk->totaal[1];
  leeg_terug=0.;
	if(totaal<0) p_vrk->CreditNotaFlag=true;	else p_vrk->CreditNotaFlag=false;
	//// CHECK TOTAAL for ILLEGAL ZERO !!
	for (i=0; i<p_vrk->used; i++) {
		if (p_vrk->lijn[i].groep==GRP_DIVUITGAVE) fl_divuitgave_=YES;
	  if (p_vrk->lijn[i].groep>=0 && p_vrk->lijn[i].groep<1000 &&
			p_vrk->lijn[i].totaal>-0.01 && p_vrk->lijn[i].totaal<0.01 &&
			p_vrk->lijn[i].aantal!=0. && p_vrk->lijn[i].prijs!=0.) {
	  
				ConMessageBox("Ticket TOTAL is not correct, 1 line is missing !\r\n\r\nPlease cancel ticket and try again!\r\nPlease CALL & INFORM Jamadata...","*** Check Ticket ***",MB_OK | MB_ICONEXCLAMATION);
		}
	}

  if (p_vrk->btw_holland && totaal!=0) {
    mk_btw();
    prt_btw(2);
    tick_type|=1;
  }
  if (tick_type & 2) {
    for (j=0; j<p_vrk->used; j++) {
      if ((p_vrk->lijn[j].groep==groep_leeg) &&
          (p_vrk->lijn[j].totaal<0.)) leeg_terug+=p_vrk->lijn[j].totaal;
    }
  }
	if(TotaalOp5CentAfronden=='J' || TotaalOp5CentAfronden=='C'){
		BedragTotaalafronding=round_it(totaal,def_round); totaal=round_it(totaal,(double)(0.05));  BedragTotaalafronding=round_it((double)(BedragTotaalafronding-totaal),def_round);
	}
	else{
    totaal=round_it(totaal,def_round); BedragTotaalafronding=0.;
	}
  leeggoed=round_it(leeggoed,def_round);
  goederen=round_it(totaal-leeggoed+BedragTotaalafronding-p_vrk->totvoorschot_r,def_round);
  leeg_terug=round_it(leeg_terug,def_round);
  leeggoed-=leeg_terug;
	TicketTotalen[0]=totaal;TicketTotalen[1]=goederen;TicketTotalen[2]=leeggoed; // 0=totaal, 1=goederen, 2=leeggoed
	betfl=NO; 

  if (tick_type & 1) {
    if (!IsNul(p_vrk->totaal[0])) add_einde(GRP_MEETOTAAL,totaal);
  }
  else {
    if (goederen) add_einde(GRP_GOEDEREN,goederen);
    if (leeggoed) add_einde(GRP_LGMEE,leeggoed);
    if (leeg_terug) add_einde(GRP_LGTERUG,leeg_terug);
    if (p_vrk->totvoorschot_r) add_einde(GRP_VOORSCHOT,p_vrk->totvoorschot_r);
  }
	if(!IsNul(BedragTotaalafronding)) add_einde(GRP_AFRONDING,BedragTotaalafronding);
  if (totaal<0.) {
    clr_reg(); // 24/01/08 om eventuele entry te wissen.
		if (!(teg_allow&1) || fl_divuitgave_ || p_vrk->klant_nr ) {
      for (j=0; j<10; j++) if (valuta[j].coeff) {val_used=YES; break;}
			betfl=NO; // was voor 02/04/09 YES // 06/02/08 simulate dat er betaald is. Hij heeft negatief saldo.
			if (p_vrk->klant_nr) betfl=NO; // 26/02/09
    }
    else {
			if(ConMessageBox("Totaal is negatief, er wordt een tegoedbon gedrukt. OK?","Einde ticket",MB_YESNO | MB_ICONQUESTION)==IDNO) {
				for (j=p_vrk->used-1; j>=used_onentry; j--) {
					_del_line(j);
				}
				KeyCntUpper=0;
				//p_vrk->totaal[0]=tot0_save;
				//p_vrk->totaal[1]=tot1_save;
				val_inuse=NO; val_used=NO; digits=def_digits;
				goto end;/* oud scherm wordt terug gedisplayed */
			}
			else{
				beep_ok();
        j=p_vrk->used;
        p_lin=&p_vrk->lijn[j];
				add_text(" ");
				for(j=0;j<5;j++){
					if(txt_tegoedbon[j][0]){
						if(txt_tegoedbon[j][0]=='*' && txt_tegoedbon[j][1]==0) add_text(" "); else	add_text(txt_tegoedbon[j]);
					}
				}
				add_einde(GRP_TEGOED,(double)-totaal);
				close_bon(YES,false); // geen geldlade openen in dit geval
				clr_line();
				beep_fl=NO;
				goto ret;
   		}
    }
  }
//  old_screen=ConSelect(ConTempRef); 
  p_vrk->totaal[0]=totaal;
  tot0_save=p_vrk->totaal[0]; tot1_save=p_vrk->totaal[1];
	if (!IsNul(p_vrk->totaal[0]) || p_vrk->used || BedragTotaalafronding ) add_einde(GRP_TOTAAL,(double) p_vrk->totaal[0]); // altijd te betalen zetten, ook al is het 0 (Jaak 10/03/20)
  show_fl=YES; KeyCntUpper=0; TochTickFl=NO; noaccept0_fl=NO;
	voorschot_fl=NO;
	if (p_vrk->BestelKrtNr) {voorschot_fl=YES; show_fl=NO; noaccept0_fl=YES;}
  FOREVER {
   retry:;
		if (voorschot_fl) {
			for (i=0; i<p_vrk->used; i++) {
				if (p_vrk->lijn[i].groep==GRP_TOTAAL) {
					copynaam(txttxt[83],p_vrk->lijn[i].text+20,sizeof(p_lin->text)-20);
					p_vrk->totaal[0]-=p_vrk->lijn[i].totaal;
					break;
				}
			}
			disp_clr(50,1,30,24);
			disp_key(50,1,30,8,22);
			disp_ikey(50,9,30,8,303,txttxt[85]);
			disp_ikey(50,17,30,8,302,txttxt[84]);
			voorschot_fl=NO;
		}
		if (show_fl) {
      if (BTWBONPercentage) KeyCntUpper++;
			if (ex_ticket==-1) KeyCntUpper++; 
			if (KeyCntUpper) disp_clr(0,0,80,1);
      disp_clr(50,1,30,24);
			show_key(bet_layout, 30);
      show_fl=NO;
	  }
		if (KeyCntUpper) {
      if (ex_ticket==-1) {
				if (TochTickFl) disp_ikey(50-(KeyCntUpper-1)*30,0,30,1,3001,txttxt[82]);
				else disp_ikey(50-(KeyCntUpper-1)*30,0,30,1,3001,txttxt[81]);
			}
			if (BTWBONPercentage) {   
        if (p_vrk->TERPLAATSE_flag) disp_ikey(50,0,30,1,3000,txttxt[80]);
        else disp_ikey(50,0,30,1,3000,txttxt[79]);
			}
    }
    disp_window();
    if (p_vrk->used>0 && p_vrk->totaal[0]<=0 && !noaccept0_fl && betfl) goto betaald;
    if (auto_fl) {
      if (auto_fl==YES) {
        key=35;
        auto_fl=2;
      }
      else if (auto_fl==2) {
        key=36;
        auto_fl=3;
      }
    }
    else {
redo:;
      key=kbchar();
      if ((key / 0x10000) == 0 && (key / 0x100) == 110) { // verborgen F10 om in PDF af te drukken
		if (PrintControl2PDF) {
		  PrintControl2PDF = NO;
		  NoPrtCut = DefNoPrtCut;
		}
		else {
		  PrintControl2PDF = YES; NoPrtCut = YES;
		}
        goto redo; /*  key = 44;*/
      } 	  
	  if (key==0) key=0;
	  else if (key==0x02) {
		//		unkbchar(0x02);
		key=22*0x10000;bc_scanned_=YES;
	  }
	  else if (key>='0' && key<='9') key=(key-'0')*0x10000;
	  else if (key==1*256) key=13*0x10000;
	  else if (key<256) goto redo;

  	if (key==251*256) key=-1;
      else key/=0x10000;
    }
   terug_val:
	  PayCostIx=0;
    groep=0;
    if (key==13) clear(0);
		else if (key==15) {
		  j=p_vrk->used-1;
			if (p_vrk->lijn[j].groep==GRP_MAALTIJD && ep_maaltijd!=0.) {
				aantal=(int)reg;
				if (aantal==0.) {
				  if (reg_sign<0) aantal=-1; else aantal=1;
				}
			  p_vrk->lijn[j].totaal+=(aantal*ep_maaltijd);
        adj_lijn(j);
				p_vrk->totaal[0]-=(aantal*ep_maaltijd);
				clear(0);
			}
		}
    else if (key==17) maal(0);
		else if(key==19) ticket(1);
    else if (key>=0 && key<=12) numkey(key);
    else switch (key) {
      case 3000:
        if (p_vrk->TERPLAATSE_flag) p_vrk->TERPLAATSE_flag=NO;
        else p_vrk->TERPLAATSE_flag=YES;
        goto retry;
      case 3001:
        if (TochTickFl) TochTickFl=NO;
        else TochTickFl=YES;
        goto retry;
      case 22:
				if(tot_elec_betaald && PayCardServer[0]) beep_bad(); // indien al een stuk betaald via GEKOPPELDE terminal, dan NIET mogelijk om terug te keren.
				else{
					for (j=p_vrk->used-1; j>=used_onentry; j--) {
						_del_line(j);
					}
					p_vrk->totaal[0]=tot0_save;
					p_vrk->totaal[1]=tot1_save;
					val_inuse=NO; val_used=NO; digits=def_digits; reg=0; art_calc(YES);
					goto end;/* oud scherm wordt terug gedisplayed */
				}
				break;
      case 86:// schakel over naar vreemde valuta 
        if (p_vrk->fakt_type) beep_fl=BAD;
        else {
          sel_valuta(NO);
          show_fl=YES;
        }
        break;
      case 35:
        reg=p_vrk->totaal[0]; reg_db=15; reg_da=15; reg_kom=0;
        break;
      case 16: // GRP_CREDIT
			  plu_ix=-1;
				if (PluCreditCost[0]>' ') {
				  if ((MinFreeCreditCost==0) || (p_vrk->totaal[0]<MinFreeCreditCost)) {
  					plu_ix=kasplu.plu_req(PluCreditCost,ARTCODE_LEN);
					}
				}
				if (plu_ix>=0) {
				  bool RegEqualsTotaal=false;
				  if (reg==p_vrk->totaal[0]) RegEqualsTotaal=true;
					regsave=reg;
					if (reg==0) {
						reg=p_vrk->totaal[0]; reg_db=15; reg_da=15;
					}
					p_lin=&p_vrk->lijn[p_vrk->used];
					movmem(kasplu.art_info.code,p_lin->code,ARTCODE_LEN);
					p_lin->aantal=kasplu.art_info.prijs[p_vrk->prx_ix];;
					p_lin->prijs=(float)reg;
					p_lin->btw=kasplu.art_info.btw;
					p_lin->groep=kasplu.art_info.groep;
					p_lin->totaal=reg*p_lin->aantal;
					p_vrk->totaal[0]+=p_lin->totaal;
					if (RegEqualsTotaal) regsave=p_vrk->totaal[0];
					adj_lijn(p_vrk->used);
					adj_text(p_vrk->used);
					PayCostIx=p_vrk->used;
					p_vrk->used++;
					disp_window();
					reg=regsave;
				}
				groep=GRP_CREDIT;
				betfl=YES;
				break;
      case 36: groep=GRP_GELD;          betfl=YES; break;
      case 37: groep=GRP_MAALTIJD;
			  if (reg!=0. && p_vrk->totaal[0]>reg) {
					int save_screen=ConSelect(ConTempRef);
					int off;	
					char bufmtchq[50];
					ConStyle(CON_STYLE_NOBACKGROUND);
					cls();
					ConSizeWindow(70,15);
					ep_maaltijd=reg;
					ia=(int)(.99999+p_vrk->totaal[0]/reg);
					int Color;
					CString cstr;
					off=0;
					disp_key(60,0,10,3,22);
					disp_key(60,3,10,3,23); // vorig
					disp_key(60,6,10,3,24); // volgend
				redisp_mtchq:;
					disp_clr(0,0,60,15); 
					for (i=0; i<100; i++) {
					  Color=0x800000; 
						if (reg_aantal && (i==(reg_aantal-off*25-1))) Color=0xA0A000;
					  if (i==25) break;
					  if (i==(ia-off*25-1)) Color=0x2653FB;
						if (i>(ia-off*25-1)) Color=0x101010;
						cstr.Format("%dx%5.2f\r=%6.2f",i+1+off*25,ep_maaltijd,(i+off*25+1)*ep_maaltijd);
						disp_ikey(i/5*12,i%5*3,12,3,3500+i+1,(char *)(LPCTSTR)cstr.operator LPCTSTR(),Color);
					}	
				redo_mtchq:;
					int _key=kbchar()/0x10000;
					if (_key==23) {
					  off--;
						if (off<0) {off=0; goto redo_mtchq;}
						goto redisp_mtchq;
					}
					else if (_key==24) {
					  off++;
						if (off>=4) {off--; goto redo_mtchq;}
						//if (off*25>=ia) {off--; goto redo_mtchq;}
						goto redisp_mtchq;
					}
					if (_key>3500 && _key<=3525) {
					  i=(_key-3500+off*25);
						reg=i*ep_maaltijd;
					}
					cls();
					ConSizeWindow(vdlen_h, vdlen_v);
					ConSelect(save_screen);
					if (_key==22) {clear(0); disp_window(); goto redo;}
				  p_lin=&p_vrk->lijn[p_vrk->used];
					sprintf(bufmtchq,"%5d x %s @%5.2f",i,txtfin[11],ep_maaltijd);
					add_text(bufmtchq);
					reg_aantal=0.;
			  }
				break;
      case 38: groep=GRP_LEVERBON;			           break;
      case 39: groep=GRP_TGBON;                    break;
      case 40: groep=GRP_BANCONT;       betfl=YES; break;
      case 41: groep=GRP_CASHAUT;       betfl=YES; break;
      case 108:groep=GRP_ZEGELS;                   break;
      case 129:groep=GRP_CDBON_BET;                break;
      case 130:groep=GRP_VAR_BET1;                 break;
      case 131:groep=GRP_VAR_BET2;                 break;
      case 132:groep=GRP_VAR_BET3;                 break;
	  case 133:groep = GRP_EMAALTIJD;    betfl = YES;  break;
	  case 134:groep = GRP_EECOCHEQUE;   betfl = YES;  break;
	  case 135:groep = GRP_ECADEAUBON;   betfl = YES;  break;
	  case 136:groep = GRP_ECONSUMBON;   betfl = YES;  break;
	  case 110:groep=GRP_MOBIEL;       betfl=YES; break; // Payconiq/Mobiel via AtosCTEP-terminal
      case 74: dup_nul(2); break;
      case 75: dup_nul(3); break;
      case 78: reg=p_vrk->totaal[0]; groep=GRP_TBSALDO; break;
			case 303: 
				if (reg!=0) {
					groep=GRP_VOORSCHOT_B;  betfl=YES; show_fl=YES; noaccept0_fl=NO;
				}
				break;
			case 302: show_fl=YES; noaccept0_fl=NO; break;
      default:
        beep_bad();
        break;
    }
    if (groep) {
	  if ((groep == GRP_TGBON  || groep==GRP_GELD) && (teg_allow & 1) && p_vrk->totaal[0] < 0.) {
		if (ConMessageBox("Totaal is negatief, er wordt een tegoedbon gedrukt. OK?", "Einde ticket", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		  betfl = NO;  goto redo;
		}
		else{
	   	  beep_ok();
		  j = p_vrk->used;
		  p_lin = &p_vrk->lijn[j];
		  add_text(" ");
		  for (j = 0; j < 5; j++) {
			if (txt_tegoedbon[j][0]) {
			  if (txt_tegoedbon[j][0] == '*' && txt_tegoedbon[j][1] == 0) add_text(" "); else	add_text(txt_tegoedbon[j]);
			}
		  }
		  add_einde(GRP_TEGOED, (double)-p_vrk->totaal[0]);
		  close_bon(YES, false); // geen geldlade openen in dit geval
		  clr_line();
		  beep_fl = NO;
		  goto ret;
		}
	  }

			int subgroep=0;
			if(TotaalOp5CentAfronden=='C'){ // correctie owv knop volledig gebruikt
				if(groep==GRP_GELD && reg==p_vrk->totaal[0]) reg=0;
				else if(groep!=GRP_GELD && !IsNul(BedragTotaalafronding)) {  // afronding teniet doen indien geen geld
					if (reg==p_vrk->totaal[0]) reg=0;  // als men op volledig heeft gedrukt, dan toch NIET afgerond bedrag nemen
					p_vrk->totaal[0]+=BedragTotaalafronding;totaal+=BedragTotaalafronding;tot0_save+=BedragTotaalafronding;BedragTotaalafronding=0;
					for (j=0; j<p_vrk->used; j++) {
						if (p_vrk->lijn[j].groep==GRP_AFRONDING){ p_vrk->lijn[j].groep=GRP_TOTAAL; p_vrk->lijn[j].totaal=p_vrk->lijn[j].prijs;} // afrondingslijn naar totaal  terugzetten
						else if (p_vrk->lijn[j].groep==GRP_TOTAAL) _del_line(j); // te betalen lijn wegdoen wegdoen
					}
				}
			}
			if (reg==0 && (groep==GRP_GELD || groep==GRP_BANCONT || groep==GRP_MOBIEL || groep==GRP_CREDIT || groep==GRP_CASHAUT || groep==GRP_TBSALDO || groep==GRP_ECHEQUE ||
			  groep==GRP_VAR_BET1 || groep==GRP_VAR_BET2 || groep==GRP_VAR_BET3 || groep == GRP_EMAALTIJD || groep == GRP_EECOCHEQUE ||
			  groep == GRP_ECADEAUBON || groep == GRP_ECONSUMBON)) {
			  reg=p_vrk->totaal[0]; reg_db=15; reg_da=15;
				if(TotaalOp5CentAfronden=='C'){
					if(groep==GRP_GELD){ // checken of bedrag op 5 cent is, zoniet corrigeren 
						tmp_afr_=round_it(reg,def_round); tmp_tot_=round_it(reg,(double)(0.05));  tmp_afr_=round_it((double)(tmp_afr_-tmp_tot_),def_round);
						if(!IsNul(tmp_afr_)){
						  if(!IsNul(BedragTotaalafronding)) { // als er al afgerond is, dan teniet doen
								reg+=BedragTotaalafronding;p_vrk->totaal[0]+=BedragTotaalafronding;BedragTotaalafronding=0;
								for (j=0; j<p_vrk->used; j++) {
									if (p_vrk->lijn[j].groep==GRP_AFRONDING) p_vrk->lijn[j].groep=GRP_TOTAAL; // afrondingslijn in totaal 
									else if (p_vrk->lijn[j].groep==GRP_TOTAAL) _del_line(j); // te betalen lijn wegdoen wegdoen
								}
							}
          		BedragTotaalafronding=round_it(p_vrk->totaal[0],def_round); p_vrk->totaal[0]=round_it(p_vrk->totaal[0],(double)(0.05));  
							BedragTotaalafronding=round_it((double)(BedragTotaalafronding-p_vrk->totaal[0]),def_round);
            	if(!IsNul(BedragTotaalafronding)){
								add_einde(GRP_AFRONDING,BedragTotaalafronding);
								copynaam("SUBTOT CASH",&p_vrk->lijn[p_vrk->used-1].text[POS_NAAM+7],POS_TOTAAL-POS_NAAM-7);
	//							movmem("SUBTOT CASH",p_vrk->lijn[p_vrk->used-1].text,11);
								reg=p_vrk->totaal[0]; reg_db=15; reg_da=15;
							}
						}
					}
					if(groep!=GRP_GELD && !IsNul(BedragTotaalafronding)) {
						reg+=BedragTotaalafronding;p_vrk->totaal[0]+=BedragTotaalafronding;BedragTotaalafronding=0;
						for (j=0; j<p_vrk->used; j++) {
							if (p_vrk->lijn[j].groep==GRP_AFRONDING) p_vrk->lijn[j].groep=GRP_TOTAAL; // afrondingslijn in totaal 
							else if (p_vrk->lijn[j].groep==GRP_TOTAAL) _del_line(j); // te betalen lijn wegdoen wegdoen
						}
					}
				}
			}
      if ((groep==GRP_BANCONT || groep==GRP_CREDIT || groep==GRP_CASHAUT  || groep==GRP_MOBIEL || groep == GRP_EMAALTIJD || groep == GRP_EECOCHEQUE ||
		groep == GRP_ECADEAUBON || groep == GRP_ECONSUMBON) && PayCardServer[0]) {
				if(reg<=0){
					beep_bad();
					clr_reg(); reg_aantal=0.;betfl=NO;reg=0;
				  goto retry; // Niet betaald
				}
			  p_lin=&p_vrk->lijn[p_vrk->used];
				int orig_groep = groep;
				int ret=DoPayCard(groep); //  0 -> Niet-Betaald,  1 -> Bankcontact, 2 -> Kredietkaart, 3 -> Mobiel, 4 -> Sodexo, 5 -> Edenred, 6 -> PayFair/Monizze, 7 -> RES
				if (ret==0) {
					if(IsNul(tot_elec_betaald) && IsNul(tot_div_betaald)){ // indien noig niets betaald, dan volle reset doen
  					for (j=p_vrk->used-1; j>=used_onentry; j--) {
	  					_del_line(j);
		  			}
			  		p_vrk->totaal[0]=tot0_save;
				  	p_vrk->totaal[1]=tot1_save;
					  val_inuse=NO; val_used=NO; digits=def_digits; reg=0; art_calc(YES);clr_reg();
						goto redo_full_betaling;
					}

					// remove de eventuele extra kosten 
					if (PayCostIx && (PayCostIx==p_vrk->used-1)) {
						p_vrk->totaal[0]-=p_vrk->lijn[PayCostIx].totaal;
						p_vrk->used--;
						disp_window();
					}
					clr_reg(); reg_aantal=0.;
				  goto retry; // Niet betaald
				}
				
				if (orig_groep == GRP_CASHAUT && ret > 0) {
					groep = GRP_CASHAUT;
				} else {
					if (ret==1) groep=GRP_BANCONT;
					if (ret==2) groep=GRP_CREDIT;
					if (ret==3) groep=GRP_MOBIEL;
					if (ret>=4 && ret<=7) {
						groep=GRP_ECHEQUE;
						subgroep=ret; // voor kasverslag !
					}
				}
			}
			if (groep==GRP_LEVERBON) tot_div_betaald+=reg;
			if (groep==GRP_CDBON_BET) tot_div_betaald+=reg;
			if (groep==GRP_BANCONT || groep==GRP_CREDIT || groep==GRP_CASHAUT  || groep==GRP_MOBIEL  || groep==GRP_ECHEQUE || groep == GRP_EMAALTIJD ||
			  groep == GRP_EECOCHEQUE || groep == GRP_ECADEAUBON || groep == GRP_ECONSUMBON) tot_elec_betaald+=reg;
			if (reg!=0) {
        if (reg_aantal) reg*=reg_aantal;
        if (groep==GRP_GELD && reg<0) add_einde(GRP_TERUG,-reg);
        else add_einde(groep,reg,subgroep);
        if (groep==GRP_VOORSCHOT_B) p_vrk->totaal[0]+=reg;
				else p_vrk->totaal[0]-=reg;
        clr_reg(); reg_aantal=0.;
      }
      else beep_bad();
    }
   betaald:;
    if (!noaccept0_fl && p_vrk->used && (IsNul(p_vrk->totaal[0]) || (p_vrk->totaal[0]<0 && betfl))) {
      wait=YES;
      if (p_vrk->totaal[0]<0) {
        if (val_used) {
          disp_window();
          if (sel_valuta(YES)) {key=22; goto terug_val;}
        }
			 // checken of bedrag op 5 cent is, zoniet corrigeren 
				reg=p_vrk->totaal[0];
				tmp_afr_=round_it(reg,def_round); tmp_tot_=round_it(reg,(double)(0.05));  tmp_afr_=round_it((double)(tmp_afr_-tmp_tot_),def_round);
				if(!IsNul(tmp_afr_)){
					if(!IsNul(BedragTotaalafronding)) { // als er al afgerond is, dan teniet doen
						reg+=BedragTotaalafronding;p_vrk->totaal[0]+=BedragTotaalafronding;BedragTotaalafronding=0;
						for (j=0; j<p_vrk->used; j++) {
							if (p_vrk->lijn[j].groep==GRP_AFRONDING) p_vrk->lijn[j].groep=GRP_TOTAAL; // afrondingslijn in totaal 
							else if (p_vrk->lijn[j].groep==GRP_TOTAAL) _del_line(j); // te betalen lijn wegdoen wegdoen
						}
					}
          BedragTotaalafronding=round_it(p_vrk->totaal[0],def_round); p_vrk->totaal[0]=round_it(p_vrk->totaal[0],(double)(0.05));  
					BedragTotaalafronding=round_it((double)(BedragTotaalafronding-p_vrk->totaal[0]),def_round);
          if(!IsNul(BedragTotaalafronding)){
						add_einde(GRP_AFRONDING,BedragTotaalafronding);
						copynaam("SUBTOT CASH",&p_vrk->lijn[p_vrk->used-1].text[POS_NAAM+7],POS_TOTAAL-POS_NAAM-7);
//							movmem("SUBTOT CASH",p_vrk->lijn[p_vrk->used-1].text,11);
//						reg=p_vrk->totaal[0]; reg_db=15; reg_da=15;
					}
				}
	      add_einde(GRP_TERUG,-p_vrk->totaal[0]);
        disp_window(); wait=YES;
      }
      else {
			  disp_window();
        disp_large(); // was if (ir300_fl) ...
      }
      for (j=1; j<p_vrk->used; j++) {
        if (p_vrk->lijn[j].groep==GRP_TOTAAL
          && (p_vrk->lijn[j-1].groep==GRP_GOEDEREN
          || p_vrk->lijn[j-1].groep==GRP_MEETOTAAL)) {
          _del_line(j-1);
          break;
        }
      }
			ex_ticket_save=ex_ticket;
      if (ex_ticket==-1 && TochTickFl) ex_ticket=1;
			if (p_vrk->ExtraTicket && !p_vrk->fakt_type) {
			  ex_ticket++;
        if (ex_ticket==0) ex_ticket=1;
			}
			if(p_vrk->CreditNotaFlag && fl_KasCtrl)  LogThisAction(ticketnr,0,0) ;
			if((tot_elec_betaald+tot_div_betaald)>0 && (tot_elec_betaald+tot_div_betaald)==tot0_save) close_bon(YES,false); // geen geldlade openen indien alles electronisch/divers betaald
			else close_bon(YES,true);
			ex_ticket=ex_ticket_save;
      if (wait && !auto_fl) {
				
        disp_clr(50,1,30,24);
				if(fl_freedelity){
					if(IsFreedelityRunning(NO) || goederen==0){
					  disp_key(50,1,30,20,22); // grote terugkey
						disp_key(50,21,30,4,127); // kleinere freedelitykey
					}
					else{
					  disp_key(50,1,30,20,127); // grote freedelitykey
					  disp_key(50,21,30,4,22); // kleinere terugkey
					}
				}
        else disp_key(50,1,30,24,22); // grote terugkey
        key=kbchar();
				if (key==0x02) bc_scanned_=YES;
				else if (key==0x160000) {	
					kbflush();} // to clean double keypress on 'TERUG'
				else if (key==0x7F0000){ // 127 freedelity
					if(DumpTicketToFreedelityXml(ticketnr)) CallFreedelityExe(); // call freedelity
					kbflush();
				}
				else {
			    _unkbchar=key;
//				  if (key>=0x10000 && key<=0x90000) key='0'+key/0x10000;
//					if (key==0xA0000) key='0';
//				  unkbchar(key);
				}
      }
      break;
    }
  }
 end:;
  einde_fl=NO;
  clr_line();
 ret:;
	if (KeyCntUpper) disp_kas(0);
	else disp_kas(1);
  val_inuse=NO; val_used=NO; digits=def_digits;
  einde_fl=NO;
	if (_unkbchar!=0x7FFFFFFE) unkbchar(_unkbchar);
	if(bc_scanned_) bc_process(YES);
}

#include <tlhelp32.h>
static int CallFreedelityExe(void)
{
	IsFreedelityRunning(YES); // kill eventueel draaiende freedelity
  ::ShellExecute(NULL,"open","Freedelity.exe","Ticket.XML",NULL,SW_SHOWNORMAL); // kan wel even duren 
// +++ om eerst proces te deleten https://stackoverflow.com/questions/1916574/how-to-effectively-kill-a-process-in-c-win32
  return 1;
}

static bool IsFreedelityRunning(int killproces)
{
  bool ExeFound=false;  
	HANDLE handle = NULL;
  try
  {
    // Create snapshot of the processes
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 info;
    info.dwSize = sizeof(PROCESSENTRY32);
    // Get the first process
    int loop = Process32First(handle, &info);
    // If we failed to get the first process, throw an exception
    while (loop) {
			if (info.th32ProcessID!=GetCurrentProcessId()) {
				if (_strcmpi(info.szExeFile,"Freedelity.exe")==0) {
   //       DWORD dwDesiredAccess = PROCESS_TERMINATE;
    //      BOOL  bInheritHandle  = FALSE;
					if(killproces){
						HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, info.th32ProcessID);
						if (hProcess != NULL) {
							TerminateProcess(hProcess, 1);
							 CloseHandle(hProcess);		
						}
					}
  				ExeFound=true;break;
				}
			}
		  loop=Process32Next(handle,&info);
		}
  }
	catch (...)
	{
	}
  // Release handle of the snapshot
  CloseHandle(handle);
  return ExeFound;
}



static int DumpTicketToFreedelityXml(int ticketNr) // -1=enkel LEGE xml aanmaken  
{
  char *ptxt_,buf30[31];
  int i, j,ix_,i2dump;
	double bd_,bd_korting_,bd_totaal,bd_leeg,bd_divers;
	CString cstr;
	struct s_lijn* pl;
	CMarkup Ticket;
	 
	if(ticketNr==-1){ // lege (dummy) xml aanmaken
		Ticket.AddElem("Ticket");
		Ticket.IntoElem();
		  bd_=0.;
			cstr.Format("%.2f",bd_);Ticket.AddElem("Total",cstr);
			cstr.Format("%.2f",bd_);Ticket.AddElem("Goods",cstr);
			cstr.Format("%.2f",bd_);Ticket.AddElem("Others",cstr);
			cstr.Format("%.2f",bd_);Ticket.AddElem("Empties",cstr);

			Ticket.AddElem("Detail");
		Ticket.OutOfElem(); // ticket
		i=Ticket.Save("Ticket.XML");
		return i;
	}
	
	log_loadticket(ticketNr);
	bd_leeg=0;bd_totaal=0; bd_divers=0;
	for (j=0; j<p_vrk->used; j++) {
		if (p_vrk->lijn[j].groep==GRP_TOTAAL) bd_totaal=p_vrk->lijn[j].totaal;
		else if (p_vrk->lijn[j].groep==groep_leeg) bd_leeg+=p_vrk->lijn[j].totaal;
		else if (p_vrk->lijn[j].groep>=1 && p_vrk->lijn[j].groep<99 && p_vrk->lijn[j].btw==0) bd_divers+=p_vrk->lijn[j].totaal;
	}
	round_it(bd_totaal,def_round);round_it(bd_leeg,def_round);
//	DumpFreedelityXml(round_it(bd_totaal-bd_leeg,def_round),round_it(bd_leeg,def_round));
//	CallFreedelityExe();


	
	Ticket.AddElem("Ticket");
  Ticket.IntoElem();
	  bd_=bd_totaal;cstr.Format("%.2f",bd_);Ticket.AddElem("Total",cstr);
		bd_=bd_totaal-bd_leeg-bd_divers;cstr.Format("%.2f",bd_);Ticket.AddElem("Goods",cstr);
		bd_=bd_divers;cstr.Format("%.2f",bd_);Ticket.AddElem("Others",cstr);
		bd_=bd_leeg;cstr.Format("%.2f",bd_);Ticket.AddElem("Empties",cstr);

		Ticket.AddElem("Detail");
		Ticket.IntoElem();
		i2dump=-1;bd_korting_=0;
		for (i=0; i<p_vrk->used; i++) {
			pl=&p_vrk->lijn[i];

			if (pl->groep>=-9 && pl->groep<=999 && pl->groep!=99) { // geen leeggoed
				if(pl->groep>=1 && pl->groep<99){
					if(i2dump>=0){
						pl=&p_vrk->lijn[i2dump];
						ix_=-1;
						if (pl->code[0]) ix_=kasplu.plu_req(pl->code,ARTCODE_LEN);
						Ticket.AddElem("Line");
							Ticket.IntoElem();
							zeroes(buf30,sizeof buf30); if(ix_>=0) copynaam(kasplu.art_info.code,buf30,ARTCODE_LEN); Ticket.AddElem("ArticleID",buf30);
							zeroes(buf30, sizeof buf30);
							if (ix_ >= 0) copynaam(kasplu.art_info.naam, buf30, 30); else copynaam(grp_info[pl->groep].naam, buf30, 20);
							Ticket.AddElem("Description", buf30);
							cstr.Format("%.2f",pl->aantal); Ticket.AddElem("Quantity",cstr);
							if(pl->bits&STUKS && !(ix_>=0 && kasplu.art_info.st_verp==1)) Ticket.AddElem("PcOfCrate","yes"); else Ticket.AddElem("PcOfCrate","no");
							cstr.Format("%.2f",pl->prijs); Ticket.AddElem("UnitPrice",cstr);
							cstr.Format("%.2f",pl->totaal+bd_korting_); Ticket.AddElem("Total",cstr);
							cstr.Format("%.2f",pl->btw); Ticket.AddElem("VatPct",cstr);
							cstr.Format("%02i",pl->groep); Ticket.AddElem("ArticleGroup",cstr);
							zeroes(buf30,sizeof buf30); if(ix_>=0) copynaam(kasplu.art_info.alt_code,buf30,20); Ticket.AddElem("PnTCode",buf30);
							zeroes(buf30,sizeof buf30); if(ix_>=0) copynaam(kasplu.art_info.ean,buf30,ARTEAN_LEN); Ticket.AddElem("EanCode",buf30);
							zeroes(buf30,sizeof buf30); if(ix_>=0) copynaam(kasplu.art_info.ean_st,buf30,ARTEAN_LEN); Ticket.AddElem("EanCodePc",buf30);
						Ticket.OutOfElem();
					}
					i2dump=i;bd_korting_=0;
				}
				else { // -1 en -2 korting bijhouden
					if(i2dump>=0 && (pl->groep==-1 || pl->groep==-2)) bd_korting_+=pl->totaal;
				}
			}
		}
		if(i2dump>=0){ // laatste lijn wegschrijven 
			pl=&p_vrk->lijn[i2dump];
			ix_=-1;
			if (pl->code[0]) ix_=kasplu.plu_req(pl->code,ARTCODE_LEN);
			Ticket.AddElem("Line");
				Ticket.IntoElem();
				zeroes(buf30,sizeof buf30); if(ix_>=0) copynaam(kasplu.art_info.code,buf30,ARTCODE_LEN); Ticket.AddElem("ArticleID",buf30);
				zeroes(buf30, sizeof buf30); 
				if (ix_ >= 0) copynaam(kasplu.art_info.naam, buf30, 30); else copynaam(grp_info[pl->groep].naam, buf30, 20);
				Ticket.AddElem("Description", buf30);
  			cstr.Format("%.2f",pl->aantal); Ticket.AddElem("Quantity",cstr);
				if(pl->bits&STUKS && !(ix_>=0 && kasplu.art_info.st_verp==1)) Ticket.AddElem("PcOfCrate","yes"); else Ticket.AddElem("PcOfCrate","no");
				cstr.Format("%.2f",pl->prijs); Ticket.AddElem("UnitPrice",cstr);
				cstr.Format("%.2f",pl->totaal+bd_korting_); Ticket.AddElem("Total",cstr);
				cstr.Format("%.2f",pl->btw); Ticket.AddElem("VatPct",cstr);
				cstr.Format("%02i",pl->groep); Ticket.AddElem("ArticleGroup",cstr);
				zeroes(buf30,sizeof buf30); if(ix_>=0) copynaam(kasplu.art_info.alt_code,buf30,20); Ticket.AddElem("PnTCode",buf30);
				zeroes(buf30,sizeof buf30); if(ix_>=0) copynaam(kasplu.art_info.ean,buf30,ARTEAN_LEN); Ticket.AddElem("EanCode",buf30);
				zeroes(buf30,sizeof buf30); if(ix_>=0) copynaam(kasplu.art_info.ean_st,buf30,ARTEAN_LEN); Ticket.AddElem("EanCodePc",buf30);
			Ticket.OutOfElem();
		}
		Ticket.OutOfElem(); // detail
  Ticket.OutOfElem(); // ticket
  i=Ticket.Save("Ticket.XML");
  _clr_ticket(); // tabellen wissen na dump
	return i;
}




static int sel_valuta(char einde)
{
  char *s;
  int j, key, groep;
                        
  disp_clr(50,1,30,24);
  if (einde) {
    if (!val_inuse) {val_ix=10; s=def_valuta;}
    else s=valuta[val_ix].naam;
    disp_key(70,1,10,4,22);
    CString cstr;
		cstr.Format(txttxt[53],s);
		cstr="\r\n"+cstr;
		cstr=txttxt[63]+cstr;
		disp_ikey(50,1,20,4,3500+val_ix,(char *)cstr.operator LPCTSTR());
    for (j=0; j<10; j++) {
      if (val_ix==j) disp_ikey(50+(j%2)*15,5+(j/2)*4,16,4,3510,def_valuta); // valuta[j].naam);
      else if (valuta[j].coeff>.001) disp_ikey(50+(j%2)*15,5+(j/2)*4,15,4,3500+j,valuta[j].naam);
    }
  }
  else if (val_inuse) disp_key(50,5,30,20,3210);
  else for (j=0; j<10; j++) {
    if (valuta[j].coeff>.00001) disp_ikey(50+(j%2)*15,5+(j/2)*4,15,4,3500+j,valuta[j].naam);
  }
  if (!einde) disp_key(50,1,30,4,22);
  FOREVER {
    key=kbchar();
    if (key==251*256) key=-1;
    else key/=0x10000;
    if (key==22) return YES;
    if (key>=3500 && key<=3510) {
      if (key==3510) {
        if (!val_inuse) break;
        val_inuse=NO;
      }
      else {
        if (val_inuse) {
          if (val_ix==key-3500) break;/* do nothing, same valuta */
          val_inuse=NO; val_llast=-1; val_wlast=-1;
          add_einde(GRP_TOTAAL,(double) p_vrk->totaal[0]);
          add_einde(GRP_CONVERT,(double) p_vrk->totaal[0]);
        }
        val_inuse=YES; val_ix=key-3500; val_used=YES;
      }
      groep = p_vrk->lijn[p_vrk->used-1].groep;
      if (groep != GRP_TOTAAL && groep != GRP_CONVERT) {
        add_einde(GRP_TOTAAL,(double) p_vrk->totaal[0]);
      }
      add_einde(GRP_CONVERT,(double) p_vrk->totaal[0]);
      if (!einde) add_einde(GRP_TOTAAL,(double) p_vrk->totaal[0]);
      break;
    }
    beep_fl=BAD;
  }
  if (val_inuse) {
    j=valuta[val_ix].lade;
    if (j>0 && j<=MAX_LADE) lade_used[j]=YES;
    digits=valuta[val_ix].digits;
  }
  else digits=def_digits;
  return NO;
}

void show_key(struct layout *p_lay, int keycnt)
{
  FOREVER {
    if (!p_lay->x_len && !p_lay->y_len) break;
		if (p_lay->key_numb==78) { // Kredietknop
			if (((specialfl&0x01)==0) && !p_vrk->fakt_type)  goto next;	// niets doen, is al gecleared
			if(p_vrk->fakt_type){
				klant_nr=p_vrk->klant_nr; kasklt.get_klant(); 
				if(specialfl&0x02){
					if(klant.naam[39]!='!') goto next; // enkel gemarkeerde klanten
				}
				else{
					if(klant.naam[39]=='!') goto next; // NIET bij gemarkeerde klanten
				}
			}
			disp_key(p_lay->x_pos,p_lay->y_pos,p_lay->x_len,p_lay->y_len,p_lay->key_numb);
		}
    else disp_key(p_lay->x_pos,p_lay->y_pos,p_lay->x_len,p_lay->y_len,p_lay->key_numb);
next:;
		p_lay++;
  }
}

float ReadScaleAantal()
{
	DCB m_dcb;
	COMMTIMEOUTS commTimeout;
	double gewicht;
	DWORD BytesRead;
	char buf[100];
	CString Com;

#if defined (_DEBUG)
  Com="COM1:";
#else
  Com="COM2:";
#endif

	HANDLE ScaleRef=CreateFile(Com, GENERIC_WRITE | GENERIC_READ,
					0, // exclusive access
					NULL, // no security
					OPEN_EXISTING,
					0, // no overlapped I/O
					0); // null template 

  if (ScaleRef<0) {beep_bad(); return 0;}

  SetupComm(ScaleRef, 350, 350); // set buffer sizes
	GetCommState(ScaleRef, &m_dcb);
  m_dcb.ByteSize = 8;
	m_dcb.fParity = FALSE;
  m_dcb.Parity = NOPARITY; // zo overgenomen uit status na hun testprogramma
 	m_dcb.StopBits = ONESTOPBIT;
 	m_dcb.fAbortOnError = FALSE;
	m_dcb.fOutxDsrFlow=FALSE;
	m_dcb.fOutxCtsFlow=FALSE;
	m_dcb.fDtrControl=DTR_CONTROL_ENABLE;
	m_dcb.fRtsControl=RTS_CONTROL_ENABLE;
	m_dcb.fDsrSensitivity=FALSE;
  m_dcb.BaudRate = 9600;
	SetCommState(ScaleRef, &m_dcb);
	if(GetCommTimeouts(ScaleRef, &commTimeout)) {
		commTimeout.ReadIntervalTimeout=100; // max 0,1 seconde tussen 2 character input
		commTimeout.ReadTotalTimeoutConstant=100; // max 100 msec wacht op input
		commTimeout.ReadTotalTimeoutMultiplier=0; 
		commTimeout.WriteTotalTimeoutMultiplier=0;
		commTimeout.WriteTotalTimeoutConstant =1000; // 1 seconden time-out 
		SetCommTimeouts(ScaleRef, &commTimeout);
	}
	
  DWORD BytesWritten=0;
	CString cstr;

  cstr="\x06";
  WriteFile(ScaleRef,cstr,cstr.GetLength(),&BytesWritten,NULL);
	Sleep(100);
	PurgeComm(ScaleRef,PURGE_RXCLEAR);

	long l;
	l=(long)(1000000+(kasplu.art_info.prijs[p_vrk->prx_ix]*100+.5));
	CString pstr;
	pstr.Format("%8d",l);
	cstr.Format("\x04\x02");
	cstr+="01\x1B";
	cstr+=pstr.Right(6);
	cstr+="\x1B\x03";
  
  WriteFile(ScaleRef,cstr,cstr.GetLength(),&BytesWritten,NULL);
	ReadFile(ScaleRef,buf,1,&BytesRead,NULL);

  cstr="\x04\x05";
	WriteFile(ScaleRef,cstr,cstr.GetLength(),&BytesWritten,NULL);
	ReadFile(ScaleRef,buf,26,&BytesRead,NULL);
  cstr="\x04";
	WriteFile(ScaleRef,cstr,cstr.GetLength(),&BytesWritten,NULL);

  gewicht=0;
	if (BytesRead==26) {
		stcd_df(&buf[6],&gewicht);
		gewicht/=1000.;
	}
  CloseHandle(ScaleRef);

  if (gewicht==0.) beep_bad();

  return (float) gewicht;
}

void CheckGoodWeight(struct s_lijn *p_lin)
{
  char buf[50];
	int j;

  if (p_lin->aantal==0) {
		p_lin->groep=GRP_ATTENTION;	
		_clr_text(p_lin->text);
		sprintf(buf,"*** WEEG OPNIEUW ***");
		copynaam(buf,p_lin->text,40);
		disp_fl=YES;
		p_vrk->AttentionFlag=TRUE;
	}
	else {
 		_clr_text(p_lin->text);
	  if (p_vrk->AttentionFlag) {
			p_vrk->AttentionFlag=FALSE;
			for (j=0; j<p_vrk->used; j++) {
				if (p_vrk->lijn[j].groep==GRP_ATTENTION) p_vrk->AttentionFlag=TRUE;
			}
		}
	}
}

int add_art(char idem_fl) // 1=idem
{
  struct s_lijn *p_lin;
  char *code_leeg;
  float prijs;
  float punten;
  double aantal,q_spec_;
  int j, lijn_ix, ix, art_ptr, _groep, count,fl_pctkorting_=NO,fl_skippromo=NO;
	CString cstr;
 
  aantal = reg_aantal; _groep = 0;
  if (aantal == 0.) aantal = reg;
  if (aantal == 0.) if (reg_sign < 0) aantal = -1.; else aantal = 1.;
  lijn_ix=p_vrk->used;
  if (idem_fl==1) {
    if (lijn_ix==0) return YES;
    else lijn_ix--;
  }
  p_lin=(struct s_lijn *) p_vrk->lijn[lijn_ix].text;
  if (p_vrk->leeg_flag & 2) fl_skippromo = YES; // geen promo bij retour leeggoed
  if (idem_fl==1) {
	if (p_vrk->leeg_flag&2) aantal=-aantal;
	count=0;fl_pctkorting_=NO; q_spec_=0;
	while (p_lin->bits & AUTO_LEEG || p_lin->groep==GRP_PKORT || p_lin->groep==GRP_FKORT || p_lin->fl_promoLijn==YES) {
	  if(p_lin->groep==GRP_PKORT) fl_pctkorting_=YES;
	  if((p_lin->groep>=1 && p_lin->groep<=98) || p_lin->fl_promoLijn == YES){
		if(p_lin->fl_promoLijn == NO) q_spec_+=p_lin->aantal;
		_del_line(lijn_ix-count);
		p_lin--; larg_next--;
		if(!(p_lin->bits & AUTO_LEEG || p_lin->groep==GRP_PKORT || p_lin->groep==GRP_FKORT || p_lin->fl_promoLijn == YES)) break;
	  }
	  else{p_lin--; count++; larg_next--;}
	  if (count==p_vrk->used) break;
	}
	p_lin->aantal+=(float)q_spec_; 
    if ((p_lin->groep>=0 && p_lin->groep<1000) || p_lin->groep==GRP_ATTENTION) {
	  int pluix=kasplu.plu_req(p_lin->code,ARTCODE_LEN); // kan zijn dat product niet gevonden wordt (GROEP gebruikt)
	  if (pluix>=0 && p_lin->groep==GRP_ATTENTION) p_lin->groep=kasplu.art_info.groep;
	  if (pluix>=0 && kasplu.art_info.st_verp==999) {  // product moet gewogen worden
		if (reg_aantal==0.) p_lin->aantal=ReadScaleAantal();
		else p_lin->aantal=(float)aantal;
		CheckGoodWeight(p_lin);
		aantal=0.;
	  }
	  else p_lin->aantal += (float)aantal;
	  adj_lijn(p_vrk->used-1-count); art_ptr=p_vrk->used-1-count;
 	  p_lin++;
    }
    while (count-->0) {
	  if(p_lin->groep!=GRP_PKORT) p_lin->aantal +=(float) aantal; // if(fl_pctkorting_==NO) p_lin->aantal +=(float) aantal;
	  adj_lijn(p_vrk->used-1-count);
      p_lin++;
    }
	lijn_ix=p_vrk->used-1; p_lin=(struct s_lijn *) p_vrk->lijn[lijn_ix].text;
    count=0;
	while (p_lin->bits & AUTO_LEEG || p_lin->groep==GRP_PKORT || p_lin->groep==GRP_FKORT) {
	  p_lin--; count++; larg_next--;
	  if (count==p_vrk->used) break;
	}
	art_ptr=p_vrk->used-1-count; fl_skippromo=NO;
	if (p_vrk->leeg_flag & 2) fl_skippromo = YES; // geen promo bij retour leeggoed
    if (p_lin->bits & STUKS) { // geen promo op stuks
      int pluix=kasplu.plu_req(p_lin->code,ARTCODE_LEN); // kan zijn dat product niet gevonden wordt (GROEP gebruikt)
	  if (PromoOpStuksAllowed==0 && pluix>=0 && kasplu.art_info.st_verp>1 && kasplu.art_info.PromoFormule==0) fl_skippromo=YES; // bij nieuwe promoformules alles doorlaten
    }
	if(idem_fl && fl_pctkorting_ && kasplu.art_info.PromoFormule <5) fl_skippromo=YES; // om te vermijden dat korting 2x wordt gerekend (niet bij promo)
	if (art_ptr >= 0 && fl_skippromo == NO) {
	  if (kasplu.art_info.PromoFormule) CalcArtikelPromo(art_ptr);
	  else calc_promo(art_ptr);
	}
    while (count-->0) {
	  adj_lijn(p_vrk->used-1-count);
      p_lin++;
    }
  }
  else {
	if (chk_overflow && (p_vrk->used>=(LIN_COUNT-LIN_MARGIN))) {
	  beep_fl=BAD; return YES;
	}
	art_ptr=-1;
	if (p_vrk->stuks_flag) {
	  p_lin->bits|=STUKS;
	  prijs=kasplu.art_info.st_prijs;
	  if (p_vrk->prx_ix>0) { /* ook horeca prijzen voor stuks (spec. barcodes) */
		if (prijs==kasplu.art_info.prijs[0]) prijs=kasplu.art_info.prijs[p_vrk->prx_ix];
	  }
	  code_leeg=kasplu.art_info.code_lst;
	  if(PromoOpStuksAllowed==0 && kasplu.art_info.st_verp>1 && kasplu.art_info.PromoFormule == 0) fl_skippromo=YES; // geen promo op stuks (behalve via sys3430)
	}
	else {
	  prijs =kasplu.art_info.prijs[p_vrk->prx_ix];
      code_leeg=kasplu.art_info.code_l;
    }
    if (optiestype==1 && kasplu.art_info.groep==optiesgroep) {
      for (j=p_vrk->used-1; j>=0; j--) {
        if ((p_vrk->lijn[j].bits&AUTO_LEEG)==0) {
          aantal=p_vrk->lijn[j].aantal;
          break;
        }
      }
    }
    if ((p_vrk->leeg_flag&2)==0 || kasplu.art_info.groep==groep_leeg) {
/* artikel enkel nemen zo niet retour of zo extra leeggoed */
      movmem(kasplu.art_info.code,p_lin->code,ARTCODE_LEN);
      p_lin->groep =kasplu.art_info.groep;
	  if (reg_aantal==0. && kasplu.art_info.st_verp==999) {  // product moet gewogen worden
		  p_lin->aantal=ReadScaleAantal();
		CheckGoodWeight(p_lin);
	  }
      else p_lin->aantal=(float)aantal;
	  if (idem_fl==2) p_lin->bits=AUTO_LEEG;
      _groep=p_lin->groep;
      p_lin->btw   =kasplu.art_info.btw;
      p_lin->prijs =prijs;
      movmem((char *)&kasplu.art_info,(char *)&art_promo,sizeof(art_promo));
      art_ptr=p_vrk->used;
      if (p_vrk->stuks_flag) punten=kasplu.art_info.punten_st;
      else punten=kasplu.art_info.punten;
      p_vrk->punten[p_vrk->used]=0.; p_vrk->bdr2punt[p_vrk->used]=0.;
      if (punten==0.) p_vrk->bdr2punt[p_vrk->used]=p_lin->prijs;
      else if (punten>0) p_vrk->punten[p_vrk->used]=punten;
      if (optiestype && (optiesgroep==kasplu.art_info.groep)) {
        p_lin->bits|=AUTO_LEEG;
      }
      adj_lijn(p_vrk->used++); p_lin++;
    }
    if (kasplu.art_info.ex_text[0] && fl_skippromo==NO) {
      _clr_text(p_lin->text);
      copynaam(kasplu.art_info.ex_text,p_lin->text+POS_NAAM,sizeof(kasplu.art_info.ex_text));
      p_lin->bits=AUTO_LEEG; p_lin->groep=GRP_TEXT;
      adj_lijn(p_vrk->used++); p_lin++;
    }
    if (plulink==0 && (p_vrk->leeg_flag&3) && *code_leeg) {
      ix=kasplu.plu_req(code_leeg,ARTCODE_LEN);
      if (ix>=0) {
        plu_ix=ix;
        movmem(kasplu.art_info.code,p_lin->code,ARTCODE_LEN);
        if (p_vrk->leeg_flag&2) p_lin->aantal=-(float)aantal;
        else {
          p_lin->aantal=(float)aantal;
          p_lin->bits=AUTO_LEEG;
        }
        p_lin->groep =kasplu.art_info.groep;
        p_lin->btw   =kasplu.art_info.btw;
        p_lin->prijs =kasplu.art_info.prijs[p_vrk->prx_ix];
        adj_lijn(p_vrk->used++); p_lin++;
      }
    }
	if (art_ptr >= 0 && fl_skippromo == NO) {
	  ix = kasplu.plu_req(p_vrk->lijn[art_ptr].code, ARTCODE_LEN); // product opnieuw zoeken owv leeggoed
	  if (ix>=0 && kasplu.art_info.PromoFormule) CalcArtikelPromo(art_ptr);
	  else calc_promo(art_ptr);
	}
    if (p_vrk->alg_korting && _groep!=groep_leeg) {
      reg_aantal=0.; reg=p_vrk->alg_korting;
      korting(2);
    }
  }
  art_calc(YES);
  return NO;
}
 
void _del_line(int index)
{
  char *s;
  int j,used;
 
  used=p_vrk->used;
  if (index>=0 && index<used) {
    j=(used-1)-index;
    if (j>0) {
      movmem((char *)&p_vrk->lijn[index+1],(char *)&p_vrk->lijn[index],j*sizeof(struct s_lijn));
    }
    s=(char *)&p_vrk->lijn[used-1];
    j=sizeof(struct s_lijn);
    while (j-->0) *s++=0;

    for (j=index; j<used-1; j++) {
      p_vrk->punten[j]=p_vrk->punten[j+1];
      p_vrk->bdr2punt[j]=p_vrk->bdr2punt[j+1];
    }
    p_vrk->punten[used-1]=0.;
    p_vrk->bdr2punt[used-1]=0.;
    
    p_vrk->used--;
  }
  if (p_vrk->AttentionFlag) {
		p_vrk->AttentionFlag=FALSE;
		for (j=0; j<p_vrk->used; j++) {
			if (p_vrk->lijn[j].groep==GRP_ATTENTION) p_vrk->AttentionFlag=TRUE;
		}
	}
}
 
void art_calc(char compleet)
{
  int j,used;
 
  used=p_vrk->used;
  if (!compleet) _add_tot(used-1);
  else {
    _clr_tot(YES);
    for (j=0; j<used; j++) _add_tot(j);
  }
  disp_fl=YES;
}

static void _clr_tot(char allemaal)
{
  int i;

  for (i=0; i<2; i++) {
    p_vrk->subaantal[i]=0.;
    p_vrk->subtotaal[i]=0.;
    if (allemaal) {
      p_vrk->aantal[i]=0.;
      p_vrk->totaal[i]=0.;
      p_vrk->t_punten=0.;
      p_vrk->t_bdr2punt=0.;
			p_vrk->totvoorschot_r=0.;
    }
  }
}
 
static void _add_tot(int nr)
{
  double aantal, totaal;
  int groep, i;

  if (p_vrk->lijn[nr].text[0]==0) adj_text(nr);
  groep =p_vrk->lijn[nr].groep;
  if (groep<0) {
    if (groep==GRP_SUBTOT) {
      p_vrk->lijn[nr].totaal=p_vrk->subtotaal[0];/* - p_vrk->subtotaal[1]; */
      p_vrk->lijn[nr].prijs =(float)(p_vrk->subaantal[0] - p_vrk->subaantal[1]);
      _clr_tot(NO);
    }
    adj_lijn(nr);
  }
  aantal=p_vrk->lijn[nr].aantal; totaal=p_vrk->lijn[nr].totaal;
  if (groep==GRP_VOORSCHOT_R) p_vrk->totvoorschot_r=totaal;
	if (groep>GRP_SUBTOT) {
    p_vrk->t_punten+=(float)((aantal * p_vrk->punten[nr]));
    p_vrk->t_bdr2punt+=(float)((aantal * p_vrk->bdr2punt[nr]));
    for (i=0; i<2; i++) {
      p_vrk->aantal[i]    += aantal;
      p_vrk->subaantal[i] += aantal;
      p_vrk->totaal[i]    += totaal;
      p_vrk->subtotaal[i] += totaal;
      if (groep!=groep_leeg) break;
    }
  }
}

#if _DEBUG
#include <malloc.h>

long HeapUsed()
{
    _HEAPINFO info = { 0, 0, 0 };
    long used = 0;
    int rc;

    while ((rc=_heapwalk(&info)) == _HEAPOK)
    {
        if (info._useflag == _USEDENTRY) used += info._size;
    }
		if (rc != _HEAPEND && rc != _HEAPEMPTY) used = (used?-used:-1);

		return used;
}
#endif
 
void disp_window(void)
{
  char buf[30];
  int i;
  double aantal,punten;
 
  _lin(p_vrk->used-2,1);
  _lin(p_vrk->used-1,2);
  if (p_vrk->leeg_flag&2) disp_vid(20,4,txttxt[19],2);
  else if (p_vrk->leeg_flag&1) disp_vid(20,4,txttxt[18],2);
  else disp_vid(20,4,"     ",0);
  if (p_vrk->prx_ix) {
    int2str(p_vrk->prx_ix,txttxt[20]+3,1);
    disp_vid(30,4,txttxt[20],2);
  }
  else disp_vid(30,4,"     ",0);
	disp_vid(0,4,"                    ",0);
  if (p_vrk->klant_nr) { 
    buf[0]='F'; buf[1]=' ';
    int2str(p_vrk->klant_nr,buf+2,5); buf[7]=0;
    disp_vid(1,4,buf,2);
  }
  else if (p_vrk->krtnr) {
		punten = p_vrk->t_punten + p_vrk->krtPunten + p_vrk->t_bdr2punt * krtperc / 100;  i=(int)punten; punten=i;  // integer part nemen
    buf[0]='#'; buf[1]=' ';
    int2str(p_vrk->krtnr,buf+2,5); buf[7]=0;
		if(punten){sprintf(buf+7," (%4d pnt)",(int)(punten)); buf[18]=0;}
		if(krtfull && punten>=krtfull) disp_vid(1,4,buf,8); // indien kaart vol, dan reversed
    else disp_vid(1,4,buf,2);
  }
  else if (p_vrk->BestelKrtNr) {
    buf[0]='B'; buf[1]=':';
    int2str(p_vrk->BestelKrtNr,buf+2,5); buf[7]=0;
    disp_vid(1,4,buf,2);
  }
  else disp_vid(1,4,"        ",0);
  if(einde_fl){
  	sprintf(buf,"%s :%8s",txttxt[25],""); // totaal goederen tonen 
	  conv_getal(TicketTotalen[1],buf+11,7,1,def_digits);
	  disp_vid(0,4,buf,0);
	}
	
  conv_getal(reg_aantal,buf,7,2,3); buf[7]=' ';
  if (reg_aantal) buf[8]='x'; else buf[8]=' ';
  buf[9]=0; disp_vid(0,3,buf,0);
  if (regalffl) {
    i=17-regix;
    regalfa[regix]=0;
    if (regix<8) disp_vid(9,3,"        ",0);
    disp_vid(i,3,regalfa,0);
  }
  else {
    conv_getal(reg,buf,8,2,3); buf[8]=0; disp_vid(9,3,buf,0);
  }
  if (p_vrk->stuks_flag) disp_vid(18,3,txttxt[7],2); else disp_vid(18,3,"  ",2);
  disp_vid(21,3,txtvrk,2);
  aantal=p_vrk->aantal[0]-p_vrk->aantal[1];
  conv_getal(aantal,buf,5,0,2); buf[5]=0; disp_vid(27,3,buf,2);
  //largevid(240,302,buf,0);
  disp_vid(33,3,"-->",2);
  if (val_inuse!=val_wlast) {
    if (val_inuse) {
      disp_vid(47,3,"   ",2);
      disp_vid(47,3,valuta[val_ix].naam,2);
    }
    else {
      disp_vid(47,3,def_valuta,2);
    }
    val_wlast=val_inuse;
  }
  conv_getal(p_vrk->totaal[0],buf,10,1,digits); buf[10]=0; disp_vid(36,3,buf,2);
  if (p_vrk->alg_korting) {
    conv_getal(p_vrk->alg_korting,buf,5,2,2); buf[5]=0;
    disp_vid(41,4,buf,2);
    disp_vid(46,4," %",2);
  }
  else disp_vid(41,4,"        ",0);
  disp_large();

#if _DEBUGxx
  long l = HeapUsed();
	char _buf[100];
	sprintf(_buf,"H=%-8ld",l);
	disp_vid(1,4,_buf,8);
#endif
}

void disp_large(void)
{
  int i, j, start, attr, off, groep, to_scroll,_off,_attr;
  char buf[41], *s, curval[4], prvval[4];
  double aantal, totaal;
 
  if (model==1 || model==2) {
    if (p_vrk->used==0) {
      if (prevcust[0]!=0xFF) cust_init();
      prevcust[0]=(char)0xFF;
    }
    else {
      for (i=0; i<sizeof(buf); i++) buf[i]=' ';
      buf[40]=0;
      i=p_vrk->used-1;
      s=p_vrk->lijn[i].text;
      if (einde_fl) {
        if (val_inuse) {
          movmem(valuta[val_ix].naam,curval,4);
          movmem(def_valuta,prvval,4);
        }
        else {
          movmem(def_valuta,curval,4);
          movmem(valuta[val_ix].naam,prvval,4);
        }
        while (p_vrk->lijn[i].groep == GRP_TOTAAL) i--;  
        s=p_vrk->lijn[i].text;
        if (p_vrk->lijn[i].groep == GRP_CONVERT) {
          movmem(s+3,&buf[0],10);
          movmem(prvval,&buf[10],3);
          movmem(" -> ",&buf[13],4);
          movmem(curval,&buf[17],3);
        }
        else {
          movmem(s+20,&buf[0],20);
        } 
        movmem(txttxt[66],&buf[20],20);
        movmem(curval,&buf[20],3);
        if (p_vrk->lijn[i].groep==GRP_TERUG || p_vrk->totaal[0]==0) movmem(txttxt[67],&buf[20],20);
        else conv_getal(p_vrk->totaal[0],buf+30,10,1,digits);
      }
      else {
        if ((p_vrk->lijn[i].bits & AUTO_LEEG) && (p_vrk->lijn[i].groep==groep_leeg)) {
          movmem(s+6,&buf[34],6);
          if (buf[34]==' ') buf[34]='+';
          i--;
          s=p_vrk->lijn[i].text;
        }
				groep=p_vrk->lijn[i].groep;
        aantal=0.; totaal=aantal;
        while (p_vrk->lijn[i].bits & AUTO_LEEG) {
          aantal+=p_vrk->lijn[i].aantal;
          totaal+=p_vrk->lijn[i].totaal;
          i--;
          s=p_vrk->lijn[i].text;
        }
        movmem(s+13,&buf[0],20);
        movmem(s+ 0,&buf[20],13);
        j=26;
				if (buf[25]>' ' && p_vrk->lijn[i].prijs<100) j=27;
        for (i=33; i>j; i--) buf[i]=buf[i-1];
        buf[j]='x';
				if (groep == GRP_SUBTOT) {
				  for (i=0; i<sizeof(buf)-1; i++) buf[i]=' ';
					movmem(s+7,&buf[0],20);
					buf[20]='=';
					movmem(s+30,&buf[30],10);
				}

      }    
      if (compare(buf,prevcust,sizeof(prevcust))) cust_disp(buf);
      movmem(buf,prevcust,sizeof(prevcust));
    }
  }

  if (ConLargeIx) {
		WndSelect(ConLargeIx);
		disp_clr(1,1,40,17);
		int txtoff, linix=16;
		for (i=p_vrk->used-1; i>=0; i--) {
		  if (linix<0) break;
			txtoff=0;
			if (p_vrk->lijn[i].groep>=1000) {
	      if (p_vrk->lijn[i].groep!=GRP_TEXT && p_vrk->lijn[i].bits!=AUTO_LEEG) { // is ex_text 
					txtoff=20;
					if (linix<1) break;
				}
			}
			linix--;
		  if (txtoff) linix--;
		}
		i++; linix=0;
		for (; i<p_vrk->used; i++) {
			attribute=0; txtoff=0;
			if (p_vrk->lijn[i].groep>=1000 && (p_vrk->lijn[i].groep!=GRP_CDBON_VRK)) {
	      if (p_vrk->lijn[i].groep!=GRP_TEXT && p_vrk->lijn[i].bits!=AUTO_LEEG) { // is ex_text 
				  attribute=0x10;
		      txtoff=20; linix++;
				}
			}
			vdposp(1+linix,1);
			tkdsp(p_vrk->lijn[i].text+txtoff);
			attribute=0;
			linix++;
		}
		double aantal=p_vrk->aantal[0]-p_vrk->aantal[1];
		conv_getal(aantal,buf,10,1,0); buf[10]=0; disp_vid(11,19,buf,0);
    double goederen=p_vrk->totaal[0]-p_vrk->totaal[1];
    conv_getal(goederen,buf,10,1,digits); buf[10]=0; disp_vid(11,20,buf,0);
    conv_getal(p_vrk->totaal[1],buf,10,1,digits); buf[10]=0; disp_vid(11,21,buf,0);

		if (p_vrk->totaal[0]<0) disp_vid(22,19,txttxt[28],15);
		else disp_vid(22,19,txttxt[27],13);
    conv_getal(p_vrk->totaal[0],buf,10,1,digits); buf[10]=0; disp_vid(22,21,buf,0x10);
		
		kbtest();
		WndSelect(0);
	}

  conv_getal(p_vrk->totaal[0],buf,10,1,digits); buf[10]=0;
  if (val_inuse!=val_llast) {
    if (val_inuse) {
      //largevid(328,302,"   ",13);
      //largevid(328,318,valuta[val_ix].naam,10);
    }
    else {
      //largevid(328,302,"   ",0);
      //largevid(328,318,"   ",2);
    }
    val_llast=val_inuse;
  }
/*  if (p_vrk->totaal[0]<0) {
	  largevid(376,302,txttxt[28],13);
	}
  else largevid(376,302,txttxt[27],13);
  largevid(376,318,buf,11); */
  if (!einde_fl) {
    aantal=p_vrk->totaal[0]-p_vrk->totaal[1];
    conv_getal(aantal,buf,10,1,digits); //largevid(160,318,buf,0);
    conv_getal(p_vrk->totaal[1],buf,10,1,digits); //largevid(160,334,buf,0);
    attr=0; off=0;
  }
  else {
    attr=3; off=20;
  }
  if (larg_next>p_vrk->used) {
 //   largecom(0,0,3,0);
    start=p_vrk->used - larg_len;
    to_scroll=0;
  }
  else {
    if (larg_next<larg_last) {
      to_scroll=larg_next-larg_last;
      for (i=larg_next; i<larg_last; i++) {
        _off=off; _attr=attr;
        if (p_vrk->lijn[i].groep==GRP_CONVERT) {_off=0; _attr=2;}
        //largevid(-1,to_scroll,p_vrk->lijn[i].text+_off,_attr);
        to_scroll=0;
      }
    }
    start=larg_last;
    to_scroll=p_vrk->used-start-1;
    if (to_scroll>0) {
		  //largevid(-1,to_scroll,"",attr);
		  to_scroll++;
		}
    else to_scroll=0;
  }
  if (start<0) start=0;
  for (i=start; i<p_vrk->used; i++) {
    _off=off; _attr=attr;
    if (p_vrk->lijn[i].groep==GRP_CONVERT) {_off=0; _attr=2;}
    //largevid(-1,-to_scroll,p_vrk->lijn[i].text+_off,_attr);
    to_scroll=0;
  }
  larg_next=p_vrk->used; larg_last=p_vrk->used;
}

void larg_init(void)
{
	m_strExtraDisplayName="";
	FindExtraDisplay();
	if (m_strExtraDisplayName.GetLength()==0) return;

  int VirtualDisplaySize=GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int MainDisplaySize=GetSystemMetrics(SM_CXSCREEN);
	int CustDisplaySize=VirtualDisplaySize-MainDisplaySize;

	if (CustDisplaySize==1920) {
	
		rtCust.SetRect(MainDisplaySize+750,0,MainDisplaySize+ExtraDisplaySize.right,252);
		
		rtAff.left=MainDisplaySize+750;
		rtAff.top =252;
		rtAff.right=MainDisplaySize+ExtraDisplaySize.Width();
		rtAff.bottom=ExtraDisplaySize.Height();

		rtLarge.left=MainDisplaySize;
		rtLarge.top=0;
		rtLarge.right=MainDisplaySize+750;
		rtLarge.bottom=ExtraDisplaySize.Height();

	}

	else if (CustDisplaySize==1366) {   // 1366 x 768 of 1,405563689604685 keer kleiner dan FULL-HD
	
		rtCust.SetRect(MainDisplaySize+534,0,MainDisplaySize+ExtraDisplaySize.right,181);
		
		rtAff.left=MainDisplaySize+534;
		rtAff.top =181;
		rtAff.right=MainDisplaySize+ExtraDisplaySize.Width();
		rtAff.bottom=ExtraDisplaySize.Height();

		rtLarge.left=MainDisplaySize;
		rtLarge.top=0;
		rtLarge.right=MainDisplaySize+534;
		rtLarge.bottom=ExtraDisplaySize.Height();

	}

	else {
	
		rtCust.SetRect(MainDisplaySize,0,MainDisplaySize+ExtraDisplaySize.right,(int)(ExtraDisplaySize.bottom*0.25));
		
		rtAff.left=(LONG)(MainDisplaySize+ExtraDisplaySize.Width()-ExtraDisplaySize.Height()*0.75*21.0/29.7);
		rtAff.top =rtCust.Height();
		rtAff.right=MainDisplaySize+ExtraDisplaySize.Width();
		rtAff.bottom=ExtraDisplaySize.Height();

		rtLarge.left=MainDisplaySize;
		rtLarge.top=rtCust.Height();
		rtLarge.right=rtAff.left;
		rtLarge.bottom=ExtraDisplaySize.Height();
	}

  ConLargeIx=WndAdd(true);  // no Keyboard Messages !
	WndShowWindow(ConLargeIx, SW_SHOW);
	WndSetWindowPos(ConLargeIx,FALSE,rtLarge.left,rtLarge.top,rtLarge.Width(),rtLarge.Height(),0);
	WndSelect(ConLargeIx);
	ConSizeWindow(43,23);
  disp_panel(0, 0, 43, 19, PANEL_HOR_SMALLER | PANEL_VER_SMALLER | PANEL_WITH_EDGE, RGB(255,255,255));
	disp_vid(1,1," ",1); // so panel is displayed now
  disp_panel(0, 18, 22, 5, PANEL_HOR_SMALLER | PANEL_VER_SMALLER | PANEL_WITH_EDGE, RGB(255,255,255));
  disp_vid(1,19,txttxt[24],0);
  disp_vid(1,20,txttxt[25],0);
  disp_vid(1,21,txttxt[26],0); 
	disp_panel(21,18, 22, 5, PANEL_HOR_SMALLER | PANEL_VER_SMALLER | PANEL_WITH_EDGE, RGB(255,255,255));
	disp_vid(22,19," ",1); // so panel is displayed now

	pCustDisplay = new CCustDisplay;
	pCustDisplay->Create((UINT)IDD_CUSTDISPLAY,NULL);
	SetWindowPos(pCustDisplay->GetSafeHwnd(),HWND_TOP,rtCust.left,rtCust.top,rtCust.Width(),rtCust.Height(),0);
	pCustDisplay->ShowWindow(SW_SHOW);


	pAffDisplay = new CAffDisplay;
	pAffDisplay->Create((UINT)IDD_AFFDISPLAY,NULL);
	SetWindowPos(pAffDisplay->GetSafeHwnd(),HWND_TOP,rtAff.left,rtAff.top,rtAff.Width(),rtAff.Height(),0);
	pAffDisplay->ShowWindow(SW_SHOW);
  
 	

/*
	ConCustIx=WndAdd();
	WndSetWindowPos(ConCustIx,FALSE,800,0,1280,1024-767,0);
	WndShowWindow(ConCustIx, SW_SHOW);
	WndSelect(ConCustIx);
	ConSizeWindow(20,2);
	attribute=6;
	tkdspnl("Dit is een test om  ");
	tkdspnl("te zien of het ok is");
*/

//	kbtest();
	WndSelect(0);

/*  largeini(); 
  largecom(0,0,1,0);
  largecom(0,18,2,0); larg_len=(18-0)-1;
  largevid(264,  0,txttxt[23],8);*/

}

void _lin(int nr, int y)
{
  char buf[10];
 
  if (nr>=0) {
    sprintf(buf,"[%3d]",nr+1); disp_vid(0,y,buf,0);
    disp_vid(6,y,p_vrk->lijn[nr].text,2);
  }
  else {
    disp_vid(0,y,"                                               ",0);
  }
}
 
void disp_kas(int type)
{
  int j;
 
  for (j=0; j<MAX_NIVEAU; j++) sear_niv[j]=0;
  if (type==0) {
    cls();
    p_lay=&key_layout[0];
    disp_panel(0,1,50,4,0,VerkoperKleur);
    for (int i=0; i<100; i++) {
      if (!p_lay->x_len && !p_lay->y_len) break;
      if (p_lay->key_numb < 1000) {
        disp_key(p_lay->x_pos,p_lay->y_pos,p_lay->x_len,p_lay->y_len,p_lay->key_numb);
				if (p_lay->key_numb==123) BestelButtonDisplay=true;
      }
      p_lay++;
    }
  }
  else {
    disp_clr(50,1,30,24);
  }
  kasusr.xpos=50; kasusr.ypos=1;
  kasusr.SelKeyConen(0,sear_niv);
}

void dummy(int dum)
{
}

void stand_by(int dum)
{
} 
 
void _sel_kltkrt(int type)
{
	kaskrt.sel_kltkrt(type);
}

struct {
  void (*rout)(int);
  int argument;
} toetsen [MAX_KEYS] =
{
  numkey,0,/* 0 */
  numkey,1,
  numkey,2,
  numkey,3,
  numkey,4,
  numkey,5,
  numkey,6,
  numkey,7,
  numkey,8,
  numkey,9,
  numkey,10,/* 10 */
  numkey,11,
  numkey,12,
  clear,0,
  plu,0,            // 0 duidt op gewone call, bij 1 dan automatische call ...
  idem,0,
  dummy,0,
  maal,3,
  swap,0,
  ticket,0,
  diversen,0,/* 20 */
  groep,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  verkoper,1,
  verkoper,2,
  verkoper,3,
  and_klant,0,
  korting,0,/* 30 */
  korting,1,
  subtotaal,0,
  eenh_prijs,0,
  einde,NO,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,/* 40 */
  dummy,0,
  stuks,0,
  geldlade,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,/* 50 */
  dummy,0,
  auto_leeg,0,
  terug_leeg,0,
  prx_upd,-1,
  dummy,0,
  faktuur,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,/* 60 */
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,/* 70 */
  dummy,0,
  dummy,0,
  dummy,0,
  dup_nul,2,
  dup_nul,3,
  dummy,0,
  dummy,0,
  dummy,0,
  stand_by,0,
  dummy,0,/* 80 */
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,/* 90 */
  dummy,0,
  dummy,0,
  leeg_ok,0,
  sel_kassier,0,
  sel_kassier,0,
  sel_kassier,0,
  sel_kassier,0,
  prt_kas,0,
  wrk_put,-1,
  wrk_get,-1,/* 100 */
  ean,0,
  uitgave,1,
  uitgave,-1,
  test,0,
  clr_ticket,0,
  dummy,0,
  alg_korting,0,
  dummy,0,
  dummy,0,
  dummy,0, /* 110 */
  dummy,0,
  dummy,0,
	_sel_kltkrt,0, // 0 -> punten op krt
  dummy,0,
  pro_forma,0, /* 115 */
  dummy,0,
  dummy,0,
  dummy,0,
  dummy,0,
  einde_zn_ticket,0, // 120
	_sel_kltkrt,1, // 1 -> bestelling via krt
	_controle,0,
	_menu_bestel,0,
	einde_met_btwtab,0,
	readEID,0, // 125
	dummy,0, // pda-bon
  dummy,0 // freedelity	
};

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
CMemoryState OrigState,CurrState,DiffState;
bool OrigStateUsed=false;
#endif
 
void exec_pen(void)
{
  int i, j;
  char full, idem_fl;
 
  adj_verkopen(0);
  BarcodeSet(1,"\x02","\x03");
  if (chk_kassier) sel_kassier(0);
  disp_kas(0);

  ConSelect(ConRef);
  SplashHide(); // unhide program & hide splash screen

  if (chk_kassier) disp_key(31, 0, 29,1,94);
  beep_fl=NO; disp_fl=YES; digits=def_digits;
  for (j=0; j<VRK_COUNT; j++) {
    for (i=0; i<KLT_COUNT; i++) {
      verkopen[j*KLT_COUNT+i].leeg_flag=(char)leeg_sys[j];
      verkopen[j*KLT_COUNT+i].bak_flag=(prx_sys[j]/10)%10;
      verkopen[j*KLT_COUNT+i].prx_ix=prx_sys[j]%10;
			verkopen[j*KLT_COUNT+i].btw_holland=btw_holland;
    }
  }
  back_start(YES);
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
	OrigState.Checkpoint();
#endif
	FOREVER {
    if (p_vrk->used || regix) ss_enable=NO; else ss_enable=YES;

		kbtest(false); // om display-update te krijgen
    if (disp_fl) {disp_window(); disp_fl=NO;}
    full=NO;
    if (p_vrk->used>=LIN_COUNT-LIN_MARGIN) {full=YES; disp_vid(2,4,txttxt[64],8);}
   redo:;
	  if (p_vrk->AttentionFlag!=PrevAttentionFlag) {
			if (p_vrk->AttentionFlag) disp_panel(0,1,50,4,0,RGB(255,0,128));
			else disp_panel(0,1,50,4,0,VerkoperKleur); 
			PrevAttentionFlag=p_vrk->AttentionFlag;
		}
		if (beep_fl==BAD) beep_bad();
		beep_fl=NO;
		if (ss_enable) disp_reclame();
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
		CurrState.Checkpoint();
		if(DiffState.Difference(OrigState,CurrState)==0) {
			//AfxMessageBox("No Memory Leak");
		}
		else {
			//AfxMessageBox("Warning : Memory Leak");
			DiffState.DumpStatistics();
		}
#endif
    key_touched=kbchar();
		if (key_touched==0) key_touched=0;
    else if (key_touched==0x02) {
      bc_process(YES);
      continue;
    }
		else if (key_touched>='0' && key_touched<='9') key_touched=(key_touched-'0')*0x10000;
		else if (key_touched==1*256) key_touched=13*0x10000;
		else if (key_touched<256) goto redo;
    if (key_touched==251*256) goto redo;
    else key_touched/=0x10000;

//    winkassa nog op te lossen mvg
//    bc_allowed=bc_option;
//    key_touched=pen_scan(NO);
//    bc_allowed=NO;
//    ss_enable=NO;
//    if (key_touched==-2) {
//    bc_process(YES);/* do process the rout() */
//      goto next;
//    }

    if (key_touched>=0 && key_touched<1000) (*toetsen[key_touched].rout)(toetsen[key_touched].argument);
    else {
      if (full) beep_fl=BAD;
      else if (key_touched<(1000+96+8)) {  // dit is de maximale value voor 'user-keys' !
       kasusr.aantal=reg_aantal;
        if (kasusr.aantal==0) kasusr.aantal=reg;
        if (kasusr.aantal==0) {
          if (reg_sign<0) kasusr.aantal=-1;
          else kasusr.aantal=1;
        }
        kasusr.stuks_fl=p_vrk->stuks_flag;
        kasusr.SelKeyConen(-(key_touched*0x10000),"");
        if (kasusr.vrkused>0) {
          for (i=0; i<kasusr.vrkused; i++) {
            kasplu.get_plu(kasusr.vrk[i].plu_ix);
            reg=kasusr.vrk[i].aantal;
            p_vrk->stuks_flag=kasusr.vrk[i].stuks_fl;
            idem_fl=NO;
            if (kasusr.vrk[i].optie_fl) idem_fl=2;
            add_art(idem_fl);
          }
          clr_line(); reg=0.;
        }  
      }
    }
//   next:;
  }
}

void back_start(int first)
{
  if (back_time>0) {
    if (first) {back_doit=get_hun(); back_check();}
    else back_doit=get_hun()+back_time*100L;
  }
}
 
void back_check(void)
{
  long now;
 
  if (back_doit) {
    now=get_hun();
    if (now>=back_doit || now<(back_doit-back_time*100L)) {
      disp_vid(1,4,"B",4);
      log_copy(back_file);
      disp_vid(1,4," ",0);
      back_start(NO);
    }
  }
}

 
// #include "KasCommn.cpp"

// kaswrk.cpp

static struct FILEINFO {
  char resv[21];
  char attr;
  long time;
  long size;
  char name[13];
} file;

static int wrk_size;
static char filnam[100];
extern char wrkpath[64];

/* --------------------------- Declaratie functies ---------------------- */

#include "kassa.h"
static int get_nr(char exist);
static int wrk_exist(int nr);
//////////////////

void mkfilnam(char *s)
{
  if (*wrkpath==0) {
    sprintf(filnam,"%1s",s);
  }
  else {
    sprintf(filnam,"%1s\\%1s",wrkpath,s);
  }
}

void op_kaswrk(int line)
{
 
  disp_vid(0,line,"Checking for WRK-files ...",0);
	wrk_size = &p_lin->EindeWRKReclen - (char *)&p_lin->bits;
  // wrk_size = sizeof(struct s_lijn) - sizeof(p_lin->text);
}


static int wrk_exist(int nr)
{
  int fa;
	char buffer[20],buf1[4];
 
  if (nr>=490 || nr<0) return NO;
	movmem("KASBON00.WRK",buffer,sizeof(buffer));
	if(nr<100) sprintf(buf1,"N%02i",nr); else sprintf(buf1,"%03i",nr); 
	movmem(buf1,&buffer[5],3);
	/*	
  movmem("KASBON00.WRK",buffer,sizeof(buffer));
  nr=nr%100;
  buffer[6]='0'+nr/10; buffer[7]='0'+nr%10;*/
  mkfilnam(buffer);
  fa=getfa(filnam);
  if (fa<=0) return NO;
  return YES;
}
 
static int vkpda_exist(int nr)
{
  char buffer[20];
  sprintf(buffer,"VKPDA%03d.DAT",nr);
  mkfilnam(buffer);

  CFileFind finder;
  BOOL FoundFile = finder.FindFile(buffer);
  if (!FoundFile) return -1;
  finder.FindNextFile();
	CTime filetime;
  finder.GetLastWriteTime(filetime);
	CTimeSpan age = CTime::GetCurrentTime() - filetime;
	return (int)age.GetTotalHours();
}

static void vkpda_dispfile(int nr, int xpos, int ypos)
{
  char buffer[1000];
	int j;

  sprintf(buffer,"VKPDA%03d.DAT",nr);
  mkfilnam(buffer);
  
	CFileFind finder;
  BOOL FoundFile = finder.FindFile(buffer);
  if (!FoundFile) return;

	finder.FindNextFile();
	CTime filetime;
  finder.GetLastWriteTime(filetime);
	sprintf(buffer,"Ref# : %-5d     %s",nr, (char *)(LPCTSTR)filetime.Format( "%a %d/%m/%y %H:%M" ));
	disp_vid(xpos,ypos,buffer,0);

	int used_onentry = p_vrk->used;
  double tot0_save=p_vrk->totaal[0];
	double tot1_save=p_vrk->totaal[1];
	wrk_put(nr+1000+10000); // vkpda & niet wissen dus !
	beep_fl=NO; // om beep te vermijden wanneer een artikel# niet gevonden werd
	double val0 = p_vrk->totaal[0]-tot0_save;
	double val1 = p_vrk->totaal[1]-tot1_save;
	val0 -= val1;
  for (j=p_vrk->used-1; j>=used_onentry; j--) {
    _del_line(j);
  }
	art_calc(YES);

	sprintf(buffer,"%s :%15s",txttxt[25],"");
	conv_getal(val0,buffer+12,9,1,def_digits);
	disp_vid(xpos,ypos+2,buffer,0);

	sprintf(buffer,"%s :%15s",txttxt[26],"");
	conv_getal(val1,buffer+12,9,1,def_digits);
	disp_vid(xpos,ypos+3,buffer,0);
}

void wrk_put(int nr) // nr = 1000 + indien VKPDA, +10.000 indien niet wissen
{
  int i, j,k,reclen_, wrkref,old_screen, stukssave, leegsave,pda_methode_,curs,key,z;
  char buf[1000], filename[20], *s, printed, DoNotDelFlag=false;
  int sortcode[LIN_COUNT], sortnr, VKPDAref;
  CString cvkpfull_,vkp;

	if (nr>=1000) { // verkoopsbonnekes gemaakt met PDA (VKPDAnnn.DAT) : datum|uur|code|aantal|stuks|EANBak|EANStuk
	  nr-=1000;
		if (nr>10000) {
		  DoNotDelFlag=true;
			nr-=10000;
		}
		sprintf(filename,"VKPDA000.DAT");
		filename[5]+=((nr/100)%10);
		filename[6]+=((nr/10)%10);
		filename[7]+=(nr%10);
		mkfilnam(filename); // om path voor wrk-bonnetjes te nemen !
		VKPDAref=dopen(filnam,RDWRMODE);

		if (VKPDAref>=0) {                  // artikelen afkomstig van PDA
			cvkpfull_=""; i=sizeof(buf)-1;
			while (i==(sizeof(buf)-1)) {
				i=dread(VKPDAref,buf,sizeof(buf)-1);
				buf[i]=0;
				cvkpfull_+=buf;
			}
			dclose(VKPDAref);   
			cvkpfull_+='\r';cvkpfull_.Replace("\r\n", "\r");
			leegsave=p_vrk->leeg_flag;
			stukssave=p_vrk->stuks_flag;
			reclen_=cvkpfull_.Find("\r",0); if(reclen_<0) goto end_pda_ticket;
			vkp=cvkpfull_.Mid(0,reclen_);if(vkp.GetLength()<5) goto end_pda_ticket;
			i=-1;
			for(j=0;j<10;j++){i=vkp.Find("|",i+1);if(i<0) break;}
			pda_methode_=NO; if(j>=6) pda_methode_=YES; // rechtstreekse bonnekes van PDA
			while (cvkpfull_.GetLength()>5) {
				reclen_=cvkpfull_.Find("\r",0); if(reclen_<0) break;
				vkp=cvkpfull_.Mid(0,reclen_);if(vkp.GetLength()<5) goto next_rec;
				vkp.Replace(" ","");
				if(pda_methode_){ // eerste 2 kolommen zijn datum en tijd 
  				i=vkp.Find("|",0);if(i<0) goto next_rec; // datum skippen
	  			i=vkp.Find("|",i+1);if(i<0) goto next_rec; // uur skippen
		  		vkp=vkp.Mid(i+1); 
				}
				i=vkp.FindOneOf("|\r");
				if (i>0) movmem((void *)vkp.operator LPCTSTR(),regalfa,i);
				regix=i; regalfa[i]=0;
				if(compare(regalfa,"SUBTOTAAL",9)==0) goto next_rec; // subtotaal van PDA skippen
				i=vkp.Find("|",0);vkp=vkp.Mid(i+1);

				reg_aantal=str2dbl(vkp);
				i=vkp.Find("|",0); vkp=vkp.Mid(i+1);
				if(pda_methode_){
				  if (vkp.GetAt(0)=='J') p_vrk->stuks_flag=1;
				  else p_vrk->stuks_flag=0;
				}
				else{
				  if (vkp.GetAt(0)=='1') p_vrk->stuks_flag=1;
				  else p_vrk->stuks_flag=0;
				}
				i=vkp.Find("|",0);vkp=vkp.Mid(i+1);
				
				// EANbak/stuk wordt niet gebruikt

  			p_vrk->leeg_flag=0; // default 0
				plu(1);
			next_rec:;
				cvkpfull_=cvkpfull_.Mid(reclen_+1);
			}
			end_pda_ticket:;
			clr_line();
			p_vrk->leeg_flag=leegsave;
			p_vrk->stuks_flag=stukssave;
			if (!DoNotDelFlag) unlink(filnam);
		}
		else beep_bad();
	}

  else {                              // verwerk op klassieke manier ;
    old_screen=ConSelect(ConWrkPut);
    ConStyle(CON_STYLE_NOBACKGROUND);
    cls();

    if (nr==-1) nr=get_nr(NO);
    if (nr==-2) goto ret;
	if(KeepWRKBon420 && nr>=KeepWRKBon420 && nr<=490){ // indien men bestaande wil overschrijven, dan deze eerst deleten
	  if (wrk_exist(nr)){
		  wrk_del(nr);
		  if(p_vrk->used==0) goto ret; // om wrk-bon echt te schrappen
	  }
	}
    if (wrk_exist(nr)) wrk_get(nr);
    else {

	  memset((char *)&WrkBonHdr.DateTimeStr[0],0,WRK_BONHDR_LEN);
	  get_tijd(); memcpy(WrkBonHdr.DateTimeStr,tijd,20);
	  WrkBonHdr.KlantNr=p_vrk->klant_nr;
	  WrkBonHdr.KaartNr=p_vrk->krtnr;
	  WrkBonHdr.TotTicket=p_vrk->totaal[0];
	  WrkBonHdr.TotLeeggoed=p_vrk->totaal[1];
	  if(p_vrk->klant_nr){
		  klant_nr=p_vrk->klant_nr; kasklt.get_klant(); 
		  memcpy(WrkBonHdr.code,klant.code,10);
		  memcpy(WrkBonHdr.naam,klant.naam,40);
		  memcpy(WrkBonHdr.straat,klant.straat,30);
		  memcpy(WrkBonHdr.postnr,klant.postnr,6);
		  memcpy(WrkBonHdr.gemeente,klant.gemeente,25);
	  }
	  else if(p_vrk->krtnr){
		  kaskrt.FGetKaart(p_vrk->krtnr);
		  memcpy(WrkBonHdr.code,kaskrt.KaartFiche.code,10);
		  memcpy(WrkBonHdr.naam,kaskrt.KaartFiche.naam,40);
		  memcpy(WrkBonHdr.straat,kaskrt.KaartFiche.straat,30);
		  memcpy(WrkBonHdr.postnr,kaskrt.KaartFiche.postnr,6);
		  memcpy(WrkBonHdr.gemeente,kaskrt.KaartFiche.gemeente,25);
	  }
	  else if(p_vrk->EidNaam[0]){
		  memcpy(WrkBonHdr.naam,p_vrk->EidNaam,40);
		  memcpy(WrkBonHdr.straat,p_vrk->EidStraat,30);
		  memcpy(WrkBonHdr.postnr,p_vrk->EidPostCode,6);
		  memcpy(WrkBonHdr.gemeente,p_vrk->EidGemeente,25);
		  memcpy(WrkBonHdr.EIDnr,p_vrk->EidRRN,20);
	  }
	  cls();
	  ConStyle(0); curs=1;// grijze achtergrond
	  while(true){
		  scrnum=0;scrget(2,1506); z=1; 
		  scrifld(z++,fm_ou3,&nr);
		  scrifld(z++,fm_os20,WrkBonHdr.DateTimeStr);
		  scrifld(z++,fm_od6_2,&WrkBonHdr.TotTicket);
		  scrifld(z++,fm_os40,WrkBonHdr.naam);
		  for(k=0;k<2;k++) scrifld(z++,fm_us40,WrkBonHdr.BonText[k]);
		  disp_ikey(2,10,20,2,106,"annuleer",KLEUR_FTOETS);
		  disp_ikey(22,10,20,2,108,"neem aan",KLEUR_FTOETS);
		  DisplayKeyboard(0,13,0,1,KeyboardType);
		  key=scrupd(curs,0xA0); curs=4;
		  if (key&0xFFFF0000) key/=0x10000;
		  if(key==106) goto ret;
		  if(key==108) break;
	  }
      ConStyle(CON_STYLE_NOBACKGROUND);
      cls();
      wrkref=wrk_open(nr);
      if (wrkref<0) goto ret;
      if (WRK_BONHDR_LEN!=dwrite(wrkref,(char *)&WrkBonHdr.DateTimeStr[0],WRK_BONHDR_LEN)) {
        wrk_close(wrkref);
        goto ret;
      }

	  p_vrk->klant_nr=0;
	  p_vrk->fakt_type=0; // anders gaat gij factuur afdrukken indien factuurklant geselecteerd !
      for (i=0; i<p_vrk->used; i++) {
		if(p_vrk->lijn[i].aantal==0 && p_vrk->lijn[i].code[0]=='\0' && p_vrk->lijn[i].prijs==0 && p_vrk->lijn[i].totaal==0) continue; // lijn EID skippen, want anders lege lijnen
        if (wrk_size!=dwrite(wrkref,(char *)&p_vrk->lijn[i].bits,wrk_size)) {
          wrk_close(wrkref);
          goto ret;
        }
      }
      wrk_close(wrkref);
      if (tafel_cnt>0) {
        sortnr='A';
        prt_nl("----------------------------------------");
        for (i=0; i<p_vrk->used; i++) {
          s=p_vrk->lijn[i].text;
          for (j=POS_PRIJS; j<POS_NAAM; j++) s[j]=' ';
          for (j=POS_TOTAAL; j<sizeof(p_vrk->lijn[0].text)-1; j++) s[j]=' ';
          j=p_vrk->lijn[i].groep;
          if (j>=0 && j<=99) j=grp_extra[j].sortnr;
          if (j>='A' && j<='Z') sortnr=j;
          sortcode[i]=sortnr;
        }
        for (j='A'; j<='Z'; j++) {
          printed=NO;
          for (i=0; i<p_vrk->used; i++) {
            if (sortcode[i]==j) {
              prt_nl(p_vrk->lijn[i].text);
              printed=YES;
            }
          }
          if (printed) prt_nl("----------------------------------------");
        }
        prt_nl("");
        if (nr<tafel_cnt) sprintf(buf," BESTELLING TAFEL-%-2d",nr+1);
  //    else sprintf(buf," BESTELLING TOOG-%-2d",nr-tafel_cnt+1);
        else sprintf(buf," BESTEL.INPAKKEN-%-2d",nr-tafel_cnt+1);
        prt_cod(3);
        prt_nl(buf);
        prt_hoofd(YES);
		prt_close();
      }
      if (PrtOnWRKPutFlag) {
#if CONTROL2PDF
		char *b;
		b = new char[CTRLPDFSIZE];
		unsigned short int *w = (unsigned short int *)b;

		w[0] = 0x09B0;
		w[1] = 0x0DB4;
		w[2] = 0x0000;
		w[3] = 0x0056;
		w[4] = 0x0076;
		w[5] = 0x0076;
		w[6] = 0x0000;
		w[7] = 0x0304; /// was 0x0304;
		w[8] = 0x0B06;
		w[9] = 0x0450;
		w[10] = 0x0100;
		w[11] = 0x0000;
		JMU_s = (char *)&w[12];
		JMU_s = CopyString(JMU_s, "\xE0\xD4[landscape;]|\xF0");
		TotSpoolBytes = 50;
		//		  PrintControl2PDF = NO;

#endif
        add_einde(GRP_MEETOTAAL,p_vrk->totaal[0]);
		prt_cod(2); prt_cod(3);
		short jj, mm, dd;
		jddate(dateget(),&jj,&mm,&dd);
		if(PrtOnWRKPutFlag!=2 && nr>=140 && nr<=500) sprintf(buf,"BON# %-3d",nr); // tussen 140 en 490 default geen datum afdrukken (wel bij D in paramaters)
		else sprintf(buf,"BON# %-3d  %2d/%02d/%4d",nr,dd,mm,jj);
		prt_nl(buf);
		prt_cod(4);
		if (!PrintControl2PDF) { // niet bij pdf
		  memcpy(buf, BCPREFIXWERKBON, 9);
		  j = nr;
		  for (i = 0; i < 3; i++) {
			buf[11 - i] = '0' + j % 10;
			j = j / 10;
		  }
		  buf[12] = 0;
		  prt_ean(buf);
		}
		if(WrkBonHdr.BonText[0][0]) prt_nl(WrkBonHdr.BonText[0]);
		if(WrkBonHdr.BonText[1][0]) prt_nl(WrkBonHdr.BonText[1]);
		close_bon(NO,true);
		prt_close();
#if CONTROL2PDF
		delete[] b;
#endif
      }
      _clr_ticket();
      clr_line();
    }
   ret:;
    ConSelect(old_screen);
  }

  return;
}
 
void vkpda_disp()
{
  char buf[20];
  int i, key, j;
 
  int count, old_screen, age;
	COLORREF color;

  old_screen=ConSelect(ConTempRef);
  ConStyle(CON_STYLE_NOBACKGROUND);
retry:
  cls();

  disp_key(72,0,8,2,22);
  j=0; count=0;
  for (i=0; i<=255; i++) {
		if ((age=vkpda_exist(i))>=0) {
      sprintf(buf,"%03i",i);
			if (age>=24) color=RGB(64,64,0);
			else color=RGB(255,255,0);
      disp_ikey((count%16)*5,2+(count/16)*2,5,2,3000+i,buf,color);
			count++;
    }
  }

  FOREVER {
    key=kbchar();
    key/=0x10000;
    if (key==22) break;
    if (key>=3000 && key<=3000+255) {
			disp_panel(20,16,40,9,  PANEL_HOR_SMALLER | PANEL_VER_SMALLER | PANEL_WITH_EDGE,RGB(255,255,0));
			if (!VKPDADisplayBlockedFlag) disp_key(22,22,17,2,100);
  		disp_key(41,22,17,2,22);
		  redisp:;
			int nr=key-3000;
			vkpda_dispfile(nr,22,17);
			key=kbchar();
			key/=0x10000;
			if (key==22) goto retry;
			if (key==100) {
				wrk_get(nr+1000);
				break;
			}
			if (key>=3000 && key<=3000+255) goto redisp;
    }
  }
  ConSelect(old_screen);
}

void wrk_get(int nr)
{
  long size;
  int i, count, wrkref, old_screen, bonwrk_size;
  float punten;
  struct s_lijn *p_lin;

  bonwrk_size = wrk_size; p_lin = (struct s_lijn *) &p_vrk->lijn[0].text;
  old_screen=ConSelect(ConWrkGet);
  ConStyle(CON_STYLE_NOBACKGROUND);
  cls();
  if (nr==-1) nr=get_nr(YES);
  if (nr==-2) goto ret;
  if (!wrk_exist(nr)) wrk_put(nr);
  else {
    wrkref=wrk_open(nr);
    if (wrkref<0) goto ret;
    size=dseek(wrkref,0L,2); dseek(wrkref,0L,0);
		memset((char *)&WrkBonHdr.DateTimeStr[0],0,WRK_BONHDR_LEN);
		if(size>=WRK_BONHDR_LEN){
			count=(size-WRK_BONHDR_LEN)% bonwrk_size;
			if (count) { // nog oude bon zonder promo
			  bonwrk_size= &p_lin->EindeReclenKaslog - p_lin->text-sizeof(p_lin->text);
			  count = (size - WRK_BONHDR_LEN) % bonwrk_size;
			}
			if(count==0){ // nieuwe wrk-file met bonheader
				dread(wrkref,(char *)&WrkBonHdr.DateTimeStr[0],WRK_BONHDR_LEN);
				count=(size-WRK_BONHDR_LEN)/ bonwrk_size;
			}
		}
		else count=size/bonwrk_size;
    for (i=0; i<count; i++) {
      if (bonwrk_size!=dread(wrkref,(char *)&p_vrk->lijn[p_vrk->used].bits,bonwrk_size)) break;
      adj_lijn(p_vrk->used++);
    }
	for (i = 0; i < p_vrk->used; i++) { // aantal uitgesplitste lijn terug op origineel zetten
	  if (!(p_vrk->lijn[i].bits&AUTO_LEEG)) {
		if (kasplu.plu_req(p_vrk->lijn[i].code, ARTCODE_LEN) >= 0) {
		  if (p_vrk->lijn[i].PromoFormule == 5 || p_vrk->lijn[i].PromoFormule == 7) {
			if (p_vrk->lijn[i + 1].bits&AUTO_LEEG && p_vrk->lijn[i + 1].groep > 0 && p_vrk->lijn[i + 1].groep < 99) { 
			  p_vrk->lijn[i].aantal += p_vrk->lijn[i + 1].aantal;
			  adj_lijn(i);
			  _del_line(i + 1);
			}
		  }
		  CalcArtikelPromo(i);
		}
	  }
	}

	for (i = 0; i < p_vrk->used; i++) {// puntenbasis terug invullen want die werden niet gesaved
	  p_lin = (struct s_lijn *) &p_vrk->lijn[i].text; 
	  if (p_lin->groep == GRP_TEXT && p_lin->aantal == 0 && p_lin->totaal == 0) continue;
	  else if (p_lin->groep >= 0 && p_lin->groep < 1000) {
		int pluix = kasplu.plu_req(p_lin->code, ARTCODE_LEN);
		if (pluix >= 0) {
		  if (p_lin->bits&STUKS) punten = kasplu.art_info.punten_st;
		  else punten = kasplu.art_info.punten;
		  p_vrk->punten[i] = 0.; p_vrk->bdr2punt[i] = 0.;
		  if (punten == 0.) p_vrk->bdr2punt[i] = p_lin->prijs;
		  else if (punten > 0) p_vrk->punten[i] = punten;
		}
	  }
	  adj_lijn(i);
	}

    if (BTWBONPercentage && nr<tafel_cnt) p_vrk->TERPLAATSE_flag=YES;
    else p_vrk->TERPLAATSE_flag=NO;

		if(WrkBonHdr.EIDnr[0]){ // Eid-gegevens terug juistzetten 
		  char buf[50];
			memcpy(p_vrk->EidNaam,WrkBonHdr.naam,40);
			memcpy(p_vrk->EidStraat,WrkBonHdr.straat,30);
			memcpy(p_vrk->EidPostCode,WrkBonHdr.postnr,6);
			memcpy(p_vrk->EidGemeente,WrkBonHdr.gemeente,25);
			memcpy(p_vrk->EidRRN,WrkBonHdr.EIDnr,20);
      add_ix_text(p_vrk->used++,txttxt[96]);
			strcpy(buf,txttxt[97]);	copystring(buf,2,40,WrkBonHdr.naam,37);	add_ix_text(p_vrk->used++,buf);
			strcpy(buf,txttxt[98]); copystring(buf,2,40,p_vrk->EidStraat,37); add_ix_text(p_vrk->used++,buf);
			strcpy(buf,txttxt[99]); copystring(buf,2,40,p_vrk->EidPostCode,7); copystring(buf,7,40,p_vrk->EidGemeente,25);	add_ix_text(p_vrk->used++,buf);
			strcpy(buf,txttxt[100]); copystring(buf,8,40,p_vrk->EidRRN,20);	add_ix_text(p_vrk->used++,buf);
			strcpy(buf,txttxt[101]); add_ix_text(p_vrk->used++,buf);
		}
    wrk_close(wrkref);
    if(KeepWRKBon420==0  || nr<KeepWRKBon420 || nr>490) wrk_del(nr);
    art_calc(YES);
  }
 ret:;
  ConSelect(old_screen);
  return;
}

static int get_nr(char exist)
{
  char buf[100], filexist;
  int i, key, j, pos_,off_=0,max_ico_=70,bonnr_, count, wrkref,bonwrk_size;
  long size;
	float punten;

  FOREVER{

		cls();
		disp_ikey(0,0,10,2,200,"1-69"); disp_ikey(10,0,10,2,201,"70-139");disp_ikey(20,0,10,2,202,"140-209");disp_ikey(30,0,10,2,203,"210-279");
		disp_ikey(40,0,10,2,204,"280-349");disp_ikey(50,0,10,2,205,"350-419");disp_ikey(60,0,10,2,206,"420-489");
		disp_key(72,0,8,2,22);
		j=0;
		for (i=off_; i<off_+max_ico_; i++) {
			filexist=wrk_exist(i);
			if (tafel_cnt>0) {
				if (filexist==exist) {
					if (i<tafel_cnt) {
						sprintf(buf,"TAF-%-2i",i+1);
						disp_ikey(1+(i%10)*8,2+(i/10)*4,8,4,3000+i,buf);
					}
					else {
						sprintf(buf,"TOG-%-2i",i+1-tafel_cnt);
						if (buf[5]==' ') buf[5]=0;
						disp_ikey(1+((j+tafel_cnt)%10)*8,2+((j+tafel_cnt)/10)*4,8,4,3000+i,buf,RGB(0,0,255));
						j++;
						if ((j+tafel_cnt)>=60) break;
					}
				}
			}
			else {
				if (filexist==exist) {
					if(i>100) sprintf(buf,"%3i",i); else sprintf(buf,"%2i",i);
					if(exist)	disp_ikey(11+((i-off_)%10)*6,3+((i-off_)/10)*2,6,2,3000+(i-off_),buf); // smaller
					else disp_ikey(11+((i-off_)%10)*6,3+((i-off_)/10)*3,6,3,3000+(i-off_),buf);
				}
				else {
          if(exist) disp_clr(11+((i-off_)%10)*6,3+((i-off_)/10)*2,6,2);
					else {
						if(KeepWRKBon420 && i>=KeepWRKBon420 && i<=490){
							if(i>100) sprintf(buf,"%3i",i); else sprintf(buf,"%2i",i);
							disp_ikey(11+((i-off_)%10)*6,3+((i-off_)/10)*3,6,3,3000+(i-off_),buf,RGB(0,0,255));
						}
						else disp_clr(11+((i-off_)%10)*6,3+((i-off_)/10)*3,6,3);
					}
				}
			}
		}

		FOREVER {
			key=kbchar();
			if (key==251*256) key=-1;
			else key/=0x10000;
			redo_key:;
			if (key==200) {off_=0;break;}
			if (key==201) {off_=70;break;}
			if (key==202) {off_=140;break;}
			if (key==203) {off_=210;break;}
			if (key==204) {off_=280;break;}
			if (key==205) {off_=350;break;}
			if (key==206) {off_=420;break;}
			if (key==22) return -2;
			if (key>=3000 && key<max_ico_+3000) {
	
				bonnr_=key-3000+off_;
				if(exist){ // bon tonen 
					redo_bonscreen:;
					disp_clr(6,18,68,7);
    			disp_panel(5,17,70,8,  PANEL_HOR_SMALLER | PANEL_VER_SMALLER | PANEL_WITH_EDGE,RGB(255,255,0));
		   	  disp_key(7,22,18,2,100);disp_key(25,22, 9,2,44); //	disp_key(41,22,18,2,22);
					memset((char *)&WrkBonHdr.DateTimeStr[0],0,WRK_BONHDR_LEN);
          wrkref=wrk_open(bonnr_);
          if (wrkref>=0){
			bonwrk_size = wrk_size;
            size=dseek(wrkref,0L,2); dseek(wrkref,0L,0);
						if(size>=WRK_BONHDR_LEN){
							count=(size-WRK_BONHDR_LEN)% bonwrk_size;
							if (count) { // nog oude bon zonder promo
							  bonwrk_size = &p_lin->EindeReclenKaslog - p_lin->text - sizeof(p_lin->text);
							  count = (size - WRK_BONHDR_LEN) % bonwrk_size;
							}
							if(count==0){ // nieuwe wrk-file met bonheader
								dread(wrkref,(char *)&WrkBonHdr.DateTimeStr[0],WRK_BONHDR_LEN);
							}
						}
						dclose(wrkref);
					}
					pos_=0;
					j=sprintf(buf,"Bon#  : ");disp_vid(7+pos_,18,buf,0); pos_+=j;
					j=sprintf(buf,"%-3d",bonnr_);disp_vid(7+pos_,18,buf,2); pos_+=j;
					j=sprintf(buf,"          %.20s",WrkBonHdr.DateTimeStr);disp_vid(7+pos_,18,buf,2); pos_+=j;
					j=sprintf(buf,"        Totaal: ");disp_vid(7+pos_,18,buf,0); pos_+=j;
					j=sprintf(buf,"%5.2f EUR",WrkBonHdr.TotTicket);disp_vid(7+pos_,18,buf,2); pos_+=j;
					pos_=0;
					j=sprintf(buf,"Klant : ");disp_vid(7+pos_,19,buf,0); pos_+=j;
					j=sprintf(buf,"%.40s",WrkBonHdr.naam);disp_vid(7+pos_,19,buf,2); pos_+=j;
					pos_=0;
					j=sprintf(buf,"%.40s",WrkBonHdr.BonText[0]);disp_vid(20+pos_,20,buf,2); pos_+=j;
					pos_=0;
					j=sprintf(buf,"%.40s",WrkBonHdr.BonText[1]);disp_vid(20+pos_,21,buf,2); pos_+=j;
		    	key=kbchar();
			    key/=0x10000;
    			if (key==100) return bonnr_;
					else if(key==44){
						wrkref=wrk_open(bonnr_);
						if (wrkref<0) goto redo_key;
						_clr_ticket();
						clr_line();
						size=dseek(wrkref,0L,2); dseek(wrkref,0L,0);
						memset((char *)&WrkBonHdr.DateTimeStr[0],0,WRK_BONHDR_LEN);
						bonwrk_size = wrk_size;
						if(size>=WRK_BONHDR_LEN){
							count=(size-WRK_BONHDR_LEN)% bonwrk_size;
							if (count) { // nog oude bon zonder promo
							  bonwrk_size = &p_lin->EindeReclenKaslog - p_lin->text - sizeof(p_lin->text);
							  count = (size - WRK_BONHDR_LEN) % bonwrk_size;
							}
							if (count == 0) { // nieuwe wrk-file met bonheader
							  dread(wrkref, (char *)&WrkBonHdr.DateTimeStr[0], WRK_BONHDR_LEN);
							  count = (size - WRK_BONHDR_LEN) / bonwrk_size;
							}
						}
						count=size/bonwrk_size;
						for (i=0; i<count; i++) {
							if (bonwrk_size!=dread(wrkref,(char *)&p_vrk->lijn[p_vrk->used].bits,bonwrk_size)) break;

							p_lin=(struct s_lijn *) &p_vrk->lijn[p_vrk->used].text; // puntenbasis terug invullen want die werden niet gesaved
							if (p_lin->groep>=0 && p_lin->groep<1000) {
								int pluix=kasplu.plu_req(p_lin->code,ARTCODE_LEN);
								if(pluix>=0){
									if (p_lin->bits&STUKS) punten=kasplu.art_info.punten_st;
									else punten=kasplu.art_info.punten;
									p_vrk->punten[p_vrk->used]=0.; p_vrk->bdr2punt[p_vrk->used]=0.;
									if (punten==0.) p_vrk->bdr2punt[p_vrk->used]=p_lin->prijs;
									else if (punten>0) p_vrk->punten[p_vrk->used]=punten;
								}
							}
							adj_lijn(p_vrk->used++);
					 }
					 if (BTWBONPercentage && bonnr_<tafel_cnt) p_vrk->TERPLAATSE_flag=YES;
					 else p_vrk->TERPLAATSE_flag=NO;
					 dclose(wrkref);
					 art_calc(YES);
					 add_einde(GRP_MEETOTAAL,p_vrk->totaal[0]);
	  			 prt_cod(2); prt_cod(3);
					 short jj, mm, dd;
					 jddate(dateget(),&jj,&mm,&dd);
					 if(PrtOnWRKPutFlag!=2 && bonnr_>=140 && bonnr_<=500) sprintf(buf,"BON# %-3d",bonnr_); // tussen 140 en 490 default geen datum afdrukken (wel bij D in paramaters)
					 else sprintf(buf, "BON# %-3d  %.20s", bonnr_,WrkBonHdr.DateTimeStr);  // else sprintf(buf,"BON# %-3d  %2d/%02d/%4d",bonnr_,dd,mm,jj);
					 prt_nl(buf);
					 prt_cod(4);

					memcpy(buf,BCPREFIXWERKBON,9);
					j=bonnr_;
					for (i=0; i<3; i++) {
						buf[11-i]='0'+j%10;
						j=j/10;
					}
					buf[12]=0;
					prt_ean(buf);

					 if(WrkBonHdr.BonText[0][0]) prt_nl(WrkBonHdr.BonText[0]);
					 if(WrkBonHdr.BonText[1][0]) prt_nl(WrkBonHdr.BonText[1]);
					 close_bon(NO,true);
					 prt_close();
				   _clr_ticket();
				   clr_line();
					 goto redo_bonscreen;
					}
					else goto redo_key;
  			}
				else return key-3000+off_;
			}
		}
	}
}
 
int wrk_open(int nr)
{
  int wrkref;
  char buffer[20],buf1[4];
 
  movmem("KASBON00.WRK",buffer,sizeof(buffer));
	if(nr<100) sprintf(buf1,"N%02i",nr); else sprintf(buf1,"%03i",nr); 
	movmem(buf1,&buffer[5],3);
  //nr=nr%100;
  //buffer[6]='0'+nr/10; buffer[7]='0'+nr%10;
  mkfilnam(buffer);
  wrkref=dopen(filnam,RDWRMODE);
  if (wrkref<0) wrkref=dcreat(filnam,CREAMODE);
  return wrkref;
}

void wrk_del(int nr)
{
  char buffer[20],buf1[4];
 
  movmem("KASBON00.WRK",buffer,sizeof(buffer));
	if(nr<100) sprintf(buf1,"N%02i",nr); else sprintf(buf1,"%03i",nr); 
	movmem(buf1,&buffer[5],3);
 
 /* movmem("KASBON00.WRK",buffer,sizeof(buffer));
  nr=nr%100;
  buffer[6]='0'+nr/10; buffer[7]='0'+nr%10;*/
  mkfilnam(buffer);
  unlink(filnam);
}
 
void wrk_close(int wrkref)
{
  dwrite(wrkref,(char *)&wrkref,0);/* trucate file at current position */
  dclose(wrkref);
}



// kaspromo.cpp


extern struct {
  short int formule;
  float getal[4];
  char dummy[7];
} promo_desc[20];

void insert_line(int art_ptr, int toadd)
{
  int to_move,j;
 
  to_move=p_vrk->used-art_ptr-1;
  p_lin=(struct s_lijn *) p_vrk->lijn[p_vrk->used+toadd-1].text;
  for (j=0; j<to_move; j++) {
    movmem((char *)(p_lin-toadd),(char *)p_lin,sizeof(struct s_lijn));
    p_lin--;
  }
  p_lin=(struct s_lijn *) p_vrk->lijn[art_ptr+1].text;
  p_vrk->used+=toadd;
}

void CalcArtikelPromo(int art_ptr)
{
  int formule, k, dig, convertqlv_, q_mixlines_, orig_used_, max_promo_per_ticket_,ptr_last_art_,promo_qlv_cnv_; 
  float bdf_,promoaantal, promogratis, gratis, aantal, getal[4 + 1], q_bak, kortingpct_, kortingBTWpct_,totaalaantal_, kortingaantal_, prijs_, PG_aantal_, stuksaantal_,qlv_coef_;
  double PG_totaal_;
  char promo_bf,gr_art_code[ARTCODE_LEN],gr_text[ARTNAAM_LEN],last_mixcode_[ARTCODE_LEN],str_[30],*code_promoleeg;
  long promo_groepscode=0;
 

  formule = kasplu.art_info.PromoFormule;
  promo_bf = kasplu.art_info.PromoBakFles;
  max_promo_per_ticket_ = kasplu.art_info.MaxPromoPerTicket;
  for (k = 0; k < 4; k++) getal[k] = kasplu.art_info.PromoFormuleGetallen[k];
  movmem(kasplu.art_info.PromoGratisArtCode, gr_art_code, ARTCODE_LEN);
  movmem(kasplu.art_info.PromoGratisTekst, gr_text, ARTNAAM_LEN);
  promo_groepscode = kasplu.art_info.PromoGroepsCode;
  ptr_last_art_ = art_ptr;
  orig_used_ = p_vrk->used;
  PG_aantal_ = 0; PG_totaal_ = 0; q_mixlines_ = 0; zeros(last_mixcode_, sizeof last_mixcode_); promo_qlv_cnv_ = NO; kortingBTWpct_ = 0;
  if (kasplu.art_info.PromoGroepsCode && kasplu.art_info.PromoFormule>=5) { // artikel behoort bij mixed promo
	promo_groepscode = kasplu.art_info.PromoGroepsCode;
	for (k = 0; k <= art_ptr; k++) { // eerst alle promo's van deze code schrappen
	  p_vrk->lijn[k].PromoAantalUsed = 0; // used aantal resetten voor alle lijnen
	  if (p_vrk->lijn[k].PromoGroepsCode == promo_groepscode && !(p_vrk->lijn[art_ptr].bits&AUTO_LEEG)) {
		if (kortingBTWpct_ < p_vrk->lijn[k].btw) kortingBTWpct_ = p_vrk->lijn[k].btw; // hoogste BTW% nemen voor korting bij mixed promo en BTW
	//	if (last_mixcode_[0]/* && cmpstr(p_vrk->lijn[k].code, last_mixcode_, ARTCODE_LEN)*/) fl_artmix_ = YES;
		bcopy(p_vrk->lijn[k].code, last_mixcode_, ARTCODE_LEN); //if (k < art_ptr) q_mixlines_++;
		p_vrk->lijn[k].PromoAantalUsed = p_vrk->lijn[k].PromoBasisAantal;
		if (p_vrk->lijn[k].PromoBasisAantal != p_vrk->lijn[k].aantal) promo_qlv_cnv_ = YES;
		if (p_vrk->lijn[k].PromoFormule == 5) { // korting%
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep > 0 && p_vrk->lijn[k + 1].groep < 99) { // aantal uitgesplitste lijn terug op origineel zetten
			p_vrk->lijn[k].aantal += p_vrk->lijn[k + 1].aantal; 
			adj_lijn(k);
			_del_line(k + 1);
		  }
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep == GRP_FKORT) _del_line(k + 1);
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep == GRP_PKORT) _del_line(k + 1);
		}
		else if (p_vrk->lijn[k].PromoFormule == 6) { // EUR korting
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep == GRP_FKORT) _del_line(k + 1);
		}
		else if (p_vrk->lijn[k].PromoFormule == 7) {// aantal gratis
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep > 0 && p_vrk->lijn[k + 1].groep < 99) { // aantal uitgesplitste lijn terug op origineel zetten
			p_vrk->lijn[k].aantal += p_vrk->lijn[k + 1].aantal;
			adj_lijn(k);
			_del_line(k + 1);
		  }
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep == GRP_FKORT) _del_line(k + 1);
		}
		else if (p_vrk->lijn[k].PromoFormule == 8) { // gratis artikel
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && compare(p_vrk->lijn[k + 1].code, gr_art_code, ARTCODE_LEN) == 0) _del_line(k + 1);
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].fl_promoLijn) _del_line(k + 1); // leeggoed van promoartikel
		}
		else if (p_vrk->lijn[k].PromoFormule == 9) { // gratis text
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep == GRP_TEXT) _del_line(k + 1); // gratis tekstlijn wegdoen
		}
		else if (p_vrk->lijn[k].PromoFormule == 10) { // staffelkorting in %
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep == GRP_PKORT) _del_line(k + 1);
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep == GRP_FKORT) _del_line(k + 1); // indien max bereikt was
		}
		else if (p_vrk->lijn[k].PromoFormule == 11) { // x aantal voor een bedrag
		  if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && p_vrk->lijn[k + 1].groep == GRP_FKORT) _del_line(k + 1);
		}

		if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[k + 1].groep == GRP_TEXT) _del_line(k + 1);

		if (k < art_ptr) { art_ptr -= orig_used_ - p_vrk->used; orig_used_ = p_vrk->used; }// pointer juistzetten na deleten lijnen 
		ptr_last_art_ = art_ptr;
		if (k < art_ptr) { q_mixlines_++; PG_aantal_ += p_vrk->lijn[k].PromoBasisAantal; PG_totaal_ += p_vrk->lijn[k].totaal; } // op einde doen na correctie
	  }
	  
	}
	q_mixlines_++; // incl. laatste artikel
  }
  if (q_mixlines_ <= 1) { PG_aantal_ = 0; PG_totaal_ = 0; }
  q_bak = (float)kasplu.art_info.st_verp; if (q_bak < 1) q_bak = 1;
  if (q_bak == 1 && promo_bf == 'F') promo_bf = 'B';
  prijs_ = p_vrk->lijn[art_ptr].prijs;
  aantal = p_vrk->lijn[art_ptr].aantal; convertqlv_ = NO;
  if (promo_bf != 'F' || q_bak==1) {  // bij bak, stuks herrekenen naar bak of indien stuks en aantal/bak ==1 dan als bak behandelen
	if (p_vrk->lijn[art_ptr].bits&STUKS) {
	  aantal /= q_bak; if (q_bak != 1) convertqlv_ = 1; promo_qlv_cnv_ = YES;
	}
  }
  else { // bij stuks, bak herrekenen naar stuks
	if (!(p_vrk->lijn[art_ptr].bits&STUKS)) {
	  aantal *= q_bak; if (q_bak != 1) convertqlv_ = 2; promo_qlv_cnv_ = YES;
	}
  }
  aantal = round_it((double)(aantal), (double)0.001);
  p_vrk->lijn[art_ptr].PromoGroepsCode = kasplu.art_info.PromoGroepsCode;
  p_vrk->lijn[art_ptr].PromoBasisAantal = aantal; p_vrk->lijn[art_ptr].PromoAantalUsed = aantal;
  p_vrk->lijn[art_ptr].PromoFormule = formule;
  aantal += PG_aantal_; 
  if (PromoNotOnHorecaPrice == 'J' && p_vrk->prx_ix>0) formule = 0; // NIET toepassen op horecaprijzen
  if (q_mixlines_>1 && (formule == 5 || formule == 7 || formule == 11)) { // bij 2-de k%, 1+1 of 2 voor x EUR enkel gebruikte artikels nemen voor gemiddelde prijs
	totaalaantal_ = getal[0]; if (totaalaantal_ == 0) totaalaantal_ = 1;
	bdf_ = aantal / totaalaantal_;
	if (((int)(bdf_) * 100) != (int)(bdf_ * 100)) { // het is geen veelvoud, dan controleren
	  stuksaantal_ = round_it((double)(aantal - (int)aantal),(double)(0.001)); // aantal niet gebruikte stuks berekenen (na komma)
	  if(stuksaantal_){ // er zijn ongebruikte stuks, deze niet laten meetellen in mix
		for (k = art_ptr; k >= 0; k--) { // overbodige stuks lijnen uit berekening halen
		  if (p_vrk->lijn[k].bits&STUKS && p_vrk->lijn[k].PromoAantalUsed && stuksaantal_>= p_vrk->lijn[k].PromoAantalUsed) {
			stuksaantal_ -= p_vrk->lijn[k].PromoAantalUsed; aantal -= p_vrk->lijn[k].PromoAantalUsed; PG_totaal_ -= p_vrk->lijn[k].totaal; p_vrk->lijn[k].PromoAantalUsed = 0;
			q_mixlines_--; if (stuksaantal_ < 0.01) { stuksaantal_ = 0; aantal = round_it((double)aantal, (double)1.0);}
			if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[k + 1].groep == GRP_TEXT) _del_line(k + 1);
			if (stuksaantal_ < 0.01 || q_mixlines_<=1) break;
		  }
		}
	  }
	  bdf_ = aantal / totaalaantal_;
	  if (q_mixlines_ > 1 && ((int)(bdf_) * 100) != (int)(bdf_ * 100)) { // het is geen veelvoud, dan losse artikels wegdoen
		stuksaantal_ = round_it((double)((bdf_ - (int)bdf_)*totaalaantal_),(double)(0.001)); // aantal teveel, losse artikels wegdoen
		for (k = art_ptr; k >= 0; k--) { // losse overbodige lijnen  wegdoen tot veelvoud
		  if (p_vrk->lijn[k].PromoAantalUsed && stuksaantal_>=p_vrk->lijn[k].PromoAantalUsed) {
			stuksaantal_ -= p_vrk->lijn[k].PromoAantalUsed; aantal -= p_vrk->lijn[k].PromoAantalUsed; PG_totaal_ -= p_vrk->lijn[k].totaal; p_vrk->lijn[k].PromoAantalUsed = 0;
			q_mixlines_--; if (stuksaantal_ < 0.01) { stuksaantal_ = 0; aantal = round_it((double)aantal,(double)1.0); }
			if (p_vrk->lijn[k + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[k + 1].groep == GRP_TEXT) _del_line(k + 1);
			if (stuksaantal_ < 0.01 || q_mixlines_ <= 1) break;
		  }
		}
	  }
	  if (promo_qlv_cnv_ || q_mixlines_ > 1) {		// ???
		if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
		  for (k = 0; k < art_ptr; k++) {
			if (p_vrk->lijn[k].PromoAantalUsed) {
			  insert_line(k, 1);
			  movmem(p_vrk->lijn[k].code, p_lin->code, sizeof(p_lin->code));
			  _clr_text(p_lin->text);
			  copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
			  p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
			  adj_lijn(k + 1);
			  art_ptr++; k++;
			}
		  }
		}
		ptr_last_art_ = -1;
		for (k = art_ptr; k >= 0; k--) {
		  if (!(p_vrk->lijn[k].bits&AUTO_LEEG) && ptr_last_art_ == -1) ptr_last_art_ = k;
		  if (p_vrk->lijn[k].PromoAantalUsed) break;
		}
		if (k >= 0) {
		  art_ptr = k;
		  if (art_ptr<ptr_last_art_) {
			PG_totaal_ = 0;
			for (k = 0; k <= art_ptr; k++) {
			  if (p_vrk->lijn[k].bits&AUTO_LEEG) continue;
			  if (p_vrk->lijn[k].PromoBasisAantal) qlv_coef_ = p_vrk->lijn[k].aantal / p_vrk->lijn[k].PromoBasisAantal; else qlv_coef_ = 1;
			  if (p_vrk->lijn[k].PromoAantalUsed) PG_totaal_ += p_vrk->lijn[k].totaal* p_vrk->lijn[k].PromoAantalUsed*qlv_coef_ / p_vrk->lijn[k].aantal;
			}
		  }
		}
	  }
	}  
  }
  if (formule == 5) { // vanaf aantal,vb 2 kopen en dan is er  1 aan %korting    vb 2 kopen en dan is 2-de aan -40% korting
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && p_vrk->lijn[art_ptr + 1].groep == GRP_FKORT) _del_line(art_ptr + 1);
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && p_vrk->lijn[art_ptr + 1].groep == GRP_PKORT) _del_line(art_ptr + 1);
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[art_ptr + 1].groep == GRP_TEXT) _del_line(art_ptr + 1);
	totaalaantal_ = getal[0]; if (totaalaantal_ == 0) totaalaantal_ = 1;
	kortingaantal_ = getal[2];
	if (kortingaantal_ == 0 || kortingaantal_ >= totaalaantal_) kortingaantal_ = totaalaantal_;
	if (totaalaantal_ && (aantal >= totaalaantal_ || -aantal >= totaalaantal_)) {
	  if ((totaalaantal_==1 || aantal==totaalaantal_) && totaalaantal_ == kortingaantal_) { // gewoon korting% op alles indien totaal == 1 
		if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
		  insert_line(art_ptr, 1);
		  movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		  _clr_text(p_lin->text);
		  copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
		  p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
		  adj_lijn(art_ptr + 1);
		}
		insert_line(art_ptr, 1);
		movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		p_lin->btw = p_vrk->lijn[art_ptr].btw;
		p_lin->bits = AUTO_LEEG;
		p_lin->aantal = 0.;
		p_lin->prijs = getal[1];
		p_lin->groep = GRP_PKORT;
		adj_lijn(art_ptr + 1);
		if (kasplu.art_info.PromoGroepsCode) {
		  for (k = 0; k < art_ptr; k++) {
			if (p_vrk->lijn[k].PromoGroepsCode == kasplu.art_info.PromoGroepsCode && !(p_vrk->lijn[k].bits&AUTO_LEEG)) {
			  if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
				insert_line(k, 1);
				movmem(p_vrk->lijn[k].code, p_lin->code, sizeof(p_lin->code));
				_clr_text(p_lin->text);
				copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
				p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
				adj_lijn(k + 1); art_ptr++;
			  }
			  insert_line(k, 1);
			  movmem(p_vrk->lijn[k].code, p_lin->code, sizeof(p_lin->code));
			  p_lin->btw = p_vrk->lijn[k].btw;
			  p_lin->bits = AUTO_LEEG;
			  p_lin->aantal = 0.;
			  p_lin->prijs = getal[1];
			  p_lin->groep = GRP_PKORT;
			  adj_lijn(k + 1); art_ptr++;
			}
		  }
		}
	  }
	  else { // korting % 1 + 1 aan 50 %
		k = (int)(aantal / totaalaantal_);
		if (max_promo_per_ticket_ && k > max_promo_per_ticket_) k = max_promo_per_ticket_;
		promoaantal = k * kortingaantal_;
		//if ((aantal - k * totaalaantal_) > (totaalaantal_- kortingaantal_)) {
		//  promoaantal += aantal - k * (totaalaantal_ - kortingaantal_) - totaalaantal_;
		//}
		if (promoaantal) {
		  if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
			insert_line(art_ptr, 1);
			movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
			_clr_text(p_lin->text);
			copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
			p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
			adj_lijn(art_ptr + 1);
		  }
		  if (promo_qlv_cnv_ || convertqlv_ || q_mixlines_>1) {  // indien gewijzigd van eenheid of mixed promo, dan korting als EUR-bedrag nemen
			if (convertqlv_ == 1) prijs_ *= q_bak; 
			else if (convertqlv_ == 2) prijs_ /= q_bak;
			if(!(p_vrk->lijn[art_ptr+1].bits&AUTO_LEEG) || p_vrk->lijn[art_ptr + 1].groep!= GRP_FKORT) insert_line(art_ptr, 1);
			movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
			p_lin->btw = p_vrk->lijn[art_ptr].btw;
			p_lin->bits = AUTO_LEEG;
			p_lin->aantal = 0.;
			if ((promo_qlv_cnv_ || q_mixlines_ > 1) && aantal) {
			  if (art_ptr < ptr_last_art_) prijs_ = PG_totaal_ / aantal;
			  else prijs_ = (p_vrk->lijn[art_ptr].prijs * p_vrk->lijn[art_ptr].aantal + PG_totaal_) / aantal;
			}
			p_lin->prijs = (float)(round_it((double)((prijs_*promoaantal)* getal[1] / 100.), def_round));
			p_lin->groep = GRP_FKORT;
			adj_lijn(art_ptr + 1);
		  }

		  else {
			insert_line(art_ptr, 1);
			p_vrk->lijn[art_ptr].aantal -= promoaantal;
			movmem(p_vrk->lijn[art_ptr].text, p_lin->text, sizeof(struct s_lijn));
			p_lin->aantal = promoaantal;
			p_lin->bits |= AUTO_LEEG;
			p_lin->prijs = (float)(round_it((double)(p_lin->prijs*(100. - getal[1]) / 100.), def_round));
			p_lin->totaal = round_it((double)(p_lin->prijs*p_lin->aantal), def_round);
			if (p_lin->bits&STUKS) { movmem(txttxt[7], &p_lin->text[POS_AANTAL + 4], 2); dig = 3; }
			else dig = 5;
			conv_getal((double)p_lin->aantal, &p_lin->text[POS_AANTAL], dig, NO, 3);
			adj_lijn(art_ptr);
			adj_lijn(art_ptr + 1);
		  }
		}
	  }
	}
  }
  if (formule == 6) { // vanaf aantal, dan EUR-korting op x artikels vb 2 kopen en dan is er  1 aan -0.5 EUR korting
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && p_vrk->lijn[art_ptr + 1].groep == GRP_FKORT) _del_line(art_ptr + 1);
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[art_ptr + 1].groep == GRP_TEXT) _del_line(art_ptr + 1);
	totaalaantal_ = getal[0]; if (totaalaantal_ == 0) totaalaantal_ = 1;
	kortingaantal_ = getal[2];
	if (kortingaantal_ == 0 || kortingaantal_ >= totaalaantal_) kortingaantal_ = totaalaantal_;
	if (totaalaantal_ && (aantal >= totaalaantal_ || -aantal >= totaalaantal_)) {
      k = (int)(aantal / totaalaantal_);
	  if (max_promo_per_ticket_ && k > max_promo_per_ticket_) k = max_promo_per_ticket_;
	  promoaantal = k * kortingaantal_;
	  if (promoaantal) {
		if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
		  insert_line(art_ptr, 1);
		  movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		  _clr_text(p_lin->text);
		  copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
		  p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
		  adj_lijn(art_ptr + 1);
		}
		if (!(p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG) || p_vrk->lijn[art_ptr + 1].groep != GRP_FKORT) insert_line(art_ptr, 1);
		movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		p_lin->btw = p_vrk->lijn[art_ptr].btw;
		p_lin->bits = AUTO_LEEG;
		p_lin->aantal = 0.;
		p_lin->prijs = (float)(round_it((double)(promoaantal* getal[1]), def_round));
		p_lin->groep = GRP_FKORT;
		adj_lijn(art_ptr + 1);
	  }
	}
  }

  if (formule ==7) { // 1+1 gratis
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && compare(p_vrk->lijn[art_ptr].code, p_vrk->lijn[art_ptr + 1].code,ARTCODE_LEN) == 0) _del_line(art_ptr + 1);
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[art_ptr + 1].groep == GRP_TEXT) _del_line(art_ptr + 1);
	totaalaantal_ = getal[0]; if (totaalaantal_ == 0) totaalaantal_ = 1;
	promogratis = getal[1];
	if (totaalaantal_ && (aantal >= totaalaantal_ || -aantal >= totaalaantal_)) {
	  k = (int)(aantal / totaalaantal_);
	  //    gratis=k*promogratis;
	   //    if (aantal-k*(promoaantal+promogratis)>promoaantal) {
	   //      gratis+=aantal-k*(promoaantal+promogratis)-promoaantal;
	   //    }
	  if (max_promo_per_ticket_ && k > max_promo_per_ticket_) k = max_promo_per_ticket_;
	  gratis = k * promogratis;
	  if ((aantal - k * totaalaantal_) > (totaalaantal_-promogratis) && (max_promo_per_ticket_ && k < max_promo_per_ticket_)) {
		gratis += aantal - (k * totaalaantal_) - (totaalaantal_ - promogratis);
	  }
	  if (gratis) {
		if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
		  insert_line(art_ptr, 1);
		  movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		  _clr_text(p_lin->text);
		  copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
		  p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
		  adj_lijn(art_ptr + 1);
		}
		if (promo_qlv_cnv_|| convertqlv_ || q_mixlines_ > 1) {  // indien gewijzigd van eenheid of mixed promo, dan korting als EUR-bedrag nemen
		  if (convertqlv_ == 1) prijs_ *= q_bak;
		  else if (convertqlv_ == 2) prijs_ /= q_bak;
		  if (!(p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG) || p_vrk->lijn[art_ptr + 1].groep != GRP_FKORT) insert_line(art_ptr, 1);
		  movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		  if (kortingBTWpct_ < p_vrk->lijn[art_ptr].btw) kortingBTWpct_ = p_vrk->lijn[art_ptr].btw; // BTW% van dit artikel ook meenemen, anders 0% indien geen mixed promo (vb. enkel omrekening stuks/bak bij leeggoed)
		  p_lin->btw = kortingBTWpct_; // hoogste BTW% nemen voor korting bij mixed promo en mixed BTW
		  // p_lin->btw = p_vrk->lijn[art_ptr].btw;
		  p_lin->bits = AUTO_LEEG;
		  p_lin->aantal = 0.;
		  if (q_mixlines_ > 1 && aantal) {
			if (art_ptr < ptr_last_art_) prijs_ = PG_totaal_ / aantal;
			else prijs_ = (p_vrk->lijn[art_ptr].prijs * p_vrk->lijn[art_ptr].aantal + PG_totaal_) / aantal;
		  }
		  p_lin->prijs = (float)(round_it((double)(prijs_*gratis), def_round));
		  p_lin->groep = GRP_FKORT;
		  _clr_text(p_lin->text);
		  zeros(str_, sizeof str_); sprintf_s(str_, 25, "Korting %d+%d gratis", (int)(totaalaantal_ - promogratis), (int)(promogratis)); 
		  copynaam(str_, p_lin->text + POS_NAAM, 20);
		  p_lin->fl_promoLijn = YES;
		  adj_lijn(art_ptr + 1);
		}
		else {
		  insert_line(art_ptr, 1);
		  p_vrk->lijn[art_ptr].aantal -= gratis;
		  movmem(p_vrk->lijn[art_ptr].text, p_lin->text, sizeof(struct s_lijn));
		  p_lin->aantal = gratis;
		  p_lin->bits |= AUTO_LEEG;
		  p_lin->prijs = 0.;
		  p_lin->totaal = 0.;
		  if (p_lin->bits&STUKS) { movmem(txttxt[7], &p_lin->text[POS_AANTAL + 4], 2); dig = 3; }
		  else dig = 5;
		  conv_getal((double)p_lin->aantal, &p_lin->text[POS_AANTAL], dig, NO, 3);
		  adj_lijn(art_ptr);
		  adj_lijn(art_ptr + 1);
		}
	  }
	}
  }
  
  if (formule == 8) { //  vanaf aantal gratis artikel

	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && compare(p_vrk->lijn[art_ptr + 1].code, gr_art_code, ARTCODE_LEN) == 0) _del_line(art_ptr + 1);
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && p_vrk->lijn[art_ptr + 1].fl_promoLijn == YES) _del_line(art_ptr + 1); // leeggoed
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[art_ptr + 1].groep == GRP_TEXT) _del_line(art_ptr + 1);
	totaalaantal_ = getal[0];
	if (totaalaantal_ && (aantal >= totaalaantal_ || -aantal >= totaalaantal_)) {
	  gratis = (int)(aantal / totaalaantal_);
	  if (max_promo_per_ticket_ && gratis > max_promo_per_ticket_) gratis = max_promo_per_ticket_;
	  if (gratis) {
		if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
		  insert_line(art_ptr, 1);
		  movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		  _clr_text(p_lin->text);
		  copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
		  p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
		  adj_lijn(art_ptr + 1);
		}
		insert_line(art_ptr, 1);
		// p_vrk->lijn[art_ptr].aantal -= gratis;
		movmem(p_vrk->lijn[art_ptr].text, p_lin->text, sizeof(struct s_lijn));
		movmem(gr_art_code, p_lin->code, ARTCODE_LEN);
		int pluix = kasplu.plu_req(p_lin->code, ARTCODE_LEN); // kan zijn dat product niet gevonden wordt (GROEP gebruikt)
		code_promoleeg = kasplu.art_info.code_l;
		_clr_text(p_lin->text);
		copynaam(kasplu.art_info.naam, p_lin->text + POS_NAAM, 20);
		p_lin->groep = kasplu.art_info.groep;
		p_lin->btw = kasplu.art_info.btw;
		p_lin->aantal = gratis;
		p_lin->bits |= AUTO_LEEG;
		p_lin->prijs = 0.;
		p_lin->totaal = 0.;
		p_lin->fl_promoLijn = YES;
		//if (p_lin->bits&STUKS) { movmem(txttxt[7], &p_lin->text[POS_AANTAL + 4], 2); dig = 3; } niet voor gratis artikel
		//else dig = 5;
		dig = 5;
		conv_getal((double)p_lin->aantal, &p_lin->text[POS_AANTAL], dig, NO, 3);
		adj_lijn(art_ptr + 1);

		if ((p_vrk->leeg_flag & 3) && *code_promoleeg) {
		  pluix = kasplu.plu_req(code_promoleeg, ARTCODE_LEN);
		  if (pluix >= 0) {
			insert_line(art_ptr+1, 1);
			movmem(p_vrk->lijn[art_ptr].text, p_lin->text, sizeof(struct s_lijn));
			movmem(kasplu.art_info.code, p_lin->code, ARTCODE_LEN);
			copynaam(kasplu.art_info.naam, p_lin->text + POS_NAAM, 20);
    		p_lin->aantal = gratis;
			p_lin->bits = AUTO_LEEG;
			p_lin->groep = kasplu.art_info.groep;
			p_lin->btw = kasplu.art_info.btw;
			p_lin->prijs = kasplu.art_info.prijs[p_vrk->prx_ix];
			p_lin->fl_promoLijn = YES;
			dig = 5;
			conv_getal((double)p_lin->aantal, &p_lin->text[POS_AANTAL], dig, NO, 3);
			adj_lijn(art_ptr + 2);
		  }
		}




	  }
	}
  }

  if (formule == 9) { //  vanaf aantal gratis tekst
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && p_vrk->lijn[art_ptr + 1].groep == GRP_TEXT) _del_line(art_ptr + 1); // gratis tekstlijn wegdoen
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[art_ptr + 1].groep == GRP_TEXT) _del_line(art_ptr + 1);
	totaalaantal_ = getal[0];
	if (totaalaantal_ && (aantal >= totaalaantal_ || -aantal >= totaalaantal_)) {
	  gratis = (int)(aantal / totaalaantal_);
	  if (max_promo_per_ticket_ && gratis > max_promo_per_ticket_) gratis = max_promo_per_ticket_;
	  if (gratis) {
		if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
		  insert_line(art_ptr, 1);
		  movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		  _clr_text(p_lin->text);
		  copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
		  p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
		  adj_lijn(art_ptr + 1);
		}
		insert_line(art_ptr, 1);
		movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		_clr_text(p_lin->text);
		p_lin->btw = p_vrk->lijn[art_ptr].btw;
		p_lin->bits = AUTO_LEEG;
		p_lin->groep = GRP_TEXT;
		p_lin->aantal = gratis;
		p_lin->prijs = 0;
		p_lin->fl_promoLijn = YES;
		copynaam(gr_text, p_lin->text + POS_NAAM,20);
		conv_getal((double)p_lin->aantal, &p_lin->text[POS_AANTAL], 5, NO, 3);
		adj_lijn(art_ptr + 1);
	  }
	}
  }
  if (formule == 10) { // vanaf aantal, kort%, vanaf aantal1 korting1% vb <6 0, 6-11 10%, >11 15%
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && p_vrk->lijn[art_ptr + 1].groep == GRP_PKORT) _del_line(art_ptr + 1);
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[art_ptr + 1].groep == GRP_TEXT) _del_line(art_ptr + 1);
	kortingpct_ = 0;
	if (getal[2] && (aantal >= getal[2] || -aantal >= getal[2])) kortingpct_ = getal[3];
	else if(getal[0] && (aantal>=getal[0] || -aantal >= getal[0])) kortingpct_ = getal[1];
	if (kortingpct_) { // gewoon korting% op alles
	  if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
		insert_line(art_ptr, 1);
		movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		_clr_text(p_lin->text);
		copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
		p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
		adj_lijn(art_ptr + 1);
	  }

	  if (max_promo_per_ticket_&& aantal > max_promo_per_ticket_) { // maar korting geven tot dat aantal, en dan in EUR zetten
		if (!(p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG) || p_vrk->lijn[art_ptr + 1].groep != GRP_FKORT) insert_line(art_ptr, 1);
		movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		p_lin->btw = p_vrk->lijn[art_ptr].btw;
		p_lin->bits = AUTO_LEEG;
		p_lin->aantal = 0.;
		prijs_ = p_vrk->lijn[art_ptr].prijs*max_promo_per_ticket_;
		p_lin->prijs = (float)(round_it((double)(prijs_*kortingpct_/100.), def_round));
		p_lin->groep = GRP_FKORT;
		_clr_text(p_lin->text);
		zeros(str_, sizeof str_); sprintf_s(str_, 25, "Korting %d%% op %d St", (int)(kortingpct_), (int)(max_promo_per_ticket_));
		copynaam(str_, p_lin->text + POS_NAAM, 20);
		p_lin->fl_promoLijn = YES;
		adj_lijn(art_ptr + 1);
	  }
	  else {
		insert_line(art_ptr, 1);
		movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		p_lin->btw = p_vrk->lijn[art_ptr].btw;
		p_lin->bits = AUTO_LEEG;
		p_lin->aantal = 0.;
		p_lin->prijs = kortingpct_;
		p_lin->groep = GRP_PKORT;
		adj_lijn(art_ptr + 1);
		if (kasplu.art_info.PromoGroepsCode) {
		  for (k = 0; k < art_ptr; k++) {
			if (p_vrk->lijn[k].PromoGroepsCode == kasplu.art_info.PromoGroepsCode && !(p_vrk->lijn[k].bits&AUTO_LEEG)) {
			  if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
				insert_line(k, 1);
				movmem(p_vrk->lijn[k].code, p_lin->code, sizeof(p_lin->code));
				_clr_text(p_lin->text);
				copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
				p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
				adj_lijn(k + 1); art_ptr++;
			  }
			  insert_line(k, 1);
			  movmem(p_vrk->lijn[k].code, p_lin->code, sizeof(p_lin->code));
			  p_lin->btw = p_vrk->lijn[k].btw;
			  p_lin->bits = AUTO_LEEG;
			  p_lin->aantal = 0.;
			  p_lin->prijs = kortingpct_;
			  p_lin->groep = GRP_PKORT;
			  adj_lijn(k + 1); art_ptr++;
			}
		  }
		}
	  }
	}
  }
  if (formule == 11) { // vanaf aantal, vast bedrag  vb 2 kopen voor 5 EUR
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && p_vrk->lijn[art_ptr + 1].groep == GRP_FKORT) _del_line(art_ptr + 1);
	if (p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG && kasplu.art_info.ex_text[0] && p_vrk->lijn[art_ptr + 1].groep == GRP_TEXT) _del_line(art_ptr + 1);
	totaalaantal_ = getal[0]; if (totaalaantal_ == 0) totaalaantal_ = 1;
	kortingaantal_ = totaalaantal_; 
	if (totaalaantal_ && (aantal >= totaalaantal_ || -aantal >= totaalaantal_)) {
	  k = (int)(aantal / totaalaantal_);
	  if (max_promo_per_ticket_ && k > max_promo_per_ticket_) k = max_promo_per_ticket_;
	  promoaantal = k * kortingaantal_;
	  if (promoaantal) {
		if (kasplu.art_info.ex_text[0]) { // promo tekst invoegen
		  insert_line(art_ptr, 1);
		  movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		  _clr_text(p_lin->text);
		  copynaam(kasplu.art_info.ex_text, p_lin->text + POS_NAAM, sizeof(kasplu.art_info.ex_text));
		  p_lin->bits = AUTO_LEEG; p_lin->groep = GRP_TEXT;
		  adj_lijn(art_ptr + 1);
		}

		if (convertqlv_ == 1) prijs_ *= q_bak;
		else if (convertqlv_ == 2) prijs_ /= q_bak;
		if (!(p_vrk->lijn[art_ptr + 1].bits&AUTO_LEEG) || p_vrk->lijn[art_ptr + 1].groep != GRP_FKORT) insert_line(art_ptr, 1);
		movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
		p_lin->btw = p_vrk->lijn[art_ptr].btw;
		p_lin->bits = AUTO_LEEG;
		p_lin->aantal = 0.;
		if (q_mixlines_ > 1 && aantal) {
		  if (art_ptr < ptr_last_art_) prijs_ = PG_totaal_ / aantal;
		  else prijs_ = (p_vrk->lijn[art_ptr].prijs * p_vrk->lijn[art_ptr].aantal + PG_totaal_) / aantal;
		}
		p_lin->prijs = (float)(round_it((double)((prijs_-getal[1]/kortingaantal_)*promoaantal), def_round));
		p_lin->groep = GRP_FKORT;
		zeros(str_, sizeof str_); sprintf_s(str_, 29, "%d St voor %.2f EUR", (int)(kortingaantal_), (double)(getal[1]));
		_clr_text(p_lin->text);
		copynaam(str_, p_lin->text + POS_NAAM, 20);
		p_lin->fl_promoLijn = YES;
		adj_lijn(art_ptr + 1);
	  }
	}
  }
}


void calc_promo(int art_ptr)
{
  int groep, promo, formule, k, l, dig;
  float promoaantal, promogratis, gratis, aantal, getal[4 + 1];

  groep = art_promo.groep;
  if ((promo = art_promo.promo) < 'A') {
	promo = grp_extra[groep].promo;
  }
  if (art_ptr < 0 || promo<'A' || promo>'T') goto skip;
  promo -= 'A';
  formule = promo_desc[promo].formule;
  for (l = 0; l < 4; l++) getal[1 + l] = promo_desc[promo].getal[l];
  aantal = p_vrk->lijn[art_ptr].aantal;

  if (formule == 3) {
	if (getal[3] && (aantal >= getal[3])) {
	  formule = 2;
	  getal[1] = getal[3];
	  getal[2] = getal[4];
	}
	else if (aantal >= getal[1]) {
	  formule = 1;
	  getal[1] = getal[2];
	}
  }

  if (formule == 1) { // korting%
	insert_line(art_ptr, 1);
	movmem(p_vrk->lijn[art_ptr].code, p_lin->code, sizeof(p_lin->code));
	p_lin->btw = p_vrk->lijn[art_ptr].btw;
	p_lin->bits = AUTO_LEEG;
	p_lin->aantal = 0.;
	p_lin->prijs = getal[1];
	p_lin->groep = GRP_PKORT;
	adj_lijn(art_ptr + 1);
  }

  if (formule == 2) { // 1+1 gratis
	promoaantal = getal[1]; promogratis = getal[2];
	if (promoaantal && (aantal > promoaantal || -aantal > promoaantal)) {
	  k = (int)(aantal / (promoaantal + promogratis));
	  gratis = k * promogratis;
	  if (aantal - k * (promoaantal + promogratis) > promoaantal) {
		gratis += aantal - k * (promoaantal + promogratis) - promoaantal;
	  }
	  if (gratis) {
		insert_line(art_ptr, 1);
		p_vrk->lijn[art_ptr].aantal -= gratis;
		movmem(p_vrk->lijn[art_ptr].text, p_lin->text, sizeof(struct s_lijn));
		p_lin->aantal = gratis;
		p_lin->bits |= AUTO_LEEG;
		p_lin->prijs = 0.;
		p_lin->totaal = 0.;
		if (p_lin->bits&STUKS) { movmem(txttxt[7], &p_lin->text[POS_AANTAL + 4], 2); dig = 3; }
		else dig = 5;
		conv_getal((double)p_lin->aantal, &p_lin->text[POS_AANTAL], dig, NO, 3);
		adj_lijn(art_ptr);
		adj_lijn(art_ptr + 1);
	  }
	}
  }
  if (formule == 4) { // 1 + 1 aan 50%
	promoaantal = getal[1]; promogratis = getal[2];
	if (promoaantal && (aantal > promoaantal || -aantal > promoaantal)) {
	  k = (int)(aantal / (promoaantal + promogratis));
	  gratis = k * promogratis;
	  if (aantal - k * (promoaantal + promogratis) > promoaantal) {
		gratis += aantal - k * (promoaantal + promogratis) - promoaantal;
	  }
	  if (gratis) {
		insert_line(art_ptr, 1);
		p_vrk->lijn[art_ptr].aantal -= gratis;
		movmem(p_vrk->lijn[art_ptr].text, p_lin->text, sizeof(struct s_lijn));
		p_lin->aantal = gratis;
		p_lin->bits |= AUTO_LEEG;
		p_lin->prijs = (float)(round_it((double)(p_lin->prijs*(100. - getal[3]) / 100.), def_round));
		p_lin->totaal = round_it((double)(p_lin->prijs*p_lin->aantal), def_round);
		if (p_lin->bits&STUKS) { movmem(txttxt[7], &p_lin->text[POS_AANTAL + 4], 2); dig = 3; }
		else dig = 5;
		conv_getal((double)p_lin->aantal, &p_lin->text[POS_AANTAL], dig, NO, 3);
		adj_lijn(art_ptr);
		adj_lijn(art_ptr + 1);
	  }
	}
  }
skip:;
}


// kasklt.cpp oud gedeelte

struct s_klant klant;
int klant_nr;

void txt_klt(char *datum)
{
  kasklt.get_klant();
  add_text(txttxt[43]);
  copynaam(klant.code,(p_lin-1)->text+10,10);
  copynaam(datum,(p_lin-1)->text+32,8);
  add_text("");
  txt_aklt(NO);
  add_text(txttxt[44]);
  copynaam(klant.telefoon,(p_lin-1)->text+7,18);
  copynaam(klant.btwnummer,(p_lin-1)->text+28,12);
}

void txt_aklt(char add_fl)
{
  int i;
  
  if (add_fl) {
    add_text(txttxt[43]);
    copynaam(klant.code,(p_lin-1)->text+10,10);
    for (i=21; i<40; i++) (p_lin-1)->text[i]=' ';
    copynaam(txttxt[44]+21,(p_lin-1)->text+21,19);
    copynaam(klant.btwnummer,(p_lin-1)->text+28,12);  
  }
  add_text(klant.naam);
  add_text(klant.straat);
  add_text(klant.postnr);
  copynaam(klant.gemeente,(p_lin-1)->text+sizeof(klant.postnr),40-sizeof(klant.postnr));
}

void gt_txtklt(char *s, int type)
{
  char *p;
  int len, i;

  p=""; len=0;
  switch (type) {
    case 1: p=klant.code; len=sizeof(klant.code); break;
    case 2: p=klant.naam; len=sizeof(klant.naam); break;
    case 3: p=klant.straat; len=sizeof(klant.straat); break;
    case 4: p=klant.postnr; len=sizeof(klant.postnr); break;
    case 5: p=klant.gemeente; len=sizeof(klant.gemeente); break;
    case 6: p=klant.telefoon; len=sizeof(klant.telefoon); break;
    case 7: p=klant.btwnummer; len=sizeof(klant.btwnummer); break;
  }
  if (len>0) {
    for (i=0; i<len; i++) {
      if (!*p) break;
      else *s++=*p++;
    }
  }
}

// KASFAC.CPP

extern struct s_lijn *p_lin;
extern struct s_verkopen *p_vrk;
extern struct s_klant klant;
extern int klant_nr;
extern char txttxt[200][150];

char *getml();
long _lseek();
 

/* --------------------------- Declaratie functies ---------------------- */

static void wr_crlf(void);
static void wr_kasfac(char *s);
static int  facref;

void op_kasfac(int line)
{
  disp_vid(0,line,  "_opening KASFAC.DAT ...",0);
  facref=_open("KASFAC.DAT",RDWRMODE,0);
  if (facref<0) facref=_creat("KASFAC.DAT",CREAMODE);
  if (facref<0) disp_exit("Impossible to _open KASFAC.DAT");
  _lseek(facref,0L,2);
}

void add_kasfac(char *type, char datum[], unsigned volgnr)
{
  char buf30[30];
  int i,j,k,groep, _groep;
  float goederen=0.,lgmee=0.,lgterug=0.,totaal=0.,betaald=0.,saldo=0.,bedrag;
  float prijs, aantal;
 
  wr_kasfac(type); wr_crlf();
  sprintf(buf,"H1|%1s|%1d\r\n",datum,volgnr); wr_kasfac(buf);
  sprintf(buf,"H2|%1s|%1s|%1s|%1s|%1s|%1s|%1s\r\n",
    klant.code,
    klant.naam,
    klant.straat,
    klant.postnr,
    klant.gemeente,
    klant.telefoon,
    klant.btwnummer); wr_kasfac(buf);
  p_lin = &p_vrk->lijn[0];
  for (i=0; i<p_vrk->used; i++) {
    groep=p_lin->groep;
    if (groep>=-9 && groep<1000) {
      if (p_lin->bits & AUTO_LEEG) {
        wr_kasfac("R2");
      }
      else wr_kasfac("R1");
			movmem(p_lin->code,buf30,ARTCODE_LEN); buf30[ARTCODE_LEN]=0;
      sprintf(buf,"|%1s|",buf30); wr_kasfac(buf);
      if (p_lin->bits & STUKS) {wr_kasfac(txttxt[7]); wr_kasfac(": ");}
      movmem(&p_lin->text[POS_NAAM],buf30,20); buf30[20]=0;
      for (j=19; j>=0; j--) if (buf30[j]>' ') {buf30[j+1]=0; break;}
      aantal=p_lin->aantal; prijs=p_lin->prijs; _groep=groep;
      if (groep<0) {
        aantal=1.; prijs=(float)p_lin->totaal;
				for (k=i-1; k>=0; k--) {
				  if (memcmp(p_vrk->lijn[k].code,p_lin->code,ARTCODE_LEN)==0) break;
				}				
        if (k>=0) _groep=p_vrk->lijn[k].groep;
        sprintf(buf,"%2.3f ",p_lin->prijs); Komma2Punt(buf); wr_kasfac(buf);
      }
      sprintf(buf,"%1s|%1d|%2.2f|%2.3f|%2.3f|%2.2f\r\n",
        buf30,_groep,p_lin->btw,aantal,prijs,p_lin->totaal);
        Komma2Punt(buf); wr_kasfac(buf);
    }
    else if ((groep>=1000 && groep<1030) || (groep>=1041 && groep<=1044)) {
      bedrag=(float)p_lin->totaal;
      switch (groep) {
        case GRP_LGMEE:   lgmee+=bedrag; break;
        case GRP_LGTERUG: lgterug+=bedrag; break;
        case GRP_GOEDEREN:goederen+=bedrag; break;
        case GRP_TOTAAL:  totaal+=bedrag; break;
        case GRP_TERUG:   betaald-=bedrag; break;
        case GRP_TBSALDO: saldo+=bedrag; break;
				case GRP_TGBON:   betaald-=bedrag; break; // is negatief
        case GRP_TEGOED:  totaal-=bedrag; saldo-=bedrag; break;
        case GRP_LEVERBON:totaal-=bedrag; betaald-=bedrag; break;
        case GRP_CDBON_BET:totaal-=bedrag; betaald-=bedrag; break;
        default: if(groep!=GRP_MEETOTAAL || TotaalOp5CentAfronden!='J') betaald+=bedrag; break;
      }
    }
    p_lin++;
  }
  sprintf(buf,"T1|%2.2f|%2.2f|%2.2f|%2.2f|%2.2f|%2.2f\r\n",goederen,lgmee,lgterug,
              totaal,betaald,saldo); Komma2Punt(buf); wr_kasfac(buf);
  _close(facref);
  facref=_open("KASFAC.DAT",RDWRMODE,0);
  if (facref<0) disp_exit("Couldn't re_open KASFAC.DAT");
  _lseek(facref,0L,2);
}

static void wr_kasfac(char *s)
{
  char *p;
  int len;
 
  len=0; p=s;
  while (*p++) len++;
  _write(facref,s,len);
}

static void wr_crlf(void)
{
  _write(facref,"\r\n",2);
}

// KASEINDE.CPP

extern struct s_lijn *p_lin;
extern struct s_verkopen *verkopen, *p_vrk;
                        
extern struct layout key_layout[], bet_layout[], bet_krediet;

extern unsigned reg_ds, mulfunok;
 
extern char txttxt[200][150], *txtbet[];
 
extern int key_count, art_count, no_prtkas, fl_freedelity ,fl_KasCtrl;
extern char prt_fil, prt_trans;
extern char fakt_head[20][51], fakt_vtekst[3][81];
extern int fakt_dist, teg_allow, fakt_sp1, epson_fl;
extern char ss_enable;
extern int prt_cut_count, groep_leeg;
extern short int prx_sys[VRK_COUNT], vrk_lade[VRK_COUNT], leeg_sys[VRK_COUNT];
extern int prx_count, bc_allowed, bc_option, chk_kassier;
extern int klant_nr, fakt_allow, fl_open_lade, sprook;
extern int fref_sys;
extern char tijd[];
extern char def_valuta[],TotaalOp5CentAfronden, PromoNotOnHorecaPrice;
extern int def_digits, EigenPrijsOpStuksAllowed;
extern float def_round, krtperc;
extern double BedragTotaalafronding;
extern unsigned jddatum, faktnr, herctab[], tick_type;

static char gr_line[200]; // was vroeger 81 maar is te klein !
 
extern char einde_fl, val_inuse, val_used, val_ix, disp_fl;
extern int val_einde, val_wlast, val_llast, larg_next, vrk_ix, lade_used[];
extern int larg_fl, plu_ix, ticketnr;
 
double round_it();
 

/* --------------------------- Declaratie functies ---------------------- */
#include "kassa.h"
// geen static ...

void add_einde(int groep, double bedrag, int subgroep)
{
  char *p;
  unsigned len;
  int i, to_use;
 
  to_use=p_vrk->used;
  p_lin=&p_vrk->lijn[to_use];
  if (groep==GRP_LGTERUG || groep==GRP_LEVERBON || groep==GRP_TGBON || groep==GRP_CDBON_BET) {
    bedrag=-bedrag;
    for (i=to_use-1; i>=0; i--) {
      if (p_vrk->lijn[i].groep == GRP_TOTAAL) break;
    }
    if (i>=0) {
      larg_next=i;
      p_lin=&p_vrk->lijn[i]; to_use=i;
      p_lin->totaal+=bedrag; adj_text(to_use);
      len = (p_vrk->used - to_use) * sizeof(struct s_lijn);
      if (len>0) movmem((char *)p_lin, (char *)(p_lin+1), len);
      p=(char *)p_lin; i=sizeof(struct s_lijn);
      while (i-->0) *p++=0;
    }
  }
  p_lin->aantal=(float)subgroep;
  if(groep==GRP_AFRONDING) p_lin->prijs=(float)p_vrk->totaal[0];  else p_lin->prijs=0.;  // nodig om als totaal af te drukken later, ipv afrondingsbedrag
  p_lin->btw=(float)(val_einde+1);
  p_lin->groep=groep;
  p_lin->totaal=bedrag;
  if (p_lin->groep==GRP_CONVERT) {
    if (val_inuse) {
      movmem(valuta[val_ix].naam,p_lin->code,4);
      val_einde=val_ix;
    }
    else {
      movmem(def_valuta,p_lin->code,4);
      val_einde=-1;
    }
    p_lin->prijs=(float)p_vrk->totaal[0];
    p_lin->btw=(float)val_einde+1;
    p_lin->aantal=valuta[val_ix].coeff;
    for (i=0; i<2; i++) {
      if (val_inuse) {
        p_vrk->totaal[i]/=valuta[val_ix].coeff;
        p_vrk->totaal[i]=round_it(p_vrk->totaal[i],valuta2[val_ix].round);
      }
      else {
        p_vrk->totaal[i]*=valuta[val_ix].coeff;
        p_vrk->totaal[i]=round_it(p_vrk->totaal[i],def_round);
      }
    }
    p_lin->totaal=p_vrk->totaal[0];
  }
  adj_lijn(to_use);
  p_vrk->used++;
}
 
void close_bon(char save_fl, bool DoOpenGeldlade)
{
  char datum[9],buf_[20];
  int i, j,_faktnr,PrtNrSaved,full_count,JmcError_=NO;
	short jj, mm, dd;
	char nm_pdffile[20];
  CString cstr;
  CFile fil;

  kbtest(); // om update van display te doen via JamaCon
	if (sprook==2) {
    disp_clr(0,0,80,25);
    disp_exit("Hardware not found !");
  }

#if CONTROL2PDF
	char *b;
	b = new char[CTRLPDFSIZE];
	unsigned short int *w = (unsigned short int *)b;

	w[0] = 0x09B0;
	w[1] = 0x0DB4;
	w[2] = 0x0000;
	w[3] = 0x0056;
	w[4] = 0x0076;
	w[5] = 0x0076;
	w[6] = 0x0000;
	w[7] = 0x0304; /// was 0x0304;
	w[8] = 0x0B06;
	w[9] = 0x0450;
	w[10] = 0x0100;
	w[11] = 0x0000;
	JMU_s = (char *)&w[12];
	JMU_s = CopyString(JMU_s, "\xE0\xD4[landscape;]|\xF0");
	TotSpoolBytes = 50;
//	PrintControl2PDF = NO;
#endif

  p_lin=&p_vrk->lijn[p_vrk->used];
  if (p_vrk->fakt_type) {
    if (p_vrk->JmcFactuurFlag && (KassaTestConfigFlag || (JMD=::FindWindow("THE_JMD",NULL))!=NULL)) { //_T("THE_JMD")
      CMarkup Ticket;

			if (p_vrk->JmcDocType==2) {   // 1=factuur, 2=bon. Voor de volgende fase verwacht ik van u een status 3 (factuur) of 4 (bon), afhankelijk van DocType
				Ticket.AddElem("Status",4); // leveringsbon maken ...
			}
			else Ticket.AddElem("Status",3); // zoniet factuur maken ...
      Ticket.AddElem("Ticket");
      Ticket.IntoElem();
      Ticket.AddElem("Klant",klant_nr);
      Ticket.OutOfElem();

      Ticket.AddElem("Detail");
      Ticket.IntoElem();
      for (i=0; i<p_vrk->used; i++) {
        struct s_lijn* pl=&p_vrk->lijn[i];
          /*
          char text[41];
          unsigned char bits;
          char code[ARTCODE_LEN];
          float aantal;
          short groep;
          float btw;
          float prijs;
          double totaal;*/
        Ticket.AddElem("L");
        Ticket.IntoElem();
        if (pl->groep==GRP_TEXT) Ticket.AddElem("X",pl->text);
        Ticket.AddElem("B",pl->bits);
        Ticket.AddElem("C",pl->code);
        cstr.Format("%.2f",pl->aantal);
        Ticket.AddElem("A",cstr);
        Ticket.AddElem("G",pl->groep);
        cstr.Format("%.2f",pl->btw);
        Ticket.AddElem("W",cstr);
        cstr.Format("%.3f",pl->prijs);
        Ticket.AddElem("P",cstr);
        cstr.Format("%.2f",pl->totaal);
        Ticket.AddElem("T",cstr);
        Ticket.OutOfElem();
      }
      Ticket.OutOfElem();

      Ticket.Save(JmcCmdFilepath);
      UpdateOnJMC();

			CMarkup Xml;
      for (i=0; i<750; i++) {
        Xml.Load(KasCmdFilepath);
		if (Xml.GetDoc().GetLength() > 0) {
		  Xml.ResetMainPos();
		  if(Xml.FindElem("/Ticket") == true){
		    Xml.ResetMainPos();
		    break;
		  }
		}
        Sleep(200);
      }
      if(i>=750 || Xml.FindElem("/Ticket")==false){
				JmcError_=YES;
				p_vrk->JmcFactuurFlag = false;
				add_text(" ");
				add_text("*********** Communicatiefout ************");
				add_text("Controleer de factuur en maak deze");
				add_text("eventueel manueel aan.");
				movmem("Klantnr. : ",buf_,11); int2str(p_vrk->klant_nr,&buf_[11],5); buf_[16]=0;add_text(buf_);
			  add_text("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
				p_vrk->lijn[p_vrk->used].groep =GRP_FAKT;
				p_vrk->lijn[p_vrk->used].btw   =(float)p_vrk->fakt_type;
				p_vrk->lijn[p_vrk->used].aantal=(float)p_vrk->klant_nr;
				p_vrk->lijn[p_vrk->used].prijs =(float)0;
				p_vrk->lijn[p_vrk->used].totaal=jddatum;
				if (p_vrk->JmcDocType==2) p_vrk->lijn[p_vrk->used].code[0]='L'; else p_vrk->lijn[p_vrk->used].code[0]='F';
				adj_text(p_vrk->used++); p_lin++;
				klant_nr=p_vrk->klant_nr;
				kasklt.get_klant();
				txt_aklt(YES);
			}
			else{
				Xml.ResetMainPos();
				i=atol(Xml.FindGetData("RetValue")); // op hoogste niveau
				if(i==0){
				  JmcError_=YES;
					p_vrk->JmcFactuurFlag = false;
					add_text(" ");
					add_text("**** Probleem bij maken bon/factuur ****");
					add_text("Controleer de factuur en maak deze");
					add_text("eventueel manueel aan.");
					movmem("Klantnr. : ",buf_,11); int2str(p_vrk->klant_nr,&buf_[11],5); buf_[16]=0;add_text(buf_);
					add_text("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
					p_vrk->lijn[p_vrk->used].groep =GRP_FAKT;
					p_vrk->lijn[p_vrk->used].btw   =(float)p_vrk->fakt_type;
					p_vrk->lijn[p_vrk->used].aantal=(float)p_vrk->klant_nr;
					p_vrk->lijn[p_vrk->used].prijs =(float)0;
					p_vrk->lijn[p_vrk->used].totaal=jddatum;
					if (p_vrk->JmcDocType==2) p_vrk->lijn[p_vrk->used].code[0]='L'; else p_vrk->lijn[p_vrk->used].code[0]='F';
					adj_text(p_vrk->used++); p_lin++;
					klant_nr=p_vrk->klant_nr;
					kasklt.get_klant();
					txt_aklt(YES);
				}
				else{
					Xml.ResetMainPos();Xml.FindElem("Ticket");Xml.IntoElem();
					_faktnr=atol(Xml.FindGetData("FaktNr"));
					p_vrk->lijn[p_vrk->used].groep =GRP_FAKT;
					p_vrk->lijn[p_vrk->used].btw   =(float)p_vrk->fakt_type;
					p_vrk->lijn[p_vrk->used].aantal=(float)p_vrk->klant_nr;
					p_vrk->lijn[p_vrk->used].prijs =(float)_faktnr;
					p_vrk->lijn[p_vrk->used].totaal=jddatum;
					if (p_vrk->JmcDocType==2) p_vrk->lijn[p_vrk->used].code[0]='L'; else p_vrk->lijn[p_vrk->used].code[0]='F';
					adj_text(p_vrk->used++); p_lin++;
					while (Xml.FindElem("KltInfo")) {
						CString cstr=Xml.GetData();
						add_text((char *)(LPCTSTR)cstr);
					}
				}
			}
    }

    else {
      _faktnr=faktnr+1;
      if (_faktnr>=30000) _faktnr=1;
      p_vrk->lijn[p_vrk->used].groep =GRP_FAKT;
      p_vrk->lijn[p_vrk->used].btw   =(float)p_vrk->fakt_type;
      p_vrk->lijn[p_vrk->used].aantal=(float)p_vrk->klant_nr;
      p_vrk->lijn[p_vrk->used].prijs =(float)_faktnr;
      p_vrk->lijn[p_vrk->used].totaal=jddatum;
      adj_text(p_vrk->used++); p_lin++;
      klant_nr=p_vrk->klant_nr;
      kasklt.get_klant();
      txt_aklt(YES);
    }
  }
  if (p_vrk->TERPLAATSE_flag) {
    p_vrk->lijn[p_vrk->used].groep=GRP_TERPLAATSE;
    adj_text(p_vrk->used++); p_lin++; 
    for (j=0; j<p_vrk->used; j++) {
      if (p_vrk->lijn[j].groep>=0 && p_vrk->lijn[j].groep<=1000 && p_vrk->lijn[j].btw>0) {
			  p_vrk->lijn[j].btw=BTWBONPercentage;
				if (p_vrk->lijn[j].groep==DrankGroep) p_vrk->lijn[j].btw=BTWBONDrankPercentage;
			}
    }
  }
  for (j=0; j<5; j++) {
    if (compare("EUR",valuta[j].naam,3)==0) {
      for (jj=0; jj<p_vrk->used; jj++) {
        if (p_vrk->lijn[jj].groep==GRP_TOTAAL) break;
      }
      if (jj==p_vrk->used) break;
      p_vrk->lijn[p_vrk->used].btw=(float)(j+1);
      p_vrk->lijn[p_vrk->used].groep=GRP_EURO;
      p_vrk->lijn[p_vrk->used].totaal=p_vrk->lijn[jj].totaal/valuta[j].coeff;
      adj_text(p_vrk->used++); p_lin++;
      break;
    } 
  }
#if CONTROL2PDF
  if (PrintControl2PDF==NO && DoOpenGeldlade) {
#else
  if(DoOpenGeldlade){
#endif
    if (!val_used) o_lade(1<<(vrk_lade[vrk_ix]-1));
    else val_lades();
	}
  if (p_vrk->BestelKrtNr>=1) {
    kaskrt.AdjustTicketAndSaveToXml();
    if (p_vrk->lijn[p_vrk->used-1].groep!=GRP_TOTAAL) {
      p_vrk->lijn[p_vrk->used].groep=GRP_TIJD;
      adj_text(p_vrk->used++);
    }
	if (NoPrtCut == YES) prt_hoofd(YES);
    prt_body(0);
	if (NoPrtCut == NO) prt_hoofd(YES); 
	else { prt_nl(" ");	prt_nl(" "); }
    kaskrt.MakeVoorschotTicket();
  }
  else { 
    full_count=0;
    if (p_vrk->krtflag) full_count=kaskrt.updkltkrt();
    if (full_count){ 
	  if (NoPrtCut == YES) prt_hoofd(YES);
	  kaskrt.prtkrtfull(full_count); 
	  if (NoPrtCut == NO) prt_hoofd(YES); 
	  else { prt_nl(" ");	prt_nl(" "); }
	}
    if (save_fl) {
  		p_vrk->lijn[p_vrk->used].groep=GRP_TIJD;
      adj_text(p_vrk->used++);
		}
  }
  if (p_vrk->used>0 && ex_ticket!=-1) {
	if (NoPrtCut == YES) prt_hoofd(YES);
    prt_body(0);
	if (NoPrtCut == NO) prt_hoofd(YES); 
	else { prt_nl(" ");	prt_nl(" "); }
  }
  if (p_vrk->used>0 && JmcError_) {
	if (NoPrtCut == YES) prt_hoofd(YES);
    prt_body(0);
	if (NoPrtCut == NO) prt_hoofd(YES); 
	else { prt_nl(" ");	prt_nl(" "); }
  } 
  if (tick_type & 0x04) {
    prt_close();
    PrtNrSaved=PrtNr;
    PrtNr=2; // controle ticket ...
    //prt_init();  niet meer nodig in versie WinTouch
    prt_body(YES);
    prt_close();
    PrtNr=PrtNrSaved;
    //prt_init();	 niet meer nodig in versie WinTouch
  }
  for (j=2;j<=(int)ex_ticket;j++) {
    if (p_vrk->used==0) continue;
	if (NoPrtCut == YES) prt_hoofd(YES);
    prt_body(0);
	if (NoPrtCut == NO) prt_hoofd(YES); 
	else { prt_nl(" ");	prt_nl(" "); }
  }

  if (!save_fl) {
    ticketnr=0;
  }
  else {
    ticketnr=log_getticket();
    p_vrk->lijn[0].bits|=NEW_TICKET;
    log_add(YES);
  }
  if (p_vrk->fakt_type) {
    jddate(jddatum,&jj,&mm,&dd);
    int2str(jj,&datum[6], 2);
    int2str(mm,&datum[3],-2); datum[5]='/';
    int2str(dd,&datum[0],-2); datum[2]='/';
    datum[8]=0;

		if (!p_vrk->JmcFactuurFlag || (ConfigFlags&2)) {
		  if (NoPrtCut == NO) prt_body(0);  // enkel in oude systeem 2x drukken, behalve bij printer zonder cut, want dat is moeilijk te scheuren
			switch (p_vrk->fakt_type) {
				case 1:
					prt_hoofd(NO);
					faktnr++;
					if (faktnr>=30000) faktnr=1;
					add_kasfac("K1",datum,faktnr); // opletten, moet voor prt_kl_faktuur staan, die doet CLR_TICKET !!!
					prt_kl_faktuur(datum);
					log_add(NO); kassys.upd_sys();
					break;
				case 2:
					faktnr++;
					if (faktnr>=30000) faktnr=1;
					prt_gr_faktuur(datum);
					add_kasfac("F1",datum,faktnr);
					kassys.upd_sys();
					break;
				case 3:
					add_kasfac("L1",datum,ticketnr);
					break;
			}
			if (NoPrtCut == NO) prt_hoofd(YES); 
			else { prt_nl(" ");	prt_nl(" "); }
		}

  }
  _clr_ticket(); IsOk=true;

#if CONTROL2PDF
  if (PrintControl2PDF) {
	int len = (JMU_s - b);

	fil.Open("Ticket.spl", CFile::modeCreate | CFile::modeWrite);
	fil.Write(b, len);
	fil.Close();

	//		if(pDocControle==NULL){
	pDocControle = new CJmuDoc();

	pDocControle->ReadDocument("Ticket.spl", 0, true);
	for (int j = 0; j < 4; j++) {
	  pDocControle->BedrukkingFlag[j] = false;
	}
	memset(nm_pdffile, 0, sizeof nm_pdffile);
	jddate(lst_dag, &jj, &mm, &dd);
	sprintf_s(nm_pdffile, 20, "Ticket %05d.pdf", ticketnr);
	pDocControle->Convert2Pdf("Ticket.spl", nm_pdffile); // "Controle.pdf");
	CFile::Remove("Ticket.spl");
	//if (pDocControle) {
	//	delete pDocControle;
	//	pDocControle=NULL;
	//};
	::ShellExecute(NULL,"OPEN",nm_pdffile,NULL,NULL,SW_SHOW);
//	KASSA LOOPT VAST (CONSELECT) ALS IK DIT DOE : 	::ShellExecute(NULL,"OPEN","Controle.pdf",NULL,NULL,SW_SHOW);
// Jaak 23/03/22  	PrintControl2PDF = NO; // uit veiligheid
  }
#endif

#if CONTROL2PDF
  delete[] b;
#endif

  prt_close();
  disp_fl=YES;
}

void val_lades(void)
{
  int byte, i;
 
  byte=0;
  for (i=1; i<=MAX_LADE; i++) {
    if (lade_used[i]) {
      byte|=(1<<(i-1));
    }
  }
  o_lade(byte);
}
 
//char * CopyString(char *s, char * p)
//{
//	while (*p) *s++=*p++;
//	return s;
//}

void JMU_prt_char(char val)
{
  *JMU_s++=val;
}

void JMU_prt_lin(char *sc)
{
  unsigned char *s;
	s=(unsigned char *)sc;
  while (*s) {
    if (*s==0xFF) {
      JMU_prt_char(0); s++;
    }
    else {
      if (*s<128) JMU_prt_char(*s++);  // || epson_flag   weggedaan voor conversie naar 
      else JMU_prt_char(PrtDrv[Prt[PrtNr].type].spec[*s++-128]);
    }
  }
}

void JMU_prt_nl(char *sc)
{
  unsigned char *s;
	s=(unsigned char *)sc;
  //if (PrtNr==1) JMU_prt_char(' '); // PCL factuur (1 naar rechts !)
  while (*s) {
    if (*s==0xFF) {
      JMU_prt_char(0); s++;
    }
    else {
      if (*s<128) JMU_prt_char(*s++);
      else JMU_prt_char(PrtDrv[Prt[PrtNr].type].spec[*s++-128]);
    }
  }
  JMU_prt_char(0x0D);
  JMU_prt_char(0x0A);
  /*
  prt_cod(8);  zou niet meer nodig zijn.
                        Anders moet het verhuisd worden naar 9 of zo,
                        want op 8 zit er bij de IR-300 een Emphased code
                         in de kassys.dat die echter niet gebruikt ! */
}

void JMU_gr_header(char datum[9], char first_fl)
{
  char _tijd[50];
  int i, j,k, a_first, h_stop;

  if(first_fl) FactPageNr=1;
	movmem(p_vrk->lijn[p_vrk->used-1].text,_tijd,sizeof(p_lin->text));
  if (fakt_dist==0) {
    a_first=7; h_stop=20;
  }
  else {
    a_first=fakt_dist-5;
    if (a_first<1) a_first=1;
    h_stop=fakt_dist+8;
  }
  for (i=1; i<=30; i++) {
    if (i==h_stop+fakt_sp1) break;
    cl_gr_line();
    if (i>=a_first) {
      j=i-a_first;

      if (j>=0 && j<=1) gt_txtklt(gr_line+47,j+2);
      else if (j==2) {
        gt_txtklt(gr_line+47,4);
        gt_txtklt(gr_line+55,5);
      }
      else if (j==6) {
				if(p_vrk->CreditNotaFlag){
					if (first_fl) copynaam(txttxt[103],gr_line,30);
					else {
						copynaam(txttxt[104],gr_line,30);
						for(k=0;k<29;k++) if(gr_line[k]==')') break;
						int2str(FactPageNr,&gr_line[k-2],2);gr_line[k]=')';
					}
				}
				else{
          if (first_fl) copynaam(txttxt[56],gr_line,30);
					else {
						copynaam(txttxt[57],gr_line,30);
						for(k=0;k<29;k++) if(gr_line[k]==')') break;
						int2str(FactPageNr,&gr_line[k-2],2);gr_line[k]=')';
					}
				}
      }
      else if (j==9) {
        copynaam(txttxt[42]+18,gr_line,40);
        copynaam(_tijd+8,gr_line+7,4);
        gr_line[11]='-';
        copynaam(datum,gr_line+12,8);
				copynaam("BE-",gr_line+22,3);
        gt_txtklt(gr_line+22+3,7);
        gt_txtklt(gr_line+44,1);
        int2str(faktnr,gr_line+56,5);
        copynaam(datum,gr_line+69,8);
      }
    }
    JMU_prt_nl(gr_line);
  }
	FactPageNr++;
}

int JMU_lincheck(int lincnt, char datum[9])
{
  if (lincnt && lincnt%(26-fakt_sp1) == 0) {
    lincnt=0;
    JMU_prt_lin("\x0C");
    JMU_gr_header(datum,NO);
  }
  return lincnt;
}

void JMU_gr_footer(char datum[9],int lincnt,bool betaald)
{
  int j, i, ix, tb[6], btw_ix;
  float diff;
  int off;
  float kleinste;
  double goederen, tot_btw, leeggoed, subtotaal, leegterug, totaal;
 
  while (lincnt==0 || lincnt%(26-fakt_sp1)!=0) {JMU_prt_nl(""); lincnt++;}
  for (j=0; j<1; j++) JMU_prt_nl("");
  leegterug=0.;
  for (j=0; j<p_vrk->used; j++) {
    if (p_vrk->lijn[j].groep == groep_leeg && p_vrk->lijn[j].aantal<0) {
      leegterug -= p_vrk->lijn[j].totaal;
    }
  }
  mk_btw(); goederen=0.; tot_btw=goederen; totaal=goederen;/* alles op 0 */
  leeggoed=goederen;
  diff=4.5; off=4;
  for (ix=0; ix<4; ix++) { /* was 6 !!! */
    kleinste=101.;
    for (i=0; i<CUMBTW_COUNT; i++) {
      if (btw_cumul[i].btw_perc==-1.) {
        leeggoed=btw_cumul[i].totaal;
        btw_cumul[i].btw_perc=1000.;
      }
      if (btw_cumul[i].totaal && btw_cumul[i].btw_perc<kleinste) {
        kleinste=btw_cumul[i].btw_perc;
        btw_ix=i;
      }
    }
    if (kleinste==101.) break;
    tb[ix]=btw_ix;
    btw_cumul[btw_ix].btw_perc+=200;
    goederen+=btw_cumul[btw_ix].basis;
    tot_btw+=btw_cumul[btw_ix].btw;
    totaal+=btw_cumul[btw_ix].totaal;
  }
  cl_gr_line();
  for (i=0; i<ix; i++) {
    gr_line[4+off+iabs((9+diff)*i)]=(char)('A'+(btw_cumul[tb[i]].btw_perc-200.)/3.);
    gr_line[5+off+iabs((9+diff)*i)]='=';
    conv_getal((double)btw_cumul[tb[i]].btw_perc-200.,gr_line+6+off+iabs((9+diff)*i),4,1,1);
  }
  leeggoed+=leegterug; subtotaal=leeggoed+goederen+tot_btw;
  totaal=subtotaal-leegterug;
  conv_getal(leeggoed,gr_line+68,10,3,def_digits);
  JMU_prt_nl(gr_line);
  JMU_prt_nl("");
  cl_gr_line();
  for (i=0; i<ix; i++) {
    conv_getal((double)btw_cumul[tb[i]].basis,gr_line+4+off+iabs((9+diff)*i),8,1,def_digits);
  }
  conv_getal(goederen,gr_line+68,10,3,def_digits);
  JMU_prt_nl(gr_line);
  JMU_prt_nl("");
  cl_gr_line();
  for (i=0; i<ix; i++) {
    conv_getal((double)btw_cumul[tb[i]].btw,gr_line+4+off+iabs((9+diff)*i),8,1,def_digits);
  }
  conv_getal(tot_btw,gr_line+68,10,3,def_digits);
  JMU_prt_nl(gr_line);
  JMU_prt_nl("");
  cl_gr_line();
  conv_getal(subtotaal,gr_line+68,10,3,def_digits);
  JMU_prt_nl(gr_line);
  JMU_prt_nl("");
  cl_gr_line();
  conv_getal(leegterug,gr_line+68,10,3,def_digits);
  JMU_prt_nl(gr_line);
  JMU_prt_nl(""); 
  cl_gr_line();
  conv_getal(totaal,gr_line+68,10,3,def_digits);
  JMU_prt_nl(gr_line);
  JMU_prt_nl(""); 
	if (betaald) {
		cl_gr_line();
		sprintf(gr_line+68,"%10s",txttxt[94]);
		JMU_prt_nl(gr_line);
	}
	else {
		cl_gr_line();
    copynaam(datum,gr_line+68,8);
		JMU_prt_nl(gr_line);
	}
}

void JMU_prt_gr_faktuur(char datum[9])
{
	CString SplFileName; // ="factuur.spl";

	char *b;
	b = new char[100000];
	unsigned short int *w = (unsigned short int *)b;

	w[0] = 0x09B0;
	w[1] = 0x0DB4;
	w[2] = 0x0000;
	w[3] = 0x0056;
	w[4] = 0x0076;
	w[5] = 0x0076;
	w[6] = 0x0000;
	w[7] = 0x0304; /// was 0x0304;
	w[8] = 0x0B06;
	w[9] = 0x0450;
	w[10]= 0x0100;
	w[11]= 0x0000;
	JMU_s = (char *) &w[12];
	JMU_s = CopyString(JMU_s,"\xE0\xD4[landscape;]|\xF0");

// afprinten factuur

  int _ix, j,lincnt;
  int diff, count;
  double prijs, totaal;
 
  count=pcl3flag;

  JMU_gr_header(datum,YES);

  lincnt=0;
  for (j=0; j<p_vrk->used; j++) {
    lincnt=JMU_lincheck(lincnt,datum);
    cl_gr_line();
    p_lin=(struct s_lijn *) p_vrk->lijn[j].text;
    if (p_lin->groep <= -1 && p_lin->groep >= -9) {
      /*
      p_lin->groep = p_vrk->lijn[j-1].groep;
      */
      p_lin->code[0]=0;
      if (p_lin->aantal==0.) {
        p_lin->aantal=p_lin->prijs;
        p_lin->prijs=(float)p_lin->totaal;
      }
    }
		if (p_lin->groep >= 0 && p_lin->groep < 1000 || p_lin->groep==GRP_PKORT || p_lin->groep==GRP_FKORT) {
      copynaam(p_lin->code,gr_line,sizeof(p_lin->code));
      _ix=kasplu.plu_req(p_lin->code,ARTCODE_LEN);
      if (_ix>=0) copynaam(kasplu.art_info.naam,gr_line+8,20);
      else copynaam(p_lin->text+POS_NAAM,gr_line+8,20);
      diff=7;
			if(p_lin->groep!=GRP_PKORT && p_lin->groep!=GRP_FKORT){ // indien kortingen, dan enkel totaal drukken
        conv_getal((double)p_lin->aantal,gr_line+37-diff,6,1,2); 
        prijs=p_lin->prijs/(1.+p_lin->btw/100.);
        conv_getal(prijs,gr_line+44-diff,9,1,def_digits);
			}
      totaal=p_lin->totaal/(1.+p_lin->btw/100.);
      diff=3;
      conv_getal(totaal,gr_line+61-diff,9,1,def_digits);
      /*
      conv_getal((double)p_lin->btw,gr_line+71,4,2);       zero suppress
      */
      diff=3;
      gr_line[72-diff]=(char)('A'+(p_lin->btw)/3.);
      p_lin++;
      diff=0;
      if ((p_lin->bits&AUTO_LEEG) && p_lin->groep==groep_leeg) {
        conv_getal((double)p_lin->totaal,gr_line+73-diff,7,0,def_digits); 
        j++;
      }
      JMU_prt_nl(gr_line); lincnt++;
    }
  }
  if (fakt_vtekst[0][0] || fakt_vtekst[1][0] || fakt_vtekst[2][0]) {
    lincnt=JMU_lincheck(lincnt,datum);
    JMU_prt_nl(""); lincnt++;
    for (j=0; j<3; j++) {
      if (fakt_vtekst[j][0]) {
        lincnt=JMU_lincheck(lincnt,datum);
        JMU_prt_nl(fakt_vtekst[j]); lincnt++;
      }
    }
  }
	bool betaald=YES;
	for (j=0; j<p_vrk->used; j++) if (p_vrk->lijn[j].groep==GRP_TBSALDO) {betaald=NO; break;}
  JMU_gr_footer(datum,lincnt,betaald);
  JMU_prt_lin("\x0C");

	int len = (JMU_s-b);
	CFile fil;
	fil.Open("factuur.spl",CFile::modeCreate|CFile::modeWrite);
	fil.Write(b,len);
	fil.Close();


	if (pDoc==NULL) pDoc=new CJmuDoc();

	pDoc->ReadDocument("factuur.spl",0,true);
	while (count-->0) pDoc->PrintDocument("factuur.spl","");
	CString PdfName;
	char *sKassa = getenv("jama-kassa");
	char *kassanr="0";
	if (sKassa && sKassa[5]=='-') kassanr=&sKassa[7];
	PdfName.Format("F%2s%1s%04d.pdf",&datum[6],kassanr,faktnr);
	pDoc->Convert2Pdf("factuur.spl",PdfName);

	delete [] b;
}

void prt_gr_faktuur(char datum[9])
{
	if (GetFileAttributes("KEYFACT.PNG")!=INVALID_FILE_ATTRIBUTES) {
		JMU_prt_gr_faktuur(datum);
		return;
	}

  int _ix, j,lincnt;
  int diff, count;
  double prijs, totaal;
 
  prt_close();
  int PrtNrSaved=PrtNr; PrtNr=1;
  prt_init(); 

  count=pcl3flag;
reprint:;
  gr_header(datum,YES);
  lincnt=0;
  for (j=0; j<p_vrk->used; j++) {
    lincnt=lincheck(lincnt,datum);
    cl_gr_line();
    p_lin=(struct s_lijn *) p_vrk->lijn[j].text;
    if (p_lin->groep <= -1 && p_lin->groep >= -9) {
      /*
      p_lin->groep = p_vrk->lijn[j-1].groep;
      */
      p_lin->code[0]=0;
      if (p_lin->aantal==0.) {
        p_lin->aantal=p_lin->prijs;
        p_lin->prijs=(float)p_lin->totaal;
      }
    }
    if (p_lin->groep >= 0 && p_lin->groep < 1000) {
      copynaam(p_lin->code,gr_line,sizeof(p_lin->code));
      _ix=kasplu.plu_req(p_lin->code,ARTCODE_LEN);
      if (_ix>=0) copynaam(kasplu.art_info.naam,gr_line+8,20);
      else copynaam(p_lin->text+POS_NAAM,gr_line+8,20);
      diff=7;
      conv_getal((double)p_lin->aantal,gr_line+37-diff,6,1,2); 
      prijs=p_lin->prijs/(1.+p_lin->btw/100.);
      conv_getal(prijs,gr_line+44-diff,9,1,def_digits);
      totaal=p_lin->totaal/(1.+p_lin->btw/100.);
      diff=3;
      conv_getal(totaal,gr_line+62-diff,9,1,def_digits);
      /*
      conv_getal((double)p_lin->btw,gr_line+71,4,2);       zero suppress
      */
      diff=3;
      gr_line[73-diff]=(char)('A'+(p_lin->btw)/3.);
      p_lin++;
      diff=0;
      if ((p_lin->bits&AUTO_LEEG) && p_lin->groep==groep_leeg) {
        conv_getal((double)p_lin->totaal,gr_line+73-diff,7,0,def_digits); 
        j++;
      }
      prt_nl(gr_line); lincnt++;
    }
  }
  if (fakt_vtekst[0][0] || fakt_vtekst[1][0] || fakt_vtekst[2][0]) {
    lincnt=lincheck(lincnt,datum);
    prt_nl(""); lincnt++;
    for (j=0; j<3; j++) {
      if (fakt_vtekst[j][0]) {
        lincnt=lincheck(lincnt,datum);
        prt_nl(fakt_vtekst[j]); lincnt++;
      }
    }
  }
	bool betaald=YES;
	for (j=0; j<p_vrk->used; j++) if (p_vrk->lijn[j].groep==GRP_TBSALDO) {betaald=NO; break;}
  gr_footer(datum,lincnt,betaald);
  prt_lin("\x0C");
  prt_close();
  while (count-->1) goto reprint;
  PrtNr=PrtNrSaved;
  prt_init();
}

int lincheck(int lincnt, char datum[9])
{
  if (lincnt && lincnt%(26-fakt_sp1) == 0) {
    lincnt=0;
    prt_lin("\x0C");
    gr_header(datum,NO);
  }
  return lincnt;
}

void gr_header(char datum[9], char first_fl)
{
  char _tijd[50], buf[1000];
  int i, j, k, a_first, h_stop, len, ref;
  DWORD iBytesWritten;

	if(first_fl) FactPageNr=1;
	if (pcl3flag) {
    prt_lin("\x1B\x45\x1B\x39\x1B&l6D\x1B&l0L\x1B&s1C\x1B(10U\x0F\x1B&l0E\x1B(s0P\x1B(s10H\x1B&k11.2H");  // 11.6 ipv 12 (smaller dan 10 cpi) !
    prt_nl("");
    prt_nl("");
  }
  movmem(p_vrk->lijn[p_vrk->used-1].text,_tijd,sizeof(p_lin->text));
  if (fakt_dist==0) {
    a_first=7; h_stop=20;
  }
  else {
    a_first=fakt_dist-5;
    if (a_first<1) a_first=1;
    h_stop=fakt_dist+8;
  }
  for (i=1; i<=30; i++) {
    if (i==h_stop+fakt_sp1) break;
    cl_gr_line();
    if (i<=20) copynaam(fakt_head[i-1],gr_line,50);
    if (i>=a_first) {
      j=i-a_first;
      if (j==5 && pcl3flag) {
        ref=dopen("KEYFACT.JAM",RDWRMODE);
        if (ref>=0) {
          FOREVER {
            len=dread(ref,buf,sizeof(buf));
            if (len==0) break;
            WriteFile(PrtRef,&buf,len,&iBytesWritten,NULL);   // gaan transparant naar buiten ! Moet ook zo !!!
          }
          dclose(ref);  
        }
//        prt_lin("\x1B*r3U\x1B*v1S"); //-> om tekst in rode kleur te drukken (voor test op OKI marc)
      }

      if (j>=0 && j<=1) gt_txtklt(gr_line+47,j+2);
      else if (j==2) {
        gt_txtklt(gr_line+47,4);
        gt_txtklt(gr_line+55,5);
      }
      else if (j==6) {
				if(p_vrk->CreditNotaFlag){
					if (first_fl) copynaam(txttxt[103],gr_line,30);
					else {
						copynaam(txttxt[104],gr_line,30);
						for(k=0;k<29;k++) if(gr_line[k]==')') break;
						int2str(FactPageNr,&gr_line[k-2],2);gr_line[k]=')';
					}
				}
				else{
          if (first_fl) copynaam(txttxt[56],gr_line,30);
					else {
						copynaam(txttxt[57],gr_line,30);
						for(k=0;k<29;k++) if(gr_line[k]==')') break;
						int2str(FactPageNr,&gr_line[k-2],2);gr_line[k]=')';
					}
				}
      }
      else if (j==9) {
        copynaam(txttxt[42]+18,gr_line,40);
        copynaam(_tijd+8,gr_line+7,4);
        gr_line[11]='-';
        copynaam(datum,gr_line+12,8);
				copynaam("BE-",gr_line+22,3);
        gt_txtklt(gr_line+22+3,7);
        gt_txtklt(gr_line+44,1);
        int2str(faktnr,gr_line+56,5);
        copynaam(datum,gr_line+69,8);
      }
    }
    prt_nl(gr_line);
  }
	FactPageNr++;
}

int iabs(float getal)
{
  return (int)getal;
}
 
void gr_footer(char datum[9],int lincnt,bool betaald)
{
  int j, i, ix, tb[6], btw_ix;
  float diff;
  int off;
  float kleinste;
  double goederen, tot_btw, leeggoed, subtotaal, leegterug, totaal;
 
  while (lincnt==0 || lincnt%(26-fakt_sp1)!=0) {prt_nl(""); lincnt++;}
  for (j=0; j<1; j++) prt_nl("");
  leegterug=0.;
  for (j=0; j<p_vrk->used; j++) {
    if (p_vrk->lijn[j].groep == groep_leeg && p_vrk->lijn[j].aantal<0) {
      leegterug -= p_vrk->lijn[j].totaal;
    }
  }
  mk_btw(); goederen=0.; tot_btw=goederen; totaal=goederen;/* alles op 0 */
  leeggoed=goederen;
  diff=4.5; off=4;
  for (ix=0; ix<4; ix++) { /* was 6 !!! */
    kleinste=101.;
    for (i=0; i<CUMBTW_COUNT; i++) {
      if (btw_cumul[i].btw_perc==-1.) {
        leeggoed=btw_cumul[i].totaal;
        btw_cumul[i].btw_perc=1000.;
      }
      if (btw_cumul[i].totaal && btw_cumul[i].btw_perc<kleinste) {
        kleinste=btw_cumul[i].btw_perc;
        btw_ix=i;
      }
    }
    if (kleinste==101.) break;
    tb[ix]=btw_ix;
    btw_cumul[btw_ix].btw_perc+=200;
    goederen+=btw_cumul[btw_ix].basis;
    tot_btw+=btw_cumul[btw_ix].btw;
    totaal+=btw_cumul[btw_ix].totaal;
  }
  cl_gr_line();
  for (i=0; i<ix; i++) {
    gr_line[4+off+iabs((9+diff)*i)]=(char)('A'+(btw_cumul[tb[i]].btw_perc-200.)/3.);
    gr_line[5+off+iabs((9+diff)*i)]='=';
    conv_getal((double)btw_cumul[tb[i]].btw_perc-200.,gr_line+6+off+iabs((9+diff)*i),4,1,1);
  }
  leeggoed+=leegterug; subtotaal=leeggoed+goederen+tot_btw;
  totaal=subtotaal-leegterug;
  conv_getal(leeggoed,gr_line+68,10,3,def_digits);
  prt_nl(gr_line);
  prt_nl("");
  cl_gr_line();
  for (i=0; i<ix; i++) {
    conv_getal((double)btw_cumul[tb[i]].basis,gr_line+4+off+iabs((9+diff)*i),8,1,def_digits);
  }
  conv_getal(goederen,gr_line+68,10,3,def_digits);
  prt_nl(gr_line);
  prt_nl("");
  cl_gr_line();
  for (i=0; i<ix; i++) {
    conv_getal((double)btw_cumul[tb[i]].btw,gr_line+4+off+iabs((9+diff)*i),8,1,def_digits);
  }
  conv_getal(tot_btw,gr_line+68,10,3,def_digits);
  prt_nl(gr_line);
  prt_nl("");
  cl_gr_line();
  conv_getal(subtotaal,gr_line+68,10,3,def_digits);
  prt_nl(gr_line);
  prt_nl("");
  cl_gr_line();
  conv_getal(leegterug,gr_line+68,10,3,def_digits);
  prt_nl(gr_line);
  prt_nl(""); 
  if (!pcl3flag) prt_nl("");
  cl_gr_line();
  conv_getal(totaal,gr_line+68,10,3,def_digits);
  prt_nl(gr_line);
  prt_nl(""); 
	if (betaald) {
		cl_gr_line();
		sprintf(gr_line+68,"%10s",txttxt[94]);
		prt_nl(gr_line);
	}
	else {
		cl_gr_line();
    copynaam(datum,gr_line+68,8);
		prt_nl(gr_line);
	}
}
 
void cl_gr_line(void)
{
  int i;
 
  for (i=0; i<80; i++) gr_line[i]=' ';
  gr_line[i]=0;
}
 
void gr_skip(int count)
{
  int i;
 
  gr_line[0]=0;
  for (i=0; i<count; i++) prt_nl(gr_line);
}
 
void prt_kl_faktuur(char datum[9])
{
  char _tijd[50];
 
  movmem(p_vrk->lijn[p_vrk->used-1].text,_tijd,sizeof(p_lin->text));
  mk_btw();
  _clr_ticket();
  p_lin=&p_vrk->lijn[0];
  add_text(""); 
	if(p_vrk->CreditNotaFlag==false) copynaam(txttxt[41],(p_lin-1)->text+20,20);
	else copynaam(txttxt[102],(p_lin-1)->text+20,20);
	int2str(faktnr,(p_lin-1)->text+35,5); (p_lin-1)->groep=GRP_T_RB;
  add_text("");
  txt_klt(datum);
  add_text("");
  add_text(txttxt[42]);
  copynaam(_tijd+8,(p_lin-1)->text+25,4);
  copynaam(datum,(p_lin-1)->text+32,8);
  add_text("");
  add_text(txttxt[16]); (p_lin-1)->groep=GRP_T_U;
  prt_btw(NO);
  prt_body(0);
  prt_hoofd(NO);
  prt_body(0);
}

void mk_btw(void)
{
  int i;
 
  clr_btw();
  p_lin=&p_vrk->lijn[0];
  for (i=0; i<p_vrk->used; i++) {
    if (p_lin->groep>=-9 && p_lin->groep<1000) add_btw();
    p_lin++;
  }
  calc_btw();
}

int IsNul(double bd_)
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}


//static char version[] = "KASRECLA 00.01 09/08/90";


/* 
#include "..\library\JamaConL.h"
#include "kashead.h"
 
extern struct s_verkopen *p_vrk;

extern char larg_fl, beep_fl, ir300_fl;
extern char reclame[6][11][22];
extern int ss1_delay, ss2_delay;

long get_hun();
 
*/
 
static int screen_cnt, pos, ir_rec_nr=-1, rec_maxix;
static long to_wait;
static long saver_on, mark_last;
 

/* --------------------------- Declaratie functies ---------------------- */
#include "kassa.h"
static void find_next_ir_rec(void);
static void show_mark(void);
static void wait_txt(int screen);

//////////////

static void find_next_ir_rec(void)
{
  int j, start_nr;
   
  start_nr=ir_rec_nr;
  FOREVER {
    ir_rec_nr++;
    if (ir_rec_nr==3) {
      if (start_nr==-1) {  // geen reclameteksten ingegeven !
        ir_rec_nr=-2;
        return;
      }
      ir_rec_nr=0;
    }
    for (j=0; j<10; j++) {
      if (reclame[ir_rec_nr][j][0]) return;
    } 
  }
}
 
static void disp_reclame(void)
{
  char b, buf[41];
  int screen, j, lineix, cnt;
 
  if (model==0) scr_clr();
  screen=0; pos=0; lineix=0; mark_last=get_hun()-100;
  if (ir_rec_nr==-1) find_next_ir_rec();
  FOREVER {
    if (model==0) show_mark();
    //largecom(0,0,1,0);
    if (model==1 || model==2) {
      if (ir_rec_nr==-2) return; // geen reclameteksten 

      for (j=0; j<40; j++) buf[j]=' ';
      buf[40]=0; cust_disp(buf);
      cnt=0;
      for (j=0; j<20; j++) {
        b=reclame[ir_rec_nr][lineix][j];
        if (!b) break;
        else buf[j]=b;
        cnt++;
      }
      lineix++;
      for (j=0; j<20; j++) {
        b=reclame[ir_rec_nr][lineix][j];
        if (!b) break;
        else buf[20+j]=b;
        cnt++;
      }
      lineix++;
      if (lineix>=10) {
        find_next_ir_rec();
        lineix=0;
      }
      cust_disp(buf);
      to_wait=get_hun();
      if (cnt) to_wait+=300; // enkel als er tekst op staat !
    }
    else {
      for (j=0; j<11; j++) {
        //largevid(0,32*j,reclame[screen][j],3);
      }
      wait_txt(screen);
      if (++screen==6) screen=0;
    }
    while (to_wait>get_hun()) {
      if (model==0) show_mark();
      if (kbtest()) goto end;
      Sleep(100);
    }
    if (kbtest()) goto end;
    back_check();
  }
 end:
  if (model==1 || model==2) cust_disp("");
  //largecom(0,0,1,0);
  beep_fl=GOOD;
}

static void show_mark(void)
{
  long time,i;

  time=get_hun();
  i = (time-mark_last)/100;
  while (i>0) {
    disp_vid(pos%80,pos/80," ",0);
    if (++pos>2000) pos=0;
    disp_vid(pos%80,pos/80,"*",0);
    mark_last=time;
    i--;
  }
  if (i<0) mark_last=time;
}

static void wait_txt(int screen)
{
  int i, j, char_count;
 
  char_count=0;
  for (j=0; j<11; j++) {
    for (i=0; i<22; i++) {
      if (reclame[screen][j][i]>' ') char_count++;
    }
  }
  to_wait=get_hun()+(char_count*100/CHAR_SEC);
}

// kasean.c

static char key_buf[20], bcd[7], _stuks_fl;
 
extern char beep_fl;
extern int art_count, ext_count, plu_ix, art_used, bc_option, bc_no_stxetx, ext_used;
extern char weeg_lead[4], krt_lead[], weeg_type, weeg_cpos, weeg_clen;
extern char tomra_lead[5], tomra_path[33], tomra_plu[11];
extern char weeg_epos, weeg_elen, weeg_edig, disp_fl;

extern struct _extra *extra;


/*
	Barcode-lezer : STX <DATA> ETX
									
	ofwel           <DATA> CR (kan alleen serieel, COM : 11 -14
									
	Als data begint met :
									
	      cijfer : dan is het een EAN nummer.
									
	      $-teken: dan is het een commando specifiek voor barcodes
		       Het volgende teken is een commando (0-9,A-Z).
									
			    0 -> Overrule BAK/FLES naar BAK  (hoewel fles)
			    1 -> Overrule BAK/FLES naar FLES (hoewel bakcode)
									
	      %-teken: Dan is het een KEY-COON die men wenst uit te voeren.
		       De twee volgende tekens zijn HEXADECIMAAL de toetscode.
									
	In de <DATA> string kan of een EAN nummer zijn, ofwel een keten van
	commando's (bv. $1$A%1E%01)
*/

bool IsValidHex(char byte)
{
  if (byte<'0') return false;
	if (byte>='a' && byte<='z') byte+='A'-'a';
	if (byte>'9' && byte<'A') return false;
	if (byte>'F') return false;
	return true;
}

int bc_process(int exec_rout)
{
  int pos, len, key, key_touched, parm, special, tomra, i, bonnr=0;
  int nr, punten;

  len=0; key_touched=0; parm=-1;
  //if (!bc_no_stxetx) bc_get();/* STX is gedetecteerd in exec_pen ...
  FOREVER {
    key=kbchar();
    if (key==0x03) break; // ETX
    if (len<sizeof(key_buf)) key_buf[len++]=key;
  }
  key_buf[len]=0;

  nr=-1; 
  if (len==20) {
    bool ValidRR=false;
    char basebuf[25], modcbuf[5];
    memcpy(basebuf,key_buf,9); basebuf[9]=0;
    int base=atol(basebuf);
    memcpy(modcbuf,key_buf+9,2); modcbuf[2]=0;
    int modc=atol(modcbuf);
    if ((base%97+modc)==97) ValidRR=true;
    else if (((2000000000+base)%97+modc)==97) ValidRR=true; // voor personen geboren na 1/1/2000
    if (ValidRR) {
      memset(&eID,0,sizeof(eID));
      memcpy(eID.nationalNumber,key_buf,11); eID.nationalNumber[11]=0;
      kaskrt.dsp_krtinfo(1);
      return 0;
    }
  }

  if (len==5 && stcd_i(key_buf,&i)==5 && i<kaskrt.krt_used) nr=i;
  else if (len==13 && key_buf[0]=='2' && key_buf[1]=='4') { // punten toevoegen op kaart
    for (i=0; i<5; i++) {
      if (key_buf[2+i]!=krt_lead[i]) break;
    }
    if (i==5) {
      key_buf[7+5]=0;
      stcd_i(key_buf+7,&punten);
    }
    p_vrk->lijn[p_vrk->used].groep=GRP_PUNTEXTRA;
    p_vrk->lijn[p_vrk->used].aantal=(float)punten;
    p_vrk->punten[p_vrk->used]=1.; //(float)punten;
    adj_lijn(p_vrk->used++);
    art_calc(NO); disp_fl=YES;
    return 0;
  }
  else if (len==13 && key_buf[0]=='2' && key_buf[1]=='5') { // zoek kaart
    for (i=0; i<5; i++) {
      if (key_buf[2+i]!=krt_lead[i]) break;
    }
    if (i==5) {
      key_buf[7+5]=0;
      stcd_i(key_buf+7,&nr);
    }
  } 
	else  if(len==13 && compare(key_buf,BCPREFIXWERKBON,9)==0) { // werkbonnen via barcode
    bonnr=0;
		for(i=9;i<=11;i++) {if(key_buf[i]>='0' && key_buf[i]<='9') bonnr=bonnr*10 + key_buf[i]-'0';}
		if (!wrk_exist(bonnr)) { beep_bad(); beep_fl=NO; }
		else{wrk_get(bonnr); disp_fl=YES;}
		return 0;
	}
  if (nr>=0) {
    p_vrk->krtnr=nr;
    kaskrt.dsp_krtinfo(0);
    return 0;
  }
  
  pos=0;
  while (pos<len) {
    if (key_buf[pos]>='0' && key_buf[pos]<='9' && exec_rout) {
      
			special=NO;
      if (weeg_type) {
        special=weeg_type;
        if (weeg_type==3) special=1;
        for (i=0; i<3; i++) {
          if (weeg_lead[i]==0) break;
          else if (weeg_lead[i]!=key_buf[pos+i]) {
            special=NO;
            break;
          }
        }
      }
      if (special) {
        if (special==2) {
          for (i=0; i<weeg_elen; i++) {
            if (i==(weeg_elen-weeg_edig)) numkey(10);
            numkey(key_buf[pos+weeg_epos+i]-'0');
          }
          maal(0);
        }
        for (i=0; i<weeg_clen; i++) numkey(key_buf[pos+weeg_cpos+i]-'0');
        plu(1);
        if (beep_fl==GOOD) {
          if (special==1) {
            for (i=0; i<weeg_elen; i++) {
              if (i==(weeg_elen-weeg_edig)) numkey(10);
              numkey(key_buf[pos+weeg_epos+i]-'0');
            }
            if (weeg_type==3) numkey(12);
            eenh_prijs(0);
          }
        }
				break;
      }

      tomra=NO;
      if (tomra_lead[0]) {
        tomra=YES;
        for (i=0; i<3; i++) {
          if (tomra_lead[i]==0) break;
          else if (tomra_lead[i]!=key_buf[pos+i]) {
            tomra=NO;
            break;
          }
        }
      }
      if (tomra) {
				int _pos=pos+i; // EAN-13 - 1 checkdigit - leadin
				char filnam[100];
				key_buf[pos+12]=0; // ipv checkdigit
				sprintf(filnam,"%s\\ER%s.txt",tomra_path,&key_buf[_pos]);

				char filbuf[1000];
				filbuf[0]=0;
				int filref=dopen(filnam,RDWRMODE);
				if (filref>=0) {
				  i=dread(filref,filbuf,sizeof(buf)-1);
					filbuf[i]=0;
					dclose(filref);
				}
				else {
					CString cstr;
					cstr.Format("Impossible to open: %1s",filnam);
				  ConMessageBox(cstr,"Tomra Ticket not found",MB_ICONEXCLAMATION|MB_OK);
				}
				if (filbuf[0]) {
					CString cstr = filbuf;
					i=cstr.Find("Refund=");
					double tomra_refund=0.;
					if (i>0) {
						tomra_refund=atoi(&filbuf[i+7])/100.;
					}
					int plu_ix=kasplu.plu_req(tomra_plu,ARTCODE_LEN);
					if (plu_ix>=0) {
						//double regsave=reg;
						//if (reg==0) {
						//	reg=p_vrk->totaal[0]; reg_db=15; reg_da=15;
						//}
						p_lin=&p_vrk->lijn[p_vrk->used];
						movmem(kasplu.art_info.code,p_lin->code,ARTCODE_LEN);
						p_lin->aantal=-1;
						p_lin->prijs=(float)tomra_refund;
						p_lin->btw=kasplu.art_info.btw;
						p_lin->groep=kasplu.art_info.groep;
						p_lin->totaal=p_lin->prijs*p_lin->aantal;
						p_vrk->totaal[0]+=p_lin->totaal;
						p_vrk->totaal[1]+=p_lin->totaal;
						adj_lijn(p_vrk->used);
						adj_text(p_vrk->used);
						p_vrk->used++; p_lin++;
						disp_window();
						//reg=regsave;

						char txtbuf[41]; sprintf(txtbuf,"%40s","");
						int it=POS_NAAM;

						i=cstr.Find("Time=");
						if (i>0) {
							txtbuf[it++]=filbuf[i+5+4];
							txtbuf[it++]=filbuf[i+5+5];
							txtbuf[it++]=filbuf[i+5+2];
							txtbuf[it++]=filbuf[i+5+3];
							txtbuf[it++]=filbuf[i+5+0];
							txtbuf[it++]=filbuf[i+5+1];

							txtbuf[it++]=filbuf[i+5+7];
							txtbuf[it++]=filbuf[i+5+8];
							txtbuf[it++]=filbuf[i+5+9];
							txtbuf[it++]=filbuf[i+5+10];
						}
						txtbuf[it++]='#';
						i=cstr.Find("Reference=");
						if (i>0) {
							for (i=i+10; i<cstr.GetLength(); i++) {
								if (filbuf[i]<'0') break;
								txtbuf[it++]=filbuf[i];
							}
							txtbuf[it++]='-';
						}
						i=cstr.Find("NumEntries=");
						if (i>0) {
							for (i=i+11; i<cstr.GetLength(); i++) {
								if (filbuf[i]<'0') break;
								txtbuf[it++]=filbuf[i];
							}
							txtbuf[it++]=' ';
						}
						txtbuf[it]=0;
						add_text(txtbuf);
						
						disp_window();
						unlink(filnam);
					}
				}
				break;
			}

      if (add_ean(key_buf+pos)) {
        beep_bad(); beep_fl=NO; 
//      disp_vid(2,3,key_buf+pos,8);  // display hoeft niet meer, overschrijft trouwens omdat lengte niet beperkt wordt tot 15
      }
      break;
    }
    else if (key_buf[pos]=='$') {
      switch (key_buf[pos+1]) {
        case '0': bak_fles=0; p_vrk->stuks_flag=NO; break;
        case '1': bak_fles=1; CntFlesInBak=-1; p_vrk->stuks_flag=YES; break;
        case '2': p_vrk->leeg_flag|=1; break;
        case '3': p_vrk->leeg_flag&=0xFFFE; break;
        case '4': p_vrk->leeg_flag|=2; break;
        case '5': p_vrk->leeg_flag&=0xFFFD; break;
        case '6': bak_fles=0; CntFlesInBak=6;  p_vrk->stuks_flag=YES; break;
        case '7': bak_fles=0; CntFlesInBak=12; p_vrk->stuks_flag=YES; break;
        case '8': bak_fles=0; CntFlesInBak=24; p_vrk->stuks_flag=YES; break;
      }
      disp_window();
      pos+=2;
    }
    else if (key_buf[pos]=='+') {
      parm=16*hex2dec(key_buf[pos+1])+hex2dec(key_buf[pos+2]);
      pos+=3;
    }
    else if (key_buf[pos]=='%' && IsValidHex(key_buf[pos+1]) && IsValidHex(key_buf[pos+2])) {
      key_touched=16*hex2dec(key_buf[pos+1])+hex2dec(key_buf[pos+2]);
      if (key_touched<MAX_KEYS && exec_rout) {
        if (parm>=0) {
					if (key_touched==99) { // wrk_put ()
						parm+=1000;
					}
				  (*toetsen[key_touched].rout)(parm);
				}
        else (*toetsen[key_touched].rout)(toetsen[key_touched].argument);
      }
      if (key_touched==13) bak_fles=-1;
      pos+=3;
    }
    else break;
  }
  return key_touched;
}
 
int hex2dec(char byte)
{
  int ret;
 
  ret=byte-'0';
  if (ret<0) ret=0;
  else if (ret>9) {
    if (byte>='a' && byte<='z') byte+='A'-'a';
    ret=byte-'A'+10;
  }
  return ret;
}

double String2Getal(CString S,char decim_kar)
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

/* laatste */
