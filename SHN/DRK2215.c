/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK2215GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK2215dat
#define ovlcod DRK2215cod
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

char ovldat[] = "drk2215  00:01 10/11/10 (c) Jamadata"; /* selectie artikels op lijsten */
// FLAGCOC : Datum prijswijziging : u(6,67) ipv 6,11

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXFLD          201
#define flag            uint16
#define VOLL            0
#define STAT            2
#define PRIX            4
#define ETIK            5
#define KPRX            6

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
static float get_prx();
extern double *d();
extern double valu_cnv();
					
extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];


static char fmt[40],vptekst[100],stuksprx[10],oldnm[50],nm_fil[6],nm_loc[10][6];
static uint16 sys3894,stu=6,SelectMode;
static int16 fld_nr[8]={6,22,7,8,20,21,23,24};



static uint16 *pu_2_1,*pu_6_1;

static int16 retmain;

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
 
static flag klcd,lvcd;
static char *selp_txt[6]={"Ondergrens (>)","Ondergrens (> of =)",
		"Bovengrens (<)","Bovengrens (< of =)",
		"Gelijk","Niet gelijk"};

ovlcod(parmval) // Bit0 =geen klantgerelateerde selecties, Bit1=prijslijst/bestelbon, Bit2 : allow_blocked_art, Bit 7=eerst selecties wissen
int16 parmval;
{
  uint16 krec_,lrec_;
 
  retcall=YES;
  initload();

  SelectMode=parmval;
	if(SelectMode&0x80) WisSelecties();
  if(seldata.tab_read==NO) fill_tabel();
  if(seldata.prx_klt) seldata.inq_klt=seldata.prx_klt;
  krec_=*u(2,1); lrec_=*u(1,1);
  retcall=select_art();
  if(krec_){fasinit(2);*u(2,1)=krec_;fasgeti(2);}
  if(lrec_){fasinit(1);*u(1,1)=lrec_;fasgeti(1);}
  ovlexit(-1);
}

static initload()
{
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  if(fldlen(8,1)) fileopen(8);
  if(fldlen(9,1)) fileopen(9);
  if(fldlen(60,1)) fileopen(14);
  if(fldlen(66,1)) fileopen(12);
	if(fldlen(16,1)) fileopen(13);

	sysget(2770,60,(char *)&nm_loc[0][0]);
	sysget(3894,2,&sys3894);
  sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  sysget(4670,6,stuksprx);
	sysget(4780,4,&stuksprx[6]);

  pu_6_1=u(6,1);
  pu_2_1=u(2,1);
 
}

static fill_tabel()/* vult recs in tabel 0-499 lev, 500-599 grp */
{
  int16 g,k,mode_;
  uint16 *pu_1_1,*pu_6_7,ori_lev_;

  pu_1_1=u(1,1);pu_6_7=u(6,7);
	ori_lev_=*u(1,1);
  scrget(1,170);scrifld(10,fm_os63,"De selectietabellen worden nu aangemaakt...");scrupd(-3,0);
  zero((char *)&seldata.tb[0].rec,sizeof seldata.tb);seldata.inq_klt=0;
  fasinit(1); seldata.p_max_lev=0; mode_=1;
  FOREVER{
    if(faskeyi(1,2,mode_)) break; mode_=2;
    fasinit(6); *pu_6_7=*pu_1_1;
    g=faskeyi(6,4,1);
    if(g==0 && *pu_6_7==*pu_1_1) seldata.tb[seldata.p_max_lev++].rec=*pu_1_1;
    if(seldata.p_max_lev>=500) break;
  }
  seldata.p_max_grp=0;
  for(k=1;k<100;k++){
    fasinit(52);*u(52,1)=k;
    g=fasgeti(52);
    if(g==0 && *s(52,14)) seldata.tb[500+seldata.p_max_grp++].rec=k;
  }
  WisSelecties();
	if(ori_lev_) {fasinit(1);*u(1,1)=ori_lev_;fasgeti(1);}
}

