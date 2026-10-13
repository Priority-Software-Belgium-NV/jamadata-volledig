/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0215GetD() {return &zzvw;}

#include "OvlShare.h"

#define ovldat DRK0215dat
#define ovlcod DRK0215cod
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

char ovldat[] = "drk0215  00:16 06/01/11 (c) Jamadata";
        // FLAGALS : prijslijst in XLS : formaat Districo uitschrijven om te kunnen inlezen via ovl2292
         // FLAGGBL : specifieke prijslijst excl. accijnzen 		 
        // FLAGEET : specifieke prijslijst excl. accijnzen 		
        // FLAGEPD : korting EUR na % rekenen, dus wordt bij HLkorting geteld
				// FLAGGRS : Leverancier uitschrijven in prijslijst-XLS
        // FLAGLOY : geen drankgedoe + speciale  prijslijst/bestellijst
       // FLAGHOE : "drankenlijst" ipv bestelbon
      // FLAGTOL : extra omschrijving (6,3+3) niet afdrukken op prijslijst
			// FLAGVDW : korting EUR na % rekenen, dus wordt bij HLkorting geteld
      // FLAGWYN : Bestelformulier/XLS klant : aantal in 1-ste kolom




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
#define DIM_LG          150
#define DIM_TBE         750
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
extern uint16 *u();
static uint16 hash();
extern long *l();
extern long val();
extern float *f();
static float rnd_vprx(),get_prx();
extern double *d();
extern double valu_cnv();
static double Round();

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];
extern uint16 jamin1[5];
extern uint16 code_seg, data_seg;
								
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
static char fm_us5U[] = {7,0xC8,5,0,1,0,0};
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
static char fm_od62_[] = {6,0x95,6,2,0x60,0};
static char fm_of7_2[] = {6,0x94,7,2,0x30,0};
static char fm_of6_2[] = {6,0x94,6,2,0x30,0};
static char fm_of62_[] = {6,0x94,6,2,0x60,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf6_3[] = {6,0xD4,6,3,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uONA[] = {13,0xC8,1,0,1,0,'A','A','N','N','O','O',0};
static char fm_uIE[]   = {11,0xC8,1,0,1,0,'I','I','E','E',0};
static char fm_ALNGIP[]= {19,0xC8,1,0,1,0,'A','A','I','I','G','G','L','L','N','N','P','P',0};
static char fm_u_FSV[] = {13,0xC8,1,0,0x09,0,'F','F','S','S','V','V',0};
static char fm_u_SAM[] = {13,0xC8,1,0,0x09,0,'A','A','M','M','S','S',0};
static char fm_u_09[] = {9,0xC8,1,0,1,0,'0','9',0};
 
static char *maand_str[12]={"JAN","FEB","MRT","APR","MEI","JUN","JUL","AUG","SEP","OKT","NOV","DEC"};
static int16 free,sys3596,sys3724,fld_ap,stu=6,mode,taal_nr,SortKey;
static int16 StylTotaal, StylDate, StylKlasse, StylNormal, StylTitel, Styl2Use;
static int16 prx_nr,zz_prx,max_loc,lgg_exist,acc_exist;
static int16 def_taal,prt2pdf;
extern int16 ilength; // XLS
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi,prt2xls; // XLS
static unsigned SpoolFileNr,DatumPrijs;
static int16 tot_veld[10] = {33,51,53,54,55,56,57,58,59,60};/* te totaliseren velden */
static int16 form_dat[8],pr_mode,prtnr,wpct_beg, wpct_end;
static uint16 dt_inv,cnt,sys3760,q_prx2prt;
static uint16 drv_lev,drv_grp,lg_fles,dt_p_upd,inq_loc;
static long RecNrContract;
static char fmt[40],vptekst[100],oldnm[50],def_munt[4],fld_attr[40];
static char bew_only,ak_vk_0[4],type_prx[6],std_txt[4][80],add_bstk,sel_beweg;
static char tot_buf[200],apprx='N',prt_leeg,lg_splits,prt_acc,prt_stock,prx_str[6][6];
static char prt_nprx='N',prt_kkrt='N',krt_str[10],prt_vpr='N',p_np_bld='J',prt_AKfiches='N';
static char nm_fil[6],nm_loc[10][6],stuksprx[10],prt_waarde,prt_wpct='N',LijstDeelverpakkingen='N';
static char MailBodyText[5][80],MailTemplate[10],ConfirmKlant='J',MailSelectOnlyOwnArt='J';
static char p_qfles[3][5],best_hdr;
static float p_qbak[3],sys3614,sys2830[10],NettoArtStock;
static float vp_exc,vp_inc;
static float prt_bd[6];  // FLAGEET | FLAGGBL
static double stockw,stockgt,stockwt;
/* float bd_leeg, leegwt,leeggt,bd_goed,goedgt,goedwt,ind_prx; */
static float bd_leeg, bd_goed,ind_prx;
static double leegwt,leeggt,goedgt,goedwt;
static float vp_kas[10],p_lg_bak,p_lg_stk,w_bedrag,w_pct,vp_norm,vp_inorm;
static double bd_afrond;
static flag chk_btoeg=NO,klcd,lvcd,arcd=NO,FlagMailPrijsOpslag,FlagSortViaGroep;
static flag sear_stt,sys3618,sys3876,sys1790,sys3894,sys3622,mult_prx,sys4731,sys3586;
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
  char magaz[5];
} stl[3];/* art = 0, grp=1, tot=2 */

#include "Std\XlsFunc.c"

ovlcod()
{
  int16 curs=1,z,key;
  char choice;

  initload();
  FOREVER{
#if FLAGOLH
		z=520; scrget(2,z);
#else
    scrget(2,16);
#endif
		z=1;fasunlck(0);
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
    if(key==101 || key==111) break;
		fasunlck(-1);
    switch(choice){
      case '1': mode=VOLL;lijst();break;
      case '2': if(fldlen(6,33) && ovltest(267)) ovlexit(267); else errnum=12; break;
      case '3': if(ovltest(290)){mode=KPRX;lijst();} else errnum=12; break;
      case '4': mode=PRIX;lijst();break;
      case '5': mode=KBESTLST;lijst();break;
#if FLAGOLH
      case '6': if(ovltest(235)) ovlexit(235); else errnum=12; break;
#else
      case '6': if(ovltest(266)) ovlexit(266); else errnum=12; break;
#endif
      case '7': mode=STAT;lijst();break;
      case '8': if(fldlen(11,1)) lijst_AKfiches();break;
      case '9': if(ovltest(261)) ovlexit(261); else errnum=12; break;
 //     case 'F': fileout(); break;
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}

static statist()
{
  int16 j,k,key,z,ret=NO;

  j=0;
  for(k=0;k<4;k++){
    ak_vk_0[k]='\0';
    if(fldlen(6,53+k*2) || fldlen(6,54+k*2)) {ak_vk_0[k]='N';j++;}
  }
  if(j==0){
    errnum=12;goto endsr;
  }
  bew_only='J';
  FOREVER{
    scrget(2,13);z=1;scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrfld(z++,25,1);
    for(k=0;k<4;k++){
      if(ak_vk_0[k]) scrifld(z++,fm_uJN,&ak_vk_0[k]); else streepje(z++);
    }
    scrifld(z++,fm_uJN,&bew_only);
    key=scrupd(2,0x0481);
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    if(key==111) ovlexit(-1);
    if(key==101) goto endsr;
    if(key==108){
      for(k=0;k<4;k++) if(ak_vk_0[k]=='J') break;
      if(k!=4) break; else errnum=34;
    }
  }
  ret=YES;
  endsr:;
  return ret;
}

static lijst_AKfiches()
{
  int16 curs=1,key,fkey,z,j,k,curspos_,amode_,used_;
	uint16 last_krec_;
  char choice='A',OnlymetAKfiche='J';

  FOREVER{
    redo:
    scrget(2,327);   z=1;
		scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
		scraddpicto(2,0,72,22,4,2,573,0,0,"Maak XLS"); 
    scrifld(z++,fm_ALNGIP,&choice);
		scrifld(z++,fm_uJN,&OnlymetAKfiche);
    key=scrupd(curs,0x81);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) goto endsr;
    taal_nr=0;
    if(seldata.prx_klt && fldlen(2,24)) taal_nr=*s(2,24);
    if(fldlen(6,3+taal_nr)==0) taal_nr=0;
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    prt2xls=NO;if(key==5002){prt2xls=YES;key=108;}
		if(key==108){
      via_ind_inp=NO;
      switch(choice){
				case 'N' : fkey=1;break;
				case 'A' : fkey=2;break;
				default : fkey=0;via_ind_inp=YES;break;
      }
      drv_lev=0;drv_grp=1;
			if(fkey){
				if(ovlcall(2215,2)) goto endsr;
			}
			else{
				if(get_art()) goto endsr;
			}
			break;
    }

	}
	if(prt2xls){
		scrget(1,7);scrupd(-3,0);
		XlsRef=OpenXlsFile("Aankoopfiches",*u(25,2));
    if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsColumnSize(XlsRef,1,8);
		XlsColumnSize(XlsRef,2,35);
		XlsColumnSize(XlsRef,3,35);
	  XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,0,XlsKol++,0,"Code",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Naam",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Leverancier",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Ref.Lev.",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Vanaf",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Pr.Bruto",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"Pr.Netto",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"A/bak",0);
		XlsWrite(XlsRef,0,XlsKol++,0,"L.Aankoop",0);
		XlsRij++;
    goto no_header;
	}
	scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; 
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;

  prtfld(25,1,-1);
  prttext("<t33eb>Lijst aankoopfiches");
	prttext("<eb><t95>");  prtfld(25,2,-1);
  prttext("<t120>"); prttext("Blz.<ppp>.");
  prtbuf(1);

  z=1;
  prttab(z,6,2,1,-1); prttitle(z++,"Code",3);
  prttab(z,6,3,2,-1); prttitle(z++,"Omschrijving",3);
  prttab(z,1,3,1,20); prttitle(z++,"Leverancier",3);
  prttab(z,11,5,1,12); prttitle(z++,"Ref.lev.",3);
	prttab(z,11,8,1,-1); prttitle(z++,"Vanaf",3);
	prttab(z,11,6,1,-1); prttitle(z++,"Pr.Bruto",0x13);
	prttab(z,11,60,1,-1); prttitle(z++,"Pr.Netto",0x13);
  prttab(z,11,68,2,-1); prttitle(z++,"A/bak",0x13);
	prttab(z,11,63,2,-1); prttitle(z++,"L.Aankoop",0x13);
  prtbuf(3);

	no_header:;

  fasinit(6);cnt=0;free=999;
/* subtotaalbuffer op 0 zetten */
  if(fkey==0){
    for(k=0;k<DIM_TBE;k++){
      if(tbe[k].code[0]){
				fasinit(6);*pu_6_1=tbe[k].recnr;fasgeti(6);used_=NO;
				fasinit(11);*u(11,3)=*u(6,1);amode_=1;
				FOREVER{
					if(faskeyi(11,2,amode_)) break; amode_=2;
					if(*u(11,3)!=*u(6,1)) break;
					fasinit(1);*u(1,1)=*u(11,2);fasgeti(1);
					if(prt2xls){
						XlsKol=1;
						WriteFld2Xls(XlsRij,XlsKol++,6,2,0);
						WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
						WriteFld2Xls(XlsRij,XlsKol++,1,3,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,5,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,8,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,6,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,60,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,68,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,63,0);
						XlsRij++;
					}
					else{
  					k=1; if(used_) k=3;
	  				for(k;k<20;k++) prtinfo(k,0);nextline();
					}
					used_=YES;
				}
				if(used_==NO && OnlymetAKfiche!='J'){
					if(prt2xls){
						fasinit(11);fasinit(1);
						XlsKol=1;
						WriteFld2Xls(XlsRij,XlsKol++,6,2,0);
						WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
						WriteFld2Xls(XlsRij,XlsKol++,1,3,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,5,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,8,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,6,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,60,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,68,0);
						WriteFld2Xls(XlsRij,XlsKol++,11,63,0);
						XlsRij++;
					}
					else{
  					for(k=1;k<=2;k++) prtinfo(k,0); 
	  				nextline();
					}
				}
			}
		}
	}
	else{
		fasinit(6);
    FOREVER{
			next_a:;
      if(faskeyi(6,fkey,2)) break;
      if(DirCall_DRK2215_SelectArtikel()==NO) goto next_a;
			fasinit(11);*u(11,3)=*u(6,1);amode_=1;used_=NO;
			FOREVER{
				if(faskeyi(11,2,amode_)) break; amode_=2;
				if(*u(11,3)!=*u(6,1)) break;
				fasinit(1);*u(1,1)=*u(11,2);fasgeti(1);
				if(prt2xls){
					XlsKol=1;
					WriteFld2Xls(XlsRij,XlsKol++,6,2,0);
					WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
					WriteFld2Xls(XlsRij,XlsKol++,1,3,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,5,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,8,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,6,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,60,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,68,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,63,0);
					XlsRij++;
				}
				else{
  				k=1; if(used_) k=3;
	  			for(k;k<20;k++) prtinfo(k,0);nextline();
				}
				used_=YES;
			}
			if(used_==NO && OnlymetAKfiche!='J'){
				if(prt2xls){
					fasinit(11);fasinit(1);
					XlsKol=1;
					WriteFld2Xls(XlsRij,XlsKol++,6,2,0);
					WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
					WriteFld2Xls(XlsRij,XlsKol++,1,3,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,5,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,8,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,6,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,60,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,68,0);
					WriteFld2Xls(XlsRij,XlsKol++,11,63,0);
					XlsRij++;
				}
				else{
  				for(k=1;k<=2;k++) prtinfo(k,0); 
	  			nextline();
				}
			}
		}
	}
	if(prt2xls)	XlsClose(XlsRef,1);
  else prtclose();
	endsr:;
}

static lijst()
{
  int16 curs=1,key,z,j,k,curspos_,kmode_;
	uint16 last_krec_;
  char choice='A';

  taal_nr=0;prt2xls=NO;LijstDeelverpakkingen='N';
  if(mode==PRIX || mode==KBESTLST){
#if FLAGGRS
		choice='A';
#else
		choice='G';
#endif
    fasinit(2);*pu_2_1=seldata.prx_klt;fasgeti(2);
    copy(s(2,3),oldnm,fldlen(2,3));
  }
  if(dt_p_upd==0) dt_p_upd=*u(25,2);
  if(type_prx[0]=='\0') type_prx[0]='0';
  zero((char *)prx_str[0],sizeof prx_str);
  for(k=0;k<6;k++){
    if(type_prx[k]){
      j=type_prx[k]-'0'; copy(&vptekst[j*10],prx_str[k],6);
    }
  }
  if(sys4731 || acc_exist==NO) prt_acc='N';
  if(prt_acc=='\0' || bit(sys3760,5)==1) prt_acc='J';
  if(!acc_exist) prt_acc='N';
	prt_stock='N'; NettoArtStock=0;
  if(mode==STAT) if(!statist()) goto endsr;
  FOREVER{
    redo:
    if(mode==PRIX) scrget(2,17);
		else if(mode==KBESTLST) {scrget(2,281);scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0215A");}
    else scrget(2,15);
    z=1;
		scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
		if(mode==PRIX){
			scraddpicto(3,0,72,22,4,2,569,0,0,"Mail prijslijst"); 
			scraddpicto(2,0,68,22,4,2,573,0,0,"Maak XLS"); 
		  if(fldlen(2,124)) scraddpicto(4,0,64,22,4,2,604,0,0,"Mail prijslijst naar geselecteerde klanten"); 
		}
		if(mode==KBESTLST){
			scraddpicto(2,0,72,22,4,2,573,0,0,"Maak XLS"); 
		}
    scrifld(z++,fm_os20,pname[mode]);
    scrfld(z++,25,1);
    scrifld(z++,fm_ALNGIP,&choice);
		if(mode==VOLL || mode==KPRX){
			if(fldlen(6,102)) scrifld(z++,fm_uJN,&LijstDeelverpakkingen);
			else z++;
		}
    if(mode==KBESTLST){
      for(k=0;k<4;k++) scrifld(z++,fm_us75,std_txt[k]);
      scrfld(z++,2,3);
    }
    if(mode==PRIX){
      for(k=0;k<4;k++) scrifld(z++,fm_us75,std_txt[k]);
      scrfld(z++,2,3);
      if(mult_prx){
				for(k=0;k<6;k++){
					scrifld(-z,fm_u_09,&type_prx[k]); z++;
					scrifld(z++,fm_os6,prx_str[k]);
				}
      }
      else for(k=0;k<6;k++){streepje(z++);z++;}
      scrifld(z++,fm_uJN,&prt_nprx);
      scrifld(z++,fm_uJN,&prt_kkrt);
      if(acc_exist) scrifld(z++,fm_uJN,&prt_acc); else streepje(z++);
			if(fldlen(6,33) && fldlen(8,1)) scrifld(z++,fm_uJN,&prt_stock); else streepje(z++);
      scrifld(z++,fm_uJN,&apprx);
			if(fldlen(11,1)) scrifld(z++,fm_uJN,&prt_AKfiches); else streepje(z++);
      scrifld(z++,fm_udat,&dt_p_upd);scrifld(z++,fm_uJN,&p_np_bld);
      scrifld(z++,fm_uJN,&prt_wpct);
      scrifld(z++,fm_uu3,&wpct_beg);scrifld(z++,fm_uu3,&wpct_end);
    }
    key=scrupd(curs,0x0481);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(mode==PRIX || mode==KBESTLST){
      if(cmpstr(s(2,3),oldnm,fldlen(2,3))){
				if(*s(2,3)){
					if(search(2,0)) {curs=8;goto redo;}
				}
				else fasinit(2);
				copy(s(2,3),oldnm,fldlen(2,3));
				seldata.prx_klt=*pu_2_1;
      }
      zero(prx_str[0],sizeof prx_str);
      for(k=0;k<6;k++){
				if(type_prx[k]){
					j=type_prx[k]-'0'; 
					if(fldlen(6,PrNrs[j])==0){errnum=34;curs=curspos_; goto redo;}
					copy(&vptekst[j*10],prx_str[k],6);
				}
      }
      if(key==18){curs=curspos_+1; goto redo;}
    }
    if(seldata.prx_klt) q_prx2prt=1;
    else{
      q_prx2prt=0; for(k=0;k<6;k++) if(type_prx[k]) q_prx2prt++;
    }
    taal_nr=0;
    if(seldata.prx_klt && fldlen(2,24)) taal_nr=*s(2,24);
    if(fldlen(6,3+taal_nr)==0) taal_nr=0;
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    prt2xls=NO;if(key==5002){prt2xls=YES;key=108;}
		if(key==108 || key==5003){
			FlagMailPrijsOpslag=NO;
			if(key==5003){
			  if(AskMailOpties(NO)==NO) goto redo;
				prt2pdf=2;
			}
      via_ind_inp=NO;
      switch(choice){
				case 'N' : key=1;break;
				case 'A' : key=2;break;
				case 'P' : key=6;break;
				case 'L' : key=90;break;
				case 'G' : key=91;break;
				default : key=0;via_ind_inp=YES;break;
      }
      drv_lev=0;drv_grp=1;
      execute(key);
			if(prt2pdf==2) MailDocument(0);
			break;
    }
		else if(mode==PRIX && key==5004){ // automatisch mailen van prijsopslag
			FlagMailPrijsOpslag=YES; 
      via_ind_inp=NO;
      switch(choice){
				case 'N' : key=1;break;
				case 'A' : key=2;break;
				case 'P' : key=6;break;
				case 'L' : key=90;break;
				case 'G' : key=91;break;
				default : key=0;via_ind_inp=YES;break;
      }
			if(AskMailOpties(YES)==NO) goto redo;
  	  seldata.selp_use=NO;
			if(key){
				if(ovlcall(2215,2)) break;
			}
			else{
				if(get_art()) break;
			}
			fasinit(2); prt2pdf=2; kmode_=1; last_krec_=0;
			FOREVER{
				next_klt:;
				if(faskeyi(2,2,kmode_)) break; kmode_=2;
				if(fldlen(2,200) && *u(2,200)) goto next_klt;
				last_krec_=*u(2,1);
				if(*s(2,21) && *s(2,124)=='J'){
					if(ConfirmKlant=='J'){
						k=ExecConfirmKlant();
						if(k==-1) break;
						if(k==0) goto next_klt;
					}
					seldata.prx_klt=*u(2,1);
					if(MailSelectOnlyOwnArt=='J'){seldata.inq_klt=*u(2,1); seldata.klt_st_used=YES;}
					drv_lev=0;drv_grp=1; prt2pdf=2;
					execute(key);
					if(SpoolFileNr>0){ // enkel indien artikels
						_sleep(4000); // 4 seconden wachten owv problemen overlast
						FOREVER{
							if(MailDocument(1))break;
							if(DisplayWarning("Mailen NIET gelukt! Nogmaals proberen?",605,1)==NO) goto endsr;
						}
					}
					fasinit(2);*u(2,1)=last_krec_;fasgeti(2); // uit veiligheid
				}
			}
			seldata.prx_klt=0;seldata.inq_klt=0; seldata.klt_st_used=NO;fasinit(2);
    }
  }
  endsr:;
}

static AskMailOpties(mailinglist)
int16 mailinglist;
{
	int z,key,k;

	if(ConfirmKlant=='\0') ConfirmKlant='J'; 
	if(MailSelectOnlyOwnArt=='\0')MailSelectOnlyOwnArt='J';
	if(MailTemplate[0]=='\0') sysget(18244,5,MailTemplate); // default uit parameters 
	FOREVER{
		scrget(2,359); z=1;
		for(k=0;k<5;k++) scrifld(z++,fm_us75,MailBodyText[k]);
		scrifld(z++,fm_udat,&dt_p_upd);
//		scrifld(z++,fm_udat,&seldata.dt_p_beg);scrifld(z++,fm_udat,&seldata.dt_p_end);
		if(mailinglist){
			scrifld(z++,fm_uJN,&MailSelectOnlyOwnArt);
			scrifld(z++,fm_uJN,&ConfirmKlant);
		} else{scrifld(z++,fm_os1,"-");scrifld(z++,fm_os1,"-");}
		scrifld(z++,fm_us5U,MailTemplate);
		key=scrupd(1,0x81);
		if(key==101) return NO;
		if(key==108) break;
	}
	return YES;
}

static ExecConfirmKlant()
{
	int key;

	FOREVER{
		redo:;
		scrget(2,360);
		scrofld(1,2,3,-1);
		scrofld(2,2,4,-1);
		scrofld(3,2,5,-1);scrofld(4,2,6,-1);
		scrfld(5,2,21);
		key=scrupd(5,0x119);
		if(key==101) return -1;
		if(key==105) return NO;
//		if(CheckEmailAdres(s(2,21),fldlen(2,21),NO)==false){errnum=38; goto redo;}
		if(key==104) break;
		if(key==109){ConfirmKlant='N';break;}
	}
	return YES;
}
   
static execute(fkey)
int16 fkey;
{
  int16 g,j,k,key=0,m,z,base_z,char_line,len_,kk_mode,nr_,lijsttaalnr_,mode15_,v_used_;
  uint16 date_,drv_mode_,firsttime,akey_,MastArtRec_;
  char txt_[50];
  flag skipflag,opm_used_=NO;

	stockwt=0;FlagSortViaGroep=NO;
	if(!FlagMailPrijsOpslag){
		seldata.selp_use=NO;
		if(fkey){
			if(mode==PRIX || mode==KBESTLST) {
			  if(ovlcall(2215,2)) goto endsr;
			}
			else{
				if(ovlcall(2215,0)) goto endsr;
			}
		}
		else{
			if(get_art()) goto endsr;
			fkey=SortKey;
		}
	}
	lijsttaalnr_=0;
  if(seldata.prx_klt && fldlen(2,24)) lijsttaalnr_=*s(2,24);
  zz_prx=1; opm_used_=NO;
  zero(fld_attr,sizeof fld_attr);

	if(mode==PRIX && prt2xls){
		scrget(1,7);scrupd(-3,0);
		zero(txt_,sizeof txt_);
		k=copy0("Prijslijst",txt_,20);
		if(seldata.prx_klt) {txt_[k++]=' ';copy0(s(2,3),&txt_[k],20);}
		XlsRef=OpenXlsFile(txt_,dt_p_upd);
    if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsRij=1;XlsKol=1;
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,0,0,NO,NO);
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		pline2xls(1);XlsRij++;
	  goto no_hdr;
	}

  scrget(1,6);scrupd(-3,0);
  k=12;j=4;char_line=132;

  if(mode==PRIX && apprx!='J' && prt_nprx!='J' && prt_kkrt!='J'){
    if(seldata.prx_klt || q_prx2prt<4) char_line=96;
  }
#if FLAGEET  || FLAGGBL
	char_line=132; // steeds 132 char
#endif
  if(mode==KBESTLST){
		PrintKlantBestelFormulier(fkey); goto endsr;
    k=12;j=4;char_line=80;
  }
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,char_line,pr_mode,j))!=0) goto endsr;

  if((sys3760 & 0x400)==0 || mode!=PRIX) prtfld(25,1,-1);
  prttext("<t33eb>");

  if(mode==PRIX && lijsttaalnr_==1) prttext("Liste des prix");
	else if(mode==VOLL && LijstDeelverpakkingen=='J') prttext("Lijst deelverpakkingen");
	else prttext(pname[mode]);
  if(char_line==132) prttext("<eb><t95>");
  else{
    if(mode!=PRIX || seldata.prx_klt==0) prttext("<eb><t62>");
    else{
     prttext("<eb><t55>T");prtfld(2,26,-1);
     prttext("<t62>");
    }
  }
  prtfld(25,2,-1);
  if(char_line==132) prttext("<t120>");
  else prttext("<t88>");
  prttext("Blz.<ppp>.");
  prtbuf(1);
  
  if(mode==PRIX){
    if(seldata.prx_klt){
      if(mode==PRIX){
				if(lijsttaalnr_==1) prttext("<be>Liste des prix : "); else prttext("<be>Prijslijst : ");
			}
      else prttext("<be>             ");
      prtfld(2,3,-1);prttext("<be>");nextline();
      prttext("<be>             ");prtfld(2,4,-1);prttext("<be>");nextline();
      prttext("<be>             ");prtfld(2,5,-1);
      prttext("  ");prtfld(2,6,-1);prttext("<be>");nextline(); nextline();
      opm_used_=YES;
    }
    j=0;
    for(k=0;k<4;k++){
      if(std_txt[k][0]){prtifld(fm_us75,std_txt[k],-1);nextline();j++;}
    }
    if(j){nextline(); opm_used_=YES;}
  }
  redo_hdr:;
  z=1;
  prttab(z,6,arcd+1,1,-1);prttitle(z++,"Code",3);
  sysget(3584,2,&k);
