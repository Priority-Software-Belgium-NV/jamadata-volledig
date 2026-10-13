/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0217GetD() {return &zzvw;}

#define ovldat DRK0217dat
#define ovlcod DRK0217cod
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

char ovldat[] = "drk0217  00:01 17/09/10 (c) Jamadata";
/* menu klantenrapporten */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DUM     0
#define MAXRL           500
#define LEN_PTR         2+4+4+4
#define flag            uint16
#define MAXFLD          100
#define DIMBTW          8
#define Q_SCR           300


extern int16 retcall,parmcall[8];
extern int16 ilength;
extern uint16 procid,onext;
extern char info[];
extern uint16 jamin1[5];

extern char *s();
extern int16 *i();
extern uint16 *u();
extern uint16 datejd();
extern long *l();
extern long val();
extern float *f();
extern double *d(),valu_cnv();
static double round();

static int16 free;

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_odsp[]  = {7,0x88,79,0,0,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os25[]  = {7,0x88,25,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us5[]   = {7,0xC8,5,0,0,0,0};
static char fm_us1U[]  = {7,0xC8,1,0,1,0,0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf3_1[] = {6,0xD4,3,1,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_od5_4[] = {6,0x95,5,4,0x70,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,1,0,'A','A','N','N',0};
static char fm_uHV[]   = {11,0xC8,1,0,1,0,'H','H','V','V',0};
static char fm_uDMJ[]  = {13,0xC8,1,0,1,0,'D','D','M','M','J','J',0};
static char fm_uAVOW[]  = {13,0xC8,1,0,1,0,'A','A','O','O','V','W',0};
static char fm_u_ALN[]= {13,0xC8,1,0,0x09,0,'A','A','L','L','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
 
static char *mnd_str[12]={"jan","feb","maa","apr","mei","jun","jul","aug","sep","okt","nov","dec"};
/* de variabelen */
static char *p_data;
static long *pl_80_1;

static char filnam[100],fmt_qlv[40],fmt_bdr[40];
static char fmt[40],skip_leegg;
static uint16 dat_beg,dat_end,dat_vbeg,dat_vend;
static uint16 inq_grp,fkey;
static char def_munt[4],soort_waarde,inq_ktype,groep_grafiek;
static int16 form_dat[8],prtnr,prmode,new_DB;
static int16 kdsp,kdsp_off=1;
static long inq_klt,inq_art,inq_lev,inq_ftnr;
static flag lvcd,klcd,chk_btoeg=NO,sear_stt,sys3876;
static char disp_str[55],sta_hoofd[80];
 
static int16 sys2723,sys4397;
static uint16 *pu_2_1,*pu_6_1;
static int16 *pi;
static int16 FormdatA4[8]={2480,3508,0,118,118,118,118,4};
static int16 date2str();
static struct {
	char Prijsafspraken;
	char Facturenlijst;
	char Vervallenlijst;
	char Statistieken;
	char Herafdrukfacturen;
} OpRapport={'J','J','J','J','N'};

ovlcod()
{
  initload();
  FOREVER{
redo:
		fasunlck(0);
    if(ask_sel("Rapport klant",1)) break;
    scrget(1,7);scrupd(-3,0);
		fasunlck(-1);
    *u(27,2)=dat_beg;*u(27,3)=dat_end;*s(27,4)='K';*u(27,5)=*u(2,1);
    openrapport();
		if(OpRapport.Prijsafspraken=='J'){tussenblad("Prijsafspraken");ovlcall(230,1);}
		if(OpRapport.Statistieken=='J'){ tussenblad("Statistieken"); ovlcall(239,1);}
		if(OpRapport.Facturenlijst=='J'){tussenblad("Facturenlijst"); ovlcall(79,1);}
		if(OpRapport.Vervallenlijst=='J'){tussenblad("Intrestberekening"); ovlcall(74,1);}
		if(OpRapport.Herafdrukfacturen=='J'){tussenblad("Kopie facturen"); ovlcall(257,1);}
    closerapport();

  }
}

static tussenblad(txt_)
char *txt_;
{
  getsysprNew(5,form_dat,&prmode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,FormdatA4,6,80,prmode,3))!=0) ovlexit(10);
  prt_string("\x1B&f1S\x1B&f0S\x1B*p+1000x*p+200Y\x1B(s1p(s20v0s3B");
  prt_string(s(25,1));
  prt_string("\x1B&f1S\x1B&f0S\x1B*p+400x*p+1500Y\x1B(s1p(s50v0s3B");
  prt_string(txt_);
  prtline();
  prtform(0);
  prtclose();
}
 
static openrapport()
{
  uint16 j,yy, mm, dd;
  int16 slen_;
  char str_[100];

  getsysprNew(5,form_dat,&prmode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,FormdatA4,6,80,prmode,3))!=0) ovlexit(10);
	p_pdfname(s(2,3),*u(27,2),*u(27,3));
//  prttext("\xD0\xCE\xD0");
  prttext("\xD0\xCD\xD0");
  prtline();
  prt_string("\x1B&f1S\x1B&f0S\x1B*p+1000x*p+200Y\x1B(s1p(s20v0s3B");
  prt_string(s(25,1));
  prt_string("\x1B&f1S\x1B&f0S\x1B*p+100x*p+1000Y\x1B(s1p(s25v0s3B");
  zero(str_,sizeof str_);/* 1-ste omschrijving */
  copy0(s(2,3),str_,fldlen(2,3));
  prt_string(str_);
  prt_string("\x1B&f1S\x1B&f0S\x1B*p+100x*p+1100Y\x1B(s1p(s25v0s3B");
  zero(str_,sizeof str_);/* 1-ste omschrijving */
  copy0(s(2,4),str_,fldlen(2,4));
  prt_string(str_);
  prt_string("\x1B&f1S\x1B&f0S\x1B*p+100x*p+1200Y\x1B(s1p(s25v0s3B");
  zero(str_,sizeof str_);
  j=copy0(s(2,5),str_,fldlen(2,5));
  j+=copy0("  ",&str_[j],2);
  j+=copy0(s(2,6),&str_[j],fldlen(2,6));
  prt_string(str_);
  zero(str_,sizeof str_);
  slen_=0;
  jddate(*u(27,2),&yy,&mm,&dd);yy%=100;
  stcli_d(&str_[slen_],(long)dd,2,0);str_[slen_+2]='/';slen_+=3;
  stcli_d(&str_[slen_],(long)mm,2,0);str_[slen_+2]='/';slen_+=3;
  stcli_d(&str_[slen_],(long)yy,2,0);slen_+=2;
  copy("  -  ",&str_[slen_],5);slen_+=5;
  jddate(*u(27,3),&yy,&mm,&dd);yy%=100;
  stcli_d(&str_[slen_],(long)dd,2,0);str_[slen_+2]='/';slen_+=3;
  stcli_d(&str_[slen_],(long)mm,2,0);str_[slen_+2]='/';slen_+=3;
  stcli_d(&str_[slen_],(long)yy,2,0);slen_+=2;
  prt_string("\x1B&f1S\x1B&f0S\x1B*p+100x*p+2000Y\x1B(s1p(s60v0s3B");
  prt_string(str_);
  prtline();
  prtform(0);
  prtclose();
}

static closerapport()
{
  getsysprNew(5,form_dat,&prmode,&prtnr);PrintPaperNr=0;
  if((errnum=prtopen(prtnr,FormdatA4,6,80,prmode,3))!=0) ovlexit(10);
//  prttext("\xD0\xCE\xD0");
  prttext("\xD0\xCC\xD0");
  prtline();
  prtform(0);
  prtclose();
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

static ask_sel(ptitel,sel_mode_)/* 0=klt/art/ft 1=klt/art 2=geen */
char *ptitel;
int16 sel_mode_;
{
  int16 key,z,curs=1;
 
  if(skip_leegg=='\0') skip_leegg='J';
  fasinit(1); if(inq_lev){*u(1,1)=inq_lev;fasgeti(1);}
  fasinit(2); if(inq_klt){*u(2,1)=inq_klt;fasgeti(2);}
  fasinit(6); if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
	
  FOREVER{
    redo:;
    scrget(2,319);z=1;
		DisplayMenuTitel(1,ptitel,0x3);z++;
    //scrifld(z++,fm_os38,ptitel);
    scrifld(z++,fm_udat,&dat_beg);
    scrifld(z++,fm_udat,&dat_end);
    scrfld(z++,2,3);
		if(ovltest(230)) scrifld(z++,fm_uJN,&OpRapport.Prijsafspraken);else{OpRapport.Prijsafspraken='N'; z++;}
		if(ovltest(239)) scrifld(z++,fm_uJN,&OpRapport.Statistieken);else{OpRapport.Statistieken='N'; z++;}
		if(ovltest(79)) scrifld(z++,fm_uJN,&OpRapport.Facturenlijst);else{OpRapport.Facturenlijst='N'; z++;}
		if(ovltest(74)) scrifld(z++,fm_uJN,&OpRapport.Vervallenlijst); else{OpRapport.Vervallenlijst='N'; z++;}
		if(ovltest(257)) scrifld(z++,fm_uJN,&OpRapport.Herafdrukfacturen); else{OpRapport.Herafdrukfacturen='N'; z++;}
    key=scrupd(curs,0x81);curs=1;
    if(key==101) return YES;
    if(dat_beg==0) {errnum=34;curs=2;goto redo;}
    if(dat_end<dat_beg) {curs=3;errnum=34;goto redo;}
    if(*s(2,3)){
      if(search(2,0)){curs=4;goto redo;}
    } else fasinit(2);
    inq_klt=*u(2,1);
    if(*s(6,3)){
      if(search(6,0)){curs=5;goto redo;}
    } else fasinit(6);
    inq_art=*u(6,1);
    if(*s(1,3)){
      if(search(1,0)){curs=6;goto redo;}
    } else fasinit(1);
    inq_lev=*u(1,1);
    if(sel_mode_==YES && inq_klt==0 && inq_art==0) {errnum=34;curs=4;goto redo;}
    if(sel_mode_==NO && inq_klt==0 && inq_art==0 && inq_ftnr==0) {errnum=34;curs=4;goto redo;}
    if(key!=108) goto redo;
    break;
  }
  endsr:;
  return NO;
}

static int16 date2str(str_,date_,no_delim_)
char *str_;
uint16 date_,no_delim_;
{
  int16 dd,mm,jj,len_=0;
 
  if(date_==0) goto endsr;
  jddate(date_,&jj,&mm,&dd);
  stcli_d(&str_[len_],(long)dd,2,0);len_+=2;if(!no_delim_) str_[len_++]='/';
  stcli_d(&str_[len_],(long)mm,2,0);len_+=2;if(!no_delim_) str_[len_++]='/';
  stcli_d(&str_[len_],(long)jj,4,0);len_+=4;
  endsr:;
  return len_;
}

static copy_0(ps,pd,len)
char *ps,*pd;
int16 len;
{
  int16 k;
 
  for(k=0;k<len;k++) if(*(ps+k)=='\0') break;
  copy(ps,pd,k);
  return k;
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



static initload()
{

  char *pdum_;
 
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(13);
			
  sysget(294,4,def_munt);
  sysget(2723,2,&sys2723);
  sysget(4397,2,&sys4397);
  fieldspc(16,30,&pdum_,fmt_qlv);
  fieldspc(16,31,&pdum_,fmt_bdr);
  fasinit(80);fasinfo(80,207);
  new_DB=NO; if(*l(80,1)) new_DB=YES;

  pu_2_1=u(2,1);
  pu_6_1=u(6,1);

  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

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

static double round(bd_)
double bd_;
{
  double bdr_;

  bdr_=valu_cnv("EUR","EUR",bd_,(double)0.01);
  return (double)bdr_;
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
 
static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os1,"-");
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
