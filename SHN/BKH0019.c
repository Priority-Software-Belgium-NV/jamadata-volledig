/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0019GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0019dat
#define ovlcod BKH0019cod
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


// FLAGCOC : CC adres bij klant is voor facturen/rappels (ander scherm)
// FLAGEPD : nieuwe lev/klantcode met 44/41 
// FLAGGRS : default prijs op bon op N
// FLAGEET : default prijs op bon op N
// FLAGDMD : default prijstype 6


char ovldat[] = "bkh0019  00:63 30/08/10 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define D_LIN_SCR       17
#define DIM_LETIK       100
#define MAXFLD          120
#define flag            uint16

static struct {
  char filname[15];
  int16 filstru;
} files[5];

static char *fichenm[3]={"Leveranciersfiche","Klantenfiche","Grootboekfiche"};
static char *modenm[4]={"aan te passen","toe te voegen","te schrappen","te schrijven"};
static char *selp_txt[6]={"Ondergrens (>)","Ondergrens (> of =)",
		"Bovengrens (<)","Bovengrens (< of =)",
		"Gelijk","Niet gelijk"};

 
extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

extern char *s();
extern int16 *i();
extern uint16 *u();
static uint16 hash();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();
static flag geboekt();
static double Round();

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_of2_1[] = {6,0x94,2,1,0x30,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,0x09,0,'A','A','N','N',0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_btw[]   = {6,0x91,2,0,0x20,0};

extern int16 ilength;
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi;
static char SelectXlsFldNr[150];

static char ram[10000],buf1000[1000];
static int16 dat_len,ram_recl,hash_len,max_line,len6_2,len6_3,len2_120;
static uint16 hash_val,*pu_6_1,fact_klt;
								
static uint16 tb_etik[DIM_LETIK],tot_etik,x_offset,y_offset;
static int16 hz_dots,vt_dots,lettype,line_dots,q_hor,q_vert;

static char def_munt[4];
static char prt_info,only_info,type_info;
static uint16 dt_beg,dt_end;

static int16 stu,free,key21;
static int16 prt2pdf;
static uint16 def_qfak,vers_298,lst_recs[10];
static char nm_20[20],nm_dehr[52],taal_i,talen[4],oldtyp;
static char sort_meth,prt_fiche,fiche_per_blad,only_memo,prt_memo,skip_blocked;
static int16 selp_stu=0;
static char selp_bf[4][1000],selp_des[40],*selp_fld;
static flag selp_use,selp_ge,selp_le,sys1854,sys1816;
static flag chk_btoeg=NO,lvcd,klcd,debit_allow=NO,credt_allow=NO;
static flag sear_stt,sys3876,sys3762,chk_intra,sys2698,only_dsp;
static char sys4521,str4498[23],*p_data;
static char oldnm[50],fmt[40];
static float Bkhbtwpct[4];
static float btw_pct[8];
static long TbDiversArtikel[10];
static char vptekst[100],stuksprx[10];
static char intr_def_land[2];
static int16 intr_def_vervoer,intr_def_transactie;

/* de seqo-variabelen */
							
static char *p_data;
static long *pl_80_1;
									
static char seqo_str[1000],DelimKar=0x09;
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;

ovlcod()
{
  int16 key;
  char choice;

  fasunlck(0);
  initload();
  FOREVER{
    scrget(1,3);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
    if(key==101 || key==111) break;
    switch(choice){
      case '1': if(fldlen(1,1)) execute(1 -1); else errnum=12; break;
      case '2': if(fldlen(2,1)) execute(2 -1); else errnum=12; break;
      case '3': execute(3 -1);break;
      default : errnum=34;break;
    }
  }
  ovlexit(-1);
}

static execute(nr)
int16 nr;
{
  int16 key,scr_nr_;
  char choice;
  if(errnum=fasopen(files[nr].filname,0)) goto endsr;
  stu=files[nr].filstru;
  if(stu==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
  if(stu==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  key21=21;if(faskeyi(stu,key21,0)==45) key21=2;
  copy(fichenm[nr],nm_20,20);
  FOREVER{
    if(stu<3) scr_nr_=50; else scr_nr_=51;
    scrget(1,scr_nr_);fasunlck(0);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_menu,&choice);
    key=scrupd(3,0x0401);
    if(key==101) break;
    if(key==111) ovlexit(-1);
	  switch(choice){
      case '1': upd();break;
      case '2': if(CheckPw(0,11,0)) add(NO);break;
      case '3': if(CheckPw(0,11,0)) kill();break;
      case '4': if(stu<3) prt_ask(nr); else print(nr,1);break;
      case '5': if(stu>2) print(nr,2);break;
      case '6': ovlcall(2918,stu);break;// etiket();
      case '7': if(stu<4) Fiches2Xls(); else errnum=34; break; //fileout();
      case 'L': if(stu<4) ovlcall(2919,stu);
		else errnum=34;
		break;
      default : errnum=34;break;
    }
  }
  endsr:;
}

static upd()
{
  int16 k,key,smode_,len_f9,fkey_;
  char f9_text[40];
	uint16 tb_recs_[1000],p_tb_recs_;

	zero(f9_text,sizeof f9_text);
	len_f9=copy0(" F9 NIEUWE ",f9_text,20);
	k=nm_20[0];if(k>='A' && k<='Z') k+='a'-'A';f9_text[len_f9++]=k;	// hoofdlette wegdoen
	len_f9+=copy0(&nm_20[1],&f9_text[len_f9],19);f9_text[len_f9++]=' ';

  FOREVER{
    if(!errnum){
      fasinit(stu);
    }
		redo:;
    scrget(1,5);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_os15,modenm[0]);
    scrfld(4,stu,3);scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		scraddf(119,23,24,8); scrifld(119,VarTextFmt(len_f9,0),f9_text);
    key=scrupd(4,0x0781);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
    if(key==111) ovlexit(-1);
		if(key==109) {add(YES); goto redo;}
		smode_=0;	if(key==5001) smode_=98;
    if(search(stu,smode_)) goto redo;
		zero(tb_recs_,sizeof tb_recs_); p_tb_recs_=0;tb_recs_[p_tb_recs_]=*u(stu,1);
		next_fiche:;
			/* fasupd */
    if(stu==2 && fldlen(62,1)) {
	    fasinit(62);*u(62,2)=*u(2,1);faskeyi(62,1,0);
    }
    k=fichupd(1);
		if(k==0) break; // stop
		if(k==10) { // previous 
			if(p_tb_recs_){
				*u(stu,1)=tb_recs_[--p_tb_recs_]; fasgeti(stu);
			}
			goto next_fiche;
		}
		if(k==11) { // next
			fkey_=2; if(stu==3) fkey_=1; // alfa, bij grb volgens rekening#
			if(faskeyi(stu,fkey_,2)==0){
				if(p_tb_recs_<999) tb_recs_[++p_tb_recs_]=*u(stu,1);
			} else fasgeti(stu);
			goto next_fiche;
		}
  }
}

static add(single_add_)
int16 single_add_;
{
  FOREVER{
    if(single_add_==NO) fasinit(stu);
		if(stu==1){
			if(fldlen(1,35)) copy(intr_def_land,s(1,35),2);
			if(fldlen(1,36)) *u(1,36)=intr_def_vervoer;
			if(fldlen(1,38)) *u(1,38)=intr_def_transactie;
		}
    if(stu==2){
      if(fldlen(62,1)) fasinit(62);
			sysget(2994,1,s(2,26));
      if(fldlen(2,25)>0) *s(2,25)='0';
#if FLAGEET
      if(fldlen(2,25)>0) *s(2,25)='1';
#endif
#if FLAGSAS
			copy("14", s(2, 13), 2); // Betalingstermijn
			*s(2, 26) = '1'; // Prijstype
			*s(2, 35) = 'N'; // Prijs op bon
			*s(2, 41) = 'J'; // Nettoprijs op JA
#endif
#if FLAGDMD
			*s(2,26) = '6';
#endif
#if !FLAGGRS && !FLAGEET && !FLAGSAS
      if(fldlen(2,35)>0) *s(2,35)='J';
#endif
      if(fldlen(2,36)) *u(2,36)=def_qfak;
      //  if(fldlen(2,44)>0) *s(2,44)='J';
			if(fldlen(2,74)) copy(intr_def_land,s(2,74),2);
			if(fldlen(2,75)) *u(2,75)=intr_def_vervoer;
			if(fldlen(2,77)) *u(2,77)=intr_def_transactie;
    }
    if(!fichupd(2)) break;/* fasadd */
		if(single_add_) break;
  }
}

static kill()
{
  int16 key,smode_;

  if(stu<3 && (sys1854 & stu)) {errnum=65;goto endsr;}
  FOREVER{
    if(!errnum){
      fasinit(stu);
    }
		redo:;
    scrget(1,5);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_os15,modenm[2]);
    scrfld(4,stu,3);scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    key=scrupd(4,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101 && !errnum) break;
    if(key==111) ovlexit(-1);
  	smode_=0;	if(key==5001) smode_=98;
	    if(!search(stu,smode_)){
      if(stu==2 && fldlen(62,1)) {
	fasinit(62);*u(62,2)=*u(2,1);faskeyu(62,1,0);
      }
      if(!fichkil()) break;
    }
  }
  endsr:;
}

static prt_ask(nr)
int16 nr;
{
  int16 z,k,curs=1,key;
						
						
  copy(fichenm[nr],nm_20,20);
  sort_meth='A'; prt_fiche='N'; fiche_per_blad='N';prt_memo='N';only_memo='N';skip_blocked='J';
  FOREVER{
    redo:;
    scrget(1,222);z=1;scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrifld(z++,fm_os20,nm_20);
    scrfld(z++,25,1);
    scrifld(z++,fm_uAN,&sort_meth);
		z+=2;
    if(stu==2 && fldlen(62,1)){
      scrifld(z++,fm_uJN,&prt_memo);
      scrifld(z++,fm_uJN,&only_memo);
			if(fldlen(2,200)) scrifld(z++,fm_uJN,&skip_blocked); else streepje(z++);
    } else {streepje(z++);streepje(z++);streepje(z++);}
    key=scrupd(curs,0x0481);curs=2;
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    if(key==108) break;
  }
  k=1; if(sort_meth=='A') k=2;
  print(nr,k);
  endsr:;
}

