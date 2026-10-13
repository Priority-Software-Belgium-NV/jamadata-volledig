/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0079GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0079dat   // lijst facturen klant/leverancier
#define ovlcod BKH0079cod
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

char ovldat[] = "bkh0079  00:08 17/09/10 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define MAXFLD          120

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

static char *selp_txt[6]={"Ondergrens (>)","Ondergrens (> of =)",
		"Bovengrens (<)","Bovengrens (< of =)",
		"Gelijk","Niet gelijk"};
							
static int16 selp_stu=0,stu;
static char selp_bf[4][1000],selp_des[40],*selp_fld;
static flag selp_use,selp_ge,selp_le,sys1854,sys1816;

extern char *s();
extern int16 *i();
extern uint16 *u();
static uint16 getgrb();
extern long *l();
extern long val();
static long val86_1(),val4_1();
extern float *f();
extern double *d();
extern double valu_cnv();

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_obd[]   = {6,0x95,8,2,0x70,0};                             /* od8_2 */
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};

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
} j_tab[80];

static int16 form_dat[8],pr_mode,free,prtnr,stu_bew,stu_lk;
static int16 prt2pdf;
static int16 StylTotaal, StylDate, StylKlasse, StylNormal, StylTitel, Styl2Use;
static uint16 rek_nr,journl,j_typ,scrcount,notfound;
static uint16 dt_bew,searcnr,volgnr,last_arc,clean_prev[3];
static uint16 df_recnr[15],rec_d_ak, rec_d_vk;
extern int16 ilength; // XLS
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi,prt2xls; // XLS
static long kltcent,levcent,df_grb[15],grb_d_ak, grb_d_vk,btws[5],noomzet[10];

static double bd_inc,bd_exc,bd_btw,bd_tot_lst,bdt_inc,bdt_exc,bdt_btw,bd_div,bdt_div,rbdt_inc,rbdt_exc,rbdt_btw,rbdt_div;
static double tbdt_inc,tbdt_exc,tbdt_btw,tbdt_div,tbdt_voldaan,tbdt_nietvoldaan;
static char prt_lev='N',prt_klt='N',skippage='N',tekst[20],buf750[750],prt_fdet='J',buff1000[1000],def_munt[4];
static char use_kselp='N',txt_voldaan[4],short_list='J';
static char taal_i,talen[4];
static flag debit_allow=NO,credt_allow=NO,lvcd,klcd,printed,allow_yr=NO;
static flag sear_stt,sys3876;
static flag chk_btoeg,p_opened=NO;
static uint16 *pu_4_1,len4_1,*pu_86_1,len86_1;
static long *pl_4_1,*pl_86_1;
static double *pd_4_32;

#include "Std\XlsFunc.c"

ovlcod(parmval)
int16 parmval;
{
  initload();fasunlck(-1);
  if(parmval){                                  /* automatisch voor 1 klant */
    j_typ=2;stu_lk=2;prt_fdet='J';
    *u(26,2)=*u(27,2);*u(26,3)=*u(27,3);
    fasinit(2);*u(2,1)=*u(27,5);fasgeti(2);
    prt2pdf=YES;prt_1rek(YES);
    ovlexit(-1);
  }
 
  if(ask_parm()) goto endsr;/* individuele worden direkt geprint16 */
  if(p_opened) {
		if(prt2xls) XlsClose(XlsRef,1);	else free=prtclose();
		p_opened=NO;
	}
  if(prt_lev=='J') {stu_lk=1;j_typ=1;pr_1lst();}
	  if(p_opened) {
		if(prt2xls) XlsClose(XlsRef,1);	else free=prtclose();
		p_opened=NO;
	}
  if(prt_klt=='J') {stu_lk=2;j_typ=2;pr_1lst();}
  if(p_opened) {
		if(prt2xls) XlsClose(XlsRef,1);	else free=prtclose();
		p_opened=NO;
	}
  endsr:;
  ovlexit(-1);
}

