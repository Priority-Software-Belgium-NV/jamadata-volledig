/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* BKH0058GetD() {return &zzvw;}
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" int IbanTools(char *pIBAN,char *pBIC,char *pJamaRek,int16 ToolNr); // 0 = check iban/bic, 1=check+fill bic, 2=convert jamarek -> IBAN/BIC
extern "C" int16 Search(int stu_,int mod_);
extern "C" char *VarTextFmt(int len_,int update_);

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
static int16 ovlcall();
extern "C" char BKH0058dat[] = "BKH0058  00:03 21/11/17 (c) Jamadata";   // lijst openstaande/vervallen facturen

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define TABSIZ          4000
#define DIM_TBREC4      4000
#define MAXFLD          120
#define flag            uint16

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF
								
static char *types[5]={"","Fact","C.N.","Bet.","Div."};
 
extern uint16 jamin1[5];
extern int16 retcall,parmcall[8];
extern char info[];
extern char *s();
extern int16 *is();
extern uint16 *us(),dateadd(),datejd();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();

/* --------------------------- Declaratie functies ---------------------- */
static int OpenXlsFile(char *text_, short unsigned bdatum_, short unsigned edatum_);
static double Round(double bd_, short int q_decim_);
static void add_bew(void);
static int comp_byt(char *p1, char *p2, int16 len);
static int comp_num(char *p1, char *p2, int16 type);
static int comp_str(char *p1, char *p2, int16 len);
static int comp_taa(char *p1, char *p2, int16 len);
static void compress(void);
static int copy0(char *ps,char *pd,int max);
static void corr_y2000(uint16 bstu_, uint16 searcnr_);
static void del_line(int16 line);
static void del_stuk(int16 k);
static void DisplayList(void);
static void dsp_factuur(int p_rec4_);
static void exec_lst(void);
static void fileopen(int16 nr_);
static int fmt_get(int16 stu_, int16 elet_);
static void initload(void);
static int is_nul(double bd_);
static void make_vstr(void);
static void nextline(void);
static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_);
static int selp_ask(void);
static int selp_tst(void);
static void selp_upd(int16 bfnr, char men_keuze);
static void selp_wis(void);
static void sort_tab(void);
static int taal_chk(int16 fld_);
static void taal_upd(int16 z, int16 fld_);
static void tab_chk(void);
static int used(char *b, int16 len);
/* ---------------------------------------------------------------------- */

