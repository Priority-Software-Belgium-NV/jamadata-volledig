#pragma warning(disable: 4996)
//#define WINVER 0x500

#include "stdafx.h"
#include "p:\jamacon\library\JamaConL.h"
#include "..\kassawin\kashead.h"
#include "windows.h"
#include "..\kassawin\picture.h"

#include "..\kassawin\kaspluc.h"
#include "..\kassawin\kassysc.h"
#include "..\kassawin\kastxtnc.h"
#include "..\kassawin\CustDisplay.h"
#include "..\kassawin\AffDisplay.h"

#include "..\kassawin\JmuDoc.h"

CKasPLU kasplu;
CKasSYS kassys;

CString m_strExtraDisplayName;
CRect ExtraDisplaySize, rtCust, rtAff, rtLarge;

CCustDisplay *pCustDisplay;
CAffDisplay *pAffDisplay; 

char beep_fl;

#define DATLEN  10000
#define MAX_LINES  36
 
extern char *txtmenu[],tijd[30], txttxt[200][150];
extern int ir300_fl;
extern int fref_sys;
extern int art_count;
extern int cumart_count, cumart_size;
extern int cumgrp_count, cumgrp_size;
extern unsigned pen_ok, mous_ok;
extern int prx_count, btw_holland;
extern unsigned jamin1[];
char *getml();

struct s_lijn *p_lin;
struct s_verkopen verkopen, *p_vrk=&verkopen;
int vrk_ix;/* wordt niet gebruikt, enkel voor kaslog.c */
int plu_ix, ticketnr,Print2PDF=0;
long mem_needed, get_hun();

struct {
  char code;
  char *tekst;
  char *exec;
} lines [MAX_LINES];

struct {
  float btw_perc;
  double basis;
  double btw;
  double totaal;
} btw_cumul[CUMBTW_COUNT];
int btw_used;
 
extern struct s_grp_info {
  char naam[20];
  float btw;
} grp_info[100];

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

char *p, *menudat;
int menulen,b_ref;

char alles_geladen;
 
long rec_used, dag_used, per_dag;
extern long rec_aantal, dag_aantal;
float voldoende;

int model=2;
int ConRef, ConTempRef;

#if CONTROL2PDF
CJmuDoc *pDocControle=NULL;
char* JMU_s;
#endif

/* --------------------------- Declaratie functies ---------------------- */
#include "KASMENU.H"

/* ---------------------------------------------------------------------- */

static void rls_mem()
{
  if (alles_geladen) {
    rls_memcumul();
	}
	rlsml(menudat,DATLEN);
}

void main(int argc, char *argv[])
{
  char disp_fl, splash_fl;
  int key;
  int ref;
 
  //AfxInitCommonControls();
	//AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
	//AfxSocketInit(); IsOk=true;
	//AfxEnableControlContainer();
	//AfxInitRichEdit();

  TouchPanelFlag=true;
#if _DEBUG
  TouchPanelFlag=false;
#endif
  //SplashShow();  // show splash screen
  splash_fl=true;
  moinit(0,1);
  SetProgramName("KeyConenTouch");
  ConRef=ConSelect(-1);
  ConStyle(CON_STYLE_NOBACKGROUND);
  ConTempRef=ConSelect(ConRef);

  kassys.rd_kassys(0); 
	if (fref_sys<0) {printf("KASSYS.DAT -> File not found"); exit(1);}
	disp_init(); disp_clr(0,0,80,25);
	//for(k=0;k<200;k++) if(ctxttxt[k]==0) break; else bcopy0(&ctxttxt[k][0],txttxt[k],sizeof txttxt[0]);
  menudat=getml((long)DATLEN);
	if ((long)menudat == 0L) disp_exit("Problems with getml() for creating MENU-buffer");
  if (prx_count>PRX_COUNT) prx_count=PRX_COUNT;
  else if (prx_count<1) prx_count=1;
	log_open(1,0);  
  disp_vid(0,2,"Initialising PRINTER ...",0);
  prt_init(); 
  cust_init();
//  pen_check(3,NO);
  alles_geladen=NO;
  /*get_memcumul();*/

  ref=dopen("kasmenu.dat",RDWRMODE);
  menulen = dread(ref,menudat,DATLEN); menudat[menulen++]='\x1A';
  dclose(ref);
  rem_comment();
                                                        
  init_menu();
  getstat();
  key=0; disp_fl=YES;

  FOREVER {
    if (disp_fl) {disptext(); displine(); disp_fl=NO;}
    if (splash_fl) {splash_fl=false; SplashHide();}
    cursor(77,23);
    key=get_toets(60,0);
    //beep_ok();
    cursor(100,100);
    if (key==8) key='1';
    switch (key) {
      case 1: goto end;
      case 9: 
        openen();
        ConSelect(ConTempRef);
        controle(YES);
        ConSelect(ConRef);
        if(Print2PDF) goto end;
        break;
      case 1000:
			  dispstat(NO); disp_fl=YES;
				break;
      default:execute(key); disp_fl=YES; break;
    }
  }
 end:
  rls_mem();
  disp_exit(".");
}

