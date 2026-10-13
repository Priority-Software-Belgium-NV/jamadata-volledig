/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0057GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0057dat
#define ovlcod BKH0057cod
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

char ovldat[] = "bkh0057  00:02 19/03/10 (c) Jamadata";
/* controle balansen */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXFLD          120
#define flag            uint16
								
 
extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

extern char *s();
extern int16 *i();
extern uint16 *u(),dateadd(),datejd();
extern long *l();
extern long val();
static long val4_1();
extern float *f();
extern double *d();
extern double valu_cnv();

static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us100[] = {7,0xC8,100,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_udatD[] = {4,0xC0,5,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};

static flag chk_btoeg=NO;
static flag sys3876;

static int16 form_dat[8],pr_mode,free=0,prtnr,j_tb[101],stu,pmax_tb;
static uint16 last_arc,dt_spil,mnd_strt, dt_1_1, dt_vj_11;
static char def_munt[4],mast_munt;
static flag sear_stt,first,sys1790;
static flag debit_allow=NO,credt_allow=NO,lvcd,klcd;
static long *pl_4_6;
static uint16 *pu_4_4,*pu_4_5;
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;

static struct {
  uint16 nr;
  uint16 typ;
  char nm[16];
  uint16 lastnr;
  long fingrb;
  long saldo;
  double saldo_vm;
  char munt[4];
  uint16 blz_o;
  uint16 blz_n;
} j_tab[81];                                             /* 1 extra element */


static struct {
  long grb;
  char nm[16];
  uint16 rec;
  uint16 journaal;
  double saldo_vj;
  double saldo_11;
  double saldo_nu;
} dsp_tab[25];/* 1 extra element */

static long kltcent, levcent;

ovlcod()
{
  int16 z,key,curs=2,dd_,mm_,yy_;
 
  initload();
  if(dt_spil==0) dt_spil=*u(25,2);
  FOREVER{
    redo:;
    scrget(1,224);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dt_spil);
    scrifld(z++,fm_odat,&dt_1_1);
    scrifld(z++,fm_odat,&last_arc);
    key=scrupd(curs,0xC1); curs=2;
    if(key==101) break;
    if(key==111) ovlexit(*u(25,4));
    if(dt_spil<last_arc || dt_spil==0) {errnum=37;goto redo;}
    jddate(dt_spil,&yy_,&mm_,&dd_); yy_%=100;
    yy_%=100; if(mnd_strt>mm_) yy_--; if(yy_<0) yy_=99;/* jaar 2000 */
    dt_1_1=datejd(yy_,mnd_strt,1);
    if(dt_1_1<last_arc) errnum=37;
    yy_--; if(yy_<0) yy_=99; dt_vj_11=datejd(yy_,mnd_strt,1);
    if(key==108){
      scrget(1,7);scrupd(-3,0);
      calc_sal();
      display();
      break;
    }
  }
  ovlexit(-1);
}
 
static calc_sal()
{
  int16 k,ks,mode_;

  for(k=0;k<2;k++){/* leveranciers en klanten */
    fasinit(4);*pl_4_6=dsp_tab[k].grb;mode_=1;
    FOREVER{
      if(faskeyi(4,3,mode_)) break; mode_=2;
      if(*pl_4_6!=dsp_tab[k].grb) break;
      if(*pu_4_4<=dt_spil){
	if(*pu_4_4<dt_1_1){/* enkel ECHTE klt/lev boekingen */
	  if(*pu_4_5!=dsp_tab[k].rec) dsp_tab[k].saldo_vj+=*d(4,32);
	}
	else{
	  if(*pu_4_4==dt_1_1 && *pu_4_5==dsp_tab[k].rec){/* rechtstreeks op grb */
	    dsp_tab[k].saldo_11+=*d(4,32);
	  }
	  dsp_tab[k].saldo_nu+=*d(4,32);
	}
      }
    }
  }
  for(k=2;k<pmax_tb;k++){/* bankjournalen */
    fasinit(5);
    *u(5,2)=dsp_tab[k].rec;
    ks=faskeyi(5,1,0);
    if(ks==0){
      if(last_arc<dt_1_1 && last_arc>dt_vj_11){
	dsp_tab[k].saldo_vj=*d(5,31)+*d(5,32);
      }
    }
    fasinit(4);*pl_4_6=dsp_tab[k].grb;mode_=1;/* banken */
    FOREVER{
      if(faskeyi(4,3,mode_)) break; mode_=2;
      if(*pl_4_6!=dsp_tab[k].grb) break;
      if(*pu_4_4<=dt_spil && *pu_4_4>last_arc){
	if(*pu_4_4<dt_1_1) dsp_tab[k].saldo_vj+=*d(4,32);
	else{
	  if(*pu_4_4==dt_1_1){
	    if(*s(4,2)!=dsp_tab[k].journaal) dsp_tab[k].saldo_11+=*d(4,32);
	  }
	  dsp_tab[k].saldo_nu+=*d(4,32);
	}
      }
    }
  }
}
 
