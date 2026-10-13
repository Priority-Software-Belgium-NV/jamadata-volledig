/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0210GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0210dat
#define ovlcod DRK0210cod
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

char ovldat[] = "drk0210  00:04 16/09/10 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0

extern uint16 procid;
extern char info[];

extern char *s();
extern uint16 *u();
extern long *l();

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os23[]   = {7,0x88,23,0,0,0,0};

static char xon_char[2];
extern uint16 *u();
static sys1820,sys1788;
static uint16 use_xon,x1_ok,x2_ok;

ovlcod()
{
  int16 key;
  char choice;

  initload();
 
  FOREVER{
    redo:;
    scrnum=0;scrget(2,1);fasunlck(0);
		if(AllowMasterFunctions) scraddpicto(1,0,78,23,2,1,59,0,4,"Masterfuncties"); 
		if(sys1788){scraddfield(99,1,23,8); scrifld(99,fm_os23," F4 selecteer systeem ");}
    scrfld(1,25,1);
		scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x8);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==5001) {*s(25,5)=1;ovlexit(5);goto redo;} // parameters
		if(fldlen(25,11)==0 || *s(25,11)==0){
		  fasinfo(80,201);*u(25,2)=*l(80,1);
		}
 
    errnum=0;
    if(key==104) ovlexit(9);
    else{
      switch (choice){
				case '1': if(CheckPw(1,0,0)){
										if(ovltest(255)) {ovlexit(255);break;}
										if(ovltest(211)) {ovlexit(211);break;}
										if(ovltest(33)) {ovlcall(33,0);break;}
										errnum=34;
									} break;
				case '2': if(CheckPw(1,1,0)){
										if(ovltest(212)) {ovlexit(212);break;}
										if(ovltest(222)) {ovlexit(222);break;}
										if(ovltest(262)) {ovlexit(262);break;}
										if(ovltest(290)) {ovlexit(290);break;}
										if(ovltest(293)) {ovlexit(293);break;}
										if(ovltest(112)) {ovlexit(112);break;}
										errnum=34;
									} break;
				case '3': if(CheckPw(1,2,0)){
										if(ovltest(213)) {ovlexit(213);break;}
										if(ovltest(230)) {ovlexit(230);break;}
										errnum=34;
									} break;
				case '4': if(CheckPw(1,3,0)) submen1();    break;
				case '5': if(CheckPw(1,4,0)) submen2();    break;
				case '6': if(CheckPw(1,5,0)) ovlexit(  6); break;
				case '7': if(CheckPw(1,6,0)){
										if(ovltest(217)) {ovlexit(217);break;}
	//									if(ovltest( 17)) {ovlexit( 17);break;}
										errnum=34;
									} break;
				case '8': if(!ok(1800)) errnum=12;
									else if(CheckPw(1,7,0)) ovlexit(ok(1800)*100+18);
									break;
				case '9': if(CheckPw(1,8,0)) ovlexit(219); break;
				case 'A': if(CheckPw(1,9,0)){
										if(ovltest(220)) {ovlexit(220);break;}
										if(ovltest(236)) {ovlexit(236);break;}
										errnum=34;
									} break;
				case 'B': if(!ok(1804)) errnum=12;
										else if(CheckPw(1,15,0)) ovlexit( 10);
										break;
				case 'T': if(ok(1798)) ovlexit(ok(1798)*100+10);
									else errnum=34;
									break;
				case 'W': if(ovltest(2295)){if(CheckPw(1,8,0)) ovlexit(2295);}
									else if(ovltest(2296)){if(CheckPw(1,8,0)) ovlexit(2296);}
									break;
				case 'J': if(ovltest(410)) ovlexit(410); else errnum=34; break;
				case 'E': if(ovltest(196)) ovlexit( 27); else errnum=34; break;
				case 'I': if(ovltest(229)) ovlexit(229); else errnum=34; break;
				case 'M': if(ovltest( 28)) ovlexit( 28); else errnum=34; break;
				case 'P': if(ovltest(2291)) ovlexit(2291); else errnum=34; break;
				case 'F': if(ovltest( 25)) ovlexit( 25); else errnum=34; break;
				case '+': *s(25,5)=0;ovlexit(5); break;
				case '%': ovlexit( 99); break;
		
				case '=': ovlexit( 98); break;
				default : errnum=34; break;
			}
      if(errnum && use_xon){if(execx(choice)) choice='\0';}
    }
  }
}

static submen1()
{
  if(fldlen(16,1) && ovltest(239)) ovlexit(239);
	else if(fldlen(60,1) && ovltest(236)) ovlexit(236);
  if(!ok(3590)) ovlexit(214);
  endsr:;
}

static submen2()
{

  if(!ovltest(225) && !ovltest(215) && ovltest(238)) ovlexit(238);
  if(!ovltest(225)) ovlexit(215);

  endsr:;
}

static execx(choice)
char choice;
{
  if(x1_ok==NO){
    if(choice==xon_char[0]) x1_ok=YES; else return(NO);
  }
  else if(choice==xon_char[1]) x2_ok=YES; else {x1_ok=NO;return(NO);}
  if(x1_ok && x2_ok) ovlexit(253);
}

static ok(pos)
int16 pos;
{
  int16 k;

  sysget(pos,2,&k);
  return k;
}

static initload()
{
	char kar_;
	int color_;

	sysget(1788,2,&sys1788);
  sysget(1820,2,&sys1820);

  sysget(2706,2,&xon_char[0]);
  if(ovltest(253)==0) zero(xon_char,sizeof xon_char);
  if(xon_char[0]){
    use_xon=YES;
    if(xon_char[1]==0) x2_ok=YES; else x2_ok=NO;
  }
  else {use_xon=NO;x1_ok=NO;x2_ok=NO;}
	sysget(18480,1,&kar_);if(kar_<1 || kar_>8) kar_=DefaultBackGroundColor;	color_=kar_; scrchat(-1,color_); // kleur juistzetten 
  ClearSysPosNrCheck();
	if(AllowMasterFunctions && *u(25,4)) CheckForJamaDataUpdates(NO); // op updates controleren (de 2-de keer owv automatisch opstarten)
	*u(25,4)=210;
}

static ClearSysPosNrCheck()
{
  int16 k,this_proc;

	for(k=0;k<16;k++){
  	sysget((3774+k*2),2,&this_proc);
    if(this_proc==procid){this_proc=0;sysput((3774+k*2),2,&this_proc);}
	}
}
  

				
