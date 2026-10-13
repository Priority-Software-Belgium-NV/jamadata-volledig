/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0230GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0230dat
#define ovlcod DRK0230cod
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

// FLAGABT : Prijs met 4 decimalen + apart scherm 133 (533) 
// FLAGDWP : ook opmerking drukken op lijst 
// FLAGEPD : korting EUR na % rekenen en alle combinatioes toelaten 
// FLAGCOC : sem%=prijsfactor + apart scherm 133 en 61 (geen DRK) 
// FLAGGOU : brij_korting (9,23) is "prijstype" 
// FLAGVDW : korting EUR na % rekenen en alle combinatioes toelaten 
char ovldat[] = "drk0230  00:05 18/10/10 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_REC         2000
#define MAP_OFFERTE     "..\\Offerte\\"
#define DIM_TB_OFFERTE  200
#define DELIM           ';'

static char *fichenm[1]={"Prijsafspraak"};
static char *modenm[3]={"aan te passen","toe te voegen","te schrappen"};

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d(),valu_cnv();

static long GetRecNr();
static float get_num(nr);
static char *rec_ele();
static uint16 str2date(datestr_);
static double Round(bd_,bd_afr_);

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os18[]   = {7,0x88,18,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os7[]   = {7,0x88,7,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x20,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_of6_0[] = {6,0x94,6,0,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_4[] = {6,0xD4,5,4,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf4_4[] = {6,0xD4,4,4,0x70,0};
static char fm_uf4_2[] = {6,0xD4,4,2,0x70,0};
static char fm_uf4_0[] = {6,0xD4,4,0,0x60,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x60,0};
static char fm_uf2_4[] = {6,0xD4,2,4,0x60,0};
static char fm_uf504[] = {6,0xD4,5,4,0x30,0};
static char fm_uf302[] = {6,0xD4,3,2,0x30,0};
static char fm_uf2_2[] = {6,0xD4,2,2,0x70,0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_us1X[]  = {9,0xC8,1,0,1,0,'X','X',0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_uref[]  = {11,0xC8,8,0,1,0,'A','Z','0','9',0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

static int16 stu,free,p_tb,only_dsp;
static unsigned SpoolFileNr;
static char nm_20[20],nm_15[15],oldnm[50],fmt[40],buf750[750],nm_merk[50],nm_lev[50],filnam[80],*p_data;
static uint16 inq_klt,inq_art,inq_lev,inq_groep,inq_merk,dt_p_upd;
static char inq_page='N', inq_detail='N',klt_str[101], only_kprx='N',prt_akpr='N',ref_offerte[10];
static char lev_res[60],klt_res[60],art_res[60],prt_kort='J',disp_kon,prt_det='J';
static float contr_prx,echt_prx,kort_pct,semest_pct,kort_abs,accijns;
static float factor[4],offset[4],min_q,sys2830;
static double prx_afrond;
static flag sear_stt,lvcd,klcd,chk_btoeg=NO,fld_hlkort;
static flag sys3876,sys3894;
static int16 fld_nr[8]={6,22,7,8,20,21,23,24}; // pas op met FLAGGOU als ge hier iets wijzigt
static struct{
  long rec;/* 0-9999 : artikel , 20000-65000 contract */
  uint16 type;
} tb[DIM_REC];
 
static float tb_val[18][10][9];/* 18 lijnen (contracten) x (10 x 5) waardes */
static uint16 *pu_9_2,*pu_9_3,*pu_2_1,*pu_6_1;
static int16 prt2pdf;
static char seqo_str[2500];
static long seqo_pos,value,*pl_80_1;
static int16 seqo_len,seqo_mode,pos;
static struct{
  char filname[30];
	char referentie[15];
	char klantstu[200];
  uint16 datum;
} tb_offerte[DIM_TB_OFFERTE];
static int q_offertes;

extern int16 ilength; // XLS
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi,prt2xls; // XLS
#include "Std\XlsFunc.c"

ovlcod(parmval)
int16 parmval;
{
  int16 k,key;
  char choice;
									
  initload();
  stu=9;
  for(k=0;k<8;k++) if(fldlen(9,fld_nr[k])==0) fld_nr[k]=0;
  copy(fichenm[0],nm_20,20);
  if(parmval==1){                                  /* automatisch afdrukken voor 1 klant vanuit ovl217 */
    fasinit(2);*u(2,1)=*u(27,5);fasgeti(2);inq_klt=*u(27,5);
    print(YES);
    ovlexit(-1);
  }
  if(parmval==2){                                  /* prijsafspraken klant/artikel vanuit ovl0x19 */
		if(*s(27,4)=='A') inq_art=*u(27,6);/* 1 artikel */
	  else inq_klt=*u(27,5);/* 1 klant */
		fasinit(6);*u(6,1)=inq_art; if(*u(6,1)) fasgeti(6);
    fasinit(2);*u(2,1)=inq_klt; if(*u(2,1)) fasgeti(2);
		only_dsp=YES;
		if(inq_art){
			 if(fill_tabel(7)==0) dsp_tabel(YES); 
			 else errnum=39;
		}
		else{
      if(fill_tabel(2)==0) dsp_tabel(NO); 
	  	else errnum=39;
	  }
    ovlexit(-1);
  }
  FOREVER{
    scrget(2,88);fasunlck(0);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_menu,&choice);
    key=scrupd(3,0x0401);
    if(key==101) break;
    if(key==111) ovlexit(210);
		fasunlck(-1);
    switch(choice){
      case '1':upd_add(0);break;
      case '2':upd_add(1);break;
      case '3':kill();break;
      case '4':print(NO);break;
      case '9':upd_k_pr();break;
      case 'A':globkil();break;
      case 'K':KltContractCopy();break;
      case 'L':ArtContractCopy();break;
      case 'U':clean_up();break;
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}

static upd_add(mode_)
int16 mode_;
{
  int16 curs=1,key,z;
  char choice;
 
  copy(modenm[mode_],nm_15,15);
  FOREVER{
    if(mode_==1) scrget(2,274); else scrget(2,132);
    z=1;
    scrifld(z++,fm_os20,nm_15);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0481);
    if(key==101) break;
    if(key==111) ovlexit(-1);
    switch(choice){
      case '1': if(mode_==0) upd_single(); else add_single();break;
      case '2': if(mode_==0) upd_mult(NO); else add_mult();break;
      case '3': if(mode_==0) upd_mult(YES); else add_gr_mult();break;
      case '4': if(mode_==1 && ovltest(266)) add_via_offerte();break;
      default : errnum=34; break;
    }
  }
}

static upd_single()
{
  int16 k,clr_=YES;
 
  FOREVER{
    redo:;
    if(select_kon(nm_20,modenm[0],0xFF,YES)) break;
    fasinit(9);
    *pu_9_2=*pu_2_1;
    *pu_9_3=*pu_6_1;
    if(fldlen(9,18)) {
			if(inq_lev) *u(9,18)=inq_lev;
			else{
				if(inq_merk) *u(9,18)=30000+inq_merk;
			}
		}
    if(fldlen(9,19)) *u(9,19)=inq_groep;
    k=sear_contr();
    if(errnum || k==NO){clr_=NO; goto redo;}

    if(!fichupd(1)) break;
  }
}

static upd_mult(mode_) // 0=klant  1=artikel
int16 mode_;
{
	only_dsp=NO;
  FOREVER{
redo:
		if(mode_==0){
      if(select_kon("Alle prijsafspraken van ……n klant",modenm[0],0x1,YES)) break;
      if(fill_tabel(2)) {errnum=39;goto redo;}
			dsp_tabel(NO);
		}
		else{
      if(select_kon("Alle prijsafspraken van ……n artikel",modenm[0],0x2,YES)) break;
      if(fill_tabel(7)) {errnum=39;goto redo;}
			dsp_tabel(YES);
		}
 
  }
}
 
static fill_tabel(a_key_)
int16 a_key_;
{
  int16 j,k,n,len_;

  len_=sizeof tb[0];
  zeroL((char *)&tb[0],sizeof tb);p_tb=0;
	if(a_key_==7){// afspraken van 1 artikel
    fasinit(9);*pu_9_2=1;*pu_9_3=inq_art;
    _fill_tab(7,0); 
	  fasinit(2);j=0;/* sorteren volgens klant */
		FOREVER{
			if(j>=p_tb-1) break;
			if(faskeyi(2,2,2)) break;
			for(k=j;k<p_tb;k++){
				if(*u(2,1)==tb[k].type){
					if(k!=j){
						copy((char *)&tb[k],art_res,len_);
						for(n=k-1;n>=j;n--) copy((char *)&tb[n],(char *)&tb[n+1],len_);
						copy(art_res,(char *)&tb[j],len_);
					}
					j++;break;
				}
			}
		}	
		for(j=0;j<p_tb;j++) tb[j].type=0;/* terug juist zetten van type */
	}
	else{
		fasinit(9);*pu_9_2=*pu_2_1;*pu_9_3=inq_art;
		_fill_tab(1,0);
		fasinit(6);j=0;/* sorteren artikels */
		FOREVER{
			if(j>=p_tb-1) break;
			if(faskeyi(6,a_key_,2)) break;
			for(k=j;k<p_tb;k++){
				if(*pu_6_1==tb[k].type){
					if(k!=j){
						copy((char *)&tb[k],art_res,len_);
						for(n=k-1;n>=j;n--) copy((char *)&tb[n],(char *)&tb[n+1],len_);
						copy(art_res,(char *)&tb[j],len_);
					}
					j++;break;
				}
			}
		}
		for(j=0;j<p_tb;j++) tb[j].type=0;/* terug juist zetten van type */
		if(inq_art==0){
			fasinit(9);*pu_9_2=*pu_2_1;*u(9,18)=1;_fill_tab(2,1);/* lev. + groep */
			fasinit(9);*pu_9_2=*pu_2_1;*u(9,18)=1;_fill_tab(2,2);/* leverancier */
			fasinit(9);*pu_9_2=*pu_2_1;*u(9,18)=0;*u(9,19)=1;_fill_tab(2,3);/* groep */
		}
		if(fldlen(2,18)){
			if(fldlen(2,18)) tb[p_tb].rec=0xFFFFFF;
			tb[p_tb].type=4;
			p_tb++;
		}
	}
	endsr:;
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
    if(faskeyi(9,keyno_,mode_)) break;mode_=2;
		if(keyno_==7){ // alle afspraken van 1 artikel
  		if(inq_art!=*u(9,3)) break;
		}
    else{
			if(*pu_2_1!=*pu_9_2) break;
			if(nr_==0){
				if(inq_art && inq_art!=*u(9,3)) break;
				else if(*u(9,3)==0) goto next;
			}
		}
    if(nr_==1 && *u(9,19)==0) goto next;
    if(nr_==2 && *u(9,19)!=0) goto next;
    if(nr_==3 && *u(9,18)!=0) break;
    if(testinhoud()==YES) {
      if(nr_ && first){
				tb[p_tb].rec=0xFFFFFF;tb[p_tb].type=nr_;p_tb++;
				first=NO;
      }
      tb[p_tb].rec=GetRecNr(9)+20000L;
      if(nr_>0) tb[p_tb].type=nr_;
      else{
				if(keyno_==7) tb[p_tb].type=*u(9,2); else tb[p_tb].type=*pu_9_3;/* tydelijk rec. invullen voor sort */
			}
    }
    else goto next;
  }
}

static dsp_tabel(art_mode_)
int16 art_mode_;
{
  int16 j,g,k,n,pos_,key,z,start=0,curs=1,dcurs_,o_start,curspos_;
  char *pd;
	
	if(art_mode_){
		fasinit(6);*u(6,1)=inq_art;fasgeti(6);
    pd=&klt_str[0];
    for(k=2;k<=3;k++){
      if(k<3) pd+=add_str(pd,30,6,k,' ');
      else pd+=add_str(pd,30,6,k,'\0');
    }
	}
	else{
		pd=&klt_str[0];
		for(k=3;k<=6;k++){
			if(k!=5){
				if(k<6) pd+=add_str(pd,30,2,k,',');
				else pd+=add_str(pd,30,2,k,'\0');
			}
		}
  }
  ld_tb_val(0,p_tb);
  FOREVER{
redo:;
		k=133;
#if FLAGCOC
		k=357;
#endif
#if FLAGGOU
		k=524;
#endif
#if FLAGABT
		k=533;
#endif
    scrnum=0;scrget(2,k);z=1;
		if(art_mode_){scraddf(200,0,0,0);scrifld(200,VarTextFmt(8,0),"Artikel");} // woord klant: wegdoen
    scrifld(z++,fm_os63,klt_str);
    for(k=start;k<p_tb;k++){
      dsp_1_lin(z,k,start,0,art_mode_);z+=6;
      if(k==start+17) break;
    }
		dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0x3A6);curs=1;curspos_=fldcurs;
		if(key==15 && only_dsp){only_dsp=NO;goto redo;}
    if(key==106) ld_tb_val(start,p_tb);
    for(n=start;n<k;n++){
#if !FLAGEPD  && !FLAGVDW// alle combinaties toelaten 
      j=0; for(g=1;g<5;g++) if(g!=2 && tb_val[n-start][0][g]) j++;
      if(j==2 && (tb_val[n-start][0][1] && tb_val[n-start][0][4]));
      else if(j>1) {errnum=72;curs=3+(n-start)*5; goto redo;}
#endif
    }
    if(key==108) {wr_tb_val(start,p_tb);break;}
    if(key==109){
      wr_tb_val(start,p_tb);
      curs=curspos_;
      pos_=(curspos_-2)/6;
      if(tb[start+pos_].rec && tb[start+pos_].rec!=0xFFFFFF){
				dsp_1_lin(0,start+pos_,0,YES,art_mode_);/* enkel string samenstellen */
				if(NO /* fldlen(9,88)*/){
					dsp_detail(pos_); wr_tb_val(start,p_tb);
				}
				else{
					if(tb[start+pos_].rec>20000L){
						fasinit(9);SetRecNr(9,(long)(tb[start+pos_].rec-20000L));fasgeti(9);
						fichupd(1);
					}
				}
      }
      ld_tb_val(start,p_tb);
    }
		if(key==110){
      wr_tb_val(start,p_tb);
      curs=curspos_;
      pos_=(curspos_-2)/6;
      if(tb[start+pos_].rec && tb[start+pos_].rec!=0xFFFFFF){
				fasinit(9);
				if(tb[start+pos_].rec>20000L){SetRecNr(9,(long)(tb[start+pos_].rec-20000L));fasgeti(9);}
				if(IsWisKortingAfspraak()==NO){
					zero(tb_val[pos_],sizeof tb_val[0]);
					tb_val[pos_][0][2]=(float)(0.0001);
					wr_tb_val(start,p_tb);
				}
      }
      ld_tb_val(start,p_tb);
    }
    o_start=start;
    if(key==102) start-=18;
    if(key==103) {start+=18;if(start>=p_tb-18) start=p_tb-18;}
    if(start<0) start=0;
    if(o_start!=start) {wr_tb_val(o_start,p_tb);ld_tb_val(start,p_tb);}
  }
	DeleteEmptyAfspraken(p_tb);
  return NO;
}

static DeleteEmptyAfspraken(max_)
int16 max_;
{
	int16 k;

fasunlck(-2);
  for(k=0;k<max_;k++){
		if(tb[k].rec<=20000L || tb[k].rec==0xFFFFFF) continue;
    fasinit(9); SetRecNr(9,(long)(tb[k].rec-20000L));if(fasgetu(9)) continue;
		if(testinhoud()==NO && contract()){	faskill(9);tb[k].rec=0L;	}
  }
	fasunlck(-1);
}




static dsp_detail(pos_)
{
  int16 j,k,g,z,curs=3,key;
 
  FOREVER{
    redo:;
    scrget(2,134);z=1;
    scrofld(z++,2,3,-1);
    scrifld(z++,fm_os40,oldnm);
    for(k=0;k<10;k++){
      if(k==0 || fldlen(9,88+k*5)){
				if(k) scrifld(z++,fm_uf6_0,&tb_val[pos_][k][0]); else z++;
				scrifld(z++,fm_uf2_2,&tb_val[pos_][k][1]);
				scrifld(z++,fm_uf2_2,&tb_val[pos_][k][2]);
				scrifld(z++,fm_uf2_4,&tb_val[pos_][k][3]);
				scrifld(z++,fm_uf4_4,&tb_val[pos_][k][4]);
        if(k && fldlen(9,77+k-1)) scrifld(z++,fm_uf4_4,&tb_val[pos_][k][5]); else z++; // prijs op datum 10/12
      }
    }
    key=scrupd(curs,0x80);curs=3;
    for(k=0;k<10;k++){
#if !FLAGEPD  && !FLAGVDW// alle combinaties toelaten 
      j=0; for(g=1;g<5;g++) if(g!=2 && tb_val[pos_][k][g]) j++;
      if(j==2 && (tb_val[pos_][k][1] && tb_val[pos_][k][4]));
      else if(j>1) {errnum=72;curs=3+(k*5); goto redo;}
#endif
    }
    for(k=1;k<9;k++){/* aantal moet in stijgende volgorde zijn */
      if(fldlen(9,88+k*5)){
				if(tb_val[pos_][k][0] && tb_val[pos_][k][0]<=tb_val[pos_][k-1][0]){
					errnum=52;curs=3+k*5;goto redo;
				}
      }
    }
    if(key==108) break;
  }
}
 
static ld_tb_val(rpos,max_)
int16 rpos,max_;
{
  int16 j,k,n;
 
  zeros((char *)tb_val,sizeof tb_val);
  for(k=0;k<18;k++){
    if((rpos+k)>=max_) break;
    if(tb[rpos+k].rec!=0xFFFFFF && tb[rpos+k].rec>20000L){
      fasinit(9);SetRecNr(9,(long)(tb[rpos+k].rec-20000L));fasgeti(9);
      for(j=0;j<8;j++) if(fld_nr[j]) tb_val[k][0][j+1]=*f(9,fld_nr[j]);
      for(j=0;j<9;j++){
				if(fldlen(9,88+j*5)>0){
					for(n=0;n<5;n++){
						tb_val[k][j+1][n]=*f(9,88+(j*5)+n);
					}
					if(fldlen(9,77+j)) tb_val[k][j+1][5]=*f(9,77+j); // prijs op datum
				}
      }
    }
    else if(tb[rpos+k].rec==0xFFFFFF && tb[rpos+k].type==4){
      if(fldlen(2,18)) tb_val[k][0][1]=*f(2,18);
      if(fldlen(2,56)) tb_val[k][0][2]=*f(2,56);
    }
  }
}
 
static dsp_1_lin(z,j,start,mode_,art_mode_)/* mode_=1 : enkel string samenstellen */
int16 z,j,start,mode_,art_mode_;
{
  char *pd,byte_=0;
	
  fasinit(9);pd=&oldnm[0];
  if(tb[j].rec!=0xFFFFFF) {
		if(tb[j].rec>20000L){SetRecNr(9,(long)(tb[j].rec-20000L));if(tb[j].rec) fasgeti(9);}
		else {if(tb[j].type==0) *u(9,3)=tb[j].rec; else *u(9,19)=tb[j].rec;}
    switch(tb[j].type){
      case 0 : if(art_mode_){
				        fasinit(2);*u(2,1)=*u(9,2);fasgeti(2);
	              pd+=add_str(pd,30,2,3,'\0');
							 }
							 else{
				        fasinit(6);*pu_6_1=*pu_9_3;fasgeti(6);
	              pd+=add_str(pd,10,6,2,' ');pd+=add_str(pd,30,6,3,'\0');
							 }
	       break;
      case 1 : 
				 fasinit(1);*u(1,1)=*u(9,18);if(*u(1,1)>30000) *u(1,1)-=30000; fasgeti(1); // merk zit op +30000
	       fasinit(52);*u(52,1)=*u(9,19);fasgeti(52);
	       pd+=add_str(pd,20,1,3,'-');
	       stcli_d(pd,(long)*u(52,1),2,0);pd+=2;*(pd++)=' ';
	       pd+=add_str(pd,15,52,14,'\0');
	       break;
      case 2 : fasinit(1);*u(1,1)=*u(9,18);if(*u(1,1)>30000) *u(1,1)-=30000; fasgeti(1); // merk zit op +30000
	       pd+=add_str(pd,40,1,3,'\0');
	       break;
      default: fasinit(52);*u(52,1)=*u(9,19);fasgeti(52);
	       stcli_d(pd,(long)*u(52,1),2,0);pd+=2;*(pd++)=' ';
	       pd+=add_str(pd,30,52,14,'\0');
	       break;
    }
    if(mode_) goto endsr;
    scrifld(z,fm_os40,oldnm);
    if(kon_info(j-start,1)) scrchat(z++,0x2); else z++;
		if(IsWisKortingAfspraak()==YES){
			scrifld(z++,fm_us1X,&byte_);
			scrifld(z++,fm_os20,"*** GEEN KORTING ***");scrchat(z-1,0xB);z+=3;
		}
		else{
			if(tb[j].rec || tb[j].type){
				scrifld(z++,fm_uf2_2,&tb_val[j-start][0][1]);
#if FLAGABT // prijs/korting met 4 decimalen 
        if(tb[j].type==0){
     	    scrifld(z++,fm_uf2_4,&tb_val[j-start][0][3]); 
			 	  scrifld(z++,fm_uf4_4,&tb_val[j-start][0][4]); // 4 cijfers na komma
				} else z+=2;
				scrifld(z++,fm_uf2_2,&tb_val[j-start][0][2]); 
				z++; // if(fld_hlkort) scrifld(z++,fm_uf3_2,&tb_val[j-start][0][6]); else z++;
#else
				if(tb[j].type==0) scrifld(z++,fm_uf4_2,&tb_val[j-start][0][4]);
				else z++;
#if FLAGGOU
				scrifld(z++,fm_u_05,&tb_val[j-start][0][7]); // afwijkend prijstype
#else
				if(fld_hlkort) scrifld(z++,fm_uf3_2,&tb_val[j-start][0][5]); else z++;
#endif
				scrifld(z++,fm_uf2_2,&tb_val[j-start][0][2]); 
				if(fld_hlkort) scrifld(z++,fm_uf3_2,&tb_val[j-start][0][6]); else z++;
#endif
			} else z+=5; // geschrapt
		}
  }
  else {
    switch(tb[j].type){
      case 1 : scrifld(z,fm_os40,"Leverancier/merk + groep");break;
      case 2 : scrifld(z,fm_os40,"Leverancier/merk");break;
      case 3 : scrifld(z,fm_os40,"Groep");break;
      default: scrifld(z,fm_os40,"Algemene korting op klantenfiche");break;
    }
    scrchat(z++,0x8);
    if(tb[j].type==4){
      scrifld(z++,fm_uf2_2,&tb_val[j-start][0][1]);
      z++;
      z++;
      if(fldlen(2,56)) scrifld(z++,fm_uf2_2,&tb_val[j-start][0][2]); else z++;
      z++;
    }
    else z+=5;
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

static add_single()
{
  fasinit(2);
  FOREVER{
    fasinit(1);fasinit(6);fasinit(9); *pu_9_2=*pu_2_1;
    if(!fichupd(2)) break;/* fasadd */
  }
}

static add_mult()
{
  int16 j,g,n,k,curs,z,key,mode_,pos_,start,max_,o_start,curspos_;
  char *pd;
  uint16 last_fnd,rec_;

  zeroL((char *)&tb[0],sizeof tb);fasinit(6);p_tb=0;max_=0;
  FOREVER{
    if(select_kon("Lijst artikelen",modenm[1],0xD,YES)) break;
    pd=&klt_str[0];
    for(k=3;k<=6;k++){
      if(k!=5){
				if(k<6) pd+=add_str(pd,30,2,k,',');
				else pd+=add_str(pd,30,2,k,'\0');
      }
    }
		zeroL((char *)&tb[0],sizeof tb);
    zeros((char *)tb_val,sizeof tb_val);
    start=0;max_=DIM_REC;mode_=1;curs=2;last_fnd=0;

		//fasinit(6);max_=0;
  //  FOREVER{
		//	next_art:;
		//	if(faskeyi(6,2,2)) break;
		//	if(inq_lev && *u(6,7)!=inq_lev) goto next_art;
		//	if(inq_merk && *u(6,101)!=inq_merk) goto next_art;
		//	if(groep && *u(6,9)!=groep)  goto next_art;
		//	tb[max_].rec=*pu_6_1;tb[max_].type=0;
		//	fasinit(9);*pu_9_2=*pu_2_1;*pu_9_3=*pu_6_1;
		//	if(faskeyi(9,1,0)==0)	tb[max_].rec=GetRecNr(9)+20000L;
		//	last_fnd=*u(6,1);
		//	max_++; if(max_>=DIM_REC) break;
		//}

    FOREVER{
redo:;
		  k=133;
#if FLAGCOC
		  k=357;
#endif
#if FLAGABT
		  k=533;
#endif
      scrnum=0;scrget(2,k);z=1;
      scrifld(z++,fm_os63,klt_str);
      for(j=start;j<start+18;j++){
				next:;
				if(tb[j].rec==0){
					if(faskeyi(6,1,mode_)) {max_=j;p_tb=j;break;}
					mode_=2;
					last_fnd=*pu_6_1;
					if(inq_lev && *u(6,7)!=inq_lev) goto next;
					if(inq_merk && *u(6,101)!=inq_merk) goto next;
					if(inq_groep && *u(6,9)!=inq_groep)  goto next;
					tb[j].rec=*pu_6_1;tb[j].type=0;
					fasinit(9);*pu_9_2=*pu_2_1;*pu_9_3=*pu_6_1;
					zeros((char *)tb_val[j-start],sizeof tb_val[0]);
					if(faskeyi(9,1,0)==0){
						tb[j].rec=GetRecNr(9)+20000L;
						for(k=0;k<8;k++) if(fld_nr[k]) tb_val[j-start][0][k+1]=*f(9,fld_nr[k]);
						for(k=0;k<9;k++){
							if(fldlen(9,88+k*5)>0){
								for(n=0;n<5;n++){
									tb_val[j-start][k+1][n]=*f(9,88+(k*5)+n);
								}
								if(fldlen(9,77+k)) tb_val[j-start][k+1][5]=*f(9,77+k); // prijs op datum
							}
						}
					}
				}
				else {
					fasinit(6);
					if(tb[j].rec>20000L){
						fasinit(9);SetRecNr(9,(long)(tb[j].rec-20000L));fasgeti(9);*pu_6_1=*pu_9_3;
					}
					else *pu_6_1=tb[j].rec;tb[j].type=0;
					fasgeti(6);
				}
				rec_=*u(6,1);
				dsp_1_lin(z,j,start,0,NO);z+=6;
        fasinit(6);*u(6,1)=rec_;fasgeti(6);
//
//pd=&oldnm[0]; pd+=add_str(pd,10,6,2,' ');pd+=add_str(pd,30,6,3,'\0');
//				scrifld(z,fm_os40,oldnm);
//				if(kon_info(j-start,0)) scrchat(z++,0x2); else z++;/* contract */
//				scrifld(z++,fm_uf2_2,&tb_val[j-start][0][1]);
//			//      scrifld(z++,fm_uf2_4,&tb_val[j-start][0][3]); 
//				scrifld(z++,fm_uf4_2,&tb_val[j-start][0][4]);
//				if(fld_hlkort) scrifld(z++,fm_uf3_2,&tb_val[j-start][0][5]); else z++;
//				scrifld(z++,fm_uf2_2,&tb_val[j-start][0][2]);
//				if(fld_hlkort) scrifld(z++,fm_uf3_2,&tb_val[j-start][0][6]); else z++;
      }
      if(max_==0) {errnum=39;break;}
      if(start && start==max_){start-=18;goto redo;}
      key=scrupd(curs,0x3A6);curs=2;curspos_=fldcurs;
      if(key==106) break;
      for(k=start;k<j;k++){
#if !FLAGEPD  && !FLAGVDW// alle combinaties toelaten 
				n=0; for(g=1;g<5;g++) if(g!=2 && tb_val[k-start][0][g]) n++;
				if(n==2 && (tb_val[k-start][0][1] && tb_val[k-start][0][4]));
				else if(n>1) {errnum=72;curs=3+(k-start)*6; goto redo;}
#endif
      }
      if(key==108){wr_tb_val(start,max_);break;}
      if(key==109){
				wr_tb_val(start,max_);
				curs=curspos_;
				pos_=(curspos_-2)/6;
				if(tb[start+pos_].rec && tb[start+pos_].rec!=0xFFFFFF){
					dsp_1_lin(0,start+pos_,0,YES,NO);/* enkel string samenstellen */
					if(fldlen(9,88)) dsp_detail(pos_);
					else{
						if(tb[start+pos_].rec>20000L){
							fasinit(9);SetRecNr(9,(long)(tb[start+pos_].rec-20000L));fasgeti(9);
							fichupd(1);
						}
					}
				}
				ld_tb_val(start,max_);
      }
			if(key==110){
				wr_tb_val(start,max_);
				curs=curspos_;
				pos_=(curspos_-2)/6;
				if(tb[start+pos_].rec && tb[start+pos_].rec!=0xFFFFFF){
					fasinit(9);
					if(tb[start+pos_].rec>20000L){SetRecNr(9,(long)(tb[start+pos_].rec-20000L));fasgeti(9);}
					if(IsWisKortingAfspraak()==NO){
						zero(tb_val[pos_],sizeof tb_val[0]);
						tb_val[pos_][0][2]=(float)(0.0001);
						wr_tb_val(start,max_);
					}
				}
				ld_tb_val(start,max_);
			}
      o_start=start;
      if(key==102) start-=18;
      if(key==103) {start+=18;if(start>=max_-18) start=max_-18;}
      if(start<0) start=0;
      if(o_start!=start) {wr_tb_val(o_start,max_);ld_tb_val(start,max_);}
      fasinit(6);*pu_6_1=last_fnd;fasgeti(6);
    }
		DeleteEmptyAfspraken(max_);
  }
	
  endsr:;
}

static add_via_offerte()
{
  int16 z=1,curs=1,key,k,prxnr;
  char txt_[100],ptype_off_,stuks_[2];
	float q_bak_;

	fasinit(2);
  FOREVER{
redo:;
		scraddf(-1,0,0,0);z=1;
	  DisplayMenuTitel(4,"Toevoegen prijsafspraken a.h.v. bestaande offerte",0xA);
		scraddf(z++,8,4,0); scraddf(z++,8,12,2);
    scraddf(z++,10,4,0); scraddf(z++,10,25,2);
    scraddf(z++,23,1,8);scraddf(z++,23,11,8);
    z=1;
		scrifld(z++,fm_os63,"Klant : ");scrfld(z++,2,3);scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		scrifld(z++,fm_os63,"Referentie offerte : ");
    scrifld(z++,fm_uref,ref_offerte);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,VarTextFmt(9,0)," F1 stop ");scrifld(z++,VarTextFmt(12,0)," F8 zoek op ");
    key=scrupd(curs,0x81);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) return NO;
		if(key==5002){
			if(search(2,98)){curs=2;goto redo;}
	  }
		if(search(2,0)){curs=2;goto redo;}
		inq_klt=*u(2,1);
		if(key==5001){
			if(SearchOfferte()) {curs=4;goto redo;}
	  }
    if(ref_offerte[0]=='\0') {curs=4;errnum=38; goto redo;}
    if(key==108 || key==5001){
      zero(filnam,sizeof filnam);k=0;
      k+=copy0(MAP_OFFERTE,&filnam[k],20);
      k+=copy0(ref_offerte,&filnam[k],sizeof ref_offerte);
      k+=copy0(".csv",&filnam[k],5);
      fasclos(-2);
      errnum=fasopen(filnam,1);if(!errnum) break;
    }
  }
	fasinit(80);
  zero(seqo_str,sizeof seqo_str);pos=0;
  if(read_rec(0)) {fasclos(-2); return NO;}
  fasinit(2);*u(2,1)=get_num(2);if(fasgeti(2)) {fasclos(-2); return NO;}
	ptype_off_=*s(2,26); if(ptype_off_=='\0') ptype_off_='0';
	fasinit(2);*u(2,1)=inq_klt;fasgeti(2);
	if(*s(2,26)=='\0') *s(2,26)='0'; fasupd(2);
	if(ptype_off_!=*s(2,26)){
		zero(txt_,sizeof txt_);
		k=copy0("Het prijstype van de offerte (",txt_,35);txt_[k++]=ptype_off_;
		k+=copy0(") is NIET hetzelfde als dit van de klant (",&txt_[k],50);txt_[k++]=*s(2,26);copy0(")!",&txt_[k],2);
		DisplayWarning(txt_,61,0);
		fasclos(-2); errnum=52; return NO;
	}
	DisplayWarning("Wenst U echt deze offerte toe te voegen aan de prijsafspraken?",605,1);
	fasinit(2);*u(2,1)=inq_klt;fasgeti(2);
  prxnr=*s(2,26)-'0';
  if(prxnr<0 || prxnr>9) prxnr=0;
  if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;

	FOREVER{
		next:;
    if(read_rec(1)) break; z=0;
		zero(stuks_,sizeof stuks_); q_bak_=0;
    fasinit(6);*u(6,1)=get_num(z++);if(fasgeti(6)) goto next;
		fasinit(9);*pu_9_2=*pu_2_1;*pu_9_3=*pu_6_1;
		if(faskeyi(9,1,0)) fasinit(9);
		*pu_9_2=*pu_2_1;*pu_9_3=*pu_6_1;
    z++; z++; z++; z++; 
    *f(9,8)=Round((double)(get_num(z++)),prx_afrond); if(Round((double)(*f(9,8)),prx_afrond)==Round((double)(*f(6,PrNrs[prxnr])),prx_afrond)) *f(9,8)=0;
    z++;
    *f(9,6)=get_num(z++); // kort%
    z++; 
    *f(9,20)=get_num(z++); if(*f(6,37)) *f(9,20)/= *f(6,37)/100; // hl korting
    z++; 
    z++; 
    z++; 
    z++; 
    z++; 
    *f(9,22)=get_num(z++); // sem %
    *f(9,21)=get_num(z++);if(*f(6,37)) *f(9,21)/= *f(6,37)/100; // sem hl korting 
		z+=11;
		if(fldlen(9,23)) *f(9,23)=get_num(z); z++; // brij tussenkomst %
    if(fldlen(9,24)) *f(9,24)=get_num(z); z++; // brij tussenkomst EUR
		z++; // brij totaal
		get_str(stuks_,z++,1);  // stuksflag
		q_bak_=get_num(z++); // aantal/bak
		if(stuks_[0]=='S' && q_bak_>1) {
			*f(9,8)=Round((double)(*f(9,8)*q_bak_),prx_afrond); if(Round((double)(*f(9,8)),prx_afrond)==Round((double)(*f(6,PrNrs[prxnr])),prx_afrond)) *f(9,8)=0;
		}


		for(k=0;k<8;k++) if(*f(9,fld_nr[k])) break;
		if(k<8){
			if(fldlen(9,1)==4){if(*l(9,1)) fasupd(9); else fasadd(9);}
			else {if(*u(9,1)) fasupd(9); else fasadd(9);}
		}
  }
  fasflush(0);
  fasclos(-2); only_dsp=NO;
	if(fill_tabel(1)==NO) dsp_tabel(NO);
  endsr:;
  return YES;
}

static SearchOfferte()
{
	int16 j,k,curs=1,key,z,start_,d_lin_scr=17,nr_,q_,lijnpos;
	uint16 funckeys;
	char str_[150];

	zeroL((char *)&tb_offerte[0].filname[0],sizeof tb_offerte); q_offertes=0;
	zero(filnam,sizeof filnam);k=0;
  k+=copy0(MAP_OFFERTE,&filnam[k],20);
  k+=copy0(ref_offerte,&filnam[k],sizeof ref_offerte);
  k+=copy0("*.csv",&filnam[k],5);
	fasclos(-2);fasinit(80);
  fasopen(filnam,102);/* eerste call voor dir */
  FOREVER {
		fasinit(80);
    fasinfo(80,204);                            /* ophalen antwoord van dir */
    if (*s(80,1)=='\0') break;
    copy(s(80,1),tb_offerte[q_offertes++].filname,14);
    if(q_offertes>=DIM_TB_OFFERTE) break;
  }
	if(q_offertes==0) return YES;

  for(j=0;j<q_offertes;j++) {
	  zero(filnam,sizeof filnam);k=0;
    k+=copy0(MAP_OFFERTE,&filnam[k],20);
		k+=copy0(tb_offerte[j].filname,&filnam[k],sizeof (tb_offerte[0].filname));
    fasclos(-2);
    errnum=fasopen(filnam,1);if(errnum) break;

		fasinit(80);fasinit(2);
		zero(seqo_str,sizeof seqo_str);pos=0;
		if(read_rec(0)) {fasclos(-2); return NO;}
		z=0;
		get_str(tb_offerte[j].referentie,z++,10);
		zero(str_,sizeof str_);get_str(str_,z++,10); tb_offerte[j].datum=str2date(str_);
		*u(2,1)=get_num(z++);
		for(k=2;k<=7;k++) get_str(s(2,k),z++,fldlen(2,k));
		copy(s(2,1),tb_offerte[j].klantstu,s(2,8)-s(2,1));
    fasclos(-2);
	}
  
	  start_=0; nr_=0; lijnpos=0; scrnum=0;
	scraddf(-1,0,0,0);
	FOREVER{
    redo:;
    scrnum=0;scrget(2,330);z=1; q_=0;
    funckeys=0x80A1;
		if(start_>0) {
      scraddpicto(1,0,75,1,4,2,18,0,4,"up"); 
      funckeys+=2;
    }
		if((start_+d_lin_scr)<q_offertes) {
      scraddpicto(2,0,75,21,4,2,13,0,4,"down"); 
      funckeys+=4;
    }
    for(k=start_;k<(start_+d_lin_scr);k++){
      if(k>=q_offertes)	break;
      k++; scrifld(z++,fm_ou3,&k); k--;
			scrifld(z++,VarTextFmt(8,0),&tb_offerte[k].referentie);
			zero(str_,sizeof str_);
			copy(tb_offerte[k].klantstu,s(2,1),s(2,8)-s(2,1));
      j=copy0(s(2,3),&str_[0],fldlen(2,3));j+=copy0(" - ",&str_[j],3); j+=copy0(s(2,4),&str_[j],fldlen(2,4));str_[j++]='-';j+=copy0(s(2,6),&str_[j],fldlen(2,6));
      scrifld(z++,VarTextFmt(50,0),str_);  if(q_==(lijnpos+1)) scrchat(z-1,0x8); else scrchat(z-1,0xFF);
			scrifld(z++,fm_odat,&tb_offerte[k].datum);
			scraddpicto(11+k-start_,z-1,1,0,2,1,540,0,0,"schrap"); 
    }
    scrifld(69,fm_uu3,&nr_);
    key=scrupd(36,funckeys);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5011 && key<5011+d_lin_scr){
			j=key-5011+start_;
			copy(tb_offerte[j].klantstu,s(2,1),s(2,8)-s(2,1));
			scrget(2,331);z=1;
			
			for(k=3;k<7;k++) scrfld(z++,2,k);
			scrifld(z++,fm_odat,&tb_offerte[j].datum);
			scrifld(z++,VarTextFmt(8,0),&tb_offerte[j].referentie);
			key=scrupd(-1,0x19);
			if(key==104){
			  zero(filnam,sizeof filnam);k=0;
        k+=copy0(MAP_OFFERTE,&filnam[k],20);
		    k+=copy0(tb_offerte[j].filname,&filnam[k],sizeof (tb_offerte[0].filname));
        fasclos(-2);
        errnum=fasopen(filnam,99);
				for(k=j+1;k<q_offertes;k++) copy(tb_offerte[k].filname,tb_offerte[k-1].filname,sizeof tb_offerte[0]);
		  	zero((char *)&tb_offerte[q_offertes-1].filname,sizeof tb_offerte[0]);
			  q_offertes--;if(q_offertes==0) return YES;
			}
			goto redo;
		}

    switch(key){
			case 8       : lijnpos--;// pijl opmhoog 
										 if(lijnpos<0) lijnpos=q_-1;
										 break;
			case 9       : lijnpos++;// pijl omlaag 
										 if(lijnpos>=q_) lijnpos=0;
									   break;
			case 12      :// PgUp 
			case 5001    :
			case 102     : if(start_>0){
											 start_-=d_lin_scr; if(start_<0) start_=0;lijnpos=0;scrnum=0;
										 }
										 break;
			case 13      :// PgDn 
			case 5002    :
			case 103     : if((start_+d_lin_scr)<q_offertes) {start_+=d_lin_scr;lijnpos=0;scrnum=0;}
										 break;
			case 10      : start_=0;lijnpos=0;scrnum=0;// HOME 
										 break;
			case 11      : start_=q_offertes-d_lin_scr;if(start_<0) start_=0;// END 
										 lijnpos=0;scrnum=0;
										 break;
			case 101     :
			case 106     : errnum=39;goto end;// annuleer 
										 break;
			case 18      :// ENTER 
			case 15      : // TAB  
			case 108     : if(nr_<1 || nr_>q_offertes) {errnum=34; goto redo;}
										 else{
											 if(nr_>0) copy(tb_offerte[nr_-1].referentie,ref_offerte,sizeof ref_offerte);
											 else errnum=38;
											 goto end;
										 }
										 break;
			default      : break;
    }
  }
 
end:;
  if(errnum) return YES;
	else return NO;

	
}

static read_rec(mode_)
int16 mode_;
{
  int16 j,k;
  flag eof_=NO;
  long pos_;
									
  if(mode_){
    for(j=0;j<1000;j++) if(*(p_data+j)==0x0A || *(p_data+j)=='\0') break;
    if(*(p_data+j)==0x0A || *(p_data+j)=='\0') *pl_80_1+=(j+1);
    zero(p_data,1000);
  }
  pos_=*pl_80_1;
  for(k=0;k<4;k++){
    fasinit(80); *pl_80_1=pos_+k*250;
    if(fasseqi(80,1,254)) {eof_=YES;}
    copy(s(80,1)+4,p_data+k*250,250);
    if(eof_){
      if(*p_data=='\0') return YES;
      break;
    }
  }
  *pl_80_1=pos_;
  return NO;
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
    if(*(pos+k)==DELIM || *(pos+k)==0x0D) break;
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

static get_str(ps_,nr_,mlen_)
char *ps_,nr_;
int16 mlen_;
{
  int16 j,k,len_,add_,dbl_quot_;
  char *pos_,last_kar_;
						
  len_=ele_len(nr_);if(len_>mlen_) len_=mlen_;
  if(len_==0) return 0;
  pos_=rec_ele(nr_);dbl_quot_=NO;
/*
  if(*pos_=='"'){
    pos_++;dbl_quot_=YES;
    if(len_==ele_len(nr_)) len_--;
  }
*/
  j=0;last_kar_='\0';
  for(k=0;k<len_;k++){
    add_=YES;
    if(add_ && *pos_==' ' && j==0) add_=NO;/* leading blancs */
    if(add_ && *pos_=='"' && last_kar_=='"') add_=NO;/* dubbel quotes */
    if(add_){*(ps_+j)=*pos_;last_kar_=*pos_;j++;}
    pos_++;
  }
  for(len_=j-1; len_>=0;len_--){/* trailing blancs */
    if(*(ps_+len_)!=' ') break; else *(ps_+len_)='\0';
  }
  if(dbl_quot_ && *(ps_+len_)=='"') {*(ps_+len_)='\0'; len_--;}
  len_++;
  CnvJamaChar(ps_,len_,1);
  return len_;
}

static ele_len(nr_)
int16 nr_;
{
  int16 k=0;
  char *p;
								
  p=rec_ele(nr_);
  FOREVER{
    if(*p==DELIM || *p==0x0D || *p==0x0A || *p=='\0') return k;
    p++;k++;
  }
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
  beg_=(80-len_)/2; if(beg_<1) beg_=1; 
	copy(fm_titel,fmt_,sizeof fm_titel);fmt_[2]=len_;
	scraddfield(200,beg_,ypos_,attrib_);scrifld(200,fmt_,dsptekst_);
}

static char *rec_ele(nr_)
int16 nr_;
{
  int16 k;
  char *p;
						
  p=p_data;
  for(k=0;k<nr_;k++){
    FOREVER{
      if(*p==DELIM || *p==0xD || *p=='\0') break;
      p++;
    }
    if(*p==0xD || *p=='\0') break;/* einde record */
    p++;
  }
  return p;
}

static uint16 str2date(datestr_)
char *datestr_;
{
 
  uint16 dt_=0;
  int16 dd_,mm_,jj_;
  char str_[10];
 
  if(datestr_[0]){
    zero(str_,sizeof str_);copy(&datestr_[0],str_,2);dd_=val(str_);
    zero(str_,sizeof str_);copy(&datestr_[3],str_,2);mm_=val(str_);
    zero(str_,sizeof str_);copy(&datestr_[6],str_,4);jj_=val(str_);
    if(dd_ && mm_ && jj_) dt_=datejd(jj_,mm_,dd_);
  }
  return dt_;
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}

static add_gr_mult()
{
  int16 j,g,n,k,curs,z,key,mode_,pos_,start,max_,o_start,curspos_;
  char *pd;
  uint16 last_fnd;

  zeroL((char *)&tb[0],sizeof tb);fasinit(6);p_tb=0;max_=0;
  FOREVER{
    if(select_kon("Lijst groepen",modenm[1],0x1,YES)) break;
    pd=&klt_str[0];
    for(k=3;k<=6;k++){
      if(k!=5){
	if(k<6) pd+=add_str(pd,30,2,k,',');
	else pd+=add_str(pd,30,2,k,'\0');
      }
    }
    zeroL((char *)&tb[0],sizeof tb);fasinit(6);p_tb=0;
    zeros((char *)tb_val,sizeof tb_val);
    start=0;max_=DIM_REC;mode_=1;curs=2;last_fnd=0;
    max_=0;
    for(k=1;k<100;k++){
      fasinit(52);*u(52,1)=k;
      g=fasgeti(52);
      if(g==0 && *s(52,14)){
				tb[max_].rec=k;tb[max_].type=3;
				fasinit(9);*pu_9_2=*pu_2_1;*u(9,19)=k;
				if(faskeyi(9,2,0)==0){
					tb[max_].rec=GetRecNr(9)+20000L;
				}
				max_++;
      }
    }
    ld_tb_val(0,max_);
    FOREVER{
redo:;
		  k=133;
#if FLAGCOC
		  k=357;
#endif
#if FLAGABT
		  k=533;
#endif
      scrnum=0;scrget(2,k);z=1;
      scrifld(z++,fm_os63,klt_str);
      for(j=start;j<start+18;j++){
				next:;
				if(j>=max_) break;
				dsp_1_lin(z,j,start,0,NO);z+=6;
			//	fasinit(52);
			//	if(tb[j].rec>20000L){
			//		fasinit(9);SetRecNr(9,(long)(tb[j].rec-20000L));fasgeti(9);*u(52,1)=*u(9,19);
			//	}
			//	else *u(52,1)=tb[j].rec;
			//	fasgeti(52);
			//	pd=&oldnm[0];
			//	stcli_d(pd,(long)*u(52,1),2,0);pd+=2;*(pd++)=' ';
			//	pd+=add_str(pd,30,52,14,'\0');
			//	scrifld(z,fm_os40,oldnm);
			//	if(kon_info(j-start,0)) scrchat(z++,0x2); else z++;/* contract */
			//	scrifld(z++,fm_uf2_2,&tb_val[j-start][0][1]);
			///*      scrifld(z++,fm_uf2_4,&tb_val[j-start][0][3]); */
			//	z++;
			//  if(fld_hlkort) scrifld(z++,fm_uf3_2,&tb_val[j-start][0][5]); else z++;
   //     scrifld(z++,fm_uf2_2,&tb_val[j-start][0][2]);
   //     if(fld_hlkort) scrifld(z++,fm_uf3_2,&tb_val[j-start][0][6]); else z++;
      }
      if(max_==0) {errnum=39;break;}
      if(start && start==max_){start-=18;goto redo;}
      key=scrupd(curs,0x3A6);curs=2;curspos_=fldcurs;
      if(key==106) break;
      for(k=start;k<j;k++){
#if !FLAGEPD  && !FLAGVDW// alle combinaties toelaten 
				n=0; for(g=1;g<5;g++) if(g!=2 && tb_val[k-start][0][g]) n++;
				if(n==2 && (tb_val[k-start][0][1] && tb_val[k-start][0][4]));
				else if(n>1) {errnum=72;curs=3+(k-start)*6; goto redo;}
#endif
			}
			if(key==108){wr_tb_val(start,max_);break;}
			if(key==109){
				wr_tb_val(start,max_);
				curs=curspos_;
				pos_=(curspos_-2)/6;
				if(tb[start+pos_].rec && tb[start+pos_].rec!=0xFFFFFF){
					dsp_1_lin(0,start+pos_,0,YES,NO);/* enkel string samenstellen */
					if(fldlen(9,88)) dsp_detail(pos_);
					else{
						if(tb[start+pos_].rec>20000L){
							fasinit(9);SetRecNr(9,(long)(tb[start+pos_].rec-20000L));fasgeti(9);
							fichupd(1);
						}
					}
				}
				ld_tb_val(start,max_);
      }
			if(key==110){
				wr_tb_val(start,max_);
				curs=curspos_;
				pos_=(curspos_-2)/6;
				if(tb[start+pos_].rec && tb[start+pos_].rec!=0xFFFFFF){
					fasinit(9);
					if(tb[start+pos_].rec>20000L){SetRecNr(9,(long)(tb[start+pos_].rec-20000L));fasgeti(9);}
					if(IsWisKortingAfspraak()==NO){
						zero(tb_val[pos_],sizeof tb_val[0]);
						tb_val[pos_][0][2]=(float)(0.0001);
						wr_tb_val(start,max_);
					}
				}
				ld_tb_val(start,max_);
			}
      o_start=start;
      if(key==102) start-=18;
      if(key==103) {start+=18;if(start>=max_-18) start=max_-18;}
      if(start<0) start=0;
      if(o_start!=start) {wr_tb_val(o_start,max_);ld_tb_val(start,max_);}
      fasinit(6);*pu_6_1=last_fnd;fasgeti(6);
    }
	  DeleteEmptyAfspraken(max_);
  }

  endsr:;
}
 
static kon_info(pos_,j)
int16 pos_,j;
{
  int16 k;
 
  for(j;j<9;j++){
    for(k=0;k<7;k++) if(tb_val[pos_][j][k]) return YES;
  }
  return NO;
}

static wr_tb_val(rpos,max_)
int16 rpos,max_;
{
  int16 j,k,n;
		
	fasunlck(-2);
  for(k=0;k<18;k++){
    if((rpos+k)>=max_) break;
    fasinit(9);
    if(tb[rpos+k].rec==0xFFFFFF){
      if(tb[rpos+k].type==4){
				*f(2,18)=tb_val[k][0][1];
				if(fldlen(2,56)) *f(2,56)=tb_val[k][0][2];
				fasupd(2);
      }
    }
    else if(tb[rpos+k].rec) {
      if(tb[rpos+k].rec>20000L){
	      SetRecNr(9,(long)(tb[rpos+k].rec-20000L));fasgetu(9);
      }
      else {
				*pu_9_2=*pu_2_1;
				if(tb[rpos+k].type==3) *u(9,19)=tb[rpos+k].rec;
				else *pu_9_3=tb[rpos+k].rec;
      }
      for(j=0;j<8;j++) if(fld_nr[j]) *f(9,fld_nr[j])=tb_val[k][0][j+1];
      for(j=0;j<9;j++){
				if(fldlen(9,88+j*5)>0){
					for(n=0;n<5;n++){
						*f(9,88+(j*5)+n)=tb_val[k][j+1][n];
					}
					if(fldlen(9,77+j)) *f(9,77+j)=tb_val[k][j+1][5]; // prijs op datum
				}
      }
      if(tb[rpos+k].rec>20000L){
				//if(testinhoud()==NO && contract()){
				//	faskill(9);tb[rpos+k].rec=0;tb[rpos+k].type=0;
				//}
			 // else fasupd(9);
				fasupd(9);
			}
      else if(testinhoud()){
				errnum=fasadd(9);
				tb[rpos+k].rec=GetRecNr(9)+20000L;/* is nu een contract geworden */
      }
    }
  }
	fasunlck(-1);
}
 
static kill()
{
  int16 k,clr_=YES;

  FOREVER{
    redo:
    if(select_kon(nm_20,modenm[2],0xF,clr_)) break;
    fasinit(9);
    *pu_9_2=*pu_2_1;
    *pu_9_3=*pu_6_1;
		if(fldlen(9,18)) {
			if(inq_lev) *u(9,18)=inq_lev;
			else{
				if(inq_merk) *u(9,18)=30000+inq_merk;
			}
		}
    if(fldlen(9,19)) *u(9,19)=inq_groep;
    k=sear_contr();
    if(errnum || k==NO){clr_=NO;goto redo;}
    else clr_=YES;
 
    if(!fichkil()) break;
  }
}

static globkil()
{
  int16 mode_,key,z;

  copy(modenm[2],nm_15,15);fasinit(2);
  FOREVER{
    redo:
    if(select_kon("Te SCHRAPPEN prijsafspraken",modenm[2],0x3,YES)) break;
    FOREVER{
      scrget(2,63);z=1;scraddpicto(1,0,65,0,10,5,605,0,0,"Waarschuwing"); 
      scrifld(z++,fm_os38,"Selectie prijsafspraken");
      scrfld(z++,25,1);
      scrofld(z++,2,3,-1);
			scrofld(z++,6,3,-1);
      z++;z++;
      key=scrupd(-1,0x419);
      if(key==111) ovlexit(210);
      if(key==101 || key==105) break;
      if(key==104){
				scrget(1,6);scrupd(-3,0);
				fasunlck(-2);
				fasinit(9);mode_=1;
				*pu_9_2=*pu_2_1;*pu_9_3=*pu_6_1;
				FOREVER{
					if(faskeyu(9,1,mode_)) break; mode_=2;
					if(*pu_2_1 && *pu_2_1!=*pu_9_2) break;
					if(*u(6,1)==0 || *u(6,1)==*u(9,3)){
  					if(contract()==YES) faskill(9);
	  				else zero_kon();
					}
				}
				fasflush(0);fasinit(2);break;
				fasunlck(-1);
      }
    }
  }
}

static KltContractCopy()
{
  int16 mode_,key,z,curs=1,full_copy_=NO;
  uint16 from_klt,to_klt;
	long rec_,rec1_;
  char klt[2][45],buf750_[750];
							
  zero((char *)&klt[0][0],sizeof klt);
  fasinit(2);
  FOREVER{
    redo:
    scrget(2,242);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_us40,klt[0]);
    scrifld(z++,fm_us40,klt[1]);
    key=scrupd(curs,0x05C1);
    if(key==101) goto endsr;
    if(key==111) ovlexit(*u(25,2));
    fasinit(2); copy(klt[0],s(2,3),fldlen(2,3));
    if(search(2,0)){curs=2;goto redo;}
    copy(s(2,3),klt[0],fldlen(2,3));
    from_klt=*pu_2_1;
    fasinit(2); copy(klt[1],s(2,3),fldlen(2,3));
    if(search(2,0)){curs=3;goto redo;}
    copy(s(2,3),klt[1],fldlen(2,3));
    to_klt=*pu_2_1;
		full_copy_=NO; if(key==109) full_copy_=YES;
    if(key==108 || key==109) break;
  }
  scrget(1,7);scrupd(-3,0);
	if(full_copy_){ // eerst allemaal deleten 
		scrget(1,6);scrupd(-3,0);
		fasunlck(-2);
		fasinit(9);mode_=1;
		*pu_9_2=*pu_2_1;
		FOREVER{
			if(faskeyu(9,1,mode_)) break; mode_=2;
			if(*pu_2_1!=*pu_9_2) break;
 			if(contract()==YES) faskill(9);
  		else zero_kon();
		}
	}
  fasinit(9);mode_=1;
  *pu_9_2=from_klt;
	fasunlck(-2);
  FOREVER{
    if(faskeyu(9,1,mode_)) break; mode_=2;
    if(from_klt!=*pu_9_2) break;
    if(testinhoud()==YES){
      zero(s(9,27),s(9,61)-s(9,27));/* omzetten wissen */
      rec_=GetRecNr(9); *pu_9_2=to_klt; 
			if(fasadd(9)){
				if(fldlen(9,27)){
					if(faskeyi(9,7,0)==0){
						copy(s(9,27),buf750_,s(9,61)-s(9,27));/* omzetten bijhouden */
						rec1_=GetRecNr(9);
						SetRecNr(9,rec_);fasgeti(9);
						SetRecNr(9,rec1_);*pu_9_2=to_klt; 
						copy(buf750_,s(9,27),s(9,61)-s(9,27));/* omzetten terugzetten */
						fasupd(9);
					}
				}
			}
      SetRecNr(9,rec_);fasgeti(9);
    }
  }
	fasunlck(-1);
  endsr:;
}

static ArtContractCopy()
{
  int16 mode_,key,z,curs=1;
  uint16 from_art,to_art;
	long rec_;
  char art[2][45],skip_vasteprijs='N';
							
  zero((char *)&art[0][0],sizeof art);
  fasinit(2);
  FOREVER{
redo:;
		scraddf(-1,0,0,0);z=1;
	  DisplayMenuTitel(4,"Kopieren alle prijsafspraken van 1 artikel naar een ander artikel",0xA);
		scraddf(z++,8,2,0); scraddf(z++,8,33,2);
    scraddf(z++,10,2,0); scraddf(z++,10,33,2);
    scraddf(z++,12,2,0); scraddf(z++,12,45,2);
		scraddf(z++,16,2,0);scraddf(z++,17,2,0);scraddf(z++,18,2,0);scraddf(z++,19,2,0);
    scraddf(z++,23,1,8);scraddf(z++,23,11,8);scraddf(z++,23,30,8);
    z=1;
		scrifld(z++,VarTextFmt(31,0),"Prijsafspraken overnemen van : ");scrifld(z++,fm_us40,art[0]);
		scrifld(z++,VarTextFmt(31,0),"Prijsafspraken toevoegen aan : ");scrifld(z++,fm_us40,art[1]);
		scrifld(z++,VarTextFmt(43,0),"Prijsafspraken met vaste prijs overslaan : ");scrifld(z++,fm_u_JN,&skip_vasteprijs);
		scrifld(z++,VarTextFmt(79,0),"Met dit programma worden alle individuele prijsafspraken van artikel 1");
		scrifld(z++,VarTextFmt(79,0),"aangemaakt voor artikel 2. Dus heeft een klant een prijsafspraak op");
		scrifld(z++,VarTextFmt(79,0),"artikel 1 (bv 10%), dan zal hij dezelfde voorwaarden krijgen voor artikel 2");
		scrifld(z++,VarTextFmt(79,0),"Bestaat er al een prijsafspraak op artikel 2, dan gebeurt er niks.");
    scrifld(z++,VarTextFmt(9,0)," F1 stop ");scrifld(z++,VarTextFmt(18,0)," F7 zoek artikels ");scrifld(z++,VarTextFmt(19,0)," F8 begin kopieren ");
		key=scrupd(curs,0x04C1);
    if(key==101) goto endsr;
    if(key==111) ovlexit(*u(25,2));
    fasinit(6); copy(art[0],s(6,3),fldlen(6,3));
    if(search(6,0)){curs=2;goto redo;}
    copy(s(6,3),art[0],fldlen(6,3));
    from_art=*u(6,1);
    fasinit(6); copy(art[1],s(6,3),fldlen(6,3));
    if(search(6,0)){curs=4;goto redo;}
    copy(s(6,3),art[1],fldlen(6,3));
    to_art=*u(6,1);
    if(key==108) break;
  }
	if(DisplayWarning("Wenst U echt deze prijsafspraken aan te maken ?", 605,1)==NO) goto endsr;
  scrget(1,7);scrupd(-3,0);
  fasinit(9);mode_=1;
  *u(9,3)=from_art;
	fasunlck(-2);
  FOREVER{
    if(faskeyu(9,7,mode_)) break; mode_=2;
    if(from_art!=*u(9,3)) break;
		rec_=GetRecNr(9);
    if(testinhoud()==YES){
			if(skip_vasteprijs!='J' || *f(9,8)==0){
        zero(s(9,27),s(9,61)-s(9,27));/* omzetten wissen */
        rec_=GetRecNr(9); *u(9,3)=to_art; 
		  	fasadd(9);
			}
      SetRecNr(9,rec_);fasgeti(9);
    }
  }
	fasunlck(-1);
  endsr:;
}

static contract()
{
  int16 j,k;

  for(k=27;k<=42;k+=4){
    for(j=0;j<3;j++) if(fldlen(9,k+j) && *f(9,k+j)) return NO;
  }
  for(k=47;k<=62;k+=4){
    for(j=0;j<2;j++) if(fldlen(9,k+j) && *f(9,k+j)) return NO;
  }
  if(fldlen(9,43) && *f(9,43)) return NO;/* aktuele stock */
  return YES;
}
 
static zero_kon()
{
  int16 k;
 
  for(k=4;k<25;k++) zeros(s(9,k),fldlen(9,k));
  for(k=72;k<83;k++) zeros(s(9,k),fldlen(9,k));
  fasupd(9);
}
 
static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os2,"--");
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
 
static select_kon(p_sel,p_mode,sel_,clr_)
char *p_sel,*p_mode,sel_;
int16 clr_;
{
  int16 key,z,curs=4;
 
  if(clr_){
    fasinit(2);fasinit(6);fasinit(1);
		zero(nm_merk,sizeof nm_merk);zero(nm_lev,sizeof nm_lev);
    zeros(art_res,sizeof art_res);
    zeros(klt_res,sizeof klt_res);
    inq_groep=0;inq_lev=0;inq_merk=0; inq_art=0;
  }
  if(inq_lev) {
		fasinit(1);*u(1,1)=inq_lev;fasgeti(1);
		copy(s(1,3),nm_lev,fldlen(1,3));
	}
	if(inq_merk) {
		fasinit(1);*u(1,1)=inq_merk;fasgeti(1);
		copy(s(1,3),nm_merk,fldlen(1,3));
	}
  FOREVER{
    redo:
    scrget(2,60);z=1; if(cmpstr(p_mode,modenm[2],7)==0) scraddpicto(1,0,65,0,10,5,605,0,0,"Waarschuwing"); 
    scrifld(z++,fm_os38,p_sel);
    scrfld(z++,25,1);
    scrifld(z++,fm_os15,p_mode);
		if(sel_ & 0x1) {scrfld(z++,2,3);scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); } else z++;
		if(sel_ & 0x2) {scrfld(z++,6,3);scraddpicto(6,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); } else z++;
    if(sel_ & 0x4){
			scrifld(z++,fm_us40,nm_lev);
		  if(fldlen(6,101)) scrifld(z++,fm_us40,nm_merk); else z++;
		} else z+=2;
    if(sel_ & 0x8) scrifld(z++,fm_uu2,&inq_groep); else z++;
    key=scrupd(curs,0x0481);curs=4;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) return YES;
    if(key==111) ovlexit(210);
		if(key==5002){
			if(search(2,98)) goto redo;
      copy(s(2,3),klt_res,fldlen(2,3));
		}
    if(cmp_str(s(2,3),klt_res,fldlen(2,3))){
			if(*s(2,3)){
        if(search(2,0)) goto redo;
        copy(s(2,3),klt_res,fldlen(2,3));
			}
			else fasinit(2);
    }
		if(key==5006){
			if(search(6,98)) {curs=5;goto redo;}
			copy(s(6,3),art_res,fldlen(6,3));
		}
    if(cmp_str(s(6,3),art_res,fldlen(6,3))){
      if(*s(6,3)){
				if(search(6,0)) {curs=5;goto redo;}
				copy(s(6,3),art_res,fldlen(6,3));
      }
      else fasinit(6);
    }
		if(nm_lev[0]){
			fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
			if(search(1,0)){curs=6;goto redo;}
			copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
		} else inq_lev=0;
		if(fldlen(6,101) && nm_merk[0]){
			fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
			if(search(1,0)){curs=7;goto redo;}
			copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
		} else inq_merk=0;
		if(sel_==0x03){ // klant of artikel moet ingevuld zijn bij globaal schrappen
			if(*u(2,1)==0 && *u(6,1)==0){errnum=38;goto redo;}
		}
		else if(sel_==0x02){ // artikel moet ingevuld zijn 
			if(*u(6,1)==0){errnum=38;goto redo;}
		}
		else if(*u(2,1)==0){errnum=38;goto redo;}
		inq_art=*u(6,1);
    if(key==108) break;
  }
  return NO;
}

static fichkil()
{
  int16 key,z;

	zero(nm_merk,sizeof nm_merk);zero(nm_lev,sizeof nm_lev);
  fasinit(2);*pu_2_1=*pu_9_2;fasgeti(2);
  fasinit(6);*pu_6_1=*pu_9_3;fasgeti(6);
  if(fldlen(9,18)) {
		fasinit(1);
		*u(1,1)=*u(9,18);
		if(*u(1,1)>30000){
			*u(1,1)-=30000; fasgeti(1); copy(s(1,3),nm_merk,fldlen(1,3));
		}
		else if(*u(1,1)){
		  fasgeti(1); copy(s(1,3),nm_lev,fldlen(1,3));
		}
	}
  redo:
  scrget(2,63);z=1;scraddpicto(1,0,65,0,10,5,605,0,0,"Waarschuwing"); 
  scrifld(z++,fm_os20,fichenm[0]);
  scrfld(z++,25,1);
  scrofld(z++,2,3,-1);
  scrofld(z++,6,3,-1);
  scrifld(z++,fm_os40,nm_lev);
	scrifld(z++,fm_os40,nm_merk);
  if(fldlen(9,19)) scrofld(z++,9,19,-1);
  key=scrupd(-1,0x419);
  if(key==111) ovlexit(210);
  if(key==101) return NO;
  if(key!=104 && key!=105) {errnum=21;goto redo;}
  if(key==104){
		fasunlck(-2);
		if(contract()==YES) faskill(9);
    else zero_kon();
		fasunlck(-1);
    fasflush(0);
  }
  return YES;
}

static print(auto_)
int16 auto_;
{
  int16 form_dat[8],prmode,cnt,j,k,prtnr,z,g,n,modek_,z_netto_;
  uint16 getnr,prev_klt;
  flag a_printed,first;
  char bufklt[1000],txt_[50];

	prt2xls=NO; 
  if(auto_){
    prt_det='J'; prt_kort='J'; only_kprx='N'; prt2pdf=YES;
  }
  else if(!get_selectie(YES)) goto endsr;

	if(prt2xls){
		scrget(1,7);scrupd(-3,0);
		zero(txt_,sizeof txt_);
		k=copy0("Prijsafspraken.XLS",txt_,20);
//			pos_+=copy0(".XLS",&string[pos_],4);
//		if(seldata.prx_klt) {txt_[k++]=' ';copy0(s(2,3),&txt_[k],20);}
		XlsRef=XlsCreate(txt_);
    if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsRij=1;XlsKol=1;
	}
	else{
		getsysprNew(5,form_dat,&prmode,&prtnr);if(prt2pdf) PrintPaperNr=0;
		if((errnum=prtopen(prtnr,form_dat,6,132,prmode,4))!=0) goto endsr;
		scrget(1,6);scrupd(-3,0);
		fmt_get(6,21);
		prtfld(25,1,-1); prttext("<t40eb>"); prttext("Prijsafspraken");
		prttext("<eb>");
		prttext("<t95>"); prtfld(25,2,-1); prttext("<t120>Blz.<ppp>.");
		prtbuf(1);
	}
  z=1;XlsKol=1;
  if(prt_det=='J'){
		if(prt2xls){
			XlsWrite(XlsRef,0,XlsKol++,0,"KltNr",0);
      XlsColumnSize(XlsRef,XlsKol,35);XlsWrite(XlsRef,0,XlsKol++,0,"Naam",0);
		}
		if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"Code",0); else {prttab(z,6,2,1,-1); prttitle(z++,"Code",3);}
		if(prt2xls){XlsColumnSize(XlsRef,XlsKol,30); XlsWrite(XlsRef,0,XlsKol++,0,"Artikel",0);} else {prttab(z,6,3,1,25); prttitle(z++,"Artikel",3);}
    if(fldlen(9,18)){
			if(prt2xls) {XlsColumnSize(XlsRef,XlsKol,15);XlsWrite(XlsRef,0,XlsKol++,0,"Leverancier",0);} else {prttab(z,1,3,1,10); prttitle(z++,"Lev./Merk",3);}
    }
    if(fldlen(9,19)){
			if(prt2xls){XlsColumnSize(XlsRef,XlsKol,15); XlsWrite(XlsRef,0,XlsKol++,0,"Groep",0);} else {prttab(z,52,14,1,10); prttitle(z++,"Groep",3);}
    }
    if(fldlen(9,88)){
			if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"Min.St",0); else {prtitab(z,fm_uf4_0,&min_q,1,-1); prttitle(z++,"Min.st",0x13);}
    }
    if(prt_kort!='N'){
			if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"Kort.%",0); else { prttab(z,9,6,1,-1); prttitle(z++,"Kort.%",0x13);}
			if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"Kort.EUR",0); else {prtitab(z,fm_uf4_2,f(9,7),1,-1);prttitle(z++,"Kort.EUR",0x13);}
