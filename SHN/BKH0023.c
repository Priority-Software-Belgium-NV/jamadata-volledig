/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0023GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0023dat
#define ovlcod BKH0023cod
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
  
char ovldat[] = "bkh0023  00:28 26/11/10 (c) Jamadata";
	// FLAGCOC : CC-adres gebruiken voor email
  
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define Q_LINES         80
#define LINE_LEN        128
#define SCR_LINES       20
#define TABSIZ          500
#define INP_LENGTH      200
#define flag            uint16
 
static char *types[4][5]={"","Fact","K.N.","Bet.","Div.",
		   "","Fact","N.C.","Pay.","Div.",
		   "","Invo","C.N.","Pay.","Div.",
		   "","Rech","G.S.","Zahl","Div."};

static struct _st {
  long rec4;
  uint16 jr;
  uint16 vl;
  uint16 ft_date;
  uint16 verv_dt;
  uint16 r_yy;
  uint16 r_jr;
  uint16 r_vl;
  char typ;/* 1=ft, 2=kn, 3=bet, 4=div */
  char status;/* 0=n.verv/n.vold 1=n.verv/vold 2=verv/n.vold 3=verv/vold */
  double VM_bedr;
  char dum;
  double ebedr;
  double bd_open;
} st[TABSIZ];

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

extern char *s();
static char get_byte();
extern int16 *i();
extern uint16 *u();
extern uint16 dateadd();
extern long *l();
extern long val();
static long val4_1();
extern float *f();
static float getgetal();
extern double *d(),valu_cnv();
static double eround();

static char *edit_buf;
static int16 form_dat[8],pr_mode,free,lst_typ,prtnr,pr_open=0;

