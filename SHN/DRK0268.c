/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0268GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0268dat
#define ovlcod DRK0268cod
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

char ovldat[] = "drk0268  00:04 05/01/05 (c) Jamadata"; // Aankoopfiches artikels / AK-prijzen per leverancier

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_AKLEV       50

static char *modenm[3]={"aan te passen","toe te voegen","te schrappen"};

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
static float  round();
extern double *d();
extern double valu_cnv();

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os7[]   = {7,0x88,7,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x20,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_of6_0[] = {6,0x94,6,0,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_4[] = {6,0xD4,5,4,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf4_2[] = {6,0xD4,4,2,0x60,0};
static char fm_uf504[] = {6,0xD4,5,4,0x30,0};
static char fm_uf302[] = {6,0xD4,3,2,0x30,0};
static char fm_uf2_2[] = {6,0xD4,2,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};


static int16 prt2pdf;
static int16 stu,groep,free,p_tb;
static char nm_20[20],nm_15[15],oldnm[50],fmt[40],buf750[750];
static uint16 inq_klt,inq_art,inq_lev,inq_groep,dt_exec,dt_beg,dt_end;
static char upd_prx='N',skip_empty='J',sel_per[7],def_munt[4];
static char lev_res[60],klt_res[60],art_res[60],prt_kort='J',disp_kon,prt_det='J';
static float new_prx,sys3614,tb_tot[2][35];
static flag sear_stt,lvcd,klcd,chk_btoeg=NO,sys3618;
static flag sys3876,sys3894,sys4729,sys3624,sys3652;
static int16 fld_nr[4]={6,22,7,8};
static double prx_afrond;

static tb_rec11[DIM_AKLEV];
static struct {
	uint16 rec11;
	uint16 dt_beg;
	char   lcode[20];
	uint16 dt_lastAK;
} tb_AK[DIM_AKLEV];

ovlcod(parmval) // 0: toon actieve 1: toon alles (artikelfiche) 2: enkel fichupd (stu 11 staat klaar)
uint16 parmval;
{
  char orig_art[1500],orig_lev[1500];
	int16 j,k,key,z,d_lin_scr_=5,max_akfiches,start_,show_all_fiches_=NO;
	float verp_factor_;

  if(*u(6,1)==0) ovlexit(-1); // artikelfiche moet ingevuld zijn 
	initload();
	if(parmval==2){fichupd();ovlexit(-1);}
	show_all_fiches_=NO;
	if(parmval==1) show_all_fiches_=YES; // vanuit artikelfiche 
	copy(s(6,1),orig_art,fldlen(6,0));copy(s(1,1),orig_lev,fldlen(1,0));
	max_akfiches=LoadAkFiches(show_all_fiches_); start_=0;
	FOREVER{
		redo:;
		scrnum=0;scrget(2,347);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0268A");
		if(start_>0) scraddpicto(1,0,75,3,4,2,18,0,4,"up"); 
		if((start_+d_lin_scr_)<max_akfiches) scraddpicto(2,0,75,22,4,2,13,0,4,"down"); 
		scrfld(z++,25,1);
		scrofld(z++,6,2,-1);scrofld(z++,6,3,-1);
		if(show_all_fiches_) scrifld(z++,fm_os7," ALLES "); else scrifld(z++,fm_os8," ACTIEF ");
		scrfld(z++,6,11);scrfld(z++,6,12);scrofld(z++,6,18,-1);scrfld(z++,6,46);
  	for(k=start_;k<start_+d_lin_scr_;k++){
			if(k>=max_akfiches) break;
			fasinit(11);fasinit(1);
			if(tb_AK[k].rec11){
				fasinit(11);*u(11,1)=tb_AK[k].rec11;fasgeti(11);
				fasinit(1);*u(1,1)=*u(11,2);fasgeti(1);
			}
			verp_factor_=1.;
			if(fldlen(11,68) && *f(11,68)>0 && *f(6,31)>0 && *f(11,68)!=*f(6,31)) verp_factor_=*f(11,68)/ *f(6,31); 
			*f(11,6)=valu_cnv("EUR","EUR",(double)(*f(11,6)/verp_factor_),(double)0.001);
			*f(11,60)=valu_cnv("EUR","EUR",(double)(*f(11,60)/verp_factor_),(double)0.001);			
			if(sys3652){ // handlingkost erbij tellen, zit niet in AP van AK-fiche
				if(fldlen(6,19)){
					if(sys3652==2) *f(11,60)*=(100.+*f(6,19))/100.;  // als %
					else *f(11,60)+=*f(6,19); 
				}
				*f(11,60)=valu_cnv("EUR","EUR",(double)(*f(11,60)),(double)0.001);
			}

			scrofld(z++,1,3,25);scrfld(z++,11,8);scrfld(z++,11,6);scrofld(z++,11,60,-1);if(*u(11,9)) scrchat(z-1,0x4);
			scrfld(z++,11,63);  scraddpicto(11+k-start_,z-1,1,0,4,2,141,0,0xFF00FF,"Aanpassen"); 
			if(verp_factor_!=1){scrifld(z++,VarTextFmt(13,0),"Aantal/verp. ");scrfld(z++,11,68);}
			else z+=2;
			scrfld(11,68,-1); scrfld(z++,11,75);
		}
		key=scrupd(-1,0xB17);
		if(key==101) break;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
		if(key>=5011 && key<5011+d_lin_scr_){
			if(tb_AK[start_+key-5011].rec11){
				fasinit(11);*u(11,1)=tb_AK[start_+key-5011].rec11;fasgeti(11);
				fasinit(1);*u(1,1)=*u(11,2);fasgeti(1);
			}
			fichupd();
			if(*u(11,1)==0){ // fiche geschrapt
				for(j=start_+key-5011;j<max_akfiches-1;j++) tb_AK[j].rec11=tb_AK[j+1].rec11;
				tb_AK[max_akfiches-1].rec11=0; max_akfiches--;
			}
			else tb_AK[start_+key-5011].rec11=*u(11,1);
			goto redo;
		}
		if(key==105){
			if(show_all_fiches_) show_all_fiches_=NO; else show_all_fiches_=YES;
			max_akfiches=LoadAkFiches(show_all_fiches_);
			start_=0; goto redo;
		}
	  if(key==109 && max_akfiches<DIM_AKLEV){ // toevoegen fiche
			fasinit(11);*u(11,3)=*u(6,1);*u(11,8)=*u(25,2);
			fasinit(1);
			fichupd();
			if(*u(11,1)!=0){ // fiche toegevoegd
				tb_AK[max_akfiches++].rec11=*u(11,1);
			}
			goto redo;
    }
    if(key==110 && (fldlen(16,1) || fldlen(60,12))){
   		fasinit(27);*u(27,2)=*u(25,2)-730;/* 2 jaar terug */
			*s(27,4)='L';// ALLE leveranciers  *u(27,5)=*u(1,1);
			*u(27,6)=*u(6,1);
			if(fldlen(16,1)) ovlcall(239,2); else ovlcall(236,2);
    }
	  if(key==102 || key==5001) {start_-=d_lin_scr_; if(start_<0) start_=0;}
    if(key==103 || key==5002) start_+=d_lin_scr_;
		if(key==112) {Correct11(); break;}
    if(start_>(max_akfiches-d_lin_scr_)) start_=max_akfiches-d_lin_scr_;
		if(start_<0) start_=0;
	}
	endsr:;
	copy(orig_art,s(6,1),fldlen(6,0));copy(orig_lev,s(1,1),fldlen(1,0));
	ovlexit(-1);
}

static LoadAkFiches(int16 show_all_fiches_) // 0=actieve, 1=alle
{
	int16 j,k,mode_,last_k_,sw;
	uint16 last_lev_,last_dt_;
	char buf_[100];
	   
	zero((char *)&tb_AK[0].rec11,sizeof tb_AK);last_dt_=0;last_lev_=0xFFFF;last_k_=-1;
	fasinit(11);*u(11,3)=*u(6,1);mode_=1;
	for(k=0;k<DIM_AKLEV;k++){
		next:;
		if(faskeyi(11,2,mode_)) break; mode_=2;
		if(*u(11,3)!=*u(6,1)) break;
		if(show_all_fiches_==NO){
			if(*u(11,9) && *u(11,9)<*u(25,2)) goto next; // verlopen promotie
			if(last_lev_==*u(11,2)){
				if(*u(11,9)==0 && *u(11,8)>last_dt_ && last_k_>=0){// nieuwe gewone prijs (geen promo)
					for(j=last_k_;j<k-1;j++) copy((char *)&tb_AK[j+1].rec11,(char *)&tb_AK[j].rec11,sizeof tb_AK[0]); 
					k--;zero((char *)&tb_AK[k].rec11,sizeof tb_AK[0]);
				}
			}
			else{last_dt_=0;last_lev_=0;last_k_=-1;}
		}
		tb_AK[k].rec11=*u(11,1);
		tb_AK[k].dt_beg=*u(11,8);
		copy(s(11,5),tb_AK[k].lcode,fldlen(11,5));
		tb_AK[k].dt_lastAK=*u(11,63);
		if(*u(11,9)==0) {last_lev_=*u(11,2);last_dt_=*u(11,8);last_k_=k;}
	}
  FOREVER{/* sorteren */
    sw=NO;
    for(j=0;j<k-1;j++){
			if(tb_AK[j].dt_lastAK<tb_AK[j+1].dt_lastAK){
				copy((char *)&tb_AK[j+1].rec11,buf_,sizeof tb_AK[0]); 
				copy((char *)&tb_AK[j].rec11,(char *)&tb_AK[j+1].rec11,sizeof tb_AK[0]); 
				copy(buf_,(char *)&tb_AK[j].rec11,sizeof tb_AK[0]); 
				sw=YES;
			}
    }
    if(sw==NO) break;
  }
	return k;
}
  
static initload()
{
  int16 j,k;
  char *pdum_;
 
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);
	fileopen(13);

  sysget( 294,4,def_munt);
  sysget(1918,2,&sear_stt);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
  sysget(3624,2,&sys3624);
	sysget(3652,2,&sys3652);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(4729,2,&sys4729);
 
  fieldspc(11,60,&pdum_,fmt);
  k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;
}

static Correct11()
{									// clearen dubbele fiches
	uint16 n,j,k,qrecs_,arec_,lrec_,mode_,rec_;

	
	if(fldlen(11,8)==0 || fldlen(11,9)==0) goto endsr;

	fasinit(11);                            /* scannen op losgeslagen records */
  n=0;scrget(1,7);scrupd(-3,0);fasunlck(-2); arec_=0;lrec_=0;mode_=1;fasinit(11);
	zero((char *)&tb_AK[0].rec11, sizeof tb_AK); qrecs_=0;
  FOREVER{
		next:;
		if(faskeyi(11,2,mode_)) break; mode_=2;
		if(*u(11,2)==0){faskill(11); goto next;} // geen leverancier
		fasinit(1);*u(1,1)=*u(11,2); if(fasgeti(1)){faskill(11); goto next;} // ongeldige leverancier
		if(arec_!=*u(11,3) || lrec_!=*u(11,2)){
			rec_=*u(11,1);
			if(qrecs_>1){ // enkel indien meer per leverancier
				for(k=0;k<qrecs_;k++){
					fasinit(11);*u(11,1)=tb_AK[k].rec11; fasgeti(11);
					if(k<qrecs_-1 && *s(11,5)=='\0'){faskill(11);tb_AK[k].rec11=0;goto next_k;} // enkel laatste overhouden indien geen code
					for(j=k+1;j<qrecs_;j++){
						if(tb_AK[j].lcode[0]=='\0' || cmpstr(tb_AK[k].lcode,tb_AK[j].lcode,fldlen(11,5))==0) {// bij zelfde of lege opschuiven naar 1 hoger
	  					copy(tb_AK[k].lcode,tb_AK[j].lcode,fldlen(11,5));faskill(11);tb_AK[k].rec11=0;goto next_k;
						}
					}
					copy(tb_AK[k].lcode,s(11,5),fldlen(11,5)); fasupd(11);
next_k:;
				}
			}
			zero((char *)&tb_AK[0].rec11, sizeof tb_AK); qrecs_=0;
			fasinit(11);*u(11,1)=rec_;fasgeti(11);
			arec_=*u(11,3);lrec_=*u(11,2);
		}
		if(qrecs_<DIM_AKLEV){
			tb_AK[qrecs_].rec11=*u(11,1);
			tb_AK[qrecs_].dt_beg=*u(11,8);
			copy(s(11,5),tb_AK[qrecs_].lcode,fldlen(11,5));
			qrecs_++;
		}
	}
	if(qrecs_>1){ // enkel indien meer per leverancier
		for(k=0;k<qrecs_;k++){
			fasinit(11);*u(11,1)=tb_AK[k].rec11; fasgeti(11);
			if(k<qrecs_-1 && *s(11,5)=='\0'){faskill(11);tb_AK[k].rec11=0;goto next_k1;} // enkel laatste overhouden indien geen code
			for(j=k+1;j<qrecs_;j++){
				if(tb_AK[j].lcode[0]=='\0' || cmpstr(tb_AK[k].lcode,tb_AK[j].lcode,fldlen(11,5))==0) {// bij zelfde of lege opschuiven naar 1 hoger
	  			copy(tb_AK[k].lcode,tb_AK[j].lcode,fldlen(11,5));faskill(11);tb_AK[k].rec11=0;goto next_k1;
				}
			}
			copy(tb_AK[k].lcode,s(11,5),fldlen(11,5)); fasupd(11);
next_k1:;
		}
  }
	endsr:;
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

static fichupd()
{
  int16 mask_,curs,k,key,z,z_base,mode;
 
	mode=1; if(*u(11,1)==0) mode=2;
  errnum=0; mask_=0x1E1; if(mode==1) mask_=0x1E0;
	if(mode==2){
		for(k=0;k<5;k++) {
			if(fldlen(11,12+k*10)) *s(11,12+k*10)='N';
			if(fldlen(11,13+k*10)) *s(11,13+k*10)='E';
			if(fldlen(11,14+k*10)) *s(11,14+k*10)='F';
		}
	}
  if(mode==1) curs=6; else curs=1;
  fasinit(1);*u(1,1)=*u(11,2);fasgeti(1);
//  fasinit(6);*u(6,1)=*u(11,3);fasgeti(6);
  FOREVER{
    copy(s(1,3),lev_res,fldlen(1,3));
    copy(s(6,3),art_res,fldlen(6,3));
    redo:
    scrget(2,348);z=1;
    scrfld(z++,25,1);
    scrofld(z++,1,lvcd+1,-1);scrfld(z++,1,3);
    if(fldlen(6,2)) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
    for(k=4;k<=5;k++) scrfld(z++,11,k);
		scrfld(z++,11,68);
		for(k=6;k<10;k++) scrfld(z++,11,k);
    z_base=z;
    for(k=10;k<=67;k++) if(k==60 || k==61) scrofld(z++,11,k,-1); else scrfld(z++,11,k);
		z++; // 68: aantal/bak bovenaan
		for(k=69;k<100;k++) scrfld(z++,11,k);
    key=scrupd(curs,0x2E9);curs=13;
    if(key==106){
      if(mode==2) return NO;
      else return YES;
    }
    if(key==101 && mode==2) break;
		if(key==104){
			if(scr_ok("Wenst U echt deze aankoopfiche te schrappen???")==YES){
				if(*u(11,1)) faskill(11);
				fasinit(11);
				break;
			}
		}
    if(*s(1,3)=='\0' || cmp_str(s(1,3),lev_res,fldlen(1,3))){
      if(search(1,0)) {curs=3;goto redo;}
      copy(s(1,3),lev_res,fldlen(1,3));
    }
    //if(*s(6,3)=='\0' || cmp_str(s(6,3),art_res,fldlen(6,3))){
    //  if(search(6,0)) {curs=5;goto redo;}
    //  copy(s(6,3),art_res,fldlen(6,3));
    //  if(*f(11,65)==0) *f(11,65)=*f(6,30);
    //}
    if(fldlen(11,7)){
      valu_cnv(s(11,7),def_munt,1.,1.);
      if(errnum) {curs=9; goto redo;}
    }
    for(k=0;k<5;k++) if(*f(11,10+k*10)){
      if(*s(11,11+k*10)=='\0'){errnum=38;curs=z_base+k*10+1;goto redo;}
      if(*s(11,12+k*10)=='\0'){errnum=38;curs=z_base+k*10+2;goto redo;}
      if(*s(11,13+k*10)=='\0'){errnum=38;curs=z_base+k*10+3;goto redo;}
      if(*s(11,14+k*10)=='\0'){errnum=38;curs=z_base+k*10+4;goto redo;}
    }
    calculate();
    *u(11,2)=*u(1,1);
    *u(11,3)=*u(6,1);
    if(key==106){
      if(mode==2) return NO;
      else return YES;
    }
    if(key==110 && (fldlen(16,1) || fldlen(60,12))){
   		fasinit(27);*u(27,2)=*u(25,2)-730;/* 2 jaar terug */
			*s(27,4)='L'; *u(27,5)=*u(1,1);
			*u(27,6)=*u(6,1);
			if(fldlen(16,1)) ovlcall(239,2); else ovlcall(236,2);
    }
    if(key!=108 && key!=101) goto redo;
    if(mode==1){
      errnum=fasupd(11);
    }
    else if(mode==2){
      errnum=fasadd(11);
    }
/*
    if(*u(1,1)==*u(6,7) && sys3624!=0){// indien hoofdleverancier dan prijzen updaten 
      *f(6,12)=*f(11,6);
      if(fldlen(11,7)) copy(s(11,7),s(6,13),fldlen(6,13));
      *f(6,14)=0;*f(6,17)=0;
      for(k=0;k<5;k++){
				if((sys4729 || *s(11,14+k*10)=='D') && *f(11,10+k*10)){
					if(*s(11,11+k*10)=='%') *f(6,14)+=*f(11,10+k*10);
					else *f(6,17)+=*f(11,10+k*10);
				}
      }
      if(sys4729) *f(6,18)=*f(11,61);
      else{
				*f(6,18)=*f(11,60);
				if(fldlen(11,7)){
					*f(6,18)=valu_cnv(s(11,7),def_munt,(double)*f(11,60),(double)0.001);
				}
      }
      fasupd(6);
    }
*/
    fasflush(0);
    if(errnum==48||errnum==49)errnum=9;
    if(!errnum) break;
  }
  if(key==101) return NO;/* stop */
  return YES;
}

static calculate()
{
  int16 j,k;
  float ap_brut, ap_net, ap_stat, ap_, bd_acc, verp_factor_=1.;
 
	if(fldlen(11,68) && *f(11,68)>0 && *f(6,31)>0 && *f(11,68)!=*f(6,31)) verp_factor_=*f(11,68)/ *f(6,31); 
  ap_brut=*f(11,6);
  ap_net=ap_brut;ap_stat=ap_brut;	bd_acc=*f(6,30)*verp_factor_;
  if(ap_brut==0){
    for(k=0;k<5;k++) *f(11,15+k*10)=0;
    goto calc_ok;
  }
  for(k=0;k<5;k++){
    if(*f(11,10+k*10)){
      if(*s(11,11+k*10)=='H') *f(11,15+k*10)=*f(11,10+k*10) * *f(6,37)/100; // HL-korting
      else if(*s(11,11+k*10)=='%'){ // % korting
				ap_=ap_brut;
				if(*s(11,12+k*10)!='B'){
					for(j=0;j<k;j++){
						if(*s(11,14+j*10)) ap_-=*f(11,15+j*10);
					}
				}
				if(*s(11,13+k*10)!='I') ap_-=bd_acc;
				*f(11,15+k*10)=valu_cnv("EUR","EUR",(double)(ap_ * *f(11,10+k*10)/100.),prx_afrond);
			}
			else *f(11,15+k*10)=*f(11,10+k*10); // eur korting 
		} else *f(11,15+k*10)=0;
  }
  calc_ok:;
  ap_net=ap_brut;ap_stat=ap_brut;
  for(k=0;k<5;k++){
    ap_stat-=*f(11,15+k*10);
    if(*s(11,14+k*10)=='F') ap_net-=*f(11,15+k*10);
  }
  *f(11,60)=ap_net;
  if(fldlen(11,7)){
    ap_stat=valu_cnv(s(11,7),def_munt,(double)ap_stat,(double)0.001);
  }
  *f(11,61)=ap_stat;/* steeds in DEF-munt */
  endsr:;
}
 
static float round(value_)
double value_;
{
  float add;
								
  add=sys3614; if(value_<0) add=-add;
  if(sys3618==0) add/=2.;
  add=add*.999999;
  if(sys3614>0.0001){
    value_=((long)((value_+add)/sys3614)) * sys3614;
  }
  return (float)(value_);
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

static streepje(z)
int16 z;
{
  scrifld(z,fm_os1,"-");
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
  parmcall[7]=0x00;/* ALLE REKENINGEN ! */
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}

 
