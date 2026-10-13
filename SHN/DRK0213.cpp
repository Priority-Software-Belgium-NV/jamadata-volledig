/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* DRK0213GetD() {return &zzvw;}

extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" char *VarTextFmt(int len_,int update_);
extern "C" int DirCall_DRK2215_SelectArtikel(void);


typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;

static int16 ovlcall();
__declspec(dllimport) unsigned char PrintPaperNr;
 
extern "C" char DRK0213dat[] = "drk0213  00:10 07/10/10 (c) Jamadata";
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define CALCDEF         "%N%0%0%0%0%0%0%0%0%0"
#define DIM_REC         1000
#define DIM_ARTIKEL				  20000
						
extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l(), val();
extern float *f();
extern double *d();
extern double valu_cnv();
extern int16 retcall,parmcall[8];
extern int16 procid;
extern char info[];
static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_os78[]  = {7,0x88,78,0,0,0,0};
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
static char fm_us45[]  = {7,0xC8,45,0,0,0,0};
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
static char fm_ud4_2[] = {6,0xD5,4,2,0x70,0};
static char fm_ud4_0[] = {6,0xD5,4,0,0x70,0};
static char fm_ud3_4[] = {6,0xD5,3,4,0x70,0};
static char fm_ud2_2[] = {6,0xD5,2,2,0x70,0};
static char fm_od4_2[] = {6,0x95,4,2,0x70,0};
static char fm_od3_4[] = {6,0x95,3,4,0x70,0};
static char fm_od4_0[] = {6,0x95,4,0,0x70,0};
static char fm_of6_0[] = {6,0x94,6,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf5_4[] = {6,0xD4,5,4,0x70,0};
static char fm_uf504[] = {6,0xD4,5,4,0x30,0};
static char fm_uf302[] = {6,0xD4,3,2,0x30,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_uf2_5[] = {6,0xD4,2,5,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x20,0};
static char fm_uf201[] = {6,0xD4,2,1,0x30,0};
static char fm_of5_2[] = {6,0x94,5,2,0x70,0};
static char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static char fm_of3_2[] = {6,0x94,3,2,0x70,0};
static char fm_of4_1[] = {6,0x94,4,1,0x70,0};
static char fm_of4_2[] = {6,0x94,4,2,0x70,0};
static char fm_of4_4[] = {6,0x94,4,4,0x70,0};
static char fm_of2_1[] = {6,0x94,2,1,0x20,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_btw[]   = {6,0x91,2,0,0x20,0};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_u_AK[]  = {11,0xC8,1,0,1,0,'A','A','K','K',0};
static char fm_usAT[]  = {9,0xC8,1,0,1,0,'A','T',0};
static char fm_uPB[]   = {11,0xC8,1,0,1,0,'%','%','B','B',0};
static char fm_uNB[]   = {11,0xC8,1,0,1,0,'N','N','B','B',0};
static char fm_u09A[] = {11,0xC8,1,0,1,0,'0','9','A','A',0};
static char fm_u_09[] = {9,0xC8,1,0,1,0,'0','9',0};
static char *modenm[3]={"aan te passen","toe te voegen","te schrappen"};
static int16 fkey=2,linfree,groep,prx_loff,prt2pdf;
static char nm_20[20],nm_15[15],oldnm[65],manier='A',*calctype,flag_prx[11];
static char fmt[40],promocode,art_res[50],lev_res[50],inq_type,sys3896[6],buf750[750];
static char pro_buf[200],prn_buf[200],pr_buf[200],orig_vpbuf[100],upd_contr='J',ModeAccijnsVerhoging='N',CalcOnlyAccijns='N',SkipBlockedArt='J',SkipBlockedAfspraak='J';
static float upd_kor[4],upd_btw,prx_coef,aant_prx[5],LgPrArt,LgPrFile;
static int16 p_max_grp,NrKassaStkPr,NrKassaBakPr;
static char prx_upd[10],prx_opdat,b3598[6];
static flag inc_prijs,chk_bkh,q_newgrb,sgrp_used,slev_used,stu11_exist,rev_prx_calc,sys3242;
static int16 b3604,b3606,sys3652;
static float btw_old,btw_new,afrond,prx_afrond,AP_afrond;
static CString SearchString;
static double BdAccVerhogingHl,PctAccVerhoging,AccVerschil;

static struct{
  uint16 rec;
  char select;
} tbgr[100];
static flag lvcd,klcd,chk_btoeg=NO,sys3720,used_tb[5];
static int16 inq_groep=0,inq_disp='J',inq_lev,inq_merk,inq_art,inpmode,pr_blen, pr_blen69;
static float factor[12]={1,1,1,1,1,1,1,1,1,1,1,1}, offset[12],nieuw[12],dnieuw[12];
static float sys3614,net_winst[22],dsp_winst[22],old_prx,new_prx,old_pct,new_pct,MastPrxCoef;
static float sys2830[10];
static flag sear_stt,sys3586,sys3588,sys3894,sys3632,sys3876,sys3618;
static int16 fld_nr[4]={6,22,7,8};
static uint16 dt_beg,dt_end,inq_klt,dt_start,dt_prlast;
static int MaxArtikel;
static struct{
  uint16 rec;
  char bits;
} tb[DIM_REC];
static char vptekst[100],stuksprx[10],def_munt[4],nm_lev[50],nm_merk[50],MasterArt[1000];
static int16 def_taal;
 
static struct _TbArtikel {
	unsigned int RecordNr;
	double OldAantal;
	double OldInhoud;
	double NewAantal;
	double NewInhoud;
	long DmCode;
	double Inhoud;
	unsigned int updated;
} *TbArtikel=0; // TbArt[DIM_ARTIKEL];


/* --------------------------- Declaratie functies ---------------------- */
static int _btwupdart(void);
static void VerhoogAccijnzen(void);
static int add1str(char *pd, int16 len_, int16 stu_, int16 nr_, char kar_);
static int add_str(char *pd, int16 len_, int16 stu_, int16 nr_, char kar_);
static int art_upd(int16 p_tb_, int16 direct_);
static int btw_upd(void);
static void btwupart(void);
static void calc_kon(char *pn_, int16 mode_);
static void CalcAKFiche(void);
static void calcnet(char *pn_, int16 mode_);
static void calcpr_(char *pr_pos_, float pnew_[],int OpDatum);
static void calcprx(void);
static void CheckInhoud(void);
static bool CheckKeyWord(char *keyword);
static void CheckPrijsMetAankoopfiche(void);
static void chk_oldp(void);
static int copy0(char *ps,char *pd,int max);
static int copy_prx(void);
static void dispgroep(int16 z);
static int dsp_tabel(int16 type_);
static float  ExecOneVol(char* Name, char* Ean, float ArtVol, float ArtCnt);
static void execute(void);
static void fileopen(int16 nr_);
static int fmt_get(int16 stu_, int16 elet_);
static int16 GetLastAKFiche(uint16 lev_rec_,uint16 art_rec_);
static int get_next(int16 first);
static void grb_controle(void);
static void initload(int16 singlemode_);
static void KopieerPrijs(void);
static long makegrb(int16 mode_);
static void newkonprx(int16 type_, float vast_bdr_);
static void nextline(void);
static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_);
static char *pMST(int16 stu_, int16 fld_); // veld nemen van masterartikel in buffer MasterArt
static char *pos_pbf(int16 stu_, int16 fld_);
static int print_prx(void);
static float rnd_vprx(float fl_, int16 type_);
static void round(void);
static double RoundDouble(double getal, double round);
static float roundfloat(float fl_, float afrond_);
static int scr_ok(char *ptxt);
static int search(int16 stu_,int16  mod_);
static int sel_art(int16 direct_);
static int selec_tst(void);
static int select_art(char *ptxt, int16 mode_,int16 printmode_,int16 art_per_art_);
static void streepje(int16 z);
static int testinhoud(void);
static int upav_tab(void);
static void upavpr(void);
static int upd_inq(void);
static int upd_pr(void);
static int upprx_tab(void);
static int used(char *b, int16 len);
static float valuta(void);
/* ---------------------------------------------------------------------- */


// FLAGCOC : prijsdatum (6,11) zit op een andere positie 
// FLAGEPD : korting EUR na % rekenen, dus wordt bij HLkorting geteld
// FLAGVDW : korting EUR na % rekenen, dus wordt bij HLkorting geteld



extern "C" void DRK0213cod(int16 parmval) // 1=prijs direct aanpassen vanuit OVL255/211
{
  initload(parmval);
	if(parmval==1) {retcall=art_upd(-2,YES);ovlexit(-1);} // nieuwe brutoprijs zit in d(26,18)
	if(parmval==3) {// ACCIJNSVERHOGING nieuwe brutoprijs zit in d(26,18)
	  ModeAccijnsVerhoging='J';CalcOnlyAccijns='J';
		retcall=art_upd(-2,YES);ovlexit(-1); 
  }
	if(parmval==2) {CheckInhoud();ovlexit(-1);} // inhoud invullen, vanuit ovl2503,2391,...
  execute();
  ovlexit(-1);
}

static void execute(void)
{
  int16 key,ovlnr_;
  char choice;

	ovlnr_=0;
	if(sys3242==2 && ovltest(2292)) ovlnr_=2292; // districo
	else if(sys3242==1 && ovltest(2293)) ovlnr_=2293; // Belbev
	if(ovlnr_==0){
		if(ovltest(2291)) ovlnr_=2291; // Prik&Tik
		else if(ovltest(2292)) ovlnr_=2292;// districo
		else if(ovltest(2293)) ovlnr_=2293;// Belbev
	}
  FOREVER{
		redo:;
    scrget(3,1);fasunlck(0);
		scraddpicto(50,0,78,6,2,1,105,1,7,"^!B0213A");
		if(fldlen(6,105)) scraddpicto(51,0,78,8,2,1,105,1,7,"^!B0213B");
		if(fldlen(6,31)&& fldlen(6,37)) scraddpicto(52,0,78,17,2,1,105,1,7,"^!B0213D");
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    if(ovlnr_==2292){
      scraddf(117,21,4,2);
      scrifld(117,VarTextFmt(79,0),"Beheer koppelingen Districo (prijslijsten, promofolder, ...) ...... : D ");
    }
    else if(ovlnr_==2293){
      scraddf(117,21,4,2);
      scrifld(117,VarTextFmt(79,0),"Beheer koppelingen Belbev (prijslijsten, promofolder, ...) ........ : D ");
    }
    else if(ovlnr_==2291){
      scraddf(117,21,4,2);
      scrifld(117,VarTextFmt(79,0),"Beheer koppelingen Prik&Tik (prijslijsten, promofolder, ...) ...... : D ");
    }
    key=scrupd(2,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5050 && key<=5052) goto redo; // link help 
    if(key==101) break;
    if(key==111) ovlexit(-1);
		fasunlck(-1);
    inpmode=choice-'0';
    switch(choice){
      case '1': upavpr();break;
      case '2': calcprx();break;
      case '3': sel_art(YES); break;
      case '4': if(fldlen(6,105)) sel_art(NO);
								else errnum=12;
								break;
      case '5': if(fldlen(6,105)) copy_prx();
								else errnum=12;
								break;
      case '6': if(fldlen(6,105)) print_prx();
								else errnum=12;
								break;
      case '7': if(fldlen(11,1)) CheckPrijsMetAankoopfiche();break;
			case '8': btw_upd();break;
      case '9': if(ovltest(296)) ovlexit(296); else errnum=12; break;
      case 'I': if(fldlen(6,31) && fldlen(6,37)) CheckInhoud(); else errnum=12; break;
			case 'A': if(fldlen(6,30)) VerhoogAccijnzen();break;
      case 'D': if(ovltest(ovlnr_)) ovlexit(ovlnr_); 
								break;
      case 'P': KopieerPrijs();break;
      default : errnum=34; break;
    }
  }
}


static void CheckPrijsMetAankoopfiche(void)
{
  int16 k,key,z,curs=2,mode11_,ok_,firsttime_=YES,ret_;
	int16 form_dat[8],pr_mode,prtnr;
	uint16 dt_orig_,last_rec_,last_dt_,ori_ldt_,ori_adt_;
	float prx_verschil_,pct_verschil_,verp_factor_,cnv_11_60_,cnv_11_6_,ori_lpr_,ori_apr_;
	char ShowAllDifferences='N',txt_actie_[50];

#if FLAGCOC
	goto endsr;
#endif
#if FLAGGBL
	ShowAllDifferences='J';
#endif

  fasinit(6);fasinit(1);
	zero(nm_merk,sizeof nm_merk);zero(nm_lev,sizeof nm_lev);
  inq_groep=0;inq_art=0;upd_contr='J';
  FOREVER{
    redo:
    scrget(3,13);z=1; 
    scrfld(z++,25,1);
		scrifld(z++,fm_us40,nm_lev);
		if(fldlen(6,101)) scrifld(z++,fm_us40,nm_merk); else z++;
    //scrfld(z++,1,3);
    scrifld(z++,fm_uu2,&inq_groep);
    scrifld(z++,fm_udat,&dt_beg);scrifld(z++,fm_udat,&dt_end);
    if(fldlen(6,200)) scrifld(z++,fm_uJN,&SkipBlockedArt);
    else {SkipBlockedArt='N'; streepje(z++);}
		scrifld(z++,fm_uJN,&ShowAllDifferences);
    key=scrupd(curs,0x0481);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) return;
		if(nm_lev[0]){
      fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=4;goto redo;}
	    copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
    } else inq_lev=0;
	  if(fldlen(6,101) && nm_merk[0]){
      fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=5;goto redo;}
	    copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
    } else inq_merk=0;
    if(key==108) break;
  }
	firsttime_=YES;
	fasinit(6);scrget(1,7);scrupd(-3,0);
	FOREVER{
		next_art:;
		if(faskeyi(6,2,2)) break;
		if(inq_merk && *u(6,101)!=inq_merk) goto next_art;
		if(inq_groep && *u(6,9)!=inq_groep)  goto next_art;
		if(SkipBlockedArt=='J' && fldlen(6,200) && *u(6,200)) goto next_art;
		if(inq_lev){
			if(*u(6,7)!=inq_lev){ // toch kijken op AK-fixhe
				fasinit(11);*u(11,3)=*u(6,1);mode11_=1;ok_=NO;last_dt_=0;last_rec_=0;
				FOREVER{
					next11_1:;
					if(faskeyi(11,2,mode11_)) break; mode11_=2;
					if(*u(11,3)!=*u(6,1)) break;
					if(*u(11,2)!=inq_lev) goto next11_1;		
 					if(fldlen(11,9) && *u(11,9)) goto next11_1; // geen promoties 
					if(dt_beg && *u(11,8)<dt_beg) goto next11_1;
					if(dt_end && *u(11,8)>dt_end) goto next11_1;	
	
//					ok_=YES; break;
				}
				if(ok_==NO) goto next_art;
			}
		}

  	fasinit(11);*u(11,3)=*u(6,1);mode11_=1;ok_=NO;last_dt_=0;last_rec_=0;
		FOREVER{
			next11:;
			if(faskeyi(11,2,mode11_)) break; mode11_=2;
			if(*u(11,3)!=*u(6,1)) break;
			if(inq_lev){
        if(*u(11,2)!=inq_lev) goto next11;	
			}
			else{
  			if(*u(11,2)!=*u(6,7)){ // als #lev, dan moet merk wel kloppen 
#if !FLAGGBL // ALLE leveranciers zijn OK
    			if(fldlen(6,101)==0 || *u(11,2)!=*u(6,101)) goto next11;
#endif
		  	}
			}
			if(fldlen(11,9) && *u(11,9)) goto next11; // geen promoties 
			if(dt_beg && *u(11,8)<dt_beg) goto next11;
			if(dt_end && *u(11,8)>dt_end) goto next11;

			CalcAKFiche();
			verp_factor_=1.;
			if(fldlen(11,68) && *f(11,68)>0 && *f(6,31)>0 && *f(11,68)!=*f(6,31)) verp_factor_=*f(11,68)/ *f(6,31); 
			cnv_11_6_=roundfloat(*f(11,6)/verp_factor_,AP_afrond);
#if FLAGEPD
			cnv_11_60_=roundfloat(*f(11,61)/verp_factor_,AP_afrond); // statistische prijs nemen 
#else
			cnv_11_60_=roundfloat(*f(11,60)/verp_factor_,AP_afrond);
#endif
			if(sys3652){ // handlingkost erbij tellen, zit niet in AP van AK-fiche
				if(fldlen(6,19)){
					if(sys3652==2) cnv_11_60_*=(100.+*f(6,19))/100.;  // als %
					else cnv_11_60_+=*f(6,19); 
				}
				cnv_11_60_=roundfloat(cnv_11_60_,AP_afrond);
			}
			if(ShowAllDifferences=='J'){
				if(fldlen(6,105) && *u(6,105)){
					*f(6,112)=roundfloat(*f(6,112),AP_afrond);
					if(*u(11,8)>=*u(6,105) && cnv_11_60_!=*f(6,112)){
						if(last_dt_<*u(11,8)){	last_dt_=*u(11,8);last_rec_=*u(11,1);ok_=YES;}
					}
				}
				else{
					*f(6,18)=roundfloat(*f(6,18),AP_afrond);
					if(*u(11,8)>=*u(6,11) && cnv_11_60_!=*f(6,18)){
						if(last_dt_<*u(11,8)){	last_dt_=*u(11,8);last_rec_=*u(11,1);ok_=YES;}
					}
				}
			}
			else{
				if(fldlen(6,105) && *u(6,105)){
					*f(6,112)=roundfloat(*f(6,112),AP_afrond);
					if(*u(11,8)>=*u(6,105) && cnv_11_60_>*f(6,112)){
						if(last_dt_<*u(11,8)){	last_dt_=*u(11,8);last_rec_=*u(11,1);ok_=YES;}
					}	
				}
				else{
					*f(6,18)=roundfloat(*f(6,18),AP_afrond);
					if(*u(11,8)>=*u(6,11) && cnv_11_60_>*f(6,18)){
						if(last_dt_<*u(11,8)){	last_dt_=*u(11,8);last_rec_=*u(11,1);ok_=YES;}
					}
				}
			}
		}
		if(ok_==NO) goto next_art;
		fasinit(11);*u(11,1)=last_rec_;fasgeti(11);
			CalcAKFiche();
			verp_factor_=1.;
			if(fldlen(11,68) && *f(11,68)>0 && *f(6,31)>0 && *f(11,68)!=*f(6,31)) verp_factor_=*f(11,68)/ *f(6,31); 
			cnv_11_6_=roundfloat(*f(11,6)/verp_factor_,AP_afrond);
#if FLAGEPD
			cnv_11_60_=roundfloat(*f(11,61)/verp_factor_,AP_afrond); // statistische prijs nemen 
#else
			cnv_11_60_=roundfloat(*f(11,60)/verp_factor_,AP_afrond);
#endif
			if(sys3652){ // handlingkost erbij tellen, zit niet in AP van AK-fiche
				if(fldlen(6,19)){
					if(sys3652==2) cnv_11_60_*=(100.+*f(6,19))/100.;  // als %
					else cnv_11_60_+=*f(6,19); 
				}
				cnv_11_60_=roundfloat(cnv_11_60_,AP_afrond);
			}
		redo_11fiche:;
		zero(pr_buf,sizeof pr_buf); 
		fasinit(1);*u(1,1)=*u(11,2);fasgeti(1);
		if(fldlen(6,105) && *u(6,105)){copy(s(6,106),pr_buf,pr_blen);copy(s(6,190),&pr_buf[150],pr_blen69);dt_orig_=*u(6,105);}
		else{copy(s(6,12),pr_buf,pr_blen);copy(s(6,185),&pr_buf[150],pr_blen69);dt_orig_=*u(6,11);}
		*f(6,12)=cnv_11_6_;
		if(fldlen(11,7)) copy(s(11,7),s(6,13),fldlen(6,13));
		*f(6,14)=0;*f(6,17)=0;
		for(k=0;k<5;k++){
#if FLAGEPD
			if(*f(11,10+k*10)){ // ALLE kortingen nemen
#else
			if((*s(11,14+k*10)=='F' || *s(11,14+k*10)=='D') && *f(11,10+k*10)){
#endif
	  		if(*s(11,11+k*10)=='%') *f(6,14)+=*f(11,10+k*10);
	  		else *f(6,17)+=*f(11,10+k*10);
			}
		}
		*f(6,18)=cnv_11_60_; *u(6,11)=*u(11,8);
		prx_verschil_=*f(6,18)- *(float *)pos_pbf(6,18);
		if(*(float *)(pos_pbf(6,18))) pct_verschil_=(prx_verschil_/ *(float *)pos_pbf(6,18))*100.;
		else pct_verschil_=0;
		pct_verschil_=rnd_vprx(pct_verschil_,0);
		ori_lpr_=*f(6,18);ori_ldt_=*u(6,11);ori_apr_=*(float *)(pos_pbf(6,18)); ori_adt_=dt_orig_;
		FOREVER{
			scrget(3,14);z=1;
#if FLAGGBL
			scraddfield(50,20,21,8);scrifld(50,VarTextFmt(43,0)," F9 niets aanpassen, enkel uit lijst halen ");
#endif
      if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
      scrofld(z++,6,3,-1);
      scrofld(z++,1,3,-1);
			for(k=11;k<=20;k++) scrfld(z++,6,k); // nieuwe prijzen
			scrifld(z++,fm_udat,&dt_orig_);
      for(k=12;k<=20;k++){ // oude prijzen 
        fmt_get(6,k);scrifld(z++,fmt,pos_pbf(6,k));
      }
			fmt_get(6,18);
			scrifld(z++,fmt,&prx_verschil_);
			scrifld(z++,fm_of3_2,&pct_verschil_);
      key=scrupd(-1,0x13B);
			if(key==101) goto endsr; // stop ermee
      if(key==106) break;; // overslaan
			if(key==102){ovlcall(268,2);fasgeti(6);goto redo_11fiche;}
			if(key==105){// enkel aankoopprijs aanpassen
				copy(s(6,12),pr_buf,pr_blen);copy(s(6,185),&pr_buf[150],pr_blen69);dt_orig_=*u(6,11);
				fasgeti(6);
				if(*u(6,105)){copy(pr_buf,s(6,106),pr_blen);copy(&pr_buf[150],s(6,190),pr_blen69);*u(6,105)=dt_orig_;}
				else{copy(pr_buf,s(6,12),pr_blen);copy(&pr_buf[150],s(6,185),pr_blen69);*u(6,11)=dt_orig_;}
				if(fldlen(6,198)) *u(6,198)=procid;
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				fasupd(6);
				fasupd(11); // om berekende AP te saven
				break;
			}
			if(key==104){ // aan- EN verkoopprijs aanpassen
				copy(s(6,12),pr_buf,pr_blen);copy(s(6,185),&pr_buf[150],pr_blen69);
				fasgeti(6);
				ret_=art_upd(-1,YES); if(ret_!=1) key=106; // niets aangepast
				fasupd(11); // om berekende AP te saven
				break;
			}
#if FLAGGBL
			if(key==109){ // enkel uit lijst halen == datum wegvegen
				zero(s(11,5),fldlen(11,5));
				*u(11,8)=0; fasupd(11); 
				break;
			}
#endif
		}
		if(firsttime_){
			scrget(1,6);scrupd(-3,0);
			getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0; // pdf
			if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
			prtfld(25,1,-1);prttext("<t33eb>");
			prttext("Controle prijzen met aankoopfiche");
			prttext("<eb><t95>");
			prtfld(25,2,-1);
			prttext("<t120>Blz.<ppp>.");
			prtbuf(1);z=1;
			prttab(z,6,2,1,-1);prttitle(z++,"Code",3);
			prttab(z,6,3,1,-1);prttitle(z++,"Omschrijving",3);
			prttab(z,1,3,1,20);prttitle(z++,"Leverancier",3);
			prtitab(z,fm_udat,&ori_adt_,1,-1); prttitle(z++,"Art.Dat",0x13);
			fmt_get(6,18);prtitab(z,fmt,&ori_apr_,1,-1); prttitle(z++,"Pr.Artik.",0x13);
			prtitab(z,fm_udat,&ori_ldt_,1,-1); prttitle(z++,"Lev.Dat",0x13);
			fmt_get(6,18);prtitab(z,fmt,&ori_lpr_,1,-1);prttitle(z++,"Pr.Lever.",0x13);
			prtitab(z,fm_of3_2,&pct_verschil_,1,-1);prttitle(z++,"V%",0x13);
			prtitab(z,fm_os40,txt_actie_,1,-1);prttitle(z++,"Genomen actie",3);
			prtbuf(3);
			p_pdfname("Controle prijzen met aankoopfiche",*u(25,2),0);
			firsttime_=NO;
		}
		zero(txt_actie_,sizeof txt_actie_);
		switch(key){
	  	case 102: copy0("Aankoopfiche aangepast",txt_actie_,50); break;
	  	case 104: copy0("Aan- en verkoopprijzen aangepast",txt_actie_,50); break;
	  	case 105: copy0("Aankoopprijs artikel aangepast",txt_actie_,50); break;
	  	case 106: copy0("Niets aangepast, overgeslagen",txt_actie_,50); break;
#if FLAGGBL
	  	case 109: copy0("Enkel uit lijst gehaald",txt_actie_,50); break;
#endif
	  	default: copy0(" ",txt_actie_,1); break;
		}
		for(k=1;k<20;k++) prtinfo(k,0); nextline();
		scrget(1,7);scrupd(-3,0);
	}
	endsr:;
	if(firsttime_==NO) prtclose();

}
  
