/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0266GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0266dat
#define ovlcod DRK0266cod
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

char ovldat[] = "drk0266  00:01 26/11/10 (c) Jamadata";  // beheer offertes 
     // FLAGART : geen codenummer
     // FLAGEPD : korting EUR na % rekenen, dus wordt bij HLkorting geteld
     // FLAGHOE : drukt op eigen voorbedrukt document
     // FLAGVDW : korting EUR na % rekenen, dus wordt bij HLkorting geteld

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define MAXFLD          100
#define BTWDIV          2
#define BTWDIM          8+BTWDIV
#define DOUBLE_FACT     2
#define D_LIN_SCR       16
#define DIM_TB_OFFERTE  750
#define DELIM           ';'
#define C1      256E0
#define C2      65536E0
#define MAP_OFFERTE     "..\\Offerte\\"

#if FLAGHOE  // specifieke layout
#define EIGENLAYOUT    1
#endif

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

extern char *s();
static char *rec_ele();
extern int16 *i();
extern uint16 *u();
static uint16 hash(),str2date();
extern long *l();
extern long val();
extern float *f();
static float get_num();
extern double *d();
extern double valu_cnv();
static double Round();

static long *pl_80_1;
extern uint16 datejd();

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os9[]  = {7,0x88,9,0,0,0,0};
static char fm_os8[]  = {7,0x88,8,0,0,0,0};
static char fm_os6[]  = {7,0x88,6,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us75[]   = {7,0xC8,75,0,0,0,0};
static char fm_us30[]   = {7,0xC8,30,0,0,0,0};
static char fm_us15[]   = {7,0xC8,15,0,0,0,0};
static char fm_us10[]   = {7,0xC8,10,0,0,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_od4_1[] = {6,0x95,4,1,0x60,0};
static char fm_od5_2[] = {6,0x95,5,2,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf4_2[] = {6,0xD4,4,2,0x70,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_uf20_[] = {6,0xD4,2,0,0x20,0};
static char fm_uf21_[] = {6,0xD4,2,1,0x20,0};
static char fm_of5_0[] = {6,0x94,5,0,0x70,0};
static char fm_of3_0[] = {6,0x94,3,0,0x70,0};
static char fm_of2_1[] = {6,0x94,2,1,0x70,0};
static char fm_of2_0[] = {6,0x94,2,0,0x70,0};
static char fm_of3_2[] = {6,0x94,3,2,0x70,0};
static char fm_of4_2[] = {6,0x94,4,2,0x70,0};
static char fm_of5_2[] = {6,0x94,5,2,0x70,0};
static char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_ul8[]   = {6,0xD3,8,0,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_u_SP[]  = {11,0xC8,1,0,1,0,'S','S','P','P',0};
static char fm_uref[]  = {11,0xC8,8,0,1,0,'A','Z','0','9',0};

							
static int16 max_line,len_tblin;
static long ram_size;
static char *ram,*p_tblin;
 
static char seqo_str[2500],talen[4];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos,KarPerLine=80;
static unsigned SpoolFileNr;
static int16 free,stu=6;
static int16 sys3588,taaltxt,sys4731;
static int16 form_dat[8],pr_mode,prtnr;
static int16 prt2pdf;
static uint16 sys3758,ft_date,dat_beg,dat_end,dt_p_upd,inq_klt;
static char filnam[80],OrigFilnam[80],fmt[40],ft_nr[15],def_munt[4],*p_data;
static char old_kltnm[50],leeggcod[20],opm_foot[8][75],firma[350],DrukOpEigenLayout;
static char buf500[500],adrbuf[1000],fm_prx[40],ref_offerte[11],str_tav[40];
static char stdkolJN[20], prtkolJN[20],std_foot[4][75],prtwinstJN;
/*
char p_vp_norm='N',p_accijns='J',p_ft_kort='N',p_sem_kort='N',p_vp_z_acc='N';
char p_bd_leeg='J';
*/
static flag lvcd,klcd=NO,chk_btoeg=NO,sys3624,sys3720,sear_stt;
static int16 prxnr,z_netto,prxnr_kassastuk;
static float brij_tpct,brij_tbd,btw_pct[BTWDIM];
static float def_btw,calc_prx,calc_kort,calc_sem,hl_korting,hl_semkort,ft_hlkorting,ft_semhlkorting,directpc,semestpc;
static double alg_tot,belastbt,btw_tot,tot_leeg,btw_bas[BTWDIM],btw_bd[BTWDIM],semestbd;
static double ft_afrond,prx_afrond,tot_winst,tot_wpct;
static uint16 rec_pklt;
static flag newkort,nokort,OfferteMetAantal=0;
static flag sys3876,sys3590,exec_mode,sys4608,sys2727,sys1820,sys3894;
static char sys4436,sys3896[6];
static uint16 *pu_6_1,*pu_2_1;

static struct {
  int16 begpos;
  int16 lengte;
  char *txt[4];
} firm[10] = {116,17,"Telefoon","N– t…l…phone","Telephone","Telefon",
	     170,17,"Fax","Fax","Fax","Fax",
	      86,15,"B.T.W. nr.","N– T.V.A.","T.V.A.","M.W.S.",
	     101,14,"Bankrek.","Banque","Bank","Bank",
	     134,12,"RPR","RPM","","",
	     149,20,"Erkenningsnr","","","",
	     188,30,"Web-site","Web-site","","",
	     222,30,"E-mail","E-mail","","",
	     256,42,"IBAN","IBAN","IBAN","IBAN",
	     298,11,"BIC","BIC","BIC","BIC"};
 
static struct{
	uint16 rec;
	char  code[15];
	char  omschr[40];
	float ak_prx;
	float accijns;
	float vk_prx;
	float vk_prx_ex;
	float ft_kpct;
	float ft_kbdr;
	float ft_hlkort;
	float ft_hlkortHL;
	float ft_korting;
	float ft_prx_ex;
	float ft_prx_in;
	float net_pr_ex;
	float net_pr_in;
	float sem_kpct;
	float sem_hlkort;
	float sem_hlkortHL;
	float sem_korting;
	float brij_tk_pct;
	float brij_tk_eur;
	float brij_tk_tot;
	float inhoud;
	float btw;
	uint16 groep;
	uint16 rec_leeg;
	float q_leeg;
	float prx_leeg;
	float w_pct;
	float w_EUR;
	float prx_bruto;
	char  print_omschr[40];
	float aantal;
	char  stuksaantal;
	float q_per_bak;
	float q_per_palet;
	double tot_goederen;
	double tot_goed_inc;
	double tot_leeg;
	uint16 hash;
} tblin;
 
static struct{
  char filname[15];
	char referentie[15];
	char klantstu[150];
  uint16 datum;
} tb_offerte[DIM_TB_OFFERTE];
static int q_offertes;



ovlcod(parmval)
int16 parmval;
{
  int16 k,curs=1,key,z;
  char choice;

  initload();

	if(parmval==1){ // vanuit x19
		FOREVER{
      ft_init();
	  	fasinit(2);*u(2,1)=*u(27,5); fasgeti(2); inq_klt=*u(2,1);
      if(ld_offerte(YES)==NO) break;
		  calc(0,NO);
    redo_dsp:;
			if(dsp_detail()) break;
			k=dsp_tot();
			if(k==NO) break;
			if(k>2)goto redo_dsp;
		}
		ovlexit(-1);
	}

  FOREVER{
		redo:;
    scrget(2,313);z=1;fasunlck(0);scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0266A");
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x1);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) ovlexit(-1);
		fasunlck(-1);
    switch(choice){
      case '1': upd_offerte();break;
      case '2': add_offerte();break;
      case '+': parameters();break;
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}

static upd_offerte()
{
  int16 k;
				
  FOREVER{
    ft_init();
    if(ld_offerte(NO)==NO) break;
		calc(0,NO);
    redo:;
    if(dsp_detail()) break;
    k=dsp_tot();
    if(k==NO) goto endsr;
    if(k>2)goto redo;
    endsr:;
  }
}

static add_offerte()
{
  int16 k;
 
  FOREVER{
    ft_init();
    redo:;
    if(dsp_detail()) break;
    k=dsp_tot();
    if(k==NO) goto endsr;
    if(k>2)goto redo;
    endsr:;
  }
}
 
static parameters()
{

  int16 key,k,z;

/* stdkolJN : 0 = basispr, 1=nettopr, 2=accijns, 3=ftkort%, 4=ftkortbd
	      5 = semest%, 6=semestbd, 7=leeggoed, 8=factuurprijs
	      10= prijs ex.accijns, 11=firmahoofding, 12=GEEN incl.BTW prijzen drukken 
*/

  for(k=0;k<sizeof stdkolJN;k++) if(stdkolJN[k]!='J' && stdkolJN[k]!='N') stdkolJN[k]='N';

  FOREVER{
    scrget(2,317);z=1;
		scrifld(z++,fm_u_JN,&stdkolJN[0]);  // basis
		if(!sys4731) scrifld(z++,fm_u_JN,&stdkolJN[2]);  else z++;// accijns
		scrifld(z++,fm_u_JN,&stdkolJN[3]);  // ft kort%
		scrifld(z++,fm_u_JN,&stdkolJN[4]);  // ft korting EUR
		scrifld(z++,fm_u_JN,&stdkolJN[8]);  // factuurprijs
		if(!sys4731) scrifld(z++,fm_u_JN,&stdkolJN[5]); else z++; // sem %
		if(!sys4731) scrifld(z++,fm_u_JN,&stdkolJN[6]); else z++; // sem.korting EUR
		scrifld(z++,fm_u_JN,&stdkolJN[1]); // nettoprijs
		scrifld(z++,fm_u_JN,&stdkolJN[12]); // GEEN prijs incl.BTW
		if(!sys4731) scrifld(z++,fm_u_JN,&stdkolJN[7]); else z++;// leeggoed
    if(!sys4731) scrifld(z++,fm_u_JN,&stdkolJN[10]); else z++;// prijs excl.acc
		scrifld(z++,fm_u_JN,&stdkolJN[11]); // firmahoofding
    for(k=0;k<4;k++)scrifld(z++,fm_us75,std_foot[k]);
    key=scrupd(1,0xA0);
    if(key==106) break;
    if(key==108){wr_param(); break;}
  }
  ld_param();
}

static dsp_detail()
{
  int16 curs,j,key,k,start_=0,z,z_base,q_per_line,nstart_,auto_enter,err_pos_,curspos_,smode_;
  uint16 sr_nm_;
 
  curs=1;q_per_line=7;err_pos_=0;
  fasinit(2);if(rec_pklt) {*u(2,1)=rec_pklt;fasgeti(2);}
	calc(0,NO);
  FOREVER{
    redo:
    scrnum=0;z=1;
#if FLAGART // geen codenummer
		scrget(2,509);
#else
		scrget(2,309);
		scraddpicto(5,0,75,1,4,2,596,0,0,"Vernieuw prijzen");
		scraddpicto(1,0,76,22,4,2,127,0,4,"Voeg artikels toe");
		if(!OfferteMetAantal) scraddpicto(4,0,8,4,2,1,70,0,4,"Met aantallen"); else scraddpicto(4,0,8,4,2,1,71,0,3,"Zonder aantallen");
#endif

    j=start_+1; scrifld(z++,fm_ou3,&j);
    j=start_+D_LIN_SCR; scrifld(z++,fm_ou3,&j);
    scrfld(-z,2,3);z++;
		scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		scraddpicto(3,z-1,2,0,2,1,64,0,4,"Klantenfiche");
   
#if !FLAGART // geen aantallen
		if(OfferteMetAantal) {
			scrifld(z++,fm_od4_1,&tot_wpct);
			scrifld(z++,fm_udat,&dt_p_upd);
			scrifld(z++,VarTextFmt(6,0),"Totaal"); scrifld(z++,fm_od6_2,&alg_tot);
		}
		else{
			z++;
			scrifld(z++,fm_udat,&dt_p_upd);
			z++;z++;
		}
#else 
		 scrifld(z++,fm_udat,&dt_p_upd);
#endif
    z_base=z;auto_enter=NO;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      ram2stu(j);
#if FLAGART // geen codenummer 
			z++;
#else
			if(OfferteMetAantal){
				dspdetln(z++,j,fm_uf5_0,&tblin.aantal);
				dspdetln(z++,j,fm_u_SP,&tblin.stuksaantal);
			}
			else{
				dspdetln(z++,j,fm_of5_0,&tblin.aantal);
				dspdetln(z++,j,fm_os1,&tblin.stuksaantal);
			}
			auto_enter=YES;if(tblin.code[0]!='\0' && z!=err_pos_) auto_enter=NO;
      fmt_get(6,2);
      if(auto_enter){dspdetln(-z,j,fmt,tblin.code);z++;}
      else dspdetln(z++,j,fmt,tblin.code);
#endif
      auto_enter=YES;if(tblin.omschr[0]!='\0' && z!=err_pos_) auto_enter=NO;
      fmt_get(6,3);
      if(auto_enter){dspdetln(-z,j,fmt,tblin.omschr);z++;}
      else dspdetln(z++,j,fmt,tblin.omschr);
			scraddpicto(10+j-start_,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
      dspdetln(z++,j,fm_prx,&tblin.vk_prx);
      fmt_get(58,21);dspdetln(z++,j,fmt,&tblin.ft_kpct);
//      dspdetln(z++,j,fm_of4_2,&tblin.ft_korting);
      dspdetln(z++,j,fm_of6_2,&tblin.ft_prx_ex);
      if(tblin.code[0] && tblin.w_pct<=0) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);
    }
    key=scrupd(curs,0x3FF);curs=z_base;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5004){ // aantallen aan/uit
			if(OfferteMetAantal){OfferteMetAantal=NO;}
			else {OfferteMetAantal=YES;}
			goto redo;
		}
    auto_enter=NO;nstart_=start_;err_pos_=0;
    if(key==106){
      if(scr_ok("Wenst U echt de gegevens te annuleren ???")){
	ft_init();curs=1; goto redo;
      }
    }

    if(key==101){
      for(k=0;k<max_line;k++){ram2stu(k);if(tblin.omschr[0]) break;}
      if(k<max_line){
	if(wr_offerte()) return YES;
      } else return YES;
    }
    if(key==18 && curspos_>=z_base){
/*
      if(curspos_<z_base){
	curs=curspos_+1;goto redo;
      }
*/
      auto_enter=YES;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      k=(curspos_-z_base)%q_per_line;
      ram2stu(j);
      if(k==2 && tblin.code[0]=='\0') {curs=curspos_+1;goto redo;}
      if(k==3 && (tblin.omschr[0]=='\0' || tblin.omschr[0]=='*')) {curs=curspos_+1;goto redo;}
    }
		smode_=0;if(key==5002) smode_=98;
    if(smode_==98 || *s(2,3)=='\0' || cmp_str(s(2,3),old_kltnm,fldlen(2,3))){
      if(search(2,smode_)) {curs=3;goto redo;}
      copy(s(2,3),old_kltnm,fldlen(2,3));
      if(fldlen(2,18)) directpc=*f(2,18);
      if(fldlen(2,56)) semestpc=*f(2,56);
      prxnr=*s(2,26)-'0';
      if(prxnr<0 || prxnr>9) prxnr=0;
      if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
      fmt_get(6,PrNrs[prxnr]);copy(fmt,fm_prx,sizeof fmt);
      k=fmt[3];
      prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;
    }
		if(key==5003){ovlcall(2921,0); curs=curspos_; goto redo;}
		if(key==5005){
			if(DisplayWarning("Wenst u echt de prijzen te vernieuwen? Specifieke prijzen gaan verloren!",605,1)){
				for(k=0;k<max_line;k++){
					ram2stu(k);
					if(tblin.rec){
						fasinit(6);*u(6,1)=tblin.rec; fasgeti(6);
						fillart2tb(YES);
						stu2ram(k);
					}
				}
			}
//			curs=curspos_; goto redo;
		}
		if(key>=5010 && key<5010+D_LIN_SCR){
			k=key-5010+start_;
			ram2stu(k);fasinit(6);
			if(tblin.code[0]) {*s(6,3)='.';copy(tblin.code,s(6,3)+1,fldlen(6,2));}
			else {copy(tblin.omschr,s(6,3),fldlen(6,3));sr_nm_=YES;}
			if(search(6,98)){
				curs=z_base+1+ (k-start_)*q_per_line ; if(tblin.code[0]=='\0') curs++;
				err_pos_=curs;errnum=39;goto redo;
			}
			copy(s(6,2),tblin.code,fldlen(6,2));
			if(sr_nm_ || tblin.omschr[0]=='\0') copy(s(6,3),tblin.omschr,fldlen(6,3));
			tblin.rec=*u(6,1);
			fillart2tb(NO); stu2ram(k);
		}
    if(key==104){
      k=(curspos_-z_base)/q_per_line;
      if(curspos_<z_base || k<0){errnum=34; curs=curspos_;goto redo;}
      else {
				for(j=k+start_+1;j<max_line;j++){
					ram2stu(j); stu2ram(j-1);
				}
				zero((char *)p_tblin,len_tblin);
				stu2ram(max_line-1);
      }
			calc(0,NO);
      curs=curspos_; goto redo;
    }

    if(key==105){
      k=(curspos_-z_base)/q_per_line;
      if(curspos_<z_base || k<0 || k>=max_line-1){errnum=34; curs=curspos_;goto redo;}
      else {
				for(j=max_line-1;j>k+start_;j--){
					ram2stu(j-1); stu2ram(j);
				}
				zero((char *)p_tblin,len_tblin);
				stu2ram(k+start_);
      }
      curs=curspos_; goto redo;
    }
    if(key==5001 || key==110) load_art();

    for(k=start_;k<(start_+D_LIN_SCR);k++){
      ram2stu(k);
      if((tblin.code[0] || tblin.omschr[0]) && tblin.omschr[0]!='*' && tblin.hash!=hash()){
				fasinit(6);
				sr_nm_=NO;
				if(tblin.code[0]) {*s(6,3)='.';copy(tblin.code,s(6,3)+1,fldlen(6,2));}
				else {copy(tblin.omschr,s(6,3),fldlen(6,3));sr_nm_=YES;}
				if(search(6,0)){
					curs=z_base+1+ (k-start_)*q_per_line ; if(tblin.code[0]=='\0') curs++;
					err_pos_=curs;errnum=39;goto redo;
				}
				copy(s(6,2),tblin.code,fldlen(6,2));
				if(sr_nm_ || tblin.omschr[0]=='\0') copy(s(6,3),tblin.omschr,fldlen(6,3));
				tblin.rec=*u(6,1);
				fillart2tb(NO);
      }
      else if(tblin.code[0]=='\0' && tblin.omschr[0]=='\0'){
				zero((char *)&tblin,len_tblin);
      }
      if(tblin.groep==99){
				tblin.rec_leeg=*u(6,1);
				tblin.prx_leeg=tblin.vk_prx;
				tblin.q_leeg=1;
      }
      if(tblin.omschr[0]=='*'){
				tblin.accijns=0;
      }
      stu2ram(k);
    }
    calc(0,NO);
    if(key==108) break;
    if(key==109){
      k=(curspos_-z_base)/q_per_line;
      if(k<0) errnum=34;
      else{
				ram2stu(k+start_);
				if(tblin.omschr[0]=='\0') errnum=34;
				else {detail(start_+k);calc(0,NO);}
      }
    }
    start_=nstart_;
    if(key==18 || auto_enter){ /* automatische bladskip op einde van scherm */
      for(k=0;k<D_LIN_SCR;k++){ram2stu(start_+k);if(tblin.omschr[0]==0) break;}
      if(k==D_LIN_SCR) key=103;
    }
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=start_;k<start_+D_LIN_SCR;k++){ram2stu(k);if(tblin.omschr[0]=='\0') break;}
    if(k==start_+D_LIN_SCR) k=start_;curs=z_base + (k-start_)*q_per_line;
  }
  return NO;
}

static FindNewReference()
{
	int j,k,len_,max_;
	char ref_[11];

	if(ref_offerte[0]=='\0'){zero(ref_offerte,sizeof ref_offerte); sprintf_s(ref_offerte,7,"%04d-",*u(2,1));}
	zero(ref_,sizeof ref_);	len_=copy0(ref_offerte,ref_,10);
	len_=8-len_; if(len_>4) len_=4;
	max_=1;	for(k=0;k<len_;k++) max_*=10;
	fasclos(-2);
	for(k=1;k<max_;k++){
    zero(filnam,sizeof filnam);j=0;
		j+=copy0(MAP_OFFERTE,&filnam[j],20);
    j+=copy0(ref_offerte,&filnam[j],sizeof ref_offerte);
		stcli_d(&filnam[j],k,len_,0);j+=len_;
    j+=copy0(".csv",&filnam[j],6);
    if(fasopen(filnam,1)==0) fasclos(-2);
		else break;
	}
  zero(ref_offerte,sizeof ref_offerte);j=0;
	j=copy0(ref_,ref_offerte,10);
	if(k<max_) stcli_d(&ref_offerte[j],k,len_,0);
}

static wr_offerte()
{
	int16 z=1,key,k;

	fasunlck(-2);

	FOREVER{
redo:;
		scraddf(-1,0,0,0);z=1;
		DisplayMenuTitel(4,"Opslaan offerte",0xA);
		scraddf(z++,10,4,0); scraddf(z++,10,40,2);
		scraddf(z++,23,1,8);scraddf(z++,23,12,8); scraddf(z++,23,28,8);
		z=1;
		scrifld(z++,fm_os63,"Offerte opslaan onder referentie : ");
		scrifld(z++,fm_uref,ref_offerte);if(OrigFilnam[0]=='\0') scraddpicto(1,z-1,0,0,2,1,112,0,4,"Zoek vrije referentie"); 
		scrifld(z++,fm_os10," F1 terug");
		scrifld(z++,fm_os15,"F6 NIET opslaan");scrifld(z++,fm_os10," F8 sla op");
		key=scrupd(1,0xA1);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) return NO;
		if(key==106) return YES;
		if(key==5001) {FindNewReference(); goto redo;}
		if(ref_offerte[0]=='\0') {errnum=38; goto redo;}
		if(key==108){
			zero(filnam,sizeof filnam);k=0;
			k+=copy0(MAP_OFFERTE,&filnam[k],20);
			k+=copy0(ref_offerte,&filnam[k],sizeof ref_offerte);
			k+=copy0(".csv",&filnam[k],6);
			fasclos(-2);
			if(OrigFilnam[0] && cmpstr(OrigFilnam,filnam,sizeof filnam)){
				if(fasopen(filnam,1)==0){
					fasclos(-2);
					if(DisplayWarning("Er bestaat al een offerte onder deze naam! Overschrijven?",605,1)==NO) goto redo;
				}
			}
			errnum=fasopen(filnam,2);if(!errnum) break;
		}
	}

	copy(adrbuf,s(2,1),fldlen(2,0)); *u(2,1)=rec_pklt;
	fasinit(80);seqo_pos=0;seqo_mode=2;pos=0;
	zero(seqo_str,sizeof seqo_str);pos=0;
	char2str(ref_offerte,10);
	seqo_var(fm_udat,&ft_date);
	for(k=1;k<=7;k++) seqo_fld(2,k);
	seqo_fld(2,21);
	for(k=0;k<6;k++){
		char2str(opm_foot[k],sizeof opm_foot[0]);
	}
	char2str(str_tav,sizeof str_tav);
	seqo_var(fm_uu2,&OfferteMetAantal);
	dump_rec();

	for(k=0;k<max_line;k++){
		ram2stu(k);
		if(tblin.omschr[0]){
			flt2str((float)tblin.rec); // A
			char2str(tblin.code,15);
			char2str(tblin.omschr,40);
			flt2str(tblin.ak_prx);
			flt2str(tblin.accijns);
			flt2str(tblin.vk_prx); // F 
			flt2str(tblin.vk_prx_ex);
			flt2str(tblin.ft_kpct); // H
			flt2str(tblin.ft_kbdr);
			flt2str(tblin.ft_hlkort);
			flt2str(tblin.ft_korting);
			flt2str(tblin.ft_prx_ex);
			flt2str(tblin.ft_prx_in);
			flt2str(tblin.net_pr_ex);
			flt2str(tblin.net_pr_in);
			flt2str(tblin.sem_kpct);
			flt2str(tblin.sem_hlkort);
			flt2str(tblin.sem_korting);
			flt2str(tblin.inhoud);
			flt2str(tblin.btw);
			flt2str((float)tblin.groep);
			flt2str((float)tblin.rec_leeg);
			flt2str(tblin.q_leeg);
			flt2str(tblin.prx_leeg);
			flt2str(tblin.w_pct);
			flt2str((float)tblin.aantal);
			flt2str((float)tblin.tot_goederen);
			flt2str((float)tblin.tot_leeg);
			flt2str((float)tblin.brij_tk_pct);
			flt2str((float)tblin.brij_tk_eur);
			flt2str((float)tblin.brij_tk_tot);
			char2str(&tblin.stuksaantal,1);
			flt2str((float)tblin.q_per_bak);
			flt2str((float)tblin.q_per_palet);
			dump_rec();
		}
	}
	fasflush(0);
	fasclos(-2);
endsr:;
	fasunlck(-1);
	return YES;
}

static ld_offerte(mode_) // YES = geen scherm vragen, maar op inq_klt
{
  int16 z=1,key,k;
  char str_[20];

	if(mode_){
    if(SearchOfferte()) return NO;
    zero(filnam,sizeof filnam);k=0;
    k+=copy0(MAP_OFFERTE,&filnam[k],20);
    k+=copy0(ref_offerte,&filnam[k],sizeof ref_offerte);
    k+=copy0(".csv",&filnam[k],5);
    fasclos(-2);
    errnum=fasopen(filnam,1);if(errnum) return NO;
		copy(filnam,OrigFilnam,sizeof filnam);
		goto load_off;
	}
  FOREVER{
redo:;
		scraddf(-1,0,0,0);z=1;
	  DisplayMenuTitel(4,"Oproepen bestaande offerte",0xA);
    scraddf(z++,10,4,0); scraddf(z++,10,25,2);
    scraddf(z++,23,1,8);scraddf(z++,23,12,8);
    z=1;
		scrifld(z++,fm_os63,"Referentie offerte : ");
    scrifld(z++,fm_uref,ref_offerte);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_os10," F1 stop");scrifld(z++,fm_os15," F8 zoek op ");
    key=scrupd(1,0x81);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) return NO;
		if(key==5001){
		  if(SearchOfferte()) goto redo;
	  }
    if(ref_offerte[0]=='\0') {errnum=38; goto redo;}
    if(YES /* key==108 || key==5001*/){
      zero(filnam,sizeof filnam);k=0;
      k+=copy0(MAP_OFFERTE,&filnam[k],20);
      k+=copy0(ref_offerte,&filnam[k],sizeof ref_offerte);
      k+=copy0(".csv",&filnam[k],5);
      fasclos(-2);
      errnum=fasopen(filnam,1);
			if(!errnum){copy(filnam,OrigFilnam,sizeof filnam); break;}
    }
  }
