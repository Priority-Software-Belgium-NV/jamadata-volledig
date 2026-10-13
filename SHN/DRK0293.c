/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0293GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0293dat
#define ovlcod DRK0293cod
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

char ovldat[] = "drk0293  00:03 24/12/09 (c) Jamadata";
/* uitschrijven alle gegevens voor kassa */

// FLAGCOC : EAN-codenr + geen drankgedoe
// FLAGMLO : kasplu.dat ook uitschrijven in ..\share\prijzen

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_TB          200
#define MAXFLD          100
#define DIMBTW          8

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];
 
extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
static float calc_pnt();
extern double *d(),valu_cnv();
static double round();
static char *p_data;
static long *pl_80_1;

static int16 stu=6,free;
static int16 lvcd,klcd;
static float btw_pct[DIMBTW];

static char fm_os80[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us5[]   = {7,0xC8,5,0,0,0,0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x91,5,0,0x60,0};
static char fm_ou3[]   = {6,0x91,3,0,0x60,0};
static char fm_uu3[]   = {6,0xD1,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD1,2,0,0x60,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf3_1[] = {6,0xD4,3,1,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,1,0,'A','A','N','N',0};
static char fm_uDMJ[]  = {13,0xC8,1,0,1,0,'D','D','M','M','J','J',0};
static char fm_uAVW[]  = {11,0xC8,1,0,1,0,'A','A','V','W',0};
static char fm_u_ALN[]= {13,0xC8,1,0,0x09,0,'A','A','L','L','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
 
static char KASSAfas2sif[32]  = {160,133,131,132,135,130,138,136,137,161,141,140,   // enkel gebruiken voor kassa!
		   139,162,149,147,148,163,151,150,129,154,248,21,
		   254,27,26,24,25,0,0,128};
		
static char seqo_str[1500],sys3896[6],big_str[16][30],upd_veld[20],PtypePerKassa[20][6],nm_kassa[20][6];
static char filnam[80],out_JN[10],def_munt[4],kas_munt[4],fmt[40];
static long seqo_pos,value,ok_pos;
static int16 stu6_len,seqo_len,seqo_mode,pos,max_kaart,max_koppeling;
static flag sys2974,sys3894,sys3618,sys3978,sys4126;
static uint16 dt_exec,RecPrikTik,loc_nr[20];
static flag chk_btoeg=NO,arcd=YES,fl_freedelity=NO, fl_NO_PrxOpDatum=NO;
static flag sear_stt,sys3876,sys4402,sys4408,sys2700;
static float sys3614,*pf_6_28;
static double prx_afrond;

static char df_bpmode,df_fpmode;
static float df_bpval,df_fpval,df_pafr;
static int16 tb_kprx[6],max_kprx;
static int16 def_taal;

static struct{
  float kas_prx[6];
  float bak_punt;
  float stk_punt;
  char  KassaPromoCode;  // formule A-T van kassa zelf
	char  PromoBakFles;
	uint16 MaxPromoPerTicket;
	int16 BlokkeerOpKassa;
	int   PromoFormule;
	float PromoGetallen[4];
	char  PromoGratisArtCode[10];
	char  PromoGratisTekst[30];
	long  PromoGroepsCode; // voor samengestelde promo's
	char promotekst[30];
  char promoEAN[20];
  float norm_kas_prx[6];
} tba;

static struct{
  float kas_prx[6];
  float bak_punt;
  float stk_punt;
  char  KassaPromoCode;// formule A-T van kassa zelf
	char  PromoBakFles;
	uint16 MaxPromoPerTicket;
	int   PromoFormule;
	float PromoGetallen[4];
	char  PromoGratisArtCode[10];
	char  PromoGratisTekst[30];
	long  PromoGroepsCode; // voor samengestelde promo's
  char promotekst[30];
  char promoEAN[20];
  uint16 dt_beg;
  uint16 dt_end;
} tbaNEXT;

static struct{
	char Omschrijving[25];
	char Formule;
	char SelBakFles;
	float Getallen[4];
	char dummy[2]; // totaal 45 bytes
} PromoFormule[20];

ovlcod()
{
  int16 j,k,z,key,nr_;

  initload();
	fasunlck(-1);
  for(z=0;z<10;z++) out_JN[z]='J'; out_JN[9]='N'; dt_exec=*u(25,2);fl_NO_PrxOpDatum=NO;
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,4,22,2);
  scraddf(z++,8,6,0); scraddf(z++,8,24,2);
  scraddf(z++,10,6,0); scraddf(z++,10,57,2);
  scraddf(z++,11,6,0); scraddf(z++,11,57,2);
  scraddf(z++,12,6,0); scraddf(z++,12,57,2);
  scraddf(z++,13,6,0); scraddf(z++,13,57,2);
  scraddf(z++,14,6,0); scraddf(z++,14,57,2);
  scraddf(z++,15,6,0); scraddf(z++,15,57,2);
  scraddf(z++,16,6,0); scraddf(z++,16,57,2);
  scraddf(z++,17,6,0); scraddf(z++,17,57,2);
  scraddf(z++,18,6,0); scraddf(z++,18,57,2);
  scraddf(z++,19,6,0); scraddf(z++,19,57,2);
  scraddf(50,23,1,8); scraddf(51,23,11,8); scraddf(52,23,25,8);

#if FLAGJAC
  scraddf(53,23,63,8);
#endif

  FOREVER{
    redo:;
    z=1;
    scrifld(z++,fm_os63,"Uitschrijven gegevens voor kassa/pda");
    scrifld(z++,fm_os63,"Datum promoties : ");
    scrifld(z++,fm_udat,&dt_exec);
    scrifld(z++,fm_os63,"Uitschrijven artikels en prijzen voor kassa/pda .. : ");
    scrifld(z++,fm_uJN,&out_JN[0]);
    if(fldlen(53,1)){
      scrifld(z++,fm_os63,"Uitschrijven blokjes voor kassa/pda ............ : ");
      scrifld(z++,fm_uJN,&out_JN[1]);
      scrifld(z++,fm_os63,"Uitschrijven facturatieklanten ................. : ");
      scrifld(z++,fm_uJN,&out_JN[2]);
    } else {out_JN[1]='N'; out_JN[2]='N';}
    if(fldlen(92,1)){
      scrifld(z++,fm_os63,"Uitschrijven kassa-klanten ..................... : ");
      scrifld(z++,fm_uJN,&out_JN[3]);
    } // else z+=2;
    if(ovltest(297)){
      scrifld(z++,fm_os63,"Uitschrijven gegevens voor mobiele stockcontrole : ");
      scrifld(z++,fm_uJN,&out_JN[4]);
    } else out_JN[4]='N';
    if(sys2974){ // DIGI electronische kaartjes ESL
      scrifld(z++,fm_os63,"Uitschrijven gegevens voor DIGI ESL-systeem .... : ");
      scrifld(z++,fm_uJN,&out_JN[5]);
    } else out_JN[5]='N';
    if(ovltest(2295)){
      scrifld(z++,fm_os63,"Uitschrijven gegevens voor webshop ............. : ");
      scrifld(z++,fm_uJN,&out_JN[6]);
    } else out_JN[6]='N';
    if(ovltest(2296)){
#if FLAGJAC
      scrifld(z++,fm_os63,"Uitschrijven gegevens voor SmartSales .......... : ");
#else
      scrifld(z++,fm_os63,"Uitschrijven gegevens voor B2B-webshop ......... : ");
#endif
      scrifld(z++,fm_uJN,&out_JN[7]);
    } else out_JN[7]='N';
		scrifld(50, fm_os9, " F1 stop ");
		scrifld(51, fm_os13, " F8 neem aan ");
		scrifld(52, VarTextFmt(37, 0), " F10 GEEN toekomstige prijs meegeven ");

#if FLAGJAC
		scrifld(53, VarTextFmt(16, 0), " F11 SmartSales ");
#endif

    key=scrupd(1,0x681);

#if FLAGJAC
	if (key == 111) {
		ovlcall(2296, NO);
		goto endsr;
	}
#endif

    if(key==101) goto endsr;
		if(key==110){fl_NO_PrxOpDatum=YES;break;}
    if(key==108) break;
  }
	fasunlck(-2); max_koppeling=0;
//	if(fldlen(93,35)) MakeKoppelTabel(); // zelfde promo voor gelijkaardige artikels
  scrnum=0;scrget(1,170); z=1;
  scrifld(z,fm_os63,"Uitschrijven gegevens voor kassa"); z+=5;
  if(out_JN[0]=='J'){
    scrifld(z,fm_os63,"Uitschrijven artikels en prijzen ... : ");scrupd(-3,0);
    out_art(0); // standaard prijzen in map kassa
		for(k=0;k<10;k++){
			if(nm_kassa[k][0]=='\0' || fldlen(91,11+k*5)==0) continue;
			if(PtypePerKassa[k][0]=='\0') continue;
		  zero((char *)&tb_kprx[0],sizeof tb_kprx); max_kprx=0;
			for(j=0;j<6;j++){
				if(PtypePerKassa[k][j]){
					nr_=PtypePerKassa[k][j]-'0';
					if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
						tb_kprx[max_kprx++]=nr_;
					}
				}
			}
		  out_art(10+k); // speciale prijs uitschrijven per kassa in to-map
		  zero((char *)&tb_kprx[0],sizeof tb_kprx); max_kprx=0; // terug resetten
			for(j=0;j<6;j++){
				if(sys3896[j]){
					nr_=sys3896[j]-'0';
					if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
						tb_kprx[max_kprx++]=nr_;
					}
				}
			}
		}
		if(fldlen(64,0)) out_art(2);
    scrifld(z++,fm_os63,"Uitschrijven artikels en prijzen ... : OK");scrupd(-3,0);
  }
  if(out_JN[1]=='J'){
    scrifld(z,fm_os63,"Uitschrijven blokjes ............... : ");scrupd(-3,0);
    out_keys();
    scrifld(z++,fm_os63,"Uitschrijven blokjes ............... : OK");scrupd(-3,0);
  }
  if(out_JN[2]=='J'){
    scrifld(z,fm_os63,"Uitschrijven facturatieklanten ..... : ");scrupd(-3,0);
    out_klt(2);
    scrifld(z++,fm_os63,"Uitschrijven facturatieklanten ..... : OK");scrupd(-3,0);
  }
  if(out_JN[3]=='J' && fldlen(92,1)){
    scrifld(z,fm_os63,"Uitschrijven kassa-klanten ......... : ");scrupd(-3,0);
    out_klt(92);
    scrifld(z++,fm_os63,"Uitschrijven kassa-klanten ......... : OK");scrupd(-3,0);
  }
  if(out_JN[4]=='J' && sys2700){
    scrifld(z,fm_os63,"Uitschrijven gegevens voor mobiele stockcontrole : ");scrupd(-3,0);
    out_art(1);
    scrifld(z++,fm_os63,"Uitschrijven gegevens voor mobiele stockcontrole : OK");scrupd(-3,0);
  }
  if(out_JN[5]=='J' && sys2974){
    scrifld(z,fm_os63,"Uitschrijven gegevens voor DIGI ESL-systeem .... : ");scrupd(-3,0);
    out_DIGI(0); // standaard prijzen
		for(k=0;k<10;k++){
			if(nm_kassa[k][0]=='\0' || fldlen(91,11+k*5)==0) continue;
			if(PtypePerKassa[k][0]=='\0') continue;
		  zero((char *)&tb_kprx[0],sizeof tb_kprx); max_kprx=0;
			for(j=0;j<6;j++){
				if(PtypePerKassa[k][j]){
					nr_=PtypePerKassa[k][j]-'0';
					if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
						tb_kprx[max_kprx++]=nr_;
					}
				}
			}
		  out_DIGI(10+k); // speciale prijs uitschrijven per kassa in to-map
		  zero((char *)&tb_kprx[0],sizeof tb_kprx); max_kprx=0; // terug resetten
			for(j=0;j<6;j++){
				if(sys3896[j]){
					nr_=sys3896[j]-'0';
					if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
						tb_kprx[max_kprx++]=nr_;
					}
				}
			}
		}
    scrifld(z++,fm_os63,"Uitschrijven gegevens voor DIGI ESL-systeem .... : OK");scrupd(-3,0);
  }
  if(out_JN[6]=='J'){
    scrifld(z,fm_os63,"Uitschrijven gegevens voor webshop ............. : ");scrupd(-3,0);
    if(ovltest(2295)) ovlcall(2295,1);
		scrget(1,170); 
    scrifld(z++,fm_os63,"Uitschrijven gegevens voor webshop ............. : OK");scrupd(-3,0);
  }
  if(out_JN[7]=='J'){
#if FLAGJAC
    scrifld(z,fm_os63,"Uitschrijven gegevens voor SmartSales .......... : ");scrupd(-3,0);
#else
    scrifld(z,fm_os63,"Uitschrijven gegevens voor B2B-webshop ......... : ");scrupd(-3,0);
#endif
		if(ovltest(2296)) ovlcall(2296,1);
		scrget(1,170);
#if FLAGJAC
    scrifld(z++,fm_os63,"Uitschrijven gegevens voor SmartSales .......... : OK");scrupd(-3,0);
#else
    scrifld(z++,fm_os63,"Uitschrijven gegevens voor B2B-webshop ......... : OK");scrupd(-3,0);
#endif
  }
  endsr:;
  ovlexit(-1);
}