static select_art()
{
  int16 z,key,curs=1,upd_klt_=NO;
  char choice;

  fasinit(2);if(seldata.inq_klt){*pu_2_1=seldata.inq_klt;fasgeti(2);}
  seldata.klt_st_used=NO; seldata.sklt_used=NO;seldata.safsp_used=NO;
/*  if(mode!=PRIX || inq_klt==0 || fldlen(2,120)==0) sklt_used=NO; */
  FOREVER{
    redo:;
    scrnum=0;scrget(2,47); z=1; scraddpicto(50,0,76,0,4,2,105,1,7,"^!B2215A");
		if(seldata.slev_used) {scrifld(z++,VarTextFmt(14,0)," Geselecteerd ");scrchat(z-1,0x9);} else z++;
    if(seldata.sgrp_used==YES) {scrifld(z++,VarTextFmt(14,0)," Geselecteerd ");scrchat(z-1,0x9);} else z++;
    if(fldlen(6,101)){
      if(seldata.inq_merk) {scrifld(z++,VarTextFmt(14,0)," Geselecteerd ");scrchat(z-1,0x9);} else z++;
    } else {scrifld(z++,VarTextFmt(15,0)," Niet mogelijk ");scrchat(z-1,0xB);}
    if(seldata.selp_use) {scrifld(z++,VarTextFmt(14,0)," Geselecteerd ");scrchat(z-1,0x9);} else z++;
    if(seldata.dt_p_beg || seldata.dt_p_end) {scrifld(z++,VarTextFmt(14,0)," Geselecteerd ");scrchat(z-1,0x9);} else z++;
    if(SelectMode&0x01 || fldlen(2,120)==0) {scrifld(z++,VarTextFmt(15,0)," Niet mogelijk ");scrchat(z-1,0xB);}
		else if(seldata.inq_klt==0) {scrifld(z++,VarTextFmt(12,0)," Geen klant ");scrchat(z-1,0xB);}
    else if(seldata.sklt_used) {scrifld(z++,VarTextFmt(14,0)," Geselecteerd ");scrchat(z-1,0x9);}
    else z++;
    if((SelectMode&0x01 && fldlen(16,10)==0) || !(fldlen(16,10) || fldlen(60,2) || fldlen(9,27))) {scrifld(z++,VarTextFmt(15,0)," Niet mogelijk ");scrchat(z-1,0xB);}
		else if(seldata.klt_st_used) {scrifld(z++,VarTextFmt(14,0)," Geselecteerd ");scrchat(z-1,0x9);}
		else if(seldata.inq_klt==0 && fldlen(66,11)==0 && fldlen(16,8)==0) {scrifld(z++,VarTextFmt(12,0)," Geen klant ");scrchat(z-1,0xB);}
    else z++;
    if(SelectMode&0x01 || ovltest(230)==0) {scrifld(z++,VarTextFmt(15,0)," Niet mogelijk ");scrchat(z-1,0xB);}
		else if(seldata.inq_klt==0) {scrifld(z++,VarTextFmt(12,0)," Geen klant ");scrchat(z-1,0xB);}
    else if(seldata.safsp_used) {scrifld(z++,VarTextFmt(14,0)," Geselecteerd ");scrchat(z-1,0x9);}
    else z++;
    if(fldlen(6,33)){
			if(seldata.sel_met_stock) {scrifld(z++,VarTextFmt(14,0)," Geselecteerd ");scrchat(z-1,0x9);} else z++;
    } else {scrifld(z++,VarTextFmt(15,0)," Niet mogelijk ");scrchat(z-1,0xB);}
    if(!(SelectMode&0x01) && upd_klt_){
      scrfld(z++,2,3); z++;
    }
    else{
      scrofld(z++,2,3,-1);
      scrifld(z++,fm_menu,&choice);
    }
    key=scrupd(curs,0x05C9);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==111) ovlexit(-1);
    if(key==101 || key==111) return YES;
    if(!(SelectMode&0x01) && *s(2,3)){
      if(search(2,0)){upd_klt_=YES;goto redo;}
      else seldata.inq_klt=*pu_2_1;
    } 
		else {
			seldata.inq_klt=0;seldata.safsp_used=NO;seldata.sklt_used=NO;
			if(seldata.inq_filiaal==0) seldata.klt_st_used=NO;
		}
    if(key==104){
      if(upd_klt_) upd_klt_=NO; else upd_klt_=YES;
      goto redo;
    }
	if(key==109){WisSelecties();goto redo;}
    switch(choice){
      case '1': dsp_tabel(0);break;
      case '2': dsp_tabel(1); break;
      case '3': if(fldlen(6,101)) dsp_merk(); break;
      case '4': selp_ask(); break;
      case '5': dsp_plim(); break;
      case '6': if(!(SelectMode&0x01) && seldata.inq_klt && fldlen(2,120)){
				  if(seldata.sklt_used) seldata.sklt_used=NO; else seldata.sklt_used=YES;
				} else errnum=34;
				choice='\0';
				break;
      case '7': if(!(SelectMode&0x01 && fldlen(16,10)==0) && (seldata.inq_klt || fldlen(16,10)) && (fldlen(16,10) || fldlen(60,2) || fldlen(9,27))){
				  if(seldata.klt_st_used) {seldata.klt_st_used=NO;seldata.dt_s_beg=*u(25,2)-730;seldata.dt_s_end=0;seldata.inq_filiaal=0;}
					else if(AskHisPeriode()) seldata.klt_st_used=YES;
				} else errnum=34;
				choice='\0';
			    break;
      case '8': if(!(SelectMode&0x01) && seldata.inq_klt){
				  if(seldata.safsp_used) seldata.safsp_used=NO; else seldata.safsp_used=YES;
				} else errnum=34;
				choice='\0';
				break;
      case '9': dsp_stockselectie(); break;
      default : break;
    }
    if(key==108) break;
  }
  return NO;
}
 
