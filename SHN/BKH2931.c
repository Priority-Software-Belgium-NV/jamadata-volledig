/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH2931GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH2931dat
#define ovlcod BKH2931cod
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

char ovldat[] = "bkh2931  00:01 22/10/98 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define MAXFLD          120
#define STU             3

extern int16 retcall,parmcall[8];

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern float *f();
extern double *d();
static flag geboekt();

static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_of2_1[] = {6,0x94,2,1,0x30,0};

static int16 parmmain[8];
static char naam51[51],oldnm[51], reserv[520];
static flag code,chk_intra,klcd,lvcd;
static float btwpct[4];

static struct {
  char filname[15];
  int16 filstru;
} files[5];

ovlcod(parmval)
int16 parmval;
{
  copy((char *)parmcall,(char *)parmmain,sizeof parmmain);
  initload();
  retcall=fichupd(parmval);
  copy((char *)parmmain,(char *)parmcall,sizeof parmcall);
  ovlexit(-1);
}
 
static initload()
{
  int16 k;
 
  for(k=0;k<5;k++) getfname(k+1,k);
	fileopen(3);
  sysget(1008,16,(char *)btwpct);
  chk_intra=NO; if(fldlen(4,48)) chk_intra=YES;
}

static fileopen(nr_)
int16 nr_;
{
  int16 stu_,k;
  char filename[15];

  k=300+17*(nr_-1);
  sysget(k,15,filename);
  sysget(k+15,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(errnum=fasopen(filename,0)) ovlexit(-1);
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  }
}

static fichupd(mode)/* 0=display, 1=update, 2=add */
int16 mode;
{
  int16 k,curs=2,key,z;
  char *p_stu_3;
  long old_grb_;
 
  p_stu_3=s(3,3);
  if(*s(3,4)=='\0')*s(3,4)='N';
  if(*s(3,5)=='\0')*s(3,5)='J';
  if(*s(3,6)=='\0')*s(3,6)='0';
  if(*s(3,7)=='\0')*s(3,7)='0';
  if(*s(3,10)=='\0')*s(3,10)='0';
  if(*s(3,11)=='\0')*s(3,11)='J';
  old_grb_=*l(3,2);
  FOREVER{
    redo:
    scrget(1,8); z=1;
    scrfld(z++,25,1);
    for(k=2;k<=7;k++) scrfld(z++,3,k);
    for(k=0;k<4;k++) scrifld(z++,fm_of2_1,&btwpct[k]);
    for(k=8;k<=13;k++) scrfld(z++,3,k);
    if(fldlen(4,48)) scrfld(z++,3,14); else streepje(z++);
    z+=15;
    for(k=32;k<52;k++) scrfld(z++,3,k);
    if(mode==0) curs=-1;
    key=scrupd(curs,0x00A1);curs=2;
    if(key==106){
      if(mode==2) return NO;
      else return YES;
    }
    k=*p_stu_3;
    if(key==101 && k=='\0') return NO;

    if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;curs=3;goto redo;}
    if(*l(3,2)==0) {errnum=38;curs=2;goto redo;}
    if(*s(3,4)!='J' && *s(3,4)!='N') {errnum=34;curs=4;goto redo;}
    if(*s(3,5)!='J' && *s(3,5)!='N') {errnum=34;curs=5;goto redo;}
    if(*s(3,6)=='\0')*s(3,6)='0';
    if(*s(3,7)=='\0')*s(3,7)='0';
    if(*s(3,11)=='\0')*s(3,11)='J';
    if(*s(3,10)=='\0')*s(3,10)='0';
    if(*s(3,5)=='J'){
      if(*s(3,10)!='0') {errnum=22;curs=13;goto redo;}
    }
    else{
      if(*s(3,10)=='0') {errnum=23;curs=13;goto redo;}
    }
    if(mode==1 && old_grb_!=*l(3,2)){
      if(geboekt()) {errnum=60;goto redo;}
    }
    if(mode==1) {errnum=fasupd(3);fasflush(0);}
    else if(mode==2) {errnum=fasadd(3);fasflush(0);}
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
  return YES;
}

static flag geboekt()
{
  uint16 rec__;
					
  rec__=*u(3,1)+30000*(3-1);

  if(fasopen(files[3].filname,0)==0){
    fasinit(4);
    *u(4,5)=rec__;
    if(faskeyi(4,4,2)==0){
      if(*u(4,5)==rec__) return YES;
    }
  }
  if(fasopen(files[4].filname,0)==0){
    fasinit(5);
    *u(5,2)=rec__;
    if(faskeyi(5,1,0)==0) return YES;
  }
  return NO;
}
 
static getfname(nr,array)
int16 nr,array;
{
  nr--;
  sysget(300+17*nr,15,files[array].filname);
  sysget(315+17*nr,2,&files[array].filstru);
}

static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
}
 
static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
						
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero(parmcall,sizeof parmcall);
  parmcall[0]=mod_;
  parmcall[1]=1;/* bits : 0 = display, 1=update, 2=add */
  parmcall[2]=0;
  parmcall[3]=0;
  parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}
 
