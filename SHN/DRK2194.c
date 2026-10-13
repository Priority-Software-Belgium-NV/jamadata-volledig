/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK2194GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK2194dat
#define ovlcod DRK2194cod
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
__declspec(dllimport) unsigned char PrintPaperNr;

char ovldat[] = "drk2194  00:01 25/06/07 (c) Jamadata";
/* aanpassen groepen V.9.4 */

// FLAGCOC : kaartpercentage 52,25
// FLAGGOU : afronding prijs 52,28
// FLAGLEA : groepen : soort was (52,23) --> ander scherm
  
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXFLD          120
#define flag            uint16
#define CALCDEF         "%N%0%0%0%0%0%0%0%0%0"

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

extern char *s();
extern int16 *i();
extern uint16 *u();
static uint16 hash();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();

static int16 stu,chk_btoeg=0,free,key21;
static int16 lvcd,klcd;
static uint16 def_qfak,inq_grp;
static char nm_20[20],nm_dehr[52],taal_i,talen[4],def_grbex[2],oldnm[50];
static char *calctype;
static flag sys3618;
static float def_btw, btw_pct[8],sys3614;
static long def_grb;
static char vptekst[100],stuksprx[10];

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_uf7_1[] = {6,0xD4,7,1,0x60,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_uf4_1[] = {6,0xD4,4,1,0x60,0};
static char fm_uf3_0[] = {6,0xD4,3,0,0x70,0};
static char fm_of7_1[] = {6,0x94,7,1,0x60,0};
static char fm_of5_0[] = {6,0x94,5,0,0x60,0};
static char fm_of4_3[] = {6,0x94,4,3,0x60,0};
static char fm_of4_0[] = {6,0x94,4,0,0x60,0};
static char fm_of4_1[] = {6,0x94,3,1,0x60,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_btw[]   = {6,0x94,2,1,0x20,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_u_SI[]  = {11,0xC8,1,0,1,0,'S','S','I','I',0};
static char fm_of4_2[] = {6,0x94,4,2,0x70,0};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,0x09,0,'A','A','N','N',0};
static char fm_u_AK[]  = {11,0xC8,1,0,1,0,'A','A','K','K',0};
static char fm_uPB[]   = {11,0xC8,1,0,1,0,'%','%','B','B',0};
static char fm_uNB[]   = {11,0xC8,1,0,1,0,'N','N','B','B',0};
static char fm_u09NB[] = {13,0xC8,1,0,1,0,'0','9','N','N','B','B',0};
							
static char buf600[600];
 
static char def_munt[4],fmt[40];
static uint16 dt_beg,dt_end;
static flag sear_stt,sys1854,sys2698;
static char sys3896[6];
static flag sys3586,sys3894,sys3652;
static flag suppr_wi,rev_prx_calc;
static float net_winst[10];

static int16 def_taal;

ovlcod()
{
  initload();
  execgr();
  ovlexit(-1);
}

static execgr()
{
  flag updfield;
  int16 key;
  char choice;
 
  if(fldlen(52,1)==0) {errnum=12;goto endsr;}
	fasinit(52);fasinfo(52,1); // zorgen dat alle groepen bestaan tot 99
  if(fldlen(52,21)) *s(52,21)='J';
	if(fldlen(52,24)) *s(52,24)='N';
	while(99>*u(52,1)) if(fasadd(52)) break;    
	if(fldlen(6,103)){while(1100>*u(52,1)) if(fasadd(52)) break;  } // 1000 subgroepen aanmaken
	fasinit(52);
	updfield=NO;
  FOREVER{
    scrget(2,72);fasunlck(0);
    scrifld(1,fm_os20,"Artikelgroepen");
    scrfld(2,25,1);
    scrifld(3,fm_menu,&choice);
    key=scrupd(3,0x0401);
    if(key==101) break;
    if(key==111) ovlexit(-1);
		fasunlck(-1);
    switch(choice){
      case'1': upgrtab(); break;
      case'4': printgr(); break;
      default: errnum=34; break;
    }
  }
  endsr:;
}
 
static upgrtab()
{
  int16 key,recnr;
 
  FOREVER{
    recnr=0;
    redo:
    scrget(2,70);
    scrifld(1,fm_os38,"Artikelgroepen");
    scrfld(2,25,1);
    scrifld(3,fm_uu2,&recnr);scraddpicto(1,3,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    key=scrupd(2,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){// uitgebreid groep zoeken
			if(recnr){*u(52,1)=recnr; fasgetu(52);}
			else{
			  if(Search(52,98)) goto redo;
			  recnr=*u(52,1);
			}
 		} 
    if(key==101) goto endsr;
    if(key==111) ovlexit(210);
    if(recnr==0) {errnum=38; goto redo;}
    if(recnr>99) {errnum=39; goto redo;}
    *u(52,1)=recnr; fasgetu(52);
    if(!fichupgr()) goto endsr;
  }
  endsr:;
}
 
static printgr()
{
  int16 form_dat[8],pr_mode,cnt,prtnr,fuval,k,z,g;
  uint16 getnr;
 
  getsysprNew(5,form_dat,&pr_mode,&prtnr);
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  free=999;

  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,28); prttext("<t30eb>"); prttext("Artikelgroepen"); prttext("<eb>");
  prttext("<t80>"); prtfld(25,2,-1); prttext("<t119>");prttext("Blz.<ppp>.");
  prtbuf(1);
  z=1;
  prtitab(z,fm_ou3,u(52,1),3,-1); prttitle(z++,"Groep",3);
  prttab(z,52,14,5,-1); prttitle(z++,"Naam",3);
  prttab(z,52,21,5,-1); prttitle(z++,"Krt",3);
	prttab(z,52,24,5,-1); prttitle(z++,"Divrs",3);
  for(g=0;g<10;g++){
    if(((g<6 && fldlen(52,2+g*2)) || (g>5 && fldlen(52,30+(g-6)*2)))  && fldlen(6,PrNrs[g])){
      if(g<6) prttab(z,52,2+g*2,1,-1); else prttab(z,52,30+(g-6)*2,1,-1);  prttitle(z++,&vptekst[g*10],0x13);
      prtitab(z++,fm_os1,calctype+1+g*2,1,-1);
    }
  }
  prtbuf(3);
	p_pdfname("Artikelgroepen",0,0);
  cnt=0;getnr=0;
  fasinit(52);
  while (free>=0){
next:
		getnr++;
		if(getnr>=100) break; // max 99 groepen
    *u(52,1)=getnr;
    fuval=fasgeti(52);
    if(fuval==46) continue;
    else if(fuval) break;
    if(*s(52,14)=='\0') goto next;
		if(fldlen(52,24) && *s(52,24)=='\0') *s(52,24)='N';
    if(free<3) {prtform(0);free=999;}
    for(k=1;k<=50;k++) prtinfo(k,0); nextline();
		if(fldlen(6,103)){
			for(k=0;k<10;k++){
				*u(52,1)=100+getnr*10+k; 
				if(fasgetu(52)==0){
					if(*s(52,14)){
						prttext("        * ");
						k++;prtifld(fm_ou2,&k,-1); k--;
						prttext("  ");prtfld(52,14,-1); nextline();
					}
				}
  		}
		}
    cnt++;
  }
  nextline();
  prttext("*** Aantal groepen :"); *u(52,1)=cnt; prtfld(52,1,-1); nextline();
  prtclose();
  endsr:;
}

static p_pdfname(naam_,dt_beg_,dt_end_)
char *naam_;
uint16 dt_beg_,dt_end_;
{
  int16 pos_,slen_,len_,dd,mm,yy;
  char buf_[30],string[100];
				
  zero(string,sizeof string);
  for(slen_=0;slen_<50;slen_++){
    if(naam_[slen_]=='\0') break;
    string[slen_]=naam_[slen_];
  }
  if(dt_beg_){
    string[slen_++]=' ';
    jddate(dt_beg_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[slen_],(long)dd,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)mm,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)yy,2,0);slen_+=2;
  }
  if(dt_end_){
    if(dt_beg_){copy(" - ",&string[slen_],3);slen_+=3;}
    jddate(dt_end_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[slen_],(long)dd,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)mm,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)yy,2,0);slen_+=2;
  }
  for(dd=0;dd<slen_;dd++) if(string[dd]=='\\' || string[dd]=='/') string[dd]='-';
  pos_=0;
  FOREVER{
    if(slen_<=0) break;
    zero(buf_,sizeof buf_);
    copy("\xD0\xCF",buf_,2);
    if(slen_>25) len_=25; else len_=slen_;
		if(string[pos_+len_-1]=='.') string[pos_+len_-1]=' '; // geen punt op einde van naam 
    copy(&string[pos_],&buf_[2],len_);
    buf_[2+len_]=0xD0;
    prttext(buf_);
    slen_-=len_;pos_+=len_;
  }
}


