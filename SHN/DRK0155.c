/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0155GetD() {return &zzvw;}

#define ovldat DRK0155dat
#define ovlcod DRK0155cod
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

#include "OvlShare.h"

char ovldat[] = "drk0155  00*01 29/09/10 (c) Jamadata";
	
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DIM8            34
#define DIM58           400
#define EL_BKH          150
#define DF_GRB          15
#define MINFREE         150
#define OPMLEN          20
#define BTWDIV          2
#define BTWDIM          8+BTWDIV
#define MAXFLD          120
#define WRK_REF         155/* referentie nummer van wrk-blokken */
#define WRK_DTNR        100  /* volgnummer van detail-blokken (blok=scherm) */
#define flag            uint16

#ifndef _WIN32
#include "E:\par0155.c"
#else
#include "par0155.c"
#endif

extern char RamBon[];
extern int RamBonSize;
static int SpoolFileNr;
static int16 len58_35,len8_23;
static double *pd_58_35;
static char *ps_8_23,ft_munt[3];
									
#define BEDRAG          double
static char fmeobd[]   = {6,0x95,6,2,0x70,0};                          /* fm_od9_2 */
static char fmeobdk[]  = {6,0x95,5,2,0x70,0};
static char fmeobdk1[] = {6,0x95,6,2,0x60,0};                    /* geen 1000-punt */
static char fmeobdk2[] = {6,0x95,6,2,0x60,0};
									
static char fmfobd[]   = {6,0x95,9,0,0x70,0};                          /* fm_od9_0 */
static char fmfobdk[]  = {6,0x95,7,0,0x70,0};
static char fmfobdk1[] = {6,0x95,7,0,0x70,0};
static char fmfobdk2[] = {6,0x95,7,0,0x70,0};
#define TABT            "<t69>"
									
static char fm_obd[40],fm_obdk[40],fm_obdk1[40],fm_obdk2[40];
static double ft_afrond,prx_afrond;

#if FIRMAPRT
static struct {
  int16 begpos;
  int16 lengte;
  char *txt[4];
} firm[10] = {116,17,"Telefoon","N– t…l…phone","Telephone","Telefon",
	     170,17,"Telefax","Telefax","Fax","Telefax",
	      86,15,"B.T.W. nr.","N– T.V.A.","T.V.A.","M.W.S.",
	     101,14,"Bankrek.","Banque","Bank","Bank",
	     134,12,"RPR","RPM","","",
	     149,20,"Erkenningsnr","","","",
	     188,30,"Web-site","Web-site","","",
	     222,30,"E-mail","E-mail","","",
	     256,42,"IBAN","IBAN","IBAN","IBAN",
	     298,11,"BIC","BIC","BIC","BIC"};