static out_art(mode_)/* 0=kassa, 1=stockcontrole,2= extra barcodes, 10-20=speciale prijzen per kassa in to-map*/
flag mode_;
{
  int16 n,g;
	char str_[30];
							
	if(mode_==2) mk_name(3902,"kaspluEX.dat");
  else if(mode_==1) mk_name(3902,"kaspluST.dat");
	else if(mode_>=10 && mode_<=20){ // prijs per kassa in TO
		zero(str_,sizeof str_);
		sprintf_s(str_,30,"to\\kassa-%02d\\kasplu.dat",mode_-10+1);
		mk_name(3902,str_);
	}
  else mk_name(3902,"kasplu.dat");
#if FLAGDU4
	if(mode_==0 && cmpstr(s(25,3),"DRC",3)==0) goto endsr; // gewone kasplu NIET uitschrijven in dossier DRC
#endif
  errnum=fasopen(filnam,2);if(errnum) goto endsr;

  fasinit(80);seqo_pos=0;seqo_mode=2;

  if(mode_==2){
		fasinit(64);
		FOREVER{
			if(faskeyi(64,1,2)) break;
			fasinit(6);*u(6,1)=*u(64,3);
			if(fasgeti(6)==0){
				memset(s(6,70),0,fldlen(6,70)+fldlen(6,71));
				n=70; if(*u(64,5))  n=71;
				copy(s(64,2),s(6,n),fldlen(6,n));
				dump_art(mode_);
			}
		}
	}
	else{
		fasinit(6);
		n=0;
		FOREVER{
			*u(6,1)=++n;
			g=fasgeti(6);
			if(g==47)break;
			if(g!=46){                                            /* deleted record */
				dump_art(mode_);
			}
		}
	}
  fasflush(0);
  fasclos(-2);
#if FLAGMLO
		if(mode_==0) CopyMoveFile(filnam, "..\\share\\prijzen\\kasplu.dat",NO);
		else if(mode_==1) CopyMoveFile(filnam, "..\\share\\prijzen\\kaspluST.dat",NO);
		else if(mode_==2) CopyMoveFile(filnam, "..\\share\\prijzen\\kaspluEX.dat",NO);
#endif
  endsr:;
}