static WisSelecties()
{
  int k;
      
  seldata.selp_use=NO;seldata.slev_used=NO;seldata.sgrp_used=NO;seldata.safsp_used=NO;
	seldata.sklt_used=NO;seldata.klt_st_used=NO;seldata.inq_filiaal=0;seldata.sel_met_stock=0;
  seldata.dt_p_beg=0;seldata.dt_p_end=0; seldata.dt_s_beg=*u(25,2)-730;seldata.dt_s_end=0;
	seldata.inq_merk=0;
	if(SelectMode&0x04) seldata.allow_blocked_art=1;	
	for(k=0;k<600;k++) seldata.tb[k].select='J';
	if(SelectMode&0x02 && fldlen(52,24)){ // prijslijst + bestelbons
		for(k=500;k<600;k++){
			if(seldata.tb[k].rec==0) break;
			fasinit(52);*u(52,1)=seldata.tb[k].rec;fasgeti(52);
			if(*s(52,24)=='J') {seldata.tb[k].select='N';seldata.sgrp_used=2;} // automatisch selectie afzetten
		}
	}
	selp_wis();
}
 
int DirCall_DRK2215_SelectArtikel()
{
  int16 k,retbad_,mode16_;
  uint16 dt_;
	long last_hisrec_;

	if(seldata.allow_blocked_art==0 && fldlen(6,200) && *u(6,200) && used(&seldata.selp_bf[2][s(6,200)-s(6,1)],fldlen(6,200))==NO) return NO; // artikel geblokkeerd, wel checken indien selectie
  if(fldlen(2,120) && seldata.inq_klt && seldata.sklt_used){
    for(k=0;k<fldlen(2,120)/2; k++){
      if(*(uint16 *)(s(2,120)+k*2)==*pu_6_1) break;
    }
    if(k>=fldlen(2,120)/2) return NO;
  }
  if(seldata.dt_p_beg || seldata.dt_p_end){
    dt_=0;
#if FLAGCOC
		if(fldlen(6,67)==2) dt_=*u(6,67);
#else
    if(fldlen(6,11)) dt_=*u(6,11);
#endif
    if(fldlen(6,105) && *u(6,105)) dt_=*u(6,105);
    if(seldata.dt_p_beg && dt_<seldata.dt_p_beg) return NO;
    if(seldata.dt_p_end && dt_>seldata.dt_p_end) return NO;
  }
  if(seldata.inq_merk && fldlen(6,101)){
    if(*u(6,101)!=seldata.inq_merk) return NO;
  }

  if(seldata.sel_met_stock && fldlen(6,33)){
		if(seldata.sel_met_stock==99){
			if(*f(6,33)<=0)  return NO;
		}
		else{
			fasinit(66);*u(66,2)=*u(6,1); if(faskeyi(66,1,0)) return NO;
      if(*f(66,11+(seldata.sel_met_stock-1)*15)<=0) return NO;
    }
  }
  if(seldata.safsp_used){
    fasinit(9);*u(9,2)=*pu_2_1;*u(9,3)=*pu_6_1;
		if(faskeyi(9,1,0)) return NO;
	  for(k=0;k<8;k++) if(fld_nr[k] && *f(9,fld_nr[k])) break; // testinhoud
		if(k>=8) return NO;
//		for(k=0;k<9;k++) if(fldlen(9,88+k*5) && *f(9,88+k*5)) return YES;
	}
	if((seldata.inq_klt || seldata.inq_filiaal) && seldata.klt_st_used){
    if(fldlen(16,1)){
			last_hisrec_=*l(16,1);
			if(seldata.inq_filiaal){
				retbad_=YES;
        fasinit(16);*u(16,3)=seldata.dt_s_beg; *l(16,20)=*pu_6_1;mode16_=1;
 	  		FOREVER{
					next16:;
					if(faskeyi(16,5,mode16_)) {retbad_=YES;break;}  mode16_=2;
					if(*l(16,20)!=*pu_6_1) {retbad_=YES;break;}
					if(seldata.dt_s_end && *u(16,3)>seldata.dt_s_end) {retbad_=YES;break;}
					if(seldata.inq_klt && *l(16,10)!=seldata.inq_klt) goto next16;
					if(seldata.inq_filiaal && *u(16,8)!=seldata.inq_filiaal && !(seldata.inq_filiaal==99 && *u(16,8)==0)) goto next16;
					retbad_=NO; break;
				}
			}
			else{
				fasinit(16);*l(16,10)=seldata.inq_klt;*l(16,20)=*pu_6_1;
				*u(16,3)=seldata.dt_s_beg;    // laatste 2 jaar 
				if(seldata.inq_klt) k=faskeyi(16,1,1); 
				else k=faskeyi(16,5,1); 
				retbad_=NO;
				if(k) retbad_=YES;
				else if(*l(16,20)!=*pu_6_1) retbad_=YES;
				else if(seldata.inq_klt && *l(16,10)!=seldata.inq_klt) retbad_=YES;
				if(seldata.dt_s_end && *u(16,3)>seldata.dt_s_end) retbad_=YES;
			}
			fasinit(16);if(last_hisrec_){*l(16,1)=last_hisrec_;fasgeti(16);}
			if(retbad_) return NO;
    }
    else if(fldlen(60,1)){
      fasinit(60);*l(60,2)=seldata.inq_klt;*l(60,22)=*pu_6_1;
      if(faskeyi(60,1,0)) return NO;
    }
    else if(fldlen(9,1)){
      fasinit(9);*u(9,2)=seldata.inq_klt;*u(9,3)=*pu_6_1;
      if(faskeyi(9,1,0)) return NO;
    }
  }

  if(selp_tst()==NO) return NO;
  if(seldata.slev_used){
    for(k=0;k<seldata.p_max_lev;k++) if(*u(6,7)==seldata.tb[k].rec) break;
    if(k>=seldata.p_max_lev || seldata.tb[k].select!='J') return NO;
  }
  if(seldata.sgrp_used){
    for(k=500;k<500+seldata.p_max_grp;k++) if(*u(6,9)==seldata.tb[k].rec) break;
    if(k>=500+seldata.p_max_grp || seldata.tb[k].select!='J') return NO;
  }
  return YES;
}

