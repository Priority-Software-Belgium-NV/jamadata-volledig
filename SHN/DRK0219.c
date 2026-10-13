/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0219GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0219dat
#define ovlcod DRK0219cod
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

char ovldat[] = "drk0219  00:16 05/11/10 (c) Jamadata";
// FLAGCRA : indien T-menu, dan allerlei keuzes blokkeren
// FLAGGOU : vertegenwoordiger+koopwarengroep+ aparte afronding via 52,28
// FLAGDU3 : stock is geblokkeerd, met F4 kunt ge hem deblokkeren
// FLAGHDY : FostPlus-controle
// FLAGEET : default prijs op bon op N
// FLAGEPD : nieuwe lev/klantcode met 44/41 
// FLAGGRS : default prijs op bon op N
// FLAGOLH : statistiek van artikelfiche met F10
// FLAGMAE : schrappen klanten ook de plaatfiches schrappen 
// FLAGRUB : lijst per vertegenwoordiger
// FLAGSLB : nieuwe lev/klantcode met 9 
// FLAGVHY : nieuw artikel ahv ander : code NIET wissen
// FLAGVLO : nieuwe lev/klantcode met 9 
// FLAGWYN : nieuwe klantcode beginnen met 5
// FLAGDMD : default prijstype 6


/* beheer basisgegevens V.9 */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXFLD          120
#define flag            uint16
#define DIM_LETIK       100
#define D_LIN_SCR       17
#define CALCDEF         "%N%0%0%0%0%0%0%0%0%0"

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

static struct {
  char filname[15];
  int16 filstru;
} files[7];

static char *fichenm[6]={"Leveranciersfiche","Klantenfiche","","","Klantentoer","Artikelfiche"};
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
static uint16 hash(),hashbuf();
extern long *l();
extern long val();
extern float *f();
extern double *d(),valu_cnv();
static double getsaldo();
static double Round();
static char *pMST(int16 stu_, int16 fld_);

static int16 stu,chk_btoeg=0,free,key21;
static int16 lvcd,klcd;
static uint16 def_qfak,inq_grp;
static char nm_20[20],nm_dehr[52],taal_i,talen[4],def_grbex[2],oldnm[50];
static int16 selp_stu=0;
static int16 prt2pdf;
static char selp_bf[4][1000],selp_des[40],*selp_fld,*calctype;
static flag selp_use,selp_ge,selp_le,sys3618;
static float def_btw, btw_pct[8],sys3614;
static long def_grb;
static char vptekst[100],stuksprx[10];

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os59[]  = {7,0x88,59,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_od62_[] = {6,0x95,6,2,0x60,0};
static char fm_uf7_1[] = {6,0xD4,7,1,0x60,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_uf4_1[] = {6,0xD4,4,1,0x60,0};
static char fm_uf3_0[] = {6,0xD4,3,0,0x70,0};
static char fm_of7_1[] = {6,0x94,7,1,0x60,0};
static char fm_of6_2[] = {6,0x94,6,2,0x60,0};
static char fm_of5_0[] = {6,0x94,5,0,0x60,0};
static char fm_of4_3[] = {6,0x94,4,3,0x60,0};
static char fm_of4_0[] = {6,0x94,4,0,0x60,0};
static char fm_of4_1[] = {6,0x94,3,1,0x60,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_btw[]   = {6,0x94,2,1,0x20,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_u_SI[]  = {11,0xC8,1,0,1,0,'S','S','I','I',0};
static char fm_of4_2[] = {6,0x94,4,2,0x70,0};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,0x09,0,'A','A','N','N',0};
static char fm_u_AK[]  = {11,0xC8,1,0,1,0,'A','A','K','K',0};
static char fm_uPB[]   = {11,0xC8,1,0,1,0,'%','%','B','B',0};
static char fm_uNB[]   = {11,0xC8,1,0,1,0,'N','N','B','B',0};
static char fm_u05NB[] = {13,0xC8,1,0,1,0,'0','5','N','N','B','B',0};
static char fm_uAGPN[]   = {15,0xC8,1,0,0x09,0,'A','A','G','G','P','P','N','N',0};

#if FLAGHDY
static struct{ // specifiek
  char code[3];
  char omschr[20];
  double bedrag[3];
  long grb[3];
  char dummy[21];
} fost_stu[20];
#endif


extern int16 ilength;
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi;
static char SelectXlsFldNr[150];
static int16 StylTotaal, StylGrpTot, StylKlasse, StylNormal, StylDate, StylTitel, Styl2Use;
 
static char ram[15000],buf1000[1000];
static int16 dat_len,ram_recl,hash_len,max_line,len6_2,len6_3,len2_120,PwUpdNr=11;
static int16 len2_3,len63_10;
static uint16 hash_val,stat_dat[14];
 
static uint16 tb_etik[DIM_LETIK],tot_etik,x_offset,y_offset;
static int16 hz_dots,vt_dots,lettype,line_dots,q_hor,q_vert;

static char sort_meth;
static char def_munt[4],fmt[40],*ps2_120;
static char prt_info,only_info,type_info,only_memo,prt_memo,MasterArt[1500],skip_blocked,prt_bestbon;
static char nm_loc[10][6],stubuf[2][150];
static uint16 dt_beg,dt_end,lst_recs[10],loc_klt[20];
static flag sear_stt,sys1854,sys2698,only_dsp,chk_intra,BlokVerpakkingDisplay=NO;
static int16 pfld_ext,pnr_kbak,pnr_kstk;
static char sys4521,str4498[23],sys3896[6];
static flag sys3876,sys3586,sys3762,sys3892,sys3894,sys3976,sys3652;
static flag loaded,suppr_wi,rev_prx_calc,BlokkeerStock=NO;
static uint16 dsp_last,auto_nr,fact_klt;
static float net_winst[10],sys2830[10];
static uint16 *pu_6_1,*pu_2_1;
static uint16 chk_dblbtw();
static long TbDiversArtikel[10];
static int16 def_taal;
static char intr_def_land[2];
static int16 intr_def_vervoer,intr_def_transactie;
/* de seqo-variabelen */
							
static char *p_data;
static long *pl_80_1;
									
static char seqo_str[1000],DelimKar=0x09;
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;


#if FLAGRUB
static char inq_vert[10],inq_regio[10],prt_omz='J';/* SPECIFIEK */
#endif

#if FLAGGOU
static struct{
  char code[2];
  char naam[10];
} vertegenw[10];
static char kw_groep[20][15];
#endif


ovlcod(parmval)
int16 parmval;
{
  int16 key;
  char choice;
									
  initload();
	if(parmval==2){execute(2 -1);ovlexit(-1);}
  FOREVER{
    scrget(2,3);fasunlck(0);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
    if(key==101||key==111) ovlexit(-1);
#if FLAGCRA
		if(*u(25,4)==110){
			if(choice>'3') choice='\0';
			suppr_wi=YES; sys3892=7;
		}
#endif
    switch(choice){
      case '1': execute(1 -1);break;
      case '2': execute(2 -1);break;
      case '3': execute(6 -1);break;
      case '4': if(ovltest(2194) && CheckPw(1,12,0)) ovlexit(2194);/* execgr() */
		else errnum=12;
		break;
      case '5': if(ovltest(230)) ovlexit(230);
		else errnum=12;
		break;
      case '7': if(fldlen(63,1)) {stu=63;execute(4);}
		else errnum=12;
		break;
      case '8': if(ovltest(233)) ovlexit(233);
		else errnum=12;
		break;
  //    case '9': if(ovltest(260)) ovlexit(260);
		//else errnum=12;
		//break;
      default : errnum=34;break;
    }
  }
  ovlexit(-1);
}

static execute(nr)
int16 nr;
{
  int16 key,nr_;
  char choice;

  if(nr==4) nr_=1; else nr_=nr;
  if(files[nr_].filname[0]=='\0') goto endsr;
  if(errnum=fasopen(files[nr_].filname,0)) goto endsr;
  if(nr!=4) stu=files[nr].filstru;
  if(stu==6)if(errnum=fasopen(files[0].filname,0)) goto endsr;
  if(stu==1 || stu==6) {lvcd=1; if(faskeyi(1,1,0)==45) lvcd=0;}
  if(stu==2 || stu==63){
    klcd=1; if(faskeyi(2,1,0)==45) klcd=0;
    if(len2_120 || fldlen(2,26))if(errnum=fasopen(files[5].filname,0)) goto endsr;
  }
  key21=21;if(faskeyi(stu,key21,0)==45) key21=2;
  copy(fichenm[nr],nm_20,20);
	PwUpdNr=11; if(stu==6) PwUpdNr=12;
  FOREVER{
    if(stu<3 || stu==63) scrget(1,50); else scrget(2,50);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_menu,&choice);
    key=scrupd(3,0x0401);
    if(key==101) break;
    if(key==111) ovlexit(-1);
		BlokVerpakkingDisplay=NO;
#if FLAGCRA
		if(*u(25,4)==110 && ((stu!=2 && choice=='2') || choice>'2')) choice='\0';
#endif
    switch(choice){
      case '1': upd();break;
      case '2': if(CheckPw(1,PwUpdNr,0)) add(NO);break;
      case '3': if(CheckPw(1,PwUpdNr,0)) kill();break;
      case '4': if(stu<3) prt_ask(nr); else print(nr,1);break;
      case '5': if(stu>2) print(nr,2);break;
      case '6': ovlcall(2918,stu);break;
			case '7': if(stu==6){if(CheckPw(1,PwUpdNr,0)) add_cop();}
								else if(stu<3) Fiches2Xls(); 
								else errnum=34;
								break;
      case '8': if(stu==6) upd_bulk();
								else errnum=34;
								break;
	    case 'E': if(stu==6 && CheckPw(1,PwUpdNr,0)) Fiches2Xls();
								else errnum=34;
								break;
      case 'L': if(stu==6 && ovltest(229) && CheckPw(1,PwUpdNr,0)) ovlcall(229);
								else if(stu<3) ovlcall(2919,stu);
								else errnum=34;
								break;
      case 'W': if(stu==6 && suppr_wi==YES) suppr_wi=NO;
								else errnum=34;
								break;
      default : errnum=34;break;
    }
  }
  endsr:;
}

static upd()
{
  int16 k,key,smode_,len_f9;
	char werkveld[25],f9_text[40];
	uint16 tb_recs_[1000],p_tb_recs_;

	zero(f9_text,sizeof f9_text);
	len_f9=copy0(" F9 NIEUWE ",f9_text,20);
	k=nm_20[0];if(k>='A' && k<='Z') k+='a'-'A';f9_text[len_f9++]=k;	// hoofdlette wegdoen
	len_f9+=copy0(&nm_20[1],&f9_text[len_f9],19);f9_text[len_f9++]=' ';


	memset(werkveld,0,sizeof werkveld);
  FOREVER{
    if(!errnum){
      fasinit(stu);
    }
		redo:;
    scrnum=0;scrget(1,5);
		if(stu==6 && fldlen(6,70)){ // zoek met barcodescanner ($ ervoor zetten)
  		scraddfield(300,0,0,0xAA);
  		scrifld(300,fm_os59,"^0A$|^6C");
		}
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_os15,modenm[0]);
    scrfld(4,stu,3); scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		scraddf(119,23,24,8); scrifld(119,VarTextFmt(len_f9,0),f9_text);
    if(stu==63){
      scraddf(120,23,59,8); scrifld(120,fm_os20," F10 zoek via klant ");
    }
    key=scrupd(4,0x0781);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
    if(key==111) ovlexit(-1);
		if(key==109) {add(YES); goto redo;}
  	smode_=0;	if(key==5001) smode_=98;
    if(stu==63 && key==110) zoek_toer();
    if(search(stu,smode_)) goto redo;
		zero(tb_recs_,sizeof tb_recs_); p_tb_recs_=0;tb_recs_[p_tb_recs_]=*u(stu,1);
		next_fiche:;
    if(stu==2 && fldlen(62,1)) {
	    fasinit(62);*u(62,2)=*pu_2_1;faskeyi(62,1,0);
    }
    if(stu==6 && fldlen(66,1)) {
	    fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
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
			if(faskeyi(stu,2,2)==0){
				if(p_tb_recs_<999) tb_recs_[++p_tb_recs_]=*u(stu,1);
			} else fasgeti(stu);
			goto next_fiche;
		}
  }
}

static add(single_add_)
int16 single_add_;
{
  int16 len_;
  FOREVER{
    if(single_add_==NO) fasinit(stu);
    if(auto_nr && fldlen(stu,2)){
      fasinfo(stu,1);stcli_d(s(stu,2),(long)(*u(stu,1)+1),4,0);
      *u(stu,1)=0;
    }
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
#if FLAGOLH
     *f(2,80)=5;
#endif
      if(fldlen(2,36)) *u(2,36)=def_qfak;
      // if(fldlen(2,44)>0) *s(2,44)='J';
			if(fldlen(2,74)) copy(intr_def_land,s(2,74),2);
			if(fldlen(2,75)) *u(2,75)=intr_def_vervoer;
			if(fldlen(2,77)) *u(2,77)=intr_def_transactie;
    }
    if(stu==6){
      if(fldlen(66,1)) fasinit(66);
      if(fldlen(6,13)) copy(def_munt,s(6,13),3);
      if(fldlen(6,28)) *f(6,28)=def_btw;
      if(len_=fldlen(6,39)){
				if(len_>2) len_=2;
				copy(def_grbex,s(6,39),len_);
      }
      if(fldlen(6,40)) *l(6,40)=def_grb;
      if(fldlen(6,42)) *f(6,42)=1;
      if(fldlen(6,76)) *s(6,76)='J';
#if FLAGEET
			*s(6,67)='J';  // standaard op laadbon
#endif
#if FLAGSAS
			*s(6,104)='J';  // standaard GEEN korting toegestaan bioj nieuw artikel
#endif
			fasinit(52);
    }
    if(!fichupd(2)) break;
		if(single_add_) break;
  }
}

static add_cop()
{
  int16 key,smode_;
 
  fasinit(stu);
  FOREVER{
    if(dsp_last){
      if(fldlen(stu,2)) copy(s(stu,2),s(stu,3),fldlen(stu,2));
    }
    else if(!errnum){
      fasinit(stu);
    }
    redo:
    scrget(1,5);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_os38,"gedeeltelijk over te nemen");
    scrfld(4,stu,3);scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    key=scrupd(4,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
    if(key==111) ovlexit(-1);
  	smode_=0;	if(key==5001) smode_=98;
	  if(search(stu,smode_))goto redo;
#if FLAGVHY
		zero(s(6,1),s(6,2)-s(6,1));
#else
		zero(s(6,1),s(6,3)-s(6,1));
#endif
		zero(s(6,8),fldlen(6,8));
		zero(s(6,29),fldlen(6,29));
		zero(s(6,33),fldlen(6,33));
		zero(s(6,46),s(6,51)-s(6,46));
		zero(s(6,63),s(6,65)-s(6,63));
		zero(s(6,53),s(6,74)-s(6,53));
		zero(s(6,102),fldlen(6,102));
		zero(s(6,105),s(6,150)-s(6,105));
    if(fldlen(66,1)) fasinit(66);
		if(fldlen(64,1)) fasinit(64);
    if(!fichupd(3)) break;
  }
}

static kill()
{
  int16 key,err_,smode_;

  if(stu<3 && (sys1854 & stu)) {errnum=65;goto endsr;}
  FOREVER{
    if(!errnum) fasinit(stu);
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
	fasinit(62);*u(62,2)=*pu_2_1;faskeyu(62,1,0);
      }
      if(stu==6 && fldlen(66,1)) {
				fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
      }
			if((stu==6 || stu==2) && fldlen(16,1)){
				err_=NO;
				fasinit(16);
				if(stu==2){
					*l(16,10)=*u(stu,1);
				   if(faskeyi(16,2,1)) err_=NO;
					 else if(*l(16,10)==*u(stu,1)) err_=YES;
				}
				else if(stu==6){
					*l(16,20)=*u(stu,1);
				  if(faskeyi(16,1,1)) err_=NO;
					else if(*l(16,20)==*u(stu,1)) err_=YES;
				}
				if(err_){if(DisplayWarning("Deze fiche bevat nog historieken! Toch doorgaan?",61,1)!=YES) {errnum=63;goto redo;}}
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

#if FLAGRUB
	if(stu==2) print(nr,1); goto endsr;
#endif


  if(nr==4) {prt_toer(0);goto endsr;}
  if(nr==5) goto endsr;

  copy(fichenm[nr],nm_20,20);
  sort_meth='A'; prt_memo='N';only_memo='N'; skip_blocked='J';only_memo='N'; prt_bestbon='N';
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
		if(stu==2 && fldlen(2,120)){
			scraddfield(z,3,18,0); scrifld(z++,VarTextFmt(38,0),"Artikels bestelbon afdrukken (J/N) : ");
			scraddfield(z,40,18,2); scrifld(z++,fm_uJN,&prt_bestbon);
		}
    key=scrupd(curs,0x0481);curs=2;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(key==108) break;
  }
  k=1; if(sort_meth=='A') k=2;
 	print(nr,k);
  endsr:;
}

