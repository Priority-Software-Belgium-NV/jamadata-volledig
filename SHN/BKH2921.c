/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH2921GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH2921dat
#define ovlcod BKH2921cod
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

char ovldat[] = "bkh2921  00:01 08/03/99 (c) Jamadata";  // adden klant vanuit search()
     // FLAGGRS : default prijs op bon op N
    // FLAGQIC : waarschuwing geven als er geen BTW-nummer is ingevuld
     //  FLAGWYN  : nieuwe klantcode steeds 50000
     //  FLAGEET  : deault GRB-extentie op 1 vanuit kassa en default prijs op bon op N
		 // FLAGVLO : nieuwe lev/klantcode met 9 
	 // FLAGSLB : nieuwe lev/klantcode met 9 

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define MAXFLD          120
#define STU             2

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

static int16 parmmain[8];
static char vptekst[100];
static char taal_i,talen[4],naam51[51],oldnm[51], reserv[1000],rel_naam[100];
static flag code,chk_intra,only_dsp,sys3762;
static uint16 def_qfak,stu=2;

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
  sysget(2222,2,&def_qfak);
  sysget(3762,2,&sys3762);
  sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);

  code=YES; 
	if(fldlen(2,2)==0) code=NO;
//	if(faskeyi(STU,1,0)==45) code=NO;
  chk_intra=NO; if(fldlen(4,48)) chk_intra=YES;
}
 
