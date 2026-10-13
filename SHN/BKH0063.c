/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0063GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0063dat
#define ovlcod BKH0063cod
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

char ovldat[] = "bkh0063  00:32 04/08/10 (c) Jamadata";
/* afdrukken rekeningen LKG */

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DIM_CENT        30
#define flag            uint16
#define C1              256E0
#define C2              65536E0

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF
					
extern char info[];
extern uint16 procid;
extern uint16 jamin1[5];


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

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
static long val(),val1();
extern float *f();
extern double *d();
static double Round(bd_,q_decim_);

static char fm_obd[]   = {6,0x95,8,2,0x70,0};/* od8_2 */
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_od9_2[] = {6,0x95,9,2,0x70,0};

static int16 form_dat[8],pr_mode,free,lst_typ,prtnr,stu_bew,stu;
static int16 z_opm,z_cumsal;
static uint16 rek_nr,dt_beg,dt_end,jaar,journl,ref_yy,ref_jr,mnd_kw,mnd_strt,period_1,MinBkhDatum;
static uint16 dt_bew,searcnr,volgnr,ref_vl,recordcnt,sys4524,last_arc;
static uint16 dat_sbeg;
static double bd_cre,bd_deb,bd_tot_lst;
static double bdt_cre,bdt_deb,bdp_cre,bdp_deb,cum_saldo;
static long grb_nr,sub_mask,kltcent,levcent,hoev;
static char naam[21],opm[41],meded[15],sys1787,oldnm[51],fmt[40],filres[20],anal_opm[41];
static char str4498[23],sys4521,munt[4],buf50[50],str_beg[15],buf750[750];
static double bd_vm;
static flag debit_allow=NO,credt_allow=NO,lvcd,klcd,year_rek;
static flag analyt,anal_skipped=NO,Prt2Xls=NO,opened,full_lst;

extern int16 ilength; // XLS
static int XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi; // XLS
static int16 StylTotaal, StylGrpTot, StylKlasse, StylNormal, StylDate, StylTitel, Styl2Use;


#include "Std\XlsFunc.c"

							   /* de variabelen */
static struct {
  uint16 dt_beg;
  uint16 dt_end;
  double bd_deb;
  double bd_cre;
} tb_cent[DIM_CENT];
									
static char *p_data;
static long *pl_80_1;
									
static char seqo_str[4000];
static char filnam[80];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;

static int16 date2str();
ovlcod()
{
  sel_lst=(struct _sel_lst*)u(26,1);
  if(sel_lst->l_rk==NO && sel_lst->k_rk==NO && sel_lst->g_rk==NO) goto endsr;

  initload();fasunlck(-1);

  if(sel_lst->l_rk && credt_allow) {lst_typ=0;pr_1lst("Leveranciers");}
  if(sel_lst->k_rk && debit_allow) {lst_typ=1;pr_1lst("Klanten");}
  if(sel_lst->g_rk) {lst_typ=2;pr_1lst("Grootboek");}
  if(Prt2Xls==NO) free=prtclose();
  endsr:
  if(sel_lst->yr) ovlexit(10); else ovlexit(64);
}

static pr_1lst(phdr)
char *phdr;
{
  int16 ks,fkey=2,p26;
  flag first;

  if(free==-1) goto endsr;
  scrget(1,6);scrupd(-3,0);
  stu=lst_typ+1;
  bd_tot_lst=0;
  pr_init(phdr);
  fasinit(stu);
  p26=0; if(stu<3) p26=26+(stu-1)*2;
  switch(lst_typ){
    case 0  : if(p26){*u(1,1)=*u(26,26); if(*u(1,1)) fasgeti(1);} break;
    case 1  : if(p26){*u(2,1)=*u(26,28); if(*u(2,1)) fasgeti(2);} break;
    default : *l(3,2)=*l(26,9); break;
  }
  fkey=1;
  FOREVER{
    next:
    if(lst_typ<2) ks=faskeyi(stu,2,fkey);
    else ks=faskeyi(stu,1,fkey);
    fkey=2;
    if(ks) break;
    if(lst_typ==2){
      if(*l(26,10) && cmp_fmx(l(26,10),l(3,2))>0) break;
      if(*l(3,2)==levcent || *l(3,2)==kltcent) *s(3,4)='J';
      if(year_rek && *s(3,4)=='J' && *u(26,2)==0) goto next;/* punt 5.0.8 */
    }
    else{
      searcnr=*u(stu,1)+lst_typ*30000;
      if(stu<3) corr_y2000(4,searcnr);
    }
    first=YES;
    fasinit(4);stu_bew=4;
    searcnr=*u(stu,1)+lst_typ*30000;
    if(init_rek()) first=NO;
    fasinit(4);stu_bew=4;
    if(lst_typ<2 || year_rek) *u(4,5)=searcnr; else *l(4,6)=*l(3,2);
    if(year_rek){
      fasinit(86);
      if(lst_typ<2 || year_rek) *u(86,5)=searcnr; else *l(86,6)=*l(3,2);
      rec_get(86);
    }
    FOREVER{
      if(next_rec()==0){/* get record, en stu_bew zetten */
	if(first==NO) pr_rek();
	break;
      }
      if((*u(stu_bew,4)<=dt_end) && ((lst_typ<2 && full_lst) || *u(stu_bew,4)>=dt_beg)){
	if(first) pr_rk_nm(0);
	add_bew();
	first=NO;
      }
      if(free==-1) break;
    }
    if(free==-1) break;
    if(lst_typ<2 && p26){/* van-tot */
      if(*u(26,p26+1) && *u(26,p26+1)==*u(stu,1)) break;
    }
  }
  if(year_rek==NO && lst_typ<2) prt_totaal();
  if(Prt2Xls==NO) formfeed();
	else XlsClose(XlsRef,1);
  endsr:;
}