static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os14[]  = {7,0x88,14,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us79[]  = {7,0xC8,79,0,0,0,0};
static char fm_us78[]  = {7,0xC8,78,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us10U[]  = {7,0xC8,10,0,1,0,0};
static char fm_us8[]   = {7,0xC8,8,0,0,0,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou2_[]  = {6,0x90,2,0,0x00,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ol9[]   = {6,0x93,9,0,0x70,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_uf3_3[] = {6,0xD4,3,3,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_udat6[] = {4,0xC0,0,' '};
static char fm_udatw[] = {4,0xC0,0xE,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_u_EF[]  = {11,0xC8,1,0,1,0,'E','E','F','F',0};
static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};

static struct {
  int16 begpos;
  int16 lengte;
} firm[14] = {0,30,/* naam */
	      31,25,/* straat  */
	      57,7,/* postcode */
	      65,20,/* gemeente */
	     116,17,/* "Telefoon","N– t…l…phone","Telephone","Telefon", */
	     170,17,/* "Telefax","Telefax","Fax","Telefax", */
	      86,15,/* "B.T.W. nr.","N– T.V.A.","T.V.A.","M.W.S.", */
	     101,14,/* "Bankrek.","Banque","Bank","Bank", */
	     134,12,/* "RPR","RPM","","", */
	     149,20,/* "Erkenningsnr","","","", */
	     188,30,/* "Web-site","Web-site","","", */
	     222,30,/* "E-mail","E-mail","","", */
	     256,42,/* "IBAN","IBAN","IBAN","IBAN", */
	     298,11};/* "BIC","BIC","BIC","BIC"}; */

static int16 FormdatA4[8]={2480,3508,0,118,118,118,118,4};
static int16 loaded,j_tb[101],rap_model,chk_btoeg=0,q_rap=1,taaltxt,left_mar=0,PandJournaal;
static uint16 stu_80_ix,loadnr;
static unsigned SpoolFileNr;
static int16 nm_pdf_ok,prt2pdf;
static int16 VM_stu=4,VM_mnt=24,VM_bd=25;
static uint16 vrap_beg,vrap_end,min_vrap,dat_verz,briefterm[3];
static uint16 rek_nr,vdat_beg,vdat_end,ref_yy,ref_jr,ref_vl,ref_nr,q_dagen;
static double bedr_min,ebd_verv,ebd_nverv,etot_deb,etot_cre;
static double min_boete,eboetebd,eintr_bd,intr_bd;
static double vbd_verv,vbd_nverv,vtot_deb,vtot_cre,vboetebd,vintr_bd;
static float boetepct,intr_pct;
static char naam[21],opm[41],ver_term[4],display,prt_nvv,prt_bet,firma[350],NaamRappelBrief[20],AddKopieFacturen='N';
static char talen[4],structmed[15],resul[15],buf_[200],brfname[20],filname[30];
static char fre_in_txt[80],filnminp[3][16],def_munt[4],raptitel[20];
static flag ned_,sear_stt,lvcd,klcd,printed,skip_empty,fre_in_ok,stu4_ok,stu4_copied;
static flag sys3876,sys1848,stopflag;
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;

ovlcod()
{
  int16 curs,key,z,k;
  char gaverder='N';

  initload();

  *u(26,3)=*u(25,2);vdat_beg=0;vdat_end=*u(25,2);
  vrap_beg=0;vrap_end=0; min_vrap=0;
  display='J';prt_bet='N';prt_nvv='N';
#if FLAGDUB
	prt_nvv='J';
#endif
  bedr_min=0;
  curs=1;
  FOREVER{
    fasinit(2);fasunlck(0);
    redo:
    scrget(1,33);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0023A");
    scrfld(z++,26,3);
    scrifld(z++,fm_u_JN,&display);
    scrifld(z++,fm_udat,&vdat_beg);scrifld(z++,fm_udat,&vdat_end);
    if(fldlen(4,30)){
      scrifld(z++,fm_udat,&vrap_beg);scrifld(z++,fm_udat,&vrap_end);
    } else {streepje(z++);streepje(z++);}
    if(fldlen(4,29)) scrifld(z++,fm_uu2,&min_vrap); else streepje(z++);
    scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_u_JN,&gaverder);
    scrifld(z++,fm_ud7_2,&bedr_min);
    scrifld(z++,fm_u_JN,&prt_bet);
    scrifld(z++,fm_u_JN,&prt_nvv);
    scrifld(z++,fm_uu1,&q_rap);z++;
    scrifld(z++,fm_uu3,&briefterm[0]);
    scrifld(z++,fm_us10U,filnminp[0]);
    scrifld(z++,fm_uu3,&briefterm[1]);
    scrifld(z++,fm_us10U,filnminp[1]);
    scrifld(z++,fm_us10U,filnminp[2]);
    key=scrupd(curs,0x781);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==111) ovlexit(10);
    if(key==101) ovlexit(-1);
    prt2pdf=NO;if(key==109) prt2pdf=YES;
    if(key==110) {edit_brf();goto redo;}
    if(q_rap==0) q_rap=1;
	  if(key==5001){
			if(search(2,98)==0){curs=8;goto redo;}
	  }
    dat_verz=*u(26,3);
    if(vdat_end>*u(26,3)){errnum=76;curs=4; goto redo;}
    for(k=0;k<3;k++){
      sysput(1760+k*2,2,(char *)&briefterm[k]);
      sysput(1690+k*10,10,filnminp[k]);
    }
    if(*s(2,3)){
      if(search(2,0)) {curs=8;goto redo;}
    }
    if(*u(2,1) && gaverder!='J'){
      exec_klt();
      curs=8;
    }
    else{
      exec_all(*u(2,1));
      if(stopflag==NO) break;
    }
    if(free==-1) break;
  }
  prtclose();
  ovlexit(-1);
}

static exec_all(start_)
uint16 start_;
{
  int16 ks;

  if(free==-1)goto endsr;
  scrget(1,6);scrupd(-3,0);
  fasinit(2); stopflag=NO;
  FOREVER{
    if(start_){*u(2,1)=start_;fasgeti(2);start_=0;ks=0;}
    else ks=faskeyi(2,2,2);
    if(ks)break;
    if(YES /* fldlen(2,44)!=1 || *s(2,44)!='N' */) exec_klt();
    if(free==-1 || stopflag) break;
  }
  endsr:;
}

static exec_klt()
{
  int16 k,ks,q_exemp_,p_fil_,q_dag_;
  uint16 searcnr;
 
  searcnr=*u(2,1)+30000;
  if(2<3) corr_y2000(4,searcnr);

  fasunlck(-1);
	ref_nr=0;
  fasinit(4);
  *u(4,5)=*u(2,1)+30000;
  loaded=0;
  FOREVER{
    ks=faskeyi(4,4,2);
    if(ks || *u(4,5)!=*u(2,1)+30000) break;
    add_bew();
  }
  compress();/* schrap voldane stukken */
  tab_chk();/* vergelijk met datums en minimum */
  if(loaded){/* indien er bewegingen overschieten */
	fasclos(-2);
		p_fil_=0;
		for(k=0;k<loaded;k++){
			if(st[k].typ==1 && st[k].status==2){
				q_dag_=vdat_end-st[k].verv_dt;
				if(q_dag_>briefterm[1] /* 60 */) p_fil_=2;
				else if(p_fil_<2 && q_dag_>briefterm[0] /* 30 */) p_fil_=1;
			}
		}
		for(k=p_fil_;k>0;k--){
			if(filnminp[k][0]) break;
		}
		zero(NaamRappelBrief,sizeof NaamRappelBrief);
		copy(filnminp[k],NaamRappelBrief,16);

		redo_print:;
    if(printask()==YES){
			q_exemp_=q_rap;
			if(fldlen(2,123) && *s(2,123)=='J' && prt2pdf==0){
				k=prt2pdf;prt2pdf=2; prt_rap();
				FOREVER{
					if(MailDocument(1))break;
					if(DisplayWarning("Mailen NIET gelukt! Nogmaals proberen?",605)==NO) goto redo_print;
				}
    		if(fldlen(7,0) && MailUniqueID[0]!='\0'){
					fasinit(7);
					copy(MailUniqueID,s(7,2),12); *u(7,4)=*u(25,2); 
					*u(7,10)=2;*l(7,11)=*u(2,1);
					*u(7,15)=2;*u(7,16)=1+(procid/5);
					copy0("Rappel",s(7,17),20);
					fasadd(7);
				}
				prt2pdf=k;
				q_exemp_--;//if(q_exemp_<1) q_exemp_=1; prt_KOPIE+=1;
	  	}
				
      for(k=0;k<q_exemp_;k++){
				prt_rap();
				if(prt2pdf==2) {MailDocument(0);prt2pdf=0;break;}
			}
      if(fldlen(4,29)) upd_rapnr();
			if(display=='J') goto redo_print;
    }
  }
}

static upd_rapnr()
{
  int16 k;
							
  fasunlck(-2);
	for(k=0;k<loaded;k++){
    if(st[k].status==2){
      fasinit(4);chg4_1(st[k].rec4);fasgeti(4);
      if(fldlen(4,30)==0 || *u(4,30)<dat_verz){
	*u(4,29)+=1;
	if(fldlen(4,30)) *u(4,30)=dat_verz; fasupd(4);
      }
    }
  }
	fasunlck(-1);
}


static prt_rap()
{
  etot_deb=0,etot_cre=0;vtot_deb=0;vtot_cre=0;
  de_heer();
  ft_rappel();
  fasgeti(2);
}

static structm(pd,refnr_)/* 00.02 */
char *pd;/* 'kkk/kkff/fffcc'   K(lant) F(aktnr) C(heck) */
uint16 refnr_;
{
  int16 k,g=0,d=0;
  char resul[15];
  long lan1=0,lan2,rest;
  double doub;

  if(klcd && (sys1848&1)==0){
    copy(s(2,2),&resul[0],5);
    for(k=0;k<5;k++) if(resul[k]<'0' || resul[k]>'9') resul[k]='0';
    for(k=0;k<5;k++) lan1=lan1*10+resul[k]-'0';
  }
  else{
    stcli_d(resul,(long)*u(2,1),5,0);lan1=*u(2,1);
  }
  lan2=refnr_;stcli_d(&resul[5],lan2,5,0);
  doub=( ((double)lan1)*100000E0+lan2 );
  rest = doub - ((long)(doub/97E0)) * 97E0; if(rest==0) rest=97;
  stcli_d(&resul[10],rest,2,0);

  for(k=0;k<3;k++) *(pd+d++)=resul[g++];
  *(pd+d++)='/';
  for(k=0;k<4;k++) *(pd+d++)=resul[g++];
  *(pd+d++)='/';
  for(k=0;k<5;k++) *(pd+d++)=resul[g++];
  *(pd+d)='\0';
}

static add_bew()
{
  int16 k,typ;
  char *pa;

  if(loaded==TABSIZ) compress();
  if(loaded==TABSIZ) goto endsr;

  pa=(char *)&st[loaded];/* dit element volledig op 0 zetten */
  for(k=0;k<sizeof(struct _st);k++) *pa++='\0';

  st[loaded].rec4=val4_1();
  st[loaded].jr=*s(4,2);
  st[loaded].vl=*u(4,3);
  st[loaded].ft_date=*u(4,4);
  st[loaded].ebedr=*d(4,32);
  st[loaded].VM_bedr+=*d(VM_stu,VM_bd);
  st[loaded].r_yy=*s(4,8);
  st[loaded].r_jr=*s(4,9);
  st[loaded].r_vl=*u(4,10);
  k=j_tb[st[loaded].jr];
  if(k<3 || k>8){
    if(st[loaded].ebedr<0) typ=2; else typ=1;
  }
  else if(k<5) typ=3;
  else typ=4;
  st[loaded].typ=typ;
  loaded++;
  endsr:;
}

static printask()
{
  int16 start_,k,g,z,key,upd_,curs;
  uint16 t_qrap_[10],t_dt_rap_[10];
  double esal_tot,ebd_;
	char txtfile_[25];
							
  if(display!='J') return YES;
  esal_tot=ebd_verv+ebd_nverv;
  start_=0;upd_=NO;curs=1;
  FOREVER{
		redo:;
    scrnum=0;scrget(1,36);z=1;
		if(fldlen(2,123) && *s(2,123)=='J'){scraddf(199,0,70,0xB); scrifld(199,fm_os10," Via mail ");}
		scraddpicto(1,0,71,22,4,2,583,0,0,"Maak PDF"); 
		scraddpicto(2,0,75,22,4,2,569,0,0,"Mail"); 
    if(klcd) scrofld(z++,2,2,-1); else scrofld(z++,2,1,-1);
    scrofld(z++,2,3,-1);
		scrofld(z++,2,8,-1);  scrofld(z++,2,4,-1);
    scrofld(z++,2,20,-1);  scrofld(z++,2,5,-1); scrofld(z++,2,6,-1);
		scrifld(z++,fm_us10U,&NaamRappelBrief);
    scrifld(z++,fm_os3,"EUR");
    zero((char *)&t_qrap_[0],sizeof t_qrap_);
    zero((char *)&t_dt_rap_[0],sizeof t_dt_rap_);
    for(k=start_;k<start_+10;k++){
      if(k>=loaded) break;
      fasinit(4);chg4_1(st[k].rec4);fasgeti(4);
      if(fldlen(4,29)) t_qrap_[k-start_]=*u(4,29);
      if(fldlen(4,30)) t_dt_rap_[k-start_]=*u(4,30);
      scrifld(z++,fm_ou5,&st[k].vl);
      if(PandJournaal && st[k].jr==PandJournaal) scrifld(z++,fm_os4,"Huur"); else scrifld(z++,fm_os4,types[taaltxt][st[k].typ]);
      scrifld(z++,fm_odat,&st[k].ft_date);
      ebd_=st[k].ebedr;
      scrifld(z++,fm_od8_2,&ebd_);
      g=st[k].r_yy; if(g>=100) g-=100;
      scrifld(z++,fm_ou2_,&g);
      scrifld(z++,fm_ou2,&st[k].r_jr);
      scrifld(z++,fm_ou5,&st[k].r_vl);
      scrifld(z++,fm_odat,&st[k].verv_dt);
      if(upd_){scrifld(z++,fm_uu2,&t_qrap_[k-start_]);scrifld(z++,fm_udat,&t_dt_rap_[k-start_]);}
      else{scrifld(z++,fm_ou2,&t_qrap_[k-start_]);scrifld(z++,fm_odat,&t_dt_rap_[k-start_]);}
    }
    scrifld(110,fm_od8_2,&ebd_verv);
    scrifld(111,fm_od8_2,&ebd_nverv);
		scrifld(112,fm_u_JN,&AddKopieFacturen);
    scrifld(113,fm_od8_2,&esal_tot);
    key=scrupd(curs,0x78F);
		prt2pdf=NO;
  	if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) {stopflag=YES;return NO;}
    if(key==108) return NO;
		zero(txtfile_,sizeof txtfile_);
  	for(k=0;k<16;k++){
			if(NaamRappelBrief[k]=='\0') break;
			txtfile_[k]=NaamRappelBrief[k];
		}
		if(fldlen(2,24)) txtfile_[k++]=talen[taaltxt];
		copy(".txt",&txtfile_[k],5);
		fasclos(-2);
		if(errnum=fasopen(txtfile_,1)) goto redo;
		fasclos(-2);

		switch(key){
			case 5001 : prt2pdf=YES; return YES; break; // pdf
			case 5002 : prt2pdf=2; return YES; break; // mailen
			default : break;
		}

    if(upd_){
      for(k=start_;k<start_+10;k++){
				if(k>=loaded) break;
				fasinit(4);chg4_1(st[k].rec4);fasgeti(4);
				if(fldlen(4,29)) *u(4,29)=t_qrap_[k-start_];
				if(fldlen(4,30)) *u(4,30)=t_dt_rap_[k-start_];
				fasupd(4);
      }
      upd_=NO; curs=1;
    }
    if(key==111) {upd_=YES;curs=1;}
 
    prt2pdf=NO;
    if(key==104) return YES;/* afdrukken */
    if(key==109) {prt2pdf=YES; return YES;}/* pdf */
    if(key==110) {prt2pdf=2; return YES;} // mailen 
    if(key==102) start_-=10;
    if(key==103) start_+=10;
    if(start_>(loaded-10)) start_=loaded-10;
    if(start_<0) start_=0;
  }
}

static compress()
{
  int16 g,k,n;
  long bedrag;
  double ebedrag;

  bedrag=0; ebedrag=0;
  for(k=0;k<loaded;k++){
    ebedrag+=st[k].ebedr;
    st[k].status=0;
  }
  if(is_nul(ebedrag)){loaded=0;goto endsr;}

  for(k=0;k<loaded;k++){
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
    bedrag=0; ebedrag=0;
    n=k-1;
    FOREVER{
      n++;
      if(n>=loaded) break;
      if(st[n].r_yy!=ref_yy || st[n].r_jr!=ref_jr || st[n].r_vl!=ref_vl) break;
      ebedrag+=st[n].ebedr;
    }
    if(!is_nul(ebedrag)){
      k=n-1;
    }
    else{
      if(prt_bet!='J'){
	FOREVER{/* schrap voldane */
	  if(k==loaded) break;
	  if(st[k].r_yy!=ref_yy || st[k].r_jr!=ref_jr || st[k].r_vl!=ref_vl) break;
	  del_line(k);
	}
	k--;
      }
      else {
	for(g=k;g<n;g++){
	  st[g].status++;
	}
      }
    }
  }
  endsr:;
}

static tab_chk()
{
  int16 g,k,n,accept,vervallen;
/* controle op vervaldatums */
  for(k=0;k<loaded;k++){
    if(j_tb[st[k].jr]<3 || j_tb[st[k].jr]>8){
      chg4_1(st[k].rec4);fasgeti(4);
      if(*u(4,20)) st[k].ft_date=*u(4,20);
      st[k].verv_dt=*u(4,21);
      if(st[k].verv_dt==0){
				copy(s(2,13),ver_term,4);
				ver_term[3]='\0';
				st[k].verv_dt=dateadd(st[k].ft_date,ver_term);
      }
    }
		else if(st[k].verv_dt==0 && st[k].ebedr>0) st[k].verv_dt=st[k].ft_date; // toch forceren rappel te maken 
  }
  for(k=0;k<loaded;k++){
    if((st[k].verv_dt>vdat_end || st[k].verv_dt<vdat_beg) && prt_nvv=='N'){
      del_stuk(k);k--;
    }
  }
  accept=0;
  for(k=0;k<loaded;k++){
    if(st[k].verv_dt!=0 &&
	st[k].verv_dt>=vdat_beg &&
	st[k].verv_dt<=vdat_end){
      accept=1;
    }
  }
  if(accept==0){loaded=0;goto endsr;}

/* duidt vervallen stukken aan */
  for(k=0;k<loaded;k++){
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
    vervallen=0;
    n=k-1;
    FOREVER{
      n++;
      if(n>=loaded) break;
      if(st[n].r_yy!=ref_yy || st[n].r_jr!=ref_jr || st[n].r_vl!=ref_vl) break;
      if(st[n].verv_dt<=vdat_end) vervallen=1;
    }
    if(vervallen){
      for(g=k;g<n;g++){
	st[g].status+=2;
      }
    }
    k=n-1;
  }
/* controle op minimumbedrag */
  ebd_verv=0; ebd_nverv=0;
  vbd_verv=0;vbd_nverv=0;
  for(k=0;k<loaded;k++){
    if(st[k].status>1){
      if(st[k].typ<2){
	if(fldlen(2,46)>0){
	  st[k].ebedr=st[k].ebedr*(1.+ *f(2,46)/100.);
	}
      }
      ebd_verv+=st[k].ebedr; vbd_verv+=st[k].VM_bedr;
    }
    else {ebd_nverv+=st[k].ebedr; vbd_nverv+=st[k].VM_bedr;}
  }
  if(ebd_verv<bedr_min || is_nul(ebd_verv)){loaded=0;goto endsr;}

  if(min_vrap || vrap_beg || vrap_end){       /* controle op vorige rappels */
    for(k=0;k<loaded;k++){
      accept=0;
      if(st[k].status==2){
	accept=1;
	fasinit(4);chg4_1(st[k].rec4);fasgeti(4);
	if(fldlen(4,30)){
	  if(vrap_beg && *u(4,30)<vrap_beg) accept=0;
	  if(vrap_end && *u(4,30)>vrap_end) accept=0;
	}
	if(fldlen(4,29) && min_vrap && *u(4,29)<min_vrap) accept=0;
      }
      if(accept) break;
    }
    if(accept==0){loaded=0;goto endsr;}
  }
 
  for(k=0;k<loaded;k++){       /* bereken hoeveel de factuur nog open staat */
    st[k].bd_open=0;
    if(st[k].typ<2 && st[k].status==2){
      ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
      for(n=0;n<loaded;n++){
	if(st[n].r_yy==ref_yy && st[n].r_jr==ref_jr && st[n].r_vl==ref_vl){
	  st[k].bd_open+=st[n].ebedr;
	}
      }
    }
  }

  sort_tab();
  endsr:;
}

static sort_tab()
{
  int16 j,k,n,sw;
  char buf_[50];
									
  FOREVER{/* sorteren */
    sw=NO;
    for(k=0;k<loaded-1;k++){
      if(st[k].verv_dt > st[k+1].verv_dt){
	copy((char *)&st[k].rec4,buf_,sizeof st[0]);
	copy((char *)&st[k+1].rec4,(char *)&st[k].rec4,sizeof st[0]);
	copy(buf_,(char *)&st[k+1].rec4,sizeof st[0]);
	sw=YES;
      }
    }
    if(sw==NO) break;
  }
 
  for(k=0;k<loaded;k++){/* betalingen achter facturen zetten */
    redo_k:;
    if(st[k].verv_dt) break;
    if(st[k].dum==YES) continue;/* reeds verhuisd */
    if(st[k].r_yy==0 && st[k].r_jr==0 && st[k].r_vl==0) continue;/* voorschot */
    for(j=loaded-1;j>k;j--){
      if(st[j].r_yy==st[k].r_yy && st[j].r_jr==st[k].r_jr && st[j].r_vl==st[k].r_vl) break;
    }
    if(j>k){
      st[k].dum=YES;
      copy((char *)&st[k].rec4,buf_,sizeof st[0]);
      for(n=k+1;n<=j;n++){
	copy((char *)&st[n].rec4,(char *)&st[n-1].rec4,sizeof st[0]);
      }
      copy(buf_,(char *)&st[j].rec4,sizeof st[0]);
      goto redo_k;
    }
  }
}

static del_stuk(k)
int16 k;
{
  ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
  FOREVER{
    if(k==loaded) break;
    if(st[k].r_yy!=ref_yy || st[k].r_jr!=ref_jr || st[k].r_vl!=ref_vl) break;
    del_line(k);
  }
}

static del_line(line)
int16 line;
{
  int16 k;

  for(k=line;k<(loaded-1);k++){
    copy(&st[k+1].rec4,&st[k].rec4,sizeof(struct _st));
  }
  loaded--;
}

static edit_brf()
{

	FOREVER{
		redo:;
		if(ask_brief("aan te passen", NO)==NO) break;
		if(read_fil()==NO){
			zero(edit_buf,Q_LINES*LINE_LEN);
			if(scr_ok("Brief bestaat niet. Wenst U een nieuwe aan te maken?")==NO) goto redo;
		}
		if(edit_fil()) write_fil();
	}
}


static ask_brief(txt_actie_,fl_exist_)
char *txt_actie_;
int16 fl_exist_;
{
  int16 z,j,k,key;
	char nm_brief[20][20],fname_[20];

	memset(nm_brief,0,sizeof nm_brief);
	memset(fname_,0,sizeof fname_);copy("RAP*.TXT",fname_,10);
  fasopen(fname_,102);/* eerste call voor dir */
  for(k=0;k<20;k++){
    fasinfo(80,204);                            /* ophalen antwoord van dir */
    if (*s(80,1)=='\0') break;
    for(j=0;j<14;j++)	if(*(s(80,1)+j)=='.') break;
		copy(s(80,1),nm_brief[k],j);
  }
 
  FOREVER{
    zero(brfname,sizeof brfname); 
		redo:;
    scrget(1,227); z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_os50,txt_actie_);
    scrifld(z++,fm_us8,brfname);
		for(k=0;k<10;k++){
			scrifld(z++,fm_os10,nm_brief[k]);scrifld(z++,fm_os10,nm_brief[k+10]);
		}
    key=scrupd(1,0x04A1);
    if(key==101 || key==106) return NO;
		if(brfname[0]=='\0') {errnum=34;goto redo;}
    if(key==108){
			if(fl_exist_){
				for(k=0;k<20;k++) if(cmpstrU(brfname,nm_brief[k],14)==0) break;
				if(k>=20){errnum=1;goto redo;}
			}
			break;
		}
	}
	return YES;
}

static read_fil()
{
  int16 k, line, kol,count;
  char byte;
 
  zero(filname,sizeof filname);
  for(k=0;k<10;k++) if(brfname[k]) filname[k]=brfname[k]; else break;
  if(k==0) goto endsr;
  copy(".TXT",&filname[k],5);
  fasclos(-2);
  if(fasopen(filname,1)) return NO;
	zero(edit_buf,Q_LINES*LINE_LEN);
  inp_clr();line=0;kol=0;
  while(line<Q_LINES){
    byte=get_byte();
    if(!byte) break;
    if(byte==0x0D){
      get_byte();/* skip linefeed */
      if(kol<LINE_LEN) edit_buf[line*LINE_LEN+kol]='\0';
      line++;kol=0;
    }
    else{
      count=1;
      if(byte==9) {byte=' '; count=8;}/* expand TAB */
      while(count-->0)
	if(kol<LINE_LEN) edit_buf[line*LINE_LEN+kol++]=byte;
    }
  }
  fasclos(-2);
	return YES;
  endsr:;
}
 
static edit_fil()
{
  int16 j,k,z,curs, lpos_,z_lin_,curspos_;
  int16 start_,line,key,old_start;
 
  start_=0; old_start=-1; curs=1; lpos_=0;
  FOREVER{
    redo:;
    scrget(1,228); z=1;
		scraddpicto(1,0,76,22,4,2,514,0,0,"Extra opties"); 
    k=start_+1;scrifld(z++,fm_ou3,&k);
    k=start_+SCR_LINES;scrifld(z++,fm_ou3,&k);
    z_lin_=z;
    for(line=start_;line<start_+SCR_LINES;line++){
      scrifld(z++,fm_us78,&edit_buf[line*LINE_LEN+lpos_]);
    }
    key=scrupd(curs,0xFFF); curs=fldcurs;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){DisplayExtraFuncties();key=107;} // extra opties
    if(key==108) return YES;
    if(key==106) return NO;
    if(key==104){
      k=curspos_-z_lin_+start_;
      for(k;k<Q_LINES-1;k++){
				copy(&edit_buf[LINE_LEN*(k+1)],&edit_buf[LINE_LEN*k],LINE_LEN);
      }
      zero(&edit_buf[LINE_LEN*(Q_LINES-1)],LINE_LEN);
    }
    if(key==105){
      k=curspos_-z_lin_+start_;
      for(j=Q_LINES-1;j>k;j--){
				copy(&edit_buf[LINE_LEN*(j-1)],&edit_buf[LINE_LEN*j],LINE_LEN);
      }
      zero(&edit_buf[LINE_LEN*k],LINE_LEN);
    }

    if(key==102){
      start_-=SCR_LINES;
      if(start_<0) start_=0;
    }
    if(key==103){
      start_+=SCR_LINES;
      if(start_>=(Q_LINES-SCR_LINES)) start_=Q_LINES-SCR_LINES;
    }
    if(key==109){
      if(lpos_) lpos_=0; else lpos_=50;
    }
  }
}

static write_fil()
{
  int16 line,kol,j,k,max_line;
 
  for(max_line=Q_LINES-1;max_line>=0;max_line--){
    if(edit_buf[max_line*LINE_LEN]) break;
    if(edit_buf[max_line*LINE_LEN+50]) break;
  }
  if(max_line<0) goto endsr;/* no text */
  for(k=0;k<max_line;k++){
    if(edit_buf[(k*LINE_LEN)+50]){
      for(j=0;j<50;j++) if(edit_buf[(k*LINE_LEN)+j]=='\0') break;
      for(j;j<50;j++) edit_buf[(k*LINE_LEN)+j]=' ';
    }
  }

	fasunlck(-2);
  zero(filname,sizeof filname);
  for(k=0;k<10;k++) if(brfname[k]) filname[k]=brfname[k]; else break;
  if(k==0) goto endsr;
  copy(".TXT",&filname[k],5);
  fasclos(-2);
  if(fasopen(filname,2)){errnum=38;fasunlck(-1);return NO;}
  fasinit(80); stu_80_ix=0;
  for(line=0;line<=max_line;line++){
		for(kol=0;kol<LINE_LEN;kol++){
			if(edit_buf[line*LINE_LEN+kol]=='\0') break;
		}
		for(k=0;k<kol;k++){
			put_byte(edit_buf[line*LINE_LEN+k]);
		}
		put_byte(0x0D); put_byte(0x0A);
	}
	if(stu_80_ix){
	  CnvJamaChar(s(80,1)+4,stu_80_ix,NO);
	  fasseqo(80,2,stu_80_ix+4);
	}
  fasclos(-2);
	fasunlck(-1);
	return YES;
  endsr:;
}

static DisplayExtraFuncties()
{
	int z,j,k,key,used_=0,max_line;
	char choice,menu_punten[10],dsp_lijn[80],oldname_[20];

	FOREVER{
		scrget(1,7);cls();z=1;
		DisplayMenuTitel(5,"Extra opties rappelbrief",0xA);
		used_=0;zero(dsp_lijn,sizeof dsp_lijn);zero(menu_punten,sizeof menu_punten);
    used_++; sprintf(dsp_lijn,"Druk deze brief af ........................... : %d",used_);
		scraddfield(z,8,8+used_,0); scrifld(z++,fm_os50,dsp_lijn); menu_punten[0]='0'+used_;
	  used_++; sprintf(dsp_lijn,"Maak een pdf van deze brief .................. : %d",used_);
	  scraddfield(z,8,8+used_,0); scrifld(z++,fm_os50,dsp_lijn); menu_punten[1]='0'+used_;
	  used_++; sprintf(dsp_lijn,"Kopieer de inhoud van een andere brief ....... : %d",used_);
	  scraddfield(z,8,8+used_,0); scrifld(z++,fm_os50,dsp_lijn); menu_punten[1]='0'+used_;
		sprintf(dsp_lijn,"                                       U kiest ?");
		scraddfield(z,8,8+used_+3,0); scrifld(z++,fm_os50,dsp_lijn);
		scraddfield(z,57,8+used_+3,2);scrifld(z++,fm_menu,&choice);
		scraddfield(z,1,23,8);scrifld(z++,fm_os10," F1 terug ");
    if(used_){
			key=scrupd(1,0x81);
		} else break;
	  if(key==101) break;
		if(choice=='1' || choice=='2'){
      scrget(1,6);scrupd(-3,0);scrnum=0;
      getsysprNew(4,form_dat,&pr_mode,&prtnr); if(choice=='2')  PrintPaperNr=0;
			if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,0))!=0) break;
      free=999;
      p_pdfname("Rappelbrief",0,0);     
      for(max_line=Q_LINES-1;max_line>0;max_line--){
				if(edit_buf[max_line*LINE_LEN]) break;
				if(edit_buf[max_line*LINE_LEN+50]) break;
			}
			for(k=0;k<=max_line;k++){
				if(edit_buf[(k*LINE_LEN)+50]){
					for(j=0;j<50;j++) if(edit_buf[(k*LINE_LEN)+j]=='\0') break;
					for(j;j<50;j++) edit_buf[(k*LINE_LEN)+j]=' ';
				}
				prttext(&edit_buf[k*LINE_LEN]); nextline();
      }
      prtclose();
      break;
    }
		if(choice=='3'){
			copy(brfname,oldname_,sizeof brfname);
			if(ask_brief("te kopieren", YES)){
  			if(read_fil()==NO){errnum=1;}
			}
			copy(oldname_,brfname,sizeof brfname);break;
		}
		errnum=34;
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