#endif

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_us75[]  = {7,0xC8,75,0,0,0,0};
static char fm_us60[]  = {7,0xC8,60,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us25[]  = {7,0xC8,25,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us7[]   = {7,0xC8,7,0,0,0,0};
static char fm_us2_U[] = {7,0xC8,2,0,1,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os60[]  = {7,0x88,60,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os25[]  = {7,0x88,25,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os7[]   = {7,0x88,7,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x20,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static char fm_of6_0[] = {6,0x94,6,0,0x70,0};
static char fm_uf3_3[] = {6,0xD4,3,3,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf2_0[] = {6,0xD4,2,0,0x70,0};
static char fm_uf21_[] = {6,0xD4,2,1,0x20,0};
static char fm_ul8[]   = {6,0xD3,8,0,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_menu[]  = {7,0x48,1,0,8,0,0};
static char fm_uALN[]  = {13,0xC8,1,0,1,0,'A','A','L','L','N','N',0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_u_04[]  = {10,0xD0,1,0,0x60,0xC0,0,0,4,0};

extern char *s();
static flag yet_booked();
extern int16 *i();
extern uint16 *u(),dateadd();
static uint16 find_grb(),sear_grb(),hash();
extern long *l(),val();
static long makegrb();
extern float *f();
extern double *d(),valu_cnv();
static double getsaldo();
static BEDRAG round();
static uint16 GetAKFiche(arec_,lrec_,dt_beg_);
							
extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];


static struct {
  int16 typ;
  char *pnm;
} aard[] = {10,"AK",110,"OF",120,"BS",130,"CO",180,"LV",190,"FK"};

#if BOEKALLO
static uint16 rec_nr[EL_BKH],df_recnr[DF_GRB];
static int16 journl;
static long grb_tb[EL_BKH],opmhoev[EL_BKH];
static long kltcent,grb_notf;
static BEDRAG bedrag[EL_BKH];
static char df_rek[DF_GRB][4];
#endif

static int16 det_nr[]={7,62,15,16,20,100};
static int16 wrk_in_ram,dbl_factor;
static int16 stu,prmode,prt_error,free,z_base,hash_len,akpr_len,ft_off,max_kassa,upd_mode,chk_nr,SysPosNrCheck;
static int16 def_qfact,btw_kol,zz,stu58_len,notfound=0;
static int16 b2228,b3604,b3606,skip_off;
static int16 form_dat[8],prtnr,dok_type,taaltxt,q_per_line;
static int16 prt2pdf;
static uint16 ft_date,ft_nr,last_ft,last_fta,last_vf,last_vfa,verv_dt;
static uint16 max_line,filiaal,auto_enter,orig_klt,DefaultFiliaal;
static uint16 rec_8[DIM8],loc_klt[20],loc_nr[20],dt_kvk[20];

static long ram_size;
static char *voldtxt[4] = {"Voldaan","Pour acquit","Received","Betrag erhalten"};
static char firma[350],*ram,b3598[6];
static char opm_foot[4][75],nm_dehr[43],std_txt[4][61],buf1000[1000];
static char fmt[40],prt_levbon='J',sortbuf[1000],boek_JN='J';
static char def_munt[4],nm_fil[6],van_fil[6],nm_loc[10][6],nm_kassa[20][6],OnlyWithDepotStock;
static BEDRAG alg_tot,belastbt,btw_tot,btw_bas[BTWDIM],tot_leeg;
static BEDRAG btw_bd[BTWDIM];
static float def_btw, max_btw, btw_pct[BTWDIM];
static flag art_exist,chk_btoeg,boek_mode;
static flag hist_exist,sear_stt,lvcd,klcd;
static flag stuk_per_stuk=YES,keepdata,sys2170,sys1787;
static flag sys3624,sys3590,sys3876,centiem,sys3588,sys3720,sys4608;

static int16 len58_25,len58_15,len58_62;
static char *ps_1_3,*ps_58_16,*ps_58_25,*ps_58_15,*ps_58_62;
static uint16 *pu_8_28,*pu_6_1,*pu_58_14,*pu_58_1;
static float *pf_58_20,*pf_58_31,*pf_58_50,*pf_58_24,*pf_58_21;
static char talen[4];

#if SEARBFLEN
static float btwpct[4];
static uint16 vers_298;
static char taal_i;
static char searbuf[SEARBFLEN+1];
#endif

#if PDA_INPUT
static char *rec_ele();
static float get_num();
extern uint16 datejd();
static uint16 get_date();
#endif
static uint16 pdad_beg,pdad_end,pda_nr,sys4408;
static char filnam[80], *p_data;
static long *pl_80_1;


ovlcod(parmval)
int16 parmval;
{
  int16 curs=1,key,z;
  char choice='\0';
									
  initload();
  ft_date=*u(25,2); chk_nr=YES;
	if(parmval==1){add_bon(); goto endsr;} 

  FOREVER{
		redo:;
    scrget(2,235);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0155A");
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) ovl_exit(218);
    if(key==111) ovl_exit(0);
    switch(choice){
      case '1': upd_bon();break;
      case '2': add_bon();break;
      case '3': kil_bon();break;
      case '4': bon_lst();break;
      case '5': inboeken();break;
      case '6': add_boek();break;
      default : errnum=34; break;
    }
  }
	endsr:;
}

static upd_bon()
{
  boek_mode=NO; upd_mode=YES;
  FOREVER{
    ft_init();prt_levbon='J';
    redo:
    if(!get_lev("Van welk filiaal wenst u een bon aan te passen:",YES,NO))break;
    if(!load_bon(NO,0,THISTYP))goto redo;
    if(exec()){
      write_bon();
    }
  }
}

static add_bon()
{
  int16 j,key,z,new_=0,mode_;
  char choice;

  boek_mode=NO; upd_mode=NO;
  FOREVER{
    scrget(2,236);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(2,0x401);
    if(key==101) goto endsr;
    if(key==111) ovl_exit(0);
    switch(choice){
      case '1': new_=YES;break;
      case '2': new_=NO;break;
      default : errnum=34; break;
    }
    if(!errnum){
      FOREVER{
				sysget(last_vfa,2,&last_vf);
				ft_init();*u(8,2)=last_vf+1;prt_levbon=DEFLVPRT;
				if(new_==NO){
					if(!get_lev("Aan welk filiaal wenst u te leveren:",YES,YES)) break;
					seldata.selp_use=NO;
					if(ovlcall(2215,1)) break;
					scrget(1,7);scrupd(-3,0);
					fasinit(6);mode_=2;j=0;
					FOREVER{
						next_art:;
						if(faskeyi(6,1,mode_)) break; mode_=2;
//						if(OnlyWithDepotStock=='J' && *f(6,33)==0) goto next_art;
            if(DirCall_DRK2215_SelectArtikel()){
							fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
							if(OnlyWithDepotStock=='J'){
								if(*u(8,38)<1 || *u(8,38)>10){
								  if(*f(6,33)==0) goto next_art;
								}
								else if(*f(66,11+(*u(8,38)-1)*15)==0) goto next_art;
							}
							
							if(filiaal==99){
								*f(6,33)=valu_cnv("EUR","EUR",(double)(*f(6,33)),(double)(0.001)); // om vieze dingen na komma weg te doen
								if(*f(6,33)< *f(6,36)){
									fasinit(58);
									copy(s(6,2),s(58,15),len58_15);
									*u(58,14)=*u(6,1);
									copy(s(6,3),ps_58_16,fldlen(58,16));
									Fill1Line();*u(58,17)=hash();
									*f(58,7)=(long)(*f(6,35)-*f(6,33)+.49);
									if(*f(58,7)==0) fasinit(58); // enkel volle stuks
									else stu2ram(j++);
								}
							}
							else{
								*f(66,11+(filiaal-1)*15)=valu_cnv("EUR","EUR",(double)(*f(66,11+(filiaal-1)*15)),(double)(0.001)); // om vieze dingen na komma weg te doen
								if(*f(66,11+(filiaal-1)*15) < *f(66,12+(filiaal-1)*15))	{
									fasinit(58);
									copy(s(6,2),s(58,15),len58_15);
									*u(58,14)=*u(6,1);
									copy(s(6,3),ps_58_16,fldlen(58,16));
									Fill1Line();*u(58,17)=hash();
									if(*f(66,13+(filiaal-1)*15)==0) *f(66,13+(filiaal-1)*15)=*f(66,12+(filiaal-1)*15); // normale stock niet ingevuld
									*f(58,7)=(long)(*f(66,13+(filiaal-1)*15)-*f(66,11+(filiaal-1)*15)+.49);
									if(*f(58,7)==0) fasinit(58); // enkel volle stuks
									else stu2ram(j++);
							  }
							}
							if(j>max_line) break;
						}
					}
					*i(8,36)=THISTYP;*u(8,2)=last_vf+1;*u(8,8)=*u(25,2);
					*u(8,3)=filiaal;
					keepdata=YES;
				}
				if(exec()==NO) break;
				write_bon();
				last_vf=*u(8,2);
				sysput(last_vfa,2,&last_vf);
				ClearSysPosNrCheck();
      }
    }
  }
  endsr:;
}

static kil_bon()
{
  boek_mode=NO; upd_mode=YES;
  FOREVER{
    ft_init();
    redo:
    if(!get_lev("Van welk filiaal wenst u een bon te schrappen:",YES,NO)) break;
    if(!load_bon(NO,0,THISTYP)) goto redo;
    if(!ok_kil()) goto redo;
    kill();
  }
}

static add_boek()
{
  boek_mode=YES; upd_mode=NO;
  FOREVER{
    sysget(last_vfa,2,&last_vf);
    ft_init();*u(8,2)=last_vf+1;prt_levbon='J';

    if(exec()){
      if(upd_stock(YES)) break;
#if BOEKALLO
      if(boek_JN=='J') {
	boekbkh();
	last_ft=ft_nr; sysput(last_fta,2,&last_ft);
	sysflush();
      }
#endif
      last_vf=*u(8,2);
      sysput(last_vfa,2,&last_vf);
			ClearSysPosNrCheck();
    }
    else break;
  }
}

static inboeken()
{
  boek_mode=YES; upd_mode=YES;
  FOREVER{
    ft_init();prt_levbon='J';
    redo:
    if(!get_lev("Van welk filiaal wenst u een bon in te boeken:",YES,NO))break;
    if(!load_bon(NO,0,THISTYP))goto redo;
    if(exec()){
      if(upd_stock(NO)) break;
#if BOEKALLO
      if(boek_JN=='J') {
	boekbkh();
	last_ft=ft_nr; sysput(last_fta,2,&last_ft);
	sysflush();
      }
#endif
    }
  }
}

static upd_stock(direct_)
int16 direct_;
{
  int16 k,key,len_,v_fil_;
  flag nalevering=NO,del_stu8;
  float qlv_,belastbf,factor_;

  if(direct_) {nalevering=NO;goto do_upd;}
  redo:;
  if(chk_qlv()){
    nalevering=NO;
    scrget(2,57);
    key=scrupd(-1,0x2A);
    switch(key){
      case 104: nalevering=YES;break;
      case 106: nalevering=NO;break;
      default : if(dsp_detail()==NO) return YES;else goto redo;break;
    }
  }
  do_upd:;
  len_=akpr_len; if(sys3624) len_-=fldlen(6,18)+fldlen(6,19)+fldlen(6,20);
  v_fil_=*u(8,38); if(v_fil_<1 || v_fil_>10 || v_fil_==filiaal) v_fil_=0;
  for(k=0;k<max_line;k++){
    ram2stu(k);
    *u(6,1)=*u(58,14);
    if(*u(6,1) && *pf_58_31){
      if(fasgetu(6)==0){
				factor_=1.;
				if(fldlen(6,102) && *u(6,102)){// stock/omzet op moederfiche bijwerken
			    factor_=*f(6,31);
			    *u(6,1)=*u(6,102);fasgeti(6);
			    if(*f(6,31)) factor_/=*f(6,31); else factor_=1.;
		    }
				fasinit(66);*u(66,2)=*u(6,1);
				if(faskeyi(66,1,0)) {fasinit(66);*u(66,2)=*u(6,1);errnum=fasadd(66);}
#if STATISTIEK
				statistiek_upd();
#endif
				belastbf=*pd_58_35;
				qlv_=*pf_58_31*factor_; if(len58_62 && *ps_58_62=='S') qlv_/=*f(58,63);
				if(filiaal<=10){
  				stu_add(66,11+(filiaal-1)*15,&qlv_);
	  			stu_add(66,14+(filiaal-1)*15,&qlv_);
		  		*u(66,16+(filiaal-1)*15)=*u(25,2);
				}
				else stu_add(6,33,&qlv_);
#if HISTORIEK
				if(filiaal<1 || filiaal>10) *u(1,1)=30000; else *u(1,1)=30000+filiaal;	_his_upd(*u(6,1),&qlv_,&belastbf);
#endif
				qlv_=-*pf_58_31*factor_; if(len58_62 && *ps_58_62=='S') qlv_/=*f(58,63);
				if(v_fil_){/* mutatie */
					stu_add(66,11+(v_fil_-1)*15,&qlv_);
					stu_add(66,14+(v_fil_-1)*15,&qlv_);
					*u(66,16+(v_fil_-1)*15)=*u(25,2);
				}
				else {
					stu_add(6,33,&qlv_);
				}
#if HISTORIEK
				if(v_fil_<1 || v_fil_>10) *u(1,1)=30000; else *u(1,1)=30000+v_fil_;	_his_upd(*u(6,1),&qlv_,&belastbf);
#endif
			  if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				fasupd(6);
				if(*u(66,1)) fasupd(66); else fasadd(66);
	    }
      if(*u(58,48) && *u(58,14)!=*u(58,48)){ // leeggoed
				fasinit(6);*u(6,1)=*u(58,48);fasgeti(6);
				fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
				qlv_=*f(58,49) * *pf_58_31;
				if(filiaal<=10){
  				stu_add(66,14+(filiaal-1)*15,&qlv_);
  				stu_add(66,11+(filiaal-1)*15,&qlv_);
  				*u(66,16+(filiaal-1)*15)=*u(25,2);
				}
				else stu_add(6,33,&qlv_);
#if HISTORIEK
				if(filiaal<1 || filiaal>10) *u(1,1)=30000; else *u(1,1)=30000+filiaal;	_his_upd(*u(6,1),&qlv_,f(58,47));
#endif
				if(v_fil_){/* mutatie */
					qlv_=-qlv_;
					stu_add(66,14+(v_fil_-1)*15,&qlv_);
					stu_add(66,11+(v_fil_-1)*15,&qlv_);
					*u(66,16+(v_fil_-1)*15)=*u(25,2);
				}
				else{
					stu_add(6,53,&qlv_);
					stu_add(6,54,f(58,47));
					stu_add(6,55,&qlv_);
					stu_add(6,56,f(58,47));
					qlv_=-qlv_;stu_add(6,33,&qlv_);
				}
#if HISTORIEK
				belastbf=-*f(58,47);
				if(v_fil_<1 || v_fil_>10) *u(1,1)=30000; else *u(1,1)=30000+v_fil_;	_his_upd(*u(6,1),&qlv_,&belastbf);
#endif
			  if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				fasupd(6); if(*u(66,1)) fasupd(66); else fasadd(66);
      }
    }
    if(*u(58,1) && nalevering){
      qlv_=*pf_58_31;
      fasgeti(58);
      qlv_=*pf_58_31-qlv_;if(qlv_<0) qlv_=0;
      ram2stu(k);
      if(qlv_ && *pf_58_31+qlv_) *pd_58_35=*pd_58_35 * qlv_/(*pf_58_31+qlv_);
      *pf_58_31=qlv_;*f(58,7)=qlv_;if(fldlen(58,62) && *s(58,62)!='S') *s(58,62)='\0'; stu2ram(k);
    }
    else *pf_58_31=0;
    stu2ram(k);
  }
  if(direct_) goto endsr;
  del_stu8=YES;
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*u(58,1)){
      if(*pf_58_31) {fasupd(58);del_stu8=NO;}
      else faskill(58);
    }
  }
  if(del_stu8) faskill(8);
  else {
		sysget(last_vfa,2,&last_vf);
		*u(8,2)=last_vf+1;prt_levbon=DEFLVPRT;*u(8,8)=*u(25,2);
		*i(8,36)=THISTYP;
		if(fldlen(8,71)) *u(8,71)=procid;
		if(fldlen(8,72)) *u(8,72)=*u(25,2);
		fasupd(8);
		last_vf=*u(8,2);
		sysput(last_vfa,2,&last_vf);
		ClearSysPosNrCheck();
	}
  endsr:;
  return NO;
}

#if HISTORIEK
static _his_upd(rec_,qlv_,bd_)
uint16 rec_;
float *qlv_,*bd_;
{
  uint16 k,jj,mm,dd,dt_;
  flag add_rec_;
	float tr_aantal_,factor_;
  long ft_nr_;

  if(fldlen(16,15)==0) goto endsr;
  dt_=*u(25,2); // if(*u(8,37)) dt_=*u(8,37);
  jddate(dt_,&jj,&mm,&dd);
  ft_nr_=*u(8,2);

//  fasinit(6);*pu_6_1=rec_;if(fasgeti(6)) goto endsr;
  if(fldlen(6,76) && *s(6,76)!='J') goto endsr;
 
  fasinit(16);*l(16,20)=rec_;*l(16,15)=*u(1,1);*l(16,2)=ft_nr_;*u(16,3)=dt_;
  if(*l(16,15)==0) goto endsr;/* leverancier MOET ingevuld zijn */
  if(faskeyu(16,1,0)) add_rec_=YES;
  else add_rec_=NO;
  if(*l(16,2)!=ft_nr_){add_rec_=YES;fasinit(16);}
  *l(16,2)=ft_nr_;
  *u(16,3)=dt_;
	if(fldlen(16,8)) *u(16,8)=*u(1,1)-30000; // filiaalnr
  *l(16,15)=*u(1,1);
  *l(16,20)=*u(6,1);
  copy(s(6,2),s(16,21),fldlen(16,21));
  copy(s(6,3),s(16,22),fldlen(16,22));
  *l(16,23)=*u(6,9);/* groep */
	if(fldlen(6,103) && fldlen(16,28)) *u(16,28)=*u(6,103); // subgroep
  *f(16,24)=*f(6,28);/* BTW% */
  copy(s(6,10),s(16,25),fldlen(16,25));/* eenheid */
  if(fldlen(6,31)) *f(16,26)=*f(6,31);/* q_bak */
  if(fldlen(6,30)) *f(16,27)=*f(6,30);/* accijns */
  *d(16,30)+=*qlv_;/* aantal */
  *d(16,31)+=*bd_;/* vw */
  *d(16,32)+=*bd_;/* aw */
  if(add_rec_) errnum=fasadd(16);
  else errnum=fasupd(16);
  if(errnum){
    if(errnum==48||errnum==49)errnum=9;
    scrget(1,170);
    scrifld(5,fm_os63,"    Fout tijdens het bijwerken van de historieken.");
    scrifld(10,fm_os63,"Druk F8 om verder te gaan");
    scrupd(-1,0x80);
    scrget(1,7);scrupd(-3,0);
  }
  endsr:;
}
#endif



#if STATISTIEK
static statistiek_upd()
{
  int16 dd=0,mm=0,jj=0;
  flag add_rec_;
					
  if(fldlen(60,12)==0) goto endsr;
  jddate(*u(25,2),&jj,&mm,&dd);mm--;
  fasinit(60);
  *l(60,22)=*u(58,14);
  *l(60,12)=filiaal;
  if(faskeyu(60,2,0)) add_rec_=YES;
  else add_rec_=NO;
  *i(60,24)= *i(6,9);
  copy(s(6,2),s(60,23),fldlen(6,2));
  if(fldlen(60,82)) *f(60,82+mm)+=*d(58,35);
  if(fldlen(60,112)) *f(60,112+mm)+=*pf_58_31;
  if(add_rec_) errnum=fasadd(60);
  else errnum=fasupd(60);
  if(errnum){
    if(errnum==48||errnum==49)errnum=9;
    scrget(1,170);
    scrifld(5,fm_os63,"    Fout tijdens het bijwerken van de statistieken.",-1);
    scrifld(10,fm_os63,"     Druk <TAB> om verder te gaan.",-1);
    scrupd(-1,0);
    scrget(1,7);scrupd(-3,0);
  }
  endsr:;
}
#endif

static chk_qlv()
{
  int16 k;
  float qlv_;

  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*u(58,1) && *ps_58_16){
      qlv_=*pf_58_31;
      fasgeti(58);
      if(qlv_<*pf_58_31) {ram2stu(k);return YES;}
    }
  }
  return NO;
}
 
static ft_init()
{
  int16 k;

  filiaal=0; zero(nm_fil,6);
  fasinit(8);

  *pu_8_28=1;
  *u(8,8)=*u(25,2);
  for(k=0;k<2;k++) if(fldlen(8,31+k)) *s(8,31+k)='N';
  for(k=0;k<4;k++) opm_foot[k][0]='\0';
  copy("EUR",ft_munt,3);
  if(len8_23) copy(ft_munt,ps_8_23,3);
  belastbt=0;tot_leeg=0;alg_tot=0;
  init58(0,NO);keepdata=NO;
	if(ovltest(2241))	zero(BestelFileUsed,sizeof BestelFileUsed); 
}

static init58(start_,mode_)
int16 start_,mode_;
{
  int16 k;

  fasinit(58);
  *pf_58_24=def_btw;
  for(k=start_;k<max_line;k++) {stu2ram(k);if(mode_) break;}
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

static initload()
{
  int16 j,k;
  char *pdum_;

  fasunlck(0);
  fileopen(1);
  fileopen(2);
#if BOEKALLO
  fileopen(3);
  fileopen(4);
#endif
  fileopen(6);
  fileopen(8);
  fileopen(12);
  fileopen(14);
  sysget(3590,2,&sys3590);
  if(((sys3590&2)==2) && fldlen(10,1)>0){
    fileopen(9);hist_exist=YES;
  }
  ram=RamBon;
  ram_size=125000;
#ifdef DOUBLE_FACT
  ram_size*=DOUBLE_FACT;
#endif
  if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;zeroL(ram,ram_size);
	stu58_len=fldlen(58,0);max_line=ram_size/stu58_len;

  akpr_len=0;for(k=12;k<=20;k++) akpr_len+=fldlen(6,k);
  sysget( 294,4,def_munt);

  last_vfa=LAST_VFA;
  sysget(last_vfa,2,&last_vf);

  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);
	if(firma[256]){ // IBAN bij voorkeur gebruiken voor rekeningnummer
		copy(&firm[8].begpos,&firm[3].begpos,sizeof firm[0]); 
		firm[8].begpos+=41; // om IBAN te misleiden
	}
  sysget(1787,1,&sys1787);
  sysget(1918,2,&sear_stt);
  sysget(1920,61,std_txt[0]);
  sysget(1981,61,std_txt[1]);
  sysget(2042,61,std_txt[2]);
  sysget(2103,61,std_txt[3]);
  sysget(2172,2,&btw_kol);
  sysget(1048,32,&btw_pct[0]);
  for(k=8;k<BTWDIM;k++) {btw_pct[k]=0;}
  sysget(2208,2,&skip_off);
  sysget(2222,2,&def_qfact);
  sysget(1080,4,&max_btw);
  sysget(2228,2,&b2228);
  sysget(2854,2,&DefaultFiliaal);
  sysget(3588,2,&sys3588);
  sysget(1084,4,&def_btw);
  sysget(3598,6,b3598);
  sysget(3604,2,&b3604);
  sysget(3606,2,&b3606);
  sysget(3624,2,&sys3624);
  sysget(3720,2,&sys3720);
  sysget(3876,2,&sys3876);
  sysget(3974,2,&ft_off);
#if SEARBFLEN
  sysget( 298,2,&vers_298);
#endif
  sysget(2212,4,talen);
  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(2770,60,(char *)&nm_loc[0][0]);
  sysget(4294,40,(char *)&loc_klt[0]);

	sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4254,40,(char *)&dt_kvk[0]);
  sysget(4408,2,&sys4408);

  sysget(4608,2,&sys4608);

 if(ft_off && fldlen(91,11+(ft_off*5))==0) ft_off=0;
	j=0;
  for(max_kassa=0;max_kassa<10;max_kassa++){
    if(fldlen(91,11+(max_kassa*5))==0) break;
    if(fldlen(91,11+((max_kassa+ft_off)*5))==0) break;
		if(nm_kassa[max_kassa][0]) j++;
  }
	if(ft_off && max_kassa>ft_off) max_kassa=ft_off; // veiligheid voor ft_offset
	if(j<=1) max_kassa=1; // meer velden, maar geen naam ingevuld
#if BOEKALLO
  sysget(784,4,&kltcent);
  find_grb(kltcent);
  sysget(3636,4,&grb_notf); find_grb(grb_notf);
  for(k=0;k<DF_GRB;k++){
    sysget(788+k*4,4,&df_rek[k][0]);
    if(df_rek[k][0]!=0xFF && df_rek[k][0]!=0x00){
      df_recnr[k]=find_grb(*(long *)&df_rek[k][0]);
    }
  }
  if(notfound){
    errnum=notfound;
    scrupd(-1,0x80);
    ovlexit(-1);
  }
//  if(df_recnr[12]==0) {errnum=82;ovlexit(-1);}
//  if(df_recnr[14]==0) {errnum=40;ovlexit(-1);}
  journl=BOEK_JOURNL;
  for(k=0;k<80;k++){
    sysget(10240+k*80,2,&last_vf);
    if(last_vf==journl)break;
  }
  if(k==80){errnum=4;ovlexit(-1);}
  last_fta=10260+k*80;
  sysget(last_vfa,2,&last_ft);
  fasinit(4);
  fasinfo(4,2);
  if(*l(4,1)<MINFREE) {errnum=64;ovl_exit(-1);}
#endif
	SysPosNrCheck=3778;// blokkage mutatiebons of bestelbons klanten
  fieldspc(58,20,&pdum_,fmt);
  k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;
  copy(def_munt,ft_munt,3);
  copy(fmeobd,fm_obd,sizeof fmeobd);
  copy(fmeobdk,fm_obdk,sizeof fmeobdk);
  copy(fmeobdk1,fm_obdk1,sizeof fmeobdk1);
  copy(fmeobdk2,fm_obdk2,sizeof fmeobdk2);
  ft_afrond=0.01;
  ps_8_23=s(8,23); len8_23=fldlen(8,23);
  len58_35=fldlen(58,35); pd_58_35=d(58,35);

	pl_80_1=l(80,1); p_data=s(80,1)+4;
  ps_1_3=s(1,3);
	pu_58_14=u(58,14);pu_58_1=u(58,1);pu_6_1=u(6,1);
  pu_8_28=u(8,28);
  len58_15=fldlen(58,15);
  ps_58_15=s(58,15);
  ps_58_16=s(58,16);
  ps_58_62=s(58,62); len58_62=fldlen(58,62);
  pf_58_20=f(58,20);pf_58_50=f(58,50);
  pf_58_21=f(58,21);
  pf_58_24=f(58,24);
  ps_58_25=s(58,25);len58_25=fldlen(58,25);
  pf_58_31=f(58,31);
  hash_len=fldlen(58,14)+len58_15+fldlen(58,16);
}


#if BOEKALLO
static boekbkh()
{
  int16 g,j,k;
  long rekenc;
  double bd_;
  char str_[10],reken[11];

  ft_date=*u(25,2);
  zero(str_,sizeof str_);grb_deco(str_,&grb_notf);
  str_[0]='6'; str_[2]='0'+filiaal;grb_comp(str_,&grb_notf);
  if(sear_grb(grb_notf) ==60000){
    sysget(3636,4,&grb_notf);
  }
  zero((char *)&bedrag[0],sizeof bedrag);
  zero((char *)&grb_tb[0],sizeof grb_tb);
  zero((char *)&opmhoev[0],sizeof opmhoev);
  j=1;

  if(!is_nul((double)tot_leeg)){
#if FLAGKEE // 418000FF
  	zero(reken,sizeof reken);rekenc=0; 
  	if(filiaal>=1 && filiaal<10) sprintf_s(reken,10,"418000%02d", filiaal);
	  else copy("41800099",reken,8);
    grb_comp(reken,&rekenc);
		grb_tb[j]=rekenc;
		if( (rec_nr[j]=sear_grb(rekenc)) ==60000){
			errnum=0;
			rec_nr[j]=df_recnr[12];grb_tb[j]=*(long *)&df_rek[12][0];
		}
    bedrag[j]=tot_leeg;
    j++;
 	  zero(reken,sizeof reken);rekenc=0; 
  	if(*u(8,38)>=1 && *u(8,38)<10) sprintf_s(reken,10,"418000%02d", *u(8,38));
	  else copy("41800099",reken,8);
    grb_comp(reken,&rekenc);
		grb_tb[j]=rekenc;
		if( (rec_nr[j]=sear_grb(rekenc)) ==60000){
			errnum=0;
			rec_nr[j]=df_recnr[12];grb_tb[j]=*(long *)&df_rek[12][0];
		}
    bedrag[j]=-tot_leeg;
    j++;
#else
    bedrag[j]=tot_leeg;
    rec_nr[j]=df_recnr[12];grb_tb[j]=*(long *)&df_rek[12][0];
    j++;
    bedrag[j]=-tot_leeg;
    rec_nr[j]=df_recnr[12];grb_tb[j]=*(long *)&df_rek[12][0];
    j++;
#endif
  }
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*pd_58_35){
			fasinit(6); *u(6,1)=*u(58,14); if(*u(6,1)) fasgeti(6);
      rekenc=makegrb(filiaal); // to boeking 
      if(sear_grb(rekenc)==60000){errnum=0;rekenc=grb_notf;}
      for(g=1;g<EL_BKH;g++){
				if(rekenc==grb_tb[g])	break;
      }
      if(g==EL_BKH){
				for(g=1;g<EL_BKH;g++){
					if(is_nul((double)bedrag[g])){
						grb_tb[g]=rekenc;
						if( (rec_nr[g]=sear_grb(rekenc)) ==60000){
							errnum=0;
							rec_nr[g]=sear_grb(grb_notf);
							grb_tb[g]=grb_notf;
						}
						break;
					}
				}
      }
      bedrag[g]+=*pd_58_35;opmhoev[g]+=*pf_58_31;

      rekenc=makegrb(*u(8,38)); // from boeking
      if(sear_grb(rekenc)==60000){errnum=0;rekenc=grb_notf;}
      for(g=1;g<EL_BKH;g++){
				if(rekenc==grb_tb[g])	break;
      }
      if(g==EL_BKH){
				for(g=1;g<EL_BKH;g++){
					if(is_nul((double)bedrag[g])){
						grb_tb[g]=rekenc;
						if( (rec_nr[g]=sear_grb(rekenc)) ==60000){
							errnum=0;
							rec_nr[g]=sear_grb(grb_notf);
							grb_tb[g]=grb_notf;
						}
						break;
					}
				}
      }
      bedrag[g]-=*pd_58_35;opmhoev[g]-=*pf_58_31;


    }
  }
	// uit veiligheid
  for(k=1;k<EL_BKH;k++) bedrag[0]-=bedrag[k];
	rec_nr[0]=sear_grb(grb_notf);		grb_tb[0]=grb_notf;

//  rec_nr[0]=df_recnr[14];grb_tb[0]=*(long *)&df_rek[14][0];
/* rec_nr[0]=*u(2,1)+30000; */
  boek();
}

