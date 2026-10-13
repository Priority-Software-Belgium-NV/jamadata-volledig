/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0015GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0015dat
#define ovlcod BKH0015cod
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

char ovldat[] = "bkh0015  00:29 16/09/10 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16

static struct _sel_lst{
  flag rapport:1;
  flag prt2pdf:1;
  flag a_btw:1;
  flag filrek:1;
  flag btw:1;
  flag filbal:1;
  flag yr:1;
  flag fk:1;
  flag jr:1;
  flag cj:1;
  flag l_rk:1;
  flag k_rk:1;
  flag g_rk:1;
  flag l_bl:1;
  flag k_bl:1;
  flag g_bl:1;
} sel_lst;

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();

static char fm_os80[]  = {7,0x88,80,0,0,0,0};
static char fm_us65[]  = {7,0xC8,65,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_of2_1[] = {6,0x94,2,1,0x30,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_ui4[]   = {6,0xD1,4,0,0x60,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};
static char fm_uOLD[]  = {13,0xC8,1,0,0x09,0,'O','O','L','L','D','D',0};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};

static int16 mnd_strt;
static uint16 last_arc,sys1790;
static char jn[13],b[16],fm_bd[40],niveaus[2][10];
static char sel_lev[2][50],sel_klt[2][50];
static flag sear_stt,seqo_rek,pdfrapport;
static flag chk_btoeg=NO,lvcd,klcd,sys3876;
static uint16 passwrds[3],clean_prev[3];
static flag fil_out=NO,prt2pdf;

ovlcod()
{
  int16 key;
  char choice;

  initload();
  FOREVER{
redo:;
		fasunlck(0);
    scrget(1,72); scraddpicto(1,0,69,19,4,2,60,0,4,"^*financien.belgium.be/nl/E-services/Intervat");
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001) goto redo; // link intervat
    if(key==111) ovlexit(10);
    if(key==101) ovlexit(-1);
		fasunlck(-1);
    switch(choice){
      case '1': if(CheckPw(0,16,0)) periode(YES); break;
      case '2': if(CheckPw(0,16,0)){if(fldlen(26,26)) ask_rekening(); else periode(NO);}break;
      case '3': if(ovltest( 23)) {if(CheckPw(0,29,0)) ovlexit( 23); else break;}
								if(ovltest( 53)) {if(CheckPw(0,29,0)) ovlexit( 53); else break;}
								errnum=12; break;
			case '5': if(CheckPw(0,16,0)){if(!ovltest( 67)) errnum=12; else ovlexit(67);} break;
			case '6': if(CheckPw(0,16,0)){if(!ovltest( 70)) errnum=12; else ovlexit(70);} break;
			case '7': if(CheckPw(0,26,0)){if(!ovltest( 79)) errnum=12; else ovlexit(79);} break;
			case '8': if(CheckPw(0,27,0)){if(ovltest( 58)) ovlexit( 58); else errnum=12;} break;
      case '9': if(CheckPw(0,35,0)) ovlexit( 59); break;
      case '0': if(CheckPw(0,36,0)) opties(); break;
      default:  errnum=34; break;
    }
  }
}