#if FLAGGOU
      prttab(z,9,23,1,-1); prttitle(z++,"T",3);
#else
			if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"HLKort",0); else {prtitab(z,fm_uf4_2,f(9,20),1,-1); prttitle(z++,"HlKort",0x13);}
#endif
			if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"Spec.prijs",0); else {prttab(z,9,8,1,-1);prttitle(z++,"Spec.Prijs",0x13);}
    }
    z_netto_=z;
		fmt_get(6,21);
		if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"Fact.prijs",0); else {prtitab(z,fmt,&echt_prx,1,-1);prttitle(z++,"Fact.Pr.",0x13);}
    if(prt_kort!='N'){
#if FLAGCOC
      prttab(z,9,22,1,-1);prttitle(z++,"Factor",0x13);
#else
			if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"SKrt%",0); else {prttab(z,9,22,1,-1);prttitle(z++,"SKrt%",0x13);}
#endif
			if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"SHLkort",0); else {prtitab(z,fm_uf4_2,f(9,21),1,-1); prttitle(z++,"SHlKort",0x13);}
    }
    if(prt_akpr=='J'){
			if(prt2xls) XlsWrite(XlsRef,0,XlsKol++,0,"AK-prijs",0); else {prttab(z,6,18,1,-1);prttitle(z++,"AK-prijs",0x13);}
    }