static dump_art(mode_) /* 0=kassa, 1=stockcontrole,2= extra barcodes, 10-20=speciale prijzen per kassa in to-map*/
flag mode_;
{
  int16 k,dd,mm,yy;
  uint16 rec6_,rec_lgb_,rec_lgs_,mode6_;
  char str_[15],txt_freedelity[21];
 
	if(fldlen(6,200) && *u(6,200)) goto endsr; // geblokkeerd artikel
  zeros(seqo_str,sizeof seqo_str);pos=0;

  rec6_=*u(6,1);rec_lgb_=0;rec_lgs_=0;
	zero(txt_freedelity,sizeof txt_freedelity);
	if(fl_freedelity){
		if(fldlen(6,8) && *u(6,7)==RecPrikTik && *s(6,8)) copy(s(6,8),txt_freedelity,fldlen(6,8));
		else {
			fasinit(11);*u(11,2)=RecPrikTik; *u(11,3)=*u(6,1);mode6_=1;
			FOREVER{ // controleren of artikel al een code heeft voor deze leverancier 
				if(faskeyi(11,1,mode6_)) break; mode6_=2;
				if(*u(11,2)!=RecPrikTik || *u(11,3)!=*u(6,1)) break;
				if(*s(11,5)) copy(s(11,5),txt_freedelity,fldlen(11,5)); // steeds de laatste nemen 
			}
		}
	}
  if(mode_!=2) get_prx(); // niet nodig bij barcode
	if((mode_==0 || (mode_>=10 && mode_<=20)) && tba.BlokkeerOpKassa) goto endsr;  // volgens promofiche geblokkeerd
  if(sys4408){ // record# ipv codenummer 
    if(*s(6,41)){
      *u(6,1)=0;
      copy(s(6,41),s(6,2),fldlen(6,2));
      faskeyi(6,1,0); rec_lgb_=*u(6,1);
      *u(6,1)=rec6_;fasgeti(6);
    }
    if(*s(6,44)){
      *u(6,1)=0;
      copy(s(6,44),s(6,2),fldlen(6,2));
      faskeyi(6,1,0); rec_lgs_=*u(6,1);
      *u(6,1)=rec6_;fasgeti(6);
    }
    zero(str_,sizeof str_); if(rec6_) stcli_d(str_,(long)rec6_,5,0);
    copy(str_,s(6,2),fldlen(6,2));
    zero(str_,sizeof str_); if(rec_lgb_) stcli_d(str_,(long)rec_lgb_,5,0);
    copy(str_,s(6,41),fldlen(6,41));
    zero(str_,sizeof str_); if(rec_lgs_) stcli_d(str_,(long)rec_lgs_,5,0);
    copy(str_,s(6,44),fldlen(6,44));
  }
#if FLAGCOC
  zero(str_,sizeof str_); if(rec6_) stcli_d(str_,(long)(*u(6,1)),5,0);
	char2str(str_,5);
#else
  char2str(s(6,2),fldlen(6,2)); // A  code
#endif
  if(mode_==1){                            /* gegevens stockcontrole toevoegen */
    if(fldlen(6,33)) flt2str(*f(6,33));seqo_str[pos++]='|';/* stock */
    if(fldlen(6,35)) flt2str(*f(6,35));seqo_str[pos++]='|';/* norm.stock */
    if(fldlen(6,36)) flt2str(*f(6,36));seqo_str[pos++]='|';/* min.stock */
    if(fldlen(6,51)) flt2str(*f(6,51));seqo_str[pos++]='|';/* aantal besteld */
    if(fldlen(6,83)) flt2str(*f(6,83));seqo_str[pos++]='|';/* aantal per pallet */
    goto dump_fi;
  }
	else if(mode_==2){ // extra barcodes : enkel code + barcode
		for(k=0;k<3+max_kprx;k++) seqo_str[pos++]='|';
		for(k=0;k<4;k++) seqo_str[pos++]='|';
		if(*u(64,5)==0) {char2strN(s(64,2),14); seqo_str[pos++]='|';}
		else{seqo_str[pos++]='|';char2strN(s(64,2),14);}
		for(k=0;k<3;k++) seqo_str[pos++]='|';
		goto dump_fi;
	}

	char2str(s(6,3),30); // B omschrijving
  if(fldlen(6,9)){value=*i(6,9);val2str(0);} seqo_str[pos++]='|'; // C groep
  if(fldlen(6,28)){btw2str();} seqo_str[pos++]='|'; // D BTW
  for(k=0;k<max_kprx;k++){ // E .. I prijzen
    flt2str(tba.kas_prx[k]);seqo_str[pos++]='|';
  }
#if FLAGCOC
	seqo_str[pos++]='|';seqo_str[pos++]='|';
#else
  char2str(s(6,41),5);// J lg bak
  char2str(s(6,44),5);// K lg stuk
#endif
  if(fldlen(6,31)){ // L aantal/bak
    value=*f(6,31);if(value==0) value=1;
    val2str(0);
  }
  seqo_str[pos++]='|';
#if FLAGCOC
	 seqo_str[pos++]='|'; char2str(s(6,2),13); seqo_str[pos++]='|';
	 seqo_str[pos++]='|'; seqo_str[pos++]='|'; seqo_str[pos++]='|';
#else
  if(tba.KassaPromoCode) seqo_str[pos++]=tba.KassaPromoCode;  seqo_str[pos++]='|'; // M promo-code
  if(tba.promoEAN[0]) char2strN(tba.promoEAN,14); else char2strN(s(6,70),14); // N  EAN bak
  char2strN(s(6,71),14); // O EAN stuk
  flt2str(tba.bak_punt);seqo_str[pos++]='|'; // P promo-punten bak
  flt2str(tba.stk_punt);seqo_str[pos++]='|'; // Q promo-punten stuk
  char2str(tba.promotekst,20);// R promo-tekst 
  char2str(txt_freedelity,20);// S code Prik&Tik voor Freedelity (kol 19)
	if(tbaNEXT.dt_beg){ // T datum begin volgende promo
    jddate(tbaNEXT.dt_beg,&yy,&mm,&dd);yy%=100;
    stcli_d(&seqo_str[pos],(long)dd,2,0);seqo_str[pos+2]='/';pos+=3;
    stcli_d(&seqo_str[pos],(long)mm,2,0);seqo_str[pos+2]='/';pos+=3;
    stcli_d(&seqo_str[pos],(long)yy,2,0);seqo_str[pos+2]='|';pos+=3;
		if(tbaNEXT.dt_end){ // U datum einde volgende promo
			jddate(tbaNEXT.dt_end,&yy,&mm,&dd);yy%=100;
			stcli_d(&seqo_str[pos],(long)dd,2,0);seqo_str[pos+2]='/';pos+=3;
			stcli_d(&seqo_str[pos],(long)mm,2,0);seqo_str[pos+2]='/';pos+=3;
			stcli_d(&seqo_str[pos],(long)yy,2,0);seqo_str[pos+2]='|';pos+=3;
		} else seqo_str[pos++]='|';
		for(k=0;k<max_kprx;k++){ // V .. Z   prijzen
			flt2str(tbaNEXT.kas_prx[k]);seqo_str[pos++]='|';
		}
		if(tbaNEXT.KassaPromoCode) seqo_str[pos++]=tbaNEXT.KassaPromoCode;  seqo_str[pos++]='|'; // AA promo-code
		flt2str(tbaNEXT.bak_punt);seqo_str[pos++]='|'; // AB promo-punten bak
		flt2str(tbaNEXT.stk_punt);seqo_str[pos++]='|'; // AC promo-punten stuk
		char2str(tbaNEXT.promotekst,20);// AD promo-tekst 
	}
	else{
		seqo_str[pos++]='|'; // T dt_beg
		seqo_str[pos++]='|'; // U dt_end
		for(k=0;k<max_kprx;k++) seqo_str[pos++]='|';// V..Z prijzen
		seqo_str[pos++]='|';// AA promo-code
		seqo_str[pos++]='|';// AB promo-punten bak
		seqo_str[pos++]='|';// AC promo-punten stuk
		seqo_str[pos++]='|';// AD promo-tekst 
	}
	if(fldlen(93,35)){
		value=tba.PromoFormule; val2str(0); seqo_str[pos++]='|'; // AE huidige promotieformule
		if(tba.PromoBakFles) seqo_str[pos++]=tba.PromoBakFles;  seqo_str[pos++]='|'; // AF huidige promo op bak/fles
		for(k=0;k<4;k++){ // AG..AJ   huidige formule getallen
			if(k==1 && tba.PromoFormule==8) char2str(tba.PromoGratisArtCode,5); // AH : huidige indien gratis artikel, hier code gratis artikel zetten
			else {flt2str(tba.PromoGetallen[k]);seqo_str[pos++]='|';}
		}
		char2str(tba.PromoGratisTekst,20);// AK promo-gratis tekst 
		value=tba.PromoGroepsCode; val2str(0); seqo_str[pos++]='|'; // AL huidige promo-groepscode 
		value=tba.MaxPromoPerTicket; val2str(0); seqo_str[pos++]='|'; // AM huidige Max. Promo per ticket
		seqo_str[pos++]='|'; // AN huidige reserve 
		if(tbaNEXT.dt_beg){ // datum begin volgende promo
			value=tbaNEXT.PromoFormule; val2str(0); seqo_str[pos++]='|'; // AO toekomstige promotieformule
			if(tbaNEXT.PromoBakFles) seqo_str[pos++]=tbaNEXT.PromoBakFles;  seqo_str[pos++]='|'; // AP toekomstige promo op bak/fles
			for(k=0;k<4;k++){ // AQ..AT   formule getallen
				if(k==1 && tbaNEXT.PromoFormule==8) char2str(tbaNEXT.PromoGratisArtCode,5); // AR : toekomstige indien gratis artikel, hier code gratis artikel zetten
				else {flt2str(tbaNEXT.PromoGetallen[k]);seqo_str[pos++]='|';}
			}
			char2str(tbaNEXT.PromoGratisTekst,20);// AU toekomstige promo-gratis tekst 
			value=tbaNEXT.PromoGroepsCode; val2str(0); seqo_str[pos++]='|'; // AV toekomstige promo-groepscode 
			value=tbaNEXT.MaxPromoPerTicket; val2str(0); seqo_str[pos++]='|'; // AW toekomstige Max. Promo per ticket
			seqo_str[pos++]='|'; // AX toekomstige reserve 
		}
		else {
			for(k=0;k<10;k++) seqo_str[pos++]='|'; // AE - AX leeg
		}
  }
	// voorlopig geen lege velden wegschrijven owv compatibiliteit
	//else{
	//	for(k=0;k<20;k++) seqo_str[pos++]='|'; // AE - AX leeg
	//}

	// test char2str("X",1);
#endif

dump_fi:;
  KASSAcnv_char();/* convert jamascii to std-ascii */
  seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
/* artikel dumpen */
  seqo_len=0;
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
    seqo_flush();
  }
  *u(6,1)=rec6_;fasgeti(6);/* herstellen origineel */
	endsr:;
}