static upd_bulk()
{
  int16 z,curs,k,key,fkey_,mode_;
  char sort_meth='N',lst_code[10],lst_omsch[40];
  uint16 inq_lev=0,inq_art;
	uint16 tb_recs_[2500],p_tb_recs_;
									
  fasinit(6);fasinit(1); inq_grp=0; curs=2;
  FOREVER{
    redo:;
    scrget(2,170);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_uAN,&sort_meth);
    scrfld(z++,stu,3);
    scrfld(z++,1,3);
    scrifld(z++,fm_uu2,&inq_grp);
    key=scrupd(curs,0x0481);curs=2;
    if(key==101) break;
    if(key==111) ovlexit(-1);
    if(*s(6,3)){
      if(search(6,0)) {curs=3;goto redo;}
    }
    else fasinit(6);
    if(*s(1,3)){
      if(search(1,0)) {curs=4;goto redo;}
    }
    else fasinit(1);
    inq_art=*pu_6_1;inq_lev=*u(1,1);
    if(key!=108) goto redo;
		seldata.selp_use=NO;
		if(ovlcall(2215,4)) break;
		fasinit(6);if(inq_art){*u(6,1)=inq_art;fasgeti(6);} // juistzetten na selectie
    mode_=1; fkey_=1; if(sort_meth=='A') fkey_=2;
    copy(s(6,2),lst_code,fldlen(6,2));
    copy(s(6,3),lst_omsch,fldlen(6,3));
    scrget(1,7);scrupd(-3,0);
		fasunlck(-1);
		zero(tb_recs_,sizeof tb_recs_); p_tb_recs_=0;
    FOREVER{
      copy(lst_code,s(6,2),fldlen(6,2));
      copy(lst_omsch,s(6,3),fldlen(6,3));
      next:;
      if(faskeyi(6,fkey_,mode_)) break; mode_=2;
			if(DirCall_DRK2215_SelectArtikel()==NO) goto next;
      if(inq_lev && inq_lev!=*u(6,7)) goto next;
      if(inq_grp && *i(6,9)!=inq_grp) goto next;
			if(p_tb_recs_<2500) tb_recs_[p_tb_recs_++]=*u(stu,1);
      copy(s(6,2),lst_code,fldlen(6,2));
      copy(s(6,3),lst_omsch,fldlen(6,3));
upd_fiche:;
      if(stu==6 && fldlen(66,1)) {
				fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
      }

			k=fichupd(1);
		  if(k==0) break; // stop
		  if(k==10) { // previous 
		  	if((p_tb_recs_-2)>=0){
		 			*u(stu,1)=tb_recs_[--p_tb_recs_-1]; fasgeti(stu);
				}
				goto upd_fiche;
			}
			if(k==11) { // next
				if(tb_recs_[p_tb_recs_]){ // al gepasseerd
		 			*u(stu,1)=tb_recs_[p_tb_recs_++]; fasgeti(stu);
					goto upd_fiche;
				}
			}
      scrget(1,7);scrupd(-3,0);
    }
    fasinit(6);fasinit(1);
  }
}

static print(nr,fkey)
int16 nr,fkey;
{
  int16 form_dat[8],pr_mode,cnt,prtnr,fuval,k,z,q_info_,key;
  uint16 getnr;
  flag cd,prt_fax;
  double bkhsaldo;
 
  if(nr==4) {prt_toer(0);goto endsr;}
  if(nr==5) goto endsr;

#if FLAGRUB
  if(stu==2){/* SPECIFIEK */
    fasinit(2);copy(inq_vert,s(2,28),fldlen(2,28));
    copy(inq_regio,s(2,29),fldlen(2,29));
    FOREVER{
      scrget(2,500);z=1;
      scrifld(z++,fm_uAGPN,&sort_meth);
      scrfld(z++,2,28);
      scrfld(z++,2,29);
      scrifld(z++,fm_uJN,&prt_omz);
      key=scrupd(1,0x81);
      if(key==101) goto endsr;
      if(key==108) break;
    }
    copy(s(2,28),inq_vert,fldlen(2,28));
    copy(s(2,29),inq_regio,fldlen(2,29));
    fkey=1;
    if(sort_meth=='A') fkey=2;
    else if(sort_meth=='P') fkey=21;
    else if(sort_meth=='G') fkey=7;
  }
#endif

  if(fldlen(22,1)){
    if(sel_info()) goto endsr;
  }
  selp_use=NO;
  if(selp_ask()) goto endsr;
#if !FLAGRUB
  if(stu==2 && fkey==1 && klcd==NO){
    fkey=21;if(faskeyi(stu,fkey,0)==45) fkey=1;
  }
#endif
  if(stu==2 && fldlen(2,200) && selp_use){
		k=s(2,200)-s(2,1);
		if(used(&selp_bf[2][k],fldlen(2,200))) 	skip_blocked='N'; // deze vraag overrulen omdat ze elders geselecteerd is
	}
	fasunlck(-1);
  cd=YES; if((stu==1 && lvcd==NO) || (stu==2 && klcd==NO)) cd=NO;
	k=1; if(nr==2) k=3;
  getsysprNew(k,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;

	k=1; if(nr==2) k=3;
	getsysprNew(k,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  free=999;

  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t50eb>"); prttext(fichenm[nr]); prttext("<eb><t95>");
  prtfld(25,2,-1); prttext("<t120>");prttext("Blz.<ppp>.");
  prtbuf(1);
  z=1;
  prt_fax=NO;if(sys3762 & 2) prt_fax=YES;
  if(stu<=2){
#if FLAGRUB
    if(stu!=2) {prttab(z,stu,1,1,-1); prttitle(z++,"Recnr",3);}/* SPECIFIEK */
    if(cd) {prttab(z,stu,2,1,-1); prttitle(z++,"Code",3);}
    prttab(z,stu,3,1,35); prttitle(z++,"Naam",3);
    if(stu==2 && pfld_ext>0 && fldlen(2,pfld_ext)){
      prttab(z,stu,pfld_ext,1,-1); prttitle(z++,"",3);
    }

    prttab(z,stu,4,1,25); prttitle(z++,"Straat",3);
    if(prt_omz!='J'){/* SPECIFIEK */
      prttab(z,stu,5,1,-1); prttitle(z++,"Postnr.",3);
    }
    prttab(z,stu,6,1,20); prttitle(z++,"Gemeente",3);
    if(stu==2 && pfld_ext>0 && fldlen(2,pfld_ext)) goto stop_hdr;
    prttab(z,stu,8,1,-1); prttitle(z++,"Telefoon",3);
    if(prt_omz!='J'){/* SPECIFIEK */
      prttab(z,stu,9,1,-1); prttitle(z++,"Fax",3);
      prttab(z,stu,7,0,30); prttitle(z++,"Land",3);
    }
    else{
      prttab(z,stu,47,1,-1); prttitle(z++,"L.AK.dat",0x13);
      prttab(z,stu,57,1,-1); prttitle(z++,"Jaaromzet",0x13);
      prtitab(z,fm_od62_,&bkhsaldo,1,-1); prttitle(z++,"Saldo",0x13);
    }
#else
    prttab(z,stu,1,1,-1); prttitle(z++,"Recnr",3);
    if(cd) {prttab(z,stu,2,1,-1); prttitle(z++,"Code",3);}
    prttab(z,stu,3,1,35); prttitle(z++,"Naam",3);
    if(stu==2 && pfld_ext>0 && fldlen(2,pfld_ext)){
      prttab(z,stu,pfld_ext,1,-1); prttitle(z++,"",3);
    }

    if(prt_fax==NO){
      prttab(z,stu,4,1,25); prttitle(z++,"Straat",3);
      prttab(z,stu,5,1,-1); prttitle(z++,"Postnr.",3);
    }
    prttab(z,stu,6,1,20); prttitle(z++,"Gemeente",3);
    if(stu==2 && pfld_ext>0 && fldlen(2,pfld_ext)) goto stop_hdr;
    prttab(z,stu,8,1,-1); prttitle(z++,"Telefoon",3);
    if(stu==2 && (sys3762 & 0x10)){
      prttab(z,stu,10,1,-1); prttitle(z++,"BTW-nr",3);
      goto stop_hdr;
    }
    if((sys3762 & 8) && fldlen(4,0)){
      prtitab(z,fm_od6_2,&bkhsaldo,1,-1); prttitle(z++,"Saldo",0x13);
      goto stop_hdr;
    }
    if(sys3762 & 0x20){
      prttab(z,stu,70,1,-1); prttitle(z++,"Saldo",3);
      goto stop_hdr;
    }
    if(prt_fax){
      prttab(z,stu,9,1,-1); prttitle(z++,"Fax",3);
      prttab(z,stu,12,1,-1); prttitle(z++,"Rekening",3);
    }
    else{
#if FLAGGBL
      prttab(z,stu,9,1,-1); prttitle(z++,"GSM",3);
#else
      prttab(z,stu,9,1,-1); prttitle(z++,"Fax",3);
#endif
    }
    prttab(z,stu,7,0,30); prttitle(z++,"Land",3);
#endif

  }
  stop_hdr:;
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
      *u(stu,1)=getnr++;
      fuval=fasgeti(stu);
      if(fuval==46) goto next;
      else if(fuval) break;
    }
    if((nr==0 || nr==1)){
#if FLAGRUB
      if(stu==2){/* SPECIFIEK */
		    if(inq_vert[0] && cmpstr(inq_vert,s(2,28),fldlen(2,28))) goto next;
				if(inq_regio[0] && cmpstr(inq_regio,s(2,29),fldlen(2,29))) goto next;
      }
#endif
      if(selp_tst()){
				if(stu==2 && fldlen(62,1)){
					if(fldlen(2,200) && *u(2,200) && skip_blocked=='J') goto next;
					fasinit(62);*u(62,2)=*pu_2_1;faskeyi(62,1,0);
					for(k=5;k<10;k++) if(*s(62,k)) break;
					if(only_memo=='J' && k>=10) goto next;
				}
				if(fldlen(22,1)){
					q_info_=get_info(YES);
					if(only_info=='J' && q_info_==0) goto next;
					if(stu==2 && fact_klt && *u(2,51)!=fact_klt) goto next;
				}
#if FLAGRUB
  if(prt_omz=='J' && fldlen(4,0) && stu<3){
#else
	if((sys3762 & 8) && fldlen(4,0) && stu<3){
#endif
	  bkhsaldo=getsaldo(*u(stu,1)+((stu-1)*30000));
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
	if(stu==2 && prt_bestbon=='J'){
	  z=0;
	  for(k=0;k<fldlen(2,120)/2;k++){
 			fasinit(6);
			if(*pu_6_1=*(uint16 *)(s(2,120)+k*2)){
				if(fasgeti(6)==0){
					prttext("<t15>");prtfld(6,2,-1);prttext("  "); prtfld(6,3,-1); nextline();
					z++;
				}
			}
		}
	  if(z) nextline();
	}
	if(fldlen(22,1) && q_info_ && prt_info=='J') print_info(q_info_);
      }
    }
  }
  if(cnt){
    nextline();
    prttext("*** Aantal fiches :"); *u(stu,1)=cnt; prtfld(stu,1,-1); nextline();
  }
  prtclose();
  endsr:;
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


static double getsaldo(rek_)                                    /* lev or klt only */
uint16 rek_;
{
  int16 ks;
  double saldo_=0;
									
  fasinit(4);
  *u(4,5)=rek_;
  FOREVER{
    ks=faskeyi(4,4,2);
    if(ks || *u(4,5)!=rek_) break;
    if(rek_<30000) saldo_-=*d(4,32); else saldo_+=*d(4,32);
  }
  return (double) saldo_;
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
    scrget(2,90);z=1;
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
      fact_klt=*pu_2_1;
    } else fact_klt=0;
    if(key==108) break;
  }
  return NO;
}
 
static prt_toer(mode_)
int16 mode_;
{
  int16 form_dat[8],pr_mode,prtnr,j,k,z;
 
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  free=999;
	fasunlck(-1);
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t50eb>Klantentoeren<eb><t95>");
  prtfld(25,2,-1); prttext("<t120>");prttext("Blz.<ppp>.");
  prtbuf(1);
  z=1;
  prttab(z,stu,3,1,-1); prttitle(z++,"Toer",3);
  k=1; if(fldlen(2,2)) k=2;
//  prttab(z,2,k,1,-1); prttitle(z++,"Code",3);
  prttab(z,2,3,1,38); prttitle(z++,"Naam",3);
  prttab(z,2,4,1,25); prttitle(z++,"Straat",3);
  prttab(z,2,5,1,-1); prttitle(z++,"Postnr.",3);
  prttab(z,2,6,1,20); prttitle(z++,"Gemeente",3);
  prttab(z,2,8,1,-1); prttitle(z++,"Telefoon",3);
	prttab(z,2,20,1,-1); prttitle(z++,"Gsm",3);
  prtbuf(3);
  p_pdfname("Klantentoeren",0,0);

  if(mode_==0) fasinit(stu);
  FOREVER{
    if(mode_==0){
      if(faskeyi(stu,2,2)) break;
    }
    nextline();
    prtinfo(1,2);
    for(k=0;k<fldlen(63,10)/2;k++){
      fasinit(2);*pu_2_1=*(uint16 *)(s(63,10)+k*2);
      if(fasgeti(2)==0){
	for(j=2;j<=15;j++) prtinfo(j,0); nextline();
      }
    }
    if(mode_) break;
  }
  prtform(0);
  prtclose();
  endsr:;
}
 
static nextline()
{
  free=prtline();
}

static getfname(nr,array)
int16 nr,array;
{
  nr--;
  sysget(300+17*nr,15,files[array].filname);
  sysget(315+17*nr,2,&files[array].filstru);
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

static initload()
{
  int16 k,nr_;
 
  fasunlck(0);
	fileopen(1);
	fileopen(2);
  fileopen(15);
	if(fldlen(16,1)) fileopen(13);
  if(fldlen(66,1)) fileopen(12);
  if(fldlen(4,1)) fileopen(4);
  for(k=0;k<6;k++) getfname(k+1,k);
	if(fldlen(7,1)) fileopen(7);
	fileopen(9);
  getfname(12,6);
	if(fldlen(3,1)) fileopen(3);
  sysget( 294,4,def_munt);
  sysget(586,2,intr_def_land); if(intr_def_land[0]=='\0') copy("BE",intr_def_land,2);
  sysget(588,2,&intr_def_vervoer);if(intr_def_vervoer==0) intr_def_vervoer=3;
  sysget(590,2,&intr_def_transactie); if(intr_def_transactie==0) intr_def_transactie=11;
  sysget(1854,2,&sys1854);
  sysget(1918,2,&sear_stt);
  sysget(1048,32,&btw_pct[0]);
  sysget(2212,4,talen);
  sysget(2222,2,&def_qfak);
  sysget(2698,2,&sys2698);
  sysget(2830,24,(char *)&sys2830[0]);
	sysget(3654,16,(char *)&sys2830[6]);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
  sysget(3586,2,&sys3586);
  sysget(1084,4,&def_btw);
  sysget(3608,2,def_grbex);
  sysget(3610,4,&def_grb);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
	sysget(3652,2,&sys3652);
  sysget(3714, 2,&stat_dat[12]);
  sysget(3726,24,&stat_dat[ 0]); stat_dat[13]=*u(25,2);
  sysget(3892,2,&sys3892); if(sys3892 & (1<<1)) suppr_wi=YES;
  sysget(3894,2,&sys3894);
  sysget(3976,2,&sys3976);
  sysget(2770,60,(char *)&nm_loc[0][0]);
	sysget(4294,40,(char *)&loc_klt[0]); 
  sysget(4366,2,&pfld_ext);
  sysget(4610,60,vptekst);
  sysget(4670,6,stuksprx);
  sysget(4740,40,&vptekst[60]);
  sysget(4780,4,&stuksprx[6]);
  sysget(3762,2,&sys3762);if(sys3762 & 0x01) dsp_last=YES;
  if(sys3762 & 0x04) auto_nr=YES;
  sysget(3876,2,&sys3876);
  sysget(3896,6,sys3896);
#if FLAGHDY
	for(k=0;k<10;k++) sysget(5000+k*80,80,(char *)&fost_stu[k].code[0]);
	for(k=0;k<10;k++) sysget(6600+k*80,80,(char *)&fost_stu[10+k].code[0]);
#endif
#if FLAGGOU
	sysget(27926,120,&vertegenw[0].code[0]);
  sysget(28166,300,&kw_groep[0][0]);
#endif

  pnr_kbak=0;pnr_kstk=0;
  for(k=0;k<6;k++){
    if(sys3896[k]){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
	if(pnr_kbak==0) pnr_kbak=PrNrs[nr_];
	pnr_kstk=PrNrs[nr_];
      }
    }
  }
  chk_intra=NO; if(fldlen(4,48)) chk_intra=YES; 
  len2_120=fldlen(2,120);
  len6_2=fldlen(6,2);len6_3=fldlen(6,3);
  len2_3=fldlen(2,3);
  calctype=s(52,22);

  sysget(3678,2,&def_taal);
  pu_6_1=u(6,1);
  pu_2_1=u(2,1);
}

static fichupd(mode)
int16 mode;
{
  int16 g,j,k,pnr_,curs,curs_taal,key,z,start_,dcurs_,z_prx_,pos_1_4_,curspos_,pr_offset_,kleur_,dsp_recnr_;
  char *pdum,dumm_[10],*pvar,nm_groep[50],nm_subgroep[50],vstr_[12],dspstr_[50];
  uint16 fakklnr,last_grp,ix_vpbeg_=0,prstu_;
  char *p_stu_3;
 
	fasunlck(-1);
#if FLAGEPD
	if(mode==2){
		if(stu==1) copy("44",s(1,2),2); else if(stu==2) copy("42",s(2,2),2);
		get_newcode();
	}
#else
	if(((sys3762 & (1<<6))==0) && mode==2 && (stu==1 || stu==2) && fldlen(stu,2) && *s(stu,2)=='\0') get_newcode();
#endif
#if FLAGCRA
	only_dsp=NO; if((*u(25,4)==110 || sys2698) && mode==1) only_dsp=YES;
#else
  only_dsp=NO; if(sys2698 && mode==1) only_dsp=YES;
#endif
#if FLAGGBL
	if(only_dsp){sys3892=6; suppr_wi=YES;}
	else {sys3892=0; suppr_wi=NO;}
#endif
  loaded=NO;
  p_stu_3=s(stu,3);pos_1_4_=s(1,4)-s(1,1);
  taal_i='\0'; dsp_recnr_=NO;
  FOREVER{
    if(stu==1){/* leveranciers */
      curs=2;
redo_l:
			if(fldlen(stu,200)){
				if(*u(stu,200)) ConLook(1); else   ConLook(0);
			}
      scrnum=0; scrget(2,6);z=1;dsp_i_flag();
			if(mode==1){
				scraddpicto(25,0,0,0,2,1,93,0,4,"vorig"); 
				scraddpicto(26,0,78,0,2,1,92,0,4,"volgend"); 
				scraddpicto(20,0,75,1,4,2,514,0,0,"Extra opties"); 
			}
      scrfld(z++,25,1);
      if(lvcd  && dsp_recnr_==NO) scrfld(z++,1,2); else scrofld(z++,1,1,-1);
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
			if(key==5020){DisplayExtraFuncties(stu);key=107;} // extra opties
#if FLAGCRA
			if(*u(25,4)!=110 && key==15 && only_dsp){only_dsp=NO;goto redo_l;}
#else
      if(key==15 && only_dsp && CheckPw(1,PwUpdNr,0)){only_dsp=NO;goto redo_l;}
#endif
      if(key==106){
				if(mode==2) return NO;
				else return YES;
      }
			if(key==111 && mode==1){ if(dsp_recnr_) dsp_recnr_=NO; else dsp_recnr_=YES; goto redo_l;} // voor test om recordnr te zien
      if(mode==2 && key==111 && lst_recs[stu]){
				fasinit(stu);*u(stu,1)=lst_recs[stu];fasgeti(stu);
				zero(s(stu,1),s(stu,3)-s(stu,1));
      }
      k=*p_stu_3;
      if(key==101 && k=='\0') return NO;

      if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo_l;}
      if((k<'A' && k>'Z') && (k<'a' && k>'z') && (k<'0' && k>'9')) {errnum=30;curs=3;goto redo_l;}
      if(lvcd && *s(1,2)=='\0') {errnum=38;curs=2;goto redo_l;}
      if(taal_chk(16)) {curs=curs_taal;goto redo_l;}
			if(!only_dsp && fldlen(stu,18) && *s(stu,18)){
				if(k=IbanTools(s(stu,18),s(stu,19),s(stu,12),1)) {curs=18+k-1; goto redo_l;} 
		  }
      if(chk_intra){
				if(fldlen(1,35)) if(*s(1,35)=='\0'){errnum=38;curs=35;goto redo_l;}
				if(fldlen(1,36)) if(*i(1,36)==0){errnum=38;curs=36;goto redo_l;}
				if(fldlen(1,38)) if(*i(1,38)==0){errnum=38;curs=38;goto redo_l;}
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
					*pu_2_1=*u(2,51);
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
					*pu_2_1=*u(2,52);
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
#if FLAGGOU
      if(fldlen(2,29)){  // GOU
				for(k=0;k<10;k++){
					if(cmpstr(s(2,28),vertegenw[k].code,2)==0) break;
				}
				if(k<10) copy(vertegenw[k].naam,s(2,29),10);
				else zero(s(2,29),fldlen(2,29));
      }
#endif
      curs=2; dsp_recnr_=NO;
redo_k:
			if(fldlen(2,200)){
				if(*u(2,200)) ConLook(1); else   ConLook(0);
			}
      scrnum=0;scrget(2,7); z=1;dsp_i_flag();
			if(mode==1){
				scraddpicto(25,0,0,0,2,1,93,0,4,"vorig"); 
				scraddpicto(26,0,78,0,2,1,92,0,4,"volgend"); 
				scraddpicto(20,0,75,1,4,2,514,0,0,"Extra opties"); 
			}
      scrfld(z++,25,1);
      if(klcd && dsp_recnr_==NO) scrfld(z++,2,2); else scrofld(z++,2,1,-1);
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
					scrchat(z-1,0xB);if(!only_dsp) scraddpicto(10,z-1,4,0,2,1,86,0,4,"Maak BTW-plichtig"); 
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
      for(k=53;k<MAXFLD;k++)
		  scrfld(z++,2,k);
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
      key=scrupd(dcurs_,0x7A9);curs=2;curspos_=fldcurs;
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
			if(key==5010){
				if (*(s(2,10)+3) & 0x40) *(s(2,10)+3)  &= 0xBF; else *(s(2,10)+3)  |= 0x40;
//				if(*l(2,10)>=BTWNR_OFFSET) *l(2,10)-=BTWNR_OFFSET;
//				else *l(2,10)+=BTWNR_OFFSET;
				goto redo_k;
			}	
			if(key==5011 && fldlen(2,195) && !only_dsp){
				if(*s(2,195)=='J') *s(2,195)='N'; 
				else{
					if(*s(2,21)){
						*s(2,195)='J';
						if(fldlen(2,2) || fldlen(2,196)) DisplayExcludeLev();
					}
					else {curs=21;errnum=38;}
				}
				goto redo_k;
			}		
			if(key==5020){DisplayExtraFuncties(stu);key=107;} // extra opties
#if FLAGCRA
			if(*u(25,4)!=110 && key==15 && only_dsp){only_dsp=NO;goto redo_k;}
#else
      if(key==15 && only_dsp && CheckPw(1,PwUpdNr,0)){only_dsp=NO;goto redo_k;}
#endif
      if(key==106){
	if(mode==2) return NO;
	else return YES;
      }
			if(key==111 && mode==1){ if(dsp_recnr_) dsp_recnr_=NO; else dsp_recnr_=YES; goto redo_k;} // voor test om recordnr te zien
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

#if FLAGGOU
      if(fldlen(2,29)){ // GOU
				for(k=0;k<10;k++){
					if(cmpstr(s(2,28),vertegenw[k].code,2)==0) break;
				}
				if(k<10) copy(vertegenw[k].naam,s(2,29),10);
				else zero(s(2,29),fldlen(2,29));
			}
#endif
 			if(key==18){curs=curspos_+1;goto redo_k;}
      k=*p_stu_3;
      if(key==101 && k=='\0') return NO;

      if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo_k;}
      if((k<'A' || k>'Z') && (k<'a' || k>'z') && (k<'0' || k>'9')) {errnum=30;curs=3;goto redo_k;}
      if(klcd && *s(2,2)=='\0') {errnum=38;curs=2;goto redo_k;}
      if(taal_chk(24)) {curs=curs_taal;goto redo_k;}

      if(fldlen(2,51)){
				if(selp_bf[1][0]=='\0') {*u(2,51)=0;selp_bf[1][50]='\0';}
				else if(cmp_str(&selp_bf[1][0],&selp_bf[1][50],fldlen(2,3))){
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					fasinit(2);
					copy(&selp_bf[1][0],s(2,3),fldlen(2,3));
					k=search(2,0); if(k==YES && errnum==0) errnum=39;
					if(!errnum){
						copy(s(2,3),&selp_bf[1][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[1][50],fldlen(2,3));
					}
					fakklnr=*pu_2_1;
					copy(selp_bf[0],s(2,1),fldlen(2,0));
					*u(2,51)=fakklnr;
					if(errnum) {curs=51;goto redo_k;}
	
				}
      }
      if(fldlen(2,52)==2){ // relatieklant
				if(selp_bf[2][0]=='\0') {*u(2,52)=0;selp_bf[2][50]='\0';}
				else if(cmp_str(&selp_bf[2][0],&selp_bf[2][50],fldlen(2,3))){
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					fasinit(2);
					copy(&selp_bf[2][0],s(2,3),fldlen(2,3));
					k=search(2,0); if(k==YES && errnum==0) errnum=39;
					if(!errnum){
						copy(s(2,3),&selp_bf[2][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[2][50],fldlen(2,3));
					}
					fakklnr=*pu_2_1;
					copy(selp_bf[0],s(2,1),fldlen(2,0));
					*u(2,52)=fakklnr;
					if(errnum) {curs=52;goto redo_k;}
	
				}
      }
			if(fldlen(stu,16)>30 && *s(stu,16)){
				if(k=IbanTools(s(stu,16),s(stu,17),s(stu,12),0)) {curs=18+k-1; goto redo_k;} 
		  }
      if(chk_intra){
				if(fldlen(2,74)) if(*s(2,74)=='\0'){errnum=38;curs=74;goto redo_k;}
				if(fldlen(2,75)) if(*i(2,75)==0){errnum=38;curs=75;goto redo_k;}
				if(fldlen(2,77)) if(*i(2,77)==0){errnum=38;curs=77;goto redo_k;}
      }
      if(key==109 && len2_120) {bst_inp();goto redo_k;}
      if(key==110 && fldlen(62,1)) {
				if(ovltest(2922)) ovlcall(2922,1); else DisplayMemo(stu);
				goto redo_k;
      }
      if(key==112 && *u(stu,1)) {dsp_info(); goto redo_k;}
      if(key!=5025 && key!=5026 && key!=101 && key!=108) goto redo_k;
    }

    else if(stu==6){/* artikel */
#if FLAGDU3
			BlokkeerStock=YES; // op achterkant fiche met F4 te deblokkeren 
#endif
      rev_prx_calc=NO;pr_offset_=0; dsp_recnr_=NO;
			if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(25,2)) pr_offset_=94;
      if(!errnum){
				zero(stubuf,sizeof stubuf);
				fasinit(1); fasinit(52);zero(nm_groep,sizeof nm_groep); zero(nm_subgroep,sizeof nm_subgroep); 
				if(mode==1 || mode==3 || mode==10) {
					fasinit(1);*u(1,1)=*u(6,7); fasgeti(1);
					copy(s(1,1),stubuf[0],pos_1_4_);
					*(uint16 *)&stubuf[0][pos_1_4_]=hashbuf(stubuf[0],pos_1_4_);
					if(fldlen(6,101)){
						fasinit(1);*u(1,1)=*u(6,101); fasgeti(1);
						copy(s(1,1),stubuf[1],pos_1_4_);
						*(uint16 *)&stubuf[1][pos_1_4_]=hashbuf(stubuf[1],pos_1_4_);
					}
					if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);}
					zero(nm_groep,sizeof nm_groep); zero(nm_subgroep,sizeof nm_subgroep); 
					if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);copy(s(52,14),nm_groep,fldlen(52,14));}
					if(fldlen(6,103) && *u(6,103) && *u(6,9)){
						fasinit(52);*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;
						if(fasgeti(52)==0) copy(s(52,14),nm_subgroep,fldlen(52,14));
  				}
#if FLAGGOU
					if(fldlen(6,49)){ // GOU
						k=*u(6,49)-1;
						if(k<0 || k>14) zero(s(6,50),fldlen(6,50));
						else copy(&kw_groep[k],s(6,50),fldlen(6,50));
					}
#endif

				}
				calcnet(pr_offset_);
				copy(s(1,3),oldnm,fldlen(1,3));
      }
      curs=2; rev_prx_calc=NO;
			last_grp=*u(6,9); ix_vpbeg_=0;
