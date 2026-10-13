// KasKRTc.cpp: implementation of the CKasKRT class.
//
//////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4996)

#pragma pack(1)

// #define WINVER 0x0501  // was 500
// #define _WIN32_WINNT 0x0501  // was 500
#include "p:\jamacon\library\JamaConL.h"
#include "kashead.h"

#include "kassysc.h"
#include "kaspluc.h"
#include "KasKRTc.h"
#include "Afxwin.h"
#include "Markup.h"
#if XP_KASSA
#include "eidnative.h"
#else
#include "swelio.h"
#endif
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


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



static void Asc2JamaAsc(char *ps_,int len_);
static void JamaAsc2Asc(char *ps_,int len_);

static CString CurrentTime2String(void);
static CString Date2String(unsigned int date_,int mode_);
static bool FileExist(char *fname_);
static bool FileExist(CString Cfname_);

static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_);
static int cmp_srt(char *p1,char *p2,int len);
static void int2str(int d, char *s, int len); // len negatief geeft leadind zeros, anders spaces 
static double String2Getal(CString S,char decim_kar);
static unsigned int String2Date(CString datestr_,CString format_="DDMMJJJJ");
static double String2Double(CString S){return String2Getal(S,',');}
static double String2Double(CString S,char decim_kar){ return String2Getal(S,decim_kar);}
static int String2Int(CString S){return (int)(String2Getal(S,','));}
static CString Double2String(double getal,long mode); // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
static int SpaceZeros(char* ps_,int max_len);
static void String2DateUur(char *ps_,unsigned int *jdt_,int *uur_);
static void DateUur2String(char *ps_,unsigned int jdt_,int uur_);
static void DisplayKalender(int xpos_,int ypos_,unsigned int dt_eerste_,unsigned int inqdate_,int inquur_,unsigned int dt_min_);
static void DisplayKeyboard(int x, int y, int x_adjust_=0,int y_adjust_=0, int soort_kb_=0);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/* ---------------------------------------------------------------------- */
extern CKasPLU kasplu;
extern CKasSYS kassys;
extern bool KassaTestConfigFlag;

extern struct s_grp_info {
  char naam[20];
  float btw;
} grp_info[100];


#if XP_KASSA
extern TEIDIdentity eID;
extern TEIDAddress eIDaddr;
#else
extern tagEidIdentityA eID;
extern tagEidAddressA eIDaddr;
#endif
void UpdateOnJMC();
extern HWND JMD;
extern CString PathSpoolToServer, JmcCmdFilepath, KasCmdFilepath;

extern struct s_lijn *p_lin;
extern struct s_verkopen *p_vrk;
extern char txttxt[200][150], *txterr[], disp_fl, tijd[];
extern char prt_krtfull[5][41], def_valuta[],TotaalOp5CentAfronden, PromoNotOnHorecaPrice;
extern int krt_count, krtsort, krt_bits, def_digits, groep_leeg, EigenPrijsOpStuksAllowed;
extern long mem_needed;
extern float krtperc, krtfull, krtvalue;
extern struct s_verkopen *p_vrk;
extern char *txtjn[], *txtper[], *txtcumper[], *txtmnd[], *txtfin[];
extern void disp_window(void);
extern void show_key(struct layout *p_lay, int keycnt);
extern struct layout keyb_layout[];
extern int KeyboardType;

extern int reg_db, reg_da, reg_kom, regix,vrk_ix;
extern char regalfa[];
extern int reg_sign;
extern double reg,reg_aantal;
extern void plu(int dum);
extern void korting(int type);
extern void subtotaal(int dum);
extern void add_text(char *s);
extern void adj_lijn(int index);
extern void art_calc(char compleet);

unsigned char fm_us40[]  = {7,0xC8,40,0,0,0,0};
unsigned char fm_us30[]  = {7,0xC8,30,0,0,0,0};
unsigned char fm_us25[]  = {7,0xC8,25,0,0,0,0};
unsigned char fm_us15[]  = {7,0xC8,15,0,0,0,0};
unsigned char fm_us7[]  = {7,0xC8,7,0,0,0,0};
unsigned char fm_us1U[]  = {7,0xC8,1,0,1,0,0};
unsigned char fm_os79[]  = {7,0x88,79,0,0,0,0};
unsigned char fm_os30[]  = {7,0x88,30,0,0,0,0};
unsigned char fm_os20[]  = {7,0x88,20,0,0,0,0};
unsigned char fm_os10[]  = {7,0x88,10,0,0,0,0};
unsigned char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
unsigned char fm_uu2_[]   = {6,0xD0,2,0,0x00,0};
unsigned char fm_ou5[]   = {6,0x90,5,0,0x60,0};
unsigned char fm_ui2[]   = {6,0xD1,2,0,0x60,0};
unsigned char fm_ol8[]   = {6,0x93,8,0,0x70,0};
unsigned char fm_of6_2[] = {6,0x94,6,2,0x70,0};
unsigned char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
unsigned char fm_udat[]  = {4,0xC0,1,'/'};
unsigned char fm_odat[]  = {4,0x80,1,'/'};
unsigned char fm_menu[]  = {7,0x48,1,0,9,0,0};
unsigned char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};

CMarkup AllBestXml;

CUIntArray TbBestXmlPos,TbBestKlantNr,TbSelectedDays;
CStringArray  TbBestDateString;
int MaxTbBest,MaxSelectedDays;
  
struct _BestelInfo{
  int KlantNr;
  char OpmaakDatum[25];
  char AfhaalDatum[25];
  char Opmerking[4][40];
  double voorschot;
  char FileNameXml[100];
} BestelInfo,LastLoadedBestelInfo[VRK_COUNT];

CKasKRT::CKasKRT()
{
	brwsfirst=0; krtsort=0;
}

CKasKRT::~CKasKRT()
{
  long krtsize;

  krtsize=(long) sizeof (struct s_krtinfo) * (krt_count+10);
  if (krtsize) rlsml((char *)krtinfo,krtsize);
}

void CKasKRT::sel_kltkrt(int type) // 0 = klantenkaart, 1=bestelling 
{
  if (krt_bits&8) {
    dsp_krtinfo(3);
    return;
  }
 
  char buf[57], find[30], findnetto[30],str_netto[100], byte;
  int j,k, i, krec_,key, keyraw, aantal, prevsel, x, y, attr, selected, findix, krtnrsave, nr, old_screen,last_krtsort;
  int ret_positie_=-1,*pvrk_kaart_,ScreenLines=21,tb_scr[25],only_bestelling_=NO,pos_,knr_,findixnetto;

  old_screen=ConSelect(KrtConRef);last_krtsort=krtsort;
  if(type==1)pvrk_kaart_=&p_vrk->BestelKrtNr; else pvrk_kaart_=&p_vrk->krtnr;
  krtnrsave=*pvrk_kaart_;
  if(type==1 && *pvrk_kaart_==0){
    if(LastLoadedBestelInfo[vrk_ix].KlantNr>0) *pvrk_kaart_=LastLoadedBestelInfo[vrk_ix].KlantNr;
  }
redo_full:;
  if(type==1) MakeAllBestXml(0);
  cls();ConStyle(CON_STYLE_NOBACKGROUND);
//  disp_panel(12,0,58,23,PANEL_VER_SMALLER | PANEL_HOR_SMALLER | PANEL_WITH_EDGE,RGB(255,255,0));
  disp_key(70, 0,10,2,22);
  disp_key(70, 2,10,3,23);
  disp_key(70,17,10,3,114);
  disp_key(70,20,10,3,24);
  disp_key(70,23,10,2,13);
  disp_key( 0, 0,12,4,112);
  if(type==1){
    disp_ikey(15,23,15,2,5000,"wijzig klant",KLEUR_FTOETS);
    disp_ikey(30,23,15,2,5001,"nieuwe klant",KLEUR_FTOETS);
    if(only_bestelling_) disp_ikey(45,23,15,2,5002,"alle klanten",KLEUR_FTOETS);
    else disp_ikey(45,23,15,2,5002,"bestellingen",KLEUR_FTOETS);

  }


  buf[0]=' '; buf[2]=' '; buf[3]=0;
  for (j=0; j<26; j++) {
    y = 7 + (j/3) * 2;
    x = (j%3) * 4; 
    buf[1]='A'+j;
    disp_ikey(x,y,4,2,2000+'A'+j,buf);
  }
  for (j=0; j<=9; j++) {
    y = (j/2) * 2;
    x = (j%2) * 5;
    buf[1]='0'+j;
    disp_ikey(x+70,7+y,5,2,2000+'0'+j,buf);
  }
  disp_ikey(8,23,4,2,2000+' '," ");
  disp_key(0,5,12,2,83);
  disp_key(70,5,10,2,83);
  findix=0; selected=-1; brwsfirst=0; krtnrsave=-1;
  if (*pvrk_kaart_>0) {
    for (i=0; i<krt_used; i++) {
      if (krtinfo[i].nr==*pvrk_kaart_) {
      
        selected=i;
        brwsfirst=i;
        *pvrk_kaart_=0;
        break;
      }
    }  
  }
  else {
    if(ret_positie_>=0) brwsfirst=ret_positie_;
  }
  disp_clr(12,0,58,23);
  disp_panel(12,0,58,23,PANEL_VER_SMALLER | PANEL_HOR_SMALLER | PANEL_WITH_EDGE,RGB(255,255,0));

  FOREVER {
   redisp:;
    movmem(find,buf,11);
    i=findix;
    if (i<0) i=0;
    for (; i<12; i++) buf[i]=' ';
    buf[i]=0;
    disp_vid(0,4,buf,2);
    p_krt=&krtinfo[brwsfirst];

    pos_=brwsfirst;
    for(aantal=0;aantal<ScreenLines;aantal++) tb_scr[aantal]=-1;
    for(aantal=0;aantal<ScreenLines;aantal++){
      pos_=FindNextKlant(pos_,only_bestelling_,1);
      if(pos_<0 || pos_>=krt_used) break;
      tb_scr[aantal]=pos_;
      pos_++;
    }

    for (j=0; j<aantal; j++) {
      knr_=tb_scr[j];
      if (knr_==selected) attr=8; else attr=2;
      if(type==1 && HeeftBestelling(krtinfo[knr_].nr)){
				attr+=4;
//				disp_panel(13,1+j,56,1,PANEL_WITH_EDGE,RGB(255,255,0)); 
      }
      p_krt=&krtinfo[knr_];krtline(buf);
      disp_vid(13,1+j,buf,attr);
    }
    for (i=0; i<56; i++) buf[i]=' '; buf[i]=0;
    for (j; j<ScreenLines; j++) disp_vid(13,1+j,buf,2);

    prevsel=selected;ret_positie_=brwsfirst;
    keyraw=kbchar();
    key=keyraw;
    if (key==251*256) key=-1;
    if (key<0x10000) {
      if (key>=256) {
        key/=256;
        switch (key) {
          case  3: key=83; break; // backspace
          case 12: key=23; break;  // PgUp
				  case 13: key=24; break;   // PgDn
          case 18: key=18; break;  // ENTER
          default: key= 1; break; /* om ongeldige toets te maken */
        }
				if(key==1 || key==8 || key==9) goto redisp;
      }
      else key+=2000;
    }
    else key/=0x10000;
 //   key=keyraw/0x10000;
    if(key==5000){
      if(selected>=0){
				krec_=krtinfo[selected].nr;
				if(FGetKaart(krec_)){
					if(UpdateKaartFiche(krec_)) ReloadKaartFile();
          if(KaartFiche.naam[0]=='X' && KaartFiche.naam[1]=='Y' && KaartFiche.naam[2]=='Z') *pvrk_kaart_=-1;
          else *pvrk_kaart_=krec_;
					goto redo_full;
				}
      }
    }
    if(key==5001){
      for(k=0;k<krt_used;k++){
        if(krtinfo[k].naam[0]==0 || (krtinfo[k].naam[0]=='X' && krtinfo[k].naam[1]=='Y' && krtinfo[k].naam[2]=='Z')) break;
      }
      if(k<krt_used){
				selected=k;krec_=krtinfo[selected].nr;
        if(FGetKaart(krec_)){
					for(k=0;k<40;k++) KaartFiche.naam[k]=' ';
					if(UpdateKaartFiche(krec_)){ 
						ReloadKaartFile();
						if(KaartFiche.naam[0]=='X' && KaartFiche.naam[1]=='Y' && KaartFiche.naam[2]=='Z') *pvrk_kaart_=-1;
						else *pvrk_kaart_=krec_;
					}
					goto redo_full;
				}
      }
    }
    if(key==5002){
      if(only_bestelling_) only_bestelling_=NO; else only_bestelling_=YES;
      if(only_bestelling_){
				if(*pvrk_kaart_ && HeeftBestelling(krtinfo[*pvrk_kaart_].nr) ==false) *pvrk_kaart_=0;
				if(ret_positie_>=0 && HeeftBestelling(krtinfo[ret_positie_].nr)==false) ret_positie_=-1;
      }
      selected=-1;goto redo_full;
    }
    if (key==112) {
      if (selected>=0) break;
      else {
        ConMessageBox(txttxt[1],"Opzoeken Klanten",MB_ICONEXCLAMATION|MB_OK);
      }
    }
    else if (key==114) {
      krtsort++; findix=0;
      if (krtsort==1) krtsort++; // GEEN kode
      if (krtsort==4) krtsort=0;

      if (selected>=0) {
        *pvrk_kaart_=krtinfo[selected].nr;
      } 
      sortkltkrt();
      brwsfirst=0;
      if (selected>=0) {
        for (i=0; i<krt_used; i++) {
          if (krtinfo[i].nr==*pvrk_kaart_) {
            selected=i;
            brwsfirst=i;
            *pvrk_kaart_=0;
            break;
          }
        }
      }  
      kassys.upd_sys(); /* pas doen als alles zeker in orde is ! */
      findix=0; find[0]=0; last_krtsort=krtsort;
      goto redisp;
    }
    selected=-1;
    if (keyraw==251*256) { // left mouse
      x=mspos_h; y=mspos_v;
      if (y>=1 && y<=21 && x>=13 && x<=67) {
        if(tb_scr[y-1]>=0) {
					selected=tb_scr[y-1]; 
          if (selected==prevsel) break;
				}
      }
    }

    if (key==18) { // ENTER GEDUWD
      if(prevsel>=0) {
        selected=prevsel; break;
      }
    }


    if (key==22) { // terug 
      if (krtnrsave>=0) *pvrk_kaart_=krtnrsave;
      else *pvrk_kaart_=0;
      break;
    }
    if (key==13) {
      selected=-1;
      break;  
    }
    else if (key==23) {
      pos_=brwsfirst;
      for(k=0;k<19;k++){
        pos_=FindNextKlant(pos_,only_bestelling_,-1);
				if(pos_>0) pos_--; else break;
      }
      if(pos_>=0) brwsfirst=pos_; else brwsfirst=0;
    }
    else if (key==24) {
      for(k=19;k>=0;k--) if(tb_scr[k]>=0) break;
      if(k>=19) brwsfirst=tb_scr[k];
    }
    if (brwsfirst >= krt_used) brwsfirst-=19;
    if (brwsfirst<0) brwsfirst=0;
    
    if ((key==83) || (key>=2000 && key<3000)) {
      if (key==83) {
        findix--;
        if (findix<0) findix=0;
      }
      if (key>=2000 && key<=3000) {
        find[findix]=key-2000;
				if ((find[findix]>='a') && (find[findix]<='z')) find[findix]+='A'-'a';
				if(findix<25) findix++;
      }
      if (findix>0) {

				if(find[0]>='0' && find[0]<='9') {  
				  if (krtsort==0) krtsort=2;				// zo alfabetisch op naam en nummer ingedrukt, dan op telefoonnummer
				}
				else if (krtsort!=0) krtsort=0;			// zo letter en niet alfabetisch, dan opnieuw sorteren

				if(krtsort!=last_krtsort){
					sortkltkrt();last_krtsort=krtsort;
				}
        if (krtsort==3) {
          nr=0;
          for (i=0; i<findix; i++) {
            nr=nr*10+find[i]-'0';
          }
          for (j=0; j<krt_used; j++) {
            if (krtinfo[j].nr==nr) {
              brwsfirst=j;
              selected=j;
            }             
          }
        }
        else {
					findixnetto=CopyNettoChar(find,findnetto,findix);
          for (j=0; j<krt_used; j++) {
						zeros(str_netto,sizeof str_netto);
						if(krtsort==1) CopyNettoChar(krtinfo[j].code,str_netto,sizeof krtinfo[0].code);
						else if(krtsort==2) CopyNettoChar(krtinfo[j].telefoon,str_netto,sizeof krtinfo[0].telefoon);
						else CopyNettoChar(krtinfo[j].naam,str_netto,sizeof krtinfo[0].naam);
            for (i=0; i<findixnetto; i++) {
              byte = str_netto[i];
              if ((byte>='a') && (byte<='z')) byte+='A'-'a';
              if (byte>findnetto[i]) {
                j=krt_used; i=findixnetto;
                break;
              }
              brwsfirst=j;
              selected=j;
              if (byte < findnetto[i]) break;
            }
            if (i==findixnetto) break;       
          }
        }
      }
    }
  }
  if (selected>=0) {
    if(type==1){
      k=LoadBestBon(krtinfo[selected].nr);
      if(k<1 || k>2) {selected=-1;goto redo_full;}
      else if(k==2) *pvrk_kaart_=krtinfo[selected].nr; // nieuwe bestelling 
      else if(k==1) *pvrk_kaart_=0; // bestaande bestelling  opgeladen 
    }
    else *pvrk_kaart_=krtinfo[selected].nr; // klanten-kaart nummer
    ConSelect(old_screen);
    if(*pvrk_kaart_) dsp_krtinfo(0);
  }
  else {
    ConSelect(old_screen); disp_fl=YES;
  }
}



