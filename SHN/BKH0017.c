/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0017GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0017dat
#define ovlcod BKH0017cod
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

char ovldat[] = "bkh0017  00:11 14/09/10 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();


static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_us3[]   = {7,0xC8,3,0,1,0,0};
static char fm_uf3_5[] = {6,0xD4,3,5,0x70,0};
static char fm_od4_6[] = {6,0x95,4,6,0x60,0};

static char b[100];
static char def_munt[4];

static struct {
  char name[4];
  float coef;
} valtab[13];

extern struct{
  char fval[4];
  char tval[4];
  double coef;
} vtab[30];

static struct {
  char fval[4];
  char tval[4];
  double coef;
} def_vtab[30];

ovlcod()
{
  int16 j,k,key,curs=1,z,z_base_;
  char to_munt_[4];
  long l;

  fasunlck(0);
  zero(def_vtab[0].fval,sizeof def_vtab);
  copy("BEF",def_vtab[0].fval,3);
  copy("EUR",def_vtab[0].tval,3);
  def_vtab[0].coef=(double)(40.3399);

  sysget(2560,96,&valtab[0].name[0]);
  sysget( 294,4,def_munt);
  FOREVER{
    redo:;
    scrget(1,16);z=1;
    scrifld(z++,fm_os3,"EUR");
    z_base_=z;
    for(k=0;k<12;k++){
      scrifld(z++,fm_us3,valtab[k].name);
      scrifld(z++,fm_uf3_5,&valtab[k].coef);
    }
    key=scrupd(curs,0x04A1);curs=z_base_;
    if(key==101 || key==106) goto endsr;
    if(key==111) ovlexit(*u(25,4));
    for(k=0;k<12;k++){
      if(valtab[k].name[0]!='\0' && valtab[k].coef==0){
	errnum=38;curs=z_base_+k*2+1;goto redo;
      }
    }
    if(key==108) break;
  }
  if(key!=108) goto endsr;
  sysput(2560,96,&valtab[0].name[0]);
  sysget(6,6,b);
  stcd_li(b,&l);
  stcli_d(b,l+1,5,NO);
  sysput(6,5,b);
  zero((char *)&vtab[0].fval[0],sizeof vtab);
  for(k=0;k<15;k++){
    if(def_vtab[k].fval[0]){
      copy((char *)def_vtab[k].fval,(char *)vtab[k].fval,sizeof vtab[0]);
    }
    else break;
  }
  copy("EUR",to_munt_,3);
  //  else copy(def_munt,to_munt_,3);
  for(k=0;k<12;k++){
    if(valtab[k].name[0]=='\0' || valtab[k].coef==0) continue;
    for(j=0;j<30;j++){                     /* zoek rechtstreekse combinatie */
      if(vtab[j].fval[0]=='\0') {break;}
      if(cmpstr(valtab[k].name,vtab[j].fval,3)) continue;
      if(cmpstr(to_munt_,vtab[j].tval,3)) continue;
      break;
    }
    if(j<30){
      copy(valtab[k].name,vtab[j].fval,3); copy(to_munt_,vtab[j].tval,3);
      vtab[j].coef=valtab[k].coef;/* vtab[j].coef=(double)(1.)/vtab[j].coef; */
    }
  }
  if(cmpstr(to_munt_,"EUR",3)){/* DEF-munt moet in BEIDE richtingen staan */
    for(k=0;k<30;k++){/* zoek rechtstreekse combinatie */
      if(vtab[k].fval[0]=='\0') {break;}
      if(cmpstr("EUR",vtab[k].fval,3)) continue;
      if(cmpstr(def_munt,vtab[k].tval,3)) continue;
      break;
    }
    if(k<30 && vtab[k].fval[0]=='\0'){
      for(j=0;j<30;j++){/* zoek omgekeerde combinatie */
	if(vtab[j].fval[0]=='\0') {break;}
	if(cmpstr("EUR",vtab[j].tval,3)) continue;
	if(cmpstr(def_munt,vtab[j].fval,3)) continue;
	break;
      }
      if(vtab[j].fval[0]!='\0'){/* gevonden */
	copy(vtab[j].fval,vtab[k].tval,3);
	copy(vtab[j].tval,vtab[k].fval,3);
	vtab[k].coef=vtab[j].coef; vtab[k].coef=(double)(1.)/vtab[k].coef;
      }
    }
  }
  endsr:;
  ovlexit(-1);
}
