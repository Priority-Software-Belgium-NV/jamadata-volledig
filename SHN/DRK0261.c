/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0261GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0261dat
#define ovlcod DRK0261cod
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
   
char ovldat[] = "drk0261  00:02 25/11/10 (c) Jamadata";
	// FLAGCOC : soortetiket per lijn kunnen kiezen (prt_ray en prt_prijs)
  // FLAGGDN : soortetiket per lijn kunnen kiezen (prt_ray en prt_prijs)
	// FLAGPED : affiche in portrait of landscape via vraag
   

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXFLD          100
#define flag            uint16
#define ETIK            0
#define RAYON           1
#define AFFICHE         2
#define DIM_TBE         1000
#define D_LIN_SCR       19
#define ESIGN           '\x80'

static char *defname[] = {"Etiketten","Rayon-etiketten","Prijsaffiches"};

extern char *s();
extern int16 *i();
extern uint16 *u();
static uint16 hash();
extern long *l();
extern long val();
extern float *f();
static float *prf(),round();
extern double *d();
extern double valu_cnv();

static long *pl_80_1;
static char *rec_ele();
static float get_num();
extern uint16 datejd();
static uint16 get_date();
static int16 date2str();


extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];
extern uint16 jamin1[5];

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os59[]  = {7,0x88,59,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_us13[]  = {7,0xC8,13,0,0,0,0};
static char fm_us8[]   = {7,0xC8,8,0,0,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x20,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x20,0};
static char fm_uu1_[]  = {6,0xD0,1,0,0x00,0};
static char fm_ul6[]   = {6,0xD3,6,0,0x70,0};
static char fm_of9_0[] = {6,0x94,9,0,0x30,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf6_3[] = {6,0xD4,6,3,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_ANIP[]= {15,0xC8,1,0,0x09,0,'A','A','I','I','N','N','P','P',0};
static char fm_u_FSV[] = {13,0xC8,1,0,0x09,0,'F','F','S','S','V','V',0};
static char fm_u_FB[] = {11,0xC8,1,0,0x01,0,'F','F','B','B',0};
static char fm_u_LS[] = {11,0xC8,1,0,0x09,0,'L','L','S','S',0};
static char fm_u_09[] = {9,0xC8,1,0,0,0,'0','9',0};
 
/* breedte in punten formaat 90: spatie, A-Z, a-z, 0-9,REST=150 */
//static int16 lbreedte[64] = {116,240,240,245,245,226,208,260,244,95,188,245,202,285,
//		    243,260,225,260,242,223,208,245,228,285,228,228,206,194,
//		    210,173,215,173,145,194,219,108,132,219,112,321,219,194,
//		    215,215,173,149,132,215,194,280,198,194,173,194,186,198,
//		    194,198,194,194,194,194,194,150};


static int16 free,sys3596,sys3724,stu=6,etikaant,mode,max_kprx,skip_aant;
static int16 sys3614[3],prx_nr,fls_nr,x_offset[3],y_offset[3];
static uint16 inq_lev,grp_beg,grp_end,soort_ray=1,dat_beg,dat_end,pda_nr,sys4408;
static uint16 drv_lev,drv_grp,tot_etik,prx_loff,dt_exec,dt_pbeg,dt_pend;
static char fmt[40],vptekst[100],oldnm[50],etikmode,grp_used[101];
static char type_prx[6],def_munt[4],nm_etiket[4][51];
static char p_fls_bak,only_promo;
static flag chk_btoeg=NO,klcd,lvcd,arcd=NO,prt2pdf;
static flag sear_stt,sys3876,sys3894,sys4368,sys4404;
static char sys3896[6];
static char p_et_prijs='J',p_et_ray='J',AfficheSoortAfdruk='L';

static char seqo_str[1500],*p_data;
static char filnam[80],fmt[40];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;

static char *ps_6_3;
static uint16 *pu_6_1,len6_2,len6_3;
static float lg_bak,lg_fles;
static flag sgrp_used,slev_used,p_max_grp;
					
static struct _tbe {
  uint16 aantal;
  uint16 recnr;
  char code[15];
  char eancode[15];
  char omschr[36];
  char aff_hdr[20];/* titel affiche */
  char promo_txt[15];
	char p_fls_bak;
  float vp_prx;
  float lg_bak;
  float vp_fles;
  float lg_fles;
  char opm[31];
  float inhoud;
  float gewicht;
	unsigned dt_prijs;
  uint16 hash;
#if FLAGCOC
	char prt_prijs;
  char prt_ray;
#endif
} tbe[DIM_TBE];
#include "Std\HPBarc.c"

ovlcod()
{
  int16 k,len_,curs=1,z,key;
  char choice,txt_[51];

  initload();
  FOREVER{
		redo:;
    scrget(2,97);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0261A");
    scrfld(z++,25,1);
    for(k=0;k<3;k++){
      len_=copy0(nm_etiket[k],txt_,40);
      if(len_<40) copy0(" .......................................",&txt_[len_],40-len_);
      scrifld(z++,fm_os40,txt_);
    }
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101 || key==111) break;
    switch(choice){
      case '1': mode=ETIK;lijst();break;
      case '2': mode=RAYON;lijst();break;
      case '3': mode=AFFICHE;lijst();break;
      case '+': upd_offset();break;
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}

#include "paretik.c"

static lijst()
{
  int16 curs=1,key,z,k,curspos_;
  char choice='I',txt_[66];

  if(dt_exec==0) dt_exec=*u(25,2);
#if PRT_ROLENA4  // deze staat in de paretik van de klant
	if(soort_ray!='J') soort_ray='N';
#endif
  if(only_promo=='\0' || fldlen(93,1)==0) only_promo='N';
  zero(type_prx,sizeof type_prx);skip_aant=0;
  etikmode='V';etikaant=1; p_fls_bak='B';
  if(mode==ETIK && (sys4368 & 0x02)==0) p_fls_bak='F';/* bij 2 zijn het rayons */
  if((sys4368 & 0x01) && mode==RAYON) p_fls_bak='F';
  if(fldlen(6,31)==0) p_fls_bak='B';/* voo systeem zonder fles */
  fasinit(1);if(inq_lev){*u(1,1)=inq_lev;fasgeti(1);}
	sysget(3896,6,&sys3896[0]);
#if FLAGDU4
	if(DisplayWarning("De prijzen van Drinkcenter St-Niklaas nemen?",605,1)==YES){
   	sysget(19380+54,6,&sys3896[0]); // rayonkaartjes A4 met prijzen van kassa 10
		if(sys3896[0]=='\0') sysget(3896,6,&sys3896[0]);
	}
#endif
  type_prx[0]=sys3896[0];
  for(k=0;k<6;k++){
    if(sys3896[k]){
      if(type_prx[0]=='\0') type_prx[0]=sys3896[k];
      type_prx[1]=sys3896[k];
    }
  }
	
  FOREVER{
redo:
#if FLAGCOC
		scrget(2,596);
#else
    scrget(2,96);
#endif		
		z=1;
		scraddpicto(1,0,76,23,4,2,583,0,0,"PDF");
#if FLAGCOC
		  scraddf(60,18,3,0); scrifld(60,fm_os38,"Prijs afdrukken (J/N) ...... : ");
      scraddf(61,18,34,2); scrifld(61,fm_uJN,&p_et_prijs);
			scraddf(62,19,3,0); scrifld(62,fm_os38,"Rayonkaartje drukken (J/N) . : ");
      scraddf(63,19,34,2); scrifld(63,fm_uJN,&p_et_ray);
#endif
#if FLAGPED
    if(mode==AFFICHE){
      scraddf(50,21,2,0); scrifld(50,VarTextFmt(62,0),"Affiche liggend of staand drukken (L/S) ................... : ");
      scraddf(51,21,64,2); scrifld(51,fm_u_LS,&AfficheSoortAfdruk);
    }
#endif
#if PRT_ROLENA4  // deze staat in de paretik van de klant
    if(mode==ETIK || mode==RAYON){
			zero(txt_,sizeof txt_);
			if(nm_etiket[3][0]){
				copy0("........................................................... : ",txt_,65);
				copy0("Afdrukken op .............................................. : ",txt_,65);
				k=copy0(nm_etiket[3],&txt_[13],40); txt_[13+k]=' ';
#if FLAGSAS // 4-de soort 
				if(mode==ETIK) copy0("Afdrukken op Artikel-etiketten (65/blad) .................. : ",txt_,65);
#endif
#if FLAGDU4 // 4-de soort 
				if(mode==ETIK) copy0("Afdrukken op Rayon-kaartjes (33/blad) ..................... : ",txt_,65);
#endif
			}
			else copy0("Kaartjes op A4-blad (16/blad) afdrukken ................... : ",txt_,65);
	    scraddf(50,21,2,0); scrifld(50,VarTextFmt(62,0),txt_);
      scraddf(51,21,64,2); scrifld(51,fm_uJN,&soort_ray);
    }
#else
    if(mode==RAYON && sys4404){
      scraddf(50,21,2,0); scrifld(50,fm_os38,"Selectie soort kaartje (1/2) : ");
      scraddf(51,21,33,2); scrifld(51,fm_uu1,&soort_ray);
    }
#endif
    scrifld(z++,fm_os30,nm_etiket[mode]);
    scrfld(z++,25,1);
    scrifld(z++,fm_ANIP,&choice);
    if(fldlen(93,1)) scrifld(z++,fm_uJN,&only_promo); else streepje(z++);
    scrifld(z++,fm_u_FSV,&etikmode);
    scrifld(z++,fm_uu5,&etikaant);
    scrifld(-z,fm_u_09,&type_prx[0]);z++;
    k=type_prx[0]-'0'; if(k<0 || k>9) k=0;
    scrifld(z++,fm_os6,&vptekst[k*10]);
#if FLAGCOC
//		scrifld(z++,fm_uJN,&p_et_prijs);
//		scrifld(z++,fm_uJN,&p_et_ray);
#else
    scrifld(-z,fm_u_09,&type_prx[1]);z++;
    k=type_prx[1]-'0'; if(k<0 || k>9) k=0;
    scrifld(z++,fm_os6,&vptekst[k*10]);
    scrifld(z++,fm_udat,&dt_exec);
    if(fldlen(6,31)) scrifld(z++,fm_u_FB,&p_fls_bak); else streepje(z++);
#endif
    key=scrupd(curs,0x0481);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		prt2pdf=NO; if(key==5001){prt2pdf=YES;key=108;}
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(key==18){curs=curspos_+1; goto redo;}
    if(etikmode=='F' && fldlen(6,72)!=2) goto redo;
    if(key==108){
      if(etikaant<1) etikaant=1;
      switch(choice){
#if FLAGCOC
				case 'N' : key=11;break; // volgens code leverancier
#else
				case 'N' : key=1;break;
#endif
				case 'A' : key=2;break;
				case 'P' : key=6;break;
				default : key=0;break;
      }
      drv_lev=0;drv_grp=0;
      if(key==90){
				if(inq_lev) drv_lev=inq_lev;
      }
      else if(key==91){
				if(grp_beg) drv_grp=grp_beg;
				else drv_grp=1;
      }
      etiketten(key);
      break;
    }
  }
  endsr:;
}

static etiketten(fkey)
int16 fkey;
{
  int16 k,mode_,LastTotEtik;
	uint16 arec_;
 
  seldata.selp_use=NO;
  if(fkey){
    if(ovlcall(2215,2)) goto endsr;
    scrget(1,6);scrupd(-3,0);
  }
  prx_nr=type_prx[0]-'0';
  if(prx_nr<0 || prx_nr>9 || fldlen(6,PrNrs[prx_nr])==0) prx_nr=0;
  fls_nr=type_prx[1]-'0';
  if(fls_nr<0 || fls_nr>9 || fldlen(6,PrNrs[fls_nr])==0) fls_nr=0;

  fasinit(6);
  for(k=0;k<DIM_TBE;k++){
		zero((char *)&tbe[k].aantal,sizeof tbe[0]);
		tbe[k].p_fls_bak=p_fls_bak;
	}
  tot_etik=0; LastTotEtik=-1;
  if(fkey==0){
    FOREVER{
			if(mode==AFFICHE && (sys4368 & 0x04)==0) {if(ask_aff()) break;}
      else if(ask_art())break;
      if(tot_etik>=16 && LastTotEtik!=tot_etik) print_era(0);
      else print_era(1);
			LastTotEtik=tot_etik;
    }
  }
  else{
    mode_=1;arec_=*u(6,1);
    FOREVER{
			if(arec_) {fasinit(6);*u(6,1)=arec_;fasgeti(6);}
      if(faskeyi(6,fkey,mode_)) break;mode_=2;
			arec_=*u(6,1);
      if(accept(mode)){
				if(DirCall_DRK2215_SelectArtikel()){
					add_etik();
					if(mode==AFFICHE  && (sys4368 & 0x04)==0){
						if(ask_aff()){tot_etik=0; break;}
						print_era(1);
						tot_etik=0;
						fasinit(6);*u(6,1)=arec_;fasgeti(6);
					}
				}
      }
    }
    print_era(1);
  }
  endsr:;
}
 
static ask_art()
{
  int16 curs,j,key,k,start_=0,z,q_per_lijn_,curspos_,artikelgezocht_,z_base_;
  flag sr_nm;
  char *pdum,dumm_[10];
  pdum=&dumm_[0];
 
	q_per_lijn_=6;
#if FLAGCOC
	q_per_lijn_=6;
#endif
#if FLAGGDN
	q_per_lijn_=4;
#endif
  curs=4;
  FOREVER{
    redo:
    k=95; if((sys4368 & 0x08)) k=307;/* scrget(2,95); voor scr-controle */
#if FLAGCOC || FLAGJAC || FLAGJRN || FLAGGDN || FLAGALB
		k=595;
#endif
    scrget(2,k);z=1;
		scraddpicto(1,0,76,22,4,2,127,0,4,"Voeg artikels toe");
		scraddfield(300,0,0,0xAA);	scrifld(300,fm_os59,"|^6B"); // barcode allowed
#if PRT_ROLENA4  // deze staat in de paretik van de klant
		if(soort_ray=='J'){
#if FLAGDU4
      if(mode==ETIK) scrifld(z++,fm_os30,"Rayon-kaartjes (33/blad)");
			else
#endif
				scrifld(z++,fm_os30,nm_etiket[3]);
		}
    else scrifld(z++,fm_os30,nm_etiket[mode]);
#else
		scrifld(z++,fm_os30,nm_etiket[mode]);
#endif
    scrifld(z++,fm_ou3,&tot_etik);
    scrifld(z++,fm_uu3,&skip_aant);
		z_base_=z;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      scrifld(z++,fm_uu3,&tbe[j].aantal);
#if !FLAGCOC && !FLAGGDN
			scrifld(z++,fm_u_FB,&tbe[j].p_fls_bak);
#endif
#if !FLAGGDN
      fieldspc(6,2,&pdum,fmt); scrifld(z++,fmt,tbe[j].code);
#endif
      fieldspc(6,3,&pdum,fmt); scrifld(z++,fmt,tbe[j].omschr);
#if FLAGCOC
			scrifld(z++,fm_uf6_2,&tbe[j].vp_prx);
			scrifld(z++,fm_uJN,&tbe[j].prt_ray);
      scrifld(z++,fm_uJN,&tbe[j].prt_prijs);
#else
#if !FLAGJAC
			if(!(sys4368 & 0x08)) scraddpicto(10+j-start_,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
#endif
      scrifld(z++,fm_us20,tbe[j].opm);
      // if(mode==ETIK && (sys4368 & 0x02)==0 && p_fls_bak=='F') scrifld(z++,fm_uf6_2,&tbe[j].vp_fles);
      scrifld(z++,fm_uf5_2,&tbe[j].vp_prx);
#endif
	  }
    key=scrupd(curs,0x03FF);curs=4;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106){
			tot_etik=0;for(k=0;k<DIM_TBE;k++) tot_etik+=tbe[k].aantal;
			if(tot_etik==0 || DisplayWarning("Wenst U echt de geselecteerde artikels NIET af te drukken?",605,1)) return YES;
		}
    if(key==105 && curspos_>=z_base_){
      j=(curspos_-3)/q_per_lijn_;j+=start_;
      for(k=DIM_TBE-2;k>=j;k--){
				copy((char *)&tbe[k].aantal,(char *)&tbe[k+1].aantal,sizeof tbe[0]);
      }
      zero((char *)&tbe[j].aantal,sizeof tbe[0]);tbe[j].p_fls_bak=p_fls_bak;
			curs=curspos_; goto redo;
    }
    if(key==104 && curspos_>=z_base_){
      j=(curspos_-3)/q_per_lijn_;j+=start_;
      for(k=j;k<DIM_TBE-1;k++){
				copy((char *)&tbe[k+1].aantal,(char *)&tbe[k].aantal,sizeof tbe[0]);
      }
      zero((char *)&tbe[DIM_TBE-1].aantal,sizeof tbe[0]);
			curs=curspos_; goto redo;
    }
		artikelgezocht_=NO;
		if(key>=5010 && key<5010+D_LIN_SCR){
			k=key-5010+start_;
			fasinit(6);sr_nm=NO;
#if FLAGGDN // geen code-display
			copy(tbe[k].omschr,s(6,3),len6_3);sr_nm=YES;
#else
			if(len6_2 && tbe[k].code[0]) {*s(6,3)='.';copy(tbe[k].code,s(6,3)+1,len6_2);}
			else {copy(tbe[k].omschr,s(6,3),len6_3);sr_nm=YES;}
#endif
			if(search(6,98)){curs=7+(k-start_)*q_per_lijn_;goto redo;}
			fill_tbe(k,sr_nm); tbe[k].recnr=*u(6,1);artikelgezocht_=YES;
		}

    for(k=start_;k<(start_+D_LIN_SCR);k++){
			if(tbe[k].p_fls_bak=='\0') tbe[k].p_fls_bak=p_fls_bak;
      if((tbe[k].code[0] || tbe[k].omschr[0]) && tbe[k].hash!=hash(k)){
				fasinit(6);
				sr_nm=NO;
#if FLAGGDN // geen code-display
			  copy(tbe[k].omschr,s(6,3),len6_3);sr_nm=YES;
#else
				if(len6_2 && tbe[k].code[0]) {*s(6,3)='.';copy(tbe[k].code,s(6,3)+1,len6_2);}
				else {copy(tbe[k].omschr,s(6,3),len6_3);sr_nm=YES;}
#endif
				if(search(6,0)){curs=6+(k-start_)*q_per_lijn_;goto redo;}
				fill_tbe(k,sr_nm); tbe[k].recnr=*u(6,1);artikelgezocht_=YES;
      }
      else if(tbe[k].aantal && tbe[k].omschr[0]=='\0'){
#if FLAGGDN // geen code-display
				errnum=38;curs=5+(k-start_)*q_per_lijn_;
#else
				errnum=38;curs=6+(k-start_)*q_per_lijn_;
#endif
				goto redo;
      }
      if(tbe[k].p_fls_bak=='F'){// bakprijs in flesprijs zetten 
        tbe[k].vp_fles=tbe[k].vp_prx;
      }
    }
    tot_etik=0;for(k=0;k<DIM_TBE;k++) tot_etik+=tbe[k].aantal;
    if(key==101 && tot_etik==0) return YES;

		if(key==108 && artikelgezocht_==NO)break; // alleen als er niet op artikel is gezocht owv foute F8
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
		if(key==5001) DisplayExtraFuncties(); //load_art(0);
		if(key==110) get_isel();
		if(key==109) load_art(1); // artikels in promo
    if(start_>(DIM_TBE-D_LIN_SCR)) start_=DIM_TBE-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){if(tbe[k+start_].aantal==0) {j=k;break;}}
    if(k<D_LIN_SCR) curs=4+k*q_per_lijn_; else curs=z_base_;
  }
	for(k=0;k<DIM_TBE;k++) if(tbe[k].recnr) break;
  if(k<DIM_TBE) dmp_isel();
  return NO;
}

static DisplayExtraFuncties()
{
	int z,k,key,vt_,hz_;

	FOREVER{
		scrget(1,170);z=1;
		DisplayMenuTitel(4,"Laad geselecteerde artikels",0xA);
//		scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0240A");
		z=25;hz_=10;vt_=6;
		AddTextKey(z++,hz_,vt_,60,2,10001,"Artikels in promotie op kassa",0xFF);vt_+=2;
		AddTextKey(z++,hz_,vt_,60,2,10002,"Artikels met selectie",0xFF);vt_+=2;
		if(fldlen(6,72)==2) {AddTextKey(z++,hz_,vt_,60,2,10005,"Artikels met recente prijswijziging",0xFF);vt_+=2;}
		AddTextKey(z++,hz_,vt_,60,2,10003,"Artikels van laatste ingave",0x00FF);vt_+=2;
		if(ovltest(297)){AddTextKey(z++,hz_,vt_,60,2,10004,"Artikels van PDA (barcode)",0xFF);vt_+=2;}
		scraddf(20,23,1,8); scrifld(20,VarTextFmt(9,0)," F1 stop ");  // functietoetsen 
		key=scrupd(-1,0x7FF);
		if((key/0x10000)>0) key/=0x10000;
		switch(key){
		  case 101 : return 0; break;
			case 10001 : load_art(1); return 1; break;
			case 10002 : load_art(0); return 1; break;
			case 10003 : get_isel(); return 1; break;
			case 10004 : LoadArtikelsFromPda(); return 1; break;
			case 10005 : LoadArtikelsFromAantalEtiketten(); return 1; break;
			default : break;
		}
  }
}

static LoadArtikelsFromAantalEtiketten()
{
  int16 nr_=0,loaded_=0;

	if(fldlen(6,72)!=2) goto endsr;
  fasinit(6);
	FOREVER{
		if(faskeyi(6,2,2)) break;
		if(*i(6,72)) {
      for(nr_;nr_<DIM_TBE;nr_++) {
        if(tbe[nr_].omschr[0]=='\0') break;
      }
      if(nr_>=DIM_TBE){errnum=11; break;}
  		tbe[nr_].aantal=*i(6,72);fill_tbe(nr_,YES);
			get_prx(nr_,YES); // meest recente prijs nemen 
			loaded_++;
			*i(6,72)=0;fasupd(6);
		}
  }
  endsr:;
  return loaded_;
}




static LoadArtikelsFromPda()
{
  int16 key,k,len_,mode_,loaded_=0,do_sel_lev_=NO,nr_;
  uint16 dt_;


  if(dat_end==0) dat_end=*u(25,2);
//  if(dat_beg==0) dat_beg=dat_end;

  FOREVER{
    scrget(2,273);
//    scrofld(1,1,3,-1);
    scrifld(2,fm_udat,&dat_beg); scrifld(3,fm_udat,&dat_end);
    scrifld(4,fm_uu2,&pda_nr);
    key=scrupd(1,0x181);
//    do_sel_lev_=YES;
    if(key==101) return 0;
    if(key==109) do_sel_lev_=NO;
    if(key==108 || key==109) break;
  }
  load_BS:;
  mk_pdaname(4410,"moblogIN.dat");
  fasclos(-2);if(fasopen(filnam,1)!=0) return NO;

  scrget(1,7);scrupd(-3,0);
  fasinit(80);mode_=0;loaded_=0;
  nr_=0;
  FOREVER{
    next:;
    if(read_rec(mode_)) break; mode_=1;
 //   if(get_num(2)==0) goto next;/* geen aantal */
    len_=ele_len(2); if(len_>fldlen(6,2)) len_=fldlen(6,2);
    if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;/* begin eruit */

    len_=ele_len(2); if(len_>fldlen(6,2)) len_=fldlen(6,2);
    if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;// begin eruit 
    fasinit(6);copy(rec_ele(2),s(6,2),len_);
    if(sys4408){
      *pu_6_1=val(s(6,2));
      if(*pu_6_1) fasgeti(6);
    }
    else faskeyi(6,1,0);
    if(do_sel_lev_){
      if(*u(6,7)!=*u(1,1)){
				if(fldlen(11,0)){
					*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);
					if(faskeyi(11,1,1)) goto next;
					if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) goto next;
				}
				else goto next;
      }
    }
    dt_=get_date(0);
    if(dat_beg && dt_<dat_beg) goto next;
    if(dat_end && dt_>dat_end) goto next;
    for(nr_;nr_<DIM_TBE;nr_++) {
      if(tbe[nr_].omschr[0]=='\0') break;
    }
    if(nr_>=DIM_TBE){errnum=11; break;}
		tbe[nr_].aantal=1;fill_tbe(nr_,YES);
  }
  endsr:;
  fasclos(-2);
  return loaded_;
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

static float get_num(nr)                           /* read number starting at pos  */
int16 nr;
{
  int16 j=0,k=0,n;
  float val_=0,val1_;
  flag na_komma=NO,neg_get=NO;
  char *pos;
									
  if(ele_len(nr)==0) return (float) val_; // leeg
	pos=rec_ele(nr); 
  FOREVER{
    if(*(pos+k)=='|' || *(pos+k)==0x0D || *(pos+k)=='\0') break;
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

static uint16 get_date(nr)              /* read date DD/MM/JJJJ starting at pos  */
int16 nr;
{
  int16 k=0,getal_[3],p_getal_;
  uint16 dt_=0;
  char *pos;
									
  zero(getal_,sizeof getal_);p_getal_=0;
  dt_=0; pos=rec_ele(nr); if(ele_len(nr)==0) goto endsr;
  FOREVER{
    if(*(pos+k)=='|' || *(pos+k)==0x0D  || *(pos+k)=='\0') break;
    if(*(pos+k)=='/'){p_getal_++;if(p_getal_>2) break;}
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
	getal_[p_getal_]=getal_[p_getal_]*10 + (*(pos+k)-'0');
      }
    }
    k++;
  }
  getal_[2]%=100;
  if(getal_[0]>=1 && getal_[0]<=31 && getal_[1]>=1 && getal_[1]<=12 && getal_[2]>=0 && getal_[2]<=99) dt_=datejd(getal_[2],getal_[1],getal_[0]);
  endsr:;
  return (uint16) dt_;
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

static load_art(sel_mode_) // 0: algemene artikelselectie, 1: artikels in promotie
{
  int16 mode_,nr_,fkey;
 
	if(sel_mode_==0){
		seldata.prx_klt=0;
		seldata.selp_use=NO;
		if(ovlcall(2215,2)) goto endsr;
	}
  scrget(1,7);scrupd(-3,0);
  fasinit(6);mode_=1;nr_=0; fkey=2;
  FOREVER{
    redo:;
    if(faskeyi(6,fkey,mode_)) break; mode_=2;
		if(sel_mode_==0){
	    if(DirCall_DRK2215_SelectArtikel()==NO) goto redo;
		}
		else{
			if(get_promo(1,*u(6,1),0,0)) goto redo;
		}
    for(nr_;nr_<DIM_TBE;nr_++) {
      if(tbe[nr_].omschr[0]=='\0') break;
    }
    if(nr_>=DIM_TBE){errnum=11; break;}
		tbe[nr_].aantal=1;fill_tbe(nr_,YES);
  }
  endsr:;
}


static get_isel()
{
  int16 k,ele_size_;
  char selname_[15],sr_nm;
									
	ele_size_=sizeof (tbe[0]);
  
  zero(selname_,sizeof selname_);copy("SEL261x.jam",selname_,12);
  selname_[6]='0'+mode;
  fasclos(-2);fasinit(80);
  if(fasopen(selname_,1)==0){
		for(k=0;k<DIM_TBE;k++){
			fasinit(80);*l(80,1)=k*ele_size_;
			if(fasseqi(80,1,ele_size_+4)) break;
			copy(s(80,1)+4,(char *)&tbe[k].aantal,ele_size_);
			if(tbe[k].omschr[0]){
				fasinit(6);
				sr_nm=NO;
				if(len6_2 && tbe[k].code[0]) {*s(6,3)='.';copy(tbe[k].code,s(6,3)+1,len6_2);}
				else {copy(tbe[k].omschr,s(6,3),len6_3);sr_nm=YES;}
				if(search(6,0)) tbe[k].hash=0;
				else {fill_tbe(k,sr_nm); tbe[k].recnr=*u(6,1);}
			}
		}
    fasclos(-2);
  } else errnum=1;
}

static dmp_isel()
{
  int16 k,ele_size_;
  char selname_[15];
									
	ele_size_=sizeof (tbe[0]);
  zero(selname_,sizeof selname_);copy("SEL261x.jam",selname_,12);
  selname_[6]='0'+mode;
  fasclos(-2);fasinit(80);
  if(fasopen(selname_,2)==0){
		for(k=0;k<DIM_TBE;k++){
			if(tbe[k].recnr){
				copy((char *)&tbe[k].aantal,s(80,1)+4,ele_size_); fasseqo(80,2,ele_size_+4);
			}
		}
    fasclos(-2);
  }
  else errnum=1;
}


static ask_aff()
{
  int16 k,curs,key,z;
  flag sr_nm;
  char *pdum,dumm_[10];
  pdum=&dumm_[0];
					
  curs=1;
  FOREVER{
    redo:
    scrget(2,98);z=1;
    fieldspc(6,3,&pdum,fmt);
    scrifld(z++,fmt,tbe[0].omschr);
    scrifld(z++,fm_us13,tbe[0].aff_hdr);
#if FLAGCOC
		copy(fm_us20,fmt,sizeof fm_us20);
#else
    fieldspc(6,73,&pdum,fmt);
#endif
    scrifld(z++,fmt,tbe[0].opm);
    scrifld(z++,fm_us15,tbe[0].promo_txt);
    scrifld(z++,fm_uf6_2,&tbe[0].vp_prx);
    scrifld(z++,fm_uf6_2,&tbe[0].vp_fles);
    scrifld(z++,fm_uf6_2,&tbe[0].lg_bak);
    scrifld(z++,fm_uf6_2,&tbe[0].lg_fles);
    key=scrupd(curs,0xE1);curs=1;
    if(key==101) return YES;
    if(key==106){
      for(k=0;k<DIM_TBE;k++) zero((char *)&tbe[k].aantal,sizeof tbe[0]);
      tot_etik=0;
break;
    }
    if((tbe[0].code[0] || tbe[0].omschr[0]) && tbe[0].hash!=hash(0)){
      fasinit(6);
      copy(tbe[0].omschr,s(6,3),len6_3);sr_nm=YES;
      if(search(6,0)){curs=1;goto redo;}
      fill_tbe(0,sr_nm);
      key=107;
    }
    else if(tbe[0].omschr[0]=='\0'){
      errnum=38;curs=1;
      goto redo;
    }
    tbe[0].aantal=etikaant; tot_etik=etikaant;
    if(key==108)break;
  }
  return NO;
}

static add_etik()
{
  int16 k,pmode_=0;
					
  if(etikmode=='F'){
		if(fldlen(6,72)==2) etikaant=*u(6,72); else etikaant=0;
	}
  if(etikmode=='S') etikaant=*f(6,33);
  redo_add:;
  for(k=0;k<DIM_TBE;k++){
    if(tbe[k].aantal==0){
      zero((char *)&tbe[k].aantal,sizeof tbe[0]);
      tbe[k].aantal=etikaant;
      fill_tbe(k,YES);
      break;
    }
  }
  if(k>=DIM_TBE){print_era(pmode_); pmode_=1; goto redo_add;}
  if(k<DIM_TBE) tot_etik+=etikaant;
  if(tot_etik>=75 || k>=DIM_TBE) print_era(0);
  if(etikmode=='F' && fldlen(6,72)==2){
    fasgetu(6);*u(6,72)=0;fasupd(6);
    fasflush(0);
  }
  endsr:;
}


static fill_tbe(n,sr_nm)
int16 n,sr_nm;
{
  int16 p_code_,pos_,end_,j,k;
  char *p_omschr_;

  
	if(fldlen(6,72)==1 && (*s(6,72)=='B' || *s(6,72)=='F') && *u(6,1)!=tbe[n].recnr) tbe[n].p_fls_bak=*s(6,72);
	if(tbe[n].p_fls_bak=='\0') tbe[n].p_fls_bak=p_fls_bak;
	p_code_=71; if(tbe[n].p_fls_bak=='B') p_code_=70;
#if FLAGCOC 
	p_code_=2;
#endif
  p_omschr_=ps_6_3;
  if(fldlen(6,5) && fldlen(2,24)==0 && *s(6,5)) p_omschr_=s(6,5);/* aparte omschr */
  copy(s(6,2),tbe[n].code,len6_2);
  if(sr_nm || tbe[n].omschr[0]=='\0'){
    copy(p_omschr_,tbe[n].omschr,len6_3);
  }
  copy(s(6,p_code_),tbe[n].eancode,fldlen(6,p_code_));
#if !FLAGCOC
  if(tbe[n].opm[0]=='\0') copy(s(6,73),tbe[n].opm,fldlen(6,73));
#endif
  get_prx(n,NO);
  get_leegg(n);
  tbe[n].lg_bak=lg_bak;tbe[n].lg_fles=lg_fles;
#if FLAGCOC
	if(tbe[n].prt_prijs=='\0') tbe[n].prt_prijs=p_et_prijs;
  if(tbe[n].prt_ray=='\0') tbe[n].prt_ray=p_et_ray;
#endif
  if(mode==AFFICHE && !(sys4368 & 0x04)){
#if FLAGVHY
    zero(tbe[n].opm,sizeof tbe[n].opm);
#endif
    pos_=0;end_=NO;k=0;
    for(j=0;j<13;j++){
      if(*(p_omschr_+pos_)=='\0') {end_=YES;break;}
      else{
				if(*(p_omschr_+pos_)==' ') k=pos_;
				tbe[n].aff_hdr[j]=*(p_omschr_+pos_);pos_++;
      }
      if(pos_>=len6_3) {end_=YES;break;}
    }
    if(j>=13){/* afkappen op woord */
      if(*(p_omschr_+pos_)==' ' || *(p_omschr_+pos_)=='\0') {k=pos_;pos_++;}
      else{
				if(k){zero(&tbe[n].aff_hdr[k],13-k); pos_=k+1;}
      }
/* resterend op opm zetten */
      if(tbe[n].opm[0]=='\0') copy(p_omschr_+pos_,tbe[n].opm,len6_3-pos_);
    }
  }

  tbe[n].recnr=*u(6,1);
  tbe[n].inhoud=*f(6,37); if(fldlen(6,38)) tbe[n].gewicht=*f(6,38);
  if(tbe[n].p_fls_bak=='F'){/* flesgegevens in bak zetten */
    if(fldlen(6,31) && *f(6,31)) tbe[n].inhoud/=*f(6,31);
    if(fldlen(6,31) && *f(6,31)) tbe[n].gewicht/=*f(6,31);
    tbe[n].vp_prx=tbe[n].vp_fles; // tbe[n].vp_fles=0;
    tbe[n].lg_bak=tbe[n].lg_fles; 
  }
  tbe[n].hash=hash(n);
}

static get_prx(n,most_recent_prx_)
int16 n,most_recent_prx_;
{
  int16 m,pos_,len_;
 
  pos_=0;
  if(fldlen(6,105) && *u(6,105) && (*u(6,105)<=dt_exec || most_recent_prx_)) pos_=10;
	if(*f(6,31)<1) *f(6,31)=1;
  tbe[n].vp_prx=*f(6,PrNrs[prx_nr+pos_]);
  if(!(sys3894 & (1<<prx_nr))) tbe[n].vp_prx*=1.+ *f(6,28)/100.;
  if(tbe[n].vp_prx!=*f(6,PrNrs[prx_nr+pos_])) tbe[n].vp_prx=round(tbe[n].vp_prx);
  if(pos_==10) tbe[n].dt_prijs=*u(6,105); else tbe[n].dt_prijs=*u(6,11);
  if(fldlen(6,31) && (*f(6,31)>1 || tbe[n].p_fls_bak=='F')) tbe[n].vp_fles=*f(6,PrNrs[fls_nr+pos_]);
  if(!(sys3894 & (1<<fls_nr))) tbe[n].vp_fles*=1.+ *f(6,28)/100.;
  if(tbe[n].vp_fles!=*f(6,PrNrs[fls_nr+pos_])) tbe[n].vp_fles=round(tbe[n].vp_fles);

  if(fldlen(93,1)){
    fasinit(93);*u(93,2)=*u(6,1);
    m=get_promo(1,*u(6,1),0,0);/* enkel op artikel */
    if(m==0){
      if(*f(93,11)) tbe[n].vp_prx=*f(93,11);
      if(*f(93,11+max_kprx-1) && fldlen(6,31) && (*f(6,31)>1 || tbe[n].p_fls_bak=='F')) tbe[n].vp_fles=*f(93,11+max_kprx-1);
			tbe[n].dt_prijs=*u(93,7);
			if(mode==AFFICHE){
        len_=sizeof tbe[0].promo_txt; if(len_>fldlen(93,30)) len_=fldlen(93,30);
        if(*s(93,30) && tbe[n].promo_txt[0]=='\0') copy(s(93,30),tbe[n].promo_txt,len_);
			}
			else{
				len_=sizeof tbe[0].opm; if(len_>fldlen(93,30)) len_=fldlen(93,30);
        if(*s(93,30) && tbe[n].opm[0]=='\0') copy(s(93,30),tbe[n].opm,len_);
			}
    }
    endsr:;
  }
#if FLAGTOL // indien deelverpakking, dan is prijs van pak ALTIJD flesprijs X aantal (verkoopt altijd per fles of BAK)
	if(*u(6,102)){
		tbe[n].vp_prx=tbe[n].vp_fles* *f(6,31);
	}
#endif


	if(tbe[n].p_fls_bak=='F') tbe[n].vp_prx=tbe[n].vp_fles;
}
 
static get_promo(keynr_,arec_,lrec_,grp_)
int16 keynr_;
uint16 arec_,lrec_,grp_;
{
  int16 mode_;
						
  fasinit(93);*u(93,2)=arec_;*u(93,3)=lrec_;*u(93,4)=grp_; mode_=1;
  FOREVER{
    if(faskeyi(93,keynr_,mode_)) break; mode_=2;
    if(keynr_==1){
      if(*u(93,2)!=arec_) break;
    }
    else{
      if(*u(93,3)!=lrec_) break;
      if(*u(93,4)!=grp_) break;
    }
    if(dt_exec>=*u(93,7) && (*u(93,8)==0 || dt_exec<=*u(93,8))) return NO;
  }
  return YES;
}

static int16 date2str(str_,date_)
char *str_;
uint16 date_;
{
  int16 dd,mm,jj,len_=0;
 
  if(date_==0) goto endsr;
  jddate(date_,&jj,&mm,&dd);jj%=100;
  stcli_d(&str_[len_],(long)dd,2,0);len_+=2;str_[len_++]='/';
  stcli_d(&str_[len_],(long)mm,2,0);len_+=2;str_[len_++]='/';
  stcli_d(&str_[len_],(long)jj,2,0);len_+=2;
  endsr:;
  return len_;
}

static print_era(pmode_)
int16 pmode_;
{
	int k;

  switch(mode){
    case ETIK    : prt_etik(pmode_); break;
    case RAYON   : prt_rayon(pmode_);break;
    case AFFICHE : prt_affiche(pmode_);break;
    default      : break;
  }
  for(k=0;k<DIM_TBE;k++) if(tbe[k].p_fls_bak=='\0') tbe[k].p_fls_bak=p_fls_bak;
}
 
 
static upd_offset()
{
  int16 k,key,z;
  char txt_[80];

  for(k=0;k<3;k++){
    sysget(3958+k*4,2,&x_offset[k]);
    sysget(3960+k*4,2,&y_offset[k]);
  }
 
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,4,16,2);
  scraddf(z++,6,7,0); scraddf(z++,6,36,2);
  scraddf(z++,7,7,0); scraddf(z++,7,36,2);
  scraddf(z++,10,16,2);
  scraddf(z++,12,7,0); scraddf(z++,12,36,2);
  scraddf(z++,13,7,0); scraddf(z++,13,36,2);
  scraddf(z++,15,16,2);
  scraddf(z++,17,7,0); scraddf(z++,17,36,2);
  scraddf(z++,18,7,0); scraddf(z++,18,36,2);
  scraddf(z++,23,1,8);scraddf(z++,23,11,8);
  FOREVER{
    redo:;
    z=1;
    for(k=0;k<3;k++){
      copy0("Corrigeren positie ",txt_,19);copy0(nm_etiket[k],&txt_[19],30);
      scrifld(z++,fm_os63,txt_);
      scrifld(z++,fm_os63,"Geef de offset horizontaal :");
      scrifld(z++,fm_uu5,&x_offset[k]);
      scrifld(z++,fm_os63,"Geef de offset vertikaal   :");
      scrifld(z++,fm_uu5,&y_offset[k]);
    }
    scrifld(z++,fm_os9," F1 stop");scrifld(z++,fm_os13," F8 neem aan");
    key=scrupd(1,0x81);
    if(key==101) return YES;
    for(k=0;k<3;k++){
      sysput(3958+k*4,2,&x_offset[k]);
      sysput(3960+k*4,2,&y_offset[k]);
    }
    return YES;
  }
  endsr:;
  return NO;
}

static get_leegg(n)
int16 n;
{
  uint16 rec_,nr_;
  float hoev_;
  char buf_[20];
									
  lg_bak=0;lg_fles=0;
  if(*i(6,9)==99) goto endsr;         /* leeggoed in leeggoedkolom optellen */
  rec_=*u(6,1);
	nr_=41;if(tbe[n].p_fls_bak=='F') nr_=44; // etiketmode
  if(fldlen(6,nr_) && *s(6,nr_)){
    hoev_=*f(6,42);
    copy(s(6,nr_),buf_,len6_2);
    fasinit(6);copy(buf_,s(6,2),len6_2);
    if(faskeyi(6,1,0)==0){
      lg_bak=*f(6,PrNrs[prx_nr]);
      lg_bak*=hoev_;
    }
  }
  fasinit(6);*u(6,1)=rec_;fasgeti(6);
  nr_=44;
  if(fldlen(6,44) && *s(6,44)){
    hoev_=*f(6,42);
    copy(s(6,44),buf_,len6_2);
    fasinit(6);copy(buf_,s(6,2),len6_2);
    if(faskeyi(6,1,0)==0){
      lg_fles=*f(6,PrNrs[prx_nr]);
      lg_fles*=hoev_;
    }
  }
  fasinit(6);*u(6,1)=rec_;fasgeti(6);
  endsr:;
}

static cnv_char(ps_,len_)// oude naam owv paretik bij elke klant
char *ps_;
int16 len_;
{
	CnvJamaChar(ps_,len_,0);
}

static uint16 hash(pos_)
int16 pos_;
{
  char *ps;
  int16 k;
  uint16 fuval=0;
				
  k= sizeof tbe[0].code + sizeof tbe[0].omschr;
  ps=tbe[pos_].code;
  while(k--) fuval=fuval*3+*(ps++);
	fuval=fuval*3+tbe[pos_].p_fls_bak;
  return fuval;
}

static eprx2str(ps_,bd_)
char *ps_;
float bd_;
{
  int16 len_;
  long val_,val1_;
									
  val_=bd_*100 +.49; val1_=val_/100;
  val_=val_-val1_*100;
  *(ps_++)=0x80;/* EURO teken */
  len_=7; if(val_) len_=5;
  stcli_d(ps_,val1_,len_,1);
  if(val_){
    *(ps_+len_)=',';
    stcli_d(ps_+len_+1,val_,2,0);
    len_+=3;
  }
  *(ps_+len_)='\0';
  return len_+1;
}

static prx2str(ps_,bd_)
char *ps_;
float bd_;
{
  int16 len_;
  long val_,val1_;
 
  val_=bd_*100 +.49; val1_=val_/100;
  val_=val_-val1_*100;
  len_=7; if(val_ || bd_<9999) len_=4;
  stcli_d(ps_,val1_,len_,1);
  if(YES /* val_ || enot_*/){
    *(ps_+len_)=',';
    stcli_d(ps_+len_+1,val_,2,0);
    len_+=3;
  }
  *(ps_+len_)='\0';
  return len_;
}

static flt2str(ps_,bd_)
char *ps_;
float bd_;
{
  int16 k,len_=0;
  char buff[15];
  double bedrag_,add_=0;
  long val_,value;
							
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*100+add_;value=val_/100;
 
  zero(buff,sizeof buff);
  stcli_d(&buff[0],value,10,1);
  for(k=0;k<10;k++){
    if(buff[k]=='\0') break;
    if(buff[k]!=' ') *(ps_+len_++)=buff[k];
  }
  value=val_-value*100;
  if(value){
    *(ps_+len_++)=',';
    if(value<0) value=-value;
    zero(buff,sizeof buff);
    stcli_d(&buff[0],value,2,0);
    for(k=1;k>=0;k--) if(buff[k]!='0') break;
    copy(&buff[0],ps_+len_,k+1);len_+=k+1;
  }
  return len_;
}
 
static prt_string(string)
char *string;
{
  char *_string;
  int16 len;

  len=0; _string=string;
  while (*_string++) len++;
  prt_bin(string,len);
}

static prt_bin(string,len)
char *string;
int16 len;
{
  char fm[8];
 
  fm[0]=7; fm[1]=0x88; fm[2]=len%256; fm[3]=len/256; fm[4]=0; fm[5]=0; fm[6]=0;
  if (len>0) prtifld(fm,string,-2);
}
 
static sel_orient(or_)
char or_;
{
  char str_[10];

  zero(str_,sizeof str_);str_[0]=0x1B;
  if(or_=='l' || or_=='L'){copy("&l1O",&str_[1],4); prt_string(str_);}
  else if(or_=='p' || or_=='P') {copy("&l0O",&str_[1],4);prt_string(str_);}
}

static p_esign(dikte_,hpos_,vpos_)
int16 dikte_,hpos_,vpos_;
{
  int16 v_,k,h_,len_;
						
  txt(dikte_,hpos_,vpos_,"C","");
  k=dikte_*.8; v_=vpos_-(dikte_-dikte_*0.7);
  h_=hpos_-dikte_*.5;
  txt(k,h_,v_,"=","");
  len_=txt_plen(dikte_,"C ");
  return len_;
}

static txt_plen(dikte_,ps_)
char *ps_;
int16 dikte_;
{
  int16 j;
  char kar_;
  float qpunten_;
									
  j=0; qpunten_=0;
  FOREVER{
    kar_=*(ps_+j++);
    if(kar_=='\0') break;
    if(kar_==' ') qpunten_+=lbreedte[0];
    else if(kar_>='A' && kar_<='Z') qpunten_+=lbreedte[1+(kar_-'A')];
    else if(kar_>='a' && kar_<='z') qpunten_+=lbreedte[27+(kar_-'a')];
    else if(kar_>='0' && kar_<='0') qpunten_+=lbreedte[53+(kar_-'0')];
    else qpunten_+=lbreedte[63];
  }
  qpunten_+=lbreedte[0]*1.5;
  if(dikte_) qpunten_=(qpunten_* ((float)dikte_/90.))+.49;
  j=qpunten_;
  return j;
}

//static cent_txt(dikte_,bpos_,epos_,ps_)
//char *ps_;
//int16 dikte_,bpos_,epos_;
//{
//  int16 j,pos_;
//  char kar_;
//  float qpunten_;
//
//  j=0; qpunten_=0;
//  FOREVER{
//    kar_=*(ps_+j++);
//    if(kar_=='\0') break;
//    if(kar_==' ') qpunten_+=lbreedte[0];
//    else if(kar_>='A' && kar_<='Z') qpunten_+=lbreedte[1+(kar_-'A')];
//    else if(kar_>='a' && kar_<='z') qpunten_+=lbreedte[27+(kar_-'a')];
//    else if(kar_>='0' && kar_<='0') qpunten_+=lbreedte[53+(kar_-'0')];
//    else qpunten_+=lbreedte[63];
//  }
//  if(dikte_) qpunten_=(qpunten_* ((float)dikte_/90.))+.49;
//  pos_=(epos_-bpos_-qpunten_)/2;
//  if(pos_<0) pos_=bpos_; else pos_+=bpos_;
//  return pos_;
//}

static next_drv(fkey,mode_)
int16 fkey,mode_;
{
  if(fkey==90){
    fasinit(1);*u(1,1)=drv_lev; if(drv_lev) fasgeti(1);
    if(faskeyi(1,2,mode_)) return YES;
    drv_lev=*u(1,1);
  }
  else {
    if(mode_==2){
      drv_grp++;
      for(drv_grp;drv_grp<100;drv_grp++) if(grp_used[drv_grp]) break;
    }
    if(drv_grp>99 || (grp_end && drv_grp>grp_end)) return YES;
    fasinit(52);*u(52,1)=drv_grp; if(fasgeti(52)) return YES;
    drv_grp=*u(52,1);
  }
  return NO;
}
 
static cmp_str(p1,p2,len)
char *p1,*p2;
int16 len;
{
  while(len--){
    if(*p1++!=*p2++)return 1;
  }
  return 0;
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

static initload()
{
  int16 k,nr_;
 
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);
  fileopen(11);
  if(fldlen(60,1)) fileopen(14);
  if(fldlen(16,1)) fileopen(13);

  sysget( 294,4,def_munt);
  sysget(1918,2,&sear_stt);
  sysget(3596,2,&sys3596);
  sysget(3614,6,&sys3614[0]);
  sysget(3724,2,&sys3724);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,&sys3896[0]);
  sysget(4368,2,&sys4368);
  sysget(4404,2,&sys4404);
  sysget(4408,2,&sys4408);
  sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  for(k=0;k<3;k++){
    sysget(3958+k*4,2,&x_offset[k]);
    sysget(3960+k*4,2,&y_offset[k]);
  }

  if(fldlen(6,130) && fldlen(25,8) && *u(25,8)) prx_loff=*u(25,8);
  else prx_loff=0;
  len6_2=fldlen(6,2);if(len6_2>15) len6_2=15;
  len6_3=fldlen(6,3);if(len6_3>35) len6_3=35;
  pu_6_1=u(6,1);
  ps_6_3=s(6,3);
  if(len6_2) arcd=YES;
	pl_80_1=l(80,1); p_data=s(80,1)+4;

  max_kprx=0;
  for(k=0;k<6;k++){
    if(sys3896[k]){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])) max_kprx++;
    }
  }