static int sel_art(int16 direct_)
{
  int16 j,n,curs,z,key,mode_,start,max_,mode1_,curspos_,art_per_art_=NO;
  char *pd;
  uint16 last_fnd;
	 
  if(prx_loff){errnum=63;return NO;}
  FOREVER{
		redo_select:;
    if(select_art("Inbrengen prijswijzigingen",direct_,NO,art_per_art_)) break;
    zero((char *)&tb[0],sizeof tb);fasinit(6);
    if(inq_art) {*u(6,1)=inq_art;fasgeti(6);tb[0].rec=inq_art;art_upd(0,direct_);art_per_art_=YES;goto redo_select;}
    start=0;max_=DIM_REC;mode_=1;curs=2;last_fnd=0;art_per_art_=NO;
    FOREVER{
      redo:;
      scrnum=0; scrget(3,2);z=1;
      scrifld(z++,fm_os40,"Lijst geselecteerde artikels");
      for(j=start;j<start+18;j++){
				next:;
				if(tb[j].rec==0){
					if(faskeyi(6,fkey,mode_)) {max_=j;break;}
					mode_=2;
					last_fnd=*u(6,1);
					if(inq_art && *u(6,1)!=inq_art) {max_=j;break;}
					if(inq_lev && *u(6,7)!=inq_lev) goto next;
					if(inq_merk && *u(6,101)!=inq_merk) goto next;
					if(inq_groep && *u(6,9)!=inq_groep)  goto next;
					if(!direct_ && dt_beg && *u(6,105)<dt_beg) goto next;
					if(!direct_ && dt_end && *u(6,105)>dt_end) goto next;
					if(SkipBlockedArt=='J' && fldlen(6,200) && *u(6,200)) goto next;
					tb[j].rec=*u(6,1);
					if(fldlen(9,1) && (direct_ || fldlen(9,72))){
						fasinit(9);*u(9,3)=*u(6,1);mode1_=1;
						FOREVER{
							next_9:;
							if(faskeyi(9,7,mode1_)) break; mode1_=2;
							if(*u(9,3)!=*u(6,1)) break;
							if(!direct_ && dt_beg && *u(9,72)<dt_beg) goto next_9;
							if(!direct_ && dt_end && *u(9,72)>dt_end) goto next_9;
							if(testinhoud()){tb[j].bits|=0x01;break;}
						}
					}
				}
				else {
					fasinit(6); *u(6,1)=tb[j].rec;fasgeti(6);
				}
				pd=&oldnm[0]; pd+=add_str(pd,fldlen(6,2)+1,6,2,' ');pd+=add_str(pd,fldlen(6,3),6,3,'\0');
				scrifld(z,fm_us45,oldnm);
				if(tb[j].bits & 0x10) scrchat(z++,0x8); else z++;
				if(direct_) scrifld(z++,fm_os6,"Direct"); else scrofld(z++,6,105,-1);
				if(tb[j].bits & 0x01){
					scrifld(z,fm_os2,"JA");
					if(tb[j].bits & 0x02) scrchat(z++,0x8); else z++;
				} else z++;
      }
      if(start && start==max_){start-=18;goto redo;}
      if(max_==0) {errnum=39;break;}
      key=scrupd(curs,0x087);curs=2;curspos_=fldcurs;
      if(key==101) break;
      if(key==108 || key==109){
				n=(curspos_-1)/3; n+=start;
				curs=curspos_;
				if(tb[n].rec){
					if(key==108) {art_upd(n,direct_);tb[n].bits |=0x10;}
				}
      }
      if(key==102) start-=18;
      if(key==103) {start+=18;if(start>=max_-18) start=max_-18;}
      if(start<0) start=0;
      fasinit(6);*u(6,1)=last_fnd;fasgeti(6);
    }
  }

	return YES;
}