static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us100[] = {7,0xC8,100,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_od9_2[] = {6,0x95,9,2,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_od7_2[] = {6,0x95,7,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_udatD[] = {4,0xC0,5,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_u_vv[]  = {15,0xC8,4,0,1,0,'0','9',' ',' ','E','E','-','-',0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_u_KL[]  = {11,0xC8,1,0,1,0,'K','K','L','L',0};
static char fm_u_OV[]  = {11,0xC8,1,0,1,0,'O','O','V','V',0};

static flag chk_btoeg=NO;
static flag sys3876;

static int16 form_dat[8],pr_mode,sfree=0,prtnr,j_tb[101],stu;
static int16 dg_arr[8],loaded,max_tbrec4;
static int16 nm_pdf_ok,prt2pdf;
static uint16 dt_spil,inq_rec,dt_boek;
static uint16 ref_yy,ref_jr,ref_vl,ref_nr,dt_bet;
static char ver_term[4],prt_page,verv_str[50],sel_nm[40];
static char b1784,type_fich;
static char def_munt[4],type_lst;
static flag sear_stt,first,sys1790;
static flag debit_allow=NO,credt_allow=NO,lvcd,klcd;
static int StylTotaal, StylDate, StylKlasse, StylNormal, StylTitel, Styl2Use;

// ----- XLS-FUNC 
extern int16 ilength; // XLS
static int XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol,XlsMaxKol,XlsMaxRij;
static int16 *pi,prt2xls; // XLS

static int fas_ret(char *s);
static int XlsCreate(char *name);
static int XlsClose(int16 ref,int16 Action);
static int XlsSaveAsPdf(int16 ref);
static int XlsWrite(int16 ref,int16 rownr,int16 colnr,int16 type,char *val, int16 StyleIx);
static int XlsSelectWorkSheet(int16 ref,int16 WksNr,char *WksName); // WknNr = 1, 2, ... WksCount
static int XlsChart(int16 ref,int16 rowcnt,int16 colcnt,int16 chartType,char *title);
static int XlsGraf(int16 ref,int16 colnr,int16 chartType,long Color);
static int XlsRowSize(int16 ref,int16 rownr,int16 size);
static int XlsColumnSize(int16 ref,int16 rownr,int16 size);
static int XlsStyle(int16 ref, char *NumFormat,int16 Size,long Color,int16 BoldFlag,int16 ItalicFlag,int16 UnderlineFlag,int16 HorAlignment,int16 VerAlignment,long BackCol,int16 Pattern,int16 Kader,long KaderCol,int16 Lock,int16 Hide);
static int16 WriteVar2Xls(int16 rij_,int16 kol_,char *fmt_,char *pvar_,int16 StylIx);
static int16 WriteFld2Xls(int16 rij_,int16 kol_,int16 stu_,int16 fld_,int16 StylIx);

static int XlsOpen(char *name); // XLS open for read
static int XlsGetMaxKol(int16 ref);
static int XlsGetMaxRij(int16 ref);
static int XlsReadString(int16 ref,int16 rownr,int16 colnr,char *ret_string, int16 MaxLen);
static int XlsReadInt(int16 ref,int16 rownr,int16 colnr);
static double XlsReadDouble(int16 ref,int16 rownr,int16 colnr);
static short unsigned XlsReadDate(int16 ref,int16 rownr,int16 colnr);


#include "Std\XlsFunc.CPP"
// ---------------------------------------

static int16 selp_stu=0;
static char selp_bf[4][1000],selp_des[40],*selp_fld;
static char taal_i,talen[4];
static flag selp_use,selp_ge,selp_le;
static char *selp_txt[6]={"Ondergrens (>)","Ondergrens (> of =)",
		"Bovengrens (<)","Bovengrens (< of =)",
		"Gelijk","Niet gelijk"};

static struct _st {
  long rec4;
  uint16 jr;
  uint16 vl;
  uint16 ft_date;
  uint16 verv_dt;
  uint16 r_yy;
  uint16 r_jr;
  uint16 r_vl;
  char typ;                                     /* 1=ft, 2=kn, 3=bet, 4=div */
  char status;   /* 0=n.verv/n.vold 1=n.verv/vold 2=verv/n.vold 3=verv/vold */
  char dum;
  double ebedr;
} st[TABSIZ];

static long tb_rec4[DIM_TBREC4];	


static char *p_data;
static long *pl_80_1;
									
static char seqo_str[1000];
static char filnam[40],fmt[40];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;




extern "C" void BKH0058cod(void)
{
  int16 k,z,key,curs=2;
 
  initload();
  if(type_lst=='\0') type_lst='V';
  if(dt_spil==0) dt_spil=*us(25,2);if(type_fich=='\0') type_fich='K';
  if(dt_bet==0) dt_bet=*us(25,2); zeros(sel_nm,sizeof sel_nm);
  inq_rec=0;
  FOREVER{
    redo:;
    scrget(1,206);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0058A");
		scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
		if(sys1790 & 0x10) scraddpicto(2,0,72,22,4,2,573,0,0,"Maak XLS"); 

    scrfld(z++,25,1);
    scrifld(z++,fm_u_OV,&type_lst);
    scrifld(z++,fm_udat,&dt_spil);
    scrifld(z++,fm_udat,&dt_bet);
    scrifld(z++,fm_u_KL,&type_fich);
    scrifld(z++,fm_us40,sel_nm);
    scrifld(z++,fm_udat,&dt_boek);
    key=scrupd(curs,0x281); curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) break;
    if(key==111) ovlexit(*us(25,4));
    if(dt_spil==0) {errnum=38;goto redo;}
    if(sel_nm[0]){
      if(type_fich=='L') stu=1; else stu=2;
      bcopy(sel_nm,s(stu,3),fldlen(stu,3));
      if(Search(stu,0)){curs=6;goto redo;}
      bcopy(s(stu,3),sel_nm,fldlen(stu,3));
      inq_rec=*us(stu,1);
    } else inq_rec=0;
    prt2pdf=NO;if(key==5001) {prt2pdf=YES;key=108;}
		prt2xls=NO;if(key==5002) {prt2xls=YES;key=108;}
    if(key==108) exec_lst();
		if(key==110) DisplayList();
  }
  ovlexit(-1);
}
 
static void DisplayList(void)
{
  int16 z,j,k,ks,kmode_,kod_;
  uint16 ft_nr,dt_ft,dt_verv,rec_,sear_nr_,journl_;
  double bd_,ft_bd,tot_ftbd,ttot_ftbd;
	int key,len_,start_,typ,ScreenLines=18;

	fasunlck(-1);
  if(type_fich=='L') stu=1; else stu=2;
  selp_use=NO;
  if(selp_ask()) goto endsr;
  max_tbrec4=0;
	scrget(1,7);scrupd(-3,0);
  kod_=1; if(fldlen(stu,2)) kod_=2;
 
  ttot_ftbd=0;
  fasinit(stu); *us(stu,1)=inq_rec; if(inq_rec) fasgeti(stu);kmode_=1;
  FOREVER{
    next:;
    if(faskeyi(stu,2,kmode_)) break; kmode_=2;
    if(inq_rec && *us(stu,1)!=inq_rec) break;
    if(selp_tst()==NO) goto next;
    sear_nr_=*us(stu,1)+30000*(stu-1);
    corr_y2000(4,sear_nr_);
    fasinit(4);*us(4,5)=sear_nr_;

    loaded=0;
    FOREVER{
      next4:;
      ks=faskeyi(4,4,2);
      if(ks || *us(4,5)!=sear_nr_) break;
      if(dt_boek && dt_boek<*us(4,4)) goto next4;
      add_bew();
    }
    compress();/* schrap voldane stukken */
    tab_chk();/* vergelijk met datums en minimum */
    if(loaded){
      tot_ftbd=0;
      for(k=0;k<loaded;k++){
				tb_rec4[max_tbrec4++]=st[k].rec4;
				if(max_tbrec4>=DIM_TBREC4) break;
			}
			if(max_tbrec4>=DIM_TBREC4) break;
		}
	}
	if(max_tbrec4==0){errnum=34; goto endsr;}

  start_=0; 
  FOREVER{
		redo:;
    scrnum=0;scrget(1,98);z=1;
    if(type_lst=='V') scrifld(z++,VarTextFmt(20,0)," Vervallen facturen ");
    else scrifld(z++,VarTextFmt(22,0)," Openstaande facturen ");
	  start_++;scrifld(z++,fm_ou4,&start_);start_--;scrifld(z++,fm_ou4,&max_tbrec4);
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=max_tbrec4) break;
			fasinit(4);*l(4,1)=tb_rec4[k];fasgeti(4);
			fasinit(stu);*u(stu,1)=*u(4,5)-(stu-1)*30000; fasgeti(stu);
      bd_=*d(4,32); if(stu!=2) bd_=-bd_;
			journl_=*s(4,2); j=j_tb[journl_];
			if(j<3 || j>8){if(bd_<0) typ=2; else typ=1;}
			else if(k<5) typ=3;
			else typ=4;
      scrofld(z++,stu,3,32);
			scrifld(z++,fm_os1,&types[typ][0]);
			scrofld(z++,4,3,-1);
			if(typ<3) scrofld(z++,4,20,-1); else scrofld(z++,4,4,-1);
			scrifld(z++,fm_od6_2,&bd_); if(stu==2 && typ<3) scraddpicto(10+k-start_,z-1,1,0,2,1,43,0,6,"Factuur");
			if(typ<3) scrofld(z++,4,21,-1); else scrofld(z++,4,4,-1);

    }
    key=scrupd(-1,0x7);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5010 && key<5010+ScreenLines) dsp_factuur(start_+key-5010);

    switch(key){
			case 12      :// PgUp 
	//		case 5001    :
			case 102     : if(start_>0){
											 start_-=ScreenLines; if(start_<0) start_=0;scrnum=0;
										 }
										 break;
			case 13      :// PgDn 
	//		case 5002      :// PgDn 
			case 103     : if((start_+ScreenLines)<max_tbrec4) {start_+=ScreenLines;scrnum=0;}
										 break;
			case 101     :
			case 106     : goto endsr;// annuleer 
										 break;
			default      : break;
    }
	}
	endsr:;
	
}

static void dsp_factuur(int p_rec4_)
{
  int16 k;
  uint16 journl_,volgnr_,bk_dat_,klgrec_;
 
	fasinit(4);*l(4,1)=tb_rec4[p_rec4_];fasgeti(4);
  klgrec_=*u(stu,1);
  journl_=*s(4,2);volgnr_=*u(4,3); bk_dat_=*u(4,4);
 
  *u(26,1)=1; *u(26,2)=bk_dat_;*u(26,5)=volgnr_; *u(26,26)=klgrec_; 
  if(ovltest(257)) ovlcall(257,0);
  else if(ovltest(263)) ovlcall(263,0);

  endsr:;
  fasinit(stu);*u(stu,1)=klgrec_;fasgeti(stu);
}

static void exec_lst(void)
{
  char type_[5],opmstr_[60],nm_list_[100];
  int16 z,j,k,ks,kmode_,kod_;
  uint16 ft_nr,dt_ft,dt_verv,rec_,sear_nr_;
  double ft_bd,tot_ftbd,ttot_ftbd,bd_cum;

	fasunlck(-1);
  if(type_fich=='L') stu=1; else stu=2;
  selp_use=NO;
  if(selp_ask()) goto endsr;
  max_tbrec4=0;
  kod_=1; if(fldlen(stu,2)) kod_=2;
  if(prt2xls){
		scrget(1,7);scrupd(-3,0);XlsRef=-1; zeros(nm_list_,sizeof nm_list_);
    if(type_lst=='V') k=copy0("Vervallen facturen ",nm_list_,30);
    else k=copy0("Openstaande facturen ",nm_list_,30);
    if(stu==1) k+=copy0("leveranciers",&nm_list_[k],15); else k+=copy0("klanten",&nm_list_[k],10);
		XlsRef=OpenXlsFile(nm_list_,dt_spil,0);
    if(XlsRef<=0) {errnum=1;goto endsr;}
		if(type_lst=='V') XlsSelectWorkSheet(XlsRef,1,"Vervallen facturen");
		else XlsSelectWorkSheet(XlsRef,1,"Openstaande facturen");
		XlsColumnSize(XlsRef,2,40);XlsColumnSize(XlsRef,9,30);XlsColumnSize(XlsRef,10,30);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
		StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);

		XlsRij=1;XlsKol=1;Styl2Use=StylTitel; // StylTitel;
	  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Code",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Naam",Styl2Use);
#if FLAGPED
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"BTW-nummer",Styl2Use);
#endif
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Type",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"FactNr",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Factuurdatum",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Vervaldatum",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Bedrag",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Laatste rappel",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Opmerking",Styl2Use);
		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Mededeling",Styl2Use);
		XlsRij++;XlsKol=1;
    scrget(1,6);scrupd(-3,0);
  }
  else{
    scrget(1,7);scrupd(-3,0);
		if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) ovlexit(-1);
    sfree=999;
    prtfld(25,1,25);
    if(type_lst=='V') prttext("<t28><b>Vervallen facturen ");
    else prttext("<t28><b>Openstaande facturen ");
    if(stu==1) prttext("leveranciers"); else prttext("klanten");
    prttext("<b><t64>Einddatum : ");prtifld(fm_udat,&dt_spil,-1);
    prttext(" (");prtifld(fm_udat,&dt_bet,-1);prttext(")<t97>");prtfld(25,2,-1);prttext("<t120>Blz.<ppp>.");
    prtbuf(1);z=1;
    prttab(z,stu,kod_,1,-1); prttitle(z++,"Code",3);
    prttab(z,stu,3,1,30); prttitle(z++,"Naam",3);
    prtitab(z,fm_os30,verv_str,1,20);prttitle(z++,"Betalingscondities",3);
    prtitab(z,fm_os4,type_,3,-1); prttitle(z++,"Type",3);
    prtitab(z,fm_uu5,&ft_nr,1,-1); prttitle(z++,"Fact.NO",0x13);
    prtitab(z,fm_udat,&dt_ft,1,-1); prttitle(z++,"Fact.dat",0x13);
    prtitab(z,fm_udat,&dt_verv,1,-1); prttitle(z++,"Verv.dat",0x13);
    prtitab(z,fm_od7_2,&ft_bd,1,-1); prttitle(z++,"Fact.bedr",0x13);