static put_byte(byte)
char byte;
{
  if(stu_80_ix==INP_LENGTH){
    CnvJamaChar(s(80,1)+4,INP_LENGTH,NO);
    fasseqo(80,2,INP_LENGTH+4);
    stu_80_ix=0;
  }
  *(s(80,1)+4+stu_80_ix++)=byte;
}

static streepje(z_)
int16 z_;
{
  scrifld(z_,fm_os1,"-");
}
 
static initload()
{
  int16 g,k;
  long rsize_,size_;

  fasunlck(0);
  fileopen(2);
  fileopen(4);
	if(fldlen(7,1)) fileopen(7);

#if _WIN32
  rsize_=ExtraSTOSize;
#else
  rsize_=onext-(uint16)s(99,1)-100; 
#endif
  size_=Q_LINES * LINE_LEN;
  if(rsize_<size_){
    scrget(1,170);
    scrifld(10,fm_os63,"Er is onvoldoende geheugen om verder te gaan!");
    scrifld(12,fm_os63,"Bel Jamadata over dit probleem");
    scrupd(-1,0x81);
    ovlexit(-1);
  }
  edit_buf=s(99,1)+50;

  for(k=0;k<80;k++){
    sysget(10240+k*80,2,&g);
    sysget(10242+k*80,2,&j_tb[g]);
  }

  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);

  sysget( 294,3,def_munt);
  sysget(1760,6,(char *)&briefterm[0]);
	sysget(1727,2,&PandJournaal); if(ovltest(71)==0) PandJournaal=0;
  for(k=0;k<3;k++) if(briefterm[k]!=0) break;
  if(k>=3){briefterm[0]=30; briefterm[1]=60;}
  sysget(1808,2,&rap_model);
  sysget(1848,2,&sys1848);
  sysget(1918,2,&sear_stt);
  sysget(2212,4,talen);
  sysget(3876,2,&sys3876);

  if(fldlen(4,20)==0){VM_stu=84;VM_mnt=11;VM_bd=9;}
  if(fldlen(4,15)){VM_stu=4;VM_mnt=15;VM_bd=16;}
  for(k=0;k<3;k++) sysget(1690+k*10,10,filnminp[k]);
  for(k=0;k<3;k++){
    if(filnminp[k][0]=='\0') copy("RAP1",filnminp[k],5);
  }
  pu_4_1=u(4,1); pl_4_1=l(4,1); len4_1=fldlen(4,1);
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

