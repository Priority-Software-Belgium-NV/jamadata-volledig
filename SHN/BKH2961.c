/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH2961GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH2961dat
#define ovlcod BKH2961cod
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

char ovldat[] = "bkh2961  00:01 05/11/10 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define MAXFLD          120
#define D_LIN_SCR       17
#define CALCDEF         "%N%0%0%0%0%0%0%0%0%0"
#define STU             6

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];
				
extern char *s();
extern int16 *i();
extern uint16 *u();
static uint16 hash(),hashbuf();
extern long *l();
extern long val();
extern float *f();
static float rnd_prx();
extern double *d(),valu_cnv();

static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_uf4_1[] = {6,0xD4,4,1,0x60,0};
static char fm_of4_1[] = {6,0x94,3,1,0x60,0};
					
static float net_winst[10],btw_pct[8],sys3614,def_btw,sys2830[10];
static long def_grb;
static char stubuf[2][150],fmt[40];
static char vptekst[100],stuksprx[10],def_munt[4],def_grbex[2],oldnm[50];
static char *calctype,reserv[512];
static flag sys3586,sys3618,sys3894,sys3976,sys2698,suppr_wi,klcd,lvcd,rev_prx_calc;
static int16 parmmain[8],stu=6,sys3652,sys3892;
static uint16 dt_beg,dt_end;
static char orig_lev[1000];
static char ram[15000],buf1000[1000],nm_20[20],type_info;
static int16 dat_len,ram_recl,hash_len,max_line;
static uint16 hash_val;
  
ovlcod(parmval)
int16 parmval;
{
  copy((char *)parmcall,(char *)parmmain,sizeof parmmain);
  initload();
  copy(s(1,1),orig_lev,fldlen(1,0));
  retcall=fichupd(parmval);
  copy(orig_lev,s(1,1),fldlen(1,0));
  copy((char *)parmmain,(char *)parmcall,sizeof parmcall);
  ovlexit(-1);
}
 
static initload()
{
  int16 k;
 
  fileopen(1);/* uit veiligheid */
	if(fldlen(22,1)) fileopen(15);
 
  sysget( 294,4,def_munt);
  sysget(1048,32,&btw_pct[0]);
  sysget(1084,4,&def_btw);
	sysget(2698,2,&sys2698);
	sysget(2830,24,(char *)&sys2830[0]);
	sysget(3654,16,(char *)&sys2830[6]);
  sysget(3586,2,&sys3586);
  sysget(3608,2,def_grbex);
  sysget(3610,4,&def_grb);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
	sysget(3652,2,&sys3652);
  sysget(3892,2,&sys3892);if(sys3892 & (1<<1)) suppr_wi=YES;
  sysget(3894,2,&sys3894);
  sysget(3976,2,&sys3976);
  sysget(4610,60,vptekst);
  sysget(4670,6,stuksprx);
  sysget(4740,40,&vptekst[60]);
  sysget(4780,4,&stuksprx[6]);

  calctype=s(52,22);
}
 
