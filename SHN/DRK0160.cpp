#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* DRK0160GetD() {return &zzvw;}

extern "C" int16 CheckPw(int16 type,int16 nr,int16 aard_);
extern "C" int CopyMoveFile(char *FromFile,char *ToFile,int DeleteOriginal); // kopieren van een file
extern "C" void CnvJamaChar(char *pString,int16 MaxLen,int16 CnvMode);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" int ShowSavedDocument(int16 MastStuNr, long MastRecord, int16 SoortDocument, uint16 dat_beg, uint16 dat_end) ;
extern "C" int16 Search(int stu_,int mod_);
extern "C" char *VarTextFmt(int len_,int update_);
extern "C" int DirCall_DRK2215_SelectArtikel(void);

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;

static int16 ovlcall();
__declspec(dllimport) unsigned char PrintPaperNr;

extern "C" char DRK0160dat[] = "DRK0160  00:01 13/06/18 (c) Jamadata"; // Uitschrijven artikellijst voor Beedrop


static void Export2Beedrop(void);
static void FillBeedropFlag(void);
static void FillArt2Tb(int16 ptb_);
static double Round(double bd_, double bd_afr_);
static int cmpstr(char *p1, char *p2, int16 len);
static int copy0(char *ps, char *pd, int16 len);
static int date2str(char *str_, uint16 date_, uint16 no_delim_);
static void fileopen(int16 nr_);
static int fmt_get(int16 stu_, int16 elet_);
static uint16 hash(int16 nr_);
static void initload(void);
static void nextline(void);
static int scr_ok(char *ptxt);
static void streepje(int16 fldnr);
static void UpdateParameters(void);


#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_TB          1500
#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

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

static int16 stu=6,sfree;
static int16 lvcd,klcd;