#if FLAGDWP
    prttab(z,9,9,1,-1); prttitle(z++,"Opmerk.",3); 
#endif
  }
  else {
		if(prt2xls){
			XlsWrite(XlsRef,0,XlsKol++,0,"KltNr",0);
      XlsColumnSize(XlsRef,XlsKol,35);XlsWrite(XlsRef,0,XlsKol++,0,"Naam",0);
			XlsColumnSize(XlsRef,XlsKol,25);XlsWrite(XlsRef,0,XlsKol++,0,"Straat",0);
			XlsColumnSize(XlsRef,XlsKol,7);XlsWrite(XlsRef,0,XlsKol++,0,"PostNr",0);
			XlsColumnSize(XlsRef,XlsKol,20);XlsWrite(XlsRef,0,XlsKol++,0,"Gemeente",0);
			XlsColumnSize(XlsRef,XlsKol,15);XlsWrite(XlsRef,0,XlsKol++,0,"Telefoon",0);
			XlsRij++;
		}
		else{
			if(fldlen(2,2)) {prttab(z,2,2,1,-1); prttitle(z++,"Code",3);}
			else prttab(z,2,1,1,-1); prttitle(z++,"Recnr",3);
			prttab(z,2,3,1,40); prttitle(z++,"Naam",3);
			prttab(z,2,4,1,25); prttitle(z++,"Straat",3);
			prttab(z,2,5,1,-1); prttitle(z++,"Postnr.",3);
			prttab(z,2,6,1,-1); prttitle(z++,"Gemeente",3);
			prttab(z,2,8,1,-1); prttitle(z++,"Telefoon",3);
		}
  }
	if(prt2xls) XlsRij++;
	else{
    prtbuf(3);
    p_pdfname("Prijsafspraken",*u(25,2),0);
	}
 
  free=999; getnr=1; prev_klt=0; cnt=0;
  fasinit(2);if(inq_klt) *pu_2_1=inq_klt; fasgeti(2);modek_=1;
	copy(s(2,1),bufklt,fldlen(2,0));
  FOREVER{
next_k:;
		copy(bufklt,s(2,1),fldlen(2,0));
    if(faskeyi(2,2,modek_)) break; modek_=2;
    if(inq_klt && *pu_2_1!=inq_klt) break;
		copy(s(2,1),bufklt,fldlen(2,0));
		if(inq_klt==0){scrget(1,170);scrfld(10,2,3); scrupd(-3,0);}
    if(fill_tabel(2)) goto next_k;
    if(p_tb==1 && tb[0].rec==0xFFFFFF) goto next_k;
    if(tb[p_tb-1].rec==0xFFFFFF) p_tb--;/* geen klantkorting */
    first=YES;
    for(j=0;j<p_tb;j++){
      fasinit(9);SetRecNr(9,(long)(tb[j].rec-20000L));
      if(fasgeti(9)) continue;
      if(inq_art&&(inq_art!=*pu_9_3)) continue;
      fasinit(6); *pu_6_1=*pu_9_3; fasgeti(6);
      fasinit(52);*u(52,1)=*u(9,19);fasgeti(52);
      if(fldlen(9,18)) {fasinit(1);*u(1,1)=*u(9,18);if(*u(1,1)>30000) *u(1,1)-=30000; fasgeti(1);} // merk +30000
      if(inq_groep&&fldlen(6,9)&&(inq_groep!=*i(6,9))) continue;
      if(inq_lev&&(inq_lev!=*u(6,7))) continue;
			if(inq_merk && *u(6,101)!=inq_merk) continue;
      if(only_kprx=='J' && *f(9,8)==0) continue;
      if(first){
				*pu_2_1=*pu_9_2; prev_klt=*pu_9_2;
				fasgeti(2);
				if(prt2xls){
					if(prt_det!='J'){
						XlsKol=1;
						WriteFld2Xls(XlsRij,XlsKol++,2,klcd+1,0);
						WriteFld2Xls(XlsRij,XlsKol++,2,3,0);
						WriteFld2Xls(XlsRij,XlsKol++,2,4,0);
						WriteFld2Xls(XlsRij,XlsKol++,2,5,0);
						WriteFld2Xls(XlsRij,XlsKol++,2,6,0);
						WriteFld2Xls(XlsRij,XlsKol++,2,8,0);
						XlsRij++;
					}
				}
				else{
					if(prev_klt && prt_det=='J') {nextline();nextline();}/* when not first klt */
					if(free<10) prtform(0);
					if(inq_page=='J') prtform(0);
					if(prt_det=='J'){
						prttext("<beu>Klant :<eu>");
						if(fldlen(2,2)) prtfld(2,2,-1); else prtfld(2,1,-1);
						prttext(" <e>"); prtfld(2,3,-1);prttext("<be>  ");prtfld(2,27,-1);
						if(fldlen(2,18)) {prtfld(2,18,-1);prttext(" %");}
						if(fldlen(2,56) && *f(2,56)) {prttext(", sem.: ");prtfld(2,56,-1);prttext(" %");}
						nextline();nextline();
					}
					else{
						for(g=0;g<20;g++) prtinfo(g,0);
						nextline();
					}
				}
				first=NO;
      }
      if(prt_det!='J') break;
      fasinit(6); *pu_6_1=*pu_9_3; fasgeti(6);min_q=0;a_printed=NO;
      for(n=0;n<10;n++){
				if(n){
					if(fldlen(9,88+(n-1)*5)==0 || *f(9,88+(n-1)*5)==0) break;
					min_q=*f(9,88+(n-1)*5);
					*f(9,6)=*f(9,89+(n-1)*5);
					*f(9,22)=*f(9,90+(n-1)*5);
					*f(9,7)=*f(9,91+(n-1)*5);
					*f(9,8)=*f(9,92+(n-1)*5);
				}
				else {
					if(fldlen(9,72) && *u(9,72) && *u(9,72)<=dt_p_upd){
						*f(9,8)=*f(9,75);
						*f(9,6)=*f(9,73);
						*f(9,7)=*f(9,74);
						if(fldlen(9,20)) *f(9,20)=*f(9,81);
						if(fldlen(9,21)) *f(9,21)=*f(9,82);
						*f(9,22)=*f(9,76); 
						
					}
					if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd) {
						*f(6,18)=*f(6,112);
						*f(6,30)=*f(6,124);
					}
					for(g=0;g<8;g++) if(fld_nr[g] && *f(9,fld_nr[g])) break;
          if(g==8) goto no_prt;/* enkel contract vanaf een bepaald aantal */
				}
				calculate(0);
				if(prt2xls){
					XlsKol=1;
					WriteFld2Xls(XlsRij,XlsKol++,2,klcd+1,0);
					WriteFld2Xls(XlsRij,XlsKol++,2,3,0);
					WriteFld2Xls(XlsRij,XlsKol++,6,2,0);
					WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
					WriteFld2Xls(XlsRij,XlsKol++,1,3,0);
					WriteFld2Xls(XlsRij,XlsKol++,52,14,0);
			    if(fldlen(9,88)) WriteVar2Xls(XlsRij,XlsKol++,fm_uf4_0,&min_q,0);
			    if(prt_kort!='N'){
						WriteFld2Xls(XlsRij,XlsKol++,9,6,0);
						WriteFld2Xls(XlsRij,XlsKol++,9,7,0);
						WriteFld2Xls(XlsRij,XlsKol++,9,20,0);
						WriteFld2Xls(XlsRij,XlsKol++,9,8,0);
					}
					fmt_get(6,21); WriteVar2Xls(XlsRij,XlsKol++,fmt,&echt_prx,0);
			    if(prt_kort!='N'){
			      WriteFld2Xls(XlsRij,XlsKol++,9,22,0);
				  	WriteFld2Xls(XlsRij,XlsKol++,9,21,0);
					}
			    if(prt_akpr=='J') WriteFld2Xls(XlsRij,XlsKol++,6,18,0);
					XlsRij++;
				}
				else{
					for(g=0;g<3;g++) if(*f(9,6+g)) break;
					g=g+4;
				/*    *f(9,6)=kort_pct; *f(9,7)=kort_abs; *f(9,8)=contr_prx;  */
					if(a_printed==YES) k=5; else {k=1;a_printed=YES;}
					for(k;k<5;k++) prtinfo(k,0);
					if(IsWisKortingAfspraak()) prttext(" Geen korting");
					else for(k;k<=15;k++) if(k==z_netto_) prtinfo(k,2); else prtinfo(k,0);
					nextline();
				}
				no_prt:;
      }
      cnt++;
      no_detail:;
      fasinit(1);fasinit(6);
    }
    if(inq_klt) break;
  }
	if(prt2xls) XlsClose(XlsRef,1);
	else{
		if(cnt){
			nextline();
			prttext("*** Aantal fiches :"); SetRecNr(9,(long)cnt); prtfld(9,1,-1);nextline();
		}
		prtclose();
	}
  endsr:;
}

