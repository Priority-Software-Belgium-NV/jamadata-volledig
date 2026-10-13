/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0267GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0267dat
#define ovlcod DRK0267cod
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

char ovldat[] = "drk0267  00:01 25/11/10 (c) Jamadata"; // stock/voorraadlijsten 

// FLAGDWP en FLAGLVB en FLAGOLH : geen stuks exporteren naar XLS
// FLAGGRS : geen code leverancier op bestellijst
// FLAGEPD : korting EUR na % rekenen, dus wordt bij HLkorting geteld
// FLAGVDW : korting EUR na % rekenen, dus wordt bij HLkorting geteld

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define C1              256E0
#define C2              65536E0
#define MAXFLD          100
#define flag            uint16
#define VOLL            0
#define STAT            2
#define PRIX            4
#define ETIK            5
#define KPRX            6
#define KBESTLST        7
#define DIMBTW          8
#define DIM_TBE         500
#define D_LIN_SCR       18

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF


static char *pname[] = {"Artikellijst","","Statistieklijst",
		 "","Prijslijst","",
		 "Prijslijst kassa","Bestellijst klant"};


extern char *s();
extern int16 *i();
extern uint16 *u(),datejd();
static uint16 hash();
extern long *l();
extern long val();
extern float *f();
static float rnd_vprx(),get_prx();
static double Round();
extern double *d();
extern double valu_cnv();

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