static corr_y2000(bstu_,searcnr_)    /* Y2000 probleem oplossen tijdelijk tot 2005 */
uint16 bstu_,searcnr_;
{
  char *ry_,*rjn_,ly_;
  uint16 *prec_,*rvl_,mode_,len_stu_;
									
  scrget(1,7);scrupd(-3,0);
  prec_=u(bstu_,5);ry_=s(bstu_,8);
  rjn_=s(bstu_,9); rvl_=u(bstu_,10); len_stu_=fldlen(bstu_,0);
  fasinit(bstu_); *prec_=searcnr_; mode_=1; ly_=*ry_;
  FOREVER{
    if(faskeyi(bstu_,4,mode_)) break; mode_=2;
    if(*prec_!=searcnr_) break;
		if(*ry_>=100) break; // geen foute referenties 
    ly_=*ry_;
    if(*rjn_ || *rvl_){
      if(*ry_<50) *ry_+=100;
    } else if(*ry_==100) *ry_=0;
    if(*ry_!=ly_) { fasupd(bstu_); mode_=1;}               /* indien gewijzigd, updaten */
    *ry_=ly_;                                      /* key-volgorde behouden */
  }
}
		
static pr_init(phdr)
char *phdr;
{
  int16 z;
	char nm_list_[35];

  if(Prt2Xls==NO){
		getsysprNew(3,form_dat,&pr_mode,&prtnr);if(sel_lst->prt2pdf) PrintPaperNr=0;
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) ovlexit(10);
    free=999;
    prtnew();
    prtfld(25,1,-1);
    prttext("<t45eb>"); prttext(phdr);prttext("rekeningen<eb>");
    prttext("<t92>"); prtfld(26,2,-1);
    prttext(" - "); prtfld(26,3,-1);
    if(full_lst==NO) prttext("<t118>* ");
    prttext("<t120>Blz.<ppp>.");
    prtbuf(1);
    z=1;
    prtitab(z,fm_uu2_,&jaar,3,-1); prttitle(z++,"Jr.",3);
    prtitab(z,fm_uu2,&journl,2,-1); prttitle(z++,"Jrn.",3);
    prtitab(z,fm_uu5,&volgnr,2,-1); prttitle(z++,"Volgn.",3);
    prtitab(z,fm_odat,&dt_bew,0,-1); prttitle(z++,"Datum",0x43);
    prtitab(z,fm_obd,&bd_deb,0,-1); prttitle(z++,"D-Bedrag",0x13);
    prtitab(z,fm_obd,&bd_cre,1,-1); prttitle(z++,"C-Bedrag",0x13);
    if(lst_typ<2 || bit(sys1787,6)){
      if(fldlen(4,15)){
	prtitab(z,fm_od9_2,&bd_vm,1,-1); prttitle(z++,"Bedrag",0x13);
	prtitab(z,fm_os3,munt,1,-1); prttitle(z++,"VM",0x13);
      }
      prtitab(z,fm_uu4,&ref_yy,2,-1); prttitle(z++,"Jr.",3);
      prtitab(z,fm_uu2,&ref_jr,2,-1); prttitle(z++,"Jrn.",3);
      prtitab(z,fm_uu5,&ref_vl,2,-1); prttitle(z++,"Volgn.",3);
    }
    z_cumsal=z;
    prtitab(z,fm_obd,&cum_saldo,1,-1); prttitle(z++,"Cum.saldo",0x13);
    z_opm=z;
    prtitab(z,fm_os20,opm,1,-1); prttitle(z++,"Opmerking",3);
    if(lst_typ==0){
      prtitab(z,fm_os15,meded,0,-1); prttitle(z++,"Mededeling",3);
    }
    if(lst_typ==2 && bit(sys1787,0)) prttext(" <bu>Tegenrekening<bu>");
    prtbuf(3);
    
    p_pdfname(phdr,0,0);p_pdfname("rekeningen",dt_beg,dt_end);
  }
  else{
		scrget(1,7);scrupd(-3,0);XlsRef=-1; zero(nm_list_,sizeof nm_list_);
		if(lst_typ==0) copy0("Leveranciersrekeningen",nm_list_,30);
		else if(lst_typ==1) copy0("Klantenrekeningen",nm_list_,30);
		else if(lst_typ==2) copy0("Grootboekrekeningen",nm_list_,30);
		XlsRef=OpenXlsFile(nm_list_,*u(26,2),*u(26,3));
    if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsSelectWorkSheet(XlsRef,1,nm_list_);
		XlsColumnSize(XlsRef,2,40);XlsColumnSize(XlsRef,11,30);
		if(lst_typ==2){
			XlsColumnSize(XlsRef,13,30);XlsColumnSize(XlsRef,14,20);
			if(analyt) XlsColumnSize(XlsRef,15,30);
		}
//XlsStyle(ref, char *NumFormat,Size, long /*COLORREF*/ Color, BoldFlag, ItalicFlag, UnderlineFlag,HorAlignment, VerAlignment,
//	long /*COLORREF*/ BackCol, int16 Pattern, Kader, KaderCol, Lock, Hide)
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
		StylGrpTot=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_BEIGE,1,1,0,NO,NO);
		StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);

		XlsRij=1;XlsKol=1;Styl2Use=StylTitel;
	  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Nr",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Journaal",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Volgnr",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Datum",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Debet",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Credit",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Ref.jaar",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Ref.journaal",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Ref.volgnr",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Opmerking",Styl2Use);
		if(lst_typ==2){
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Nummer tegenrekening",Styl2Use);
		  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Naam tegenrekening",Styl2Use);
		  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Opmerking tegenrekening",Styl2Use);
			if(analyt) XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Analytische rekening",Styl2Use);
		}
		XlsRij++;XlsKol=1;
  }
  endsr:;
  //else{

  //  if(lst_typ==0) seq_open("lev_rek.txt");
  //  else if(lst_typ==1) seq_open("klt_rek.txt");
  //  else if(lst_typ==2) seq_open("grb_rek.txt");
  //}
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
	pos_+=copy0(".XLSX",&string[pos_],4);
	
  pos_=XlsCreate(string);
	return pos_;
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

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
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
  int16 k,ks,sal_jn_;

  if(lst_typ==2 && analyt && ((*s(3,2) &0xF0)>>4)==9){
    if(anal_skipped==NO && Prt2Xls==NO) prtform(0);
    anal_skipped=YES;
  }
  bd_deb=0;bd_cre=0;sal_jn_=0;
  bdt_deb=0;bdt_cre=0;
  bdp_deb=0;bdp_cre=0;
  for(k=0;k<DIM_CENT;k++) {tb_cent[k].bd_deb=0;tb_cent[k].bd_cre=0;}
  hoev=0;
  if(year_rek && lst_typ>=2) return NO;
  fasinit(5);
  if(lst_typ>=2){/* enkel GRB */
    fasinit(5);
    *u(5,2)=*u(lst_typ+1,1)+lst_typ*30000;
    ks=faskeyi(5,1,0);
    if(ks==0 && period_1==0){
      bd_deb=*d(5,31);bd_cre=-*d(5,32);
      bdt_deb=bd_deb;bdt_cre=bd_cre;
      sal_jn_=YES;
    }
  }
  if(full_lst==NO){/* bereken saldo over deze periode */
    if(lst_typ<2 && year_rek){
      if(add_saldo(0,*u(26,2),86)) sal_jn_=YES;
      if(sal_jn_){/* als 1 saldobedrag voorstellen */
				bdt_deb-=bd_deb; bdt_cre-=bd_cre;
				if(bd_deb>bd_cre) {bd_deb-=bd_cre; bd_cre=0;}
				else {bd_cre-=bd_deb; bd_deb=0;}
				if(is_nul(bd_deb) && is_nul(bd_cre)) sal_jn_=NO;
				else {bdt_deb+=bd_deb; bdt_cre+=bd_cre;}
      }
      fasinit(86);
    }
    if(add_saldo(dat_sbeg,*u(26,2),4)) sal_jn_=YES;
    if(lst_typ<2) bd_tot_lst+=bd_deb-bd_cre;
    fasinit(4);
  }
  if(sal_jn_){
    pr_rk_nm(1);
    return YES;
  }
  return NO;
}