static clean_up()
{
  int16 g;
  long n;

  if(scr_ok("Wenst U echt het afspraken-bestand op te kuisen ?")==NO) goto endsr;
	fasunlck(-2);
  fasinit(9);/* scannen op losgeslagen records */
  n=0;scrget(1,7);scrupd(-3,0);
  FOREVER{
    SetRecNr(9,++n);
    g=fasgetu(9);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
      fasinit(2);*pu_2_1=*pu_9_2;
      if(fasgeti(2)) faskill(9);
      else {
				if(testinhoud()==NO && contract()){
					faskill(9);
				}
      }
    }
  }
	fasunlck(-1);
  endsr:;
  fasinfo(9,101);fasflush(0);
}

static testinhoud()
{
  int16 k;
 
  for(k=0;k<8;k++) if(fld_nr[k] && *f(9,fld_nr[k])) return YES;
	if(fldlen(9,72) && *u(9,72)) return YES;// prijswijziging op datum
  for(k=0;k<9;k++) if(fldlen(9,88+k*5) && *f(9,88+k*5)) return YES;
  return NO;
}

static upd_k_pr()
{
  int16 j,k,mode;
  flag update_;
 
  if(!upd_k_tab()) goto endsr;
  redo:
  if(!get_selectie(NO)) goto endsr;
	if(disp_kon=='N') {
	  if(DisplayWarning("Wenst U echt de geselecteerde prijsafafspraken te wijzigen?",605,1)!=YES) goto endsr;
	}
  fasinit(9);
  if(inq_klt) *pu_9_2=inq_klt;
  if(inq_art) *pu_9_3=inq_art;
  mode=1;
  FOREVER{
    scrget(1,7);scrupd(-3,0);
    next:
    if(faskeyi(9,1,mode)) break;
    mode=2;
    if(inq_klt&&(inq_klt!=*pu_9_2)) break;/* last reached */
    if(inq_art&&(inq_art!=*pu_9_3)) goto next;
    if(testinhoud()==NO) goto next;
    *pu_6_1=*pu_9_3; fasgeti(6);

//    if(fldlen(9,18)) {*u(1,1)=*u(9,18);fasgeti(1);}
    if(inq_groep&&fldlen(6,9)&&(inq_groep!=*i(6,9))) goto next;
    if(inq_lev&&(inq_lev!=*u(6,7))) goto next;
		if(inq_merk && *u(6,101)!=inq_merk) goto next;
    *pu_6_1=*pu_9_3; fasgeti(6);
    update_=NO;
    for(k=0;k<4;k++){
      if(factor[k]){
				if(fld_nr[k] && *f(9,fld_nr[k])){
					*f(9,fld_nr[k])=offset[k]+factor[k] * *f(9,fld_nr[k]);
					if(fld_nr[k]==8){ // vaste prijs
						*f(9,fld_nr[k])=valu_cnv("EUR","EUR",(double)(*f(9,fld_nr[k])),(double)(sys2830)); // afronden
						if(fldlen(9,72)){
							if(*u(9,72)){
								if(*f(9,75)){ // vaste prijs op datum
									*f(9,75)=offset[k]+factor[k] * *f(9,75);
									*f(9,75)=valu_cnv("EUR","EUR",(double)(*f(9,75)),(double)(sys2830));
								}
							}
							else *f(9,75)=0;
						}
					}
					update_=YES;
				}
				for(j=0;j<9;j++){
					if(fldlen(9,88+j*5)==0) break;
					if(*f(9,88+j*5)==0) break;
					*f(9,89+j*5+k)=offset[k]+factor[k] * *f(9,89+j*5+k);
					if(fld_nr[k]==8) *f(9,89+j*5+k)=valu_cnv("EUR","EUR",(double)(*f(9,89+j*5+k)),(double)(sys2830));
					update_=YES;
				}
      }
    }
    if(update_) if(upd_contr()) break;
    fasinit(1);fasinit(6);
  }
  endsr:;
}
 