static fichupd(mode)/* 0=display, 1=update, 2 (of 12)=add */
int16 mode;
{
  int16 k,curs=2,curs_taal,key,z,curspos_,kleur_;
  uint16 fakklnr;
  char *p_stu_3;
 
  if(mode==12){sysget(3896,1,s(2,26));mode=2;} // toevoegen vanuit kassa : prijstype default op kassaprijs  zetten 
	else if(mode==2) *s(2,26)='0';
	   
	if(mode==2 && *s(2,3)) zero(s(2,2),fldlen(2,2));
  p_stu_3=s(2,3);
  taal_i='\0';
 
  if(mode==2){
    if(fldlen(2,25)>0) *s(2,25)='0';
		sysget(2994,1,s(2,26));
#if FLAGEET
    if(fldlen(2,25)>0) *s(2,25)='1';
#endif
    if(fldlen(62,1)) fasinit(62);
#if FLAGSAS
		copy("30",s(2,13),2);
		*s(2,41)='J'; // nettoprijs op JA
#endif
#if !FLAGGRS && !FLAGEET
    if(fldlen(2,35)>0) *s(2,35)='J';
#endif
#if FLAGOLH
    *f(2,80)=5;
#endif
    if(fldlen(2,36)) *u(2,36)=def_qfak;
    // if(fldlen(2,44)>0) *s(2,44)='J';
		if(((sys3762 & (1<<6))==0) && mode==2 && (stu==1 || stu==2) && fldlen(stu,2) && *s(stu,2)=='\0') get_newcode();
  }
#if FLAGEET
  if((mode==2 || mode==12) && fldlen(2,25)) *s(2,25)='1';
#endif
  if(fldlen(62,1)){
    fasinit(62);
		if(*u(2,1)){*u(62,2)=*u(2,1);faskeyi(62,1,0);}
  }
  if(fldlen(2,51)){
    zero(naam51,sizeof naam51);
    if(*u(2,51)){
      copy(s(2,1),reserv,fldlen(2,0));
      *u(2,1)=*u(2,51);
      if(fasgeti(2)==0) copy(p_stu_3,naam51,fldlen(2,3));
      copy(naam51,oldnm,fldlen(2,3));
      copy(reserv,s(2,1),fldlen(2,0));
    }
  }
  if(fldlen(2,52)==2){
    zero(&rel_naam[50],50);
    if(*u(2,52)){
      copy(s(2,1),reserv,fldlen(2,0));
      *u(2,1)=*u(2,52);
      if(fasgeti(2)==0) copy(p_stu_3,&rel_naam[0],fldlen(2,3));
      copy(&rel_naam[0],&rel_naam[50],fldlen(2,3));
      copy(reserv,s(2,1),fldlen(2,0));
    }
  }
  if(fldlen(2,27)){
    k=*s(2,26)-'0';if(k<0 || k>9) k=0;
    if(fldlen(6,PrNrs[k])==0) k=0;
    copy(&vptekst[k*10],s(2,27),fldlen(2,27));
  }
  FOREVER{
    redo:
    scrnum=0;scrget(2,7); z=1;
    scrfld(z++,25,1);
    if(code) scrfld(z++,2,2); else scrofld(z++,2,1,-1);
		if(fldlen(2,195)){
			if(*s(2,195)=='J') scraddpicto(11,z-1,2,0,2,1,32,0,4,"Mag NIET bestellen via webshop"); else scraddpicto(11,z-1,2,0,2,1,32,0,3,"Mag bestellen via webshop");
		}

    for(k=3;k<7;k++) scrfld(z++,2,k);
		if(!only_dsp && fldlen(29,1)) scraddpicto(8,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    ShowGoogleMapsButton(24,z-1,2,0,2,1,2); 
		for(k=7;k<=10;k++) scrfld(z++,2,k);
		if(fldlen(2,10)){
			if(*l(2,10)==0 || *l(2,10)==BTWNR_OFFSET) scrchat(z-1,0xFF);
			else if (*(s(2,10)+3) & 0x40){ // if(*l(2,10)>=BTWNR_OFFSET){
				scrchat(z-1,0xB);scraddpicto(10,z-1,4,0,2,1,86,0,4,"Maak BTW-plichtig"); 
			}
			else{
				scrchat(z-1,0xFF);scraddpicto(10,z-1,4,0,2,1,76,0,3,"Maak NIET BTW-plichtig"); 
			}
		}
		for(k=11;k<24;k++) scrfld(z++,2,k);
    curs_taal=z;
    taal_upd(z++,24);
    scrfld(z++,2,25);
    if(fldlen(2,27)){scrfld(-z,2,26);z++;}
    else scrfld(z++,2,26);
    for(k=27;k<51;k++) scrfld(z++,2,k);
    if(fldlen(2,51)>0) scrifld(z++,fm_us40,naam51); else z++;
		if(fldlen(2,52)==2) scrifld(z++,fm_us40,&rel_naam[0]); else scrfld(z++,2,52); // relatieadres
    for(k=53;k<MAXFLD;k++) scrfld(z++,2,k);
		if((fldlen(2,121) || fldlen(2,130))){
			kleur_=3;
			for(k=0;k<4;k++){
				if(fldlen(2,121+k) && *s(2,121+k)=='J') {kleur_=4;break;}
			}
			if(fldlen(2,128) && *s(2,128)) kleur_=4;
			scraddpicto(1,21,0,0,2,1,101,0,kleur_,"Email-instellingen"); 
		}
		if(fldlen(2,143)){
			kleur_=3;
			for(k=143;k<=146;k++){
				if(fldlen(2,k) && *s(2,k)) {kleur_=4;break;}
			}
			scraddpicto(7,4,0,0,2,1,101,0,kleur_,"Afwijkend leveradres"); 
		}
    if(mode==0 || only_dsp) curs=-1;/* NO update */
    key=scrupd(curs,0x3A9);curs=2;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==15 && only_dsp){only_dsp=NO;goto redo;}
		if(key==5001){DisplayEmailSettings(stu,mode);goto redo;}
		if(key==5007){DisplayLeveradres(stu);goto redo;}
		if(key==5008){
			fasinit(29);
			if(*s(2,6)) copy(s(2,6),s(29,3),fldlen(2,6));
			else copy(s(2,5),s(29,3),fldlen(2,5));				
			if(search(29,0)==0){ copy(s(29,2),s(2,5),fldlen(2,5)); copy(s(29,3),s(2,6),fldlen(2,6));}
			else curs=6;
			goto redo;
		}

    if(key==106){
      if(mode==2) return NO;
      else return YES;
    }
		if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo;}
		if(key==5010){
			if (*(s(2,10)+3) & 0x40) *(s(2,10)+3)  &= 0xBF; else *(s(2,10)+3)  |= 0x40;
//			if(*l(2,10)>=BTWNR_OFFSET) *l(2,10)-=BTWNR_OFFSET;
//			else *l(2,10)+=BTWNR_OFFSET;
			goto redo;
		}		
		if(key==5011 && fldlen(2,195)){
			if(*s(2,195)=='J') *s(2,195)='N'; else *s(2,195)='J';
			goto redo;
		}		
    if(fldlen(2,27)){
      k=*s(2,26)-'0';if(k<0 || k>9) k=0;
      if(fldlen(6,PrNrs[k])==0) k=0;
      copy(&vptekst[k*10],s(2,27),fldlen(2,27));
      if(key==18){curs=curspos_+1;goto redo;}
    }
    k=*p_stu_3;
    if(key==101 && k=='\0') return NO;
		if(mode==1 && key==15 && only_dsp){only_dsp=NO;goto redo;}
    if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;curs=3;goto redo;}
    if(code && *s(2,2)=='\0') {errnum=38;curs=2;goto redo;}
    if(taal_chk(24)) {curs=curs_taal;goto redo;}

    if(fldlen(2,51)){
      if(naam51[0]=='\0') {*u(2,51)=0;oldnm[0]='\0';}
      else if(cmpstr(naam51,oldnm,fldlen(2,3))){
				copy(s(2,1),reserv,fldlen(2,0));
				fasinit(2);
				copy(naam51,s(2,3),fldlen(2,3));
				k=search(2,0); if(k==YES && errnum==0) errnum=39;
				if(!errnum){
					copy(s(2,3),naam51,fldlen(2,3));
					copy(s(2,3),oldnm,fldlen(2,3));
				}
				fakklnr=*u(2,1);
				copy(reserv,s(2,1),fldlen(2,0));
				*u(2,51)=fakklnr;
				if(errnum) {curs=51;goto redo;}
      }
    }
    if(fldlen(2,52)==2){
      if(rel_naam[0]=='\0') {*u(2,52)=0;rel_naam[50]='\0';}
      else if(cmpstr(&rel_naam[0],&rel_naam[50],fldlen(2,3))){
				copy(s(2,1),reserv,fldlen(2,0));
				fasinit(2);
				copy(rel_naam,s(2,3),fldlen(2,3));
				k=search(2,0); if(k==YES && errnum==0) errnum=39;
				if(!errnum){
					copy(s(2,3),&rel_naam[0],fldlen(2,3));
					copy(s(2,3),&rel_naam[50],fldlen(2,3));
				}
				fakklnr=*u(2,1);
				copy(reserv,s(2,1),fldlen(2,0));
				*u(2,52)=fakklnr;
				if(errnum) {curs=51;goto redo;}
      }
    }
    if(chk_intra){
      if(fldlen(2,74)) if(*s(2,74)=='\0'){errnum=38;curs=74;goto redo;}
      if(fldlen(2,75)) if(*i(2,75)==0){errnum=38;curs=75;goto redo;}
      if(fldlen(2,77)) if(*i(2,77)==0){errnum=38;curs=77;goto redo;}
    }