#if FLAGJAC
	len_=-1;
#else
  len_=30;
#endif
  prttab(z,6,3,1,len_);if(lijsttaalnr_==1) prttitle(z++,"Description",3); else prttitle(z++,"Naam",3);
#if !FLAGLOY
  if(mode==PRIX || mode==KPRX) {
    prttab(z,6,10,1,-1); if(lijsttaalnr_==1) prttitle(z++,"Un",3); else prttitle(z++,"Eh",3);
  }
#endif
  if(mode!=PRIX && mode!=KPRX){
    len_=10;
    if(sys3760 & 1){
      prttab(z,6,8,0,-1);prttitle(z++,"Code",3);
      len_=7;
    }
    prttab(z,1,3,1,len_);prttitle(z++,"Lever.",3);
  }
  if(mode!=KPRX) {
#if FLAGLOY
    prttab(z,6,31,1,-1); prttitle(z++,"A/vp",0x13);
    prttab(z,6,10,1,-1); prttitle(z++,"",0x13);
#else
    prttab(z,6,9,1,-1); prttitle(z++,"Gr",0x13);
#endif
    prttab(z,6,28,1,-1); if(lijsttaalnr_==1) prttitle(z++,"TVA%",0x13); else prttitle(z++,"BTW%",0x13);
  }
  if(mode!=PRIX && mode!=KPRX){
    if(fldlen(6,18)){prttab(z,6,18,0,-1);prttitle(z++,"AP-net",0x13);}
    else{prttab(z,6,12,0,-1); prttitle(z++,"A.P.",0x13);}
    if(sys3724==NO){
      prttab(z,6,21,1,-1); prttitle(z++,"V.P.",0x13);
    }
    if(mode<STAT){
#if FLAGOLH
      prttab(z,6,33,0,-1); prttitle(z++,"Stock",0x13);
      prtitab(z,fm_od62_,&stockw,1,-1); prttitle(z++,"Waarde",0x13);
      prttab(z,6,46,1,-1); prttitle(z++,"AKdatum",3);
      prttab(z,6,57,1,-1); prttitle(z++,"Verk.",0x13);
			prttab(z,6,48,1,-1); prttitle(z++,"VKdatum",3);

#else
#if FLAGLOY
      prttab(z,6,38,1,-1); prttitle(z++,"Gewicht",0x13);
      prttab(z,6,65,1,-1); prttitle(z++,"FP",0x13);
#else
      prttab(z,6,31,2,-1); if(sys4731) prttitle(z++,"A/krt",0x13); else prttitle(z++,"A/bak",0x13);
      prttab(z,6,37,1,-1); prttitle(z++,"Inhoud",0x13);
      prttab(z,6,38,1,-1); prttitle(z++,"Gewicht",0x13);
#endif
      prttab(z,6,39,1,-1); prttitle(z++,"E",0x13);
      prttab(z,6,40,1,-1); prttitle(z++,"VK-reken",3);

      prttab(z,6,29,1,-1); prttitle(z++,"Mag.",3);
      prttab(z,6,33,0,-1); prttitle(z++,"Stock",0x13);
      prttab(z,6,36,0,-1); prttitle(z++,"M.stock",0x13);
#endif
    }
    if(mode==STAT){
      base_z=z;
      copy("xk.xx",txt_,8);
      for(k=0;k<4;k++){
				if(ak_vk_0[k]=='J'){
					if(k<2) txt_[0]='A'; else txt_[0]='V';
					if(fldlen(6,53+k*2)){
						copy("St",&txt_[3],4);
						prttab(z,6,53+k*2,0,-1); prttitle(z++,txt_,0x13);
					}
					if(fldlen(6,54+k*2)){
						copy(def_munt,&txt_[3],4);
						prttab(z,6,54+k*2,0,-1); prttitle(z++,txt_,0x13);
					}
				}
      }
    }
  }
  if(mode==PRIX){
    lg_fles=NO;
    zz_prx=z;
    if(apprx=='J'){
      for(k=0;k<7;k++){
				if(fldlen(6,12+k)){
					prttab(z,6,12+k,1,-1);
					if(bit(sys3760,8)==1) prttitle(z++," ",0x13);
					else switch(k+12){
						case 12 : prttitle(z++,"AP-bruto",0x13);break;
						case 13 : prttitle(z++,"Mnt",0x13);break;
						case 14 :
						case 15 :
						case 16 : prttitle(z++,"K%",0x13);break;
						case 17 : prttitle(z++,"K.bd.",0x13);break;
						case 18 : prttitle(z++,"AP-netto",0x13);break;
						default : prttitle(z++," ",0x13);break;
					}
				}
      }
    }
#if FLAGEET || FLAGGBL // specifieke prijslijst 
    if(q_prx2prt>1){/* SPECIFIEK */
      for(k=0;k<6;k++){
				if(type_prx[k]){
					prx_nr=type_prx[k]-'0';
					if(fldlen(6,PrNrs[prx_nr])){
						prttab(z,6,PrNrs[prx_nr],1,-1); prttitle(z++,&vptekst[prx_nr*10],0x13);
					}
				}
      }
      if(/* sys4731==0 &&*/ prt_acc=='J' && acc_exist && q_prx2prt>1){
				prttab(z,6,30,0,-1);
				 if(bit(sys3760,5)==1) prttitle(z++,"Accijns",0x13);
				else prttitle(z++,"Acc.inb",0x13);
      }
      if(lgg_exist && q_prx2prt>0){
				prtitab(z,fm_uf5_2,&bd_leeg,0,-1); prttitle(z++,"Leegg.",0x13);
      }
      prx_nr=0;
    }
    else{
      if(seldata.inq_klt) prx_nr=*s(2,26)-'0';
      else prx_nr=type_prx[0]-'0';
      if(prx_nr<0 || prx_nr>9) prx_nr=0;
      fmt_get(6,PrNrs[prx_nr]);
      for(k=0;k<6;k++){
#if FLAGGBL
				if(k==3) continue; // geen btw
#endif
				prtitab(z,fmt,&prt_bd[k],1,-1);
				switch(k){
#if FLAGGBL
					case 0 : prttitle(z++,"Basis",0x13);break;
#else 
					case 0 : prttitle(z++,"Exc.acc.",0x13);break;
#endif
					case 1 : prttitle(z++,"Accijns",0x13);break;
					case 2 : prttitle(z++,"Inc.acc",0x13);break;
					case 3 : prttitle(z++,"BTW",0x13);break;
					case 4 : prttitle(z++,"Inc.BTW",0x13);break;
					default: prttitle(z++,"Leegg.",0x13);break;
				}
				if(k==1 && prt_kkrt=='J'){prtitab(z,fm_os10,krt_str,0,-1); prttitle(z++,"Korting",0x3);}
      }

      if(prt_wpct=='J'){
				prtitab(z,fm_uf5_2,&w_pct,1,-1);prttitle(z++,"W%",0x13);
				if(bit(sys3760,3)==1){
					prtitab(z,fm_uf5_2,&w_bedrag,1,-1);prttitle(z++,"W.bedr.",0x13);
				}
      }
    }
#else  // hier volgt de standaard  

    if(q_prx2prt>1){
      if(prt_acc=='J' && bit(sys3760,5)==1 && acc_exist){
				prttab(z,6,30,0,-1); if(lijsttaalnr_==1) prttitle(z++,"Acc.",0x13); else prttitle(z++,"Accijns",0x13);/* vp = excl acc */
      }
      for(k=0;k<6;k++){
				if(type_prx[k]){
					prx_nr=type_prx[k]-'0';
					if(fldlen(6,PrNrs[prx_nr])){
						prttab(z,6,PrNrs[prx_nr],0,-1); prttitle(z++,&vptekst[prx_nr*10],0x13);
					}
				}																							
      }
      prx_nr=0;
    }
    else if(q_prx2prt==1){
      if(seldata.prx_klt) prx_nr=*s(2,26)-'0';
      else prx_nr=type_prx[0]-'0';
      if(prx_nr<0 || prx_nr>9) prx_nr=0;
      if(stuksprx[prx_nr]=='J') lg_fles=YES;
      fmt_get(6,PrNrs[prx_nr]);
      if(seldata.prx_klt){
				if(prt_nprx=='J'){
					prtitab(z,fmt,&vp_norm,1,-1); if(lijsttaalnr_==1) prttitle(z++,"Normal",0x13); else prttitle(z++,"Normaal",0x13);
					if(bit(sys3760,4)==1 && bit(sys3894,prx_nr)==0){
						fld_attr[z]=2;
						prtitab(z,fmt,&vp_inorm,1,-1); prttitle(z++,"Norm.Inc",0x13);
					}
				}
				if(prt_kkrt=='J'){prtitab(z,fm_os10,krt_str,0,-1); if(lijsttaalnr_==1) prttitle(z++,"Rist.",0x13); else prttitle(z++,"Korting",0x3);}
			}
			if(prt_acc=='J' && (bit(sys3760,5)==1  || (fldlen(2,88)==1 && *s(2,88)=='J')) && acc_exist){
				prttab(z,6,30,0,-1); if(lijsttaalnr_==1) prttitle(z++,"Acc.",0x13); else prttitle(z++,"Accijns",0x13);/* vp = excl acc */
      }

      if(bit(sys3894,prx_nr)==0 || seldata.prx_klt){
				prtitab(z,fmt,&vp_exc,0,-1);
				if(seldata.prx_klt) {if(lijsttaalnr_==1) prttitle(z++,"Exc.TVA",0x13); else prttitle(z++,"Exc.BTW",0x13);}
				else prttitle(z++,&vptekst[prx_nr*10],0x13);
				if((sys3760 & 0x0200)==0){
					if(bit(sys3760,4)==1) fld_attr[z]=2;
					prtitab(z,fmt,&vp_inc,0,-1); if(lijsttaalnr_==1) prttitle(z++,"Inc.TVA",0x13); else prttitle(z++,"Inc.BTW",0x13);
				}
      }
      else {
				prtitab(z,fmt,&vp_inc,0,-1);
				if(seldata.prx_klt) {if(lijsttaalnr_==1) prttitle(z++,"Inc.TVA",0x13); else prttitle(z++,"Inc.BTW",0x13);}
				else prttitle(z++,&vptekst[prx_nr*10],0x13);
      }
      if((bit(sys3760,3)==1 && apprx=='J') || prt_wpct=='J'){
				prtitab(z,fm_uf5_2,&w_pct,1,-1);prttitle(z++,"W%",0x13);
				if(bit(sys3760,3)==1){
					prtitab(z,fm_uf5_2,&w_bedrag,1,-1);prttitle(z++,"W.bedr.",0x13);
				}
      }
    }
    if(prt_acc=='J' && bit(sys3760,5)==0 && (fldlen(2,88)!=1 || *s(2,88)!='J') && acc_exist && q_prx2prt>0){
      prttab(z,6,30,2,-1); if(lijsttaalnr_==1) prttitle(z++,"Acc.inc",0x13); else prttitle(z++,"Acc.inb",0x13);
#if FLAGWLM
			prttab(z,6,87,1,-1); prttitle(z++,"Gr/plato",0x13); 
#endif
    }
    if(lgg_exist && q_prx2prt>0){
      prtitab(z,fm_uf5_2,&bd_leeg,0,-1); if(lijsttaalnr_==1) prttitle(z++,"Vidange",0x13); else prttitle(z++,"Leegg.",0x13);
    }
		if(prt_stock=='J'){prtitab(z,fm_uf5_2,&NettoArtStock,0,-1); prttitle(z++,"Stock",0x13);}
#endif
	}
  if(mode==KPRX){
    prttab(z,6,31,1,-1);prttitle(z++,"St/vp",0x13);
    zz_prx=z;

    j=0;
    for(k=0;k<6;k++){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])) j++;
    }

    for(k=0;k<j;k++){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
				prtitab(z,fm_uf6_2,&vp_kas[nr_],1,-1);
				if(k==0) prttitle(z++,"Kassa BAK",0x13);
				else if(k==j-1) prttitle(z++,"Kassa STK",0x13);
				else{
					zero(txt_,sizeof txt_);
					txt_[0]='H'; txt_[1]='0'+k; txt_[2]=':';
					copy(&vptekst[nr_*10],&txt_[3],6);
					prttitle(z++,txt_,0x13);
				}
      }
    }
    if(lgg_exist){
      prtitab(z,fm_uf6_2,&p_lg_bak,1,-1);prttitle(z++,"Lg bak",0x13);
    }
    if(lgg_exist){
      prtitab(z,fm_uf6_2,&p_lg_stk,1,-1);prttitle(z++,"Lg stk",0x13);
    }
  }
  if(mode==PRIX && opm_used_){/* nodig om TITELlijn lager te krijgen */
    prtbuf(0); prttext(GetPtrInfo()); nextline(); opm_used_=NO; goto redo_hdr;
  }
  prtbuf(3);
  if(mode==STAT){
    z=base_z;
    for(k=0;k<4;k++){
      if(ak_vk_0[k]=='J'){
				sysget(3710+k*2,2,&date_);
				if(date_){
					jddate(date_,&j,&m,&g);
					stcli_d(&txt_[0],(long)g,2,0);
					stcli_d(&txt_[2],(long)m,2,0);
					stcli_d(&txt_[4],(long)j%100,2,0);
					txt_[6]='\0';
				}
				else txt_[0]='\0';
				if(fldlen(6,53+k*2)){
					prttitle(z++,txt_,0x10);
				}
				if(fldlen(6,54+k*2)){
					prttitle(z++,txt_,0x10);
				}
      }
    }
    nextline();nextline();
  }
	zero(txt_,sizeof txt_);	k=copy0(pname[mode],txt_,30);
	if(mode==PRIX){
		if(seldata.prx_klt) {txt_[k++]=' ';copy0(s(2,3),&txt_[k],20);}
	}
  p_pdfname(txt_,0,0);
  
 
  no_hdr:;

  fasinit(6);cnt=0;free=999;