static upd_contr()
{
  int16 curs=1,g,k,key,z;
 
	
  if(disp_kon=='N') {fasupd(9);return NO;}
	zero(nm_merk,sizeof nm_merk);zero(nm_lev,sizeof nm_lev);
  fasinit(2);*pu_2_1=*pu_9_2;fasgeti(2);
  fasinit(6);*pu_6_1=*pu_9_3;fasgeti(6);
  if(fldlen(9,18)) {
		fasinit(1);
		*u(1,1)=*u(9,18);
		if(*u(1,1)>30000){
			*u(1,1)-=30000; fasgeti(1); copy(s(1,3),nm_merk,fldlen(1,3));
		}
		else if(*u(1,1)){
		  fasgeti(1); copy(s(1,3),nm_lev,fldlen(1,3));
		}
	}
  fasinit(52);if(*u(9,19)) {*u(52,1)=*u(9,19);fasgeti(52);}
  FOREVER{
redo:;
		k=61;
#if FLAGCOC
		k=358;
#endif
#if FLAGGOU // prijstype ipv brij-korting
		k=523;
#endif
    scrnum=0;scrget(2,k);z=1;
    scrifld(z++,fm_os15," ");
    scrofld(z++,2,klcd+1,-1);scrofld(z++,2,3,-1);
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
    if(fldlen(9,18)) {
			scrifld(z++,fm_os40,nm_lev);
			scrifld(z++,fm_os40,nm_merk);
		} else z+=2;
    if(fldlen(9,19)) scrofld(z++,9,19,-1); else z++;
    scrofld(z++,52,14,-1);
#if FLAGGOU
    z+=2;
#endif
#if FLAGCOC
    for(g=4;g<=5;g++)scrofld(z++,9,g,-1);
#endif
    for(k=0;k<6;k++){
			
#if FLAGGOU
			if(fld_nr[k]!=20 && fld_nr[k]==0) z++;
			else{
			  if(fld_nr[k]==20) scrifld(z++,fm_u_05,s(9,23));
			  else scrfld(z++,9,fld_nr[k]);
			}
#else
			if(fld_nr[k]==0) z++;
			else scrfld(z++,9,fld_nr[k]);
#endif
    }
    scrfld(z++,9,72);
    scrfld(z++,9,73);scrfld(z++,9,76);
    scrfld(z++,9,74);
    scrfld(z++,9,75);
    scrfld(z++,9,81);scrfld(z++,9,82);
    for(k=6;k<8;k++){
#if FLAGGOU
			z++;
#else
			if(fld_nr[k]==0) z++;
			else scrfld(z++,9,fld_nr[k]);
#endif
    }

    scrofld(z++,9,9,-1);/* opmerking */
    key=scrupd(curs,0x00E1);curs=1;
    if(key==106) return NO;
		 if(key==101) {return YES;}
#if !FLAGEPD && !FLAGVDW // alle combinaties toelaten 
    k=0; for(g=6;g<9;g++) if(*f(9,g)) k++;
    if(k==2 && (*f(9,6) && *f(9,8)));
    else if(k>1) {errnum=72;curs=11; goto redo;}
#endif
   
    if(key==108) {fasupd(9);return NO;}
  }
}