static fichupd(mode)/* 0 = display, 1=update, 2=add */
int16 mode;
{
  int16 g,j,k,curs=2,key,z,len_,pos_1_4_,curspos_,z_prx_,pr_offset_,pnr_,prstu_,only_dsp;
  char *p_stu_3,buf1000[1000],nm_groep[50],nm_subgroep[50];
  uint16 last_grp;
	
	only_dsp=NO; if(mode==0 || (sys2698 && mode==1)) only_dsp=YES;
  pos_1_4_=s(1,4)-s(1,1);
  copy(s(1,1),buf1000,fldlen(1,0)); // leverancier bewaren om niet te verminken in moederpgm
  p_stu_3=s(6,3); rev_prx_calc=NO; pr_offset_=0; 
  if(mode==2){
    if(fldlen(6,13)) copy(def_munt,s(6,13),3);
    if(fldlen(6,28) && *f(6,28)==0) *f(6,28)=def_btw;
		if(fldlen(6,31) && *f(6,31)==0) *f(6,31)=1;
    if(len_=fldlen(6,39)){
      if(len_>2) len_=2;
      copy(def_grbex,s(6,39),len_);
    }
    if(fldlen(6,40)) *l(6,40)=def_grb;
    if(fldlen(6,42)) *f(6,42)=1;
#if FLAGEET
			*s(6,67)='J';  // standaard op laadbon
#endif
#if FLAGSAS
			*s(6,104)='J';  // standaard GEEN korting toegestaan bioj nieuw artikel
#endif
  }
  fasinit(52);zero(nm_groep,sizeof nm_groep); zero(nm_subgroep,sizeof nm_subgroep); 
	if(mode==2)  *u(6,7)=*u(1,1); // bestaande leverancier nemen
	else{
		fasinit(1);*u(1,1)=*u(6,7); fasgeti(1);
	}
  copy(s(1,1),stubuf[0],pos_1_4_);
  if(fldlen(6,101)){
    fasinit(1);*u(1,1)=*u(6,101); fasgeti(1);
    copy(s(1,1),stubuf[1],pos_1_4_);
  }
  if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);}
	zero(nm_groep,sizeof nm_groep); zero(nm_subgroep,sizeof nm_subgroep); 
	if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);copy(s(52,14),nm_groep,fldlen(52,14));}
	if(fldlen(6,103) && *u(6,103) && *u(6,9)){
		fasinit(52);*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;
		if(fasgeti(52)==0) copy(s(52,14),nm_subgroep,fldlen(52,14));
  }
  calcnet(0);

  FOREVER{
redo:
#if FLAGGBL
  	if(only_dsp){sys3892=6; suppr_wi=YES;}
  	else {sys3892=0; suppr_wi=NO;}
#endif
		if(fldlen(6,200)){
			if(*u(6,200)) ConLook(1); else   ConLook(0);
		}
		k=19; scrnum=0;scrget(2,k); z=1;	// if(fldlen(6,185)) k=59; 
    scrfld(z++,25,1);
    if(fldlen(6,2)) scrfld(z++,6,2); else scrofld(z++,6,1,-1);
		if(fldlen(6,200) && mode==1){
			if(*u(6,200)==1) scrchat(z-1,0xB); else scrchat(z-1,0xFF);
			if(*u(6,200)==1) scraddpicto(7,z-1,0,0,2,1,70,0,4,"Maak actief"); else scraddpicto(7,z-1,0,0,2,1,71,0,3,"Blokkeer");
		}
		if(fldlen(6,195)){
			if(*s(6,195)=='J') scraddpicto(8,z-1,2,0,2,1,32,0,4,"NIET in webshop"); else scraddpicto(8,z-1,2,0,2,1,32,0,3,"Toon in webshop");
		}
		if(fldlen(6,194)){
			k=2; if(fldlen(6,195)) k=4;
			if(*s(6,194)=='J') scraddpicto(10,z-1,k,0,2,1,82,0,4,"NIET in B2B-webshop"); else scraddpicto(10,z-1,k,0,2,1,82,0,3,"Toon in B2B-webshop");
		}
		if(fldlen(6,104)){
			if(*s(6,104)=='J') {
				if(fldlen(6,185)) scraddpicto(9,0,71,6,4,2,88,0,3,"Korting toestaan"); 
				else scraddpicto(9,0,12,13,4,2,88,0,3,"Korting toestaan"); 
			}
			else{
				if(fldlen(6,185)) scraddpicto(9,0,71,6,4,2,88,0,4,"Blokkeer korting");
				else scraddpicto(9,0,12,13,4,2,88,0,4,"Blokkeer korting");
			}
		}
    for(k=3;k<=6;k++) scrfld(z++,6,k);
    scrbfld(z++,1,1+lvcd,stubuf[0],YES);
    scrbfld(z++,1,3,stubuf[0],NO);
    scrfld(z++,6,8);
    if(fldlen(6,101)) scrbfld(z++,1,3,stubuf[1],NO);
    scrfld(-z,6,9);z++;scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_groep);if(mode==2) scraddpicto(3,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		if(fldlen(6,103)){
			scrfld(-z,6,103);z++;scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_subgroep);
//			if(mode==2 && *u(6,9)) scraddpicto(6,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		}
    for(k=10;k<=11;k++) scrfld(z++,6,k);
		for(k=12;k<=20;k++) if(!(sys3892 & 0x04)) scrfld(z++,6,k); else z++;
    z_prx_=z;
		if(fldlen(6,185)){
			for(k=0;k<5;k++){
				pnr_=k;
redo_rechts:;  
				if(pr_offset_) prstu_=PrNrs[pnr_+10]; else prstu_=PrNrs[pnr_];
				if(fldlen(6,prstu_)){
					scrifld(z++,fm_os6,&vptekst[pnr_*10]);
					fmt_get(6,prstu_); if(rev_prx_calc) fmt[1]&=0xBF;
					scrifld(z++,fmt,f(6,prstu_)); if(pr_offset_) scrchat(z-1,0x9);
					if(sys3894 & 1<<pnr_) scrifld(z++,fm_os2,"IN");
					else scrifld(z++,fm_os2,"EX");
					if(suppr_wi==NO){
						if(rev_prx_calc) scrifld(z++,fm_uf4_1,&net_winst[pnr_]);
						else scrifld(z++,fm_of4_1,&net_winst[pnr_]);
					}
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
					fmt_get(6,prstu_); if(rev_prx_calc) fmt[1]&=0xBF;
					scrifld(z++,fmt,f(6,prstu_)); if(pr_offset_) scrchat(z-1,0x9);
					if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
					else scrifld(z++,fm_os5,"Excl.");
					if(suppr_wi==NO){
						if(rev_prx_calc) scrifld(z++,fm_uf4_1,&net_winst[k]);
						else scrifld(z++,fm_of4_1,&net_winst[k]);
					}
					else z++;
				}
				else for(j=0;j<4;j++) streepje(z++);
			}
		}
    if(mode==0) curs=-1;
    key=scrupd(curs,0x03EB);curs=2;curspos_=fldcurs;
		if(fldlen(6,200)) ConLook(0);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(*u(25,4)!=110 && key==15 && only_dsp){only_dsp=NO;goto redo;}
		if(key==5003){// uitgebreid groep zoeken
			if(search(52,98)) {
				fasinit(52); if(*u(6,9)){	*u(52,1)=*u(6,9);fasgeti(52);}
			}
  		else *u(6,9)=*u(52,1);
			zero(nm_groep,sizeof nm_groep); 
			if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);copy(s(52,14),nm_groep,fldlen(52,14));}
			if(fldlen(6,103)){
				zero(nm_subgroep,sizeof nm_subgroep); 
				if(*u(6,9)!=last_grp || *u(6,9)==0) *u(6,103)=0; // SUBGROEP WISSEN
				if(*u(6,103) && *u(6,9)){
					fasinit(52);*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;
					if(fasgeti(52)==0) copy(s(52,14),nm_subgroep,fldlen(52,14));
  			}
			}
			last_grp=*u(6,9);
			goto redo;
		} 
    if(key==106){
			copy(buf1000,s(1,1),fldlen(1,0)); // leverancier restoren
      if(mode==2) return NO;
      else return YES;
    }
		//if(key==5006 && fldlen(6,103)){
		//	*u(6,103)=SelecteerSubgroep(*u(6,9)); 
		//	fasinit(52);
		//	if(*u(6,103)){*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;fasgeti(52);}
		//	copy(s(52,14),nm_subgroep,fldlen(52,14));
		//	goto redo;
		//}
		if(key==5007 && fldlen(6,200)){ // blokkeer
			if(*u(6,200)) *u(6,200)=0; else *u(6,200)=1;
			goto redo;
		}
		if(key==5008 && fldlen(6,195)){ // webshop artikel
			if(*s(6,195)=='J') *s(6,195)='N'; else *s(6,195)='J';
			goto redo;
		}
		if(key==5010 && fldlen(6,194)){ // B2B-webshop artikel
			if(*s(6,194)=='J') *s(6,194)='N'; else *s(6,194)='J';
			goto redo;
		}
		if(key==5009 && fldlen(6,104)){ // blokkeer korting 
			if(*s(6,104)=='J') *s(6,104)='N'; else *s(6,104)='J';
			goto redo;
		}
		fasinit(52);zero(nm_groep,sizeof nm_groep); 
		if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);copy(s(52,14),nm_groep,fldlen(52,14));}
		zero(nm_subgroep,sizeof nm_subgroep); 
		if(fldlen(6,103)){
			if(*u(6,9)!=last_grp || *u(6,9)==0) *u(6,103)=0; // SUBGROEP WISSEN
			if(*u(6,103) && *u(6,9)){
				if(*u(6,103)>10) errnum=34;
				else{
  				fasinit(52);*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;
	  			if(fasgeti(52)==0) copy(s(52,14),nm_subgroep,fldlen(52,14));
					if(nm_subgroep[0]=='\0') errnum=34;
				}
  		}
			if(errnum) {curs=curspos_; goto redo;}
		}
		last_grp=*u(6,9);
    if(*u(6,9)){
			if(key==18){curs=curspos_+1;goto redo;}
    }
    g=*p_stu_3;
    if(g=='\0'){
      if(key==101) {copy(buf1000,s(1,1),fldlen(1,0));return NO;} // leverancier restoren
      errnum=38;curs=3;goto redo;
    }
		if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo;}
    if(fldlen(6,2)){
      if(g<'A' || g>'z' || (g>'Z' && g<'a')) {errnum=30;curs=3;goto redo;}
      if(*s(6,2)=='\0'){errnum=38;curs=2;goto redo;}
    }
    if(stubuf[0][s(1,3)-s(1,1)]=='\0'){errnum=30;curs=8;goto redo;}
    if(*(uint16 *)&stubuf[0][pos_1_4_]!=hashbuf(stubuf[0],pos_1_4_)){
      fasinit(1);copy(&stubuf[0][s(1,3)-s(1,1)],s(1,3),fldlen(1,3));
      if(search(1,0)){curs=8;goto redo;}
      copy(s(1,1),stubuf[0],pos_1_4_);
      *(uint16 *)&stubuf[0][pos_1_4_]=hashbuf(stubuf[0],pos_1_4_);
      *u(6,7)=*u(1,1);
    }
    if(fldlen(6,101) && *(uint16 *)&stubuf[1][pos_1_4_]!=hashbuf(stubuf[1],pos_1_4_)){
      fasinit(1);copy(&stubuf[1][s(1,3)-s(1,1)],s(1,3),fldlen(1,3));
      if(search(1,0)){curs=10;goto redo;}
      copy(s(1,1),stubuf[1],pos_1_4_);
      *(uint16 *)&stubuf[1][pos_1_4_]=hashbuf(stubuf[1],pos_1_4_);
      *u(6,101)=*u(1,1);
    }

    if(fldlen(6,9)){
      if(*i(6,9)<1 || *i(6,9)>99){
				if(fldlen(6,101)) curs=11; else curs=10;
				errnum=34;goto redo;
			}
    }
    if(key==109) key=artik_bis(mode);
    if(mode==2 && key==110) {
			if(rev_prx_calc) {calcnet(0);rev_prx_calc=NO;}
			else {rev_prx_calc=YES;}
			curs=z_prx_;goto redo;
    }
    calcnet(0);
  //  if(mode==2 && !sys3976) fill_dfprx();
    if(key==106){
			copy(buf1000,s(1,1),fldlen(1,0));
      if(mode==2) return NO;
      else return YES;
    }
		if(key==102 && ovltest(268)) ovlcall(268,1);
    if(key==112 && *u(6,1)) {dsp_info(); goto redo;}
    if(key!=108 && key!=101 && key!=111) goto redo;
		if(fldlen(6,198)) *u(6,198)=procid;
		if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
    if(mode==1){
      errnum=fasupd(6);
      fasflush(0);
    }
    else if(mode==2 || mode==3){
      errnum=fasadd(6);
      fasflush(0);
    }
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
	copy(buf1000,s(1,1),fldlen(1,0));
  if(key==101) return NO;/* stop */
  return YES;
}




