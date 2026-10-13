/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0060GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0060dat
#define ovlcod BKH0060cod
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

char ovldat[] = "bkh0060  00:14 16/09/10 (c) Jamadata";
/* afdrukken fouten en controle lijst */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAX             1000
#define MAX_DT          20
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
} j_tab[81];/* 1 extra element */

static struct {
  long grb;
  uint16 rec;
  uint16 journaal;
} grb2chk[50+1];/* 1 extra element */

static struct _sel_lst{
  flag rapport:1;
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
extern uint16 datejd();
extern long *l();
extern long val();
static long val4_1();
extern float *f();
extern double *d();

static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_ogrb[]  = {2,0xA8};

static int16 nr_journ,arr_jr,jr_typ,mnd_strt,form_dat[8],pr_mode,free,prtnr;
static uint16 dt_prev,stuknr,qloaded,dt_tab[MAX_DT],q_ex_period;
static uint16 dt_beg,dt_end,_beg_bkhper,_end_bkhper,jr_beg,jr_end,volg_beg,volg_end;
static uint16 volg_first,volg_last,last_arc,onb_fout;
static uint16 dt_bkh[MAX],rek_nr[MAX],pgrb2chk;
static double bedrag[MAX];
static long grb_notf,err_sgrb;
static flag debit_allow=NO,credt_allow=NO,new_jrl,lvcd,klcd,analyt,opened[10];
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;

ovlcod()
{
  int16 ks,key_mode;
  flag first=YES;

  sel_lst=(struct _sel_lst*)u(26,1);
  if(sel_lst->rapport) openrapport();
  if(sel_lst->fk==0) goto endsr;

  initload();fasunlck(-1);

  scrget(1,6);scrupd(-3,0);
  fasinit(4);
  if(jr_beg || volg_beg){*s(4,2)=jr_beg;*u(4,3)=volg_beg;}
  key_mode=1; onb_fout=NO; err_sgrb=0;
  FOREVER{
    ks=faskeyi(4,1,key_mode);key_mode=2;
    if((*s(4,2)>jr_end) || (*s(4,2)==jr_end && *u(4,3)>volg_end)) ks=YES;
    if(ks)*s(4,2)=255;
    else{
      if(*u(4,4)<_beg_bkhper || *u(4,4)>_end_bkhper) goto next;
      if(*u(4,4)<=last_arc) goto next;
    }
    if(*s(4,2)!=nr_journ || *u(4,3)!=stuknr){
      if(first==NO){
				chk_stuk();
				if(*s(4,2)!=nr_journ) exit_jrn();
      }
      if(ks)break;
      if(*s(4,2)!=nr_journ) init_jrn();
      init_stk(); onb_fout=NO; err_sgrb=0;
    }
    if(ks)break;
    add_bew();
    if(free==-1) break;
    first=NO;
    next:;
  }
  prtform(0);
  free=prtclose();
  if(free==-1) ovlexit(10);
  endsr:
  ovlexit(61);
}

static init_jrn()
{
  int16 k;

  nr_journ=*s(4,2);
  for(k=0;k<80;k++){
    if(nr_journ==j_tab[k].nr) break;
  }
  jr_typ=j_tab[k].typ;
  arr_jr=k;

  prttext("<b>"); prtifld(fm_uu2,&j_tab[arr_jr].nr,-1);
  prtblank(2);prttext(j_tab[arr_jr].nm); prttext("<b>");
  nextline();nextline();

  volg_first=0;volg_last=0;
  new_jrl=YES;
}

static init_stk()
{
  stuknr=*u(4,3);
  qloaded=0;
}

static add_bew()/* voeg 1 boeking toe in tabel */
{
  int16 k;
 
  if(analyt && ((*s(4,6) &0xF0)>>4)==9) goto endsr;
  dt_bkh[qloaded]=*u(4,4);
  rek_nr[qloaded]=*u(4,5);
  bedrag[qloaded]=*d(4,32);
  qloaded++;
  if(qloaded>=MAX) qloaded=MAX-1;
  if(jr_typ==2 && grb_notf==*l(4,6)) onb_fout=YES;

  for(k=0;k<pgrb2chk;k++){
    if(*l(4,6)==grb2chk[k].grb){
      if(k<2){/* klt/lev checken op recordnummer */
	if(grb2chk[k].rec==*u(4,5)) err_sgrb=*l(4,6);
      }
      else {/* bank-rekeningen */
	if(grb2chk[k].journaal!=*s(4,2)) err_sgrb=*l(4,6);
      }
    }
  }
  endsr:;
}

static exit_jrn()
{
  nextline();
  if(volg_first){
    prttext("  Volgnrs. : ");prtifld(fm_uu5,&volg_first,-1);
    prttext("  t/m ");prtifld(fm_uu5,&volg_last,-1);
    nextline();nextline();
  }
  nextline();
}

static initload()
{
  int16 jaar,maand,dum,k;

  fasunlck(0);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  if(credt_allow) fileopen(1);
  if(debit_allow) fileopen(2);
  for(k=3;k<=4;k++) fileopen(k);

  for(k=0;k<80;k++){
    sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
  }
  j_tab[80].nr=0;j_tab[80].typ=3;copy("???",&j_tab[80].nm[0],4);

  sysget(1858,2,&last_arc);
  getsysprNew(3,form_dat,&pr_mode,&prtnr);
	if(sel_lst->prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) ovlexit(10);
  free=999;
  prtnew();
  prtfld(25,1,25);
  prttext("<t27b>Fouten- & controlelijst");prttext("<b>");
  prttext("<t52>"); prtfld(26,2,-1);
  prttext("-"); prtfld(26,3,-1);
  prttext("<t72>Blz.<ppp>.");
  prtbuf(1);
 
  p_pdfname("Foutenlijst",*u(26,2),*u(26,3));

  sysget(1866,2,&mnd_strt);
  dt_beg=*u(26,2);
  dt_end=*u(26,3);
  jr_beg=*u(26,4);volg_beg=*u(26,5);
  jr_end=*u(26,6);volg_end=*u(26,7);
  jddate(dt_beg,&jaar,&maand,&dum);
  if(maand<mnd_strt) jaar--;
  _beg_bkhper=datejd(jaar,mnd_strt,01);
  _end_bkhper=datejd(jaar+1,mnd_strt,01)-1;
  analyt=fldlen(4,11);
  sysget(1800,2,&k); if(k) sysget(3636,4,&grb_notf);

  zero((char *)&grb2chk[0].grb,sizeof grb2chk); pgrb2chk=0;
  for(pgrb2chk=0;pgrb2chk<2;pgrb2chk++){
    sysget(780+pgrb2chk*4,4,&grb2chk[pgrb2chk].grb);
    fasinit(3);*l(3,2)=grb2chk[pgrb2chk].grb;faskeyi(3,1,0);
    grb2chk[pgrb2chk].rec=*u(3,1)+60000;
  }
  for(k=0;k<80;k++){
    if(j_tab[k].typ==3 || j_tab[k].typ==4){/* echte bank en kas */
      fasinit(3);*l(3,2)=j_tab[k].fingrb; if(faskeyi(3,1,0)) continue;
      grb2chk[pgrb2chk].grb=*l(3,2); grb2chk[pgrb2chk].rec=*u(3,1)+60000;
      grb2chk[pgrb2chk].journaal=j_tab[k].nr;
      pgrb2chk++;
    }
    if(pgrb2chk>49) break;
  }
  pu_4_1=u(4,1); pl_4_1=l(4,1); len4_1=fldlen(4,1);
}
 
static prt_string(string)
char *string;
{
  char *_string;
  int16 len;

  len=0; _string=string;
  while (*_string++) len++;
  prt_bin(string,len);
}

static prt_bin(string,len)
char *string;
int16 len;
{
  char fm[8];
 
  fm[0]=7; fm[1]=0x88; fm[2]=len%256; fm[3]=len/256; fm[4]=0; fm[5]=0; fm[6]=0;
  if (len>0) prtifld(fm,string,-2);
}

static openrapport()
{
  uint16 yy, mm, dd;
  int16 slen_;
  char string[100];

  getsysprNew(3,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) ovlexit(10);
	
	prttext("\xD0\xCD\xD0");  prtline();
	zero(string,sizeof string);copy("Boekhouding ",string,12);copy(s(25,1),&string[12],15);
	p_pdfname(string,*u(26,2),*u(26,3));

  prt_string("\x1B&f1S\x1B&f0S\x1B*p+254x*p+410Y\x1B(s1p(s30v0s3B");
  prt_string(s(25,1));
  prt_string("\x1B&f1S\x1B&f0S\x1B*p+254x*p+1010Y\x1B(s1p(s60v0s3B");
  prt_string("\r\nBoekhouding\r\n");
  if (*u(26,2)) {
    slen_=0;
    jddate(*u(26,2),&yy,&mm,&dd);yy%=100;
    stcli_d(&string[slen_],(long)dd,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)mm,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)yy,2,0);slen_+=2;
    prt_string("\x1B&f1S\x1B&f0S\x1B*p+254x*p+1510Y\x1B(s1p(s60v0s3B");
    prt_string("    ");
    prt_string(string);
  }
  if (*u(26,2) && *u(26,3)) {
    prt_string("\x1B&f1S\x1B&f0S\x1B*p+254x*p+1810Y\x1B(s1p(s60v0s3B");
    prt_string("           -");
  }
  if (*u(26,3)) {
    slen_=0;
    jddate(*u(26,3),&yy,&mm,&dd);yy%=100;
    stcli_d(&string[slen_],(long)dd,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)mm,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)yy,2,0);slen_+=2;
    string[slen_++]=0;
    prt_string("\x1B&f1S\x1B&f0S\x1B*p+254x*p+2110Y\x1B(s1p(s60v0s3B");
    prt_string("    ");
    prt_string(string);
  }
  prtline();
  prtform(0);
  prtclose();
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
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  }
  opened[nr_]=YES;
}

