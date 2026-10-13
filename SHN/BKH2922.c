/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH2922GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH2922dat
#define ovlcod BKH2922cod
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
typedef short int int16;__declspec(dllimport) unsigned char PrintPaperNr;
__declspec(dllimport) unsigned char PrintOverlayRef;

int16 ovlcall();

char ovldat[] = "bkh2922  00:01 30/11/10 (c) Jamadata";
/* aanpassen/schrappen memo/afhalingen klanten  */

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define D_LIN_SCR       10
							
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


static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os30[]   = {7,0x88,30,0,0,0,0};
static char fm_os15[]   = {7,0x88,15,0,0,0,0};
static char fm_us25[]   = {7,0xC8,25,0,0,0,0};
static char fm_us10[]   = {7,0xC8,10,0,0,0,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uf4_0[] = {6,0xD4,4,0,0x70,0};
static char fm_of7_2[] = {6,0x94,7,2,0x70,0};
static char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_u_SP[]  = {11,0xC8,1,0,1,0,'S','S','P','P',0};

static struct{
  uint16 rec;
  float qlv;
  char  stuks_fl;
  char  code[15];
  char  omschr[40];
	char  gratis;
  uint16 hash;
}tblin[30];

static flag klcd,lvcd,only_dsp=NO;
static char fmt[40], addartJN[30];
static int16 prt2pdf;
static uint16 inq_klt;
static int16 form_dat[8],prtnr,pr_mode,free;

ovlcod(parmval)
int16 parmval;/* 0=klant ook vragen, 1 = update, 2=facturatie */
{
  retcall=YES;
  initload();

	redo:;
  if(parmval==0) if(ask_klant()==NO) goto endsr;
  if(*u(2,1)==0) goto endsr;
  fasinit(62);*u(62,2)=*u(2,1); faskeyi(62,1,0);
  if(fldlen(62,10)==0) DisplayMemo(2);
  else retcall=dsp_afhaling(parmval);
  if(*u(62,1)) fasupd(62); else fasadd(62);
	if(parmval==0 && retcall==0) goto redo;
  endsr:;
  ovlexit(-1);
}

static ask_klant()
{
  int16 z,key;
									
  fasinit(2);inq_klt=0;
  FOREVER{
		redo:;
    scrget(1,5); if(fldlen(62,10)) scraddpicto(2,0,76,22,4,2,583,0,0,"Lijst afhalingen"); 
    scrifld(1,fm_os30,"Klantenmemo/afhaling");
    scrfld(2,25,1);
    scrifld(3,fm_os15,"aan te passen");
    scrfld(4,2,3);scraddpicto(1,4,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    key=scrupd(4,0x0481);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101 || key==111){fasinit(2);return NO;}
		z=0; if(key==5001) z=98;
    if(key!=5002 || *s(2,3)){
			if(!search(2,z)) {
				if(key!=5002) return YES;
			} 
			else goto redo;
		} else fasinit(2);
		inq_klt=*u(2,1);
		if(key==5002) list_afhalingen();
  }
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
    if(key==15 && only_dsp){only_dsp=NO;goto redo;}
    if(key==108) break;
  }
}
 
