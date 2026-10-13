/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0220GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0220dat
#define ovlcod DRK0220cod
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
 
char ovldat[] = "drk0220  00:21 30/07/10 (c) Jamadata";
		// FLAGCOC : jaartotalen klt-fiche verschuiven bij op 0 zetten 

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_REC         15000

#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_RDWR         0x0002  /* open for reading and writing */
#define O_APPEND       0x0008  /* writes done at eof */
#define O_CREAT        0x0100  /* create and open file */
#define O_TRUNC        0x0200  /* open and truncate */
#define O_EXCL         0x0400  /* open only if file doesn't already exist */
#define O_TEXT         0x4000  /* file mode is text (translated) */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */

#define ARTCODE_LEN     5  // controleer steeds met kassa !!!!
#define WRK_BONHDR_LEN  329
#define STUKS           1

extern char *s();
extern int16 *i();
extern uint16 *u();
static uint16 hash();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();


static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os59[]  = {7,0x88,59,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os36[]  = {7,0x88,36,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us6[]   = {7,0xC8,6,0,0,0,0};
static char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_uf4_2[] = {6,0xD4,4,2,0x70,0};
static char fm_uf4_3[] = {6,0xD4,4,3,0x70,0};
static char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static char fm_of5_0[] = {6,0x94,5,0,0x70,0};
static char fm_stock[] = {6,0xD4,6,0,0x70,0};/* uf6_0 */
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x20,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uOA[]   = {11,0xC8,1,0,1,0,'O','O','A','A',0};
static char fm_uOV[]   = {11,0xC8,1,0,1,0,'O','O','V','V',0};
static char fm_u_AKP[]  = {13,0xC8,1,0,1,0,'A','A','K','K','P','P',0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

extern int16 ilength;
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol,prt2xls;
static int16 *pi;

static uint16 dt_kvk[20],loc_klt[20],loc_nr[20],inq_loc;
static char fl_ak,fl_vk,sta_0,akf_0,his_0,kvk_0;
static char nm_kassa[20][6],nm_loc[10][6];
					
static char ram[10000],buf600[600],add_leeg,nm_fil[6],oldnm[50],filnam[100];
static int16 dat_len,ram_recl,hash_len;
static int16 len2_3;
static uint16 hash_val;

static int16 start,p_max_grp;
static char art_nm[50],lev_res[50],werkveld[30],manier='A',st_per_art='N';
static uint16 inq_groep=0,inq_lev,inq_art,sort_key,mnd_beg,mnd_end,add_year,bon_beg,bon_end;
static uint16 *pu_6_1;

static int16 free,groep_i=0,arcd,wrk_size,inq_kassa;
static uint16 dat_st_0;
static char ak_vk_0[4],fmt[40],fr_gw_0[4],omz_0[2],add_fstk,AlleenMetStock,AddWrkBon2Loc;
static flag lvcd,klcd,chk_btoeg=NO,sgrp_used,slev_used;
static flag sear_stt,sys3876,sys3766,omzet,barc_used,sys4408,sys2696;
static int16 def_taal;
static int16 kdsp,kdsp_off=1;
static long rec_working;
static char disp_str[55];

/* de seqo-variabelen */
				
static char seqo_str[1000];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;


static struct{
  uint16 rec;
} tb[DIM_REC];

static struct{
  uint16 rec;
  char select;
} tbgr[100];
			
static struct{
  float stock[2];
  float ostock[2];
} tb_val[20];

//static struct s_lijn{   // als we hier iets aan wijzigen, ook aanpassen in OVL290 
//                 // is ook belangrijk bij adden in kaslog.dat (truuk voor textlijn)
//  char text[41];							// ingevuld zo groep >= 9900, bv. GRP_TEXT of GRP_TIJD
//  unsigned char bits;					// & STUKS om te weten of het stuksflag is of niet 
//  char code[ARTCODE_LEN];	
//  float aantal;
//  short groep;
//  float btw;
//  float prijs;
//  double totaal;
//} p_lin;


	struct s_lijn{   // als we hier iets aan wijzigen, ook aanpassen in OVL290 
									 // is ook belangrijk bij adden in kaslog.dat (truuk voor textlijn)
		char text[41];							// ingevuld zo groep >= 9900, bv. GRP_TEXT of GRP_TIJD
		unsigned char bits;					// & STUKS om te weten of het stuksflag is of niet 
		char code[ARTCODE_LEN];	
		float aantal;
		short groep;
		float btw;
		float prijs;
		double totaal;
		char  EindeReclenKaslog; // vanaf hier UITKIJKEN met wegschrijven in kaslog/WRK-bons owv ovl0290 en compatibiliteit !!!!
		short fl_promoLijn;
		int PromoFormule;
		int  MaxPromoPerTicket;
		long PromoGroepsCode;
		float PromoBasisAantal;
		char  EindeWRKReclen; // tot hier wordt uitgeschreven in WRK-bons, kijk uit dat hier geen vitale velden staan!!!!
		float PromoAantalUsed;
	} p_lin;

static float get_num();
static char *p_data,*rec_ele();
static long *pl_80_1;

ovlcod()
{
  int16 key;
  char choice;

  initload();
  FOREVER{
		redo:;
    scrget(3,12);fasunlck(0);
		if(fldlen(91,1) || fldlen(66,1)) scraddpicto(1,0,76,22,4,2,59,0,4,"Parameters"); 
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
  	if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==5001) {upd_loc();goto redo;} // parameters
    if(key==101||key==111) break;
		fasunlck(-1);
    switch(choice){
			case '1': if(AllowMasterFunctions) PrepareForNewYear(); else errnum=50;break;
      case '2': if(fldlen(6,33)) MenuInventaris();else errnum=12; break;
      case 'M': if(ovltest(297)) ovlexit(297); else errnum=12; break;
      case 'U': corr_bstock(); break;
      case 'W': zero_stat();break;
      default : errnum=34;break;
    }
  }
  ovlexit(-1);
}

static MenuInventaris()
{
  int16 key;
  char choice;

  initload();
  FOREVER{
redo:;
#if FLAGSHN
		scrget(3,117); 
#else
    scrget(3,17);
#endif		
		fasunlck(0);
		if(ovltest(297)) scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0220C");
		else scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0220B");

#if FLAGGRS
    scraddf(118,17,3,0);
    scrifld(118,fm_os79,"Toevoegen stockopnames van TAB-gescheiden TXT-bestand (XLS) ..... : E ");
#endif
#if FLAGDKR
    scraddf(118,17,3,0);
    scrifld(118,fm_os79,"Vervangen \"Actuele stock\" door \"Stock van stocklocatie\" ......... : V ");
#endif
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101||key==111) break;
		fasunlck(-1);
    switch(choice){
      case '1': zero_stock(0); break;
			case '2': if(ovltest(290)) AddStockFromWrkFilesKassa(); else errnum=12; break;
      case '3': if(ovltest(297)) ovlcall(297,1); else errnum=12; break;
      case '4': stock_input(0); break;
      case '5': kop_inv();break;
      case '6': if(ovltest(267)) ovlcall(267,1); break;
      case 'C': stock_input(1); break;
      case 'T': if(ovltest(267)) ovlcall(267,2); break;
#if FLAGDKR
      case 'V': ReplaceStockByStockLocatie(); break;
#endif
#if FLAGGRS || FLAGCRA
      case 'E': AddStockFromXls(); break;
#endif
#if FLAGSHN
      case 'E': ExportArtikels2Txt(); break;
      case 'V': AddStockFromTxt(); break;
#endif
      default : errnum=34;break;
    }
  }
}

static PrepareForNewYear()
{
  int16 j,k,key,z,yy,mm,dd,curs=1;
  char WisFactuurNr='N',WisBonNr='N',WisAlleOmzet='J',MaakInterneKopie='J',MaakBackup='J';
  uint16 nr_,mnd_strt;
	char NewCode[4],NewName[31],str_[20];

	dat_st_0=*u(25,2);
	zero(NewCode,sizeof NewCode);zero(NewName,sizeof NewName);
	jddate(*u(25,2),&yy,&mm,&dd); 
	k=(yy%100)-1;NewCode[0]=*s(25,3);stcli_d(&NewCode[1],(long)(k),2,0);
	copy(s(25,1),NewName,30);
	j=0;for(k=0;k<23;k++){ if(NewName[k]=='\0' || j){ NewName[k]=' ';j=1;}}
  copy(" (",&NewName[k],2);k+=2;stcli_d(&NewName[k],(long)(yy-1),4,0);k+=4;NewName[k]=')';
	sysget(1866,2,&mnd_strt);if(mm==mnd_strt){WisFactuurNr='J';WisBonNr='J';}// begin nieuw boekjaar

  FOREVER{
		redo:;
    scrget(3,18);z=1;
		scraddpicto(1,0,65,3,12,6,605,0,0,"Opgelet!"); 
		scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0220A");
		scrifld(z++,fm_uJN,&MaakBackup);
		scrifld(z++,fm_uJN,&MaakInterneKopie);
		scrofld(z++,25,3,-1); scrofld(z++,25,1,-1);
		scrifld(z++,fm_us3U,NewCode);scrifld(z++,fm_us30,NewName);
		scrifld(z++,fm_uJN,&WisAlleOmzet);
    scrifld(z++,fm_uJN,&WisFactuurNr);
    scrifld(z++,fm_uJN,&WisBonNr);
    key=scrupd(curs,0x9);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101 || key==105) goto endsr;
		if(MaakInterneKopie=='J'){
			for(k=0;k<3;k++) if(NewCode[k]=='\0') break;
			if(k<3){curs=4;errnum=34;goto redo;}
			j=copy0("..\\FAS\\SYS.",str_,15);copy(NewCode,&str_[j],4);
			if(FileExist(str_)){curs=4;errnum=31;goto redo;}
		}
    if(key==104) break;
	}

	if(MaakBackup=='J' || MaakInterneKopie=='J'){ // systeem stoppen
  	if(ovlcall(2,2)==0){
  		DisplayWarning("Kan systeem niet stoppen, probeer later opnieuw!",605,0); goto endsr;
	  }
	}

	if(MaakBackup=='J'){
		if(!MakeFullExternalBackup(YES,NO)){
			ovlcall(2,3); // DB heropstarten en posten vrijmaken 
      goto endsr;
	  }
	}

	if(MaakInterneKopie=='J'){
		zero(str_,sizeof str_);copy(s(25,3),str_,3);// om viezigheid hierachter weg te doen
  	if(ExecCopyDossier(str_,NewCode,NewName,2,NO)==NO){
  		DisplayWarning("Het aanmaken van de kopie is mislukt! Gelieve opnieuw te proberen.",605,0);
			ovlcall(2,3); // DB heropstarten en posten vrijmaken 
      goto endsr;
	  }
	}

	if(MaakBackup=='J' || MaakInterneKopie=='J') ovlcall(2,3); // DB heropstarten en posten vrijmaken 

	if(WisAlleOmzet=='J'){
		for(k=0;k<4;k++){	if(fldlen(6,53+k*2) || fldlen(6,54+k*2)) ak_vk_0[k]='J'; else ak_vk_0[k]='\0';}
		fl_ak='\0';	for(k=0;k<5;k++){if(fldlen(66,14+k*15)) {fl_ak='J';break;}}
		fl_vk='\0';	for(k=0;k<5;k++){if(fldlen(66,17+k*15)) {fl_vk='J';break;}}
		for(k=0;k<4;k++) fr_gw_0[k]='\0';
		if(fldlen(2,57)) fr_gw_0[0]='J'; 
		if(fldlen(2,58)) fr_gw_0[1]='J';
		if(fldlen(2,62)) fr_gw_0[2]='J';
		if(fldlen(2,63)) fr_gw_0[3]='J';
		if(fldlen(9,27)){
		  for(k=0;k<2;k++) omz_0[k]='J'; omzet=YES;
		}
		sta_0='\0';if(fldlen(60,1)) sta_0='J';
		akf_0='\0';if(fldlen(11,100))akf_0='J';
		his_0='\0';if(fldlen(16,1)) his_0='J';
		kvk_0='\0';if(fldlen(91,1)) kvk_0='J';
		wis_stat();
	}
	if(WisBonNr=='J'){nr_=0; sysput(3718,2,&nr_);}
	if(WisFactuurNr=='J'){ // ALLE verkoopjournalen op 0 zetten 
		nr_=0;
		for(k=0;k<80;k++){
			sysget(10242+k*80,2,&j);
			if(j==2) sysput(10260+k*80,2,&nr_);
		}
  }
	if(MaakBackup=='J' && ServerVersion>SERVER_MONO){ // dit scherm echt laten wachten tot ie aangekomen is
		FOREVER{
			_sleep(600);
			if(FileExist(BackupFile2Receive)==NO) break;
			scrnum=0;scrget(1,170);
			scraddfield(1,8,10,0); scrifld(1,VarTextFmt(65,0),"Bezig met klaarzetten backup voor USB-stick. Even geduld aub...");
      scraddfield(2,15,14,0); scrifld(2,VarTextFmt(65,0),"De andere posten/schermen mogen nu verderwerken.");
      scrupd(-3,0);
		}
	}
  endsr:;
}