static float GetHisBew(arec_,dt_beg_,dt_end_,loc_nr_);

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us75[]  = {7,0xC8,75,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_us8[]   = {7,0xC8,8,0,0,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x20,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x20,0};
static char fm_uu1_[]  = {6,0xD0,1,0,0x00,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_od7_2[] = {6,0x95,7,2,0x30,0};
static char fm_od6_2[] = {6,0x95,6,2,0x30,0};
static char fm_of7_2[] = {6,0x94,7,2,0x30,0};
static char fm_of6_2[] = {6,0x94,6,2,0x30,0};
static char fm_of5_3[] = {6,0x94,5,3,0x30,0};
static char fm_of62_[] = {6,0x94,6,2,0x20,0};
static char fm_of62[] = {6,0x94,6,2,0x60,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf6_3[] = {6,0xD4,6,3,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uONA[] = {13,0xC8,1,0,1,0,'A','A','N','N','O','O',0};
static char fm_uIE[]   = {11,0xC8,1,0,1,0,'I','I','E','E',0};
static char fm_ALNGIP[]= {19,0xC8,1,0,0x09,0,'A','A','I','I','G','G','L','L','N','N','P','P',0};
static char fm_u_FSV[] = {13,0xC8,1,0,0x09,0,'F','F','S','S','V','V',0};
static char fm_u_SAM[] = {13,0xC8,1,0,0x09,0,'A','A','M','M','S','S',0};
static char fm_uKM_[] = {13,0xC8,1,0,1,0,'K','K','M','M',' ',' ',0};
static char fm_u_05[] = {9,0xC8,1,0,1,0,'0','5',0};
 
extern int16 ilength;
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi;
static char *maand_str[12]={"JAN","FEB","MRT","APR","MEI","JUN","JUL","AUG","SEP","OKT","NOV","DEC"};
static int16 free,sys3596,sys3724,fld_ap,stu=6,mode,taal_nr,lgg_exist,prt2xls;
static int16 prx_nr,zz_prx,max_loc;
static int16 def_taal,prt2pdf;
static int16 tot_veld[10] = {33,51,53,54,55,56,57,58,59,60};/* te totaliseren velden */
static int16 form_dat[8],pr_mode,prtnr,wpct_beg, wpct_end,dt_his_beg;
static uint16 dt_inv,cnt,sys3760,q_prx2prt;
static uint16 drv_lev,drv_grp,lg_fles,dt_p_upd,inq_loc;
static char fmt[40],vptekst[100],oldnm[50],def_munt[4],fld_attr[40];
static char bew_only,ak_vk_0[4],type_prx[6],std_txt[4][80],add_bstk,sel_beweg,skip_blocked;
static char tot_buf[200],apprx='N',prt_leeg,lg_splits,prt_acc,prx_str[6][6];
static char prt_nprx='N',prt_kkrt='N',krt_str[10],prt_vpr='N',p_np_bld='J';
static char nm_fil[6],nm_loc[10][6],stuksprx[10],prt_waarde,prt_wpct='N';
static char p_qfles[3][6],best_hdr;
static float p_qbak[3],sys3614,sys2830[10];
static float vp_exc,vp_inc;
static double stockw,stockgt,stockwt, StockwPerBtw[10];
/* float bd_leeg, leegwt,leeggt,bd_goed,goedgt,goedwt,ind_prx; */
static float ind_prx;
static double leegwt,leeggt,goedgt,goedwt,bd_leeg, bd_goed;
static float vp_kas[6],p_lg_bak,p_lg_stk,w_bedrag,w_pct,vp_norm,vp_inorm;
static float btw_pct[DIMBTW],def_btw;
static double bd_afrond;
static flag chk_btoeg=NO,klcd,lvcd,arcd=NO;
static flag sear_stt,sys3618,sys3876,sys1790,sys3894,sys3622,mult_prx,sys4731,sys3586,sys2696;
static flag kont_exist,prx_op_dt,via_ind_inp;
static char grp_used[101];

/* de seqo-variabelen */
static char *p_data;
static long *pl_80_1;
									
static char seqo_str[1000];
static char filnam[40];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;

static char sys3768,sys4521,str4498[23],sys3896[6];

static uint16 *pu_6_1,*pu_2_1;

static struct{
  uint16 recnr;
  char code[10];
  char omschr[31];
  float vp_prx;
  uint16 hash;
} tbe[DIM_TBE];

static struct{
  float qlv[3];
  double bd[2];
  char magaz[10];
	float min_stock;
	float max_stock;
} stl[3];/* art = 0, grp=1, tot=2 */

static struct{
	float q_bak;
	float q_stuk;
	float pr_bak;
	float pr_stuk;
	float lg_bak;
	float lg_stuk;
} InvXlsLijn;

ovlcod(parmval)
int16 parmval;
{
  initload();
	if(parmval==1){invent();ovlexit(-1);} // vanuit ovl0220
	if(parmval==2){stocklst(NO);ovlexit(-1);} // vanuit ovl0220
  menu_stock();
  ovlexit(-1);
}

static menu_stock()
{
  int16 curs=1,z,key;
  char choice;

  mode=VOLL;
  FOREVER{
    scrget(2,233);z=1;fasunlck(0);
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
		if(key==101 || key==111) break;
		fasunlck(-1);
    switch(choice){
      case '1': stocklst(YES); break;
      case '2': if(fldlen(6,63)) invent(); else errnum=12; break;
      case '3': stocklst(NO);break;
      case '4': bestellst();break;
      case '5': stock2txt();break;
      default : errnum=34; break;
    }
  }
}
 
static next_drv(fkey,mode_)
int16 fkey,mode_;
{
  if(fkey==90){
    fasinit(1);*u(1,1)=drv_lev; if(drv_lev) fasgeti(1);
    if(faskeyi(1,2,mode_)) return YES;
    drv_lev=*u(1,1);
  }
  else {
    if(mode_==2){
      drv_grp++;
      for(drv_grp;drv_grp<100;drv_grp++) if(grp_used[drv_grp]) break;
    }
    if(drv_grp>99) return YES;
    fasinit(52);*u(52,1)=drv_grp; if(fasgeti(52)) return YES;
    drv_grp=*u(52,1);
  }
  return NO;
}
 
static uint16 hash(pos_)
int16 pos_;
{
  char *ps;
  int16 k;
  uint16 fuval=0;
						
  k= sizeof tbe[0].code + sizeof tbe[0].omschr;
  ps=tbe[pos_].code;
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
}

static get_art()
{
  int16 curs,j,key,k,start_=0,z,curspos_;
  flag sr_nm;
  char *pdum,dumm_[10];
  pdum=&dumm_[0];


  if(seldata.inq_klt) prx_nr=*s(2,26)-'0';
  else prx_nr=type_prx[0]-'0';
  if(prx_nr<0 || prx_nr>9) prx_nr=0;
  curs=1;
  FOREVER{
    redo:
    scrget(2,218);z=1;
    scrifld(z++,fm_os20,pname[mode]);
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      j++;scrifld(z++,fm_ou3,&j);j--;
      fieldspc(6,2,&pdum,fmt);
      scrifld(z++,fmt,tbe[j].code);
      fieldspc(6,3,&pdum,fmt);
      scrifld(z++,fmt,tbe[j].omschr);
      scrifld(z++,fm_uf6_2,&tbe[j].vp_prx);
    }
    key=scrupd(curs,0x2DF);curs=1;curspos_=fldcurs;
    if(key==101) return YES;
    if(key==104){
      j=(curspos_-1)/4;j+=start_;
      for(k=DIM_TBE-2;k>=j;k--){
	copy((char *)&tbe[k].recnr,(char *)&tbe[k+1].recnr,sizeof tbe[0]);
      }
      zero((char *)&tbe[j].recnr,sizeof tbe[0]);
    }
    if(key==105){
      j=(curspos_-1)/4;j+=start_;
      for(k=j;k<DIM_TBE-2;k++){
	copy((char *)&tbe[k+1].recnr,(char *)&tbe[k].recnr,sizeof tbe[0]);
      }
      zero((char *)&tbe[DIM_TBE-1].recnr,sizeof tbe[0]);
    }

    if(key==110) get_isel();

    for(k=start_;k<(start_+D_LIN_SCR);k++){
      if((tbe[k].code[0] || tbe[k].omschr[0]) && tbe[k].hash!=hash(k)){
	fasinit(6);
	sr_nm=NO;
	if(tbe[k].code[0]) {*s(6,3)='.';copy(tbe[k].code,s(6,3)+1,fldlen(6,2));}
	else {copy(tbe[k].omschr,s(6,3),fldlen(6,3));sr_nm=YES;}
	if(search(6,0)){curs=3+(k-start_)*4;goto redo;}
	copy(s(6,2),tbe[k].code,fldlen(6,2));
	copy(s(6,3),tbe[k].omschr,fldlen(6,3));
	tbe[k].recnr=*pu_6_1;
	tbe[k].vp_prx=*f(6,PrNrs[prx_nr]);
	if(mode==PRIX/* && seldata.inq_klt*/) tbe[k].vp_prx=get_prx(NO);
      }
      else if(tbe[k].code[0]=='\0'){
	zero((char *)&tbe[k].recnr,sizeof tbe[0]);
      }
      tbe[k].hash=hash(k);
    }
    if(key==108){
      if(scr_ok("Wenst U de geselecteerde artikels af te drukken ?")==YES) break;
    }
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
    if(start_>(DIM_TBE-D_LIN_SCR)) start_=DIM_TBE-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){if(tbe[k+start_].code[0]=='\0') {j=k;break;}}
    curs=2+k*4;
  }
  for(k=0;k<DIM_TBE;k++) if(tbe[k].recnr) break;
  if(k<DIM_TBE) dmp_isel();
  return NO;
}

static get_isel()
{
  int16 j,k;
  uint16 rec_;
  char selname_[15];
 
  zero(selname_,sizeof selname_);copy("SEL215x.jam",selname_,12);
  selname_[6]='0'+mode;
  fasclos(-2);fasinit(80);
  if(fasopen(selname_,1)==0){
    k=0;
    FOREVER{
      fasinit(80);*l(80,1)=k*50*2;
      fasseqi(80,1,104);
      for(j=0;j<50;j++){
	rec_=*(uint16 *)(p_data+j*2);
	fasinit(6); *pu_6_1=rec_; if(rec_) fasgeti(6);
	tbe[k*50+j].recnr=*pu_6_1;
	copy(s(6,2),tbe[k*50+j].code,fldlen(6,2));
	copy(s(6,3),tbe[k*50+j].omschr,fldlen(6,3));
	tbe[k*50+j].vp_prx=*f(6,PrNrs[prx_nr]);
	if(mode==PRIX && seldata.inq_klt) tbe[k*50+j].vp_prx=get_prx(NO);
	tbe[k*50+j].hash=hash(k*50+j);
      }
      k++; if((k*50)>=DIM_TBE) break;
    }
    fasclos(-2);
  } else errnum=1;
}

static dmp_isel()
{
  int16 j,k;
  char selname_[15];
									
  zero(selname_,sizeof selname_);copy("SEL215x.jam",selname_,12);
  selname_[6]='0'+mode;
  fasclos(-2);fasinit(80);
  if(fasopen(selname_,2)==0){
    k=0;
    FOREVER{
      *l(80,1)=k*50*2;
      for(j=0;j<50;j++){
	copy((char *)&tbe[k*50+j].recnr,p_data+j*2,2);
      }
      fasseqo(80,2,100+4);
      k++; if((k*50)>=DIM_TBE) break;
    }
    fasclos(-2);
  }
  else errnum=1;
}


static stocklst(lsttype_)/* key 2 in stu 58 moet bestaan ! */
int16 lsttype_;/* YES = stocklijst, NO=tel-lijst */
{
  int16 key,curs=1,j,k,kk,n,z,key_mode,keynr,curspos_,pos_bdr_;
  int16 akey_,drv_mode_,firsttime,bpos_,z_stock_,bloc_,mloc_;
	int16 StylFill,StylNormal;
  char choice='A',extra_ln_='N',PrintTotaalPerBtw='N';
 
  bew_only='N'; inq_loc=99; copy("DEPOT",nm_fil,6);
  if(best_hdr=='\0') best_hdr='N';
  if(add_bstk=='\0') add_bstk='A';
  if(prt_waarde=='\0') prt_waarde='N';
  if(sel_beweg=='\0') sel_beweg='S';
  if(lsttype_==NO) sel_beweg='A';
	if(skip_blocked=='\0') skip_blocked='J';

  FOREVER{
    redo:
    if(lsttype_) scrget(2,221);else scrget(2,234); z=1;
		scraddpicto(1,0,72,22,4,2,583,0,0,"Maak PDF"); 
		if(YES /* lsttype_==1 */) scraddpicto(2,0,76,22,4,2,573,0,0,"Maak XLS"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_ALNGIP,&choice);
    if(fldlen(66,1)){
      scrifld(-z,fm_uu2,&inq_loc);z++;scrifld(z++,fm_os6,nm_fil);
    } else {streepje(z++); z++;}
    if(lsttype_){
      scrifld(z++,fm_uONA,&add_bstk);
			if(fldlen(16,1)) scrifld(z++,fm_udat,&dt_his_beg); else streepje(z++);
      scrifld(z++,fm_u_SAM,&sel_beweg);
      scrifld(z++,fm_uJN,&prt_waarde);
			scrifld(z++,fm_uJN,&PrintTotaalPerBtw);
    }
    else {
      scrifld(z++,fm_uJN,&prt_waarde);
      scrifld(z++,fm_uONA,&add_bstk);
      scrifld(z++,fm_uJN,&extra_ln_);
      scrifld(z++,fm_uJN,&best_hdr);
    }
		scrifld(z++,fm_uJN,&skip_blocked);
    key=scrupd(curs,0x0481);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		prt2pdf=NO;if(key==5001){prt2pdf=YES; key=108;} // pdf
		prt2xls=NO;if(key==5002){prt2xls=YES; key=108;} // xls
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
 
    if(inq_loc==99) copy("DEPOT",nm_fil,6);
    else if(inq_loc==0) copy("ALLEN",nm_fil,6);
    else if(inq_loc>=1 && inq_loc<=10){
      if(fldlen(66,11+(inq_loc-1)*15) && nm_loc[inq_loc-1][0]!='\0'){
	copy(nm_loc[inq_loc-1],nm_fil,6);
      }
      else {curs=3;zero(nm_fil,6);errnum=34;goto redo;}
    }
    else {curs=3;zero(nm_fil,6);errnum=34;goto redo;}
    if(key==18){
      curs=curspos_+1;goto redo;
    }

    bloc_=0; mloc_=max_loc;/* allemaal */
    if(fldlen(66,1)==0 || inq_loc==99) {bloc_=0;mloc_=0;}/* depot */
    else if(inq_loc>=1 && inq_loc<=10) {bloc_=inq_loc;mloc_=inq_loc;}

    if(key==108){
      switch(choice){
				case 'N' : keynr=1;break;
				case 'A' : keynr=2;break;
				case 'P' : keynr=6;break;
				case 'L' : keynr=90;break;
				case 'G' : keynr=91;break;
				default : keynr=0;break;
      }
      drv_lev=0;drv_grp=1;
      break;
    }
  }
  seldata.selp_use=NO;
  if(keynr){
    if(ovlcall(2215,5)) goto endsr;
  }
  else{
    if(get_art()) goto endsr;
  }
  scrget(1,6);scrupd(-3,0);
	if(prt2xls){
		scrget(1,7);scrupd(-3,0);
		if(lsttype_) XlsRef=OpenXlsFile("Actuele stocklijst",*u(25,2));
		else{
      if(best_hdr=='J') XlsRef=OpenXlsFile("Bestellijst",*u(25,2));
      else XlsRef=OpenXlsFile("Tellijst",*u(25,2));  
    }
    if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsColumnSize(XlsRef,1,8);
		XlsColumnSize(XlsRef,2,35);
		StylFill  =XlsStyle(XlsRef,"",12,0x00,NO,NO,NO,1,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,1,0,KLEUR_WIT,1,1,0,YES,NO);
	  XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,0,XlsKol++,0,"Code",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Naam",StylNormal);
		if(lsttype_){
			XlsWrite(XlsRef,0,XlsKol++,0,"Leverancier",StylNormal);
			XlsWrite(XlsRef,0,XlsKol++,0,"Groep",StylNormal);
			if(fldlen(6,10)) XlsWrite(XlsRef,0,XlsKol++,0,"EH",StylNormal);
			if(fldlen(66,1)) XlsWrite(XlsRef,0,XlsKol++,0,"Locatie",StylNormal);
			XlsWrite(XlsRef,0,XlsKol++,0,"A.stock",StylNormal);
			if(add_bstk=='O' || add_bstk=='A'){
				XlsWrite(XlsRef,0,XlsKol++,0,"Bons",StylNormal);
				XlsWrite(XlsRef,0,XlsKol++,0,"Stock",StylNormal);
			}
			if(sel_beweg=='M') XlsWrite(XlsRef,0,XlsKol++,0,"M.Stock",StylNormal);
			if(prt_waarde=='J'){
				XlsWrite(XlsRef,0,XlsKol++,0,"Netto AP",StylNormal);
				pos_bdr_=XlsKol;
				XlsWrite(XlsRef,0,XlsKol++,0,"Goederen",StylNormal);
				if(sys4731==0) XlsWrite(XlsRef,0,XlsKol++,0,"Leeggoed",StylNormal);
			}
		}
		else{
			if(fldlen(66,1)) XlsWrite(XlsRef,0,XlsKol++,0,"Filiaal",StylNormal);
			XlsWrite(XlsRef,0,XlsKol++,0,"Pl.Mag.",StylNormal);
			if(prt_waarde=='J'){
			  XlsWrite(XlsRef,0,XlsKol++,0,"Min.Stock",StylNormal);
			  XlsWrite(XlsRef,0,XlsKol++,0,"Norm.Stock",StylNormal);
				XlsWrite(XlsRef,0,XlsKol++,0,"Stock",StylNormal);
			}
			XlsWrite(XlsRef,0,XlsKol++,0,"Aantal",StylFill);
		}
		XlsRij++;
    goto no_header;
	}
  k=132;/* if(prt_waarde=='J') k=132; */
  if(lsttype_==NO){
		if(best_hdr=='J' || prt_waarde=='J') k=96; else k=80;
	}
  getsysprNew(5,form_dat,&pr_mode,&prtnr); if(prt2pdf)PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,k,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,25);
  if(lsttype_){
    if(sel_beweg=='M') prttext("<t30b>Artikels onder minimumstock<b><t65>");
    else prttext("<t40b>Actuele stocklijst<b><t65>");
    prtfld(25,2,-1);
    prttext("<t124>");prttext("Blz.<ppp>.");
  }
  else{
    if(best_hdr=='J'){
      prttext("<t50b>Bestellijst<b>");
    }
    else{
      prttext("<t30b>Tellijst<b><t45>");
      prtfld(25,2,-1);
    }
    prttext("<t72>");prttext("Blz.<ppp>.");
  }
  prtbuf(1);z=1;
  prttab(z,6,arcd+1,1,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,2,-1); prttitle(z++,"Naam",3);
  if(lsttype_ && prt_waarde!='J'){
    prttab(z,1,3,1,12); prttitle(z++,"Leverancier",3);
    prttab(z,6,10,2,-1); prttitle(z++,"EH",3);
  }
  z_stock_=z;
  if(fldlen(66,1)){
    prtitab(z,fm_os6,nm_fil,2,-1); prttitle(z++,"Locatie",3);
  }
  if(lsttype_){
    prtitab(z,fm_uf6_0,&p_qbak[0],1,-1); prttitle(z++,"A.stock",0x13);
    prtitab(z,fm_os4,p_qfles[0],1,-1); prttitle(z++,"",3);
    if(add_bstk=='O' || add_bstk=='A'){
      prtitab(z,fm_uf6_0,&p_qbak[1],1,-1); prttitle(z++,"Bons",0x13);
      prtitab(z,fm_os4,p_qfles[1],1,-1); prttitle(z++,"",3);
      prtitab(z,fm_uf6_0,&p_qbak[2],1,-1); prttitle(z++,"Stock",0x13);
      prtitab(z,fm_os4,p_qfles[2],2,-1); prttitle(z++,"",3);
    }
    if(sel_beweg=='M'){
      prttab(z,6,36,0,-1); prttitle(z++,"M.stock",0x13);
    }
    if(prt_waarde=='J'){
      prttab(z,6,18,0,-1); prttitle(z++,"Netto AP",0x13);
      prtitab(z,fm_od8_2,&stl[0].bd[0],0,-1); prttitle(z++,"Goederen",0x13);
      if(lgg_exist && sys4731==0){
				prtitab(z,fm_od8_2,&stl[0].bd[1],0,-1); prttitle(z++,"Leeggoed",0x13);
      }
    }
  }
  else{
    prtitab(z,fm_os5,stl[0].magaz,1,-1); prttitle(z++,"Mag.",3);
		prttab(z,6,36,0,-1); prttitle(z++,"Min.Stk",0x13);
		prttab(z,6,35,2,-1); prttitle(z++,"Nrm.Stk",0x13);
    if(prt_waarde=='J'){
      prtitab(z,fm_uf6_0,&p_qbak[2],1,-1); prttitle(z++,"Stock",0x13);
      prtitab(z,fm_os4,p_qfles[2],3,-1); prttitle(z++,"",3);
    }
    prtitab(z,fm_os15,"..............",1,-1); prttitle(z++,"Aantal",3);
  }
  prtbuf(3);
  if(lsttype_) p_pdfname("Stocklijst",0,0);
  else{
    if(best_hdr=='J') p_pdfname("Bestellijst",0,0);
    else p_pdfname("Tellijst",0,0);
  }
 
 no_header:;
  cnt=0;free=0;
  zero((char *)&stl[0].qlv[0],sizeof stl);zero((char *)&StockwPerBtw[0],sizeof StockwPerBtw);
  fasinit(6);
  key_mode=1;

  if(keynr==0){
    for(kk=0;kk<DIM_TBE;kk++){
      if(tbe[kk].code[0]){
				fasinit(6);*pu_6_1=tbe[kk].recnr;fasgeti(6);
				*u(1,1)=*u(6,7);fasgeti(1); bpos_=1;
				*u(52,1)=*u(6,9);fasgeti(52);
				if(fldlen(66,1)){
					fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
				}
				for(n=bloc_;n<=mloc_;n++){
					k=get_stlbd(n);
					if(sel_beweg!='A' && k==NO) continue;
					if(prt2xls){
						XlsKol=1;
						WriteFld2Xls(XlsRij,XlsKol++,6,arcd+1,StylNormal);
						WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
						if(lsttype_){
							WriteFld2Xls(XlsRij,XlsKol++,1,3,StylNormal);
							WriteFld2Xls(XlsRij,XlsKol++,52,14,StylNormal);
							if(fldlen(6,10)) WriteFld2Xls(XlsRij,XlsKol++,6,10,StylNormal);
							if(fldlen(66,1)) WriteVar2Xls(XlsRij,XlsKol++,fm_os6,nm_fil,StylNormal);
							WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[0],StylNormal);
							if(add_bstk=='O' || add_bstk=='A'){
								WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[1],StylNormal);
								WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[2],StylNormal);
							}
							if(sel_beweg=='M') WriteFld2Xls(XlsRij,XlsKol++,6,36,StylNormal);
							if(prt_waarde=='J'){
								WriteFld2Xls(XlsRij,XlsKol++,6,18,StylNormal);
								WriteVar2Xls(XlsRij,XlsKol++,fm_od7_2,&stl[0].bd[0],StylNormal);
								if(sys4731==0) WriteVar2Xls(XlsRij,XlsKol++,fm_od7_2,&stl[0].bd[1],StylNormal);
							}
						}
						else{
							if(fldlen(66,1)) WriteVar2Xls(XlsRij,XlsKol++,fm_os6,nm_fil,StylNormal);
							WriteVar2Xls(XlsRij,XlsKol++,fm_os5,stl[0].magaz,StylNormal);  // WriteFld2Xls(XlsRij,XlsKol++,6,29,StylNormal);
							if(prt_waarde=='J'){
								if(stl[0].min_stock) WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].min_stock,StylNormal); else XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylNormal);
								if(stl[0].max_stock) WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].max_stock,StylNormal); else XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylNormal);
								WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[0],StylNormal);
							}
							XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylFill);
						}
						XlsRij++;cnt++;
					}
					else{
						for(k=0;k<3;k++){
							stock2stks(stl[0].qlv[k],*f(6,31),&p_qbak[k],&p_qfles[k][0]);
						}
						k=0; if(lsttype_ && stl[0].qlv[2]<0) k=2;
						for(j=bpos_;j<=20;j++) prtinfo(j,k); nextline();
						if(bpos_==1 && fldlen(6,3+3) && *s(6,3+3)){
							copy(s(6,3+3),s(6,3),fldlen(6,3));
							prtinfo(2,0);nextline();
							fasgeti(6);
						}
						if(extra_ln_=='J') nextline();
						cnt++; bpos_=z_stock_;
					}
				}
      }
    }
    zero((char *)&tbe[0].recnr,sizeof tbe);
  }
  else if(keynr<90){
    FOREVER{
      next_1:;
      if(faskeyi(6,keynr,key_mode)) break;
      key_mode=2;
			if(skip_blocked=='J' && fldlen(6,200) && *u(6,200)) goto next_1;
      if(DirCall_DRK2215_SelectArtikel() && accept(10)){
				*u(1,1)=*u(6,7);fasgeti(1); bpos_=1;
				*u(52,1)=*u(6,9);fasgeti(52);
				if(fldlen(66,1)){
					fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
				}
#if FLAGAST // in firma FFC bedragen zonder accijns
        if(sys2696 && *f(6,18)>*f(6,30)) *f(6,18)-=*f(6,30);
#endif
				for(n=bloc_;n<=mloc_;n++){
					k=get_stlbd(n);
					if(sel_beweg!='A' && k==NO) continue;
					if(prt2xls){
						XlsKol=1;
						WriteFld2Xls(XlsRij,XlsKol++,6,arcd+1,StylNormal);
						WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
						if(lsttype_){
							WriteFld2Xls(XlsRij,XlsKol++,1,3,StylNormal);
							WriteFld2Xls(XlsRij,XlsKol++,52,14,StylNormal);
							if(fldlen(6,10)) WriteFld2Xls(XlsRij,XlsKol++,6,10,StylNormal);
							if(fldlen(66,1)) WriteVar2Xls(XlsRij,XlsKol++,fm_os6,nm_fil,StylNormal);
							WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[0],StylNormal);
							if(add_bstk=='O' || add_bstk=='A'){
								WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[1],StylNormal);
								WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[2],StylNormal);
							}
							if(sel_beweg=='M') WriteFld2Xls(XlsRij,XlsKol++,6,36,StylNormal);
							if(prt_waarde=='J'){
								WriteFld2Xls(XlsRij,XlsKol++,6,18,StylNormal);
								WriteVar2Xls(XlsRij,XlsKol++,fm_od7_2,&stl[0].bd[0],StylNormal);
								if(sys4731==0) WriteVar2Xls(XlsRij,XlsKol++,fm_od7_2,&stl[0].bd[1],StylNormal);
							}
						}
						else{
							if(fldlen(66,1)) WriteVar2Xls(XlsRij,XlsKol++,fm_os6,nm_fil,StylNormal);
							WriteVar2Xls(XlsRij,XlsKol++,fm_os5,stl[0].magaz,StylNormal);  // WriteFld2Xls(XlsRij,XlsKol++,6,29,StylNormal);
							if(prt_waarde=='J'){
								if(stl[0].min_stock) WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].min_stock,StylNormal); else XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylNormal);
								if(stl[0].max_stock) WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].max_stock,StylNormal); else XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylNormal);
								WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[0],StylNormal);
							}
							XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylFill);
						}

						XlsRij++;cnt++;
					}
					else{
						for(k=0;k<3;k++){
							stock2stks(stl[0].qlv[k],*f(6,31),&p_qbak[k],&p_qfles[k][0]);
						}
						if(n){
							*f(6,36)=*f(66,12+(n-1)*15);
							*f(6,35)=*f(66,13+(n-1)*15);
						}
						k=0; if(lsttype_ && stl[0].qlv[2]<0) k=2;
						for(j=bpos_;j<=20;j++) prtinfo(j,k);nextline();
						if(bpos_==1 && fldlen(6,3+3) && *s(6,3+3)){
							copy(s(6,3+3),s(6,3),fldlen(6,3));
							prtinfo(2,0);nextline();
							fasgeti(6);
						}
						if(extra_ln_=='J') nextline();
						cnt++; bpos_=z_stock_;
					}
				}
      }
    }
  }
  else {
    fasinit(6);
    if(keynr==90) akey_=4;
    else{
      akey_=2; if(faskeyi(6,5,1)==0) akey_=5;/* toch rechtstreekse key */
    }
    drv_mode_=1;
    zero(grp_used,sizeof grp_used);
    FOREVER{
      if(next_drv(keynr,drv_mode_)) break; drv_mode_=2;
      fasinit(6); firsttime=YES; key_mode=1; stockgt=0;
      goedgt=0;leeggt=0;
      if(keynr==90) *u(6,7)=drv_lev;
      else if(keynr==91) *u(6,9)=drv_grp;
      FOREVER{
				next_art:;
				if(faskeyi(6,akey_,key_mode)) break; key_mode=2;
				if(skip_blocked=='J' && fldlen(6,200) && *u(6,200)) goto next_art;
				if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
#if FLAGAST // in firma FFC bedragen zonder accijns
        if(sys2696 && *f(6,18)>*f(6,30)) *f(6,18)-=*f(6,30);
#endif
				if(keynr==90){
					if(*u(6,7)!=drv_lev) break;
				}
				else{
					grp_used[*i(6,9)]=1;
					if(*i(6,9)!=drv_grp){
						if(akey_==5) break; else goto next_art;
					}
				}
				if(accept(10)){
					bpos_=1;
					*u(52,1)=*u(6,9);fasgeti(52);
					*u(1,1)=*u(6,7);fasgeti(1);
					if(fldlen(66,1)){
						fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
					}
					for(n=bloc_;n<=mloc_;n++){
						k=get_stlbd(n);
						if(sel_beweg!='A' && k==NO) continue;
						if(prt2xls){
							XlsKol=1;
							WriteFld2Xls(XlsRij,XlsKol++,6,arcd+1,StylNormal);
							WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
							if(lsttype_){
								WriteFld2Xls(XlsRij,XlsKol++,1,3,StylNormal);
								WriteFld2Xls(XlsRij,XlsKol++,52,14,StylNormal);
								if(fldlen(6,10)) WriteFld2Xls(XlsRij,XlsKol++,6,10,StylNormal);
								if(fldlen(66,1)) WriteVar2Xls(XlsRij,XlsKol++,fm_os6,nm_fil,StylNormal);
								WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[0],StylNormal);
								if(add_bstk=='O' || add_bstk=='A'){
									WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[1],StylNormal);
									WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[2],StylNormal);
								}
								if(sel_beweg=='M') WriteFld2Xls(XlsRij,XlsKol++,6,36,StylNormal);
								if(prt_waarde=='J'){
									WriteFld2Xls(XlsRij,XlsKol++,6,18,StylNormal);
									WriteVar2Xls(XlsRij,XlsKol++,fm_od7_2,&stl[0].bd[0],StylNormal);
									if(sys4731==0) WriteVar2Xls(XlsRij,XlsKol++,fm_od7_2,&stl[0].bd[1],StylNormal);
								}
							}
							else{
								if(fldlen(66,1)) WriteVar2Xls(XlsRij,XlsKol++,fm_os6,nm_fil,StylNormal);
								WriteVar2Xls(XlsRij,XlsKol++,fm_os5,stl[0].magaz,StylNormal);  // WriteFld2Xls(XlsRij,XlsKol++,6,29,StylNormal);
								if(prt_waarde=='J'){
									if(stl[0].min_stock) WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].min_stock,StylNormal); else XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylNormal);
									if(stl[0].max_stock) WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].max_stock,StylNormal); else XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylNormal);
									WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&stl[0].qlv[0],StylNormal);
								}
								XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",StylFill);
							}
							XlsRij++;cnt++;
						}
						else{
							if(firsttime){
								nextline();
								prttext("<eb>");
								if(keynr==90){
									prtfld(1,1+lvcd,-1);prttext("  ");prtfld(1,3,-1);
								}
								else {
									prtfld(52,1,-1);prttext("  ");prtfld(52,14,-1);
								}
								prttext("<eb>");
								nextline(); nextline(); firsttime=NO;
							}
							*u(1,1)=*u(6,7);fasgeti(1);
							for(k=0;k<3;k++){
								stock2stks(stl[0].qlv[k],*f(6,31),&p_qbak[k],&p_qfles[k][0]);
							}
							if(n){
								*f(6,36)=*f(66,12+(n-1)*15);
								*f(6,35)=*f(66,13+(n-1)*15);
							}
							k=0; if(lsttype_ && stl[0].qlv[2]<0) k=2;
							for(j=1;j<=20;j++) prtinfo(j,k);nextline();
							if(bpos_==1 && fldlen(6,3+3) && *s(6,3+3)){
								copy(s(6,3+3),s(6,3),fldlen(6,3));
								prtinfo(2,0);nextline();
								fasgeti(6);
							}
							if(extra_ln_=='J') nextline();
							cnt++; bpos_=z_stock_;
						}
					}
				}
      }
      if((keynr==90 || keynr==91) && firsttime==NO){
				copy((char *)&stl[1].qlv[0],(char *)&stl[0].qlv[0],sizeof stl[0]);
				zero(stl[0].magaz,5);
				fasinit(6);zero(nm_fil,sizeof nm_fil);
				for(k=0;k<3;k++){
					stock2stks(stl[0].qlv[k],*f(6,31),&p_qbak[k],&p_qfles[k][0]);
				}
				if(prt2xls==NO){
					copy("Totaal ",s(6,3),7);
					if(keynr==91){fasinit(1);copy(s(52,14),s(6,3)+7,15);}
					if(lsttype_ /*  && prt_waarde=='J'*/ ){
						for(j=1;j<=20;j++) prtinfo(j,2);nextline();
					}
				}
				zero((char *)&stl[0].qlv[0],sizeof stl[0]);
				zero((char *)&stl[1].qlv[0],sizeof stl[0]);
      }
    }
  }
  if(cnt){
    copy((char *)&stl[2].qlv[0],(char *)&stl[0].qlv[0],sizeof stl[0]);
    zero(stl[0].magaz,5);
    fasinit(1);fasinit(6);zero(nm_fil,sizeof nm_fil);
    copy("Algemeen totaal ",s(6,3),20);
    for(k=0;k<3;k++){
      stock2stks(stl[0].qlv[k],*f(6,31),&p_qbak[k],&p_qfles[k][0]);
    }
		if(lsttype_ && prt_waarde=='J'){
			if(prt2xls){
			  XlsRij++;XlsKol=1;
			  XlsWrite(XlsRef,XlsRij,2,0,"Algemeen totaal",0);
				XlsKol=pos_bdr_;
				WriteVar2Xls(XlsRij,XlsKol++,fm_od7_2,&stl[0].bd[0],0);
				WriteVar2Xls(XlsRij,XlsKol++,fm_od7_2,&stl[0].bd[1],0);
			}
			else{
				stockw=0;bd_goed=0;bd_leeg=0;
				if(PrintTotaalPerBtw=='J'){
					nextline();z=0;stockw=0;
 					for(j=0;j<DIMBTW;j++){
						if(StockwPerBtw[j]){
							if(btw_pct[j]==def_btw) z=j;
							stockw+=StockwPerBtw[j];
						}
					}
					StockwPerBtw[z]+=stockw-stl[0].bd[0]; // correctie afronding
  				for(j=0;j<DIMBTW;j++){
	  				if(StockwPerBtw[j]){
		  				prttext("<t8b>Totaal goederen "); *f(6,28)=btw_pct[j]; prtfld(6,28,-1); prttext(" % : ");bd_goed=StockwPerBtw[j]; prtifld(fm_od6_2,&bd_goed,-1); nextline();
			  		}
					}
				}
			  nextline();for(j=1;j<=20;j++) prtinfo(j,2);nextline();
			}
		}
    zero((char *)&stl[0].qlv[0],sizeof stl);
  }
	if(prt2xls)	XlsClose(XlsRef,1);
  else prtclose();
  endsr:;
}

