/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK2290GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK2290dat
#define ovlcod DRK2290cod
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

char ovldat[] = "drk2290  00:01 25/11/10 (c) Jamadata"; // Lijsten KeyConen-kassa (punt V.2.5)

     // FLAGWIS : bonverkopen meetellen default op UIT

#define FOREVER          while(1)
#define YES              1
#define NO               0
#define flag             uint16
#define DIM_TB           1500
#define DIM_CENT         20
#define MAXFLD           100
#define DIMBTW           8

#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_RDWR         0x0002  /* open for reading and writing */
#define O_APPEND       0x0008  /* writes done at eof */
#define O_CREAT        0x0100  /* create and open file */
#define O_TRUNC        0x0200  /* open and truncate */
#define O_EXCL         0x0400  /* open only if file doesn't already exist */
#define O_TEXT         0x4000  /* file mode is text (translated) */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

extern char *s();
extern int16 *i();
extern uint16 *u(),hash();
extern long *l();
extern long val();
extern float *f();
static float get_num();
extern double *d(),valu_cnv();
static double round();
static char *p_data,*rec_ele();
static long *pl_80_1;
static long GetRecNr();

static int16 stu=6,free;
static int16 lvcd,klcd;
static float btw_pct[DIMBTW];

static char fm_os80[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us5[]   = {7,0xC8,5,0,0,0,0};
static char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x91,5,0,0x60,0};
static char fm_ou4[]   = {6,0x91,4,0,0x60,0};
static char fm_ou3[]   = {6,0x91,3,0,0x60,0};
static char fm_uu4[]   = {6,0xD1,4,0,0x60,0};
static char fm_uu3[]   = {6,0xD1,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD1,2,0,0x60,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_uf4_0[] = {6,0xD4,4,0,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_uf3_1[] = {6,0xD4,3,1,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_uf21_[] = {6,0xD4,2,1,0x20,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_od4_2[] = {6,0xD5,4,2,0x70,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_obd[]   = {6,0x95,6,2,0x70,0};                             /* od6_2 */
static char fm_ubd[]   = {6,0xD5,6,2,0x70,0};                             /* ud6_2 */
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uANP[]   = {13,0xC8,1,0,1,0,'A','A','N','N','P', 'P',0};
static char fm_uS[]   = {11,0xC8,1,0,1,0,'S','S',' ',' ',0};
static char fm_uAVW[]  = {11,0xC8,1,0,1,0,'A','A','V','W',0};
static char fm_u_ALN[]= {13,0xC8,1,0,0x09,0,'A','A','L','L','N','N',0};
static char fm_usP_G[]= {13,0xC8,1,0,0x09,0,'%','%','P','P','G','G',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
 
static int16 dag_nr[7] = {2,3,4,5,6,0,1};
static int16 StylTotaal, StylDate, StylKlasse, StylNormal, StylTitel, Styl2Use;
static char seqo_str[500],sys3896[6],upd_veld[20],kas_munt[4],buf600[600],fmt[40];
static char periodprt[3],filnam[40],oldnm[50],prx2kas,upd_stock,add_ftvk,enkel_aantallen,def_munt[4],nm_fil[10];
static char nm_loc[10][6],btwhfd[6][7];
static long seqo_pos,value,ok_pos,btw_nr,krtok_pos,TbDiversArtikel[10],ArtOnbekend;
static int16 stu6_len,seqo_len,seqo_mode,pos,first_prx,last_prx,ft_off,inq_filiaal;
static uint16 dat_beg,dat_end,sys3772,dt_dag1,inq_kassa,prx_loff,max_kassa,art_div;
static uint16 inq_lev,inq_art,inq_groep,inq_disp,fkey,klt_div1,def_qfak,kaartnr;
static int16 prt2pdf, prt2xls;
static flag sys3894,sys3618,sys3978,sys4400,sys4408,sys1790,sys4478;
static flag chk_btoeg=NO,arcd=YES,use_kaart;
static flag sear_stt,sys3876, sgrp_used,slev_used,p_max_grp,sys2727;
static float sys3614,pct1,pct2,winstpct,tot_qlv,*pf_6_28,def_btw;
static double bd_tab[10],bd_tot[10];
static double AW,VW,winst,tot_aw,tot_vw,qlv,qlit,tot_lit;
static double EUR_munten[15] = {500,200,100,50,20,10,5,2,1,.5,.2,.1,.05,.02,.01};
static float kas_sal;

static uint16 *pu_2_1, *pu_6_1, *pu_91_2, *pu_91_3;

static uint16 dt_kvk[20],loc_klt[20],loc_nr[20],dt_last;
static char nm_kassa[20][6], firma[256];

static double btw_bas[DIMBTW+1],btw_bd[DIMBTW+1];
static int16 def_taal;
 
static struct{
  float omzet;
  float winst;
} dag_totl[31];
 
static struct {
  uint16 rec;
  float aantal;
	char stuks;
  char  code[15];
  char  omschr[40];
	char eenh[5];
  double AW;
  double VW;/* excl. btw */
  uint16 hash;
} tb[DIM_TB+1];

static struct{
  char eenh[5];
  float q_bak;
  float q_fles;
} cent[DIM_CENT];

static int16 *pi;
static int16 XlsRef, XlsRij, XlsKol;
extern int16 ilength;

#include "Std\XlsFunc.c"

ovlcod()
{

  initload();
  prt_menu();
  endsr:;
  fasclos(-2);
  ovlexit(-1);
}

static prt_menu()
{
  int16 curs=1,key,z;
  char choice;
								
  FOREVER{
    scrget(2,139);z=1;fasunlck(0);
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0481);
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
		fasunlck(-1);
    switch(choice){
      case '1': if(sys3772 & 8) prt_ft_lst();break;
      case '2': prt_grp_w();break;
      case '3': prt_art_w();break;
      case '4': toplijst(0);break;
      case '5': toplijst(1);break;
      case '6': prt_dag_tot();break;
			case '7': BestellijstWinkel(); break;
      case 'C': p_dbl_ean();break;
      case 'F': if(sys1790 & 2) dump_vrk();break;
      default : errnum=34; break;
    }
  }
  endsr:;
}
 
static p_dbl_ean()
{
  int16 z,g,k,used_,dubbel_;
  int16 form_dat[8],pr_mode,prtnr;
  char ean_bak[15],ean_stk[15];
  char *ps_6_70,*ps_6_71;
  uint16 n,nn_,max_;
 
  if(fldlen(6,70)==0 && fldlen(6,71)==0) goto endsr;
  if(scr_ok("Wenst U echt een controle uit te voeren ?")==NO) goto endsr;
 
  ps_6_70=s(6,70);ps_6_71=s(6,71);
  fasinfo(6,1);max_=*pu_6_1;prt2pdf=YES;
  zero(ean_bak,sizeof ean_bak);zero(ean_stk,sizeof ean_stk);
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
									
  prtfld(25,1,20);prttext("<t25b>Lijst dubbele EAN-nummers<bt62>");
  prtifld(fm_odat,u(25,2),-1);prttext("<t72>Blz.<ppp>");
  prtbuf(1);z=1;
  prttab(z,6,2,2,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,2,-1); prttitle(z++,"Omschrijving",3);
  prttab(z,6,70,2,-1); prttitle(z++,"EAN bak",3);
  prttab(z,6,71,2,-1); prttitle(z++,"EAN stuk",3);
  prtbuf(3);
  p_pdfname("Lijst dubbele EAN",0,0);
  

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
    if(g!=46){
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
			if(fldlen(64,1)){ // extra barcodes checken
				if(ean_bak[0]){
					fasinit(64);copy(ean_bak,s(64,2),fldlen(64,2));
					if(faskeyi(64,1,0)==0){
						fasinit(6);*u(6,1)=*u(64,3);fasgeti(6);
						copy(s(64,2),s(6,70),fldlen(6,70));
            for(k=0;k<20;k++) prtinfo(k,0);nextline();
						used_=YES;
					}
				}
				if(ean_stk[0]){
					fasinit(64);copy(ean_stk,s(64,2),fldlen(64,2));
					if(faskeyi(64,1,0)==0){
						fasinit(6);*u(6,1)=*u(64,3);fasgeti(6);
						copy(s(64,2),s(6,70),fldlen(6,70));
            for(k=0;k<20;k++) prtinfo(k,0);nextline();
						used_=YES;
					}
				}
			}
      fasinit(6); nn_=n; 
      FOREVER{
				nnext_art:;
				*pu_6_1=++nn_;
				g=fasgeti(6);
				if(g==47)break;
				if(g!=46){
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
 
static prt_dag_tot()
{
  int16 form_dat[8],pr_mode,prtnr,yy,mm,dd;
  int16 j,k,z,mode,end;
  uint16 last_dt,qklt,tot_qklt;
  double omzet,winst,tot_vw,tot_evw,tot_w,qlv,vw_ex,vw_art_;
	char str_[80];
									
  if(ask_in_dt("Afdrukken dagtotalen",2,NO)) goto endsr;
	if (prt2xls) {
		scrget(1,6);scrupd(-3,0);
		zero(str_, sizeof str_);
		if(inq_kassa){ copy("Dagtotalen kassa ",str_,17);stcli_d(&str_[strlen(str_)], (long)inq_kassa, 2, 0);}
		else if(inq_filiaal) {copy("Dagtotalen filiaal ",str_,19);copy0(nm_fil,&str_[strlen(str_)],5);}
		else copy("Dagtotalen",str_,10);
		if (dat_beg) {
			copy(" ", &str_[strlen(str_)], 1);
			jddate(dat_beg, &yy, &mm, &dd);
			yy %= 100;
			stcli_d(&str_[strlen(str_)], (long)dd, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)mm, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)yy, 2, 0);
		}

		if (dat_end) {
			if (dat_beg)
				copy(" - ",&str_[strlen(str_)], 3);

			jddate(dat_end, &yy, &mm, &dd);
			yy %= 100;
			stcli_d(&str_[strlen(str_)], (long)dd, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)mm, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)yy, 2, 0);
		}

		copy(".xls", &str_[strlen(str_)], 4);
		XlsRef = XlsCreate(str_);

		if (XlsRef <= 0)
		{
			errnum = 1;
			goto endsr;
		}
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,0,0,NO,NO);
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		XlsSelectWorkSheet(XlsRef, 1, "Dagtotalen");
		XlsRij = 1;
		XlsKol = 1;
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Datum", 0);
		for(k=0;k<6;k++){
			if(btwhfd[k][0]){
				XlsWrite(XlsRef, XlsRij, XlsKol++, 0, btwhfd[k], 0);
			}
		}
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "BTW", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Leeggoed", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Totaal", 0);
#if !FLAGDMY
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Klanten", 0);
#endif
		XlsRij++;
	}
	else {
		getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
		if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
		free=999;

		zero((char *)&bd_tab[0],sizeof bd_tab);
		zero((char *)&bd_tot[0],sizeof bd_tot);
									
		scrget(1,6);scrupd(-3,0);
		prtfld(25,1,29);
		if(inq_kassa){ prttext("<t30b>");prttext("Dagtotalen kassa ");prtifld(fm_uu2,&inq_kassa,-1); }
		else if(inq_filiaal) {prttext("<t30>Dagtotalen filiaal ");prtifld(fm_os5,nm_fil,-1);}
		else prttext("<t32b>");prttext("Dagtotalen");
		if(ft_off && add_ftvk=='J') prttext(" (TOTAAL)");
		prttext("<b><t80>");prtifld(fm_udat,&dat_beg,-1);
		prttext(" - ");prtifld(fm_udat,&dat_end,-1);
		prttext("<t122>");prttext("Blz.<ppp>.");
		prtbuf(1);
		z=1;
		prtitab(z,fm_udat,&last_dt,5,-1); prttitle(z++,"Datum",3);
	/*
		prtitab(z,fm_od8_2,&omzet,5,-1); prttitle(z++,"Dagtotaal",0x13);
	*/
		for(k=0;k<6;k++){
			if(btwhfd[k][0]){
				prtitab(z,fm_od8_2,&bd_tab[k],0,-1);prttitle(z++,btwhfd[k],0x13);
			}
		}
		prtitab(z,fm_od8_2,&bd_tab[7],0,-1);prttitle(z++,"BTW",0x13);
		prtitab(z,fm_od8_2,&bd_tab[8],0,-1);prttitle(z++,"Leeggoed",0x13);
		prtitab(z,fm_od8_2,&bd_tab[9],5,-1);prttitle(z++,"Totaal",0x13);
#if !FLAGDMY
		prtitab(z,fm_ou5,&qklt,0,-1);prttitle(z++,"Klanten",0x13);
#endif
		prtbuf(3);
	/*
		prtitab(z,fm_od8_2,&vw_ex,5,-1); prttitle(z++,"Omzet ex.BTW",0x13);
		prtitab(z,fm_od8_2,&winst,1,-1); prttitle(z++,"Br.winst",0x13);
		prtbuf(3);
	*/

		p_pdfname("Lijst dagtotalen",dat_beg,dat_end);
	}
 
  tot_vw=0;tot_w=0; tot_evw=0; last_dt=0xFFFF;end=NO;
  fasinit(91);*pu_91_3=dat_beg;mode=1;AW=0;VW=0;qlv=0;omzet=0;winst=0;vw_ex=0; qklt=0;tot_qklt=0;
  FOREVER{
    next_bew:;
    if(faskeyi(91,2,mode)) end=YES;mode=2;
    if(dat_beg && *pu_91_3< dat_beg) goto next_bew;
    if(dat_end && *pu_91_3>dat_end) end=YES;
    if(end || (*pu_91_3!=0xFFFF && *pu_91_3!=last_dt)){
      if(VW){
				for(k=0;k<6;k++){
					vw_ex=bd_tab[k] / (1.+btw_pct[k]/100.);
					vw_ex=valu_cnv("EUR","EUR",vw_ex,(double)(0.01));
					bd_tab[7]+=bd_tab[k]-vw_ex;bd_tab[k]=vw_ex;
				}
				if(prt2xls){
					XlsKol=1;
					WriteVar2Xls(XlsRij,XlsKol++,fm_odat,(char *)&last_dt,StylDate);
					for(k=0;k<6;k++){
						if(btwhfd[k][0]){
							WriteVar2Xls(XlsRij,XlsKol++,fm_od8_2,(char *)&bd_tab[k],0);
						}
					}
					for(k=7;k<10;k++) WriteVar2Xls(XlsRij,XlsKol++,fm_od8_2,(char *)&bd_tab[k],0);
					WriteVar2Xls(XlsRij,XlsKol++,fm_ou5,(char *)&qklt,0);
					XlsRij++;
				}
				else{
				  for(k=0;k<20;k++) prtinfo(k,0);nextline();
				}
				for(k=0;k<10;k++) bd_tot[k]+=bd_tab[k];
				tot_qklt+=qklt; qklt=0;
      }
      if(end) break;
			
      zero((char *)&bd_tab[0],sizeof bd_tab);
      omzet=0; VW=0;AW=0;vw_ex=0; qklt=0;
    }
    last_dt=*pu_91_3;
		if(*u(91,2)==0){// aantal klanten
			if(inq_kassa){
				qklt+= *f(91,11+(inq_kassa-1)*5);
				if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)) qklt+=*f(91,11+(inq_kassa-1+ft_off)*5);
			}
			else{
				for(k=0;k<max_kassa;k++){
					if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue; // hoort niet bij dit filiaal
					qklt+= *f(91,11+k*5);
					if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)) qklt+=*f(91,11+(k+ft_off)*5);
				}
			}
			goto next_bew;
		}
    fasinit(6);*pu_6_1=*pu_91_2;
		if(fasgeti(6)){
			fasinit(6);*pu_6_1=ArtOnbekend;fasgeti(6);
		}
	  vw_art_=0;
    if(inq_kassa){
      AW+=*f(91,12+(inq_kassa-1)*5);
      VW+=*f(91,13+(inq_kassa-1)*5);
      vw_art_+=*f(91,13+(inq_kassa-1)*5);
      vw_ex+=*f(91,13+(inq_kassa-1)*5)/(1.+*pf_6_28/100.);
      if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
				AW+=*f(91,12+(inq_kassa-1+ft_off)*5);
				VW+=*f(91,13+(inq_kassa-1+ft_off)*5);
				vw_art_+=*f(91,13+(inq_kassa-1+ft_off)*5);
				vw_ex+=*f(91,13+(inq_kassa-1+ft_off)*5)/(1.+*pf_6_28/100.);
      }
    }
    else{
      for(k=0;k<max_kassa;k++){
				if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue; // hoort niet bij dit filiaal
				if(fldlen(91,11+k*5)){
					AW+=*f(91,12+k*5);
					VW+=*f(91,13+k*5);
					vw_art_+=*f(91,13+k*5);
					vw_ex+=*f(91,13+k*5)/(1.+*pf_6_28/100.);
				}
				if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
					AW+=*f(91,12+(k+ft_off)*5);
					VW+=*f(91,13+(k+ft_off)*5);
					vw_art_+=*f(91,13+(k+ft_off)*5);
					vw_ex+=*f(91,13+(k+ft_off)*5)/(1.+*pf_6_28/100.);
				}
      }
    }
    if(*i(6,9)==99) bd_tab[8]+=vw_art_;
    else{
      for(k=0;k<6;k++) if(*pf_6_28==btw_pct[k]){bd_tab[k]+=vw_art_;break;}
    }
    bd_tab[9]+=vw_art_;
  }
  if(prt2xls==NO) nextline();
  last_dt=0;
  omzet=tot_vw;winst=tot_w; vw_ex=tot_evw;qklt=tot_qklt;
  for(k=0;k<10;k++) bd_tab[k]=bd_tot[k];
	if(prt2xls){
		XlsRij++;
		XlsKol=1;
		XlsKol++; //WriteVar2Xls(XlsRij,XlsKol++,fm_odat,(char *)&last_dt,0);
		for(k=0;k<6;k++){
			if(btwhfd[k][0]){
				WriteVar2Xls(XlsRij,XlsKol++,fm_od8_2,(char *)&bd_tab[k],0);
			}
		}
		for(k=7;k<10;k++) WriteVar2Xls(XlsRij,XlsKol++,fm_od8_2,(char *)&bd_tab[k],0);
		WriteVar2Xls(XlsRij,XlsKol++,fm_ou5,(char *)&qklt,0);
		XlsRij++;
	}
	else{
    for(j=2;j<20;j++) prtinfo(j,2);nextline();
	}
	if (prt2xls) XlsClose(XlsRef, 1);
	else{
    prtform(0);
    prtclose();
	}
  endsr:;
}
 