#if !FLAGGRS
    prtitab(z,fm_od6_2,&bd_cum,1,-1); prttitle(z++,"Cum.bedrag",0x13);
#endif
    if(type_lst=='V' && type_fich=='K' && fldlen(4,30)){
      prttab(z,4,30,1,-1); prttitle(z++,"L.rappel",3);
			prttab(z,4,29,0,-1); prttitle(z++,"Nr",0x13);
    }
    else{
      prtitab(z,VarTextFmt(35,0),opmstr_,0,-1); prttitle(z++,"Opmerking",3);
    }
    prtbuf(3);
    if(type_lst=='V') p_pdfname("Vervallen facturen",dt_spil,0);
    else p_pdfname("Openstaande facturen",dt_spil,0);
    
  }
  sfree=999;
  ttot_ftbd=0;bd_cum=0;
  fasinit(stu); *us(stu,1)=inq_rec; if(inq_rec) fasgeti(stu);kmode_=1;
  FOREVER{
    next:;
    if(faskeyi(stu,2,kmode_)) break; kmode_=2;
    if(inq_rec && *us(stu,1)!=inq_rec) break;
    if(selp_tst()==NO) goto next;
    sear_nr_=*us(stu,1)+30000*(stu-1);
    corr_y2000(4,sear_nr_);
    fasinit(4);*us(4,5)=sear_nr_;

    loaded=0;
    FOREVER{
      next4:;
      ks=faskeyi(4,4,2);
      if(ks || *us(4,5)!=sear_nr_) break;
      if(dt_boek && dt_boek<*us(4,4)) goto next4;
      add_bew();
    }
    compress();/* schrap voldane stukken */
    tab_chk();/* vergelijk met datums en minimum */
    if(loaded){
      tot_ftbd=0;bd_cum=0;
      make_vstr();
      for(k=0;k<loaded;k++){
				fasinit(4);*l(4,1)=st[k].rec4;fasgeti(4);
				dt_ft=st[k].ft_date;ft_nr=st[k].vl;
				zeros(type_,sizeof type_);bcopy(types[st[k].typ],type_,4);
				dt_verv=st[k].verv_dt;
				ft_bd=st[k].ebedr;bd_cum+=ft_bd;
				zeros(opmstr_,sizeof opmstr_);j=copy0(s(4,28),&opmstr_[0],fldlen(4,28)); 
				if(j && *s(4,27)) opmstr_[j++]='*'; copy0(s(4,27),&opmstr_[j],fldlen(4,27));
				if(prt2xls){
					XlsKol=1;
					if(fldlen(stu,2)) WriteFld2Xls(XlsRij,XlsKol++,stu,2,StylNormal);  
					else WriteFld2Xls(XlsRij,XlsKol++,stu,1,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,stu,3,StylNormal);
#if FLAGPED
					WriteFld2Xls(XlsRij,XlsKol++,stu,10,StylNormal);
#endif
					WriteVar2Xls(XlsRij,XlsKol++,fm_os4,type_,StylNormal);
					WriteVar2Xls(XlsRij,XlsKol++,fm_uu5,(char *)&ft_nr,StylNormal);
					WriteVar2Xls(XlsRij,XlsKol++,fm_udat,(char *)&dt_ft,StylDate);
					WriteVar2Xls(XlsRij,XlsKol++,fm_udat,(char *)&dt_verv,StylDate);
					WriteVar2Xls(XlsRij,XlsKol++,fm_od9_2,(char *)&ft_bd,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,4,30,StylDate);
					WriteFld2Xls(XlsRij,XlsKol++,4,28,StylDate);
					WriteFld2Xls(XlsRij,XlsKol++,4,27,StylDate);
					//WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(35,0),opmstr_,StylNormal);
					XlsRij++;XlsKol=1;
				}
				else{
					if(k==0) for(j=1;j<4;j++) prtinfo(j,0);
					for(j=4;j<20;j++) prtinfo(j,0);nextline();
				}
				tot_ftbd+=ft_bd;
      }
      if(prt2xls==NO) nextline();
      rec_=*us(stu,1);
      zeros(verv_str,sizeof verv_str); fasinit(4);
      fasinit(stu);bcopy("Totaal ==>",s(stu,3),11);
      dt_ft=0;ft_nr=0;type_[0]='\0';dt_verv=0;zeros(opmstr_,sizeof opmstr_);
      ft_bd=tot_ftbd;bd_cum=0;
      if(prt2xls==NO){
      	for(k=0;k<20;k++) prtinfo(k,2);nextline();nextline();
      }
      ttot_ftbd+=tot_ftbd;
      *us(stu,1)=rec_;fasgeti(stu);
    }
    if(sfree==-1) break;
  }
  zeros(verv_str,sizeof verv_str); fasinit(4);
  fasinit(stu);bcopy("Totaal lijst ==>",s(stu,3),20);
  dt_ft=0;ft_nr=0;type_[0]='\0';dt_verv=0;zeros(opmstr_,sizeof opmstr_);
  ft_bd=ttot_ftbd;bd_cum=0;
  if(prt2xls==NO){
    for(k=0;k<20;k++) prtinfo(k,2);nextline();nextline();
    prtform(0);
    prtclose();
  }
  else XlsClose(XlsRef,1);
  endsr:;
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;
  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}