static ExistLeveranciersHistoriek(rec_art_,rec_lev_)
uint16 rec_art_,rec_lev_;
{
	int k,retbad_;
	long last_hisrec_;
	 
  if(fldlen(16,15)==0) return NO;
	if(rec_lev_==0 || rec_art_==0) return NO;
	last_hisrec_=*l(16,1);
  fasinit(16);*l(16,15)=rec_lev_;*l(16,20)=rec_art_;
  *u(16,3)=*u(25,2)-730;    // laatste 2 jaar 
  k=faskeyi(16,1,1); retbad_=NO;
	if(k) retbad_=YES;
  else if(*l(16,15)!=rec_lev_ || *l(16,20)!=rec_art_) retbad_=YES;
	fasinit(16);if(last_hisrec_){*l(16,1)=last_hisrec_;fasgeti(16);}
	if(retbad_) return NO;
	return YES;
}

static stock2txt()/* key 2 in stu 58 moet bestaan ! */
{
  int16 key,curs=1,k,n,z,key_mode,keynr,curspos_;
  int16 bpos_,bloc_,mloc_;
  char choice='A';
 
  sysget(1790,2,&k);
  if((k&2)==0) {errnum=12;goto endsr;}

  if(filnam[0]=='\0') copy("STOCK.TXT",filnam,20);seqo_mode=2;
  bew_only='N'; inq_loc=99; copy("DEPOT",nm_fil,6);
  if(add_bstk=='\0') add_bstk='N';
  if(sel_beweg=='\0') sel_beweg='S';
  sel_beweg='A';
  FOREVER{
    redo:
    scrget(2,268); z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_ALNGIP,&choice);
    if(fldlen(66,1)){
      scrifld(-z,fm_uu2,&inq_loc);z++;scrifld(z++,fm_os6,nm_fil);
    } else {streepje(z++); z++;}

    scrifld(z++,fm_us20,filnam);
 
    scrifld(z++,fm_uONA,&add_bstk);
    scrifld(z++,fm_u_SAM,&sel_beweg);

    key=scrupd(curs,0x0481);curs=1;curspos_=fldcurs;
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
 
    if(inq_loc==99) copy("DEPOT",nm_fil,6);
    else if(inq_loc==0) copy("ALLEN",nm_fil,6);
    else if(inq_loc>=1 && inq_loc<=10){
      if(fldlen(66,11+(inq_loc-1)*15) && nm_loc[inq_loc-1][0]!='\0'){
	copy(nm_loc[inq_loc-1],nm_fil,6);
      }
      else {curs=3;zero(nm_fil,6);errnum=34;goto redo;}
    }
    else {curs=3;zero(nm_fil,6);errnum=34;goto redo;}
    if(key==18){
      curs=curspos_+1;goto redo;
    }

    bloc_=0; mloc_=max_loc;/* allemaal */
    if(fldlen(66,1)==0 || inq_loc==99) {bloc_=0;mloc_=0;}/* depot */
    else if(inq_loc>=1 && inq_loc<=10) {bloc_=inq_loc;mloc_=inq_loc;}
    if(filnam[0]=='\0'){curs=5;errnum=38;goto redo;}

    if(key==108){
      switch(choice){
	case 'N' : keynr=1;break;
	case 'A' : keynr=2;break;
	case 'P' : keynr=6;break;
	default : keynr=1;break;
      }
      drv_lev=0;drv_grp=1;
      break;
    }
  }
  seldata.selp_use=NO;
  if(ovlcall(2215,5)) goto endsr;
  scrget(1,170);
  fasclos(-2);if(fasopen(filnam,2)) {errnum=9;goto endsr;}
  fasinit(80);seqo_pos=0;seqo_mode=2;
  zero(seqo_str,sizeof seqo_str);pos=0;
 
  scrget(1,7);scrupd(-3,0);
  zero((char *)&stl[0].qlv[0],sizeof stl);
  fasinit(6);
  key_mode=1;
  FOREVER{
    next_1:;
    if(faskeyi(6,keynr,key_mode)) break;
    key_mode=2;
		if(skip_blocked=='J' && fldlen(6,200) && *u(6,200)) goto next_1;
    if(DirCall_DRK2215_SelectArtikel() && accept(10)){
#if FLAGAST // in firma FFC bedragen zonder accijns
      if(sys2696 && *f(6,18)>*f(6,30)) *f(6,18)-=*f(6,30);
#endif
      zero(seqo_str,sizeof seqo_str);pos=0;
      *u(1,1)=*u(6,7);fasgeti(1); bpos_=1;
      if(fldlen(66,1)){
				fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
      }
      for(n=bloc_;n<=mloc_;n++){
				k=get_stlbd(n);
				if(sel_beweg!='A' && k==NO && bloc_==mloc_) goto next_1;
				if(n==0) seqo_fld(6,29);/* plaats magazijn */
				else seqo_fld(66,20+(n-1)*15);
				if(n==bloc_) {seqo_fld(6,2);seqo_fld(6,3);}
				*f(6,33)=stl[0].qlv[2]; seqo_fld(6,33); fasgeti(6);
      }
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

static bestellst()
{
  int16 key,curs=1,j,k,g,z,dd,mm,jj,key_mode,keynr,mode_,curspos_,last_grp_;
  int16 firsttime,lmode_,mode60_,use_lev_;
  uint16 n,inq_lev, dt_vrk_[4],dt_bon_end_=0,dt_nu_;
  char choice='A',only_min, prt_verk,skip_clips='J', reeds_aangekocht_='N', kw_str_[3][20];
  float vrk_per_[4],q_stock,q_bons,qlv_,minstock;
 
	dt_bon_end_=*u(25,2); inq_loc=0;
  jddate(*u(25,2),&jj,&mm,&dd); mm--;
#if FLAGGRS || FLAGSAS
  if(add_bstk=='\0') add_bstk='A';
#else
  if(add_bstk=='\0') add_bstk='N';
#endif
  if(fldlen(16,1) || fldlen(60,1)) prt_verk='M'; else prt_verk='\0';
	dt_nu_=*u(25,2);
  only_min='N';fasinit(1);
  FOREVER{
    redo:
    scrget(2,264);z=1; scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_ALNGIP,&choice);
    scrfld(z++,1,3);
    if(fldlen(8,1)){
			scrifld(z++,fm_uONA,&add_bstk); 
			scrifld(z++,fm_udat,&dt_bon_end_); 
		}
		else {streepje(z++);streepje(z++);}
    scrifld(z++,fm_uJN,&only_min);
    if(fldlen(16,15)) scrifld(z++,fm_uJN,&reeds_aangekocht_); else z++;
		scrifld(z++,fm_uJN,&skip_clips);
    if(fldlen(66,1)){
      scrifld(-z,fm_uu2,&inq_loc);z++;scrifld(z++,fm_os6,nm_fil);
    } else {streepje(z++); z++;}
    if(fldlen(16,1) || fldlen(60,1)){
			scrifld(z++,fm_uKM_,&prt_verk); 
			scrifld(z++,fm_udat,&dt_nu_); 
		}
		else {streepje(z++);streepje(z++);}
    key=scrupd(curs,0x0481);curspos_=fldcurs;curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		prt2pdf=NO;if(key==5001){prt2pdf=YES; key=108;} // pdf
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(*s(1,3)){
	  if(search(1,0)){curs=3; goto redo;}
    } else fasinit(1);
    inq_lev=*u(1,1);
    if(inq_loc==99 || inq_loc==0) copy("DEPOT",nm_fil,6);
    // else if(inq_loc==0) copy("ALLEN",nm_fil,6);
    else if(inq_loc>=1 && inq_loc<=10){
      if(fldlen(66,11+(inq_loc-1)*15) && nm_loc[inq_loc-1][0]!='\0') copy(nm_loc[inq_loc-1],nm_fil,6);
      else {curs=7;zero(nm_fil,6);errnum=34;goto redo;}
    }
    else {curs=7;zero(nm_fil,6);errnum=34;goto redo;}
    if(key==18){
      curs=curspos_+1;goto redo;
    }
    if(only_min=='J') sel_beweg='M'; else sel_beweg='A';
    if(key==108){
      switch(choice){
				case 'N' : keynr=1;break;
				case 'A' : keynr=2;break;
				case 'P' : keynr=6;break;
				case 'G' : keynr=5;break;
				default : keynr=1;break;
      }
      break;
    }
  }
  seldata.selp_use=NO;
  if(ovlcall(2215,3)) goto endsr;
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,25);
  prttext("<t30b>Bestellijst<b><t65>");
  prtfld(25,2,-1);
  prttext("<t124>");prttext("Blz.<ppp>.");
  prtbuf(1);z=1;
  prttab(z,6,arcd+1,1,-1); prttitle(z++,"Code",3);
#if !FLAGGRS
  prttab(z,11,5,1,10); prttitle(z++,"Lev.Ref.",3);
#endif
  prttab(z,6,3,2,-1); prttitle(z++,"Naam",3);
	zero(kw_str_,sizeof kw_str_);
  if(dt_nu_ && (prt_verk=='M' || fldlen(16,1)==0)){
		jddate(dt_nu_,&jj,&mm,&dd);
		if(prt_verk=='M'){
			mm++; if(mm>12){mm=1; jj++;}
			for(k=3;k>=0;k--){
				dt_vrk_[k]=datejd(jj,mm,1);
				mm--;if(mm<1){mm=12; jj--;}
			}
		}
		jddate(dt_nu_,&jj,&mm,&dd);mm--;
    prtitab(z,fm_of62,&vrk_per_[0],1,-1);
    k=mm-2; if(k<0) k=12+k; prttitle(z++,maand_str[k],0x13);
    prtitab(z,fm_of62,&vrk_per_[1],1,-1);
    k=mm-1; if(k<0) k=12+k; prttitle(z++,maand_str[k],0x13);
    prtitab(z,fm_of62,&vrk_per_[2],1,-1);
    k=mm-0; if(k<0) k=12+k; prttitle(z++,maand_str[k],0x13);
  }
	else if(dt_nu_ && prt_verk=='K'){
		jddate(dt_nu_,&jj,&mm,&dd);
	  if(mm%3) mm=mm+3-mm%3; 
	 
		for(k=3;k>=0;k--){
			j=4-((12-mm+1)/3);
			if(k>0) sprintf_s(kw_str_[k-1],15,"KW%d-%d",j,jj%100);
			mm++; if(mm>12){mm=1; jj++;}
			dt_vrk_[k]=datejd(jj,mm,1);
			mm--; if(mm<1){mm=12; jj--;}
			mm-=3;if(mm<1){mm=12; jj--;}
		}
		for(k=0;k<3;k++){prtitab(z,fm_of62,&vrk_per_[k],1,-1);prttitle(z++,kw_str_[k],0x13);}
	}
  prttab(z,6,29,1,-1); prttitle(z++,"Mag.",3);
  prttab(z,6,10,2,-1); prttitle(z++,"EH",3);
  prttab(z,6,36,1,-1); prttitle(z++,"Min.Stk",0x13);
  prttab(z,6,35,0,-1); prttitle(z++,"Nrm.Stk",0x13);
  prttab(z,6,33,1,-1); prttitle(z++,"A.Stock",0x13);
  if(add_bstk=='O' || add_bstk=='A'){
    prtitab(z,fm_of62_,&q_bons,1,-1); prttitle(z++,"Bons",0x13);
    prtitab(z,fm_of62_,&q_stock,1,-1); prttitle(z++,"Stock",0x13);
  }
  prtitab(z,fm_os15,"..............",1,-1); prttitle(z++,"Aantal",3);
  prtbuf(3);
  p_pdfname("Bestellijst",0,0);


  cnt=0;free=0;
  fasinit(1);if(inq_lev){*u(1,1)=inq_lev;fasgeti(1);} lmode_=1;
  FOREVER{
    next_l:;
    if(faskeyi(1,2,lmode_)) break; lmode_=2;
    if(inq_lev && *u(1,1)!=inq_lev) break;
    if(inq_lev==0){
      for(k=0;k<seldata.p_max_lev;k++) if(*u(1,1)==seldata.tb[k].rec) break;
      if(k>=seldata.p_max_lev || seldata.tb[k].select!='J') goto next_l;
    }
    scrget(1,170);scrfld(10,1,3);scrupd(-3,0);
    firsttime=YES;
    fasinit(6);
    n=0;scrnum=0;
    FOREVER{
      next_a1:;
      *u(6,1)=++n;
      g=fasgeti(6);
      if(g==47)break;
      if(g!=46){
				if(*i(6,9)==99) goto next_a1;
				if(skip_clips=='J' && fldlen(6,102) && *u(6,102)) goto next_a1;
				if(only_min=='J'){
				  if(inq_loc==0 || inq_loc==99){
						if(fldlen(6,36)){	if(*f(6,33)<*f(6,36)) goto next_a1;}
					}
					else{
						fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
            if(fldlen(66,11+(inq_loc-1)*15) && fldlen(66,12+(inq_loc-1)*15) && *f(66,11+(inq_loc-1)*15)<*f(66,12+(inq_loc-1)*15)) goto next_a1;
  				}
				}
				if(reeds_aangekocht_=='J'){
					if(ExistLeveranciersHistoriek(*u(6,1),*u(1,1))==NO) goto next_a1;
				}
//				if(only_min=='J' && *f(6,33)>=*f(6,36)) goto next_a1;
				use_lev_=NO;
				if(*u(6,7)==*u(1,1)){use_lev_=YES;break;}
				if(fldlen(11,1)){
					fasinit(11);*u(11,2)=*u(1,1); *u(11,3)=*u(6,1);
					if(faskeyi(11,1,1)==0){
						if(*u(11,2)==*u(1,1) && *u(11,3)==*u(6,1)) {use_lev_=YES;break;}
					}
				}
      }
    }
    if(use_lev_==NO) goto next_l;
	
    fasinit(6); key_mode=1;last_grp_=0;
    FOREVER{
      next_a:;
      if(faskeyi(6,keynr,key_mode)) break; key_mode=2;
      if(*i(6,9)==99) goto next_a;
			if(skip_clips=='J' && fldlen(6,102) && *u(6,102)) goto next_a;
      if(DirCall_DRK2215_SelectArtikel()==NO) goto next_a;
      if(*u(6,7)!=*u(1,1)){
				if(fldlen(11,1)){
					fasinit(11);*u(11,2)=*u(1,1); *u(11,3)=*u(6,1);
					if(faskeyi(11,1,1)) goto next_a;
					if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) goto next_a;
				} else goto next_a;
      }
			if(reeds_aangekocht_=='J'){
				if(ExistLeveranciersHistoriek(*u(6,1),*u(1,1))==NO) goto next_a;
			}
			fasinit(11);*u(11,2)=*u(1,1); *u(11,3)=*u(6,1);
			if(faskeyi(11,1,1)) fasinit(11); // goto next_a;
			if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) fasinit(11);
      q_bons=0;
      if(fldlen(8,1) && (add_bstk=='O' || add_bstk=='A')){
				fasinit(58);*u(58,14)=*pu_6_1;mode_=1;
				FOREVER{
					next58:;
					if(faskeyi(58,2,mode_)) break; mode_=2;
					if(*u(58,14)!=*pu_6_1) break;
					fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
					if(fldlen(8,36) && *u(8,36)) goto next58;
					if(dt_bon_end_ && *u(8,8)>dt_bon_end_) goto next58;
					if(fldlen(66,1) && fldlen(8,48) && inq_loc>=1 && inq_loc<=10 && *u(8,48)!=inq_loc) goto next58;
					qlv_=*f(58,31);
					if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
					q_bons+=qlv_;
				}
      }
			if(inq_loc==0 || inq_loc==99) {q_stock=*f(6,33);minstock=*f(6,36);}
			else {
				fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
				*f(6,33)=*f(66,11+(inq_loc-1)*15);
				*f(6,36)=*f(66,12+(inq_loc-1)*15);
				*f(6,35)=*f(66,13+(inq_loc-1)*15);
				copy(s(66,20+(inq_loc-1)*15),s(6,29),fldlen(66,20));
			}
      if(add_bstk=='A') q_stock=*f(6,33)-q_bons; else q_stock=*f(6,33)+q_bons;
      if(only_min=='J' && *f(6,33)>=*f(6,36)) goto next_a;
      if((prt_verk=='M' || prt_verk=='K') && dt_nu_){
				zero((char *)&vrk_per_[0],sizeof vrk_per_);
				if(fldlen(16,1)){
					fasinit(16); *l(16,20)=*u(6,1);*l(16,10)=1; mode60_=1;
					FOREVER{
						next16:;
						if(faskeyi(16,1,mode60_)) break; mode60_=2;
						if(*l(16,20)!=*u(6,1)) break;
						if(fldlen(16,15) && *l(16,15)) goto next16;/* geen aankopen */
						if(*u(16,3)<dt_vrk_[0] || *u(16,3)>=dt_vrk_[3]) goto next16;
						if(fldlen(16,8) && inq_loc){
							if(!(inq_loc==*u(16,8) || (inq_loc==99 && *u(16,8)==0))) goto next16; 
						}
						for(k=2;k>=0;k--) if(*u(16,3)>=dt_vrk_[k]) break;
						if(k>=0) vrk_per_[k]+=*d(16,30);
					}
				}
				else if(fldlen(60,1)){
					fasinit(60); *l(60,22)=*u(6,1);mode60_=1;
					FOREVER{
						next60:;
						if(faskeyi(60,1,mode60_)) break; mode60_=2;
						if(*l(60,22)!=*u(6,1)) break;
						if(fldlen(60,12) && *l(60,12)) goto next60;/* geen aankopen */
						for(k=mm-2;k<=mm;k++){
							if(k<0) vrk_per_[k-mm+2]+=*f(60,124+12+k);
							else vrk_per_[k-mm+2]+=*f(60,112+k);
						}
					}
				}
			}
      if(firsttime){
				nextline();
				prttext("<eb>");
				prtfld(1,1+lvcd,-1);prttext("  ");prtfld(1,3,-1);
				prttext("  ");prtfld(1,7,-1);
				prttext("<eb>");
				nextline(); nextline(); firsttime=NO;
      }
			if(keynr==5 && *u(6,9)!=last_grp_){
			  nextline();
				fasinit(52); *u(52,1)=*u(6,9);fasgeti(52);
				prttext("<eb>    ");
				prtfld(52,1,-1);prttext("  ");prtfld(52,14,-1);
				prttext("<eb>");
				nextline(); nextline(); 
				last_grp_=*u(6,9);
			}
      for(j=0;j<=20;j++) prtinfo(j,0); nextline();
      if(fldlen(6,3+3) && *s(6,3+3)){
				copy(s(6,3+3),s(6,3),fldlen(6,3));
				prtinfo(2,0);nextline();
				fasgeti(6);
      }
    }
  }
  prtclose();
  endsr:;
}