static int art_upd(int16 p_tb_, int16 direct_) // p_tb_==-1 : alles staat al klaar, NIET uit tabel nemen 
{
  int16 j,k,key,z,curs=6,pos_=94,mode_,type_,firsttime_,z_prx_,start_=0;
  flag upd_old=NO;
  float pr_,q_st_,vast_bdr=0,pct_opslag_,factor_,verp_factor_,inhoud_;
  uint16 last_dt_=0;
	char kar_;
	
	rev_prx_calc=NO; LgPrFile=0; LgPrArt=0;
  if(p_tb_==-1){ // alles staat al klaar, NIET uit tabel nemen 
		copy(s(6,21),orig_vpbuf,24); copy(s(6,185),&orig_vpbuf[50],pr_blen69);
		if(fldlen(6,105)) {copy(s(6,115),&orig_vpbuf[25],24);copy(s(6,190),&orig_vpbuf[75],pr_blen69);}
		vast_bdr=0;
		if(fldlen(6,105) && *u(6,105)) {last_dt_=*u(6,105);direct_=NO;}
		else direct_=YES;
    if(CalcOnlyAccijns=='J' && ModeAccijnsVerhoging=='J'){/* prijsverschil NETTO doorrekenen in prijzen */
			vast_bdr = *(float *)pos_pbf(6,12)-*f(6,12);
      *(float *)pos_pbf(6,18)=*f(6,18) + vast_bdr;
			*(float *)pos_pbf(6,30)=*f(6,30) + vast_bdr;
      for(k=0;k<10;k++){
				if(fldlen(6,PrNrs[k]) && *f(6,PrNrs[k])){
					pr_=*f(6,PrNrs[k]); q_st_=1;
					if(sys3894 & 1<<k) pr_/=1.+*f(6,28)/100.;
					if(stuksprx[k]=='J' && fldlen(6,31)) q_st_=*f(6,31);
					if(q_st_==0) q_st_=1;
					pr_+=vast_bdr/q_st_;
					if(sys3894 & 1<<k) pr_*=1.+*f(6,28)/100.;
					pr_=rnd_vprx((float)pr_,k);
					*(float *)pos_pbf(6,PrNrs[k])=pr_;
				}
      }
			calcnet(pr_buf,NO);
    }
		else calcnet(pr_buf,YES);
	}
	else if(p_tb_==-2){   // oproepen via ovl0255 of 2291, in d(26,18) zit nieuwe bruto AP, 26,19: accijns, 26,20: ecotax, 26,21: leeggoed bak, 26,2:datum 26,22 zwerfvuiltax
		LgPrFile=*d(26,21); 
		if(LgPrFile && *s(6,41)){
			copy(s(6,1),buf750,fldlen(6,0));
			copy(s(6,41),s(6,2),fldlen(6,2)); 
			if(faskeyi(6,1,0)==0) LgPrArt=*f(6,21);
			copy(buf750,s(6,1),fldlen(6,0));
		}

		copy(s(6,21),orig_vpbuf,24);  copy(s(6,185),&orig_vpbuf[50],pr_blen69);
		if(fldlen(6,105)){ copy(s(6,115),&orig_vpbuf[25],24);copy(s(6,190),&orig_vpbuf[75],pr_blen69);}
		zero(pr_buf,sizeof pr_buf);
		if(fldlen(6,105) && *u(6,105)) {last_dt_=*u(6,105);	copy(s(6,106),pr_buf,pr_blen); copy(s(6,190),&pr_buf[150],pr_blen69);direct_=NO;}
		else {copy(s(6,12),pr_buf,pr_blen);copy(s(6,185),&pr_buf[150],pr_blen69);}
		if(fldlen(6,105) && *u(26,2)){
			if(*u(6,105)> *u(26,2)){
				if(DisplayWarning("Er is een prijswijziging met HOGERE datum!   Overschrijven?",605,1)==NO) return NO;
			}			
			*u(6,105)=*u(26,2); direct_=NO;}
//		*(float *)pos_pbf(6,28)=*f(6,28);
		if(fldlen(6,30) && (*d(26,19) || *d(26,20) || *d(26,22))) *(float *)pos_pbf(6,30)=*d(26,19)+*d(26,20)+*d(26,22); // enkel accijns of ecotax indien ingevuld
		*(float *)pos_pbf(6,18)=0;
		*(float *)pos_pbf(6,12)=*d(26,18);
		if(CalcOnlyAccijns=='J' && ModeAccijnsVerhoging=='J'){/* prijsverschil NETTO doorrekenen in prijzen */
			vast_bdr = *(float *)pos_pbf(6,12)-*f(6,12);
      *(float *)pos_pbf(6,18)=*f(6,18) + vast_bdr;
			*(float *)pos_pbf(6,30)=*f(6,30) + vast_bdr;
      for(k=0;k<10;k++){
				if(fldlen(6,PrNrs[k]) && *f(6,PrNrs[k])){
					pr_=*f(6,PrNrs[k]); q_st_=1;
					if(sys3894 & 1<<k) pr_/=1.+*f(6,28)/100.;
					if(stuksprx[k]=='J' && fldlen(6,31)) q_st_=*f(6,31);
					if(q_st_==0) q_st_=1;
					pr_+=vast_bdr/q_st_;
					if(sys3894 & 1<<k) pr_*=1.+*f(6,28)/100.;
					pr_=rnd_vprx((float)pr_,k);
					*(float *)pos_pbf(6,PrNrs[k])=pr_;
				}
      }
			calcnet(pr_buf,NO);
    }
		else{
			if(*d(26,18)) calcnet(pr_buf,YES);
		  else{
			  for(j=0;j<10;j++) zero(pos_pbf(6,PrNrs[j]),fldlen(6,PrNrs[j])); // geen VP prijzen overnemen
  			calcnet(pr_buf,NO);
			}
		}
	}
	else if(p_tb_==-3){ // oproepen routine voor de deelverpakkingen 
		copy(s(6,21),orig_vpbuf,24);  copy(s(6,185),&orig_vpbuf[50],pr_blen69);
		if(fldlen(6,105)){ copy(s(6,115),&orig_vpbuf[25],24);copy(s(6,190),&orig_vpbuf[75],pr_blen69);}
		zero(pr_buf,sizeof pr_buf); 		
		if(fldlen(6,105) && *u(6,105)){copy(s(6,106),pr_buf,pr_blen);copy(s(6,190),&pr_buf[150],pr_blen69);}
		else{copy(s(6,12),pr_buf,pr_blen);copy(s(6,185),&pr_buf[150],pr_blen69);}
		if(!direct_ && *u(6,105) && MastPrxCoef==0) {copy(s(6,106),pr_buf,pr_blen);copy(s(6,190),&pr_buf[150],pr_blen69);last_dt_=*u(6,105);*u(6,105)=0;} // geschrapte prijswijziging 
		else{
			*(float *)pos_pbf(6,28)=*f(6,28);
			factor_=*f(6,31)/ *(float *)pMST(6,31);
			if(fldlen(6,30)){
				if(*(float *)pMST(6,31)){ // terug synchroniseren met moederverpakking 
					if(direct_) *(float *)pos_pbf(6,30)=*(float *)pMST(6,30) * factor_;
					else *(float *)pos_pbf(6,30)=*(float *)pMST(6,124) * factor_;
				} 
				else {
					if(direct_) *(float *)pos_pbf(6,30)=*f(6,30); 
					else *(float *)pos_pbf(6,30)=*(float *)pMST(6,124);
				}
			}
			copy(s(6,13),pos_pbf(6,13),s(6,21)-s(6,13));
			copy(s(6,29),pos_pbf(6,29),fldlen(6,29));
			*(float *)pos_pbf(6,18)=0;
			*(float *)pos_pbf(6,12)=*f(6,12)*MastPrxCoef;
			if(!direct_) *u(6,105)=*(unsigned *)pMST(6,105);
		}
    if(ModeAccijnsVerhoging=='J') *(float *)pos_pbf(6,30)=*f(6,30) + (*(float *)pos_pbf(6,12)-*f(6,12)); // accijnsverhoging
		calcnet(pr_buf,YES);
	}
	else{
		zero(pr_buf,sizeof pr_buf); vast_bdr=0;
		fasinit(6);*u(6,1)=tb[p_tb_].rec;fasgeti(6);
		copy(s(6,21),orig_vpbuf,24);  copy(s(6,185),&orig_vpbuf[50],pr_blen69);
		if(fldlen(6,105)) {copy(s(6,115),&orig_vpbuf[25],24);copy(s(6,190),&orig_vpbuf[75],pr_blen69);}
		fasinit(1);*u(1,1)=*u(6,7);fasgeti(1);
		if(!direct_ && *u(6,105)){copy(s(6,106),pr_buf,pr_blen);copy(s(6,190),&pr_buf[150],pr_blen69);last_dt_=*u(6,105);}
		else {/* reeds btw + accijns vooraf invullen */
			if(!direct_ && *u(6,105)==0 && dt_prlast) *u(6,105)=dt_prlast;
			*(float *)pos_pbf(6,28)=*f(6,28);
			if(fldlen(6,30)) *(float *)pos_pbf(6,30)=*f(6,30);
			copy(s(6,13),pos_pbf(6,13),s(6,21)-s(6,13));
			copy(s(6,29),pos_pbf(6,29),fldlen(6,29));
			*(float *)pos_pbf(6,18)=0;
		}
		calcnet(pr_buf,NO);
	}
	if(*f(6,18) && *(float *)pos_pbf(6,18)){// pct opslag berekenen
    pct_opslag_=(*(float *)pos_pbf(6,18) / *f(6,18))*100. - 100.;
    pct_opslag_=valu_cnv("EUR","EUR",(double)pct_opslag_,(double)(0.01));
  } else pct_opslag_=0;
	start_=0;
  FOREVER{
		rev_prx_calc=NO;
redo_a:
		if(fldlen(6,200)){
			if(*u(6,200)) ConLook(1); else   ConLook(0);
		}
    scrnum=0;if(p_tb_==-1 && ModeAccijnsVerhoging=='J') scrget(3,18); else scrget(3,3); z=1;
		if(fldlen(6,PrNrs[6])){
			if(start_) scraddpicto(1,0,32,9,4,2,18,0,4,"Pr 0-5"); 
			else scraddpicto(2,0,32,9,4,2,13,0,4,"Pr 4-9"); 
		}
		if(ModeAccijnsVerhoging=='J'){scraddfield(80,13,6,0x9);scrifld(80,VarTextFmt(26,0)," *** Accijnsverhoging *** ");}
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
    scrofld(z++,1,3,20);
    if(direct_){
      scrifld(z++,VarTextFmt(6,0),"DIRECT"); scrchat(z-1,0x7);
    }
    else scrfld(z++,6,105);
		scrifld(z++,fm_of3_2,&pct_opslag_);if(pct_opslag_<0) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);
		if(p_tb_==-1 && ModeAccijnsVerhoging=='J'){
			scrfld(z++,6,37); scrifld(z++,fm_od3_4,&AccVerschil);
		}
    for(k=12;k<=20;k++){
#if FLAGCOC
	  	if(k==19 || k==20) z++;
		  else{fmt_get(6,k);scrifld(z++,fmt,pos_pbf(6,k));}
#else
      fmt_get(6,k);scrifld(z++,fmt,pos_pbf(6,k));
#endif
    }
#if FLAGCOC
		z++;
#else
    if(upd_old) scrfld(z++,6,11); else scrofld(z++,6,11,-1);
#endif
    for(k=12;k<=20;k++){
#if FLAGCOC
		  if(k==19 || k==20) z++;
		  else{
		  	if(upd_old) scrfld(z++,6,k); else scrofld(z++,6,k,-1);
		  }
#else
      if(upd_old) scrfld(z++,6,k);
      else scrofld(z++,6,k,-1);
#endif
    }
		z_prx_=z;
    for(k=start_;k<start_+6;k++){
      if(fldlen(6,PrNrs[k])){
				kar_='0'+k; scrifld(z++,fm_os1,&kar_);
				scrifld(z++,fm_os6,&vptekst[k*10]);
				if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
				else scrifld(z++,fm_os5,"Excl.");
				fmt_get(6,PrNrs[k]);if(rev_prx_calc) fmt[1]&=0xBF;scrifld(z++,fmt,pos_pbf(6,PrNrs[k]));
				if(upd_old) scrfld(z++,6,PrNrs[k]);
				else scrofld(z++,6,PrNrs[k],-1);
				if(rev_prx_calc) scrifld(z++,fm_uf3_2,&dsp_winst[k+10]); else scrifld(z++,fm_of3_2,&dsp_winst[k+10]);
				scrifld(z++,fm_of3_2,&dsp_winst[k]);
      }
      else for(j=0;j<7;j++) streepje(z++);
    }
    fmt_get(6,28);scrifld(z++,fmt,pos_pbf(6,28));
    if(upd_old) scrfld(z++,6,28); else scrofld(z++,6,28,-1);
		scrfld(z++,6,41); 
		if(LgPrFile && LgPrFile!=LgPrArt){ scrchat(z-1,0xB);scrifld(z++,fm_of3_2,&LgPrFile);}
		else z++;
    fmt_get(6,30);scrifld(z++,fmt,pos_pbf(6,30));if(ModeAccijnsVerhoging=='J' || *(float *)pos_pbf(6,30)!=*f(6,30)) scrchat(z-1,0x9);
    if(upd_old) scrfld(z++,6,30); else scrofld(z++,6,30,-1);
		scrfld(z++,6,44);
    key=scrupd(curs,0x3E1);curs=6;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(fldlen(6,200)) ConLook(0);
		if(key==5001) {start_=0;}
		if(key==5002 && fldlen(6,PrNrs[6])) {start_=4;}
		if(key==101) return NO;
    if(key==106) return 2;
		if(key==112){if(upd_old) upd_old=NO; else upd_old=YES;goto redo_a;}
		if(p_tb_==-1 && ModeAccijnsVerhoging=='J' && BdAccVerhogingHl && *f(6,37)==0){errnum=38; curs=6; goto redo_a;} // inhoud moet ingevuld zijn bij deze acc-update
    if(CalcOnlyAccijns=='J' && key==107){/* prijsverschil NETTO doorrekenen in prijzen */
			vast_bdr = *(float *)pos_pbf(6,12)-*f(6,12);
      *(float *)pos_pbf(6,18)=*f(6,18) + vast_bdr;
      for(k=0;k<10;k++){
				if(fldlen(6,PrNrs[k]) && *f(6,PrNrs[k])){
					pr_=*f(6,PrNrs[k]); q_st_=1;
					if(sys3894 & 1<<k) pr_/=1.+*f(6,28)/100.;
					if(stuksprx[k]=='J' && fldlen(6,31)) q_st_=*f(6,31);
					if(q_st_==0) q_st_=1;
					pr_+=vast_bdr/q_st_;
					if(sys3894 & 1<<k) pr_*=1.+*f(6,28)/100.;
					pr_=rnd_vprx((float)pr_,k);
					*(float *)pos_pbf(6,PrNrs[k])=pr_;
				}
      }
    }
    if(*(float *)pos_pbf(6,12)==0 && *f(6,12)) {curs=5;errnum=38;goto redo_a;}
    if(key==107){
			if(ModeAccijnsVerhoging=='J'){
  			if(p_tb_==-1){
	  			inhoud_=*f(6,37);fasgeti(6);*f(6,37)=inhoud_;
		  		return -1; // herberekenen a.h.v. nieuwe inhoud
			  }
			  *(float *)pos_pbf(6,30)=*f(6,30) + (*(float *)pos_pbf(6,12)-*f(6,12)); // accijnsverhoging
			}
			if(CalcOnlyAccijns!='J') {vast_bdr=0;calcnet(pr_buf,YES);}
		}
		if(key==110) {
			if(rev_prx_calc) {calcnet(pr_buf,YES);rev_prx_calc=NO;}
			else {rev_prx_calc=YES;}
			curs=z_prx_;goto redo_a;
    }
    calcnet(pr_buf,NO);
		if(*f(6,18) && *(float *)pos_pbf(6,18)){// pct opslag berekenen
			pct_opslag_=(*(float *)pos_pbf(6,18) / *f(6,18))*100. - 100.;
			pct_opslag_=valu_cnv("EUR","EUR",(double)pct_opslag_,(double)(0.01));
		} else pct_opslag_=0;
    if(key==108){
			if(!direct_ && *u(6,105)==0 && last_dt_==0 && *f(6,18)){errnum=6;curs=4;goto redo_a;}
			else break;
		}
  }
  if(!direct_ && *u(6,105)==0){
   
    if(last_dt_!=0){
      if(scr_ok("Wenst U echt deze prijswijziging te schrappen (ook op prijsafspraak!) ???")){
				fasunlck(-2);
				zero(pr_buf,sizeof pr_buf);
				if(fldlen(6,198)) *u(6,198)=procid;
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				zero(s(6,106),pr_blen); zero(s(6,190),pr_blen69); fasupd(6);
				fasinit(9);*u(9,3)=*u(6,1);mode_=1;
				FOREVER{
					if(faskeyi(9,7,mode_)) break; mode_=2;
					if(*u(6,1)!= *u(9,3)) break;
					zero(pr_buf,sizeof pr_buf);
					*u(9,72)=0;zero(s(9,73),s(9,77)-s(9,73));zero(s(9,77),s(9,81)-s(9,77));
					fasupd(9);
				}
				fasunlck(-1);
				prx_coef=0; MastPrxCoef=0;goto end_contract;
//				return YES;/* ga naar volgend artikel */
      } else goto redo_a;
    }
		else { zero(pr_buf,sizeof pr_buf);zero(s(6,106),pr_blen);zero(s(6,190),pr_blen69);}
  }
  if(*f(6,18)){/* coefficient berekenen voor prijsafspraken */
    prx_coef=*(float *)pos_pbf(6,18);
    prx_coef=prx_coef / *f(6,18);
  } else prx_coef=1.;
	if(p_tb_!=-3){ // niet bij updaten deelverpakkingen
		if(*f(6,12)){/* coefficient berekenen voor deelverpakkingen */
			MastPrxCoef=*(float *)pos_pbf(6,12);
			MastPrxCoef=MastPrxCoef / *f(6,12);
		} else MastPrxCoef=1.;
	}
  if(direct_){
    copy(pr_buf,s(6,12),pr_blen); copy(&pr_buf[150],s(6,185),pr_blen69);
#if !FLAGCOC
    if(fldlen(6,11)) *u(6,11)=*u(25,2);
#endif
  }
  else{
    copy(pr_buf,s(6,106),pr_blen);copy(&pr_buf[150],s(6,190),pr_blen69);
    dt_start=*u(6,105);
  }
  if(!direct_ && *u(6,105) && last_dt_==0) dt_prlast=*u(6,105);
	fasunlck(-2);
	if(fldlen(6,198)) *u(6,198)=procid;
	if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
	if(fldlen(6,72)==2){ // als er iets veranderd is, deze vlag aanzetten om later etiketten te kunnen selecteren.
		if(cmpstr(s(6,21),orig_vpbuf,24)) *i(6,72)=1;
		if(cmpstr(s(6,185),&orig_vpbuf[50],pr_blen69)) *i(6,72)=1;
		if(fldlen(6,105) && cmpstr(s(6,115),&orig_vpbuf[25],24)) *i(6,72)=1;
		if(fldlen(6,105) && cmpstr(s(6,190),&orig_vpbuf[75],pr_blen69)) *i(6,72)=1;
	}
  fasupd(6); fasflush(0);
	if(fldlen(11,5) && direct_ && p_tb_!=-2){// nieuwe versie AK-fiches, maar niet vanuit ovl211/255 omdat het daar rechtstreeks gebeurt
		if(GetLastAKFiche(*u(6,7),*u(6,1)) && *u(11,8)<*u(25,2)){
			verp_factor_=1.;
			if(fldlen(11,68) && *f(11,68)>0 && *f(6,31)>0 && *f(11,68)!=*f(6,31)) verp_factor_=*f(11,68)/ *f(6,31); 
			*f(11,6)=*f(6,12)*verp_factor_;*f(11,60)=*f(6,18)*verp_factor_;*u(11,8)=*u(25,2); 
			fasupd(11);
		}
	}
	fasunlck(-1);
  if(upd_contr!='J' || (!direct_ && fldlen(9,72)==0)) goto end_contract;
  fasinit(9);*u(9,3)=*u(6,1);mode_=1;
  FOREVER{
    next_9:;
    if(faskeyi(9,7,mode_)) break; mode_=2;
    if(*u(6,1)!= *u(9,3)) break;
    if(*f(9,8)==0){/* enkel met vaste prijs */
      for(k=0;k<4;k++) if(fldlen(9,92+k*5) && *f(9,92+k*5)) break;
      if(k>=4) goto next_9;
    }
    fasinit(2); *u(2,1)=*u(9,2); fasgeti(2);
    type_=*s(2,26)-'0'; if(type_<0 || type_>9 || fldlen(6,PrNrs[type_])==0) type_=0;
    zero(pr_buf,sizeof pr_buf);rev_prx_calc=NO;
    if(direct_ || (*u(9,72)==0 || *u(9,72)!=dt_start)){
      newkonprx(type_,vast_bdr);
      if(!direct_) *u(9,72)=dt_start;
    }
    else {
      copy(s(9,73),pr_buf,s(9,9)-s(9,6));
      copy(s(9,77),(char *)&aant_prx[0],s(9,81)-s(9,77));
    }
    calc_kon(pr_buf,direct_);
    FOREVER{
      scrnum=0;scrget(3,4); z=1;
			scraddpicto(1,0,76,21,4,2,133,0,3,"Schrap deze prijsafspraak"); 
      if(fldlen(2,2)) scrofld(z++,2,2,-1); else z++;
      scrofld(z++,2,3,-1);
      if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
      scrofld(z++,6,3,-1);
      scrofld(z++,2,26,-1);scrofld(z++,2,27,-1);
      if(sys3894 & 1<<type_) scrifld(z++,fm_os5,"Incl.");
      else scrifld(z++,fm_os5,"Excl.");
      if(vast_bdr) scrifld(z++,fm_of4_4,&vast_bdr);
      else scrifld(z++,fm_of4_4,&prx_coef);
      if(direct_){
				scrifld(z++,fm_os10,"DIRECT"); scrchat(z-1,0x7);
      }
      else scrfld(z++,9,72);
      fmt_get(9,6); if(rev_prx_calc) fmt[1]&=0xBF; pos_=0;
      scrifld(z++,fmt,&pr_buf[pos_]);
      fmt_get(9,7);pos_=s(9,7)-s(9,6);if(rev_prx_calc) fmt[1]&=0xBF;
      scrifld(z++,fmt,&pr_buf[pos_]);
      fmt_get(9,8);pos_=s(9,8)-s(9,6);if(rev_prx_calc) fmt[1]&=0xBF;
      scrifld(z++,fmt,&pr_buf[pos_]);
      scrifld(z++,fm_of6_2,&new_prx);
      if(rev_prx_calc) scrifld(z++,fm_uf3_2,&new_pct); else scrifld(z++,fm_of3_2,&new_pct);
      scrofld(z++,9,6,-1); scrofld(z++,9,7,-1);scrofld(z++,9,8,-1);
      scrifld(z++,fm_of6_2,&old_prx);
      scrifld(z++,fm_of3_2,&old_pct);
			if(fldlen(9,4) && *s(9,4)=='J'){
				scraddpicto(1,0,67,2,12,6,605,0,0,"Opgelet!"); 
				scraddfield(50,7,19,11);scrifld(50,VarTextFmt(66,0)," VASTE prijs, kan hier niet gewijzigd worden. Druk op F6 sla over ");
				scraddfield(51,7,20,11);scrifld(51,VarTextFmt(25,0)," Contractdatum: ");
				scraddfield(52,23,20,11);scrofld(52,9,5,-1);
				if(SkipBlockedAfspraak=='J') {key=106;break;}
			}
			else {
				for(k=0;k<4;k++){
					if(fldlen(9,88+k*5)){
						scrofld(z++,9,88+k*5,-1); scrifld(z++,fm_of6_2,f(9,92+k*5)); scrifld(z++,fm_uf6_2,&aant_prx[k]);
					}
					else break;
				}
			}
      key=scrupd(curs,0x368);curs=3;
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key==5001){
				if(DisplayWarning("Wenst U echt deze prijsafspraak volledig te schrappen???",605,1)==YES){
					faskill(9); break;
				}
			}
      if(key==106) break;
			if(key==109) {newkonprx(type_,vast_bdr);rev_prx_calc=NO;}
			if(key==110) {
				if(rev_prx_calc) {calc_kon(pr_buf,direct_);rev_prx_calc=NO;}
				else {rev_prx_calc=YES;}
			}
      calc_kon(pr_buf,direct_);
      if(key==104 && (fldlen(9,4)==0 || *s(9,4)!='J')){
				if(direct_){
					copy(pr_buf,s(9,6),s(9,9)-s(9,6));
					for(k=0;k<4;k++){
						if(fldlen(9,92+k*5)) *f(9,92+k*5)=aant_prx[k];
					}
				}
				else{
					if(*u(9,72)==0){
						zero(pr_buf,sizeof pr_buf);
						zero((char *)&aant_prx[0],sizeof aant_prx);
					}
					copy(pr_buf,s(9,73),s(9,9)-s(9,6));
					*f(9,76)=*f(9,22);
					copy((char *)&aant_prx[0],s(9,77),s(9,81)-s(9,77));
				}
				fasunlck(-2);fasupd(9); fasflush(0);fasunlck(-1);
				break;
      }
    }
  }
end_contract:;
	if(fldlen(6,102)==0 || p_tb_==-3) goto endsr; // geen deelverpakkingen
	if(fldlen(6,102) && *u(6,102)) goto endsr; // is zelf deelverpakking
	copy(s(6,1),MasterArt,fldlen(6,0));
	fasinit(6);*u(6,102)=*(uint16 *)pMST(6,1);mode_=1; firsttime_=YES;
	FOREVER{
		next_clip:;
		if(faskeyi(6,15,mode_)) break; mode_=2;
		if(*u(6,102)!=*(uint16 *)pMST(6,1)) break;
		if(!direct_ && MastPrxCoef==0 && *u(6,105)==0) goto next_clip;// schrappen prijswijziging op datum enkel als ze echt bestaat
		if(firsttime_){
		  if(DisplayWarning("Wenst U ook de prijzen van de deelverpakkingen (clips) te wijzigen?",605,1)==NO) break;
			firsttime_=NO;
		}
		art_upd(-3,direct_);
		for(k=0;k<DIM_REC;k++) if(tb[k].rec==*u(6,1)) break;
		if(k<DIM_REC) tb[k].bits|=0x10;
	}
	copy(MasterArt,s(6,1),fldlen(6,0));
  endsr:;
  return YES;
}

static char *pMST(int16 stu_, int16 fld_)
{
  int16 k;
  char *ps_;
  k=s(6,fld_)-s(6,1);
  ps_=MasterArt+k;
  return ps_;
}


static int16 GetLastAKFiche(uint16 lev_rec_,uint16 art_rec_)// zoek ak-fiche met recentste prijs
{
	uint16 rec11_,mode_;
	  
	fasinit(11);*u(11,2)=lev_rec_;*u(11,3)=art_rec_;rec11_=0;mode_=1;
	FOREVER{
		next11:;
		if(faskeyi(11,2,mode_)) break; mode_=2;
		if(*u(11,3)!=art_rec_) break;
		if(*u(11,2)!=lev_rec_) break;
		if(fldlen(11,9) && *u(11,9)) goto next11; // geen promoties 
		rec11_=*u(11,1); 
	}
  fasinit(11);
	if(rec11_){*u(11,1)=rec11_;fasgeti(11);return YES;}
	return NO;
}