/* subtotaalbuffer op 0 zetten */
  for(k=0;k<sizeof tot_buf;k++) tot_buf[k]='\0';
  kk_mode=2;
	if(via_ind_inp) fkey=SortKey;
  if(fkey==0){
    for(k=0;k<DIM_TBE;k++){
      if(tbe[k].code[0]){
				fasinit(6);*pu_6_1=tbe[k].recnr;fasgeti(6);
				ind_prx=tbe[k].vp_prx;
#if FLAGEET || FLAGGBL
				if(mode==PRIX && q_prx2prt<=1 && prt2xls==NO){         // speciale afdruk voor EET
					p_EET_line();
				}
				else p_line();
#else
				p_line();
#endif
      }
    }
    zero((char *)&tbe[0].recnr,sizeof tbe);
  }
  else if(fkey<90){
    FOREVER{
      if(faskeyi(6,fkey,kk_mode)) break;
      kk_mode=2;
      if(accept(mode) && (via_ind_inp || DirCall_DRK2215_SelectArtikel())){
				if((mode==VOLL || mode==KPRX) && LijstDeelverpakkingen=='J'){
					if(*u(6,102)==0){
						MastArtRec_=*u(6,1);
						fasinit(6);*u(6,102)=MastArtRec_;mode15_=1; v_used_=0;
      			FOREVER{
			      	if(faskeyi(6,15,mode15_)) break; mode15_=2;
				      if(*u(6,102)!=MastArtRec_) break;
							p_line(); v_used_++;
						}
						fasinit(6);*u(6,1)=MastArtRec_;fasgeti(6);
						if(v_used_){
							prttext("<b>");p_line();nextline();
						}
					}
				}
				else{
#if FLAGEET || FLAGGBL
  				if(mode==PRIX && q_prx2prt<=1 && prt2xls==NO){         // speciale afdruk voor EET
	  				p_EET_line();
		  		}
			  	else p_line();
#else
				  p_line();
#endif
				}
			}
    }
  }
  else {
    fasinit(6);
    if(fkey==90) akey_=4;
    else{
      akey_=2; if(faskeyi(6,5,1)==0) akey_=5;/* toch rechtstreekse key */
    }
    drv_mode_=1;
    zero(grp_used,sizeof grp_used);
    FOREVER{
      if(next_drv(fkey,drv_mode_)) break; drv_mode_=2;
      fasinit(6); firsttime=YES; kk_mode=1;
      if(fkey==90) *u(6,7)=drv_lev;
      else if(fkey==91) *u(6,9)=drv_grp;
      FOREVER{
				next_art:;
				if(faskeyi(6,akey_,kk_mode)) break; kk_mode=2;
				if(fkey==90){
					if(*u(6,7)!=drv_lev) break;
				}
				else{
					grp_used[*i(6,9)]=1;
					if(*i(6,9)!=drv_grp){
						if(akey_==5) break; else goto next_art;
					}
				}
				if((mode==VOLL || mode==KPRX) && LijstDeelverpakkingen=='J' && *u(6,102)) goto next_art;
				if(accept(mode)==NO) goto next_art;
				if(via_ind_inp==NO && DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
				if(firsttime){
					if(prt2xls==NO){
						if(free<6) prtform(0);
						nextline();
						prttext("<eb>");
						if(fkey==90){
							prtfld(1,1+lvcd,-1);prttext("  ");prtfld(1,3,30);
							if(mode!=PRIX){
								prttext("<e> Telefoon : ");prtfld(1,8,-1);
								if(fldlen(1,9)){prttext("  Fax : ");prtfld(1,9,-1);}
								prttext("<e>");
							}
						}
						else {
							prtfld(52,1,-1);prttext("  ");prtfld(52,14,-1);
						}
						prttext("<eb>");
						nextline(); nextline(); 
					}
					firsttime=NO;
				}

				if((mode==VOLL || mode==KPRX) && LijstDeelverpakkingen=='J'){
					if(*u(6,102)==0){
						MastArtRec_=*u(6,1);
						fasinit(6);*u(6,102)=MastArtRec_;mode15_=1; v_used_=0;
      			FOREVER{
			      	if(faskeyi(6,15,mode15_)) break; mode15_=2;
				      if(*u(6,102)!=MastArtRec_) break;
							p_line(); v_used_++;
						}
						fasinit(6);*u(6,1)=MastArtRec_;fasgeti(6);
						if(v_used_){
							prttext("<b>");p_line();nextline();
						}
					}
				}
				else{
#if FLAGEET || FLAGGBL
   				if(mode==PRIX && q_prx2prt<=1 && prt2xls==NO){         // speciale afdruk voor EET
		  			p_EET_line();
			  	}
				  else p_line();
#else
				  p_line();
#endif
				}
      }
    }
  }
	if(prt2xls){
		if(cnt) XlsClose(XlsRef,1);
	}
	else{
		skipflag=YES;
		zero((char *)&vp_kas[0],sizeof vp_kas);p_lg_bak=0;p_lg_stk=0;
		vp_inc=0;vp_exc=0;
		fasinit(1);fasinit(6);
		copy_total();
		if(cnt){
			if(mode!=PRIX){
				nextline();skipflag=NO;
#if FLAGOLH
				stockw=stockwt;
#endif
				for(k=5;k<20;k++) prtinfo(k,2);nextline();/* totalen */
			}
			if(skipflag) nextline();
			if(seldata.prx_klt==0){
				prttext("*** Aantal fiches :"); *pu_6_1=cnt; prtfld(6,1,-1);
				nextline();
			}
			SpoolFileNr=prtclose();
		}
		else {prtclose();SpoolFileNr=0;} // om GEEN automatische mail te sturen
	}
  endsr:;
  if(key==111) ovlexit(-1);
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

static PrintKlantBestelFormulier(fkey)
int16 fkey;
{
	uint16 tb_artrecs[7500],max_art,rec_,SomRijBeg,SomRijEnd,RijSubtotaal,kol_aantal_,kol_code_;
	int16 k,n,kk_mode,lijsttaalnr_,taal_off_,start_,q_per_page;
  uint16 drv_mode_,firsttime,akey_;
	int16 StylHidden, StylFill, StylFillCt, StylTotSum, StylTotTxt, StylGrpTxt, StylCusInf, StylNormal, StylNormalCt;
  char txt_[100];
  

//	if(fkey==0){FlagSortViaGroep=YES; fkey=91;}   // individueel toch volgens groep afdrukken 

	lijsttaalnr_=0;
  if(seldata.prx_klt && fldlen(2,24)) lijsttaalnr_=*s(2,24);  
	zero((char *)&tb_artrecs[0],sizeof tb_artrecs);max_art=0;
	fasinit(6);cnt=0;free=999;
/* subtotaalbuffer op 0 zetten */
  kk_mode=2;
  if(fkey==0){
    for(k=0;k<DIM_TBE;k++){
      if(tbe[k].code[0]) tb_artrecs[max_art++]=tbe[k].recnr;
    }
  }
  else if(fkey<90){
    FOREVER{
      if(faskeyi(6,fkey,kk_mode)) break; kk_mode=2;
			if(*i(6,9)!=99 && accept(mode) && (via_ind_inp || DirCall_DRK2215_SelectArtikel())) tb_artrecs[max_art++]=*u(6,1);
			if(max_art>=7500) break;
    }
  }
  else {
    fasinit(6);
    if(fkey==90) akey_=4;
    else{
      akey_=2; if(faskeyi(6,5,1)==0) akey_=5;/* toch rechtstreekse key */
    }
    drv_mode_=1;
    zero(grp_used,sizeof grp_used);
    FOREVER{
      if(next_drv(fkey,drv_mode_)) break; drv_mode_=2;
      fasinit(6); firsttime=YES; kk_mode=1;
      if(fkey==90) *u(6,7)=drv_lev;
      else if(fkey==91) *u(6,9)=drv_grp;
      FOREVER{
				next_art:;
				if(faskeyi(6,akey_,kk_mode)) break; kk_mode=2;
				if(*i(6,9)==99) goto next_art; // geen leeggoed 
				if(fkey==90){
					if(*u(6,7)!=drv_lev) break;
				}
				else{
					grp_used[*i(6,9)]=1;
					if(*i(6,9)!=drv_grp){
						if(akey_==5) break; else goto next_art;
					}
				}
				if(FlagSortViaGroep){
					for(k=0;k<DIM_TBE;k++) if(tbe[k].recnr==*u(6,1)) break;
					if(k>=DIM_TBE) goto next_art;
		    }
				else{
  				if(accept(mode)==NO) goto next_art;
	  			if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
				}
				if(firsttime){
					if(fkey==90) tb_artrecs[max_art++]=*u(1,1)+30000;
					else tb_artrecs[max_art++]=*u(52,1)+60000;
					firsttime=NO;
				}
				tb_artrecs[max_art++]=*u(6,1);
				if(max_art>=7500) break;
      }
    }
  }

	if(max_art==0) goto endsr;

	if(prt2xls){
		scrget(1,7);scrupd(-3,0);
		zero(txt_,sizeof txt_);
		if(lijsttaalnr_==1) k=copy0("Bon de commande ",&txt_[0],30);
#if FLAGHOE
		else k=copy0("Drankenlijst ",&txt_[0],30);
#else
		else k=copy0("Bestelformulier ",&txt_[0],30);
#endif
		k+=copy0(s(2,3),&txt_[k],30); for(n=0;n<k;n++) if(txt_[n]=='/') txt_[n]=' ';
		XlsRef=OpenXlsFile(txt_,*u(25,2));
    if(XlsRef<=0) {errnum=1;goto endsr;}
		zero(txt_,sizeof txt_);
		if(lijsttaalnr_==1) k=copy0("Bon de commande",&txt_[0],30);
#if FLAGHOE
		else k=copy0("Drankenlijst",&txt_[0],30);
#else
		else k=copy0("Bestelformulier",&txt_[0],30);
#endif
		XlsSelectWorkSheet(XlsRef,1,txt_); XlsStyle(XlsRef,"PORTRAIT",0,0,NO,NO,NO,0,0,0,0,0,0,NO,NO); // Afdruk in PORTRAIT mode (met JMS versie 53 of hoger
		kol_aantal_=4; kol_code_=1;
#if FLAGWYN // kolom aantal / code verwisseld 
    kol_aantal_=1; kol_code_=4;
#endif
	  XlsColumnSize(XlsRef,kol_code_,8);
		XlsColumnSize(XlsRef,2,50);
		XlsColumnSize(XlsRef,3,10);
		XlsColumnSize(XlsRef,kol_aantal_,10);
		// Styles
		StylHidden=XlsStyle(XlsRef,"",5,KLEUR_WIT,YES,NO,NO,1,0,KLEUR_WIT,1,0,0,YES,YES);
		StylFill  =XlsStyle(XlsRef,"",12,0x00,NO,NO,NO,1,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylFillCt=XlsStyle(XlsRef,"",12,0x00,NO,NO,NO,2,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylTotSum=XlsStyle(XlsRef,"0;-0;;@",12,0xFFFFFF,NO,NO,NO,2,0,KLEUR_DONKERGROEN,1,0,0,YES,NO);
		StylTotTxt=XlsStyle(XlsRef,"",12,0xFFFFFF,YES,NO,NO,2,0,0x00,1,0,0,YES,NO);
		StylGrpTxt=XlsStyle(XlsRef,"",12,0x00,YES,NO,NO,2,0,KLEUR_BEIGE,1,0,0,YES,NO);
		StylCusInf=XlsStyle(XlsRef,"",12,0x00,YES,NO,NO,1,0,KLEUR_LICHTBLAUW,1,0,0,YES,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,1,0,KLEUR_WIT,1,1,0,YES,NO);
		StylNormalCt=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,2,0,KLEUR_WIT,1,1,0,YES,NO);

		XlsRij=1;XlsKol=1;
//XlsStyle(ref, char *NumFormat,Size, long /*COLORREF*/ Color, BoldFlag, ItalicFlag, UnderlineFlag,HorAlignment, VerAlignment,
//	long /*COLORREF*/ BackCol, int16 Pattern, Kader, KaderCol, Lock, Hide)
		XlsStyle(XlsRef,"",5,KLEUR_WIT,YES,NO,NO,1,0,KLEUR_WIT,1,0,0,YES,YES);
		zero(txt_,sizeof txt_);copy("**0101",txt_,6);stcli_d(&txt_[6],(long)(*u(2,1)),5,0);copy("**",&txt_[11],2);
		XlsWrite(XlsRef,XlsRij,1,0,txt_,StylHidden); // soort document + klantrecord hidden
    
		WriteFld2Xls(XlsRij++,2,2,3,StylCusInf);
		WriteFld2Xls(XlsRij++,2,2,4,StylCusInf);
		zero(txt_,sizeof txt_);k=copy0(s(2,5),txt_,6);txt_[k++]=' ';copy0(s(2,6),&txt_[k],fldlen(2,6));
		XlsWrite(XlsRef,XlsRij++,2,0,txt_,StylCusInf); 
	//	XlsRij++;
		
	//	if(tb_artrecs[0]<3000) XlsRij++;

		SomRijBeg=0;SomRijEnd=0; RijSubtotaal=0;
	  for(n=0;n<max_art;n++){
			rec_=tb_artrecs[n];
			if(rec_>60000){
				if(SomRijBeg && RijSubtotaal){
			    zero(txt_,sizeof txt_);	sprintf(txt_,"=SUM(R%dC4:R%dC%d)",SomRijBeg,SomRijEnd,kol_aantal_); 
			    XlsWrite(XlsRef,RijSubtotaal,kol_aantal_,4,txt_,StylTotSum);
					SomRijBeg=0;SomRijEnd=0;
				}
				fasinit(52);*u(52,1)=rec_-60000; fasgeti(52);
			  zero(txt_,sizeof txt_);k=0; k+=copy0(s(52,14),&txt_[k],fldlen(52,14));
				/* XlsRij++; */ XlsWrite(XlsRef,XlsRij,2,0,&txt_[0],StylGrpTxt); 
				zero(txt_,sizeof txt_);	if(lijsttaalnr_==1) k=copy0("Total",&txt_[0],30); else k=copy0("Totaal",&txt_[0],30);
				if(kol_aantal_==4) XlsWrite(XlsRef,XlsRij,3,0,txt_,StylTotTxt);
			  XlsWrite(XlsRef,XlsRij,kol_aantal_,0,"",StylTotSum);	// eerst dummy totaal
				RijSubtotaal=XlsRij;
				XlsRij++;//XlsRij++;
			}
			else if(rec_>30000){
				if(SomRijBeg && RijSubtotaal){
			    zero(txt_,sizeof txt_);	sprintf(txt_,"=SUM(R%dC4:R%dC%d)",SomRijBeg,SomRijEnd,kol_aantal_); 
					XlsWrite(XlsRef,RijSubtotaal,kol_aantal_,4,txt_,StylTotSum);
					SomRijBeg=0;SomRijEnd=0;
				}
				fasinit(1);*u(1,1)=rec_-30000; fasgeti(1);
			  zero(txt_,sizeof txt_);k=0; k+=copy0(s(1,3),&txt_[k],30);
				/* XlsRij++; */ XlsWrite(XlsRef,XlsRij,2,0,&txt_[0],StylGrpTxt);
				zero(txt_,sizeof txt_);	if(lijsttaalnr_==1) k=copy0("Total",&txt_[0],30); else k=copy0("Totaal",&txt_[0],30);
				if(kol_aantal_==4) XlsWrite(XlsRef,XlsRij,3,0,txt_,StylTotTxt);
			  XlsWrite(XlsRef,XlsRij,kol_aantal_,0,"",StylTotSum);	// eerst dummy totaal
				RijSubtotaal=XlsRij;
				XlsRij++;//XlsRij++;
			}
			else if(rec_>0){
				fasinit(6);*u(6,1)=rec_; fasgeti(6);
				taal_off_=0;if(lijsttaalnr_==1 && fldlen(6,4) && *s(6,4)) taal_off_=1;
				XlsKol=1;
				WriteFld2Xls(XlsRij,kol_code_,6,arcd+1,StylNormal); XlsKol++;
				WriteFld2Xls(XlsRij,XlsKol++,6,3+taal_off_,StylNormal);
#if FLAGLOY
				zero(txt_,sizeof txt_); 
				if(*f(6,31)) stcli_d(txt_,(long)(*f(6,31)),4,1); else copy("    ",txt_,4);
				txt_[4]=' '; copy(s(6,10),&txt_[5],3);
				XlsWrite(XlsRef,XlsRij,XlsKol++,0,txt_,StylNormalCt);
#else
				WriteFld2Xls(XlsRij,XlsKol++,6,10,StylNormalCt);
#endif
				XlsWrite(XlsRef,XlsRij,kol_aantal_,0,"",StylFillCt); XlsKol++;
				if(SomRijBeg==0) SomRijBeg=XlsRij; SomRijEnd=XlsRij;
				XlsRij++;
			}
	  }
		if(SomRijBeg && RijSubtotaal){
		  zero(txt_,sizeof txt_);	sprintf(txt_,"=SUM(R%dC4:R%dC%d)",SomRijBeg,SomRijEnd,kol_aantal_); 
		  XlsWrite(XlsRef,RijSubtotaal,kol_aantal_,4,txt_,StylTotSum);
			SomRijBeg=0;SomRijEnd=0;
		}
		zero(txt_,sizeof txt_);	
		if(lijsttaalnr_==1) k=copy0("Articles divers - Remarques",&txt_[0],30); else k=copy0("Losse artikels - Opmerkingen",&txt_[0],30);
		/* XlsRij++; */ XlsWrite(XlsRef,XlsRij,2,0,txt_,StylGrpTxt);
		XlsRij++;//XlsRij++;
		for(k=0;k<5;k++){
			XlsWrite(XlsRef,XlsRij,2,0,"",StylFill);
			XlsWrite(XlsRef,XlsRij,3,0,"",StylNormal);
			XlsWrite(XlsRef,XlsRij,kol_aantal_,0,"",StylFillCt);
			XlsRij++;
		}
		XlsClose(XlsRef,1);
	  goto endsr;
	}

	getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,106,pr_mode,4))!=0) goto endsr;

  prtfld(25,1,-1); 
	if(lijsttaalnr_==1) prttext("<t38eb>Bon de commande<eb><t97>Pag.<ppp>."); 