static fichupgr()
{
  float marge[10], *pf,max_vp_;
  int16 g,k,key,z,curs,fld_,z_base_;
  char *ptov,fm_wi_[40];
 
	max_vp_=10; if(fldlen(6,PrNrs[6])==0 || fldlen(52,22)<20 || fldlen(52,30)==0) max_vp_=6; 
  errnum=0;
  fieldspc(52,3,&pf,fm_wi_);
  fm_wi_[1]=fm_wi_[1]&0xBF;
  g=0; for(k=0;k<fldlen(52,22);k++) g+=*(calctype+k);
  if(g==0) copy(CALCDEF,calctype,fldlen(52,22));
	for(g=0;g<fldlen(52,22)/2;g++) *(calctype+g*2)='%';
  fasinit(6);
  *f(6,18)=100;*f(6,12)=100;
  for(g=0;g<max_vp_;g++){
		if(fldlen(6,PrNrs[g])==0) continue;
    ptov=calctype+1+g*2;fld_=0;
    if(*ptov=='B') fld_=12;
    else if(*ptov=='N') fld_=18;
    else if(*ptov>='0' && *ptov<='8') fld_=PrNrs[*ptov-'0'];
    if(fld_ && fld_<(PrNrs[g])){
			if(g<6) *f(6,PrNrs[g])=*f(6,fld_)*(1.+*f(52,2+g*2)/100.);
			else *f(6,PrNrs[g])=*f(6,fld_)*(1.+*f(52,30+(g-6)*2)/100.);
		}
    else *f(6,PrNrs[g])=0;
    if(*f(6,PrNrs[g])) marge[g]=(*f(6,PrNrs[g])-100.)/ *f(6,PrNrs[g]);
    else marge[g]=0;
  }
  calcnet();
  curs=3;
  FOREVER{
redo:;
		k=68;
#if FLAGGOU | FLAGCOC | FLAGLEA
		k=568;
#endif
    scrnum=0;scrget(2,k);
		z=1;
    scrfld(z++,25,1);
    scrofld(z++,52,1,-1);
    scrfld(z++,52,14);
    if(fldlen(52,21)) scrfld(z++,52,21);
    else scrifld(z++,fm_os5,"-");
#if !FLAGCOC
    scrfld(z++,52,24); // NIET op prijslijst/bestellijst 
#endif
#if FLAGGOU
    scrfld(z++,52,28); // afronding prijs 
#endif
    if(sys3586==1) scrifld(z++,fm_os10,"Nett.marge");
    else scrifld(z++,fm_os10,"Nett.winst");
    z_base_=z;
#if FLAGGOU | FLAGCOC | FLAGLEA
    for(g=0;g<6;g++){
#else 
    for(g=0;g<max_vp_;g++){
#endif
      ptov=calctype+1+g*2;
      if(((g<6 && fldlen(52,2+g*2)) || (g>5 && fldlen(52,30+(g-6)*2)))  && fldlen(6,PrNrs[g])){
				scrifld(z++,fm_os6,&vptekst[g*10]);
				if(g<6) scrfld(z++,52,2+g*2); else  scrfld(z++,52,30+(g-6)*2);
				scrifld(z++,fm_u09NB,ptov);
				if(sys3586!=1) scrifld(z++,fm_wi_,&net_winst[g]);
				else scrifld(z++,fm_wi_,&marge[g]);
      }
      else{
				z++; scrifld(z++,fm_os6,"     -");
				scrifld(z++,fm_os1,"-");
				scrifld(z++,fm_os6,"     -");
      }
    }
#if FLAGCOC
		if(fldlen(52,25)) scrfld(z++,52,25);/* kaart_pct */
#else
		if(fldlen(52,23)) scrfld(z++,52,23);
#endif
//		if(fldlen(6,103)) AddTextKey(z++,60,22,20,2,10001,"Subgroepen",0x0000FF);
		if(fldlen(6,103)){
			scraddfield(z,60,23,8);scrifld(z++,VarTextFmt(15,0)," F9 subgroepen ");
		}
    key=scrupd(curs,0x1E1);
		if((key/0x10000)>0) key/=0x10000;
		else if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==109 && fldlen(6,103) && *s(52,14)) {UpdateSubgroepen();}
    if(key==106) break;
		fasinit(6);
		*f(6,18)=100;*f(6,12)=100;
		for(g=0;g<max_vp_;g++){
			if(fldlen(6,PrNrs[g])==0) continue;
			ptov=calctype+1+g*2;fld_=0;
			if(*ptov=='B') fld_=12;
			else if(*ptov=='N') fld_=18;
			else if(*ptov>='0' && *ptov<='8' && *ptov<(g+'0')) fld_=PrNrs[*ptov-'0'];
      else{errnum=52;curs=z_base_+2+g*4;goto redo;}
			if(fld_ && fld_<(PrNrs[g])){
				if(g<6) *f(6,PrNrs[g])=*f(6,fld_)*(1.+*f(52,2+g*2)/100.);
				else *f(6,PrNrs[g])=*f(6,fld_)*(1.+*f(52,30+(g-6)*2)/100.);
			}
			else *f(6,PrNrs[g])=0;
			if(*f(6,PrNrs[g])) marge[g]=(*f(6,PrNrs[g])-100.)/ *f(6,PrNrs[g]);
			else marge[g]=0;
		}
    calcnet();
    if(key==101 || key==108){
      fasupd(52);fasflush(0);
      if(key==101) return NO;
      if(key==108) break;
    }
  }
  return YES;
}

