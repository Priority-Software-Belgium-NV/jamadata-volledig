/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0064GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0064dat
#define ovlcod BKH0064cod
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

char ovldat[] = "bkh0064  00:28 16/09/10 (c) Jamadata";
/* afdrukken klt/lev/grb balansen */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

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
 
extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

extern char *s();
extern int16 *i();
extern uint16 *u();
extern uint16 datejd();
extern long *l();
static long val(),val1();
static long val4_1();
extern float *f();
extern double *d(),valu_cnv();
static double round();
static double Round(bd_,q_decim_);
	  
static char *pfil_pref[3] = {"LEV","KLT","GRB"};

static char fm_obd[]   = {6,0x95,9,2,0x70,0};/* od9_2 */
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};

static int16 level,period_1,mnd_strt,skipniv=0,maxfld,out_naam;
static int16 form_dat[8],pr_mode,free,lst_typ,prtnr,seqo_len=0;
static uint16 rek_nr,dt_beg,dt_end,rec_anal=0,sys4524,recordcnt,last_arc,date_1_1;
static char sys4521,str4498[23],filres[20],oldnm[51],sys1787,out_tot_rek;
static long grb_anal,hoev,sub_mask;
static double bdn_cre,bdn_deb,bdv_cre[11],bdv_deb[11],bdp_cre[11],bdp_deb[11];
static double bds_cre[11],bds_deb[11],bdt_deb,bdt_cre,bdn_sal,bdv_sal;
static double saldo_in;/* grb : saldo geboekt op deze rekening ZELF, dus zonder */
/* bedragen die er supplem.in getotaliseerd werden van detailrekeningen */
static long grb_nr;
static char naam[21],anal_naam[30],filnam[3][15],fmt[40],dcn_code,dcv_code;
static flag debit_allow=NO,credt_allow=NO,lvcd,klcd,code,analyt,fil_out=NO;
static flag list_ok,opened,full_lst,sys2694,sys1822;
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;
extern int16 ilength; // XLS
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi,prt2xls; // XLS
static int16 StylTotaal, StylGrpTot, StylKlasse, StylNormal, StylTitel, Styl2Use;


#include "Std\XlsFunc.c"

ovlcod()
{
  sel_lst=(struct _sel_lst*)u(26,1);
  if(sel_lst->l_bl==0 && sel_lst->k_bl==0 && sel_lst->g_bl==0) goto endsr;
  if(sel_lst->filbal) fil_out=YES;

  initload();fasunlck(-1);

  if(fil_out) ask_fil_parm();
  if(sel_lst->l_bl && credt_allow) {lst_typ=0;pr_1lst("Leveranciers");}
  if(sel_lst->k_bl && debit_allow) {lst_typ=1;pr_1lst("Klanten");}
  if(sel_lst->g_bl){
    lst_typ=2;pr_1lst("Grootboek");
//    fil_out=NO;/* tijdelijk voor Somers */
    if(analyt && sys1822!=1) prt_anal();
  }
  if(fil_out==NO) free=prtclose(); // seq_clos();
  if(free==-1) ovlexit(10);
  endsr:
  if(sel_lst->rapport) closerapport();
  ovlexit(10);
}

static pr_1lst(phdr)
char *phdr;
{
  int16 k,ks,stop,stu,mode4_;
  flag first=YES;

  list_ok=NO;
  if(free==-1) goto endsr;
  scrget(1,6);scrupd(-3,0);
  for(k=0;k<11;k++){
    bdv_deb[k]=0;bdv_cre[k]=0;
    bdp_deb[k]=0;bdp_cre[k]=0;
    bds_deb[k]=0;bds_cre[k]=0;
  }
  bdt_deb=0;bdt_cre=0;
  stu=lst_typ+1;
  pr_init(phdr);
  fasinit(stu);
  FOREVER{
    if(lst_typ<2)ks=faskeyi(stu,2,2);
    else{
      ks=faskeyi(3,1,2);
    }
    if(ks)break;
    if(lst_typ==2 && analyt && g_anal_tst()) break;
    first=YES;
    init_rek();
    fasinit(4); mode4_=1;
    if(lst_typ<2){
      *u(4,5)=*u(stu,1)+lst_typ*30000;
    }
    else{
      if(rec_anal==0) *l(4,6)=*l(3,2);
      else{
	*l(4,6)=grb_anal;
	*l(4,11)=*l(3,2);
      }
    }
    FOREVER{
      stop=NO;
      if(lst_typ<2){
	ks=faskeyi(4,4,mode4_); mode4_=2;
	if(*u(4,5)!=*u(stu,1)+lst_typ*30000) stop=YES;
      }
      else{
	ks=faskeyi(4,3,mode4_); mode4_=2;
	if(rec_anal==0) {if(*l(4,6)!=*l(3,2)) stop=YES;}
	else{if(*l(4,6)!=grb_anal || *l(4,11)!=*l(3,2)) stop=YES;}
      }
      if(ks)stop=YES;
      if(stop){
	pr_rek();
	break;
      }
      if((*u(4,4)<=dt_end) && (lst_typ<2 || *u(4,4)>=dt_beg)){
	if(fldlen(4,19)==0 || (sub_mask & *l(4,19))){
	  add_bew();
	  first=NO;
	}
      }
      if(free==-1) break;
    }
    if(free==-1) break;
  }
  if(list_ok) pr_end_lst();
  if(fil_out) XlsClose(XlsRef,1);// seq_clos();
	else free=prtclose();
  endsr:;
}