#if FLAGHOE
	else prttext("<t38eb>Drankenlijst<eb><t97>Blz.<ppp>."); 
#else
	else prttext("<t38eb>Bestelformulier<eb><t97>Blz.<ppp>."); 
#endif

	prtbuf(1);			
  zero(txt_,sizeof txt_);
  prttext("<t20>Tel.: ");sysget(150,15,txt_);prttext(txt_);
  prttext("<t45>Mail: ");
#if FLAGEET	
	prttext("bestel@drankenvaneetvelde.be");
#else
	sysget(256,30,txt_);prttext(txt_);
#endif
  prtbuf(2);
	if(seldata.prx_klt){
		prttext("<t1be>");zero(txt_,sizeof txt_);copy(s(2,3),txt_,fldlen(2,3));prttext(txt_);prttext("<be>");prtbuf(3);// prttext(", ");
		prttext("<t1b>");
		zero(txt_,sizeof txt_);copy(s(2,4),txt_,fldlen(2,4));prttext(txt_);prttext(", ");
		zero(txt_,sizeof txt_);copy(s(2,5),txt_,fldlen(2,5));prttext(txt_);prttext("  ");
		zero(txt_,sizeof txt_);copy(s(2,6),txt_,fldlen(2,6));prttext(txt_);
		prttext("<t60>KlantNr "); if(fldlen(2,2)) prtfld(2,2,-1); else prtfld(2,1,-1);
		if(*s(2,8)) {zero(txt_,sizeof txt_);copy(s(2,8),txt_,fldlen(2,8));prttext("<t80>Tel. ");prttext(txt_);}
		prttext("<b>");prtbuf(4);
	}
	zero(txt_,sizeof txt_);
	if(lijsttaalnr_==1) k=copy0("Bon de commande ",txt_,25); 