static periode(mode_)
int16 mode_;
{
  int16 curs=2,k,key,maxlev,lev_,z;
  int16 yyyy1,yyyy2,mm1,mm2,dd1,dd2;

	for(k=0;k<sizeof jn;k++) jn[k]='N';
  *u(26,4)=0;*u(26,5)=0;
  *u(26,6)=0;*u(26,7)=0;fil_out=NO;
  if(mode_){*l(26,9)=0;*l(26,10)=0;}
  for(k=26;k<=29;k++) if(fldlen(26,k)) *u(26,k)=0;
  FOREVER{
    redo:
    if(mode_) scrget(1,13); else scrget(1,80);
    z=1;scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrfld(z++,25,1);
    for(k=2;k<4;k++) scrfld(z++,26,k);
    if(mode_){
      for(k=4;k<8;k++) scrfld(z++,26,k);
      for(k=0;k<=1;k++) scrifld(z++,fm_uJN,&jn[k]);
      z++;/* scrifld(z++,fm_uJN,&jn[10]); */
      scrifld(z++,fm_uJN,&jn[12]);
      for(k=2;k<5;k++) scrifld(z++,fm_uJN,&jn[k]);
    }
    scrifld(z++,fm_uJN,&jn[5]);
    if(mode_){
			for(k=6;k<9;k++){
				scrifld(z++,fm_uJN,&jn[k]);
				if(sys1790&0x04) scraddpicto(10+k-6,z-1,2,0,2,1,573,0,0,"Schrijf uit in Excel"); 
			}
		}
    if(mode_==0) for(k=9;k<11;k++) scrfld(z++,26,k);
    scrifld(z++,fm_odat,&last_arc);
    key=scrupd(curs,0x0781);
		prt2pdf=NO; pdfrapport=NO;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){prt2pdf=YES; key=108;} // pdf
    if(key==109){prt2pdf=YES; pdfrapport=YES;key=108;}
    if(key==111) ovlexit(10);
    if(key==101) goto endsr;
    if(*u(26,2)==0){errnum=38;curs=2;goto redo;}
    if(*u(26,3)==0){errnum=38;curs=3;goto redo;}
    if(*u(26,2)<=last_arc){errnum=37;curs=2;goto redo;}
    if(*u(26,3)<*u(26,2)){errnum=36;curs=3;goto redo;}
    jddate(*u(26,2),&yyyy1,&mm1,&dd1);
    jddate(*u(26,3),&yyyy2,&mm2,&dd2);
    if(mnd_strt==1) mnd_strt=13;
    if(mm1<mnd_strt && (mm2>=mnd_strt || yyyy1!=yyyy2)) {errnum=27;goto redo;}
    if(mm1>=mnd_strt){
      if((mm2>=mnd_strt && yyyy1!=yyyy2) || (mm2<mnd_strt && (yyyy1+1)!=yyyy2)){errnum=27;goto redo;}
    }
    if(*u(26,4)==0 && *u(26,5)){errnum=38;curs=4;goto redo;}
    if(*u(26,6)==0 && *u(26,7)){errnum=38;curs=6;goto redo;}
    if(*u(26,6) || *u(26,7)){
      if(*u(26,6)<*u(26,4)){errnum=34;curs=6;goto redo;}
      if(*u(26,6)==*u(26,4) && *u(26,7)<*u(26,5)){errnum=34;curs=7;goto redo;}
    }
		if(key>=5010 && key<=5012){ // balans in xls
      for(k=0;k<sizeof jn;k++) jn[k]='N';
			jn[6+key-5010]='J';fil_out=YES; key=108;
		}
    if(key==108) break;
    errnum=21;
  }
/*  if(jn[12]=='J') spec_vak(); */
  //if(pdfrapport==NO && sys1790 & 0x04){
  //  if(jn[6]=='J' || jn[7]=='J' || jn[8]=='J'){
  //    scrget(1,170);
  //    scrifld(8,fm_os80,"Wenst U de balansen in een Excel-bestand uit te schrijven ???");
  //    scrifld(10,fm_os80,"   F4 = Ja    F5 = Neen");
  //    key=scrupd(0xFFFF,0x18);
  //    if(key==104) fil_out=YES;
  //  }
  //}
  maxlev=0;z=0;
  for(k=0;k<9;k++){
    if(jn[k]=='J'){
  		lev_=(int16)(niveaus[0][(17+k)/4]>>(2*((17+k)%4))) &0x3;
			if(lev_>maxlev){ maxlev=lev_;z=17+k;}
		}
  }
  if(maxlev){
    if(CheckPw(0,z,0)==0) goto endsr;
  }
  if(*u(26,6)==0)*u(26,6)=99;
  if(*u(26,7)==0)*u(26,7)=0xFFFF;
  wr_work();ovlexit(60);
  endsr:;
}


