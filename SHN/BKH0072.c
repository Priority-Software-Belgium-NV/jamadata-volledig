/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0072GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0072dat
#define ovlcod BKH0072cod
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

char ovldat[] = "bkh0072  00:35 19/03/10 (c) Jamadata";
/* automatische overschrijving via banksoft (oa Isabel) */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DIM_SEPA        43 // excl. BE want die wordt als Belgisch nummer doorgegeven
#define MINFREE         200
#define TABSIZ          500
#define MAXFK           8/* max fact. met 1 overschr. te betalen */
#define MAXKN           8/* max KN hierin te verrekenen */
#define MAXLEN          30
#define WRK_REF         72/* referentie nummer van wrk-blokken */
#define flag            uint16
#define C1              256E0
#define C2              65536E0

// FLAGCOC : uitschrijven op SERVER in map ..\CODA_UIT\

static char XMLfas2sif[32]  = {'a','a','a','a','c','e','e','e','e','i','i','i','i', // enkel conversie naar letters a,u,i,o,...
			                      'o','o','o','o','u','u','u','u','U',' ',' ',' ',' ',' ',' ',' ',' ',' ','E'};

static char *sepa_land[DIM_SEPA]={"BE","BG","CY","DK","DE","EE","FI","FR","GR","GB","HU","IE","IS","IT","LV","LI","LT","LU",
															"MT","MC","NL","NO","AT","PL","PT","SK","RO","SI","ES","CZ","SE","CH","AD","BA","FO","GL",
															"HR","MK","MU","SM","RS","TN","TR"};
static struct _st {
  long rec4;
  uint16 jr;
  uint16 vl;
  uint16 ft_date;
  uint16 verv_dat;
  uint16 verv_disk;
  double ebedr;
  double bd_vrm_mnt;
  double ebd_disk;
  double bd_disk_vm;
  char munt[3];
  uint16 r_yy;
  uint16 r_jr;
  uint16 r_vl;
  char typ;                                     /* 1=ft, 2=kn, 3=bet, 4=div */
  char status;   /* 0=n.verv/n.vold 1=n.verv/vold 2=verv/n.vold 3=verv/vold */
  double bd_tebet;
  uint16 lev_rec;
  char mode_VD;
  char dum;
} st[TABSIZ],st_ovr[MAXFK+MAXKN],fullst[TABSIZ*2];

static struct _fak {
  uint16 elem;
  double bedr;
} fak[TABSIZ];

static struct{
  char rekening[15];
  uint16 journal;
  char kod_fin[3];
  char inschrnr[10];
  char filnam[30];
  char Iban[39];
  char Bic[11];
} tb_bank[3];  // totaal 3x110 bytes


extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

extern struct{
  char fval[4];
  char tval[4];
  double coef;
} vtab[30];

extern char *s();
extern int16 *i();
extern uint16 *u(),dateadd();
static uint16 getgrb();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();