static void newkonprx(int16 type_, float vast_bdr_)
{
  int16 k;
  float pr_;
 
  copy(s(9,6),pr_buf,s(9,9)-s(9,6));
  if(vast_bdr_){
    pr_=*f(9,8);
    if(sys3894 & 1<<type_) pr_/=1.+*f(6,28)/100.;
    pr_+=vast_bdr_;
    if(sys3894 & 1<<type_) pr_*=1.+*f(6,28)/100.;
    pr_=rnd_vprx(pr_,type_);
  }
  else pr_=rnd_vprx(*f(9,8) * prx_coef,type_);
  *(float *)(&pr_buf[s(9,8)-s(9,6)])=pr_;
  zero((char *)&aant_prx[0],sizeof aant_prx);
  for(k=0;k<4;k++){
    if(fldlen(9,92+k*5) && *f(9,92+k*5)){
      if(vast_bdr_){
				pr_=*f(9,92+k*5);
				if(sys3894 & 1<<type_) pr_/=1.+*f(6,28)/100.;
				pr_+=vast_bdr_;
				if(sys3894 & 1<<type_) pr_*=1.+*f(6,28)/100.;
				pr_=rnd_vprx(pr_,type_);
      }
      else pr_=rnd_vprx(*f(9,92+k*5) * prx_coef,type_);
      aant_prx[k]=pr_;
    }
  }
}

static char *pos_pbf(int16 stu_, int16 fld_)
{
  int16 k;
  char *ps_;
	if(fld_<185){
    k=s(6,fld_)-s(6,12);
    ps_=pr_buf+k;
	}
	else {
    k=s(6,fld_)-s(6,185);
    ps_=pr_buf+150+k;
	}
 
  return ps_;
}

static void calc_kon(char *pn_, int16 mode_)
/* directe update */
{
  int16 pos_,type_,bf_len_;
  float accijns_,net_,ak_pr_;
									
  bf_len_=s(9,9)-s(9,6); if(prx_coef==0) prx_coef=1.;
  copy(s(9,6),pro_buf,bf_len_);
  copy(pn_,prn_buf,bf_len_);
  type_=*s(2,26)-'0'; if(type_<0 || type_>9 || fldlen(6,PrNrs[type_])==0) type_=0;
  if(fldlen(6,30)) accijns_=*f(6,30); else accijns_=0;
  old_prx=*f(6,PrNrs[type_]); if(mode_) old_prx/=prx_coef;
  if(*f(9,8)) old_prx=*f(9,8); old_prx-=accijns_;
  old_prx*=(100.-*f(9,6))/100.;
#if !FLAGEPD && !FLAGVDW
  old_prx-=*f(9,7); 
#endif
	old_prx+=accijns_;
  ak_pr_=*f(6,18); if(mode_) ak_pr_/=prx_coef;
  if(ak_pr_){
    net_=old_prx;
    if(sys3894 & 1<<type_) net_/=1.+*f(6,28)/100.;
    old_pct=((net_-ak_pr_)/ ak_pr_) * 100.;
  }
  else old_pct=0;
  copy(s(9,6),pro_buf,bf_len_);
  copy(prn_buf,s(9,6),bf_len_);
  pos_=0;if(mode_==NO && *u(6,105) && *u(9,72)>=*u(6,105)) pos_=94;
  if(fldlen(6,30)) accijns_=*f(6,30+pos_); else accijns_=0;
  if(mode_ || *u(9,72)){
    new_prx=*f(6,PrNrs[type_+10]); if(*f(9,8)) new_prx=*f(9,8); new_prx-=accijns_;
    new_prx*=(100.-*f(9,6))/100.;
#if !FLAGEPD && !FLAGVDW
    new_prx-=*f(9,7); 
#endif
		new_prx+=accijns_;
    if(*f(6,18+pos_)){
  		if(rev_prx_calc){
				net_=*f(6,18+pos_) * (1. + new_pct/100);
				if(sys3894 & 1<<type_) net_*=1.+*f(6,28)/100.;
				new_prx=rnd_vprx((float)net_,type_);
				*f(9,6)=0;*f(9,7)=0; *f(9,8)=new_prx;// copy(s(9,6),prn_buf,bf_len_);
			}
      net_=new_prx;
      if(sys3894 & 1<<type_) net_/=1.+*f(6,28+pos_)/100.;
      new_pct=((net_-*f(6,18+pos_))/ *f(6,18+pos_)) * 100.;
    }
  }
  else {new_prx=0;new_pct=0;}
  copy(s(9,6),pn_,bf_len_);
  copy(pro_buf,s(9,6),bf_len_);
}
						

static void calcnet(char *pn_, int16 mode_) // NO=enkel wint% berekenen, YES=prijs herberekenen
{
  int16 n,k,bf_len_;
  float accijns_,net_,ak_net_,q_stuks,deler_;
									
  bf_len_= s(6,31)-s(6,12);
  copy(s(6,12),pro_buf,bf_len_);copy(s(6,185),&pro_buf[150],pr_blen69);
  copy(pn_,prn_buf,sizeof pr_buf);
  for(n=0;n<2;n++){
		if(n==0) {copy(pro_buf,s(6,12),bf_len_);copy(&pro_buf[150],s(6,185),pr_blen69);}
		else {copy(prn_buf,s(6,12),bf_len_);copy(&prn_buf[150],s(6,185),pr_blen69);}
    if(*f(6,18)){
      if(n==0) goto calc_wpct;/* originele ap-net nooit herberekenen */
      else if(mode_==NO) goto calc_wpct;/* nieuwe enkel aanpassen bij F7 */
    }
    if(*f(6,12)==0) {*f(6,18)=0; goto calc_wpct;}
    accijns_=0;
    net_=*f(6,12); if(fldlen(6,30)) accijns_=*f(6,30); if(net_==0) accijns_=0;
    net_-=accijns_;
    for(k=0;k<3;k++) if(fldlen(6,14+k)) net_*=(100.-*f(6,14+k))/100.;
    if(fldlen(6,17) && net_!=0) net_-=*f(6,17);
		net_+=accijns_; 
		if(sys3652){ // afhaal en losvergoediong erbij tellen 
			if(fldlen(6,19)) {
				if(sys3652==2) net_*=(100.+*f(6,19))/100.;  // als %
				else net_+=*f(6,19);
			}
			if(fldlen(6,20)) net_+=*f(6,20);
		}
    *f(6,18)=net_;
    calc_wpct:;
    if(sys3586==2) ak_net_=*f(6,12); else ak_net_=*f(6,18);
    for(k=0;k<10;k++){  
      if(fldlen(6,PrNrs[k]) && ak_net_){
				q_stuks=0;
				if(stuksprx[k]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
				if(q_stuks==0) q_stuks=1;
				net_=*f(6,PrNrs[k]);
				if(n && (net_==0 || mode_ || rev_prx_calc)){

					if(rev_prx_calc){
						net_=ak_net_* (1. + dsp_winst[k+n*10]/100);
						if(sys3894 & 1<<k) net_*=1.+*f(6,28)/100.;
						net_/=q_stuks;
						net_=rnd_vprx((float)net_,k);
						*f(6,PrNrs[k])=net_;
					}
					else{

						net_=ak_net_/q_stuks + (ak_net_/q_stuks)*net_winst[k]/100.;
						if(sys3894 & 1<<k) net_*=1.+*f(6,28)/100.;
						net_=rnd_vprx((float)net_,k);
						*f(6,PrNrs[k])=net_;
					}
				}
				if(sys3894 & 1<<k) net_/=1.+*f(6,28)/100.;
				net_winst[k+n*10]=((net_-ak_net_/q_stuks)/ (ak_net_/q_stuks)) * 100;
				deler_=ak_net_; if(sys3586==1) deler_=net_*q_stuks;
				if(deler_) dsp_winst[k+n*10]=((net_-ak_net_/q_stuks)/ (deler_/q_stuks)) * 100;
				else dsp_winst[k+n*10]=0;
      }
      else {net_winst[k+n*10]=0;dsp_winst[k+n*10]=0;}
    }
    if(n==0) {copy(s(6,12),pro_buf,bf_len_);copy(s(6,185),&pro_buf[150],pr_blen69);}
		else {copy(s(6,12),prn_buf,bf_len_);copy(s(6,185),&prn_buf[150],pr_blen69);}
  }
  copy(pro_buf,s(6,12),bf_len_);copy(&pro_buf[150],s(6,185),pr_blen69);
  copy(prn_buf,pn_,sizeof pr_buf);
}

static int select_art(char *ptxt, int16 mode_,int16 printmode_,int16 art_per_art_)
{
  int16 key,z,curs=2;
 
  if(art_per_art_==NO) fasinit(6); else curs=7;
	fasinit(1);	zero(nm_merk,sizeof nm_merk);zero(nm_lev,sizeof nm_lev);
	if(manier=='\0') manier='A';
  inq_groep=0;  if(upd_contr=='\0') upd_contr='J';
  FOREVER{
    redo:
    scrget(3,5);z=1; if(printmode_) scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
		if(fldlen(6,30) && printmode_==NO) scraddpicto(50,0,71,21,2,1,105,1,7,"^!B0213C");
    scrifld(z++,fm_os40,ptxt);
    scrifld(z++,fm_u_AK,&manier);
		scrifld(z++,fm_us40,nm_lev);
		if(fldlen(6,101)) scrifld(z++,fm_us40,nm_merk); else z++;
    //scrfld(z++,1,3);
    scrifld(z++,fm_uu2,&inq_groep);scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrfld(z++,6,3);
    if(mode_){streepje(z++);streepje(z++);}
    else{
      scrifld(z++,fm_udat,&dt_beg);scrifld(z++,fm_udat,&dt_end);
    }
    if(fldlen(6,200)) scrifld(z++,fm_uJN,&SkipBlockedArt);
    else {SkipBlockedArt='N'; streepje(z++);}
    if(fldlen(9,4)) scrifld(z++,fm_uJN,&SkipBlockedAfspraak);
    else {SkipBlockedAfspraak='N'; streepje(z++);}
    if(fldlen(9,1)) scrifld(z++,fm_uJN,&upd_contr);
    else {upd_contr='N'; streepje(z++);}
		if(fldlen(6,30) && printmode_==NO){
			scrifld(z++,fm_uJN,&ModeAccijnsVerhoging);
			scrifld(z++,fm_uJN,&CalcOnlyAccijns);
		} 
		else {streepje(z++);streepje(z++);}
    key=scrupd(curs,0x0481);curs=1;
		prt2pdf=NO;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
		if(key==5001){prt2pdf=YES; key=108;} // pdf
		if(key==5002){// uitgebreid groep zoeken
			*u(52,1)=inq_groep;
			if(search(52,98)==0) inq_groep=*u(52,1);
			curs=5;goto redo;
		} 
    if(key==101) return YES;
    if(key==111) ovlexit(-1);
		if(nm_lev[0]){
      fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=3;goto redo;}
	    copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
    } else inq_lev=0;
	  if(fldlen(6,101) && nm_merk[0]){
      fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=4;goto redo;}
	    copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
    } else inq_merk=0;
    if(*s(6,3)){
      if(search(6,0)) {curs=6;goto redo;}
    }
    else fasinit(6);
    inq_art=*u(6,1);
    if(manier=='K') fkey=1; else fkey=2;
    if(key==108) break;
  }
  return NO;
}

static int copy_prx(void)
{
  int16 k,g;
  long n;
	char pl_mag_[15];

	dt_end=*u(25,2);
  if(prx_loff){errnum=63;return NO;}
  if(select_art("Vervangen huidige prijzen door nieuwe",NO,NO,NO)) goto endsr;
  if(scr_ok("Wenst U echt de huidige prijzen te vervangen door de nieuwe ???")==NO) goto endsr;
  fasunlck(-2);
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
			if(inq_merk && *u(6,101)!=inq_merk) goto next_6;
      if(inq_groep && *u(6,9)!=inq_groep)  goto next_6;
      if(*u(6,105)==0) goto next_6;
      if(dt_beg && *u(6,105)<dt_beg) goto next_6;
      if(dt_end && *u(6,105)>dt_end) goto next_6;
			copy(s(6,29),pl_mag_,fldlen(6,29)); // bewaren 
      copy(s(6,106),s(6,12),s(6,125)-s(6,106));
			if(fldlen(6,185)) copy(s(6,190),s(6,185),pr_blen69);
#if !FLAGCOC
      if(fldlen(6,11)) *u(6,11)=*u(6,105);
#endif
      if(fldlen(11,5)){// nieuwe versie AK-fiches 
				if(GetLastAKFiche(*u(6,7),*u(6,1)) && *u(11,8)<*u(6,105)){
					*f(11,6)=*f(6,12);*f(11,60)=*f(6,18);*u(11,8)=*u(6,105); 
					fasupd(11);
				}
			}
			else if(stu11_exist){// 'oude' aankoopfiche updaten 
				fasinit(11);*u(11,2)=*u(6,7);*u(11,3)=*u(6,1);
				if(faskeyi(11,1,0)==0){
					if(*u(11,66)<*u(6,105)){
						*u(11,66)=*u(11,9);*f(11,67)=*f(11,6);
					}
					*f(11,6)=*f(6,12);*f(11,60)=*f(6,18);*u(11,9)=*u(6,105); *f(11,65)=*f(6,30);
					fasupd(11);
				}
      }
      zero(s(6,105),s(6,125)-s(6,105)); if(fldlen(6,190)) zero(s(6,190),pr_blen69);
			copy(pl_mag_,s(6,29),fldlen(6,29)); // terug juistzetten 
			if(fldlen(6,198)) *u(6,198)=procid;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
      fasupd(6);
    }
  }
  if(fldlen(9,1)==0) goto endsr;
  fasinit(9);n=0;
  FOREVER{/* afspraken */
    if(fldlen(9,72)==0) break;
    next_9:;
    if(fldlen(9,1)==4) *l(9,1)=++n; else *u(9,1)=++n;
    g=fasgeti(9);
    if(g==47)break;
    if(g!=46){/* deleted record */
      if(inq_art && *u(9,3)!=inq_art) goto next_9;
      if(*u(9,72)==0) goto next_9;
      if(dt_beg && *u(9,72)<dt_beg) goto next_9;
      if(dt_end && *u(9,72)>dt_end) goto next_9;
      fasinit(6);*u(6,1)=*u(9,3);if(*u(6,1)) fasgeti(6);
      if(inq_lev && *u(6,7)!=inq_lev) goto next_9;
			if(inq_merk && *u(6,101)!=inq_merk) goto next_9;
      if(inq_groep && *u(6,9)!=inq_groep)  goto next_9;
      for(k=0;k<3;k++) *f(9,6+k)=*f(9,73+k);
      *f(9,22)=*f(9,76);
      zero(s(9,72),s(9,77)-s(9,72));
      for(k=0;k<4;k++){
				if(fldlen(9,92+k*5) && fldlen(9,77+k) && *f(9,77+k)) *f(9,92+k*5)=*f(9,77+k);
      }
      zero(s(9,77),s(9,81)-s(9,77));
      fasupd(9);
    }
  }
  fasflush(0);
	fasunlck(-1);
endsr:;
	return YES;
}

static int print_prx(void)
{
  int16 form_dat[8],pr_mode,k,prtnr,z,mode_,mode1_,jj,mm,dd,j,z_acc_;
  uint16 rec_;
  char *pd;
	float pct_opslag_;
 
  if(prx_loff){errnum=63;return NO;}
  if(select_art("Afdrukken prijswijzigingen",NO,YES,NO)) return NO;
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) return NO;
  prtfld(25,1,-1);prttext("<t33eb>");
  prttext("Prijswijzigingen op datum");
  prttext("<eb><t95>");
  prtfld(25,2,-1);
  prttext("<t120>Blz.<ppp>.");
  prtbuf(1);z=1;
  prtitab(z,fm_os40,oldnm,1,-1);prttitle(z++,"Omschrijving",3);
  prttab(z,6,18,1,-1); prttitle(z++,"AK-prijs",0x13);
  for(k=0;k<10;k++){
    if(fldlen(6,PrNrs[k])){
      prttab(z,6,PrNrs[k],0,-1); prttitle(z++,&vptekst[k*10],0x13);
    }
  }
  z_acc_=z;
  prttab(z,6,30,1,-1); prttitle(z++,"Acc/eco",0x13);
  prtitab(z,fm_of4_2,&pct_opslag_,1,-1); prttitle(z++,"Opslag%",0x13);
  prtbuf(3);
	p_pdfname("Prijswijzigingen",dt_beg,dt_end);
  fasinit(6);linfree=999;
  mode_=1;
  FOREVER{
    next:;
    if(faskeyi(6,fkey,mode_)) break;
    mode_=2;
    if(inq_art && *u(6,1)!=inq_art) goto next;
    if(inq_lev && *u(6,7)!=inq_lev) goto next;
		if(inq_merk && *u(6,101)!=inq_merk) goto next;
    if(inq_groep && *u(6,9)!=inq_groep)  goto next;
    if(*u(6,105)==0) goto next;
    if(dt_beg && *u(6,105)<dt_beg) goto next;
    if(dt_end && *u(6,105)>dt_end) goto next;
    pd=&oldnm[0]; pd+=add_str(pd,fldlen(6,2)+1,6,2,' ');pd+=add_str(pd,fldlen(6,3),6,3,'\0');
    pct_opslag_=0;
		for(k=0;k<20;k++) prtinfo(k,0);nextline();
    rec_=*u(6,1);
    if(*u(6,105)){
      pd=oldnm;
      jddate(*u(6,105),&jj,&mm,&dd);
      copy("    Vanaf ",pd,10);
      stcli_d(pd+10,(long)dd,2,0);*(pd+12)='/';
      stcli_d(pd+13,(long)mm,2,0);*(pd+15)='/';
      stcli_d(pd+16,(long)jj,4,0);copy(" :",pd+20,3);
			if(*f(6,18) && *f(6,112)){// pct opslag berekenen
        pct_opslag_=(*f(6,112) / *f(6,18))*100. - 100.;
        pct_opslag_=valu_cnv("EUR","EUR",(double)pct_opslag_,(double)(0.01));
      } else pct_opslag_=0;
      copy(s(6,106),s(6,12),s(6,125)-s(6,106)); if(fldlen(6,185)) copy(s(6,190),s(6,185),pr_blen69); 
      for(k=0;k<20;k++) prtinfo(k,2);nextline();
    }
    if(fldlen(9,72)==0) goto next;
		pct_opslag_=0;
    fasinit(9);*u(9,3)=rec_;mode1_=1; fasinit(6);
    FOREVER{
      next_9:;
      if(faskeyi(9,7,mode1_)) break; mode1_=2;
      if(*u(9,3)!=rec_) break;
      if(dt_beg && *u(9,72)<dt_beg) goto next_9;
      if(dt_end && *u(9,72)>dt_end) goto next_9;
      if(testinhoud()){
				fasinit(2);*u(2,1)=*u(9,2);fasgeti(2);
				j=*s(2,26)-'0'; if(j<0 || j>9 || fldlen(6,PrNrs[j])==0) j=0;
				fasinit(6);*u(6,1)=rec_;fasgeti(6);
				calc_kon(s(9,73),NO);
				pd=oldnm;
				copy("       Afspraak : ",pd,17);pd+=17;
				add_str(pd,30,2,3,'\0'); fasinit(6);
				*f(6,PrNrs[j])=old_prx;
				for(k=0;k<z_acc_;k++) prtinfo(k,0);nextline();
				if(*u(9,72)){
					pd=oldnm;
					jddate(*u(9,72),&jj,&mm,&dd);
					copy("                  Vanaf : ",pd,26);
					stcli_d(pd+26,(long)dd,2,0);*(pd+28)='/';
					stcli_d(pd+29,(long)mm,2,0);*(pd+31)='/';
					stcli_d(pd+32,(long)jj,4,0);copy(" :",pd+36,3);
					*f(6,PrNrs[j])=new_prx;
					for(k=0;k<z_acc_;k++) prtinfo(k,2);nextline();
				}
      }
    }
    fasinit(6);*u(6,1)=rec_;fasgeti(6);
  }
  prtclose();
	return YES;
}

