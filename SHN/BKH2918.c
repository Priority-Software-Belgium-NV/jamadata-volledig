/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH2918GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH2918dat
#define ovlcod BKH2918cod
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

char ovldat[] = "bkh2918  00:01 10/11/09 (c) Jamadata";
																																	/* afdrukken klant/lev etiketten  */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXFLD          120
#define DIM_LETIK       100
#define DIM_TBE         75
#define flag            uint16
#define D_LIN_SCR       17
#define CALCDEF         "%N%0%0%0%0%0%0%0%0%0"

static struct {
  char filname[15];
  int16 filstru;
} files[7];

static struct{
  uint16 rec;
  char naam[51];
} tb_kaart[DIM_TBE];

static struct{
  uint16 aantal;
  uint16 rec;
} tbe[DIM_TBE];

static char *fichenm[6]={"Leveranciersfiche","Klantenfiche","Grootboekrekening","","Klantentoer","Artikelfiche"};
static char *selp_txt[6]={"Ondergrens (>)","Ondergrens (> of =)",
		"Bovengrens (<)","Bovengrens (< of =)",
		"Gelijk","Niet gelijk"};

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

static int16 sys3648;
static uint16 sys3650;
static int16 stu,chk_btoeg=0,free,key21;

static uint16 tb_etik[DIM_LETIK],tot_etik,x_offset,y_offset;
static int16 hz_dots,vt_dots,lettype,line_dots,q_hor,q_vert;

static int16 lvcd,klcd,sys3670;
static char nm_20[20],nm_dehr[52],taal_i,talen[4],def_grbex[2],oldnm[50];
static int16 selp_stu=0;
static char selp_bf[4][1000],selp_des[40],*selp_fld,*calctype;
static flag selp_use,selp_ge,selp_le,sys3618,prt2pdf;
static float def_btw, btw_pct[8],sys3614;
static long def_grb;
static char vptekst[100],stuksprx[10];

//static int16 lbreedte[64] = {116,280,260,272,280,260,239,301,305,153,194,305,260,371,
//		    284,301,235,305,280,206,260,284,284,391,280,280,260,194,
//		    210,173,215,173,145,194,219,108,132,219,112,321,219,194,
//		    215,215,173,149,132,215,194,280,198,194,173,194,186,198,
//		    194,198,194,194,194,194,194,214};
									
static int16 etikaant,FormsPrinted,PrinterIsOpen;



static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_uf7_1[] = {6,0xD4,7,1,0x60,0};
static char fm_of7_1[] = {6,0x94,7,1,0x60,0};
static char fm_btw[]   = {6,0x94,2,1,0x20,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_u_SI[]  = {11,0xC8,1,0,1,0,'S','S','I','I',0};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,0x09,0,'A','A','N','N',0};
static char fm_uANI[]  = {13,0xC8,1,0,1,0,'A','A','N','N','I','I',0};							
static char ram[10000],buf600[600];
static int16 dat_len,ram_recl,hash_len,max_line,len6_2,len6_3,len2_120;
static int16 len2_3,len63_10;
static uint16 hash_val;
 
static char sort_meth,prt_fiche,fiche_per_blad;
static char def_munt[4],fmt[40],*ps2_120;
static char prt_info,only_info,type_info,only_memo,prt_memo;
static uint16 dt_beg,dt_end,lst_recs[10];
static flag sear_stt,sys1854,sys2698,only_dsp;
static int16 seqo_len,pfld_ext,pnr_kbak,pnr_kstk;
static flag loaded,suppr_wi,rev_prx_calc;
static uint16 *pu_6_1,*pu_2_1;

static int16 def_taal;

ovlcod(parmval)
int16 parmval;
{
  retcall=YES;
  initload();
  stu=parmval; if(stu>2) ovlexit(-1);
  key21=21;if(faskeyi(stu,key21,0)==45) key21=2;
  selp_wis();
  if(stu==2 && sys3670) prt_kaart(); else etiket();
  ovlexit(-1);
}