static get_stlbd(loc_nr_)
int16 loc_nr_;
{
  int16 j,k,mode_;
  uint16 rec_;
  char buf_[10];
  float qlv_,mqlv_=0,q_bak_,q_stk_,hoev_;

  zero((char *)&stl[0].qlv[0],sizeof stl[0]);
  if(loc_nr_==0){
    copy("DEPOT",nm_fil,6);
    if(fldlen(6,36)) mqlv_=*f(6,36);
    copy(s(6,29),stl[0].magaz,fldlen(6,29));
		stl[0].min_stock=*f(6,36);
		stl[0].max_stock=*f(6,35);
    stl[0].qlv[0]=*f(6,33);
    if(fldlen(8,1) && (add_bstk=='O' || add_bstk=='A')){
      fasinit(58);*u(58,14)=*pu_6_1;mode_=1;
      FOREVER{
				next58:;
				if(faskeyi(58,2,mode_)) break; mode_=2;
				if(*u(58,14)!=*pu_6_1) break;
				fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
				if(fldlen(8,36) && *u(8,36)!=0 && *u(8,36)!=10 && *u(8,36)!=180) goto next58;
				if(fldlen(66,1) && fldlen(8,48) /* && inq_loc>=0 && inq_loc<=10 */ && *u(8,48)!=99 && *u(8,48)!=0) goto next58;
				qlv_=*f(58,31); if(fldlen(8,36) && *u(8,36)==10) qlv_=-qlv_; // bestelling
				if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
				stl[0].qlv[1]+=qlv_;
      }
    }
		if(fldlen(16,1) && dt_his_beg) stl[0].qlv[0]+=GetHisBew(*u(6,1),dt_his_beg,0,loc_nr_);
  }
  else{
    if(fldlen(66,11+(loc_nr_-1)*15) && nm_loc[loc_nr_-1][0]!='\0'){
      copy(nm_loc[loc_nr_-1],nm_fil,6);
      if(fldlen(66,12+(loc_nr_-1)*15)) mqlv_=*f(66,12+(loc_nr_-1)*15);
      stl[0].qlv[0]=*f(66,11+(loc_nr_-1)*15);
      copy(s(66,20+(loc_nr_-1)*15),stl[0].magaz,fldlen(66,20+(loc_nr_-1)*15));
			stl[0].min_stock=*f(66,12+(loc_nr_-1)*15);
			stl[0].max_stock=*f(66,13+(loc_nr_-1)*15);
			if(fldlen(8,1) && (add_bstk=='O' || add_bstk=='A')){
				fasinit(58);*u(58,14)=*pu_6_1;mode_=1;
				FOREVER{
					next58_1:;
					if(faskeyi(58,2,mode_)) break; mode_=2;
					if(*u(58,14)!=*pu_6_1) break;
					fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
					if(fldlen(8,36) && *u(8,36)!=0 && *u(8,36)!=10 && *u(8,36)!=180) goto next58_1;
					if(fldlen(66,1) && fldlen(8,48) /* && inq_loc>=0 && inq_loc<=10*/ && *u(8,48)!=loc_nr_) goto next58_1;
					qlv_=*f(58,31); if(fldlen(8,36) && *u(8,36)==10) qlv_=-qlv_; // bestelling
					if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
					stl[0].qlv[1]+=qlv_;
				}
			}
			if(fldlen(16,1) && dt_his_beg) stl[0].qlv[0]+=GetHisBew(*u(6,1),dt_his_beg,0,loc_nr_);
    }
  }
	for(k=0;k<3;k++) stl[0].qlv[k]=Round((double)(stl[0].qlv[k]),3);
  if(add_bstk=='A') stl[0].qlv[2]=stl[0].qlv[0]-stl[0].qlv[1];
  else stl[0].qlv[2]=stl[0].qlv[0]+stl[0].qlv[1];
  if(*i(6,9)!=99){
    stl[0].bd[0]=stl[0].qlv[2] * *f(6,18);
    stl[0].bd[1]=0; // leeggoed 0 maken 
    if(*f(6,31)<1) *f(6,31)=1;
		rec_=*pu_6_1;
		q_bak_=stl[0].qlv[2];q_stk_=0;
		if(fldlen(6,31)){
			q_bak_=(long)(stl[0].qlv[2]);
			if(*f(6,31)>1 && stl[0].qlv[2]>0){
				q_stk_=(long)(((stl[0].qlv[2]-q_bak_)* *f(6,31))+0.49);
			} else q_stk_=0;
		}
		if(lgg_exist && *s(6,41)){
			hoev_=*f(6,42) * q_bak_;
			copy(s(6,41),buf_,fldlen(6,2));
			fasinit(6);copy(buf_,s(6,2),fldlen(6,2));
			if(faskeyi(6,1,0)==0) stl[0].bd[1]=*f(6,18) * hoev_;
			*pu_6_1=rec_;fasgeti(6);
		}
		if(lgg_exist && *s(6,44)){
			hoev_=*f(6,42) * q_stk_;
			copy(s(6,44),buf_,fldlen(6,2));
			fasinit(6);copy(buf_,s(6,2),fldlen(6,2));
			if(faskeyi(6,1,0)==0) stl[0].bd[1]+=*f(6,18) * hoev_;
			*pu_6_1=rec_;fasgeti(6);
		}

    //if(lgg_exist && *s(6,41)){
    //  rec_=*pu_6_1;bd_leeg_=0;
    //  copy(s(6,41),buf_,fldlen(6,2));
    //  fasinit(6);copy(buf_,s(6,2),fldlen(6,2));
    //  if(faskeyi(6,1,0)==0) bd_leeg_=*f(6,18);
    //  *pu_6_1=rec_;fasgeti(6);
    //  stl[0].bd[1]=stl[0].qlv[2] * *f(6,42) * bd_leeg_;
    //}
  }
  else {
    stl[0].bd[1]=stl[0].qlv[2] * *f(6,18);
  }
  if(sel_beweg=='S' && stl[0].qlv[0]==0 && stl[0].qlv[1]==0) return NO;
  if(sel_beweg=='M' && stl[0].qlv[2]>=mqlv_) return NO;
  for(k=1;k<3;k++){
    stl[k].qlv[0]+=stl[0].qlv[0];
    stl[k].qlv[1]+=stl[0].qlv[1];
    stl[k].qlv[2]+=stl[0].qlv[2];
    stl[k].bd[0]+=stl[0].bd[0];
    stl[k].bd[1]+=stl[0].bd[1];
	}
	for(j=0;j<8;j++) if(*f(6,28)==btw_pct[j]) break;
  if(j<8) StockwPerBtw[j]+=stl[0].bd[0];
  if(stl[0].qlv[0] || stl[0].qlv[1] || sel_beweg=='M') return YES;
  else return NO;
}

