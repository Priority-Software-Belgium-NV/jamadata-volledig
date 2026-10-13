/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0264GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0264dat
#define ovlcod DRK0264cod
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

char ovldat[] = "drk0264  00:01 25/02/09 (c) Jamadata"; // verhuurprogramma 

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DIMLINE         45
#define DIM_TB          500
#define DIM_95          500
#define flag            uint16
#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

extern char *s();
extern int16 *i();
extern uint16 *u();
static uint16 hash();
extern long *l();
extern long val();
extern float *f();
extern double *d();

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os25[]  = {7,0x88,25,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os35[]  = {7,0x88,35,0,0,0,0};
static char fm_os23[]  = {7,0x88,23,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os12[]  = {7,0x88,12,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us75[]  = {7,0xC8,75,0,0,0,0};
static char fm_ou2[]   = {6,0x91,2,0,0x60,0};
static char fm_ou3[]   = {6,0x91,3,0,0x60,0};
static char fm_oi5[]   = {6,0x91,5,0,0x70,0};
static char fm_oi3[]   = {6,0x91,3,0,0x60,0};
static char fm_ui3[]   = {6,0xD1,3,0,0x60,0};
static char fm_oi4_s[] = {6,0x91,4,0,0x60,0};
static char fm_ui4_s[] = {6,0xD1,4,0,0x60,0};
static char fm_ou5[]   = {6,0x91,5,0,0x60,0};
static char fm_ou4[]   = {6,0x91,4,0,0x70,0};
static char fm_ou1[]   = {6,0x91,1,0,0x20,0};
static char fm_uu5[]   = {6,0xD1,5,0,0x60,0};
static char fm_uu2[]   = {6,0xD1,2,0,0x60,0};
static char fm_uu3[]   = {6,0xD1,3,0,0x60,0};
static char fm_uu1[]   = {6,0xD1,1,0,0x20,0};
static char fm_of4_0[] = {6,0x94,4,0,0x60,0};
static char fm_of6_0[] = {6,0x94,6,0,0x70,0};
static char fm_uf4_0[] = {6,0xD4,4,0,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_od7_2[] = {6,0x95,7,2,0x70,0};
static char fm_uJN[]   = {11,0xC8,1,0,9,0,'J','J','N','N',0};
static char fm_u_SR[]  = {13,0xC8,1,0,1,0,'S','S','R','R','?','?',0};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_titel[]  = {7,0x88,80,0,0,0,0};

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

static struct {
  int16 begpos;
  int16 lengte;
  char *txt[4];
} firm[10] = {116,17,"Telefoon","N– t…l…phone","Telephone","Telefon",
	     170,17,"Fax","Fax","Fax","Fax",
	      86,15,"B.T.W. nr.","N– T.V.A.","T.V.A.","M.W.S.",
	     101,14,"Bankrek.","Banque","Bank","Bank",
	     134,12,"RPR","RPM","","",
	     149,20,"Erkenningsnr","","","",
	     188,30,"Web-site","Web-site","","",
	     222,30,"E-mail","E-mail","","",
	     256,42,"IBAN","IBAN","IBAN","IBAN",
	     298,11,"BIC","BIC","BIC","BIC"};

static char nm_20[20],nm_15[15],oldnm[50],buff500[500],firma[350],StdTekst[4][75];
static char def_munt[4],tb_lever[DIM_95];
static int16 free,taaltxt;
static int16 form_dat[8],prtnr,pr_mode,skip_off,prt2pdf;
static uint16 uit_dat,dt_uitb,dt_uite,dt_beg,dt_end,last_vf,dtb_vrh_beg,dte_vrh_beg;
static uint16 inq_klt,inq_art,bonnr,tb_recs[DIM_95],upd_mode;
static char fmt[40],sys1920[250], nm_dehr[60], prt_JN,opm_foot[4][80];
static double totaal;
static flag sear_stt,chk_btoeg=NO,sys3876,sys5660,sys5694,lvcd,klcd,arcd,sys5696;
static flag sys3894,sys4608;

static struct _line {
  float aantal;
  char code[10];
  char omschr[40];
  float ehpr;
  double totaal;
  uint16 arec;
  uint16 rec95;
  uint16 hval;
} line[DIMLINE];

static struct{
  uint16 rec;
  uint16 q_verh;
  uint16 dt_beg;
  uint16 dt_end;
} tb[DIM_TB];

static flag Prt2Xls=NO;

extern int16 ilength; // XLS
static int XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi; // XLS
static int16 StylTotaal, StylGrpTot, StylKlasse, StylNormal, StylDate, StylTitel, Styl2Use;


#include "Std\XlsFunc.c"

ovlcod(parmval)
int16 parmval;
{
  int16 key;
  char choice=' ';

  initload();
	upd_mode=YES;

	if(parmval==1){ // oproepen vanuit x19
		fasinit(2);*u(2,1)=*u(27,5); fasgeti(2); 
		fasinit(6);inq_klt=*u(2,1);inq_art=0;
		dsp_1len(inq_art,inq_klt,*u(25,2)-30,0);
		ovlexit(-1);
  }


  FOREVER{
		redo:;
    scrget(2,246);fasunlck(0);scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0264A");
    scrfld(1,25,1); scraddpicto(1,0,76,22,4,2,514,0,0,"Extra opties"); 
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
		if(key==5001){VerhuurParameters();goto redo;} // extra opties
    if(key==101) break;
    if(key==111) ovlexit(*u(25,4));
		fasunlck(-1); upd_mode=YES;
    switch(choice){
      case '1': uit_len();break;
      case '2': bin_len();break;
      case '3': dsp_len();break;
      case '4': upd_len();break;
      case '5': prt_len();break;
      case '6': WeekOverzicht();break;
      case 'A': kil_len();break;
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}

static VerhuurParameters()
{

  int16 key,k,z;

  scraddf(-1,0,0,0);z=1;
  DisplayMenuTitel(4,"Parameters",0xA);
	scraddf(z++,10,3,0);
  for(k=0;k<4;k++) scraddf(z++,12+k,3,2);
  scraddf(z++,23,1,8);scraddf(z++,23,15,8); 
  FOREVER{
    redo:;
    z=1;
    scrifld(z++,VarTextFmt(65,0),"Vaste teksten af te drukken op de verhuurbon : ");
		for(k=0;k<4;k++) scrifld(z++,fm_us75,StdTekst[k]);
    scrifld(z++,VarTextFmt(13,0)," F6 annuleer ");scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
    key=scrupd(1,0xA0);
    if(key==106) break;
		if(key==108){sysput(19700,300,StdTekst); break;}
  }
	sysget(19700,300,StdTekst);
}


static uit_len()
{
  int16 k,key;
						
  uit_dat=*u(25,2);upd_mode=NO;dt_uitb=0;dt_uite=0;
  prt_JN='J';
  FOREVER{
    redo:;
    sysget(3634,2,&bonnr);
    if(++bonnr>65000) bonnr=1;
    zeroL((char *)&line[0].aantal,sizeof line);
    if(uit_dat==0) uit_dat=*u(25,2);
    fasinit(2); fasinit(6); totaal=0;
    redo_upd:;
    k=_uitlen();
    if(k==1) break;/* stop */
    if(k==-1) goto redo;/* annuleer */

    if((k=dsp_tot(NO))==NO) break;
    sysget(3634,2,&bonnr);
    if(++bonnr>65000) bonnr=1;
    if(k>1)goto redo_upd;
    if(prt_JN=='J') {
      if(print_bon()) goto redo_upd;
      FOREVER{
				scrget(2,28);
				key=scrupd(0xFFFF,0xF58);
				if(key==105) break;
				
				if(key==104) print_bon();
				if(key==107) goto redo_upd;
      }
    }
    write_bon();
    sysput(3634,2,&bonnr);
  }
}

static upd_len()
{
  int16 j,k,key,mode_;
						
  uit_dat=*u(25,2);upd_mode=YES;
  prt_JN='J';
  FOREVER{
    redo:;
    if(get_len()==NO) break;
    zero((char *)&line[0].aantal,sizeof line); j=0;
    fasinit(95);*u(95,2)=inq_klt;mode_=1;
    FOREVER{
      next95:;
      if(faskeyi(95,2,mode_)) break; mode_=2;
      if(*u(95,2)!=inq_klt) break;
      if(*u(95,4)!=bonnr) goto next95;
	
      uit_dat=*u(95,5);dt_uitb=*u(95,6);dt_uite=*u(95,7);
      line[j].aantal=*f(95,8);line[j].ehpr=*f(95,9);line[j].totaal=*d(95,10);
			fasinit(6);
			if(*u(95,3)){
        *u(6,1)=*u(95,3);fasgeti(6);
        copy(s(6,2),line[j].code,fldlen(6,2));
        copy(s(6,3),line[j].omschr,fldlen(6,3));
			}
			else if(fldlen(95,13)){
				copy(s(95,13),line[j].omschr,fldlen(95,13));
			}
      line[j].arec=*u(6,1);line[j].rec95=*u(95,1);
      j++;
    }
 
    if(uit_dat==0) uit_dat=*u(25,2);
    totaal=0;
    redo_upd:;
    k=_uitlen();
    if(k==1) break;/* stop */
    if(k==-1) goto redo;/* annuleer */

    if((k=dsp_tot(YES))==NO) break;
    if(k>1)goto redo_upd;
    if(prt_JN=='J') {
      if(print_bon()) goto redo_upd;
      FOREVER{
				scrget(2,28);
				key=scrupd(0xFFFF,0xF58);
				if(key==105) break;
				if(key==104) print_bon();
				if(key==107) goto redo_upd;
      }
    }
    write_bon();
  }
}

static get_len()
{
  int16 j,k,key,mode_=1,z,curs=3,start=0;

  fasinit(2);
  redo:
  scrget(2,262);z=1;
  scrfld(z++,25,1);
  scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
  key=scrupd(3,0x81);curs=2;
	if ((key/0x100)==1) key=(key&0xFF)+5000;
  if(key==101) return NO;
  if(key==111) ovlexit(-1);
	if(key==5001) {if(search(2,98)) goto redo;}
	else {if(search(2,0)) goto redo;}
  bonnr=0;
  fasinit(95);*u(95,2)=*u(2,1);mode_=1;
  zero((char *)&tb[0].rec,sizeof tb);
  FOREVER{
    next:;
    if(faskeyu(95,2,mode_)) break;mode_=2;
    if(*u(95,2)!=*u(2,1)) break;
    for(k=0;k<DIM_TB;k++){
      if(tb[k].rec==0 || tb[k].rec==*u(95,4)) break;
    }
    tb[k].rec=*u(95,4);tb[k].dt_beg=*u(95,6);tb[k].dt_end=*u(95,7);
  }
  for(k=0;k<DIM_TB;k++) if(tb[k].rec==0) break;
  if(k==0) {errnum=39;goto redo;}
  if(k>1){
    FOREVER{
      scrnum=0;scrget(2,263);z=1;
      scrofld(z++,2,3,-1);
      for(j=start;j<k;j++){
				j++;scrifld(z++,fm_ou2,&j);j--;
				scrifld(z++,fm_ou5,&tb[j].rec);
				scrifld(z++,fm_odat,&tb[j].dt_beg);
				scrifld(z++,fm_odat,&tb[j].dt_end);
				if(j==start+14) break;
      }
      j=0;scrifld(62,fm_uu2,&j);
      key=scrupd(1,0x87);
      if(key==101) {goto redo;}
      if(j>0 && j<=k) {bonnr=tb[j-1].rec;inq_klt=*u(2,1);break;}
      if(key==102) start-=15;
      if(key==103) {start+=15;if(start>k-15) start=k-15;}
      if(start<0) start=0;
    }
  }
  else{bonnr=tb[0].rec;inq_klt=*u(2,1);}
  if(bonnr==0) return NO;
  return YES;
}
 
static _uitlen()
{
  int16 j,k,z,key,z_base,curs=4,start_,q_per_line=6,auto_enter,err_pos_,nstart_,curspos_;
  uint16 rec_;
  char lst_klt[50];
 
  totaal=0; start_=0;err_pos_=0;lst_klt[0]=0xFF;
  FOREVER{
    redo:;
    scrget(2,247); z=1;
    scrifld(z++,fm_udat,&uit_dat);
    scrifld(z++,fm_uu5,&bonnr);
    scrifld(z++,fm_uJN,&prt_JN);
    scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_udat,&dt_uitb); scrifld(z++,fm_udat,&dt_uite);
    scrifld(z++,fm_od6_2,&totaal);
    z_base=z;
    for (k=start_;k<start_+15; k++) {
      auto_enter=NO;
      k++;scrifld(z++,fm_ou2,&k); k--;
      scrifld(z++,fm_uf4_0,&line[k].aantal);
      if(sys4608 & 1){
				auto_enter=YES;if(line[k].code[0]!='\0' && z!=err_pos_) auto_enter=NO;
      }
      fmt_get(6,2);
      if(auto_enter){scrifld(-z,fmt,line[k].code);z++;}
      else scrifld(z++,fmt,line[k].code);
      if(sys4608 & 1){
				auto_enter=YES;if(line[k].omschr[0]!='\0' && z!=err_pos_) auto_enter=NO;
      }
      fmt_get(95,13);
      if(auto_enter){scrifld(-z,fmt,line[k].omschr);z++;}
      else scrifld(z++,fmt,line[k].omschr);
			scraddpicto(10+k-start_,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
      scrifld(z++,fm_uf5_2,&line[k].ehpr);
      scrifld(z++,fm_od6_2,&line[k].totaal);
    }
    key=scrupd(curs,0x1EF); curs=z_base;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    auto_enter=NO;nstart_=start_;err_pos_=0;
		if(key==101 || key==106){
  		for(k=0;k<DIMLINE;k++) if(line[k].omschr[0]) break;
			if(k>=DIMLINE || scr_ok("Wenst U echt deze verhuurbon te annuleren ?")){
				if(key==101) return 1;
				else return -1;
			}
		}
    if(key==5001 || cmpstr(lst_klt,s(2,3),fldlen(2,3))){
			z=0; if(key==5001) z=98;
      if(search(2,z)){curs=4; goto redo;}
      copy(s(2,3),lst_klt,fldlen(2,3));
			if(upd_mode==NO){
			  fasinit(95);*u(95,2)=*u(2,1);
        if(faskeyi(95,2,1)==0){
					if(*u(95,2)==*u(2,1)) DisplayWarning("Let op: Er bestaat reeds een verhuurbon op deze klant!",605,0);
				}
			}
    }
    if(dt_uitb==0) {curs=5;errnum=38;goto redo;}
    if(dt_uite<dt_uitb) {curs=6;errnum=34;goto redo;}
		if(key>=5010 && key<5010+15){
			k=key-5010+start_;
			if(fldlen(95,13) && line[k].omschr[0]=='*'){curs=curspos_; goto redo;} // losse opmerking
			fasinit(6);
			if(line[k].code[0]!='\0') {*s(6,3)='.';copy(line[k].code,s(6,3)+1,fldlen(6,2));}
			else {copy(line[k].omschr,s(6,3),fldlen(6,3));}
			if(search(6,98)){
				curs=z_base+2+(k-start_)*6; if(line[k].code[0]=='\0') curs++;
				errnum=39;goto redo;
			}
			copy(s(6,2),line[k].code,fldlen(6,2));
			copy(s(6,3),line[k].omschr,fldlen(6,3));
			line[k].arec=*u(6,1);
			j=*s(2,26)-'0';if(j<0 || j>9) j=0;
			if(line[k].ehpr==0) line[k].ehpr=*f(6,PrNrs[j]);
		}

    if(key==18){
      if(curspos_<z_base){
				curs=curspos_+1;goto redo;
      }
      auto_enter=YES;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      k=(curspos_-z_base)%q_per_line;
      if(k==2 && line[j].code[0]=='\0') {curs=curspos_+1;goto redo;}
      if(k==3 && line[j].omschr[0]=='\0') {curs=curspos_+1;goto redo;}
    }

    if(key==104){
      j=(curspos_-z_base)/q_per_line;j+=start_;
      rec_=line[j].rec95;
      zero((char *)&line[j].aantal,sizeof line[0]);
      line[j].rec95=rec_;
    }

    for(k=start_;k<start_+15;k++){
      if((line[k].code[0] || line[k].omschr[0]) && line[k].hval!=hash(k)){
				if(fldlen(95,13) && line[k].omschr[0]=='*'){// losse opmerking, niet checken
					line[k].code[0]='\0'; line[k].arec=0; 
				}
				else{
					fasinit(6);
					if(line[k].code[0]!='\0') {*s(6,3)='.';copy(line[k].code,s(6,3)+1,fldlen(6,2));}
					else {copy(line[k].omschr,s(6,3),fldlen(6,3));}
					if(search(6,0)){
						curs=z_base+2+(k-start_)*6; if(line[k].code[0]=='\0') curs++;
						errnum=39;goto redo;
					}
					copy(s(6,2),line[k].code,fldlen(6,2));
					copy(s(6,3),line[k].omschr,fldlen(6,3));
					line[k].arec=*u(6,1);
					j=*s(2,26)-'0';if(j<0 || j>9) j=0;
					if(line[k].ehpr==0) line[k].ehpr=*f(6,PrNrs[j]);
				}
			}
			else{ // lege lijn wissen
				if(line[k].code[0]=='\0' && line[k].omschr[0]=='\0'){
					rec_=line[k].rec95;
					zero((char *)&line[k].aantal,sizeof line[0]);
					line[k].rec95=rec_;
				}
				else if(line[k].aantal==0 && line[k].omschr[0]!='*') {curs=z_base+k*5;errnum=38;goto redo;}
      }
      if(chk_vrij(k)==NO){curs=z_base+(k-start_)*6;errnum=38;goto redo;}
      line[k].hval=hash(k);
    }
    totaal=0;
    for(k=0;k<DIMLINE;k++){
      line[k].totaal=line[k].aantal*line[k].ehpr;
      totaal+=line[k].totaal;
    }

    if(key==102){
      start_-=15; if(start_<=0) start_=0;
    }
    if(key==103){
      start_+=15; if(start_>=DIMLINE) start_=DIMLINE-15;
			if(start_<=0) start_=0;
    }
    if(key==108) break;

    if(key==109 && fldlen(62,1)){
      fasinit(62);*u(62,2)=*u(2,1);
      if(faskeyi(62,1,0)){
				fasinit(62);*u(62,2)=*u(2,1);fasadd(62);
      }
      klt_memo();fasupd(62);
    }

    for(k=start_;k<start_+15;k++){
      if(line[k].code[0]=='\0' && line[k].omschr[0]=='\0'){
				curs=z_base+1+(k-start_)*6;
				break;
      }
    }
  }
  return 0;
}
 
static dsp_tot(allow_bon_)
int16 allow_bon_;
{
  int16 k,key,z,curs=2;

	redo:;
  scrget(2,253);z=1; scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
  scrfld(z++,25,1);
  scrifld(z++,fm_od7_2,&totaal);
  for(k=0;k<4;k++)scrifld(z++,fm_us75,opm_foot[k]);
  key=scrupd(curs,0x3A2);
	if ((key/0x100)==1) key=(key&0xFF)+5000;
  if(key==102)return 2;
  if(key==106)return NO;
	prt2pdf=NO; if(key==5001) {prt2pdf=YES;key=108;}
  if(allow_bon_ && key==109 && fldlen(8,1)){
    if(scr_ok("Wenst U een leveringsbon te maken van de ingebrachte artikels")==YES){
      conv_lbon(0);
    }
  }
	if(key!=108) goto redo;
  return YES;
}
 
static klt_memo()
{
  int16 z,k,key;
					
  FOREVER{
    redo:;
    scrget(2,122); z=1;
    scrofld(z++,2,3,-1);
    for(k=5;k<9;k++) scrfld(z++,62,k);
    key=scrupd(2,0x80);
    if(key==108) break;
  }
}

static chk_vrij(nr_)
int16 nr_;
{
  int16 k,mode_,z,key,qlines_;
	uint16 dt_;
  float q_used_,qlv_;
	
	if(line[nr_].arec==0 || line[nr_].aantal==0) return YES;
  fasinit(6);*u(6,1)=line[nr_].arec;fasgeti(6);
  fasinit(95);*u(95,3)=*u(6,1);mode_=1; q_used_=0;
	zero((char *)&tb[0].rec,sizeof tb); qlines_=0;
  FOREVER{
    next:;
    if(faskeyi(95,1,mode_)) break; mode_=2;
    if(*u(95,3)!=*u(6,1)) break;
    if(*u(95,6)<dt_uitb && *u(95,7)<dt_uitb) goto next;
    if(*u(95,6)>dt_uite && *u(95,7)>dt_uite) goto next;
    if(*u(95,1)==line[nr_].rec95) goto next;
		q_used_+=*f(95,8);
		tb[qlines_].rec=*u(95,4);tb[qlines_].dt_beg=*u(95,6);tb[qlines_].dt_end=*u(95,7);
    tb[qlines_].q_verh=*f(95,8);
		qlines_++;
  }
	if((q_used_+line[nr_].aantal)>*f(6,45)){ // dag per dag bekijken want mss 2x verhuren in die periode
		for(dt_=dt_uitb;dt_<=dt_uite;dt_++){
			q_used_=0;
		  for(k=0;k<qlines_;k++){
				if(dt_>=tb[k].dt_beg && dt_<=tb[k].dt_end) q_used_+=tb[k].q_verh;
			}
			if((q_used_+line[nr_].aantal)>*f(6,45)) break;
		}
	}
  if((q_used_+line[nr_].aantal)>*f(6,45)){
		redo:;
    scrget(2,249); z=1;
    scrofld(z++,6,3,-1);
    scrifld(z++,fm_uf4_0,f(6,45));
    scrifld(z++,fm_uf4_0,&q_used_);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Toon verhuringen"); 
    qlv_=*f(6,45)-q_used_;
    scrifld(z++,fm_uf4_0,&qlv_);
    scrifld(z++,fm_uf4_0,&line[nr_].aantal);
    key=scrupd(-1,0x81);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001){dsp_1len(*u(6,1),0,dt_uitb,dt_uite); goto redo;}
    return NO;
  }
  endsr:;
  return YES;
}
 
static write_bon()
{
  int16 k;

	fasunlck(-2);
  for(k=0;k<DIMLINE;k++){
		if(line[k].omschr[0] && (line[k].arec || (fldlen(93,13) && line[k].omschr[0]=='*'))){
      fasinit(95);
      *u(95,2)=*u(2,1);*u(95,3)=line[k].arec;
			copy(line[k].omschr,s(95,13),fldlen(95,13));
      *u(95,4)=bonnr;*u(95,5)=uit_dat;*u(95,6)=dt_uitb;*u(95,7)=dt_uite;
      *f(95,8)=line[k].aantal;*f(95,9)=line[k].ehpr;*d(95,10)=line[k].totaal;
      if(line[k].rec95){*u(95,1)=line[k].rec95; errnum=fasupd(95);}
      else errnum=fasadd(95);
    }
    else if(line[k].rec95) {*u(95,1)=line[k].rec95;fasgeti(95);faskill(95);}
  }
	fasunlck(-1);
}

static uint16 hash(nr_)
int16 nr_;
{
  char *ps;
  int16 k;
  uint16 fuval=0;
					
  k=sizeof line[0].code + sizeof line[0].omschr;ps=line[nr_].code;
  while(k--) fuval=fuval*3+*(ps++);
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

static skip_lin(line_)
int16 line_;
{
  while(free>(line_+skip_off)) nextline();
}

static dsp_len()
{
							
  fasinit(2);fasinit(6);inq_klt=0;inq_art=0;
  FOREVER {
    redo:;
    if(inq_len(1,"Raadplegen uitleningen")==NO) break;
    if(inq_klt || inq_art) dsp_1len(inq_art,inq_klt,dt_beg,dt_end);
    else dsp_all();
  }
}

static dsp_1len(i_art_,i_klt_,dat_beg_,dat_end_)
uint16 i_art_,i_klt_,dat_beg_,dat_end_;
{
  int16 key, k,z, key_,mode_,start_,max_,dstu_;
	char bufklt_[1000],bufart_[1000];

	copy(s(2,1),bufklt_,fldlen(2,0)); copy(s(6,1),bufart_,fldlen(6,0));

  scrget(1,6);scrupd(-3,0);
  zero((char *)&tb_recs[0],sizeof tb_recs);
  key_=1; if(i_klt_) key_=2; mode_=1;
  fasinit(95);*u(95,2)=i_klt_;*u(95,3)=i_art_;k=0;
  FOREVER{
    next:;
    if(faskeyi(95,key_,mode_)) break; mode_=2;
    if(i_klt_ && *u(95,2)!=i_klt_) break;
    if(i_art_ && *u(95,3)!=i_art_) {
      if(i_klt_) goto next; else break;
    }
    if(dat_beg_ && *u(95,6)<dat_beg_ && *u(95,7)<dat_beg_) goto next;
    if(dat_end_ && *u(95,6)>dat_end_ && *u(95,7)>dat_end_) goto next;
    tb_recs[k++]=*u(95,1);
    if(k>=DIM_95) break;
  }
  if(k==0) {errnum=14;goto endsr;}
  max_=k;start_=0; if(i_klt_) dstu_=6; else dstu_=2;
  FOREVER{
    scrget(2,250); z=1;
    fasinit(2); if(i_klt_){*u(2,1)=i_klt_;fasgeti(2);}
    scrofld(z++,2,3,-1);
    fasinit(6); if(i_art_){*u(6,1)=i_art_;fasgeti(6);}
    scrofld(z++,6,3,30);
    for(k=start_;k<start_+15;k++){
      if(tb_recs[k]==0) break;
      fasinit(95);*u(95,1)=tb_recs[k];fasgeti(95);
      fasinit(2);*u(2,1)=*u(95,2);fasgeti(2);
      fasinit(6);*u(6,1)=*u(95,3);if(*u(6,1)) fasgeti(6);
			if(*s(6,3)=='\0') copy(s(95,13),s(6,3),fldlen(95,13)); // losse tekst
      k++;scrifld(z++,fm_ou3,&k);k--;
      scrofld(z++,95,5,-1);
      scrofld(z++,95,4,-1);
      scrofld(z++,dstu_,3,30);
      scrofld(z++,95,8,-1);
      scrofld(z++,95,6,-1);
      scrofld(z++,95,7,-1);
    }
    key=scrupd(-1,0x87);
    if(key==101 || key==108) break;
    if(key==102){
      start_-=15; if(start_<=0) start_=0;
    }
    if(key==103){
      start_+=15; if(start_>=max_) start_=max_-15;
			if(start_<=0) start_=0;
    }
		if(start_<0) start_=0;
  }
endsr:;
	copy(bufklt_,s(2,1),fldlen(2,0)); copy(bufart_,s(6,1),fldlen(6,0));
}
 
static dsp_all()
{
  int16 j,n,curs,z,z_base_,key,mode_,mode95_,q_rest_,start_,max_,curspos_;

  scrget(1,7);scrupd(-3,0);
  zero((char *)&tb[0].rec,sizeof tb);fasinit(6);
  start_=0;max_=0;mode_=1;curs=2;
  FOREVER{
    next:;
    if(faskeyi(6,2,mode_)) break; mode_=2;
    if(*f(6,45)<=0) goto next;
    tb[max_].rec=*u(6,1);
    fasinit(95);*u(95,3)=*u(6,1); mode95_=1;
    FOREVER{
      next95:;
      if(faskeyi(95,1,mode95_)) break; mode95_=2;
      if(*u(95,3)!=*u(6,1)) break;
      if(dt_beg && *u(95,6)<dt_beg && *u(95,7)<dt_beg) goto next95;
      if(dt_end && *u(95,6)>dt_end && *u(95,7)>dt_end) goto next95;
			if(dtb_vrh_beg && *u(95,6)<dtb_vrh_beg) goto next95;
			if(dte_vrh_beg && *u(95,6)>dte_vrh_beg) goto next95;
      tb[max_].q_verh+=*f(95,8);
      if(tb[max_].dt_beg==0 || tb[max_].dt_beg>*u(95,6)) tb[max_].dt_beg=*u(95,6);
      if(tb[max_].dt_end==0 || tb[max_].dt_end<*u(95,7)) tb[max_].dt_end=*u(95,7);
    }
    max_++;if(max_>=DIM_TB) break;
  }
  if(max_==0) {errnum=14;goto endsr;}
  start_=0;curs=1;
  FOREVER{
    redo:;
    scrnum=0; scrget(2,261);z=1;
    z_base_=z;
    for(j=start_;j<start_+18;j++){
      if(tb[j].rec==0) break;
      fasinit(6); *u(6,1)=tb[j].rec;fasgeti(6);
      scrfld(z++,6,3);
      q_rest_=*f(6,45)-tb[j].q_verh;
      scrifld(z++,fm_oi5,&q_rest_); if(q_rest_<=0) scrchat(z-1,0x8);
      scrifld(z++,fm_oi5,&tb[j].q_verh);
      scrofld(z++,6,45,-1);
    }
    key=scrupd(curs,0xA7);curs=1;curspos_=fldcurs;
    if(key==106) goto redo;

    if(key==101) break;
    if(key==108 && curspos_>=z_base_){
      n=(curspos_)/4; n+=start_;
      curs=curspos_;
      if(tb[n].rec){
	      if(key==108) dsp_1len(tb[n].rec,0,dt_beg,dt_end);
      }
    }
    if(key==102) start_-=18;
    if(key==103) {start_+=18;if(start_>=max_-18) start_=max_-18;}
    if(start_<0) start_=0;
  }
  endsr:;
}

static WeekOverzicht()
{
  int16 k,z,mode_,kmode_,first_;

  
  fasinit(2);fasinit(6);inq_klt=0;inq_art=0;
  FOREVER {
    if(inq_len(2,"Lijst uitleningen per klant")==NO) break;
		if(Prt2Xls){
			scrget(1,7);scrupd(-3,0);
			XlsRef=OpenXlsFile("Lijst uitleningen per klant",dt_beg,dt_end);
			if(XlsRef<=0) {errnum=1;goto endsr;}
			XlsColumnSize(XlsRef,1,35);
			XlsColumnSize(XlsRef,4,35);
			StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
			StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
			StylGrpTot=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_BEIGE,1,1,0,NO,NO);
			StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
			StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
			StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
			XlsRij=1;XlsKol=1;
			XlsWrite(XlsRef,0,XlsKol++,0,"Klant",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Bonnr",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Datum",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Artikel",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Aantal",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Begin",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Einde",0);
			XlsRij++;
			goto no_header;
		}
    scrget(1,6);scrupd(-3,0);
		getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
    if((errnum=prtopen(prtnr,form_dat,6,96,pr_mode,4))!=0) goto endsr;
		p_pdfname("Lijst uitleningen per klant",dt_beg,dt_end);
    free=999;
    prtfld(25,1,30); prttext("<t35b>Lijst uitleningen per klant<b><t75>");
    prtifld(fm_udat,u(25,2),-1); prttext("<t88>");prttext("Blz.<ppp>.");
    prtbuf(1);
    z=1;
    prttab(z,2,3,1,30); prttitle(z++,"Klant",3);
    prttab(z,95,4,1,-1); prttitle(z++,"Bonnr",0x13);
    prttab(z,95,5,1,-1); prttitle(z++,"Datum",0x13);
    prttab(z,6,3,3,25); prttitle(z++,"Artikel",3);
    prttab(z,95,8,1,-1); prttitle(z++,"Aantal",0x13);
    prttab(z,95,6,1,-1); prttitle(z++,"Begin",0x43);
    prttab(z,95,7,1,-1); prttitle(z++,"Einde",0x43);
    prtbuf(3);
		no_header:;
		fasinit(2); if(inq_klt){*u(2,1)=inq_klt;fasgeti(2);} kmode_=1;
		FOREVER{
			if(faskeyi(2,2,kmode_)) break; kmode_=2;
			if(inq_klt && *u(2,1)!=inq_klt) break;
			first_=YES;	mode_=1;
			fasinit(95);*u(95,2)=*u(2,1);*u(95,3)=inq_art;
			FOREVER{
				next:;
				if(faskeyi(95,2,mode_)) break; mode_=2;
				if(*u(95,2)!=*u(2,1)) break;
				if(inq_art && *u(95,3)!=inq_art) goto next;
				if(dt_beg && *u(95,7)<dt_beg) goto next; // einddatum < begin
				if(dt_end && *u(95,6)>dt_end) goto next;
				if(dtb_vrh_beg && *u(95,6)<dtb_vrh_beg) goto next;
				if(dte_vrh_beg && *u(95,6)>dte_vrh_beg) goto next;
				fasinit(6);*u(6,1)=*u(95,3);fasgeti(6);
				if(*s(6,3)=='\0') copy(s(95,13),s(6,3),fldlen(95,13)); // losse tekst
				if(Prt2Xls){
					XlsKol=1;
					WriteFld2Xls(XlsRij,XlsKol++,2,3,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,95,4,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,95,5,StylDate);
					WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,95,8,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,95,6,StylDate);
					WriteFld2Xls(XlsRij,XlsKol++,95,7,StylDate);
					XlsRij++;
				}
				else{
				  k=2; if(first_){k=1; first_=NO;}
				  for(k;k<20;k++) prtinfo(k,0);nextline();
				}
			}
    }
		if(Prt2Xls) XlsClose(XlsRef,1);
		else{ prtform(0); prtclose();}
  }
  endsr:;
}
 
static prt_len()
{
  int16 k,z,key_,mode_;

  
  fasinit(2);fasinit(6);inq_klt=0;inq_art=0;
  FOREVER {
    if(inq_len(2,"Lijst uitleningen")==NO) break;
		if(Prt2Xls){
			scrget(1,7);scrupd(-3,0);
			XlsRef=OpenXlsFile("Lijst uitleningen",dt_beg,dt_end);
			if(XlsRef<=0) {errnum=1;goto endsr;}
			XlsColumnSize(XlsRef,3,35);
			XlsColumnSize(XlsRef,4,35);
			StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
			StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
			StylGrpTot=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_BEIGE,1,1,0,NO,NO);
			StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
			StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
			StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
			XlsRij=1;XlsKol=1;
			XlsWrite(XlsRef,0,XlsKol++,0,"Bonnr",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Datum",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Klant",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Artikel",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Aantal",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Begin",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Einde",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Eh.prijs",0);
			XlsWrite(XlsRef,0,XlsKol++,0,"Totaal",0);
			XlsRij++;
			goto no_header;
		}
    scrget(1,6);scrupd(-3,0);
		getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
		p_pdfname("Lijst uitleningen",dt_beg,dt_end);
    free=999;
    prtfld(25,1,-1); prttext("<t50eb>Lijst uitleningen<eb><t95>");
    prtfld(25,2,-1); prttext("<t120>");prttext("Blz.<ppp>.");
    prtbuf(1);
    z=1;
    prttab(z,95,4,1,-1); prttitle(z++,"Bonnr",0x13);
    prttab(z,95,5,1,-1); prttitle(z++,"Datum",0x13);
    prttab(z,2,3,1,35); prttitle(z++,"Klant",3);
    prttab(z,6,3,3,30); prttitle(z++,"Artikel",3);
    prttab(z,95,8,3,-1); prttitle(z++,"Aantal",0x13);
    prttab(z,95,6,1,-1); prttitle(z++,"Begin",0x13);
    prttab(z,95,7,1,-1); prttitle(z++,"Einde",0x13);
    prttab(z,95,9,1,-1); prttitle(z++,"Eh.prijs",0x13);
    prttab(z,95,10,1,-1); prttitle(z++,"Totaal",0x13);
    prtbuf(3);
		no_header:;
    key_=1; if(inq_klt) key_=3; mode_=1;
    fasinit(95);*u(95,2)=inq_klt;*u(95,3)=inq_art;k=0;
    FOREVER{
      next:;
      if(faskeyi(95,key_,mode_)) break; mode_=2;
      if(inq_klt && *u(95,2)!=inq_klt) goto next;
      if(inq_art && *u(95,3)!=inq_art) goto next;
      if(dt_beg && *u(95,6)<dt_beg && *u(95,7)<dt_beg) goto next;
      if(dt_end && *u(95,6)>dt_end && *u(95,7)>dt_end) goto next;
			if(dtb_vrh_beg && *u(95,6)<dtb_vrh_beg) goto next;
			if(dte_vrh_beg && *u(95,6)>dte_vrh_beg) goto next;
      fasinit(2);*u(2,1)=*u(95,2);fasgeti(2);
      fasinit(6);*u(6,1)=*u(95,3);fasgeti(6);
			if(*s(6,3)=='\0') copy(s(95,13),s(6,3),fldlen(95,13)); // losse tekst
			if(Prt2Xls){
				XlsKol=1;
        WriteFld2Xls(XlsRij,XlsKol++,95,4,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,95,5,StylDate);
				WriteFld2Xls(XlsRij,XlsKol++,2,3,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,95,8,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,95,6,StylDate);
				WriteFld2Xls(XlsRij,XlsKol++,95,7,StylDate);
				WriteFld2Xls(XlsRij,XlsKol++,95,9,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,95,10,StylNormal);
				XlsRij++;
			}
			else{
        for(k=0;k<20;k++) prtinfo(k,0);nextline();
			}
    }
		if(Prt2Xls) XlsClose(XlsRef,1);
		else{
      prtform(0);  prtclose();
		}
  }
  endsr:;
}

static OpenXlsFile(text_,bdatum_,edatum_)
char *text_;
unsigned bdatum_,edatum_;
{
	int16 pos_,dd,mm,yy;
  char string[100];
				
  zero(string,sizeof string);
	pos_=copy0(text_,&string[0],30);
  if(bdatum_){
    string[pos_++]=' ';
    jddate(bdatum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
  if(edatum_){
    if(edatum_){copy(" - ",&string[pos_],3);pos_+=3;}
    jddate(edatum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
	pos_+=copy0(".XLSX",&string[pos_],4);
	
  pos_=XlsCreate(string);
	return pos_;
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}

static kil_len()
{
  uint16 n,g;
				
  fasinit(2);fasinit(6);inq_klt=0;inq_art=0;dt_end=0;dt_beg=0;
  if(inq_len(3,"Schrappen verouderde uitleningen")==NO) goto endsr;
  if(scr_ok("Wenst U echt de geselecteerde verhuringen te schrappen ????")==NO) goto endsr;
  scrget(1,7);scrupd(-3,0);
  fasinit(95);*u(95,2)=inq_klt;*u(95,3)=inq_art;
  n=0;scrnum=0;fasunlck(-2);
  FOREVER{
    next:;
    *u(95,1)=++n;
    g=fasgeti(95);
    if(g==47)break;
    if(g!=46){
      if(inq_klt && *u(95,2)!=inq_klt) goto next;
      if(inq_art && *u(95,3)!=inq_art) goto next;
      if(dt_beg && *u(95,6)<dt_beg && *u(95,7)<dt_beg) goto next;
      if(dt_end && *u(95,6)>dt_end && *u(95,7)>dt_end) goto next;
			if(dtb_vrh_beg && *u(95,6)<dtb_vrh_beg) goto next;
			if(dte_vrh_beg && *u(95,6)>dte_vrh_beg) goto next;
      faskill(95);
    }
  }
	fasunlck(-1);
  endsr:;
}
 
static inq_len(mode_,ptitel_)
int16 mode_;/* 1=raadplegen, 2=afdrukken, 3=schrappen */
char *ptitel_;
{
  int16 key,z,curs=3;

  FOREVER {
    fasinit(2);if(inq_klt){*u(2,1)=inq_klt;fasgeti(2);}
    fasinit(6);if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
    redo:
    scrget(2,248); z=1; 
		if(mode_==2){
			scraddpicto(3,0,76,22,4,2,583,0,0,"Maak PDF"); 
			scraddpicto(4,0,72,22,4,2,573,0,0,"Maak XLS"); 
		}
		DisplayMenuTitel(3,ptitel_,0xA);
    scrfld(z++,25,1);
    if(mode_==1) scrifld(z++,fm_os13,"te raadplegen");
    else if(mode_==2) scrifld(z++,fm_os13,"af te drukken");
    else if(mode_==3) scrifld(z++,fm_os13,"TE SCHRAPPEN !");
    scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrfld(z++,6,3);scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_udat,&dt_beg);scrifld(z++,fm_udat,&dt_end);
		scrifld(z++,fm_udat,&dtb_vrh_beg);scrifld(z++,fm_udat,&dte_vrh_beg);
		if(mode_==1){
			scraddf(100,18,5,0); scrifld(100,VarTextFmt(75,0),"Ps. U krijgt een overzicht van ALLE beschikbare materialen");
			scraddf(101,19,5,0); scrifld(101,VarTextFmt(75,0),"    als u GEEN klant/artikel invult.");
		}
    key=scrupd(curs,0x05E1);curs=3;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==111) ovlexit(*u(25,4));
    if (key==101) return NO;
    if(key==5001 || *s(2,3)){
			z=0; if(key==5001) z=98;
      if (search(2,z)) goto redo;
    } else fasinit(2);
 
    if(key==5002 || *s(6,3)){
			z=0; if(key==5002) z=98;
      if (search(6,z)){curs=4;goto redo;}
    } else fasinit(6);
    inq_klt=*u(2,1);inq_art=*u(6,1);
    if(mode_==1 && inq_klt==0 && inq_art==0 && dt_beg==0) {curs=5;errnum=38;goto redo;} 
    if(mode_==3 && dt_end==0){curs=6;errnum=38;goto redo;}
		prt2pdf=NO; if(key==5003 && mode_==2) {prt2pdf=YES;key=108;}
		Prt2Xls=NO; if(key==5004 && mode_==2) {Prt2Xls=YES;key=108;}
    if(key==108) break;
  }
  return YES;
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


static bin_len()
{
  int16 key, k,z, curs=2,key_,mode_,start_,max_;

  fasinit(2);fasinit(6);inq_klt=0;inq_art=0; bonnr=0;
  FOREVER {
    fasinit(2);if(inq_klt){*u(2,1)=inq_klt;fasgeti(2);}
    fasinit(6);if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
    redo:
    scrget(2,251); z=1;
    scrfld(z++,25,1);
    scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_uu5,&bonnr);
    key=scrupd(curs,0x04E1);curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if (key==101 || key==111) goto endsr;
    if(key==5001 || *s(2,3)){
			z=0;if(key==5001) z=98;
			if (search(2,z)) goto redo;
    } else fasinit(2);
 
    inq_klt=*u(2,1);inq_art=*u(6,1);
    if(inq_klt==0 && bonnr==0) {errnum=38;goto redo;}
    if(key!=108) goto redo;
    scrget(1,6);scrupd(-3,0);
    zero((char *)&tb_recs[0],sizeof tb_recs);
    key_=2; if(bonnr) key_=3; mode_=1;
    fasinit(95);*u(95,2)=inq_klt;*u(95,4)=bonnr;k=0;
    FOREVER{
      next:;
      if(faskeyi(95,key_,mode_)) break; mode_=2;
      if(bonnr && *u(95,4)!=bonnr) break;
      if(inq_klt && *u(95,2)!=inq_klt) {
	if(bonnr) goto next; else break;
      }
      tb_recs[k++]=*u(95,1);
      if(k>=DIM_95) break;
    }
    if(k==0) {errnum=14;goto redo;}
    max_=k;start_=0;
    fasinit(2);
    if(inq_klt){*u(2,1)=inq_klt;fasgeti(2);}
    else{
      *u(95,1)=tb_recs[0];fasgeti(95);
      *u(2,1)=*u(95,2);fasgeti(2);
    }
    zero(tb_lever,sizeof tb_lever);
    for(k=0;k<max_;k++) tb_lever[k]='J';
    FOREVER{
      scrnum=0;scrget(2,252); z=1;
      scrofld(z++,2,3,-1);
      scrifld(z++,fm_ou5,&bonnr);
      for(k=start_;k<start_+15;k++){
				if(tb_recs[k]==0) break;
				fasinit(95);*u(95,1)=tb_recs[k];fasgeti(95);
				fasinit(6);*u(6,1)=*u(95,3);fasgeti(6);
				if(*s(6,3)=='\0') copy(s(95,13),s(6,3),fldlen(95,13)); // losse tekst
				scrifld(z++,fm_uJN,&tb_lever[k]);
				scrofld(z++,95,5,-1);
				scrofld(z++,95,4,-1);
				scrofld(z++,6,3,30);
				scrofld(z++,95,8,-1);
				scrofld(z++,95,6,-1);
				scrofld(z++,95,7,-1);
	    }
      key=scrupd(1,0x287);
      if(key==101) goto endsr;
      if(key==102){
				start_-=15; if(start_<=0) start_=0;
      }
      if(key==103){
				start_+=15; if(start_>=max_) start_=max_-15;
				if(start_<=0) start_=0;
      }
      if(key==108 && fldlen(8,1)){
				if(scr_ok("Wenst U een leveringsbon te maken van de ingebrachte artikels ?")){
					conv_lbon(1); wis_uit(); break;
				}
      }
      if(key==110){
				if(scr_ok("Wenst U de ingebrachte artikels te wissen ?")){
					wis_uit(); break;
				}
      }
    }
  }
  endsr:;
}
 
static wis_uit()
{
  int16 k;
						
  scrget(1,7);scrupd(-3,0);fasunlck(-2);
  for(k=0;k<DIM_95;k++){
    if(tb_lever[k]=='J' && tb_recs[k]){
      fasinit(95);*u(95,1)=tb_recs[k]; fasgetu(95);
      faskill(95);
    }
  }
	fasunlck(-1);
}

static conv_lbon(mode_)/* 0=alles , 1=geleverde */
{
  int16 j,k,yy,mm,dd,max_,len_;
  uint16 last_b_,last_e_;
  char def_inc;

  scrget(1,7);scrupd(-3,0);
	fasunlck(-2);
  if(mode_){
    for(k=0;k<DIM_95;k++){
      if(tb_lever[k]=='J' && tb_recs[k]) break;
    }
    if(k>=DIM_95) goto endsr;
  }
  k=*s(2,26)-'0'; if(k<0 || k>9) k=0;
  def_inc='N';if(sys3894 & (1<<k)) def_inc='J';
  fasinit(8);
  *s(8,22)='N';
  *s(8,26)='N';
  if(fldlen(8,23)) copy(def_munt,s(8,23),3);
  *u(8,28)=1;
  *u(8,8)=*u(25,2);
  *u(8,3)=*u(2,1);
  for(k=0;k<4;k++) copy(s(2,3+k),s(8,14+k),fldlen(8,14+k));
  sysget(3718,2,&last_vf); last_vf++;  *u(8,2)=last_vf;  sysput(3718,2,&last_vf);
  if(fldlen(8,33)){
    if(fldlen(2,35) && *s(8,33)=='\0') *s(8,33)=*s(2,35);
  }
	if(fldlen(8,70)) *u(8,70)=procid;
	if(fldlen(8,72)) *u(8,72)=*u(25,2);
  errnum=fasadd(8); j=0; last_b_=0xFFFF; last_e_=0xFFFF;
 
  max_=DIMLINE; if(mode_) max_=DIM_95;
  for(k=0;k<max_;k++){
    if(mode_==0){
      if(line[k].omschr[0] && (line[k].arec || (fldlen(93,13) && line[k].omschr[0]=='*'))){
				fasinit(95);
				*u(95,2)=*u(2,1);*u(95,3)=line[k].arec;
				*u(95,4)=bonnr;*u(95,5)=uit_dat;*u(95,6)=dt_uitb;*u(95,7)=dt_uite;
				*f(95,8)=line[k].aantal;*f(95,9)=line[k].ehpr;*d(95,10)=line[k].totaal;
				copy(line[k].omschr,s(95,13),fldlen(95,13));
      }
      else continue;
    }
    else{
      if(tb_lever[k]!='J' || tb_recs[k]==0) continue;
      fasinit(95);*u(95,1)=tb_recs[k];fasgeti(95);
    }
    if(*u(95,6)!=last_b_ || *u(95,7)!=last_e_){
      fasinit(58); *u(58,2)=*u(8,1);*u(58,3)=j++;
      *s(58,16)='*'; errnum=fasadd(58);
      fasinit(58); *u(58,2)=*u(8,1);*u(58,3)=j++;
      copy("*Periode : ",s(58,16),11);
      jddate(*u(95,6),&yy,&mm,&dd); yy=yy%100;
      stcli_d(s(58,16)+11,(long)dd,2,0);*(s(58,16)+13)='/';
      stcli_d(s(58,16)+14,(long)mm,2,0);*(s(58,16)+16)='/';
      stcli_d(s(58,16)+17,(long)yy,2,0);*(s(58,16)+19)='-';
      jddate(*u(95,7),&yy,&mm,&dd); yy=yy%100;
      stcli_d(s(58,16)+20,(long)dd,2,0);*(s(58,16)+22)='/';
      stcli_d(s(58,16)+23,(long)mm,2,0);*(s(58,16)+25)='/';
      stcli_d(s(58,16)+26,(long)yy,2,0);
      errnum=fasadd(58);
      fasinit(58); *u(58,2)=*u(8,1);*u(58,3)=j++;
      *s(58,16)='*'; errnum=fasadd(58);
      last_b_=*u(95,6);last_e_=*u(95,7);
    }
    fasinit(6);*u(6,1)=*u(95,3);if(*u(6,1)) fasgeti(6);
    fasinit(58);
    *u(58,2)=*u(8,1); *u(58,3)=j++;
    copy(s(6,2),s(58,15),fldlen(58,15));
    *u(58,14)=*u(6,1);
    copy(s(6,3),s(58,16),fldlen(58,16));
	len_=fldlen(95,13); if(fldlen(58,16)<len_) len_=fldlen(58,16);
		if(*s(58,16)=='\0' && fldlen(95,13)) copy(s(95,13),s(58,16),len_);
    *f(58,24)=*f(6,28);
    if(fldlen(58,25) && fldlen(6,39)) copy(s(6,39),s(58,25),fldlen(58,25));
    if(fldlen(6,40) && fldlen(58,26)) *l(58,26)=*l(6,40);
    *i(58,34)=*i(6,9);
    if(fldlen(58,27)) *s(58,27)=def_inc;
    if(fldlen(6,38) && fldlen(58,13)) *f(58,13)=*f(6,38);
    if(fldlen(58,8)) {*f(58,8)=*f(6,83); if(*f(58,8)==0) *f(58,8)=1;}
    if(fldlen(58,12)) copy(s(6,10),s(58,12),fldlen(58,12));
    if(fldlen(58,50)) *f(58,50)=*f(6,84);
    if(fldlen(58,51)) *i(58,51)=*i(6,85);
    if(fldlen(58,54)) *f(58,54)=*f(6,83);
    if(fldlen(58,63)){*f(58,63)=*f(6,31);if(*f(58,63)==0) *f(58,63)=1;}
    *f(58,7)=*f(95,8);*f(58,31)=*f(95,8);
    *f(58,20)=*f(95,9);*l(58,32)=*d(95,10);
    *d(58,35)=*d(95,10);
    errnum=fasadd(58);
  }
endsr:;
	fasunlck(-1);
}
 
static scr_ok(ptxt)
char *ptxt;
{
  int16 key;

  scrget(1,169);
  scrifld(12,fm_os79,ptxt);
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  return NO;
}
 
static print_bon()
{
  int16 j,k;
  char *ps;

  getsysprNew(15,form_dat,&pr_mode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if (prtopen(prtnr,form_dat,6,80,pr_mode,0)!=0) {return YES;}
	p_pdfname("Uitlening",uit_dat,0);
  scrget(1,6);scrupd(-3,0);

  de_heer(2);
  prttext("<t1><eb>");prtifld(fm_os79,&firma[0],30);prttext("<eb>");nextline();
  prttext("<t1>");prtifld(fm_os79,&firma[31],25);nextline();
  prttext("<t1>");prtifld(fm_os79,&firma[57],7);prtblank(2);
  prtifld(fm_os79,&firma[65],20);nextline();
  if(free-skip_off>66) nextline();
  for(k=0;k<9;k++){
    if(firma[firm[k].begpos]){
      prttext("<t1>");ps=firm[k].txt[taaltxt];prttext(ps);
      for(j=0;j<12;j++) if(*ps++=='\0') break;
      for(;j<12;j++) prtblank(1);prttext(": ");
      prtifld(fm_os79,&firma[firm[k].begpos],firm[k].lengte);
      nextline();
    }
  }

  skip_lin(60);
  prttext("<t47>");prtifld(fm_os38,nm_dehr,-1);nextline();
  prttext("<t47>");prtfld(2,4,-1);nextline();
  prttext("<t47>");prtfld(2,5,-1);prttext(" ");prtfld(2,6,-1);nextline();
  skip_lin(54);
  prttext("<b>Uitlening<b>");
  nextline();nextline();
  prttext("<t23>BTW nr.<t41>Klant<t55>Nummer<t71>Datum");
  nextline();
  skip_lin(51);
  if(*l(2,10) && *l(2,10)!=999999999L){
    prttext("<t23>BE ");prtfld(2,10,-1);
  }
  else if(fldlen(2,22)){
    prttext("<t21>");prtfld(2,22,-1);
  }
  prttext("<t41>");
  k=1; if(klcd) k=2;
  prtfld(2,k,-1);
  prttext("<t56>");
  prtifld(fm_uu5,&bonnr,-1);prttext("<t69>");prtifld(fm_udat,&uit_dat,-1);
  nextline(); nextline();
  skip_lin(47);
  prttext("<u>Art.<ut7u>Omschrijving<ut39u>Aant<ut48u>Eh.Prijs<u>");nextline();
  nextline();
  prttext("<t7b>Uitleenperiode : ");prtifld(fm_udat,&dt_uitb,-1);
  prttext(" t.e.m. ");prtifld(fm_udat,&dt_uite,-1);nextline();nextline();
  for(k=0;k<DIMLINE;k++){
		if(line[k].arec || (fldlen(95,13) && line[k].omschr[0]=='*')){
      fasinit(6);*u(6,1)=line[k].arec;fasgeti(6);
			if(*s(6,3)=='\0') copy(line[k].omschr,s(6,3),fldlen(6,3)); // losse tekst
      prtfld(6,2,-1);
      prttext("<t7>");
      prtfld(6,3,30);
      prttext("<t36>");
      prtifld(fm_uf4_0,&line[k].aantal,-1);
      prttext("<t45>");prtifld(fm_uf6_2,&line[k].ehpr,-1);
      nextline();
    }
  }
  nextline(); nextline();
  for(k=0;k<4;k++){
    if(opm_foot[k][0]) {prttext(opm_foot[k]);nextline();}
  }
#if FLAGSMM
  if(fldlen(2,65) && *s(2,65)){
    prttext("<b>"); prtfld(2,65,-1); prttext("<b>");nextline();
  }
#endif
	skip_lin(16);
	for(k=0;k<4;k++){
		if(StdTekst[k][0]) {prtifld(VarTextFmt(75,0),StdTekst[k],-1);nextline();}
  }
	skip_lin(10);
	prttext("<t1><bu>Klaargezet+controle<bu><t25bu>Afgeleverd<bu><t45bu>Opgehaald<bu><t65bu>Nacontrole<bu>");nextline();nextline();
	prttext("<t1>..................<t22>..................<t42>..................<t62>..................");nextline();
	skip_lin(6);
	prttext("<t1>Opmerkingen :");nextline();
	//skip_lin(8);
	//prttext("<t1>Klaargezet door :");nextline();nextline();
	//prttext("<t1>Afgeleverd door :");nextline();nextline();
	//prttext("<t1>Opgehaald door :");nextline();
  prtform(0);
  prtclose();
  endsr:;
  return NO;
}
 
static de_heer(stu_)
int16 stu_;
{
  int16 g,j,k,len;

  len=fldlen(stu_,3);if(len>50) len=50;
  for(k=0;k<52;k++) nm_dehr[k]='\0';
  for(k=0;k<len-1;k++){
    if(*(s(stu_,3)+k)=='*')break;
  }
  if(k==len-1) {/* no * */
    copy(s(stu_,3),nm_dehr,len);
  }
  else {
    for(g=k+1;g<len;g++) if(*(s(stu_,3)+g)!=' ') break;
    if(g>=len) copy(s(stu_,3),nm_dehr,len);
    else {
      for(j=len-1;j>=g;j--) if(*(s(stu_,3)+j)>' ') break;
      j=j-g+1;
      copy(s(stu_,3)+g,nm_dehr,j);
      nm_dehr[j++]=' ';
      g=len-j;if(g>(k-1)) g=k-1;
      copy(s(stu_,3),&nm_dehr[j],g);
    }
  }
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


static initload()
{
  fasunlck(0);
  fileopen(2);
  fileopen(6);
  fileopen(8);
  fileopen(9);


  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);
	if(firma[101] && firma[256]){ // IBAN bij voorkeur gebruiken voor rekeningnummer
		copy(&firm[8].begpos,&firm[3].begpos,sizeof firm[0]); 
		firm[8].begpos+=41; // om IBAN te misleiden
	}
  sysget(294,4,def_munt);
  sysget(1918,2,&sear_stt);
  sysget(1920,244,sys1920);
  sysget(2208,2,&skip_off);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(4608,2,&sys4608);
	sysget(19700,300,StdTekst);
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
    if(errnum=fasopen(filename,0)) ovlexit(*u(25,4));
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
    if(stu_==6) {arcd=YES; if(faskeyi(6,1,0)==45) arcd=NO;}
  }
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
  if(upd_mode) parmcall[7]=0x04; else parmcall[7]=0x0C;  // geblokkeerde klanten weigeren bij nieuwe bon
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}