static prt_kaart()
{
  int16 k,cnt,fuval,fkey;
  uint16 getnr;

  if(sel_kaart("Drukken klantenkaarten",NO,NO)) goto endsr;

	if(sort_meth=='I'){
		if(ask_kltkaart()) goto endsr;
	}
	else{
		if(sort_meth=='K') fkey=0;
		else if(sort_meth=='N' && fldlen(stu,2)) fkey=1;
		else fkey=2;

		selp_use=NO;
		if(selp_ask()) goto endsr;
	}

  free=999;
									
  scrget(1,6);scrupd(-3,0);
  cnt=0;getnr=1;
  fasinit(stu); tot_etik=0;
	
	if(sort_meth=='I'){
		for(k=0;k<DIM_TBE;k++){
			if(tb_kaart[k].rec==0) continue;
			fasinit(2);*u(2,1)=tb_kaart[k].rec;fasgeti(2);
			add_etik();
	  }
		prt_krt(1);
    prtclose();
    goto endsr;
	}

  while(free>=0){
    next:;
    if(fkey>=1){
      if(faskeyi(stu,fkey,2)) break;
    }
    else{
      *u(stu,1)=getnr++;
      fuval=fasgeti(stu);
      if(fuval==46) continue;
      else if(fuval) break;
    }
    if(selp_tst()){
      add_etik();
      cnt++;
    }
  }
  prt_krt(1);
  prtclose();
  endsr:;
}

static sel_kaart(ptxt_,mode_,pdf_allowed_)/* NO=ind.kaartm YES=vereniging */
char *ptxt_;
{
  int16 z,key,curs=3;
							
  if(sort_meth=='\0') sort_meth='I';
  fasinit(2);
  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,2,25,3);
    scraddf(z++,6,5,0);
		scraddf(z++,7,5,0);scraddf(z++,7,48,2); 
	  scraddf(z++,23,1,8);scraddf(z++,23,11,8);  // functietoetsen 
		scraddpicto(1,0,76,22,4,2,583,0,0,"maak PDF"); 
		z=1;
    scrifld(z++,VarTextFmt(24,0),"Afdrukken klantenkaarten");
 //   scrfld(z++,25,1);
		scrifld(z++,VarTextFmt(40,0),"Print volgens Nummer, Alfabetisch");
		scrifld(z++,VarTextFmt(43,0),"of met Individuele opgave van de klanten :");
    scrifld(z++,fm_uANI,&sort_meth);
		scrifld(z++,VarTextFmt(9,0)," F1 stop");scrifld(z++,VarTextFmt(13,0)," F8 neem aan");
    key=scrupd(curs,0x81);
		prt2pdf=NO;
  	if ((key/0x100)==1) key=(key&0xFF)+5000;
		switch(key){
			case 5001 : prt2pdf=YES; key=108; break; // pdf
			default : break;
		}
    if(key==101) return YES;
		if(key==108) break;
  }
	
  return NO;
}


static add_etik()
{
  int16 k,pmode_=0;
					
  redo_add:;
  for(k=0;k<DIM_TBE;k++){
    if(tbe[k].aantal==0){
      tbe[k].aantal=1; tbe[k].rec=*u(2,1);
      break;
    }
  }
  if(k>=DIM_TBE){prt_krt(pmode_); pmode_=1; goto redo_add;}
  if(k<DIM_TBE) tot_etik+=1;
  if(tot_etik>=75 || k>=DIM_TBE) prt_krt(0);
  endsr:;
}