redo_a:
			if(fldlen(6,200)){
				if(*u(6,200)) ConLook(1); else   ConLook(0);
			}
			k=19; //if(fldlen(6,185)) k=59;
      scrnum=0;scrget(2,k); z=1;		dsp_i_flag();
			if(mode==1){
				scraddpicto(25,0,0,0,2,1,93,0,4,"vorig"); 
				scraddpicto(26,0,78,0,2,1,92,0,4,"volgend"); 
				scraddpicto(20,0,75,1,4,2,514,0,0,"Extra opties"); 
			}

			if(fldlen(6,105) && (*u(6,105) || pr_offset_)) {
				if(fldlen(6,185)) scraddpicto(1,0,75,6,4,2,538,0,4,"Prijs op datum"); 
				else scraddpicto(1,0,6,13,4,2,538,0,4,"Prijs op datum"); 
			}
			if(mode==2 && lst_recs[stu]) scraddpicto(10,0,74,2,4,2,532,0,0,"Kopieer vorig artikel"); 
			if(fldlen(6,104)){
				if(*s(6,104)=='J') {
					if(fldlen(6,185)) scraddpicto(9,0,71,6,4,2,88,0,3,"Korting toestaan"); 
					else scraddpicto(9,0,12,13,4,2,88,0,3,"Korting toestaan"); 
				}
				else{
					if(fldlen(6,185)) scraddpicto(9,0,71,6,4,2,88,0,4,"Blokkeer korting");
					else scraddpicto(9,0,12,13,4,2,88,0,4,"Blokkeer korting");
				}
			}
      scrfld(z++,25,1);
      if(fldlen(6,2) && dsp_recnr_==NO) scrfld(z++,6,2); else scrofld(z++,6,1,-1);
			if(fldlen(6,200) && mode==1){
				if(*u(6,200)==1) scrchat(z-1,0xB); else scrchat(z-1,0xFF);
				if(!only_dsp){
					if(*u(6,200)==1) scraddpicto(7,z-1,0,0,2,1,70,0,4,"Maak actief"); else scraddpicto(7,z-1,0,0,2,1,71,0,3,"Blokkeer");
				}
			}
			if(fldlen(6,195) && !only_dsp){
				if(*s(6,195)=='J') scraddpicto(8,z-1,2,0,2,1,32,0,4,"NIET in webshop"); else scraddpicto(8,z-1,2,0,2,1,32,0,3,"Toon in webshop");
			}
			if(fldlen(6,194) && !only_dsp){
				k=2; if(fldlen(6,195)) k=4;
				if(*s(6,194)=='J') scraddpicto(10,z-1,k,0,2,1,82,0,4,"NIET in B2B-webshop"); else scraddpicto(10,z-1,k,0,2,1,82,0,3,"Toon in B2B-webshop");
			}
			scrfld(z++,6,3);
			if(BlokVerpakkingDisplay==NO && fldlen(6,102) && *u(6,1)){ // deelverpakkingen
				copy(s(6,1),MasterArt,fldlen(6,0));
				if(*u(6,102)) scraddpicto(5,z-1,0,0,2,1,527,0,0,"Hoofdfiche");  // is zelf een deelverpakking
				else{
					fasinit(6);*u(6,102)=*(uint16 *)pMST(6,1); 
  				if(faskeyi(6,15,0)==0) scraddpicto(4,z-1,0,0,2,1,101,0,4,"Verpakkingen"); // er zijn deelverpakkingen
					else scraddpicto(4,z-1,0,0,2,1,101,0,3,"Verpakkingen"); // er zijn geen deelverpakkingen
				}
				copy(MasterArt,s(6,1),fldlen(6,0));
			}
      for(k=4;k<=6;k++) scrfld(z++,6,k);
      scrbfld(z++,1,1+lvcd,stubuf[0],YES);
      scrbfld(z++,1,3,stubuf[0],NO);
      scrfld(z++,6,8);
      if(fldlen(6,101)) scrbfld(z++,1,3,stubuf[1],NO);
      scrfld(-z,6,9);z++;scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_groep); /* scrofld(z++,52,14,-1);*/ scraddpicto(3,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		  if(fldlen(6,103)){
				scrfld(-z,6,103);z++;scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_subgroep);
				if(*u(6,9)) scraddpicto(6,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
			}
      scrfld(z++,6,10);
			scrfld(z++,6,11+pr_offset_);if(pr_offset_) scrchat(z-1,0x9);
			if(mode==1 && fldlen(6,30)&& only_dsp==NO) scraddpicto(2,z-1,0,0,4,2,522,0,4,"Bereken prijs"); 
      for(k=12;k<=18;k++){
				if(suppr_wi==NO || !(sys3892 & 0x04)){
					scrfld(z++,6,k+pr_offset_); if(pr_offset_ && fldlen(6,k+pr_offset_)) scrchat(z-1,0x9);
				}
				else z++;
      }
			for(k=19;k<=20;k++) {scrfld(z++,6,k+pr_offset_);if(pr_offset_ && fldlen(6,k+pr_offset_)) scrchat(z-1,0x9);}
      z_prx_=z;
			if(fldlen(6,185)){
				for(k=0;k<5;k++){
					pnr_=k;
redo_rechts:;  
					if(pr_offset_) prstu_=PrNrs[pnr_+10]; else prstu_=PrNrs[pnr_];
					if(fldlen(6,prstu_)){
						scrifld(z++,fm_os6,&vptekst[pnr_*10]);
						fmt_get(6,prstu_); if(rev_prx_calc) fmt[1]&=0xBF;
						scrifld(z++,fmt,f(6,prstu_)); if(pr_offset_) scrchat(z-1,0x9);
						if(sys3894 & 1<<pnr_) scrifld(z++,fm_os2,"IN");
						else scrifld(z++,fm_os2,"EX");
						if(suppr_wi==NO){
							if(rev_prx_calc) scrifld(z++,fm_uf4_1,&net_winst[pnr_]);
							else scrifld(z++,fm_of4_1,&net_winst[pnr_]);
						}
						else z++;
					}
					else for(j=0;j<4;j++) streepje(z++);
					if(pnr_<5){pnr_=k+5; goto redo_rechts;}
				}
			}
			else{
				for(k=0;k<6;k++){
					if(pr_offset_) prstu_=PrNrs[k+10]; else prstu_=PrNrs[k];
					if(fldlen(6,prstu_)){
						scrifld(z++,fm_os6,&vptekst[k*10]);
						fmt_get(6,prstu_); if(rev_prx_calc) fmt[1]&=0xBF;
						scrifld(z++,fmt,f(6,prstu_)); if(pr_offset_) scrchat(z-1,0x9);
						if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
						else scrifld(z++,fm_os5,"Excl.");
						if(suppr_wi==NO){
							if(rev_prx_calc) scrifld(z++,fm_uf4_1,&net_winst[k]);
							else scrifld(z++,fm_of4_1,&net_winst[k]);
						}
						else z++;
					}
					else for(j=0;j<4;j++) streepje(z++);
				}
			}
      dcurs_=curs; if(only_dsp) dcurs_=-1;
      key=scrupd(dcurs_,0x07FB);
			curs=2;curspos_=fldcurs;
			if(fldlen(6,200)) ConLook(0);
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key==5001){
				if(pr_offset_==0) pr_offset_=94; else pr_offset_=0; 
				calcnet(pr_offset_);
				goto redo_a;
			}
			if(key==5002){fasinit(26);*d(26,18)=0.; ovlcall(213,1);} // prijzenbeheer
			if(key==5011){ 
				if(ix_vpbeg_) ix_vpbeg_=0; else ix_vpbeg_=4;
				goto redo_a;
			}
			if(key==5003){// uitgebreid groep zoeken
				if(search(52,98)) {
					fasinit(52); if(*u(6,9)){	*u(52,1)=*u(6,9);fasgeti(52);}
				}
  			else *u(6,9)=*u(52,1);
				zero(nm_groep,sizeof nm_groep); 
				if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);copy(s(52,14),nm_groep,fldlen(52,14));}
				if(fldlen(6,103)){
					zero(nm_subgroep,sizeof nm_subgroep); 
					if(*u(6,9)!=last_grp || *u(6,9)==0) *u(6,103)=0; // SUBGROEP WISSEN
					if(*u(6,103) && *u(6,9)){
						fasinit(52);*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;
						if(fasgeti(52)==0) copy(s(52,14),nm_subgroep,fldlen(52,14));
  				}
				}
				last_grp=*u(6,9);
				goto redo_a;
			} 
			if(key==5004) DisplayDeelVerpakkingen();
			if(key==5005) DisplayKoppeling();
			if(key==5006 && fldlen(6,103)){
				*u(6,103)=SelecteerSubgroep(*u(6,9)); 
				fasinit(52);
				if(*u(6,103)){*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;fasgeti(52);}
				copy(s(52,14),nm_subgroep,fldlen(52,14));
				goto redo_a;
			}
			if(key==5007 && fldlen(6,200)){ // blokkeer
				if(*u(6,200)) *u(6,200)=0; else *u(6,200)=1;
				goto redo_a;
			}
			if(key==5008 && fldlen(6,195)){ // webshop artikel
				if(*s(6,195)=='J') *s(6,195)='N'; else *s(6,195)='J';
				goto redo_a;
			}
			if(key==5010 && fldlen(6,194)){ // B2B-webshop artikel
				if(*s(6,194)=='J') *s(6,194)='N'; else *s(6,194)='J';
				goto redo_a;
			}
			if(key==5009 && fldlen(6,104) && only_dsp==NO){ // blokkeer korting 
				if(*s(6,104)=='J') *s(6,104)='N'; else *s(6,104)='J';
				goto redo_a;
			}
      if(key==5020){DisplayExtraFuncties(stu);key=107;} // extra opties
			if(key==111 && mode==1){ if(dsp_recnr_) dsp_recnr_=NO; else dsp_recnr_=YES; goto redo_a;} // voor test om recordnr te zien