static bit(byte_,bit_)
char byte_;
int16 bit_;
{
  if(byte_ & 1<<bit_) return YES;
  return NO;
}

static selp_tst()/* 00.02 */
{
  int16 g,k,type,parm,f_len,index;
  char fldtype,*stu_base,*adres,ret;

  if(seldata.selp_use==NO) return YES;
  stu_base=s(stu,1);
  for(k=2;k<MAXFLD;k++){
    f_len=fieldspc(stu,k,&seldata.selp_fld,seldata.selp_des);
    if(f_len>0){
      fldtype=(seldata.selp_des[1] & 0x38)/8;
      switch(fldtype){
	case 0:/* date */
	  type=1;parm=11;
	  break;
	case 1:/*string*/
	  type=2;
	  break;
	case 2:/*num*/
	  type=1;parm=seldata.selp_des[1]&7;
	  break;
	case 3:/*bt#*/
	  type=1;parm=3;
	  break;
	case 4:/* rek# */
	  type=3;parm=5;
	  break;
	case 5:/* grb */
	  type=1;parm=3;
	  break;
	default: type=0;break;
      }
      index=seldata.selp_fld-stu_base;
      for(g=0;g<4;g++){
	adres=&seldata.selp_bf[g][index];
	if(used(adres,f_len)){
	  ret=3;
	  switch(type){
	    case 1: ret=comp_num(adres,seldata.selp_fld,parm); break;
	    case 2: ret=comp_str(adres,seldata.selp_fld,f_len); break;
	    case 3: ret=comp_byt(adres,seldata.selp_fld,f_len); break;
	  }
	  if(ret==3) goto next;
	  if(g==0 && (ret==1 || (seldata.selp_ge && ret==0))) goto next;
	  if(g==1 && (ret==2 || (seldata.selp_le && ret==0))) goto next;
	  if(g==2 && ret==0) goto next;
	  if(g==3 && ret!=0) goto next;
	  return NO;
	}
	next:;
      }
    }
  }
  return YES;
}

static used(b,len)
char *b;
int16 len;
{
  while(len-->0)
    if(*b++!=0xFE) return YES;
  return NO;
}
 