int CKasKRT::FindNextKlant(int pos_,int only_bestelling_,int mode_) // mode_ : 1=vooruit, -1=achteruit
{
   if(pos_<0 || pos_>=krt_used) return -1;
   FOREVER{
     if(only_bestelling_==NO || HeeftBestelling(krtinfo[pos_].nr)) break;
     if(mode_<0){pos_--; if(pos_<0) break;}
     else {pos_++; if(pos_>=krt_used) break;}
   }
   return pos_;
}
 

bool CKasKRT::HeeftBestelling(unsigned int klantnr_)
{
  int k;

  for(k=0;k<MaxTbBest;k++) if(TbBestKlantNr.GetAt(k)==klantnr_) break;
  if(k<MaxTbBest) return true;
  return false;
}


int CKasKRT::LoadBestBon(int recordnr_) // 0=false, 1=bestaande bon opgeladen, 2=nieuwe bon
{
  int k,z, key,ScreenLines=18,rebuild_screen_=YES,pos_,uur_;
	short jj,mm,dd;
  bool nieuwe_bestelling_;
  unsigned int date_,dt_nu_,dt_eerste;
  char dsptekst[100],keytekst[100],buf_[50];
  CString cstr_,orig_sector_,tagname_,bonfilename_;
   SYSTEMTIME st;
  CMarkup bonxml_; 
  COLORREF kleur_;
  

  FGetKaart(recordnr_);ConStyle(0);nieuwe_bestelling_=true;
 
  if(MakeAllBestXml(recordnr_)==0){
    zeros(&BestelInfo,sizeof BestelInfo);
    if(recordnr_==LastLoadedBestelInfo[vrk_ix].KlantNr) bcopy(&LastLoadedBestelInfo[vrk_ix],&BestelInfo,sizeof BestelInfo);
    BestelInfo.KlantNr=recordnr_;
    zeros(BestelInfo.OpmaakDatum,sizeof BestelInfo.OpmaakDatum);pos_=0;
    GetLocalTime(&st);
    int2str((int)st.wDay,&BestelInfo.OpmaakDatum[pos_],-2);pos_+=2;BestelInfo.OpmaakDatum[pos_++]='/'; // datum
    int2str((int)st.wMonth,&BestelInfo.OpmaakDatum[pos_],-2);pos_+=2;BestelInfo.OpmaakDatum[pos_++]='/';
    int2str((int)st.wYear,&BestelInfo.OpmaakDatum[pos_],-4);pos_+=4;BestelInfo.OpmaakDatum[pos_++]='-'; // uur
    int2str((int)st.wHour,&BestelInfo.OpmaakDatum[pos_],-2);pos_+=2;BestelInfo.OpmaakDatum[pos_++]=':';  
    int2str((int)st.wMinute,&BestelInfo.OpmaakDatum[pos_],-2);
    bonxml_.SetDoc("");bonxml_.AddElem("BESTELLING");bonxml_.IntoElem();
    bonfilename_=CString("B00-");
    cstr_=CString(BestelInfo.OpmaakDatum);
    if(cstr_.GetLength()>=16){
      bonfilename_+=cstr_.Mid(6,4)+cstr_.Mid(3,2)+cstr_.Mid(0,2); //JJJJMMDD
      bonfilename_+=CString("-")+cstr_.Mid(11,2)+cstr_.Mid(14,2);
    }
    bonfilename_+=CString("-")+CString(KaartFiche.code); 
    bonfilename_.TrimRight();bonfilename_+=".XML";
    bonxml_.AddElem("FILENAME",bonfilename_);
    bonxml_.AddElem("OPMAAKDATUM",BestelInfo.OpmaakDatum);
    bonxml_.AddElem("KLANTNR",KaartFiche.code);
    nieuwe_bestelling_=true;
  }
  else{
    FOREVER{
      cls();
      disp_panel(0,0,80,1,0,KLEUR_TITEL);
      disp_panel(0,1,80,1,0,RGB(240,240,240)); 
      zeros(dsptekst,sizeof dsptekst);
      bcopy("Bestelling(en) van : ",&dsptekst[0],21);
      bcopy(KaartFiche.naam,&dsptekst[21],sizeof KaartFiche.naam);
      dsptekst[SpaceZeros(dsptekst,80)]='\0';
      disp_vid(0,0,dsptekst,0);
      zeros(dsptekst,sizeof dsptekst);
      bcopy("Besteld op",&dsptekst[2],10);bcopy("Wordt afgehaald op",&dsptekst[30],18);
      dsptekst[SpaceZeros(dsptekst,80)]='\0';
      disp_vid(0,1,dsptekst,0);
      disp_key(0,vdmax_v-2,20,2,0x16);
      disp_ikey(20,vdmax_v-2,20,2,109,"nieuwe bestelling",KLEUR_FTOETS);
      for(k=0;k<ScreenLines;k++){
        if(k>=MaxTbBest) break;
        zeros(keytekst,sizeof keytekst);
        AllBestXml.GotoElemIndex(TbBestXmlPos.GetAt(k));
				AllBestXml.IntoElem();
        AllBestXml.ResetMainPos();AllBestXml.FindElem("OPMAAKDATUM");cstr_=AllBestXml.GetData();
        if(cstr_.GetLength()) Zcstr2arr(cstr_,&keytekst[1],30);
        AllBestXml.ResetMainPos();AllBestXml.FindElem("AFHAALDATUM");cstr_=AllBestXml.GetData();
        zeros(buf_,sizeof buf_);if(cstr_.GetLength()) Zcstr2arr(cstr_,buf_,30);
				String2DateUur(buf_,&date_,&uur_); if(date_) datefm(&keytekst[30],date_,14);
        if(uur_){keytekst[56]='(';int2str(uur_,&keytekst[57],-2);bcopy(":00h)",&keytekst[59],5);}
        keytekst[SpaceZeros(keytekst,79)]='\0';
        disp_ikey(0,2+k,80,1,5000+k,keytekst,KLEUR_GROEN);
      }
      if(k<ScreenLines) disp_clr(0,k+2,79,ScreenLines-k);

      key=kbchar();
      if (key&0xFFFF0000) key/=0x10000; 
      else if(key>255) key=key/256;
      if(key==0x16 || key==101) return 0;
      if(key>=5000 && key<5000+ScreenLines){
        zeros(&BestelInfo,sizeof BestelInfo);
        BestelInfo.KlantNr=recordnr_;
        AllBestXml.GotoElemIndex(TbBestXmlPos.GetAt(key-5000));
				AllBestXml.IntoElem();
				AllBestXml.ResetMainPos();bonfilename_=AllBestXml.FindGetData("FILENAME");
        if(bonxml_.Load(bonfilename_)){nieuwe_bestelling_=false; break;}
      }
      if(key==109){ // nieuwe bestelling 
        zeros(&BestelInfo,sizeof BestelInfo);
        if(recordnr_==LastLoadedBestelInfo[vrk_ix].KlantNr) bcopy(&LastLoadedBestelInfo[vrk_ix],&BestelInfo,sizeof BestelInfo);
				BestelInfo.KlantNr=recordnr_;
				zeros(BestelInfo.OpmaakDatum,sizeof BestelInfo.OpmaakDatum);pos_=0;
				GetLocalTime(&st);
				int2str((int)st.wDay,&BestelInfo.OpmaakDatum[pos_],-2);pos_+=2;BestelInfo.OpmaakDatum[pos_++]='/'; // datum
				int2str((int)st.wMonth,&BestelInfo.OpmaakDatum[pos_],-2);pos_+=2;BestelInfo.OpmaakDatum[pos_++]='/';
				int2str((int)st.wYear,&BestelInfo.OpmaakDatum[pos_],-4);pos_+=4;BestelInfo.OpmaakDatum[pos_++]='-'; // uur
				int2str((int)st.wHour,&BestelInfo.OpmaakDatum[pos_],-2);pos_+=2;BestelInfo.OpmaakDatum[pos_++]=':';  
				int2str((int)st.wMinute,&BestelInfo.OpmaakDatum[pos_],-2);
        bonxml_.SetDoc("");bonxml_.AddElem("BESTELLING");bonxml_.IntoElem();
        bonfilename_=CString("B00-");
        cstr_=CString(BestelInfo.OpmaakDatum);
        if(cstr_.GetLength()>=16){
          bonfilename_+=cstr_.Mid(6,4)+cstr_.Mid(3,2)+cstr_.Mid(0,2); //JJJJMMDD
          bonfilename_+=CString("-")+cstr_.Mid(11,2)+cstr_.Mid(14,2);
				}
        bonfilename_+=CString("-")+CString(KaartFiche.code); 
        bonfilename_.TrimRight();bonfilename_+=".XML";
				Zcstr2arr(bonfilename_,BestelInfo.FileNameXml,sizeof BestelInfo.FileNameXml-1);
        bonxml_.AddElem("FILENAME",bonfilename_);
        bonxml_.AddElem("OPMAAKDATUM",BestelInfo.OpmaakDatum);
        bonxml_.AddElem("KLANTNR",KaartFiche.code);
				nieuwe_bestelling_=true;
				break;
      }
    } 
  }

  bonxml_.ResetPos();
  bonxml_.FindElem("BESTELLING"); bonxml_.IntoElem();
  bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMAAKDATUM");
  if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.OpmaakDatum,30);
  bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("AFHAALDATUM");
  if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.AfhaalDatum,30);
  bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMERK1");
  if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.Opmerking[0],40);
  bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMERK2");
  if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.Opmerking[1],40);
  bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMERK3");
  if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.Opmerking[2],40);
  bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMERK4");
  if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.Opmerking[3],40);
  String2DateUur(BestelInfo.AfhaalDatum,&date_,&uur_);
  Zcstr2arr(bonfilename_,BestelInfo.FileNameXml,sizeof BestelInfo.FileNameXml-1);
  GetLocalTime(&st);
  dt_nu_=datejd((int)st.wYear%100,(int)st.wMonth,(int)st.wDay);
  dt_eerste=date_; if(dt_eerste==0) dt_eerste=dt_nu_;  
  jddate(dt_eerste,&jj,&mm,&dd);
  dt_eerste=datejd(jj,mm,1); 
  FOREVER{

    cls();scrnum=0;scrget(2,1501);
    disp_panel(0,0,80,1,0,KLEUR_TITEL);
    disp_panel(0,1,50,5,0,RGB(255,255,100));
    kleur_=KLEUR_ROOD; if(date_>0) kleur_=KLEUR_GROEN;
    disp_panel(12,7,20,1,0,kleur_);
    disp_vid(14,7,BestelInfo.AfhaalDatum,0);
    zeros(dsptekst,sizeof dsptekst);
    bcopy("Bestelling op ",&dsptekst[30],15);
    bcopy(BestelInfo.OpmaakDatum,&dsptekst[45],20);
    dsptekst[SpaceZeros(dsptekst,50)]='\0';
    disp_vid(0,0,dsptekst,0);
    
    zeros(dsptekst,sizeof dsptekst);
    bcopy("Nummer  : ",&dsptekst[0],10);
    bcopy(KaartFiche.code,&dsptekst[10],sizeof KaartFiche.code);
    dsptekst[SpaceZeros(dsptekst,50)]='\0';
    disp_vid(0,1,dsptekst,0);
    zeros(dsptekst,sizeof dsptekst);
    bcopy("Naam .. : ",&dsptekst[0],10);
    bcopy(KaartFiche.naam,&dsptekst[10],sizeof KaartFiche.naam);
    dsptekst[SpaceZeros(dsptekst,50)]='\0';
    disp_vid(0,2,dsptekst,0);
    zeros(dsptekst,sizeof dsptekst);
    bcopy("Straat  : ",&dsptekst[0],10);
    bcopy(KaartFiche.straat,&dsptekst[10],sizeof KaartFiche.straat);
    dsptekst[SpaceZeros(dsptekst,50)]='\0';
    disp_vid(0,3,dsptekst,0);
    zeros(dsptekst,sizeof dsptekst);
    bcopy("Gemeente: ",&dsptekst[0],10);
    bcopy(KaartFiche.postnr,&dsptekst[10],6);bcopy(KaartFiche.gemeente,&dsptekst[18+7],sizeof KaartFiche.gemeente);
    dsptekst[SpaceZeros(dsptekst,50)]='\0';
    disp_vid(0,4,dsptekst,0);
    zeros(dsptekst,sizeof dsptekst);
    bcopy("Telefoon: ",&dsptekst[0],10);
    bcopy(KaartFiche.telefoon,&dsptekst[10],sizeof KaartFiche.telefoon);
    dsptekst[SpaceZeros(dsptekst,50)]='\0';
    disp_vid(0,5,dsptekst,0);
    z=1;
    
    scrifld(z++,fm_us40,BestelInfo.Opmerking[0]);
    scrifld(z++,fm_us40,BestelInfo.Opmerking[1]);
    scrifld(z++,fm_us40,BestelInfo.Opmerking[2]);
    scrifld(z++,fm_us40,BestelInfo.Opmerking[3]);
    DisplayKalender(50,1,dt_eerste,date_,uur_,dt_nu_);
    disp_ikey(0,15,20,2,106,"annuleer",KLEUR_FTOETS);
    disp_ikey(20,15,20,2,108,"neem aan",KLEUR_FTOETS);
    DisplayKeyboard(0,17,0,0,KeyboardType);
    key=scrupd(1,0xA0);
    if (key&0xFFFF0000) key/=0x10000;
    if(key==106) return 0;
    if(key==102){
      mm--; if(mm<1) {mm=12; jj--;}
      dt_eerste=datejd(jj,mm,1); 
    }
    if(key==103){
      mm++; if(mm>12) {mm=1; jj++;}
      dt_eerste=datejd(jj,mm,1); 
    }
    if(key>=5001 && key<=5031) date_=dt_eerste+key-5001;
    if(key>=5100 && key<=5124) uur_=key-5100;
    DateUur2String(BestelInfo.AfhaalDatum,date_,uur_);  
    if(key==108){
      if(date_>0) break;
      ConMessageBox(_T("Geen afhaaldatum ingevuld !"),_T("Ingeven bestelling"),MB_OK |  MB_ICONEXCLAMATION |MB_ICONWARNING);
    }
  }
  if(nieuwe_bestelling_==false){
    Xml2Ticket();return 1;
  }
  else return 2;
}