static zero_stat()
{
  int16 j,k,key,z,g,m,journaal_;
  char wis_fnr_='N',wis_bnr_='N';
  uint16 nr_,pos_;

  j=0;
  for(k=0;k<4;k++){
    ak_vk_0[k]='\0';
    if(fldlen(6,53+k*2) || fldlen(6,54+k*2)) {ak_vk_0[k]='N';j++;}
  }
  fl_ak='\0';
  fl_vk='\0';
  for(k=0;k<5;k++){
    if(fldlen(66,14+k*15)) {fl_ak='N';j++;break;}
  }
  for(k=0;k<5;k++){
    if(fldlen(66,17+k*15)) {fl_vk='N';j++;break;}
  }
  for(k=0;k<4;k++) fr_gw_0[k]='\0';
  if(fldlen(2,57)) {fr_gw_0[0]='N'; j++;}
  if(fldlen(2,58)) {fr_gw_0[1]='N'; j++;}
  if(fldlen(2,62)) {fr_gw_0[2]='N'; j++;}
  if(fldlen(2,63)) {fr_gw_0[3]='N'; j++;}
  for(k=0;k<2;k++) omz_0[k]='N';if(fldlen(9,27)) omzet=YES;
  sta_0='\0';if(fldlen(60,1)) {sta_0='N';j++;}
  akf_0='\0';if(fldlen(11,100)){akf_0='N';j++;}
	his_0='\0';if(fldlen(16,1)) his_0='N';
	kvk_0='\0';if(fldlen(91,1)) kvk_0='N';
  //if(j==0){
  //  errnum=12;goto endsr;
  //}
  FOREVER{
    scrget(3,11);z=1;
    scrfld(z++,25,1);
 
    for(k=0;k<4;k++){
      if(ak_vk_0[k]) scrifld(z++,fm_uJN,&ak_vk_0[k]); else streepje(z++);
      if(k==1){
	if(fl_ak) scrifld(z++,fm_uJN,&fl_ak); else streepje(z++);
      }
      if(k==3){
	if(fl_vk) scrifld(z++,fm_uJN,&fl_vk); else streepje(z++);
      }
    }
    for(k=0;k<2;k++){
      if(fr_gw_0[k]) scrifld(z++,fm_uJN,&fr_gw_0[k]); else streepje(z++);
    }
    if(omzet){
      for(k=0;k<2;k++){
	scrifld(z++,fm_uJN,&omz_0[k]);
      }
    } else {streepje(z++);streepje(z++);}
    if(fldlen(60,1)) scrifld(z++,fm_uJN,&sta_0); else streepje(z++);
    if(fldlen(11,100)) scrifld(z++,fm_uJN,&akf_0); else streepje(z++);
    scrifld(z++,fm_uJN,&wis_fnr_);
    scrifld(z++,fm_uJN,&wis_bnr_);
    key=scrupd(1,0x0419);
    if(key==111) ovlexit(-1);
    if(key==101 || key==105) break;
    if(key==104){
      for(k=0;k<4;k++) if(ak_vk_0[k]=='J') break;
      for(g=0;g<4;g++) if(fr_gw_0[g]=='J') break;
      for(m=0;m<2;m++) if(omz_0[m]=='J') break;
      if(k!=4 || g!=4 || m!=2 || sta_0=='J' || akf_0=='J' || wis_fnr_=='J' || wis_bnr_=='J' || fl_ak=='J' || fl_vk=='J'){
				if(k!=4 || g!=4 || m!=2 || sta_0=='J' || akf_0=='J' || fl_ak=='J' || fl_vk=='J') wis_stat();
				if(wis_bnr_=='J'){
					pos_=3718; nr_=0; sysput(pos_,2,&nr_);
				}
				if(wis_fnr_=='J'){
					sysget(2166,2,&journaal_);
					for(k=0;k<80;k++){
						sysget(10240+k*80,2,&nr_);
						if(nr_==journaal_)break;
					}
					if(k<80){
						pos_=10260+k*80;nr_=0;
						sysput(pos_,2,&nr_);
					}
				}
				break;
      }
    }
    else errnum=21;
  }
  endsr:;
}

static wis_stat()
{
  int16 k,g,dd,mm,yy;
  long a;
  flag art,klt,his, omz;
	uint16 stat_dat[13],dt_end_;
 
  fasunlck(-2);
	scrnum=0;scrget(1,170);
  scrifld(10,fm_os79,"    De gewenste omzetten worden nu op 0 gezet");scrupd(-3,0);
#if FLAGOLH
  his=NO;
  if(ak_vk_0[2]=='J' && fldlen(6,57) && fldlen(6,106)){
    scrifld(13,fm_os79,"    De verkoopsgegevens van de periode worden overgeschreven in tabel");
    his=YES;
    sysget(3714, 2,&stat_dat[12]);
    sysget(3726,24,&stat_dat[ 0]);
    for(k=0; k<12; k++) stat_dat[k]=stat_dat[k+1];
    sysput(3726,24,&stat_dat[ 0]);
  }
#endif
  art=NO;klt=NO;omz=NO;
  for(k=0;k<4;k++){
    if(ak_vk_0[k]=='J') {sysput(3710+k*2,2,&dat_st_0); art=YES;}
  }
  for(k=0;k<4;k++){
    if(fr_gw_0[k]=='J') {sysput(3750+k*2,2,&dat_st_0); klt=YES;}
  }
  for(k=0;k<2;k++){
    if(omz_0[k]=='J') omz=YES;
  }
  if(art){
    a=0;
    FOREVER{
      *u(6,1)=++a; dsp_working();
      g=fasgeti(6);
      if(g==47)break;
      if(g!=46){/* deleted record */
#if FLAGOLH
				if(his){
					for(k=0;k<11;k++){
						*f(6,106+k*4)=*f(6,106+(k+1)*4);
						*f(6,107+k*4)=*f(6,107+(k+1)*4);
						*f(6,108+k*4)=*f(6,108+(k+1)*4);
					}
					*f(6,106+44)=*f(6,57);
					*f(6,108+44)=*f(6,58);
					if(fldlen(6,34)) *f(6,107+44)=*f(6,57) * *f(6,34);
					else if(fldlen(6,18)) *f(6,107+44)=*f(6,57) * *f(6,18);
					else *f(6,107+44)=0;
				}
#endif
				for(k=0;k<4;k++){
					if(ak_vk_0[k]=='J'){
						if(fldlen(6,53+k*2)) *f(6,53+k*2)=0;
						if(fldlen(6,54+k*2)) *f(6,54+k*2)=0;
					}
				}
				fasupd(6);
      }
    }
  }
  if(fl_ak=='J' || fl_vk=='J'){
    a=0;
    FOREVER{
      *u(66,1)=++a; dsp_working();
      g=fasgeti(66);
      if(g==47)break;
      if(g!=46){/* deleted record */
				for(k=0;k<10;k++){
					if(fl_ak=='J') if(fldlen(66,14+k*15)) *f(66,14+k*15)=0;
					if(fl_vk=='J') if(fldlen(66,17+k*15)) *f(66,17+k*15)=0;
				}
				fasupd(66);
      }
    }
  }

  if(klt){
    a=0;
    FOREVER{
      *u(2,1)=++a; dsp_working();
      g=fasgeti(2);
      if(g==47)break;
      if(g!=46){/* deleted record */
				if(fr_gw_0[0]=='J'){
					if(fldlen(2,64)) *f(2,64)=0;
#if FLAGCOC
					for(k=84;k>80;k--) *f(2,k)=*f(2,k-1); 
					*f(2,80)=*f(2,57); 
#endif
					*f(2,57)=0;
				}
				if(fr_gw_0[1]=='J'){
					if(fldlen(2,61)) *f(2,61)=*f(2,58);

					*f(2,58)=0;
				}
				if(fr_gw_0[2]=='J') *f(2,62)=0;
				if(fr_gw_0[3]=='J') *f(2,63)=0;
				fasupd(2);
      }
    }
  }
  if(omz){
    a=0;
    FOREVER{
      if(fldlen(9,1)==4) *l(9,1)=++a; else *u(9,1)=++a;
      g=fasgeti(9); dsp_working();
      if(g==47)break;
      if(g!=46){/* deleted record */
				if(omz_0[0]=='J' && omz_0[1]=='J' && contract()==NO) faskill(9);
				else{
					for(k=0;k<2;k++){
						if(omz_0[k]=='J'){
							for(g=0;g<3;g++){
								if(fldlen(9,27+g+k*4)) *f(9,27+g+k*4)=0;
								if(fldlen(9,35+g+k*4)) *f(9,35+g+k*4)=0;
							}
							for(g=0;g<2;g++){
								if(fldlen(9,47+g+k*4)) *f(9,47+g+k*4)=0;
							}
							for(g=0;g<2;g++){
								if(fldlen(9,55+g+k*4)) *f(9,55+g+k*4)=0;
							}
						}
					}
				}
				fasupd(9);
      }
    }
    fasinfo(9,101);
  }
	if(fldlen(16,1) && his_0=='J'){ // historieken, ouder dan 4 jaar schrappen
	  jddate(*u(25,2),&yy,&mm,&dd); dt_end_=datejd(yy-4,1,1);
    a=0;
    FOREVER{
      *l(16,1)=++a;
      g=fasgeti(16); dsp_working();
      if(g==47)break;
      if(g!=46 && *u(16,3)<dt_end_) faskill(16);
		}
	}
  if(fldlen(91,1) && kvk_0=='J'){ // kasverkopen, ouder dan 4 jaar schrappen
	  jddate(*u(25,2),&yy,&mm,&dd); dt_end_=datejd(yy-4,1,1);
    a=0;
    FOREVER{
      *l(91,1)=++a;
      g=fasgeti(91); dsp_working();
      if(g==47)break;
      if(g!=46 && *u(91,3)<dt_end_) faskill(91);
		}
	}


  if(sta_0=='J') clr_60();
  if(akf_0=='J') clr_11();
  fasflush(0);
  sysflush();
	fasunlck(-1);
}
 