static comp_num(p1,p2,type)
char *p1, *p2;
int16 type;
{
  int16 ret;
  uint16 jj,mm,dd, oldp2;
 
  if(type==11){
    oldp2=*(uint16 *)p2;
    if(*(uint16 *)p1>=44 && *(uint16 *)p1<=409){
      jddate(*(uint16 *)p2,&jj,&mm,&dd);
      *(uint16 *)p2=datejd(1892,mm,dd);
    }
  }
  switch(type){
    case 0:
      if(*(int16 *)p1 < *(int16 *)p2) ret=1;
      else if(*(int16 *)p1 > *(int16 *)p2) ret=2;
      else ret=0;
      break;
    case 1:
    case 11:
      if(*(uint16 *)p1 < *(uint16 *)p2) ret=1;
      else if(*(uint16 *)p1 > *(uint16 *)p2) ret=2;
      else ret=0;
      if(type==11) *(uint16 *)p2=oldp2;
      break;
    case 3:
      if(*(long *)p1 < *(long *)p2) ret=1;
      else if(*(long *)p2 > *(long *)p2) ret=2;
      else ret=0;
      break;
    case 4:
      if(*(float *)p1 < *(float *)p2) ret=1;
      else if(*(float *)p1 > *(float *)p2) ret=2;
      else ret=0;
      break;
    case 5:
      if(*(double *)p1 < *(double *)p2) ret=1;
      else if(*(double *)p1 > *(double *)p2) ret=2;
      else ret=0;
      break;
    default:
      ret=3;
      break;
  }
  return ret;
}
 
static comp_str(p1,p2,len)
char *p1, *p2;
int16 len;
{
  char b1,b2;
  int16 len1,len2;

  len1=len;len2=len;
  FOREVER{
    FOREVER{
      if(!(b1=*p1++)){len1=-1; break;}/* 0-byte found */
      if(!len1--) break;
      if(b1>='a' && b1<='z') b1=b1-'a'+'A';
      if((b1>='A' && b1<='Z') || (b1>='0' && b1<='9') || (b1=='?')) break;
      if(b1=='*') return 0;
    }
    FOREVER{
      if(!(b2=*p2++)){len2=-1; break;}/* 0-byte found */
      if(!len2--) break;
      if(b2>='a' && b2<='z') b2=b2-'a'+'A';
      if((b2>='A' && b2<='Z') || (b2>='0' && b2<='9')) break;
    }
    if(len1<0 || len2<0){
      if(len1<0 && len2<0) return 0;
      if(len1<0) return 1; else return 2;
    }
    if(b1=='?') b1=b2;
    if(b1<b2) return 1;
    if(b1>b2) return 2;
  }
}
 
static comp_byt(p1,p2,len)
int16 len;
char *p1,*p2;
{
  while(len-->0){
    if(*p1<*p2) return 1;
    if(*p1>*p2) return 2;
    p1++; p2++;
  }
  return 0;
}
 
static selp_wis()
{
  int16 j;

  for(j=0;j<sizeof seldata.selp_bf;j++) *(&seldata.selp_bf[0][0]+j)=0xFE;
}

static AskHisPeriode()
{
  int16 key,z;

	if(fldlen(16,10)==0) return YES;
	FOREVER{								
		redo:;
		scraddf(-1,0,0,0);z=1;
		scraddf(z++,10,2,0);scraddf(z++,10,24,2);	scraddf(z++,10,33,0);	scraddf(z++,10,40,2);
		scraddf(z++,12,2,0);	scraddf(z++,12,35,2);
		scraddf(z++,23,1,8);   scraddf(z++,23,16,8);
		z=1;
		scrifld(z++,VarTextFmt(22,0),"Periode historieken :");
		scrifld(z++,fm_udat,&seldata.dt_s_beg);
		scrifld(z++,VarTextFmt(7,0),"t.e.m. ");
		scrifld(z++,fm_udat,&seldata.dt_s_end);
		if(fldlen(66,11) && fldlen(16,8)){
			scrifld(z++,VarTextFmt(35,0),"Selectie 1 filiaal (1-10 of 99): ");
			scrifld(z++,fm_uu2,&seldata.inq_filiaal);
		} else z+=2;

		scrifld(z++,VarTextFmt(14,0)," F6 annuleer ");scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
		key=scrupd(1,0xA1);
		if(key==101 || key==108) break;
		if(key==106) return NO;
	}
	if(seldata.inq_klt==0 && seldata.inq_filiaal==0) return NO;
	return YES;
}