static void DisplayKalender(int xpos_,int ypos_,unsigned int dt_eerste_,unsigned int inqdate_,int inquur_,unsigned int dt_min_)
{
  char buf_[30];
  int i, dagen, lijn, dg, x, y,mm1_,jj1_;
	short jj,mm,dd;
  CString cstr_,dt_str_;
  unsigned dt_nu_, jd_eerste, jd_volgende;
  SYSTEMTIME st;
  COLORREF kleur_;
   

  GetLocalTime(&st);
  dt_nu_=datejd((int)st.wYear%100,(int)st.wMonth,(int)st.wDay);
  if(dt_eerste_==0) jd_eerste=dt_nu_;  
  
  jddate(dt_eerste_,&jj,&mm,&dd);
  mm1_=mm;jj1_=jj;dt_eerste_=datejd(jj1_,mm1_,1); 
  disp_panel(xpos_,ypos_,21,2,0,KLEUR_TITEL);
  dg=(dt_eerste_+2)%7;buf_[0]=' ';
  bcopy(txtmnd[mm1_-1],&buf_[1],3); bcopy(". ",&buf_[4],2);
  int2str(jj1_,&buf_[6],4); buf_[10]=' '; buf_[11]=0;
  disp_vid(xpos_+5,ypos_,buf_,0); 
  disp_vid(xpos_,ypos_+1,"Ma Di Wo Do Vr Za Zo ",0); 
  lijn=ypos_+2;
  mm=mm1_+1; jj=jj1_;if (mm>12) {mm-=12; jj++;}
  jd_volgende=datejd(jj,mm,1);
  dagen=jd_volgende-dt_eerste_; buf_[2]=0;
  for (i=1; i<=dagen; i++) {
    int2str(i,buf_,2);
    x=xpos_+dg*3; y=lijn;
    if(dg==5 || dg==6) kleur_=KLEUR_OUDROOD; else kleur_=KLEUR_GROEN;
    if((dt_eerste_+i-1)==dt_nu_) kleur_=KLEUR_GEEL;
    if((dt_eerste_+i-1)==inqdate_) kleur_=KLEUR_ROOD;
    if((dt_eerste_+i-1)>=dt_min_)disp_ikey(x,y,3,2,5000+i,buf_,kleur_);
    else { disp_panel(x,y,3,2,0,KLEUR_TITEL);disp_vid(x,y,buf_,0);}
    if (++dg==7) {dg=0; lijn+=2;} 
  }
  for(i=6;i<20;i++){
    int2str(i,buf_,-2);bcopy(":00",&buf_[2],3);buf_[5]=0;
    if(inquur_==i) kleur_=KLEUR_ROOD; else kleur_=KLEUR_GROEN;
    disp_ikey(xpos_+22,ypos_+i-5,8,1,5100+i,buf_,kleur_);
  }
  disp_ikey(xpos_,ypos_,4,1,102,"<<",KLEUR_FTOETS);
  disp_ikey(xpos_+17,ypos_,4,1,103,">>",KLEUR_FTOETS);
}

void CKasKRT::MenuBestelLijsten(void)
{

  int i,n, key,ScreenLines=18,dagen, lijn, dg, x, y,xpos_,ypos_;
	short jj,mm,dd,jj1_,mm1_;
  bool lijst_printed_=false;
  unsigned int date_,dt_nu_,dt_eerste_,dt_volgende_;
  char buf_[30],dsptekst[100];
  CString cstr_,dt_str_;
  SYSTEMTIME st;
  COLORREF kleur_;


  ConStyle(0);
 
  if(MakeAllBestXml(0)==0) goto endsr;
  SortBestTab(1); // volgens datum
  TbSelectedDays.RemoveAll();TbSelectedDays.FreeExtra();MaxSelectedDays=0;


  GetLocalTime(&st);
  dt_nu_=datejd((int)st.wYear%100,(int)st.wMonth,(int)st.wDay);
  dt_eerste_=dt_nu_; jddate(dt_eerste_,&jj1_,&mm1_,&dd); dt_eerste_=datejd(jj1_,mm1_,1); 
  xpos_=0; ypos_=1;
  FOREVER{
    cls();scrnum=0;scrget(2,1500);
    disp_panel(0,0,80,1,0,KLEUR_TITEL);
    zeros(dsptekst,sizeof dsptekst);
    bcopy("Afdrukken diverse bestellijsten",&dsptekst[20],31);
    int2str(MaxTbBest,&dsptekst[60],3); bcopy(" bestellingen",&dsptekst[63],13);
    dsptekst[SpaceZeros(dsptekst,79)]='\0';
    disp_vid(0,0,dsptekst,0);
                                                                   // kalender 
    disp_panel(xpos_,ypos_,21,2,0,KLEUR_TITEL);
    dg=(dt_eerste_+2)%7;buf_[0]=' ';
    bcopy(txtmnd[mm1_-1],&buf_[1],3); bcopy(". ",&buf_[4],2);
    int2str(jj1_,&buf_[6],4); buf_[10]=' '; buf_[11]=0;
    disp_vid(xpos_+5,ypos_,buf_,0); 
    disp_vid(xpos_,ypos_+1,"Ma Di Wo Do Vr Za Zo ",0); 
    lijn=ypos_+2;
    mm=mm1_+1; jj=jj1_;if (mm>12) {mm-=12; jj++;}
    dt_volgende_=datejd(jj,mm,1);
    dagen=dt_volgende_-dt_eerste_; buf_[2]=0;
    for (i=1; i<=dagen; i++) {
      int2str(i,buf_,2);
      x=xpos_+dg*3; y=lijn;
      cstr_=Date2String((dt_eerste_+i-1),2);dt_str_=cstr_.Mid(4,4);dt_str_+=cstr_.Mid(2,2)+cstr_.Mid(0,2);
      for(n=0;n<MaxTbBest;n++){
				cstr_=TbBestDateString.GetAt(n);
				if(dt_str_==cstr_.Left(8)) break;
      }
      if(n>=MaxTbBest){
				if((dt_eerste_+i-1)==dt_nu_) kleur_=KLEUR_GEEL; else kleur_=KLEUR_TITEL;
				disp_panel(x,y,3,2,0,kleur_);disp_vid(x,y,buf_,0);
      }
      else{
        if(dg==5 || dg==6) kleur_=KLEUR_OUDROOD; else kleur_=KLEUR_GROEN;
        if((dt_eerste_+i-1)==dt_nu_) kleur_=KLEUR_GEEL;
        for(n=0;n<MaxSelectedDays;n++) if((dt_eerste_+i-1)==TbSelectedDays.GetAt(n)) break;
				if(n<MaxSelectedDays) kleur_=KLEUR_ROOD;
        disp_ikey(x,y,3,2,5000+i,buf_,kleur_);
      }
      if (++dg==7) {dg=0; lijn+=2;} 
    }
    disp_ikey(xpos_,ypos_,4,1,102,"<<",KLEUR_FTOETS);
    disp_ikey(xpos_+17,ypos_,4,1,103,">>",KLEUR_FTOETS);
                                                                  // einde kalender 
    kleur_=KLEUR_ROOD; if(MaxSelectedDays>0) kleur_=KLEUR_GROEN;
    disp_panel(30,2,26,1,0,kleur_);
    zeros(dsptekst,sizeof dsptekst); bcopy("Geselecteerde dagen :",dsptekst,21);int2str(MaxSelectedDays,&dsptekst[21],3);
    disp_vid(31,2,dsptekst,0);
    disp_ikey(59,2,19,2,5000,"wis selecties",KLEUR_FTOETS);
    kleur_=KLEUR_ROOD; if(MaxSelectedDays>0) kleur_=KLEUR_FTOETS;
    disp_ikey(30,5,49,2,5200,"Druk totalen per artikel",kleur_);
    disp_ikey(30,7,49,2,5201,"Druk ticketten",kleur_);
    disp_ikey(30,9,49,2,5202,"Druk lijst bestellingen",kleur_);
    disp_ikey(0,14,20,2,101,"stop",KLEUR_FTOETS);
    key=scrupd(-1,0x81);
    if (key&0xFFFF0000) key/=0x10000;
    if(key==101) break;
    if(key==102){
      mm1_--; if(mm1_<1) {mm1_=12; jj1_--;}
      dt_eerste_=datejd(jj1_,mm1_,1); 
    }
    if(key==103){
      mm1_++; if(mm1_>12) {mm1_=1; jj1_++;}
      dt_eerste_=datejd(jj1_,mm1_,1); 
    }
    if(key==5000){
      TbSelectedDays.RemoveAll();TbSelectedDays.FreeExtra();MaxSelectedDays=0;
    }
    if(key>=5001 && key<=5031){
      date_=dt_eerste_+key-5001;
      for(n=0;n<MaxSelectedDays;n++) if(date_==TbSelectedDays.GetAt(n)) break;
      if(n<MaxSelectedDays){
				TbSelectedDays.RemoveAt(n,1);MaxSelectedDays=TbSelectedDays.GetSize();
      }
      else {
				TbSelectedDays.Add(date_);MaxSelectedDays=TbSelectedDays.GetSize();
      }
    }
    if(key>=5200 && key<=5202 && MaxSelectedDays>0){
      if(key==5200) PrintArtikelCumuul();
      if(key==5201) PrintPickBestelTicketten();
      if(key==5202) PrintLijstBestelTicketten();
      lijst_printed_=true;
    }
    if(key==101) break;
  }
  if(lijst_printed_) {prt_hoofd(YES);prt_close();}
endsr:;
}