#if FLAGCRA
			if(*u(25,4)!=110 && key==15 && only_dsp){only_dsp=NO;goto redo_a;}
#else
      if(key==15 && only_dsp && CheckPw(1,PwUpdNr,0)){
				only_dsp=NO;
#if FLAGGBL
	      if(only_dsp){sys3892=6; suppr_wi=YES;}
	      else {sys3892=0; suppr_wi=NO;}
#endif
				goto redo_a;
			}
#endif
      if(key==106){
				if(mode==2) return NO;
				else return YES;
      }
      if(mode==2 && (key==111 || key==5010) && lst_recs[stu]){
				fasinit(stu);*u(stu,1)=lst_recs[stu];fasgeti(stu);
				fasinit(1);*u(1,1)=*u(6,7); fasgeti(1);
				copy(s(1,1),stubuf[0],pos_1_4_);
				if(fldlen(6,101)){
					fasinit(1);*u(1,1)=*u(6,101); fasgeti(1);
					copy(s(1,1),stubuf[1],pos_1_4_);
				}
#if FLAGVHY
				zero(s(stu,1),s(stu,2)-s(stu,1));
#else
				zero(s(stu,1),s(stu,3)-s(stu,1));
#endif
				if(fldlen(66,1)) fasinit(66);
	      if(fldlen(64,1)) fasinit(64);
				zero(s(6,8),fldlen(6,8));
				zero(s(6,29),fldlen(6,29));
				zero(s(6,33),fldlen(6,33));
				zero(s(6,46),s(6,51)-s(6,46));
				zero(s(6,63),s(6,65)-s(6,63));
				zero(s(6,53),s(6,74)-s(6,53));
				zero(s(6,102),fldlen(6,102));
				zero(s(6,105),s(6,150)-s(6,105));
      }
			fasinit(52);zero(nm_groep,sizeof nm_groep); 
			if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);copy(s(52,14),nm_groep,fldlen(52,14));}
			zero(nm_subgroep,sizeof nm_subgroep); 
			if(fldlen(6,103)){
				if(*u(6,9)!=last_grp || *u(6,9)==0) *u(6,103)=0; // SUBGROEP WISSEN
				if(*u(6,103) && *u(6,9)){
					if(*u(6,103)>10) errnum=34;
					else{
  					fasinit(52);*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;
	  				if(fasgeti(52)==0) copy(s(52,14),nm_subgroep,fldlen(52,14));
						if(nm_subgroep[0]=='\0') errnum=34;
					}
  			}
				if(errnum) {curs=curspos_; goto redo_a;}
			}
			last_grp=*u(6,9);
      if(*u(6,9)){
				if(key==18){curs=curspos_+1;goto redo_a;}
      }
      if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo_a;}
      g=*p_stu_3;
      if(g=='\0'){
				if(key==101) return NO;
				errnum=38;curs=3;goto redo_a;
      }
      if(g<'A' || g>'z' || (g>'Z' && g<'a')) {errnum=30;curs=3;goto redo_a;}
#if !FLAGGDN // mogelijkheid ook zonder code
      if(*s(6,2)=='\0'){errnum=38;curs=2;goto redo_a;}
      if(*s(6,2)==' '){errnum=34;curs=2;goto redo_a;}
#endif
      if(stubuf[0][s(1,3)-s(1,1)]=='\0'){errnum=30;curs=8;goto redo_a;}
      if(*(uint16 *)&stubuf[0][pos_1_4_]!=hashbuf(stubuf[0],pos_1_4_)){
				fasinit(1);copy(&stubuf[0][s(1,3)-s(1,1)],s(1,3),fldlen(1,3));
				if(search(1,0)){curs=8;goto redo_a;}
				copy(s(1,1),stubuf[0],pos_1_4_);
				*(uint16 *)&stubuf[0][pos_1_4_]=hashbuf(stubuf[0],pos_1_4_);
				*u(6,7)=*u(1,1);
      }
      if(fldlen(6,101) && *(uint16 *)&stubuf[1][pos_1_4_]!=hashbuf(stubuf[1],pos_1_4_)){
				fasinit(1);copy(&stubuf[1][s(1,3)-s(1,1)],s(1,3),fldlen(1,3));
				if(*s(1,3)=='\0') fasinit(1);
				else{
				  if(search(1,0)){curs=10;goto redo_a;}
				}
				copy(s(1,1),stubuf[1],pos_1_4_);
				*(uint16 *)&stubuf[1][pos_1_4_]=hashbuf(stubuf[1],pos_1_4_);
				*u(6,101)=*u(1,1);
      }
      if(*i(6,9)<1 || *i(6,9)>99){
				if(fldlen(6,101)) curs=11; else curs=10;
				errnum=34;goto redo_a;
			}
      if(key==105 && fldlen(66,1)) {stock_loc();goto redo_a;}
//      if(fldlen(6,200) && key==102) key=art_verp();
      if(key==109) key=artik_bis(mode);
#if FLAGOLH
      if(key==110 && fldlen(6,106)){
	       key=dsp_stat();
	       if(key==106){
	        if(mode==2) return NO;
	        else return YES;
	      }
      }
      if(key==105) {
#else
			if(key==110) {
#endif
				if(rev_prx_calc) {calcnet(pr_offset_);rev_prx_calc=NO;}
				else {rev_prx_calc=YES;}
				curs=z_prx_;goto redo_a;
      }
      calcnet(pr_offset_);
      if(mode==2 && sys3976) fill_dfprx();
      if(key==106){
				if(mode==2) return NO;
				else return YES;
      }
			if(key==102 && ovltest(268)) ovlcall(268,1);
      if(key==112 && *u(stu,1)) {dsp_info(); goto redo_a;}
      if(key!=5025 && key!=5026 && key!=108 && key!=101 && key!=111) goto redo_a;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
    }
    else if(stu==63){/* klantentoeren */
      only_dsp=NO;
      pdum=&dumm_[0];
      ram_recl=s(2,4)-s(2,1) + 2;/* + 2 bytes hash */
      max_line=fldlen(63,10)/2;
      if(max_line>(sizeof ram)/ram_recl) max_line=(sizeof ram)/ram_recl;
      hash_len=fldlen(2,1)+ fldlen(2,2)+fldlen(2,3);
      dat_len=hash_len;start_=0;
 
      zeros(ram,sizeof ram);
      for(k=0;k<max_line;k++){
				fasinit(2);*pu_2_1=*(uint16 *)(s(63,10)+k*2);fasgeti(2);
				hash_val=hash(2);
				stu2ram(2,k);
      }
      scrnum=0;
      FOREVER{
				redo_t:
				scrget(2,135);z=1;
				scrfld(z++,63,3);
				for(j=start_;j<(start_+D_LIN_SCR);j++){
					j++; scrifld(z++,fm_ou2,&j); j--;
					if(fieldspc(2,3,&pdum,fmt)>0){
						pvar=ram+(j*ram_recl + (s(2,3)-s(2,1)));
						scrifld(z++,fmt,pvar);
					}
					z++;
				}
				key=scrupd(curs,0x2FF);curs=1;curspos_=fldcurs;
				if(key==106){
					if(mode==2) return NO;
					else return YES;
				}
				k=*p_stu_3;
				if(key==101 && k=='\0') return NO;
				if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;curs=1;goto redo_t;}
									
				if(key==104){
					j=(curspos_-2)/3;j+=start_;
					ins_lin(2,j);
					curs=curspos_;goto redo_t;
				}
				if(key==105){
					j=(curspos_-2)/3;j+=start_;
					del_lin(2,j);
					curs=curspos_;goto redo_t;
				}
				for(k=start_;k<(start_+D_LIN_SCR);k++){
					chk_again:;
					ram2stu(2,k);
					if(*s(2,3) && hash_val!=hash(2)){
						if(search(2,0)){
							errnum=39;curs=2+(k-start_)*3;goto redo_t;
						}
						hash_val=hash(2);
					}
					else if(*s(2,3)=='\0'){fasinit(2);hash_val=0;}
					stu2ram(2,k);
				}
				for(k=0;k<max_line;k++){
					ram2stu(2,k);
					copy(s(2,1),s(63,10)+k*2,2);
				}
				if(key==108 || key==101)break;
				if(key==110) prt_toer(1);
				if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
				if(key==103) start_+=D_LIN_SCR;
				if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
				j=0;
				for(k=0;k<D_LIN_SCR;k++){ram2stu(2,k+start_);if(*s(2,3)=='\0') {j=k;break;}}
				curs=2+j*3;
      }
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
	*u(62,2)=*pu_2_1;
	if(*u(62,1)) fasupd(62); else fasadd(62);
      }
      if(stu==6 && fldlen(66,1)){
	*u(66,2)=*pu_6_1;
	if(*u(66,1)) fasupd(66); else fasadd(66);
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
#if FLAGDMD
			if(stu==2) *s(2,26)='6';
#endif
      errnum=fasadd(stu); if(stu<10) lst_recs[stu]=*u(stu,1);
      if(stu==2 && fldlen(62,1)){
	*u(62,2)=*pu_2_1; fasadd(62);
      }
      if(stu==6 && fldlen(66,1)){
	*u(66,2)=*pu_6_1; fasadd(66);
      }
      fasflush(0);
    }
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
	fasunlck(-1);
  if(key==101) return NO;/* stop */
	if(key==5025) return 10;
	if(key==5026) return 11;
  return YES;
}

static SelecteerSubgroep(mastgroep)
int16 mastgroep;
{

  int16 j,k,key,z,curs,subgrpnr_=0,subnr_[10],max_sg_=0;
  char nm_subgroep[10][50],nm_groep[50],buf750[750];

  int16 nr_,start_,lijnpos,q_;
  char lijn_attrib_;
  uint16 funckeys;
 
	fmt_get(52,14);copy(s(52,1),buf750,fldlen(52,0));
	fasinit(52);*u(52,1)=mastgroep; if(fasgeti(52)) goto endsr;
	copy(s(52,14),nm_groep,fldlen(52,14));
	zero(nm_subgroep,sizeof nm_subgroep);zero((char *)subnr_,sizeof subnr_);
	max_sg_=0;
	for(k=0;k<10;k++){
		*u(52,1)=100+mastgroep*10+k; 
		if(fasgetu(52)==0){
			if(*s(52,14)){
			  copy(s(52,14),nm_subgroep[max_sg_],fldlen(52,14));subnr_[max_sg_++]=k+1;
			}
  	}
	}
	if(max_sg_==0) goto endsr;
  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
    redo:;
    scrnum=0;scrget(1,96);q_=0;
    funckeys=0x80E1;
		if(start_>0) {
      scraddpicto(1,0,76,2,4,2,18,0,4,"up"); 
      funckeys+=2;
    }
		if((start_+D_LIN_SCR)<max_sg_) {
      scraddpicto(2,0,76,21,4,2,13,0,4,"down"); 
      funckeys+=4;
    }
    scrifld(1,fm_os38,nm_groep);z=2;
    for(k=start_;k<start_+D_LIN_SCR;k++){
		  if(k>=max_sg_) break;
      k++;scrifld(z++,fm_ou4,&k);k--;
			scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_subgroep[k]);q_++;
			lijn_attrib_=0xFF;
			if(q_==(lijnpos+1)) lijn_attrib_=0x08;
  		scrchat(z-1,lijn_attrib_);
    }
    scrifld(36,fm_uu3,&nr_);
    key=scrupd(36,funckeys);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
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
											 start_-=D_LIN_SCR; if(start_<0) start_=0;lijnpos=0;scrnum=0;
										 }
										 break;
			case 13      :// PgDn 
			case 5002    :
			case 103     : if((start_+D_LIN_SCR)<max_sg_) {start_+=D_LIN_SCR;lijnpos=0;scrnum=0;}
										 break;
			case 10      : start_=0;lijnpos=0;scrnum=0;// HOME 
										 break;
			case 11      : start_=max_sg_-D_LIN_SCR;if(start_<0) start_=0;// END 
										 lijnpos=0;scrnum=0;
										 break;
			case 101     :
			case 106     : goto endsr;// annuleer 
										 break;
			case 18      :// ENTER 
			case 15      : // TAB  
			case 108     : if(nr_>max_sg_) errnum=34;// neem aan en exit 
										 else{
											 if(nr_>0) subgrpnr_=subnr_[nr_-1];
											 else subgrpnr_=subnr_[start_+lijnpos];
											 nr_=0; 
											 goto endsr;
										 }
										 break;
			default      : break;
    }
  }
 
endsr:;
	copy(buf750,s(52,1),fldlen(52,0));
  return subgrpnr_;
}