static dsp_merk()
{
  int16 key,z;
  char oldnm[50];


  fasinit(1);*u(1,1)=seldata.inq_merk; if(*u(1,1)) fasgeti(1);
  copy(s(1,3),oldnm,fldlen(1,3));
									
  redo:;
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,10,2,0);
  scraddf(z++,10,30,2);
  scraddf(z++,23,1,8);   scraddf(z++,23,17,8);
									
  z=1;
  scrifld(z++,fm_os63,"Selectie merk/producent  :");
  scrfld(z++,1,3);
  scrifld(z++,fm_os15," F7 zoek op ");scrifld(z++,fm_os15," F8 neem aan");
  key=scrupd(1,0xC1);
  if(*s(1,3)){
    if(cmpstr(s(1,3),oldnm,fldlen(1,3))){
      if(search(1,0)){errnum=39;goto redo;}
      copy(s(1,3),oldnm,fldlen(1,3));
    }
  } else fasinit(1);
  seldata.inq_merk=*u(1,1);
  if(key==107) goto redo;
}

static dsp_stockselectie()
{
  int16 key,z,curs=1;
		
  if(fldlen(6,33)==0) goto endsr;
	if(fldlen(66,11)==0){
		if(seldata.sel_met_stock) seldata.sel_met_stock=0;
		else seldata.sel_met_stock=99;
		goto endsr;
	}

	redo:;
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,3,16,2);
  scraddf(z++,10,2,0); scraddf(z++,10,38,2);scraddf(z++,10,41,0); 
  scraddf(z++,23,1,8);
									
  z=1;
  scrifld(z++,fm_os40,"Selectie periode laatste prijswijziging");
  scrifld(z++,fm_os63,"Selectie filiaal (1-10, 99=depot) :");
	scrifld(-z,fm_uu2,&seldata.sel_met_stock);z++; scrifld(z++,fm_os6,nm_fil);
  scrifld(z++,fm_os15," F8 neem aan");
  key=scrupd(curs,0x81); curs=1;
  if(seldata.sel_met_stock==99) copy("DEPOT",nm_fil,6);
  else if(seldata.sel_met_stock==0) zero(nm_fil,6);
  else if(seldata.sel_met_stock>=1 && seldata.sel_met_stock<=10){
    if(fldlen(66,11+(seldata.sel_met_stock-1)*15) && nm_loc[seldata.sel_met_stock-1][0]!='\0'){
	    copy(nm_loc[seldata.sel_met_stock-1],nm_fil,6);
    }
    else {curs=3;zero(nm_fil,6);errnum=34;goto redo;}
  }
  else {curs=3;zero(nm_fil,6);errnum=34;goto redo;}
  if(key==18){
    curs=1;goto redo;
  }
	endsr:;

}


static dsp_plim()
{
  int16 key,z;
									
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,3,16,2);
  scraddf(z++,10,2,0);
  scraddf(z++,10,23,2);scraddf(z++,10,32,0);
  scraddf(z++,10,39,2);
  scraddf(z++,23,1,8);
									
  z=1;
  scrifld(z++,fm_os40,"Selectie periode laatste prijswijziging");
  scrifld(z++,fm_os63,"Periode wijziging : ");
  scrifld(z++,fm_udat,&seldata.dt_p_beg);
  scrifld(z++,fm_os63,"t.e.m. ");
  scrifld(z++,fm_udat,&seldata.dt_p_end);
  scrifld(z++,fm_os15," F8 neem aan");
  key=scrupd(1,0x81);
}
 