load_off:;
	zero(adrbuf,sizeof adrbuf);fasinit(2);
  fasinit(80);
  zero(seqo_str,sizeof seqo_str);pos=0;
  if(read_rec(0)) {fasclos(-2); return NO;}
  z=0;
  get_str(ref_offerte,z++,10);
  zero(str_,sizeof str_);get_str(str_,z++,10); ft_date=str2date(str_);
  *u(2,1)=get_num(z++);
  for(k=2;k<=7;k++) get_str(s(2,k),z++,fldlen(2,k));
  get_str(s(2,21),z++,fldlen(2,21));
  for(k=0;k<6;k++){
    get_str(opm_foot[k],z++,sizeof opm_foot[0]);
  }
  get_str(str_tav,z++,sizeof str_tav);
	OfferteMetAantal=get_num(z++);

  for(k=0;k<max_line;k++){
    if(read_rec(1)) break; z=0;
    ram2stu(k);
    tblin.rec=get_num(z++);
		fasinit(6);if(tblin.rec){*u(6,1)=tblin.rec;fasgeti(6);}
    get_str(tblin.code,z++,15);
    get_str(tblin.omschr,z++,40);
    tblin.ak_prx=get_num(z++);
    tblin.accijns=get_num(z++);
    tblin.vk_prx=get_num(z++);
    tblin.vk_prx_ex=get_num(z++);
    tblin.ft_kpct=get_num(z++);
    tblin.ft_kbdr=get_num(z++);
    tblin.ft_hlkort=get_num(z++);
    tblin.ft_korting=get_num(z++);
    tblin.ft_prx_ex=get_num(z++);
    tblin.ft_prx_in=get_num(z++);
    tblin.net_pr_ex=get_num(z++);
    tblin.net_pr_in=get_num(z++);
    tblin.sem_kpct=get_num(z++);
    tblin.sem_hlkort=get_num(z++);
    tblin.sem_korting=get_num(z++);
    tblin.inhoud=get_num(z++);
    tblin.btw=get_num(z++);
    tblin.groep=get_num(z++);
    tblin.rec_leeg=get_num(z++);
    tblin.q_leeg=get_num(z++);
    tblin.prx_leeg=get_num(z++);
    tblin.w_pct=get_num(z++);
		tblin.aantal=get_num(z++);
		tblin.tot_goederen=get_num(z++);
		tblin.tot_leeg=get_num(z++);
		tblin.brij_tk_pct=get_num(z++);
		tblin.brij_tk_eur=get_num(z++);
		tblin.brij_tk_tot=get_num(z++);
		get_str(&tblin.stuksaantal,z++,1);
		tblin.q_per_bak=get_num(z++);
		tblin.q_per_palet=get_num(z++);
		if(fldlen(6,37)) tblin.inhoud=*f(6,37);
		if(fldlen(6,31)) tblin.q_per_bak=*f(6,31);
		if(fldlen(6,83)) tblin.q_per_palet=*f(6,83);
		if(tblin.inhoud){
			tblin.ft_hlkortHL=tblin.ft_hlkort/ (tblin.inhoud/100.);
	  	tblin.sem_hlkortHL=tblin.sem_hlkort/ (tblin.inhoud/100.);
		}
		tblin.hash=hash();
    stu2ram(k);
  }
  copy(s(2,1),adrbuf,fldlen(2,0)); rec_pklt=*u(2,1);
  fasflush(0);
  fasclos(-2);
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
		if(inq_klt==0 || *u(2,1)==inq_klt){ 
  		for(k=2;k<=7;k++) get_str(s(2,k),z++,fldlen(2,k));
	  	copy(s(2,1),tb_offerte[j].klantstu,s(2,8)-s(2,1));
		}
		else{
			for(k=j+1;k<q_offertes;k++) copy(tb_offerte[k].filname,tb_offerte[k-1].filname,sizeof tb_offerte[0]);
			zero(tb_offerte[q_offertes-1].filname,sizeof tb_offerte[0]);
			j--;q_offertes--;
		}
    fasclos(-2);
	}
  if(q_offertes==0) return YES;
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
			scrifld(z++,fm_os8,&tb_offerte[k].referentie);
			zero(str_,sizeof str_);
			copy(tb_offerte[k].klantstu,s(2,1),s(2,8)-s(2,1));
      j=copy0(s(2,3),&str_[0],fldlen(2,3));j+=copy0(" - ",&str_[j],3); j+=copy0(s(2,4),&str_[j],fldlen(2,4));str_[j++]='-';j+=copy0(s(2,6),&str_[j],fldlen(2,6));
      scrifld(z++,fm_os50,str_);  if(q_==(lijnpos+1)) scrchat(z-1,0x8); else scrchat(z-1,0xFF);
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
			scrifld(z++,fm_os8,&tb_offerte[j].referentie);
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