static copy0(char *ps_, char *pd_, int maxlen_)
{
  int k;

  for(k=0;k<maxlen_;k++){
    if(*ps_=='\0') break;
    *pd_++=*ps_++;
  }
  return k;
}

static bit(byte_,bit_)
char byte_;
int16 bit_;
{
  if(byte_ & 1<<bit_) return YES;
  return NO;
}

static ask_in_dt(ptxt,only1kas,ask_stock)
char *ptxt;
flag only1kas,ask_stock;
{
  int16 z,k,key,curs=3,xls_;
								
	xls_=NO;if(only1kas==2){xls_=YES;only1kas=0;}
#if FLAGWIS || FLAGVLO
  if(add_ftvk=='\0') add_ftvk='N';
#endif
  upd_stock='J'; if(add_ftvk=='\0') add_ftvk='J';
  if(sys3978) upd_stock='N';
  inq_kassa=0;if(max_kassa==1) inq_kassa=1;
								
  if(ask_stock && dat_beg==0 && inq_kassa==1) dat_beg=dt_kvk[0]+1;
  if(dat_beg==0 && ask_stock==NO) dat_beg=*u(25,2);
  if(dat_end==0) dat_end=dat_beg;
	inq_filiaal=0;zero(nm_fil,sizeof nm_fil);
  FOREVER{
    redo:;
    scrget(2,381);z=1; scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
		if(xls_) 	scraddpicto(2,0,72,22,4,2,573,0,0,"Schrijf uit in Excel");
    scrifld(z++,fm_os38,ptxt);
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&inq_kassa);
		if(fldlen(66,11)){scrifld(-z,fm_uu2,&inq_filiaal);z++; scrifld(z++,fm_os6,nm_fil);}
		else z+=2;
    if(ask_stock==NO && only1kas==NO && ft_off>0) scrifld(z++,fm_uJN,&add_ftvk);
    else streepje(z++);
    if(ask_stock) scrifld(z++,fm_uJN,&upd_stock);
    else z++;
    for(k=0;k<5;k++) {
      scrifld(z++,fm_os6,&nm_kassa[k][0]);
      scrifld(z++,fm_odat,&dt_kvk[k]);
      scrifld(z++,fm_os6,&nm_kassa[k+5][0]);
      scrifld(z++,fm_odat,&dt_kvk[k+5]);
    }
    key=scrupd(curs,0x481);curs=3;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(inq_filiaal<0 || (inq_filiaal>10 && inq_filiaal!=99)) {zero(nm_fil,sizeof nm_fil);curs=5; errnum=34;goto redo;}
		if(inq_filiaal && inq_filiaal<=10){
			if(fldlen(66,11+(inq_filiaal-1)*15)==0) {errnum=34;curs=5; goto redo;}
			copy(nm_loc[inq_filiaal-1],nm_fil,6);
		}
		else if(inq_filiaal==99) copy("DEPOT",nm_fil,6);
		else zero(nm_fil,sizeof nm_fil);
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    if(key==111) ovlexit(-1);
    if(key==101) return YES;
    if(dat_beg==0 && ask_stock){curs=3;errnum=38;goto redo;}
    if(dat_end==0 || dat_end<dat_beg){curs=4;errnum=38;goto redo;}
    if(only1kas && inq_kassa==0){curs=5;errnum=38;goto redo;}
    if(inq_kassa && (fldlen(91,11+(inq_kassa-1)*5)==0 || nm_kassa[inq_kassa-1][0]=='\0')){
      curs=5;errnum=34;goto redo;
    }
    if(ask_stock){if(chk_dates()) {curs=3;goto redo;}}
		prt2xls=NO;if(key==5002){prt2xls=YES;key=108;}
    if(key==108) break;
  }
  if(dat_end==0) dat_end=0xFFFF;
  return NO;
}