static char fm_os80[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us5[]   = {7,0xC8,5,0,0,0,0};
static char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x91,5,0,0x60,0};
static char fm_ou4[]   = {6,0x91,4,0,0x60,0};
static char fm_ou3[]   = {6,0x91,3,0,0x60,0};
static char fm_uu4[]   = {6,0xD1,4,0,0x60,0};
static char fm_uu3[]   = {6,0xD1,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD1,2,0,0x60,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_uf4_2[] = {6,0xD4,4,2,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_uf3_1[] = {6,0xD4,3,1,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_uf21_[] = {6,0xD4,2,1,0x20,0};
static char fm_of4_2[] = {6,0x94,4,2,0x70,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_ud4_2[] = {6,0xD5,4,2,0x70,0};
static char fm_od6_2[] = {6,0xD5,6,2,0x70,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_obd[]   = {6,0x95,6,2,0x70,0};                             /* od6_2 */
static char fm_ubd[]   = {6,0xD5,6,2,0x70,0};                             /* ud6_2 */
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uANP[]   = {13,0xC8,1,0,1,0,'A','A','N','N','P', 'P',0};
static char fm_uS[]   = {11,0xC8,1,0,1,0,'S','S',' ',' ',0};
static char fm_uAVW[]  = {11,0xC8,1,0,1,0,'A','A','V','W',0};
static char fm_u_ALN[]= {13,0xC8,1,0,0x09,0,'A','A','L','L','N','N',0};
static char fm_usP_G[]= {13,0xC8,1,0,0x09,0,'%','%','P','P','G','G',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
 
static int16 dag_nr[7] = {2,3,4,5,6,0,1};
static char seqo_str[500],sys3896[6],upd_veld[20],kas_munt[4],buf600[600],fmt[40];
static char periodprt[3],filnam[40],oldnm[50],prx2kas,upd_stock,add_ftvk,def_munt[4];
static char vptekst[100];
static long seqo_pos,value,ok_pos,btw_nr,krtok_pos,TbDiversArtikel[10],ArtOnbekend;
static int16 stu6_len,seqo_len,seqo_mode,pos,first_prx,last_prx,len6_155,ft_off;
static uint16 dat_beg,dat_end,sys3772,dt_dag1,inq_kassa,prx_loff,max_kassa,art_div;
static int16 tb_kprx[6],max_kprx,BakPrxNr;
static uint16 inq_lev,inq_art,inq_groep,inq_disp,fkey,klt_div1,def_qfak,kaartnr,MaxAantal;
static int16 prt2pdf;
static flag sys3894,sys3618,sys3978,sys4400,sys4408,sys1790,sys4478;
static flag chk_btoeg=NO,arcd=YES,use_kaart;
static flag sear_stt,sys3876, sgrp_used,slev_used,p_max_grp,sys2727;
static float sys3614,pct1,pct2,winstpct,tot_qlv,def_btw;
static double bd_tab[10],bd_tot[10];
static double AW,VW,winst,tot_aw,tot_vw,qlv;
static float kas_sal;

static char nm_kassa[20][6], firma[256];
static int16 def_taal;

static struct {
  uint16 rec;
  float aantal;
	char stuks;
  char  code[15];
  char  omschr[40];
	char eenh[5];
	float vp[2];
	float vp_lg[2];
  double AW;
  double VW;/* excl. btw */
  uint16 hash;
	char used;
} tb[DIM_TB+1];

// ----- XLS-FUNC 
extern int16 ilength; // XLS
static int XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol,XlsMaxKol,XlsMaxRij;
static int16 *pi,prt2xls; // XLS
static int StylTotaal, StylDate, StylKlasse, StylNormal, StylTitel, Styl2Use;

static int fas_ret(char *s);
static int XlsCreate(char *name);
static int XlsClose(int16 ref,int16 Action);
static int XlsSaveAsPdf(int16 ref);
static int XlsWrite(int16 ref,int16 rownr,int16 colnr,int16 type,char *val, int16 StyleIx);
static int XlsSelectWorkSheet(int16 ref,int16 WksNr,char *WksName); // WknNr = 1, 2, ... WksCount
static int XlsChart(int16 ref,int16 rowcnt,int16 colcnt,int16 chartType,char *title);
static int XlsGraf(int16 ref,int16 colnr,int16 chartType,long Color);
static int XlsRowSize(int16 ref,int16 rownr,int16 size);
static int XlsColumnSize(int16 ref,int16 rownr,int16 size);
static int XlsStyle(int16 ref, char *NumFormat,int16 Size,long Color,int16 BoldFlag,int16 ItalicFlag,int16 UnderlineFlag,int16 HorAlignment,int16 VerAlignment,long BackCol,int16 Pattern,int16 Kader,long KaderCol,int16 Lock,int16 Hide);
static int16 WriteVar2Xls(int16 rij_,int16 kol_,char *fmt_,char *pvar_,int16 StylIx);
static int16 WriteFld2Xls(int16 rij_,int16 kol_,int16 stu_,int16 fld_,int16 StylIx);

static int XlsOpen(char *name); // XLS open for read
static int XlsGetMaxKol(int16 ref);
static int XlsGetMaxRij(int16 ref);
static int XlsReadString(int16 ref,int16 rownr,int16 colnr,char *ret_string, int16 MaxLen);
static int XlsReadInt(int16 ref,int16 rownr,int16 colnr);
static double XlsReadDouble(int16 ref,int16 rownr,int16 colnr);
static short unsigned XlsReadDate(int16 ref,int16 rownr,int16 colnr);


#include "Std\XlsFunc.CPP"
// ---------------------------------------


extern "C" void DRK0160cod(int16 parmval)
{
  int16 curs=1,key,z;
  char choice;

  initload();
  FOREVER{
		redo:;
    scrnum=0;scrget(3,3);z=1;fasunlck(0);
		scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0160A");
		scraddpicto(1,0,76,22,4,2,59,0,4,"Parameters");
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0681);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
		if(key==5001){UpdateParameters();goto redo;}
    if(key==101) break;
		
    if(key==111) ovlexit(-1);
		fasunlck(-1);
    switch(choice){
      case '1': Export2Beedrop(); break;
      default : errnum=34; break;
    }
  }
  endsr:;
  ovlexit(-1);
}

static void Export2Beedrop(void)
{
  int16 curs=1,k,n,key,fkey,z,mode,j,start_=0,q_per_lijn_,d_lin_scr_=19,curspos_,artikelgezocht_,z_base_,pmaxtb_,ok_,p_max;
	uint16 used,a,pos_,prx_op_dt,dt_p_upd,first_,last_,nr_,rec_;
	float vp_kas[10],p_lg_bak,p_lg_stk,q_lg_;
  flag sr_nm;
	double bd_,afrond_;
  char *pdum,dumm_[10],str_[50],k_lg_b_[10],k_lg_s_[10];
	long qbak_,qstks_;
  char sortmeth='A',only_used='J',skip_lg='J',nm_winkel[40];

	pdum=&dumm_[0];

  seldata.selp_use=NO;
//  if(ovlcall(2215,2)) goto endsr;
	scrget(1,7);scrupd(-3,0);
	for(k=0;k<DIM_TB;k++) zeros((char *)&tb[k].rec,sizeof tb[0]);
  used=*u(6,1);p_max=0; fasinit(6);
	FOREVER{
		nexta:;
		if(faskeyi(6,2,2)) break;
 //   if(DirCall_DRK2215_SelectArtikel()==NO) goto nexta;
		if(*s(6,75)=='J') FillArt2Tb(p_max++);
		if(p_max>=DIM_TB) break;
	}


	q_per_lijn_=5;start_=0;
  curs=1;
  FOREVER{
    redoscr:
    scrnum=0;scrget(3,5);z=1;
		z_base_=z;
    for(j=start_;j<(start_+d_lin_scr_);j++){
			j++;scrifld(z++,fm_ou4,&j);j--;
      fieldspc(6,2,&pdum,fmt); scrifld(z++,fmt,tb[j].code);
      fieldspc(6,3,&pdum,fmt); scrifld(z++,fmt,tb[j].omschr); scraddpicto(20+j-start_,z-1,1,0,2,1,540,0,0,"NIET uitschrijven"); 
      scrifld(z++,fm_uf4_2,&tb[j].vp[0]);
		  scrifld(z++,fm_uf4_2,&tb[j].vp[1]);
	  }
    key=scrupd(curs,0x03FF);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101){
			for(k=0;k<DIM_TB;k++) if(tb[k].rec) break;
			if(k<DIM_TB){
				if(DisplayWarning("Wenst u echt te stoppen?", 61,1)==YES) goto endsr;
			}
			else goto endsr;
		}
    if(key>=5020 && key<5020+d_lin_scr_){
			j=start_+key-5020;
			fasinit(6);*u(6,1)=tb[j].rec; fasgeti(6);
			*s(6,75)='N'; fasupd(6);
      for(k=j;k<DIM_TB-1;k++){
				bcopy((char *)&tb[k+1].rec,(char *)&tb[k].rec,sizeof tb[0]);
      }
      zeros((char *)&tb[DIM_TB-1].rec,sizeof tb[0]);
			if(p_max>j) p_max--; 
			if(p_max<0) p_max=0;
			curs=curspos_; goto redoscr;
		}
    if(key==105 && curspos_>=z_base_){
      j=(curspos_-1)/q_per_lijn_;j+=start_;
      for(k=DIM_TB-2;k>=j;k--){
				bcopy((char *)&tb[k].rec,(char *)&tb[k+1].rec,sizeof tb[0]);
      }
      zeros((char *)&tb[j].rec,sizeof tb[0]);
			curs=curspos_; 
			p_max++; if(p_max>DIM_TB) p_max=DIM_TB; goto redoscr;
    }
   // if(key==104 && curspos_>=z_base_){
   //   j=(curspos_-1)/q_per_lijn_;j+=start_;
   //   for(k=j;k<DIM_TB-1;k++){
			//	bcopy((char *)&tb[k+1].rec,(char *)&tb[k].rec,sizeof tb[0]);
   //   }
   //   zeros((char *)&tb[DIM_TB-1].rec,sizeof tb[0]);
			//if(p_max>j) p_max--; 
			//if(p_max<0) p_max=0;
			//curs=curspos_; goto redoscr;
   // }
		artikelgezocht_=NO;
    for(k=start_;k<(start_+d_lin_scr_);k++){
      if((tb[k].code[0] || tb[k].omschr[0]) && tb[k].hash!=hash(k)){
				fasinit(6);
				sr_nm=NO;
				if(fldlen(6,2) && tb[k].code[0]) {*s(6,3)='.';bcopy(tb[k].code,s(6,3)+1,fldlen(6,2));}
				else {bcopy(tb[k].omschr,s(6,3),fldlen(6,3));sr_nm=YES;}
				if(Search(6,0)){curs=3+(k-start_)*q_per_lijn_;goto redoscr;}
				FillArt2Tb(k);
				*s(6,75)='J'; fasupd(6);
				artikelgezocht_=YES;
      }
			else if(tb[k].omschr[0]=='\0') zeros((char *)&tb[k].rec,sizeof tb[0]);
    }


		if(key==108 && artikelgezocht_==NO) break;
    if(key==102) {start_-=d_lin_scr_; }
    if(key==103) start_+=d_lin_scr_;
    if(start_>(p_max-d_lin_scr_)) start_=p_max-d_lin_scr_;
		if(start_<0) start_=0;
    j=0;
    for(k=0;k<d_lin_scr_;k++){if(tb[k+start_].code[0]=='\0') {j=k;break;}}
    if(k<d_lin_scr_) curs=3+k*q_per_lijn_; else curs=z_base_;
  }
	scrget(1,7);scrupd(-3,0);
  zeros(str_,sizeof str_);
  k=copy0("Artikellijst ",str_,13);k+=copy0(s(25,1),&str_[k],20);
  str_[k++]=' ';k+=date2str(&str_[k],*us(25,2),1);
  k=copy0(".XLSX",&str_[k],5);
  XlsRef=XlsCreate(str_);
  if(XlsRef<=0) {errnum=1;goto endsr;}
	XlsSelectWorkSheet(XlsRef,1,"Artikellijst");  // sheet verkopen
	XlsColumnSize(XlsRef,2,30);XlsColumnSize(XlsRef,3,25);
	StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
	StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
	StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
	StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
	StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
	XlsRij=1;XlsKol=1;
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Code",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",StylTitel);
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Groep",StylTitel);
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Eenheid",StylTitel);
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Prijs",StylTitel);
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Leeggoed",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Prijs/stuk",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Leeggoed/Stuk",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EAN bak",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"EAN stuk",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal/bak",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Inhoud",StylTitel);
	XlsRij++;
	for(k=0;k<p_max;k++){
		if(tb[k].omschr[0]){
			XlsKol=1;
			fasinit(6);*us(6,1)=tb[k].rec;fasgeti(6);
			fasinit(52);*us(52,1)=*us(6,9);fasgeti(52); 
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,tb[k].code,0);
#if FLAGTOL
			if(*s(6,5)) WriteFld2Xls(XlsRij,XlsKol++,6,5,0);
			else 
#endif
			XlsWrite(XlsRef,XlsRij,XlsKol++,0,tb[k].omschr,0);
			WriteFld2Xls(XlsRij,XlsKol++,52,14,0);
			WriteFld2Xls(XlsRij,XlsKol++,6,10,0);
			bd_=Round((double)tb[k].vp[0],(double)(0.01));	WriteVar2Xls(XlsRij,XlsKol++,fm_od6_2,(char *)&bd_,0);
			bd_=Round((double)tb[k].vp_lg[0],(double)(0.01));WriteVar2Xls(XlsRij,XlsKol++,fm_od6_2,(char *)&bd_,0);
			bd_=Round((double)tb[k].vp[1],(double)(0.01));	WriteVar2Xls(XlsRij,XlsKol++,fm_od6_2,(char *)&bd_,0);
			bd_=Round((double)tb[k].vp_lg[1],(double)(0.01));	WriteVar2Xls(XlsRij,XlsKol++,fm_od6_2,(char *)&bd_,0);
			WriteFld2Xls(XlsRij,XlsKol++,6,70,0);
			WriteFld2Xls(XlsRij,XlsKol++,6,71,0);
			WriteFld2Xls(XlsRij,XlsKol++,6,31,0);
			WriteFld2Xls(XlsRij,XlsKol++,6,37,0);
			XlsRij++;
		}
	}
	XlsClose(XlsRef,1);
  endsr:;
}


static void FillArt2Tb(int16 ptb_)
{

	uint16 pos_,prx_op_dt,dt_p_upd,rec_;
	float p_lg_bak,p_lg_stk,q_lg_;
  char k_lg_b_[10],k_lg_s_[10];
	long qbak_,qstks_;
	double afrond_;
  
	tb[ptb_].rec=*us(6,1);
  bcopy(s(6,2),tb[ptb_].code,fldlen(6,2));
	bcopy(s(6,3),tb[ptb_].omschr,fldlen(6,3));
	bcopy(s(6,10),tb[ptb_].eenh,fldlen(6,10));
	pos_=0;prx_op_dt=NO;dt_p_upd=*us(25,2);
	if(fldlen(6,105) && *us(6,105) && *us(6,105)<=dt_p_upd){pos_=94;prx_op_dt=YES;}
	tb[ptb_].vp[0]=*f(6,21+BakPrxNr+pos_); 
	if(*f(6,31)<=1) tb[ptb_].vp[1]=*f(6,21+BakPrxNr+pos_);
	else {
#if FLAGKLV
    tb[ptb_].vp[1]=*f(6,tb_kprx[max_kprx-1]+pos_); // kassa stukprijs nemen 
#else
		tb[ptb_].vp[1]=*f(6,21+BakPrxNr+pos_)/ *f(6,31);
#endif
		afrond_=0.05; if(tb[ptb_].vp[1]<1.) afrond_=0.01; // indien minder dan 1 euro, dan afronden op 1 cent
		tb[ptb_].vp[1]=Round((double)(tb[ptb_].vp[1]),afrond_); 
	}
	q_lg_=*f(6,42);
	bcopy(s(6,41),k_lg_b_,fldlen(6,41));
	bcopy(s(6,44),k_lg_s_,fldlen(6,44));
	rec_=*u(6,1);
	if(k_lg_b_[0]){
		fasinit(6);bcopy(k_lg_b_,s(6,2),fldlen(6,2));faskeyi(6,1,0);
		tb[ptb_].vp_lg[0]=*f(6,21+BakPrxNr); 
	}
	if(k_lg_s_[0]){
		fasinit(6);bcopy(k_lg_s_,s(6,2),fldlen(6,2));faskeyi(6,1,0);
		tb[ptb_].vp_lg[1]=*f(6,21+BakPrxNr); 
	}
	fasinit(6);*us(6,1)=rec_;fasgetu(6);
	tb[ptb_].used=*s(6,75);
	tb[ptb_].hash=hash(ptb_);
}


 static void FillBeedropFlag(void)
 {
  int16 curs=1,k,n,key,fkey,z,mode,j,start_=0,q_per_lijn_,d_lin_scr_=19,curspos_,artikelgezocht_,z_base_,pmaxtb_,ok_,p_max;
	uint16 used,a,pos_,prx_op_dt,dt_p_upd,first_,last_,nr_,rec_;
	float vp_kas[10],p_lg_bak,p_lg_stk,q_lg_;
  flag sr_nm;
	double bd_,afrond_;
  char *pdum,dumm_[10],str_[50],k_lg_b_[10],k_lg_s_[10];
	long qbak_,qstks_;
  char sortmeth='V',only_used='J',skip_lg='J',nm_winkel[40];

	pdum=&dumm_[0]; MaxAantal=250;
  if(add_ftvk=='\0') add_ftvk='J';
	if(dat_beg==0) dat_beg=*us(25,2)-365;if(dat_end==0) dat_end=*us(25,2);
  inq_kassa=0;if(max_kassa==1) inq_kassa=1;
  FOREVER{
    redo376:;
    scrget(3,2);z=1;// scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_uAVW,&sortmeth);
    scrifld(z++,fm_udat,&dat_beg);scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_uu2,&inq_kassa);
    if(ft_off>0) scrifld(z++,fm_uJN,&add_ftvk); else streepje(z++);
		scrifld(z++,fm_uu4,&MaxAantal);
    key=scrupd(curs,0x481);curs=3;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    if(key==111) ovlexit(-1);
    if(key==101) goto endsr;
    if(dat_end==0 || dat_end<dat_beg){curs=4;errnum=38;goto redo376;}
    if(inq_kassa && fldlen(91,11+(inq_kassa-1)*5)==0){
      curs=6;errnum=34;goto redo376;
    }
    if(key==108) break;
  }
	if(MaxAantal>DIM_TB) MaxAantal=DIM_TB;
  seldata.selp_use=NO;
  if(ovlcall(2215,2)) goto endsr;
	scrget(1,7);scrupd(-3,0);
	for(k=0;k<DIM_TB;k++) zeros((char *)&tb[k].rec,sizeof tb[0]);
  fasinfo(6,1);
  used=*u(6,1);p_max=0;
  for(a=1;a<=used;a++){
    *u(6,1)=a;
    if(fasgetu(6)==0){
      if(skip_lg=='J' && *us(6,9)==99) continue;
      if(DirCall_DRK2215_SelectArtikel()==NO) continue;
      fasinit(91);*u(91,2)=*u(6,1);*u(91,3)=dat_beg;mode=1;AW=0;VW=0;qlv=0;
      FOREVER{
				next_bew:;
				if(faskeyi(91,1,mode)) break;mode=2;
				if(*u(6,1)!=*u(91,2)) break;
				if(dat_beg && *u(91,3)< dat_beg) goto next_bew;
				if(dat_end && *u(91,3)>dat_end) break;

				if(inq_kassa){
					qlv+=*f(91,11+(inq_kassa-1)*5);
					AW+=*f(91,12+(inq_kassa-1)*5);
					VW+=*f(91,13+(inq_kassa-1)*5)/(1.+*f(6,28)/100.);
					if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
						qlv+=*f(91,11+(inq_kassa-1+ft_off)*5);
						AW+=*f(91,12+(inq_kassa-1+ft_off)*5);
						VW+=*f(91,13+(inq_kassa-1+ft_off)*5)/(1.+*f(6,28)/100.);
					}
				}
				else{
					for(k=0;k<max_kassa;k++){
						if(fldlen(91,11+k*5)){
							qlv+=*f(91,11+k*5);
							AW+=*f(91,12+k*5);
							VW+=*f(91,13+k*5)/(1.+*f(6,28)/100.);
						}
						if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
							qlv+=*f(91,11+(k+ft_off)*5);
							AW+=*f(91,12+(k+ft_off)*5);
							VW+=*f(91,13+(k+ft_off)*5)/(1.+*f(6,28)/100.);
						}
					}
				}
      }
      if(only_used!='J' || qlv){
				winst=VW-AW; ok_=NO;
				for(k=0;k<p_max;k++){
					switch(sortmeth){/* sorteren volgens beste */
						case 'A' : if(qlv>=tb[k].aantal) ok_=YES; break;
						case 'V' : if(VW>=tb[k].VW) ok_=YES; break;
						case 'W' : if(winst>=(tb[k].VW-tb[k].AW)) ok_=YES; break;
						default  : break;
					}

					if(ok_){
						for(j=p_max-1;j>=k;j--){
							bcopy((char *)&tb[j],(char *)&tb[j+1],sizeof tb[0]);
						}
						FillArt2Tb(k);
						tb[k].AW=AW;tb[k].VW=VW;tb[k].aantal=qlv;
						p_max++; if(p_max>=MaxAantal) p_max--;
						break;
					}
				}
				if(ok_==NO && k<MaxAantal){
					FillArt2Tb(k);
					tb[k].AW=AW;tb[k].VW=VW;tb[k].aantal=qlv;
					p_max++; if(p_max>=MaxAantal) p_max=MaxAantal;
				}
      }
    }
  }
	if(p_max>MaxAantal) p_max=MaxAantal;
	for(k=MaxAantal;k<DIM_TB;k++) zeros((char *)&tb[k].rec,sizeof tb[0]);
	q_per_lijn_=5;start_=0;
  curs=1;
  FOREVER{
    redoscr:
    scrnum=0;scrget(3,1);z=1;
		z_base_=z;
    for(j=start_;j<(start_+d_lin_scr_);j++){
			j++;scrifld(z++,fm_ou4,&j);j--;
			fieldspc(6,2,&pdum,fmt); scrifld(z++,fmt,tb[j].code); if(tb[j].used=='J') scrchat(z-1,0x09); else scrchat(z-1,0xFF);
      fieldspc(6,3,&pdum,fmt); scrifld(z++,fmt,tb[j].omschr); 
			if(tb[j].used=='J'){
				scrchat(z-1,0x09); scraddpicto(20+j-start_,z-1,1,0,2,1,540,0,0,"NIET uitschrijven"); 
		  }
			else scrchat(z-1,0xFF);
      scrifld(z++,fm_of4_2,&tb[j].vp[0]);
		  scrifld(z++,fm_of4_2,&tb[j].vp[1]);
	  }
    key=scrupd(curs,0x03FF);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101){
			for(k=0;k<MaxAantal;k++) if(tb[k].rec) break;
			if(k<MaxAantal){
				if(DisplayWarning("Wenst u echt te stoppen?", 61,1)==YES) goto endsr;
			}
			else goto endsr;
		}
    if(key>=5020 && key<5020+d_lin_scr_){
			j=start_+key-5020;
			fasinit(6);*u(6,1)=tb[j].rec; fasgeti(6);
			*s(6,75)='N'; fasupd(6);
      for(k=j;k<DIM_TB-1;k++){
				bcopy((char *)&tb[k+1].rec,(char *)&tb[k].rec,sizeof tb[0]);
      }
      zeros((char *)&tb[DIM_TB-1].rec,sizeof tb[0]);
			if(p_max>j) p_max--; 
			if(p_max<0) p_max=0;
			curs=curspos_; goto redoscr;
		}
		if(key==105 && curspos_>=z_base_){
      j=(curspos_-1)/q_per_lijn_;j+=start_;
      for(k=DIM_TB-2;k>=j;k--){
				bcopy((char *)&tb[k].rec,(char *)&tb[k+1].rec,sizeof tb[0]);
      }
      zeros((char *)&tb[j].rec,sizeof tb[0]);
			curs=curspos_; 
			p_max++; if(p_max>MaxAantal) p_max=MaxAantal; goto redoscr;
    }
    if(key==104 && curspos_>=z_base_){
      j=(curspos_-1)/q_per_lijn_;j+=start_;
      for(k=j;k<DIM_TB-1;k++){
				bcopy((char *)&tb[k+1].rec,(char *)&tb[k].rec,sizeof tb[0]);
      }
      zeros((char *)&tb[DIM_TB-1].rec,sizeof tb[0]);
			if(p_max>j) p_max--; 
			if(p_max<0) p_max=0;
			curs=curspos_; goto redoscr;
    }
		artikelgezocht_=NO;
    for(k=start_;k<(start_+d_lin_scr_);k++){
      if((tb[k].code[0] || tb[k].omschr[0]) && tb[k].hash!=hash(k)){
				fasinit(6);
				sr_nm=NO;
				if(fldlen(6,2) && tb[k].code[0]) {*s(6,3)='.';bcopy(tb[k].code,s(6,3)+1,fldlen(6,2));}
				else {bcopy(tb[k].omschr,s(6,3),fldlen(6,3));sr_nm=YES;}
				if(Search(6,0)){curs=3+(k-start_)*q_per_lijn_;goto redoscr;}
				FillArt2Tb(k);
				artikelgezocht_=YES;
      }
			else if(tb[k].omschr[0]=='\0') zeros((char *)&tb[k].rec,sizeof tb[0]);
    }


		if(key==108 && artikelgezocht_==NO) break;
    if(key==102) {start_-=d_lin_scr_; }
    if(key==103) start_+=d_lin_scr_;
    if(start_>(p_max-d_lin_scr_)) start_=p_max-d_lin_scr_;
		if(start_<0) start_=0;
    j=0;
    for(k=0;k<d_lin_scr_;k++){if(tb[k+start_].code[0]=='\0') {j=k;break;}}
    if(k<d_lin_scr_) curs=3+k*q_per_lijn_; else curs=z_base_;
  }
	if(p_max==0 || DisplayWarning("Wenst u deze artikels te activeren voor Beedrop?", 61,1)==NO) goto endsr;
	for(k=0;k<p_max;k++){
		if(tb[k].rec){
			fasinit(6);*u(6,1)=tb[k].rec; fasgeti(6); *s(6,75)='J'; fasupd(6);
		}
	}
  endsr:;
}