static fillart2tb(refresh_mode_) // refresh_mode_ YES : enkel prijzen ed vernieuwen, geen kortingen
int refresh_mode_;
{
  uint16 rec_;
 
  tblin.rec=*u(6,1);
  tblin.groep=*i(6,9);
  tblin.ak_prx=*f(6,18);
  if(fldlen(6,30)) tblin.accijns=*f(6,30);
  tblin.btw=*f(6,28);

  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd) tblin.ak_prx=*f(6,18+94);
  else tblin.ak_prx=*f(6,18);
	if(refresh_mode_==NO){
    tblin.ft_kpct=directpc;
    tblin.sem_kpct=semestpc;
	}
  copy(s(6,41),leeggcod,fldlen(6,41));
  tblin.q_leeg=*f(6,42);
  rec_=*u(6,1);fasinit(6);copy(leeggcod,s(6,2),fldlen(6,41));
  if(leeggcod[0]){
    if(search(6,2)==0){
      tblin.rec_leeg=*u(6,1);
      tblin.prx_leeg=*f(6,21);
    }
  }
  *u(6,1)=rec_;fasgeti(6);
	
  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd) tblin.accijns=*f(6,30+94);
  else tblin.accijns=*f(6,30);
  calc_prx=tblin.vk_prx;get_prx();
	if(refresh_mode_==NO) {if(calc_sem!=-99) tblin.sem_kpct=calc_sem;}/* sem. kort. van contrakt */
	if(fldlen(6,37)) tblin.inhoud=*f(6,37);
	if(fldlen(6,31)) tblin.q_per_bak=*f(6,31);
	if(fldlen(6,83)) tblin.q_per_palet=*f(6,83);
	if(refresh_mode_==NO){
    tblin.ft_hlkortHL=hl_korting;
    tblin.sem_hlkortHL=hl_semkort;
    tblin.ft_hlkort=ft_hlkorting;
    tblin.sem_hlkort=ft_semhlkorting;
	  tblin.brij_tk_pct=brij_tpct;
	  tblin.brij_tk_eur=brij_tbd;
	}
  if(refresh_mode_ || tblin.vk_prx==0 || (tblin.stuksaantal=='S' && tblin.q_per_bak>1) || (tblin.stuksaantal=='P' && tblin.q_per_palet>1)){
    tblin.vk_prx=calc_prx;
  }
	if(refresh_mode_==NO){
    if(tblin.ft_kpct==0 || newkort) tblin.ft_kpct=calc_kort;
    if(nokort) {tblin.ft_kpct=0;tblin.sem_kpct=0;}
	}
	if (tblin.stuksaantal == 'S' && tblin.q_per_bak>1) { // corrigeren naar stuks
		copy(s(6,44), leeggcod, fldlen(6,44));
		tblin.q_leeg = 1;
		rec_=*u(6,1); fasinit(6); copy(leeggcod, s(6,2), fldlen(6,44));
		if(leeggcod[0]){
			if(search(6,2)==0){
				tblin.rec_leeg=*u(6,1);
				tblin.prx_leeg=*f(6,21);
			}
		}
		*u(6,1)=rec_;fasgeti(6);
		tblin.ak_prx/= tblin.q_per_bak;
		tblin.inhoud/= tblin.q_per_bak;
		tblin.accijns/= tblin.q_per_bak;
	}

	if (tblin.stuksaantal == 'P' && tblin.q_per_palet > 1) {
		copy(s(6,41), leeggcod, fldlen(6,41));
		tblin.q_leeg *= tblin.q_per_palet;
		rec_ = *u(6,1);
		fasinit(6);
		copy(leeggcod, s(6,2), fldlen(6,41));

		if (leeggcod[0]) {
			if(search(6,2) == 0) {
				tblin.rec_leeg = *u(6,1);
				tblin.prx_leeg = *f(6,21);
			}
		}

		*u(6,1) = rec_;
		fasgeti(6);
		tblin.ak_prx *= tblin.q_per_palet;
		tblin.inhoud *= tblin.q_per_palet;
		tblin.accijns *= tblin.q_per_palet;
	}

  tblin.hash=hash();
}