static ask_parm()
{
  int16 curs=1,k,key,z;
  uint16 dt_;

  sysget(1842,6,(char *)clean_prev);
 
  FOREVER{
    fasinit(1);fasinit(2);
    redo:;
    scrget(1,74);z=1;
		scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0079A");
		scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
		scraddpicto(2,0,72,22,4,2,573,0,0,"Maak XLS"); 
    scrfld(z++,25,1);
    if(p_opened==NO){scrfld(z++,26,2);scrfld(z++,26,3);}
    else {scrofld(z++,26,2,-1);scrofld(z++,26,3,-1);}
    if(credt_allow){
      scrifld(z++,fm_uJN,&prt_lev);
      scrfld(z++,1,3);
    }
    else {streepje(z++);streepje(z++);}
    if(debit_allow){
      scrifld(z++,fm_uJN,&prt_klt);
      scrfld(z++,2,3);
      scrifld(z++,fm_uJN,&use_kselp);
    }
    else {streepje(z++);streepje(z++);}
    scrifld(z++,fm_uJN,&prt_fdet);
    scrifld(z++,fm_uJN,&skippage);
    scrifld(z++,fm_uJN,&short_list);
    scrifld(z++,fm_odat,&last_arc);
    if(allow_yr){
      for(k=0;k<3;k++) scrifld(z++,fm_odat,&clean_prev[k]);
    }
    else for(k=0;k<3;k++) streepje(z++);
    key=scrupd(curs,0x0581);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) return YES;
    if(key==111) ovlexit(10);
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
		prt2xls=NO;if(key==5002){prt2xls=YES;key=108;}
    if(*u(26,2)==0){curs=2;errnum=38;goto redo;}
    if(*u(26,3)<*u(26,2)){curs=3;errnum=33;goto redo;}
    if(prt_lev=='N' && prt_klt=='N'){curs=4;errnum=52;goto redo;}
    if(prt_lev=='J'){
      dt_=last_arc;
      if(allow_yr) dt_=clean_prev[0];
      if(*u(26,2)<dt_) {errnum=37; goto redo;}
      if(*s(1,3)){
	if(search(1,0)){curs=1*2+3;goto redo;}
	stu_lk=1;j_typ=1;prt_1rek(YES);
	curs=1*2+3;fasinit(stu_lk);goto redo;
      }
    }
    if(prt_klt=='J'){
      dt_=last_arc;
      if(allow_yr) dt_=clean_prev[1];
      if(*u(26,2)<dt_) {errnum=37; goto redo;}
      if(*s(2,3)){
	if(search(2,0)){curs=2*2+3;goto redo;}
	stu_lk=2;j_typ=2;prt_1rek(YES);
	curs=2*2+3;fasinit(stu_lk);goto redo;
      }
    }
    if(*s(1,3)=='\0' && *s(2,3)=='\0') break;
  }
  selp_use=NO;stu=2;
  if(prt_klt=='J' && use_kselp=='J'){
    if(selp_ask()) return YES;
  }
  return NO;
}

static pr_1lst()
{
  if(free==-1) goto endsr;
  if(prt2xls) scrget(1,7); else scrget(1,6);
	scrupd(-3,0);
  tbdt_inc=0;tbdt_exc=0;tbdt_btw=0;tbdt_div=0;
	tbdt_voldaan=0;tbdt_nietvoldaan=0;

  fasinit(stu_lk);
  FOREVER{
    if(faskeyi(stu_lk,2,2)) break;
    if(stu_lk!=2 || selp_use==NO || selp_tst()){
      prt_1rek(NO);
    }
  }
  if(prt2xls==NO) prt_endr(YES);
  endsr:;
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
    bd_+=*pd_4_32;
  }
  if(is_nul(bd_)) ret_val_=YES;
  endsr:;
  copy(buff1000,s(4,1),fldlen(4,0));
  return ret_val_;
}


