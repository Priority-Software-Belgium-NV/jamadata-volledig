/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0297GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0297dat
#define ovlcod DRK0297cod
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


static uint16 get_date();char ovldat[] = "drk0297  00:01 28/09/10 (c) Jamadata";
                      // PDA-programma's V.A.M 

// FLAGCOC : geen verkopers hier, hebben eigen param.

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_ARTSTOCK    10000
#define DIM_TBVK        500
#define LEN_LOGLINE     (long)75
#define MAXFLD          100
#define DIMBTW          8

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

extern char *s();
extern int16 *i();
extern uint16 *u(),datejd();
static uint16 get_date();
extern long *l();
extern long val();
extern float *f();
static float get_num(),get_bstk();
extern double *d(),valu_cnv();
static double round();
static char *p_data,*rec_ele();
static long *pl_80_1;

static int16 stu=6,free;
static int16 lvcd,klcd;

static char fm_os80[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us25[]  = {7,0xC8,25,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us16[]  = {7,0xC8,16,0,0,0,0};
static char fm_us10[]  = {7,0xC8,10,0,0,0,0};
static char fm_us5[]   = {7,0xC8,5,0,0,0,0};
static char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
static char fm_us2U[]  = {7,0xC8,2,0,1,0,0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_ou5[]   = {6,0x91,5,0,0x60,0};
static char fm_ou3[]   = {6,0x91,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD1,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD1,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD1,2,0,0x60,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_uf3_1[] = {6,0xD4,3,1,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_uf21_[] = {6,0xD4,2,1,0x20,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_of5_0[] = {6,0x94,5,0,0x60,0};
static char fm_of5_2[] = {6,0x94,5,2,0x70,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_obd[]   = {6,0x95,6,2,0x70,0};                             /* od6_2 */
static char fm_ubd[]   = {6,0xD5,6,2,0x70,0};                             /* ud6_2 */
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,1,0,'A','A','N','N',0};
static char fm_uNAS[] = {13,0xC8,1,0,0x09,0,'A','A','N','N','S','S',0};
static char fm_uONA[] = {13,0xC8,1,0,1,0,'A','A','N','N','O','O',0};
static char fm_u_ALN[]= {13,0xC8,1,0,0x09,0,'A','A','L','L','N','N',0};
static char fm_us6_09[] = {9,0xC8,6,0,1,0,'0','9',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
 
static char sys3896[6],fmt[40];
static char logfile[80],filnam[80],oldnm[50],def_munt[4];
static char wis_eerst,nm_fil[10],add_bstk;
static int16 form_dat[8],pr_mode,prtnr,inq_loc=99,p_tr_stuk,p_tr_bak;
static uint16 dat_beg,dat_end,sys3772,sys4470, dt_bonb,dt_bone;
static uint16 inq_lev,inq_art,inq_groep,pda_nr;
static flag sys3894,sys3618,sys3978,sys1790,sys4408,prt2pdf;
static flag chk_btoeg=NO,arcd=YES;
static flag sear_stt,sys3876, sgrp_used,slev_used,p_max_grp;
static float sys3614,*pf_6_28,ArtPdaStock[DIM_ARTSTOCK];
static uint16 sys4436;

static uint16 *pu_6_1,cnt_good,cnt_bad;
static uint16 negatief;

static char nm_loc[10][6], firma[256];

static int16 def_taal;
static double btw_bas[DIMBTW+1],btw_bd[DIMBTW+1];
static double AW,VW,winst,tot_aw,tot_vw,qlv,tot_qlv,winstbd;
static float btw_pct[DIMBTW],winstpct;

extern int16 ilength;
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol,Prt2Xls;
static int16 *pi;
static char SelectXlsFldNr[150];
static int16 StylTotaal, StylGrpTot, StylKlasse, StylNormal, StylDate, StylTitel, Styl2Use;

static struct{
  uint16 rec;
  float aantal;
  float bedrag;
} tb_toervk[DIM_TBVK];


static struct{
  uint16 rec;
  char select;
} tbgr[100];

static struct{
  char code[2];
  char naam[10];
} verkoper[10];


ovlcod(parmval)
int16 parmval;
{
  int16 curs=1,key,z;
  char choice;
									
  initload();
	if(parmval==1){read_inv();goto endsr;}
	if(parmval==2){exec_toervk();goto endsr;}
  
	FOREVER{
		redo:;
    scrget(2,269);z=1;scraddpicto(50,0,78,7,2,1,105,1,7,"^!B0297B");
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) goto endsr;
    if(key==111) ovlexit(*u(25,4));
    switch(choice){
      case '1': if((sys4436 & 0x01) && fldlen(6,33)) read_inv(); else errnum=12; break;
      case '2': read_barc(); break;
      case '3': if(sys4436 & 0x200) exec_toervk(); else errnum=12; break;
			case '4': PrintStockVerschillen(); break;
      case '5': p_dbl_ean(); break;
			case 'A': DeleteMobstock(); break;
      case '+': param(); break;
      case 'K': ovlexit(293); break;
      default : errnum=34; break;
    }
  }
  endsr:;
  fasclos(-2);
  ovlexit(-1);
}

#include "Std\XlsFunc.c"

static exec_toervk()
{
  int16 z,curs=2;
	int key;

  copy("MoblogTV.dat",logfile,25);fasinit(6);inq_art=0;

  FOREVER{
    fasinit(6); if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
    redo:;
    scrget(2,320);z=1;// scraddpicto(1,0,76,22,4,2,583,0,0,"maak PDF"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&pda_nr);
    scrfld(z++,6,3);
#if FLAGKEE
		AddTextKey(z++,45,22,25,2,10001,"Druk totaallijst en\nverwerk filiaalstock",0xFF);
#endif
    key=scrupd(curs,0x0381);curs=3;
		prt2pdf=YES;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if((key/0x10000)>0) key/=0x10000;
//    if(key==5001){prt2pdf=YES; key=108;} // pdf
    if(key==101) break;
		if(dat_beg==0){errnum=38;curs=2;goto redo;}
		if(dat_end==0 || dat_end<dat_beg){errnum=38;curs=3;goto redo;}
		if(pda_nr<1 || pda_nr>10 || fldlen(66,11+pda_nr*15)==0){errnum=38;curs=4;goto redo;}
    if(*s(6,3)){
      if(search(6,0)){curs=5;goto redo;}
    } else fasinit(6);
    inq_art=*u(6,1);
    fasclos(-2);mk_pdaname(4410,logfile);
    if(fasopen(filnam,1)){
      errnum=1; curs=4; goto redo;
    }
#if FLAGKEE
		if(key==10001) print_toervk(YES);
#endif
    if(key==108) print_toervk(NO);
    if(key==110) disp_toervk();
  }
}

static print_toervk(fl_boeken_)/* afdrukken toerverkoop */
int16 fl_boeken_;
{
  int16 mode_=0,len_,z,k,j,nr_,max_art_;
  uint16 dt_;
  char stuksfl_;
  float qlv_,fls_,bak_,rd_stock_,bedrag_,prx_;
									
  scrget(1,6);scrupd(-3,0);
  zero(&tb_toervk[0].rec,sizeof tb_toervk);

  fasinit(80);cnt_good=0;cnt_bad=0;max_art_=0;
  FOREVER{
    next:;
    if(read_rec(mode_)) break;mode_=1;
    fasinit(6);
    len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) goto next;
    if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0) goto next;
    dt_=get_date(0);
    if(dat_beg && dt_<dat_beg) goto next;
    if(dat_end && dt_>dat_end) goto next;
    qlv_=get_num(3); if(qlv_==0) goto next;
    if(sys4408){
      *pu_6_1=val(s(6,2));
      if(*pu_6_1) k=fasgeti(6); else k=1;
    }
    else k=faskeyi(6,1,0);
    if(k) goto next;
    if(inq_art && inq_art!=*u(6,1)) goto next;
    get_str(&stuksfl_,4,1);
    if(stuksfl_=='P' && fldlen(6,83)==0) stuksfl_='N';
    else if(stuksfl_!='J' && stuksfl_!='P') stuksfl_='N';
    if(stuksfl_=='P' && *f(6,83)!=0) qlv_*=*f(6,83);
    bak_=0;fls_=0; if(stuksfl_=='J') fls_=qlv_; else bak_=qlv_;
    rd_stock_=0;stks2stock(&rd_stock_,*f(6,31),bak_,fls_);
/*  if(stuksfl_=='J') nr_=p_tr_stuk; else nr_=p_tr_bak; */
    nr_=p_tr_bak; prx_=*f(6,PrNrs[nr_]);
    if(stuksfl_=='J' && *f(6,31)>1){
      prx_=valu_cnv("EUR","EUR",(double)(prx_/ *f(6,31)),(double)(0.05));
    }
    bedrag_=qlv_* prx_;
    if(sys3894 & (1<<nr_)) bedrag_/=1.+ *pf_6_28/100.;

    for(j=0;j<DIM_TBVK;j++){
      if(tb_toervk[j].rec ==0 || tb_toervk[j].rec==*u(6,1)) break;
    }
    if(j<DIM_TBVK){
      tb_toervk[j].rec=*u(6,1);
      tb_toervk[j].aantal+=rd_stock_;
      tb_toervk[j].bedrag+=bedrag_;
      if(j>max_art_) max_art_=j;
    }
  }
  fasclos(-2);


  getsysprNew(5,form_dat,&pr_mode,&prtnr); if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  free=999;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,25);
  prttext("<t27b>Toerverkopen, pda ");prtifld(fm_uu2,&pda_nr,-1);
  prttext("<b><t53>");prtifld(fm_udat,&dat_beg,-1);
  prttext(" - ");prtifld(fm_udat,&dat_end,-1);
  prttext("<t73>");prttext("Blz.<ppp>");
  prtbuf(1);
  z=1;
  prttab(z,6,2,2,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,1,-1); prttitle(z++,"Omschrijving",3);
  prtitab(z,fm_uf5_2,&qlv_,1,-1); prttitle(z++,"Aantal",0x13);
  prtitab(z,fm_ud7_2,&VW,2,-1); prttitle(z++,"V.waarde",0x13);
  prtbuf(3);
  p_pdfname("Toerverkopen",dat_beg,dat_end);
  

  zero((char *)&btw_bas[0],sizeof btw_bas);
  tot_qlv=0;tot_aw=0;tot_vw=0;
  fasinit(6);
  FOREVER{
    next_art:;
    if(faskeyi(6,2,2)) break;
    for(j=0;j<max_art_+1;j++) if(*u(6,1)==tb_toervk[j].rec) break;
    if(j>max_art_) goto next_art;
    qlv_=tb_toervk[j].aantal;
    AW=qlv_* *f(6,18);
    VW=tb_toervk[j].bedrag;
    if(*i(6,9)==99) k=DIMBTW;
    else {
      for(k=0;k<DIMBTW;k++) if(btw_pct[k]==*pf_6_28) break;
    }
    btw_bas[k]+=VW;
    winst=VW-AW;if(AW) winstpct=winst/AW*100;  else winstpct=0;
    for(k=0;k<20;k++) prtinfo(k,0);nextline();
    tot_qlv+=qlv_;tot_aw+=AW;tot_vw+=VW;
  }
  fasinit(6); copy("T O T A A L   ===>",s(6,3),19);
  qlv=tot_qlv;
  AW=tot_aw;
  VW=tot_vw;
  winst=VW-AW;if(AW) winstpct=winst/AW*100; else winstpct=0;
  nextline();for(k=0;k<20;k++) prtinfo(k,2);nextline();
  prt_btwtab();
  prtclose();
#if FLAGKEE
	if(fl_boeken_){
		if(scr_ok("Wenst u deze toerverkopen in te boeken in de filiaalstock?")!=YES) goto endsr;
    for(k=0;k<max_art_+1;k++){
			fasinit(66);*u(66,2)=tb_toervk[k].rec;
			if(faskeyi(66,1,0)) {fasinit(66);*u(66,2)=tb_toervk[k].rec;errnum=fasadd(66);}
			*f(66,11+(pda_nr-1)*15)-=tb_toervk[k].aantal;
			*f(66,17+(pda_nr-1)*15)+=tb_toervk[k].aantal;
			if(fldlen(66,18+(pda_nr-1)*15)) *f(66,18+(pda_nr-1)*15)+=tb_toervk[k].aantal;
			if(fldlen(66,19+(pda_nr-1)*15)) *u(66,19+(pda_nr-1)*15)=dat_end;
			fasupd(66);
		}
	}
#endif
  endsr:;
}

static prt_btwtab()
{
  int16 j,k;
  double bedrag_,btw_tot_,belastbt_;

  zero((char *)&btw_bd[0],sizeof btw_bd);
  nextline();
  prttext("<u>BTW tabel<u>");nextline();nextline();

  btw_tot_=0; belastbt_=0;
  for(k=0;k<DIMBTW;k++){
    btw_bas[k]=valu_cnv("EUR","EUR",(double)btw_bas[k],(double)0.01);
    if(btw_bas[k]){
      belastbt_+=btw_bas[k];
      bedrag_=valu_cnv("EUR","EUR",(double)(btw_bas[k]*btw_pct[k]/100.),(double)0.01);
      btw_tot_+=bedrag_;btw_bd[k]+=bedrag_;
    }
  }
  for(j=0;j<4;j++){
    switch(j){
      case 0 : prttext("       "); break;
      case 1 : prttext("Basis  "); break;
      case 2 : prttext("Btw    "); break;
      default: nextline();prttext("<b>Totaal "); break;
    }
    for(k=0;k<DIMBTW;k++){
      if(btw_bas[k]){
	if(j==0){prttext("    <u>");prtifld(fm_uf21_,&btw_pct[k],-1);prttext(" %<u> ");}
	else{
	  if(j==1) bedrag_=btw_bas[k];
	  if(j==2) bedrag_=btw_bd[k];
	  if(j==3) bedrag_=btw_bas[k]+btw_bd[k];
	  prtifld(fm_obd,&bedrag_,-1);prtblank(1);
	}
      }
    }
    if(j==0){
      prttext("<t55>Leeggoed:");
      bedrag_=btw_bas[DIMBTW];
    }
    else if(j==1){
      prttext("<t55>Goederen:");
      bedrag_=belastbt_;
    }
    else if(j==2){
      prttext("<t57>B.T.W.:");
      bedrag_=btw_tot_;
    }
    else {
      prttext("<t57>TOTAAL:");
      bedrag_=btw_tot_+belastbt_+btw_bas[DIMBTW];
    }
    prttext("<t69>");prtifld(fm_obd,&bedrag_,-1);
    nextline();
  }
}

static disp_toervk()
{
  int16 j,k,len_,len1_,z,key,mode_,max_;
  char date_str_[15],time_str_[15],stuksfl_,str_[25];
  uint16 dt_,goto_end_=NO;
  float qbak_,qfles_;
  long fpos,start,beg_start;

  fpos=0;start=0;max_=30000;fasinit(80);mode_=0;
  for(beg_start=0;beg_start<max_;beg_start++){
    next1:;
    if(read_rec(mode_)) {max_=beg_start;break;} mode_=1;
    fasinit(6);
    len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) continue;
    dt_=get_date(0);
    if(dat_beg && dt_<dat_beg) continue;
    if(dat_end && dt_>dat_end) continue;
    if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0){
      if(inq_art) continue;
    }
    else{
      if(sys4408){
	*pu_6_1=val(s(6,2));
	if(*pu_6_1) k=fasgeti(6); else k=1;
      }
      else k=faskeyi(6,1,0);
      if(inq_art && inq_art!=*u(6,1)) continue;
    }
    break;
  }
  fpos=0;start=beg_start;max_=30000;fasinit(80);mode_=0;
  FOREVER{
    redo:;
    fpos=(long)(start)*LEN_LOGLINE;fasinit(80);*pl_80_1=fpos;mode_=0;
    scrnum=0; scrget(2,277);z=1;scraddpicto(1,0,76,22,4,2,583,0,0,"maak PDF"); 
    for(j=start;j<start+18;j++){
      next:;
      if(read_rec(mode_)) {max_=j;break;} mode_=1;
      fasinit(6);
      len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) goto next;
      dt_=get_date(0);
      if(dat_beg && dt_<dat_beg) goto next;
      if(dat_end && dt_>dat_end) goto next;
      qbak_=0;qfles_=0;
      if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0){
				if(inq_art) goto next;
				copy("--------------------------",s(6,3),30);
				len_=get_str(str_,5,10); len1_=get_str(&str_[10],6,10);
				if(len_ || len1_){
					*(s(6,3)+4)=' '; copy(str_,s(6,3)+5,len_);len_+=5;
					copy(" / ",s(6,3)+len_,3);len_+=3;
					copy(&str_[10],s(6,3)+len_,len1_);*(s(6,3)+len_+len1_)=' ';
				}
				else{
  				len_=get_str(str_,3,10); // PDA-nummer
	  			if(len_){
		  			*(s(6,3)+9)=' '; copy(str_,s(6,3)+10,len_);*(s(6,3)+10+len_)=' ';
			  	}
				}
      }
      else{
				if(sys4408){
					*pu_6_1=val(s(6,2));
					if(*pu_6_1) k=fasgeti(6); else k=1;
				}
				else k=faskeyi(6,1,0);
				if(inq_art && inq_art!=*u(6,1)) goto next;
				qbak_=get_num(3);
				get_str(&stuksfl_,4,1);
				if(stuksfl_=='P' && fldlen(6,83)==0) stuksfl_='N';
				else if(stuksfl_!='J' && stuksfl_!='P') stuksfl_='N';
				if(stuksfl_=='J'){ qfles_=qbak_;qbak_=0;}
				else if(stuksfl_=='P' && *f(6,83)!=0){qbak_*=*f(6,83);qfles_=0;}
				else qfles_=0;
      }
      len_=get_str(date_str_,0,10); date_str_[len_]='\0';
      len_=get_str(time_str_,1,10); time_str_[len_]='\0';
      scrifld(z++,fm_os10,date_str_);
      scrifld(z++,fm_os5,time_str_);
      scrofld(z++,6,2,-1);
      scrofld(z++,6,3,-1);
      scrifld(z++,fm_of5_0,&qbak_);
      scrifld(z++,fm_of5_0,&qfles_);
    }
    if(max_==j && goto_end_==YES) goto_end_=NO;
    if(goto_end_ && max_>j) key=103;
    else key=scrupd(-1,0x1AF);
		prt2pdf=NO;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==5001){prt2pdf=YES; prt_tr_input(); break;} // pdf
    if(key==101) break;
    if(key==104 && start<max_-18){goto_end_=YES;key=103;}
    if(key==102){
      start-=18;if(start<beg_start) start=beg_start;
    }
    if(key==103) {
      start+=18;if(start>=max_-18) start=max_-18;
      if(start<beg_start) start=beg_start;
    }
    if(key==109){
      if(scr_ok("Wenst U echt deze lijst af te drukken ?")){
				prt_tr_input(); break;
      }
    }
    if(start<beg_start) start=beg_start;
  }
  endsr:;
}