static out_DIGI(int16 outputmode_) // DIGI ESL systeem  0=default, 10-20=in to per kassa met zijn prijzen
{
	int16 len_,k,n,nr_,g,mode_,firsttime_=YES;
	char str_[200];
	float bdf_;
	uint16 stockloc_;

	if (outputmode_ == 0) {
		errnum = fasopen("..\\Share\\ArticleData.dat",2);
		
		if(errnum)
			goto endsr;
	}
	else if (outputmode_ >= 10 && outputmode_ <= 20) { // prijs per kassa in TO
		zero(str_, sizeof str_);
		zeros(filnam, sizeof filnam);
		sprintf_s(str_, 30, "to\\kassa-%02d\\DigiArt.dat", outputmode_ - 10 + 1);
		mk_name(3902,str_);
		errnum = fasopen(filnam,2);
		
		if (errnum)
			goto endsr;
	}
	else {
		zeros(filnam, sizeof filnam);
		mk_name(3902, "ArticleData.dat");
		errnum = fasopen(filnam,2);
		
		if(errnum)
			goto endsr;
	}

	fasinit(80);
	seqo_pos = 0;
	seqo_mode = 2;

	fasinit(6);
	n = 0;

	FOREVER {
		*u(6,1) = ++n;
		g = fasgeti(6);

		if (g == 47)
			break;
		
		if (g != 46) { /* deleted record */
			zeros(seqo_str, sizeof seqo_str);
			pos = 0;
			get_prx(); // niet nodig bij barcode
			char2str(s(6,2), fldlen(6,2)); // Artikel Code
			char2str(s(6,3), 30);          // Omschrijving
			zero(str_, sizeof str_);
			len_ = 0;

			if (*s(6,70))
				len_ += copy0cijfers(s(6,70),&str_[len_],fldlen(6,70));

			if (fldlen(64,1)) {
				fasinit(64);
				*u(64,3) = *u(6,1);
				mode_ = 1;

				for (k = 0; k < 10; k++) {
					if (faskeyi(64,2,mode_))
						break;
					
					mode_ = 2;

					if (*u(64,3) != *u(6,1))
						break;

					if (*u(64,5) == 0) {
						if (len_)
							str_[len_++] = ';';

						len_ += copy0cijfers(s(64,2),&str_[len_],fldlen(64,2));
					}
				}
			}

			char2str(str_, len_); // EAN Codes Bakken

			zero(str_, sizeof str_);
			len_ = 0;

			if (*s(6,71))
				len_ += copy0cijfers(s(6,71),&str_[len_],fldlen(6,71));

			if (fldlen(64,1)) {
				fasinit(64);
				*u(64,3) = *u(6,1);
				mode_ = 1;

				for (k = 0; k < 10; k++) {
					if (faskeyi(64,2,mode_))
						break;
					
					mode_ = 2;

					if (*u(64,3) != *u(6,1))
						break;

					if (*u(64,5) == 1) {
						if (len_)
							str_[len_++] = ';';

						len_ += copy0cijfers(s(64,2),&str_[len_],fldlen(64,2));
					}
				}
			}

			char2str(str_, len_);           // EAN Codes Flessen
			char2str(s(6,73),fldlen(6,73)); // Extra Omschrijving 
			char2str(tba.promotekst,20);    // Promo Tekst

#if FLAGSCP // op locatie een andere prijs (1) !
			if(!firsttime_) DecFloat2String(tba.norm_kas_prx[1]); // Prijs (BAK)
			else DecFloat2String(tba.norm_kas_prx[0]);
			seqo_str[pos++]='|'; 
#else
			DecFloat2String(tba.norm_kas_prx[0]); // Prijs (BAK)
			seqo_str[pos++] = '|';
#endif

			nr_ = max_kprx - 1;
			
			if (fldlen(6,89) == 1 && *s(6,89) == 'J')
				nr_ = 0; // bakprijs als stuk-prijs nemen

			DecFloat2String(tba.norm_kas_prx[nr_]); // Prijs Per Stuk
			seqo_str[pos++] = '|';

#if FLAGSCP // op locatie een andere prijs (1) !
			if(!firsttime_){
				if(tba.norm_kas_prx[1]!=tba.kas_prx[1]) bdf_=tba.kas_prx[1]; else bdf_=0;
			}
			else{
				if(tba.norm_kas_prx[0]!=tba.kas_prx[0]) bdf_=tba.kas_prx[0]; else bdf_=0;
			}
#else
			if (tba.norm_kas_prx[0] != tba.kas_prx[0])
				bdf_ = tba.kas_prx[0];
			else
				bdf_ = 0;
#endif

			DecFloat2String(bdf_); // Speciale Prijs (BAK)
			seqo_str[pos++] = '|';
			nr_ = max_kprx - 1;
			
			if (fldlen(6,89) == 1 && *s(6,89) == 'J')
				nr_ = 0; // bakprijs als stuk-prijs nemen

			if (tba.norm_kas_prx[nr_] != tba.kas_prx[nr_])
				bdf_ = tba.kas_prx[nr_];
			else
				bdf_ = 0;

			DecFloat2String(bdf_); // Speciale Prijs Per Stuk
			seqo_str[pos++] = '|';

			if (fldlen(6,37))
				bdf_ = *f(6,37);
			else
				bdf_ = 0;
			
			bdf_ = valu_cnv("EUR", "EUR", (double)bdf_, (double)(0.01));
			DecFloat2String(bdf_); // Inhoud
			seqo_str[pos++] = '|';

			if (fldlen(6,38))
				bdf_ = *f(6,38);
			else
				bdf_ = 0;
			
			bdf_ = valu_cnv("EUR", "EUR", (double)bdf_, (double)(0.01));
			DecFloat2String(bdf_); // Gewicht
			seqo_str[pos++] = '|';

			copy(s(6,41), s(6,2), fldlen(6,2));
			
			if (faskeyi(6,1,0) == 0)
				bdf_ = *f(6,PrNrs[tb_kprx[0]]);
			else
				bdf_ = 0;

			DecFloat2String(bdf_); // Leeggoed Per Bak
			seqo_str[pos++] = '|';

			*u(6,1) = n;
			fasgeti(6);
			nr_ = 44;
			
			if (fldlen(6,89) == 1 && *s(6,89) == 'J')
				nr_ = 41; // bakprijs als stuk-prijs nemen

			copy(s(6,nr_), s(6,2), fldlen(6,2));
			
			if (faskeyi(6,1,0) == 0)
				bdf_ = *f(6,PrNrs[tb_kprx[0]]);
			else
				bdf_ = 0;

			DecFloat2String(bdf_); // Leeggoed Per Stuk
			seqo_str[pos++] = '|';

#if FLAGCRA // Stock in bakken en flessen meegeven
			*u(6,1) = n;
			fasgeti(6);

			if (outputmode_ == 0)
				bdf_ = *f(6,33);
			else if (outputmode_ >= 10 && outputmode_ < 20) {
				stockloc_ = loc_nr[outputmode_ - 10];

				if (stockloc_ == 0 || stockloc_ == 99)
					bdf_ = *f(6,33);
				else {
					fasinit(66);
					*u(66,2) = *u(6,1);

					if (faskeyi(66,1,0) == 0) {
						if (fldlen(66,11 + (stockloc_ - 1) * 15))
							bdf_ = *f(66,11 + (stockloc_ - 1) * 15);
						else
							bdf_ = 0;
					}
					else
						bdf_ = 0;
				}
			}
			else
				bdf_ = 0;

			value = bdf_;
			val2str(0); // Stock in bakken
			seqo_str[pos++] = '/';

			if (bdf_ != 0 && *f(6,31) > 1) {
				bdf_ = bdf_ - value;
				bdf_ = bdf_ * *f(6,31);
			}
			else
				bdf_ = 0;

			zero(str_, sizeof str_);
			sprintf(str_, "%.0f", bdf_);
			char2str(str_, strlen(str_)); // Stock in flessen
#endif

			*u(6,1) = n;
			fasgeti(6);
			KASSAcnv_char();/* convert jamascii to std-ascii */
			seqo_str[pos++] = 0x0D;
			seqo_str[pos++] = 0x0A;

			/* artikel dumpen */
			seqo_len = 0;

			for (k = 0; k < pos; k += 280) {
				if ((k + 280) > pos)
					seqo_len = pos - k;
				else
					seqo_len = 280;

				copy(&seqo_str[k],s(80,1)+4,seqo_len);
				seqo_flush();
			}
		}
	}

	fasflush(0);
	fasclos(-2);

	if (outputmode_ == 0) {
		zeros (filnam, sizeof filnam);
		mk_name(3902, "DigiArt.dat");
		CopyMoveFile("..\\Share\\ArticleData.dat",filnam,NO); // kopieren van een file
		zeros(filnam, sizeof filnam);
		mk_name(3902, "ArticleData.dat");
		CopyMoveFile("..\\Share\\ArticleData.dat",filnam,NO); // kopieren van een file
		errnum = fasopen("..\\Share\\ArticleData.flg",2);
		
		if (errnum)
			goto endsr;

		fasinit(80);
		*(s(80,1)+4) = '1';
		fasseqo(80,2,5);
		fasclos(-2);
		zeros(filnam, sizeof filnam);
		mk_name(3902,"DigiArt.flg");
		CopyMoveFile("..\\Share\\ArticleData.flg",filnam,NO); // kopieren van een file
		zeros(filnam, sizeof filnam);
		mk_name(3902,"ArticleData.flg");
		CopyMoveFile("..\\Share\\ArticleData.flg",filnam,NO); // kopieren van een file
		firsttime_ = NO;
	}
	else if (outputmode_ >= 10 && outputmode_ <= 20) { // prijs per kassa in TO
		zero(str_, sizeof str_);
		zeros(filnam, sizeof filnam);
		sprintf_s(str_,30,"to\\kassa-%02d\\DigiArt.flg",outputmode_-10+1);
		mk_name(3902,str_);
		errnum = fasopen(filnam,2);
		
		if (errnum)
			goto endsr;

		fasinit(80);
		*(s(80,1)+4) = '1';
		fasseqo(80,2,5);
		fasclos(-2);
	}
	else {
		zeros(filnam, sizeof filnam);
		mk_name(3902,"ArticleData.flg");
		errnum = fasopen(filnam,2);
		
		if (errnum)
			goto endsr;

		fasinit(80);
		*(s(80,1)+4) = '1';
		fasseqo(80,2,5);
		fasclos(-2);
	}

endsr:;
}