static upd_k_tab()
{
  int16 k,z,curs=1,key;

  zeros((char *)offset,sizeof offset);zeros((char *)factor,sizeof factor);
  disp_kon='N';
  FOREVER{
    redo:;
    scrget(2,87);z=1;
    scrfld(z++,25,1);
    for(k=0;k<4;k++){
      if(fld_nr[k]){
	scrifld(z++,fm_uf5_4,&factor[k]); scrifld(z++,fm_uf5_4,&offset[k]);
      }
      else {z++;z++;}
    }
    scrifld(z++,fm_u_JN,&disp_kon);
    key=scrupd(curs,0x0481);curs=1;
    if(key==101) break;
    if(key==111) ovlexit(210);
    for(k=0;k<4;k++) if(factor[k]) break;
    if(k==4) errnum=38;
    for(k=0;k<4;k++) if(offset[k] && factor[k]==0) {errnum=38;curs=k*2+2;break;}
    if(key==108 && !errnum) return YES;
  }
  return NO;
}

static get_selectie(mode_)
flag mode_;
{
  int16 z,curs,key;

  fasinit(1); fasinit(2); fasinit(6); fasinit(9);inq_groep=0;
	if(dt_p_upd==0) dt_p_upd=*u(25,2);
	zero(nm_merk,sizeof nm_merk);zero(nm_lev,sizeof nm_lev);
  if(inq_lev) {
		fasinit(1);*u(1,1)=inq_lev;fasgeti(1);
		copy(s(1,3),nm_lev,fldlen(1,3));
	}
	if(inq_merk) {
		fasinit(1);*u(1,1)=inq_merk;fasgeti(1);
		copy(s(1,3),nm_merk,fldlen(1,3));
	}
  art_res[0]='\0';klt_res[0]='\0';lev_res[0]='\0';
  if(inq_klt) {*pu_2_1=inq_klt; fasgeti(2);}
  if(inq_art) {*pu_6_1=inq_art; fasgeti(6);}
  curs=1;
  FOREVER{
    redo:
    scrget(2,73); z=1;
    if(mode_) {
			scrifld(z++,fm_os9,"Afdrukken");
			scraddpicto(7,0,72,22,4,2,573,0,0,"Maak XLS"); 
			scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
		}
    else scrifld(z++,fm_os9,"Aanpassen");
    scrfld(z++,25,1);
    scrfld(z++,2,3);scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrfld(z++,6,3);scraddpicto(6,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    if(fldlen(6,9)) scrifld(z++,fm_uu2,&inq_groep); else scrifld(z++,fm_os5,"-");
		scrifld(z++,fm_us40,nm_lev);
		if(fldlen(6,101)) scrifld(z++,fm_us40,nm_merk); else z++;
    if(mode_) scrifld(z++,fm_u_JN,&only_kprx);
    else scrifld(z++,fm_os5,"-");
    if(mode_) scrifld(z++,fm_u_JN,&prt_det);
    else scrifld(z++,fm_os5,"-");
    if(mode_) scrifld(z++,fm_u_JN,&inq_page);
    else scrifld(z++,fm_os5,"-");
    if(mode_) scrifld(z++,fm_u_JN,&prt_kort);
    else scrifld(z++,fm_os5,"-");
    if(mode_) scrifld(z++,fm_u_JN,&prt_akpr);
    else scrifld(z++,fm_os5,"-");
		if(mode_) scrifld(z++,fm_udat,&dt_p_upd);
		else scrifld(z++,fm_os5,"-");
    key=scrupd(curs,0x0581);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if((key==101)&&(!errnum)) break;
    else if(key==111) ovlexit(210);
    else{
			if(key==5002){
				if(search(2,98)) {curs=2;goto redo;}
				copy(s(2,3),klt_res,fldlen(2,3));
			}
			if(key==5006){
				if(search(6,98)) {curs=3;goto redo;}
				copy(s(6,3),art_res,fldlen(6,3));
			}
 //     if(fldlen(6,9)) inq_groep=*i(6,9);
			if(nm_lev[0]){
				fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
				if(search(1,0)){curs=6;goto redo;}
				copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
			} else inq_lev=0;
			if(fldlen(6,101) && nm_merk[0]){
				fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
				if(search(1,0)){curs=7;goto redo;}
				copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
			} else inq_merk=0;
      if(cmp_str(s(2,3),klt_res,fldlen(2,3))){
				if(*s(2,3)){
					if(search(2,0)) {curs=2; goto redo;}
				}
				else fasinit(2);
      }
      copy(s(2,3),klt_res,fldlen(2,3)); inq_klt=*pu_2_1;
      if(cmp_str(s(6,3),art_res,fldlen(6,3))){
				if(*s(6,3)){
					if(search(6,0)) {curs=3; goto redo;}
				}
				else fasinit(6);
      }
      copy(s(6,3),art_res,fldlen(6,3)); inq_art=*pu_6_1;
      prt2pdf=NO; if(key==5001 && mode_) {prt2pdf=YES;key=108;}
			prt2xls=NO;if(key==5007 && mode_) {prt2xls=YES;key=108;}
      if(key==108) return YES;
    }
  }
  return NO;
}

static initload()
{
	int16 k;
	  
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);

  sysget(1918,2,&sear_stt);
	sysget(2830,4,&sys2830);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  fmt_get(9,8);  prx_afrond=1.; for(k=0;k<fmt[3];k++) prx_afrond/=10.;
  pu_9_2=u(9,2);
  pu_9_3=u(9,3);
  pu_2_1=u(2,1);
  pu_6_1=u(6,1);
  fld_hlkort=NO; if(fldlen(9,20) && fldlen(58,36)) fld_hlkort=YES;
	pl_80_1=l(80,1); p_data=seqo_str;
}