static prt_tr_input()
{

  int16 k,len_,len1_,z,mode_,nr_;
  char date_str_[15],time_str_[15],stuksfl_,str_[25];
  uint16 dt_;
  float qbak_,qfles_,prx_,bedrag_;

  getsysprNew(5,form_dat,&pr_mode,&prtnr); if(prt2pdf) PrintPaperNr=0;
  if ((errnum=prtopen(prtnr,form_dat,6,96,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t30b>Detail toerverkopen, pda ");
  prtifld(fm_uu2,&pda_nr,-1);
  prttext("<b><t60>");prtifld(fm_udat,&dat_beg,-1);
  prttext(" - ");prtifld(fm_udat,&dat_end,-1);
  prttext("<t89>Blz.<ppp>.");
  prtbuf(1);z=1;
  prtitab(z,fm_os10,date_str_,2,-1); prttitle(z++,"Datum",3);
  prtitab(z,fm_os5,time_str_,2,-1); prttitle(z++,"Uur",3);
  prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,1,-1); prttitle(z++,"Omschrijving",3);
  prtitab(z,fm_of5_0,&qbak_,4,-1); prttitle(z++,"Aantal",0x13);
  prtitab(z,fm_of5_0,&qfles_,4,-1); prttitle(z++,"Fls/Stk",0x13);
  prtitab(z,fm_uf5_2,&prx_,2,-1); prttitle(z++,"Prijs",0x13);
  prtitab(z,fm_uf5_2,&bedrag_,2,-1); prttitle(z++,"Bedrag",0x13);
  prtbuf(3);
  p_pdfname("Detail toerverkopen",dat_beg,dat_end);
  fasinit(80); mode_=0;
  FOREVER{
    next:;
    if(read_rec(mode_)) break; mode_=1;
    fasinit(6);
    len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) goto next;
    dt_=get_date(0);
    if(dat_beg && dt_<dat_beg) goto next;
    if(dat_end && dt_>dat_end) goto next;
    qbak_=0;qfles_=0;prx_=0;bedrag_=0;
    if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0){
      if(inq_art) goto next;
      copy("--------------------------",s(6,3),30);
      len_=get_str(str_,5,10); len1_=get_str(&str_[10],6,10);
      if(len_ || len1_){
				*(s(6,3)+4)=' '; copy(str_,s(6,3)+5,len_);len_+=5;
				copy(" / ",s(6,3)+len_,3);len_+=3;
				copy(&str_[10],s(6,3)+len_,len1_);*(s(6,3)+len_+len1_)=' ';
      }
			else{
  				len_=get_str(str_,3,10); // PDA-nummer
	  			if(len_){
		  			*(s(6,3)+9)=' '; copy(str_,s(6,3)+10,len_);*(s(6,3)+10+len_)=' ';
			  	}
				}
    }
    else{
      if(sys4408){
				*pu_6_1=val(s(6,2));
				if(*pu_6_1) k=fasgeti(6); else k=1;
      }
      else k=faskeyi(6,1,0);
      if(inq_art && inq_art!=*u(6,1)) goto next;
      qbak_=get_num(3);
      get_str(&stuksfl_,4,1);
      if(stuksfl_=='P' && fldlen(6,83)==0) stuksfl_='N';
      else if(stuksfl_!='J' && stuksfl_!='P') stuksfl_='N';
      if(stuksfl_=='J'){ qfles_=qbak_;qbak_=0;}
      else if(stuksfl_=='P' && *f(6,83)!=0){qbak_*=*f(6,83);qfles_=0;}
      else qfles_=0;
#if 0
      if(stuksfl_=='J') nr_=p_tr_stuk; else nr_=p_tr_bak;
      prx_=*f(6,PrNrs[nr_]); bedrag_=(qfles_+qbak_)* prx_;
#endif
      nr_=p_tr_bak; prx_=*f(6,PrNrs[nr_]);
      if(stuksfl_=='J' && *f(6,31)>1){
	prx_=valu_cnv("EUR","EUR",(double)(prx_/ *f(6,31)),(double)(0.05));
      }
      bedrag_=(qfles_+qbak_) * prx_;
    }
    len_=get_str(date_str_,0,10); date_str_[len_]='\0';
    len_=get_str(time_str_,1,10); time_str_[len_]='\0';
    for(k=0;k<20;k++) prtinfo(k,0); nextline();
  }
  prtclose();
  endsr:;
}