static chk_stuk()
{
  int16 k;
  flag ok_periode;
 
  ok_periode=NO;
  for(k=0;k<qloaded;k++){
    if(dt_bkh[k]>=dt_beg && dt_bkh[k]<=dt_end) ok_periode=YES;
  }
  if(ok_periode){
    deb_cr_chk();/* Debet != Credit */
    if(jr_typ==2 && onb_fout){
      prt_STUK(stuknr);
      prttext("Boeking op rekening onbekende samenstelling (");
      prtifld(fm_ogrb,&grb_notf,-1);prttext(")");nextline();
    }

    if(err_sgrb){
      prt_STUK(stuknr);
      prttext("Rechtstreekse boeking op journaal-rekening : ");
      prtifld(fm_ogrb,&err_sgrb,-1);nextline();
    }

    if(jr_typ<3) dubb_fact_chk();/* dubbele facturen */
    dubb_datum_chk();/* verschill.datum in 1 stuk */
 
    if(volg_last){
      if(jr_typ<3 || jr_typ==3 || jr_typ==5 || jr_typ==7){
				if(q_ex_period){
					txt_peri("  Boekingen buiten periode : ",volg_last+1,stuknr-1);
				}
				if(volg_last+q_ex_period+1!=stuknr){
					txt_peri("  Ontbrekende stuknummers : ",volg_last+1,stuknr-1);
				}
      }
      inc_date_chk();/* ophogende datum */
    }
    dt_prev=dt_bkh[0];
    volg_last=stuknr;q_ex_period=0;
    if(new_jrl) volg_first=stuknr;
    new_jrl=NO;
  }
  else q_ex_period++;
}