static chk_dates()
{
  int16 k,max_;
  uint16 dt_,dt_beg_,dt_end_;

  scrget(1,7);scrupd(-3,0);
  dt_beg_=dat_beg;dt_end_=dat_end;
  k=1; max_=10; if(inq_kassa){k=inq_kassa; max_=inq_kassa;}
								
  for(k;k<=max_;k++){
    if(nm_kassa[k-1][0]=='\0') continue;
    dt_beg_=dat_beg;dt_end_=dat_end;
    if(dt_kvk[k-1]+1 > dt_beg_){
      if(inq_kassa) {errnum=34;return YES;}
      else  dt_beg_=dt_kvk[k-1]+1;
    }
    if(dt_beg_>dt_end_) continue;

    for(dt_=dt_beg_;dt_<=dt_end_;dt_++){
      fasinit(91);*pu_91_3=dt_;
      if(faskeyi(91,1,0)==0){
	if(*f(91,11+(k-1)*5)) break;
      }
    }
    if(dt_<=dt_end_){
      if(scr_ok("U heeft reeds verkopen ingelezen in deze periode ... overschrijven ???")==NO) return YES;
      else return NO;
    }
  }
  return NO;
}

static double Round(double bd_, double bd_afr_)
{
	double wrk1_, wrk2_, wrk3_, add_, result_;

	result_ = bd_;
	add_ = 0.500001;

	if (result_ < 0)
		add_ = -add_;

	if (bd_afr_ > 0.00001) {
		if (bd_afr_ <= 1.) {
			wrk1_ = (long int)result_;
			wrk2_ = result_ - wrk1_;
		}
		else {
			wrk1_ = 0.;
			wrk2_ = result_;
		}

		wrk3_ = wrk2_ / bd_afr_;
		wrk2_ = (double)((long)((wrk2_ / bd_afr_) + add_)) * bd_afr_;
		result_ = wrk1_ + wrk2_;
	}

endsr:;
	return (double)(result_);
}

static void exp_line(uint16 isTotaal)
{
	char code_[6];
	double qlv_, qlit_, AW_, VW_, winst_, winstpct_;

	XlsKol = 1;

	if (!isTotaal) {
		zero(code_, sizeof code_);
		copy(s(6, 2), code_, 5);
		code_[strlen(code_)] = '\0';
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, code_, 0);   // Code
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, s(6, 3), 0); // Omschrijving
	}
	else
		XlsKol = 3;

	qlv_ = Round(qlv, (double)0.01);
	qlit_ = Round(qlit, (double)0.01);
	AW_ = Round(AW, (double)0.01);
	VW_ = Round(VW, (double)0.01);
	winst_ = Round(winst, (double)0.01);
	winstpct_ = Round(winstpct, (double)0.1);

	XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &qlv_, 0);  // Aantal

	if (qlit_)
		XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &qlit_, 0); // Aantal (Liter)
	else
		XlsKol++;

	if (enkel_aantallen != 'J') {
		if (!(sys4478 & 0x01))
			XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &AW_, 0); // Aankoop Waarde

		XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &VW_, 0); // Verkoop Waarde

		if (!(sys4478 & 0x01)) {
			XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &winst_, 0);    // Winst
			XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &winstpct_, 0); // Winst %
		}
	}

	XlsRij++;
}

static prt_art_w()
{
  int16 form_dat[8],pr_mode,prtnr;
  int16 curs=1,k,key,z,mode,moded_;
  int16 dd, mm, yy;
	uint16 rec6_;
	float coef_,q_bak_;
  char sortmeth='A',only_used='J',GEEN_deelverpakkingen_='N';
  char str_[50];

  if(add_ftvk=='\0') add_ftvk='J';
  inq_kassa=0;if(max_kassa==1) inq_kassa=1;
	inq_filiaal=0;zero(nm_fil,sizeof nm_fil);
  FOREVER{
    redo:;
    scrget(2,140);z=1;scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF");
	scraddpicto(2,0,72,22,4,2,573,0,0,"Schrijf uit in Excel");
    scrfld(z++,25,1);
    scrifld(z++,fm_uANP,&sortmeth);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&inq_kassa);
		if(fldlen(66,11)){scrifld(-z,fm_uu2,&inq_filiaal);z++; scrifld(z++,fm_os6,nm_fil);}
		else z+=2;
    if(ft_off>0) scrifld(z++,fm_uJN,&add_ftvk); else streepje(z++);
	  scrifld(z++, fm_uJN, &enkel_aantallen);
		if(fldlen(6,102)) scrifld(z++, fm_uJN, &GEEN_deelverpakkingen_); else streepje(z++);
    key=scrupd(curs,0x481);curs=3;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(inq_filiaal<0 || (inq_filiaal>10 && inq_filiaal!=99)) {zero(nm_fil,sizeof nm_fil);curs=5; errnum=34;goto redo;}
		if(inq_filiaal && inq_filiaal<=10){
			if(fldlen(66,11+(inq_filiaal-1)*15)==0) {errnum=34;curs=5; goto redo;}
			copy(nm_loc[inq_filiaal-1],nm_fil,6);
		}
		else if(inq_filiaal==99) copy("DEPOT",nm_fil,6);
		else zero(nm_fil,sizeof nm_fil);
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    prt2xls=NO;if(key==5002){prt2xls=YES;key=108;}
    if(key==111) ovlexit(-1);
    if(key==101) return YES;
    if(dat_end==0 || dat_end<dat_beg){curs=4;errnum=38;goto redo;}
    if(inq_kassa && fldlen(91,11+(inq_kassa-1)*5)==0){
      curs=6;errnum=34;goto redo;
    }
    if(key==108) break;
  }
  seldata.selp_use=NO;
  if(ovlcall(2215,4)) goto endsr;

  key=1; 
	if(sortmeth=='A') key=2;
	else if(sortmeth=='P') key=6;

  scrget(1,6);scrupd(-3,0);

	if (prt2xls) {
		zero(str_, sizeof str_);
		copy("Artikelverkopen", str_, 15);

		if (dat_beg) {
			copy(" ", &str_[strlen(str_)], 1);
			jddate(dat_beg, &yy, &mm, &dd);
			yy %= 100;
			stcli_d(&str_[strlen(str_)], (long)dd, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)mm, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)yy, 2, 0);
		}

		if (dat_end) {
			if (dat_beg)
				copy(" - ",&str_[strlen(str_)], 3);

			jddate(dat_end, &yy, &mm, &dd);
			yy %= 100;
			stcli_d(&str_[strlen(str_)], (long)dd, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)mm, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)yy, 2, 0);
		}

		copy(".xls", &str_[strlen(str_)], 4);
		XlsRef = XlsCreate(str_);

		if (XlsRef <= 0)
		{
			errnum = 1;
			goto endsr;
		}
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,0,0,NO,NO);
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		XlsSelectWorkSheet(XlsRef, 1, "Artikelverkopen");
		XlsRij = 1;
		XlsKol = 1;
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Code", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Omschrijving", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Aantal", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Aantal (Liter)", 0);
	}
	else {
		getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
		k=132; if(sys4478 & 1) k=80;
		if((errnum=prtopen(prtnr,form_dat,6,k,pr_mode,4))!=0) goto endsr;
		free=999;
		prtfld(25,1,25);
		if(inq_kassa){prttext("<t27b>Artikelverkopen, kassa ");prtifld(fm_uu2,&inq_kassa,-1);}
		else if(inq_filiaal) {prttext("<t27b>Artikelverkopen, filiaal ");prtifld(fm_os5,nm_fil,-1);}
		else prttext("<t27b>Artikelverkopen");
		if(sys4478 & 1){
			prttext("<b><t53>");prtifld(fm_udat,&dat_beg,-1);
			prttext(" - ");prtifld(fm_udat,&dat_end,-1);
			prttext("<t73>");prttext("Blz.<ppp>");
		}
		else{
			prttext("<b><t85>");prttext("Periode ");prtifld(fm_udat,&dat_beg,-1);
			prttext(" - ");prtifld(fm_udat,&dat_end,-1);
			prttext("<t120>");prttext("Blz.<ppp>.");
		}
		prtbuf(1);
		z=1;
		prttab(z,6,2,2,-1); prttitle(z++,"Code",3);
		prttab(z,6,3,1,-1); prttitle(z++,"Omschrijving",3);
		prtitab(z,fm_ud7_2,&qlv,1,-1); prttitle(z++,"Aantal",0x13);
		prtitab(z,fm_ud7_2,&qlit,1,-1); prttitle(z++,"Aantal L",0x13);
	}

	if (enkel_aantallen != 'J') {
		if (!(sys4478 & 0x01)) {
			if (prt2xls)
				XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Aankoop Waarde", 0);
			else {
				prtitab(z, fm_ud7_2, &AW, 1, -1);
				prttitle(z++, "A.waarde", 0x13);
			}
		}

		if (prt2xls)
			XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Verkoop Waarde", 0);
		else {
			prtitab(z, fm_ud7_2, &VW, 2, -1);
			prttitle(z++,"V.waarde",0x13);
		}

		if (!(sys4478 & 0x01)) {
			if (prt2xls) {
				XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Winst", 0);
				XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Winst %", 0);
			}
			else {
				prtitab(z, fm_ud7_2, &winst, 3, -1);
				prttitle(z++, "Winst", 0x13);
				prtitab(z, fm_uf3_1, &winstpct, 2, -1);
				prttitle(z++, "Winst%", 0x13);
			}
		}
	}

	if (prt2xls)
		XlsRij++;
	else {
		prtbuf(3);
		p_pdfname("Artikelverkopen",dat_beg,dat_end);
	}
 
  zero((char *)&btw_bas[0],sizeof btw_bas);
  tot_qlv=0;tot_aw=0;tot_vw=0;tot_lit=0;
  fasinit(6);
  FOREVER{
    next_art:;
    if(faskeyi(6,key,2)) break;
    if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
		if(GEEN_deelverpakkingen_=='J' && fldlen(6,102) && *u(6,102)) goto next_art;
		rec6_=*u(6,1); q_bak_=*f(6,31); coef_=1.;AW=0;VW=0;qlv=0;qlit=0;
		redo_artik:;
    fasinit(91);*pu_91_2=*pu_6_1;*pu_91_3=dat_beg;mode=1;
    FOREVER{
      next_bew:;
      if(faskeyi(91,1,mode)) break;mode=2;
      if(*pu_6_1!=*pu_91_2) break;
      if(dat_beg && *pu_91_3< dat_beg) goto next_bew;
      if(dat_end && *pu_91_3>dat_end) break;
      if(inq_kassa){
				qlv+=*f(91,11+(inq_kassa-1)*5)*coef_;
				qlit += *f(91, 11 + (inq_kassa - 1) * 5) * *f(6, 37);
				AW+=*f(91,12+(inq_kassa-1)*5);
				VW+=*f(91,13+(inq_kassa-1)*5)/(1.+*pf_6_28/100.);
				if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
					qlv+=*f(91,11+(inq_kassa-1+ft_off)*5)*coef_;
					qlit += *f(91, 11 + (inq_kassa - 1 + ft_off) * 5) * *f(6, 37);
					AW+=*f(91,12+(inq_kassa-1+ft_off)*5);
					VW+=*f(91,13+(inq_kassa-1+ft_off)*5)/(1.+*pf_6_28/100.);
				}
      }
      else{
				for(k=0;k<max_kassa;k++){
						if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue; // hoort niet bij dit filiaal
					if(fldlen(91,11+k*5)){
						qlv+=*f(91,11+k*5)*coef_;
						qlit += *f(91, 11 + k * 5) * *f(6, 37);
						AW+=*f(91,12+k*5);
						VW+=*f(91,13+k*5)/(1.+*pf_6_28/100.);
					}
					if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
						qlv+=*f(91,11+(k+ft_off)*5)*coef_;
						qlit += *f(91, 11 + (k + ft_off) * 5) * *f(6, 37);
						AW+=*f(91,12+(k+ft_off)*5);
						VW+=*f(91,13+(k+ft_off)*5)/(1.+*pf_6_28/100.);
					}
				}
      }
    }
		if(GEEN_deelverpakkingen_=='J' && fldlen(6,102)){  // deelverpakkingen bij hoofdartikel tellen
			if(*u(6,102)==0){
				fasinit(6); *u(6,102)=rec6_;moded_=1;
			}
			FOREVER{
				if(faskeyi(6,15,moded_)) break; moded_=2;
				if(*u(6,102)!=rec6_) break;
				coef_=1.; if(*f(6,31) && q_bak_) coef_=*f(6,31)/q_bak_;
				goto redo_artik;
			}
		}

		fasinit(6);*u(6,1)=rec6_;fasgeti(6);
    if(only_used!='J' || qlv || qlit || VW){
      if(*i(6,9)==99) k=DIMBTW;
      else {
	for(k=0;k<DIMBTW;k++) if(btw_pct[k]==*pf_6_28) break;
      }
      btw_bas[k]+=VW;
      winst=VW-AW;if(AW) winstpct=winst/AW*100;  else winstpct=0;

		if (prt2xls)
			exp_line(NO);
		else {
			for (k = 0; k < 20; k++)
				prtinfo(k, 0);

			nextline();
		}

      tot_qlv+=qlv;tot_lit+=qlit;tot_aw+=AW;tot_vw+=VW;
    }
  }
  fasinit(6); copy("T O T A A L   ===>",s(6,3),19);
  qlv=tot_qlv;
  qlit=tot_lit;
  AW=tot_aw;
  VW=tot_vw;
  winst=VW-AW;if(AW) winstpct=winst/AW*100; else winstpct=0;

	if (prt2xls)
		exp_line(YES);
	else {
		nextline();
		
		for (k = 0; k < 20; k++)
			prtinfo(k, 2);
		
		nextline();
	}

	if (enkel_aantallen != 'J') {
		prt_btwtab();
	}

	if (prt2xls)
		XlsClose(XlsRef, 1);
	else
		prtclose();

  endsr:;
}

