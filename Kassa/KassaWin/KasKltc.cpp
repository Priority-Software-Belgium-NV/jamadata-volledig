// KasKLTc.cpp: implementation of the CKasKLT class.
//
//////////////////////////////////////////////////////////////////////
// #define WINVER 0x0501  // was 500
// #define _WIN32_WINNT 0x0501  // was 500

// #include "StdAfx.h"

#pragma warning(disable: 4996)

#include "p:\jamacon\library\JamaConL.h"
#include "kashead.h"
#if XP_KASSA
#include "EIDNative.h"  // in configuration -> link -> input de Swelio32.lib  door EIDRead.lib vervangen 
#else
#include "Swelio.h"   // in configuration -> link -> input de EIDRead.lib vervangen door Swelio32.lib 
#endif
#include "kassysc.h"
#include "kaspluc.h"
#include "KasKLTc.h"
#include "Afxwin.h"
#include "Markup.h"


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
#define KLEUR_LICHTBLAUW    RGB(200,250,225)


static void Asc2JamaAsc(char *ps_,int len_);
static void JamaAsc2Asc(char *ps_,int len_);

static CString CurrentTime2String(void);
static CString Date2String(unsigned int date_,int mode_);
static bool FileExist(char *fname_);
static bool FileExist(CString Cfname_);

static char *Zcstr2arr(CString cstr_,char *pbuf_,int maxlen_);
static int cmp_srt(char *p1,char *p2,int len);
static int cmpstrU(char *s1,char *s2,int len);
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

extern struct s_lijn *p_lin;
extern struct s_verkopen *p_vrk;
extern char txttxt[200][150], *txterr[], disp_fl;
extern long mem_needed;
extern struct s_verkopen *p_vrk;
extern struct s_klant klant;
extern void disp_window(void);
extern int klant_nr,fakt_allow;
extern int KeyboardType;

void UpdateOnJMC();
extern HWND JMD;
extern CString PathSpoolToServer, JmcCmdFilepath, KasCmdFilepath;

static unsigned char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static unsigned char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static unsigned char fm_us25[]  = {7,0xC8,25,0,0,0,0};
static unsigned char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static unsigned char fm_us10[]  = {7,0xC8,10,0,0,0,0};
static unsigned char fm_us7[]  = {7,0xC8,7,0,0,0,0};
static unsigned char fm_us1U[]  = {7,0xC8,1,0,1,0,0};
static unsigned char fm_os79[]  = {7,0x88,79,0,0,0,0};
static unsigned char fm_os30[]  = {7,0x88,30,0,0,0,0};
static unsigned char fm_os20[]  = {7,0x88,20,0,0,0,0};
static unsigned char fm_os10[]  = {7,0x88,10,0,0,0,0};
static unsigned char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static unsigned char fm_uu2_[]   = {6,0xD0,2,0,0x00,0};
static unsigned char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static unsigned char fm_ui2[]   = {6,0xD1,2,0,0x60,0};
static unsigned char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static unsigned char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static unsigned char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static unsigned char fm_udat[]  = {4,0xC0,1,'/'};
static unsigned char fm_odat[]  = {4,0x80,1,'/'};
static unsigned char fm_menu[]  = {7,0x48,1,0,9,0,0};
static unsigned char fm_ubtw[]  = {2,0xD8};
static unsigned char fm_u04[]   = {9,0xC8,1,0,0,0,'0','4',0};
static unsigned char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};

struct s_klantinfo {
  short unsigned nr;
  char code[10];
  char naam[60];
  char telefoon[12];
  char btwnummer[12+1];
	char NoCredit;
};

static int kltsort, FilterMode;

CKasKLT::CKasKLT()
{
  int n,k;
  char *ps_;

  brwsfirst=0; kltsort=0;

  for(n=0;n<4;n++){
    if(n==0) ps_=txttxt[31];
    else if(n==1) ps_=txttxt[30];
    else if(n==2) ps_=txttxt[35];
    else if(n==3) ps_=txttxt[36];

    for(k=0;k<10;k++) {
      if(*ps_==' ' || *ps_=='.') break;
      SortKeyText[n][k]=*ps_++;
    }
    SortKeyText[n][k]=0;
  }
}

CKasKLT::~CKasKLT()
{
  long kltsize;

  kltsize=(long) sizeof (struct s_klantinfo) * (MAX_KLANT+10);
  if (kltsize) rlsml((char *)klantinfo,kltsize);
  dclose(KlantFileRef);
}