static txt_peri(ptxt,nr1,nr2)
char *ptxt;
uint16 nr1,nr2;
{
  prttext(ptxt);
  prtifld(fm_uu5,&nr1,-1);
  if(nr1!=nr2){prttext(" t/m ");prtifld(fm_uu5,&nr2,-1);}
  nextline();
}

static prt_dubb(elem)
int16 elem;
{
  int16 stu_;
  uint16 offset;
  double bedr_;

  bedr_=bedrag[elem]; if(rek_nr[elem]<30000) bedr_=-bedr_;
  prttext("<t35>");prtifld(fm_ud8_2,&bedr_,-1);prtblank(1);
  if(rek_nr[elem]<30000) {offset=0;stu_=1;}
  else {offset=30000;stu_=2;}
  if(opened[stu_]) fasinit(stu_);
  copy("???",s(stu_,3),4);
  if(opened[stu_]){*u(stu_,1)=rek_nr[elem]-offset;fasgeti(stu_);}
  prtfld(stu_,3,-1);prtblank(1);
  prtifld(fm_udat,&dt_bkh[elem],-1);
  nextline();
}

static prt_STUK(stuknr_)
uint16 stuknr_;
{
  prttext("  Stuknr. ");prtifld(fm_uu5,&stuknr_,-1);prttext(" : ");
}

static deb_cr_chk()
{
  int16 k;
  double bedr_=0;

  for(k=0;k<qloaded;k++) bedr_+=bedrag[k];
  if(!is_nul(bedr_)){
    prt_STUK(stuknr);
    prttext("<b>debet niet gelijk aan credit. Verschil : ");
    prtifld(fm_ud8_2,&bedr_,-1);
    nextline();
  }
}

static dubb_fact_chk()
{
  int16 j=-1,k;
  flag first=YES;

  for(k=0;k<qloaded;k++){
    if(rek_nr[k]<60000){
      if(j!=-1){
	if(first){
	  prt_STUK(stuknr);
	  prttext("<b>dubbele boeking");
	  prt_dubb(j);
	  first=NO;
	}
	prt_dubb(k);
      }
      j=k;
    }
  }
}

static dubb_datum_chk()
{
  int16 g,k;

  for(k=0;k<MAX_DT;k++) dt_tab[k]=0;
  for(k=0;k<qloaded;k++){
    for(g=0;g<MAX_DT;g++){
      if(dt_tab[g]==0) break;
      if(dt_bkh[k]==dt_tab[g]) break;
    }
    if(dt_tab[g]==0 && g<=(MAX_DT-1)) dt_tab[g]=dt_bkh[k];
  }
  if(dt_tab[1]){
    for(k=0;k<MAX_DT;k++){
      if(k==0){
	prt_STUK(stuknr);
	prttext("dubbele datum :");
      }
      if(dt_tab[k]){
	prttext("<t35>");prtifld(fm_udat,&dt_tab[k],-1);
	nextline();
      }
    }
  }
}

static inc_date_chk()
{
  int16 k;

  for(k=0;k<qloaded;k++){
    if(dt_bkh[k]<dt_prev){
      prt_STUK(stuknr);
      prttext("boekdatum ");
      prtifld(fm_udat,&dt_bkh[k],-1);prttext(" ouder dan boekdatum vorig stuk ");
      prtifld(fm_udat,&dt_prev,-1);
      nextline();
      break;
    }
  }
}
 
 
static nextline()
{
  free=prtline();
}
 
static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}