static float GetHisBew(arec_,dt_beg_,dt_end_,loc_nr_)
uint16 arec_,dt_beg_,dt_end_,loc_nr_;
{
	int mode_;
	float qlv_=0;

	fasinit(16);*l(16,20)=arec_;mode_=1;
	FOREVER{
		next:;
		if(faskeyi(16,1,mode_)) break; mode_=2;
		if(*l(16,20)!=arec_) break;
		if(*u(16,3)<=dt_beg_) goto next;
		if(dt_end_ && *u(16,3)>dt_end_) goto next;
		if(fldlen(16,8)){
			if(loc_nr_>=1 && loc_nr_<=10 && *u(16,8)!=loc_nr_) goto next;
			if((loc_nr_==0 || loc_nr_==99) && *u(16,8)!=0 && *u(16,8)!=99) goto next;
		}
		if(*l(16,10)) qlv_+=*d(16,30); // verkocht
		else qlv_-=*d(16,30); // aangekocht/mutatie
	}
	return qlv_;
}

static stock2stks(stock_,qst_,bak_,fls_)
float stock_,qst_,*bak_;
char *fls_;
{
  long stk_;
	float add_;
						
  zero(fls_,5);
  if(qst_<1) qst_=1;
  *bak_=(long)(stock_); stk_=0;
	add_=0.49; if(stock_<0) add_=-0.49;
  if(qst_>1 && stock_!=0){
    stk_=(long)(((stock_- *bak_) * qst_)+add_);
  } else stk_=0;
  if(stk_>999) stk_/=100;
  if(stk_) *fls_='/'; stcli_d(fls_+1,stk_,3,1);
}

