/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0229GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0229dat
#define ovlcod DRK0229cod
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

char ovldat[] = "drk0229  00:01 25/11/10 (c) Jamadata"; // Aanpassen/schrappen lijst artikels 

  // FLAGGOU : koopwarengroep in selectie 

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_REC         10000
#define D_LIN_SCR       17
#define MAXFLD          100
							
extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();
static uint16 hashbuf();
static uint16 chk_omzet(rec_);
			

static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os59[]  = {7,0x88,59,0,0,0,0};
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
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x20,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x20,0};
static char fm_uf7_1[] = {6,0xD4,7,1,0x60,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_uf4_1[] = {6,0xD4,4,1,0x60,0};
static char fm_uf3_0[] = {6,0xD4,3,0,0x70,0};
static char fm_of7_1[] = {6,0x94,7,1,0x60,0};
static char fm_of6_2[] = {6,0x94,6,2,0x60,0};
static char fm_of5_0[] = {6,0x94,5,0,0x60,0};
static char fm_of4_3[] = {6,0x94,4,3,0x60,0};
static char fm_of4_0[] = {6,0x94,4,0,0x60,0};
static char fm_of4_1[] = {6,0x94,3,1,0x60,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_uf5_4[] = {6,0xD4,5,4,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_AKP []  = {13,0xC8,1,0,1,0,'A','A','K','K','P','P',0};

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

static int16 stu=6,fkey=2,free,start;
static char oldnm[65],manier='A',dsp_txt[80],OnlyBlockedArt,OnlyNoStock,nm_loc[10][6];
static char fmt[40],art_nm[50],lev_res[50],werkveld[30];
static char stubuf[2][150];
static float btw_pct[8];
static long TbDiversArtikel[10];
static flag lvcd,klcd,chk_btoeg=NO,sys3720,only_dsp;
static uint16 inq_groep=0,inq_lev,inq_art,p_max_grp,max_fich,dt_stat_beg,dt_stat_end;
static uint16 *pu_6_1;
static float sys3614,net_winst[12];
static flag sgrp_used,slev_used,del_mode,sys2698;
static flag sear_stt,sys3586,sys3588,sys3894,sys3632,sys3876,sys3618,sys3652;
static uint16 dt_beg,dt_end,inq_klt,max_dfld,sort_key;
static struct{
  uint16 rec;
  char mark_omz;
	uint16 dt_last_omz;
} tb[DIM_REC];

static struct{
  int16 nr;
  int16 fld;
  int16 flen;
  char *pos;
  char fmt[40];
  char txt[20];
} kol[2];
 
static struct{
  int16 fld;
  char omschr[20];
} dsp_tab[50];

static struct{
  char data[2][100];
  char o_data[2][100];
} tb_val[20];

static char vptekst[100],stuksprx[10],def_munt[4];
static int16 def_taal;
 
ovlcod()
{
  initload();
  display();
  ovlexit(-1);
}

static display()
{
  int16 j,k,g,curs,z,z_base_,key,mode_,pos_,dsp_rev_,code_corr_,curspos_;
	long n;
	uint16 dt_;
	char mask_;

  code_corr_=0; if(fldlen(6,2)>5) code_corr_=fldlen(6,2)-5;
  inq_lev=0;inq_groep=0;manier='A';del_mode=NO;
  zero((char *)&kol[0].nr,sizeof kol);
  sysget(4334,2,&kol[0].nr);
  sysget(4336,2,&kol[1].nr);
  for(k=0;k<2;k++){
    if(kol[k].nr && kol[k].nr<=max_dfld){
      kol[k].fld=dsp_tab[kol[k].nr-1].fld;
      kol[k].flen=fldlen(6,kol[k].fld);
      kol[k].pos=s(6,kol[k].fld);
      fmt_get(6,kol[k].fld); copy(fmt,kol[k].fmt,sizeof fmt);
      copy(dsp_tab[kol[k].nr-1].omschr,kol[k].txt,20);
    } else zero((char *)&kol[k].nr,sizeof kol[0]);
  }

  FOREVER{
    redo_sel:;fasunlck(0);
    if(ask_kolom()) break;
    scrget(1,7);scrupd(-3,0);
    for(k=0;k<DIM_REC;k++) zero((char *)&tb[k].rec,sizeof tb[0]);fasinit(6);
    start=0;max_fich=0;mode_=1;curs=2;
    FOREVER{
      next:;
      if(faskeyi(6,sort_key,mode_)) break; mode_=2;
			if(del_mode && OnlyBlockedArt=='J' && *u(6,200)==0) goto next;
      if(DirCall_DRK2215_SelectArtikel()==NO) goto next;
      tb[max_fich].rec=*pu_6_1;
			tb[max_fich].dt_last_omz=0xFFFF;
			if(fldlen(6,200) && *u(6,200)) tb[max_fich].mark_omz|=0x02;
      if(del_mode){
				if(OnlyNoStock=='J'){
					if(*f(6,33)) goto next;
					if(fldlen(66,11)){
						fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
						for(k=0;k<10;k++){
			        if(fldlen(66,11+k*15) && *f(66,11+k*15)) goto next;
						}
					}
				}

				dt_=chk_omzet(*pu_6_1);
				if(dt_stat_beg && dt_< dt_stat_beg) goto next;
				if(dt_stat_end && dt_> dt_stat_end) goto next;
				if(dt_>1) tb[max_fich].dt_last_omz=dt_;
				if(dt_) tb[max_fich].mark_omz|=0x01;
			}
      max_fich++;
      if(max_fich>=DIM_REC) break;
    }
		if(max_fich==0) {errnum=39;goto redo_sel;}
		//if(del_mode){
		//	if(fldlen(16,1)){
  //			fasinit(16);n=0;
		//		FOREVER{
		//			*l(16,1)=++n;
		//			g=fasgeti(16);
		//			if(g==47)break;
		//			if(g!=46){
		//				for(j=0;j<max_fich;j++){
		//					if(*l(16,20)==tb[j].rec){
		//						if(*u(16,3)>tb[j].dt_last_omz) tb[j].dt_last_omz=*u(16,3);
		//						break;
		//					}
		//  			}
		//			}
		//		}
		//	}
		//	if(fldlen(91,1)){
  //			fasinit(91);n=0;
		//		FOREVER{
		//			*l(91,1)=++n;
		//			g=fasgeti(91);
		//			if(g==47)break;
		//			if(g!=46){
		//				for(j=0;j<max_fich;j++){
		//					if(*u(91,2)==tb[j].rec){
		//						if(*u(91,3)>tb[j].dt_last_omz) tb[j].dt_last_omz=*u(91,3);
		//						break;
		//					}
		//  			}
		//			}
		//		}
		//	}
  //    for(j=0;j<max_fich-1;j++){
		//		if((dt_stat_beg && tb[j].dt_last_omz < dt_stat_beg) || (dt_stat_end && tb[j].dt_last_omz< dt_stat_end)){
		//			for(k=j+1;k<max_fich;k++) copy((char *)&tb[k].rec,(char *)&tb[j].rec,sizeof tb[0]);
		//			zero((char *)&tb[max_fich-1].rec,sizeof tb[0]);
		//			j--;max_fich--;
		//		}
		//	}
		//}

 //   if(max_fich==0) {errnum=39;goto redo_sel;}
    start=0;curs=2;
		fasunlck(-1);
    FOREVER{
redo:;
   //   if(del_mode){
			//	
  	//		for(j=start;j<start+18;j++){
			//		if(tb[j].rec==0) break;
			//		if(tb[j].dt_last_omz==0xFFFF){
			//			scrget(1,7); scrupd(-3,0);
  	//				fasinit(6); *pu_6_1=tb[j].rec;fasgeti(6);
	  //				dt_=chk_omzet(*pu_6_1);
		 // 			if(dt_>1) tb[j].dt_last_omz=dt_;
			//			else tb[j].dt_last_omz=0;
			//  		if(dt_) tb[j].mark_omz=1;
			//		}
			//	}
			//}
      scrnum=0; scrget(2,224);z=1;
      if(del_mode){
				if(del_mode==1) scraddpicto(1,0,76,22,4,2,133,0,3,"Schrap allen");
				else scraddpicto(1,0,76,22,4,2,31,0,3,"Blokkeer allen");
				scraddf(118,22,15,8);
				if(del_mode==1) scrifld(118,fm_os40," F9 markeer dit artikel om te schrappen");
				else scrifld(118,fm_os40," F9 blokkeer/deblokkeer dit artikel ");
      }
      scrifld(-z,fm_us30,werkveld);z++;
      if(del_mode){
				scrifld(z++,fm_os18,"Laatste prijswijz.");
				scrifld(z++,fm_os18,"Omzet/statistieken");
      }
      else{
				for(k=0;k<2;k++){
					if(kol[k].nr) scrifld(z++,fm_os18,kol[k].txt);
					else z++;
				}
				scraddfield(300,0,0,0xAA);scrifld(300,fm_os59,"|");
	    }
      z_base_=z;
      zero((char *)tb_val[0].data,sizeof tb_val);
      for(j=start;j<start+18;j++){
				if(tb[j].rec==0) break;
				fasinit(6); *pu_6_1=tb[j].rec;fasgeti(6);
				mask_=0xFF; if(tb[j].mark_omz&0x02) mask_=0x0B;
				if(del_mode && tb[j].mark_omz&0x80) mask_=0x08;
				zero(art_nm,sizeof art_nm);pos_=0;
				if(sort_key==1){
					pos_+=add_str(&art_nm[pos_],s(6,2),fldlen(6,2));art_nm[pos_++]=' ';
					pos_+=add_str(&art_nm[pos_],s(6,3),fldlen(6,3));
				}
				else if(sort_key==6){
					pos_+=add_str(&art_nm[pos_],s(6,29),fldlen(6,29));art_nm[pos_++]=' ';
					pos_+=add_str(&art_nm[pos_],s(6,3),fldlen(6,3));
				}
				else {
					pos_+=add_str(&art_nm[pos_],s(6,3),fldlen(6,3)-code_corr_);art_nm[pos_++]=' ';
					pos_+=add_str(&art_nm[pos_],s(6,2),fldlen(6,2));
				}
				scrifld(z++,fm_os36,art_nm); scrchat(z-1,mask_);
				pos_=j-start;
				if(del_mode){
					scrfld(z++,6,11); scrchat(z-1,mask_);
					if(tb[j].mark_omz&0x01) scrifld(z++,fm_os5," JA");
					else scrifld(z++,fm_os15,"    NEE");
					scrchat(z-1,mask_);
					if(tb[j].dt_last_omz){
						if(mask_==0xFF) mask_=0x02;
						scraddf(80+j-start,4+j-start,70,mask_); scrifld(80+j-start,fm_odat,&tb[j].dt_last_omz);
					}
				}
				else{
					for(k=0;k<2;k++){
						if(kol[k].nr){
							copy(kol[k].pos,tb_val[pos_].data[k],kol[k].flen);
							copy(kol[k].pos,tb_val[pos_].o_data[k],kol[k].flen);
							scrifld(z++,kol[k].fmt,tb_val[pos_].data[k]);
						} else z++;
					}
				}
      }
      redo_upd:;
      key=scrupd(curs,0x3A7);curs=2;curspos_=fldcurs;
		  if ((key/0x100)==1) key=(key&0xFF)+5000;

		  if(key==5001){ // alles markeren
        for(j=start;j<start+18;j++){
	  			if(tb[j].rec==0) break;
					if(del_mode==1) tb[j].mark_omz|=0x80;
					else{
						fasinit(6);*u(6,1)=tb[j].rec; fasgeti(6);
						*u(6,200)=1; tb[j].mark_omz|=0x02;
						if(fldlen(6,198)) *u(6,198)=procid;
						if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
						fasupd(6);
					}
			  }
				goto redo; 
			}
      if(key==106) goto redo;
			fasunlck(-2);
			if(key==112){
		    if(del_mode==1 && DisplayWarning("Wenst echt ALLE fiches te markeren om te schrappen? ",61,1)==YES) {
					for(j=0;j<max_fich;j++){
	  				if(tb[j].rec==0) break;
						tb[j].mark_omz|=0x80;
					}
				}
			}
			for(j=start;j<start+18;j++){
				if(tb[j].rec==0) break;
				fasinit(6); *pu_6_1=tb[j].rec;fasgeti(6);
				pos_=j-start;n=0;
				if(cmpstr(tb_val[pos_].data,tb_val[pos_].o_data,sizeof tb_val[0].data)){
					for(k=0;k<2;k++){
						if(kol[k].nr){
							copy(tb_val[pos_].data[k],kol[k].pos,kol[k].flen);
						}
					}
					if(fldlen(6,198)) *u(6,198)=procid;
					if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
					fasupd(6);
				}
      }
			fasunlck(-1);
      if(key==18){exec_work();curs=curspos_+1;goto redo;}

      if(key==101) break;
      if(key==108 && curspos_>=z_base_){
				n=(curspos_-4)/3; n+=start;
				curs=curspos_;
				if(tb[n].rec){
					if(key==108) art_upd(n);
				}
      }
      if(key==109 && del_mode && curspos_>=z_base_){
				n=(curspos_-4)/3; n+=start;
				curs=curspos_;
				if(tb[n].rec){
					if(del_mode==1){
  					if(tb[n].mark_omz & 0x80) tb[n].mark_omz&=0x7F;
	  				else tb[n].mark_omz|=0x80;
					}
					else{
						fasinit(6);*u(6,1)=tb[n].rec; fasgeti(6);
						if(*u(6,200)){ *u(6,200)=0; tb[n].mark_omz&=0xFD;}
						else { *u(6,200)=1; tb[n].mark_omz|=0x02;}
						if(fldlen(6,198)) *u(6,198)=procid;
						if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
						fasupd(6);
					}
				}
      }
      if(key==102) start-=18;
      if(key==103) {start+=18;if(start>=max_fich-18) start=max_fich-18;}
      if(start<0) start=0;
    }
    if(key==101 && del_mode==1){
      n=0;
      for(k=0;k<max_fich;k++) if(tb[k].rec && tb[k].mark_omz&0x80) n++;
      if(n){
				copy("Wenst U deze",dsp_txt,12);stcli_d(&dsp_txt[12],(long)n,4,1);
				copy(" artikels te schrappen ????",&dsp_txt[16],30);
				if(scr_ok(dsp_txt)==YES){
					fasunlck(-2);
					kill_art(max_fich);
					//for(k=0;k<max_fich;k++){
					//	if(tb[k].rec && tb[k].mark_omz&0x80) kill_art(tb[k].rec);
					//}
					fasunlck(-1);
				}
      }
    }
  }

  endsr:;
}

static ask_kolom()
{
  int16 key,z,j,k,n,curs=2,curspos_;
 
  FOREVER{
    redo:
    scrget(2,225);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0229A");
		scraddpicto(1,0,76,22,4,2,127,0,4,"Uitgebreide selectie");
    scrfld(z++,25,1);
    scrifld(z++,fm_AKP,&manier);
    for(k=0;k<2;k++){
      scrifld(-z,fm_uu2,&kol[k].nr);z++;scrifld(z++,fm_os18,kol[k].txt);
    }
    for(k=0;k<9;k++){
      for(j=0;j<3;j++){
				n=k+j*9;
				if(n<max_dfld){
					n++;scrifld(z++,fm_ou2,&n);n--;
					scrifld(z++,fm_os18,dsp_tab[n].omschr);
				} else z+=2;
      }
    }
    key=scrupd(curs,0x0689);curs=2;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) return YES;
    if(key==111) ovlexit(*u(25,4));
    sort_key=2;
    if(manier=='K') sort_key=1;
    else if(manier=='P') sort_key=6; 
    for(k=0;k<2;k++){
      if(kol[k].nr && kol[k].nr<=max_dfld){
				if(k==1 && kol[1].nr==kol[0].nr){
					errnum=34;curs=5;goto redo;
				}
				kol[k].fld=dsp_tab[kol[k].nr-1].fld;
				kol[k].flen=fldlen(6,kol[k].fld);
				kol[k].pos=s(6,kol[k].fld);
				fmt_get(6,kol[k].fld); copy(fmt,kol[k].fmt,sizeof fmt);
				copy(dsp_tab[kol[k].nr-1].omschr,kol[k].txt,20);
			} else zero((char *)&kol[k].nr,sizeof kol[0]);
    }
    if(key==18){curs=curspos_+1;goto redo;}
		if(key==5001){
			if(AskFields2Display()==NO) return NO;
			key=108;
		}
    if(key==108){
      del_mode=NO;
      seldata.selp_use=NO;
      if(ovlcall(2215,0)==0) break;
    }
    if((key==104 || key==110) && CheckPw(1,11,0)){
			if(key==104) del_mode=1;  else del_mode=2;
			scraddf(-1,0,0,0);z=1;
			scraddf(z++,3,21,3);
			scraddf(z++,8,2,0);	scraddf(z++,8,32,2);
			scraddf(z++,10,2,0); scraddf(z++,10,32,2);
			scraddf(z++,12,2,0); scraddf(z++,12,32,2);
			scraddf(z++,23,1,8);scraddf(z++,23,11,8);
									
			z=1;
			if(key==104) scrifld(z++,VarTextFmt(30,0),"Selectie te schrappen artikels");
			else scrifld(z++,VarTextFmt(30,0),"Selectie te blokkeren artikels");
			scrifld(z++,VarTextFmt(30,0),"Enkel geblokkeerde artikels : ");scrifld(z++,fm_uJN,&OnlyBlockedArt);
			scrifld(z++,VarTextFmt(30,0),"Niet meer verkocht na ..... : ");	scrifld(z++,fm_udat,&dt_stat_end);
			if(fldlen(6,33)){
  			scrifld(z++,VarTextFmt(30,0),"Enkel artikels ZONDER stock : ");	scrifld(z++,fm_uJN,&OnlyNoStock);
			} else z+=2;
			scrifld(z++,VarTextFmt(9,0)," F1 stop "); scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
			key=scrupd(1,0x81);
			if(key==101) return YES;
			seldata.selp_use=NO;
			if(ovlcall(2215,4)==0) break;
    }
  }
  sysput(4334,2,&kol[0].nr);
  sysput(4336,2,&kol[1].nr);
  return NO;
}


static AskFields2Display()
{
  int16 j,k,n,z,key,curs=1,start_;
	int16 FldNr[150],MaxFld;
  char SelectFldNr[150];

	MaxFld=0;stu=6;
	for(k=1;k<101;k++){ // boven 100 zitten data achter de schermen 
		if(UpdateFldAllowed(6,k)){
			FldNr[MaxFld]=k;SelectFldNr[MaxFld]='N';
			MaxFld++; if(MaxFld>=114) break; // Maximaal 2 schermen van 57 kolommen 
		}
	}
	start_=0;
	FOREVER{
		redo:;
	  scrnum=0;scrget(1,250);z=1;
		if(start_>0) scraddpicto(1,0,74,1,4,2,18,0,4,"vorig"); 
		if((start_+57)<MaxFld) scraddpicto(2,0,74,22,4,2,13,0,4,"volgend"); 
		for(k=0;k<19;k++){
		  for(j=0;j<3;j++){
				n=start_+k+19*j;
				if(n<MaxFld){
					scrifld(z++,fm_uJN,&SelectFldNr[n]);scrifld(z++,fm_os20,s(stu,-FldNr[n])); 
				} else z+=2;
			}
		}
		key=scrupd(curs,0x81);if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) return NO;
		if(key==5001){start_-=57;if(start_<0) start_=0;goto redo;}
		if(key==5002 && (start_+57)<MaxFld) {start_+=57;goto redo;}

		if(key==108) break;
	}
	for(k=0;k<MaxFld;k++)	if(SelectFldNr[k]=='J') break; 
	if(k>=MaxFld) return NO; // niks geselecteerd
	j=0;zero((char *)&kol[0].nr,sizeof kol);
	for(k=0;k<MaxFld;k++){
		if(SelectFldNr[k]=='J'){
			kol[j].nr=FldNr[k];
			kol[j].fld=FldNr[k];
			kol[j].flen=fldlen(6,kol[j].fld);
			kol[j].pos=s(6,kol[j].fld);
			fmt_get(6,kol[j].fld); copy(fmt,kol[j].fmt,sizeof fmt);
			copy(s(stu,-FldNr[k]),kol[j].txt,20);				
			j++;
		}
		if(j>=2) break;
	}				

	return YES;
}


static UpdateFldAllowed(stu_,fld_)
int16 stu_,fld_;
{
  char *pdum_;

  if(fld_<=1) return NO; // recordnr altijd skippen 
	if(fieldspc(stu_,fld_,&pdum_,fmt)>0){
    if(fmt[1]&=0x40) return YES;
  } 
	return NO;
}

static uint16 chk_omzet(rec_)
uint16 rec_;
{
  int16 omz_=0,mode_;
	uint16 dt_=0;
 
  if(fldlen(16,1)){
    fasinit(16);*l(16,20)=rec_; mode_=1;
		FOREVER{
      if(faskeyi(16,1,mode_)) break; mode_=2;
      if(*l(16,20)!=rec_) break;
			omz_=YES;
			if(dt_<*u(16,3)) dt_=*u(16,3);
			if(dt_stat_end && dt_>dt_stat_end) break;
    }
  }
	if(omz_==0 && fldlen(60,1)){
    fasinit(60);*l(60,22)=rec_;
    if(faskeyi(60,1,1)==0){
      if(*l(60,22)==rec_) omz_=YES;
    }
  }
  if(omz_==0 && fldlen(8,1)){
    fasinit(58);*u(58,14)=rec_;
    if(faskeyi(58,2,1)==0){
      if(*u(58,14)==rec_) omz_=YES;
    }
  }

  if(omz_==0 && fldlen(9,27)){
    fasinit(9);*u(9,3)=rec_;
    if(faskeyi(9,7,1)==0){
      if(*u(9,3)==rec_) omz_=YES;
    }
  }

  if(fldlen(91,2)){
    fasinit(91);*u(91,2)=rec_; mode_=1;
		FOREVER{
      if(faskeyi(91,1,mode_)) break; mode_=2;
      if(*u(91,2)!=rec_) break;
			omz_=YES;
			if(dt_<*u(91,3)) dt_=*u(91,3);
			if(dt_stat_end && dt_>dt_stat_end) break;
    }
  }
	if(dt_==0 && omz_) dt_=1;
  return dt_;
}

static kill_art(max_)
uint16 max_;
{
  int16 jj,z;

	fasunlck(-2);
  for(jj=0;jj<max_fich;jj++){
    if(tb[jj].rec && (tb[jj].mark_omz&0x80)){
			for(z=0;z<10;z++) if(tb[jj].rec==TbDiversArtikel[z]) break;
	    if(z<10) tb[jj].mark_omz=0; // blokkeren divers-artikel
    }
  }

  scrnum=0;scrget(1,170); z=1;
  //scrifld(z++,fm_os63,"Bezig met schrappen : ");z++;
  //scrofld(z++,6,2,-1);
  //scrofld(z++,6,3,-1);z+=2;
  scrifld(z++,fm_os63,"                    Schrappen van aanverwante fiches ");
  z=4;
	z=kil_bew(z,6,9,3);
  z=kil_bew(z,6,11,3);
  z=kil_bew(z,6,16,20);
  z=kil_bew(z,6,22,3);
	z=kil_bew(z,6,53,10);
  z=kil_bew(z,6,60,22);
	z=kil_bew(z,6,64,3);
	z=kil_bew(z,6,66,2);
  z=kil_bew(z,6,91,2);
  z=kil_bew(z,6,93,2);
	z=kil_bew(z,6,95,3);
	z=kil_bew(z,stu,6,102); // koppeling deelverpakkingen wegdoen
  
  for(jj=0;jj<max_fich;jj++){
    if(tb[jj].rec && (tb[jj].mark_omz&0x80)){
      fasinit(stu);*u(stu,1)=tb[jj].rec;fasgeti(stu); faskill(stu);
    }
  }
	endsr:;
	fasunlck(-1);
}

static kil_bew(z,mstu_,bstu_,nr_)
int16 z,mstu_,bstu_,nr_;
{

  int16 j,jj,g,mode_,len1_;
  uint16 mrec_,*prec_,dcnt_,*pu1_;
  long *lprec_,*pl1_,n,div_rec_;

  if(fldlen(bstu_,1)==0) goto endsr; // structuur bestaat niet 
	if(fldlen(bstu_,nr_)==0) goto endsr;
  switch(bstu_){
    case 7 : fileopen(7);
						 scrifld(z++,fm_os63,"Schrappen bestaande documenten ...");
						 lprec_=l(7,nr_); break;
    case 8 : if(fldlen(8,1)==0) break;
				     fileopen(8);
						 scrifld(z++,fm_os63,"Schrappen bestaande leveringsbons ...");
						 prec_=u(8,nr_); break;
    case 9 : fileopen(9);
						 scrifld(z++,fm_os63,"Schrappen bestaande prijsafspraken/omzetfiches ...");
						 prec_=u(9,nr_); break;
    case 11: prec_=u(11,nr_);
						 scrifld(z++,fm_os63,"Schrappen bestaande aankoopfiches ...");
						 break;
		case 16: fileopen(13);
						 scrifld(z++,fm_os63,"Schrappen bestaande historieken ...");
						 lprec_=l(16,nr_); break;
    case 22: fileopen(15);
						 scrifld(z++,fm_os63,"Schrappen bestaande info ...");
						 prec_=u(22,nr_); break;
    case 53: scrifld(z++,fm_os63,"Schrappen blokjes kassa ...");
   					 prec_=u(53,10); break;
    case 60: fileopen(14);
				     scrifld(z++,fm_os63,"Schrappen bestaande statistieken ...");
						 lprec_=l(60,nr_); break;
    case 62: prec_=u(62,nr_);
						 scrifld(z++,fm_os63,"Schrappen bestaande klanten-memo ...");
						 break;
		case 64: prec_=u(64,nr_);
				     scrifld(z++,fm_os63,"Schrappen extra barcodes ...");
						 break;
		case 66: prec_=u(66,nr_);
						 scrifld(z++,fm_os63,"Schrappen bestaande stocklocaties ...");
						 break;
    case 86: fileopen(10);
						 scrifld(z++,fm_os63,"Schrappen bestaande boekingen in jaararchief ...");
						 prec_=u(86,nr_); break;
    case 91: fileopen(9);
						 scrifld(z++,fm_os63,"Schrappen bestaande kasverkopen ...");
						 prec_=u(91,nr_); break;
    case 93: fileopen(11);
						 scrifld(z++,fm_os63,"Schrappen bestaande kassa-promoties ...");
						 prec_=u(93,nr_); break;
    case 95: fileopen(9);
						 scrifld(z++,fm_os63,"Schrappen bestaande verhuurfiches ...");
						 prec_=u(95,nr_); break;
    default: break;
  }
	scrupd(-3,0);
  mrec_=*u(mstu_,1);
  if(bstu_==86){
    mrec_=*u(mstu_,1)+(mstu_-1)*30000;
  }
	if(bstu_==6 && mstu_==6 && nr_==102){ // koppeling wegdoen van deelverpakkingen
		fasinit(6);n=0;
		FOREVER{
      *u(6,1)=++n;
      g=fasgeti(6);
			if(g==47)break;
			if(g!=46 && *u(6,102)){
        for(jj=0;jj<max_fich;jj++){
		  		if(tb[jj].rec==0 || (tb[jj].mark_omz&0x80)==0) continue;
		  		if(*u(6,102)==tb[jj].rec) {*u(6,102)=0;fasupd(6);break;}
		  	}
			}
		}
		fasinit(6);*u(6,1)=mrec_; fasgetu(6);
		goto endsr;
	}
  
  len1_=fldlen(bstu_,1); pu1_=u(bstu_,1);pl1_=l(bstu_,1);
  fasinit(bstu_); dcnt_=0;n=0;scrnum=0;
  FOREVER{
		next:;
    if(len1_==4) *pl1_=++n; else *pu1_=++n;
    if((n%500)==0) {scrifld(24,fm_ol8,&n);scrupd(-3,0);}
    g=fasgeti(bstu_);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
			if(bstu_==7 && *u(7,10)!=mstu_) goto next;
      for(jj=0;jj<max_fich;jj++){
				if(tb[jj].rec==0 || (tb[jj].mark_omz&0x80)==0) continue;
				mrec_=tb[jj].rec;
				//if((bstu_==91 || bstu_==16) && mstu_==6){ // historieken naar divers artikel zetten 
		  //    fasinit(6);*u(6,1)=mrec_;fasgeti(6);
		  //    div_rec_=*u(6,1);
		  //    if(*i(6,9)==99) div_rec_=TbDiversArtikel[9]; // leeggoed divers
  		//		else {
	  	//			for(j=0;j<8;j++) if(*f(6,28)==btw_pct[j]) break;
  		//			if(j<8) div_rec_=TbDiversArtikel[j];
				//	}
				//}
				if(bstu_==86){mrec_+=(stu-1)*30000;}
				switch(bstu_){
					case 7 : if(*lprec_==mrec_){faskill(7);dcnt_++;}
										break;
					case 8 : if(*prec_==mrec_){
											fasinit(58);*u(58,2)=*u(8,1);mode_=1;
											FOREVER{
												if(faskeyu(58,1,mode_)) break; mode_=2;
												if(*u(58,2)!=*u(8,1)) break;
												faskill(58);
											}
											faskill(8); dcnt_++;
										}
										break;
					case 9 : if(*prec_==mrec_){faskill(9);dcnt_++;}
										break;
					case 11: if(*prec_==mrec_){faskill(11);dcnt_++;}
										break;
					case 16: if(*lprec_==mrec_){
											if(mstu_==6){ // historieken naar divers artikel zetten 
												fasinit(6);*u(6,1)=mrec_;fasgeti(6);
												div_rec_=*u(6,1);
												if(*i(6,9)==99) div_rec_=TbDiversArtikel[9]; // leeggoed divers
  											else {
	  											for(j=0;j<8;j++) if(*f(6,28)==btw_pct[j]) break;
  												if(j<8) div_rec_=TbDiversArtikel[j];
												}
												*l(16,20)=div_rec_;fasupd(16);
											}
											else faskill(16);
											dcnt_++;
										}
										break;
					case 22: if(*i(22,2)==mstu_ &&  *prec_==mrec_){faskill(22);dcnt_++;}
										break;
					case 53: if(*prec_==mrec_){faskill(53);dcnt_++;}
							break;
					case 60: if(*lprec_==mrec_){faskill(60);dcnt_++;}
							break;
					case 62: if(*prec_==mrec_){faskill(62);dcnt_++;}
							break;
					case 64: if(*prec_==mrec_){faskill(64);dcnt_++;}
							break;
					case 66: if(*prec_==mrec_){faskill(66);dcnt_++;}
							break;
					case 86: if(*prec_==mrec_){faskill(86);dcnt_++;}
							break;
					case 91: if(*prec_==mrec_){// kasverkopen naar divers artikel zetten 
											if(mstu_==6){
												fasinit(6);*u(6,1)=mrec_;fasgeti(6);
												div_rec_=*u(6,1);
												if(*i(6,9)==99) div_rec_=TbDiversArtikel[9]; // leeggoed divers
  											else {
	  											for(j=0;j<8;j++) if(*f(6,28)==btw_pct[j]) break;
  												if(j<8) div_rec_=TbDiversArtikel[j];
												}												
												*prec_=div_rec_;fasupd(91);
											}
											else faskill(91);
											dcnt_++;
										}
										break;
					case 93: if(*prec_==mrec_){faskill(93);dcnt_++;}
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

static exec_work()
{
  int16 k,mode_,ok_;

  if(werkveld[0]=='\0') return NO;
  fasinit(6);
  if(sort_key==6) copy(werkveld,s(6,29),fldlen(6,29));
  else copy(werkveld,s(6,2+(sort_key-1)),30);
  scrget(1,7);scrupd(-3,0); ok_=NO;mode_=1;
  FOREVER{
    next:;
    if(faskeyi(6,sort_key,mode_)) break; mode_=2;
    if(inq_art && *pu_6_1!=inq_art) break;
    if(inq_lev && *u(6,7)!=inq_lev) goto next;
    if(inq_groep && *u(6,9)!=inq_groep)  goto next;
    if(DirCall_DRK2215_SelectArtikel()==NO) goto next;
    ok_=YES;break;
  }
  zero(werkveld,sizeof werkveld);
  if(ok_==NO) return NO;
  for(k=0;k<DIM_REC;k++){
    if(tb[k].rec==0) break;
    if(tb[k].rec==*pu_6_1) break;
  }
  if(tb[k].rec==*pu_6_1) start=k;
}
 
static art_upd(n)
int16 n;
{
  int16 g,j,k,curs,key,z,stu=6,mode=1,pos_1_4_,curspos_,pnr_,prstu_;
  char *p_stu_3,nm_groep[50],nm_subgroep[50];
  uint16 last_grp;

  pos_1_4_=s(1,4)-s(1,1);
  fasinit(6);*pu_6_1=tb[n].rec;fasgeti(6);
  if(fldlen(66,1)) {
	  fasinit(66);*u(66,2)=*pu_6_1;faskeyi(66,1,0);
  }
  mode=1;
  p_stu_3=s(stu,3);
  FOREVER{
    if(stu==6){/* artikel */
      if(!errnum){
				fasinit(1);   fasinit(52);zero(nm_groep,sizeof nm_groep); zero(nm_subgroep,sizeof nm_subgroep); 
				if(mode==1 || mode==3) {
					fasinit(1);*u(1,1)=*u(6,7); fasgeti(1);
					copy(s(1,1),stubuf[0],pos_1_4_);
					*(uint16 *)&stubuf[0][pos_1_4_]=hashbuf(stubuf[0],pos_1_4_);
					if(fldlen(6,101)){
						fasinit(1);*u(1,1)=*u(6,101); fasgeti(1);
						copy(s(1,1),stubuf[1],pos_1_4_);
						*(uint16 *)&stubuf[1][pos_1_4_]=hashbuf(stubuf[1],pos_1_4_);
					}
					if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);}
					zero(nm_groep,sizeof nm_groep); zero(nm_subgroep,sizeof nm_subgroep); 
					if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);copy(s(52,14),nm_groep,fldlen(52,14));}
					if(fldlen(6,103) && *u(6,103) && *u(6,9)){
						fasinit(52);*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;
						if(fasgeti(52)==0) copy(s(52,14),nm_subgroep,fldlen(52,14));
					}
				}
				last_grp=*u(6,9);
				calcnet();
      }
      curs=2;
redo_a:
			if(fldlen(6,200)){
				if(*u(6,200)) ConLook(1); else   ConLook(0);
			}
			k=19; // if(fldlen(6,185)) k=59;
      scrnum=0;scrget(2,k); z=1;	
      scrfld(z++,25,1);
      if(fldlen(6,2)) scrfld(z++,6,2); else scrofld(z++,6,1,-1);
			if(fldlen(6,200)){
				if(*u(6,200)==1) scrchat(z-1,0xB); else scrchat(z-1,0xFF);
				if(*u(6,200)==1) scraddpicto(7,z-1,0,0,2,1,70,0,4,"Maak actief"); else scraddpicto(7,z-1,0,0,2,1,71,0,3,"Blokkeer");
			}
			if(fldlen(6,195)){
				if(*s(6,195)=='J') scraddpicto(8,z-1,2,0,2,1,32,0,4,"NIET in webshop"); else scraddpicto(8,z-1,2,0,2,1,32,0,3,"Toon in webshop");
			}
			if(fldlen(6,194)){
				k=2; if(fldlen(6,195)) k=4;
				if(*s(6,194)=='J') scraddpicto(10,z-1,k,0,2,1,82,0,4,"NIET in B2B-webshop"); else scraddpicto(10,z-1,k,0,2,1,82,0,3,"Toon in B2B-webshop");
			}
			if(fldlen(6,104)){
				if(*s(6,104)=='J') scraddpicto(9,0,12,13,4,2,88,0,3,"Korting toestaan"); else scraddpicto(9,0,12,13,4,2,88,0,4,"Blokkeer korting");
			}
      for(k=3;k<=6;k++) scrfld(z++,6,k);
      scrbfld(z++,1,1+lvcd,stubuf[0],YES);
      scrbfld(z++,1,3,stubuf[0],NO);
      scrfld(z++,6,8);
      if(fldlen(6,101)) scrbfld(z++,1,3,stubuf[1],NO);
			scrfld(-z,6,9);z++;scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_groep); scraddpicto(3,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
#if FLAGCOC
      scrfld(z++,6,10);
			scrfld(z++,6,11);
			if(fldlen(6,103)){
				scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_subgroep);
				if(*u(6,9)) scraddpicto(4,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
			}
      for(k=12;k<=18;k++){
				if(YES /* suppr_wi==NO || !(sys3892 & 0x04)*/){
					scrfld(z++,6,k); 
				}
				else z++;
      }
			for(k=19;k<=20;k++) scrfld(z++,6,k);
#else
			if(fldlen(6,103)){
				scrfld(-z,6,103);z++;scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_subgroep);
				if(*u(6,9)) scraddpicto(6,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
			}
      for(k=10;k<=20;k++) scrfld(z++,6,k);
#endif
			if(fldlen(6,185)){
				for(k=0;k<5;k++){
					pnr_=k;
redo_rechts:;  
					prstu_=PrNrs[pnr_];
					if(fldlen(6,prstu_)){
						scrifld(z++,fm_os6,&vptekst[pnr_*10]);
						fmt_get(6,prstu_); 
						scrifld(z++,fmt,f(6,prstu_)); 
						if(sys3894 & 1<<pnr_) scrifld(z++,fm_os2,"IN");
						else scrifld(z++,fm_os2,"EX");
						scrifld(z++,fm_of4_1,&net_winst[pnr_]);
					}
					else for(j=0;j<4;j++) streepje(z++);
					if(pnr_<5){pnr_=k+5; goto redo_rechts;}
				}
			}
			else{
				for(k=0;k<6;k++){
					prstu_=PrNrs[k];
					if(fldlen(6,prstu_)){
						scrifld(z++,fm_os6,&vptekst[k*10]);
						fmt_get(6,prstu_);
						scrifld(z++,fmt,f(6,prstu_));
						if(sys3894 & 1<<k) scrifld(z++,fm_os5,"Incl.");
						else scrifld(z++,fm_os5,"Excl.");
						scrifld(z++,fm_of4_1,&net_winst[k]);
					}
					else for(j=0;j<4;j++) streepje(z++);
				}
			}
			key=scrupd(curs,0x01F9);curs=2;curspos_=fldcurs;
			if(fldlen(2,200)) ConLook(0);
			if ((key/0x100)==1) key=(key&0xFF)+5000;
			if(key==106){
				if(mode==2) return NO;
				else return YES;
      }
      fasinit(52); if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);}
      g=*p_stu_3;
      if(g=='\0'){
				if(key==101) return NO;
				errnum=38;curs=3;goto redo_a;
      }
      if(fldlen(6,2)){
				if(g<'A' || g>'z' || (g>'Z' && g<'a')) {errnum=30;curs=3;goto redo_a;}
				if(*s(6,2)=='\0'){errnum=38;curs=2;goto redo_a;}
      }
      if(stubuf[0][s(1,3)-s(1,1)]=='\0'){errnum=30;curs=8;goto redo_a;}
      if(*(uint16 *)&stubuf[0][pos_1_4_]!=hashbuf(stubuf[0],pos_1_4_)){
				fasinit(1);copy(&stubuf[0][s(1,3)-s(1,1)],s(1,3),fldlen(1,3));
				if(search(1,0)){curs=8;goto redo_a;}
				copy(s(1,1),stubuf[0],pos_1_4_);
				*(uint16 *)&stubuf[0][pos_1_4_]=hashbuf(stubuf[0],pos_1_4_);
				*u(6,7)=*u(1,1);
      }
      if(fldlen(6,101) && *(uint16 *)&stubuf[1][pos_1_4_]!=hashbuf(stubuf[1],pos_1_4_)){
				fasinit(1);copy(&stubuf[1][s(1,3)-s(1,1)],s(1,3),fldlen(1,3));
				if(search(1,0)){curs=10;goto redo_a;}
				copy(s(1,1),stubuf[1],pos_1_4_);
				*(uint16 *)&stubuf[1][pos_1_4_]=hashbuf(stubuf[1],pos_1_4_);
				*u(6,101)=*u(1,1);
      }
			if(key==5003){// uitgebreid groep zoeken
				if(search(52,98)) {
					fasinit(52); if(*u(6,9)){	*u(52,1)=*u(6,9);fasgeti(52);}
				}
  			else *u(6,9)=*u(52,1);
				zero(nm_groep,sizeof nm_groep); 
				if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);copy(s(52,14),nm_groep,fldlen(52,14));}
				if(fldlen(6,103)){
					zero(nm_subgroep,sizeof nm_subgroep); 
					if(*u(6,9)!=last_grp || *u(6,9)==0) *u(6,103)=0; // SUBGROEP WISSEN
					if(*u(6,103) && *u(6,9)){
						fasinit(52);*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;
						if(fasgeti(52)==0) copy(s(52,14),nm_subgroep,fldlen(52,14));
  				}
				}
				last_grp=*u(6,9);
				goto redo_a;
			} 
      if(fldlen(6,9)){
				if(*i(6,9)<1 || *i(6,9)>99){curs=10;errnum=34;goto redo_a;}
      }
			if(key==105 && fldlen(66,1)) {stock_loc();goto redo_a;}
			if(key==5006 && fldlen(6,103)){
				*u(6,103)=SelecteerSubgroep(*u(6,9)); 
				fasinit(52);
				if(*u(6,103)){*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;fasgeti(52);}
				copy(s(52,14),nm_subgroep,fldlen(52,14));
				goto redo_a;
			}
			if(key==5007 && fldlen(6,200)){ // blokkeer
				if(*u(6,200)) *u(6,200)=0; else *u(6,200)=1;
				goto redo_a;
			}
			if(key==5008 && fldlen(6,195)){ // webshop artikel
				if(*s(6,195)=='J') *s(6,195)='N'; else *s(6,195)='J';
				goto redo_a;
			}
			if(key==5010 && fldlen(6,194)){ // B2B-webshop artikel
				if(*s(6,194)=='J') *s(6,194)='N'; else *s(6,194)='J';
				goto redo_a;
			}
			if(key==5009 && fldlen(6,104)){ // blokkeer korting 
				if(*s(6,104)=='J') *s(6,104)='N'; else *s(6,104)='J';
				goto redo_a;
			}
			fasinit(52);zero(nm_groep,sizeof nm_groep); 
			if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);copy(s(52,14),nm_groep,fldlen(52,14));}
			zero(nm_subgroep,sizeof nm_subgroep); 
			if(fldlen(6,103)){
				if(*u(6,9)!=last_grp || *u(6,9)==0) *u(6,103)=0; // SUBGROEP WISSEN
				if(*u(6,103) && *u(6,9)){
					if(*u(6,103)>10) errnum=34;
					else{
  					fasinit(52);*u(52,1)=100+*u(6,9)*10+*u(6,103)-1;
	  				if(fasgeti(52)==0) copy(s(52,14),nm_subgroep,fldlen(52,14));
						if(nm_subgroep[0]=='\0') errnum=34;
					}
  			}
				if(errnum) {curs=curspos_; goto redo_a;}
			}
			last_grp=*u(6,9);
      if(*u(6,9)){
				if(key==18){curs=curspos_+1;goto redo_a;}
      }
      if(key==109) key=artik_bis();
      calcnet();
      if(key==106){
				if(mode==2) return NO;
				else return YES;
      }
      if(key!=108 && key!=101 && key!=111) goto redo_a;
			if(fldlen(6,198)) *u(6,198)=procid;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
    }
		fasunlck(-2);
    if(mode==1){
      errnum=fasupd(stu);
      if(stu==2 && fldlen(62,1)){
				*u(62,2)=*u(2,1);
				if(*u(62,1)) fasupd(62); else fasadd(62);
      }
      if(stu==6 && fldlen(66,1)){
				*u(66,2)=*u(6,1);
				if(*u(66,1)) fasupd(66); else fasadd(66);
      }
      fasflush(0);
    }
    if(errnum==48||errnum==49)errnum=9;
		fasunlck(-1);
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
  return YES;
}
 