static add_saldo(dt_b_,dt_e_,bstu_)
uint16 dt_b_,dt_e_,bstu_;
{
  int16 mode_,sal_fnd_,new_boeking_=NO;
  double bedrag_,sal_bd_=0;

  sal_fnd_=NO; fasinit(bstu_); mode_=1;
  if(lst_typ<2){
    *u(bstu_,5)=*u(stu,1)+lst_typ*30000;
    dt_b_=0;/* steeds ALLES nemen */
  }
  else{
    *l(bstu_,6)=*l(3,2);
  }
  FOREVER{
    if(lst_typ<2 || year_rek){
      if(faskeyi(bstu_,4,mode_)) break; mode_=2;
      if(*u(bstu_,5)!=*u(stu,1)+lst_typ*30000) break;
    }
    else{
      if(faskeyi(bstu_,3,mode_)) break; mode_=2;
      if(*l(bstu_,6)!=*l(3,2)) break;
    }
    if(*u(bstu_,4)>=dt_b_ && *u(bstu_,4)<dt_e_){
      bedrag_=*d(bstu_,32);
      if(bedrag_>=0){
				bd_deb+=bedrag_;
				bdt_deb+=bedrag_;
      }
      else {
				bd_cre-=bedrag_;
				bdt_cre-=bedrag_;
      }
			if(*u(bstu_,4)>MinBkhDatum) new_boeking_=YES;
      sal_bd_+=*d(bstu_,32); sal_fnd_=YES;
    }
  }
	if(new_boeking_==NO && is_nul(sal_bd_)) sal_fnd_=NO;
  return sal_fnd_;
  endsr:;
}