static read_barc()
{
  int16 key,z,curs=1;

  copy("moblogIN.dat",logfile,25);
  FOREVER{
    redo:;
    scrget(2,271);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_us30,logfile);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&pda_nr);
    key=scrupd(curs,0x0419);curs=1;
    if(key==111) ovlexit(*u(25,4));
    if(key==101 || key==105) break;
    fasclos(-2);
    mk_pdaname(4410,logfile);if(fasopen(filnam,1)){
      errnum=1; curs=2; goto redo;
    }
    if(key==104){
      if(scr_ok("Wenst U echt de opgenomen barcodes in te vullen op artikelfiches ?")==NO) break;
      exec_mbar(); fasclos(-2);
    }
  }
}

static exec_mbar()/* inlezen genoteerde stock */
{
  uint16 dt_;
  int16 mode_=0,len_,len1_,k,mode64_,ok_;
	char b_ean_[15],s_ean_[15];
									
  getsysprNew(5,form_dat,&pr_mode,&prtnr); if(prt2pdf) PrintPaperNr=0;
  if ((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t33b>Niet gevonden artikels");
  prttext("<b><t55>"); prtfld(25,2,-1); prttext("<t72>Blz.<ppp>.");
  prtbuf(1);
  scrnum=0;scrget(1,170); scrifld(2,fm_os38,"Verwerken artikel : ");scrupd(-3,0);
  fasinit(80); cnt_good=0;cnt_bad=0;
  FOREVER{
    next:;
    if(read_rec(mode_)) break;mode_=1;
    fasinit(6);
    len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) goto next;
    if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0) goto next;
    dt_=get_date(0);
    if(dat_beg && dt_<dat_beg) goto next;
    if(dat_end && dt_>dat_end) goto next;
    len_=get_str(b_ean_,5,fldlen(6,70));
    len1_=get_str(s_ean_,6,fldlen(6,71));
		if(len_<8 && len1_<8) goto next; // geen geldige barcodes
    if(sys4408){
      *pu_6_1=val(s(6,2));
      if(*pu_6_1) k=fasgeti(6); else k=1;
    }
    else k=faskeyi(6,1,0);
		if(fldlen(64,1)==0){
      len_=get_str(s(6,70),5,fldlen(6,70));
      len1_=get_str(s(6,71),6,fldlen(6,71));
		}
		else{
			zero(b_ean_,sizeof b_ean_);len_=get_str(b_ean_,5,fldlen(6,70));
			if(len_){
				fasinit(64);copy(b_ean_,s(64,2),len_);mode64_=1; ok_=NO;
				FOREVER{
					if(faskeyi(64,1,mode64_)) break; mode64_=2;
					if(cmpstr(b_ean_,s(64,2),len_)==0){copy(b_ean_,s(64,2),fldlen(64,2));*u(64,3)=*u(6,1);*u(64,5)=0;fasupd(64);ok_=YES;break;}
				}
				if(ok_==NO){
					if(*s(6,70)=='\0' || cmpstr(b_ean_,s(6,70),len_)==0) copy(b_ean_,s(6,70),fldlen(6,70));
					else{
  					fasinit(64);*u(64,3)=*u(6,1);
	  				copy(b_ean_,s(64,2),fldlen(64,2));*u(64,5)=0;
		  			fasadd(64);
					}
				}
			}
			
      zero(s_ean_,sizeof s_ean_);len1_=get_str(s_ean_,6,fldlen(6,71));
			if(len1_){
	      fasinit(64);copy(s_ean_,s(64,2),fldlen(64,3));mode64_=1; ok_=NO;
				FOREVER{
					if(faskeyi(64,1,mode64_)) break; mode64_=2;
					if(cmpstr(s_ean_,s(64,2),len1_)==0){copy(s_ean_,s(64,2),fldlen(64,2));*u(64,3)=*u(6,1);*u(64,5)=1;fasupd(64);ok_=YES;break;}
				}
				if(ok_==NO){
					if(*s(6,71)=='\0' || cmpstr(s_ean_,s(6,71),len_)==0) copy(s_ean_,s(6,71),fldlen(6,71));
					else{
  					fasinit(64);*u(64,3)=*u(6,1);
	  				copy(s_ean_,s(64,2),fldlen(64,2));*u(64,5)=1;
		  			fasadd(64);
					}
				}
			}
		}
    if(len_==0 && len1_==0) goto next;
    if(k){
      prttext("Code : ");prtfld(6,2,-1);
      prttext("EAN : ");prtfld(6,70,-1);
      prttext("EAN St : ");prtfld(6,71,-1);
      nextline();cnt_bad++;
      goto next;
    }
    scrfld(5,6,2); scrfld(6,6,3);scrfld(10,6,70);scrfld(11,6,71);scrupd(-3,0);
		if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
    fasupd(6);cnt_good++;
  }
  fasclos(-2);
  prtform(0);prtclose();
  scrnum=0;
  scrget(1,170);
  scrifld(5,fm_os63,"Aantal goed verwerkte artikels : ");
  scrifld(6,fm_ou5,&cnt_good);
  scrifld(8,fm_os63,"Aantal NIET verwerkte artikels : ");
  scrifld(9,fm_ou5,&cnt_bad);
  scrifld(15,fm_os63,"Druk op F8 om verder te gaan ... ");
  scrupd(-1,0x81);

  endsr:;
}
 