//    if(key==109 && fldlen(2,120)) {bst_inp();goto redo;}
    if(key==110 && fldlen(62,1)) {klt_memo(mode);goto redo;}
//    if(key==112 && *u(2,1)) {dsp_info(); goto redo;}
    if(key!=101 && key!=108) goto redo;
		if(fldlen(2,198)) *u(2,198)=procid;
		if(fldlen(2,199)) *u(2,199)=*u(25,2); // datum laatste update
    if(mode==1){
			if(only_dsp==NO){
				errnum=fasupd(2);
				if(!errnum && fldlen(62,1)){
					*u(62,2)=*u(2,1);
					if(*u(62,1)) fasupd(62); else fasadd(62);
				}
				fasflush(0);
			}
    }
    else if(mode==2 || mode==3 || mode==12){
			if(chk_dblbtw()==NO) goto redo;
#if FLAGQIC
			if(*l(2,10)==0 && fldlen(2,137) && *s(2,137)=='\0'){
			  if(DisplayWarning("Geen BTW-nummer ingegeven, toch doorgaan?", 605,1)==NO) goto redo;
			}
#endif
			if(DisplayWarning("Wenst U echt deze klant toe te voegen?",605,1)!=YES) goto redo;
      errnum=fasadd(2);
      if(!errnum && fldlen(62,1)){
				*u(62,2)=*u(2,1); fasadd(62);
      }
      fasflush(0);
    }
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
  return YES;
}

