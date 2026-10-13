/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH2911GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH2911dat
#define ovlcod BKH2911cod
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

char ovldat[] = "bkh2911  00:01 22/10/98 (c) Jamadata"; // adden leveranciers vanuit search()

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define MAXFLD          120
#define STU             1

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern float *f();
extern double *d();

static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};

static int16 parmmain[8],stu=1,only_dsp;
static char taal_i,talen[4],naam51[51],oldnm[51], reserv[520];
static flag code,chk_intra;

ovlcod(parmval)
int16 parmval;
{
  copy((char *)parmcall,(char *)parmmain,sizeof parmmain);
  initload(); if(parmval==0 || parmval==1) only_dsp=YES;
  retcall=fichupd(parmval);
  copy((char *)parmmain,(char *)parmcall,sizeof parmcall);
  ovlexit(-1);
}
 
static initload()
{

  sysget(2212,4,talen);

  code=YES; if(fldlen(1,2)==0) code=NO;
  chk_intra=NO; if(fldlen(4,48)) chk_intra=YES;
}
 
static fichupd(mode)/* 0=display, 1=update, 2=add */
int16 mode;
{
  int16 k,curs=2,curs_taal,key,z,curspos_,kleur_;
  char *p_stu_3;
 
  if(mode==2 && *s(1,3)) zero(s(1,2),fldlen(1,2));
  p_stu_3=s(1,3);
  taal_i='\0';
  FOREVER{
    redo:
    scrnum=0;scrget(2,6);z=1;
    scrfld(z++,25,1);
    if(code) scrfld(z++,1,2); else scrofld(z++,1,1,-1);
    for(k=3;k<7;k++) scrfld(z++,1,k);
		if(!only_dsp && fldlen(29,1)) scraddpicto(8,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		ShowGoogleMapsButton(24,z-1,2,0,2,1,1); 
    for(k=7;k<16;k++) scrfld(z++,1,k);
    curs_taal=z;
    taal_upd(z++,16);
    for(k=17;k<MAXFLD;k++) scrfld(z++,1,k);
		if(fldlen(1,130)){
			kleur_=3; if(*s(1,130)) kleur_=4;
			scraddpicto(1,21,0,0,2,1,101,0,kleur_,"Email-instellingen"); 
		}
    if(mode==0 || only_dsp) curs=-1;/* NO update */
//    if(mode==0) curs=-1;
    key=scrupd(curs,0x07A9);curs=2;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==15 && only_dsp){only_dsp=NO;goto redo;}
		if(key==5001){DisplayEmailSettings(stu,mode);goto redo;}
		if(key==5008){
			fasinit(29); 
			if(*s(1,6)) copy(s(1,6),s(29,3),fldlen(1,6));
			else copy(s(1,5),s(29,3),fldlen(1,5));
			if(search(29,0)==0){ copy(s(29,2),s(1,5),fldlen(1,5)); copy(s(29,3),s(1,6),fldlen(1,6));}
			else curs=6;
			goto redo;
		}
    if(key==106){
      if(mode==2) return NO;
      else return YES;
    }
    k=*p_stu_3;
    if(key==101 && k=='\0') return NO;
		if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo;}
    if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;curs=3;goto redo;}
    if(code && *s(1,2)=='\0') {errnum=38;curs=2;goto redo;}
    if(taal_chk(16)) {curs=curs_taal;goto redo;}
    if(chk_intra){
      if(fldlen(1,35)) if(*s(1,35)=='\0'){errnum=38;curs=35;goto redo;}
      if(fldlen(1,36)) if(*i(1,36)==0){errnum=38;curs=36;goto redo;}
      if(fldlen(1,38)) if(*i(1,38)==0){errnum=38;curs=38;goto redo;}
    }
    if(key==110 && fldlen(1,125)) {DisplayMemo(stu);goto redo;}
    if(key==112 && *u(1,1)) {dsp_info(); goto redo;}
    if(key!=101 && key!=108) goto redo;
		if(fldlen(1,198)) *u(1,198)=procid;
		if(fldlen(1,199)) *u(1,199)=*u(25,2); // datum laatste update
    if(mode==1){
      errnum=fasupd(1);
      fasflush(0);
    }
    else if(mode==2 || mode==3){
      errnum=fasadd(1);
      fasflush(0);
    }
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
  return YES;
}
 

static DisplayEmailSettings(stu_,mode)
int16 stu_,mode;
{
  int z,key,curs=2;

	FOREVER{
		redo:;
		scrget(1,255);z=1;
		scrofld(z++,stu_,3,-1);
		scrfld(z++,stu_,21);
		scrfld(z++,stu_,130);
		if(mode==0 || only_dsp) curs=-1;/* NO update */
		key=scrupd(curs,0x1);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
	}
}