static invent()
{
  int16 key,curs=1,j,z,key_mode,keynr;
  int16 akey_,drv_mode_,firsttime;
  char choice='A',qfles_[6],str_[50],PrintTotaalPerBtw='N';
  float qbak_,lg_prijs_,gd_prijs_;
	struct{
		int aantal;
		int stuks;
		int eenheid;
		int ak_prijs;
		int ak_stprijs;
		int lg_prijs;
		int lg_stprijs;
		int goederen;
		int leeggoed;
		int totaal;
	} kolomnr;
 
  if(bew_only=='\0') bew_only='J';
  if(prt_leeg=='\0') prt_leeg='J'; if(sys4731) prt_leeg='N';
  if(lg_splits=='\0') lg_splits='N';
  if(prt_vpr=='\0') prt_vpr='N';
	if(skip_blocked=='\0') skip_blocked='J';
	zero((char *)&kolomnr.aantal,sizeof kolomnr);
  FOREVER{
    redo:
    scrget(2,83);z=1;
		scraddpicto(1,0,72,22,4,2,583,0,0,"Maak PDF"); 
		scraddpicto(2,0,76,22,4,2,573,0,0,"Maak XLS"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_ALNGIP,&choice);
    if(lgg_exist) scrifld(z++,fm_uJN,&prt_leeg); else streepje(z++);
    z++;/*  scrifld(z++,fm_uJN,&lg_splits); */
    scrifld(z++,fm_uJN,&bew_only);
    scrifld(z++,fm_uJN,&prt_vpr);
    scrifld(z++,fm_uJN,&PrintTotaalPerBtw);
		scrifld(z++,fm_uJN,&skip_blocked);
    key=scrupd(curs,0x0481);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		prt2pdf=NO;if(key==5001){prt2pdf=YES; key=108;} // pdf
    prt2xls=NO;if(key==5002){prt2xls=YES; key=108;} // xls
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(key==108){
      switch(choice){
				case 'N' : keynr=1;break;
				case 'A' : keynr=2;break;
				case 'P' : keynr=6;break;
				case 'L' : keynr=90;break;
				case 'G' : keynr=91;break;
				default : keynr=1;break;
      }
      drv_lev=0;drv_grp=1;
      break;
    }
  }
  seldata.selp_use=NO;
  if(ovlcall(2215,5)) goto endsr;
/* zero((char *)&tb_lg[0].rec,sizeof tb_lg); */
	if(prt2xls){
		scrget(1,7);scrupd(-3,0);
		XlsRef=OpenXlsFile("Inventaris",dt_inv);
    if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsColumnSize(XlsRef,1,8);
		XlsColumnSize(XlsRef,2,35);
	  XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,0,XlsKol++,0,"Code",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Naam",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Leverancier",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Groep",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"BTW",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Aantal",0);kolomnr.aantal=XlsKol-1;
#if !FLAGDWP & !FLAGLVB & !FLAGOLH
		if(fldlen(6,31)){XlsWrite(XlsRef,0,XlsKol++,0,"Stuks",0);kolomnr.stuks=XlsKol-1;}
#endif
		if(fldlen(6,10)){XlsWrite(XlsRef,0,XlsKol++,0,"EH",0);kolomnr.eenheid=XlsKol-1;}
	//	if(prt_vpr=='J') XlsWrite(XlsRef,0,XlsKol++,0,"Verkoopprijs",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Aankoopprijs",0);kolomnr.ak_prijs=XlsKol-1;
#if !FLAGDWP  & !FLAGLVB & !FLAGOLH
		if(fldlen(6,31)){XlsWrite(XlsRef,0,XlsKol++,0,"Stuksprijs",0);kolomnr.ak_stprijs=XlsKol-1;}
#endif
		if(lgg_exist && sys4731==0){XlsWrite(XlsRef,0,XlsKol++,0,"LgPrijs",0);kolomnr.lg_prijs=XlsKol-1;}
		if(fldlen(6,31) && lgg_exist && sys4731==0){XlsWrite(XlsRef,0,XlsKol++,0,"LgStuk",0);kolomnr.lg_stprijs=XlsKol-1;}
		if(lgg_exist && sys4731==0){
		  XlsWrite(XlsRef,0,XlsKol++,0,"Goederen",0);kolomnr.goederen=XlsKol-1;
		  XlsWrite(XlsRef,0,XlsKol++,0,"Leeggoed",0);kolomnr.leeggoed=XlsKol-1;
  		XlsWrite(XlsRef,0,XlsKol++,0,"Totaal",0);kolomnr.totaal=XlsKol-1;
		}
		else {
      XlsWrite(XlsRef,0,XlsKol++,0,"Totaal",0);kolomnr.goederen=XlsKol-1;
		}
		XlsRij++;
    goto no_header;
	}


  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf)PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1);prttext("<t40eb>Inventarisboek<eb><t90>");
  prtifld(fm_udat,&dt_inv,-1);
  prttext("<t112>");prttext("Blz.<ppp>.");
  prtbuf(1);z=1;
  prttab(z,6,arcd+1,1,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,1,-1); prttitle(z++,"Naam",3);
  prttab(z,1,3,1,15); prttitle(z++,"Leverancier",3);
  if(fldlen(6,9)) {prttab(z,6,9,1,-1); prttitle(z++,"Gr",0x13);}
  prtitab(z,fm_uf6_0,&qbak_,1,-1); prttitle(z++,"Aantal",0x13);
  prtitab(z,fm_os4,qfles_,2,-1); prttitle(z++,"",3);
  prttab(z,6,10,1,-1); prttitle(z++,"EH",3);
  if(prt_vpr=='J'){
    prttab(z,6,21,1,-1); prttitle(z++,"Verk.pr.",0x13);
  }
  if(fldlen(6,64)){
    prttab(z,6,64,1,-1); prttitle(z++,"Aank.pr.",0x13);
    if(prt_leeg=='J' && lgg_exist){
      prtitab(z,fm_od7_2,&bd_goed,1,-1); prttitle(z++,"Goederen",0x13);
      prtitab(z,fm_od6_2,&bd_leeg,1,-1); prttitle(z++,"Leeggoed",0x13);
    }
    prtitab(z,fm_od7_2,&stockw,1,-1); prttitle(z++,"Totaal",0x13);
  }
  prtbuf(3);
  p_pdfname("Inventaris",dt_inv,0);
  
	no_header:;
  cnt=0;free=0;stockwt=0;stockgt=0; goedwt=0;goedgt=0; leegwt=0;leeggt=0; zero((char *)&StockwPerBtw[0],sizeof StockwPerBtw);
  fasinit(6);
  key_mode=1;
  if(keynr<90){
    FOREVER{
			next_1:;
      if(faskeyi(6,keynr,key_mode)) break;
      key_mode=2;
			if(skip_blocked=='J' && fldlen(6,200) && *u(6,200)) goto next_1;
      if(DirCall_DRK2215_SelectArtikel() && accept(10)){
				*u(1,1)=*u(6,7);fasgeti(1);*u(52,1)=*u(6,9);fasgeti(52);
				calc_inv();
				stock2stks(*f(6,63),*f(6,31),&qbak_,&qfles_[0]);
				if(prt2xls){
					if(*i(6,9)==99){
						gd_prijs_=0;lg_prijs_=*f(6,64);
					}
					else{
						gd_prijs_=*f(6,64);
						if(*f(6,63)){
							lg_prijs_=valu_cnv("EUR","EUR",(double)(bd_leeg/ *f(6,63)),(double)(0.01));
						} else lg_prijs_=0;
					}
					XlsKol=1;
					WriteFld2Xls(XlsRij,XlsKol++,6,arcd+1,0);
					WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
					WriteFld2Xls(XlsRij,XlsKol++,1,3,0);
					WriteFld2Xls(XlsRij,XlsKol++,52,14,0);
					WriteFld2Xls(XlsRij,XlsKol++,6,28,0);
					WriteVar2Xls(XlsRij,kolomnr.aantal,fm_of5_3,&InvXlsLijn.q_bak,0);
					if(kolomnr.stuks) WriteVar2Xls(XlsRij,kolomnr.stuks,fm_of5_3,&InvXlsLijn.q_stuk,0);
					if(fldlen(6,10)) WriteFld2Xls(XlsRij,kolomnr.eenheid,6,10,0);
			//		if(prt_vpr=='J') WriteFld2Xls(XlsRij,XlsKol++,6,21,0);
					WriteVar2Xls(XlsRij,kolomnr.ak_prijs,fm_of5_3,&InvXlsLijn.pr_bak,0);
					if(kolomnr.stuks) WriteVar2Xls(XlsRij,kolomnr.ak_stprijs,fm_of5_3,&InvXlsLijn.pr_stuk,0);
					if(kolomnr.lg_prijs) WriteVar2Xls(XlsRij,kolomnr.lg_prijs,fm_of5_3,&InvXlsLijn.lg_bak,0);
					if(kolomnr.lg_stprijs) WriteVar2Xls(XlsRij,kolomnr.lg_stprijs,fm_of5_3,&InvXlsLijn.lg_stuk,0);
		//			WriteVar2Xls(XlsRij,XlsKol++,fm_of5_3,&lg_prijs_,0);
					zero(str_,sizeof str_);
					if(kolomnr.ak_stprijs) sprintf(str_,"=ROUND(R%dC%d*R%dC%d + R%dC%d*R%dC%d ;2)",XlsRij,kolomnr.aantal,XlsRij,kolomnr.ak_prijs,XlsRij,kolomnr.stuks,XlsRij,kolomnr.ak_stprijs); 
					else sprintf(str_,"=ROUND(R%dC%d*R%dC%d;2)",XlsRij,kolomnr.aantal,XlsRij,kolomnr.ak_prijs); 
					XlsWrite(XlsRef,XlsRij,kolomnr.goederen,4,str_,0);
					zero(str_,sizeof str_);
					if(kolomnr.leeggoed){
						if(kolomnr.lg_stprijs) sprintf(str_,"=ROUND(R%dC%d*R%dC%d + R%dC%d*R%dC%d ;2)",XlsRij,kolomnr.aantal,XlsRij,kolomnr.lg_prijs,XlsRij,kolomnr.stuks,XlsRij,kolomnr.lg_stprijs);  
						else sprintf(str_,"=ROUND(R%dC%d*R%dC%d;2)",XlsRij,kolomnr.aantal,XlsRij,kolomnr.lg_prijs);  
					  XlsWrite(XlsRef,XlsRij,kolomnr.leeggoed,4,str_,0);
				
				  	zero(str_,sizeof str_);
					  sprintf(str_,"=R%dC%d+R%dC%d",XlsRij,kolomnr.goederen,XlsRij,kolomnr.leeggoed); 
					  XlsWrite(XlsRef,XlsRij,kolomnr.totaal,4,str_,0);
					}
					XlsRij++;cnt++;
				}
				else{
					for(j=1;j<=20;j++) prtinfo(j,0);
					nextline(); cnt++;
					if(fldlen(6,3+3) && *s(6,3+3)){
						copy(s(6,3+3),s(6,3),fldlen(6,3));
						prtinfo(2,0);nextline();
						fasgeti(6);
					}
				}
      }
    }
  }
  else {
    fasinit(6);
    if(keynr==90) akey_=4;
    else{
      akey_=2; if(faskeyi(6,5,1)==0) akey_=5;/* toch rechtstreekse key */
    }
    drv_mode_=1;
    zero(grp_used,sizeof grp_used);
    FOREVER{
      if(next_drv(keynr,drv_mode_)) break; drv_mode_=2;
      fasinit(6); firsttime=YES; key_mode=1; stockgt=0;
      goedgt=0;leeggt=0;
      if(keynr==90) *u(6,7)=drv_lev;
      else if(keynr==91) *u(6,9)=drv_grp;
      FOREVER{
				next_art:;
				if(faskeyi(6,akey_,key_mode)) break; key_mode=2;
				if(skip_blocked=='J' && fldlen(6,200) && *u(6,200)) goto next_art;
				if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
				if(keynr==90){
					if(*u(6,7)!=drv_lev) break;
				}
				else{
					grp_used[*i(6,9)]=1;
					if(*i(6,9)!=drv_grp){
						if(akey_==5) break; else goto next_art;
					}
				}
				if(accept(10)){
					if(firsttime && !prt2xls){
						nextline();
						prttext("<eb>");
						if(keynr==90){
							prtfld(1,1+lvcd,-1);prttext("  ");prtfld(1,3,-1);
						}
						else {
							prtfld(52,1,-1);prttext("  ");prtfld(52,14,-1);
						}
						prttext("<eb>");
						nextline(); nextline(); firsttime=NO;
					}
					*u(1,1)=*u(6,7);fasgeti(1);*u(52,1)=*u(6,9);fasgeti(52);
					calc_inv();
					stock2stks(*f(6,63),*f(6,31),&qbak_,&qfles_[0]);
					if(prt2xls){
						if(*i(6,9)==99){
							gd_prijs_=0;lg_prijs_=*f(6,64);
						}
						else{
							gd_prijs_=*f(6,64);
							if(*f(6,63)){
								lg_prijs_=valu_cnv("EUR","EUR",(double)(bd_leeg/ *f(6,63)),(double)(0.01));
							} else lg_prijs_=0;
						}
						XlsKol=1;
						WriteFld2Xls(XlsRij,XlsKol++,6,arcd+1,0);
						WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
						WriteFld2Xls(XlsRij,XlsKol++,1,3,0);
						WriteFld2Xls(XlsRij,XlsKol++,52,14,0);
						WriteFld2Xls(XlsRij,XlsKol++,6,28,0);
						WriteVar2Xls(XlsRij,kolomnr.aantal,fm_of5_3,&InvXlsLijn.q_bak,0);
						if(kolomnr.stuks) WriteVar2Xls(XlsRij,kolomnr.stuks,fm_of5_3,&InvXlsLijn.q_stuk,0);
						if(fldlen(6,10)) WriteFld2Xls(XlsRij,kolomnr.eenheid,6,10,0);
				//		if(prt_vpr=='J') WriteFld2Xls(XlsRij,XlsKol++,6,21,0);
						WriteVar2Xls(XlsRij,kolomnr.ak_prijs,fm_of5_3,&InvXlsLijn.pr_bak,0);
						if(kolomnr.stuks) WriteVar2Xls(XlsRij,kolomnr.ak_stprijs,fm_of5_3,&InvXlsLijn.pr_stuk,0);
						if(kolomnr.lg_prijs) WriteVar2Xls(XlsRij,kolomnr.lg_prijs,fm_of5_3,&InvXlsLijn.lg_bak,0);
						if(kolomnr.lg_stprijs) WriteVar2Xls(XlsRij,kolomnr.lg_stprijs,fm_of5_3,&InvXlsLijn.lg_stuk,0);
			//			WriteVar2Xls(XlsRij,XlsKol++,fm_of5_3,&lg_prijs_,0);
						zero(str_,sizeof str_);
						if(kolomnr.ak_stprijs) sprintf(str_,"=ROUND(R%dC%d*R%dC%d + R%dC%d*R%dC%d ;2)",XlsRij,kolomnr.aantal,XlsRij,kolomnr.ak_prijs,XlsRij,kolomnr.stuks,XlsRij,kolomnr.ak_stprijs); 
						else sprintf(str_,"=ROUND(R%dC%d*R%dC%d;2)",XlsRij,kolomnr.aantal,XlsRij,kolomnr.ak_prijs); 
						XlsWrite(XlsRef,XlsRij,kolomnr.goederen,4,str_,0);
						zero(str_,sizeof str_);
						if(kolomnr.leeggoed){
							if(kolomnr.lg_stprijs) sprintf(str_,"=ROUND(R%dC%d*R%dC%d + R%dC%d*R%dC%d ;2)",XlsRij,kolomnr.aantal,XlsRij,kolomnr.lg_prijs,XlsRij,kolomnr.stuks,XlsRij,kolomnr.lg_stprijs);  
							else sprintf(str_,"=ROUND(R%dC%d*R%dC%d;2)",XlsRij,kolomnr.aantal,XlsRij,kolomnr.lg_prijs);  
							XlsWrite(XlsRef,XlsRij,kolomnr.leeggoed,4,str_,0);
				
				  		zero(str_,sizeof str_);
							sprintf(str_,"=R%dC%d+R%dC%d",XlsRij,kolomnr.goederen,XlsRij,kolomnr.leeggoed); 
							XlsWrite(XlsRef,XlsRij,kolomnr.totaal,4,str_,0);
						}
						XlsRij++;cnt++;
					}
					else{
						for(j=1;j<=20;j++) prtinfo(j,0);
						nextline(); cnt++;
						if(fldlen(6,3+3) && *s(6,3+3)){
							copy(s(6,3+3),s(6,3),fldlen(6,3));
							prtinfo(2,0);nextline();
							fasgeti(6);
						}
					}
				}
      }
      if((keynr==90 || keynr==91) && firsttime==NO && !prt2xls){
				bd_goed=goedgt;bd_leeg=leeggt;
				fasinit(6);stockw=stockgt;
				copy("Totaal ",s(6,3),7);
				if(keynr==91){fasinit(1);copy(s(52,14),s(6,3)+7,15);}
				stock2stks(*f(6,63),*f(6,31),&qbak_,&qfles_[0]);
				for(j=1;j<=20;j++) prtinfo(j,2);nextline();
      }
    }
  }
  if(cnt){
		if(prt2xls){
			XlsRij++;XlsKol=1;
			XlsWrite(XlsRef,XlsRij,2,0,"Algemeen totaal",0);
			zero(str_,sizeof str_);	sprintf(str_,"=SUM(R2C%d:R%dC%d)",kolomnr.goederen,XlsRij-1,kolomnr.goederen); 
			XlsWrite(XlsRef,XlsRij,kolomnr.goederen,4,str_,0);
			if(kolomnr.leeggoed){
  			zero(str_,sizeof str_);sprintf(str_,"=SUM(R2C%d:R%dC%d)",kolomnr.leeggoed,XlsRij-1,kolomnr.leeggoed); 
  			XlsWrite(XlsRef,XlsRij,kolomnr.leeggoed,4,str_,0);
  			zero(str_,sizeof str_);sprintf(str_,"=SUM(R2C%d:R%dC%d)",kolomnr.totaal,XlsRij-1,kolomnr.totaal);
  			XlsWrite(XlsRef,XlsRij,kolomnr.totaal,4,str_,0);
			}
			XlsClose(XlsRef,1);
		}
		else{
			fasinit(1);fasinit(6);
			stockw=0;bd_goed=0;bd_leeg=0;
      if(PrintTotaalPerBtw=='J'){
				nextline();z=0;stockw=0;
 			  for(j=0;j<DIMBTW;j++){
					if(StockwPerBtw[j]){
						if(btw_pct[j]==def_btw) z=j;
						stockw+=StockwPerBtw[j];
					}
				}
				StockwPerBtw[z]+=stockw-goedwt; // correctie afronding
  			for(j=0;j<DIMBTW;j++){
	  			if(StockwPerBtw[j]){
		  			prttext("<t8b>Totaal goederen "); *f(6,28)=btw_pct[j]; prtfld(6,28,-1); prttext(" % : ");bd_goed=StockwPerBtw[j]; prtifld(fm_od6_2,&bd_goed,-1); nextline();
			  	}
			  }
			}
			fasinit(6);	stockw=stockwt;	bd_leeg=leegwt;bd_goed=goedwt;
			copy("Algemeen totaal ",s(6,3),20);
			nextline();
			stock2stks(*f(6,63),*f(6,31),&qbak_,&qfles_[0]);
			for(j=1;j<=20;j++) prtinfo(j,2);
			nextline();
		}
  }
  prtclose();
  endsr:;
}