static PrintStockVerschillen()
{
  int16 key,z,curs=3,curspos_,k,mode_;
	char filedatestr_[20];
	float *p_stock_,st_pda_,st_verschil_;

  fasinit(6);inq_art=0;Prt2Xls=NO;
	zero(logfile,sizeof logfile);  copy("MobStock.dat",logfile,25);  mk_pdaname(4410,logfile);
	fasclos(-2);fasinit(80);
	fasopen(filnam,102);/* eerste call voor dir */
	fasinfo(80,204);/* ophalen antwoord van dir */
	if(*s(80,1)){
		fasinit(80);fasinfo(80,205);/* get date  */
	} else fasinit(80);
	copy(s(80,1),filedatestr_,20);
	fasclos(-2);
  inq_loc=99;copy("DEPOT",nm_fil,6);wis_eerst='N';add_bstk='N';dt_bone=*u(25,2);
  FOREVER{
    fasinit(6); if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
    redo:;
    scrget(2,384);z=1;
		scraddpicto(1,0,76,22,4,2,573,0,0,"Maak XLS"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_us30,logfile);
		scrifld(z++,fm_os20,filedatestr_);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&pda_nr);
		if(fldlen(66,11)){scrifld(-z,fm_uu2,&inq_loc);z++; scrifld(z++,fm_os6,nm_fil);}
		else z+=2;
    scrfld(z++,6,3);
    key=scrupd(curs,0x081);curs=3;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==111) ovlexit(*u(25,4));
    if(key==101) goto endsr;
    if(inq_loc==99) copy("DEPOT",nm_fil,6);
    else if(inq_loc>=1 && inq_loc<=10){
      if(fldlen(66,11+(inq_loc-1)*15) && nm_loc[inq_loc-1][0]!='\0'){
			copy(nm_loc[inq_loc-1],nm_fil,6);
      }
      else {curs=11;zero(nm_fil,6);errnum=34;goto redo;}
    }
    else {curs=11;zero(nm_fil,6);errnum=34;goto redo;}
    if(*s(6,3)){
      if(search(6,0)){curs=13;goto redo;}
    } else fasinit(6);
    inq_art=*u(6,1);
    if(key==18){
      curs=curspos_+1;goto redo;
    }
    if(sys4470 && fldlen(66,1) && inq_loc>=1 && inq_loc<=10){
      zero(logfile,sizeof logfile);
      copy("pda-",logfile,4);stcli_d(&logfile[4],(long)(inq_loc),2,0);
      copy("\\MobStock.dat",&logfile[6],14);
    }
    else{
      zero(logfile,sizeof logfile);
      copy("MobStock.dat",logfile,25);
    }
    fasclos(-2);fasinit(80);mk_pdaname(4410,logfile);
		fasopen(filnam,102);/* eerste call voor dir */
		fasinfo(80,204);/* ophalen antwoord van dir */
		if(*s(80,1)){
			fasinit(80);fasinfo(80,205);/* get date  */
		} else fasinit(80);
		copy(s(80,1),filedatestr_,20);
    if(*s(80,1)=='\0'){
      errnum=1; curs=2; goto redo;
    }
		fasclos(-2);
		Prt2Xls=NO;if(key==5001){Prt2Xls=YES;key=108;}
    if(key==108) break;
	}
  p_stock_=f(6,33);
  if(inq_loc>=1 && inq_loc<=10 && fldlen(66,11+(inq_loc-1)*15)){
    p_stock_=f(66,11+(inq_loc-1)*15);
  }
	for(k=0;k<DIM_ARTSTOCK;k++) ArtPdaStock[k]=0;
	fasopen(filnam,1);
  exec_mstk(NO); fasclos(-2);
	if(Prt2Xls){
		scrget(1,7);scrupd(-3,0);
		XlsRef=XlsCreate("Verschillen stock vs opnames.XLS");
		if(XlsRef<=0) {errnum=1;goto endsr;}

		XlsColumnSize(XlsRef,2,40);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
		StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);

		XlsRij=1;XlsKol=1;Styl2Use=StylTitel;
	  XlsWrite(XlsRef,0,XlsKol++,0,"Code",Styl2Use); 
    XlsWrite(XlsRef,0,XlsKol++,0,"Naam",Styl2Use); 
		XlsWrite(XlsRef,0,XlsKol++,0,nm_fil,Styl2Use); 
		XlsWrite(XlsRef,0,XlsKol++,0,"PDA",Styl2Use); 
		XlsWrite(XlsRef,0,XlsKol++,0,"Verschil",Styl2Use); 
		XlsRij++;
	}
	else{
		getsysprNew(5,form_dat,&pr_mode,&prtnr); if(YES) PrintPaperNr=0;
		if ((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
		scrget(1,6);scrupd(-3,0);
		prtfld(25,1,-1); prttext("<t30b>Lijst verschillen stock vs opnames<b>");
		prttext("<t72>Blz.<ppp>.");
		prtbuf(1);z=1;
		prttab(z,6,2,2,-1); prttitle(z++,"Code",3);
		prttab(z,6,3,2,-1); prttitle(z++,"Omschrijving",3);
		prtitab(z,fm_of5_2,p_stock_,2,-1); prttitle(z++,nm_fil,0x13);
		prtitab(z,fm_of5_2,&st_pda_,2,-1); prttitle(z++,"PDA",0x13);
		prtitab(z,fm_of5_2,&st_verschil_,2,-1); prttitle(z++,"Verschil",0x13);
		prtbuf(3);
		p_pdfname("Lijst verschillen stock vs opnames",dat_beg,dat_end);
	}
	fasinit(6);mode_=1;
  FOREVER{
    next:;
    if(faskeyi(6,2,mode_)) break; mode_=2;
		if(*u(6,1)>=DIM_ARTSTOCK) goto next;
    if(fldlen(66,1)){
      fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
    }
    if(/* *p_stock_==0 && */ ArtPdaStock[*u(6,1)]==0) goto next;
		st_pda_=ArtPdaStock[*u(6,1)]; st_verschil_=*p_stock_-st_pda_;
		if(Prt2Xls){
			XlsKol=1;
			WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);
			WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
			WriteVar2Xls(XlsRij,XlsKol++,fm_of5_2,p_stock_,StylNormal);
			WriteVar2Xls(XlsRij,XlsKol++,fm_of5_2,&st_pda_,StylNormal);
			WriteVar2Xls(XlsRij,XlsKol++,fm_of5_2,&st_verschil_,StylNormal);
			XlsRij++;
		}
		else{
  		for(k=1;k<20;k++) prtinfo(k,0); nextline();
		}
	}
	if(Prt2Xls) XlsClose(XlsRef,1);
  else prtclose();
	endsr:;
}


static read_inv()
{
	int16 key,z,curs=3,curspos_;
	char filedatestr_[20];

	fasinit(6);inq_art=0;
	zero(logfile,sizeof logfile);  copy("MobStock.dat",logfile,25);  mk_pdaname(4410,logfile);
	fasclos(-2);fasinit(80);
	fasopen(filnam,102);/* eerste call voor dir */
	fasinfo(80,204);/* ophalen antwoord van dir */
	if(*s(80,1)){
		fasinit(80);fasinfo(80,205);/* get date  */
	} else fasinit(80);
	copy(s(80,1),filedatestr_,20);
	fasclos(-2);
	inq_loc=99;copy("DEPOT",nm_fil,6);wis_eerst='N';add_bstk='N';dt_bone=*u(25,2);
	FOREVER{
		fasinit(6); if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
redo:;
		scrget(2,270);z=1;
		scrfld(z++,25,1);
		scrifld(z++,fm_us30,logfile);
		scrifld(z++,fm_os20,filedatestr_);
		scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
		scrifld(z++,fm_uu2,&pda_nr);
		scrifld(z++,fm_uNAS,&wis_eerst);
		scrifld(z++,fm_uONA,&add_bstk);
		scrifld(z++,fm_udat,&dt_bonb);scrifld(z++,fm_udat,&dt_bone);
		if(fldlen(66,11)){scrifld(-z,fm_uu2,&inq_loc);z++; scrifld(z++,fm_os6,nm_fil);}
		else z+=2;
		scrfld(z++,6,3);
		key=scrupd(curs,0xd19);curs=3;curspos_=fldcurs;
		if(key==111) ovlexit(*u(25,4));
		if(key==101 || key==105) break;
		if(inq_loc==99) copy("DEPOT",nm_fil,6);
		else if(inq_loc>=1 && inq_loc<=10){
			if(fldlen(66,11+(inq_loc-1)*15) && nm_loc[inq_loc-1][0]!='\0'){
				copy(nm_loc[inq_loc-1],nm_fil,6);
			}
			else {curs=11;zero(nm_fil,6);errnum=34;goto redo;}
		}
		else {curs=11;zero(nm_fil,6);errnum=34;goto redo;}
		if(*s(6,3)){
			if(search(6,0)){curs=13;goto redo;}
		} else fasinit(6);
		inq_art=*u(6,1);
		if(key==18){
			curs=curspos_+1;goto redo;
		}
		if(sys4470 && fldlen(66,1) && inq_loc>=1 && inq_loc<=10){
			zero(logfile,sizeof logfile);
			copy("pda-",logfile,4);stcli_d(&logfile[4],(long)(inq_loc),2,0);
			copy("\\MobStock.dat",&logfile[6],14);
		}
		else{
			zero(logfile,sizeof logfile);
			copy("MobStock.dat",logfile,25);
		}
		fasclos(-2);fasinit(80);mk_pdaname(4410,logfile);
		fasopen(filnam,102);/* eerste call voor dir */
		fasinfo(80,204);/* ophalen antwoord van dir */
		if(*s(80,1)){
			fasinit(80);fasinfo(80,205);/* get date  */
		} else fasinit(80);
		copy(s(80,1),filedatestr_,20);
		if(*s(80,1)=='\0'){
			errnum=1; curs=2; goto redo;
		}
		fasclos(-2);

		negatief = NO;

		if (key == 112) {
			negatief = YES;
			key = 104;
		}

		if(key==104){
			if(inq_art){
				if(scr_ok("Wenst U echt de stock van 1 ARTIKEL te verwerken ?")==NO) break;
			}
			else{
				if(scr_ok("Wenst U echt de opgenomen aantallen in te vullen op artikelfiches ?")==NO) break;
			}
			fasopen(filnam,1);
			if(wis_eerst=='A') {
				wis_stock();
				if(add_bstk=='A' || add_bstk=='O') AddAantalOpBons();
			}
			else if(wis_eerst=='S') wis_selec();
			exec_mstk(YES); fasclos(-2);
		}
		if(key==109) {fasopen(filnam,1);disp_stock();fasclos(-2);}
	}
}