static pr_init(phdr)
char *phdr;
{
  int16 z;
	char nm_list_[50];

  code=YES;
  if((lst_typ==0 && lvcd==NO) || (lst_typ==1 && klcd==NO)) code=NO;
  if(fil_out==NO){
		getsysprNew(3,form_dat,&pr_mode,&prtnr);if(sel_lst->prt2pdf) PrintPaperNr=0;
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) ovlexit(10);
    free=999;
    prtnew();
    prtfld(25,1,-1);
    prttext("<t48eb>"); prttext(phdr);prttext("balans<eb>");
    prttext("<t92>"); prtfld(26,2,-1);
    prttext(" - "); prtfld(26,3,-1);
    if(full_lst==NO) prttext("<t118>* ");
    prttext("<t120>Blz.<ppp>.");
    prtbuf(1);
    z=1;
    if(lst_typ==2){
      prtblank(10);
      prttab(z,3,2,0,-1);
    }
    else{
      prttab(z,lst_typ+1,code+1,2,-1);
    }
    prttitle(z++,"Nr.",3);
    prttab(z,lst_typ+1,3,0,25); prttitle(z++,"Omschrijving",3);
    prtitab(z,fm_obd,&bdn_sal,1,-1); prttitle(z++,"Nieuw saldo",0x13);
    prtitab(z,fm_os1,&dcn_code,1,-1); prttitle(z++,"",3);
    if(rec_anal==0){
      prtitab(z,fm_obd,&bdv_sal,1,-1); prttitle(z++,"Vorig saldo",0x13);
      prtitab(z,fm_os1,&dcv_code,1,-1); prttitle(z++,"",3);
    }
    else z+=2;
    prtitab(z,fm_obd,&bdp_deb[10],0,-1); prttitle(z++,"D-Periode",0x13);
    prtitab(z,fm_obd,&bdp_cre[10],1,-1); prttitle(z++,"C-Periode",0x13);
    if(rec_anal==0){
      prtitab(z,fm_obd,&bds_deb[10],0,-1); prttitle(z++,"D-Jaar",0x13);
      prtitab(z,fm_obd,&bds_cre[10],1,-1); prttitle(z++,"C-Jaar",0x13);
    }
    else z+=2;
    prtbuf(3);
    if(rec_anal){
      prtifld(fm_ogrb,&grb_anal,-1);prtblank(1);
      prtifld(fm_os20,anal_naam,-1);
      prtbuf(4);
    }
    
    p_pdfname(phdr,0,0);
    p_pdfname("balans",dt_beg,dt_end);
 
  }
  else{
		scrget(1,7);scrupd(-3,0);XlsRef=-1; zero(nm_list_,sizeof nm_list_);
		if(lst_typ==0) copy0("Leveranciersbalans",nm_list_,30);
		else if(lst_typ==1) copy0("Klantenbalans",nm_list_,30);
		else if(lst_typ==2) {
			z=copy0(phdr,nm_list_,20);z+=copy0("balans ",&nm_list_[z],7);
		  if(rec_anal) grb_deco(&nm_list_[z],&grb_anal);
		}
		XlsRef=OpenXlsFile(nm_list_,*u(26,2),*u(26,3));
    if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsSelectWorkSheet(XlsRef,1,nm_list_);
		XlsColumnSize(XlsRef,2,50);
//XlsStyle(ref, char *NumFormat,Size, long /*COLORREF*/ Color, BoldFlag, ItalicFlag, UnderlineFlag,HorAlignment, VerAlignment,
//	long /*COLORREF*/ BackCol, int16 Pattern, Kader, KaderCol, Lock, Hide)
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
		StylGrpTot=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_BEIGE,1,1,0,NO,NO);
		StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);

		XlsRij=1;XlsKol=1;Styl2Use=StylTitel;
	  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Nr",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Nieuw saldo",Styl2Use);