static boek()
{
  int16 g,ref_yy,dum1,dum2;
  double bd_eur,tot_eur=0,ebd_;
	char opmerk_[25];
 

	zero(opmerk_,sizeof opmerk_);
	if(*u(8,38)>=1 && *u(8,38)<=10) sprintf_s(opmerk_,25,"Mutatie %d naar %d",*u(8,38),filiaal);
	else sprintf_s(opmerk_,25,"Mutatie depot naar %d",filiaal);

  copy(def_munt,ft_munt,3);
  for(g=0;g<EL_BKH;g++){
    if(!is_nul((double)bedrag[g])){
      initrec(4);
      bd_eur=valu_cnv(ft_munt,"EUR",(double)bedrag[g],(double)0.01);
      tot_eur+=bd_eur;
      *l(4,7)=bd_eur; *d(4,32)=bd_eur;
      *u(4,5)=rec_nr[g];
      *s(4,31)='E';
			copy(opmerk_,s(4,28),20);
      if(rec_nr[g]<60000){ /// komt eigenlijk niet voor
				*l(4,6)=grb_tb[g];
				jddate(*u(4,4),&ref_yy,&dum1,&dum2);
				*s(4,8)=ref_yy%100; if(*s(4,8)<50) *s(4,8)+=100;           /* y2000 */
				*s(4,9)=journl;
				*u(4,10)=*u(4,3);
				ebd_=valu_cnv(ft_munt,"EUR",(double)btw_tot,(double)0.01);
				copy((char*)&ebd_,s(4,38)+40,8);
				*u(4,20)=ft_date;
				*u(4,21)=verv_dt;
				copy(def_munt,s(4,24),3);
      }
      else{
				*l(4,6)=grb_tb[g];
      }
      errnum=fasadd(4);
    }
  }
}
 
static long makegrb(filiaal_)
int16 filiaal_;
{
  int16 g,gg,kk;
  long rekenc;
  char reken[11];
 
// De eerste 3 cijfers van de AK-rekening nemen (604), dan filiaal# (0=depot, 1-9=filiaal) en dan de rest nemen van AK-rekening

	zero(reken,sizeof reken);rekenc=0; 
#if FLAGKEE // 604000FF
	if(filiaal_>=1 && filiaal_<10) sprintf_s(reken,10,"604000%02d", filiaal_);
	else copy("60400099",reken,8);
#else
	if(fldlen(6,52) && *l(6,52)) rekenc=*l(6,52);
	if(rekenc) grb_deco(reken,&rekenc); else copy("604000",reken,6);
	if(filiaal_>=1 && filiaal_<10) reken[3]='0'+filiaal_;
#endif
  grb_comp(reken,&rekenc);

//  if(fldlen(58,26) && *l(58,26)) rekenc=*l(58,26);
//  else{
//    zero(reken,sizeof reken);
//    copy(b3598,reken,6);
//    for(g=0;g<10;g++) if(reken[g]=='\0') break;
//    if(g>0){reken[0]='6';reken[g-1]=reken[g-1]+filiaal;}
//#if 0
//    if(fldlen(2,25)){
//      copy(s(2,25),&reken[g],fldlen(2,25));
//      for(g=0;g<10;g++) if(reken[g]=='\0') break;
//    }
//#endif
//    if(len58_25){
//      copy(ps_58_25,&reken[g],len58_25);
//      for(g=0;g<10;g++) if(reken[g]=='\0') break;
//    }
//    if(b3604){
//      stcli_d(&reken[g],(long)*i(58,34),b3604,0);
//      g+=b3604;
//    }
//    if(b3606){
//      kk=*pf_58_24;gg=*pf_58_24*10 - kk*10;/* gg = decimaal */
//      stcli_d(&reken[g],(long)kk,2,0);
//      if(gg && b3606==2) stcli_d(&reken[g]+2,(long)gg,1,0);/* decimaal */
//    }
//    grb_comp(reken,&rekenc);
//  }
  return (long)rekenc;
}

static initrec(stu_)
int16 stu_;
{
  fasinit(stu_);
  *s(stu_,2)=journl;
  *u(stu_,3)=ft_nr;
  *u(stu_,4)=ft_date;
}

#if 0
ftchk()
{
  int16 curs_=0;

#if BOEKALLO
  if(last_arc){
    if(ft_date<=last_arc) {errnum=37;goto endsr;}
    if((sys1862 & 8)==0) if(ft_date>last_arc+600) {errnum=61;goto endsr;}
  }
  if(yet_booked(journl,ft_nr,ft_date)){errnum=59;curs_=1;goto endsr;}
#endif
  endsr:;
  return curs_;
}

static flag yet_booked(jrnl_,volgnr_,dt_)
int16 jrnl_;
uint16 volgnr_,dt_;
{
  int16 fkey_,jj,mm,dum;
  uint16 dt_beg,dt_end;
							
  if(sys1862 & 0x10) return NO;
  jddate(dt_,&jj,&mm,&dum);
  FOREVER{
    dt_end=datejd(++jj,mnd_strt,1);
    dt_beg=datejd(--jj,mnd_strt,1);
    if(dt_>=dt_beg) break;
    jj--;
  }
  fasinit(4);*s(4,2)=jrnl_;*u(4,3)=volgnr_;fkey_=1;
  FOREVER{
    if(faskeyi(4,1,fkey_)) break;fkey_=2;
    if(*s(4,2)!=jrnl_ || *u(4,3)!=volgnr_) break;
    if(*u(4,4)>=dt_beg && *u(4,4)<dt_end) return YES;
  }
  return NO;
}
#endif
static uint16 find_grb(rek_)
long rek_;
{
  uint16 fuval;
  fuval=sear_grb(rek_);
  if(errnum){
	scrget(1,170);
    if(notfound==0){
      scrget(1,170);zz=1;
      scrifld(zz++,fm_os60,"Niet gevonden rekeningen");
    }
    scrifld(zz++,fm_ogrb,&rek_);
    notfound=errnum;errnum=0;
  }
  return fuval;
}
		
static uint16 sear_grb(rek_)
long rek_;
{
  fasinit(3);*l(3,2)=rek_;
  search(3,2);
  return (uint16)(*u(3,1)+60000);
}
#endif

static fileopen(nr_)
int16 nr_;
{
  int16 stu_;
  char filename[15];

  nr_--;
  sysget(300+17*nr_,15,filename);
  sysget(315+17*nr_,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(errnum=fasopen(filename,0)) exit_hfdmenu();
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
    if(stu_==6) art_exist=YES;
  }
}

static ovl_exit(nr_)
int16 nr_;
{
/*  sysput(last_vfa,2,&last_vf); */
	ClearSysPosNrCheck();
  sysflush();
  fasflush(0);
  prtclose();
#if FLAGCRA
	if(*u(25,4)==110) exit_hfdmenu();
#endif
  if(ovltest(249) && nr_==218) ovlexit(218);
  exit_hfdmenu();
}
						
static exit_hfdmenu()
{
  ovlexit(*u(25,4));
}

static ram2stu(lin_)
int16 lin_;
{
  copy(ram+(lin_*stu58_len),s(58,1),stu58_len);
}
						
static stu2ram(lin_)
int16 lin_;
{
  copy(s(58,1),ram+(lin_*stu58_len),stu58_len);
}

static fld_test(nr_,stu_,elet_)
int16 nr_,stu_,elet_;
{
  if(fldlen(stu_,elet_)) scrfld(nr_,stu_,elet_);
  else streepje(nr_);
}

static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
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

static test_line()
{
  if(*s(58,15) || *ps_58_16 || *pf_58_20) return YES;
  return NO;
}

static btw_tab(bd_)
BEDRAG bd_;
{
  int16 k;
  float btw_;

  btw_=*pf_58_24;
  for(k=0;k<BTWDIM-BTWDIV;k++){
    if(btw_==btw_pct[k]) break;
  }
  return k;
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}
							
static BEDRAG round(value_)
double value_;
{
  double bd_;
							
  bd_=valu_cnv(def_munt,def_munt,value_,ft_afrond);
  return (BEDRAG)(bd_);
}

static stu_add(stu_,elet_,pf1)
int16 stu_,elet_;
float *pf1;
{
  if(fldlen(stu_,elet_)){
    *f(stu_,elet_)+=*pf1;
  }
}

static skip_lin(line_)
int16 line_;
{
  while(free>(line_+skip_off)) nextline();
}

static nextline()
{
  free=prtline();
}