static dsp_afhaling(mode_)
int16 mode_;/* 2=bon/facturatie */
{
  int16 curs,j,key,k,start_=0,z,z_base,q_per_line,nstart_,auto_enter,err_pos_,curspos_;
  

	copy("JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ",addartJN,30);


  for(k=0;k<30;k++){
    if(fldlen(62,12+k*5) && *u(62,12+k*5)){
      fasinit(6);*u(6,1)=*u(62,12+k*5);fasgeti(6);
      tblin[k].qlv=*f(62,10+k*5);
      tblin[k].stuks_fl=*s(62,11+k*5);
      copy(s(6,2),tblin[k].code,fldlen(6,2));
      copy(s(6,3),tblin[k].omschr,fldlen(6,3));
      tblin[k].rec=*u(6,1);
			if(fldlen(62,13+k*5)) tblin[k].gratis=*s(62,13+k*5);
      tblin[k].hash=hash(k);
    }
  }
  curs=1;q_per_line=6;err_pos_=0;
  FOREVER{
    redo:
    scrnum=0;scrget(2,318);z=1;
		if(start_>0) scraddpicto(1,0,75,12,4,2,18,0,4,"up"); 
		if((start_+D_LIN_SCR)<30) scraddpicto(2,0,75,20,4,2,13,0,4,"down"); 
		scraddpicto(3,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrofld(z++,2,3,-1);
    for(k=0;k<4;k++) scrfld(z++,62,5+k);
    scrifld(z++,fm_us25,s(62,9));
    z_base=z;auto_enter=NO;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      if(fldlen(62,10+j*5)==0) continue;
			if(mode_==2 && fldlen(62,9)>=60){ // bij toevoegen op bon, selectie per artikel 
				scraddfield(100+j,1,12+j-start_,2); scrifld(100+j,fm_u_JN,&addartJN[j],-1);
			}
      j++;scrifld(z++,fm_ou3,&j); j--;
      scrifld(z++,fm_uf4_0,&tblin[j].qlv);
      scrifld(z++,fm_u_SP,&tblin[j].stuks_fl);
      auto_enter=YES;if(tblin[j].code[0]!='\0' && z!=err_pos_) auto_enter=NO;
      fmt_get(6,2);
      if(auto_enter){scrifld(-z,fmt,tblin[j].code);z++;}
      else scrifld(z++,fmt,tblin[j].code);
      auto_enter=YES;if(tblin[j].omschr[0]!='\0' && z!=err_pos_) auto_enter=NO;
      fmt_get(6,3);
      if(auto_enter){scrifld(-z,fmt,tblin[j].omschr);z++;}
      else scrifld(z++,fmt,tblin[j].omschr);
			if(fldlen(62,13+j*5)) scrifld(z++,fm_u_JN,&tblin[j].gratis); else z++;
    }
    if(mode_==2){
      scraddf(z,22,35,8);	scrifld(z++,VarTextFmt(37,0),"F10 voeg afhaling toe aan bon/factuur");		
			key=scrupd(curs,0x3A1);
		}
    else key=scrupd(curs,0x1E1);
    curs=z_base;curspos_=fldcurs;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    auto_enter=NO;nstart_=start_;err_pos_=0;
    if(key==101){
      fasinit(62);*u(62,2)=*u(2,1); faskeyi(62,1,0);
      return NO;
    }
    if(key==106){
      fasinit(62);*u(62,2)=*u(2,1); faskeyi(62,1,0);
      break;
    }
    if(key==18){
      if(curspos_<z_base){
				curs=curspos_+1;goto redo;
      }
      auto_enter=YES;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      k=(curspos_-z_base)%q_per_line;
      if(k==3 && tblin[j].code[0]=='\0') {curs=curspos_+1;goto redo;}
      if(k==4 && tblin[j].omschr[0]=='\0') {curs=curspos_+1;goto redo;}
    }
    for(k=start_;k<(start_+D_LIN_SCR);k++){
      if((tblin[k].code[0] || tblin[k].omschr[0]) && tblin[k].hash!=hash(k)){
				fasinit(6);
				if(tblin[k].code[0]) {*s(6,3)='.';copy(tblin[k].code,s(6,3)+1,fldlen(6,2));}
				else {copy(tblin[k].omschr,s(6,3),fldlen(6,3));}
				if(search(6,0)){
					curs=z_base+ (k-start_)*q_per_line +3; if(tblin[k].code[0]=='\0') curs++;
					err_pos_=curs;errnum=39;goto redo;
				}
				copy(s(6,2),tblin[k].code,fldlen(6,2));
				copy(s(6,3),tblin[k].omschr,fldlen(6,3));
				tblin[k].rec=*u(6,1);
				tblin[k].hash=hash(k);
      }
      else if(tblin[k].code[0]=='\0' && tblin[k].omschr[0]=='\0'){
				zero((char *)&tblin[k],sizeof tblin[0]);
      }
    }
    if(key==108 || key==110){
      j=0;
      for(k=0;k<30;k++){
				if(fldlen(62,10+j*5)==0) break;
				if(tblin[k].rec){
					*f(62,10+j*5)=tblin[k].qlv;
					*s(62,11+j*5)=tblin[k].stuks_fl;
					*u(62,12+j*5)=tblin[k].rec;
					if(fldlen(62,13+j*5)) *s(62,13+j*5)=tblin[k].gratis;
				  if(mode_==2 && fldlen(62,9)>=60){ // bij toevoegen op bon, selectie per artikel 
						*(s(62,9)+30+j)=addartJN[k];
					}
					j++;
				}
      }
      for(j;j<30;j++){
				if(fldlen(62,10+j*5)==0) break;
				*f(62,10+j*5)=0;*s(62,11+j*5)=0;*u(62,12+j*5)=0;
				if(fldlen(62,13+j*5)) *s(62,13+j*5)=0;
      }
      break;
    }

		prt2pdf=NO;if(key==5003){prt2pdf=YES;key=109;}
		if(key==109) plaadbon();

    start_=nstart_;
    if(key==18 || auto_enter){ /* automatische bladskip op einde van scherm */
      for(k=0;k<D_LIN_SCR;k++){if(tblin[start_+k].qlv==0) break;}
      if(k==D_LIN_SCR) key=103;
    }
    if(key==5001) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==5002) start_+=D_LIN_SCR;
    if(start_>(30-D_LIN_SCR)) start_=30-D_LIN_SCR;
    j=0;
    for(k=start_;k<start_+D_LIN_SCR;k++){if(tblin[k].omschr[0]=='\0') break;}
    if(k==start_+D_LIN_SCR) k=start_;curs=z_base + (k-start_)*q_per_line;
  }
  endsr:;
  if(key==110) return 2;
  return YES;
}