static BestellijstWinkel()
{
  int16 curs=1,k,key,fkey,z,mode,j,start_=0,q_per_lijn_,d_lin_scr_=19,curspos_,artikelgezocht_,z_base_,pmaxtb_;
  flag sr_nm;
  char *pdum,dumm_[10];
	long qbak_,qstks_;
  char sortmeth='P',only_used='J',nm_winkel[40];

	pdum=&dumm_[0];
  if(add_ftvk=='\0') add_ftvk='J';
	if(dat_beg==0) dat_beg=*u(25,2);if(dat_end==0) dat_end=*u(25,2);
  inq_kassa=0;if(max_kassa==1) inq_kassa=1;
	inq_filiaal=0;zero(nm_fil,sizeof nm_fil);
  FOREVER{
    redo376:;
    scrget(2,376);z=1;// scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_uANP,&sortmeth);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&inq_kassa);
		if(fldlen(66,11)){scrifld(-z,fm_uu2,&inq_filiaal);z++; scrifld(z++,fm_os6,nm_fil);}
		else z+=2;
    if(ft_off>0) scrifld(z++,fm_uJN,&add_ftvk); else streepje(z++);
    key=scrupd(curs,0x481);curs=3;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(inq_filiaal<0 || (inq_filiaal>10 && inq_filiaal!=99)) {zero(nm_fil,sizeof nm_fil);curs=5; errnum=34;goto redo376;}
		if(inq_filiaal && inq_filiaal<=10){
			if(fldlen(66,11+(inq_filiaal-1)*15)==0) {errnum=34;curs=5; goto redo376;}
			copy(nm_loc[inq_filiaal-1],nm_fil,6);
		}
		else if(inq_filiaal==99) copy("DEPOT",nm_fil,6);
		else zero(nm_fil,sizeof nm_fil);
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    if(key==111) ovlexit(-1);
    if(key==101) return YES;
    if(dat_end==0 || dat_end<dat_beg){curs=4;errnum=38;goto redo376;}
    if(inq_kassa && fldlen(91,11+(inq_kassa-1)*5)==0){
      curs=6;errnum=34;goto redo376;
    }
    if(key==108) break;
  }
  seldata.selp_use=NO;
  if(ovlcall(2215,4)) goto endsr;

  fasinit(6);fkey=1; 
	if(sortmeth=='A') fkey=2;
	else if(sortmeth=='P') fkey=6;
	for(k=0;k<DIM_TB;k++) zero((char *)&tb[k].rec,sizeof tb[0]); pmaxtb_=0;
  FOREVER{
    next_art:;
    if(faskeyi(6,fkey,2)) break;
    if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
    fasinit(91);*u(91,2)=*u(6,1);*u(91,3)=dat_beg;mode=1;AW=0;VW=0;qlv=0;
    FOREVER{
      next_bew:;
      if(faskeyi(91,1,mode)) break;mode=2;
      if(*u(6,1)!=*u(91,2)) break;
      if(dat_beg && *pu_91_3< dat_beg) goto next_bew;
      if(dat_end && *pu_91_3>dat_end) break;
      if(inq_kassa){
				qlv+=*f(91,11+(inq_kassa-1)*5);
				if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
					qlv+=*f(91,11+(inq_kassa-1+ft_off)*5);
				}
      }
      else{
				for(k=0;k<max_kassa;k++){
					if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue; // hoort niet bij dit filiaal
					if(fldlen(91,11+k*5)){
						qlv+=*f(91,11+k*5);
					}
					if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
						qlv+=*f(91,11+(k+ft_off)*5);
					}
				}
      }
    }
    if(qlv){
			if(*f(6,31)<1) *f(6,31)=1;					
			qbak_=(long)(qlv); qstks_=0;
			if(*f(6,31)>1 && qlv>0){
				qstks_=(long)(((qlv-qbak_) * *f(6,31))+0.49);
			} else qstks_=0;
			if(qbak_){
  			tb[pmaxtb_].rec=*u(6,1);
	  		copy(s(6,2),tb[pmaxtb_].code,fldlen(6,2));
		  	copy(s(6,3),tb[pmaxtb_].omschr,fldlen(6,3));
			  copy(s(6,10),tb[pmaxtb_].eenh,fldlen(6,10));
			  tb[pmaxtb_].hash=hash(pmaxtb_);
			  tb[pmaxtb_].aantal=qbak_;pmaxtb_++;
			}
			if(qstks_) {
  			tb[pmaxtb_].rec=*u(6,1);
	  		copy(s(6,2),tb[pmaxtb_].code,fldlen(6,2));
		  	copy(s(6,3),tb[pmaxtb_].omschr,fldlen(6,3));
			  copy(s(6,10),tb[pmaxtb_].eenh,fldlen(6,10));
			  tb[pmaxtb_].hash=hash(pmaxtb_);				
				tb[pmaxtb_].aantal=qstks_;tb[pmaxtb_].stuks='S'; pmaxtb_++;
			}
			if(pmaxtb_>=DIM_TB-1) break;
    }
  }
	zero(nm_winkel,sizeof nm_winkel);
  if(max_kassa<=1) copy("Winkel",nm_winkel,6);
	else if(inq_kassa){	j=sprintf_s(nm_winkel,5,"%d ",inq_kassa);copy(nm_kassa[inq_kassa-1],&nm_winkel[j],6);}
	else if(inq_filiaal) {j=sprintf_s(nm_winkel,30,"%d ",inq_filiaal);copy(nm_fil,&nm_winkel[j],6);}
	else copy("Winkels",nm_winkel,7);
	q_per_lijn_=5;
  curs=5;
  FOREVER{
    redo377:
    scrget(2,377);z=1;
    scrifld(z++,fm_os30,nm_winkel);
    scrifld(z++,fm_odat,&dat_beg);scrifld(z++,fm_odat,&dat_end);
		z_base_=z;
    for(j=start_;j<(start_+d_lin_scr_);j++){
			j++;scrifld(z++,fm_ou4,&j);j--;
      scrifld(z++,fm_uf4_0,&tb[j].aantal);
			scrifld(z++,fm_uS,&tb[j].stuks);
      fieldspc(6,2,&pdum,fmt); scrifld(z++,fmt,tb[j].code);
      fieldspc(6,3,&pdum,fmt); scrifld(z++,fmt,tb[j].omschr);
	  }
    key=scrupd(curs,0x03FF);curs=5;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101){
			for(k=0;k<DIM_TB;k++) if(tb[k].rec) break;
			if(k<DIM_TB){
				if(DisplayWarning("Wenst u echt te stoppen?", 61,1)==YES) return YES;
			}
			else return YES;
		}
    if(key==105 && curspos_>=z_base_){
      j=(curspos_-3)/q_per_lijn_;j+=start_;
      for(k=DIM_TB-2;k>=j;k--){
				copy((char *)&tb[k].rec,(char *)&tb[k+1].rec,sizeof tb[0]);
      }
      zero((char *)&tb[j].rec,sizeof tb[0]);
			curs=curspos_; goto redo377;
    }
    if(key==104 && curspos_>=z_base_){
      j=(curspos_-3)/q_per_lijn_;j+=start_;
      for(k=j;k<DIM_TB-1;k++){
				copy((char *)&tb[k+1].rec,(char *)&tb[k].rec,sizeof tb[0]);
      }
      zero((char *)&tb[DIM_TB-1].rec,sizeof tb[0]);
			curs=curspos_; goto redo377;
    }
		artikelgezocht_=NO;
    for(k=start_;k<(start_+d_lin_scr_);k++){
      if((tb[k].code[0] || tb[k].omschr[0]) && tb[k].hash!=hash(k)){
				fasinit(6);
				sr_nm=NO;
				if(fldlen(6,2) && tb[k].code[0]) {*s(6,3)='.';copy(tb[k].code,s(6,3)+1,fldlen(6,2));}
				else {copy(tb[k].omschr,s(6,3),fldlen(6,3));sr_nm=YES;}
				if(search(6,0)){curs=8+(k-start_)*q_per_lijn_;goto redo377;}
				copy(s(6,2),tb[k].code,fldlen(6,2));
				copy(s(6,3),tb[k].omschr,fldlen(6,3));
				copy(s(6,10),tb[k].eenh,fldlen(6,10));
				tb[k].rec=*u(6,1);
				artikelgezocht_=YES;
      }
      else if(tb[k].aantal && tb[k].omschr[0]=='\0'){
				errnum=38;curs=5+(k-start_)*q_per_lijn_;
				goto redo377;
      }
    }


		if((key==108 || key==109) && artikelgezocht_==NO){
			if(plaadbon(key-108)) {
				if(DisplayWarning("Wenst u verder aan te passen?", 605,1)==0) break;
			}
		}
    if(key==102) {start_-=d_lin_scr_; if(start_<0) start_=0;}
    if(key==103) start_+=d_lin_scr_;
    if(start_>(DIM_TB-d_lin_scr_)) start_=DIM_TB-d_lin_scr_;
    j=0;
    for(k=0;k<d_lin_scr_;k++){if(tb[k+start_].aantal==0) {j=k;break;}}
    if(k<d_lin_scr_) curs=5+k*q_per_lijn_; else curs=z_base_;
  }
  endsr:;
}