static de_heer()
{
  int16 g,j,k,slen;
  char *px,nm_dehr[53];

  px=s(2,3);slen=fldlen(2,3);
  for(k=0;k<slen-1;k++){
    if(*(px+k)=='*')break;
  }
  if(k>=slen-2) goto endsr;
  else{
    for(g=k+1;g<slen;g++) if(*(px+g)!=' ') break;
    if(g>slen-1) copy(px,nm_dehr,slen);
    else{
      for(j=slen-2;j>=g;j--) if(*(px+j)>' ') break;
      j=j-g+1;
      copy(px+g,nm_dehr,j);
      nm_dehr[j++]=' ';
      g=slen-j;if(g>k) g=k;
      copy(px,&nm_dehr[j],g);
      nm_dehr[j+g]='\0';
    }
  }
  copy(nm_dehr,px,slen);
  endsr:;
}

static skip_lin(line_)
int16 line_;
{
  while(free>line_) nextline();
}

static nextline()
{
  free=prtline();
}

static ft_rappel()
{
  int16 k;
  int16 form_dat[8],prmode,prtnr,pos_,count;
  char byte,txtfile_[21];

  taaltxt=0; if(fldlen(2,24)) taaltxt=*s(2,24);
  boetepct=0;min_boete=0;eboetebd=0;intr_pct=0;vboetebd=0;vintr_bd=0;
  eintr_bd=0;

	if(prt2pdf && AddKopieFacturen=='J'){
		getsysprNew(4,form_dat,&prmode,&prtnr);// PrintPaperNr=0;
		if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
		if((errnum=prtopen(prtnr,form_dat,6,80,prmode,3))!=0) ovlexit(10);
		copy("Rappel ",raptitel,7);copy(s(2,3),&raptitel[7],10);
		p_pdfname(raptitel,dat_verz,0); free=999;
		prttext("\xD0\xCD\xD0"); // meerdere docs
		nextline(); // prtline();
	}
	else{
    getsysprNew(4,form_dat,&prmode,&prtnr);
  	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
    if (prtopen(prtnr,form_dat,6,80,prmode,0)!=0) ovl_exit();
    free=999;
	}
	if(prt2pdf==0 || AddKopieFacturen!='J'){
    copy("Rappel ",raptitel,7);copy(s(2,3),&raptitel[7],10);
    p_pdfname(raptitel,dat_verz,0);
	}
  fasclos(-2);
	zero(txtfile_,sizeof txtfile_);
  for(k=0;k<16;k++){
		if(NaamRappelBrief[k]=='\0') break;
		txtfile_[k]=NaamRappelBrief[k];
	}
	if(fldlen(2,24)) txtfile_[k++]=talen[taaltxt];
	copy(".txt",&txtfile_[k],5);
	fasclos(-2);
	if(errnum=fasopen(txtfile_,1)) goto endsr;

  pos_=0;
  inp_clr();
  FOREVER{
    byte=get_byte();
    if(!byte) break;
    if(byte==0x0D){
      get_byte();/* skip linefeed */
      buf_[pos_++]='\0';buf_[pos_++]='\0';
      print_line();
      pos_=0;
    }
    else{
      count=1;
      if(byte==9) {byte=' '; count=8;}/* expand TAB */
      while(count-->0) buf_[pos_++]=byte;
    }
  }
  prtform(0);
	if(prt2pdf && AddKopieFacturen=='J'){ // niet bij afdrukken
		SpoolFileNr=prtclose();fasclos(-2);
		for(k=0;k<loaded;k++){
			if(st[k].typ==1 || st[k].typ==2){
				*u(26,1)=1; *u(26,2)=st[k].ft_date; *u(26,5)=st[k].vl; *u(26,26)=*u(2,1);
				ovlcall(257,2);
			}
		}

	// close rapport 
		getsysprNew(5,form_dat,&prmode,&prtnr);PrintPaperNr=0;
	//	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
		if((errnum=prtopen(prtnr,FormdatA4,6,80,prmode,3))!=0) ovlexit(10);
		prttext("\xD0\xCC\xD0");
		prtline();
		prtform(0);
	}
  endsr:;
  if(AddKopieFacturen=='J') prtclose(); else  SpoolFileNr=prtclose(); // indien met facturen, dan originele Spoolfilenr nemen 
	fasclos(-2);
}