static double Round(bd_,bd_afr_)
double bd_,bd_afr_;
{
  double wrk1_,wrk2_,wrk3_,add_,result_;
 
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
  char update=1,*pd;
  int16 curs,g,j,k,key,z,n,z_contract_=1;
	uint16 r_lev_,r_merk_;
	
  errnum=0;
  if(mode==1) curs=10; else curs=4;
  if(*pu_2_1==0) curs=3;
 	zero(nm_merk,sizeof nm_merk);zero(nm_lev,sizeof nm_lev);
  fasinit(2);*pu_2_1=*pu_9_2;fasgeti(2);
  fasinit(6);*pu_6_1=*pu_9_3;fasgeti(6);
	r_lev_=0;r_merk_=0;
  if(fldlen(9,18)) {
		fasinit(1);
		*u(1,1)=*u(9,18);
		if(*u(1,1)>30000){
			*u(1,1)-=30000; fasgeti(1); copy(s(1,3),nm_merk,fldlen(1,3));r_merk_=*u(1,1);
		}
		else if(*u(1,1)){
		  fasgeti(1); copy(s(1,3),nm_lev,fldlen(1,3));r_lev_=*u(1,1);
		}
	}
  fasinit(52); if(*u(9,19)){*u(52,1)=*u(9,19);fasgeti(52);}
  FOREVER{
    copy(s(2,3),klt_res,fldlen(2,3));
    copy(s(6,3),art_res,fldlen(6,3));
redo:
		k=61;
#if FLAGCOC
		k=358;
#endif
#if FLAGGOU // prijstype ipv brij-korting
		k=523;
#endif
    scrnum=0;scrget(2,k);z=1;
		if(fldlen(9,22) && update){
	  	scraddf(119,22,55,8);
		  if(IsWisKortingAfspraak()==NO) scrifld(119,fm_os18," F10 GEEN korting");
		  else scrifld(119,fm_os13," F10 korting");
		}
		if(fldlen(9,88) && update){
	  	scraddf(118,22,21,8); scrifld(118,VarTextFmt(29,0)," F4 afspraak afh. van aantal ");
		}
		if(mode==2) scrifld(z++,fm_os15," Toevoegen");
		else if(update) scrifld(z++,fm_os15," Aanpassen");
    else scrifld(z++,fm_os15," Raadplegen");
    scrofld(z++,2,klcd+1,-1);scrfld(z++,2,3);scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken");
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrfld(z++,6,3);scraddpicto(6,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken");
    if(fldlen(9,18)) {
			scrifld(z++,fm_us40,nm_lev);
		  if(fldlen(6,101)) scrifld(z++,fm_us40,nm_merk); else z++;
		} else z+=2;
    if(fldlen(9,19)) scrfld(z++,9,19); else z++;
    scrofld(z++,52,14,-1);
#if FLAGGOU
    z+=2;
#endif
#if FLAGCOC
    for(g=4;g<=5;g++)scrfld(z++,9,g);
#endif
    if(update){
			if(IsWisKortingAfspraak()==YES){
				scrifld(z++,fm_os20,"*** GEEN KORTING ***");scrchat(z-1,0xB);z+=5;curs=2;
			}
			else{
				for(k=0;k<4;k++){
					if(fld_nr[k]) scrfld(z++,9,fld_nr[k]);
					else z++;
				}
#if FLAGGOU
			  scrifld(z++,fm_u_05,s(9,23));z++;
#else
				if(fld_hlkort) {scrfld(z++,9,20);scrfld(z++,9,21);}
				else {z++;z++;}
#endif
			}
      scrfld(z++,9,72);
      scrfld(z++,9,73);scrfld(z++,9,76);
      scrfld(z++,9,74);
      scrfld(z++,9,75);
      if(fld_hlkort){scrfld(z++,9,81);scrfld(z++,9,82);}
      else {z++;z++;}
      for(k=6;k<8;k++){
  			if(fld_nr[k]==0) z++;
#if FLAGGOU
				else z++;
#else
	  		else scrfld(z++,9,fld_nr[k]);
#endif
      }
    }
    else{
      z=calculate(z); z+=11;
    }
#if !FLAGGOU && !FLAGCOC
		scrfld(z++,9,4); z_contract_=z; scrfld(z++,9,5);// prijs NIET aanpassen 
#endif
    scrfld(z++,9,9);/* opmerking */
    key=scrupd(curs,0x3E9);curs=10;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106){
      if(mode==2) return NO;
      else return YES;
    }
    if(key==101){
      if(*s(2,3)=='\0') return NO;
      if(mode==2 && testinhoud()==NO) return NO;
    }
		if(key==5002){
			if(search(2,98)) {curs=3;goto redo;}
			copy(s(2,3),klt_res,fldlen(2,3));
		}
		if(key==5006){
			if(search(6,98)) {curs=5;goto redo;}
			copy(s(6,3),art_res,fldlen(6,3));
		}
    if(*s(2,3)=='\0' || cmp_str(s(2,3),klt_res,fldlen(2,3))){
      if(search(2,0)) {curs=3;goto redo;}
      copy(s(2,3),klt_res,fldlen(2,3));
    }
    if(*s(6,3)){
      if(cmp_str(s(6,3),art_res,fldlen(6,3))){
				if(search(6,0)) {curs=5;goto redo;}
				copy(s(6,3),art_res,fldlen(6,3));
      }
    } else {fasinit(6);copy(s(6,3),art_res,fldlen(6,3));}
		if(nm_lev[0]){
			if (*s(6,3)) {errnum=72; curs=6; goto redo;}
      fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=6;goto redo;}
	    copy(s(1,3),nm_lev,fldlen(1,3)); r_lev_=*u(1,1);
    } else r_lev_=0;
	  if(fldlen(6,101) && nm_merk[0]){
			if (*s(6,3)) {errnum=72; curs=7; goto redo;}
			if (r_lev_) {errnum=72; curs=7; goto redo;}
      fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=7;goto redo;}
	    copy(s(1,3),nm_merk,fldlen(1,3)); r_merk_=*u(1,1);
    } else r_merk_=0;

    //if(*s(1,3)) {
    //  if (*s(6,3)) {errnum=72; curs=7; goto redo;}
    //  if(search(1,0)) {curs=8;goto redo;}
    //}
    //else *u(1,1)=0;
    fasinit(52);
    if(*u(9,19)){
      *u(52,1)=*u(9,19);fasgeti(52);
    }
    if(*u(9,19) && *s(6,3)) {errnum=72; curs=8; goto redo;}
    *pu_9_2=*pu_2_1;
    *pu_9_3=*pu_6_1;
	  if(fldlen(9,18)) {
      if(r_lev_) *u(9,18)=r_lev_;
      else{
        if(r_merk_) *u(9,18)=30000+r_merk_;
      }
    }
 //   if(fldlen(9,18)) *u(9,18)=*u(1,1);
    if(*pu_9_3==0 && *u(9,18)==0 && *u(9,19)==0) {errnum=38;curs=5;goto redo;}
		if(update && fldlen(9,22) && key==110){
			if(IsWisKortingAfspraak()==NO){ // kortingen wissen 
			  for(k=0;k<8;k++) if(fld_nr[k]) *f(9,fld_nr[k])=0;
			  *f(9,22)=(float)(0.0001);
			} 
			else *f(9,22)=0; // vlag nokorting wegdoen 
			goto redo;
		}