static stock_loc()
{
  int16 z,k,key,dcurs_,curs=2;
  float tot_vk_=0,tot_ak_=0,q_stk_;
  float stock_[12][2];
	

	only_dsp=NO; if(sys2698) only_dsp=YES;
  fmt_get(66,11); zero((char *)&stock_[0][0],sizeof stock_);
  q_stk_=*f(6,31); if(q_stk_<1) q_stk_=1;
  stock2stks(*f(6,33),q_stk_,&stock_[0][0],&stock_[0][1]);

  if(fldlen(6,57)) tot_vk_=*f(6,57);if(fldlen(6,53)) tot_ak_=*f(6,53);
  for(k=0;k<10;k++) {
    if(fldlen(66,11+k*15)){
      stock2stks(*f(66,11+k*15),q_stk_,&stock_[k+1][0],&stock_[k+1][1]);
    }
    if(fldlen(66,14+k*15)) tot_ak_+=*f(66,14+k*15);
    if(fldlen(66,17+k*15)) tot_vk_+=*f(66,17+k*15);
  }
  zero(&stock_[11][0],sizeof stock_[11]);
  for(k=0;k<11;k++){stock_[11][0]+=stock_[k][0];stock_[11][1]+=stock_[k][1];}
 
  FOREVER{
    redo:;
    scrget(2,232); z=1;
    scrfld(z++,25,1);
    scrofld(z++,6,2,-1);scrofld(z++,6,3,-1);
    scrifld(z++,fm_os6,"DEPOT");
    scrifld(z++,fm_uf5_0,&stock_[0][0]);scrifld(z++,fm_uf3_0,&stock_[0][1]);
    if(fldlen(6,36)) scrifld(z++,fm_uf7_1,f(6,36)); else z++;
    if(fldlen(6,35)) scrifld(z++,fm_uf7_1,f(6,35)); else z++;
    if(fldlen(6,53)) scrifld(z++,fm_uf7_1,f(6,53)); else z++;
    if(fldlen(6,57)) scrifld(z++,fm_uf7_1,f(6,57)); else z++;
    scrfld(z++,6,48);
    scrfld(z++,6,29);

    for(k=0;k<10;k++){
      if(fldlen(66,11+k*15) && nm_loc[k][0]){
	scrifld(z++,fm_os6,&nm_loc[k]);
	scrifld(z++,fm_uf5_0,&stock_[k+1][0]);scrifld(z++,fm_uf3_0,&stock_[k+1][1]);
	scrifld(z++,fm_uf7_1,f(66,12+k*15));
	scrifld(z++,fm_uf7_1,f(66,13+k*15));
	scrifld(z++,fm_uf7_1,f(66,14+k*15));
/*    scrfld(z++,66,16+k*15); */
	scrifld(z++,fm_uf7_1,f(66,17+k*15));
	scrfld(z++,66,19+k*15);
	scrfld(z++,66,20+k*15);
      } else z+=9;
    }
    scrifld(z++,fm_of5_0,&stock_[11][0]);scrifld(z++,fm_of3_0,&stock_[11][1]);
    scrifld(z++,fm_of7_1,&tot_ak_);
    scrifld(z++,fm_of7_1,&tot_vk_);
    dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0xC0);
    if(key==15 && only_dsp && CheckPw(1,11,0)){only_dsp=NO;goto redo;}
    if(key==106) break;
    zero(&stock_[11][0],sizeof stock_[11]);
    for(k=0;k<11;k++){stock_[11][0]+=stock_[k][0];stock_[11][1]+=stock_[k][1];}
    if(fldlen(6,57)) tot_vk_=*f(6,57);if(fldlen(6,53)) tot_ak_=*f(6,53);
    for(k=0;k<10;k++) {
      if(fldlen(66,14+k*15)) tot_ak_+=*f(66,14+k*15);
      if(fldlen(66,17+k*15)) tot_vk_+=*f(66,17+k*15);
    }
    if(key==108){
      stks2stock(f(6,33),q_stk_,stock_[0][0],stock_[0][1]);
      for(k=0;k<10;k++) {
	if(fldlen(66,11+k*15)){
	  stks2stock(f(66,11+k*15),q_stk_,stock_[k+1][0],stock_[k+1][1]);
	}
      }
      break;
    }

  }
}