static dsp_tabel(type_)
int16 type_;/* 0=leveranciers, 1=groepen */
{
  int16 j,k,key,z,start=0,startpos,p_tb,curs=1,q_y,q_n,stu_,curspos_;
  char *pd;

  if(type_==0) {stu_=1;startpos=0; p_tb=seldata.p_max_lev;}
  else {stu_=52;startpos=500; p_tb=500+seldata.p_max_grp;}
  start=startpos; pd=oldnm;
  FOREVER{
    redo:;
    scrnum=0;scrget(2,46);z=1;
    if(type_==0) scrifld(z++,fm_os15,"LEVERANCIER");
    else scrifld(z++,fm_os15,"GROEP");
    for(k=start;k<p_tb;k++){
      fasinit(stu_); *u(stu_,1)=seldata.tb[k].rec; fasgeti(stu_);
      pd=oldnm; zero(pd,40);
      switch(stu_){
	case 6 : pd+=add_str(pd,10,6,2,' ');pd+=add_str(pd,30,6,3,'\0');
		 break;
	case 1 : pd+=add_str(pd,40,1,3,'\0');
		 break;
	case 52: stcli_d(pd,(long)*u(52,1),2,0);pd+=2;*(pd++)=' ';
		 pd+=add_str(pd,30,52,14,'\0');
		 break;
	default: zero(pd,40);break;
      }
      scrifld(z,fm_os40,oldnm);
      if(seldata.tb[k].select=='J') scrchat(z++,0x08); else scrchat(z++,0x00);
      scrifld(z,fm_uJN,&seldata.tb[k].select);
      if(seldata.tb[k].select=='J') scrchat(z++,0x02); else scrchat(z++,0x00);
      if(k==start+17) break;
    }
    key=scrupd(curs,0x40B6);curs=1;curspos_=fldcurs;
    if(key==18 || key==9){/* pijl dn */
      curs=curspos_+1;  
			j=(curs-1)/2-1;
			if(j>=0){
			  if(seldata.tb[j+start].select=='J') seldata.tb[j+start].select='N'; else seldata.tb[j+start].select='J';
			}
			goto redo;
    }
    if(key==8){/* pijl up */
      curs=curspos_-2; if(curs<=1) curs=1;  goto redo;
    }
    if(key==105) {for(k=startpos;k<p_tb;k++) seldata.tb[k].select='J';}
    if(key==106) {for(k=startpos;k<p_tb;k++) seldata.tb[k].select='N';}
    if(key==108){
      q_y=0;q_n=0;
      for(k=startpos;k<p_tb;k++){
				if(seldata.tb[k].select=='J') q_y++; else q_n++;
      }
      if(q_n==0){ if(type_==0) seldata.slev_used=NO; else seldata.sgrp_used=NO;}
      else{
				if(q_y==0){errnum=38; goto redo;}
				else{if(type_==0) seldata.slev_used=YES; else seldata.sgrp_used=YES;}
      }
      break;
    }
    if(key==102) start-=18;
    if(key==103) {start+=18;if(start>=p_tb-18) start=p_tb-18;}
    if(start<startpos) start=startpos;
  }
  return NO;
}

 
static bittst(val_,bnr_)
uint16 val_,bnr_;
{
  if(val_ & (1<<bnr_)) return YES;
  else return NO;
}
 
static add_str(pd,len_,stu_,nr_,kar_)
char *pd,kar_;
int16 stu_,nr_,len_;
{
  int16 k;
 
  if(len_>fldlen(stu_,nr_)) len_=fldlen(stu_,nr_);
  copy(s(stu_,nr_),pd,len_);
  for(k=0;k<len_;k++){
    if(*(pd+k)=='\0') break;
  }
  *(pd+k++)=kar_;if(kar_==',') *(pd+k++)=' ';
  return k;
}


static fileopen(nr_)
int16 nr_;
{
  int16 stu_;
  char filename[15];

  nr_--;
  sysget(300+17*nr_,15,filename);
  sysget(315+17*nr_,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(errnum=fasopen(filename,0)) ovlexit(-1);
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  }
}

static fmt_get(stu_,elet_)
int16 stu_,elet_;
{
  int16 k;
  char *pdum,dummy_[10];

  pdum=&dummy_[0];
  k=fieldspc(stu_,elet_,&pdum,fmt);
  if(k>0) return k;
  return 0;
}

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
}

static selp_ask()
{
  int16 key;
  char choice;

  FOREVER{
    scrget(1,46);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(1,0x0581);
    if(key==101) return YES;
    if(key==111) ovlexit(-1);
    if(key==108) {seldata.selp_use=YES;break;}
    if(key==109) {seldata.selp_use=NO;break;}
    switch(choice){
      case '1': seldata.selp_ge=NO;selp_upd(0,choice);break;
      case '2': seldata.selp_ge=YES;selp_upd(0,choice);break;
      case '3': seldata.selp_le=NO;selp_upd(1,choice);break;
      case '4': seldata.selp_le=YES;selp_upd(1,choice);break;
      case '5': selp_upd(2,choice);break;
      case '6': selp_upd(3,choice);break;
      case '7': selp_wis();scrget(1,7);scrupd(-3,0);break;
      default : errnum=34; break;
    }
  }
  return NO;
}