static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us25[]  = {7,0xC8,25,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_us25U[]= {7,0xC8,25,0,1,0,0};
static char fm_us11U[]= {7,0xC8,11,0,1,0,0};
static char fm_us3[]   = {7,0xC8,3,0,0,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os14[]  = {7,0x88,14,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ol9[]   = {6,0x93,9,0,0x70,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_ud9_0[] = {6,0xD5,9,0,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_od92_[] = {6,0x95,9,2,0x60,0};
static char fm_od7_2[] = {6,0x95,7,2,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_od62_[] = {6,0x95,6,2,0x60,0};
static char fm_od9_0[] = {6,0x95,9,0,0x70,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};

static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_udatw[] = {4,0xC0,0xE,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_u_13[]  = {9,0xC8,1,0,1,0,'1','3',0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_u_BEV[]  = {13,0xC8,1,0,1,0,'B','B','E','E','V','V',0};
static char fm_u_EF[]  = {11,0xC8,1,0,1,0,'E','E','F','F',0};

static uint16 rec_d_ak, rec_d_vk,rec_d_fi;
static long grb_d_ak, grb_d_vk,grb_d_fi;


static int16 form_dat[8],pr_mode,free,prtnr;
static int16 loaded,fullloaded,j_tb[101],bet_q;
static int16 fk1,fk2,actu_ln,sys_adr,nr_bank;
static int16 bet_tab[MAXFK+MAXKN],bet_res[MAXFK+MAXKN+1];
static int16 prt2pdf;
static uint16 dt_ovr,vdat_beg,vdat_end,ref_yy,ref_jr,ref_vl;
static uint16 rf_yy,rf_jr,rf_vl,recnr_ovr,recnr_disk,last_arc,MinBkhDatum,rec_nr;
static uint16 vdisk_beg,vdisk_end,journl,aank_jrl[7],volgnr_ovr,ram_nr,inq_lev,len_mededeling;
static long levcent,tot_bef,firmbtwn;
static double bedr_dis,bedr_ovr,bedr_tbt,tot_disk,bd_bkh,tot_eur;
static double tot_ovr=0,fulltot_ovr=0;
static char ver_term[4],firma[256],rekening[14],filnam[15],fin_cod[3];
static char prt_disc,prt_verv,mededeling[200],insch_nr[10];
static char def_munt[4],disk_out='J',sel_rekening,boek_JN,bet_munt,bet_belg;
static double bd_vm_ovr,bd_lowest;
static char rek_kumul[15],fm_ubd[40],fm_obd[40];
static int16 seq_nr,r12_cnt,r1_cnt;

static char seqo_str[2000];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;



static flag sear_stt,lvcd,klcd,chk_btoeg=NO,full_list;
static flag stopflag;
static flag sys3876,sys1792;

ovlcod()
{
  int16 curs=1,k,z,z_bank,ShowIbanKey;
  long grb_,key;

  initload();

	ShowIbanKey=NO; full_list=NO;
  if(fldlen(1,12)==5){ // tijdelijk om conversie naar IBAN te doen
		for(k=0;k<3;k++) if(tb_bank[k].Iban[0]) break;
		if(k>=3) ShowIbanKey=YES;
	}
	zeroL(RamBon,RamBonSize); ram_nr=0; 
  dt_ovr=*u(25,2);vdat_beg=0;vdat_end=*u(25,2);
  vdisk_beg=*u(25,2);vdisk_end=*u(25,2);boek_JN='J';
  prt_disc='J';prt_verv='J';sel_rekening='1';
	bet_belg='E'; //if(sys1792 & 0x8) bet_belg='E';
  bet_munt='E';
  disk_out='J';fasunlck(-1);
  FOREVER{
    fasinit(1);
    redo:
    scrget(1,86);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0072A");
    scrifld(z++,fm_udat,&dt_ovr);
    scrifld(z++,fm_uJN,&prt_verv);
    scrifld(z++,fm_udat,&vdat_beg);scrifld(z++,fm_udat,&vdat_end);
    scrifld(z++,fm_uJN,&prt_disc);
    scrifld(z++,fm_udat,&vdisk_beg);scrifld(z++,fm_udat,&vdisk_end);
    scrifld(z++,fm_u_13,&sel_rekening);
    scrifld(z++,fm_uJN,&boek_JN);
    scrifld(z++,fm_uJN,&disk_out);
    scrfld(z++,1,3);
    z_bank=z;
    for(k=0;k<3;k++){
			scrifld(z++,fm_uu2,&tb_bank[k].journal);
      scrifld(z++,fm_us25U,tb_bank[k].Iban);
      scrifld(z++,fm_us11U,tb_bank[k].Bic);
      scrifld(z++,fm_us20,tb_bank[k].filnam);
    }
		if(ShowIbanKey) AddTextKey(z++,60,14,20,2,10001,"Controleer IBAN\nleveranciers",0x0000FF);
    key=scrupd(curs,0x781);curs=1;
		if((key/0x10000)>0) key/=0x10000;
		else if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==10001) {ConvertJamaRek2IBAN(); goto redo;}
		if(key==5050) goto redo; // link help 
    if(key==101 || key==111) goto endsr;
    if(dt_ovr<=last_arc || dt_ovr<=MinBkhDatum) {errnum=37;curs=1;goto redo;}
    if(sel_rekening>='1' && sel_rekening<='3') nr_bank=sel_rekening-'1';
    else {errnum=38;curs=9; goto redo;}
    if(*s(1,3)){
      if(search(1,0)) {curs=10;goto redo;}
    } else fasinit(1);
    inq_lev=*u(1,1);k=1;
		if(tb_bank[nr_bank].Iban[0]=='\0' || (k=IbanTools(tb_bank[nr_bank].Iban,tb_bank[nr_bank].Bic,0,0))) {
      errnum=34;curs=z_bank+k+nr_bank*4; goto redo;
    }
    if(tb_bank[nr_bank].Bic[0]=='\0') {
      errnum=38;curs=z_bank+2+nr_bank*4; goto redo;
    }
    if(boek_JN=='J'){
      journl=tb_bank[nr_bank].journal;
      if(journl==0){errnum=39;curs=z_bank+nr_bank*4; goto redo;}
      if(j_tb[journl]!=7) {errnum=7;curs=z_bank+nr_bank*4; goto redo;}
      for(k=0;k<80;k++){
				sysget(10240+k*80,2,&z);
				if(z==journl) break;
      }
      sys_adr=10260+k*80;
      sysget(sys_adr,2,&volgnr_ovr);
      sysget(sys_adr+2,4,&grb_);
      volgnr_ovr++; if(volgnr_ovr>65000) volgnr_ovr=1;
      fasinit(3);*l(3,2)=grb_;
      search(3,2);
      recnr_ovr=*u(3,1)+60000;
      if(errnum){
				if(errnum==39) errnum=28;
				curs=z_bank+nr_bank*4; goto redo;
      }
    }
    if(disk_out=='J'){
      if(tb_bank[nr_bank].filnam[0]=='\0'){errnum=38;curs=z_bank+3+nr_bank*4; goto redo;}
    }
    prt2pdf=NO;if(key==109) {prt2pdf=YES;key=108;}
    if(key!=108 && key!=110) goto redo;
		if(key==108) {full_list=NO;break;}
		if(key==110) {full_list=YES;break;}
  }
  for(k=0;k<3;k++){
    sysput(3250+k*110,110,(char *)&tb_bank[k].rekening[0]);
  }
  stopflag=NO;
  copy(fm_ud7_2,fm_ubd,sizeof fm_ud7_2);
  copy(fm_od7_2,fm_obd,sizeof fm_od7_2);
 
  if(inq_lev==0) exec_all();
  else{
		full_list=NO;
    FOREVER{
      exec_lev();
      fasinit(1);
      redo_lev:;
      scrget(1,211);z=1;
      scrfld(z++,1,3);
      key=scrupd(2,0x81);
      if(key==101) break;
      if(search(1,0)) {curs=2;goto redo_lev;}
      inq_lev=*u(1,1);
      if(key!=108) goto redo_lev;
    }
  }
  if(ram_nr==0) goto endsr;
  print_lst();
  redo_prt:;
  FOREVER{
    scrget(1,212);
    scrifld(1,fm_obd,&tot_ovr);
    key=scrupd(-1,0x38);
    if(key==105) break;
    if(key==104) print_lst();
    if(key==106) goto endsr;
  }
	if(disk_out=='J') {
		if(Ovr2Xml()==NO) goto redo_prt;
	}
  if(boek_JN=='J') boekbkh();
  endsr:;
  ovlexit(-1);
}

static exec_all()
{
	if(full_list==NO){
		fasinit(1);
		FOREVER{
			if(faskeyi(1,2,2)) break;
			exec_lev();
			if(stopflag) break;
		}
	}
	else{
		fasinit(1);fullloaded=0; zeroL((char *)&fullst[0].rec4,sizeof fullst);fulltot_ovr=0;
		FOREVER{
			if(faskeyi(1,2,2)) break;
			add_lev();
		}
		if(fullloaded){
			if(fullselect_ft()==NO) ram_nr=0;
		}
	}
}

static add_lev()
{
  int16 k,ks;
  uint16 searcnr;
  double bd_ltot_=0;

/* indien geen banknummer of DOM, dan niet overlopen */

  if(*s(1,18)=='\0' || cmpstr(s(1,18),"DOM",3)==0 || IbanTools(s(1,18),s(1,19),s(1,12),0)) goto endsr;/* geen  of foute IBAN of BIC */

  searcnr=*u(1,1)+(1-1)*30000;
   
  fasinit(4);
  *u(4,5)=*u(1,1);
  loaded=0; zeroL((char *)&st[0].rec4,sizeof st);
  FOREVER{
    ks=faskeyi(4,4,2);
    if(ks || *u(4,5)!=*u(1,1)) break;
    add_bew();
  }
  compress();/* schrap voldane stukken */
  bd_ltot_=0;
  for(k=0;k<loaded;k++) bd_ltot_+=st[k].ebedr;
  if(bd_ltot_<=0) {loaded=0;goto endsr;}/* lev. heeft meer KN dan FACT */
  munt_chk();/* schrap alle niet-EMU boekingen, of alle EMU's */
  jrnl_chk();/* scherm-gevraagde journalen only */
  datum_chk();/* schrap facturen buiten periode */
  bd_ltot_=0;
  for(k=0;k<loaded;k++) bd_ltot_+=st[k].ebedr;
  if(bd_ltot_<=0) {loaded=0;goto endsr;}/* lev. heeft meer KN dan FACT */
  drop_voors();/* drop voorschotten */
  bd_ltot_=0;
  for(k=0;k<loaded;k++) bd_ltot_+=st[k].ebedr;
  if(bd_ltot_<=0) {loaded=0;goto endsr;}/* lev. heeft meer KN dan FACT */
	for(k=0;k<loaded;k++){
    copy((char *)&st[k],(char *)&fullst[fullloaded++],sizeof(struct _st));
		if(fullloaded>=TABSIZ*2) break;
  }
  endsr:;
}

static fullselect_ft()
{
  int16 k,key,z,start=0,curs=1,yy_,lastk_,lastrec_;
  char t_ok[TABSIZ*2],fm_yy_[10];
  double totaal_,bd_;
					
  totaal_=0;
  for(k=0;k<fullloaded;k++){
    bd_=fullst[k].ebedr-fullst[k].ebd_disk;
    fullst[k].bd_tebet=bd_;
    totaal_+=bd_;t_ok[k]='J';
  }
  FOREVER{
    redo:;
    scrnum=0;scrget(1,118);z=1;
    bd_=fulltot_ovr+totaal_;
    scrifld(z++,fm_obd,&bd_);
 //   scrifld(z++,fm_obd,&totaal_);
    for(k=start;k<fullloaded;k++){
      scrifld(z++,fm_uJN,&t_ok[k]);
			fasinit(1);*u(1,1)=fullst[k].lev_rec;fasgeti(1);
			scrofld(z++,1,3,20);if(t_ok[k]=='J') scrchat(z-1,0x0A);
      scrifld(z++,fm_ou2,&fullst[k].jr);
			scrifld(z++,fm_ou5,&fullst[k].vl); if(fullst[k].typ==1 || fullst[k].typ==2) scraddpicto(10+k-start,z-1,0,0,2,1,141,0,6,"Bekijk factuur");
      scrifld(z++,fm_odat,&fullst[k].ft_date);
      scrifld(z++,fm_od62_,&fullst[k].ebedr); if(t_ok[k]=='J') scrchat(z-1,0x0A);
      copy(fm_ou2,fm_yy_,sizeof fm_ou2);/* y2000 */
      yy_=fullst[k].r_yy; if(yy_>=100) yy_-=100;
      if(fullst[k].r_jr || fullst[k].r_vl) fm_yy_[4]=0;
 //     if(t_ok[k]=='J'){
	//scrifld(z++,fm_ubd,&st[k].bd_tebet);
 //     }
 //     else{
	//scrifld(z++,fm_obd,&st[k].bd_tebet);
	//scrchat(z-1,0);
 //     }
      if(fullst[k].mode_VD=='D' && fullst[k].verv_disk){
      	scrifld(z++,fm_odat,&fullst[k].verv_disk); scrchat(z-1,0x08);
      }
      else if(fullst[k].verv_dat) scrifld(z++,fm_odat,&fullst[k].verv_dat);
      else z++;
      fasinit(4);*l(4,1)=fullst[k].rec4;fasgeti(4);
      if(*s(4,28)) scrofld(z++,4,28,14);
      else z++;
      if(k==start+17) break;
    }
    key=scrupd(curs,0xF6);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		prt2pdf=NO; 
		if(key==105)  for(k=0;k<fullloaded;k++) t_ok[k]='N';
		if(key>=5010 && key<5010+16) dsp_detail(start+key-5010,YES);
//    if(key==101) return NO; //fullloaded=0; scrget(1,7);scrupd(-3,0); stopflag=YES; goto endsr;}
    if(key==106) return NO; //{fullloaded=0; scrget(1,7);scrupd(-3,0); goto endsr;}
    if(key==102 && (start-17)>=0) {
      start-=17;
    }
    if(key==103 && (start+17)<fullloaded) {start+=17;}
    if(start<0) start=0;
    totaal_=0;
    for(k=0;k<fullloaded;k++){
      if(t_ok[k]=='J'){
				if(is_nul(fullst[k].bd_tebet)) t_ok[k]='N';
				totaal_+=fullst[k].bd_tebet;
      }
    }
		bd_=0;lastrec_=0;lastk_=0;
		for(k=0;k<fullloaded;k++){
			if(fullst[k].lev_rec!=lastrec_){
				if(bd_<0) {start=lastk_;k;errnum=52;goto redo;}
				lastk_=k;bd_=0;lastrec_=fullst[k].lev_rec;
			}
			if(t_ok[k]=='J') bd_+=fullst[k].bd_tebet;
		}
		if(bd_<0) {start=lastk_;k;errnum=52;goto redo;}
		if(key==108){
      if(totaal_<=0.01) {errnum=38; goto redo;}
      else break;
		}
  }
  for(k=0;k<fullloaded;k++){/* delete geschrapte facturen */
    if(t_ok[k]!='J'){
      del_fullbew(k); copy(&t_ok[k+1],&t_ok[k],TABSIZ*2-(k+1)); t_ok[TABSIZ*2-1]='\0';
      k--;
    }
  }
	bd_=0;lastrec_=0;loaded=0; zeroL((char *)&st[0].rec4,sizeof st);
	for(k=0;k<fullloaded;k++){
		if(fullst[k].lev_rec!=lastrec_){
			if(loaded){/* indien er bewegingen overschieten */
				compr_ref();/*  per referentie 1 st-lijn maken */
				FOREVER{
					if(make_ovr()==NO) break;/* get overschrijving */
					if(bedr_ovr>0){
						tot_ovr+=bedr_ovr;
						dump_tab();/* dump overgeschreven boekingen in wrk */
						del_tab();/* schrap overgeschreven boekingen */
					}
					else{
						del_stuk(0);
					}
				}
			}
		  loaded=0; zeroL((char *)&st[0].rec4,sizeof st);
			lastrec_=fullst[k].lev_rec;
		}
		if(t_ok[k]=='J') copy((char *)&fullst[k],(char *)&st[loaded++],sizeof(struct _st)); 
	}
  if(loaded){/* indien er bewegingen overschieten */
    compr_ref();/*  per referentie 1 st-lijn maken */
    FOREVER{
      if(make_ovr()==NO) break;/* get overschrijving */
      if(bedr_ovr>0){
				tot_ovr+=bedr_ovr;
				dump_tab();/* dump overgeschreven boekingen in wrk */
				del_tab();/* schrap overgeschreven boekingen */
      }
      else{
				del_stuk(0);
      }
    }
  }
  endsr:;
  return YES;
}

static del_fullbew(line)
int16 line;
{
  int16 k;

  for(k=line;k<(fullloaded-1);k++){
    copy((char *)&fullst[k+1],(char *)&fullst[k],sizeof(struct _st));
  }
  fullloaded--;
}

static exec_lev()
{
  int16 k,ks;
  uint16 searcnr;
  double bd_ltot_=0;

/* indien geen banknummer of DOM, dan niet overlopen */

  if(*s(1,18)=='\0' || cmpstr(s(1,18),"DOM",3)==0 || IbanTools(s(1,18),s(1,19),s(1,12),0)) goto endsr;/* geen  of foute IBAN of BIC */

  searcnr=*u(1,1)+(1-1)*30000;
   
  fasinit(4);
  *u(4,5)=*u(1,1);
  loaded=0; zeroL((char *)&st[0].rec4,sizeof st);
  FOREVER{
    ks=faskeyi(4,4,2);
    if(ks || *u(4,5)!=*u(1,1)) break;
    add_bew();
  }
  compress();/* schrap voldane stukken */
  bd_ltot_=0;
  for(k=0;k<loaded;k++) bd_ltot_+=st[k].ebedr;
  if(bd_ltot_<=0) {loaded=0;goto endsr;}/* lev. heeft meer KN dan FACT */
  munt_chk();/* schrap alle niet-EMU boekingen, of alle EMU's */
  jrnl_chk();/* scherm-gevraagde journalen only */
  datum_chk();/* schrap facturen buiten periode */
  bd_ltot_=0;
  for(k=0;k<loaded;k++) bd_ltot_+=st[k].ebedr;
  if(bd_ltot_<=0) {loaded=0;goto endsr;}/* lev. heeft meer KN dan FACT */
  drop_voors();/* drop voorschotten */
  bd_ltot_=0;
  for(k=0;k<loaded;k++) bd_ltot_+=st[k].ebedr;
  if(bd_ltot_<=0) {loaded=0;goto endsr;}/* lev. heeft meer KN dan FACT */
  if(loaded) select_ft();
  if(loaded){/* indien er bewegingen overschieten */
    compr_ref();/*  per referentie 1 st-lijn maken */
    FOREVER{
      if(make_ovr()==NO) break;/* get overschrijving */
      if(bedr_ovr>0){
				tot_ovr+=bedr_ovr;
				dump_tab();/* dump overgeschreven boekingen in wrk */
				del_tab();/* schrap overgeschreven boekingen */
      }
      else{
				del_stuk(0);
      }
    }
  }
  endsr:;
}

static ConvertJamaRek2IBAN()
{
	uint16 n,g,k;

	if(DisplayWarning("Wenst U echt de IBAN en BIC in te vullen op leveranciersfiches?",61,1)==NO) return 0; 
  scrget(1,7);scrupd(-3,0);
	fileopen(1);
	n=0;
	FOREVER{
		next:;
		*u(1,1)=++n;
		g=fasgeti(1);
		if(g==47)break;
		if(g!=46){
			for(k=0;k<5;k++) if(*(s(1,12)+k)!='\0') break;
			if(*s(1,18)){
				if(IbanTools(s(1,18),s(1,19),s(1,12),1)==0) {fasupd(1);goto next;}
			}
			if(k<5) IbanTools(s(1,18),s(1,19),s(1,12),2); // Belgische invullen
			else{*s(1,18)=0; *s(1,19)=0;} // anders clearen
			fasupd(1);
		}
	}
}


static drop_voors()
{
  int16 k,last_k,ft_cn_ok;

  if(loaded==0) return NO;
  last_k=0;
  for(k=0;k<loaded;k++){
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;last_k=k;
    ft_cn_ok=NO;
    FOREVER{
      if(st[k].r_yy==ref_yy && st[k].r_jr==ref_jr && st[k].r_vl==ref_vl
      && k<loaded){
	if(j_tb[st[k].jr]<3) ft_cn_ok=YES;
	k++;
      }
      else break;
    }
    if(ft_cn_ok==NO){/* drop correcties en voorschotten */
      del_stuk(last_k);k=last_k;
    }
    k--;
  }
  return YES;
}

static chk_land(ps_)
char *ps_;
{
  int16 k;
 
  for(k=0;k<DIM_SEPA;k++) if(cmpstr(ps_,sepa_land[k],2)==0) break;
  if(k>=DIM_SEPA) return NO;
  return YES;
}
 
static compr_ref()/* per referentie 1 st-lijn maken met juiste bedrag */
{
  int16 k,last_k;
									
  if(loaded==0) return NO;
  for(k=0;k<loaded;k++){
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;last_k=k;
    FOREVER{
      if(st[k].r_yy==ref_yy && st[k].r_jr==ref_jr && st[k].r_vl==ref_vl
      && k<loaded){
	if(k>last_k){
	  st[last_k].bd_tebet+=st[k].bd_tebet;
	  st[last_k].ebd_disk+=st[k].ebd_disk;
	  st[last_k].bd_disk_vm+=st[k].bd_disk_vm;
	  del_bew(k);
	}
	else k++;
      }
      else break;
    }
    k--;
  }
}

static make_ovr()
{
  int16 k,m;
  char buffje[sizeof(struct _fak)];
  flag swapped=YES;

  if(loaded==0) return NO;
  bd_lowest=999999999;zeroL((char *)&bet_res[0],sizeof bet_res);
  zeroL((char *)&fak[0].elem,sizeof fak);
  fk1=0;fk2=TABSIZ-1;/* bereken bedrag per referentie */
  for(k=0;k<loaded;k++){/* en stop ze in tabel fak[] */
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
    if(st[k].bd_tebet>0) m=fk1++;/* fact vooraan */
    else m=fk2--;/* KN achteraan */
    fak[m].bedr=st[k].bd_tebet;fak[m].elem=k;
  }
 
/* sort KN : grootste negatieve voorop */
  while(swapped){/* gaat achteraf grootste KN eerst */
    swapped=NO;/*  proberen te verrekenen */
    for(k=fk2+1;k<TABSIZ-1;k++){
      if(fak[k].bedr>fak[k+1].bedr){
				copy((char *)&fak[k],buffje,sizeof(struct _fak));
				copy((char *)&fak[k+1],(char *)&fak[k],sizeof(struct _fak));
				copy(buffje,(char *)&fak[k+1],sizeof(struct _fak));
				swapped=YES;
      }
    }
  }
 
  zeroL((char *)&bet_res[0],sizeof bet_res);
  zeroL((char *)&bet_tab[0],sizeof bet_tab);
  bet_q=probeer(0,0);/* zoek combinatie voor kleinste overschrijvingsbedr */
  if(bet_q==0){
    bet_q=bet_res[0];copy(&bet_res[1],&bet_tab[0],sizeof bet_tab);
    if(bet_q==0) return NO;
  }

/* in bet_tab zitten bet_q elementen, die mogen betaald worden */
  bedr_ovr=0;tot_disk=0;bd_vm_ovr=0;/* bereken bedrag overschrijving */
  for(k=0;k<bet_q;k++){
    bedr_ovr+=fak[bet_tab[k]].bedr;
  }
  return YES;
}

static probeer(niv_,start_)
int16 niv_,start_;
{
  int16 j,k,qbet_,kn_accept_;
  double bedr_;

  for(k=start_;k<fk1;k++){
    bet_tab[niv_]=k;
    qbet_=niv_+1;
    if(fk2==TABSIZ-1) return 1;/* geen KN */
    bedr_=0;for(j=0;j<qbet_;j++) bedr_+=fak[bet_tab[j]].bedr;
    kn_accept_=NO;
    for(j=fk2+1;j<=TABSIZ-1;j++){
      if((bedr_+fak[j].bedr)>0){
				bedr_+=fak[j].bedr;
				bet_tab[qbet_++]=j;
				kn_accept_++;
      }
      if(kn_accept_==MAXKN) return qbet_;
    }
    if(kn_accept_){
      bedr_=0;for(j=0;j<qbet_;j++) bedr_+=fak[bet_tab[j]].bedr;
      if(bedr_>0){
				if((qbet_-niv_-1)==((TABSIZ-1)-fk2)) bedr_-=1000000;/* bonus */
				if(bedr_<bd_lowest){
					bet_res[0]=qbet_;copy(&bet_tab[0],&bet_res[1],sizeof bet_tab);
					bd_lowest=bedr_;
				}
      }
    }
    if(niv_<(MAXFK-1)){
      j=probeer(niv_+1,k+1); if(j) return j;
    }
  }
  return NO;
}


static add_bew()
{
  int16 k,typ;
									
  if(loaded==TABSIZ) compress();
  if(loaded==TABSIZ) goto endsr;
									
  zeroL((char *)&st[loaded],sizeof st[0]);
									
  st[loaded].rec4=*l(4,1);
  st[loaded].jr=*s(4,2);
  st[loaded].vl=*u(4,3);
  st[loaded].ft_date=*u(4,4);
  st[loaded].ebedr=-*d(4,32);
  st[loaded].r_yy=*s(4,8);
  st[loaded].r_jr=*s(4,9);
  st[loaded].r_vl=*u(4,10);
  st[loaded].lev_rec=*u(1,1);
  k=j_tb[st[loaded].jr];
  if(k<3 || k>8){
    if(st[loaded].ebedr<0) typ=2; else typ=1;
  }
  else if(k<5) typ=3;
  else typ=4;
  st[loaded].typ=typ;
  if(typ<3){
    st[loaded].verv_dat=*u(4,21);
    st[loaded].bd_vrm_mnt=-*d(4,25);
    if(prt_disc=='J' && *u(4,22)>=vdisk_beg && *u(4,22)<=vdisk_end){
      st[loaded].verv_disk=*u(4,22);
      st[loaded].bd_disk_vm=*f(4,26);/* ook BEF ! */
      st[loaded].ebd_disk=*d(4,34);
      if(is_nul(st[loaded].ebd_disk)) st[loaded].verv_disk=0;
    }
    copy(s(4,24),st[loaded].munt,3);
    if(*u(4,20)) st[loaded].ft_date=*u(4,20);
    if(st[loaded].verv_dat==0){
      copy(s(1,13),ver_term,4);
      ver_term[3]='\0';
      st[loaded].verv_dat=dateadd(st[loaded].ft_date,ver_term);
    }
    if(st[loaded].ebd_disk<=0.01) st[loaded].verv_disk=0;
  }

  loaded++;
  endsr:;
}

static compress()
{
  int16 k,n;
  double ebd_;

  if(loaded==0) goto endsr;
  ebd_=0;for(k=0;k<loaded;k++) ebd_+=st[k].ebedr;
  if(is_nul(ebd_)) {loaded=0;goto endsr;}

  for(k=0;k<loaded;k++){
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
    ebd_=0;
    n=k-1;
    FOREVER{
      n++;
      if(n>=loaded) break;
      if(st[n].r_yy!=ref_yy || st[n].r_jr!=ref_jr || st[n].r_vl!=ref_vl) break;
      ebd_+=st[n].ebedr;
    }
    if(!is_nul(ebd_)){
      k=n-1;
    }
    else{
      FOREVER{/* schrap voldane */
	if(k==loaded) break;
	if(st[k].r_yy!=ref_yy || st[k].r_jr!=ref_jr || st[k].r_vl!=ref_vl) break;
	del_bew(k);
      }
      k--;
    }
  }
  endsr:;
}
 
static munt_chk()
{
  int16 k;

  for(k=0;k<loaded;k++){/* moet EUR zijn */
    if(j_tb[st[k].jr]<3){
      if(st[k].munt[0]=='\0') copy(def_munt,st[k].munt,3);
      if(bet_belg!='V' && cmpstr(st[k].munt,"EUR",3)){
	del_stuk(k);k--;
      }
    }
  }
}

static jrnl_chk()
{
  int16 g,k;

  for(k=0;k<loaded;k++){
    if(j_tb[st[k].jr]<3){
      for(g=0;g<7;g++){
	if(st[k].jr==aank_jrl[g]) break;
      }
      if(g==7) {del_stuk(k);k--;}
    }
  }
}

static datum_chk()
{
  int16 g,k,ft_kn_ok,ft_in_st;

  for(g=0;g<loaded;g++){
    ref_yy=st[g].r_yy;ref_jr=st[g].r_jr;ref_vl=st[g].r_vl;
    ft_kn_ok=NO;ft_in_st=NO;
    k=g;
    FOREVER{
      if(st[k].r_yy==ref_yy && st[k].r_jr==ref_jr && st[k].r_vl==ref_vl && k<loaded){
	if(j_tb[st[k].jr]<3){
	  ft_in_st=YES;
	  if(st[k].ebedr<0) ft_kn_ok=YES;/* KN steeds houden */
	  else{/* facturen */
	    if(prt_verv=='J' && st[k].verv_dat>=vdat_beg && st[k].verv_dat<=vdat_end){
	      st[k].mode_VD='V';
	      ft_kn_ok=YES;
	    }
	    if(prt_disc=='J' && st[k].verv_disk>=vdisk_beg && st[k].verv_disk<=vdisk_end){
	      st[k].mode_VD='D';
	      ft_kn_ok=YES;
	    }
	  }
	}
      }
      else{/* voorschotten laten staan (er moet een factuur inzitten) */
	if(ft_kn_ok==NO && ft_in_st==YES) {del_stuk(g);g--;}
	else g=k-1;
	break;
      }
      k++;
    }
  }
}

static dump_tab()/* schrijf alle st-records naar wrk */
{
  int16 j,k,n;
				
  zeroL((char *)&st_ovr[0].rec4,sizeof st_ovr);n=0;
  for(k=0;k<bet_q;k++){
    j=fak[bet_tab[k]].elem;
    copy((char *)&st[j].rec4,(char *)&st_ovr[n].rec4,sizeof st[0]);
    n++;
  }
  copy((char *)&st_ovr[0].rec4,&RamBon[(ram_nr*sizeof st_ovr)],sizeof st_ovr);
//  wrkwrite(WRK_REF,ram_nr,(char *)&st_ovr[0].rec4,sizeof st_ovr);
  ram_nr++;
}

static load_tab(nr_)/* schrijf alle st-records naar wrk */
int16 nr_;
{
  int16 k;
		
  zeroL((char *)&st_ovr[0].rec4,sizeof st_ovr);
  zeroL((char *)&st[0].rec4,sizeof st); bd_vm_ovr=0;bedr_tbt=0; bedr_dis=0;bet_q=0;
	copy(&RamBon[(nr_*sizeof st_ovr)],(char *)&st_ovr[0].rec4,sizeof st_ovr);
//  if(wrknread(WRK_REF,nr_,(char *)&st_ovr[0].rec4)==0) return YES;
  for(k=0;k<MAXKN+MAXFK;k++){
    if(st_ovr[k].rec4){
      copy((char *)&st_ovr[k].rec4,(char *)&st[bet_q].rec4,sizeof st[0]);
      bedr_tbt+=st[k].bd_tebet; bd_vm_ovr+=st[k].bd_vrm_mnt;
      bedr_dis+=st[k].ebd_disk;
      bet_q++;
    }
  }

					/* maak mededeling voor leverancier */
  zeroL(&mededeling[0],sizeof mededeling);len_mededeling=0;
  for(k=0;k<bet_q;k++){
    *l(4,1)=st[k].rec4;fasgeti(4);
    if(*s(4,27) && len_mededeling<140){
			if(len_mededeling) mededeling[len_mededeling++]='+';
			len_mededeling+=copy0(s(4,27),&mededeling[len_mededeling],15);
		}
    if(sys1792 & 1){
      if(*s(4,28) && len_mededeling<140){
			  if(len_mededeling) mededeling[len_mededeling++]='+';
			  len_mededeling+=copy0(s(4,28),&mededeling[len_mededeling],20);				
			}
    }
  }
  return NO;
}

static del_tab()
{
  int16 j,k;

  for(k=0;k<bet_q;k++){
    j=fak[bet_tab[k]].elem;
    st[j].rec4=0xFFFFFFFF;
  }
  for(k=0;k<loaded;k++){
    if(st[k].rec4==0xFFFFFFFF){
      del_stuk(k);k--;
    }
  }
}

static del_stuk(k)
int16 k;
{
  ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
  for(k=0;k<loaded;k++){
    if(st[k].r_yy==ref_yy && st[k].r_jr==ref_jr && st[k].r_vl==ref_vl){
      del_bew(k);
      k--;
    }
  }
}

static del_bew(line)
int16 line;
{
  int16 k;

  for(k=line;k<(loaded-1);k++){
    copy((char *)&st[k+1],(char *)&st[k],sizeof(struct _st));
  }
  loaded--;
}
 
static select_ft()
{
  int16 k,key,z,start=0,curs=1,yy_;
  char t_ok[TABSIZ],fm_yy_[10];
  double totaal_,bd_;
					
  totaal_=0;
  for(k=0;k<loaded;k++){
    bd_=st[k].ebedr-st[k].ebd_disk;
    st[k].bd_tebet=bd_;
    totaal_+=bd_;t_ok[k]='J';
  }
  FOREVER{
    redo:;
    scrnum=0;scrget(1,213);z=1;
    bd_=tot_ovr+totaal_;
    scrifld(z++,fm_obd,&bd_);
    scrofld(z++,1,3,-1);
    scrifld(z++,fm_obd,&totaal_);
    for(k=start;k<loaded;k++){
      scrifld(z++,fm_uJN,&t_ok[k]);
      scrifld(z++,fm_ou2,&st[k].jr);
			scrifld(z++,fm_ou5,&st[k].vl); if(st[k].typ==1 || st[k].typ==2) scraddpicto(10+k-start,z-1,0,0,2,1,141,0,6,"Bekijk factuur");
      scrifld(z++,fm_odat,&st[k].ft_date);
      scrifld(z++,fm_od6_2,&st[k].ebedr);
      copy(fm_ou2,fm_yy_,sizeof fm_ou2);/* y2000 */
      yy_=st[k].r_yy; if(yy_>=100) yy_-=100;
      if(st[k].r_jr || st[k].r_vl) fm_yy_[4]=0;
      if(t_ok[k]=='J'){
	scrifld(z++,fm_ubd,&st[k].bd_tebet);
      }
      else{
	scrifld(z++,fm_obd,&st[k].bd_tebet);
	scrchat(z-1,0);
      }
      if(st[k].mode_VD=='D' && st[k].verv_disk){
      	scrifld(z++,fm_odat,&st[k].verv_disk); scrchat(z-1,0x08);
      }
      else if(st[k].verv_dat) scrifld(z++,fm_odat,&st[k].verv_dat);
      else z++;
      fasinit(4);*l(4,1)=st[k].rec4;fasgeti(4);
      if(*s(4,28)) scrofld(z++,4,28,14);
      else z++;
      if(k==start+16) break;
    }
    key=scrupd(curs,0xF7);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		prt2pdf=NO; 
		if(key==105)  for(k=0;k<loaded;k++) t_ok[k]='N';
		if(key>=5010 && key<5010+16) dsp_detail(start+key-5010,NO);
    if(key==101) {loaded=0; scrget(1,7);scrupd(-3,0); stopflag=YES; goto endsr;}
    if(key==106) {loaded=0; scrget(1,7);scrupd(-3,0); goto endsr;}
    if(key==102 && (start-17)>=0) {
      start-=17;
    }
    if(key==103 && (start+17)<loaded) {start+=17;}
    if(start<0) start=0;
    totaal_=0;
    for(k=0;k<loaded;k++){
      if(t_ok[k]=='J'){
				if(is_nul(st[k].bd_tebet)) t_ok[k]='N';
				totaal_+=st[k].bd_tebet;
      }
    }
		if(key==108){
      if(totaal_<=0.01) {errnum=38; goto redo;}
      else break;
		}
  }
  for(k=0;k<loaded;k++){/* delete geschrapte facturen */
    if(t_ok[k]!='J'){
      del_bew(k); copy(&t_ok[k+1],&t_ok[k],TABSIZ-(k+1)); t_ok[TABSIZ-1]='\0';
      k--;
    }
  }
  endsr:;
  return NO;
}

static dsp_detail(p_rec4_,sel_fulltb_)
uint16 p_rec4_,sel_fulltb_;
{
  int16 z,k,key,start_=0,aard,mode_,ptb;
  double factor_;
  uint16 journl_,volgnr_,bk_dat_,kl_stu_;
  long mast4_;
  char buf4_[500];
	struct _fdet {
		double bedrag;
		char omschr[MAXLEN];
		char opmerk[20];
	} fdet[50];
	struct _j_tab {
		uint16 nr;
		uint16 typ;
	} j_tab[81];/* 1 extra element */

	copy(s(4,1),buf4_,fldlen(4,0));
	for(k=0;k<80;k++){
    sysget(10240+k*80,4,(char *)&j_tab[k]);
  }
  zeroL((char *)&fdet[0].bedrag,sizeof fdet);
  fasinit(4);
	if(sel_fulltb_) *l(4,1)=fullst[p_rec4_].rec4;
	else *l(4,1)=st[p_rec4_].rec4;
	fasgeti(4);
  journl_=*s(4,2);volgnr_=*u(4,3); bk_dat_=*u(4,4);
  for(k=0;k<80;k++) if(j_tab[k].nr==journl_) break;
  if(k>=80 || j_tab[k].typ<1 || j_tab[k].typ>2) goto endsr;/* enkel AK en VK */
  factor_=-1;aard=3; if(j_tab[k].typ<2) {aard=1;factor_=1;}
  fasinit(4);*s(4,2)=journl_;*u(4,3)=volgnr_; mode_=1; ptb=0;
  mast4_=0;kl_stu_=0;
  FOREVER{
    next4:;
    if(faskeyi(4,1,mode_)) break; mode_=2;
    if(*s(4,2)!=journl_ || *u(4,3)!=volgnr_) break;
    if(*u(4,4)!=bk_dat_) goto next4;
    if(fldlen(4,11)){
      if(*l(4,11)) goto next4;/* GEEN analytisch */
    }
    if(*u(4,5)<60000){
      if(kl_stu_==0){
	mast4_=*l(4,1);
	if(*u(4,5)<30001){
	  kl_stu_=1;
	}
	else{
	  kl_stu_=2;
	}
      }
      else{
	errnum=59;
	fdet[ptb].bedrag=*d(4,32)*factor_;
	if(*u(4,5)<30000){
	  fasinit(1);*u(1,1)=*u(4,5);fasgeti(1);
	  copy(s(1,3),fdet[ptb].omschr,30);
	}
	else{
	  fasinit(2);*u(2,1)=*u(4,5)-30000;fasgeti(2);
	  copy(s(2,3),fdet[ptb].omschr,30);
	}
	copy(s(4,28),fdet[ptb].opmerk,20);
	ptb++;
      }
    }
    else if(bk_dat_>last_arc){
      fasinit(3);*u(3,1)=*u(4,5)-60000;fasgeti(3);
      makename(fdet[ptb].omschr);
      copy(s(4,28),fdet[ptb].opmerk,20);
      fdet[ptb].bedrag=*d(4,32)*factor_;
      ptb++;
    }
    if(ptb>=50) break;
  }
  if(bk_dat_<=last_arc) copy("DETAIL IS GEARCHIVEERD !!!",fdet[5].omschr,30);
  fasinit(4);*l(4,1)=mast4_; fasgeti(4);
  if(aard<3) {*l(4,7)=-*l(4,7);*d(4,32)=-*d(4,32);}
  fasinit(kl_stu_);*u(kl_stu_,1)=*u(4,5)-(kl_stu_-1)*30000;fasgeti(kl_stu_);
  FOREVER{
    scrget(1,66); z=1;
    if(aard<3) scrifld(z++,fm_os15,"Aankoopfactuur");
    else scrifld(z++,fm_os15,"Verkoopfactuur");
    scrifld(z++,fm_uu2,&journl_);
    scrifld(z++,fm_uu5,&volgnr_);
    scrfld(z++,4,4);
    scrofld(z++,kl_stu_,1,-1);scrfld(z++,kl_stu_,3);
    scrfld(z++,4,28);
    if(aard<3) scrfld(z++,4,27); else streepje(z++);
    scrfld(z++,4,20);
    scrfld(z++,4,21);
    if(aard==1){
      scrfld(z++,4,34);
      scrfld(z++,4,22);
    } else {streepje(z++);streepje(z++);}
    if(aard<3){streepje(z++);streepje(z++);}
    else {scrfld(z++,4,30);scrfld(z++,4,29);}
    scrfld(z++,4,32); scrifld(z++,fm_os3,"EUR");
    z+=2;/*    scrfld(z++,4,7); scrifld(z++,fm_os3,"BEF"); */
    k=start_+1; scrifld(z++,fm_uu2,&k);
    k=start_+10; scrifld(z++,fm_uu2,&k);
    for(k=start_;k<start_+10;k++){
      scrifld(z++,fm_obd,&fdet[k].bedrag);
      scrifld(z++,fm_os30,fdet[k].omschr);
      scrifld(z++,fm_os20,fdet[k].opmerk);
    }
    key=scrupd(-1,0x87);
    if(key==101 || key==108) break;
    if(key==102) {start_-=10; if(start_<0) start_=0;}
    if(key==103) {start_+=10; if(start_>40) start_-=10;}
  }
  endsr:;
  copy(buf4_,s(4,1),fldlen(4,0));

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

static print_lst()
{
  int16 k,n,lin_,z,len_;
  uint16 last_lev;
	struct {
		double bd_ovr;
		char munt[4];
		char klantstr[40];
		char mededeling[40];
		uint16 ft_nr;
		uint16 ft_date;
		uint16 dt_verv;
		double ft_bedrag;
		char ft_mededeling[40];
	} plin;

  getsysprNew(3,form_dat,&pr_mode,&prtnr); if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) return YES;
	scrget(1,6);scrupd(-3,0);
  prtfld(25,1,30);prttext("<t35b>");prttext("Overschrijvingslijst via ");prtifld(fm_os79,tb_bank[nr_bank].Iban,25);prttext("<b>");
	prttext("<t80>Betaaldatum : ");prtifld(fm_udat,&dt_ovr,-1);prttext("<t122>Blz.<ppp>.");
	prtbuf(1);z=1;
	prtitab(z,fm_obd,&plin.bd_ovr,1,-1); prttitle(z++,"Bedrag",0x13);
	prtitab(z,fm_os3,plin.munt,1,-1); prttitle(z++,"Mnt",3);
	prtitab(z,fm_os30,plin.klantstr,1,-1); prttitle(z++,"Begunstigde",3);
	prtitab(z,fm_os30,plin.mededeling,1,-1); prttitle(z++,"Mededeling aan bank",3);
	prtitab(z,fm_ou5,&plin.ft_nr,1,-1); prttitle(z++,"Ft.nr",0x13);
	prtitab(z,fm_odat,&plin.ft_date,1,-1); prttitle(z++,"Ft.dat.",0x13);
	prtitab(z,fm_odat,&plin.dt_verv,1,-1); prttitle(z++,"Verv.Dt",0x13);
	prtitab(z,fm_obd,&plin.ft_bedrag,1,-1); prttitle(z++,"Bedrag",0x13);
	prtitab(z,fm_os20,plin.ft_mededeling,1,-1); prttitle(z++,"Factuurmededeling",3);
	prtbuf(3);
	p_pdfname("Overschrijvingslijst",dt_ovr,0);
  free=999;
  scrget(1,6);scrupd(-3,0);
  last_lev=0xFFFF;actu_ln=0; tot_ovr=0;
  for(n=0;n<ram_nr;n++){
    if(load_tab(n)) break;
		fasinit(1);*u(1,1)=st_ovr[0].lev_rec;fasgeti(1);
		lin_=0;
		FOREVER{
			zero((char *)&plin.bd_ovr,sizeof plin);
			switch(lin_){
			  case 0 : 	plin.bd_ovr=bedr_tbt;if(bet_belg!='V') copy("EUR",plin.munt,3); else copy(st_ovr[0].munt,plin.munt,3);
									copy(s(1,3),plin.klantstr,30);
									copy(&mededeling[0],plin.mededeling,30);
									break;
				case 1 :	copy(s(1,18),plin.klantstr,fldlen(1,18));
									copy("BIC : ",plin.mededeling,6);copy0(s(1,19),&plin.mededeling[6],fldlen(1,19));
									break;
				default : break;
			}
			if(lin_<bet_q){
				fasinit(4); if(st_ovr[lin_].rec4){*l(4,1)=st_ovr[lin_].rec4;fasgeti(4);}
				plin.ft_nr=st_ovr[lin_].vl;plin.ft_date=st_ovr[lin_].ft_date;plin.dt_verv=st_ovr[lin_].verv_dat;
			  if(bet_belg!='V') plin.ft_bedrag=st_ovr[lin_].bd_tebet; else plin.ft_bedrag=st_ovr[lin_].bd_vrm_mnt;
        len_=0;
				if(*s(4,27)) len_=copy0(s(4,27),plin.ft_mededeling,15);
				if(sys1792 & 1){if(*s(4,28)) copy0(s(4,28),&plin.ft_mededeling[len_],20);}
			}
			for(k=1;k<20;k++) prtinfo(k,0);nextline();
			lin_++;
			if(lin_>1 && lin_>=bet_q) break;
		}
		tot_ovr+=bedr_tbt;
  }
	zero((char *)&plin.bd_ovr,sizeof plin);copy("EUR",plin.munt,3);
	plin.bd_ovr=tot_ovr;
	k=copy0("Totaal lijst (",plin.klantstr,30);stcli_d(&plin.klantstr[k],(long)ram_nr,3,1); copy0(" betalingen)",&plin.klantstr[k+3],15);
	nextline();for(k=1;k<20;k++) prtinfo(k,2);nextline();

	if(boek_JN=='J'){
		nextline();
		prttext("<t7>Deze lijst wordt geboekt via journaal <b>");prtifld(fm_uu2,&journl,-1);
		prttext("<b>, volgnummer<b>");prtifld(fm_uu5,&volgnr_ovr,-1);
		prttext("<b> met tegenrekening <b>");fasinit(3);*u(3,1)=recnr_ovr-60000;fasgeti(3);prtfld(3,2,-1);prttext(" ");prtfld(3,3,-1);
		nextline();
	}

  prtform(0); prtclose();
}



static boekbkh()
{
  int16 n;
 
	fasunlck(-2);
  tot_disk=0;tot_ovr=0;tot_bef=0;tot_eur=0;
  for(n=0;n<ram_nr;n++){
    if(load_tab(n)) break;
    fasinit(1);*u(1,1)=st[0].lev_rec;fasgeti(1);
    boek_stuk();
    tot_ovr+=bedr_tbt;  tot_disk+=bedr_dis;
  }
  boek_end();
  if(!is_nul(tot_eur)){                 /* verschillen wegboeken */
    *s(4,2)=journl;
    *u(4,3)=volgnr_ovr;
    *u(4,4)=dt_ovr;
    *u(4,20)=dt_ovr;
    if(grb_d_fi){
      *u(4,5)=rec_d_fi; *l(4,6)=grb_d_fi;
    }
    else{
      if(tot_eur>0){
				*u(4,5)=rec_d_ak; *l(4,6)=grb_d_ak;
      }
      else {*u(4,5)=rec_d_vk; *l(4,6)=grb_d_vk;}
    }
    *l(4,7)=-tot_bef; *d(4,32)=-tot_eur;
    *s(4,31)='E';
		if(fldlen(4,60)) *u(4,60)=procid;
    errnum=fasadd(4);
  }
  sysput(sys_adr,2,&volgnr_ovr);
	fasunlck(-1);
}

static boek_stuk()
{
  int16 k;
 
  for(k=0;k<bet_q;k++){
    bd_bkh=st[k].bd_tebet;
    bd_bkh+=st[k].ebd_disk;/* terug bijtellen */

    rec_nr=*u(1,1);
    rf_yy=st[k].r_yy;rf_jr=st[k].r_jr;rf_vl=st[k].r_vl;
    boek_div();
  }
}

static boek_end()
{
  bd_bkh=-tot_disk;
  rec_nr=recnr_disk;
  rf_yy=0;rf_jr=0;rf_vl=0;
  zeroL(s(4,28),fldlen(4,28));/* vorige opm wegvegen */
  boek_div();
  bd_bkh=-tot_ovr;
  rec_nr=recnr_ovr;
  zeroL(s(4,28),fldlen(4,28));/* vorige opm wegvegen */
	stcli_d(s(4,28),(long)ram_nr,2,1);copy(" betalingen",s(4,28)+2,11);
  boek_div();
}
 
static boek_div()
{
  long grbveld;
  long bd_bef;
  double bd_eur;/* verschillen in EUR nog inbouwen */

  *s(4,2)=journl;
  *u(4,3)=volgnr_ovr;
  *u(4,4)=dt_ovr;
  *u(4,20)=dt_ovr;
  if(!is_nul(bd_bkh)){
    bd_eur=bd_bkh;
    bd_bef=valu_cnv("EUR","BEF",(double)(bd_bkh),(double)(1.));
    *l(4,7)=bd_bef; *s(4,31)='E'; *d(4,32)=bd_eur;
    tot_bef+=bd_bef; tot_eur+=bd_eur;
    *u(4,5)=rec_nr;
    if(rec_nr<30000) grbveld=levcent;
    else {*u(3,1)=rec_nr-60000;fasgeti(3);grbveld=*l(3,2);}
    *l(4,6)=grbveld;
    *s(4,8)=rf_yy;
    *s(4,9)=rf_jr;
    *u(4,10)=rf_vl;
    if(*s(4,9) || *u(4,10)){/* correctie y2000 */
      if(*s(4,8)<50) *s(4,8)+=100;
      else if(*s(4,8)>=150) *s(4,8)-=100;
    } else if(*s(4,8)==100) *s(4,8)=0;
    *s(4,12)=0;
		if(fldlen(4,60)) *u(4,60)=procid;
    fasadd(4);
  }
  fasflush(0);
}

static Ovr2Xml()  // uitschrijven betalingen in xml voor bankpgm
{
  int16 spos_,j,k,jjjj,mm,dd,n,act_jj_,act_mm_,act_dd_,act_uur_,act_min_,act_sec_;
  long lbd_;
  char kar_,str_[100],str1_[100],PmtId[50],filname_[50],lev_iban_[50],lev_bic_[20];	
									
	fasclos(-2); fasunlck(-2);
#if FLAGCOC || FLAGVGV
	zero(filname_,sizeof filname_);
#if FLAGCOC
	k=copy0("..\\CODA_UIT\\",filname_,15);
#else 
  k=copy0("..\\SHARE\\CODA\\",filname_,15);
#endif
	k+=copy0(tb_bank[nr_bank].filnam,&filname_[k],sizeof tb_bank[nr_bank].filnam);
	k+=copy0(".XML",&filname_[k],4);
  if(errnum=fasopen(filname_,2)) return NO;
#else
	zero(filname_,sizeof filname_);k=0;
	k+=copy0(tb_bank[nr_bank].filnam,&filname_[k],sizeof tb_bank[nr_bank].filnam);
	k+=copy0(".XML",&filname_[k],4);
  if(errnum=fasopen(filname_,12)) return NO;
#endif
	

//	fasinit(80);fasinfo(80,202);
//	lbd_=*l(80,1);
//	act_uur_=*l(80,1)/3600; act_min_=(*l(80,1)%3600)/60; act_min_=(*l(80,1)%3600)%60;
	GetCurrentDateTime(&act_jj_,&act_mm_,&act_dd_,&act_uur_,&act_min_,&act_sec_);
  fasinit(80); seqo_pos=0;
  scrget(1,7);scrupd(-3,0); tot_ovr=0;

	fasinit(80);seqo_pos=0;zero(seqo_str,sizeof seqo_str);seqo_mode=2;pos=0;
  pos+=copy0("<?xml version=\"1.0\" encoding=\"UTF-8\"?>",&seqo_str[pos],150);add_crlf();dmp2file();
  pos+=copy0("<Document xmlns=\"urn:iso:std:iso:20022:tech:xsd:pain.001.001.03\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">",&seqo_str[pos],250);add_crlf();dmp2file();
  
	pos+=copy0("<CstmrCdtTrfInitn>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("<GrpHdr>",&seqo_str[pos],30);add_crlf();
	 
	  zero(PmtId,sizeof PmtId);spos_=0;
		spos_=copy0(s(25,3),&PmtId[spos_],3);PmtId[spos_++]='/';
    journl=tb_bank[nr_bank].journal;stcli_d(&PmtId[spos_],(long)(journl),2,0);spos_+=2;PmtId[spos_++]='/';
    stcli_d(&PmtId[spos_],(long)(volgnr_ovr),5,0);spos_+=5;
  	dmpxmlstr("MsgId",PmtId,spos_);

		zero(str_,sizeof str_);spos_=0;
		stcli_d(&str_[spos_],(long)act_jj_,4,0);spos_+=4;str_[spos_++]='-';
		stcli_d(&str_[spos_],(long)act_mm_,2,0);spos_+=2;str_[spos_++]='-';
		stcli_d(&str_[spos_],(long)act_dd_,2,0);spos_+=2;str_[spos_++]='T';
		stcli_d(&str_[spos_],(long)act_uur_,2,0);spos_+=2;str_[spos_++]=':';
		stcli_d(&str_[spos_],(long)act_min_,2,0);spos_+=2;str_[spos_++]=':';
		stcli_d(&str_[spos_],(long)act_sec_,2,0);spos_+=2;
		dmpxmlstr("CreDtTm",str_,spos_);
		zero(str_,sizeof str_);spos_=0;
		stcli_d(str_,(long)ram_nr,5,1);for(k=0;k<5;k++) if(str_[k]!=' ') break;
		dmpxmlstr("NbOfTxs",&str_[k],5-k);
  pos+=copy0("<InitgPty>",&seqo_str[pos],30);add_crlf();
    dmpxmlstr("Nm",&firma[0],30);
		pos+=copy0("<Id>",&seqo_str[pos],30);add_crlf();
		  pos+=copy0("<OrgId>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("<Othr>",&seqo_str[pos],30);add_crlf();
			  zero(str_,sizeof str_);btw_deco(&str_[0],(long *)&firmbtwn,0);//copy("0",&str_[0],1);stcli_d(&str_[1],firmbtwn,9,0);
				dmpxmlstr("Id",str_,10);
				dmpxmlstr("Issr","KBO-BCE",10);
      pos+=copy0("</Othr>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("</OrgId>",&seqo_str[pos],30);add_crlf();
    pos+=copy0("</Id>",&seqo_str[pos],30);add_crlf();
  pos+=copy0("</InitgPty>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("</GrpHdr>",&seqo_str[pos],30);add_crlf();
	dmp2file();

	pos+=copy0("<PmtInf>",&seqo_str[pos],30);add_crlf();
    copy("000",&PmtId[12],3);dmpxmlstr("PmtInfId",PmtId,15);
		dmpxmlstr("PmtMtd","TRF",3);
		if(sys1792 & 0x10) dmpxmlstr("BtchBookg","false",5); else dmpxmlstr("BtchBookg","true",4);
		pos+=copy0("<PmtTpInf>",&seqo_str[pos],30);add_crlf();
		  pos+=copy0("<SvcLvl>",&seqo_str[pos],30);add_crlf();
			  dmpxmlstr("Cd","SEPA",4);
			pos+=copy0("</SvcLvl>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("</PmtTpInf>",&seqo_str[pos],30);add_crlf();

	jddate(dt_ovr,&jjjj,&mm,&dd);spos_=0;
	stcli_d(&str_[spos_],(long)jjjj,4,0);spos_+=4;str_[spos_++]='-';
	stcli_d(&str_[spos_],(long)mm,2,0);spos_+=2;str_[spos_++]='-';
	stcli_d(&str_[spos_],(long)dd,2,0);spos_+=2;
	dmpxmlstr("ReqdExctnDt",str_,spos_);
	pos+=copy0("<Dbtr>",&seqo_str[pos],30);add_crlf();
	  dmpxmlstr("Nm",&firma[0],30);
		pos+=copy0("<PstlAdr>",&seqo_str[pos],30);add_crlf();
		  if(firma[31]){
  		  zero(str_,sizeof str_); k=copy0(&firma[31],str_,25);
				for(j=k-1;j>0;j--) if(str_[j]==' ') break;
				if(j>2) {
					dmpxmlstr("StrtNm",str_,j);
					dmpxmlstr("BldgNb",&str_[j+1],k-j);
				}
				else dmpxmlstr("StrtNm",str_,k);
			}
			if(firma[57]){
  		  zero(str_,sizeof str_); k=copy0(&firma[57],str_,6);
				dmpxmlstr("PstCd",str_,k);
			}
			if(firma[65]){
  		  zero(str_,sizeof str_); k=copy0(&firma[65],str_,20);
				dmpxmlstr("TwnNm",str_,k);
			}
			dmpxmlstr("Ctry","BE",2);
			//if(firma[31]) dmpxmlstr("AdrLine",&firma[31],25);
			//zero(str_,sizeof str_);spos_=0;
			//spos_+=copy0(&firma[57],&str_[spos_],6); if(spos_) str_[spos_++]=' ';
			//spos_+=copy0(&firma[65],&str_[spos_],20);
			//if(spos_) dmpxmlstr("AdrLine",str_,30);
		pos+=copy0("</PstlAdr>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("</Dbtr>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("<DbtrAcct>",&seqo_str[pos],30);add_crlf();
	  pos+=copy0("<Id>",&seqo_str[pos],30);add_crlf();
			zero(str_,sizeof str_);spos_=0;
			for(k=0;k<25;k++){ 
				kar_=tb_bank[nr_bank].Iban[k];
		 		if(kar_=='\0') break;
		 		if((kar_>='0' && kar_<='9') || (kar_>='A' && kar_<='Z')) str_[spos_++]=kar_;
			}
		  dmpxmlstr("IBAN",str_,30);
		pos+=copy0("</Id>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("</DbtrAcct>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("<DbtrAgt>",&seqo_str[pos],30);add_crlf();
	  pos+=copy0("<FinInstnId>",&seqo_str[pos],30);add_crlf();
			zero(str_,sizeof str_);spos_=0;
			for(k=0;k<11;k++){ 
				kar_=tb_bank[nr_bank].Bic[k];
		 		if(kar_=='\0') break;
		 		if((kar_>='0' && kar_<='9') || (kar_>='A' && kar_<='Z')) str_[spos_++]=kar_;
			}
		  dmpxmlstr("BIC",str_,30);
		pos+=copy0("</FinInstnId>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("</DbtrAgt>",&seqo_str[pos],30);add_crlf();
	dmpxmlstr("ChrgBr","SLEV",4); // elk betaalt zijn eigen kosten 
	dmp2file();
	for(n=0;n<ram_nr;n++){ // individuele betalingen 
    if(load_tab(n)) break;
    fasinit(1);*u(1,1)=st[0].lev_rec;fasgeti(1);
		zero(lev_bic_,sizeof lev_bic_);spos_=0;
		for(k=0;k<11;k++){ 
			kar_=*(s(1,19)+k);
		 	if(kar_=='\0') break;
		 	if((kar_>='0' && kar_<='9') || (kar_>='A' && kar_<='Z')) lev_bic_[spos_++]=kar_;
		}
		zero(lev_iban_,sizeof lev_iban_);spos_=0;
		for(k=0;k<34;k++){ 
			kar_=*(s(1,18)+k);
		 	if(kar_=='\0') break;
		 	if((kar_>='0' && kar_<='9') || (kar_>='A' && kar_<='Z')) lev_iban_[spos_++]=kar_;
		}
		pos+=copy0("<CdtTrfTxInf>",&seqo_str[pos],30);add_crlf();
		  pos+=copy0("<PmtId>",&seqo_str[pos],30);add_crlf();
			  stcli_d(&PmtId[12],(long)(n+1),3,0);dmpxmlstr("EndToEndId",PmtId,15);
			pos+=copy0("</PmtId>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("<Amt>",&seqo_str[pos],30);add_crlf();
			  pos+=copy0("<InstdAmt Ccy=\"EUR\">",&seqo_str[pos],30);
        pos+=bd2xstr(&seqo_str[pos],bedr_tbt,12);
				pos+=copy0("</InstdAmt>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("</Amt>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("<CdtrAgt>",&seqo_str[pos],30);add_crlf();
			  pos+=copy0("<FinInstnId>",&seqo_str[pos],30);add_crlf();
				  dmpxmlstr("BIC",lev_bic_,11);
        pos+=copy0("</FinInstnId>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("</CdtrAgt>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("<Cdtr>",&seqo_str[pos],30);add_crlf();
			  for(k=0;k<(s(2,8)-s(2,3));k++) if(*(s(2,3)+k)=='*') *(s(2,3)+k)=' '; // sommige banken weigeren '*'
			  dmpxmlstr("Nm",s(1,3),30);
				pos+=copy0("<PstlAdr>",&seqo_str[pos],30);add_crlf();
					if(*s(1,4)){
  					zero(str_,sizeof str_); k=copy0(s(1,4),str_,fldlen(1,4));
						for(j=k-1;j>0;j--) if(str_[j]==' ') break;
						if(j>2 && (k-j)<5) { // nr max 5 karakters, anders wellicht geen nr
							dmpxmlstr("StrtNm",str_,j);
							dmpxmlstr("BldgNb",&str_[j+1],k-j);
						}
						else dmpxmlstr("StrtNm",str_,k);
					}
					if(*s(1,5)){
  					zero(str_,sizeof str_); k=copy0(s(1,5),str_,fldlen(1,5));
						dmpxmlstr("PstCd",str_,k);
					}
					if(*s(1,6)){
  					zero(str_,sizeof str_); k=copy0(s(1,6),str_,fldlen(1,6));
						dmpxmlstr("TwnNm",str_,k);
					}
				  dmpxmlstr("Ctry",lev_iban_,2);
					//if(*s(1,4)) dmpxmlstr("AdrLine",s(1,4),30);
					//zero(str_,sizeof str_);spos_=0;
					//spos_+=copy0(s(1,5),&str_[spos_],6); if(spos_) str_[spos_++]=' ';
					//spos_+=copy0(s(1,6),&str_[spos_],25);
					//if(spos_) dmpxmlstr("AdrLine",str_,30);
				pos+=copy0("</PstlAdr>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("</Cdtr>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("<CdtrAcct>",&seqo_str[pos],30);add_crlf();
			  pos+=copy0("<Id>",&seqo_str[pos],30);add_crlf();
				  dmpxmlstr("IBAN",lev_iban_,41);
				pos+=copy0("</Id>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("</CdtrAcct>",&seqo_str[pos],30);add_crlf();
			pos+=copy0("<RmtInf>",&seqo_str[pos],30);add_crlf();
			  zero(str_,sizeof str_);spos_=0;
			  for(k=0;k<140;k++){
					if(mededeling[k]=='\0') break;
					if(mededeling[k]>='0' && mededeling[k]<='9') str_[spos_++]=mededeling[k];
					if(spos_>12) break; // kan maar 12 cijfers zijn 
				}
				if(spos_==12){ // checken of wel echte gestructureerde mededeling
					zero(str1_,sizeof str1_);copy(str_,str1_,6);lbd_=val(str1_);
					lbd_=lbd_%97; zero(str1_,sizeof str1_);stcli_d(str1_,lbd_,2,0);copy(&str_[6],&str1_[2],4);lbd_=val(str1_);
					lbd_=lbd_%97; if(lbd_==0) lbd_=97;
					if(lbd_!=val(&str_[10])) spos_=0; // geen struct.med.
				}
				if(spos_==12){ // struct.med
					pos+=copy0("<Strd>",&seqo_str[pos],30);add_crlf();
					  pos+=copy0("<CdtrRefInf>",&seqo_str[pos],30);add_crlf();
						  pos+=copy0("<Tp>",&seqo_str[pos],30);add_crlf();
						    pos+=copy0("<CdOrPrtry>",&seqo_str[pos],30);add_crlf();
								  dmpxmlstr("Cd","SCOR",10);
								pos+=copy0("</CdOrPrtry>",&seqo_str[pos],30);add_crlf();
								dmpxmlstr("Issr","BBA",10);
						  pos+=copy0("</Tp>",&seqo_str[pos],30);add_crlf();
							dmpxmlstr("Ref",str_,12);
						pos+=copy0("</CdtrRefInf>",&seqo_str[pos],30);add_crlf();
					pos+=copy0("</Strd>",&seqo_str[pos],30);add_crlf();
				} 
				else if(mededeling[0]) dmpxmlstr("Ustrd",mededeling,140); // gewone mededeling 
			pos+=copy0("</RmtInf>",&seqo_str[pos],30);add_crlf();
		pos+=copy0("</CdtTrfTxInf>",&seqo_str[pos],30);add_crlf();
		dmp2file();
	}
	pos+=copy0("</PmtInf>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("</CstmrCdtTrfInitn>",&seqo_str[pos],30);add_crlf();
	pos+=copy0("</Document>",&seqo_str[pos],30);add_crlf();
	dmp2file();

  fasclos(-2);
	return YES;
  endsr:;
}
 
static bd2xml(xname_,bd_)
char *xname_;
double bd_;
{
  char str_[15];
 
  zero(str_,sizeof str_);
  bd2xstr(str_,bd_,12);
  dmpxmlstr(xname_,str_,12);
  endsr:;
}


static bd2xstr(ps_,bd_,totlen_)
char *ps_;
double bd_;
int16 totlen_;
{
  int16 k,negat_,len_;
  double bd1_,bd2_;
  long lbd1_,lbd2_;
  char str_[15];
 
 
  bd_=valu_cnv("EUR","EUR",bd_,(double)(0.01));
	negat_=NO; if(bd_<0){negat_=YES;bd_=-bd_;}

  zero(str_,sizeof str_);
  bd1_=(long)(bd_);
  bd2_=(long)((bd_-bd1_)*(double)(100.) +(double).49);
  lbd1_=(long)(bd1_+.49); lbd2_=(long)(bd2_+.49);
  stcli_d(str_,lbd1_,8,1);str_[8]='.'; stcli_d(&str_[9],lbd2_,2,0);
  if(negat_){                                             /* negatief getal */
    for(k=0;k<10;k++) if(str_[k]!=' ') break;
    if(k>0) str_[k-1]='-';
  }
  for(k=0;k<10;k++) if(str_[k]!=' ') break;
  len_=copy0(&str_[k],ps_,12-k); 
  
  return len_;
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
  add_crlf();
}

static dmp2file()
{
  int16 k;
 
  XMLcnv_char(seqo_str,pos);
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
  pos=0;
}

static add_crlf()
{
  seqo_str[pos++]=0x0D;
  seqo_str[pos++]=0x0A;
}

static XMLcnv_char(ps_,len_)/* convert jama-ascii to ascii */
char *ps_;
int16 len_;
{
  int16 k,q_ele_;
  char kar_;
									
  q_ele_=sizeof XMLfas2sif;
  for(k=0;k<len_;k++){
    kar_=*(ps_+k);
    if(kar_>=0x80 && kar_<0x80+q_ele_){
      *(ps_+k)=XMLfas2sif[kar_-0x80];
    }
  }
}

static kumul(rek)
char rek[12];
{
  int16 j;
 
  for(j=0;j<12;j++) rek_kumul[j+3]+=rek[j]-'0';
  for(j=14;j>=0;j--){
    if(rek_kumul[j]>'9'){
      rek_kumul[j]-=10; rek_kumul[j-1]++;
    }
  }
}
 
static set_dum(p,len,byte)
char *p, byte;
int16 len;
{
  while (len-->0) *p++=byte;
}
 
static nextline()
{
  free=prtline();
}

static str_len(p,len)
int16 len;
char *p;
{
  int16 k=0;

  while(len--){
    if(*p++=='\0') break;
    k++;
  }
  return k;
}


static initload()
{
  int16 g,k,j,z;
	char str_[10];

  fasunlck(0);
  fileopen(1);
  fileopen(3);
  fileopen(4);

  for(k=0;k<80;k++){
    sysget(10240+k*80,2,&g);
    sysget(10242+k*80,2,&j_tb[g]);
  }

  k=0;
  for(g=0;g<100;g++){
    if(j_tb[g]==1) aank_jrl[k++]=g;
    if(k==7) break;
  }

  journl=0;
  for(g=0;g<100;g++){
    if(j_tb[g]==7){journl=g;break;}
  }
  if(journl){/* als journaal hier 0 is, kan men nooit boeken */
    chk_btoeg=NO;/* jvg kan volgend stuk niet met get_grb verkleind worden */
    sysget( 780,4,&levcent);
    fasinit(3);*l(3,2)=levcent;
    search(3,2);
    if(errnum==39) errnum=28;
    chk_btoeg=YES;
    if(errnum) ovlexit(-1);
    fasinit(3);
    sysget( 808,4,l(3,2));
    search(3,2);
    if(errnum==39) errnum=28;                                /* discontorek */
    if(errnum) ovlexit(-1);
    recnr_disk=*u(3,1)+60000;
    sysget(1201,4,&grb_d_ak);
    if(grb_d_ak==0 || grb_d_ak==-1) {errnum=16; ovlexit(-1);}
    rec_d_ak=getgrb(grb_d_ak);
    if(errnum==39) errnum=28;
    if(errnum) ovlexit(-1);
    sysget(1205,4,&grb_d_vk);
    if(grb_d_vk==0 || grb_d_vk==-1) {errnum=16; ovlexit(-1);}
    rec_d_vk=getgrb(grb_d_vk);
    if(errnum==39) errnum=28;
    if(errnum) ovlexit(-1);
    sysget(1209,4,&grb_d_fi);
    if(grb_d_fi==0 || grb_d_fi==-1) {grb_d_fi=0;rec_d_fi=0;}
    else rec_d_fi=getgrb(grb_d_fi);
    if(errnum==39) errnum=28;
    if(errnum) ovlexit(-1);
  }
 
  sysget(  34,256,firma);
  sysget( 294,4,def_munt);
  sysget(1792,2,&sys1792);
  sysget(1858,2,&last_arc);
	sysget(2300,2,&MinBkhDatum);if(MinBkhDatum<last_arc) MinBkhDatum=last_arc;
  sysget(1918,2,&sear_stt);
  sysget(3876,2,&sys3876);
  for(k=0;k<3;k++){
    sysget(3250+k*110,110,(char *)&tb_bank[k].rekening[0]);
  }

  firmbtwn=0;z=0;j=-1;
  for(k=0;k<15;k++){
    if(firma[86+k]=='\0') break;
    if(firma[86+k]>='0' && firma[86+k]<='9'){
      z++;if(j==-1) j=k;
    }
  }
  for(k=0;k<15;k++){
    if(firma[86+k]=='\0') break;
    if(firma[86+k]>='0' && firma[86+k]<='9'){
      if(k>j || z<=10){                     /* enkel laatste 9 cijfers nemen */
	firmbtwn=(firmbtwn*10) + (firma[86+k]-'0');
      }
    }
  }
	if(firmbtwn>1000000000) {
    firmbtwn-= 1000000000L;
  	copy((char *)(&firmbtwn), str_, 4);
	  str_[3] |= 0x80; copy(str_, (char *)(&firmbtwn), 4);
	}

	if(CheckForFreeSpace(4,MINFREE)) ovlexit(10);/* onvoldoende vrije records */
}

			
static uint16 getgrb(lgrb)
long lgrb;
{
  uint16 retcd=0;
								
  if(*(char *)&lgrb!=0xFF && *(char *)&lgrb!=0x00){
    *l(3,2)=lgrb;
    *u(3,1)=0;
    search(3,2);
    if(errnum==0){
      retcd=*u(3,1)+60000;
    }
  }
  return retcd;
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
  }
}

static GetBErekeningFromIban(p_iban_,p_rek_,iban_len_)
char *p_iban_,*p_rek_;
int iban_len_;
{
  int16 j,k,ret_val_=NO;
  char str_[15],rek_nr[10];

  zero(str_,sizeof str_); zero(rek_nr,sizeof rek_nr);
	if(cmpstr(p_iban_,"BE",2)) goto endsr;
	j=0;
	for(k=2;k<iban_len_;k++){
		if(j==2) break;
    if(*(p_iban_+k)>='0' && *(p_iban_+k)<='9') j++;
	}
	if(j!=2) goto endsr;
	j=0;
	for(k;k<iban_len_;k++){
		if(j==12) break;
    if(*(p_iban_+k)>='0' && *(p_iban_+k)<='9') str_[j++]=*(p_iban_+k);
	}
	if(j!=12) goto endsr;
  if(rek_comp(str_,rek_nr)==0) ret_val_=YES;
endsr:;
	if(ret_val_) copy(rek_nr,p_rek_,5);
	return ret_val_;
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
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

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}

static p_pdfname(naam_,dt_beg_,dt_end_)
char *naam_;
uint16 dt_beg_,dt_end_;
{
  int16 pos_,slen_,len_,dd,mm,yy;
  char buf_[30],string[100];
				
  zeroL(string,sizeof string);
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
    zeroL(buf_,sizeof buf_);
    copy("\xD0\xCF",buf_,2);
    if(slen_>25) len_=25; else len_=slen_;
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
  zeroL((char *)parmcall,sizeof parmcall);
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