static stock2stks(stock_,qst_,bak_,fls_)
float stock_,qst_,*bak_,*fls_;
{
  int16 neg_;
  neg_=NO; if(stock_<0){stock_=-stock_;neg_=YES;}
  if(qst_<1) qst_=1;
  *bak_=(long)(stock_); *fls_=0;
  if(qst_>1 && stock_>0){
    *fls_=(long)(((stock_- *bak_) * qst_)+0.49);
  } else *fls_=0;
  if(neg_){*bak_=-*bak_; *fls_=-*fls_;}
}
						
static stks2stock(stock_,qst_,bak_,fls_)
float *stock_,qst_,bak_,fls_;
{
  if(qst_<1) qst_=1;
  *stock_=bak_+ fls_/qst_;
}



static SelecteerSubgroep(mastgroep)
int16 mastgroep;
{

  int16 j,k,key,z,curs,subgrpnr_=0,subnr_[10],max_sg_=0;
  char nm_subgroep[10][50],nm_groep[50],buf750[750];

  int16 nr_,start_,lijnpos,q_;
  char lijn_attrib_;
  uint16 funckeys;
 
	fmt_get(52,14);copy(s(52,1),buf750,fldlen(52,0));
	fasinit(52);*u(52,1)=mastgroep; if(fasgeti(52)) goto endsr;
	copy(s(52,14),nm_groep,fldlen(52,14));
	zero(nm_subgroep,sizeof nm_subgroep);zero((char *)subnr_,sizeof subnr_);
	max_sg_=0;
	for(k=0;k<10;k++){
		*u(52,1)=100+mastgroep*10+k; 
		if(fasgetu(52)==0){
			if(*s(52,14)){
			  copy(s(52,14),nm_subgroep[max_sg_],fldlen(52,14));subnr_[max_sg_++]=k+1;
			}
  	}
	}
	if(max_sg_==0) goto endsr;
  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
    redo:;
    scrnum=0;scrget(1,96);q_=0;
    funckeys=0x80E1;
		if(start_>0) {
      scraddpicto(1,0,76,2,4,2,18,0,4,"up"); 
      funckeys+=2;
    }
		if((start_+D_LIN_SCR)<max_sg_) {
      scraddpicto(2,0,76,21,4,2,13,0,4,"down"); 
      funckeys+=4;
    }
    scrifld(1,fm_os38,nm_groep);z=2;
    for(k=start_;k<start_+D_LIN_SCR;k++){
		  if(k>=max_sg_) break;
      k++;scrifld(z++,fm_ou4,&k);k--;
			scrifld(z++,VarTextFmt(fldlen(52,14),0),nm_subgroep[k]);q_++;
			lijn_attrib_=0xFF;
			if(q_==(lijnpos+1)) lijn_attrib_=0x08;
  		scrchat(z-1,lijn_attrib_);
    }
    scrifld(36,fm_uu3,&nr_);
    key=scrupd(36,funckeys);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    switch(key){
			case 8       : lijnpos--;// pijl opmhoog 
										 if(lijnpos<0) lijnpos=q_-1;
										 break;
			case 9       : lijnpos++;// pijl omlaag 
										 if(lijnpos>=q_) lijnpos=0;
									   break;
			case 12      :// PgUp 
			case 5001    :
			case 102     : if(start_>0){
											 start_-=D_LIN_SCR; if(start_<0) start_=0;lijnpos=0;scrnum=0;
										 }
										 break;
			case 13      :// PgDn 
			case 5002    :
			case 103     : if((start_+D_LIN_SCR)<max_sg_) {start_+=D_LIN_SCR;lijnpos=0;scrnum=0;}
										 break;
			case 10      : start_=0;lijnpos=0;scrnum=0;// HOME 
										 break;
			case 11      : start_=max_sg_-D_LIN_SCR;if(start_<0) start_=0;// END 
										 lijnpos=0;scrnum=0;
										 break;
			case 101     :
			case 106     : goto endsr;// annuleer 
										 break;
			case 18      :// ENTER 
			case 15      : // TAB  
			case 108     : if(nr_>max_sg_) errnum=34;// neem aan en exit 
										 else{
											 if(nr_>0) subgrpnr_=subnr_[nr_-1];
											 else subgrpnr_=subnr_[start_+lijnpos];
											 nr_=0; 
											 goto endsr;
										 }
										 break;
			default      : break;
    }
  }
 