static selp_upd(bfnr,men_keuze)
int16 bfnr;
char men_keuze;
{
  int16 j,key,k,curs,z,pnr_,prstu_;
 
  men_keuze=men_keuze-'1';
  copy(seldata.selp_bf[bfnr],s(6,1),fldlen(6,0));
  curs=2;
redo_a:;
	k=19; // if(fldlen(6,185)) k=59;
  scrget(2,k); z=1; scrinq();
  scrifld(z++,fm_os20,selp_txt[men_keuze]);
  if(fldlen(6,2)) scrfld(z++,6,2); else scrofld(z++,6,1,-1);
	if(bfnr==2){
		if(fldlen(6,200)){
			if(*u(6,200)==1){
				scrchat(z-1,0xB); 
			  scraddpicto(7,z-1,0,0,2,1,70,0,3,"Maak actief");
			}
			else{
				scrchat(z-1,0xFF);
				if(*u(6,200)==0) scraddpicto(7,z-1,0,0,2,1,71,0,4,"Blokkeer");
				else scraddpicto(7,z-1,0,0,2,1,71,0,0,"Blokkeer");
			}
		}
		if(fldlen(6,195)){
			if(*s(6,195)=='J') scraddpicto(8,z-1,2,0,2,1,32,0,4,"NIET in webshop");
			else{
				if(*s(6,195)=='N') scraddpicto(8,z-1,2,0,2,1,32,0,3,"Toon in webshop");
				else scraddpicto(8,z-1,2,0,2,1,32,0,0,"Toon in webshop");
			}
		}
		if(fldlen(6,194)){
			k=2; if(fldlen(6,195)) k=4;
			if(*s(6,194)=='J') scraddpicto(10,z-1,k,0,2,1,82,0,4,"NIET in B2B-webshop"); 
			else{
  			if(*s(6,194)=='N') scraddpicto(10,z-1,k,0,2,1,82,0,3,"Toon in B2B-webshop");			
	  		else scraddpicto(10,z-1,k,0,2,1,82,0,0,"Toon in B2B-webshop");
			}
		}
	}

  for(k=3;k<=6;k++) scrfld(z++,6,k);
  z++;scrfld(z++,6,7);
  scrfld(z++,6,8);
  if(fldlen(6,101)) scrfld(z++,6,101);
  scrfld(z++,6,9);z++;
	if(fldlen(6,103)){scrfld(z++,6,103);z++;}
  for(k=10;k<=20;k++) scrfld(z++,6,k);
	if(fldlen(6,185)){
		for(k=0;k<5;k++){
			pnr_=k;
redo_rechts:;  
			prstu_=PrNrs[pnr_];
			if(fldlen(6,prstu_)){
				scrifld(z++,fm_os6,&vptekst[pnr_*10]);
				fmt_get(6,prstu_); 
				scrifld(z++,fmt,f(6,prstu_)); 
				if(sys3894 & 1<<pnr_) scrifld(z++,fm_os2,"IN");
				else scrifld(z++,fm_os2,"EX");
				z++;
			}
			else for(j=0;j<4;j++) streepje(z++);
			if(pnr_<5){pnr_=k+5; goto redo_rechts;}
		}
	}
	else{
		for(k=0;k<6;k++){
			prstu_=PrNrs[k];
			if(fldlen(6,prstu_)){
				scrifld(z++,fm_os6,&vptekst[k*10]);
				fmt_get(6,prstu_);
				scrifld(z++,fmt,f(6,prstu_));
				if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
				else scrifld(z++,fm_os5,"Excl.");
				z++;
			}
			else for(j=0;j<4;j++) streepje(z++);
		}
	}

  //for(k=0;k<6;k++){
  //  if(fldlen(6,PrNrs[k])){
  //    scrifld(z++,fm_os6,&vptekst[k*10]);
  //    scrfld(z++,6,21+k);
  //    if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
  //    else scrifld(z++,fm_os5,"Excl.");
  //    z++;
  //  }
  //  else for(j=0;j<4;j++) streepje(z++);
  //}
  key=scrupd(curs,0x0180);curs=2;
	if ((key/0x100)==1) key=(key&0xFF)+5000;
	if(key==5007 && fldlen(6,200)){ // blokkeer
		if(*u(6,200)==0) *u(6,200)=1; else *u(6,200)=0;
		goto redo_a;
	}
	if(key==5008 && fldlen(6,195)){ // webshop artikel
		if(*s(6,195)=='J') *s(6,195)='N'; else *s(6,195)='J';
		goto redo_a;
	}
	if(key==5010 && fldlen(6,194)){ // B2B-webshop artikel
		if(*s(6,194)=='J') *s(6,194)='N'; else *s(6,194)='J';
		goto redo_a;
	}
  if(key==109) key=artik_bis();
  if(key!=108) goto redo_a;
  copy(s(6,1),seldata.selp_bf[bfnr],fldlen(6,0));
}

static artik_bis()
{
  int16 k,curs=3,key,z;
 
  FOREVER{
    redo_a:
    scrget(2,20); z=1; scrinq();
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
    for(k=27;k<=79;k++) scrfld(z++,6,k);
    for(k=81;k<101;k++) scrfld(z++,6,k);
    key=scrupd(curs,0x0180);curs=3;
    if(key!=108 && key!=101 && key!=109) goto redo_a;
    else break;
  }
  return key;
}
 

static scraddf(fld,v,h,attr)
int16 fld,v,h,attr;
{
  int16 *pi;
					
  pi=(int16 *)info;
  *(pi+0)=fld;
  *(pi+1)=v;
  *(pi+2)=h;
  *(pi+3)=attr;
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

 
 
