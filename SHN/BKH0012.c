/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0012GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0012dat
#define ovlcod BKH0012cod
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

char ovldat[] = "bkh0012  00:63 05/08/10 (c) Jamadata";
 // FLAGOPS : automatisch saldo + enkel zoeken in NIETvoldane facturen 
 // FLAGVDW : automatisch saldo bij kas (type 4)
 // FLAGVNT : automatisch saldo bij kas (type 4)
 // FLAGEBO : automatisch saldo bij kas (type 4)
 // FLAGSU2 : F10 zoek, enkel laatste 6 maanden overlopen om blokkage te vermijden owv te hoge trafiek
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAX_CNIV        5
#define MAXLEN          30
#define OPMLEN          20
#define MAX_TB_EL       5000
#define MINFREE         200
#define DIM_OFIN        1000
#define DIM_OPEN        1000
#define DIMAT           185
#define DIMA            10
#define DIMZOEK         15
#define MAXFLD          120
#define SEARBFLEN       50
#define flag            uint16

// journaaltype : 1=AK-journaal, 2=VK-journaal, 3=Fin.journaal, 4=fin.journaal met dagnummer 
// journaaltype : 5=div-journaal, 6=div-journaal met dagnummer, 7=overschrijving 
// journaaltype : 8=Openingsbalans, 9/10 = 3/4 met rekeninguittreksel 



static struct {
  uint16 nr;
  uint16 typ;
/* geen naam */
  uint16 lastnr;
  long fingrb;
  long saldo;
  double saldo_vm;
  char munt[4];
  char mast_munt;
  double e_saldo;
/* niet uit sys.fas : */
  uint16 recnr;/* extra element */
} j_tab[80];

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l(),val();
extern float *f();
extern double *d(), valu_cnv();
static double absdoubl(),get_finsaldo();
static uint16 getgrb();
static flag zk_combi();
static flag yet_booked();

