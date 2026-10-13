/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0296GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0296dat
#define ovlcod DRK0296cod
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

char ovldat[] = "drk0296  00:01 10/10/05 (c) Jamadata"; // promoties in facturatie : punt V.3.9 (velden 58,90-94 en 6,150-184 )

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_REC         1000

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF
						
extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os7[]   = {7,0x88,7,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_os18[]  = {7,0x88,18,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x20,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_ui5_[]  = {6,0xD1,5,0,0x20,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x20,0};
static char fm_of6_0[] = {6,0x94,6,0,0x70,0};
static char fm_uf5_4[] = {6,0xD4,5,4,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_uf4_2[] = {6,0xD4,4,2,0x70,0};
static char fm_uf504[] = {6,0xD4,5,4,0x30,0};
static char fm_uf302[] = {6,0xD4,3,2,0x30,0};
static char fm_uf201[] = {6,0xD4,2,1,0x30,0};
static char fm_of5_2[] = {6,0x94,5,2,0x70,0};
static char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static char fm_of4_1[] = {6,0x94,4,1,0x70,0};
static char fm_of4_2[] = {6,0x94,4,2,0x70,0};
static char fm_of4_4[] = {6,0x94,4,4,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_btw[]   = {6,0x91,2,0,0x20,0};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_u_AK[]  = {11,0xC8,1,0,1,0,'A','A','K','K',0};
static char fm_usAT[]  = {9,0xC8,1,0,1,0,'A','T',0};
static char fm_uPB[]   = {11,0xC8,1,0,1,0,'%','%','B','B',0};
static char fm_uNB[]   = {11,0xC8,1,0,1,0,'N','N','B','B',0};
static char fm_u05NBFG[] = {15,0xC8,1,0,1,0,'0','5','N','N','B','B','F','G',0};
static char fm_u_09[] = {9,0xC8,1,0,1,0,'0','9',0};


static int16 prt2pdf;
static int16 fkey=2,free;
static char nm_20[20],nm_15[15],oldnm[65],buff500[500];
static char fmt[40],promocode,art_res[50],lev_res[50],inq_type,type_str[6];
static flag lvcd,klcd,chk_btoeg=NO,sys3720;
static uint16 inq_groep=0,inq_lev,inq_art,last_dtb,last_dte;
static flag sear_stt,sys3586,sys3588,sys3894,sys3632,sys3876,sys3618;
static uint16 dt_beg,dt_end,inq_klt,dt_start;
static struct{
  uint16 rec;
  char bits;
} tb[DIM_REC];

static char vptekst[100],stuksprx[10],def_munt[4];
static int16 def_taal;
 
extern int16 ilength;
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol,Prt2Xls;
static int16 *pi;
static char SelectXlsFldNr[150];
static int16 StylTotaal, StylGrpTot, StylKlasse, StylNormal, StylDate, StylTitel, Styl2Use;


ovlcod()
{
  int16 key;
  char choice;
 
  initload();
  FOREVER{
		redo:;
    scrget(2,226);scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0296A");
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) break;
    if(key==111) ovlexit(-1);
    switch(choice){
      case '1': single();break;
      case '2': multiple();break;
      case '3': prt_pro(); break;
      case '4': kill_pro(); break;
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}

#include "Std\XlsFunc.c"

static single()
{
									
  FOREVER{
    if(select_pro("Toevoegen/aanpassen van 1 promotie",NO)) break;
    tb[0].rec=*u(6,1);
    pro_upd(0);
  }
}

static multiple()
{
  int16 j,n,curs,z,key,mode_,start,max_;
  char *pd;
  uint16 last_fnd;

  FOREVER{
    if(select_pro("Aanpassen lijst BESTAANDE promoties",YES)) break;
    zero((char *)&tb[0],sizeof tb);fasinit(6);
    if(inq_art) {*u(6,1)=inq_art;fasgeti(6);}
    start=0;max_=DIM_REC;mode_=1;curs=2;last_fnd=0;
    FOREVER{
      redo:;
      scrnum=0; scrget(2,227);z=1;
      scrifld(z++,fm_os40,"Lijst geselecteerde promoties");
      for(j=start;j<start+18;j++){
	next:;
	if(tb[j].rec==0){
	  if(faskeyi(6,1,mode_)) {max_=j;break;}
	  mode_=2;
	  last_fnd=*u(6,1);
	  if(inq_art && *u(6,1)!=inq_art) {max_=j;break;}
	  if(inq_lev && *u(6,7)!=inq_lev) goto next;
	  if(inq_groep && *u(6,9)!=inq_groep)  goto next;
	  if((dt_beg || dt_end) && *u(6,150)==0) goto next;
	  if(dt_end && *u(6,150)>dt_end ) goto next;
	  if(dt_beg && *u(6,151) && *u(6,151)<dt_beg) goto next;
	  tb[j].rec=*u(6,1);
	}
	else {
	  fasinit(6); *u(6,1)=tb[j].rec;fasgeti(6);
	}
	pd=&oldnm[0]; pd+=add_str(pd,10,6,2,' ');pd+=add_str(pd,30,6,3,'\0');
	scrifld(z,fm_us40,oldnm);
	if(tb[j].bits & 0x10) scrchat(z++,0x8); else z++;
	scrofld(z++,6,150,-1); scrofld(z++,6,151,-1);
      }
      if(start && start==max_){start-=18;goto redo;}
      if(max_==0) {errnum=39;break;}
      key=scrupd(curs,0x087);curs=2;
      if(key==101) break;
      if(key==108 || key==109){
	n=(fldcurs-1)/3; n+=start;
	curs=fldcurs;
	if(tb[n].rec){
	  if(key==108) {pro_upd(n);tb[n].bits |=0x10;}
	}
      }
      if(key==102) start-=18;
      if(key==103) {start+=18;if(start>=max_-18) start=max_-18;}
      if(start<0) start=0;
      fasinit(6);*u(6,1)=last_fnd;fasgeti(6);
    }
  }
  endsr:;
}

static pro_upd(p_tb_)
int16 p_tb_;
{
  int16 j,k,key,z,curs=3;

  fasinit(6);*u(6,1)=tb[p_tb_].rec;fasgeti(6);
  if(*u(6,150)==0 && *u(6,151)==0){
    zero(s(6,150),s(6,185)-s(6,150));
    *u(6,150)=last_dtb; *u(6,151)=last_dte;
  }
  FOREVER{
    redo:;
    scrget(2,228); z=1;
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
    for(k=150;k<155;k++) scrfld(z++,6,k);
    for(k=0;k<6;k++){
      if(fldlen(6,PrNrs[k])){
				scrifld(z++,fm_os6,&vptekst[k*10]);
				scrofld(z++,6,PrNrs[k],-1);
				if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
				else scrifld(z++,fm_os5,"Excl.");
				scrfld(z++,6,155+k*5);
				scrfld(z++,6,156+k*5);
				scrfld(z++,6,157+k*5);
				scrfld(z++,6,158+k*5);
				scrfld(z++,6,159+k*5);
      }
      else for(j=0;j<8;j++) streepje(z++);
    }
    for(k=6;k<10;k++){
      if(fldlen(6,PrNrs[k]) && fldlen(6,149)==52){
				scrifld(z++,fm_os6,&vptekst[k*10]);
				scrofld(z++,6,PrNrs[k],-1);
				if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
				else scrifld(z++,fm_os5,"Excl.");
				scrifld(z++,fm_uf6_2,s(6,149)+(k-6)*13);
				scrifld(z++,fm_uf3_2,s(6,149)+4+(k-6)*13);
				scrifld(z++,fm_uf4_2,s(6,149)+8+(k-6)*13);
				scrifld(z++,fm_uJN,s(6,149)+12+(k-6)*13);
				z++;
      }
      else for(j=0;j<8;j++) streepje(z++);
    }
    key=scrupd(curs,0x0A0);curs=3;
    if(key==106) return NO;
    if(*u(6,151)<*u(6,150)){errnum=38;goto redo;}
    if(key==108){
      if(*u(6,150)==0 && *u(6,151)==0){
				if(scr_ok("Wenst U deze promotie te schrappen ?")==NO) goto redo;
				zero(s(6,150),s(6,185)-s(6,150)); zero(s(6,149),fldlen(6,149));
      }
      else{
				if(*u(6,150)==0 || *u(6,151)==0) {errnum=38;goto redo;}
				for(k=0;k<6;k++){
					if(*f(6,155+k*5) || *f(6,156+k*5) || *f(6,157+k*5)) break;
				}
				if(k>=6 && *s(6,154)=='\0'){curs=5;errnum=38;goto redo;}
				last_dtb=*u(6,150); last_dte=*u(6,151);
      }
      break;
    }
  }
	if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
  fasupd(6); fasflush(0);
  endsr:;
  return YES;
}

static select_pro(ptxt,mode_) // mode_ : 0= 1 artikel, 1= selectie lijst, 2=selectie lijst om te printen
char *ptxt;
int16 mode_;
{
  int16 key,z,j,curs=2;
 
  fasinit(6);fasinit(1);Prt2Xls=NO;
  inq_groep=0;
  FOREVER{
    redo:
    scrget(2,229);z=1;
		scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF");
		if(mode_==2) scraddpicto(2,0,72,22,4,2,573,0,0,"Maak XLS"); 
    scrifld(z++,fm_os40,ptxt);
    scrfld(z++,25,1);
    scrfld(z++,6,3);
    if(mode_){
      scrifld(z++,fm_udat,&dt_beg);scrifld(z++,fm_udat,&dt_end);
      if(mode_==2){
  			scrifld(-z,fm_u_09,&inq_type); z++;
        scrifld(z++,fm_os6,type_str);
			} else streepje(z++);
    } else for(j=0;j<3;j++) streepje(z++);
    key=scrupd(curs,0x0481);curs=2;
		prt2pdf=NO;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    prt2pdf=NO;if(key==5001){prt2pdf=YES; key=108;} // pdf
		Prt2Xls=NO;if(key==5002){Prt2Xls=YES;key=108;}
    if(key==101) return YES;
    if(key==111) ovlexit(-1);
    if(*s(6,3) || mode_==NO){
      if(search(6,0)) {curs=3;goto redo;}
    }
    else fasinit(6);
#if 0
    if(*s(1,3)){
      if(search(1,0)) {curs=3;goto redo;}
    }
    else fasinit(1);
#endif
    if(mode_ && dt_beg==0) {curs=4;errnum=38;goto redo;}
    inq_lev=*u(1,1);inq_art=*u(6,1);
    zero(type_str,sizeof type_str);
    if(inq_type){
      j=inq_type-'0'; copy(&vptekst[j*10],type_str,6);
    }
    if(key==18){curs=fldcurs+1; goto redo;}
    if(key==108) break;
  }
  return NO;
}

static kill_pro()
{
  int16 g;
  uint16 n;

  if(select_pro("Wissen van factuur-promoties",YES)) goto endsr;
  if(scr_ok("Wenst U echt de geselecteerde promoties te wissen ???")==NO) goto endsr;
  scrget(1,7);scrupd(-3,0);
  fasinit(6);
  if(inq_art) {*u(6,1)=inq_art;fasgeti(6);}
  n=0;scrnum=0;
  FOREVER{/* artikels */
    next_6:;
    *u(6,1)=++n;
    g=fasgeti(6);
    if(g==47)break;
    if(g!=46){/* deleted record */
      if(inq_art && *u(6,1)!=inq_art) goto next_6;
      if(inq_lev && *u(6,7)!=inq_lev) goto next_6;
      if(inq_groep && *u(6,9)!=inq_groep)  goto next_6;
      if((dt_beg || dt_end) && *u(6,150)==0) goto next_6;
      if(dt_end && *u(6,150)>dt_end ) goto next_6;
      if(dt_end && *u(6,151)>dt_end ) goto next_6;/* loopt nog verder */
      if(dt_beg && *u(6,151) && *u(6,151)<dt_beg) goto next_6;
      zero(s(6,150),s(6,185)-s(6,150));
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
      fasupd(6);
    }
  }
  fasflush(0);
  endsr:;
}

static prt_pro()
{
  int16 form_dat[8],prmode,j,k,prtnr,z,mode_,first_;
  float pprx_,pkrt_,pkbd_,nprx_;
  char ptype_[7],pgrat_,type_[2],str_[25];
 
  if(select_pro("Afdrukken factuur-promoties",2)) goto endsr;
  scrget(1,6);scrupd(-3,0);
	zero(type_,sizeof type_);
	if(Prt2Xls){
		scrget(1,7);scrupd(-3,0);
		XlsRef=XlsCreate("Factuurpromoties.XLS");
		if(XlsRef<=0) {errnum=1;goto endsr;}

		XlsColumnSize(XlsRef,2,40);XlsColumnSize(XlsRef,6,30);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
		StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);

		XlsRij=1;XlsKol=1;Styl2Use=StylTitel;
	  XlsWrite(XlsRef,0,XlsKol++,0,"Code",Styl2Use); 
    XlsWrite(XlsRef,0,XlsKol++,0,"Naam",Styl2Use); 
		XlsWrite(XlsRef,0,XlsKol++,0,"Van",Styl2Use); 
		XlsWrite(XlsRef,0,XlsKol++,0,"Tot",Styl2Use); 
		XlsWrite(XlsRef,0,XlsKol++,0,"Vanaf",Styl2Use); 
		XlsWrite(XlsRef,0,XlsKol++,0,"Promo-tekst",Styl2Use); 
		for(k=0;k<10;k++){
			if(k>5 && fldlen(6,149)!=52) continue;
			type_[0]='0'+k;
			if(inq_type && inq_type!=type_[0]) continue;
			zero(str_,sizeof str_); sprintf_s(str_,20,"P%s-Verkoopprijs",type_); XlsWrite(XlsRef,0,XlsKol++,0,str_,Styl2Use); 
			zero(str_,sizeof str_); sprintf_s(str_,20,"P%s-Promo-prijs",type_); XlsWrite(XlsRef,0,XlsKol++,0,str_,Styl2Use);
			zero(str_,sizeof str_); sprintf_s(str_,20,"P%s-Korting%%",type_); XlsWrite(XlsRef,0,XlsKol++,0,str_,Styl2Use);
			zero(str_,sizeof str_); sprintf_s(str_,20,"P%s-KortingEUR",type_); XlsWrite(XlsRef,0,XlsKol++,0,str_,Styl2Use);
			zero(str_,sizeof str_); sprintf_s(str_,20,"P%s-Nettoprijs",type_); XlsWrite(XlsRef,0,XlsKol++,0,str_,Styl2Use);
		}
		//XlsWrite(XlsRef,0,XlsKol++,0,"P0-prijs",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P0-kort%",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P0-korting",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P0-netto",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P1-prijs",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P1-kort%",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P1-korting",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P1-netto",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P2-prijs",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P2-kort%",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P2-korting",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P2-netto",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P3-prijs",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P3-kort%",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P3-korting",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P3-netto",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P4-prijs",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P4-kort%",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P4-korting",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P4-netto",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P5-prijs",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P5-kort%",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P5-korting",Styl2Use); 
		//XlsWrite(XlsRef,0,XlsKol++,0,"P5-netto",Styl2Use); 
		XlsRij++;
	}
	else{

		getsysprNew(5,form_dat,&prmode,&prtnr);if(prt2pdf) PrintPaperNr=0;

		if((errnum=prtopen(prtnr,form_dat,6,132,prmode,4))!=0) goto endsr;
		prtfld(25,1,25);prttext("<t35b>Promoties ");
		prtifld(fm_udat,&dt_beg,-1);prttext(" - ");prtifld(fm_udat,&dt_end,-1);
		prttext("<b><t65>");
		prtfld(25,2,-1);
		prttext("<t119>Blz.<ppp>.");
		prtbuf(1);z=1;
 
		prttab(z,6,2,1,-1);prttitle(z++,"Code",3);
		prttab(z,6,3,1,-1);prttitle(z++,"Artikel",3);
		prttab(z,6,153,1,-1);prttitle(z++,"Vanaf",0x13);
		prttab(z,6,154,1,-1);prttitle(z++,"Promo-tekst",3);
		prtitab(z,fm_os6,ptype_,1,-1); prttitle(z++,"Ptype",3);
		prtitab(z,fm_of6_2,&pprx_,0,-1); prttitle(z++,"Prom.pr.",0x13);
		prtitab(z,fm_of4_2,&pkrt_,0,-1); prttitle(z++,"Kort.%",0x13);
		prtitab(z,fm_of6_2,&pkbd_,0,-1); prttitle(z++,"Kort.bdr",0x13);
		prtitab(z,fm_of6_2,&nprx_,0,-1); prttitle(z++,"Netto pr.",0x13);
	/*  prtitab(z,fm_os1,&pgrat_,1,-1); prttitle(z++,"Toon",3); */
		prtbuf(3);
		p_pdfname("Promoties",dt_beg,dt_end);
	}
  fasinit(6);free=999;
  mode_=1;
  while(free>=0){
    next:;
    if(faskeyi(6,1,mode_)) break; mode_=2;
    if(inq_art && *u(6,1)!=inq_art) break;
#if 0
    if(inq_lev && *u(6,7)!=inq_lev) goto next;
    if(inq_groep && *u(6,9)!=inq_groep)  goto next;
#endif
    if((dt_beg || dt_end) && *u(6,150)==0) goto next;
    if(dt_end && *u(6,150)>dt_end ) goto next;
    if(dt_beg && *u(6,151) && *u(6,151)<dt_beg) goto next;
    if(inq_type){
      k=inq_type-'0';
      if(is_pro(k)==NO) goto next;
			if(Prt2Xls){
				XlsKol=1;
				WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
				WriteVar2Xls(XlsRij,XlsKol++,fm_udat,(char *)u(6,150),StylDate);
				WriteVar2Xls(XlsRij,XlsKol++,fm_udat,(char *)u(6,151),StylDate);
				if(*f(6,153)) WriteFld2Xls(XlsRij,XlsKol++,6,153,StylNormal); else WriteVar2Xls(XlsRij,XlsKol++,fm_os1,"",StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,6,154,StylNormal);
				for(k=0;k<10;k++){
					if(k>5 && fldlen(6,149)!=52) continue;
					type_[0]='0'+k;	if(inq_type && inq_type!=type_[0]) continue;
					if(is_pro(k)==NO) XlsKol+=5;
					else{
						if(k<6){
							pprx_=*f(6,155+k*5);
							pkrt_=*f(6,156+k*5);
							pkbd_=*f(6,157+k*5);
							pgrat_=*s(6,158+k*5);
						}
						else{
							pprx_=*(float *)(s(6,149)+(k-6)*13);
							pkrt_=*(float *)(s(6,149)+4+(k-6)*13);
							pkbd_=*(float *)(s(6,149)+8+(k-6)*13);
							pgrat_=*(s(6,149)+12+(k-6)*13);
						}
						if(pprx_) nprx_=pprx_; else nprx_=*f(6,PrNrs[k]);
						if(pkbd_) nprx_-=pkbd_;
						if(pkrt_){
							nprx_=(nprx_-*f(6,30))*(100-pkrt_)/100+*f(6,30);
						}
						nprx_=valu_cnv("EUR","EUR",(double)nprx_,(double)0.01);
						WriteFld2Xls(XlsRij,XlsKol++,6,21+k,StylNormal); 
						if(pprx_) WriteVar2Xls(XlsRij,XlsKol++,fm_of4_2,&pprx_,StylNormal); else WriteVar2Xls(XlsRij,XlsKol++,fm_os1,"",StylNormal);
						if(pkrt_) WriteVar2Xls(XlsRij,XlsKol++,fm_of4_2,&pkrt_,StylNormal); else WriteVar2Xls(XlsRij,XlsKol++,fm_os1,"",StylNormal);
						if(pkbd_) WriteVar2Xls(XlsRij,XlsKol++,fm_of4_2,&pkbd_,StylNormal); else WriteVar2Xls(XlsRij,XlsKol++,fm_os1,"",StylNormal);
						WriteVar2Xls(XlsRij,XlsKol++,fm_of4_2,&nprx_,StylNormal);
					}
				}
				XlsRij++;
			}
			else{
				copy(&vptekst[k*10],ptype_,6);
				if(k<6){
					pprx_=*f(6,155+k*5);
					pkrt_=*f(6,156+k*5);
					pkbd_=*f(6,157+k*5);
					pgrat_=*s(6,158+k*5);
				}
				else{
					pprx_=*(float *)(s(6,149)+(k-6)*13);
					pkrt_=*(float *)(s(6,149)+4+(k-6)*13);
					pkbd_=*(float *)(s(6,149)+8+(k-6)*13);
					pgrat_=*(s(6,149)+12+(k-6)*13);
				}
				if(pprx_) nprx_=pprx_; else nprx_=*f(6,PrNrs[k]);
				if(pkbd_) nprx_-=pkbd_;
				if(pkrt_){
					nprx_=(nprx_-*f(6,30))*(100-pkrt_)/100+*f(6,30);
				}
				nprx_=valu_cnv("EUR","EUR",(double)nprx_,(double)0.01);
				for(j=0;j<20;j++) prtinfo(j,0);nextline();
			}
    }
    else {
			if(Prt2Xls){
				XlsKol=1;
				WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
				WriteVar2Xls(XlsRij,XlsKol++,fm_udat,(char *)u(6,150),StylDate);
				WriteVar2Xls(XlsRij,XlsKol++,fm_udat,(char *)u(6,151),StylDate);
				if(*f(6,153)) WriteFld2Xls(XlsRij,XlsKol++,6,153,StylNormal); else WriteVar2Xls(XlsRij,XlsKol++,fm_os1,"",StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,6,154,StylNormal);
			}
      first_=YES;
      for(k=0;k<10;k++){
				if(k>5 && fldlen(6,149)!=52) continue;
				if(is_pro(k)==NO){
					if(Prt2Xls) XlsKol+=5;
					continue;
				}
				copy(&vptekst[k*10],ptype_,6);
				if(k<6){
					pprx_=*f(6,155+k*5);
					pkrt_=*f(6,156+k*5);
					pkbd_=*f(6,157+k*5);
					pgrat_=*s(6,158+k*5);
				}
				else{
					pprx_=*(float *)(s(6,149)+(k-6)*13);
					pkrt_=*(float *)(s(6,149)+4+(k-6)*13);
					pkbd_=*(float *)(s(6,149)+8+(k-6)*13);
					pgrat_=*(s(6,149)+12+(k-6)*13);
				}
				if(pprx_) nprx_=pprx_; else nprx_=*f(6,PrNrs[k]);
				if(pkbd_) nprx_-=pkbd_;
				if(pkrt_){
					nprx_=(nprx_-*f(6,30))*(100-pkrt_)/100+*f(6,30);
				}
				nprx_=valu_cnv("EUR","EUR",(double)nprx_,(double)0.01);
				if(Prt2Xls){
					WriteFld2Xls(XlsRij,XlsKol++,6,21+k,StylNormal); 
					if(pprx_) WriteVar2Xls(XlsRij,XlsKol++,fm_of4_2,&pprx_,StylNormal); else WriteVar2Xls(XlsRij,XlsKol++,fm_os1,"",StylNormal);
					if(pkrt_) WriteVar2Xls(XlsRij,XlsKol++,fm_of4_2,&pkrt_,StylNormal); else WriteVar2Xls(XlsRij,XlsKol++,fm_os1,"",StylNormal);
					if(pkbd_) WriteVar2Xls(XlsRij,XlsKol++,fm_of4_2,&pkbd_,StylNormal); else WriteVar2Xls(XlsRij,XlsKol++,fm_os1,"",StylNormal);
					WriteVar2Xls(XlsRij,XlsKol++,fm_of4_2,&nprx_,StylNormal);
				}
				else{
					j=0; if(first_==NO) j=3;
					for(j;j<20;j++) prtinfo(j,0);nextline();
				}
				first_=NO;
      }
			if(Prt2Xls) XlsRij++;
    }
    fasgeti(6);
  }
	if(Prt2Xls) XlsClose(XlsRef,1);
  else prtclose();
  endsr:;
}

static is_pro(nr_)
int16 nr_;
{
	if(nr_<6){
    if(fldlen(6,155+nr_*5)==0 || *f(6,155+nr_*5)) return YES;
    if(fldlen(6,156+nr_*5)==0 || *f(6,156+nr_*5)) return YES;
    if(fldlen(6,157+nr_*5)==0 || *f(6,157+nr_*5)) return YES;
    if(fldlen(6,158+nr_*5)==0 || *s(6,158+nr_*5)=='J') return YES;
	}
	else{
		if(fldlen(6,149)!=52) return NO;
		if(*(float *)(s(6,149)+(nr_-6)*13)) return YES;
		if(*(float *)(s(6,149)+4+(nr_-6)*13)) return YES;
		if(*(float *)(s(6,149)+8+(nr_-6)*13)) return YES;
		if(*(s(6,149)+12+(nr_-6)*13)=='J') return YES;
	}
  return NO;
}
 
static initload()
{
									
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);

  sysget( 294,4,def_munt);
  sysget(1918,2,&sear_stt);
  sysget(3586,2,&sys3586);
  sysget(3588,2,&sys3588);
  sysget(3618,2,&sys3618);
  sysget(3632,2,&sys3632);
  sysget(3720,2,&sys3720);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  sysget(4670,6,stuksprx);
	sysget(4780,4,&stuksprx[6]);
 
  sysget(3678,2,&def_taal);
  dt_beg=*u(25,2);dt_end=dt_beg;
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
 
static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
}

static add_str(pd,len_,stu_,nr_,kar_)
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
 
static used(b,len)
char *b;
int16 len;
{
  while (len-->0)
    if(*b++!=0xFE) return YES;
  return NO;
}

static nextline()
{
  free=prtline();
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
//  if(DspTotRek==NO) parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}
