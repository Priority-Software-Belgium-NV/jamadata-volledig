/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0011GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0011dat
#define ovlcod BKH0011cod
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

char ovldat[] = "bkh0011  00:70 07/10/10 (c) Jamadata";
/* indien ge schermen verandert, doe dit ook voor ovl031 */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXLEN          30
#define FACTEL          4+10+10+10+10+10
#define DIM_EU          27
#define DIMA            10
#define MINFREE         4+10+10+10+10+10
#define MAXFLD          120
#define SEARBFLEN       50
#define flag            uint16

static struct {
  uint16 nr;
  uint16 typ;
  char nm[16];
  uint16 lastnr;
  long fingrb;
  long saldo;
  double saldo_vm;
  char munt[4];
  uint16 blz_o;
  uint16 blz_n;
  char mast_munt;
  double e_saldo;
} j_tab[80];

static struct {
  int16 stelsel;
  char staat1[2];
  int16 vervoer;
  int16 transakt;
	char staat_ori[2];
  char goedercod[8];
  double gewicht;
  double aanveenh;
} intras[FACTEL-4];

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l(),val();
static long val4_1();
extern float *f();
extern double *d(),valu_cnv();
static double absdoubl();
extern uint16 dateadd(),datejd();
static uint16 getgrb();
static flag yet_booked();

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];
extern char RamBon[];
extern int RamBonSize;

