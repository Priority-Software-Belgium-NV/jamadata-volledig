/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH2919GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH2919dat
#define ovlcod BKH2919cod
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

char ovldat[] = "bkh2919  00:02 10/09/09 (c) Jamadata";
/* aanpassen/schrappen klanten en leveranciers via lijst 9.x.L */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define D_LIN_SCR       17
#define DIM_REC         1500
#define MAXFLD          120
						
extern char *s();
extern int16 *i();
static flag geboekt();
extern uint16 *u();
static uint16 hash();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();

static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os36[]  = {7,0x88,36,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os18[]  = {7,0x88,18,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os7[]   = {7,0x88,7,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us65[]  = {7,0xC8,65,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x20,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x20,0};
static char fm_uf5_4[] = {6,0xD4,5,4,0x70,0};
static char fm_of2_1[] = {6,0x94,2,1,0x30,0};
static char fm_of4_1[] = {6,0x94,4,1,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_u_AK[]  = {11,0xC8,1,0,1,0,'A','A','K','K',0};

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

					
static char ram[10000],buf1000[1000];
static char vptekst[100];
static int16 dat_len,ram_recl,hash_len,max_line;
static uint16 hash_val,fact_klt;
static char prt_info,only_info,type_info;

static int16 fkey=2,free,start,kdsp,MaxDefGrb;
static char oldnm[65],manier='A',OnlyBlocked='N',OnlyNoOmzet='N',dsp_txt[80],def_munt[4],dsp_kar[5];
static char fmt[40],fich_nm[100],lev_res[50],werkveld[30];
static float btw_pct[8];
static float Bkhbtwpct[4];
static long DefGrb[30];
static flag lvcd,klcd,cd,chk_btoeg=NO,sys3720;
static uint16 inq_groep=0,inq_lev,inq_art,p_max_grp;
static uint16 stu,getnr,fuval,only_dsp,loc_klt[20];
static float sys3614,net_winst[12];
static flag sgrp_used,slev_used,del_mode,sys2698;
static flag sear_stt,sys3586,sys3588,sys3894,sys3632,sys3876,sys3618;
static uint16 dt_beg,dt_end,inq_klt,max_dfld,sort_key;

static char *fichenm[3]={"Leveranciersfiche","Klantenfiche","Grootboekfiche"};
static char *selp_txt[6]={"Ondergrens (>)","Ondergrens (> of =)",
		"Bovengrens (<)","Bovengrens (< of =)",
		"Gelijk","Niet gelijk"};
									
									
									
static int16 key21;
static uint16 def_qfak,vers_298,lst_recs[10];
static char nm_20[20],nm_dehr[52],taal_i,talen[4],oldtyp;
static char sort_meth,prt_fiche,fiche_per_blad,only_memo,prt_memo;
static int16 selp_stu=0,max_fich;
static char selp_bf[4][1500],selp_des[40],*selp_fld;
static flag selp_use,selp_ge,selp_le,sys1854,sys1816;

static struct{
  uint16 rec;
  char mark_omz;
} tb[DIM_REC];

static struct{
  int16 fld;
  char omschr[20];
} dsp_tab[25];

static int16 def_taal;
 
ovlcod(parmval)
int16 parmval;
{
  retcall=YES;

  stu=parmval; if(stu!=1 && stu!=2 && stu!=3) ovlexit(-1);
  initload();
  if(stu==1) cd=lvcd; 
	else if(stu==2) cd=klcd;
	else if(stu==3) cd=1;
  display();
  ovlexit(-1);
}

static display()
{
  int16 j,k,n,curs,z,z_base_,key,mode_,pos_,dsp_rev_,code_corr_,codelen_,curspos_;
  char codestr_[15],mask_;

  code_corr_=0; if(fldlen(stu,2)>5) code_corr_=fldlen(stu,2)-5;
  manier='A';del_mode=YES;
  FOREVER{
redo_sel:;
		if(selecteer()) break;
    scrget(1,7);scrupd(-3,0);
    zero((char *)&tb[0].rec,sizeof tb);fasinit(stu);
    start=0;max_fich=0;mode_=1;curs=2;getnr=1;
    FOREVER{
      next:;
      if(sort_key!=1 || cd){
				if(faskeyi(stu,sort_key,mode_)) break;  mode_=2;
      }
      else{
				*u(stu,1)=getnr++;fuval=fasgeti(stu);
				if(fuval==46) goto next;
				else if(fuval) break;
      }
			if(OnlyBlocked=='J' && fldlen(stu,200) && *u(stu,200)==0) goto next;
      if(stu<3 && selp_tst()==NO) goto next;
      tb[max_fich].rec=*u(stu,1);
      if(stu<3) tb[max_fich].mark_omz=chk_omzet(*u(stu,1));
      if(geboekt()) tb[max_fich].mark_omz|=0x02;
			if(OnlyNoOmzet=='J' && tb[max_fich].mark_omz){tb[max_fich].mark_omz=0;tb[max_fich].rec=0;}
      else max_fich++;
      if(max_fich>=DIM_REC){errnum=11; break;}
    }
    if(max_fich==0) {errnum=39;goto redo_sel;}
    start=0;curs=2;
    FOREVER{
      redo:;
      scrnum=0; scrget(1,245);z=1;
      scrifld(-z,fm_us30,werkveld);z++;
#if 0
      scrifld(z++,fm_os18,"BKH");
      scrifld(z++,fm_os18,"Stat.");
#endif
      z_base_=z;
      for(j=start;j<start+18;j++){
	if(tb[j].rec==0) break;
	fasinit(stu); *u(stu,1)=tb[j].rec;fasgeti(stu);
	dsp_rev_=NO; if(del_mode && tb[j].mark_omz&0x80) dsp_rev_=YES;
	zero(fich_nm,sizeof fich_nm);pos_=0;
	if(stu==3){
		 zero(codestr_,sizeof codestr_);
		 grb_deco(codestr_,l(3,2)); codelen_=8;
	}
	else{
  	if(cd){
			codelen_=fldlen(stu,2);copy(s(stu,2),codestr_,codelen_);
		}
		else{
			codelen_=5; zero(codestr_,sizeof codestr_);
			stcli_d(codestr_,(long)(*u(stu,1)),5,1);
		}
	}
	if(sort_key==1){
	  pos_+=add_str(&fich_nm[pos_],codestr_,codelen_);fich_nm[pos_++]=' ';
	  pos_+=add_str(&fich_nm[pos_],s(stu,3),-fldlen(stu,3));
		if(stu<3){
			pos_+=add_str(&fich_nm[pos_]," - ",3);
			pos_+=add_str(&fich_nm[pos_],s(stu,4),-fldlen(stu,4));
			pos_+=add_str(&fich_nm[pos_]," - ",3);
			pos_+=add_str(&fich_nm[pos_],s(stu,6),-fldlen(stu,6));
		}
	}
	else {
	  pos_+=add_str(&fich_nm[pos_],s(stu,3),-fldlen(stu,3));
		if(stu<3){
			pos_+=add_str(&fich_nm[pos_]," - ",3);
			pos_+=add_str(&fich_nm[pos_],s(stu,4),-fldlen(stu,4));
			pos_+=add_str(&fich_nm[pos_]," - ",3);
			pos_+=add_str(&fich_nm[pos_],s(stu,6),-fldlen(stu,6));fich_nm[pos_++]=' ';
		}
	  if(pos_<=(65-codelen_)) pos_+=add_str(&fich_nm[pos_],"",65-codelen_-pos_);
	  else if(pos_>65-codelen_) pos_=65-codelen_;
	  pos_+=add_str(&fich_nm[pos_],codestr_,codelen_);fich_nm[pos_++]=' ';
	}
	scrifld(z++,fm_us65,fich_nm);
	if(tb[j].mark_omz&0x80) scrchat(z-1,0x08); 
	else if(tb[j].mark_omz&0x10) scrchat(z-1,0x09); 
	else scrchat(z-1,0xFF);
	pos_=j-start;
	if(tb[j].mark_omz&0x02){scrifld(z++,fm_os3," JA");mask_=0x02;}
	else{scrifld(z++,fm_os3,"NEE");mask_=0x00;}
	if(dsp_rev_) mask_|=0x08;scrchat(z-1,mask_);
	if(tb[j].mark_omz&0x01){scrifld(z++,fm_os3," JA");mask_=0x02;}
	else{scrifld(z++,fm_os3,"NEE");mask_=0x00;}
	if(dsp_rev_) mask_|=0x08;scrchat(z-1,mask_);
      }
      redo_upd:;
      key=scrupd(curs,0x4387);curs=2;curspos_=fldcurs;
      if(key==101) break;
 
      switch(key){
	case 8       : if(curspos_<=z_base_) curs=curspos_-1;/* pijl opmhoog */
		       else curs=curspos_-3;
		       if(curs<1) curs=1;
		       break;
	case 9       : if(curspos_<z_base_) curs=curspos_+1;/* pijl omlaag */
		       else curs=curspos_+3;
		       break;
	case 12      :                                              /* PgUp */
	case 102     : start-=18; if(start<0) start=0;
		       curs=z_base_;
		       break;
	case 13      :                                              /* PgDn */
	case 103     : start+=18;if(start>=max_fich-18) start=max_fich-18;
		       if(start<0) start=0;
		       curs=z_base_;
		       break;
	case 10      : start=0;/* HOME */
		       break;
	case 11      : start=max_fich-18; if(start<0) start=0;/* END */
		       break;

	case 18      : if(curspos_<z_base_){/* ENTER */
			 exec_work();curs=curspos_+1;goto redo;
		       }
		       else curs=curspos_+3;
		       break;
	case 108     : if(curspos_>=z_base_){/* detail*/
			 n=(curspos_-2)/3; n+=start;
			 curs=curspos_;
			 if(tb[n].rec){
			   fasinit(stu);*u(stu,1)=tb[n].rec;fasgeti(stu);
			   fichupd(1); tb[n].mark_omz|=0x10;
			 }
		       }
		       break;
	case 109     : if(curspos_>=z_base_ && CheckPw(1,11,0)){// schrappen
			 n=(curspos_-2)/3; n+=start;
			 curs=curspos_;
			 if(tb[n].rec && (tb[n].mark_omz & 0x02)==0 && (tb[n].mark_omz & 0x04)==0){
			   if(tb[n].mark_omz & 0x80) tb[n].mark_omz&=0x7F;
			   else tb[n].mark_omz|=0x80;
			 }
		       }
		       break;
	case 112 :
		    if(DisplayWarning("Wenst echt ALLE fiches te markeren om te schrappen? ",61,1)==YES) {
					for(j=0;j<max_fich;j++){
	  				if(tb[j].rec==0) break;
						if((tb[j].mark_omz & 0x02)==0 && (tb[j].mark_omz & 0x04)==0) tb[j].mark_omz|=0x80;
					}
				}
				break;
	default      : curs=curspos_; break;
      }
    }
    if(key==101 && del_mode){
      n=0;
      for(k=0;k<max_fich;k++) if(tb[k].rec && tb[k].mark_omz&0x80) n++;
      if(n){
				fasunlck(-2);
				copy("Wenst U deze",dsp_txt,12);stcli_d(&dsp_txt[12],(long)n,4,1);
				copy(" fiches te schrappen ????",&dsp_txt[16],30);
				if(scr_ok(dsp_txt)==YES) kill_fich(max_fich);
				fasunlck(-1);
      }
    }
  }

  endsr:;
}

static selecteer()
{
  int16 key,z,curs=2;
 
  FOREVER{
    redo:
    scrget(1,246);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_u_AK,&manier);
		if(fldlen(stu,200)) scrifld(z++,fm_uJN,&OnlyBlocked);
		scrifld(z++,fm_uJN,&OnlyNoOmzet);
    key=scrupd(curs,0x281);curs=2;
    if(key==101) return YES;
    if(key==111) ovlexit(*u(25,4));
    sort_key=2; if(manier=='K') sort_key=1;
    if(key==108){
      del_mode=YES; break;
    }
  }
  selp_use=NO;
  if(stu<3 && selp_ask()) return YES;
  return NO;
}

static chk_omzet(rec_)
uint16 rec_;
{
  int16 fld_,omz_=0,key_;
 
  fld_=2;key_=11; if(stu==1){fld_=12;key_=21;}
  if(omz_==0 && fldlen(60,fld_)){
    fasinit(60);*l(60,fld_)=rec_;
    if(faskeyi(60,key_,1)==0){
      if(*l(60,fld_)==rec_) omz_=YES;
    }
  }
  fld_=3;key_=1; if(stu==1){fld_=36;}
  if(omz_==0 && fldlen(8,1) && fldlen(8,fld_)){
    fasinit(8);*u(8,3)=rec_;
    if(faskeyi(8,1,1)==0){
      if(*u(8,3)==rec_){ 
				if(stu==1){
					if(fldlen(8,36) && *u(8,36)) omz_=YES;
				}
				else if(stu==2){
					if(fldlen(8,36)==0 || *u(8,36)==0) omz_=YES;
				}
			}
	  }
  }

  if(omz_==0 && stu==2 && fldlen(9,2)){
    fasinit(9);*u(9,2)=rec_;
    if(faskeyi(9,2,1)==0){
      if(*u(9,2)==rec_) omz_=YES;
    }
  }
  if(omz_==0 && stu==2 && fldlen(16,10)){
    fasinit(16);*l(16,10)=rec_;
    if(faskeyi(16,2,1)==0){
      if(*l(16,10)==rec_) omz_=YES;
    }
  }
	if(omz_==0 && stu==1 && fldlen(16,15)){
    fasinit(16);*l(16,15)=rec_;
    if(faskeyi(16,2,1)==0){
      if(*l(16,15)==rec_) omz_=YES;
    }
  }
	if(stu==1 && fldlen(6,7)){
    fasinit(6);*u(6,7)=rec_;
    if(faskeyi(6,4,1)==0){
      if(*u(6,7)==rec_) omz_+=4;
    }
  }
  return	omz_;
}

static kill_fich(max_)
int16 max_;
{
  int16 z,jj;

  scrnum=0;scrget(1,170); z=1;
  scrifld(z,fm_os63,"                    Schrappen van aanverwante fiches ");
  scrchat(z,0x2);
  z=5;
  if(stu==1){
		z=kil_bew(z,stu,7,11);
    z=kil_bew(z,stu,86,5);
    z=kil_bew(z,stu,11,2);
    z=kil_bew(z,stu,13,2);
		z=kil_bew(z,stu,16,15);
    z=kil_bew(z,stu,22,3);
    z=kil_bew(z,stu,60,12);
  }
  else if(stu==2){
		z=kil_bew(z,stu,7,11);
    z=kil_bew(z,stu,86,5);
    z=kil_bew(z,stu,62,2);
    z=kil_bew(z,stu,22,3);
    z=kil_bew(z,stu,8,3);
    z=kil_bew(z,stu,9,2);
		z=kil_bew(z,stu,16,10);
    z=kil_bew(z,stu,60,2);
		z=kil_bew(z,stu,95,2);
  }
  for(jj=0;jj<max_fich;jj++){
    if(tb[jj].rec && (tb[jj].mark_omz&0x80) && (tb[jj].mark_omz&0x02)==0){
      fasinit(stu);*u(stu,1)=tb[jj].rec;fasgetu(stu); faskill(stu);
    }
  }
  fasinfo(stu,101);
}
 
static kil_bew(z,mstu_,bstu_,nr_)
int16 z,mstu_,bstu_,nr_;
{

  int16 g,mode_,jj,len1_;
  uint16 mrec_,*prec_,dcnt_,*pu1_;
  long *lprec_,*pl1_;
	long n;

  if(fldlen(bstu_,1)==0) goto endsr;
  if(fldlen(bstu_,nr_)==0) goto endsr;
  switch(bstu_){
    case 7 : fileopen(7);
						 scrifld(z++,fm_os63,"Schrappen bestaande documenten ...");
						 lprec_=l(7,nr_); break;
    case 8 : if(fldlen(8,1)==0) break;
/* fileopen(8); */
	     scrifld(z++,fm_os63,"Schrappen bestaande leveringsbons ...");
	     prec_=u(8,nr_); break;
    case 9 :/* fileopen(9); */
	     scrifld(z++,fm_os63,"Schrappen bestaande prijsafspraken/omzetfiches ...");
	     prec_=u(9,nr_); break;
    case 11: prec_=u(11,nr_);
	     scrifld(z++,fm_os63,"Schrappen bestaande aankoopfiches ...");
	     break;
    case 13: prec_=u(13,nr_);
						 scrifld(z++,fm_os63,"Schrappen bestaande peppolkoppelingen ...");
						 break;
		case 16: fileopen(13);
	     scrifld(z++,fm_os63,"Schrappen bestaande historieken ...");
	     lprec_=l(16,nr_); break;
    case 22:/* fileopen(15); */
	     scrifld(z++,fm_os63,"Schrappen bestaande info ...");
	     prec_=u(22,nr_); break;
    case 60:/* fileopen(14); */
	     scrifld(z++,fm_os63,"Schrappen bestaande statistieken ...");
	     lprec_=l(60,nr_); break;
    case 62: prec_=u(62,nr_);
	     scrifld(z++,fm_os63,"Schrappen bestaande klanten-memo ...");
	     break;
    case 86:/* fileopen(10); */
	     scrifld(z++,fm_os63,"Schrappen bestaande boekingen in jaararchief ...");
	     prec_=u(86,nr_); break;
   case 95: fileopen(9);
			 scrifld(z++,fm_os63,"Schrappen bestaande verhuurfiches ...");
			 prec_=u(95,nr_); break;
    default: break;
  }
  len1_=fldlen(bstu_,1); pu1_=u(bstu_,1);pl1_=l(bstu_,1);
  n=0;scrnum=0;fasinit(bstu_); dcnt_=0;
  FOREVER{
		next:;
    if(len1_==4) *pl1_=++n; else *pu1_=++n;
    if((n%500)==0) {scrifld(24,fm_ol8,&n);scrupd(-3,0);}
    g=fasgeti(bstu_);
    if(g==47)break;
    if(g!=46){  	/* deleted record */
			if(bstu_==7 && *u(7,10)!=mstu_) goto next;
      for(jj=0;jj<max_fich;jj++){
				if(tb[jj].rec==0 || (tb[jj].mark_omz&0x80)==0) continue;
				mrec_=tb[jj].rec;
				if(bstu_==86){
					mrec_+=(stu-1)*30000;
				}
				switch(bstu_){
					case 7: if(*lprec_==mrec_){faskill(7); dcnt_++;}
					 break;
					case 8 : if(*prec_!=mrec_) break;
						 if(stu==1 && (fldlen(8,36)==0 || *u(8,36)==0)) break;
						 if(stu==2 && fldlen(8,36) && *u(8,36)) break;
						 fasinit(58);*u(58,2)=*u(8,1);mode_=1;
						 FOREVER{
							 if(faskeyu(58,1,mode_)) break; mode_=2;
							 if(*u(58,2)!=*u(8,1)) break;
							 faskill(58);
						 }
						 faskill(8); dcnt_++;
						 break;
					case 9 : if(*prec_==mrec_){faskill(9);dcnt_++;}
						 break;
					case 11: if(*prec_==mrec_){faskill(11);dcnt_++;}
						 break;
					case 13: if(*prec_==mrec_){faskill(13);dcnt_++;}
					 break;
				  case 16: if(*lprec_==mrec_){faskill(16); dcnt_++;}
					 break;
					case 22: if(*i(22,2)==mstu_ &&  *prec_==mrec_){faskill(22);dcnt_++;}
						 break;
					case 60: if(*lprec_==mrec_){faskill(60);dcnt_++;}
						 break;
					case 62: if(*prec_==mrec_){faskill(62);dcnt_++;}
						 break;
					case 86: if(*prec_==mrec_){faskill(86);dcnt_++;}
						 break;
			    case 95: if(*prec_==mrec_){faskill(95);dcnt_++;}
					 break;
					default: break;
				}
      }
    }
  }
	if(dcnt_){scraddfield(z-1+50,50,z-2,0xB); scrifld(z-1+50,fm_ou5,&dcnt_);}
	scrupd(-3,0);
  fasflush(0);
endsr:;
	return z;
}
 
static fichupd(mode)
int16 mode;
{
  int16 k,curs,curs_taal,key,z,dcurs_,curspos_,kleur_;
  uint16 fakklnr;
  char *p_stu_3;
	long old_grb_;
 
	only_dsp=NO; if(sys2698 && mode==1) only_dsp=YES;
  p_stu_3=s(stu,3);
  taal_i='\0';
  FOREVER{
    curs=2;
    if(stu==1){/* leveranciers */
      redo_l:
      scrget(2,6);z=1;
/*  dsp_i_flag(); */
      scrfld(z++,25,1);
      if(lvcd) scrfld(z++,1,2); else scrofld(z++,1,1,-1);
      for(k=3;k<16;k++) scrfld(z++,1,k);
      curs_taal=z;
      taal_upd(z++,16);
      for(k=17;k<MAXFLD;k++) scrfld(z++,1,k);
#if 0
      if(mode==10){print_screen(NO);return YES;}
#endif
      dcurs_=curs; if(only_dsp) dcurs_=-1;
      key=scrupd(dcurs_,0x07A9);curs=2;curspos_=fldcurs;
      if(key==15 && only_dsp && CheckPw(1,11,0)){only_dsp=NO;goto redo_l;}
      if(key==106){
	if(mode==2) return NO;
	else return YES;
      }
      if(mode==2 && key==111 && lst_recs[stu]){
	fasinit(stu);*u(stu,1)=lst_recs[stu];fasgeti(stu);
	zero(s(stu,1),s(stu,3)-s(stu,1));
      }
      k=*p_stu_3;
      if(key==101 && k=='\0') return NO;
#if 0
      if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo_l;}
#endif
      if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;curs=3;goto redo_l;}
      if(lvcd && *s(1,2)=='\0') {errnum=38;curs=2;goto redo_l;}
      if(taal_chk(16)) {curs=curs_taal;goto redo_l;}
#if 0
      if(chk_intra){
	if(fldlen(1,35)) if(*s(1,35)=='\0'){errnum=38;curs=35;goto redo_l;}
	if(fldlen(1,36)) if(*i(1,36)==0){errnum=38;curs=36;goto redo_l;}
	if(fldlen(1,38)) if(*i(1,38)==0){errnum=38;curs=38;goto redo_l;}
      }
      if(key==109 && fldlen(1,121)) {lev_dfgrb();goto redo_l;}
			if(key==110 && fldlen(1,125)) {DisplayMemo(stu);goto redo_l;}
      if(key==172) {print_screen(YES); goto redo_l;}
#endif
      if(key==112 && *u(stu,1)) {dsp_info(); goto redo_l;}
      if(key!=108 && key!=101) goto redo_l;
    }

    else if(stu==2){/* klanten */
      if(fldlen(2,51)){ // facturatieklant
				selp_stu=0;
				if(*u(2,51)==0) selp_bf[1][0]='\0';
				else{
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					*u(2,1)=*u(2,51);
					if(fasgeti(2)) {selp_bf[1][0]='\0';selp_bf[1][50]='\0';}
					else {
						copy(s(2,3),&selp_bf[1][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[1][50],fldlen(2,3));
					}
					copy(selp_bf[0],s(2,1),fldlen(2,0));
				}
      }
      if(fldlen(2,52)==2){ // relatieklant
				selp_stu=0;
				if(*u(2,52)==0) selp_bf[2][0]='\0';
				else{
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					*u(2,1)=*u(2,52);
					if(fasgeti(2)) {selp_bf[2][0]='\0';selp_bf[2][50]='\0';}
					else {
						copy(s(2,3),&selp_bf[2][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[2][50],fldlen(2,3));
					}
					copy(selp_bf[0],s(2,1),fldlen(2,0));
				}
      }
      if(stu==2 && fldlen(62,1)) {
	fasinit(62);*u(62,2)=*u(2,1);faskeyi(62,1,0);
      }
redo_k:
			if(fldlen(2,200)){
				if(*u(2,200)) ConLook(1); else   ConLook(0);
			}
      scrget(2,7); z=1;
/* dsp_i_flag(); */

      scrfld(z++,25,1);
      if(klcd) scrfld(z++,2,2); else scrofld(z++,2,1,-1);
			if(fldlen(2,200) && mode==1){
				if(*u(2,200)==1) scrchat(z-1,0xB); else scrchat(z-1,0xFF);
				if(!only_dsp){
					if(*u(2,200)==1) scraddpicto(4,z-1,0,0,2,1,70,0,4,"Maak actief"); else scraddpicto(4,z-1,0,0,2,1,71,0,3,"Blokkeer");
				}
			}
			if(fldlen(2,195) && !only_dsp){
				if(*s(2,195)=='J') scraddpicto(11,z-1,2,0,2,1,32,0,4,"Mag NIET bestellen via webshop"); else scraddpicto(11,z-1,2,0,2,1,32,0,3,"Mag bestellen via webshop");
			}
			scrfld(z++,2,3);
      if(*(s(2,3)+fldlen(2,3)-1)=='!') scrchat(z-1,0xB); else scrchat(z-1,0xFF);
			if(!only_dsp){
  			if(*(s(2,3)+fldlen(2,3)-1)!='!') scraddpicto(2,z-1,0,0,2,1,48,0,3,"Markeer"); 
    		else scraddpicto(2,z-1,0,0,2,1,86,0,4,"Normaal"); 
			}
      for(k=4;k<7;k++) scrfld(z++,2,k);
			if(!only_dsp && fldlen(29,1)) scraddpicto(8,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
			ShowGoogleMapsButton(24,z-1,2,0,2,1,2); 
			for(k=7;k<=10;k++) scrfld(z++,2,k);
			if(fldlen(2,10)){
				if(*l(2,10)==0 || *l(2,10)==BTWNR_OFFSET) scrchat(z-1,0xFF);
				else if (*(s(2,10)+3) & 0x40){ // if(*l(2,10)>=BTWNR_OFFSET){
					scrchat(z-1,0xB);scraddpicto(10,z-1,4,0,2,1,86,0,4,"Maak BTW-plichtig"); 
				}
				else{
					scrchat(z-1,0xFF);scraddpicto(10,z-1,4,0,2,1,76,0,3,"Maak NIET BTW-plichtig"); 
				}
			}
      for(k=11;k<16;k++) scrfld(z++,2,k);
			scrfld(z++,2,16);if(fldlen(2,16)) scraddpicto(3,z-1,0,0,2,1,105,0,3,"Controleer IBAN/BIC"); 
      for(k=17;k<24;k++) scrfld(z++,2,k);
      curs_taal=z;
			taal_upd(z++,24);
      scrfld(z++,2,25);
      if(fldlen(2,27)){scrfld(-z,2,26);z++;}
      else scrfld(z++,2,26);
      for(k=27;k<51;k++) scrfld(z++,2,k);
      if(fldlen(2,51)>0) scrifld(z++,fm_us40,selp_bf[1]); else z++;
			if(fldlen(2,52)==2) scrifld(z++,fm_us40,selp_bf[2]); else scrfld(z++,2,52); // relatieadres
      for(k=53;k<MAXFLD;k++) scrfld(z++,2,k);
			//if(!only_dsp && fldlen(2,121)){
			//	kleur_=3;
			//	for(k=0;k<10;k++){
			//		if(fldlen(2,121+k) && *s(2,121+k)=='J') {kleur_=4;break;}
			//	}
			//	scraddpicto(1,21,0,0,2,1,101,0,kleur_,"Email-instellingen"); 
			//}
      dcurs_=curs; if(only_dsp) dcurs_=-1;
      key=scrupd(dcurs_,0x07A9);curs=2;curspos_=fldcurs;
			if(fldlen(2,200)) ConLook(0);
			if ((key/0x100)==1) key=(key&0xFF)+5000;
//			if(key==5001){DisplayEmailSettings(stu);goto redo_k;}
			if(key==5002){
				if(*(s(2,3)+fldlen(2,3)-1)=='!') *(s(2,3)+fldlen(2,3)-1)=' ';
				else{
					*(s(2,3)+fldlen(2,3)-1)='!';
				}
				goto redo_k;
			}
			if(key==5003){IbanTools(s(2,16),s(2,17),s(2,12),1);goto redo_k;}
			if(key==5004 && fldlen(2,200)){ // blokkeer
				if(*u(2,200)) *u(2,200)=0; else *u(2,200)=1;
				goto redo_k;
			}
			if(key==5008){
				fasinit(29);
				if(*s(2,6)) copy(s(2,6),s(29,3),fldlen(2,6));
				else copy(s(2,5),s(29,3),fldlen(2,5));				
				if(search(29,0)==0){ copy(s(29,2),s(2,5),fldlen(2,5)); copy(s(29,3),s(2,6),fldlen(2,6));}
				else curs=6;
				goto redo_k;
			}
      if(key==15 && only_dsp && CheckPw(1,11,0)){only_dsp=NO;goto redo_k;}
      if(key==106){
	if(mode==2) return NO;
	else return YES;
      }
			if(key==5010){
				if (*(s(2,10)+3) & 0x40) *(s(2,10)+3)  &= 0xBF; else *(s(2,10)+3)  |= 0x40;
//				if(*l(2,10)>=BTWNR_OFFSET) *l(2,10)-=BTWNR_OFFSET;
//				else *l(2,10)+=BTWNR_OFFSET;
				goto redo_k;
			}	
			if(key==5011 && fldlen(2,195) && !only_dsp){
				if(*s(2,195)=='J') *s(2,195)='N'; 
				else{
					if(*s(2,21)){
						*s(2,195)='J';
	//					if(fldlen(2,2) || fldlen(2,196)) DisplayExcludeLev();
					}
					else {curs=21;errnum=38;}
				}
				goto redo_k;
			}	
      if(mode==2 && key==111 && lst_recs[stu]){
	fasinit(stu);*u(stu,1)=lst_recs[stu];fasgeti(stu);
	zero(s(stu,1),s(stu,3)-s(stu,1));
      }
      if(fldlen(2,27)){
				k=*s(2,26)-'0';if(k<0 || k>9) k=0;
				if(fldlen(6,PrNrs[k])==0) k=0;
				if(*s(2,26)=='A') copy("*AKpr*",s(2,27),fldlen(2,27));
				else copy(&vptekst[k*10],s(2,27),fldlen(2,27));
      }
			if(key==18){curs=curspos_+1;goto redo_k;}
      k=*p_stu_3;
      if(key==101 && k=='\0') return NO;
 //     if(mode!=1 && key==104) {get_newcode();curs=curspos_;goto redo_k;}
      if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;curs=3;goto redo_k;}
      if(klcd && *s(2,2)=='\0') {errnum=38;curs=2;goto redo_k;}
      if(taal_chk(24)) {curs=curs_taal;goto redo_k;}
      if(fldlen(2,51)){
				if(selp_bf[1][0]=='\0') {*u(2,51)=0;selp_bf[1][50]='\0';}
				else if(cmpstr(&selp_bf[1][0],&selp_bf[1][50],fldlen(2,3))){
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					fasinit(2);
					copy(&selp_bf[1][0],s(2,3),fldlen(2,3));
					k=search(2,0); if(k==YES && errnum==0) errnum=39;
					if(!errnum){
						copy(s(2,3),&selp_bf[1][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[1][50],fldlen(2,3));
					}
					fakklnr=*u(2,1);
					copy(selp_bf[0],s(2,1),fldlen(2,0));
					*u(2,51)=fakklnr;
					if(errnum) {curs=51;goto redo_k;}
	
				}
      }
      if(fldlen(2,52)==2){ // relatieklant
				if(selp_bf[2][0]=='\0') {*u(2,52)=0;selp_bf[2][50]='\0';}
				else if(cmpstr(&selp_bf[2][0],&selp_bf[2][50],fldlen(2,3))){
					copy(s(2,1),selp_bf[0],fldlen(2,0));
					fasinit(2);
					copy(&selp_bf[2][0],s(2,3),fldlen(2,3));
					k=search(2,0); if(k==YES && errnum==0) errnum=39;
					if(!errnum){
						copy(s(2,3),&selp_bf[2][0],fldlen(2,3));
						copy(s(2,3),&selp_bf[2][50],fldlen(2,3));
					}
					fakklnr=*u(2,1);
					copy(selp_bf[0],s(2,1),fldlen(2,0));
					*u(2,52)=fakklnr;
					if(errnum) {curs=52;goto redo_k;}
	
				}
      }
    //  if(chk_intra){
				//if(fldlen(2,74)) if(*s(2,74)=='\0'){errnum=38;curs=74;goto redo_k;}
				//if(fldlen(2,75)) if(*i(2,75)==0){errnum=38;curs=75;goto redo_k;}
				//if(fldlen(2,77)) if(*i(2,77)==0){errnum=38;curs=77;goto redo_k;}
    //  }
			if(fldlen(stu,16)>30 && *s(stu,16)){
				if(k=IbanTools(s(stu,16),s(stu,17),s(stu,12),0)) {curs=18+k-1; goto redo_k;} 
		  }
//			if(key==109 && len2_120) {bst_inp();goto redo_k;}
      if(key==110 && fldlen(62,1)) {
	if(ovltest(2922)) ovlcall(2922,1); else DisplayMemo(stu);
	goto redo_k;
      }
      if(key==112 && *u(stu,1)) {dsp_info(); goto redo_k;}
      if(key!=5025 && key!=5026 && key!=108 && key!=101) goto redo_k;
    }
    else if(stu==3){/* grootboek */
      if(*s(3,4)=='\0')*s(3,4)='N';
      if(*s(3,5)=='\0')*s(3,5)='J';
      if(*s(3,6)=='\0')*s(3,6)='0';
      if(*s(3,7)=='\0')*s(3,7)='0';
      if(*s(3,10)=='\0')*s(3,10)='0';
      if(*s(3,11)=='\0')*s(3,11)='J';
      old_grb_=*l(3,2);
      redo_g:
      scrget(1,8);
			if(mode==2 && lst_recs[stu]) scraddpicto(10,0,74,2,4,2,532,0,0,"Kopieer vorige rekening"); 
      z=1;
      scrfld(z++,25,1);
      for(k=2;k<=7;k++) scrfld(z++,3,k);
      for(k=0;k<4;k++) scrifld(z++,fm_of2_1,&Bkhbtwpct[k]);
      for(k=8;k<=13;k++) scrfld(z++,3,k);
      if(fldlen(4,48)) scrfld(z++,3,14); else streepje(z++);
      z+=15;
      for(k=32;k<52;k++) scrfld(z++,3,k);
      dcurs_=curs; if(only_dsp) dcurs_=-1;
      key=scrupd(dcurs_,0x04A1);curs=2;curspos_=fldcurs;
			if ((key/0x100)==1) key=(key&0xFF)+5000;
      if(key==15 && only_dsp && CheckPw(1,11,0)){only_dsp=NO;goto redo_g;}
      if(key==106){
				if(mode==2) return NO;
				else return YES;
      }
      if(mode==2 && (key==111 || key==5010) && lst_recs[stu]){
				fasinit(stu);*u(stu,1)=lst_recs[stu];fasgeti(stu);
				zero(s(stu,1),s(stu,2)-s(stu,1));
      }
      k=*p_stu_3;
      if(key==101 && k=='\0') return NO;
      if(k<'A' || k>'z' || (k>'Z' && k<'a')) {errnum=30;curs=3;goto redo_g;}
      if(*l(3,2)==0) {errnum=38;curs=2;goto redo_g;}
      if(*s(3,4)!='J' && *s(3,4)!='N') {errnum=34;curs=4;goto redo_g;}
      if(*s(3,5)!='J' && *s(3,5)!='N') {errnum=34;curs=5;goto redo_g;}
      if(*s(3,6)=='\0')*s(3,6)='0';
      if(*s(3,7)=='\0')*s(3,7)='0';
      if(*s(3,11)=='\0')*s(3,11)='J';
      if(*s(3,10)=='\0')*s(3,10)='0';
      if(*s(3,5)=='J'){
				if(*s(3,10)!='0') {errnum=22;curs=13;goto redo_g;}
      }
      else{
				if(*s(3,10)=='0') {errnum=23;curs=13;goto redo_g;}
      }
      if(mode==1 && old_grb_!=*l(3,2)){
				if(geboekt()) {errnum=60;goto redo_g;}
      }
      if(key!=108 && key!=101) goto redo_g;
    }
    if(mode==1){
      if(only_dsp) goto no_upd;
      errnum=fasupd(stu); if(stu<10) lst_recs[stu]=*u(stu,1);
      if(stu==2 && fldlen(62,1)){
	*u(62,2)=*u(2,1);
	if(*u(62,1)) fasupd(62); else fasadd(62);
      }
      no_upd:;
      fasflush(0);
    }
    else if(mode==2 || mode==3){
      errnum=fasadd(stu); if(stu<10) lst_recs[stu]=*u(stu,1);
      if(stu==3){
	if(errnum==0 && *u(3,1)>=5500) {faskill(3);errnum=9;}
      }
      if(stu==2 && fldlen(62,1)){
	*u(62,2)=*u(2,1); fasadd(62);
      }
      fasflush(0);
    }
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
  return YES;
}
 
static DisplayMemo(stu_)
int16 stu_;
{
  int16 curs=2,dcurs_;
  int16 z,k,key;
					
  FOREVER{
    redo:;
    scrget(2,122); z=1;
    scrofld(z++,stu_,3,-1);
		if(stu_==1){
			for(k=125;k<128;k++) scrfld(z++,1,k);
		}
		else{
      for(k=5;k<10;k++) scrfld(z++,62,k);
		}
    dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0x80);
    if(key==15 && only_dsp && CheckPw(1,11,0)){only_dsp=NO;goto redo;}
    if(key==108) break;
  }
}

static selp_ask()
{
  int16 key;
  char choice;

  if(selp_stu!=stu) selp_wis();
  selp_stu=stu;

  FOREVER{
    scrget(1,46);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(1,0x0581);
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

static taal_upd(z,fld_)
int16 z,fld_;
{
  if(fldlen(stu,fld_)!=1) scrfld(z,stu,fld_);
  else{
    if(taal_i=='\0' && *s(stu,fld_)!=0xFE){
      if(*s(stu,fld_)>=4) *s(stu,fld_)=0;
      taal_i=talen[*s(stu,fld_)];
    }
    scrifld(z,fm_us1_U,&taal_i);
  }
}

static taal_chk(fld_)
int16 fld_;
{
  int16 k;
									
  if(fldlen(stu,fld_)==1){
    for(k=0;k<4;k++) if(taal_i==talen[k]) {*s(stu,fld_)=k;break;}
    if(k==4 && taal_i!='\0') {errnum=34;return YES;}
  }
  return NO;
}

static selp_upd(bfnr,men_keuze)
int16 bfnr;
char men_keuze;
{
  int16 k,curs,z,curs_taal,key;
 
  men_keuze=men_keuze-'1'; taal_i='\0';
  copy(selp_bf[bfnr],s(stu,1),fldlen(stu,0));
  if(stu==1){/* leveranciers */
    curs=2;
    redo_l:;
    scrget(2,6); z=1;
    scrinq();
    z=1;
    scrifld(z++,fm_os20,selp_txt[men_keuze]);
    if(lvcd) scrfld(z++,stu,2); else scrofld(z++,stu,1,-1);
    for(k=3;k<16;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,16);
    for(k=17;k<MAXFLD;k++) scrfld(z++,stu,k);
    scrupd(curs,0x0080);
    if(taal_chk(16)) {curs=curs_taal;goto redo_l;}
  }

  else if(stu==2){/* klanten */
    curs=2;
    redo_k:;
    scrget(2,7); z=1;
    scrinq();
    z=1;
    scrifld(z++,fm_os20,selp_txt[men_keuze]);
    if(klcd) scrfld(z++,stu,2); else scrofld(z++,stu,1,-1);
		if(bfnr==2 && fldlen(2,195)){
			if(*s(2,195)=='J'){
				scraddpicto(11,z-1,2,0,2,1,32,0,4,"Mag NIET bestellen via webshop");
			}
			else{
				if(*s(2,195)!='N') scraddpicto(11,z-1,2,0,2,1,32,0,0,"Mag bestellen via webshop");
				else scraddpicto(11,z-1,2,0,2,1,32,0,3,"Mag bestellen via webshop");
			}
		}
    for(k=3;k<24;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,24);
    for(k=25;k<MAXFLD;k++) scrfld(z++,stu,k);
    key=scrupd(curs,0x0080);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5011 && fldlen(2,195) && !only_dsp){
			if(*s(2,195)=='J') *s(2,195)='N';  else *s(2,195)='J';
			goto redo_k;
		}	
    if(taal_chk(24)) {curs=curs_taal;goto redo_k;}
  }
  copy(s(stu,1),selp_bf[bfnr],fldlen(stu,0));
}

static selp_tst()/* 00.04 */
{
  int16 g,k,type,parm,f_len,index;
  char fldtype,*stu_base,*adres,ret;

  if(selp_use==NO) return YES;
  stu_base=s(stu,1);
  for(k=2;k<201;k++){
    f_len=fieldspc(stu,k,&selp_fld,selp_des);
    if(f_len>0){
      fldtype=(selp_des[1] & 0x38)/8;
      if((stu==2 && k==24) || (stu==1 && k==16)) fldtype=6;
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
				case 6:
					type=4;
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
						case 4: ret=comp_taa(adres,selp_fld,f_len); break;
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

static comp_taa(p1,p2,len)
char *p1, *p2;
int16 len;
{
  if(*p1==*p2) return 0;
  if(*p1<*p2) return 1;
  if(*p1>*p2) return 2;
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

static flag geboekt()
{
  uint16 rec__,k;

	if(stu==3){ // default rekeningen
		for(k=0;k<MaxDefGrb;k++) if(*l(3,2)==DefGrb[k]) break;
		if(k<MaxDefGrb) return YES;
	}

  rec__=*u(stu,1)+30000*(stu-1);
	if(stu==2){ // staat in kassaparameters 
  	for(k=0;k<10;k++) if(*u(2,1)==loc_klt[k]) return YES;
	}

  if(fldlen(4,0)==0) return NO;
 
  fasinit(4);
  *u(4,5)=rec__;
  if(faskeyi(4,4,2)==0){
    if(*u(4,5)==rec__) return YES;
  }
	if(fldlen(5,0)){
  	fasinit(5);
    *u(5,2)=rec__;
    if(faskeyi(5,1,0)==0) return YES;
	}

  if(fldlen(86,1)){
    fasinit(86);
    *u(86,5)=rec__;
    if(faskeyi(86,4,2)==0){
      if(*u(86,5)==rec__) return YES;
    }
  }

  return NO;
}
 
 
static exec_work()
{
  int16 k,mode_,ok_;

  if(werkveld[0]=='\0') return NO;
  fasinit(stu); copy(werkveld,s(stu,2+(sort_key-1)),30); mode_=1;
  if(sort_key==1){
   if(cd){copy(werkveld,s(stu,2+(sort_key-1)),30); mode_=1;}
   else *u(stu,1)=val(werkveld);
  }
  scrget(1,7);scrupd(-3,0); ok_=NO;
  FOREVER{
    next:;
    if(sort_key!=1 || cd){
      if(faskeyi(stu,sort_key,mode_)) break; mode_=2;
      if(selp_tst()==NO) goto next;
      ok_=YES;break;
    }
    else {
      if(*u(stu,1)==0 || fasgeti(stu)) break;
      if(selp_tst()==YES) ok_=YES;
      break;
    }
  }
  zero(werkveld,sizeof werkveld);
  if(ok_==NO) return NO;
  for(k=0;k<DIM_REC;k++){
    if(tb[k].rec==0) break;
    if(tb[k].rec==*u(stu,1)) break;
  }
  if(tb[k].rec==*u(stu,1)) start=k;
}
 
static add_str(pd_,ps_,len_)
char *pd_,*ps_;
int16 len_;
{
  int16 k,add_sp_=NO,no_sp_=NO;
							
  if(len_<0){no_sp_=YES;len_=-len_;}
  for(k=0;k<len_;k++){
    if(*(ps_+k)=='\0'){if(no_sp_) break; else add_sp_=YES;}
    if(add_sp_) *(pd_+k)=' ';
    else *(pd_+k)=*(ps_+k);
  }
  return k;
}

static get_info(select_)
int16 select_;
{
  int16 k,mode_;
									
  ram_recl=fldlen(22,0) +2;                               /* + 2 bytes hash */
  max_line=(sizeof ram /ram_recl) -1;
  hash_len=0; dat_len=ram_recl-2;
  zero(ram,sizeof ram);
  fasinit(22);*u(22,2)=stu;*u(22,3)=*u(stu,1); mode_=1; k=0;
  FOREVER{
    next:;
    if(faskeyi(22,1,mode_)) break; mode_=2;
    if(*u(22,2)!=stu) break;
    if(*u(22,3)!=*u(stu,1)) break;
    if(select_){
      if(dt_beg && *u(22,4)<dt_beg) goto next;
      if(dt_end && *u(22,4)>dt_end) goto next;
      if(type_info && *s(22,6)!=type_info) goto next;
    }
    stu2ram(22,k);
    k++; if(k>=max_line) break;
  }
  return k;
}

static dsp_info()
{
  int16 j,k,curs=1,z_base_,key,z,start_,d_mode_=NO,curspos_;
  char *pdum,dumm_[10],*pvar;
 
  if(fldlen(22,0)==0) goto endsr;
  get_info(NO);
  pdum=&dumm_[0];
  scrnum=0; start_=0;
  FOREVER{
    redo:
    scrget(2,89);z=1;
		scraddpicto(3,0,76,0,4,2,105,1,7,"^!B0019B");
		if(fldlen(22,7)) scraddpicto(1,0,11,3,2,1,605,0,0,"Alarm"); 
    j=start_+1; scrifld(z++,fm_ou3,&j);
    j+=D_LIN_SCR-1; scrifld(z++,fm_ou3,&j);
    if(fldlen(stu,2)) scrofld(z++,stu,2,-1); else scrofld(z++,stu,1,-1);
    scrofld(z++,stu,3,-1);
    z_base_=z;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      if(fieldspc(22,4,&pdum,fmt)>0){
				if(d_mode_==NO) fmt[1]&=0xBF;
				pvar=ram+(j*ram_recl + (s(22,4)-s(22,1)));
				scrifld(z++,fmt,pvar);
      }
      if(fieldspc(22,7,&pdum,fmt)>0){
				if(d_mode_==NO) fmt[1]&=0xBF;
	      pvar=ram+(j*ram_recl + (s(22,7)-s(22,1)));
	      scrifld(z++,fmt,pvar);
      } else z++;
      if(fieldspc(22,6,&pdum,fmt)>0){
				if(d_mode_==NO) fmt[1]&=0xBF;
				pvar=ram+(j*ram_recl + (s(22,6)-s(22,1)));
				scrifld(z++,fmt,pvar);
      }
      if(fieldspc(22,10,&pdum,fmt)>0){
				pvar=ram+(j*ram_recl + (s(22,10)-s(22,1)));
				scrifld(z++,fmt,pvar);
      }

    }
    key=scrupd(curs,0x3BF);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000; 
		if(key==5001){curs=fldcurs;goto redo;}
		if(key==5002){curs=fldcurs;goto redo;}
    if(key==101 || key==106) goto endsr;
    if(key==104){
      j=(curspos_-z_base_)/4;j+=start_;
      ins_lin(22,j);
      curs=curspos_;goto redo;
    }
    if(key==105){
      j=(curspos_-z_base_)/4;j+=start_;
      del_lin(22,j);
      curs=curspos_;goto redo;
    }
//    if(key==110) copy_info();
    if(key==109) {if(d_mode_) d_mode_=NO; else d_mode_=YES;}
    if(key==108)break;
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
//    if(key==172) {print_screen(YES);}
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){ram2stu(22,k+start_);if(*s(22,10)=='\0') {j=k;break;}}
    curs=z_base_+j*4;
  }
	fasunlck(-2);
  for(k=0;k<max_line;k++){
    ram2stu(22,k);
    if(*s(22,10)){
      *u(22,2)=stu; *u(22,3)=*u(stu,1); *u(22,5)=k;
      if(*u(22,4)==0) *u(22,4)=*u(25,2);
      if(*u(22,1)) fasupd(22); else fasadd(22);
    }
    else if(*u(22,1)) faskill(22);
  }
	fasunlck(-1);
  endsr:;/* stop */
}
 
static copy_info()
{
  int16 k,key,mode_;
  uint16 adr_,mrec_,rec_;
									
  copy(s(stu,1),buf1000,fldlen(stu,0));
  adr_=4128; if(stu==2) adr_=4130; else if(stu==6) adr_=4132;
  sysget(adr_,2,&mrec_); fasinit(stu); if(mrec_) {*u(stu,1)=mrec_;fasgeti(stu);}
  FOREVER{
    redo:;
    scrget(1,5);
    scrifld(1,fm_os20,nm_20);
    scrfld(2,25,1);
    scrifld(3,fm_os38,"DE INFO OVER TE NEMEN ?");
    scrfld(4,stu,3);
    key=scrupd(4,0x0481);
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(search(stu,0)) goto redo;
    break;
  }
  mrec_=*u(stu,1);sysput(adr_,2,&mrec_);
  for(k=max_line-1;k>=0;k--){
    ram2stu(22,k); if(*u(22,1) || *s(22,10)) break;
  }
  if(k>=max_line) goto endsr;
  fasinit(22);*u(22,2)=stu;*u(22,3)=mrec_; mode_=1; k=k+1;
  FOREVER{
    next:;
    if(faskeyi(22,1,mode_)) break; mode_=2;
    if(*u(22,2)!=stu) break;
    if(*u(22,3)!=mrec_) break;
    rec_=*u(22,1); *u(22,1)=0; *u(22,4)=0;             /* forceren te adden */
    stu2ram(22,k);
    k++; if(k>=max_line) break;
    *u(22,1)=rec_; fasgeti(22);
  }
  endsr:;
  copy(buf1000,s(stu,1),fldlen(stu,0));
}

static ins_lin(stu_,lin_)
int16 stu_,lin_;
{
  int16 k;
								
  if(stu_==22){
    ram2stu(stu_,max_line-1);
    if(*u(22,1)) faskill(stu_);
  }
  for(k=max_line-2;k>=lin_;k--){
    ram2stu(stu_,k);
    stu2ram(stu_,k+1);
  }
  zero(ram+ram_recl*lin_,ram_recl);
}

static del_lin(stu_,lin_)
int16 stu_,lin_;
{
  int16 k;
 
  if(stu_==22){
    ram2stu(stu_,lin_);
    if(*u(22,1)) faskill(stu_);
  }
  for(k=lin_;k<max_line-1;k++){
    ram2stu(stu_,k+1);stu2ram(stu_,k);
  }
  zero(ram+ram_recl*(max_line-1),ram_recl);
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



static streepje(z)
int16 z;
{
  scrifld(z,fm_os7,"      -");
}
 
static initload()
{
	int16 k;
	long grb_;

  fileopen(1);
  fileopen(2);
  fileopen(3);
  fileopen(4);
  fileopen(5);
  fileopen(10);
  fileopen(6);
	if(fldlen(7,1)) fileopen(7);
  if(fldlen(8,1)) fileopen(8);
  fileopen(9);
	if(fldlen(16,1)) fileopen(13);
  if(fldlen(60,1)){
    if(ovltest(210) && fldlen(45,1)) fileopen(13);/* Degros KLD zit op 14 */
    else fileopen(14);
  }
  fileopen(15);

  sysget( 294,4,def_munt);
  sysget(1008,16,(char *)Bkhbtwpct);
  sysget(1918,2,&sear_stt);
  sysget(1048,32,&btw_pct[0]);
	sysget(2212,4,talen);
	sysget(2698,2,&sys2698);
  sysget(3586,2,&sys3586);
  sysget(3588,2,&sys3588);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3632,2,&sys3632);
  sysget(3720,2,&sys3720);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(4294,40,(char *)&loc_klt[0]); 
  sysget(3678,2,&def_taal);
	sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  selp_wis();
  copy("-X|/",dsp_kar,4);dsp_kar[1]=0x5C;
	if(stu==3){ // default grb uit parameters laden 
    MaxDefGrb=0;
		for(k=0;k<17;k++){
      sysget(780+k*4,4,&grb_); if(grb_!=0 && grb_!=-1) DefGrb[MaxDefGrb++]=grb_;
    }
		sysget(1201,4,&grb_); if(grb_!=0 && grb_!=-1) DefGrb[MaxDefGrb++]=grb_;
		sysget(1205,4,&grb_); if(grb_!=0 && grb_!=-1) DefGrb[MaxDefGrb++]=grb_;
		for(k=0;k<80;k++){
      sysget(10262+k*80,4,&grb_); if(grb_!=0 && grb_!=-1) DefGrb[MaxDefGrb++]=grb_;
			if(MaxDefGrb>=30) break;
    }
	}
}

static copy0(ps,pd)
char *ps,*pd;
{
  int16 fuval=0;
			
  while(*ps){
    *pd++=*ps++;
    fuval++;
  }
  *pd='\0';
  return fuval;
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