static void make_vstr(void)
{
  int16 g,j,k;
  char term_[4];

  bcopy(s(stu,13),term_,3); term_[3]='\0';
	if(stu==1 && fldlen(stu,18) && cmpstr("DOM",s(stu,18),3)==0) g=3;
	else{
		g=0;
		for(k=0;k<3;k++){
			if(term_[k]=='\0') break;
			if(term_[k]=='E') {g=1;break;}
			if(term_[k]>='0' && term_[k]<='9') {g=2;break;}
		}
	}
  zeros(verv_str,sizeof verv_str);
  switch(g){
    case 1 : j=val(&term_[k+1]);j*=30;
	     if(j){
	       stcli_d(verv_str,(long)j,3,1);
	       bcopy(" dagen einde maand",&verv_str[3],18);
	     }
	     else {
	       bcopy("einde maand na ft.datum",verv_str,23);
	     }
	     break;
    case 2 : j=val(&term_[k]);
	     stcli_d(verv_str,(long)j,3,1);
	     bcopy(" dagen na ft.datum",&verv_str[3],18);
	     break;
    case 3 : bcopy("Domiciliering",&verv_str[0],18);
			 break;
    default: bcopy("Contant",verv_str,7);break;
  }
}


static void add_bew(void)
{
  int16 k,typ,kill_;
  char *pa;

  if(loaded==TABSIZ) compress();
  if(loaded==TABSIZ) goto endsr;

  pa=(char *)&st[loaded];/* dit element volledig op 0 zetten */
  for(k=0;k<sizeof(struct _st);k++) *pa++='\0';

  st[loaded].rec4=*l(4,1);
  st[loaded].jr=*s(4,2);
  st[loaded].vl=*us(4,3);
  st[loaded].ft_date=*us(4,4);
  st[loaded].ebedr=*d(4,32);
  if(stu!=2){
    st[loaded].ebedr=-st[loaded].ebedr;
  }
  st[loaded].r_yy=*s(4,8);
  st[loaded].r_jr=*s(4,9);
  st[loaded].r_vl=*us(4,10);
  k=j_tb[st[loaded].jr];
  if(k<3 || k>8){
    if(st[loaded].ebedr<0) typ=2; else typ=1;
    if(*us(4,20) && *us(4,20)<=st[loaded].ft_date) st[loaded].ft_date=*us(4,20);
    st[loaded].verv_dt=*us(4,21);
    if(st[loaded].verv_dt==0){
      bcopy(s(2,13),ver_term,4);
      ver_term[3]='\0';
      st[loaded].verv_dt=dateadd(st[loaded].ft_date,ver_term);
    }
  }
  else if(k<5) typ=3;
  else typ=4;
  st[loaded].typ=typ;
  kill_=NO;
  if(st[loaded].typ==1){
    if(type_lst=='O' && st[loaded].ft_date>dt_spil) kill_=YES;
//    WORDT IN TAB_CHK GEDELETE if(type_lst=='V' && st[loaded].verv_dt>dt_spil) kill_=YES;
  }
  else if(st[loaded].typ>1 && st[loaded].ft_date>dt_bet) kill_=YES;
  if(kill_) zeros((char *)&st[loaded].rec4,sizeof st[0]);
  else loaded++;
  endsr:;
}