//    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"D/C",StylNormal);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Vorig saldo",Styl2Use);
//    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"D/C",StylNormal);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"D-periode",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"C-periode",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"D-jaar",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"C-jaar",Styl2Use);
		XlsRij++;
//    seq_open(filnam[lst_typ]);
  }
  endsr:;
}

static OpenXlsFile(text_,bdatum_,edatum_)
char *text_;
unsigned bdatum_,edatum_;
{
	int16 pos_,dd,mm,yy;
  char string[100];
				
  zero(string,sizeof string);
	pos_=copy0(text_,&string[0],30);
  if(bdatum_){
    string[pos_++]=' ';
    jddate(bdatum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
  if(edatum_){
    if(edatum_){copy(" - ",&string[pos_],3);pos_+=3;}
    jddate(edatum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
	pos_+=copy0(".XLS",&string[pos_],4);
	
  pos_=XlsCreate(string);
	return pos_;
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}

static double Round(bd_,q_decim_)
double bd_;
int q_decim_;
{
	int k;
  double wrk1_,wrk2_,wrk3_,add_,result_,bd_afr_;
 
	bd_afr_=1.; 
	for(k=0;k<q_decim_;k++) bd_afr_/=10.;
  result_=bd_;
  add_=0.500001;
  if(result_<0) add_=-add_;
  if(bd_afr_>0.00001){
    if(bd_afr_<=1.){
      wrk1_=(long int)result_;
      wrk2_=result_-wrk1_;
    } else{wrk1_=0.;wrk2_=result_;}
    wrk3_=wrk2_/bd_afr_;
    wrk2_=(double)((long)((wrk2_/bd_afr_)+add_)) * bd_afr_;
    result_=wrk1_+wrk2_;
  }
  endsr:;
  return (double)(result_);
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

static init_rek()
{
  int16 k,ks;
  uint16 dt_;
 
  bdv_deb[10]=0;bdv_cre[10]=0;
  bdp_deb[10]=0;bdp_cre[10]=0;
  bds_deb[10]=0;bds_cre[10]=0;
  saldo_in=0;
  hoev=0;
  if(lst_typ<2)level=10;
  else{
    if(*s(3,5)=='J')level=10;
    else level=*s(3,10)-'0';
    if(level<1 || level>9) level=10;
  }
  fasinit(5);
  *u(5,2)=*u(lst_typ+1,1)+lst_typ*30000;
  ks=faskeyi(5,1,0);
  if(ks==0){
    if(period_1 || (lst_typ==2 && grb_anal)) fasinit(5);
    for(k=0;k<=level;k++){
      bds_deb[k]+=*d(5,31);bds_cre[k]-=*d(5,32);
    }
    saldo_in+=*d(5,31)+*d(5,32);
  }
  if(full_lst==NO && lst_typ==2){
    dt_=last_arc+1;
    if(last_arc && (last_arc+1)<date_1_1) dt_=date_1_1;
    add_saldo(dt_,*u(26,2));
  }
}

static add_saldo(dt_b_,dt_e_)
uint16 dt_b_,dt_e_;
{
  int16 mode_,k;
  double bedrag_;

  fasinit(4); mode_=1;
  if(lst_typ<2){
    *u(4,5)=*u(lst_typ+1,1)+lst_typ*30000;
  }
  else{
    if(rec_anal==0) *l(4,6)=*l(3,2);
    else{
      *l(4,6)=grb_anal;
      *l(4,11)=*l(3,2);
    }
  }
  FOREVER{
    if(lst_typ<2){
      if(faskeyi(4,4,mode_)) break; mode_=2;
      if(*u(4,5)!=*u(lst_typ+1,1)+lst_typ*30000) break;
      dt_b_=0;
    }
    else{
      if(faskeyi(4,3,mode_)) break; mode_=2;
      if(rec_anal==0) {if(*l(4,6)!=*l(3,2)) break;}
      else{if(*l(4,6)!=grb_anal || *l(4,11)!=*l(3,2)) break;}
    }
    if(*u(4,4)>=dt_b_ && *u(4,4)<dt_e_){
      bedrag_=*d(4,32);
      for(k=0;k<=level;k++){
	if(bedrag_>=0) bdv_deb[k]+=bedrag_; else bdv_cre[k]-=bedrag_;
	if(*u(4,4)>=date_1_1){/* dit boekjaar : jaartotalen updaten */
	  if(bedrag_>=0) bds_deb[k]+=bedrag_; else bds_cre[k]-=bedrag_;
	}
      }
      saldo_in+=bedrag_;
    }
  }
  endsr:;
}

static add_bew()
{
  int16 k;
  double bedrag;

  bedrag=round(*d(4,32));
  for(k=0;k<=level;k++){
    if(lst_typ<2){
      if(*u(4,4)<dt_beg){
	if(bedrag>=0) bdv_deb[k]+=bedrag;
	else bdv_cre[k]-=bedrag;
	if(*u(4,4)>last_arc && *u(4,4)>=date_1_1){/* jaargegevens updaten */
	  if(bedrag>=0) bds_deb[k]+=bedrag;
	  else bds_cre[k]-=bedrag;
	}
      }
      else{
	if(bedrag>=0) bdp_deb[k]+=bedrag;
	else bdp_cre[k]-=bedrag;
      }
    }
    else{
      if(bedrag>=0) bdp_deb[k]+=bedrag;
      else bdp_cre[k]-=bedrag;
    }
  }
  if(lst_typ==2) saldo_in+=bedrag;
  if(bit(sys1787,5)){
    if(lst_typ==2 || *u(4,4)>=dt_beg){
      hoev+=val1(s(4,28));
    }
  }
}
 
static initload()
{
  int16 k,dd_,yy_,mm_;

  fasunlck(0);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  if(credt_allow) fileopen(1);
  if(debit_allow) fileopen(2);
  for(k=3;k<=5;k++) fileopen(k);

  getsysprNew(3,form_dat,&pr_mode,&prtnr);

  sysget(1787,1,&sys1787);

  sel_lst=(struct _sel_lst*)u(26,1);
  dt_beg=*u(26,2);
  dt_end=*u(26,3);
  sysget(1822,2,&sys1822);
  sysget(1858,2,&last_arc);
  sysget(1866,2,&mnd_strt);
  sysget(2694,2,&sys2694);
  full_lst=YES; if(last_arc!=0 && *u(26,2)!= last_arc+1) full_lst=NO;
  jddate(dt_beg,&yy_,&mm_,&dd_); yy_%=100;
  yy_%=100; if(mnd_strt>mm_) yy_--; if(yy_<0) yy_=99;/* jaar 2000 */
  date_1_1=datejd(yy_,mnd_strt,1);
  period_1=0;   jddate(last_arc+1,&yy_,&mm_,&dd_);
  if(mm_==mnd_strt || (last_arc+1)<date_1_1) period_1=1;
  analyt=fldlen(4,11);
  sub_mask=*l(26,14);
  pu_4_1=u(4,1); pl_4_1=l(4,1); len4_1=fldlen(4,1);
}

static closerapport()
{
  getsysprNew(3,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) ovlexit(10);
  prttext("\xD0\xCC\xD0");
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
}

static pr_rek()
{
  int16 blank,k,used_;
  double bd_;
 
  used_=0;XlsKol=1;
  bd_=bdv_deb[level]-bdv_cre[level];/* enkel indien saldo */
  if(!is_nul(bd_)) used_++;
  if(!is_nul(bdp_deb[level])) used_++;
  if(!is_nul(bdp_cre[level])) used_++;
  if(!is_nul(bds_deb[level])) used_++;
  if(!is_nul(bds_cre[level])) used_++;
  if(used_){
		if(level==1) Styl2Use=StylKlasse;//StylTotSum;
		else if(level<10) Styl2Use=StylGrpTot;
		else Styl2Use=StylNormal;
    if(fil_out && level<10 && out_tot_rek!='J') goto no_seqo;
    if(lst_typ==2 && *s(3,11)=='N') skiplin(3);
    if(lst_typ<2 || *s(3,5)=='J' || *s(3,11)!='N'){
      free_tst(3);
      if(fil_out==NO){
				if(lst_typ==2){
					if(*s(3,10)=='1'){
						streeppr();
						prttext("<b> Klasse : <b>");prtinfo(1,2);
					}
					else{
						skiplin(0);
						blank=level*2-4;
						if(blank>=10) blank=9;
						if(blank<0) blank=0;
						prtblank(blank); prtinfo(1,0); prtblank(10-blank);
					}
				}
				else prtinfo(1,0);
				prtinfo(2,0);
      }
      else{
				WriteFld2Xls(XlsRij,XlsKol++,lst_typ+1,code+1,Styl2Use);
				WriteFld2Xls(XlsRij,XlsKol++,lst_typ+1,3,Styl2Use);
	//			seqo_x(lst_typ+1,code+1);
	//			if(out_naam=='J') seqo_x(lst_typ+1,3);
      }
      pr_bedr(0,1);
      if(lst_typ==2 && fil_out==NO){
				if(*s(3,10)=='1') streeppr();
      }
    }
    no_seqo:;
    list_ok=YES;
    if(lst_typ==2){
      if(saldo_in<0) bdt_cre-=saldo_in; else bdt_deb+=saldo_in;
    }
    for(k=level;k<=10;k++){
      bdv_deb[k]=0;bdv_cre[k]=0;
      bdp_deb[k]=0;bdp_cre[k]=0;
      bds_deb[k]=0;bds_cre[k]=0;
    }
  }
  endsr:;
}

static pr_end_lst()
{
  free_tst(2);
  if(fil_out==NO) nextline();
  else if(out_tot_rek!='J') goto endsr;
  if(lst_typ==2){
    bdn_deb=bdt_deb;
    bdn_cre=bdt_cre;
    dcn_code='\0';
    if(bdn_deb>bdn_cre){/* enkel saldo indien balans niet in evenwicht */
      bdn_sal=bdn_deb-bdn_cre;
      if(!is_nul(bdn_sal)) dcn_code='D';
    }
    else{
      bdn_sal=bdn_cre-bdn_deb;
      bdn_sal=-bdn_sal;if(!is_nul(bdn_sal)) dcn_code='C';
    }
    if(fil_out==NO) prtblank(10);
  }
  if(fil_out==NO) prttitle(1,"   Algemeen totaal",2);
  else {
		fasinit(lst_typ+1); copy("Algemeen totaal",s(lst_typ+1,3),15);
		Styl2Use=StylTotaal;
    XlsKol++;//		WriteFld2Xls(XlsRij,XlsKol++,lst_typ+1,code+1,Styl2Use);
		WriteFld2Xls(XlsRij,XlsKol++,lst_typ+1,3,Styl2Use);
//		seqo_x(lst_typ+1,code+1);
//		if(out_naam=='J') seqo_x(lst_typ+1,3);
	}
  level=0;
  if(lst_typ==2) pr_bedr(2,0); else pr_bedr(2,1);
  if(fil_out==NO){
		if(rec_anal){
			prtblank(8);prtifld(fm_ogrb,&grb_anal,-1);prtblank(1);
			prtifld(fm_os20,anal_naam,-1);
			nextline();
		}
		prtform(0);
	}
	free=999;
  endsr:;
}

static pr_bedr(mode,calc)
int16 mode,calc;
{
  char str_[20];
 
  if(lst_typ==2){
    bdv_deb[level]=bds_deb[level];
    bdv_cre[level]=bds_cre[level];
  }
  if(calc){
    bdn_deb=bdv_deb[level]+bdp_deb[level];
    bdn_cre=bdv_cre[level]+bdp_cre[level];
    if(fil_out==NO){
      dcn_code='\0';
      if(bdn_deb>bdn_cre){
				bdn_deb=bdn_deb-bdn_cre;
				bdn_cre=0;
				bdn_sal=bdn_deb;if(!is_nul(bdn_sal)) dcn_code='D';
				prtinfo(3,mode);prtinfo(4,mode);
      }
      else{
				bdn_cre=bdn_cre-bdn_deb;
				bdn_deb=0;
				bdn_sal=-bdn_cre;if(!is_nul(bdn_sal)) dcn_code='C';
				prtinfo(3,mode);prtinfo(4,mode);
      }
    }
    else{
      *d(26,18)=bdn_deb-bdn_cre;// seqo_x(26,18);
			WriteFld2Xls(XlsRij,XlsKol++,26,18,Styl2Use);
    }
  }
  else{
    if(fil_out==NO){
      prtinfo(3,mode); prtinfo(4,mode);
    }
    else{
      *d(26,18)=bdn_deb-bdn_cre;// seqo_x(26,18);
			WriteFld2Xls(XlsRij,XlsKol++,26,18,Styl2Use);
    }
  }
  if(fil_out==NO){
    dcv_code='\0';
    if(bdv_deb[level]>bdv_cre[level]){
      bdv_deb[10]=bdv_deb[level]-bdv_cre[level];
      bdv_sal=bdv_deb[10];if(!is_nul(bdv_sal)) dcv_code='D';
      prtinfo(5,mode);prtinfo(6,mode);
    }
    else{
      bdv_cre[10]=bdv_cre[level]-bdv_deb[level];
      bdv_sal=-bdv_cre[10];if(!is_nul(bdv_sal)) dcv_code='C';
      prtinfo(5,mode);prtinfo(6,mode);
    }
  }
  else{
    *d(26,18)=bdv_deb[level]-bdv_cre[level];// seqo_x(26,18);
		WriteFld2Xls(XlsRij,XlsKol++,26,18,Styl2Use);
  }
  if(level!=10){bdp_deb[10]=bdp_deb[level];bdp_cre[10]=bdp_cre[level];}
  if(fil_out==NO){
    if(bdp_deb[10]>1000000000 ||  bdp_deb[10]<-999999999){
      if(mode) prttext("<b>");
      cnv_bd(str_,bdp_deb[10]);prtifld(fm_os13,&str_[2],-1);
      if(mode) prttext("<b>");
    }
    else prtinfo(7,mode);
    if(bdp_cre[10]>1000000000 ||  bdp_cre[10]<-999999999){
      if(mode) prttext("<b>");
      cnv_bd(str_,bdp_cre[10]);prtifld(fm_os13,&str_[2],-1);
      if(mode) prttext("<b>");
      prttext(" ");
    }
    else prtinfo(8,mode);
  }
  else{
    *d(26,18)=bdp_deb[10];WriteFld2Xls(XlsRij,XlsKol++,26,18,Styl2Use); // seqo_x(26,18);
    *d(26,18)=bdp_cre[10];WriteFld2Xls(XlsRij,XlsKol++,26,18,Styl2Use); // seqo_x(26,18);
  }
  bds_deb[level]+=bdp_deb[level];bds_cre[level]+=bdp_cre[level];
  if(level!=10){bds_deb[10]=bds_deb[level];bds_cre[10]=bds_cre[level];}
  if(fil_out==NO){
    if(bds_deb[10]>1000000000 ||  bds_deb[10]<-999999999){
      if(mode) prttext("<b>");
      cnv_bd(str_,bds_deb[10]);prtifld(fm_os13,&str_[2],-1);
      if(mode) prttext("<b>");
    }
    else prtinfo(9,mode);
    if(bds_cre[10]>1000000000 ||  bds_cre[10]<-999999999){
      if(mode) prttext("<b>");
      cnv_bd(str_,bds_cre[10]);prtifld(fm_os13,&str_[2],-1);
      if(mode) prttext("<b>");
    }
    else prtinfo(10,mode);
    nextline();
  }
  else{
    *d(26,18)=bds_deb[10];WriteFld2Xls(XlsRij,XlsKol++,26,18,Styl2Use); // seqo_x(26,18);
    *d(26,18)=bds_cre[10];WriteFld2Xls(XlsRij,XlsKol++,26,18,Styl2Use); // seqo_x(26,18);
    if(bit(sys1787,5)){
      *l(26,8)=hoev;WriteFld2Xls(XlsRij,XlsKol++,26,8,Styl2Use); //  seqo_x(26,8);
    }
    XlsRij++;XlsKol=1; //seqo_x(0,0);
  }
}

static cnv_bd(ps_,bd_)
char *ps_;
double bd_;
{
  int16 j,k,len_;
  char str_[20];
  double bd1_,bd2_;
  long lbd1_,lbd2_;
								
  zero(ps_,20);
  bd2_=bd_/1000000;
  bd1_=(long)(bd_/1000000);
  bd2_=(long)((bd2_-bd1_)*(double)(1000000.) +(double).49);
  lbd1_=(long)(bd1_+.49); lbd2_=(long)(bd2_+.49);

  len_=7;
  if(lbd1_){
    stcli_d(str_,(long)lbd1_,len_,1);
    j=len_-1;
    for(k=0;k<len_;k++){
      if(k && k%3==0 && str_[len_-k-1]!=' ') *(ps_+j--)='.';
      *(ps_+j--)=str_[len_-k-1];
      if(j<0) break;
    }
    ps_+=len_;*(ps_++)='.';
  }
  len_=7;
  if(lbd1_) stcli_d(str_,(long)lbd2_,len_,0);
  else stcli_d(str_,(long)lbd2_,len_,1);
  j=len_-1;
  for(k=0;k<len_;k++){
    if(k && k%3==0 && str_[len_-k-1]!=' ') *(ps_+j--)='.';
    *(ps_+j--)=str_[len_-k-1];
    if(j<0) break;
  }
}

static free_tst(aantal)
int16 aantal;
{
  if(fil_out) free=999;
	else	if(free<aantal){
    prtform(0);free=999;
  }
}

static streeppr()
{
  int16 k;
  char streep[130];

  for(k=0;k<129;k++) streep[k]='-';
  streep[129]='\0';
  prttext(streep);nextline();
}

static skiplin(mode)
int16 mode;
{
  if(fil_out) goto endsr;
  if(skipniv==0 && *s(3,10)!='0') nextline();
  else if(skipniv==1 && *s(3,10)=='0') nextline();
  skipniv=mode;
  if(*s(3,10)!='0') skipniv++;
  endsr:;
}

static nextline()
{
  free=prtline();
}

static prt_anal()
{
  uint16 rec_,mode_,key;
  char p_anal_='N';
  long inq_anal_=0;
							
  fasinit(3);
  FOREVER{
    redo:;
    scrget(1,244);
    scrifld(1,fm_uJN,&p_anal_);
    scrfld(2,3,2);
    key=scrupd(1,0x81);
    if(key==101 || (key==108 && p_anal_=='N')) goto endsr;
    if(*l(3,2)){
      if(faskeyi(3,1,0)){errnum=39; goto redo;}
      if(*l(3,2) && g_anal_tst()==NO){errnum=68; goto redo;}
    } else fasinit(3);
    inq_anal_=*l(3,2);
    if(key==108) break;
  }

  fasinit(3);mode_=1;
  if(inq_anal_) *l(3,2)=inq_anal_;
  else grb_comp("90000000",l(3,2));
  FOREVER{
    if(faskeyi(3,1,mode_)) break; mode_=2;
    if(inq_anal_ && *l(3,2)!=inq_anal_) break;
    rec_=*u(3,1);
    rec_anal=*u(3,1)+60000;
    grb_anal=*l(3,2);
    copy(s(3,3),anal_naam,20);
    lst_typ=2;pr_1lst("Analytische ");
    if(free==-1) break;
    *u(3,1)=rec_;fasgeti(3);
  }
  endsr:;
  rec_anal=0;
}
 
static g_anal_tst()
{
  if(!analyt || ((*s(3,2) &0xF0)>>4)!=9) return NO;
  return YES;
}
 
static ask_fil_parm()
{
  int16 j,k;
  char buf_[3];

//  sel_lst->l_bl=NO;sel_lst->k_bl=NO;sel_lst->g_bl=NO;
  zero(filnam,sizeof filnam);
  jddate(dt_end,&k,&j,&k);
  stcli_d(buf_,(long)j,2,0);
  for(k=0;k<3;k++){
    copy(pfil_pref[k],filnam[k],3);
    j=3; if(*s(25,3)) {copy(s(25,3),&filnam[k][j],3);j+=3;}
    copy(buf_,&filnam[k][j],2); j+=2;
    copy(".TXT",&filnam[k][j],5);
  }
  sysget(4522,2,&maxfld);
  sysget(4498,23,str4498);
  sysget(4521,1,&sys4521);
  sysget(4524,2,&sys4524);
  out_naam='J'; 
  out_tot_rek='J';

  sysput(4522,2,&maxfld);
  if(maxfld<1) maxfld=1;/* ?????? of iets anders ? */
  if(out_naam=='J') sys4524=sys4524 | 1; else sys4524=sys4524 & 0xFFFE;
  sysput(4524,2,&sys4524);
 
}

static seq_open(pnam)
char *pnam;
{
  scrget(1,170);
  copy(pnam,filres,20);
  fasopen(filres,2);seqo_len=0;fasinit(80);
  if(sys4521 & 4) fasseqo(80,2,11);
  seqo_flush();
  scrget(1,7);scrupd(-3,0);
  getsysprNew(1,form_dat,&pr_mode,&prtnr);
  if((errnum=prtopen(prtnr,form_dat,0,132,pr_mode,4))!=0) ovlexit(10);
  recordcnt=0;opened=YES;
  free=999;
}

static seq_clos()
{
  if(opened==NO) goto endsr;
  seqo_ko(&str4498[18],5);
  seqo_flush();
  fasclos(-2);
  if(sys4521 & 4){
    fasopen(filres,3);
    fasinit(80);
    stcli_d(s(80,1)+4,(long)recordcnt,5,0);
    *(s(80,1)+9)=0x0D;*(s(80,1)+10)=0x0A;
    fasseqo(80,3,11);
    fasclos(-2);
  }
  fasflush(0);
  opened=NO;
  endsr:;
  prtclose();
}

static seqo_x(stu_,elem_)
int16 stu_,elem_;
{
  int16 off_;

  if(stu_){
    WriteFld2Xls(XlsRij,XlsKol,stu_,elem_,0);
    if(seqo_len) seqo_ko(&str4498[8],5);
    fmt_get(stu_,elem_);
    if((fmt[1]&0x3F)>=0x10 && (fmt[1]&0x3F)<=0x15) off_=0;
    else off_=4;
    seqo_ko(&str4498[0+off_],2);
    seqo_fld(stu_,elem_,off_);
    seqo_ko(&str4498[2+off_],2);
  }
  else{
    seqo_ko(&str4498[13],5);
    seqo_flush();
    recordcnt++;
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

static seqo_fld(stu_,fld_,off_)
int16 stu_,fld_,off_;
{
  int16 k;
  char byte_;

  byte_=str4498[2+off_];
  if(off_==4) {
    prtfld(stu_,fld_,-1);
    prtbuf(0);
    copy(GetPtrInfo(),oldnm,50);
  }
  else {
    fmt[4]=fmt[4]&0xAF;
    prtifld(fmt,s(stu_,fld_),-1);
    prtbuf(0);
    copy(GetPtrInfo(),oldnm,50);
    if(sys4521 & 8) for(k=0;k<50;k++) if(oldnm[k]==',') oldnm[k]='.';
  }
  if(sys4521 & 2){/* blank achteraan weg */
    for(k=0;k<50;k++) if(oldnm[k]=='\0') break;
    if(k!=50){
      for(k--;k>=0;k--) if(oldnm[k]!=' ') break; else oldnm[k]='\0';
    }
  }
  k=0;
  if(sys4521 & 1){/* blank vooraan weg */
    while(k<50){
      if(oldnm[k]!=' ') break;
      k++;
    }
  }
  FOREVER{
    if(k==50 || oldnm[k]=='\0') break;
    if(oldnm[k]==byte_) seqo_1(byte_);
    seqo_1(oldnm[k]);
    k++;
  }
}

static seqo_ko(ps,q)
char *ps;
int16 q;
{
  int16 k;

  for(k=0;k<q;k++){
    if(*ps=='\0') break;
    seqo_1(*ps++);
  }
}

static seqo_1(byte_)
char byte_;
{
  *(s(80,1)+4+seqo_len++)=byte_;
}

static seqo_flush()
{
  if(seqo_len){
    fasseqo(80,2,seqo_len+4);
    seqo_len=0;
  }
}
 
static long val1(ps)
char *ps;
{
  long fuval=0;
  flag sign=NO;

  FOREVER{
    if(*ps>='0' && *ps<='9'){
      fuval=fuval*10+*ps-'0';
    }
    else if(*ps=='-') sign=YES;
    else if(*ps!=' ') break;
    ps++;
  }
  if(sign) fuval=-fuval;
  return fuval;
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
 
static double round(value_)
double value_;
{
  double bd_;
							
  bd_=valu_cnv("EUR","EUR",value_,(double)(0.01));
  return (double)(bd_);
}