static add_bew()
{
  int16 k,len,dum1,dum2,code,mode_,q_anal_;
  uint16 dt_;
	long rec4_,analgrbs_[10];
  double bedrag;

  code=YES; if((lst_typ==0 && lvcd==NO) || (lst_typ==1 && klcd==NO)) code=NO;
  bedrag=*d(stu_bew,32);
  if(bedrag>=0){
    bd_deb=bedrag;bd_cre=0;
    bdt_deb+=bedrag;
  }
  else {
    bd_cre=-bedrag;bd_deb=0;
    bdt_cre-=bedrag;
  }
  if(lst_typ<2 || *s(3,4)=='N' || Prt2Xls==YES || (*s(3,4)=='J' && year_rek && stu_bew==86)){
    if(Prt2Xls==NO) free_tst(2);
    jddate(*u(stu_bew,4),&jaar,&dum1,&dum2);
    jaar=jaar%100;
    journl=*s(stu_bew,2);
    volgnr=*u(stu_bew,3);
    dt_bew=*u(stu_bew,4);
    ref_yy=*s(stu_bew,8);
    ref_jr=*s(stu_bew,9);
    ref_vl=*u(stu_bew,10);
    if(ref_jr || ref_vl) ref_yy+=1900;/* y2000 */
    if(fldlen(4,15)){
      copy(s(stu_bew,15),munt,3);
      bd_vm=*d(stu_bew,16);
    }
    zero(opm,sizeof opm); zero(anal_opm,sizeof anal_opm);
    zero(meded,sizeof meded);zero((char *)analgrbs_,sizeof analgrbs_); q_anal_=0;
    len=fldlen(stu_bew,28);if(len>40) len=40;
    copy(s(stu_bew,28),opm,len);
    hoev+=val1(opm);
    if(lst_typ==2 && analyt){
      if(((*s(3,2) &0xF0)>>4)==9) mk_anal_opm(*l(stu_bew,11),opm,40);
			else if(Prt2Xls && stu_bew==4){ // bij gewone rekening analytische rekening uitschrijven
				rec4_=*l(4,1);
				*l(4,1)=0;mode_=1;
				FOREVER{
					if(faskeyi(4,1,mode_)) break; mode_=2;
					if(*s(4,2)!=journl) break;
					if(*u(4,3)!=volgnr) break;
					if(*u(4,4)==dt_bew && ((*s(4,6) &0xF0)>>4)==9 && *l(4,11)==*l(3,2)){
						if(bedrag==*d(stu_bew,32)){	mk_anal_opm(*l(4,6),anal_opm,40);	break;}
						else{
							for(k=0;k<q_anal_;k++) if(*l(4,6)==analgrbs_[k]) break;
							analgrbs_[k]=*l(4,6);
							if(k==q_anal_ && q_anal_<10-1) q_anal_++;
						}
					}
				}
				*l(4,1)=rec4_; fasgeti(4);
			}
    }
    if(bit(sys1787,4) && *u(stu_bew,20)) dt_bew=*u(stu_bew,20);
    copy(s(stu_bew,27),meded,15);
    if(Prt2Xls==NO){
      cum_saldo=bdt_deb-bdt_cre;
      for(k=1;k<30;k++) prtinfo(k,0);
      if(lst_typ==2 && bit(sys1787,0)){
	prt_tegen();
      }
      nextline();
    }
    else{
			XlsKol=1;
      if(fldlen(stu,2)) WriteFld2Xls(XlsRij,XlsKol++,stu,2,StylNormal);  else WriteFld2Xls(XlsRij,XlsKol++,stu,1,StylNormal);
      WriteFld2Xls(XlsRij,XlsKol++,stu,3,StylNormal);
      *u(stu_bew,3)=*s(stu_bew,2);WriteFld2Xls(XlsRij,XlsKol++,stu_bew,3,StylNormal);fasgeti(stu_bew);
      WriteFld2Xls(XlsRij,XlsKol++,stu_bew,3,StylNormal);WriteFld2Xls(XlsRij,XlsKol++,stu_bew,4,StylDate);
      *d(stu_bew,32)=bd_deb;WriteFld2Xls(XlsRij,XlsKol++,stu_bew,32,StylNormal);
      *d(stu_bew,32)=bd_cre;WriteFld2Xls(XlsRij,XlsKol++,stu_bew,32,StylNormal);
      fasgeti(stu_bew);
      *u(stu_bew,10)=ref_yy;WriteFld2Xls(XlsRij,XlsKol++,stu_bew,10,StylNormal);
      *u(stu_bew,10)=ref_jr;WriteFld2Xls(XlsRij,XlsKol++,stu_bew,10,StylNormal);
      *u(stu_bew,10)=ref_vl;WriteFld2Xls(XlsRij,XlsKol++,stu_bew,10,StylNormal);
			WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(40,0),opm,StylNormal);
//      WriteFld2Xls(XlsRij,XlsKol++,stu_bew,28,StylNormal);
      if(lst_typ==2) prt_tegen();
			if(analyt){
				if(anal_opm[0]) WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(40,0),anal_opm,StylNormal);
				else {
					for(k=0;k<q_anal_;k++){
						zero(anal_opm,sizeof anal_opm);mk_anal_opm(analgrbs_[k],anal_opm,40);
						WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(40,0),anal_opm,StylNormal);
					}
				}
			}
			XlsRij++;XlsKol=1;
    }
  }
  else{
    dt_=*u(stu_bew,4);
    for(k=0;k<DIM_CENT;k++){
      if(dt_>=tb_cent[k].dt_beg && dt_<=tb_cent[k].dt_end){
	tb_cent[k].bd_deb+=bd_deb;tb_cent[k].bd_cre+=bd_cre;
	break;
      }
    }
    bdp_deb+=bd_deb;bdp_cre+=bd_cre;
  }
  bd_tot_lst+=bedrag;
}