void CKasKRT::PrintArtikelCumuul(void)
{
  int j,k,grp_,nI,nJ,last_grp_,q_bons_;
  char code_[20],prtbuf_[50];
  unsigned int dt_,ix_;
  double aantal_,grp_aantal_,tot_aantal_;
  CString cstr_,str_aantal_;
  CUIntArray TbArtGrp,TbArtIx,TbArtBons;
  CStringArray  TbArtAantal; // als string owv double-getallen
  int MaxTbArt;
  CMarkup bonxml_;
// 2=bold on, 8=bold off, 3=elong on, 4=elong off, 5=underl on, 6=underl off 

  disp_panel(0,vdmax_v-5,80,2,0,KLEUR_GEEL);  // geel vlak 
  disp_vid(4,vdmax_v-4,"Bezig met afdrukken.  Even geduld...",0x12);
  kbcharnw();

  TbArtGrp.RemoveAll();TbArtGrp.FreeExtra();
  TbArtIx.RemoveAll();TbArtIx.FreeExtra();
  TbArtAantal.RemoveAll();TbArtAantal.FreeExtra();
  TbArtBons.RemoveAll();TbArtBons.FreeExtra();
  MaxTbArt=0;

  for(k=0;k<kasplu.art_used;k++){
    ix_=kasplu.SortIndex[1][k];
    TbArtIx.Add(ix_);TbArtGrp.Add(kasplu.artikel[ix_].groep);TbArtBons.Add(0);TbArtAantal.Add("0");MaxTbArt++;
  }
  for(nI=0;nI<MaxTbBest;nI++){
     cstr_=TbBestDateString.GetAt(nI).Left(8);
     dt_=String2Date(cstr_,"JJJJMMDD");
     for(k=0;k<MaxSelectedDays;k++) if(dt_==TbSelectedDays.GetAt(k)) break;
     if(k<MaxSelectedDays){
        AllBestXml.GotoElemIndex(TbBestXmlPos.GetAt(nI));
				AllBestXml.IntoElem();
        AllBestXml.ResetMainPos();
				if(AllBestXml.FindElem("FILENAME")==false) continue;
				cstr_=AllBestXml.GetData();
        if(bonxml_.Load(cstr_)==false) continue;
        bonxml_.FindElem("BESTELLING"); bonxml_.IntoElem();
				bonxml_.ResetMainPos();
				FOREVER{
					if(bonxml_.FindElem("ITEM")==false) break;
					bonxml_.IntoElem();
					bonxml_.ResetMainPos();bonxml_.FindElem("GROEP");grp_=String2Int(bonxml_.GetData());
          bonxml_.ResetMainPos();bonxml_.FindElem("KODE");Zcstr2arr(bonxml_.GetData(),code_,10);
          bonxml_.ResetMainPos();bonxml_.FindElem("AANTAL");aantal_=String2Int(bonxml_.GetData());
					if(grp_>=1 && grp_<=999){
						ix_=kasplu.find_plu(code_);
						for(j=0;j<MaxTbArt;j++) if(TbArtIx.GetAt(j)==ix_) break;
						if(j<MaxTbArt){
							aantal_+=String2Double(TbArtAantal.GetAt(j));TbArtBons[j]+=1;
							cstr_=Double2String(aantal_,-1);TbArtAantal.SetAt(j,cstr_);
						}
					}
					bonxml_.OutOfElem();
				}
     }
  }
  for (nI=0; nI<MaxTbArt-1; ++nI ){ // sorteren op groep
    for (nJ=nI+1; nJ<MaxTbArt; ++nJ ){
      if ( TbArtGrp[nI] > TbArtGrp[nJ] ){
        grp_ = TbArtGrp[nI];ix_ = TbArtIx[nI];str_aantal_ = TbArtAantal[nI];q_bons_=TbArtBons[nI];
        TbArtGrp[nI] = TbArtGrp[nJ];TbArtIx[nI] = TbArtIx[nJ];TbArtAantal[nI] = TbArtAantal[nJ];TbArtBons[nI]=TbArtBons[nJ];
        TbArtGrp[nJ] = grp_;TbArtIx[nJ] = ix_;TbArtAantal[nJ] = str_aantal_;TbArtBons[nJ]=q_bons_;
      }
    }
  }
  

  PrintBstTitel("  Bestelde artikels","Aantal Omschrijving               (Bons)");
  last_grp_=-1; grp_aantal_=0; tot_aantal_=0;
  for(nI=0;nI<MaxTbArt;nI++){
    aantal_=String2Double(TbArtAantal[nI]); 
    if(aantal_==0) continue;
    grp_=TbArtGrp[nI]; ix_=TbArtIx[nI]; q_bons_=TbArtBons[nI];
    if(last_grp_!=grp_){
      if(last_grp_>=0){
				zeros(prtbuf_,sizeof prtbuf_);
        cstr_="      "; cstr_+=Double2String(grp_aantal_,-1);Zcstr2arr(cstr_.Right(5),prtbuf_,6);
        bcopy(" <-- Totaal ",&prtbuf_[6],11);bcopy(grp_info[last_grp_].naam,&prtbuf_[18],20);
				SpaceZeros(prtbuf_,40); prtbuf_[40]=0;
				prt_cod(2);prt_nl(prtbuf_);prt_cod(8);
      }
      prt_nl("");
      last_grp_=grp_;grp_aantal_=0;
      zeros(prtbuf_,sizeof prtbuf_);
      bcopy(grp_info[grp_].naam,prtbuf_,20);
      prt_cod(5);prt_cod(3); prt_nl(prtbuf_); prt_cod(6);prt_cod(4);
    }
    zeros(prtbuf_,sizeof prtbuf_);
    cstr_="      "; cstr_+=Double2String(aantal_,-6);Zcstr2arr(cstr_.Right(5),prtbuf_,6);
    sprintf(&prtbuf_[7],"%s",kasplu.artikel[ix_].naam); 
    sprintf(&prtbuf_[35],"(%3d)",q_bons_); SpaceZeros(prtbuf_,40); prtbuf_[40]=0;
 
    prt_nl(prtbuf_);
    grp_aantal_+=aantal_; tot_aantal_+=aantal_;
  }
  if(grp_aantal_ && last_grp_>0){
    zeros(prtbuf_,sizeof prtbuf_);
    cstr_="      "; cstr_+=Double2String(grp_aantal_,-1);Zcstr2arr(cstr_.Right(5),prtbuf_,6);
    bcopy(" <-- Totaal ",&prtbuf_[6],11);bcopy(grp_info[last_grp_].naam,&prtbuf_[18],20);
    SpaceZeros(prtbuf_,40); prtbuf_[40]=0;
    prt_cod(2);prt_nl(prtbuf_);prt_cod(8); 
  }


  zeros(prtbuf_,sizeof prtbuf_); for (k=0; k<40; k++) prtbuf_[k]='-'; prt_nl(prtbuf_);
  prt_cod(2); prt_cod(3);
  zeros(prtbuf_,sizeof prtbuf_); copynaam(txttxt[14],prtbuf_,8);
  cstr_="                  "; cstr_+=Double2String(tot_aantal_,-1);Zcstr2arr(cstr_.Right(10),&prtbuf_[8],11);
  SpaceZeros(prtbuf_,20); prtbuf_[20]=0; prt_nl(prtbuf_); prt_cod(4);
  
  prt_time();
  prt_close();
  TbArtGrp.RemoveAll();TbArtGrp.FreeExtra();
  TbArtIx.RemoveAll();TbArtIx.FreeExtra();
  TbArtAantal.RemoveAll();TbArtAantal.FreeExtra();
  TbArtBons.RemoveAll();TbArtBons.FreeExtra();
  MaxTbArt=0;

}

void  CKasKRT::PrintBstTitel(char *s, char *s2)
{
  char lijn[45];
  char cut_flag;
  int j;
	short jj,mm,dd;
 
  cut_flag=NO;
  prt_cod(0); j=0;
  FOREVER {
    _clr_text(lijn);
    if (j==2) copynaam(s,lijn,20);
    else if (j==3) {
      if(MaxSelectedDays==1){
        jddate(TbSelectedDays[0],&jj,&mm,&dd);
        int2str(dd,lijn+ 5, 2); lijn[ 7]='/';
        int2str(mm,lijn+ 8,-2); lijn[10]='/';
        int2str(jj,lijn+11,-4); lijn[20]=0;
      }
    }
    if (j>=2 && j<=4) {prt_cod(2); prt_cod(3); lijn[20]=0;}
    if (j==5) {copynaam(s2,lijn,40); prt_nlu(lijn);}
    else prt_nl(lijn);
    if (lijn[20]==0) prt_cod(4);
    cut_flag|=prt_cut(2+j++);
    if (j>=6 && cut_flag) break;
  }
}
  
