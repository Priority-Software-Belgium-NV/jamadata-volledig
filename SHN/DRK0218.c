/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0218GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0218dat
#define ovlcod DRK0218cod
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

char ovldat[] = "drk0218  00*07 30/08/10 (c) Jamadata";

#define FOREVER         while(1)

extern uint16 procid;
extern char info[];


#include "par0240.c"

extern char *s();
extern uint16 *u();

static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char use_xon;

ovlcod()
{
  int16 key,keuze;
  char choice;

  if(sizeof ovl_tabel==2 && ovltest(234)==0){
    ovlexit(ovl_tabel[0]);
  }
  sysget(2706,1,&use_xon);

  FOREVER{
    redo:;
    scrget(2,100);fasunlck(0);
    if(ovltest(2922)){
      scraddf(120,23,59,8);scrifld(120,fm_os20," F10 afhalingen/memo");
    }
    if(ovltest(234)){
      scraddf(118,21,4,2);
      scrifld(118,fm_os79,"Herafdrukken facturen ............................................. : H ");
    }
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0601);
    if(key==101 || key==111) ovlexit(*u(25,4));
    if(key==110){ovlcall(2922,0); goto redo;}
    if(choice=='H'){
      if(ovltest(234)) ovlexit(234); else errnum=12;
    }
    keuze=0;
    if(choice>='A' && choice<='Z') keuze=9+choice-'A';
    else keuze=choice-'1';
    if(keuze>=0 && keuze<(sizeof ovl_tabel/2)){
      if(ovl_tabel[keuze]){
				if(ovl_tabel[keuze]==14) ovlcall(ovl_tabel[keuze],1);/* om parm 1 door te geven */
				else if(ovl_tabel[keuze]==297) ovlcall(ovl_tabel[keuze],2);/* om parm 2 door te geven (verwerken toerverkopen) */
				else if(use_xon && ovl_tabel[keuze]==253) errnum=34;
				else ovlexit(ovl_tabel[keuze]);
      }
    }
    else errnum=34;
  }
}
 
static scraddf(fld,v,h,attr)
int16 fld,v,h,attr;
{
  int16 *pi;
				
  pi = (int16 *)info;
  *(pi+0) = fld;
  *(pi+1) = v;
  *(pi+2) = h;
  *(pi+3) = attr;
  sendtask(procid+20,3,11,info,8);
  scrnum=0;
}
 