static bon_lst()
{
  int16 j,z,mode_;


  getsysprNew(5,form_dat,&prmode,&prtnr); PrintPaperNr=0; //altijd pdf if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,prmode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1);prttext("<t40b>");prttext("Mutatie-bons");prttext("<b>");
  prttext("<t60>");prtfld(25,2,-1);
  prttext("<t72>Blz.<ppp>.");
  prtbuf(1);z=1;
  prtitab(z,fm_os6,van_fil,4,-1); prttitle(z++,"Van Fil.",3);
	prtitab(z,fm_os6,nm_fil,4,-1); prttitle(z++,"Naar Fil.",3);
  prttab(z,8,8,1,-1); prttitle(z++,"Bst.dt.",0x13);
  prttab(z,8,2,6,-1); prttitle(z++,"Bonnr",0x13);
  prttab(z,58,15,2,-1); prttitle(z++,"Artnr",3);
  prttab(z,58,16,2,30); prttitle(z++,"Omschrijving",3);
  prttab(z,58,31,2,-1); prttitle(z++,"Aantal",0x13);
	prttab(z,58,62,1,-1); prttitle(z++,"",3);

  prtbuf(3);
  p_pdfname("Lijst mutatie-bons",0,0);
  free=999;
  fasinit(8);
  while(free>=0){
    next:;
    if(faskeyi(8,1,2)) break;
    if(*i(8,36)!=THISTYP) goto next;
		if(*u(8,3)>=1 && *u(8,3)<=10) copy(nm_loc[*u(8,3)-1],nm_fil,6);
		else copy("DEPOT",nm_fil,6);
		if(*u(8,38)>=1 && *u(8,38)<=10) copy(nm_loc[*u(8,38)-1],van_fil,6);
		else copy("DEPOT",van_fil,6);
    for(j=1;j<=4;j++) prtinfo(j,0);
    fasinit(58);*u(58,2)=*u(8,1);mode_=1;
    while(free>=0){
      if(faskeyi(58,1,mode_)) break; mode_=2;
      if(*u(58,2)!=*u(8,1)) break;
      for(j;j<15;j++) prtinfo(j,0);nextline();j=4;
    }
    nextline();
    if(free<0) break;
  }
  prtclose();
  endsr:;
}

static exec()
{
  int16 k,key,fuval=NO;

  if(dsp_hoofding()) goto endsr;
  redo:
  if(dsp_detail()==NO) goto endsr;
  calc(0,NO);
  if((k=dsp_tot())==NO) goto endsr;
  if(k>1)goto redo;
  load_sysnr(NO);
  if(chk_nr){
    if(upd_mode==NO){
      *u(8,2)=last_vf+1;
    }
	}
#if BOEKALLO
  sysget(last_fta,2,&last_ft); ft_nr=last_ft+1;
#endif
#if BONSORT
  sort_bon(0);
#endif
  if(prt_levbon=='J') ft_prt();
	if(prt2pdf==2) {MailDocument(0);prt2pdf=0;}
  if(stuk_per_stuk && prt_levbon=='J'){
    FOREVER{
      scrget(2,28);key=scrupd(0xFFFF,0x58);
      if(key==105) break;
      if(key==104) ft_prt();
      if(key==107) goto redo;
    }
  }
  scrget(1,7);scrupd(-3,0);
  if(free!=-1){
    fasflush(0);
  }
	if(ovltest(2241)){
		for(k=0;k<2;k++) if(BestelFileUsed[k][0]  && *(uint16 *)(&BestelFileUsed[k][100])==2241) fasopen(BestelFileUsed[k],99); // deleten 
		zero(BestelFileUsed,sizeof BestelFileUsed); // om later te deleten
	}
  fuval=YES;
  endsr:;
  return fuval;
}

static dsp_hoofding()
{
  int16 curs,curspos_,k,key,z;

	if(ovltest(2241))	zero(BestelFileUsed,sizeof BestelFileUsed); // om later te deleten
  curs=1;
  FOREVER{
    redo:
    scrget(2,SCRNUM);
    if(upd_mode && (fldlen(8,70) || fldlen(8,71) || fldlen(8,72))) scraddpicto(5,0,78,0,2,1,64,0,0x007FFF,"Info"); 
		if(ovltest(2241) && upd_mode==NO) scraddpicto(3,0,74,19,6,3,77,0,4,"Laad XLS-bestelling");
    z=1;
    scrfld(z++,25,1);
    scrifld(-z,fm_uu2,&filiaal); z++; scrifld(z++,fm_os6,nm_fil);
    scrfld(z++,8,2);
    scrfld(z++,8,8);
    scrifld(z++,fm_u_JN,&prt_levbon);
    for(k=0;k<2;k++) scrfld(z++,8,19+k);
#if BOEKALLO
		if(boek_mode){
			scraddf(50,16,2,0);  scrifld(50,VarTextFmt(27,0),"Boeken in boekhouding J/N : ");
			scraddf(51,16,30,2); scrifld(51,fm_u_JN,&boek_JN);
		}
#endif
    key=scrupd(curs,0x4E1);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101 || key==106) return YES;
    if(key==111) ovl_exit(0);
		if(key==5005){DisplayBonInfo(); curs=curspos_;goto redo;}
		if(key==5003){
			if(ovlcall(2241,0)) keepdata=YES;
			else {errnum=14; goto redo;}
		}
    if(filiaal<=0 || (filiaal>10 && filiaal!=99)) {zero(nm_fil,sizeof nm_fil);curs=2;errnum=38;goto redo;}
		if(filiaal<=10){
      copy(nm_loc[filiaal-1],nm_fil,6);
      if(fldlen(66,11+(filiaal-1)*15)==0) {curs=2;errnum=39;goto redo;}
		} else copy("DEPOT",nm_fil,6);
    if(nm_fil[0]=='\0') {curs=2;errnum=39;goto redo;}
    if(key==18){
      curs=fldcurs+1;goto redo;
    }
    if(key==108) break;
  }
  if(keepdata==NO) init58(0,NO);
  return NO;
}



static dsp_detail()
{
  int16 curs=1,j,key,k,start_=0,k_k,pos_15,err_pos=0,nstart_,curspos_;
  uint16 rec_,sr_nm,len_;
	int qbak_,qstk_;
  char *pdum,dumm_[10],*pvar,qlv_str_[25];
  pdum=&dumm_[0];
 
  q_per_line=1;
  for(k=0;k<sizeof det_nr/2;k++){
    if(det_nr[k]==15) pos_15=q_per_line;
    if(fldlen(58,det_nr[k])>0) q_per_line++;
  }

  curs=7;
  if(*u(8,38)<=0 || *u(8,38)>10) {zero(van_fil,sizeof van_fil);}
  else copy(nm_loc[*u(8,38)-1],van_fil,6);
	if(filiaal==99) curs=4;
#if FLAGCRA
		if(*u(8,38)==0){curs=4;}
#endif
  FOREVER{
    redo:
    scrnum=0;scrget(2,237); scraddpicto(1,0,76,22,4,2,127,0,4,"Voeg artikels toe");
    zz=1;
    scrifld(zz++,fm_ou2,&filiaal); scrifld(zz++,fm_os6,nm_fil);
    scrifld(zz++,fm_obd,&belastbt);
    scrifld(-zz,fm_uu2,u(8,38));zz++; scrifld(zz++,fm_os6,van_fil);
    scrifld(zz++,fm_obd,&tot_leeg);
    scrfld(zz++,8,25);
    scrifld(zz++,fm_obd,&alg_tot);
    z_base=zz;auto_enter=NO;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      j++; scrifld(zz++,fm_ou4,&j); j--;
      ram2stu(j);
      for(k=0;k<sizeof det_nr/2;k++){
				k_k=det_nr[k];
				if(fieldspc(58,k_k,&pdum,fmt)>0){
					pvar=ram+(j*stu58_len)+(s(58,k_k)-s(58,1));
					if(sys4608 & 1){
						auto_enter=YES;
						if((k_k!=15 && k_k!=16)||(*pvar!='\0' && zz!=err_pos)) auto_enter=NO;
						if(auto_enter){
							if(k_k==15){
								if(*(ram+(j*stu58_len)+(s(58,16)-s(58,1)))!='\0') auto_enter=NO;
							}
							else{
								if(*(ram+(j*stu58_len)+(s(58,15)-s(58,1)))!='\0') auto_enter=NO;
							}
						}
					}
					if(k_k==100){
						stock2string(*f(58,100),*f(58,63),qlv_str_,15);
						scrifld(zz++,fm_os10,qlv_str_);
					}
					else{
						if(k_k==16 && fmt[2]>30) fmt[2]=30;
  					if(auto_enter){scrifld(-zz,fmt,pvar);zz++;}
	  				else scrifld(zz++,fmt,pvar);
					}
					if(k_k==16) scraddpicto(10+j-start_,zz-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
				}
      }
    }
    redo_upd:;
    key=scrupd(curs,0x0FE);curs=1;curspos_=fldcurs;
    auto_enter=NO;nstart_=start_;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    auto_enter=NO;nstart_=start_;

    if(key==106){
			for(k=0;k<max_line;k++){ram2stu(k);if(*s(58,16)) break;}
			if(k<max_line){
        if(scr_ok("Wenst U echt deze bon te annuleren ?")) return NO;
			} else return NO;
   }
#if FLAGCRA
		if(*u(8,38)==0){errnum=38; goto redo;}
#endif
	 if(*u(8,38)==0 || *u(8,38)==99){copy("DEPOT",van_fil,6);}
   else if(*u(8,38)<1 || *u(8,38)>10){*u(8,38)=0;zero(van_fil,sizeof van_fil);}
   else{
      if(fldlen(66,11+(*u(8,38)-1)*15)==0) {errnum=39;goto redo;}
      if(*u(8,38)==filiaal){errnum=34;goto redo;}
      copy(nm_loc[*u(8,38)-1],van_fil,6);
      if(van_fil[0]=='\0') {errnum=39;goto redo;}
    }
		if(filiaal==99 && (*u(8,38)==0 || *u(8,38)==99)){errnum=38;goto redo;}
		if(cmp_str(van_fil,nm_fil,6)==0){errnum=34;goto redo;}
    if(key==5001){DisplayExtraFuncties();key=107;} // extra opties
		if(key>=5010 && key<5010+D_LIN_SCR){
			k=key-5010+start_;
			ram2stu(k);fasinit(6);
			if(len58_15 && *ps_58_15) {*s(6,3)='.';copy(ps_58_15,s(6,3)+1,len58_15);}
			else {copy(ps_58_16,s(6,3),fldlen(6,3));sr_nm=YES;}
			if(search(6,98)){
				curs=cursget(k-start_,15); if(*ps_58_15=='\0') curs++;
				err_pos=curs;errnum=39;goto redo;
			}
			else {
				copy(s(6,2),s(58,15),fldlen(58,15));
				copy(s(6,3),s(58,16),fldlen(58,16));
				stu2ram(k);
			}
		}
 

    if(key==18){
      if(curspos_<z_base){curs=curspos_+1;goto redo;}
      auto_enter=YES;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      k=(curspos_-z_base)%q_per_line;
      if(k==pos_15) k_k=15; else k_k=16;
      ram2stu(j);
      if(*s(58,k_k)=='\0' || *s(58,k_k)=='*'){curs=curspos_+1;goto redo_upd;}
    }
    if(key==104){
      j=(curspos_-z_base)/q_per_line;j+=start_;
      ram2stu(j);
      rec_=*u(58,1);
      init58(j,YES);
      ram2stu(j);
      *u(58,1)=rec_;
      stu2ram(j);
			curs=curspos_;goto redo;
    }
    if(key==105){
      j=(curspos_-z_base)/q_per_line;j+=start_;
      ins_lin(j);
    }

    for(k=start_;k<(start_+D_LIN_SCR);k++){
      ram2stu(k);k_k=k-start_;
      if((*s(58,15) || *ps_58_16) && *ps_58_16!='*' && *u(58,17)!=hash()){
				fasinit(6);
				sr_nm=NO;
				if(len58_15 && *s(58,15)) {*s(6,3)='.';copy(s(58,15),s(6,3)+1,len58_15);}
				else {copy(ps_58_16,s(6,3),fldlen(58,16));sr_nm=YES;}
				if(search(6,0)){
					curs=cursget(k_k,15); if(*ps_58_15=='\0') curs++;
					err_pos=curs;errnum=39;goto redo;
				}
				copy(s(6,2),s(58,15),len58_15);
				*u(58,14)=*u(6,1);
				if(sr_nm || *ps_58_16=='\0'){
					copy(s(6,3),ps_58_16,fldlen(58,16));
				}
				Fill1Line();
				*u(58,17)=hash();
      }
      else if(*s(58,15)=='\0' && *ps_58_16=='\0'){
				zero(s(58,2),fldlen(58,0)-2);
      }
      stu2ram(k);
    }
    calc(0,NO);
    if(key==108)break;

    start_=nstart_;
    if(key==18 || auto_enter){ /* automatische bladskip op einde van scherm */
      for(k=0;k<D_LIN_SCR;k++){ram2stu(k+start_);if(test_line()==NO) break;}
      if(k==D_LIN_SCR) key=103;
    }
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){ram2stu(k+start_);if(test_line()==NO) {j=k;break;}}
    curs=cursget(j,0);
  }
  return YES;
}

static Fill1Line()
{
	uint16 rec_;
	char leeggcod[6];

	*pf_58_24=*f(6,28);
	*i(58,34)=*i(6,9); *f(58,20)=*f(6,18);
	if(fldlen(58,63)){*f(58,63)=*f(6,31);if(*f(58,63)==0) *f(58,63)=1;}
	if(fldlen(58,8) && fldlen(6,83)) {*f(58,8)=*f(6,83); if(*f(58,8)==0) *f(58,8)=1;}
	if(fldlen(58,62)){
		if(*ps_58_62=='S') *f(58,20)/=*f(58,63);
	}
	if(len58_25 && fldlen(6,39)) copy(s(6,39),ps_58_25,len58_25);
/*  if(fldlen(6,40) && fldlen(58,26)) *l(58,26)=*l(6,40); */
	copy(s(6,41),leeggcod,fldlen(6,41));
	if(fldlen(58,62)){
		if(*ps_58_62=='S') copy(s(6,44),leeggcod,fldlen(6,44));
	}
	*f(58,49)=*f(6,42);
	if(fldlen(58,101) && fldlen(6,29)) copy(s(6,29),s(58,101),fldlen(58,101));
	fasinit(66);*u(66,2)=*u(6,1);faskeyi(66,1,0);
	if(fldlen(58,100)) fill_astock();
	//if(filiaal<=10) *f(58,100)=*f(66,11+(filiaal-1)*15);
	//else *f(58,100)=*f(6,33);
	rec_=*u(6,1);fasinit(6);copy(leeggcod,s(6,2),fldlen(6,41));
	if(leeggcod[0]){
		if(search(6,2)==0){
			*u(58,48)=*u(6,1);
			*f(58,46)=*f(6,21);
		}
	}
	*u(6,1)=rec_;fasgeti(6);
	*f(58,38)=*f(6,30);
	if(*i(6,9)==99){
		*u(58,48)=*u(58,14);
		*f(58,46)=*f(58,20);
		*f(58,49)=1;
	}

}