static UpdateSubgroepen()
{
  int16 mastgroep,j,k,key,z,curs;
  char nm_subgroep[10][50],nm_groep[50],buf750[750];
 
	fmt_get(52,14);copy(s(52,1),buf750,fldlen(52,0));
	mastgroep=*u(52,1);copy(s(52,14),nm_groep,fldlen(52,14));
	for(k=0;k<10;k++){
		*u(52,1)=100+mastgroep*10+k; 
		if(fasgetu(52)==0) copy(s(52,14),nm_subgroep[k],fldlen(52,14));
	}
	  curs=3;
  FOREVER{
redo:;
    scrnum=0;scrget(2,373);
		z=1;
    scrifld(z++,fm_ou2,&mastgroep);
    scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_groep);
		for(k=0;k<10;k++){
			j=k+1; scrifld(z++,fm_ou3,&j);
			scrifld(z++,fmt,nm_subgroep[k]);
		}
    key=scrupd(curs,0x00E1);
		if((key/0x10000)>0) key/=0x10000;
		else if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106) break;
		if(key==108){
			for(k=0;k<10;k++){
		    *u(52,1)=100+mastgroep*10+k; 
		    if(fasgetu(52)==0){
					copy(nm_subgroep[k],s(52,14),fldlen(52,14));
					fasupd(52);
				}
	    }
			break;
		}
  }
	fasinit(52);
	copy(buf750,s(52,1),fldlen(52,0));
}