void CKasKRT::PrintPickBestelTicketten(void)
{
  int j,k,grp_,nI,tb_ix_[500],ix_;
  char code_[20],lijn[50],cut_flag,prtbuf_[50];
  unsigned int dt_;
  double aantal_,tb_aantal_[500],tot_aantal_;
  CString cstr_,str_aantal_;
  CMarkup bonxml_;
 
  disp_panel(0,vdmax_v-5,80,2,0,KLEUR_GEEL);  // geel vlak 
  disp_vid(4,vdmax_v-4,"Bezig met afdrukken.  Even geduld...",0x12);
  kbcharnw();


  for(nI=0;nI<MaxTbBest;nI++){
     cstr_=TbBestDateString.GetAt(nI);
     dt_=String2Date(cstr_.Left(8),"JJJJMMDD");
     for(k=0;k<MaxSelectedDays;k++) if(dt_==TbSelectedDays.GetAt(k)) break;
     if(k>=MaxSelectedDays) goto next_bon;
     AllBestXml.GotoElemIndex(TbBestXmlPos.GetAt(nI));
     AllBestXml.IntoElem();
     AllBestXml.ResetMainPos();	if(AllBestXml.FindElem("FILENAME")==false) goto next_bon;
     cstr_=AllBestXml.GetData();
     if(bonxml_.Load(cstr_)==false) goto next_bon;
     bonxml_.ResetPos();bonxml_.FindElem("BESTELLING"); bonxml_.IntoElem();
     zeros(&KaartFiche,sizeof KaartFiche);zeros(&BestelInfo,sizeof BestelInfo);
     bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("KLANTNR");
     if(cstr_.GetLength()) FGetKaart(String2Int(cstr_));
     bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMAAKDATUM");
     if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.OpmaakDatum,30);
     bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("AFHAALDATUM");
     if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.AfhaalDatum,30);
     bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMERK1");
     if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.Opmerking[0],40);
     bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMERK2");
     if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.Opmerking[1],40);
     bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMERK3");
     if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.Opmerking[2],40);
     bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMERK4");
     if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.Opmerking[3],40);
     for(k=0;k<500;k++){tb_ix_[k]=-1;tb_aantal_[k]=0;}
     bonxml_.ResetMainPos();tot_aantal_=0;
     FOREVER{
       if(bonxml_.FindElem("ITEM")==false) break;
       bonxml_.IntoElem();
       bonxml_.ResetMainPos();bonxml_.FindElem("GROEP");grp_=String2Int(bonxml_.GetData());
       bonxml_.ResetMainPos();bonxml_.FindElem("KODE");Zcstr2arr(bonxml_.GetData(),code_,10);
       bonxml_.ResetMainPos();bonxml_.FindElem("AANTAL");aantal_=String2Int(bonxml_.GetData());
       if(grp_>=1 && grp_<=999){
         ix_=kasplu.find_plu(code_);
			   if(ix_>=0) {
           for(j=0;j<500-1;j++) if(tb_ix_[j]==ix_ || tb_ix_[j]==-1) break;
				   tb_ix_[j]=ix_;tb_aantal_[j]+=aantal_;tot_aantal_+=aantal_;
				 }
			 }
       bonxml_.OutOfElem();
     }


     cut_flag=NO; 
     prt_cod(0); j=0;
     FOREVER {
       _clr_text(lijn);
       switch(j){
       case 2  : bcopy("     BESTELLING",lijn,15); break;
       case 3  : bcopy("  ",lijn,2);bcopy(BestelInfo.AfhaalDatum,&lijn[2],20);break;
  //     case 5  : bcopy(KaartFiche.code,lijn,10);break;
       case 5  : bcopy(KaartFiche.naam,lijn,35);break;
       case 6  : bcopy(KaartFiche.straat,lijn,30);break;
       case 7  : bcopy(KaartFiche.postnr,lijn,6);bcopy(KaartFiche.gemeente,&lijn[8],25);
                 SpaceZeros(lijn,40);
		 break;
       case 8  : bcopy("Telefoon : ",lijn,11);bcopy(KaartFiche.telefoon,&lijn[11],15);
                 SpaceZeros(lijn,40);break;
       case 10:  bcopy("Aantal Omschrijving",lijn,19); break;
       default : break;
       }
       if (j>=2 && j<=3) {prt_cod(2); prt_cod(3); lijn[20]=0;}
       if (j==10) prt_nlu(lijn); else prt_nl(lijn);
       if (j<5 && lijn[20]==0) prt_cod(4);
       cut_flag|=prt_cut(2+j++);
       if (j>=11 && cut_flag) break;
     }
  
     tot_aantal_=0;
     for(k=0;k<kasplu.art_used;k++){
       for(j=0;j<500;j++) if(tb_ix_[j]>=0 && tb_ix_[j]==kasplu.SortIndex[1][k]) break;
       if(j<500){
         zeros(lijn,sizeof lijn);
				 cstr_="      "; cstr_+=Double2String(tb_aantal_[j],-1);Zcstr2arr(cstr_.Right(5),lijn,6);
         sprintf(&lijn[7],"%s",kasplu.artikel[tb_ix_[j]].naam); 
         SpaceZeros(lijn,40); lijn[40]=0;prt_nl(lijn);
         tot_aantal_+=tb_aantal_[j];
       }
     }
     prt_nl("");
     for(k=0;k<4;k++) if(BestelInfo.Opmerking[k][0]) prt_nl(BestelInfo.Opmerking[k]);
     zeros(prtbuf_,sizeof prtbuf_); for (k=0; k<40; k++) prtbuf_[k]='-'; prt_nl(prtbuf_);
     prt_cod(2); prt_cod(3);
     zeros(prtbuf_,sizeof prtbuf_); copynaam(txttxt[14],prtbuf_,8);
     cstr_="                  "; cstr_+=Double2String(tot_aantal_,-1);Zcstr2arr(cstr_.Right(10),&prtbuf_[8],11);
     SpaceZeros(prtbuf_,20); prtbuf_[20]=0; prt_nl(prtbuf_); prt_cod(4);
     prt_time();
     prt_close();

next_bon:;
  }
}

void CKasKRT::PrintLijstBestelTicketten(void)
{
  int k,nI,uur_;
  char prtbuf_[50];
  unsigned int dt_;
  double tot_aantal_;
  CString cstr_;
  CMarkup bonxml_;
 
  disp_panel(0,vdmax_v-5,80,2,0,KLEUR_GEEL);  // geel vlak 
  disp_vid(4,vdmax_v-4,"Bezig met afdrukken.  Even geduld...",0x12);
  kbcharnw();
  
  zeros(prtbuf_,sizeof prtbuf_);
  if(MaxSelectedDays==1) bcopy(" Uur  Klant",prtbuf_,16);
  else bcopy("  Datum/uur      Klant",prtbuf_,25);
  PrintBstTitel(" Lijst bestellingen",prtbuf_);
  tot_aantal_=0;
  for(nI=0;nI<MaxTbBest;nI++){
    cstr_=TbBestDateString.GetAt(nI);
    dt_=String2Date(cstr_.Left(8),"JJJJMMDD");
    for(k=0;k<MaxSelectedDays;k++) if(dt_==TbSelectedDays.GetAt(k)) break;
    if(k>=MaxSelectedDays) goto next_bon;
    AllBestXml.GotoElemIndex(TbBestXmlPos.GetAt(nI));
    AllBestXml.IntoElem();
    AllBestXml.ResetMainPos();	if(AllBestXml.FindElem("FILENAME")==false) goto next_bon;
    cstr_=AllBestXml.GetData();
    if(bonxml_.Load(cstr_)==false) goto next_bon;
    bonxml_.ResetPos();bonxml_.FindElem("BESTELLING"); bonxml_.IntoElem();
    zeros(&KaartFiche,sizeof KaartFiche);zeros(&BestelInfo,sizeof BestelInfo);
    bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("KLANTNR");
    if(cstr_.GetLength()) FGetKaart(String2Int(cstr_));
    bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("OPMAAKDATUM");
    if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.OpmaakDatum,30);
    bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("AFHAALDATUM");
    if(cstr_.GetLength()) Zcstr2arr(cstr_,BestelInfo.AfhaalDatum,30);
    String2DateUur(BestelInfo.AfhaalDatum,&dt_,&uur_);
    zeros(prtbuf_,sizeof prtbuf_);
    if(MaxSelectedDays==1){
      int2str(uur_,prtbuf_,-2); bcopy(":00 ",&prtbuf_[2],4);
      bcopy(KaartFiche.naam,&prtbuf_[6],32);
    }
    else {
      bcopy(BestelInfo.AfhaalDatum,prtbuf_,16); prtbuf_[16]=' ';
      bcopy(KaartFiche.naam,&prtbuf_[17],23);
    }
    prt_nl(prtbuf_);tot_aantal_++;
next_bon:;
  }
  zeros(prtbuf_,sizeof prtbuf_); for (k=0; k<40; k++) prtbuf_[k]='-'; prt_nl(prtbuf_);
  prt_cod(2); prt_cod(3);
  zeros(prtbuf_,sizeof prtbuf_); copynaam(txttxt[14],prtbuf_,8);
  cstr_="                  "; cstr_+=Double2String(tot_aantal_,-1);Zcstr2arr(cstr_.Right(10),&prtbuf_[8],11);
  SpaceZeros(prtbuf_,20); prtbuf_[20]=0; prt_nl(prtbuf_); prt_cod(4);
  prt_time();
  prt_close();
}



bool CKasKRT::AdjustTicketAndSaveToXml(void)
{
  int k,p_used_,uur_;
  char buf_[100];
  unsigned int date_;
    
  if(Ticket2Xml()==false) return false;

  p_used_=p_vrk->used;
  for(k=p_used_-1;k>=0;k--) bcopy((char *)&p_vrk->lijn[k],(char *)&p_vrk->lijn[k+10],sizeof p_vrk->lijn[0]); // 10 lijnen opschuiven
  for(k=0;k<10;k++) zeros((char *)&p_vrk->lijn[k],sizeof p_vrk->lijn[0]); // 10 lijnen wissen 

  p_vrk->used=0;   // tekstlijnen vooraan toevoegen 
  p_lin=&p_vrk->lijn[p_vrk->used];
  add_text("");
  add_text("-------- ***** BESTELLING ***** --------");
  add_text(KaartFiche.code);
  add_text(KaartFiche.naam);
  add_text(KaartFiche.straat);
  add_text(KaartFiche.postnr);bcopy(KaartFiche.gemeente,&p_vrk->lijn[p_vrk->used-1].text[7],25);
  add_text("Telefoon : ");bcopy(KaartFiche.telefoon,&p_vrk->lijn[p_vrk->used-1].text[11],15);
  add_text("");
  zeros(buf_,sizeof buf_);
  bcopy("Afhaling : ",buf_,11);
  String2DateUur(BestelInfo.AfhaalDatum,&date_,&uur_); if(date_) datefm(&buf_[11],date_,14);
  if(uur_){buf_[32]='(';int2str(uur_,&buf_[33],-2);bcopy(":00h)",&buf_[35],5);}
  SpaceZeros(buf_,40);
  add_text(buf_);
  add_text("----------------------------------------");
  p_vrk->used=p_used_+10;  p_lin=&p_vrk->lijn[p_vrk->used];// pointer juistzetten 
  return true;
}


bool CKasKRT::MakeVoorschotTicket(void)
{
  int i,n;
 char DelFlag;
    
  for (i=10;i<p_vrk->used;i++){ // alle artikels wissen 
    p_lin= &p_vrk->lijn[i];
    DelFlag=NO;
    if((p_lin->groep<1010 && p_lin->groep!=GRP_VOORSCHOT_B && p_lin->groep!=GRP_TERUG)) DelFlag=YES;
    if(p_lin->groep==GRP_VOORSCHOT_R) DelFlag=YES;
    if(p_lin->groep==GRP_TEXT && cmpstr(p_lin->text,"   *** Bestelling ",18)==0) DelFlag=YES;
    if (DelFlag) {
      for(n=i+1;n<p_vrk->used;n++) bcopy((char *)&p_vrk->lijn[n],(char *)&p_vrk->lijn[n-1],sizeof p_vrk->lijn[0]);
      if(p_vrk->used>0) zeros((char *)&p_vrk->lijn[p_vrk->used-1],sizeof p_vrk->lijn[0]);
      p_vrk->used--;i--;
    }
  }
  bcopy("--- Betaald voorschot bij bestelling ---",p_vrk->lijn[1].text,40);
  if (p_vrk->used==10) p_vrk->used=0;
  return true;
}

bool CKasKRT::Ticket2Xml(void)
{
  int i,grp_;
  double aantal_,prijs_,totaal_;
  CString code_;
  CMarkup bonxml_;
    
  bonxml_.SetDoc("");bonxml_.AddElem("BESTELLING");bonxml_.IntoElem();
  bonxml_.AddElem("FILENAME",BestelInfo.FileNameXml);
  bonxml_.AddElem("KLANTNR",KaartFiche.code);
  bonxml_.AddElem("OPMAAKDATUM",BestelInfo.OpmaakDatum);
  bonxml_.AddElem("AFHAALDATUM",BestelInfo.AfhaalDatum);
  bonxml_.AddElem("OPMERK1",BestelInfo.Opmerking[0]);
  bonxml_.AddElem("OPMERK2",BestelInfo.Opmerking[1]);
  bonxml_.AddElem("OPMERK3",BestelInfo.Opmerking[2]);
  bonxml_.AddElem("OPMERK4",BestelInfo.Opmerking[3]);
  for (i=0;i<p_vrk->used;i++){
    p_lin= &p_vrk->lijn[i];
    if (p_lin->bits & AUTO_LEEG) continue;
    if ((p_lin->groep>=-9 && p_lin->groep<=999) || 
                  p_lin->groep==GRP_SUBTOT || p_lin->groep==GRP_VOORSCHOT_R || p_lin->groep==GRP_VOORSCHOT_B) {
      bonxml_.AddElem("ITEM");
      bonxml_.IntoElem();
        aantal_=p_lin->aantal;grp_=p_lin->groep; code_=CString(p_lin->code);prijs_=p_lin->prijs;totaal_=p_lin->totaal;
        bonxml_.AddElem("KODE",code_);
        bonxml_.AddElem("AANTAL",Double2String(aantal_,-1));
        bonxml_.AddElem("PRIJS",Double2String(prijs_,-1));
	if(grp_==GRP_VOORSCHOT_R){
	  grp_=GRP_VOORSCHOT_B;totaal_=-totaal_;
	  bonxml_.AddElem("TOTAAL",Double2String(totaal_,-1));
          bonxml_.AddElem("GROEP",grp_);
	}
	else{
	  bonxml_.AddElem("TOTAAL",Double2String(totaal_,-1));
          bonxml_.AddElem("GROEP",grp_);
	}
	bonxml_.OutOfElem();
    }
  }
  if(bonxml_.Save(BestelInfo.FileNameXml)==false){
    ConMessageBox(_T("Kan de bestelling NIET wegschrijven!"),_T("Opslaan bestelling"),MB_OK |  MB_ICONEXCLAMATION |MB_ICONWARNING);
    return false;
  }
  bcopy(&BestelInfo,&LastLoadedBestelInfo[vrk_ix],sizeof BestelInfo);
  return true;
}