static display()
{
  int16 k,z,key;
  uint16 dt_;

  FOREVER{
    scrget(1,225);z=1;
    dt_=dt_1_1-1;scrifld(z++,fm_odat,&dt_);
    scrifld(z++,fm_odat,&dt_1_1);
    scrifld(z++,fm_odat,&dt_spil);
    for(k=0;k<pmax_tb;k++){
      scrifld(z++,fm_ogrb,&dsp_tab[k].grb);
      scrifld(z++,fm_os15,dsp_tab[k].nm);
      if(dt_1_1<last_arc){
	scrifld(z++,fm_os3,"???");
	scrifld(z++,fm_os3,"???");
      }
      else{
	scrifld(z++,fm_od8_2,&dsp_tab[k].saldo_vj);
	scrifld(z++,fm_od8_2,&dsp_tab[k].saldo_11);
      }
      scrifld(z++,fm_od8_2,&dsp_tab[k].saldo_nu);
      if(k>=18) break;
    }
    key=scrupd(-1,0x1);
    if(key==101) break;
  }
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static nextline()
{
  free=prtline();
}

static initload()
{
  int16 k,yy_,mm_,dd_;

  fasunlck(0);
 
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  fileopen(1);
  fileopen(2);
  fileopen(3);
  fileopen(4);
  fileopen(5);

  mast_munt=*s(26,17);
 
  sysget( 294,3,def_munt);
  sysget(780,4,&levcent);
  sysget(784,4,&kltcent);
  sysget(1858,2,&last_arc);
  sysget(1866,2,&mnd_strt);
  sysget(1918,2,&sear_stt);
  sysget(3876,2,&sys3876);

  for(k=0;k<80;k++){
    sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
    j_tab[k].blz_n=j_tab[k].blz_o;
  }
  j_tab[80].nr=0;j_tab[80].typ=3;copy("???",&j_tab[80].nm[0],4);
  pu_4_4=u(4,4);
  pu_4_5=u(4,5);
  pl_4_6=l(4,6);
  pu_4_1=u(4,1); pl_4_1=l(4,1); len4_1=fldlen(4,1);

  dt_spil=*u(25,2);jddate(dt_spil,&yy_,&mm_,&dd_); yy_%=100;
  yy_%=100; if(mnd_strt>mm_) yy_--; if(yy_<0) yy_=99;          /* jaar 2000 */
  dt_1_1=datejd(yy_,mnd_strt,1);
  yy_--; if(yy_<0) yy_=99; dt_vj_11=datejd(yy_,mnd_strt,1);

  zero((char *)&dsp_tab[0].grb,sizeof dsp_tab);
  fasinit(3);*l(3,2)=levcent;faskeyi(3,1,0);
  dsp_tab[0].grb=*l(3,2); dsp_tab[0].rec=*u(3,1)+60000;
  copy(s(3,3),dsp_tab[0].nm,16);
  fasinit(3);*l(3,2)=kltcent;faskeyi(3,1,0);
  dsp_tab[1].grb=*l(3,2); dsp_tab[1].rec=*u(3,1)+60000;
  copy(s(3,3),dsp_tab[1].nm,16);
 
  pmax_tb=2;
  for(k=0;k<80;k++){
    if(j_tab[k].typ==3 || j_tab[k].typ==4 || j_tab[k].typ==7){
      fasinit(3);*l(3,2)=j_tab[k].fingrb; if(faskeyi(3,1,0)) continue;
      dsp_tab[pmax_tb].grb=*l(3,2); dsp_tab[pmax_tb].rec=*u(3,1)+60000;
      dsp_tab[pmax_tb].journaal=j_tab[k].nr;
      copy(j_tab[k].nm,dsp_tab[pmax_tb].nm,16);
      pmax_tb++;
    }
    if(pmax_tb>19) break;
  }
}

 

static long val4_1()
{
  if(len4_1==4) return *pl_4_1;
  else return (long)(*pu_4_1);
}
				
static chg4_1(value_)
long value_;
{
  if(len4_1==4) *pl_4_1=value_;
  else *pu_4_1=value_;
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

static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
#if 0
  if(stu_<=2) parmcall[1]=7;            bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3;                                              GEEN ADD
#endif
  if(stu_==6) parmcall[1]=0;
  parmcall[2]=0;
  parmcall[3]=0;
#ifdef STRAATKEY
  if(stu_==2) parmcall[4]=STRAATKEY;
#endif
  parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}

 
 
 