static chk_dblbtw()
{
  int16 ok_=YES;
  uint16 key,krec_,g,n;
  long btwnr_,*p_btwnr_;
	char buf1000[1000];

  p_btwnr_=l(2,10);btwnr_=*p_btwnr_;krec_=*u(2,1);
  btwnr_=*p_btwnr_ & 0xBFFFFFFF;
  if(btwnr_==000000000 || btwnr_==999999999) return YES;
  copy(s(2,1),buf1000,fldlen(2,0));
  fasinit(2); n=0;scrget(1,7);scrupd(-3,0);
  FOREVER{
    *u(2,1)=++n;
    g=fasgeti(2);
    if(g==47)break;
    if(g!=46 && n!=krec_){/* deleted record */
      if(*p_btwnr_==btwnr_) {ok_=NO;break;}
    }
  }
  if(ok_==NO){
    scrget(1,169);
    scrifld(10,VarTextFmt(40,0),"BTW-nummer is al gebruikt door :");
    scrfld(12,2,3);
    scrifld(18,VarTextFmt(25,0),"Toch doorgaan ???");
    key=scrupd(-1,0x18);
    if(key==104) ok_=YES;
  }
  copy(buf1000,s(2,1),fldlen(2,0));
  return ok_;
}

static DisplayLeveradres(stu_)
int16 stu_;
{
  int z,k,key,curs=2;

	FOREVER{
		redo:;
		scrget(1,275);z=1;
		scrofld(z++,stu_,3,-1);
 		for(k=143;k<=146;k++) scrfld(z++,stu_,k);
		key=scrupd(curs,0x1);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
	}
}


static bst_inp()
{
}
 
static dsp_info()
{
}

static get_newcode()
{
  int16 j,k,g,code_len_,num_len_,fmt_len_;
  long min_kod_=1,max_kod_,lbd_;
  char str_[15],code_[15],kar_,kod_fmt_[15],buf1000[1000],kltcodeprefix_[2];


  if(stu!=1 && stu!=2 && stu!=6) return NO;
  if(fldlen(stu,2)==0) return NO;
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
#if FLAGVLO  || FLAGSLB // nieuwe klantcode steeds 9000
	if(stu==2 && *s(stu,2)=='\0') *s(2,2)='9';
#endif
  zero(code_,sizeof code_);
  copy(s(stu,1),buf1000,fldlen(stu,0));
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


static DisplayEmailSettings(stu_,mode)
int16 stu_,mode;
{
  int z,k,key,curs=2,dcurs_;

	FOREVER{
redo:;
		if(stu_==2)
#if FLAGCOC // CC adres bij klant is voor facturen/rappels
		scrget(2,503);
#else
		scrget(1,276);
#endif		
		else scrget(1,255);
		z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0X19A");
		if(stu_==2 && fldlen(7,1) && *u(stu_,1)) scraddpicto(1,0,75,22,4,2,570,0,0,"Mail"); 
		scrofld(z++,stu_,3,-1);
		scrfld(z++,stu_,21);
		scrfld(z++,stu_,130);
		if(stu_==2){
#if !FLAGCOC
		  scrfld(z++,stu_,129);
#endif
  		for(k=0;k<8;k++) scrfld(z++,stu_,121+k);
		}
		dcurs_=curs; if(mode==0 || only_dsp) dcurs_=-1;
		key=scrupd(dcurs_,0x1);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==5001){
			ShowSavedDocument(stu,(long)(*u(stu_,1)),0,0,0) ;
      goto redo;
    }
		if(stu_==2 && !only_dsp){
			if(*s(stu_,21)=='\0'){
			  for(k=0;k<8;k++) if(fldlen(stu_,121+k) && *s(stu_,121+k)=='J') break;
			  if(k<8){errnum=38;curs=2;goto redo;}
			}
//			if(fldlen(2,128) && *s(2,128)=='J' && (*s(2,121)=='J' || *s(2,122)=='J')){curs=5;errnum=72;goto redo;}
		}
		if(key==101) break;
	}
}