static prt_1rek(mode_)/* YES=1 klt/lev NO=lijst */
int16 mode_;
{
 
  printed=NO;
  fasinit(4);stu_bew=4;
  searcnr=*u(stu_lk,1)+(stu_lk-1)*30000;
  init_rek();
  *u(4,5)=searcnr;
  if(allow_yr){
    fasinit(86);
    *u(86,5)=searcnr;
  }
  rec_get(86);
  FOREVER{
    if(next_rec()==0) break;/* get record, en stu_bew zetten */
    if(*u(stu_bew,4)>=*u(26,2) && *u(stu_bew,4)<=*u(26,3)){
      if(printed==NO) pr_rk_nm();
      prt_bew();
    }
    if(free==-1) break;
  }
	if(prt2xls){
		if(mode_) {XlsClose(XlsRef,1);p_opened=NO;}
	}
	else{
    prt_endr(NO);
    if(mode_ && p_opened) {free=prtclose();p_opened=NO;}
	}
  endsr:;
}

static open_prt()
{
  int16 z,qkol_;

	if(prt2xls){
		scrget(1,7);scrupd(-3,0);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,0,0,NO,NO);
		if(stu_bew==1) XlsRef=OpenXlsFile("Facturenlijst leveranciers",*u(25,2));
		else XlsRef=OpenXlsFile("Facturenlijst klanten",*u(25,2));
    if(XlsRef<=0) {errnum=1;ovlexit(-1);}
		XlsColumnSize(XlsRef,1,35);
	  XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,0,XlsKol++,0,"Naam",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"FtNr",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Datum",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Totaal",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Belastbaar",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"BTW",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Divers",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Voldaan",0);
		XlsRij++;
    goto no_header;
	}

  getsysprNew(3,form_dat,&pr_mode,&prtnr); if(prt2pdf) PrintPaperNr=0;
  qkol_=96; if(prt_fdet=='J' && short_list!='J') qkol_=80;
  if((errnum=prtopen(prtnr,form_dat,6,qkol_,pr_mode,4))!=0) ovlexit(10);
  free=999;
  prtnew();
  prtfld(25,1,-1);
  if(prt_fdet=='J') prttext("<t33b>Facturenlijst<b>");
  else prttext("<t33b>Omzetlijst<b>");
  prttext("<t50>"); prtfld(26,2,-1);
  prttext(" - "); prtfld(26,3,-1);
  if(prt_fdet=='J' && short_list!='J') prttext("<t72>Blz.<ppp>.");
  else prttext("<t88>Blz.<ppp>.");
  prtbuf(1);
  z=1;
/*  prtitab(z,fm_os8,tekst,1,-1); prttitle(z++,"",3); */
  if(prt_fdet!='J'){prttab(z,stu_lk,3,1,30); prttitle(z++,"Naam",3);}
  else{
		if(short_list=='J') {prttab(z,stu_lk,3,1,25); prttitle(z++,"Naam",3);}
		if(short_list!='J') {prtitab(z,fm_uu2,&journl,3,-1); prttitle(z++,"Jrn",3);}
    prtitab(z,fm_uu5,&volgnr,3,-1); if(short_list=='J') prttitle(z++,"Ft.Nr",0x13); else prttitle(z++,"VolgNr",0x13);
    prtitab(z,fm_odat,&dt_bew,1,-1); prttitle(z++,"Datum",0x43);
  }
  prtitab(z,fm_obd,&bd_inc,0,-1); prttitle(z++,"Totaal",0x13);
  prtitab(z,fm_obd,&bd_exc,0,-1); prttitle(z++,"Belastb",0x13);
  prtitab(z,fm_obd,&bd_btw,0,-1); prttitle(z++,"BTW",0x13);
  prtitab(z,fm_obd,&bd_div,1,-1); prttitle(z++,"Divers",0x13);
	if(prt_fdet=='J'){prtitab(z,VarTextFmt(4,0),txt_voldaan,1,-1); prttitle(z++,"Vold",3);}
  if(fldlen(4,13)){
    prtitab(z,fm_obd,&bd_exc,1,-1); prttitle(z++,"Exclus.",0x13);
    prtitab(z,fm_obd,&bd_btw,1,-1); prttitle(z++,"BTW",0x13);
  }
  prtbuf(3);
  p_pdfname("Facturenlijst",*u(26,2),*u(26,3));
	no_header:;
  p_opened=YES;
}

