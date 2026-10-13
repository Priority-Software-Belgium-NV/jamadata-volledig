/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0020GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0020dat
#define ovlcod BKH0020cod
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

char ovldat[] = "bkh0020  00:38 05/08/10 (c) Jamadata";
/* archivatie */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DIM_LK          4000
#define DIM_CENT        200
#define flag            uint16

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

extern char *s();
extern int16 *i();
extern uint16 *u(),datejd();
static uint16 tegen_rek();
extern long *l();
static long val(),val4_1(),val86_1(),get_qrecs();
extern float *f();
extern double *d();
static flag centr_grb();

static struct {
  int16 nr;
  int16 typ;
} j_tab[81];

static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os76[]  = {7,0x88,76,0,0,0,0};
static char fm_os12[]  = {7,0x88,12,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_count[] = {6,0x93,6,0,0x20,0};/* long */
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};

static int16 mnd_kw,mnd_strt,arch_bsy,arch_niv=0,stapnr=0,cnt_low,middenste,cnt_high;
static int16 r_yy,r_jr,r_vl,jrnal_btw[100],bka_file;
static uint16 dat_beg,dat_end,last_arc,dt_opruim[2]={0,0},clean_dt[3]={0,0,0};
static uint16 bkaadd,max_lk,ram_size;
static long bd_omit,bd_lk,bd_r,bd_r_omit;
static double ebd_omit,ebd_lk,ebd_r,ebd_r_omit;
static int16 q_ref,q_lk,ref_poin,kdsp;
static long *rec_lk;/* rec_lk[DIM_LK]; */
static char buf160[160],arch_ref,sys1861,dsp_kar[5],keep_saldo;
static long kltcent,levcent,btws[5],noomzet[10];
static flag period_1=NO,period_last=NO,januari,kwart1m;
static flag analyt;

static char *ps_4_2;
static uint16 *pu_4_3,*pu_4_4,*pu_4_5;
static uint16 *pu_5_1,*pu_5_2,*pu_85_1,*pu_88_1;
static uint16 *pu_4_1,len4_1,*pu_86_1,len86_1;
static long *pl_4_1,*pl_86_1;

static long *pl_4_7,*pl_5_3,*pl_5_4,*pl_86_7;
static double *pd_4_32,*pd_5_31,*pd_5_32,*pd_86_32;

static struct {
  uint16 dt;
  uint16 qrecs[3];
  uint16 tot;
} t_bka[5];

static struct {
  uint16 rec;
  long bdcent[2];
  double ebdcent[2];
} t_cent[DIM_CENT+1];
 
ovlcod()
{
  int16 k,key,z;
  uint16 clean_prev[3],ubd_;
  long rfree_,mfree_,count_;
  char choice,cfout_;

  initload();
  if(bka_file==0 || arch_bsy) archiv_per();
  else{
    sysget(1842,6,(char *)clean_prev);cfout_=0;

    FOREVER{
      scrget(1,47);z=1;
      scrfld(z++,25,1);
      scrifld(z++,fm_menu,&choice);
      scrifld(z++,fm_odat,&last_arc);
      if(len4_1==2){
	for(k=0;k<3;k++){
	  fasinfo(4,k+1); count_=val4_1();
	  if(k==2) rfree_=count_;
	  else scrifld(z++,fm_count,&count_);
	}
	mfree_=val4_1()*5/100;
	if(rfree_<=mfree_ || rfree_<=200){/* indien minder dan 5% vrij dan reversed */
	  scrchat(z-1,0x7);cfout_|=0x01;
	}
      }
      else{
	fasinfo(4,1); count_=val4_1();
	scrifld(z++,fm_count,&count_);
	scrifld(z++,fm_os5,"n.v.t");
      }
      scrifld(z++,fm_odat,&clean_prev[0]);
      if(len86_1==2){
	for(k=0;k<3;k++){
	  fasinfo(86,k+1);count_=val86_1();
	  if(k==2) rfree_=count_;
	  else scrifld(z++,fm_count,&count_);
	}
	mfree_=val86_1()*5/100;
	if(mfree_>=rfree_){scrchat(z-1,0x7); cfout_|=0x02;}
	sysget(1916,2,&ubd_); mfree_=ubd_; mfree_*=1.3; fasinfo(86,2);
	if(mfree_>=val86_1()){scrchat(z-1,0x7);cfout_|=0x02;}
      }
      else{
	fasinfo(86,1); count_=val86_1();
	scrifld(z++,fm_count,&count_);
	scrifld(z++,fm_os5,"n.v.t");
      }
      for(k=1;k<3;k++) scrifld(z++,fm_odat,&clean_prev[k]);
      if(cfout_&0x02) scrifld(z++,fm_os76,"Jaararchief is (bijna) vol! Gelieve te schrappen (zie punt 2).");
      if(cfout_&0x01) scrifld(z++,fm_os76,"Boekhouding is (bijna) vol! Gelieve te archiveren (zie punt 1).");
      key=scrupd(1,0x0401);
      if(key==101 || key==111) ovlexit(10);
      switch(choice){
				case '1': if(bka_ok()) break;
						archiv_per();goto endsr;
				case '2': clean_bka();goto endsr;
				default : errnum=34; break;
      }
    }
  }
  endsr:;
  ovlexit(10);
}

