/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0061GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0061dat
#define ovlcod BKH0061cod
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

char ovldat[] = "bkh0061  00:43 04/08/10 (c) Jamadata";
/* afdrukken journalen */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define STK_REC         65
#define QCJ             300
#define QINV            50
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
static char jnl_used[81];
 
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

static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x10,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};
static char fm_ud82_[] = {6,0xD5,8,2,0x60,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};

static int16 form_dat[8],pr_mode,free,prtnr;
static int16 stulk,loscnt,stk_r_poin,arr_jr,cj_poin;
static int16 inv_poin=0,pdf_open;
static uint16 bk_dat,stuknr,rekennr,ref_yy,ref_jr,ref_vl;
static uint16 dt_beg,dt_end,jr_beg,jr_end,volg_beg,volg_end;
static uint16 last_arc,nr_journ,jr_typ;
static uint16 mnd_strt, period_1, dat_sbeg, full_lst;
static long stk_rec[STK_REC],inv_rec[QINV];
static double bd_cre,bd_deb,bd_v[10],bd_los[50],bd_los_,bedrag,fin_saldo;
static double bdt_cre,bdt_deb,bdt_v[10],bdt_los;
static double btw_bdjr[100],btw_bdt[100],btw_bdft[100];
static double cj_deb[QCJ],cj_cre[QCJ],cjt_deb=0,cjt_cre=0;

static long grb_los[50],grb_los_,sub_mask,cj_grb[QCJ];

static char hdr_v[4][7],naam[30],klnaam[30],omschr[40],nm_los[50][20],rek_kod[9];
static char opm[51],mededeling[21],sys1785,sys1786,fm_bdr[40],fm_vbdr[40];
static flag debit_allow=NO,credt_allow=NO,fin_1e,fin_yet_prt,lvcd,klcd,prt_fin_sal;
static flag analyt,opened[10],v86_used,v87_used;
static float btwpct[4];
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;

ovlcod()
{
  sel_lst=(struct _sel_lst*)u(26,1);
  if(sel_lst->jr || sel_lst->btw){
    initload();fasunlck(-1);
    execute();
  }
  if(sel_lst->a_btw && ovltest(65)) ovl_exit(65);
  ovl_exit(62);
}