int CKasKLT::SelectKlant(int type) // 0 = klant
{
  char buf[57], find[30],findnetto[30],str_netto[100], byte,txt_OK[30];
  int j,k, i, krec_,key, keyraw, aantal, prevsel, x, y, attr, selected,filterchanged_=NO;
  int findix, last_findix,findixnetto,kltnrsave, nr, old_screen,last_kltsort;
  int ret_positie_=-1,*pvrk_klant,ScreenLines=21,tb_scr[25],only_bestelling_=NO,pos_,knr_;


  zeros(txt_OK,sizeof txt_OK);bcopy("OK \n",txt_OK,4);
	if (fakt_allow & 0x01) copystring(txt_OK,4,25,GetPtrTxtKey(67),20);
	else if (fakt_allow & 0x02)  copystring(txt_OK,4,25,GetPtrTxtKey(76),20);
	else if (fakt_allow & 0x04)  copystring(txt_OK,4,25,GetPtrTxtKey(77),20);
	else if (fakt_allow != 8) return 0;
	zeros(find,sizeof find);
  if ((fakt_allow & 0x08) && (KassaTestConfigFlag || (JMD=::FindWindow("THE_JMD",NULL))!=NULL)) {
    CMarkup Xmlo;
    Xmlo.AddElem("Status",1); // laat een klant selecteren
    Xmlo.Save(JmcCmdFilepath);

    UpdateOnJMC();
    
		CMarkup Xml;
    for (i=0; i<5; i++) {
      Xml.Load(KasCmdFilepath);
			if (Xml.GetDoc().GetLength()>0) break;
      Sleep(100);
    }
		if (i==5) goto DoLocal;
		zeros(&KlantFiche,sizeof KlantFiche);klant_nr=0;p_vrk->fakt_type=0;
    klant_nr=atol(Xml.FindGetData("/Klant/F1"));
		p_vrk->JmcFactuurFlag=false;
		p_vrk->JmcDocType=0;
		p_vrk->PrijsViaJmcFlag=false;
    if (klant_nr>0) {
			p_vrk->JmcDocType=(unsigned char)atol(Xml.FindGetData("/DocType"));
			strcpy(KlantFiche.code,Xml.FindGetData("/Klant/F2").Left(sizeof(KlantFiche.code)));
      strcpy(KlantFiche.naam,Xml.FindGetData("/Klant/F3").Left(sizeof(KlantFiche.naam)));
      strcpy(KlantFiche.straat,Xml.FindGetData("/Klant/F4").Left(sizeof(KlantFiche.straat)));
      strcpy(KlantFiche.postnr,Xml.FindGetData("/Klant/F5").Left(sizeof(KlantFiche.postnr)));
      strcpy(KlantFiche.gemeente,Xml.FindGetData("/Klant/F6").Left(sizeof(KlantFiche.gemeente)));
      strcpy(KlantFiche.telefoon,Xml.FindGetData("/Klant/F8").Left(sizeof(KlantFiche.telefoon)));
      strcpy(KlantFiche.btwnummer,Xml.FindGetData("/Klant/F10").Left(sizeof(KlantFiche.btwnummer)));
      strcpy(KlantFiche.type,Xml.FindGetData("/Klant/F26").Left(sizeof(KlantFiche.type)));
			strcpy(KlantFiche.PrijsViaJmd,Xml.FindGetData("/Klant/F89").Left(sizeof(KlantFiche.PrijsViaJmd)));
			if(KlantFiche.PrijsViaJmd[0]=='J') p_vrk->PrijsViaJmcFlag=true;
			for(i=0;i<40;i++) if(KlantFiche.naam[i]=='\0') break;
			if(i && i<40 && KlantFiche.naam[i-1]=='!') {KlantFiche.naam[i-1]='\0'; KlantFiche.naam[39]='!';}
      int i=p_vrk->used;
      if(p_vrk->used>1) p_vrk->used++;  // om laatste artikel lijn niet te overschrijven 
      disp_window();
      p_vrk->used=i;
      disp_fl=NO;
      disp_vid(0,2,"                                               ",0);
      sprintf(buf,"%s", (char *)(LPCTSTR)Xml.FindGetData("/Klant/F3"));
      buf[20]=0;
      disp_vid(19,2,buf,2);  
      p_vrk->JmcFactuurFlag=true;

      if (fakt_allow & 0x01) p_vrk->fakt_type=1;
      else if (fakt_allow & 0x02) p_vrk->fakt_type=2;
      else if (fakt_allow & 0x04) p_vrk->fakt_type=3;

      disp_fl=YES;
    }
  }
  else {
	DoLocal:;
    old_screen=ConSelect(KltConRef);last_kltsort=kltsort; if(kltsort<0 || kltsort>=4) kltsort=0;
    pvrk_klant=&p_vrk->klant_nr; last_findix=0;
    kltnrsave=*pvrk_klant;FilterMode=NO;filterchanged_=NO;
		p_vrk->PrijsViaJmcFlag=false;
  redo_full:;
    cls();ConStyle(CON_STYLE_NOBACKGROUND);
   // disp_panel(12,0,58,23,PANEL_VER_SMALLER | PANEL_HOR_SMALLER | PANEL_WITH_EDGE,RGB(255,255,0));
    disp_key(70, 0,10,2,22);
    disp_key(70, 2,10,3,23);
    disp_ikey(70,17,10,3,114,SortKeyText[kltsort],KLEUR_FTOETS); //disp_key(70,17,10,3,114);
    disp_key(70,20,10,3,24);
    disp_key(70,23,10,2,13);
    disp_ikey( 0, 0,12,4,112,txt_OK,KLEUR_FTOETS);
    disp_ikey(13,23,15,2,5000,"wijzig klant",KLEUR_FTOETS);
    disp_ikey(28,23,15,2,5001,"nieuwe klant",KLEUR_FTOETS);
	if(!FilterMode) disp_ikey(43,23,13,2,5002,"zoek in naam",KLEUR_FTOETS);
	else disp_ikey(43,23,13,2,5002,"zoek",KLEUR_FTOETS);
	disp_ikey(56, 23, 14, 2, 5003, "zet op ticket", KLEUR_FTOETS);

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
    disp_ikey(8,23,4,2,2000+'.',".");
    disp_key(0,5,12,2,83);
    disp_key(70,5,10,2,83);
    findix=0; selected=-1; brwsfirst=0; 
    if (*pvrk_klant>0) {
      for (i=0; i<klt_used; i++) {
        if (klantinfo[i].nr==*pvrk_klant) {
          selected=i;
          brwsfirst=i;
          *pvrk_klant=0;
          break;
        }
      }  
    }
    else {
      if(ret_positie_>=0) brwsfirst=ret_positie_;
    }
    disp_clr(12,0,58,23);
    disp_panel(12,0,58,23,PANEL_VER_SMALLER | PANEL_HOR_SMALLER | PANEL_WITH_EDGE,KLEUR_TITEL);

    FOREVER {
      redisp:;
      disp_ikey(70,17,10,3,114,SortKeyText[kltsort],KLEUR_FTOETS); //disp_key(70,17,10,3,114);
      movmem(find,buf,11);
      i=findix;
      if (i<0) i=0;
      for (; i<12; i++) buf[i]=' ';
      buf[i]=0;
      disp_vid(0,4,buf,2);
      p_klant=&klantinfo[brwsfirst];

      pos_=brwsfirst;
      for(aantal=0;aantal<ScreenLines;aantal++) tb_scr[aantal]=-1;
      for(aantal=0;aantal<ScreenLines;aantal++){
        pos_=FindNextKlant(pos_,1,find);
        if(pos_<0 || pos_>=klt_used) break;
        tb_scr[aantal]=pos_;
        pos_++;
      }
 
      for (j=0; j<aantal; j++) {
        knr_=tb_scr[j];
        if (knr_==selected) attr=8; else attr=2;
        p_klant=&klantinfo[knr_];
				if (p_klant->NoCredit) {
					if (knr_==selected) attr=11; else attr=15;
				}
				kltline(buf);
        disp_vid(13,1+j,buf,attr);
      }
      for (i=0; i<56; i++) buf[i]=' '; buf[i]=0;
      for (j; j<ScreenLines; j++) disp_vid(13,1+j,buf,2);
      prevsel=selected;ret_positie_=brwsfirst;last_findix=findix;
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
      if(key==5000){
        if(selected>=0){
				  krec_=klantinfo[selected].nr;
				  if(FGetKlant(krec_)){
					  if(UpdateKlantFiche(krec_,NO)) LoadKlantFile();
            if(KlantFiche.naam[0]=='X' && KlantFiche.naam[1]=='Y' && KlantFiche.naam[2]=='Z') *pvrk_klant=-1;
            else *pvrk_klant=krec_;
					  goto redo_full;
				  }
        }
      }
      if(key==5001){
        zeros(&KlantFiche,sizeof KlantFiche);
        if(UpdateKlantFiche(0,YES)){ 
          LoadKlantFile();
				  *pvrk_klant=klt_used;
        }
        goto redo_full;
      }
	  if(key==5002) {
		  if(!FilterMode) FilterMode=YES; else FilterMode=NO;
		  if(!FilterMode) disp_ikey(45,23,15,2,5002,"zoek in naam",KLEUR_FTOETS);
	  else disp_ikey(45,23,15,2,5002,"zoek",KLEUR_FTOETS);
		  filterchanged_=YES;last_findix=0;brwsfirst=0;
	  }
	  if (key == 5003 && selected >= 0){ // zet adres op ticket
		  *pvrk_klant = klantinfo[selected].nr; // klanten-nummer
		  FGetKlant(*pvrk_klant);
		  char buf[50];
		  p_lin = &p_vrk->lijn[p_vrk->used];
		  strcpy(buf, txttxt[101]); add_text(buf);
		  strcpy(buf, txttxt[98]);
		  pos_ = copystring(buf, 2, 40, KlantFiche.naam, 37);
		  add_text(buf);
		  strcpy(buf, txttxt[98]);
		  copystring(buf, 2, 40, KlantFiche.straat, 37);
		  add_text(buf);
		  strcpy(buf, txttxt[99]);
		  copystring(buf, 2, 40, KlantFiche.postnr, 7);
		  copystring(buf, 7, 40, KlantFiche.gemeente, 25);
		  add_text(buf);
		  strcpy(buf, txttxt[101]); add_text(buf);
		  selected = -1; *pvrk_klant = 0;
		  disp_window();
//		  p_vrk->ExtraTicket = true;
		  ConSelect(old_screen);
		  break;
		}
      if (key==112) {
        if (selected>=0) break;
      }
      else if (key==114) { // sortering 
        kltsort++; findix=0;
        if (kltsort==4) kltsort=0; // geen recnr
        if (selected>=0) {
          *pvrk_klant=klantinfo[selected].nr;
        } 
        sortkasklt();
        brwsfirst=0;
        if (selected>=0) {
          for (i=0; i<klt_used; i++) {
            if (klantinfo[i].nr==*pvrk_klant) {
              selected=i;
              brwsfirst=i;
              *pvrk_klant=0;
              break;
            }
          }
        }  
        findix=0; find[0]=0; last_kltsort=kltsort;
        goto redisp;
      }
	  selected = -1;
	  if (keyraw == 251 * 256) { // left mouse
		x = mspos_h; y = mspos_v;
		if (y >= 1 && y <= 21 && x >= 13 && x <= 67) {
		  if (tb_scr[y - 1] >= 0) {
			selected = tb_scr[y - 1];
			if (selected == prevsel) break;
		  }
		}
	  }

      if (key==18) { // ENTER GEDUWD
        if(prevsel>=0) {
          selected=prevsel; break;
        }
      }
      if (key==22) { // terug 
        if (kltnrsave>0) *pvrk_klant=kltnrsave;
        else *pvrk_klant=0;
        break;
      }
      if (key==13) { // clear
        selected=-1;*pvrk_klant=0;
        break;  
      }
      else if (key==23) {
        pos_=brwsfirst;
        for(k=0;k<19;k++){
          pos_=FindNextKlant(pos_,-1,find);
				  if(pos_>0) pos_--; else break;
        }
        if(pos_>=0) brwsfirst=pos_; else brwsfirst=0;
      }
      else if (key==24) {
        for(k=19;k>=0;k--) if(tb_scr[k]>=0) break;
        if(k>=19) brwsfirst=tb_scr[k];
      }
      if (brwsfirst >= klt_used) brwsfirst-=19;
      if (brwsfirst<0) brwsfirst=0;
    
      if ((key==83) || (key>=2000 && key<3000) || filterchanged_) {
				if(filterchanged_ && FilterMode){
					kltsort=0; // steeds alfabetisch	
					if(kltsort!=last_kltsort){sortkasklt();last_kltsort=kltsort;}
				}
				filterchanged_=NO;
        if (key==83) {
          findix--;
          if (findix<0) findix=0; zeros(&find[findix],sizeof(find) - findix);
        }
        if (key>=2000 && key<=3000) {
          find[findix]=key-2000;
				  if ((find[findix]>='a') && (find[findix]<='z')) find[findix]+='A'-'a';
				  if(findix<25) findix++;
        }
				if(FilterMode && findix!=last_findix) {brwsfirst=0;goto redisp;} // steeds vanaf 0 terug beginnen
        if (findix>0) {
				  if(last_findix==0){
					  if(find[0]>='0' && find[0]<='9'){
		  			  if(kltsort==0) kltsort=2; // default is telefoon
					  }
				    else if(find[0]=='.') kltsort=1;
				    else kltsort=0; // alfa altijd op naam
				  }
			    if(kltsort!=last_kltsort){
				    sortkasklt();last_kltsort=kltsort;
				  }
          if (kltsort==4) { // nummer 
            nr=0;
            for (i=0; i<findix; i++) {
              nr=nr*10+find[i]-'0';
					  }
            for (j=0; j<klt_used; j++) {
              if (klantinfo[j].nr==nr) {brwsfirst=j; selected=j; break;}             
					  }
				  }
          else {
				    findixnetto=CopyNettoChar(find,findnetto,findix);
            for (j=0; j<klt_used; j++) {
					    zeros(str_netto,sizeof str_netto);
					    if(kltsort==1) CopyNettoChar(klantinfo[j].code,str_netto,sizeof klantinfo[0].code);
					    else if(kltsort==2) CopyNettoChar(klantinfo[j].telefoon,str_netto,sizeof klantinfo[0].telefoon);
					    else if(kltsort==3) CopyNettoChar(klantinfo[j].btwnummer,str_netto,sizeof klantinfo[0].btwnummer);
					    else CopyNettoChar(klantinfo[j].naam,str_netto,sizeof klantinfo[0].naam);
              for (i=0; i<findixnetto; i++) {
                byte = str_netto[i];
                if ((byte>='a') && (byte<='z')) byte+='A'-'a';
                if (byte>findnetto[i]) {
                  j=klt_used; i=findixnetto;
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

    if (selected>=0 || *pvrk_klant) {
      if(selected>=0) *pvrk_klant=klantinfo[selected].nr; // klanten-nummer
      FGetKlant(*pvrk_klant);
	  ConSelect(old_screen);
	  if (*pvrk_klant) {
		klant_nr = *pvrk_klant;
		if (fakt_allow & 0x01) p_vrk->fakt_type = 1;
		else if (fakt_allow & 0x02) p_vrk->fakt_type = 2;
		else if (fakt_allow & 0x04) p_vrk->fakt_type = 3;
	  }
    }
    else {
      zeros(&KlantFiche,sizeof KlantFiche);*pvrk_klant=0;klant_nr=0;p_vrk->fakt_type=0;
      ConSelect(old_screen); disp_fl=YES;
    }
  }
  return (int)(KlantFiche.type[0]);
}



int CKasKLT::FindNextKlant(int pos_,int mode_,char *pfind_) // mode_ : 1=vooruit, -1=achteruit
{
	 CString cfind_,cnaam_;
	 	 
   if(pos_<0 || pos_>=klt_used) return -1;
	 if(FilterMode){
		 cfind_=CString(pfind_,12); cfind_.MakeUpper(); cfind_.Trim();
		 for(pos_;pos_<klt_used && pos_>=0;pos_+=mode_){
			 if(pos_<0 || pos_>=klt_used) return -1;
			 cnaam_=CString(klantinfo[pos_].naam,sizeof klantinfo[0].naam);cnaam_.MakeUpper(); cnaam_.Trim();
			 if(cnaam_.Find(cfind_,0)>=0) return pos_;
		 }
	 }
/*
   FOREVER{
     if(mode_<0){pos_--; if(pos_<0) break;}
     else {pos_++; if(pos_>=klt_used) break;}
   }
 */
   return pos_;
}
 

bool CKasKLT::UpdateKlantFiche(int recordnr_, int newklant_)
{
  int j,k,key,z,curs=2;
  bool ret_val_;
  long btw_nr_;
  char str_[15];  

						
  j=0;btw_nr_=0;
  for(k=0;k<12;k++) {
    if(KlantFiche.btwnummer[k]>='0' && KlantFiche.btwnummer[k]<='9'){
      btw_nr_=btw_nr_*10+KlantFiche.btwnummer[k]-'0'; j++;
    }
    if(j>=10) break;
  }
  if(j!=9 && j!=10) btw_nr_=0;
  if (btw_nr_ > 1000000000) {
	btw_nr_ -= 1000000000L;
	bcopy((char *)(&btw_nr_), str_, 4);
	str_[3] |= 0x80; bcopy(str_, (char *)(&btw_nr_), 4);
  }
  if(KlantFiche.type[0]<'0' || KlantFiche.type[0]>4) KlantFiche.type[0]='0';
  ConStyle(0); // grijze achtergrond
  while(true){
redo:;
    scrnum=0;scrget(2,1503); z=1;
    if (newklant_) scrifld(z++,fm_os10,KlantFiche.code);
    else scrifld(z++,fm_us10,KlantFiche.code);
    scrifld(z++,fm_us40,KlantFiche.naam);
    scrifld(z++,fm_us30,KlantFiche.straat);
    scrifld(z++,fm_us7,KlantFiche.postnr);
    scrifld(z++,fm_us25,KlantFiche.gemeente);
    scrifld(z++,fm_us15,KlantFiche.telefoon);
    scrifld(z++,fm_ubtw,&btw_nr_);
    scrifld(z++,fm_u04,KlantFiche.type);
    disp_ikey(2,10,20,2,106,"annuleer",KLEUR_FTOETS);
    disp_ikey(22,10,20,2,108,"neem aan",KLEUR_FTOETS);
 //   disp_ikey(vdmax_h-13,8,10,2,110,"schrap",KLEUR_FTOETS);
    DisplayKeyboard(0,13,0,1,KeyboardType);
    key=scrupd(curs,0xA0); curs=2;
    if (key&0xFFFF0000) key/=0x10000;
    if(key==106) return false;
/*
    if(key==110){
      if(ConMessageBox(_T("Wenst U echt deze fiche te schrappen???"),_T("Schrappen klantenkaart"),MB_YESNO | MB_ICONQUESTION)==IDYES){
	return FKillKlant(recordnr_);
      }
    }
*/
    if((KlantFiche.code[0]<'0' || KlantFiche.code[0]>'9') && newklant_==NO) {curs=1;errnum=34;goto redo;}
    k=KlantFiche.naam[0];
    if(k<'A' || k>'z' || (k>'Z' && k<'a')) {curs=2;errnum=30;goto redo;}
	btw_deco((char *)&KlantFiche.btwnummer[0], &btw_nr_, YES);
    //lbd_=btw_nr_&0xBFFFFFFF;                                   /* BTW-nummer */
    //stcli_d(str_,lbd_,9,0);
    //bcopy(&str_[0],&KlantFiche.btwnummer[0],3);KlantFiche.btwnummer[3]='.';
    //bcopy(&str_[3],&KlantFiche.btwnummer[4],3);KlantFiche.btwnummer[7]='.';
    //bcopy(&str_[6],&KlantFiche.btwnummer[8],3);
    if(key==108){
      if(newklant_) ret_val_=FAddKlant(); else ret_val_=FUpdKlant(recordnr_);
      if(ret_val_==true) break;
    }
  }
  return true;
}

bool CKasKLT::FUpdKlant(int recnr_)
{

  long pos_;
  char buf_[200];
    
  if(recnr_<1 || recnr_>klt_used) return false;
  if(CheckDubbeleKlant(recnr_)) {errnum=31;return false;}
redo_open:; 
  pos_ = (recnr_-1) * (long) sizeof(struct s_klant);
  dseek(KlantFileRef,pos_,0);


  movmem(&KlantFiche,buf_,sizeof(struct s_klant));
  JamaAsc2Asc(buf_,sizeof(struct s_klant)); // naar ascii
  dwrite(KlantFileRef,buf_,sizeof(struct s_klant));
  dclose(KlantFileRef);
  KlantFileRef=dopen("KasKLT.DAT",RDWRMODE);
  if (KlantFileRef<0){
    if(ConMessageBox(_T("Probleem met wegschrijven!\nOpnieuw proberen?"),_T("Wegschrijven gegevens"),MB_YESNO | MB_ICONQUESTION)==IDYES) goto redo_open;
    else return false;
  }

  return true;
}


bool CKasKLT::FAddKlant(void)
{

  int k,recnr_;
  long pos_;
  char buf_[200];
  
  k=KlantFiche.naam[0];
  if(k<'A' || k>'z' || (k>'Z' && k<'a')) return false;
  if(klt_used+1>=MAX_KLANT) return false;
  bcopy("9999999900",KlantFiche.code,10);
  recnr_=klt_used+1;
  if(CheckDubbeleKlant(recnr_)) {errnum=31;return false;}

  pos_ = (recnr_-1) * (long) sizeof(struct s_klant);
  dseek(KlantFileRef,pos_,0);
  movmem(&KlantFiche,buf_,sizeof(struct s_klant));
  JamaAsc2Asc(buf_,sizeof(struct s_klant)); // naar ascii
  dwrite(KlantFileRef,buf_,sizeof(struct s_klant));
  dclose(KlantFileRef);
redo_open:; 
  KlantFileRef=dopen("KasKLT.DAT",RDWRMODE);
  if (KlantFileRef<0){
    if(ConMessageBox(_T("Probleem met wegschrijven!\nOpnieuw proberen?"),_T("Wegschrijven gegevens"),MB_YESNO | MB_ICONQUESTION)==IDYES) goto redo_open;
    else return false;
  }
  klt_used++;
  return true;
}


bool CKasKLT::FGetKlant(int recnr_)
{

  int len_;
  long pos_;
  char buf_[200];
    
  if(recnr_<1 || recnr_>klt_used) return false;
  pos_ = (recnr_-1) * (long) sizeof(struct s_klant);
  dseek(KlantFileRef,pos_,0);
  len_=dread(KlantFileRef,buf_,sizeof(struct s_klant));
  if(len_==sizeof(struct s_klant)){
    Asc2JamaAsc(buf_,sizeof(struct s_klant)); // naar Jama-ascii
    movmem(buf_,&KlantFiche,sizeof(struct s_klant));
  } else len_=0;
  if(len_) return true; else return false;
}
  
bool CKasKLT::get_klant(void)
{
  int len_;
  long pos_;
  char buf_[200];
    


	len_=0;
  if (KassaTestConfigFlag || (JMD=::FindWindow("THE_JMD",NULL))!=NULL) {
		if(KlantFiche.naam[0]){
			len_=sizeof(struct s_klant);
  		movmem(&KlantFiche,&klant,sizeof(struct s_klant));
		}
		else{
			zeros(&klant,sizeof klant);len_=0;
		}
	}
	else{
		if(klant_nr<1 || klant_nr>klt_used) {
			zeros(&klant,sizeof klant);
			return false;
		}
	}
  if(len_==0){ // op oude manier opzoeken
		pos_ = (klant_nr-1) * (long) sizeof(struct s_klant);
		dseek(KlantFileRef,pos_,0);
		len_=dread(KlantFileRef,buf_,sizeof(struct s_klant));
		if(len_==sizeof(struct s_klant)){
			Asc2JamaAsc(buf_,sizeof(struct s_klant)); // naar Jama-ascii
			movmem(buf_,&klant,sizeof(struct s_klant));
		} 
		else{
			zeros(&klant,sizeof klant);len_=0;
		}
	}
  if(len_) return true; else return false;
}


bool CKasKLT::FKillKlant(int recnr_)
{

  int k;
  char buf_[200];

  if(recnr_<1 || recnr_>klt_used) return false;
  for(k=0;k<sizeof(struct s_klant);k++) buf_[k]=' ';
  movmem(buf_,&KlantFiche,sizeof(struct s_klant));
  stcli_d(buf_,(long)(recnr_+1),5,0);
  movmem(buf_,KlantFiche.code,5);
  movmem("XYZ",KlantFiche.naam,3);movmem(buf_,&KlantFiche.naam[3],5);
  return FUpdKlant(recnr_);
}

void CKasKLT::kltline(char buf[])
{
  int i, k;

  for (i=0; i<56; i++) buf[i]=' ';
  buf[i]=0;
  k=0;
  if (kltsort==1) {
    for (i=0; i<sizeof(p_klant->code); i++) {
      if (p_klant->code[i]==0) break;
      buf[k++]=p_klant->code[i];
    }
    k=sizeof(p_klant->code)+1;
  }
  if (kltsort==2) {
    for (i=0; i<sizeof(p_klant->telefoon); i++) {
      if (p_klant->telefoon[i]==0) break;
      buf[k++]=p_klant->telefoon[i];
    }
    k=sizeof(p_klant->telefoon);
  }
  if (kltsort==3) {
    for (i=0; i<sizeof(p_klant->btwnummer); i++) {
      if (p_klant->btwnummer[i]==0) break;
      buf[k++]=p_klant->btwnummer[i];
    }
    k=sizeof(p_klant->btwnummer);
  }
  if (kltsort==4) {
    sprintf(buf,"%5d",p_klant->nr);
    buf[5]=' ';
    k=6;
  }
  for (i=0; i<sizeof(p_klant->naam); i++) {
    if (k==56 || p_klant->naam[i]==0) break;
    buf[k++]=p_klant->naam[i];
  }
  buf[56]=0;
}


void CKasKLT::dsp_klantinfo(void)
{
  char buf[50];
  int i, nr_;
   
  nr_=p_vrk->klant_nr;
  i=p_vrk->used;
  if(p_vrk->used>1) p_vrk->used++;  // om laatste artikel lijn niet te overschrijven 
  disp_window();
  p_vrk->used=i;
  disp_fl=NO;
  disp_vid(0,2,"                                               ",0);
  for (i=0; i<20; i++) {
    buf[i]=KlantFiche.naam[i];
    if (buf[i]==0) break;
  }
  buf[i]=0;
  disp_vid(19,2,buf,2);
}


int CKasKLT::copy2JAMASCIstring(unsigned char *buf, int pos, int buflen, unsigned char *s, int len)
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

int CKasKLT::copystring(char *buf, int pos, int buflen, char *s, int len)
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

int CKasKLT::kltcompare(char *p1, char *p2, int dumlen)
{

  char *s1, *s2, b1[100], b2[100];
  int c1, c2, i, len, _kltsort;
  struct s_klantinfo *p_klant1, *p_klant2;

  p_klant1=(struct s_klantinfo *)p1; p_klant2=(struct s_klantinfo *)p2;
  _kltsort=kltsort;
recompare:;
  if (_kltsort==1) {
    s1=p_klant1->code;
    s2=p_klant2->code;
    len=sizeof (p_klant1->code);
  }
  else if (_kltsort==2) {
    s1=p_klant1->telefoon;
    s2=p_klant2->telefoon;
    len=sizeof (p_klant1->telefoon);
  }
  else if (_kltsort==3) {
    s1=p_klant1->btwnummer;
    s2=p_klant2->btwnummer;
    len=sizeof (p_klant1->btwnummer);
  }

//  else if (_kltsort==4) {
//    if (p_klant1->nr < p_klant2->nr) return -1;
//    if (p_klant1->nr > p_klant2->nr) return 1;
//    return 0;
//  }

  else {
    len=sizeof (p_klant1->naam); 
		CopyNettoChar(p_klant1->naam,b1,len); s1=b1;
    CopyNettoChar(p_klant2->naam,b2,len); s2=b2;
    if (*s1=='X' && *(s1+1)=='Y' && *(s1+2)=='Z') b1[0]=127;
    if (*s2=='X' && *(s2+1)=='Y' && *(s2+2)=='Z') b2[0]=127;
  }

  if (_kltsort==1 || _kltsort==2 || _kltsort==3) {
    if (s1[0]<=' ') {
      s1=b1; b1[0]=127; b2[1]=0;
    }
    if (s2[0]<=' ') {
      s2=b2; b2[0]=127; b2[1]=0;
    }
    if (*s1==127 && *s2==127) {
      _kltsort=0;
      goto recompare;
    }
  }
  for (i=0; i<len; i++) {
    c1=*s1;
    if (c1<0) c1+=256; // char kan negatief zijn (0-127,-1 tot - 127) 
    c2=*s2;
    if (c2<0) c2+=256;
    if (c1>='a' && c1<='z') c1+='A'-'a';
    if (c2>='a' && c2<='z') c2+='A'-'a';  
    if (c1<c2) return -1;
    else if (c1>c2) return 1;
    else {s1++; s2++;}
  }
  if (_kltsort==2 || _kltsort==3) {
    _kltsort=0;
    goto recompare;
  }

  return 0;
}

void CKasKLT::sortkasklt(void)
{
  jsort(klantinfo,(long) klt_used,sizeof( struct s_klantinfo),(int(*)(char *, char *, int))CKasKLT::kltcompare);
}
 
void CKasKLT::op_kasklt(int line)
{
  long kltsize;

 
  klt_used=0;
  if (MAX_KLANT==0) goto endsr;
  kltsize=(long) sizeof (struct s_klantinfo) * (MAX_KLANT+10);
  memory=getml(kltsize);
  if ((long)memory == 0L) disp_exit("Problems with getml() for creating KLT_INFO");
  klantinfo=(struct s_klantinfo *)memory;
  SplashText("Reading KASKLT.DAT ...");
  KlantFileRef=dopen("KASKLT.DAT",RDWRMODE);
  if (KlantFileRef<0){
    KlantFileRef=_creat("KASKLT.DAT",CREAMODE);
    if (KlantFileRef<0) disp_exit("Impossible to open KASKLT.DAT"); 
    else{
      dclose(KlantFileRef);
      KlantFileRef=dopen("KASKLT.DAT",RDWRMODE);
    }
    klt_used=0;
  }
  LoadKlantFile();

endsr:;
  int plusave=ConSelect(ConTempRef);
  if(PlatformType(0)!=2)  ConStyle(CON_STYLE_NOBACKGROUND); // niet bij PDA
  cls();
  KltConRef=ConSelect(plusave);
}

void CKasKLT::LoadKlantFile(void)
{
  int i, j,k, pos;
  long fpos_;
  
  klt_used=0;
  if (MAX_KLANT==0) goto endsr;


  klt_used = dseek(KlantFileRef,0L,2)/sizeof(struct s_klant);
  if (klt_used > MAX_KLANT) klt_used=MAX_KLANT;

  p_klant=klantinfo;
  for (i = 0; i < klt_used; i++) {
	fpos_ = i * (long) sizeof(struct s_klant);
	dseek(KlantFileRef, fpos_, 0);
	dread(KlantFileRef, &kaskltnm, sizeof(struct s_klant));
	p_klant = &klantinfo[i];
	p_klant->nr = i + 1;
	if (kaskltnm.naam[39] == '!') {
	  p_klant->NoCredit = TRUE;
	  kaskltnm.naam[39] = 0;
	}
	movmem(kaskltnm.code, p_klant->code, sizeof(klantinfo[0].code));
	pos = copy2JAMASCIstring((unsigned char *)p_klant->naam, 0, sizeof(p_klant->naam), (unsigned char *)kaskltnm.naam, sizeof(kaskltnm.naam));
	pos = copystring(p_klant->naam, pos, sizeof(p_klant->naam), " - ", -3);
	pos = copy2JAMASCIstring((unsigned char *)p_klant->naam, pos, sizeof(p_klant->naam), (unsigned char *)kaskltnm.straat, sizeof(kaskltnm.straat));
	pos = copystring(p_klant->naam, pos, sizeof(p_klant->naam), " - ", -3);
	pos = copy2JAMASCIstring((unsigned char *)p_klant->naam, pos, sizeof(p_klant->naam), (unsigned char *)kaskltnm.gemeente, sizeof(kaskltnm.gemeente));
	p_klant->naam[pos] = 0;
	pos = 0;
	for (j = 0; j < sizeof(kaskltnm.telefoon); j++) {
	  if (pos == sizeof(p_klant->telefoon)) break;
	  if (kaskltnm.telefoon[j] >= '0' && kaskltnm.telefoon[j] <= '9') p_klant->telefoon[pos++] = kaskltnm.telefoon[j];
	}
	while (pos < sizeof(p_klant->telefoon)) p_klant->telefoon[pos++] = 0;
	j = 0;  for (k = 0; k < 12; k++) if (kaskltnm.btwnummer[k] >= '0' && kaskltnm.btwnummer[k] <= '9') j++;
	if (j < 10){
	  p_klant->btwnummer[0] = '0'; movmem(kaskltnm.btwnummer, &p_klant->btwnummer[1], 12);
	}
    else movmem(kaskltnm.btwnummer,p_klant->btwnummer,sizeof(klantinfo[0].btwnummer));
  }

  sortkasklt();

endsr:;
}

bool CKasKLT::CheckDubbeleKlant(int recnr_) 
{
  char netto_kode_[11],klt_code_[11],klt_naam_[61],netto_naam_[61],netto_btw_[13],klt_btw_[13];
  int j,pos,chk_btw_=YES;

  zeros(netto_kode_,sizeof netto_kode_);zeros(netto_naam_,sizeof netto_naam_);zeros(netto_btw_,sizeof netto_btw_);
  if(cmpstr(KlantFiche.code,"99999999",8)) CopyNettoChar(KlantFiche.code,netto_kode_,sizeof KlantFiche.code-1);
  CopyNettoChar(KlantFiche.btwnummer,netto_btw_,sizeof KlantFiche.btwnummer-1);
  if(cmpstr(netto_btw_,"000000000",9)==0 || cmpstr(netto_btw_,"999999999",9)==0 || cmpstr(netto_btw_, "0999999999", 10) == 0) chk_btw_=NO;
  pos = copystring(klt_naam_,0,sizeof klt_naam_,KlantFiche.naam,sizeof(KlantFiche.naam));
  pos = copystring(klt_naam_,pos,sizeof klt_naam_," - ",-3);
  pos = copystring(klt_naam_,pos,sizeof klt_naam_,KlantFiche.straat,sizeof(KlantFiche.straat));
  pos = copystring(klt_naam_,pos,sizeof klt_naam_," - ",-3);
  pos = copystring(klt_naam_,pos,sizeof klt_naam_,KlantFiche.gemeente,sizeof(KlantFiche.gemeente));
  klt_naam_[pos]=0;CopyNettoChar(klt_naam_,netto_naam_,sizeof netto_naam_-1);

  for (j=0; j<klt_used; j++) {
    if(klantinfo[j].nr==recnr_) continue;
    zeros(klt_code_,sizeof klt_code_);CopyNettoChar(klantinfo[j].code,klt_code_,sizeof klantinfo[0].code-1);
    zeros(klt_naam_,sizeof klt_naam_);CopyNettoChar(klantinfo[j].naam,klt_naam_,sizeof klantinfo[0].naam-1);
    zeros(klt_btw_,sizeof klt_btw_);CopyNettoChar(klantinfo[j].btwnummer,klt_btw_,sizeof klantinfo[0].btwnummer-1);
    if(cmp_srt(netto_kode_,klt_code_,sizeof klt_code_)==0) return true;
    if(cmp_srt(netto_naam_,klt_naam_,sizeof klt_naam_)==0) return true;
    if(chk_btw_ && cmp_srt(netto_btw_,klt_btw_,sizeof klt_btw_)==0){
      if(ConMessageBox(_T("Klant met zelfde BTW-nummer bestaat reeds! Toch doorgaan?"),_T("Wegschrijven klant"),MB_YESNO | MB_ICONQUESTION)==IDNO) return true;
      else chk_btw_=NO;
    }
  }
  return false;
}


int CKasKLT::CopyNettoChar(char *s, char *d, int len)
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

int cmpstrU(char *s1,char *s2,int len)
{
  char b1,b2;

  while (len-->0) {
    b1=*s1;if (b1>='a' && b1<='z') b1+='A'-'a';
    b2=*s2;if (b2>='a' && b2<='z') b2+='A'-'a';
    if (b1<b2) return -1;
    else if (b1>b2) return 1;
    else {s1++; s2++;}
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

void JamaAsc2Asc(char *ps_,int len_)
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

void Asc2JamaAsc(char *ps_,int len_)
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
      else u=intab[u];
    }
    ps_[i]=u;
  }
}
 