static load_art()
{
  int16 k,mode_,nr_,fkey;
 
  seldata.prx_klt=*u(2,1);
  seldata.selp_use=NO;
  if(ovlcall(2215,2)) goto endsr;

  scrget(1,7);scrupd(-3,0);
  fasinit(6);mode_=1;nr_=0; fkey=2;
	if(seldata.sklt_used){ // in volgorde van bestelbon 
    for(k=0;k<fldlen(2,120)/2; k++){
      fasinit(6); *u(6,1)=*(uint16 *)(s(2,120)+k*2);
			if(*u(6,1)){
				fasgeti(6);
				if(DirCall_DRK2215_SelectArtikel()) {
					for(nr_;nr_<max_line;nr_++) {
						ram2stu(nr_); if(tblin.omschr[0]=='\0') break;
					}
					if(nr_>=max_line){errnum=11; break;}
 
					copy(s(6,2),tblin.code,fldlen(6,2));
					copy(s(6,3),tblin.omschr,fldlen(6,3));
					tblin.rec=*u(6,1);
					fillart2tb(NO);
					stu2ram(nr_);
				}
			}
    }
	}
	else{
		FOREVER{
			redo:;
			if(faskeyi(6,fkey,mode_)) break; mode_=2;
			if(DirCall_DRK2215_SelectArtikel()==NO) goto redo;
			for(nr_;nr_<max_line;nr_++) {
				ram2stu(nr_); if(tblin.omschr[0]=='\0') break;
			}
			if(nr_>=max_line){errnum=11; break;}
 
			copy(s(6,2),tblin.code,fldlen(6,2));
			copy(s(6,3),tblin.omschr,fldlen(6,3));
			tblin.rec=*u(6,1);
			fillart2tb(NO);
			stu2ram(nr_);
		}
	}
  endsr:;
}
 
 
static dspdetln(z,j,fmt_,pvar_)
int16 z,j;
char *fmt_,*pvar_;
{
  char *vpos_;

  vpos_=ram+(j*len_tblin)+(pvar_-p_tblin);
  scrifld(z,fmt_,vpos_);
}

static dsp_tot()
{
  int16 key,z,k,curs=1;
  double bd_;

  if(DrukOpEigenLayout!='J') DrukOpEigenLayout='J';
  rec_pklt=*u(2,1);prtwinstJN='N';
  copy(adrbuf,s(2,1),fldlen(2,0));
  if(*s(2,3)==0) {fasinit(2);*u(2,1)=rec_pklt;fasgeti(2);}

  FOREVER{
		redo:;
    scrnum=0;scrget(2,310);z=1;
		scraddpicto(1,0,72,22,4,2,583,0,0,"Maak PDF"); 
		scraddpicto(2,0,76,22,4,2,569,0,0,"Mail"); 
#if EIGENLAYOUT
    scraddfield(50,45,9,0x02);scrifld(50,VarTextFmt(26,0),"Drukken op eigen document ");
    scraddfield(51,71,9,0x02);scrifld(51,fm_u_JN,&DrukOpEigenLayout);
#endif
    scrfld(z++,2,3);
    scrifld(z++,fm_us30,str_tav);
    for(k=4;k<7;k++) scrfld(z++,2,k);scraddpicto(3,z-1,0,0,2,1,589,0,0,"Herdisplay"); ShowGoogleMapsButton(24,z-1,2,0,2,1,2); 
		if(OfferteMetAantal){bd_=belastbt+btw_tot; scrifld(z++,fm_od6_2,&bd_);} 	else z++;
    scrifld(z++,fm_udat,&ft_date);
		if(OfferteMetAantal){bd_=tot_leeg; scrifld(z++,fm_od6_2,&bd_);} 	else z++;
		scrifld(z++,fm_uref,ref_offerte); if(OrigFilnam[0]=='\0') scraddpicto(3,z-1,0,0,2,1,112,0,4,"Zoek vrije referentie"); 
		if(OfferteMetAantal){bd_=alg_tot; scrifld(z++,fm_od6_2,&bd_);} 	else z++;
		for(k=0;k<6;k++)scrifld(z++,fm_us75,opm_foot[k]);

/* stdkolJN : 0 = basispr, 1=nettopr, 2=accijns, 3=ftkort%, 4=ftkortbd
	      5 = semest%, 6=semestbd, 7=leeggoed, 8=factuurprijs
	      10= prijs ex.accijns, 11=firmahoofding, 12=Prijs incl.BTW NIET drukken
*/
		scrifld(z++,fm_u_JN,&prtkolJN[0]);  // basis
		if(!sys4731) scrifld(z++,fm_u_JN,&prtkolJN[2]); else z++; // accijns
		scrifld(z++,fm_u_JN,&prtkolJN[3]);  // ft kort%
		scrifld(z++,fm_u_JN,&prtkolJN[4]);  // ft korting EUR
		scrifld(z++,fm_u_JN,&prtkolJN[8]);  // factuurprijs
		if(!sys4731) scrifld(z++,fm_u_JN,&prtkolJN[5]); else z++;// sem %
		if(!sys4731) scrifld(z++,fm_u_JN,&prtkolJN[6]); else z++;  // sem.korting EUR
		scrifld(z++,fm_u_JN,&prtkolJN[1]); // nettoprijs
		scrifld(z++,fm_u_JN,&prtkolJN[12]); // GEEN incl.BTW prijs
		if(!sys4731) scrifld(z++,fm_u_JN,&prtkolJN[7]); else z++;// leeggoed
		scrifld(z++,fm_u_JN,&prtwinstJN);
    key=scrupd(curs,0x38B); curs=1;
	  prt2pdf=NO;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
		switch(key){
			case 5001 : prt2pdf=YES; key=108; break; // pdf
			case 5002 : prt2pdf=2;key=108; break; // mailen
			case 5003 : FindNewReference(); break; // zoek referentie
			default : break;
		}
		copy(s(2,1),adrbuf,fldlen(2,0));
    if(key==101){
      for(k=0;k<max_line;k++){ram2stu(k);if(tblin.omschr[0]) break;}
      if(k<max_line){
	      if(wr_offerte()) return 0;
      } else return 0;
    }
    if(key==102)return 3;
		taaltxt=0; 
		if(fldlen(2,24)){
			fasinit(2);*u(2,1)=rec_pklt;fasgeti(2);
			taaltxt=*s(2,24); 
      copy(adrbuf,s(2,1),fldlen(2,0));
		}
    if(key==108) {
			if(ref_offerte[0]=='\0') {errnum=38;curs=9;goto redo;}
      prt_offerte();
			if(prt2pdf==2) {MailDocument(0);prt2pdf=0;}
      for(k=0;k<max_line;k++){ram2stu(k);if(tblin.omschr[0]) break;}
      if(k<max_line){
        if(wr_offerte()) return 0;
      } else return 0;
    }
  }
  return YES;
}

static MailDocument(SendMode) // 0=tonen, 1=direct versturen
int SendMode;
{
  int k,p_adr_=0;
	uint16 dt_,yy,mm,dd;
	  
		// keywords invullen 
	zero(MailMergeData[0],sizeof MailMergeData);MailSaveAdres='N';


	dt_=ft_date;
	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy(s(2,3),MailMergeData[k],fldlen(2,3)); continue;}
		if(cmpstr(MailMergeKeywords[k],"ADRES",5)==0){copy(s(2,4),MailMergeData[k],fldlen(2,4)); continue;}
		if(cmpstr(MailMergeKeywords[k],"POSTCODE",8)==0){copy(s(2,5),MailMergeData[k],fldlen(2,5)); continue;}
		if(cmpstr(MailMergeKeywords[k],"GEMEENTE",8)==0){copy(s(2,6),MailMergeData[k],fldlen(2,6)); continue;}
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){p_adr_=k;copy(s(2,21),MailMergeData[k],fldlen(2,21)); continue;}
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNAAM",12)==0){copy0("Offerte",MailMergeData[k],50);continue;}

		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNUMMER",13)==0){copy0(ref_offerte,MailMergeData[k],10);continue;}
		if(cmpstr(MailMergeKeywords[k],"DATUM",5)==0){
			jddate(dt_,&yy,&mm,&dd);
      stcli_d(&MailMergeData[k][0],(long)dd,2,0);MailMergeData[k][2]='/';
      stcli_d(&MailMergeData[k][3],(long)mm,2,0);MailMergeData[k][5]='/';
      stcli_d(&MailMergeData[k][6],(long)yy,4,0);
			continue;
		}
//		if(cmpstr(MailMergeKeywords[k],"TOTAALBEDRAG",12)==0){stcli_d(MailMergeData[k],(long)(nr_),5,1); continue;}
	}
	zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage); // voor de veiligheid
	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);MailMergeBijlage[0]=SpoolFileNr;
	MailMergeFormaat=8; 
	if(fldlen(2,24)) MailMergeTaal=talen[taaltxt]; else MailMergeTaal='\0';
	k=SendMail(SendMode); 
	// hier NIET owv prijslijstklant ! if(k && MailSaveAdres=='J'){copy(MailMergeData[p_adr_],s(2,21),fldlen(2,21));fasupd(2);} // email adres bewaren
}