static MailDocument(SendMode)
int SendMode;
{
  int j,k,p_adr_=0,fld_adres_=21;
	uint16 dt_,nr_,yy,mm,dd;
	double bd_;
	
		// keywords invullen 
	zero(MailMergeData[0],sizeof MailMergeData);MailSaveAdres='N';
	dt_=dat_verz; nr_=0; bd_=etot_deb+etot_cre+eboetebd+eintr_bd; // bd_=ebd_verv;
  if(fldlen(2,129) && *s(2,129)) fld_adres_=129; // apart bkh-adres  
	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"FIRMANAAM",4)==0){copy(&firma[0],MailMergeData[k],30); continue;}
		if(cmpstr(MailMergeKeywords[k],"KLANTID",7)==0){
			if(fldlen(2,2)) copy(s(2,2),MailMergeData[k],fldlen(2,2));
			else stcli_d(MailMergeData[k],(long)(*u(2,1)),5,1);
			continue;
		}
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy(s(2,3),MailMergeData[k],fldlen(2,3)); continue;}
		if(cmpstr(MailMergeKeywords[k],"ADRES",5)==0){copy(s(2,4),MailMergeData[k],fldlen(2,4)); continue;}
		if(cmpstr(MailMergeKeywords[k],"POSTCODE",8)==0){copy(s(2,5),MailMergeData[k],fldlen(2,5)); continue;}
		if(cmpstr(MailMergeKeywords[k],"GEMEENTE",8)==0){copy(s(2,6),MailMergeData[k],fldlen(2,6)); continue;}