static get_prx()
{
  int16 j,k,m,pos_,pos1_,findnextpromo_=YES;
	uint16 rec6_;
  float add_;
 
  zero((char *)&tba.kas_prx[0],sizeof tba);
	zero((char *)&tbaNEXT.kas_prx[0],sizeof tbaNEXT);
	pos_=0;
  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_exec) pos_=10; // direct al nieuwe prijzen in huidige zetten 
	pos1_=pos_;
	if(fl_NO_PrxOpDatum==NO && fldlen(6,105) && *u(6,105) && *u(6,105)>dt_exec && pos_==0){ pos1_=10;tbaNEXT.dt_beg=*u(6,105);} // er komt een prijswijziging aan

  for(k=0;k<max_kprx;k++){
    tba.kas_prx[k]=*f(6,PrNrs[tb_kprx[k]+pos_]);
    if(tba.kas_prx[k]<0) add_=-.5; else add_=.5;
    if(!(sys3894 & (1<<(tb_kprx[k])))) tba.kas_prx[k]*=1.+ *pf_6_28/100.;
    tba.kas_prx[k]=round(tba.kas_prx[k]);
    tba.norm_kas_prx[k]=round(tba.kas_prx[k]);
    tbaNEXT.kas_prx[k]=*f(6,PrNrs[tb_kprx[k]+pos1_]);
    if(tbaNEXT.kas_prx[k]<0) add_=-.5; else add_=.5;
    if(!(sys3894 & (1<<(tb_kprx[k])))) tbaNEXT.kas_prx[k]*=1.+ *pf_6_28/100.;
    tbaNEXT.kas_prx[k]=round(tbaNEXT.kas_prx[k]);
  }
  if(*i(6,9)==99){/* geen punten of promoties op leeggoed */
    tba.bak_punt=-1; tba.stk_punt=-1;
    tbaNEXT.bak_punt=-1; tbaNEXT.stk_punt=-1;
		goto endsr;
  }
  tba.bak_punt=calc_pnt(tba.kas_prx[0],df_bpmode,df_bpval);
  if(*f(6,31)>1 || tba.kas_prx[max_kprx-1]<tba.kas_prx[0]){
    tba.stk_punt=calc_pnt(tba.kas_prx[max_kprx-1],df_fpmode,df_fpval);
  }
  else {/* zoniet de bak-parameters nemen */
    tba.stk_punt=calc_pnt(tba.kas_prx[max_kprx-1],df_bpmode,df_bpval);
  }

  tbaNEXT.bak_punt=calc_pnt(tbaNEXT.kas_prx[0],df_bpmode,df_bpval);
  if(*f(6,31)>1 || tbaNEXT.kas_prx[max_kprx-1]<tbaNEXT.kas_prx[0]){
    tbaNEXT.stk_punt=calc_pnt(tbaNEXT.kas_prx[max_kprx-1],df_fpmode,df_fpval);
  }
  else {/* zoniet de bak-parameters nemen */
    tbaNEXT.stk_punt=calc_pnt(tbaNEXT.kas_prx[max_kprx-1],df_bpmode,df_bpval);
  }
	if(fldlen(93,1)==0) goto endsr;
  fasinit(93);*u(93,2)=*u(6,1);
  m=get_promo(1,*u(6,1),0,0,YES);
  if(m){/* leverancier + groep */
    m=get_promo(2,0,*u(6,7),*u(6,9),YES);
    if(m){/* leverancier */
      m=get_promo(2,0,*u(6,7),0,YES);
    }
    if(m){/* groep */
      m=get_promo(2,0,0,*u(6,9),YES);
    }
  }
	//if(m && fldlen(93,35)){ // indien geen promotie, dan zoeken naar gekoppelde promo
	//	for(k=0;k<max_koppeling;k++) if(TbKoppeling[k].arec==*u(6,1)) break;
	//	if(k<max_koppeling) {fasinit(93);*u(93,1)=TbKoppeling[k].rec93;fasgeti(93); m=0;}
	//}
  if(m==0){  // er is een promo op vandaag
    for(k=0;k<max_kprx;k++){
      if(*f(93,11+k)) tba.kas_prx[k]=*f(93,11+k);
    }
		if(fldlen(93,35) && *i(93,35)){
			tba.PromoBakFles=*s(93,34);
			tba.MaxPromoPerTicket=*u(93,41);
			tba.PromoFormule=*i(93,35);
			for(j=0;j<4;j++) tba.PromoGetallen[j]=*f(93,36+j);
			copy(s(93,40),tba.PromoGratisTekst,fldlen(93,40));
			if(*i(93,35)==8){ // formule gratis artikel, dan code bewaren
				rec6_=*u(6,1);
				fasinit(6);*u(6,1)=*f(93,37); fasgeti(6);
        if(sys4408){ // record# ipv codenummer 
					stcli_d(tba.PromoGratisArtCode,(long)(*u(6,1)),5,0);
				}
				else copy(s(6,2),tba.PromoGratisArtCode,fldlen(6,2));
				fasinit(6);*u(6,1)=rec6_; fasgeti(6);
			}
			if(fldlen(93,45)) tba.PromoGroepsCode=*l(93,45);
		}

    tba.KassaPromoCode=*s(93,25);
		if(fldlen(93,10)) tba.BlokkeerOpKassa=*u(93,10);
    tba.bak_punt=calc_pnt(tba.kas_prx[0],*s(93,20),*f(93,21));
    tba.stk_punt=calc_pnt(tba.kas_prx[max_kprx-1],*s(93,22),*f(93,23));
    copy(s(93,30),tba.promotekst,fldlen(93,30));
		if(fldlen(93,31)) copy(s(93,31),tba.promoEAN,fldlen(93,31));

		if(*u(93,8)>dt_exec+100) *u(93,8)=0; // langlopende promo als ze meer dan 100 dagen loopt vanaf nu
		if(*u(93,8)){  // einde vaste promo-periode terug naar defaultprijzen
			findnextpromo_=NO;
			if(tbaNEXT.dt_beg==0) tbaNEXT.dt_beg=*u(93,8)+1; // geen prijswijziging op datum : na promotie terug resetten naar default prijs
			else{
				if(tbaNEXT.dt_beg<=*u(93,8)){ // er is een prijswijziging op datum tijdens promo-periode, dan promo voortzetten aan nieuwe prijs
				  for(k=0;k<max_kprx;k++){
					  if(*f(93,11+k)) tbaNEXT.kas_prx[k]=*f(93,11+k);
				  }
					if(fldlen(93,35) && *i(93,35)){
						tbaNEXT.PromoBakFles=*s(93,34);
						tbaNEXT.MaxPromoPerTicket=*u(93,41);
						tbaNEXT.PromoFormule=*i(93,35);
						for(j=0;j<4;j++) tbaNEXT.PromoGetallen[j]=*f(93,36+j);
						copy(s(93,40),tbaNEXT.PromoGratisTekst,fldlen(93,40));
						if(*i(93,35)==8){ // formule gratis artikel, dan code bewaren
							rec6_=*u(6,1);
							fasinit(6);*u(6,1)=*f(93,37); fasgeti(6);
							if(sys4408){ // record# ipv codenummer 
								stcli_d(tbaNEXT.PromoGratisArtCode,(long)(*u(6,1)),5,0);
							}
							else copy(s(6,2),tbaNEXT.PromoGratisArtCode,fldlen(6,2));
							fasinit(6);*u(6,1)=rec6_; fasgeti(6);
						}
						if(fldlen(93,45)) tbaNEXT.PromoGroepsCode=*l(93,45);
					}
					tbaNEXT.KassaPromoCode=*s(93,25);
					tbaNEXT.bak_punt=calc_pnt(tbaNEXT.kas_prx[0],*s(93,20),*f(93,21));
					tbaNEXT.stk_punt=calc_pnt(tbaNEXT.kas_prx[max_kprx-1],*s(93,22),*f(93,23));
					copy(s(93,30),tbaNEXT.promotekst,fldlen(93,30));
				}
				else{ // prijswijziging in de toekomst, resetten naar huidige prijs
					for(k=0;k<max_kprx;k++) tbaNEXT.kas_prx[k]=tba.norm_kas_prx[k];
					tbaNEXT.bak_punt=calc_pnt(tbaNEXT.kas_prx[0],df_bpmode,df_bpval);
					if(*f(6,31)>1 || tbaNEXT.kas_prx[max_kprx-1]<tbaNEXT.kas_prx[0]){
						tbaNEXT.stk_punt=calc_pnt(tbaNEXT.kas_prx[max_kprx-1],df_fpmode,df_fpval);
					}
					else {/* zoniet de bak-parameters nemen */
						tbaNEXT.stk_punt=calc_pnt(tbaNEXT.kas_prx[max_kprx-1],df_bpmode,df_bpval);
					}
					tbaNEXT.dt_beg=*u(93,8)+1;
				}
			}
		}
		else{ // langlopende promo
			if(tbaNEXT.dt_beg){ // er is een prijswijziging op datum, tijdens promo-periode, dan promo herberekenen aan nieuwe prijs
			  for(k=0;k<max_kprx;k++){
				  if(*f(93,11+k)) tbaNEXT.kas_prx[k]=*f(93,11+k);
				}
				if(fldlen(93,35) && *i(93,35)){
					tbaNEXT.PromoBakFles=*s(93,34);
					tbaNEXT.MaxPromoPerTicket=*u(93,41);
					tbaNEXT.PromoFormule=*i(93,35);
					for(j=0;j<4;j++) tbaNEXT.PromoGetallen[j]=*f(93,36+j);
					copy(s(93,40),tbaNEXT.PromoGratisTekst,fldlen(93,40));
					if(*i(93,35)==8){ // formule gratis artikel, dan code bewaren
						rec6_=*u(6,1);
						fasinit(6);*u(6,1)=*f(93,37); fasgeti(6);
						if(sys4408){ // record# ipv codenummer 
							stcli_d(tbaNEXT.PromoGratisArtCode,(long)(*u(6,1)),5,0);
						}
						else copy(s(6,2),tbaNEXT.PromoGratisArtCode,fldlen(6,2));
						fasinit(6);*u(6,1)=rec6_; fasgeti(6);
					}
					if(fldlen(93,45)) tbaNEXT.PromoGroepsCode=*l(93,45);
				}
				tbaNEXT.KassaPromoCode=*s(93,25);
				tbaNEXT.bak_punt=calc_pnt(tbaNEXT.kas_prx[0],*s(93,20),*f(93,21));
				tbaNEXT.stk_punt=calc_pnt(tbaNEXT.kas_prx[max_kprx-1],*s(93,22),*f(93,23));
				copy(s(93,30),tbaNEXT.promotekst,fldlen(93,30));
			  findnextpromo_=NO;
			}
		}
	}
	if(findnextpromo_){ // zoeken naar promo in de toekomst
		fasinit(93);*u(93,2)=*u(6,1);
		m=get_promo(1,*u(6,1),0,0,NO);
		if(m){/* leverancier + groep */
			m=get_promo(2,0,*u(6,7),*u(6,9),NO);
			if(m){/* leverancier */
				m=get_promo(2,0,*u(6,7),0,NO);
			}
			if(m){/* groep */
				m=get_promo(2,0,0,*u(6,9),NO);
			}
		}
		if(m==0){
			tbaNEXT.dt_beg=*u(93,7);
			for(k=0;k<max_kprx;k++){
				if(*f(93,11+k)) tbaNEXT.kas_prx[k]=*f(93,11+k);
			}
			if(fldlen(93,35) && *i(93,35)){
				tbaNEXT.PromoBakFles=*s(93,34);
				tbaNEXT.MaxPromoPerTicket=*u(93,41);
				tbaNEXT.PromoFormule=*i(93,35);
				for(j=0;j<4;j++) tbaNEXT.PromoGetallen[j]=*f(93,36+j);
				copy(s(93,40),tbaNEXT.PromoGratisTekst,fldlen(93,40));
				if(*i(93,35)==8){ // formule gratis artikel, dan code bewaren
					rec6_=*u(6,1);
					fasinit(6);*u(6,1)=*f(93,37); fasgeti(6);
					if(sys4408){ // record# ipv codenummer 
						stcli_d(tbaNEXT.PromoGratisArtCode,(long)(*u(6,1)),5,0);
					}
					else copy(s(6,2),tbaNEXT.PromoGratisArtCode,fldlen(6,2));
					fasinit(6);*u(6,1)=rec6_; fasgeti(6);
				}
				if(fldlen(93,45)) tbaNEXT.PromoGroepsCode=*l(93,45);
			}
			tbaNEXT.KassaPromoCode=*s(93,25);
			tbaNEXT.bak_punt=calc_pnt(tba.kas_prx[0],*s(93,20),*f(93,21));
			tbaNEXT.stk_punt=calc_pnt(tba.kas_prx[max_kprx-1],*s(93,22),*f(93,23));
			copy(s(93,30),tbaNEXT.promotekst,fldlen(93,30));
			tbaNEXT.dt_end=*u(93,8);
		}
	}
	if(tbaNEXT.dt_beg && tbaNEXT.dt_end==0) tbaNEXT.dt_end=tbaNEXT.dt_beg+60;// promo in toekomst standaard op 60 dagen zetten (binnen 60 dagen opnieuw 2.K nemen)
  endsr:;
