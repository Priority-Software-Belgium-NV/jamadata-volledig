/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0010GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0010dat
#define ovlcod BKH0010cod
#pragma warning (disable: 4716 4013 4244 4102 4018 4715)
__declspec(dllimport) short int errnum;
__declspec(dllimport) short int scrnum;
__declspec(dllimport) short int fldcurs;
__declspec(dllimport) int ExtraSTOSize;
#else
extern int errnum;
extern int scrnum;
extern int fldcurs;
#define zeroL zero
#endif
typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

char ovldat[] = "bkh0010  00:44 17/05/10 (c) Jamadata";

// FLAGDSP : andere hoofdmenu (2,501) owv punt V : Inlezen exporteren klt/lev
// FLAGMUY : andere hoofdmenu (2,501) owv punt V : werkregeling
// FLAGLEV : andere hoofdmenu (2,501) owv punt V : fiscal attesten 

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16

extern uint16 procid;
extern char info[];

extern char *s();
extern uint16 *u();
extern long *l();

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_us8PW[] = {7,0xC8,8,0,5,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os23[]   = {7,0x88,23,0,0,0,0};

static uint16 sys1820,sys1788;

ovlcod()
{
  int16 bk_allow,key;
  char choice;
  
  *u(25,6)=YES;
 
  sysget(1804,2,&bk_allow);
  if(bk_allow==0) ovlexit(ok(1802)*100+10);
  initload();
	
  FOREVER{
    redo:;
    scrnum=0;
#if FLAGMUY || FLAGDSP || FLAGLEV
		scrget(2,501);
#else
		scrget(1,1);
#endif
		fasunlck(0);
		if(AllowMasterFunctions) scraddpicto(1,0,78,23,2,1,59,0,4,"Masterfuncties"); 
		if(sys1788){scraddfield(99,1,23,8); scrifld(99,fm_os23," F4 selecteer systeem ");}
		if(fldlen(4,15)){scraddfield(100,4,12,0); scrifld(100,VarTextFmt(73,0),"Aanpassen wisselkoersen ........................................... : 7");}
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x8);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==5001) {*s(25,5)=1;ovlexit(5);goto redo;} // parameters
		if(fldlen(25,11)==0 || *s(25,11)==0){
		  fasinfo(80,201);*u(25,2)=*l(80,1);
		}
    if(key==104) ovlexit(9);
    else{
      switch (choice){
				case '1': if(CheckPw(0,0,0)) ovlexit( 11); break;
				case '2': if(CheckPw(0,1,0)) submen1(); break;
				case '4': if(CheckPw(0,3,0)) ovlexit( 14); break;
				case '5': if(CheckPw(0,4,0)) ovlexit( 15); break;
				case '6': if(CheckPw(0,5,0)) ovlexit(  6); break;
				case '7': if(fldlen(4,15)==0) errnum=12; else if(CheckPw(0,6,0)) ovlexit( 17);
									break;
				case '8': if(!ok(1800)) errnum=12;
									else if(CheckPw(0,7,0)) ovlexit(ok(1800)*100+18);
									break;
				case '9': if(CheckPw(0,8,0)) ovlexit( 19); break;
				case 'A': if(CheckPw(0,9,0)) ovlexit( 20); break;
				case 'U': if(CheckPw(0,13,0)) ovlexit( 21); break;
				case 'V': if(CheckPw(0,15,0)){
										if(ok(1802)) ovlexit(ok(1802)*100+10);
										else errnum=12;
									}
									break;
				case 'T': if(CheckPw(0,15,0)){
										if(ok(1798)) ovlexit(ok(1798)*100+10);
										else errnum=34;
									}
									break;
				case 'J': if(ovltest(410)) ovlexit(410); else errnum=12; break;
				case 'E': if(ovltest( 27)) ovlexit( 27); else errnum=12; break;
				case 'I': if(ovltest( 31)) ovlexit( 31);
									else errnum=12; break;
				case 'M': if(ovltest( 28)) ovlexit( 28); else errnum=12; break;
//				case 'P': if(ovltest(2800)) ovlcall(2800); else errnum=12; break;
				case '+': *s(25,5)=0;ovlexit(5); break;
				case '%': ovlexit( 99); break;
				case '=': ovlexit( 98); break;
				default : errnum=34; break;
      }
    }
  }
}

static submen1()
{
  int16 key,z;
  char choice;

  if(!ovltest( 22) && !ovltest(72) && !ovltest(73) && !ovltest(78) && !ovltest(77)) ovlexit( 12);
  FOREVER{
    redo:;
    scrget(1,32);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(1,0x0601);
    if(key==101||key==111) goto endsr;
    if(key==110){
      if(ovltest(32)) {ovlexit(32);}
      else {errnum=12; goto redo;}
    }
    switch(choice){
      case '1': ovlexit( 12);break;
      case '2': if(ovltest( 78)) ovlcall( 78,0); else errnum=12; break; // afboeken verkoopfacturen
      case '3': if(ovltest( 72)) ovlcall( 72,0); else errnum=12; break;
      case '4': if(ovltest( 73)) ovlcall( 73,0); else errnum=12; break;
      case '5': if(ovltest( 77)) ovlcall( 77,0); else errnum=12; break;
      default : errnum=34; break;
    }
  }
  endsr:;
}


static initload()
{
	char kar_;
	int color_;
	  
  sysget(1788,2,&sys1788);
  sysget(1820,2,&sys1820);
	sysget(18480,1,&kar_);if(kar_<1 || kar_>8) kar_=DefaultBackGroundColor;	color_=kar_; scrchat(-1,color_); // kleur juistzetten 
	ClearSysPosNrCheck();
  if(AllowMasterFunctions && *u(25,4)) CheckForJamaDataUpdates(NO); // op updates controleren (de 2-de keer owv automatisch opstarten)
  *u(25,4)=10;
}

static ClearSysPosNrCheck()
{
  int16 k,this_proc;

	for(k=0;k<16;k++){
  	sysget((3774+k*2),2,&this_proc);
    if(this_proc==procid){this_proc=0;sysput((3774+k*2),2,&this_proc);}
	}
}

static ok(pos)
int16 pos;
{
  int16 k;

  sysget(pos,2,&k);
  return k;
}

 

 