static fill_astock()/* fill actuele stock in */
{
  int16 k,mode_=1,muteer_=NO,fnr_;
  uint16 rec58_,arec_,rec8_;
  float stock_,qlv_,factor_=1.;
 
  if(test_line()==NO || *ps_58_16=='*'){stock_=0;goto endsr;}
 
  copy(s(58,1),sortbuf,fldlen(58,0)); 
  copy(s(8,1),buf1000,fldlen(8,0));rec8_=*u(8,1);
	fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6); arec_=*u(6,1); factor_=*f(6,31);if(factor_==0) factor_=1.;
	if(fldlen(6,102) && *u(6,102)){ // stock van moederfiche nemen
		*u(6,1)=*u(6,102); 
		if(fasgeti(6)==0) {
			arec_=*u(6,1); if(*f(6,31)) factor_= *f(6,31)/factor_;
		}
		else {fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6); arec_=*u(6,1);factor_=1;}
	} else factor_=1.;
#if YES // STOCK_OP_LOCATIE
//#if FLAGAST
//	if(DefaultFiliaal==0 || DefaultFiliaal==99){
//		for(k=0;k<10;k++) if(orig_klt==loc_klt[k]) break;
//		if(k<10 && loc_nr[k]) muteer_=YES;
//	}
//#endif
  if(muteer_==NO && fldlen(8,48) && filiaal>0 && filiaal<=10){
		fasinit(66);*u(66,2)=arec_;faskeyi(66,1,0);
    stock_=*f(66,11+(filiaal-1)*15)*factor_;goto calc_bonstock;
  }
#endif    
  stock_=*f(6,33)*factor_; 
#if FLAGCHA // controle doen op minimumstock
  stock_-=*f(6,36);
#endif
	calc_bonstock:;
	rec58_=*pu_58_1;
#if !STOCK244
  fasinit(58);*u(58,14)=*u(6,1);mode_=1;
  FOREVER{
    next:;
    if(faskeyi(58,2,mode_)) break; mode_=2;
    if(*u(58,14)!=*u(6,1)) break;
    if(*pu_58_1==rec58_) goto next;
    fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
		if(*u(8,1)==rec8_) goto next; // bij aanpassen eigen bon overslaan
#if FLAGGRS // geen rekening houden met bestelde goederen
		if(*u(8,36) && *u(8,36)==10) goto next;
#endif
#if BACKORDER
    if(*u(8,36) && *u(8,36)!=10 && *u(8,36)!=20) goto next;
#endif
		fnr_=3;
#if YES // STOCK_OP_LOCATIE
		if(*u(8,36)==20){ // stockmutatie
  		if(filiaal>0 && filiaal<=10){
				if(*u(8,3)==filiaal) fnr_=3;
				else if(*u(8,38)==filiaal) fnr_=38;
				else goto next; // geen van filiaal of naar filiaal
			}
			else{
				if(*u(8,3)<1 && *u(8,3)>10) fnr_=3;
				else if(*u(8,38)<1 && *u(8,38)>10) fnr_=38;
				else goto next; // geen van filiaal of naar filiaal
			}
		}
		else {
 		  if(filiaal>0 && filiaal<=10){
				if(*u(8,48)!=filiaal)  goto next; // geen van filiaal of naar filiaal
			}
			else{
				if(*u(8,48)>0 && *u(8,48)<=10) goto next;
			}
		}
#endif
    qlv_=*pf_58_31;
    if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) qlv_/=*f(58,63);
		if(fldlen(8,36)){
			if(*u(8,36)==20){ // mutatiebon
				if(fnr_==3) stock_+=qlv_*factor_; // mutatie naar dit filiaal
				else stock_-=qlv_*factor_; // mutatie van dit filiaal naar ander filiaal
			}
			else if(*u(8,36)==10) stock_+=qlv_*factor_; // bestelbons leveranciers bijtellen
			else stock_-=qlv_*factor_; // leveringsbons
		}
    else stock_-=qlv_*factor_;
  }
  copy(sortbuf,s(58,1),fldlen(58,0));
  copy(buf1000,s(8,1),fldlen(8,0));
#endif
  endsr:;
  if(fldlen(58,100)) *f(58,100)=stock_;
}


static DisplayBonInfo()
{
  int16 z=1,key;
	char cpostnm_[20],upostnm_[20];

	zero(cpostnm_,sizeof cpostnm_);	zero(upostnm_,sizeof upostnm_);
	if(fldlen(8,70) && *u(8,70)) GetPostName(cpostnm_,*u(8,70));
	if(fldlen(8,71) && *u(8,71)) GetPostName(upostnm_,*u(8,71));

  FOREVER{
redo:;
		scraddf(-1,0,0,0);z=1;
	  DisplayMenuTitel(4,"Update-informatie bon",0xA);
    scraddf(z++,10,4,0); scraddf(z++,10,20,2);
		scraddf(z++,12,4,0); scraddf(z++,12,26,2);
		scraddf(z++,14,4,0); scraddf(z++,14,28,2);
    scraddf(z++,23,1,8);
    z=1;
		scrifld(z++,VarTextFmt(18,0),"Aangemaakt door "); scrifld(z++,VarTextFmt(15,0),cpostnm_);
		scrifld(z++,VarTextFmt(24,0),"Laatst aangepast door "); scrifld(z++,VarTextFmt(15,0),upostnm_);
		scrifld(z++,VarTextFmt(26,0),"Datum laatste wijziging ");scrofld(z++,8,72,-1);
    scrifld(z++,VarTextFmt(10,0)," F1 terug ");
    key=scrupd(-1,0x01);
		if(key==101) break;
  }
}

static stock2string(stock_,qperbak_,outstr_,max_len_)
float stock_,qperbak_;
char *outstr_;
int16 max_len_;
{
  long qstk_,qbak_;
	float add_;
						
  zero(outstr_,max_len_);
	if(stock_){
		if(qperbak_<1) qperbak_=1;
		qbak_=(long)(stock_); qstk_=0;
		add_=0.49; if(stock_<0) add_=-0.49;
		if(qperbak_>1 && stock_!=0){
			qstk_=(long)(((stock_- qbak_) * qperbak_)+add_);
		} else qstk_=0;
		if(qstk_) sprintf_s(outstr_,max_len_,"%5d/%2d",qbak_,qstk_);
		else sprintf_s(outstr_,max_len_,"%5d",qbak_);
  }
}


static DisplayExtraFuncties()
{
	int z,k,key,used_=0,vt_,hz_;
	char dsp_lijn[80];

	FOREVER{
redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,4,5,0);
		scraddf(z++,10,5,0);
		scraddf(z++,23,1,8); // scraddf(z++,23,11,8);  // functietoetsen 
    z=1;
    DisplayMenuTitel(1,"Extra funties bij ingave bon",0xA);z=1;
		scrifld(z++,VarTextFmt(25,0),"Sorteer artikels volgens:");
		scrifld(z++,VarTextFmt(25,0),"Voeg artikels toe via:");
	  scrifld(z++,VarTextFmt(9,0)," F1 stop");
		/* scrget(2,353);*/z=1;used_=0;zero(dsp_lijn,sizeof dsp_lijn);
		z=20;hz_=34;vt_=3;
		AddTextKey(z++,hz_,vt_,15,2,10001,"codenummer",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		AddTextKey(z++,hz_,vt_,15,2,10002,"omschrijving",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		AddTextKey(z++,hz_,vt_,15,2,10003,"groep",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		if(faskeyi(6,6,0)!=45){AddTextKey(z++,hz_,vt_,15,2,10004,"plaats\nmagazijn",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}}
		AddTextKey(z++,hz_,vt_,15,2,10005,"leverancier",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		if(faskeyi(6,14,0)!=45){AddTextKey(z++,hz_,vt_,15,2,10006,"merk\nproducent",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}}
		hz_=34;vt_=9;
		AddTextKey(z++,hz_,vt_,20,2,10011,"uitgebreide selectie",0x007FFF);hz_+=20;if(hz_>=70){hz_=34;vt_+=2;}
		AddTextKey(z++,hz_,vt_,20,2,10012,"winkelverkopen",0x007FFF); hz_+=20;if(hz_>=70){hz_=34;vt_+=2;}
#if PDA_INPUT
		AddTextKey(z++,hz_,vt_,20,2,10013,"bestelling PDA",0x007FFF);hz_+=20;if(hz_>=70){hz_=34;vt_+=2;}
#endif
    if(ovltest(2241)){
  		AddTextKey(z++,hz_,vt_,20,2,10014,"bestelling XLS",0x007FFF);hz_+=20;if(hz_>=70){hz_=34;vt_+=2;}
		}
		key=scrupd(-1,0x7FF);
		if((key/0x10000)>0) key/=0x10000;
		switch(key){
		  case 101 : return 0; break;
			case 10001 : SortArtikelsOpBon(1); return 1; break;
			case 10002 : SortArtikelsOpBon(2); return 1; break;
			case 10003 : SortArtikelsOpBon(5); return 1; break;
			case 10004 : SortArtikelsOpBon(6); return 1; break;
			case 10005 : SortArtikelsOpBon(4); return 1; break;
			case 10006 : SortArtikelsOpBon(14); return 1; break;
			case 10011 : LoadArtikelFromSelectie(); return 1; break;
			case 10012 : BestellijstWinkel(); return 1; break;
#if PDA_INPUT
			case 10013 : load_pda(NO); return 1; break;
#endif
			case 10014 : ovlcall(2241,0); return 1; break;
			default : break;
		}
  }
}

static LoadArtikelFromSelectie()
{
  int16 mode_,k,fkey;
	uint16 this_lev_;

	this_lev_=*u(1,1);
 
  seldata.prx_klt=0;
  seldata.selp_use=NO;
  if(ovlcall(2215,2)) goto endsr;

  scrget(1,7);scrupd(-3,0);
  fasinit(6);mode_=1; fkey=2;
  FOREVER{
    redo:;
    if(faskeyi(6,fkey,mode_)) break; mode_=2;
    if(DirCall_DRK2215_SelectArtikel()==NO) goto redo;

    for(k=0;k<max_line;k++){
      ram2stu(k);
      if(test_line()==NO) break;
    }
    if(k>=max_line-2) break;
		*u(58,14)=*u(6,1);
    copy(s(6,2),ps_58_15,len58_15);
    copy(s(6,3),ps_58_16,fldlen(58,16));
    stu2ram(k);
  }
endsr:;
	fasinit(1);*u(1,1)=this_lev_;fasgeti(1);
}

static SortArtikelsOpBon(sortkey_)
int16 sortkey_;
{
  int16 j,k,hz_,vt_,sw,max_,amode_,z,key,used_=0,fld_,filiaal_;
	char sortbuf[1000],choice,menu_punten[10],dsp_lijn[80];
  uint16 artrecs_[DIM58],pos_,reclev_,pos_lev_;

	reclev_=*u(1,1);

  if(sortkey_==6 && filiaal>=1 && filiaal<=10 && fldlen(58,101)){ // sorteren op pl.magazijn van filiaal
		filiaal_=*u(8,38); // van filiaal
		if(filiaal_<1 || filiaal>10) filiaal_=99;
		else if(filiaal_>0 && filiaal_<=10 && fldlen(66,11+(filiaal_-1)*15)==0) filiaal_=99;
		for(k=0;k<max_line;k++){ // meest recente stocklocatie van filiaal invullen 
			ram2stu(k);
			if(test_line() && *u(58,14)){
				if(filiaal_>0 && filiaal_<=10){
  				fasinit(66);*u(66,2)=*u(58,14); faskeyi(66,1,0);
					copy(s(66,20+(filiaal_-1)*15),s(58,101),fldlen(58,101));
				}
				else {
  				fasinit(6);*u(6,1)=*u(58,14); fasgeti(6);
					copy(s(6,29),s(58,101),fldlen(58,101));
				}
				stu2ram(k);
			}
		}
		sort_bon(101);
		return YES;
	}
	if(faskeyi(6,sortkey_,0)==45) return 0; // key bestaat niet
	scrget(1,7);scrupd(-3,0);
  zero((char *)&artrecs_[0],sizeof artrecs_);max_=0;
	k=max_line-1; if(k>DIM58) k=DIM58-1;
  for(k;k>=0;k--){
		ram2stu(k);
		if(test_line()){
		  if(max_==0 ) max_=k+1;
		  if(*u(58,14)) artrecs_[k]=*u(58,14);
		} else artrecs_[k]=0xFFFF;
	}
	fasinit(6);pos_=30000;
	if(sortkey_==4 || sortkey_==14){
		pos_lev_=7; if(sortkey_==14) pos_lev_=101;
		fasinit(1);
		FOREVER{
			if(faskeyi(1,2,2)) break;
			fasinit(6);*u(6,pos_lev_)=*u(1,1);amode_=1;
			FOREVER{
				if(faskeyi(6,sortkey_,amode_)) break; amode_=2;
				if(*u(6,pos_lev_)!=*u(1,1)) break;
				for(k=0;k<max_;k++) if(artrecs_[k]==*u(6,1)) artrecs_[k]=pos_++;
			}
		}
	}
	else{
		FOREVER{
			if(faskeyi(6,sortkey_,2)) break;
			for(k=0;k<max_;k++) if(artrecs_[k]==*u(6,1)) artrecs_[k]=pos_++;
		}
	}
	max_--;
  FOREVER{/* sorteren */
    sw=NO;
    for(k=0;k<max_;k++){
			if(artrecs_[k]>artrecs_[k+1]){
			  ram2stu(k);
	      copy(s(58,1),sortbuf,fldlen(58,0));
	      ram2stu(k+1);
	      stu2ram(k);
	      copy(sortbuf,s(58,1),fldlen(58,0));
	      stu2ram(k+1);
				pos_=artrecs_[k];artrecs_[k]=artrecs_[k+1];artrecs_[k+1]=pos_;
	      sw=YES;
			}
    }
    if(sw==NO) break;
  }
	fasinit(1);if(reclev_){*u(1,1)=reclev_;fasgeti(1);}
	return 1;
}



static BestellijstWinkel()
{
  int16 curs=3,k,key,z,mode,pmaxtb_,inq_kassa,inq_filiaal;
	uint16 dt_bon_beg=0,dt_bon_end=0,rec_;
	long qbak_,qstks_;
	float qlv,factor_;
  char add_ftvk='J';

  inq_kassa=0; inq_filiaal=0;
	if(filiaal) inq_filiaal=filiaal;
	else{
  	if(max_kassa<=1) inq_kassa=1;
  	else{
  		for(k=0;k<max_kassa;k++) if(loc_nr[k]==filiaal) break;
  		if(k<max_kassa) inq_kassa=k+1;
  	}
	}
  if(dt_bon_beg==0) dt_bon_beg=*u(25,2); if(dt_bon_end==0) dt_bon_end=dt_bon_beg;
  FOREVER{
    redo:;
    scrget(2,381);z=1;
    scrifld(z++,VarTextFmt(45,0),"Toevoegen verkochte artikels van winkel");
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dt_bon_beg);scrifld(z++,fm_udat,&dt_bon_end);
    scrifld(z++,fm_uu2,&inq_kassa);
		if(fldlen(66,11)){scrifld(-z,fm_uu2,&inq_filiaal);z++; scrifld(z++,fm_os6,nm_fil);}
		else z+=2;
		if(ft_off>0) scrifld(z++,fm_u_JN,&add_ftvk);	else streepje(z++);
		z++;
		for(k=0;k<5;k++) {
			scrifld(z++,fm_os6,&nm_kassa[k][0]);
			scrifld(z++,fm_odat,&dt_kvk[k]);
			scrifld(z++,fm_os6,&nm_kassa[k+5][0]);
			scrifld(z++,fm_odat,&dt_kvk[k+5]);
		}
    key=scrupd(curs,0x481);curs=3;
    if(key==101 || key==111) goto endsr;
    if(dt_bon_end==0 || dt_bon_end<dt_bon_beg){curs=4;errnum=38;goto redo;}
    if(inq_filiaal<0 || (inq_filiaal>10 && inq_filiaal!=99)) {zero(nm_fil,sizeof nm_fil);curs=5; errnum=34;goto redo;}
		if(inq_filiaal && inq_filiaal<=10){
			if(fldlen(66,11+(inq_filiaal-1)*15)==0) {errnum=34;curs=5; goto redo;}
			copy(nm_loc[inq_filiaal-1],nm_fil,6);
		}
		else if(inq_filiaal==99) copy("DEPOT",nm_fil,6);
		else zero(nm_fil,sizeof nm_fil);
    if(inq_kassa && (fldlen(91,11+(inq_kassa-1)*5)==0 || nm_kassa[inq_kassa-1][0]=='\0') ){
      curs=5;errnum=34;goto redo;
    }
    if(key==108) break;
  }
  seldata.selp_use=NO;
  if(ovlcall(2215,2)) goto endsr;
	for(pmaxtb_=max_line-1;pmaxtb_>=0;pmaxtb_--){ram2stu(pmaxtb_); if(*s(58,16)) break;} pmaxtb_++;
	fasinit(6);
  FOREVER{
    next_art:;
    if(faskeyi(6,2,2)) break;
    if(DirCall_DRK2215_SelectArtikel()==NO) goto next_art;
    fasinit(91);*u(91,2)=*u(6,1);*u(91,3)=dt_bon_beg;mode=1;qlv=0;rec_=*u(6,1);
    FOREVER{
      next_bew:;
      if(faskeyi(91,1,mode)) break;mode=2;
      if(*u(6,1)!=*u(91,2)) break;
      if(dt_bon_beg && *u(91,3)< dt_bon_beg) goto next_bew;
      if(dt_bon_end && *u(91,3)>dt_bon_end) break;
      if(inq_kassa){
				qlv+=*f(91,11+(inq_kassa-1)*5);
				if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
					qlv+=*f(91,11+(inq_kassa-1+ft_off)*5);
				}
      }
      else{
				for(k=0;k<max_kassa;k++){
					if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue;
					if(fldlen(91,11+k*5)){
						qlv+=*f(91,11+k*5);
					}
					if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
						qlv+=*f(91,11+(k+ft_off)*5);
					}
				}
      }
    }
    if(qlv){
			if(*f(6,31)<1) *f(6,31)=1;					
			factor_=1.;
			if(fldlen(6,102) && *u(6,102)){// stock/omzet op moederfiche bijwerken
				factor_=*f(6,31);
				*u(6,1)=*u(6,102);fasgeti(6);
				if(*f(6,31)) factor_/=*f(6,31); else factor_=1.;
			}
			qlv*=factor_;
			qbak_=(long)(qlv); qstks_=0;
			if(*f(6,31)>1 && qlv>0){
				qstks_=(long)(((qlv-qbak_) * *f(6,31))+0.49);
			} else qstks_=0;
			if(qbak_){
				ram2stu(pmaxtb_);
				*u(58,14)=*u(6,1); 
				copy(s(6,2),s(58,15),fldlen(58,15));
				copy(s(6,3),s(58,16),fldlen(58,16));
   		  *f(58,7)=qbak_;
				Fill1Line();*u(58,17)=hash();
				stu2ram(pmaxtb_++);
				if(pmaxtb_>=max_line) goto endsr;
			}
			if(qstks_) {
				ram2stu(pmaxtb_);
				*u(58,14)=*u(6,1); 
				copy(s(6,2),s(58,15),fldlen(58,15));
				copy(s(6,3),s(58,16),fldlen(58,16));
   		  *f(58,7)=qstks_; *s(58,62)='S';
				Fill1Line();*u(58,17)=hash();
				stu2ram(pmaxtb_++);
				if(pmaxtb_>=max_line) goto endsr;
			}
			*u(6,1)=rec_;fasgeti(6);
    }
  }
	endsr:;
}

