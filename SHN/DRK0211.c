/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0211GetD() {return &zzvw;}

#define ovldat DRK0211dat
#define ovlcod DRK0211cod
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

#include "OvlShare.h"

char ovldat[] = "drk0211  00:28 22/06/10 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DOUBLE_FACT     5
#define D_LIN_SCR       15
#define DIM_LPDARECS    38
#define LEVER           0
#define BESTEL          1

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

static long *pl_80_1;
static char *rec_ele();
static float get_num();
extern uint16 datejd();
static uint16 get_date();
static uint16 GetAKFiche(arec_,lrec_);
static char *GetRefLeverancier(arec_,lrec_,dt_beg_);
static double Round(double getal, double bd_afr_);

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os9[]  = {7,0x88,9,0,0,0,0};
static char fm_os6[]  = {7,0x88,6,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us75[]   = {7,0xC8,75,0,0,0,0};
static char fm_us10[]   = {7,0xC8,10,0,0,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_aantal[]= {6,0xD4,5,0,0x60,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_of7_2[] = {6,0x94,7,2,0x70,0};
static char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static char fm_of5_2[] = {6,0x94,5,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_u_SP[]  = {11,0xC8,1,0,1,0,'S','S','P','P',0};

							
static int16 max_line,len_tblin;
static long ram_size;
static char *ram,*p_tblin;

static unsigned SpoolFileNr;
static int16 free,len_1_3mx,credt_allow;
static int16 sys3588,taaltxt,OKovl2282,OKovl2283,OKovl2284,PrxOvl2282,PrxOvl2284,OKovl33,ViaOvl33;
static int16 form_dat[8],pr_mode,prtnr,IxLin[500];
static int16 prt2pdf;
static uint16 sys3758,ft_date,dat_beg,dat_end,pda_nr,RecPrikTik,RecDistrico,sys2978,sys3652;
static uint16 lpdarecs[DIM_LPDARECS],q_levpda,filiaal,ArtRefLeverancier[50];
static char filnam[80],fmt[40],ft_nr[15],def_munt[4],*p_data,sortbuf[1000];
static char old_levnm[50],leeggcod[20],opm_foot[4][75],firma[350],CnvPdaAantal2LevAantal='J';
static char nm_fil[6],nm_loc[10][6],buf1000[1000];
static flag flag_apbr=NO,lvcd,klcd=NO,chk_btoeg=NO,sys3624,sys3720,sys3594,sear_stt;
static flag via_pda_lev;
static float ap_netlev,alg_tot,tot_goed,tot_leeg;
static flag sys3876,sys3590,exec_mode,sys4608,sys2727,sys1820,sys3592;
static char sys4436;
static double prx_afrond;
static char seqo_str[1500];
static char filnam[80],fmt[40];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;

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
 
static struct{ // ZELFDE HOUDEN IN DRK2282, DRK2283 EN DRK2284!!!!
  uint16 rec;
  float qlv;
  char  stuks_fl;
  char  code[15];
	char  ref_lev[20];
	uint16 rec11;
  char  omschr[40];
  char  valuta[4];
  float tbprx[8];/* bruto, perc1, perc2, kortfr, apnet , afh.verg, losverg.*/
  float accijns;
  float btw;
  uint16 groep;
  float q_per_bak; // indien afwijkend
  uint16 rec_leeg;
  float q_leeg;
  float bd_leeg;
  float tot_akw;
  float calc_qlv;
	char  PlMag[10];
  uint16 hash;
}tblin;

// FLAGART : uitschrijven bestelling voor AkzoNobel
// FLAGDCN : aantal met 2 decimalen 



ovlcod()
{
  int16 z,curs=1,key;
  char choice;
 
  initload();exec_mode=LEVER;
#if FLAGDCN // aantal met 2 decimalen
	fm_aantal[2]=3;fm_aantal[3]=2;fm_aantal[4]=0x60; 
#endif

  FOREVER{
	  redo:;
    scrget(2,278);z=1;fasunlck(0);
		if(OKovl33) scraddpicto(52,0,78,10,2,1,105,1,7,"^!B0211C");
		if(sys2978){
      if(RecPrikTik) scraddpicto(51,0,78,18,2,1,105,1,7,"^!B0211A");
		  else if(RecDistrico) scraddpicto(51,0,78,18,2,1,105,1,7,"^!B0211B");
		}
	  if(OKovl2283) {scraddfield(13,3,18,0);scrifld(13,VarTextFmt(79,0),"Uitschrijven excel voor opname bestelling ....................... : B");}
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
	if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key>=5050 && key<=5051) goto redo; // link help 
    if(key==101 || key==111) break;
		ViaOvl33=NO;
    switch(choice){
      case '1': exec_mode=LEVER;execute();break;
      case '2': exec_mode=BESTEL;execute(); break;
			case 'B': if(OKovl2283) ovlcall(2283,1); break;
      case 'K': if((sys4436 & 0x02) && ovltest(298)) ovlexit(298); else errnum=12; break;
			case 'P': if(OKovl33){exec_mode=LEVER; ViaOvl33=YES;execute();} else errnum=12; break;
      case 'H': if(OKovl33) ovlcall(33,2); else errnum=34; break;
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}

static execute()
{
  int16 k,key;
 
  via_pda_lev=NO;
  if(!ViaOvl33 && (sys4436 & 0x02)){
    if(ask_meth()==NO) return 0;
    if(via_pda_lev){
      if(ld_pdalev()==0){return 0;}
    }
  }
	fasunlck(-1);
  FOREVER{
    ft_init();PrxOvl2282=NO;
		if(ViaOvl33){
	    if(ovlcall(33,0)==0) break;
			AddPeppol2Doc();
		}

    if(via_pda_lev){
      if(get_pdalev()) break;
      load_pda(YES);
    }
    redo:;
    if(dsp_detail()){
			if(ViaOvl33) goto endsr;
			else break;
		}
    k=dsp_tot();
    if(k==NO) goto endsr;
    if(k>2)goto redo;
    if(k==1){
      if(exec_mode==LEVER) prt_lever(); else prt_best();
			if(prt2pdf==2) {MailDocument(0);prt2pdf=0;}
      FOREVER{
				scrget(2,28);
				key=scrupd(0xFFFF,0xF58);
				if(key==105) break;
				if(key==104){
					if(exec_mode==LEVER) prt_lever(); else prt_best();
				}
				if(key==107) goto redo;
      }
    }
    if(exec_mode==LEVER) upd_stock();
		if(ViaOvl33){
			if(credt_allow==NO) ovlcall(33,3); // peppolfactuur wegschrijven
			else ovlcall(33,4); // aanduiden dat stock verwerkt is
		}
		if(OKovl2283 && *(uint16 *)&BestelFileUsed[0][100]==2283){
			if(DisplayWarning("Mag de opname-excel geschrapt worden?",605,1)){ // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
				for(k=0;k<2;k++){
					if(BestelFileUsed[k][0] && *(uint16 *)&BestelFileUsed[k][100]==2283){
						fasopen(BestelFileUsed[k],99); // deleten 
						zero(BestelFileUsed[k],sizeof BestelFileUsed[0]); 
					}
				}
			}
		}
		if(OKovl2282 || OKovl2284){
			for(k=0;k<2;k++){
				if(BestelFileUsed[k][0] && (*(uint16 *)&BestelFileUsed[k][100]==2281 || *(uint16 *)&BestelFileUsed[k][100]==2282 || *(uint16 *)&BestelFileUsed[k][100]==2284)){
					fasopen(BestelFileUsed[k],99); // deleten 
				  zero(BestelFileUsed[k],sizeof BestelFileUsed[0]); 
				}
			}
		}

    for(k=0;k<q_levpda;k++) if(lpdarecs[k]==*u(1,1)){lpdarecs[k]=0;break;}
    endsr:;
  }
}
 
static AddPeppol2Doc(void)
{
	int16 n,j,k,ok_;
	char artnm_[50];
	float factor_,acc_factor_;


	scrget(1,7);scrupd(-3,0);

	copy(PeppolHeader.FactuurNr,ft_nr,10);
	for(n=0;n<PeppolHeader.BewCount;n++){
		if(PeppolLijn[n].ArtRec){
			*u(6,1)=PeppolLijn[n].ArtRec; fasgeti(6);
			factor_=1.; if(PeppolLijn[n].AfwijkendAantal && *f(6,31)) factor_= PeppolLijn[n].AfwijkendAantal/ *f(6,31);
//			acc_factor_=1.; if(PeppolLijn[n].AfwijkendAantal && *f(6,31)) acc_factor_= PeppolLijn[n].AfwijkendAantal/ *f(6,31); // accijns moet volgens artikel zijn
			for(j=0;j<max_line;j++){
				ram2stu(j);
				if(tblin.rec==*u(6,1) && tblin.tbprx[0]==Round((double)(PeppolLijn[n].Prijs/factor_),prx_afrond)){
					tblin.qlv+=PeppolLijn[n].Aantal*factor_; 
					if(PeppolLijn[n].Prijs<=0.0001) tblin.tbprx[0]=0.0001;  // gratis artikel, opvragen prijs misleiden
					else tblin.tbprx[0]=Round((double)(PeppolLijn[n].Prijs/factor_),prx_afrond);
					// else if(PeppolLijn[n].KortPct==100.) *f(58,73)=0.0001;
					// if(PeppolLijn[n].Accijns) *f(58,38)=Round((double)(PeppolLijn[n].Accijns/acc_factor_),(double)(0.001));
					stu2ram(j);
					break;
				}
			}
			if(j>=max_line){
				for(j=max_line-1;j>=0;j--){
					ram2stu(j);
					if(tblin.code[0] || tblin.omschr[0]) break;
				}
				j++;
				if(j>=0 && j<max_line){
					ram2stu(j);
					tblin.rec=*u(6,1); copy(s(6,2),tblin.code,fldlen(6,2)); copy(s(6,3),tblin.omschr,fldlen(6,3)); tblin.qlv=PeppolLijn[n].Aantal*factor_;
					copy(s(6,29),tblin.PlMag,fldlen(6,29));
					if(PeppolLijn[n].Prijs<=0.0001) tblin.tbprx[0]=0.0001;  // gratis artikel, opvragen prijs misleiden
					else if(PeppolLijn[n].Prijs) tblin.tbprx[0]=Round((double)(PeppolLijn[n].Prijs/factor_),prx_afrond);
//					if(PeppolLijn[n].Accijns) *f(58,38)=Round((double)(PeppolLijn[n].Accijns/acc_factor_),(double)(0.001));
					stu2ram(j); 
				}
			}
		}
		else{
			zero(artnm_,sizeof artnm_); copy0(PeppolLijn[n].Naam,artnm_,fldlen(6,3)); // artnm_[0]='+'; copy0(PeppolLijn[n].Code,&artnm_[1],fldlen(58,16)-1); 
			factor_=1.; if(PeppolLijn[n].AfwijkendAantal && *f(6,31)) factor_= PeppolLijn[n].AfwijkendAantal/ *f(6,31);
			for(j=0;j<max_line;j++){
				ram2stu(j);
				if(*u(58,14)==0 && cmpstr(artnm_,tblin.omschr,fldlen(6,3))==0){
					tblin.qlv+=PeppolLijn[n].Aantal; 
					if(PeppolLijn[n].Prijs) tblin.tbprx[0]=Round((double)(PeppolLijn[n].Prijs),prx_afrond);
//					if(PeppolLijn[n].Accijns) *f(58,38)=PeppolLijn[n].Accijns;
					stu2ram(j);break;
				}
			}
			if(j>=max_line){
				for(j=max_line-1;j>=0;j--){
					ram2stu(j);
					if(tblin.code[0] || tblin.omschr[0]) break;
				}
				j++;
				if(j>=0 && j<max_line){
					ram2stu(j);
					copy(artnm_,tblin.omschr,fldlen(6,3));
					tblin.qlv=PeppolLijn[n].Aantal;
					if(PeppolLijn[n].Prijs) tblin.tbprx[0]=Round((double)(PeppolLijn[n].Prijs),prx_afrond);
//					if(PeppolLijn[n].Accijns) *f(58,38)=PeppolLijn[n].Accijns;
					stu2ram(j); 
				}
			}
		}
	}
	endsr:;
}

static double Round(double getal, double bd_afr_)
{
 double wrk1_,wrk2_,add_,result_;
 
	add_=(double)(0.5);result_=getal;
  if(result_<0) add_=-add_;
  if(bd_afr_>0.00001){
    if(bd_afr_<=1.){
      wrk1_=(long int)result_;
      wrk2_=result_-wrk1_;
    } else{wrk1_=0.;wrk2_=result_;}
    wrk2_=(double)((int)((wrk2_/bd_afr_)+add_)) * bd_afr_;
    result_=wrk1_+wrk2_;
  }
  return (double)(result_);
}


static get_pdalev()
{
  int16 j,curs=1,key,z,start_,d_lin_scr=19;
 
  scrnum=0;start_=0;
  FOREVER{
    redo:
    scrnum=0;scrget(2,298);z=1;
    for(j=start_;j<(start_+d_lin_scr);j++){
      if(j>=q_levpda) break;
      j++; scrifld(z++,fm_ou2,&j); j--;
      fasinit(1);*u(1,1)=lpdarecs[j]; if(*u(1,1)) fasgeti(1);
      scrfld(-z,1,3);z++;
    }
    key=scrupd(curs,0x4A7);curs=1;
    if(key==101 || key==111) goto endsr;
    if(key==108 || key==18){
      j=fldcurs/2;j--;j+=start_;
      fasinit(1);*u(1,1)=lpdarecs[j]; if(*u(1,1)) fasgeti(1);
      if(*u(1,1)) return NO;
    }
    if(key==102) start_-=d_lin_scr;
    if(key==103){
      start_+=d_lin_scr;
      if(start_>(q_levpda-d_lin_scr)) start_=q_levpda-d_lin_scr;
    }
    if(start_<0) start_=0;
  }
  endsr:;
  return YES;
}
 
static ask_meth()
{
  char choice;
  int16 z,curs=1,key;
						
  scraddf(-1,0,0,0);z=1;scraddpicto(50,0,54,10,2,1,105,1,7,"^!B0297A");
  scraddf(z++,6,10,0);
  scraddf(z++,8,10,0);
  scraddf(z++,10,10,0);
  scraddf(z++,12,10,0);scraddf(z++,12,51,2);
  scraddf(z++,23,1,8);
  z=1;
  redo:;
  scrifld(z++,fm_os79,"Kies de methode van ingave :");
  scrifld(z++,fm_os79,"    Manuele ingave ................... : 1");
  scrifld(z++,fm_os79,"    Lijst leveranciers van PDA-opnames : 2");
  scrifld(z++,fm_os79,"                               U kiest ? ");
  scrifld(z++,fm_menu,&choice);
  scrifld(z++,fm_os9," F1 stop");
  key=scrupd(curs,0x01);
	if ((key/0x100)==1) key=(key&0xFF)+5000;
	if(key==5050 || key==5051) goto redo; // link help 
  if(key==101) return NO;
  switch(choice){
    case '1': via_pda_lev=NO;break;
    case '2': via_pda_lev=YES; break;
    default : errnum=34; break;
  }
  if(errnum) goto redo;
  return YES;
}

static ld_pdalev()
{
  int16 z,key,k,len_,mode_,amode_;
  uint16 dt_;
 

  if(dat_end==0) dat_end=*u(25,2);
  if(dat_beg==0) dat_beg=dat_end;
  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,12,10,0);scraddf(z++,12,32,2);
    scraddf(z++,12,41,0);scraddf(z++,12,48,2);
    scraddf(z++,14,10,0);scraddf(z++,14,32,2);
    scraddf(z++,23,1,8);scraddf(z++,23,11,8);
    fasinit(1);
    FOREVER{
      z=1;
			DisplayMenuTitel(4,"Opzoeken lijst leveranciers van PDA-bestelling",0xA);
      scrifld(z++,fm_os79,"Periode PDA-opnames :");
      scrifld(z++,fm_udat,&dat_beg);
      scrifld(z++,fm_os9,"t.e.m.");
      scrifld(z++,fm_udat,&dat_end);
      scrifld(z++,fm_os79,"Selectie 1 PDA .... :");
      scrifld(z++,fm_uu2,&pda_nr);
      scrifld(z++,fm_os9," F1 stop");scrifld(z++,fm_os13," F8 zoek op");
      key=scrupd(2,0x81);
      if(key==101) return 0;
      if(key==108) break;
    }
    zero((char *)&lpdarecs[0],sizeof lpdarecs); mode_=1;
    mk_pdaname(4410,"moblogBS.dat");
    fasclos(-2);if(fasopen(filnam,1)!=0){errnum=1;goto redo;}
    scrget(1,7);scrupd(-3,0);
    fasinit(80);mode_=0;
    q_levpda=0;
									
    FOREVER{
      next:;
      if(read_rec(mode_)) break; mode_=1;
      if(get_num(2)==0) goto next;/* geen aantal */
      len_=ele_len(2); if(len_>fldlen(6,2)) len_=fldlen(6,2);
      if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;/* begin eruit */
      fasinit(6);copy(rec_ele(2),s(6,2),len_);if(faskeyi(6,1,0)) goto next;
      dt_=get_date(0);
      if(dat_beg && dt_<dat_beg) goto next;
      if(dat_end && dt_>dat_end) goto next;
      for(k=0;k<DIM_LPDARECS;k++) if(lpdarecs[k]==*u(6,7) || lpdarecs[k]==0) break;
      if(k<DIM_LPDARECS) lpdarecs[k]=*u(6,7);
      if(fldlen(11,0)){
				fasinit(11);*u(11,3)=*u(6,1);amode_=1;
				FOREVER{
					if(faskeyi(11,2,amode_)) break; amode_=2;
					if(*u(11,3)!=*u(6,1)) break;
					for(k=0;k<DIM_LPDARECS;k++) if(lpdarecs[k]==*u(11,2) || lpdarecs[k]==0) break;
					if(k<DIM_LPDARECS) lpdarecs[k]=*u(11,2);
				}
      }
    }
    fasclos(-2);
    for(q_levpda=0;q_levpda<DIM_LPDARECS;q_levpda++) if(lpdarecs[q_levpda]==0) break;
    if(q_levpda) break; else errnum=14;
  }
  return (int16)q_levpda;
}

static dsp_detail()
{
  int16 curs,j,key,k,start_=0,z,z_base,q_per_line,nstart_,auto_enter,err_pos_,curspos_=1;
 
  curs=1;q_per_line=7;err_pos_=0;
  FOREVER{
redo:
#if FLAGGDN
    scrnum=0;scrget(2,514);z=1;
#else
    scrnum=0;scrget(2,14);z=1;
#endif
    if(exec_mode==0) scrifld(z++,fm_os10,"leveringen");
    else scrifld(z++,fm_os10,"bestellingen");
	  scraddpicto(1,0,76,22,4,2,127,0,4,"Voeg artikels toe");
    j=start_+1; scrifld(z++,fm_ou3,&j);
    j=start_+D_LIN_SCR; scrifld(z++,fm_ou3,&j);
    scrfld(z++,1,3);scraddpicto(9,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_udat,&ft_date);scrifld(z++,fm_us10,ft_nr);
    scrifld(z++,fm_of7_2,&tot_goed);
    if(exec_mode==0){
      if(fldlen(66,1)){scrifld(-z,fm_uu2,&filiaal); z++; }
      else scrifld(z++,fm_ou2,&filiaal);
      scrifld(z++,fm_os6,nm_fil);
    } else {filiaal=0;z+=2;}
    scrifld(z++,fm_of7_2,&tot_leeg);
    z_base=z;auto_enter=NO;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      ram2stu(j);
      dspdetln(z++,j,fm_aantal,&tblin.qlv); if(tblin.q_per_bak) scrchat(z-1,0x0A); // afwijkende verpakking bij leverancier
#if FLAGGDN
			z++;
#else
      dspdetln(z++,j,fm_u_SP,&tblin.stuks_fl);
#endif
      if(sys4608 & 1){
				auto_enter=YES;if(tblin.code[0]!='\0' && z!=err_pos_) auto_enter=NO;
      }
#if FLAGGDN
			z++;
#else
      fmt_get(6,2); if(sys3594==1) fmt[1]&=0xBF; // output maken
      if(auto_enter){dspdetln(-z,j,fmt,tblin.code);z++;}
      else dspdetln(z++,j,fmt,tblin.code);
			if(sys2978 && (*u(1,1)==RecPrikTik || *u(1,1)==RecDistrico) && tblin.rec && tblin.ref_lev[0]=='\0') scrchat(z-1,0xB);  // koppeling P&T : code leverancier moet ingevuld zijn
#endif
      if(sys4608 & 1){
				auto_enter=YES;if(tblin.omschr[0]!='\0' && z!=err_pos_) auto_enter=NO;
      }
      fmt_get(6,3); if(fmt[2]>30) fmt[2]=30; // anders schermprobleem
      if(auto_enter){dspdetln(-z,j,fmt,tblin.omschr);z++;}
      else dspdetln(z++,j,fmt,tblin.omschr);
			scraddpicto(10+j-start_,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
      fmt_get(6,12);dspdetln(z++,j,fmt,&tblin.tbprx[0]);
      fmt_get(6,18);dspdetln(z++,j,fmt,&tblin.tbprx[5]);
      dspdetln(z++,j,fm_of6_2,&tblin.tot_akw);
    }
    key=scrupd(curs,0x7FF);curs=z_base; curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    auto_enter=NO;nstart_=start_;err_pos_=0;
    if(key==106){
      if(scr_ok("Wenst U echt de gegevens te annuleren ???")){
				ft_init();curs=1; goto redo;
      }
    }
    if(key==101){
      for(k=0;k<max_line;k++){ram2stu(k);if(tblin.qlv) break;}
      if(k<max_line){
				if(scr_ok("Wenst U echt de gegevens te annuleren en te stoppen ???")) return YES;
      } else return YES;
    }
    if(key==5009){
      if(search(1,98)) {curs=4;goto redo;}
      copy(s(1,3),old_levnm,fldlen(1,3));
    }
		if(key>=5010 && key<5010+D_LIN_SCR){
			k=key-5010+start_;
			ram2stu(k);
			fasinit(6);
			if(sys3594==0 && tblin.code[0]) {*s(6,3)='.';copy(tblin.code,s(6,3)+1,fldlen(6,2));}
			else {copy(tblin.omschr,s(6,3),fldlen(6,3));}
			if(search(6,98)){
				curs=z_base+ (k-start_)*q_per_line +2; if(tblin.code[0]=='\0') curs++;
				err_pos_=curs;errnum=39;goto redo;
			}
			copy(s(6,2),tblin.code,fldlen(6,2));
			copy(s(6,3),tblin.omschr,fldlen(6,3));
			tblin.rec=*u(6,1);
			copy(s(6,29),tblin.PlMag,fldlen(6,29));
			FillDetailLijn();
			stu2ram(k);
		}
    if(filiaal==99 || filiaal==0) copy("DEPOT",nm_fil,6);
    else if(filiaal<1 || filiaal>10 || fldlen(66,11+(filiaal-1)*15)==0) {
      zero(nm_fil,sizeof nm_fil); curs=8;errnum=34;goto redo;
    }
    else copy(nm_loc[filiaal-1],nm_fil,6);

    if(key==18){
      if(curspos_<z_base){
				curs=curspos_+1;goto redo;
      }
      auto_enter=YES;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      k=(curspos_-z_base)%q_per_line;
      ram2stu(j);
      if(k==2 && tblin.code[0]=='\0') {curs=curspos_+1;goto redo;}
      if(k==3 && tblin.omschr[0]=='\0') {curs=curspos_+1;goto redo;}
    }
    if(*s(1,3)=='\0' || cmp_str(s(1,3),old_levnm,fldlen(1,3))){
      if(search(1,0)) {curs=4;goto redo;}
      copy(s(1,3),old_levnm,fldlen(1,3));
    }
    if(key==111){
      if(load_pda(NO)<=0) {errnum=14; goto redo;}
      key=107;
    }

    if(key==105){
      k=(curspos_-z_base)/q_per_line;
      if(curspos_<z_base || k<0){errnum=34; curs=curspos_;goto redo;}
      else {
				ram2stu(k+start_);
				zero((char *)p_tblin,len_tblin);
				stu2ram(k+start_);
      }
			curs=z_base+ k*q_per_line; goto redo;
    }

    for(k=start_;k<(start_+D_LIN_SCR);k++){
      ram2stu(k);
      if(((sys3594==0 && tblin.code[0]) || tblin.omschr[0]) && tblin.hash!=hash()){
				fasinit(6);
				if(sys3594==0 && tblin.code[0]) {*s(6,3)='.';copy(tblin.code,s(6,3)+1,fldlen(6,2));}
				else {copy(tblin.omschr,s(6,3),fldlen(6,3));}
				if(ARTsearch(6,0)){
					curs=z_base+ (k-start_)*q_per_line +2; if(tblin.code[0]=='\0') curs++;
					err_pos_=curs;errnum=39;goto redo;
				}
				copy(s(6,2),tblin.code,fldlen(6,2));
				copy(s(6,3),tblin.omschr,fldlen(6,3));
				tblin.rec=*u(6,1);
				copy(s(6,29),tblin.PlMag,fldlen(6,29));
				FillDetailLijn();
	    }
      else if(tblin.code[0]=='\0' && tblin.omschr[0]=='\0'){
				zero((char *)&tblin,len_tblin);
      }
      stu2ram(k);
    }
		if(key==5001){
			DisplayExtraFuncties();
		  PrxOvl2282=NO;	if(OKovl2282 && BestelFileUsed[0][0] && *(uint16 *)&BestelFileUsed[0][100]==2282) PrxOvl2282=YES;
			PrxOvl2284=NO;	if(OKovl2284 && BestelFileUsed[0][0] && *(uint16 *)&BestelFileUsed[0][100]==2284) PrxOvl2284=YES;
		}
    calc(0,NO);
    if(key==109) {if(exec_mode==LEVER) prt_lever(); else prt_best();}
    if(key==108){
			for(k=start_;k<max_line;k++){
				ram2stu(k);
				if(((sys3594==0 && tblin.code[0]) || tblin.omschr[0]) && tblin.hash!=hash()){
					fasinit(6);
					if(sys3594==0 && tblin.code[0]) {*s(6,3)='.';copy(tblin.code,s(6,3)+1,fldlen(6,2));}
					else {copy(tblin.omschr,s(6,3),fldlen(6,3));}
					if(ARTsearch(6,0)){
						start_=k;
						curs=z_base+ (k-start_)*q_per_line +2; if(tblin.code[0]=='\0') curs++;
						err_pos_=curs;errnum=39;goto redo;
					}
					copy(s(6,2),tblin.code,fldlen(6,2));
					copy(s(6,3),tblin.omschr,fldlen(6,3));
					tblin.rec=*u(6,1);
					copy(s(6,29),tblin.PlMag,fldlen(6,29));
					FillDetailLijn();
				}
				else if(tblin.code[0]=='\0' && tblin.omschr[0]=='\0'){
					zero((char *)&tblin,len_tblin);
				}
				stu2ram(k);
			}			
			
			
			
			break;
		}
    if(key==110){
      k=(curspos_-z_base)/q_per_line;
      if(k<0) errnum=34;
      else{
				ram2stu(k+start_);
				if(tblin.omschr[0]=='\0') errnum=34;
				else {dsp_akfich(start_+k);calc(0,NO);}
      }
    }
    if(key==104){
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
      for(k=0;k<D_LIN_SCR;k++){ram2stu(start_+k);if(tblin.qlv==0) break;}
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

static DisplayExtraFuncties()
{
	int z,k,key,used_=0,vt_,hz_;
	char choice='\0',menu_punten[10],dsp_lijn[80];

	FOREVER{
redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,4,25,3);
    scraddf(z++,10, 5,0);
    scraddf(z++,23,1,8);scraddf(z++,23,11,8);

    z=1;used_=0;zero(dsp_lijn,sizeof dsp_lijn);zero(menu_punten,sizeof menu_punten);
    scrifld(z++,VarTextFmt(29,0),"Extra functes bij ingeven bon");
    scrifld(z++,fm_os79,"Laad artikels van :");
    scrifld(z++,VarTextFmt(9,0)," F1 stop ");// scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
 
		z=30;hz_=34;vt_=10;
		AddTextKey(z++,hz_,vt_,20,2,10011,"uitgebreide selectie",0x007FFF);hz_+=20;if(hz_>=74){hz_=34;vt_+=2;}
		AddTextKey(z++,hz_,vt_,20,2,10012,"opnames van PDA",0x007FFF);hz_+=20;if(hz_>=74){hz_=34;vt_+=2;}
		if(OKovl2282 && exec_mode==LEVER){AddTextKey(z++,hz_,vt_,20,2,10015,"verzendnota\nPrik Tik",0x007FFF);hz_+=20;if(hz_>=74){hz_=34;vt_+=2;}}
		if(OKovl2284){AddTextKey(z++,hz_,vt_,20,2,10017,"verzendnota\nDistrico",0x007FFF);hz_+=20;if(hz_>=74){hz_=34;vt_+=2;}}
    if(OKovl2283){
  		AddTextKey(z++,hz_,vt_,20,2,10016,"XLS-bestelling",0x007FFF);hz_+=20;if(hz_>=75){hz_=34;vt_+=2;}
		}
		key=scrupd(-1,0x7FF);
		if((key/0x10000)>0) key/=0x10000;
		switch(key){
		  case 101 : return 0; break;
			case 10011 : load_art(); return 1; break;
			case 10012 : if(load_pda(NO)<=0) {errnum=14; goto redo;}  else return 1; break;
			case 10015 : ovlcall(2282,1); return 1; break;
			case 10016 : ovlcall(2283,0); return 1; break;
			case 10017 : ovlcall(2284,1); return 1; break;
			default : break;
		}
  }
}

static load_art()
{
  int16 mode_,nr_,fkey;
 
  seldata.prx_klt=0;
  seldata.selp_use=NO;
  if(ovlcall(2215,2)) goto endsr;

  scrget(1,7);scrupd(-3,0);
  fasinit(6);mode_=1;nr_=0; fkey=2;
  FOREVER{
    redo:;
    if(faskeyi(6,fkey,mode_)) break; mode_=2;
    if(DirCall_DRK2215_SelectArtikel()==NO) goto redo;
    for(nr_;nr_<max_line;nr_++){
			ram2stu(nr_); if(tblin.omschr[0]=='\0') break;
		}
		if(nr_>=max_line) break;
		copy(s(6,1),buf1000,fldlen(6,0));
		copy(s(6,2),tblin.code,fldlen(6,2));
		copy(s(6,3),tblin.omschr,fldlen(6,3));
		tblin.rec=*u(6,1);
		copy(s(6,29),tblin.PlMag,fldlen(6,29));
		FillDetailLijn();
    copy(buf1000,s(6,1),fldlen(6,0));
		stu2ram(nr_);
  }
  endsr:;
}


static FillDetailLijn() // artikel en tblin moeten klaarstaan
{
	int16 j,fl_ak_fiche_,pr_offset_;
	uint16 pr_date_;
	   
	tblin.groep=*i(6,9); tblin.q_per_bak=0;
	pr_date_=*u(6,11);pr_offset_=0; if(fldlen(6,105) && *u(6,105) && *u(6,105)<=ft_date){pr_date_=*u(6,105); pr_offset_=94;}
	
	fl_ak_fiche_=NO;
	if(*i(6,9)!=99 && fldlen(11,2)){ 
		if(GetAKFiche(*u(6,1),*u(1,1))){
			if(*s(11,5)) copy(s(11,5),tblin.ref_lev,fldlen(11,5));
		  if(fldlen(11,68) && *f(11,68)>0 && *f(11,68)!=*f(6,31)) tblin.q_per_bak=*f(11,68);// afwijkende verpakking 
		  tblin.rec11=*u(11,1);	
			fl_ak_fiche_=YES;
		} else copy(s(6,8),tblin.ref_lev,fldlen(6,8));
	}
	if(fl_ak_fiche_){ // controle op lege of oude fiche (dan prijs van artikel nemen)
		if((*f(11,6)==0 && *f(11,60)==0) || // bij lege fiche de prijs van artikelfiche nemen
			(*u(1,1)==*u(6,7) && *u(11,8)<pr_date_ && *f(6,12+pr_offset_))) fl_ak_fiche_=NO;// als prijs van hoofdlev. OUDER is dan op artikelfiche
	}
	if(sys3592==0 && fl_ak_fiche_){
  	if((PrxOvl2282==NO  && PrxOvl2284==NO) || tblin.tbprx[0]==0) tblin.tbprx[0]=*f(11,6);
	  tblin.tbprx[5]=*f(11,60);
		tblin.tbprx[1]=0;
	  for(j=0;j<5;j++){
			if(*f(11,10+j*10)==0) continue;
			if(*s(11,11+j*10)=='%' && *s(11,14+j*10)=='F'){
				if(tblin.tbprx[1]==0 || fldlen(6,15)==0) tblin.tbprx[1]+=*f(11,10+j*10); 
				else if(tblin.tbprx[2]==0) tblin.tbprx[2]=*f(11,10+j*10); 
				else tblin.tbprx[3]=*f(11,10+j*10);
			}
			if(*s(11,11+j*10)=='E' && *s(11,14+j*10)=='F') tblin.tbprx[4]=*f(11,10+j*10);
		}
		if(sys3652){// handlingkost invullen
			if(fldlen(6,19+pr_offset_)) tblin.tbprx[6]=*f(6,19+pr_offset_);
		}
	}
	else{
  	if(fldlen(6,12) && tblin.tbprx[0]==0) tblin.tbprx[0]=*f(6,12+pr_offset_);
  	if(fldlen(6,13)) copy(s(6,13+pr_offset_),tblin.valuta,3);
	  for(j=0;j<7;j++){
		  if(fldlen(6,14+pr_offset_+j)) tblin.tbprx[1+j]=*f(6,14+pr_offset_+j);
		}
	}
	if(fldlen(6,30)){
		if((PrxOvl2284==NO && PrxOvl2284==NO) || tblin.accijns==0) tblin.accijns=*f(6,30);
	}
	tblin.btw=*f(6,28);
	j=41; if(tblin.stuks_fl=='S') j=44;
	if(fldlen(6,j)){
		copy(s(6,j),leeggcod,fldlen(6,j));
		tblin.q_leeg=*f(6,42);
		fasinit(6);copy(leeggcod,s(6,2),fldlen(6,j));
		if(leeggcod[0]){
			if(search(6,2)==0){
				tblin.rec_leeg=*u(6,1);
				tblin.bd_leeg=*f(6,18);
			}
		}
	}
	tblin.hash=hash();
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
  int16 z,k,best_sent_=NO;
	long key;
					

  FOREVER{
    scrnum=0; scrget(2,245);z=1;
		if(exec_mode==BESTEL){
			k=74;
			if(sys2978){
				if(RecPrikTik) {scraddpicto(3,0,k,20,4,2,581,0,0,"Maak online-bestelling");k-=4;} 	
				if(RecDistrico) {scraddpicto(5,0,k,20,4,2,572,0,0,"Maak online-bestelling Districo");k-=4;}  	//572
			}
			scraddpicto(2,0,72,22,4,2,569,0,0,"Mail"); 
		}

		scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
		
    scrfld(z++,25,1);
    scrofld(z++,1,3,-1);
    scrifld(z++,fm_os10,ft_nr);
    scrifld(z++,fm_odat,&ft_date);
    scrifld(z++,fm_of7_2,&tot_goed);
    scrifld(z++,fm_of7_2,&tot_leeg);
    for(k=0;k<4;k++)scrifld(z++,fm_us75,opm_foot[k]);
#if FLAGART
		if(exec_mode==BESTEL && best_sent_==NO) AddTextKey(z++,58,5,20,3,10001,"Schrijf uit voor\nAkzoNobel",0x0000FF);
#endif
    key=scrupd(1,0x782);
		if((key/0x10000)>0) key/=0x10000;
		else if ((key/0x100)==1) key=(key&0xFF)+5000;
	  prt2pdf=NO;
  	if ((key/0x100)==1) key=(key&0xFF)+5000;
		switch(key){
			case 5001 : prt2pdf=YES; key=108; break; // pdf
			case 5002 : prt2pdf=2;key=108; break; // mailen
	    case 5003 : MakePnTOrderFile(); break; // Prik&Tik file
	    case 5005 : MakeDistricoOrderFile(); break; // Districo file
			default : break;
		}
#if FLAGART
		if(key==10001) {
			if(DisplayWarning("Wenst U echt de bestelling door te sturen naar AkzoNobel?",605,1)){
  			if(Export2AkzoNobel()) best_sent_=YES;
			}
		}
#endif
    if(key==102)return 3;
    if(key==108) return YES;
    if(key==110) return 2;
  }
  return YES;
}

static MakeDistricoOrderFile(void)
{
  int16 k,j,yy,mm,dd,cnt_;
	char buf_[100],ref_[20],FileName[100],*ps_;

	cnt_=0;
	for(k=0;k<max_line;k++){
		ram2stu(k);
		if(tblin.qlv==0 || tblin.rec==0) continue;
		if(tblin.ref_lev[0]) ps_=tblin.ref_lev; else ps_=GetRefLeverancier(tblin.rec,RecDistrico,ft_date);
		if(*ps_=='\0') cnt_++;
	}
	if(cnt_){
		zero(buf_,sizeof buf_);
		sprintf_s(buf_,100," %d artikel(s) zonder code Districo! Toch doorgaan?",cnt_);
	  if(DisplayWarning(buf_,61,1)==NO) goto endsr; // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop  
	}
	scrget(1,7);scrupd(-3,0);
	zero(buf_,sizeof buf_);
  jddate(ft_date,&yy,&mm,&dd);
  stcli_d(&buf_[0],(long)dd,2,0);buf_[2]='-';
  stcli_d(&buf_[3],(long)mm,2,0);buf_[5]='-';
  stcli_d(&buf_[6],(long)yy,4,0);

	zero(FileName,sizeof FileName);
//	k=copy0("..\\Spool\\Temp\\Bestelling_",FileName,30);
  k=copy0("Bestelling_",FileName,30);
	k+=copy0(buf_,&FileName[k],10); FileName[k++]='_';
	stcli_d(&FileName[k],(long)(*u(8,2)),5,0);k+=5;
 	copy0(".CSV",&FileName[k],4);
	fasclos(-2);
  errnum=fasopen(FileName,12);if(errnum) goto endsr;

  scrget(1,6);scrupd(-3,0);
	fasinit(80);seqo_pos=0;seqo_mode=2;pos=0;

	for(k=0;k<max_line;k++){
		ram2stu(k);
		if(tblin.qlv==0 || tblin.rec==0) continue;
		if(tblin.ref_lev[0]) ps_=tblin.ref_lev; else ps_=GetRefLeverancier(tblin.rec,RecDistrico,ft_date);
		zero(ref_,sizeof ref_);copy0(ps_,ref_,15);
		if(ref_[0]=='\0') copy("?????",ref_,5);
		for(j=0;j<15;j++) if(ref_[j]==',') ref_[j]='.';
		for(j=0;j<sizeof tblin.omschr;j++) if(tblin.omschr[j]==',') tblin.omschr[j]='.';
		zero(buf_,sizeof buf_);sprintf_s(buf_,100,"%s,%d,%s",ref_,(int)(tblin.calc_qlv),tblin.omschr);
		pos+=copy0(buf_,&seqo_str[pos],100);add_eor();dmp2file();
	}
	fasclos(-2);
	DisplayWarning("De bestelling werd geplaatst in Documenten\\Jamadata\\Diversen",605,0); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
  endsr:;
}


static MakePnTOrderFile(void)
{
  int16 k,j,yy,mm,dd;
	uint16 rec_levPnT;
	char datebuf_[15],buf_[20],FileName[100],*pean_,*ps_;

  
	scrget(1,7);scrupd(-3,0);
  sysget(2942,2,(char *)&rec_levPnT);
	zero(datebuf_,sizeof datebuf_);
  jddate(ft_date,&yy,&mm,&dd);
  stcli_d(&datebuf_[0],(long)dd,2,0);datebuf_[2]='-';
  stcli_d(&datebuf_[3],(long)mm,2,0);datebuf_[5]='-';
  stcli_d(&datebuf_[6],(long)yy,4,0);

	zero(FileName,sizeof FileName);
//	k=copy0("..\\Spool\\Temp\\Bestelling_",FileName,30);
  k=copy0("Bestelling_",FileName,30);
	k+=copy0(datebuf_,&FileName[k],10);
	if(ft_nr[0]){
  	FileName[k++]='_';k+=copy0(ft_nr,&FileName[k],10);
	}
 	copy0(".XML",&FileName[k],4);
	fasclos(-2);
  errnum=fasopen(FileName,12);if(errnum) goto endsr;
	datebuf_[2]='/';datebuf_[5]='/';

  scrget(1,6);scrupd(-3,0);
	fasinit(80);seqo_pos=0;seqo_mode=2;pos=0;
  pos+=copy0("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>",&seqo_str[pos],100);add_eor();dmp2file();

	pos+=copy0("<Order>",&seqo_str[pos],10);add_eor();
		pos+=copy0("<Info>",&seqo_str[pos],10);add_eor();
//			dmpxmlstr("ID","",2);
			dmpxmlstr("Name",&firma[0],30);
  		dmpxmlstr("Street",&firma[31],25);
			dmpxmlstr("Zip",&firma[57],6);
			dmpxmlstr("City",&firma[65],20);
			dmpxmlstr("VAT",&firma[86],15);
			dmpxmlstr("Date",datebuf_,10);
		pos+=copy0("</Info>",&seqo_str[pos],10);add_eor();dmp2file(); // einde info
	  pos+=copy0("<Data>",&seqo_str[pos],10);add_eor();
		for(k=0;k<max_line;k++){
			ram2stu(k);
			if(tblin.qlv==0 || tblin.rec==0) continue;
			fasinit(6);*u(6,1)=tblin.rec; if(*u(6,1)) fasgeti(6);
			pos+=copy0("<Art>",&seqo_str[pos],10);add_eor();
			*f(58,31)=tblin.qlv; // gebruik stu 58 om aantal uit te schrijven
				j=Fld2String(58,31,buf_,sizeof buf_);dmpxmlstr("Quantity",buf_,j);
				if(tblin.stuks_fl=='P') dmpxmlstr("Type","P",1); else dmpxmlstr("Type","E",1);
				if(tblin.ref_lev[0]) ps_=tblin.ref_lev; else ps_=GetRefLeverancier(tblin.rec,RecPrikTik/* *u(1,1)*/,ft_date);
				for(j=0;j<15;j++) if(*(ps_+j)=='-') {*(ps_+j)='\0'; break;} // om -6 etc achter code weg te doen
				dmpxmlstr("ID",ps_,15);
				dmpxmlstr("Name",tblin.omschr,sizeof tblin.omschr);
				dmpxmlstr("OwnID",tblin.code,sizeof tblin.code);
				pean_=s(6,70); if(*s(6,71)) pean_=s(6,71); 
        dmpxmlstr("EAN",pean_,fldlen(6,70));
			pos+=copy0("</Art>",&seqo_str[pos],10);add_eor();dmp2file(); // Art
		}
	  pos+=copy0("</Data>",&seqo_str[pos],10);add_eor();// Data
	pos+=copy0("</Order>",&seqo_str[pos],10);add_eor(); // Order
	dmp2file();

	fasclos(-2);
	DisplayWarning("De bestelling werd geplaatst in MijnDocumenten\\Jamadata\\Diversen",605,0); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
  endsr:;
}



#if FLAGART
static Export2AkzoNobel(void)
{
  int16 k,j,act_jj_,act_mm_,act_dd_,act_uur_,act_min_,act_sec_;
  char filname_[50];	
									
	fasclos(-2); fasunlck(-2);
	zero(filname_,sizeof filname_);k=copy0("..\\Share\\AkzoNobel\\ART",filname_,25);
	GetCurrentDateTime(&act_jj_,&act_mm_,&act_dd_,&act_uur_,&act_min_,&act_sec_);
	stcli_d(&filname_[k],(long)act_mm_,2,0);k+=2;
	stcli_d(&filname_[k],(long)act_dd_,2,0);k+=2;
	stcli_d(&filname_[k],(long)act_uur_,2,0);k+=2;
	stcli_d(&filname_[k],(long)act_min_,2,0);k+=2;
	k+=copy0(".CSV",&filname_[k],4);
  if(errnum=fasopen(filname_,2)) return NO;
	fasinit(80);seqo_pos=0;seqo_mode=2;
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(tblin.omschr[0]){
      zeros(seqo_str,sizeof seqo_str);pos=0;
      fasinit(6);*u(6,1)=tblin.rec;fasgeti(6);
			flt2str(tblin.qlv);seqo_str[pos++]='\x09';
			char2str(s(6,70),fldlen(6,70));
			char2str(tblin.omschr,sizeof tblin.omschr);
      seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
      seqo_len=0;
      for(j=0;j<pos;j+=280){
        if((j+280)>pos) seqo_len=pos-j;
        else seqo_len=280;
        copy(&seqo_str[j],s(80,1)+4,seqo_len);
			  if(seqo_len){
          fasseqo(80,seqo_mode,seqo_len+4);
          seqo_pos+=seqo_len;
          *l(80,1)=seqo_pos;
          seqo_len=0;
        }
      }
    }
  }
	fasclos(-2);
	return YES;
}
#endif

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
  seqo_str[pos++]='\x09';
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

static ft_init()
{
  int16 k;
 
  fasinit(1);fasinit(6);copy(s(1,3),old_levnm,fldlen(1,3));
  zeroL(ram,ram_size);
  zero((char *)p_tblin,len_tblin);
  for(k=0;k<max_line;k++) stu2ram(k);
  zero(ft_nr,sizeof ft_nr);alg_tot=0;tot_goed=0;tot_leeg=0;
  zero(opm_foot[0],sizeof opm_foot);
	if(OKovl2282 || OKovl2283 || OKovl2284)	zero(BestelFileUsed,sizeof BestelFileUsed); 
}
 
static load_pda(auto_mode_)
int16 auto_mode_;
{
  int16 key,k,len_,mode_,loaded_=0,do_sel_lev_=YES;
  uint16 dt_;

  if(auto_mode_) goto load_BS;
  if(dat_end==0) dat_end=*u(25,2);
  if(dat_beg==0) dat_beg=dat_end;
  FOREVER{
    scrget(2,273);
    scrofld(1,1,3,-1);
    scrifld(2,fm_udat,&dat_beg); scrifld(3,fm_udat,&dat_end);
    scrifld(4,fm_uu2,&pda_nr);
		if(fldlen(11,68)) scrifld(5,fm_u_JN,&CnvPdaAantal2LevAantal);
    key=scrupd(2,0x181);
    do_sel_lev_=YES;
    if(key==101) return 0;
    if(key==109) do_sel_lev_=NO;
    if(key==108 || key==109) break;
  }
  load_BS:;
  mk_pdaname(4410,"moblogBS.dat");
  fasclos(-2);if(fasopen(filnam,1)!=0) return NO;

  scrget(1,7);scrupd(-3,0);
  fasinit(80);mode_=0;loaded_=0;
 
  FOREVER{
    next:;
    if(read_rec(mode_)) break; mode_=1;
    if(get_num(2)==0) goto next;/* geen aantal */
    len_=ele_len(2); if(len_>fldlen(6,2)) len_=fldlen(6,2);
    if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;/* begin eruit */
    fasinit(6);copy(rec_ele(2),s(6,2),len_);faskeyi(6,1,0);
    if(do_sel_lev_){
      if(*u(6,7)!=*u(1,1)){
				if(fldlen(11,0)){
					fasinit(11);*u(11,2)=*u(1,1);*u(11,3)=*u(6,1);
					if(faskeyi(11,1,1)){
						goto next;
					}
					if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)){
						goto next;
					}
				}
				else goto next;
      }
    }
    dt_=get_date(0);
    if(dat_beg && dt_<dat_beg) goto next;
    if(dat_end && dt_>dat_end) goto next;
    for(k=0;k<max_line;k++){
      ram2stu(k);
      if(tblin.code[0]=='\0' && tblin.omschr[0]=='\0') break;
    }
    if(k>=max_line-2) return NO;
    copy(s(6,2),tblin.code,fldlen(6,2));
    copy(s(6,3),tblin.omschr,fldlen(6,3));
		tblin.rec=*u(6,1);
		copy(s(6,29),tblin.PlMag,fldlen(6,29));
    tblin.qlv=get_num(3);
    if(*rec_ele(4)=='J') tblin.stuks_fl='S';
    else if(*rec_ele(4)=='P') tblin.stuks_fl='P';
		FillDetailLijn();
		if(CnvPdaAantal2LevAantal=='J' && fldlen(11,68) && tblin.rec11 && tblin.stuks_fl!='S' && tblin.stuks_fl!='P'){
			fasinit(6);*u(6,1)=tblin.rec; fasgeti(6); if(*f(6,31)==0) *f(6,31)=1;
			fasinit(11);*u(11,1)=tblin.rec11;fasgeti(11);
			if(*f(11,68)>0 && *f(6,31)>0 && *f(6,31)!=*f(11,68)){
				tblin.qlv*= *f(6,31)/ *f(11,68);// aantal in leveranciers	verpakking zetten  
			}
		}
    stu2ram(k);
    loaded_++;
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

static char *GetRefLeverancier(arec_,lrec_,dt_beg_)
uint16 arec_,lrec_,dt_beg_;
{
	zero(ArtRefLeverancier,sizeof ArtRefLeverancier);if(arec_==0) goto endsr;
	fasinit(6);*u(6,1)=arec_;fasgeti(6);
  if(GetAKFiche(arec_,lrec_)) copy(s(11,5),ArtRefLeverancier,fldlen(11,5));
	if(ArtRefLeverancier=='\0' && fldlen(6,8) && *u(6,7)==lrec_) copy(s(6,8),ArtRefLeverancier,fldlen(6,8));
	endsr:;
	return (char *)ArtRefLeverancier;
}

static dmpxmlstr(xname_,ps_,maxlen_)
char *xname_,*ps_;
int16 maxlen_;
{
  int16 k,len_,slen_,nm_beg_,ps_beg_;

  nm_beg_=-1;
  for(len_=0;len_<20;len_++){
    if(nm_beg_<0 && xname_[len_]!=' ') nm_beg_=len_;
    if(xname_[len_]=='\0') break;
  }
  if(nm_beg_>0) len_-=nm_beg_; else nm_beg_=0;/* leading blanks */

  ps_beg_=-1;
  for(slen_=0;slen_<maxlen_;slen_++){
    if(ps_beg_<0 && ps_[slen_]!=' ') ps_beg_=slen_;
    if(ps_[slen_]=='\0') break;
  }
  if(ps_beg_>0) slen_-=ps_beg_; else ps_beg_=0;/* leading blanks */

  if(slen_==0){/* lege string */
    seqo_str[pos++]='<';pos+=copy0(&xname_[nm_beg_],&seqo_str[pos],len_);
    pos+=copy0("/>",&seqo_str[pos],2);
  }
  else{
    seqo_str[pos++]='<';pos+=copy0(&xname_[nm_beg_],&seqo_str[pos],len_);seqo_str[pos++]='>';
    copy(&ps_[ps_beg_],&seqo_str[pos],slen_);
    for(k=0;k<slen_;k++){
      if(seqo_str[pos+k]=='<') seqo_str[pos+k]=' ';
      if(seqo_str[pos+k]=='>') seqo_str[pos+k]=' ';
      if(seqo_str[pos+k]=='&') seqo_str[pos+k]=' ';
    }
    pos+=slen_;
    pos+=copy0("</",&seqo_str[pos],2);pos+=copy0(&xname_[nm_beg_],&seqo_str[pos],len_);seqo_str[pos++]='>';
  }
  add_eor();
}

static dmp2file()
{
  int16 k;
 
	for(k=0;k<pos;k++) if(seqo_str[k]=='\x96') seqo_str[k]=' '; // gradenteken
  CnvJamaChar(seqo_str,pos,0);
  seqo_len=0;
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
/*  seqo_flush(); */
    if(seqo_len){
      fasseqo(80,seqo_mode,seqo_len+4);
      seqo_pos+=seqo_len;
      *l(80,1)=seqo_pos;
      seqo_len=0;
    }
  }
  pos=0;
}

static add_eor()
{
  seqo_str[pos++]=0x0D;
  seqo_str[pos++]=0x0A;
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
  int16 curs=1,k,key,z;
  float bd_;

  ram2stu(nr_);
  fasinit(6);*u(6,1)=tblin.rec;fasgeti(6);
  calc(nr_,YES);
 
  FOREVER{
    redo:
    scrget(2,18);z=1; // PAS OP : als ge dit scherm aanpast owv wijzigende tekst handlingkost !!!!
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else streepje(z++);
    scrofld(z++,6,3,-1);
    scrifld(z++,fm_aantal,&tblin.qlv);
    if(fldlen(6,12)) {fmt_get(6,12);scrifld(z++,fmt,&tblin.tbprx[0]);}
    else streepje(z++);
    if(fldlen(6,13)) {fmt_get(6,13);scrifld(z++,fmt,&tblin.valuta[0]);}
    else streepje(z++);
    for(k=0;k<4;k++){
      if(fldlen(6,14+k)) {fmt_get(6,14+k);scrifld(z++,fmt,&tblin.tbprx[1+k]);}
      else streepje(z++);
    }
    for(k=0;k<2;k++){
      if(fldlen(6,19+k) && sys3652) {fmt_get(6,19+k);scrifld(z++,fmt,&tblin.tbprx[6+k]);}
      else streepje(z++);
    }
    fmt_get(6,18);scrifld(z++,fmt,&tblin.tbprx[5]);
    if(fldlen(6,30)) {fmt_get(6,30);scrifld(z++,fmt,&tblin.accijns);}
    else streepje(z++);
    if(fldlen(6,41)){
      bd_=tblin.q_leeg * tblin.bd_leeg;
      scrifld(z++,fm_of6_2,&bd_);
    } else streepje(z++);

    for(k=0;k<6;k++) if(fldlen(6,21+k)) scrfld(z++,6,21+k); else z++;
		if(fldlen(11,5)){fmt_get(11,5); scrifld(z++,fmt,tblin.ref_lev);} else z++;
		if(fldlen(11,68)){fmt_get(11,68); scrifld(z++,fmt,&tblin.q_per_bak);} else z++;
    scrifld(z++,fm_of7_2,&tot_goed);scrifld(z++,fm_of7_2,&tot_leeg);
		if(sys3652==2){ // PAS OP
			scraddf(100,9,43,0);scrifld(100,VarTextFmt(1,0),"%");
		}
    key=scrupd(curs,0x00E0);curs=3;
    if(key==106) break;
    if(fldlen(6,30)) *f(6,30)=tblin.accijns;
    stu2ram(nr_);
    if(key==108) {/* verkoopprijzen aanpassen */
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			fasupd(6);
			if(tblin.rec11){
				fasinit(11); *u(11,1)=tblin.rec11;fasgeti(11);
				copy(tblin.ref_lev,s(11,5),fldlen(11,5));
				if(fldlen(11,68)) *f(11,68)=tblin.q_per_bak;
				fasupd(11);
			}
			else if(tblin.rec && tblin.ref_lev[0]){
				fasinit(11); *u(11,2)=*u(1,1);*u(11,3)=tblin.rec;
				copy(tblin.ref_lev,s(11,5),fldlen(11,5));
				if(fldlen(11,68)) *f(11,68)=tblin.q_per_bak;
				if(*u(11,8)==0) *u(11,8)=ft_date;
				fasadd(11);
				tblin.rec11=*u(11,1);
				stu2ram(nr_);
			}
			break;
		}
    calc(nr_,YES);
  }
}
 

static calc(nr_,mode_)
int16 nr_,mode_;
{
  int16 j,k,max_;
  float kort_,accijns_,bd_leeg_;
									
  alg_tot=0;tot_leeg=0;tot_goed=0;
  if(mode_) max_=nr_+1; else max_=max_line;
  for(k=nr_;k<max_;k++){
    ram2stu(k);
    if(tblin.omschr[0] && tblin.rec){
      fasinit(6);*u(6,1)=tblin.rec;fasgeti(6);
      ap_netlev=tblin.tbprx[0];
      if(sys3720) ap_netlev/=1.+tblin.btw/100;
      accijns_=0;
      if(fldlen(6,30)) accijns_=tblin.accijns;
      if(tblin.tbprx[0]==0) accijns_=0;
      if(fldlen(6,13)){/* vreemde valuta */
	ap_netlev=valu_cnv(s(6,13),def_munt,(double)ap_netlev,(double)0.01);
      }
      ap_netlev-=accijns_;
      if(!sys3588){/* geen cascade */
	for(kort_=0,j=0;j<3;j++){
	  if(fldlen(6,14+j)) kort_+=tblin.tbprx[1+j];
	}
	ap_netlev*=(100-kort_)/100;
      }
      else{/* cascade */
	for(j=0;j<3;j++) if(fldlen(6,14+j)) ap_netlev*=(100-tblin.tbprx[1+j])/100;
      }
      if(fldlen(6,17)) ap_netlev-=tblin.tbprx[4];
			ap_netlev+=accijns_;
			if(sys3652){
				if(fldlen(6,19)) {
			    if(sys3652==2) ap_netlev*=(100.+tblin.tbprx[6])/100.;  // als %
			    else ap_netlev+=tblin.tbprx[6];
		    }
	//			if(fldlen(6,19)) ap_netlev+=tblin.tbprx[6];
				if(fldlen(6,20)) ap_netlev+=tblin.tbprx[7];
			}
     
      if(ap_netlev) tblin.tbprx[5]=ap_netlev;
      tblin.calc_qlv=tblin.qlv;
      if(tblin.stuks_fl=='S' && *f(6,31)>1) tblin.calc_qlv/=*f(6,31);
      else if(tblin.stuks_fl=='P' && fldlen(6,83) && *f(6,83)>1) tblin.calc_qlv*=*f(6,83);
      ap_netlev*=tblin.calc_qlv;
      if(tblin.groep!=99) tblin.tot_akw=ap_netlev;
      else {tblin.tot_akw=0;tot_leeg+=ap_netlev;}
      if(tblin.groep!=99 && fldlen(6,41)){
				if(tblin.stuks_fl=='S'){
					copy(s(6,44),leeggcod,fldlen(6,44));
					fasinit(6);copy(leeggcod,s(6,2),fldlen(6,2));
					faskeyi(6,1,0);
					bd_leeg_=*f(6,18);
					fasinit(6);*u(6,1)=tblin.rec;fasgeti(6);
					tot_leeg+=bd_leeg_ * tblin.qlv;
				}
				else if(tblin.stuks_fl=='P'){
					tot_leeg+=(tblin.q_leeg * tblin.bd_leeg) * tblin.calc_qlv;
				}
				else{
					tot_leeg+=(tblin.q_leeg * tblin.bd_leeg) * tblin.qlv;
				}
      }
      tot_goed+=tblin.tot_akw;
      stu2ram(k);
    }
    alg_tot=tot_leeg + tot_goed;
  }
}

static full_chk()
{
  if(free<4){prtform(0);ft_hdr();}
}
 
static prt_best()
{
  int16 k;
  char str_[25];

  getsysprNew(7,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
	if (prtopen(prtnr,form_dat,6,80,pr_mode,0)!=0) {goto endsr;}
  zero(str_,sizeof str_);copy("Bestelling ",str_,11);copy(s(1,3),&str_[11],10);
  p_pdfname(str_,ft_date,0);
  
  scrget(1,6);scrupd(-3,0);
  ft_hdr();
  prttext("<t3u>Code<ut11u>Uw ref.<ut27u>Omschrijving<ut65u>Aantal<u>");nextline();
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(tblin.omschr[0]){
      full_chk();
      fasinit(6);*u(6,1)=tblin.rec;fasgeti(6);
      prttext("<t3>");prtfld(6,2,-1);
      if(fldlen(6,8)) fmt_get(6,8); else fmt_get(11,5); prttext("<t11>");prtifld(fmt,&tblin.ref_lev,-1);
      prttext("<t27>");prtfld(6,3,-1);
      prttext("<t63>");prtifld(fm_aantal,&tblin.qlv,-1);
      if(tblin.stuks_fl=='S') prttext(" St");
      else if(tblin.stuks_fl=='P') prttext(" Pl");
      nextline();
    }
  }
  if(free<32 && free>26) {nextline();nextline();}
  else skip_lin(32);
  for(k=0;k<4;k++){
    if(opm_foot[k][0]!='\0'){
      full_chk();
      prtifld(fm_us75,opm_foot[k],-1);nextline();
    }
  }
  prtform(0);
  prtform(0);SpoolFileNr=prtclose();

  endsr:;
}

static ft_hdr()
{
  int16 j,k,stu_;
  char *ps;

  stu_=1;
  free=999;
  prttext("<t1><eb>");prtifld(fm_os79,&firma[0],30);prttext("<eb>");nextline();
  prttext("<t1>");prtifld(fm_os79,&firma[31],25);
  if(firma[firm[6].begpos]){
    prttext("<t40>");ps=firm[6].txt[taaltxt];prttext(ps);
    for(j=0;j<9;j++) if(*ps++=='\0') break;
    for(;j<9;j++) prtblank(1);prttext(": ");
    prtifld(fm_os79,&firma[firm[6].begpos],firm[6].lengte);
  }
  nextline();
  prttext("<t1>");prtifld(fm_os79,&firma[57],7);prtblank(2);
  prtifld(fm_os79,&firma[65],20);
  if(firma[firm[7].begpos]){
    prttext("<t40>");ps=firm[7].txt[taaltxt];prttext(ps);
    for(j=0;j<9;j++) if(*ps++=='\0') break;
    for(;j<9;j++) prtblank(1);prttext(": ");
    prtifld(fm_os79,&firma[firm[7].begpos],firm[7].lengte);
  }
  nextline();
  if(free>66) nextline();
  for(k=0;k<6;k++){
    if(firma[firm[k].begpos]){
      prttext("<t1>");ps=firm[k].txt[taaltxt];prttext(ps);
      for(j=0;j<12;j++) if(*ps++=='\0') break;
      for(;j<12;j++) prtblank(1);prttext(": ");
      prtifld(fm_os79,&firma[firm[k].begpos],firm[k].lengte);
      nextline();
    }
  }

  skip_lin(60);
  prttext("<t47>");prtfld(stu_,3,-1);nextline();
  prttext("<t47>");prtfld(stu_,4,-1);nextline();
  prttext("<t47>");prtfld(stu_,5,-1);prtblank(1);prtfld(stu_,6,-1);nextline();
  if(fldlen(stu_,7)>0){
    prttext("<t47>");prtfld(stu_,7,-1);
    nextline();
  }
  skip_lin(54);
  prttext("<t3><be>Bestelbon<be>");nextline();nextline();
  prttext("<t3>Telefoon<t18>Fax<t37>Lev.<t50>Nummer<t66>Datum");
  nextline();
  skip_lin(51);
  prttext("<t3>");prtfld(stu_,8,-1);
  prttext("<t18>");prtfld(stu_,9,-1);
  prttext("<t36>");
  k=1; if(klcd) k=2;
  prtfld(stu_,k,-1);
  prttext("<t50>");prtifld(fm_os10,ft_nr,-1);
  prttext("<t64>");prtifld(fm_udat,&ft_date,-1);
  nextline();
  skip_lin(47);
}
 
static prt_lever()
{
  int16 j,k,z;
  float qlv_,bd_ak_,bd_lg_,ak_pr_;
  char str_[25],pl_mag_[10];
									

  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
	k=80;
#if FLAGNEY
	k=96;
#endif
  if((errnum=prtopen(prtnr,form_dat,6,k,pr_mode,2))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);z=1;
  prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
#if FLAGNEY
	prtitab(z,VarTextFmt(6,0),pl_mag_,1,-1); prttitle(z++,"PlMag",3);
#endif
  prttab(z,6,3,1,-1); prttitle(z++,"Naam",3);
  prtitab(z,fm_aantal,&qlv_,0,-1); prttitle(z++,"Aantal",0x13);
  prtitab(z,fm_of6_2,&ak_pr_,0,-1); prttitle(z++,"AK-prijs",0x13);
  prtitab(z,fm_of7_2,&bd_ak_,0,-1); prttitle(z++,"Goederen",0x13);
	if(fldlen(6,41)){ prtitab(z,fm_of7_2,&bd_lg_,0,-1); prttitle(z++,"Leeggoed",0x13);}
  prtbuf(1);
  zero(str_,sizeof str_);copy("Levering ",str_,9);copy(s(1,3),&str_[9],10);
  p_pdfname(str_,ft_date,0);
  prttext("<b>Levering : ");prtfld(1,3,25);
  prttext(" Factuur : ");prtifld(fm_us10,ft_nr,-1);
  prttext(" Datum : "); prtifld(fm_udat,&ft_date,-1);
  prttext("<b>");
  nextline();nextline();
  if(filiaal && filiaal!=99){/* direct leveren aan filiaal */
    prttext("<t10>Rechtstreeks geleverd in filiaal : ");
    prtifld(fm_os6,nm_fil,-1); nextline();nextline();
  }
  free=0;zero(pl_mag_,sizeof pl_mag_);
#if FLAGNEY
	SortBonIndex();
#endif
  for(k=0;k<max_line;k++){
    if(free<0) goto endsr;
#if FLAGNEY
		if(IxLin[k]<0) break;
    ram2stu(IxLin[k]);
#else
    ram2stu(k);
#endif
    if(tblin.omschr[0]){
      fasinit(6);
      copy(tblin.code,s(6,2),fldlen(6,2));
			copy(tblin.PlMag,pl_mag_,fldlen(6,29));
      copy(tblin.omschr,s(6,3),fldlen(6,3));
      qlv_=tblin.calc_qlv;ak_pr_=tblin.tbprx[5];
      if(tblin.stuks_fl!='S'){
	bd_lg_=(tblin.q_leeg * tblin.bd_leeg) * tblin.calc_qlv;
      }
      else{
	bd_lg_=(tblin.q_leeg * tblin.bd_leeg) * tblin.qlv;
      }
      if(tblin.groep==99) bd_lg_=qlv_*ak_pr_;
      bd_ak_=tblin.tot_akw;
      for(j=0;j<20;j++) prtinfo(j,0);nextline();
    }
  }
  nextline();
  fasinit(6);copy("TOTAAL  ==>",s(6,3),12);
  qlv_=0;ak_pr_=0;bd_lg_=tot_leeg;bd_ak_=tot_goed;pl_mag_[0]='\0';
  for(j=0;j<20;j++) prtinfo(j,2);nextline();
  nextline();
  if(free<32 && free>26) {nextline();nextline();}
  else skip_lin(32);
  for(k=0;k<4;k++){
    if(opm_foot[k][0]!='\0'){
      full_chk();
      prtifld(fm_us75,opm_foot[k],-1);nextline();
    }
  }
  prtform(0);prtclose();
  endsr:;
}
 
static SortBonIndex()
{
  int16 j,k,len_,sw,max_;
  char str1[35],str2[35],*ps_;
 
  len_=sizeof tblin.PlMag; ps_=tblin.PlMag;
	for(k=0;k<500;k++) IxLin[k]=-1;
  max_=max_line-1;
  for(max_;max_>=0;max_--){ram2stu(max_); if(tblin.omschr[0]) break;}
	max_++;
  for(k=0;k<max_;k++){
    ram2stu(k);
    if(tblin.omschr[0]=='\0'){
			copy((char *)p_tblin,sortbuf,len_tblin);
      for(j=k;j<max_;j++){
				ram2stu(j+1);
				stu2ram(j);
      }
      copy(sortbuf,(char *)p_tblin,len_tblin);
      stu2ram(max_); max_--;
    }
		IxLin[k]=k;
  }
  //for(k=0;k<max_;k++) {
  //  ram2stu(k); if(*ps_58_62=='S' && *ps_58_16=='*'){max_=k-1; break;}
  //}
  FOREVER{/* sorteren */
    sw=NO;
    for(k=0;k<max_;k++){
      ram2stu(IxLin[k]);
      copy(ps_,str1,len_);
      ram2stu(IxLin[k+1]);
      if(tblin.omschr[0]){
 				if(cmp_srt(str1,ps_,len_)==1){
					j=IxLin[k];IxLin[k]=IxLin[k+1];IxLin[k+1]=j;
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


static upd_stock()
{
  int16 j,k,clip_;
	uint16 arec_;
  float stock_beg,qlv_,verp_factor_,lev_factor_,stockqlv_;

	fasunlck(-2);
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(tblin.rec && tblin.qlv){
      fasinit(6);*u(6,1)=tblin.rec;fasgeti(6);
			lev_factor_=1.;	if(*f(6,31)==0) *f(6,31)=1;
			if(tblin.q_per_bak>0 && *f(6,31)>0 && tblin.q_per_bak!=*f(6,31)) lev_factor_=tblin.q_per_bak/ *f(6,31); 
      if(fldlen(6,34)) if(*f(6,34)==0) *f(6,34)=*f(6,18);
      if(sys3624==1 && fldlen(11,2)==0){
				if(fldlen(6,12)) *f(6,12)=tblin.tbprx[0]/lev_factor_;
				for(j=0;j<4;j++){
					if(fldlen(6,14+j)) *f(6,14+j)=tblin.tbprx[1+j];
				}
				*f(6,18)=tblin.tbprx[5]/lev_factor_;
      }
      if(sys3758 & 0x02) *u(6,7)=*u(1,1);/* laatste leverancier voor aankoop */
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
			fasupd(6); // prijsgedoe al saven, stock kan op ander artikel komen 
 
			clip_=NO;
			if(fldlen(6,102) && *u(6,102)){// stock/omzet op moederfiche bijwerken
				arec_=*u(6,1);
				stockqlv_=*f(6,31);
				*u(6,1)=*u(6,102);fasgeti(6);
#if FLAGSAS | FLAGGRS | FLAGALB
				clip_=YES; // gekoppeld, altijd moederfiche bijwerken
#else
				if(*f(6,31)!=stockqlv_) clip_=YES;
#endif
				fasinit(6);*u(6,1)=arec_;fasgeti(6);
			}		
			verp_factor_=1.;
			if(clip_){
				verp_factor_=*f(6,31);
				*u(6,1)=*u(6,102);fasgeti(6);
				lev_factor_=1.;	if(*f(6,31)==0) *f(6,31)=1; // terug naar origineel aantal zetten en dan vergelijken met moederartikel
			  if(tblin.q_per_bak>0 && *f(6,31)>0 && tblin.q_per_bak!=*f(6,31)) lev_factor_=tblin.q_per_bak/ *f(6,31); 
				if(*f(6,31)) verp_factor_/=*f(6,31); else verp_factor_=1.;
				verp_factor_*=lev_factor_;
			}
			else verp_factor_=lev_factor_;
			// if(tblin.q_per_bak>0 && *f(6,31)>0 && tblin.q_per_bak!=*f(6,31)) verp_factor_=tblin.q_per_bak/ *f(6,31); 
 
			if(filiaal==0 || filiaal==99){// direct leveren aan depot
			  *f(6,33)+=tblin.calc_qlv*verp_factor_;
        if(fldlen(6,34)){/* stock voortschrijdend gemiddeld */
			  	stock_beg=*f(6,33);if(stock_beg<0) stock_beg=0;
				  *f(6,34)=(stock_beg* *f(6,34)+tblin.calc_qlv* tblin.tbprx[5])/(stock_beg+tblin.calc_qlv);
        }
			}
      if(fldlen(6,53)) *f(6,53)+=tblin.calc_qlv*verp_factor_;
      if(fldlen(6,54)) *f(6,54)+=tblin.calc_qlv*tblin.tbprx[5];
      if(fldlen(6,55)) *f(6,55)+=tblin.calc_qlv*verp_factor_;
      if(fldlen(6,56)) *f(6,56)+=tblin.calc_qlv*tblin.tbprx[5];
      if(fldlen(6,51)){
				*f(6,51)-=tblin.calc_qlv*verp_factor_;
				if(*f(6,51)<0) *f(6,51)=0;
      }

      if(fldlen(6,47)) copy(ft_nr,s(6,47),fldlen(6,47));
      if(fldlen(6,46)) if(ft_date) *u(6,46)=ft_date;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
      fasupd(6); // stock en omzetten

      if(filiaal && filiaal!=99){// direct leveren aan filiaal : op eventuele moederfiche 
				fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
				*f(66,11+(filiaal-1)*15)+=tblin.calc_qlv*verp_factor_;
				*f(66,14+(filiaal-1)*15)+=tblin.calc_qlv*verp_factor_;
				if(fldlen(66,16+(filiaal-1)*15)) *u(66,16+(filiaal-1)*15)=ft_date;
				if(*u(66,1)) fasupd(66); else fasadd(66);
      }

			fasinit(6);*u(6,1)=tblin.rec;fasgeti(6); // origineel artikel terug laden
			verp_factor_=1.;	if(tblin.q_per_bak>0 && *f(6,31)>0 && tblin.q_per_bak!=*f(6,31)) verp_factor_=tblin.q_per_bak/ *f(6,31); 

			if(fldlen(11,1)) upd_akfiche(*u(6,1),tblin.calc_qlv*tblin.tbprx[5],tblin.calc_qlv);
			
      if(((sys3590&2)==2) && fldlen(10,1)>0){
				fasinit(10);
				*u(10,2)=*u(6,7); *u(10,3)=*u(6,1);
				j=fldlen(6,47); if(j>fldlen(10,4)) j=fldlen(10,4);
				copy(ft_nr,s(10,4),j);
				*u(10,5)=ft_date; *f(10,6)=tblin.calc_qlv; *f(10,7)=tblin.tbprx[5];
				if(fldlen(10,8)) *f(10,8)=*f(6,18);
				fasadd(10);
      }
      if(fldlen(6,41) && tblin.rec_leeg){
				fasinit(6);*u(6,1)=tblin.rec_leeg;fasgeti(6);
				qlv_=tblin.calc_qlv; if(tblin.stuks_fl=='S') qlv_=tblin.qlv; qlv_*=verp_factor_;
			/*  *f(6,33)+=qlv_ * tblin.q_leeg; NIET BIJ GEKOPPELD LEEGGOED */
				if(fldlen(6,53)) *f(6,53)+=qlv_ * tblin.q_leeg;
				if(fldlen(6,54)) *f(6,54)+=qlv_ * tblin.q_leeg * *f(6,18);
				if(fldlen(6,55)) *f(6,55)+=qlv_ * tblin.q_leeg;
				if(fldlen(6,56)) *f(6,56)+=qlv_ * tblin.q_leeg * *f(6,18);
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				if(sys2727==0) fasupd(6);
      }
      fasflush(0);
    }
  }
	fasunlck(-1);
}

static dsp_akfich(nr_)
int16 nr_;
{
  int16 j;
  
	if(fldlen(11,1)==0 || ovltest(268)==0) return 0;
	ram2stu(nr_);
  fasinit(6);*u(6,1)=tblin.rec;fasgeti(6);
  ovlcall(268,0);
	if(GetAKFiche(*u(6,1),*u(1,1))){
		if(*f(11,6) || *f(11,60)==0){
			for(j=0;j<6;j++) tblin.tbprx[j]=0; // clearen 
			tblin.tbprx[0]=*f(11,6);
			tblin.tbprx[5]=*f(11,60);
			tblin.tbprx[1]=0;
			for(j=0;j<5;j++){
				if(*f(11,10+j*10)==0) continue;
				if(*s(11,11+j*10)=='%' && *s(11,14+j*10)=='F'){
					if(tblin.tbprx[1]==0 || fldlen(6,15)==0) tblin.tbprx[1]+=*f(11,10+j*10); 
					else if(tblin.tbprx[2]==0) tblin.tbprx[2]=*f(11,10+j*10); 
					else tblin.tbprx[3]=*f(11,10+j*10);
				}
				if(*s(11,11+j*10)=='E' && *s(11,14+j*10)=='F') tblin.tbprx[4]=*f(11,10+j*10);
			}
			copy(s(11,5),tblin.ref_lev,fldlen(11,5));
			if(fldlen(11,68) && *f(11,68)>0 && *f(11,68)!=*f(6,31)) tblin.q_per_bak=*f(11,68);// afwijkende verpakking 
		}
	}
	stu2ram(nr_);
	calc(nr_,YES);
  endsr:;
  return YES;
}

static upd_akfiche(rec_,belastb_,qlv_)
uint16 rec_;
float belastb_,qlv_;
{
  int16 z,key,dd=0,mm=0,jj=0,k;
  flag add_rec_;

	if(fldlen(11,1)==0) return 0;
	fasinit(11);
  add_rec_=NO; if(GetAKFiche(rec_,*u(1,1))==0) add_rec_=YES;
	if(add_rec_) fasinit(11);
  *u(11,2)=*u(1,1);*u(11,3)=rec_;
	if(fldlen(11,63)) *u(11,63)=ft_date; // laatste ak-datum

	if(belastb_==0) goto save_fiche; // geen prijzen bijwerken indien gratis
	if(add_rec_==NO && tblin.tbprx[5]!=*f(11,60)){ // aangekochte prijs is lager dan vorige aankoop
		fasinit(6);*u(6,1)=rec_;fasgeti(6);fmt_get(6,18);
		FOREVER{
			scrnum=0;scrget(2,356); z=1;scraddpicto(1,0,32,2,12,6,605,0,0,"Opgelet!"); 
			scrofld(z++,6,3,-1);
			scrifld(z++,fmt,&tblin.tbprx[0]);scrofld(z++,11,6,-1);
			scrifld(z++,fmt,&tblin.tbprx[5]);scrofld(z++,11,60,-1);
			if(tblin.tbprx[5]<*f(11,60)){
				scrifld(z++,VarTextFmt(5,0),"LAGER");
				scraddpicto(2,0,40,13,4,2,592,0,0,"Nieuwe prijs is lager!"); 
			}
			else{
				scrifld(z++,VarTextFmt(5,0),"HOGER");
			  scraddpicto(3,0,40,13,4,2,512,0,0,"Nieuwe prijs is hoger!"); 
			}
			key=scrupd(-1,0x18);
			if(key==104) break;
			goto save_fiche;
		}
	}

	*f(11,6)=tblin.tbprx[0];
	if(*f(11,60)!=tblin.tbprx[5]){
	  *f(11,60)=tblin.tbprx[5];// netto
		if(fldlen(11,8)) *u(11,8)=ft_date; // indien nettopr wijzigt, dan ook startdatum aanpassen
	}
  if(fldlen(11,61)) *f(11,61)=tblin.tbprx[5]; // statist
	k=0;
  if(YES /* add_rec_ */){
		if(fldlen(11,8)) *u(11,8)=ft_date;
		if(tblin.tbprx[1]){ // %
			*f(11,10+k*10)=tblin.tbprx[1];*s(11,11+k*10)='%';*s(11,12+k*10)='N';*s(11,13+k*10)='E';*s(11,14+k*10)='F';
			k++;
		}
		if(tblin.tbprx[2]){  // %
			*f(11,10+k*10)=tblin.tbprx[2];*s(11,11+k*10)='%';*s(11,12+k*10)='N';*s(11,13+k*10)='E';*s(11,14+k*10)='F';
			k++;
		}
		if(tblin.tbprx[3]){  // %
			*f(11,10+k*10)=tblin.tbprx[3];*s(11,11+k*10)='%';*s(11,12+k*10)='N';*s(11,13+k*10)='E';*s(11,14+k*10)='F';
			k++;
		}
		if(tblin.tbprx[4]){  // EUR
			*f(11,10+k*10)=tblin.tbprx[4];*s(11,11+k*10)='E';*s(11,12+k*10)='N';*s(11,13+k*10)='E';*s(11,14+k*10)='F';
			k++;
		}
		for(k;k<5;k++){
			if(*s(11,14+k*10)=='F') *f(11,10+k*10)=0; // andere directe kortingen wissen 
		}
	}
	save_fiche:;
  if(add_rec_) errnum=fasadd(11);
  else errnum=fasupd(11);
}

static uint16 GetAKFiche(arec_,lrec_)
uint16 arec_,lrec_;
{
	int16 mode_;
	uint16 verv_rec11_=0,rec11_=0;
	   
	fasinit(11);*u(11,3)=arec_;*u(11,2)=lrec_;mode_=1;
	FOREVER{
		next:;
		if(faskeyi(11,2,mode_)) break; mode_=2;
		if(*u(11,3)!=arec_) break;
		if(*u(11,2)!=lrec_) break;
		if(*u(11,9) && *u(11,9)<ft_date) verv_rec11_=*u(11,1); // verlopen promotie
		else rec11_=*u(11,1);
	}
  if(rec11_==0) rec11_=verv_rec11_;
	fasinit(11);if(rec11_) {*u(11,1)=rec11_,fasgeti(11);}
	return rec11_;
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
  int j,k; 
	char *pdum_;

  fasunlck(0);
  fileopen(1);
  fileopen(6);
  if(fldlen(10,1)>0) fileopen(9);
  if(fldlen(66,1)>0) fileopen(12);

  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);
	if(firma[256]){ // IBAN bij voorkeur gebruiken voor rekeningnummer
		copy(&firm[8].begpos,&firm[3].begpos,sizeof firm[0]); 
		firm[8].begpos+=41; // om IBAN te misleiden
	}
  sysget( 294,4,def_munt);
	sysget(1804,2,&k); if(ovltest(11) && (k & 5)) credt_allow=YES;
  sysget(1820,2,&sys1820);
  sysget(1918,2,&sear_stt);
  sysget(2727,2,&sys2727);
  sysget(2976,2,(char *)&RecPrikTik);
	sysget(2978,2,(char *)&sys2978);
	sysget(2987,2,(char *)&RecDistrico);
  sysget(3588,2,&sys3588);
  sysget(3590,2,&sys3590);
	sysget(3592,2,&sys3592);
	sysget(3594,2,&sys3594); if(sys3594!=1) sys3594=0; // om eventueel rommel weg te doen
  sysget(3624,2,&sys3624);
	sysget(3652,2,&sys3652);
  sysget(3720,2,&sys3720);
  sysget(3758,2,&sys3758);
  sysget(3876,2,&sys3876);
  sysget(4436,1,&sys4436);
  sysget(4608,2,&sys4608);
  sysget(2770,60,(char *)&nm_loc[0][0]);
  filiaal=99; copy("DEPOT",nm_fil,6);

  len_1_3mx=fldlen(1,3); if(len_1_3mx>50) len_1_3mx=50;
  if(fldlen(6,12)) flag_apbr=YES;
  ft_date=*u(25,2);
 
	ram=RamBon;
  ram_size=75000;

  if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;zero(ram,ram_size);
  len_tblin=sizeof tblin;max_line=ram_size/len_tblin;
  p_tblin=(char *)&tblin.rec;
	OKovl2282=ovltest(2282); OKovl2283=ovltest(2283); OKovl2284=ovltest(2284); 
  pl_80_1=l(80,1); p_data=s(80,1)+4;
	 fieldspc(6,12,&pdum_,fmt);
  k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;



	OKovl33=ovltest(33); 	CallingOvl=211;
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
static MailDocument(SendMode)  // 0=tonen, 1=direct versturen
int SendMode;
{
  int k,p_adr_=0;
	uint16 yy,mm,dd;
	  
		// keywords invullen 
	zero(MailMergeData[0],sizeof MailMergeData);MailSaveAdres='N';
	
	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy(s(1,3),MailMergeData[k],fldlen(1,3)); continue;}
		if(cmpstr(MailMergeKeywords[k],"ADRES",5)==0){copy(s(1,4),MailMergeData[k],fldlen(1,4)); continue;}
		if(cmpstr(MailMergeKeywords[k],"POSTCODE",8)==0){copy(s(1,5),MailMergeData[k],fldlen(1,5)); continue;}
		if(cmpstr(MailMergeKeywords[k],"GEMEENTE",8)==0){copy(s(1,6),MailMergeData[k],fldlen(1,6)); continue;}
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){p_adr_=k;copy(s(1,21),MailMergeData[k],fldlen(1,21)); continue;}
		if(fldlen(1,130) && cmpstr(MailMergeKeywords[k],"CC_EMAILADRES",13)==0){copy(s(1,130),MailMergeData[k],fldlen(1,130)); continue;}
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNAAM",12)==0){copy0("Bestelbon",MailMergeData[k],50);continue;}
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNUMMER",13)==0){copy0(ft_nr,MailMergeData[k],10); continue;}
		if(cmpstr(MailMergeKeywords[k],"DATUM",5)==0){
			jddate(ft_date,&yy,&mm,&dd);
      stcli_d(&MailMergeData[k][0],(long)dd,2,0);MailMergeData[k][2]='/';
      stcli_d(&MailMergeData[k][3],(long)mm,2,0);MailMergeData[k][5]='/';
      stcli_d(&MailMergeData[k][6],(long)yy,4,0);
			continue;
		}
//		if(cmpstr(MailMergeKeywords[k],"TOTAALBEDRAG",12)==0){stcli_d(MailMergeData[k],(long)(nr_),5,1); continue;}
	}
	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);MailMergeBijlage[0]=SpoolFileNr;
	zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate);
	MailMergeFormaat=7; 

	// if(fldlen(1,16)) MailMergeTaal=talen[taaltxt]; else MailMergeTaal='\0';
	k=SendMail(SendMode); 
	if(k && MailSaveAdres=='J'){copy(MailMergeData[p_adr_],s(1,21),fldlen(1,21));fasupd(1);} // email adres bewaren
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

static cmpstrU(p1,p2,len)
char *p1,*p2;
int16 len;
{
  char b1,b2;
					
  while(len--){
    b1=*p1++;b2=*p2++;
    if(b1>='a' && b1<='z') b1=b1-'a'+'A';
    if(b2>='a' && b2<='z') b2=b2-'a'+'A';
    if(b1!=b2)return 1;
  }
  return 0;
}

static ARTsearch(stu_,mod_) // indien omschrijving begint met +, dan zoeken op referentie leverancier
int16 stu_,mod_;
{
	int16 codelen_;
	char levcode_[25];

	if(*s(stu_,3)!='+') return search(stu_,mod_); // gewone search
	copy(s(6,1),buf1000,fldlen(6,0));
	if(fldlen(6,8)){
		codelen_=fldlen(6,8); copy(s(6,3)+1,levcode_,codelen_);
		fasinit(6);*u(6,7)=*u(1,1);
		FOREVER{
			if(faskeyi(6,4,2)) break;
			if(*u(6,7)!=*u(1,1)) break;
			if(cmpstrU(levcode_,s(6,8),codelen_)==0)return 0;
		}
	}
	copy(buf1000,s(6,1),fldlen(6,0));
	if(fldlen(11,5)==0) {errnum=39;return YES;}
	codelen_=fldlen(11,5); copy(s(6,3)+1,levcode_,codelen_);
	fasinit(11);*u(11,2)=*u(1,1);
	FOREVER{
		if(faskeyi(11,1,2)) break; 
		if(*u(11,2)!=*u(1,1)) break;
		if(cmpstrU(levcode_,s(11,5),codelen_)==0){*u(6,1)=*u(11,3);fasgeti(6); return NO;}
	}
	copy(buf1000,s(6,1),fldlen(6,0));
	errnum=39;return YES;
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


