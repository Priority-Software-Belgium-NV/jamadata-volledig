/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0214GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0214dat
#define ovlcod DRK0214cod
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

char ovldat[] = "drk0214  00:04 05/11/10 (c) Jamadata";

// FLAGEPD : korting EUR na % rekenen, dus wordt bij HLkorting geteld
// FLAGVDW : korting EUR na % rekenen, dus wordt bij HLkorting geteld
// FLAGOLH : prijs en stock tonen bij lijst artikels 

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define TABSIZ          (5*51+2)
#define flag            uint16
#define D_LIN_SCR       17

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
static float rnd_vprx();
extern double *d();
extern double valu_cnv();
			

static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os61[]  = {7,0x88,61,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os36[]  = {7,0x88,36,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou1_[]  = {6,0x90,1,0,0x00,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_of4_1[] = {6,0x94,3,1,0x60,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_uJN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

static char ram[10000],buf600[600];
static char stubuf[2][150];
static int16 dat_len,ram_recl,hash_len,max_line;
static uint16 hash_val;
 
static int16 free,type_prx;
static float sys3614;
static uint16 rec_d[TABSIZ];
static char nm_20[20],nm_15[15],bew_only,fmt[40],vptekst[100],stuksprx[10];
static char krt_str[20],def_munt[4];
static flag chk_btoeg=NO,lvcd,klcd,sear_stt,sys3722,sys3892,sys3652,sys3586;
static flag sys3876,sys3894,arcd=NO,kont_exist,prx_op_dt,sys3618;
static float sys2830[10];
static float net_winst[10],vp_norm;
static int16 def_taal,stu=6;
static uint16 *pu_2_1,*pu_6_1;

ovlcod()
{
  int16 curs=1,key,z;

  initload();
  if(sys3722==NO && fldlen(6,22)){
    FOREVER{
      fasinit(2);
      redo:
      scrget(2,30);
      z=1;
      scrfld(z++,25,1);
      scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
      if(fldlen(2,26)) scrfld(z++,2,26); else streepje(z++);
      key=scrupd(curs,0x0481); curs=1;
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key==5001){
				if(Search(2,98)) {curs=3; goto redo;}
			}
      if(key==101) break;
      if(key==111) ovlexit(-1);
      if(*s(2,3)){
	if(search(2,0)) {curs=1;goto redo;}
      }
      type_prx=0; if(fldlen(2,26)) type_prx=*s(2,26)-'0';
      if(type_prx<1 || type_prx>9) type_prx=0;
      if(fldlen(6,PrNrs[type_prx])==0) {errnum=34;goto redo;}
      execute();
    }
  }
  else execute();
  ovlexit(-1);
}

static execute()
{
  int16 key;

  copy("te raadplegen",nm_15,15);
  copy("Artikelen",nm_20,20);
  FOREVER{
    fasinit(6);
    redo:
    scrget(1,5);fasunlck(0);
    scraddf(50,18,7,0); scrifld(50,fm_os15,"Klant ... : ");
    scraddf(51,18,19,2); scrofld(51,2,3,-1);
    scraddf(52,19,7,0); scrifld(52,fm_os15,"Prijstype : ");
    scraddf(53,19,19,2); scrofld(53,2,26,-1);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_os15,nm_15);
    scrfld(4,6,3);scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
//#if FLAGOLH
//		scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
//#endif
    key=scrupd(4,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) break;
    if(key==111) ovlexit(-1);
#if FLAGOLH
		if(key==5001) search(6,98); else search(6,0);
		errnum=0;
#else
		if(key==5001) Search(6,98);
    if(*s(6,3)=='\0') goto redo;
    display();
#endif
  }
}

static display()
{
  int16 j,k,key,z,pos_1_4_,prstu_,pnr_,pr_offset_=0,suppr_wi=NO;

  pos_1_4_=s(1,4)-s(1,1);fasunlck(-1);
  k=disp_art(0);
  if(errnum || k==NO) goto endsr;
  fasinit(1);*u(1,1)=*u(6,7);fasgeti(1);
  copy(s(1,1),stubuf[0],pos_1_4_);
  if(fldlen(6,101)){
    fasinit(1);*u(1,1)=*u(6,101); fasgeti(1);
    copy(s(1,1),stubuf[1],pos_1_4_);
  }
  fasinit(52);*u(52,1)=*u(6,9);fasgeti(52);
	if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(25,2)) pr_offset_=94;
  if(*u(2,1)){fasgeti(6);get_prx();}
  calcnet(pr_offset_);
  redo_scr:;
  scrnum=0;
	k=19; if(fldlen(6,185)) k=59;
  scrnum=0;scrget(2,k); z=1;		dsp_i_flag();
  scrfld(z++,25,1);
  scrfld(z++,6,arcd+1);
  for(k=3;k<=6;k++) scrfld(z++,6,k);
  if(sys3892 & 2 || sys3892 & 8) {
		z+=2;
		suppr_wi=YES;
	}
  else{
    scrbfld(z++,1,1+lvcd,stubuf[0],YES);
    scrbfld(z++,1,3,stubuf[0],NO);

  }
  scrfld(z++,6,8);
  if(fldlen(6,101)) scrbfld(z++,1,3,stubuf[1],NO);
  scrfld(z++,6,9);scrofld(z++,52,14,-1);
	if(fldlen(6,103)){
		scrfld(z++,6,103);z++; // scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_subgroep);
	}
  for(k=10;k<=10;k++) scrfld(z++,6,k);
  if(sys3892 & 2 || sys3892 & 8) z+=10;
  else{
    for(k=11;k<=20;k++){
			scrfld(z++,6,k+pr_offset_); if(pr_offset_ && fldlen(6,k+pr_offset_)) scrchat(z-1,0x9);
		}
  }
	if(fldlen(6,185)){
		for(k=0;k<5;k++){
			pnr_=k;
redo_rechts:;  
			if(pr_offset_) prstu_=PrNrs[pnr_+10]; else prstu_=PrNrs[pnr_];
			if(fldlen(6,prstu_)){
				scrifld(z++,fm_os6,&vptekst[pnr_*10]);
				fmt_get(6,prstu_); 
				scrifld(z++,fmt,f(6,prstu_)); if(pr_offset_) scrchat(z-1,0x9);
				if(k==type_prx) scrchat(z-1,0xA);
				if(sys3894 & 1<<pnr_) scrifld(z++,fm_os2,"IN");
				else scrifld(z++,fm_os2,"EX");
				if(suppr_wi==NO) scrifld(z++,fm_of4_1,&net_winst[pnr_]);
				else z++;
			}
			else for(j=0;j<4;j++) streepje(z++);
			if(pnr_<5){pnr_=k+5; goto redo_rechts;}
		}
	}
	else{
		for(k=0;k<6;k++){
			if(pr_offset_) prstu_=PrNrs[k+10]; else prstu_=PrNrs[k];
			if(fldlen(6,prstu_)){
				scrifld(z++,fm_os6,&vptekst[k*10]);
				fmt_get(6,prstu_); 
				scrifld(z++,fmt,f(6,prstu_)); if(pr_offset_) scrchat(z-1,0x9);
				if(k==type_prx) scrchat(z-1,0xA);
				if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
				else scrifld(z++,fm_os5,"Excl.");
				if(suppr_wi==NO){
				  scrifld(z++,fm_of4_1,&net_winst[k]);
				}
				else z++;
			}
			else for(j=0;j<4;j++) streepje(z++);
		}
	}



  //for(k=0;k<6;k++){
  //  if(fldlen(6,PrNrs[k])){
  //    scrifld(z++,fm_os6,&vptekst[k*10]);
  //    scrfld(z++,6,PrNrs[k]); if(k==type_prx) scrchat(z-1,6);
  //    if(k==type_prx) scrchat(z-1,6);
  //    else if(prx_op_dt) scrchat(z-1,3);
  //    if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
  //    else scrifld(z++,fm_os5,"Excl.");
  //    if(sys3892 & 2 || sys3892 & 8) z++;
  //    else scrifld(z++,fm_of4_1,&net_winst[k]);
  //  }
  //  else for(j=0;j<4;j++) streepje(z++);
  //}
  key=scrupd(0xFFFF,0x01A1);
  if(key==109) key=artik_bis();
  if(key==112 && *u(stu,1)) dsp_info();
  if(key!=101 && key!=108 && key!=106) goto redo_scr;

  endsr:;
}

static scrbfld(z,stu_,fld_,stubuf_,fl_output_)
int16 z,stu_,fld_;
char *stubuf_;
{
  char *pvar_,*pdum_;
						
  if(fieldspc(stu_,fld_,&pdum_,fmt)>0){
    if(fl_output_) fmt[1]&=0xBF;
    pvar_=stubuf_+ (s(stu_,fld_)-s(stu_,1));
    scrifld(z,fmt,pvar_);
  }
}

static artik_bis()
{
  int16 k,curs=3,key,z;
									
  FOREVER{
    redo_a:
    scrget(2,20); z=1;
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
    for(k=27;k<=79;k++) scrfld(z++,6,k);
    for(k=81;k<101;k++) scrfld(z++,6,k);
    key=scrupd(0xFFFF,0x01E1);curs=3;
    if(key!=108 && key!=101 && key!=106 && key!=109) goto redo_a;
    else break;
  }
  return key;
}

static dsp_i_flag()
{
						
  if(fldlen(22,0)==0) goto endsr;
						
  fasinit(22);*u(22,2)=stu;*u(22,3)=*u(stu,1);
  if(faskeyi(22,1,1)) goto endsr;
  if(*u(22,2)!=stu) goto endsr;
  if(*u(22,3)!=*u(stu,1)) goto endsr;
						
  scraddf(119,23,78,7); scrifld(119,fm_os2,"IN");
  endsr:;
}

static calcnet(pr_offset_)
int pr_offset_;
{
  int16 k,t_ap_,prstu_;
  float accijns_,net_,q_stuks,bd_,bd_deler_,apbd_;
									
  t_ap_=18; if(sys3586==2) t_ap_=12;
  if(*f(6,18+pr_offset_)) goto calc_wpct;
  net_=*f(6,12+pr_offset_);
  if(fldlen(6,13+pr_offset_)) net_=valu_cnv(s(6,13+pr_offset_),def_munt,(double)net_,(double)0.01);
  if(fldlen(6,30+pr_offset_)) accijns_=*f(6,30+pr_offset_); else accijns_=0;
  net_-=accijns_;
  for(k=0;k<3;k++) if(fldlen(6,14+k+pr_offset_)) net_*=(100.-*f(6,14+k+pr_offset_))/100.;
  if(fldlen(6,17+pr_offset_)){
    bd_=*f(6,17+pr_offset_);
    if(fldlen(6,13+pr_offset_)) bd_=valu_cnv(s(6,13+pr_offset_),def_munt,(double)bd_,(double)0.01);
    net_-=bd_;
  }
	net_+=accijns_; 
	if(sys3652){ // afhaal en losvergoediong erbij tellen 
		if(fldlen(6,19+pr_offset_)) {
			if(sys3652==2) net_*=(100.+*f(6,19+pr_offset_))/100.;  // als %
			else net_+=*f(6,19+pr_offset_);
		}
//		if(fldlen(6,19+pr_offset_)) net_+=*f(6,19+pr_offset_);
		if(fldlen(6,20+pr_offset_)) net_+=*f(6,20+pr_offset_);
	}
  *f(6,18+pr_offset_)=net_;
  calc_wpct:;
  for(k=0;k<10;k++){
		prstu_=PrNrs[k]; if(pr_offset_) prstu_=PrNrs[k+10];
		if(fldlen(6,prstu_)==0) {net_winst[k]=0; continue;}
    bd_deler_=*f(6,18+pr_offset_);
#if FLAGCRA
		if(k<3){ t_ap_=12;bd_deler_=*f(6,12+pr_offset_)+*f(6,19+pr_offset_);} // eerste 3 VP altijd tov BRUTO-aankoopprijs + hkost (Frans 26/11/18)
		else{ t_ap_=18; if(sys3586==2) t_ap_=12;}
#endif
    if(sys3586==2) bd_deler_=*f(6,12+pr_offset_);
    else if(sys3586==1) bd_deler_=*f(6,prstu_);
		apbd_=*f(6,t_ap_+pr_offset_);
#if FLAGCRA
		if(k<3) apbd_+=*f(6,19+pr_offset_);
#endif
		if(fldlen(6,prstu_) && apbd_ && bd_deler_){
      q_stuks=0;
      if(stuksprx[k]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
      if(q_stuks==0) q_stuks=1;
      net_=*f(6,prstu_);
      if(NO /* rev_prx_calc*/ ){
				net_=apbd_* (1.+net_winst[k]/100);
				if(sys3586==1){/* marge */
					net_+=((net_-apbd_)*  net_/ apbd_) * net_winst[k]/100;
				}
				if(sys3894 & 1<<k) net_*=1.+*f(6,28)/100.;
				net_/=q_stuks;
#if FLAGGOU
				if(k<6) *f(6,21+k+pr_offset_)=valu_cnv("EUR","EUR",(double)(net_),(double)(*d(52,28))); // GOU
#else
        if(*f(6,prstu_) || net_winst[k]) *f(6,prstu_)=valu_cnv("EUR","EUR",(double)(net_),(double)(sys2830[k])); // winst%==0, enkel prijs invullen indien er al een prijs in staat
#endif
			}
			else{
				if(sys3894 & 1<<k) net_/=1.+*f(6,28)/100.;
				if(sys3586==1) bd_deler_=net_*q_stuks;/* correctie VP-prijs/stuk */
				net_winst[k]=((net_-(apbd_/q_stuks))/ (bd_deler_/q_stuks)) * 100.;
				if(*f(6,prstu_)==0) net_winst[k]=0;
      }
    }
    else net_winst[k]=0;
  }
}

/*
static calcnet()
{
  int16 k;
  float accijns_,net_,q_stuks;
									
  if(*f(6,18)) goto calc_wpct;
  net_=*f(6,12);
  if(fldlen(6,30)) accijns_=*f(6,30); else accijns_=0;
  net_-=accijns_;
  for(k=0;k<3;k++) if(fldlen(6,14+k)) net_*=(100.-*f(6,14+k))/100.;
  if(fldlen(6,17)) net_-=*f(6,17);
	net_+=accijns_; 
	if(sys3652){ // afhaal en losvergoediong erbij tellen 
		if(fldlen(6,19)) {
			if(sys3652==2) net_*=(100.+*f(6,19))/100.;  // als %
			else net_+=*f(6,19);
		}
		if(fldlen(6,20)) net_+=*f(6,20);
	}
  *f(6,18)=net_;
  calc_wpct:;
  for(k=0;k<6;k++){
    if(fldlen(6,PrNrs[k]) && *f(6,18)){
      q_stuks=0;
      if(stuksprx[k]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
      if(q_stuks==0) q_stuks=1;
      net_=*f(6,PrNrs[k]);
      if(sys3894 & 1<<k) net_/=1.+*f(6,28)/100.;
      net_winst[k]=((net_-(*f(6,18)/q_stuks))/ (*f(6,18)/q_stuks)) * 100.;
    }
    else net_winst[k]=0;
  }
}
*/
static initload()
{
 
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(15);
  kont_exist=NO;
  if(fldlen(9,1)) {fileopen(9);kont_exist=YES;}

  sysget(294,3,def_munt);
  sysget(1918,2,&sear_stt);
  sysget(2830,24,(char *)&sys2830[0]);
	sysget(3586,2,&sys3586);
	sysget(3654,16,(char *)&sys2830[6]);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3652,2,&sys3652);
  sysget(3722,2,&sys3722);
  sysget(3876,2,&sys3876);
  sysget(3892,2,&sys3892);
  sysget(3894,2,&sys3894);
  sysget(4610,60,vptekst);
  sysget(4670,6,stuksprx);
  sysget(4740,40,&vptekst[60]);
  sysget(4780,4,&stuksprx[6]);
  if(fldlen(6,2)) arcd=YES;

  sysget(3678,2,&def_taal);
  pu_2_1=u(2,1);
  pu_6_1=u(6,1);
 
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

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
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

static float rnd_vprx(fl_,type_)
float fl_;
int16 type_;
{
  float add, *pf;
							
  if(type_<0 || type_>9) type_=0; pf=&sys2830[type_];
  add=*pf;
  if(sys3618==0) add/=2.;
  add=add*.999999;
  if(*pf>0.0001){
    fl_=((long)((fl_+add)/(*pf))) * *pf;
  }
  return (float)fl_;
}

static zeros(pd,len)
char *pd;
int16 len;
{
  int16 k;
				
  for(k=0;k<len;k++) *(pd+k)='\0';
}

static disp_art(mod__)
int16 mod__;
{
/* mod__ 0: naam of code#, mod__ 2 of 3: volgens dat veld */
  int16 byte,inr=0,k,key,len2,len3,m,z,fkey=2;
  char zoek_arg[41],*ps2,*ps3,*pzoek;
  flag code_=NO;

  ps2=s(6,2);ps3=s(6,3);pzoek=ps3;
  len3=fldlen(6,3);
  if(len2=fldlen(6,2)) code_=YES;
  if(mod__==0){
    mod__=3;
    byte=*ps3;
    if(byte=='\0') {errnum=38;goto endsr;}
    if(byte=='.'){
      if(code_==NO) byte='?';
      else {mod__=2;copy(ps3+1,ps2,len2);}
    }
    if(byte=='?'){
      mod__=1;*u(6,1)=val(ps3+1);
    }
    if(byte>='0'&&byte<='9'){
      mod__=2;
      if(code_) {copy(ps3,ps2,len2);}
      else{
	if(sys3876&1) {*u(6,1)=val(s(6,3));mod__=1;}
	else mod__=3;
      }
    }
  }

  if(mod__<3){
    if(mod__==1){
      errnum=fasgetu(6);
      if(errnum==46||errnum==47)errnum=39;
    }
    if(mod__==2){
      if(sys3876&2){fkey=1;pzoek=ps2;goto select;}
      errnum=faskeyu(6,1,0);
    }
  }
  else{
    select:;
    if(len3>40)len3=40;
    *u(6,1)=0;
    copy(ps3,&zoek_arg[0],len3);zoek_arg[len3]='\0';
    k=0;
    rec_d[0]=0;
    FOREVER{
      m=0;
      FOREVER{

				if(k<0)k=0;
				fasinit(6);*u(6,1)=rec_d[k];
				copy(&zoek_arg[0],pzoek,len3);
			next_art:;
				errnum=faskeyi(6,fkey,5);
				if(errnum){
					if(k==0)goto endsr;
					else break;
				}
				if((fldlen(6,200) && *u(6,200))){
					copy(&zoek_arg[0],pzoek,len3); goto next_art;
				} // geen geblokkeerd artikel
				rec_d[k+1]=*u(6,1);rec_d[k+2]=0;
				get_prx();
				if(m==0){
					scrnum=0;/* jvgxxx */
					if(scrget(2,31)==NO) scrclrf();
					z=1;
					scrifld(z++,fm_os38,zoek_arg);
					scrifld(z++,fm_ou1_,&type_prx);
				}
				k++;

  				disp_line(k,&z);
	  			m++;

				if(m==17)break;
      }
      scrifld(105,fm_uu3,&inr);
      errnum=0;
      FOREVER{
	key=scrupd(53,0xA6);
	if(key==106) return NO;
	if(key==103 && k<TABSIZ) {inr=0;break;}
	if(key==102 && k>17) {k=k-((k-1)%17)-18;inr=0;break;}
	if(inr>k)errnum=39;
	else if(inr)break;
      }
      if(inr)break;
    }
    if(inr) {*u(6,1)=rec_d[inr];errnum=fasgetu(6);get_prx();}
  }
  endsr:
  return YES;
}

static disp_line(nr_,pz)
int16 nr_,*pz;
{
  float btw_,vp_,vp_exc,vp_inc,ap_exc;

  scrifld((*pz)++,fm_ou3,&nr_);

/* if(fldlen(6,2))scrofld((*pz)++,6,2,-1); else (*pz)++; */
  scrofld((*pz)++,6,3,30);
/* scrofld((*pz)++,6,33,9); */
  if(sys3722==NO){
    fmt_get(6,21+0); fmt[1]=fmt[1]&0xBF;                          /* output */
    scrifld((*pz)++,fmt,&vp_norm);
    scrifld((*pz)++,fm_os10,krt_str);
    vp_=*f(6,PrNrs[type_prx]);
    btw_=1.+*f(6,28)/100;
    vp_exc=vp_;vp_inc=vp_;
    if(sys3894 & (1<<type_prx)) vp_exc=vp_/btw_;
    else vp_inc=vp_*btw_;
    fmt_get(6,21+0); fmt[1]=fmt[1]&0xBF;/* output */
    scrifld((*pz)++,fmt,&vp_exc);
    scrifld((*pz)++,fmt,&vp_inc);
  }
  else{
    if(fldlen(6,34)){
      ap_exc=*f(6,34);fmt_get(6,34);
    }
    else {
      ap_exc=*f(6,18);
      if(ap_exc==0 && fldlen(6,19)) ap_exc=*f(6,19);
      fmt_get(6,18);
    }
    fmt[1]=fmt[1]&0xBF;
    scrifld((*pz)++,fmt,&ap_exc);
    (*pz)++;
  }
}
 

static get_info(select_)
int16 select_;
{
  int16 k,mode_;
									
  ram_recl=fldlen(22,0) +2;                               /* + 2 bytes hash */
  max_line=(sizeof ram /ram_recl) -1;
  hash_len=0; dat_len=ram_recl-2;
  zeros(ram,sizeof ram);
  fasinit(22);*u(22,2)=stu;*u(22,3)=*u(stu,1); mode_=1; k=0;
  FOREVER{
    next:;
    if(faskeyi(22,1,mode_)) break; mode_=2;
    if(*u(22,2)!=stu) break;
    if(*u(22,3)!=*u(stu,1)) break;
    stu2ram(22,k);
    k++; if(k>=max_line) break;
  }
  return k;
}

static dsp_info()
{
  int16 j,k,curs=1,z_base_,key,z,start_,d_mode_=NO,curspos_;
  char *pdum,dumm_[10],*pvar;
 
  if(fldlen(22,0)==0) goto endsr;
  get_info(NO);
  pdum=&dumm_[0];
  scrnum=0; start_=0;
  FOREVER{
    redo:
    scrget(2,89);z=1;
		if(fldlen(22,7)) scraddpicto(1,0,11,3,2,1,605,0,0,"Alarm"); 
    scraddpicto(3,0,76,0,4,2,105,1,7,"^!B0019B");
		j=start_+1; scrifld(z++,fm_ou3,&j);
    j+=D_LIN_SCR-1; scrifld(z++,fm_ou3,&j);
    if(fldlen(stu,2)) scrofld(z++,stu,2,-1); else scrofld(z++,stu,1,-1);
    scrofld(z++,stu,3,-1);
    z_base_=z;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      if(fieldspc(22,4,&pdum,fmt)>0){
				if(d_mode_==NO) fmt[1]&=0xBF;
				pvar=ram+(j*ram_recl + (s(22,4)-s(22,1)));
				scrifld(z++,fmt,pvar);
      }
      if(fieldspc(22,7,&pdum,fmt)>0){
				if(d_mode_==NO) fmt[1]&=0xBF;
	      pvar=ram+(j*ram_recl + (s(22,7)-s(22,1)));
	      scrifld(z++,fmt,pvar);
      } else z++;
      if(fieldspc(22,6,&pdum,fmt)>0){
				if(d_mode_==NO) fmt[1]&=0xBF;
				pvar=ram+(j*ram_recl + (s(22,6)-s(22,1)));
				scrifld(z++,fmt,pvar);
      }
      if(fieldspc(22,10,&pdum,fmt)>0){
				pvar=ram+(j*ram_recl + (s(22,10)-s(22,1)));
				scrifld(z++,fmt,pvar);
      }

    }
    key=scrupd(-1,0x3BF);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000; 
		if(key==5001){curs=fldcurs;goto redo;}
		if(key==5003){curs=fldcurs;goto redo;}
    if(key==101 || key==106) goto endsr;
    //if(key==104){
    //  j=(curspos_-z_base_)/4;j+=start_;
    //  ins_lin(22,j);
    //  curs=curspos_;goto redo;
    //}
    //if(key==105){
    //  j=(curspos_-z_base_)/4;j+=start_;
    //  del_lin(22,j);
    //  curs=curspos_;goto redo;
    //}
//    if(key==110) copy_info();
//    if(key==109) {if(d_mode_) d_mode_=NO; else d_mode_=YES;}
    if(key==108)break;
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
 //   if(key==172) {print_screen(YES);}
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){ram2stu(22,k+start_);if(*s(22,10)=='\0') {j=k;break;}}
    curs=z_base_+j*4;
  }
	//fasunlck(-2);
 // for(k=0;k<max_line;k++){
 //   ram2stu(22,k);
 //   if(*s(22,10)){
 //     *u(22,2)=stu; *u(22,3)=*u(stu,1); *u(22,5)=k;
 //     if(*u(22,4)==0) *u(22,4)=*u(25,2);
 //     if(*u(22,1)) fasupd(22); else fasadd(22);
 //   }
 //   else if(*u(22,1)) faskill(22);
 // }
	//fasunlck(-1);
  endsr:;/* stop */
}
 