endsr:;
	copy(buf750,s(52,1),fldlen(52,0));
  return subgrpnr_;
}






static scrbfld(z,stu_,fld_,stubuf_,fl_output_)
int16 z,stu_,fld_;
char *stubuf_;
{
  char *pvar_,*pdum_;

  if(fieldspc(stu_,fld_,&pdum_,fmt)>0){
    if(fl_output_) fmt[1]&=0xBF;
    pvar_=stubuf_+ (s(stu_,fld_)-s(stu_,1));
    scrifld(z,fmt,pvar_);
  }
}
 
static uint16 hashbuf(buf_,len_)
char *buf_;
int16 len_;
{
  char *ps;
  int16 k;
  uint16 fuval=0;
					
  k=len_;ps=buf_;
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
}

static artik_bis()
{
  int16 k,curs=3,key,z;
 
  FOREVER{
    redo_a:
    scrget(2,20); z=1;
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
    for(k=27;k<=79;k++) scrfld(z++,6,k);
    for(k=81;k<101;k++) scrfld(z++,6,k);
    key=scrupd(curs,0x03E1);curs=3;
    if(key==106) break;
    for(k=0;k<8;k++) if(*f(6,28)==btw_pct[k]) break;
    if(k==8) {curs=3;errnum=34;goto redo_a;}

    if(key==110 && fldlen(6,70)){
      ean13c(s(6,70));
      ean13c(s(6,71));
    }
    if(key!=108 && key!=101 && key!=109) goto redo_a;
    else break;
  }
  return key;
}