void rem_comment(void)
{
  int j, k, len;

  for (j=0; j<menulen-1; j++) {
    if (menudat[j]=='/' && menudat[j+1]=='*') {
      for (k=j+2; k<menulen-1; k++) {
        if (menudat[k]=='*' && menudat[k+1]=='/') {
          k+=2;
          len=menulen-k;
          if (len>0) movmem(menudat+k,menudat+j,len);
          len=(k-j);
          for (k=menulen-len; k<menulen; k++) menudat[k]=0;
          menulen-=len;
          if (j>0) j--;
          break;
        }
      }
    }
  }
}
 
int shure(char *s)
{
  char *s1,buf[100];
  int key, ret, len;
 
  s1=s+1;
  disp_clr(0,0,80,25);
  for (len=0; len<80; len++) {
    buf[len]=*s1;
    if (!*s1++) break;
  }
  buf[len]=0;
  disp_vid((80-len)/2,11,buf,6);
  disp_ikey( 0,24,15,1,4,txtmenu[12]);
  disp_ikey(16,24,15,1,5,txtmenu[13]);
  FOREVER{
//    pen_reset();
    key=get_toets(0,0);
    if(key==4) {ret=1; break;}
    if(key==5) {ret=2; break;}
    if(key==8) {ret=0; break;}
    beep_bad();
  }
  if(ret==1 && *s=='J') ret=1;
  else if(ret==2 && *s=='N') ret=1;
  else ret=0;
  /* disp_vid(0,0,80,25); */
  if (ret) /*beep_ok()*/; else beep_bad();
  return ret;
}

void openen(void)
{
  if (!alles_geladen) {
    SplashShow();
    get_memory(mem_needed);
    get_memcumul();
    kasplu.rd_kasplu(1);
    alles_geladen=YES;
    SplashHide();
  }
}
 
void execute(int key)
{
  int j, len;

  for (j=0; j<MAX_LINES; j++) {
    if (lines[j].code==key) break;
  }
  if (j<MAX_LINES) {
    len=0; p=lines[j].exec;
    while (*p!='#') {len++; p++;}
    b_ref=dcreat("kasmenub.bat",CREAMODE);
    wr_bat("echo off\x0D\x0a");
    p=lines[j].exec;
    FOREVER{
      switch(*p){
        case ';':
          wr_bat("echo ");
          if (!*(p+1)) wr_bat("."); else wr_bat(p+1);
          wr_crlf();
          break;
        case '.':
          wr_bat("pause"); wr_crlf();
          break;
        case 0x1A:
        case '#':
          goto endsr;
        case '!':
          if(!shure(p+1)) goto skip_it;
          break;
        case '+':
          wr_bat("cls\x0D\x0A");
          break;
        default:
          wr_bat(p); wr_crlf();
          break;
      }
      while(*p) p++;
      while(!*p) p++;
    }
	endsr:
		if (key=='1') {
			wr_bat("if errorlevel 1 goto end\r\n");
		}
    wr_bat("kasstart\x0D\x0A");
		if (key=='1') {
			wr_bat(":end\r\n");
			wr_bat("exit\r\n");
		}
		wr_bat("\x1A");
    dclose(b_ref);
		rls_mem();
		disp_exit("");
   skip_it:
    dclose(b_ref);
  }
}

void wr_crlf(void)
{
  dwrite(b_ref,"\x0D\x0A",2);
}

void wr_bat(char *s)
{
  char *s1;
  int len;
 
  len=0; s1=s;
  while (*s1) {len++; s1++;}
  dwrite(b_ref,s,len);
}
 
void init_menu(void)
{
  char buf[100], teken[2];
  int line, option, line_nr;
 
  p=menudat; line_nr=1;
  FOREVER{
    option = *p;
    if(option == '\x1A') break;
    if(option>='a'&&option<='z') option = option - 'a' + 'A';
    if((option>='0'&&option<='9')||(option>='A'&&option<='Z')){
      line = option - '0';
      if(line > 9) line += '9' - 'A' + 1;
      lines[line].code=option;
      lines[line].tekst=p+2;
      line_nr+=skip_cr();
      lines[line].exec =p;
      FOREVER{
        if(*p=='#') {line_nr+=skip_cr(); break;}
        line_nr+=skip_cr();
      }
    }
    else {
      teken[0]=option; teken[1]=0;
      sprintf(buf,"Illegal MENU-CHARACTER found : %1s in line%5d",teken,line_nr);
      disp_exit(buf);
    }
  }
}

