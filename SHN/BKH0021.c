/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0021GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0021dat
#define ovlcod BKH0021cod
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

char ovldat[] = "bkh0021  00:07 19/03/10 (c) Jamadata";
/* schrappen boeking (B.U) */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXEL           1000
#define flag            uint16

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();
static long val4_1();


static char fm_os75[]  = {7,0x88,75,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x20,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ol9[]   = {6,0x93,9,0,0x70,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};

static int16 jaar,journl, blokkeer;
static uint16 volgnr,dt_boek,last_arc,MinBkhDatum,tot_cnt[8];
static long recnr[MAXEL];
static double tot_bd[8];
static char def_munt[4];
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;

ovlcod()
{
  initload();

  execute();
  ovlexit(-1);
}

static execute()
{
  int16 key,dum1,dum2;

  jddate(*u(25,2),&jaar,&dum1,&dum2);fasunlck(-1);
  FOREVER{
    journl=0;volgnr=0;dt_boek=0;
    redo:
    scrget(1,17);
    scrfld(1,25,1);
    scrifld(2,fm_uu4,&jaar);
    scrifld(3,fm_uu2,&journl);
    scrifld(4,fm_uu5,&volgnr);
    scrifld(5,fm_udat,&dt_boek);
    scrifld(6,fm_odat,&last_arc);
    key=scrupd(1,0x409);
    if(key==101 || key==111) break;
    if(jaar==0) {errnum=38;goto redo;}
    if(key!=104) {errnum=21;goto redo;}
    if(ft_kil()==0) goto redo;
    fasflush(0);
    scrget(1,170);
    scrifld(11,fm_os75,"De gevraagde boekingen werden geschrapt.");
    scrifld(13,fm_os75,"Druk F8");
    scrupd(0xFFFF,0x81);
  }
}

static ft_kil()
{
  int16 g,k,dum1,dum2,jaari,key_mode;
  uint16 q=0;
  flag found=NO;

	
  for(k=0;k<8;k++) {tot_cnt[k]=0;tot_bd[k]=0;}
  blokkeer=NO;
  fasinit(4);
  *s(4,2)=journl;
  *u(4,3)=volgnr;
  key_mode=1;
  fasinit(1);fasinit(2);
  FOREVER{
    if(faskeyu(4,1,key_mode)) break;
    key_mode=2;
    if(*s(4,2)!=journl || *u(4,3)!=volgnr) break;
    jddate(*u(4,4),&jaari,&dum1,&dum2);
    if(jaari==jaar){
      if(dt_boek==0 || dt_boek==*u(4,4)){
	if(*u(4,4)<=last_arc || *u(4,4)<=MinBkhDatum) {blokkeer=YES;}/* errnum=37;return NO;}*/
	found=YES;
	if(q==MAXEL) {tab_del(q);q=0;}
	recnr[q++]=val4_1();
	g=0;
	if(*d(4,32)<0) g=-1; else g=1;
	k=*u(4,5)/30000;if(g<0) k+=4;
	tot_cnt[k]++;
	if(k<4) tot_bd[k]+=*d(4,32); else tot_bd[k]-=*d(4,32);
	if(*u(4,5)<30000){
	  if(*u(1,1)==0){
	    *u(1,1)=*u(4,5); fasgeti(1);
	  }
	}
	else if(*u(4,5)<60000){
	  if(*u(2,1)==0){
	    *u(2,1)=*u(4,5)-30000; fasgeti(2);
	  }
	}
      }
    }
  }
	
  if(found==NO) {errnum=39;return NO;}
  if(ask_ok()==NO) return NO;
  tab_del(q);

  return YES;
}

static ask_ok()
{
  int16 k,key,z,mask_;

  for(k=0;k<3;k++){
    tot_cnt[3]+=tot_cnt[k];tot_cnt[7]+=tot_cnt[k+4];
    tot_bd[3]+=tot_bd[k];tot_bd[7]+=tot_bd[k+4];
  }
  FOREVER {
    scrget(1,18);
    z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_os3,"EUR"); scrifld(z++,fm_os3,"EUR");
    for(k=0;k<4;k++){
      scrifld(z++,fm_ou5,&tot_cnt[k]);
      scrifld(z++,fm_od8_2,&tot_bd[k]);
      scrifld(z++,fm_ou5,&tot_cnt[k+4]);
      scrifld(z++,fm_od8_2,&tot_bd[k+4]);
    }
    scrofld(z++,1,3,-1);
    scrofld(z++,2,3,-1);
    if(blokkeer){
      scrifld(z++,fm_os75,"Boeking OUDER dan archiveringsdatum.  Deze kan NIET geschrapt worden !");
    }
    mask_=0x0418; if(blokkeer) mask_=0x0410;
    key=scrupd(0xFFFF,mask_);
    if(key==105) return NO;
    if(key==111) ovlexit(-1);
    if(key==104 && blokkeer==NO) return YES;
    errnum=21;
  }
}

static tab_del(q)
int16 q;
{
  int16 k;
	fasunlck(-2);
  for(k=0;k<q;k++){
    chg4_1(recnr[k]);
    faskill(4);
  }
  fasinit(4);
  *s(4,2)=journl;
  *u(4,3)=volgnr;
	fasunlck(-1);
}

static initload()
{
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(4);

  sysget( 294,4,def_munt);
  sysget(1858,2,&last_arc);
	sysget(2300,2,&MinBkhDatum);if(MinBkhDatum<last_arc) MinBkhDatum=last_arc;
  pu_4_1=u(4,1); pl_4_1=l(4,1); len4_1=fldlen(4,1);
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
  }
}