static DeleteMobstock()
{
  int16 key,z,curs=3,curspos_,len_,k;
	char str_[200];

  inq_art=0; inq_loc=99;copy("DEPOT",nm_fil,6);
  zero(logfile,sizeof logfile);  copy("MobStock.dat",logfile,25);  mk_pdaname(4410,logfile);
	fasclos(-2);fasinit(80);
	fasopen(filnam,102);/* eerste call voor dir */
	fasinfo(80,204);/* ophalen antwoord van dir */
	if(*s(80,1)){
		fasinit(80);fasinfo(80,205);/* get date  */
	} else fasinit(80);
  FOREVER{
    fasinit(6); if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
    redo:;
    scrget(2,352);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_us30,logfile);
		scrifld(z++,fm_uu2,&pda_nr);
		scrifld(z++,fm_os20,s(80,1));
    key=scrupd(curs,0x059);curs=3;curspos_=fldcurs;
    if(key==101 || key==105) goto endsr;
    if(sys4470 && fldlen(66,1) && inq_loc>=1 && inq_loc<=10){
      zero(logfile,sizeof logfile);
      copy("pda-",logfile,4);stcli_d(&logfile[4],(long)(inq_loc),2,0);
      copy("\\MobStock.dat",&logfile[6],14);
    }
    else{
      zero(logfile,sizeof logfile);
      copy("MobStock.dat",logfile,25);
    }
    fasclos(-2);mk_pdaname(4410,logfile);
		fasopen(filnam,102);/* eerste call voor dir */
		fasinfo(80,204);/* ophalen antwoord van dir */
		if(*s(80,1)){
			fasinit(80);fasinfo(80,205);/* get date  */
		} else fasinit(80);
    if(*s(80,1)=='\0'){
      errnum=1; curs=2; goto redo;
    }

    if(key==104){
    	if(scr_ok("Wenst U echt de stock-opnames van de pda te wissen ?")==YES) break;
    }
  }
	fasunlck(-2);zero(logfile,sizeof logfile);
  if(sys4470 && fldlen(66,1) && inq_loc>=1 && inq_loc<=10){
		copy("pda-",logfile,4);stcli_d(&logfile[4],(long)(inq_loc),2,0);
		copy("\\MobStock.DAT",&logfile[6],14);
	}
	else{
		copy("MobStock.DAT",logfile,25);
	}
	mk_pdaname(4410,logfile);
	for(len_=0;len_<sizeof filnam;len_++) if(filnam[len_]=='\0') break;
	for(k=5;k>=0;k--){
		if(k==5){ // 005 deleten 
			copy("005",&filnam[len_-3],3);
			fasclos(-2);fasopen(filnam,99);
		}
		else{
			zero(str_,sizeof str_);
			copy(filnam,str_,len_);
			if(k==0) copy("DAT",&str_[len_-3],3); else stcli_d(&str_[len_-3],(long)(k),3,0);
			str_[len_]='|';
			copy(filnam,&str_[len_+1],len_); stcli_d(&str_[len_+1+len_-3],(long)(k+1),3,0);
			fasclos(-2);  fasopen(str_,100);
		}
	}

	endsr:;
}



static exec_mstk(upd_art_)/* inlezen genoteerde stock */
int16 upd_art_;
{
  int16 mode_=0,len_,k;
  uint16 dt_,arec_;
  char stuksfl_;
  float *p_stock_,qlv_,fls_,bak_,rd_stock_,verp_factor_;
									
  p_stock_=f(6,33);
  if(inq_loc>=1 && inq_loc<=10 && fldlen(66,11+(inq_loc-1)*15)){
    p_stock_=f(66,11+(inq_loc-1)*15);
  }

  getsysprNew(5,form_dat,&pr_mode,&prtnr); if(prt2pdf) PrintPaperNr=0;
  if ((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t33b>Niet gevonden artikels");
  prttext("<b><t55>"); prtfld(25,2,-1); prttext("<t72>Blz.<ppp>.");
  prtbuf(1);
  scrnum=0;scrget(1,170); scrifld(2,fm_os38,"Verwerken artikel : ");scrupd(-3,0);
  fasinit(80);cnt_good=0;cnt_bad=0;
  FOREVER{
    next:;
    if(read_rec(mode_)) break;mode_=1;
    fasinit(6);
    len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) goto next;
    if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0) goto next;
    dt_=get_date(0);
    if(dat_beg && dt_<dat_beg) goto next;
    if(dat_end && dt_>dat_end) goto next;
    qlv_=get_num(3); if(qlv_==0) goto next;

	if (negatief)
		qlv_ = -qlv_;

    if(sys4408){
      *pu_6_1=val(s(6,2));
      if(*pu_6_1) k=fasgeti(6); else k=1;
    }
    else k=faskeyi(6,1,0);
    get_str(&stuksfl_,4,1);
    if(stuksfl_=='P' && fldlen(6,83)==0) stuksfl_='N';
    else if(stuksfl_!='J' && stuksfl_!='P') stuksfl_='N';
    if(stuksfl_=='P' && *f(6,83)!=0) qlv_*=*f(6,83);
    if(k){
      prttext("Code : ");prtfld(6,2,-1);
      prttext("Aantal :");prtifld(fm_uf6_2,&qlv_,-1);
      prttext("St : ");prtifld(fm_os1,&stuksfl_,-1);
      nextline();cnt_bad++;
      goto next;
    }
    if(inq_art && inq_art!=*u(6,1)) goto next;
		if(*f(6,31)<1) *f(6,31)=1;
		if(stuksfl_=='J' && *f(6,31)<=1) stuksfl_='N';
		verp_factor_=1.;	arec_=*u(6,1);
		if(fldlen(6,102) && *u(6,102)){// stock op moederfiche bijwerken
			verp_factor_=*f(6,31);
			*u(6,1)=*u(6,102);fasgeti(6);
#if FLAGSAS | FLAGAST
		  if(NO){ // gekoppeld, altijd moederfiche bijwerken
#else
			if(*f(6,31) ==verp_factor_) {// bij zelfde aantal/bak toch op eigen artikel bijhouden
#endif
				fasinit(6);*u(6,1)=arec_;fasgeti(6);
			} 
			if(*f(6,31)  && stuksfl_!='J') verp_factor_/=*f(6,31); else verp_factor_=1.; // indien stuks, dan ook als stuks van hoofdartikel beschouwen
		}
		qlv_*=verp_factor_;
 
    if(fldlen(66,1)){
      fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
    }
    bak_=0;fls_=0; if(stuksfl_=='J') fls_=qlv_; else bak_=qlv_;
    rd_stock_=0;stks2stock(&rd_stock_,*f(6,31),bak_,fls_);
		if(upd_art_) *p_stock_+=rd_stock_;
		else if(*u(6,1)<DIM_ARTSTOCK) ArtPdaStock[*u(6,1)]+=rd_stock_; // enkel tellen
    scrfld(5,6,2); scrfld(6,6,3);scrifld(10,fm_uf6_2,&qlv_);scrifld(11,fm_os1,&stuksfl_);
    scrifld(13,fm_uf6_2,p_stock_);scrupd(-3,0);
		cnt_good++;
		if(upd_art_){
  		if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
      fasupd(6);
      if(fldlen(66,1)){
        if(*u(66,1)) fasupd(66); else fasadd(66);
      }
		}
  }
  fasclos(-2);
  prtform(0);prtclose();
  scrnum=0;
  scrget(1,170);
  scrifld(5,fm_os63,"Aantal goed verwerkte artikels : ");
  scrifld(6,fm_ou5,&cnt_good);
  scrifld(8,fm_os63,"Aantal NIET verwerkte artikels : ");
  scrifld(9,fm_ou5,&cnt_bad);
  scrifld(15,fm_os63,"Druk op F8 om verder te gaan ... ");
  scrupd(-1,0x81);
  endsr:;
}

static disp_stock()
{
  int16 j,k,len_,z,key,mode_,max_;
  char date_str_[15],time_str_[15],stuksfl_,str_[20];
  uint16 dt_,goto_end_=NO;
  float qbak_,qfles_;
  long fpos,start,beg_start;

  fpos=0;start=0;max_=30000;fasinit(80);mode_=0;
  for(beg_start=0;beg_start<max_;beg_start++){
    next1:;
    if(read_rec(mode_)) {max_=beg_start;break;} mode_=1;
    fasinit(6);
    len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) continue;
    dt_=get_date(0);
    if(dat_beg && dt_<dat_beg) continue;
    if(dat_end && dt_>dat_end) continue;
    if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0){
      if(inq_art) continue;
    }
    else{
      if(sys4408){
	*pu_6_1=val(s(6,2));
	if(*pu_6_1) k=fasgeti(6); else k=1;
      }
      else k=faskeyi(6,1,0);
      if(inq_art && inq_art!=*u(6,1)) continue;
    }
    break;
  }
  fpos=0;start=beg_start;max_=30000;fasinit(80);mode_=0;
  FOREVER{
    redo:;
    fpos=(long)(start)*LEN_LOGLINE;fasinit(80);*pl_80_1=fpos;mode_=0;
    scrnum=0; scrget(2,277);z=1;scraddpicto(1,0,76,22,4,2,583,0,0,"maak PDF"); 
    for(j=start;j<start+18;j++){
      next:;
      if(read_rec(mode_)) {max_=j;break;} mode_=1;
      fasinit(6);
      len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) goto next;
      dt_=get_date(0);
      if(dat_beg && dt_<dat_beg) goto next;
      if(dat_end && dt_>dat_end) goto next;
      qbak_=0;qfles_=0;
      if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0){
				if(inq_art) goto next;
				else{
					copy("--------------------------",s(6,3),30);
  				len_=get_str(str_,3,10); // PDA-nummer
	  			if(len_){
		  			*(s(6,3)+9)=' '; copy(str_,s(6,3)+10,len_);*(s(6,3)+10+len_)=' ';
			  	}
				}
      }
      else{
				if(sys4408){
					*pu_6_1=val(s(6,2));
					if(*pu_6_1) k=fasgeti(6); else k=1;
				}
				else k=faskeyi(6,1,0);
				if(inq_art && inq_art!=*u(6,1)) goto next;
				qbak_=get_num(3);
				get_str(&stuksfl_,4,1);
				if(stuksfl_=='P' && fldlen(6,83)==0) stuksfl_='N';
				else if(stuksfl_!='J' && stuksfl_!='P') stuksfl_='N';
				if(stuksfl_=='J'){ qfles_=qbak_;qbak_=0;}
				else if(stuksfl_=='P' && *f(6,83)!=0){qbak_*=*f(6,83);qfles_=0;}
				else qfles_=0;
      }
      len_=get_str(date_str_,0,10); date_str_[len_]='\0';
      len_=get_str(time_str_,1,10); time_str_[len_]='\0';
      scrifld(z++,fm_os10,date_str_);
      scrifld(z++,fm_os5,time_str_);
      scrofld(z++,6,2,-1);
      scrofld(z++,6,3,-1);
      scrifld(z++,fm_of5_0,&qbak_);
      scrifld(z++,fm_of5_0,&qfles_);
    }
    if(max_==j && goto_end_==YES) goto_end_=NO;
    if(goto_end_ && max_>j) key=103;
    else key=scrupd(-1,0x1AF);
		prt2pdf=NO;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==5001){prt2pdf=YES;prt_input(); break;} // pdf
    if(key==101) break;
    if(key==104 && start<max_-18){goto_end_=YES;key=103;}
    if(key==102){
      start-=18;if(start<beg_start) start=beg_start;
    }
    if(key==103) {
      start+=18;if(start>=max_-18) start=max_-18;
      if(start<beg_start) start=beg_start;
    }
    if(key==109){
      if(scr_ok("Wenst U echt deze lijst af te drukken ?")){
				prt_input(); break;
      }
    }
    if(start<beg_start) start=beg_start;
  }
  endsr:;
}