/* specifieke omschrijvingen invullen */
  zero(nm_etiket, sizeof nm_etiket);
  for(k=0;k<3;k++) copy0(defname[k],nm_etiket[k],20);
  tot_etik=0;prt_etik(0);prt_rayon(0); prt_affiche(0);
  if(faskeyi(6,6,0)==45){                /* controle op key plaats magazijn */
    for(k=0;k<sizeof fm_ANIP;k++) if(fm_ANIP[k]=='P') fm_ANIP[k]='A';
  }
  zero(&seldata.data_begin,sizeof seldata); seldata.dt_s_beg=*u(25,2)-730;
}

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

static float *prf(stu_,ele_)
int16 stu_,ele_;
{
  float *pf_;
						
  pf_=(float *)(s(stu_,ele_));
  if(prx_loff && stu_==6 && (ele_>=21 && ele_<=26)){
    pf_=(float *)(s(stu_,ele_)+prx_loff);
  }
  return pf_;
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

static accept(mode)
int16 mode;
{

  if(only_promo=='J'){
    if(get_promo(1,*u(6,1),0,0)) return NO;
  }
  return YES;
}

static nextline()
{
  free=prtline();
}

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
}

static float round(fl_)
float fl_;
{
  float add, *pf;

  pf=(float *)sys3614;
  add=*pf;
  if(sys3614[2]==0) add/=2.;
  add=add*.999999;
  if(*pf>0.0001){
    fl_=((long)((fl_+add)/(*pf))) * *pf;
  }
  return (float)fl_;
}

static zeros(pd,len)
char *pd;
int16 len;
{
  int16 k;
				
  for(k=0;k<len;k++) *(pd+k)='\0';
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
  parmcall[7]=0x0C;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}