void CKasKRT::Xml2Ticket(void)
{
  int i,len_,grp_,leegsave_,stukssave_;
  char buf_[100];
  double aantal_,prijs_,totaal_;
  CString cstr_,code_;
  CMarkup bonxml_;

  leegsave_=p_vrk->leeg_flag;
  stukssave_=p_vrk->stuks_flag;

  if(bonxml_.Load(BestelInfo.FileNameXml)==false){
    ConMessageBox(_T("Kan de bestelling NIET lezen!"),_T("Inlezen bestelling"),MB_OK |  MB_ICONEXCLAMATION |MB_ICONWARNING);
    goto endsr;
  }
  bonxml_.ResetMainPos();
  bonxml_.FindElem("BESTELLING"); bonxml_.IntoElem();
  bonxml_.ResetMainPos();bonxml_.FindElem("OPMAAKDATUM");cstr_=bonxml_.GetData();
  zeros(buf_,sizeof buf_);
  bcopy("   *** Bestelling ",buf_,18); 
  if(cstr_.GetLength()) len_=cstr2arr(cstr_,&buf_[18],16);bcopy(" ***",&buf_[18+len_],4);
  p_lin=&p_vrk->lijn[p_vrk->used];
  add_text(buf_);
  bonxml_.ResetMainPos();

  FOREVER{
    if(bonxml_.FindElem("ITEM")==false) break;
    bonxml_.IntoElem();
      bonxml_.ResetMainPos();bonxml_.FindElem("KODE"); code_=bonxml_.GetData();
      bonxml_.ResetMainPos();bonxml_.FindElem("GROEP"); grp_=String2Int(bonxml_.GetData());
      bonxml_.ResetMainPos();bonxml_.FindElem("AANTAL"); aantal_=String2Double(bonxml_.GetData());
      bonxml_.ResetMainPos();bonxml_.FindElem("PRIJS"); prijs_=String2Double(bonxml_.GetData());
      bonxml_.ResetMainPos();bonxml_.FindElem("TOTAAL"); totaal_=String2Double(bonxml_.GetData());
      if(grp_>=1 && grp_<=999){
        i=code_.GetLength(); if(i> ARTCODE_LEN) i=ARTCODE_LEN;
        if (i>0) cstr2arr(code_,regalfa,i);
        regix=i; regalfa[i]=0;
        reg_aantal=aantal_;
        plu(1);
      }
      else if(grp_==GRP_FKORT){
        reg_aantal=prijs_;korting(0);
      }
      else if(grp_==GRP_PKORT){
        reg_aantal=prijs_;korting(1);
      }
      else if(grp_==GRP_SUBTOT){
        subtotaal(0);
      }
      else if(grp_==GRP_VOORSCHOT_B){
			  p_lin=&p_vrk->lijn[p_vrk->used];
		    p_lin->groep=GRP_VOORSCHOT_R;
        p_lin->totaal=-totaal_;
        adj_lijn(p_vrk->used++); art_calc(NO);
      }
      bonxml_.OutOfElem();
  }

  remove(BestelInfo.FileNameXml);
  bcopy(&BestelInfo,&LastLoadedBestelInfo[vrk_ix],sizeof BestelInfo);
endsr:;
  p_vrk->leeg_flag=leegsave_;
  p_vrk->stuks_flag=stukssave_;
}
 
static void String2DateUur(char *ps_,unsigned int *jdt_,int *uur_)
{
  int jj, mm, dd;
  CString dt_str_;
 
  dt_str_=CString(ps_);
  if(dt_str_.GetLength()>=10){
    dd=String2Int(dt_str_.Mid(0,2));
    mm=String2Int(dt_str_.Mid(3,2));
    jj=String2Int(dt_str_.Mid(8,2));
    *jdt_=datejd(jj,mm,dd);
  } else *jdt_=0;
  if(dt_str_.GetLength()>=13){
    *uur_=String2Int(dt_str_.Mid(11,2));if(*uur_<0 || *uur_>24) *uur_=0;
  } else *uur_=0;
}
  
static void DateUur2String(char *ps_,unsigned int jdt_,int uur_)
{
 
  if(jdt_) datefm(ps_,jdt_,3);
  else bcopy("  /  /    ",ps_,10);
  ps_+=10;*ps_++='-';
  stcli_d(ps_,(long)uur_,2,0);ps_+=2; bcopy(":00",ps_,3);
}


int CKasKRT::MakeAllBestXml(int inq_kltrec_) // 0 = geen selectie
{

  int  jobcount,krec_,xml_ix_;
  CString cstr_,datestr_,bonfile_,sectordir_,bondir_,wildcard_;
  CMarkup bonxml_;
  WIN32_FIND_DATA BonData;   // Data structure describes the file found
  HANDLE hBon;             // Search handle returned by FindFirstFile
  bool first_=true;
 
  TbBestXmlPos.RemoveAll();TbBestXmlPos.FreeExtra();
  TbBestKlantNr.RemoveAll();TbBestKlantNr.FreeExtra();
  TbBestDateString.RemoveAll();TbBestDateString.FreeExtra();
  MaxTbBest=0;

//  InfoSetup(20,10,40,5); InfoCls();
//InfoShow();
//InfoHide();
  AllBestXml.SetDoc("");AllBestXml.AddElem("ALLBEST");AllBestXml.IntoElem();
 
  jobcount=0;
  bondir_=""; wildcard_="B00-*.XML";cstr_=bondir_; cstr_+=wildcard_;
  hBon = FindFirstFile (cstr_, &BonData);
  FOREVER{
    if (hBon == INVALID_HANDLE_VALUE) break;
    if (!(BonData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){ // GEEN directory 
      bonfile_=bondir_; bonfile_+=BonData.cFileName;
//      dspbuffer[cstr2arr(bonfile_,dspbuffer,50)]='\0';InfoDisp(dspbuffer);InfoDisp("\r\n");
      bonxml_.SetDoc("");
      if(bonxml_.Load(bonfile_)){
        bonxml_.FindElem("BESTELLING"); 
        bonxml_.ResetChildPos(); 
        bonxml_.FindChildElem("KLANTNR");krec_=String2Int(bonxml_.GetChildData());
//	dt_=String2Int("0");
//        dt_=String2Date(bonxml_.GetChildData(),"JJJJMMDD");
        if(inq_kltrec_==0 || inq_kltrec_==krec_){
          //cstr_=bonxml_.GetElemContent();
          bonxml_.IntoElem();
	  AllBestXml.AddElem("ORDER");//AllBestXml.SetElemContent(cstr_);
      	  xml_ix_=AllBestXml.GetElemIndex();
          AllBestXml.IntoElem();AllBestXml.ResetMainPos();
	  AllBestXml.AddElem("FILENAME",bonfile_);
	  bonxml_.ResetMainPos();bonxml_.FindElem("KLANTNR");
	  cstr_=bonxml_.GetData();
	  AllBestXml.AddElem("KLANTNR",cstr_);
	  bonxml_.ResetMainPos();AllBestXml.AddElem("KLANTNAAM",bonxml_.FindGetData("KLANTNAAM"));
	  bonxml_.ResetMainPos();AllBestXml.AddElem("OPMAAKDATUM",bonxml_.FindGetData("OPMAAKDATUM"));
	  bonxml_.ResetMainPos();cstr_=bonxml_.FindGetData("AFHAALDATUM");
	  AllBestXml.AddElem("AFHAALDATUM",cstr_);
	  datestr_="";
          if(cstr_.GetLength()>=16){	    
            datestr_+=cstr_.Mid(6,4)+cstr_.Mid(3,2)+cstr_.Mid(0,2); //JJJJMMDD
            datestr_+=CString("-")+cstr_.Mid(11,2)+cstr_.Mid(14,2); //HHMM
          }
	  TbBestXmlPos.Add(xml_ix_);
	  TbBestKlantNr.Add(krec_);
	  TbBestDateString.Add(datestr_);
//	  bonxml_.ResetMainPos();AllBestXml.AddElem("AFHAALUUR",bonxml_.FindGetData("AFHAALUUR"));
          AllBestXml.OutOfElem();
          jobcount++;
	}
      }
    }
    if(FindNextFile (hBon, &BonData)==false) break;
  }
  FindClose(hBon);
  MaxTbBest=TbBestXmlPos.GetSize();
  SortBestTab(0);
 // InfoHide();
  return jobcount;
}

void CKasKRT::SortBestTab(int sortmode_) // 0 = klantnr, 1=datum
{
  CString sw_datestring_;
  int nI,nJ,sw_xmlpos_,sw_klantnr_;


  if(sortmode_==1){
    for (nI=0; nI<MaxTbBest-1; ++nI ){
      for (nJ=nI+1; nJ<MaxTbBest; ++nJ ){
        if ( TbBestDateString[nI] > TbBestDateString[nJ] ){
          sw_datestring_ = TbBestDateString[nI];
          TbBestDateString[nI] = TbBestDateString[nJ];
          TbBestDateString[nJ] = sw_datestring_;
          sw_klantnr_ = TbBestKlantNr[nI];
          TbBestKlantNr[nI] = TbBestKlantNr[nJ];
          TbBestKlantNr[nJ] = sw_klantnr_;
          sw_xmlpos_ = TbBestXmlPos[nI];
          TbBestXmlPos[nI] = TbBestXmlPos[nJ];
          TbBestXmlPos[nJ] = sw_xmlpos_;
	}
      }
    }
  }
  else{
    for (nI=0; nI<MaxTbBest-1; ++nI ){
      for (nJ=nI+1; nJ<MaxTbBest; ++nJ ){
        if ( TbBestKlantNr[nI] > TbBestKlantNr[nJ] ){
          sw_datestring_ = TbBestDateString[nI];
          TbBestDateString[nI] = TbBestDateString[nJ];
          TbBestDateString[nJ] = sw_datestring_;
          sw_klantnr_ = TbBestKlantNr[nI];
          TbBestKlantNr[nI] = TbBestKlantNr[nJ];
          TbBestKlantNr[nJ] = sw_klantnr_;
          sw_xmlpos_ = TbBestXmlPos[nI];
          TbBestXmlPos[nI] = TbBestXmlPos[nJ];
          TbBestXmlPos[nJ] = sw_xmlpos_;
	}
      }
    }
  }
         
}


bool CKasKRT::UpdateKaartFiche(int recordnr_)
{
  int k,key,z;
  
  ConStyle(0); // grijze achtergrond
  while(true){
redo:;
    scrnum=0;scrget(2,1502); z=1;
    scrifld(z++,fm_os10,KaartFiche.code);
    scrifld(z++,fm_us40,KaartFiche.naam);
    scrifld(z++,fm_us30,KaartFiche.straat);
    scrifld(z++,fm_us7,KaartFiche.postnr);
    scrifld(z++,fm_us25,KaartFiche.gemeente);
    scrifld(z++,fm_us15,KaartFiche.telefoon);
    disp_ikey(2,8,20,2,106,"annuleer",KLEUR_FTOETS);
    disp_ikey(22,8,20,2,108,"neem aan",KLEUR_FTOETS);
    disp_ikey(vdmax_h-13,8,10,2,110,"schrap",KLEUR_FTOETS);
    DisplayKeyboard(0,13,0,1,KeyboardType);
    key=scrupd(2,0xA0);
    if (key&0xFFFF0000) key/=0x10000;
    if(key==106) return false;
    if(key==110){
      if(HeeftBestelling(recordnr_)==true) goto redo;
      if(ConMessageBox(_T("Wenst U echt deze fiche te schrappen???"),_T("Schrappen klantenkaart"),MB_YESNO | MB_ICONQUESTION)==IDYES){
	return FKillKaart(recordnr_);
      }
    }
    k=KaartFiche.naam[0];
    if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;goto redo;}
    if(key==108) break;
  }
  return FUpdKaart(recordnr_);
}



void CKasKRT::ReloadKaartFile(void)
{
  int i, j, pos;
 
  if (krt_count==0) goto endsr;
  krtref=dopen("KASKRTNM.DAT",O_RDONLY|O_BINARY);
  if (krtref<0) goto endsr;
  p_krt=krtinfo;
  for (i=0; i<krt_used; i++) {
    rd_kltkrt(i);
    p_krt=&krtinfo[i];
    p_krt->nr=i+1;
    movmem(kaskrtnm.code,p_krt->code,sizeof(krtinfo[0].code));
    pos = copy2JAMASCIstring((unsigned char *)p_krt->naam,0,sizeof(p_krt->naam),(unsigned char *)kaskrtnm.naam,sizeof(kaskrtnm.naam));
    pos = copystring(p_krt->naam,pos,sizeof(p_krt->naam)," - ",-3);
    pos = copy2JAMASCIstring((unsigned char *)p_krt->naam,pos,sizeof(p_krt->naam),(unsigned char *)kaskrtnm.straat,sizeof(kaskrtnm.straat));
    pos = copystring(p_krt->naam,pos,sizeof(p_krt->naam)," - ",-3);
    pos = copy2JAMASCIstring((unsigned char *)p_krt->naam,pos,sizeof(p_krt->naam),(unsigned char *)kaskrtnm.gemeente,sizeof(kaskrtnm.gemeente));
    p_krt->naam[pos]=0;
    pos=0;
    for (j=0; j<sizeof(kaskrtnm.telefoon); j++) {
      if (pos==sizeof(p_krt->telefoon)) break;
      if (kaskrtnm.telefoon[j]>='0' && kaskrtnm.telefoon[j]<='9') p_krt->telefoon[pos++]=kaskrtnm.telefoon[j];
    }
    while (pos<sizeof(p_krt->telefoon)) p_krt->telefoon[pos++]=0;
  }
  sortkltkrt();
  dclose(krtref);
endsr:;
}