#if 0
  if(kas_munt[0] && cmpstr(def_munt,kas_munt,3)){
    for(k=0;k<6;k++){
      tba.kas_prx[k]=valu_cnv(def_munt,kas_munt,(double)(tba.kas_prx[k]),(double)1.);
    }
  }
#endif
}
 
static get_promo(keynr_,arec_,lrec_,grp_,fl_today_) // fl_today_ : NO is eerstvolgende na dt_exec
int16 keynr_;
uint16 arec_,lrec_,grp_,fl_today_;
{
  int16 mode_;
  uint16 rec_=0xFFFF, last_bdt_=0;
						
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
		if(fl_today_){// zoek naar huidige promo
      if(dt_exec>=*u(93,7) && (*u(93,8)==0 || dt_exec<=*u(93,8))){
        if(last_bdt_==0 || *u(93,7)>last_bdt_){/* promo met hoogste beg.datum nemen */
	        last_bdt_=*u(93,7); rec_=*u(93,1);
        }
      }
		}
		else{// zoek naar eerstkomende promo
      if(dt_exec<*u(93,7)){
        if(last_bdt_==0 || *u(93,7)<last_bdt_){/* promo met LAAGSTE beg.datum nemen */
	        last_bdt_=*u(93,7); rec_=*u(93,1);
        }
      }
		}
  }
  if(rec_!=0xFFFF){fasinit(93);*u(93,1)=rec_;fasgeti(93); return NO;}
  return YES;
}
 
 
static float calc_pnt(prx_,pmode_,pval_)
float prx_,pval_;
char pmode_;
{
  float val_=0,val1_;

  if(pmode_=='G') return (float)(-1);
  if(pmode_=='P') return (float)pval_;
  if(pmode_=='%'){
    val_=prx_ * (pval_/100.);
    if(df_pafr){
      val1_=(long)(val_ / df_pafr);
      val_=val1_*df_pafr;
    }
  }
  return (float)val_;
}