static void UpdateParameters(void)
{
  int curs,z,key;
	char nmprx_[10],prxtype_;
 
	sysget(2729,1,&prxtype_); BakPrxNr=prxtype_-'0'; if(BakPrxNr<0 || BakPrxNr>5) BakPrxNr=4;
	zero(nmprx_,sizeof nmprx_);
	if(prxtype_>='0' && prxtype_<='5') copy(&vptekst[(prxtype_-'0')*10],nmprx_,6);

	curs=1;
  FOREVER {
		redo:; 
    scrnum=0;scrget(3,4);z=1;
	  scrifld(-z,fm_u_05,&prxtype_);z++;
		scrifld(z++,fm_os6,&nmprx_);
    key=scrupd(curs,0x2A0);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106) break;
		zero(nmprx_,sizeof nmprx_);
		if(prxtype_>='0' && prxtype_<='5') copy(&vptekst[(prxtype_-'0')*10],nmprx_,6);
		else {errnum=38;curs=1;goto redo;}
		if(key==18 && fldcurs<5){curs=fldcurs+1;goto redo;}
		if(key==110){FillBeedropFlag(); goto redo;}
    if(key==108){
			sysput(2729,1,&prxtype_); break;
		}
	}
	sysget(2729,1,&prxtype_); BakPrxNr=prxtype_-'0'; if(BakPrxNr<0 || BakPrxNr>5) BakPrxNr=4;