static init_rek()
{
  bdt_inc=0;bdt_exc=0;bdt_btw=0;bdt_div=0;
	rbdt_inc=0;rbdt_exc=0;rbdt_btw=0; rbdt_div=0;
}

static prt_bew()
{
  int16 k;
  double bd_dif_;

  zero(tekst,sizeof tekst);
  journl=*s(stu_bew,2);
  volgnr=*u(stu_bew,3);
  dt_bew=*u(stu_bew,4);
  bd_exc=0;bd_btw=0;bd_div=0;
  bd_inc=*d(stu_bew,32);
  get_detail();
  if(stu_lk==1)bd_inc=-bd_inc;
  bd_dif_=bd_inc-bd_exc-bd_btw-bd_div;
  if(!is_nul(bd_dif_)) bd_div+=bd_dif_;
/*  bd_btw=bd_inc-bd_exc; */
	zero(txt_voldaan,sizeof txt_voldaan); if(is_voldaan(*l(stu_bew,1))) copy ("JA",txt_voldaan,2);
	if(prt2xls){
		XlsKol=1;
		WriteFld2Xls(XlsRij,XlsKol++,stu_lk,3,0);
		WriteVar2Xls(XlsRij,XlsKol++,fm_uu5,&volgnr,0);
		XlsWrite(XlsRef,XlsRij,XlsKol++,3,(char *)&dt_bew,StylDate); //WriteVar2Xls(XlsRij,XlsKol++,fm_odat,&dt_bew,StylDate);
		WriteVar2Xls(XlsRij,XlsKol++,fm_obd,&bd_inc,0);
		WriteVar2Xls(XlsRij,XlsKol++,fm_obd,&bd_exc,0);
		WriteVar2Xls(XlsRij,XlsKol++,fm_obd,&bd_btw,0);
		WriteVar2Xls(XlsRij,XlsKol++,fm_obd,&bd_div,0);
		WriteVar2Xls(XlsRij,XlsKol++,fm_os2,&txt_voldaan,0);
		XlsRij++;
	}
	else if(prt_fdet=='J') {for(k=1;k<20;k++) prtinfo(k,0);nextline();}
  printed=YES;
	if(txt_voldaan[0]) tbdt_voldaan+=bd_inc; else tbdt_nietvoldaan+=bd_inc;
  bdt_inc+=bd_inc;bdt_exc+=bd_exc;bdt_btw+=bd_btw; bdt_div+=bd_div;
	rbdt_inc+=bd_inc;rbdt_exc+=bd_exc;rbdt_btw+=bd_btw; rbdt_div+=bd_div;
}

static get_detail()
{
  int16 k,stu_,mode_;
  double *pd_,bd_;
 
  stu_=stu_bew;
  if(allow_yr && last_arc && dt_bew<=last_arc){/* indien gearchiveerd */
    if(fldlen(stu_,38)){
      copy(s(stu_,38),(char *)&bd_exc,8);
      copy(s(stu_,38)+8,(char *)&bd_div,8);
      copy(s(stu_,38)+40,(char *)&bd_btw,8);
      if(stu_lk==1)bd_=-bd_inc; else bd_=bd_inc;
      bd_=bd_-bd_exc-bd_btw-bd_div;
      if(is_nul(bd_)) goto endsr;/* bedragen goed ingevuld bij archivatie */
    }
    stu_=86;/* haal de bedragen uit het archief */
  }
  copy(s(stu_,1),buf750,fldlen(stu_,0));
  fasinit(stu_); *s(stu_,2)=journl; *u(stu_,3)=volgnr; mode_=1;
  FOREVER{
    next:;
    if(faskeyi(stu_,1,mode_)) break;mode_=2;
    if(*s(stu_,2)!=journl) break;
    if(*u(stu_,3)!=volgnr) break;
    if(*u(stu_,4)!=dt_bew) goto next;
    if(*u(stu_,5)==*u(stu_lk,1)+(stu_lk-1)*30000) goto next;/* niet K/L */
    pd_=&bd_div;
    if(*u(stu_,5)>=60000){
      fasinit(3);*u(3,1)=*u(stu_,5)-60000; fasgeti(3);
			if(fldlen(4,11) && ((*s(3,2) &0xF0)>>4)==9) goto next;
      for(k=0;k<5;k++){
	if(*l(3,2)==btws[k]) break;
      }
      if(k<5) pd_=&bd_btw;
      else{
	for(k=0;k<10;k++){
	  if(*l(3,2)==noomzet[k]) break;
	}
	if(k>=10) pd_=&bd_exc; else pd_=&bd_div;
      }
    }
    if(stu_lk==1){
      *pd_+=*d(stu_,32);
    }
    else {
      *pd_-=*d(stu_,32);
    }

  }
  copy(buf750,s(stu_,1),fldlen(stu_,0));
  endsr:;
}
 