static mk_anal_opm(rek_,ps_,len_)
char *ps_;
long rek_;
int16 len_;
{
  int16 k;
  char buf_[50];
									
  zero(buf_,sizeof buf_); copy(s(3,1),buf750,fldlen(3,0));
  fasinit(3); *l(3,2)=rek_;faskeyi(3,1,0);
  grb_deco(buf_,l(3,2));
  for(k=0;k<9;k++) if(buf_[k]=='\0') break;
  buf_[k++]=' '; copy(s(3,3),&buf_[k],fldlen(3,3));
  copy(buf_,ps_,len_);
  copy(buf750,s(3,1),fldlen(3,0));
}

static rec_get(stu_)
int16 stu_;
{
  int16 ks;
  flag stop=NO;

  redo:;
  if(lst_typ<2 || year_rek){
    ks=faskeyi(stu_,4,2);
    if(*u(stu_,5)!=*u(stu,1)+lst_typ*30000) stop=YES;
  }
  else{
    ks=faskeyi(stu_,3,2);
    if(*l(stu_,6)!=*l(3,2)) stop=YES;
  }
  if(ks || stop){
    if(stu_==86) *l(86,1)=0; else *l(4,1)=0;
  }
  else if(fldlen(stu_,19) && ((sub_mask & *l(stu_,19))==0)) goto redo;
}

static next_rec()
{
  rec_get(stu_bew);
  if(year_rek==0){
    if(*l(4,1)==0) return NO;
    else return YES;
  }
  if(*l(4,1)==0 && *l(86,1)==0) {return NO;}
  FOREVER{
    if(*l(4,1)==0) {stu_bew=86;break;}
    if(*l(86,1)==0) {stu_bew=4;break;}
    if(*s(4,8)<*s(86,8)) {stu_bew=4;break;}
    if(*s(86,8)<*s(4,8)) {stu_bew=86;break;}
    if(*s(4,9)<*s(86,9)) {stu_bew=4;break;}
    if(*s(86,9)<*s(4,9)) {stu_bew=86;break;}
    if(*u(4,10)<*u(86,10)) {stu_bew=4;break;}
    stu_bew=86;break;
  }
  return YES;
}

static prt_tegen()
{
  int16 k,jr_,stu_,fkey_;
  uint16 date_,vl_,tegen_rek=0;
  long rec_,rect_=0;

  if(stu_bew==4){
    rec_=*l(4,1);
    jr_=*s(4,2);
    for(k=0;k<80;k++){
      if(jr_==j_tab[k].nr) break;
    }
    if(j_tab[k].typ<3){
      vl_=*u(4,3);date_=*u(4,4);
      *l(4,1)=0;
      fkey_=1;
      FOREVER{
				if(faskeyi(4,1,fkey_)) break;
				fkey_=2;
				if(jr_!=*s(4,2) || vl_!=*u(4,3)) break;
				if(*u(4,5)<60000 && date_==*u(4,4)){
					tegen_rek=*u(4,5);rect_=*l(4,1);
					break;
				}
      }
      *l(4,1)=rec_;fasgeti(4);
    }
		else if(j_tab[k].typ!=8){ // fin. journalen excl openingsbalans
			if(*u(4,5)<60000){
				tegen_rek=*u(4,5);rect_=*l(4,1);
			}
		}
  }
  else {/* in stu 86 */
    tegen_rek=*u(86,6);
  }
  if(tegen_rek){
    if(tegen_rek<30000) stu_=1; else stu_=2;
    fasinit(stu_);*u(stu_,1)=tegen_rek-((stu_-1)*30000);fasgeti(stu_);
    if(Prt2Xls==NO){
      if((stu_==1 && lvcd) || (stu_==2 && klcd)){
				prtfld(stu_,2,-1);
      }
      else prtfld(stu_,1,-1);
      prtblank(1);prtfld(stu_,3,28);
    }
    else{
      if((stu_==1 && lvcd) || (stu_==2 && klcd)) WriteFld2Xls(XlsRij,XlsKol++,stu_,2,StylNormal);
      else WriteFld2Xls(XlsRij,XlsKol++,stu_,1,StylNormal);
      WriteFld2Xls(XlsRij,XlsKol++,stu_,3,StylNormal);
			if(rect_){
				fasinit(4);*l(4,1)=rect_;fasgeti(4);
				WriteFld2Xls(XlsRij,XlsKol++,4,28,StylNormal);
				fasinit(4);*l(4,1)=rec_;fasgeti(4);
			}
			else XlsWrite(XlsRef,XlsRij,XlsKol++,0," ",StylNormal);
    }
  }
	else if(Prt2Xls){
		for(k=0;k<3;k++) XlsWrite(XlsRef,XlsRij,XlsKol++,0," ",StylNormal);
	}
}
 