static bka_ok()
{
  int16 key,z;
  uint16 a;
  long count_;

	if(fldlen(4,1)==4) return NO;

  sysget(1916,2,&a);
  fasinit(86);fasinfo(86,2);count_=val86_1();
  if((a*1.3)>count_){
    FOREVER{
      scrget(1,45);z=1;
      scrfld(z++,25,1);
      scrifld(z++,fm_count,&count_);
      scrifld(z++,fm_ou5,&a);
      key=scrupd(0xFFFF,0x0409);
      if(key==101) return YES;
      if(key==111) ovlexit(10);
      if(key==104) break;
      errnum=21;
    }
  }
  return NO;
}

static archiv_per()
{
	fasunlck(-2);
  if(arch_bsy==0) params();
  init_1e();
  pages_jr();

  archief();/* not used */
  sal_old();/* schuif saldi-kolommen in saldi-file op */
  sal_upd();/* upd saldi-bedragen */
  btw_old();/* schuif btw-kolommen in saldi-file op */
  btw_upd();/* upd btw bedragen */
  sal_del();/* del unused saldi-rec */
  grb_del();/* del grootb. rec */
  lk_del();/* del lev/klt rec */
/* jvg hier later : alle opmerkingen seq. overlopen, en schrappen indien hoofd-
   boeking ook reeds weg is. Analoog voor factuurrecords   jvg
   maar niet elke keer : slechts om het 1/2 jaar b.v. voor foutief gemaakte
   records, of afbrekingen tijdens het archiveren op te rommelen */
 
  resetsys();
//  dsp_rwarn();
	fasunlck(0);
  endsr:;
}

static dsp_rwarn()
{
  scrnum=0;scrget(1,170);
  scrifld(10,fm_os79,"   Gelieve eerst de gegevens te laten repareren ");
  scrifld(11,fm_os79,"      alvorens verder te werken.");
  scrifld(19,fm_os79,"Druk F8 om verder te gaan");
  scrupd(-1,0x80);
}

static params()
{
  int16 curs=4,k,key,z;
  int16 dd,dd1,dd2,mm,mm1,mm2,yyyy,yyyy1,yyyy2;
  char ft_ref,lijst_ok,buf_[5],per_txt_[13];
  long yyyy_l;

  fasunlck(-1);
	dat_beg=last_arc+1; if(dat_beg==1){dat_beg=0;curs=3;}
  dat_end=0;
  ft_ref='J';keep_saldo='J';
  lijst_ok='N';
  zero(buf160,sizeof buf160);
  chk_janu(last_arc+1);
  if(mnd_kw==0) copy("(1 maand)",per_txt_,10);
  else if(mnd_kw==1) copy("(1 kwartaal)",per_txt_,13);
  else copy("(1 jaar)",per_txt_,9);

  redo:
  if(januari && get_qrecs(5)){
    copy(" De gegevens voor de BTW-listing xxxx worden vernietigd !",buf160,80);
    jddate(dat_beg-1,&yyyy,&mm,&dd);
    yyyy_l=yyyy;stcli_d(buf_,yyyy_l,4,0);copy(buf_,&buf160[33],4);
  }
  if(period_1){
    copy(" Nieuw boekjaar. Alle saldi van vorig boekjaar gewist !",&buf160[80],79);
  }
  scrget(1,12); z=1;
  scrfld(z++,25,1);
  scrifld(z++,fm_odat,&last_arc);
  scrifld(z++,fm_udat,&dat_beg);
  scrifld(z++,fm_udat,&dat_end);
  scrifld(z++,fm_os12,per_txt_);
  scrifld(z++,fm_u_JN,&ft_ref);
  scrifld(z++,fm_u_JN,&lijst_ok);
  if(buf160[0]) scrifld(z++,fm_os76,&buf160[0]);
  if(buf160[80]) scrifld(z++,fm_os76,&buf160[80]);
  key=scrupd(curs,0x481); curs=3;
  if(key==101 || key==111) ovlexit(10);

/* controle datum */
  if(dat_beg==0) {curs=3; errnum=38;goto redo;}
  if(dat_end<=dat_beg) {curs=4;errnum=36;goto redo;}
  jddate(dat_beg,&yyyy1,&mm1,&dd1);
  jddate(dat_end,&yyyy2,&mm2,&dd2);
  jddate(dat_end+1,&yyyy,&mm,&dd);
  if(mm==mm2) {curs=4;errnum=32;goto redo;}
  if(last_arc){
    if(dat_beg!=last_arc+1) {curs=3;errnum=35;goto redo;}
  }
  else{
    if(dd1!=1) {curs=3;errnum=35;goto redo;}
  }
  if(yyyy1!=yyyy2) {curs=4;errnum=27;goto redo;}
  if(mm1<mnd_strt && mm2>=mnd_strt) {curs=4;errnum=27;goto redo;}
  if(mnd_kw==0){
    if(mm1!=mm2) {curs=4;errnum=33;goto redo;}
  }
  else if(mnd_kw==1){
    if((mm2%3) || ((mm1-1)/3)!=((mm2-1)/3)) {curs=4;errnum=33;goto redo;}
  }
  else{
    if(mm2!=12) {curs=4;errnum=33;goto redo;}
  }
  chk_janu(dat_beg);
  if(lijst_ok!='J') {errnum=34;curs=7;goto redo;}
  if(key!=108) {errnum=21;goto redo;}

  if(bit(sys1861,0)){
    FOREVER{
      curs=1;
      redo_x:
      scrget(1,49);z=1;
      for(k=0;k<2;k++)scrifld(z++,fm_udat,&dt_opruim[k]);
      scrifld(z++,fm_u_JN,&keep_saldo);/* indien N, dan GEEN saldo in stk */
      key=scrupd(curs,0x480);curs=1;
      if(key==111) ovlexit(10);
      for(k=0;k<2;k++){
	if(dt_opruim[k]>dat_end) {errnum=62;curs=k+1;goto redo_x;}
      }
      if(key==108) break;
    }
  }

  k=mnd_strt-1; if(k<1) k=12;
  if(k==mm2) period_last=YES;
  if(ft_ref=='J') arch_ref=1; else arch_ref=0;
  arch_bsy=1;
  sysput(1856,2,&arch_bsy);
  sysput(1860,1,&arch_ref);
  sysput(1868,2,&dat_beg);
  sysput(1870,2,&dat_end);
  sysflush();
  if(get_qrecs(5)==0){
    fasinit(5);
    fasadd(5);fasflush(0);
  }
  *pu_5_1=1;fasgetu(5);
  *pd_5_32=0;
  fasupd(5);
}

