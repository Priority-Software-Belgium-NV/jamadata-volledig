/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0074GetD() {return &zzvw;}

#define ovldat BKH0074dat
#define ovlcod BKH0074cod
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


char ovldat[] = "bkh0074  00:02 17/09/10 (c) Jamadata";  // intrestberekening
 
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define TABSIZ          2000
#define MAXFLD          120
#define flag            uint16
								
static char *types[5]={"","Fact","C.N.","Bet.","Div."};
 
extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];
extern uint16 jamin1[5];

extern char *s();
extern int16 *i();
extern uint16 *u(),dateadd(),datejd();
extern long *l();
extern long val();
static long val4_1();
extern float *f();
extern double *d(),valu_cnv();
static double calc_intr();

static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us100[] = {7,0xC8,100,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_od9_2[] = {6,0x95,9,2,0x70,0};
static char fm_uf2_2[] = {6,0xD4,2,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_udatD[] = {4,0xC0,5,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_u_vv[]  = {15,0xC8,4,0,1,0,'0','9',' ',' ','E','E','-','-',0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_u_KL[]  = {11,0xC8,1,0,1,0,'K','K','L','L',0};
static char fm_u_OV[]  = {11,0xC8,1,0,1,0,'O','O','V','V',0};

static flag chk_btoeg=NO;
static flag sys3876;

static int16 form_dat[8],pr_mode,free=0,prtnr,j_tb[101],stu;
static int16 dg_arr[8],loaded;
static int16 prt2pdf;
static uint16 dt_spil,inq_rec,dt_boek,dt_beg,dt_end,last_arc;
static uint16 ref_yy,ref_jr,ref_vl,ref_nr;
static char ver_term[4],prt_page,verv_str[50],sel_nm[40];
static char b1784,type_fich;
static char def_munt[4],type_lst,buf750[1000];
static flag sear_stt,first,sys1790;
static flag debit_allow=NO,credt_allow=NO,lvcd,klcd;
static float pct_intr;

static int16 selp_stu=0;
static char selp_bf[4][1000],selp_des[40],*selp_fld;
static char taal_i,talen[4];
static flag selp_use,selp_ge,selp_le;
static char *selp_txt[6]={"Ondergrens (>)","Ondergrens (> of =)",
		"Bovengrens (<)","Bovengrens (< of =)",
		"Gelijk","Niet gelijk"};

static struct _st {
  long rec4;
  uint16 jr;
  uint16 vl;
  uint16 ft_date;
  uint16 verv_dt;
  uint16 r_yy;
  uint16 r_jr;
  uint16 r_vl;
  char typ;                                     /* 1=ft, 2=kn, 3=bet, 4=div */
  char status;   /* 0=n.verv/n.vold 1=n.verv/vold 2=verv/n.vold 3=verv/vold */
  char dum;
  double ebedr;
  double intr;
} st[TABSIZ];

								
static char *p_data;
static long *pl_80_1;
									
static char seqo_str[1000];
static char filnam[40],fmt[40];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;

ovlcod(parmval)
int16 parmval;
{
  int16 k,z,key,curs=2;
 
  initload();fasunlck(-1);
  if(parmval){/* automatisch voor 1 klant */
    type_lst='V';
    type_fich='K'; stu=2;
    dt_beg=*u(27,2);dt_end=*u(27,3);inq_rec=*u(27,5);
    prt2pdf=YES;exec_lst(NO);
    ovlexit(-1);
  }
 
  if(type_lst=='\0') type_lst='V';
  if(dt_end==0) dt_end=*u(25,2);if(type_fich=='\0') type_fich='K';
  zero(sel_nm,sizeof sel_nm);
  inq_rec=0;
  FOREVER{
    redo:;
    scrget(1,218);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dt_beg);
    scrifld(z++,fm_udat,&dt_end);
    scrifld(z++,fm_uf2_2,&pct_intr);
/* scrifld(z++,fm_u_KL,&type_fich); */
    scrifld(z++,fm_us40,sel_nm);

    k=0x181; if(sys1790 & 0x10){
      k|=0x200;
      scraddf(z,23,58,8); scrifld(z++,fm_os20," F10 naar TXT-bestand ");
    }
    key=scrupd(curs,k); curs=2;
    if(key==101) break;
    if(key==111) ovlexit(*u(25,4));
    if(dt_beg==0) {curs=2;errnum=38;goto redo;}
    if(dt_beg<=last_arc){errnum=37;curs=2;goto redo;}
    if(dt_end==0) {curs=3;errnum=38;goto redo;}
    if(pct_intr==0) {curs=4;errnum=38;goto redo;}
    if(sel_nm[0]){
      if(type_fich=='L') stu=1; else stu=2;
      copy(sel_nm,s(stu,3),fldlen(stu,3));
      if(search(stu,0)){curs=6;goto redo;}
      copy(s(stu,3),sel_nm,fldlen(stu,3));
      inq_rec=*u(stu,1);
    } else inq_rec=0;
    prt2pdf=NO;if(key==109) {prt2pdf=YES;key=108;}
    if(key==108) exec_lst(NO);
    else if(key==110) exec_lst(YES);
  }
  sysput(1721,4,&pct_intr);
  ovlexit(-1);
}
 
static exec_lst(sif_)
flag sif_;
{
  char type_[5];
  int16 z,j,k,ks,kmode_,kod_;
  uint16 ft_nr,dt_ft,dt_verv,rec_;
  double ft_bd,tot_ftbd,ttot_ftbd,bd_i,tot_i,ttot_i;


  if(type_fich=='L') stu=1; else stu=2;
  selp_use=NO;
  if(inq_rec==0){
    if(selp_ask()) goto endsr;
  }
  kod_=1; if(fldlen(stu,2)) kod_=2;
  if(sif_){
    if(ask_file()==NO) goto endsr;
    scrget(1,6);scrupd(-3,0);
  }
  else{
    scrget(1,7);scrupd(-3,0);
		getsysprNew(3,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) ovlexit(-1);
    free=999;
    prtfld(25,1,25);
    prttext("<t28><b>Intrestberekening ");
#if 0
    if(stu==1) prttext("leveranciers"); else prttext("klanten");
#endif
    prttext("periode : ");prtifld(fm_udat,&dt_beg,-1);
    prttext(" - ");prtifld(fm_udat,&dt_end,-1);
    prttext("<b><t85>(");prtifld(fm_uf2_2,&pct_intr,-1);
    prttext("%)<t97>");prtfld(25,2,-1);prttext("<t120>Blz.<ppp>.");
    prtbuf(1);z=1;
    prttab(z,stu,kod_,1,-1); prttitle(z++,"Code",3);
    prttab(z,stu,3,1,30); prttitle(z++,"Naam",3);
    prtitab(z,fm_os4,type_,3,-1); prttitle(z++,"Type",3);
    prtitab(z,fm_uu5,&ft_nr,1,-1); prttitle(z++,"Nummer",0x13);
    prtitab(z,fm_udat,&dt_ft,1,-1); prttitle(z++,"Datum",0x13);
    prtitab(z,fm_udat,&dt_verv,1,-1); prttitle(z++,"Verv.dat",0x13);
    prtitab(z,fm_od9_2,&ft_bd,1,-1); prttitle(z++,"Bedrag",0x13);
    prtitab(z,fm_od9_2,&bd_i,1,-1); prttitle(z++,"Intrest",0x13);
    prtbuf(3);
    p_pdfname("Intrestberekening",dt_beg,dt_end);
    if(prt2pdf) prttext("\xD0\xCE\xD0");
  }
  free=999;
  ttot_ftbd=0;tot_i=0;ttot_i=0;
  fasinit(stu); *u(stu,1)=inq_rec; if(inq_rec) fasgeti(stu);kmode_=1;
  FOREVER{
    next:;
    if(faskeyi(stu,2,kmode_)) break; kmode_=2;
    if(inq_rec && *u(stu,1)!=inq_rec) break;
    if(selp_tst()==NO) goto next;
    fasinit(4);
    *u(4,5)=*u(stu,1)+30000*(stu-1);
    loaded=0;
    FOREVER{
      next4:;
      ks=faskeyi(4,4,2);
      if(ks || *u(4,5)!=*u(stu,1)+30000*(stu-1)) break;
      if(dt_boek && dt_boek<*u(4,4)) goto next4;
      add_bew();
    }
    compress();/* schrap voldane stukken */
    tab_chk();/* vergelijk met datums en minimum */
    if(loaded){
      tot_ftbd=0;tot_i=0;
      make_vstr();
      for(k=0;k<loaded;k++){
	fasinit(4);chg4_1(st[k].rec4);fasgeti(4);
	dt_ft=st[k].ft_date;ft_nr=st[k].vl;bd_i=st[k].intr;
	zero(type_,sizeof type_);copy(types[st[k].typ],type_,4);
	dt_verv=st[k].verv_dt;
	ft_bd=st[k].ebedr;
	if(sif_){
	  zero(seqo_str,sizeof seqo_str);pos=0;
	  seqo_fld(stu,kod_);
	  seqo_fld(stu,3);
	  seqo_var(fm_os30,verv_str);
	  seqo_var(fm_os4,type_);
	  seqo_var(fm_uu5,&ft_nr);
	  seqo_var(fm_udat,&dt_ft);
	  seqo_var(fm_udat,&dt_verv);
	  seqo_var(fm_od9_2,&ft_bd);
	  if(type_lst=='V' && type_fich=='K' && fldlen(4,30)){
	    seqo_fld(4,30);
	  }
	  else{
	    seqo_fld(4,28);
	  }
	  CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
	  seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
/* dumpen */
	  seqo_len=0;
	  for(j=0;j<pos;j+=280){
	    if((j+280)>pos) seqo_len=pos-j;
	    else seqo_len=280;
	    copy(&seqo_str[j],s(80,1)+4,seqo_len);
	    seqo_flush();
	  }
	}
	else{
	  if(k==0) for(j=1;j<3;j++) prtinfo(j,0);
	  for(j=3;j<20;j++) prtinfo(j,0);nextline();
	}
	tot_ftbd+=ft_bd;tot_i+=bd_i;
      }
      if(sif_==NO) nextline();
      rec_=*u(stu,1);
      zero(verv_str,sizeof verv_str); fasinit(4);
      fasinit(stu);copy("Totaal ==>",s(stu,3),11);
      dt_ft=0;ft_nr=0;type_[0]='\0';dt_verv=0;
      ft_bd=tot_ftbd;bd_i=tot_i;
      if(sif_==NO){
	for(k=0;k<20;k++) prtinfo(k,2);nextline();nextline();
      }
      ttot_ftbd+=tot_ftbd;  ttot_i+=tot_i;
      *u(stu,1)=rec_;fasgeti(stu);
    }
    if(free==-1) break;
  }
  zero(verv_str,sizeof verv_str); fasinit(4);
  fasinit(stu);copy("Totaal lijst ==>",s(stu,3),20);
  dt_ft=0;ft_nr=0;type_[0]='\0';dt_verv=0;
  ft_bd=ttot_ftbd;
  if(sif_==NO){
    for(k=0;k<20;k++) prtinfo(k,2);nextline();nextline();
    prtform(0);
    prtclose();
  }
  else {fasflush(0);fasclos(-2);}
  endsr:;
}

static make_vstr()
{
  int16 g,j,k;
  char term_[4];

  copy(s(stu,13),term_,3); term_[3]='\0';
  g=0;
  for(k=0;k<3;k++){
    if(term_[k]=='\0') break;
    if(term_[k]=='E') {g=1;break;}
    if(term_[k]>='0' && term_[k]<='9') {g=2;break;}
  }
  zero(verv_str,sizeof verv_str);
  switch(g){
    case 1 : j=val(&term_[k+1]);j*=30;
	     if(j){
	       stcli_d(verv_str,(long)j,3,1);
	       copy(" dagen einde maand",&verv_str[3],18);
	     }
	     else {
	       copy("einde maand na ft.datum",verv_str,23);
	     }
	     break;
    case 2 : j=val(&term_[k]);
	     stcli_d(verv_str,(long)j,3,1);
	     copy(" dagen na ft.datum",&verv_str[3],18);
	     break;
    default: copy("Contant",verv_str,7);break;
  }
}

static add_bew()
{
  int16 k,typ,kill_;
  char *pa;

  if(loaded==TABSIZ) compress();
  if(loaded==TABSIZ) goto endsr;
  if(is_oud_stuk(val4_1())) goto endsr;/* voldaan voor deze periode */

  pa=(char *)&st[loaded];/* dit element volledig op 0 zetten */
  for(k=0;k<sizeof(struct _st);k++) *pa++='\0';

  st[loaded].rec4=val4_1();
  st[loaded].jr=*s(4,2);
  st[loaded].vl=*u(4,3);
  st[loaded].ft_date=*u(4,4);
  st[loaded].ebedr=*d(4,32);
  if(stu!=2){
    st[loaded].ebedr=-st[loaded].ebedr;
  }
  st[loaded].r_yy=*s(4,8);
  st[loaded].r_jr=*s(4,9);
  st[loaded].r_vl=*u(4,10);
  k=j_tb[st[loaded].jr];
  if(k<3 || k>8){
    if(st[loaded].ebedr<0) typ=2; else typ=1;
    if(*u(4,20)) st[loaded].ft_date=*u(4,20);
    st[loaded].verv_dt=*u(4,21);
    if(st[loaded].verv_dt==0){
      copy(s(2,13),ver_term,4);
      ver_term[3]='\0';
      st[loaded].verv_dt=dateadd(st[loaded].ft_date,ver_term);
    }
  }
  else if(k<5) typ=3;
  else typ=4;
  st[loaded].typ=typ;
  if(typ!=1) st[loaded].verv_dt=st[loaded].ft_date;/* CN/bet */
  kill_=NO;
  if(st[loaded].verv_dt>dt_end) kill_=YES;
  if(st[loaded].ft_date>dt_end) kill_=YES;
  if(kill_) zero((char *)&st[loaded].rec4,sizeof st[0]);
  else{
    st[loaded].intr=calc_intr(st[loaded].ebedr,st[loaded].verv_dt);
    loaded++;
  }
  endsr:;
}

static is_oud_stuk(rec4_)
long rec4_;
{
  int16 mode_,ret_val_,k;
  uint16 lkg_rec_,ref_jr_,ref_jn_,ref_vl_,dt_v_;
  double bd_;
									
  ret_val_=NO;
  copy(s(4,1),buf750,fldlen(4,0));
/*  fasinit(4);*u(4,1)=rec4_;fasgeti(4); */
  if(*s(4,8)==0 && *s(4,9)==0 && *u(4,10)==0) goto endsr;
  ref_jr_=*s(4,8);ref_jn_=*s(4,9);ref_vl_=*u(4,10);lkg_rec_=*u(4,5);
  fasinit(4);*u(4,5)=lkg_rec_;*s(4,8)=ref_jr_;*s(4,9)=ref_jn_;*u(4,10)=ref_vl_;
  bd_=0;mode_=1;
  FOREVER{
    if(faskeyi(4,4,mode_)) break; mode_=2;
    if(*u(4,5)!=lkg_rec_) break;
    if(*s(4,8)!=ref_jr_ || *s(4,9)!=ref_jn_ || *u(4,10)!=ref_vl_) break;

/*  bd_=-*d(4,32); */
    k=j_tb[*s(4,2)];
    dt_v_=0;
    if(k<3 || k>8 && bd_>0) dt_v_=*u(4,21);
    if(dt_v_==0) dt_v_=*u(4,4);
    if(dt_v_>=dt_beg) goto endsr;
    bd_+=*d(4,32);
  }
  if(is_nul(bd_)) ret_val_=YES;
  endsr:;
  copy(buf750,s(4,1),fldlen(4,0));
/*  fasinit(4);*u(4,1)=rec4_;fasgeti(4); */
  return ret_val_;
}

static double calc_intr(bd_,dt_verv_)
double bd_;
uint16 dt_verv_;
{
  float pct_,q_dagen;
  double bdi_;
							
  if(dt_verv_<dt_beg) dt_verv_=dt_beg-1;
  bdi_=0;  pct_=pct_intr;
  if(pct_==0) goto endsr;
  q_dagen=dt_end-dt_verv_;
  bdi_=bd_*(pct_*(q_dagen/365.))/100.;
  endsr:;
  bdi_=valu_cnv("EUR","EUR",bdi_,(double)0.01);
  return (double)bdi_;
}

static compress()
{
  int16 k,n;
  double ebedrag,bd_i;

  for(k=0;k<loaded;k++){
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
    bd_i=0; ebedrag=0;
    n=k-1;
    FOREVER{
      n++;
      if(n>=loaded) break;
      if(st[n].r_yy!=ref_yy || st[n].r_jr!=ref_jr || st[n].r_vl!=ref_vl) break;
      bd_i+=st[n].intr; ebedrag+=st[n].ebedr;
    }
    if(bd_i<=0 && is_nul(ebedrag)){
      FOREVER{/* schrap voldane */
	if(k==loaded) break;
	if(st[k].r_yy!=ref_yy || st[k].r_jr!=ref_jr || st[k].r_vl!=ref_vl) break;
	del_line(k);
      }
      k--;
    }
    else{
      k=n-1;
    }
  }
  endsr:;
}

static tab_chk()
{
  int16 g,k,n,vervallen;
/* controle op vervaldatums */
  if(loaded==0){loaded=0;goto endsr;}

/* duidt vervallen stukken aan */
  for(k=0;k<loaded;k++){
    ref_yy=st[k].r_yy;ref_jr=st[k].r_jr;ref_vl=st[k].r_vl;
    vervallen=0;
    n=k-1;
    FOREVER{
      n++;
      if(n>=loaded) break;
      if(st[n].r_yy!=ref_yy || st[n].r_jr!=ref_jr || st[n].r_vl!=ref_vl) break;
      if(st[n].verv_dt<=dt_spil) vervallen=1;
    }
    if(vervallen){
      for(g=k;g<n;g++){
	st[g].status+=2;
      }
    }
    k=n-1;
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

static ask_file()
{
  int16 z=1,key;

  if(type_fich=='K') copy("KLT-",filnam,4);
  else copy("LEV-",filnam,4);
  if(type_lst=='V') copy("VERV.TXT",&filnam[4],8);
  else copy("OPEN.TXT",&filnam[4],8);
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,4,12,1);
  scraddf(z++,10,7,0); scraddf(z++,10,27,2);
  scraddf(z++,23,1,8);scraddf(z++,23,15,8);
  FOREVER{
    redo:;
    z=1;
    scrifld(z++,fm_os63,"Uitschrijven gegevens naar TXT-bestand");
    scrifld(z++,fm_os63,"Naam TXT-bestand : ");
    scrifld(z++,fm_us30,filnam);
    scrifld(z++,fm_os13," F1 Stop");scrifld(z++,fm_os13," F8 neem aan");
    key=scrupd(1,0x81);
    if(key==101) return NO;
    if(key==108) break;
  }
  fasclos(-2);errnum=fasopen(filnam,2);if(errnum) return NO;
  fasinit(80);seqo_pos=0;seqo_mode=2;
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
    while(seqo_str[pos]==' ') seqo_str[pos--]='\0';/* delete trailing blanks */
    pos++;
  }
  seqo_str[pos++]=0x09;
}

static flt2str(bd_)
float bd_;
{
  double bedrag_,add_=0;
  long val_;
								
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*100+add_;value=val_/100;
  val2str(0);
  value=val_-value*100;
  if(value){
    seqo_str[pos++]='.';
    if(value<0) value=-value;val2str(1);
  }
}

static val2str(mode_)
int16 mode_;
{
  int16 k;
  char buff[15];

  zero(buff,sizeof buff);
  if(mode_==0){
    stcli_d(&buff[0],value,10,1);
    for(k=0;k<10;k++){
      if(buff[k]=='\0') break;
      if(buff[k]!=' ') seqo_str[pos++]=buff[k];
    }
  }
  else{
    if(value<0) value=-value;
    stcli_d(&buff[0],value,2,0);
    for(k=1;k>=0;k--) if(buff[k]!='0') break;
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
 
static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static nextline()
{
  free=prtline();
}

static initload()
{
  int16 g,k;

  fasunlck(0);
 
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  fileopen(1);
  fileopen(2);
  fileopen(3);
  fileopen(4);

  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

  for(k=0;k<80;k++){
    sysget(10240+k*80,2,&g);
    sysget(10242+k*80,2,&j_tb[g]);
  }
			
 			
  sysget( 294,3,def_munt);
  sysget(1721,4,&pct_intr);
  sysget(1790,2,&sys1790);
  sysget(1858,2,&last_arc);
  sysget(1918,2,&sear_stt);
  sysget(2212,4,talen);
  sysget(3876,2,&sys3876);
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
  int16 k,curs,z,curs_taal;
 
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
    for(k=3;k<24;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,24);
    for(k=25;k<MAXFLD;k++) scrfld(z++,stu,k);
    scrupd(curs,0x0080);
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
  for(k=2;k<MAXFLD;k++){
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