static clr_60()
{
  int16 j=0,k,g;
  uint16 n,kill_rec_;

  mnd_beg=1;mnd_end=12; add_year='J';
  for(k=0;k<7;k++){
    j+=fldlen(60,64+k*30)+fldlen(60,76+k*30);
  }
  if(j==0) goto endsr;

  n=0;fasinit(60);
  scrnum=0;scrget(1,170);
  scrifld(10,fm_os79,"    De statistieken worden gewist ...");
  n=0;kdsp=0;kdsp_off=1;
  FOREVER{
    *u(60,1)=++n;
    dsp_working();
    g=fasgeti(60);
    if(g==47)break;
    if(g!=46){/* deleted record */
      if(add_year=='J'){
	for(j=0;j<7;j++){/* opschuiven jaartotalen */
	  for(k=79;k>=76;k--){
	    if(fldlen(60,j*30+k+1)) *f(60,j*30+k+1)=*f(60,j*30+k);
	  }
	  if(fldlen(60,76+j*30)) *f(60,76+j*30)=0;
	}
      }
      for(j=0;j<7;j++){/* opschuiven maandtotalen en optellen jaartotaal */
	for(k=mnd_beg-1;k<mnd_end;k++){
	  if(fldlen(60,52+j*30+k)){
	    if(add_year=='J'){
	      if(fldlen(60,64+j*30+k)) *f(60,64+j*30+k)=*f(60,52+j*30+k);
	      if(fldlen(60,76+j*30)) *f(60,76+j*30)+=*f(60,52+j*30+k);
	    }
	    *f(60,52+j*30+k)=0;
	  }
	}
      }
      kill_rec_=YES;
      for(j=0;j<7;j++){
	for(k=0;k<12;k++){
	  if(fldlen(60,52+j*30+k)){
	    if(*f(60,52+j*30+k)) kill_rec_=NO;
	    if(fldlen(60,64+j*30+k) && *f(60,64+j*30+k)) kill_rec_=NO;
	  }
	}
	if(kill_rec_==NO) break;
      }
      if(kill_rec_==NO) fasupd(60); else faskill(60);
    }
  }
  sysput(3770,2,&dat_st_0);
  endsr:;
  fasflush(0);
}
 
static clr_11()
{
  int16 len_,g;
  uint16 n;
									
  n=0;fasinit(11);
  scrget(1,7);scrupd(-3,0);
  n=0;scrnum=0; len_=s(11,135)-s(11,100);
  FOREVER{
    *u(11,1)=++n; dsp_working();
    g=fasgeti(11);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
      copy(s(11,100),s(11,135),len_);
      zero(s(11,100),len_);
      fasupd(11);
    }
  }
  fasflush(0);
  endsr:;
}

static contract()
{
  int16 k;
									
  if(fldlen(9,4) && *s(9,4)) return YES;
  if(fldlen(9,5) && *u(9,5)) return YES;
  for(k=6;k<=8;k++) if(fldlen(9,k) && *f(9,k)) return YES;
  if(fldlen(9,9) && *s(9,9)) return YES;
  for(k=10;k<=15;k++) if(fldlen(9,k) && *f(9,k)) return YES;
  for(k=20;k<=24;k++) if(fldlen(9,k) && *f(9,k)) return YES;
  if(fldlen(9,16) && *i(9,16)) return YES;
  return NO;
}

static zero_stock()
{
  int16 key,z,curs=1;
  char zeker='N';

  inq_loc=99;
  FOREVER{
    redo:;
    scrget(3,8);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_uJN,&zeker);
    scrifld(z++,fm_uu2,&groep_i);
    if(fldlen(66,1)) scrifld(z++,fm_uu2,&inq_loc);
    else streepje(z++);
    key=scrupd(curs,0x0519);curs=1;
    if(key==111) ovlexit(-1);
    if(inq_loc==99) copy("DEPOT",nm_fil,6);
    else if(inq_loc>=1 && inq_loc<=10){
      if(fldlen(66,11+(inq_loc-1)*15) && nm_loc[inq_loc-1][0]!='\0'){
	copy(nm_loc[inq_loc-1],nm_fil,6);
      }
      else {curs=4;zero(nm_fil,6);errnum=34;goto redo;}
    }
    else if(inq_loc!=0) {curs=4;zero(nm_fil,6);errnum=34;goto redo;}
		seldata.selp_use=NO;
		if(key==109 && zeker=='J'){
      if(ovlcall(2215,5)==0){
				wis_stock(1);break;
			}
		}
    if(key==101 || key==105) break;
    if(key==104 && zeker=='J'){
      wis_stock(0);break;
    }
    else errnum=21;
  }
}

static wis_stock(select_mode_) // 1= uitgebreide selectie
int16 select_mode_;
{
  uint16 a,g,k;
 
  fasunlck(-2);
	scrnum=0;scrget(1,170);
  scrifld(10,fm_os79,"    De actuele stock wordt nu op 0 gezet");
	a=0;
  FOREVER{
		next_art:;
    *u(6,1)=++a; dsp_working();
    g=fasgeti(6);
    if(g==47)break;
    if(g!=46){/* deleted record */
			if(select_mode_){
				if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
			}
			if(groep_i==0 || groep_i==*i(6,9)){
				if(fldlen(66,1)){
					if(inq_loc==0 || inq_loc==99) {
						if(fldlen(6,32)) *f(6,32)=0;
						*f(6,33)=0; fasupd(6);
					}
					if(inq_loc!=99){
						fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
						for(k=0;k<10;k++) {
							if((k==inq_loc-1 || inq_loc==0) && fldlen(66,11+k*15)) *f(66,11+k*15)=0;
						}
						if(*u(66,1)) fasupd(66);
					}
				}
				else{
					if(fldlen(6,32)) *f(6,32)=0;
					*f(6,33)=0;
					fasupd(6);
				}
			}
		}
  }
  fasflush(0);
	fasunlck(-1);
}