static int add_str(char *pd, int16 len_, int16 stu_, int16 nr_, char kar_)
{
  int16 k,len1_;
							
	len1_=len_;
  if(len1_>fldlen(stu_,nr_)) len1_=fldlen(stu_,nr_);
  copy(s(stu_,nr_),pd,len1_);
  for(k=0;k<len1_;k++){
    if(*(pd+k)=='\0') break;
  }
	for(k;k<len_;k++){
    *(pd+k)=kar_;if(kar_=='\0') break;
	}
  return k;
}

static int testinhoud(void)
{
  int16 k;
 
  for(k=0;k<4;k++) if(fld_nr[k] && *f(9,fld_nr[k])) return YES;
  for(k=0;k<4;k++) if(fldlen(9,88+k*5) && *f(9,88+k*5)) return YES;
  return NO;
}

static int scr_ok(char *ptxt)
{
  int16 key;
  scrget(1,169);
  scrifld(12,fm_os78,ptxt);
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  return NO;
}

static void upavpr(void)
{
  int16 g;
  flag first=YES;
 
  for(g=0;g<11;g++) flag_prx[g]='N';
  if(!upav_tab()) goto endsr;
  redo:
  if(!upd_inq()) goto endsr;
	seldata.prx_klt=0;
	seldata.selp_use=NO;
	if(ovlcall(2215,2)) goto endsr;
	fasinit(6);
  FOREVER{
    if(!get_next(first)) break;
    first=NO;
    if(fldlen(6,12)){
      nieuw[0]=offset[0]+factor[0] * *f(6,12);
      if(nieuw[0]!= *f(6,12)) flag_prx[0]='J';
    }
    if(fldlen(6,18)) {nieuw[1]=offset[1]+factor[1] * *f(6,18);}
    for(g=0;g<10;g++){
      if(fldlen(6,PrNrs[g])){
				nieuw[2+g]=offset[2+g]+factor[2+g] * *f(6,PrNrs[g]);
				if(nieuw[2+g]!=*f(6,PrNrs[g])) flag_prx[1+g]='J';
      }
    }
    if(fldlen(6,105)){
      if(fldlen(6,12)){
				dnieuw[0]=offset[0]+factor[0] * *f(6,106);
      }
      if(fldlen(6,18)) {dnieuw[1]=offset[1]+factor[1] * *f(6,112);}
      for(g=0;g<10;g++){
				if(fldlen(6,PrNrs[g+10])){
					dnieuw[2+g]=offset[2+g]+factor[2+g] * *f(6,PrNrs[g+10]);
				}
      }
    }
    if(!upd_pr()) break;/* stopped */
  }
  fasflush(0);
  if(errnum) goto redo;
  endsr:;
}
 

static int upprx_tab(void)
{
  int16 z,g,key;
  for(g=0;g<11;g++) flag_prx[g]='N';
  FOREVER{
    scrget(3,6); z=1;
    scrfld(z++,25,1);
    if(fldlen(6,12)) scrifld(z++,fm_uJN,&flag_prx[0]);
    else scrifld(z++,fm_os1,"-");
    for(g=0;g<10;g++){
      if(fldlen(6,PrNrs[g])){
				scrifld(z++,fm_os6,&vptekst[g*10]);
				scrifld(z++,fm_uJN,&flag_prx[g+1]);
      }
      else {z++;scrifld(z++,fm_os1,"-");}
    }
    key=scrupd(2,0x0481);
    if(key==101) break;
    else if(key==111) ovlexit(210);
    else if(key==108) return YES;
  }
  return NO;
}

static void calcprx(void)
{
  int16 g;
  flag first=YES;
				
  if(!upprx_tab()) goto endsr;
  for(g=0;g<11;g++) if(flag_prx[g]=='J') break;
  if(g==11) goto endsr;
  redo:
  if(!upd_inq()) goto endsr;
	seldata.prx_klt=0;
	seldata.selp_use=NO;
	if(ovlcall(2215,2)) goto endsr;
	fasinit(6);
  FOREVER{
    if(!get_next(first)) break;
    first=NO;
    calcpr_(s(6,12),nieuw,0);
    if(fldlen(6,105) && *u(6,105)) calcpr_(s(6,106),dnieuw,1);
    if(!upd_pr()) break;/* stopped */
  }
  if(errnum) goto redo;
  endsr:;
}

