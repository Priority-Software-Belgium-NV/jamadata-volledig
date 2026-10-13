/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0062GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0062dat
#define ovlcod BKH0062cod
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

char ovldat[] = "bkh0062  00:14 19/03/10 (c) Jamadata";
/* centralisatiejournalen */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16

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
} j_tab[81];/* 1 extra element */

static struct _sel_lst{
  uint16 dum:1;
  flag prt2pdf:1;
  flag a_btw:1;
  flag filrek:1;
  flag btw:1;
  flag filbal:1;
  flag yr:1;
  flag fk:1;
  flag jr:1;
  flag cj:1;
  flag l_rk:1;
  flag k_rk:1;
  flag g_rk:1;
  flag l_bl:1;
  flag k_bl:1;
  flag g_bl:1;
} *sel_lst;
 

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
static long val4_1();
extern float *f();
extern double *d();

static int16 form_dat[8],pr_mode,free,prtnr;
static char fm_obd[]   = {6,0x95,8,2,0x70,0};                             /* od8_2 */
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};

static int16 nr_journ,arr_jr,jr_typ;
static int16 nm_pdf_ok;
static uint16 dt_beg,dt_end,jr_beg,jr_end,volg_beg,volg_end;
static double bd_cre,bd_deb;
static double bdt_cre,bdt_deb;
static long grb_nr,sub_mask;
static flag analyt;
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;

ovlcod()
{
  int16 first=1,ks;

  sel_lst=(struct _sel_lst*)u(26,1);
  if(sel_lst->cj==0) goto endsr;
  initload();fasunlck(-1);
  pr_init();

  scrget(1,6);scrupd(-3,0);scrupd(1,0);
  fasinit(4);
  if(jr_beg) *s(4,2)=jr_beg;
  FOREVER{
    ks=faskeyi(4,2,2);
    if(*s(4,2)>jr_end) ks=YES;
    if(ks)*s(4,2)=255;
    if(!ks && (*u(4,4)<dt_beg || *u(4,4)>dt_end)) goto next;
    if((*s(4,2)==jr_end && *u(4,3)>volg_end)) goto next;
    if((*s(4,2)==jr_beg && *u(4,3)<volg_beg)) goto next;
    if(!ks && fldlen(4,19) && ((sub_mask & *l(4,19))==0)) goto next;
    if(*s(4,2)!=nr_journ || *l(4,6)!=grb_nr){
      if(first==0){
	pr_grb();
	if(*s(4,2)!=nr_journ) exit_jrn();
      }
      if(ks)break;
      if(*s(4,2)!=nr_journ) init_jrn();
      init_grb();
    }
    if(ks)break;
    add_bew();
    if(free==-1) break;
    first=0;
    next:;
  }
  free=prtclose();
  if(free==-1) {prtclose();ovlexit( 10);}
  endsr:
  ovlexit( 63);
}

static pr_init()
{
	getsysprNew(3,form_dat,&pr_mode,&prtnr);
	if(sel_lst->prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,5))!=0) ovlexit( 10);
  free=999;
  prtnew();
  prtfld(25,1,-1);
  prttext("<t40>"); prtfld(26,2,-1);
  prttext(" - "); prtfld(26,3,-1);
  prttext("<t63>Blz.<ppp>.");
  prtbuf(1);
  prttext("<t5>");prttext("<eb> Centralisatie per journaal <eb>");
  prtbuf(2);
  prttab(1,3,3,3,-1); prttitle(1,"Omschrijving",3);
  prtitab(2,fm_ogrb,&grb_nr,1,-1); prttitle(2,"Rekening",3);
  prtitab(3,fm_obd,&bd_deb,1,-1); prttitle(3,"D-Bedrag",0x13);
  prtitab(4,fm_obd,&bd_cre,4,-1); prttitle(4,"C-Bedrag",0x13);
  prttab(5,3,8,3,-1);  prttitle(5,"BTW-vak",3);
  prtbuf(4);
 
  if(nm_pdf_ok==NO) {p_pdfname("Centralisatie-journalen",dt_beg,dt_end);nm_pdf_ok=YES;}
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





static init_jrn()
{
  int16 k;

  nr_journ=*s(4,2);
  for(k=0;k<80;k++) if(nr_journ==j_tab[k].nr) break;
  jr_typ=j_tab[k].typ;
  arr_jr=k;
  bdt_cre=0;bdt_deb=0;

  free_tst(7);
  prttext("<t15e>"); prtifld(fm_ou2,&j_tab[arr_jr].nr,-1);
  prtblank(2);prttext(j_tab[arr_jr].nm); prttext("<e>");
  nextline();nextline();
}

static init_grb()
{
  bd_deb=0;bd_cre=0;
  grb_nr=*l(4,6);
  fasinit(3);
  copy("???",s(3,3),4);
  *l(3,2)=grb_nr;faskeyi(3,1,0);
}

static add_bew()
{
  double bedrag;

  if(analyt && ((*s(4,6) &0xF0)>>4)==9) goto endsr;
  bedrag=*d(4,32);
  if(bedrag>=0){
    bd_deb+=bedrag;
  }
  else {
    bd_cre-=bedrag;
  }
  endsr:;
}
 
static exit_jrn()
{
  nextline();
  pr_tot("*** Totaal journaal ***");
  nextline();
}

static initload()
{
  int16 k;

  fasunlck(0);
  for(k=3;k<5;k++) fileopen(k);

  for(k=0;k<80;k++){
    sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
  }
  j_tab[80].nr=0;j_tab[80].typ=3;copy("???",&j_tab[80].nm[0],4);

  getsysprNew(3,form_dat,&pr_mode,&prtnr);

  dt_beg=*u(26,2);
  dt_end=*u(26,3);
  jr_beg=*u(26,4);volg_beg=*u(26,5);
  jr_end=*u(26,6);volg_end=*u(26,7);
  analyt=fldlen(4,11);
  sub_mask=*l(26,14);
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
    if(errnum=fasopen(filename,0)) ovlexit(10);
  }
}

static pr_grb()
{
  int16 k;
  if(!is_nul(bd_deb) || !is_nul(bd_cre)){
    free_tst(3);
    for(k=1;k<=20;k++) prtinfo(k,0);
    nextline();
  }
  bdt_deb+=bd_deb;bdt_cre+=bd_cre;
}

static free_tst(aantal)
int16 aantal;
{
  if(free<aantal){
    prtform(0);free=999;
  }
}

static nextline()
{
  free=prtline();
}

static pr_tot(ptxt)
char *ptxt;
{
  int16 k;
  bd_deb=bdt_deb;bd_cre=bdt_cre;
  prttitle(1,ptxt,0);
  for(k=3;k<5;k++)prtinfo(k,2);
  nextline();
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}