static prt_krt(mode_)/* kaartjes van 5,1 cm op 9,3 cm */
int16 mode_;/* 1= blad moet niet perse vol zijn */
{
  int16 j,k,vt,hz,max_loop,n,bpos_;
  int16 form_dat[8],pr_mode,prtnr;
  char str_[100];
	
	getsysprNew(6,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  scrget(1,6);

  n=0;
  while(free>=0 && (tot_etik>=10 || (mode_ && tot_etik>0))){
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) {free=-1;break;}
    mov(x_offset,y_offset); push();
    for(vt=0;vt<5;vt++){
      if(vt) mov(0,570+47);
      for(hz=0;hz<2;hz++){
	push();
	j=60; if(hz==2) j=30;
	if(hz==1) mov(1150,0);
	while(n<DIM_TBE){
	  if(n<DIM_TBE && tbe[n].aantal>0){
	    fasinit(2);*u(2,1)=tbe[n].rec;fasgeti(2);
	    box(3,0,5,1100,550);
	    block(12,190,10,760,90);
	    txt(20,210,80,"KLANTENKAART","B");

	    zeros(str_,sizeof str_);
	    copy(s(25,1),str_,30);
	    cnv_char(str_,30);
	    bpos_=cent_txt(8,300,1150,str_);
	    txt(8,bpos_,140,str_,"");

			zeros(str_,sizeof str_);
	    copy(s(2,3),str_,40);
	    cnv_char(str_,40);
	    bpos_=cent_txt(12,5,1150,str_);
	    txt(12,bpos_,245,str_,"IB");
	
	    zeros(str_,sizeof str_);
	    copy(s(2,4),str_,30);
	    cnv_char(str_,30);
	    bpos_=cent_txt(12,5,1150,str_);
	    txt(12,bpos_,315,str_,"B");

	    zeros(str_,sizeof str_);
	    copy(s(2,5),str_,7);
	    for(k=0;k<7;k++) if(str_[k]=='\0') break;
	    copy("       ",&str_[k],7);
	    copy(s(2,6),&str_[7],25);
	    cnv_char(str_,30);
	    bpos_=cent_txt(12,5,1150,str_);
	    txt(12,bpos_,365,str_,"B");

	    zeros(str_,sizeof str_);j=0;
			if(fldlen(2,2)) {copy(s(2,2),str_,fldlen(2,2)); str_[5]='\0';} //afkappen op 5 kar
			else stcli_d(&str_[0],(long)(tbe[n].rec),5,0);
	    txt(18,100,510,str_,"B");

	    zeros(str_,sizeof str_);j=0;
	    copy("25",str_,2);
	    copy("40123",&str_[2],5); // stcli_d(&str_[2],(long)bar_pref,5,0);
	    stcli_d(&str_[7],(long)(tbe[n].rec),5,0);
	    ean13c(str_);
	    prtean(600,440,4,90,90,str_);
	    tbe[n].aantal--;tot_etik--;break;
	  }
	  else n++;
	}
	pop();
      }
    }
    prt_string("\x0C");
  }
  max_loop=DIM_TBE;tot_etik=0;
  for(k=0;k<DIM_TBE;k++){
    if(max_loop>0) max_loop--; else break;
    if(tbe[k].aantal==0){/* lege plaatsen compressen */
      for(j=k;j<DIM_TBE-1;j++){copy((char *)&tbe[j+1],(char *)&tbe[j],sizeof tbe[0]);}
      zeros((char *)&tbe[DIM_TBE-1],sizeof tbe[0]);
      k--;
    }
    else tot_etik+=tbe[k].aantal;
  }
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  prtclose();
  endsr:;
}

static cnv_char(ps_,len_) // om par294 compatibel te houden 
char *ps_;
int16 len_;
{
	CnvJamaChar(ps_,len_,0);
}

static prt_string(string)
char *string;
{
  char *_string;
  int16 len;

  len=0; _string=string;
  while (*_string++) len++;
  prt_bin(string,len);
}

static prt_bin(string,len)
char *string;
int16 len;
{
  char fm[8];
 
  fm[0]=7; fm[1]=0x88; fm[2]=len%256; fm[3]=len/256; fm[4]=0; fm[5]=0; fm[6]=0;
  if (len>0) prtifld(fm,string,-2);
}
 
static sel_orient(or_)
char or_;
{
  char str_[10];

  zero(str_,sizeof str_);str_[0]=0x1B;
  if(or_=='l' || or_=='L'){copy("&l1O",&str_[1],6); prt_string(str_);}
  else if(or_=='p' || or_=='P') {copy("&l0O",&str_[1],6);prt_string(str_);}
}

//static cent_txt(dikte_,bpos_,epos_,ps_)
//char *ps_;
//int16 dikte_,bpos_,epos_;
//{
//  int16 j,pos_;
//  char kar_;
//  float qpunten_;
//
//  j=0; qpunten_=0;
//  FOREVER{
//    kar_=*(ps_+j++);
//    if(kar_=='\0') break;
//    if(kar_==' ') qpunten_+=lbreedte[0];
//    else if(kar_>='A' && kar_<='Z') qpunten_+=lbreedte[1+(kar_-'A')];
//    else if(kar_>='a' && kar_<='z') qpunten_+=lbreedte[27+(kar_-'a')];
//    else if(kar_>='0' && kar_<='0') qpunten_+=lbreedte[53+(kar_-'0')];
//    else qpunten_+=lbreedte[63];
//  }
//  if(dikte_) qpunten_=(qpunten_* ((float)dikte_/90.))+.49;
//  pos_=(epos_-bpos_-qpunten_)/2;
//  if(pos_<0) pos_=bpos_; else pos_+=bpos_;
//  return pos_;
//}

 
#include "Std\HPBarc.c"