static out_klt(stu_)
int16 stu_;
{
  int16 n,g;
							
  zeros(filnam,sizeof filnam);
  if(stu_==2) mk_name(3902,"KASKLT.DAT");
  else mk_name(3902,"KASKRTNM.DAT");

  fasclos(-2);
  errnum=fasopen(filnam,2);if(errnum) goto endsr;
  fasinit(80);seqo_pos=0;seqo_mode=2;
  fasinit(stu_);
  n=0;
  FOREVER{
    next:;
    if(stu_==92 && max_kaart && n>=max_kaart) break;
    *u(stu_,1)=++n;
    g=fasgeti(stu_);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
      if(stu_==2 && sys4126 && *l(2,10)==0) goto next;
      if(stu_==2 && fldlen(2,200) && *u(2,200)) goto next; // geblokkeerde klant
      dump_klt(stu_);
    }
    else if(stu_==92){fasinit(stu_);*u(92,1)=n;dump_klt(stu_);}/* DUMMY klant uitschrijven */
  }
  fasflush(0);
  fasclos(-2);
  endsr:;
}

static dump_klt(stu_)
int16 stu_;
{
  int16 k;
  long lbd_;
  char str_[25];
							
  zeros(seqo_str,sizeof seqo_str);pos=0;
							
  if(fldlen(stu_,2)) cfld2str(stu_,2,10);
  else{
    stcli_d(str_,(long)(*u(stu_,1)),10,1);
    for(k=0;k<10;k++) if(str_[k]!=' ') break;
    copy(&str_[k],&seqo_str[pos],10-k); pos+=10-k;
    zero(&seqo_str[pos],k);pos+=k;
    seqo_str[pos++]='\0';
  }
  cfld2str(stu_,3,40);	if(stu_==2 && *(s(2,3)+fldlen(2,3)-1)=='!') seqo_str[pos-2]='!'; // markering doorgeven
  cfld2str(stu_,4,30);
  cfld2str(stu_,5,7);cfld2str(stu_,6,25);
  cfld2str(stu_,8,15);

  if(stu_==2){
    lbd_=0;zero(str_,sizeof str_);
    if(fldlen(stu_,10)) lbd_=*l(stu_,10);/* BTW-nummer */
		btw_deco(&str_[0],(long *)&lbd_,1);
		if(str_[0]=='0'){
  		copy(&str_[1],&seqo_str[pos],11); pos+=11; seqo_str[pos++]=' '; // voorlopig 9 cijfers tot kassapgm is aangepast, dan volgende lijn nemen (Jaak17/10/23)
		}
		else{
		  copy(&str_[0],&seqo_str[pos],12); pos+=12; 
		}




//		if(fldlen(stu_,10)) lbd_=*l(stu_,10)&0xBFFFFFFF;/* BTW-nummer */
    //stcli_d(str_,lbd_,9,0);
    //copy(&str_[0],&seqo_str[pos],3); pos+=3; seqo_str[pos++]='.';
    //copy(&str_[3],&seqo_str[pos],3); pos+=3; seqo_str[pos++]='.';
    //copy(&str_[6],&seqo_str[pos],3); pos+=3; seqo_str[pos++]=' ';
    seqo_str[pos++]='\0';
    for(k=0;k<max_kprx;k++) if(*s(stu_,26)==sys3896[k]) break;
    if(k>=max_kprx) *s(stu_,26)='0'; else *s(stu_,26)=k+'0';
    cfld2str(stu_,26,1);/* Horeca-type */
  }
  else{/* dummy voor klantenkaarten */
    for(k=0;k<15;k++) seqo_str[pos++]='\0';
  }
  for(k=0;k<2;k++) seqo_str[pos++]='\0'; // gebruikt voor veld 2,89 : prijs via JMD
  for(k=0;k<10;k++) seqo_str[pos++]='\0';
  KASSAcnv_char();
/* fact.klant dumpen */
  seqo_len=0;
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
    seqo_flush();
  }
}

