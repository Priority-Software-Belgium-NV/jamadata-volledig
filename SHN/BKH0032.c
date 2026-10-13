/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0032GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0032dat
#define ovlcod BKH0032cod
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

char ovldat[] = "bkh0032  00:02 19/03/10 (c) Jamadata";
/* beheer openingsbalans */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define D_LIN_SCR       15
#define MINFREE         200
#define MAXFLD          120
#define SEARBFLEN       50
#define flag            uint16

static struct {
  uint16 nr;
  uint16 typ;
/* geen naam */
  uint16 lastnr;
  long fingrb;
  long saldo;
  double saldo_vm;
  char munt[4];
  char mast_munt;
  double e_saldo;
/* niet uit sys.fas : */
  uint16 recnr;/* extra element */
} j_tab[80];

extern char *s();
extern int16 *i();
extern uint16 *u();
static uint16 get_odate();
extern long *l();
extern long val();
static long val4_1();
extern float *f();
extern double *d(), valu_cnv();
static double absdoubl();
static uint16 getgrb();

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os27[]  = {7,0x88,27,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os16[]  = {7,0x88,16,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou2_[]  = {6,0x90,2,0,0x00,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us18[]  = {7,0xC8,18,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_ol9[]   = {6,0x93,9,0,0x70,0};
static char fm_od92_[] = {6,0x95,9,2,0x60,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};
static char fm_uf3_4[] = {6,0xD4,3,4,0x70,0};
static char fm_uf3_2[] = {6,0xD4,3,2,0x70,0};
static char fm_of2_1[] = {6,0x94,2,1,0x30,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ugrb[]  = {2,0xE8};
static char fm_ogrb[]  = {2,0xA8};
static char fm_uLKG[]  = {11,0xC8,1,0,0x09,0,'K','L','G','G',0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_uXb[]   = {11,0xC8,1,0,1,0,'X','X',' ',' ',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};

static struct {
  long rec4;
  uint16 recnr;
  long code;
  char naam[30];
  double bedrag;
} bklin;
					
static char *ram,buf600[600];
static int16 ram_recl,hash_len,max_line;
static long ram_size;
static uint16 hash_val;

static uint16 last_arc,MinBkhDatum;
static uint16 df_recnr[15],rec_d_ak, rec_d_vk,rec_d_fi;
static long kltcent,levcent,df_grb[15],grb_d_ak, grb_d_vk,grb_d_fi;

static flag lvcd,klcd,debit_allow=NO,credt_allow=NO,sear_stt,halve_bkg;
static int16 journl,scrcount,notfound=0,stutyp,ref_jr,ref_yy;
static int16 chk_btoeg=1,len4_0;
static uint16 dt1_beg,dt1_end,dt2_beg,dt2_end,mnd_strt,dt1_open,dt2_open;
static char munt[4];
static char def_munt[4],valtype;
static uint16 def_qfak,vers_298,bkh_dt,volgnr,rec_kdif;
static char taal_i,talen[4];
static char searbuf[SEARBFLEN+1];
static flag sys1818,sys1840,sys1850,sys1862,sys3876,analyt;
static float btwpct[4];
static double tot_saldo;
static long *pl_4_6;
static uint16 *pu_4_4,*pu_4_5;
static char *ps_4_2;
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;


ovlcod()
{
  int16 key;
  int16 z,dd_,mm_,yy_;
  uint16 dt_;
  char choice;

  if(CheckForFreeSpace(4,MINFREE)) goto endsr;/* onvoldoende vrije records */
  initload();
  dt_=*u(25,2); if(MinBkhDatum) dt_=MinBkhDatum+1;
  jddate(dt_,&yy_,&mm_,&dd_); yy_%=100;
  yy_%=100; if(mnd_strt>mm_) yy_--; if(yy_<0) yy_=99;/* jaar 2000 */
  dt1_beg=datejd(yy_,mnd_strt,1);
  yy_++; if(yy_>99) yy_=0; dt2_beg=datejd(yy_,mnd_strt,1);
  dt1_end=dt2_beg-1;
  if(dt2_beg<=*u(25,2)){
    yy_++; if(yy_>99) yy_=0; dt2_end=datejd(yy_,mnd_strt,1)-1;
  }
  else {dt2_beg=0;dt2_end=0;}
  dt1_open=get_odate(dt1_beg,dt1_end);
  dt2_open=get_odate(dt2_beg,dt2_end);
  if(dt2_beg){
    choice='\0';
    FOREVER{
      scrget(1,238);z=1;
      scrfld(z++,25,1);
      scrifld(z++,fm_odat,&dt1_beg);scrifld(z++,fm_odat,&dt1_end);
      dsp_ftxt(z++,dt1_open);
      scrifld(z++,fm_odat,&dt2_beg);scrifld(z++,fm_odat,&dt2_end);
      dsp_ftxt(z++,dt2_open);
      scrifld(z++,fm_menu,&choice);
      scrifld(z++,fm_odat,&MinBkhDatum);
      key=scrupd(1,0x81);

      if(key==101) goto endsr;
      if(choice=='1') break;
      if(choice=='2'){
	dt1_beg=dt2_beg;dt1_end=dt2_end;dt1_open=dt2_open;
	break;
      }
      errnum=34;
    }
  }
  bkh_dt=dt1_beg; if(last_arc && bkh_dt<=last_arc) bkh_dt=last_arc+1;
  jddate(bkh_dt,&yy_,&mm_,&dd_);volgnr=mm_*100+dd_;

  choice='\0';
  FOREVER{
		redo239:;
    scrget(1,239);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0032A");
    scrfld(z++,25,1);
    scrifld(z++,fm_odat,&dt1_beg);scrifld(z++,fm_odat,&dt1_end);
    dsp_ftxt(z++,dt1_open);
    scrifld(z++,fm_menu,&choice);
    scrifld(z++,fm_odat,&last_arc);
    key=scrupd(2,0x81);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo239; // link help 
    if(key==101) break;
    switch (choice){
      case '1':  addbalans(YES);break;
      case '2':  addbalans(NO);break;
      case '3':  updbalans(); break;
      case '4':  killbalans(); break;
      case '5':  if(ovltest(57)) ovlexit(57); break;
      default : errnum=34; break;
    }
  }
  endsr:;
  ovlexit(-1);
}

static uint16 get_odate(dt_beg_,dt_end_)
uint16 dt_beg_,dt_end_;
{
  int16 mode_;
  uint16 dt_=0;
 
  if(dt_beg_==0) return (uint16)0;

  fasinit(4);*s(4,2)=journl;mode_=1;
  FOREVER{
    if(faskeyi(4,1,mode_)) break; mode_=2;
    if(*s(4,2)!=journl) break;
    if(*pu_4_4>=dt_beg_ && *pu_4_4<=dt_end_){dt_=*pu_4_4;break;}
  }
  return dt_;
}

static dsp_ftxt(z,dt_found_)
int16 z;
uint16 dt_found_;
{
  int16 yy,mm,dd;
  char txt_[80];

  zero(txt_,sizeof txt_);
  if(dt_found_){
    copy("(Balans ingegeven op ",txt_,21);
    jddate(dt_found_,&yy,&mm,&dd);
    stcli_d(&txt_[21],(long)dd,2,0);txt_[23]='/';
    stcli_d(&txt_[24],(long)mm,2,0);txt_[26]='/';
    stcli_d(&txt_[27],(long)yy,4,0);txt_[31]=')';
  }
  else{
    if(dt1_beg<last_arc) copy("(Geen balans gevonden, gearchiveerd???)",txt_,60);
    else copy("(Geen openingsbalans gevonden)",txt_,40);
  }
  scrifld(z,fm_os40,txt_);
}
 
static addbalans(mode_)/* NO=leeg, YES=get bkhsaldi */
int16 mode_;
{
  if(dt1_open) {errnum=31;goto endsr;}
  if(mode_ && dt1_beg<last_arc) {errnum=37;goto endsr;}
	zero(RamBon,RamBonSize);zeroL(ram,ram_size);
  if(mode_) getbkhbd();
  dspbalans();
  endsr:;
  dt1_open=get_odate(dt1_beg,dt1_end);
}

static getbkhbd()
{
  int16 max_,mode_,yy_,mm_,dd_;
  uint16 dt_vbeg_,add_sal_;
  double bedrag_;

  add_sal_=YES;dt_vbeg_=dt1_beg;

  jddate(dt1_beg,&yy_,&mm_,&dd_); yy_%=100;
  yy_--; if(yy_<0) yy_=99; dt_vbeg_=datejd(yy_,mm_,dd_);

  if(last_arc<dt_vbeg_) add_sal_=NO;
  if(last_arc>dt_vbeg_) dt_vbeg_=last_arc+1;

  scrget(1,7);scrupd(-3,0);
  fasinit(3); max_=0;
  FOREVER{
    next:;
    if(faskeyi(3,1,2)) break;
    if(((*s(3,2) &0xF0)>>4)>5) break;/* klasse 1 t.e.m. 5 */
    if(*s(3,5)!='J') goto next;
    bedrag_=0;
    if(add_sal_){
      fasinit(5); *u(5,2)=*u(3,1)+60000;
      if(faskeyi(5,1,0)==0) bedrag_+=*d(5,31)+*d(5,32);
    }
    if(dt_vbeg_<dt1_beg){
      fasinit(4); *l(4,6)=*l(3,2); mode_=1;
      FOREVER{
	if(faskeyi(4,3,mode_)) break; mode_=2;
	if(*l(4,6)!=*l(3,2)) break;
	if(*pu_4_4>=dt_vbeg_ && *pu_4_4<dt1_beg) bedrag_+=*d(4,32);
      }
    }
    if(!is_nul(bedrag_)){
      ram2stu(max_);
      bklin.recnr=*u(3,1);
      bklin.code=*l(3,2);
      copy(s(3,3),bklin.naam,fldlen(3,3));
      bklin.bedrag=bedrag_;
      stu2ram(max_++); if(max_>=max_line) {errnum=11;break;}
    }
  }
  endsr:;
}

static g_anal_tst()
{
  if(!analyt || ((*s(3,2) &0xF0)>>4)!=9) return NO;
  return YES;
}

static updbalans()
{
  int16 k,sw,max_,mode_;
  uint16 n;
  char str1_[10],str2_[10];
 
  if(dt1_open==0) {errnum=14;goto endsr;}
	zero(RamBon,RamBonSize);zeroL(ram,ram_size);
 
  fasinit(4);*ps_4_2=journl;mode_=1; scrget(1,7);scrupd(-3,0);
  n=0;scrnum=0;max_=0;
  FOREVER{
    next:;
    if(faskeyi(4,1,mode_)) break; mode_=2;
    if(*ps_4_2!=journl) break;
    if(*pu_4_4<dt1_beg || *pu_4_4>dt1_end) goto next;

    ram2stu(max_);
    fasinit(3);*l(3,2)=*l(4,6);faskeyi(3,1,0);
    bklin.rec4=val4_1();
    bklin.recnr=*u(3,1);
    bklin.code=*l(3,2);
    copy(s(3,3),bklin.naam,fldlen(3,3));
    bklin.bedrag=*d(4,32);
    stu2ram(max_++); if(max_>=max_line) {errnum=11;break;}
  }

  FOREVER{                                                      /* sorteren */
    sw=NO;
    for(k=0;k<max_;k++){
      ram2stu(k);
      zero(str1_,sizeof str1_);grb_deco(str1_,(long *)&bklin.code);
      ram2stu(k+1);
      if(bklin.bedrag){
	zero(str2_,sizeof str2_);grb_deco(str2_,(long *)&bklin.code);
	if(cmp_srt(str1_,str2_,sizeof str1_)==1){
	  ram2stu(k);
	  copy(&bklin.rec4,buf600,sizeof bklin);
	  ram2stu(k+1);
	  stu2ram(k);
	  copy(buf600,&bklin.rec4,sizeof bklin);
	  stu2ram(k+1);
	  sw=YES;
	}
      }
    }
    if(sw==NO) break;
  }
  dspbalans();
  endsr:;
  dt1_open=get_odate(dt1_beg,dt1_end);
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

static killbalans()
{
  if(dt1_open==0) {errnum=14;goto endsr;}
  if(scr_ok("Wenst U echt de openingsbalans te schrappen ???")==YES){
    kill_bew(journl,dt1_beg,dt1_end);
    fasinfo(4,101);fasflush(0);
  }
  endsr:;
  dt1_open=get_odate(dt1_beg,dt1_end);
}

static ins_lin(lin_)
int16 lin_;
{
  int16 k;
								
  for(k=max_line-2;k>=lin_;k--){
    ram2stu(k);
    stu2ram(k+1);
  }
  zero(ram+ram_recl*lin_,ram_recl);
}

static del_lin(lin_)
int16 lin_;
{
  int16 k;
 
  for(k=lin_;k<max_line-1;k++){
    ram2stu(k+1);stu2ram(k);
  }
  zero(ram+ram_recl*(max_line-1),ram_recl);
}

static ram2stu(lin_)
int16 lin_;
{
//  chk_ram(lin_);
//  lin_=lin_%(max_line/dbl_factor);
  copy(ram+(lin_*ram_recl),(char *)&bklin.rec4,ram_recl);
}
						
static stu2ram(lin_)
int16 lin_;
{
  copy((char *)&bklin.rec4,ram+(lin_*ram_recl),ram_recl);
}

static uint16 hash()
{
  char *ps;
  int16 k;
  uint16 fuval=0;
					
  k=hash_len;ps=(char *)&bklin.code;
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
}
 
static dspbalans()
{
  int16 curs=1,j,key,k,z,start_=0,z_base,auto_enter,err_pos_=0,curspos_;
  char *pdum,dumm_[10],*pvar;
  pdum=&dumm_[0];
 
	fasunlck(-1);
  calc_saldo();
  scrnum=0;
  FOREVER{
    redo:
    scrget(1,240);z=1;
    scrifld(z++,fm_odat,&dt1_beg);scrifld(z++,fm_odat,&dt1_end);
    scrifld(z++,fm_odat,&bkh_dt);
    scrifld(z++,fm_od8_2,&tot_saldo);
    scrifld(z++,fm_ou2,&journl);scrifld(z++,fm_ou5,&volgnr);
    z_base=z;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      ram2stu(j);
      j++; scrifld(z++,fm_ou3,&j); j--;
      pvar=ram+(j*ram_recl + ((char *)&bklin.bedrag-(char *)&bklin.rec4));
      scrifld(z++,fm_ud8_2,pvar);
      pvar=ram+(j*ram_recl + ((char *)&bklin.code-(char *)&bklin.rec4));
      auto_enter=YES;if(bklin.code  && bklin.code!=-1 && z!=err_pos_) auto_enter=NO;
      if(auto_enter) {scrifld(-z,fm_ugrb,pvar);z++;}
      else scrifld(z++,fm_ugrb,pvar);
      pvar=ram+(j*ram_recl + ((char *)&bklin.naam[0]-(char *)&bklin.rec4));
      auto_enter=YES;if(bklin.naam[0] && z!=err_pos_) auto_enter=NO;
      if(auto_enter) {scrifld(-z,fm_us30,pvar);z++;}
      else scrifld(z++,fm_us30,pvar);
    }
    key=scrupd(curs,0x7FE);curs=1;curspos_=fldcurs;
    if(key==106){
      if(scr_ok("Wenst U echt de aanpassingen te annuleren ???")==YES) goto endsr;
    }
    auto_enter=NO;err_pos_=0;
    if(key==18){
      auto_enter=YES;
      j=(curspos_-z_base)/4;j+=start_;
      k=(curspos_-z_base)%4;
      ram2stu(j);
      if(k==2 && bklin.code==0 || bklin.code==-1) {curs=curspos_+1;goto redo;}
      if(k==3 && bklin.naam[0]=='\0') {curs=curspos_+1;goto redo;}
    }

    if(key==104){
      j=(curspos_-z_base)/4;j+=start_;
      ins_lin(j);
      curs=curspos_;goto redo;
    }
    if(key==105){
      j=(curspos_-z_base)/4;j+=start_;
      del_lin(j);
      curs=curspos_;goto redo;
    }
    for(k=start_;k<(start_+D_LIN_SCR);k++){
      chk_again:;
      ram2stu(k);
      fasinit(3);*l(3,2)=bklin.code;copy(bklin.naam,s(3,3),fldlen(3,3));
      if((*l(3,2) || *s(3,3)) && hash_val!=hash()){
	if(*l(3,2) && *l(3,2)!=-1){
	  if(search(3,2)){
	    errnum=39;curs=z_base+2+(k-start_)*4;err_pos_=curs;goto redo;
	  }
	}
	else{
	  if(search(3,0)){
	    errnum=39;curs=z_base+3+(k-start_)*4;err_pos_=curs;goto redo;
	  }
	}
	bklin.recnr=*u(3,1);bklin.code=*l(3,2);copy(s(3,3),bklin.naam,fldlen(3,3));
	hash_val=hash();
      }
      else if(*l(3,2)==0 && *s(3,3)=='\0'){
	if(!is_nul(bklin.bedrag)){
	  errnum=38;curs=z_base+2+(k-start_)*4;goto redo;
	}
	else zero((char *)&bklin.rec4,sizeof bklin);
      }
      stu2ram(k);
    }
    calc_saldo();
    if(key==108){
      if(!is_nul(tot_saldo)) errnum=10;
      else{
	if(scr_ok("Wenst U echt deze lijst te boeken ???")==YES) break;
      }
    }
    if(key==18 || auto_enter){ /* automatische bladskip op einde van scherm */
      for(k=0;k<D_LIN_SCR;k++){ram2stu(start_+k);if(bklin.bedrag==0) break;}
      if(k==D_LIN_SCR) key=103;
    }
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){ram2stu(k+start_);if(bklin.code==0) {j=k;break;}}
    curs=z_base+j*4;
  }
  kill_bew(journl,dt1_beg,dt1_end);
  boek_bew();

  endsr:;
}

static kill_bew(jn_,dt_beg_,dt_end_)
int16 jn_;
uint16 dt_beg_,dt_end_;
{
  int16 g;
  long n;

	fasunlck(-2);
  scrget(1,7);scrupd(-3,0);
  fasinit(4);
  n=0;scrnum=0;
  FOREVER{
    next:;
    chg4_1(++n);
    g=fasgeti(4);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
      if(*ps_4_2!=jn_) goto next;
      if(*pu_4_4<dt_beg_ || *pu_4_4>dt_end_) goto next;
      faskill(4);
    }
  }
  fasflush(0);fasunlck(-1);
}

static boek_bew()
{
  int16 k;
  double bd_eur,tot_eur=0;
 
  fasunlck(-2);
	for(k=0;k<max_line;k++){
    ram2stu(k);
    if(!is_nul(bklin.bedrag)){
      bd_eur=valu_cnv("EUR","EUR",bklin.bedrag,(double)0.01);
      tot_eur+=bd_eur;
      initrec(4);
      *u(4,5)=bklin.recnr+60000;
      *l(4,6)=bklin.code;
      *l(4,7)=bd_eur; *d(4,32)=bd_eur;
      *s(4,31)='E';
      copy("Opening",s(4,28),8);
			if(fldlen(4,60)) *u(4,60)=procid;
      errnum=fasadd(4);
      tot_eur+=bd_eur;
    }
  }
  if(!is_nul(tot_eur)){
    initrec(4);
    if(grb_d_fi){
      *u(4,5)=rec_d_fi; *l(4,6)=grb_d_fi;
    }
    else{
      if(tot_eur>0){
	*u(4,5)=rec_d_ak; *l(4,6)=grb_d_ak;
      }
      else {*u(4,5)=rec_d_vk; *l(4,6)=grb_d_vk;}
    }
    *l(4,7)=-tot_eur; *d(4,32)=-tot_eur;
    *s(4,31)='E';
		if(fldlen(4,60)) *u(4,60)=procid;
    errnum=fasadd(4);
  }
  fasflush(0);fasunlck(-1);
}
 
static calc_saldo()
{
  int16 k;

  tot_saldo=0;
 
  for(k=0;k<max_line;k++){
    ram2stu(k);
    tot_saldo+=bklin.bedrag;
  }
  tot_saldo=-tot_saldo;
}
 
static streepje(z)
int16 z;
{
  scrifld(z,fm_os1,"-");
}

static initrec(stu_)
int16 stu_;
{
  fasinit(stu_);
  *s(stu_,2)=journl;
  *u(stu_,3)=volgnr;
  *u(stu_,4)=bkh_dt;
}


static initload()
{
  int16 g,k;

  fasunlck(0);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  if(credt_allow) fileopen(1);
  if(debit_allow) fileopen(2);
  for(k=3;k<=5;k++) fileopen(k);

  journl=0;
  for(k=0;k<80;k++){
    sysget(10240+k*80,4,(char *)&j_tab[k]);
    sysget(10240+20+k*80,22,(char *)&j_tab[k].lastnr);
    sysget(10286+k*80,1,&j_tab[k].mast_munt);
    sysget(10287+k*80,8,&j_tab[k].e_saldo);

    if(j_tab[k].typ==7) zero((char *)&j_tab[k],sizeof j_tab[0]);
    else j_tab[k].recnr=getgrb(j_tab[k].fingrb);
    if(j_tab[k].typ==8) journl=j_tab[k].nr;/* openingsjournaal */
  }
 
  if(journl==0){/* openingsjournaal creeren indien onbestaand */
    journl=99;
    FOREVER{
      for(k=0;k<80;k++) if(j_tab[k].nr==journl) break;
      if(k>=80) break; else journl--;
      if(journl<=0) break;
    }
    if(journl){
      for(k=19;k>=0;k--) if(j_tab[k].nr==0 && j_tab[k].typ==0) break;
      if(k<0){for(k=20;k<80;k++) if(j_tab[k].nr==0 && j_tab[k].typ==0) break;}
      j_tab[k].nr=journl; j_tab[k].typ=8;
      j_tab[k].lastnr=0;j_tab[k].fingrb=0;j_tab[k].e_saldo=0;j_tab[k].mast_munt='E';
      sysput(10240+k*80,4,(char *)&j_tab[k]);
      sysput(10240+4+k*80,15,"Openingsbalans");
      sysput(10240+20+k*80,22,(char *)&j_tab[k].lastnr);
      sysput(10286+k*80,1,&j_tab[k].mast_munt);
      sysput(10287+k*80,8,&j_tab[k].e_saldo);
    }
  }

  for(g=0;g<15;g++){
    sysget(788+g*4,4,&df_grb[g]);
    df_recnr[g]=getgrb(df_grb[g]);
  }

  chk_btoeg=0;
  sysget( 780,4,&levcent);getgrb(levcent);
  sysget( 784,4,&kltcent);getgrb(kltcent);
  chk_btoeg=1;
  sysget(1201,4,&grb_d_ak);
  if(grb_d_ak==0 || grb_d_ak==-1) {errnum=16; ovlexit(-1);}
  rec_d_ak=getgrb(grb_d_ak);
  sysget(1205,4,&grb_d_vk);
  if(grb_d_vk==0 || grb_d_vk==-1) {errnum=16; ovlexit(-1);}
  rec_d_vk=getgrb(grb_d_vk);
  sysget(1209,4,&grb_d_fi);
  if(grb_d_fi==0 || grb_d_fi==-1) {grb_d_fi=0;rec_d_fi=0;}
  else rec_d_fi=getgrb(grb_d_fi);
  if(notfound){
    errnum=notfound;
    scrupd(-1,0x80);
    ovlexit(-1);
  }

  sysget( 294,4,def_munt);
  sysget( 298,2,&vers_298);
  sysget(1008,16,(char *)btwpct);
  sysget(1818,2,&sys1818);
  sysget(1840,2,&sys1840);
  sysget(1850,2,&sys1850);
  sysget(1862,2,&sys1862);
  sysget(1858,2,&last_arc);
	sysget(2300,2,&MinBkhDatum); if(MinBkhDatum<last_arc) MinBkhDatum=last_arc;
  sysget(1866,2,&mnd_strt);
  sysget(1918,2,&sear_stt);
  sysget(2212,4,talen);
  sysget(2222,2,&def_qfak);
  sysget(3876,2,&sys3876);
  len4_0=fldlen(4,0);
  analyt=fldlen(4,11);
 
  ram_recl=sizeof bklin;
	ram=RamBon;
  ram_size=45000;
  if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;zeroL(ram,ram_size);
  max_line=ram_size/ram_recl;
  hash_len=sizeof(bklin.code) + sizeof(bklin.naam);
 
  ps_4_2=s(4,2);
  pu_4_4=u(4,4);
  pu_4_5=u(4,5);
  pl_4_6=l(4,6);
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

static uint16 getgrb(lgrb)
long lgrb;
{
  uint16 retcd=0;

  if(*(char *)&lgrb!=0xFF && *(char *)&lgrb!=0x00 && scrcount<23){
    *l(3,2)=lgrb;
    *u(3,1)=0;
    search(3,2);
    if(errnum){
      if(notfound==0){
	scrget(1,170);
	scrcount=1;
      }
      scrifld(scrcount++,fm_ogrb,&lgrb);
      if(errnum==39) errnum=28;
      notfound=errnum;errnum=0;
    }
    else{
      retcd=*u(3,1)+60000;
    }
  }
  return retcd;
}
 
static double absdoubl(bd_)
double bd_;
{
  if(bd_>=0) return bd_;
  else return -bd_;
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static scraddf(fld,v,h,attr)
int16 fld,v,h,attr;
{
  int16 *pi;
				
  pi = (int16 *)info;
  *(pi+0) = fld;
  *(pi+1) = v;
  *(pi+2) = h;
  *(pi+3) = attr;
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
  parmcall[7]=0x04; // enkel boeken toegestaan
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}