static stock_input(int16 inputmode_)  // 0=stock input, 1=invewntariscorrectie
{
  int16 j,k,n,curs,z,z_base_,key,mode_,max_,pos_,add_kol_=YES,curspos_;
  uint16 dt_,arec_;
  char stuksfl_;
  float *p_stock_,qlv_,fls_,bak_,rd_stock_,verp_factor_;

	inq_lev=0;inq_groep=0;inq_art=0;manier='A';inq_loc=99;copy("DEPOT",nm_fil,5);AlleenMetStock='N';

  FOREVER{
    redo_sel:;
    if(select_art(inputmode_)) break;
    if(st_per_art=='J') {man_stock(inputmode_);break;}
    p_stock_=f(6,33); if(inputmode_==1) p_stock_=f(6,63);
    if(inq_loc>=1 && inq_loc<=10 && fldlen(66,11+(inq_loc-1)*15)){
      p_stock_=f(66,11+(inq_loc-1)*15);
    }
    scrget(1,7);scrupd(-3,0);
    zero((char *)&tb[0],sizeof tb);fasinit(6);
    if(inq_art) {*u(6,1)=inq_art;fasgeti(6);}
    start=0;max_=0;mode_=1;curs=2;
    FOREVER{
      next:;
      if(faskeyi(6,sort_key,mode_)) break; mode_=2;
			if(fldlen(6,200) && *u(6,200)) goto next;
      if(inq_lev && *u(6,7)!=inq_lev) goto next;
      if(inq_groep && *u(6,9)!=inq_groep)  goto next;
			if(inq_groep==0 && inq_art==0){
        if(selec_tst()==NO) goto next;
			}
			if(AlleenMetStock=='J' && *p_stock_==0) goto next;
      tb[max_++].rec=*u(6,1);
			if(inq_art) break;
      if(max_>=DIM_REC){errnum=11; break;}
    }
    if(max_==0) {errnum=39;goto redo_sel;}
    start=0;curs=2;
    FOREVER{
      redo:;
      scrnum=0; z=1;
			if(inputmode_==0) scrget(3,13); else scrget(3,19);
      scrifld(-z,fm_us30,werkveld);z++;

      z_base_=z;
      zero((char *)&tb_val[0].stock[0],sizeof tb_val);
      for(j=start;j<start+18;j++){
				if(tb[j].rec==0) break;
				fasinit(6); *u(6,1)=tb[j].rec;fasgeti(6);
				if(fldlen(66,1)){
					fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
				}
				zero(art_nm,sizeof art_nm);pos_=0;
				if(sort_key==1){
					pos_+=add_str(&art_nm[pos_],s(6,2),fldlen(6,2));art_nm[pos_++]=' ';
					pos_+=add_str(&art_nm[pos_],s(6,3),fldlen(6,3));
				}
				else {
					pos_+=add_str(&art_nm[pos_],s(6,3),fldlen(6,3));art_nm[pos_++]=' ';
					pos_+=add_str(&art_nm[pos_],s(6,2),fldlen(6,2));
				}
				scrifld(z++,fm_os36,art_nm);
				pos_=j-start;
				if(inputmode_==0){
					for(k=0;k<2;k++){
						if(add_kol_) scrifld(z++,fm_uf5_0,&tb_val[pos_].stock[k]);
						else scrifld(z++,fm_of5_0,&tb_val[pos_].stock[k]);
					}
					stock2stks(*p_stock_,*f(6,31),&tb_val[pos_].ostock[0],&tb_val[pos_].ostock[1]);
					for(k=0;k<2;k++){
						if(add_kol_) scrifld(z++,fm_of5_0,&tb_val[pos_].ostock[k]);
						else scrifld(z++,fm_uf5_0,&tb_val[pos_].ostock[k]);
						if(*p_stock_<-0.0001) scrchat(z-1,0x0B); else scrchat(z-1,0xFF);
					}
				}
				else{
					stock2stks(*p_stock_,*f(6,31),&tb_val[pos_].stock[0],&tb_val[pos_].stock[1]);
					tb_val[pos_].ostock[0]=*f(6,64);tb_val[pos_].ostock[1]=*f(6,63)* *f(6,64);
					scrifld(z++,fm_uf5_0,&tb_val[pos_].stock[0]);
					scrifld(z++,fm_uf5_0,&tb_val[pos_].stock[1]);
					scrifld(z++,fm_uf4_3,&tb_val[pos_].ostock[0]); // eh.prijs
					scrifld(z++,fm_of6_2,&tb_val[pos_].ostock[1]);  // waarde 
				}
      }
      redo_upd:;
      key=scrupd(curs,0x1A7);curs=2;curspos_=fldcurs;
      if(key==106) goto redo;

      for(j=start;j<start+18;j++){
				if(tb[j].rec==0) break;
				fasinit(6); *u(6,1)=tb[j].rec;fasgeti(6);
				if(fldlen(66,1)){
					fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
				}
				pos_=j-start;n=0;
				if(inputmode_==0){
					tb_val[pos_].ostock[0]+=tb_val[pos_].stock[0];
					tb_val[pos_].ostock[1]+=tb_val[pos_].stock[1];
					stks2stock(&qlv_,*f(6,31),tb_val[pos_].ostock[0],tb_val[pos_].ostock[1]);
					if(*f(6,31)<1) *f(6,31)=1;
					stuksfl_='N'; // is al geconverteerd
					verp_factor_=1.;	arec_=*u(6,1);
					if(fldlen(6,102) && *u(6,102)){// stock op moederfiche bijwerken
						verp_factor_=*f(6,31);
						*u(6,1)=*u(6,102);fasgeti(6);
				#if FLAGSAS | FLAGAST
						if(NO){ // gekoppeld, altijd moederfiche bijwerken
				#else
						if(*f(6,31) ==verp_factor_) {// bij zelfde aantal/bak toch op eigen artikel bijhouden
				#endif
							fasinit(6);*u(6,1)=arec_;fasgeti(6);
						} 
						if(*f(6,31)  && stuksfl_!='J') verp_factor_/=*f(6,31); else verp_factor_=1.; // indien stuks, dan ook als stuks van hoofdartikel beschouwen
						qlv_*=verp_factor_;
					}
					if(fldlen(66,1)){
						fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
					}
					bak_=0;fls_=0; if(stuksfl_=='J') fls_=qlv_; else bak_=qlv_;
					rd_stock_=0;stks2stock(&rd_stock_,*f(6,31),bak_,fls_);
					*p_stock_+=rd_stock_;
					if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				}
				else{
					stks2stock(p_stock_,*f(6,31),tb_val[pos_].stock[0],tb_val[pos_].stock[1]);
					*f(6,64)=tb_val[pos_].ostock[0];
				}
				fasunlck(-2);
				fasupd(6);
				if(fldlen(66,1)){
					if(*u(66,1)) fasupd(66); else fasadd(66);
				}
				fasunlck(-1);
				zero((char *)&tb_val[pos_].stock[0],sizeof tb_val[0].stock);
			}
      if(key==18){exec_work();curs=curspos_+1;goto redo;}
      if(key==109 && inputmode_==0){
				if(add_kol_) add_kol_=NO;
				else add_kol_=YES;
      }

      if(key==101) break;
      if(key==102) start-=18;
      if(key==103) {start+=18;if(start>=max_-18) start=max_-18;}
      if(start<0) start=0;
    }
  }
  endsr:;
}

static select_art(int16 inputmode_)
{
  int16 key,z,curs=2,curspos_;
 
  if(fldlen(66,1)==0) inq_loc=99;
  fasinit(52);if(inq_groep) {*u(52,1)=inq_groep;fasgeti(52);}
	fasinit(6);if(inq_art) {*u(6,1)=inq_art;fasgeti(6);}
	fasinit(1);if(inq_lev) {*u(1,1)=inq_lev;fasgeti(1);}
  FOREVER{
    redo:
    scrget(3,14);z=1;
    if(inputmode_==0) DisplayMenuTitel(2,"Ingeven getelde aantallen in stock",0xA);   
		else DisplayMenuTitel(2,"Corrigeren inventaris (aantallen/prijzen)",0xA);
		scrfld(z++,25,1);
    scrifld(z++,fm_u_AKP,&manier);
    scrifld(-z,fm_uu2,&inq_groep); z++;scrofld(z++,52,14,-1);
		scrfld(z++,1,3);
    scrfld(z++,6,3);
    if(fldlen(66,1)){
      scrifld(-z,fm_uu2,&inq_loc);z++;scrifld(z++,fm_os6,nm_fil);
    } else {streepje(z++); z++;}
    scrifld(z++,fm_uJN,&AlleenMetStock);
    key=scrupd(curs,0x0281);curs=2;curspos_=fldcurs;
    if(key==101) return YES;
    if(key==111) ovlexit(*u(25,4));
		st_per_art='N';if(key==110) {st_per_art='J';return NO;}
    fasinit(52);
    if(inq_groep){
			*u(52,1)=inq_groep;fasgeti(52);
			if(key==18){curs=curspos_+1;goto redo;}
    }
    zero(nm_fil,sizeof nm_fil);
		if(inq_loc==99) copy("DEPOT",nm_fil,6);
    else if(inq_loc>=1 && inq_loc<=10){
      if(fldlen(66,11+(inq_loc-1)*15) && nm_loc[inq_loc-1][0]!='\0'){
			copy(nm_loc[inq_loc-1],nm_fil,6);
      }
      else {curs=7;zero(nm_fil,6);errnum=34;goto redo;}
    }
    else {curs=7;zero(nm_fil,6);errnum=34;goto redo;}
    if(key==18){
      curs=curspos_+1;goto redo;
    }
		if(*s(1,3)){
      if(search(1,0)) {curs=5;goto redo;}
    }
    else fasinit(1);
		inq_lev=*u(1,1);
		if(*s(6,3)){
      if(search(6,0)) {curs=6;goto redo;}
    }
    else fasinit(6);
		inq_art=*u(6,1);
    sort_key=2;
    if(manier=='K') sort_key=1;
    else if(manier=='P') sort_key=6;
    if(key==108) break;
  }
	if(inq_groep==0 && inq_art==0) dsp_tabel(1);
  return NO;
}

static man_stock(int16 inputmode_)
{
  int16 k,key,curs=1,z,smode_;
  float stockwijz[2],stock[3][2],o_stock[3][2],q_stuks,*p_stock_;
  char o_code[15],o_name[50];
  flag mode;
  uint16 arec_;
  char stuksfl_;
  float qlv_,fls_,bak_,rd_stock_,verp_factor_;

	if(fldlen(66,1)==0) inq_loc=99;
  zero(werkveld,sizeof werkveld);
  zero((char *)&stockwijz[0],sizeof stockwijz);
  zero((char *)&stock[0][0],sizeof stock);
  zero((char *)&o_stock[0][0],sizeof o_stock);
  o_code[0]='\0';o_name[0]='\0';
  p_stock_=f(6,33); if(inputmode_==1) p_stock_=f(6,63);
  if(inq_loc>=1 && inq_loc<=10 && fldlen(66,11+(inq_loc-1)*15)){
    p_stock_=f(66,11+(inq_loc-1)*15);
  }
  FOREVER{
    fasinit(6);mode=YES;q_stuks=1;
    redo:

		if(fldlen(6,200)){
			if(*u(6,200)) ConLook(1); else   ConLook(0);
		}
    scrnum=0;scrget(3,9);z=1;
    if(inputmode_==0) DisplayMenuTitel(0,"Ingeven getelde aantallen in STOCK",0xA);   
		else DisplayMenuTitel(0,"Corrigeren INVENTARIS",0xA);
		if(barc_used){
      scraddfield(300,0,0,0xAA);
		  scrifld(300,fm_os59,"^0A^08|^12");
		}
    scrofld(z++,6,arcd,-1);
    if(mode){
			scrfld(z++,6,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
			fm_stock[1]|=0x40;
		}
		else{scrofld(z++,6,3,-1);fm_stock[1]&=0xBF;}
    scrifld(z++,fm_stock,&stockwijz[0]);
    scrifld(z++,fm_stock,&stockwijz[1]);
    fm_stock[1]&=0xBF;/* output */
    for(k=0;k<3;k++){
      if(k==2 && mode==NO) fm_stock[1]|=0x40;/* update */
      scrifld(z++,fm_stock,&stock[k][0]);
      scrifld(z++,fm_stock,&stock[k][1]);
    }
    fmt_get(fmt,6,arcd);fmt[1]&=0xBF;scrifld(z++,fmt,o_code);
    fmt_get(fmt,6,3);fmt[1]&=0xBF;scrifld(z++,fmt,o_name);
    fm_stock[1]&=0xBF;
    for(k=0;k<3;k++){
      scrifld(z++,fm_stock,&o_stock[k][0]);
      scrifld(z++,fm_stock,&o_stock[k][1]);
    }
		if(fldlen(66,1)){
      scrifld(z++,fm_ou2,&inq_loc);scrifld(z++,fm_os6,nm_fil);
    } else {streepje(z++); z++;}
    if(barc_used){
      scrifld(-z,fm_us30,werkveld); z++;
    } else z++;
    key=scrupd(curs,0xC1);curs=1;
		if(fldlen(6,200)) ConLook(0);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		smode_=0;if(key==5001) smode_=98;
    if(key==101) break;

    if(barc_used && key==18 && werkveld[0]){
      if(*s(6,3)){screrr(-1);goto redo;}
      k=exec_barc();
      if(k>0){curs=2+k;goto redo;}
    }

    if(mode){
      if(search(6,smode_)) goto redo;
			if(fldlen(66,1)){
				fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
			}
			stock2stks(*p_stock_,*f(6,31),&stock[0][0],&stock[0][1]);
      if(fldlen(6,31)) q_stuks=*f(6,31);
      if(q_stuks<1) q_stuks=1;
    //  stock[0][0]=(long)(*p_stock_); stock[0][1]=0;
    //  if(q_stuks>1 && *p_stock_!=0){
				//stock[0][1]=(long)(((*p_stock_-stock[0][0])*q_stuks)+0.49);
    //  } else stock[0][1]=0;
      stock[1][0]=stockwijz[0];stock[1][1]=stockwijz[1];
      zero((char *)stockwijz,sizeof stockwijz);
      for(k=0;k<2;k++){
				stock[2][k]=stock[0][k]+stock[1][k];
      }
    }
    if(key==107 || key==18){
      mode=NO;
      goto redo;
    }
    if(key!=108) goto redo;
    if(stock[1][0] || stock[1][1] || stock[0][0]!=stock[2][0] || stock[0][0]!=stock[2][0] || stock[0][1]!=stock[2][1]){

			stks2stock(&qlv_,*f(6,31),stock[2][0],stock[2][1]);
			if(*f(6,31)<1) *f(6,31)=1;
			stuksfl_='N'; // is al geconverteerd
			verp_factor_=1.;	arec_=*u(6,1);
			if(fldlen(6,102) && *u(6,102)){// stock op moederfiche bijwerken
				verp_factor_=*f(6,31);
				*u(6,1)=*u(6,102);fasgeti(6);
		#if FLAGSAS | FLAGAST
				if(NO){ // gekoppeld, altijd moederfiche bijwerken
		#else
				if(*f(6,31) ==verp_factor_) {// bij zelfde aantal/bak toch op eigen artikel bijhouden
		#endif
					fasinit(6);*u(6,1)=arec_;fasgeti(6);
				} 
				if(*f(6,31)  && stuksfl_!='J') verp_factor_/=*f(6,31); else verp_factor_=1.; // indien stuks, dan ook als stuks van hoofdartikel beschouwen
				qlv_*=verp_factor_;
			}
			if(fldlen(66,1)){
				fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
			}
			bak_=0;fls_=0; if(stuksfl_=='J') fls_=qlv_; else bak_=qlv_;
			rd_stock_=0;stks2stock(&rd_stock_,*f(6,31),bak_,fls_);
			*p_stock_+=rd_stock_;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update

//      *p_stock_=stock[2][0]+ stock[2][1]/q_stuks;
			fasupd(6);
			if(fldlen(66,1)){if(*u(66,1)) fasupd(66); else fasadd(66);}
			fasflush(0);
			*u(6,1)=arec_;fasgeti(6); // om origineel te tonen
      copy(s(6,arcd),o_code,fldlen(6,arcd));
      copy(s(6,3),o_name,fldlen(6,3));
      for(k=0;k<3;k++){o_stock[k][0]=stock[k][0];o_stock[k][1]=stock[k][1];}
    }
    zero((char *)&stock[0][0],sizeof stock);
  }
}


static AddStockFromWrkFilesKassa(void)
{
  int16 key,z,k,g,curs=3,wrkref,displaymode_;
	char wrk_name_[50],sttxt_[4],buf1[10],bonean_[14];
  int16 mode_=0,nr_,bnr_,kasnr_,lnr_,size,count,bonwrk_size;
	int16 form_dat[8],pr_mode,prtnr;
  float qlv_,*p_stock_,fls_,bak_,rd_stock_,verp_factor_,prx_;
  uint16 arec_;
  char stuksfl_;

	wrk_size = &p_lin.EindeWRKReclen - (char *)&p_lin.bits;
  // wrk_size=sizeof(struct s_lijn) - sizeof(p_lin.text);
  inq_loc=99; AddWrkBon2Loc='J'; if(fldlen(66,1)==0 || AddWrkBon2Loc!='J') AddWrkBon2Loc='N';
	FOREVER{
		redo:;
		scrget(3,25);z=1;
		scraddpicto(2,0,76,22,4,2,573,0,0,"Maak XLS"); 
		scrifld(z++,VarTextFmt(65,0),"Toevoegen stock van de bewaarde bons op de kassa (geschenkmanden)");
		scrfld(z++,25,1);
		scrifld(z++,fm_uu2,&inq_kassa);
		scrifld(z++,fm_uu3,&bon_beg);scrifld(z++,fm_uu3,&bon_end);
    if(fldlen(66,1)) scrifld(z++,fm_uJN,&AddWrkBon2Loc);
    else streepje(z++);
  	for(k=0;k<5;k++) {
			scrifld(z++,fm_os6,&nm_kassa[k][0]);
			scrifld(z++,fm_odat,&dt_kvk[k]);
			scrifld(z++,fm_os6,&nm_kassa[k+5][0]);
			scrifld(z++,fm_odat,&dt_kvk[k+5]);
		}
		key=scrupd(curs,0x189);curs=3;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) goto endsr;
		if(inq_kassa==0) {curs=3;errnum=38;goto redo;}
    if(inq_kassa && (fldlen(91,11+(inq_kassa-1)*5)==0 || nm_kassa[inq_kassa-1][0]=='\0') ){
      curs=3;errnum=34;goto redo;
    }
		if(bon_end && (bon_end>490 || bon_end<bon_beg)){curs=5; errnum=34; goto redo;}
		prt2xls=NO;if(key==5002){prt2xls=YES; key=109;} // xls
		if(key==104){
			if(scr_ok("Wenst U echt de werkbonnen op de server te wissen ?")==NO) goto redo;
			kasnr_=1; if(inq_kassa) kasnr_=inq_kassa;
			for(kasnr_;kasnr_<=10;kasnr_++){
				if(inq_kassa && kasnr_!=inq_kassa) break;
				if(nm_kassa[kasnr_-1][0]=='\0') continue;
				zero(wrk_name_,sizeof wrk_name_);copy("kassa-00",wrk_name_,8);stcli_d(&wrk_name_[6],(long)kasnr_,2,0);wrk_name_[8]=0x5C;

				for(nr_=bon_beg;nr_<490;nr_++){
					if(bon_end && nr_>bon_end) break;
					movmem("KASBON00.WRK",&wrk_name_[9],13);
					if(nr_<100) sprintf(buf1,"N%02i",nr_); else sprintf(buf1,"%03i",nr_); 
					movmem(buf1,&wrk_name_[14],3);
					mk_name(3936,wrk_name_);
					if(FileExist(filnam)) _unlink(filnam);
				}
			}
			DisplayWarning("U dient nu eerst met de kassa's door te sturen !",0,0);
		}
		if(key==109){displaymode_=YES;break;}
    if(key==108){
			displaymode_=NO;
      if(scr_ok("Wenst U echt de stock te wijzigen met aantallen uit bestand ?")==YES) break;
    }
	}
  p_stock_=f(6,33);

	if(prt2xls){
		scrget(1,7);scrupd(-3,0);
		XlsRef=OpenXlsFile("Stocklijst werkbons kassa",*u(25,2));
    if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsColumnSize(XlsRef,4,35);
	  XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,0,XlsKol++,0,"Kassa",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"BonNr",0);
#if FLAGDKR
		XlsWrite(XlsRef,0,XlsKol++,0,"EAN bon",0);
#endif
		XlsWrite(XlsRef,0,XlsKol++,0,"Code",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Omschrijving",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Aantal",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Prijs",0);
		XlsRij++; XlsKol=1;
    goto no_header;
	}




	getsysprNew(5,form_dat,&pr_mode,&prtnr); PrintPaperNr=0;
  if ((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,25); prttext("<t30b>Stocklijst werkbons kassa");
  prttext("<b><t60>"); prtifld(fm_udat,u(25,2),-1); prttext("<t72>Blz.<ppp>.");
  prtbuf(1);
	z=1;
  prtitab(z,fm_ou3,&kasnr_,1,-1); prttitle(z++,"Kas",0x13);
  prtitab(z,fm_ou3,&bnr_,1,-1); prttitle(z++,"Bnr",0x13);
#if FLAGDKR
	prtitab(z,VarTextFmt(13,0),bonean_,1,-1); prttitle(z++,"EAN bon",3);
#endif
  prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,2,-1); prttitle(z++,"Omschrijving",3);
  prtitab(z,fm_uf6_0,&qlv_,1,-1); prttitle(z++,"Aantal",0x13);
	prtitab(z,fm_uf4_2,&prx_,1,-1); prttitle(z++,"Prijs",0x13);
  prtitab(z,fm_os2,sttxt_,2,-1); prttitle(z++,"",3);
	prtbuf(3);
	no_header:;
	kasnr_=1; if(inq_kassa) kasnr_=inq_kassa;
	for(kasnr_;kasnr_<=10;kasnr_++){
		if(inq_kassa && kasnr_!=inq_kassa) break;
		if(nm_kassa[kasnr_-1][0]=='\0') continue;
		zero(wrk_name_,sizeof wrk_name_);copy("kassa-00",wrk_name_,8);stcli_d(&wrk_name_[6],(long)kasnr_,2,0);wrk_name_[8]=0x5C;
    p_stock_=f(6,33);
    if(AddWrkBon2Loc=='J' && loc_nr[kasnr_-1]>=1 && loc_nr[kasnr_-1]<=10 && fldlen(66,11+(loc_nr[kasnr_-1]-1)*15)){
      p_stock_=f(66,11+(loc_nr[kasnr_-1]-1)*15);
    }
		for(nr_=bon_beg;nr_<490;nr_++){
			if(bon_end && nr_>bon_end) break;
			movmem("KASBON00.WRK",&wrk_name_[9],13);
			if(nr_<100) sprintf(buf1,"N%02i",nr_); else sprintf(buf1,"%03i",nr_); 
			movmem(buf1,&wrk_name_[14],3);
      mk_name(3936,wrk_name_);
			if( (wrkref= dopen(filnam, O_RDONLY|O_BINARY )) == -1 ) continue;


			bonwrk_size = wrk_size;
      size=dseek(wrkref,0L,2); dseek(wrkref,0L,0);
			if(size>=WRK_BONHDR_LEN){
				count=(size-WRK_BONHDR_LEN)% bonwrk_size;
				if (count) { // nog oude bon zonder promo
					bonwrk_size = &p_lin.EindeReclenKaslog - p_lin.text - sizeof(p_lin.text);
					count = (size - WRK_BONHDR_LEN) % bonwrk_size;
				}
				if(count==0){ // nieuwe wrk-file met bonheader
					count=(size-WRK_BONHDR_LEN)/ bonwrk_size;  
					dread(wrkref,(char *)buf600,WRK_BONHDR_LEN); // om pointer juist te zetten
				} else count=size/bonwrk_size;
			}
	    else count=size/bonwrk_size;

			//size=dseek(wrkref,0L,2); dseek(wrkref,0L,0);
			//if(size>=WRK_BONHDR_LEN){
			//	count=(size-WRK_BONHDR_LEN)% wrk_size;
			//	if(count==0){ // nieuwe wrk-file met bonheader
			//		dseek(wrkref,(long)(WRK_BONHDR_LEN),0);
			//		count=(size-WRK_BONHDR_LEN)/ wrk_size;
			//	}
			//}
			bnr_=nr_;
			zero(bonean_,sizeof bonean_);
			sprintf_s(bonean_,sizeof bonean_,"%s%03d","283900198",bnr_);bonean_[12]='0'; ean13c(bonean_);
			for (lnr_=0; lnr_<count; lnr_++) { 
				if (bonwrk_size!=dread(wrkref,(char *)&p_lin.bits,bonwrk_size)) break;
				if (p_lin.groep>=1 && p_lin.groep<=98) { // GEEN leeggoed
		//			if (p_lin.groep==99 && p_lin.bits&0x02) continue; // geen gekoppeld leeggoed 
					fasinit(6);  copy(p_lin.code,s(6,2),fldlen(6,2));
			    if(sys4408){*u(6,1)=val(s(6,2));g=fasgetu(6);} // record# is code op kassa
			    else{g=faskeyu(6,1,0);}
					if(g==0){
						qlv_=p_lin.aantal; prx_=p_lin.prijs;
						sttxt_[0]='\0'; if (p_lin.bits&STUKS && *f(6,31)>1) copy("St",sttxt_,3);

						if(*f(6,31)<1) *f(6,31)=1;
						stuksfl_='N';if(sttxt_[0] && *f(6,31)>1) stuksfl_='J';
						verp_factor_=1.;	arec_=*u(6,1);
						if(fldlen(6,102) && *u(6,102)){// stock op moederfiche bijwerken
							verp_factor_=*f(6,31);
							*u(6,1)=*u(6,102);fasgeti(6);
				#if FLAGSAS | FLAGAST
							if(NO){ // gekoppeld, altijd moederfiche bijwerken
				#else
							if(*f(6,31) ==verp_factor_) {// bij zelfde aantal/bak toch op eigen artikel bijhouden
				#endif
								fasinit(6);*u(6,1)=arec_;fasgeti(6);
							} 
							if(*f(6,31)  && stuksfl_!='J') verp_factor_/=*f(6,31); else verp_factor_=1.; // indien stuks, dan ook als stuks van hoofdartikel beschouwen
						}
						qlv_*=verp_factor_;
 
						if(fldlen(66,1)){
							fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
						}
						bak_=0;fls_=0; if(stuksfl_=='J') fls_=qlv_; else bak_=qlv_;
						rd_stock_=0;stks2stock(&rd_stock_,*f(6,31),bak_,fls_);
						*p_stock_+=rd_stock_;
						if(displaymode_==NO){
 							if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
							fasupd(6);
							if(fldlen(66,1)){
								if(*u(66,1)) fasupd(66); else fasadd(66);
							}
						}
						if(prt2xls){
  						XlsKol=1;
							WriteVar2Xls(XlsRij,XlsKol++,fm_ou3,&kasnr_,0);
							WriteVar2Xls(XlsRij,XlsKol++,fm_ou3,&bnr_,0);
							WriteVar2Xls(XlsRij,XlsKol++,VarTextFmt(13,0),bonean_,0);
							WriteFld2Xls(XlsRij,XlsKol++,6,2,0);
							WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
							if(sttxt_[0]) qlv_/=*f(6,31);
							WriteVar2Xls(XlsRij,XlsKol++,fm_of6_2,&rd_stock_,0);
							WriteVar2Xls(XlsRij,XlsKol++,fm_of6_2,&prx_,0);
							XlsRij++;
						}
						else{
							*u(6,1)=arec_;fasgeti(6); // om origineel artikel te drukken met origineel aantal
  						for(k=0;k<20;k++) prtinfo(k,0);nextline();
						}
					}
				}
			}
			dclose(wrkref);
		}
	}
	if(prt2xls) XlsClose(XlsRef,1);
	else{  prtform(0);prtclose();}
  endsr:;
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

#include "Std\XlsFunc.c"

static OpenXlsFile(text_,datum_)
char *text_;
unsigned datum_;
{
	int16 pos_,dd,mm,yy;
  char string[100];
				
  zero(string,sizeof string);
	pos_=copy0(text_,&string[0],30);
  if(datum_){
    string[pos_++]=' ';
    jddate(datum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
	pos_+=copy0(".XLS",&string[pos_],4);
	
  pos_=XlsCreate(string);
	return pos_;
}


static mk_name(adr_pref,ps)
uint16 adr_pref;
char *ps;
{
  char *pd;
				
  zero(filnam,sizeof filnam); pd=filnam;
  sysget(adr_pref,25,pd);
  while(*pd) pd++;
  while(*ps!='\0') *pd++=*ps++;
  *pd='\0';
}

static nextline()
{
  free=prtline();
}

#if FLAGSHN
static ExportArtikels2Txt()/* key 2 in stu 58 moet bestaan ! */
{
  int16 key,curs=1,k,n,z,key_mode,keynr,curspos_;
  int16 bpos_,bloc_,mloc_;
  char choice='A';
 

  if(filnam[0]=='\0') copy("Articles.TXT",filnam,20);seqo_mode=2;
  FOREVER{
    redo:
    scrget(3,118); z=1;
    scrfld(z++,25,1);
 
    scrifld(z++,fm_us20,filnam);
    key=scrupd(curs,0x0481);curs=1;curspos_=fldcurs;
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
 
    if(filnam[0]=='\0'){curs=5;errnum=38;goto redo;}

    if(key==108) break;
  }
  seldata.selp_use=NO;
  if(ovlcall(2215,1)) goto endsr;
  scrget(1,170);
  fasclos(-2);if(fasopen(filnam,12)) {errnum=9;goto endsr;}
  fasinit(80);seqo_pos=0;seqo_mode=2;
  zero(seqo_str,sizeof seqo_str);pos=0;
 
	char2str("Code",4); char2str("EAN",3);char2str("Description",11);char2str("PcInCrate",9);
  CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
	seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
/* artikel dumpen */
	seqo_len=0;
	for(k=0;k<pos;k+=280){
		if((k+280)>pos) seqo_len=pos-k;
		else seqo_len=280;
		copy(&seqo_str[k],s(80,1)+4,seqo_len);
		seqo_flush();
	}



  scrget(1,7);scrupd(-3,0);
  fasinit(6);  key_mode=1;
  FOREVER{
    if(faskeyi(6,2,key_mode)) break; key_mode=2;
    if(DirCall_DRK2215_SelectArtikel()){
			if(*s(6,70)){
        zero(seqo_str,sizeof seqo_str);pos=0; if(*f(6,31)<1) *f(6,31)=1;
        seqo_fld(6,2); seqo_fld(6,70); seqo_fld(6,3); seqo_fld(6,31);
        CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
				seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
	/* artikel dumpen */
				seqo_len=0;
				for(k=0;k<pos;k+=280){
					if((k+280)>pos) seqo_len=pos-k;
					else seqo_len=280;
					copy(&seqo_str[k],s(80,1)+4,seqo_len);
					seqo_flush();
				}
			}
			if(*s(6,71)){// stuks 
        zero(seqo_str,sizeof seqo_str);pos=0;
        seqo_fld(6,2); seqo_fld(6,71); seqo_fld(6,3); 
				*f(6,31)=1; seqo_fld(6,31);
        CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
				seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
	/* artikel dumpen */
				seqo_len=0;
				for(k=0;k<pos;k+=280){
					if((k+280)>pos) seqo_len=pos-k;
					else seqo_len=280;
					copy(&seqo_str[k],s(80,1)+4,seqo_len);
					seqo_flush();
				}
			}
    }
  }
  fasinit(64);
  key_mode=1;
  FOREVER{ // extra barcodes
    if(faskeyi(64,2,key_mode)) break; key_mode=2;
		fasinit(6);*u(6,1)=*u(64,3); fasgeti(6); if(*f(6,31)<1) *f(6,31)=1;
    if(DirCall_DRK2215_SelectArtikel()){
      zero(seqo_str,sizeof seqo_str);pos=0;
      seqo_fld(6,2); seqo_fld(64,2); seqo_fld(6,3); 
			if(*u(64,4)==1) *f(6,31)=1;
			seqo_fld(6,31);
      CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
  		seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
	/* artikel dumpen */
			seqo_len=0;
			for(k=0;k<pos;k+=280){
				if((k+280)>pos) seqo_len=pos-k;
				else seqo_len=280;
				copy(&seqo_str[k],s(80,1)+4,seqo_len);
				seqo_flush();
			}
		}
  }
  fasclos(-2);
  endsr:;
}



static AddStockFromTxt(void)
{
  int16 key,z,curs=3;
	char logfile[50];
  int16 mode_=0,cnt_bad=0,cnt_good=0;
	int16 form_dat[8],pr_mode,prtnr;
  float qlv_;

  fasinit(6);
	zero(logfile,sizeof logfile);  
	fasclos(-2);fasinit(80);

  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,4,15,3);
    scraddf(z++,8, 5,0);scraddf(z++,8,22,2);
    scraddf(z++,15,1,0);
		scraddf(z++,16,1,0);
		scraddf(z++,17,1,0);
    scraddf(z++,23,1,8);scraddf(z++,23,11,8);

    z=1;
    scrifld(z++,VarTextFmt(49,0),"Toevoegen stock vanuit TAB-gescheiden TXT-bestand");
    scrifld(z++,fm_os79,"Naam bestand :");scrifld(z++,fm_us30,logfile);
    scrifld(z++,fm_os79,"Opmerking :");
		scrifld(z++,fm_os79," - Kolommen :  A=EAN, B=Aantal");

		scrifld(z++,fm_os79," - kopieer het bestand op de SERVER in de map J:\\JamaData\\PROG");
    scrifld(z++,VarTextFmt(9,0)," F1 stop ");scrifld(z++,VarTextFmt(18,0)," F8 begin inlezen ");
    key=scrupd(curs,0x81);curs=1;
    if(key==101) goto endsr;
		fasclos(-2);
		if(logfile[0]=='\0') {errnum=38;goto redo;}
		if(fasopen(logfile,1)){errnum=1;goto redo;}
		fasclos(-2);
    if(key==108){
      if(scr_ok("Wenst U echt de stock te verhogen met de aantallen uit bestand ?")==YES) break;
    }
	}
	fasclos(-2);if(fasopen(logfile,1)){errnum=1;goto endsr;}
  getsysprNew(5,form_dat,&pr_mode,&prtnr); PrintPaperNr=0;
  if ((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t33b>Niet gevonden artikels");
  prttext("<b><t55>"); prtfld(25,2,-1); prttext("<t72>Blz.<ppp>.");
  prtbuf(1);
  scrnum=0;scrget(1,170); scrifld(2,fm_os38,"Verwerken artikel : ");scrupd(-3,0);
  fasinit(80);cnt_good=0;cnt_bad=0;mode_=0;
  FOREVER{
    next:;
    if(read_rec(mode_)) break;mode_=1;
		fasinit(64);get_str(s(64,2),0,fldlen(64,2)); 
		if(*s(64,2)=='\0') goto next;
		qlv_=get_num(1); if(qlv_==0) goto next;
		if(faskeyi(64,1,0)==0){
			fasinit(6);*u(6,1)=*u(64,3);fasgeti(6);
			 if(*u(64,4)==1 && *f(6,31)) qlv_/=*f(6,31);
		}
		else{
			fasinit(6);get_str(s(6,70),0,fldlen(6,70)); 
			if(faskeyi(6,10,0)){
				fasinit(6);get_str(s(6,71),0,fldlen(6,71)); 
				if(faskeyi(6,11,0)==0){
					if(*f(6,31)) qlv_/=*f(6,31);
				} else qlv_=0;
			}
	  }
		if(qlv_){
			*f(6,33)+=qlv_;
			scrfld(5,6,2); scrfld(6,6,3);scrifld(10,fm_of6_2,&qlv_);
			scrfld(13,6,33);scrupd(-3,0);
			fasupd(6);cnt_good++;
		}
		else{
			qlv_=get_num(1);
			prttext("EAN : ");prtfld(6,71,-1);
      prttext("Aantal :");prtifld(fm_of6_2,&qlv_,-1);
      prtline();cnt_bad++;
    }
  }
  fasclos(-2);
  prtform(0);prtclose();
  scrnum=0;
  scrget(1,170);
  scrifld(5,fm_os63,"Aantal goed verwerkte artikels : ");
  scrifld(6,fm_ou5,&cnt_good);
  scrifld(8,fm_os63,"Aantal NIET verwerkte artikels : ");
  scrifld(9,fm_ou5,&cnt_bad);
  scrifld(15,fm_os63,"Druk op F8 om verder te gaan ... ");
  scrupd(-1,0x81);
  endsr:;
}


#endif

static ReplaceStockByStockLocatie(void)
{
	int z,select_mode_,curs=1,key;
  uint16 a,g;
	char sel_vervangen='V';

  inq_loc=0;
  FOREVER{
    redo:;
    scrget(3,20);z=1;
    scrfld(z++,25,1);
		scrifld(z++,fm_uu2,&inq_loc);
    scrifld(z++,fm_uOV,&sel_vervangen);
    key=scrupd(curs,0x0109);curs=1;
    if(key==101) goto endsr;
    if(inq_loc>=1 && inq_loc<=10){
      if(fldlen(66,11+(inq_loc-1)*15) && nm_loc[inq_loc-1][0]!='\0'){
	      copy(nm_loc[inq_loc-1],nm_fil,6);
      }
      else {curs=2;zero(nm_fil,6);errnum=34;goto redo;}
    }
    else {curs=2;zero(nm_fil,6);errnum=34;goto redo;}
		seldata.selp_use=NO;select_mode_=NO;
		if(key==109){
      if(ovlcall(2215,1)==0){
				select_mode_=YES;break;
			}
		}
    if(key==104) break;
  }
	if(sel_vervangen=='O') {
  	if(DisplayWarning("Wenst u echt de stock te VERHOGEN met deze van de stocklocatie?",605,1)!=YES) goto endsr;
	}
	else{
		if(DisplayWarning("Wenst u echt de stock te VERVANGEN door deze van de stocklocatie?",605,1)!=YES) goto endsr;
	}
  fasunlck(-2);
	scrnum=0;scrget(1,170);
  scrifld(10,fm_os79,"    De actuele stock wordt aangepast...");
	a=0;
  FOREVER{
		next_art:;
    *u(6,1)=++a; dsp_working();
    g=fasgeti(6);
    if(g==47)break;
    if(g!=46){/* deleted record */
			if(select_mode_){
				if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
			}
			fasinit(66);*u(66,2)=*u(6,1);if(faskeyi(66,1,0)) fasinit(66);
			if(sel_vervangen=='O') *f(6,33)+=*f(66,11+(inq_loc-1)*15);
			else *f(6,33)=*f(66,11+(inq_loc-1)*15);
			fasupd(6);
		}
  }
  fasflush(0);
	fasunlck(-1);
	endsr:;
}

static AddStockFromXls(void)
{
  int16 key,z,curs=3;
	char logfile[50];
  int16 mode_=0,cnt_bad=0,cnt_good=0;
	int16 form_dat[8],pr_mode,prtnr;
  float qlv_,*p_stock_;

  fasinit(6);inq_loc=99;
	zero(logfile,sizeof logfile);  
	fasclos(-2);fasinit(80);
  
  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,4,15,3);
		scraddf(z++,6, 5,0);scraddf(z++,6,22,2);
    scraddf(z++,8, 5,0);scraddf(z++,8,22,2);
    scraddf(z++,15,1,0);
		scraddf(z++,16,1,0);
		scraddf(z++,17,1,0);
		scraddf(z++,18,1,0);
    scraddf(z++,23,1,8);scraddf(z++,23,11,8);

    z=1;
    scrifld(z++,VarTextFmt(49,0),"Toevoegen stock vanuit TAB-gescheiden TXT-bestand");
		scrifld(z++,fm_os79,"Stocklocatie :");  if(fldlen(66,1)) scrifld(z++,fm_uu2,&inq_loc); else streepje(z++);
    scrifld(z++,fm_os79,"Naam bestand :");scrifld(z++,fm_us30,logfile);
    scrifld(z++,fm_os79,"Opmerking :");
		scrifld(z++,fm_os79," - Kolommen :  A=Code, B=Omschrijving, C=Aantal");
		scrifld(z++,fm_os79," - in Excel : 'Opslaan als' en dan 'TXT-bestand' (TAB=scheidingsteken)");
		scrifld(z++,fm_os79," - kopieer het bestand op de SERVER in de map J:\\JamaData\\PROG");
    scrifld(z++,VarTextFmt(9,0)," F1 stop ");scrifld(z++,VarTextFmt(18,0)," F8 begin inlezen ");
    key=scrupd(curs,0x81);curs=1;
    if(key==101) goto endsr;
    if(inq_loc==99) copy("DEPOT",nm_fil,6);
    else if(inq_loc>=1 && inq_loc<=10){
      if(fldlen(66,11+(inq_loc-1)*15) && nm_loc[inq_loc-1][0]!='\0'){
      	copy(nm_loc[inq_loc-1],nm_fil,6);
      }
      else {curs=3;zero(nm_fil,6);errnum=34;goto redo;}
    }
    else if(inq_loc!=0) {curs=3;zero(nm_fil,6);errnum=34;goto redo;}
    p_stock_=f(6,33); 
    if(inq_loc>=1 && inq_loc<=10 && fldlen(66,11+(inq_loc-1)*15)){
      p_stock_=f(66,11+(inq_loc-1)*15);
    }
		fasclos(-2);
		if(logfile[0]=='\0') {errnum=38;goto redo;}
		if(fasopen(logfile,1)){errnum=1;goto redo;}
		fasclos(-2);
    if(key==108){
      if(scr_ok("Wenst U echt de stock te wijzigen met aantallen uit bestand ?")==YES) break;
    }
	}
	fasclos(-2);if(fasopen(logfile,1)){errnum=1;goto endsr;}
  getsysprNew(5,form_dat,&pr_mode,&prtnr); PrintPaperNr=0;
  if ((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1); prttext("<t33b>Niet gevonden artikels");
  prttext("<b><t55>"); prtfld(25,2,-1); prttext("<t72>Blz.<ppp>.");
  prtbuf(1);
  scrnum=0;scrget(1,170); scrifld(2,fm_os38,"Verwerken artikel : ");scrupd(-3,0);
  fasinit(80);cnt_good=0;cnt_bad=0;
  FOREVER{
    next:;
    if(read_rec(mode_)) break;mode_=1;
    fasinit(6);
    get_str(s(6,2),0,fldlen(6,2)); if(*s(6,2)=='\0') goto next; // code
    get_str(s(6,3),1,fldlen(6,3)); 
		if(*s(6,2)=='\0') goto next;
		qlv_=get_num(2);
		if(faskeyi(6,1,0)){
			prttext("Code : ");prtfld(6,2,-1);
      prttext("Aantal :");prtifld(fm_of6_2,&qlv_,-1);
      prtline();cnt_bad++;
      goto next;
    }
		if(fldlen(66,1)){
			fasinit(66);*u(66,2)=*pu_6_1;
			if(faskeyi(66,1,0)){fasinit(66);*u(66,2)=*u(6,1);}
		}
    *p_stock_+=qlv_;
		fasupd(6);cnt_good++;
		if(fldlen(66,1)){if(*u(66,1)) fasupd(66); else fasadd(66);}
    scrfld(5,6,2); scrfld(6,6,3);scrifld(10,fm_of6_2,&qlv_);
    scrfld(13,6,33);scrupd(-3,0);
  }
  fasclos(-2);
  prtform(0);prtclose();
  scrnum=0;
  scrget(1,170);
  scrifld(5,fm_os63,"Aantal goed verwerkte artikels : ");
  scrifld(6,fm_ou5,&cnt_good);
  scrifld(8,fm_os63,"Aantal NIET verwerkte artikels : ");
  scrifld(9,fm_ou5,&cnt_bad);
  scrifld(15,fm_os63,"Druk op F8 om verder te gaan ... ");
  scrupd(-1,0x81);
  endsr:;
}

static exec_barc()
{
  int16 g;
								
  if(werkveld[0]<'0' || werkveld[0]>'9'){
    fasinit(6);copy(werkveld,s(6,3),30);
    search(6,0);
		if(fldlen(66,1)){
			fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
		}
  }
  else{
		if(fldlen(64,2)){
			fasinit(64);copy(werkveld,s(64,2),fldlen(64,2));
			g=faskeyi(64,1,0);
			if(g==0){
				fasinit(6);*u(6,1)=*u(64,3); g=fasgeti(6);
				if(g==0){
					zero(werkveld,sizeof werkveld); 
					if(fldlen(66,1)){
						fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
					}
					if(*u(64,5)==1) return 2; else return 1;
				}
			}
		}
    fasinit(6);copy(werkveld,s(6,70),fldlen(6,70));
    g=faskeyi(6,10,0);
    if(g){
      fasinit(6);copy(werkveld,s(6,71),fldlen(6,71));
      g=faskeyi(6,11,0);
      if(g) errnum=g;
      else {
				zero(werkveld,sizeof werkveld); 
				if(fldlen(66,1)){fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);}
				return 2;
			}
    }
    else {
			zero(werkveld,sizeof werkveld); 
			if(fldlen(66,1)){fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);}
			return 1;
		}
  }
  if(errnum==0) {
		if(fldlen(66,1)){
			fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
		}
		zero(werkveld,sizeof werkveld);
	}
  else {fasinit(6);screrr(-1);return NO;}
  return YES;
}

static stock2stks(stock_,qst_,bak_,fls_)
float stock_,qst_,*bak_,*fls_;
{
 float add_;
  
  if(qst_<1) qst_=1;
  *bak_=(long)(stock_); *fls_=0;
	add_=0.49; if(stock_<0) add_=-0.49;
  if(qst_>1 && stock_!=0){
    *fls_=(long)(((stock_- *bak_) * qst_)+add_);
  } else *fls_=0;
}

static stks2stock(stock_,qst_,bak_,fls_)
float *stock_,qst_,bak_,fls_;
{
  if(qst_<1) qst_=1;
  *stock_=bak_+ fls_/qst_;
}

static exec_work()
{
  int16 k,mode_,ok_;

  if(werkveld[0]=='\0') return NO;
  fasinit(6); copy(werkveld,s(6,2+(sort_key-1)),30); mode_=1;
  scrget(1,7);scrupd(-3,0); ok_=NO;
  FOREVER{
    next:;
    if(faskeyi(6,sort_key,mode_)) break; mode_=2;
    if(inq_art && *u(6,1)!=inq_art) break;
    if(inq_lev && *u(6,7)!=inq_lev) goto next;
    if(inq_groep && *u(6,9)!=inq_groep)  goto next;
    if(selec_tst()==NO) goto next;
    ok_=YES;break;
  }
  zero(werkveld,sizeof werkveld);
  if(ok_==NO) return NO;
  for(k=0;k<DIM_REC;k++){
    if(tb[k].rec==0) break;
    if(tb[k].rec==*u(6,1)) break;
  }
  if(tb[k].rec==*u(6,1)) start=k;
}
 
static add_str(pd_,ps_,len_)
char *pd_,*ps_;
int16 len_;
{
  int16 k,add_sp_=NO;
							
  for(k=0;k<len_;k++){
    if(*(ps_+k)=='\0') add_sp_=YES;
    if(add_sp_) *(pd_+k)=' ';
    else *(pd_+k)=*(ps_+k);
  }
  return k;
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;
  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}

static kop_inv()
{
  int16 curs,key,z;
  char choice;
  uint16 dt_old,dt_new=0;

  if(fldlen(6,63)==0) {errnum=12;goto endsr;}
  sysget(3626,2,&dt_old);
  choice='N'; add_fstk='N';
  curs=1;
  FOREVER{
    redo:
    scrget(3,10);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_odat,&dt_old);
    scrifld(z++,fm_uJN,&choice);
    scrifld(z++,fm_udat,&dt_new);
    if(fldlen(66,1)) scrifld(z++,fm_uJN,&add_fstk); else streepje(z++);
    key=scrupd(curs,0x04A1);curs=1;
    if(key==101 || key==106) goto endsr;
    if(key==111) ovlexit(-1);
    if(dt_new==0) {errnum=38;curs=4;goto redo;}
    if(choice!='J') {errnum=34;goto redo;}
    if(key==108){
      copy_inv();
      sysput(3626,2,&dt_new);
      break;
    }
  }
  endsr:;
}

static copy_inv()
{
  uint16 j,used,mode_,arec_,NOstock_;
	float stock_,q_stuks_;
 
  fasunlck(-2);
	scrnum=0;scrget(1,170);
  scrifld(10,fm_os79,"    De inventarisstock wordt nu gekopieerd.");
  fasinfo(6,1);
  used=*u(6,1);kdsp=0;kdsp_off=1;
  for(arec_=1;arec_<=used;arec_++){
    dsp_working();
    *u(6,1)=arec_;
    if(fasgetu(6)) continue;
		stock_=0;q_stuks_=*f(6,31); if(q_stuks_==0) q_stuks_=1.; NOstock_=NO;
		if(fldlen(6,102)){
			if(*u(6,102)==0){// stock mogelijke deelverpakkingen optellen 
				fasinit(6);*u(6,102)=arec_;mode_=1;
				FOREVER{
					if(faskeyi(6,15,mode_)) break; mode_=2;
					if(*u(6,102)!=arec_) break;
#if FLAGSAS | FLAGGRS  | FLAGALB  | FLAGAST
		      if(YES){  // gekoppeld, altijd moederfiche bijwerken
#else
					if(q_stuks_!=*f(6,31)){ // ENKEL indien verschillende verpakking om te vermijden dat gekoppelde bakken ook samengeteld worden
#endif
						stock_+=*f(6,33) * *f(6,31)/ q_stuks_;
						if(fldlen(66,1) && add_fstk=='J') {
							fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
							for(j=0;j<10;j++) {
								if(fldlen(66,11+j*15)) stock_+=*f(66,11+j*15) * *f(6,31)/ q_stuks_;
         			}
						}
					}
				}
				fasinit(6);*u(6,1)=arec_;fasgeti(6);
			}
			else{ //  deelverpakking: inventaris wissen (wordt geteld bij bij hoofdartikel)
				*u(6,1)=*u(6,102); fasgeti(6);
#if FLAGSAS | FLAGGRS  | FLAGALB  | FLAGAST
		    NOstock_=YES; // gekoppeld, altijd moederfiche bijwerken
#else
				if(q_stuks_!=*f(6,31)) NOstock_=YES;
#endif
				fasinit(6);*u(6,1)=arec_;fasgeti(6);
			}
		}
		*f(6,63)=stock_;
    if(fldlen(6,33)) *f(6,63)+=*f(6,33);
    if(fldlen(66,1) && add_fstk=='J') {
	    fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
	    for(j=0;j<10;j++) {
	      if(fldlen(66,11+j*15)) *f(6,63)+=*f(66,11+j*15);
    	}
    }
		if(NOstock_) *f(6,63)=0;  // inventaris van deelverpakking wissen (wordt geteld bij bij hoofdartikel)
	  if(fldlen(6,64)){
			if(fldlen(6,34) && ((sys3766 & 1)==0)) *f(6,64)=*f(6,34);
			else if(sys3766 & 2) *f(6,64)=*f(6,12);
			else if(sys3766 & 4) *f(6,64)=*f(6,21);  // kleinhandel : ap=vp
#if FLAGAST // in firma FFC bedragen zonder accijns
      else if(sys2696 && *f(6,18)>*f(6,30)) *f(6,64)=*f(6,18)-*f(6,30);
#endif
			else *f(6,64)=*f(6,18);
    }
    fasupd(6);
  }
  fasflush(0);
	fasunlck(-1);
}

static corr_bstock()
{
  int16 key,z,curs=1,g,mode_;
  uint16 dt_bonb=0,dt_bone=0,n=0;
  char add_bstk;
  float qlv_,q_bons_;

  if(fldlen(8,1)==0) goto endsr;
  inq_loc=99;add_bstk='A';dt_bone=*u(25,2);
  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,4,25,3);
    scraddf(z++,6, 5,0);scraddf(z++,6,57,2);
    scraddf(z++,8,5,0);scraddf(z++,8,21,2);
    scraddf(z++,8,30,0);scraddf(z++,8,37,2);
    scraddf(z++,23,1,8);scraddf(z++,23,11,8);

    z=1;
    scrifld(z++,fm_os79,"Corrigeren stock met aantal op bons");
    scrifld(z++,fm_os79,"Bonaantal Optellen (O) of Aftrekken (A) van stock :");
    scrifld(z++,fm_uOA,&add_bstk);
    scrifld(z++,fm_os79,"Periode bons :");
    scrifld(z++,fm_udat,&dt_bonb);
    scrifld(z++,fm_os9,"t.e.m.");
    scrifld(z++,fm_udat,&dt_bone);
    scrifld(z++,fm_os9," F1 stop");scrifld(z++,fm_os13," F8 neem aan");
    key=scrupd(curs,0x81);curs=1;
    if(key==101) goto endsr;
    if(key==108){
      if(scr_ok("Wenst U echt de stock te wijzigen met aantallen op bons ?")==YES) break;
    }
  }

	fasunlck(-2);
  scrget(1,7);scrupd(-3,0);
  fasinit(6);
  n=0;scrnum=0;
  FOREVER{
    *u(6,1)=++n; dsp_working();
    g=fasgeti(6);
    if(g==47)break;
    if(g!=46){/* deleted record */
      q_bons_=0;
      fasinit(58);*u(58,14)=n;mode_=1;
      FOREVER{
	next58:;
	if(faskeyi(58,2,mode_)) break; mode_=2;
	if(*u(58,14)!=n) break;
	fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
	if(dt_bonb && *u(8,8)<dt_bonb) goto next58;
	if(dt_bone && *u(8,8)>dt_bone) goto next58;
	if(fldlen(8,36) && *u(8,36)) goto next58;
	qlv_=*f(58,31);
	if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
	q_bons_+=qlv_;
      }
      if(add_bstk=='A') q_bons_=-q_bons_;
      *f(6,33)+=q_bons_;
      fasupd(6);
    }
  }
  fasflush(0);
	fasunlck(-1);
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

static dsp_working()
{
  rec_working++;
  if((rec_working%1000)==0){
    if(kdsp_off==-1){if((kdsp%10)!=9) disp_str[kdsp]=' ';}
    else {if((kdsp%10)==9) disp_str[kdsp]='|'; else disp_str[kdsp]='*';}
    scrifld(22,fm_os63,disp_str);
    kdsp+=kdsp_off;
    if(kdsp>=50){kdsp--;kdsp_off=-1;}
    else if(kdsp<0) {kdsp=0;kdsp_off=1;}
		scrupd(-3,0);
  }
}

static DisplayMenuTitel(ypos_,tekst_,attrib_)
int ypos_;
char *tekst_,attrib_;
{
  int len_,beg_;
	char dsptekst_[100];
   
	zero(dsptekst_,sizeof dsptekst_);dsptekst_[0]=' ';
  for(len_=0;len_<80;len_++){
		if(tekst_[len_]=='\0') break;
		dsptekst_[len_+1]=tekst_[len_];
	}
	len_+=1;dsptekst_[len_++]=' ';if(len_>80) len_=80;
  beg_=(80-len_)/2; if(beg_<1) beg_=1; 
	scraddfield(200,beg_,ypos_,attrib_);scrifld(200,VarTextFmt(len_,0),dsptekst_);
}

static initload()
{
  int16 g,k;
 
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  if(fldlen(8,1)) fileopen(8);
  fileopen(9);
  if(fldlen(6,2)) arcd=2; else arcd=1;
  if(fldlen(66,1)) fileopen(12);
  if(fldlen(60,1)) fileopen(14);

  sysget(1918,2,&sear_stt);
	sysget(2696,2,&sys2696);
  sysget(3766,2,&sys3766);
  sysget(3876,2,&sys3876);
	sysget(4408,2,&sys4408);
  sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4254,40,(char *)&dt_kvk[0]);
  sysget(4294,40,(char *)&loc_klt[0]);
  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);
  dat_st_0=*u(25,2);

  sysget(3678,2,&def_taal);
  pu_6_1=u(6,1);
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;
  barc_used=NO;
  if(fldlen(6,70) && faskeyi(6,10,0)!=45) barc_used=YES;
  if(fldlen(6,71) && faskeyi(6,11,0)!=45) barc_used=YES;
  if(faskeyi(6,6,0)==45){/* controle op key plaats magazijn */
    for(k=0;k<sizeof fm_u_AKP;k++) if(fm_u_AKP[k]=='P') fm_u_AKP[k]='A';
  }
  zero((char *)&tbgr[0].rec,sizeof tbgr);
  p_max_grp=0;sgrp_used=NO;
  for(k=1;k<100;k++){
    fasinit(52);*u(52,1)=k;
    g=fasgeti(52);
    if(g==0 && *s(52,14)) tbgr[p_max_grp++].rec=k;
  }
  for(k=0;k<100;k++) tbgr[k].select='J';
}