static ins_lin(nr_)
int16 nr_;
{
  int16 j;
						
  ram2stu(max_line-1);
  if(*s(58,16)) return NO;/* geen plaats voor insert */
  for(j=max_line-1;j>nr_;j--){
    ram2stu(j-1);stu2ram(j);
  }
  init58(nr_,YES);
  return YES;
}

static calc(nr_,mode_)
int16 nr_,mode_;
{
  int16 j,k,max_;
  double ap_netlev;
									
  for(j=0;j<BTWDIM;j++) btw_bas[j]=0;
  alg_tot=0;tot_leeg=0;belastbt=0;
  if(mode_) max_=nr_+1; else max_=max_line;
  for(k=nr_;k<max_;k++){
    ram2stu(k);
    if(*ps_58_16 && *u(58,14)){
      *pf_58_31=*f(58,7);
      if(fldlen(58,8)){
        if(*s(58,62)=='P' && *f(58,8)) *pf_58_31*=*f(58,8);
      }
      ap_netlev=*f(58,20);
      ap_netlev=round((double)ap_netlev* *pf_58_31);

      if(*i(58,34)!=99){
	if(len58_35) *pd_58_35=ap_netlev;
      }
      else {
	*pd_58_35=0;
	*f(58,47)=ap_netlev;
      }
      *f(58,47)=round((double)(*f(58,49) * *f(58,46)* *pf_58_31));
      belastbt+=*pd_58_35; tot_leeg+=*f(58,47);
    }
    j=btw_tab((BEDRAG)*pd_58_35);
    if(fldlen(58,33)) *s(58,33)=j+btw_kol;
    btw_bas[j]+=*pd_58_35;
    stu2ram(k);
  }
  belastbt=0;
  for(k=0;k<BTWDIM-BTWDIV;k++){
    belastbt+=btw_bas[k];
  }
  btw_tot=0;
  for(k=0;k<BTWDIM;k++){
    btw_bd[k]=round((double)(btw_bas[k]*btw_pct[k])/100.);
    btw_tot+=btw_bd[k];
  }
  alg_tot=belastbt+btw_tot+tot_leeg;
}

static cursget(lin_,fld_)
int16 lin_,fld_;
{
  int16 g=0,k,q_per_line=1;

  for(k=0;k<sizeof det_nr/2;k++){
    if(fld_ && det_nr[k]==fld_) g=q_per_line;
    if(fldlen(58,det_nr[k])>0) q_per_line++;
  }
  return (int16)(z_base+lin_*q_per_line+g);
}

static dsp_tot()
{
  int16 k,key,z,z_extra_;

  scrget(2,29);z=1;z_extra_=110;
	scraddf(z_extra_,23,52,8);
  if(prt_levbon=='J') scrifld(z_extra_++,VarTextFmt(15,0)," F9 geen print");
  else scrifld(z_extra_++,VarTextFmt(14,0)," F9 print bon ");
	scraddpicto(1,0,72,22,4,2,583,0,0,"maak PDF"); 
	scraddpicto(2,0,76,22,4,2,569,0,0,"mail"); 
  scrfld(z++,25,1);
  scrifld(z++,fm_obd,&alg_tot);
  for(k=0;k<4;k++)scrifld(z++,fm_us75,opm_foot[k]);
  for(k=0;k<2;k++)if(*u(8,19+k)) scrifld(z++,fm_os60,std_txt[*u(8,19+k)-1]);
  else z+=2;
  key=scrupd(2,0x1A2);
  prt2pdf=NO;
  if ((key/0x100)==1) key=(key&0xFF)+5000;
	switch(key){
		case 5001 : prt_levbon='J'; prt2pdf=YES; key=108; break; // pdf
		case 5002 : prt_levbon='J';prt2pdf=2;key=108; break; // mailen
		default : break;
	}
  if(key==102)return 2;
  if(key==106)return NO;
  if(key==109){
    if(prt_levbon=='J') prt_levbon='N'; else prt_levbon='J';
    return YES;
  }
  return YES;
}
 
static MailDocument(SendMode)  // 0=tonen, 1=direct versturen
int SendMode;
{
  int j,k,p_adr_=0;
	uint16 dt_,nr_,yy,mm,dd;
	  
		// keywords invullen 
	fasinit(2);
	if(filiaal!=99){
		for(k=0;k<10;k++) if(loc_nr[k]==filiaal) break;
	  if(k<10){*u(2,1)=loc_klt[k];fasgeti(2);}
	}
	else copy("DEPOT",s(2,3),10);
	zero(MailMergeData[0],sizeof MailMergeData);MailSaveAdres='N';
	dt_=*u(8,8);nr_=*u(8,2);
	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy(s(2,3),MailMergeData[k],fldlen(2,3)); continue;}
		if(cmpstr(MailMergeKeywords[k],"ADRES",5)==0){copy(s(2,4),MailMergeData[k],fldlen(2,4)); continue;}
		if(cmpstr(MailMergeKeywords[k],"POSTCODE",8)==0){copy(s(2,5),MailMergeData[k],fldlen(2,5)); continue;}
		if(cmpstr(MailMergeKeywords[k],"GEMEENTE",8)==0){copy(s(2,6),MailMergeData[k],fldlen(2,6)); continue;}
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){p_adr_=k;copy(s(2,21),MailMergeData[k],fldlen(2,21)); continue;}
		if(fldlen(1,130) && cmpstr(MailMergeKeywords[k],"CC_EMAILADRES",13)==0){copy(s(2,130),MailMergeData[k],fldlen(2,130)); continue;}
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNAAM",12)==0){
			if(dok_type!=110){
			 if(alg_tot>=0) copy0(facttxt[taaltxt],MailMergeData[k],50);
			 else copy0(credntxt[taaltxt],MailMergeData[k],50);
			}
			else copy0("Offerteaanvraag",MailMergeData[k],50);
			continue;
		}
		if(dok_type!=110 && cmpstr(MailMergeKeywords[k],"DOCUMENTNUMMER",13)==0){stcli_d(MailMergeData[k],(long)nr_,5,1); continue;}
		if(cmpstr(MailMergeKeywords[k],"DATUM",5)==0){
			jddate(dt_,&yy,&mm,&dd);
      stcli_d(&MailMergeData[k][0],(long)dd,2,0);MailMergeData[k][2]='/';
      stcli_d(&MailMergeData[k][3],(long)mm,2,0);MailMergeData[k][5]='/';
      stcli_d(&MailMergeData[k][6],(long)yy,4,0);
			continue;
		}
		if(cmpstr(MailMergeKeywords[k],"TOTAALBEDRAG",12)==0){stcli_d(MailMergeData[k],(long)(nr_),5,1); continue;}
		if(cmpstr(MailMergeKeywords[k],"FIRMAGEMEENTE",13)==0){
      if(filiaal==99 || filiaal==0) copy(&firma[65],MailMergeData[k],20); 
      else if(filiaal>0 && filiaal<=10 && fldlen(66,11+(filiaal-1)*15)) {
				copy(s(2,1),buf1000,fldlen(2,0));
				fasinit(2);
      	for(j=0;j<10;j++) if(filiaal==loc_nr[j]) break;
	      if(j<10){
  				fasinit(2);*u(2,1)=loc_klt[j]; if(*u(2,1)) fasgeti(2);
				}
				copy(s(2,6),MailMergeData[k],20);
				copy(buf1000,s(2,1), fldlen(2,0));
			}
			continue;
		}
	}
	zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage); // voor de veiligheid
	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);MailMergeBijlage[0]=SpoolFileNr;
	zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate);
	if(dok_type==110) copy("AKOFF",MailMergeSpecialTemplate,5);
	MailMergeFormaat=7; 

	if(fldlen(2,16)) MailMergeTaal=talen[taaltxt]; else MailMergeTaal='\0';
	k=SendMail(SendMode); 
//	if(k && MailSaveAdres=='J'){copy(MailMergeData[p_adr_],s(1,21),fldlen(1,21));fasupd(1);} // email adres bewaren
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

static kill()
{
  int16 k;

  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*u(58,1)) faskill(58);
  }
  for(k=0;k<DIM8;k++) if(rec_8[k]) {*u(8,1)=rec_8[k];faskill(8);}
}

static load_bon(mode_,mode1,type_)
int16 mode_,mode1,type_;
{
  int16 g=0,k,j=0,h=0;
  flag first=YES;

  for(k=0;k<DIM8;k++) rec_8[k]=0;
  FOREVER{
    if(first==NO){
      if(g==DIM8) break;
      if(faskeyi(8,1,2)) break;
    }
    if(*u(8,3)!=filiaal) break;
    if(fldlen(8,36) && *i(8,36)!=type_) goto next;
    rec_8[g++]=*u(8,1);
    for(k=0;k<max_line;k++){
      fasinit(58);*u(58,2)=*u(8,1);*u(58,3)=k;
      if(faskeyi(58,1,0)==0){
	stu2ram(j++);
      }
      if(mode_){
	if(j>=(max_line-3)){/* bon gaat er niet meer bij */
	  rec_8[--g]=0;init58(h,NO);j=h;
	  goto end;
	}
      }
    }
    h=j;
    if(mode_==NO) break;/* slechts 1 bon laden */
    next:;
    first=NO;
  }
  end:;
  if(g==0) return NO;
  init58(j,NO);
  if(mode_){*u(8,1)=rec_8[0];fasgetu(8);}
  keepdata=YES;
  return YES;
}
 