endsr:;
}



static uint16 hash(int16 nr_)
{
  char *ps;
  int16 len_;
  uint16 fuval=0;
					
  len_=sizeof tb[nr_].code + sizeof tb[nr_].omschr;ps=tb[nr_].code;
  while(len_--){
    fuval=fuval*3+*(ps++);
  }
  return fuval;
}


static int date2str(char *str_, uint16 date_, uint16 no_delim_)
{
  int16 dd,mm,jj,len_=0;
 
  if(date_==0) goto endsr;
  jddate(date_,&jj,&mm,&dd);
  stcli_d(&str_[len_],(long)dd,2,0);len_+=2;if(!no_delim_) str_[len_++]='/';
  stcli_d(&str_[len_],(long)mm,2,0);len_+=2;if(!no_delim_) str_[len_++]='/';
  stcli_d(&str_[len_],(long)jj,4,0);len_+=4;
  endsr:;
  return len_;
}


static int copy0(char *ps, char *pd, int16 len)
{
  int16 k;
 
  for(k=0;k<len;k++) if(*(ps+k)=='\0') break;
  bcopy(ps,pd,k);
  return k;
}

static int cmpstr(char *p1, char *p2, int16 len)
{
  while(len--){
    if(*p1++!=*p2++)return 1;
  }
  return 0;
}