static prt_input()
{

  int16 k,len_,z,mode_;
  char date_str_[15],time_str_[15],stuksfl_,str_[20];
  uint16 dt_;
  float qbak_,qfles_;

  getsysprNew(5,form_dat,&pr_mode,&prtnr); if(prt2pdf) PrintPaperNr=0;
  if ((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t40b>Lijst stockopnames<b>");
  prttext("<t72>Blz.<ppp>.");
  prtbuf(1);z=1;
  prtitab(z,fm_os10,date_str_,2,-1); prttitle(z++,"Datum",3);
  prtitab(z,fm_os5,time_str_,2,-1); prttitle(z++,"Uur",3);
  prttab(z,6,2,2,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,2,-1); prttitle(z++,"Omschrijving",3);
  prtitab(z,fm_of5_0,&qbak_,4,-1); prttitle(z++,"Aantal",0x13);
  prtitab(z,fm_of5_0,&qfles_,4,-1); prttitle(z++,"Fls/Stk",0x13);
  prtbuf(3);
  p_pdfname("Lijst stockopnames",dat_beg,dat_end);
  fasinit(80); mode_=0;
  FOREVER{
    next:;
    if(read_rec(mode_)) break; mode_=1;
    fasinit(6);
    len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) goto next;
    dt_=get_date(0);
    if(dat_beg && dt_<dat_beg) goto next;
    if(dat_end && dt_>dat_end) goto next;
    qbak_=0;qfles_=0;
    if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0){
      if(inq_art) goto next;
      else{
				copy("--------------------------",s(6,3),30);
  			len_=get_str(str_,3,10); // PDA-nummer
	  		if(len_){
		  		*(s(6,3)+9)=' '; copy(str_,s(6,3)+10,len_);*(s(6,3)+10+len_)=' ';
			  }
			}
    }
    else{
      if(sys4408){
	*pu_6_1=val(s(6,2));
	if(*pu_6_1) k=fasgeti(6); else k=1;
      }
      else k=faskeyi(6,1,0);
      if(inq_art && inq_art!=*u(6,1)) goto next;
      qbak_=get_num(3);
      get_str(&stuksfl_,4,1);
      if(stuksfl_=='P' && fldlen(6,83)==0) stuksfl_='N';
      else if(stuksfl_!='J' && stuksfl_!='P') stuksfl_='N';
      if(stuksfl_=='J'){ qfles_=qbak_;qbak_=0;}
      else if(stuksfl_=='P' && *f(6,83)!=0){qbak_*=*f(6,83);qfles_=0;}
      else qfles_=0;
    }
    len_=get_str(date_str_,0,10); date_str_[len_]='\0';
    len_=get_str(time_str_,1,10); time_str_[len_]='\0';
    for(k=0;k<20;k++) prtinfo(k,0); nextline();
  }
  prtclose();
  endsr:;
}
 
static float get_bstk(arec_,fil_)
uint16 arec_,fil_;
{
  float q_bons_,qlv_;
  int16 mode_,chkfil_;
 
	chkfil_=NO;if(fldlen(66,11) && fldlen(8,48)) chkfil_=YES;
  q_bons_=0;
  if(fldlen(8,1)==0) return (float)0.;
  fasinit(58);*u(58,14)=arec_;mode_=1;
  FOREVER{
    next58:;
    if(faskeyi(58,2,mode_)) break; mode_=2;
    if(*u(58,14)!=arec_) break;
    fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
    if(dt_bonb && *u(8,8)<dt_bonb) goto next58;
    if(dt_bone && *u(8,8)>dt_bone) goto next58;
    if(fldlen(8,36) && *u(8,36)) goto next58;
		if(chkfil_ && *u(8,48)!=fil_) goto next58;
    qlv_=*f(58,31);
    if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
    q_bons_+=qlv_;
  }
  return q_bons_;
}


static get_str(ps_,nr_,mlen_)
char *ps_,nr_;
int16 mlen_;
{
  int16 j,k,len_;
  char *pos_;

  len_=ele_len(nr_);if(len_>mlen_) len_=mlen_;
  pos_=rec_ele(nr_);
  j=len_;
  for(k=0;k<j;k++){
    if(*pos_!=' ') break;
    pos_++; len_--;
  }
  copy(pos_,ps_,len_);
  for(k=len_-1;k>=0;k--) if(*(pos_+k)>' ') break;
  for(j=k+1;j<len_;j++) *(ps_+j)='\0';
  CnvJamaChar(ps_,len_,1);
  return k+1;
}

static wis_selec()
{
  uint16 k,dt_,mode_=0,len_,tbrecs_[7500],max_,hoofdart_, curart_;
  float qlv_;
 
  scrnum=0;scrget(1,170);
  scrifld(10,fm_os63,"    De actuele stock wordt nu SELECTIEF op 0 gezet");scrupd(-3,0);
	zero((char *)tbrecs_,sizeof tbrecs_);max_=0;
  fasinit(80);
  FOREVER{
next:;
	  if(read_rec(mode_)) break;mode_=1;
	  fasinit(6);
	  len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) goto next;
	  if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0) goto next;
	  dt_=get_date(0);
	  if(dat_beg && dt_<dat_beg) goto next;
	  if(dat_end && dt_>dat_end) goto next;
	  qlv_=get_num(3); if(qlv_==0) goto next;
	  if(sys4408){
		  *pu_6_1=val(s(6,2));
		  if(*pu_6_1) k=fasgeti(6); else k=1;
	  }
	  else k=faskeyi(6,1,0);
	  if(k) goto next;
	  if(inq_art && inq_art!=*u(6,1)) goto next;
	  for(k=0;k<max_;k++) if(tbrecs_[k]==*u(6,1)) break;
	  if(k>=max_ && max_<7500) tbrecs_[max_++]=*u(6,1); 
	  else goto next; // al gedaan 
	  scrfld(14,6,3);scrupd(-3,0);
	  hoofdart_ = fldlen(6,102) && *u(6,102) ? *u(6,102) : 0;

	  if(fldlen(66,1)){
		  if(inq_loc<1 || inq_loc>10) {
			  *f(6,33)=0;
			  if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			  fasupd(6);
		  }
		  if(inq_loc!=99){
			  fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
			  for(k=0;k<10;k++) {
				  if((k==inq_loc-1 || inq_loc==0) && fldlen(66,11+k*15)) *f(66,11+k*15)=0;
			  }
			  if(*u(66,1)) fasupd(66);
		  }
	  }
	  else{
		  *f(6,33)=0;
		  if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
		  fasupd(6);
	  }

	  // Ook stock op hoofdartikel op 0 zetten
	  if (hoofdart_) {
		  curart_ = *u(6,1);
		  *u(6,1) = hoofdart_;

		  if (fasgeti(6,1,0) == 0) {
			  if(fldlen(66,1)) {
				  if (inq_loc < 1 || inq_loc > 10) {
					  *f(6,33) = 0;
					  if (fldlen(6,199))
						  *u(6,199) = *u(25,2); // datum laatste update

					  fasupd(6);
				  }

				  if (inq_loc != 99) {
					  fasinit(66);
					  *u(66,2) = *u(6,1);
					  faskeyi(66,1,0);

					  for (k = 0; k < 10; k++) {
						  if ((k == inq_loc - 1 || inq_loc == 0) && fldlen(66,11+k*15))
							  *f(66,11+k*15) = 0;
					  }

					  if (*u(66,1))
						  fasupd(66);
				  }
			  }
			  else {
				  *f(6,33) = 0;

				  if (fldlen(6,199))
					  *u(6,199) = *u(25,2); // datum laatste update

				  fasupd(6);
			  }
		  }

		  *u(6,1) = curart_;
		  fasgeti(6,1,0);
	  }
  }
	if(add_bstk=='A' || add_bstk=='O'){
		for(k=0;k<max_;k++){
			fasinit(6);*u(6,1)=tbrecs_[k]; fasgeti(6);
			qlv_=get_bstk(*u(6,1),inq_loc);
			if(fldlen(66,1)){
				if(inq_loc<1 || inq_loc>10) {
					if(add_bstk=='A') *f(6,33)-=qlv_;
					else if(add_bstk=='O') *f(6,33)+=qlv_;
					if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
					fasupd(6);
				}
				else{
					fasinit(66);*u(66,2)=*u(6,1);
					if(faskeyi(66,1,0)){fasinit(66);*u(66,2)=*u(6,1);fasadd(66);}
					if(add_bstk=='A') *f(66,11+(inq_loc-1)*15)-=qlv_;
					else if(add_bstk=='O') *f(66,11+(inq_loc-1)*15)+=qlv_;
					fasupd(66);
				}
			}
			else{
				*f(6,33)=0;
				if(add_bstk=='A') *f(6,33)-=qlv_;
				else if(add_bstk=='O') *f(6,33)+=qlv_;
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				fasupd(6);
			}
		}
  }
  fasflush(0);
}