static klt_memo(mode)
int16 mode;
{
  int16 z,k,key,curs=2;
								
  FOREVER{
    redo:;
    scrget(2,122); z=1;
    scrofld(z++,2,3,-1);
    for(k=5;k<10;k++) scrfld(z++,62,k);
    if(mode==0 || only_dsp) curs=-1;
    key=scrupd(curs,0x80);curs=2;
		if(key==15 && only_dsp){only_dsp=NO;goto redo;}
    if(key==108) break;
  }
}


#if 0
fichupd(mode)
int16 mode;
{
  int16 k,curs,curs_taal,key,z;
  uint16 fakklnr;
  char *p_stu_3;
  flag scrdata=YES;
 
  p_stu_3=s(STU,3);
  taal_i='\0';
  FOREVER{
    curs=2;
    if(fldlen(STU,51)){
      zero(naam51,sizeof naam51);
      if(*u(STU,51)){
	copy(s(STU,1),reserv,fldlen(STU,0));
	*u(STU,1)=*u(STU,51);
	if(fasgeti(STU)==0) copy(p_stu_3,naam51,fldlen(STU,3));
	copy(reserv,s(STU,1),fldlen(STU,0));
      }
    }

    redo:;
    if(scrget(2,7)) scrdata=YES;
    if(scrdata){
      z=1;
      scrfld(z++,25,1);
      if(code) scrfld(z++,2,2); else scrofld(z++,2,1,-1);
      for(k=3;k<24;k++) scrfld(z++,2,k);
      curs_taal=z;
      taal_upd(z++,24);
      for(k=25;k<51;k++) scrfld(z++,2,k);
      if(fldlen(STU,51)) scrifld(z++,fm_us40,naam51); else z++;
      for(k=52;k<MAXFLD;k++) scrfld(z++,2,k);
      scrdata=NO;
    }
    key=scrupd(-1,0x00A1);curs=2;
    if(key==106) goto end_NO;
    k=*p_stu_3;
    if(key==101 && k=='\0') goto end_NO;

    if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;curs=3;goto redo;}
    if(code && *s(STU,2)=='\0') {errnum=38;curs=2;goto redo;}
    if(taal_chk(24)) {curs=curs_taal;goto redo;}

    if(fldlen(STU,51)){
      if(naam51[0]=='\0') *u(STU,51)=0;
      else{
	copy(s(STU,1),reserv,fldlen(STU,0));
	fasinit(STU);
	copy(naam51,p_stu_3,fldlen(STU,3));
	k=ovlcall(2902,0);
	fakklnr=*u(STU,1);
	copy(reserv,s(STU,1),fldlen(STU,0));
	*u(STU,51)=fakklnr;
	if(errnum) {curs=51;goto redo;}
      }
    }
    if(chk_intra){
      if(fldlen(STU,74)) if(*s(STU,74)=='\0'){errnum=38;curs=74;goto redo;}
      if(fldlen(STU,75)) if(*i(STU,75)==0){errnum=38;curs=75;goto redo;}
      if(fldlen(STU,77)) if(*i(STU,77)==0){errnum=38;curs=77;goto redo;}
    }
    if(*u(STU,1)==0) errnum=fasadd(STU); else errnum=fasupd(STU);
    fasflush(0);
    if(errnum==48 || errnum==49) errnum=9;
    if(!errnum) break;
  }
  endsr:;
  if(key==101) goto end_NO;
  return YES;
  end_NO:;
  return NO;
}
#endif
 
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
 