static ft_init()
{
  int16 j,k;
 
  fasinit(2);fasinit(6);copy(s(2,3),old_kltnm,fldlen(2,3));rec_pklt=0;
  ft_date=*u(25,2); zero(ref_offerte,sizeof ref_offerte);zero(adrbuf,sizeof adrbuf);
  semestpc=0;directpc=0;OfferteMetAantal=NO;
  zeroL(ram,ram_size);
  zero((char *)p_tblin,len_tblin);
  for(k=0;k<max_line;k++) stu2ram(k);
  zero(opm_foot[0],sizeof opm_foot);
  zero(str_tav,sizeof str_tav);
  prxnr=*s(2,26)-'0';
  if(prxnr<0 || prxnr>9) prxnr=0;
  if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
  fmt_get(6,PrNrs[prxnr]);copy(fmt,fm_prx,sizeof fmt);
  k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;
	zero(OrigFilnam,sizeof OrigFilnam);
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

static mk_name(adr_pref,ps)
uint16 adr_pref;
char *ps;
{
  char *pd;
				
  pd=filnam;
  sysget(adr_pref,25,pd);
  while(*pd) pd++;
  while(*ps!='\0') *pd++=*ps++;
  *pd='\0';
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

static detail(nr_)
int16 nr_;
{
  int16 curs=1,key,z,inc_btw_,mode_calcprx_=NO;
	float bruto_wpct_=0,prx_,w_EUR_;

  ram2stu(nr_);
  fasinit(6);*u(6,1)=tblin.rec; if(*u(6,1)) fasgeti(6);
  calc(nr_,YES);

	inc_btw_=NO;if(sys3894 & (1<<prxnr)) inc_btw_=YES;
  if(tblin.ak_prx) bruto_wpct_=(tblin.vk_prx_ex-tblin.ak_prx+tblin.brij_tk_tot)/tblin.ak_prx * 100.;
	else bruto_wpct_=0;

	 FOREVER{
    redo:
    scrnum=0;scrget(2,311);z=1;
    scrofld(z++,6,2,-1);
    scrofld(z++,6,3,-1);
    if(sys3894 & (1<<prxnr)) scrifld(z++,fm_os10,"(Incl.BTW)");
    else scrifld(z++,fm_os10,"(Excl.BTW)");
    
		if(mode_calcprx_){
			scrifld(z++,fm_of6_2,&tblin.vk_prx); 
			scrifld(z++,fm_uf3_2,&bruto_wpct_);
		}
		else{
			scrifld(z++,fm_uf6_2,&tblin.vk_prx); 
			scrifld(z++,fm_of3_2,&bruto_wpct_);
			fmt_get(58,21);scrifld(z++,fmt,&tblin.ft_kpct);
			scrifld(z++,fm_uf4_2,&tblin.ft_hlkortHL);
			scrifld(z++,fm_of6_2,&tblin.ft_korting);
			scrifld(z++,fm_of6_2,&tblin.ft_prx_ex);
			scrifld(z++,fm_of6_2,&tblin.ft_prx_in);
			scrifld(z++,fm_of6_2,&tblin.prx_leeg);
			fmt_get(58,21);scrifld(z++,fmt,&tblin.sem_kpct);
			scrifld(z++,fm_uf4_2,&tblin.sem_hlkortHL);
			scrifld(z++,fm_of6_2,&tblin.sem_korting);
			fmt_get(6,30);scrifld(z++,fmt,&tblin.accijns);
			scrifld(z++,fm_uf20_,&tblin.btw);
			scrifld(z++,fm_of6_2,&tblin.ak_prx);
			fmt_get(9,23);scrifld(z++,fmt,&tblin.brij_tk_pct);
			scrifld(z++,fm_uf4_2,&tblin.brij_tk_eur);
			scrifld(z++,fm_of6_2,&tblin.brij_tk_tot);
			scrifld(z++,fm_of3_2,&tblin.w_pct);
			w_EUR_=Round((double)(tblin.ak_prx*tblin.w_pct/100.),prx_afrond);scrifld(z++,fm_of4_2,&w_EUR_);
			if(tblin.w_pct<=0) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);
		}
    key=scrupd(curs,0x02E0);curs=3;
    if(key==106){ram2stu(nr_);break;}
		if(mode_calcprx_){
			prx_= (tblin.ak_prx-tblin.brij_tk_tot) * (100.+bruto_wpct_)/100.;
			if(inc_btw_) tblin.vk_prx=Round((double)(prx_* (100.+tblin.btw)/100.),prx_afrond);
			else tblin.vk_prx=Round((double)(prx_),prx_afrond);
		}
		if(key==110){
			if(mode_calcprx_==NO){mode_calcprx_=YES; goto redo;}
			else mode_calcprx_=NO;
		}
		if(fldlen(6,37)) tblin.inhoud=*f(6,37);
		if(fldlen(6,31)) tblin.q_per_bak=*f(6,31);
		if(fldlen(6,83)) tblin.q_per_palet=*f(6,83);
		if(tblin.inhoud){
			tblin.ft_hlkort=tblin.ft_hlkortHL* tblin.inhoud/100.;
	  	tblin.sem_hlkort=tblin.sem_hlkortHL* tblin.inhoud/100.;
		}
		else{
			tblin.ft_hlkort=0;tblin.ft_hlkortHL=0;
			tblin.sem_hlkort=0;tblin.sem_hlkortHL=0;
		}
    stu2ram(nr_);
    if(key==108) break;
    calc(nr_,YES);
		if(mode_calcprx_==NO){
      if(tblin.ak_prx) bruto_wpct_=(tblin.vk_prx_ex-tblin.ak_prx+tblin.brij_tk_tot)/tblin.ak_prx * 100.;
	    else bruto_wpct_=0;
		}
  }
}
 

static calc(nr_,mode_) // YES=enkel deze lijn, NO=alles
int16 nr_,mode_;
{
  int16 j,k,max_,inc_btw_;
  float prx_,bd_accijn=0,prx_r,netto_;
	double tot_akw_=0,tot_vkw_=0;

	if(mode_==NO){ 
	  tot_leeg=0;semestbd=0;tot_winst=0; tot_wpct=0;
    zero((char *)btw_bas,sizeof btw_bas);
	}
									
  inc_btw_=NO;if(sys3894 & (1<<prxnr)) inc_btw_=YES;
  if(mode_) max_=nr_+1; else max_=max_line;
  for(k=nr_;k<max_;k++){
    ram2stu(k);
    if(tblin.omschr[0]=='*' && tblin.btw==0) tblin.btw=def_btw;
    prx_=tblin.vk_prx;
    if(tblin.groep==99) prx_=0;
    if(inc_btw_) prx_/=1.+tblin.btw/100.;
    tblin.vk_prx_ex=Round((double)prx_,prx_afrond);
    bd_accijn=tblin.accijns;
    if(prx_>=0){/* bedrag accijns mag niet groter zijn de ehpr */
      if(bd_accijn>prx_) bd_accijn=prx_;
    }
    else {
      bd_accijn=-bd_accijn;
      if(bd_accijn<prx_) bd_accijn=prx_;
    }
    prx_r=prx_;
    if(tblin.ft_kpct){
      prx_=(prx_-bd_accijn)*(100.- tblin.ft_kpct)/100.+bd_accijn;
    }
    prx_-=tblin.ft_hlkort;
    tblin.ft_korting=prx_r-prx_;
    tblin.ft_korting=Round((double)tblin.ft_korting,prx_afrond);
    tblin.ft_prx_ex=Round((double)prx_,prx_afrond);
    tblin.ft_prx_in=prx_* (1.+tblin.btw/100.);
#if FLAGDOM
		tblin.ft_prx_in=tblin.vk_prx*(100.- tblin.ft_kpct)/100.;
#endif
    tblin.ft_prx_in=Round((double)tblin.ft_prx_in,prx_afrond);

    tblin.sem_korting=0;
    if(tblin.sem_kpct){
      tblin.sem_korting=(prx_-bd_accijn)*tblin.sem_kpct/100.;
    }
    tblin.sem_korting+=tblin.sem_hlkort;
    tblin.sem_korting=Round((double)tblin.sem_korting,prx_afrond);
    netto_=tblin.ft_prx_ex-tblin.sem_korting;
    tblin.net_pr_ex=Round((double)netto_,prx_afrond);
    tblin.net_pr_in=netto_* (1.+tblin.btw/100.);
#if FLAGDOM
		tblin.net_pr_in=tblin.vk_prx*(100.- tblin.ft_kpct)/100.;
#endif
    tblin.net_pr_in=Round((double)tblin.net_pr_in,prx_afrond);

		tblin.brij_tk_tot=0; //  tussenkomst brij voor winstberekening
    if(tblin.brij_tk_pct) tblin.brij_tk_tot=(prx_r-bd_accijn)* tblin.brij_tk_pct/100.;
    tblin.brij_tk_tot+=tblin.brij_tk_eur; 
		tblin.brij_tk_tot=Round((double)tblin.brij_tk_tot,prx_afrond);

    if(tblin.ak_prx) tblin.w_pct=(netto_-tblin.ak_prx+tblin.brij_tk_tot)/tblin.ak_prx * 100.;
    else tblin.w_pct=0;
		tblin.tot_leeg=tblin.aantal*tblin.q_leeg*tblin.prx_leeg;
		tblin.tot_goederen=tblin.aantal*tblin.ft_prx_ex;
		tblin.tot_goed_inc=Round((double)(tblin.aantal*tblin.ft_prx_in),ft_afrond);
		tblin.w_EUR=tblin.ak_prx*tblin.w_pct/100.;
		if(mode_==NO){
			if(tblin.aantal) tblin.w_EUR=tblin.w_EUR*tblin.aantal;
			tot_akw_+=tblin.ak_prx*tblin.aantal; tot_vkw_+=netto_*tblin.aantal;
			tot_leeg+=tblin.tot_leeg;
      for(j=0;j<BTWDIM-BTWDIV;j++) if(tblin.btw==btw_pct[j]) break;
			btw_bas[j]+=tblin.tot_goederen;
			semestbd+=tblin.aantal*tblin.sem_korting;
		}
		tblin.w_EUR=Round((double)(tblin.w_EUR),ft_afrond);
    stu2ram(k);
  }
	if(mode_==NO){
		tot_winst=tot_vkw_-tot_akw_; if(tot_akw_) tot_wpct=Round((double)((tot_winst/tot_akw_)*100.),(double)0.1); 
    belastbt=0;
    for(k=0;k<BTWDIM-BTWDIV;k++) belastbt+=btw_bas[k];
		btw_tot=0;
		for(k=0;k<BTWDIM;k++){
			btw_bd[k]=Round((double)(btw_bas[k]*btw_pct[k])/100.,ft_afrond);
			btw_tot+=btw_bd[k];
		}
		tot_leeg=Round((double)tot_leeg,ft_afrond);
		alg_tot=belastbt+btw_tot+tot_leeg;
	}
}

static full_chk()
{
  if(free<2){
		prtnew();
		prtform(1);
		
		PrintHeader(KarPerLine);
	}
}
 
static prt_offerte()
{
  int16 j,k,printed_;
	char omschr_[50];
	float ori_btw_;
	double bedrag_;

#if EIGENLAYOUT
	if(DrukOpEigenLayout=='J') {PrintEigenOfferte(); goto endsr;}
#endif

	/* stdkolJN : 0 = basispr, 1=nettopr, 2=accijns, 3=ftkort%, 4=ftkortbd
	      5 = semest%, 6=semestbd, 7=leeggoed, 8=factuurprijs
	      10= prijs ex.accijns, 11=firmahoofding
*/

	KarPerLine=0;
	if(OfferteMetAantal) KarPerLine+=19;
	KarPerLine+=fldlen(6,2)+fldlen(6,3)+1;
	for(k=0;k<10;k++){
		if(prtkolJN[k]=='J'){
			switch(k){
			  case 0 : KarPerLine+=9; break;
				case 1 : KarPerLine+=9; if(prtkolJN[8]!='J' && (sys3894 & (1<<prxnr)) /* !OfferteMetAantal*/) KarPerLine+=9;  break;
				case 2 : KarPerLine+=9; break;
				case 3 : KarPerLine+=4; break;
				case 4 : KarPerLine+=9; break;
				case 5 : KarPerLine+=4; break;
				case 6 : KarPerLine+=9; break;
				case 7 : KarPerLine+=9; break;
				case 8 : KarPerLine+=9; if(prtkolJN[1]!='J' && !OfferteMetAantal) KarPerLine+=9;break;
				default: break;
			}
		}
	}
  KarPerLine+=4; // btw
	if(prtwinstJN=='J') KarPerLine+=17;
	if(KarPerLine<=80) KarPerLine=80;
	else if(KarPerLine<=96) KarPerLine=96;
	else KarPerLine=132;
  getsysprNew(8,form_dat,&pr_mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if (prtopen(prtnr,form_dat,6,KarPerLine,pr_mode,2)!=0) {goto endsr;}
	zero(omschr_,sizeof omschr_);if(taaltxt==1) copy("Offre ",omschr_,8); else copy("Offerte ",omschr_,8);
  copy(s(2,3),&omschr_[8],10);
  p_pdfname(omschr_,ft_date,0);
  scrget(1,6);scrupd(-3,0);

  PrintHeader(KarPerLine);
  nextline();
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(tblin.omschr[0]){
      full_chk(); 

      tblin.prx_bruto=tblin.vk_prx_ex;
      if(prtkolJN[10]=='J') tblin.prx_bruto-=tblin.accijns;
      zero(tblin.print_omschr,sizeof tblin.print_omschr);
      if(tblin.omschr[0]=='*'){
				copy(&tblin.omschr[1],tblin.print_omschr,39);
				if(tblin.tot_goederen==0){ //geen BTW% drukken bij losse tekst
					ori_btw_=tblin.btw;tblin.btw=0;
				}
			}
      else copy(tblin.omschr,tblin.print_omschr,40);
      for(j=1;j<20;j++){
				if(j==3 && tblin.ft_prx_in==0 && tblin.aantal==0 && tblin.prx_leeg==0 && tblin.omschr[0]!='*') break;
				if(j==z_netto) prtinfo(j,2); else prtinfo(j,0);
      }
      nextline();
      if(tblin.omschr[0]=='*' &&  tblin.tot_goederen==0) 	tblin.btw=ori_btw_; // terugzetten
    }
  }
  if(free<32 && free>26) {nextline();nextline();}
  else skip_lin(32);
  printed_=NO;
  for(k=0;k<6;k++){
    if(opm_foot[k][0]!='\0'){
      printed_=YES; full_chk(); 
      prtifld(fm_us75,opm_foot[k],-1);nextline();
    }
  }
  if(printed_) nextline();
  for(k=0;k<4;k++){
    prtifld(fm_us75,std_foot[k],-1);nextline();
  }
	if(OfferteMetAantal){
#if FLAGDOM
		skip_lin(20);
#else 
		skip_lin(10);
#endif
		for(j=0;j<3;j++){
			prttext("<t3>");
			for(k=0;k<BTWDIM-BTWDIV+1;k++){
				if(btw_bas[k]){
	       	prtblank(2);
		      if(j==0){prtblank(3);prtifld(fm_uf21_,&btw_pct[k],-1);prttext(" % ");}
					else{
						if(j==1) bedrag_=btw_bas[k];
						if(j==2) bedrag_=btw_bd[k];
						prtifld(fm_od5_2,&bedrag_,-1);prtblank(1);
					}
				}
			}
			if(j==0){
#if !FLAGDOM
				if(taaltxt==1) prttext("<t51>Vidange:"); else prttext("<t50>Leeggoed:");
#endif
				bedrag_=tot_leeg;
			}
			else if(j==1){
				if(taaltxt==1) prttext("<t46>Marchandises:"); else prttext("<t50>Goederen:");
				bedrag_=belastbt;
			}
			else{
				if(taaltxt==1) prttext("<t52>T.V.A.:"); else prttext("<t52>B.T.W.:");
				bedrag_=btw_tot;
			}
			prttext("<t69>");prtifld(fm_od6_2,&bedrag_,-1);
			nextline();nextline();
		}
		if(taaltxt==1) prttext("<t51>A payer:"); else prttext("<t48>Te betalen:");
		prttext("<t65b>EUR");
		prttext("<t69>");prtifld(fm_od6_2,&alg_tot,-1);
		nextline();
	}
  prtform(0);
  SpoolFileNr=prtclose();
  
  endsr:;
}

static PrintHeader(int16 linelen_)
{
	int16 z;

  ft_hdr(linelen_);
  prttext("<t85>Pag.<ppp>");prtbuf(1);
  fmt_get(6,PrNrs[prxnr]);copy(fmt,fm_prx,sizeof fmt);
  z=1; z_netto=-1;
	if(OfferteMetAantal) {
		prtitab(z++,fm_uf5_0,&tblin.aantal,1,-1);
		prtitab(z++,fm_os1,&tblin.stuksaantal,1,-1);
	}
  fmt_get(6,2); prtitab(z++,fmt,tblin.code,1,-1); //prttitle(z++,"Code",3);
  fmt_get(6,3); prtitab(z++,fmt,tblin.print_omschr,0,-1); //if(taaltxt==1) prttitle(z++,"Description",3); else prttitle(z++,"Omschrijving",3);

/* stdkolJN : 0 = basispr, 1=nettopr, 2=accijns, 3=ftkort%, 4=ftkortbd
	      5 = semest%, 6=semestbd, 7=leeggoed, 8=factuurprijs
	      10= prijs ex.accijns, 11=firmahoofding, 12= prijs incl BTW NIET drukken
*/

  if(prtkolJN[0]=='J'){
#if FLAGDOM
    prtitab(z++,fm_of4_2,&tblin.vk_prx,0,-1);
#else
    prtitab(z++,fm_of4_2,&tblin.prx_bruto,0,-1);
#endif
//    if(taaltxt==1) prttitle(z++,"Base",0x13); else prttitle(z++,"Basis",0x13);

  }
  if(prtkolJN[2]=='J' || prtkolJN[10]=='J'){
    prtitab(z++,fm_of4_2,&tblin.accijns,0,-1);
//		if(prtkolJN[10]=='J') {if(taaltxt==1) prttitle(z++,"Accises",0x13); else prttitle(z++,"Accijns",0x13);}
//    else prttitle(z++,"Acc.inc",0x13);
  }
  if(prtkolJN[3]=='J'){
    prtitab(z++,fm_of3_0,&tblin.ft_kpct,0,-1);// if(taaltxt==1) prttitle(z++,"R%",0x13); else prttitle(z++,"K%",0x13);
  }
  if(prtkolJN[4]=='J'){
    prtitab(z++,fm_of4_2,&tblin.ft_korting,0,-1); //if(taaltxt==1) prttitle(z++,"Rist.Ft",0x13); else prttitle(z++,"Ft.kort",0x13);
  }
  if(prtkolJN[8]=='J'){
    if(prtkolJN[1]!='J') z_netto=z;
    prtitab(z++,fm_of5_2,&tblin.ft_prx_ex,0,-1);// if(taaltxt==1) prttitle(z++,"Prix Ft",0x13); else prttitle(z++,"Ft.prijs",0x13);
    if(prtkolJN[1]!='J' && OfferteMetAantal==NO && prtkolJN[12]!='J'){
      prtitab(z++,fm_of4_2,&tblin.ft_prx_in,0,-1);//if(taaltxt==1) prttitle(z++,"TVA Inc",0x13); else prttitle(z++,"Inc.BTW",0x13);
    }
	}
  if(prtkolJN[5]=='J'){
    prtitab(z++,fm_of3_0,&tblin.sem_kpct,0,-1); //prttitle(z++,"S%",0x13);
  }
  if(prtkolJN[6]=='J'){
    prtitab(z++,fm_of5_2,&tblin.sem_korting,0,-1);// if(taaltxt==1) prttitle(z++,"Rist.Sem",0x13); else prttitle(z++,"Sem.kort",0x13);
	}
  if(prtkolJN[1]=='J'){
    z_netto=z;

#if FLAGDOM
    if(prtkolJN[8]!='J' && prtkolJN[12]!='J'){
#else
    prtitab(z++,fm_of4_2,&tblin.net_pr_ex,0,-1); //if(taaltxt==1) prttitle(z++,"Net",0x13); else prttitle(z++,"Netto",0x13);
    if(/* prtkolJN[8]!='J' && */ (sys3894 & (1<<prxnr)) /* OfferteMetAantal==NO */ && prtkolJN[12]!='J'){
#endif
      prtitab(z++,fm_of4_2,&tblin.net_pr_in,0,-1);// if(taaltxt==1) prttitle(z++,"TVA Inc",0x13); else prttitle(z++,"Inc.BTW",0x13);
    }
  }
  if(prtkolJN[7]=='J'){
    prtitab(z++,fm_of4_2,&tblin.prx_leeg,0,-1);  // if(taaltxt==1) prttitle(z++,"Vidange",0x13); else prttitle(z++,"Leegg.",0x13);
  }
  if(OfferteMetAantal){
#if FLAGDOM
		prtitab(z++,fm_od5_2,&tblin.tot_goed_inc,1,-1);
#else
		prtitab(z++,fm_od5_2,&tblin.tot_goederen,1,-1);
	  prtitab(z++,fm_od5_2,&tblin.tot_leeg,1,-1);
#endif
	}
  prtitab(z++,fm_of3_0,&tblin.btw,0,-1); //  if(taaltxt==1) prttitle(z++,"T%",0x13); else prttitle(z++,"B%",0x13);
	if(prtwinstJN=='J'){
    prtitab(z++,fm_of4_2,&tblin.w_pct,0,-1);  
		prtitab(z++,fm_of5_2,&tblin.w_EUR,0,-1);
	}

  prtbuf(2);

  z=1;
	if(OfferteMetAantal){
    if(taaltxt==1) prttitle(z++,"Quant.",0x13); else prttitle(z++,"Aantal",0x13);
		prttitle(z++,"",3);
	}
  prttitle(z++,"Code",3);
  if(taaltxt==1) prttitle(z++,"Description",3); else prttitle(z++,"Omschrijving",3);
	if(prtkolJN[0]=='J') {if(taaltxt==1) prttitle(z++,"Base",0x13); else prttitle(z++,"BasisPr",0x13);}
  if(prtkolJN[2]=='J' || prtkolJN[10]=='J'){
		if(prtkolJN[10]=='J') {if(taaltxt==1) prttitle(z++,"Accises",0x13); else prttitle(z++,"Accijns",0x13);}
    else prttitle(z++,"Acc.inc",0x13);
  }
	if(prtkolJN[3]=='J'){ if(taaltxt==1) prttitle(z++,"R%",0x13); else prttitle(z++,"K%",0x13);}
	if(prtkolJN[4]=='J'){ if(taaltxt==1) prttitle(z++,"Rist.Ft",0x13); else prttitle(z++,"Ft.kort",0x13);}
  if(prtkolJN[8]=='J'){ 
#if FLAGCRA
		if(taaltxt==1) prttitle(z++,"Prix Ft",0x13); else prttitle(z++,"Uw prijs",0x13);
#else
		if(taaltxt==1) prttitle(z++,"Prix Ft",0x13); else prttitle(z++,"Fact.Pr",0x13);
#endif
	  if(prtkolJN[1]!='J' && OfferteMetAantal==NO && prtkolJN[12]!='J'){if(taaltxt==1) prttitle(z++,"TVA Inc",0x13); else prttitle(z++,"Inc.BTW",0x13);}
  }
  if(prtkolJN[5]=='J') prttitle(z++,"S%",0x13);
	if(prtkolJN[6]=='J'){if(taaltxt==1) prttitle(z++,"Rist.Sem",0x13); else prttitle(z++,"Sem.kort",0x13);}
	if(prtkolJN[1]=='J') {

#if FLAGDOM
		if(prtkolJN[8]!='J' && prtkolJN[12]!='J'){
#else
		if(taaltxt==1) prttitle(z++,"PrixNet",0x13); else prttitle(z++,"NettoPr",0x13);
		if(/* prtkolJN[8]!='J' && */(sys3894 & (1<<prxnr)) /* OfferteMetAantal==NO*/ && prtkolJN[12]!='J'){
#endif
			if(taaltxt==1) prttitle(z++,"TVA Inc",0x13); else prttitle(z++,"Inc.BTW",0x13);
		}
  }
#if !FLAGDOM
	if(prtkolJN[7]=='J'){ if(taaltxt==1) prttitle(z++,"Vidange",0x13); else prttitle(z++,"Leegg.",0x13);}
#endif
	if(OfferteMetAantal){
    if(taaltxt==1) prttitle(z++,"Montant",0x13); else prttitle(z++,"Totaal",0x13);
#if !FLAGDOM
    if(taaltxt==1) prttitle(z++,"Vidange",0x13); else prttitle(z++,"Leeggoed",0x13);
#endif
	}
  if(taaltxt==1) prttitle(z++,"T%",0x13); else prttitle(z++,"B%",0x13);
	if(prtwinstJN=='J'){
		prttitle(z++,"W%",0x13);
		prttitle(z++,"W.EUR",0x13);
	}
  nextline();

}

static ft_hdr(int16 linelen_)
{
  int16 j,k,stu_;
  char *ps,str_[10];

  stu_=2; copy(adrbuf,s(2,1),fldlen(2,0));
  free=999;
  if(prtkolJN[11]!='J'){nextline();goto no_hdr;}
  prttext("<t1><eb>");prtifld(fm_os79,&firma[0],30);prttext("<eb>");nextline();
  prttext("<t1>");prtifld(fm_os79,&firma[31],25);
  nextline();
  prttext("<t1>");prtifld(fm_os79,&firma[57],7);prtblank(2);
  prtifld(fm_os79,&firma[65],20);
  nextline();
  if(free>66) nextline();
  for(k=0;k<9;k++){
		if(k==3 || k==4 || k==5) continue;
    if(firma[firm[k].begpos]){
      prttext("<t1>");ps=firm[k].txt[taaltxt];prttext(ps);
      for(j=0;j<12;j++) if(*ps++=='\0') break;
      for(;j<12;j++) prtblank(1);prttext(": ");
      prtifld(fm_os79,&firma[firm[k].begpos],firm[k].lengte);
      nextline();
    }
  }

 no_hdr:;
  skip_lin(60);
	if(linelen_==132) copy("<t75>",str_,10);
	else if(linelen_==96) copy("<t57>",str_,10);
	else copy("<t40>",str_,10);
  prttext(str_);prtfld(stu_,3,-1);nextline();
  prttext(str_);prtifld(fm_us30,str_tav,-1);nextline();
  prttext(str_);prtfld(stu_,4,-1);nextline();
  prttext(str_);prtfld(stu_,5,-1);prtblank(1);prtfld(stu_,6,-1);nextline();
  if(fldlen(stu_,7)>0){
    prttext(str_);prtfld(stu_,7,-1);
    nextline();
  }
	nextline();nextline();
  skip_lin(52);

  if(taaltxt==1) prttext("<t1><be>Offre<be>"); else prttext("<t1><be>Offerte<be>");
  if(taaltxt==1) prttext("<t30>R…f…rence : ");else prttext("<t30>Referentie : "); prtifld(fm_uref,ref_offerte,-1);
  if(taaltxt==1) prttext("<t60>Date : "); else prttext("<t60>Datum : "); prtifld(fm_udat,&ft_date,-1);
  nextline();nextline();
  skip_lin(49);
}

#if FLAGHOE // offerte met layout
static PrintEigenOfferte()
{
  int16 j,k,printed_,len_;
  char omschr_[50];
  double bedrag_;


  copy(adrbuf,s(2,1),fldlen(2,0));

  getsysprNew(23,form_dat,&pr_mode,&prtnr);
  if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if (prtopen(prtnr,form_dat,6,80,pr_mode,2)!=0) {goto endsr;}
  zero(omschr_,sizeof omschr_);if(taaltxt==1) copy("Offre ",omschr_,8); else copy("Offerte ",omschr_,8);
  copy(s(2,3),&omschr_[8],10);
  p_pdfname(omschr_,ft_date,0);
  scrget(1,6);scrupd(-3,0);


  PrintEigenHeader();
  fmt_get(6,PrNrs[prxnr]);copy(fmt,fm_prx,sizeof fmt);
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(tblin.omschr[0]){
      if((free)<8){prtform(0);PrintEigenHeader();}
	  fmt_get(6,2); prttext("<t1>");prtifld(fmt,tblin.code,-1); 
      zero(tblin.print_omschr,sizeof tblin.print_omschr);
      if(tblin.omschr[0]=='*') copy(&tblin.omschr[1],tblin.print_omschr,39);
      else copy(tblin.omschr,tblin.print_omschr,40);
	  fmt_get(6,3); prttext("<t11>");prtifld(fmt,tblin.print_omschr,-1);
	  prttext("<t41>"); prtifld(fm_prx,&tblin.prx_leeg,-1); 
	  prttext("<t51>"); prtifld(fm_prx,&tblin.net_pr_ex,-1); 
	  prttext("<t62>");prtifld(fm_of3_0,&tblin.btw,-1); 
      nextline();
    }
  }
  if(free<32 && free>26) {nextline();nextline();}
  else skip_lin(32-3);
  printed_=NO;
  for(k=0;k<6;k++){
    if(opm_foot[k][0]!='\0'){
      printed_=YES; if((free)<8){prtform(0);PrintEigenHeader();}
       prttext("<t1>");prtifld(fm_us75,opm_foot[k],-1);nextline();
    }
  }
  if(printed_) nextline();
  for(k=0;k<4;k++){
     prttext("<t1>");prtifld(fm_us75,std_foot[k],-1);nextline();
  }
  prtform(0);
  SpoolFileNr=prtclose();
  
  endsr:;
}

static PrintEigenHeader()
{
  int16 k;
    
  nextline();
  skip_lin(60-3);
  prttext("<t47>");prtfld(2,3,-1);nextline();
  prttext("<t47>");prtifld(fm_us30,str_tav,-1);nextline();
  prttext("<t47>");prtfld(2,4,-1);nextline();
  prttext("<t47>");prtfld(2,5,-1);prtblank(1);prtfld(2,6,-1);nextline();
  if(fldlen(2,7)>0){
    prttext("<t47>");prtfld(2,7,-1);
    nextline();
  }
  skip_lin(54-3);
  prttext("<eb>Offerte<eb>");nextline();
  skip_lin(51-3);
  prtifld(fm_uref,ref_offerte,-1);
  prttext("<t23>");
  k=1; if(fldlen(2,2)) k=2;
  prtfld(2,k,-1);
  prttext("<t38>");prtifld(fm_udat,&ft_date,-1);
  nextline();
  skip_lin(47-3);
}


#endif
  
static dump_rec()
{
  int16 k;
									
  CnvJamaChar(seqo_str,pos,0);                              /* convert jamascii to std-ascii */
  seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
/* lijn dumpen */
  seqo_len=0;
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
    seqo_flush();
  }
  zero(seqo_str,sizeof seqo_str);pos=0;
}
 
static copy0(ps,pd)
char *ps,*pd;
{
  int16 fuval=0;
		
  while(*ps){
    *pd++=*ps++;
    fuval++;
  }
  *pd='\0';
  return fuval;
}

static seqo_fld(stu_,fld_)
int16 stu_,fld_;
{
  if(fldlen(stu_,fld_)){
    fmt_get(stu_,fld_);
    seqo_var(fmt,s(stu_,fld_));
  }
  else seqo_str[pos++]=DELIM;
}

static seqo_var(fm_,pvar_)
char *fm_,*pvar_;
{
  int16 yy,mm,dd,len_;
  float fbd_;
  char str_[15];
 
  if(fm_[1]==0xC8 || fm_[1]==0x88){/* string */
    len_=fm_[2];
    char2str(pvar_,len_);
  }
  if(fm_[1]==0xD0 || fm_[1]==0x90){/* uint16 */
    fbd_=*(uint16 *)pvar_;
    flt2str(fbd_);
  }
  if(fm_[1]==0xD1 || fm_[1]==0x91){/* integer */
    fbd_=*(int16 *)pvar_;
    flt2str(fbd_);
  }
  if(fm_[1]==0xD3 || fm_[1]==0x93){/* long */
    fbd_=*(long *)pvar_;
    flt2str(fbd_);
  }
  if(fm_[1]==0xD4 || fm_[1]==0x94){/* float */
    fbd_=*(float *)pvar_;
    flt2str(fbd_);
  }
  if(fm_[1]==0xD5 || fm_[1]==0x95){/* double */
    fbd_=*(double *)pvar_;
    flt2str(fbd_);
  }
  if(fm_[1]==0xC0 || fm_[1]==0x80){/* date */
    if(*(uint16 *)pvar_==0) seqo_str[pos++]=DELIM;
    else{
      jddate(*(uint16 *)pvar_,&yy,&mm,&dd);
      stcli_d(str_,(long)dd,2,0);str_[2]='/';
      stcli_d(&str_[3],(long)mm,2,0);str_[5]='/';
      stcli_d(&str_[6],(long)yy,4,0);
      char2str(str_,10);
    }
  }
  if(fm_[1]==0xA8 || fm_[1]==0xE8){/* grb */
    zero(str_,sizeof str_);
    grb_deco(str_,(long *)pvar_);
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
  for(k=0;k<len_;k++) if(*(ps_+k)!=' ') break;
  if((len_-k)>0){
    copy(ps_+k,&seqo_str[pos],len_-k);while(seqo_str[pos]) pos++;
    for(k=orig_pos_;k<pos;k++){
      if(seqo_str[k]==DELIM) seqo_str[k]='.';/* delete | */
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;/* delete trailing blanks */
    pos++;
  }
  seqo_str[pos++]=DELIM;
}

static flt2str(bd_)
float bd_;
{
  int16 k,dlen_;
  char buff[15];
  double bedrag_,add_=0,dfactor_;
  long val_,value;
							
  if(bd_==0) goto endsr;
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  dfactor_=1000.;dlen_=3; if(bedrag_<-10000 || bedrag_>10000){dfactor_=100.;dlen_=2;}
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
    for(k=dlen_-1;k>=0;k--) if(buff[k]!='0') break;
    copy(&buff[0],&seqo_str[pos],k+1);pos+=k+1;
  }
  endsr:;
  seqo_str[pos++]=DELIM;
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
 
static seqo_bdr(get,len_,dec_)
float get;
int16 len_,dec_;
{
  int16 k,negat_;
  long lget_;
  double afrond_;
  char buf_[25];
									
  zero(buf_,sizeof buf_);
  if(get==0) goto endsr;
  negat_=NO; if(get<0){negat_=YES;get=-get;}
  afrond_=1.; for(k=0;k<dec_;k++) afrond_*=10.;
  lget_=(get*afrond_)+.49;
  stcli_d(&buf_[0],lget_,len_,1);
  if(dec_){
    for(k=1;k<len_-dec_;k++) buf_[k-1]=buf_[k]; buf_[len_-3]=',';
    for(k=0;k<=dec_+2;k++) if(buf_[len_-k]==' ') buf_[len_-k]='0';
  }
  if(negat_){
    for(k=0;k<len_;k++) if(buf_[k]!=' ') break;
    if(k>0) buf_[k-1]='-';
  }
  endsr:;
  seqo_txt(&buf_[0],len_,' ');
}

static seqo_txt(ps,len_,fill_kar)
int16 len_;
char *ps,fill_kar;
{
  int16 k,add_blnc=NO;
									
  for(k=0;k<len_;k++){
    if(add_blnc || *ps=='\0' || *ps>=0xFE) {add_blnc=YES;seqo_str[pos++]=fill_kar;}
    else seqo_str[pos++]=*ps;
    ps++;
  }
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

static rek_deco(s,r,sepflag)
char s[], r[], sepflag;
{
  double d;
  int16 index, i;
							
  d = r[0]+C1*(r[1]+C1*(r[2]+C1*(r[3]+C1*r[4])));
  stcdf_d(s,d,12,NO);
  if (sepflag) {
    i=2;
    for (index=14; index>2; index--) {
      if ((index==11)||(index==3)) {s[index]='-'; i--;}
      else s[index]=s[index-i];
    }
  }
}

static get_prx()
{
  int16 m,pos_;
  float kort_=0,vp_=0,k_fr_=0,acc_;
  flag aant_flag;
  uint16 pr_klt_;
 
  pr_klt_=*u(2,1);
  pos_=0;
  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd) pos_=10;
  newkort=NO;nokort=NO;calc_kort=0;calc_sem=-99;brij_tpct=0;brij_tbd=0;
  hl_korting=0;hl_semkort=0;ft_hlkorting=0;ft_semhlkorting=0;
  *u(52,1)=*i(6,9);
  vp_=0;aant_flag=NO;kort_=0;
  if(fldlen(6,PrNrs[pos_])) vp_=*f(6,PrNrs[pos_]);
	if(fldlen(6,104) && *s(6,104)=='J') nokort=YES;
  if(fasgeti(52)==0){
/*
    for(j=0;j<5;j++){
      if(fldlen(52,15+j)>0){
	if(*s(52,15+j)=='>'){
	  if(*f(58,7)<val(s(52,15+j)+1)) break;
	  vp_=*f(6,22+pos_+j);aant_flag=YES;
	}
      }
    }
*/
    if(fldlen(52,21) && *s(52,21)=='N') nokort=YES;
    if(aant_flag) {newkort=YES;goto vp_ok;}
  }
  vp_=*f(6,PrNrs[pos_+prxnr]);
  vp_ok:
  if(fldlen(9,8)==0) goto endsr;
  fasinit(9);*u(9,2)=pr_klt_;*u(9,3)=*u(6,1);
  m=get_contr(1);if(m==0) nokort=NO;// wel korting indien expliciet 
  if(m && fldlen(9,18)){
    *u(9,18)=*u(6,7);*u(9,19)=*u(6,9);m=get_contr(2);
    if(m){
      *u(9,19)=0;m=get_contr(2);
    }
	  if(m && fldlen(6,101)){ // merk/ producent 
      *u(9,18)=*u(6,101)+30000;*u(9,19)=*u(6,9);m=get_contr(2);
      if(m){
        *u(9,19)=0;m=get_contr(2);
      }
    }
    if(m){
      *u(9,18)=0;*u(9,19)=*u(6,9);m=get_contr(2);
      if(m==0 && (fldlen(6,104)==0 || *s(6,104)!='J')) nokort=NO;/* wel korting indien expleciet contract op groep */
    }
  }
  if(m==0){
    if(fldlen(9,72) && *u(9,72) && *u(9,72)<=dt_p_upd){
      if(*f(9,75)) vp_=*f(9,75);
      if(*f(9,73)) kort_=*f(9,73);
      if(*f(9,74)) k_fr_=*f(9,74);
      if(fldlen(9,81)) hl_korting=*f(9,81);
      if(fldlen(9,82)) hl_semkort=*f(9,82);
      calc_sem=*f(9,76);
    }
    else{
      if(*f(9,8)) vp_=*f(9,8);
      if(*f(9,6)) kort_=*f(9,6);
      if(*f(9,7)) k_fr_=*f(9,7);
      if(fldlen(9,20)) hl_korting=*f(9,20);
      if(fldlen(9,21)) hl_semkort=*f(9,21);
      calc_sem=*f(9,22);
    }
    if(fldlen(9,23)) brij_tpct=*f(9,23);
    if(fldlen(9,24)) brij_tbd=*f(9,24);
    newkort=YES;
  }
  endsr:;
  if(fldlen(52,23) && *s(52,23)=='J' && kort_){
    acc_=*f(6,30);
    k_fr_+=(vp_-acc_) * kort_/100.; kort_=0;
  }
#if !FLAGEPD && !FLAGVDW // EUR korting als hl-korting gebruiken
  if(k_fr_) vp_-=k_fr_;
#endif
  calc_kort=kort_;
  calc_prx=Round((double)vp_,prx_afrond);

	if (tblin.stuksaantal == 'S' && *f(6,31) > 1) {
		if (prxnr == sys3896[0] - '0')
			calc_prx = *f(6, prxnr_kassastuk + pos_); // bij kassaprijs ook de kassastuks nemen
		else
			calc_prx = Round((double)(calc_prx / *f(6,31)), prx_afrond);

		k_fr_ /= *f(6,31);
	}

	if (tblin.stuksaantal == 'P' && *f(6,83) > 1) {
		calc_prx = Round((double)(calc_prx * *f(6,83)), prx_afrond);
		k_fr_ *= *f(6,83);
	}

  if(fldlen(6,37)==0 || *f(6,37)==0){hl_korting=0;hl_semkort=0;ft_hlkorting=0;ft_semhlkorting=0;}
  else{/* omrekenen naar verpakking */
    ft_hlkorting=hl_korting* *f(6,37)/100;
    ft_semhlkorting=hl_semkort* *f(6,37)/100;
  }
#if FLAGEPD || FLAGVDW// EUR korting als hl-korting gebruiken
	ft_hlkorting+=k_fr_;
#endif
}
 
static get_contr(keynr_)
int16 keynr_;
{
  int16 k;
						
  if(faskeyi(9,keynr_,0)) return YES;
  for(k=0;k<3;k++) if(*f(9,6+k)) return NO;
  for(k=20;k<=24;k++){
    if(fldlen(9,k) && *f(9,k)) return NO;
  }
  if(fldlen(9,16) && *i(9,16)) return NO;
  return YES;
}
 
static skip_lin(line_)
int16 line_;
{
  if(line_>0){
    while(free>line_) nextline();
  }
}

static uint16 hash()
{
  char *ps;
  int16 len_;
  uint16 fuval=0;
					
	len_=sizeof tblin.code + sizeof tblin.omschr;ps=tblin.code;
  while(len_--){
    fuval=fuval*3+*(ps++);
  }
	fuval=fuval*3+tblin.stuksaantal;
  return fuval;
}

static ram2stu(lin_)
int16 lin_;
{
  copy(ram+(lin_*len_tblin),p_tblin,len_tblin);
}
							
static stu2ram(lin_)
int16 lin_;
{
  copy(p_tblin,ram+(lin_*len_tblin),len_tblin);
}

static initload()
{
  int k;

  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);
  if(fldlen(60,1)) fileopen(14);
  if(fldlen(16,1)) fileopen(13);

  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);
  sysget( 294,4,def_munt);
	sysget(1048,32,&btw_pct[0]);
  sysget(1084,4,&def_btw);
  sysget(1820,2,&sys1820);
  sysget(1918,2,&sear_stt);
	sysget(2212,4,talen);
  sysget(2727,2,&sys2727);
  sysget(3588,2,&sys3588);
  sysget(3590,2,&sys3590);
  sysget(3624,2,&sys3624);
  sysget(3720,2,&sys3720);
  sysget(3758,2,&sys3758);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
	sysget(3896,6,&sys3896[0]);
	for(k=0;k<6;k++) if(sys3896[k]=='\0') break; k--; 
	if(k>=0) prxnr_kassastuk=PrNrs[sys3896[k]-'0']; else prxnr_kassastuk=21;
  sysget(4436,1,&sys4436);
  sysget(4608,2,&sys4608);
  sysget(4731,2,&sys4731); // geen aacijns en leeggoed op lijsten

  ft_date=*u(25,2);dt_p_upd=*u(25,2);
  ram=RamBon;
  ram_size=125000;
#ifdef DOUBLE_FACT
  ram_size*=DOUBLE_FACT;
#endif
  if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;zero(ram,ram_size);

  len_tblin=sizeof tblin;max_line=ram_size/len_tblin;
  p_tblin=(char *)&tblin.rec;
  
  pu_2_1=u(2,1);
  pu_6_1=u(6,1);
  pl_80_1=l(80,1); p_data=seqo_str;
	ft_afrond=(double)(0.01);
  zero(stdkolJN,sizeof stdkolJN);zero(std_foot,sizeof std_foot);
  ld_param(); if(stdkolJN[0]=='\0') parameters();
  zero(&seldata.data_begin,sizeof seldata); seldata.dt_s_beg=*u(25,2)-730;
}

static ld_param()
{
  int16 k,z;
 
  fasclos(-2);
  if(fasopen("Offerte.jam",1)==0){
    fasinit(80);
    zero(seqo_str,sizeof seqo_str);pos=0;
    if(read_rec(0)==0){
      z=0;
      get_str(stdkolJN,z++,sizeof stdkolJN);
      for(k=0;k<4;k++){
	get_str(std_foot[k],z++,sizeof std_foot[0]);
      }
    }
    fasclos(-2);
  }
  for(k=0;k<sizeof stdkolJN;k++) if(stdkolJN[k]!='J' && stdkolJN[k]!='N') stdkolJN[k]='N';
  copy(stdkolJN,prtkolJN,sizeof prtkolJN);
}


static wr_param()
{
  int16 k;

  fasclos(-2);
  if(fasopen("Offerte.jam",2)==0){
    fasinit(80);seqo_pos=0;seqo_mode=2;pos=0;
    zero(seqo_str,sizeof seqo_str);pos=0;
    char2str(stdkolJN,sizeof stdkolJN);
    for(k=0;k<4;k++){
      char2str(std_foot[k],sizeof std_foot[0]);
    }
    dump_rec();
    fasclos(-2);
  }
}


static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
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

static cmp_str(p1,p2,len)
char *p1,*p2;
int16 len;
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
 
static chk_email()
{
  int16 z,key,k,at_fnd_,punt_fnd_;
  char kar_;
						
  if(fldlen(2,21)==0) return NO;
  copy(adrbuf,s(2,1),fldlen(2,0));
						
  at_fnd_=0; punt_fnd_=0;
  for(k=0;k<fldlen(2,21);k++){
    kar_=*(s(2,21)+k);
    if(kar_=='\0') break;
    if(kar_=='@') at_fnd_++;
    if(kar_=='.' && at_fnd_) punt_fnd_++;
  }
/*  if(at_fnd_==1 && punt_fnd_>0) return YES; */
  FOREVER{
    redo:;
    scrget(1,249); z=1;
    for(k=3;k<7;k++) scrofld(z++,2,k,-1);
    scrfld(z++,2,21);
    key=scrupd(1,0x81);
    if(key==101) return NO;
    at_fnd_=0; punt_fnd_=0;
    for(k=0;k<fldlen(2,21);k++){
      kar_=*(s(2,21)+k);
      if(kar_=='\0') break;
      if(kar_=='@') at_fnd_++;
      if(kar_=='.' && at_fnd_) punt_fnd_++;
    }
    if(at_fnd_!=1 || punt_fnd_==0) {errnum=34;goto redo;}
    if(key==108) {
      copy(s(2,1),adrbuf,fldlen(2,0));
      return YES;
    }
  }
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
  parmcall[7]=0x0C;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}