static void nextline(void)
{
  sfree=prtline();
}


static double Round(double bd_, double bd_afr_)
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


static void streepje(int16 fldnr)
{
  scrifld(fldnr,fm_os1,"-");
}
 

static void initload(void)
{
  int16 g,j,k,nr_;
	char str_[10];

  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);
  if(fldlen(66,1)) fileopen(12);
  if(fldlen(92,1)) fileopen(11);
  if(fldlen(60,1)) fileopen(14);
  if(fldlen(16,1)) fileopen(13);

			
  sysget(  34,256,firma);
  sysget(294,4,def_munt);
  sysget(1790,2,&sys1790);
  sysget(1918,2,&sear_stt);
  sysget(2216,2,&klt_div1); if(klt_div1==0) klt_div1=1;
  sysget(2222,2,&def_qfak);
  sysget(2727,2,&sys2727);
	sysget(2729,1,str_); BakPrxNr=str_[0]-'0'; if(BakPrxNr<0 || BakPrxNr>5) BakPrxNr=4;
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3772,2,&sys3772);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,&sys3896[0]);
  for(k=0;k<6;k++){
    if(sys3896[k]){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=5 && fldlen(6,21+nr_)){
		   tb_kprx[max_kprx++]=nr_+21;
      }
    }
  }
  sysget(3974,2,&ft_off);
  sysget(4338,3,kas_munt);
  sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4400,2,&sys4400);
  sysget(4406,2,&art_div);
  sysget(4408,2,&sys4408);
  sysget(4478,2,&sys4478);
	sysget(4610,60,vptekst);
  sysget(4740,40,&vptekst[60]);

  if(ft_off && fldlen(91,11+(ft_off*5))==0) ft_off=0;
	j=0;
  for(max_kassa=0;max_kassa<10;max_kassa++){
    if(fldlen(91,11+(max_kassa*5))==0) break;
    if(fldlen(91,11+((max_kassa+ft_off)*5))==0) break;
		if(nm_kassa[max_kassa][0]) j++;
  }
	if(ft_off && max_kassa>ft_off) max_kassa=ft_off; // veiligheid voor ft_offset
	if(j<=1) max_kassa=1; // meer velden, maar geen naam ingevuld
  sysget(3978,2,&sys3978);/* geen artikelfiche updaten */
  len6_155=fldlen(6,155);
  use_kaart=NO; if(fldlen(92,30) && ovltest(294)) use_kaart=YES;

  if(fldlen(6,130) && fldlen(25,8) && *us(25,8)) prx_loff=*us(25,8);
  else prx_loff=0;
  if(fldlen(60,1) && (sys3772 & 0x10)) fileopen(14);

  sysget(3678,2,&def_taal);
  zeros(&seldata.data_begin,sizeof seldata); seldata.dt_s_beg=*u(25,2)-730;
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
 

static int scr_ok(char *ptxt)
{
  int16 key;

  scrget(1,169);
  scrifld(12,fm_os80,ptxt);
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  return NO;
}

 