#if FLAGHOE	
	else k=copy0("Drankenlijst ",txt_,25);
#else
	else k=copy0("Bestelformulier ",txt_,25);
#endif	
	k+=copy0(s(2,3),&txt_[k],20);
	p_pdfname(txt_,0,0);
	for(k=0;k<4;k++){
    if(std_txt[k][0]){prtifld(fm_us75,std_txt[k],-1);nextline();}
  }
  start_=0;
	FOREVER{
		if(start_>=max_art) break;
		free=999;nextline();q_per_page=free-1;
		prttext("\xD4[kader:0x10F,0,0,1,0,0xF0F0F0,-53;]|");
		if(start_+q_per_page<max_art){
			prttext("\xD4[kader:0x10F,0,0,1,53,0xF0F0F0,-106;]|");
		}
#if FLAGWYN // aantal en code verwisseld
		if(lijsttaalnr_==1) {prttext("<b>");if(fldlen(6,2)) prttext("<t2>Quant.");PrintTabPos(4+fldlen(6,2));prttext("Description<t43>Un.<t47> Code<b>");}
		else {prttext("<b>");if(fldlen(6,2)) prttext("<t2>Aantal");PrintTabPos(4+fldlen(6,2));prttext("Omschrijving<t43>Eh<t47> Code<b>");}
		if(start_+q_per_page<max_art){
			if(lijsttaalnr_==1){prttext("<b>"); if(fldlen(6,2)) prttext("<t55>Quant.");PrintTabPos(57+fldlen(6,2));prttext("Description<t96>Un.<t100> Code<b>");}
			else {prttext("<b>");if(fldlen(6,2)) prttext("<t55>Aantal");PrintTabPos(57+fldlen(6,2));prttext("Omschrijving<t96>Eh<t100> Code<b>");}
		}
#else
		if(lijsttaalnr_==1) {prttext("<b>");if(fldlen(6,2)) prttext("<t2>Code");PrintTabPos(4+fldlen(6,2));prttext("Description<t43>Un.<t47>Quant.<b>");}
		else {prttext("<b>");if(fldlen(6,2)) prttext("<t2>Code");PrintTabPos(4+fldlen(6,2));prttext("Omschrijving<t43>Eh<t47>Aantal<b>");}
		if(start_+q_per_page<max_art){
			if(lijsttaalnr_==1){prttext("<b>"); if(fldlen(6,2)) prttext("<t55>Code");PrintTabPos(57+fldlen(6,2));prttext("Description<t96>Un.<t100>Quant.<b>");}
			else {prttext("<b>");if(fldlen(6,2)) prttext("<t55>Code");PrintTabPos(57+fldlen(6,2));prttext("Omschrijving<t96>Eh<t100>Aantal<b>");}
		}
#endif
		nextline();
    for(k=start_;k<start_+q_per_page;k++){
			if(k>=max_art) break;
			if(tb_artrecs[k]>30000) 	prttext("\xD4[kader:0x10F,0,0,1,0,0xF0F090,-53;]|");
			else 	{
				zero(txt_,sizeof txt_);
#if FLAGLOY
				sprintf(txt_,"\xD4[kader:0x10F,0,0,1,0,0,%d,0,40,0,47,0,-53;]|",fldlen(6,2)+2);
#else
				sprintf(txt_,"\xD4[kader:0x10F,0,0,1,0,0,%d,0,40,0,45,0,-53;]|",fldlen(6,2)+2);
#endif
				prttext(txt_);
			}
			if(k+q_per_page<max_art){	
				if(tb_artrecs[k+q_per_page]>30000)	prttext("\xD4[kader:0x10F,0,0,1,53,0xF0F090,-106;]|");
			  else{
					zero(txt_,sizeof txt_);
#if FLAGLOY
					sprintf(txt_,"\xD4[kader:0x10F,0,0,1,53,0,%d,0,93,0,100,0,-106;]|",55+fldlen(6,2));
#else
					sprintf(txt_,"\xD4[kader:0x10F,0,0,1,53,0,%d,0,93,0,98,0,-106;]|",55+fldlen(6,2));
#endif
					prttext(txt_);
				}
			}
      rec_=tb_artrecs[k];
			if(rec_>60000){
					fasinit(52);*u(52,1)=rec_-60000; fasgeti(52);
					prttext("<t1b>"); PrintHoofdstuk(s(52,14),fldlen(52,14),53);prttext("<b>");
			}
			else if(rec_>30000){
				fasinit(1);*u(1,1)=rec_-30000; fasgeti(1);
				prttext("<t1b>"); PrintHoofdstuk(s(1,3),fldlen(1,3),53);prttext("<b>");
			}
			else if(rec_>0){
				fasinit(6);*u(6,1)=rec_; fasgeti(6);
				taal_off_=0;if(lijsttaalnr_==1 && fldlen(6,4) && *s(6,4)) taal_off_=1;
#if !FLAGWYN
				prttext("<t2>"); prtfld(6,2,-1);
#endif
				PrintTabPos(4+fldlen(6,2)); prtfld(6,3+taal_off_,31-(fldlen(6,2)-5));
#if FLAGLOY
				zero(txt_,sizeof txt_); 
				if(*f(6,31)) stcli_d(txt_,(long)(*f(6,31)),4,1); else copy("    ",txt_,4);
				txt_[4]=' '; copy(s(6,10),&txt_[5],3);
        prttext("<t41>"); prttext(txt_);

#else
				prttext("<t42>"); prtfld(6,10,3);
#if FLAGWYN
				prttext("<t48>"); prtfld(6,2,-1);
#endif
#endif

			}
			if(k+q_per_page<max_art) rec_=tb_artrecs[k+q_per_page]; else rec_=0;
			if(rec_>60000){
					fasinit(52);*u(52,1)=rec_-60000; fasgeti(52);
					prttext("<t54b>"); PrintHoofdstuk(s(52,14),fldlen(52,14),53); prttext("<b>");
			}
			else if(rec_>30000){
				fasinit(1);*u(1,1)=rec_-30000; fasgeti(1);
				prttext("<t54b>"); PrintHoofdstuk(s(1,3),fldlen(1,3),53);prttext("<b>");
			}
			else if(rec_>0){
				fasinit(6);*u(6,1)=rec_; fasgeti(6);
				taal_off_=0;if(lijsttaalnr_==1 && fldlen(6,4) && *s(6,4)) taal_off_=1;
#if !FLAGWYN
				prttext("<t55>"); prtfld(6,2,-1);
#endif
				PrintTabPos(57+fldlen(6,2)); prtfld(6,3+taal_off_,31-(fldlen(6,2)-5));
				// prttext("<t62>"); prtfld(6,3,30);
#if FLAGLOY
				zero(txt_,sizeof txt_); 
				if(*f(6,31)) stcli_d(txt_,(long)(*f(6,31)),4,1); else copy("    ",txt_,4);
				txt_[4]=' '; copy(s(6,10),&txt_[5],3);
        prttext("<t94>"); prttext(txt_);
#else
				prttext("<t95>"); prtfld(6,10,3);
#endif
#if FLAGWYN
				prttext("<t101>"); prtfld(6,2,-1);
#endif
			}
			nextline();
		}
		prtform(0);
		start_+=q_per_page*2;
	}
	prtclose();
	endsr:;
}

