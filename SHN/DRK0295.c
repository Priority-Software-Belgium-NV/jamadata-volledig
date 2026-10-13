/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0295GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0295dat
#define ovlcod DRK0295cod
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

char ovldat[] = "drk0295  00:04 29/10/10 (c) Jamadata";
																																					/* beheer promoties kassa */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_REC         1000
#define DIM_PRTGRPR     200
#define MAX_MIXART      30
#define PROMO_PRX_FILE  "Folder.TXT"
#define PROMO_PRX_MAP   "..\\Div\\"
#define PROMO_BIBI_MAP  "PRIKTIK"

static char *fichenm[1]={"Promotie"};
static char *modenm[4]={"aan te passen","toe te voegen","te schrappen","te schrijven"};

extern int16 retcall,parmcall[8];
extern int16 ilength;
extern uint16 procid,onext;
extern char info[];
extern uint16 jamin1[5];


extern char *s();
extern int16 *i();
extern uint16 *u(),datejd();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();

static char *rec_ele(nr_);
static float get_num(nr);
static uint16 get_date(nr);

static char *p_data;
static long *pl_80_1;

static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us25[]  = {7,0xC8,25,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us10[]  = {7,0xC8,10,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os7[]   = {7,0x88,7,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x20,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static char fm_of4_2[] = {6,0x94,4,2,0x70,0};
static char fm_of3_1[] = {6,0x94,3,1,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_4[] = {6,0xD4,5,4,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf4_2[] = {6,0xD4,4,2,0x60,0};
static char fm_uf4_1[] = {6,0xD4,4,1,0x60,0};
static char fm_uf504[] = {6,0xD4,5,4,0x30,0};
static char fm_uf302[] = {6,0xD4,3,2,0x30,0};
static char fm_uf3_0[] = {6,0xD4,3,0,0x70,0};
static char fm_uf2_0[] = {6,0xD4,2,0,0x70,0};
static char fm_uf2_2[] = {6,0xD4,2,2,0x70,0};
static char fm_us10PW[] = {7,0xC8,10,0,4,0,0};
static char fm_uJN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uAT[]   = {11,0xC8,1,0,1,0,'A','A','T','T',0};
static char fm_u_BF[]   = {13,0xC8,1,0,1,0,'B','B','F','F',' ',' ',0};
static char fm_u_14[]   = {13,0xC8,1,0,1,0,'1','4',' ',' ',0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};

static int16 stu,groep,free,p_tb,tb_ktypes[6],max_kprx,ViaLijst;
static char nm_20[20],nm_15[15],oldnm[50],fmt[40],buf500[500],ScheidingsTeken='\x09',PrintArtikelPromo,PromoTekst[100],PromoEenheid[4];
static uint16 inq_klt,inq_art,inq_lev,inq_grp,dt_beg,dt_end,AantalPromoInFile,MaxPromoPerTicket,sys2978;
static char klt_str[101];
static char lev_res[60],klt_res[60],art_res[60],FTPUsername[15],FTPPaswoord[15];
static char sys3896[6];
static flag sear_stt,lvcd,klcd,chk_btoeg=NO,prt2pdf;
static flag sys3876,sys3894,kaart_used;
static int16 fld_nr[4]={6,22,7,8};
static int16 def_taal;
static long PrintedGroepsPromos[DIM_PRTGRPR];

static struct{
  uint16 rec;/* 0-19999 : artikel , 20000-65000 promo */
  uint16 type;
	long groepscode;
} tb[DIM_REC];
 

static struct{
	uint16 dt_beg;
	uint16 dt_end;
	char fcode[20];
	char fomschr[50];
	float prijs;
	float kassaprijs[6];
	char promotekst[50];
	char ean[20];
	char promocode;
} folderlijn;

static struct {
  uint16 dt_beg;
  uint16 dt_end;
  float kprx;
} tb_val[18];/* 18 lijnen (promo's) */
 
static struct{
	char Omschrijving[25];
	char Formule;
	char SelBakFles;
	float Getallen[4];
	char dummy[2]; // totaal 45 bytes
} PromoFormule[20];


static struct{
	char _begin;
	uint16 Rec93;
	uint16 DatBeg;
	uint16 DatEnd;
	uint16 BlokArtikel;
	long  MixGroepCode;
	char PromoText[20];
	uint16 ArtRec;
	char SelBakFles;
	uint16 MaxPromoPerTicket;
  char SelPromo[7];
	float VanafAantal;
	float kPCT;
	float kPCTAantal;
	float kEUR;
	float kEURAantal;
	float GratisAantal;
	float GratisArt;
	char GratisText[20];
	float KstafPct1;
	float KstafAantal2;
	float KstafPct2;
	uint16 MixVkpRec[MAX_MIXART]; // orig vkp records
	uint16 MixArtRec[MAX_MIXART]; 
	float VasteTotaalPrijs;
} PromoFiche;

ovlcod(parmval)
int16 parmval;
{
  int16 k,key,mode_,vialijst_=NO;
  char choice;

  initload();
  stu=93;
  for(k=0;k<4;k++) if(fldlen(93,fld_nr[k])==0) fld_nr[k]=0;
  copy(fichenm[0],nm_20,20);
  if(parmval==1){  // direct folderupdate Prik&Tik doen (opgeroepen vanuit ovl2291)
    add_via_file(YES);
    ovlexit(-1);
  }
  if(parmval==2){  // manueel promo toevogen vanuit andere ovl
    add_single(YES);
    ovlexit(-1);
  }
	if(parmval==3){
		if(*u(93,1)) mode_=1; else mode_=2;
		ViaLijst=YES;
		retcall=fichupd(mode_); // 0=annuleer, 1=OK, 10=OK + vorig, 11=OK+volgend
		ovlexit(-1);
	}

  FOREVER{
		redo:;
    scrget(3,1);fasunlck(0);scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0295A");
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_menu,&choice);
    key=scrupd(3,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) break;
    if(key==111) ovlexit(*u(25,4));
		fasunlck(-1);
    switch(choice){
      case '1':upd_mult();break;
      case '2':add_single(NO);break;
      case '3':kill();break;
      case '4':print();break;
			case '5':if(ovltest(2291)) ovlexit(2291); 
							 if(ovltest(2292)) ovlexit(2292);
							 else add_via_file(NO);break;
      case 'A':globkil();break;
      case 'F':UpdatePromoFormules();break;
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}

static sel_upd()
{
  int16 curs=1,key,z;
  char choice;
 
  copy(modenm[0],nm_15,15);
  FOREVER{
    scrget(3,2);
    z=1;
    scrifld(z++,fm_os20,nm_15);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0481);
    if(key==101) break;
    if(key==111) ovlexit(*u(25,4));
    switch(choice){
      case '1': upd_single();break;
      case '2': upd_mult();break;
      default : errnum=34; break;
    }
  }
}

static upd_single()
{
  int16 k,clr_=YES;
 
  FOREVER{
    redo:;
    if(select_promo(nm_20,modenm[0],0xFF,YES)) break;
    fasinit(93);
    *u(93,2)=*u(6,1);
    *u(93,3)=*u(1,1);
    *u(93,4)=groep;
    k=sear_promo();
    if(errnum || k==NO){clr_=NO; goto redo;}

    if(!fichupd(1)) break;
  }
}

static upd_mult()
{
	int clr_=YES;
  FOREVER{
    redo:
    if(select_promo("Kassa-promoties ",modenm[0],0xFF,clr_)) break;
		clr_=NO;
    scrget(1,7);scrupd(-3,0);
    if(fill_tabel(2)) {errnum=39;goto redo;}
    dsp_tabel(); inq_art=0;
  }
}
 
static fill_tabel(a_key_)
int16 a_key_;
{
  int16 j,k,n,len_;

  len_=sizeof tb[0];
  zeros((char *)&tb[0],sizeof tb);
  fasinit(93);*u(93,2)=1;p_tb=0;
  _fill_tab(1,0);
  fasinit(6);j=0;/* sorteren artikels */
  FOREVER{
    if(j>=p_tb-1) break;
    if(faskeyi(6,a_key_,2)) break;
    for(k=j;k<p_tb;k++){
      if(*u(6,1)==tb[k].type){
				if(k!=j){
					copy((char *)&tb[k],art_res,len_);
					for(n=k-1;n>=j;n--) copy((char *)&tb[n],(char *)&tb[n+1],len_);
					copy(art_res,(char *)&tb[j],len_);
				}
				j++;//break;
      }
    }
  }
  for(j=0;j<p_tb;j++) tb[j].type=0;/* terug juist zetten van type */
	for(j=0;j<p_tb;j++){
		if(tb[j].groepscode){
  		for(n=0;n<p_tb;n++) if(n!=j && tb[n].groepscode==tb[j].groepscode) break;
	  	if(n>=p_tb) tb[j].groepscode=0;
		}
	}
  fasinit(93);*u(93,3)=1;_fill_tab(2,1);/* lev. + groep */
  fasinit(93);*u(93,3)=1;_fill_tab(2,2);/* leverancier */
  fasinit(93);*u(93,3)=0;*u(93,4)=1;_fill_tab(2,3);/* groep */
  if(p_tb<1) return YES;
  else return NO;
}
 
static _fill_tab(keyno_,nr_)
int16 keyno_,nr_;
{
  int16 mode_=1;
  flag first=YES;
 
  for(p_tb;p_tb<DIM_REC;p_tb++){
    next:;
    if(faskeyi(93,keyno_,mode_)) break;mode_=2;
    if(nr_==3 && *u(93,3)!=0) break;
    if(dt_end && *u(93,7)>dt_end ) goto next;
    if(dt_beg && *u(93,8) && *u(93,8)<dt_beg) goto next;
		if(inq_art && *u(93,2)!=inq_art) goto next;
		if(nr_==0){ // bij artikels groep en leverancier gebruiken als selectie
			if((inq_lev || groep) && *u(93,2)){
				fasinit(6);*u(6,1)=*u(93,2);fasgeti(6);
  		  if(inq_lev && *u(6,7)!=inq_lev) goto next;
	  	  if(groep && *u(6,9)!=groep) goto next;
			}
		}
		else{
  		if(inq_lev && *u(93,3)!=inq_lev) goto next;
	  	if(groep && *u(93,4)!=groep) goto next;
		}
    if(nr_==1 && *u(93,4)==0) goto next;
    if(nr_==2 && *u(93,4)!=0) goto next;
    if(nr_ && first){
      tb[p_tb].rec=0xFFFF;tb[p_tb].type=nr_;p_tb++;
      first=NO;
    }
    tb[p_tb].rec=*u(93,1)+20000;
		if(fldlen(93,45)) tb[p_tb].groepscode=*l(93,45);
    if(nr_>0) tb[p_tb].type=nr_;
    else tb[p_tb].type=*u(93,2);/* tydelijk rec. invullen voor sort */
  }
}

static dsp_tabel()
{
  int16 k,n,pos_,key,z,start=0,curs=1,o_start,yy,dd,mm,curspos_;
					
  n=copy0("Kassa-promoties ",klt_str,30);

  if(dt_beg){
    jddate(dt_beg,&yy,&mm,&dd);
    stcli_d(&klt_str[n],(long)dd,2,0);n+=2;klt_str[n++]='/';
    stcli_d(&klt_str[n],(long)mm,2,0);n+=2;klt_str[n++]='/';
    stcli_d(&klt_str[n],(long)yy,4,0);n+=4;
  }
  else {copy("  /  /    ",&klt_str[n],10); n+=10;}
  copy(" t.e.m. ",&klt_str[n],8);n+=8;
  if(dt_end){
    jddate(dt_end,&yy,&mm,&dd);
    stcli_d(&klt_str[n],(long)dd,2,0);n+=2;klt_str[n++]='/';
    stcli_d(&klt_str[n],(long)mm,2,0);n+=2;klt_str[n++]='/';
    stcli_d(&klt_str[n],(long)yy,4,0);n+=4;
  }
  else copy("  /  /    ",&klt_str[n],10);

  ld_tb_val(0,p_tb);
  FOREVER{
redo:;
		if(p_tb==0) break;
    scrnum=0;scrget(3,3);z=1;
    scrifld(z++,fm_os63,klt_str);
    for(k=start;k<p_tb;k++){
      dsp_1_lin(z,k,start,0);z+=4;
      if(k==start+17) break;
    }
    key=scrupd(curs,0xA7);curs=1;curspos_=fldcurs;
    if(key==106) ld_tb_val(start,p_tb);
    for(n=start;n<k;n++){
      if(tb_val[n-start].dt_beg==0 && tb_val[n-start].dt_end){
	errnum=39;curs=3+(n-start)*4; goto redo;
      }
    }
    if(key==101) {wr_tb_val(start,p_tb);break;}
	if(key==108){
		wr_tb_val(start,p_tb);
		curs=curspos_;
		pos_=(curspos_-2)/4;
		if(tb[start+pos_].rec && tb[start+pos_].rec!=0xFFFF){
			fasinit(93);*u(93,1)=tb[start+pos_].rec-20000;fasgeti(93);
			*u(93,7)=tb_val[pos_].dt_beg;
			*u(93,8)=tb_val[pos_].dt_end;
			*f(93,11)=tb_val[pos_].kprx;
			fichupd(1);
			fill_tabel(2);
			if(start>=p_tb-18) start=p_tb-18;
			if(start<0) start=0;
			ld_tb_val(start,p_tb);

			/*tb_val[pos_].dt_beg=*u(93,7);
			tb_val[pos_].dt_end=*u(93,8);
			tb_val[pos_].kprx=*f(93,11);*/
		}
	}
	o_start=start;
    if(key==102) start-=18;
    if(key==103) {start+=18;if(start>=p_tb-18) start=p_tb-18;}
    if(start<0) start=0;
    if(o_start!=start) {wr_tb_val(o_start,p_tb);ld_tb_val(start,p_tb);}
  }
  return NO;
}

static ld_tb_val(rpos,max_)
int16 rpos,max_;
{
  int16 k;
 
  zeros((char *)tb_val,sizeof tb_val);
  for(k=0;k<18;k++){
    if((rpos+k)>=max_) break;
    if(tb[rpos+k].rec!=0xFFFF && tb[rpos+k].rec>20000){
      fasinit(93);*u(93,1)=tb[rpos+k].rec-20000;fasgeti(93);
      tb_val[k].dt_beg=*u(93,7);
      tb_val[k].dt_end=*u(93,8);
      tb_val[k].kprx=*f(93,11);
    }
  }
}
 
static dsp_1_lin(z,j,start,mode_)/* mode_=1 : enkel string samenstellen */
int16 z,j,start,mode_;
{
  char *pd;
	
  fasinit(93);pd=&oldnm[0];
  if(tb[j].rec!=0xFFFF) {
    *u(93,1)=tb[j].rec-20000;fasgeti(93);
    switch(tb[j].type){
      case 0 : fasinit(6);*u(6,1)=*u(93,2);fasgeti(6);
	       pd+=add_str(pd,10,6,2,' ');pd+=add_str(pd,30,6,3,'\0');
	       break;
      case 1 : fasinit(1);*u(1,1)=*u(93,3);fasgeti(1);
	       fasinit(52);*u(52,1)=*u(93,4);fasgeti(52);
	       pd+=add_str(pd,20,1,3,'-');
	       stcli_d(pd,(long)*u(52,1),2,0);pd+=2;*(pd++)=' ';
	       pd+=add_str(pd,15,52,14,'\0');
	       break;
      case 2 : fasinit(1);*u(1,1)=*u(93,3);fasgeti(1);
	       pd+=add_str(pd,40,1,3,'\0');
	       break;
      default: fasinit(52);*u(52,1)=*u(93,4);fasgeti(52);
	       stcli_d(pd,(long)*u(52,1),2,0);pd+=2;*(pd++)=' ';
	       pd+=add_str(pd,15,52,14,'\0');
	       break;
    }
    if(mode_) goto endsr;
    scrifld(z,fm_os40,oldnm);
		if(tb[j].type==0 && fldlen(93,45) && tb[j].groepscode) scrchat(z,0x9);
		else if(fldlen(93,10) && *u(93,10)) scrchat(z,0xB);
    else if(tb_val[j-start].dt_beg) scrchat(z,0x2); 
		else scrchat(z,0xFF); 
		z++;
		if(!(tb[j].type==0 && fldlen(93,45) && tb[j].groepscode)){
			scrifld(z++,fm_udat,&tb_val[j-start].dt_beg);
			scrifld(z++,fm_udat,&tb_val[j-start].dt_end);
			scrifld(z++,fm_uf6_2,&tb_val[j-start].kprx);
		}
		else{
			scrifld(z++,fm_udat,&tb_val[j-start].dt_beg);
			scrifld(z++,fm_odat,&tb_val[j-start].dt_end);
			scrifld(z++,fm_of6_2,&tb_val[j-start].kprx);
		}
  }
  else {
    switch(tb[j].type){
      case 1 : scrifld(z,fm_os40,"Leverancier + groep");break;
      case 2 : scrifld(z,fm_os40,"Leverancier");break;
      case 3 : scrifld(z,fm_os40,"Groep");break;
      default: scrifld(z,fm_os40,"Algemene korting");break;
    }
    scrchat(z++,0x8);
    z+=4;
  }
  endsr:;
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

static add_single(single_add_)
int single_add_;
{
  FOREVER{
    fasinit(1);fasinit(6);fasinit(52); 
		if(single_add_==NO){fasinit(93); *u(93,7)=dt_beg; *u(93,8)=dt_end;}
    if(!fichupd(2)) break;/* fasadd */
		if(single_add_) break; // vanuit andere ovl
    dt_beg=*u(93,7);dt_end=*u(93,8);
  }
}

static wr_tb_val(rpos,max_)
int16 rpos,max_;
{
  int16 k;
 
	fasunlck(-2);
  for(k=0;k<18;k++){
    if((rpos+k)>=max_) break;
    fasinit(93);
    if(tb[rpos+k].rec!=0xFFFF && tb[rpos+k].rec >20000 && !(tb[rpos+k].type==0 && fldlen(93,45) && tb[rpos+k].groepscode)) { // niet bij mixed promo's
      *u(93,1)=tb[rpos+k].rec-20000;fasgetu(93);
      *u(93,7)=tb_val[k].dt_beg;
      *u(93,8)=tb_val[k].dt_end;
      *f(93,11)=tb_val[k].kprx;
      if(*u(93,7)) fasupd(93);
      else faskill(93);
    }
  }
	fasunlck(-1);
}
 
static kill()
{
  int16 k,clr_=YES;

  FOREVER{
    redo:
    if(select_promo(nm_20,modenm[2],0xF,clr_)) break;
    fasinit(93);
    *u(93,2)=*u(6,1);
    *u(93,3)=*u(1,1);
    *u(93,4)=groep;
    k=sear_promo();
    if(errnum || k==NO){clr_=NO;goto redo;}
    else clr_=YES;
 
    if(!fichkil()) break;
  }
}

static globkil()
{
  int16 g,key;
  uint16 n;

  dt_beg=0;dt_end=0;
  FOREVER{
    redo:
    scrget(3,4);
    scrifld(1,fm_udat,&dt_beg); scrifld(2,fm_udat,&dt_end);
    key=scrupd(1,0x19);
    if(key==101 || key==105) goto endsr;
    if(dt_beg==0) {errnum=38;goto redo;}
    if(dt_end==0) {errnum=38; goto redo;}
    if(key==104) break;
  }
  scrget(1,7);scrupd(-3,0);
  fasinit(93);
	fasunlck(-2);
  n=0;scrnum=0;
  FOREVER{
    next:;
    *u(93,1)=++n;
    g=fasgeti(93);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
      if(dt_beg>*u(93,7)) goto next;
      if(*u(93,8)==0 || *u(93,8)>dt_end) goto next;
      faskill(93);
    }
  }
	fasunlck(-1);
  endsr:;
}

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
}
 
static select_promo(p_sel,p_mode,sel_,clr_)
char *p_sel,*p_mode,sel_;
int16 clr_;
{
  int16 key,z,curs=4;
 
  if(clr_){
    fasinit(6);fasinit(1); fasinit(52);
    zeros(art_res,sizeof art_res);
    zeros(klt_res,sizeof klt_res);
    groep=0;
  }
	else{
		fasinit(6);fasinit(1); fasinit(52);
		if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
		if(inq_lev){*u(1,1)=inq_lev;fasgeti(1);}
	}
  FOREVER{
    redo:
    scrget(3,5);z=1;
    scrifld(z++,fm_os38,p_sel);
    scrfld(z++,25,1);
    scrifld(z++,fm_os15,p_mode);
		if(sel_ & 0x2) {scrfld(z++,6,3);scraddpicto(6,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken");} else streepje(z++);
		if(sel_ & 0x4) {scrfld(z++,1,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken");} else streepje(z++);
		if(sel_ & 0x8) {scrifld(z++,fm_uu2,&groep);scraddpicto(9,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken");} else streepje(z++);
    scrifld(z++,fm_udat,&dt_beg); scrifld(z++,fm_udat,&dt_end);
    key=scrupd(curs,0x0481);curs=4;
    if(key==101) return YES;
    if(key==111) ovlexit(*u(25,4));
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5006){
			if(search(6,98)) {curs=4;goto redo;}
      copy(s(6,3),art_res,fldlen(6,3));
		}
    if(cmp_str(s(6,3),art_res,fldlen(6,3))){
      if(*s(6,3)){
				if(search(6,0)) {curs=4;goto redo;}
				copy(s(6,3),art_res,fldlen(6,3));
      }
      else fasinit(6);
    }
		if(key==5001){
			if(search(1,98)) {curs=5;goto redo;}
  	}
    if(*s(1,3)){
      if(search(1,0)) {curs=5;goto redo;}
    }
    else fasinit(1);
		if(key==5009){
			fasinit(52);*u(52,1)=groep;
			if(search(52,98)) {curs=6;goto redo;}
			groep=*u(52,1);
  	}
		inq_lev=*u(1,1);inq_art=*u(6,1);
    if(key==108) break;
  }
  return NO;
}

static fichkil()
{
  int16 key,z;


  fasinit(6);*u(6,1)=*u(93,2);fasgeti(6);
  fasinit(1);*u(1,1)=*u(93,3);fasgeti(1);

  redo:
  scrget(3,6);z=1;
  scrifld(z++,fm_os20,fichenm[0]);
  scrfld(z++,25,1);
  scrofld(z++,6,3,-1);
  scrofld(z++,1,3,-1);
  scrofld(z++,93,4,-1);
  scrofld(z++,93,7,-1);scrofld(z++,93,8,-1);
  key=scrupd(0xFFFF,0x419);
  if(key==111) ovlexit(*u(25,4));
  if(key==101) return NO;
  if(key!=104 && key!=105) {errnum=21;goto redo;}
  if(key==104) faskill(93);
  return YES;
}

static print()
{
  int16 form_dat[8],prmode,k,prtnr,z,mode_;
  char str_[15];
  uint16 rec_;
 
  if(!get_selectie(YES)) goto endsr;
	zero((char *)&PrintedGroepsPromos[0],sizeof PrintedGroepsPromos);

  getsysprNew(5,form_dat,&prmode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,prmode,4))!=0) goto endsr;
  fmt_get(6,21);
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t40eb>"); prttext("Promoties kassa");
  prttext("<eb>");
  prttext("<t95>"); prtifld(fm_odat,u(25,2),-1); prttext("<t120>");prttext("Blz.<ppp>.");
  prtbuf(1);
  z=1;
  prttab(z,93,7,1,-1); prttitle(z++,"Van",0x13);
  prttab(z,93,8,1,-1); prttitle(z++,"Tot",0x13);
  prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,1,30); prttitle(z++,"Artikel",3);
	if(PrintArtikelPromo=='J'){
		prttab(z,93,11,1,-1);prttitle(z++,"Pr.Kassa",0x13);
		if(fldlen(93,41)){prtitab(z,fm_uu2,&MaxPromoPerTicket,1,-1); prttitle(z++,"Mx",0x13);}
		prtitab(z,fm_os3,PromoEenheid,1,-1); prttitle(z++,"Eh",3);
		prtitab(z,fm_os40,PromoTekst,1,-1); prttitle(z++,"Promotie",3);
	}
	else{
		if(kaart_used){
			prttab(z,1,3,2,10); prttitle(z++,"Leverancier",3);
			prttab(z,52,14,1,10); prttitle(z++,"Groep",3);
			prttab(z,93,20,1,-1); prttitle(z++,"T",3);
			prttab(z,93,21,1,-1); prttitle(z++,"Bak wrd",0x13);
			prttab(z,93,22,1,-1); prttitle(z++,"T",3);
			prttab(z,93,23,1,-1); prttitle(z++,"Stk wrd",0x13);
			prttab(z,93,26,1,-1); prttitle(z++,"PF",3);
			prttab(z,93,25,1,-1); prttitle(z++,"P",3);
		}
		else{
			for(k=0;k<max_kprx;k++){
				prttab(z,93,11+k,1,-1);
				if(k==0) prttitle(z++,"Kassa bak",0x13);
				else if(k==max_kprx-1) prttitle(z++,"Kassa stuk",0x13);
				else {copy("Horeca",str_,6);stcli_d(&str_[6],(long)k,2,1);prttitle(z++,str_,0x13);}
			}
			prttab(z,93,26,1,-1); prttitle(z++,"PF",3);
			prttab(z,93,25,1,-1); prttitle(z++,"F",3);
		}
	}
  prttab(z,93,30,1,-1); prttitle(z++,"Promo tekst",3);
  prtbuf(3);
	p_pdfname("Kassa-promoties",dt_beg,dt_end);
  free=999;
  if(inq_lev==0 && inq_grp==0){/* eerst artikels alfabetisch */
    fasinit(6);rec_=inq_art;
    mode_=1;
    FOREVER{
      fasinit(6);*u(6,1)=rec_;if(rec_) fasgeti(6);
      if(faskeyi(6,2,mode_)) break; mode_=2;
      rec_=*u(6,1);
      if(inq_art && *u(6,1)!=inq_art) break;
      p_93_det(rec_);
    }
  }
  if(inq_art==0 && PrintArtikelPromo!='J') p_93_det(0);/* groepen en leveranciers */
  prtclose();
  endsr:;
}

static p_93_det(rec_)
uint16 rec_;
{
  int16 k,mode_,mode1_,fkey_,p_used_;
	uint16 rec93_;
	long groepscode_;
  char str_[30];
 
  fasinit(93);*u(93,2)=rec_;
  if(rec_) fkey_=1; else fkey_=2; mode_=1;
  FOREVER{
    next:;
    if(faskeyi(93,fkey_,mode_)) break; mode_=2;
    if(fkey_==1){
      if(rec_!=*u(93,2)) break;
    }
    else{
      if(inq_lev && *u(93,3)!=inq_lev) break;
      if(*u(93,2)) goto next;/* geen artikels hier */
      if(inq_grp && *u(93,4)!=inq_grp)  goto next;
    }
    if(dt_end && *u(93,7)>dt_end ) goto next;
    if(dt_beg && *u(93,8) && *u(93,8)<dt_beg) goto next;
		if(fldlen(93,45) && *l(93,45) && PrintArtikelPromo=='J'){
			for(k=0;k<DIM_PRTGRPR;k++) if(PrintedGroepsPromos[k]==*l(93,45) || PrintedGroepsPromos[k]==0) break;
			if(k<DIM_PRTGRPR && PrintedGroepsPromos[k]==0) PrintedGroepsPromos[k]=*l(93,45);
			else goto next;
		}
    fasinit(6); *u(6,1)=*u(93,2); fasgeti(6);
    fasinit(52);*u(52,1)=*u(93,4);fasgeti(52);
    fasinit(1);*u(1,1)=*u(93,3);fasgeti(1);
		if(PrintArtikelPromo=='J'){
			zero(PromoEenheid,sizeof PromoEenheid);if(*s(93,34)=='F') copy("FLS",PromoEenheid,3); else copy("BAK",PromoEenheid,3);
			if(fldlen(93,41)) MaxPromoPerTicket=*u(93,41); else MaxPromoPerTicket=0;
			zero(PromoTekst,sizeof PromoTekst);
			switch(*u(93,35)){
				case 5: sprintf_s(PromoTekst,100,"Bij %.0f St, dan %.0f%% korting op %.0f St",*f(93,36),*f(93,37),*f(93,38)); break;
				case 6: sprintf_s(PromoTekst,100,"Bij %.0f St, dan %.2f EUR korting op %.0f St",*f(93,36),*f(93,37),*f(93,38)); break;
				case 7: sprintf_s(PromoTekst,100,"Bij %.0f St, dan %.0f St gratis",*f(93,36),*f(93,37)); break;
				case 8: fasinit(6);*u(6,1)=*f(93,37); fasgeti(6);
								 sprintf_s(PromoTekst,100,"Bij %.0f St gratis %s",*f(93,36),s(6,3)); 
								 fasinit(6); *u(6,1)=*u(93,2); fasgeti(6);
								 break;
				case 9: zero(str_,sizeof str_); copy(s(93,40),str_,fldlen(93,40));
					      sprintf_s(PromoTekst,100,"Bij %.0f St gratis %s",*f(93,36),str_); 
								break;
				case 10: sprintf_s(PromoTekst,100,"Bij %.0f St %.0f%% korting, vanaf %.0f St %.0f%% korting",*f(93,36),*f(93,37),*f(93,38),*f(93,39)); break;
				case 11: sprintf_s(PromoTekst,100,"%.0f St voor %.2f EUR",*f(93,36),*f(93,37)); break;
				default: break;
			}
			if(PromoTekst[0]=='\0'){
				for(k=0;k<6;k++) if(*f(93,11+k)) {copy("Promo-prijs",PromoTekst,20);break;}
			}
			for(k=0;k<20;k++) prtinfo(k,0);nextline();
		}
		else{
			for(k=0;k<20;k++) prtinfo(k,0);nextline();
			if(kaart_used){
				p_used_=NO;
				for(k=0;k<max_kprx;k++){
					if(*f(93,11+k)){
						if(p_used_==NO) prttext("     --> Promotieprijzen : ");
						if(k==0) prttext("Kassa bak : ");
						else if(k==max_kprx-1) prttext("  Kassa stuk :");
						else {copy("  Horeca",str_,8);stcli_d(&str_[8],(long)k,2,1);prttext(str_);}
						prtfld(93,11+k,-1);
						p_used_=YES;
					}
				}
				if(p_used_) nextline();
			}
		}
		if(fldlen(93,35) && *l(93,45) && PrintArtikelPromo=='J'){ // mixed artikels afdrukken
			groepscode_=*l(93,45);rec93_=*u(93,1);
			fasinit(93);*l(93,45)=groepscode_; mode1_=1;
			FOREVER{
				next1:;
				if(faskeyi(93,5,mode1_)) break; mode1_=2;
				if(*l(93,45)!=groepscode_) break;
				if(*u(93,1)==rec93_) goto next1;
				if(dt_end && *u(93,7)>dt_end ) goto next1;
				if(dt_beg && *u(93,8) && *u(93,8)<dt_beg) goto next1;
				fasinit(6); *u(6,1)=*u(93,2); fasgeti(6);
				for(k=3;k<5;k++) prtinfo(k,0);nextline();
			}
			fasinit(93);*u(93,1)=rec93_; fasgeti(93);
		}
  }
}

static int16 SelectPromoFormule()
{
  int16 k,z,key,start;
	uint16 nr_=0;


	start=0;
	FOREVER{
		redo:;
		scrget(3,15); z=1;
		for(k=start;k<start+17;k++){
			k++; scrifld(z++,fm_ou2,&k); k--;
			scrifld(z++,VarTextFmt(25,0),PromoFormule[k].Omschrijving);
		}
		nr_=0; scrifld(35,fm_uu2,&nr_);
		key=scrupd(1,0xA7);
		if(key==101 || key==106) return 0;
		if(key==102){start=0; goto redo;}
		if(key==103){start=3;	goto redo;}
		if(nr_<1 || nr_>20 || PromoFormule[nr_-1].Omschrijving[0]=='\0') errnum=39;
		else break;
	}
	return nr_;
  endsr:;
}



static UpdatePromoFormules()
{
  int16 j,k,curs,z,key,curspos_,start;


	for(k=0;k<10;k++) sysget(20500+k*45,45,&PromoFormule[k].Omschrijving[0]);
	curs=1; start=0;
	FOREVER{
		redo:;
		scrnum=0; scrget(3,13);z=1; 
		for(k=start;k<start+10;k++){
			k++; scrifld(z++,fm_ou2,&k); k--;
			scrifld(z++,fm_us25,PromoFormule[k].Omschrijving);
			scrifld(z++,fm_u_14,&PromoFormule[k].Formule);
			scrifld(z++,fm_u_BF,&PromoFormule[k].SelBakFles);
			for(j=0;j<4;j++) scrifld(z++,fm_uf4_1,&PromoFormule[k].Getallen[j]);
		}
		key=scrupd(curs,0xA6);curs=1;curspos_=fldcurs;
  	if(key==106) goto endsr;
		for(k=start;k<start+10;k++){
			if(PromoFormule[k].Omschrijving[0] && (PromoFormule[k].Formule<'1' || PromoFormule[k].Formule>'4')) {errnum=38;curs=(k-start)*8+3; goto redo;}
			if(PromoFormule[k].Formule=='1'){ // korting%
				if(PromoFormule[k].Getallen[1]==0) {errnum=38;curs=(k-start)*8+6; goto redo;}
				if(PromoFormule[k].Getallen[2] && PromoFormule[k].Getallen[2]<=PromoFormule[k].Getallen[0]) {errnum=77;curs=(k-start)*8+7; goto redo;}
			}
			if(PromoFormule[k].Formule=='2'){ // korting EUR
				if(PromoFormule[k].Getallen[1]==0) {errnum=38;curs=(k-start)*8+6; goto redo;}
				if(PromoFormule[k].Getallen[2] && PromoFormule[k].Getallen[2]<=PromoFormule[k].Getallen[0]) {errnum=77;curs=(k-start)*8+7; goto redo;}
			}
			if(PromoFormule[k].Formule=='3'){ // aantal gratis	
				if(PromoFormule[k].Getallen[0]==0) {errnum=38;curs=(k-start)*8+5; goto redo;}
				if(PromoFormule[k].Getallen[1]==0) {errnum=77;curs=(k-start)*8+6; goto redo;}
			}
			if(PromoFormule[k].Formule=='4'){ // aantal met korting 
				if(PromoFormule[k].Getallen[0]==0) {errnum=38;curs=(k-start)*8+5; goto redo;}
				if(PromoFormule[k].Getallen[1]==0) {errnum=77;curs=(k-start)*8+6; goto redo;}
				if(PromoFormule[k].Getallen[1]==0) {errnum=77;curs=(k-start)*8+7; goto redo;}
			}
		}

    if(key==108){
			for(k=0;k<10;k++) sysput(20500+k*45,45,&PromoFormule[k].Omschrijving[0]);
			break;
		}
		//if(key==102) start=0; 
		//if(key==103) start=5;
  }
	for(k=0;k<10;k++) sysget(20500+k*45,45,&PromoFormule[k].Omschrijving[0]);
  endsr:;
}

static get_selectie(mode_)
flag mode_;
{
  int16 z,curs,key;

  fasinit(1); fasinit(6); fasinit(93);
  art_res[0]='\0';klt_res[0]='\0';lev_res[0]='\0';
	if(PrintArtikelPromo=='\0') {
		if(fldlen(93,35)) PrintArtikelPromo='J';
		else PrintArtikelPromo='N';
	}
  if(inq_lev) {*u(1,1)=inq_lev; fasgeti(1);}
  if(inq_art) {*u(6,1)=inq_art; fasgeti(6);}
  curs=1;
  FOREVER{
    redo:
    scrget(3,7); z=1;
		if(mode_) {scrifld(z++,fm_os9,"Afdrukken");scraddpicto(1,0,76,22,4,2,583,0,0,"PDF");}
    else scrifld(z++,fm_os9,"Aanpassen");
    scrfld(z++,25,1);
    scrfld(z++,6,3);
    scrfld(z++,6,9);
    scrfld(z++,1,3);
    scrifld(z++,fm_udat,&dt_beg); scrifld(z++,fm_udat,&dt_end);
		if(fldlen(93,35) && mode_) scrifld(z++,fm_uJN,&PrintArtikelPromo); else z++;
    key=scrupd(curs,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		prt2pdf=NO; if(key==5001){prt2pdf=YES;key=108;}
    if((key==101)&&(!errnum)) break;
    else if(key==111) ovlexit(*u(25,4));
    else{
      if(fldlen(6,9)) inq_grp=*i(6,9);
      if(cmp_str(s(1,3),lev_res,fldlen(1,3))){
	if(*s(1,3)){
	  if(search(1,0)) {curs=6; goto redo;}
	  copy(s(1,3),lev_res,fldlen(1,3));
	}
	else *u(1,1)=0;
      }
      if(cmp_str(s(6,3),art_res,fldlen(6,3))){
	if(*s(6,3)){
	  if(search(6,0)) {curs=3; goto redo;}
	  copy(s(6,3),art_res,fldlen(6,3));
	}
	else *u(6,1)=0;
      }
      inq_lev=*u(1,1); inq_klt=*u(2,1); inq_art=*u(6,1);
      if(key==108) return YES;
    }
  }
  return NO;
}

static initload()
{
  int16 k,nr_;
 
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(11);

  sysget(1918,2,&sear_stt);
	sysget(2978,2,&sys2978);
	sysget(3004,10,FTPUsername);
	sysget(3014,10,FTPPaswoord);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,sys3896);
	for(k=0;k<10;k++) sysget(20500+k*45,45,&PromoFormule[k].Omschrijving[0]);

	if(FTPUsername[0]=='\0' && FTPPaswoord[0]=='\0'){//serial en PW uit jms.ini nemen
    ExecJmsCommand(FTPUsername,sizeof FTPUsername,"GetIniKeyValue|JamaSettings|SerialNr");
    ExecJmsCommand(FTPPaswoord,sizeof FTPPaswoord,"GetIniKeyValue|JamaSettings|Password");
	}

  zero((char *)&tb_ktypes[0],sizeof tb_ktypes); max_kprx=0;
  for(k=0;k<6;k++){
    if(sys3896[k]){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
	tb_ktypes[max_kprx++]=nr_;
      }
    }
  }
  sysget(3678,2,&def_taal);
  kaart_used=NO; if(ovltest(294)) kaart_used=YES;
}

static fileopen(nr_)
int16 nr_;
{
  int16 stu_;
  char filename[15];

  nr_--;
  sysget(300+17*nr_,15,filename);
  sysget(315+17*nr_,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(errnum=fasopen(filename,0)) ovlexit(-1);
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  }
}

static fichupd(mode)
int16 mode;
{
  int16 curs,j,k,key,z,pr_offset_,vpos_,pfm_,multiart_,z_promo_,z_formule_,mode_,act_jj_,act_mm_,act_dd_,act_uur_,act_min_,act_sec_,fl_newpromo_;
	int16 dsp_items[7]={25,30,20,21,22,23,31};
	uint16 rec_;
  float nm_vp[6],ap_,vp_,wpct_;
  char str_[10],buf500_[500],nm_formule[30],nm_gr_art_[50],nm_art_[50];
 
	if(fldlen(93,35)==0) {return fichupdOLD(mode);}

  zero(&PromoFiche._begin,sizeof PromoFiche);zero(nm_gr_art_,sizeof nm_gr_art_);zero(nm_art_,sizeof nm_art_);
	PromoFiche.Rec93=*u(93,1);
	PromoFiche.DatBeg=*u(93,7);
	PromoFiche.DatEnd=*u(93,8);
	PromoFiche.MaxPromoPerTicket=*u(93,41);
	if(fldlen(93,10)) PromoFiche.BlokArtikel=*u(93,10);
	if(mode==2){
		if(PromoFiche.VanafAantal==0) PromoFiche.VanafAantal=1;
		if(PromoFiche.SelBakFles=='\0') PromoFiche.SelBakFles='B';
	}
	multiart_=NO;fl_newpromo_=NO;
	if(fldlen(93,45) && *l(93,45)){ // mixed promo's laden
		PromoFiche.MixGroepCode=*l(93,45);
		
		fasinit(93);*u(93,7)=PromoFiche.DatBeg; *l(93,45)=PromoFiche.MixGroepCode;mode_=1; j=0;
		for(k=0;k<MAX_MIXART;k++){
			if(faskeyi(93,5,mode_)) break; mode_=2;
			if(*l(93,45)!=PromoFiche.MixGroepCode) break;
			if(*u(93,7)!=PromoFiche.DatBeg) break;
			if(*u(93,1)!=PromoFiche.Rec93){
				PromoFiche.MixVkpRec[j]=*u(93,1); PromoFiche.MixArtRec[j]=*u(93,2);
				j++; multiart_=YES;
			}
		}
		fasinit(93);*u(93,1)=PromoFiche.Rec93; fasgeti(93);
	}
	copy(s(93,30),PromoFiche.PromoText,20);
	if(mode!=2) {PromoFiche.SelBakFles=*s(93,34);PromoFiche.MaxPromoPerTicket=*u(93,41);}
	pfm_=*u(93,35); 
	switch(pfm_){
	  case 5 : PromoFiche.SelPromo[pfm_-5]='J'; PromoFiche.VanafAantal=*f(93,36); PromoFiche.kPCT=*f(93,37); PromoFiche.kPCTAantal=*f(93,38); break;
	  case 6 : PromoFiche.SelPromo[pfm_-5]='J';PromoFiche.VanafAantal=*f(93,36); PromoFiche.kEUR=*f(93,37); PromoFiche.kEURAantal=*f(93,38); break;
	  case 7 : PromoFiche.SelPromo[pfm_-5]='J';PromoFiche.VanafAantal=*f(93,36); PromoFiche.GratisAantal=*f(93,37); break;
	  case 8 : PromoFiche.SelPromo[pfm_-5]='J';PromoFiche.VanafAantal=*f(93,36); PromoFiche.GratisArt=*f(93,37); 
			       fasinit(6);*u(6,1)=PromoFiche.GratisArt; if(*u(6,1)) fasgeti(6); copy(s(6,3),nm_gr_art_,fldlen(6,3)); 
						 break;
	  case 9 : PromoFiche.SelPromo[pfm_-5]='J';PromoFiche.VanafAantal=*f(93,36); copy(s(93,40),PromoFiche.GratisText,20); break;
	  case 10 : PromoFiche.SelPromo[pfm_-5]='J'; PromoFiche.VanafAantal=*f(93,36); PromoFiche.KstafPct1=*f(93,37); PromoFiche.KstafAantal2=*f(93,38); PromoFiche.KstafPct2=*f(93,39); break;
	  case 11 : PromoFiche.SelPromo[pfm_-5]='J';PromoFiche.VanafAantal=*f(93,36); PromoFiche.VasteTotaalPrijs=*f(93,37);break;
	  default: break;
	}

  errnum=0;
  if(mode==1) curs=6; else curs=1;
  fasinit(6);*u(6,1)=*u(93,2);fasgeti(6); copy(s(6,3),nm_art_,fldlen(6,3));PromoFiche.ArtRec=*u(6,1);
	zeros((char *)&nm_vp[0],sizeof nm_vp);  pr_offset_=0; vpos_=0;
	if(fldlen(6,105) && *u(6,105)){
		if(*u(6,105)<=*u(25,2) || *u(6,105)<=*u(93,7)){ pr_offset_=94; vpos_=10;}
	}
	ap_=*f(6,18+pr_offset_)*=1.+ *f(6,28)/100.; // AK-prijs incl BTW om gemakkelijker W% te berekenen
  for(k=0;k<max_kprx;k++){
    nm_vp[k]=*f(6,PrNrs[tb_ktypes[k]+vpos_]);
    if(!(sys3894 & (1<<(tb_ktypes[k])))) nm_vp[k]*=1.+ *f(6,28)/100.;
    if(nm_vp[k]!=*f(6,PrNrs[tb_ktypes[k]+vpos_])) nm_vp[k]=valu_cnv("EUR","EUR",(double)nm_vp[k],(double)0.01);
  }
	//if(fldlen(93,26)){
 // 	zero(nm_formule,sizeof nm_formule);
 // 	if(*u(93,26)>=1 && *u(93,26)<=20) copy(PromoFormule[*u(93,26)-1].Omschrijving,nm_formule,25);
	//}
  fasinit(1);*u(1,1)=*u(93,3);fasgeti(1);
  fasinit(52); if(*u(93,4)){*u(52,1)=*u(93,4);fasgeti(52);}
  FOREVER{
    copy(s(6,3),art_res,fldlen(6,3));
redo:
    if(PromoFiche.BlokArtikel) ConLook(1); else   ConLook(0);
    scrnum=0;scrget(3,16);z=1;
		if(ViaLijst){
			scraddpicto(2,0,75,1,4,2,93,0,4,"Vorige promotie");
			scraddpicto(3,0,75,20,4,2,92,0,4,"Volgende promotie");
			DisplayMenuTitel(11,GlobalTextBuffer,0xA);
		}
		else if(mode==1){
			scraddpicto(5,0,75,1,4,2,133,0,3,"Schrap promotie");
		}

 //   scrfld(z++,25,1);
    scrfld(z++,93,7); scrfld(z++,93,8);
//   if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    fmt_get(6,3); scrifld(z++,fmt,nm_art_);scraddpicto(6,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken");


  	if(fldlen(93,45) && PromoFiche.BlokArtikel==NO ){
			if(multiart_) {scrchat(z-1,0x9);scraddpicto(4,0,60,15,7,3,69,0,4,"Gelijkaardige artikels");} // er zijn gelijkaardige artikels 
			else {scrchat(z-1,0xFF);scraddpicto(4,0,60,15,7,3,69,0,3,"Gelijkaardige artikels");} // er zijn geen gelijkaardige artikels 
		}
    if(fldlen(93,10) && PromoFiche.ArtRec && multiart_==NO){
			if(PromoFiche.BlokArtikel) {
				scraddpicto(10,z-1,2,0,2,1,578,0,4,"Artikel toestaan op kassa");
			}
			else{
				scraddpicto(10,z-1,2,0,2,1,593,0,4,"Artikel BLOKKEREN op kassa");
			}
		}
    scrfld(z++,1,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken");
    scrfld(z++,93,4);scraddpicto(9,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); scrofld(z++,52,14,-1);
		fasinit(6);*u(6,1)=PromoFiche.ArtRec; if(*u(6,1)) fasgeti(6);
    for(k=0;k<max_kprx;k++){
      if(k==0) scrifld(z++,fm_os10,"Kassa bak");
      else if(k==max_kprx-1) scrifld(z++,fm_os10,"Kassa stuk");
      else {copy("Horeca",str_,6);stcli_d(&str_[6],(long)k,2,1);scrifld(z++,fm_os10,str_);}
      scrfld(z++,93,11+k);
			wpct_=0;
			if(*u(6,1) && ap_){
				vp_=*f(93,11+k); if(vp_==0) vp_=nm_vp[k];
				if(vp_){
					if(k==max_kprx-1 && *f(6,31)>1) wpct_=(vp_-(ap_/ *f(6,31)))/ (ap_ / *f(6,31));
					else wpct_=(vp_-ap_)/ ap_;
				} else wpct_=0;
				wpct_=valu_cnv("EUR","EUR",(double)(wpct_*100.),(double)0.1);
			}
			scrifld(z++,fm_of3_1,&wpct_); if(wpct_<0) scrchat(z-1,0x0B); 
      scrifld(z++,fm_of4_2,&nm_vp[k]); if(pr_offset_) scrchat(z-1,0x9);
    }
    for(k=max_kprx;k<6;k++) z+=4;
		//if(fldlen(93,26)){
  //		scrfld(-z,93,26);scraddpicto(3,z++,0,0,2,1,112,0,4,"Uitgebreid zoeken");scrifld(z++,VarTextFmt(25,0),nm_formule); 
		//} else z+=2;
//		for(k=0;k<7;k++) scrfld(z++,93,dsp_items[k]);

		z_promo_=z;
		scrifld(z++,fm_us20,PromoFiche.PromoText);
		scrifld(z++,fm_u_BF,&PromoFiche.SelBakFles);scrifld(z++,fm_uu2,&PromoFiche.MaxPromoPerTicket);
		scrifld(z++,fm_uf3_0,&PromoFiche.VanafAantal);
		scrifld(z++,fm_uJN,&PromoFiche.SelPromo[0]);
		scrifld(z++,fm_uf3_0,&PromoFiche.kPCT);
		scrifld(z++,fm_uf2_0,&PromoFiche.kPCTAantal);
		scrifld(z++,fm_uJN,&PromoFiche.SelPromo[1]);
		scrifld(z++,fm_uf2_2,&PromoFiche.kEUR);
		scrifld(z++,fm_uf2_0,&PromoFiche.kEURAantal);
		scrifld(z++,fm_uJN,&PromoFiche.SelPromo[2]);
		scrifld(z++,fm_uf2_0,&PromoFiche.GratisAantal);
		scrifld(z++,fm_uJN,&PromoFiche.SelPromo[3]);
		fmt_get(6,3); scrifld(z++,fmt,nm_gr_art_);scraddpicto(8,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken");
		scrifld(z++,fm_uJN,&PromoFiche.SelPromo[4]);
		scrifld(z++,fm_us20,PromoFiche.GratisText);
		scrifld(z++,fm_uJN,&PromoFiche.SelPromo[5]); // staffelkorting 
//		scrifld(z++,fm_uf2_0,&PromoFiche.KstafAantal1);
		scrifld(z++,fm_uf3_0,&PromoFiche.KstafPct1);
		scrifld(z++,fm_uf2_0,&PromoFiche.KstafAantal2);
		scrifld(z++,fm_uf3_0,&PromoFiche.KstafPct2);
		scrifld(z++,fm_uJN,&PromoFiche.SelPromo[6]);
		scrifld(z++,fm_uf4_2,&PromoFiche.VasteTotaalPrijs);
		z_formule_=z;
		scrfld(z++,93,25);
    key=scrupd(curs,0x1E1);curs=z_promo_;
		if(fldlen(93,10)) ConLook(0);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106){
      if(mode==2) return NO;
			else {fasgeti(93);return YES;}
    }
		if(key==5005){
			if(DisplayWarning("Wenst u echt deze promotie te schrappen?",605,1)==YES) {
				faskill(93);return YES;
		  }
		}
    if(key==101 && *u(93,2)==0 && *u(93,3)==0 && *u(93,4)==0) return NO;
    if(*u(93,7)==0) {errnum=38;curs=2;goto redo;}
    if(*u(93,8)==0) {errnum=38;curs=3;goto redo;}
		if(key==5006){
			fasinit(6); copy(nm_art_,s(6,3),fldlen(6,3));
			if(search(6,98)){curs=3;goto redo;}
      copy(s(6,3),nm_art_,fldlen(6,3));
		}
		if(key==5008){
			fasinit(6); copy(nm_gr_art_,s(6,3),fldlen(6,3));
			if(search(6,98)) {curs=z_promo_+12;goto redo;}
			copy(s(6,3),nm_gr_art_,fldlen(6,3));PromoFiche.GratisArt=*u(6,1);
		}
    if(nm_art_[0]){
      if(cmp_str(nm_art_,art_res,fldlen(6,3))){
				fasinit(6); copy(nm_art_,s(6,3),fldlen(6,3));
				if(search(6,0)) {curs=3;goto redo;}
				copy(s(6,3),art_res,fldlen(6,3));copy(s(6,3),nm_art_,fldlen(6,3));PromoFiche.ArtRec=*u(6,1);
				pr_offset_=0; vpos_=0;
				if(fldlen(6,105) && *u(6,105)){
					if(*u(6,105)<=*u(25,2) || *u(6,105)<=*u(93,7)) {pr_offset_=94;vpos_=10;}
				}
				ap_=*f(6,18+pr_offset_)*=1.+ *f(6,28)/100.; // AK-prijs incl BTW om gemakkelijker W% te berekenen
				for(k=0;k<max_kprx;k++){
					nm_vp[k]=*f(6,PrNrs[tb_ktypes[k]+vpos_]);
					if(!(sys3894 & (1<<(tb_ktypes[k])))) nm_vp[k]*=1.+ *f(6,28)/100.;
					if(nm_vp[k]!=*f(6,PrNrs[tb_ktypes[k]+vpos_])) nm_vp[k]=valu_cnv("EUR","EUR",(double)nm_vp[k],(double)0.01);
				}
      }
    }
    else{
      fasinit(6);copy(s(6,3),art_res,fldlen(6,3));copy(s(6,3),nm_art_,fldlen(6,3));PromoFiche.ArtRec=0;
      zeros((char *)&nm_vp[0],sizeof nm_vp);ap_=0;
    }
		if(PromoFiche.ArtRec==0) PromoFiche.BlokArtikel=0; 
		if(key==5010){ // blokkeer/deblokkeer
			if(PromoFiche.BlokArtikel) PromoFiche.BlokArtikel=0; 
			else PromoFiche.BlokArtikel=YES;
			goto redo;
		}
		if(key==5001){
			if(search(1,98)){curs=5;goto redo;}
		}
    if(*s(1,3)) {
      if (nm_art_[0]) {errnum=72; curs=4; goto redo;}
      if(search(1,0)) {curs=5;goto redo;}
    }
    else *u(1,1)=0;
		if(key==5009){
		  if(search(52,98)) {
		  	fasinit(52); if(*u(93,4)){	*u(52,1)=*u(93,4);fasgeti(52);}
		  }
		 	else *u(93,4)=*u(52,1);
		}
    fasinit(52);
    if(*u(93,4)){
      *u(52,1)=*u(93,4);fasgeti(52);
    }
    if(*u(93,4) && nm_art_[0]) {errnum=72; curs=5; goto redo;}
		if(key==5004){
			if(PromoFiche.ArtRec==0){errnum=39;curs=3; goto redo;}
			else {
				
				ShowSameArticles();
				multiart_=NO; for(k=0;k<MAX_MIXART;k++) if(PromoFiche.MixArtRec[k]) {multiart_=YES;break;}
			}
		}
		if(multiart_) PromoFiche.BlokArtikel=0; 
		//if(fldlen(93,26)){
		//	if(key==5003){
		//		k=SelectPromoFormule();
		//		if(k) *u(93,26)=k;
		//	}
		//	zero(nm_formule,sizeof nm_formule);
		//	if(*u(93,26)){
		//		if(*u(93,26)<1 || *u(93,26)>20 || PromoFormule[*u(93,26)-1].Omschrijving[0]=='\0'){errnum=39; curs=33;goto redo;}
		//		copy(PromoFormule[*u(93,26)-1].Omschrijving,nm_formule,25);
		//	}
		//}
    *u(93,2)=PromoFiche.ArtRec;
    *u(93,3)=*u(1,1);
    if(*u(93,2)==0 && *u(93,3)==0 && *u(93,4)==0) {errnum=38;curs=3;goto redo;}
		if(PromoFiche.SelPromo[0]=='J' && PromoFiche.kPCT==0){curs=z_promo_+4; errnum=38; goto redo;}
		if(PromoFiche.SelPromo[1]=='J' && PromoFiche.kEUR==0){curs=z_promo_+7; errnum=38; goto redo;}
		if(PromoFiche.SelPromo[2]=='J' && PromoFiche.GratisAantal==0){curs=z_promo_+10; errnum=38; goto redo;}
		if(PromoFiche.SelPromo[3]=='J'){
			if(nm_gr_art_[0]){
				fasinit(6); copy(nm_gr_art_,s(6,3),fldlen(6,3));
				if(search(6,0)) {curs=z_promo_+12;goto redo;}
				copy(s(6,3),nm_gr_art_,fldlen(6,3));PromoFiche.GratisArt=*u(6,1);
			}
			else{
				fasinit(6);copy(s(6,3),nm_gr_art_,fldlen(6,3));PromoFiche.GratisArt=0;
				curs=z_promo_+12; errnum=38; goto redo;
			}
		}
		if(PromoFiche.SelPromo[4]=='J'){
			if(PromoFiche.GratisText[0]=='\0'){curs=z_promo_+14; errnum=38; goto redo;}
		}
		if(PromoFiche.SelPromo[5]=='J'){
      if(PromoFiche.KstafAantal2<=PromoFiche.VanafAantal && PromoFiche.KstafPct2){curs=z_promo_+18; errnum=77; goto redo;}
		}
		if(PromoFiche.SelPromo[6]=='J' && PromoFiche.VasteTotaalPrijs==0){curs=z_promo_+20; errnum=38; goto redo;}
		j=0; for(k=0;k<7;k++) if(PromoFiche.SelPromo[k]=='J') j++;
		fl_newpromo_=NO; if(j) fl_newpromo_=YES;
		if(j==1 && PromoFiche.VanafAantal==0){curs=z_promo_+12; errnum=38; goto redo;}
		else if(j>1) {errnum=72; curs=z_promo_+3; goto redo;}
		if(key==109) DspPromoBis();
    if(*f(93,21) && *s(93,20)=='\0') {errnum=38;DspPromoBis(); goto redo;}
    if(*f(93,23) && *s(93,22)=='\0') {errnum=38;DspPromoBis(); goto redo;}
//    if(fldlen(93,26) && *u(93,26) && *s(93,25)) {errnum=72;curs=33;goto redo;}
    for(k=11;k<=25;k++){
      if(fldlen(93,k)==0) continue;
      if((k==20 || k==22) && *s(93,k)=='G') break;
      if(k==25 && *s(93,k)) break;
      if(*f(93,k)) break;
    }
    if(k>=25){
			j=0; for(k=0;k<7;k++) if(PromoFiche.SelPromo[k]=='J') j++;
		  if(j==0){
				if(fldlen(93,25)==0 || *s(93,25)=='\0') {curs=z_promo_+3; errnum=38;goto redo;}
			}
			else{
				if(fldlen(93,25) && *s(93,25)!='\0') {curs=z_formule_; errnum=72;goto redo;}
			}
		}
    if(key!=108 && key!=5002 && key!=5003) goto redo;
		fasunlck(-2);
		multiart_=NO; for(k=0;k<MAX_MIXART;k++) if(PromoFiche.MixArtRec[k]) {multiart_=YES;break;}
		if(fldlen(93,10)){
			if(PromoFiche.BlokArtikel && PromoFiche.ArtRec) *u(93,10)=YES; else *u(93,10)=NO;
		}
		copy(PromoFiche.PromoText,s(93,30),20);
		*s(93,34)=PromoFiche.SelBakFles;
		*u(93,41)=PromoFiche.MaxPromoPerTicket;
		*u(93,35)=0;
		if(PromoFiche.SelPromo[0]=='J'){
			*u(93,35)=5; *f(93,36)=PromoFiche.VanafAantal; *f(93,37)=PromoFiche.kPCT; *f(93,38)=PromoFiche.kPCTAantal;
		}
		else if(PromoFiche.SelPromo[1]=='J'){
			*u(93,35)=6; *f(93,36)=PromoFiche.VanafAantal; *f(93,37)=PromoFiche.kEUR; *f(93,38)=PromoFiche.kEURAantal; 
		}
		else if(PromoFiche.SelPromo[2]=='J'){
			*u(93,35)=7;*f(93,36)=PromoFiche.VanafAantal; *f(93,37)=PromoFiche.GratisAantal;
		}
		else if(PromoFiche.SelPromo[3]=='J'){
			*u(93,35)=8; *f(93,36)=PromoFiche.VanafAantal; *f(93,37)=PromoFiche.GratisArt; 
		}
    else if(PromoFiche.SelPromo[4]=='J'){
			*u(93,35)=9; *f(93,36)=PromoFiche.VanafAantal; copy(PromoFiche.GratisText,s(93,40),20);
		}
		if(PromoFiche.SelPromo[5]=='J'){
			*u(93,35)=10; *f(93,36)=PromoFiche.VanafAantal; *f(93,37)=PromoFiche.KstafPct1; *f(93,38)=PromoFiche.KstafAantal2; *f(93,39)=PromoFiche.KstafPct2;
		}
		if(PromoFiche.SelPromo[6]=='J'){
			*u(93,35)=11; *f(93,36)=PromoFiche.VanafAantal; *f(93,37)=PromoFiche.VasteTotaalPrijs;
		}

		if(multiart_ || (fl_newpromo_ && PromoFiche.ArtRec)){
			GetCurrentDateTime(&act_jj_,&act_mm_,&act_dd_,&act_uur_,&act_min_,&act_sec_);
			fasinit(80);fasinfo(80,202); PromoFiche.MixGroepCode=(PromoFiche.ArtRec%100)*1000000 + act_uur_*10000+act_min_*100+act_sec_;
			*l(93,45)=PromoFiche.MixGroepCode;
		}
    if(mode==1){
      errnum=fasupd(stu);
    }
    else if(mode==2){
      errnum=fasadd(stu);
    }
		if(!errnum && fldlen(93,45)){
  		PromoFiche.Rec93=*u(93,1);
			for(k=0;k<MAX_MIXART;k++){
				if(PromoFiche.MixVkpRec[k]){
					fasinit(93); *u(93,1)=PromoFiche.MixVkpRec[k];
					if(fasgetu(93)==0) faskill(93);
				}
			}
			if(multiart_){
				fasinit(93); *u(93,1)=PromoFiche.Rec93; fasgeti(93);
				for(k=11;k<=16;k++) *f(93,k)=0; // eventuele vaste prijs NIET meenemen
				for(k=0;k<MAX_MIXART;k++){
					if(PromoFiche.MixArtRec[k]){
						 *u(93,1)=0; *u(93,2)=PromoFiche.MixArtRec[k]; fasadd(93);
					}
				}
			}
		}
		fasunlck(-1);
    fasflush(0);
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
	if(key==5002) return 2;
	if(key==5003) return 3;
  return YES;
}

static DspPromoBis()
{
  int16 curs=7,key,k,z;
	int16 dsp_items[5]={20,21,22,23,31};

	fasinit(6);*u(6,1)=PromoFiche.ArtRec; fasgeti(6);
	curs=7;
  FOREVER{
redo:
    scrnum=0;scrget(3,17);z=1;
    scrofld(z++,93,7,-1); scrofld(z++,93,8,-1);
		scrofld(z++,6,3,-1);
    scrofld(z++,1,3,-1);
    scrofld(z++,93,4,-1); scrofld(z++,52,14,-1);
		for(k=0;k<5;k++) scrfld(z++,93,dsp_items[k]);
    key=scrupd(curs,0x81);curs=7;
    if(*f(93,21) && *s(93,20)=='\0') {errnum=38;curs=7;goto redo;}
    if(*f(93,23) && *s(93,22)=='\0') {errnum=38;curs=9;goto redo;}
		if(key==101 || key==108)break;
  }
	fasinit(6);*u(6,1)=PromoFiche.ArtRec; fasgeti(6);
endsr:;
}

static fichupdOLD(mode)
int16 mode;
{
  int16 curs,k,key,z,pr_offset_,vpos_;
	int16 dsp_items[7]={25,30,20,21,22,23,31};
  float nm_vp[6],ap_,vp_,wpct_;
  char str_[10],nm_formule[30];
 
  errnum=0;
  if(mode==1) curs=10; else curs=2;
  fasinit(6);*u(6,1)=*u(93,2);fasgeti(6);zeros((char *)&nm_vp[0],sizeof nm_vp);
  pr_offset_=0; vpos_=0;
	if(fldlen(6,105) && *u(6,105)){
		if(*u(6,105)<=*u(25,2) || *u(6,105)<=*u(93,7)){ pr_offset_=94; vpos_=10;}
	}
	ap_=*f(6,18+pr_offset_)*=1.+ *f(6,28)/100.; // AK-prijs incl BTW om gemakkelijker W% te berekenen
  for(k=0;k<max_kprx;k++){
    nm_vp[k]=*f(6,PrNrs[tb_ktypes[k]+vpos_]);
    if(!(sys3894 & (1<<(tb_ktypes[k])))) nm_vp[k]*=1.+ *f(6,28)/100.;
    if(nm_vp[k]!=*f(6,PrNrs[tb_ktypes[k]+vpos_])) nm_vp[k]=valu_cnv("EUR","EUR",(double)nm_vp[k],(double)0.01);
  }
	if(fldlen(93,26)){
  	zero(nm_formule,sizeof nm_formule);
  	if(*u(93,26)>=1 && *u(93,26)<=20) copy(PromoFormule[*u(93,26)-1].Omschrijving,nm_formule,25);
	}
  fasinit(1);*u(1,1)=*u(93,3);fasgeti(1);
  fasinit(52); if(*u(93,4)){*u(52,1)=*u(93,4);fasgeti(52);}
  FOREVER{
    copy(s(6,3),art_res,fldlen(6,3));
redo:
    scrnum=0;scrget(3,8);z=1;
    scrfld(z++,25,1);
    scrfld(z++,93,7); scrfld(z++,93,8);
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrfld(z++,6,3);
  	if(fldlen(93,35)){
			if(*u(93,35)) {scrchat(z-1,0x9);scraddpicto(4,z-1,1,0,3,1,69,0,4,"Gelijkaardige artikels");} // er zijn gelijkaardige artikels 
			else {scrchat(z-1,0xFF);scraddpicto(4,z-1,1,0,3,1,69,0,3,"Gelijkaardige artikels");} // er zijn geen gelijkaardige artikels 
		}
    if(YES /* kaart_used*/){scrofld(z++,1,lvcd+1,-1);scrfld(z++,1,3);} else z+=2;
    if(YES /* kaart_used*/){scrfld(z++,93,4); scrofld(z++,52,14,-1);} else z+=2;
    for(k=0;k<max_kprx;k++){
      if(k==0) scrifld(z++,fm_os10,"Kassa bak");
      else if(k==max_kprx-1) scrifld(z++,fm_os10,"Kassa stuk");
      else {copy("Horeca",str_,6);stcli_d(&str_[6],(long)k,2,1);scrifld(z++,fm_os10,str_);}
      scrfld(z++,93,11+k);
			wpct_=0;
			if(*u(6,1) && ap_){
				vp_=*f(93,11+k); if(vp_==0) vp_=nm_vp[k];
				if(vp_){
					if(k==max_kprx-1 && *f(6,31)>1) wpct_=(vp_-(ap_/ *f(6,31)))/ (ap_ / *f(6,31));
					else wpct_=(vp_-ap_)/ ap_;
				} else wpct_=0;
				wpct_=valu_cnv("EUR","EUR",(double)(wpct_*100.),(double)0.1);
			}
			scrifld(z++,fm_of3_1,&wpct_); if(wpct_<0) scrchat(z-1,0x0B); 
      scrifld(z++,fm_of4_2,&nm_vp[k]); if(pr_offset_) scrchat(z-1,0x9);
    }
    for(k=max_kprx;k<6;k++) z+=4;
		if(fldlen(93,26)){
  		scrfld(-z,93,26);scraddpicto(3,z++,0,0,2,1,112,0,4,"Uitgebreid zoeken");scrifld(z++,VarTextFmt(25,0),nm_formule); 
		} else z+=2;
		for(k=0;k<7;k++) scrfld(z++,93,dsp_items[k]);
//    for(k=20;k<35;k++) scrfld(z++,93,k);
    key=scrupd(curs,0xE1);curs=10;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106){
      if(mode==2) return NO;
			else {fasgeti(93);return YES;}
    }
    if(key==101 && *u(93,2)==0 && *u(93,3)==0 && *u(93,4)==0) return NO;
    if(*u(93,7)==0) {errnum=38;curs=2;goto redo;}
    if(*u(93,8)==0) {errnum=38;curs=3;goto redo;}
    if(*s(6,3)){
      if(cmp_str(s(6,3),art_res,fldlen(6,3))){
				if(search(6,0)) {curs=5;goto redo;}
				copy(s(6,3),art_res,fldlen(6,3));
				pr_offset_=0; vpos_=0;
				if(fldlen(6,105) && *u(6,105)){
					if(*u(6,105)<=*u(25,2) || *u(6,105)<=*u(93,7)) {pr_offset_=94;vpos_=10;}
				}
				ap_=*f(6,18+pr_offset_)*=1.+ *f(6,28)/100.; // AK-prijs incl BTW om gemakkelijker W% te berekenen
				for(k=0;k<max_kprx;k++){
					nm_vp[k]=*f(6,PrNrs[tb_ktypes[k]+vpos_]);
					if(!(sys3894 & (1<<(tb_ktypes[k])))) nm_vp[k]*=1.+ *f(6,28)/100.;
					if(nm_vp[k]!=*f(6,PrNrs[tb_ktypes[k]+vpos_])) nm_vp[k]=valu_cnv("EUR","EUR",(double)nm_vp[k],(double)0.01);
				}
      }
    }
    else{
      fasinit(6);copy(s(6,3),art_res,fldlen(6,3));
      zeros((char *)&nm_vp[0],sizeof nm_vp);ap_=0;
    }
    if(*s(1,3)) {
      if (*s(6,3)) {errnum=72; curs=7; goto redo;}
      if(search(1,0)) {curs=8;goto redo;}
    }
    else *u(1,1)=0;
    fasinit(52);
    if(*u(93,4)){
      *u(52,1)=*u(93,4);fasgeti(52);
    }
    if(*u(93,4) && *s(6,3)) {errnum=72; curs=9; goto redo;}
		if(key==5004){
			if(*u(6,1)==0){errnum=39;curs=5; goto redo;}
			else ShowSameArticles();
		}
		if(fldlen(93,26)){
			if(key==5003){
				k=SelectPromoFormule();
				if(k) *u(93,26)=k;
			}
			zero(nm_formule,sizeof nm_formule);
			if(*u(93,26)){
				if(*u(93,26)<1 || *u(93,26)>20 || PromoFormule[*u(93,26)-1].Omschrijving[0]=='\0'){errnum=39; curs=33;goto redo;}
				copy(PromoFormule[*u(93,26)-1].Omschrijving,nm_formule,25);
			}
		}
    *u(93,2)=*u(6,1);
    *u(93,3)=*u(1,1);
    if(*u(93,2)==0 && *u(93,3)==0 && *u(93,4)==0) {errnum=38;curs=5;goto redo;}
    if(*f(93,21) && *s(93,20)=='\0') {errnum=38;curs=28;goto redo;}
    if(*f(93,23) && *s(93,22)=='\0') {errnum=38;curs=30;goto redo;}
    if(fldlen(93,26) && *u(93,26) && *s(93,25)) {errnum=72;curs=33;goto redo;}
    for(k=11;k<=26;k++){
      if(fldlen(93,k)==0) continue;
      if((k==20 || k==22) && *s(93,k)=='G') break;
      if(k==25 && *s(93,k)) break;
			if(k==26 && *u(93,k)) break;
      if(*f(93,k)) break;
    }
    if(k>=27) {errnum=38;goto redo;}
    if(key!=108) goto redo;
		fasunlck(-2);
    if(mode==1){
      errnum=fasupd(stu);
    }
    else if(mode==2){
      errnum=fasadd(stu);
    }
		fasunlck(-1);
    fasflush(0);
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
  return YES;
}
  
static ShowSameArticles()
{
  int16 curs=1,j,key,k,n,z,mode_,cursupd_,start_=0;
	char TbOmschr[MAX_MIXART][40],MastOmschr[40];

	memset((char *)TbOmschr[0],0,sizeof TbOmschr); memset((char *)MastOmschr,0,sizeof MastOmschr);
	fasinit(6);*u(6,1)=PromoFiche.ArtRec; fasgeti(6); copy(s(6,3),MastOmschr,fldlen(6,3));
	
	for(k=0;k<MAX_MIXART;k++){
		if(PromoFiche.MixArtRec[k]){
			fasinit(6); *u(6,1)=PromoFiche.MixArtRec[k]; fasgeti(6);
			copy(s(6,3),TbOmschr[k],fldlen(6,3));
		}
	}
  FOREVER{
    redo:
    scrnum=0;scrget(3,14);z=1;
		scrifld(z++,fm_os40,MastOmschr);
		cursupd_=NO;
		fmt_get(6,3);
    for(k=0;k<15;k++){
			if(start_ && k>=14) continue; // tot 29 stuks
			n=1+k+start_;scrifld(z++,fm_ou2,&n);
			scrifld(z++,fmt,&TbOmschr[k+start_][0]);
			scraddpicto(1+k,z-1,9,0,2,1,112,0,4,"Zoek artikel"); 
			scraddpicto(21+k,z-1,12,0,2,1,540,0,0,"Schrap koppeling"); 
			cursupd_=YES;
  	}
		if(cursupd_==NO) curs=-1;
    key=scrupd(curs,0x47);curs=1;
    if(key==101) break;

		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
		if(key>=5001 && key<=5015){ // zoek
			k=key-5001;
			fasinit(6);copy(TbOmschr[k+start_],s(6,3),fldlen(6,3));
			if(search(6,98)) {curs=2+k*2;errnum=39;goto redo;}
			if(*u(6,1)==PromoFiche.ArtRec) {curs=2+k*2;errnum=77;goto redo;} // niet hoofdartikel
			PromoFiche.MixArtRec[k+start_]=*u(6,1); copy(s(6,3),TbOmschr[k+start_],fldlen(6,3));
			goto redo;
		}
		if(key>=5021 && key<=5035){ // schrappen
			k=key-5021;
			PromoFiche.MixArtRec[k+start_]=0;zero(TbOmschr[k+start_],fldlen(6,3));
			goto redo;
		}
		for(k=0;k<15;k++){
			if(TbOmschr[k+start_][0]=='\0') PromoFiche.MixArtRec[k+start_]=0;
			else{
				fasinit(6);copy(TbOmschr[k+start_],s(6,3),fldlen(6,3));
				if(search(6,0)) {curs=2+k*2;errnum=39;goto redo;}
				if(*u(6,1)==PromoFiche.ArtRec) {curs=2+k*2;errnum=77;goto redo;} // niet hoofdartikel
				PromoFiche.MixArtRec[k+start_]=*u(6,1); copy(s(6,3),TbOmschr[k+start_],fldlen(6,3));
			}
		}
		if(key==102){ start_-=15; if(start_<0) start_=0;}
		if(key==103){ start_+=15; if(start_+15>MAX_MIXART) start_=MAX_MIXART-15;}
		if(key==108)break;
  }
	fasinit(6);*u(6,1)=PromoFiche.ArtRec; fasgeti(6);
endsr:;
}



static add_via_file(auto_mode_)
int16 auto_mode_;
{
  int16 key,k,len_,mode_,curs=1,z,fl_update=YES;
	int16 form_dat[8],pr_mode,prtnr;
  uint16 inq_lev=0,promo_nr_;
  char promofile[40],date_last_download[20];

	// A=datum begin, B=datum einde, C=code, D=omschrijving, E=prijs, F=promotekst, G=promo-EAN

	fl_update = BibiFileUpdated(PROMO_BIBI_MAP,FTPUsername,FTPPaswoord,PROMO_PRX_FILE,PROMO_PRX_MAP);

	pl_80_1=l(80,1);  p_data=s(80,1)+4;
	zero(promofile,sizeof promofile); 
	k=copy0(PROMO_PRX_MAP,promofile,sizeof promofile);copy0(PROMO_PRX_FILE,&promofile[k],sizeof promofile-k);
	fasclos(-2);fasinit(80);
	fasopen(promofile,102);/* eerste call voor dir */
	fasinfo(80,204);/* ophalen antwoord van dir */
	if(*s(80,1)){
		fasinit(80);fasinfo(80,205);/* get date  */
	} else fasinit(80);
	copy(s(80,1),date_last_download,20);
	fasclos(-2);
	sysget(2942,2,(char *)&inq_lev); fasinit(1); if(inq_lev){*u(1,1)=inq_lev;fasgeti(1);}
  FOREVER{
		redo:;
    scrget(3,9);z=1;
		scraddpicto(1,0,65,9,4,2,60,0,fl_update*4,"Ophalen folder"); // "^!PRIKENTIK");
		scraddpicto(2,0,76,22,4,2,59,0,4,"Parameters");
    scrfld(z++,1,3);
		scrifld(z++,fm_os20,date_last_download);

    key=scrupd(curs,0x81);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){ // folder.txt downloaden 
		  k = BibiDownload(PROMO_BIBI_MAP,FTPUsername,FTPPaswoord,PROMO_PRX_FILE,PROMO_PRX_MAP);
			if(k==1){
        fl_update=NO;
				fasclos(-2);fasinit(80);
				fasopen(promofile,102);/* eerste call voor dir */
				fasinfo(80,204);/* ophalen antwoord van dir */
				if(*s(80,1)){
					fasinit(80);fasinfo(80,205);/* get date  */
				} else fasinit(80);
				copy(s(80,1),date_last_download,20);
				fasclos(-2);
			}
			else{
				 scrget(1,170);scrifld(10,fm_os63,"Ophalen folder NIET gelukt, druk op F8 om verder te gaan");scrchat(14,0x3);
				 scrupd(-1,0x81); 
//				 con_derr("Hallo");
			}
			goto redo; 
		}
		if(key==5002){UpdateLoginInfo(); goto redo;}
    if(key==101) goto endsr;
		if(promofile[0]=='\0'){curs=1;errnum=38; goto redo;}
		if(search(1,0)){curs=1;goto redo;}
		inq_lev=*u(1,1);
		if(sys2978){
			sysput(2976,2,(char *)&inq_lev);
			sysput(2942,2,(char *)&inq_lev);
		}
		fasclos(-2);if(fasopen(promofile,1)!=0) {errnum=1;curs=1;goto redo;}
		if(key==108) break;
  }
	sysput(2942,2,(char *)&inq_lev);
  scrget(1,7);scrupd(-3,0);

	getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
									
  prtfld(25,1,20);prttext("<t25b>Ingelezen promoties via folder-bestand<bt90>");
  prtifld(fm_odat,u(25,2),-1);prttext("<t124>Blz.<ppp>");
  prtbuf(1);z=1;
	prtitab(z,fm_udat,&folderlijn.dt_beg,1,-1); prttitle(z++,"Dt.begin",3);
	prtitab(z,fm_udat,&folderlijn.dt_end,1,-1); prttitle(z++,"Dt.einde",3);
  prtitab(z,fm_os10,folderlijn.fcode,1,-1); prttitle(z++,"Code",3);
	prtitab(z,fm_os40,folderlijn.fomschr,1,-1); prttitle(z++,"Omschrijving",3);
	prtitab(z,fm_of4_2,&folderlijn.kassaprijs[0],1,-1); prttitle(z++,"Prijs",0x13);
	prtitab(z,fm_of4_2,&folderlijn.kassaprijs[max_kprx-1],1,-1); prttitle(z++,"St.Prijs",0x13);
	prtitab(z,fm_os30,folderlijn.promotekst,1,-1); prttitle(z++,"Promo-tekst",3);
	prtitab(z,fm_os15,folderlijn.ean,1,-1); prttitle(z++,"EAN",3);
	prtitab(z,fm_os1,&folderlijn.promocode,1,-1); prttitle(z++,"F",3);
  prtbuf(3);
  p_pdfname("Promoties van folderbestand",0,0);

	AantalPromoInFile=0;
	fasinit(80);mode_=0;
  FOREVER{
    if(read_rec(mode_)) break; mode_=1;
    if(get_date(0)!=0 && get_date(1)!=0) AantalPromoInFile++;
	}
	fasinit(80);mode_=0;promo_nr_=0;
  FOREVER{
next:;
	
    if(read_rec(mode_)) break; mode_=1;
		CnvJamaChar(p_data,256,1); // convert2 JamaAscii
		fasinit(93);zero((char *)&folderlijn.dt_beg,sizeof folderlijn);
		folderlijn.dt_beg=get_date(0);if(folderlijn.dt_beg==0) goto next; else *u(93,7)=folderlijn.dt_beg;
		folderlijn.dt_end=get_date(1);if(folderlijn.dt_end==0) goto next; else *u(93,8)=folderlijn.dt_end;
		len_=ele_len(2); if(len_>fldlen(11,5)) len_=fldlen(11,5);copy(rec_ele(2),folderlijn.fcode,len_);
		len_=ele_len(3); if(len_>50) len_=50;copy(rec_ele(3),folderlijn.fomschr,len_);
		folderlijn.prijs=get_num(4);folderlijn.kassaprijs[0]=folderlijn.prijs;
		len_=ele_len(5);if(len_>50) len_=50;copy(rec_ele(5),folderlijn.promotekst,len_);copy(folderlijn.promotekst,s(93,30),fldlen(93,30));
		len_=ele_len(6);if(len_>20) len_=20;copy(rec_ele(6),folderlijn.ean,len_);copy(folderlijn.ean,s(93,31),fldlen(93,31));
		copy(&folderlijn.promocode,s(93,25),fldlen(93,25));
		promo_nr_++;
		k=find_artikel(inq_lev,folderlijn.fcode,folderlijn.fomschr,promo_nr_);
		if(k==1) {
			folderlijn.kassaprijs[0]=folderlijn.prijs;
			for(k=3;k<20;k++) prtinfo(k,0);nextline();
			goto next; // skip
		}
		if(k==2) break; // stop
		for(k=0;k<max_kprx;k++) folderlijn.kassaprijs[k]=*f(93,11+k);
		copy(s(93,30),folderlijn.promotekst,fldlen(93,30));
		copy(s(93,31),folderlijn.ean,fldlen(93,31));
		copy(s(93,25),&folderlijn.promocode,fldlen(93,25));
		*u(93,2)=*u(6,1);
		if(faskeyi(93,7,0)==0) faskill(93);
		fasinit(93);
		*u(93,7)=folderlijn.dt_beg;*u(93,8)=folderlijn.dt_end;*u(93,2)=*u(6,1);
		for(k=0;k<max_kprx;k++) *f(93,11+k)=folderlijn.kassaprijs[k];
		copy(folderlijn.promotekst,s(93,30),fldlen(93,30));
		copy(folderlijn.ean,s(93,31),fldlen(93,31));
		copy(&folderlijn.promocode,s(93,25),fldlen(93,25));
		errnum=fasadd(93);
		for(k=1;k<20;k++) prtinfo(k,0);nextline();
		prttext("<t11b>Toegewezen aan : ");prtfld(6,2,-1); prttext("  "); prtfld(6,3,-1);nextline();
  }
  endsr:;
  fasclos(-2);prtclose();
}

static find_artikel(lev_rec_,lev_code_,art_naam_,promo_nr_)
uint16 lev_rec_,promo_nr_;
char *lev_code_,*art_naam_;
{
	int16 k,codelen_,z,key,curs=6,mode_,found_=NO;
	uint16 last_art_,lrec_;
	float nm_vp[10];
	char str_[15];


	zero((char *)&folderlijn.kassaprijs[0],sizeof folderlijn.kassaprijs);last_art_=0;
	zero((char *)&nm_vp[0],sizeof nm_vp);
	if(lev_code_[0]=='\0') goto disp_promo;
	codelen_=fldlen(11,5);found_=NO;
	if(fldlen(11,5)){
		fasinit(11);*u(11,2)=lev_rec_;mode_=1;
		FOREVER{
			if(faskeyi(11,1,mode_)) break; mode_=2;
			if(*u(11,2)!=lev_rec_) break;
			if(cmpstr(lev_code_,s(11,5),codelen_)==0){found_=YES;break;}
		}
	}
	if(found_){fasinit(6);*u(6,1)=*u(11,3);fasgeti(6);goto disp_promo;}
	//codelen_=fldlen(6,8);found_=NO;
	//if(codelen_){
	//	fasinit(6);*u(6,7)=lev_rec_;mode_=1;
	//	FOREVER{
	//		if(faskeyi(6,4,mode_)) break; mode_=2;
	//		if(*u(6,7)!=lev_rec_) break;
	//		if(cmpstr(lev_code_,s(6,8),codelen_)==0){found_=YES;break;}
	//	}
	//}
	disp_promo:;
	if(found_){
		for(k=0;k<max_kprx;k++){
			nm_vp[k]=*f(6,PrNrs[tb_ktypes[k]]);
			if(!(sys3894 & (1<<(tb_ktypes[k])))) nm_vp[k]*=1.+ *f(6,28)/100.;
			if(nm_vp[k]!=*f(6,PrNrs[tb_ktypes[k]])) nm_vp[k]=valu_cnv("EUR","EUR",(double)nm_vp[k],(double)0.01);
			if(k==0) *f(93,11+k)=folderlijn.prijs;
			else if(k==max_kprx-1 && *f(6,31)<=1) *f(93,11+k)=folderlijn.prijs;
			else *f(93,11+k)=0;
		}
		last_art_=*u(6,1);
	}
	else{
		fasinit(6);
		for(k=0;k<fldlen(6,3);k++){
			if(art_naam_[k]==' ' || art_naam_[k]=='\0') break;
			*(s(6,3)+k)=art_naam_[k];
		}
	}
	FOREVER{
		redo_art:;
		scrget(3,10);z=1;
		scrifld(z++,fm_ou3,&promo_nr_);scrifld(z++,fm_ou3,&AantalPromoInFile);
		scrifld(z++,fm_os20,lev_code_);
		scrifld(z++,fm_os50,art_naam_);
		scrifld(z++,fm_of4_2,&folderlijn.prijs);
		scrifld(z++,fm_os40,folderlijn.promotekst);
		scrifld(z++,fm_os20,folderlijn.ean);
		scrifld(z++,fm_odat,&folderlijn.dt_beg);scrifld(z++,fm_odat,&folderlijn.dt_end);
		scrfld(z++,6,3); if(found_==NO) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);	scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		for(k=0;k<max_kprx;k++){
			zero(str_,sizeof str_);
      if(k==0) scrifld(z++,fm_os10,"Kassa bak");
      else if(k==max_kprx-1) scrifld(z++,fm_os10,"Kassa stuk");
      else {copy("Horeca",str_,6);stcli_d(&str_[6],(long)k,2,1);scrifld(z++,fm_os10,str_);}
      if(found_) scrfld(z++,93,11+k); else scrofld(z++,93,11+k,-1);
      scrifld(z++,fm_of4_2,&nm_vp[k]);
    }
    for(k=max_kprx;k<6;k++) z+=3;
		if(found_) scrfld(z++,93,30); else scrofld(z++,93,30,-1);
		if(found_) scrfld(z++,93,31); else scrofld(z++,93,31,-1);
		if(found_) scrfld(z++,93,25); else scrofld(z++,93,25,-1);
		key=scrupd(curs,0xE1);curs=6;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) return 2; // stop
		if(key==106) return 1; // skip
		if(key==5001){
			if(search(6,98)){found_=NO; curs=10; goto redo_art;}
			else found_=YES;
	  }
		else{
			if(search(6,0)){found_=NO; curs=10; goto redo_art;}
			else found_=YES;
		}
		if(found_ && *u(6,1)!=last_art_){
			for(k=0;k<max_kprx;k++){
				nm_vp[k]=*f(6,PrNrs[tb_ktypes[k]]);
				if(!(sys3894 & (1<<(tb_ktypes[k])))) nm_vp[k]*=1.+ *f(6,28)/100.;
				if(nm_vp[k]!=*f(6,PrNrs[tb_ktypes[k]])) nm_vp[k]=valu_cnv("EUR","EUR",(double)nm_vp[k],(double)0.01);
				if(k==0) *f(93,11+k)=folderlijn.prijs;
				else if(k==max_kprx-1 && *f(6,31)<=1) *f(93,11+k)=folderlijn.prijs;
			}
			last_art_=*u(6,1);goto redo_art;
		}

		if(key==108){
			if(fldlen(11,5) && lev_code_[0]){
				fasinit(11);*u(11,2)=lev_rec_;*u(11,3)=*u(6,1);mode_=1;lrec_=0;
				FOREVER{
					if(faskeyi(11,2,mode_)) break; mode_=2;
					if(*u(11,2)!=lev_rec_ || *u(11,3)!=*u(6,1)) break;
					if(cmpstr(s(11,5),lev_code_,fldlen(11,5))==0) {lrec_=*u(11,1);break;}
					if(*s(11,5)=='\0') lrec_=*u(11,1);
				}
				fasinit(11);
				if(lrec_){
					*u(11,1)=lrec_;fasgeti(11);
				  copy(lev_code_,s(11,5),fldlen(11,5));errnum=fasupd(11);
				}
				else{
					*u(11,2)=lev_rec_;*u(11,3)=*u(6,1);
					copy(lev_code_,s(11,5),fldlen(11,5));errnum=fasadd(11);
				}
			}
			break;
		}
	}
	return 0;
}
 
static UpdateLoginInfo()
{
  int16 z,key,curs=1;
 
  sysget(3004,10,FTPUsername);
	sysget(3014,10,FTPPaswoord);
  FOREVER{
    redo:;
    scrget(3,11);z=1;
		scrifld(z++,fm_us10,FTPUsername);
		scrifld(z++,fm_us10PW,FTPPaswoord);
    key=scrupd(curs,0xE0);curs=1;
    if(key==106) break;
    if(key==108){
			sysput(3004,10,FTPUsername);
      sysput(3014,10,FTPPaswoord);
      break;
    }
  }
	sysget(3004,10,FTPUsername);
	sysget(3014,10,FTPPaswoord);
	if(FTPUsername[0]=='\0' && FTPPaswoord[0]=='\0'){//serial en PW uit jms.ini nemen
    ExecJmsCommand(FTPUsername,sizeof FTPUsername,"GetIniKeyValue|JamaSettings|SerialNr");
    ExecJmsCommand(FTPPaswoord,sizeof FTPPaswoord,"GetIniKeyValue|JamaSettings|Password");
	}
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

static ele_len(nr_)
int16 nr_;
{
  int16 k=0;
  char *p;
								
  p=rec_ele(nr_);
  FOREVER{
    if(*p==ScheidingsTeken || *p==0x0D || *p==0x0A || *p=='\0') return k;
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
      if(*p==ScheidingsTeken || *p==0xD || *p=='\0') break;
      p++;
    }
    p++;
  }
  return p;
}

static float get_num(nr)                           /* read number starting at pos  */
int16 nr;
{
  int16 j=0,k=0,n;
  float val_=0,val1_;
  flag na_komma=NO,neg_get=NO;
  char *pos;
									
  pos=rec_ele(nr);
  FOREVER{
    if(*(pos+k)==ScheidingsTeken || *(pos+k)==0x0D) break;
    if(*(pos+k)==',') na_komma=YES;
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

static uint16 get_date(nr)              /* read date DD/MM/JJJJ starting at pos  */
int16 nr;
{
  int16 k=0,getal_[3],p_getal_;
  uint16 dt_=0;
  char *pos;
									
  zero(getal_,sizeof getal_);p_getal_=0;
  dt_=0; pos=rec_ele(nr); 
	if(ele_len(nr)==0) goto endsr;
	if(*pos<'0' || *pos>'9') goto endsr; // geen geldige datum
  FOREVER{
    if(*(pos+k)==ScheidingsTeken || *(pos+k)==0x0D) break;
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

  
static sear_promo()
{
  int16 j,z,key,mode_,start,fkey_,max_;
  uint16 a_rec_,l_rec_,groep_=0;

  a_rec_=*u(93,2);l_rec_=*u(93,3);
  groep_=*u(93,4);*u(93,1)=0;
  if(a_rec_) fkey_=1; else fkey_=2;
  zeros((char *)&tb[0],sizeof tb);
  start=0;max_=DIM_REC;mode_=1;
  FOREVER{
    scrnum=0;scrget(3,12);z=1;
    for(j=start;j<max_;j++){
      next:;
      if(tb[j].rec==0){
				if(faskeyi(93,fkey_,mode_)) {max_=j;break;}
				mode_=2;
				if(fkey_==1){
					if(a_rec_!=*u(93,2)) {max_=j;break;}
				}
				else{
					if(l_rec_ && *u(93,3)!=l_rec_){max_=j;break;}
					if(groep_ && *u(93,4)!=groep_) {goto next;}
				}
				if(dt_end && *u(93,7)>dt_end ) goto next;
				if(dt_beg && *u(93,8) && *u(93,8)<dt_beg) goto next;
				tb[j].rec=*u(93,1)+20000;
      }
      else {
				fasinit(93);*u(93,1)=tb[j].rec-20000;fasgeti(93);
      }
      fasinit(6);*u(6,1)=*u(93,2);fasgeti(6);
      fasinit(1);*u(1,1)=*u(93,3);fasgeti(1);
      j++;scrifld(z++,fm_ou3,&j);j--;
      scrofld(z++,6,2,-1);if(fldlen(93,10) && *u(93,10)) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);
      scrofld(z++,6,3,30);if(fldlen(93,10) && *u(93,10)) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);
      scrofld(z++,1,3,20);
      scrofld(z++,93,4,-1);
      if(j==start+15) break;
    }
    if(max_==0) {errnum=39;return NO;}
    else if(max_==1) break;
    j=0; scrifld(81,fm_uu3,&j);
    key=scrupd(1,0xA6);
    if(key==106) return NO;
    if((j>0 && j<=max_) && tb[j-1].rec) {tb[0].rec=tb[j-1].rec;break;}
    if(key==102) start-=16;
    if(key==103) {start+=16;if(start>=max_-16) start=max_-16;}
    if(start<0) start=0;
  }
  endsr:;
  fasinit(93);*u(93,1)=tb[0].rec-20000;fasgetu(93);
  return YES;
}

static DisplayMenuTitel(ypos_,tekst_,attrib_)
int ypos_;
char *tekst_,attrib_;
{
  int len_,beg_;
	char fmt_[40],dsptekst_[100];
   
	zero(dsptekst_,sizeof dsptekst_);dsptekst_[0]=' ';
  for(len_=0;len_<80;len_++){
		if(tekst_[len_]=='\0') break;
		dsptekst_[len_+1]=tekst_[len_];
	}
	len_+=1;dsptekst_[len_++]=' ';if(len_>80) len_=80;
	if(len_<15) len_=15;
  beg_=(80-len_)/2; if(beg_<1) beg_=1; 
	
	copy(VarTextFmt(80,0),fmt_,10);fmt_[2]=len_;
	scraddfield(100,beg_,ypos_,attrib_);scrifld(100,fmt_,dsptekst_);
}

static copy0(ps,pd,max_len_)
char *ps,*pd;
int16 max_len_;
{
  int16 fuval=0;
			
  while(*ps && max_len_--){
    *pd++=*ps++;
    fuval++;
  }
  *pd='\0';
  return fuval;
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

static zeros(pd,len)
char *pd;
int16 len;
{
  int16 k;
				
  for(k=0;k<len;k++) *(pd+k)='\0';
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
  if(stu_<=2) parmcall[1]=7; // bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3; // GEEN ADD
#endif
  if(stu_==6) parmcall[1]=0;
  parmcall[2]=0;
  parmcall[3]=0;
#ifdef STRAATKEY
  if(stu_==2) parmcall[4]=STRAATKEY;
#endif
  parmcall[7]=0x0C;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}