static void compress(void)
{
  int16 k,n;
  double ebedrag;

  ebedrag=0;
  for(k=0;k<loaded;k++){
    ebedrag+=st[k].ebedr;
    st[k].status=0;
  }
  if(is_nul(ebedrag)){loaded=0;goto endsr;}

  for(k=0;k<loaded;k++){
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
    ebedrag=0;
    n=k-1;
    FOREVER{
      n++;
      if(n>=loaded) break;
      if(st[n].r_yy!=ref_yy || st[n].r_jr!=ref_jr || st[n].r_vl!=ref_vl) break;
      ebedrag+=st[n].ebedr;
    }
    if(!is_nul(ebedrag)){
      k=n-1;
    }
    else{
      FOREVER{/* schrap voldane */
	if(k==loaded) break;
	if(st[k].r_yy!=ref_yy || st[k].r_jr!=ref_jr || st[k].r_vl!=ref_vl) break;
	del_line(k);
      }
      k--;
    }
  }
  endsr:;
}


static void tab_chk(void)
{
  int16 g,k,n,vervallen;
/* controle op vervaldatums */
  if(loaded==0){loaded=0;goto endsr;}

/* duidt vervallen stukken aan */
	if(type_lst=='V'){
	  for(k=0;k<loaded;k++){
			if(st[k].verv_dt>dt_spil) {del_line(k);k--;} // de niet-vervallen eruit halen
		}
	}


  for(k=0;k<loaded;k++){
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
    vervallen=0;
    n=k-1;
    FOREVER{
      n++;
      if(n>=loaded) break;
      if(st[n].r_yy!=ref_yy || st[n].r_jr!=ref_jr || st[n].r_vl!=ref_vl) break;
      if(st[n].verv_dt<=dt_spil) vervallen=1;
    }
    if(vervallen){
      for(g=k;g<n;g++){
	st[g].status+=2;
      }
    }
    k=n-1;
  }
  sort_tab();
  endsr:;
}