static DisplayExtraFuncties(stu_)
int16 stu_;
{
	int z,k,key,vt_,hz_;
	char buf1000_[1000],postnm_[20];

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
			case 10013 : fasinit(27);*u(27,2)=*u(25,2)-366;/* 2 jaar terug */
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

		if (stu_ == 2) {
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

static DisplayLeveradres(stu_)
int16 stu_;
{
  int z,k,key,curs=2,dcurs_;
	 
	
	FOREVER{
		redo:;
		scrget(1,275);z=1;
		scrofld(z++,stu_,3,-1);
 		for(k=143;k<=146;k++) scrfld(z++,stu_,k);
		dcurs_=curs; if(only_dsp) dcurs_=-1;
		key=scrupd(dcurs_,0x1);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
	}
}


  
static scrbfld(z,stu_,fld_,stubuf_,fl_output_)
int16 z,stu_,fld_;
char *stubuf_;
{
  char *pvar_,*pdum_;

  if(fieldspc(stu_,fld_,&pdum_,fmt)>0){
    if(fl_output_) fmt[1]&=0xBF;
    pvar_=stubuf_+ (s(stu_,fld_)-s(stu_,1));
    scrifld(z,fmt,pvar_);
  }
}
 
static uint16 hashbuf(buf_,len_)
char *buf_;
int16 len_;
{
  char *ps;
  int16 k;
  uint16 fuval=0;
					
  k=len_;ps=buf_;
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
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
#if FLAGCRA
		if(*u(25,4)!=110 && key==15 && only_dsp){only_dsp=NO;goto redo;}
#else
    if(key==15 && only_dsp && CheckPw(1,PwUpdNr,0)){
				only_dsp=NO;
#if FLAGGBL
	      if(only_dsp){sys3892=6; suppr_wi=YES;}
	      else {sys3892=0; suppr_wi=NO;}
#endif
				goto redo;
			}			
#endif
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

//static art_verp()
//{
//  int16 k,curs=6,key,z;
//									
//  FOREVER{
//    redo_a:
//    scrget(2,286); z=1;
//    scrofld(z++,6,2,-1); scrofld(z++,6,3,-1);
//    scrfld(z++,6,31);scrfld(z++,6,pnr_kbak);scrfld(z++,6,70);
//    for(k=0;k<5;k++){
//      scrfld(z++,6,200+k*5);
//      scrfld(z++,6,201+k*5);
//      scrfld(z++,6,202+k*5);
//      scrfld(z++,6,203+k*5);
//    }
//    scrfld(z++,6,pnr_kstk);scrfld(z++,6,71);
//    key=scrupd(curs,0x02A1);curs=6;
//    if(key==106) break;
//    for(k=0;k<5;k++) {
//      if(*s(6,200+k*5) && *i(6,201+k*5)==0) {curs=6+k*4;errnum=34;goto redo_a;}
//      if(*i(6,201+k*5)>*f(6,31)) {curs=7+k*4;errnum=34;goto redo_a;}
//    }
//    if(key==110 && fldlen(6,70)){
//      ean13c(s(6,70));
//      ean13c(s(6,71));
//      for(k=0;k<5;k++) ean13c(s(6,203+k*5));
//    }
//    if(key==108 || key==101) key=107;
//    if(key==106 || key==107) break;
//  }
//  return key;
//}

static artik_bis(mode)
int16 mode;
{
  int16 k,curs=3,key,z,dcurs_,kleur_,searchmode_;
 
  FOREVER{
    redo_a:
    scrget(2,20); z=1;
		if(fldlen(6,70)){ // zoek met barcodescanner ($ ervoor zetten)
  		scraddfield(300,0,0,0xAA);
  		scrifld(300,fm_os59,"|");
		}
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
#if FLAGGOU
    for(k=27;k<=48;k++) scrfld(z++,6,k);
    if(fldlen(6,50)){scrfld(-z,6,49);z++;}
    else scrfld(z++,2,49);
    for(k=50;k<=79;k++) scrfld(z++,6,k);
#else
    for(k=27;k<=79;k++){
			if(BlokkeerStock && (k==33 || (k>=53 && k<=60))) scrofld(z++,6,k,-1);
			else scrfld(z++,6,k);
			if(k==33 && fldlen(6,k) && fldlen(8,1)) scraddpicto(4,z-1,0,0,2,1,112,0,4,"Toon netto-stock"); 
			if(k==40 && fldlen(6,k)) scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
			if(k==52 && fldlen(6,k)) scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
  		if(k==39 && fldlen(6,k) && fldlen(3,2)) scraddpicto(3,z-1,0,0,2,1,64,0,4,"Toon rekening"); 
		}
#endif
    for(k=81;k<101;k++) scrfld(z++,6,k);
		if(fldlen(6,70) && fldlen(64,0) && *u(6,1)){ // bijkomende barcodes
			kleur_=3;
			fasinit(64);*u(64,3)=*u(6,1);
			if(faskeyi(64,2,1)==0){if(*u(64,3)==*u(6,1)) kleur_=4;} // er zijn extra barcodes
			scraddpicto(10,3+70-27,0,0,2,1,101,0,kleur_,"Extra barcodes"); 
		}
    dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0x03F9);curs=3;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001 || key==5002){
			k=40; if(key==5002) k=52;
			searchmode_=0;fasinit(3);
			if(*l(6,k)){*s(3,3)='.'; grb_deco(s(3,3)+1,l(6,k));}
			else searchmode_=98;
			if(search(3,searchmode_)==0) *l(6,k)=*l(3,2);
		}
		if(key==5003) DisplayVerkoopRekening(); // toon rekening ahv extentie
		if(key==5004) DisplayNettoStock(); // toon ook de aantallen op bons
		if(key==5010) DisplayExtraBarcodes();
#if FLAGCRA
		if(*u(25,4)!=110 && key==15 && only_dsp){only_dsp=NO;goto redo_a;}
#else
    if(key==15 && only_dsp && CheckPw(1,PwUpdNr,0)){
			only_dsp=NO;
#if FLAGGBL
	    if(only_dsp){sys3892=6; suppr_wi=YES;}
	    else {sys3892=0; suppr_wi=NO;}
#endif
			goto redo_a;
		}			
#endif
		if(key==104) {BlokkeerStock=NO; goto redo_a;}
    if(key==106) break;
    for(k=0;k<8;k++) if(*f(6,28)==btw_pct[k]) break;
    if(k==8) {curs=3;errnum=34;goto redo_a;}
#if FLAGGOU
    if(fldlen(6,49)){ // GOU
      k=*u(6,49)-1;
      if(k<0 || k>14) zero(s(6,50),fldlen(6,50));
      else copy(&kw_groep[k],s(6,50),fldlen(6,50));
    }
#endif
#if FLAGHDY
		if(*s(6,43)){ // 
      for(k=0;k<20;k++) if(cmpstr(s(6,43),fost_stu[k].code,3)==0) break;
      if(k>=20) {curs=43-27+2;errnum=34;goto redo_a;}
    }
#endif
    if(key==18){curs=fldcurs+1;goto redo_a;}
    if(key==110 && fldlen(6,70)){
      ean13c(s(6,70));
      ean13c(s(6,71));
    }
    if(key==105 && fldlen(66,1)) {stock_loc();goto redo_a;}
    if(key==112 && *u(stu,1)) {dsp_info(); goto redo_a;}
    if(key!=108 && key!=101 && key!=109) goto redo_a;
    else break;
  }
  return key;
}

static DisplayNettoStock()
{
	int k,mode_,p_s,z,key;
	float bonstock_=0,beststock_=0,netstock_=0,qlv_,verp_factor_;
	char bf8_[1000],bf58_[1000];


	if(fldlen(8,1)==0) goto endsr;
	fileopen(8);
	copy(s(8,1),bf8_,fldlen(8,0));copy(s(58,1),bf58_,fldlen(58,0));
	fasinit(58);*u(58,14)=*u(6,1);mode_=1;
	FOREVER{
		next58:;
		if(faskeyi(58,2,mode_)) break; mode_=2;
		if(*u(58,14)!=*pu_6_1) break;
		fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
#if FLAGALS
		if(*u(8,43)) goto next58; // geen filiaal 
#endif
		if(fldlen(8,36) && *u(8,36)==10){ // bestelling
			verp_factor_=1.; if(fldlen(58,87) && *f(58,87)>0 && *f(6,31)>0 && *f(58,87)!=*f(6,31)) verp_factor_=*f(58,87)/ *f(6,31); // converteren van verpakking leverancier naar artikel
    	qlv_=*f(58,31)*verp_factor_;
		  if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
			  beststock_+=qlv_;
		}
		else if(fldlen(8,36)==0 || *u(8,36)==0){ // leverbon
    	qlv_=*f(58,31);
		  if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
			  bonstock_-=qlv_;
		}
	}
	redo:;
	netstock_=*f(6,33)+bonstock_;
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,5,29,3);
  scraddf(z++,8,5,0);scraddf(z++,8,15,2);
	scraddf(z++,10,5,0);scraddf(z++,10,20,2);
	scraddf(z++,11,5,0);scraddf(z++,11,20,2);
	scraddf(z++,12,20,0);
	scraddf(z++,13,5,0);scraddf(z++,13,20,2);
	scraddf(z++,15,5,0);scraddf(z++,15,27,2);
  scraddf(z++,23,1,8);
  z=1;
  scrifld(z++,VarTextFmt(22,0),"Berekening netto-stock");
  scrifld(z++,VarTextFmt(10,0),"Artikel :");scrfld(z++,6,3);
	scrifld(z++,VarTextFmt(15,0),"Artikelfiche  :");scrifld(z++,fm_of6_2,f(6,33));
	scrifld(z++,VarTextFmt(15,0),"Aantal op bons:");scrifld(z++,fm_of6_2,&bonstock_); if(bonstock_) scraddpicto(1,z-1,1,0,2,1,112,0,4,"Toon klanten"); 
	scrifld(z++,VarTextFmt(10,0),"---------");
	scrifld(z++,VarTextFmt(15,0),"Netto stock . :");scrifld(z++,fm_of6_2,&netstock_);
	scrifld(z++,VarTextFmt(22,0),"Aantal in bestelling:");scrifld(z++,fm_of6_2,&beststock_); if(beststock_ && ovltest(255)) scraddpicto(2,z-1,1,0,2,1,112,0,4,"Toon leveranciers"); 
  scrifld(z++,VarTextFmt(10,0)," F1 terug ");
  key=scrupd(-1,0x81);
	if ((key/0x100)==1) key=(key&0xFF)+5000;
  if(key==5001){DisplayBonsWithThisArt(0); goto redo;}
	if(key==5002){DisplayBonsWithThisArt(1); goto redo;}
	copy(bf8_,s(8,1),fldlen(8,0));copy(bf58_,s(58,1),fldlen(58,0));
  endsr:;
}

static DisplayBonsWithThisArt(KLmode_) // 0 = klanten, 1=leveranciers
{
  int16 j,key,z,d_lin_scr_=19,start_,stu_;
	uint16 brecs_[200],max_,mode_;
	float qlv_,verp_factor_;
	
	if(KLmode_==1) stu_=1; else stu_=2;
	fileopen(8);
  fasinit(58);*u(58,14)=*u(6,1);mode_=1;
	zero((char *)brecs_,sizeof brecs_); max_=0;
  FOREVER{
    next:;
    if(faskeyi(58,2,mode_)) break; mode_=2;
    if(*u(58,14)!=*u(6,1)) break;
    fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
		if(KLmode_==1){ // lev-bestelbons
			if(fldlen(8,36)==0 || *u(8,36)!=10) goto next;	
		}
		else{ // enkel leveringsbons
		  if(fldlen(8,36) && *u(8,36) && *u(8,36)!=180) goto next; // enkel leveringsbons
		}
		brecs_[max_++]=*u(58,1); if(max_>=200) break;
  }

  scrnum=0;start_=0;
  FOREVER{
    redo:
    scrnum=0;scrget(2,383);z=1;
		scrofld(z++,6,3,-1);
    for(j=start_;j<(start_+d_lin_scr_);j++){
      if(j>=max_) break;
      j++; scrifld(z++,fm_ou3,&j); j--;
			fasinit(58);*u(58,1)=brecs_[j]; fasgeti(58);
			fasinit(8);*u(8,1)=*u(58,2); fasgeti(8);
			if(*u(8,3)==0){
				*u(8,3)=1; fasupd(8);}
			fasinit(stu_);*u(stu_,1)=*u(8,3); fasgeti(stu_);
			verp_factor_=1.; 
			if(KLmode_==1){ // leveranciers
			  if(fldlen(58,87) && *f(58,87)>0 && *f(6,31)>0 && *f(58,87)!=*f(6,31)) verp_factor_=*f(58,87)/ *f(6,31); // converteren van verpakking leverancier naar artikel
			}
    	qlv_=*f(58,31)*verp_factor_;

			if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)!=0 && *s(58,16)!='*') qlv_/=*f(58,63);
			scrofld(z++,8,8,-1);
			scrofld(z++,stu_,3,-1);
			scrifld(z++,fm_of6_2,&qlv_);
    }
    key=scrupd(-1,0x7);
    if(key==101 || key==111) break;
    if(key==102) start_-=d_lin_scr_;
    if(key==103){
      start_+=d_lin_scr_;
      if(start_>(max_-d_lin_scr_)) start_=max_-d_lin_scr_;
    }
    if(start_<0) start_=0;
  }
	endsr:;
}



static DisplayVerkoopRekening()
{
  int16 z,g,gg,kk,b3604,b3606;
  long rekenc,grb_notf,grb_leeggoed;
  char reken[10],b3598[6];

	fileopen(3);
	sysget(3598,6,b3598);
  sysget(3604,2,&b3604);
  sysget(3606,2,&b3606);
	sysget(3636,4,&grb_notf);
	sysget(836,4,&grb_leeggoed);
	if(*i(6,9)==99) rekenc=grb_leeggoed;
	else{
    zero(reken,sizeof reken);
    copy(b3598,reken,6);
#if FLAGPED                             /* afhaalvergoeding op 74-rekening */
    if(*s(6,39)=='9') reken[1]='4';
#endif
		for(g=0;g<10;g++) if(reken[g]=='\0') break;
		if(fldlen(2,25)){
			if(*s(2,25)=='\0') *s(2,25)='0';
			copy(s(2,25),&reken[g],fldlen(2,25));
			for(g=0;g<10;g++) if(reken[g]=='\0') break;
		}
		copy(s(6,39),&reken[g],fldlen(6,39));
		for(g=0;g<10;g++) if(reken[g]=='\0') break;
		if(b3604){
			stcli_d(&reken[g],(long)*i(6,9),b3604,0);
			g+=b3604;
		}
		if(b3606){
			kk=*f(6,28);gg=*f(6,28)*10 - kk*10;/* gg = decimaal */
	   	stcli_d(&reken[g],(long)kk,2,0);
			if(gg && b3606==2) stcli_d(&reken[g]+2,(long)gg,1,0);/* decimaal */
		}
//#if FLAGSHN
//		if(*f(6,28)==0 && *s(6,39)=='9') copy("460000",reken,7); // eigen cadeaubon
//#endif
		grb_comp(reken,&rekenc);
	}
  fasinit(3);*l(3,2)=rekenc; errnum=faskeyi(3,1,0);
	if(errnum){
		fasinit(3);*l(3,2)=grb_notf;faskeyi(3,1,0);
	}
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,5,15,3);
  scraddf(z++,8,5,0);scraddf(z++,8,23,2);scraddf(z++,8,34,2);
  scraddf(z++,23,1,8);
  z=1;
  scrifld(z++,VarTextFmt(43,0),"Controle grootboekrekening voor dit artikel");
  scrifld(z++,VarTextFmt(17,0),"Verkooprekening :");scrfld(z++,3,2);scrfld(z++,3,3);
  scrifld(z++,VarTextFmt(10,0)," F1 terug ");
  scrupd(-1,0x81);
}

static DisplayExtraBarcodes()
{
  int16 curs=1,j,key,k,z,mode_;
  struct {
		long rec64;
		long rec6;
		char barcode[15];
		int  soort;
		char dsp_soort;
	} tb_ebarc[10];

	memset((char *)tb_ebarc,0,sizeof tb_ebarc);
	  
	fasinit(64);*u(64,3)=*u(6,1);mode_=1;
	for(k=0;k<10;k++){
		if(faskeyi(64,2,mode_)) break; mode_=2;
		if(*u(64,3)!=*u(6,1)) break;
		tb_ebarc[k].rec64=*l(64,1);
		copy(s(64,2),tb_ebarc[k].barcode,fldlen(64,2));
		tb_ebarc[k].soort=*u(64,5);
		if(tb_ebarc[k].soort==1) tb_ebarc[k].dsp_soort='J'; else tb_ebarc[k].dsp_soort='N';
	}
  scrnum=0;
  FOREVER{
    redo:
    scrget(2,362);z=1;
    scrofld(z++,6,3,-1);
		scrfld(z++,6,70);
		scrfld(z++,6,71);
    for(k=0;k<10;k++){
      fmt_get(64,2);scrifld(z++,fmt,&tb_ebarc[k].barcode[0]);
      scrifld(z++,fm_uJN,&tb_ebarc[k].dsp_soort);
		}
    key=scrupd(curs,0xA0);curs=1;
    if(key==106) goto endsr;
    for(k=0;k<10;k++){
			if(tb_ebarc[k].barcode[0]){// barcodes controleren 
				if(cmpstr(s(6,70),tb_ebarc[k].barcode,fldlen(6,70))==0){errnum=31;curs=4+k*2;goto redo;}
				if(cmpstr(s(6,71),tb_ebarc[k].barcode,fldlen(6,71))==0){errnum=31;curs=4+k*2;goto redo;}
				for(j=k+1;j<10;j++) { // checken in eigen tabel
					if(cmpstr(tb_ebarc[j].barcode,tb_ebarc[k].barcode,sizeof tb_ebarc[0].barcode)==0){errnum=31;curs=4+k*2;goto redo;}
				}
				fasinit(64); copy(tb_ebarc[k].barcode,s(64,2),fldlen(64,2));mode_=1;
				FOREVER{ // checken op ander artikel
					if(faskeyi(64,1,mode_)) break; mode_=2;
					if(cmpstr(s(64,2),tb_ebarc[k].barcode,fldlen(64,2))==0){
						if(*u(64,3)!=*u(6,1)){errnum=31;curs=4+k*2;goto redo;}
					} else break;
				}
			}
		}
		if(key==108)break;
  }

  for(k=0;k<10;k++){
		if(tb_ebarc[k].barcode[0]){
			fasinit(64);
			*l(64,1)=tb_ebarc[k].rec64;
			copy(tb_ebarc[k].barcode,s(64,2),fldlen(64,2));
			*u(64,3)=*u(6,1);
			if(tb_ebarc[k].dsp_soort=='J') *u(64,5)=1;
			if(tb_ebarc[k].rec64) fasupd(64); else fasadd(64);
		}
		else{
			if(tb_ebarc[k].rec64){fasinit(64);*l(64,1)=tb_ebarc[k].rec64; faskill(64);}
		}
	}
   
  endsr:;
}