static ram2stu(stu_,lin_)
int16 stu_,lin_;
{
  copy(ram+(lin_*ram_recl),s(stu_,1),dat_len);
  copy(ram+(lin_*ram_recl)+dat_len,&hash_val,2);
}

static stu2ram(stu_,lin_)
int16 stu_,lin_;
{
  copy(s(stu_,1),ram+(lin_*ram_recl),dat_len);
  copy(&hash_val,ram+(lin_*ram_recl)+dat_len,2);
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
 
static get_prx()
{
  int16 k,m,nokort,pos_;
  float kort_=0,vp_=0,bd_accijn,hl_kort_,EUR_kort_=0;
  uint16 dt_p_upd;
 
  pos_=0;hl_kort_=0; dt_p_upd=*u(25,2);
  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd){pos_=94;prx_op_dt=YES;}
  if(pos_) vp_=*f(6,PrNrs[type_prx+10]); else vp_=*f(6,PrNrs[type_prx]); 
	if(*i(6,9)!=99) vp_norm=vp_;
  if(fldlen(2,18)) kort_=*f(2,18); else kort_=0;
  nokort=NO;
	if(fldlen(6,104) && *s(6,104)=='J') nokort=YES;
  *u(52,1)=*i(6,9);
  if(fasgeti(52)==0){
    if(fldlen(52,21) && *s(52,21)=='N') nokort=YES;
  }
  if(kont_exist){
    fasinit(9);*u(9,2)=*pu_2_1;*u(9,3)=*pu_6_1;
    m=get_contr(1);if(m==0) nokort=NO;// wel korting indien expliciet 
    if(m && fldlen(9,18)){
      *u(9,18)=*u(6,7);*u(9,19)=*u(6,9);m=get_contr(2);
      if(m){
				*u(9,19)=0;m=get_contr(2);
      }
			if(m && fldlen(6,101)){ // merk/ producent 
        *u(9,18)=*u(6,101)+30000;*u(9,19)=*u(6,9);m=get_contr(2);
        if(m){
          *u(9,19)=0;m=get_contr(2);
        }
      }
      if(m){
	*u(9,18)=0;*u(9,19)=*u(6,9);m=get_contr(2);
	if(m==0 && (fldlen(6,104)==0 || *s(6,104)!='J')) nokort=NO;/* wel korting indien expleciet contract op groep */
      }
    }
    if(m==0){
      if(fldlen(9,72) && *u(9,72) && *u(9,72)<=dt_p_upd){
				prx_op_dt=YES;
				if(*f(9,75)) vp_=*f(9,75);
				if(*i(6,9)!=99 && vp_>vp_norm) vp_norm=vp_;
				kort_=*f(9,73);/* korting in % altijd overrulen */
				EUR_kort_=*f(9,74);
				if(*f(9,74)) vp_-=*f(9,74);
				if(fldlen(9,81)) hl_kort_=*f(9,81);
      }
      else{
#if FLAGGOU // afwijkend prijstype in contract
  			if(*s(9,23)){
				  k=*s(9,23)-'0'; if(k>=0 && k<=5 && fldlen(6,PrNrs[k])) vp_=*f(6,PrNrs[k]);
			  }
#endif
				if(*f(9,8)) vp_=*f(9,8);
				if(*i(6,9)!=99 && vp_>vp_norm) vp_norm=vp_;
				kort_=*f(9,6);/* korting in % altijd overrulen */
				EUR_kort_=*f(9,7);
				if(*f(9,7)) vp_-=*f(9,7);
				if(fldlen(9,20)) hl_kort_=*f(9,20);
      }
    }
  }
  if(fldlen(6,37)==0 || *f(6,37)==0) hl_kort_=0;
  else{                                        /* omrekenen naar verpakking */
    hl_kort_=hl_kort_* *f(6,37)/100;
  }
#if FLAGEPD | FLAGVDW // EUR korting als hl-korting gebruiken
	vp_+=EUR_kort_; hl_kort_+=EUR_kort_;
#endif
  bd_accijn=0;
  if(fldlen(6,30) && *i(6,9)!=99){
    bd_accijn=*f(6,30+pos_);
  }

  if((hl_kort_ || kort_) && nokort==NO){
    vp_=(vp_-bd_accijn)*(100.- kort_)/100.+bd_accijn;
    vp_-=hl_kort_;
  }
  if(*i(6,9)!=99){
    vp_=rnd_vprx((float)vp_,type_prx);
    zero(krt_str,sizeof krt_str);
    if(kort_ && nokort==NO){
      flt2str(krt_str,kort_,4,2);copy(" %",&krt_str[7],2);
    }
  }
  *f(6,PrNrs[type_prx])=vp_;
}
 
static get_contr(keynr_)
int16 keynr_;
{
  int16 k;
						
  if(faskeyi(9,keynr_,0)) return YES;
  for(k=0;k<3;k++) if(*f(9,6+k)) return NO;
  for(k=20;k<=24;k++){
    if(fldlen(9,k) && *f(9,k)) return NO;
  }
  if(fldlen(9,16) && *i(9,16)) return NO;
  return YES;
}
 
static flt2str(ps_,bd_,len_,dec_)
float bd_;
char *ps_;
int16 len_,dec_;
{
  int16 k;
  double bedrag_,add_=0,fact_;
  long val_,value;
							
  fact_=1; for(k=0;k<dec_;k++) fact_*=10;
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*fact_+add_;value=val_/fact_;
  stcli_d(ps_,value,len_,1); ps_+=len_;
  value=val_-value*fact_;
  if(dec_){
    *(ps_++)=',';
    if(value<0) value=-value;
    stcli_d(ps_,value,dec_,0);
  }
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
//  if(DspTotRek==NO) parmcall[7]=0x04;
  parmcall[7]=0x04; parmcall[7]+=0x08; // enkel actieve artikels
	parmcall[7]+=0x10; // ook bij 1 artikel het selectiescherm tonen
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}