static calc_inv()
{
  uint16 j,rec_;
  char buf_[10];
  float hoev_,q_bak_,q_stk_;

  rec_=*pu_6_1;zero((char *)&InvXlsLijn.q_bak,sizeof InvXlsLijn);
  bd_leeg=0;bd_goed=0; q_bak_=*f(6,63);q_stk_=0;
  if(*i(6,9)!=99 && fldlen(6,31)){
    if(*f(6,31)<1) *f(6,31)=1;
    q_bak_=(long)(*f(6,63));
		InvXlsLijn.pr_bak=*f(6,64);InvXlsLijn.pr_stuk=*f(6,64);
    if(*f(6,31)>1 && *f(6,63)>0){
      q_stk_=(long)(((*f(6,63)-q_bak_)* *f(6,31))+0.49);
			InvXlsLijn.pr_stuk=Round((double)(*f(6,64)/ *f(6,31)),3);
    } else q_stk_=0;
  }
	InvXlsLijn.q_bak=q_bak_;InvXlsLijn.q_stuk=q_stk_;
	if(*i(6,9)==99){
    InvXlsLijn.lg_bak=*f(6,64);InvXlsLijn.lg_stuk=*f(6,64);
	}
	if(*i(6,9)!=99 && lgg_exist && *s(6,41)){
    hoev_=*f(6,42) * q_bak_;
    copy(s(6,41),buf_,fldlen(6,2));
    fasinit(6);copy(buf_,s(6,2),fldlen(6,2));
    if(faskeyi(6,1,0)==0){
			InvXlsLijn.lg_bak=*f(6,64);
      bd_leeg=*f(6,64) * hoev_;
    }
    *pu_6_1=rec_;fasgeti(6);
  }
  if(*i(6,9)!=99 && lgg_exist && *s(6,44)){
    hoev_=*f(6,42) * q_stk_;
    copy(s(6,44),buf_,fldlen(6,2));
    fasinit(6);copy(buf_,s(6,2),fldlen(6,2));
    if(faskeyi(6,1,0)==0){
			InvXlsLijn.lg_stuk=*f(6,64);
      bd_leeg+=*f(6,64) * hoev_;
    }
    *pu_6_1=rec_;fasgeti(6);
  }

  bd_goed=*f(6,63) * *f(6,64);
  bd_goed=valu_cnv(def_munt,def_munt,(double)bd_goed,bd_afrond);
  bd_leeg=valu_cnv(def_munt,def_munt,(double)bd_leeg,bd_afrond);
  if(prt_leeg=='J'){
    if(*i(6,9)==99){
      hoev_=*f(6,63);
      *f(6,63)=hoev_;bd_leeg=hoev_ * *f(6,64);
      bd_leeg=valu_cnv(def_munt,def_munt,(double)bd_leeg,bd_afrond);
      bd_goed=0;
    }
    stockw=bd_leeg + bd_goed;
  }
  else stockw=bd_goed;
  stockgt+=stockw;stockwt+=stockw;
  goedgt+=bd_goed;goedwt+=bd_goed;
  leeggt+=bd_leeg;leegwt+=bd_leeg;
	for(j=0;j<8;j++) if(*f(6,28)==btw_pct[j]) break;
	if(j<8) StockwPerBtw[j]+=bd_goed;
}
 