static void calcpr_(char *pr_pos_, float pnew_[],int OpDatum)
{
  float kort,work,apbruto_,acc_,accijns,fabrica_,q_stuks;
  double bd_;
	int16 g,k,bf_len_,grpnrs_[10]={2,4,6,8,10,12,30,32,34,36};
  char *ptype, *ptov;
				
  bf_len_=s(6,31)-s(6,12);
  copy(s(6,12),pro_buf,bf_len_);copy(s(6,185),&pro_buf[150],pr_blen69);
  copy(pr_pos_,s(6,12),bf_len_); if(OpDatum) copy(s(6,190),s(6,185),pr_blen69); 
  for(g=0;g<7;g++) pnew_[g]=0;
  accijns=0;
  if(fldlen(6,30)) accijns=*f(6,30);
  apbruto_=*f(6,12);
  if(sys3720) apbruto_/=1.+*f(6,28)/100;
  if(fldlen(6,13)) apbruto_=valu_cnv(s(6,13),def_munt,(double)apbruto_,(double)0.001);
  if(fldlen(6,19)) fabrica_=*f(6,19); else fabrica_=0;
  if(fldlen(6,12)) pnew_[0]=*f(6,12);
  if((flag_prx[0]=='J') && fldlen(6,12)){
    if(!sys3588){/* geen cascade */
      for(kort=0,k=0;k<3;k++) if(fldlen(6,14+k)) kort+=*f(6,14+k);
      work=(apbruto_-accijns)*(100-kort)/100;
    }
    else{/* cascade */
      work=apbruto_-accijns;
      for(k=0;k<3;k++) if(fldlen(6,14+k)) work*=(100-*f(6,14+k))/100;
    }
    bd_=0;
    if(fldlen(6,17)){
      bd_=*f(6,17);
      if(fldlen(6,13)) bd_=valu_cnv(s(6,13),def_munt,bd_,(double)0.001);
    }
    work-=bd_;
		work+=accijns; 
		if(sys3652){ // afhaal en losvergoediong erbij tellen 
			if(fldlen(6,19)) {
				if(sys3652==2) work*=(100.+*f(6,19))/100.;  // als %
				else work+=*f(6,19);
			}
	//		if(fldlen(6,19)) work+=*f(6,19);
			if(fldlen(6,20)) work+=*f(6,20);
		}
    pnew_[1]=work;
  }
  else pnew_[1]=*f(6,18);
  
	fasinit(52);/* if nothing found, use empty fiche */
  *i(52,1)=*i(6,9);
  fasgeti(52);
  g=0; for(k=0;k<12;k++) g+=*(calctype+k);
  if(g==0)copy(CALCDEF,calctype,fldlen(52,22));
  accijns=0; // bij VP GEEN rekening houden met accijns 
  for(g=0;g<10;g++){
    if(fldlen(6,PrNrs[g]) && fldlen(52,grpnrs_[g]) && (flag_prx[g+1]=='J')){
      ptype=calctype+0+g*2; ptov=calctype+1+g*2;
      switch(*ptov){
				case 'F': work=fabrica_; break;
				case 'B': work=apbruto_-accijns; break;
				case 'N': work=pnew_[1]-accijns; break;
				default:/* 0 - 4 */
					k=*ptov-'0';
					work=pnew_[k+2]-accijns;
					if(sys3894 & (1<<k)) work/=1.+ *f(6,28)/100;
					q_stuks=0;
					if(stuksprx[k]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
					if(q_stuks==0) q_stuks=1;
					work*=q_stuks;/* converteren naar bakprijs */
					break;
			}
			q_stuks=0;
			if(stuksprx[g]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
			if(q_stuks==0) q_stuks=1;
			work/=q_stuks; acc_=accijns/q_stuks;
			if(*ptype=='B'){
				pnew_[g+2]= work + *f(52,grpnrs_[g]) + *f(52,grpnrs_[g]+1) + acc_;
			}
			else{
				pnew_[g+2]= work*(1.+*f(52,grpnrs_[g])/100.) + acc_;
      }
      if(sys3894 & (1<<g)) pnew_[g+2]*=1.+ *f(6,28)/100;
    }
    else pnew_[g+2]=*f(6,PrNrs[g]);
  }
  copy(pro_buf,s(6,12),bf_len_);copy(&pro_buf[150],s(6,185),pr_blen69);
}

static int btw_upd(void)
{
  int16 k,key,z,curs;
  afrond=(float)0.05; inq_disp='J';dt_start=*u(25,2);
  inc_prijs=NO;
  for(k=0;k<10;k++){
    if(fldlen(6,PrNrs[k])==0 || !(sys3894 & (1<<k))) prx_upd[k]='\0';
    else {prx_upd[k]='J';inc_prijs=YES;}
  }
  if(inc_prijs && fldlen(6,105)) prx_opdat='J'; else prx_opdat='N';
  curs=1;
  FOREVER{
    redo:;
    scrnum=0;scrget(3,7); z=1;
    scrifld(z++,fm_uf2_1,&btw_new);
    for(k=0;k<10;k++){
      scrifld(z++,fm_os6,&vptekst[k*10]);
      if(inc_prijs && prx_upd[k]) scrifld(z++,fm_uJN,&prx_upd[k]);
      else scrifld(z++,fm_os1,"-");
    }
    if(inc_prijs && fldlen(6,105)) scrifld(z++,fm_uJN,&prx_opdat);
    else scrifld(z++,fm_os1,"-");
    scrifld(z++,fm_uJN,&inq_disp);
    if(fldlen(6,11)==2) scrifld(z++,fm_udat,&dt_start);
    else scrifld(z++,fm_os1,"-");
    if(inc_prijs) scrifld(z++,fm_uf2_5,&afrond);
    else scrifld(z++,fm_os1,"-");
    key=scrupd(curs,0x81);curs=1;
    if(key==101) return YES;
    if(btw_new==0){errnum=34;curs=1;goto redo;}
    if(!errnum && key==108) break;
  }
  dsp_tabel(1);
  btwupart();
  return NO;
}

static void btwupart(void)/* aanpassen btw% artikelen */
{
  int16 g;
  uint16 n;
  if(scr_ok("   Wenst U echt de BTW-percentages aan te passen ?")==NO) goto endsr;
  fasinit(6); q_newgrb=0;
  n=0;scrnum=0;
  FOREVER{
    next_art:;
    *u(6,1)=++n;
    g=fasgeti(6);
    if(g==47)break;
    if(g!=46){/* deleted record */
      if(selec_tst()==NO) goto next_art;
      if(*f(6,28)==btw_new) goto next_art;
      if(_btwupdart()==NO) break;
      if(chk_bkh) grb_controle();
    }
  }
  if(q_newgrb){
    scrget(1,170);
    scrifld(5,fm_os63,"Aantal bijgevoegde grootboekrekeningen :");
    scrifld(6,fm_ou5,&q_newgrb);
    scrifld(10,fm_os63,"Indien er een rekening bestond voor het oude BTW%");
    scrifld(11,fm_os63,"  dan werden de gegevens overgenomen.");
    scrifld(13,fm_os63,"Indien er GEEN rekening bestond, dan werd een nieuwe");
    scrifld(14,fm_os63,"  gemaakt met omschrijving REKENING xxxxxxxx");
    scrifld(16,fm_os63,"Druk een lijst af en vul deze rekeningen aan");
    scrifld(20,fm_os63,"Druk op F8 om verder te gaan ...");
    scrupd(-1,0x81);
  }
  fasflush(0);
  endsr:;
}

static int _btwupdart(void)
{
  float *pf,nieuw[22];
  int16 z,g,k,key;
  double bd_;
 
  zero((char *)&nieuw[0],sizeof nieuw);
  for(k=0;k<10;k++){
    nieuw[k]=*f(6,PrNrs[k]);
    if(fldlen(6,PrNrs[k+10])) nieuw[k+10]=*f(6,PrNrs[k+10]);
    if(prx_upd[k]=='J'){
      bd_=*f(6,PrNrs[k]);
      bd_/=1.+*f(6,28)/100.;
      bd_*=1.+btw_new/100.;
      nieuw[k]=valu_cnv("EUR","EUR",(double)bd_,(double)afrond);
      if(prx_opdat=='J'){
				bd_=*f(6,PrNrs[k+10]);
				bd_/=1.+*f(6,122)/100.;
				bd_*=1.+btw_new/100.;
				nieuw[k+10]=valu_cnv("EUR","EUR",(double)bd_,(double)afrond);
      }
    }
  }
  if(inq_disp!='J') goto update;
  FOREVER{// SCHERM NIET AANGEPAST AAN 10 PRIJZEN: er worden enkel de eerste 6 prijzen gedisplayed (Jaak 24/01/20)
    scrnum=0;scrget(3,8); z=1;
    scrofld(z++,6,2,-1);
    scrofld(z++,6,3,42);
    scrofld(z++,6,28,-1); scrifld(z++,fm_of2_1,&btw_new);
    for(g=0;g<6;g++){
      scrifld(z++,fm_os6,&vptekst[g*10]);
      fieldspc(6,PrNrs[g],&pf,fmt); fmt[1]=fmt[1] & 0xBF;
      scrifld(z++,fmt,f(6,PrNrs[g]));
      fieldspc(6,PrNrs[g],&pf,fmt); scrifld(z++,fmt,&nieuw[g]);
      if(prx_upd[g]=='J') scrchat(z-1,0x8);
    }
    if(prx_opdat=='J' && *u(6,105)){
      scrofld(z++,6,105,-1);
      scrofld(z++,6,122,-1); scrifld(z++,fm_of2_1,&btw_new);
      for(g=0;g<6;g++){
				scrifld(z++,fm_os6,&vptekst[g*10]);
				fieldspc(6,PrNrs[g],&pf,fmt); fmt[1]=fmt[1] & 0xBF;
				scrifld(z++,fmt,f(6,PrNrs[g+10]));
				fieldspc(6,PrNrs[g],&pf,fmt); scrifld(z++,fmt,&nieuw[g+10]);
				if(prx_upd[g]=='J') scrchat(z-1,0x8);
      }
    }
    key=scrupd(1,0x119);
    if(key==101) return NO;
    if(key==104) break;/* pas aan */
    if(key==105) return YES;/* pas niet aan, volgende */
    if(key==109) {inq_disp='N'; break;}/* pas aan, niet meer vragen */
  }
  update:;
  for(k=0;k<10;k++){
    if(fldlen(6,PrNrs[k])) *f(6,PrNrs[k])=nieuw[k];
    if(fldlen(6,PrNrs[k+10])) *f(6,PrNrs[k+10])=nieuw[k+10];
  }
  *f(6,28)=btw_new;
#if !FLAGCOC
  if(fldlen(6,11) && dt_start) *u(6,11)=dt_start;
#endif
  if(prx_opdat=='J') *f(6,122)=btw_new;
	if(fldlen(6,198)) *u(6,198)=procid;
	if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
  fasunlck(-2);errnum=fasupd(6);fasunlck(-1);
  return YES;/* volgende */
}

static void grb_controle(void)
{
  int16 g,k;
  long new_rek,old_rek;
  new_rek=makegrb(NO);
  fasinit(3);*l(3,2)=new_rek;
  if(faskeyi(3,1,0)){
    q_newgrb++;
    old_rek=makegrb(YES);
    fasinit(3);*l(3,2)=old_rek;
    if(faskeyi(3,1,0)==0){
      *l(3,2)=new_rek;
      for(k=0;k<fldlen(3,3);k++) if(*(s(3,3)+k)=='\0') break;
      if(k>fldlen(3,3)-4) k=fldlen(3,3)-4;
      stcli_d(s(3,3)+k,(long)(btw_new),3,1);
      *u(3,1)=0;g=fasadd(3);
      if(g) errnum=g;
    }
    else{
      fasinit(3);
      *l(3,2)=new_rek;
      copy("REKENING ",s(3,3),9); grb_deco(s(3,3)+9,&new_rek);
      *s(3,4)='N';
      *s(3,5)='J';
      *s(3,6)='0';
      *s(3,7)='0';
      *s(3,10)='0';
      *s(3,11)='J';
      g=fasadd(3);
      if(g) errnum=g;
    }
  }
}

static long makegrb(int16 mode_)
{
  int16 g,gg,kk;
  long rekenc;
  char reken[10];
  float btw_;
 
  btw_=btw_new; if(mode_) btw_=btw_old;
  if(fldlen(6,40)) rekenc=*l(6,40);
  else{
    zero(reken,sizeof reken);
    copy(b3598,reken,6);
    for(g=0;g<10;g++) if(reken[g]=='\0') break;
    if(fldlen(6,39)){
      copy(s(6,39),&reken[g],fldlen(6,39));
      for(g=0;g<10;g++) if(reken[g]=='\0') break;
    }
    if(b3604){
      stcli_d(&reken[g],(long)*i(6,9),b3604,0);
      g+=b3604;
    }
    if(b3606){
      kk=btw_;gg=btw_*10 - kk*10;/* gg = decimaal */
      stcli_d(&reken[g],(long)kk,2,0);
      if(gg && b3606==2) stcli_d(&reken[g]+2,(long)gg,1,0);/* decimaal */
    }
    grb_comp(reken,&rekenc);
  }
  return (long)rekenc;
}
 

static int dsp_tabel(int16 type_)
/* 0=leveranciers, 1=groepen */
{
  int16 k,key,z,start=0,startpos,p_tb,curs=1,q_y,q_n,stu_,curspos_;
  char *pd;
					
  stu_=52;startpos=0; p_tb=p_max_grp;
  start=startpos; pd=oldnm;
  FOREVER{
    redo:;
    scrnum=0;scrget(3,9);z=1;
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
								 pd+=add1str(pd,30,52,14,'\0');
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

static int add1str(char *pd, int16 len_, int16 stu_, int16 nr_, char kar_)
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
 

static int selec_tst(void)
{
  int16 k;
								
  if(sgrp_used){
    for(k=0;k<p_max_grp;k++) if(*u(6,9)==tbgr[k].rec) break;
    if(k>=p_max_grp || tbgr[k].select!='J') return NO;
  }
  return YES;
}
	

static int upav_tab(void)
{
  int16 z,g,curs=1,key;
  FOREVER{
    scrget(3,10);z=1;
    scrfld(z++,25,1);
    if(fldlen(6,12)){
      scrifld(z++,fm_uf5_4,&factor[0]); scrifld(z++,fm_uf5_4,&offset[0]);
    }
    else {streepje(z++);streepje(z++);}
    if(fldlen(6,18)){
      scrifld(z++,fm_uf5_4,&factor[1]); scrifld(z++,fm_uf5_4,&offset[1]);
    }
    else {streepje(z++);streepje(z++);}
    for(g=0;g<10;g++){
      if(fldlen(6,PrNrs[g])){
				scrifld(z++,fm_os6,&vptekst[g*10]);
				scrifld(z++,fm_uf5_4,&factor[2+g]); scrifld(z++,fm_uf5_4,&offset[2+g]);
      }
      else {z++;streepje(z++);streepje(z++);}
    }
    key=scrupd(curs,0x0481);
    if(key==101) break;
    else if(key==111) ovlexit(210);
    else if(key==108) return YES;
  }
  return NO;
}

static int get_next(int16 first)
{
	 
  if(inq_art){
    if(!first) return NO;
    *u(6,1)=inq_art;
    errnum=fasgetu(6); if(errnum) return NO; else return YES;
	}
	scrget(1,7);scrupd(-3,0);
  FOREVER{
		next_art:;
    errnum=faskeyu(6,fkey,2);
    if(errnum){
      if(!first) errnum=0;
      return NO;
    }
		if(inq_lev && *u(6,7)!=inq_lev) goto next_art;
    if(inq_merk && *u(6,101)!=inq_merk) goto next_art;
    if(inq_groep && *i(6,9)!=inq_groep) goto next_art;
		if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
		break;
	}
  return YES;
}

static float roundfloat(float fl_, float afrond_)
{
  float add;
	
  add=afrond_/2.;
  add=add*.999999;
  if(afrond_>0.0001){
    fl_=((long)((fl_+add)/(afrond_))) * afrond_;
  }
  return (float)fl_;
}



static float rnd_vprx(float fl_, int16 type_)
{
  float add, *pf;
						
  if(type_<0 || type_>9) type_=0; pf=&sys2830[type_];/* pf=&sys3614; */
	fl_=valu_cnv("EUR","EUR",(double)(fl_),(double)(*pf));
  //add=*pf;
  //if(sys3618==0) add/=2.;
  //add=add*.999999;
  //if(*pf>0.0001){
  //  fl_=((long)((fl_+add)/(*pf))) * *pf;
  //}
  return (float)fl_;
}

static int upd_pr(void)
{
  float *pf,net_winst[10],net_, q_stuks,accijns=0,deler_;
  int16 z,g,key;
 
  round();
  if(inq_disp=='J'){
    if(fldlen(6,30)) accijns=*f(6,30);
    fasinit(1); *u(1,1)=*u(6,7); fasgeti(1);
    *u(52,1)=*i(6,9); fasgeti(52);
    FOREVER{
      scrget(3,11); z=1;
      scrfld(z++,25,1);
      if(fldlen(1,2)) scrofld(z++,1,2,-1); else scrofld(z++,1,1,-1);
      scrofld(z++,1,3,42);
      if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
      scrofld(z++,6,3,42);
      if(fldlen(6,13)) scrofld(z++,6,13,-1); else scrifld(z++,fm_os5,"-");
      dispgroep(z++);
      if(sys3586) scrifld(z++,fm_os9,"Net.Marge");
      else scrifld(z++,fm_os9,"Net.Winst");
      if(fldlen(6,12)){
				scrofld(z++,6,12,-1);
				fieldspc(6,12,&pf,fmt); scrifld(z++,fmt,&nieuw[0]);
      }
      else {streepje(z++);streepje(z++);}
      if(fldlen(6,18)){
				if(sys3632==2 && inpmode!=2) scrofld(z++,6,34,-1);
				else scrofld(z++,6,18,-1);
				fieldspc(6,18,&pf,fmt); scrifld(z++,fmt,&nieuw[1]);
      }
      else {streepje(z++);streepje(z++);}
      for(g=0;g<10;g++){
				if(fldlen(6,PrNrs[g])){
					net_=nieuw[2+g];
					if(sys3894 & 1<<g) net_/=1.+*f(6,28)/100.;
					deler_=nieuw[1]; if(sys3586==1) deler_=net_;
					if(deler_){
						q_stuks=0;
						if(stuksprx[g]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
						if(q_stuks==0) q_stuks=1;
						deler_=nieuw[1]; if(sys3586==1) deler_=net_*q_stuks;
						net_winst[g]=(net_-(nieuw[1]/q_stuks))/ (deler_/q_stuks)*100.;
					}
					else net_winst[g]=0;
					scrifld(z++,fm_os6,&vptekst[g*10]);
					fieldspc(6,PrNrs[g],&pf,fmt); fmt[1]=fmt[1] & 0xBF;
					scrifld(z++,fmt,f(6,PrNrs[g]));
					fieldspc(6,PrNrs[g],&pf,fmt); scrifld(z++,fmt,&nieuw[2+g]);
					scrifld(z++,fm_of5_2,&net_winst[g]);
				}
				else {z++;streepje(z++);streepje(z++);streepje(z++);}
      }
      key=scrupd(1,0x0059);
      if(key==101) return NO;
      if(key==104) break;/* pas aan */
      if(key==105) return YES;/* pas niet aan, volgende */
      round();
    }
  }
  if(fldlen(6,12)) *f(6,12)=nieuw[0];
  if(fldlen(6,18) && inpmode!=3) *f(6,18)=nieuw[1];
  if(fldlen(6,80)) *u(6,80)=*u(6,80)|0x8000;
  for(g=0;g<10;g++){
    if(fldlen(6,PrNrs[g])) *f(6,PrNrs[g])=nieuw[2+g];
  }
  if(fldlen(6,105)){
    if(fldlen(6,12)) *f(6,106)=dnieuw[0];
    if(fldlen(6,18) && inpmode!=3) *f(6,112)=dnieuw[1];
    for(g=0;g<10;g++){
      if(fldlen(6,PrNrs[g])) *f(6,PrNrs[g+10])=dnieuw[2+g];
    }
  }
	if(fldlen(6,11)) *u(6,11)=*u(25,2);
	if(fldlen(6,198)) *u(6,198)=procid;
	if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
  fasunlck(-2); errnum=fasupd(6); fasunlck(-1);
  return YES;/* volgende */
}

static void dispgroep(int16 z)
{
  char buf[40];
 
  stcli_d(buf,(long)*u(52,1),2,1);
  buf[2]=' ';
  copy(s(52,14),&buf[3],fldlen(52,14));
  buf[3+fldlen(52,14)]='\0';
  scrifld(z,fm_os20,buf);
}
 

static void round(void)
{
  int16 g;
  for(g=2;g<12;g++){
    if(flag_prx[g-1]=='J'){
      nieuw[g]=rnd_vprx(nieuw[g],g-2);
      dnieuw[g]=rnd_vprx(dnieuw[g],g-2);
    }
  }
}
 

static void streepje(int16 z)
{
  scrifld(z,fm_os7,"      -");
}
 

static float valuta(void)
{
  int16 z;
  valu_cnv(s(6,13),def_munt,1.,1.);
  if(errnum==0) return (float)1.;
  scrnum=0;scrget(3,11);z=1;scrnum=0;
  scrifld(z++,fm_os38,"Omrekenen van vreemde valuta");
  if(fldlen(1,2)) scrofld(z++,1,2,-1); else scrofld(z++,1,1,-1);
  scrofld(z++,1,3,42);
  if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
  scrofld(z++,6,3,42);
  scrofld(z++,6,13,-1); scrchat(z-1,6);
  if(fldlen(6,9)) scrofld(z++,6,9,-1); else z++;
  z+=28;
  scrifld(z++,fm_os50,"Druk <F8> voor vervolg ... Corrigeer later !");
  errnum=39;
  scrupd(0xFFFF,0x00D9);
  return (float)-1.;
}
 

static int upd_inq(void)
{
  int16 z,curs=1,key;

  fasinit(1);fasinit(6);
	zero(nm_merk,sizeof nm_merk);zero(nm_lev,sizeof nm_lev);
  if(inq_lev) {
		fasinit(1);*u(1,1)=inq_lev;fasgeti(1);
		copy(s(1,3),nm_lev,fldlen(1,3));
	}
	if(inq_merk) {
		fasinit(1);*u(1,1)=inq_merk;fasgeti(1);
		copy(s(1,3),nm_merk,fldlen(1,3));
	}
  if(inq_art) {*u(6,1)=inq_art;fasgeti(6);}
  if(fldlen(6,9)) *i(6,9)=inq_groep;
  inq_disp='J';
  FOREVER{
    redo:
    scrget(3,12); z=1;
    scrfld(z++,25,1);
    if(fldlen(6,9)) scrfld(z++,6,9); else scrifld(z++,fm_os5," -");
    scrifld(z++,fm_uJN,&inq_disp);
		scrifld(z++,fm_us40,nm_lev);
		if(fldlen(6,101)) scrifld(z++,fm_us40,nm_merk); else z++;
    scrfld(z++,6,3);
    scrifld(z++,fm_u_AK,&manier);
    key=scrupd(curs,0x0481);
    if(manier=='K') fkey=1; else fkey=2;
    if((key==101)&&(!errnum)) break;
    else if(key==111) ovlexit(210);
    else{
      inq_groep=*i(6,9);
			if(nm_lev[0]){
				fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
				if(search(1,0)){curs=4;goto redo;}
				copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
			} else inq_lev=0;
			if(fldlen(6,101) && nm_merk[0]){
				fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
				if(search(1,0)){curs=5;goto redo;}
				copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
			} else inq_merk=0;
      if(*s(6,3)){
				if(search(6,0)){curs=6; goto redo;}
      }
      else *u(6,1)=0;
      inq_art=*u(6,1);
      if(key==108) return YES;
    }
  }
  return NO;
}

static double RoundDouble(double getal, double round)
{
  long lbd_;
                                
  if (round==0) round=0.0001; // om vieze dinges ver na komma weg te doen 
  if (getal<0.) getal-=(round/2.);
  else getal+=(round/2.);
  getal/=round;
  lbd_=(long)getal;
  return (double) (lbd_*round);
}


static void VerhoogAccijnzen(void)
{
	int16 z,key,curs=1,ret_;
	uint16 dt_prx_,dt_beg_prx_;
	char prx_op_datum_,check_op_datum_='J',show_artikel_='J';

	
	PctAccVerhoging=0; BdAccVerhogingHl=0;

	if(*u(25,2)>=45326 && *u(25,2)<=45364){ // Suikertaks 3,0849/Hl op 1/1/16   (tussen 25/12/15 en 31/01/16 )
	  dt_prx_=45334; BdAccVerhogingHl=3.0849; // 1/1/2016
  } else dt_prx_=*u(25,2); 
	if(fldlen(6,105)) prx_op_datum_='J'; 
	else {prx_op_datum_='N'; dt_prx_=*u(25,2);}
	dt_beg_prx_=dt_prx_;
  ModeAccijnsVerhoging='J'; upd_contr='J'; CalcOnlyAccijns='N';
	FOREVER{
		redo:;
		scrget(3,17); z=1;
	  if(*u(25,2)>=45326 && *u(25,2)<=45364){ // Suikertaks 3,7284/Hl op 1/1/16   (tussen 25/12/15 en 31/01/16 )
		  scraddfield(50,30,2,9);scrifld(50,VarTextFmt(27,0)," Suikertaks vanaf 1/1/2016 ");
		}
		scraddpicto(1,0,1,19,6,3,605,0,0,"Opgelet!"); 
		scrifld(z++,fm_ud3_4,&BdAccVerhogingHl);
		scrifld(z++,fm_ud2_2,&PctAccVerhoging);
		scrifld(z++,fm_udat,&dt_prx_);
		scrifld(z++,fm_uJN,&prx_op_datum_);
		scrifld(z++,fm_udat,&dt_beg_prx_);
    if(fldlen(9,1)) scrifld(z++,fm_uJN,&upd_contr);
    else {upd_contr='N'; streepje(z++);}
		scrifld(z++,fm_uJN,&CalcOnlyAccijns);
		key=scrupd(curs,0x81); curs=1;
	  if(key==101) goto endsr;
		if(BdAccVerhogingHl==0 && PctAccVerhoging==0){errnum=38;curs=1;goto redo;}
		if(BdAccVerhogingHl && PctAccVerhoging){errnum=72;curs=1;goto redo;}
		if(key==108){
			seldata.prx_klt=0;
			seldata.selp_use=NO;
			if(ovlcall(2215,2)) goto endsr;
			break;
		}
	}
//	if(DisplayWarning("Wenst U echt de prijzen/accijnzen automatisch te verhogen ?",605,1)==NO) goto endsr;
  scrget(1,7);scrupd(-3,0);
	fasinit(6);
	FOREVER{
		next_art:;
		if(faskeyi(6,2,2)) break;
		if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
		if(dt_beg_prx_ && (*u(6,11)>=dt_beg_prx_ || (fldlen(6,105) && *u(6,105)>=dt_beg_prx_))) goto next_art;
		redo_art:;
		zero(pr_buf,sizeof pr_buf); 
		fasinit(1);*u(1,1)=*u(6,7);fasgeti(1);
		if(fldlen(6,105) && *u(6,105)){copy(s(6,106),pr_buf,pr_blen);copy(s(6,190),&pr_buf[150],pr_blen69);}
		else{copy(s(6,12),pr_buf,pr_blen);copy(s(6,185),&pr_buf[150],pr_blen69);}
		if(BdAccVerhogingHl) AccVerschil=BdAccVerhogingHl/100. * *f(6,37);
		else AccVerschil=*f(6,30) * PctAccVerhoging/100.; 
		AccVerschil=roundfloat(AccVerschil,AP_afrond);
		*(float *)pos_pbf(6,12)+=AccVerschil; *(float *)pos_pbf(6,30)+=AccVerschil;
		if(prx_op_datum_=='J' || (fldlen(6,105) && *u(6,105))){
			if(YES /* *u(6,105)==0*/) *u(6,105)=dt_prx_;
		}
		copy(s(6,21),orig_vpbuf,24);  copy(s(6,185),&orig_vpbuf[50],pr_blen69);
		if(fldlen(6,105)) {copy(s(6,115),&orig_vpbuf[25],24);copy(s(6,190),&orig_vpbuf[75],pr_blen69);}
		ret_=art_upd(-1,YES);
		if(ret_==-1) goto redo_art;
		if(ret_==NO) break;
	}
endsr:;
	 ModeAccijnsVerhoging='N';
}


static void KopieerPrijs(void)
{
	int z,key,curs=3;
	uint16 n,tchg_=0,tcop_=0,g,chgbtw_,copbtw_;
	char chg_type_,cop_type_,chg_text[10],cop_text[10];
	float vrh_pct_=0,vrh_bd_=0,prxtochg_,prxtocopy_;

	chg_type_='\0';cop_type_='\0';zero(chg_text,sizeof chg_text);zero(cop_text,sizeof cop_text);
	fasinit(2);
	FOREVER{
		redo:;
		scraddf(-1,0,0,0);z=1;
		scraddfield(z,22,4,1);scrifld(z++,VarTextFmt(35,0),"Vervangen prijs door een ander type");
		scraddfield(z,10,7,0);scrifld(z++,VarTextFmt(44,0),"Prijstype dat U wenst te WIJZIGEN (0-9)    : ");
		scraddfield(z,54,7,2);scrifld(-z,fm_u_09,&chg_type_);z++;
		scraddfield(z,57,7,2);scrifld(z++,fm_os6,&chg_text);
		scraddfield(z,10,9,0);scrifld(z++,VarTextFmt(44,0),"Prijstype dat U wenst te kopieren (0-9, A) :");
		scraddfield(z,54,9,2);scrifld(-z,fm_u09A,&cop_type_);z++;
		scraddfield(z,57,9,2);scrifld(z++,fm_os6,&cop_text);
    scraddfield(z,13,10,0);scrifld(z++,VarTextFmt(30,0),"- Prijs verhogen met % ..... :");
		scraddfield(z,43,10,2);scrifld(z++,fm_uf3_2,&vrh_pct_);
    scraddfield(z,13,11,0);scrifld(z++,VarTextFmt(30,0),"- Prijs verhogen met bedrag  :");
		scraddfield(z,43,11,2);scrifld(z++,fm_uf3_2,&vrh_bd_);
		scraddfield(z,1,23,8);scrifld(z++,VarTextFmt(9,0)," F1 Stop ");
		scraddfield(z,12,23,8);scrifld(z++,VarTextFmt(14,0)," F4 selecteer ");
    key=scrupd(curs,0x249);curs=3;
	  if(key==101) goto endsr;
		zero(chg_text,sizeof chg_text);
		if(chg_type_>='0' && chg_type_<='9' && fldlen(6,PrNrs[chg_type_-'0'])) copy(&vptekst[(chg_type_-'0')*10],chg_text,6);
		else {errnum=38;curs=3;goto redo;}
		if(key==18 && fldcurs<5){curs=fldcurs+1;goto redo;}
		zero(cop_text,sizeof cop_text);
		if(cop_type_>='0' && cop_type_<='9' && fldlen(6,PrNrs[cop_type_-'0'])) copy(&vptekst[(cop_type_-'0')*10],cop_text,6);
		else if(cop_type_=='A') copy("AKprys",cop_text,6);
		else if(key!=110) {errnum=38;curs=6;goto redo;}
		if(key!=110 && chg_type_==cop_type_){errnum=38;curs=6;goto redo;}
		if(key==18){curs=fldcurs+1;goto redo;}
		if(key==104 || key==110){
			seldata.prx_klt=0;
			seldata.selp_use=NO;
			if(ovlcall(2215,5)) goto endsr;
			break;
		}
	}
	if(key==110){ // in of ex BTW zetten
		if(DisplayWarning("Wenst U echt deze prijs in/ex BTW te maken (daarna param. +.5 aanpassen!) ?",605,1)==NO) goto endsr;
    tchg_=PrNrs[chg_type_-'0']; if(sys3894 & (1<<(chg_type_-'0')))  chgbtw_=0; else chgbtw_=1; // pas op: dit is omgekeerd!
	  tcop_=tchg_;  if(chgbtw_) copbtw_=0; else copbtw_=1; // omgekeerd
	}
	else{
		if(DisplayWarning("Wenst U echt deze prijs te overschrijven ?",605,1)==NO) goto endsr;
		tchg_=PrNrs[chg_type_-'0']; if(sys3894 & (1<<(chg_type_-'0')))  chgbtw_=1; else chgbtw_=0;
	  if(cop_type_=='A') tcop_=18; else tcop_=PrNrs[cop_type_-'0']; if(tcop_>=21 && (sys3894 & (1<<(cop_type_-'0'))))  copbtw_=1; else copbtw_=0;
	}
  scrget(1,7);scrupd(-3,0);
  fasinit(6);
  n=0;scrnum=0;
  FOREVER{
		next6:;
    *u(6,1)=++n;
    g=fasgeti(6);
    if(g==47)break;
    if(g!=46){
  		if(DirCall_DRK2215_SelectArtikel()==NO) goto next6;
			prxtochg_=*f(6,tchg_); prxtocopy_=*f(6,tcop_);
			*f(6,tchg_)=prxtocopy_;
			if(*f(6,28) && chgbtw_!=copbtw_){
				if(chgbtw_) *f(6,tchg_)*=1.+ *f(6,28)/100.;
				else *f(6,tchg_)/=1.+ *f(6,28)/100;
			}
      if(vrh_pct_) *f(6,tchg_)*=1.+ vrh_pct_/100.;
			if(vrh_bd_) *f(6,tchg_)+=vrh_bd_;
			*f(6,tchg_)=rnd_vprx(*f(6,tchg_),chg_type_-'0');
			if(fldlen(6,198)) *u(6,198)=procid;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			fasupd(6);
		}
  }
	endsr:;
}



static void CalcAKFiche(void)
{
  int16 j,k;
  float ap_brut, ap_net, ap_stat, ap_, bd_acc;
 
  ap_brut=*f(11,6);
  ap_net=ap_brut;ap_stat=ap_brut;bd_acc=*f(6,30);
  if(ap_brut==0){
    for(k=0;k<5;k++) *f(11,15+k*10)=0;
    goto calc_ok;
  }
  for(k=0;k<5;k++){
    if(*f(11,10+k*10)){
      if(*s(11,11+k*10)=='H') *f(11,15+k*10)=*f(11,10+k*10) * *f(6,37)/100; // HL-korting
      else if(*s(11,11+k*10)=='%'){ // % korting
				ap_=ap_brut;
				if(*s(11,12+k*10)!='B'){
					for(j=0;j<k;j++){
						if(*s(11,14+j*10)) ap_-=*f(11,15+j*10);
					}
				}
				if(*s(11,13+k*10)!='I') ap_-=bd_acc;
				*f(11,15+k*10)=roundfloat((ap_ * *f(11,10+k*10)/100.),AP_afrond);
			}
			else *f(11,15+k*10)=*f(11,10+k*10); // eur korting 
		} else *f(11,15+k*10)=0;
  }
  calc_ok:;
  ap_net=ap_brut;ap_stat=ap_brut;
  for(k=0;k<5;k++){
    ap_stat-=*f(11,15+k*10);
    if(*s(11,14+k*10)=='F') ap_net-=*f(11,15+k*10);
  }
  *f(11,60)=roundfloat(ap_net,AP_afrond);
  if(fldlen(11,7)){
    ap_stat=valu_cnv(s(11,7),def_munt,(double)ap_stat,(double)0.001);
  }
  *f(11,61)=ap_stat;/* steeds in DEF-munt */
}


static bool CheckKeyWord(char *keyword)
{
	int k;
	char kar_;
	  
	if((k=SearchString.Find(keyword))>0){
		kar_=SearchString.GetAt(k-1);
		if(keyword[0]>='0' && keyword[0]<='9' && ((kar_>='0' && kar_<='9') || kar_==',' || kar_=='.' || kar_=='+')){
			return false;
		} 
		else return true;
	}
	return false;
}



static void CheckInhoud(void)
{
	char anm_[50],ean_[15];
	int16 cnt_,start_,k,z,key,curs;
	float NewVol_;
	CString cstr_,artnaam_;

	if (!TbArtikel) {
		TbArtikel = new _TbArtikel[DIM_ARTIKEL]; 
		memset(TbArtikel,0,DIM_ARTIKEL * sizeof TbArtikel[0]);
	}

	fasinit(6);fasinit(1);
	zero(nm_merk,sizeof nm_merk);zero(nm_lev,sizeof nm_lev);
  inq_groep=0;inq_art=0;upd_contr='J';curs=1;
  FOREVER{
    redo:
    scrget(3,15);z=1; 
    scrfld(z++,25,1);
		scrifld(z++,fm_us40,nm_lev);
		if(fldlen(6,101)) scrifld(z++,fm_us40,nm_merk); else z++;
    scrifld(z++,fm_uu2,&inq_groep);
    key=scrupd(curs,0x0481);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) return;
		if(nm_lev[0]){
      fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=4;goto redo;}
	    copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
    } else inq_lev=0;
	  if(fldlen(6,101) && nm_merk[0]){
      fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=5;goto redo;}
	    copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
    } else inq_merk=0;
    if(key==108) break;
  }
			
	MaxArtikel=0;
	fasinit(6);cnt_=0;scrget(1,7);scrupd(-3,0);cnt_=0;
	FOREVER{
		next_art:;
		if(faskeyi(6,2,2)) break;
		if(inq_lev && *u(6,7)!=inq_lev) goto next_art;
		if(inq_merk && *u(6,101)!=inq_merk) goto next_art;
		if(inq_groep && *u(6,9)!=inq_groep)  goto next_art;
  	cnt_++;if((cnt_%1000)==0){scrnum=0;scrget(1,7);scrupd(-3,0);}
		if(*u(6,9)!=99){
			zero(anm_,sizeof anm_);	copy0(s(6,3),anm_,fldlen(6,3));
			cstr_=CString(anm_);cstr_.MakeUpper(); copy((char *)(LPCTSTR)cstr_,anm_,cstr_.GetLength());// uppercase
			zero(ean_,sizeof ean_); if(*s(6,71)) copy0(s(6,71),ean_,fldlen(6,71)); else copy0(s(6,70),ean_,fldlen(6,70)); 
			NewVol_=ExecOneVol(anm_,ean_,*f(6,37),*f(6,31));
		}
	}
	if(MaxArtikel==0) goto endsr;
/* 
for(k=0;k<MaxArtikel;k++){
			fasinit(6);*u(6,1)=TbArtikel[k].RecordNr; fasgeti(6);
			*f(6,31)=TbArtikel[k].NewAantal;*f(6,37)=TbArtikel[k].NewInhoud;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			fasupd(6);
}
goto endsr;
*/ 
	start_=0;
	FOREVER{
		scrnum=0;scrget(3,16);z=1;
		scraddpicto(50,0,75,23,4,2,578,0,0,"Pas ALLE artikels aan");
		for(k=start_;k<start_+20;k++){
			if(k>=MaxArtikel) break;
			fasinit(6);*u(6,1)=TbArtikel[k].RecordNr; fasgeti(6);
			scrofld(z++,6,3,-1);

			scrifld(z++,fm_od4_0,&TbArtikel[k].OldAantal);
			scrifld(z++,fm_ud4_0,&TbArtikel[k].NewAantal); 
			scrifld(z++,fm_od4_2,&TbArtikel[k].OldInhoud);
			scrifld(z++,fm_ud4_2,&TbArtikel[k].NewInhoud);
			scrofld(z++,6,NrKassaBakPr,-1);
			if(TbArtikel[k].updated) scraddpicto(10+k-start_,0,66,2+k-start_,2,1,86,1034,0,"Pas artikel aan");
			else scraddpicto(10+k-start_,0,66,2+k-start_,2,1,578,0,0,"Pas artikel aan");
		}
		key=scrupd(1,0x7);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5010 && key<5030){
			k=start_+key-5010;
			fasinit(6);*u(6,1)=TbArtikel[k].RecordNr; fasgeti(6);
			*f(6,31)=TbArtikel[k].NewAantal;*f(6,37)=TbArtikel[k].NewInhoud;
			if(fldlen(6,198)) *u(6,198)=procid;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			fasupd(6);
			TbArtikel[k].OldAantal=TbArtikel[k].NewAantal;
			TbArtikel[k].OldInhoud=TbArtikel[k].NewInhoud;
			TbArtikel[k].updated=YES;
		}
		if(key==5050){
			for(k=start_;k<start_+20;k++){
				if(k>=MaxArtikel) break;
				fasinit(6);*u(6,1)=TbArtikel[k].RecordNr; fasgeti(6);
				*f(6,31)=TbArtikel[k].NewAantal;*f(6,37)=TbArtikel[k].NewInhoud;
				if(fldlen(6,198)) *u(6,198)=procid;
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				fasupd(6);
				TbArtikel[k].OldAantal=TbArtikel[k].NewAantal;
				TbArtikel[k].OldInhoud=TbArtikel[k].NewInhoud;
				TbArtikel[k].updated=YES;
			}
		}
		if(key==101) break;
		if(key==102) start_-=20;
		if(key==103) {start_+=20; if(start_>=MaxArtikel) start_-=20;}
		if(start_<0) start_=0;
	}
endsr:;
		if (TbArtikel) {delete TbArtikel; TbArtikel=0;}
}

static float  ExecOneVol(char* Name, char* Ean, float ArtVol, float ArtCnt)
{
	float DMVol=0;
	float ItmVol=0.;
	float ItmCnt=0;
	float cnt_;
	  
	CString N=Name;
	N.Replace("O","0");
	N.Replace("1664","    ");
	N.Replace(" 2.4 X","");
	N.Replace(" 1X6LT "," 6X1LT ");
	SearchString=N;


	
	//if (CheckKeyWord(" 5 C")) ItmVol=0.05;
	//else if (CheckKeyWord("5 CL")) ItmVol=0.05;
	//else if (CheckKeyWord("5CL")) ItmVol=0.05;
	if (CheckKeyWord("0,05 L")) ItmVol=0.05;
  else if (CheckKeyWord("0,05L")) ItmVol=0.05;
	else if (CheckKeyWord("0.05 L")) ItmVol=0.05;
	else if (CheckKeyWord("0.05L")) ItmVol=0.05;
	else if (CheckKeyWord("0,050 L")) ItmVol=0.05;
	else if (CheckKeyWord("0,050L")) ItmVol=0.05;
	else if (CheckKeyWord("0.050 L")) ItmVol=0.05;
	else if (CheckKeyWord("0.050L")) ItmVol=0.05;

	else if (CheckKeyWord(" 15 C")) ItmVol=0.15;
	else if (CheckKeyWord("15 CL")) ItmVol=0.15;
	else if (CheckKeyWord("15CL")) ItmVol=0.15;
	else if (CheckKeyWord("0,15 L")) ItmVol=0.15;
	else if (CheckKeyWord("0,15L")) ItmVol=0.15;
	else if (CheckKeyWord("0.15 L")) ItmVol=0.15;
	else if (CheckKeyWord("0.15L")) ItmVol=0.15;
	else if (CheckKeyWord("0,150 L")) ItmVol=0.15;
	else if (CheckKeyWord("0,150L")) ItmVol=0.15;
	else if (CheckKeyWord("0.150 L")) ItmVol=0.15;
	else if (CheckKeyWord("0.150L")) ItmVol=0.15;


	else if (CheckKeyWord(" 20 C")) ItmVol=0.20;
	else if (CheckKeyWord("20 CL")) ItmVol=0.20;
	else if (CheckKeyWord("20CL")) ItmVol=0.20;
	else if (CheckKeyWord("1/5")) ItmVol=0.20;
	else if (CheckKeyWord("0,20 L")) ItmVol=0.2;
	else if (CheckKeyWord("0,20L")) ItmVol=0.2;
	else if (CheckKeyWord("0.20 L")) ItmVol=0.2;
	else if (CheckKeyWord("0.20L")) ItmVol=0.2;
	else if (CheckKeyWord("0,2 L")) ItmVol=0.2;
	else if (CheckKeyWord("0,2L")) ItmVol=0.2;
	else if (CheckKeyWord("0.2 L")) ItmVol=0.2;
	else if (CheckKeyWord("0.2L")) ItmVol=0.2;
	else if (CheckKeyWord("24x20")) ItmVol=0.2;

	else if (CheckKeyWord(" 25 C")) ItmVol=0.25;
	else if (CheckKeyWord("25 CL")) ItmVol=0.25;
	else if (CheckKeyWord("25CL")) ItmVol=0.25;
	else if (CheckKeyWord("1/4")) ItmVol=0.25;
	else if (CheckKeyWord("0,25 L")) ItmVol=0.25;
	else if (CheckKeyWord("0,25L")) ItmVol=0.25;
	else if (CheckKeyWord("0.25 L")) ItmVol=0.25;
	else if (CheckKeyWord("0.25L")) ItmVol=0.25;
	else if (CheckKeyWord("0,250 L")) ItmVol=0.25;
	else if (CheckKeyWord("0,250L")) ItmVol=0.25;
	else if (CheckKeyWord("0.250 L")) ItmVol=0.25;
	else if (CheckKeyWord("0.250L")) ItmVol=0.25;
	else if (CheckKeyWord("X25L")) ItmVol=0.25;
	else if (CheckKeyWord("X25 L")) ItmVol=0.25;
	else if (CheckKeyWord("X025L")) ItmVol=0.25;
	else if (CheckKeyWord("X025 L")) ItmVol=0.25;

	else if (CheckKeyWord("0,275 L")) ItmVol=0.275;
	else if (CheckKeyWord("0,275L")) ItmVol=0.275;
	else if (CheckKeyWord("0.275 L")) ItmVol=0.275;
	else if (CheckKeyWord("0.275L")) ItmVol=0.275;

	else if (CheckKeyWord(" 33 C")) ItmVol=0.33;
	else if (CheckKeyWord("33 CL")) ItmVol=0.33;
	else if (CheckKeyWord("33CL")) ItmVol=0.33;
	else if (CheckKeyWord("1/3")) ItmVol=0.33;
	else if (CheckKeyWord("0,33 L")) ItmVol=0.33;
	else if (CheckKeyWord("0,33L")) ItmVol=0.33;
	else if (CheckKeyWord("0.33 L")) ItmVol=0.33;
	else if (CheckKeyWord("0.33L")) ItmVol=0.33;
	else if (CheckKeyWord("0.33 CL")) ItmVol=0.33;
	else if (CheckKeyWord("0.33CL")) ItmVol=0.33;
	else if (CheckKeyWord("0,33 CL")) ItmVol=0.33;
	else if (CheckKeyWord("0,33CL")) ItmVol=0.33;
	else if (CheckKeyWord("24X33")) ItmVol=0.33;

	else if (CheckKeyWord(" 35 C")) ItmVol=0.35;
	else if (CheckKeyWord("0,35 L")) ItmVol=0.35;
	else if (CheckKeyWord("0,35L")) ItmVol=0.35;
	else if (CheckKeyWord("0.35 L")) ItmVol=0.35;
	else if (CheckKeyWord("0.35L")) ItmVol=0.35;
	else if (CheckKeyWord("0,350 L")) ItmVol=0.35;
	else if (CheckKeyWord("0,350L")) ItmVol=0.35;
	else if (CheckKeyWord("0.350 L")) ItmVol=0.35;
	else if (CheckKeyWord("0.350L")) ItmVol=0.35;
	else if (CheckKeyWord("X35L")) ItmVol=0.35;
	else if (CheckKeyWord("X35 L")) ItmVol=0.35;      

	else if (CheckKeyWord("37,5 CL")) ItmVol=0.375;
	else if (CheckKeyWord("37,5CL")) ItmVol=0.375;
	else if (CheckKeyWord("37.5 CL")) ItmVol=0.375;
	else if (CheckKeyWord("37.5CL")) ItmVol=0.375;
	else if (CheckKeyWord("375CL")) ItmVol=0.375;
	else if (CheckKeyWord("37,5L")) ItmVol=0.375;
	else if (CheckKeyWord("37.5L")) ItmVol=0.375;
	else if (CheckKeyWord("0,375 L")) ItmVol=0.375;
	else if (CheckKeyWord("0,375L")) ItmVol=0.375;
	else if (CheckKeyWord("0.375 L")) ItmVol=0.375;
	else if (CheckKeyWord("0.375L")) ItmVol=0.375;

	else if (CheckKeyWord(" 30 C")) ItmVol=0.3;
	else if (CheckKeyWord("0,30 L")) ItmVol=0.3;
	else if (CheckKeyWord("0,30L")) ItmVol=0.3;
	else if (CheckKeyWord("0.30 L")) ItmVol=0.3;
	else if (CheckKeyWord("0.30L")) ItmVol=0.3;
	else if (CheckKeyWord("0,3 L")) ItmVol=0.3;
	else if (CheckKeyWord("0,3L")) ItmVol=0.3;
	else if (CheckKeyWord("0.3 L")) ItmVol=0.3;
	else if (CheckKeyWord("0.3L")) ItmVol=0.3;

	else if (CheckKeyWord(" 50 C")) ItmVol=0.5;
	else if (CheckKeyWord("50 CL")) ItmVol=0.5;
	else if (CheckKeyWord("50CL")) ItmVol=0.5;
	else if (CheckKeyWord("1/2")) ItmVol=0.5;
	else if (CheckKeyWord("0,50 L")) ItmVol=0.5;
	else if (CheckKeyWord("0,50L")) ItmVol=0.5;
	else if (CheckKeyWord("0.50 L")) ItmVol=0.5;
	else if (CheckKeyWord("0.50L")) ItmVol=0.5;
	else if (CheckKeyWord("0,5 L")) ItmVol=0.5;
	else if (CheckKeyWord("0,5L")) ItmVol=0.5;
	else if (CheckKeyWord("0.5 L")) ItmVol=0.5;
	else if (CheckKeyWord("0.5L")) ItmVol=0.5;

	else if (CheckKeyWord(" 70 C")) ItmVol=0.70;
	else if (CheckKeyWord("70 CL")) ItmVol=0.70;
	else if (CheckKeyWord("70CL")) ItmVol=0.70;
	else if (CheckKeyWord("0,70 L")) ItmVol=0.70;
	else if (CheckKeyWord("0,70L")) ItmVol=0.70;
	else if (CheckKeyWord("0.70 L")) ItmVol=0.70;
	else if (CheckKeyWord("0.70L")) ItmVol=0.70;

	if (ItmVol>0.01) goto GetCount; // om de compiler blocks nested too deeply op te lossen

	else if (CheckKeyWord(" 75 C")) ItmVol=0.75;
	else if (CheckKeyWord("75CL")) ItmVol=0.75;
	else if (CheckKeyWord("75 CL")) ItmVol=0.75;
	else if (CheckKeyWord("75CL")) ItmVol=0.75;
	else if (CheckKeyWord("X75C")) ItmVol=0.75;
	else if (CheckKeyWord("X 75C")) ItmVol=0.75;
	else if (CheckKeyWord("3/4")) ItmVol=0.75;
	else if (CheckKeyWord("0,75 L")) ItmVol=0.75;
	else if (CheckKeyWord("0,75L")) ItmVol=0.75;
	else if (CheckKeyWord("0.75 L")) ItmVol=0.75;
	else if (CheckKeyWord("0.75L")) ItmVol=0.75;
	else if (CheckKeyWord("0.75 CL")) ItmVol=0.75;
	else if (CheckKeyWord("0.75CL")) ItmVol=0.75;
	else if (CheckKeyWord("0,750 L")) ItmVol=0.75;
	else if (CheckKeyWord("0,750L")) ItmVol=0.75;
	else if (CheckKeyWord("0.750 L")) ItmVol=0.75;
	else if (CheckKeyWord("0.750L")) ItmVol=0.75;
	else if (CheckKeyWord("X,75L")) ItmVol=0.75;
	else if (CheckKeyWord("X.75L")) ItmVol=0.75;
	else if (CheckKeyWord("X,75 L")) ItmVol=0.75;
	else if (CheckKeyWord("X.75 L")) ItmVol=0.75;

	else if (CheckKeyWord(" 100 C")) ItmVol=1.;
	else if (CheckKeyWord("1 L")) ItmVol=1.;
	else if (CheckKeyWord("1L")) ItmVol=1.;
	else if (CheckKeyWord("1/1")) ItmVol=1.;
	else if (CheckKeyWord("100 CL")) ItmVol=1.;
	else if (CheckKeyWord("100CL")) ItmVol=1.;
	else if (CheckKeyWord("1,00 L")) ItmVol=1.;
	else if (CheckKeyWord("1,00L")) ItmVol=1.;
	else if (CheckKeyWord("1.00 L")) ItmVol=1.;
	else if (CheckKeyWord("1.00L")) ItmVol=1.;

	else if (CheckKeyWord("1.5 L")) ItmVol=1.5;
  else if (CheckKeyWord("1.5L")) ItmVol=1.5;
	else if (CheckKeyWord("1,5 L")) ItmVol=1.5;
  else if (CheckKeyWord("1,5L")) ItmVol=1.5;
	else if (CheckKeyWord("1.50 L")) ItmVol=1.5;
  else if (CheckKeyWord("1.50L")) ItmVol=1.5;
	else if (CheckKeyWord("1,50 L")) ItmVol=1.5;
  else if (CheckKeyWord("1,50L")) ItmVol=1.5;
  else if (CheckKeyWord(" 150 C")) ItmVol=1.5;
	else if (CheckKeyWord("6x1.5")) ItmVol=1.5;
	else if (CheckKeyWord("6x150")) ItmVol=1.5;

	else if (CheckKeyWord("6X1")) ItmVol=1.;
	else if (CheckKeyWord("12X1")) ItmVol=1.;

	else if (CheckKeyWord(" 125 C")) ItmVol=1.25;
	else if (CheckKeyWord("1,25 L")) ItmVol=1.25;
	else if (CheckKeyWord("1,25L")) ItmVol=1.25;
	else if (CheckKeyWord("1.25 L")) ItmVol=1.25;
	else if (CheckKeyWord("1.25L")) ItmVol=1.25;
	else if (CheckKeyWord("1,250 L")) ItmVol=1.25;
	else if (CheckKeyWord("1,250L")) ItmVol=1.25;
	else if (CheckKeyWord("1.250 L")) ItmVol=1.25;
	else if (CheckKeyWord("1.250L")) ItmVol=1.25;
	
	else if (CheckKeyWord("2.0 L")) ItmVol=2.0;
  else if (CheckKeyWord("2.0L")) ItmVol=2.0;
	else if (CheckKeyWord("2,0 L")) ItmVol=2.0;
  else if (CheckKeyWord("2,0L")) ItmVol=2.0;
	else if (CheckKeyWord("2.00 L")) ItmVol=2.0;
  else if (CheckKeyWord("2.00L")) ItmVol=2.0;
	else if (CheckKeyWord("2,00 L")) ItmVol=2.0;
  else if (CheckKeyWord("2,00L")) ItmVol=2.0;

  else if (CheckKeyWord("15 L")) ItmVol=15.;
	else if (CheckKeyWord("15L")) ItmVol=15.;
  else if (CheckKeyWord("18 L")) ItmVol=18.;
	else if (CheckKeyWord("18L")) ItmVol=18.;
	else if (CheckKeyWord("25 L")) ItmVol=25.;
	else if (CheckKeyWord("25L")) ItmVol=25.;
	else if (CheckKeyWord("20 L")) ItmVol=20.;
	else if (CheckKeyWord("20L")) ItmVol=20.;
	else if (CheckKeyWord("30 L")) ItmVol=30.;
	else if (CheckKeyWord("30L")) ItmVol=30.;
	else if (CheckKeyWord("50 L")) ItmVol=50.;
	else if (CheckKeyWord("50L")) ItmVol=50.;
	else if (CheckKeyWord("5 L")) ItmVol=5.;
	else if (CheckKeyWord("5L")) ItmVol=5.;
	else if (CheckKeyWord("6 L")) ItmVol=6.;
	else if (CheckKeyWord("6L")) ItmVol=6.;


GetCount:;
	if (CheckKeyWord("4X6X")) ItmCnt=24;
	else if (CheckKeyWord("6X4X")) ItmCnt=24;
	else if (CheckKeyWord("3X8X")) ItmCnt=24;
	else if (CheckKeyWord("8X3X")) ItmCnt=24;
	else if (CheckKeyWord("12 X")) ItmCnt=12;
	else if (CheckKeyWord("12X")) ItmCnt=12;
	else if (CheckKeyWord("18X")) ItmCnt=18;
	else if (CheckKeyWord("18 X")) ItmCnt=18;
	else if (CheckKeyWord("20 X")) ItmCnt=20;
	else if (CheckKeyWord("20X")) ItmCnt=20;
	else if (CheckKeyWord("24 X")) ItmCnt=24;
	else if (CheckKeyWord("24X")) ItmCnt=24;
	else if (CheckKeyWord("30 X")) ItmCnt=30;
	else if (CheckKeyWord("30X")) ItmCnt=30;
	else if (CheckKeyWord("10X")) ItmCnt=10;
	else if (CheckKeyWord("1X")) ItmCnt=1;
	else if (CheckKeyWord("1 X")) ItmCnt=1;
	else if (CheckKeyWord("3X")) ItmCnt=3;
	
	else if (CheckKeyWord("X 12")) ItmCnt=12;
	else if (CheckKeyWord("X12")) ItmCnt=12;
	else if (CheckKeyWord("X18") /* && ItmVol<1*/) ItmCnt=18;
	else if (CheckKeyWord("X 18") /*&& ItmVol<1*/) ItmCnt=18;
	else if (CheckKeyWord("X 20") && ItmVol<1) ItmCnt=20;
	else if (CheckKeyWord("X20") && ItmVol<1) ItmCnt=20;
	else if (CheckKeyWord("X 24") /*&& ItmVol<1*/) ItmCnt=24;
	else if (CheckKeyWord("X24") /*&& ItmVol<1*/) ItmCnt=24;
	else if (CheckKeyWord("28X") /*&& ItmVol<1*/) ItmCnt=28;
	else if (CheckKeyWord("X28")/* && ItmVol<1*/) ItmCnt=28;
	else if (CheckKeyWord("X 30") && ItmVol<1) ItmCnt=30;
	else if (CheckKeyWord("X30") && ItmVol<1) ItmCnt=30;
	else if (CheckKeyWord("X 6")) ItmCnt=6;
	else if (CheckKeyWord("X6")) ItmCnt=6;
	else if (CheckKeyWord("X 8")) ItmCnt=8;
	else if (CheckKeyWord("X8")) ItmCnt=8;

	else if (CheckKeyWord("3+1")) ItmCnt=4;

	else if (CheckKeyWord("4+2")) ItmCnt=6;
	else if (CheckKeyWord("5+1")) ItmCnt=6;

	else if (CheckKeyWord("CL4")) ItmCnt=4;
	else if (CheckKeyWord("CL8")) ItmCnt=8;


	else if (CheckKeyWord("4 X")) ItmCnt=4;
	else if (CheckKeyWord("4X")) ItmCnt=4;
	else if (CheckKeyWord("6 X")) ItmCnt=6;
	else if (CheckKeyWord("6X")) ItmCnt=6;
	else if (CheckKeyWord("8 X")) ItmCnt=8;
	else if (CheckKeyWord("8X")) ItmCnt=8;
		 
	else if (CheckKeyWord("24 BTL")) ItmCnt=24;
	else if (CheckKeyWord("24BTL")) ItmCnt=24;
	else if (CheckKeyWord("24 ST")) ItmCnt=24;
	else if (CheckKeyWord("24ST")) ItmCnt=24;
	else if (CheckKeyWord("24 FL")) ItmCnt=24;
	else if (CheckKeyWord("24FL")) ItmCnt=24;
	else if (CheckKeyWord("18+6")) ItmCnt=24;
	else if (CheckKeyWord("19+5")) ItmCnt=24;
	else if (CheckKeyWord("20+4")) ItmCnt=24;
	else if (CheckKeyWord("21+3")) ItmCnt=24;
	else if (CheckKeyWord("22+2")) ItmCnt=24;
	else if (CheckKeyWord("23+1")) ItmCnt=24;

	else if (CheckKeyWord("12 BTL")) ItmCnt=12;
	else if (CheckKeyWord("12BTL")) ItmCnt=12;
	else if (CheckKeyWord("12 ST")) ItmCnt=12;
	else if (CheckKeyWord("12ST")) ItmCnt=12;
	else if (CheckKeyWord("12 FL")) ItmCnt=12;
	else if (CheckKeyWord("12FL")) ItmCnt=12;

	else if (CheckKeyWord("6 BTL")) ItmCnt=6;
	else if (CheckKeyWord("6BTL")) ItmCnt=6;
	else if (CheckKeyWord("6 ST")) ItmCnt=6;
	else if (CheckKeyWord("6ST")) ItmCnt=6;
	else if (CheckKeyWord("6 FL")) ItmCnt=6;
	else if (CheckKeyWord("6FL")) ItmCnt=6;

  else if (CheckKeyWord("4 BTL")) ItmCnt=4;
	else if (CheckKeyWord("4BTL")) ItmCnt=4;
	else if (CheckKeyWord("4 ST")) ItmCnt=4;
	else if (CheckKeyWord("4ST")) ItmCnt=4;
	else if (CheckKeyWord("4 FL")) ItmCnt=4;
	else if (CheckKeyWord("4FL")) ItmCnt=4;

  else if (CheckKeyWord("CLIP12")) ItmCnt=12;
	else if (CheckKeyWord("12 BTL")) ItmCnt=12;
	else if (CheckKeyWord("12BTL")) ItmCnt=12;
	else if (CheckKeyWord("6 BTL")) ItmCnt=6;
	else if (CheckKeyWord("6BTL")) ItmCnt=6;
	else if (CheckKeyWord("4 BTL")) ItmCnt=4;
	else if (CheckKeyWord("4BTL")) ItmCnt=4;

	if(ItmCnt<=1 && *f(6,25) && *f(6,26) && *f(6,26)<*f(6,25)){
		cnt_=*f(6,25) / *f(6,26);
	  if(cnt_>=5 && cnt_<=7) cnt_=6;
	  else if(cnt_>=11 && cnt_<=13) cnt_=12;
	  else if(cnt_>=23 && cnt_<=25) cnt_=24;
	  else cnt_=0;
		if(cnt_) {ItmCnt=cnt_; ArtVol*=cnt_;}
	}

	ItmVol=RoundDouble((double)(ItmVol),0.001);ItmCnt=RoundDouble((double)(ItmCnt),1);
	ArtVol=RoundDouble((double)(ArtVol),0.001);ArtCnt=RoundDouble((double)(ArtCnt),1);

	if(ItmVol==0 || ItmCnt==0){ 
		if(ItmVol==0 && ItmCnt==0){// als niks gevonden en fiche is goed ingevuld, dan data van fiche nemen
			if(ArtVol && ArtCnt){ItmVol=ArtVol/ArtCnt; ItmCnt=ArtCnt;}
		}
		else if(ItmVol){
			if(ItmVol>=5) ItmCnt=1;  // vat of zo
			else if(ArtVol){
				int count_=RoundDouble((double)(ArtVol/ItmVol),1);
				if(count_==RoundDouble((double)(ArtVol/ItmVol),0.01)) ItmCnt=count_;
			}
			else if(ArtCnt) ItmCnt=ArtCnt;
  		if(ItmCnt==0) ItmCnt=1;
		}
		else if(ItmCnt && ArtVol){
			ItmVol=ArtVol/ItmCnt;
		}
	}


	// let op : hieronder zijn alle O vervangen door 0 ! (zie bovenaan)
	if (N.Find("G0BELET")>=0) ItmVol=0;
	else if (N.Find("TASSES")==0) ItmVol=0;
	else if (N.Find("EC0TAX")==0) ItmVol=0;
	else if (N.Find("BIERGLAS")==0) ItmVol=0;
	else if (N.Find("K00LZUUR")>=0) ItmVol=0;
	else if (N.Find("VERRE")==0) ItmVol=0;
	else if (N.Find("GLAS")==0) ItmVol=0;
	else if (N.Find("BEKER")==0) ItmVol=0;
	else if (N.Find("DRINKBEKER")==0) ItmVol=0;

	DMVol=ItmVol*ItmCnt;
  if (MaxArtikel<DIM_ARTIKEL && (!(ArtVol>(DMVol*0.95) || DMVol<0.001) || (*f(6,NrKassaStkPr) && ArtCnt<=1 && *f(6,NrKassaStkPr)<*f(6,NrKassaBakPr)))){ // gewijzigd of stuksprijs is toch lager dan bak!
		TbArtikel[MaxArtikel].RecordNr=*u(6,1);
		TbArtikel[MaxArtikel].OldAantal=ArtCnt;
		TbArtikel[MaxArtikel].OldInhoud=ArtVol;
		TbArtikel[MaxArtikel].NewAantal=ItmCnt;
		TbArtikel[MaxArtikel].NewInhoud=DMVol;
		MaxArtikel++;
	}

//	TRACE("Vol=%.2f ipv %f (%s %s %f)\r\n",DMVol,ArtVol,Name,Ean,ArtVol,ArtCnt);
//
//	CString cstr;
//	cstr.Format(_T("%.2f;%.2f;\"%s\";\"'%s\";%.2f;%.2f\r\n"),ItmCnt,DMVol,Name,Ean,ArtCnt,ArtVol);
//	CFile filspec;
//	CString FileNam;
//	FileNam.Format(_T("..\\DMC\\VOL-%06.2f.csv"),DMVol);
//	if (filspec.Open(FileNam,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite,NULL)) {
//		filspec.SeekToEnd();
//		filspec.Write(cstr,cstr.GetLength());
//		filspec.Close();
//	}
//
//	if (ArtVol>(DMVol*0.95) || DMVol<0.001) return ArtVol; // ongewijzigd !
//
//	if (filspec.Open("..\\DMC\\VOL-CORR.csv",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite,NULL)) {
//		filspec.SeekToEnd();
//		filspec.Write(cstr,cstr.GetLength());
//		filspec.Close();
//	}

	return DMVol;
}



static void initload(int16 singlemode_)
{
  int16 j,k,g;
									
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);
	if(fldlen(16,1)) fileopen(13);
  chk_bkh=NO;if(fldlen(3,0)){fileopen(3);chk_bkh=YES;}
  sysget( 294,4,def_munt);
  sysget(1918,2,&sear_stt);
  sysget(2830,24,(char *)&sys2830[0]);
	sysget(3242,2,&sys3242);
	sysget(3654,16,(char *)&sys2830[6]);
  sysget(3586,2,&sys3586);
  sysget(3588,2,&sys3588);
  sysget(3598,6,b3598);
  sysget(3604,2,&b3604);
  sysget(3606,2,&b3606);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3632,2,&sys3632);
	sysget(3652,2,&sys3652);
  sysget(3720,2,&sys3720);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(4610,60,vptekst);
  sysget(4670,6,stuksprx);
  sysget(4740,40,&vptekst[60]);
  sysget(4780,4,&stuksprx[6]);
  if(fldlen(6,130) && fldlen(25,8) && *u(25,8)) prx_loff=*u(25,8);
  else prx_loff=0;
  pr_blen=s(6,31)-s(6,12); pr_blen69=s(6,190)-s(6,185);
  sysget(3678,2,&def_taal);
  stu11_exist=NO; if(fldlen(11,0)) stu11_exist=YES;
  fmt_get(6,21);k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;
  fmt_get(6,18);k=fmt[3];
  AP_afrond=(float)1.; 
	for(j=0;j<k;j++) AP_afrond=AP_afrond/(float)(10.);
  if(sys3614<prx_afrond) sys3614=prx_afrond;/* afstemmen op decimalen op scherm */
  for(k=0;k<10;k++) if(sys2830[k]) break;
  if(k>=10){/* EERSTE KEER JUIST ZETTEN */
    for(k=0;k<10;k++) sys2830[k]=prx_afrond;
    sysput(2830,24,(char *)&sys2830[0]);
		sysput(3654,16,(char *)&sys2830[6]);
  }
  calctype=s(52,22);
  zero((char *)&tbgr[0].rec,sizeof tbgr);
  p_max_grp=0;sgrp_used=NO;
	if(singlemode_==0){// via hoofdmenu aangekomen
		for(k=1;k<100;k++){
			fasinit(52);*u(52,1)=k;
			g=fasgeti(52);
			if(g==0 && *s(52,14)) tbgr[p_max_grp++].rec=k;
		}
		for(k=0;k<100;k++) tbgr[k].select='N';
		if(fldlen(6,105)) chk_oldp();
	}
	sysget(3896,6,&sys3896[0]);  // bak en stuks prjs bepalen 
	j=0;
  for(k=0;k<6;k++){
    NrKassaBakPr=sys3896[k]-'0';
    if(NrKassaBakPr>=0 && NrKassaBakPr<=9 && fldlen(6,PrNrs[NrKassaBakPr])) j++;
		else break;
  }
	NrKassaBakPr=PrNrs[sys3896[0]-'0']; if(NrKassaBakPr<21)  NrKassaBakPr=21;
	NrKassaStkPr=0; if(j) NrKassaStkPr=PrNrs[sys3896[j-1]-'0']; if(NrKassaStkPr<21)  NrKassaStkPr=NrKassaBakPr;
}