static prt_totaal()
{
  if(bd_tot_lst){
    if(Prt2Xls==NO){
      prttitle(1," Totaal lijst",2);
      if(bd_tot_lst>0) {bd_deb=bd_tot_lst;prtinfo(5,2);}
      else {bd_cre=-bd_tot_lst;prtinfo(6,2);}
      nextline();
    }
  }
}

static initload()
{
  int16 j,k,yy_,mm_,dd_,dum1,dum2;
  uint16 dtb_, dte_;

  fasunlck(0);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  if(credt_allow) fileopen(1);
  if(debit_allow) fileopen(2);
  for(k=3;k<=5;k++) fileopen(k);
  fileopen(10);

  for(k=0;k<80;k++){
    sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
  }
  j_tab[80].nr=0;j_tab[80].typ=3;copy("???",&j_tab[80].nm[0],4);

  getsysprNew(3,form_dat,&pr_mode,&prtnr);

  sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);

  sysget(1787,1,&sys1787);
  sysget(1858,2,&last_arc);
  sysget(2300,2,&MinBkhDatum);if(MinBkhDatum<last_arc) {MinBkhDatum=last_arc;sysput(2300,2,&MinBkhDatum);}
  sysget(4498,23,str4498);
  sysget(4521,1,&sys4521);
  sysget(4524,2,&sys4524);
	
  dt_beg=*u(26,2);
  dt_end=*u(26,3);
  sysget(1864,2,&mnd_kw);
  sysget(1866,2,&mnd_strt);
  full_lst=YES; if(last_arc!=0 && *u(26,2)!= last_arc+1) full_lst=NO;
  if(full_lst==NO){
    jddate(dt_beg,&yy_,&mm_,&dd_); yy_%=100;
    yy_%=100; if(mnd_strt>mm_) yy_--; if(yy_<0) yy_=99;/* jaar 2000 */
    dat_sbeg=datejd(yy_,mnd_strt,1);/* 1/1 van gevraagd boekjaar */
    if(dat_sbeg>(last_arc+1)){/* GEEN saldi tellen */
      period_1=1;
      jddate(dat_sbeg,&yy_,&mm_,&dd_);
      stcli_d(str_beg,(long)dd_,2,0);str_beg[2]='/';
      stcli_d(&str_beg[3],(long)mm_,2,0);str_beg[5]='/';
      stcli_d(&str_beg[6],(long)yy_,4,0);
    }
    else{
      dat_sbeg=last_arc+1;
      period_1=0;   jddate(dat_sbeg,&yy_,&mm_,&dd_);
      if(mm_==mnd_strt) period_1=1;
    }
  }
  else {
    jddate(dt_beg,&dum1,&mm_,&dum2);
    period_1=0;
    if(mm_==mnd_strt) period_1=1;
  }
  dtb_=dt_beg; if(dt_beg<=last_arc) dtb_=last_arc+1;
  zero((char *)tb_cent,sizeof tb_cent);
  for(k=0;k<DIM_CENT;k++){
    jddate(dtb_,&yy_,&mm_,&dd_); yy_%=100;
    if(mnd_kw==1){/* kwartaal */
      mm_+=2;
      j=mm_%3; if(j) mm_-=j;
    }
    mm_++; if(mm_>12) {mm_=1; yy_++;}
    dte_=datejd(yy_,mm_,1); dte_--;if(dte_>=dt_end) dte_=dt_end;
    tb_cent[k].dt_beg=dtb_; tb_cent[k].dt_end=dte_;
    if(dte_>=dt_end) break;
    dtb_=dte_+1;
  }

  analyt=fldlen(4,11);
  sub_mask=*l(26,14);
  year_rek=sel_lst->yr;
  Prt2Xls=sel_lst->filrek;
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;
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