static out_keys()
{
  int16 mode_;
							
  mk_name(3902,"kasusr.dat"); fasclos(-2);
  errnum=fasopen(filnam,2);if(errnum) goto endsr;
  fasinit(80);seqo_pos=0;seqo_mode=2;
  fasinit(53);mode_=2;
  FOREVER{
    if(faskeyi(53,2,mode_)) break; mode_=2;
    copy(s(53,2),p_data,4);
						
    zeros(seqo_str,sizeof seqo_str);
    copy(s(53,7),seqo_str,24);
    if(sys4408 && *u(53,10)) stcli_d(&seqo_str[24],(long)(*u(53,10)),5,0);
    else copy(s(53,6),&seqo_str[24],5);
    pos=29;
    KASSAcnv_char();
    copy(seqo_str,p_data+4,29); seqo_len=33;
    seqo_flush();
  }
  fasclos(-2);
  endsr:;
}


static cfld2str(stu_,fld_,len_)
int16 stu_,fld_,len_;
{
  int16 flen_,k;
  flag zero_rest=NO;
  char str_[100];
 
  zero(str_,sizeof str_); flen_=fldlen(stu_,fld_);
  copy(s(stu_,fld_),str_,flen_);
  zero_rest=NO;
  for(k=0;k<len_;k++){
    if(str_[k]=='\0') zero_rest=YES;
    if(zero_rest) str_[k]=' ';
  }
  copy(str_,&seqo_str[pos],len_); pos+=len_;
  seqo_str[pos++]='\0';/* tussenzero */
}

static KASSAcnv_char() // speciale tabel owv kassa
{
  int16 k;

  for(k=0;k<pos;k++){
    if(seqo_str[k]>=0x80 && seqo_str[k]<0x80+sizeof KASSAfas2sif){
      seqo_str[k]=KASSAfas2sif[seqo_str[k]-0x80];
    }
  }
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
      if(seqo_str[k]=='|') seqo_str[k]='.';/* delete | */
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;/* delete trailing blanks */
    pos++;
  }
  seqo_str[pos++]='|';
}

static char2strN(ps_,len_) // enkel cijfers
char *ps_;
int16 len_;
{
  int16 k,orig_pos_;
 
  orig_pos_=pos;
  if(len_){
    copy0cijfers(ps_,&seqo_str[pos],len_);while(seqo_str[pos]) pos++;
    for(k=orig_pos_;k<pos;k++){
      if(seqo_str[k]=='|') seqo_str[k]='.';/* delete | */
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;/* delete trailing blanks */
    pos++;
  }
  seqo_str[pos++]='|';
}



static flt2str(bd_)
float bd_;
{
  double bedrag_,add_=0;
  long val_;
								
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  if(bedrag_<0 && bedrag_> -1)seqo_str[pos++]='-';/* correctie kleine neg.getallen */
  val_=bedrag_*1000+add_;value=val_/1000;
  val2str(0);
  value=val_-value*1000;
  if(value){
    seqo_str[pos++]='.';
    if(value<0) value=-value;val2str(1);
  }
}

static DecFloat2String(bd_)   // steeds met 2 decimalen 
float bd_;
{
  double bedrag_,add_=0;
  long val_;
								
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  if(bedrag_<0 && bedrag_> -1)seqo_str[pos++]='-';/* correctie kleine neg.getallen */
  val_=bedrag_*100+add_;value=val_/100;
  val2str(0);
  value=val_-value*100; if(value<0) value=-value;
  seqo_str[pos++]='.'; stcli_d(&seqo_str[pos],value,2,0);pos+=2;
}


static double round(bedrag_)
double bedrag_;
{
  bedrag_=valu_cnv("EUR","EUR",bedrag_,prx_afrond);

  return bedrag_;
}

static btw2str()
{
  int16 k;
  char buff[15];
						
  zeros(buff,sizeof buff);
  value=*pf_6_28;
  stcli_d(&buff[0],value,2,1);
  for(k=0;k<10;k++){
    if(buff[k]=='\0') break;
    if(buff[k]!=' ') seqo_str[pos++]=buff[k];
  }
  value=*pf_6_28*10-value*10;
  if(value){
    seqo_str[pos++]='.';
    zeros(buff,sizeof buff);
    stcli_d(&seqo_str[pos++],value,1,0);
  }
}

static val2str(mode_)
int16 mode_;
{
  int16 k;
  char buff[15];

  zeros(buff,sizeof buff);
  if(mode_==0){
    stcli_d(&buff[0],value,10,1);
    for(k=0;k<10;k++){
      if(buff[k]=='\0') break;
      if(buff[k]!=' ') seqo_str[pos++]=buff[k];
    }
  }
  else{
    if(value<0) value=-value;
    stcli_d(&buff[0],value,3,0);
    for(k=2;k>=0;k--) if(buff[k]!='0') break;
    copy(&buff[0],&seqo_str[pos],k+1);pos+=k+1;
  }
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

static copy0cijfers(ps,pd,max_len_)
char *ps,*pd;
int16 max_len_;
{
  int16 fuval=0;
			
  while(*ps && max_len_--){
		if(*ps>='0' && *ps<='9'){*pd++=*ps++; fuval++;}
		else ps++; // geen cijfer
  }
  *pd='\0';
  return fuval;
}



static initload()
{
  int16 j,k,nr_;
  char *pdum_;

  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);
  if(fldlen(93,1)) fileopen(11);
			
  sysget(294,4,def_munt);
  sysget(1048,32,&btw_pct[0]);
  sysget(1918,2,&sear_stt);
  sysget(2700,2,&sys2700);
  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(2974,2,&sys2974); // DIGI artikels uitschrijven
	sysget(2976,2,(char *)&RecPrikTik); if(ovltest(2291) && fldlen(11,1) && RecPrikTik) fl_freedelity=YES;
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,&sys3896[0]);
  sysget(3978,2,&sys3978);/* geen artikelfiche updaten */


  sysget(3982,1,&df_bpmode);
  sysget(3983,4,&df_bpval);
  sysget(3987,1,&df_fpmode);
  sysget(3988,4,&df_fpval);
  sysget(3992,4,&df_pafr);
  sysget(4126,2,&sys4126);
	sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4472,2,&max_kaart);
/*  sysget(4338,3,kas_munt); */
  sysget(4402,2,&sys4402);
  sysget(4408,2,&sys4408);
	sysget(19380,120,PtypePerKassa); 
  zero((char *)&tb_kprx[0],sizeof tb_kprx); max_kprx=0;
  for(k=0;k<6;k++){
    if(sys3896[k]){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
				tb_kprx[max_kprx++]=nr_;
      }
    }
  }
  sysget(3678,2,&def_taal);
//	for(k=0;k<20;k++) sysget(20500+k*45,45,&PromoFormule[k].Omschrijving[0]);
  fieldspc(6,21,&pdum_,fmt);
  k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;/* afronden vlgs fmt */
#if 0
  if(sys3614>prx_afrond) prx_afrond=sys3614;/* afstemmen op decimalen fmt */
#endif
  pf_6_28=f(6,28);
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

}

static seqo_flush()
{
  if(seqo_len){
    fasseqo(80,seqo_mode,seqo_len+4);
    seqo_pos+=seqo_len;
    *l(80,1)=seqo_pos;
    seqo_len=0;
  }
}
 
static mk_name(adr_pref,ps)
uint16 adr_pref;
char *ps;
{
  char *pd;

  memset(filnam,0,sizeof filnam);
	pd=filnam;
  sysget(adr_pref,16,pd);
  while(*pd) pd++;
  while(*ps!='\0') *pd++=*ps++;
}

static zeros(pd,len)
char *pd;
int16 len;
{
  int16 k;

  for(k=0;k<len;k++) *(pd+k)='\0';
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