static ask_kltkaart()
{
  int16 curs,j,key,k,start_=0,z,z_base,q_per_line,nstart_,auto_enter,err_pos_,curspos_;
  flag sr_nm;
  char *pdum,dumm_[10];
  pdum=&dumm_[0];
 
  curs=1;q_per_line=3;err_pos_=0;


  zero((char *)&tb_kaart[0].rec,sizeof tb_kaart);
  curs=1;
  FOREVER{
    redo:
    scrget(1,284);z=1;
    z_base=z;auto_enter=NO;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      j++;scrifld(z++,fm_ou3,&j);j--;
      fieldspc(2,1,&pdum,fmt);
      auto_enter=YES;if(tb_kaart[j].rec && z!=err_pos_) auto_enter=NO;
      if(auto_enter){scrifld(-z,fmt,&tb_kaart[j].rec);z++;}
      else scrifld(z++,fmt,&tb_kaart[j].rec);
      fieldspc(2,3,&pdum,fmt);
      auto_enter=YES;if(tb_kaart[j].naam[0]!='\0' && z!=err_pos_) auto_enter=NO;
      if(auto_enter){scrifld(-z,fmt,tb_kaart[j].naam);z++;}
      else scrifld(z++,fmt,tb_kaart[j].naam);
    }
    key=scrupd(curs,0x2DF);curs=z_base;curspos_=fldcurs;
    auto_enter=NO;nstart_=start_;err_pos_=0;
    if(key==101) return YES;
    if(key==18){
      auto_enter=YES;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      k=(curspos_-z_base)%q_per_line;
      if(k==1 && tb_kaart[j].rec==0) {curs=curspos_+1;goto redo;}
      if(k==2 && tb_kaart[j].naam[0]=='\0') {curs=curspos_+1;goto redo;}
    }
    if(key==104){
      j=(curspos_-1)/3;j+=start_;
      for(k=DIM_TBE-2;k>=j;k--){
	      copy((char *)&tb_kaart[k].rec,(char *)&tb_kaart[k+1].rec,sizeof tb_kaart[0]);
      }
      zero((char *)&tb_kaart[j].rec,sizeof tb_kaart[0]);
    }
    if(key==105){
      j=(curspos_-1)/3;j+=start_;
      for(k=j;k<DIM_TBE-2;k++){
				copy((char *)&tb_kaart[k+1].rec,(char *)&tb_kaart[k].rec,sizeof tb_kaart[0]);
      }
      zero((char *)&tb_kaart[DIM_TBE-1].rec,sizeof tb_kaart[0]);
    }
		 

    for(k=start_;k<(start_+D_LIN_SCR);k++){
      if(tb_kaart[k].rec || tb_kaart[k].naam[0]){
				fasinit(2);
				sr_nm=NO;
				if(tb_kaart[k].rec){
					*u(2,1)=tb_kaart[k].rec;if(fasgeti(2)){curs=1+(k-start_)*3;err_pos_=curs;goto redo;}
					copy(s(2,3),tb_kaart[k].naam,fldlen(2,3));
				}
				else{
				  copy(tb_kaart[k].naam,s(2,3),fldlen(2,3));
				  if(search(2,0)){curs=2+(k-start_)*3;err_pos_=curs;goto redo;}
					copy(s(2,3),tb_kaart[k].naam,fldlen(2,3));tb_kaart[k].rec=*u(2,1);
				}
      }
      else	zero((char *)&tb_kaart[k].rec,sizeof tb_kaart[0]);
    }
    if(key==108){
			if(DisplayWarning("Wenst U de geselecteerde kaarten af te drukken ?",61,1)==YES) break;
    }
    if(key==18 || auto_enter){/* automatische bladskip op einde van scherm */
      for(k=0;k<D_LIN_SCR;k++){if(tb_kaart[k+start_].rec==0) break;}
      if(k==D_LIN_SCR) key=103;
    }
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
    if(start_>(DIM_TBE-D_LIN_SCR)) start_=DIM_TBE-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){if(tb_kaart[k+start_].rec==0) {j=k;break;}}
    curs=2+k*3;
  }
  return NO;
}