static wis_stock()
{
  uint16 a,k,used;
 
  scrnum=0;scrget(1,170);
  scrifld(10,fm_os63,"    De actuele stock wordt nu op 0 gezet");scrupd(-3,0);
  fasinfo(6,1);
  used=*u(6,1);
  for(a=1;a<=used;a++){
    *u(6,1)=a;
    if(fasgetu(6)==0){
      if(fldlen(66,1)){
				if(inq_loc==0 || inq_loc==99) {
					*f(6,33)=0;
					if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
					fasupd(6);
				}
				if(inq_loc!=99){
					fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
					for(k=0;k<10;k++) {
						if((k==inq_loc-1 || inq_loc==0) && fldlen(66,11+k*15)) *f(66,11+k*15)=0;
					}
					if(*u(66,1)) fasupd(66);
				}
      }
      else{
				*f(6,33)=0;
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				fasupd(6);
      }
    }
  }

  fasflush(0);
}

static AddAantalOpBons()
{
  uint16 a,k,used;
	float qlv_;
 
  scrnum=0;scrget(1,170);
  scrifld(10,fm_os63,"    De aantallen op leveringsbons worden nu verwerkt in de stock...");scrupd(-3,0);
  fasinfo(6,1);
  used=*u(6,1);
  for(a=1;a<=used;a++){
    *u(6,1)=a;
    if(fasgetu(6)==0){
			qlv_=get_bstk(*u(6,1),inq_loc);
			if(fldlen(66,1)){
				if(inq_loc<1 || inq_loc>10) {
					if(add_bstk=='A') *f(6,33)-=qlv_;
					else if(add_bstk=='O') *f(6,33)+=qlv_;
					if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
					fasupd(6);
				}
				else{
					fasinit(66);*u(66,2)=*u(6,1);
					if(faskeyi(66,1,0)){fasinit(66);*u(66,2)=*u(6,1);fasadd(66);}
					if(add_bstk=='A') *f(66,11+(inq_loc-1)*15)-=qlv_;
					else if(add_bstk=='O') *f(66,11+(inq_loc-1)*15)+=qlv_;
					fasupd(66);
				}
			}
			else{
				*f(6,33)=0;
				if(add_bstk=='A') *f(6,33)-=qlv_;
				else if(add_bstk=='O') *f(6,33)+=qlv_;
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				fasupd(6);
			}
		}
	}
  fasflush(0);
}




#if 0
exec_barc()
{
  int16 g;
								
  if(werkveld[0]<'0' || werkveld[0]>'9'){
    fasinit(6);copy(werkveld,s(6,3),30);
    search(6,0);
  }
  else{
    fasinit(6);copy(werkveld,s(6,70),fldlen(6,70));
    g=faskeyi(6,10,0);
    if(g){
      fasinit(6);copy(werkveld,s(6,71),fldlen(6,71));
      g=faskeyi(6,11,0);
      if(g) errnum=g;
      else {zero(werkveld,sizeof werkveld); return 2;}
    }
    else {zero(werkveld,sizeof werkveld); return 1;}
  }
  if(errnum==0) {zero(werkveld,sizeof werkveld);}
  else {fasinit(6);screrr(-1);return NO;}
  return YES;
}
#endif
 
static stock2stks(stock_,qst_,bak_,fls_)
float stock_,qst_,*bak_,*fls_;
{
	float add_;
 
  if(qst_<1) qst_=1;
  *bak_=(long)(stock_); *fls_=0;
	add_=0.49; if(stock_<0) add_=-0.49;
  if(qst_>1 && stock_!=0){
    *fls_=(long)(((stock_- *bak_) * qst_)+add_);
  } else *fls_=0;
}

static stks2stock(stock_,qst_,bak_,fls_)
float *stock_,qst_,bak_,fls_;
{
  if(qst_<1) qst_=1;
  *stock_=bak_+ fls_/qst_;
}

static p_dbl_ean()
{
  int16 z,g,k,used_,dubbel_;
  int16 form_dat[8],pr_mode,prtnr,mode_;
  char ean_bak[15],ean_stk[15];
  char *ps_6_70,*ps_6_71;
  uint16 n,nn_,max_;
 
  if(fldlen(6,70)==0 && fldlen(6,71)==0) goto endsr;
  if(scr_ok("Wenst U echt een controle uit te voeren ?")==NO) goto endsr;
 
  ps_6_70=s(6,70);ps_6_71=s(6,71);
  fasinfo(6,1);max_=*pu_6_1;
  zero(ean_bak,sizeof ean_bak);zero(ean_stk,sizeof ean_stk);
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr); if(YES || prt2pdf) PrintPaperNr=0; // altijd in PDF 
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
									
  prtfld(25,1,20);prttext("<t25b>Lijst dubbele EAN-nummers<bt62>");
  prtifld(fm_odat,u(25,2),-1);prttext("<t72>Blz.<ppp>");
  prtbuf(1);z=1;
  prttab(z,6,2,2,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,2,-1); prttitle(z++,"Omschrijving",3);
  prttab(z,6,70,2,-1); prttitle(z++,"EAN bak",3);
  prttab(z,6,71,2,-1); prttitle(z++,"EAN stuk",3);
  prtbuf(3);

  fasinit(6);
  n=0;scrnum=0;scrget(1,170);
  scrifld(2,fm_os63,"                 Controle op dubbele EAN-nummers");
  scrifld(5,fm_os63,"Bezig met fiche :");
  scrfld(6,6,1);
  scrifld(7,fm_os63,"van :");
  scrifld(8,fm_ou5,&max_);
  scrfld(11,6,3);
  FOREVER{
    next_art:;
    *pu_6_1=++n;
    g=fasgeti(6);
    if(g==47)break;
    if(g!=46){/* deleted record */
      if((n%10)==0){
				scrfld(6,6,1);
				scrfld(11,6,3);scrupd(-3,0);
      }
      if(*ps_6_70<'0' && *ps_6_71<'0') goto next_art;
      if(*ps_6_70>='0' && *ps_6_70<='9') copy(ps_6_70,ean_bak,14);
      else zero(ean_bak,sizeof ean_bak);
      if(*ps_6_71>='0' && *ps_6_71<='9') copy(ps_6_71,ean_stk,14);
      else zero(ean_stk,sizeof ean_stk);
			used_=NO;
			if(fldlen(64,1)){
				if(ean_bak[0]){
					fasinit(64);copy(ean_bak,s(64,2),fldlen(64,2)); mode_=1;
					if(faskeyi(64,1,0)==0){
						if(used_==NO) nextline(); used_=YES;
						fasinit(6);*u(6,1)=*u(64,3);fasgeti(6);
  					if(*i(64,5)==0) copy(ean_bak,s(6,70),fldlen(6,70));
						else copy(ean_bak,s(6,71),fldlen(6,71));
						for(k=0;k<20;k++) prtinfo(k,0); nextline();
					}
				}
				if(ean_stk[0]){
					fasinit(64);copy(ean_stk,s(64,2),fldlen(64,2)); mode_=1;
					if(faskeyi(64,1,0)==0){
						if(used_==NO) nextline(); used_=YES;
						fasinit(6);*u(6,1)=*u(64,3);fasgeti(6);
						if(*i(64,5)==0) copy(ean_stk,s(6,70),fldlen(6,70));
						else copy(ean_stk,s(6,71),fldlen(6,71));
						for(k=0;k<20;k++) prtinfo(k,0); nextline();
					}
				}
			}
      fasinit(6);
      nn_=n; 
      FOREVER{
				nnext_art:;
				*pu_6_1=++nn_;
				g=fasgeti(6);
				if(g==47)break;
				if(g!=46){/* deleted record */
					if(*ps_6_70<'0' && *ps_6_71<'0') goto nnext_art;
					dubbel_=NO;
					if(ean_bak[0]){
						if(*ps_6_70>='0' && cmpstr(ean_bak,ps_6_70,14)==0) dubbel_=YES;
						if(*ps_6_71>='0' && cmpstr(ean_bak,ps_6_71,14)==0) dubbel_=YES;
					}
					if(ean_stk[0]){
						if(*ps_6_70>='0' && cmpstr(ean_stk,ps_6_70,14)==0) dubbel_=YES;
						if(*ps_6_71>='0' && cmpstr(ean_stk,ps_6_71,14)==0) dubbel_=YES;
					}
					if(dubbel_){
						if(used_==NO) nextline();
						for(k=0;k<20;k++) prtinfo(k,0);nextline();
						used_=YES;
					}
				}
      }
      if(used_){
	*pu_6_1=n;fasgeti(6);
	for(k=0;k<20;k++) prtinfo(k,0);nextline();
      }
    }
  }
  prtclose();
  endsr:;
}
 