static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os16[]  = {7,0x88,16,0,0,0,0};
static char fm_os14[]  = {7,0x88,14,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_us2_U[] = {7,0xC8,2,0,1,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu3_x[] = {6,0xD0,3,0,0x40,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x60,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us8[]   = {7,0xC8,8,0,0,0,0};
static char fm_us3_U[] = {7,0xC8,3,0,1,0,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_ul8_s[] = {6,0xD3,8,0,0x60,0};
static char fm_ol9[]   = {6,0x93,9,0,0x70,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};
static char fm_ud6_2[] = {6,0xD5,6,2,0x70,0};
static char fm_ud6s2[] = {6,0xD5,6,2,0x60,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_of2_1[] = {6,0x94,2,1,0x30,0};
static char fm_uXb[]   = {11,0xC8,1,0,1,0,'X','X',' ',' ',0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uAV[]   = {11,0xC8,1,0,1,0,'A','A','V','V',0};

static char *eu_land[DIM_EU]={"BG","CY","DK","DE","EE","FI","FR","EL","XI","HU","IE","IT","HR","LV","LT","LU",
		       "MT","NL","AT","PL","PT","RO","SI","SK","ES","CZ","SE"};

static uint16 last_arc,MinBkhDatum;
static uint16 df_recnr[15],rec_d_ak, rec_d_vk;
static long kltcent,levcent,df_grb[15],grb_d_ak, grb_d_vk,btws[4];
static char lkg,mast_munt;

static int16 journl,jtb_,scrcount,notfound=0,mcnt,stutyp,aard,mnd_strt,intr_stel;
static int16 sys3770,PeppolProviderInkomend;
static int16 tb_typ[5]={0,1,1,2,2};
static uint16 volgnr,ft_dat,ft_verv,di_verv,rec_nr[FACTEL],btw_vak[FACTEL],bkh_dt;
static uint16 btwvaknr[5];
static uint16 def_qfak,vers_298;
static uint16 oft_dt,oft_jn,oft_nr,jaartal;
static long grb_tb[FACTEL],tb_ofact[50],tb_grbnotfound[50],GrbPeppol[10];
static double bedrag[FACTEL],disc_bd,bd_tot,mst_afrond,tot_mirror;
static long subnr[FACTEL];
static char nm_upd[FACTEL][MAXLEN],nm_old[FACTEL][MAXLEN],opm_bkh[FACTEL][20],sys1833;
static char mededelin[15],anal_ask[FACTEL],def_munt[4],mir_munt[4];
static char taal_i,talen[4],*ram;
static char lkgkod[9],lkgnaam[51],verv_term[4],munt[4];
static char searbuf[SEARBFLEN+1],sys1318;
static float btwpct[4],vak_pct[5],btw_pct[FACTEL],maxdifbtw;
static flag chk_btoeg=YES,verk_chk,sys1850;
static flag sys_vm,lvcd,klcd,debit_allow=NO,credt_allow=NO,sear_stt,sys1862;
static flag sys1894,sys3876,analyt,upd_mode;
static uint16 a_rec_nr[FACTEL-4][DIMA];
static long a_grbrek[FACTEL-4][DIMA];
static float anal_pct[DIMA],DefBtwPct[10];
static double a_bedrag[FACTEL-4][DIMA];
static char anal_nm[DIMA][MAXLEN],anal_onm[DIMA][MAXLEN];
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;
/*
static struct { // !!! STRUCTUUR FACTUURHEADER EN BEWLIJN HETZELFDE HOUDEN IN BKH0011/BKH0033 !!!
	char Code[20];
	char Naam[40];
	char FactuurLineNr[5];
	float Aantal;
	float Prijs;
	double Bedrag;
	float BtwPct;
	char BtwId;
	uint16 GrbRec;
} BewLijn;

static struct { // !!! STRUCTUUR FACTUURHEADER EN BEWLIJN HETZELFDE HOUDEN IN BKH0011/BKH0033 !!!
	char FactuurNr[15];
	int16 CNflag;
	uint16 Datum;
	uint16 VervalDatum;
	char Naam[40];
	char Adres[40];
	char Postcode[10];
	char Gemeente[30];
	char BTWNummer[20];
	uint16 RecNr;
	char KoperReferentie[50];
	char OrderReferentie[50];
	char Mededeling[30];
	char Opmerking[100];
	char PdfFileName[200];
	char PeppolFileName[200];
	float BtwPct[10];
	char  BtwId[10];
	double Belastbaar[10];
	double BTWbedrag[10];
	uint16 GrbRecBtw[10];
	char   InvoiceTypeCode[5];
	int    BewCount;
	double Ft_belastbaar;
	double Ft_btw;
	double Ft_totaal;
	double Ft_Tebetalen;
	int    Detailverwerking;
} FactuurHeader;
 */ 
ovlcod()
{
  int16 key;
  char choice;

  initload();
	if(ovltest(33))	zero(BestelFileUsed,sizeof BestelFileUsed); 
  FOREVER{
    scrget(1,20); fasunlck(0);
    scrifld(2,fm_menu,&choice);
    scrfld(1,25,1);
    key=scrupd(2,0x0401);
    if(key==101 || key==111) ovlexit(-1);
    if(choice=='P') aard=1; else aard=choice-'0';
    switch(choice){
      case '1':
      case '2': if(credt_allow){upd_mode=NO; factr(0);} else errnum=12; break;
      case '3':
      case '4': if(debit_allow){upd_mode=NO; factr(0);} else errnum=12; break;
      case 'P': if(credt_allow && ovltest(33)){upd_mode=NO; factr(1);} else errnum=12; break; 
      case 'H': if(ovltest(33)) ovlcall(33,2); else errnum=12; break; 
      case 'U': upd_mode=YES; upd_fact();break;
      default :errnum=34; break;
    }
  }
}

static factr(mode_) // 0=leeg document 1=via peppol
{
  int16 z,z_base_,curs,curspos_,g,j,k,n,key,len_naam,mask,d_off_=0,fld_code_;
	uint16 last_kl_rec_;
  int16 jaartal,mm,dd,jj,use_Afile=NO;
  char ofname[100],subdir[25];
  char *pnaam, str_[200];
  double dctot,bd_,btw_,belastb_;
  flag first_vk=YES,kn_flag,det_used_;

  fasunlck(-1);
	kn_flag=((aard-1) & 1);
  jtb_=0;
  if(sys1862 & 0x400 && upd_mode==NO){/* selectie aankoopjournaal */
    jtb_=select_jn();
    if(jtb_<0) goto endsr;
  }
  for(jtb_;jtb_<80;jtb_++){
    if(j_tab[jtb_].typ==tb_typ[aard])break;
  }
  if((sys1862 & 0x100) && kn_flag){
    journl=j_tab[jtb_].nr;
    journl++;
    for(jtb_=0;jtb_<80;jtb_++){
      if(j_tab[jtb_].typ==tb_typ[aard] && j_tab[jtb_].nr==journl)break;
    }
  }
  if(jtb_==80){errnum=4;goto endsr;}
  if(upd_mode==NO){
    sysget(10240+20+jtb_*80,2,(char *)&j_tab[jtb_].lastnr);/* zo uptodate mogel.*/
    journl=j_tab[jtb_].nr;
    volgnr=j_tab[jtb_].lastnr+1;
  }
  mast_munt=j_tab[jtb_].mast_munt;
  if(aard<3){
    if(df_recnr[0]==0 || df_recnr[4]==0) {errnum=16;goto endsr;}
    stutyp=1;
    grb_tb[1]=df_grb[0];
    rec_nr[1]=df_recnr[0];
    grb_tb[2]=df_grb[4];
    rec_nr[2]=df_recnr[4];
    fld_code_=lvcd+1;
  }
  else{
    if(df_recnr[1]==0) {errnum=16;goto endsr;}
    stutyp=2;
    grb_tb[1]=df_grb[1];
    rec_nr[1]=df_recnr[1];
    fld_code_=klcd+1;
  }

  zero((char *)btw_pct,sizeof btw_pct);
  zero((char *)btw_vak,sizeof btw_vak);
  pnaam=s(stutyp,3);
  len_naam=fldlen(stutyp,3);if(len_naam>MAXLEN)len_naam=MAXLEN;
	if(upd_mode){
		copy(pnaam,nm_old[0],len_naam);
    rec_nr[0]=*u(stutyp,1)+(stutyp-1)*30000;
	}
  if(upd_mode==NO) bkh_dt=*u(25,2);
  FOREVER{
		redo_fact:;
		if(CheckForFreeSpace(4,MINFREE)) goto endsr;/* onvoldoende vrije records */
    if(upd_mode==NO){
      fasinit(stutyp);
      mededelin[0]='\0';
      ft_dat=0;ft_verv=0;disc_bd=0;di_verv=0;
      if(mast_munt=='E') copy("EUR",munt,4);
      else copy(def_munt,munt,4);
      zero((char *)bedrag,sizeof bedrag);
      zero((char *)nm_upd,sizeof nm_upd);zero((char *)nm_old,sizeof nm_old);
      zero((char *)opm_bkh,sizeof opm_bkh);
      zero((char *)a_rec_nr,sizeof a_rec_nr);
      zero((char *)a_bedrag,sizeof a_bedrag);
      zero((char *)anal_ask,sizeof anal_ask);
      zero((char *)a_grbrek,sizeof a_grbrek);
      zero((char *)anal_nm,sizeof anal_nm);
      zero((char *)anal_onm,sizeof anal_onm);
      zero((char *)subnr,sizeof subnr);
      zero((char *)intras,sizeof intras);
			for(g=4;g<FACTEL;g++){rec_nr[g]=0;grb_tb[g]=0;}
    }
    dctot=0; tot_mirror=0; zero(mir_munt,sizeof mir_munt);
    curs=4; if(aard>=3 && first_vk==NO) curs=6;
    first_vk=NO;
    if(volgnr>65000) volgnr=1;
    d_off_=0;last_kl_rec_=*u(stutyp,1);
		if(mode_==1){
			if(FillDataFromPeppolXml()==0) goto endsr;
			if(sys1318=='J' && PeppolHeader.StockVerwerkt==YES){  // is al ingeboekt
			  if(DisplayWarning("Deze factuur is al ingeboekt! Toch verdergaan?",605,1)==NO) goto redo_fact;
		  }
      if(PeppolHeader.Selfbilling){
		    if(DisplayWarning("Dit is een Self-billing factuur. Als creditnota inboeken?",605,1)==NO) goto redo_fact;
	    }

		}
    redo:
    scrnum=0; scrget(1,20+aard);
		scrfld(1,25,1);
    scrifld(2,fm_uu2,&journl);
    scrifld(3,fm_uu5,&volgnr);
    scrifld(4,fm_udat,&bkh_dt);
    scrofld(5,stutyp,fld_code_,-1);scrfld(-6,stutyp,3);scraddpicto(1,6,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(7,fm_us20,&opm_bkh[0][0]);
    if(aard<3) scrifld(8,fm_us15,&mededelin[0]);
    scrifld(9,fm_udat,&ft_dat);
    if(aard==1 || aard==2 || aard==3) scrifld(10,fm_udat,&ft_verv);
    if(aard==1){
      scrifld(11,fm_ud6_2,&disc_bd);
      scrifld(12,fm_udat,&di_verv);
    }
    scr_bd(13,0);
    scrifld(14,fm_us3_U,munt);
    if(cmpstr(munt,mir_munt,3)){
      scrifld(15,fm_od8_2,&tot_mirror);scrifld(16,fm_os3,mir_munt);
    }
    scr_bd(17,1);
    if(aard<3) scr_bd(18,2);
    if(aard==1) {scr_bd(19,3);scrifld(20,fm_us30,nm_upd[3]);}
    g=d_off_+1;scrifld(22,fm_ou2,&g);
    g=d_off_+10; scrifld(23,fm_ou2,&g);
    z_base_=24;
	  for(g=0;g<10;g++){
      scr_bd(24+g*4,g+4+d_off_);
      z=-(25+g*4);scrifld(z,fm_us30,nm_upd[g+4+d_off_]);/* auto-enter */
      scrifld(26+g*4,fm_us20,&opm_bkh[g+4+d_off_][0]);
      if(analyt){
				if(!is_nul(bedrag[g+4+d_off_]) || nm_upd[g+4+d_off_][0]!='\0'){
					z=3; if(anal_ask[g+4+d_off_]=='X') z=4;
					scraddpicto(10+g,26+g*4,0,0,2,1,130,0,z,"Analytische uitsplitsing"); 
				}
			}
	//			scrifld(27+g*4,fm_uJN,&anal_ask[g+4+d_off_]);
      else if(fldlen(4,19)) scrifld(28+g*4,fm_uu2,&subnr[g+4+d_off_]);
    }
 /*
    for(g=4;g<FACTEL-20;g++){
      scr_bd(24+(g-4)*4,g+d_off_);
      z=-(25+(g-4)*4);scrifld(z,fm_us30,nm_upd[g+d_off_]);
      scrifld(26+(g-4)*4,fm_us20,&opm_bkh[g+d_off_][0]);
      if(analyt) scrifld(27+(g-4)*4,fm_uXb,&anal_ask[g+d_off_]);
      else if(fldlen(4,19)) scrifld(28+(g-4)*4,fm_uu2,&subnr[g+d_off_]);
    }
*/
    scrifld(64,fm_od8_2,&dctot);
    mask=0x06E7;
    if(fldlen(4,48)){scrifld(65,fm_os14," F9 Intrastat ");mask|=0x0100;}
    key=scrupd(curs,mask);
	curs=6;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106){
			if(mode_==1) goto redo_fact;
			else goto endsr;
		}
		if(key==101){
      if(bedrag[0]==0) goto endsr;
      else goto redo;
    } 
/* check journaal */
    if(journl==0){errnum=8;curs=2;goto redo;}
    if(journl!=j_tab[jtb_].nr){/* if changed */
      if(journl==0){errnum=8;curs=2;goto redo;}
      for(jtb_=0;jtb_<80;jtb_++) if(j_tab[jtb_].nr==journl) break;
      if(jtb_==80 || tb_typ[aard]!=j_tab[jtb_].typ){
	errnum=7;curs=2;goto redo;
      }
    }

    if(last_arc){/* check datum */
      if(bkh_dt<=last_arc) errnum=37;
//      if((sys1862 & 8)==0) if(bkh_dt>last_arc+600) errnum=61;
      if(errnum) {curs=4;goto redo;}
    }
		if(MinBkhDatum){/* check datum */
      if(bkh_dt<=MinBkhDatum) errnum=37;
      if(bkh_dt>(*u(25,2)+31) || bkh_dt>(MinBkhDatum+600)) errnum=61;
      if(errnum) {curs=4;goto redo;}
    }
/* check naam */
    if(key!=5001 && *pnaam=='\0'){errnum=38;goto redo;}
    if(key==5001 || cmpstr(nm_old[0],pnaam,len_naam)){
			if(key==5001) { if(search(stutyp,98)) goto redo;}
			else {if(search(stutyp,0)) goto redo;}
      rec_nr[0]=*u(stutyp,1)+(stutyp-1)*30000;
      copy(pnaam,nm_old[0],len_naam);
      if(stutyp==1 && fldlen(1,121)){
				for(g=4;g<FACTEL;g++){
					if(!is_nul(bedrag[g]) || nm_upd[g][0]!='\0') break;
				}
				if(g>=FACTEL){
					for(k=0;k<fldlen(1,121)/2;k++){/* default rekeningen invullen */
						if(k>=(FACTEL-4)) break; // veiligheid 
						if(*(uint16 *)(s(1,121)+k*2)==0) continue;
						fasinit(3);*u(3,1)=*(uint16 *)(s(1,121)+k*2);
						if(fasgeti(3)==0){
							grb_tb[4+k]=*l(3,2);
							rec_nr[4+k]=*u(3,1)+60000;
							grb_deco(&nm_upd[4+k][0],l(3,2));
							for(g=0;g<9;g++) if(nm_upd[4+k][g]=='\0') nm_upd[4+k][g]=' ';
							g=fldlen(3,3);if(g>MAXLEN-9)g=MAXLEN-9;
							copy(s(3,3),&nm_upd[4+k][9],g);
						}
					}
				}
      }
			if(last_kl_rec_!=*u(stutyp,1)) {DisplayMemo(stutyp);last_kl_rec_=*u(stutyp,1);}
    }
    if(key==18 || key==5001){
      if(key==5001 || curspos_==6){curs=7;goto redo;}/* leverancier */
    }
///* automatisch berekenen/invullen van BTW-intracom */
//    if(upd_mode==NO && aard==1 && is_nul(bedrag[3]) && !is_nul(bedrag[0]) && *l(1,10)==0 && fldlen(1,22) && *s(1,22)){
//      fasinit(3); *l(3,2)=df_grb[2]; if(faskeyi(3,1,0)) goto no_intra;
//
//      for(k=0;k<DIM_EU;k++) if(cmpstr(s(1,22),eu_land[k],2)==0) break;
//      if(k>=DIM_EU) goto no_intra;
//
//      btw_=0;
//      for(k=0;k<5;k++) if(vak_pct[k]>btw_) btw_=vak_pct[k];
//      bd_=valu_cnv(def_munt,def_munt,(double)(bedrag[0]* btw_/100.),(double)0.01);
//      if(bedrag[0]>0){
//	bedrag[1]=bd_;
//	bedrag[3]=bd_;copy(s(3,3),nm_upd[3],fldlen(3,3));
//      }
//      else{
//	bedrag[3]=1;copy(s(3,3),nm_upd[3],fldlen(3,3));
//	for(k=4;k<FACTEL;k++) if(nm_upd[k][0]=='\0') break;
//	if(k<FACTEL){
//	  bedrag[k]=1;copy(s(3,3),nm_upd[k],fldlen(3,3));
//	}
//      }
//      no_intra:;
//    }
/* controle munt */
    valu_cnv(munt,def_munt,(double)1.,(double)1.);
    if(errnum){curs=14; goto redo;}
    valu_cnv(munt,"EUR",(double)1.,(double)1.);
    if(errnum){curs=14; goto redo;}

    mst_afrond=0.01;
    for(g=0;g<FACTEL;g++){
      bedrag[g]=valu_cnv(munt,munt,bedrag[g],mst_afrond);
    }
/* controle grb rekeningnamen */
		redo_checkgrb:;
    det_used_=NO;
    for(g=3;g<FACTEL;g++){
      if(!is_nul(bedrag[g])) det_used_=YES;
      if(bedrag[g] && nm_upd[g][0]=='\0'){
				if(g>=14)	d_off_=(g-4)/10 *10; else d_off_=0;
				k=g-d_off_;
				errnum=38;curs=25+(k-4)*4;
				if(aard==1 && g==3) curs=20;
				goto redo;
      }
      if(cmpstr(nm_old[g],nm_upd[g],MAXLEN)){
				if(nm_upd[g][0]!='\0'){
					copy(nm_upd[g],s(3,3),fldlen(3,3));
					if(search(3,0) && errnum==0)errnum=39;
					if(g_anal_tst()) errnum=24;
					if(errnum){
						if(g>=14)	d_off_=(g-4)/10 *10; else d_off_=0;
				    k=g-d_off_;
						curs=25+(k-4)*4;
						if(aard==1 && g==3) curs=20;
						goto redo;
					}
					grb_tb[g]=*l(3,2);
					rec_nr[g]=*u(3,1)+60000;
					makename(nm_upd[g]);
					btw_vak[g]=*u(3,8);
					btw_pct[g]=0;
					for(k=0;k<5;k++) if(*u(3,8)==btwvaknr[k]) {btw_pct[g]=vak_pct[k];break;}
					if(analyt && fldlen(3,32) && g>=4){/* default grb invullen */
						for(k=0;k<DIMA;k++){
							if(fldlen(3,33+k*2) && *l(3,33+k*2)){
					a_grbrek[g-4][k]=*l(3,33+k*2); anal_ask[g]='J';
							}
						}
					}
				}
				copy(nm_upd[g],nm_old[g],MAXLEN);
      }
    }

		if(key>=5010 && k<5010) anal_det(key-5010+4+d_off_);
/* check bedragen */
    if(bedrag[0]==0 && det_used_==NO) {errnum=38;curs=13;goto redo;}
    if(kn_flag && bedrag[0]<0) {errnum=80;curs=13;goto redo;}

    dctot=bedrag[0]-bedrag[1]-bedrag[2]+bedrag[3];
    for(g=4;g<FACTEL;g++)dctot-=bedrag[g];
    if(key==110 && fldlen(1,121) && (aard==1 || aard==2)) add_stdgrb();
	
    if(key==18){curs=curspos_+1;goto redo;}
    if(key==102){
      if(d_off_-=10) if(d_off_<0) d_off_=0;
      curs=24; goto redo;
    }
    if(key==103){
      if((d_off_+20)<FACTEL) d_off_+=10;
      curs=24; goto redo;
    }
    if(!is_nul(dctot)){/* afrondingsfout */
      errnum=10;curs=13;goto redo;
    }


    if(upd_mode==NO && aard==1 && is_nul(bedrag[3]) && !is_nul(bedrag[0]) && *l(1,10)==0 && fldlen(1,22) && *s(1,22)){// automatisch berekenen/invullen van BTW-intracom 
      fasinit(3); *l(3,2)=df_grb[2]; if(faskeyi(3,1,0)) goto no_intra;

      for(k=0;k<DIM_EU;k++) if(cmpstr(s(1,22),eu_land[k],2)==0) break;
      if(k>=DIM_EU) goto no_intra;
			belastb_=0;
      for(g=4;g<FACTEL;g++) if(!is_nul(bedrag[g]) && btw_vak[g]>=81 && btw_vak[g]<=83) belastb_+=bedrag[g];

      btw_=0;
      for(k=0;k<5;k++) if(vak_pct[k]>btw_) btw_=vak_pct[k];
      bd_=valu_cnv(def_munt,def_munt,(double)(belastb_* btw_/100.),(double)0.01);
      if(bedrag[0]>0){
				bedrag[1]=bd_;
				bedrag[3]=bd_;copy(s(3,3),nm_upd[3],fldlen(3,3));
      }
      else{
				bedrag[3]=1;copy(s(3,3),nm_upd[3],fldlen(3,3)); rec_nr[3]=0;
				for(k=4;k<FACTEL;k++) if(nm_upd[k][0]=='\0') break;
				if(k<FACTEL){
					bedrag[k]=1;copy(s(3,3),nm_upd[k],fldlen(3,3));
				}
      }
			if(rec_nr[3]==0) goto redo_checkgrb; // om grb-info verder aan te vullen
      no_intra:;
    }

/* btw-controle */


    if(verk_chk && tb_typ[aard]==2){
      dctot=0;
      for(g=3;g<FACTEL;g++){
	dctot+=bedrag[g]*btw_pct[g]/100.;
      }
      dctot-=bedrag[1];
      dctot=valu_cnv(munt,munt,dctot,mst_afrond);
      if(dctot<(-maxdifbtw) || dctot>maxdifbtw){
	errnum=58;goto redo;
      }
      dctot=0;
    }
/* aanvullen datums */
    if(ft_dat==0) ft_dat=bkh_dt;
    if(ft_verv==0){
      copy(s(stutyp,13),verv_term,3); verv_term[3]='\0';
      ft_verv=dateadd(ft_dat,verv_term);
    }
    if(stutyp<2){
      if(disc_bd==0 && fldlen(stutyp,14)){
/* float of integer */
	if(fldlen(stutyp,14)==4) bd_=*f(stutyp,14); else bd_=*i(stutyp,14);
	if((sys1862 & 0x200) && stutyp==1){
	  for(g=4;g<FACTEL;g++){/* analytisch */
	    if(bedrag[g] && btw_vak[g]==81) disc_bd+=bedrag[g];
	  }
	  disc_bd=(double)(bd_)*disc_bd/(double)100.;
	}
	else{
	  disc_bd=((double)(bd_)*(bedrag[0]-bedrag[1]-bedrag[2]+bedrag[3]))/(double)100.;
	}
	disc_bd=valu_cnv(munt,munt,disc_bd,mst_afrond);
      }
      if(di_verv==0 && fldlen(stutyp,15)){
	copy(s(stutyp,15),verv_term,3);
	di_verv=dateadd(ft_dat,verv_term);
      }
    }

    if(volgnr==0) errnum=38;
    if(yet_booked(journl,volgnr,bkh_dt)) errnum=59;
    if(errnum) {curs=3;goto redo;}
		if(stutyp==1 && upd_mode==NO && CheckAKyetbooked(NO)){
			if(sys1833=='O') curs=7; else curs=8;
			errnum=59; goto redo;
		}

    for(g=4;g<FACTEL;g++){/* analytisch */
      if(bedrag[g] && anal_ask[g]=='J') anal_det(g);
    }
/* spiegeltotaal berekenen voor display */
    if(cmpstr(munt,def_munt,3)==0) copy("EUR",mir_munt,3);
    else copy(def_munt,mir_munt,3);
    bd_=0.01; if(cmpstr(mir_munt,"BEF",3)==0) bd_=1.;
    tot_mirror=valu_cnv(munt,mir_munt,bedrag[0],bd_);
    if(key==109) intrastat();
    if(key!=101 && key!=108 && key!=111) goto redo;
		//if(stutyp==1 && upd_mode==NO && CheckAKyetbooked(YES)){
		//	if(sys1833=='O') curs=7; else curs=8;
		//	errnum=59; goto redo;
		//}
    if(is_nul(bedrag[0])){
      if(scr_ok("Wenst U echt een NUL-factuur te boeken ???")==NO) goto redo;
    }
    if(upd_mode){/* eerst originele factuur schrappen */
      for(k=0;k<50;k++){
	if(tb_ofact[k]){
	  fasinit(4);chg4_1((long)tb_ofact[k]);fasgetu(4);faskill(4);
	}
      }
    }
/* boek */
    bedrag[0]=-bedrag[0];
    bedrag[3]=-bedrag[3];
    if(aard==2 || aard==3){
      for(g=0;g<FACTEL;g++){bedrag[g]=-bedrag[g];}
      for(g=0;g<FACTEL-4;g++)for(k=0;k<DIMA;k++)a_bedrag[g][k]=-a_bedrag[g][k];
    }
    for(g=1;g<FACTEL;g++) {subnr[g]=(1L<<subnr[g])/2;subnr[0]|=subnr[g];}
    boek();
    if(sys1862 & 64) upd_sta();

    if(upd_mode==NO){
      j_tab[jtb_].lastnr=volgnr++;
      sysput(10240+20+jtb_*80,2,(char *)&j_tab[jtb_].lastnr);
      sysflush();
			if(ovltest(33)){
				if(BestelFileUsed[0][0]  && *(uint16 *)(&BestelFileUsed[0][100])==33){
					zero(ofname,sizeof ofname);	sysget(1286,25,ofname);
					if(ofname[0]){  // kopie opslaan voor extern boekhoudpakket
						for(k=0;k<25;k++) if(ofname[k]=='\0') break;
						for(j=99;j>=0;j--) if(BestelFileUsed[0][j]=='\\') break;
						copy0(&BestelFileUsed[0][j+1],&ofname[k],50);
						CopyMoveFile(BestelFileUsed[0],ofname,0);
					}
					zero(subdir,sizeof subdir);
					zero(ofname,sizeof ofname);
					sysget(1731,25,subdir); // AKKOPIE
	        if(subdir[0]=='\0') sysget(4704,25,subdir);// indien leeg dan verkoopmap nemen
					copy(subdir,ofname,25);
					jddate(bkh_dt,&jaartal,&mm,&dd);
					if(mnd_strt!=1){// indien boekjaar NIET op 1/1 begint, dan uitkijken met overlappende factuurnummers
						if(mm>=mnd_strt) use_Afile=YES; // indien in nieuw BOEKjaar van huidig kalenderjaar
					}
					jaartal%=100; 
					for(k=0;k<25;k++) if(ofname[k]=='\0') break;
					copy("AK",&ofname[k],2);k+=2;
					copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';k+=3;
					stcli_d(&ofname[k],(long)(j_tab[jtb_].lastnr),5,0);k+=5;
					stcli_d(&ofname[k],(long)(*u(1,1)),5,0);k+=5;
					ofname[k++]='.';stcli_d(&ofname[k],(long)jaartal,2,0);k+=2;
					if(use_Afile)	ofname[k]='A';
					if(sys1318=='J'){
						if(DisplayWarning("Wenst U deze factuur nog te verwerken in de voorraad ?",605,1)==YES){
							ovlcall(33,4);
							CopyMoveFile(BestelFileUsed[0],ofname,0); 
     	      }
					  else CopyMoveFile(BestelFileUsed[0],ofname,1);
					}
          else CopyMoveFile(BestelFileUsed[0],ofname,1); 
					zero(BestelFileUsed[0],sizeof BestelFileUsed[0]);
/*
		zero(BestelFileUsed[0],sizeof BestelFileUsed[0]);copy(ofname,BestelFileUsed[0],k);
					for(n=0;n<100;n++) if(BestelFileUsed[k][n]=='\0') break;
					copy(BestelFileUsed[k],str_,n);str_[n]='|';
					copy(BestelFileUsed[k],&str_[n+1],n);
					for(n=0;n<200;n++) if(str_[n]=='\0') break;
					for(j=n;j>0;j--) if(str_[j]=='.') break;
					if(j<=1) {j=n;str_[j]='.';}
					j++;
					copy("DONE",&str_[j],4);
					fasclos(-2);
					fasopen(str_,100);  // renamen naar .DONE				
*/
					zero(BestelFileUsed[0],sizeof BestelFileUsed[0]); 
				}
			}
    }
    if(key==111) ovlexit(-1);
    if(key==101 || (kn_flag && !(sys1862 & 0x100))){
			if(mode_==0) goto endsr;
		}
    if(upd_mode) break;
  }
endsr:;
	if(ovltest(33)){
		for(k=0;k<2;k++) if(BestelFileUsed[k][0]  && *(uint16 *)(&BestelFileUsed[k][100])==33){
			zero(BestelFileUsed[k],sizeof BestelFileUsed[0]); 
		}
	}
}

static int FillDataFromPeppolXml() // !!! STRUCTUUR FACTUURHEADER EN BEWLIJN HETZELFDE HOUDEN IN BKH0011/BKH0033 !!!
{
	int j,k,n;
	char str_selectie_[100];
	double factor_;

	if(ovlcall(33,0)==0) return 0;
	scrget(1,7);scrupd(-3,0);

	mededelin[0]='\0';
  ft_dat=0;ft_verv=0;disc_bd=0;di_verv=0;
  if(mast_munt=='E') copy("EUR",munt,4);
  else copy(def_munt,munt,4);
  zero((char *)bedrag,sizeof bedrag);
  zero((char *)nm_upd,sizeof nm_upd);zero((char *)nm_old,sizeof nm_old);
  zero((char *)opm_bkh,sizeof opm_bkh);
  zero((char *)a_rec_nr,sizeof a_rec_nr);
  zero((char *)a_bedrag,sizeof a_bedrag);
  zero((char *)anal_ask,sizeof anal_ask);
  zero((char *)a_grbrek,sizeof a_grbrek);
  zero((char *)anal_nm,sizeof anal_nm);
  zero((char *)anal_onm,sizeof anal_onm);
  zero((char *)subnr,sizeof subnr);
  zero((char *)intras,sizeof intras);
	for(k=4;k<FACTEL;k++){rec_nr[k]=0;grb_tb[k]=0;}

	factor_=1.; if(PeppolHeader.Selfbilling) factor_=-1.; // selfbilling factuur altijd als creditnota inboeken
	copy(PeppolHeader.Mededeling,mededelin,sizeof mededelin);
	copy(PeppolHeader.FactuurNr,&opm_bkh[0][0],15);
	ft_dat=PeppolHeader.Datum;
	ft_verv=PeppolHeader.VervalDatum;
	bedrag[0]=PeppolHeader.Ft_totaal*factor_;
	bedrag[1]=PeppolHeader.Ft_btw*factor_;
	j=4;
	if(PeppolHeader.Detailverwerking==YES){ // op artikelniveau
		for(k=0;k<PeppolHeader.BewCount;k++){
//			copy(ram+(hdr_size_+k*det_size_),(char *)PeppolLijn.Code,det_size_);
			if(PeppolLijn[k].Aantal || !is_nul(PeppolLijn[k].Bedrag)){
				bedrag[j]=PeppolLijn[k].Bedrag*factor_;
				if(PeppolLijn[k].GrbRec){
					fasinit(3);*u(3,1)=PeppolLijn[k].GrbRec;fasgeti(3);
					copy(s(3,3),nm_upd[j],fldlen(3,3));
				}
				else copy(PeppolLijn[k].Naam,nm_upd[j],30);
				copy(PeppolLijn[k].Naam,opm_bkh[j],20);
				j++;
			}
		}
	}
	else{
		for(k=0;k<10;k++){
			if(!is_nul(PeppolHeader.Belastbaar[k])){
				bedrag[j]=PeppolHeader.Belastbaar[k]*factor_;
				if(PeppolHeader.GrbRecBtw[k]){
					fasinit(3);*u(3,1)=PeppolHeader.GrbRecBtw[k];fasgeti(3);
					copy(s(3,3),nm_upd[j],fldlen(3,3));
				}
				else{
	  			if((PeppolHeader.BtwId[k]=='E' && PeppolHeader.BtwPct[k]==0) || PeppolHeader.BtwId[k]=='Z') {
						if(GrbPeppol[9]){
							fasinit(3);*l(3,2)=GrbPeppol[9];
							if(faskeyi(3,1,0)) sprintf_s(nm_upd[j],30,"Leeggoed");
							else copy(s(3,3),nm_upd[j],fldlen(3,3));
						}
						else sprintf_s(nm_upd[j],30,"Leeggoed");
					}
  	  		else{
						for(n=0;n<9;n++) if(DefBtwPct[n]==PeppolHeader.BtwPct[k]) break;
						if(n<9 ){
							if(GrbPeppol[n]){
								fasinit(3);*l(3,2)=GrbPeppol[n];
								if(faskeyi(3,1,0)) sprintf_s(nm_upd[j],30,"%2.0f%%",PeppolHeader.BtwPct[k]);
								else copy(s(3,3),nm_upd[j],fldlen(3,3));
							}
							else sprintf_s(nm_upd[j],30,"%2.0f%%",PeppolHeader.BtwPct[k]);
						}
					}
				}
				j++;
			}
		}
		if(fldlen(1,121)){ // standaard GRB invullen zodat men gemakkelijk kan uitsplitsen
			for(k=0;k<fldlen(1,121)/2;k++){/* default rekeningen invullen */
				if(*(uint16 *)(s(1,121)+k*2)==0) continue;
				fasinit(3);*u(3,1)=*(uint16 *)(s(1,121)+k*2);
				if(fasgeti(3)==0){
					for(n=4;n<FACTEL;n++){
						if(cmpstr(s(3,3),nm_upd[n],fldlen(3,3))==0) goto next_line;
						if(is_nul(bedrag[n]) && nm_upd[n][0]=='\0') break;
					}
					if(n<FACTEL){
						grb_tb[n]=*l(3,2);
						rec_nr[n]=*u(3,1)+60000;
						copy(s(3,3),&nm_upd[n][0],fldlen(3,3));
					}
				}
				next_line:;
			}
    }
	}
// voorlopig niks doen met detail, enkel totalen per BTW%
			//for(k=0;k<PeppolHeader.BewCount;k++) copy((char *)PeppolLijn[k].Code,ram+(hdr_size_+k*det_size_),det_size_);
			//if(OrigLevRec){ // bestaande leverancier terugzetten uit veiligheid
			//	fasinit(1);*u(1,1)=OrigLevRec; fasgeti(1);
			//}
	return 1;
}

static add_stdgrb()
{
  int16 j,k,max_;
  uint16 rec_;

  if(scr_ok("De gebruikte rekeningen standaard maken voor deze leverancier?")==NO) goto endsr;
  max_=fldlen(1,121)/2;
  for(k=4;k<FACTEL;k++){
    if(rec_nr[k]==0) continue;
    rec_=rec_nr[k]-60000;
    for(j=0;j<max_;j++){
      if(*(uint16 *)(s(1,121)+j*2)==rec_) break;
    }
    if(j<max_) continue;
    for(j=0;j<max_;j++){
      if(*(uint16 *)(s(1,121)+j*2)==0) break;
    }
    if(j<max_) *(uint16 *)(s(1,121)+j*2)=rec_;
  }
  fasupd(1);
  endsr:;
}

static select_jn()
{
  int16 g,k,z,key,jr_nr_,rec_nr[5];
  char benam[25];
									
  for(k=0;k<5;k++) rec_nr[k]=100;
  g=0;jr_nr_=0;
  for(k=0;k<80;k++){
    if(j_tab[k].nr && j_tab[k].typ==tb_typ[aard]) rec_nr[g++]=k;
    if(g>=5) break;
  }
	jr_nr_=j_tab[rec_nr[0]].nr;
  FOREVER{
    redo:
    scrnum=0;scrget(1,229); z=1;
    for(k=0;k<5;k++){
      if(rec_nr[k]<100){
	scrifld(z++,fm_ou2,&j_tab[rec_nr[k]].nr);
	sysget(10240+4+rec_nr[k]*80,16,benam);
	scrifld(z++,fm_os16,benam);
      }
    }
    scrifld(11,fm_uu2,&jr_nr_);
    if(g>1) key=scrupd(1,0x4A1);
    if(key==101 || key==111) return(-1);
    for(k=0;k<5;k++) if(rec_nr[k]<100 && jr_nr_==j_tab[rec_nr[k]].nr) break;
    if(jr_nr_==0 || k==5) {errnum=34;goto redo;}
    for(k=0;k<80;k++) if(jr_nr_==j_tab[k].nr) break;
    if(jr_nr_==0 || k==80) {errnum=34;goto redo;}
    return k;/* positie in jtab */
  }
  return -1;
}

static CheckAKyetbooked(chk_bdr_) // controleer of AK factuur al geboekt is geweest met die referentie
uint16 chk_bdr_;
{
	int mode_;

	if(sys1833!='M' && sys1833!='O') return NO;
	if(sys1833=='M' && mededelin[0]=='\0') return NO;
	if(sys1833=='O' && opm_bkh[0][0]=='\0') return NO;
	fasinit(4);*u(4,5)=*u(1,1); mode_=1;
	FOREVER{
		next4:;
		if(faskeyi(4,4,mode_)) break; mode_=2;
		if(*u(4,5)!=*u(1,1)) break;
		if(*s(4,2)!=journl) goto next4;
		if(chk_bdr_ && !is_nul(*d(4,32)+bedrag[0])) goto next4; // 
		if(*u(4,4)<(bkh_dt-60) || *u(4,4)>(bkh_dt+60)) goto next4;
		if(sys1833=='M' && cmpstrU(s(4,27),mededelin,15)==0) return YES;
		if(sys1833=='O' && cmpstrU(s(4,28),opm_bkh[0],20)==0) return YES;
	}
	return NO;
}

static upd_fact()
{
  int16 k,curs=1,key,z,mm,dd,sel_journl_;
  char type_;
	fasunlck(-1);				
  type_='A';
  jddate(*u(25,2),&jaartal,&mm,&dd);
  bkh_dt=0;volgnr=0;sel_journl_=0;
					
  FOREVER{
    redo:;
    scrnum=0;scrget(1,220); z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_uAV,&type_);
    scrifld(z++,fm_uu5,&volgnr);
    scrifld(z++,fm_udat,&bkh_dt);
    scrifld(z++,fm_uu2,&sel_journl_);
    scrifld(z++,fm_uu4,&jaartal);
    key=scrupd(curs,0x281); curs=3;
    if(key==101) break;
    if(type_=='A'){
      aard=1;
      for(k=0;k<80;k++){
	if(j_tab[k].typ==tb_typ[aard] && (sel_journl_==0 || j_tab[k].nr==sel_journl_))break;
      }
      if(k==80){curs=5;errnum=4;goto redo;}
      journl=j_tab[k].nr;
    }
    else{
      aard=3;
      for(k=0;k<80;k++){
	if(j_tab[k].typ==tb_typ[aard] && (sel_journl_==0 || j_tab[k].nr==sel_journl_))break;
      }
      if(k==80){curs=5;errnum=4;goto redo;}
      journl=j_tab[k].nr;
    }
    if(volgnr==0 && key!=110) {errnum=38;goto redo;}
    if(get_fact()) goto redo;
    factr();
    volgnr=0;bkh_dt=0;sel_journl_=0;
  }
  endsr:;
}
 
static get_fact()
{
  int16 g,k,mm,dd,mode_,jaari,pft_;
  flag det_used_;

  zero((char *)&grb_tb[0],sizeof grb_tb);
  zero((char *)&rec_nr[0],sizeof rec_nr);
  if(aard<3){
    if(df_recnr[0]==0 || df_recnr[4]==0) {errnum=16;return NO;}
    stutyp=1;
    grb_tb[0]=levcent;
    grb_tb[1]=df_grb[0];
    rec_nr[1]=df_recnr[0];
    grb_tb[2]=df_grb[4];
    rec_nr[2]=df_recnr[4];
  }
  else{
    if(df_recnr[1]==0) {errnum=16;return NO;}
    stutyp=2;
    grb_tb[0]=kltcent;
    grb_tb[1]=df_grb[1];
    rec_nr[1]=df_recnr[1];
  }

  zero((char *)btw_pct,sizeof btw_pct);
  zero((char *)btw_vak,sizeof btw_vak);
	if(CheckForFreeSpace(4,MINFREE)) return NO;/* onvoldoende vrije records */
  fasinit(stutyp);
  mededelin[0]='\0';det_used_=NO;
  ft_dat=0;ft_verv=0;disc_bd=0;di_verv=0;
  copy(def_munt,munt,4);
  zero((char *)bedrag,sizeof bedrag);
  zero((char *)nm_upd,sizeof nm_upd);zero((char *)nm_old,sizeof nm_old);
  zero((char *)opm_bkh,sizeof opm_bkh);
  zero((char *)a_rec_nr,sizeof a_rec_nr);
  zero((char *)a_bedrag,sizeof a_bedrag);
  zero((char *)anal_ask,sizeof anal_ask);
  zero((char *)a_grbrek,sizeof a_grbrek);
  zero((char *)anal_nm,sizeof anal_nm);
  zero((char *)anal_onm,sizeof anal_onm);
  zero((char *)subnr,sizeof subnr);
  zero((char *)intras,sizeof intras);
  zero((char *)&tb_ofact[0],sizeof tb_ofact); pft_=0;
  fasinit(4);*s(4,2)=journl;*u(4,3)=volgnr; mode_=1;
  FOREVER{
    next4:;
    if(faskeyi(4,1,mode_)) break; mode_=2;
    if(*s(4,2)!=journl || *u(4,3)!=volgnr) break;
    if(bkh_dt==0){
      jddate(*u(4,4),&jaari,&mm,&dd);
      if(jaari!=jaartal) goto next4;
      if(*u(4,4)<=last_arc){errnum=37;goto next4;}
			if(*u(4,4)<=MinBkhDatum){errnum=37;goto next4;}
      bkh_dt=*u(4,4);
    }
    else if(bkh_dt!=*u(4,4)) goto next4;
    det_used_=YES;

    if(analyt){
      *l(3,2)=*l(4,6);
      if(g_anal_tst()){
	for(g=0;g<FACTEL-4;g++){
	  if(*l(4,11)==grb_tb[g+4] || grb_tb[g+4]==0) break;
	}
	if(g<FACTEL-4){
	  grb_tb[g+4]=*l(4,11);
	  for(k=0;k<DIMA;k++) if(is_nul(a_bedrag[g][k])) break;
	  if(k<DIMA){
	    a_rec_nr[g][k]=*u(4,5);
	    a_grbrek[g][k]=*l(4,6);
	    a_bedrag[g][k]=*d(4,32);
	    fasinit(3); *l(3,2)=*l(4,6);faskeyi(3,1,0);
	    makename(anal_nm[g]);
	  }
	} else errnum=73;
	tb_ofact[pft_++]=val4_1();
	goto next4;
      }
    }
    for(g=0;g<FACTEL;g++){
      if(((g>=4 && grb_tb[g]==0) || grb_tb[g]==*l(4,6)) && is_nul(bedrag[g])) break;
    }
    if(g<FACTEL){
      if(g>0 && *l(4,6)==grb_tb[0]) {errnum=63;return YES;}/* dubbele factuur */
      if(g==0){
	fasinit(stutyp);*u(stutyp,1)=*u(4,5)-(stutyp-1)*30000;fasgeti(stutyp);
	ft_dat=*u(4,20);
	ft_verv=*u(4,21);
	di_verv=*u(4,22);
	copy(s(4,27),mededelin,15);
	disc_bd=valu_cnv("EUR",munt,*d(4,34),(double)0.01);
      }
      else{
	fasinit(3); *l(3,2)=*l(4,6);faskeyi(3,1,0);
	grb_tb[g]=*l(3,2);
	rec_nr[g]=*u(3,1)+60000;
	revmakename(nm_upd[g]);
      }
      bedrag[g]=*d(4,32);
      copy(s(4,28),opm_bkh[g],20);
      if(fldlen(4,48)){
	if(g>=4){
	  intras[g-4].stelsel=*i(4,48);
	  copy(s(4,49),intras[g-4].staat1,2);
	  intras[g-4].vervoer=*i(4,51);
	  intras[g-4].transakt=*i(4,53);
		if(fldlen(4,57)) copy(s(4,57),intras[g-4].staat_ori,2);
	  copy(s(4,54),intras[g-4].goedercod,8);
	  intras[g-4].gewicht=*d(4,55);
	  intras[g-4].aanveenh=*d(4,56);
	}
      }
    }
    else {errnum=63;return YES;}
    tb_ofact[pft_++]=val4_1();
  }
  bedrag[0]=-bedrag[0];
  bedrag[3]=-bedrag[3];
  if(aard==2 || aard==3){
    for(g=0;g<FACTEL;g++){bedrag[g]=-bedrag[g];}
    for(g=0;g<FACTEL-4;g++)for(k=0;k<DIMA;k++)a_bedrag[g][k]=-a_bedrag[g][k];
  }
  oft_dt=bkh_dt; oft_jn=journl;oft_nr=volgnr;
  if(det_used_) return NO;
  else {errnum=39;return YES;}
}
 
static revmakename(pd)
char *pd;
{
  int16 g,h;

  grb_deco(pd,l(3,2));
  h=0;for(g=0;g<8;g++){
    if(*pd=='\0' || h){h=1;*pd=' ';}
    pd++;
  }
  *(pd++)=' ';
  g=fldlen(3,3);if(g>MAXLEN-1-8) g=MAXLEN-1-8;
  copy(s(3,3),pd,g);
}

static makename(pd)
char *pd;
{
  int16 g,h;
  char *ps;
  g=fldlen(3,3);if(g>MAXLEN-1)g=MAXLEN-1;
  h=MAXLEN-1;
  ps=s(3,3);
  while(g--){
    if(*ps==0)break;
    *pd++=*ps++;
    h--;
  }
  while(h--){
    *pd++=' ';
  }
  *pd='\0';
  pd=pd-8;
  grb_deco(pd,l(3,2));
}

static boek()
{
  int16 g,j,k,ref_yy,dum1,dum2;
  char valtype_;
  long bd_bef,grbveld;
  double tot_eur,tot_vm,bd_eur,bd_vm,bd_;

	fasunlck(-2);
  tot_eur=0;tot_vm=0;
  if(cmpstr(munt,"EUR",3)==0) valtype_='E';
  else if(cmpstr(munt,def_munt,3)==0) valtype_='F';
  else valtype_='V';
  for(g=0;g<FACTEL;g++){
    if(bedrag[g] || g==0){/* 0=klt/lev boeking altijd boeken */
      bd_bef=valu_cnv(munt,def_munt,bedrag[g],(double)1.);
      bd_eur=valu_cnv(munt,"EUR",bedrag[g],(double)0.01);
      if(valtype_=='V') bd_vm=valu_cnv(munt,def_munt,bedrag[g],(double)1.);
      else bd_vm=0;
      tot_eur+=bd_eur;tot_vm+=bd_vm;
      initrec(4);
      *u(4,5)=rec_nr[g];
      if(rec_nr[g]<30000) grbveld=levcent;
      else if(rec_nr[g]<60000) grbveld=kltcent;
      else grbveld=grb_tb[g];
      *l(4,6)=grbveld;
      *l(4,7)=bd_bef; *d(4,32)=bd_eur;
      if(valtype_=='E') *s(4,31)='E'; else *s(4,31)='F';
      if(rec_nr[g]<60000){
				jddate(bkh_dt,&ref_yy,&dum1,&dum2);
				*s(4,8)=ref_yy%100; if(*s(4,8)<50) *s(4,8)+=100;/* y2000 */
				*s(4,9)=journl;
				*u(4,10)=volgnr;
				if(fldlen(4,13)){
					*l(4,13)=0; *d(4,33)=0; bd_=0;
					for(j=1;j<FACTEL;j++){
						for(k=0;k<4;k++) if(grb_tb[j]==btws[k]) break;
						if(k==4) bd_-=bedrag[j];
					}
					*l(4,13)=valu_cnv(munt,def_munt,bd_,(double)1.);
					*d(4,33)=valu_cnv(munt,"EUR",bd_,(double)0.01);
				}
      }
      if(fldlen(4,19)){
				if(subnr[g]==0) subnr[g]=0x80000000;
				*l(4,19)=subnr[g];
      }
      if(g==0){
				*u(4,20)=ft_dat;
				*u(4,21)=ft_verv;
				*u(4,22)=di_verv;
				copy(mededelin,s(4,27),15);
				if(sys1894 && mededelin[0]=='\0') copy(opm_bkh[0],s(4,27),15);
				copy(munt,s(4,24),3);
				*d(4,25)=bedrag[0];
				*f(4,26)=disc_bd;
				*d(4,34)=valu_cnv(munt,"EUR",disc_bd,(double)0.01);
				if(fldlen(4,15) && valtype_=='V'){
					copy(munt,s(4,15),3);
					*d(4,16)=bedrag[0];
					*f(4,17)=disc_bd;
				}
      }
      copy(opm_bkh[g],s(4,28),20);
      if(fldlen(4,48)){
				if(g>=4){
					*i(4,48)=intras[g-4].stelsel;
					copy(intras[g-4].staat1,s(4,49),2);
					*i(4,51)=intras[g-4].vervoer;
					*i(4,53)=intras[g-4].transakt;
					if(fldlen(4,57)) copy(intras[g-4].staat_ori,s(4,57),2);
					copy(intras[g-4].goedercod,s(4,54),8);
					*d(4,55)=intras[g-4].gewicht;
					*d(4,56)=intras[g-4].aanveenh;
				}
      }
			if(fldlen(4,60)) *u(4,60)=procid;
      errnum=fasadd(4);
    }
  }
  if(!is_nul(tot_eur)){/* omrekeningsverschillen BEF- EUR wegboeken */
    initrec(4);
    if(aard<3){*u(4,5)=rec_d_ak; *l(4,6)=grb_d_ak;}
    else {*u(4,5)=rec_d_vk; *l(4,6)=grb_d_vk;}
    *l(4,7)=-tot_eur; *d(4,32)=-tot_eur;
    if(valtype_=='E') *s(4,31)='E'; else *s(4,31)='F';
		if(fldlen(4,60)) *u(4,60)=procid;
    errnum=fasadd(4);
  }
 
  if(analyt){
    for(g=0;g<FACTEL-4;g++){
      for(k=0;k<DIMA;k++){
	if(a_bedrag[g][k]){
	  initrec(4);
	  *u(4,5)=a_rec_nr[g][k];
	  *l(4,6)=a_grbrek[g][k];
	  *l(4,7)=valu_cnv(munt,def_munt,a_bedrag[g][k],(double)1.);
	  *d(4,32)=valu_cnv(munt,"EUR",a_bedrag[g][k],(double)0.01);
	  if(valtype_=='E') *s(4,31)='E'; else *s(4,31)='F';
	  *l(4,11)=grb_tb[g+4];
		if(fldlen(4,60)) *u(4,60)=procid;
	  errnum=fasadd(4);
	}
      }
    }
  }
  fasflush(0);fasunlck(-1);
}

static intrastat()
{
  int16 curs=1,k,g,key,z,d_off_=0,used_;

  for(k=0;k<sizeof intras/sizeof intras[0];k++){
    if(intras[k].stelsel==0) intras[k].stelsel=29;
    if(stutyp==1) intras[k].stelsel=19;
    z=35;if(stutyp==2) z=74;
    if(fldlen(stutyp,z)){
      if(intras[k].staat1[0]=='\0') copy(s(stutyp,z),intras[k].staat1,2);
      if(intras[k].vervoer==0) intras[k].vervoer=*i(stutyp,z+1);
      if(intras[k].transakt==0) intras[k].transakt=*i(stutyp,z+3);
			if(intras[k].staat_ori[0]=='\0') copy("BE",intras[k].staat_ori,2);
    }
    if(intras[k].goedercod[0]=='\0'){
      fasinit(3);*u(3,1)=rec_nr[k+4]-60000;fasgeti(3);
      copy(s(3,14),intras[k].goedercod,8);
    }
  }
  d_off_=0;
  FOREVER{
    scrnum=0;scrget(1,107);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_ou5,&volgnr);
    scrifld(z++,fm_odat,&bkh_dt);
    z+=5;
    scrofld(z++,stutyp,3,-1);
    z+=2;
    g=d_off_+1;scrifld(z++,fm_ou2,&g);
    g=d_off_+10; scrifld(z++,fm_ou2,&g);
    if(aard<3) scrifld(z++,fm_os5,"Herk.");
    else scrifld(z++,fm_os5,"Best.");
		used_=NO;
    for(k=0+d_off_;k<10+d_off_;k++){
      if(bedrag[k+4]){
				scrifld(z++,fm_od8_2,&bedrag[k+4]);
				scrifld(z++,fm_uu2,&intras[k].stelsel);
				scrifld(z++,fm_us2_U,intras[k].staat1);
				scrifld(z++,fm_uu1,&intras[k].vervoer);
				scrifld(z++,fm_uu2,&intras[k].transakt);
				if(aard>=3 && fldlen(4,57)) scrifld(z++,fm_us2_U,intras[k].staat_ori); else z++; 
				scrifld(z++,fm_us8,intras[k].goedercod);
				scrifld(z++,fm_ud6s2,&intras[k].gewicht);
				scrifld(z++,fm_ud6s2,&intras[k].aanveenh);
				used_=YES;
      }
    }
		if(used_) curs=1; else curs=-1;
    key=scrupd(curs,0x088);
    if(key==104){if(d_off_==10) d_off_=0; else d_off_=10;}
    if(key==108) break;
  }
}

static initrec(stu_)
int16 stu_;
{
  fasinit(stu_);
  *s(stu_,2)=journl;
  *u(stu_,3)=volgnr;
  *u(stu_,4)=bkh_dt;
}

static initload()
{
  int16 k;

  fasunlck(0);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  fileopen(1);
  fileopen(2);
  for(k=3;k<=5;k++) fileopen(k);
  fileopen(14);
	zero((char *)tb_grbnotfound,sizeof tb_grbnotfound);notfound=0;
  for(k=0;k<80;k++) sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
  for(k=0;k<15;k++){
    sysget(788+k*4,4,&df_grb[k]);
    df_recnr[k]=getgrb(df_grb[k]);
  }

  chk_btoeg=NO;
  sysget( 780,4,&levcent);getgrb(levcent);
  sysget( 784,4,&kltcent);getgrb(kltcent);
  sysget(1201,4,&grb_d_ak);
  if(grb_d_ak==0 || grb_d_ak==-1) {errnum=16; ovlexit(-1);}
  rec_d_ak=getgrb(grb_d_ak);
  sysget(1205,4,&grb_d_vk);
  if(grb_d_vk==0 || grb_d_vk==-1) {errnum=16; ovlexit(-1);}
  rec_d_vk=getgrb(grb_d_vk);

  chk_btoeg=YES;
 
  if(notfound){
		errnum=2;
		scrnum=0;scrget(1,170);
		for(k=0;k<notfound && k<15;k++) scrifld(k+1,fm_ogrb,&tb_grbnotfound[k]);
		scrifld(18,fm_os63,"      Druk F8 om terug te keren ....");
    scrupd(-1,0x80);
    ovlexit(-1);
  }

  sysget( 294,4,def_munt);
  sysget( 298,2,&vers_298);
/*  sysget( 626,2,&intr_stel); */
  sysget( 788,16,&btws[0]);
  sysget(1008,16,(char *)btwpct);
  sysget(1024,20,&vak_pct[0]);
	sysget(1048,40,&DefBtwPct[0]);
	sysget(1280, 2, &PeppolProviderInkomend);
	sysget(1318,1,&sys1318);
	sysget(1326,40,&GrbPeppol[0]); 
	sysget(1833,1,&sys1833);
  sysget(1850,2,&sys1850);
  sysget(1858,2,&last_arc);
  sysget(1862,2,&sys1862);sys_vm=sys1862&1;
  sysget(1866,2,&mnd_strt);
  sysget(1892,2,&verk_chk);
  sysget(1894,2,&sys1894);
  sysget(1213,4,&maxdifbtw);
  sysget(1896,10,&btwvaknr[0]);
  sysget(1918,2,&sear_stt);
  sysget(2212,4,talen);
  sysget(2222,2,&def_qfak);
  sysget(2300,2,&MinBkhDatum);if(MinBkhDatum<last_arc) MinBkhDatum=last_arc;
  sysget(3770,2,&sys3770);
  sysget(3876,2,&sys3876);
  analyt=fldlen(4,11);
  pu_4_1=u(4,1); pl_4_1=l(4,1); len4_1=fldlen(4,1);
  ram=RamBon;
	CallingOvl=11;
}

static long val4_1()
{
  if(len4_1==4) return *pl_4_1;
  else return (long)(*pu_4_1);
}
				
static chg4_1(value_)
long value_;
{
  if(len4_1==4) *pl_4_1=value_;
  else *pu_4_1=value_;
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

static DisplayMemo(stu_)
int16 stu_;
{
  int16 curs=2,dcurs_;
  int16 z,k,key,ok_;
	int16 only_dsp=YES;
		
	ok_=NO;
	if(stu_==1){
		for(k=0;k<3;k++) if(fldlen(1,125+k) && *s(1,125+k)) break;
		if(k<3) ok_=YES;
	}
	else if(stu_==2){
		if(fldlen(62,1)){
			fasinit(62);*u(62,2)=*u(2,1);
			if(faskeyi(62,1,0)==0){
				for(k=0;k<5;k++) if(*s(62,5+k)) break;
				if(k<5) ok_=YES;
			} 
		}
  }
	if(ok_==NO) goto endsr;

  FOREVER{
    redo:;
    scrnum=0;scrget(2,122); z=1;
    scrofld(z++,stu_,3,-1);
		if(stu_==1){
			for(k=125;k<128;k++) scrfld(z++,1,k);
		}
		else{
      for(k=5;k<10;k++) scrfld(z++,62,k);
		}
    dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0x80);
    if(key==15 && only_dsp){only_dsp=NO;goto redo;}
    if(key==108) break;
  }
	if(stu_==1) fasupd(1); 
	else if(stu_==2) fasupd(62);
	endsr:;
}


static uint16 getgrb(lgrb)
long lgrb;
{
  uint16 retcd=0;

  if(*(char *)&lgrb!=0xFF && *(char *)&lgrb!=0x00 && scrcount<23){
    *l(3,2)=lgrb;
    *u(3,1)=0;
    search(3,2);
    if(errnum) tb_grbnotfound[notfound++]=lgrb;
    else{
      retcd=*u(3,1)+60000;
    }
  }
  return retcd;
}
 
static scr_bd(fld_,elem_)
int16 fld_,elem_;
{
  scrifld(fld_,fm_ud8_2,&bedrag[elem_]);
}

static flag yet_booked(jrnl_,volgnr_,dt_)
int16 jrnl_;
uint16 volgnr_,dt_;
{
  int16 fkey_,jj,mm,dum;
  uint16 dt_beg,dt_end;

  if(sys1862 & 0x10) return NO;
  jddate(dt_,&jj,&mm,&dum);
  FOREVER{
    dt_end=datejd(++jj,mnd_strt,1);
    dt_beg=datejd(--jj,mnd_strt,1);
    if(dt_>=dt_beg) break;
    jj--;
  }
  fasinit(4);*s(4,2)=jrnl_;*u(4,3)=volgnr_;fkey_=1;
  FOREVER{
    next:;
    if(faskeyi(4,1,fkey_)) break;fkey_=2;
    if(*s(4,2)!=jrnl_ || *u(4,3)!=volgnr_) break;
    if(upd_mode){/* originele boeking overslaan */
      if(*s(4,2)==oft_jn && *u(4,3)==oft_nr && *u(4,4)==oft_dt) goto next;
    }
 
    if(*u(4,4)>=dt_beg && *u(4,4)<dt_end) return YES;
  }
  return NO;
}

static anal_det(nr_)
int16 nr_;
{
  int16 k,z,key,nx,curs=1;
  double bd_;

  nx=nr_-4;
  zero((char *)anal_pct,sizeof anal_pct);
  zero((char *)anal_onm,sizeof anal_onm);
  if(fldlen(3,33)){/* 1-ste keer default percentages zetten */
    fasinit(3);*u(3,1)=rec_nr[nr_]-60000;fasgeti(3);
    for(k=0;k<DIMA;k++){
      if(a_grbrek[nx][k] && a_rec_nr[nx][k]==0) anal_pct[k]=*f(3,32+k*2);
    }
    for(k=0;k<DIMA;k++){
      if(a_grbrek[nx][k] && a_rec_nr[nx][k]==0){
	fasinit(3);*l(3,2)=a_grbrek[nx][k];faskeyi(3,1,0);
	if(faskeyi(3,1,0)==0) a_rec_nr[nx][k]=*u(3,1)+60000;
      }
    }
  }

  for(k=0;k<DIMA;k++){
    if(a_rec_nr[nx][k]){
      fasinit(3);*u(3,1)=a_rec_nr[nx][k]-60000;fasgeti(3);
      makename(anal_nm[k]);
    }
    else anal_nm[k][0]='\0';
		copy(anal_nm[k],anal_onm[k],sizeof anal_nm[0]);
  }
  FOREVER{
    redo:
    scrnum=0;scrget(1,44);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_ou2,&journl);
    scrifld(z++,fm_ou5,&volgnr);
    scrifld(z++,fm_odat,&bkh_dt);
    scrifld(z++,fm_os30,nm_upd[nr_]);
    scrifld(z++,fm_od8_2,&bedrag[nr_]);
    for(k=0;k<DIMA;k++){
      scrifld(z++,fm_ud8_2,&a_bedrag[nx][k]);
      scrifld(z++,fm_uf3_2,&anal_pct[k]);
      scrifld(z++,fm_us30,anal_nm[k]);
    }
    key=scrupd(curs,0x4C1);curs=1;
    if(key==111) ovlexit(-1);
/* bedragen */
    for(k=0;k<DIMA;k++){
      if(is_nul(a_bedrag[nx][k])){
	a_bedrag[nx][k]=valu_cnv(munt,munt,(double)(bedrag[nr_]*anal_pct[k]/100.),mst_afrond);
      }
    }
    bd_=0;
    for(k=0;k<DIMA;k++){
      bd_+=a_bedrag[nx][k];
    }
    if(absdoubl(bd_)>absdoubl(bedrag[nr_])){errnum=67;goto redo;}
    if(sys1850){
      if(absdoubl(bd_)<absdoubl(bedrag[nr_])){errnum=70;goto redo;}
    }
/* controle grb rekeningnamen */
    for(k=0;k<DIMA;k++){
      if(a_bedrag[nx][k] && anal_nm[k][0]=='\0'){
				errnum=38;curs=9+k*3;goto redo;
      }
      if(cmpstr(anal_onm[k],anal_nm[k],MAXLEN)){
				if(anal_nm[k][0]!='\0'){
					copy(anal_nm[k],s(3,3),fldlen(3,3));
					if(search(3,0) && errnum==0)errnum=39;
					if(errnum){curs=9+k*3;goto redo;}
					makename(anal_nm[k]);
					if(((*s(3,2) &0xF0)>>4)!=9) {errnum=68;curs=9+k*3;goto redo;}
					a_grbrek[nx][k]=*l(3,2);
					a_rec_nr[nx][k]=*u(3,1)+60000;
				}
				copy(anal_nm[k],anal_onm[k],MAXLEN);
      }
    }
    if(key==101 || key==108) break;
  }
	for(k=0;k<DIMA;k++) if(a_bedrag[nx][k]) break;
	if(k<DIMA) anal_ask[nr_]='X'; else anal_ask[nr_]='\0';
}

static double absdoubl(bd_)
double bd_;
{
  bd_=valu_cnv("EUR","EUR",bd_,mst_afrond);
  if(bd_>=0) return bd_;
  else return -bd_;
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static g_anal_tst()
{
  if(!analyt || ((*s(3,2) &0xF0)>>4)!=9) return NO;
  return YES;
}

static cmpstrU(p1,p2,len)
char *p1,*p2;
int16 len;
{
  char b1,b2;
					
  while(len--){
    b1=*p1++;b2=*p2++;
		if(b1==0 && b2==0) break; // stoppen op 0
    if(b1>='a' && b1<='z') b1=b1-'a'+'A';
    if(b2>='a' && b2<='z') b2=b2-'a'+'A';
    if(b1!=b2)return 1;
  }
  return 0;
}
 
static upd_sta()
{
  int16 dd,mm,jj,k;
  double bedr_=0;

  jddate(bkh_dt,&jj,&mm,&dd);
/*  if(sys3770==jj || (sys3770-1)==jj){ */
  for(k=4;k<FACTEL;k++) bedr_+=bedrag[k];
  if(aard==2 || aard==3) bedr_=-bedr_;
  bedr_=valu_cnv(munt,"EUR",bedr_,(double)0.01);
  fasinit(60);
  if(rec_nr[0]>30000){*l(60,2)=rec_nr[0]-30000;k=1;}
  else{*l(60,12)=rec_nr[0];k=2;}
  if(fldlen(60,22)) *l(60,22)=1;
  faskeyu(60,k,0);
  if(sys3770==jj) *f(60,82-1+mm)+=bedr_;
  else *f(60,94-1+mm)+=bedr_;
  if(*u(60,1)) fasupd(60); else fasadd(60);
/* else errnum=81; */
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

static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
}

static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
	if(stu_<=3) parmcall[1]=7;/*  bits : 0 = display, 1=update, 2=add */
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
  parmcall[7]=0x0C; // enkel boeken toegestaan
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}