static write_bon()
{
  int16 k,g;
  uint16 rec8_;

  *u(8,3)=filiaal;
  if(fldlen(8,36)) *i(8,36)=THISTYP;
  if(fldlen(8,37) && DT_EXEC0) *u(8,37)=0;
  if(*u(8,1)){
		if(fldlen(8,71)) *u(8,71)=procid;
		if(fldlen(8,72)) *u(8,72)=*u(25,2);
		g=fasupd(8); 
	}
	else{
		if(fldlen(8,70)) *u(8,70)=procid;
		if(fldlen(8,72)) *u(8,72)=*u(25,2);
		g=fasadd(8);
	}	
  rec8_=*u(8,1);
  if(errnum==0) errnum=g;
  for(k=0;k<max_line;k++){
    fasinit(58);*u(58,2)=rec8_;*u(58,3)=k;
    if(faskeyi(58,1,0)==0) faskill(58);
    ram2stu(k); *u(58,1)=0;
    if(*ps_58_16 || *u(58,14)){
      if(fldlen(58,72)){
	if(DT_EXEC0) *u(58,72)=0;
	else *u(58,72)=*u(8,37);
      }
      *u(58,2)=rec8_;
      *u(58,3)=k;
      if(*u(58,1)) g=fasupd(58); else g=fasadd(58);
      if(errnum==0) errnum=g;
    }
  }
  fasflush(0);
}
 
static get_lev(ptxt,mode_,only_lev)
char *ptxt;
int16 mode_,only_lev;
{
  int16 j,k,key,fkey,z,curs,start=0,mode8_;
  uint16 lev_dt_,bonnr_=0,vanfilnr_=99;
  char c_type[3];

  for(k=0;k<(sizeof aard)/4;k++){
    if(aard[k].typ==THISTYP){
      copy(aard[k].pnm,c_type,2);break;
    }
  }
  curs=4;
  fasinit(1);fasinit(8);
	if(vanfilnr_<=0 || vanfilnr_>10) {zero(van_fil,sizeof van_fil);}
  else copy(nm_loc[vanfilnr_-1],van_fil,6);
  redo:
  scrget(2,238);z=1;
  if(only_lev) scrifld(z++,fm_os30,"Artikelen onder minimumstock");
  else scrifld(z++,fm_os25,"Leveringsbons");
  scrfld(z++,25,1);
  scrifld(z++,VarTextFmt(60,0),ptxt);
  scrifld(-z,fm_uu2,&filiaal); z++; scrifld(z++,fm_os6,nm_fil);
  if(only_lev==NO){
		scrifld(z++,fm_uu5,&bonnr_);
		scrfld(z++,8,8);
		streepje(z++);z++;
		streepje(z++);
	}
	else{
		streepje(z++);streepje(z++);
		scrifld(-z,fm_uu2,&vanfilnr_);z++; scrifld(z++,fm_os6,van_fil);
	  scrifld(z++,fm_u_JN,&OnlyWithDepotStock);
	}
  key=scrupd(curs,0x0481);curs=4;
  if(key==101) return NO;
  if(key==111) ovl_exit(0);
	if(only_lev){
		if(filiaal<=0 || (filiaal>10 && filiaal!=99)) {zero(nm_fil,sizeof nm_fil); errnum=34;goto redo;}
	}
	else{
    if(filiaal && (filiaal<=0 || (filiaal>10 && filiaal!=99))) {zero(nm_fil,sizeof nm_fil); errnum=34;goto redo;}
		if(key!=18 && filiaal==0 && bonnr_==0) {errnum=38; goto redo;}
	}
	
	if(filiaal && filiaal<=10){
    if(fldlen(66,11+(filiaal-1)*15)==0) {errnum=34;goto redo;}
    copy(nm_loc[filiaal-1],nm_fil,6);
	}
	else if(filiaal==99) copy("DEPOT",nm_fil,6);
	if(nm_fil[0]=='\0') {curs=4;errnum=39;goto redo;}
	if(only_lev){
		if(vanfilnr_ && vanfilnr_<=10){
			if(fldlen(66,11+(vanfilnr_-1)*15)==0) {curs=8;errnum=34;goto redo;}
			copy(nm_loc[vanfilnr_-1],van_fil,6);
		}
		else copy("DEPOT",van_fil,6);
		if(van_fil[0]=='\0') {curs=8;errnum=39;goto redo;}
		if(cmpstr(van_fil, nm_fil,6)==0) {curs=8;errnum=34;goto redo;}
		if(key==18){curs=fldcurs+1;goto redo;}
		*u(8,38)=vanfilnr_;
		return YES;
	}
	if(key==18){curs=fldcurs+1;goto redo;}
  dok_type=THISTYP;
  lev_dt_=*u(8,8);
  fasinit(8);*u(8,3)=filiaal;*u(8,8)=lev_dt_;*u(8,2)=bonnr_; mode8_=1;
	if(bonnr_){ // direct bonnr ingevuld
    FOREVER{
			next8:;
			if(faskeyi(8,2,mode8_)) break; mode8_=2;
			if(lev_dt_ && *u(8,8)!=lev_dt_) goto next8;
			if(fldlen(8,36) && *i(8,36)!=dok_type) goto next8;
			if(*u(8,2)!=bonnr_) goto next8;
			filiaal=*u(8,3);
			if(filiaal && filiaal<=10){
				if(fldlen(66,11+(filiaal-1)*15)==0) {errnum=34;goto redo;}
				copy(nm_loc[filiaal-1],nm_fil,6);
			}
			else if(filiaal==99) copy("DEPOT",nm_fil,6);
			return YES;
		}
		if(bonnr_) curs=6; errnum=34; goto redo;
	}
  fkey=1; // volgens filiaal 
  for(k=0;k<DIM8;k++){
    if(k==1 && mode_==NO) break;
    next:;
    if(faskeyu(8,1,fkey)) break;
    fkey=2;
    if(*u(8,3)!=filiaal) break;
    if(lev_dt_ && *u(8,8)!=lev_dt_) goto next;
    if(fldlen(8,36) && *i(8,36)!=dok_type) goto next;
    rec_8[k]=*u(8,1);
  }
  if(k==0) {fasinit(8);*u(8,8)=lev_dt_;errnum=14;goto redo;}
  if(k>1){
    FOREVER{
      scrget(2,32);z=1;
      /* scrifld(z++,fm_ou2,&filiaal);*/ scrifld(z++,fm_os6,nm_fil);
      for(j=start;j<k;j++){
	fasinit(8);*u(8,1)=rec_8[j];fasgeti(8);
	j++;scrifld(z++,fm_ou2,&j);j--;
	scrofld(z++,8,8,-1);
	scrofld(z++,8,25,-1);
	scrofld(z++,8,2,-1);
	if(j==start+14) break;
      }
      j=0;scrifld(62,fm_uu2,&j);
      key=scrupd(1,0x87);
      if(key==101) {fasinit(8);*u(8,8)=lev_dt_;goto redo;}
      if(j>0 && j<=k) {rec_8[0]=rec_8[j-1];break;}
      if(key==102) start-=15;
      if(key==103) {start+=15;if(start>k-15) start=k-15;}
      if(start<0) start=0;
    }
  }
  *u(8,1)=rec_8[0];fasgetu(8);
  return YES;
}

static ok_kil()
{
  int16 key;

  redo:
  scrget(1,10);
  scrifld(1,fm_os25,"Leveringsbons");
  scrfld(2,25,1);
  scrofld(3,8,3,-1);
  key=scrupd(0xFFFF,0x419);
  if(key==111) ovl_exit(0);
  if(key==101) return NO;
  if(key!=104 && key!=105) {errnum=21;goto redo;}
  if(key==104) return YES;
  return NO;
}
 
static uint16 hash()
{
  char *ps;
  int16 k;
  uint16 fuval=0;
				
  k=hash_len;ps=s(58,14);
  while(k--) fuval=fuval*3+*(ps++);
  k=len58_62;ps=ps_58_62;
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
}

static sort_bon(sortfld_)
int16 sortfld_;
{
  int16 j,k,len_,beg_,sw,max_,b_beg_,b_end_;
  char str1[35],str2[35],*ps_;
 
	if(sortfld_ && fldlen(58,sortfld_)){len_=fldlen(58,sortfld_);ps_=s(58,sortfld_);}
	else{sortfld_=0; len_=len58_15;ps_=ps_58_15;}
#if SORT_FLD
  if(sortfld_==0 && fldlen(58,SORT_FLD)){len_=fldlen(58,SORT_FLD);ps_=s(58,SORT_FLD);}
#endif
  max_=max_line-1;
  for(max_;max_>=0;max_--){ram2stu(max_); if(test_line()) break;}
#if YES // SCREXEC/* lege lijnen wissen, enkel nodig bij schermupdate */
  for(k=0;k<max_;k++){
    ram2stu(k);
    if(test_line()==NO){
      copy(s(58,1),sortbuf,fldlen(58,0));
      for(j=k;j<max_;j++){
	ram2stu(j+1);
	stu2ram(j);
      }
      copy(sortbuf,s(58,1),fldlen(58,0));
      stu2ram(max_); max_--;
    }
  }
#endif

	beg_=0; max_++;
	FOREVER{
next_blok:;
		if(beg_>=max_-1) break;
		b_beg_=-1; b_end_=-1;
	  for(k=beg_;k<max_;k++) {
      ram2stu(k); 
#if FLAGEPD
		  if(*ps_58_16=='*'){
#else
		  if(*ps_58_16=='*' && *s(58,62)=='S'){
#endif
		  	if(b_beg_<beg_) continue;
				else {b_end_=k; break;}
		  }
		  else if(b_beg_<beg_) b_beg_=k;
	  }
		if(b_end_<0) b_end_=k;
		if((b_end_-b_beg_)<2) {beg_=b_end_+1;goto next_blok;} // te weinig lijnen om te sorteren
		FOREVER{/* sorteren */
			sw=NO;
			for(k=b_beg_;k<b_end_-1;k++){
				ram2stu(k);
				copy(ps_,str1,len_);
				ram2stu(k+1);
				if(test_line()){
					if(cmp_srt(str1,ps_,len_)==1){
						ram2stu(k);
						copy(s(58,1),sortbuf,fldlen(58,0));
						ram2stu(k+1);
						stu2ram(k);
						copy(sortbuf,s(58,1),fldlen(58,0));
						stu2ram(k+1);
						sw=YES;
					}
				}
			}
			if(sw==NO) break;
		}
		beg_=b_end_+1;
	}
}

static cmp_srt(p1,p2,len)
char *p1,*p2;
int16 len;
{
  while(len--){
    if(*p1>*p2) return 1;
    if(*p1<*p2) return -1;
    p1++;p2++;
  }
  return 0;
}

static load_sysnr(just_blok)
int16 just_blok;
{
  int16 sec_=0,k,busy_proc,last_proc_=0;
	char cmd_str_[100],postnaam_[30];
                                                            
  if((upd_mode==NO && chk_nr) || just_blok){
    FOREVER{
redo_wait:;
			sysflush();
      sysget(SysPosNrCheck,2,&busy_proc);
      if(busy_proc && busy_proc!=procid) {
				if(busy_proc!=last_proc_){
					zero(cmd_str_,sizeof cmd_str_);zero(postnaam_,sizeof postnaam_);
					k=copy0("GetIniKeyValue|Post-",&cmd_str_[0],50);
					stcli_d(&cmd_str_[k],(long)(1+busy_proc/5),3,0);k+=3;
					k+=copy0("_Settings|Name",&cmd_str_[k],50);
					ExecJmsCommand(postnaam_,25,cmd_str_);
					last_proc_=busy_proc;
				}
				sprintf(buf1000,"       Bonnummer bezet door %s (Post-%d, Scherm-%d)",postnaam_,1+(busy_proc/5),busy_proc%5);
        scrget(1,170);
        scrifld(10,fm_os79,buf1000);
        scrifld(14,fm_os79,"                          Even geduld a.u.b.");
        scrupd(-3,0);
        _sleep(1000);sec_++;
      }
      else{
				sysput(SysPosNrCheck,2,&procid);
				sysflush();
				if(just_blok==NO) sysget(last_vfa,2,&last_vf);
				for(k=0;k<10;k++){
					sysget(SysPosNrCheck,2,&busy_proc);/* dubbele check */
					if(busy_proc!=procid) goto redo_wait;
				}
				break;
      }
    }
  }
}

static ClearSysPosNrCheck()
{
  int16 busy_proc;
	  
	sysget(SysPosNrCheck,2,&busy_proc);
  if(busy_proc==procid){busy_proc=0;sysput(SysPosNrCheck,2,&busy_proc);}
}

static copy0(ps,pd,len_)
char *ps,*pd;
int16 len_;
{
  int16 fuval=0;
				
  while(*ps){
    *pd++=*ps++;
    fuval++;
    if(fuval>=len_) break;
  }
  *pd='\0';
  return fuval;
}



static ft_prt()
{
  int16 j,k,z,prt_ok_;
  double bedrag_;
	float vstock_;
	char str_st_[3],ori_fil_[10],buf_[50],vpl_mag_[10];

  scrget(1,6);scrupd(-3,0);
	k=14;
#if FLAGSAS
	k=16;
#endif
  getsysprNew(k,form_dat,&prmode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if (prtopen(prtnr,form_dat,6,80,prmode,4)!=0) {prt_error=YES;goto endsr;}

  scrget(1,6);scrupd(-3,0);
	zero(ori_fil_,sizeof ori_fil_);
	if(*u(8,38)<1 || *u(8,38)>10) copy("DEPOT",ori_fil_,6);
	else copy(nm_loc[*u(8,38)-1],ori_fil_,6);
	 
  prttext("<t1b>Levering nr.");prtfld(8,2,-1);
	prttext(" van <e>"); prttext(ori_fil_); prttext("<e> aan <e>");prtifld(fm_uu2,&filiaal,-1); prttext("<e> ");
	fasinit(2);
	if(filiaal!=99){
		for(k=0;k<10;k++) if(loc_nr[k]==filiaal) break;
	  if(k<10){*u(2,1)=loc_klt[k];fasgeti(2);}
	}
	else copy("DEPOT",s(2,3),10);
  prtfld(2,3,20);
  prttext("<t68>Datum ");prtfld(8,8,-1);prttext("<b>");
  prtbuf(1);z=1;
#if FLAGSAS
  prttab(z,58,15,2,-1); prttitle(z++,"Artnr",3);
  prttab(z,58,101,2,-1); prttitle(z++,"Mag.",3);
  prttab(z,58,7,1,-1); prttitle(z++,"Aantal",0x13);
  prtitab(z,fm_os3,&str_st_,2,-1); prttitle(z++,"",3);
  prttab(z,58,16,2,-1); prttitle(z++,"Omschrijving",3);
#else
  
#if FLAGAST
	fmt_get(58,101); prtitab(z,fmt,vpl_mag_,1,-1); prttitle(z++,"Mag.",3);
  fmt_get(6,33); prtitab(z,fmt,&vstock_,1,-1); prttitle(z++,"Stock",0x13);
#else
	prttab(z,58,101,2,-1); prttitle(z++,"Mag.",3);
#endif
  prttab(z,58,15,2,-1); prttitle(z++,"Artnr",3);
  prttab(z,58,16,2,30); prttitle(z++,"Omschrijving",3);
  prttab(z,58,7,1,-1); prttitle(z++,"Aantal",0x13);
  prtitab(z,fm_os3,&str_st_,2,-1); prttitle(z++,"",3);
#endif
#if PRTBDR
  prttab(z,58,20,1,-1); prttitle(z++,"Eh.prijs",0x13);
  prttab(z,58,35,1,-1); prttitle(z++,"Goederen",0x13);
  prttab(z,58,47,1,-1); prttitle(z++,"Leegg.",0x13);
#endif
  prtbuf(3);
	zero(buf_,sizeof buf_); sprintf_s(buf_,50,"Levering van %s aan %s",ori_fil_,nm_fil);
	p_pdfname(buf_,*u(8,8),0);
  free=999;
  if(*u(8,38)){
    prttext("<b>Stockmutatie van ");
		fasinit(2);
		if(*u(8,38)>=1 && *u(8,38)<=10){
			for(k=0;k<10;k++) if(loc_nr[k]==*u(8,38)) break;
			if(k<10){*u(2,1)=loc_klt[k];fasgeti(2);}
		}
		else copy("DEPOT",s(2,3),10);
		*(s(2,3)+20)='\0';prttext(s(2,3));
		prttext(" naar ");
		fasinit(2);
		if(filiaal!=99){
			for(k=0;k<10;k++) if(loc_nr[k]==filiaal) break;
			if(k<10){*u(2,1)=loc_klt[k];fasgeti(2);}
		}
		else copy("DEPOT",s(2,3),10);
		*(s(2,3)+20)='\0';prttext(s(2,3));
		prttext("<b>");
    nextline(); nextline();
  }
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(test_line()){
      if(*u(58,14)==0 || *pf_58_31){/* niet gebruikte lijnen skippen */
				fasinit(6);fasinit(66);
				if(*u(58,14)){
					*u(6,1)=*u(58,14); fasgeti(6);
					*u(66,2)=*u(58,14); faskeyi(66,1,0);
				}
#if FLAGAST
				if(*u(8,38)>=1 && *u(8,38)<=10){
					copy(s(66,20+(*u(8,38)-1)*15),vpl_mag_,fldlen(58,101));
					vstock_=*f(66,11+(*u(8,38)-1)*15);
				}
				else {
					copy(s(6,29),vpl_mag_,fldlen(58,101));
					vstock_=*f(6,33);
				}
#endif  
				zero(str_st_,3);
				if(fldlen(58,62)){
					if(*s(58,62)=='S') copy("Stk",str_st_,3);
					else if(*s(58,62)=='P') copy("Pal",str_st_,3);
				}
				if((free-skip_off)<5) prtform(0);
	for(j=0;j<10;j++) prtinfo(j,0);nextline();
      }
    }
  }
  nextline();
  if(boek_mode){
    nextline();
#if BOEKALLO
    prttext("<t5b>*** INGEBOEKT OP ");prtifld(fm_udat,u(25,2),-1);
    if(boek_JN=='J'){
      prttext(" via interne boeking ");prtifld(fm_uu2,&journl,-1); prttext("/");prtifld(fm_uu5,&ft_nr,-1);
    }
#else
    prttext("<t5b>*** INGEBOEKT OP ");prtifld(fm_udat,u(25,2),-1);
#endif
    prttext(" ***<b>");nextline();
  }
  if((free-skip_off)<26 && (free-skip_off)>20) {nextline();nextline();}
  else skip_lin(26);
  prt_ok_=NO;
  for(k=0;k<4;k++){
    if(opm_foot[k][0]!='\0'){
      prtifld(fm_us75,opm_foot[k],-1);nextline();
      prt_ok_=YES;
    }
  }
  if(prt_ok_)nextline();

#if PRTBDR
  skip_lin(10);
  for(j=0;j<3;j++){
    prttext("<t3>");
    for(k=0;k<BTWDIM-BTWDIV+1;k++){
      if(btw_bas[k]){
	prtblank(2);
	if(j==0){prttext("    <u>");prtifld(fm_uf21_,&btw_pct[k],-1);
	  prttext(" %<u> ");}
	else{
	  if(j==1) bedrag_=btw_bas[k];
	  if(j==2) bedrag_=btw_bd[k];
	  prtifld(fm_obd,&bedrag_,-1);prtblank(1);
	}
      }
    }
    if(j==0){
      prttext("<t50>Leeggoed:");
      bedrag_=tot_leeg;
    }
    else if(j==1){
      prttext("<t50>Goederen:");
      bedrag_=belastbt;
    }
    else{
      prttext("<t52>B.T.W.:");
      bedrag_=btw_tot;
    }
    prttext(TABT);prtifld(fm_obd,&bedrag_,-1);
    nextline();
  }
  prttext("<t52>Totaal:");
  prttext("<t65>");prtifld(fm_os3,ft_munt,-1);
  prttext(TABT);prtifld(fm_obd,&alg_tot,-1);
  nextline();
#endif
  prtform(0);SpoolFileNr=prtclose();
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
    copy(&string[pos_],&buf_[2],len_);
    buf_[2+len_]=0xD0;
    prttext(buf_);
    slen_-=len_;pos_+=len_;
  }
}