static plaadbon(int16 doc_mode_) // 1=bestelling, 0=laadbon
{
  int16 form_dat[8],pr_mode,prtnr;
	int16 j,k,z;
  char stuks_;
  float tot_qlv_=0,aantal_;

  getsysprNew(14,form_dat,&pr_mode,&prtnr);
	if(YES /* prt2pdf==1 */) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if (prtopen(prtnr,form_dat,6,80,pr_mode,5)!=0) return NO;
  free=999;

  scrget(1,6);
  prtfld(25,1,20);if(doc_mode_==1) prttext("<t25b>Bestellijst winkel"); else prttext("<t25b>LAADBON winkel");
  prttext("<b>   Datum : ");prtfld(25,2,-1);prttext("<t72>Blz.<pp>.");
  prtbuf(1);
	prttext("<t42>Verkopen periode ");prtifld(fm_udat,&dat_beg,-1); prttext(" - "); prtifld(fm_udat,&dat_end,-1);
  prtbuf(2);
	fasinit(2);
  if(max_kassa<=1) *u(2,1)=loc_klt[0];
	else if(inq_kassa) *u(2,1)=loc_klt[inq_kassa-1];
	else copy("Alle kassa's",s(2,3),15);
	if(*u(2,1)) fasgeti(2);
	prttext("<eb>");prtfld(2,3,35);prttext("<eb>");prtbuf(3);
	z=1;
  prttab(z,6,2,2,-1); prttitle(z++,"Code",3);
  prttab(z,6,29,2,-1); prttitle(z++,"Pl.Mg",3);
  prttab(z,6,10,2,-1); prttitle(z++,"Eh",3);
  prtitab(z,fm_uf4_0,&aantal_,1,-1); prttitle(z++,"Aantal",0x13);
  prtitab(z,fm_uS,&stuks_,1,-1); prttitle(z++,"",3);
  prttab(z,6,3,2,-1); prttitle(z++,"Omschrijving",3);
  prtbuf(5);

	zeros((char *)&cent[0].eenh[0],sizeof cent);
  for(k=0;k<DIM_TB;k++){
		if(tb[k].rec==0) continue;
		fasinit(6);*u(6,1)=tb[k].rec; fasgeti(6);
    for(j=0;j<DIM_CENT;j++){
	    if(cent[j].q_bak==0 && cent[j].q_fles==0) break;
	    if(cmp_str(s(6,10),cent[j].eenh,fldlen(6,10))==0) break;
    }
    if(j<DIM_CENT){
	    copy(s(6,10),cent[j].eenh,fldlen(6,10));
	    if(tb[k].stuks=='S') cent[j].q_fles+=tb[k].aantal; else cent[j].q_bak+=tb[k].aantal;
    }
		aantal_=tb[k].aantal;stuks_=tb[k].stuks;tot_qlv_+=aantal_;
		if(free<5) prtform(0);
    for(j=1;j<10;j++) prtinfo(j,0);nextline();
  }
  nextline();
  fasinit(6);
  copy("<== TOTAAL aantal",s(6,3),20);aantal_=tot_qlv_;stuks_='\0';
  nextline();
	if(doc_mode_==0){
		for(k=0;k<20;k++) prtinfo(k,2);nextline();nextline();
		for(k=0;k<DIM_CENT;k++) if(cent[k].q_bak==0 && cent[k].q_fles==0) break;
		if(free<k+3) prtform(0);
		prttext("<t10><e>Centralisatie");nextline();nextline();
		for(k=0;k<DIM_CENT;k++){
			if(cent[k].q_bak || cent[k].q_fles){
				prttext("<t5>");copy(cent[k].eenh,s(6,10),fldlen(6,10));prtfld(6,10,-1);
				prttext("   ");prtifld(fm_uf4_0,&cent[k].q_bak,-1);
				prttext("   ");prtifld(fm_uf4_0,&cent[k].q_fles,-1);
				nextline();
			}
		}
  
		while(free>5) nextline();
		prttext("Klaargezet door : ............... Datum .../.../...    Chauffeur : ...............");nextline();
	}
  prtform(0);
	prtclose();
endsr:;
	return YES;
}



static uint16 hash(int16 nr_)
{
  char *ps;
  int16 len_;
  uint16 fuval=0;
					
  len_=sizeof tb[nr_].code + sizeof tb[nr_].omschr;ps=tb[nr_].code;
  while(len_--){
    fuval=fuval*3+*(ps++);
  }
  return fuval;
}


static stock2stks(stock_,qst_,bak_,fls_)
float stock_,qst_,*bak_;
char *fls_;
{
  long stk_;
	float add_;
						
  zero(fls_,5);
  if(qst_<1) qst_=1;
  *bak_=(long)(stock_); stk_=0;
	add_=0.49; if(stock_<0) add_=-0.49;
  if(qst_>1 && stock_!=0){
    stk_=(long)(((stock_- *bak_) * qst_)+add_);
  } else stk_=0;
  if(stk_>999) stk_/=100;
  if(stk_) *fls_='/'; stcli_d(fls_+1,stk_,2,1);
}

static prt_btwtab()
{
  int16 j,k;
  double bedrag_,btw_tot_,belastbt_;

  zero((char *)&btw_bd[0],sizeof btw_bd);

	if (prt2xls) {
		XlsKol = 1;
		XlsRij++;
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "BTW tabel", 0);
		XlsRij += 2;
	}
	else {
		nextline();
		prttext("<u>BTW tabel<u>");
		nextline();
		nextline();
	}

  btw_tot_=0; belastbt_=0;
  for(k=0;k<DIMBTW;k++){
    btw_bas[k]=valu_cnv("EUR","EUR",(double)btw_bas[k],(double)0.01);
    if(btw_bas[k]){
      belastbt_+=btw_bas[k];
      bedrag_=valu_cnv("EUR","EUR",(double)(btw_bas[k]*btw_pct[k]/100.),(double)0.01);
      btw_tot_+=bedrag_;btw_bd[k]+=bedrag_;
    }
  }

  for (j = 0; j < 4; j++) {
	  if (prt2xls) {
		  XlsKol = 1;

		  switch(j) {
			  case 0:
				  XlsKol++;
				  break;
			  case 1:
				  XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Basis", 0);
				  break;
			  case 2:
				  XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "BTW", 0);
				  break;
			  default:
				  XlsRij++;
				  XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Totaal", 0);
				  break;
		  }

		  for (k = 0; k < DIMBTW; k++) {
			  if (btw_bas[k]) {
				  if (j == 0) {
					  double dbl = (double)btw_pct[k];
					  XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &dbl, 0);
				  }
				  else {
					  if (j == 1)
						  bedrag_ = btw_bas[k];

					  if (j == 2)
						  bedrag_ = btw_bd[k];

					  if (j == 3)
						  bedrag_ = btw_bas[k] + btw_bd[k];

					  bedrag_ = Round(bedrag_, (double)0.01);
					  XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &bedrag_, 0);
				  }
			  }
		  }

		  XlsKol++;

		  if (j == 0) {
			  XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Leeggoed", 0);
			  bedrag_ = btw_bas[DIMBTW];
		  }
		  else if (j == 1) {
			  XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Goederen", 0);
			  bedrag_ = belastbt_;
		  }
		  else if (j == 2) {
			  XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "BTW", 0);
			  bedrag_ = btw_tot_;
		  }
		  else {
			  XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "TOTAAL", 0);
			  bedrag_ = btw_tot_ + belastbt_ + btw_bas[DIMBTW];
		  }

		  bedrag_ = Round(bedrag_, (double)0.01);
		  XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &bedrag_, 0);
		  XlsRij++;
	  }
	  else {
		  switch(j) {
			  case 0:
				  prttext("       ");
				  break;
			  case 1:
				  prttext("Basis  ");
				  break;
			  case 2:
				  prttext("Btw    ");
				  break;
			  default:
				  nextline();
				  prttext("<b>Totaal ");
				  break;
		  }

		  for (k = 0; k < DIMBTW; k++) {
			  if (btw_bas[k]) {
				  if (j == 0) {
					  prttext("    <u>");
					  prtifld(fm_uf21_, &btw_pct[k], -1);
					  prttext(" %<u> ");
				  }
				  else {
					  if (j == 1)
						  bedrag_ = btw_bas[k];

					  if (j == 2)
						  bedrag_ = btw_bd[k];

					  if (j == 3)
						  bedrag_ = btw_bas[k] + btw_bd[k];

					  prtifld(fm_obd, &bedrag_, -1);
					  prtblank(1);
				  }
			  }
		  }

		  if (j == 0) {
			  prttext("<t55>Leeggoed:");
			  bedrag_ = btw_bas[DIMBTW];
		  }
		  else if (j == 1) {
			  prttext("<t55>Goederen:");
			  bedrag_ = belastbt_;
		  }
		  else if (j == 2) {
			  prttext("<t57>B.T.W.:");
			  bedrag_ = btw_tot_;
		  }
		  else {
			  prttext("<t57>TOTAAL:");
			  bedrag_ = btw_tot_ + belastbt_ + btw_bas[DIMBTW];
		  }

		  prttext("<t69>");
		  prtifld(fm_obd, &bedrag_, -1);
		  nextline();
	  }
  }
}