#if FLAGCOC
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){
		  j=21; if(*s(2,130)) j=130; // CC adres = boekhouding
		  copy(s(2,j),MailMergeData[k],fldlen(2,j)); 
		  continue;
		}			
#else
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){p_adr_=k;copy(s(2,fld_adres_),MailMergeData[k],fldlen(2,fld_adres_)); continue;}
		if(fldlen(2,130) && fld_adres_==21 && cmpstr(MailMergeKeywords[k],"CC_EMAILADRES",13)==0){copy(s(2,130),MailMergeData[k],fldlen(2,130)); continue;}
#endif
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNAAM",12)==0){copy0("Rappel",MailMergeData[k],50); continue;}
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNUMMER",13)==0){stcli_d(MailMergeData[k],(long)nr_,5,1); continue;}
		if(cmpstr(MailMergeKeywords[k],"DATUM",5)==0){
			jddate(dt_,&yy,&mm,&dd);
      stcli_d(&MailMergeData[k][0],(long)dd,2,0);MailMergeData[k][2]='/';
      stcli_d(&MailMergeData[k][3],(long)mm,2,0);MailMergeData[k][5]='/';
      stcli_d(&MailMergeData[k][6],(long)yy,4,0);
			continue;
		}
		if(cmpstr(MailMergeKeywords[k],"TOTAALBEDRAG",12)==0){double2str(MailMergeData[k],(double)(bd_)); continue;}
	}
	zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage); // voor de veiligheid
	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);MailMergeBijlage[0]=SpoolFileNr;
	zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate);
	MailMergeFormaat=4; 
	if(fldlen(2,24)) MailMergeTaal=talen[taaltxt]; else MailMergeTaal='\0';
	k=SendMail(SendMode); 
#if FLAGCOC
	if(k && MailSaveAdres=='J'){copy(MailMergeData[p_adr_],s(2,130),fldlen(2,130));fasupd(2);} // email adres bewaren
#else
	if(k && MailSaveAdres=='J'){copy(MailMergeData[p_adr_],s(2,fld_adres_),fldlen(2,fld_adres_));fasupd(2);} // email adres bewaren
#endif
}



static int double2str(ps_,bd_)
char *ps_;
double bd_;
{
  int k,len_=0;
  char buff[15];
  double bedrag_,add_=0;
  long val_,value;
							
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*100+add_;value=val_/100;
 
  zero(buff,sizeof buff);
  stcli_d(&buff[0],value,10,1);
  for(k=0;k<10;k++){
    if(buff[k]=='\0') break;
    if(buff[k]!=' ') *(ps_+len_++)=buff[k];
  }
  value=val_-value*100;
  if(value){
    *(ps_+len_++)=',';
    if(value<0) value=-value;
    zero(buff,sizeof buff);
    stcli_d(&buff[0],value,2,0);
    for(k=1;k>=0;k--) if(buff[k]!='0') break;
    copy(&buff[0],ps_+len_,k+1);len_+=k+1;
  }
  return len_;
}