static DisplayDeelVerpakkingen()
{
  int16 curs=1,j,key,k,z,mode_,prbaknr_,prstuknr_,nr_,cursupd_;
	char buf750_[750];
	uint16 MastRec,rec_;
	double factor_;

  struct {
		long artrec;
		float  q_verpakking;
		char omschrijving[40];
		float apnet;
		float kassapr;
		char lgcode[10];
	} tb_verp[10]; // momenteel max. 10 !

	BlokVerpakkingDisplay=YES; // blokkeren om via fichupd opnieuw in deze lus te komen
	prbaknr_=0;prstuknr_=0;
	for(k=0;k<6;k++){
    nr_=sys3896[k]-'0';
    if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])) nr_=PrNrs[nr_];
    else nr_=0;
		if(nr_) {if(prbaknr_==0) prbaknr_=nr_; prstuknr_=nr_;}
	}
	if(*f(6,31)==0) *f(6,31)=1;
	MastRec=*u(6,1); copy(s(6,1),MasterArt,fldlen(6,0));
	if(fldlen(66,1)) copy(s(66,1),buf750_,fldlen(66,0));
	memset((char *)tb_verp,0,sizeof tb_verp);
	fasinit(6);*u(6,102)=MastRec;mode_=1;k=0;
	FOREVER{
		if(faskeyi(6,15,mode_)) break; mode_=2;
		if(*u(6,102)!=MastRec) break;
		if(k<10){
  		tb_verp[k].artrec=*u(6,1);
  		tb_verp[k].q_verpakking=*f(6,31);
		  copy(s(6,3),tb_verp[k].omschrijving,fldlen(6,3));
			tb_verp[k].apnet=*f(6,18);
		  tb_verp[k].kassapr=*f(6,prbaknr_);
		  copy(s(6,41),tb_verp[k].lgcode,fldlen(6,41));
			k++;
		}
	}
	copy(MasterArt,s(6,1),fldlen(6,0));
  scrnum=0;
  FOREVER{
    redo:
    scrnum=0;scrget(2,370);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0219C");

		scrofld(z++,6,3,-1);
		scrofld(z++,6,31,-1);
		scrofld(z++,6,prbaknr_,-1);
		scrofld(z++,6,41,-1); 
		cursupd_=NO;
    for(k=0;k<10;k++){
			k++; scrifld(z++,fm_ou2,&k); k--;
			fmt_get(6,3);if(tb_verp[k].artrec) fmt[1]&=0xBF;scrifld(z++,fmt,&tb_verp[k].omschrijving[0]);
			fmt_get(6,31);if(tb_verp[k].artrec) fmt[1]&=0xBF;scrifld(z++,fmt,&tb_verp[k].q_verpakking);
			fmt_get(6,prbaknr_);if(tb_verp[k].artrec) fmt[1]&=0xBF;scrifld(z++,fmt,&tb_verp[k].kassapr);
			fmt_get(6,41);if(tb_verp[k].artrec) fmt[1]&=0xBF;scrifld(z++,fmt,&tb_verp[k].lgcode[0]);
			if(tb_verp[k].artrec==0){
				cursupd_=YES;
				scraddpicto(1+k,z-1,9,0,2,1,112,0,4,"Zoek artikel"); 
				scraddpicto(11+k,z-1,11,0,2,1,36,0,4,"Nieuw artikel"); 
			}
			else{
				scraddpicto(21+k,z-1,13,0,2,1,64,0,4,"Aanpassen"); 
				scraddpicto(31+k,z-1,15,0,2,1,540,0,0,"Schrap koppeling"); 
			}
  	}
		if(cursupd_==NO) curs=-1;
    key=scrupd(curs,0x1);curs=1;
    if(key==101) break;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
		if(key>=5001 && key<=5010){ // zoek
			k=key-5001;
			fasinit(6);copy(tb_verp[k].omschrijving,s(6,3),fldlen(6,3));
			if(search(6,98)) errnum=39;
			if(errnum==0 && (*u(6,102) || *u(6,1)==MastRec)  ) errnum=63; // mag geen deelverpakking zijn of zichzelf
			if(errnum==0){// mag geen hoofdverpakking zijn 
				rec_=*u(6,1);
				fasinit(6);*u(6,102)=rec_; 
				if(faskeyi(6,15,0)==0) errnum=63;
				else{
					fasinit(6);*u(6,1)=rec_; fasgeti(6);
					if(fldlen(6,198)) *u(6,198)=procid;
					if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
					*u(6,102)=MastRec;fasupd(6);
				}
			}
			if(errnum==0){
  			tb_verp[k].artrec=*u(6,1);
    		tb_verp[k].q_verpakking=*f(6,31);
  		  copy(s(6,3),tb_verp[k].omschrijving,fldlen(6,3));
  			tb_verp[k].apnet=*f(6,18);
  		  tb_verp[k].kassapr=*f(6,prbaknr_);
	  	  copy(s(6,41),tb_verp[k].lgcode,fldlen(6,41));
			} 
			copy(MasterArt,s(6,1),fldlen(6,0));
			goto redo;
		}
		if(key>=5011 && key<=5020){ // nieuw
			k=key-5011;
			if(tb_verp[k].q_verpakking<1){errnum=38;curs=7+k*5; goto redo;}
			if(tb_verp[k].lgcode[0]=='\0' && tb_verp[k].q_verpakking!=*(float *)pMST(6,31) && *pMST(6,41)){errnum=38;curs=9+k*5; goto redo;} 
			copy(MasterArt,s(6,1),fldlen(6,0)); factor_=tb_verp[k].q_verpakking/ *(float *)pMST(6,31);
			zero(s(6,1),s(6,3)-s(6,1));
			zero(s(6,8),fldlen(6,8));
			zero(s(6,33),fldlen(6,33));
			zero(s(6,46),s(6,51)-s(6,46));
			zero(s(6,63),s(6,65)-s(6,63));
			zero(s(6,53),s(6,74)-s(6,53));
			zero(s(6,102),fldlen(6,102));
			zero(s(6,105),s(6,150)-s(6,105));
			if(tb_verp[k].omschrijving[0]) copy(tb_verp[k].omschrijving,s(6,3),fldlen(6,3));
			*u(6,102)=MastRec;
			*f(6,31)=tb_verp[k].q_verpakking;
			for(j=12;j<21;j++){
				if(j>=13 && j<=16) continue;
				if(j==19 && sys3652==2 && fldlen(6,j)) *f(6,j)=*(float *)pMST(6,j); // handingkost in % volledig overnemen
			  else if(fldlen(6,j)) *f(6,j)=valu_cnv("EUR","EUR",(double)(*(float *)pMST(6,j)*factor_),(double)(0.001));
			}
			for(j=0;j<10;j++){
				if(fldlen(6,PrNrs[j])==0) continue;
				if(PrNrs[j]==prbaknr_ && tb_verp[k].kassapr) *f(6,prbaknr_)=tb_verp[k].kassapr;
				else if(stuksprx[j]=='J' /* PrNrs[j]==prstuknr_ */ && *(float *)pMST(6,31)>1.) *f(6,PrNrs[j])=*(float *)pMST(6,PrNrs[j]); // stuksprijs overnemen
				else 	*f(6,PrNrs[j])=*(float *)pMST(6,PrNrs[j]) * factor_;
				*f(6,PrNrs[j])=valu_cnv("EUR","EUR",(double)(*f(6,PrNrs[j])),(double)(sys2830[j]));
			}
			if(fldlen(6,30)) *f(6,30)=valu_cnv("EUR","EUR",(double)(*(float *)pMST(6,30)*factor_),(double)(0.001));
			if(fldlen(6,37)) *f(6,37)=*(float *)pMST(6,37)*factor_;
			if(fldlen(6,38)) *f(6,38)=*(float *)pMST(6,38)*factor_;
			if(tb_verp[k].lgcode[0]) copy(tb_verp[k].lgcode,s(6,41),fldlen(6,41));
			if(fldlen(6,42)) *f(6,42)=1; 
			if(fldlen(66,1)) fasinit(66);
			fichupd(3);
      if(*u(6,1)){
   			tb_verp[k].artrec=*u(6,1);
    		tb_verp[k].q_verpakking=*f(6,31);
  		  copy(s(6,3),tb_verp[k].omschrijving,fldlen(6,3));
  			tb_verp[k].apnet=*f(6,18);
  		  tb_verp[k].kassapr=*f(6,prbaknr_);
	  	  copy(s(6,41),tb_verp[k].lgcode,fldlen(6,41));
			} else errnum=39;
			copy(MasterArt,s(6,1),fldlen(6,0));
			goto redo;
		}
		if(key>=5021 && key<=5030){ // aanpassen
			k=key-5021;
			*u(6,1)=tb_verp[k].artrec;fasgeti(6);
			if(fldlen(66,1)) {fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);}
			fichupd(1);
  		tb_verp[k].artrec=*u(6,1);
    	tb_verp[k].q_verpakking=*f(6,31);
  		copy(s(6,3),tb_verp[k].omschrijving,fldlen(6,3));
  		tb_verp[k].apnet=*f(6,18);
  		tb_verp[k].kassapr=*f(6,prbaknr_);
	  	copy(s(6,41),tb_verp[k].lgcode,fldlen(6,41));
			copy(MasterArt,s(6,1),fldlen(6,0));
			goto redo;
		}
		if(key>=5031 && key<=5040){ // schrappen
			k=key-5031;
			fasinit(6);*u(6,1)=tb_verp[k].artrec;fasgeti(6);
			if(fldlen(6,198)) *u(6,198)=procid;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			*u(6,102)=0;fasupd(6);
			zero((char *)&tb_verp[k],sizeof tb_verp[0]);
			copy(MasterArt,s(6,1),fldlen(6,0));
			goto redo;
		}
		if(key==108)break;
  }
	copy(MasterArt,s(6,1),fldlen(6,0));
	if(fldlen(66,1)) copy(buf750_,s(66,1),fldlen(66,0));
	fasinit(1);*u(1,1)=*u(6,7);fasgeti(1);
	fasinit(52);*u(52,1)=*u(6,9);fasgeti(52);
endsr:;
	BlokVerpakkingDisplay=NO;
}

static DisplayKoppeling()
{
  int16 key,z;

	copy(s(6,1),MasterArt,fldlen(6,0));
	fasinit(6);*u(6,1)=*(uint16 *)pMST(6,102);fasgeti(6);

  scraddf(-1,0,0,0);z=1;
  scraddf(z,8,5,0);scrifld(z++,fm_os79,"Dit artikel is een deelverpakking van :");
	scraddf(z,10, 25,2);scrfld(z++,6,3);
	scraddf(z,23,1,8);scrifld(z++,VarTextFmt(10,0)," F1 terug ");
	scraddf(z,23,50,8);scrifld(z++,VarTextFmt(28,0)," F6 verbreek deze koppeling ");
  key=scrupd(-1,0x21);
	copy(MasterArt,s(6,1),fldlen(6,0));
	if(key==106) *u(6,102)=0;
endsr:;
}

static char *pMST(int16 stu_, int16 fld_)
{
  int16 k;
  char *ps_;
  k=s(6,fld_)-s(6,1);
  ps_=MasterArt+k;
  return ps_;
}