static void chk_oldp(void)
{
  uint16 n,g,dt_max_;
  dt_max_=*u(25,2)-30;
  scrget(1,7);scrupd(-3,0);
  fasinit(6);
  n=0;scrnum=0;
  FOREVER{
    *u(6,1)=++n;
    g=fasgeti(6);
    if(g==47)break;
    if(g!=46){
      if(*u(6,105)!=0 && *u(6,105)<dt_max_){
				scrnum=0;scrget(1,170);
				scrifld(5,fm_os78,"Sommige artikels hebben een prijswijziging van MEER DAN 1 MAAND oud !!");
				scrifld(7,fm_os78,"Om problemen te vermijden, gelieve deze eerst DEFINITIEF te maken.");
				scrifld(9,fm_os78,"Dit doet U via punt 5 (Vervangen huidige prijzen...) op deze menu.");
				scrifld(18,fm_os78,"Druk op F8 om verder te gaan ...");
				scrupd(-1,0x81);
				break;
      }
    }
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
 

static int used(char *b, int16 len)
{
  while (len-->0)
    if(*b++!=0xFE) return YES;
  return NO;
}

static void nextline(void)
{
  linfree=prtline();
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}

static void p_pdfname(char *naam_, uint16 dt_beg_, uint16 dt_end_)
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

static int search(int16 stu_,int16  mod_)
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