static seqo_fld(stu_,fld_)
int16 stu_,fld_;
{
  if(fldlen(stu_,fld_)){
    fmt_get(fmt,stu_,fld_);
    seqo_var(fmt,s(stu_,fld_));
  }
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
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fm_[1]==0xD1 || fm_[1]==0x91){/* integer */
    fbd_=*(int16 *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fm_[1]==0xD3 || fm_[1]==0x93){/* long */
    fbd_=*(long *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fm_[1]==0xD4 || fm_[1]==0x94){/* float */
    fbd_=*(float *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fm_[1]==0xD5 || fm_[1]==0x95){/* double */
    fbd_=*(double *)pvar_;
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fm_[1]==0xC0 || fm_[1]==0x80){/* date */
    if(*(uint16 *)pvar_==0) seqo_str[pos++]=0x09;
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
  if(len_){
    copy(ps_,&seqo_str[pos],len_);while(seqo_str[pos]) pos++;
    for(k=orig_pos_;k<pos;k++){
      if(seqo_str[k]==0x09) seqo_str[k]='.';/* delete | */
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;/* delete trailing blanks */
    pos++;
  }
  seqo_str[pos++]=0x09;
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
  if(bd_<0 && value==0) seqo_str[pos++]='-'; // probleem teken bij 0,xxx
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
 
static seqo_flush()
{
  if(seqo_len){
    fasseqo(80,seqo_mode,seqo_len+4);
    seqo_pos+=seqo_len;
    *l(80,1)=seqo_pos;
    seqo_len=0;
  }
}



static dsp_tabel(type_)
int16 type_;/* 0=leveranciers, 1=groepen */
{
  int16 k,key,z,start=0,startpos,p_tb,curs=1,q_y,q_n,stu_,curspos_;
  char *pd;
					
  stu_=52;startpos=0; p_tb=p_max_grp;
  start=startpos; pd=oldnm;
  FOREVER{
    redo:;
    scrnum=0;scrget(3,15);z=1;
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
		 pd+=add1str(pd,15,52,14,'\0');
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

static add1str(pd,len_,stu_,nr_,kar_)
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
 
// import-routines
static ele_len(nr_)
int16 nr_;
{
  int16 k=0;
  char *p;

  p=rec_ele(nr_);
  FOREVER{
    if(*p==0x09 || *p==0x0D || *p==0x0A || *p=='\0') return k;
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
      if(*p==0x09 || *p==0xD || *p=='\0') break;
      p++;
    }
    p++;
  }
  return p;
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
 
static float get_num(nr)/* read number starting at pos  */
int16 nr;
{
  int16 j=0,k=0,n;
  float val_=0,val1_;
  flag na_komma=NO,neg_get=NO;
  char *pos;
 
  pos=rec_ele(nr);
  FOREVER{
    if(*(pos+k)==0x09 || *(pos+k)==0x0D) break;
    if(*(pos+k)=='.' || *(pos+k)==',') na_komma=YES;
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
  int16 j,k,len_;
  char *pos_;

  len_=ele_len(nr_);if(len_>mlen_) len_=mlen_;
  pos_=rec_ele(nr_);
  j=len_;
  for(k=0;k<j;k++){
    if(*pos_!=' ') break;
    pos_++; len_--;
  }
  copy(pos_,ps_,len_);
  for(k=len_-1;k>=0;k--) if(*(pos_+k)>' ') break;
  for(j=k+1;j<len_;j++) *(ps_+j)='\0';
  CnvJamaChar(ps_,len_,1);
  return k+1;
}






//////



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

static selec_tst()
{
  int16 k;
								
  if(sgrp_used){
    for(k=0;k<p_max_grp;k++) if(*u(6,9)==tbgr[k].rec) break;
    if(k>=p_max_grp || tbgr[k].select!='J') return NO;
  }
  return YES;
}

static upd_loc()
{
  int16 k,z,key,curs=1;
  char *pdum,dumm_[10],*pvar;
						
  sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4254,40,(char *)&dt_kvk[0]);
  sysget(4294,40,(char *)&loc_klt[0]);
  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);

  pdum=&dumm_[0];
  ram_recl=s(2,4)-s(2,1) + 2;/* + 2 bytes hash */
  hash_len=fldlen(2,1)+ fldlen(2,2)+fldlen(2,3);
  dat_len=hash_len;
  zero(ram,sizeof ram);
  for(k=0;k<10;k++){
    fasinit(2);*u(2,1)=loc_klt[k];fasgeti(2);
    hash_val=hash(2);
    stu2ram(2,k);
    if(loc_nr[k]==0){
      if(fldlen(66,11+k*15)>0) loc_nr[k]=k+1;
      else loc_nr[k]=99;
    }
  }

  FOREVER{
    redo:;
    scrget(3,16);z=1;
    for(k=0;k<10;k++){
      scrifld(z++,fm_us6,nm_kassa[k]);
      scrifld(z++,fm_udat,&dt_kvk[k]);
      if(fieldspc(2,3,&pdum,fmt)>0){
	pvar=ram+(k*ram_recl + (s(2,3)-s(2,1)));
	scrifld(z++,fmt,pvar);
      }
      if(fldlen(66,1)) scrifld(z++,fm_uu2,&loc_nr[k]);
      else scrifld(z++,fm_os2,"99");
    }
    for(k=0;k<10;k++){
      if(fldlen(66,11+k*15)){
	scrifld(z++,fm_us6,nm_loc[k]);
      } else z++;
    }
    key=scrupd(curs,0x1A1);curs=1;
    if(key==111) ovlexit(-1);
    if(key==106) break;

    for(k=0;k<10;k++){
      ram2stu(2,k);
      if(nm_kassa[k][0]!='\0' && (*s(2,3)=='\0' || hash_val!=hash(2))){
	if(search(2,0)){
	  errnum=39;curs=3+k*4;goto redo;
	}
	hash_val=hash(2);
      }
      else if(*s(2,3)=='\0'){fasinit(2);hash_val=0;}
      loc_klt[k]=*u(2,1);
      if(fldlen(66,1)==0) loc_nr[k]=99;
      else{
	if(loc_nr[k]>=1 && loc_nr[k]<=10){
	  z=loc_nr[k]-1;
	  if(fldlen(66,11+z*15)==0) {errnum=34;curs=4+k*4; goto redo;}
	}
	else loc_nr[k]=99;
      }
      stu2ram(2,k);
    }

    if(key==101 || key==108){
      sysput(4134,120,(char *)&nm_kassa[0][0]);
      sysput(4254,40,(char *)&dt_kvk[0]);
      sysput(4294,40,(char *)&loc_klt[0]);
      sysput(2730,40,(char *)&loc_nr[0]);
      sysput(2770,60,(char *)&nm_loc[0][0]);
      break;
    }
  }
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

static fmt_get(pfmt,stu_,elet_)
int16 stu_,elet_;
char *pfmt;
{
  int16 k;
  char *pdum,dummy_[10];

  pdum=&dummy_[0];
  k=fieldspc(stu_,elet_,&pdum,pfmt);
  if(k>0) return k;
  return 0;
}

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
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
  if(stu_!=6) parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}