static rec_get(stu_)
int16 stu_;
{
  int16 ks,k;
  flag stop=NO;

  if(allow_yr==NO && stu_==86) goto endsr;
  FOREVER{
    ks=faskeyi(stu_,4,2);
    if(*u(stu_,5)!=*u(stu_lk,1)+(stu_lk-1)*30000) stop=YES;
    if(ks || stop){
      if(stu_==86) chg86_1(0L); else chg4_1(0L);
      break;
    }
    else{
      for(k=0;k<80;k++) if(j_tab[k].nr==*s(stu_,2)) break;
      if(j_tab[k].typ==j_typ) break;
    }
  }
  endsr:;
}

static next_rec()
{
  rec_get(stu_bew);
  if(val4_1()==0 && (allow_yr==NO || val86_1()==0)) {return NO;}
  FOREVER{
    if(val4_1()==0) {stu_bew=86;break;}
    if(allow_yr==NO || val86_1()==0) {stu_bew=4;break;}
    if(*s(4,8)<*s(86,8)) {stu_bew=4;break;}
    if(*s(86,8)<*s(4,8)) {stu_bew=86;break;}
    if(*s(4,9)<*s(86,9)) {stu_bew=4;break;}
    if(*s(86,9)<*s(4,9)) {stu_bew=86;break;}
    if(*u(4,10)<*u(86,10)) {stu_bew=4;break;}
    stu_bew=86;break;
  }
  return YES;
}

static prt_endr(mode_)/* YES = totaal lijst */
int16 mode_;
{
  int16 k;

	if(p_opened){
		if(mode_==0){
			if(printed){
				bd_inc=rbdt_inc;bd_exc=rbdt_exc;bd_btw=rbdt_btw; bd_div=rbdt_div;
				
				if(prt_fdet=='J'){
					nextline();
					copy("Totaal :",s(stu_lk,3),10);prtinfo(1,2); fasgeti(stu_lk);
					for(k=4;k<=7;k++) prtinfo(k,2);nextline();nextline();nextline();
				}
				else{
					for(k=1;k<=7;k++) prtinfo(k,0);nextline();
				}
				tbdt_inc+=bd_inc;tbdt_exc+=bd_exc;tbdt_btw+=bd_btw; tbdt_div+=bd_div;
			}
		}
		else {
			bd_inc=tbdt_inc;bd_exc=tbdt_exc;bd_btw=tbdt_btw; bd_div=tbdt_div;
			nextline();
			if(prt_fdet=='J'){
				prttext("<b>Totaal lijst :<b>");nextline();
				for(k=4;k<=7;k++) prtinfo(k,2);nextline();nextline();nextline();
				prttext("Totaal voldaan:<b>"); prtifld(fm_obd,&tbdt_voldaan); prttext("<b>   Totaal niet-voldaan:<b>"); prtifld(fm_obd,&tbdt_nietvoldaan);
			}
			else{
				fasinit(stu_lk);copy("Totaal lijst",s(stu_lk,3),20);
				for(k=1;k<=20;k++) prtinfo(k,2);
			}
			nextline();
		}
  }
  else if(printed){
    bd_inc=bdt_inc;bd_exc=bdt_exc;bd_btw=bdt_btw; bd_div=bdt_div;
    if(prt_fdet=='J'){
			if(short_list!='J'){
				nextline();
				copy("Totaal",tekst,7);
				for(k=4;k<=7;k++) prtinfo(k,2);
				nextline();
			}
      if(skippage=='J') {prtform(0);free=999;} 
			else if(short_list!='J') {nextline();nextline();}
    }
    else{
      for(k=1;k<=20;k++) prtinfo(k,0);nextline();
    }
    tbdt_inc+=bd_inc;tbdt_exc+=bd_exc;tbdt_btw+=bd_btw; tbdt_div+=bd_div;
  }
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}