static print_line()
{
  int16 k,s1,s2;
  char byte;

  loadnr=0;stu4_ok=NO;
  FOREVER{
    chg4_1(st[loadnr].rec4);fasgeti(4);ref_nr=st[loadnr].vl;
    stu4_copied=NO;
    printed=NO;
    s1=0;
    FOREVER{
      if(buf_[s1]=='\0') break;
      if(buf_[s1]=='@' && buf_[s1+1]=='@'){
	prttext("@");s1+=2;
      }
      else if(buf_[s1]=='@'){
	if(buf_[s1+1]=='!'){skip_lin((int16)getgetal(s1+2));goto endsr;}
	if(buf_[s1+1]=='*'){boetepct=getgetal(s1+2);goto endsr;}
	if(buf_[s1+1]=='B'){
	  min_boete=getgetal(s1+2);
	  goto endsr;
	}
	if(buf_[s1+1]=='I'){intr_pct=getgetal(s1+2);calc_intr();goto endsr;}
	else s1=prtveld(s1+1);
      }
      else{
	s2=s1;
	FOREVER{
	  if(buf_[s2]=='\0'|| buf_[s2]=='@'){
	    byte=buf_[s2];
	    buf_[s2]='\0';k=s1;
	    left_mar=0;
	    FOREVER{
	      if(buf_[k]!=' ') break;
	      k++;left_mar++;
	    }
	    if(buf_[k]!='\0'){
	      left_mar=0;
	      prttext(&buf_[s1]);
	      printed=YES;
	    }
	    buf_[s2]=byte;
	    s1=s2;break;
	  }
	  s2++;
	}
      }
    }
    if(printed || s1==0 || (s1==1 && buf_[0]==' '))nextline();
    if(!stu4_ok) break;
    if(*d(4,32)>0) {etot_deb+=eround(*d(4,32));vtot_deb+=*d(VM_stu,VM_bd);}
    else {etot_cre+=eround(*d(4,32));vtot_cre+=*d(VM_stu,VM_bd);}
    loadnr++;
    if(loadnr==loaded) break;
  }
  vboetebd=((float)(vtot_deb+vtot_cre))*boetepct/100.;
  eboetebd=eround((double)((etot_deb+etot_cre)*boetepct/100.));
  if(!is_nul(min_boete)){
    if(eboetebd<min_boete) eboetebd=min_boete;
  }
  endsr:;
}


static calc_intr()
{
  int16 k;
  float pct_,bd_,vbd_,q_dagen;
  double ebd_,ft_intr_;
 
  bd_=0; vbd_=0; ebd_=0; pct_=intr_pct*12.;
  if(pct_==0) goto endsr;
  for(k=0;k<loaded;k++){
    if(YES /* st[k].typ==1 && st[k].status==2*/){
			if(st[k].verv_dt==0) st[k].verv_dt=st[k].ft_date;
      q_dagen=*u(26,3)-st[k].verv_dt;
			ft_intr_=st[k].ebedr*(pct_*(q_dagen/365.))/100.;
			if(ft_intr_>=0 || st[k].typ!=1) {// enkel bij vervallen facturen of betalingen 
        ebd_+=st[k].ebedr*(pct_*(q_dagen/365.))/100.;
        vbd_+=st[k].VM_bedr*(pct_*(q_dagen/365.))/100.;
			}
    }
  }
  endsr:;
  intr_bd=bd_; eintr_bd=eround(ebd_); vintr_bd=vbd_;
}
 
static prtveld(pos_)
int16 pos_;
{
  int16 k,numb[3];
  flag ok;
  double bd_,d_bd_,ibd_,pct_;
  char str_[20],fmt_[40];

  if(buf_[pos_]=='@'){fre_input();++pos_;goto puntok;}
  skip_empty=NO;
  if(buf_[pos_]=='*') {skip_empty=YES;pos_++;}
  for(k=0;k<3;k++) numb[k]=-1;
  for(k=0;k<3;k++){
    ok=NO;
    numb[k]=0;
    FOREVER{
      if(buf_[pos_]>='0' && buf_[pos_]<='9'){
	numb[k]=numb[k]*10+buf_[pos_++]-'0';
	ok=YES;
      }
      else{if(ok==NO) numb[k]=-1; break;}
    }
    if(buf_[pos_++]!=',') break;
  }
  if(numb[0]==4){
    stu4_ok=YES;
    if(stu4_copied==NO){copy_4();stu4_copied=YES;}
  }
  if(numb[0]!=-1 && numb[1]!=-1){
    if(numb[0]==2){
      if(numb[1]==2){
	x();printed=YES;
	if(fldlen(2,2)) prtfld(2,2,-1); else prtfld(2,1,-1);
	goto puntok;
      }
    }
    if(numb[0]==4){
      if(numb[1]==2 || numb[1]==8 || numb[1]==9){
				x();printed=YES;
				k=*s(4,numb[1]);k=k%100; prtifld(fm_uu2_,&k,-1);
				goto puntok;
      }
    }
    if(numb[0]==80){
      if(numb[1]>=80 && numb[1]<94){
				if(numb[1]==87 && firma[firm[12].begpos]) numb[1]=92; // indien IBAN ingevuld, dan IBAN afdrukken
				copy(fm_os79,fmt_,sizeof fm_os79);
				for(k=0;k<firm[numb[1]-80].lengte;k++) if(firma[firm[numb[1]-80].begpos+k]=='\0') break;
				fmt_[2]=k; // enkel nettolengte nemen
				prtifld(fmt_,&firma[firm[numb[1]-80].begpos],firm[numb[1]-80].lengte);
				goto puntok;
      }


      if(numb[1]==7 || numb[1]==21 || numb[1]==22 || numb[1]==41 || numb[1]==42){
				x();printed=YES;
				if(numb[1]==7 || numb[1]==32 || numb[1]==41 || numb[1]==42) *d(4,32)=etot_deb+etot_cre;
				else if(numb[1]==21) *d(4,32)=etot_deb;
				else *d(4,32)=-etot_cre;
				if(numb[1]==42) {/* bedrag op overschrijving */
					zero(str_,sizeof str_);
					bd_=*d(4,32)*100;
					bd_=valu_cnv("EUR","EUR",bd_,(double)(1.0));/* vieze dings na de komma */
					stcli_d(str_,(long)bd_,9,1);
					prtdouble(str_,7);
					prttext("  ");prtdouble(&str_[7],2);
				}
				else if(numb[1]==41) {
					stcli_d(str_,(long)(*d(4,32)*100),9,1);
					prtdouble(str_,9);
				}
				else  prtfld(4,32,numb[2]);
				goto puntok;
      }
      if(numb[1]==10){
				x();printed=YES;
				if(PandJournaal && st[loadnr].jr==PandJournaal) prtifld(fm_os4,"Huur",-1); else prtifld(fm_os4,types[taaltxt][st[loadnr].typ],-1);
				goto puntok;
      }
      if(numb[1]==11 || numb[1]==12){
				if(stu4_copied==NO){copy_4();stu4_copied=YES;}
				x();printed=YES;
				bd_=*d(4,32);
				if(numb[1]==12) if(*d(4,32)<0) *d(4,32)=-*d(4,32); else *d(4,32)=0;
				else if(*d(4,32)<0) *d(4,32)=0;
				prtfld(4,32,numb[2]);
				*d(4,32)=bd_;
				goto puntok;
      }
      if(numb[1]==23 || numb[1]==24 || numb[1]==25){
				x();printed=YES;
				bd_=*d(4,32);
				if(numb[1]==23) *d(4,32)=etot_deb+etot_cre+eboetebd+eintr_bd;
				else if(numb[1]==24) *d(4,32)=eboetebd;
				else if(numb[1]==25) *d(4,32)=eintr_bd;
				prtfld(4,32,numb[2]);
				*d(4,32)=bd_;
				goto puntok;
      }
      if(numb[1]==26){
				x();printed=YES;
				q_dagen=0;
				if(YES /* st[loadnr].typ==1 && st[loadnr].status==2*/) q_dagen=*u(26,3)-st[loadnr].verv_dt;
				prtifld(fm_uu5,&q_dagen,-1);
				goto puntok;
      }
      if(numb[1]==27){/* intrest per factuur */
				x();printed=YES;
				bd_=*d(4,32);
				pct_=intr_pct*12.;
				q_dagen=0;ibd_=0;
				if(YES /* st[loadnr].typ==1 && st[loadnr].status==2 */) q_dagen=*u(26,3)-st[loadnr].verv_dt;
				if(q_dagen && pct_){
					ibd_=st[loadnr].ebedr*(pct_*(q_dagen/365.))/100.;
					ibd_=eround(ibd_);
				}
				*d(4,32)=ibd_;
				prtfld(4,32,numb[2]);
				*d(4,32)=bd_;
				goto puntok;
      }
      if(numb[1]==28 || numb[1]==29){
				x();printed=YES;
				bd_=*d(4,32);
				if(numb[1]==28) *d(4,32)=ebd_verv;
				if(numb[1]==29) *d(4,32)=ebd_nverv;
				prtfld(4,32,numb[2]);
				*d(4,32)=bd_;
				goto puntok;
      }
      if(numb[1]==39 || numb[1]==40){
				x();printed=YES;
				structm(structmed,ref_nr);
				if(numb[1]!=40) prtifld(fm_os14,structmed,-1);
				else prtdouble(structmed,14);
				goto puntok;
      }
      if(numb[1]==51 || numb[1]==52){/* debet/credit ook in BEF of VM */
				if(stu4_copied==NO){copy_4();stu4_copied=YES;}
				x();printed=YES;
				if(*s(VM_stu,VM_mnt)=='\0') copy(def_munt,s(VM_stu,VM_mnt),3);
				if(*s(VM_stu,VM_mnt)=='\0'
				 || *d(VM_stu,VM_bd)==0 || cmp_str(def_munt,s(VM_stu,VM_mnt),3)==0){
					bd_=*d(4,32);
					if(numb[1]==52) if(*d(4,32)<0) *d(4,32)=-*d(4,32); else *d(4,32)=0;
					else if(*d(4,32)<0) *d(4,32)=0;
					prtfld(4,32,numb[2]);
					*d(4,32)=bd_;
					goto puntok;
				}
				else {
					d_bd_=*d(VM_stu,VM_bd);
					if(numb[1]==52){
						if(*d(VM_stu,VM_bd)<0) *d(VM_stu,VM_bd)=-*d(VM_stu,VM_bd);
						else *d(VM_stu,VM_bd)=0;
					}
					else if(*d(VM_stu,VM_bd)<0) *d(VM_stu,VM_bd)=0;
					prtfld(VM_stu,VM_bd,numb[2]);
					*d(VM_stu,VM_bd)=d_bd_;
					goto puntok;
				}
      }
      if(numb[1]==53 || numb[1]==54){
				x();printed=YES;
				if(numb[1]==53) *d(4,VM_bd)=vtot_deb;
				else *d(4,VM_bd)=-vtot_cre;
				prtfld(4,VM_bd,numb[2]);
				goto puntok;
      }
      if(numb[1]==55 || numb[1]==56){
				x();printed=YES;
				d_bd_=*d(4,VM_bd);
				if(numb[1]==55) *d(4,VM_bd)=vbd_verv;
				if(numb[1]==56) *d(4,VM_bd)=vbd_nverv;
				prtfld(4,VM_bd,numb[2]);
				*d(4,VM_bd)=d_bd_;
				goto puntok;
      }
      if(numb[1]==57 || numb[1]==58 || numb[1]==59){
				x();printed=YES;
				d_bd_=*d(4,VM_bd);
				if(numb[1]==57) *d(4,VM_bd)=vtot_deb+vtot_cre+vboetebd+vintr_bd;
				else if(numb[1]==58) *d(4,VM_bd)=vboetebd;
				else if(numb[1]==59) *d(4,VM_bd)=vintr_bd;
				prtfld(4,VM_bd,numb[2]);
				*d(4,VM_bd)=d_bd_;
				goto puntok;
      }
    }
    if(fldlen(numb[0],numb[1])>0){
      if(skip_empty==NO || *s(numb[0],numb[1])){
				x();
				prtfld(numb[0],numb[1],numb[2]);
				printed=YES;
      }
    }
  }
  puntok:;
  return pos_;
}

