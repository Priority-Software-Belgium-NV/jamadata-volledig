/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0205GetD() {return &zzvw;}
#include "OvlShare.h"

extern char *VarTextFmt(int len_,int update_);

#define ovldat DRK0205dat
#define ovlcod DRK0205cod
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

char ovldat[] = "drk0205  00:04 25/02/09 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16


extern uint16 *u();

static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us6[]   = {7,0xC8,6,0,0,0,0};
static char fm_us6U[]   = {7,0xC8,6,0,1,0,0};
static char fm_us2U[]   = {7,0xC8,2,0,1,0,0};
static char fm_us2[]   = {7,0xC8,2,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_uu2_[]   = {6,0xD0,2,0,0x00,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_ui3[]   = {6,0xD1,3,0,0x60,0};
static char fm_ui2[]   = {6,0xD1,2,0,0x60,0};
static char fm_ui3_s[] = {6,0xD1,3,0,0x20,0};
static char fm_ui2_s[] = {6,0xD1,2,0,0x20,0};
static char fm_ui1[]   = {6,0xD1,1,0,0x60,0};
static char fm_uf3_4[] = {6,0xD4,3,4,0x30,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x60,0};
static char fm_uf21s[] = {6,0xD4,2,1,0x20,0};
static char fm_of2_1[] = {6,0x94,2,1,0x60,0};
static char fm_of21s[] = {6,0x94,2,1,0x20,0};
static char fm_ugrb[]  = {2,0xE8};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_u_DJN[] = {13,0xC8,1,0,1,0,'D','D','J','J','N','N',0};
static char fm_u_BNP[] = {13,0xC8,1,0,1,0,'B','B','%','%','N','N',0};
static char fm_u_NBGFEI[]= {15,0xC8,1,0,1,0,'N','N','B','B','G','G','F','F','E','E','I','I',0};
static char fm_u_EI[]  = {11,0xC8,1,0,1,0,'E','E','I','I',0};
static char fm_u_AO[]  = {11,0xC8,1,0,1,0,'A','A','O','O',0};
static char fm_u_ABV[] = {11,0xC8,1,0,1,0,'A','B','V','V',0};

static char b[1000];
static int16 skip_off;
static flag updated=NO;
static int16 def_taal;

static char xon_char[2];
static flag use_xon;
char PeppolUidOUT[40],PeppolPwOUT[15],PeppolLicOUT[60],PeppolUidIN[40],PeppolPwIN[15],PeppolLicIN[60],PeppolFirmaNaam[50],PeppolBoekApart;
int PeppolProviderOUT, PeppolProviderIN;

ovlcod()
{
  initload();fasunlck(-1);
  upd1();
  ovl_exit(-1);
}

static upd1()
{
  int16 curs,k,key,z,ok_33_,ok_2240_,pos_;
  int16 oms_t[4],sys3894,sys3926,sys,credt_allow;
	uint16 dt_lastcheck_,jj_,mm_,dd_,hh_,min_,ss_;
  float afrond_bd,v_afrond[10],btw_[10];
  char talen[4],taal_i,vp_ei[11],afv,ao_,av_,hkost_,vptekst[100],stuksprx[10];
	char sys2994,sys2993,mappeppol_[51],mapKopiepeppolOUT_[51],mapKopiepeppolIN_[25],CheckPeppolKlant;
	long grb_peppol_[10],uur_lastcheck_;
 
  if(taal()) goto endsr;
	ok_33_=ovltest(33); ok_2240_=ovltest(2240);
  sysget(3584,312,&b[584]);
	sysget(2993,1,&sys2993);
	sysget(2994,1,&sys2994);
  oms_t[0]=0;
  for(k=1;k<4;k++) {if(fldlen(6,3+k)){oms_t[k]=1;oms_t[0]=1;} else oms_t[k]=0;}
  if(oms_t[0]){
    sysget(2212,4,talen);
    taal_i=talen[b[584]];
  }
//  for(k=0;k<6;k++){ if(b[894]&(1<<k)) vp_ei[k]='I';else vp_ei[k]='E';}
  afv='N'; if(b[596]==1)afv='F'; if(b[596]==2)afv='E'; if(b[596]==3)afv='I';
  if(b[596]==4)afv='B'; if(b[596]==5)afv='G';
	if(b[652]==1) hkost_='B'; else if(b[652]==2) hkost_='%'; else hkost_='N';
  afrond_bd=*(float *)&b[614];
  ao_='A'; if(b[618]) ao_='O';
  if(b[586]==1) av_='V';
  else if(b[586]==2) av_='B';
  else av_='A';
  curs=1;
  redo_181:
  scrget(2,181);z=1;
  if(oms_t[0]) scrifld(z++,fm_us1_U,&taal_i); else streepje(z++);
  if(fldlen(6,15)) c_10_jn(z++,&b[588]); else streepje(z++);
	c_10_jn(z++,&b[592]);
  c_10_jn(z++,&b[624]);
  c_10_jn(z++,&b[594]);
#if 0
  for(k=0;k<6;k++) {
    if(fldlen(6,PrNrs[k])) scrifld(z++,fm_u_EI,&vp_ei[k]);
    else streepje(z++);
  }
#endif
  scrifld(z++,fm_u_NBGFEI,&afv);
  scrifld(z++,fm_uf3_4,&afrond_bd);
  scrifld(z++,fm_u_AO,&ao_);
	scrifld(z++,fm_u_05,&sys2994);
  scrifld(z++,fm_u_BNP,&hkost_);
  scrifld(z++,fm_u_ABV,&av_);
	scrifld(z++,fm_u_JN,&sys2993);
  key=scrupd(curs,0x04A1);curs=1;
  if(key!=106){
    updated=YES;
    if(oms_t[0]){
      for(k=0;k<4;k++) if(talen[k]==taal_i) {*(uint16 *)&b[584]=k;break;}
      if(k==4) {errnum=34;curs=1;goto redo_181;}
    }
    else *(uint16 *)&b[584]=0;
    c_jn_10(&b[588]);
		c_jn_10(&b[592]);
    c_jn_10(&b[594]);
    c_jn_10(&b[624]);
    //*(uint16 *)&b[894]=0;
    //for(k=0;k<10;k++) {
    //  if(vp_ei[k]=='I') b[894]=b[894] | (1<<k);
    //}
		if(hkost_=='B') b[652]=1; else if(hkost_=='%') b[652]=2; else b[652]=0;
    if(afv=='F') *(uint16 *)&b[596]=1; else if(afv=='E') *(uint16 *)&b[596]=2;
      else if(afv=='I') *(uint16 *)&b[596]=3;
      else if(afv=='B') *(uint16 *)&b[596]=4;
      else if(afv=='G') *(uint16 *)&b[596]=5; else *(uint16 *)&b[596]=0;
    *(float *)&b[614]=afrond_bd;
    if(ao_=='O') *(uint16 *)&b[618]=1; else *(uint16 *)&b[618]=0;
    if(av_=='V') *(uint16 *)&b[586]=1;
    else if(av_=='B') *(uint16 *)&b[586]=2;
    else *(uint16 *)&b[586]=0;
    sysput(3584,312,&b[584]);
		sysput(2993,1,&sys2993);
		sysput(2994,1,&sys2994);
  }
  if(key==111) ovl_exit(0);
  if(key==101) goto endsr;

  sysget(4610,60,vptekst);
  sysget(4670,6,stuksprx);
  sysget(4740,40,&vptekst[60]);
  sysget(4780,4,&stuksprx[6]);

  sysget(3894,2,(char *)&sys3894);

  for(k=0;k<10;k++){ if(sys3894&(1<<k)) vp_ei[k]='I';else vp_ei[k]='E';}
  for(k=0;k<6;k++) sysget(2830+k*4,4,(char *)&v_afrond[k]);
	for(k=0;k<4;k++) sysget(3654+k*4,4,(char *)&v_afrond[6+k]);
  for(k=0;k<6;k++) if(v_afrond[k]) break;
  if(k>=6 && afrond_bd){/* eerste gebruik : afrondingen invullen */
    for(k=0;k<6;k++) v_afrond[k]=afrond_bd;
  }
	sysget(3584,312,&b[584]);
  redo_183:
  scrget(2,183);z=1;
  for(k=0;k<6;k++){
    scrifld(z++,fm_us6U,&vptekst[k*10]);
    scrifld(z++,fm_u_JN,&stuksprx[k]);
    scrifld(z++,fm_u_EI,&vp_ei[k]);
    scrifld(z++,fm_uf3_4,&v_afrond[k]);
  }
	if(fldlen(6,185)){
		for(k=6;k<10;k++){
			scrifld(z++,fm_us6U,&vptekst[k*10]);
			scrifld(z++,fm_u_JN,&stuksprx[k]);
			scrifld(z++,fm_u_EI,&vp_ei[k]);
			scrifld(z++,fm_uf3_4,&v_afrond[k]);
		}
	}
  key=scrupd(1,0x04A1);
  if(key!=106){
    updated=YES;
    sysput(4610,60,vptekst);
    sysput(4670,6,stuksprx);
    sysput(4740,40,&vptekst[60]);
    sysput(4780,4,&stuksprx[6]);
//    sysput(4610,66,&b[610]);
    sys3894=0;
    for(k=0;k<10;k++) {
      if(vp_ei[k]=='I') sys3894=sys3894 | (1<<k);
    }
    sysput(3894,2,&sys3894);
    for(k=0;k<6;k++) sysput(2830+k*4,4,(char *)&v_afrond[k]);
		for(k=0;k<4;k++) sysput(3654+k*4,4,(char *)&v_afrond[6+k]);
  }
  if(key==111) ovl_exit(0);
  if(key==101) goto endsr;

  sysget(1048,100,&b[48]);
  sysget(2192,16,&b[192]);
  sysget(3584,300,&b[584]);
  sysget(2208,2,&skip_off);
	sysget(2706,2,xon_char);
	sysget(3926,2,&sys3926);

  curs=1;
redo_182:

  scrget(2,182);z=1;
  scrifld(z++,fm_uf21s,&b[48]);/* 1e btw wel 0 display */
  for(k=1;k<8;k++) scrifld(z++,fm_uf2_1,&b[48+k*4]);
  if(use_xon) scrifld(z++,fm_us2U,xon_char); else z++;
  for(k=0;k<8;k++) scrifld(z++,fm_ui2,&b[192+k*2]);
  if(fldlen(6,28)) scrifld(z++,fm_uf21s,&b[84]); else streepje(z++);
  if(fldlen(6,39)) scrifld(z++,fm_us2,&b[608]); else streepje(z++);
  if(fldlen(6,40)) scrifld(z++,fm_ugrb,&b[610]); else streepje(z++);
  if(ok(1800)){
    scrifld(z++,fm_us6,&b[598]);
    if(fldlen(58,34)>0) scrifld(z++,fm_ui1,&b[604]); else streepje(z++);
    if(fldlen(6,28)) c_210_djn(z++,&b[606]); else {b[606]=0;streepje(z++);}
  }
  else for(k=0;k<3;k++) streepje(z++);
  if(ok(1800)){
    scrifld(z++,fm_ugrb,&b[636]);
  }
  else streepje(z++);
  scrifld(z++,fm_ui2,&b[806]);
  scrifld(z++,fm_ui2,&skip_off);
  scrifld(z++,fm_uu5,&b[718]); scrifld(z++,fm_uu5,&sys3926);
  key=scrupd(curs,0x04A1);curs=1;
  if(key!=106){
    for(k=0;k<8;k++) if(*(float *)&b[84]==*(float *)&b[48+k*4]) break;
    if(k==8) {errnum=34;curs=17;goto redo_182;}
    updated=YES;
    c_djn_210(&b[606]);
    sysput(3584,300,&b[584]);
    sysput(2192,16,&b[192]);
    sysput(1048,100,&b[48]);
    sysput(2208,2,&skip_off);
    sysput(2706,2,xon_char);
		sysput(3926,2,&sys3926);
  }
  if(key==111) ovl_exit(0);
  if(key==101) goto endsr;

	// Peppol parameters 
	if (ok_33_ == 0 && ok_2240_ == NO) goto end_peppol;
	zero(mappeppol_,sizeof mappeppol_);
	sysget(1048,40,&btw_[0]);
	sysget(1286,25,mapKopiepeppolIN_); 
	sysget(1326,40,(char *)&grb_peppol_[0]);
	sysget(1366,50,mappeppol_); 
	sysget(1282,2,&PeppolProviderOUT);
	sysget(1311, 2, &dt_lastcheck_);
	sysget(1313, 4, &uur_lastcheck_);
	sysget(1317, 1, &CheckPeppolKlant);
	sysget(1318, 1, &PeppolBoekApart);
	sysget(19500,50,mapKopiepeppolOUT_); 
	sysget(20306,40,PeppolUidOUT); 
	sysget(20346,15,PeppolPwOUT); 
	sysget(20361,60,PeppolLicOUT); 
	sysget(1280,2,&PeppolProviderIN);
	sysget(21850,40,PeppolUidIN); 
	sysget(21890,15,PeppolPwIN); 
	sysget(21905,60,PeppolLicIN);
	sysget(21965,40,PeppolFirmaNaam);
	sysget(1804,2,&k); if(k==1) credt_allow=YES; else credt_allow=NO;
	hh_=uur_lastcheck_/10000;min_=(uur_lastcheck_-hh_*10000)/100;ss_=uur_lastcheck_-hh_*10000-min_*100;
	if(hh_<0 || hh_>24) hh_=0; 
	if(min_<0 || min_>60) min_=0;
	if(ss_<0 || ss_>60) ss_=0;
	curs=1;
	redo_184:
	scrget(2,184);z=1;
	scrifld(z++,VarTextFmt(50,1),mappeppol_);
	scrifld(z++,VarTextFmt(25,1),mapKopiepeppolIN_);
	if(ok_33_){
		scrifld(z++,fm_of21s,&btw_[0]);/* 1e btw wel 0 display */
		scrifld(z++,fm_ugrb,&grb_peppol_[0]);
		for(k=1;k<5;k++){
			if(btw_[k]==0) z+=2;
			else{
				scrifld(z++,fm_of2_1,&btw_[k]);
				scrifld(z++,fm_ugrb,&grb_peppol_[k]); 
			}
		}
		scrifld(z++,fm_ugrb,&grb_peppol_[9]); 
		if(ovltest(11) && (ovltest(255) || ovltest(211))) scrifld(z++,fm_u_JN,&PeppolBoekApart);
		else z++;
	} else z+=12;
	if(ok_33_ || ok_2240_){
		scrifld(z++,VarTextFmt(40,1),PeppolFirmaNaam);
	} else z++;

	if(ok_33_){
		scrifld(z++,VarTextFmt(40,1),PeppolUidIN);
		scrifld(z++,VarTextFmt(15,1),PeppolPwIN);
		scrifld(z++,VarTextFmt(60,1),PeppolLicIN);// scraddpicto(1,z-1,0,0,2,1,64,0,0x007FFF,"Info"); 
		scrifld(z++,fm_udat,&dt_lastcheck_);scrifld(z++,fm_uu2_,&hh_);scrifld(z++,fm_uu2_,&min_);scrifld(z++,fm_uu2_,&ss_);
	} else z+=7;
	if(ok_2240_){
		scrifld(z++,VarTextFmt(40,1),PeppolUidOUT);
		scrifld(z++,VarTextFmt(15,1),PeppolPwOUT);
		scrifld(z++,VarTextFmt(60,1),PeppolLicOUT);scraddpicto(2,z-1,0,0,2,1,64,0,0x007FFF,"Info"); 
		scrifld(z++,VarTextFmt(25,1),mapKopiepeppolOUT_);
		scrifld(z++,fm_u_JN,&CheckPeppolKlant);
	}
	key=scrupd(curs,0x04A1);curs=1;
	if ((key/0x100)==1) key=(key&0xFF)+5000;

	if (key == 5001)
		goto redo_184;

	if (key == 5002) {
		switch(PeppolProviderOUT) {
			case 0:
				ovlcall(2240,99);// Info over licentie Codabox
				break;
			case 1:
				break;
		}

		goto redo_184;
	}
	if(key!=106){
		if(hh_<0 || hh_>24 || min_<0 || min_>60 || ss_<0 || ss_>59) {errnum=6; goto redo_184;}
		uur_lastcheck_=hh_*10000+min_*100+ss_;
		sysput(1286,25,mapKopiepeppolIN_); 
		sysput(1326,40,(char *)&grb_peppol_[0]);
		sysput(1366,50,mappeppol_); 
		sysput(1311, 2, &dt_lastcheck_);
		sysput(1313, 4, &uur_lastcheck_);
		sysput(1317, 1, &CheckPeppolKlant);
		sysput(1318, 1, &PeppolBoekApart);
		sysput(19500,50,mapKopiepeppolOUT_); 
		sysput(20306,40,PeppolUidOUT); 
		sysput(20346,15,PeppolPwOUT); 
		sysput(20361,60,PeppolLicOUT); 
		sysput(21850,40,PeppolUidIN); 
		sysput(21890,15,PeppolPwIN); 
		sysput(21905,60,PeppolLicIN); 
		sysput(21965,40,PeppolFirmaNaam);
	}
end_peppol:;


//	if(ovltest(2240)==NO) goto endsr;
#if FLAGABT || FLAGALB || FLAEPD || FLAGHIN
	goto endsr;
#endif

	zero(mappeppol_,sizeof mappeppol_);pos_=6500;
#if FLAGMXT
	pos_=6550;
#endif
	sysget(pos_,50,mappeppol_); 

	curs=1;
	redo_185:
	scrget(2,185);z=1;
	scrifld(z++,VarTextFmt(50,1),mappeppol_);
	key=scrupd(curs,0x04A1);curs=1;
	if ((key/0x100)==1) key=(key&0xFF)+5000;

	if(key!=106){
		sysput(pos_,50,mappeppol_); 
	}

  endsr:;
}

static taal()
{
  int16 k,key,z;
 
  if(fldlen(1,16)!=1 && fldlen(2,24)!=1 && fldlen(6,4)==0) return NO;/* geen taal*/

  sysget(2212,4,&b[212]);
  scrget(1,190);z=1;
  for(k=0;k<4;k++) scrifld(z++,fm_us1_U,&b[212+k]);
  key=scrupd(1,0x04A1);
  if(key!=106){
    updated=YES;
    sysput(2212,4,&b[212]);
  }
  if(key==111) ovl_exit(0);
  if(key==101) return YES;
  return NO;
}
 
static c_210_djn(z,s)
int16 z, *s;
{
  if(*s==2) (*(char *)s = 'D');
  else if(*s==1) (*(char *)s = 'J');
  else (*(char *)s = 'N');
  scrifld(z,fm_u_DJN,s);
}
							
static c_djn_210(s)
int16 *s;
{
  if(*(char *)s!='J' && *(char *)s!='N' && *(char *)s!='D') goto endsr;
  if(*(char *)s=='D') *s=2;
  else if(*(char *)s=='J') *s=1; else *s=0;
  endsr:;
}
 
static c_10_jn(z,s)
int16 z, *s;
{
  if(*s==1) (*(char *)s = 'J'); else (*(char *)s = 'N');
  scrifld(z,fm_u_JN,s);
}

static c_jn_10(s)
int16 *s;
{
  if(*(char *)s!='J' && *(char *)s!='N') goto endsr;
  if(*(char *)s=='J') *s=1; else *s=0;
  endsr:;
}

static ok(pos)
int16 pos;
{
  int16 i1;

  sysget(pos,2,&i1);
  return i1;
}

static initload()
{

  sysget(3678,2,&def_taal);
  if(ovltest(110) || ovltest(253)) use_xon=YES; else use_xon=NO;
}
 
static ovl_exit(ovlnr)
int16 ovlnr;
{
  long l;

  if(updated){
    sysget(6,6,b);
    stcd_li(b,&l);
    stcli_d(b,l+1,5,NO);
    sysput(6,5,b);
    sysflush();
  }
  if(ovlnr==0) ovlnr=*u(25,4);
  ovlexit(ovlnr);
}

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
}