static calc_leegg()
{
  uint16 rec_,nr_;
  float hoev_;
  char buf_[20];

  if(*i(6,9)==99 || !lgg_exist) goto endsr;/* leeggoed in leeggoedkolom optellen */
  rec_=*pu_6_1;
  bd_leeg=0;
  nr_=41; if(mode==PRIX && lg_fles) nr_=44;
  if(*s(6,nr_)){
    hoev_=*f(6,42);
    copy(s(6,nr_),buf_,fldlen(6,2));
    fasinit(6);copy(buf_,s(6,2),fldlen(6,2));
    if(faskeyi(6,1,0)==0){
      bd_leeg=*f(6,PrNrs[prx_nr]);
      if(mode==PRIX && seldata.inq_klt) bd_leeg=get_prx(NO);
      bd_leeg*=hoev_;
    }
  }
  *pu_6_1=rec_;fasgeti(6);
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

static initload()
{
  int16 k;

  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  if(fldlen(8,1)) fileopen(8);
  kont_exist=NO;
  if(fldlen(9,1)) {fileopen(9);kont_exist=YES;}
  if(fldlen(60,1)) fileopen(14);
  if(fldlen(16,1)) fileopen(13);
  if(fldlen(66,1)) fileopen(12);

  if(fldlen(6,18)) fld_ap=18; else fld_ap=12;
  sysget( 294,3,def_munt);
  sysget(1048,32,&btw_pct[0]);
	sysget(1084,4,&def_btw);
  sysget(1790,2,&sys1790);
  sysget(1918,2,&sear_stt);
	sysget(2696,2,&sys2696);
  sysget(2830,24,(char *)&sys2830[0]);
	sysget(3654,16,(char *)&sys2830[6]);
  sysget(3586,2,&sys3586);
  sysget(3596,2,&sys3596);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3622,2,&sys3622);
  sysget(3626,2,&dt_inv);
  sysget(3724,2,&sys3724);
  sysget(3760,2,&sys3760);
  sysget(3768,2,&sys3768);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,&sys3896[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);
  for(max_loc=10;max_loc>0;max_loc--) if(nm_loc[max_loc-1][0]!='\0') break;
  sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  sysget(4670,6,stuksprx);
	sysget(4780,4,&stuksprx[6]);
  sysget(4731,2,&sys4731);
  mult_prx=0;
  for(k=0;k<6;k++) if(fldlen(6,PrNrs[k])) mult_prx++;
  if(mult_prx>1) mult_prx=YES;
  else mult_prx=NO;
  if(fldlen(6,2)) arcd=YES;
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

  sysget(3678,2,&def_taal);
  bd_afrond=(double)0.01;
  if(fldlen(8,0)==0) add_bstk='N';
  pu_6_1=u(6,1);
  pu_2_1=u(2,1);
  if(faskeyi(6,6,0)==45){                /* controle op key plaats magazijn */
    for(k=0;k<sizeof fm_ALNGIP;k++) if(fm_ALNGIP[k]=='P') fm_ALNGIP[k]='A';
  }
  lgg_exist=NO; fmt_get(6,41); if(fmt[1]&0x40) lgg_exist=YES; 
  zero(&seldata.data_begin,sizeof seldata); seldata.dt_s_beg=*u(25,2)-730;
}
 

static accept(mode)
int16 mode;
{
  int16 k;
  float aantal_=0;

  if(fldlen(6,33)) aantal_=*f(6,33);
  if(fldlen(6,51)) aantal_+=*f(6,51);
  if(mode==STAT && bew_only=='J'){
    for(k=0;k<4;k++){
      if(ak_vk_0[k]=='J'){
	if(fldlen(6,53+k*2)) if(*f(6,53+k*2)) break;
	if(fldlen(6,54+k*2)) if(*f(6,54+k*2)) break;
      }
    }
    if(k==4) return NO;
  }
  if(mode==10 && bew_only=='J'){
    if(*f(6,63)==0) return NO;
  }
  return YES;
}

static float get_prx(imode_)
flag imode_;
{
  int16 m,nokort,pos_,vp_manueel_;
  float kort_=0,vp_=0,bd_accijn,bd_,hl_kort_,EUR_kort_;
 
  pos_=0;seldata.fl_afspraak=NO;hl_kort_=0; EUR_kort_=0;
  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd){pos_=10;prx_op_dt=YES;}
  vp_=*f(6,PrNrs[prx_nr+pos_]);if(*i(6,9)!=99) vp_norm=vp_;
  if(fldlen(2,18)) kort_=*f(2,18); else kort_=0;
  nokort=NO;
	if(fldlen(6,104) && *s(6,104)=='J') nokort=YES;
  *u(52,1)=*i(6,9);
  if(fasgeti(52)==0){
    if(fldlen(52,21) && *s(52,21)=='N') nokort=YES;
  }
  if(kont_exist){
    fasinit(9);*u(9,2)=*pu_2_1;*u(9,3)=*pu_6_1;
		m=get_contr(1); if(m==0) {seldata.fl_afspraak=YES;nokort=NO;}// wel korting indien expliciet 
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
				prx_op_dt=YES;
				if(*f(9,75)) vp_=*f(9,75);
				if(*i(6,9)!=99 && vp_>vp_norm) vp_norm=vp_;
				kort_=*f(9,73);/* korting in % altijd overrulen */
				EUR_kort_=*f(9,74);
				if(*f(9,74)) vp_-=*f(9,74);
				if(fldlen(9,81)) hl_kort_=*f(9,81);
      }
      else{
				if(*f(9,8)) vp_=*f(9,8);
				if(*i(6,9)!=99 && vp_>vp_norm) vp_norm=vp_;
				kort_=*f(9,6);/* korting in % altijd overrulen */
				EUR_kort_=*f(9,7);
				if(*f(9,7)) vp_-=*f(9,7);
				if(fldlen(9,20)) hl_kort_=*f(9,20);
      }
    }
  }
  if(fldlen(6,37)==0 || *f(6,37)==0) hl_kort_=0;
  else{                                        /* omrekenen naar verpakking */
    hl_kort_=hl_kort_* *f(6,37)/100;
  }
#if FLAGEPD || FLAGVDW // EUR korting als hl-korting gebruiken
	vp_+=EUR_kort_; hl_kort_+=EUR_kort_;
#endif
  bd_accijn=0;
  if(fldlen(6,30) && *i(6,9)!=99){
    bd_accijn=*f(6,30+pos_);
  }

  if((hl_kort_ || kort_) && nokort==NO){
    vp_=(vp_-bd_accijn)*(100.- kort_)/100.+bd_accijn;
    vp_-=hl_kort_;
  }

  if(*i(6,9)!=99){
    vp_=rnd_vprx((float)vp_,prx_nr);
    vp_manueel_=NO;
    if(via_ind_inp && imode_){
      if(vp_!=ind_prx) vp_manueel_=YES;
      vp_=ind_prx;
    }
    if(vp_>vp_norm) vp_norm=vp_;
    vp_inorm=vp_norm;
    if(bit(sys3894,prx_nr)==0){
      vp_inorm*=1.+*f(6,28)/100;
      vp_inorm=rnd_vprx(vp_inorm,prx_nr);
    }
    zero(krt_str,sizeof krt_str);
    if(kort_ && nokort==NO && !vp_manueel_){
      fbd2str(krt_str,kort_,4,2);copy(" %",&krt_str[7],2);
    }
    else {
      bd_=rnd_vprx(vp_-vp_norm,prx_nr);
      if(bd_<0){
	bd_=vp_norm-vp_;
	fbd2str(krt_str,bd_,4,2); copy(" E",&krt_str[7],3);
      }
    }
  }
  return (float)vp_;
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

static nextline()
{
  free=prtline();
}

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
}

static float rnd_vprx(fl_,type_)
float fl_;
int16 type_;
{
  float add, *pf;
							
  if(type_<0 || type_>9) type_=0; pf=&sys2830[type_];
  add=*pf;
  if(sys3618==0) add/=2.;
  add=add*.999999;
  if(*pf>0.0001){
    fl_=((long)((fl_+add)/(*pf))) * *pf;
  }
  return (float)fl_;
}

static fbd2str(ps_,bd_,len_,dec_)
float bd_;
char *ps_;
int16 len_,dec_;
{
  int16 k;
  double bedrag_,add_=0,fact_;
  long val_,value;
							
  fact_=1; for(k=0;k<dec_;k++) fact_*=10;
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*fact_+add_;value=val_/fact_;
  stcli_d(ps_,value,len_,1); ps_+=len_;
  value=val_-value*fact_;
  if(dec_){
    *(ps_++)=',';
    if(value<0) value=-value;
    stcli_d(ps_,value,dec_,0);
  }
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
 
static bit(byte_,bit_)
char byte_;
int16 bit_;
{
  if(byte_ & 1<<bit_) return YES;
  return NO;
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
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