static etiket()
{
 
  int16 k,form_dat[8],pr_mode,prtnr,maxpos;
  flag cd;
 
  if(stu>2) goto endsr;

  selp_use=NO;
  if(selp_ask()) goto endsr;

  maxpos=fldlen(stu,3);if(maxpos==0) maxpos=30;
  getsysprNew(2,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;

  if(form_dat[7]==5){
    k=form_dat[0]*form_dat[1];
    if(k==0 || k>DIM_LETIK){errnum=13;goto endsr;}
    zero((char *)&tb_etik[0],sizeof tb_etik);tot_etik=0;
    hz_dots=form_dat[2]*11.81; vt_dots=form_dat[3]*11.81;
    lettype=valu_cnv("EUR","EUR",(double)((double)form_dat[2] / (0.204*maxpos)),(double)1.);
    lettype+=1+form_dat[6];
    line_dots=(vt_dots-60)/5;q_hor=form_dat[0];q_vert=form_dat[1];
    x_offset=form_dat[4];y_offset=form_dat[5];
  }
	else{
    if((errnum=prtopen(prtnr,form_dat,6,maxpos,pr_mode,0))!=0) goto endsr;
	}
  scrget(1,6);scrupd(-3,0);
//	p_pdfname("Etiketten",0,0);
  cd=YES; if((stu==1 && lvcd==NO) || (stu==2 && klcd==NO)) cd=NO;
  fasinit(stu);
  FOREVER{
    if(faskeyi(stu,key21,2)) break;
    if(selp_tst()){
      if(form_dat[7]==5){// laser etiketten 
				for(k=0;k<DIM_LETIK;k++){
					if(tb_etik[k]==0){
						tb_etik[k]=*u(stu,1);
						break;
					}
				}
				tot_etik++;
				if(tot_etik>=(q_hor*q_vert)) prt_etik(0);
			}
			else{
				if(cd){
					prttext("<t25>");prtfld(stu,2,-1);nextline();
				}
				de_heer(stu);
				prtifld(fm_us50,nm_dehr,-1);nextline();
				prtfld(stu,4,-1);nextline();
				prtfld(stu,5,-1);prtblank(2);prtfld(stu,6,-1);nextline();
				if(fldlen(stu,7)){
					prtfld(stu,7,-1);nextline();
				}
				prtform(0);
      }
    }
  }
  if(form_dat[7]==5) prt_etik(1);
  prtclose();
 
  endsr:;
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

static initload()
{
 
  fileopen(1);
  fileopen(2);

  sysget( 294,4,def_munt);
  sysget(1854,2,&sys1854);
  sysget(1918,2,&sear_stt);
  sysget(1048,32,&btw_pct[0]);
  sysget(2212,4,talen);
	sysget(3670,2,&sys3670);						
  len2_3=fldlen(2,3);

  pu_6_1=u(6,1);
  pu_2_1=u(2,1);
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
 
static de_heer(stu_)
int16 stu_;
{
  int16 g,j,k,len;

  len=fldlen(stu_,3);if(len>50) len=50;
  zero(nm_dehr,sizeof nm_dehr);
  for(k=0;k<len-1;k++){
    if(*(s(stu_,3)+k)=='*')break;
  }
  if(k==len-1){/* no * */
    copy(s(stu_,3),nm_dehr,len);
  }
  else{
    for(g=k+1;g<len;g++) if(*(s(stu_,3)+g)!=' ') break;
    if(g>=len) copy(s(stu_,3),nm_dehr,len);
    else{
      for(j=len-1;j>=g;j--) if(*(s(stu_,3)+j)>' ') break;
      j=j-g+1;
      copy(s(stu_,3)+g,nm_dehr,j);
      nm_dehr[j++]=' ';
      g=len-j;if(g>(k-1)) g=k-1;
      copy(s(stu_,3),&nm_dehr[j],g);
    }
  }
}

static prt_etik(mode_)
int16 mode_;/* 1= blad moet niet perse vol zijn */
{
  int16 j,k,vt,y_pos;
  int16 form_dat[8],pr_mode,prtnr;
  uint16 mrec_,recs_hor[15];
									
  sysget(3648,2,&sys3648);
  sysget(3650,2,&sys3650);
  mrec_=*u(stu,1);
  getsysprNew(2,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
//	MAG HIER NIET ! p_pdfname("Etiketten",0,0);
  scrget(1,6);scrupd(-3,0);
  if(q_hor>15) q_hor=10;

  while(free>=0 && tot_etik>0){
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) {free=-1;break;}
    prt_string("\x1B\x45");
    for(vt=0;vt<q_vert;vt++){
      y_pos=y_offset+vt*vt_dots;
      zero((char *)&recs_hor[0],sizeof recs_hor);k=0;
      for(j=0;j<q_hor;j++){
				for(k;k<DIM_LETIK;k++) if(tb_etik[k]) break;
				if(k<DIM_LETIK && tb_etik[k]){recs_hor[j]=tb_etik[k]; k++;}
				else recs_hor[j]=0;
      }
      prt_1rij(y_pos,recs_hor);
      for(j=0;j<q_hor;j++){
				if(recs_hor[j]){
					for(k=0;k<DIM_LETIK;k++) if(tb_etik[k]==recs_hor[j]){
						tb_etik[k]=0;tot_etik--;break;
					}
				}
      }
    }
  }
  endsr:;
  *u(stu,1)=mrec_;fasgeti(stu);
}

static prt_1rij(b_y_pos_,recs)
uint16 b_y_pos_,recs[];
{
  int16 jj,hz,x_pos,y_pos;
  int16 code_pos_;
  char p_str_[60];
									
  code_pos_=-1; if(sys3648) code_pos_=0;
  for(jj=0;jj<5;jj++){
    y_pos=b_y_pos_+jj*line_dots;
    zero(p_str_,sizeof p_str_);
    for(hz=0;hz<q_hor;hz++){
      x_pos=x_offset+hz*hz_dots;
      fasinit(stu);
      *u(stu,1)=recs[hz]; if(*u(stu,1)) fasgeti(stu);

      if(jj==code_pos_){
	if(fldlen(stu,2)) scopy(s(stu,2),p_str_,fldlen(stu,2));
	else stcli_d(p_str_,(long)(*u(stu,1)),5,0);
	txt_abs(lettype,x_pos,y_pos,p_str_,"");
      }
#if FLAGJAN
      else if(jj==2+code_pos_){ // geen extra spatie tussen klant en adres
#else 
      else if(jj==1+code_pos_){
#endif
	de_heer(stu);
	scopy(nm_dehr,p_str_,35);
	txt_abs(lettype,x_pos,y_pos,p_str_,"B");
      }
      else if(jj==2+code_pos_){
	if(sys3650 && stu==2){
	  scopy(s(stu,sys3650),p_str_,30);
	  txt_abs(lettype,x_pos,y_pos,p_str_,"");
	} else continue;
      }
      else if(jj==3+code_pos_){
	scopy(s(stu,4),p_str_,30);
	txt_abs(lettype,x_pos,y_pos,p_str_,"");
      }
      else if(jj==4+code_pos_){
	scopy(s(stu,5),p_str_,7);scopy(" ",&p_str_[7],1);
	scopy(s(stu,6),&p_str_[8],23);
	txt_abs(lettype,x_pos,y_pos,p_str_,"");
      }
      else if(jj==5+code_pos_ && fldlen(stu,7)){
	scopy(s(stu,7),p_str_,30);
	txt_abs(lettype,x_pos,y_pos,p_str_,"");
      }
    }
  }
  endsr:;
}

static scopy(ps_,pd_,len_)
char *ps_,*pd_;
int16 len_;
{
  int16 k,sp_;

  sp_=NO;
  for(k=0;k<len_;k++){
    if(sp_==NO){
      if(*(ps_+k)=='\0') sp_=YES;
      else *(pd_+k)=*(ps_+k);
    }
    if(sp_==YES) *(pd_+k)=' ';
  }
}
 

/* print-routine voor inktjet-printer */
/* DjPCL3.mer file 00.01 18/05/95 (c) Jamadata */

static txt_abs(size,x_pos,y_pos,ps_,attr)
char *ps_,*attr;
int16 size, x_pos, y_pos;
{
  int16 len_,stroke_weight, style;
  char und=NO;
 
  len_=0;
  while (*(ps_+len_++)) {}
  CnvJamaChar(ps_,len_,0);

  stroke_weight=0;
  style=0;
  while (*attr) {
    if (*attr=='B') stroke_weight=3;
    else if (*attr=='I') style=1;
    else if (*attr=='U') und=YES;
    attr++;
  }
  mov_abs(x_pos,y_pos);
  sel_prop(size,stroke_weight,style);
  if (und) prt_string("\x1B&d0D");
  prt_string(ps_);
  if (und) prt_string("\x1B&d@");
}
 

static mov_abs(x_pos,y_pos)
int16 x_pos, y_pos;
{
  prt_string("\x1B*p");
  prt_int(x_pos); prt_string("x");
  prt_string("*p");
  prt_int(y_pos); prt_string("Y");
}
 
 
static selp_ask()
{
  int16 key;
  char choice;

  if(selp_stu!=stu) selp_wis();
  selp_stu=stu;

  FOREVER{
    scrget(1,46);scraddpicto(1,0,72,22,4,2,583,0,0,"Maak PDF"); 
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(1,0x0581);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		prt2pdf=NO;if(key==5001){prt2pdf=YES; key=108;} // pdf

    if(key==101) return YES;
    if(key==111) ovlexit(-1);
    if(key==108) {selp_use=YES;break;}
    if(key==109) {selp_use=NO;break;}
    switch(choice){
      case '1': selp_ge=NO;selp_upd(0,choice);break;
      case '2': selp_ge=YES;selp_upd(0,choice);break;
      case '3': selp_le=NO;selp_upd(1,choice);break;
      case '4': selp_le=YES;selp_upd(1,choice);break;
      case '5': selp_upd(2,choice);break;
      case '6': selp_upd(3,choice);break;
      case '7': selp_wis();scrget(1,7);scrupd(-3,0);break;
      default : errnum=34; break;
    }
  }
  return NO;
}

static selp_upd(bfnr,men_keuze)
int16 bfnr;
char men_keuze;
{
  int16 k,curs,z,key;
 
  men_keuze=men_keuze-'1';
  copy(selp_bf[bfnr],s(stu,1),fldlen(stu,0));
  if(stu==1){/* leveranciers */
    curs=2;
		redo_l:;
    scrget(2,6);
    scrinq();
    z=1;
    scrifld(z++,fm_os20,selp_txt[men_keuze]);
    if(lvcd) scrfld(z++,stu,2); else scrofld(z++,stu,1,-1);
		if(bfnr==2 && fldlen(1,200)){
			if(*u(1,200)==1){
				scrchat(z-1,0xB); 
			  scraddpicto(7,z-1,0,0,2,1,70,0,3,"Maak actief");
			}
			else{
				scrchat(z-1,0xFF);
				if(*u(1,200)==0) scraddpicto(7,z-1,0,0,2,1,71,0,4,"Blokkeer");
				else scraddpicto(7,z-1,0,0,2,1,71,0,0,"Blokkeer");
			}
		}
    for(k=3;k<MAXFLD;k++) scrfld(z++,stu,k);
    key=scrupd(curs,0x0080);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5007 && fldlen(2,200)){ // blokkeer
			if(*u(2,200)==0) *u(2,200)=1; else *u(2,200)=0;
			goto redo_k;
		}
  }

  else if(stu==2){/* klanten */
    curs=2;
		redo_k:;
    scrget(2,7);
    scrinq();
    z=1;
    scrifld(z++,fm_os20,selp_txt[men_keuze]);
    if(klcd) scrfld(z++,stu,2); else scrofld(z++,stu,1,-1);
		if(bfnr==2 && fldlen(2,200)){
			if(*u(2,200)==1){
				scrchat(z-1,0xB); 
			  scraddpicto(7,z-1,0,0,2,1,70,0,3,"Maak actief");
			}
			else{
				scrchat(z-1,0xFF);
				if(*u(2,200)==0) scraddpicto(7,z-1,0,0,2,1,71,0,4,"Blokkeer");
				else scraddpicto(7,z-1,0,0,2,1,71,0,0,"Blokkeer");
			}
		}
    for(k=3;k<MAXFLD;k++) scrfld(z++,stu,k);
    key=scrupd(curs,0x0080);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5007 && fldlen(2,200)){ // blokkeer
			if(*u(2,200)==0) *u(2,200)=1; else *u(2,200)=0;
			goto redo_k;
		}
  }

  copy(s(stu,1),selp_bf[bfnr],fldlen(stu,0));
}

static selp_tst()/* 00.03 */
{
  int16 g,k,type,parm,f_len,index;
  char fldtype,*stu_base,*adres,ret;

  if(selp_use==NO) return YES;
  stu_base=s(stu,1);
  for(k=2;k<201;k++){
    f_len=fieldspc(stu,k,&selp_fld,selp_des);
    if(f_len>0){
      fldtype=(selp_des[1] & 0x38)/8;
      switch(fldtype){
	case 0:/* date */
	  type=1;parm=11;
	  break;
	case 1:/*string*/
	  type=2;
	  break;
	case 2:/*num*/
	  type=1;parm=selp_des[1]&7;
	  break;
	case 3:/*bt#*/
	  type=1;parm=3;
	  break;
	case 4:/* rek# */
	  type=3;parm=5;
	  break;
	case 5:/* grb */
	  type=1;parm=3;
	  break;
	default: type=0;break;
      }
      index=selp_fld-stu_base;
      for(g=0;g<4;g++){
	adres=&selp_bf[g][index];
	if(used(adres,f_len)){
	  ret=3;
	  switch(type){
	    case 1: ret=comp_num(adres,selp_fld,parm); break;
	    case 2: ret=comp_str(adres,selp_fld,f_len); break;
	    case 3: ret=comp_byt(adres,selp_fld,f_len); break;
	  }
	  if(ret==3) goto next;
	  if(g==0 && (ret==1 || (selp_ge && ret==0))) goto next;
	  if(g==1 && (ret==2 || (selp_le && ret==0))) goto next;
	  if(g==2 && ret==0) goto next;
	  if(g==3 && ret!=0) goto next;
	  return NO;
	}
	next:;
      }
    }
  }
  return YES;
}

static used(b,len)
char *b;
int16 len;
{
  while(len-->0)
    if(*b++!=0xFE) return YES;
  return NO;
}
 
static comp_num(p1,p2,type)
char *p1, *p2;
int16 type;
{
  int16 ret;
  uint16 jj,mm,dd, oldp2;
 
  if(type==11){
    oldp2=*(uint16 *)p2;
    if(*(uint16 *)p1>=44 && *(uint16 *)p1<=409){
      jddate(*(uint16 *)p2,&jj,&mm,&dd);
      *(uint16 *)p2=datejd(1892,mm,dd);
    }
  }
  switch(type){
    case 0:
      if(*(int16 *)p1 < *(int16 *)p2) ret=1;
      else if(*(int16 *)p1 > *(int16 *)p2) ret=2;
      else ret=0;
      break;
    case 1:
    case 11:
      if(*(uint16 *)p1 < *(uint16 *)p2) ret=1;
      else if(*(uint16 *)p1 > *(uint16 *)p2) ret=2;
      else ret=0;
      if(type==11) *(uint16 *)p2=oldp2;
      break;
    case 3:
      if(*(long *)p1 < *(long *)p2) ret=1;
      else if(*(long *)p1 > *(long *)p2) ret=2;
      else ret=0;
      break;
    case 4:
      if(*(float *)p1 < *(float *)p2) ret=1;
      else if(*(float *)p1 > *(float *)p2) ret=2;
      else ret=0;
      break;
    case 5:
      if(*(double *)p1 < *(double *)p2) ret=1;
      else if(*(double *)p1 > *(double *)p2) ret=2;
      else ret=0;
      break;
    default:
      ret=3;
      break;
  }
  return ret;
}
 
static comp_str(p1,p2,len)
char *p1, *p2;
int16 len;
{
  char b1,b2;
  int16 len1,len2;

  len1=len;len2=len;
  FOREVER{
    FOREVER{
      if(!(b1=*p1++)){len1=-1; break;}/* 0-byte found */
      if(!len1--) break;
      if(b1>='a' && b1<='z') b1=b1-'a'+'A';
      if((b1>='A' && b1<='Z') || (b1>='0' && b1<='9') || (b1=='?')) break;
      if(b1=='*') return 0;
    }
    FOREVER{
      if(!(b2=*p2++)){len2=-1; break;}/* 0-byte found */
      if(!len2--) break;
      if(b2>='a' && b2<='z') b2=b2-'a'+'A';
      if((b2>='A' && b2<='Z') || (b2>='0' && b2<='9')) break;
    }
    if(len1<0 || len2<0){
      if(len1<0 && len2<0) return 0;
      if(len1<0) return 1; else return 2;
    }
    if(b1=='?') b1=b2;
    if(b1<b2) return 1;
    if(b1>b2) return 2;
  }
}
 
static comp_byt(p1,p2,len)
int16 len;
char *p1,*p2;
{
  while(len-->0){
    if(*p1<*p2) return 1;
    if(*p1>*p2) return 2;
    p1++; p2++;
  }
  return 0;
}
 
static selp_wis()
{
  int16 j;

  for(j=0;j<sizeof selp_bf;j++) *(&selp_bf[0][0]+j)=0xFE;
}
static streepje(z)
int16 z;
{
  scrifld(z,fm_os1,"-");
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

static nextline()
{
  free=prtline();
}
					
static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
#if 0
  if(stu_<=2) parmcall[1]=7;          bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3;                                            GEEN ADD
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