static plaadbon()
{
  int16 j,k,z,prt_ok_,vat_used_;
	char st_kod_[2],str_[30];

  getsysprNew(14,form_dat,&pr_mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if (prtopen(prtnr,form_dat,6,80,pr_mode,4)!=0) {goto endsr;}
  free=999;

  scrget(1,6);
  prtfld(25,1,20);
  prttext("<t25b>Laadbon AFHALING  <e>");
  prttext("<eb>   Datum : ");prtfld(25,2,-1); // prttext("<t72>Blz.<pp>.");
  prtbuf(1);
  //if(*s(8,25)) {prttext("<t1>Referentie: <b>");prtfld(8,25,-1);prttext("<b>");}
  //prttext("<t45eb>");prtfld(63,3,-1); //prttext("  ");prtfld(2,71,5);
  //prtbuf(2);
	z=1;
  prttab(z,6,2,2,-1); prttitle(z++,"Code",3);
  prttab(z,6,29,4,-1); prttitle(z++,"Pl.Mg",3);
  prttab(z,58,7,1,-1); prttitle(z++,"Aantal",0x13);
  prttab(z,58,62,1,-1); prttitle(z++,"",3);
  prttab(z,6,3,2,-1); prttitle(z++,"Omschrijving",3);
  prtbuf(3);
   zero(str_,sizeof str_); sprintf_s(str_,25,"Laadbon %.15s",s(2,3));
  p_pdfname(str_,*u(8,8),0); 
  
  prttext("<eb>");prtfld(2,3,-1);prttext("<eb>");nextline();
  prttext("<eb>");prtfld(2,4,-1);prttext("<eb>");nextline();
  prttext("<eb>");prtfld(2,5,-1);prttext(" "); prtfld(2,6,-1);prttext("<eb>");
	//if(*s(2,72)=='J') prttext("<t66b>A<b>");
	//if(*s(2,71)) {prttext("<t70b>");prtfld(2,71,10);prttext("<b>");}
	nextline();
  nextline();
 
	vat_used_=NO;
  for(k=0;k<30;k++){
		if(fldlen(62,10+k*5)==0) break;
		if(tblin[k].rec && addartJN[k]=='J'){
			fasinit(6);*u(6,1)=tblin[k].rec; fasgeti(6);
			*f(58,7)=tblin[k].qlv;
			*s(58,62)=tblin[k].stuks_fl;
			for(j=1;j<10;j++) prtinfo(j,0);nextline();
			if(*i(6,9)==4) vat_used_=YES;
		}
  }

  nextline();
  if((free)<32 && (free)>26) {nextline();nextline();}
  else while(free>(32)) nextline();
	for(k=0;k<4;k++) prtfld(z++,62,5+k);
  prt_ok_=NO;

  for(k=0;k<4;k++){
    if(*s(62,5+k)!='\0'){
      prttext("<t5>"); prtfld(62,5+k,-1);nextline();
      prt_ok_=YES;
    }
  }
  if(prt_ok_)nextline();

  if(fldlen(2,65) && *s(2,65)){
      prtfld(2,65,-1);
      nextline();
  }
	while(free>(6)) nextline();
	prttext("Klaargezet door : ............... Datum .../.../...    Chauffeur : ...............");nextline();

  prtform(0);
	prtclose();

#if FLAGTHO
	if(vat_used_==NO) goto endsr;


	getsysprNew(14,form_dat,&pr_mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if (prtopen(prtnr,form_dat,6,80,pr_mode,4)!=0) {goto endsr;}
  free=999;

  scrget(1,6);
  prtfld(25,1,20);
  prttext("<t25b>Laadbon AFHALING vaten <e>");
  prttext("<eb>   Datum : ");prtfld(8,8,-1);
  prtbuf(1);
 
   zero(str_,sizeof str_); sprintf_s(str_,30,"Laadbon vaten %.15s",s(2,3));
  p_pdfname(str_,*u(8,8),0); 
  
  prttext("<be>");prtfld(2,3,-1);prttext("<be>");nextline();
  prttext("<be>");prtfld(2,4,-1);prttext("<be>");nextline();
  prttext("<be>");prtfld(2,5,-1);prttext(" "); prtfld(2,6,-1);prttext("<be>");


	nextline();
  nextline();
 
	prttext("<beu>Aantal<u> <u>Omschrijving");nextline();
  for(k=0;k<30;k++){
		if(fldlen(62,10+k*5)==0) break;
		if(tblin[k].rec && addartJN[k]=='J'){
			fasinit(6);*u(6,1)=tblin[k].rec; fasgeti(6);
			if(*i(6,9)!=4) continue;
			*f(58,7)=tblin[k].qlv;
			*s(58,62)=tblin[k].stuks_fl;
			prttext("<e>");
			prtfld(58,7,-1);prttext(" "); prtfld(58,62,-1); prttext(" "); prtfld(6,3,-1);
			nextline();
		}
  }
  nextline();
  while(free>(6)) nextline();
	prttext("Klaargezet door : ............... Datum .../.../...    Chauffeur : ...............");nextline();

  prtform(0);
	prtclose();
#endif

  endsr:;
}


static list_afhalingen()
{
  int16 z,j,k,mode_,first_;
  float qlv_,cstock_;

  prtclose();
  getsysprNew(5,form_dat,&pr_mode,&prtnr); PrintPaperNr=0; // steeds pdf
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prttext("<b>Lijst afhalingen");
  prttext("<t55>");prtfld(25,2,-1);
  prttext("<t72>");prttext("Blz.<ppp>.");
  prtbuf(1);z=1;
  prttab(z,2,klcd+1,2,-1); prttitle(z++,"Code",3);
  prttab(z,2,3,2,30); prttitle(z++,"Klant",3);
  prttab(z,58,31,1,-1); prttitle(z++,"Aantal",0x13);
  if(fldlen(58,62)){
    prttab(z,58,62,1,-1); prttitle(z++,"S",3);
  }
	prttab(z,6,3,1,-1); prttitle(z++,"Artikel",0x3);

  prtbuf(3);
	p_pdfname("Lijst afhalingen",*u(25,2),0);
  free=999;
  scrget(1,7);scrupd(-3,0);
  mode_=1;
	FOREVER{
		nextk:;
		if(faskeyi(2,2,mode_)) break; mode_=2;
		if(inq_klt && *u(2,1)!=inq_klt) break;
		fasinit(62);*u(62,2)=*u(2,1); if(faskeyi(62,1,0)) goto nextk;
		first_=YES;
		for(k=0;k<30;k++){
			if(fldlen(62,12+k*5) && *u(62,12+k*5) && *f(62,10+k*5)){
				fasinit(6);*u(6,1)=*u(62,12+k*5); fasgeti(6);
				fasinit(58);*f(58,31)=*f(62,10+k*5); *s(58,62)=*s(62,11+k*5);
				if(first_){j=1;first_=NO;} else j=3;
				for(j;j<15;j++) prtinfo(j,0); nextline();
			}
		}
  }
  prtform(0);
  prtclose();
	fasinit(2);
	if(inq_klt){*u(2,1)=inq_klt;fasgeti(2);}
  endsr:;
}


static uint16 hash(lin_)
int16 lin_;
{
  char *ps;
  int16 len_;
  uint16 fuval=0;
					
  len_=sizeof tblin[0].code + sizeof tblin[0].omschr;ps=tblin[lin_].code;
  while(len_--){
    fuval=fuval*3+*(ps++);
  }
  return fuval;
}

 

static initload()
{

 // fileopen(2); geeft problemen bij AST, wijzigingen zijn dan weg
	if(fldlen(2,2)) klcd=YES;
  fileopen(6);
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

static nextline()
{
  free=prtline();
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