PrintTabPos(pos_)
int pos_;
{
	char str_[10];

	zero(str_,sizeof str_);sprintf(str_,"<t%d>",pos_); prttext(str_);
}
static PrintHoofdstuk(ptitel_,len_titel_,kol_len_)
char *ptitel_;
int16 len_titel_,kol_len_;
{
  int k,len_;
	char tekst_[100];	
	 
	zero(tekst_,sizeof tekst_);
  for(len_=0;len_<kol_len_;len_++){
		if(len_>=len_titel_ || *(ptitel_+len_)=='\0') break;
		tekst_[len_]=*(ptitel_+len_);
	}
	len_=(kol_len_-len_)/2;for(k=0;k<len_;k++) prttext(" ");
  prttext(tekst_);	
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
  int16 curs,j,key,k,start_=0,z,z_base,q_per_line,nstart_,auto_enter,err_pos_,curspos_,fkey,choice,curs1_;
  flag sr_nm;
  char *pdum,dumm_[10];
  pdum=&dumm_[0];
 
  curs=1;q_per_line=4;err_pos_=0;


  if(seldata.prx_klt) prx_nr=*s(2,26)-'0';
  else prx_nr=type_prx[0]-'0';
  if(prx_nr<0 || prx_nr>9) prx_nr=0;
  curs=1;
  FOREVER{
    redo:
    scrnum=0;scrget(2,218);z=1;scraddpicto(1,0,76,22,4,2,127,0,4,"Voeg artikels toe");
		if(seldata.prx_klt && fldlen(2,120)){scraddf(100,22,5,8);scrifld(100,VarTextFmt(19,0)," F9 laad bestelbon ");}
    scrifld(z++,fm_os20,pname[mode]);
    z_base=z;auto_enter=NO;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      j++;scrifld(z++,fm_ou3,&j);j--;
      fieldspc(6,2,&pdum,fmt);
      auto_enter=YES;if(tbe[j].code[0]!='\0' && z!=err_pos_) auto_enter=NO;
      if(auto_enter){scrifld(-z,fmt,tbe[j].code);z++;}
      else scrifld(z++,fmt,tbe[j].code);
      fieldspc(6,3,&pdum,fmt);
      auto_enter=YES;if(tbe[j].omschr[0]!='\0' && z!=err_pos_) auto_enter=NO;
      if(auto_enter){scrifld(-z,fmt,tbe[j].omschr);z++;}
      else scrifld(z++,fmt,tbe[j].omschr);
      scrifld(z++,fm_uf6_2,&tbe[j].vp_prx);
    }
    key=scrupd(curs,0x3DF);curs=z_base;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    auto_enter=NO;nstart_=start_;err_pos_=0;
    if(key==101) return YES;
    if(key==18){
      auto_enter=YES;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      k=(curspos_-z_base)%q_per_line;
      if(k==1 && tbe[j].code[0]=='\0') {curs=curspos_+1;goto redo;}
      if(k==2 && tbe[j].omschr[0]=='\0') {curs=curspos_+1;goto redo;}
    }
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
			curs=curspos_; goto redo;
    }
		if(key==109 && seldata.prx_klt && fldlen(2,120)){
			for(j=DIM_TBE-1;j>=0;j--) if(tbe[j].code[0]) break; j++;
	    for(k=0;k<fldlen(2,120)/2;k++){
				fasinit(6); *u(6,1)=*(uint16 *)(s(2,120)+k*2);
				if(j<DIM_TBE && *u(6,1)){
					fasgeti(6);
					copy(s(6,2),tbe[j].code,fldlen(6,2));
					copy(s(6,3),tbe[j].omschr,fldlen(6,3));
					tbe[j].recnr=*u(6,1);
					tbe[j].vp_prx=*f(6,PrNrs[prx_nr]);
					if(mode==PRIX){
  					if(seldata.prx_klt) tbe[j].vp_prx=get_prx(NO);
	  				else{
							if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd){tbe[j].vp_prx=*f(6,PrNrs[prx_nr+10]);}
		  			}
					}
					j++;
				}
			}
		}
		if(key==5001) load_art();
    if(key==110) get_isel();

    for(k=start_;k<(start_+D_LIN_SCR);k++){
      if((tbe[k].code[0] || tbe[k].omschr[0]) && tbe[k].hash!=hash(k)){
				fasinit(6);
				sr_nm=NO;
				if(tbe[k].code[0]) {j=0;*s(6,3)='.';copy(tbe[k].code,s(6,3)+1,fldlen(6,2));}
				else {j=1;copy(tbe[k].omschr,s(6,3),fldlen(6,3));sr_nm=YES;}
				if(search(6,0)){curs=3+j+(k-start_)*4;err_pos_=curs;goto redo;}
				copy(s(6,2),tbe[k].code,fldlen(6,2));
				copy(s(6,3),tbe[k].omschr,fldlen(6,3));
				tbe[k].recnr=*pu_6_1;
				tbe[k].vp_prx=*f(6,PrNrs[prx_nr]);
				if(mode==PRIX){
  				if(seldata.prx_klt) tbe[k].vp_prx=get_prx(NO);
	  			else{
					  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd){tbe[k].vp_prx=*f(6,PrNrs[prx_nr+10]);}
		  		}
				}
      }
      else if(tbe[k].code[0]=='\0'){
				zero((char *)&tbe[k].recnr,sizeof tbe[0]);
      }
      tbe[k].hash=hash(k);
    }
    if(key==108){
			choice='I'; SortKey=0;
			scraddf(-1,0,0,0);z=1;
			scraddf(z++,12,1,0);
			scraddf(z++,14,1,0);scraddf(z++,14,62,2);
			scraddf(z++,23,1,8);scraddf(z++,23,12,8);
			FOREVER{
				z=1;curs1_=-1;
				scrifld(z++,fm_os63,"Wenst U de geselecteerde artikels af te drukken ?");
				if(mode==PRIX || mode==KBESTLST){
  				scrifld(z++,VarTextFmt(61,0),"Druk volgens (I)ngave, (A)lfabet, (G)roep of (L)everancier : ");
	  			scrifld(z++,fm_ALNGIP,&choice);
					curs1_=1;
				} else z+=2;
				scrifld(z++,fm_os10," F1 terug ");scrifld(z++,VarTextFmt(12,0)," F8 druk af ");
				key=scrupd(curs1_,0x81);
				if(key!=108) goto redo;
				switch(choice){
					case 'N' : SortKey=1;break;
					case 'A' : SortKey=2;break;
					case 'P' : SortKey=6;break;
					case 'L' : SortKey=90;break;
					case 'G' : SortKey=91;break;
					default : SortKey=0;break;
				}
				break;
			}
			break;
    }
    if(key==18 || auto_enter){/* automatische bladskip op einde van scherm */
      for(k=0;k<D_LIN_SCR;k++){if(tbe[k+start_].omschr[0]=='\0') break;}
      if(k==D_LIN_SCR) key=103;
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

static load_art()
{
  int16 mode_,nr_,fkey;
 
 // seldata.prx_klt=0;
  seldata.selp_use=NO;
	if(mode==PRIX || mode==KBESTLST) {
	  if(ovlcall(2215,2)) goto endsr;
	}
	else{
		if(ovlcall(2215,0)) goto endsr;
	}
  
  scrget(1,7);scrupd(-3,0);
  fasinit(6);mode_=1;nr_=0; fkey=2;
  FOREVER{
    redo:;
    if(faskeyi(6,fkey,mode_)) break; mode_=2;
    if(DirCall_DRK2215_SelectArtikel()==NO) goto redo;
    for(nr_;nr_<DIM_TBE;nr_++) {
      if(tbe[nr_].omschr[0]=='\0') break;
    }
    if(nr_>=DIM_TBE){errnum=11; break;}
		copy(s(6,2),tbe[nr_].code,fldlen(6,2));
		copy(s(6,3),tbe[nr_].omschr,fldlen(6,3));
		tbe[nr_].recnr=*u(6,1);
		tbe[nr_].vp_prx=*f(6,PrNrs[prx_nr]);
		if(mode==PRIX){
  		if(seldata.inq_klt) tbe[nr_].vp_prx=get_prx(NO);
	  	else{
			  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd){tbe[nr_].vp_prx=*f(6,PrNrs[prx_nr+10]);}
			}
		}
    tbe[nr_].hash=hash(nr_);
  }
  endsr:;
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
				if(mode==PRIX){
  				if(seldata.prx_klt) tbe[k*50+j].vp_prx=get_prx(NO);
					else{
						if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd){tbe[k*50+j].vp_prx=*f(6,PrNrs[prx_nr+10]);}
					}
				}
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

static calc_leegg()
{
  uint16 rec_,nr_,pos_,oprx_op_dt_;
  float hoev_;
  char buf_[20];

  if(*i(6,9)==99) goto endsr;/* leeggoed in leeggoedkolom optellen */
  rec_=*pu_6_1;
  bd_leeg=0;oprx_op_dt_=prx_op_dt;
  nr_=41; if(mode==PRIX && lg_fles) nr_=44;
  if(*s(6,nr_)){
    hoev_=*f(6,42);
    copy(s(6,nr_),buf_,fldlen(6,2));
    fasinit(6);copy(buf_,s(6,2),fldlen(6,2));
    if(faskeyi(6,1,0)==0){
			pos_=0;if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd) pos_=10;
      bd_leeg=*f(6,PrNrs[prx_nr+pos_]);
      if(mode==PRIX && seldata.prx_klt) bd_leeg=get_prx(NO);
      bd_leeg*=hoev_;
    }
  }
	prx_op_dt=oprx_op_dt_; // leeggoed mag artikel niet beinvloeden
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
  sysget(1790,2,&sys1790);
  sysget(1918,2,&sear_stt);
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
	acc_exist=NO; fmt_get(6,30); if(fmt[1]&0x40) acc_exist=YES; 
  zero(&seldata.data_begin,sizeof seldata); seldata.dt_s_beg=*u(25,2)-730;
}