static DisplayMemo(stu_)
int16 stu_;
{
  int16 curs=2,dcurs_;
  int16 z,k,key;
					
  FOREVER{
    redo:;
    scrget(2,122); z=1;
    scrofld(z++,stu_,3,-1);
		if(stu_==1){
			for(k=125;k<128;k++) scrfld(z++,1,k);
		}
		else{
      for(k=5;k<10;k++) scrfld(z++,62,k);
		}
    dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0x80);
    if(key==15 && only_dsp){only_dsp=NO;goto redo;}
    if(key==108) break;
  }
}

static get_newcode()
{
  int16 j,k,g,code_len_,num_len_,fmt_len_;
  long min_kod_=1,max_kod_,lbd_;
  char str_[15],code_[15],kar_,kod_fmt_[15],buf1000[1000],kltcodeprefix_[2];


  if(stu!=1 && stu!=2 && stu!=6) return NO;
  if(fldlen(stu,2)==0) return NO;
  zero(code_,sizeof code_);
  copy(s(stu,1),buf1000,fldlen(stu,0));
	if(stu==2){
		sysget(2985,2,kltcodeprefix_);
		if(*s(stu,2)=='\0' && kltcodeprefix_[0]) *s(2,2)=kltcodeprefix_[0];
	}
#if FLAGVBE// nieuwe klantcode steeds K, leverancier L
	if(stu==2) {*s(2,2)='K';	min_kod_=3600;}
	if(stu==1 && *s(stu,2)=='\0') *s(1,2)='L';
#endif
#if FLAGWYN  || FLAGPCQ// nieuwe klantcode steeds 50000
	if(stu==2 && *s(stu,2)=='\0') *s(2,2)='5';
#endif
#if FLAGCRL// nieuwe klantcode steeds 6000
	if(stu==2 && *s(stu,2)=='\0') *s(2,2)='7';
#endif
  if(*s(stu,2)) copy(s(stu,2),code_,fldlen(stu,2));
  else if(stu==6 && *i(stu,9)) stcli_d(code_,(long)(*i(6,9)),2,0);
  for(code_len_=0;code_len_<fldlen(stu,2);code_len_++) if(code_[code_len_]=='\0') break;
  fasinit(stu);num_len_=0; zero(kod_fmt_,sizeof kod_fmt_);
  g=faskeyi(stu,1,1);
  if(g){
    num_len_=5; if(num_len_>fldlen(stu,2)) num_len_=fldlen(stu,2);
    fmt_len_=num_len_;
    for(k=code_len_;k<fmt_len_;k++) kod_fmt_[k]='n';
  }
  else {
    for(k=code_len_;k<fldlen(stu,2);k++){
      kar_=*(s(stu,2)+k);
      if(kar_=='\0') break;
      if(kar_>='0' && kar_<='9'){kod_fmt_[k]='n';num_len_++;}
      else kod_fmt_[k]=kar_;
    }
    fmt_len_=k;
  }
  if(code_len_>=fmt_len_ || num_len_<1){errnum=34; goto endsr;}
  copy(code_,kod_fmt_,code_len_);
  zero(str_,sizeof str_);
  for(k=0;k<num_len_;k++) str_[k]='9';
  max_kod_=val(str_)+1;
  for(lbd_=min_kod_;lbd_<max_kod_;lbd_++){
    fasinit(stu); copy(kod_fmt_,s(stu,2),fmt_len_);
    stcli_d(str_,lbd_,num_len_,0);
    j=0;
    for(k=code_len_;k<fmt_len_;k++){
      if(kod_fmt_[k]=='n') *(s(stu,2)+k)=str_[j++];
      else *(s(stu,2)+k)=kod_fmt_[k];
    }
    if(faskeyi(stu,1,0)) break;
  }
  if(lbd_<max_kod_) copy(s(stu,2),code_,fldlen(stu,2));
 
  endsr:;
  copy(buf1000,s(stu,1),fldlen(stu,0)); copy(code_,s(stu,2),fldlen(stu,2));
}



static bst_inp()
{
}
 
static dsp_info()
{
}

static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
}
 
static taal_upd(z,fld_)
int16 z,fld_;
{
  if(fldlen(STU,fld_)!=1) scrfld(z,STU,fld_);
  else{
    if(taal_i=='\0') taal_i=talen[*s(STU,fld_)];
    scrifld(z,fm_us1_U,&taal_i);
  }
}
								
static taal_chk(fld_)
int16 fld_;
{
  int16 k;
								
  if(fldlen(STU,fld_)==1){
    for(k=0;k<4;k++) if(taal_i==talen[k]) {*s(STU,fld_)=k;break;}
    if(k==4) {errnum=34;return YES;}
  }
  return NO;
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
 