static void sort_tab(void)
{
  int16 j,k,n,sw;
  char buf_[50];
									
  FOREVER{/* sorteren */
    sw=NO;
    for(k=0;k<loaded-1;k++){
      if(st[k].verv_dt > st[k+1].verv_dt){
	bcopy((char *)&st[k].rec4,buf_,sizeof st[0]);
	bcopy((char *)&st[k+1].rec4,(char *)&st[k].rec4,sizeof st[0]);
	bcopy(buf_,(char *)&st[k+1].rec4,sizeof st[0]);
	sw=YES;
      }
    }
    if(sw==NO) break;
  }
 
  for(k=0;k<loaded;k++){/* betalingen achter facturen zetten */
    redo_k:;
    if(st[k].verv_dt) break;
    if(st[k].dum==YES) continue;/* reeds verhuisd */
    if(st[k].r_yy==0 && st[k].r_jr==0 && st[k].r_vl==0) continue;/* voorschot */
    for(j=loaded-1;j>k;j--){
      if(st[j].r_yy==st[k].r_yy && st[j].r_jr==st[k].r_jr && st[j].r_vl==st[k].r_vl) break;
    }
    if(j>k){
      st[k].dum=YES;
      bcopy((char *)&st[k].rec4,buf_,sizeof st[0]);
      for(n=k+1;n<=j;n++){
	bcopy((char *)&st[n].rec4,(char *)&st[n-1].rec4,sizeof st[0]);
      }
      bcopy(buf_,(char *)&st[j].rec4,sizeof st[0]);
      goto redo_k;
    }
  }
}