static accept(mode)
int16 mode;
{
  int16 k;
  float aantal_=0;

	if(via_ind_inp){
		for(k=0;k<DIM_TBE;k++) if(*u(6,1)==tbe[k].recnr) break;
		if(k>=DIM_TBE) return NO; 
		ind_prx=tbe[k].vp_prx;
		return YES;
	}
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

#if FLAGEET || FLAGGBL // specifieke prijslijst 
static p_EET_line()
{
  int j,k,pos_,posv_;
  unsigned rec_;
  float deler_,q_stuks_,bdf_,pr_ori_;
	

	pos_=0;prx_op_dt=NO;posv_=0; DatumPrijs=0;
  if(mode==PRIX || mode==KPRX){
		if(fldlen(6,11)) DatumPrijs=*u(6,11);
    if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd){
      pos_=94;prx_op_dt=YES;posv_=10;DatumPrijs=*u(6,105);
    }
  }



	pr_ori_=*f(6,PrNrs[prx_nr+posv_]);
  if(seldata.prx_klt) *f(6,PrNrs[prx_nr+posv_])=get_prx(YES);
  prx_op_dt=NO;if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd) prx_op_dt=YES;
  
  prt_bd[1]=*f(6,30+pos_);
  if(bit(sys3894,prx_nr)==0){
    prt_bd[2]=*f(6,PrNrs[prx_nr+posv_]);
    prt_bd[0]=prt_bd[2]-prt_bd[1];
    prt_bd[3]=prt_bd[2]* *f(6,28)/100.;
    prt_bd[4]=prt_bd[2]+prt_bd[3];
		if(prt_kkrt=='J') prt_bd[0]=pr_ori_-prt_bd[1];
  }
  else {
    prt_bd[4]=*f(6,PrNrs[prx_nr+posv_]);
    prt_bd[2]=prt_bd[4]/(1.+ *f(6,28)/100.);
    prt_bd[3]=prt_bd[4]-prt_bd[2];
    prt_bd[0]=prt_bd[2]-prt_bd[1];
		if(prt_kkrt=='J') prt_bd[0]=(pr_ori_/(1.+ *f(6,28)/100.))-prt_bd[1];
  }
  prt_bd[5]=0;
  if(*s(6,41)){
    rec_=*u(6,1);
    copy(s(6,41),s(6,2),fldlen(6,2));
    if(faskeyi(6,1,0)==0) prt_bd[5]=*f(6,PrNrs[prx_nr]);
    *u(6,1)=rec_;fasgeti(6);
  }

  q_stuks_=0; bdf_=prt_bd[2]; if(*i(6,9)==99) bdf_=prt_bd[5];
  if(stuksprx[prx_nr]=='J') q_stuks_=*f(6,31);
  if(q_stuks_==0) q_stuks_=1;
  deler_=*f(6,18+pos_); if(sys3586==1) deler_=bdf_*q_stuks_;
  w_bedrag=bdf_-*f(6,18+pos_)/q_stuks_;
  if(deler_) w_pct=(w_bedrag/ (deler_/q_stuks_))*100.;
  else w_pct=0;
  if(mode==PRIX && q_prx2prt==1){                     /* selectie op winst% */
    if(wpct_beg && w_pct<wpct_beg) goto endsr;
    if(wpct_end && w_pct>wpct_end) goto endsr;
  }
  j=0;if(prx_op_dt && p_np_bld=='J') j=2;
  for(k=0;k<20;k++) prtinfo(k,j);nextline();
  endsr:;
}
#endif

static p_line()
{
  int16 j,k,first_,last_,nr_,pos_,posv_,mode11_,firstnr_=0,lastnr_=0;
  uint16 rec_,dt_prx_;
  float q_lg_,deler_,q_stuks_,bdf_;
  char k_lg_b_[20],k_lg_s_[20];

  
  pos_=0;prx_op_dt=NO;posv_=0; DatumPrijs=0;
  if(mode==PRIX || mode==KPRX){
		if(fldlen(6,11)) DatumPrijs=*u(6,11);
    if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd){
      pos_=94;prx_op_dt=YES;posv_=10;DatumPrijs=*u(6,105);
    }
  }
	RecNrContract=0;
  if(mode==KPRX){
    zero((char *)&vp_kas[0],sizeof vp_kas);p_lg_stk=0;p_lg_bak=0;
    first_=0;last_=0;firstnr_=0,lastnr_=0;
    for(k=0;k<6;k++){
      nr_=sys3896[k]-'0';
      if(nr_<0 || nr_>9 || fldlen(6,PrNrs[nr_+posv_])==0) continue;
      if(YES) {
				if(first_==0) {first_=PrNrs[nr_];firstnr_=nr_;}
				last_=PrNrs[nr_];lastnr_=nr_;
				vp_kas[nr_]=*f(6,PrNrs[nr_+posv_]);
				if(!(sys3894 & (1<<nr_))) vp_kas[nr_]*=1.+*f(6,28)/100;
				if(vp_kas[nr_]!=*f(6,PrNrs[nr_+posv_])) vp_kas[nr_]=rnd_vprx(vp_kas[nr_],nr_);
      }
    }
    if(lgg_exist /* fldlen(6,41) || fldlen(6,44) */){
      q_lg_=*f(6,42);
      copy(s(6,41),k_lg_b_,fldlen(6,41));
      copy(s(6,44),k_lg_s_,fldlen(6,44));
      rec_=*pu_6_1;
      if(k_lg_b_[0]){
				fasinit(6);copy(k_lg_b_,s(6,2),fldlen(6,2));faskeyi(6,1,0);
				p_lg_bak=*f(6,first_);
				if(!(sys3894 & (1<<firstnr_))) p_lg_bak*=1.+*f(6,28)/100;
				p_lg_bak*=q_lg_;
				if(p_lg_bak != *f(6,first_)) p_lg_bak=rnd_vprx(p_lg_bak,0);
      }
      if(k_lg_s_[0]){
				fasinit(6);copy(k_lg_s_,s(6,2),fldlen(6,2));faskeyi(6,1,0);
				p_lg_stk=*f(6,last_);
				if(!(sys3894 & (1<<lastnr_))) p_lg_stk*=1.+*f(6,28)/100;
				if(p_lg_stk != *f(6,last_)) p_lg_stk=rnd_vprx(p_lg_stk,0);
      }
      fasinit(6);*pu_6_1=rec_;fasgetu(6);
    }
    goto dat_ok;
  }
  *u(1,1)=*u(6,7);fasgeti(1);
  vp_exc=*f(6,PrNrs[prx_nr+posv_]);
  if(mode==PRIX){
    vp_norm=0; zero(krt_str,sizeof krt_str);
    if(via_ind_inp) {
      if(seldata.prx_klt) vp_exc=get_prx(YES);/* om kortingstring te laden */
      vp_exc=ind_prx;
    }
		else if(seldata.prx_klt){ 
			vp_exc=get_prx(YES);
			if(fldlen(9,1)==4) RecNrContract=*l(9,1); else RecNrContract=*u(9,1);
		}
    if(*i(6,9)==99){bd_leeg=vp_exc; vp_exc=0;}/* leeggoed in aparte kolom */
		NettoArtStock=0;if(prt_stock=='J') CalcNettoStock();
  }
  vp_inc=vp_exc;
  if(sys3894 & (1<<prx_nr)) vp_exc=vp_inc/(1.+*f(6,28)/100);
  else vp_inc=rnd_vprx((float)(vp_exc*(1.+*f(6,28)/100)),prx_nr);
  vp_inc=rnd_vprx(vp_inc,prx_nr);

  q_stuks_=0; bdf_=vp_exc; if(*i(6,9)==99) bdf_=bd_leeg;
  if(stuksprx[prx_nr]=='J') q_stuks_=*f(6,31);
  if(q_stuks_==0) q_stuks_=1;
  deler_=*f(6,18+pos_); if(sys3586==1) deler_=bdf_*q_stuks_;
  w_bedrag=bdf_-*f(6,18+pos_)/q_stuks_;
  if(deler_) w_pct=(w_bedrag/ (deler_/q_stuks_))*100.;
  else w_pct=0;
  if(mode==PRIX && q_prx2prt==1){/* selectie op winst% */
    if(wpct_beg && w_pct<wpct_beg) goto endsr;
    if(wpct_end && w_pct>wpct_end) goto endsr;
  }
  if(bit(sys3760,5)==1 || (fldlen(2,88)==1 && *s(2,88)=='J')) vp_exc-=*f(6,30+pos_);/* zonder accijns */
#if FLAGOLH
	stockw=*f(6,33)* *f(6,34); stockwt+=stockw;
#endif
  totaliseer();
  if(lgg_exist) calc_leegg();
  dat_ok:;
  if((mode==PRIX || mode==KPRX) && prx_op_dt){
    k=0;if(p_np_bld=='J') k=2;
    copy(s(6,106),s(6,12),s(6,31)-s(6,12));
		copy(s(6,190),s(6,185),s(6,194)-s(6,190));
		if(prt2xls) pline2xls(0);
		else{
      for(j=1;j<=20;j++) prtinfo(j,k);
		}
    fasgeti(6);
  }
  else{
    if(mode==PRIX && seldata.prx_klt && taal_nr!=0){
      if(*s(6,3+taal_nr)) copy(s(6,3+taal_nr),s(6,3),fldlen(6,3));
    }
		if(prt2xls) pline2xls(0);
		else{
      for(j=1;j<=20;j++) prtinfo(j,fld_attr[j]);
		}
    fasgeti(6);
  }
  cnt++;
	if(prt2xls) XlsRij++;
	else{
	  nextline(); 
#if !FLAGTOL
    if(fldlen(6,3+3) && *s(6,3+3) && prt2xls==NO){
      copy(s(6,3+3),s(6,3),fldlen(6,3));
      prtinfo(2,0);nextline();
      fasgeti(6);
		}

		if(mode==PRIX && seldata.prx_klt && fldlen(9,88) && RecNrContract){/* contrakt afhank. van het aantal */
			fasinit(9);
			if(fldlen(9,1)==4) *l(9,1)=RecNrContract; else *u(9,1)=RecNrContract;
			fasgeti(9);
			for(k=0;k<4;k++){
				if(fldlen(9,88+k*5) && *f(9,88+k*5) && (*f(9,89+k*5) || *f(9,92+k*5))){
					if(fldlen(9,72) && *u(9,72) && *u(9,72)<=dt_p_upd && fldlen(9,77+k)) *f(9,92+k*5)=*f(9,77+k); // prijs op datum 
					zero(s(6,3),fldlen(6,3));
					if(*f(9,92+k*5) && *f(9,89+k*5)){
						bdf_=(*f(9,92+k*5)-*f(6,30+pos_))*(100.-*f(9,89+k*5))/100. + *f(6,30+pos_);
						bdf_=rnd_vprx(bdf_,prx_nr);
						sprintf_s(s(6,3),30,"  Vanaf%4.0f: %4.2f EUR",*f(9,88+k*5),bdf_); 
						// sprintf_s(s(6,3),30,"  Vanaf%4.0f: %4.2f EUR - %.0f%%",*f(9,88+k*5),*f(9,92+k*5),*f(9,89+k*5)); 
					}
					else if(*f(9,92+k*5)) sprintf_s(s(6,3),30,"  Vanaf%4.0f: %4.2f EUR",*f(9,88+k*5),*f(9,92+k*5)); 
					else if(*f(9,89+k*5)) sprintf_s(s(6,3),30,"  Vanaf%4.0f: -%.0f%% korting",*f(9,88+k*5),*f(9,89+k*5)); 
					prtinfo(2,0);nextline(); fasgeti(6);
				}
				else break;
			}
		}
#endif
  }
	if(fldlen(11,1) && mode==PRIX && prt2xls==NO && apprx=='J' && prt_AKfiches=='J'){
		fasinit(11);*u(11,3)=*u(6,1);mode11_=1;
		FOREVER{
			next11:;
			if(faskeyi(11,2,mode11_)) break; mode11_=2;
			if(*u(11,3)!=*u(6,1)) break;
		  if(*u(11,9) && *u(11,9)<dt_p_upd) goto next11; // verlopen promotie
			fasinit(1);if(*u(11,2)) {	*u(1,1)=*u(11,2); fasgeti(1);}
			prttext("   ");prtfld(1,3,30); 
			prttext(" Code: ");prtfld(11,5,-1); 
			prttext("  AP netto:"); prtfld(11,60,-1);  prttext(" Vanaf ");prtfld(11,8,-1);
			if(fldlen(11,68) && *f(11,68) && *f(11,68)!=*f(6,31)){prttext(" Aantal/verp:");prtfld(11,68,-1);}
			nextline();
		}
	}
  endsr:;
}

static CalcNettoStock()/* fill actuele stock in */
{
  int16 mode_=1;
  float qlv_;


  NettoArtStock=*f(6,33); 
  fasinit(58);*u(58,14)=*u(6,1);mode_=1;
  FOREVER{
    next:;
    if(faskeyi(58,2,mode_)) break; mode_=2;
    if(*u(58,14)!=*u(6,1)) break;
    fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
    if(fldlen(8,36) && *u(8,36)) goto next;
    qlv_=*f(58,31);
    if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)!=0) qlv_/=*f(58,63);
		if(fldlen(8,36) && *u(8,36)==10) NettoArtStock+=qlv_; // bestelbons leveranciers bijtellen
    else NettoArtStock-=qlv_;
  }
}