static OpenXlsFile(text_,datum_)
char *text_;
unsigned datum_;
{
	int16 pos_,dd,mm,yy;
  char string[100];
				
  zero(string,sizeof string);
	pos_=copy0(text_,&string[0],30);
  if(datum_){
    string[pos_++]=' ';
    jddate(datum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
	pos_+=copy0(".XLS",&string[pos_],4);
	
  pos_=XlsCreate(string);

	return pos_;
}

static initload()
{
  int16 k;

  fasunlck(0);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;
  allow_yr=NO; if(fldlen(86,1)>0) allow_yr=YES;

  if(credt_allow) fileopen(1);
  if(debit_allow) fileopen(2);
  fileopen(3);
  fileopen(4);
  if(allow_yr) fileopen(10);

	sysget( 294,4,def_munt);
  sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);
  sysget( 788,5*4,&btws[0]);
  sysget( 968,10*4,&noomzet[0]);
  sysget(1858,2,&last_arc);
  for(k=0;k<15;k++){
    sysget(788+k*4,4,&df_grb[k]);
    df_recnr[k]=getgrb(df_grb[k]);
  }
  sysget(1918,2,&sear_stt);
  sysget(2212,4,talen);
  sysget(3876,2,&sys3876);
  for(k=0;k<80;k++) sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
  pu_4_1=u(4,1); pl_4_1=l(4,1); pd_4_32=d(4,32); len4_1=fldlen(4,1);
  pu_86_1=u(86,1); pl_86_1=l(86,1); len86_1=fldlen(86,1);
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

static long val86_1()
{
  if(len86_1==4) return *pl_86_1;
  else return (long)(*pu_86_1);
}
				
static chg86_1(value_)
long value_;
{
  if(len86_1==4) *pl_86_1=value_;
  else *pu_86_1=value_;
}

static uint16 getgrb(lgrb)
long lgrb;
{
  uint16 retcd=0;
									
  if(*(char *)&lgrb!=0xFF && *(char *)&lgrb!=0x00 && scrcount<23){
    *l(3,2)=lgrb;
    *u(3,1)=0;
    search(3,2);
    if(errnum){
      if(notfound==0){
	scrget(1,170);
	scrcount=1;
      }
      scrifld(scrcount++,fm_ogrb,&lgrb);
      if(errnum==39) errnum=28;
      notfound=errnum;errnum=0;
    }
    else{
      retcd=*u(3,1)+60000;
    }
  }
  return retcd;
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

static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
}

static pr_rk_nm()
{
  if(p_opened==NO) open_prt();

  if(prt2xls==NO){
		free_tst(5);
		if(prt_fdet=='J' && short_list!='J'){
			prttext("  <b>");
			if((stu_lk==1 && lvcd) || (stu_lk==2 && klcd)) prtfld(stu_lk,2,-1);
			else prtfld(stu_lk,1,-1);
			prttext("  ");
			prtfld(stu_lk,3,-1);
			prttext("<b>");
			nextline();nextline();
		}
	}
}

static free_tst(aantal)
int16 aantal;
{
  if(free<aantal) {prtform(0);free=999;}
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static nextline()
{
  free=prtline();
}

static selp_ask()
{
  int16 key;
  char choice;

  if(selp_stu!=stu) selp_wis();
  selp_stu=stu;

  FOREVER{
    scrget(1,46);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(1,0x0581);
    if(key==101) return YES;
    if(key==111) ovlexit(-1);
    if(key==108) {selp_use=YES;break;}
    if(key==109) {selp_use=NO;break;}
    switch(choice){
      case '1': selp_ge=NO;selp_upd(0,choice);break;
      case '2': selp_ge=YES;selp_upd(0,choice);break;
      case '3': selp_le=NO;selp_upd(1,choice);break;
      case '4': selp_le=YES;selp_upd(1,choice);break;
      case '5': selp_upd(2,choice);break;
      case '6': selp_upd(3,choice);break;
      case '7': selp_wis();scrget(1,7);scrupd(-3,0);break;
      default : errnum=34; break;
    }
  }
  return NO;
}

static taal_upd(z,fld_)
int16 z,fld_;
{
  if(fldlen(stu,fld_)!=1) scrfld(z,stu,fld_);
  else{
    if(taal_i=='\0' && *s(stu,fld_)!=0xFE){
      if(*s(stu,fld_)>=4) *s(stu,fld_)=0;
      taal_i=talen[*s(stu,fld_)];
    }
    scrifld(z,fm_us1_U,&taal_i);
  }
}

static taal_chk(fld_)
int16 fld_;
{
  int16 k;
									
  if(fldlen(stu,fld_)==1){
    for(k=0;k<4;k++) if(taal_i==talen[k]) {*s(stu,fld_)=k;break;}
    if(k==4 && taal_i!='\0') {errnum=34;return YES;}
  }
  return NO;
}

static selp_upd(bfnr,men_keuze)
int16 bfnr;
char men_keuze;
{
  int16 k,curs,z,curs_taal;
 
  men_keuze=men_keuze-'1'; taal_i='\0';
  copy(selp_bf[bfnr],s(stu,1),fldlen(stu,0));
  if(stu==1){/* leveranciers */
    curs=2;
    redo_l:;
    scrget(2,6); z=1;
    scrinq();
    z=1;
    scrifld(z++,fm_os20,selp_txt[men_keuze]);
    if(lvcd) scrfld(z++,stu,2); else scrofld(z++,stu,1,-1);
    for(k=3;k<16;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,16);
    for(k=17;k<MAXFLD;k++) scrfld(z++,stu,k);
    scrupd(curs,0x0080);
    if(taal_chk(16)) {curs=curs_taal;goto redo_l;}
  }

  else if(stu==2){/* klanten */
    curs=2;
    redo_k:;
    scrget(2,7); z=1;
    scrinq();
    z=1;
    scrifld(z++,fm_os20,selp_txt[men_keuze]);
    if(klcd) scrfld(z++,stu,2); else scrofld(z++,stu,1,-1);
    for(k=3;k<24;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,24);
    for(k=25;k<MAXFLD;k++) scrfld(z++,stu,k);
    scrupd(curs,0x0080);
    if(taal_chk(24)) {curs=curs_taal;goto redo_k;}
  }
  copy(s(stu,1),selp_bf[bfnr],fldlen(stu,0));
}

static selp_tst()/* 00.04 */
{
  int16 g,k,type,parm,f_len,index;
  char fldtype,*stu_base,*adres,ret;

  if(selp_use==NO) return YES;
  stu_base=s(stu,1);
  for(k=2;k<MAXFLD;k++){
    f_len=fieldspc(stu,k,&selp_fld,selp_des);
    if(f_len>0){
      fldtype=(selp_des[1] & 0x38)/8;
      if((stu==2 && k==24) || (stu==1 && k==16)) fldtype=6;
      switch(fldtype){
	case 0:/* date */
	  type=1;parm=11;
	  break;
	case 1:/*string*/
	  type=2;
	  break;
	case 2:/*num*/
	  type=1;parm=selp_des[1]&7;
	  break;
	case 3:/*bt#*/
	  type=1;parm=3;
	  break;
	case 4:/* rek# */
	  type=3;parm=5;
	  break;
	case 5:/* grb */
	  type=1;parm=3;
	  break;
	case 6:
	  type=4;
	  break;
	default: type=0;break;
      }
      index=selp_fld-stu_base;
      for(g=0;g<4;g++){
	adres=&selp_bf[g][index];
	if(used(adres,f_len)){
	  ret=3;
	  switch(type){
	    case 1: ret=comp_num(adres,selp_fld,parm); break;
	    case 2: ret=comp_str(adres,selp_fld,f_len); break;
	    case 3: ret=comp_byt(adres,selp_fld,f_len); break;
	    case 4: ret=comp_taa(adres,selp_fld,f_len); break;
	  }
	  if(ret==3) goto next;
	  if(g==0 && (ret==1 || (selp_ge && ret==0))) goto next;
	  if(g==1 && (ret==2 || (selp_le && ret==0))) goto next;
	  if(g==2 && ret==0) goto next;
	  if(g==3 && ret!=0) goto next;
	  return NO;
	}
	next:;
      }
    }
  }
  return YES;
}

static comp_taa(p1,p2,len)
char *p1, *p2;
int16 len;
{
  if(*p1==*p2) return 0;
  if(*p1<*p2) return 1;
  if(*p1>*p2) return 2;
}

static used(b,len)
char *b;
int16 len;
{
  while(len-->0)
    if(*b++!=0xFE) return YES;
  return NO;
}
 
static comp_num(p1,p2,type)
char *p1, *p2;
int16 type;
{
  int16 ret;
  uint16 jj,mm,dd, oldp2;
 
  if(type==11){
    oldp2=*(uint16 *)p2;
    if(*(uint16 *)p1>=44 && *(uint16 *)p1<=409){
      jddate(*(uint16 *)p2,&jj,&mm,&dd);
      *(uint16 *)p2=datejd(1892,mm,dd);
    }
  }
  switch(type){
    case 0:
      if(*(int16 *)p1 < *(int16 *)p2) ret=1;
      else if(*(int16 *)p1 > *(int16 *)p2) ret=2;
      else ret=0;
      break;
    case 1:
    case 11:
      if(*(uint16 *)p1 < *(uint16 *)p2) ret=1;
      else if(*(uint16 *)p1 > *(uint16 *)p2) ret=2;
      else ret=0;
      if(type==11) *(uint16 *)p2=oldp2;
      break;
    case 3:
      if(*(long *)p1 < *(long *)p2) ret=1;
      else if(*(long *)p1 > *(long *)p2) ret=2;
      else ret=0;
      break;
    case 4:
      if(*(float *)p1 < *(float *)p2) ret=1;
      else if(*(float *)p1 > *(float *)p2) ret=2;
      else ret=0;
      break;
    case 5:
      if(*(double *)p1 < *(double *)p2) ret=1;
      else if(*(double *)p1 > *(double *)p2) ret=2;
      else ret=0;
      break;
    default:
      ret=3;
      break;
  }
  return ret;
}
 
static comp_str(p1,p2,len)
char *p1, *p2;
int16 len;
{
  char b1,b2;
  int16 len1,len2;

  len1=len;len2=len;
  FOREVER{
    FOREVER{
      if(!(b1=*p1++)){len1=-1; break;}/* 0-byte found */
      if(!len1--) break;
      if(b1>='a' && b1<='z') b1=b1-'a'+'A';
      if((b1>='A' && b1<='Z') || (b1>='0' && b1<='9') || (b1=='?')) break;
      if(b1=='*') return 0;
    }
    FOREVER{
      if(!(b2=*p2++)){len2=-1; break;}/* 0-byte found */
      if(!len2--) break;
      if(b2>='a' && b2<='z') b2=b2-'a'+'A';
      if((b2>='A' && b2<='Z') || (b2>='0' && b2<='9')) break;
    }
    if(len1<0 || len2<0){
      if(len1<0 && len2<0) return 0;
      if(len1<0) return 1; else return 2;
    }
    if(b1=='?') b1=b2;
    if(b1<b2) return 1;
    if(b1>b2) return 2;
  }
}
 
static comp_byt(p1,p2,len)
int16 len;
char *p1,*p2;
{
  while(len-->0){
    if(*p1<*p2) return 1;
    if(*p1>*p2) return 2;
    p1++; p2++;
  }
  return 0;
}
 
static selp_wis()
{
  int16 j;

  for(j=0;j<sizeof selp_bf;j++) *(&selp_bf[0][0]+j)=0xFE;
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