static double eround(value_)
double value_;
{
  double bd_;
						
  bd_=valu_cnv(def_munt,def_munt,value_,(double)0.01);
  return (double)(bd_);
}

static fre_input()
{
  if(fre_in_ok==NO){
    scrget(2,139);
    scrifld(1,fm_us79,fre_in_txt);
    scrupd(1,0x80);
    fre_in_ok=YES;
  }
  prttext(fre_in_txt);
}

static x()
{
  if(left_mar){
    prtblank(left_mar);printed=YES;
    left_mar=0;
  }
}

static inp_clr()
{
  fasinit(80); stu_80_ix=INP_LENGTH;
}

static char get_byte()
{
  if (stu_80_ix==INP_LENGTH){
    fasseqi(80,1,INP_LENGTH+4);
    CnvJamaChar(s(80,1)+4,INP_LENGTH,YES);
    stu_80_ix=0;
  }
  return (char)(*(s(80,1)+4+stu_80_ix++));
}

static ovl_exit()
{
  fasflush(0);
  fasclos(-2);
  ovlexit(-1);
}

static copy_4()
{
  *s(4,2)=st[loadnr].jr;
  *u(4,3)=st[loadnr].vl;
  *u(4,4)=st[loadnr].ft_date;
  *d(4,32)=st[loadnr].ebedr;
  *s(4,8)=st[loadnr].r_yy;
  *s(4,9)=st[loadnr].r_jr;
  *u(4,10)=st[loadnr].r_vl;
  if(fldlen(4,20)) *u(4,21)=st[loadnr].verv_dt;
  else *u(84,6)=st[loadnr].verv_dt;
}

static prtdouble(ps_,len_)
char *ps_;
int16 len_;
{
  int16 k;
					
  for(k=0;k<len_;k++){
    prtifld(fm_os1,ps_+k,-1);prttext(" ");
  }
}

static float getgetal(pos_)
int16 pos_;
{
  float fl_=0,bd_k=1.;
  flag ok=NO,komma=NO;
	
  FOREVER{
    if(buf_[pos_]>='0' && buf_[pos_]<='9'){
      if(komma==NO) fl_=fl_*10+buf_[pos_++]-'0';
      else{
	bd_k=bd_k*.1;
	fl_+=(buf_[pos_++]-'0')*bd_k;
      }
      ok=YES;
    }
    else if(buf_[pos_]==','){komma=YES;pos_++;}
    else {if(ok==NO) fl_=-1.; break;}
  }
  return (float)fl_;
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
    if(*ry_!=ly_) { fasupd(bstu_); mode_=1;}          /* indien gewijzigd, updaten */
    *ry_=ly_;                                      /* key-volgorde behouden */
  }
}
 
static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}
static cmp_str(p1,p2,len)
int16 len;
char *p1,*p2;
{
  while(len--){
    if(*p1++!=*p2++)return 1;
  }
  return 0;
}

static DisplayWarning(ptxt, icoon)
char *ptxt;
int icoon;
{
  int16 key,color_;

	color_=0; if(icoon<500) color_=3;
  scrget(1,169);
	if(icoon) scraddpicto(1,0,32,1,12,6,icoon,0,color_,"Opgelet!"); 
  scrifld(12,fm_os79,ptxt);
redo_upd:;
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  else if(key==105) return NO;
	else goto redo_upd;
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

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
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