static pline2xls(int xmode_) // xmode_ : 0=waardes, 1=titel
{
	int16 k;


#if FLAGALS  // prijslijst voor Districoleden
  if(seldata.prx_klt) prx_nr=*s(2,26)-'0'; else prx_nr=type_prx[0]-'0';
  if(prx_nr<0 || prx_nr>9) prx_nr=0;
  if(stuksprx[prx_nr]=='J') lg_fles=YES;
  fmt_get(6,PrNrs[prx_nr]);
	XlsKol=1;
	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Artikel",0); else WriteFld2Xls(XlsRij,XlsKol++,6,arcd+1,0);
  if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Benaming",0); else WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"L-prijs",0); else WriteVar2Xls(XlsRij,XlsKol++,fmt,&vp_exc,0);
	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Accijns",0); else WriteFld2Xls(XlsRij,XlsKol++,6,30,0);
	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Leegg.",0); else WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&bd_leeg,0);
	goto endsr;
#endif

	XlsKol=1;
	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Code",0); else WriteFld2Xls(XlsRij,XlsKol++,6,arcd+1,0);
  if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Naam",0); else WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
	if(fldlen(6,3+3)){
	  if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Opmerking",0); else WriteFld2Xls(XlsRij,XlsKol++,6,3+3,0);
	}
#if FLAGGRS
	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Leverancier",0);
	else{
		fasinit(1);*u(1,1)=*u(6,7);fasgeti(1);
		WriteFld2Xls(XlsRij,XlsKol++,1,3,0);
	}
#endif
  if(xmode_)  XlsWrite(XlsRef,0,XlsKol++,0,"EH",0); else WriteFld2Xls(XlsRij,XlsKol++,6,10,0);
	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Groep",0); else WriteFld2Xls(XlsRij,XlsKol++,6,9,0);
	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"BTW%",0); else WriteFld2Xls(XlsRij,XlsKol++,6,28,0);
	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Vanaf",0); else WriteVar2Xls(XlsRij,XlsKol++,fm_udat,&DatumPrijs,StylDate);
	if(apprx=='J'){
	  if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"AP-bruto",0); else WriteFld2Xls(XlsRij,XlsKol++,6,12,0);
		if(fldlen(6,14)){if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Kort%",0); else WriteFld2Xls(XlsRij,XlsKol++,6,14,0);}
		if(fldlen(6,15)){if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Kort%",0); else WriteFld2Xls(XlsRij,XlsKol++,6,15,0);}
		if(fldlen(6,17)){if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Kort.EUR",0); else WriteFld2Xls(XlsRij,XlsKol++,6,17,0);}
		if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"AP-netto",0); else WriteFld2Xls(XlsRij,XlsKol++,6,18,0);
		if(fldlen(6,19)){if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"H.kost",0); else WriteFld2Xls(XlsRij,XlsKol++,6,19,0);}
		if(fldlen(6,20)){if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Los.vg",0); else WriteFld2Xls(XlsRij,XlsKol++,6,20,0);}
	}
  if(q_prx2prt>1){
#if FLAGLRM
    if(prt_acc=='J'){
#else
    if(prt_acc=='J' /* && bit(sys3760,5)==1 */ && acc_exist){
#endif
			if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Accijns",0); else WriteFld2Xls(XlsRij,XlsKol++,6,30,0);
		}
    for(k=0;k<6;k++){
	    if(type_prx[k]){
        prx_nr=type_prx[k]-'0';
	      if(fldlen(6,PrNrs[prx_nr])){
					if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,&vptekst[prx_nr*10],0); else WriteFld2Xls(XlsRij,XlsKol++,6,PrNrs[prx_nr],0); 
				}
	    }																							
    }
    prx_nr=0;
  }
  else if(q_prx2prt==1){
    if(seldata.prx_klt) prx_nr=*s(2,26)-'0'; else prx_nr=type_prx[0]-'0';
    if(prx_nr<0 || prx_nr>9) prx_nr=0;
    if(stuksprx[prx_nr]=='J') lg_fles=YES;
    fmt_get(6,PrNrs[prx_nr]);
    if(seldata.prx_klt){
    	if(prt_nprx=='J'){
	      if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Normaal",0); else WriteVar2Xls(XlsRij,XlsKol++,fmt,&vp_norm,0);
        if(bit(sys3760,4)==1 && bit(sys3894,prx_nr)==0){
					if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Norm.Inc",0); else WriteVar2Xls(XlsRij,XlsKol++,fmt,&vp_inorm,0);
				}
      }
	    if(prt_kkrt=='J'){
				if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Korting",0); else WriteVar2Xls(XlsRij,XlsKol++,fm_os10,krt_str,0);
			}
    }
#if FLAGLRM
    if(prt_acc=='J'){
#else
    if(prt_acc=='J'/* && (bit(sys3760,5)==1 || (fldlen(2,88)==1 && *s(2,88)=='J')) */ && acc_exist){
#endif
			if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Accijns",0); else WriteFld2Xls(XlsRij,XlsKol++,6,30,0);
		}
    if(bit(sys3894,prx_nr)==0 || seldata.prx_klt){
      if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Excl.BTW",0); else WriteVar2Xls(XlsRij,XlsKol++,fmt,&vp_exc,0);
      if((sys3760 & 0x0200)==0){
				if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Incl.BTW",0); else WriteVar2Xls(XlsRij,XlsKol++,fmt,&vp_inc,0);
			}
    }
    else{
			if(xmode_){
				if(seldata.prx_klt) XlsWrite(XlsRef,0,XlsKol++,0,"Incl.BTW",0);
				else XlsWrite(XlsRef,0,XlsKol++,0,&vptekst[prx_nr*10],0);
			}
			else 	WriteVar2Xls(XlsRij,XlsKol++,fmt,&vp_inc,0);
		}
    if((bit(sys3760,3)==1 && apprx=='J') || prt_wpct=='J'){
    	if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"W%",0); else WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&w_pct,0);
	    if(bit(sys3760,3)==1){
				if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Winst",0); else WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&w_bedrag,0);
			}
    }
  }
	if(lgg_exist && q_prx2prt>0){
	  if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Leeggoed",0); else WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&bd_leeg,0);
  }
  if(prt_stock=='J'){
		if(xmode_) XlsWrite(XlsRef,0,XlsKol++,0,"Stock",0); else WriteVar2Xls(XlsRij,XlsKol++,fm_uf5_2,&NettoArtStock,0);
	}
	endsr:;
}

static float get_prx(imode_)
flag imode_;
{
  int16 m,nokort,pos_,vpos_,vp_manueel_;
  float kort_=0,vp_=0,bd_accijn,bd_,hl_kort_,EUR_kort_=0;
 
  pos_=0;vpos_=0;seldata.fl_afspraak=NO;hl_kort_=0;
  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=dt_p_upd){pos_=94; vpos_=10;prx_op_dt=YES;}
	if(*s(2,26)=='A') vp_=*f(6,18+pos_);
  else vp_=*f(6,PrNrs[prx_nr+vpos_]);
	if(*i(6,9)!=99) vp_norm=vp_;
  if(fldlen(2,18)) kort_=*f(2,18); else kort_=0;
  nokort=NO;
	if(fldlen(6,104) && *s(6,104)=='J') nokort=YES;
  *u(52,1)=*i(6,9);
  if(fasgeti(52)==0){
    if(fldlen(52,21) && *s(52,21)=='N') nokort=YES;
  }
  if(kont_exist){
    fasinit(9);*u(9,2)=*pu_2_1;*u(9,3)=*pu_6_1;
		m=get_contr(1); if(m==0) {seldata.fl_afspraak=YES;nokort=NO;}//wel korting indien expliciet op artikel
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
    } else fasinit(9);
  }
  if(fldlen(6,37)==0 || *f(6,37)==0) hl_kort_=0;
  else{                                        /* omrekenen naar verpakking */
    hl_kort_=hl_kort_* *f(6,37)/100;
  }
#if FLAGEPD || FLAGVDW// EUR korting als hl-korting gebruiken
	vp_+=EUR_kort_; hl_kort_+=EUR_kort_;
#endif
  bd_accijn=0;
  if(acc_exist && *i(6,9)!=99){
    bd_accijn=*f(6,30+pos_);
  }

  if((hl_kort_ || kort_) && nokort==NO){
		if(bit(sys3894,prx_nr)) bd_accijn*=1.+*f(6,28)/100; // accijns incl BTW maken omdat prijs ook incl is
    vp_=(vp_-bd_accijn)*(100.- kort_)/100.+bd_accijn;
		if(bit(sys3894,prx_nr)) bd_accijn/=1.+*f(6,28)/100; // terug excl. BTW maken
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
  if(type_<0 || type_>9) type_=0; 
	fl_=valu_cnv("EUR","EUR",(double)(fl_),(double)(sys2830[type_]));
  return (float)fl_;
}

static totaliseer()
{
  int16 g,k,len,pos=0;
  char *pd;

  for(k=0;k<sizeof tot_veld/2;k++){
    g=tot_veld[k];
    len=fmt_get(6,g);
    if(len){
      pd=&tot_buf[pos];
      switch(fmt[1]&0x0F){
	case 0 : *(uint16 *)pd+=*u(6,g);break;
	case 1 : *(int16 *)pd+=*i(6,g);break;
	case 3 : *(long *)pd+=*l(6,g);break;
	case 4 : *(float *)pd+=*f(6,g);break;
	case 5 : *(double *)pd+=*d(6,g);break;
      }
      pos+=len;
    }
  }
}

static copy_total()
{
  int16 g,k,len,pos=0;

  for(k=0;k<sizeof tot_veld/2;k++){
    g=tot_veld[k];
    len=fmt_get(6,g);
    if(len){
      copy(&tot_buf[pos],s(6,g),len);
      pos+=len;
    }
  }
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

static fileout()/* 0.01 */
{
  int16 maxfld,k,curs=1,z,key,key_nr_=0;
  uint16 recordcnt=0;
  char filnam[15];

  sysget(1790,2,&k);
  if((k&2)==0) {
    if(ovltest(290)){ovlexit(290);}
    else {errnum=12;goto endsr;}
  }
  sysget(3632,2,&key_nr_);if(key_nr_==0) key_nr_=2;
  sysget(4480,14,filnam);filnam[14]='\0';
  sysget(4494,2,&maxfld);
  sysget(4498,23,str4498);
  sysget(4521,1,&sys4521);
  FOREVER{
    redo:
    scrget(1,76);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_us14,filnam);
    scrifld(z++,fm_uu3,&maxfld);
    key=scrupd(curs,0x0481);
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(filnam[0]=='\0') {errnum=38;goto redo;}
    if(key==108) break;
  }
  if(ovlcall(2215,0)) goto endsr;
  sysput(4480,14,filnam);
  sysput(4494,2,&maxfld);
  scrget(1,170);
  errnum=fasopen(filnam,2);if(errnum) goto endsr;
  fasinit(80);seqo_pos=0;seqo_mode=2;
  if(maxfld<1) maxfld=MAXFLD;
  scrget(1,7);scrupd(-3,0);

  fasinit(stu);
  FOREVER{
    if(faskeyi(stu,key_nr_,2)) break;
    if(DirCall_DRK2215_SelectArtikel()){
      dump_art(maxfld);recordcnt++;
    }
  }
  fasclos(-2);
  fasflush(0);
  endsr:;
}

static dump_art(maxfld)
int16 maxfld;
{
  int16 k;
 
  zero(seqo_str,sizeof seqo_str);pos=0;
  fasinit(1);*u(1,1)=*u(6,7);fasgeti(1);
  for(k=2;k<=6;k++) seqo_fld(6,k);
  seqo_fld(1,3);
  for(k=8;k<maxfld;k++) seqo_fld(6,k);
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
      if(seqo_str[k]==0x09) seqo_str[k]='.';// delete | 
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;// delete trailing blanks 
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


static MailDocument(SendMode)
int SendMode;
{
  int j,k,pos_,p_adr_=0;
	uint16 yy,mm,dd;
	  
		// keywords invullen 
	zero(MailMergeData[0],sizeof MailMergeData);MailSaveAdres='N';

	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy(s(2,3),MailMergeData[k],fldlen(2,3)); continue;}
		if(cmpstr(MailMergeKeywords[k],"ADRES",5)==0){copy(s(2,4),MailMergeData[k],fldlen(2,4)); continue;}
		if(cmpstr(MailMergeKeywords[k],"POSTCODE",8)==0){copy(s(2,5),MailMergeData[k],fldlen(2,5)); continue;}
		if(cmpstr(MailMergeKeywords[k],"GEMEENTE",8)==0){copy(s(2,6),MailMergeData[k],fldlen(2,6)); continue;}
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){p_adr_=k;copy(s(2,21),MailMergeData[k],fldlen(2,21)); continue;}
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNAAM",12)==0){copy0("Prijslijst",MailMergeData[k],50);continue;}
//		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNUMMER",13)==0){stcli_d(MailMergeData[k],(long)nr_,5,1); continue;}
		if(cmpstr(MailMergeKeywords[k],"DATUM",5)==0){
      if(mode==PRIX) jddate(dt_p_upd,&yy,&mm,&dd); 
			else jddate(*u(25,2),&yy,&mm,&dd);
      stcli_d(&MailMergeData[k][0],(long)dd,2,0);MailMergeData[k][2]='/';
      stcli_d(&MailMergeData[k][3],(long)mm,2,0);MailMergeData[k][5]='/';
      stcli_d(&MailMergeData[k][6],(long)yy,4,0);
			continue;
		}
	//	if(cmpstr(MailMergeKeywords[k],"TOTAALBEDRAG",12)==0){stcli_d(MailMergeData[k],(long)(nr_),5,1); continue;}
	}
	for(j=4;j>=0;j--) if(MailBodyText[j][0]) break;
	zero(MailMergeBodyText,sizeof MailMergeBodyText);pos_=0;
	if(j>=0){
		for(k=0;k<=j;k++) {
			pos_+=copy0(MailBodyText[k],&MailMergeBodyText[pos_],75);
			if(k<j) MailMergeBodyText[pos_++]=' '; // '\n';
		}
	}
	zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage); // voor de veiligheid
	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);MailMergeBijlage[0]=SpoolFileNr;
	zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate);copy(MailTemplate,MailMergeSpecialTemplate,5);

	MailMergeFormaat=5; 
//	if(fldlen(2,24)) MailMergeTaal=talen[taaltxt]; else MailMergeTaal='\0';
	k=SendMail(SendMode); 
	if(k && MailSaveAdres=='J' && *u(2,1)){copy(MailMergeData[p_adr_],s(2,21),fldlen(2,21));fasupd(2);} // email adres bewaren
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

 