static uint16 GetAKFiche(arec_,lrec_,dt_beg_)
uint16 arec_,lrec_,dt_beg_;
{
	int16 mode_;
	uint16 verv_rec11_=0,rec11_=0;
	
	if(fldlen(11,1)==0) return (uint16)0;   

	fasinit(11);*u(11,3)=arec_;*u(11,2)=lrec_;mode_=1;
	FOREVER{
		next:;
		if(faskeyi(11,2,mode_)) break; mode_=2;
		if(*u(11,3)!=arec_) break;
		if(*u(11,2)!=lrec_) break;
		if(*u(11,9) && *u(11,9)<dt_beg_) verv_rec11_=*u(11,1); // verlopen promotie
		else rec11_=*u(11,1);
	}
  if(rec11_==0) rec11_=verv_rec11_;
	fasinit(11);if(rec11_) {*u(11,1)=rec11_,fasgeti(11);}
	return rec11_;
}


#if PDA_INPUT
static load_pda(auto_mode_)
int16 auto_mode_;
{
  int16 key,k,len_,mode_,loaded_=0,do_sel_lev_=YES;
  uint16 dt_;
  char str_[25];

  if(auto_mode_) goto load_BS;
  if(pdad_beg==0 && pdad_end==0){
    pdad_beg=*u(25,2);pdad_end=*u(25,2);
  }
  FOREVER{
    scrget(2,273);
 //   scrofld(1,1,3,-1);
    scrifld(2,fm_udat,&pdad_beg); scrifld(3,fm_udat,&pdad_end);
    scrifld(4,fm_uu2,&pda_nr);
//		if(fldlen(11,68)) scrifld(5,fm_u_JN,&CnvPdaAantal2LevAantal);
    key=scrupd(2,0x181);
    do_sel_lev_=YES;
    if(key==101) return 0;
    if(YES /* key==109*/ ) do_sel_lev_=NO;
    if(key==108 || key==109) break;
  }
  load_BS:;
  zero(str_,sizeof str_);
  if(pda_nr){
    copy("PDA-",str_,4);stcli_d(&str_[4],(long)pda_nr,2,0);
    copy("\\moblogBS.dat",&str_[6],14);
  }
  else  copy("moblogBS.dat",&str_[0],14);
  mk_name(4410,str_);
//   mk_name(4410,"moblogBS.dat"); 
  fasclos(-2);if(fasopen(filnam,1)!=0) return NO;

  scrget(1,7);scrupd(-3,0);
  fasinit(80);mode_=0;loaded_=0;
 
  FOREVER{
    next:;
    if(read_rec(mode_)) break; mode_=1;
    if(get_num(3)==0) goto next;//  geen aantal 
    len_=ele_len(2); if(len_>fldlen(6,2)) len_=fldlen(6,2);
    if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;// begin eruit 
    fasinit(6);copy(rec_ele(2),s(6,2),len_);
    if(sys4408){
      *u(6,1)=val(s(6,2));
      if(*u(6,1)) fasgeti(6);
    }
    else faskeyi(6,1,0);
    dt_=get_date(0);
    if(pdad_beg && dt_<pdad_beg) goto next;
    if(pdad_end && dt_>pdad_end) goto next;
    if(do_sel_lev_){
      if(*u(6,7)!=*u(1,1)){
				if(GetAKFiche(*u(6,1),*u(1,1),*u(25,2))==NO) goto next;
      }
    }
    for(k=0;k<max_line;k++){
      ram2stu(k);
      if(test_line()==NO) break;
    }
    if(k>=max_line-2) return NO;
		*u(58,14)=*u(6,1);
    copy(s(6,2),ps_58_15,len58_15);
    copy(s(6,3),ps_58_16,fldlen(58,16));
    *f(58,7)=get_num(3);
    if(len58_62){
      if(*rec_ele(4)=='J') *ps_58_62='S';
      else if(*rec_ele(4)=='P') *ps_58_62='P';
    }
		Fill1Line();// *u(58,17)=hash();
		//if(CnvPdaAantal2LevAantal=='J' && fldlen(11,68) && *s(58,62)!='S' && *s(58,62)!='P'){
		//	if(GetAKFiche(*u(6,1),*u(1,1),*u(25,2))){
		//		if(*f(6,31)==0) *f(6,31)=1;
		//		if(*f(11,68)>0 && *f(6,31)>0 && *f(6,31)!=*f(11,68)){
		//			*f(58,7)*= *f(6,31)/ *f(11,68);// aantal in leveranciers	verpakking zetten  
		//		}
		//	}
		//}
    stu2ram(k);loaded_++;
  }
  endsr:;
  fasclos(-2);
  return loaded_;
}
 
static read_rec(mode_)
int16 mode_;
{
  int16 j;
  flag eof_=NO;
  long pos_;

  if(mode_){
    for(j=0;j<256;j++) if(*(p_data+j)==0x0A || *(p_data+j)=='\0') break;
    if(*(p_data+j)==0x0A || *(p_data+j)=='\0') *pl_80_1+=(j+1);
    zero(p_data,256);
  }
  pos_=*pl_80_1;
  if(fasseqi(80,1,256)) {eof_=YES;}
  if(eof_ && *p_data=='\0') return YES;
  else{/* positioneer terug op eerste karakter */
    *pl_80_1=pos_;
    return NO;
  }
}

static ele_len(nr_)
int16 nr_;
{
  int16 k=0;
  char *p;
								
  p=rec_ele(nr_);
  FOREVER{
    if(*p=='|' || *p==0x0D || *p==0x0A || *p=='\0') return k;
    p++;k++;
  }
}

static char *rec_ele(nr_)
int16 nr_;
{
  int16 k;
  char *p;
						
  p=p_data;
  for(k=0;k<nr_;k++){
    FOREVER{
      if(*p=='|' || *p==0xD || *p=='\0') break;
      p++;
    }
    p++;
  }
  return p;
}

static float get_num(nr)                           /* read number starting at pos  */
int16 nr;
{
  int16 j=0,k=0,n;
  float val_=0,val1_;
  flag na_komma=NO,neg_get=NO;
  char *pos;
									
  if(ele_len(nr)==0) return (float) val_; // leeg
	pos=rec_ele(nr); 
  FOREVER{
    if(*(pos+k)=='|' || *(pos+k)==0x0D || *(pos+k)=='\0') break;
    if(*(pos+k)=='.') na_komma=YES;
    else if(*(pos+k)=='-') neg_get=YES;
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
	if(na_komma==NO){
	  val_=val_*10 + (*(pos+k)-'0');
	}
	else{
	  j++;
	  val1_=*(pos+k)-'0';
	  for(n=0;n<j;n++) val1_=val1_/10;
	  val_+= val1_;
	}
      }
    }
    k++;
  }
  if(neg_get) return (float) -val_;
  else return (float) val_;
}

static uint16 get_date(nr)              /* read date DD/MM/JJJJ starting at pos  */
int16 nr;
{
  int16 k=0,getal_[3],p_getal_;
  uint16 dt_=0;
  char *pos;
									
  zero(getal_,sizeof getal_);p_getal_=0;
  dt_=0; pos=rec_ele(nr); if(ele_len(nr)==0) goto endsr;
  FOREVER{
    if(*(pos+k)=='|' || *(pos+k)==0x0D) break;
    if(*(pos+k)=='/'){p_getal_++;if(p_getal_>2) break;}
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
	getal_[p_getal_]=getal_[p_getal_]*10 + (*(pos+k)-'0');
      }
    }
    k++;
  }
  getal_[2]%=100;
  dt_=datejd(getal_[2],getal_[1],getal_[0]);
  endsr:;
  return (uint16) dt_;
}
#endif

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

static mk_name(adr_pref,ps)
uint16 adr_pref;
char *ps;
{
  char *pd;
				
  pd=filnam;
  sysget(adr_pref,25,pd);
  while(*pd) pd++;
  while(*ps!='\0') *pd++=*ps++;
  *pd='\0';
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

static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
  if(stu_<=2) parmcall[1]=7; // bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3; // GEEN ADD
#if NO_ART_DSP
  if(stu_==6) parmcall[1]=0;
#endif
  parmcall[2]=0;
  parmcall[3]=0;
#ifdef STRAATKEY
  if(stu_==2) parmcall[4]=STRAATKEY;
#endif
  parmcall[7]=0x0C;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}

