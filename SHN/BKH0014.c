/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0014GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0014dat
#define ovlcod BKH0014cod
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

char ovldat[] = "bkh0014  00:49 24/10/12 (c) Jamadata";
 
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_OPEN        10000
#define DIM_STKTAB			40000
#define DIMZOEK         15
#define MAXLEN          30

extern int16 retcall,parmcall[8];
extern int16 ilength;
extern uint16 procid;
extern char info[];
extern uint16 jamin1[5];

static struct {
  uint16 nr;
  uint16 typ;
} j_tab[81];/* 1 extra element */

extern char *s();
extern int16 *i();
extern uint16 *u();
extern uint16 datejd();
extern long *l();
static long val(),str2get();
extern float *f();
extern double *d(), valu_cnv();
static double absdoubl(),round();

static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os12[]  = {7,0x88,13,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou2s[]  = {6,0x90,2,0,0x00,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_ol9[]   = {6,0x93,9,0,0x70,0};
static char fm_ol7[]   = {6,0x93,7,0,0x70,0};
static char fm_od9_2[] = {6,0x95,9,2,0x70,0};
static char fm_od7_2[] = {6,0x95,7,2,0x70,0};
static char fm_od92_[] = {6,0x95,9,2,0x60,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_us1_[]  = {9,0xC8,1,0,0x09,0,0xFF,0xFF,0};
static char fm_uLKG[]  = {11,0xC8,1,0,0x09,0,'K','L','G','G',0};
static char fm_uLKGA[]  = {13,0xC8,1,0,0x09,0,'K','L','G','G','A','A',0};
static char fm_obd[]   = {6,0x95,9,2,0x70,0};                             /* od9_2 */

static int XlsKol,XlsRij,XlsRef;
static int16 form_dat[8],pr_mode,free,prtnr,chk_btoeg=1,stu_bew,z_opm,z_cumsal;
static int16 stu,mnd_strt,period_1,tabpos,bew_key,KoppelMode=NO, CntGekoppeld,DeleteMode;
static int16 prt2pdf,Exec257,Exec263,Exec66,Exec33;
static uint16 jaar,journl,volgnr,dt_bew,ref_yy,ref_jr,ref_vl,dt_vandaag;
static long levcent,kltcent,sear_grb,sub_mask,hoev,zk_rec[20];
static double bd_cre,bd_deb,bdt_cre,bdt_deb,cum_saldo,sal_deb,sal_cre,TotaalGekoppeld;
static uint16 last_af,last_vf,last_arc,MinBkhDatum,clean_prev[3],searcnr,dat_beg,dat_end;
static char lkg='K',opm_bkh[41],munt[4],buf750[750],fm_bd[40],dsp_f_e,def_munt[4],buff1000[1000];
static char dfmunt[4],lkglet[3]={'L','K','G'};
static uint16 r_yy[12],r_yy_[12],r_jr[12],r_jr_[12],r_vl[12],r_vl_[12];
static uint16 DatumVorigSaldo;
static long StkTab[DIM_STKTAB],MaxStkTab;
static uint16 zoekscr[DIMZOEK],pzoekscr;
static char StkTabFlag[DIM_STKTAB];
static double bd_vm,BdZoek;
static flag allow_yr,lvcd,klcd,debit_allow=NO,credt_allow=NO,eerste,get_jaar;
static flag sear_stt,analyt,only_open,only_verv,only_fact,only_klt,only_dsp;
static flag sys3876,sys1787,sys1834,sys2698,DspTotRek;

static char *mnd_str[12]={"jan","feb","maa","apr","mei","jun","jul","aug","sep","okt","nov","dec"};
							   /* de variabelen */
static int16 *pi;
 
static int16 qloaded;
static long open_recs[DIM_OPEN];
 
static int16 p_scr;
static double bew_saldo,bd_totaal;
static struct{
  long rec4;
  long rec86;
  double saldo;
  char stu_bew;
} tbs[DIM_STKTAB/12 + 10];

static struct{
  double bedrag;
  char omschr[MAXLEN];
  char opmerk[20];
} fdet[50];

static int16 date2str();
  
ovlcod(parmval)
int16 parmval;
{
  int16 key,k,curs=3,z;
  uint16 mask_;

  initload();
  only_klt=NO; 
	switch(parmval){
  	case  1 : only_klt=YES; break; //  enkel klanten vanuit VOO 
    case 10 : stu=1; only_open=NO; display(NO); break; // rekening van klant
    case 11 : stu=1; only_open=YES; display(NO); break; // openstaande facturen 
		case 12 : stu=1; ShowSavedDocument(stu,(long)(*u(stu,1)),0,dat_beg,dat_end) ;
    case 20 : stu=2; only_open=NO; display(NO); break; // rekening van klant
    case 21 : stu=2; only_open=YES; display(NO); break; // openstaande facturen 
		case 22 : stu=2; ShowSavedDocument(stu,(long)(*u(stu,1)),0,dat_beg,dat_end) ;
		default : break;
	}
	if(parmval>1) goto endsr;
	  
  fasinit(1);
  FOREVER{
    redo:
    scrget(1,115); z=1;fasunlck(0);
		if(fldlen(7,1) || ovltest(2240)) scraddpicto(6,0,5,20,4,2,570,0,0,"Automatisch verzonden documenten"); 
    if(ServerVersion>1 || StdInMono){
			if(fldlen(16,1)) scraddpicto(5,0,0,20,4,2,557,0,0,"Maak grafiek"); 
			
    }
		scraddpicto(7,0,76,20,4,2,112,0,4,"Zoek bedrag in boekhouding"); 
    scrfld(z++,25,1);
    if(only_klt) scrifld(z++,fm_os1,&lkg);
    else scrifld(z++,fm_uLKG,&lkg);
    scrfld(z++,1,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_udat,&dat_beg); scrifld(z++,fm_udat,&dat_end);
		scrifld(z++,fm_odat,&MinBkhDatum);
    scrifld(z++,fm_odat,&last_arc);
    if(allow_yr){
      for(k=0;k<3;k++) scrifld(z++,fm_odat,&clean_prev[k]);
      scrifld(z,fm_os30," F10 zoek op in jaaroverzicht ");scrchat(z++,0x08);
    }
    else{
      for(k=0;k<3;k++) scrifld(z++,fm_os3,"--");
    }
    mask_=0x48F; if(allow_yr) mask_=mask_ | 0x0200;
    key=scrupd(curs,mask_);curs=3;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101 || key==111) {ovlexit(-1);}
		if(key==5007){ZoekBedrag(); goto redo;}
    stu=3;DspTotRek=NO;
    if(lkg=='L') if(credt_allow) stu=1; else {errnum=34;curs=2;goto redo;}
    else if(lkg=='K') if(debit_allow) stu=2; else {errnum=34;curs=2;goto redo;}
    if(stu!=1)copy(s(1,3),s(stu,3),fldlen(stu,3));
		if(key==5001){
			if(search(stu,98)==0){
				if(stu!=1) copy(s(stu,3),s(1,3),fldlen(stu,3));
				curs=3; goto redo;
			}
	  }
    if(dat_beg && dat_beg<=clean_prev[stu-1]){errnum=37;curs=4; goto redo;}
    if(dat_end && dat_end<dat_beg){errnum=36;curs=5; goto redo;}
    if(key==110) get_jaar=YES; else get_jaar=NO;
    if(key==102 && (stu<3 || sys1834)) only_open=YES; else only_open=NO;
    if(key==103 && stu<3) only_verv=YES; else only_verv=NO;
    if(key==104) only_fact=YES; else only_fact=NO;
    if((ServerVersion>1 || StdInMono) && key==5005){
      if(dat_beg==0) {errnum=34;curs=4; goto redo;}
      if(dat_end==0) {errnum=34;curs=5; goto redo;}
      if(makegraf()) fasinit(1);
      goto redo;
    }
    if((ServerVersion>1 || StdInMono || ovltest(2240)) && key==5006 && stu>=1 && stu<=2){
			if(search(stu,0)){curs=3;goto redo;} 
			if(stu!=1)copy(s(stu,3),s(1,3),fldlen(1,3));
			ShowSavedDocument(stu,(long)(*u(stu,1)),0,dat_beg,dat_end) ;
      goto redo;
    }
		DeleteMode=NO; if(key==112) DeleteMode=YES;
    if(key==102) k=display(YES); else k=display(NO);
    if(k==YES) fasinit(1);
  }
	endsr:;
}
 
static display(mode_)/* NO=normal, YES=detail bij 4000/4400  */
{
  int j,k,key,curs=1,tbpos_;
  flag empty,mask_,goto_end=NO,factuurmode_;
	double bd_;

	only_dsp=NO;
#if FLAGGRS
  if(sys2698) only_dsp=YES;
#endif

	fasunlck(-1);
  if(search(stu,0)) return NO;
  Exec257=YES; if(stu<2 || ovltest(257)==NO) Exec257=NO;
  Exec263=YES; if(stu<2 || ovltest(263)==NO) Exec263=NO;
  Exec66=YES; if(stu>2 || ovltest(66)==NO) Exec66=NO;
	Exec33=YES; if(stu!=1 || ovltest(33)==NO) Exec33=NO;
  searcnr=*u(stu,1)+(stu-1)*30000; bew_key=4; if(stu==3) sear_grb=*l(stu,2);
  
  scrget(1,7);scrupd(-3,0);
  if(stu<3){
    corr_y2000(4,searcnr); if(get_jaar) corr_y2000(86,searcnr);
  }
	factuurmode_=0;
	if(stu<3  || sys1834){
		if(only_open) factuurmode_=1; 
		else if(only_verv) factuurmode_=2;
		else if(only_fact) factuurmode_=3;
	}
	
redo_full:;
	if(stu==3 && sys1834 && factuurmode_!=1) factuurmode_=0; // alleen maar openstaand of alles
	switch(factuurmode_){
  	case 1 : only_open=YES;only_verv=NO; only_fact=NO; break;
	  case 2 : only_open=NO;only_verv=YES; only_fact=NO; break;
		case 3 : only_open=NO;only_verv=NO; only_fact=YES; break;
		default : only_open=NO;only_verv=NO; only_fact=NO;break;
	}
	FillStkTab(mode_);
  eerste=YES;hoev=0; tabpos=0;
  bdt_deb=0;bdt_cre=0; p_scr=0; KoppelMode=NO; TotaalGekoppeld=0; CntGekoppeld=0;

  FOREVER{
		redo:;
    scrnum=0; scrget(1,97);empty=YES;
		scraddpicto(1,0,76,22,4,2,583,0,0,"PDF");
		scraddpicto(3,0,72,22,4,2,94,0,4,"Einde");
		scraddpicto(4,0,68,22,4,2,97,0,4,"Begin");
		scraddpicto(5,0,64,22,4,2,13,0,4,"Vorig");
		scraddpicto(6,0,60,22,4,2,18,0,4,"Volgend");
		if(KoppelMode && CntGekoppeld && is_nul(TotaalGekoppeld)) scraddpicto(9,0,50,20,4,2,69,0,4,"Koppel lijnen");
		if(stu<3 || sys1834){
			if(KoppelMode==NO) scraddpicto(8,0,50,5,4,1,69,0,6,"Koppel");
			else{
				scraddf(125,20,55,0x0A);
				scraddpicto(8,0,50,5,4,1,43,0,6,"Factuur");
			}
			if(factuurmode_==0) {
				scraddf(122,22,2,8);
				if(stu==3) scrifld(122,VarTextFmt(15,0)," F4 openstaand "); else scrifld(122,VarTextFmt(13,0)," F4 facturen ");
			}
			else{
				scraddf(123,22,16,8);scrifld(123,VarTextFmt(10,0)," F5 alles ");
		    scraddpicto(7,0,23,2,4,2,106,0,4,"Wijzig");
			}
		}

    if(Exec66 && only_klt==NO){
      scraddf(121,22,39,8);scrifld(121,fm_os20," F11 corr.referentie");
    }
    if(p_scr>=(DIM_STKTAB/12)+5) errnum=11;
    if((stu==1 && lvcd) || (stu==2 && klcd) || stu>2) scrofld(1,stu,2,8);
    else scrofld(1,stu,1,-1);
    scrofld(2,stu,3,-1);
    if(stu<3){scrofld(3,stu,8,-1);scrchat(3,0x02); }
    else scrfld(3,25,1);
    if(only_verv) scrifld(4,VarTextFmt(20,0)," Vervallen facturen ");
    if(only_open) scrifld(4,VarTextFmt(22,0)," Openstaande facturen ");
    if(only_fact) scrifld(4,VarTextFmt(16,0)," Enkel facturen ");
    p_scr++;scrifld(5,fm_ou4,&p_scr);p_scr--;
		k=(MaxStkTab-1)/12+1; scrifld(6,fm_ou4,&k);
    scrifld(7,fm_os3,dfmunt);scrifld(8,fm_os3,dfmunt);
    for(j=0;j<12;j++){
      if(DisplayLine(j)==NO) break;
      if(StkTab[p_scr*12+j]>0 && (StkTabFlag[p_scr*12+j]&0x10)==0) empty=NO;
    }
    if(tbs[p_scr+1].saldo>=0)  {bdt_deb=tbs[p_scr+1].saldo;bdt_cre=0;}
    else {bdt_cre=-tbs[p_scr+1].saldo;bdt_deb=0;}
    scr_bd(117,&bdt_deb);
    scr_bd(118,&bdt_cre);
    if(stu==3 && (sys1787&0x20)){
      scrifld(119,fm_ol7,&hoev);
    }
		else if(KoppelMode) scr_bd(125,&TotaalGekoppeld);
    next:;
    if(empty || only_dsp || stu==3 /* && !sys1834*/) curs=-1;
    mask_=0x49F; //if(empty) mask_=0xD8F;
    key=scrupd(curs,mask_); if(empty) curs=-1; else curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==15 && only_dsp){only_dsp=NO;goto redo;}
		prt2pdf=NO; 
		if(key>=5010 && key<5010+12){
			if(KoppelMode){
				tbpos_=p_scr*12+key-5010; 
				fasinit(stu_bew);*l(stu_bew,1)=StkTab[tbpos_]; fasgeti(stu_bew);
				bd_=*d(4,32); if(stu==1) bd_=-bd_;
				if(StkTabFlag[tbpos_]&0x02) {StkTabFlag[tbpos_]&=0xFD;TotaalGekoppeld-=bd_;CntGekoppeld--;}
				else {StkTabFlag[tbpos_]|=0x02;TotaalGekoppeld+=bd_;CntGekoppeld++;}
			}
			else{
				if(DeleteMode) DeleteLijn(p_scr*12+key-5010);
				else dsp_detail(p_scr*12+key-5010);
			}
		}
		if(key>=5030 && key<5030+12) dsp_factuur(p_scr*12+key-5030);
    if(empty) curs=-1; else curs=1;
    if(!empty && (stu<3 || sys1834)){ // bij GRB is er niks te updaten
			fasunlck(-2);
      for(k=0;k<12;k++){
			  if((p_scr*12+k)>=MaxStkTab) break;
				if(StkTabFlag[p_scr*12+k]&0x10) continue;
				fasinit(4);*l(4,1)=StkTab[p_scr*12+k]; 
				if(fasgeti(4)==0){
  				*s(4,8)=r_yy[k];
  				*s(4,9)=r_jr[k];
  				*u(4,10)=r_vl[k];
  				if(*s(4,9) || *u(4,10)){/* correctie y2000 */
  					if(*s(4,8)<50) *s(4,8)+=100;
  					else if(*s(4,8)>=150) *s(4,8)-=100;
  				} else if(*s(4,8)==100) *s(4,8)=0;
  				fasupd(4);
				}
			}
			fasunlck(-1);
    }
		if(key==101) break;
		switch(key){
			case 102  : p_scr--; if(p_scr<0) p_scr=0; break; // up
      case 103  : p_scr++;  if((p_scr*12)>=MaxStkTab) p_scr--; break; // down
			case 104  : factuurmode_=1; goto redo_full; break; // openstaande facturen
      case 105  : factuurmode_=0; goto redo_full; break; // alles
      case 108  : p_scr++;  if((p_scr*12)>=MaxStkTab) return YES; break; 
      case 111  : if(corr_ref()) return NO; break; 
		  case 5001 : prt2pdf=YES;print(); break; // pdf
			case 5002 : prt2pdf=NO;print(); break;  // print
			case 5003 : p_scr=(MaxStkTab-1)/12;break; // einde rekening 
			case 5004 : p_scr=0; break; // begin rekening 
      case 5005 : p_scr++;  if((p_scr*12)>=MaxStkTab) p_scr--; break;  // down
      case 5006 : p_scr--; if(p_scr<0) p_scr=0; break; // up
			case 5007 : factuurmode_++; if(factuurmode_>3) factuurmode_=1;goto redo_full; break; // wijzig factuurmode
      case 5008 : if(KoppelMode) KoppelMode=NO;
									else{
										TotaalGekoppeld=0; for(k=0;k<MaxStkTab;k++) StkTabFlag[k]&=0xFD;
										CntGekoppeld=0; KoppelMode=YES; // koppel - detail
									}
									break;
      case 5009 : KoppelLijnen(); break;
			default : break;
		}
  }
  return YES;
}

static DisplayLine(line)
int16 line;
{
  int16 k,attr_;
	int tbpos_,fl_factuur_;
  char *fmt_,fm_yy_[10];
  double bd_;

	tbpos_=p_scr*12+line;
	if(tbpos_>=MaxStkTab) return NO;
	if(StkTab[tbpos_]<0){
		fasinit(4);stu_bew=4;
		*d(stu_bew,32)=sal_deb-sal_cre;*u(stu_bew,4)=DatumVorigSaldo;
	}
	else{
		stu_bew=4;if(StkTabFlag[tbpos_]&0x10) stu_bew=86;
		fasinit(stu_bew);*l(stu_bew,1)=StkTab[tbpos_]; fasgeti(stu_bew);
	}
  dt_bew=*u(stu_bew,4);
  if(sys1787 & 0x10){ if(*u(stu_bew,20)) dt_bew=*u(stu_bew,20);}
  attr_=0xFF; if(StkTab[tbpos_]<0 || StkTabFlag[tbpos_]&0x01) attr_=0xB;
  journl=*s(stu_bew,2);fl_factuur_=NO;
	if(StkTab[tbpos_]>0){
		fl_factuur_=YES;
    for(k=0;k<80;k++) if(j_tab[k].nr==journl) break;
    if(k>=80 || j_tab[k].typ<1 || j_tab[k].typ>2) fl_factuur_=NO;/* enkel AK en VK */
    scrifld(9+line*9,fm_ou2,&journl);scrchat(9+line*9,attr_);
    scrofld(10+line*9,stu_bew,3,-1); scrchat(10+line*9,attr_);
	}
  scrifld(11+line*9,fm_odat,&dt_bew); scrchat(11+line*9,attr_);
  if(*d(stu_bew,32)<-0.009){
    *d(stu_bew,32)=-*d(stu_bew,32); bd_=*d(stu_bew,32);
    scr_bd(13+line*9,&bd_);scrchat(13+line*9,attr_); 
    bdt_cre+=*d(stu_bew,32);
  }
  else{
    bd_=*d(stu_bew,32);
    scr_bd(12+line*9,&bd_); scrchat(12+line*9,attr_);
    bdt_deb+=*d(stu_bew,32);
  }
  r_yy[line]=*s(stu_bew,8); if(r_yy[line]>=100) r_yy[line]-=100;
  r_yy_[line]=r_yy[line];
	if((stu>2 && !sys1834) && stu_bew==4 && bew_key!=3) copy(fm_us1_,fm_yy_,sizeof fm_us1_);
  else{
    copy(fm_uu2,fm_yy_,sizeof fm_uu2);
    if(stu_bew!=4 || StkTab[tbpos_]<0) fm_yy_[1]=0x90;
    if(*s(stu_bew,9) || *u(stu_bew,10)) fm_yy_[4]=0;
  }
	if(stu<3 || sys1834) {scrifld(14+line*9,fm_yy_,&r_yy[line]);scrchat(14+line*9,attr_);}
	if(StkTab[tbpos_]>0){
		r_jr[line]=*s(stu_bew,9);r_jr_[line]=r_jr[line];
		if(stu_bew!=4 || (stu>2 && !sys1834) || StkTab[tbpos_]<0) fmt_=fm_ou2; else fmt_=fm_uu2;
		scrifld(15+line*9,fmt_,&r_jr[line]); scrchat(15+line*9,attr_);
		r_vl[line]=*u(stu_bew,10);r_vl_[line]=r_vl[line];
		if(stu_bew!=4 || (stu>2 && !sys1834) || StkTab[tbpos_]<0) fmt_=fm_ou5; else fmt_=fm_uu5;
		scrifld(16+line*9,fmt_,&r_vl[line]); scrchat(16+line*9,attr_);
	} 
  if(stu==3){
    if(bew_key==4 && g_anal_tst()){
      mk_anal_opm(*l(stu_bew,11),s(stu_bew,28),fldlen(stu_bew,28));
    }
    if(bew_key==3){
      mk_kl_opm(*u(stu_bew,5),s(stu_bew,28),fldlen(stu_bew,28));
    }
  }
  hoev+=str2get(s(stu_bew,28));
  if(StkTab[tbpos_]<0){
    scrifld(17+line*9,fm_os11,"Vorig saldo");scrchat(17+line*9,attr_);
  }
  else{
    scrofld(17+line*9,stu_bew,28,11);scrchat(17+line*9,attr_);
  }
	if(KoppelMode==NO){
		if(DeleteMode){
			if(stu_bew==4) scraddpicto(10+line,0,50,7+line,2,1,141,0,6,"Schrap");
		}
  	else if(fl_factuur_){
  	  if(stu_bew==4) scraddpicto(10+line,0,50,7+line,2,1,141,0,6,"Detail");
  		if(stu==2) scraddpicto(30+line,0,52,7+line,2,1,43,0,6,"Factuur");
			else if(stu==1 && Exec33) scraddpicto(30+line,0,52,7+line,2,1,583,0,0,"Factuur"); 
  	}
	}
	else if(stu_bew==4){
		if(StkTabFlag[tbpos_]&0x02) scraddpicto(10+line,0,50,7+line,4,1,69,0,3,"Verbreek");
		else if(StkTabFlag[tbpos_]&0x01) scraddpicto(10+line,0,50,7+line,4,1,69,0,4,"Koppel");
	}
  return YES;
}

static ZoekBedrag()
{
  int16 j,k,z,key,curs=1,scrnr_=0,stu_,cnt_=0,start_=0,mode_;
  long tb_ft_[20];
	char soortfiche_='K';
	double bd_x;
	
	BdZoek=0;
  FOREVER{
    redo:
    scrget(1,282); z=1;fasunlck(0);
		scrifld(z++,fm_ud7_2,&BdZoek);
		scrifld(z++,fm_udat,&dat_beg); scrifld(z++,fm_udat,&dat_end);
		scrifld(z++,fm_uLKGA,&soortfiche_);
    key=scrupd(curs,0x81);curs=1;
    if(key==101) goto endsr;
    if(dat_end && dat_end<dat_beg){errnum=36;curs=3; goto redo;}
    if(dat_beg==0) {errnum=34;curs=2; goto redo;}
    if(dat_end==0) {errnum=34;curs=3; goto redo;}
    if(key!=108) goto redo;



		scrget(1,7);scrupd(-3,0);scrnr_=0;
		fasinfo(4,1); zero((char *)&zoekscr[0],sizeof zoekscr);pzoekscr=0;
		zero((char *)&tb_ft_[0],sizeof tb_ft_);
		fasinit(4);
		if(soortfiche_=='K') *u(4,5)=30000;
		else if(soortfiche_=='G') *u(4,5)=60000;
redo_zoek:;
		mode_=1;
		FOREVER{
			if(scrnr_==0){
				scrnum=0;
				scrget(1,82);z=1;scrnr_=82;
				scrxfld(&z,NO,&BdZoek,YES);	
				scraddf(126,21,45,4); scraddf(127,21,46,4);scrifld(126,VarTextFmt(14,0)," Zoeken... ");
				scrifld(z++,fm_os3,munt);
				start_=pzoekscr*15; cnt_=start_;
				if(zoekscr[pzoekscr]){fasinit(4); *l(4,1)=zoekscr[pzoekscr];fasgeti(4);}
			}
			if(faskeyi(4,4,mode_)) break; mode_=2;
			if(soortfiche_=='L' && *u(4,5)>30000) break;
			else if(soortfiche_=='K' && *u(4,5)>60000) break;
			if(*u(4,4)>=dat_beg && *u(4,4)<=dat_end && bd_zk_ok()){
				if(zoekscr[pzoekscr]==0) zoekscr[pzoekscr]=*l(4,1);
				j=cnt_+1;
				scrifld(z++,fm_ou3,&j);
				if(!is_voldaan(*l(4,1))) scrchat(z-1,0x8);
				else scrchat(z-1,0xFF);
				k=*s(4,2);scrifld(z++,fm_ou3,&k);
				scrofld(z++,4,3,-1);
				scrofld(z++,4,4,-1);
				bd_x=*d(4,32);
				scrxfld(&z,NO,&bd_x,NO);z--;
				if(*d(4,32)<0) scrifld(z++,fm_os1,"C"); else scrifld(z++,fm_os1,"D");
				stu_=get_4lkg();
				scrifld(z++,fm_os1,&lkglet[stu_-1]);
				k=fldlen(stu_,3);if(k>20) k=20;
				scrofld(z++,stu_,3,k);
				zk_rec[cnt_-start_]=*l(4,1); cnt_++;
				scrupd(-3,0);
				if((cnt_%15)==0) {if(_zoek_b(start_,cnt_)) goto endsr; scrnr_=0;}
			}

		}
    if(_zoek_b(start_,cnt_)==0) {scrnr_=0;goto redo_zoek;}
	}
  endsr:;
  for(k=1;k<=3;k++) fasinit(k);
}

static bd_zk_ok()
{
  double bd4_,bd_i_,afw_long=0;

  bd4_=*d(4,32);
  if(bd4_<0) bd4_=-bd4_;
  bd_i_=BdZoek;if(bd_i_<0) bd_i_=-bd_i_;
  if(bd4_>(bd_i_+afw_long+.005) || bd4_<(bd_i_-afw_long-.005)) return NO;
  return YES;
}

static _zoek_b(start_,cnt_)
int16 start_,cnt_;
{
  int16 fuval=0,key,g,k,ln_=0,stu_;

  FOREVER{
    // scrifld(4+15*8,fm_uu3,&ln_);
		scrifld(127,VarTextFmt(13,0),"            ");
    key=scrupd(-1,0xA7);
    if(key==101 || key==106){fuval=106;goto endsr;}
    if(key==102){
      if(pzoekscr) pzoekscr--; fuval=0;goto endsr;
    }
    if(key==103){
      if((cnt_-start_)>=15 && pzoekscr<DIMZOEK) pzoekscr++;
      fuval=0; goto endsr;
    }
		if(key==108){fuval=0; goto endsr;}

    //if(key==108 || ln_){
    //  if(ln_>start_ && ln_<=cnt_){
				//*l(4,1)=zk_rec[ln_-1-start_];fasgeti(4);
				//stu_=get_4lkg();
				//lkg=lkglet[stu_-1];
				//if(stu_<3){
				//	if(fldlen(stu_,2)){
				//		g=0;if(*s(stu_,2)<'0' || *s(stu_,2)>'9'){lkgnaam[0]='.';g=1;}
				//		copy(s(stu_,2),&lkgnaam[g],fldlen(stu_,2)+g);
				//		for(k=0;k<fldlen(stu_,2)+g;k++) if(lkgnaam[k]=='\0') break;
				//		for(k;k<fldlen(stu_,2)+g;k++) lkgnaam[k]=' ';
				//	}
				//	else {stcli_d(lkgnaam,(long)(*u(stu_,1)),5,0);k=5;}
				//	lkgnaam[k++]=' ';
				//	copy(s(stu_,3),&lkgnaam[k],fldlen(stu_,3));
				//}
				//else{
				//	grb_deco(lkgnaam,l(3,2));
	   //     for(g=0;g<9;g++) if(lkgnaam[g]=='\0') lkgnaam[g]=' ';
	   //     g=fldlen(3,3);if(g>MAXLEN-9)g=MAXLEN-9;
	   //     copy(s(3,3),&lkgnaam[9],g);
				//	//copy(s(stu_,3),lkgnaam,fldlen(stu_,3));
				//}
				//ref_yy=*s(4,8);
				//ref_jr=*s(4,9);
				//if(ref_ft && is_nul(bd_inp)) bd_inp=*pd_4_32;
				//ref_ft=*u(4,10);
				//fuval=108;break;
    //  }
    //}
    //else goto endsr;
  }
  endsr:;
  return fuval;
}

static is_voldaan(rec4_)
long rec4_;
{
  int16 mode_,ret_val_;
  uint16 lkg_rec_,ref_jr_,ref_jn_,ref_vl_;
  double bd_;

  ret_val_=NO;
  copy(s(4,1),buff1000,fldlen(4,0));
  fasinit(4);*l(4,1)=rec4_;fasgeti(4);
  if(*u(4,5)>=60000) {ret_val_=YES;goto endsr;}/* GRB's steeds voldaan */
  if(*s(4,8)==0 && *s(4,9)==0 && *u(4,10)==0) goto endsr;
  ref_jr_=*s(4,8);ref_jn_=*s(4,9);ref_vl_=*u(4,10);lkg_rec_=*u(4,5);
  fasinit(4);*u(4,5)=lkg_rec_;*s(4,8)=ref_jr_;*s(4,9)=ref_jn_;*u(4,10)=ref_vl_;
  bd_=0;mode_=1;
  FOREVER{
    if(faskeyi(4,4,mode_)) break; mode_=2;
    if(*u(4,5)!=lkg_rec_) break;
    if(*s(4,8)!=ref_jr_ || *s(4,9)!=ref_jn_ || *u(4,10)!=ref_vl_) break;
    if(is_nul(*d(4,32))){
      *d(4,32)=valu_cnv(def_munt,"EUR",(double)(*l(4,7)),(double)0.01);
    }
    bd_+=*d(4,32);
  }
  if(is_nul(bd_)) ret_val_=YES;
  endsr:;
  copy(buff1000,s(4,1),fldlen(4,0));
  return ret_val_;
}

static get_4lkg()
{
  int16 stu_;
  uint16 rec_;

  if(*u(4,5)<30000){rec_=*u(4,5);stu_=1;}
  else if(*u(4,5)<60000){rec_=*u(4,5)-30000;stu_=2;}
  else{rec_=*u(4,5)-60000;stu_=3;}
  fasinit(stu_);*u(stu_,1)=rec_;fasgeti(stu_);
  return stu_;
}

static scrxfld(pz,upd,pd,muntdisp)
int16 *pz;
double *pd;
flag upd,muntdisp;
{
  char fmt_[40];

  copy(fm_od9_2,fmt_,sizeof fmt_);
  if(upd) fmt_[1]|=0x40;/* update */
  scrifld((*pz)++,fmt_,pd);
  if(muntdisp) scrifld(*pz,fm_os3,munt);
  (*pz)++;
}


static DeleteLijn(j)
int j;
{
  int16 z,k,key;
  uint16 klgrec_;
  char buf4_[500];

	if(StkTabFlag[j]&0x10) goto endsr; // niet uit jaararchief 
	if(StkTab[j]==0) goto endsr;
	if(DisplayWarning("Wenst u echt deze record te schrappen/wijzigen???",61,1)==NO) goto endsr;
  copy(s(4,1),buf4_,fldlen(4,0));
  klgrec_=*u(stu,1);
  zeroL((char *)&fdet[0].bedrag,sizeof fdet);
  fasinit(4);*l(4,1)=StkTab[j];fasgeti(4);
	scrget(1,170);z=3;
	scrifld(z++,fm_os63,"Wenst U volgende lijn te schrappen ?"); z+=3;
	k=*s(4,2); scrifld(z++,fm_uu5,&k);
	scrofld(z++,4,3,-1);
	scrofld(z++,4,4,-1);z++;
	scrfld(z++,4,32);
	scrifld(16,fm_os63,"F4 SCHRAP     F1/F5 schrap NIET (terug)   F10 PAS BEDRAG AAN");
	key=scrupd(1,0x219);
	if(key==104) {faskill(4);StkTab[j]=0;}
	if(key==110) fasupd(4);
	endsr:;
}


static KoppelLijnen()
{
	int j,k;
	uint16 r_yy_=0,r_jn_=0,r_vl_=0;

	for(k=0;k<MaxStkTab;k++){ // zoeken naar referentie van 1-ste factuur 
		if(StkTabFlag[k]&0x02){
			fasinit(4);*l(4,1)=StkTab[k]; fasgeti(4);
			for(j=0;j<80;j++) if(j_tab[j].nr==*s(4,2)) break;
      if(j<80 && (j_tab[j].typ==1 || j_tab[j].typ==2)){ // enkel factuur 
				jddate(*u(4,4),&r_yy_,&r_jn_,&r_vl_); r_yy_%=100; if(r_yy_<50) r_yy_+=100;/* y2000 */
				r_jn_=*s(4,2);r_vl_=*u(4,3);
				break;  
			}
		}
	}
	if(r_yy_==0 || r_jn_==0 || r_vl_==0){ // indien leeg, dan omgekeerde datum
		jddate(*u(25,2),&r_yy_,&r_jn_,&r_vl_); r_yy_%=100; if(r_yy_<50) r_yy_+=100;/* y2000 */
	}
	for(k=0;k<MaxStkTab;k++){
		if(StkTabFlag[k]&0x02){
			fasinit(4);*l(4,1)=StkTab[k]; fasgeti(4);
			*i(4,8)=r_yy_;*s(4,9)=r_jn_;*u(4,10)=r_vl_; 
			fasupd(4); StkTabFlag[k]&=0xFC; 
		}
	}
	CntGekoppeld=0; TotaalGekoppeld=0;
}

static corr_y2000(bstu_,searcnr_)    /* Y2000 probleem oplossen tijdelijk tot 2005 */
uint16 bstu_,searcnr_;
{
  char *ry_,*rjn_,ly_;
  uint16 *prec_,*rvl_,mode_,len_stu_;
									
  scrget(1,7);scrupd(-3,0);
  prec_=u(bstu_,5);ry_=s(bstu_,8);
  rjn_=s(bstu_,9); rvl_=u(bstu_,10); len_stu_=fldlen(bstu_,0);
  fasinit(bstu_); *prec_=searcnr_; mode_=1; ly_=*ry_;
  FOREVER{
    if(faskeyi(bstu_,4,mode_)) break; mode_=2;
    if(*prec_!=searcnr_) break;
		if(*ry_>=100) break; // geen foute referenties 
    ly_=*ry_;
    if(*rjn_ || *rvl_){
      if(*ry_<50) *ry_+=100;
    } else if(*ry_==100) *ry_=0;
    if(*ry_!=ly_) { fasupd(bstu_); mode_=1;}             /* indien gewijzigd, updaten */
    *ry_=ly_;                                      /* key-volgorde behouden */
  }
}
 
static makegraf()
{
  int16 g,k,mode_,yy,dd,mm,max_gkol,neg_,len_gstr_,tot_rek_;
  uint16 dt_,*p_dt_,dt_graf[51],journl_,*prec_;
  float bd_graf[51];
  double bd_;
  long color,*p_grb_,n;
  char str_[80],gstr_[10];
 
  scrget(1,7);scrupd(-3,0);
  DspTotRek=YES;
  if(search(stu,0)) return NO;
  if(dat_beg==0 || dat_end==0){errnum=6; return NO;}
  searcnr=*u(stu,1)+(stu-1)*30000;
  if(stu==3){
    sear_grb=*l(stu,2);tot_rek_=NO;
    if(*s(3,10)>'0'){
      tot_rek_=YES;
      zeroL(gstr_,sizeof gstr_);
      grb_deco(gstr_,&sear_grb);
      for(len_gstr_=0;len_gstr_<8;len_gstr_++) if(gstr_[len_gstr_]=='\0') break;
    }
  }
 
  zeroL((char *)&dt_graf[0],sizeof dt_graf);
  dt_=dat_beg;
  for(max_gkol=0;max_gkol<50;max_gkol++){
    jddate(dt_,&yy,&mm,&dd);
    mm++;if(mm>12) {mm=1;yy++;}
    dt_=datejd(yy,mm,1)-1;
    if(dt_>dat_end) dt_=dat_end;
    dt_graf[max_gkol]=dt_;
    dt_++;
    if(dt_>=dat_end) break;
  }

  max_gkol++;
  zeroL((char *)&bd_graf[0],sizeof bd_graf);
  if(allow_yr) stu_bew=86; else stu_bew=4;
  scrget(1,170);scrifld(10,fm_os63,"Bezig met berekenen...");scrupd(-3,0);
  redo_load:;
  fasinit(stu_bew);*u(stu_bew,5)=searcnr;mode_=1;
  p_dt_=u(stu_bew,4);p_grb_=l(3,2);prec_=u(stu_bew,5);scrnum=0;n=0;
  FOREVER{
    next_bew:;
    if(stu==3 && tot_rek_){
      if(stu_bew==86) *l(86,1)=++n; else *l(4,1)=++n;
      g=fasgeti(stu_bew);
      if(g==47)break;
      if(g) goto next_bew;
      if(*prec_<60000) goto next_bew;
      fasinit(3);*u(3,1)=*prec_-60000; fasgeti(3);
      grb_deco(str_,p_grb_);
      if(cmpstr(gstr_,str_,len_gstr_)) goto next_bew;
    }
    else{
      if(faskeyi(stu_bew,4,mode_)) break; mode_=2;
      if(*u(stu_bew,5)!=searcnr) break;
    }
    if(*p_dt_<dat_beg || *p_dt_>dat_end) goto next_bew;
    if(stu<3){
      journl_=*s(stu_bew,2);
      for(k=0;k<80;k++) if(j_tab[k].nr==journl_) break;
      if(k>=80 || (stu==1 && j_tab[k].typ!=1) || (stu==2 && j_tab[k].typ!=2)) goto next_bew;
    }
    for(k=0;k<max_gkol;k++) if(dt_graf[k]>=*p_dt_) break;
    bd_graf[k]+=*d(stu_bew,32);
  }
  if(stu_bew==86){stu_bew=4;goto redo_load;}
  scrget(1,170);scrifld(10,fm_os63,"Opmaken grafiek ...");scrupd(-3,0);

  neg_=NO;
  if(stu==3){
    fasinit(3);*u(3,1)=searcnr-60000;fasgeti(3);
    grb_deco(str_,l(3,2));
    if(str_[0]=='7') neg_=YES;
  }
  if(stu==1) neg_=YES;

  zeroL(str_,sizeof str_);
  k=copy0("Rek_",str_,4);k+=copy0(s(stu,3),&str_[k],10);k+=copy0(".XLS",&str_[k],4);
  XlsRef=XlsCreate(str_);
  if(XlsRef<=0) {errnum=1;return NO;}
	XlsRij=1+XLS_FIRST_DATA_ROW;XlsKol=1;
  XlsWrite(XlsRef,XlsRij,1,0,"Maand",0);
  XlsWrite(XlsRef,XlsRij,2,0,"Bedrag",0);
	XlsRij++;
  for(k=0;k<max_gkol;k++){
    jddate(dt_graf[k],&yy,&mm,&dd);
    zeroL(str_,sizeof str_); str_[0]='\'';
    if(mm>=1 && mm<=12) copy(mnd_str[mm-1],&str_[1],3);
    else copy("   ",&str_[1],3);
    str_[4]=' ';
    stcli_d(&str_[5],(long)yy,4,0);
    XlsWrite(XlsRef,XlsRij+k,1,0,str_,0);
    bd_=round((double)bd_graf[k]); if(neg_) bd_=-bd_;
    XlsWrite(XlsRef,XlsRij+k,2,2,&bd_,0);
  }
  k=copy0(s(stu,3),str_,30);
  copy("\x0D\x0A",&str_[k],2);k+=2;
  k+=date2str(&str_[k],dat_beg);
  str_[k++]='-';k+=date2str(&str_[k],dat_end);
  XlsChart(XlsRef,max_gkol,1,0,str_);
  color=0x00FF00L;
/*   XlsGraf(XlsRef,1,1,color); */
						
 // XlsSaveAsPdf(XlsRef);
  XlsClose(XlsRef,1);

  endsr:;
  return YES;
}

static int16 date2str(str_,date_)
char *str_;
uint16 date_;
{
  int16 dd,mm,jj,len_=0;
								
  if(date_==0) goto endsr;
  jddate(date_,&jj,&mm,&dd);
  stcli_d(&str_[len_],(long)dd,2,0);len_+=2;str_[len_++]='/';
  stcli_d(&str_[len_],(long)mm,2,0);len_+=2;str_[len_++]='/';
  stcli_d(&str_[len_],(long)jj,4,0);len_+=4;
  endsr:;
  return len_;
}

static copy0(ps,pd,len)
char *ps,*pd;
int16 len;
{
  int16 k;
						
  for(k=0;k<len;k++) if(*(ps+k)=='\0') break;
  copy(ps,pd,k);
  return k;
}

#include "Std\XlsFunc.c"

static  make_otab(tb_open,p_tbbeg_,p_tbmax_,dt_bew_end_)
long tb_open[];
uint16 p_tbbeg_,p_tbmax_,dt_bew_end_;
{
  int k,pos_,posr_,mpos_,qlijnen_,end_;
  uint16 first, r_yy,r_jr,r_nr,dt_factuur_,dt_open_[DIM_OPEN];
  double ebd_;

  fasinit(4);
  searcnr=*u(stu,1)+(stu-1)*30000;
  *u(4,5)=searcnr;

  first=YES; end_=NO; posr_=p_tbbeg_; pos_=p_tbbeg_; ebd_=0;zero((char *)&dt_open_[0],sizeof dt_open_);
  FOREVER{
		next:;
    if(faskeyi(4,4,2)) end_=YES;
    if(!end_ && *u(4,5)!=searcnr) end_=YES;
		if(!end_ && dt_bew_end_ && *u(4,4)>dt_bew_end_) goto next;
    if(!end_ && first){
      r_yy=*s(4,8); r_jr=*s(4,9); r_nr=*u(4,10);
      first=NO;
    }
    if(end_ || *s(4,8)!=r_yy || r_jr!=*s(4,9) || r_nr!=*u(4,10)){
      if(is_nul(ebd_)){
				for(k=posr_;k<pos_;k++) {tb_open[k]=0;dt_open_[k]=0;}
				pos_=posr_;dt_factuur_=0;
      }
			if(pos_!=posr_ && dt_factuur_){// facturen proberen chronologisch te zetten, indien boekjaar niet op 1/1 start
				for(mpos_=0;mpos_<posr_;mpos_++) if(dt_open_[mpos_] && dt_factuur_<dt_open_[mpos_]) break;
				
				if(mpos_<posr_ && ((pos_-posr_)<(DIM_OPEN-pos_))){
					qlijnen_=pos_-posr_;
					copy((char *)&tb_open[posr_],(char *)&tb_open[DIM_OPEN-qlijnen_],(sizeof tb_open[0])*qlijnen_);
					copy((char *)&dt_open_[posr_],(char *)&dt_open_[DIM_OPEN-qlijnen_],(sizeof dt_open_[0])*qlijnen_);

					for(k=pos_-1;k>=mpos_+qlijnen_;k--){tb_open[k]=tb_open[k-qlijnen_];dt_open_[k]=dt_open_[k-qlijnen_];}

					copy((char *)&tb_open[DIM_OPEN-qlijnen_],(char *)&tb_open[mpos_],(sizeof tb_open[0])*qlijnen_);
					copy((char *)&dt_open_[DIM_OPEN-qlijnen_],(char *)&dt_open_[mpos_],(sizeof dt_open_[0])*qlijnen_);

					zero((char *)&tb_open[DIM_OPEN-qlijnen_],(sizeof tb_open[0])*qlijnen_);
					zero((char *)&dt_open_[DIM_OPEN-qlijnen_],(sizeof dt_open_[0])*qlijnen_);

				}
			}
      ebd_=0;posr_=pos_;
      r_yy=*s(4,8); r_jr=*s(4,9); r_nr=*u(4,10);
      if(end_) break;
    }
    if((dat_beg==0 || *u(4,4)>=dat_beg) && (dat_end==0 || *u(4,4)<=dat_end)){
			if(only_verv==NO || *u(4,21)<=dt_vandaag) {
				tb_open[pos_]=*l(4,1);
				if(IsFactuur((int)(*s(4,2)))){
					dt_open_[pos_]=*u(4,4);dt_factuur_=*u(4,4);
				}
				else dt_open_[pos_]=0;
				pos_++;
			}
    }
    ebd_+=*d(4,32);
    if(pos_>=p_tbmax_) break;
  }
}

static corr_ref()
{
  uint16 klgrec_;
  char buf4_[500];
									
  if(searcnr>60000) return NO;/* enkel klt/lev */
	if(ovltest(66)==NO) return NO;
  if(stu==2) klgrec_=searcnr-30000; else klgrec_=searcnr;
  copy(s(4,1),buf4_,fldlen(4,0));
  *u(26,1)=66; *u(26,5)=searcnr; ovlcall(66,0);
  copy(buf4_,s(4,1),fldlen(4,0));
  fasinit(stu);*u(stu,1)=klgrec_;fasgeti(stu);
  if(stu!=1) copy(s(stu,3),s(1,3),fldlen(1,3));
  return YES;
}


static get_lkgsal(dt_saldo_end_)  // TOT en NIET met
uint16 dt_saldo_end_;
{
  int16 yy_,mm_,dd_,mnd_strt;
  uint16 dt_sbeg,dt_bj_b_,dt_bj_e_;

  sal_deb=0;sal_cre=0;
  if(dt_saldo_end_==0) goto endsr;
  dt_sbeg=0;
  if(stu==3){
    sysget(1866,2,&mnd_strt);
    jddate(dt_saldo_end_,&yy_,&mm_,&dd_);
    yy_%=100; if(mnd_strt>mm_) yy_--; if(yy_<0) yy_=99;/* jaar 2000 */
    dt_bj_b_=datejd(yy_,mnd_strt,1);/* 1/1 van geselecteerd boekjaar */
    dt_bj_e_=datejd(yy_+1,mnd_strt,1)-1;/* 31/12 van geselecteerd boekjaar */
    dt_sbeg=dt_bj_b_;
  }
/* bereken saldo over deze periode */
  if(stu==1 || stu==2){/* enkel openstaande stk tot beg.datum */
    add_saldo(dt_sbeg,dt_saldo_end_,4);
  }
  else{
    if(dt_sbeg<=last_arc && allow_yr){/* GRB indien nodig ook uit BKA halen */
      add_saldo(dt_sbeg,dt_saldo_end_,86);
    }
    add_saldo(dt_sbeg,dt_saldo_end_,4);
  }
  endsr:;
}

static add_saldo(dt_b_,dt_e_,bstu_)
uint16 dt_b_,dt_e_,bstu_;
{
  int16 mode_,sal_fnd_;
  double bedrag_;

  sal_fnd_=NO; fasinit(bstu_); mode_=1;
  if(stu<3 || bstu_==86){
    *u(bstu_,5)=searcnr;
  }
  else{
    *l(bstu_,6)=sear_grb;
  }
  FOREVER{
    if(stu<3 || bstu_==86){
      if(faskeyi(bstu_,4,mode_)) break; mode_=2;
      if(*u(bstu_,5)!=searcnr) break;
    }
    else{
      if(faskeyi(bstu_,3,mode_)) break; mode_=2;
      if(*l(bstu_,6)!=sear_grb) break;
    }
    if(*u(bstu_,4)>=dt_b_ && *u(bstu_,4)<dt_e_){
      bedrag_=*d(bstu_,32);
      if(bedrag_>=0){
	sal_deb+=bedrag_;
      }
      else {
	sal_cre-=bedrag_;
      }
      sal_fnd_=YES;
    }
  }
  return sal_fnd_;
  endsr:;
}

static dsp_factuur(p_rec4_)
long p_rec4_;
{
  int16 k,bstu_;
  uint16 journl_,volgnr_,bk_dat_,klgrec_;
	int16 jaartal,mm,dd,jj,use_Afile=NO;
  char ofname[60],subdir[25];
 
	bstu_=4; if(StkTabFlag[p_rec4_]&0x10) bstu_=86;
	fasinit(bstu_);*l(bstu_,1)=StkTab[p_rec4_];fasgeti(bstu_);
  klgrec_=*u(stu,1);
  journl_=*s(bstu_,2);volgnr_=*u(bstu_,3); bk_dat_=*u(bstu_,4);
  for(k=0;k<80;k++) if(j_tab[k].nr==journl_) break;
  if(k>=80 || (stu==1 && j_tab[k].typ!=1) || (stu==2 && j_tab[k].typ!=2)) goto endsr;/* enkel facturen */
  if(stu==1){
		zero(ofname,sizeof ofname);
		zero(subdir,sizeof subdir);sysget(1731,25,subdir);
	    if(subdir[0]=='\0') sysget(4704,25,subdir);// indien leeg dan verkoopmap nemen
		copy(subdir,ofname,25);
    jddate(bk_dat_,&jaartal,&mm,&dd);
		if(mnd_strt!=1){// indien boekjaar NIET op 1/1 begint, dan uitkijken met overlappende factuurnummers
			if(mm>=mnd_strt) use_Afile=YES; // indien in nieuw BOEKjaar van huidig kalenderjaar
		}
		jaartal%=100; 
    for(k=0;k<25;k++) if(ofname[k]=='\0') break;
		copy("AK",&ofname[k],2);k+=2;
		copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';k+=3;
		stcli_d(&ofname[k],(long)(volgnr_),5,0);k+=5;
		stcli_d(&ofname[k],(long)(*u(stu,1)),5,0);k+=5;
    ofname[k++]='.';stcli_d(&ofname[k],(long)jaartal,2,0);k+=2;
    if(use_Afile)	{
			ofname[k++]='A';
		  if(FileExist(ofname)==NO) ofname[k-1]='\0'; // indien niet bestaand, dan zonder A
		}
		else {
			if(FileExist(ofname)==NO) ofname[k++]='A';// indien niet bestaand, dan met A
		}
		zero(BestelFileUsed[0],sizeof BestelFileUsed[0]);copy(ofname,BestelFileUsed[0],sizeof ofname);
		ovlcall(33,1);
	}
	else{
		*u(26,1)=1; *u(26,2)=bk_dat_;*u(26,5)=volgnr_; *u(26,26)=*u(2,1);
		if(ovltest(257)) ovlcall(257,0); 
		else if(ovltest(263)) ovlcall(263,0);
	}
  endsr:;
  fasinit(stu);*u(stu,1)=klgrec_;fasgeti(stu);
}

static dsp_detail(p_rec4_)
long p_rec4_;
{
  int16 z,k,key,start_=0,aard,mode_,ptb;
  double factor_;
  uint16 journl_,volgnr_,bk_dat_,kl_stu_,klgrec_;
  long mast4_;
  char buf4_[500];

	if(StkTabFlag[p_rec4_]&0x10) goto endsr; // niet uit jaararchief 
  copy(s(4,1),buf4_,fldlen(4,0));
  klgrec_=*u(stu,1);
  zeroL((char *)&fdet[0].bedrag,sizeof fdet);
  fasinit(4);*l(4,1)=StkTab[p_rec4_];fasgeti(4);
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
	fdet[ptb].bedrag=*d(stu_bew,32)*factor_;
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
      fdet[ptb].bedrag=*d(stu_bew,32)*factor_;
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
  fasinit(stu);*u(stu,1)=klgrec_;fasgeti(stu);
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

static streepje(z_)
int16 z_;
{
  scrifld(z_,fm_os1,"-");
}

static print()
{
  int16 k,z,dum1,dum2,len;
	int ptb_;
  char str_[20];

  getsysprNew(3,form_dat,&pr_mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if(prtopen(prtnr,form_dat,6,132,pr_mode,4)!=0) return NO;
  free=999;
  prtfld(25,1,30);
  prttext("<t32b>Rekening ");
	if(fldlen(stu,2)) prtfld(stu,2,-1); else prtfld(stu,1,-1);
  prttext("  "); prtfld(stu,3,30);prttext("<b>");
	if(only_verv) prttext("   (vervallen facturen)");
  if(only_open) prttext("   (openstaande facturen)");
  if(only_fact) prttext("   (enkel facturen)");
  prttext("<t95>"); prtifld(fm_udat,&dat_beg,-1); prttext(" - "); prtifld(fm_udat,&dat_end,-1);
  prttext("<t123>Blz.<ppp>.");
  prtbuf(1);z=1;
  prtitab(z,fm_ou2s,&jaar,1,-1); prttitle(z++,"Jr",3);
  prtitab(z,fm_ou2,&journl,2,-1); prttitle(z++,"Jrn",3);
  prtitab(z,fm_uu5,&volgnr,1,-1); prttitle(z++,"Volgn",3);
  prtitab(z,fm_udat,&dt_bew,2,-1); prttitle(z++,"Datum",0x43);
  copy("D-bedrag    ",str_,13); copy(dfmunt,&str_[9],3);
  prtitab(z,fm_obd,&bd_deb,2,-1); prttitle(z++,str_,0x13);
  str_[0]='C';
  prtitab(z,fm_obd,&bd_cre,2,-1); prttitle(z++,str_,0x13);
  if(fldlen(4,15)){
    prtitab(z,fm_od9_2,&bd_vm,1,-1); prttitle(z++,"Bedrag",0x13);
    prtitab(z,fm_os3,munt,1,-1); prttitle(z++,"VM",0x13);
  }
	if(!(lkg=='G' && sys1787&0x01)){
		prtitab(z,fm_ou4,&ref_yy,1,-1); prttitle(z++,"Jr",3);
		prtitab(z,fm_ou2,&ref_jr,2,-1); prttitle(z++,"Jrn",3);
		prtitab(z,fm_uu5,&ref_vl,1,-1); prttitle(z++,"Volgn",3);
	}
  z_cumsal=z;
  prtitab(z,fm_obd,&cum_saldo,1,-1); prttitle(z++,"Cum.saldo",0x13);
  z_opm=z;
  prtitab(z,fm_os20,opm_bkh,1,-1); prttitle(z++,"Opmerking",3);
  if(lkg=='G' && sys1787&0x01) prttext(" <bu>Tegenrekening<bu>");
  prtbuf(3);
	zeroL(str_,sizeof str_);
  copy("Rekening ",str_,9);copy0(s(stu,3),&str_[9],10);
  p_pdfname(str_,dat_beg,dat_end);
	bdt_deb=0;bdt_cre=0;hoev=0;
	for(ptb_=0;ptb_<MaxStkTab;ptb_++){
		if(StkTab[ptb_]<0){
      prttitle(1," Vorig saldo",2);
			bd_deb=sal_deb;bd_cre=sal_cre;dt_bew=DatumVorigSaldo;
      prtinfo(5,2);prtinfo(6,2);
			bdt_deb+=bd_deb; bdt_cre+=bd_cre;
      cum_saldo=bdt_deb-bdt_cre;prtinfo(z_cumsal,0);
      nextline();
    }
		else{
			stu_bew=4; if(StkTabFlag[ptb_]&0x10) stu_bew=86;
			fasinit(stu_bew);*l(stu_bew,1)=StkTab[ptb_]; fasgeti(stu_bew);
			dt_bew=*u(stu_bew,4);  if((sys1787 & 0x10) && *u(stu_bew,20)) dt_bew=*u(stu_bew,20);
      jddate(*u(stu_bew,4),&jaar,&dum1,&dum2);jddate(*u(25,2),&k,&dum1,&dum2);
      jaar=jaar%100; journl=*s(stu_bew,2); volgnr=*u(stu_bew,3);
			if(*d(stu_bew,32)<-0.009){bd_cre=-*d(stu_bew,32);bd_deb=0;}
			else{bd_deb=*d(stu_bew,32); bd_cre=0;}
      ref_yy=*s(stu_bew,8);
      ref_jr=*s(stu_bew,9);
      ref_vl=*u(stu_bew,10);
      if(ref_jr || ref_vl) ref_yy+=1900;/* y2000        */
      if(fldlen(4,15)){copy(s(stu_bew,15),munt,3); bd_vm=*d(stu_bew,16);}
			if(stu==3){
				if(bew_key==4 && g_anal_tst()){
					mk_anal_opm(*l(stu_bew,11),s(stu_bew,28),fldlen(stu_bew,28));
				}
				if(bew_key==3){
					mk_kl_opm(*u(stu_bew,5),s(stu_bew,28),fldlen(stu_bew,28));
				}
			}
			hoev+=str2get(s(stu_bew,28));
			len=fldlen(stu_bew,28);if(len>40) len=40;
			copy(s(stu_bew,28),opm_bkh,len);opm_bkh[len]='\0';
			bdt_deb+=bd_deb; bdt_cre+=bd_cre;
	    cum_saldo=bdt_deb-bdt_cre;
	    for(z=0;z<30;z++) prtinfo(z,0);
      if(lkg=='G' && sys1787&0x01) prt_tegen();
      zeroL(opm_bkh,sizeof opm_bkh);
      nextline();
    }
	}
  prttitle(1," Nieuw saldo",2);
  if(bdt_deb>bdt_cre) {bd_deb=bdt_deb-bdt_cre;prtinfo(5,2);}
  else {bd_cre=bdt_cre-bdt_deb;prtinfo(6,2);}
  if(stu==3 && (sys1787&0x20) && hoev){
    stcli_d(opm_bkh,hoev,7,1);
    prtinfo(z_opm,2);
  }
  nextline();
  prtclose();
  return YES;
}

static mk_kl_opm(rek_,ps_,len_)
char *ps_;
uint16 rek_;
int16 len_;
{
  int16 stu_;
  char buf_[50];
							
  zeroL(buf_,sizeof buf_); copy(s(3,1),buf750,fldlen(3,0));
  if(rek_<30000) stu_=1;
  else if(rek_<60000) stu_=2;
  else goto endsr;
  fasinit(stu_); *u(stu_,1)=rek_-((stu_-1)*30000); if(fasgeti(stu_)) goto endsr;
  copy(s(stu_,3),buf_,fldlen(stu_,3));
  copy(buf_,ps_,len_);
  endsr:;
  copy(buf750,s(3,1),fldlen(3,0));
}

static mk_anal_opm(rek_,ps_,len_)
char *ps_;
long rek_;
int16 len_;
{
  int16 k;
  char buf_[50];

  zeroL(buf_,sizeof buf_); copy(s(3,1),buf750,fldlen(3,0));
  fasinit(3); *l(3,2)=rek_;faskeyi(3,1,0);
  grb_deco(buf_,l(3,2));
  for(k=0;k<9;k++) if(buf_[k]=='\0') break;
  buf_[k++]=' '; copy(s(3,3),&buf_[k],fldlen(3,3));
  copy(buf_,ps_,len_);
  copy(buf750,s(3,1),fldlen(3,0));
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

static FillStkTab(int16 mode_) // NO=normal, YES=detail bij 4000/4400 
{
	int j,k,n,ks;
	long tb_voor_min_dt_[DIM_OPEN];
	    
	scrget(1,7);scrupd(-3,0);
	searcnr=*u(stu,1)+(stu-1)*30000;
	zeroL((char *)open_recs,sizeof open_recs);
	MaxStkTab=0;zeroL((char *)&StkTab[0],sizeof StkTab);zeroL((char *)&StkTabFlag[0],sizeof StkTabFlag);
	zeroL((char *)tbs,sizeof tbs);p_scr=0;
	zeroL(tb_voor_min_dt_,sizeof tb_voor_min_dt_);
	sal_deb=0;sal_cre=0; bdt_deb=0;bdt_cre=0;
	
  if(stu<3 || sys1834){ // tabel openstaande facturen laden voor oa display
    corr_y2000(4,searcnr); if(get_jaar) corr_y2000(86,searcnr);
    make_otab(open_recs,0,DIM_OPEN,0);
  }
	
	if(only_verv || only_open){
		for(MaxStkTab=0;MaxStkTab<DIM_OPEN;MaxStkTab++){
			if(MaxStkTab && (MaxStkTab%12)==0){	p_scr++;tbs[p_scr].saldo=bdt_deb-bdt_cre;} // schermtotalen bijhouden 
			if(open_recs[MaxStkTab]==0) break;
			StkTab[MaxStkTab]=open_recs[MaxStkTab]; StkTabFlag[MaxStkTab]=1;
			fasinit(4);*l(4,1)=StkTab[MaxStkTab];fasgeti(4);
			if(*d(4,32)<-0.009)	bdt_cre+=-*d(4,32); else	bdt_deb+=*d(4,32);
		}
		goto endsr;
	}
  if(dat_beg && dat_beg<last_arc && allow_yr && only_open==NO && only_verv==NO) get_jaar=YES;
  bew_key=4;  if(mode_ && stu==3 && get_jaar==NO && (sear_grb==kltcent || sear_grb==levcent)) bew_key=3; // detail bij 4000/4400 

	if(dat_beg){ // indien begindatum, dan saldo zetten
		get_lkgsal(dat_beg); // saldo tellen : stu 1/2 openstaand tot begindatum, stu 3 : begin boekjaar tot begindatum
		if(!is_nul(sal_deb) || !is_nul(sal_cre)){ StkTab[MaxStkTab++]=-1; DatumVorigSaldo=dat_beg-1;} // saldo
		bdt_deb+=sal_deb; bdt_cre+=sal_cre;
	}
	else if(MinBkhDatum){
		if(stu<3 || sys1834){ // klt/lev : openstaande facturen tem MinBkhDatum en dan volledig
			make_otab(tb_voor_min_dt_,0,DIM_OPEN,MinBkhDatum); // records open t.e.m. MinBkhDat
		}
		else if(bew_key!=3){ // GRB : saldo tot MinBkh nemen indien geen detail 4000/4400
		  get_lkgsal(MinBkhDatum+1); // saldo tellen : stu 1/2 openstaand tot begindatum, stu 3 : begin boekjaar tot begindatum
		  if(!is_nul(sal_deb) || !is_nul(sal_cre)){ StkTab[MaxStkTab++]=-1; DatumVorigSaldo=dat_beg-1;} // saldo
			bdt_deb+=sal_deb; bdt_cre+=sal_cre;
		}

		//else if(period_1==0 && get_jaar==NO && bew_key!=3) { // GRB 
  //    fasinit(5); *u(5,2)=searcnr;
  //    if(faskeyi(5,1,0)==0){
		//		sal_deb=*d(5,31); sal_cre=*d(5,32);
		//		if(!is_nul(sal_deb) || !is_nul(sal_cre)) {StkTab[MaxStkTab++]=-1;DatumVorigSaldo=last_arc;} // saldo 1/1
		//	}
		//}
	}
	
  if(get_jaar){
    fasinit(86); *u(86,5)=searcnr;
		FOREVER{
			redo86:;
			ks=faskeyi(86,bew_key,2);
			if(ks || *u(86,5)!=searcnr){*l(86,1)=0;break;}
      if(fldlen(86,19) && ((sub_mask & *l(86,19))==0)) goto redo86;
	    if(dat_beg && *u(86,4)<dat_beg) goto redo86;
      if(dat_end && *u(86,4)>dat_end) goto redo86;
			break;
    }
  }	
	fasinit(4);  stu_bew=4;  
  if(bew_key==3) *l(4,6)=sear_grb;  else *u(4,5)=searcnr;
  for(MaxStkTab;MaxStkTab<DIM_STKTAB;MaxStkTab++){
		if(MaxStkTab && (MaxStkTab%12)==0){
			p_scr++;tbs[p_scr].saldo=bdt_deb-bdt_cre;
		} // schermtotalen bijhouden 
		redoxy:;
    ks=faskeyi(stu_bew,bew_key,2);
    if(fldlen(stu_bew,19) && !ks && ((sub_mask & *l(stu_bew,19))==0)) goto redoxy;
    if(!ks){
			if(dat_beg==0 && *u(stu_bew,4)<=MinBkhDatum){
				if(stu<3 || sys1834){ // bij klt/lev de openstaande tot MinbkhDatum meenemen
				  for(k=0;k<DIM_OPEN;k++) if(*l(4,1)==tb_voor_min_dt_[k]) break;
					if(k>=DIM_OPEN) goto redoxy;
				}
				else goto redoxy; // doen alsof gearchiveerd
			}
      if(dat_beg && *u(stu_bew,4)<dat_beg) goto redoxy;
      if(dat_end && *u(stu_bew,4)>dat_end) goto redoxy;
      if(only_fact && IsFactuur((int16)(*s(stu_bew,2)))==NO) goto redoxy;/* enkel AK en VK */
	  }
    if(get_jaar==NO){
      if(ks) break;
      if(bew_key==3){
				if(*l(stu_bew,6)!=sear_grb) break;
      }
      else {
				if(*u(stu_bew,5)!=searcnr) break;
      }
    }
    else{
      if(ks) zeroL(s(stu_bew,1),fldlen(stu_bew,1));
      else if(bew_key==4 && *u(stu_bew,5)!=searcnr) zeroL(s(stu_bew,1),fldlen(stu_bew,1));
      else if(bew_key==3 && *l(stu_bew,6)!=sear_grb) zeroL(s(stu_bew,1),fldlen(stu_bew,1));
      if(*l(4,1)==0 && *l(86,1)==0) break;
      FOREVER{
				if(*l(4,1)==0) {stu_bew=86;break;}
				if(*l(86,1)==0) {stu_bew=4;break;}
				if(*s(4,8)<*s(86,8)) {stu_bew=4;break;}
				if(*s(86,8)<*s(4,8)) {stu_bew=86;break;}
				if(*s(4,9)<*s(86,9)) {stu_bew=4;break;}
				if(*s(86,9)<*s(4,9)) {stu_bew=86;break;}
				if(*u(4,10)<*u(86,10)) {stu_bew=4;break;}
				stu_bew=86;break;
      }
    }
    if(stu_bew==4){
			StkTab[MaxStkTab]=*l(4,1);
			if(stu<3 || sys1834){
  			for(k=0;k<DIM_OPEN;k++) if(*l(4,1)==open_recs[k]) break;
        if(k<DIM_OPEN) StkTabFlag[MaxStkTab]|=0x01; // openstaand
			}
      if(bew_key==3 && *u(4,5)==searcnr) StkTabFlag[MaxStkTab]|=0x01; // openstaand
		}
		else {
			StkTab[MaxStkTab]=*l(86,1);
			StkTabFlag[MaxStkTab]|=0x10;  // stu 86
		}
		if(*d(stu_bew,32)<-0.009)	bdt_cre+=-*d(stu_bew,32);
		else	bdt_deb+=*d(stu_bew,32);
		
  }
	endsr:;
	p_scr++; if(p_scr<(DIM_STKTAB/12) + 10) tbs[p_scr].saldo=bdt_deb-bdt_cre;
	if(only_fact && MaxStkTab<DIM_OPEN){ // niet als aantal >=10000
	  zeroL((char *)tbs,sizeof tbs);p_scr=0;
	  zeroL(tb_voor_min_dt_,sizeof tb_voor_min_dt_);
	  sal_deb=0;sal_cre=0; bdt_deb=0;bdt_cre=0;
		for(k=0;k<MaxStkTab;k++){
			stu_bew=4; if(StkTabFlag[k]&0x10) stu_bew=86; 
			fasinit(stu_bew);*l(stu_bew,1)=StkTab[k]; fasgeti(stu_bew);
			tb_voor_min_dt_[k]=*u(stu_bew,4);ks=StkTabFlag[k];
			if(k){
				for(j=0;j<k;j++) if(tb_voor_min_dt_[k]<tb_voor_min_dt_[j]) break;
				if(j<k){
					for(n=k-1;n>=j;n--){tb_voor_min_dt_[n+1]=tb_voor_min_dt_[n];StkTab[n+1]=StkTab[n];StkTabFlag[n+1]=StkTabFlag[n];}
					tb_voor_min_dt_[j]=*u(stu_bew,4);StkTab[j]=*l(stu_bew,1);StkTabFlag[j]=ks;
				}
			}
		}
		p_scr=0;
		for(k=0;k<MaxStkTab;k++){
			if(k && (k%12)==0){p_scr++;tbs[p_scr].saldo=bdt_deb-bdt_cre;} // schermtotalen bijhouden 
			stu_bew=4; if(StkTabFlag[k]&0x10) stu_bew=86; 
			fasinit(stu_bew);*l(stu_bew,1)=StkTab[k]; fasgeti(stu_bew);
		  if(*d(stu_bew,32)<-0.009)	bdt_cre+=-*d(stu_bew,32);
		  else	bdt_deb+=*d(stu_bew,32);
		}
		p_scr++; if(p_scr<(DIM_STKTAB/12) + 10) tbs[p_scr].saldo=bdt_deb-bdt_cre;
	}
}

static IsFactuur(journaal_)
int16 journaal_;
{
	int16 k,fl_factuur_=NO;

	for(k=0;k<80;k++) if(j_tab[k].nr==journaal_) break;
  if(k>=80 || j_tab[k].typ<1 || j_tab[k].typ>2) return NO;/* enkel AK en VK */
	return YES;
}


static initload()
{
  int16 k,dum1,dum2,mm;
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;
  allow_yr=NO; if(fldlen(86,1)>0) allow_yr=YES;

  fasunlck(0);

  if(credt_allow) fileopen(1);
  if(debit_allow) fileopen(2);
  for(k=3;k<=5;k++) fileopen(k);
	if(fldlen(7,1)) fileopen(7);
  fileopen(10);
  sysget( 294,4,def_munt);
  sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);
  sysget(1834,2,&sys1834);
  sysget(1842,6,(char *)clean_prev);
  sysget(1858,2,&last_arc);
  if(allow_yr==NO){
    for(k=0;k<3;k++) clean_prev[k]=last_arc;
  }
  sysget(1866,2,&mnd_strt);
  jddate(last_arc+1,&dum1,&mm,&dum2);
  period_1=0;
  if(mm==mnd_strt) period_1=1;
  sysget(1787,1,&sys1787);
  sysget(1918,2,&sear_stt);
	sysget(2300,2,&MinBkhDatum);if(MinBkhDatum<last_arc) {MinBkhDatum=last_arc;sysput(2300,2,&MinBkhDatum);}
  sysget(2698,2,&sys2698);
	sysget(3876,2,&sys3876);
  analyt=fldlen(4,11);

  for(k=0;k<80;k++){
    sysget(10240+k*80,4,(char *)&j_tab[k]);
  }
  j_tab[80].nr=0;j_tab[80].typ=3;
  sub_mask=*l(26,14);
 
  dsp_f_e='E';
  copy("EUR",dfmunt,3);
  dt_vandaag=*u(25,2);
}

static double round(bd_)
double bd_;
{
  double bdr_;
						
  bdr_=valu_cnv("EUR","EUR",bd_,(double)0.01);
  return (double)bdr_;
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

static nextline()
{
  free=prtline();
}

static g_anal_tst()
{
  if(!analyt || ((*s(3,2) &0xF0)>>4)!=9) return NO;
  return YES;
}
 
static long str2get(ps)
char *ps;
{
  long fuval=0;
  flag sign=NO;

  FOREVER{
    if(*ps>='0' && *ps<='9'){
      fuval=fuval*10+*ps-'0';
    }
    else if(*ps=='-') sign=YES;
    else if(*ps!=' ') break;
    ps++;
  }
  if(sign) fuval=-fuval;
  return fuval;
}
 
static prt_tegen()
{
  int16 k,jr_,stu_,fkey_;
  uint16 date_,vl_,tegen_rek=0;
  long rec_;

  if(stu_bew==4){
    rec_=*l(4,1);
    jr_=*s(4,2);
    for(k=0;k<80;k++){
      if(jr_==j_tab[k].nr) break;
    }
    if(j_tab[k].typ<3){
      vl_=*u(4,3);date_=*u(4,4);
      *l(4,1)=0;
      fkey_=1;
      FOREVER{
	if(faskeyi(4,1,fkey_)) break;
	fkey_=2;
	if(jr_!=*s(4,2) || vl_!=*u(4,3)) break;
	if(*u(4,5)<60000 && date_==*u(4,4)){
	  tegen_rek=*u(4,5);
	  break;
	}
      }
      *l(4,1)=rec_;fasgeti(4);
    }
  }
  else{/* in stu 86 */
    tegen_rek=*u(86,6);
  }
  if(tegen_rek){
    if(tegen_rek<30000) stu_=1; else stu_=2;
    fasinit(stu_);*u(stu_,1)=tegen_rek-((stu_-1)*30000);fasgeti(stu_);
    if((stu_==1 && lvcd) || (stu_==2 && klcd)){
      prtfld(stu_,2,-1);
    }
    else prtfld(stu_,1,-1);
    prtblank(1);prtfld(stu_,3,28);
  }
}

static scr_bd(z,bd_)
int16 z;
double *bd_;
{
   zeroL(fm_bd,sizeof fm_bd);
   copy(fm_od7_2,fm_bd,sizeof fm_od7_2);
   if(*bd_<-999999 || *bd_>9999999) copy(fm_od92_,fm_bd,sizeof fm_od92_);
   scrifld(z,fm_bd,bd_);
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
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
  if(DspTotRek==NO) parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}