static print(nr,fkey)
int16 nr,fkey;
{
  int16 form_dat[8],pr_mode,cnt,blank,prtnr,fuval,k,z,q_info_;
  uint16 getnr;
  flag cd;
 
  selp_use=NO;
  if(stu<3){
    if(fldlen(22,1)){
      if(sel_info()) goto endsr;
    }
    if(selp_ask()) goto endsr;
  }
  if(stu==2 && fldlen(2,200) && selp_use){
		k=s(2,200)-s(2,1);
		if(used(&selp_bf[2][k],fldlen(2,200))) 	skip_blocked='N'; // deze vraag overrulen omdat ze elders geselecteerd is
	}
	k=1; if(nr==2) k=3;
  getsysprNew(k,form_dat,&pr_mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  cd=YES; if((stu==1 && lvcd==NO) || (stu==2 && klcd==NO)) cd=NO;

  if(prt_fiche=='J') {
    if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
    free=999;
    scrget(1,6);scrupd(-3,0);
    prtfld(25,1,25); prttext("<t30b>"); prttext(fichenm[nr]); prttext("<b><t55>");
    prtfld(25,2,-1); prttext("<t72>");prttext("Blz.<ppp>.");
    prtbuf(1);
    p_pdfname(fichenm[nr],0,0);
    goto select;
  }
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  free=999;

  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t50eb>"); prttext(fichenm[nr]); prttext("s<eb><t95>");
  prtfld(25,2,-1); prttext("<t120>Blz.<ppp>.");
  prtbuf(1);
  z=1;
  if(stu<=2){
    prttab(z,stu,1,1,-1); prttitle(z++,"Recnr",3);
    if(cd) prttab(z,stu,2,1,-1); prttitle(z++,"Code",3);
    prttab(z,stu,3,1,40); prttitle(z++,"Naam",3);
    prttab(z,stu,4,1,25); prttitle(z++,"Straat",3);
    prttab(z,stu,5,1,-1); prttitle(z++,"Postnr.",3);
    prttab(z,stu,6,1,-1); prttitle(z++,"Gemeente",3);
    prttab(z,stu,8,1,-1); prttitle(z++,"Telefoon",3);
    prttab(z,stu,7,0,30); prttitle(z++,"Land",3);
  }
  else{
    prttab(z,3,2,2,-1); prtblank(10); prttitle(z++,"Nummer",3);
    prttab(z,3,3,6,-1); prttitle(z++,"Omschrijving",3);
    prttab(z,3,4,9,-1); prttitle(z++,"Central.",3);
    prttab(z,3,5,10,-1); prttitle(z++,"Boek.Toeg.",3);
    prttab(z,3,6,9,-1); prttitle(z++,"Aank.kol.",3);
    prttab(z,3,7,7,-1); prttitle(z++,"Verk.kol.",3);
    prttab(z,3,8,7,-1);  prttitle(z++,"BTW-vak",3);
    prttab(z,3,10,9,-1); prttitle(z++,"Niveau-T.",3);
    prttab(z,3,11,7,-1); prttitle(z++,"Print-Tot.",3);
    prttab(z,3,14,0,-1); prttitle(z++,"Intrastat",3);
  }
  prtbuf(3);
  p_pdfname(fichenm[nr],0,0); 
 
  select:;
  cnt=0;getnr=1;
  fasinit(stu);
  FOREVER{
    next:;
    if(fkey!=1 || cd){
      if(faskeyi(stu,fkey,2)) break;
    }
    else{
      *u(stu,1)=getnr++;fuval=fasgeti(stu);
      if(fuval==46) goto next;
      else if(fuval) break;
    }
    if((nr==0)||(nr==1)){
      if(selp_tst()){
				if(stu==2 && fldlen(62,1)){
					if(fldlen(2,200) && *u(2,200) && skip_blocked=='J') goto next;
					fasinit(62);*u(62,2)=*u(2,1);faskeyi(62,1,0);
					for(k=5;k<10;k++) if(*s(62,k)) break;
					if(only_memo=='J' && k>=10) goto next;
				}
				if(fldlen(22,1)){
					q_info_=get_info(YES);
					if(only_info=='J' && q_info_==0) goto next;
					if(stu==2 && fact_klt && *u(2,51)!=fact_klt) goto next;
				}
				if(prt_fiche=='J') {
					if(free<25) prtform(0);
					fichupd(10);
					if(fldlen(22,1) && q_info_ && prt_info=='J') print_info(q_info_);
					if(fiche_per_blad=='J') prtform(0);
					goto next;
				}
				for(k=1;k<=15;k++) prtinfo(k,0);
				nextline(); cnt++;
				if(stu==2 && prt_memo=='J'){
					z=0;
					for(k=5;k<10;k++){
						if(*s(62,k)){z=k;prttext("<t25>");prtfld(62,k,-1);nextline();}
					}
					if(z) nextline();
				}
				if(fldlen(22,1) && q_info_ && prt_info=='J') print_info(q_info_);
						}
						if(nr==0 && sys1816&1){
				prtblank(7);
				for(k=9;k<120;k++) if(fldlen(1,k) && fldlen(1,k)<10){
					prtfld(1,k,-1);prtblank(1);
				}
				nextline();nextline();
      }
    }
    else if(nr==2){
      if(oldtyp!=*s(3,5)){if(oldtyp) nextline(); oldtyp=*s(3,5);}
      if((*s(3,5)=='J')||(*s(3,10)=='\0'))/* geen totaalrekening */
	blank=10;
      else{
	blank=(val(s(3,10))-1)*2;
	if(blank>=10) blank=9;
	if(blank<0) blank=0;
      }
      prtblank(blank); prtinfo(1,0); prtblank(10-blank); prtinfo(2,0);
      if(blank!=10) {prtinfo(4,0); prtinfo(8,0); prtinfo(9,0);}
      else {for(k=3;k<=7;k++)prtinfo(k,0);prtinfo(10,0);}
      nextline();cnt++;
    }
  }
  if(cnt && prt_fiche!='J'){
    nextline();
    prttext("*** Aantal fiches :"); *u(stu,1)=cnt; prtfld(stu,1,-1); nextline();
  }
  prtclose();
  endsr:;
}

static sel_info()
{
  int16 z,key;

  if(prt_info=='\0') prt_info='N';
  if(only_info=='\0') only_info='N';
  if(dt_end==0) dt_end=*u(25,2);
  if(stu==2){
    fact_klt=0; fasinit(2);
  }
  FOREVER{
    redo:;
    scrget(1,208);z=1;
    scrifld(z++,fm_uJN,&prt_info);
    scrifld(z++,fm_udat,&dt_beg);
    scrifld(z++,fm_udat,&dt_end);
    if(stu==2) scrfld(z++,2,3); else streepje(z++);
    scrifld(z++,fm_us1_U,&type_info);
    scrifld(z++,fm_uJN,&only_info);
    key=scrupd(1,0x81);
    if(key==101) return YES;
    if(stu==2 && fldlen(2,51) && *s(2,3)){
      if(search(2,0)) goto redo;
      fact_klt=*u(2,1);
    } else fact_klt=0;
    if(key==108) break;
  }
  return NO;
}
 
static get_info(select_)
int16 select_;
{
  int16 k,mode_;
									
  ram_recl=fldlen(22,0) +2;                               /* + 2 bytes hash */
  max_line=(sizeof ram /ram_recl) -1;
  hash_len=0; dat_len=ram_recl-2;
  zero(ram,sizeof ram);
  fasinit(22);*u(22,2)=stu;*u(22,3)=*u(stu,1); mode_=1; k=0;
  FOREVER{
    next:;
    if(faskeyi(22,1,mode_)) break; mode_=2;
    if(*u(22,2)!=stu) break;
    if(*u(22,3)!=*u(stu,1)) break;
    if(select_){
      if(dt_beg && *u(22,4)<dt_beg) goto next;
      if(dt_end && *u(22,4)>dt_end) goto next;
      if(type_info && *s(22,6)!=type_info) goto next;
    }
    stu2ram(22,k);
    k++; if(k>=max_line) break;
  }
  return k;
}

static dsp_info()
{
  int16 j,k,curs=1,z_base_,key,z,start_,d_mode_=NO,curspos_;
  char *pdum,dumm_[10],*pvar;
 
  if(fldlen(22,0)==0) goto endsr;
  get_info(NO);
  pdum=&dumm_[0];
  scrnum=0; start_=0;
  FOREVER{
    redo:
    scrget(2,89);z=1;if(stu<3 && fldlen(22,7)) scraddpicto(1,0,11,3,2,1,605,0,0,"Alarm"); 
    j=start_+1; scrifld(z++,fm_ou3,&j);
    j+=D_LIN_SCR-1; scrifld(z++,fm_ou3,&j);
    if(fldlen(stu,2)) scrofld(z++,stu,2,-1); else scrofld(z++,stu,1,-1);
    scrofld(z++,stu,3,-1);
    z_base_=z;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      if(fieldspc(22,4,&pdum,fmt)>0){
				if(d_mode_==NO) fmt[1]&=0xBF;
				pvar=ram+(j*ram_recl + (s(22,4)-s(22,1)));
				scrifld(z++,fmt,pvar);
      }
      if(fieldspc(22,7,&pdum,fmt)>0){
				if(d_mode_==NO) fmt[1]&=0xBF;
	      pvar=ram+(j*ram_recl + (s(22,7)-s(22,1)));
	      scrifld(z++,fmt,pvar);
      } else z++;
      if(fieldspc(22,6,&pdum,fmt)>0){
				if(d_mode_==NO) fmt[1]&=0xBF;
				pvar=ram+(j*ram_recl + (s(22,6)-s(22,1)));
				scrifld(z++,fmt,pvar);
      }
      if(fieldspc(22,10,&pdum,fmt)>0){
				pvar=ram+(j*ram_recl + (s(22,10)-s(22,1)));
				scrifld(z++,fmt,pvar);
      }

    }
    key=scrupd(curs,0x3BF);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000; 
		if(key==5001){curs=fldcurs;goto redo;}
    if(key==101 || key==106) goto endsr;
    if(key==104){
      j=(curspos_-z_base_)/4;j+=start_;
      ins_lin(22,j);
      curs=curspos_;goto redo;
    }
    if(key==105){
      j=(curspos_-z_base_)/4;j+=start_;
      del_lin(22,j);
      curs=curspos_;goto redo;
    }
    if(key==110) copy_info();
    if(key==109) {if(d_mode_) d_mode_=NO; else d_mode_=YES;}
    if(key==108)break;
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){ram2stu(22,k+start_);if(*s(22,10)=='\0') {j=k;break;}}
    curs=z_base_+j*4;
  }
	fasunlck(-2);
  for(k=0;k<max_line;k++){
    ram2stu(22,k);
    if(*s(22,10)){
      *u(22,2)=stu; *u(22,3)=*u(stu,1); *u(22,5)=k;
      if(*u(22,4)==0) *u(22,4)=*u(25,2);
      if(*u(22,1)) fasupd(22); else fasadd(22);
    }
    else if(*u(22,1)) faskill(22);
  }
	fasunlck(-1);
  endsr:;/* stop */
}
 
static copy_info()
{
  int16 k,key,mode_;
  uint16 adr_,mrec_,rec_;
									
  copy(s(stu,1),buf1000,fldlen(stu,0));
  adr_=4128; if(stu==2) adr_=4130; else if(stu==6) adr_=4132;
  sysget(adr_,2,&mrec_); fasinit(stu); if(mrec_) {*u(stu,1)=mrec_;fasgeti(stu);}
  FOREVER{
    redo:;
    scrget(1,5);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_os38,"DE INFO OVER TE NEMEN ?");
    scrfld(4,stu,3);
    key=scrupd(4,0x0481);
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(search(stu,0)) goto redo;
    break;
  }
  mrec_=*u(stu,1);sysput(adr_,2,&mrec_);
  for(k=max_line-1;k>=0;k--){
    ram2stu(22,k); if(*u(22,1) || *s(22,10)) break;
  }
  if(k>=max_line) goto endsr;
  fasinit(22);*u(22,2)=stu;*u(22,3)=mrec_; mode_=1; k=k+1;
  FOREVER{
    next:;
    if(faskeyi(22,1,mode_)) break; mode_=2;
    if(*u(22,2)!=stu) break;
    if(*u(22,3)!=mrec_) break;
    rec_=*u(22,1); *u(22,1)=0; *u(22,4)=0;             /* forceren te adden */
    stu2ram(22,k);
    k++; if(k>=max_line) break;
    *u(22,1)=rec_; fasgeti(22);
  }
  endsr:;
  copy(buf1000,s(stu,1),fldlen(stu,0));
}

static print_info(q_info_)
int16 q_info_;
{
  int16 k;
					
  nextline();
  for(k=0;k<q_info_;k++){
    ram2stu(22,k);
    prttext("<t10>");prtfld(22,4,-1);
    prttext("  ");prtfld(22,6,-1);
    prttext("  ");prtfld(22,10,-1);
    nextline();
  }
  nextline();
}
  
static ins_lin(stu_,lin_)
int16 stu_,lin_;
{
  int16 k;
								
  if(stu_==22){
    ram2stu(stu_,max_line-1);
    if(*u(22,1)) faskill(stu_);
  }
  for(k=max_line-2;k>=lin_;k--){
    ram2stu(stu_,k);
    stu2ram(stu_,k+1);
  }
  zero(ram+ram_recl*lin_,ram_recl);
}

static del_lin(stu_,lin_)
int16 stu_,lin_;
{
  int16 k;
 
  if(stu_==22){
    ram2stu(stu_,lin_);
    if(*u(22,1)) faskill(stu_);
  }
  for(k=lin_;k<max_line-1;k++){
    ram2stu(stu_,k+1);stu2ram(stu_,k);
  }
  zero(ram+ram_recl*(max_line-1),ram_recl);
}

static ram2stu(stu_,lin_)
int16 stu_,lin_;
{
  copy(ram+(lin_*ram_recl),s(stu_,1),dat_len);
  copy(ram+(lin_*ram_recl)+dat_len,&hash_val,2);
}

static stu2ram(stu_,lin_)
int16 stu_,lin_;
{
  copy(s(stu_,1),ram+(lin_*ram_recl),dat_len);
  copy(&hash_val,ram+(lin_*ram_recl)+dat_len,2);
}