static fmt_get(stu_, elet_)
int16 stu_, elet_;
{
  int16 k;
  char *pdum,dummy_[10];
				
  pdum=&dummy_[0];
  k=fieldspc(stu_,elet_,&pdum,fmt);
  if(k>0) return k;
  return 0;
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

static initload()
{
 
  fasunlck(0);
  fileopen(6);

  sysget( 294,4,def_munt);
  sysget(1048,32,&btw_pct[0]);
  sysget(3586,2,&sys3586);
  sysget(3652,2,&sys3652);
  sysget(1084,4,&def_btw);
  sysget(3894,2,&sys3894);
  sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  sysget(4670,6,stuksprx);
	sysget(4780,4,&stuksprx[6]);
 
  calctype=s(52,22);
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

static calcnet()
{
  int16 k,t_ap_;
  float accijns_,net_,q_stuks,bd_,bd_deler_;
									
  t_ap_=18; if(sys3586==2) t_ap_=12;
  if(*f(6,18)) goto calc_wpct;
  net_=*f(6,12);
  if(fldlen(6,13)) net_=valu_cnv(s(6,13),def_munt,(double)net_,(double)0.01);
  accijns_=*f(6,30);
  net_-=accijns_;
  if(fldlen(6,17)){
    bd_=*f(6,17);
    if(fldlen(6,13)) bd_=valu_cnv(s(6,13),def_munt,(double)bd_,(double)0.01);
    net_-=bd_;
  }
  for(k=0;k<3;k++) if(fldlen(6,14+k)) net_*=(100.-*f(6,14+k))/100.;
	net_+=accijns_; 
	if(sys3652){ // afhaal en losvergoeding erbij tellen 
		if(fldlen(6,19)) {
			if(sys3652==2) net_*=(100.+*f(6,19))/100.;  // als %
			else net_+=*f(6,19);
		}
		if(fldlen(6,20)) net_+=*f(6,20);
	}
  *f(6,18)=net_;
  calc_wpct:;
  for(k=0;k<10;k++){
		if(fldlen(6,PrNrs[k])==0) continue;
    bd_deler_=*f(6,18);
    if(sys3586==2) bd_deler_=*f(6,12);
    else if(sys3586==1) bd_deler_=*f(6,PrNrs[k]);

    if(fldlen(6,PrNrs[k]) && *f(6,t_ap_) && bd_deler_){
      q_stuks=0;
      if(stuksprx[k]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
      if(q_stuks==0) q_stuks=1;
      net_=*f(6,PrNrs[k]);
      if(rev_prx_calc){
	net_=*f(6,t_ap_)* (1.+net_winst[k]/100);
	if(sys3586==1){/* marge */
	  net_+=((net_-*f(6,t_ap_))*  net_/ *f(6,t_ap_)) * net_winst[k]/100;
	}
	if(sys3894 & 1<<k) net_*=1.+*f(6,28)/100.;
	net_/=q_stuks;
	*f(6,PrNrs[k])=valu_cnv("EUR","EUR",(double)(net_),(double)(sys3614));
      }
      else{
	if(sys3894 & 1<<k) net_/=1.+*f(6,28)/100.;
	if(sys3586==1) bd_deler_=net_*q_stuks;/* correctie VP-prijs/stuk */
	net_winst[k]=((net_-(*f(6,t_ap_)/q_stuks))/ (bd_deler_/q_stuks)) * 100.;
      }
    }
    else net_winst[k]=0;
  }
}

static nextline()
{
  free=prtline();
}
 
 