static init_1e()
{
  chk_janu(dat_beg);
  scrget(1,170);
  scrifld(1,fm_os79,"    Archivatie");scrupd(-3,0);
  *pu_5_1=1;fasgeti(5);
  arch_niv=*pd_5_32;
}

static pages_jr()
{
  int16 k,g;

  for(k=0;k<40;k++){
    sysget(10284+k*80,2,&g);
    if(period_last){
      g=0;
      sysput(10284+k*80,2,&g);
    }
    sysput(10282+k*80,2,&g);
  }
}

static archief()
{
  if(stepping(0)) goto endsr;
  endsr:;
}

static sal_old()
{
  int16 mode;
  long a,used;

  if((mode=stepping(stapnr+2))>0) goto endsr;
  used=get_qrecs(5);
  for(a=1;a<=used;a++){
    *pu_5_1=a;
    if((a%500)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
    if(fasgetu(5)==0){
      if(mode==0){/* normal */
	*l(5,5)=*pl_5_3; *l(5,6)=*pl_5_4;
	*d(5,33)=*pd_5_31; *d(5,34)=*pd_5_32;
      }
      else{/* reversed */
	*pl_5_3=*l(5,5); *pl_5_4=*l(5,6);
	*pd_5_31=*d(5,33); *pd_5_32=*d(5,34);
      }
      if(period_1){
	*pl_5_3=0; *pl_5_4=0; *l(5,5)=0; *l(5,6)=0;
	*pd_5_31=0;*pd_5_32=0;*d(5,33)=0;*d(5,34)=0;
      }
      fasupd(5);
    }
  }
  endsr:;
}
 
static sal_upd()
{
  int16 ks,k,g;
  long a,used;
  long lgrb,bd_lk_[4];
  double ebd_lk_[4];

  if(stepping(0)) goto endsr;
  for(k=0;k<4;k++){bd_lk_[k]=0;ebd_lk_[k]=0;}
  used=get_qrecs(4);
  for(a=1;a<=used;a++){
    chg4_1((long)a);
    if((a%500)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
    if(fasgeti(4)==0){
      if(*pu_4_4>=dat_beg && *pu_4_4<=dat_end){
	fasinit(5);*pu_5_2=*pu_4_5;
	ks=faskeyu(5,1,0);
	g=0;
    if(*pd_4_32<0) g=-1; else g=1;
	if(g<0){
	  *pl_5_4+=*pl_4_7; *pd_5_32+=*pd_4_32;
	  k=1;
	}
	else{
	  *pl_5_3+=*pl_4_7; *pd_5_31+=*pd_4_32;
	  k=0;
	}
	if(*pu_4_5<60000){
	  if(*pu_4_5>=30000) k+=2;
	  bd_lk_[k]+=*pl_4_7; ebd_lk_[k]+=*pd_4_32;
	}
	if(ks) fasadd(5); else fasupd(5);
      }
    }
  }
  for(k=0;k<2;k++){
    if(k==0) lgrb=levcent; else lgrb=kltcent;
    fasinit(3);*l(3,2)=lgrb;
    faskeyi(3,1,0);
    fasinit(5);*pu_5_2=*u(3,1)+60000;
    ks=faskeyu(5,1,0);
    *pl_5_3+=bd_lk_[0+k*2];*pl_5_4+=bd_lk_[1+k*2];
    *pd_5_31+=ebd_lk_[0+k*2];*pd_5_32+=ebd_lk_[1+k*2];
    if(ks) fasadd(5); else fasupd(5);
  }
  *pu_5_1=1;fasgetu(5);
  *pl_5_3=dat_end;
  fasupd(5);fasflush(0);
  endsr:;
}

static btw_old()
{
  int16 mode,k;
  long a,used;

  if((mode=stepping(stapnr+2))>0) goto endsr;
  used=get_qrecs(5);
  for(a=1;a<=used;a++){
    *pu_5_1=a;
    if((a%500)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
    if(fasgetu(5)==0){
      if(mode==0){/* normal */
	*l(5,9)=*l(5,7); *l(5,10)=*l(5,8);
	*d(5,37)=*d(5,35); *d(5,38)=*d(5,36);
	if(fldlen(5,20)){*l(5,21)=*l(5,20);*l(5,23)=*l(5,22);*l(5,25)=*l(5,24);}
	if(fldlen(5,44)){*d(5,45)=*d(5,44);*d(5,47)=*d(5,46);*d(5,49)=*d(5,48);}
      }
      else{/* reversed */
	*l(5,7)=*l(5,9); *l(5,8)=*l(5,10);
	if(fldlen(5,20)){*l(5,20)=*l(5,21);*l(5,22)=*l(5,23);*l(5,24)=*l(5,25);}
	*d(5,35)=*d(5,37); *d(5,36)=*d(5,38);
	if(fldlen(5,44)){*d(5,44)=*d(5,45);*d(5,46)=*d(5,47);*d(5,48)=*d(5,49);}

      }
      if(januari){
	*l(5,7)=0; *l(5,8)=0; *l(5,9)=0; *l(5,10)=0;
	*d(5,35)=0; *d(5,36)=0; *d(5,37)=0; *d(5,38)=0;
      }
      if(kwart1m){
	if(fldlen(5,20)) for(k=0;k<6;k++) *l(5,20+k)=0;
	if(fldlen(5,44)) for(k=0;k<6;k++) *d(5,44+k)=0;
      }
      fasupd(5);
    }
  }
  endsr:;
}

static btw_upd()
{
  int16 journl,k,ks,key_mode;
  uint16 recnr_,volgnr,dat_bk;
  long a,used;
  long btw,omz,div;
  double ebtw,eomz,ediv;
  flag klt_mode;

  if(stepping(0)) goto endsr;
  used=get_qrecs(4);
  for(a=1;a<=used;a++){
    if((a%500)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
    chg4_1((long)a);
    if(fasgeti(4)==0){
      if(*pu_4_4>=dat_beg && *pu_4_4<=dat_end && *pu_4_5<60000
      && jrnal_btw[*ps_4_2]){/* alleen aank/verkoopjrnl */
	recnr_=*pu_4_5;
	klt_mode=NO; if(*pu_4_5>=30000) klt_mode=YES;
	omz=0;btw=0; eomz=0;ebtw=0; div=0;ediv=0;
	journl=*ps_4_2;volgnr=*pu_4_3;dat_bk=*pu_4_4;
	fasinit(4);
	*ps_4_2=journl;*pu_4_3=volgnr;
	key_mode=1;
	FOREVER{
	  ks=faskeyi(4,1,key_mode);key_mode=2;
	  if(ks) break;
	  if(journl!=*ps_4_2 || volgnr!=*pu_4_3) break;
	  if(*pu_4_5>=60000 && *pu_4_4==dat_bk){
	    if(!analyt || ((*s(4,6) &0xF0)>>4)!=9){
	      if(klt_mode){*pl_4_7=-*pl_4_7; *pd_4_32=-*pd_4_32;}
	      for(k=0;k<5;k++){
		if(*l(4,6)==btws[k]) break;
	      }
	      if(k<5){btw+=*pl_4_7; ebtw+=*pd_4_32;}
	      else{
		for(k=0;k<10;k++){
		  if(*l(4,6)==noomzet[k]) break;
		}
		if(k==10){omz+=*pl_4_7;eomz+=*pd_4_32;}
		else {div+=*pl_4_7;ediv+=*pd_4_32;}
	      }
	    }
	  }
	}
	if(fldlen(4,38)){/* belastb,divers en btw bijhouden voor ovl079 facturenlijst */
	  chg4_1((long)a);  fasgeti(4);
	  copy((char *)&eomz,s(4,38),8);
	  copy((char *)&ediv,s(4,38)+8,8);
	  copy((char *)&ebtw,s(4,38)+40,8);
	  fasupd(4);
	}
/* ...oppassen voor dubbele klantendebet op dezelfde datum ! jvg */
	fasinit(5);
	*pu_5_2=recnr_;
	ks=faskeyu(5,1,0);
	*l(5,7)+=omz;*l(5,8)+=btw;
	*d(5,35)+=eomz; *d(5,36)+=ebtw;
/* 5,20 =buitenland, dus btw=normaal 0 (tenzij bij aankoop, als */
/* er geboekt is op BTW EEG, dan moet die meegeteld worden) */
	if(fldlen(5,20)) *l(5,20)+=omz+btw;
	if(fldlen(5,44)) *d(5,44)+=eomz+ebtw;
	if(ks) fasadd(5); else fasupd(5);
      }
    }
  }
  fasflush(0);
  endsr:;
}

static sal_del()
{
  int16 k;
  long a,used;

  if(stepping(0)) goto endsr;
  used=get_qrecs(5);
  for(a=1;a<=used;a++){
    if((a%500)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
    *pu_5_1=a;
    if(fasgetu(5)==0){
      for(k=1;k<=8;k++) if(*l(5,k+2)) break;
      if(k>8){
	for(k=1;k<=8;k++) if(*d(5,k+30)) break;
      }
      if(k>8) {*pu_5_1=a;faskill(5);fasinfo(5,101);}
    }
  }
  endsr:;
}

static grb_del()
{
  int16 k,g,yy,mm,dd;
  long a,used;

  if(stepping(0)) goto endsr;

  zero((char *)&t_cent[0].rec,sizeof t_cent);

  middenste=max_lk/2;
  cnt_low=middenste;cnt_high=middenste;
  used=get_qrecs(4);
  for(a=1;a<=used;a++){
    if((a%250)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
    chg4_1((long)a);
    if(fasgetu(4)==0){
      if(*pu_4_5>=60000 && *pu_4_4<=dat_end){
	if(*pu_4_4>=dat_beg && bka_file&1){
	  if(centr_grb()){
	    copy((char *)pu_4_1,(char *)pu_86_1,fldlen(86,0));
	    fill_teg_rek();                       /* invullen tegenrekening */
	    *s(86,8)='\0';*s(86,9)='\0';*u(86,10)=0;
	    fasadd(86);bkaadd++;
	  }
	  else{
	    for(k=0;k<DIM_CENT;k++) if(*pu_4_5==t_cent[k].rec || t_cent[k].rec==0) break;
	    t_cent[k].rec=*pu_4_5;
	    g=0;
        if(*pd_4_32<0) g=1;
	    t_cent[k].bdcent[g]+=*pl_4_7; t_cent[k].ebdcent[g]+=*pd_4_32;
	  }
	}
	chg4_1((long)a);faskill(4);
      }
    }
  }
  if(bka_file&1){/* add totalen centralisatie */
    for(k=0;k<DIM_CENT;k++){
      if(t_cent[k].rec==0) break;
      fasinit(86); *u(86,4)=dat_end; *u(86,5)=t_cent[k].rec;
      *s(86,12)=0xFF;/* extra aanduiding totaal-record */
      *l(86,7)=t_cent[k].bdcent[0];*d(86,32)=t_cent[k].ebdcent[0];
      copy("DEB ",s(86,28),4); g=4;
      jddate(dat_beg,&yy,&mm,&dd);
      stcli_d(s(86,28)+g,(long)mm,2,0);g+=2;
      jddate(dat_end,&yy,&mm,&dd);
      if(mnd_kw!=0) {*(s(86,28)+g++)='-'; stcli_d(s(86,28)+g,(long)mm,2,0);g+=2;}
      *(s(86,28)+g++)='/'; stcli_d(s(86,28)+g,(long)yy,4,0);
      fasadd(86); bkaadd++;/* totaal DEBET */
      *l(86,7)=t_cent[k].bdcent[1];*d(86,32)=t_cent[k].ebdcent[1];
      copy("CRE ",s(86,28),4);
      fasadd(86); bkaadd++;/* totaal CREDIT */
    }
  }
  fasflush(0);
  endsr:;
}

static lk_del()
{
  long a,b,used;

  if(stepping(0)) goto endsr;
  used=get_qrecs(1);/* lev */
  for(a=1;a<=used;a++){
    if((a%50)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
    lk_del1(a,0);
  }
  used=get_qrecs(2);/* klt */
  for(a=1;a<=used;a++){
    if((a%50)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
    b=a+30000;lk_del1(b,1);
  }
  fasflush(0);
  endsr:;
}

static lk_del1(nr_,type_)
long nr_;
int16 type_;
{
  int16 ks,key_mode=1;

  fasinit(4); *pu_4_5=nr_;
  q_ref=0;q_lk=0;bd_r=0;bd_lk=0; ebd_r=0; ebd_lk=0;
  FOREVER{
    ks=faskeyi(4,4,key_mode);key_mode=2;
    if(ks==0 && *pu_4_5!=nr_) ks=1;
    if(ks || *s(4,8)!=r_yy || *s(4,9)!=r_jr || *u(4,10)!=r_vl){
      chk_ref();
      if(ks) break;
      r_yy=*s(4,8);r_jr=*s(4,9);r_vl=*u(4,10);
    }
    if(*pu_4_4<=dat_end) addtb_lk();
  }
  if(arch_ref==0) chk_lk();
  if(dt_opruim[type_]) saldeer(dt_opruim[type_]);
}

static resetsys()
{
  arch_bsy=0;
  last_arc=dat_end;
  sysput(1856,2,&arch_bsy);
  sysput(1858,2,&last_arc);
  sysput(1916,2,&bkaadd);
  sysflush();
  *pu_5_1=1;fasgetu(5);
  *pl_5_4=0;*l(5,6)=0;
  *pd_5_32=0; *d(5,34)=0;
  fasupd(5);fasflush(0);
  fasinfo(4,101);
  fasclos(4);
  fasclos(5);
}

static stepping(mxrevers)
int16 mxrevers;
{
  int16 retcd,bpos_=0;
  long long_;
  char buf_[100];

  zeros(buf_,sizeof buf_); bpos_=0;
  if((mxrevers && mxrevers>=arch_niv && stapnr<arch_niv) || stapnr>=arch_niv){
    if(stapnr>=1){
      copy("Stap ",&buf_[bpos_],5); bpos_+=5;
      long_=stapnr; stcli_d(&buf_[bpos_],long_,2,1);bpos_+=2;
      copy(" : uitgevoerd.",&buf_[bpos_],14);
      scrifld(stapnr+3,fm_os79,buf_);scrupd(-3,0);
    }
  }

  zeros(buf_,sizeof buf_); bpos_=0;
  copy("Stap ",&buf_[bpos_],5); bpos_+=5;
  long_=++stapnr; stcli_d(&buf_[bpos_],long_,2,1);bpos_+=2;
  copy(" : ",&buf_[bpos_],3); bpos_+=3;
  if(stapnr>=arch_niv){
    switch(stapnr){
      case 1 : bpos_+=copy0("Opschuiven balans-saldi",&buf_[bpos_]); break;
      case 2 : bpos_+=copy0("Bijwerken balans-saldi",&buf_[bpos_]); break;
      case 3 : bpos_+=copy0("Opschuiven btw-totalen",&buf_[bpos_]); break;
      case 4 : bpos_+=copy0("Bijwerken  btw-totalen",&buf_[bpos_]); break;
      case 5 : bpos_+=copy0("Schrappen ongebruikte saldi-lijnen",&buf_[bpos_]); break;
      case 6 : bpos_+=copy0("Schrappen grootboek-boekingen",&buf_[bpos_]);
	       if(bka_file) bpos_+=copy0(" (en toevoegen in archief)",&buf_[bpos_]);
	       break;
      case 7 : bpos_+=copy0("Schrappen voldane klt/lev boekingen",&buf_[bpos_]);
	       if(bka_file) bpos_+=copy0(" (en toevoegen in archief)",&buf_[bpos_]);
	       break;
      case 8 : bpos_+=copy0("Bijwerken systeemgegevens",&buf_[bpos_]); break;
      default: break;
    }
  }

  if(mxrevers && mxrevers>=arch_niv && stapnr<arch_niv){
    copy(" (omgekeerd) in uitvoering ...",&buf_[bpos_],26); bpos_+=26;
    retcd=-1;
  }
  else if(stapnr<arch_niv){
    copy(" reeds uitgevoerd.",&buf_[bpos_],17);bpos_+=17;
    retcd=1;
  }
  else{
/*    copy(" in uitvoering ...",&buf_[bpos_],14); bpos_+=14; */
    retcd=0;
  }
  scrifld(stapnr+3,fm_os79,buf_);
  if(stapnr>1) scrchat(stapnr+2,0);
  scrchat(stapnr+3,2);
  if(stapnr>arch_niv){
    *pu_5_1=1;fasgetu(5);
    arch_niv++;
    *pl_5_4=arch_niv;*l(5,6)=arch_niv;
    *pd_5_32=arch_niv;*d(5,34)=arch_niv;
    fasupd(5);fasflush(0);
  }
  return retcd;
}

static zeros(pd,len)
char *pd;
uint16 len;
{
  while(len--) *pd++='\0';
}

static copy0(ps,pd)
char *ps,*pd;
{
  int16 fuval=0;
		
  while(*ps){
    *pd++=*ps++;
    fuval++;
  }
  *pd='\0';
  return fuval;
}

static initload()
{
  int16 k;

  fasunlck(0);

  for(k=1;k<=5;k++) fileopen(k);
  fileopen(10);


#if _WIN32
  ram_size=ExtraSTOSize;
#else
  ram_size=onext-(uint16)s(99,1)-100;
#endif
  rec_lk=(long *)(s(99,1)+50); max_lk=ram_size/sizeof rec_lk[0];

  sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);
  sysget( 788,5*4,&btws[0]);
  sysget( 968,10*4,&noomzet[0]);
  sysget(1806,2,&bka_file);
  sysget(1856,2,&arch_bsy);
  sysget(1858,2,&last_arc);
  sysget(1860,1,&arch_ref);
  sysget(1861,1,&sys1861);
  sysget(1864,2,&mnd_kw);
  sysget(1866,2,&mnd_strt);
  sysget(1868,2,&dat_beg);
  sysget(1870,2,&dat_end);

  for(k=0;k<80;k++){
    sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
    if(j_tab[k].typ<=2) jrnal_btw[j_tab[k].nr]=YES;/* A.K.+V.K. */
  }
  j_tab[80].nr=0;j_tab[80].typ=3;

  pu_4_1=u(4,1);ps_4_2=s(4,2);pu_4_3=u(4,3);
  pu_4_4=u(4,4);pu_4_5=u(4,5);pl_4_7=l(4,7);
  pu_5_1=u(5,1);pu_5_2=u(5,2);pl_5_3=l(5,3);pl_5_4=l(5,4);
  pd_4_32=d(4,32); pd_5_31=d(5,31);pd_5_32=d(5,32); pd_86_32=d(86,32);
  pu_86_1=u(86,1);pl_86_7=l(86,7);
  pl_4_1=l(4,1); len4_1=fldlen(4,1);
  pl_86_1=l(86,1); len86_1=fldlen(86,1);
  analyt=fldlen(4,11);
  copy("-X|/",dsp_kar,4);dsp_kar[1]=0x5C;
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

static long val86_1()
{
  if(len86_1==4) return *pl_86_1;
  else return (long)(*pu_86_1);
}
				
static chg86_1(value_)
long value_;
{
  if(len86_1==4) *pl_86_1=value_;
  else *pu_86_1=value_;
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

static addtb_lk()
{
  bd_r+=*pl_4_7; ebd_r+=*pd_4_32;
  bd_lk+=*pl_4_7; ebd_lk+=*pd_4_32;
  rec_lk[q_lk++]=val4_1();
  if(q_lk>=max_lk){
    errnum=72;
  }
}

static chk_ref()
{
  int16 g,k;
  long rec_;
	
  if(is_nul(ebd_r)) g=0; else g=1;
  if(g==0 && q_ref!=q_lk){
    rec_=val4_1();/* save new data */

    for(k=q_ref;k<q_lk;k++){
      del_lk_r(rec_lk[k]);
      rec_lk[k]=0;
    }
    q_lk=q_ref;

    chg4_1((long)rec_);fasgetu(4);/* restore new data */
  }
  q_ref=q_lk;
  bd_r=0; ebd_r=0;
}

static chk_lk()
{
  int16 g,k;

  if(is_nul(ebd_lk)) g=0; else g=1;
  if(g==0){
    for(k=0;k<q_lk;k++){
      del_lk_r(rec_lk[k]);
      rec_lk[k]=0;
    }
    bd_lk=0;ebd_lk=0;
  }
}

static saldeer(date_)
uint16 date_;
{
  int16 k,g;
  uint16 fld_5_;
  long bd_=0,fld_6_;
  double ebd_=0;

  for(k=0;k<q_lk;k++){
    chg4_1((long)rec_lk[k]);
    if(val4_1()){
      fasgetu(4);
      if(*pu_4_4<=date_){
	bd_+=*pl_4_7;
	ebd_+=*pd_4_32;
	del_lk_r(rec_lk[k]);
	rec_lk[k]=0;
	fld_5_=*pu_4_5;fld_6_=*l(4,6);
      }
    }
  }
  if(is_nul(ebd_)) g=0; else g=1;
  if(g){
    fasinit(4);*pu_4_5=fld_5_;*l(4,6)=fld_6_;
    *pu_4_4=date_;
    *pl_4_7=bd_;
    *pd_4_32=ebd_;
    *u(4,10)=date_;
		if(fldlen(4,60)) *u(4,60)=procid;
    if(keep_saldo!='N') fasadd(4);
    if(bka_file&2){
      copy((char *)pu_4_1,(char *)pu_86_1,fldlen(86,0));
      *pl_86_7=-*pl_86_7;
      *pd_86_32=-*pd_86_32;
      fasadd(86);bkaadd++;
    }
  }
}

static del_lk_r(rec_)
long rec_;
{
  chg4_1((long)rec_);fasgetu(4);
  if(bka_file&2){
    copy((char *)pu_4_1,(char *)pu_86_1,fldlen(86,0));
    fill_teg_rek();/* invullen tegenrekening */
    fasadd(86);bkaadd++;
  }
  chg4_1((long)rec_);faskill(4);
}

static chk_janu(datum)
uint16 datum;
{
  int16 dum1,dum2,mm;

  jddate(datum,&dum1,&mm,&dum2);
  if(mm==1) januari=YES;
  if(mm==mnd_strt) period_1=YES;
  if(((mm-1)%3)==0) kwart1m=YES;
}
 
static flag centr_grb()/* kijk of centralisatie op N staat */
{
  int16 k;
  uint16 rec_grb;

  rec_grb=*pu_4_5;
  for(k=cnt_low;k<cnt_high;k++){
    if(rec_lk[k]==rec_grb) break;
  }
  if(k==cnt_high){/* tabel kan vanaf midden in 2 richtingen groeien */
    *u(3,1)=rec_grb-60000;*s(3,4)='J';fasgeti(3);
    if(*s(3,4)!='J') k=cnt_high++; else k=--cnt_low;
    rec_lk[k]=rec_grb;
  }
  if(k<middenste) return NO; else return YES;
}
 
static fill_teg_rek()
{
  *l(86,6)=0;
  if(*u(86,5)<60000) goto endsr;
  *u(86,6)=tegen_rek();
  endsr:;
}

static uint16 tegen_rek()
{
  int16 k,jr_,fkey_;
  uint16 date_,vl_,tegen_rec=0;
  long rec_;

  rec_=val4_1();
  jr_=*ps_4_2;
  for(k=0;k<80;k++){
    if(jr_==j_tab[k].nr) break;
  }
  if(j_tab[k].typ<3){
    vl_=*pu_4_3;date_=*pu_4_4;
    chg4_1((long)0);
    fkey_=1;
    FOREVER{
      if(faskeyi(4,1,fkey_)) break;
      fkey_=2;
      if(jr_!=*ps_4_2 || vl_!=*pu_4_3) break;
      if(*pu_4_5<60000 && date_==*pu_4_4){
	tegen_rec=*pu_4_5;
	break;
      }
    }
    chg4_1((long)rec_);fasgeti(4);
  }
  return tegen_rec;
}
 
static clean_bka()
{
  int16 k,key,z;
  uint16 clean_prev[3];
  char realy='N';

	fasunlck(-1);
  sysget(1842,6,(char *)clean_prev);
  zeros((char *)&t_bka[0].dt,sizeof t_bka);
  if(last_arc) c_bka_used();
  fileopen(1);
  fileopen(2);
  FOREVER{
    scrget(1,48);z=1;
    scrfld(z++,25,1);
    for(k=0;k<3;k++){
      scrifld(z++,fm_udat,&clean_dt[k]);
      scrifld(z++,fm_odat,&clean_prev[k]);
    }
    scrifld(z++,fm_u_JN,&realy);
    for(k=0;k<5;k++) scrifld(z++,fm_odat,&t_bka[k].dt);
    for(k=0;k<5;k++) scrifld(z++,fm_ou5,&t_bka[k].qrecs[0]);
    for(k=0;k<5;k++) scrifld(z++,fm_ou5,&t_bka[k].qrecs[1]);
    for(k=0;k<5;k++) scrifld(z++,fm_ou5,&t_bka[k].qrecs[2]);
    for(k=0;k<5;k++) scrifld(z++,fm_ou5,&t_bka[k].tot);
    key=scrupd(1,0x0481);
    if(key==101 || key==111) goto endsr;
    if(key==108 && realy=='J') break;
  }
  scrnum=0;scrget(1,170);fasunlck(-2);
  clean_grb();/* jvgxyz */scrupd(-3,0);
  clean_lk();/* jvgxyz */scrupd(-3,0);
  fasinfo(86,101);
  for(k=0;k<3;k++) if(clean_dt[k]>clean_prev[k]) clean_prev[k]=clean_dt[k];
  sysput(1842,6,(char *)clean_prev);
  sysflush();
	fasunlck(0);
  //dsp_rwarn();
  endsr:;
}
 
static c_bka_used()
{
  int16 j,k,mm,dd,jj,step_;
  uint16 last_dt_,ref_dt_=0;
  long a,used;

  zeros((char *)&t_bka[0].dt,sizeof t_bka);
  scrget(1,170);
  scrifld(10,fm_os79,"Berekenen gebruikte plaatsen in jaararchief ...");
  sysget(1844,2,(char *)&ref_dt_);/* cleandatum KLT als referentie nemen */
  step_=1;
  if(ref_dt_==0) step_=3;
  else if(ref_dt_<last_arc-152) step_=3;/* meer dan 5 maanden */
  last_dt_=last_arc; t_bka[4].dt=last_arc;
  for(k=0;k<4;k++){
    jddate(last_dt_,&jj,&mm,&dd); jj%=100;
    mm-=step_;
    if(mm<=0) {
      mm+=12; jj--; if(jj<0) jj=99;
    }
    mm++;
    if(mm>12){mm=1;jj++; if(jj>99) jj=0;}
    last_dt_=datejd(jj,mm,1)-1;
    if(last_dt_<=ref_dt_) last_dt_=ref_dt_;
    t_bka[3-k].dt=last_dt_;
  }
  used=get_qrecs(86);
  for(a=1;a<=used;a++){/* grootboek */
    chg86_1((long)a);
    if(fasgetu(86)==0){
      if(*u(86,5)<30000) j=0;
      else if(*u(86,5)<60000) j=1;
      else j=2;
      for(k=0;k<5;k++){
	if(*u(86,4)<t_bka[k].dt) {t_bka[k].qrecs[j]++; t_bka[k].tot++;}
      }
    }
  }
}
 
static clean_grb()
{
  long a,used;

  scrifld(5,fm_os79,"Bezig met wissen grootboekrekeningen in jaararchief ...");
  used=get_qrecs(86);
  for(a=1;a<=used;a++){
    if((a%500)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
    chg86_1((long)a);
    if(fasgetu(86)==0){
      if((*u(86,5)>=60000 && *u(86,4)<=clean_dt[2])){
	chg86_1((long)a);faskill(86);
      }
    }
  }
  fasflush(0);
}
 
static clean_lk()
{
  int16 ks,stu_lk;
  long a,used,lk_nr;

  for(stu_lk=1;stu_lk<=2;stu_lk++){
    if(stu_lk==1) scrifld(5,fm_os79,"Bezig met wissen leveranciersrekeningen in jaararchief ...");
    else scrifld(5,fm_os79,"Bezig met wissen klantenrekeningen in jaararchief ...");
    used=get_qrecs(stu_lk);
    for(a=1;a<=used;a++){
      if((a%500)==0){scrifld(20,fm_os1,&dsp_kar[kdsp++]); if(kdsp==4) kdsp=0;scrupd(-3,0);}
      lk_nr=(stu_lk-1)*30000+a;
      fasinit(86);*u(86,5)=lk_nr;
      ref_poin=0;q_lk=0;
      bd_r=0;bd_lk=0;bd_omit=0;bd_r_omit=0;
      ebd_r=0;ebd_lk=0;ebd_omit=0;ebd_r_omit=0;
      FOREVER{
	ks=faskeyu(86,4,2);
	if(*u(86,5)!=lk_nr) ks=1;
	if(ks || *s(86,8)!=r_yy || *s(86,9)!=r_jr || *u(86,10)!=r_vl){
	  clean_ref();
	  if(ks) break;
	  r_yy=*s(86,8);r_jr=*s(86,9);r_vl=*u(86,10);
	}
	if(*u(86,4)<=clean_dt[stu_lk-1]) addtb_clean();
	else{
	  bd_omit+=*pl_86_7;bd_r_omit+=*pl_86_7;
	  ebd_omit+=*pd_86_32;ebd_r_omit+=*pd_86_32;
	}
      }
      cle_lk();
    }
  }
  fasflush(0);
}

static addtb_clean()
{
  bd_r+=*pl_86_7; ebd_r+=*pd_86_32;
  bd_lk+=*pl_86_7; ebd_lk+=*pd_86_32;
  rec_lk[q_lk++]=val86_1();
  if(q_lk>=max_lk){
    errnum=36;
  }
}

static clean_ref()
{
  int16 g,g1,k;
  long rec_;

  if(is_nul(ebd_r+ebd_r_omit)) g=0; else g=1;
  if(is_nul(ebd_r)) g1=0; else g1=1;
 
  if(g==0){/* refer klopt in archief */
    if(g1==0){
      rec_=val86_1();/* save new data */
      for(k=ref_poin;k<q_lk;k++){
	cle_lk_r(rec_lk[k]);
      }
      chg86_1((long)rec_);fasgetu(86);/* restore new data */
    }
    q_lk=ref_poin;
  }
  bd_r=0;bd_r_omit=0; ebd_r=0; ebd_r_omit=0;
  ref_poin=q_lk;
}

static cle_lk()
{
  int16 g,k;


  if(is_nul(ebd_lk) || is_nul(ebd_omit)) g=0; else g=1;

  if(g==0){
/* bd_omit==0 -> als er nog ongeldige brokstukken mochten in zitten */
    for(k=0;k<q_lk;k++){
      cle_lk_r(rec_lk[k]);
    }
  }
}

static cle_lk_r(rec_)
long rec_;
{
  chg86_1(rec_);fasgetu(86);
  chg86_1(rec_);faskill(86);
}
 
static long get_qrecs(stu_)
int16 stu_;
{
  long q_;
 
  fasinfo(stu_,1);
  if(fldlen(stu_,1)==4) q_=*l(stu_,1); else q_=*u(stu_,1);
  return q_;
}
 
static bit(byte_,bit_)
char byte_;
int16 bit_;
{
  if(byte_ & 1<<bit_) return YES;
  return NO;
}
 
static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}