static pr_rk_nm(mode)
int16 mode;
{
  flag cd_=NO;

  if(Prt2Xls==NO){
    free_tst(5);
    prttext("  <b>");
    if((lst_typ==0 && lvcd) || (lst_typ==1 && klcd) || lst_typ==2) cd_=YES;
    prtfld(lst_typ+1,cd_+1,-1);
    prttext("  ");prtfld(lst_typ+1,3,-1);prttext("<b>  ");
    if(lst_typ<2) prtfld(lst_typ+1,8,-1);
    nextline();nextline();
    if(mode){
      zero(buf50,sizeof buf50);
      copy(" Vorig saldo",buf50,12);
      if(lst_typ>=2 && full_lst==NO && dat_sbeg>(last_arc+1)){
	copy(" Saldo vanaf ",buf50,13);
	copy(str_beg,&buf50[13],10);
      }
      prttitle(1,buf50,0);
      prtinfo(5,2);prtinfo(6,2);
      cum_saldo=bdt_deb-bdt_cre;prtinfo(z_cumsal,0);
      nextline();
    }
  }
}

static pr_rek()
{
  int16 k;
  char str_[50];
 
  if(Prt2Xls==NO){
    free_tst(2);
    if(bdp_deb || bdp_cre){
      for(k=0;k<DIM_CENT;k++){
	if(tb_cent[k].bd_deb || tb_cent[k].bd_cre){
	  zero(str_,sizeof str_);
	  copy(" Totaal ",str_,8);
	  date2str(&str_[8],tb_cent[k].dt_beg);copy(" - ",&str_[13],3);
	  date2str(&str_[16],tb_cent[k].dt_end);
	  prttitle(1,str_,0);
	  bd_deb=tb_cent[k].bd_deb;prtinfo(5,0);
	  bd_cre=tb_cent[k].bd_cre;prtinfo(6,0);
	  cum_saldo+=bd_deb-bd_cre;prtinfo(z_cumsal,0);
	  nextline();
	}
      }
    }
    free_tst(1);
    prttitle(1," Nieuw saldo",2);
    if(bdt_deb>bdt_cre) {bd_deb=bdt_deb-bdt_cre;prtinfo(5,2);}
    else {bd_cre=bdt_cre-bdt_deb;prtinfo(6,2);}
    if(lst_typ==2 && bit(sys1787,5) && hoev){
      stcli_d(opm,hoev,7,1);
      prtinfo(z_opm,2);
    }
    nextline();
    if(bit(sys1787,lst_typ+1)) formfeed();
    else {
      if(free)nextline();
      if(free)nextline();
    }
  }
}

static int16 date2str(str_,dt_)
char *str_;
uint16 dt_;
{
  int16 yy,mm,dd;
 
  jddate(dt_,&yy,&mm,&dd);yy%=100;
  stcli_d(str_,(long)dd,2,0);str_[2]='/';
  stcli_d(str_+3,(long)mm,2,0);str_[5]='/';
  stcli_d(str_+6,(long)yy,2,0);
}

 
static formfeed()
{
  prtform(0);free=999;
}

static free_tst(aantal)
int16 aantal;
{
  if(free<aantal) formfeed();
}

static nextline()
{
  free=prtline();
}