static jaar_rek()
{
  int16 curs=2,k,key,z;

  for(k=0;k<sizeof jn;k++) jn[k]='N';
  jn[9]='J';
  *u(26,2)=0;
  *u(26,4)=0;*u(26,5)=0;
  *u(26,6)=0;*u(26,7)=0;
  *l(26,9)=0;*l(26,10)=0;
  for(k=26;k<=29;k++) if(fldlen(26,k)) *u(26,k)=0;
  redo:
  scrget(1,19);z=1;
  scrfld(z++,25,1);
  scrfld(z++,26,3);
  for(k=3;k<6;k++) scrifld(z++,fm_uJN,&jn[k]);
  for(k=9;k<11;k++) scrfld(z++,26,k);
  scrifld(z++,fm_odat,&last_arc);
  key=scrupd(curs,0x0581);curs=2;
  if(key==111) ovlexit(10);
  if(key==101) goto endsr;
  if(*u(26,3)==0){errnum=38;goto redo;}
  prt2pdf=NO;pdfrapport=NO;
  if(key==109){prt2pdf=YES; key=108;}
  if(key!=108) {errnum=21;goto redo;}
 
  wr_work();ovlexit(63);
  endsr:;
}

static opties()
{
  int16 key;
  char choice;

  FOREVER{
    scrget(1,73);fasunlck(0);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
    if(key==111) ovlexit(10);
    if(key==101) goto endsr;
		fasunlck(-1);
    switch(choice){
      case '1': if(ovltest( 71)) ovlexit(71); else errnum=12; break;
      case '2': if(!ovltest( 72)) errnum=12; else ovlexit( 72); break;
      case '3': if(!ovltest( 73)) errnum=12; else ovlexit( 73); break;
      case '4': if(!ovltest( 74)) errnum=12; else ovlexit( 74); break;
      case '5': if(!ovltest( 75)) errnum=12; else ovlexit( 75); break;
      case '6': if(fldlen(4,48)) ovlexit(76); else errnum=12; break;
      case '7': if(sys1790&8) fil_writ(); else errnum=12;break;
/*    case '8': if(!ok(1806)) errnum=12; else jaar_rek(); break; */
      default:  errnum=34; break;
    }
  }
  endsr:;
}

static wr_work()
{
  *(uint16 *)&sel_lst=NO;
  if(jn[0]=='J') sel_lst.fk=YES;
  if(jn[1]=='J') sel_lst.jr=YES;
  if(jn[2]=='J') sel_lst.cj=YES;
  if(jn[3]=='J') sel_lst.l_rk=YES;
  if(jn[4]=='J') sel_lst.k_rk=YES;
  if(jn[5]=='J') sel_lst.g_rk=YES;
  if(jn[6]=='J') sel_lst.l_bl=YES;
  if(jn[7]=='J') sel_lst.k_bl=YES;
  if(jn[8]=='J') sel_lst.g_bl=YES;
  if(jn[9]=='J') sel_lst.yr=YES;
  if(jn[10]=='J') sel_lst.btw=YES;
  if(jn[11]=='J'){
    sel_lst.filrek=YES;sel_lst.g_rk=YES;
  }
  if(jn[12]=='J') sel_lst.a_btw=YES;
  if(fil_out) sel_lst.filbal=YES;
  if(seqo_rek) sel_lst.filrek=YES;
  if(prt2pdf) sel_lst.prt2pdf=YES;
  if(pdfrapport) sel_lst.rapport=YES;
  *u(26,1)=*(uint16 *)&sel_lst;
}