bool CKasKRT::FUpdKaart(int recnr_)
{

  int fref_;
  long pos_;
  char buf_[200];
    
  if(recnr_<1 || recnr_>krt_used) return false;
redo_open:; 
  fref_=dopen("KASKRTNM.DAT",RDWRMODE);
  if (fref_<0){
    if(ConMessageBox(_T("Probleem met wegschrijven!\nOpnieuw proberen?"),_T("Wegschrijven gegevens"),MB_YESNO | MB_ICONQUESTION)==IDYES) goto redo_open;
    else return false;
  }
  pos_ = (recnr_-1) * (long) sizeof(struct s_kaskrtnm);
  dseek(fref_,pos_,0);


  movmem(&KaartFiche,buf_,sizeof(struct s_kaskrtnm));
  JamaAsc2Asc(buf_,sizeof(struct s_kaskrtnm)); // naar ascii
  dwrite(fref_,buf_,sizeof(struct s_kaskrtnm));
  dclose(fref_);
  return true;
}

bool CKasKRT::FGetKaart(int recnr_)
{

  int fref_,len_;
  long pos_;
  char buf_[200];
    
  if(recnr_<1 || recnr_>krt_used) return false;
redo_open:; 
  fref_=dopen("KASKRTNM.DAT",O_RDONLY|O_BINARY);
  if (fref_<0){
    if(ConMessageBox(_T("Probleem met openen KASKRTNM.DAT!\nOpnieuw proberen?"),_T("Lezen gegevens"),MB_YESNO | MB_ICONQUESTION)==IDYES) goto redo_open;
    else return false;
  }
  pos_ = (recnr_-1) * (long) sizeof(struct s_kaskrtnm);
  dseek(fref_,pos_,0);
  len_=dread(fref_,buf_,sizeof(struct s_kaskrtnm));
  if(len_==sizeof(struct s_kaskrtnm)){
    Asc2JamaAsc(buf_,sizeof(struct s_kaskrtnm)); // naar Jama-ascii
    movmem(buf_,&KaartFiche,sizeof(struct s_kaskrtnm));
  } else len_=0;
  dclose(fref_);
  if(len_) return true; else return false;
}
  

bool CKasKRT::FKillKaart(int recnr_)
{

  int k;
  char buf_[200];

  if(recnr_<1 || recnr_>krt_used) return false;
  for(k=0;k<sizeof(struct s_kaskrtnm);k++) buf_[k]=' ';
  movmem(buf_,&KaartFiche,sizeof(struct s_kaskrtnm));
  stcli_d(buf_,(long)(recnr_+1),5,0);
  movmem(buf_,KaartFiche.code,5);
  movmem("XYZ",KaartFiche.naam,3);movmem(buf_,&KaartFiche.naam[3],5);
  return FUpdKaart(recnr_);
}



void CKasKRT::dsp_krtinfo(int type)
{
  char buf[50];
  int i, j,nr_;
   
	p_vrk->krtflag=true;
  if (krt_bits&8) {
    CString strNaam;
		if (!KassaTestConfigFlag && (JMD=::FindWindow("THE_JMD",NULL))==NULL) { //_T("THE_JMD") {
      strNaam="*** Server OFF-LINE";
    }
    else {
      CMarkup Xmlo;
      // <Status>10</Status>
      // <KrtNr>10</KrtNr>
      Xmlo.AddElem("Status",10); 
      Xmlo.AddElem("KrtNr",p_vrk->krtnr);
      if (type==1) {
        Xmlo.AddElem("RRNr",eID.nationalNumber);
      }
      else if (type==2) {
        Xmlo.AddElem("Naam",eID.name);
        Xmlo.AddElem("VNaam",eID.firstName1);
        Xmlo.AddElem("Straat",eIDaddr.street);
        Xmlo.AddElem("PostNr",eIDaddr.zip);
        Xmlo.AddElem("Stad",eIDaddr.municipality);
        Xmlo.AddElem("GebDat",eID.birthDate);
        Xmlo.AddElem("RRNr",eID.nationalNumber);
        Xmlo.AddElem("eIdNr",eID.cardNumber);
        Xmlo.AddElem("Sex",eID.sex);
      }
      else if (type==3) {
        // add niets -> zoek via keyboard en ZOEK
      }
      Xmlo.Save(JmcCmdFilepath);

      UpdateOnJMC();

			CMarkup Xml;
      for (i=0; i<5; i++) {
        Xml.Load(KasCmdFilepath);
				if (Xml.GetDoc().GetLength()>0) break;
        Sleep(100);
      }
      if (i==5) strNaam="*** Communicatiefout !";
      else {
        p_vrk->krtnr=atol(Xml.FindGetData("/Kaart/F1"));
        strNaam=Xml.FindGetData("/Kaart/F3");
        p_vrk->krtPunten=atol(Xml.FindGetData("/Kaart/F33"));
      }
    }
    if (strNaam.GetLength()==0) strNaam="*** GEEN kaartinfo !";
    if (strNaam.GetLength()>40) strNaam=strNaam.Left(40);
    sprintf(p_vrk->krtNaam,"%-40s", (char *)(LPCTSTR)strNaam);
  }
  else {
	  if(p_vrk->BestelKrtNr) nr_=p_vrk->BestelKrtNr; else nr_=p_vrk->krtnr;
	  for (j=0; j<krt_used; j++) if (krtinfo[j].nr==nr_) break;
	  for (i=0; i<40; i++) {
		  p_vrk->krtNaam[i]=krtinfo[j].naam[i];
		  if (p_vrk->krtNaam[i]==0) break;
	  }
	  p_vrk->krtNaam[i]=0;
  }
	i=p_vrk->used;
	if(p_vrk->used>1) p_vrk->used++;  // om laatste artikel lijn niet te overschrijven 
	disp_window();
	p_vrk->used=i;
	disp_fl=NO;
	disp_vid(0,2,"                                               ",0);
  strcpy(buf,p_vrk->krtNaam);
  buf[20]=0;
  disp_vid(19,2,buf,2);
	if (p_vrk->krtNaam[0]=='*' && p_vrk->krtNaam[1]=='*' && p_vrk->krtNaam[2]=='*') {
		p_vrk->krtNaam[0]=0;
		p_vrk->krtnr=0;
	}
}

void CKasKRT::prtkrtfull(int count)
{
  int j;
  char buf[41];
  
 // get_tijd();
  while (count-->0) {
    prt_hoofd(2); /* wel hoofding, maar geen headers voor kolommen */
    prt_nl("");

	prt_nl(p_vrk->krtNaam);

	zeros(buf,sizeof buf);	for (j = 0; j < 20; j++) buf[j] = ' ';
	movmem(tijd, &buf[20], 20);	prt_nl(buf); 
	prt_nl("");

    for (j=0; j<5; j++) {
      if (prt_krtfull[j][0]=='*' && prt_krtfull[j][1]==0) prt_cod(7);
      else prt_nl(prt_krtfull[j]);
    }
    prt_nl("");
    prt_cod(3);
    for (j=0; j<20; j++) buf[j]=' ';
    buf[20]=0;
    copynaam(txttxt[78],buf,20);
		if(krtvalue){
      conv_getal(krtvalue,buf+9,7,YES,0);
      copynaam(def_valuta,buf+17,3);
		}
		else {
      conv_getal(krtfull,buf+8,5,YES,0);
      copynaam("punten",buf+14,6);
		}
    prt_nl(buf);
    prt_cod(4);
  }
}

int CKasKRT::updkltkrt(void)
{
  char buf[41], *kasfile;
  int i, j, ix, krtref=0,saldo,newsaldo,full_count;
  double punten, val;
  long timeout, pos, fillen;
  bool AddedToCard=false;

  punten = p_vrk->t_punten + p_vrk->t_bdr2punt * krtperc / 100;
  
  if (krtfull==0) { // KORTING IN EUR afdrukken VOOR EXTERNE KLANTENKAART
    for (j=0; j<40; j++) buf[j]=' ';
    buf[40]=0;
 		copynaam(txttxt[86],buf,40);
    conv_getal(punten,buf+POS_TOTAAL,7,YES,def_digits);
    add_text(buf);
    return 0;
	}

	j=(int)punten; punten=j;  // integer part nemen
  full_count=0;
  p_lin=&p_vrk->lijn[p_vrk->used];
  p_lin->groep=GRP_PUNTEN;
  p_lin->aantal=(float)punten;
  p_lin->btw=(float)p_vrk->krtnr;

  if (krt_bits&8) {
		if (p_vrk->krtnr==0 || (!KassaTestConfigFlag && (JMD=::FindWindow("THE_JMD",NULL))==NULL)) { //_T("THE_JMD") {
      AddedToCard=false;
    }
    else {
      CMarkup Xmlo;
      // <Status>11</Status>
      // <KrtNr>10</KrtNr>
      // <Punten>12</Punten>
      // <Bedrag>23.95</Bedrag>     ? liefst goederen excl BTW
      saldo=p_vrk->krtPunten;
      Xmlo.AddElem("Status",11); // betaling e.d. is gebeurd, nu factuur maken ...
      Xmlo.AddElem("KrtNr",p_vrk->krtnr);
      newsaldo=(int)(saldo+punten);
      while ((krtfull>0) && (newsaldo>=krtfull)) {
        full_count++;
        newsaldo-=(int)krtfull;
      }
      Xmlo.AddElem("Punten",(int)punten);
      Xmlo.AddElem("Saldo",newsaldo);
      double TotBedrEx=0.;
      for (i=0; i<p_vrk->used; i++) {
        if (p_vrk->lijn[i].groep<0 || p_vrk->lijn[i].groep>=1000 || p_vrk->lijn[i].groep==groep_leeg) continue;
        TotBedrEx+=(p_vrk->lijn[i].totaal/(1.+p_vrk->lijn[i].btw/100.));
      }
      CString cstr;
      cstr.Format("%.2f",TotBedrEx);
      Xmlo.AddElem("Bedrag",cstr);
      Xmlo.Save(JmcCmdFilepath);
      UpdateOnJMC();

			CMarkup Xml;
			for (i=0; i<5; i++) {
				Xml.Load(KasCmdFilepath);
				if (Xml.GetDoc().GetLength()>0) break;
				Sleep(100);
			}
  		if (i<5) AddedToCard=true;
    }
  }
  else if (p_vrk->krtnr>=1) {
    for (ix=0; ix<krt_used; ix++) {
      if (krtinfo[ix].nr == p_vrk->krtnr) break;
    }
    timeout=get_hun()+500;
    while (get_hun()<timeout) {
      kasfile=LOCKASKRTPT;
      if (krt_bits&1) kasfile=SRVKASKRTPT;
		  if (krt_bits&2) kasfile=SRVWKASKRTPT;
		  if (krt_bits&4) kasfile=ZSHAREKRTPT;
  #if (!defined(_WIN32_WCE))
      krtref=_sopen( kasfile, O_RDWR | O_CREAT | O_BINARY, _SH_DENYWR, _S_IREAD | _S_IWRITE);
                  /* S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP */
  #else
      krtref=-1;
  #endif

      if (krtref>=0) break;
    }
    if (krtref>=0) {
      pos=(p_vrk->krtnr-1)*sizeof(saldo);
      fillen=_lseek(krtref,0L,2);
      if (fillen<(long)(p_vrk->krtnr*sizeof(saldo))) {
        saldo=0;
        for (j=0; j<(int)(p_vrk->krtnr-(fillen/sizeof(saldo))); j++) _write(krtref,&saldo,sizeof(saldo));
      }
      else {
        _lseek(krtref,pos,0);
        _read(krtref,&saldo,sizeof(saldo));
      }
      newsaldo=(int)(saldo+punten);
      while ((krtfull>0) && (newsaldo>=krtfull)) {
        full_count++;
        newsaldo-=(int)krtfull;
      }
      _lseek(krtref,pos,0);
      _write(krtref,&newsaldo,sizeof(newsaldo));
      _close(krtref);
      AddedToCard=true;
    }
  }

  if (AddedToCard) {
    p_lin->prijs=(float)saldo;
    p_lin->totaal=newsaldo;
    adj_text(p_vrk->used++); p_lin=&p_vrk->lijn[p_vrk->used];
    add_text(p_vrk->krtNaam);

    for (j=0; j<40; j++) buf[j]=' ';
    buf[40]=0;
    copynaam(txttxt[75],buf+20,20);
    val=15.;
    conv_getal((double)saldo,buf+POS_TOTAAL,7,YES,0);
    add_etext(buf);
    for (j=0; j<40; j++) buf[j]=' ';
    buf[40]=0;
    copynaam(txttxt[76],buf+20,20);
    conv_getal(punten,buf+POS_TOTAAL,7,YES,0);
    add_etext(buf);
    for (j=0; j<40; j++) buf[j]=' ';
    buf[40]=0;
    copynaam(txttxt[77],buf+20,20);
    conv_getal((double)newsaldo,buf+POS_TOTAAL,7,YES,0);
    add_etext(buf);
  }
  else if (punten>0) {
    adj_text(p_vrk->used++);p_lin=&p_vrk->lijn[p_vrk->used];
    if (p_vrk->krtNaam[0]) add_text(p_vrk->krtNaam);
    add_text(txttxt[71]);
    add_text(txttxt[72]);
    add_text(txttxt[73]);
    for (j=0; j<40; j++) buf[j]=' ';
    buf[40]=0;
    copynaam(txttxt[74],buf+20,20);
    conv_getal(punten,buf+POS_TOTAAL,7,YES,0);
    add_etext(buf);
  }
  return full_count;
}