#if !FLAGEPD && !FLAGVDW// alle combinaties toelaten 
    k=0; for(g=6;g<9;g++) if(*f(9,g)) k++;
    if(k==2 && (*f(9,6) && *f(9,8))) ;
    else if(k>1) {errnum=72;curs=9; goto redo;}
#endif
#if !FLAGGOU && !FLAGCOC
		if(fldlen(9,4) && fldlen(9,5) && *s(9,4)=='J' && *u(9,5)==0){errnum=38;curs=z_contract_; goto redo;}
#endif
    if(key==107 && *pu_6_1){
      update=update^1;scrnum=0;
      if(!update) curs=-1;
      goto redo;
    }

    if(key==109 && *pu_9_3){
      ovlcall(2961,0);
      fasinit(1); fasinit(52);
      goto redo;
    }
    if(key==104 && fldlen(9,88)){
      zeros(oldnm,sizeof oldnm);
      pd=oldnm;
      if(*pu_9_3){
				fasinit(6);*pu_6_1=*pu_9_3;fasgeti(6);
				pd+=add_str(pd,10,6,2,' ');pd+=add_str(pd,30,6,3,'\0');
      }
      else if(*u(9,18) && *u(9,19)){
				fasinit(1);*u(1,1)=*u(9,18);if(*u(1,1)>30000) *u(1,1)-=30000; fasgeti(1); // merk zit op +30000
				fasinit(52);*u(52,1)=*u(9,19);fasgeti(52);
				pd+=add_str(pd,20,1,3,'-');
				stcli_d(pd,(long)*u(52,1),2,0);pd+=2;*(pd++)=' ';
				pd+=add_str(pd,15,52,14,'\0');
      }
      else if(*u(9,18)){
				fasinit(1);*u(1,1)=*u(9,18);if(*u(1,1)>30000) *u(1,1)-=30000; fasgeti(1); // merk zit op +30000
				pd+=add_str(pd,40,1,3,'\0');
      }
      else{
				fasinit(52);*u(52,1)=*u(9,19);fasgeti(52);
				stcli_d(pd,(long)*u(52,1),2,0);pd+=2;*(pd++)=' ';
				pd+=add_str(pd,30,52,14,'\0');
      }
      zeros((char *)tb_val[0],sizeof tb_val[0]);
      for(j=0;j<8;j++) if(fld_nr[j]) tb_val[0][0][j+1]=*f(9,fld_nr[j]);
      for(j=0;j<9;j++){
				if(fldlen(9,88+j*5)>0){
					for(n=0;n<5;n++){
						tb_val[0][j+1][n]=*f(9,88+(j*5)+n);
					}
					if(fldlen(9,77+j)) tb_val[0][j+1][5]=*f(9,77+j); // prijs op datum
				}
      }
      dsp_detail(0);
      for(j=0;j<8;j++) if(fld_nr[j]) *f(9,fld_nr[j])=tb_val[0][0][j+1];
      for(j=0;j<9;j++){
				if(fldlen(9,88+j*5)>0){
					for(n=0;n<5;n++){
						*f(9,88+(j*5)+n)=tb_val[0][j+1][n];
					}
					if(fldlen(9,77+j)) *f(9,77+j)=tb_val[0][j+1][5]; // prijs op datum
				}
      }
    }
    if(key!=108) goto redo;
    if(fldlen(9,16)) *i(9,16)=1;
		fasunlck(-2);
    if(mode==1){
      errnum=fasupd(stu);
    }
    else if(mode==2){
      copy(s(9,1),buf750,fldlen(9,0));
      if(*pu_9_3) g=faskeyi(9,1,0); else g=faskeyi(9,2,0);
      if(g==0){/* fiche bestaat reeds */
				if(testinhoud()){
					errnum=31;copy(buf750,s(9,1),fldlen(9,0));
					goto redo;
				}
				else {
					k=s(9,27)-s(9,1);n=s(9,61)-s(9,27);
					copy(s(9,27),&buf750[k],n);copy(s(9,1),buf750,fldlen(9,1));
					copy(buf750,s(9,1),fldlen(9,0));
					errnum=fasupd(9);
				}
      }
      else {
				copy(buf750,s(9,1),fldlen(9,0));
				errnum=fasadd(stu);
      }
    }
    fasflush(0);fasunlck(-1);
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
  return YES;
}

static calculate(z)
int16 z;
{
  int16 k,pr_inc,type;
  char fmt_[40],dmode_;
  float *pdum,norm_prx,pr_;
 
  semest_pct=0;
  for(k=8;k>=6;k--){
    if(fldlen(9,k)){
      fieldspc(9,k,&pdum,fmt_);
      break;
    }
  }
  if(k==5) return z+3;
  type=0; if(fldlen(2,26) && *s(2,26)>='0' && *s(2,26)<='9') type=*s(2,26)-'0';
  if(fldlen(6,PrNrs[type])==0) type=0;
  if(fldlen(6,30)) accijns=*f(6,30);
  if(fldlen(9,22)) semest_pct=*f(9,22);
  pr_inc=NO;if(sys3894 & (1<<type)) pr_inc=YES;
  norm_prx=*f(6,PrNrs[type]);
  if(pr_inc) norm_prx/=1.+*f(6,28)/100.;
  pr_=*f(6,PrNrs[type]); if(*f(9,8)) pr_=*f(9,8);
  if(pr_inc) pr_/=1.+*f(6,28)/100.;
#if FLAGEPD | FLAGVDW// korting EUR na % aftrekken 
  if(*f(9,6)) pr_=(pr_-accijns)* (100.-*f(9,6))/100. + accijns;
	pr_-=*f(9,7);
#else
  pr_-=*f(9,7);
#if FLAGCOC
	if(*f(9,22)) pr_=*f(6,18)* *f(9,22); // sem%-factor
#endif
  if(*f(9,6)) pr_=(pr_-accijns)* (100.-*f(9,6))/100. + accijns;
#endif
  if(*f(9,20) && fldlen(6,37) && *f(6,37)){
    pr_-=*f(6,37)/100. * *f(9,20);
  }

  kort_abs=norm_prx-pr_;
  kort_pct=100*kort_abs/(norm_prx-accijns);
  echt_prx=pr_;
	dmode_=0x6; if(echt_prx<*f(6,18)) dmode_=0xB;
  if(pr_inc) echt_prx*=1.+*f(6,28)/100.;

  if(z==0) goto endsr;/* if fldnumb = 0, no video-output */
  scrifld(z++,fmt_,&kort_pct); if(!*f(9,6)) scrchat(z-1,dmode_);
  if(fldlen(9,22)){
    scrifld(z++,fmt_,&semest_pct);if(!*f(9,22)) scrchat(z-1,dmode_);
  }
  else z++;
  scrifld(z++,fmt_,&kort_abs); if(!*f(9,7)) scrchat(z-1,dmode_);
  scrifld(z++,fmt_,&echt_prx); if(!*f(9,8))	scrchat(z-1,dmode_);
  endsr:;
  return z;
}
 
static IsWisKortingAfspraak()
{
	int k,iskorting_=YES;
	 
	if(fldlen(9,22)){
		iskorting_=YES; if(*f(9,22)==(float)(0.0001)) iskorting_=NO;
		for(k=0;k<8;k++){
			if(fld_nr[k] && fld_nr[k]!=22 && *f(9,fld_nr[k])) {iskorting_=YES;break;}
		}
	}
	if(iskorting_) return NO; else return YES;
}

static sear_contr()
{
  int16 j,z,key,mode_,start,max_;
  uint16 k_rec_,a_rec_,l_rec_,groep_=0;

  k_rec_=*pu_9_2; a_rec_=*pu_9_3;l_rec_=*u(9,18);
  groep_=*u(9,19);SetRecNr(9,0L);
  if(a_rec_){
    if(faskeyi(9,1,0)){errnum=39;return NO;}
    else return YES;
  }
  zeroL((char *)&tb[0],sizeof tb);p_tb=0;
  start=0;max_=DIM_REC;mode_=1;
  FOREVER{
    scrget(2,62);z=1;
    scrclrf();
    scrofld(z++,2,3,-1);
    for(j=start;j<max_;j++){
      next:;
      if(tb[j].rec==0){
				if(faskeyi(9,2,mode_)) {max_=j;break;}
				mode_=2;
				if(k_rec_!=*pu_9_2) {max_=j;break;}
				if(l_rec_ && *u(9,18)!=l_rec_){max_=j;break;}
				if(groep_ && *u(9,19)!=groep_) {goto next;}
				if(testinhoud()==NO && *u(9,18)==0 && *u(9,19)==0) goto next;
				tb[j].rec=GetRecNr(9)+20000L;
      }
      else {
				fasinit(9);SetRecNr(9,(long)(tb[j].rec-20000L));fasgeti(9);
      }
      fasinit(6);*pu_6_1=*pu_9_3;fasgeti(6);
			fasinit(1);*u(1,1)=*u(9,18);if(*u(1,1)>30000) *u(1,1)-=30000; fasgeti(1); // merk zit op +30000
      j++;scrifld(z++,fm_ou3,&j);j--;
      scrofld(z++,6,2,-1);
      scrofld(z++,6,3,30);
      scrofld(z++,1,3,20);
      scrofld(z++,9,19,-1);
      if(j==start+15) break;
    }
    if(max_==0) {errnum=39;return NO;}
    else if(max_==1) break;
    j=0; scrifld(82,fm_uu3,&j);
    key=scrupd(1,0xA6);
    if(key==106) return NO;
    if((j>0 && j<=max_) && tb[j-1].rec) {tb[0].rec=tb[j-1].rec;break;}
    if(key==102) start-=16;
    if(key==103) {start+=16;if(start>=max_-16) start=max_-16;}
    if(start<0) start=0;
  }
  endsr:;
  fasinit(9);SetRecNr(9,(long)(tb[0].rec-20000L));fasgetu(9);
  return YES;
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
  if(stu_<=2) parmcall[1]=7;            bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3;                                              GEEN ADD
#endif
  if(stu_==6) parmcall[1]=1;/* WEL DISPLAY !!! */
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