static long ZoekFactuur(char *pnaam_,uint16 ft_nummer_,double bedrag_);  // zoek AK/VK factuur ahv nummer of bedrag

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os27[]  = {7,0x88,27,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os16[]  = {7,0x88,16,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou2_[]  = {6,0x90,2,0,0x00,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us18[]  = {7,0xC8,18,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_ol9[]   = {6,0x93,9,0,0x70,0};
static char fm_od92_[] = {6,0x95,9,2,0x60,0};
static char fm_od9_2[] = {6,0x95,9,2,0x70,0};
static char fm_od9_0[] = {6,0x95,9,0,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};
static char fm_uf3_4[] = {6,0xD4,3,4,0x70,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_of2_1[] = {6,0x94,2,1,0x30,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uLKG[]  = {11,0xC8,1,0,0x09,0,'K','L','G','G',0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_uXb[]   = {11,0xC8,1,0,1,0,'X','X',' ',' ',0};

static struct _tb12 {
  char begin;
  uint16 rec_nr;
  long recft;
  long grb_tb;
  double bedrag;
  char opm_bkh[OPMLEN];
  uint16 vl_tb;
  char jr_tb;
  char yy_tb;
	long GRBwacht;
	long GRBoverb;
  uint16 procid;
	uint16 ori_volgnr;
} tb[5000];

static struct _tba {
  char begin;
  double a_bedrag;
  uint16 a_rec_nr;
  long a_elem;
  long a_grbrek;
	uint16 ori_volgnr;
} tba[DIMAT+DIMA];

static struct{
  long rec;
  double bedrag;
} open_recs[DIM_OPEN];
 
static struct{
	long rec4;
	char fullmatch;
} TbZoekFactuur[200];


static long tb_ofin[DIM_OFIN],zk_rec[20];
static uint16 ofi_jn,ofi_nr,ofi_dt;
static uint16 last_arc,MinBkhDatum,ref_ft,jaartal,mnd_strt;
static uint16 df_recnr[15],rec_d_ak, rec_d_vk,rec_d_fi;
static long kltcent,levcent,df_grb[15],grb_d_ak, grb_d_vk,grb_d_fi;

static flag lvcd,klcd,debit_allow=NO,credt_allow=NO,sear_stt,halve_bkg,upd_mode;
static int16 journl,jtb_,scrcount,notfound=0,mcnt,stutyp,ref_jr,ref_yy,DefAkJournaal, DefVkJournaal,PandJournaal;
static int16 sysdiff=0,chk_btoeg=1,len4_0,max_orec,combi_nr[MAX_CNIV+1];
static uint16 searcnr,subnrt;
static long afw_long,tb_grbnotfound[50];
static char munt[4],lkg,lkglet[3]={'L','K','G'};
static char opmer[OPMLEN],def_munt[4],valtype;
static char lkgkod[9],lkgnaam[51],bf[250];
static char gnm_diff[6][20],buff7[7][21],buff7res[7][21],buff1000[1000];
static uint16 def_qfak,vers_298,bkh_dt,volgnr,rec_kdif;
static uint16 oft_dt,oft_jn,oft_nr;
static char taal_i,talen[4],benam[16];
static char searbuf[SEARBFLEN+1];
static flag sys1818,sys1840,sys1850,sys1862,sys3876,analyt,zoek_op_bd;
static uint16 zoekscr[DIMZOEK],pzoekscr;
static int16 ny;
static float anal_pct[DIMA],btwpct[4];
static char anal_nm[DIMA][MAXLEN],anal_onm[DIMA][MAXLEN],anal_ask;
static float valu_val,valu_res;
static double bd_tot,bd_inp;
static double b_auto_sal;
static flag  auto_sal;
static double *pd_4_32;

ovlcod()
{
  int16 g,k,key,swit;
  char dmunt_[6];

  initload();
  FOREVER{/* maak gesorteerde tabel journaalnummers */
    for(k=0;k<80;k++) tb[k].rec_nr=100;
    g=0;for(k=0;k<80;k++) if(j_tab[k].nr && j_tab[k].typ>2 && j_tab[k].typ!=7 && j_tab[k].typ!=8) tb[g++].rec_nr=k;
    if(g>1){
      FOREVER{
	swit=NO;
	for(k=0;k<g-1;k++){
	  if(j_tab[tb[k].rec_nr].nr>j_tab[tb[k+1].rec_nr].nr){
	    key=tb[k].rec_nr;
	    tb[k].rec_nr=tb[k+1].rec_nr;
	    tb[k+1].rec_nr=key;
	    swit=YES;
	  }
	}
	if(swit==NO) break;
      }
    }
 
    swit=0;
    redo:
    scrget(1,25);
    for(k=0;k<20;k++){
      for(g=0;g<2;g++){
	if(tb[k+g*20].rec_nr<100){
	  scrifld(1+k*6+g*3,fm_ou2,&j_tab[tb[k+g*20].rec_nr].nr);
	  sysget(10240+4+tb[k+g*20].rec_nr*80,16,benam);
	  scrifld(2+k*6+g*3,fm_os16,benam);
	  zero(dmunt_,sizeof dmunt_);dmunt_[0]='(';
	  if(fldlen(4,15) && j_tab[tb[k+g*20].rec_nr].munt[0]) copy(j_tab[tb[k+g*20].rec_nr].munt,&dmunt_[1],3);
	  else if(j_tab[tb[k+g*20].rec_nr].mast_munt=='E') copy("EUR",&dmunt_[1],3);
	  else copy(def_munt,&dmunt_[1],3);
	  dmunt_[4]=')';
	  scrifld(3+k*6+g*3,fm_os5,dmunt_);
	}
      }
    }
    scrifld(121,fm_uu2,&swit);
    key=scrupd(1,0x3A1);
    if(key==101) ovlexit(-1);
    upd_mode=NO;
    if(key==110){
      if(ovltest(32)) {ovlexit(32);}
      else {errnum=12; goto redo;}
    }
    else if(key==109){
      upd_mode=YES;
      upd_fin();
    }
    else{
      for(jtb_=0;jtb_<80;jtb_++) if(swit==j_tab[jtb_].nr) break;
      if(swit==0 || jtb_==80) {errnum=34;goto redo;}
      sysget(10240+4+jtb_*80,16,benam);
      sysget(10240+20+jtb_*80,2,&j_tab[jtb_].lastnr);/* last minute */
      sysget(10240+26+jtb_*80,4,&j_tab[jtb_].saldo);
      sysget(10240+30+jtb_*80,8,&j_tab[jtb_].saldo_vm);
      sysget(10286+jtb_*80,1,&j_tab[jtb_].mast_munt);
      sysget(10287+jtb_*80,8,&j_tab[jtb_].e_saldo);
      financ1();
    }
  }
}

static financ1()
{
  int16 curs,g,j,k,key,aard,z,d_bk_sal_;
  double sal_n,sal_o,bkh_sal_;
  int16 yy_,mm_,dd_,mode_;
  uint16 dat_1_1;

  aard=j_tab[jtb_].typ;fasunlck(-1); upd_mode=NO;
  copy(j_tab[jtb_].munt,munt,4);if(fldlen(4,15)==0) munt[0]='\0';
  valtype='E';
  if(munt[0]=='\0'){
    if(j_tab[jtb_].mast_munt=='E'){copy("EUR",munt,3);valtype='E';}
    else copy(def_munt,munt,3);
  } else valtype='V';
  bkh_dt=*u(25,2);d_bk_sal_=NO;
  FOREVER{
    if(CheckForFreeSpace(4,MINFREE)) goto endsr;/* onvoldoende vrije records */
    for(k=0;k<MAX_TB_EL;k++) tb[k].bedrag=0;
    volgnr=j_tab[jtb_].lastnr+1;
    sal_o=0;sal_n=0;bd_tot=0;d_bk_sal_=NO;
    if(aard==3 || aard==4 || aard==9 || aard==10){
      if(valtype=='V') sal_o=j_tab[jtb_].saldo_vm; else sal_o=j_tab[jtb_].e_saldo;
    }
    curs=2;
    redo:
    scrget(1,26);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_ou2,&j_tab[jtb_].nr);
    scrifld(z++,fm_os16,benam);
    if(aard==4 || aard==6 || aard==8 || aard==10) scrifld(z++,fm_os5,"*****");
    else scrifld(z++,fm_uu5,&volgnr);
    scrifld(z++,fm_udat,&bkh_dt);
    if(aard==3 || aard==4 || aard==9 || aard==10) {
      if(d_bk_sal_) scrifld(z++,fm_od9_2,&bkh_sal_);
      else scrifld(z++,fm_os5,"*****");
      scrxfld(&z,YES,&sal_o,YES);
      scrxfld(&z,YES,&sal_n,YES);
      scrxfld(&z,YES,&bd_tot,YES);
    }
    else{
      scrifld(z++,fm_os5,"*****");
      for(k=7;k<13;k+=2) scrifld(k,fm_os5,"*****");
    }
    key=scrupd(curs,0x04C1);curs=2;
    if(key==101 || key==106) goto endsr;
    if(key==111) ovlexit(-1);
    if(key==107 && (aard==3 || aard==4 || aard==9 || aard==10)) {
      bkh_sal_=get_finsaldo(j_tab[jtb_].fingrb,bkh_dt);
      d_bk_sal_=YES;
    }
 
    journl=j_tab[jtb_].nr;
    if(last_arc){/* check datum */
      if(bkh_dt<=last_arc) errnum=37;
 //     if((sys1862 & 8)==0) if(bkh_dt>last_arc+600) errnum=61;
      if(errnum){curs=4;goto redo;}
    }
		if(MinBkhDatum){/* check datum */
      if(bkh_dt<=MinBkhDatum) errnum=37;
      if(bkh_dt>(*u(25,2)+10) || bkh_dt>(MinBkhDatum+600)) errnum=61;
      if(errnum) {curs=4;goto redo;}
    }
    if(aard==4 || aard==6 || aard==8 || aard==10){ // volgnummer omgekeerde datum maken
      jddate(bkh_dt,&j,&g,&k);
      volgnr=g*100+k;

			scrget(1,7);scrupd(-3,0);
			jddate(bkh_dt,&yy_,&mm_,&dd_); yy_%=100;
			yy_%=100; if(mnd_strt>mm_) yy_--; if(yy_<0) yy_=99;/* jaar 2000 */
			dat_1_1=datejd(yy_,mnd_strt,1);/* 1/1 van gevraagd boekjaar */
			fasinit(4);	*s(4,2)=journl;	*u(4,3)=volgnr;
			mode_=1;
			FOREVER{
				if(faskeyu(4,1,mode_)) break; mode_=2;
				if(*s(4,2)!=journl || *u(4,3)!=volgnr) break;
				if(*u(4,4)>=dat_1_1 && *u(4,4)!=bkh_dt){ volgnr=volgnr*10+9;break;} // al gebruikt op andere datum
			}
		}
    if(volgnr==0){curs=4; errnum=38;goto redo;}
		if(aard==5 && yet_booked(journl,volgnr,bkh_dt)){errnum=59;curs=4;goto redo;}
    if(sal_n && bd_tot){errnum=72;curs=8;goto redo;}
    if(key==107) goto redo;
#if FLAGOPS | FLAGVDW  | FLAGVNT | FLAGEBO
		/*  if(bd_tot==0) bd_tot=sal_n-sal_o; else sal_n=sal_o+bd_tot; */
#if FLAGVDW  | FLAGVNT
   if(sal_n || bd_tot || aard!=4){ // enkel autosaldo bij kas
#else
    if(sal_n || bd_tot){/* specifiek */
#endif
      if(bd_tot==0) bd_tot=sal_n-sal_o; else sal_n=sal_o+bd_tot;
      auto_sal=NO;
    } else auto_sal=YES;
    b_auto_sal=0;
#else
    if(bd_tot==0) bd_tot=sal_n-sal_o; else sal_n=sal_o+bd_tot;
#endif
    zero((char *)&tba[0].begin,sizeof tba);

    for(k=0;k<MAX_TB_EL;k++) tb[k].recft=0;
    if(fin_det()){
			if(auto_sal) sal_n=sal_o+b_auto_sal;
      j_tab[jtb_].lastnr=volgnr;
      if((aard<3 || aard>4) && (aard<9 || aard>10)) sal_n=0;
      if(valtype=='V'){
				if(j_tab[jtb_].mast_munt=='E'){
					j_tab[jtb_].e_saldo=valu_cnv(munt,"EUR",sal_n,(double).01);
				}
				else{
					j_tab[jtb_].e_saldo=valu_cnv(munt,def_munt,sal_n,(double)1.);
				}
				j_tab[jtb_].saldo_vm=sal_n;
      }
      else j_tab[jtb_].e_saldo=sal_n;
      sysput(10240+20+jtb_*80,2,&j_tab[jtb_].lastnr);
      sysput(10240+26+jtb_*80,4,&j_tab[jtb_].saldo);
      sysput(10240+30+jtb_*80,8,&j_tab[jtb_].saldo_vm);
      sysput(10287+jtb_*80,8,&j_tab[jtb_].e_saldo);
      sysflush();
    }
  }
  endsr:;
}

static flag yet_booked(jrnl_,volgnr_,dt_)
int16 jrnl_;
uint16 volgnr_,dt_;
{
  int16 fkey_,jj,mm,dum;
  uint16 dt_beg,dt_end;

  if(sys1862 & 0x10) return NO;
  jddate(dt_,&jj,&mm,&dum);
  FOREVER{
    dt_end=datejd(++jj,mnd_strt,1);
    dt_beg=datejd(--jj,mnd_strt,1);
    if(dt_>=dt_beg) break;
    jj--;
  }
  fasinit(4);*s(4,2)=jrnl_;*u(4,3)=volgnr_;fkey_=1;
  FOREVER{
    next:;
    if(faskeyi(4,1,fkey_)) break;fkey_=2;
    if(*s(4,2)!=jrnl_ || *u(4,3)!=volgnr_) break;
    if(upd_mode){/* originele boeking overslaan */
      if(*s(4,2)==oft_jn && *u(4,3)==oft_nr && *u(4,4)==oft_dt) goto next;
    }
 
    if(*u(4,4)>=dt_beg && *u(4,4)<dt_end) return YES;
  }
  return NO;
}


static upd_fin()
{
  int16 curs=1,key,z,mm,dd;
					
  fasunlck(-1);
	jddate(*u(25,2),&jaartal,&mm,&dd);
  bkh_dt=0;volgnr=0;journl=0;
					
  FOREVER{
    redo:;
    scrnum=0;scrget(1,242); z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_uu2,&journl);
    scrifld(z++,fm_uu5,&volgnr);
    scrifld(z++,fm_udat,&bkh_dt);
    scrifld(z++,fm_uu4,&jaartal);
    key=scrupd(curs,0x281); curs=2;
    if(key==101) break;
    if(journl==0){curs=2; errnum=38; goto redo;}
    for(jtb_=0;jtb_<80;jtb_++){
      if(j_tab[jtb_].typ>2 && j_tab[jtb_].typ!=8 && j_tab[jtb_].nr==journl) break;
    }
    if(jtb_==80){curs=2;errnum=34;goto redo;}
    if(volgnr==0 && key!=110) {curs=3;errnum=38;goto redo;}
    copy(j_tab[jtb_].munt,munt,4);if(fldlen(4,15)==0) munt[0]='\0';
    valtype='E';
    if(munt[0]=='\0'){
      if(j_tab[jtb_].mast_munt=='E'){copy("EUR",munt,3);valtype='E';}
      else copy(def_munt,munt,3);
    } else valtype='V';
    if(load_fin()) goto redo;
		oft_dt=bkh_dt; oft_jn=journl;oft_nr=volgnr;upd_mode=YES;
    fin_det();
    volgnr=0;bkh_dt=0;journl=0;
  }
  endsr:;
}
 
static load_fin()
{
  int16 g,j,k,mm,dd,mode_,jaari,pfi_;
  flag det_used_;

  for(k=0;k<MAX_TB_EL;k++) zero((char *)&tb[k].begin,sizeof tb[0]);
  if(CheckForFreeSpace(4,MINFREE)) return YES;/* onvoldoende vrije records */
  det_used_=NO;mcnt=0;bd_tot=0;
  copy(def_munt,munt,4);
  zero((char *)&tba[0].begin,sizeof tba);
  zero((char *)&tb_ofin[0],sizeof tb_ofin); pfi_=0;
  fasinit(4);*s(4,2)=journl;*u(4,3)=volgnr; mode_=1;
  FOREVER{
    next4:;
    if(faskeyi(4,1,mode_)) break; mode_=2;
    if(*s(4,2)!=journl || *u(4,3)!=volgnr) break;
    if(pfi_>=DIM_OFIN) {errnum=63;return YES;}
    if(bkh_dt==0){
      jddate(*u(4,4),&jaari,&mm,&dd);
      if(jaari!=jaartal) goto next4;
      if(*u(4,4)<=last_arc){errnum=37;goto next4;}
			if(*u(4,4)<=MinBkhDatum){errnum=37;goto next4;}
      bkh_dt=*u(4,4);
    }
    else if(bkh_dt!=*u(4,4)) goto next4;
    det_used_=YES;

    if(analyt){
      *l(3,2)=*l(4,6);
      if(g_anal_tst()){
				for(g=0;g<DIMAT;g++) if(is_nul(tba[g].a_bedrag)) break;
				if(g>=DIMAT){errnum=63;return YES;}
				tba[g].a_rec_nr=*u(4,5);
				tba[g].a_grbrek=*l(4,6);
				tba[g].a_bedrag=-*pd_4_32;
				tba[g].a_elem=*l(4,11);/* tijdelijk grb inzetten */
				if(fldlen(4,23)) tba[g].ori_volgnr=*u(4,23);
				tb_ofin[pfi_++]=*l(4,1);
				goto next4;
      }
    }
    if(mcnt>=MAX_TB_EL){errnum=63; return YES;}
    tb[mcnt].rec_nr=*u(4,5);
    tb[mcnt].grb_tb=*l(4,6);
    tb[mcnt].bedrag=-*pd_4_32;bd_tot+=tb[mcnt].bedrag;
    tb[mcnt].yy_tb=*s(4,8);
    tb[mcnt].jr_tb=*s(4,9);
    tb[mcnt].vl_tb=*u(4,10);
		if(fldlen(4,23)) tb[mcnt].ori_volgnr=*u(4,23);
    copy(s(4,28),tb[mcnt].opm_bkh,OPMLEN);
		if(fldlen(4,60)) tb[mcnt].procid=*u(4,60);
    tb_ofin[pfi_++]=*l(4,1);
    mcnt++;
  }
  if(analyt){
    for(k=0;k<DIMAT;k++){/* verwijzing juiszetten */
      if(tba[k].a_rec_nr==0) break;
			for(g=0;g<mcnt;g++) if(tba[k].ori_volgnr==tb[g].ori_volgnr && tba[k].a_elem==tb[g].grb_tb) break; // eerst proberen op volgnr
			if(g>=mcnt){ // dan op rekening alleen
        for(g=0;g<mcnt;g++) if(tba[k].a_elem==tb[g].grb_tb) break;
			}
			if(g>=mcnt){ // foute verwijzing schrappen
				for(j=k+1;j<DIMAT;j++){
					copy((char *)&tba[j].begin,(char *)&tba[j-1].begin,sizeof tba[0]);
				}
				zero((char *)&tba[DIMAT-1].begin,sizeof tba[0]);
			}
			else tba[k].a_elem=g;
    }
  }
  ofi_dt=bkh_dt; ofi_jn=journl;ofi_nr=volgnr;
  if(det_used_) return NO;
  else {errnum=39;return YES;}
}

static fin_det()
{
  int16 h,key,curs=10,k,n,z,ztot_,dcnt,stu_dsp_,z_base,aard,nm_chgd_;
  uint16 rec__,last_r_,rec_dsp_;
  double bd_,bd_yetdiv=0;
  char dum[2],dsp_buf_[21],*fmt_;

  if(upd_mode==NO){
    mcnt=0;valu_res=valu_val;
    if((j_tab[jtb_].typ<5 || j_tab[jtb_].typ>8) && bd_tot){
      tb[0].bedrag=-bd_tot;
      tb[0].grb_tb=j_tab[jtb_].fingrb;
      tb[0].rec_nr=j_tab[jtb_].recnr;
      *u(3,1)=tb[0].rec_nr-60000;
      fasgeti(3);
      copy(s(3,3),buff7[6],20);buff7[6][20]='\0';
      tb[0].yy_tb=0;tb[0].jr_tb=0;tb[0].vl_tb=0;
      zeros(tb[0].opm_bkh,sizeof tb[0].opm_bkh);
      mcnt++;
    }
  }
  else{
    dcnt=0;
  }
	aard=j_tab[jtb_].typ;
  lkg=lkglet[debit_allow];
  errnum=0;
  FOREVER{
    if(!errnum){
      redo_0:
      fasinit(1);fasinit(3);
      jddate(bkh_dt,&ref_yy,(int16 *)&dum[0],(int16 *)&dum[0]);ref_yy=ref_yy%100;
      ref_jr=0;ref_ft=0;bd_inp=0;subnrt=0; last_r_=0;
      zeros(opmer,sizeof opmer);
      zeros(lkgkod,sizeof lkgkod);
      zeros(lkgnaam,sizeof lkgnaam);
      valu_val=valu_res; dcnt=mcnt;
    }
    anal_ask='\0';
    for(ny=DIMAT-1;ny>=0;ny--) if(tba[ny].a_rec_nr) break;
    ny++;
    redo:
    scrnum=0;scrget(1,27); z=1;
		scraddpicto(2,0,75,20,4,2,112,0,4,"Doorzoek alles"); 
    scrfld(z++,25,1);
    scrxfld(&z,NO,&bd_tot,YES);
    scrifld(z++,fm_ou2,&journl);
    scrxfld(&z,NO,&bd_yetdiv,YES);
    if(upd_mode || errnum==59) scrifld(z++,fm_uu5,&volgnr);
    else scrifld(z++,fm_ou5,&volgnr);
    bd_=bd_tot-bd_yetdiv;scrxfld(&z,NO,&bd_,YES);
    if(upd_mode) scrifld(z++,fm_udat,&bkh_dt);
    else scrifld(z++,fm_odat,&bkh_dt);
    z=81; z_base=z;
    scrxfld(&z,YES,&bd_inp,YES);
    z+=3;
    scrifld(z++,fm_uLKG,&lkg);
    scrifld(z++,fm_os8,lkgkod);
    scrifld(z++,fm_us30,lkgnaam);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_us20,opmer);
    if(analyt){
			// scrifld(z++,fm_uJN,&anal_ask);
			k=3; if(anal_ask=='X') k=4;
			scraddpicto(10,z-1,4,0,2,1,130,0,k,"Analytische uitsplitsing"); 
			z++;
		}
    else{
      z++;
/*    if(fldlen(4,19)) scrifld(z++,fm_uu2,&subnrt);*/
/*    else z++;*/
    }
    scrifld(z++,fm_uu5,&ref_ft);
    scrifld(z++,fm_uu2,&ref_jr);
    ref_yy=ref_yy%100; scrifld(z++,fm_uu2_,&ref_yy);ztot_=z;
    for(k=dcnt-7;k<dcnt;k++){/* display vorige boekingen */
      if(k>=0){
				n=7-(dcnt-k);
				k++;scrifld(11+n*10,fm_ou3,&k);k--;
				z=12+n*10;
				scrxfld(&z,NO,&tb[k].bedrag,NO);
				stu_dsp_=0; rec_dsp_=0;
				if(tb[k].rec_nr>60000){
					stu_dsp_=3;rec_dsp_=tb[k].rec_nr-60000;
				}
				else{
					if(tb[k].rec_nr<30001){
						stu_dsp_=1;rec_dsp_=tb[k].rec_nr;
					}
					else{
						stu_dsp_=2;rec_dsp_=tb[k].rec_nr-30000;
					}
				}
				copy(s(stu_dsp_,1),buff1000,fldlen(stu_dsp_,0));
				fasinit(stu_dsp_);*u(stu_dsp_,1)=rec_dsp_;fasgeti(stu_dsp_);

				if(tb[k].rec_nr>60000){
					scrifld(14+n*10,fm_os1,"G");scrifld(15+n*10,fm_ogrb,&tb[k].grb_tb);
				}
				else{
					if(tb[k].rec_nr<30001){
						scrifld(14+n*10,fm_os1,"L");
						if(fldlen(stu_dsp_,2)) scrofld(15+n*10,stu_dsp_,2,-1);
						else scrifld(15+n*10,fm_ou5,&tb[k].rec_nr);
						stu_dsp_=1;rec_dsp_=tb[k].rec_nr;
					}
					else{
						scrifld(14+n*10,fm_os1,"K");
						rec__=tb[k].rec_nr-30000;
						if(fldlen(stu_dsp_,2)) scrofld(15+n*10,stu_dsp_,2,-1);
						else scrifld(15+n*10,fm_ou5,&rec__);
						stu_dsp_=2;rec_dsp_=tb[k].rec_nr-30000;
					}
				}
				copy(s(stu_dsp_,3),dsp_buf_,20); dsp_buf_[20]='\0';
				copy(buff1000,s(stu_dsp_,1),fldlen(stu_dsp_,0));
				scrifld(16+n*10,fm_os20,dsp_buf_);
				fmt_=fm_ou2; if(tb[k].jr_tb || tb[k].vl_tb) fmt_=fm_ou2_;
				h=tb[k].yy_tb;if(h>=100) h-=100; scrifld(17+n*10,fmt_,&h);
				h=tb[k].jr_tb;scrifld(18+n*10,fm_ou2,&h);
				scrifld(19+n*10,fm_ou5,&tb[k].vl_tb);
				if(tb[k].bedrag<0) dum[0]='D'; else dum[0]='C';
				scrifld(20+n*10,fm_os1,dum);
      }
    }
   	k=0x81EF;
		if(sys1862 & 0x80){
      k|=0x200;
      scraddf(ztot_,23,65,8); scrifld(ztot_,fm_os10," F10 zoek ");
    }
    key=scrupd(curs,k);curs=z_base;
		if ((key/0x100)==1) key=(key&0xFF)+5000;

    if(key==106){
      if(scr_ok("Wenst U echt deze boeking te annuleren ?")) return NO;
      goto redo;
    }
    if(upd_mode && (bkh_dt<=last_arc || bkh_dt<=MinBkhDatum)) {errnum=37; curs=8; goto redo;}
    if(upd_mode && volgnr==0) {errnum=38; curs=7; goto redo;}
    if(key>=10 && key<=13 || key==102 || key==103 || key==109){
      if(key==109) fin_overz(&bd_yetdiv);
      if(key==10) dcnt=7;/* home */
      if(key==11) dcnt=mcnt;/* end */
      if(key==12 || key==102) dcnt-=7;/* PgUp */
      if(key==13 || key==103) dcnt+=7;/* PgDn */
      if(dcnt<=0) dcnt=7;
      if(dcnt>mcnt) dcnt=mcnt;
      scrnum=0;goto redo;
    }
    zoek_op_bd=NO;
    if(key==5002) {zoek_op_bd=YES; searbuf[SEARBFLEN]='\0';}// doorzoek alles 

    if(lkg=='L'){
      if(credt_allow) stutyp=1;
      else {errnum=34;curs=86;goto redo;}
    }
    else if(lkg=='K'){
      if(debit_allow) stutyp=2;
      else {errnum=34;curs=86;goto redo;}
    }
    else stutyp=3;
	  if(key==5001){
			copy(lkgnaam,s(stutyp,3),fldlen(stutyp,3));
			if(search(stutyp,98)==0){copy(s(stutyp,3),lkgnaam,fldlen(stutyp,3));lkgnaam[fldlen(stutyp,3)]='\0';}
			curs=88; goto redo;
	  }
//		zoek_op_bd=NO;
		if(key==110) {
			zoek_op_bd=YES; searbuf[SEARBFLEN]='\0';
			if(ref_ft && ref_jr==0){
				if(stutyp==1) ref_jr=DefAkJournaal;
				if(stutyp==2) ref_jr=DefVkJournaal;
			}
			if(stutyp<3 && (ref_ft || !is_nul(bd_inp)) ){
				fasinit(4); *l(4,1)=ZoekFactuur(lkgnaam,ref_ft,bd_inp);
				if(*l(4,1)){
					fasgeti(4);stutyp=get_4lkg(); lkg=lkglet[stutyp-1];
					copy(s(stutyp,3),lkgnaam,fldlen(stutyp,3));lkgnaam[fldlen(stutyp,3)]='\0';
          if((is_nul(bd_inp) || bd_inp==*d(4,32)) && !is_voldaan(*l(4,1))){
						bd_inp=*d(4,32);
						//tab_add(d(4,32),(int16)*s(4,8),(int16)*s(4,9),*u(4,10),*l(4,1));
						//bd_yetdiv+=bd_inp;//BewLijn[nr_].UserChanged=YES;
						//goto redo_0;
					}
  				ref_yy=*s(4,8);
	  			ref_jr=*s(4,9);
		  		ref_ft=*u(4,10);
				} 
        goto redo;
			}
			else{
				copy(lkgnaam,s(stutyp,3),fldlen(stutyp,3));
				if(*s(stutyp,3) && Search(stutyp,98)==0){
					copy(s(stutyp,3),lkgnaam,fldlen(stutyp,3));lkgnaam[fldlen(stutyp,3)]='\0';
					if(is_nul(bd_inp)) {errnum=38;curs=z_base; goto redo;} // bd_inp=bd_tot-bd_yetdiv;
				}
				else{errnum=39;curs=z_base+3; goto redo;}
			}
    }
    if(!is_nul(bd_inp) || (zoek_op_bd && ref_ft)){
			nm_chgd_=YES; if(cmpstr(lkgnaam,s(stutyp,3),fldlen(stutyp,3))==0) nm_chgd_=NO;
      copy(lkgnaam,s(stutyp,3),fldlen(stutyp,3));
      if(*s(stutyp,3)=='\0'){
        if(zoek_op_bd){zoek_bd();goto redo;}
				else nm_chgd_=YES;
			}
			if(nm_chgd_){
  		  if(search(stutyp,0)) {fasinit(stutyp); curs=88;goto redo;}
			} else fasgeti(stutyp);
      if(stutyp==3 && g_anal_tst()) {errnum=24;curs=88;goto redo;}
      copy(s(stutyp,3),lkgnaam,fldlen(stutyp,3));lkgnaam[fldlen(stutyp,3)]='\0';
      if(stutyp<3){
				tb[mcnt].rec_nr=*u(stutyp,1)+30000*(stutyp-1);
      }
      else{
				tb[mcnt].grb_tb=*l(3,2);
				tb[mcnt].rec_nr=*u(3,1)+60000;
				grb_deco(lkgkod,l(3,2));
				if(analyt && fldlen(3,32) && last_r_!=*u(3,1)){/* default analytische uitsplitingen */
					for(k=0;k<DIMA;k++){
						if(fldlen(3,33+k*2) && *l(3,33+k*2)){
							if(ny<DIMAT-DIMA){
								zero((char *)&tba[ny].begin,sizeof tba[0] *DIMA);

							}
							anal_ask='J';break;
						}
					}
					last_r_=*u(3,1);
				}
      }
    }
    if(key==5010){
      if(stutyp==3) anal_det(mcnt);
			key=107;
    }
    if(key==107) goto redo;
		else if(!is_nul(bd_inp) && key==108) key=107; // om te vermijden dat het scherm direct weggaat als het gelijk is
    if(!is_nul(bd_inp) && stutyp!=3){
      if(ref_ft==0){
				if(zoeklk_r()==NO) {fasinit(stutyp);goto redo;}
				bd_yetdiv+=bd_inp;
				bd_inp=0;
      }
      else{
				if(ref_jr==0){errnum=38;curs=92;goto redo;}
				else{
					for(k=0;k<80;k++) if(j_tab[k].nr==ref_jr)break;
					if(k>=80) {errnum=7;curs=92;goto redo;}
				}
      }
    }
    if(anal_ask=='J'){
      if(stutyp!=3) {errnum=69;curs=90;goto redo;}
      anal_det(mcnt);anal_ask='\0';
    }
    if(!is_nul(bd_inp)){
      tab_add(&bd_inp,ref_yy,ref_jr,ref_ft,0);
      scrnum=0;/* grb kan ipv klt komen in tabel, of omgekeerd */
      bd_yetdiv+=bd_inp;
      if(errnum) goto redo;
    }

#if FLAGOPS | FLAGVDW | FLAGVNT
		if(key==101 || key==104){
	    if(auto_sal){
				if(scr_ok("Wenst U deze lijnen weg te boeken ?")==NO) goto redo;
      }
      bd_inp=0;
      for(k=0;k<mcnt;k++){
				bd_inp+=tb[k].bedrag;
      }
      if((j_tab[jtb_].typ<5 || j_tab[jtb_].typ>8) && bd_inp && auto_sal==YES){
				tb[mcnt].bedrag=-bd_inp; b_auto_sal=bd_inp;
				tb[mcnt].grb_tb=j_tab[jtb_].fingrb;
				tb[mcnt].rec_nr=j_tab[jtb_].recnr;
				*u(3,1)=tb[mcnt].rec_nr-60000;
				fasgeti(3);
				copy(s(3,3),buff7[6],20);buff7[6][20]='\0';
				tb[mcnt].yy_tb=0;tb[mcnt].jr_tb=0;tb[mcnt].vl_tb=0;
				zero(tb[mcnt].opm_bkh,sizeof tb[0].opm_bkh);
				mcnt++;
      }
#else
		if(key==101 || key==108 || key==104){
#endif
			if(aard==5 && yet_booked(journl,volgnr,bkh_dt)){errnum=59;curs=4;goto redo;}
      bd_inp=0;
      for(k=0;k<mcnt;k++){
				bd_inp+=tb[k].bedrag;
      }
      halve_bkg=NO;
      if(!is_nul(bd_inp)){
				if(key==104){
					scrget(1,29);
					key=scrupd(0xFFFF,0x110);
					if(key!=109) {errnum=10;bd_inp=0;goto redo;}
					halve_bkg=YES;
				}
				else {errnum=10;bd_inp=0;goto redo_0;}
			}
			if(upd_mode){/* eerst originele boeking schrappen */
				for(k=0;k<DIM_OFIN;k++){
					if(tb_ofin[k]){
						fasinit(4);*l(4,1)=tb_ofin[k];fasgetu(4);faskill(4);
					}
				}
      }
      boek(mcnt);
      break;
    }
  }
  return YES;
}

static fin_overz(pbd_yetdiv)
double *pbd_yetdiv;
{
  int16 h,key,curs=1,j,k,z,stu_dsp_,start_,pos_,curspos_;
  uint16 rec_dsp_,blok_first;
  double bd_;
  char dum[2],dsp_buf_[31],*fmt_;

  blok_first=NO; start_=0;
  if(upd_mode==NO && (j_tab[jtb_].typ<5 || j_tab[jtb_].typ>8) && bd_tot) blok_first=YES;
  FOREVER{
    redo:;
    scrnum=0;scrget(1,67);z=1;
    for(k=start_;k<start_+15;k++){
      if(k>=mcnt) break;
      k++;scrifld(z++,fm_ou3,&k);k--;
      if(tb[k].bedrag<0) dum[0]='D'; else dum[0]='C';
      scrifld(z++,fm_os1,dum);
      scrifld(z++,fm_od92_,&tb[k].bedrag);
      stu_dsp_=0; rec_dsp_=0;
      if(tb[k].rec_nr>60000){
	scrifld(z++,fm_os1,"G");
	stu_dsp_=3;rec_dsp_=tb[k].rec_nr-60000;
      }
      else{
	if(tb[k].rec_nr<30001){
	  scrifld(z++,fm_os1,"L");
	  stu_dsp_=1;rec_dsp_=tb[k].rec_nr;
	}
	else{
	  scrifld(z++,fm_os1,"K");
	  stu_dsp_=2;rec_dsp_=tb[k].rec_nr-30000;
	}
      }
      copy(s(stu_dsp_,1),buff1000,fldlen(stu_dsp_,0));
      fasinit(stu_dsp_);*u(stu_dsp_,1)=rec_dsp_;fasgeti(stu_dsp_);
      zero(dsp_buf_,sizeof dsp_buf_);
      copy(s(stu_dsp_,3),dsp_buf_,20); dsp_buf_[20]=' ';
      h=0;for(j=0;j<20;j++) if(dsp_buf_[j]=='\0' || h){h=1;dsp_buf_[j]=' ';}
      if(stu_dsp_<3){
	if(fldlen(stu_dsp_,2)) copy(s(stu_dsp_,2),&dsp_buf_[21],fldlen(stu_dsp_,2));
	else stcli_d(&dsp_buf_[21],(long)(*u(stu_dsp_,1)),5,1);
      }
      else{
	grb_deco(&dsp_buf_[21],l(3,2));
      }
      copy(buff1000,s(stu_dsp_,1),fldlen(stu_dsp_,0));
      scrifld(z++,fm_os27,dsp_buf_);
      fmt_=fm_ou2; if(tb[k].jr_tb || tb[k].vl_tb) fmt_=fm_ou2_;
      h=tb[k].yy_tb;if(h>=100) h-=100; scrifld(z++,fmt_,&h);
      h=tb[k].jr_tb;scrifld(z++,fm_ou2,&h);
      scrifld(z++,fm_ou5,&tb[k].vl_tb);
      scrifld(z++,fm_us18,tb[k].opm_bkh);
    }
    scrifld(136,fm_od92_,&bd_tot);
    scrifld(137,fm_od92_,pbd_yetdiv);
    bd_=bd_tot-*pbd_yetdiv;scrifld(138,fm_od92_,&bd_);
    if(k==start_) curs=-1;
    key=scrupd(curs,0x2A7); curs=1;curspos_=fldcurs;
    if(key==101 || key==108) break;
    if(key==106){
      curs=curspos_;
      j=(curspos_-1)/9; if(j<0) goto redo;
      pos_=start_+j;
      if((pos_==0 && blok_first) || pos_>=mcnt) {errnum=63; goto redo;}
      *pbd_yetdiv-=tb[pos_].bedrag;
      if(analyt){
				for(k=0;k<DIMAT;k++){
					if(tba[k].a_elem==pos_ && tba[k].a_rec_nr){
						for(j=k+1;j<DIMAT;j++){
							copy((char *)&tba[j].begin,(char *)&tba[j-1].begin,sizeof tba[0]);
						}
						zero((char *)&tba[DIMAT-1].begin,sizeof tba[0]);
						k--;
					}
					else if(tba[k].a_elem>pos_ && tba[k].a_rec_nr) tba[k].a_elem--; // element wordt geschrapt, dus alles erboven corrigeren
				}
      }
      for(j=pos_+1;j<MAX_TB_EL;j++){
      	copy((char *)&tb[j].begin,(char *)&tb[j-1].begin,sizeof tb[0]);
      }
      zero((char *)&tb[MAX_TB_EL-1].begin,sizeof tb[0]);
      mcnt--;
      if(start_>=mcnt){
				start_-=15; if(start_<0) start_=0;
      }
    }
    if(key==110){
      curs=curspos_;
      j=(curspos_-1)/9; if(j<0) goto redo;
      pos_=start_+j;
      if(pos_>=mcnt) {errnum=63; goto redo;}
      for(k=0;k<mcnt;k++){
				if(k!=pos_) copy(tb[pos_].opm_bkh,tb[k].opm_bkh,sizeof tb[0].opm_bkh);
      }
      goto redo;
    }
    if(key==102){
      start_-=15; if(start_<0) start_=0;
    }
    if(key==103){
      start_+=15; if(start_>=mcnt) start_-=15;
    }
  }
  endsr:;
}

static long ZoekFactuur(char *pnaam_,uint16 ft_nummer_,double bedrag_)  // zoek AK/VK factuur ahv nummer of bedrag
{
  int16 j,k,z,stu_,key,start_=0,mode_,only_facturen_=YES,max_ft_,max_ft_OK_,max_,d_lin_scr_=14,tb_off_;
	uint16 dt_max_;
  long used,retval_;
  double bd4_,bd_i_;
 

	scrget(1,7);scrupd(-3,0);
	dt_max_=*u(25,2)-180; // SU2 : data beperken owv blokkage
	fasinfo(4,1); used=*l(4,1);
	zero((char *)&TbZoekFactuur[0].rec4,sizeof TbZoekFactuur);max_ft_=0; max_ft_OK_=0;tb_off_=0;

  if(ft_nummer_){/* geldige facturen opzoeken via keys (snelheid) */
    for(k=0;k<40;k++){
      if(j_tab[k].nr && ((stutyp==1 && j_tab[k].typ==1) || (stutyp==2 && j_tab[k].typ==2))) { // echt zoeken naar AK of VK factuur
				fasinit(4);*s(4,2)=j_tab[k].nr;*u(4,3)=ft_nummer_;mode_=0;
				FOREVER{
					if(faskeyi(4,1,mode_)) break; mode_=2;
					if(*s(4,2)!=j_tab[k].nr || *u(4,3)!=ft_nummer_) break;
					if(*u(4,5)<60000){// alleen klt/lev
						TbZoekFactuur[max_ft_].rec4=*l(4,1);
						if(!is_voldaan(*l(4,1))){
							TbZoekFactuur[max_ft_].fullmatch=YES;
							copy((char *)&TbZoekFactuur[max_ft_].rec4,(char *)&TbZoekFactuur[100+max_ft_OK_].rec4,sizeof TbZoekFactuur[0]);
							max_ft_OK_++;
						}
						else if(*u(4,4)<=MinBkhDatum) {max_ft_--;}
						max_ft_++; if(max_ft_>=100) break;
					}
				}
      }
    }
  }
	else{
	  fasinit(4);if(stutyp>2) *u(4,5)=1+(stutyp-1)*30000; mode_=1; //j_tab[k].nr;*u(4,3)=ft_nummer_;mode_=0;
		FOREVER{
			next4:;
			if(faskeyi(4,4,mode_)) break; mode_=2;
//			if(*u(4,5)>(30000+(stutyp-1)*30000)) break;
			if(stutyp<3 && *u(4,5)>60000) break;
#if FLAGSU2  
			if(*u(4,4)<dt_max_) goto next4; // om blokkage te vermijden owv te hoge trafiek
#endif
//			if(only_facturen_ && ((stutyp==1 && *s(4,2)!=DefAkJournaal) || (stutyp==2 && *s(4,2)!=DefVkJournaal))) goto next4;
			if(only_facturen_ && (stutyp==1 || stutyp==2) && *s(4,2)!=DefAkJournaal && *s(4,2)!=DefVkJournaal) goto next4; // bij klt/lev zowel zoeken op klt/lev, bij grb op alles
			bd4_=*d(4,32);
			if(sys1840==NO && ((bedrag_<0 && bd4_>0) || (bedrag_>0 && bd4_<0))) goto next4;
			if(bd4_<0) bd4_=-bd4_;
			bd_i_=bedrag_;if(bd_i_<0) bd_i_=-bd_i_;
			if(bd4_>(bd_i_+afw_long+.005) || bd4_<(bd_i_-afw_long-.005)) goto next4;
			if(*u(4,5)<60000){ // alleen klt/lev
				TbZoekFactuur[max_ft_].rec4=*l(4,1);
				if(!is_voldaan(*l(4,1))){
					TbZoekFactuur[max_ft_].fullmatch=YES;
					copy((char *)&TbZoekFactuur[max_ft_].rec4,(char *)&TbZoekFactuur[100+max_ft_OK_].rec4,sizeof TbZoekFactuur[0]);
					max_ft_OK_++;
				} 
				else if(*u(4,4)<=MinBkhDatum) {max_ft_--;}
				max_ft_++; if(max_ft_>=100) break;
			}
		}
	}
	if(max_ft_==0) {errnum=14; return 0L;}
  start_=0;max_=max_ft_OK_; tb_off_=100;
  FOREVER{
    scrnum=0; scrget(1,271);z=1;
		scrifld(z++,VarTextFmt(30,0),pnaam_);
  	if(ft_nummer_){scrifld(z++,VarTextFmt(7,0),"FACTUUR");scrifld(z++,fm_ou5,&ft_nummer_);}
		else {scrifld(z++,VarTextFmt(7,0),"BEDRAG");scrifld(z++,fm_od6_2,&bedrag_);}
		for(k=start_;k<start_+d_lin_scr_;k++){
		  if(k>=max_) break;
			*l(4,1)=TbZoekFactuur[k+tb_off_].rec4;fasgeti(4);
			k++; scrifld(z++,fm_ou3,&k); k--; if(TbZoekFactuur[k+tb_off_].fullmatch) scrchat(z-1,0x8); else scrchat(z-1,0xFF);
			j=*s(4,2);scrifld(z++,fm_ou3,&j);
			scrofld(z++,4,3,-1);
			scrofld(z++,4,4,-1);
			scrifld(z++,fm_od6_2,d(4,32));
			if(*d(4,32)<0) scrifld(z++,fm_os1,"C"); else scrifld(z++,fm_os1,"D");
			stu_=get_4lkg();scrifld(z++,fm_os1,&lkglet[stu_-1]);
			scrofld(z++,stu_,3,30);
    }
    j=0;scrifld(116,fm_uu3,&j);
		if(tb_off_==0) scrifld(117,VarTextFmt(26,0)," F10 OPENSTAANDE facturen ");
		else scrifld(117,VarTextFmt(19,0)," F10 ALLE facturen ");
    key=scrupd(1,0x2A7);
		if(key==101 || key==106) {retval_=0; break;}
    if(key==102) start_-=d_lin_scr_;
    if(key==103) {start_+=d_lin_scr_;if(start_>max_ft_-d_lin_scr_) start_=max_ft_-d_lin_scr_;}
    if(start_<0) start_=0;
		if(j>0 && j<=max_) {retval_=TbZoekFactuur[tb_off_+j-1].rec4;break;}
		if(key==110){
			if(tb_off_==0){tb_off_=100;max_=max_ft_OK_;}
			else {tb_off_=0;max_=max_ft_;}
			start_=0;
		}
  }
  for(k=1;k<=3;k++) fasinit(k);
	return retval_;
}


static boek(quant)
int16 quant;
{
  int16 g,k;
  long grbveld;
  double tot_eur,tot_vm,bd_eur,bd_vm;
									
  fasunlck(-2);
	tot_eur=0;tot_vm=0;
  for(g=0;g<quant;g++){
    if(tb[g].bedrag){
      bd_eur=valu_cnv(munt,"EUR",tb[g].bedrag,(double)0.01);
      if(valtype=='V') bd_vm=valu_cnv(munt,munt,tb[g].bedrag,(double)0.01);
      else bd_vm=0;
      tot_eur+=bd_eur;tot_vm+=bd_vm;
      initrec(4);
      if(tb[g].rec_nr<30000) grbveld=levcent;
      else if(tb[g].rec_nr<60000) grbveld=kltcent;
      else {
				fasinit(3);*l(3,1)=tb[g].rec_nr-60000; 
				if(fasgeti(3)==0) grbveld=*l(3,2);
				else grbveld=tb[g].grb_tb;
			}
      *u(4,5)=tb[g].rec_nr;
      *l(4,6)=grbveld;
      *l(4,7)=-bd_eur; *pd_4_32=-bd_eur;
      *s(4,31)='E';
      *s(4,8)=tb[g].yy_tb;
      *s(4,9)=tb[g].jr_tb;
      *u(4,10)=tb[g].vl_tb;
      if(*s(4,9) || *u(4,10)){/* correctie y2000 */
				if(*s(4,8)<50) *s(4,8)+=100;
				else if(*s(4,8)>=150) *s(4,8)-=100;
      } else if(*s(4,8)==100) *s(4,8)=0;
      if(fldlen(4,15) && valtype=='V'){
				copy(munt,s(4,15),3);
				*d(4,16)=-tb[g].bedrag;
      }
			if(fldlen(4,23)) *u(4,23)=g; // lijnnummer onthouden voor analytisch
      copy(tb[g].opm_bkh,s(4,28),OPMLEN);
			if(fldlen(4,60)){
				if(tb[g].procid) *u(4,60)=tb[g].procid;
  			else *u(4,60)=procid;
			}
      errnum=fasadd(4);
			if(tb[g].GRBwacht && tb[g].GRBoverb){ // huurbetalingen overboeken van 4-wachtrekening naar 7-rekening
				fasinit(3);*l(3,2)=tb[g].GRBwacht; k=faskeyi(3,1,0);
				if(k==0){fasinit(3);*l(3,2)=tb[g].GRBoverb; k=faskeyi(3,1,0);}
				if(k==0){
					fasinit(3);*l(3,2)=tb[g].GRBoverb; k=faskeyi(3,1,0);
					*u(4,5)=*u(3,1)+60000; *l(4,6)=*l(3,2);
					*l(4,7)=-bd_eur; *pd_4_32=-bd_eur;
					errnum=fasadd(4);
					fasinit(3);*l(3,2)=tb[g].GRBwacht; k=faskeyi(3,1,0);
					*u(4,5)=*u(3,1)+60000; *l(4,6)=*l(3,2);
					*l(4,7)=bd_eur; *pd_4_32=bd_eur;
					errnum=fasadd(4);
				}
			}
    }
  }
  if(halve_bkg){/* correctie halve boeking  */
    bd_eur=tot_eur;
    tot_eur-=bd_eur;
  }
  if(!is_nul(tot_eur)){/* verschillen wegboeken */
    initrec(4);
    if(grb_d_fi){
      *u(4,5)=rec_d_fi; *l(4,6)=grb_d_fi;
    }
    else{
      if(tot_eur>0){
	*u(4,5)=rec_d_ak; *l(4,6)=grb_d_ak;
      }
      else {*u(4,5)=rec_d_vk; *l(4,6)=grb_d_vk;}
    }
    *l(4,7)=tot_eur; *pd_4_32=tot_eur;
    *s(4,31)='E';
		if(fldlen(4,60)) *u(4,60)=procid;
    errnum=fasadd(4);
  }
  if(analyt){
    for(g=0;g<DIMAT;g++){
      if(tba[g].a_bedrag){
				initrec(4);
				*u(4,5)=tba[g].a_rec_nr;
				*l(4,6)=tba[g].a_grbrek;
				bd_eur=valu_cnv(munt,"EUR",tba[g].a_bedrag,(double)0.01);
				*l(4,7)=-bd_eur; *pd_4_32=-bd_eur;
				*s(4,31)='E';
				*l(4,11)=tb[tba[g].a_elem].grb_tb;
				if(fldlen(4,23)) *u(4,23)=tba[g].a_elem; // lijnnummer onthouden van hoofdrekening voor analytisch update
				if(fldlen(4,60)) *u(4,60)=procid;
				errnum=fasadd(4);
      }
    }
  }
  fasunlck(-1);fasflush(0);
}

static initrec(stu_)
int16 stu_;
{
  fasinit(stu_);
  *s(stu_,2)=journl;
  *u(stu_,3)=volgnr;
  *u(stu_,4)=bkh_dt;
}

static zoeklk_r()
{
  int16 byte,curs,key,j,k,start_,lin,z,mcnt_res,stutyp_o;
  uint16 dt_bew,linenr;
  double bd_line_,bd_irest,bd_x,bd_thiskl=0,bd_,bd_fact=0,bd_disc=0,bd_df_;
  flag scrdata,found;
  char df_munt_[4],attr_;
				
  copy(def_munt,df_munt_,3);
 
  mcnt_res=mcnt;
  copy(buff7[0],buff7res[0],sizeof buff7);
  copy(s(4,1),bf,len4_0);
  corr_y2000(4,*u(stutyp,1)+(stutyp-1)*30000);/* y2000 correctie */
  copy(bf,s(4,1),len4_0);

  zero(combi_nr,sizeof combi_nr);bd_=0;
  bd_irest=valu_cnv("EUR","EUR",bd_inp,(double)0.01);
  make_otab();
  begin:
  FOREVER{
    linenr=0;bd_line_=0;
    start_=0;
    curs=8;
    FOREVER{
      redo:
      scrnum=0; scrget(1,28);z=1;
      if((stutyp==1&&lvcd) || (stutyp==2&&klcd)) scrofld(z++,stutyp,2,6);
      else scrofld(z++,stutyp,1,-1);
      scrofld(z++,stutyp,3,-1);
			scrifld(z++,fm_us20,opmer);
      scrxfld(&z,NO,&bd_inp,YES);
      scrxfld(&z,NO,&bd_irest,YES);
      scrifld(z++,fm_uu3,&linenr);
      scrxfld(&z,YES,&bd_line_,YES);
      scrifld(z++,fm_os3,munt);
      if(cmpstr(munt,df_munt_,3)==0) scrifld(z++,fm_os10,"Opmerking");
      else scrifld(z++,fm_os3,df_munt_);
      for(k=start_;k<start_+12;k++){
	if(k>=max_orec) break;
	*l(4,1)=open_recs[k].rec;
	if(fasgeti(4)) break;
	attr_=0xFF;
	for(j=0;j<MAX_CNIV;j++) if(combi_nr[j] && (combi_nr[j]-1)==k) break;
	if(j<MAX_CNIV) attr_=0x9;
	if(is_nul((double)(*pd_4_32-bd_irest))) attr_=8;
	for(j=0;j<mcnt;j++) if(*l(4,1)==tb[j].recft) break;
	if(j<mcnt) attr_=0;
	if(valtype=='V'){
	  if(cmpstr(munt,s(4,15),3)==0) bd_x=*d(4,16);
	  else bd_x=valu_cnv("EUR",munt,*pd_4_32,(double)0.01);
	}
	else bd_x=*pd_4_32;
	bd_df_=*pd_4_32;
	lin=k+1;scrifld(z++,fm_ou3,&lin);scrchat(z-1,attr_);
	dt_bew=*u(4,4);found=NO;
	if((sys1862 &2) || (sys1862 &4)){
	  if(*u(4,20)){dt_bew=*u(4,20);found=YES;}
	}
	byte=*s(4,2);scrifld(z++,fm_ou2,&byte);scrchat(z-1,attr_);
	scrofld(z++,4,3,-1); scrchat(z-1,attr_);
	scrifld(z++,fm_odat,&dt_bew);scrchat(z-1,attr_);
	if(bd_x>=0) scrifld(z++,fm_os1,"D");
	else scrifld(z++,fm_os1,"C");
	scrchat(z-1,attr_);
	scrxfld(&z,NO,&bd_x,NO); z--;scrchat(z-1,attr_);
	if(cmpstr(munt,df_munt_,3)==0) scrofld(z++,4,28,12);
	else scrifld(z++,fm_od92_,&bd_df_);
	scrchat(z-1,attr_);
	if(sys1818 & 1){
	  scrofld(z++,4,28,10);scrchat(z-1,attr_);
	  z+=2;
	}
	else if((sys1862 &4) && (sys1862 &1)){
	  scrofld(z++,4,25,-1);scrchat(z-1,attr_);
	  z+=2;
	}
	else{
	  byte=*s(4,8); if(*s(4,9) || *u(4,10)) byte+=1900;
	  scrifld(z++,fm_ou4,&byte);scrchat(z-1,attr_);
	  byte=*s(4,9); scrifld(z++,fm_ou2,&byte);scrchat(z-1,attr_);
	  scrofld(z++,4,10,-1);scrchat(z-1,attr_);
	}
      }
      key=scrupd(curs,0x3A7);curs=8;
      if(key==103){
	if((start_+12)<max_orec) start_+=12;
	goto redo;
      }
      if(key==101 && linenr==0) break;
      if(key==102){
	start_-=12; if(start_<0) start_=0;
	goto redo;
      }
      if(key==106) goto return_;
      if(key==109){
	if(is_nul(bd_line_)) bd_line_=bd_irest;
	bd_fact+=bd_line_;
	fasinit(4);/* zonder referentie */
	break;
      }
      if(key==110){
	zero(combi_nr,sizeof combi_nr);bd_=0;
	if(zk_combi(0,0,&bd_,&bd_irest)){
	  if((start_+12)<combi_nr[0]) start_=combi_nr[0]-1;
	}
	goto redo;
      }
      if(linenr==0 || linenr>max_orec) {errnum=34;goto redo;}
      *l(4,1)=open_recs[linenr-1].rec;
      if(fasgeti(4)) {errnum=39;goto redo;}
      if(is_nul(bd_line_)){
	if(valtype=='V'){
	  if(cmpstr(munt,s(4,15),3)==0) bd_line_=*d(4,16);
	  else{
	    bd_line_=valu_cnv("EUR",munt,*pd_4_32,(double)0.01);
	  }
	}
	else bd_line_=*pd_4_32;
      }
      bd_fact+=bd_line_;bd_disc+=*d(4,34);
      break;
    }
    if(bd_line_){
      tab_add(&bd_line_,(int16)*s(4,8),(int16)*s(4,9),*u(4,10),*l(4,1));
      bd_thiskl-=bd_line_;
      bd_irest-=bd_line_;
      if(errnum) {scrdata=YES;goto redo;}
    }
    if(is_nul(bd_irest)) break;
    if(key==101) break;
  }
  scrdata=YES;
  FOREVER{
    if(is_nul(bd_irest)) break;
    if(sysdiff==0){
      for(k=0;k<6;k++){
	*u(3,1)=df_recnr[k+5]-60000;
	fasgeti(3);
	copy(s(3,3),gnm_diff[k],20);
      }
      sysdiff=1;
    }

    bd_=-bd_thiskl;
    linenr=0;
    fasinit(3);
    scrdata=YES;
    bd_line_=bd_irest;
    redo_31:
    if(scrget(1,31)) scrdata=YES;
    if(scrdata){
      z=1;
      scrxfld(&z,NO,&bd_fact,YES);z+=2;
      scrxfld(&z,NO,&bd_,YES);
      scrxfld(&z,YES,&bd_line_,YES); scrifld(z++,fm_od6_2,&bd_disc);
      scrifld(z++,fm_uu2,&linenr);
      scrfld(z++,3,3);
      for(k=0;k<6;k++){
	if(gnm_diff[k][0]){
	  lin=k+1;scrifld(z,fm_ou2,&lin);
	  if(bd_irest<0 && k%2) scrchat(z,6);
	  if(bd_irest>0 && (k+1)%2) scrchat(z,6);
	  z++;
	  scrifld(z++,fm_ogrb,&df_grb[k+5]);
	  scrifld(z++,fm_os20,gnm_diff[k]);
	}
      }
      scrdata=NO;
    }
    key=scrupd(10,0x0E0);
    if(key==106) goto return_;
    if(key==107) goto begin;
    if(is_nul(bd_line_)) goto redo_31;
    if(linenr){
      if(linenr>6) {errnum=34;goto redo_31;}
      *l(3,2)=df_grb[linenr-1+5];
      if(faskeyi(3,1,0)) {errnum=39;goto redo_31;}
    }
    else{
      if(search(3,0)) {errnum=39;goto redo_31;}
      if(g_anal_tst()) {errnum=24;curs=77;goto redo;}
    }
    stutyp_o=stutyp;stutyp=3;
    tab_add(&bd_line_,0,0,0,0);
    stutyp=stutyp_o;
    if(errnum) {scrdata=YES;goto redo;}
    bd_thiskl-=bd_line_;
    bd_irest-=bd_line_;
    scrdata=YES;
  }
  copy(bf,s(4,1),len4_0);
  return YES;
 
  return_:
  mcnt=mcnt_res;
  copy(buff7res[0],buff7[0],sizeof buff7);
  copy(bf,s(4,1),len4_0);
  return NO;
}

static make_otab()
{
  int16 j,k,pos_,posr_,end_;
  uint16 first, r_yy,r_jr,r_nr;
  double ebd_;

  fasinit(4);
  searcnr=*u(stutyp,1)+(stutyp-1)*30000;
  *u(4,5)=searcnr;

  first=YES; end_=NO; posr_=0; pos_=0; ebd_=0; max_orec=0;
  FOREVER{
    if(faskeyi(4,4,2)) end_=YES;
    if(!end_ && *u(4,5)!=searcnr) end_=YES;
    if(!end_ && first){
      r_yy=*s(4,8); r_jr=*s(4,9); r_nr=*u(4,10);
      first=NO;
    }
    if(end_ || *s(4,8)!=r_yy || r_jr!=*s(4,9) || r_nr!=*u(4,10)){
      if(is_nul(ebd_)){
	for(k=posr_;k<pos_;k++) zero((char *)&open_recs[k].rec,sizeof open_recs[0]);
	pos_=posr_;
      }
      ebd_=0;posr_=pos_;
      r_yy=*s(4,8); r_jr=*s(4,9); r_nr=*u(4,10);
      if(end_) break;
    }
    open_recs[pos_].bedrag=*pd_4_32;
    open_recs[pos_++].rec=*l(4,1);
    ebd_+=*pd_4_32;
    if(pos_>=DIM_OPEN) break;
  }
  if(zoek_op_bd && pos_>0){
    for(k=0;k<pos_;k++){
      fasinit(4);*l(4,1)=open_recs[k].rec; fasgeti(4);
      if(bd_zk_ok()==NO){
	for(j=k+1;j<pos_;j++) open_recs[j-1].rec=open_recs[j].rec;
	k--;pos_--;
      }
    }
  }
  max_orec=pos_;
  return pos_;
}

static flag zk_combi(beg_,niv_,pbd_beg_,ptotaal_)
int16 beg_,niv_;
double *pbd_beg_,*ptotaal_;
{
  int16 j,k;
  double bd_;

  if(niv_>=MAX_CNIV) return NO;
  for(k=beg_;k<max_orec;k++){
    for(j=0;j<mcnt;j++) if(open_recs[k].rec==tb[j].recft) break;
    if(j<mcnt) continue;
    bd_=*pbd_beg_+open_recs[k].bedrag;
    if(is_nul(bd_-*ptotaal_)) break;
    if(zk_combi(k+1,niv_+1,&bd_,ptotaal_))break;
  }
  if(k<max_orec){combi_nr[niv_]=k+1; return YES; }
  return NO;
}

 
static corr_y2000(bstu_,searcnr_)/* Y2000 probleem oplossen tijdelijk tot 2005 */
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
		if(*ry_!=ly_){ fasupd(bstu_); mode_=1;}/* indien gewijzigd, updaten */
    *ry_=ly_;/* key-volgorde behouden */
  }
}

static zoek_bd()
{
  int16 j,k,z,scrnr_=0,stu_,cnt_=0,start_=0,mode_;
  long a,used,tb_ft_[20];
  double bd_x;
			
	scrget(1,7);scrupd(-3,0);
  fasinfo(4,1); zero((char *)&zoekscr[0],sizeof zoekscr);pzoekscr=0;
  zero((char *)&tb_ft_[0],sizeof tb_ft_);
  used=*l(4,1);
  if(ref_ft){/* geldige facturen opzoeken via keys (snelheid) */
    j=0;
    for(k=0;k<40;k++){
      if(j_tab[k].nr && j_tab[k].typ<3){
				fasinit(4);*s(4,2)=j_tab[k].nr;*u(4,3)=ref_ft;mode_=0;
				FOREVER{
					if(faskeyi(4,1,mode_)) break; mode_=2;
					if(*s(4,2)!=j_tab[k].nr || *u(4,3)!=ref_ft) break;
					if((is_nul(bd_inp) || bd_inp==*pd_4_32) && *u(4,5)<60000) tb_ft_[j++]=*l(4,1);
				}
      }
    }
    if(j==0) {errnum=14;goto endsr;}
  }

  redo_zoek:;
  for(a=1;a<=used;a++){
    if(ref_ft){/* niet geldige records al uitfilteren */
      for(k=0;k<20;k++) if(tb_ft_[k]==a) break;
      if(k>=20) continue;
    }
    if(scrnr_==0){
      scrnum=0;
      scrget(1,82);z=1;scrnr_=82;
      scrxfld(&z,NO,&bd_inp,YES);
      scrifld(z++,fm_os3,munt);
      start_=pzoekscr*15; cnt_=start_;
      if(zoekscr[pzoekscr]) a=zoekscr[pzoekscr];
    }
    *l(4,1)=a;
    if(fasgetu(4)==0){
      if(bd_zk_ok()){
				if(zoekscr[pzoekscr]==0) zoekscr[pzoekscr]=a;
				j=cnt_+1;
				scrifld(z++,fm_ou3,&j);
				if(!is_voldaan(*l(4,1))) scrchat(z-1,0x8);
				else scrchat(z-1,0xFF);
				k=*s(4,2);scrifld(z++,fm_ou3,&k);
				scrofld(z++,4,3,-1);
				scrofld(z++,4,4,-1);
				if(valtype=='V'){
					if(cmpstr(munt,s(4,15),3)==0) bd_x=*d(4,16);
					else bd_x=valu_cnv("EUR",munt,*pd_4_32,(double)0.01);
				}
				else bd_x=*pd_4_32;
			/*    else bd_x=*l(4,7); */
				scrxfld(&z,NO,&bd_x,NO);z--;
				if(*pd_4_32<0) scrifld(z++,fm_os1,"C"); else scrifld(z++,fm_os1,"D");
				stu_=get_4lkg();
				scrifld(z++,fm_os1,&lkglet[stu_-1]);
				k=fldlen(stu_,3);if(k>20) k=20;
				scrofld(z++,stu_,3,k);
				zk_rec[cnt_-start_]=*l(4,1); cnt_++;
				if((cnt_%15)==0) {if(_zoek_b(start_,cnt_)) goto endsr; scrnr_=0;}
      }
    }
  }
  if(_zoek_b(start_,cnt_)==0) {scrnr_=0;goto redo_zoek;}
  endsr:;
  for(k=1;k<=3;k++) fasinit(k);
}

static bd_zk_ok()
{
  double bd4_,bd_i_;

  if(ref_ft && is_nul(bd_inp)){
#if FLAGOPS
		if(is_voldaan(*l(4,1))) return NO;// GEEN VOLDANE FT 
    else return YES;
#endif
		return YES;/* indien geen bedrag dan altijd ok */
	}
  if(valtype=='V'){
    if(cmpstr(munt,s(4,15),3)==0) bd4_=*d(4,16);
    else bd4_=valu_cnv("EUR",munt,*pd_4_32,(double)0.01);
  }
  else bd4_=*pd_4_32;
/* else bd4_=*l(4,7); */
  if(sys1840==NO && ((bd_inp<0 && bd4_>0) || (bd_inp>0 && bd4_<0))) return NO;
  if(bd4_<0) bd4_=-bd4_;
  bd_i_=bd_inp;if(bd_i_<0) bd_i_=-bd_i_;
  if(bd4_>(bd_i_+afw_long+.005) || bd4_<(bd_i_-afw_long-.005)) return NO;
#if FLAGOPS	
	if(is_voldaan(*l(4,1))) return NO;// GEEN VOLDANE FT 
#endif
  return YES;
}

static _zoek_b(start_,cnt_)
int16 start_,cnt_;
{
  int16 fuval=0,key,g,k,ln_=0,stu_;

  FOREVER{
    scrifld(4+15*8,fm_uu3,&ln_);
    key=scrupd(4+15*8,0xA7);
    if(key==101 || key==106){fuval=106;goto endsr;}
    if(key==102){
      if(pzoekscr) pzoekscr--; fuval=0;goto endsr;
    }
    if(key==103){
      if((cnt_-start_)>=15 && pzoekscr<DIMZOEK) pzoekscr++;
      fuval=0; goto endsr;
    }
    if(key==108 || ln_){
      if(ln_>start_ && ln_<=cnt_){
				*l(4,1)=zk_rec[ln_-1-start_];fasgeti(4);
				stu_=get_4lkg();
				lkg=lkglet[stu_-1];
				if(stu_<3){
					if(fldlen(stu_,2)){
						g=0;if(*s(stu_,2)<'0' || *s(stu_,2)>'9'){lkgnaam[0]='.';g=1;}
						copy(s(stu_,2),&lkgnaam[g],fldlen(stu_,2)+g);
						for(k=0;k<fldlen(stu_,2)+g;k++) if(lkgnaam[k]=='\0') break;
						for(k;k<fldlen(stu_,2)+g;k++) lkgnaam[k]=' ';
					}
					else {stcli_d(lkgnaam,(long)(*u(stu_,1)),5,0);k=5;}
					lkgnaam[k++]=' ';
					copy(s(stu_,3),&lkgnaam[k],fldlen(stu_,3));
				}
				else{
					grb_deco(lkgnaam,l(3,2));
	        for(g=0;g<9;g++) if(lkgnaam[g]=='\0') lkgnaam[g]=' ';
	        g=fldlen(3,3);if(g>MAXLEN-9)g=MAXLEN-9;
	        copy(s(3,3),&lkgnaam[9],g);
					//copy(s(stu_,3),lkgnaam,fldlen(stu_,3));
				}
				ref_yy=*s(4,8);
				ref_jr=*s(4,9);
				if(ref_ft && is_nul(bd_inp)) bd_inp=*pd_4_32;
				ref_ft=*u(4,10);
				fuval=108;break;
      }
    }
    else goto endsr;
  }
  endsr:;
  return fuval;
}

static is_voldaan(rec4_)
long rec4_;
{
  int16 mode_,ret_val_;
  uint16 lkg_rec_,ref_jr_,ref_jn_,ref_vl_;
  double bd_;

  ret_val_=NO;
  copy(s(4,1),buff1000,fldlen(4,0));
  fasinit(4);*l(4,1)=rec4_;fasgeti(4);
  if(*u(4,5)>=60000) {ret_val_=YES;goto endsr;}/* GRB's steeds voldaan */
  if(*s(4,8)==0 && *s(4,9)==0 && *u(4,10)==0) goto endsr;
  ref_jr_=*s(4,8);ref_jn_=*s(4,9);ref_vl_=*u(4,10);lkg_rec_=*u(4,5);
  fasinit(4);*u(4,5)=lkg_rec_;*s(4,8)=ref_jr_;*s(4,9)=ref_jn_;*u(4,10)=ref_vl_;
  bd_=0;mode_=1;
  FOREVER{
    if(faskeyi(4,4,mode_)) break; mode_=2;
    if(*u(4,5)!=lkg_rec_) break;
    if(*s(4,8)!=ref_jr_ || *s(4,9)!=ref_jn_ || *u(4,10)!=ref_vl_) break;
    if(is_nul(*pd_4_32)){
      *pd_4_32=valu_cnv(def_munt,"EUR",(double)(*l(4,7)),(double)0.01);
    }
    bd_+=*pd_4_32;
  }
  if(is_nul(bd_)) ret_val_=YES;
  endsr:;
  copy(buff1000,s(4,1),fldlen(4,0));
  return ret_val_;
}
 
static tab_add(pdbl_,ref_yy_,ref_jr_,ref_ft_,ft_rec_)
uint16 ref_yy_,ref_jr_,ref_ft_;
long ft_rec_;
double *pdbl_;
{
  if(mcnt>=MAX_TB_EL) {errnum=11;goto endsr;}
  tb[mcnt].rec_nr=*u(stutyp,1)+30000*(stutyp-1);
  if(stutyp==3){
    tb[mcnt].grb_tb=*l(stutyp,2);
    ref_yy_=0;
  }
  tb[mcnt].bedrag=*pdbl_;
  copy(buff7[1],buff7[0],6*sizeof buff7[0]);
  copy(s(stutyp,3),buff7[6],20);buff7[6][20]='\0';
  tb[mcnt].yy_tb=ref_yy_;tb[mcnt].jr_tb=ref_jr_;tb[mcnt].vl_tb=ref_ft_;
  copy(opmer,tb[mcnt].opm_bkh,OPMLEN);
  tb[mcnt].recft=ft_rec_;
	if(stutyp==2 && PandJournaal && ft_rec_ && *s(4,2)==PandJournaal){  // overboeking huur 
		if(*l(4,40) && *l(4,41) && *l(4,40)!=*l(4,41)){
			tb[mcnt].GRBwacht=*l(4,40);tb[mcnt].GRBoverb=*l(4,41);
		} else{tb[mcnt].GRBwacht=0;tb[mcnt].GRBoverb=0;}
	}
  mcnt++;
  if(mcnt==MAX_TB_EL) errnum=11;
  endsr:;
}
 
static get_4lkg()
{
  int16 stu_;
  uint16 rec_;

  if(*u(4,5)<30000){rec_=*u(4,5);stu_=1;}
  else if(*u(4,5)<60000){rec_=*u(4,5)-30000;stu_=2;}
  else{rec_=*u(4,5)-60000;stu_=3;}
  fasinit(stu_);*u(stu_,1)=rec_;fasgeti(stu_);
  return stu_;
}

static double get_finsaldo(grb_,dt_sal_)
long grb_;
uint16 dt_sal_;
{
  int16 yy_,mm_,dd_,mode_;
  uint16 dat_1_1,dt_b_;
  double saldo_;
 
  scrget(1,7);scrupd(-3,0);
  jddate(dt_sal_,&yy_,&mm_,&dd_); yy_%=100;
  yy_%=100; if(mnd_strt>mm_) yy_--; if(yy_<0) yy_=99;/* jaar 2000 */
  dat_1_1=datejd(yy_,mnd_strt,1);/* 1/1 van gevraagd boekjaar */

  saldo_=0;
  fasinit(3);*l(3,2)=grb_;faskeyi(3,1,0);
  if(dat_1_1<last_arc+1){
    fasinit(5);*u(5,2)=*u(3,1)+60000;
    if(faskeyi(5,1,0)==0){
      saldo_=*d(5,31)+ *d(5,32);
    }
    dt_b_=last_arc+1;
  }
  else dt_b_=dat_1_1;

  fasinit(4); mode_=1;
  *l(4,6)=grb_;
  FOREVER{
    if(faskeyi(4,3,mode_)) break; mode_=2;
    if(*l(4,6)!=grb_) break;
    if(*u(4,4)>=dt_b_ && *u(4,4)<=dt_sal_) saldo_+=*pd_4_32;
  }
  return saldo_;
}

static initload()
{
  int16 g,k;
  
  fasunlck(0);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  if(credt_allow) fileopen(1);
  if(debit_allow) fileopen(2);
  for(k=3;k<=5;k++) fileopen(k);
	zero((char *)tb_grbnotfound,sizeof tb_grbnotfound);notfound=0;
  for(k=0;k<80;k++){
    sysget(10240+k*80,4,(char *)&j_tab[k]);
    sysget(10240+20+k*80,22,(char *)&j_tab[k].lastnr);
    sysget(10286+k*80,1,&j_tab[k].mast_munt);
    sysget(10287+k*80,8,&j_tab[k].e_saldo);

    if(NO /*j_tab[k].typ==7*/) zeros((char *)&j_tab[k],sizeof j_tab[0]);
    else j_tab[k].recnr=getgrb(j_tab[k].fingrb);
  }

  for(g=0;g<15;g++){
    sysget(788+g*4,4,&df_grb[g]);
    df_recnr[g]=getgrb(df_grb[g]);
  }

  chk_btoeg=0;
  sysget( 780,4,&levcent);getgrb(levcent);
  sysget( 784,4,&kltcent);getgrb(kltcent);
  chk_btoeg=1;
  sysget(1201,4,&grb_d_ak);
  if(grb_d_ak==0 || grb_d_ak==-1) {errnum=16; ovlexit(-1);}
  rec_d_ak=getgrb(grb_d_ak);
  sysget(1205,4,&grb_d_vk);
  if(grb_d_vk==0 || grb_d_vk==-1) {errnum=16; ovlexit(-1);}
  rec_d_vk=getgrb(grb_d_vk);
  sysget(1209,4,&grb_d_fi);
  if(grb_d_fi==0 || grb_d_fi==-1) {grb_d_fi=0;rec_d_fi=0;}
  else rec_d_fi=getgrb(grb_d_fi);
  if(notfound){
		errnum=2;
		scrnum=0;scrget(1,170);
		for(k=0;k<notfound && k<15;k++) scrifld(k+1,fm_ogrb,&tb_grbnotfound[k]);
		scrifld(18,fm_os63,"      Druk F8 om terug te keren ....");
    scrupd(-1,0x80);
    ovlexit(-1);
  }

  sysget( 294,4,def_munt);
  sysget( 298,2,&vers_298);
  sysget(1008,16,(char *)btwpct);
	sysget(1727,2,&PandJournaal); if(ovltest(71)==0 || fldlen(4,40)==0 || fldlen(4,41)==0) PandJournaal=0;
  sysget(1818,2,&sys1818);
  sysget(1836,4,&afw_long);
  sysget(1840,2,&sys1840);
  sysget(1850,2,&sys1850);
  sysget(1862,2,&sys1862);
  sysget(1858,2,&last_arc);
  sysget(1866,2,&mnd_strt);
  sysget(1918,2,&sear_stt);
  sysget(2212,4,talen);
  sysget(2222,2,&def_qfak);
	sysget(2300,2,&MinBkhDatum);if(MinBkhDatum<last_arc) MinBkhDatum=last_arc;
  sysget(3876,2,&sys3876);
  len4_0=fldlen(4,0);
  analyt=fldlen(4,11);

	for(k=0;k<80;k++){
		if(DefAkJournaal==0 && j_tab[k].typ==1) DefAkJournaal=j_tab[k].nr;
		if(DefVkJournaal==0 && j_tab[k].typ==2) DefVkJournaal=j_tab[k].nr;
		if(DefAkJournaal && DefVkJournaal) break;
  }


  pd_4_32=d(4,32);
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

static uint16 getgrb(lgrb)
long lgrb;
{
  uint16 retcd=0;

  if(*(char *)&lgrb!=0xFF && *(char *)&lgrb!=0x00 && scrcount<23){
    *l(3,2)=lgrb;
    *u(3,1)=0;
    search(3,2);
    if(errnum) tb_grbnotfound[notfound++]=lgrb;
    else{
      retcd=*u(3,1)+60000;
    }
  }
  return retcd;
}
 

static anal_det(nr_)
int16 nr_;
{
  int16 k,z,key,curs=1;
  uint16 rec_;
  double bd_,afrond_;

  rec_=*u(3,1);
	LoadAnalDetail(nr_);
  zeros((char *)anal_pct,sizeof anal_pct);
  zeros(&anal_onm[0][0],sizeof anal_onm);
  if(fldlen(3,33)){                /* 1-ste keer default percentages zetten */
    for(k=0;k<DIMA;k++){
      if(fldlen(3,33+k*2) && *l(3,33+k*2) && tba[ny+k].a_rec_nr==0){
				anal_pct[k]=*f(3,32+k*2);tba[ny+k].a_grbrek=*l(3,33+k*2);
      }
    }
    for(k=0;k<DIMA;k++){
      if(tba[ny+k].a_grbrek && tba[ny+k].a_rec_nr==0){
				fasinit(3);*l(3,2)=tba[ny+k].a_grbrek;
				if(faskeyi(3,1,0)==0) tba[ny+k].a_rec_nr=*u(3,1)+60000;
				else tba[ny+k].a_grbrek=0;
      }
    }
  }
									
  for(k=0;k<DIMA;k++){
    if(tba[ny+k].a_rec_nr){
      fasinit(3);*u(3,1)=tba[ny+k].a_rec_nr-60000;fasgeti(3);
			tba[ny+k].a_grbrek=*l(3,2);
      makename(anal_nm[k]);
    }
    else zeros(anal_nm[k],sizeof anal_nm[0]);
		copy(anal_nm[k],anal_onm[k],sizeof anal_nm[0]);
  }
  FOREVER{
    redo:
    scrget(1,44);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_ou2,&journl);
    scrifld(z++,fm_ou5,&volgnr);
    scrifld(z++,fm_odat,&bkh_dt);
    scrifld(z++,fm_os38,lkgnaam);
    scrifld(z++,fm_od9_2,&bd_inp);
    for(k=0;k<DIMA;k++){
      scrifld(z++,fm_ud8_2,&tba[ny+k].a_bedrag);
      scrifld(z++,fm_uf3_2,&anal_pct[k]);
      scrifld(z++,fm_us30,anal_nm[k]);
    }
    key=scrupd(curs,0x4C1);curs=1;
    if(key==111) ovlexit(-1);
/* bedragen */
    bd_=0; afrond_=0.01; if(valtype=='F') afrond_=1.;
    for(k=0;k<DIMA;k++){
      if(tba[ny+k].a_bedrag==0) tba[ny+k].a_bedrag=bd_inp*anal_pct[k]/100.;
      tba[ny+k].a_bedrag=valu_cnv(munt,munt,tba[ny+k].a_bedrag,afrond_);
      bd_+=tba[ny+k].a_bedrag;
    }
    if((bd_-bd_inp)>=-5 && (bd_-bd_inp)<=5){
      for(k=0;k<DIMA;k++) if(tba[ny+k].a_bedrag) break;
      if(k!=DIMA) tba[ny+k].a_bedrag-=bd_-bd_inp;
    }
    else{
      if(absdoubl(bd_)>absdoubl(bd_inp)){errnum=67;goto redo;}
      if(sys1850){
	if(absdoubl(bd_)<absdoubl(bd_inp)){errnum=70;goto redo;}
      }
    }
/* controle grb rekeningnamen */
    for(k=0;k<DIMA;k++){
      if(tba[ny+k].a_bedrag && anal_nm[k][0]=='\0'){
				errnum=38;curs=9+k*3;goto redo;
      }
      if(cmpstr(anal_onm[k],anal_nm[k],sizeof anal_nm[0])){
				if(anal_nm[k][0]){
					copy(anal_nm[k],s(3,3),fldlen(3,3));
					if(search(3,0) && errnum==0)errnum=39;
					if(errnum){curs=9+k*3;goto redo;}
					makename(anal_nm[k]);
					if(g_anal_tst()==NO) {errnum=68;curs=9+k*3;goto redo;}
					tba[ny+k].a_grbrek=*l(3,2);
					tba[ny+k].a_rec_nr=*u(3,1)+60000;
				}
				copy(anal_nm[k],anal_onm[k],sizeof anal_nm[0]);
      }
			tba[ny+k].a_elem=nr_;
    }
    if(key==101 || key==108) break;
  }
	for(k=0;k<DIMA;k++) if(tba[ny+k].a_bedrag) break;
	if(k<DIMA) anal_ask='X'; else anal_ask='\0';
  *u(3,1)=rec_;fasgeti(3);
}


static LoadAnalDetail(nr_) // analytisch detail terug op einde van tabel zetten 
{

	int j,k,pa_;

	for(k=0;k<DIMA;k++) zero(&tba[DIMAT+k].begin,sizeof tba[0]);
	pa_=0;
	for(k=0;k<DIMAT;k++){
		if(tba[k].a_elem==nr_ && tba[k].a_rec_nr){
			copy((char *)&tba[k].begin,(char *)&tba[DIMAT+pa_].begin,sizeof tba[0]);pa_++;
			for(j=k+1;j<DIMAT;j++){
				copy((char *)&tba[j].begin,(char *)&tba[j-1].begin,sizeof tba[0]);
			}
			zero((char *)&tba[DIMAT-1].begin,sizeof tba[0]);
			if(pa_>=DIMAT) break;
		}
	}
	for(ny=DIMAT-1;ny>=0;ny--) if(tba[ny].a_rec_nr) break;  ny++;
	for(k=0;k<pa_;k++)	copy((char *)&tba[DIMAT+k].begin,(char *)&tba[ny++].begin,sizeof tba[0]);
}
  
static g_anal_tst()
{
  if(!analyt || ((*s(3,2) &0xF0)>>4)!=9) return NO;
  return YES;
}

static scrxfld(pz,upd,pd,muntdisp)
int16 *pz;
double *pd;
flag upd,muntdisp;
{
  char fmt_[40];

  copy(fm_od9_2,fmt_,sizeof fmt_);
  if(upd) fmt_[1]|=0x40;/* update */
  scrifld((*pz)++,fmt_,pd);
  if(muntdisp) scrifld(*pz,fm_os3,munt);
  (*pz)++;
}

static double absdoubl(bd_)
double bd_;
{
  if(bd_>=0) return bd_;
  else return -bd_;
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static makename(pd)
char *pd;
{
  int16 g,h;
  char *ps;
  g=fldlen(3,3);if(g>MAXLEN-1)g=MAXLEN-1;
  h=MAXLEN-1;
  ps=s(3,3);
  while(g--){
    if(*ps==0)break;
    *pd++=*ps++;
    h--;
  }
  while(h--){
    *pd++=' ';
  }
  *pd='\0';
  pd=pd-8;
  grb_deco(pd,l(3,2));
}

static zeros(pd,len)
char *pd;
int16 len;
{
  int16 k;

  for(k=0;k<len;k++) *(pd+k)='\0';
}

static scraddf(fld,v,h,attr)
int16 fld,v,h,attr;
{
  int16 *pi;
				
  pi = (int16 *)info;
  *(pi+0) = fld;
  *(pi+1) = v;
  *(pi+2) = h;
  *(pi+3) = attr;
  sendtask(procid+20,3,11,info,8);
  scrnum=0;
}

static scr_ok(ptxt)
char *ptxt;
{
  int16 key;

  scrget(1,169);
  scrifld(12,fm_os63,ptxt);
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  return NO;
}

static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
  if(stu_<=3) parmcall[1]=7;/*  bits : 0 = display, 1=update, 2=add */
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