static execute()
{
  int16 ks,key_mode,kaskey_,jnkey_=1;
  flag first=YES;

  scrget(1,6);scrupd(-3,0);zero(opm,sizeof opm); zero(mededeling,sizeof mededeling);
  fasinit(4);
  if(jr_beg || volg_beg){*s(4,2)=jr_beg;*u(4,3)=volg_beg;}
  key_mode=1; jnkey_=1; kaskey_=5; if(faskeyi(4,5,0)==45) kaskey_=1; 
  FOREVER{
		redo:;
    ks=faskeyi(4,jnkey_,key_mode);key_mode=2;
    if((*s(4,2)>jr_end) || (*s(4,2)==jr_end && *u(4,3)>volg_end)) ks=YES;
    if(ks)*s(4,2)=255;
    if(!ks){
      if((*u(4,4)<dt_beg || *u(4,4)>dt_end)) goto next;
      if(fldlen(4,19) && ((sub_mask & *l(4,19))==0)) goto next;
    }
    if(*s(4,2)!=nr_journ || *u(4,3)!=stuknr){
      if(first==NO){
				if(jr_typ<3){pr_stuk();end_btw();}
				if((jr_typ==3 || jr_typ==4 || jr_typ==9 || jr_typ==10) && prt_fin_sal) pr_finsal();
				if(*s(4,2)!=nr_journ) exit_jrn();
      }
      if(ks)break;
      if(*s(4,2)!=nr_journ) init_jrn();
      init_stk();
			if((jr_typ==4 || (jr_typ==3 && mnd_strt!=1)) && jnkey_!=kaskey_){ // kasjournaal of bankjournaal bij boekjaar != 1: datum -> nummer
				jnkey_=kaskey_; *u(4,3)=0; *u(4,4)=dt_beg; first=YES; key_mode=1;goto redo;
			}
			else if(!(jr_typ==4 || (jr_typ==3 && mnd_strt!=1)) && jnkey_!=1){ // alle andere journalen : nummer
				jnkey_=1; *u(4,3)=volg_beg; *u(4,4)=0; first=YES; key_mode=1; goto redo;
			}
    }
    if(ks)break;
    add_bew();
    if(free==-1) break;
    first=NO;jnl_used[arr_jr]=YES;
    next:;
  }
  free=prtclose();pdf_open=NO;
  if(free==-1) {prtclose();ovl_exit(10);}
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

static init_jrn()
{
  int16 ks;
  char buf400_[400];

 
  nr_journ=*s(4,2);
  for(arr_jr=0;arr_jr<80;arr_jr++){
    if(nr_journ==j_tab[arr_jr].nr) break;
  }
  jr_typ=j_tab[arr_jr].typ;
  bdt_cre=0;bdt_deb=0;
  zero((char *)bdt_v,sizeof bdt_v);
  bdt_los=0;
  cj_poin=0;
  zero((char *)btw_bdjr,sizeof btw_bdjr);
  fin_yet_prt=NO;
  prt_fin_sal=NO;

  if(*u(26,5)==0 && (jr_typ==3 || jr_typ==4 || jr_typ==9 || jr_typ==10)){
    prt_fin_sal=YES;fin_saldo=0;
    fasinit(3);*l(3,2)=j_tab[arr_jr].fingrb;faskeyi(3,1,0);
    fasinit(5);*u(5,2)=*u(3,1)+60000;ks=faskeyi(5,1,0);
    if(ks==0 && (period_1==0 || full_lst)){
      fin_saldo=*d(5,31)+ *d(5,32);
    }
    if(full_lst==NO){/* bereken saldo over deze periode */
      copy(s(4,1),buf400_,fldlen(4,0));
      add_saldo(dat_sbeg,*u(26,2));
      copy(buf400_,s(4,1),fldlen(4,0));
    }
  }
  prtclose();pdf_open=NO;
	
	getsysprNew(3,form_dat,&pr_mode,&prtnr);if(sel_lst->prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) ovl_exit(10);
  if(dt_beg==last_arc+1) prtpage(j_tab[arr_jr].blz_o+1); free=999;
  prt_hdr(YES,YES);
}

static add_saldo(dt_b_,dt_e_)
uint16 dt_b_,dt_e_;
{
  int16 mode_,sal_fnd_;
  double bedrag_=0;

  sal_fnd_=NO; fasinit(4); mode_=1;
  *l(4,6)=*l(3,2);
  FOREVER{
    if(faskeyi(4,3,mode_)) break; mode_=2;
    if(*l(4,6)!=*l(3,2)) break;
    if(*u(4,4)>=dt_b_ && *u(4,4)<dt_e_){/* tot begindatum tellen */
      bedrag_=*d(4,32);
      fin_saldo+=bedrag_;
      sal_fnd_=YES;
    }
    else if(*u(4,4)==dt_e_ && *s(4,2)!=nr_journ){/* saldo 1/1 ook tellen */
      bedrag_=*d(4,32);
      fin_saldo+=bedrag_;
      sal_fnd_=YES;
    }
  }
  return sal_fnd_;
  endsr:;
}

static prt_hdr(mode1_,mode2_)
int16 mode1_,mode2_;
{
  int16 k;

  prtnew();
  prtfld(25,1,-1);
  prttext("<t50eb>");
  if(mode1_){
    prtifld(fm_uu2,&j_tab[arr_jr].nr,-1);
    prtblank(2);prttext(j_tab[arr_jr].nm);
  }
  else prttext("Totaal journalen");
  prttext("<eb>");
  prttext("<t92>"); prtfld(26,2,-1);
  prttext(" - "); prtfld(26,3,-1);
  prttext("<t120>Blz.<ppp>.");
  prtbuf(1);
  if(mode2_){
    if(jr_typ<3){
      if(jr_typ==1)stulk=1; else stulk=2;
      prtitab(1,fm_ou5,&stuknr,1,-1); prttitle(1,"Factr",3);
      prtitab(2,fm_odat,&bk_dat,1,-1); prttitle(2,"Datum",0x43);
      prtitab(3,fm_os30,klnaam,1,15); prttitle(3,"Naam",3);
      if((stulk==1 && lvcd) || (stulk==2 && klcd)){
	k=4-fldlen(stulk,2); if(k<0) k=0;
	prttab(4,stulk,2,k,6);
      }
      else prttab(4,stulk,1,0,-1);
      prttitle(4,"Code",0x43);
      prtitab(5,fm_bdr,&bd_deb,0,-1); prttitle(5,"Bedrag",0x13);
    }
    if(jr_typ==1){
      prtitab(6,fm_vbdr,&bd_v[1],1,-1); prttitle(6,"Goederen",0x13);
      prtitab(7,fm_vbdr,&bd_v[9],0,-1); prttitle(7,"B.T.W.",0x13);
      prtitab(8,fm_vbdr,&bd_los_,1,-1); prttitle(8,"Bedrag",0x13);
      prtitab(9,fm_ogrb,&grb_los_,1,-1); prttitle(9,"Rekening",3);
      prtitab(10,fm_os20,omschr,1,16); prttitle(10,"Omschrijving",3);
      if(bit(sys1785,0)){
	prtitab(11,fm_os20,mededeling,0,15);prttitle(11,"Mededeling",3);
      }
      else{
	prtitab(11,fm_os20,opm,0,20); prttitle(11,"Opmerking",3);
      }
    }
    if(jr_typ==2){
      prtitab(6,fm_vbdr,&bd_v[1],0,-1); prttitle(6,hdr_v[0],0x13);
      prtitab(7,fm_vbdr,&bd_v[2],0,-1); prttitle(7,hdr_v[1],0x13);
      prtitab(8,fm_vbdr,&bd_v[3],0,-1); prttitle(8,hdr_v[2],0x13);
      prtitab(9,fm_vbdr,&bd_v[4],0,-1); prttitle(9,hdr_v[3],0x13);
      prtitab(10,fm_vbdr,&bd_v[9],0,-1); prttitle(10,"B.T.W.",0x13);
      prtitab(11,fm_vbdr,&bd_los_,1,-1); prttitle(11,"Bedrag",0x13);
      prtitab(12,fm_ogrb,&grb_los_,0,-1); prttitle(12,"Reken.",3);
      prtitab(13,fm_os20,omschr,0,16); prttitle(13,"Omschr.",3);
    }
    if(jr_typ>=3){
      prtitab(1,fm_ou5,&stuknr,1,-1); prttitle(1,"Nr.",0x13);
      prtitab(2,fm_odat,&bk_dat,1,-1); prttitle(2,"Datum",0x43);
      prtitab(3,fm_os30,naam,1,18); prttitle(3,"Omschrijving",3);
      prtitab(4,fm_os8,rek_kod,1,8);prttitle(4,"Rekening",0x43);
      prtitab(5,fm_bdr,&bd_deb,1,-1); prttitle(5,"D-Bedrag",0x13);
      prtitab(6,fm_bdr,&bd_cre,4,-1); prttitle(6,"C-Bedrag",0x13);
      prtitab(7,fm_uu4,&ref_yy,1,-1);
      prtitab(8,fm_uu2,&ref_jr,1,-1);
      prtitab(9,fm_ou5,&ref_vl,1,-1);
      prtitab(10,fm_os30,opm,0,20); prttitle(10,"Opmerking",3);
    }
  }
  else prttext("");
  prtbuf(3);
  if(pdf_open==NO){
    
    if(mode1_) p_pdfname(j_tab[arr_jr].nm,dt_beg,dt_end);
    else  p_pdfname("Totaal journalen",dt_beg,dt_end);
    pdf_open=YES;
  }
}

static init_stk()
{
  bd_deb=0;bd_cre=0;
  zero((char *)bd_v,sizeof bd_v);
  zero((char *)bd_los,sizeof bd_los);
  zero(klnaam,sizeof klnaam);
  stuknr=*u(4,3);
  bk_dat=*u(4,4);
  loscnt=0;stk_r_poin=0;
  fin_1e=YES;
  zero(opm,sizeof opm); zero(mededeling,sizeof mededeling);
}

static add_bew()/* voeg 1 boeking toe in tabel of print16 1 financiele lijn */
{
  int16 col,k;

  if(analyt && ((*s(4,6) &0xF0)>>4)==9) goto endsr;
  makename();
  bedrag=*d(4,32);
  add_cj();
  if(stulk==3 && *u(3,8)) add_btw();
  if(jr_typ==1){
    col=*s(3,6)-'0';if(col<0 || col>9) col=0;
    if(stulk==1 && is_nul(bd_deb)){
      bd_deb=-bedrag;
      copy(s(4,27),mededeling,fldlen(4,27));
      copy(s(4,28),opm,fldlen(4,28));
      if(bit(sys1785,3) && *u(4,20)) bk_dat=*u(4,20);
    }
    else{
      if(col==0){
	if(!is_nul(bedrag)){/* lege EURO koersboekingen overslaan */
	  bd_los[loscnt]=bedrag;
	  copy(naam,nm_los[loscnt],20);
	  grb_los[loscnt]=*l(4,6);
	  loscnt++;
	}
      }
      else{
	bd_v[col]+=bedrag;
	if(stk_r_poin<STK_REC) stk_rec[stk_r_poin++]=val4_1();
      }
    }
  }
  if(jr_typ==2){
    col=*s(3,7)-'0';if(col<0 || col>9) col=0;
    if(stulk==2 && is_nul(bd_deb)){
      bd_deb=bedrag;
    }
    else{
      if(col==0){
	if(!is_nul(bedrag)){/* lege EURO koersboekingen overslaan */
	  bd_los[loscnt]=-bedrag;
	  copy(naam,nm_los[loscnt],20);
	  grb_los[loscnt]=*l(4,6);
	  loscnt++;
	}
      }
      else{
	bd_v[col]-=bedrag;
	if(stk_r_poin<STK_REC) stk_rec[stk_r_poin++]=val4_1();
      }
    }
  }
  if(jr_typ>2){
    if(is_nul(bedrag)) goto no_fin_det;/* lege EURO koersboekingen overslaan */
    if(bedrag<0) bd_cre=-bedrag;
    else bd_deb=bedrag;
    ref_yy=*s(4,8);ref_jr=*s(4,9);ref_vl=*u(4,10);
    if(ref_jr || ref_vl) ref_yy+=1900;/* y2000 */
    page_tst(3);
    if(fin_1e==YES){
      if(fin_yet_prt) jrnlline();
      else fin_yet_prt=YES;
      page_tst(6);
      for(k=1;k<3;k++) jrnlinfo(k,0);
    }
    for(k=3;k<5;k++) jrnlinfo(k,0);
    if(bedrag>=0){
      jrnlinfo(5,0);
      bdt_deb+=bd_deb;
    }
    else{
      jrnlinfo(6,0);
      bdt_cre+=bd_cre;
    }
    if(ref_jr || ref_vl)for(k=7;k<10;k++) jrnlinfo(k,0);
    zero(opm,sizeof opm); zero(mededeling,sizeof mededeling);
    if(mededeling[0]=='\0'){
      copy(s(4,27),mededeling,fldlen(4,27));
    }
    if(opm[0]=='\0'){
      copy(s(4,28),opm,fldlen(4,28));
    }
    jrnlinfo(10,0);zero(opm,sizeof opm);zero(mededeling,sizeof mededeling);
    jrnlline();
    if(j_tab[arr_jr].fingrb==*l(4,6)) fin_saldo+=bedrag;
    end_btw();
    fin_1e=NO;
    no_fin_det:;
  }
  endsr:;
}

static pr_finsal()
{
  if(sel_lst->jr){
    if(bit(sys1786,2)){
      prttitle(3,"   Saldo -->",0);
      if(fin_saldo<0) {bd_cre=-fin_saldo;prtinfo(6,2);}
      else {bd_deb=fin_saldo;prtinfo(5,2);}
      nextline();
    }
  }
}

static exit_jrn()
{
  jrnlline();
  pr_stot("*** Totaal journaal ***");
  prt_hdr(YES,NO);
  if(bit(sys1785,7)) prt_cj();
  if(bit(sys1785,5)) prt_btw(NO);/* van 1 journaal */
  if(jnl_used[arr_jr] && dt_beg==last_arc+1) j_tab[arr_jr].blz_n=prtpage(-1);
  if(*s(4,2)==255){
    nextpage();
    prtpage(1);
    prt_hdr(NO,NO);
    if(bit(sys1786,1)) prt_bladen();
    if(sel_lst->btw) prt_btw(YES);/* alle journalen samen */
    if(inv_poin) prt_invst();
  }
  nextpage();
}

static initload()
{
  int16 k,yy_,mm_,dd_,dum1,dum2;
  long lbtwpct;

  fasunlck(0);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  fileopen(1);
  fileopen(2);
  for(k=3;k<=5;k++) fileopen(k);
 
  dt_beg=*u(26,2);
  dt_end=*u(26,3);
  jr_beg=*u(26,4);volg_beg=*u(26,5);
  jr_end=*u(26,6);volg_end=*u(26,7);

  sysget(1008,16,&btwpct[0]);
  sysget(1785,1,&sys1785);
  sysget(1786,1,&sys1786);
  sysget(1858,2,&last_arc);
  sysget(1866,2,&mnd_strt);
 
  for(k=0;k<4;k++){
    lbtwpct=btwpct[k]*10;
    stcli_d(hdr_v[k],lbtwpct,3,1);
    hdr_v[k][3]=hdr_v[k][2];hdr_v[k][2]=',';
    hdr_v[k][4]=' ';hdr_v[k][5]='%';hdr_v[k][6]='\0';
  }
  for(k=0;k<80;k++){
    sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
    if(dt_beg==last_arc+1) j_tab[k].blz_n=j_tab[k].blz_o;
  }
  j_tab[80].nr=0;j_tab[80].typ=3;copy("???",&j_tab[80].nm[0],4);
  zero(jnl_used,sizeof jnl_used);
 

  getsysprNew(3,form_dat,&pr_mode,&prtnr);


  full_lst=YES; if(/*last_arc!=0 && */*u(26,2)!= last_arc+1) full_lst=NO;
  if(full_lst==NO){
    jddate(dt_beg,&yy_,&mm_,&dd_); yy_%=100;
    yy_%=100; if(mnd_strt>mm_) yy_--; if(yy_<0) yy_=99;/* jaar 2000 */
    dat_sbeg=datejd(yy_,mnd_strt,1);/* 1/1 van gevraagd boekjaar */
    if(dat_sbeg>(last_arc+1)){/* GEEN saldi tellen */
      period_1=1;
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
 
  copy(fm_ud8_2,fm_bdr,sizeof fm_ud8_2);
  copy(fm_ud82_,fm_vbdr,sizeof fm_ud82_);
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
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  }
  opened[nr_]=YES;
}

static ovl_exit(nr)
int16 nr;
{
  int16 k;

  if(sel_lst->jr){
    if(last_arc==0 || dt_beg==last_arc+1){
      for(k=0;k<80;k++) if(jnl_used[k]) sysput(10284+k*80,2,&j_tab[k].blz_n);
    }
    sysflush();
  }
  ovlexit(nr);
}

static pr_stuk()
{
  int16 k;
  page_tst(4);
  if(jr_typ==1){
		if(credt_allow==NO){
			for(k=1;k<=5;k++) jrnlinfo(k,0);
			jrnlinfo(11,0); 
			jrnlline();
			page_tst(3);
		}
		else{
			for(k=1;k<=7;k++) jrnlinfo(k,0);
			bdt_deb+=bd_deb;bdt_v[1]+=bd_v[1];bdt_v[9]+=bd_v[9];
			if(loscnt) losfill(0);
			jrnlinfo(11,0); zero(opm,sizeof opm);zero(mededeling,sizeof mededeling);
			jrnlline();
			for(k=1;k<loscnt;k++){
				losfill(k);
				jrnlline();
				page_tst(3);
			}
			if(bit(sys1785,1)) p_losdet();
		}
  }
  if(jr_typ==2){
    for(k=1;k<=10;k++) jrnlinfo(k,0);
    bdt_deb+=bd_deb;for(k=1;k<5;k++)bdt_v[k]+=bd_v[k]; bdt_v[9]+=bd_v[9];
    if(loscnt) losfill(0);
    jrnlline();
    for(k=1;k<loscnt;k++){
      losfill(k);
      jrnlline();
      page_tst(3);
    }
    if(bit(sys1785,2)) p_losdet();
  }
}

static page_tst(aantal)
int16 aantal;
{
  if(free<aantal){
    pr_stot("Overdracht");
    nextpage();
    pr_stot("Overdracht");
  }
}

static losfill(nr)
int16 nr;
{
  int16 k,offset;

  if(jr_typ==1) offset=8; else offset=11;
  bd_los_=bd_los[nr];
  bdt_los+=bd_los_;
  grb_los_=grb_los[nr];
  copy(nm_los[nr],omschr,20);
  for(k=0;k<3;k++) jrnlinfo(k+offset,0);
}

static pr_stot(ptxt)
char *ptxt;
{
  int16 k;
  double bdr_deb,bdr_cre,bdr_v[10],bdr_los;
  bdr_deb=bd_deb;bdr_cre=bd_cre;for(k=1;k<10;k++)bdr_v[k]=bd_v[k];
  bdr_los=bd_los_;
  bd_deb=bdt_deb;bd_cre=bdt_cre;for(k=1;k<10;k++)bd_v[k]=bdt_v[k];
  bd_los_=bdt_los;

  if(sel_lst->jr)prttitle(1,ptxt,0);
  if(jr_typ==1){
    for(k=5;k<9;k++)jrnlinfo(k,2);
  }
  if(jr_typ==2){
    for(k=5;k<12;k++)jrnlinfo(k,2);
  }
  if(jr_typ>2){
    jrnlinfo(5,2);jrnlinfo(6,2);
  }
  jrnlline();

  bd_deb=bdr_deb;bd_cre=bdr_cre;for(k=1;k<10;k++)bd_v[k]=bdr_v[k];
  bd_los_=bdr_los;
}

static makename()
{
  long long1;
  char ch_type;

  rekennr=*u(4,5);
  if(rekennr<30000){stulk=1;ch_type='L';}
  else if(rekennr<60000){stulk=2;rekennr=rekennr-30000;ch_type='K';}
  else {stulk=3;rekennr=rekennr-60000;ch_type='G';}
  long1=rekennr;
  if(!opened[stulk]) goto notfound;
  fasinit(stulk);
  *u(stulk,1)=rekennr;
  if(fasgeti(stulk)){
    notfound:;
    copy("???",naam,4);
    if(stulk<3)copy("???",klnaam,4);
    rek_kod[0]=ch_type;
    stcli_d(&rek_kod[1],long1,5,1);rek_kod[6]='\0';
    *s(3,6)='0';*s(3,7)='0';
    goto endsr;
  }
  copy(s(stulk,3),naam,30);
  if(stulk<3)copy(s(stulk,3),klnaam,30);
  if(stulk!=3) {*s(3,6)='0';*s(3,7)='0';}
  if(stulk==3)grb_deco(rek_kod,l(4,6));
  else{
    rek_kod[0]=ch_type;
    if((stulk==1 && lvcd) || (stulk==2 && klcd)){
      rek_kod[1]=' ';
      copy(s(stulk,2),&rek_kod[2],6);
      if(fldlen(stulk,2)<6) rek_kod[2+fldlen(stulk,2)]='\0';
    }
    else{
      stcli_d(&rek_kod[1],long1,5,1);
      rek_kod[6]='\0';
    }
  }
  endsr:;
}

static bit(byte_,bit_)
char byte_;
int16 bit_;
{
  if(byte_ & 1<<bit_) return YES;
  return NO;
}
 
static p_losdet()/* print16 detail van rekeningen in kolommen 1 - 9 */
{
  int16 j,k,offset;
  char buf400_[400];

  if(sel_lst->jr){
    if(stk_r_poin){
      copy(s(4,1),buf400_,fldlen(4,0));
      if(jr_typ==1) offset=8; else offset=11;
      page_tst(4);
      copy("--- detail ---",omschr,15);jrnlinfo(offset+2,0);jrnlline();
      for(j=0;j<stk_r_poin;j++){
	chg4_1(stk_rec[j]);fasgeti(4);
	bd_los_=*d(4,32);
	if(jr_typ==2) bd_los_=-bd_los_;
	*u(3,1)=*u(4,5)-60000;fasgeti(3);
	grb_los_=*l(3,2);
	copy(s(3,3),omschr,20);
	for(k=0;k<3;k++) jrnlinfo(k+offset,0);
	jrnlline();
	page_tst(3);
      }
      copy(buf400_,s(4,1),fldlen(4,0));
    }
    for(k=0;k<131;k++) prttext("-");jrnlline();
  }
}
 
static add_cj()
{
  int16 j,k;
  long grb_;
  flag add=NO;

  if(is_nul(bedrag)) goto no_cj_add;/* lege EURO koersboekingen overslaan */
  grb_=*l(4,6);
  for(k=0;k<cj_poin;k++){
    if(grb_==cj_grb[k]) break;
    if(cmp_grb(&grb_,&cj_grb[k])){
      for(j=cj_poin;j>k;j--){
	cj_grb[j]=cj_grb[j-1];
	cj_deb[j]=cj_deb[j-1];
	cj_cre[j]=cj_cre[j-1];
      }
      add=YES;break;
    }
  }
  if(k==cj_poin || add){
    cj_grb[k]=grb_;
    cj_deb[k]=0;cj_cre[k]=0;
    if(cj_poin<QCJ-2) cj_poin++;
  }
  if(bedrag<0) {cj_cre[k]-=bedrag;cjt_cre-=bedrag;}
  else {cj_deb[k]+=bedrag;cjt_deb+=bedrag;}
  no_cj_add:;
}

static cmp_grb(p1,p2)
char *p1,*p2;
{
  int16 k;
  for(k=0;k<4;k++){
    if(*p1<*p2) return YES;
    else if(*p1!=*p2) break;
    p1++;p2++;
  }
  return NO;
}

static add_btw()
{
  int16 vak_;
  double bd_;

  if(*u(3,8)>100) *u(3,8)=81;
  vak_=*u(3,8)%100;
  if(vak_==0) goto endsr;
  bd_=bedrag;
  if(vak_==59 || vak_>80) bd_=-bd_;
  btw_bdft[vak_]-=bd_;

  if(jr_typ==1){
    if(vak_==86) v86_used=YES;            /* markering intrastat-creditnota */
    if(vak_==87) v87_used=YES;            /* markering medecontr-creditnota */
  }
  if(bit(sys1785,4)){
    if(vak_==83 && jr_typ<3 && inv_poin<(QINV-1)) inv_rec[inv_poin++]=val4_1();
  }
  endsr:;
}
 
static end_btw()
{/* btw_bdft bevat btw tabel van deze factuur of financiele lijn */
  int16 k;/* overboeken naar btw_bdjr en btw_bdt*/
  double bd_=0,bd818283;

  btw_bdft[0]+=btw_bdft[9];btw_bdft[9]=0;
  for(k=0;k<100;k++) bd_+=btw_bdft[k];
  bd818283=btw_bdft[81]+btw_bdft[82]+btw_bdft[83];
  if(bd_<0 && jr_typ<=2){
/* creditnota verkopen */
    btw_bdft[48]-=btw_bdft[46];btw_bdft[46]=0;
    for(k=0;k<=8;k++) {btw_bdft[49]-=btw_bdft[k];btw_bdft[k]=0;}
    btw_bdft[49]-=btw_bdft[45];btw_bdft[45]=0;
    btw_bdft[49]-=btw_bdft[47];btw_bdft[47]=0;
    btw_bdft[64]-=btw_bdft[54];btw_bdft[54]=0;
    btw_bdft[64]-=btw_bdft[58];btw_bdft[58]=0;
/* creditnota aankopen */
    if(!is_nul(btw_bdft[86]) || v86_used) btw_bdft[84]-=bd818283;
    else btw_bdft[85]-=bd818283;
    btw_bdft[63]-=btw_bdft[59];btw_bdft[59]=0;
  }
  if(!is_nul(btw_bdft[86]) || v86_used){
    btw_bdft[55]-=btw_bdft[86];
    btw_bdft[86]=bd818283;
  }
  if(!is_nul(btw_bdft[87]) || v87_used){
    btw_bdft[56]-=btw_bdft[87];
    btw_bdft[87]=bd818283;
  }
  if(!is_nul(btw_bdft[88])){
    btw_bdft[56]-=btw_bdft[88];
    btw_bdft[88]=bd818283;
  }
  for(k=0;k<100;k++){btw_bdjr[k]+=btw_bdft[k];btw_bdt[k]+=btw_bdft[k];}
  zero((char *)btw_bdft,sizeof btw_bdft);v86_used=NO; v87_used=NO;
}

static prt_cj()
{
  int16 k;
  double cj_deb_t=0,cj_cre_t=0;

  if(bit(sys1786,0)) nextpage(); else nextline();
  if(free<9) nextpage();
  prttext("<be><t15>Centralisatie<be>");nextline();nextline();
  prttext("<bu>Omschrijving<t23>Rekening<t42>Debet<t57>Credit<bu>");nextline();
  nextline();
  for(k=0;k<cj_poin;k++){
    fasinit(3);*l(3,2)=cj_grb[k];faskeyi(3,1,0);
    prtfld(3,3,-1);prtblank(2);
    prtfld(3,2,-1);
    prt_cj_bd("",cj_deb[k],cj_cre[k]);
    cj_deb_t+=cj_deb[k];cj_cre_t+=cj_cre[k];
  }
  nextline();
  prt_cj_bd("<b>Totaal journaal<b>",cj_deb_t,cj_cre_t);
  if(*s(4,2)==255){
    nextline();
    prt_cj_bd("<b>Algemeen totaal ==><b>",cjt_deb,cjt_cre);
  }
}

static prt_cj_bd(ptxt,bd_d,bd_c)
char *ptxt;
double bd_d,bd_c;
{
  prttext("<t13>");prttext(ptxt);
  prttext("<t34>");
  prtifld(fm_bdr,&bd_d,-1);prtblank(3);
  prtifld(fm_bdr,&bd_c,-1);nextline();
}
 
static prt_btw(mode_)
flag mode_;
{
  int16 k;

  if(mode_) for(k=0;k<100;k++) btw_bdjr[k]=btw_bdt[k];
  if(btw_bdjr[61]<0) btw_bdjr[61]=-btw_bdjr[61];
  if(btw_bdjr[62]<0) btw_bdjr[62]=-btw_bdjr[62];
  btw_bdjr[71]=btw_bdjr[54]+btw_bdjr[55]+btw_bdjr[56]+btw_bdjr[57]+
    btw_bdjr[58]+btw_bdjr[61]+btw_bdjr[63];
  btw_bdjr[72]=btw_bdjr[59]+btw_bdjr[62]+btw_bdjr[64];
  btw_bdjr[71]-=btw_bdjr[72];
  if(btw_bdjr[71]<0){btw_bdjr[72]=-btw_bdjr[71];btw_bdjr[71]=0;}
  else btw_bdjr[72]=0;
  if(bit(sys1786,0)) nextpage(); else nextline();
  if(free<9) nextpage();
  prttext("<be><t10>B.T.W.-Aangifte<be>");nextline();nextline();

  for(k=0;k<100;k++){
    if(!is_nul(btw_bdjr[k])){
      prttext("<t10>Vak ");prtifld(fm_uu2_,&k,-1);
      prttext("<t20>");prtifld(fm_bdr,&btw_bdjr[k],-1);
      nextline();
    }
  }
  endsr:;
}

static prt_invst()
{
  int16 j,k,key_mode;
  uint16 dt_;

  nextline();nextline();
  prttext("<be><t20>Detail Investeringen<be>");nextline();nextline();
  prttext("<b>Jn Volgn.  Datum<t26>Bedrag  Rekening Omschrijving");
  prttext("<t65>Leverancier<t97>Opmerking<b>");nextline();nextline();
  for(k=0;k<inv_poin;k++){
    chg4_1(inv_rec[k]);fasgeti(4);
    *u(3,1)=*u(4,5)-60000;fasgeti(3);
    dt_=*u(4,4);
    chg4_1(0L);
    fasinit(1);key_mode=1;
    FOREVER{
      if(faskeyi(4,1,key_mode))break;
      key_mode=2;
      if(*u(4,5)<30000 && *u(4,4)==dt_){
	*u(1,1)=*u(4,5);fasgeti(1);
	break;
      }
    }
    chg4_1(inv_rec[k]);fasgeti(4);
    j=*s(4,2);prtifld(fm_uu2,&j,-1);prtblank(1);
    prtfld(4,3,-1);prtblank(2);
    prtfld(4,4,-1);prtblank(2);
    prtfld(4,32,-1); prtblank(2);
    prtfld(3,2,-1);prtblank(1);
    prtfld(3,3,-1);prtblank(2);
    prtfld(1,3,30);prtblank(2);
    prtfld(4,28,-1);
    punt25:;
    nextline();
  }
}
 
static prt_bladen()
{
  int16 j,k;

  prttext("<be>Gebruikte bladen<be>");nextline();nextline();
  prttext("<b>Jn   Omschrijving<t30>Aantal blz.<b>");
  nextline();nextline();
  for(k=0;k<80;k++){
    if(j_tab[k].nm[0]){
      prtifld(fm_uu2,&j_tab[k].nr,-1);prtblank(3);
      prttext(j_tab[k].nm);prttext("<t32>");
      j=j_tab[k].blz_n-j_tab[k].blz_o;
      if(j){
	prtifld(fm_uu3,&j,-1);
	prttext("  (");j=j_tab[k].blz_o+1;prtifld(fm_uu3,&j,-1);
	prttext(" -");prtifld(fm_uu3,&j_tab[k].blz_n,-1);prttext(")");
      }
      nextline();
    }
  }
}

static nextpage()
{
  prtform(0);
  free=999;
}

static nextline()
{
  free=prtline();
}
 
static jrnlline()
{
  if(sel_lst->jr) nextline();
}
 
static jrnlinfo(par1,par2)
int16 par1,par2;
{
  if(sel_lst->jr) prtinfo(par1,par2);
}
 
static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}