void displine(void)
{
  int len, line, lin_count;
  char buf[2];
 
  buf[1]=0; lin_count=0;
  for(line=1;line<=26;line++){/* display 1 - 9, A - Q */
    if(lines[line].code){
      disp_vid(0,lin_count*2+2,lines[line].tekst,0);
      p=lines[line].tekst;
      len=0; while(*p++) len++;
      disp_vid(72,lin_count*2+2," : ",0);
      buf[0]=lines[line].code;
			disp_ikey(75,lin_count*2+2,5,1,*buf,buf);
      while(len++<71) disp_vid(len,lin_count*2+2,".",0);
      lin_count++;
      if (lin_count==11) break;/* maximum 11 lines on screen */
    }
  }
}

void getstat(void)
{
  log_getstatist(&dag_used,&dag_aantal,&rec_used,&rec_aantal);
  if (dag_used) {
    per_dag=rec_used/dag_used;
    voldoende=(float)(rec_aantal-rec_used)/(2*per_dag);
  }
  else {
    per_dag=0;
    voldoende = (float)dag_aantal;
  }
  if (rec_used>=rec_aantal || voldoende<3) dispstat(YES);
}
 
void dispstat(char opgelet)
{
  int off;
  char buf[100];
 
  disp_clr(0,0,80,25);
  log_getstatist(&dag_used,&dag_aantal,&rec_used,&rec_aantal);
  sprintf(buf,txtmenu[5],dag_used,dag_aantal);
  disp_vid(0,0,buf,0);
  sprintf(buf,txtmenu[6],rec_used,rec_aantal);
  disp_vid(0,1,buf,0);
  if (dag_used) {
    per_dag=rec_used/dag_used;
    sprintf(buf,txtmenu[7],per_dag); disp_vid(0,3,buf,0);
    voldoende=(float)(rec_aantal-rec_used)/(2*per_dag);
    sprintf(buf,txtmenu[8],voldoende); disp_vid(0,5,buf,0);
  }
  if (opgelet) {
    if (rec_used>=rec_aantal) off=5;
    else off=0;
    disp_vid(0,10,txtmenu[9+off],0);
    disp_vid(0,12,txtmenu[10+off],0);
    disp_vid(0,14,txtmenu[11+off],0);
  }
  disp_ikey(64,24,15,1,8,txtmenu[2]);
  get_toets(0,0);
}
 
void disptext(void)
{
  disp_clr(0,0,80,25);
  disp_ikey(23,0,34,1,1000,txtmenu[0]);
  disp_ikey( 0,24,15,1,1,txtmenu[1]);
  disp_ikey(16,24,15,1,8,txtmenu[2]);
  disp_ikey(32,24,15,1,9,txtmenu[4]);
  disp_vid(64,23,txtmenu[3],0);
}

int skip_cr(void)
{
  int nr;

  nr=0;
  while(*p!=0x0D) p++;
  while(*p<=' ') {
    if (*p=='\x1A') break;
    if (*p==0x0D) nr++;
    *p++='\0';
  }
  return nr;
}

int get_toets(int x, int y)
{
  long timeout;
  int key, ret, i;
	char oldtijd[100];
 
  if (mous_ok) mous_en_curs();
  key=0;
  timeout=get_hun()+60*100L;
  FOREVER {
    if ((pen_ok || mous_ok) && (x+y) && timeout<get_hun()) {ret=8; goto end;}
    key=kbcharnw();
    Sleep(50);
    if (key<0x10000) {
      if (key>=101*256 && key<=112*256) {ret=(key/256)-100; goto end;}
      if (key>='a' && key<='z') key+='A'-'a';
      if ((key>='1' && key<='9') || (key>='A' && key<='Z')) {ret=key; goto end;}
    }
    else {
		  key/=0x10000; // pen_scan(2);
			if (key>0) {ret=key; goto end;}
		}
    if (x+y) {
      get_tijd();
			for (i=0; i<sizeof(tijd); i++) {
			  if (tijd[i]!=oldtijd[i]) {
          disp_vid(x,y,tijd,0);
					break;
				}
			}
			movmem(tijd,oldtijd,sizeof(tijd));
    }
  }
 end:;
  if (mous_ok) mous_di_curs();
  return ret;
}

int ss_enable;
void start_saver(void)
{
}

#include "..\kassawin\kasCommn.cpp"

/* einde */