void CKasKRT::krtline(char buf[])
{
  int i, k;

  for (i=0; i<56; i++) buf[i]=' ';
  buf[i]=0;
  k=0;
  if (krtsort==1) {
    for (i=0; i<sizeof(p_krt->code); i++) {
      if (p_krt->code[i]==0) break;
      buf[k++]=p_krt->code[i];
    }
    k=sizeof(p_krt->code)+1;
  }
  if (krtsort==2) {
    for (i=0; i<sizeof(p_krt->telefoon); i++) {
      if (p_krt->telefoon[i]==0) break;
      buf[k++]=p_krt->telefoon[i];
    }
    k=sizeof(p_krt->telefoon);
  }
  if (krtsort==3) {
    sprintf(buf,"%5d",p_krt->nr);
    buf[5]=' ';
    k=6;
  }
  for (i=0; i<sizeof(p_krt->naam); i++) {
    if (k==56 || p_krt->naam[i]==0) break;
    buf[k++]=p_krt->naam[i];
  }
  buf[56]=0;
}


int CKasKRT::CopyNettoChar(char *s, char *d, int len)
{
  int i,j;
  char byt;
  
	zeros(d,len);	j=0;
  for (i=0; i<len; i++) {
    byt=*s++;
    if (!byt) break;
    if (byt>='a' && byt<='z') byt+='A'-'a';
    if ((byt>='A' && byt<='Z') || (byt>='0' && byt<='9')) d[j++]=byt;
  }
  return j;
}


int CKasKRT::copy2JAMASCIstring(unsigned char *buf, int pos, int buflen, unsigned char *s, int len)
{
  const unsigned char intab[] = {  /* input convert table  intern'l keyb. -> JAMASCII */
 /*  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F          */
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,   /* 0X */
    16, 17, 18, 19, 20,151, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,   /* 1X */
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,   /* 2X */
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,   /* 3X */
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,   /* 4X */
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,   /* 5X */
    96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,   /* 6X */
   112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,   /* 7X */
   159,148,133,130,131,129,  0,132,135,136,134,140,139,138,  0,  0,   /* 8X */
     0,  0,  0,143,144,142,147,146,  0,  0,149,155,156,  0,  0,  0,   /* 9X */
   128,137,141,145,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* AX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* BX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* CX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* DX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* EX */
     0,  0,  0,  0,  0,  0,  0,  0,150,  0,  0,  0,  0,  0,152,  0};  /* FX */
  int i,byte;
 
  while (len>0) {
    if (s[len-1]>' ') break;
    len--;
  }
  if (len<0) len=-len;
  for (i=0; i<len; i++) {
    if (pos>=buflen) break;
    byte=*s++;
    if (byte==0) break;
    if (byte>=128) {
      if (byte==128) byte=0x9F;
      else byte=intab[byte];
    }
    buf[pos++]=byte;
  }
  return pos;
}

int CKasKRT::copystring(char *buf, int pos, int buflen, char *s, int len)
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

int CKasKRT::krtcompare(char *p1, char *p2, int dumlen)
{
  char *s1, *s2, b1[100], b2[100];
  int c1, c2, i, len, _krtsort;
  struct s_krtinfo *p_klant1, *p_klant2;

  p_klant1=(struct s_krtinfo *)p1; p_klant2=(struct s_krtinfo *)p2;
                                
  _krtsort=krtsort;
recompare:;
  if (_krtsort==1) {
    s1=p_klant1->code;
    s2=p_klant2->code;
    len=sizeof (p_klant1->code);
  }
  else if (_krtsort==2) {
    s1=p_klant1->telefoon;
    s2=p_klant2->telefoon;
    len=sizeof (p_klant1->telefoon);
  }
  else if (_krtsort==3) {
    if (p_klant1->nr < p_klant2->nr) return -1;
    if (p_klant1->nr > p_klant2->nr) return 1;
    return 0;
  }
  else {
    len=sizeof (p_klant1->naam);
    CopyNettoChar(p_klant1->naam,b1,len); s1=b1;
    CopyNettoChar(p_klant2->naam,b2,len); s2=b2;
 
    if (*s1=='X' && *(s1+1)=='Y' && *(s1+2)=='Z') b1[0]=127;
    if (*s2=='X' && *(s2+1)=='Y' && *(s2+2)=='Z') b2[0]=127;
  }
  if (_krtsort==1 || _krtsort==2) {
    if (s1[0]<=' ') {
      s1=b1; b1[0]=127; b2[1]=0;
    }
    if (s2[0]<=' ') {
      s2=b2; b2[0]=127; b2[1]=0;
    }
    if (*s1==127 && *s2==127) {
      _krtsort=0;
      goto recompare;
    }
  }
  for (i=0; i<len; i++) {
    c1=*s1;
    if (c1<0) c1+=256; /* char kan negatief zijn (0-127,-1 tot - 127) */
    c2=*s2;
    if (c2<0) c2+=256;
    if (c1>='a' && c1<='z') c1+='A'-'a';
    if (c2>='a' && c2<='z') c2+='A'-'a';  
    if (c1<c2) return -1;
    else if (c1>c2) return 1;
    else {s1++; s2++;}
  }
  if (_krtsort==2 || _krtsort==3) {
    _krtsort=0;
    goto recompare;
  }
  return 0;
}



void CKasKRT::sortkltkrt(void)
{
  jsort(krtinfo,(long) krt_used,sizeof( struct s_krtinfo),(int(*)(char *, char *, int))CKasKRT::krtcompare);
}
 
void CKasKRT::op_kaskrt(int line)
{
  int i, j, pos;
  long krtsize;

  if (krt_count==0) goto endsr;
  krtsize=(long) sizeof (struct s_krtinfo) * (krt_count+10);
  memory=getml(krtsize);
  if ((long)memory == 0L) disp_exit("Problems with getml() for creating KRT_INFO");
  krtinfo=(struct s_krtinfo *)memory;
  SplashText("Reading kasKRT.DAT ...");
  krtref=dopen("KASKRTNM.DAT",RDWRMODE);
  if (krtref<0) krt_used=0;
  else {
    krt_used = dseek(krtref,0L,2)/sizeof(struct s_kaskrtnm);
    if (krt_used > krt_count) disp_exit("Too many items in KASKRTNM.DAT");
    if (krt_used>0) {
      p_krt=krtinfo;
      for (i=0; i<krt_used; i++) {
        rd_kltkrt(i);
        p_krt=&krtinfo[i];
        p_krt->nr=i+1;
        movmem(kaskrtnm.code,p_krt->code,sizeof(krtinfo[0].code));
        pos = copy2JAMASCIstring((unsigned char *)p_krt->naam,0,sizeof(p_krt->naam),(unsigned char *)kaskrtnm.naam,sizeof(kaskrtnm.naam));
        pos = copystring(p_krt->naam,pos,sizeof(p_krt->naam)," - ",-3);
        pos = copy2JAMASCIstring((unsigned char *)p_krt->naam,pos,sizeof(p_krt->naam),(unsigned char *)kaskrtnm.straat,sizeof(kaskrtnm.straat));
        pos = copystring(p_krt->naam,pos,sizeof(p_krt->naam)," - ",-3);
        pos = copy2JAMASCIstring((unsigned char *)p_krt->naam,pos,sizeof(p_krt->naam),(unsigned char *)kaskrtnm.gemeente,sizeof(kaskrtnm.gemeente));
        p_krt->naam[pos]=0;
        pos=0;
        for (j=0; j<sizeof(kaskrtnm.telefoon); j++) {
          if (pos==sizeof(p_krt->telefoon)) break;
          if (kaskrtnm.telefoon[j]>='0' && kaskrtnm.telefoon[j]<='9') p_krt->telefoon[pos++]=kaskrtnm.telefoon[j];
        }
        while (pos<sizeof(p_krt->telefoon)) p_krt->telefoon[pos++]=0;
      }
    }
    sortkltkrt();
    dclose(krtref);
  }
endsr:;
  int plusave=ConSelect(-1);
  if(PlatformType(0)!=2)  ConStyle(CON_STYLE_NOBACKGROUND); // niet bij PDA
  cls();
  KrtConRef=ConSelect(plusave);
}

 
void CKasKRT::rd_kltkrt(int ix)
{
  long pos;
 
  pos = ix * (long) sizeof(struct s_kaskrtnm);
  dseek(krtref,pos,0);
  dread(krtref,&kaskrtnm,sizeof(struct s_kaskrtnm));
}

// hier algemene routines die naar JAMACON.DLL mogen 

void DisplayKeyboard(int x, int y, int x_adjust_,int y_adjust_, int soort_kb_) // soort_kb_ :0=ABCD, 1=AZERTY
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


int cmp_srt(char *p1,char *p2,int len)
{
  while(len--){
    if(*p1>*p2) return 1;
    if(*p1<*p2) return -1;
    p1++;p2++;
  }
  return 0;
}


CString Date2String(unsigned int date_,int mode_)
{
   char txtbuffer_[100];

   zeros(txtbuffer_,sizeof txtbuffer_);
   if(date_) datefm(txtbuffer_,date_,mode_);

   return CString(txtbuffer_);
}

unsigned int String2Date(CString datestr_,CString format_)
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

int SpaceZeros(char* ps_,int max_len)
{
  int k;

  for(k=0;k<max_len;k++){
    if(*(ps_+k)=='\0') *(ps_+k)=' ';
    else if(*(ps_+k)=='&') *(ps_+k)='+';
  }
  return k;
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
  


CString CurrentTime2String(void)
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
  
CString Double2String(double getal,long mode)  // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
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

char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_)
{
  int len_;

  if(cstr_.GetLength()) len_=cstr2arr(cstr_,pbuf_,maxlen_);
  else len_=0;
  if(len_>=maxlen_) len_--; pbuf_[len_]='\0'; 

  return pbuf_;
}


bool FileExist(CString Cfname_)
{
 
  char fname_[500];
  zeros(fname_,sizeof fname_); if(Cfname_.GetLength()) cstr2arr(Cfname_,fname_,500);
  return FileExist(fname_);
}



bool FileExist(char *fname_)
{
 
  FILE *fstream_;
   
  if( (fstream_  = fopen(fname_, "rb" )) != NULL ){
    fclose(fstream_);return true;
  }
  else return false;
}


void int2str(int d, char *s, int len) // len negatief geeft leadind zeros, anders spaces 
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

static void JamaAsc2Asc(char *ps_,int len_)
{
  int outtab[] = { /* output convert table JAMASCII -> intern'l video */
 /*  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F  */
   126,126,126,126,126,126,126,  7,  8,126, 10,126,126, 13,126,126, /* 0X */
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* 1X */
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, /* 2X */
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, /* 3X */
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, /* 4X */
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, /* 5X */
    96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111, /* 6X */
   112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127, /* 7X */
   160,133,131,132,135,130,138,136,137,161,141,140,139,162,149,147, /* 8X */
   148,163,151,150,129,154,248, 21,254, 27, 26, 24, 25,126,126,128,/* 9X */
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* AX */
   178,186,205,200,186,186,201,204,205,188,205,202,187,185,203,206, /* BX */
   178,179,196,192,179,179,218,195,196,217,196,193,191,180,194,197,/* CX */
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* DX */
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* EX */
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126};/* FX */
  int i;
  unsigned char u;

  for (i=0; i<len_; i++) {
    u=(unsigned char)ps_[i];
    if (u>=128) {
      u=outtab[u];
    }
    ps_[i]=u;
  }
}

static void Asc2JamaAsc(char *ps_,int len_)
{
  const unsigned char intab[] = {  /* input convert table  intern'l keyb. -> JAMASCII */
 /*  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F          */
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,   /* 0X */
    16, 17, 18, 19, 20,151, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,   /* 1X */
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,   /* 2X */
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,   /* 3X */
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,   /* 4X */
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,   /* 5X */
    96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,   /* 6X */
   112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,   /* 7X */
   159,148,133,130,131,129,  0,132,135,136,134,140,139,138,  0,  0,   /* 8X */
     0,  0,  0,143,144,142,147,146,  0,  0,149,155,156,  0,  0,  0,   /* 9X */
   128,137,141,145,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* AX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* BX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* CX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* DX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* EX */
     0,  0,  0,  0,  0,  0,  0,  0,150,  0,  0,  0,  0,  0,152,  0};  /* FX */
  int i;
  unsigned char u;

  for (i=0; i<len_; i++) {
    u=ps_[i];
    if (u>=128) {
      if (u==128) u=0x9F;
      else if (intab[u]) u=intab[u];
    }
    ps_[i]=u;
  }
}
 