static bit(byte_,bit_)
char byte_;
int16 bit_;
{
  if(byte_ & 1<<bit_) return YES;
  return NO;
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
 
static cmp_fmx(p1,p2)
char *p1,*p2;
{
  int16 q=4;

  while(q-->0){
    if(*p1<*p2) return 1;
    if(*p1>*p2) return -1;
    p1++;p2++;
  }
  return 0;
}
 
static seq_open(pnam)
char *pnam;
{
  scrget(1,170);
  copy(pnam,filres,20);
  errnum=fasopen(filres,12);if(errnum) ovlexit(10);
  fasinit(80);seqo_pos=0;seqo_mode=2;seqo_len=0;
  scrget(1,7);scrupd(-3,0);
  recordcnt=0;opened=YES;
  free=999;
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

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}
 
static seqo_fld(stu_,fld_)
int16 stu_,fld_;
{
  if(fldlen(stu_,fld_)){
    fmt_get(stu_,fld_);
    seqo_var(fmt,s(stu_,fld_));
  } else seqo_str[pos++]=0x09;
}

static seqo_var(fm_,pvar_)
char *fm_,*pvar_;
{
  int16 yy,mm,dd,len_,k;
  float fbd_;
  char str_[50];
 
  if(fm_[1]==0xC8 || fm_[1]==0x88){/* string */
    len_=fm_[2];
    char2str(&str4498[4],2);
    for(k=0;k<len_;k++){
      if(*(pvar_+k)=='\0') break;
      if(*(pvar_+k)==str4498[4]) *(pvar_+k)='.';/* delete " */
      if(*(pvar_+k)==str4498[6]) *(pvar_+k)='.';/* delete " */
      if(*(pvar_+k)==str4498[8]) *(pvar_+k)='.';/* delete ; */
    }
    char2str(pvar_,len_);
    char2str(&str4498[6],2);
  }
  if(fm_[1]==0xD0 || fm_[1]==0x90){/* uint16 */
    fbd_=*(uint16 *)pvar_;
    char2str(&str4498[0],2);
    flt2str(fbd_);
    char2str(&str4498[2],2);
  }
  if(fm_[1]==0xD1 || fm_[1]==0x91){/* integer */
    fbd_=*(int16 *)pvar_;
    char2str(&str4498[0],2);
    flt2str(fbd_);
    char2str(&str4498[2],2);
  }
  if(fm_[1]==0xD3 || fm_[1]==0x93){/* long */
    fbd_=*(long *)pvar_;
    char2str(&str4498[0],2);
    flt2str(fbd_);
    char2str(&str4498[2],2);
  }
  if(fm_[1]==0xD4 || fm_[1]==0x94){/* float */
    fbd_=*(float *)pvar_;
    char2str(&str4498[0],2);
    flt2str(fbd_);
    char2str(&str4498[2],2);
  }
  if(fm_[1]==0xD5 || fm_[1]==0x95){/* double */
    fbd_=*(double *)pvar_;
    char2str(&str4498[0],2);
    flt2str(fbd_);
    char2str(&str4498[2],2);
  }
  if(fm_[1]==0xC0 || fm_[1]==0x80){/* date */
    char2str(&str4498[0],2);
    if(*(uint16 *)pvar_!=0){
      jddate(*(uint16 *)pvar_,&yy,&mm,&dd);
      stcli_d(str_,(long)dd,2,0);str_[2]='/';
      stcli_d(&str_[3],(long)mm,2,0);str_[5]='/';
      stcli_d(&str_[6],(long)yy,4,0);
      char2str(str_,10);
    }
    char2str(&str4498[2],2);
  }
  if(fm_[1]==0xD8 || fm_[1]==0x98){/* BTW-nummer */
  	zero(str_,sizeof str_); btw_deco(&str_[0],(long *)pvar_,2); 
//    btw_deco(str_,(long *)pvar_,YES);
    char2str(&str4498[4],2);
    char2str(str_,14);
    char2str(&str4498[6],2);
  }
  if(fm_[1]==0xA8 || fm_[1]==0xE8){/* grb */
    zero(str_,sizeof str_);
    grb_deco(str_,(long *)pvar_);
    char2str(&str4498[4],2);
    char2str(str_,10);
    char2str(&str4498[6],2);
  }
  if(fm_[1]==0xE0 || fm_[1]==0xA0){/* rekening */
    zero(str_,sizeof str_);
    rek_deco(str_,pvar_,'-');
    char2str(&str4498[4],2);
    char2str(str_,14);
    char2str(&str4498[6],2);
  }
  char2str(&str4498[8],5);
  endsr:;
}

static char2str(ps_,len_)
char *ps_;
int16 len_;
{
  int16 orig_pos_;
 
  orig_pos_=pos;
  if(len_){
    copy(ps_,&seqo_str[pos],len_);while(seqo_str[pos]) pos++;
    pos--;
    while(seqo_str[pos]==' ') pos--;/* delete trailing blanks */
    pos++;
  }
}

static flt2str(bd_)
float bd_;
{
  double bedrag_,add_=0;
  long val_;
								
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*100+add_;value=val_/100;

  if(bedrag_<0 && value==0){copy("-0",&seqo_str[pos],2);pos+=2;}
  else val2str(0);
  value=val_-value*100;
  if(value){
    seqo_str[pos++]=',';
    if(value<0) value=-value;val2str(1);
  }
}

static val2str(mode_)
int16 mode_;
{
  int16 k;
  char buff[15];

  zero(buff,sizeof buff);
  if(mode_==0){
    stcli_d(&buff[0],value,10,1);
    for(k=0;k<10;k++){
      if(buff[k]=='\0') break;
      if(buff[k]!=' ') seqo_str[pos++]=buff[k];
    }
  }
  else{
    if(value<0) value=-value;
    stcli_d(&buff[0],value,2,0);
    for(k=1;k>=0;k--) if(buff[k]!='0') break;
    copy(&buff[0],&seqo_str[pos],k+1);pos+=k+1;
  }
}
 
//static btw_deco(ps_,val_)
//char *ps_;
//long *val_;
//{
//  char str_[10];
//
//  if(*val_==0) copy("  0000.000.000",ps_,14);
//  else{
//    stcli_d(str_,*val_,9,0);
//    copy("BE ",ps_,3);/* BTW nummer met BE */
//    copy(&str_[0],ps_+3,3);*(ps_+6)='.';
//    copy(&str_[3],ps_+7,3);*(ps_+10)='.';
//    copy(&str_[6],ps_+11,3);
//  }
//}

static rek_deco(s,r,sepflag)
char s[], r[], sepflag;
{
  double d;
  int16 index, i;
							
  d = r[0]+C1*(r[1]+C1*(r[2]+C1*(r[3]+C1*r[4])));
  stcdf_d(s,d,12,NO);
  if (sepflag) {
    i=2;
    for (index=14; index>2; index--) {
      if ((index==11)||(index==3)) {s[index]='-'; i--;}
      else s[index]=s[index-i];
    }
  }
}

static seqo_flush()
{
  if(seqo_len){
    fasseqo(80,seqo_mode,seqo_len+4);
    seqo_pos+=seqo_len;
    *l(80,1)=seqo_pos;
    seqo_len=0;
  }
}
 