static ok(pos)
int16 pos;
{
  int16 i1;

  sysget(pos,2,&i1);
  return i1;
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
  fasunlck(0);

  fileopen(1);fileopen(2);fileopen(3);
 
  sysget(1790,2,&sys1790);
  sysget(1858,2,&last_arc);
  sysget(1866,2,&mnd_strt);
  sysget(1918,2,&sear_stt);
  sysget(3876,2,&chk_btoeg);
	sysget(1882,10,&niveaus[0][0]);
  sysget(3882,10,&niveaus[1][0]);
  copy(fm_ud8_2,fm_bd,sizeof fm_ud8_2);
  
}


			
static fil_writ()
{
  int16 curs=2,k,key,z;
  int16 yyyy1,yyyy2,mm1,mm2,dd1,dd2;

  for(k=0;k<sizeof jn;k++) jn[k]='N';
  *l(26,9)=0;*l(26,10)=0;
  for(k=26;k<=29;k++) if(fldlen(26,k)) *u(26,k)=0;
  FOREVER{
    redo:
    scrget(1,69);z=1;
    scrfld(z++,25,1);
    for(k=2;k<4;k++) scrfld(z++,26,k);
    for(k=9;k<11;k++) scrfld(z++,26,k);
    scrifld(z++,fm_uJN,&jn[11]);
    scrifld(z++,fm_odat,&last_arc);
    key=scrupd(curs,0x0481);
    if(key==111) ovlexit(10);
    if(key==101) goto endsr;
    if(*u(26,2)==0){errnum=38;curs=2;goto redo;}
    if(*u(26,3)==0){errnum=38;curs=3;goto redo;}
    if(*u(26,2)<=last_arc){errnum=37;curs=2;goto redo;}
    if(*u(26,3)<*u(26,2)){errnum=36;curs=3;goto redo;}
    jddate(*u(26,2),&yyyy1,&mm1,&dd1);
    jddate(*u(26,3),&yyyy2,&mm2,&dd2);
    if(mnd_strt==1) mnd_strt=13;
    if(mm1<mnd_strt && (mm2>=mnd_strt || yyyy1!=yyyy2)) {errnum=27;goto redo;}
    if(mm1>=mnd_strt){
      if((mm2>=mnd_strt && yyyy1!=yyyy2) || (mm2<mnd_strt && (yyyy1+1)!=yyyy2)){
	errnum=27;goto redo;
      }
    }
    if(jn[6]=='J' || jn[7]=='J' || jn[8]=='J'){
      if(last_arc!=0 && *u(26,2)!= last_arc+1) {errnum=35;curs=2;goto redo;}
    }
    if(key==108) break;
    errnum=21;
  }
  wr_work();ovlexit(60);
  endsr:;
}
 
