/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0298GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0298dat
#define ovlcod DRK0298cod
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

char ovldat[] = "drk0298  00:01 25/11/10 (c) Jamadata";
/* Uitschrijven bestellijst voor PDA (V.1.K) */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define MAXFLD          100
#define MAXXMLLEN       (long)(175000)
#define flag            uint16

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us75[]  = {7,0xC8,75,0,0,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_of6_2[] = {6,0x94,6,2,0x30,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_AM[]    = {11,0xC8,1,0,0x09,0,'A','A','M','M',0};
static char fm_uONA[] = {13,0xC8,1,0,1,0,'A','A','N','N','O','O',0};
 
static int16 free,stu=6,mode,taal_nr;
static int16 max_loc;
static int16 def_taal;
static int16 form_dat[8],pr_mode,prtnr;
static uint16 dt_inv,cnt;
static uint16 inq_loc,sys4408;
static char fmt[40],vptekst[100],oldnm[50],def_munt[4];
static char bew_only,add_bstk,sel_beweg;
static char nm_fil[6],nm_loc[10][6],stuksprx[10];
static flag chk_btoeg=NO,klcd,lvcd,arcd=NO;
static flag sear_stt;
static flag kont_exist;

/* de seqo-variabelen */
							
static char *p_data;
static long *pl_80_1;
									
static char seqo_str[1000];
static char filnam[40];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;

static uint16 *pu_6_1,*pu_2_1;

ovlcod()
{
  initload();
  out_bstlst();
  ovlexit(-1);
}

static out_bstlst()
{
  int16 key,curs=1,k,z,dd,mm,jj,key_mode,keynr,mode_,chk_mag_;
  int16 firsttime_,lmode_,use_lev_,only_alf_=NO;
  uint16 n;
  char choice='M',only_min,prt_verk,dump_ALL_lev,str_[10];
  float q_stock,q_bons,qlv_;
 
  jddate(*u(25,2),&jj,&mm,&dd); mm--;
  if(add_bstk=='\0') add_bstk='N';
  if(fldlen(60,1)) prt_verk='J'; else prt_verk='N';
  if(faskeyi(6,6,0)==45) {only_alf_=YES;choice='A';}
  only_min='N';fasinit(1);dump_ALL_lev='J';
  FOREVER{
    redo:
    scrget(2,280);z=1;
    scrfld(z++,25,1);
    if(only_alf_) scrifld(z++,fm_os1,&choice);
    else scrifld(z++,fm_AM,&choice);
		scrifld(z++,fm_uJN,&dump_ALL_lev);
    if(fldlen(8,1)) scrifld(z++,fm_uONA,&add_bstk); else streepje(z++);
    scrifld(z++,fm_uJN,&only_min);
    key=scrupd(curs,0x0481);curs=1;
    if(key==101) goto endsr;
    if(key==111) ovlexit(-1);
    if(key==108){
      switch(choice){
				case 'M' : keynr=6;break;
				case 'A' : keynr=2;break;
				default : keynr=1;break;
      }
      break;
    }
  }
  seldata.selp_use=NO;
  if(ovlcall(2215,3)) goto endsr;
  scrget(1,6);scrupd(-3,0);
  mk_name(3902,"PdaBsLst.dat");
  errnum=fasopen(filnam,2);if(errnum) goto endsr;
  fasinit(80);seqo_pos=0;seqo_mode=2;pos=0;
  copy("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>",&seqo_str[pos],43);pos+=43;
  seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
  copy("<BESTELLIJST>",&seqo_str[pos],13);pos+=13;
  seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
  cnt=0;
  fasinit(1);lmode_=1;
  FOREVER{
next_l:;
		if(dump_ALL_lev=='J'){
			fasinit(1);copy("Alle artikels",s(1,3),20);
		}
		else{
			if(faskeyi(1,2,lmode_)) break; lmode_=2;
			if(seqo_pos>=MAXXMLLEN) {errnum=11;break;}
			for(k=0;k<seldata.p_max_lev;k++) if(*u(1,1)==seldata.tb[k].rec) break;
			if(k>=seldata.p_max_lev || seldata.tb[k].select!='J') goto next_l;
			scrget(1,170);scrfld(10,1,3);scrupd(-3,0);
			use_lev_=NO;
			fasinit(6);*u(6,7)=*u(1,1);
			n=faskeyi(6,4,1); if(n==0 && *u(1,1)==*u(6,7)) use_lev_=YES;
			if(fldlen(11,1) && use_lev_==NO){
				fasinit(11);*u(11,2)=*u(1,1);
				n=faskeyi(11,1,1); if(n==0 && *u(1,1)==*u(11,2)) use_lev_=YES;
			}
			if(use_lev_==NO) goto next_l;
		}
		chk_mag_=0; if(keynr==6) chk_mag_=1;firsttime_=YES;
redo_artikels:;
    fasinit(6); key_mode=1;
		if(dump_ALL_lev!='J' && chk_mag_==1) *s(6,29)='0'; // eerst de ingevulde overlopen en dan de lege
    while(free>=0){
      next_a:;
      if(faskeyi(6,keynr,key_mode)) break; key_mode=2;
			if(dump_ALL_lev!='J' && chk_mag_==1 && *s(6,29)=='\0') goto next_a; // mag NIET leeg zijn
			if(chk_mag_==2 && *s(6,29)) goto next_a; // MOET leeg zijn 
      if(seqo_pos>=MAXXMLLEN) {errnum=11;break;}
      if(*i(6,9)==99) goto next_a;
      if(fldlen(6,35) && *f(6,35)<0) goto next_a;
      if(DirCall_DRK2215_SelectArtikel()==NO) goto next_a;
      if(dump_ALL_lev!='J'){
				if(*u(6,7)!=*u(1,1)){
					if(fldlen(11,1)){
						fasinit(11);*u(11,2)=*u(1,1); *u(11,3)=*u(6,1);
						if(faskeyi(11,1,1)) goto next_a;
						if(*u(11,2)!=*u(1,1) || *u(11,3)!=*u(6,1)) goto next_a;
					} else goto next_a;
				}
			}
      q_bons=0;
      if(fldlen(8,1) && (add_bstk=='O' || add_bstk=='A')){
				fasinit(58);*u(58,14)=*pu_6_1;mode_=1;
				FOREVER{
					next58:;
					if(faskeyi(58,2,mode_)) break; mode_=2;
					if(*u(58,14)!=*pu_6_1) break;
					fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
					if(fldlen(8,36) && *u(8,36)) goto next58;
					qlv_=*f(58,31);
					if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
					q_bons+=qlv_;
				}
      }
      if(add_bstk=='A') q_stock=*f(6,33)-q_bons; else q_stock=*f(6,33)+q_bons;
      if(only_min=='J' && q_stock>=*f(6,36)) goto next_a;
      if(firsttime_){
				copy("<LEV>",&seqo_str[pos],5);pos+=5;
				seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
				dmpxmlstr("NAAM",s(1,3),30);
				seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
				firsttime_=NO;
      }
      copy("<ART>",&seqo_str[pos],5);pos+=5;
			if(sys4408){
				zero(str_,sizeof str_); stcli_d(str_,(long)(*u(6,1)),5,0);  copy(str_,s(6,2),fldlen(6,2));
        dmpxmlstr("PLU",s(6,2),fldlen(6,2));
				fasgeti(6);
			} else dmpxmlstr("PLU",s(6,2),fldlen(6,2));
      dmpxmlstr("MAG",s(6,29),fldlen(6,29));
      dmpxmlstr("EH",s(6,10),fldlen(6,10));
      dmpxmlflt("Mstk",*f(6,36));
      dmpxmlflt("Nstk",*f(6,35));
      dmpxmlflt("Astk",*f(6,33));
      dmpxmlflt("Bstk",q_bons);
      dmpxmlflt("STK",q_stock);
      copy("</ART>",&seqo_str[pos],6);pos+=6;
      seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
      seqo_len=0;CnvJamaChar(seqo_str,pos,0);
      for(k=0;k<pos;k+=280){
				if((k+280)>pos) seqo_len=pos-k;
				else seqo_len=280;
				copy(&seqo_str[k],s(80,1)+4,seqo_len);
				seqo_flush();
      }
      pos=0;
    }
		if(dump_ALL_lev!='J' && chk_mag_==1){chk_mag_=2;goto redo_artikels;} // nu de lege gaan doen
    if(firsttime_==NO){
      copy("</LEV>",&seqo_str[pos],6);pos+=6;
      seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
    }
		if(dump_ALL_lev=='J'){
			fasinit(1);dump_ALL_lev='N';
		}
  }
  copy("</BESTELLIJST>",&seqo_str[pos],14);pos+=14;
  seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
  seqo_len=0;CnvJamaChar(seqo_str,pos,0);
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
    seqo_flush();
  }
  pos=0;
  fasclos(-2);
  endsr:;
}

static dmpxmlstr(xname_,ps_,maxlen_)
char *xname_,*ps_;
int16 maxlen_;
{
  int16 k,len_,slen_;

  for(len_=0;len_<15;len_++) if(xname_[len_]=='\0') break;
  for(slen_=0;slen_<maxlen_;slen_++) if(ps_[slen_]!=' ') break;
  if(slen_){ps_+=slen_;maxlen_-=slen_;}/* delete leading blanks */
  for(slen_=0;slen_<maxlen_;slen_++) if(ps_[slen_]=='\0') break;
  if(slen_==0){/* lege string */
    seqo_str[pos++]='<';copy(xname_,&seqo_str[pos],len_);pos+=len_;
    copy("/>",&seqo_str[pos],2);pos+=2;
  }
  else{
    seqo_str[pos++]='<';copy(xname_,&seqo_str[pos],len_);pos+=len_;seqo_str[pos++]='>';
    copy(ps_,&seqo_str[pos],slen_);
    for(k=0;k<slen_;k++){
      if(seqo_str[pos+k]=='<') seqo_str[pos+k]=' ';
      if(seqo_str[pos+k]=='>') seqo_str[pos+k]=' ';
      if(seqo_str[pos+k]=='&') seqo_str[pos+k]=' ';
    }
    pos+=slen_;
    copy("</",&seqo_str[pos],2);pos+=2;copy(xname_,&seqo_str[pos],len_);pos+=len_;seqo_str[pos++]='>';
  }
}

static dmpxmlflt(xname_,fbd_)
char *xname_;
float fbd_;
{
  int16 len_;

  for(len_=0;len_<15;len_++) if(xname_[len_]=='\0') break;
  if(fbd_==0){/* lege string */
    seqo_str[pos++]='<';copy(xname_,&seqo_str[pos],len_);pos+=len_;
    copy("/>",&seqo_str[pos],2);pos+=2;
  }
  else{
    seqo_str[pos++]='<';copy(xname_,&seqo_str[pos],len_);pos+=len_;seqo_str[pos++]='>';
    flt2str(fbd_);
    copy("</",&seqo_str[pos],2);pos+=2;copy(xname_,&seqo_str[pos],len_);pos+=len_;seqo_str[pos++]='>';
  }
}

static mk_name(adr_pref,ps)
uint16 adr_pref;
char *ps;
{
  char *pd;
				
  pd=filnam;
  sysget(adr_pref,16,pd);
  while(*pd) pd++;
  while(*ps!='\0') *pd++=*ps++;
}

static stock2stks(stock_,qst_,bak_,fls_)
float stock_,qst_,*bak_;
char *fls_;
{
  long stk_;
	float add_;
						
  zero(fls_,5);
  if(qst_<1) qst_=1;
  *bak_=(long)(stock_); stk_=0;
	add_=0.49; if(stock_<0) add_=-0.49;
  if(qst_>1 && stock_!=0){
    stk_=(long)(((stock_- *bak_) * qst_)+add_);
  } else stk_=0;
  if(stk_) *fls_='/'; stcli_d(fls_+1,stk_,2,1);
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

  sysget( 294,3,def_munt);
  sysget(1918,2,&sear_stt);
  sysget(2770,60,(char *)&nm_loc[0][0]);
	for(max_loc=10;max_loc>0;max_loc--) if(nm_loc[max_loc-1][0]!='\0') break;
	sysget(4408,2,&sys4408);
  sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  sysget(4670,6,stuksprx);
	sysget(4780,4,&stuksprx[6]);
  if(fldlen(6,2)) arcd=YES;
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

  sysget(3678,2,&def_taal);
  if(fldlen(8,0)==0) add_bstk='N';
  pu_6_1=u(6,1);
  pu_2_1=u(2,1);
  zero(&seldata.data_begin,sizeof seldata); seldata.dt_s_beg=*u(25,2)-730;
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

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
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
    while(seqo_str[pos]==' ') pos--;/* delete trailing blanks */
    pos++;
  }
  seqo_str[pos++]=0x09;
}

static flt2str(bd_)
float bd_;
{
  int16 k;
  char buff[15];
  double bedrag_,add_=0;
  long val_,value;
							
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*100+add_;value=val_/100;
 
  zero(buff,sizeof buff);
  stcli_d(&buff[0],value,10,1);
  for(k=0;k<10;k++){
    if(buff[k]=='\0') break;
    if(buff[k]!=' ') seqo_str[pos++]=buff[k];
  }
  value=val_-value*100;
  if(value){
    seqo_str[pos++]=',';
    if(value<0) value=-value;
    zero(buff,sizeof buff);
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
 
static bit(byte_,bit_)
char byte_;
int16 bit_;
{
  if(byte_ & 1<<bit_) return YES;
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

 
 
 