static prt_grp_w()
{
  int16 form_dat[8],pr_mode,prtnr;
  int16 j,k,z,groep_;
  long a,used;

  if(ask_in_dt("Afdrukken groepsverkopen",NO,NO)) goto endsr;


  if(ovlcall(2215,4)) goto endsr;
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  free=999;
									
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,25);
  if(inq_kassa){ prttext("<t28b>Groepsverkopen kassa ");prtifld(fm_uu2,&inq_kassa,-1); }
	else if(inq_filiaal) {prttext("<t28>Groepsverkopen filiaal ");prtifld(fm_os5,&nm_fil,-1);}
  else prttext("<t30b>Verkopen per groep");
  prttext("<b><t54>");prtifld(fm_udat,&dat_beg,-1);
  prttext(" - ");prtifld(fm_udat,&dat_end,-1);
  prttext("<t74>");prttext("Blz.<ppp>");
  prtbuf(1);
  z=1;
  prttab(z,52,1,2,-1); prttitle(z++,"",3);
  prttab(z,52,14,0,-1); prttitle(z++,"Groep",3);
  if(!(sys4478 & 0x01)){
    prtitab(z,fm_ud7_2,&AW,0,-1); prttitle(z++,"A.waarde",0x13);
  }
  prtitab(z,fm_ud7_2,&VW,1,-1); prttitle(z++,"V.waarde",0x13);
  prtitab(z,fm_uf3_1,&pct1,0,-1); prttitle(z++,"Tot%",0x13);
  if(!(sys4478 & 0x01)){
    prtitab(z,fm_ud7_2,&winst,3,-1); prttitle(z++,"Winst",0x13);
    prtitab(z,fm_uf3_1,&winstpct,2,-1); prttitle(z++,"Winst%",0x13);
    prtitab(z,fm_uf3_1,&pct2,0,-1); prttitle(z++,"Tot%",0x13);
  }
  prtbuf(3);
  p_pdfname("Groepsverkopen",dat_beg,dat_end);
 
  zero((char *)&btw_bas[0],sizeof btw_bas);
	for(k=0;k<DIM_TB;k++) zero((char *)&tb[k].rec,sizeof tb[0]);
  fasinfo(91,1);
  used=GetRecNr(91);
  for(a=1;a<=used;a++){
    fasinit(91); SetRecNr(91,a);
    if(fasgetu(91)) goto next;
    if(dat_beg && *pu_91_3<dat_beg) goto next;
    if(dat_end && *pu_91_3>dat_end) goto next;
    fasinit(6);*pu_6_1=*pu_91_2;
		if(fasgeti(6)){
			fasinit(6);*pu_6_1=ArtOnbekend;fasgeti(6);
		}
    if(DirCall_DRK2215_SelectArtikel()==NO) goto next;
    groep_=*i(6,9);VW=0;AW=0;
    if(inq_kassa){
      AW+=*f(91,12+(inq_kassa-1)*5);
      VW+=*f(91,13+(inq_kassa-1)*5)/(1.+*pf_6_28/100.);
      if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
				AW+=*f(91,12+(inq_kassa-1+ft_off)*5);
				VW+=*f(91,13+(inq_kassa-1+ft_off)*5)/(1.+*pf_6_28/100.);
      }
    }
    else{
      for(k=0;k<max_kassa;k++){
				if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue; // hoort niet bij dit filiaal
				if(fldlen(91,11+k*5)){
					AW+=*f(91,12+k*5);
					VW+=*f(91,13+k*5)/(1.+*pf_6_28/100.);
				}
				if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
					AW+=*f(91,12+(k+ft_off)*5);
					VW+=*f(91,13+(k+ft_off)*5)/(1.+*pf_6_28/100.);
				}
      }
    }
    tb[groep_].AW+=AW; tb[groep_].VW+=VW;
    if(*i(6,9)==99) k=DIMBTW;
    else {
      for(k=0;k<DIMBTW;k++) if(btw_pct[k]==*pf_6_28) break;
    }
    btw_bas[k]+=VW;
    next:;
  }
  for(k=0;k<100;k++){
    if(k!=99){
      tb[100].AW+=tb[k].AW;
      tb[100].VW+=tb[k].VW;
    }
    else tb[k].AW=tb[k].VW;/* correctie foute AP in leeggoed */
  }
  for(k=1;k<101;k++){
    if(k==99) continue;
    if(k==100){nextline();fasinit(52);copy("Totaal goederen",s(52,14),15);}
    else{fasinit(52);*u(52,1)=k;fasgeti(52);}
    AW=tb[k].AW;VW=tb[k].VW;pct1=VW/tb[100].VW*100.;
    winst=VW-AW;if(AW) winstpct=winst/AW*100; else winstpct=0;
    if(tb[100].VW-tb[100].AW) pct2=winst/(tb[100].VW-tb[100].AW)*100.;
    else pct2=0;
    if(AW || VW){
      if(k==100) for(j=1;j<=15;j++) prtinfo(j,2);
      else for(j=1;j<=15;j++) prtinfo(j,0);
      nextline();
    }
  }

  k=99;
  fasinit(52);*u(52,1)=k;fasgeti(52);
  AW=tb[k].AW;VW=tb[k].VW;pct1=0;
  winst=0; winstpct=0;
  pct2=0;
  if(AW || VW){
    nextline();
    for(j=1;j<=15;j++) prtinfo(j,0); nextline();
  }

  prt_btwtab();
  prtform(0);prtclose();
  endsr:;
}

static long GetRecNr(stu_)
int16 stu_;
{
	 
	if(fldlen(stu_,1)==2) return (long)(*u(stu_,1));
	else return (long)(*l(stu_,1));
}

static SetRecNr(stu_,val_)
int16 stu_;
long val_;
{
	if(fldlen(stu_,1)==2) *u(stu_,1)=val_;
	else *l(stu_,1)=val_;
}

static cmp_str(p1,p2,len)
int16 len;
char *p1,*p2;
{
  while(len--){
    if(*p1++!=*p2++)return 1;
  }
  return 0;
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
  int16 g,j,k;

  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);
  if(fldlen(66,1)) fileopen(12);
  if(fldlen(92,1)) fileopen(11);
  if(fldlen(60,1)) fileopen(14);
  if(fldlen(16,1)) fileopen(13);

			
  sysget(  34,256,firma);
  sysget(294,4,def_munt);
  sysget(1048,32,&btw_pct[0]);
	sysget(1084,4,&def_btw);
  sysget(1790,2,&sys1790);
  sysget(1918,2,&sear_stt);
  sysget(2216,2,&klt_div1); if(klt_div1==0) klt_div1=1;
  sysget(2222,2,&def_qfak);
	sysget(2770,60,(char *)&nm_loc[0][0]);
  sysget(2727,2,&sys2727);
  sysget(2730,40,(char *)&loc_nr[0]);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
	for(j=0;j<8;j++) if(def_btw==btw_pct[j]) break;
	if(j<8) ArtOnbekend=TbDiversArtikel[j];
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3772,2,&sys3772);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,&sys3896[0]);
  sysget(3974,2,&ft_off);
  sysget(4338,3,kas_munt);
  sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4254,40,(char *)&dt_kvk[0]);
  sysget(4294,40,(char *)&loc_klt[0]);
  sysget(4400,2,&sys4400);
  sysget(4406,2,&art_div);
  sysget(4408,2,&sys4408);
  sysget(4478,2,&sys4478);

  if(ft_off && fldlen(91,11+(ft_off*5))==0) ft_off=0;
	j=0;
  for(max_kassa=0;max_kassa<10;max_kassa++){
    if(fldlen(91,11+(max_kassa*5))==0) break;
    if(fldlen(91,11+((max_kassa+ft_off)*5))==0) break;
		if(nm_kassa[max_kassa][0]) j++;
  }
	if(ft_off && max_kassa>ft_off) max_kassa=ft_off; // veiligheid voor ft_offset
	if(j<=1) max_kassa=1; // meer velden, maar geen naam ingevuld
  sysget(3978,2,&sys3978);/* geen artikelfiche updaten */
  use_kaart=NO; if(fldlen(92,30) && ovltest(294)) use_kaart=YES;

  if(fldlen(6,130) && fldlen(25,8) && *u(25,8)) prx_loff=*u(25,8);
  else prx_loff=0;
  if(fldlen(60,1) && (sys3772 & 0x10)) fileopen(14);

  sysget(3678,2,&def_taal);
  pu_2_1=u(2,1);
  pu_6_1=u(6,1);
  pf_6_28=f(6,28);
  pu_91_2=u(91,2);
  pu_91_3=u(91,3);
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

  for(k=0;k<6;k++){
    if(k==0 || btw_pct[k]){
      j=btw_pct[k];g=btw_pct[k]*10-j*10;
      stcli_d(&btwhfd[k][0],(long)j,2,1);
      copy(",",&btwhfd[k][2],1);
      stcli_d(&btwhfd[k][3],(long)g,1,0);
      copy(" %",&btwhfd[k][4],3);
    }
  }
 zero(&seldata.data_begin,sizeof seldata); seldata.dt_s_beg=*u(25,2)-730;
}
 