static void del_stuk(int16 k)
{
  ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
  FOREVER{
    if(k==loaded) break;
    if(st[k].r_yy!=ref_yy || st[k].r_jr!=ref_jr || st[k].r_vl!=ref_vl) break;
    del_line(k);
  }
}


static void del_line(int16 line)
{
  int16 k;

  for(k=line;k<(loaded-1);k++){
    bcopy(&st[k+1].rec4,&st[k].rec4,sizeof(struct _st));
  }
  loaded--;
}


static void corr_y2000(uint16 bstu_, uint16 searcnr_)/* Y2000 probleem oplossen  */
{
  char *ry_,*rjn_,ly_;
  uint16 *prec_,*rvl_,mode_,len_stu_;
									
  scrget(1,7);scrupd(-3,0);
  prec_=us(bstu_,5);ry_=s(bstu_,8);
  rjn_=s(bstu_,9); rvl_=us(bstu_,10); len_stu_=fldlen(bstu_,0);
  fasinit(bstu_); *prec_=searcnr_; mode_=1; ly_=*ry_;
  FOREVER{
    if(faskeyi(bstu_,4,mode_)) break; mode_=2;
    if(*prec_!=searcnr_) break;
		if(*ry_>=100) break; // geen foute referenties 
    ly_=*ry_;
    if(*rjn_ || *rvl_){
      if(*ry_<50) *ry_+=100;
    } else if(*ry_==100) *ry_=0;
    if(*ry_!=ly_) { fasupd(bstu_); mode_=1;}            /* indien gewijzigd, updaten */
    *ry_=ly_;                                      /* key-volgorde behouden */
  }
}

 

static int fmt_get(int16 stu_, int16 elet_)
{
  int16 k;
  char *pdum,dummy_[10];
					
  pdum=&dummy_[0];
  k=fieldspc(stu_,elet_,&pdum,fmt);
  if(k>0) return k;
  return 0;
}
 