static get_newcode()
{
  int16 j,k,g,code_len_,num_len_,fmt_len_;
  long min_kod_=1,max_kod_,lbd_;
  char str_[15],code_[15],kar_,kod_fmt_[15],buf1000[1000];


  if(stu!=1 && stu!=2 && stu!=6) return NO;
  if(fldlen(stu,2)==0) return NO;
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

static uint16 hashbuf(buf_,len_)
char *buf_;
int16 len_;
{
  char *ps;
  int16 k;
  uint16 fuval=0;
					
  k=len_;ps=buf_;
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
}

static artik_bis(mode)
int16 mode;
{
  int16 k,curs=3,key,z;
 
  FOREVER{
    redo:
    scrget(2,20); z=1;
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
    for(k=27;k<=79;k++) scrfld(z++,6,k);
    for(k=81;k<101;k++) scrfld(z++,6,k);
    if(mode==0) curs=-1;
    key=scrupd(curs,0x03E1);curs=3;
    if(key==106) break;
    for(k=0;k<8;k++) if(*f(6,28)==btw_pct[k]) break;
    if(k==8) {curs=3;errnum=34;goto redo;}

    if(key==110 && fldlen(6,70) && mode>0){
      ean13c(s(6,70));
      ean13c(s(6,71));
    }
    if(key==112 && *u(6,1)) {dsp_info(); goto redo;}
    if(key!=108 && key!=101 && key!=109) goto redo;
    else break;
  }
  return key;
}

static ean13c(p)/* vers. 00:01 25/02/94 */
char *p;
{
  int16 k, sum;
									
  for (k=0; k<12; k++) {
    if (*(p+k)==0) return YES;
  }
  sum=0;
  for (k=0; k<6; k++) {
    sum+=((*p-'0')+3*(*(p+1)-'0'));
    p+=2;
  }
  *p='0'+(10-(sum%10))%10;
  return NO;
}

static fill_dfprx()
{
 
  float pr_, btw_, q_stuks;
  int16 g,k,fld_,t_ap_,max_vp_;
  char *ptov;
									
	max_vp_=10; if(fldlen(6,PrNrs[6])==0 || fldlen(52,22)<20 || fldlen(52,30)==0) max_vp_=6; 
  for(k=0;k<max_vp_;k++) if(fldlen(6,PrNrs[k]) && *f(6,PrNrs[k])==0) break;
  if(k>=max_vp_) goto endsr;
  calcnet(0);
  q_stuks=0; btw_=*f(6,28);
  if(fldlen(6,31)) q_stuks=*f(6,31);
  if(q_stuks==0) q_stuks=1;
  t_ap_=18; if(sys3586==2) t_ap_=12;

  copy(s(6,1),buf1000,fldlen(6,0));
	if(fldlen(6,103)){fasinit(52);*u(52,1)=*u(6,9);if(*u(52,1)) fasgeti(52);}
  g=0; for(k=0;k<fldlen(52,22);k++) g+=*(calctype+k);
  if(g==0) copy(CALCDEF,calctype,fldlen(52,22));
  fasinit(6);
  *f(6,18)=100;*f(6,12)=100;
  for(g=0;g<max_vp_;g++){
    ptov=calctype+1+g*2;fld_=0;
    if(*ptov=='B') fld_=12;
    else if(*ptov=='N') fld_=18;
    else if(*ptov>='0' && *ptov<='8') fld_=PrNrs[*ptov-'0'];
    if(fld_ && fld_<(PrNrs[g])){
			if(g<6) *f(6,PrNrs[g])=*f(6,fld_)*(1.+*f(52,2+g*2)/100.);
			else *f(6,PrNrs[g])=*f(6,fld_)*(1.+*f(52,30+(g-6)*2)/100.);
		}
    else *f(6,PrNrs[g])=0;
    if(stuksprx[g]=='J') *f(6,PrNrs[g])/=q_stuks;
  }
  calcnet(0);
  copy(buf1000,s(6,1),fldlen(6,0));
  for(g=0;g<max_vp_;g++){
    if(*f(6,PrNrs[g])==0){
      pr_=*f(6,t_ap_);
      pr_+=*f(6,t_ap_) * net_winst[g]/100.;
      if(sys3894 & 1<<g) pr_=pr_* (1.+btw_/100.);
#if FLAGGOU
      *f(6,PrNrs[g])=valu_cnv("EUR","EUR",(double)(pr_),(double)(*d(52,28))); // GOU
#else
      *f(6,PrNrs[g])=valu_cnv("EUR","EUR",(double)(pr_),(double)(sys2830[g]));
#endif
    }
  }
  calcnet(0);
  endsr:;
 
}

static float rnd_prx(fl_)
float fl_;
{
  float add, *pf;
						
  pf=&sys3614;
  add=*pf;
  if(sys3618==0) add/=2.;
  add=add*.999999;
  if(*pf>0.0001){
    fl_=((long)((fl_+add)/(*pf))) * *pf;
  }
  return (float)fl_;
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
		if(fldlen(6,prstu_) && apbd_ && (bd_deler_ || rev_prx_calc)){
      q_stuks=0;
      if(stuksprx[k]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
      if(q_stuks==0) q_stuks=1;
      net_=*f(6,prstu_);
      if(rev_prx_calc){
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
    scrget(2,89);z=1;scraddpicto(3,0,76,0,4,2,105,1,7,"^!B0019B");
		if(fldlen(22,7)) scraddpicto(1,0,11,3,2,1,605,0,0,"Alarm"); 
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
    key=scrupd(curs,0x3BF);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000; 
		if(key==5001){curs=fldcurs;goto redo;}
		if(key==5003){curs=fldcurs;goto redo;}
    if(key==101 || key==106) goto endsr;
    if(key==104){
      j=(curspos_-z_base_)/4;j+=start_;
      ins_lin(22,j);
      curs=curspos_;goto redo;
    }
    if(key==105){
      j=(curspos_-z_base_)/4;j+=start_;
      del_lin(22,j);
      curs=curspos_;goto redo;
    }
    if(key==110) copy_info();
    if(key==109) {if(d_mode_) d_mode_=NO; else d_mode_=YES;}
    if(key==108)break;
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
//    if(key==172) {print_screen(YES);}
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){ram2stu(22,k+start_);if(*s(22,10)=='\0') {j=k;break;}}
    curs=z_base_+j*4;
  }
	fasunlck(-2);
  for(k=0;k<max_line;k++){
    ram2stu(22,k);
    if(*s(22,10)){
      *u(22,2)=stu; *u(22,3)=*u(stu,1); *u(22,5)=k;
      if(*u(22,4)==0) *u(22,4)=*u(25,2);
      if(*u(22,1)) fasupd(22); else fasadd(22);
    }
    else if(*u(22,1)) faskill(22);
  }
	fasunlck(-1);
  endsr:;/* stop */
}

static copy_info()
{
  int16 k,key,mode_,smode_;
  uint16 adr_,mrec_,rec_;
									
  copy(s(stu,1),buf1000,fldlen(stu,0));
  adr_=4128; if(stu==2) adr_=4130; else if(stu==6) adr_=4132;
  sysget(adr_,2,&mrec_); fasinit(stu); if(mrec_) {*u(stu,1)=mrec_;fasgeti(stu);}
  FOREVER{
    redo:;
    scrget(1,5);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_os38,"DE INFO OVER TE NEMEN ?");
    scrfld(4,stu,3);scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    key=scrupd(4,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
    if(key==111) ovlexit(-1);
  	smode_=0;	if(key==5001) smode_=98;
	  if(search(stu,smode_)) goto redo;
    break;
  }
  mrec_=*u(stu,1);sysput(adr_,2,&mrec_);
  for(k=max_line-1;k>=0;k--){
    ram2stu(22,k); if(*u(22,1) || *s(22,10)) break;
  }
  if(k>=max_line) goto endsr;
  fasinit(22);*u(22,2)=stu;*u(22,3)=mrec_; mode_=1; k=k+1;
  FOREVER{
    next:;
    if(faskeyi(22,1,mode_)) break; mode_=2;
    if(*u(22,2)!=stu) break;
    if(*u(22,3)!=mrec_) break;
    rec_=*u(22,1); *u(22,1)=0; *u(22,4)=0;             /* forceren te adden */
    stu2ram(22,k);
    k++; if(k>=max_line) break;
    *u(22,1)=rec_; fasgeti(22);
  }
  endsr:;
  copy(buf1000,s(stu,1),fldlen(stu,0));
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
    if(select_){
      if(dt_beg && *u(22,4)<dt_beg) goto next;
      if(dt_end && *u(22,4)>dt_end) goto next;
      if(type_info && *s(22,6)!=type_info) goto next;
    }
    stu2ram(22,k);
    k++; if(k>=max_line) break;
  }
  return k;
}


static ins_lin(stu_,lin_)
int16 stu_,lin_;
{
  int16 k;
								
  if(stu_==22){
    ram2stu(stu_,max_line-1);
    if(*u(22,1)) faskill(stu_);
  }
  for(k=max_line-2;k>=lin_;k--){
    ram2stu(stu_,k);
    stu2ram(stu_,k+1);
  }
  zeros(ram+ram_recl*lin_,ram_recl);
}

static del_lin(stu_,lin_)
int16 stu_,lin_;
{
  int16 k;
 
  if(stu_==22){
    ram2stu(stu_,lin_);
    if(*u(22,1)) faskill(stu_);
  }
  for(k=lin_;k<max_line-1;k++){
    ram2stu(stu_,k+1);stu2ram(stu_,k);
  }
  zeros(ram+ram_recl*(max_line-1),ram_recl);
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

static uint16 hash(stu_)
int16 stu_;
{
  char *ps;
  int16 k;
  uint16 fuval=0;
					
  k=hash_len;ps=s(stu_,1);
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
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

static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
}
 
static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
  parmcall[1]=1;/* bits : 0 = display, 1=update, 2=add */
  parmcall[2]=0;
  parmcall[3]=0;
  parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}
 