static uint16 hash(stu_)
int16 stu_;
{
  char *ps;
  int16 k;
  uint16 fuval=0;
					
  k=hash_len;ps=s(stu_,1);
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
}
 

static getfname(nr,array)
int16 nr,array;
{
  nr--;
  sysget(300+17*nr,15,files[array].filname);
  sysget(315+17*nr,2,&files[array].filstru);
}

static initload()
{
  int16 k;

  for(k=0;k<5;k++) getfname(k+1,k);

  fileopen(1);
  fileopen(2);
  fileopen(3);
	fileopen(4);
	fileopen(5);
	fileopen(10);
	if(fldlen(7,1)) fileopen(7);
  if(fldlen(22,1)) fileopen(15);
	if(fldlen(16,1)) fileopen(13);
  sysget( 294,4,def_munt);
  sysget( 298,2,&vers_298);
  sysget(586,2,intr_def_land); if(intr_def_land[0]=='\0') copy("BE",intr_def_land,2);
  sysget(588,2,&intr_def_vervoer);if(intr_def_vervoer==0) intr_def_vervoer=3;
  sysget(590,2,&intr_def_transactie); if(intr_def_transactie==0) intr_def_transactie=11;
  sysget(1008,16,(char *)Bkhbtwpct);
	sysget(1048,32,&btw_pct[0]);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;
  sysget(1816,2,&sys1816);
  sysget(1854,2,&sys1854);
  sysget(1918,2,&sear_stt);
  sysget(2212,4,talen);
  sysget(2222,2,&def_qfak);
  sysget(2698,2,&sys2698);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
  sysget(3876,2,&sys3876);
  sysget(3762,2,&sys3762);
  sysget(4610,60,vptekst);
  sysget(4670,6,stuksprx);
  sysget(4740,40,&vptekst[60]);
  sysget(4780,4,&stuksprx[6]);
  chk_intra=NO; if(fldlen(4,48)) chk_intra=YES;
  p_data=s(80,1)+4;
	len2_120=fldlen(2,120);
  len6_2=fldlen(6,2);len6_3=fldlen(6,3);
	pu_6_1=u(6,1);
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
  int16 k,curs,curs_taal,key,z,dcurs_,curspos_,kleur_;
  uint16 fakklnr;
  char *p_stu_3,dspstr_[50];
  long old_grb_;
 
	fasunlck(-1);
#if FLAGEPD
	if(mode==2){
		if(stu==1) copy("44",s(1,2),2); else if(stu==2) copy("42",s(2,2),2);
		get_newcode();
	}
#else
	if(((sys3762 & (1<<6))==0) && mode==2 && (stu==1 || stu==2) && fldlen(stu,2) && *s(stu,2)=='\0') get_newcode();
#endif
  only_dsp=NO; if(sys2698 && mode==1) only_dsp=YES;
  p_stu_3=s(stu,3);
  taal_i='\0';
  FOREVER{
    curs=2;
    if(stu==1){/* leveranciers */
redo_l:
			if(fldlen(stu,200)){
				if(*u(stu,200)) ConLook(1); else   ConLook(0);
			}
      scrget(2,6);z=1;

			if(mode==1){
				scraddpicto(25,0,0,0,2,1,93,0,4,"vorig"); 
				scraddpicto(26,0,78,0,2,1,92,0,4,"volgend"); 
				scraddpicto(20,0,75,1,4,2,514,0,0,"Extra opties"); 
			}
      dsp_i_flag();
      scrfld(z++,25,1);
      if(lvcd) scrfld(z++,1,2); else scrofld(z++,1,1,-1);
			if(fldlen(stu,200) && mode==1){
				if(*u(stu,200)==1) scrchat(z-1,0xB); else scrchat(z-1,0xFF);
				if(!only_dsp){
					if(*u(stu,200)==1) scraddpicto(4,z-1,0,0,2,1,70,0,4,"Maak actief"); else scraddpicto(4,z-1,0,0,2,1,71,0,3,"Blokkeer");
				}
			}
      for(k=3;k<7;k++) scrfld(z++,1,k);
			if(!only_dsp && fldlen(29,1)) scraddpicto(8,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
			ShowGoogleMapsButton(24,z-1,2,0,2,1,1); 
      for(k=7;k<16;k++) scrfld(z++,1,k);
      curs_taal=z;
      taal_upd(z++,16);
			scrfld(z++,1,17);
			scrfld(z++,1,18);if(!only_dsp && fldlen(1,18)) scraddpicto(3,z-1,0,0,2,1,105,0,3,"Controleer IBAN/BIC"); 
      for(k=19;k<MAXFLD;k++) scrfld(z++,1,k);
			if(!only_dsp && fldlen(1,130)){
				kleur_=3; if(*s(1,130)) kleur_=4;
				scraddpicto(1,21,0,0,2,1,101,0,kleur_,"Email-instellingen"); 
			}
      dcurs_=curs; if(only_dsp) dcurs_=-1;
      key=scrupd(dcurs_,0x07A9);curs=2;curspos_=fldcurs;
			if(fldlen(stu,200)) ConLook(0);
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key==5001){DisplayEmailSettings(stu);goto redo_l;}
			if(key==5003){IbanTools(s(1,18),s(1,19),s(1,12),1);goto redo_l;}
			if(key==5004 && fldlen(stu,200)){ // blokkeer
				if(*u(stu,200)) *u(stu,200)=0; else *u(stu,200)=1;
				goto redo_l;
			}
			if(key==5008){
				fasinit(29); 
				if(*s(1,6)) copy(s(1,6),s(29,3),fldlen(1,6));
				else copy(s(1,5),s(29,3),fldlen(1,5));
				if(search(29,0)==0){ copy(s(29,2),s(1,5),fldlen(1,5)); copy(s(29,3),s(1,6),fldlen(1,6));}
				else curs=6;
				goto redo_l;
			}
      if(key==15 && only_dsp && CheckPw(0,11,0)){only_dsp=NO;goto redo_l;}
			if(key==5020){DisplayExtraFuncties(stu);key=107;} // extra opties
      if(key==106){
	if(mode==2) return NO;
	else return YES;
      }
      if(mode==2 && key==111 && lst_recs[stu]){
	fasinit(stu);*u(stu,1)=lst_recs[stu];fasgeti(stu);
	zero(s(stu,1),s(stu,3)-s(stu,1));
      }
      k=*p_stu_3;
      if(key==101 && k=='\0') return NO;
      if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo_l;}
      if((k<'A' || k>'Z') && (k<'a' || k>'z') && (k<'0' || k>'9')) {errnum=30;curs=3;goto redo_l;}
      if(lvcd && *s(1,2)=='\0') {errnum=38;curs=2;goto redo_l;}
      if(taal_chk(16)) {curs=curs_taal;goto redo_l;}
      if(chk_intra){
				if(fldlen(1,35)) if(*s(1,35)=='\0'){errnum=38;curs=35;goto redo_l;}
				if(fldlen(1,36)) if(*i(1,36)==0){errnum=38;curs=36;goto redo_l;}
				if(fldlen(1,38)) if(*i(1,38)==0){errnum=38;curs=38;goto redo_l;}
      }
			if(!only_dsp && fldlen(stu,18) && *s(stu,18)){
				if(k=IbanTools(s(stu,18),s(stu,19),s(stu,12),1)) {curs=18+k-1; goto redo_l;} 
		  }
      if(key==109 && fldlen(1,121)) {lev_dfgrb();goto redo_l;}
      if(key==110 && fldlen(1,125)) {DisplayMemo(stu);goto redo_l;}
      if(key==112 && *u(stu,1)) {dsp_info(); goto redo_l;}
      if(key!=5025 && key!=5026 && key!=108 && key!=101) goto redo_l;
    }

    else if(stu==2){/* klanten */
      if(fldlen(2,51)){ // facturatieklant
				selp_stu=0;
				if(*u(2,51)==0) selp_bf[1][0]='\0';
				else{
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					*u(2,1)=*u(2,51);
					if(fasgeti(2)) {selp_bf[1][0]='\0';selp_bf[1][50]='\0';}
					else {
						copy(s(2,3),&selp_bf[1][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[1][50],fldlen(2,3));
					}
					copy(selp_bf[0],s(2,1),fldlen(2,0));
				}
      }
      if(fldlen(2,52)==2){ // relatieklant
				selp_stu=0;
				if(*u(2,52)==0) selp_bf[2][0]='\0';
				else{
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					*u(2,1)=*u(2,52);
					if(fasgeti(2)) {selp_bf[2][0]='\0';selp_bf[2][50]='\0';}
					else {
						copy(s(2,3),&selp_bf[2][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[2][50],fldlen(2,3));
					}
					copy(selp_bf[0],s(2,1),fldlen(2,0));
				}
      }
		  if(fldlen(2,27)){
				k=*s(2,26)-'0';if(k<0 || k>9) k=0;
				if(fldlen(6,PrNrs[k])==0) k=0;
				if(*s(2,26)=='A') copy("*AKpr*",s(2,27),fldlen(2,27));
				else copy(&vptekst[k*10],s(2,27),fldlen(2,27));
      }
			curs=2;
redo_k:
			if(fldlen(2,200)){
				if(*u(2,200)) ConLook(1); else   ConLook(0);
			}
      scrnum=0;scrget(2,7); z=1;
			if(mode==1){
				scraddpicto(25,0,0,0,2,1,93,0,4,"vorig"); 
				scraddpicto(26,0,78,0,2,1,92,0,4,"volgend"); 
				scraddpicto(20,0,75,1,4,2,514,0,0,"Extra opties"); 
			}
      dsp_i_flag();
      scrfld(z++,25,1);
      if(klcd) scrfld(z++,2,2); else scrofld(z++,2,1,-1);
			if(fldlen(2,200) && mode==1){
				if(*u(2,200)==1) scrchat(z-1,0xB); else scrchat(z-1,0xFF);
				if(!only_dsp){
					if(*u(2,200)==1) scraddpicto(4,z-1,0,0,2,1,70,0,4,"Maak actief"); else scraddpicto(4,z-1,0,0,2,1,71,0,3,"Blokkeer");
				}
			}
			if(fldlen(2,195)){
				if(*s(2,195)=='J') scraddpicto(11,z-1,2,0,2,1,32,0,4,"Mag NIET bestellen via webshop"); else scraddpicto(11,z-1,2,0,2,1,32,0,3,"Mag bestellen via webshop");
			}
			scrfld(z++,2,3);
      if(*(s(2,3)+fldlen(2,3)-1)=='!') scrchat(z-1,0xB); else scrchat(z-1,0xFF);
			if(!only_dsp){
  			if(*(s(2,3)+fldlen(2,3)-1)!='!') scraddpicto(2,z-1,0,0,2,1,48,0,3,"Markeer"); 
    		else scraddpicto(2,z-1,0,0,2,1,86,0,4,"Normaal"); 
			}
      for(k=4;k<7;k++) scrfld(z++,2,k);
			if(!only_dsp && fldlen(29,1)) scraddpicto(8,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
      ShowGoogleMapsButton(24,z-1,2,0,2,1,2); 
			for(k=7;k<=10;k++) scrfld(z++,2,k);
			if(fldlen(2,10)){
				if(*l(2,10)==0 || *l(2,10)==BTWNR_OFFSET) scrchat(z-1,0xFF);
				else if (*(s(2,10)+3) & 0x40){ // if(*l(2,10)>=BTWNR_OFFSET){
					scrchat(z-1,0xB); if(!only_dsp) scraddpicto(10,z-1,4,0,2,1,86,0,4,"Maak BTW-plichtig"); 
				}
				else{
					scrchat(z-1,0xFF);if(!only_dsp) scraddpicto(10,z-1,4,0,2,1,76,0,3,"Maak NIET BTW-plichtig"); 
				}
			}
      for(k=11;k<16;k++) scrfld(z++,2,k);
			scrfld(z++,2,16);if(!only_dsp && fldlen(2,16)) scraddpicto(3,z-1,0,0,2,1,105,0,3,"Controleer IBAN/BIC"); 
      for(k=17;k<24;k++) scrfld(z++,2,k);
      curs_taal=z;
			taal_upd(z++,24);
      scrfld(z++,2,25);
      if(fldlen(2,27)){scrfld(-z,2,26);z++;}
      else scrfld(z++,2,26);
#if FLAGGOU
			scrfld(z++,2,27);
      if(fldlen(2,29)){scrfld(-z,2,28);z++;} // GOU
      else scrfld(z++,2,28);
      for(k=29;k<51;k++) scrfld(z++,2,k);
#else
      for(k=27;k<=38;k++) scrfld(z++,2,k);
			if(!only_dsp && fldlen(2,38) && fldlen(63,1)) scraddpicto(9,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
			for(k=39;k<51;k++) scrfld(z++,2,k);
#endif
      if(fldlen(2,51)>0) scrifld(z++,fm_us40,selp_bf[1]); else z++;
			if(fldlen(2,52)==2) scrifld(z++,fm_us40,selp_bf[2]); else scrfld(z++,2,52); // relatieadres
      for(k=53;k<MAXFLD;k++) scrfld(z++,2,k);
			if((fldlen(2,121) || fldlen(2,130))){
				kleur_=3;
				for(k=0;k<4;k++){
				  if(fldlen(2,121+k) && *s(2,121+k)=='J') {kleur_=4;break;}
				}
				if(fldlen(2,128) && *s(2,128)) kleur_=4;
				scraddpicto(1,21,0,0,2,1,101,0,kleur_,"Email-instellingen"); 
			}
			if(fldlen(2,143)){
				kleur_=3;
				for(k=143;k<=146;k++){
				  if(fldlen(2,k) && *s(2,k)) {kleur_=4;break;}
				}
				scraddpicto(7,4,0,0,2,1,101,0,kleur_,"Afwijkend leveradres"); 
			}
      dcurs_=curs; if(only_dsp) dcurs_=-1;
      key=scrupd(dcurs_,0x07A9);curs=2;curspos_=fldcurs;
			if(fldlen(2,200)) ConLook(0);
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key==5001){DisplayEmailSettings(stu);goto redo_k;}
			if(key==5002){
				if(*(s(2,3)+fldlen(2,3)-1)=='!') *(s(2,3)+fldlen(2,3)-1)=' ';
				else{
					*(s(2,3)+fldlen(2,3)-1)='!';
				}
				goto redo_k;
			}
			if(key==5003){IbanTools(s(2,16),s(2,17),s(2,12),1);goto redo_k;}
			if(key==5004 && fldlen(2,200)){ // blokkeer
				if(*u(2,200)) *u(2,200)=0; else *u(2,200)=1;
				goto redo_k;
			}
			if(key==5007){DisplayLeveradres(stu);goto redo_k;}
			if(key==5008){
				fasinit(29);
				if(*s(2,6)) copy(s(2,6),s(29,3),fldlen(2,6));
				else copy(s(2,5),s(29,3),fldlen(2,5));				
				if(search(29,0)==0){ copy(s(29,2),s(2,5),fldlen(2,5)); copy(s(29,3),s(2,6),fldlen(2,6));}
				else curs=6;
				goto redo_k;
			}
			if(key==5009){
				fasinit(63);copy(s(2,38),s(63,3),fldlen(63,3));
				if(search(63,98)==0) copy(s(63,3),s(2,38),fldlen(63,3));
				else curs=38;
				goto redo_k;
			}
      if(key==15 && only_dsp && CheckPw(0,11,0)){only_dsp=NO;goto redo_k;}
			if(key==5020){DisplayExtraFuncties(stu);key=107;} // extra opties
      if(key==106){
	if(mode==2) return NO;
	else return YES;
      }
			if(key==5010){
				if (*(s(2,10)+3) & 0x40) *(s(2,10)+3)  &= 0xBF; else *(s(2,10)+3)  |= 0x40;
				//if(*l(2,10)>=BTWNR_OFFSET) *l(2,10)-=BTWNR_OFFSET;
				//else *l(2,10)+=BTWNR_OFFSET;
				goto redo_k;
			}		
			if(key==5011 && fldlen(2,195) && !only_dsp){
				if(*s(2,195)=='J') *s(2,195)='N'; 
				else{
					if(*s(2,21)){
						*s(2,195)='J';
						if(fldlen(2,2)) {
							zero(dspstr_,sizeof dspstr_);sprintf_s(dspstr_,sizeof dspstr_,"Klantcode webshop : %d",*u(2,1));
							DisplayWarning(dspstr_, 578,0);
						}
					}
					else {curs=21;errnum=38;}
				}
				goto redo_k;
			}		
      if(mode==2 && key==111 && lst_recs[stu]){
	fasinit(stu);*u(stu,1)=lst_recs[stu];fasgeti(stu);
	zero(s(stu,1),s(stu,3)-s(stu,1));
      }
      if(fldlen(2,27)){
				k=*s(2,26)-'0';if(k<0 || k>9) k=0;
				if(fldlen(6,PrNrs[k])==0) k=0;
				if(*s(2,26)=='A') copy("*AKpr*",s(2,27),fldlen(2,27));
				else copy(&vptekst[k*10],s(2,27),fldlen(2,27));
      }
			if(key==18){curs=curspos_+1;goto redo_k;}
      k=*p_stu_3;
      if(key==101 && k=='\0') return NO;
      if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo_k;}
      if((k<'A' || k>'Z') && (k<'a' || k>'z') && (k<'0' || k>'9')) {errnum=30;curs=3;goto redo_k;}
      if(klcd && *s(2,2)=='\0') {errnum=38;curs=2;goto redo_k;}
      if(taal_chk(24)) {curs=curs_taal;goto redo_k;}
      if(fldlen(2,51)){
				if(selp_bf[1][0]=='\0') {*u(2,51)=0;selp_bf[1][50]='\0';}
				else if(cmpstr(&selp_bf[1][0],&selp_bf[1][50],fldlen(2,3))){
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					fasinit(2);
					copy(&selp_bf[1][0],s(2,3),fldlen(2,3));
					k=search(2,0); if(k==YES && errnum==0) errnum=39;
					if(!errnum){
						copy(s(2,3),&selp_bf[1][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[1][50],fldlen(2,3));
					}
					fakklnr=*u(2,1);
					copy(selp_bf[0],s(2,1),fldlen(2,0));
					*u(2,51)=fakklnr;
					if(errnum) {curs=51;goto redo_k;}
	
				}
      }
      if(fldlen(2,52)==2){ // relatieklant
				if(selp_bf[2][0]=='\0') {*u(2,52)=0;selp_bf[2][50]='\0';}
				else if(cmpstr(&selp_bf[2][0],&selp_bf[2][50],fldlen(2,3))){
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					fasinit(2);
					copy(&selp_bf[2][0],s(2,3),fldlen(2,3));
					k=search(2,0); if(k==YES && errnum==0) errnum=39;
					if(!errnum){
						copy(s(2,3),&selp_bf[2][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[2][50],fldlen(2,3));
					}
					fakklnr=*u(2,1);
					copy(selp_bf[0],s(2,1),fldlen(2,0));
					*u(2,52)=fakklnr;
					if(errnum) {curs=52;goto redo_k;}
	
				}
      }
      if(chk_intra){
				if(fldlen(2,74)) if(*s(2,74)=='\0'){errnum=38;curs=74;goto redo_k;}
				if(fldlen(2,75)) if(*i(2,75)==0){errnum=38;curs=75;goto redo_k;}
				if(fldlen(2,77)) if(*i(2,77)==0){errnum=38;curs=77;goto redo_k;}
      }
			if(fldlen(stu,16)>30 && *s(stu,16)){
				if(k=IbanTools(s(stu,16),s(stu,17),s(stu,12),0)) {curs=18+k-1; goto redo_k;} 
		  }
			if(key==109 && len2_120) {bst_inp();goto redo_k;}
      if(key==110 && fldlen(62,1)) {
	if(ovltest(2922)) ovlcall(2922,1); else DisplayMemo(stu);
	goto redo_k;
      }
      if(key==112 && *u(stu,1)) {dsp_info(); goto redo_k;}
      if(key!=5025 && key!=5026 && key!=108 && key!=101) goto redo_k;
    }

    else if(stu==3){/* grootboek */
      if(*s(3,4)=='\0')*s(3,4)='N';
      if(*s(3,5)=='\0')*s(3,5)='J';
      if(*s(3,6)=='\0')*s(3,6)='0';
      if(*s(3,7)=='\0')*s(3,7)='0';
      if(*s(3,10)=='\0')*s(3,10)='0';
      if(*s(3,11)=='\0')*s(3,11)='J';
      old_grb_=*l(3,2);
      redo_g:
      scrget(1,8);
			if(mode==1){
				scraddpicto(25,0,0,0,2,1,93,0,4,"vorig"); 
				scraddpicto(26,0,78,0,2,1,92,0,4,"volgend"); 
			}
			if(mode==2 && lst_recs[stu]) scraddpicto(10,0,74,2,4,2,532,0,0,"Kopieer vorige rekening"); 
      z=1;
      scrfld(z++,25,1);
      for(k=2;k<=7;k++) scrfld(z++,3,k);
      for(k=0;k<4;k++) scrifld(z++,fm_of2_1,&Bkhbtwpct[k]);
      for(k=8;k<=13;k++) scrfld(z++,3,k);
      if(fldlen(4,48)) scrfld(z++,3,14); else streepje(z++);
			if(fldlen(4,48)) scrfld(z++,3,15); else streepje(z++);
      z+=14;
      for(k=32;k<52;k++) scrfld(z++,3,k);
      dcurs_=curs; if(only_dsp) dcurs_=-1;
      key=scrupd(dcurs_,0x04A1);curs=2;curspos_=fldcurs;
			if ((key/0x100)==1) key=(key&0xFF)+5000;
      if(key==15 && only_dsp && CheckPw(0,11,0)){only_dsp=NO;goto redo_g;}
      if(key==106){
	if(mode==2) return NO;
	else return YES;
      }
      if(mode==2 && (key==111 || key==5010) && lst_recs[stu]){
				fasinit(stu);*u(stu,1)=lst_recs[stu];fasgeti(stu);
				zero(s(stu,1),s(stu,2)-s(stu,1));
      }
      k=*p_stu_3;
      if(key==101 && k=='\0') return NO;
      if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;curs=3;goto redo_g;}
      if(*l(3,2)==0) {errnum=38;curs=2;goto redo_g;}
      if(*s(3,4)!='J' && *s(3,4)!='N') {errnum=34;curs=4;goto redo_g;}
      if(*s(3,5)!='J' && *s(3,5)!='N') {errnum=34;curs=5;goto redo_g;}
      if(*s(3,6)=='\0')*s(3,6)='0';
      if(*s(3,7)=='\0')*s(3,7)='0';
      if(*s(3,11)=='\0')*s(3,11)='J';
      if(*s(3,10)=='\0')*s(3,10)='0';
      if(*s(3,5)=='J'){
	if(*s(3,10)!='0') {errnum=22;curs=13;goto redo_g;}
      }
      else{
	if(*s(3,10)=='0') {errnum=23;curs=13;goto redo_g;}
      }
      if(mode==1 && old_grb_!=*l(3,2)){
	if(geboekt()) {errnum=60;goto redo_g;}
      }
			if(key!=5025 && key!=5026 && key!=108 && key!=101) goto redo_g;
    }
		fasunlck(-2);
		if(stu==1 || stu==2 || stu==6){
			if(fldlen(stu,198)) *u(stu,198)=procid;
			if(fldlen(stu,199)) *u(stu,199)=*u(25,2);
		}
    if(mode==1){
      if(only_dsp) goto no_upd;
      if(stu==2 && chk_dblbtw()==NO) goto redo_k;
      errnum=fasupd(stu);
      if(stu==2 && fldlen(62,1)){
	*u(62,2)=*u(2,1);
	if(*u(62,1)) fasupd(62); else fasadd(62);
      }
      no_upd:;
      if(stu<10) lst_recs[stu]=*u(stu,1);
      fasflush(0);
    }
    else if(mode==2 || mode==3){
      if(stu==2){
				if(chk_dblbtw()==NO) goto redo_k;
#if FLAGQIC
			  if(*l(2,10)==0 && fldlen(2,137) && *s(2,137)=='\0'){
				  if(DisplayWarning("Geen BTW-nummer ingegeven, toch doorgaan?", 605,1)==NO) goto redo_k;
				}
#endif
			}
      errnum=fasadd(stu); if(stu<10) lst_recs[stu]=*u(stu,1);
      if(stu==3){
	if(errnum==0 && *u(3,1)>=5500) {faskill(3);errnum=9;}
      }
      if(stu==2 && fldlen(62,1)){
	*u(62,2)=*u(2,1); fasadd(62);
      }
      fasflush(0);fasunlck(-1);
    }
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
	if(key==5025) return 10;
	if(key==5026) return 11;
  return YES;
}

static DisplayExtraFuncties(stu_)
int16 stu_;
{
	int z,k,key,vt_,hz_;
	char buf1000_[1000],postnm_[25];

	copy(s(stu_,1),buf1000_,fldlen(stu_,0));

	FOREVER{
		scrget(1,7);cls();z=1;
		scraddfield(z,33,2,0x0A);scrifld(z++,VarTextFmt(14,0)," Extra opties ");
		scraddfield(z,10,5,2); scrofld(z++,stu_,3,-1);
		if(stu_==1 || stu_==2){
		  scraddfield(z,10,6,2); scrofld(z++,stu_,4,-1);
		  scraddfield(z,10,7,2); scrofld(z++,stu_,5,-1);scraddfield(z,17,7,2); scrofld(z++,stu_,6,-1);
		}
		z=30;hz_=10;vt_=10;
		if(stu_==2 && ovltest(244)){
			AddTextKey(z++,hz_,vt_,20,2,10015,"leveringsbons",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
		}
		else if(stu_==1 && ovltest(255)){
			AddTextKey(z++,hz_,vt_,20,2,10015,"bestelbons",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
		}
		if(stu_==2 && ovltest(264)){
			AddTextKey(z++,hz_,vt_,20,2,10016,"verhuringen",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
		}
		if(stu_==2 && ovltest(266)){
			AddTextKey(z++,hz_,vt_,20,2,10017,"offertes",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
		}
		if((stu_==2 || stu_==6) && ovltest(230)){
			AddTextKey(z++,hz_,vt_,20,2,10018,"prijsafspraken",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
		}
		if(stu_!=6 && hz_>10){hz_=10;vt_+=2;} // nieuwe lijn
		if(stu_<3 && ovltest(14)){
  		AddTextKey(z++,hz_,vt_,20,2,10011,"boekhoudrekening",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
  		AddTextKey(z++,hz_,vt_,20,2,10012,"openstaande facturen",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
		}

		if(fldlen(16,1) && ovltest(239)){
  		AddTextKey(z++,hz_,vt_,20,2,10013,"historieken",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
 		}
		if(fldlen(60,1) && fldlen(16,1)==0 && ovltest(236)){
  		AddTextKey(z++,hz_,vt_,20,2,10014,"statistieken",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
		}
		if(hz_>10){hz_=10;vt_+=2;} // nieuwe lijn
		if(stu_<3){
		  if(ovltest(2923)){
			  AddTextKey(z++,hz_,vt_,20,2,10019,"documenten",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
		  }
		  AddTextKey(z++,hz_,vt_,20,2,10001,"GDPR export fiche",0x007FFF);hz_+=20;if(hz_>=60){hz_=10;vt_+=2;}
		}
		if(fldlen(stu,198)){
			zero(postnm_,sizeof postnm_);
			if(*u(stu,198)) GetPostName(postnm_,*u(stu,198));
			scraddfield(z,1,20,0); scrifld(z++,VarTextFmt(22,0),"Laatst aangepast door ");
			scraddfield(z,23,20,2); scrifld(z++,VarTextFmt(15,0),postnm_);
		}
		if(fldlen(stu,199)){
			scraddfield(z,1,21,0); scrifld(z++,VarTextFmt(22,0),"Laatst gewijzigd op  ");
			scraddfield(z,23,21,2); scrofld(z++,stu,199,-1);
		}
		scraddfield(z,1,23,8);scrifld(z++,VarTextFmt(10,0)," F1 terug ");
 		key=scrupd(-1,0x1);
		if((key/0x10000)>0) key/=0x10000;
	  if(key==101) break;
		switch(key){
		  case 10001 : GdprExportFiche(stu_); break;
			case 10011 : ovlcall(14,stu_*10+0); break;
			case 10012 : ovlcall(14,stu_*10+1); break;
			case 10013 : fasinit(27);*u(27,2)=*u(25,2)-730;/* 2 jaar terug */
			             if(stu_==6){*s(27,4)='A';*u(27,6)=*u(stu_,1);}
				           else{
					           if(stu_==1) *s(27,4)='L'; else *u(27,4)='K';
								     *u(27,5)=*u(stu_,1);
				           }
								   ovlcall(239,2);
				           break;
			case 10014 : fasinit(27);*u(27,2)=*u(25,2)-730;/* 2 jaar terug */
					         if(stu_==1) *s(27,4)='L'; else *u(27,4)='K';
								   *u(27,5)=*u(stu_,1);
								   ovlcall(236,2);
				           break;
      case 10015 : fasinit(27); *u(27,5)=*u(stu_,1);
									 if(stu_==1) ovlcall(255,1);
									 else ovlcall(244,1); 
									 break;
      case 10016 : fasinit(27); *u(27,5)=*u(stu_,1);
									 ovlcall(264,1); 
									 break;
      case 10017 : fasinit(27); *u(27,5)=*u(stu_,1);
									 ovlcall(266,1); 
									 break;
      case 10018 : fasinit(27); 
	      				   if(stu_==6) {*s(27,4)='A';*u(27,6)=*u(stu_,1);}
									 else {*s(27,4)='K';*u(27,5)=*u(stu_,1);}
									 ovlcall(230,2); 
									 break;
			case 10019 : ovlcall(2923,stu_); break;
			default : break;
		}
		copy(buf1000_,s(stu_,1),fldlen(stu_,0));
  }
}

static DisplayLeveradres(stu_)
int16 stu_;
{
  int z,k,key,curs=2;

	FOREVER{
		redo:;
		scrget(1,275);z=1;
		scrofld(z++,stu_,3,-1);
 		for(k=143;k<=146;k++) scrfld(z++,stu_,k);
		key=scrupd(curs,0x1);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
	}
}



static DisplayEmailSettings(stu_)
int16 stu_;
{
	int z, k, key, curs = 2, dcurs_, g;

	FOREVER {
redo:;
		if (stu_ == 2)
#if FLAGCOC // CC adres bij klant is voor facturen/rappels
			scrget(2,503);
#else
			scrget(1,276);
#endif		
		else scrget(1,255);

		z = 1;
		scraddpicto(50, 0, 76, 0, 4, 2, 105, 1, 7, "^!B0X19A");

		if (stu_ == 2 && fldlen(7,1) && *u(stu_,1))
			scraddpicto(1,0,75,22,4,2,570,0,0,"Mail");

		scrofld(z++,stu_,3,-1);
		scrfld(z++,stu_,21);
		scrfld(z++,stu_,130);

		if(stu_==2){
#if !FLAGCOC
			scrfld(z++,stu_,129);
#endif
			for (k = 0; k < 7; k++)
				scrfld(z++,stu_,121+k);

			scrfld(z++,stu_,128);
			
			if(fldlen(2,128) && ovltest(2240)){
				scraddpicto(2,z-1,0,0,2,1,64,0,4,"Controleer ontvanger");
			  scraddpicto(50,0,65,17,2,1,105,1,7,"^!B2240A");
			}
			scrfld(z++,stu_,137);
		}
		dcurs_=curs; if(only_dsp) dcurs_=-1;
		key=scrupd(dcurs_,0x1);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
		if(key==5001){
			ShowSavedDocument(stu,(long)(*u(stu_,1)),0,0,0) ;
			goto redo;
		}
		if(stu_==2){
			if(key==5002){
				g=0;
				if (*l(2,10)==999999999 || *l(2,10)==0){
					if (fldlen(2,137) && *s(2,137)) g = CodaBoxCheckGLN(s(2, 137));
					else errnum=29;
				}
				else {
					g = CodaBoxCheckVAT(l(2,10), ""); // eerst proberen via KBO
					if (g < 1){
						g = CodaBoxCheckVAT(l(2,10),"BE");
					}
				}

				switch(g) {
					case 0 : DisplayWarning("E-facturatie NIET mogelijk (niet op het netwerk gevonden)", 593,0); break;
					case 1 : DisplayWarning("Peppol-formaat toegelaten", 578,0); break;
					case 2 : DisplayWarning("eFFF-formaat toegelaten", 578,0); break;
					default: DisplayWarning("GEEN E-facturatie toegelaten!", 593,0); break;
				}
			}
			if(!only_dsp){
				if(*s(stu_,21)=='\0'){
					for(k=0;k<7;k++) if(fldlen(stu_,121+k) && *s(stu_,121+k)=='J') break;
					if(k<7){errnum=38;curs=2;goto redo;}
				}
//				if(fldlen(2,128) && *s(2,128) && (*s(2,121)=='J' || *s(2,122)=='J')){curs=5;errnum=72;goto redo;}
			}
		}
		if(key==101) break;
	}
}

static lev_dfgrb()
{
  int16 curs=1,j,key,k,z,start_=0,dcurs_,curspos_;
  char *pdum,dumm_[10],*pvar;
  pdum=&dumm_[0];
 
	if(fldlen(3,1)==0) goto endsr;
  ram_recl=s(3,4)-s(3,1) + 2;/* + 2 bytes hash */
  max_line=fldlen(1,121)/2;
  if(max_line>(sizeof ram)/ram_recl) max_line=(sizeof ram)/ram_recl;
  hash_len=fldlen(3,1)+ fldlen(3,2)+fldlen(3,3);
  dat_len=hash_len;

  zero(ram,sizeof ram);
  for(k=0;k<max_line;k++){
    fasinit(3);*u(3,1)=*(uint16 *)(s(1,121)+k*2);fasgeti(3);
    hash_val=hash(3);
    stu2ram(3,k);
  }
  scrnum=0;
  FOREVER{
    redo:
    scrnum=0;scrget(1,209);z=1;
    if(fldlen(1,2)) scrofld(z++,1,2,-1); else scrofld(z++,1,1,-1);
    scrofld(z++,1,3,-1);
    for(j=start_;j<start_+10;j++){
      j++; scrifld(z++,fm_ou2,&j); j--;
      if(fieldspc(3,2,&pdum,fmt)>0){
				pvar=ram+(j*ram_recl + (s(3,2)-s(3,1)));
				scrifld(z++,fmt,pvar);
      }
      if(fieldspc(3,3,&pdum,fmt)>0){
				pvar=ram+(j*ram_recl + (s(3,3)-s(3,1)));
				scrifld(z++,fmt,pvar);
      }
    }
		if(start_>0) scraddpicto(1,0,75,9,4,2,18,0,4,"vorig"); 
		if((start_+10)<max_line) scraddpicto(2,0,75,17,4,2,13,0,4,"volgend"); 
		dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0x37E);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==15 && only_dsp && CheckPw(0,11,0)){only_dsp=NO;goto redo;}
    if(key==106) goto endsr;
    if(key==104){
      j=(curspos_-3)/3;j+=start_;
      ins_lin(3,j);
      curs=curspos_;goto redo;
    }
    if(key==105){
      j=(curspos_-3)/3;j+=start_;
      del_lin(3,j);
      curs=curspos_;goto redo;
    }
    for(k=start_;k<start_+10;k++){
      chk_again:;
      ram2stu(3,k);
      if(*l(3,2)==-1) *l(3,2)=0;
      if((*l(3,2) || *s(3,3)) && hash_val!=hash(3)){
				if(*l(3,2)){
					if(faskeyi(3,1,0)){errnum=39;curs=4+(k-start_)*3;goto redo;}
				}
				else{
					if(search(3,0)){errnum=39;curs=4+(k-start_)*3;goto redo;}
				}
				if(*s(3,5)!='J'){errnum=24;curs=4+(k-start_)*3;goto redo;}
				hash_val=hash(3);
      }
      else if(*s(3,3)=='\0'){fasinit(3);hash_val=0;}
      stu2ram(3,k);
    }
		if(key==5002 || key==103) {start_+=10; if(start_>=max_line-10) start_=max_line-10;}
		if(key==5001 || key==102) start_-=10; 
		if(start_<=0) start_=0;
    if(key==109)break;
    j=0;
    for(k=0;k<10;k++){ram2stu(3,start_+k);if(*s(3,3)=='\0') {j=k;break;}}
    curs=4+j*3;
  }
  for(k=0;k<max_line;k++){
    ram2stu(3,k);
    copy(s(3,1),s(1,121)+k*2,2);
  }
  endsr:;
}
 
static dsp_i_flag()
{

  if(fldlen(22,0)==0) goto endsr;

  fasinit(22);*u(22,2)=stu;*u(22,3)=*u(stu,1);
  if(faskeyi(22,1,1)) goto endsr;
  if(*u(22,2)!=stu) goto endsr;
  if(*u(22,3)!=*u(stu,1)) goto endsr;

  scraddf(119,23,78,7); scrifld(119,fm_os2,"IN");
  endsr:;
}

static scraddf(fld,v,h,attr)
int16 fld,v,h,attr;
{
  int16 *pi;
					
  pi=(int16 *)info;
  *(pi+0)=fld;
  *(pi+1)=v;
  *(pi+2)=h;
  *(pi+3)=attr;
  sendtask(procid+20,3,11,info,8);
  scrnum=0;
}

static get_newcode()
{
  int16 j,k,g,code_len_,num_len_,fmt_len_;
  long min_kod_=1,max_kod_,lbd_;
  char str_[15],code_[15],kar_,kod_fmt_[15],kltcodeprefix_[2];


  if(stu!=1 && stu!=2 && stu!=6) return NO;
  if(fldlen(stu,2)==0) return NO;
  zero(code_,sizeof code_);
  copy(s(stu,1),buf1000,fldlen(stu,0));
	if(stu==2){
		sysget(2985,2,kltcodeprefix_);
		if(*s(stu,2)=='\0' && kltcodeprefix_[0]) *s(2,2)=kltcodeprefix_[0];
	}
#if FLAGVBE// nieuwe klantcode steeds K, leverancier L
	if(stu==2) {*s(2,2)='K';	min_kod_=3600;}
	if(stu==1 && *s(stu,2)=='\0') *s(1,2)='L';
#endif
#if FLAGWYN  || FLAGPCQ // nieuwe klantcode steeds 50000
	if(stu==2 && *s(stu,2)=='\0') *s(2,2)='5';
#endif
#if FLAGCRL// nieuwe klantcode steeds 6000
	if(stu==2 && *s(stu,2)=='\0') *s(2,2)='7';
#endif
  if(*s(stu,2)) copy(s(stu,2),code_,fldlen(stu,2));
  else if(stu==6 && *i(stu,9)) stcli_d(code_,(long)(*i(6,9)),2,0);
  for(code_len_=0;code_len_<fldlen(stu,2);code_len_++) if(code_[code_len_]=='\0') break;
  fasinit(stu);num_len_=0; zero(kod_fmt_,sizeof kod_fmt_);
  g=faskeyi(stu,1,1);
  if(g){
    num_len_=5; if(num_len_>fldlen(stu,2)) num_len_=fldlen(stu,2);
    fmt_len_=num_len_;
    for(k=code_len_;k<fmt_len_;k++) kod_fmt_[k]='n';
  }
  else {
    for(k=code_len_;k<fldlen(stu,2);k++){
      kar_=*(s(stu,2)+k);
      if(kar_=='\0') break;
      if(kar_>='0' && kar_<='9'){kod_fmt_[k]='n';num_len_++;}
      else kod_fmt_[k]=kar_;
    }
    fmt_len_=k;
  }
  if(code_len_>=fmt_len_ || num_len_<1){errnum=34; goto endsr;}
  copy(code_,kod_fmt_,code_len_);
  zero(str_,sizeof str_);
  for(k=0;k<num_len_;k++) str_[k]='9';
  max_kod_=val(str_)+1;
  for(lbd_=min_kod_;lbd_<max_kod_;lbd_++){
    fasinit(stu); copy(kod_fmt_,s(stu,2),fmt_len_);
    stcli_d(str_,lbd_,num_len_,0);
    j=0;
    for(k=code_len_;k<fmt_len_;k++){
      if(kod_fmt_[k]=='n') *(s(stu,2)+k)=str_[j++];
      else *(s(stu,2)+k)=kod_fmt_[k];
    }
    if(faskeyi(stu,1,0)) break;
  }
  if(lbd_<max_kod_) copy(s(stu,2),code_,fldlen(stu,2));
 
  endsr:;
  copy(buf1000,s(stu,1),fldlen(stu,0)); copy(code_,s(stu,2),fldlen(stu,2));
}

static DisplayMemo(stu_)
int16 stu_;
{
  int16 curs=2,dcurs_;
  int16 z,k,key;
					
  FOREVER{
    redo:;
    scrget(2,122); z=1;
    scrofld(z++,stu_,3,-1);
		if(stu_==1){
			for(k=125;k<128;k++) scrfld(z++,1,k);
		}
		else{
      for(k=5;k<10;k++) scrfld(z++,62,k);
		}
    dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0x80);
    if(key==15 && only_dsp && CheckPw(0,11,0)){only_dsp=NO;goto redo;}
    if(key==108) break;
  }
}

static bst_inp()
{
  int16 curs=1,j,key,k,z,start_=0,dcurs_,curspos_;
  char *pdum,dumm_[10],*pvar;
  pdum=&dumm_[0];
 
  ram_recl=s(6,4)-s(6,1) + 2;/* + 2 bytes hash */
  max_line=len2_120/2;
  if(max_line>(sizeof ram)/ram_recl) max_line=(sizeof ram)/ram_recl;
  hash_len=fldlen(6,1)+ len6_2+len6_3;
  dat_len=hash_len;

  zeros(ram,sizeof ram);
  for(k=0;k<max_line;k++){
    fasinit(6);*pu_6_1=*(uint16 *)(s(2,120)+k*2);fasgeti(6);
    hash_val=hash(6);
    stu2ram(6,k);
  }
  scrnum=0;
  FOREVER{
    redo:
    scrget(2,130);z=1;
    scrofld(z++,2,3,-1);
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      j++; scrifld(z++,fm_ou3,&j); j--;
      if(fieldspc(6,2,&pdum,fmt)>0){
	pvar=ram+(j*ram_recl + (s(6,2)-s(6,1)));
	scrifld(z++,fmt,pvar);
      }
      if(fieldspc(6,3,&pdum,fmt)>0){
	pvar=ram+(j*ram_recl + (s(6,3)-s(6,1)));
	scrifld(z++,fmt,pvar);
      }
    }
    dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0x77E);curs=1;curspos_=fldcurs;
    if(key==15 && only_dsp && CheckPw(0,11,0)){only_dsp=NO;goto redo;}
    if(key==106) goto endsr;
    if(key==104){
      j=(curspos_-2)/3;j+=start_;
      ins_lin(6,j);
      curs=curspos_;goto redo;
    }
    if(key==105){
      j=(curspos_-2)/3;j+=start_;
      del_lin(6,j);
      curs=curspos_;goto redo;
    }
    for(k=start_;k<(start_+D_LIN_SCR);k++){
      chk_again:;
      ram2stu(6,k);
      if((*s(6,2) || *s(6,3)) && hash_val!=hash(6)){
	if(len6_2 && *s(6,2)) {*s(6,3)='.';copy(s(6,2),s(6,3)+1,len6_2);}
	if(search(6,0)){
	  errnum=39;curs=3+(k-start_)*3;goto redo;
	}
	hash_val=hash(6);
      }
      else if(*s(6,3)=='\0'){fasinit(6);hash_val=0;}
      stu2ram(6,k);
    }
    if(key==109)break;
    if(key==110) prt_bon();
    if(key==111) sort_bon();
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){ram2stu(6,k+start_);if(*s(6,3)=='\0') {j=k;break;}}
    curs=3+j*3;
  }
  for(k=0;k<max_line;k++){
    ram2stu(6,k);
    copy(s(6,1),s(2,120)+k*2,2);
  }
  endsr:;
}

static sort_bon()
{
  int16 k,len_,sw,max_;
  char str1[50],str2[50],*ps_;
									
  max_=max_line;
  for(k=0;k<max_;k++){
    ram2stu(6,k);
    if(*pu_6_1==0){del_lin(6,k);k--;max_--;}
    else{
      fasgeti(6);hash_val=*u(6,9);stu2ram(6,k);
    }
  }

  len_=fldlen(6,3);ps_=s(6,3);
  FOREVER{                                                      /* sorteren */
    sw=NO;
    for(k=0;k<max_-1;k++){
      ram2stu(6,k);stcli_d(str1,(long)(hash_val),2,0);copy(ps_,&str1[2],len_);
      ram2stu(6,k+1);stcli_d(str2,(long)(hash_val),2,0);copy(ps_,&str2[2],len_);
      if(*pu_6_1){
	if(cmp_srt(str1,str2,len_+2)==1){
	  ram2stu(6,k);
	  copy(s(6,1),buf1000,dat_len);
	  copy(&hash_val,buf1000+dat_len,2);
	  ram2stu(6,k+1);
	  stu2ram(6,k);
	  copy(buf1000,s(6,1),dat_len);
	  copy(buf1000+dat_len,&hash_val,2);
	  stu2ram(6,k+1);
	  sw=YES;
	}
      }
    }
    if(sw==NO) break;
  }
}

static cmp_srt(p1,p2,len)
char *p1,*p2;
int16 len;
{
  while(len--){
    if(*p1>*p2) return 1;
    if(*p1<*p2) return -1;
    p1++;p2++;
  }
  return 0;
}

static prt_bon()
{
  int16 form_dat[8],pr_mode,prtnr,j,k,n,q_art_,beg_kol2_;
  char str_[16];

  q_art_=0;
  for(k=0;k<max_line;k++){
    ram2stu(6,k);
    if(*s(6,3)) q_art_++;
  }
  beg_kol2_=-1;
  if(q_art_>=30){
    j=0;
    for(k=0;k<max_line;k++){
      ram2stu(6,k);
      if(*s(6,3)) j++;
      if(j>q_art_/2) break;
    }
    beg_kol2_=k;
  }
  k=80; if(beg_kol2_>=0) k=96;
 
  getsysprNew(5,form_dat,&pr_mode,&prtnr);
  if((errnum=prtopen(prtnr,form_dat,6,k,pr_mode,4))!=0) goto endsr;
  free=999;

  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t40eb>"); prttext("Bestelformulier");
  prttext("<eb><t72>");prttext("Blz.<ppp>.");
  prtbuf(1);

  zero(str_,sizeof str_);
  prttext("<t30>Tel.: ");
  sysget(150,15,str_);prttext(str_);
  prttext("<t57>Fax.: ");
  sysget(204,15,str_);prttext(str_);
  prtbuf(2);

#if 0
  z=1;
  k=YES; if(fldlen(6,2)==0) k=NO;
  prtitab(z,fm_os8,"        ",5,-1); prttitle(z++,"Aantal",3);
  prttab(z,6,1+k,5,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,5,40); prttitle(z++,"Naam",3);
  prtbuf(3);
#endif
  if(klcd){
    prtfld(2,2,-1);prtblank(2);
  }
  de_heer(2);
  prtifld(fm_us50,nm_dehr,-1);nextline();
  prtfld(2,4,-1);nextline();
  prtfld(2,5,-1);prtblank(2);prtfld(2,6,-1);nextline();
  if(fldlen(2,7)){
    prtfld(2,7,-1);nextline();
  }
  nextline();

  prttext("<t3bu>Aantal<but10bu>Code<but16bu>Omschrijving<bu>");
  if(beg_kol2_>=0) prttext("<t50bu>Aantal<but57bu>Code<but63bu>Omschrijving<bu>");
  nextline();nextline();
  if(beg_kol2_<0) beg_kol2_=max_line; k=0;n=beg_kol2_;
  FOREVER{
    for(k;k<beg_kol2_;k++){
      ram2stu(6,k);
      if(*s(6,3)){
	prttext("<t3>......");
	prttext("<t10>");prtfld(6,2,-1);
	prttext("<t16>");prtfld(6,3,-1);
	k++;break;
      }
    }
    for(n;n<max_line;n++){
      ram2stu(6,n);
      if(*s(6,3)){
	prttext("<t50>......");
	prttext("<t57>");prtfld(6,2,-1);
	prttext("<t63>");prtfld(6,3,-1);
	n++;break;
      }
    }
    nextline();
    if(free<0) break;
    if(k>=beg_kol2_ && n>=max_line) break;
  }
  prtclose();
  endsr:;
}


static fichkil()
{
  int16 key;

  redo:
  scrget(1,10);
  scrifld(1,fm_os20,nm_20);
  scrfld(2,25,1);
  scrofld(3,stu,3,-1);
  key=scrupd(0xFFFF,0x419);
  if(key==111) ovlexit(-1);
  if(key==101) return NO;
  if(key!=104 && key!=105) {errnum=21;goto redo;}
  if(key==104){
    if(stu<4){
      if(geboekt()) {errnum=25;goto redo;}
    }
    if(stu==1 || stu==2 || stu==6) spec_kill(stu);
    else faskill(stu);
    faskill(stu);
    fasflush(0);
  }
  return YES;
}

static spec_kill(stu)
uint16 stu;
{
  int16 j,z;

  scrnum=0;scrget(1,170); z=3;
  scrifld(z,fm_os63,"                    Schrappen van aanverwante fiches ");
  scrchat(z,0x2);scrupd(-3,0);
  z=6;
  if(stu==1){
    z=kil_bew(z,stu,7,11);
    z=kil_bew(z,stu,11,2);
    z=kil_bew(z,stu,13,2);
    z=kil_bew(z,stu,22,3);
		z=kil_bew(z,stu,16,15);
		z=kil_bew(z,stu,60,12);
		z=kil_bew(z,stu,86,5);
    faskill(stu);
  }
  else if(stu==2){
    z=kil_bew(z,stu,7,11); 
    z=kil_bew(z,stu,62,2);
    z=kil_bew(z,stu,22,3);
    if(fldlen(8,1)){z=kil_bew(z,stu,8,3);}
    z=kil_bew(z,stu,9,2);
		z=kil_bew(z,stu,16,10);
    z=kil_bew(z,stu,60,2);
		z=kil_bew(z,stu,86,5);
		z=kil_bew(z,stu,95,2);
    faskill(stu);
  }
  else if(stu==6){
	  for(j=0;j<10;j++) if(*u(6,1)==TbDiversArtikel[j]) break;
		if(j<10) {errnum=63;goto endsr;} // blokkeren divers-artikel
		z=kil_bew(z,stu,9,3);
    z=kil_bew(z,stu,11,3);
		z=kil_bew(z,stu,16,20);
    z=kil_bew(z,stu,22,3);
		z=kil_bew(z,stu,53,10);
    z=kil_bew(z,stu,60,22);
		z=kil_bew(z,stu,64,3);
		z=kil_bew(z,stu,66,2);
    z=kil_bew(z,stu,91,2);
    z=kil_bew(z,stu,93,2);
		z=kil_bew(z,stu,95,3);
    faskill(stu);
  }
endsr:;

  scrifld(21,fm_os63,"            Druk F8 om verder te gaan ...");scrchat(22,2);
	scrupd(-1,0x81);
}
 
static kil_bew(z,mstu_,bstu_,nr_)
int16 z,mstu_,bstu_,nr_;
{

  int16 j,g,mode_,len1_;
  uint16 mrec_,*prec_,dcnt_,*pu1_;
  long *lprec_,*pl1_,n,div_rec_;

  if(fldlen(bstu_,1)==0) goto endsr; // structuur bestaat niet 
	if(fldlen(bstu_,nr_)==0) goto endsr;
  switch(bstu_){
    case 7 : fileopen(7);
						 scrifld(z++,fm_os63,"Schrappen bestaande documenten ...");
						 lprec_=l(7,nr_); break;
    case 8 : if(fldlen(8,1)==0) break;
				     fileopen(8);
						 scrifld(z++,fm_os63,"Schrappen bestaande leveringsbons ...");
						 prec_=u(8,nr_); break;
    case 9 : fileopen(9);
						 scrifld(z++,fm_os63,"Schrappen bestaande prijsafspraken/omzetfiches ...");
						 prec_=u(9,nr_); break;
    case 11: prec_=u(11,nr_);
						 scrifld(z++,fm_os63,"Schrappen bestaande aankoopfiches ...");
						 break;
    case 13: prec_=u(13,nr_);
						 scrifld(z++,fm_os63,"Schrappen bestaande peppolkoppelingen ...");
						 break;
		case 16: fileopen(13);
						 scrifld(z++,fm_os63,"Schrappen bestaande historieken ...");
						 lprec_=l(16,nr_); break;
    case 22: fileopen(15);
						 scrifld(z++,fm_os63,"Schrappen bestaande info ...");
						 prec_=u(22,nr_); break;
    case 53: scrifld(z++,fm_os63,"Schrappen blokjes kassa ...");
   					 prec_=u(53,10); break;
    case 60: fileopen(14);
				     scrifld(z++,fm_os63,"Schrappen bestaande statistieken ...");
						 lprec_=l(60,nr_); break;
    case 62: prec_=u(62,nr_);
						 scrifld(z++,fm_os63,"Schrappen bestaande klanten-memo ...");
						 break;
		case 64: prec_=u(64,nr_);
				     scrifld(z++,fm_os63,"Schrappen extra barcodes ...");
						 break;
		case 66: prec_=u(66,nr_);
						 scrifld(z++,fm_os63,"Schrappen bestaande stocklocaties ...");
						 break;
    case 86: fileopen(10);
						 scrifld(z++,fm_os63,"Schrappen bestaande boekingen in jaararchief ...");
						 prec_=u(86,nr_); break;
    case 91: fileopen(9);
						 scrifld(z++,fm_os63,"Schrappen bestaande kasverkopen ...");
						 prec_=u(91,nr_); break;
    case 93: fileopen(11);
						 scrifld(z++,fm_os63,"Schrappen bestaande kassa-promoties ...");
						 prec_=u(93,nr_); break;
    case 95: fileopen(9);
						 scrifld(z++,fm_os63,"Schrappen bestaande verhuurfiches ...");
						 prec_=u(95,nr_); break;
    default: break;
  }
	scrupd(-3,0);
  mrec_=*u(mstu_,1);
  if(bstu_==86){
    mrec_=*u(mstu_,1)+(mstu_-1)*30000;
  }
	if(bstu_==16 && mstu_==6){ // historieken naar divers artikel zetten 
		div_rec_=*u(6,1);
		if(*i(6,9)==99) div_rec_=TbDiversArtikel[9]; // leeggoed divers
  	else {
	  	for(j=0;j<8;j++) if(*f(6,28)==btw_pct[j]) break;
  		if(j<8) div_rec_=TbDiversArtikel[j];
		}
	}
  fasinit(bstu_); dcnt_=0;
  len1_=fldlen(bstu_,1); pu1_=u(bstu_,1);pl1_=l(bstu_,1);
  n=0;scrnum=0;
  FOREVER{
    if(len1_==4) *pl1_=++n; else *pu1_=++n;
		if((n%500)==0) {scrifld(24,fm_ol8,&n);scrupd(-3,0);}
    g=fasgeti(bstu_);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
      switch(bstu_){
				case 7 : if(*lprec_==mrec_ && mstu_==*u(7,10)){faskill(7);dcnt_++;}
								 break;
				case 8 : if(*prec_==mrec_){
									 fasinit(58);*u(58,2)=*u(8,1);mode_=1;
									 FOREVER{
										 if(faskeyu(58,1,mode_)) break; mode_=2;
										 if(*u(58,2)!=*u(8,1)) break;
										 faskill(58);
									 }
									 faskill(8); dcnt_++;
								 }
					 break;
				case 9 : if(*prec_==mrec_){faskill(9);dcnt_++;}
					 break;
				case 11: if(*prec_==mrec_){faskill(11);dcnt_++;}
					 break;
				case 13: if(*prec_==mrec_){faskill(13);dcnt_++;}
					 break;
				case 16: if(*lprec_==mrec_){
									 if(bstu_==16 && mstu_==6){ // historieken naar divers artikel zetten 
									   *l(16,20)=div_rec_;fasupd(16);
									 }
									 else faskill(16);
									 dcnt_++;
								 }
					 break;
				case 22: if(*i(22,2)==mstu_ &&  *prec_==mrec_){faskill(22);dcnt_++;}
					 break;
				case 53: if(*prec_==mrec_){faskill(53);dcnt_++;}
					 break;
				case 60: if(*lprec_==mrec_){faskill(60);dcnt_++;}
					 break;
				case 62: if(*prec_==mrec_){faskill(62);dcnt_++;}
					 break;
				case 64: if(*prec_==mrec_){faskill(64);dcnt_++;}
					 break;
				case 66: if(*prec_==mrec_){faskill(66);dcnt_++;}
					 break;
				case 86: if(*prec_==mrec_){faskill(86);dcnt_++;}
					 break;
				case 91: if(*prec_==mrec_){faskill(91);dcnt_++;}
					 break;
				case 93: if(*prec_==mrec_){faskill(93);dcnt_++;}
					 break;
				case 95: if(*prec_==mrec_){faskill(95);dcnt_++;}
					 break;
				default: break;
      }
    }
  }
	if(dcnt_){scraddfield(z-1+50,50,z-2,0xB); scrifld(z-1+50,fm_ou5,&dcnt_);}
	scrupd(-3,0);
  fasflush(0);
endsr:;
	return z;
}
 
static de_heer(stu_)
int16 stu_;
{
  int16 g,j,k,len;

  len=fldlen(stu_,3);if(len>50) len=50;
  for(k=0;k<52;k++) nm_dehr[k]='\0';
  for(k=0;k<len-1;k++){
    if(*(s(stu_,3)+k)=='*')break;
  }
  if(k==len-1){/* no * */
    copy(s(stu_,3),nm_dehr,len);
  }
  else{
    for(g=k+1;g<len;g++) if(*(s(stu_,3)+g)!=' ') break;
    if(g>=len) copy(s(stu_,3),nm_dehr,len);
    else{
      for(j=len-1;j>=g;j--) if(*(s(stu_,3)+j)>' ') break;
      j=j-g+1;
      copy(s(stu_,3)+g,nm_dehr,j);
      nm_dehr[j++]=' ';
      g=len-j;if(g>k) g=k;
      copy(s(stu_,3),&nm_dehr[j],g);
    }
  }
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
  int16 k,key,curs,z,curs_taal;
 
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
		if(bfnr==2){
			if(fldlen(stu,200)){
				if(*u(stu,200)==1){
					scrchat(z-1,0xB); 
					scraddpicto(7,z-1,0,0,2,1,70,0,3,"Maak actief");
				}
				else{
					scrchat(z-1,0xFF);
					if(*u(stu,200)==0) scraddpicto(7,z-1,0,0,2,1,71,0,4,"Blokkeer");
					else scraddpicto(7,z-1,0,0,2,1,71,0,0,"Blokkeer");
				}
			}
		}
    for(k=3;k<16;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,16);
    for(k=17;k<MAXFLD;k++) scrfld(z++,stu,k);
    key=scrupd(curs,0x0080);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5007 && fldlen(stu,200)){ // blokkeer
			if(*u(stu,200)==0) *u(stu,200)=1; else *u(stu,200)=0;
			goto redo_l;
		}
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
		if(bfnr==2){
			if(fldlen(stu,200)){
				if(*u(stu,200)==1){
					scrchat(z-1,0xB); 
					scraddpicto(7,z-1,0,0,2,1,70,0,3,"Maak actief");
				}
				else{
					scrchat(z-1,0xFF);
					if(*u(stu,200)==0) scraddpicto(7,z-1,0,0,2,1,71,0,4,"Blokkeer");
					else scraddpicto(7,z-1,0,0,2,1,71,0,0,"Blokkeer");
				}
			}
		}
    for(k=3;k<24;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,24);
    for(k=25;k<MAXFLD;k++) scrfld(z++,stu,k);
    key=scrupd(curs,0x0080);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5007 && fldlen(stu,200)){ // blokkeer
			if(*u(stu,200)==0) *u(stu,200)=1; else *u(stu,200)=0;
			goto redo_k;
		}
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
  for(k=2;k<201;k++){
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

static nextline()
{
  free=prtline();
}

static flag geboekt()
{
  uint16 rec__;

  rec__=*u(stu,1)+30000*(stu-1);
  if(fasopen(files[3].filname,0)==0){
    fasinit(4);
    *u(4,5)=rec__;
    if(faskeyi(4,4,2)==0){
      if(*u(4,5)==rec__) return YES;
    }
  }
  if(fasopen(files[4].filname,0)==0){
    fasinit(5);
    *u(5,2)=rec__;
    if(faskeyi(5,1,0)==0) return YES;
  }
  return NO;
}
 
static chk_dblbtw()
{
  int16 ok_=YES;
  uint16 key,krec_,g,n;
  long btwnr_,*p_btwnr_;

  p_btwnr_=l(2,10);btwnr_=*p_btwnr_;krec_=*u(2,1);
  btwnr_=*p_btwnr_ & 0xBFFFFFFF;
  if(btwnr_==000000000 || btwnr_==999999999) return YES;
  copy(s(2,1),buf1000,fldlen(2,0));
  fasinit(2); n=0;scrget(1,7);scrupd(-3,0);
  FOREVER{
    *u(2,1)=++n;
    g=fasgeti(2);
    if(g==47)break;
    if(g!=46 && n!=krec_){/* deleted record */
      if(*p_btwnr_==btwnr_) {ok_=NO;break;}
    }
  }
  if(ok_==NO){
    scrget(1,169);
    scrifld(10,fm_os63,"BTW-nummer is al gebruikt door :");
    scrfld(12,2,3);
    scrifld(18,fm_os63,"Toch doorgaan ???");
    key=scrupd(-1,0x18);
    if(key==104) ok_=YES;
  }
  copy(buf1000,s(2,1),fldlen(2,0));
  return ok_;
}


static Fiches2Xls()
{
  int16 k,max_,ok_,mode4_;
	char str_[100];
	uint16 searcnr;

	if(XlsStu!=stu){
	  MaxXlsFldNr=0;max_=150; if(stu==6) max_=185;
	  for(k=1;k<max_;k++){ // boven 120 zitten data achter de schermen 
		  if(fldlen(stu,k)){
			  XlsFldNr[MaxXlsFldNr]=k;SelectXlsFldNr[MaxXlsFldNr]='N';
				MaxXlsFldNr++; if(MaxXlsFldNr>=57) break; // Maximaal 57 kolommen 
			}
		}
		XlsStu=stu;
	}

	if(AskFields2Xls()==NO) goto endsr;
	if(selp_ask()==YES) goto endsr;
	scrget(1,7);scrupd(-3,0);
	zero(str_,sizeof str_);
	if(stu==1) copy0("Leveranciers.Xls",str_,17); 
	else if(stu==2) copy0("Klanten.Xls",str_,11);
	else copy0("Grootboekfiches.Xls",str_,19);
  XlsRef=XlsCreate(str_);
  if(XlsRef<=0) {errnum=1;goto endsr;}
	XlsRij=1;XlsKol=1;
	for(k=0;k<MaxXlsFldNr;k++){ // header wegschrijven 
		if(SelectXlsFldNr[k]=='J'){
//			zero(str_,sizeof str_);
//			sprintf(str_,"Veld : %2d,%3d",stu,XlsFldNr[k]); XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_);
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,s(stu,-XlsFldNr[k]),0);
		}
	}
	XlsRij++;
	fasinit(stu);
  FOREVER{
		next:;
    if(faskeyi(stu,2,2)) break;
    if(selp_tst()){
			if(stu==2){
				fasinit(4);searcnr=*u(2,1)+30000;*u(4,5)=searcnr; mode4_=1; ok_=NO;
				FOREVER{
					if(faskeyi(4,4,mode4_)) break; mode4_=2;
					if(*u(4,5)!=searcnr) break;
	  			if(*u(4,4)>= *u(25,2)-365){ok_=YES;break;}
				}
				if(ok_==NO) goto next;
			}
			XlsKol=1;
			for(k=0;k<MaxXlsFldNr;k++){ 
				if(SelectXlsFldNr[k]=='J'){
					zero(str_,sizeof str_);
					if((stu==1 && XlsFldNr[k]==16) || (stu==2 && XlsFldNr[k]==24)){ // juiste taalletter uitschrijven 
						if(*s(stu,XlsFldNr[k])>=4) *s(stu,XlsFldNr[k])=0;
            *s(stu,XlsFldNr[k])=talen[*s(stu,XlsFldNr[k])];
					}
					WriteFld2Xls(XlsRij,XlsKol++,stu,XlsFldNr[k],0);
				}
			}
			XlsRij++;
		}
	}
	XlsClose(XlsRef,1);
	endsr:;
}

static AskFields2Xls()
{
  int16 j,k,n,z,key,curs=1,start_;

	start_=0;
	FOREVER{
		redo:;
	  scrnum=0;scrget(1,250);z=1;
		if(start_>0) scraddpicto(1,0,74,1,4,2,18,0,4,"vorig"); 
		if((start_+57)<MaxXlsFldNr) scraddpicto(2,0,74,22,4,2,13,0,4,"volgend"); 
		for(k=0;k<19;k++){
		  for(j=0;j<3;j++){
				n=start_+k+19*j;
				if(n<MaxXlsFldNr){
					scrifld(z++,fm_uJN,&SelectXlsFldNr[n]);scrifld(z++,fm_os20,s(stu,-XlsFldNr[n])); 
				} else z+=2;
			}
		}
		key=scrupd(curs,0x81);if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) return NO;
		if(key==5001){start_-=57;if(start_<0) start_=0;goto redo;}
		if(key==5002 && (start_+57)<MaxXlsFldNr) {start_+=57;goto redo;}

		for(k=0;k<MaxXlsFldNr;k++) if(SelectXlsFldNr[k]=='J') break; if(k>=MaxXlsFldNr) {errnum=38;goto redo;}
		if(key==108) break;
	}
	return YES;
}


#include "Std\XlsFunc.c"

static copy0(ps,pd,len_)
char *ps,*pd;
int16 len_;
{
  int16 fuval=0;
				
  while(*ps){
    *pd++=*ps++;
    fuval++;
    if(fuval>=len_) break;
  }
  *pd='\0';
  return fuval;
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

static GdprExportFiche(stu_)
int16 stu_;
{
  int16 k;
  char str_[100];

  zero(str_,sizeof str_);
  k=copy0(s(stu_,3),str_,25);
  cnv_fname(str_,k);
  k=copy0(".CSV",&str_[k],5);
	fasclos(-2);if(fasopen(str_,12)) {errnum=9;goto endsr;}
  fasinit(80);seqo_pos=0;seqo_mode=2; DelimKar=';';
  zero(seqo_str,sizeof seqo_str);pos=0;

  char2str("Nr",10);
  char2str("Naam",10);
	char2str("Adres",10);
	char2str("Pc",10);
	char2str("Gemeente",10);
	if(fldlen(stu_,7)) char2str("Land",10);
	if(fldlen(stu_,8)) char2str("Telefoon",10);
	if(fldlen(stu_,9)) char2str("Fax",10);
	if(fldlen(stu_,20)) char2str("Gsm",10);
	if(fldlen(stu_,10)) char2str("BTW-nummer",10);
	if(fldlen(stu_,22)) char2str("Buitenl.BTW-nummer",10);
	if(fldlen(stu_,21)) char2str("Email",10);
	if(fldlen(stu_,130)) char2str("CC-Email",10);
	if(stu_==2 && fldlen(stu_,129)) char2str("Bkh-Email",10);
	char2str("Opmerkingen",15);
	seqo_dumpline(YES);
	if(fldlen(stu_,2)) seqo_fld(stu_,2); else seqo_fld(stu_,1);
	seqo_fld(stu_,3);
	seqo_fld(stu_,4);
	seqo_fld(stu_,5);
	seqo_fld(stu_,6);
	seqo_fld(stu_,7);
	seqo_fld(stu_,8);
	seqo_fld(stu_,9);
	seqo_fld(stu_,20);
  seqo_fld(stu_,10);
	seqo_fld(stu_,22);
	seqo_fld(stu_,21);
	seqo_fld(stu_,130);
	if(stu_==1){
		for(k=24;k<=29;k++) seqo_fld(stu_,k);
	}
	if(stu_==2){
		seqo_fld(stu_,129);
		for(k=68;k<=71;k++) seqo_fld(stu_,k);
	}
	seqo_dumpline(YES);
	fasclos(-2);

endsr:;
}

//// SEQO-routines 
 
static cnv_fname(ps_,len_)
char *ps_;
int16 len_;
{
  char kar_;
  int16 k;
									
  for(k=0;k<len_;k++){
    kar_=*(ps_+k);
    if(kar_==0) break;
    if(kar_>='A' && kar_<='Z') continue;
    if(kar_>='a' && kar_<='z') continue;
    if(kar_>='0' && kar_<='9') continue;
    if(kar_==' ' || kar_=='-' || kar_=='_') continue;
    *(ps_+k)=' ';
  }
}


static seqo_fld(stu_,fld_)
int16 stu_,fld_;
{
  if(fldlen(stu_,fld_)){
    fmt_get(stu_,fld_);
    seqo_var(fmt,s(stu_,fld_));
  }
}

static seqo_var(fm_,pvar_)
char *fm_,*pvar_;
{
  int16 yy,mm,dd,len_;
  float fbd_;
  char str_[20];
 
  if(fm_[1]==0xC8 || fm_[1]==0x88){/* string */
    len_=fm_[2];
    char2str(pvar_,len_);
  }
  else if(fm_[1]==0xD0 || fm_[1]==0x90){/* uint16 */
    fbd_=*(uint16 *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xD1 || fm_[1]==0x91){/* integer */
    fbd_=*(int16 *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xD3 || fm_[1]==0x93){/* long */
    fbd_=*(long *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xD4 || fm_[1]==0x94){/* float */
    fbd_=*(float *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xD5 || fm_[1]==0x95){/* double */
    fbd_=*(double *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=DelimKar;
  }
  else if(fm_[1]==0xC0 || fm_[1]==0x80){/* date */
    if(*(uint16 *)pvar_==0) seqo_str[pos++]=DelimKar;
    else{
      jddate(*(uint16 *)pvar_,&yy,&mm,&dd);
      stcli_d(str_,(long)dd,2,0);str_[2]='/';
      stcli_d(&str_[3],(long)mm,2,0);str_[5]='/';
      stcli_d(&str_[6],(long)yy,4,0);
      char2str(str_,10);
    }
  }
  else if(fm_[1]==0xA8 || fm_[1]==0xE8){/* grb */
    zero(str_,sizeof str_);
    grb_deco(str_,(long *)pvar_);
    char2str(str_,10);
  }
	else if(fm_[1]==0x98 || fm_[1]==0xD8){// btw
		zero(str_,sizeof str_);
		if(*(long *)pvar_){
			btw_deco(&str_[0],(long *)pvar_,0);
			if(str_[9]!='\0'){copy("BE-",str_,3);btw_deco(&str_[3],(long *)pvar_,1);}
			else{copy("BE-0",str_,4);btw_deco(&str_[4],(long *)pvar_,1);}
		}
		char2str(str_,15);
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
      if(seqo_str[k]==DelimKar) seqo_str[k]='.';// delete | 
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;// delete trailing blanks 
    pos++;
  }
  seqo_str[pos++]=DelimKar;
}

static flt2str(bd_)
float bd_;
{
  int16 k,dlen_;
  char buff[15];
  double bedrag_,add_=0,dfactor_;
  long val_,value;
							
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  dfactor_=10000.;dlen_=4; if(bedrag_<-10000 || bedrag_>10000){dfactor_=100.;dlen_=2;}
  val_=bedrag_*dfactor_+add_;value=val_/dfactor_;
 
  zero(buff,sizeof buff);
  stcli_d(&buff[0],value,10,1);
  for(k=0;k<10;k++){
    if(buff[k]=='\0') break;
    if(buff[k]!=' ') seqo_str[pos++]=buff[k];
  }
  value=val_-value*dfactor_;
  if(value){
    seqo_str[pos++]=',';
    if(value<0) value=-value;
    zero(buff,sizeof buff);
    stcli_d(&buff[0],value,dlen_,0);
    for(k=dlen_;k>=0;k--) if(buff[k]!='0') break;
    copy(&buff[0],&seqo_str[pos],k+1);pos+=k+1;
  }
}
 

static seqo_dumpline(add_eor_)
int16 add_eor_;
{
	int k;
	  
  CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
	if(add_eor_){seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;}
  seqo_len=0;
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
    if(seqo_len){
      fasseqo(80,seqo_mode,seqo_len+4);
      seqo_pos+=seqo_len;
      *l(80,1)=seqo_pos;
      seqo_len=0;
		}
  }
	zero(seqo_str,sizeof seqo_str);pos=0;
}
/////

 
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

static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
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
  parmcall[7]=0x00;/* ALLE REKENINGEN ! */
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}