static int is_nul(double bd_)
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}


static void nextline(void)
{
  sfree=prtline();
}


static void initload(void)
{
  int16 g,k;

  fasunlck(0);
 
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  fileopen(1);
  fileopen(2);
	fileopen(3);
  fileopen(4);

  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

  for(k=0;k<80;k++){
    sysget(10240+k*80,2,&g);
    sysget(10242+k*80,2,&j_tb[g]);
  }
					
  getsysprNew(3,form_dat,&pr_mode,&prtnr);
					
  sysget( 294,3,def_munt);
  sysget(1790,2,&sys1790);
  sysget(1918,2,&sear_stt);
  sysget(2212,4,talen);
  sysget(3876,2,&sys3876);
}
 
			

static void fileopen(int16 nr_)
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

static int selp_ask(void)
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


static void taal_upd(int16 z, int16 fld_)
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


static int taal_chk(int16 fld_)
{
  int16 k;
									
  if(fldlen(stu,fld_)==1){
    for(k=0;k<4;k++) if(taal_i==talen[k]) {*s(stu,fld_)=k;break;}
    if(k==4 && taal_i!='\0') {errnum=34;return YES;}
  }
  return NO;
}


static void selp_upd(int16 bfnr, char men_keuze)
{
  int16 k,curs,z,curs_taal;
 
  men_keuze=men_keuze-'1'; taal_i='\0';
  bcopy(selp_bf[bfnr],s(stu,1),fldlen(stu,0));
  if(stu==1){/* leveranciers */
    curs=2;
    redo_l:;
    scrget(2,6); z=1;
    scrinq(0);
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
    scrinq(0);
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
  bcopy(s(stu,1),selp_bf[bfnr],fldlen(stu,0));
}


static int selp_tst(void)/* 00.04 */
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


static int comp_taa(char *p1, char *p2, int16 len)
{
  if(*p1==*p2) return 0;
  if(*p1<*p2) return 1;
  if(*p1>*p2) return 2;
	return 0;
}


static int used(char *b, int16 len)
{
  while(len-->0)
    if(*b++!=0xFE) return YES;
  return NO;
}
 

static int comp_num(char *p1, char *p2, int16 type)
{
  int16 ret;
  short int jj,mm,dd, oldp2;
 
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
 

static int comp_str(char *p1, char *p2, int16 len)
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
 

static int comp_byt(char *p1, char *p2, int16 len)
{
  while(len-->0){
    if(*p1<*p2) return 1;
    if(*p1>*p2) return 2;
    p1++; p2++;
  }
  return 0;
}
 

static void selp_wis(void)
{
  int16 j;

  for(j=0;j<sizeof selp_bf;j++) *(&selp_bf[0][0]+j)=0xFE;
}


static int OpenXlsFile(char *text_, short unsigned bdatum_, short unsigned edatum_)
{
	int16 pos_,dd,mm,yy;
  char string[100];
				
  zeros(string,sizeof string);
	pos_=copy0(text_,&string[0],30);
  if(bdatum_){
    string[pos_++]=' ';
    jddate(bdatum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
  if(edatum_){
    if(edatum_){bcopy(" - ",&string[pos_],3);pos_+=3;}
    jddate(edatum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
	pos_+=copy0(".XLS",&string[pos_],4);
	
  pos_=XlsCreate(string);
	return pos_;
}


static double Round(double bd_, short int q_decim_)
{
	short int k;
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


static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_)
{
  int16 pos_,slen_,len_,dd,mm,yy;
  char buf_[30],string[100];
				
  zeros(string,sizeof string);
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
    if(dt_beg_){bcopy(" - ",&string[slen_],3);slen_+=3;}
    jddate(dt_end_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[slen_],(long)dd,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)mm,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)yy,2,0);slen_+=2;
  }
  for(dd=0;dd<slen_;dd++) if(string[dd]=='\\' || string[dd]=='/') string[dd]='-';
  pos_=0;
  FOREVER{
    if(slen_<=0) break;
    zeros(buf_,sizeof buf_);
    bcopy("\xD0\xCF",buf_,2);
    if(slen_>25) len_=25; else len_=slen_;
    bcopy(&string[pos_],&buf_[2],len_);
    buf_[2+len_]=0xD0;
    prttext(buf_);
    slen_-=len_;pos_+=len_;
  }
}