static dsp_i_flag()
{

  if(fldlen(22,0)==0) goto endsr;

  fasinit(22);*u(22,2)=stu;*u(22,3)=*u(stu,1);
  if(faskeyi(22,1,1)) goto endsr;
  if(*u(22,2)!=stu) goto endsr;
  if(*u(22,3)!=*u(stu,1)) goto endsr;

  if(stu==6) scraddf(119,22,78,7); else scraddf(119,23,78,7);
	scrifld(119,fm_os2,"IN");
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
#if FLAGWYN // || FLAGPCQ // nieuwe klantcode steeds 50000
	if(stu==2 && *s(stu,2)=='\0') *s(2,2)='5';
#endif
#if FLAGCRL// nieuwe klantcode steeds 6000
	if(stu==2 && *s(stu,2)=='\0') *s(2,2)='7';
#endif
#if FLAGNEY  // nieuwe klantcode steeds 90000
	if(stu==2 && *s(stu,2)=='\0') *s(2,2)='9';
#endif
#if FLAGVLO || FLAGSLB // nieuwe klantcode steeds 9000
	if(stu==2 && *s(stu,2)=='\0') *s(2,2)='9';
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
 
static ean13c(p)                                           /* vers. 00:01 25/02/94 */
char *p;
{
  int16 k, sum;
									
  for (k=0; k<13; k++) {
    if (*(p+k)==0) return YES;
  }
  sum=0;
  for (k=0; k<6; k++) {
    sum+=((*p-'0')+3*(*(p+1)-'0'));
    p+=2;
  }
  *p='0'+(10-(sum%10))%10;
  return NO;
}

 
static fill_dfprx()
{
 
  float pr_, btw_, q_stuks;
  int16 g,k,fld_,t_ap_,max_vp_;
  char *ptov;
									
	max_vp_=10; if(fldlen(6,PrNrs[6])==0 || fldlen(52,22)<20 || fldlen(52,30)==0) max_vp_=6; 
  for(k=0;k<max_vp_;k++) if(fldlen(6,PrNrs[k]) && *f(6,PrNrs[k])==0) break;
  if(k>=max_vp_) goto endsr;
  calcnet(0);
  q_stuks=0; btw_=*f(6,28);
  if(fldlen(6,31)) q_stuks=*f(6,31);
  if(q_stuks==0) q_stuks=1;
  t_ap_=18; if(sys3586==2) t_ap_=12;

  copy(s(6,1),selp_bf[0],fldlen(6,0));
	if(fldlen(6,103)){fasinit(52);*u(52,1)=*u(6,9);if(*u(52,1)) fasgeti(52);}
  g=0; for(k=0;k<fldlen(52,22);k++) g+=*(calctype+k);
  if(g==0) copy(CALCDEF,calctype,fldlen(52,22));
  fasinit(6);
  *f(6,18)=100;*f(6,12)=100;
  for(g=0;g<max_vp_;g++){
    ptov=calctype+1+g*2;fld_=0;
    if(*ptov=='B') fld_=12;
    else if(*ptov=='N') fld_=18;
    else if(*ptov>='0' && *ptov<='8') fld_=PrNrs[*ptov-'0'];
#if FLAGTOL // indien geen w%, dan prijs leeglaten
		if(*f(6,PrNrs[g])==0 && *f(52,2+g*2)==0) fld_=0;
#endif
    if(fld_ && fld_<(PrNrs[g])){
			if(g<6) *f(6,PrNrs[g])=*f(6,fld_)*(1.+*f(52,2+g*2)/100.);
			else *f(6,PrNrs[g])=*f(6,fld_)*(1.+*f(52,30+(g-6)*2)/100.);
		}
    else *f(6,PrNrs[g])=0;
    if(stuksprx[g]=='J') *f(6,PrNrs[g])/=q_stuks;
#if FLAGTOL // indien geen w%, dan prijs leeglaten
		if((fld_==12 || fld_==18) && *f(52,2+g*2)==0) {
			*f(6,PrNrs[g])=0;
		}
#endif
  }
  calcnet(0);
  copy(selp_bf[0],s(6,1),fldlen(6,0));
  for(g=0;g<max_vp_;g++){
    if(*f(6,PrNrs[g])==0){
      pr_=*f(6,t_ap_);
      pr_+=*f(6,t_ap_) * net_winst[g]/100.;
      if(sys3894 & 1<<g) pr_=pr_* (1.+btw_/100.);
#if FLAGGOU
      *f(6,PrNrs[g])=valu_cnv("EUR","EUR",(double)(pr_),(double)(*d(52,28))); // GOU
#else
      *f(6,PrNrs[g])=valu_cnv("EUR","EUR",(double)(pr_),(double)(sys2830[g]));
#endif
#if FLAGTOL // indien geen w%, dan prijs leeglaten
  		if(net_winst[g]==0) *f(6,PrNrs[g])=0;
#endif
    }
  }
  calcnet(0);
  endsr:;
 
}

static calcnet(pr_offset_)
int pr_offset_;
{
  int16 k,t_ap_,prstu_;
  float accijns_,net_,q_stuks,bd_,bd_deler_,apbd_;
									
  t_ap_=18; if(sys3586==2) t_ap_=12;
  if(*f(6,18+pr_offset_)) goto calc_wpct;
  net_=*f(6,12+pr_offset_);
  if(fldlen(6,13+pr_offset_)) net_=valu_cnv(s(6,13+pr_offset_),def_munt,(double)net_,(double)0.01);
  if(fldlen(6,30+pr_offset_)) accijns_=*f(6,30+pr_offset_); else accijns_=0;
  net_-=accijns_;
  for(k=0;k<3;k++) if(fldlen(6,14+k+pr_offset_)) net_*=(100.-*f(6,14+k+pr_offset_))/100.;
  if(fldlen(6,17+pr_offset_)){
    bd_=*f(6,17+pr_offset_);
    if(fldlen(6,13+pr_offset_)) bd_=valu_cnv(s(6,13+pr_offset_),def_munt,(double)bd_,(double)0.01);
    net_-=bd_;
  }
	net_+=accijns_; 
	if(sys3652){ // afhaal en losvergoediong erbij tellen 
		if(fldlen(6,19+pr_offset_)) {
			if(sys3652==2) net_*=(100.+*f(6,19+pr_offset_))/100.;  // als %
			else net_+=*f(6,19+pr_offset_);
		}
//		if(fldlen(6,19+pr_offset_)) net_+=*f(6,19+pr_offset_);
		if(fldlen(6,20+pr_offset_)) net_+=*f(6,20+pr_offset_);
	}
  *f(6,18+pr_offset_)=net_;
  calc_wpct:;
  for(k=0;k<10;k++){
		prstu_=PrNrs[k]; if(pr_offset_) prstu_=PrNrs[k+10];
		if(fldlen(6,prstu_)==0) {net_winst[k]=0; continue;}
    bd_deler_=*f(6,18+pr_offset_);
#if FLAGCRA
		if(k<3){ t_ap_=12;bd_deler_=*f(6,12+pr_offset_)+*f(6,19+pr_offset_);} // eerste 3 VP altijd tov BRUTO-aankoopprijs + hkost (Frans 26/11/18)
		else{ t_ap_=18; if(sys3586==2) t_ap_=12;}
#endif
    if(sys3586==2) bd_deler_=*f(6,12+pr_offset_);
    else if(sys3586==1) bd_deler_=*f(6,prstu_);
		apbd_=*f(6,t_ap_+pr_offset_);
#if FLAGCRA
		if(k<3) apbd_+=*f(6,19+pr_offset_);
#endif
		if(fldlen(6,prstu_) && apbd_ && (bd_deler_ || rev_prx_calc) ){
      q_stuks=0;
      if(stuksprx[k]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
      if(q_stuks==0) q_stuks=1;
      net_=*f(6,prstu_);
      if(rev_prx_calc){
				net_=apbd_* (1.+net_winst[k]/100);
				if(sys3586==1){/* marge */
					net_+=((net_-apbd_)*  net_/ apbd_) * net_winst[k]/100;
				}
				if(sys3894 & 1<<k) net_*=1.+*f(6,28)/100.;
				net_/=q_stuks;
#if FLAGGOU
				if(k<6) *f(6,21+k+pr_offset_)=valu_cnv("EUR","EUR",(double)(net_),(double)(*d(52,28))); // GOU
#else
        if(*f(6,prstu_) || net_winst[k]) *f(6,prstu_)=valu_cnv("EUR","EUR",(double)(net_),(double)(sys2830[k])); // winst%==0, enkel prijs invullen indien er al een prijs in staat
#endif
			}
			else{
				if(sys3894 & 1<<k) net_/=1.+*f(6,28)/100.;
				if(sys3586==1) bd_deler_=net_*q_stuks;/* correctie VP-prijs/stuk */
				net_winst[k]=((net_-(apbd_/q_stuks))/ (bd_deler_/q_stuks)) * 100.;
				if(*f(6,prstu_)==0) net_winst[k]=0;
      }
    }
    else net_winst[k]=0;
  }
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
#if FLAGCRA
	  if(*u(25,4)!=110 && key==15 && only_dsp){only_dsp=NO;goto redo;}
#else
    if(key==15 && only_dsp && CheckPw(1,PwUpdNr,0)){only_dsp=NO;goto redo;}
#endif
    if(key==108) break;
  }
}

static get_info(select_)
int16 select_;
{
  int16 k,mode_;
									
  ram_recl=fldlen(22,0) +2;                               /* + 2 bytes hash */
  max_line=(sizeof ram /ram_recl) -1;
  hash_len=0; dat_len=ram_recl-2;
  zeros(ram,sizeof ram);
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
    scrget(2,89);z=1;scraddpicto(3,0,76,0,4,2,105,1,7,"^!B0019B");
		if(fldlen(22,7)) scraddpicto(1,0,11,3,2,1,605,0,0,"Alarm"); 
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
		if(key==5003){curs=fldcurs;goto redo;}
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


static zoek_toer()
{
  int16 z,curs=1,key,q_elem_,j,k,mode_,smode_;
  uint16 inq_klt,rec_63[20];
 
  FOREVER{
    redo:;
    scrnum=0;scrget(1,5);z=1;
    scrifld(z++,fm_os20,"toer via klant"); scrchat(z-1,0x09);
    scrfld(z++,25,1);
    scrifld(z++,fm_os20,"op te zoeken");
    scrfld(z++,2,3);scraddpicto(z-1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    key=scrupd(curs,0x04C1); curs=4;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
  	smode_=0;	if(key==5001) smode_=98;
    if(key==101) {fasinit(63);return YES;}
    if(key==111) ovlexit(-1);
    if(search(2,smode_)) {curs=4;goto redo;}
    inq_klt=*u(2,1);q_elem_=fldlen(63,10)/2;
    fasinit(63);
    zero((char *)&rec_63[0],sizeof rec_63); mode_=1;
    for(k=0;k<17;k++){
      next_63:;
      if(faskeyi(63,2,mode_)) break;  mode_=2;

      for(j=0;j<q_elem_;j++){
	if(inq_klt==*(uint16 *)(s(63,10)+j*2)) break;
      }
      if(j<q_elem_) rec_63[k]=*u(63,1); else goto next_63;
    }

    if(k==0) {errnum=39;fasinit(63);goto redo;}
    if(k>1){
      FOREVER{
	scrnum=0;scrget(1,30);z=1;
	scrofld(z++,2,3,-1);
	for(j=0;j<17;j++){
	  if(rec_63[j]==0) break;
	  fasinit(63);*u(63,1)=rec_63[j];fasgeti(63);
	  j++;scrifld(z++,fm_ou3,&j); j--;
	  scrofld(z++,63,3,-1);
	}
	j=0;scrifld(36,fm_uu3,&j);
	key=scrupd(36,0xA0);
	if(key==106) goto redo;
	if(j>k)errnum=39;
	else if(j)break;
      }
      rec_63[0]=rec_63[j-1];
    }
    sta_found:;
    fasinit(63);*u(63,1)=rec_63[0];fasgetu(63);
    break;
  }
  return NO;
}

static copy_info()
{
  int16 k,key,mode_,smode_;
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
    scrfld(4,stu,3);scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    key=scrupd(4,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;
    if(key==111) ovlexit(-1);
  	smode_=0;	if(key==5001) smode_=98;
	  if(search(stu,smode_)) goto redo;
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
			if(str_[9]){copy("BE-",str_,3);btw_deco(&str_[3],(long *)pvar_,1);}
			else {copy("BE-0",str_,4);btw_deco(&str_[4],(long *)pvar_,1);}
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
  zeros(ram+ram_recl*lin_,ram_recl);
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
  zeros(ram+ram_recl*(max_line-1),ram_recl);
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
 
static uint16 chk_dblbtw()
{
  uint16 key,krec_,g,n,ok_=YES;
  long btwnr_,*p_btwnr_;

  if(fldlen(2,10)!=4) return YES;
  p_btwnr_=l(2,10);btwnr_=*p_btwnr_;krec_=*pu_2_1;
  btwnr_=*p_btwnr_ & 0xBFFFFFFF;
  if(btwnr_==000000000 || btwnr_==999999999) return YES;
  copy(s(2,1),buf1000,fldlen(2,0));
  fasinit(2); n=0;scrget(1,7);scrupd(-3,0);
  FOREVER{
    *pu_2_1=++n;
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
 
static fichkil()
{
  int16 key,k;
  uint16 rec__;

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
		if(stu==2){ // staat in kassaparameters 
  		for(k=0;k<10;k++) if(*u(2,1)==loc_klt[k]) {errnum=25;goto redo;}
		}
    if(stu<4 && fldlen(4,1)){
      rec__=*u(stu,1)+30000*(stu-1);
      if(fldlen(4,1) && fasopen(files[3].filname,0)==0){
	fasinit(4);
	*u(4,5)=rec__;
	if(faskeyi(4,4,2)==0){
	  if(*u(4,5)==rec__) {errnum=25;goto redo;}
	}
      }
      if(fldlen(5,1) && fasopen(files[4].filname,0)==0){
	fasinit(5);
	*u(5,2)=rec__;
	if(faskeyi(5,1,0)==0) {errnum=25;goto redo;}
      }
    }
		fasunlck(-2);
    if(stu==1 || stu==2 || stu==6) spec_kill(stu);
    else faskill(stu);
		fasunlck(-1);
#if 0
    if(stu==2 && fldlen(62,1) && *u(62,1)) faskill(62);
#endif
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
#if FLAGMAE
    z=kil_bew(z,stu,70,3); // plaatfiches
#endif
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
		z=kil_bew(z,stu,6,102); // koppeling deelverpakkingen wegdoen
    faskill(stu);
  }
	endsr:;
  scrifld(21,fm_os63,"             Druk F8 om verder te gaan ...");scrchat(22,2);
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
#if FLAGMAE
    case 70: scrifld(z++,fm_os63,"Schrappen nummerplaten  ...");
   					 prec_=u(70,nr_); break;
#endif
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
	if(bstu_==6 && mstu_==6 && nr_==102){ // koppeling wegdoen van deelverpakkingen
		if(*u(6,102)) goto endsr; // is zelf deelverpakking 
		fasinit(6);*u(6,102)=mrec_;mode_=1;
		FOREVER{
			if(faskeyi(6,15,mode_)) break; mode_=2;
			if(*u(6,102)!=mrec_) break;
			if(fldlen(6,198)) *u(6,198)=procid;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			*u(6,102)=0;fasupd(6);
			fasinit(6);*u(6,102)=mrec_;mode_=1;
		}
		fasinit(6);*u(6,1)=mrec_; fasgetu(6);
		goto endsr;
	}
	
	if((bstu_==91 || bstu_==16) && mstu_==6){ // historieken naar divers artikel zetten 
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
									 if(mstu_==6){ // historieken artikel naar divers artikel zetten 
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
#if FLAGMAE
				case 70: if(*prec_==mrec_){faskill(70);dcnt_++;}
					 break;
#endif
				case 86: if(*prec_==mrec_){faskill(86);dcnt_++;}
					 break;
		    case 91: if(*prec_==mrec_){// kasverkopen naar divers artikel zetten 
		  	           if(mstu_==6){*prec_=div_rec_;fasupd(91);}
						  	   else faskill(91);
	   					     dcnt_++;
							   }
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

static stock_loc()
{
  int16 z,k,key,dcurs_,curs=2;
  float tot_vk_=0,tot_ak_=0,q_stk_;
  float stock_[12][2];
							
  fmt_get(66,11); zero((char *)&stock_[0][0],sizeof stock_);
  q_stk_=*f(6,31); if(q_stk_<1) q_stk_=1;
  stock2stks(*f(6,33),q_stk_,&stock_[0][0],&stock_[0][1]);

  if(fldlen(6,57)) tot_vk_=*f(6,57);if(fldlen(6,53)) tot_ak_=*f(6,53);
  for(k=0;k<10;k++) {
    if(fldlen(66,11+k*15) && nm_loc[k][0]){
      stock2stks(*f(66,11+k*15),q_stk_,&stock_[k+1][0],&stock_[k+1][1]);
    }
    if(fldlen(66,14+k*15)) tot_ak_+=*f(66,14+k*15);
    if(fldlen(66,17+k*15)) tot_vk_+=*f(66,17+k*15);
  }
  zero(&stock_[11][0],sizeof stock_[11]);
  for(k=0;k<11;k++){stock_[11][0]+=stock_[k][0];stock_[11][1]+=stock_[k][1];}
 
  FOREVER{
    redo:;
    scrget(2,232); z=1;
    scrfld(z++,25,1);
    scrofld(z++,6,2,-1);scrofld(z++,6,3,-1);
    scrifld(z++,fm_os6,"DEPOT");
    scrifld(z++,fm_uf5_0,&stock_[0][0]);scrifld(z++,fm_uf3_0,&stock_[0][1]);
    if(fldlen(6,36)) scrifld(z++,fm_uf7_1,f(6,36)); else z++;
    if(fldlen(6,35)) scrifld(z++,fm_uf7_1,f(6,35)); else z++;
    if(fldlen(6,53)) scrifld(z++,fm_uf7_1,f(6,53)); else z++;
    if(fldlen(6,57)) scrifld(z++,fm_uf7_1,f(6,57)); else z++;
    scrfld(z++,6,48);
    scrfld(z++,6,29);

    for(k=0;k<10;k++){
      if(fldlen(66,11+k*15) && nm_loc[k][0]){
	scrifld(z++,fm_os6,&nm_loc[k]);
	scrifld(z++,fm_uf5_0,&stock_[k+1][0]);scrifld(z++,fm_uf3_0,&stock_[k+1][1]);
	scrifld(z++,fm_uf7_1,f(66,12+k*15));
	scrifld(z++,fm_uf7_1,f(66,13+k*15));
	scrifld(z++,fm_uf7_1,f(66,14+k*15));
/*    scrfld(z++,66,16+k*15); */
	scrifld(z++,fm_uf7_1,f(66,17+k*15));
	scrfld(z++,66,19+k*15);
	scrfld(z++,66,20+k*15);
      } else z+=9;
    }
    scrifld(z++,fm_of5_0,&stock_[11][0]);scrifld(z++,fm_of3_0,&stock_[11][1]);
    scrifld(z++,fm_of7_1,&tot_ak_);
    scrifld(z++,fm_of7_1,&tot_vk_);
    dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0xC0);
#if FLAGCRA
		if(*u(25,4)!=110 && key==15 && only_dsp){only_dsp=NO;goto redo;}
#else
    if(key==15 && only_dsp && CheckPw(1,PwUpdNr,0)){
			only_dsp=NO;
#if FLAGGBL
	    if(only_dsp){sys3892=6; suppr_wi=YES;}
	    else {sys3892=0; suppr_wi=NO;}
#endif
			goto redo;
		}
#endif
    if(key==106) break;
    zero(&stock_[11][0],sizeof stock_[11]);
    for(k=0;k<11;k++){stock_[11][0]+=stock_[k][0];stock_[11][1]+=stock_[k][1];}
    if(fldlen(6,57)) tot_vk_=*f(6,57);if(fldlen(6,53)) tot_ak_=*f(6,53);
    for(k=0;k<10;k++) {
      if(fldlen(66,14+k*15)) tot_ak_+=*f(66,14+k*15);
      if(fldlen(66,17+k*15)) tot_vk_+=*f(66,17+k*15);
    }
    if(key==108){
      stks2stock(f(6,33),q_stk_,stock_[0][0],stock_[0][1]);
      for(k=0;k<10;k++) {
	if(fldlen(66,11+k*15)){
	  stks2stock(f(66,11+k*15),q_stk_,stock_[k+1][0],stock_[k+1][1]);
	}
      }
      break;
    }

  }
}

static stock2stks(stock_,qst_,bak_,fls_)
float stock_,qst_,*bak_,*fls_;
{
  int16 neg_;
  neg_=NO; if(stock_<0){stock_=-stock_;neg_=YES;}
  if(qst_<1) qst_=1;
  *bak_=(long)(stock_); *fls_=0;
  if(qst_>1 && stock_>0){
    *fls_=(long)(((stock_- *bak_) * qst_)+0.49);
  } else *fls_=0;
  if(neg_){*bak_=-*bak_; *fls_=-*fls_;}
}
						
static stks2stock(stock_,qst_,bak_,fls_)
float *stock_,qst_,bak_,fls_;
{
  if(qst_<1) qst_=1;
  *stock_=bak_+ fls_/qst_;
}

#if FLAGOLH
dsp_stat()
{
  char fmt_aankw[30],fmt_verkw[30],fmt_stuks[30];
  int z,k,key;
  unsigned dagen,tot_dagen;
  float st_perdag,min_st,max_st,winst,*dummy,tot_stuks;
  float tot_aankw,tot_verkw,stuks,aankw,verkw,bd_f,bd_fve;
 
  fieldspc(6,106,&dummy,fmt_stuks); fmt_stuks[1]&=0xBF;
  fieldspc(6,107,&dummy,fmt_aankw); fmt_aankw[1]&=0xBF;
  fieldspc(6,108,&dummy,fmt_verkw); fmt_verkw[1]&=0xBF;
  FOREVER{
    scrget(2,84); z=1;
    if(fldlen(6,2)) scrofld(z++,6,2,16); else scrofld(z++,6,1,16);
    scrofld(z++,6,3,50);
    min_st=9999.999; max_st=0;
    tot_dagen=0;tot_stuks=0;tot_aankw=0;tot_verkw=0;
    for(k=0;k<14;k++){
      if(k<12){
	stuks=*f(6,106+k*4);
	aankw=*f(6,107+k*4);
	verkw=*f(6,108+k*4);
      }
      else if(k==12){
	stuks=*f(6,57);
	if(fldlen(6,34)) aankw=stuks* *f(6,34);
	else if(fldlen(6,18)) aankw=stuks* *f(6,18);
	else aankw=0;
	verkw=*f(6,58);
      }
      else if(k==13){
	stuks=tot_stuks;
	aankw=tot_aankw;
	verkw=tot_verkw;
	dagen=tot_dagen;
      }
      if(k<13){
	scrifld(z++,fm_odat,&stat_dat[k]);
	scrifld(z++,fm_odat,&stat_dat[k+1]);
	if(stat_dat[k+1]<stat_dat[k]) {z+=6; goto next;}
	dagen=stat_dat[k+1]-stat_dat[k];
	if(stat_dat[k]==0) dagen=0;
      }
      scrifld(z++,fm_ou4,&dagen);
      st_perdag=0;
      if(dagen!=0) st_perdag=stuks/dagen;
      if(st_perdag>9999.99) st_perdag=9999.999;
      scrifld(z++,fm_of4_3,&st_perdag);
      if(k<12){
	scrfld(z++,6,106+k*4);
	scrfld(z++,6,107+k*4);
	scrfld(z++,6,108+k*4);
      }
      else{
	scrifld(z++,fmt_stuks,&stuks);
	scrifld(z++,fmt_aankw,&aankw);
	scrifld(z++,fmt_verkw,&verkw);
      }
      bd_f=aankw;
      if(sys3586){
	bd_f=verkw;
      }
      bd_fve=verkw;
      if(bd_f) winst=100*((bd_fve-aankw)/bd_f); else winst=0;
      scrifld(z++,fm_of3_0,&winst);
      if(k<13){
	if(st_perdag!=0){
	  if(min_st>st_perdag) min_st=st_perdag;
	  if(max_st<st_perdag) max_st=st_perdag;
	}
	tot_dagen+=dagen; tot_stuks+=stuks; tot_aankw+=aankw; tot_verkw+=verkw;
      }
      next:;
    }
    dsp_rot(z,36,0,min_st,st_perdag,max_st); z+=4;
    dsp_rot(z,33,1,min_st,st_perdag,max_st); z+=4;
    dsp_rot(z,35,0,min_st,st_perdag,max_st); z+=4;
    key=scrupd(113,0x02E1);
    if(key==101 || key==106 || key==108) return key;
    if(key==110) return 107;
  }
}
 
dsp_rot(z,fld,out_flag,min_st,gem_st,max_st)
int z,fld;
flag out_flag;
float min_st,gem_st,max_st;
{
  int k;
  float dagen, stuks;
 
  if(fldlen(6,fld)<=0){
    for(k=0;k<4;k++) scrifld(z++,fm_os5,"  --");
  }
  else{
    if(out_flag) scrofld(z++,6,fld,12); else scrfld(z++,6,fld);
    stuks=*f(6,fld);
    dagen = 0;
    if(max_st) dagen = stuks/max_st;
    if(dagen > 9999) dagen=9999;
    scrifld(z++,fm_of4_0,&dagen);
    dagen = 0;
    if(gem_st) dagen = stuks/gem_st;
    if(dagen > 9999) dagen=9999;
    scrifld(z++,fm_of4_0,&dagen);
    dagen = 0;
    if(min_st) dagen = stuks/min_st;
    if(dagen > 9999) dagen=9999;
    scrifld(z++,fm_of4_0,&dagen);
  }
}
#endif

static DisplayExcludeLev()
{
  int16 curs=1,j,key,k,z,start_=0,dcurs_,curspos_;
  char *pdum,dumm_[10],*pvar;
  pdum=&dumm_[0];
 
	redo_full:;
  ram_recl=s(1,4)-s(1,1) + 2;/* + 2 bytes hash */
  max_line=fldlen(2,196)/2;
  if(max_line>(sizeof ram)/ram_recl) max_line=(sizeof ram)/ram_recl;
  hash_len=fldlen(1,1)+ fldlen(1,2)+fldlen(1,3);
  dat_len=hash_len;

  zeros(ram,sizeof ram);
  for(k=0;k<max_line;k++){
    fasinit(1);*u(1,1)=*(uint16 *)(s(2,196)+k*2);fasgeti(1);
    hash_val=hash(1);
    stu2ram(1,k);
  }
  scrnum=0;
  FOREVER{
    redo:
    scrget(2,334);z=1;
    scrofld(z++,2,1,-1);
    for(j=0;j<max_line;j++){
      if(fieldspc(1,3,&pdum,fmt)>0){
      	pvar=ram+(j*ram_recl + (s(1,3)-s(1,1)));
	      scrifld(z++,fmt,pvar);
      }
    }
    dcurs_=curs; if(max_line==0 || only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0xD0);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106) goto endsr;
    if(key==105){
      j=(curspos_-2);
      del_lin(1,j);
      curs=curspos_;goto redo;
    }
    for(k=0;k<max_line;k++){
      chk_again:;
      ram2stu(1,k);
      if(*s(1,3) && hash_val!=hash(1)){
     	  if(search(1,0)){
					errnum=39;curs=2+k;goto redo;
				}
				hash_val=hash(2);
      }
      else if(*s(1,3)=='\0'){fasinit(1);hash_val=0;}
      stu2ram(1,k);
    }
    if(key==108)break;
    j=0;
    for(k=0;k<max_line;k++){ram2stu(1,k);if(*s(1,3)=='\0') {j=k;break;}}
    curs=2+j;
  }
  for(k=0;k<max_line;k++){
    ram2stu(1,k);
    copy(s(1,1),s(2,196)+k*2,2);
  }
  endsr:;
}


static bst_inp()
{
  int16 curs=1,j,key,k,z,start_=0,dcurs_,curspos_;
  char *pdum,dumm_[10],*pvar;
  pdum=&dumm_[0];
 
	redo_full:;
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
		scraddpicto(20,0,76,20,4,2,514,0,0,"Extra opties"); 
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
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5020){DisplayExtraBestelFuncties(stu);key=107;} // extra opties
#if FLAGCRA
		if(*u(25,4)!=110 && key==15 && only_dsp){only_dsp=NO;goto redo;}
#else
    if(key==15 && only_dsp && CheckPw(1,PwUpdNr,0)){only_dsp=NO;goto redo;}
#endif
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
		if(key==112) {copy_bestelinfo(); goto redo_full;}
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

static DisplayExtraBestelFuncties(stu_)
int16 stu_;
{
	int z,k,key,vt_,hz_;
	FOREVER{
		scrget(1,7);cls();z=1;vt_=6;
		scraddfield(z,33,2,0x0A);scrifld(z++,VarTextFmt(14,0)," Extra opties ");
		AddTextKey(z++,10,vt_,60,2,10011,"Druk bestelformulier",0x007FFF);vt_+=2;
		if(only_dsp==NO){
			AddTextKey(z++,10,vt_,60,2,10012,"Sorteer artikels alfabetisch",0x007FFF);vt_+=2;
  		AddTextKey(z++,10,vt_,60,2,10013,"Sorteer artikels volgens groep",0x007FFF);vt_+=2;
	  	AddTextKey(z++,10,vt_,60,2,10014,"Kopieer artikels van andere klant",0x007FFF);vt_+=2;
		  if(fldlen(16,1)) AddTextKey(z++,10,vt_,60,2,10015,"Laad artikels van historieken",0x007FFF);vt_+=2;
		}
		scraddfield(z,1,23,8);scrifld(z++,VarTextFmt(10,0)," F1 terug ");
 		key=scrupd(-1,0x1);
		if((key/0x10000)>0) key/=0x10000;
	  if(key==101) break;
		switch(key){
		  case 10011 : prt_bon(); break;
      case 10012 : sort_bon(0); break;
			case 10013 : sort_bon(1); break;
			case 10014 : copy_bestelinfo(); break;
			case 10015 : LoadBestelFromHis(); break;
			default : key=107; break;
		}
		if(key!=107) break;
  }
}




static LoadBestelFromHis()
{
  int16 k,mode;
	uint16 bstinfo_[300],max_,dt_beg_;
									
  scrget(1,7);scrupd(-3,0);
  fasinit(16);*l(16,10)=*u(2,1);mode=1;dt_beg_=*u(25,2)-300;
  FOREVER{
    next:;
    if(faskeyi(16,11,mode)) break; mode=2;
    if(*l(16,10)!=*u(2,1)) break;
		if(*l(16,23)==99) {*u(16,3)=0xFFFF; mode=2;goto next;}
	  if(*u(16,3) <dt_beg_) {*u(16,3)=dt_beg_;mode=1; goto next;}
		for(k=0;k<max_line;k++){
			ram2stu(6,k);
		  if(*l(16,20)==*u(6,1) || *u(6,1)==0) {
				fasinit(6);*u(6,1)=*l(16,20);
				if(fasgeti(6)==0){
					hash_val=hash(6);	stu2ram(6,k);}
				break;
			}
		}
		*u(16,3)=0xFFFF; mode=2;goto next;
	}
}

static copy_bestelinfo()
{
  int16 key,smode_,k;
	char bstinfo_[500];
									
  copy(s(stu,1),buf1000,fldlen(stu,0));
  FOREVER{
    redo:;
    scrget(1,5);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_os38,"DE BESTELINFO OVER TE NEMEN ?");
    scrfld(4,stu,3);scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    key=scrupd(4,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) {copy(buf1000,s(stu,1),fldlen(stu,0));break;}
  	smode_=0;	if(key==5001) smode_=98;
	  if(search(stu,smode_)) goto redo;
    if(key==108){
			copy(s(2,120),bstinfo_,fldlen(2,120));
			copy(buf1000,s(stu,1),fldlen(stu,0));
			copy(bstinfo_,s(2,120),fldlen(2,120));
		  zeros(ram,sizeof ram);
			for(k=0;k<max_line;k++){
				fasinit(6);*pu_6_1=*(uint16 *)(s(2,120)+k*2);fasgeti(6);
				hash_val=hash(6);
				stu2ram(6,k);
			}
			break;
		}
  }
}


static sort_bon(int16 sortmode_) // 1 = groep, 0=alfa
{
  int16 k,len_,sw,max_;
  char str1[50],str2[50],*ps_;
									
  max_=max_line;
  for(k=0;k<max_;k++){
    ram2stu(6,k);
    if(*pu_6_1==0){del_lin(6,k);k--;max_--;}
    else if(sortmode_==1){
      fasgeti(6);hash_val=*u(6,9);stu2ram(6,k);
    }
    else {
      fasgeti(6);hash_val=0;stu2ram(6,k);
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
	p_pdfname("Bestelformulier",0,0);
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
 
static de_heer(stu_)
int16 stu_;
{
  int16 g,j,k,len;

  len=fldlen(stu_,3);if(len>50) len=50;
  zeros(nm_dehr,sizeof nm_dehr);
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
      g=len-j;if(g>(k-1)) g=k-1;
      copy(s(stu_,3),&nm_dehr[j],g);
    }
  }
}

static streepje(z)
int16 z;
{
  scrifld(z,fm_os1,"-");
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
  int16 k,curs,z,curs_taal,key;
 
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
    scrget(2,7);  scrinq();
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
			if(fldlen(2,195)){
				if(*s(2,195)=='J'){
					scraddpicto(11,z-1,2,0,2,1,32,0,4,"Mag NIET bestellen via webshop");
				}
				else{
					if(*s(2,195)!='N') scraddpicto(11,z-1,2,0,2,1,32,0,0,"Mag bestellen via webshop");
					else scraddpicto(11,z-1,2,0,2,1,32,0,3,"Mag bestellen via webshop");
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
		if(key==5011 && fldlen(2,195) && !only_dsp){
			if(*s(2,195)=='J') *s(2,195)='N';  else *s(2,195)='J';
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

static Fiches2Xls()
{
  int16 k,max_,z,key,mode_;
	uint16 inq_art_=0,dt_stat_=0;
	char str_[100];

	if(XlsStu!=stu){
	  MaxXlsFldNr=0;max_=150; if(stu==1 || stu==2 || stu==6) max_=200;
	  for(k=1;k<=max_;k++){ // boven 120 zitten data achter de schermen 
		  if(fldlen(stu,k)){
			  XlsFldNr[MaxXlsFldNr]=k;SelectXlsFldNr[MaxXlsFldNr]='N';
				MaxXlsFldNr++; if(MaxXlsFldNr>=114) break; // Maximaal 2 schermen van 57 kolommen 
			}
		}
		XlsStu=stu;
	}

	if(AskFields2Xls()==NO) goto endsr;
	if(stu==6){
		if(ovlcall(2215,0)) goto endsr;
	}
	else{
	  if(selp_ask()==YES) goto endsr;
#if FLAGSAS
		if(stu==2){
			redoasel:;
			scraddf(-1,0,0,0);z=1;
			scraddf(z++,3,21,3);
			scraddf(z++,8,2,0);	scraddf(z++,8,12,2);
			scraddf(z++,10,2,0); scraddf(z++,10,32,2);
			scraddf(z++,23,1,8);scraddf(z++,23,11,8);
			z=1;
			scrifld(z++,VarTextFmt(30,0),"Selectie op historiek");
			scrifld(z++,VarTextFmt(30,0),"Artikel : ");scrfld(z++,6,3);
			scrifld(z++,VarTextFmt(30,0),"Niet meer aangekocht na : ");	scrifld(z++,fm_udat,&dt_stat_);
			scrifld(z++,VarTextFmt(9,0)," F1 stop "); scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
			key=scrupd(1,0x81);
			if(key==101) goto endsr;
			if(*s(6,3)){
				if(search(6,0)) goto redoasel;
			}
			else fasinit(6);
			inq_art_=*u(6,1);
			if(key!=108) goto redoasel;
		}
#endif
	}
	scrget(1,7);scrupd(-3,0);
	zero(str_,sizeof str_);
	if(stu==1) copy0("Leveranciers.Xls",str_,17); 
	else if(stu==2) copy0("Klanten.Xls",str_,15);
	else if(stu==6) copy0("Artikels.Xls",str_,15);
  XlsRef=XlsCreate(str_);
  if(XlsRef<=0) {errnum=1;goto endsr;}
	StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
	StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
	StylGrpTot=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_BEIGE,1,1,0,NO,NO);
	StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
	StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
	StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);

	XlsRij=1;XlsKol=1;
	for(k=0;k<MaxXlsFldNr;k++){ // header wegschrijven 
		if(SelectXlsFldNr[k]=='J'){
			//zero(str_,sizeof str_);
			//sprintf(str_,"Veld : %2d,%3d",stu,XlsFldNr[k]); XlsWrite(XlsRef,0,XlsKol++,0,str_);
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,s(stu,-XlsFldNr[k]),StylTitel);
			if(stu==6 && XlsFldNr[k]==9){
				XlsWrite(XlsRef,XlsRij,XlsKol++,0,s(52,-14),StylTitel);
			}
		}
	}
	XlsRij++;
	fasinit(stu);
  FOREVER{
		nextf:;
    if(faskeyi(stu,2,2)) break;
    if((stu==6 && DirCall_DRK2215_SelectArtikel()) || (stu!=6 && selp_tst())){
#if FLAGSAS
			if(stu==2 && inq_art_){
				fasinit(16);*l(16,10)=*u(2,1); *l(16,20)=inq_art_;*u(16,3)=dt_stat_;
				if(faskeyi(16,1,1)==0){
					if(*l(16,10)==*u(2,1) && *l(16,20)==inq_art_) goto nextf;
				}
			}
#endif
			XlsKol=1;
			for(k=0;k<MaxXlsFldNr;k++){ 
				if(SelectXlsFldNr[k]=='J'){
					zero(str_,sizeof str_);
					if((stu==1 && XlsFldNr[k]==16) || (stu==2 && XlsFldNr[k]==24)){ // juiste taalletter uitschrijven 
						if(*s(stu,XlsFldNr[k])>=4) *s(stu,XlsFldNr[k])=0;
            *s(stu,XlsFldNr[k])=talen[*s(stu,XlsFldNr[k])];
					}
					fmt_get(stu,XlsFldNr[k]); 
					if(fmt[1]==0xC0 || fmt[1]==0x80) WriteVar2Xls(XlsRij,XlsKol++,fmt,s(stu,XlsFldNr[k]),StylDate); // datum apart
					else WriteFld2Xls(XlsRij,XlsKol++,stu,XlsFldNr[k],StylNormal);
					if(stu==6 && XlsFldNr[k]==9){
						fasinit(52); *u(52,1)=*u(6,9);fasgeti(52);
						WriteFld2Xls(XlsRij,XlsKol++,52,14,StylNormal);
					}
				}
			}
			XlsRij++;
		}
	}
	XlsClose(XlsRef,1);
#if FLAGAST
	if(stu==6){ // extrabarcodes uitschrijven
		for(k=0;k<MaxXlsFldNr;k++) {
			if(SelectXlsFldNr[k]=='J' && XlsFldNr[k]==70) break;
		}
		if(k<MaxXlsFldNr){
			scrget(1,7);scrupd(-3,0);
			XlsRef=XlsCreate("Artik_barcodes.Xls");
			if(XlsRef<=0) {errnum=1;goto endsr;}

			XlsRij=1;XlsKol=1;
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Code",StylTitel);
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",StylTitel);
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EAN-bak",StylTitel);
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EAN-stuk",StylTitel);
			fasinit(6);
			FOREVER{
				if(faskeyi(6,1,2)) break;
				if(DirCall_DRK2215_SelectArtikel()){
					if(*s(6,70)){
						XlsKol=1;
						WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);
						WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
						WriteFld2Xls(XlsRij,XlsKol++,6,70,StylNormal);
						XlsRij++;
					}
					if(*s(6,71)){
						XlsKol=1;
						WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);
						WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
						XlsKol++;
						WriteFld2Xls(XlsRij,XlsKol++,6,71,StylNormal);
						XlsRij++;
					}
					fasinit(64);*u(64,3)=*u(6,1);mode_=1;
					FOREVER{
						if(faskeyi(64,2,mode_)) break;  mode_=2;
						if(*u(64,3)!=*u(6,1)) break;
						XlsKol=1;
						WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);
						WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
						if(*u(64,5)==1) XlsKol++;
						WriteFld2Xls(XlsRij,XlsKol++,64,2,StylNormal);
						XlsRij++;
					}
				}
			}
			XlsClose(XlsRef,1);
		}
	}
#endif
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
 
static zeros(pd,len)
char *pd;
int16 len;
{
  int16 k;

  for(k=0;k<len;k++) *(pd+k)='\0';
}

static CheckBtwNr(btwnr_) // controleren op geldige BTW-nummer 
long btwnr_;
{
  long l1_,l2_;
				
  
  if(btwnr_==0) return YES;
		
  l1_=(btwnr_/100)%97;
  l2_=(97-(btwnr_%100))%97;
  if(l1_!=l2_) return NO;
  return YES;
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
  parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}



 
/* #include "E:\ovl219bi.c" */
/* voor screentest 219E : scrget(2,130); scrget(2,232) */
/* voor screentest 2194 : scrget(2,68); scrget(2,70); scrget(2,72); */
/* voor screentest 2922 : scrget(2,318); */
 
 
 
 