static param()
{
  int16 curs=1,k,key,z,kas_exist;
  char prx_str[6],subart[40],subvkp[40],subpda[40],sublgret[35],DaveLicentie[10];
	
  kas_exist=NO; if(ovltest(290)) kas_exist=YES;
  copy(sys3896,prx_str,6);
  sysget(3902,16,subart);
  sysget(3936,16,subvkp);
  sysget(4410,16,subpda);
	sysget(4426,6,DaveLicentie);
  sysget(4440,30,sublgret);
  sysget(5576,120,&verkoper[0].code[0]);
  FOREVER{
    redo:;
    scrget(2,272);z=1;
    if(kas_exist){
      for(k=0;k<6;k++) scrifld(z++,fm_os1,&prx_str[k]);
      scrifld(z++,fm_os15,subart);
    }
    else{
      for(k=0;k<6;k++) scrifld(z++,fm_u_05,&prx_str[k]);
      scrifld(z++,fm_us15,subart);
    }
    scrifld(z++,fm_us16,subpda);
    scrifld(z++,fm_us30,sublgret);

#if !FLAGCOC
    for(k=0;k<10;k++){
      scrifld(z++,fm_us2U,verkoper[k].code);
      scrifld(z++,fm_us10,verkoper[k].naam);
    }
		scrifld(z++,fm_us6_09,DaveLicentie);
#endif
    key=scrupd(curs,0x00A0);curs=1;
    if(key==106) return YES;
#if !FLAGCOC
    for(k=0;k<10;k++){
      if(verkoper[k].code[0] && verkoper[k].naam[0]=='\0'){errnum=38;goto redo;}
    }
#endif
    if(key==108){
      copy(prx_str,sys3896,6);
      sysput(3896,6,&sys3896[0]);
      sysput(3902,16,subart);
      sysput(3936,16,subvkp);
      sysput(4410,16,subpda);
			sysput(4426,6,DaveLicentie);
	    sysput(4440,30,sublgret);
      sysput(5576,120,&verkoper[0].code[0]);
      return NO;
    }
  }
}

static nextline()
{
  free=prtline();
}

static double round(bedrag_)
double bedrag_;
{
  float add;
							
  add=sys3614;
  if(sys3618==0) add/=2.;
  add=add*.999999;
  if(sys3614>0.0001){
    bedrag_=((long)((bedrag_+add)/sys3614)) * sys3614;
  }
  return bedrag_;
}

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
}

static initload()
{
  int16 nr_,g,k;

  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  if(fldlen(8,0)) fileopen(8);
  fileopen(9);
  if(fldlen(66,1)) fileopen(12);
			
  sysget(  34,256,firma);
  sysget(294,4,def_munt);
  sysget(1048,32,&btw_pct[0]);
  sysget(1790,2,&sys1790);
  sysget(1918,2,&sear_stt);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3772,2,&sys3772);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,&sys3896[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);
  sysget(4408,2,&sys4408);
  sysget(4436,2,&sys4436);
  sysget(4470,1,&sys4470);

  pu_6_1=u(6,1);
  pf_6_28=f(6,28);
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

  zero((char *)&tbgr[0].rec,sizeof tbgr);
  p_max_grp=0;sgrp_used=NO;
  for(k=1;k<100;k++){
    fasinit(52);*u(52,1)=k;
    g=fasgeti(52);
    if(g==0 && *s(52,14)) tbgr[p_max_grp++].rec=k;
  }
  for(k=0;k<100;k++) tbgr[k].select='J';
  for(k=5;k>=0;k--){
    if(sys3896[k]){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])) break;
    }
  }
							
  if(k>0){
    p_tr_stuk=sys3896[k]-'0';
    p_tr_bak=sys3896[k-1]-'0';
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
 
static dsp_tabel(type_)
int16 type_;/* 0=leveranciers, 1=groepen */
{
  int16 k,key,z,start=0,startpos,p_tb,curs=1,q_y,q_n,stu_,curspos_;
  char *pd;
					
  stu_=52;startpos=0; p_tb=p_max_grp;
  start=startpos; pd=oldnm;
  FOREVER{
    redo:;
    scrnum=0;scrget(2,46);z=1;
    if(type_==0) scrifld(z++,fm_os15,"LEVERANCIER");
    else scrifld(z++,fm_os15,"GROEP");
    for(k=start;k<p_tb;k++){
      fasinit(stu_); *u(stu_,1)=tbgr[k].rec; fasgeti(stu_);
      pd=oldnm; zero(pd,40);
      switch(stu_){
	case 6 : pd+=add1str(pd,10,6,2,' ');pd+=add1str(pd,30,6,3,'\0');
		 break;
	case 1 : pd+=add1str(pd,40,1,3,'\0');
		 break;
	case 52: stcli_d(pd,(long)*u(52,1),2,0);pd+=2;*(pd++)=' ';
		 pd+=add1str(pd,15,52,14,'\0');
		 break;
	default: zero(pd,40);break;
      }
      scrifld(z,fm_os40,oldnm);
      if(tbgr[k].select=='J') scrchat(z++,0x08); else scrchat(z++,0x00);
      scrifld(-z,fm_uJN,&tbgr[k].select);
      if(tbgr[k].select=='J') scrchat(z++,0x02); else scrchat(z++,0x00);
      if(k==start+17) break;
    }
    key=scrupd(curs,0xB6);curs=1;curspos_=fldcurs;
    if(key==18){
      curs=curspos_+1;goto redo;
    }
    if(key==105) {for(k=startpos;k<p_tb;k++) tbgr[k].select='J';}
    if(key==106) {for(k=startpos;k<p_tb;k++) tbgr[k].select='N';}
    if(key==108){
      q_y=0;q_n=0;
      for(k=startpos;k<p_tb;k++){
	if(tbgr[k].select=='J') q_y++; else q_n++;
      }
      if(q_n==0){ if(type_==0) slev_used=NO; else sgrp_used=NO;}
      else{
	if(q_y==0){errnum=38; goto redo;}
	else{if(type_==0) slev_used=YES; else sgrp_used=YES;}
      }
      break;
    }
    if(key==102) start-=18;
    if(key==103) {start+=18;if(start>=p_tb-18) start=p_tb-18;}
    if(start<startpos) start=startpos;
  }
  return NO;
}

static add1str(pd,len_,stu_,nr_,kar_)
char *pd,kar_;
int16 stu_,nr_,len_;
{
  int16 k;
 
  if(len_>fldlen(stu_,nr_)) len_=fldlen(stu_,nr_);
  copy(s(stu_,nr_),pd,len_);
  for(k=0;k<len_;k++){
    if(*(pd+k)=='\0') break;
  }
  *(pd+k++)=kar_;if(kar_==',') *(pd+k++)=' ';
  return k;
}
 
static selec_tst()
{
  int16 k;
								
  if(sgrp_used){
    for(k=0;k<p_max_grp;k++) if(*u(6,9)==tbgr[k].rec) break;
    if(k>=p_max_grp || tbgr[k].select!='J') return NO;
  }
  return YES;
}
 
static ele_len(nr_)
int16 nr_;
{
  int16 k=0;
  char *p;

  p=rec_ele(nr_);
  FOREVER{
    if(*p=='|' || *p==0x0D || *p==0x0A || *p=='\0') return k;
    p++;k++;
  }
}
 
static char *rec_ele(nr_)
int16 nr_;
{
  int16 k;
  char *p;

  p=p_data;
  for(k=0;k<nr_;k++){
    FOREVER{
      if(*p=='|' || *p==0xD || *p=='\0') break;
      p++;
    }
    p++;
  }
  return p;
}
 
static read_rec(mode_)
int16 mode_;
{
  int16 j;
  flag eof_=NO;
  long pos_;

  if(mode_){
    for(j=0;j<256;j++) if(*(p_data+j)==0x0A || *(p_data+j)=='\0') break;
    if(*(p_data+j)==0x0A || *(p_data+j)=='\0') *pl_80_1+=(j+1);
    zero(p_data,256);
  }
  pos_=*pl_80_1;
  if(fasseqi(80,1,256)) {eof_=YES;}
  if(eof_ && *p_data=='\0') return YES;
  else{/* positioneer terug op eerste karakter */
    *pl_80_1=pos_;
    return NO;
  }
}
 
static uint16 get_date(nr)/* read date DD/MM/JJJJ starting at pos  */
int16 nr;
{
  int16 k=0,getal_[3],p_getal_;
  uint16 dt_=0;
  char *pos;
									
  zero(getal_,sizeof getal_);p_getal_=0;
  dt_=0; pos=rec_ele(nr); if(ele_len(nr)==0) goto endsr;
  FOREVER{
    if(*(pos+k)=='|' || *(pos+k)==0x0D) break;
    if(*(pos+k)=='/'){p_getal_++;if(p_getal_>2) break;}
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
	getal_[p_getal_]=getal_[p_getal_]*10 + (*(pos+k)-'0');
      }
    }
    k++;
  }
  getal_[2]%=100;
  dt_=datejd(getal_[2],getal_[1],getal_[0]);
  endsr:;
  return (uint16) dt_;
}

static float get_num(nr)/* read number starting at pos  */
int16 nr;
{
  int16 j=0,k=0,n;
  float val_=0,val1_;
  flag na_komma=NO,neg_get=NO;
  char *pos;
 
  pos=rec_ele(nr);
  FOREVER{
    if(*(pos+k)=='|' || *(pos+k)==0x0D) break;
    if(*(pos+k)=='.') na_komma=YES;
    else if(*(pos+k)=='-') neg_get=YES;
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
	if(na_komma==NO){
	  val_=val_*10 + (*(pos+k)-'0');
	}
	else{
	  j++;
	  val1_=*(pos+k)-'0';
	  for(n=0;n<j;n++) val1_=val1_/10;
	  val_+= val1_;
	}
      }
    }
    k++;
  }
  if(neg_get) return (float) -val_;
  else return (float) val_;
}

static mk_pdaname(adr_pref,ps)
uint16 adr_pref;
char *ps;
{
  char *pd;
  char str_[10];
				
  zero(filnam,sizeof filnam);
  pd=filnam;
  sysget(adr_pref,26,pd);
  while(*pd) pd++;
  if(pda_nr){
    zero(str_,sizeof str_);
    copy("PDA-",str_,4);stcli_d(&str_[4],(long)pda_nr,2,0);str_[6]='\\';
    copy(str_,pd,7); pd+=7;
  }
  while(*ps!='\0') *pd++=*ps++;
}

static mk_name(adr_pref,ps)
uint16 adr_pref;
char *ps;
{
  char *pd;

  zero(filnam,sizeof filnam);
  pd=filnam;
  sysget(adr_pref,16,pd);
  while(*pd) pd++;
  while(*ps!='\0') *pd++=*ps++;
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
 
static scr_ok(ptxt)
char *ptxt;
{
  int16 key;

  scrget(1,169);
  scrifld(12,fm_os80,ptxt);
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  return NO;
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

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
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
  parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}