static prt_ft_lst()/* printen lijst te factureren bons */
{
  int16 form_dat[8],pr_mode,prtnr,fn_mast_,fn_kassa_;
  int16 mode_=0,j,k,z,n,len_,dd_,mm_,jj_,z_basis_;
  uint16 dt_bon,bonnr;
  float tot_bon,tot_excl,tot_btw,tot_leeg,tot_bet,tot_,pbtw_,bd_ex_;
  float tt_bon,tt_excl,tt_btw,tt_leeg,tt_bet,basis_;
  char btw_str[12],str_[50],buf_[5000],mstfilnm_[50];
 

	if(ask_in_dt("Afdrukken bons te factureren",NO,NO)) return YES;

  fasclos(-2);
  scrget(1,170);
  zero(str_,sizeof str_);
  if(inq_kassa){
    copy("kassa-00",str_,8);stcli_d(&str_[6],(long)inq_kassa,2,0);str_[8]=0x5C;
    copy("kasfac.dat",&str_[9],11);
    mk_name(3936,str_);
  }
	else if(inq_filiaal && (inq_filiaal<10 || inq_filiaal==99)){
		zero(mstfilnm_,sizeof mstfilnm_);
		sprintf_s(mstfilnm_,sizeof mstfilnm_,"fact%02d.dat",inq_filiaal);// factuurbestanden samenvoegen 
		if( (fn_mast_= dopen(mstfilnm_, O_RDONLY|O_BINARY )) == -1 ){// indien niet bestaand, dan creeren
			if((fn_mast_= dopen(mstfilnm_, O_CREAT|O_BINARY )) == -1 ){errnum=1;return YES;}
		}
		dclose(fn_mast_);
    if( (fn_mast_= dopen(mstfilnm_, O_WRONLY|O_BINARY )) == -1 ){errnum=1;return YES;}
		for(k=0;k<max_kassa;k++){
			zero(str_,sizeof str_);
			if(nm_kassa[k][0]){
				if(sys4400 & 0x02) copy("kasfac.dat",str_,15);
				else{
					copy("kassa-00",str_,8);j=k+1;stcli_d(&str_[6],(long)j,2,0);
					str_[8]=0x5C;copy("kasfac.dat",&str_[9],11);
				}
				mk_name(3936,str_);
				if( (fn_kassa_= dopen(filnam, O_RDONLY|O_BINARY )) == -1 )continue;
				FOREVER{
				  len_=dread(fn_kassa_,buf_,5000);
			  	if(len_>0) j=dwrite(fn_mast_,buf_,len_);
			  	if(len_<5000){dclose(fn_kassa_); break;}
				}
			}
		}
		dclose(fn_mast_);
	}
  else{
    sysget(4572,32,filnam);
  }
	if(inq_filiaal){
    if(fasopen(mstfilnm_,1)){errnum=1;return YES;}
	}
	else{
		if(fasopen(filnam,1)){errnum=1;return YES;}
	}
  scrget(1,7);scrupd(-3,0);

  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) return YES;
  free=999;
									
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t40b>Te factureren bons, kassa : ");
  prtifld(fm_uu2,&inq_kassa,-1);prttext("<b><t85>");prttext("Periode ");
  prtifld(fm_udat,&dat_beg,-1); prttext(" - ");prtifld(fm_udat,&dat_end,-1);
  prttext("<t120>");prttext("Blz.<ppp>.");
  prtbuf(1);
  z=1;
  prttab(z,2,2,1,-1); prttitle(z++,"Code",3);
  prttab(z,2,3,0,25); prttitle(z++,"Klant",3);
  prtitab(z,fm_os11,btw_str,1,-1); prttitle(z++,"BTW-nr",3);
  prtitab(z,fm_ou5,&bonnr,1,-1); prttitle(z++,"Bonnr",0x13);
  prtitab(z,fm_udat,&dt_bon,1,-1); prttitle(z++,"Datum",0x3);
  z_basis_=z;
  prtitab(z,fm_uf21_,&pbtw_,1,-1); prttitle(z++,"BTW%",0x13);
  prtitab(z,fm_uf6_2,&basis_,1,-1); prttitle(z++,"Basis",0x13);
  prtitab(z,fm_uf6_2,&tot_excl,1,-1); prttitle(z++,"Goederen",0x13);
  prtitab(z,fm_uf6_2,&tot_btw,1,-1); prttitle(z++,"BTW",0x13);
  prtitab(z,fm_uf6_2,&tot_leeg,1,-1); prttitle(z++,"Leeggoed",0x13);
  prtitab(z,fm_uf6_2,&tot_bon,1,-1); prttitle(z++,"Totaal",0x13);
  prtitab(z,fm_uf6_2,&tot_bet,1,-1); prttitle(z++,"Betaald",0x13);
  prtbuf(3);
  p_pdfname("Te factureren bons",dat_beg,dat_end);
 
  fasinit(2);dt_bon=0;bonnr=0;tot_excl=0;tot_btw=0;
  tt_excl=0;tt_leeg=0;tt_bon=0;tt_bet=0;tt_btw=0;

  fasinit(80);
  FOREVER{
    if(read_rec(mode_)) goto endsr;
    mode_=1;
    if(cmp_str(rec_ele(0),"L1",2)==NO){
      dt_bon=0;tot_excl=0;tot_btw=0;bonnr=0;
      zero((char *)&btw_bas[0],sizeof btw_bas);
      FOREVER{
	if(read_rec(1)) goto endsr;
	if(cmp_str(rec_ele(0),"H1",2)==NO){
	  dd_=val(rec_ele(1));
	  mm_=val(rec_ele(1)+3);
	  jj_=val(rec_ele(1)+6);
	  dt_bon=datejd(jj_,mm_,dd_);
	  if(dat_end && dt_bon>dat_end) break;
	  if(dat_beg && dt_bon<dat_beg) break;
	  bonnr=get_num(2);
	}
	if(cmp_str(rec_ele(0),"H2",2)==NO){
	  len_=ele_len(1);if(len_>fldlen(2,2)) len_=fldlen(2,2);
	  fasinit(2);copy(rec_ele(1),s(2,2),len_);faskeyu(2,1,0);
	  for(k=2;k<6;k++){
	    len_=ele_len(k);if(len_>fldlen(2,k+1)) len_=fldlen(2,k+1);
	    copy(rec_ele(k),s(2,k+1),len_);
	    if(len_<fldlen(2,k+1)){/* rest van veld uitvegen */
	      zero(s(2,k+1)+len_,fldlen(2,k+1)-len_);
	    }
	  }
	  len_=ele_len(6);if(len_>fldlen(2,8)) len_=fldlen(2,8);
	  copy(rec_ele(6),s(2,8),len_);
	  if(len_<fldlen(2,8)){/* rest van veld uitvegen */
	    zero(s(2,8)+len_,fldlen(2,8)-len_);
	  }
	  zero(btw_str,sizeof btw_str);
	  len_=ele_len(7);if(len_>11) len_=11;
	  copy(rec_ele(7),btw_str,len_);
	}
	if(cmp_str(rec_ele(0),"R1",2)==NO){
	  j=get_num(3);
	  if(j!=99){
	    pbtw_=get_num(4);
	    tot_=get_num(7);
	    if(pbtw_) bd_ex_=tot_/(1.+pbtw_/100.);
	    else bd_ex_=tot_;
	    bd_ex_=valu_cnv("EUR","EUR",(double)bd_ex_,(double)(0.01));
	    for(k=0;k<DIMBTW;k++) if(pbtw_==btw_pct[k]) break;
	    if(k<DIMBTW) btw_bas[k]+=bd_ex_;
	    tot_excl+=bd_ex_;tot_btw+=(tot_-bd_ex_);
	  }
	}
	if(cmp_str(rec_ele(0),"R2",2)==NO){
/* leeggoed overslaan */
	}
	n=0;
	if(cmp_str(rec_ele(0),"T1",2)==NO){
	  tot_leeg=get_num(2);
	  tot_bon=get_num(4);
	  tot_bet=get_num(5);
	  if(free<4) prtform(0);
	  else nextline();
	  for(j=0;j<z_basis_;j++) prtinfo(j,0);
	  for(n;n<DIMBTW;n++) if(btw_bas[n]) break;
	  if(n<DIMBTW){
	    pbtw_=btw_pct[n];basis_=btw_bas[n];
	    prtinfo(z_basis_,0);prtinfo(z_basis_+1,0);
	    n++;
	  }
	  for(j=z_basis_+2;j<20;j++) prtinfo(j,0); nextline();
	  zero(s(2,3),fldlen(2,3));
	  copy(s(2,4),s(2,3),fldlen(2,4));prtinfo(2,0);
	  for(n;n<DIMBTW;n++) if(btw_bas[n]) break;
	  if(n<DIMBTW){
	    pbtw_=btw_pct[n];basis_=btw_bas[n];
	    prtinfo(z_basis_,0);prtinfo(z_basis_+1,0);
	    n++;
	  }
	  nextline();
	  zero(s(2,3),fldlen(2,3));
	  copy(s(2,5),s(2,3),fldlen(2,5));
	  for(j=0;j<fldlen(2,5);j++) if(*(s(2,3)+j)=='\0') *(s(2,3)+j)=' ';
	  copy(s(2,6),s(2,3)+fldlen(2,5),fldlen(2,6));
	  prtinfo(2,0);
	  for(n;n<DIMBTW;n++) if(btw_bas[n]) break;
	  if(n<DIMBTW){
	    pbtw_=btw_pct[n];basis_=btw_bas[n];
	    prtinfo(z_basis_,0);prtinfo(z_basis_+1,0);
	    n++;
	  }
	  nextline();
	  tt_excl+=tot_excl;tt_leeg+=tot_leeg;tt_bon+=tot_bon;tt_bet+=tot_bet;
	  tt_btw+=tot_btw;
	  break;
	}
      }
    }
  }
  endsr:;
  fasinit(2);zero(btw_str,sizeof btw_str);
  copy("T O T A A L   ===>",s(2,3),20);
  tot_excl=tt_excl;tot_leeg=tt_leeg;tot_bon=tt_bon;tot_bet=tt_bet;
  tot_btw=tt_btw;bonnr=0;dt_bon=0;
  nextline();
  for(j=0;j<z_basis_;j++) prtinfo(j,2);
  for(j=z_basis_+2;j<20;j++) prtinfo(j,2);nextline();

  prtform(0);prtclose();
  fasclos(-2);
}
 