static ean13c(p)                                           /* vers. 00:01 25/02/94 */
char *p;
{
  int16 k, sum;
									
  for (k=0; k<12; k++) {
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

static calcnet()
{
  int16 k,t_ap_;
  float accijns_,net_,q_stuks,bd_,bd_deler_;
									
  t_ap_=18; if(sys3586==2) t_ap_=12;
  if(*f(6,18)) goto calc_wpct;
  net_=*f(6,12);
  if(fldlen(6,13)) net_=valu_cnv(s(6,13),def_munt,(double)net_,(double)0.01);
  if(fldlen(6,30)) accijns_=*f(6,30); else accijns_=0;
  net_-=accijns_;
  if(fldlen(6,17)){
    bd_=*f(6,17);
    if(fldlen(6,13)) bd_=valu_cnv(s(6,13),def_munt,(double)bd_,(double)0.01);
    net_-=bd_;
  }
  for(k=0;k<3;k++) if(fldlen(6,14+k)) net_*=(100.-*f(6,14+k))/100.;
	net_+=accijns_; 
	if(sys3652){ // afhaal en losvergoediong erbij tellen 
		if(fldlen(6,19)) {
			if(sys3652==2) net_*=(100.+*f(6,19))/100.;  // als %
			else net_+=*f(6,19);
		}
		if(fldlen(6,20)) net_+=*f(6,20);
	}
  *f(6,18)=net_;
  calc_wpct:;
  for(k=0;k<10;k++){
    bd_deler_=*f(6,18);
    if(sys3586==2) bd_deler_=*f(6,12);
    else if(sys3586==1) bd_deler_=*f(6,PrNrs[k]);

    if(fldlen(6,PrNrs[k]) && *f(6,t_ap_) && bd_deler_){
      q_stuks=0;
      if(stuksprx[k]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
      if(q_stuks==0) q_stuks=1;
      net_=*f(6,PrNrs[k]);
      if(sys3894 & 1<<k) net_/=1.+*f(6,28)/100.;
      if(sys3586==1) bd_deler_=net_*q_stuks;/* correctie VP-prijs/stuk */
      net_winst[k]=((net_-(*f(6,t_ap_)/q_stuks))/ (bd_deler_/q_stuks)) * 100.;
    }
    else net_winst[k]=0;
  }
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

static streepje(z)
int16 z;
{
  scrifld(z,fm_os7,"      -");
}
 
static initload()
{
  int16 k;
  char str_[20];
									
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  if(fldlen(8,1)) fileopen(8);
  fileopen(9);
  fileopen(11);
  if(fldlen(66,1)) fileopen(12);
  if(fldlen(60,1)) fileopen(14);
  if(fldlen(16,1)) fileopen(13);
  fileopen(15);

  sysget( 294,4,def_munt);
  sysget(1918,2,&sear_stt);
  sysget(1048,32,&btw_pct[0]);
	sysget(2698,2,&sys2698);
	sysget(2770,60,(char *)&nm_loc[0][0]);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
  sysget(3586,2,&sys3586);
  sysget(3588,2,&sys3588);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3632,2,&sys3632);
	sysget(3652,2,&sys3652);
  sysget(3720,2,&sys3720);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  sysget(4670,6,stuksprx);
	sysget(4780,4,&stuksprx[6]);
 
  sysget(3678,2,&def_taal);
  pu_6_1=u(6,1);

  max_dfld=0;
  for(k=21;k<=26;k++){
    zero(str_,sizeof str_);
    copy("Verkooppr. ",str_,11);
    copy(&vptekst[(k-21)*10],&str_[11],6);
    max_dfld+=add_dtab(max_dfld,str_,k);
  }
  for(k=185;k<=189;k++){
    zero(str_,sizeof str_);
    copy("Verkooppr. ",str_,11);
    copy(&vptekst[(k-185+6)*10],&str_[11],6);
    max_dfld+=add_dtab(max_dfld,str_,k);
  }
  max_dfld+=add_dtab(max_dfld,"Netto AK-prijs",18);
  max_dfld+=add_dtab(max_dfld,"Accijns",30);
  max_dfld+=add_dtab(max_dfld,"Aantal/bak",31);
	max_dfld+=add_dtab(max_dfld,"Aantal/pallet",83);
  max_dfld+=add_dtab(max_dfld,"Inhoud",37);
  max_dfld+=add_dtab(max_dfld,"Gewicht",38);
  max_dfld+=add_dtab(max_dfld,"Plaats magaz.",29);
  max_dfld+=add_dtab(max_dfld,"Stock",33);
  max_dfld+=add_dtab(max_dfld,"Inventaris",63);
  max_dfld+=add_dtab(max_dfld,"Inventarisprijs",64);
  max_dfld+=add_dtab(max_dfld,"EAN-code bak",70);
  max_dfld+=add_dtab(max_dfld,"EAN-code stuk",71);
	max_dfld+=add_dtab(max_dfld,"Ref.leverancier",8);
  if(fldlen(6,67)<15)max_dfld+=add_dtab(max_dfld,"DIVERS",67);
  max_dfld+=add_dtab(max_dfld,"LG-code bak",41);
  max_dfld+=add_dtab(max_dfld,"LG-code stuk",44);
  max_dfld+=add_dtab(max_dfld,"Min.stock",36);
  max_dfld+=add_dtab(max_dfld,"Norm.stock",35);
  max_dfld+=add_dtab(max_dfld,"WebshopArtikel",195);
#if FLAGGOU
	max_dfld+=add_dtab(max_dfld,"Koopwarengroep",49);
#endif
  if(faskeyi(6,6,0)==45){                /* controle op key plaats magazijn */
    for(k=0;k<sizeof fm_AKP;k++) if(fm_AKP[k]=='P') fm_AKP[k]='A';
  }
  zero(&seldata.data_begin,sizeof seldata); seldata.dt_s_beg=*u(25,2)-730;
}

static add_dtab(nr_,ptxt_,fld_)
int16 nr_,fld_;
char *ptxt_;
{
 
  if(fldlen(6,fld_)){
    dsp_tab[nr_].fld=fld_;
    copy0(ptxt_,dsp_tab[nr_].omschr);
    return 1;
  } else return 0;
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
 
static nextline()
{
  free=prtline();
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
/*
  if(stu_<=2) parmcall[1]=7;            bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3;                                              GEEN ADD
*/
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