static ask_rekening()
{
  int16 curs=2,k,key,z,lev_,maxlev;

  seqo_rek=NO;
  sysget(1842,6,(char *)clean_prev);
  for(k=0;k<sizeof jn;k++) jn[k]='N';
  jn[9]='J';
  *u(26,4)=0;*u(26,5)=0;
  *u(26,6)=0;*u(26,7)=0;
  *l(26,9)=0;*l(26,10)=0;
  for(k=26;k<=29;k++) if(fldlen(26,k)) *u(26,k)=0;
  zero(sel_lev,sizeof sel_lev);
  zero(sel_klt,sizeof sel_klt);
  redo:
  scrget(1,214);z=1; 
	scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
	if(sys1790&0x08) scraddpicto(2,0,72,22,4,2,573,0,0,"Schrijf uit in Excel"); 
  scrfld(z++,25,1);
  scrfld(z++,26,2); scrfld(z++,26,3);
  scrifld(z++,fm_uJN,&jn[3]);
  scrifld(z++,fm_us40,sel_lev[0]);
  scrifld(z++,fm_us40,sel_lev[1]);
  scrifld(z++,fm_uJN,&jn[4]);
  scrifld(z++,fm_us40,sel_klt[0]);
  scrifld(z++,fm_us40,sel_klt[1]);
  scrifld(z++,fm_uJN,&jn[5]);
  scrfld(z++,26,9); scrfld(z++,26,10);
  scrifld(z++,fm_odat,&last_arc);
  if(ok(1806)){
    for(k=0;k<3;k++) scrifld(z++,fm_odat,&clean_prev[k]);
  }
  else for(k=0;k<3;k++) streepje(z++);
 
  key=scrupd(curs,0x0581);curs=2;
	if ((key/0x100)==1) key=(key&0xFF)+5000;
	prt2pdf=NO; if(key==5001){prt2pdf=YES; key=108;} // pdf
	seqo_rek=NO;if(key==5002){seqo_rek=YES; key=108;}
  if(key==111) ovlexit(10);
  if(key==101) goto endsr;
  if(*u(26,2)==0){errnum=38;curs=2;goto redo;}
  if(*u(26,3)==0){errnum=38;curs=3;goto redo;}
  if(!ok(1806) && *u(26,2)<=last_arc){errnum=37;curs=2;goto redo;}
  if(*u(26,3)<*u(26,2)){errnum=36;curs=3;goto redo;}
  jn[9]='N';
  if(ok(1806)){
    for(k=0;k<3;k++){
      if(jn[3+k]=='J' && *u(26,2)<=clean_prev[k]){
				errnum=37;curs=2;goto redo;
      }
    }
    if(*u(26,2)<last_arc+1) jn[9]='J';
  }

  if(*u(26,3)==0){errnum=38;goto redo;}
  if(sel_lev[0][0]!='\0') {
    fasinit(1); copy(sel_lev[0],s(1,3),fldlen(1,3));
    if(search(1,0)){curs=5;goto redo;}
    copy(s(1,3),sel_lev[0],fldlen(1,3));
    *u(26,26)=*u(1,1);
  } else *u(26,26)=0;
  if(sel_lev[1][0]!='\0') {
    fasinit(1); copy(sel_lev[1],s(1,3),fldlen(1,3));
    if(search(1,0)){curs=6;goto redo;}
    copy(s(1,3),sel_lev[1],fldlen(1,3));
    *u(26,27)=*u(1,1);
  } else *u(26,27)=0;
  if(*u(26,26) && *u(26,27) && *u(26,26)!=*u(26,27)){
    if(comp_str(sel_lev[0],sel_lev[1],fldlen(1,3))==2) {curs=6;errnum=38;goto redo;}
  }
 
  if(sel_klt[0][0]!='\0') {
    fasinit(2); copy(sel_klt[0],s(2,3),fldlen(2,3));
    if(search(2,0)){curs=8;goto redo;}
    copy(s(2,3),sel_klt[0],fldlen(2,3));
    *u(26,28)=*u(2,1);
  } else *u(26,28)=0;
  if(sel_klt[1][0]!='\0') {
    fasinit(2); copy(sel_klt[1],s(2,3),fldlen(2,3));
    if(search(2,0)){curs=9;goto redo;}
    copy(s(2,3),sel_klt[1],fldlen(2,3));
    *u(26,29)=*u(2,1);
  } else *u(26,29)=0;
  if(*u(26,28) && *u(26,29) && *u(26,28)!=*u(26,29)){
    if(comp_str(sel_klt[0],sel_klt[1],fldlen(2,3))==2) {curs=9;errnum=38;goto redo;}
  }
  for(k=3;k<6;k++) if(jn[k]=='J') break;
  if(k>=6){curs=4;errnum=38;goto redo;}
  if(key!=108) goto redo;
  maxlev=0;z=0;
  for(k=3;k<6;k++){
    if(jn[k]=='J'){
  		lev_=(int16)(niveaus[0][(17+k)/4]>>(2*((17+k)%4))) &0x3;
			if(lev_>maxlev){ maxlev=lev_;z=17+k;}
		}
  }
  if(maxlev){
    if(CheckPw(0,z,0)==0) goto endsr;
  }
 
  
  wr_work();ovlexit(63);
  endsr:;
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
 
static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
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