static toplijst(mode_)
int16 mode_;
{
  int16 form_dat[8],pr_mode,prtnr;
  int16 curs=1,j,k,key,z,mode,mm,dd,yy;
  uint16 used,a,ok_,p_max;
  char sortmeth='V',only_used='J',skip_lg='J', skip_blocked='N',str_[100];

  if(add_ftvk=='\0') add_ftvk='J';
	inq_filiaal=0;zero(nm_fil,sizeof nm_fil);
  FOREVER{
		redo:;
    scrget(2,141);z=1;
		scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
		scraddpicto(2,0,72,22,4,2,573,0,0,"Schrijf uit in Excel");
    if(mode_==0) scrifld(z++,fm_os38,"Lijst van de BEST verkochte artikelen");
    else scrifld(z++,VarTextFmt(41,0),"Lijst van de SLECHTST verkochte artikelen");
    scrfld(z++,25,1);
    scrifld(z++,fm_uAVW,&sortmeth);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&inq_kassa);
		if(fldlen(66,11)){scrifld(-z,fm_uu2,&inq_filiaal);z++; scrifld(z++,fm_os6,nm_fil);}
		else z+=2;
    if(ft_off>0) scrifld(z++,fm_uJN,&add_ftvk); else streepje(z++);
    scrifld(z++,fm_uJN,&only_used);
    scrifld(z++,fm_uJN,&skip_lg);
		scrifld(z++,fm_uJN,&skip_blocked);
    key=scrupd(curs,0x0581);
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(inq_filiaal<0 || (inq_filiaal>10 && inq_filiaal!=99)) {zero(nm_fil,sizeof nm_fil);curs=5; errnum=34;goto redo;}
		if(inq_filiaal && inq_filiaal<=10){
			if(fldlen(66,11+(inq_filiaal-1)*15)==0) {errnum=34;curs=5; goto redo;}
			copy(nm_loc[inq_filiaal-1],nm_fil,6);
		}
		else if(inq_filiaal==99) copy("DEPOT",nm_fil,6);
		else zero(nm_fil,sizeof nm_fil);
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
		prt2xls=NO;if(key==5002){prt2xls=YES;key=108;}
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(key==108) break;
  }
  if(ovlcall(2215,4)) goto endsr;

	if (prt2xls) {
		scrget(1,6);scrupd(-3,0);
		zero(str_, sizeof str_);
		if(mode_==0) copy0("Beste artikels op ",str_,20); else copy0("Slechtste artikels op ",str_,20);
		switch(sortmeth){
			case 'A' : copy0("aantal ",&str_[strlen(str_)],17);break;
			case 'V' : copy0("verkoopwaarde ",&str_[strlen(str_)],17);break;
			case 'W' : copy0("brutowinst ",&str_[strlen(str_)],17);break;
			default  : break;
		}
		if(inq_kassa){ copy0("kassa ",&str_[strlen(str_)],17);stcli_d(&str_[strlen(str_)], (long)inq_kassa, 2, 0);}
		else if(inq_filiaal) {copy0("filiaal ",&str_[strlen(str_)],17);copy0(nm_fil,&str_[strlen(str_)],5);}
		if (dat_beg) {
			copy(" ", &str_[strlen(str_)], 1);
			jddate(dat_beg, &yy, &mm, &dd);
			yy %= 100;
			stcli_d(&str_[strlen(str_)], (long)dd, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)mm, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)yy, 2, 0);
		}

		if (dat_end) {
			if (dat_beg)
				copy(" - ",&str_[strlen(str_)], 3);

			jddate(dat_end, &yy, &mm, &dd);
			yy %= 100;
			stcli_d(&str_[strlen(str_)], (long)dd, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)mm, 2, 0); str_[strlen(str_)] = '-';
			stcli_d(&str_[strlen(str_)], (long)yy, 2, 0);
		}

		copy(".xls", &str_[strlen(str_)], 4);
		XlsRef = XlsCreate(str_);

		if (XlsRef <= 0)
		{
			errnum = 1;
			goto endsr;
		}
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,0,0,NO,NO);
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		XlsSelectWorkSheet(XlsRef, 1, "Toplijst");
		XlsColumnSize(XlsRef,3,40);
		XlsRij = 1;
		XlsKol = 1;
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Nr", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Code", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Omschrijving", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Aantal", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "A.waarde", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "V.waarde", 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Winst", 0);
		XlsRij++;
	}
	else {
		getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
		if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
		free=999;
									
		scrget(1,7);scrupd(-3,0);
		prtfld(25,1,-1); prttext("<t30b>Lijst artikels volgens ");
		if(mode_==0) prttext("beste "); else prttext("slechtste ");
		switch(sortmeth){
			case 'A' : prttext("aantal");break;
			case 'V' : prttext("verkoopwaarde");break;
			case 'W' : prttext("brutowinst");break;
			default  : break;
		}
		if(inq_kassa) {prttext("<t68>Kassa ");prtifld(fm_uu2,&inq_kassa,-1);}
		else if(inq_filiaal) {prttext("<t68>Filiaal ");prtifld(fm_os5,nm_fil,-1);}
		prttext("<b><t80>Per. ");prtifld(fm_udat,&dat_beg,-1);prttext(" - ");
		prtifld(fm_udat,&dat_end,-1); prttext("<t120>");prttext("Blz.<ppp>.");
		prtbuf(1);
		z=1;
		prtitab(z,fm_uu4,&a,1,-1); prttitle(z++,"Nr",0x13);
		prttab(z,6,2,2,-1); prttitle(z++,"Code",3);
		prttab(z,6,3,1,-1); prttitle(z++,"Omschrijving",3);
		prtitab(z,fm_ud7_2,&qlv,1,-1); prttitle(z++,"Aantal",0x13);
		prtitab(z,fm_ud7_2,&AW,1,-1); prttitle(z++,"A.waarde",0x13);
		prtitab(z,fm_ud7_2,&VW,2,-1); prttitle(z++,"V.waarde",0x13);
		prtitab(z,fm_ud7_2,&winst,3,-1); prttitle(z++,"Winst",0x13);
		prtbuf(3);
		p_pdfname("Toplijst",dat_beg,dat_end);
	}
  for(k=0;k<DIM_TB;k++) zero((char *)&tb[k].rec,sizeof tb[0]);
  fasinfo(6,1);
  used=*pu_6_1;p_max=0;
  for(a=1;a<=used;a++){
    *pu_6_1=a;
    if(fasgetu(6)==0){
      if(skip_lg=='J' && *u(6,9)==99) continue;
			if(skip_blocked=='J' && *u(6,200)) continue;
      if(DirCall_DRK2215_SelectArtikel()==NO) continue;
      fasinit(91);*pu_91_2=*pu_6_1;*pu_91_3=dat_beg;mode=1;AW=0;VW=0;qlv=0;
      FOREVER{
				next_bew:;
				if(faskeyi(91,1,mode)) break;mode=2;
				if(*pu_6_1!=*pu_91_2) break;
				if(dat_beg && *pu_91_3< dat_beg) goto next_bew;
				if(dat_end && *pu_91_3>dat_end) break;

				if(inq_kassa){
					qlv+=*f(91,11+(inq_kassa-1)*5);
					AW+=*f(91,12+(inq_kassa-1)*5);
					VW+=*f(91,13+(inq_kassa-1)*5)/(1.+*pf_6_28/100.);
					if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
						qlv+=*f(91,11+(inq_kassa-1+ft_off)*5);
						AW+=*f(91,12+(inq_kassa-1+ft_off)*5);
						VW+=*f(91,13+(inq_kassa-1+ft_off)*5)/(1.+*pf_6_28/100.);
					}
				}
				else{
					for(k=0;k<max_kassa;k++){
						if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue; // hoort niet bij dit filiaal
						if(fldlen(91,11+k*5)){
							qlv+=*f(91,11+k*5);
							AW+=*f(91,12+k*5);
							VW+=*f(91,13+k*5)/(1.+*pf_6_28/100.);
						}
						if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
							qlv+=*f(91,11+(k+ft_off)*5);
							AW+=*f(91,12+(k+ft_off)*5);
							VW+=*f(91,13+(k+ft_off)*5)/(1.+*pf_6_28/100.);
						}
					}
				}
      }
      if(only_used!='J' || qlv){
				winst=VW-AW; ok_=NO;
				for(k=0;k<p_max;k++){
					if(mode_==0){/* sorteren volgens beste */
						switch(sortmeth){
							case 'A' : if(qlv>=tb[k].aantal) ok_=YES; break;
							case 'V' : if(VW>=tb[k].VW) ok_=YES; break;
							case 'W' : if(winst>=(tb[k].VW-tb[k].AW)) ok_=YES; break;
							default  : break;
						}
					}
					else{/* sorteren volgens slechtste */
						switch(sortmeth){
							case 'A' : if(qlv<=tb[k].aantal) ok_=YES; break;
							case 'V' : if(VW<=tb[k].VW) ok_=YES; break;
							case 'W' : if(winst<=(tb[k].VW-tb[k].AW)) ok_=YES; break;
							default  : break;
						}
					}
					if(ok_){
						for(j=p_max-1;j>=k;j--){
							copy((char *)&tb[j],(char *)&tb[j+1],sizeof tb[0]);
						}
						tb[k].rec=*pu_6_1;tb[k].AW=AW;tb[k].VW=VW;tb[k].aantal=qlv;
						p_max++; if(p_max>=DIM_TB) p_max=DIM_TB;
						break;
					}
				}
				if(ok_==NO && k<DIM_TB){
					tb[k].rec=*pu_6_1;tb[k].AW=AW;tb[k].VW=VW;tb[k].aantal=qlv;
					p_max++; if(p_max>=DIM_TB) p_max=DIM_TB;
				}
      }
    }
  }
  tot_aw=0;tot_vw=0;tot_qlv=0;
  scrget(1,6);scrupd(-3,0);
  for(k=0;k<p_max;k++){
    fasinit(6);*pu_6_1=tb[k].rec;fasgeti(6);
    qlv=tb[k].aantal;
    AW=tb[k].AW;VW=tb[k].VW;winst=tb[k].VW-tb[k].AW;
    tot_aw+=AW;tot_vw+=VW;tot_qlv+=qlv;
    a=k+1;
		if(prt2xls){
			XlsKol=1;
			WriteVar2Xls(XlsRij,XlsKol++,fm_uu4,(char *)&a,0);
			WriteFld2Xls(XlsRij,XlsKol++,6,2,0);
			WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
			WriteVar2Xls(XlsRij,XlsKol++,fm_ud7_2,(char *)&qlv,0);
			WriteVar2Xls(XlsRij,XlsKol++,fm_ud7_2,(char *)&AW,0);
			WriteVar2Xls(XlsRij,XlsKol++,fm_ud7_2,(char *)&VW,0);
			WriteVar2Xls(XlsRij,XlsKol++,fm_ud7_2,(char *)&winst,0);
			XlsRij++;
		}
		else{
      for(j=1;j<20;j++) prtinfo(j,0);nextline();
		}
  }

  fasinit(6); copy("T O T A A L   ===>",s(6,3),19);
  qlv=tot_qlv;
  AW=tot_aw;
  VW=tot_vw;
  winst=VW-AW;a=0;
	if (prt2xls) XlsClose(XlsRef, 1);
	else{
    nextline();for(k=0;k<20;k++) prtinfo(k,2);nextline();
    prtclose();
	}
  endsr:;
}

static dump_vrk()
{
  int16 curs=1,k,key,z,mode;

  if(filnam[0]=='\0') copy("KASVERK.TXT",filnam,20);seqo_mode=2;
  if(add_ftvk=='\0') add_ftvk='J';
  inq_kassa=0;if(max_kassa==1) inq_kassa=1;
  FOREVER{
    redo:;
    scrget(2,267);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&inq_kassa);
    if(ft_off>0) scrifld(z++,fm_uJN,&add_ftvk); else streepje(z++);
    scrifld(z++,fm_us20,filnam);
    key=scrupd(curs,0x481);curs=3;
    if(key==111) ovlexit(-1);
    if(key==101) return YES;
    if(dat_end==0 || dat_end<dat_beg){curs=3;errnum=38;goto redo;}
    if(inq_kassa && fldlen(91,11+(inq_kassa-1)*5)==0){
      curs=5;errnum=34;goto redo;
    }
    if(filnam[0]=='\0'){curs=6;errnum=38;goto redo;}
    if(key==108) break;
  }
  fasunlck(-2);
  scrget(1,170);
  fasclos(-2);if(fasopen(filnam,2)) {errnum=9;goto endsr;}
 
  scrget(1,7);scrupd(-3,0);
  fasinit(91);*pu_91_3=dat_beg;mode=1;
  FOREVER{
    next_bew:;
    if(faskeyi(91,2,mode)) break;mode=2;
    if(dat_beg && *pu_91_3< dat_beg) goto next_bew;
    if(dat_end && *pu_91_3>dat_end) break;
    if(*u(91,2)==0) goto next_bew;
    fasinit(6);*pu_6_1=*u(91,2);fasgeti(6);

    zero(seqo_str,sizeof seqo_str);pos=0;
    seqo_fld(91,3);seqo_fld(6,2);seqo_fld(6,3);seqo_fld(6,28);
    for(k=0;k<max_kassa;k++){
      if(inq_kassa && k!=(inq_kassa-1)) continue;
      if(fldlen(91,11+k*5)==0 || nm_kassa[k][0]=='\0') continue;
      if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
	*f(91,11+k*5)+=*f(91,11+(k+ft_off)*5);/* ft stuks */
	*f(91,12+k*5)+=*f(91,12+(k+ft_off)*5);/* ft AW */
	*f(91,13+k*5)+=*f(91,13+(k+ft_off)*5);/* ft VW */
      }
      seqo_fld(91,11+k*5);/* stuks */
      seqo_fld(91,12+k*5);/* AW */
      seqo_fld(91,13+k*5);/* VW */
    }
    CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
    seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
							  /* artikel dumpen */
    seqo_len=0;
    for(k=0;k<pos;k+=280){
      if((k+280)>pos) seqo_len=pos-k;
      else seqo_len=280;
      copy(&seqo_str[k],s(80,1)+4,seqo_len);
      seqo_flush();
    }
  }
  fasclos(-2);
endsr:;
	fasunlck(-1);
}
 
static seqo_fld(stu_,fld_)
int16 stu_,fld_;
{
  int16 yy,mm,dd;
  float fbd_;
  char str_[15];
 
  if(fldlen(stu_,fld_)==0) goto endsr;
  fmt_get(stu_,fld_);
  if(fmt[1]==0xC8 || fmt[1]==0x88){/* string */
    char2str(s(stu_,fld_),fldlen(stu_,fld_));
  }
  if(fmt[1]==0xD0 || fmt[1]==0x90){/* uint16 */
    fbd_=*u(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xD1 || fmt[1]==0x91){/* integer */
    fbd_=*i(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xD3 || fmt[1]==0x93){/* long */
    fbd_=*l(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xD4 || fmt[1]==0x94){/* float */
    fbd_=*f(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xD5 || fmt[1]==0x95){/* double */
    fbd_=*d(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xC0 || fmt[1]==0x80){/* date */
    if(*u(stu_,fld_)==0) seqo_str[pos++]=0x09;
    else{
      jddate(*u(stu_,fld_),&yy,&mm,&dd);
      stcli_d(str_,(long)dd,2,0);str_[2]='/';
      stcli_d(&str_[3],(long)mm,2,0);str_[5]='/';
      stcli_d(&str_[6],(long)yy,4,0);
      char2str(str_,10);
    }
  }
  if(fmt[1]==0xA8 || fmt[1]==0xE8){/* grb */
    zero(str_,sizeof str_);
    grb_deco(str_,l(stu_,fld_));
    char2str(str_,10);
  }
  endsr:;
}

static char2str(ps_,len_)
char *ps_;
int16 len_;
{
  int16 k,orig_pos_;
 
  orig_pos_=pos;
  if(len_){
    copy(ps_,&seqo_str[pos],len_);while(seqo_str[pos]) pos++;
    for(k=orig_pos_;k<pos;k++){
      if(seqo_str[k]==0x09) seqo_str[k]='.';/* delete | */
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;/* delete trailing blanks */
    pos++;
  }
  seqo_str[pos++]=0x09;
}

static flt2str(bd_)
float bd_;
{
  double bedrag_,add_=0;
  long val_;
								
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*100+add_;value=val_/100;
  val2str(0);
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
 
static seqo_flush()
{
  if(seqo_len){
    *l(80,1)=seqo_pos;
    fasseqo(80,seqo_mode,seqo_len+4);
    seqo_pos+=seqo_len;
    seqo_len=0;
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


static mk_name(adr_pref,ps)
uint16 adr_pref;
char *ps;
{
  char *pd;

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


 
static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
/*
  if(stu_<=2) parmcall[1]=7;            bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3;                                              GEEN ADD
*/
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
