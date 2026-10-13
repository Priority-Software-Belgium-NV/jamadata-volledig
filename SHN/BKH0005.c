/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0005GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0005dat
#define ovlcod BKH0005cod
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

char ovldat[] = "bkh0005  00:63 16/03/10 (c) Jamadata"; // parameters of groene 'tools'-icoon op hoofdmenu

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define MAXFLD          120
#define EGALISA 1073741824L

static char hex2byte();
static uint16 make_pw();

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l(),val();
extern float *f();
extern double *d(),valu_cnv();
extern int16 parmcall[8];

static char fm_os70[]  = {7,0x88,70,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os17[]  = {7,0x88,17,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os12[]  = {7,0x88,12,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us65[]  = {7,0xC8,65,0,0,0,0};
static char fm_us60[]  = {7,0xC8,60,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us42U[] = {7,0xC8,42,0,1,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us25[]  = {7,0xC8,25,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us17[]  = {7,0xC8,17,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us14[]  = {7,0xC8,14,0,0,0,0};
static char fm_us12[]  = {7,0xC8,12,0,0,0,0};
static char fm_us11U[] = {7,0xC8,11,0,1,0,0};
static char fm_us7[]   = {7,0xC8,7,0,0,0,0};
static char fm_us8_U[] = {7,0xC8,8,0,1,0,0};
static char fm_us6[]   = {7,0xC8,6,0,0,0,0};
static char fm_us3[]   = {7,0xC8,3,0,0,0,0};
static char fm_us3_U[] = {7,0xC8,3,0,1,0,0};
static char fm_us2_U[] = {7,0xC8,2,0,1,0,0};
static char fm_us2[]   = {7,0xC8,2,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf2_2[] = {6,0xD4,2,2,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_uf2s1[] = {6,0xD4,2,1,0x30,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x60,0};
static char fm_uu2_s[] = {6,0xD0,2,0,0x20,0};
static char fm_uu1_s[] = {6,0xD0,1,0,0x20,0};
static char fm_ui5[]   = {6,0xD1,5,0,0x60,0};
static char fm_ui4[]   = {6,0xD1,4,0,0x60,0};
static char fm_ui3[]   = {6,0xD1,3,0,0x60,0};
static char fm_ui2[]   = {6,0xD1,2,0,0x60,0};
static char fm_ui3_s[] = {6,0xD1,3,0,0x40,0};
static char fm_ui1[]   = {6,0xD1,1,0,0x60,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_ul8[]   = {6,0xD3,8,0,0x70,0};
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_ud9_2[] = {6,0xD5,9,2,0x70,0};
static char fm_ud6_2[] = {6,0xD5,6,2,0x70,0};
static char fm_ugrb[]  = {2,0xE8};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_uJND[]  = {13,0xC8,1,0,1,0,'D','D','J','J','N','N',0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uJNa[]  = {11,0xC8,1,0,9,0,'J','J','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,0x09,0,0};
static char fm_us8PW[] = {7,0xC8,8,0,5,0,0};
static char fm_us8MP[] = {9,0xC8,8,0,1,0,'A','Z',0};
static char fm_u_WD[]  = {11,0xC8,1,0,1,0,'W','W','D','D',0};
static char fm_u_MKJ[] = {11,0xC8,1,0,1,0,'M','M','J','K',0};
static char fm_u_MNO[] = {11,0xC8,1,0,1,0,'M','N','O','O',0};
static char fm_u_AVB[] = {11,0xC8,1,0,1,0,'A','B','V','V',0};
static char fm_u_EI[]  = {11,0xC8,1,0,1,0,'E','E','I','I',0};
static char fm_u_FE[]  = {11,0xC8,1,0,1,0,'E','E','F','F',0};
static char fm_uJNSLW[] = {17,0xC8,1,0,1,0,'J','J','L','L','N','N','S','S','W','W',0};
static char fm_u09AF[] = {11,0xC8,4,0,1,0,'0','9','A','F',0};
static char fm_uu1_L[] = {10,0xD0,1,0,0x20,0xC0,0,0,3,0};
static char umaand[]   = {10,0xD0,2,0,0x20,0xC0,0,0,12,0};
static char ujtype[]   = {10,0xD0,2,0,0x60,0xC0,0,0,10,0};
static char upapnr[]   = {10,0xD0,2,0,0x20,0xC0,0,0,10,0};
static char uprtnr[]   = {10,0xD0,2,0,0x20,0xC0,1,0,10,0};
static char fm_btw[]   = {2,0x58};

static struct {
  uint16 nr;
  uint16 typ;
  char nm[16];
  uint16 lastnr;
  long fingrb;
  long saldo;
  double saldo_vm;
  char munt[4];
  uint16 blz_o;
  uint16 blz_n;
  char mast_munt;
  double e_saldo;
  char dummy[25];
  char vm_JN;/* extra element */
} j_tab[80];

static char *selp_txt[6]={"Ondergrens (>)","Ondergrens (> of =)",
		"Bovengrens (<)","Bovengrens (< of =)",
		"Gelijk","Niet gelijk"};


static uint16 niv_MPW,passwrds[5],index[40],DCalso,stu;
static char niveaus[2][10],b[1000],b1[500],def_munt[4],valu_nm[12][4],fmt[40];
static long noomzet[10],bd_afw;
static flag updated=NO,sys298,voo_ok;
static int16 def_taal;

static int16 lvcd,klcd;
static char taal_i,talen[4];
static int16 selp_stu=0;
static char selp_bf[4][1000],selp_des[40],*selp_fld;
static flag selp_use,selp_ge,selp_le;

ovlcod(parmval)
int16 parmval;
{
  int16 key;
  char choice;

  initload();
	if(*s(25,5)==1){
		FOREVER {
			redo:;
			scrget(1,260);fasunlck(0);
			scraddpicto(50,0,78,9,2,1,105,1,7,"^!B0005A");
			scraddpicto(51,0,21,20,2,1,105,1,7,"^!B0005B");
			scrfld(1,25,1);
			scrifld(2,fm_menu,&choice);
			key=scrupd(2,0x1);
  		if ((key/0x100)==1) key=(key&0xFF)+5000;
		  if(key==5050 || key==5051) goto redo; // link help 
			fasunlck(-1);
			if(key<101){
				switch (choice){
					case '1': ovlcall(95,0); break;
					case '2': if(CheckPw(0,10,0)) MaakVolledigeBackupOpStick(); break;
					case '3': UpdateFtNummer();break;
					case '4': upd7(); break;
          case '5': if(CheckPw(0,10,0)) CheckForJamaDataUpdates(YES); break;
			    case 'D': if(CheckPw(0,10,0) && ovltest(2802)){
						          if(DisplayWarning("Zijn ALLE schermen/werkposten uit het programma of op het hoofdmenu?",61,1)) ovlexit(2802); 
										}
										else errnum=12; break; 
					case 'E': DeleteAllPrintjobs(); break;
					case '+': MenuParameters(); break;
					default:  errnum=34; break;
				}
			}
			if(key==101 || key==111) break;
		}
	}
	else MenuParameters();
  ovl_exit(-1);
}

static MaakVolledigeBackupOpStick()
{
	if(DisplayWarning("Zijn ALLE schermen/werkposten uit het programma of op het hoofdmenu?",61,1)==NO) return NO;
	MakeFullExternalBackup(YES,YES); 
	if(ServerVersion>SERVER_MONO){ // dit scherm echt laten wachten tot ie aangekomen is
		FOREVER{
			_sleep(600);
			if(FileExist(BackupFile2Receive)==NO) break;
			scrnum=0;scrget(1,170);
			scraddfield(1,8,10,0); scrifld(1,VarTextFmt(65,0),"Bezig met klaarzetten backup voor USB-stick. Even geduld aub...");
      scraddfield(2,15,14,0); scrifld(2,VarTextFmt(65,0),"De andere posten/schermen mogen nu verderwerken.");
      scrupd(-3,0);
		}
	}
	return YES;
}

static MenuParameters()
{
  int16 key;
  char choice;

  sysget(1876,6,&passwrds[0]);
  sysget(1882,10,&niveaus[0][0]);
  sysget(3878,4,&passwrds[3]);
  if(sys298) sysget(3882,10,&niveaus[1][0]);
  if(!CheckPw(0,10,1)) goto endsr;

  FOREVER {
    scrget(1,180);fasunlck(0);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0405);
		fasunlck(-1);
		if(key==103) upd3();
    if(key<101){
      switch (choice){
				case '1': upd1(); break;
				case '2': upd2(); break;
				case '3': if(ok(1804)) upd3(); else errnum=12; break;
				case '4': if(ok(1800) || ovltest(222)) upd4(); else errnum=12; break;
				case '5': if(voo_ok) ovl_exit(voo_ok*100+5); 
					        else if(ovltest(2240)) ovlexit(205);
									else errnum=12; 
									break;
				case '6': upd6(); break;
				case '7': upd7(); break;
				case '8': upd8(); break;
				case '9': if(ok(1790)) upd9(); else errnum=12; break;
				case 'B': ovlcall(95,0); break;
				case 'C': if(ovltest(94)) ovlexit(94); else errnum=12; break;
						//      case 'E': upd_euro(); break; 
				case 'F': updf(); break;
				case 'J': if(ovltest(2800)) ovlexit(2800);else errnum=12; break;
				case 'H': upd_divrs(); break;
				case 'T': SpecialTools(); break;
case 'K': KleurTest(); break;
				default:  errnum=34; break;
      }
    }
    if(key==101 || key==111) break;
  }
  endsr:;
}



static  xbtw_deco(s,pl,sepflag)
char *s;
long *pl;
int sepflag;
 
{
  int index, i, ega_flag,flag_1;
  char pl_str_[4];
  long btw_long;
 
  ega_flag = NO; flag_1 = NO;
  bcopy((char *)(pl),pl_str_,4); 
  if (pl_str_[3] & 0x80) {
	flag_1 = YES; pl_str_[3] &= 0x7F;
	bcopy(pl_str_,(char *)(pl), 4);
  }
  btw_long = *pl;
  
  if (btw_long >= EGALISA) {ega_flag=YES; btw_long -= EGALISA;}
  if (flag_1) btw_long += 1000000000L;
  stcli_d(s,btw_long,10,NO);
  if (sepflag) {
    i=2;
    for (index=12; index>3; index--) {
      if ((index==8)||(index==4)) {*(s+index)='.'; i--;}
      else *(s+index)=*(s+index-i);
    }
    if (ega_flag) {
//      for (index=12; index>0; index--) *(s+index) = *(s+index-1);
//      *s='E';
    }
  }
  else if (ega_flag) {*(s+10)='N'; *(s+11)='\0';}
}

static int btw_comp(char *s,long *pl)
{
  char last2[3],pl_str_[4];
  int  i, flag_1;
 
  for (i=0; i<10; i++)
    if ((*(s+i)<'0')||(*(s+i)>'9')) return YES;
  if ((*(s+10)!=' ')&&(*(s+10)!='N')&&(*(s+10)!='\0')) return YES;
  last2[0]=*(s+8); last2[1]=*(s+9); last2[2]='\0';
  *(s+8)='\0';
  stcd_li(s,pl); stcd_i(last2,&i); *(s+8)=last2[0];
  if ((*pl % 97) != (97-i) % 97)
    if ((*pl!=9999999L)||(i!=99)) return YES;
  *pl = *pl*100 + i;
  flag_1 = NO; 
  if (*pl >= 1000000000L) {
	*pl -= 1000000000L; flag_1 = YES;
  }
  if (*(s+9)=='N') *pl += EGALISA;
  if(flag_1){
	bcopy((char *)(pl), pl_str_, 4);
	pl_str_[3] |= 0x80; bcopy(pl_str_, (char *)(pl), 4);
  }
	
  return NO;
}




static KleurTest()
{
	int k;
	char tekst[20];
	  
	copy("   Lijn   ",tekst,12);
	scrnum=0;scrget(1,170);
	for(k=0;k<16;k++){
		stcli_d(&tekst[8],(long)(k),2,0);
		scrifld(k+1,VarTextFmt(11,0),tekst);
		scrchat(k+1,k);
	}
	scrupd(-1,0);
}


static initload()
{
  int16 k;

  sysget( 294,4,def_munt);
  sysget( 298,2,&sys298);
  if(sys298) sysget(1802,2,&voo_ok);
	sysget(2212,4,talen);
  for(k=0;k<12;k++){
    sysget(2560+k*8,4,valu_nm[k]);
  }
  sysget(2210,2,&k);
  if(k){fm_uf2s1[3]=0;fm_uf2_1[3]=0;}/* GEEN btw% met decimalen */
  sysget(3678,2,&def_taal);
}
 
static upd1()
{
  int16 z,key,curs=1,bg_kleur_,mailprofiel_,def_filiaal_,color_;
  char iban_bic[55],kar_;

	sysget(34,256,&b[34]);
  sysget(1219,53,iban_bic);
  if(fldlen(2,10)) sysget(290,4,l(2,10));
	sysget(18480,1,&kar_);bg_kleur_=kar_;
	sysget(18481,1,&kar_);mailprofiel_=kar_;
	sysget(2854,2,&def_filiaal_); if(def_filiaal_<1 || def_filiaal_>10) def_filiaal_=0;
  redo_181:;
  scrnum=0;scrget(1,181);z=1;scraddpicto(1,0,71,20,4,2,535,0,0,"Test kleur"); 
  scrifld(z++,fm_us30,&b[34]);
  scrifld(z++,fm_us25,&b[65]);
  scrifld(z++,fm_us7,&b[91]);
  scrifld(z++,fm_us20,&b[99]);
  scrifld(z++,fm_us17,&b[150]);
  scrifld(z++,fm_us17,&b[204]);
  scrifld(z++,fm_us15,&b[120]);
  scrifld(z++,fm_us12,&b[168]);
  scrifld(z++,fm_us14,&b[135]);
  scrifld(z++,fm_us42U,&iban_bic[0]);
  scrifld(z++,fm_us11U,&iban_bic[42]);
  scrifld(z++,fm_us30,&b[222]);
  scrifld(z++,VarTextFmt(34,1),&b[256]);
	scrifld(z++,fm_uu1,&mailprofiel_);
	if(fldlen(66,11)) scrifld(z++,fm_uu2,&def_filiaal_); else z++;
  scrifld(z++,fm_us20,&b[183]);
	scrifld(z++,fm_uu2,&bg_kleur_);
  key=scrupd(curs,0x04A1); curs=1;
	if ((key/0x100)==1) key=(key&0xFF)+5000;
	if(key==5001){ // kleur testen
		kar_=bg_kleur_; if(kar_<1 || kar_>8) kar_=DefaultBackGroundColor;	color_=kar_;scrchat(-1,color_);
		goto redo_181;
	}
  if(key!=106){
		if(fldlen(66,11) && def_filiaal_>10) {curs=15; errnum=34; goto redo_181;}
    updated=YES;
    sysput(34,256,&b[34]);
    sysput(1219,53,iban_bic);
    copy(&b[34],s(25,1),30);
		kar_=bg_kleur_;sysput(18480,1,&kar_);
		kar_=mailprofiel_;sysput(18481,1,&kar_);
		sysput(2854,2,&def_filiaal_);
  }
	sysget(18480,1,&kar_);if(kar_<1 || kar_>8) kar_=DefaultBackGroundColor;	color_=kar_;scrchat(-1,color_); // kleur juistzetten bij vertrek

  if(key==111) ovl_exit(-1);
  if(key==101 || key==106) goto endsr;


  endsr:;
}

static upd2()
{
  int16 j,k,key,z,stu_;
  char new_code_[4],filname[20];
 
	fasclos(0);/* close all fasfiles for this user */
  sysget(300,255,&b[300]);
  copy(&b[300],&b[0],255);
  redo_182:;
  scrget(1,182);z=1;
  scrofld(z++,25,2,-1);
  scrfld(z++,25,1);
  for(k=0;k<15;k++) scrifld(z++,fm_us15,&b[300+k*17]);
  key=scrupd(1,0x06A1);
  if(key==110){
    zero(new_code_,sizeof new_code_);
    if(ask_kod(new_code_) ==NO) goto redo_182;
    for(k=0;k<15;k++){
      if(b[300+k*17]!='\0'){
				for(j=0;j<12;j++) if(b[300+k*17+j]=='.') break;
				if(j<=12) copy(new_code_,&b[300+k*17+j+1],3);
      }
    }
    goto redo_182;
  }

  if(key!=106){
    //if(cmp_str(&b[300],&b[0],255)){
    //  scrifld(20,fm_os70,"  Wenst U echt de namen van de bestanden te wijzigen ?");
    //  scrifld(18,fm_os12," F4 wijzig ");
    //  scrifld(19,fm_os17," F5 wijzig niet ");
    //  FOREVER{
				//k=scrupd(1,0x18);
				//if(k==104 || k==105) break;
    //  }
    //  if(k==104){
		sysput(300,255,&b[300]); // aanpassing wegschrijven 
		for(j=0;j<15;j++){ // controle of structuur ingevuld is, zo nee, dan default
			sysget(300+17*j,15,filname);
			sysget(315+17*j,2,&stu_);
			if(filname[0] && stu_==0){
				switch(j){
					case 0  : stu_=1;break;
					case 1  : stu_=2;break;
					case 2  : stu_=3;break;
					case 3  : stu_=4;break;
					case 4  : stu_=5;break;
					case 5  : stu_=6;break;
					case 6  : stu_=7;break;
					case 7  : stu_=8;break;
					case 8  : stu_=9;break;
					case 9  : stu_=86;break;
					case 10  : stu_=92;break;
					case 11  : stu_=66;break;
					case 12  : stu_=16;break;
					case 13  : stu_=60;break;
					case 14 : stu_=22;break;
					default : stu_=0;break;
				}
				sysput(315+17*j,2,&stu_);
			}
			updated=YES;
    }
  }
  if(key==111) ovl_exit(-1);
}
 
static upd3()
{
  int16 curs,g,j,k,key,z,jn_open=0,max_jrnl_,yy,mm,mm1,dd;
  char byte,byte1;
	uint16 MinBkhDatum;
  flag flag_;
  float fbd_;

	sysget(2300,2,&MinBkhDatum);
  sysget(1008,16,&b[8]);
  sysget(968,40,(char *)noomzet);
  sysget(1800,94,&b[800]);
  if(*(int16 *)&b[864]==0) byte='M'; else if(*(int16 *)&b[864]==1) byte='K';
  else byte='J';
  byte1='N';if(b[862] & 1) byte1='J';
	curs=1;
  redo183:;
  scrget(1,183);z=1;
  scrifld(z++,fm_u_MKJ,&byte);
  scrifld(z++,umaand,&b[866]);
  for(k=0;k<4;k++) scrifld(z++,fm_uf2s1,&b[8+k*4]);
  scrifld(z++,fm_uJNa,&byte1);
  c_10_jn(z++,&b[892]);
  for(k=0;k<10;k++) scrifld(z++,fm_ugrb,&noomzet[k]);
  scrifld(z++,fm_udat,&MinBkhDatum);
//	scrifld(z++,fm_uu2_s,&b[810]);
//  scrifld(z++,fm_uu2_s,&b[808]);
  key=scrupd(curs,0x04A1);curs=1;
  if(key!=106){
		if(MinBkhDatum){
  		jddate(MinBkhDatum,&yy,&mm1,&dd);
      jddate(MinBkhDatum+1,&yy,&mm,&dd);
      if(mm==mm1) {curs=19;errnum=32;goto redo183;}
		}
    updated=YES;
    if(*(uint16 *)(&b[866])<1 || *(uint16 *)(&b[866])>12) {errnum=38;goto redo183;}
    if(byte=='M') *(int16 *)&b[864]=0; else if(byte=='K') *(int16 *)&b[864]=1;
    else *(int16 *)&b[864]=2;
    b[862]=b[862] & 0xFE; if(byte1=='J') b[862]=b[862] | 1;
    c_jn_10(&b[892]);
    sysput(1008,16,&b[8]);
    sysput(968,40,(char *)noomzet);
    sysput(1800,94,&b[800]);
		sysput(2300,2,&MinBkhDatum);
  }
  if(key==111) ovl_exit(-1);
  if(key==101 || key==106) goto endsr;
 
  sysget(1892,2,&flag_);
  sysget(1213,4,&fbd_);
  sysget(1217,2,&max_jrnl_);
  if(flag_){
    sysget(1024,20,&b[24]);
    sysget(1894,12,&b[894]);
    scrget(1,195);z=1;
    for(k=0;k<5;k++){
      scrifld(z++,fm_uu3,&b[896+k*2]);
      scrifld(z++,fm_uf2_1,&b[24+k*4]);
    }
    scrifld(z++,fm_uf2_2,&fbd_);
    scrifld(z++,fm_uu2,&max_jrnl_);
    key=scrupd(1,0x04A1);
    if(key!=106){
      updated=YES;
      sysput(1024,20,&b[24]);
      sysput(1894,12,&b[894]);
      sysput(1213,4,&fbd_);
      sysput(1217,2,&max_jrnl_);
    }
    if(key==111) ovl_exit(-1);
    if(key==101 || key==106) goto endsr;
  }
 
  sysget(780,72,b);
  curs=1;
  redo184:
  scrget(1,184);
  for(j=0;j<18;j++) scrifld(j+1,fm_ugrb,&b[j*4]);
  key=scrupd(curs,0x04A1);curs=1;
  if(key!=106){
    for(j=0;j<2;j++){
      if(b[j*4]==0xFF || b[j*4]==0x00) {errnum=40;curs=1+j;goto redo184;}
    }
    updated=YES;
    sysput(780,72,b);
  }
  if(key==111) ovl_exit(-1);
  if(key==101 || key==106) goto endsr;


/* journaaltype : 1=AK-journaal, 2=VK-journaal, 3=Fin.journaal, 4=fin.journaal met dagnummer */
/* journaaltype : 5=div-journaal, 6=div-journaal met dagnummer, 7=overschrijving */
/* journaaltype : 8=Openingsbalans, 9/10 = 3/4 met rekeninguittreksel */
 
  jn_open=0;
  for(k=0;k<80;k++){
    sysget(10240+k*80,80,(char *)&j_tab[k]);
    j_tab[k].vm_JN='\0';
    if((j_tab[k].typ>=3 && j_tab[k].typ<=4) || (j_tab[k].typ>=9 && j_tab[k].typ<=10)){
      j_tab[k].vm_JN='N';
      if(fldlen(4,15)){
	if(j_tab[k].munt[0] && cmp_str(j_tab[k].munt,def_munt,3)) j_tab[k].vm_JN='J';
      }
    }
    if(j_tab[k].typ==8) jn_open=j_tab[k].nr;/* openingsjournaal */
  }
  if(jn_open==0){/* openingsjournaal creeren indien onbestaand */
    jn_open=99;
    FOREVER{
      for(k=0;k<80;k++) if(j_tab[k].nr==jn_open) break;
      if(k>=80) break; else jn_open--;
      if(jn_open<=0) break;
    }
    if(jn_open){
      for(k=19;k>=0;k--) if(j_tab[k].nr==0) break;
      if(k<0){for(k=20;k<80;k++) if(j_tab[k].nr==0) break;}
      j_tab[k].nr=jn_open; j_tab[k].typ=8;
      copy("Openingsbalans",j_tab[k].nm,15);
      j_tab[k].lastnr=0;j_tab[k].fingrb=0;j_tab[k].e_saldo=0;j_tab[k].mast_munt='E';
      j_tab[k].blz_o=0; j_tab[k].blz_n=0;
    }
  }
  for(j=0;j<4;j++){
    scrnum=0;
    curs=1;
    redo185:
    scrget(1,185);z=1;
    for(k=j*20;k<j*20+20;k++){
			j_tab[k].nm[15]='\0'; // om vieze tekens na naam weg te doen
      scrifld(z++,fm_uu2,&j_tab[k].nr);
      scrifld(z++,ujtype,&j_tab[k].typ);
      scrifld(z++,fm_us15,j_tab[k].nm);
      scrifld(z++,fm_uu5,&j_tab[k].lastnr);
      scrifld(z++,fm_ugrb,&j_tab[k].fingrb);
      scrifld(z++,fm_ud9_2,&j_tab[k].e_saldo);
      scrifld(z++,fm_u_FE,&j_tab[k].mast_munt);
      if(fldlen(4,15)) scrifld(z++,fm_uJN,&j_tab[k].vm_JN); else z++;
      scrifld(z++,fm_uu3,&j_tab[k].blz_o);
      scrifld(z++,fm_uu3,&j_tab[k].blz_n);
    }
    key=scrupd(curs,0x04A1);curs=1;
    if(key!=106){
      for(k=j*20;k<j*20+20;k++){
	if(j_tab[k].fingrb==-1) j_tab[k].fingrb=0;
	g=j_tab[k].typ;
	if(g==3 || g==4 || g==7 || g==9 || g==10){/* verplichte grb */
	  if(j_tab[k].fingrb==0) {errnum=40;curs=k*10+5;goto redo185;}
	}
	else if(j_tab[k].fingrb) {errnum=3;curs=k*10+5;goto redo185;}
      }
      updated=YES;
      for(k=0;k<80;k++){
	if((j_tab[k].typ<3 || j_tab[k].typ>4) && j_tab[k].typ<9) j_tab[k].vm_JN='\0';
	if(j_tab[k].vm_JN!='J'){
	  j_tab[k].saldo_vm=0;zeros(j_tab[k].munt,sizeof j_tab[0].munt);
	}
	sysput(10240+k*80,80,(char *)&j_tab[k]);
      }
    }
    if(key==111) ovl_exit(-1);
    if(key==101 || key==106) goto endsr;
    if(j_tab[j*20+19].nr==0){
      for(k=(j+1)*20;k<(j+2)*20;k++) if(j_tab[k].nr) break;
      if(k==(j+2)*20) break;/* geen volgend scherm met journalen */
    }
  }

  g=0;zeros((char *)index,sizeof index);
  for(k=0;k<80;k++){
    if(j_tab[k].vm_JN=='J') index[g++]=k;
  }
  if(g){
    if(g>19) g=19;
    curs=1;
    redo196:
    scrget(1,196);z=1;
    for(k=0;k<g;k++){
      scrifld(z++,fm_ou2,&j_tab[index[k]].nr);
      scrifld(z++,fm_ou2,&j_tab[index[k]].typ);
      scrifld(z++,fm_os15,j_tab[index[k]].nm);
      scrifld(z++,fm_ud9_2,&j_tab[index[k]].saldo_vm);
      scrifld(z++,fm_us3_U,j_tab[index[k]].munt);
    }
    key=scrupd(curs,0x04A1);curs=1;
    if(key!=106){
      for(k=0;k<g;k++){
	if(cmp_str(j_tab[index[k]].munt,def_munt,3)){/* not BEF */
	  if(j_tab[index[k]].munt[0]=='\0') {errnum=38;curs=5+k*5;goto redo196;}
	  valu_cnv(def_munt,j_tab[index[k]].munt,(double)1.,(double)1.);
	  if(errnum){
	    curs=5+k*5;goto redo196;
	  }
#if 0
	  for(j=0;j<12;j++){
	    if(cmp_str(j_tab[index[k]].munt,valu_nm[j],3)==0) break;
	  }
	  if(j==12){errnum=39;curs=5+k*5;goto redo196;}
#endif
	}
      }
      for(k=0;k<80;k++){
	if(cmp_str(j_tab[k].munt,def_munt,3)==0){
	  j_tab[k].saldo_vm=0;zeros(j_tab[k].munt,sizeof j_tab[0].munt);
	}
	sysput(10240+k*80,80,(char *)&j_tab[k]);
      }
      updated=YES;
    }
    if(key==111) ovl_exit(-1);
    if(key==101 || key==106) goto endsr;
  }

  get_JN(1785,0);
  get_JN(1786,8);
  scrget(1,192);z=1;
  scrfld(z++,25,1);
  for(k=0;k<4;k++) scrifld(z++,fm_uJNa,&b[k]);
  scrifld(z++,fm_uJNa,&b[10]);
  scrifld(z++,fm_uJNa,&b[7]);
  scrifld(z++,fm_uJNa,&b[5]);
  scrifld(z++,fm_uJNa,&b[8]);
  scrifld(z++,fm_uJNa,&b[4]);
  scrifld(z++,fm_uJNa,&b[9]);
  key=scrupd(1,0x04A1);
  if(key!=106){
    put_JN(1785,0);
    put_JN(1786,8);
    updated=YES;
  }
  if(key==111) ovl_exit(-1);
  if(key==101 || key==106) goto endsr;

	sysget(1833,1,&byte1);
  get_JN(1787,0);
  get_JN(1861,8);
  get_JN(1862,16);
  scrget(1,193);z=1;
  scrfld(z++,25,1);
  scrifld(z++,fm_uJNa,&b[4]);
  for(k=0;k<4;k++) scrifld(z++,fm_uJNa,&b[k]);
  scrifld(z++,fm_uJNa,&b[8]);
	scrifld(z++,fm_u_MNO,&byte1);
  for(k=17;k<19;k++)scrifld(z++,fm_uJNa,&b[k]);
  key=scrupd(1,0x04A1);
  if(key!=106){
    put_JN(1787,0);
    put_JN(1861,8);
    put_JN(1862,16);
		sysput(1833,1,&byte1);
    updated=YES;
  }
  if(key==111) ovl_exit(-1);
  if(key==101 || key==106) goto endsr;

  sysget(1862,2,&j);
  if(j & 0x80){
    sysget(1836,4,&bd_afw);
    sysget(1840,2,&DCalso);
    curs=1;
    redo197:
    scrget(1,197);z=1;
    scrifld(z++,fm_ul9,&bd_afw);
    c_10_jn(z++,&DCalso);
    key=scrupd(curs,0x04A1);curs=1;
    if(key!=106){
      updated=YES;
      sysput(1836,4,&bd_afw);
      c_jn_10(&DCalso);sysput(1840,2,&DCalso);
    }
    if(key==111) ovl_exit(-1);
    if(key==101 || key==106) goto endsr;
  }
  if (!parm_eur()) goto endsr;
  if (!verantwoordelijke_btw_aangifte()) goto endsr;
  if(taal()) goto endsr;
 

  endsr:;
}
 
static upd4()
{
  int16 j_adr,journl,k,key,z,curs=1;
	uint16 rec_levkost_;
  char bon_val,disk_ei,jnd,MapUbl[50],MapKlantBestelling[50],MapLeveranciersBestelling[50],MapDiverseBestanden[50],MapPdfFacturen[50];
	char MapPdfBons[50],MapDocumenten[65],ExtraBijlageFactuurmail[50];
	//char UidCodaBox[40],PwCodaBox[15],LicIDCodaBox[40];
 
	if(fldlen(6,1)) fileopen(6);
  sysget(1920,244,b1); sysget(2166,46,&b[166]);
  journl=*(int16 *)&b[166];
	sysget(3192,50,ExtraBijlageFactuurmail); 
	sysget(19500,50,MapUbl); 
	sysget(19550,50,MapKlantBestelling); 
	sysget(19600,50,MapLeveranciersBestelling); 
	sysget(19650,50,MapDiverseBestanden); 
	//sysget(20306,40,UidCodaBox); 
	//sysget(20346,15,PwCodaBox); 
	//sysget(20361,60,LicIDCodaBox); 
	sysget(20450,50,MapPdfFacturen);
	sysget(20950,50,MapPdfBons);
	sysget(21400,65,MapDocumenten);
  j_adr=0;
  for(k=0;k<40;k++){
    sysget(10240+k*80,2,&z);
    if(z==journl){j_adr=10260+k*80;break;}
  }
  if(j_adr) sysget(j_adr,2,&b[0]); else *(int16 *)&b[0]=0;
  redo:;
  scrget(1,187);
  z=1;
  for(k=0;k<4;k++) scrifld(z++,fm_us60,&b1[61*k]);
  scrifld(z++,fm_uu2,&b[166]);
  scrifld(z++,fm_uu5,&b[0]);
  c_10_jn(z++,&b[170]);
  scrifld(z++,fm_uu2,&b[168]);
	scrifld(z++,fm_us50,MapUbl);
	scrifld(z++,fm_us50,MapKlantBestelling);
	scrifld(z++,fm_us50,MapLeveranciersBestelling);
	scrifld(z++,fm_us50,MapDiverseBestanden);
	scrifld(z++,fm_us50,MapPdfFacturen);
	scrifld(z++,fm_us50,MapPdfBons);
	scrifld(z++,fm_us50,ExtraBijlageFactuurmail);
	scrifld(z++,fm_us65,MapDocumenten);
	//scrifld(z++,fm_us40,LicIDCodaBox);scraddpicto(1,z-1,0,0,2,1,64,0,0x007FFF,"Info"); 
	//scrifld(z++,fm_us40,UidCodaBox);
	//scrifld(z++,fm_us15,PwCodaBox);
  key=scrupd(curs,0x04A1); curs=1;
	if ((key/0x100)==1) key=(key&0xFF)+5000;
	if(key==5001){
		ovlcall(2240,99);// info over licentie 
		goto redo;
	}
  if(key!=106){
    if(*(int16 *)&b[166]==0) {curs=5;errnum=38;goto redo;}
    updated=YES;
    c_jn_10(&b[170]);
    sysput(2166,46,&b[166]); sysput(1920,244,b1);
    if(j_adr) sysput(j_adr,2,&b[0]);
		sysput(3192,50,ExtraBijlageFactuurmail); 
		sysput(19500,50,MapUbl); 
		sysput(19550,50,MapKlantBestelling); 
		sysput(19600,50,MapLeveranciersBestelling); 
		sysput(19650,50,MapDiverseBestanden); 
	 // sysput(20306,40,UidCodaBox); 
	 // sysput(20346,15,PwCodaBox); 
		//sysput(20361,40,LicIDCodaBox); 
		sysput(20450,50,MapPdfFacturen);
		sysput(20950,50,MapPdfBons);
		sysput(21400,65,MapDocumenten);
  }
  if(key==111) ovl_exit(-1);
  if(key==101) goto endsr;

  sysget(1044,44,&b[44]);
  sysget(2164,66,&b[164]);
	if(fldlen(6,1)){
  	fasinit(6); sysget(2991,2,u(6,1)); if(*u(6,1)) fasgeti(6);
	}
  bon_val='E'; if(b[224]) bon_val='I';
  disk_ei='I'; if(b[164]) disk_ei='E';
  scrget(1,191);
  z=1;
  scrifld(z++,fm_uf2s1,&b[48]);
  for(k=1;k<8;k++) scrifld(z++,fm_uf2_1,&b[48+k*4]);
  for(k=0;k<8;k++) scrifld(z++,fm_ui2,&b[192+k*2]);
  scrifld(z++,fm_uf2_1,&b[44]);
  scrifld(z++,fm_uf2_1,&b[80]);
  scrifld(z++,fm_uf2_1,&b[84]);
  scrifld(z++,fm_u_EI,&bon_val);
  c_10_jn(z++,&b[228]);
  scrifld(z++,fm_uu1_s,&b[222]);
  if(b[172]=='\0') *(int16 *)&b[2]=1; else *(int16 *)&b[2]=0;
  c_10_jn(z++,&b[2]);
  scrifld(z++,fm_us1,&b[172]);
  scrifld(z++,fm_u_EI,&disk_ei);
  for(k=0;k<2;k++) scrifld(z++,fm_uu5,&b[216+k*2]);
  c_10_jn(z++,&b[220]);
	scrfld(z++,6,2);
  key=scrupd(1,0x04A1);
  if(key!=106){
    updated=YES;
    if(b[2]=='J') b[172]='\0';
    c_jn_10(&b[220]); c_jn_10(&b[228]);
    if(bon_val=='I') *(uint16 *)&b[224]=1; else *(uint16 *)&b[224]=0;
    if(disk_ei=='E') *(uint16 *)&b[164]=1; else *(uint16 *)&b[164]=0;
    sysput(1044,44,&b[44]);
    sysput(2164,66,&b[164]);
		if(fldlen(6,1) && *s(6,2)){
			if(faskeyi(6,1,0)) fasinit(6);
			sysput(2991,2,u(6,1));
		}
  }
  if(key==111) ovl_exit(-1);
  if(key==101) goto endsr;

  if(ok(1804) && fldlen(6,40)<1){
    sysget(3584,56,&b[584]);
    scrget(1,194);z=1;
    scrifld(z++,fm_us6,&b[598]);
    if(fldlen(58,34)>0) scrifld(z++,fm_ui1,&b[604]);
    else {streepje(z++);*(int16 *)&b[604]=0;}
    jnd='N';if(b[606]==1) jnd='J'; else if(b[606]==2) jnd='D';
    scrifld(z++,fm_uJND,&jnd);
    scrifld(z++,fm_ugrb,&b[636]);
    key=scrupd(1,0x04A1);
    if(key!=106){
      updated=YES;
      c_jn_10(&b[606]);
      b[606]=0; if(jnd=='J') b[606]=1; else if(jnd=='D') b[606]=2;
      sysput(3584,56,&b[584]);
    }
    if(key==111) ovl_exit(-1);
    if(key==101) goto endsr;
  }

  if(taal()) goto endsr;

  endsr:;
}

static upd6()
{
  int16 j,key,papnr[20],prtnr[20],z;
 
  sysget(2304,80,b);
  scrget(1,188);
  scrofld(1,25,2,-1);
  scrfld(2,25,1);
  z=3;
  for(j=0;j<20;j++){
    papnr[j]=b[j*4];
    prtnr[j]=b[j*4+1];
    if(prtnr[j]<1) prtnr[j]=1;
  }
  for(j=0;j<17;j++){
    scrifld(z++,upapnr,&papnr[j]);
    c_12_dw(z++,&b[j*4+2]);
    scrifld(z++,uprtnr,&prtnr[j]);
  }
  key=scrupd(1,0x04A1);
  if(key!=106){
    updated=YES;
    for(j=0;j<20;j++){
      b[j*4]   =papnr[j];
      b[j*4+1] =prtnr[j];
      c_dw_12(&b[j*4+2]);
    }
    sysput(2304,80,b);
  }
  if(key==111) ovl_exit(-1);
}

static UpdateFtNummer()
{
  int16 key,k,z,posjnl1_=-1;
  uint16 tp_,jn_,bonnr_,ftnr_=65000,journl,ftnr1_=65000,last_vfa;
 
	sysget(3718,2,&bonnr_);
	sysget(2166,2,&journl);
  for(k=0;k<80;k++){
    sysget(10240+k*80,2,&jn_);
    if(jn_==journl){
			last_vfa=10260+k*80; sysget(last_vfa,2,&ftnr_);
		}
		else{
      sysget(10242+k*80,2,&tp_);
			if(tp_==2){
				posjnl1_=k; sysget(10260+posjnl1_*80,2,&ftnr1_);
				
			}
		}
		if(ftnr_!=65000 && ftnr1_!=65000) break;
  }
  if(ftnr_==65000){errnum=4;goto endsr;}

	scraddf(-1,0,0,0);z=1;
  scraddf(z,3,25,1);scrifld(z++,VarTextFmt(33,0),"Aanpassen factuurnummer/bonnummer");
  scraddf(z,6,5,0);scrifld(z++,VarTextFmt(30,0),"Laatst gemaakt factuurnummer :");
	scraddf(z,6,36,2);scrifld(z++,fm_uu5,&ftnr_);
	if(posjnl1_!=-1){	scraddf(z,6,43,2);scrifld(z++,fm_uu5,&ftnr1_);}
  scraddf(z,8,5,0);scrifld(z++,VarTextFmt(30,0),"Laatst gemaakt bonnummer.... :");
	scraddf(z,8,36,2);scrifld(z++,fm_uu5,&bonnr_);

  scraddf(z,23,1,8);scrifld(z++,VarTextFmt(9,0)," F1 stop ");
	scraddf(z,23,11,8);scrifld(z++,VarTextFmt(13,0)," F6 annuleer ");
	scraddf(z,23,25,8);scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
	scraddf(z,23,39,8);scrifld(z++,VarTextFmt(36,0)," F10 wis BLOKKAGE bon/factuurnummer ");
  key=scrupd(1,0x2A1);
	if(key==110){k=0; sysput(3774,2,&k);sysput(3776,2,&k);sysput(3778,2,&k);sysput(3780,2,&k);} // blokkage opheffen 
  else if(key!=106){
		sysput(last_vfa,2,&ftnr_);
		if(posjnl1_!=-1) sysput(10260+posjnl1_*80,2,&ftnr1_);
		sysput(3718,2,&bonnr_);
	}
	endsr:;
}

static upd7()
{
  int16 key;
  uint16 dat_new,dt_hardware;

  fasinfo(80,201);dt_hardware=*l(80,1);
 
  dat_new=*u(25,2);
  scrget(1,186);
  scrofld(1,25,2,-1);
  scrifld(2,fm_udat,&dat_new);
  key=scrupd(1,0x04A1);
  if(key!=106){
    *u(25,2)=dat_new;
		if(fldlen(25,11)){
			if(dat_new==dt_hardware) *s(25,11)=0; else *s(25,11)=1;
		}
  }
  if(key==111) ovl_exit(-1);
}

static upd8()
{
  int16 curs,j,k,key,z;
  uint16 elem[20];

  sysget(1812,2,&niv_MPW);
  if(passwrds[3-1]==0){
    scrget(1,172);
    key=scrupd(0xFFFF,0x419);
    if(key==111) ovl_exit(-1);
    if(key!=104) goto endsr;
  }
  else{
    if(!CheckPw(0,103,1)) ovl_exit(-1);
  }
  for(j=0;j<5;j++){
    if(passwrds[j]) for(k=0;k<8;k++) b[j*8+k]='#';
    else for(k=0;k<8;k++) b[j*8+k]='~';
  }
  curs=1;
  FOREVER{
    scrget(1,173);z=1;
    for(j=0;j<3;j++){
      scrifld(z++,fm_us8_U,&b[0+j*8]);
      if(j<2) if(voo_ok) scrifld(z++,fm_us8_U,&b[24+j*8]); else streepje(z++);
    }
    key=scrupd(curs,0x04B1);curs=1;
    if(key==106) goto endsr;
    if(key==105){
      for(j=0;j<5;j++) passwrds[j]=0;
    }
    else{
      if(!voo_ok) copy(&b[0],&b[24],16);
      for(j=0;j<5;j++){
				for(k=0;k<8;k++){
					if(b[j*8+k]!='#' && b[j*8+k]!='~') break;
				}
				if(k!=8) passwrds[j]=make_pw(&b[j*8]);
      }
      if(passwrds[3-1]==0) {errnum=38;curs=3;}
      for(j=0;j<5;j++) if(passwrds[j]==0) passwrds[j]=passwrds[3-1];
    }
    if(errnum==0){
      updated=YES;
      sysput(1876,6,&passwrds[0]);
      sysput(3878,4,&passwrds[3]);
      break;
    }
  }
  if(key==101 || key==105) goto endsr;
  if(key==111) ovl_exit(-1);
																					// BKH gebruikt : 0-0 10+ 11 13U 15V 16-25 29,35,36, 39 Vrij : 12,14,28,37,38
  for(k=0;k<9;k++) elem[k]=pwlevget(0,k); // 0-8
	for(k=9;k<11;k++) elem[k+1]=pwlevget(0,k); // 9-10
  elem[9]=pwlevget(0,11);elem[12]=pwlevget(0,13);elem[13]=pwlevget(0,15); elem[14]=pwlevget(0,39); // 13,15,39
  scrget(1,174);
  z=1;
  scrifld(z++,fm_uu1_L,&elem[14]);
  for(k=0;k<14;k++) scrifld(z++,fm_uu1_L,&elem[k]);
  key=scrupd(1,0x04A1);
  if(key==106) goto endsr;
  updated=YES;
  for(k=0;k<9;k++) pwlevset(0,elem[k],k);
	for(k=9;k<11;k++) pwlevset(0,elem[k+1],k);
  pwlevset(0,elem[9],11);pwlevset(0,elem[12],13);pwlevset(0,elem[13],15);
  pwlevset(0,elem[14],39);
  sysput(1882,10,&niveaus[0][0]);
  if(key==101) goto endsr;
  if(key==111) ovl_exit(-1);

  for(k=0;k<10;k++) elem[k]=pwlevget(0,16+k); // 16-27  29,35,36
  elem[10]=pwlevget(0,29);
	for(k=11;k<13;k++) elem[k]=pwlevget(0,15+k);
	elem[13]=pwlevget(0,35);elem[14]=pwlevget(0,36);
  scrget(1,175);
  z=1;
  for(k=0;k<15;k++) scrifld(z++,fm_uu1_L,&elem[k]);
  key=scrupd(1,0x04A1);
  if(key==106) goto endsr;
  updated=YES;
  for(k=0;k<10;k++) pwlevset(0,elem[k],16+k);
  pwlevset(0,elem[10],29);
	for(k=11;k<13;k++) pwlevset(0,elem[k],15+k);
	pwlevset(0,elem[13],35);pwlevset(0,elem[14],36);
  sysput(1882,10,&niveaus[0][0]);
  if(key==101) goto endsr;
  if(key==111) ovl_exit(-1);
 
  if(voo_ok){
    for(k=0;k<9;k++) elem[k]=pwlevget(1,k); // 0-8
    for(k=9;k<11;k++) elem[k+2]=pwlevget(1,k); // 0-9 10+ 13U 15B
    elem[9]=pwlevget(1,11);elem[10]=pwlevget(1,12);elem[13]=pwlevget(1,13);elem[14]=pwlevget(1,15);
    scrget(2,174);
    z=1;
    for(k=0;k<15;k++) scrifld(z++,fm_uu1_L,&elem[k]);
    key=scrupd(1,0x04A1);
    if(key==106) goto endsr;
    updated=YES;
    for(k=0;k<9;k++) pwlevset(1,elem[k],k);
		for(k=9;k<11;k++) pwlevset(1,elem[k+2],k);
    pwlevset(1,elem[9],11);pwlevset(1,elem[10],12);pwlevset(1,elem[13],13);pwlevset(1,elem[14],15);
    sysput(3882,10,&niveaus[1][0]);
    if(key==101) goto endsr;
    if(key==111) ovl_exit(-1);
  }

  endsr:;
}

static upd9()
{
  int16 k,key,j,z,curs=1;
  char filcode[23][4],buf4_[4];

  get_JN(4521,60);
  sysget(4498,23,&b[0]);
  for(k=0;k<23;k++) for(j=0;j<4;j++) filcode[k][j]='\0';
  for(k=0;k<23;k++){
    if(b[k]){
      if(b[k]>' ' && b[k]<128) filcode[k][0]=b[k];
      else{
	filcode[k][0]='x';
	byte2hex(b[k],&filcode[k][1]);
      }
    }
  }
  scrget(1,171);z=1;
  scrfld(z++,25,1);
  for(k=0;k<23;k++) scrifld(z++,fm_us3,&filcode[k][0]);
  for(k=0;k<4;k++) scrifld(z++,fm_uJNa,&b[60+k]);
  key=scrupd(curs,0x4A1);
  if(key!=106){
    for(k=0;k<23;k++){
      if(filcode[k][1]=='\0') b[k]=filcode[k][0];
      else if(filcode[k][0]=='x') b[k]=hex2byte(&filcode[k][1]);
      else {copy(&filcode[k][0],buf4_,3);buf4_[3]='\0';b[k]=val(buf4_);}
    }
    sysput(4498,23,&b[0]);
    put_JN(4521,60);
    updated=YES;
  }
  if(key==111) ovl_exit(-1);
  if(key==101 || key==106) goto endsr;

  endsr:;
}

static updf()
{
  int16 j,k,j1,key,z,curs=1,f_dat[10][8],p_used[10],curspos_;
  char b_let[10],attr_;
						
  zero((char *)&p_used[0],sizeof p_used); sysget(2304,80,b);
  for(j=0;j<20;j++){
    k=b[j*4];
    if(k>0 && k<11) p_used[k-1]=YES;
  }
 
  sysget(2384,160,b);
  for(j=0;j<10;j++){
    sysget(2384+j*16,16,(char *)&f_dat[j][0]);
    if(f_dat[j][7]==4){
      b_let[j]='W';
      for(k=0;k<7;k++) f_dat[j][k]=dots2mm(f_dat[j][k]);
    }
    else if(b[14+j*16]==3){
      b_let[j]='L';
      f_dat[j][4]=dots2mm(f_dat[j][4]);
      f_dat[j][5]=dots2mm(f_dat[j][5]);
    }
    else if(b[14+j*16]==2) b_let[j]='S';
    else if(b[14+j*16]==1) b_let[j]='J';
    else b_let[j]='N';
  }
  FOREVER{
    redo_189:;
    scrnum=0; scrget(1,189);
    scrofld(1,25,2,-1);
    scrfld(2,25,1);
    z=3;
    for(j=0;j<10;j++){
      k=j+1;attr_=0xFF; if(p_used[j]) attr_=0x0C;scrxfld(z++,fm_ou2,&k,attr_);
      attr_=0x02;
      if(b_let[j]=='S') attr_=0x09;
      else if(b_let[j]=='L') attr_=0x0A;
      else if(b_let[j]=='W') attr_=0x0B;
      for(j1=0;j1<7;j1++) scrxfld(z++,fm_ui4,&f_dat[j][j1],attr_);/* &b[j*16+j1*2],attr_);}*/
      scrxfld(-z,fm_uJNSLW,&b_let[j],attr_);z++;
    }
    key=scrupd(curs,0xBF); curs=1;curspos_=fldcurs;
    if(key==106) break;
    if(key>=102 && key<=105){
      k=(curspos_-3) /9;zero((char *)&f_dat[k][0],sizeof f_dat[0]);
      if(key==102){
	f_dat[k][0]=2850;f_dat[k][1]=3600;f_dat[k][2]=-200;f_dat[k][3]=200;
	f_dat[k][4]=50;f_dat[k][5]=240;f_dat[k][6]=50;b_let[k]='J';
      }
      if(key==103){
	f_dat[k][0]=2850;f_dat[k][1]=3400;f_dat[k][2]=-200;f_dat[k][3]=200;
	f_dat[k][4]=50;f_dat[k][5]=240;f_dat[k][6]=0;b_let[k]='S';
      }
      if(key==104){
	f_dat[k][0]=2100;f_dat[k][1]=2970;f_dat[k][2]=0;f_dat[k][3]=100;
	f_dat[k][4]=100;f_dat[k][5]=100;f_dat[k][6]=0;b_let[k]='W';
      }
      if(key==105){
	f_dat[k][0]=3;f_dat[k][1]=8;f_dat[k][2]=70;f_dat[k][3]=34;
	f_dat[k][4]=100;f_dat[k][5]=210;f_dat[k][6]=0;b_let[k]='L';
      }
      curs=curspos_;goto redo_189;
    }
    for(j=0;j<10;j++){
      if(b_let[j]=='L'){
/*     copy(&b[j*16],(char *)&f_dat[0],16); */
	if(f_dat[j][0]<1 || f_dat[j][0]>10){errnum=34;curs=3+j*9;goto redo_189;}
	if(f_dat[j][1]<1 || f_dat[j][1]>20){errnum=34;curs=4+j*9;goto redo_189;}
	if(f_dat[j][2]<1){errnum=34;curs=5+j*9;goto redo_189;}
	if(f_dat[j][3]<1){errnum=34;curs=6+j*9;goto redo_189;}
	k=valu_cnv("EUR","EUR",(double)((double)f_dat[j][2] / (0.204*40)),(double)1.);
	k+=1+f_dat[j][6];
	if(k<2 || k>50){errnum=34;curs=5+j*9;goto redo_189;}/* lettertype */
      }
    }

    if(key==18){curs=curspos_+1; goto redo_189;}

    if(key==101 || key==108) {
      updated=YES;
      for(j=0;j<10;j++){
	if(b_let[j]=='W'){
	  f_dat[j][7]=4;
	  for(k=0;k<7;k++) f_dat[j][k]=mm2dots(f_dat[j][k]);
	}
	else if(b_let[j]=='L'){
	  f_dat[j][7]=3;
	  f_dat[j][4]=mm2dots(f_dat[j][4]);
	  f_dat[j][5]=mm2dots(f_dat[j][5]);
	}
	else if(b_let[j]=='S') f_dat[j][7]=2;
	else if(b_let[j]=='J') f_dat[j][7]=1;
	else f_dat[j][7]=0;
	sysput(2384+j*16,16,(char *)&f_dat[j][0]);
      }
      break;
    }
  }
}

static dots2mm(dots)
int16 dots;
{
  float qlv_;

  qlv_=dots; qlv_/=300.; qlv_*=254.;
  qlv_=valu_cnv("EUR","EUR",(double)(qlv_),(double)1.);
  return (int16)(qlv_);
}
 
static mm2dots(mm)
int16 mm;
{
  float qlv_;
					
  qlv_=mm; qlv_*=300.; qlv_/=254.;
  qlv_=valu_cnv("EUR","EUR",(double)(qlv_),(double)1.);
  return (int16)(qlv_);
}


static scrxfld(z,pfmt_,pvar_,attr_)
int16 z;
char *pfmt_,*pvar_,attr_;
{
  scrifld(z,pfmt_,pvar_); if(z<0) z=-z; scrchat(z,attr_);
}



static upd_euro()
{
  int16 key;
  char choice;
						
  FOREVER {
    scrget(1,200);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x81);
    if(key==101) break;
    switch (choice){
      case '1': parm_eur(); break;
      case 'B': if(warn_ok(0)){*u(26,1)=0; ovlexit(97);} break;
      case 'C': if(warn_ok(0)){*u(26,1)=1; ovlexit(97);} break;
      case 'D': if(warn_ok(1)) ovlexit(197); break;
      case 'K': if(warn_ok(0)){*u(26,1)=2; ovlexit(97);} break;
      case 'R': if(cmpstr(def_munt,"EUR",3)==0){
		  copy("BEF",def_munt,3); sysput(294,4,def_munt);
		}
		else {
		  copy("EUR",def_munt,3); sysput(294,4,def_munt);
		}
		break;
      default:  errnum=34; break;
    }
  }
  endsr:;
}

static upd_divrs()
{
  int16 key;
  char choice;
								
  if(warn_ok(0)==NO) goto endsr;
  FOREVER {
    scrget(1,217);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x81);
    if(key==101) break;
    switch (choice){
      case '1': if(ovltest(66)) ovlexit(66); else errnum=34; break;
      case '2': if(fldlen(1,12) && fldlen(1,18) && fldlen(1,19)) ConvertJamaRek2IBAN(); else errnum=34; break;
      case '3': if(ovltest(93)) ovlexit(93); else errnum=34; break;
	  case '4': if(ovltest(2240) && fldlen(2,128)) ControleerKlantenOpPeppol(); else errnum=34; break;
	  case '5': if(ovltest(2240) && fldlen(2,128) && fldlen(2,121) && fldlen(2,122)) WisAutoMail(); else errnum=34; break;
      case 'C': CorrectCentRekening(); break;
      case 'G': ChangeGrbNr(); break;
			case 'H': HerschikGroepen(); break;

      case 'R': RoundBkhBedragen(); break;
      default:  errnum=34; break;
    }
  }
  endsr:;
}
 
static ControleerKlantenOpPeppol()
{
  int16 k,g,mode4_,curs,z,key,ok_;
	uint16 dt_vanaf_;

  if(DisplayWarning("Wenst U echt de registratie van alle klanten te controleren op peppol?",61,1)!=YES) goto endsr;
	dt_vanaf_=*u(25,2)-360;
	fasinit(2);scrnum=0;scrget(1,170);
	FOREVER{
		next:;
		if(faskeyi(2,2,2)) break;
		if(*s(2,128)=='P') goto next;
		if(*l(2,10)==999999999 || *l(2,10)==0 || *(s(2,10)+3) & 0x40) goto next;
		scrfld(10,2,3,-1);scrupd(-3,0);
		if(fldlen(4,1)==0) ok_=YES;
		else{
			fasinit(4);*u(4,5)=*u(2,1)+30000;mode4_=1;ok_=NO;
			scrfld(10,2,3,-1);scrupd(-3,0);
			FOREVER{
				if(faskeyi(4,4,mode4_)) break; mode4_=2;
				if(*u(4,5)!=*u(2,1)+30000) break;
				if(*u(4,4)>=dt_vanaf_) {ok_=YES;break;}
			}
		}
		if(ok_){
			if(ovlcall(2240,20)>0){*s(2,128)='P'; fasupd(2);}
		}
	}
	endsr:;
}

static WisAutoMail()
{
  int16 k,g,mode4_,curs,z,key,ok_;
  uint16 dt_vanaf_;

  if(DisplayWarning("Automatisch mailen van alle peppol-geregistreerde klanten afzetten ???",61,1)!=YES) goto endsr;
  fasinit(2);scrnum=0;scrget(1,7);
  FOREVER{
    next:;
	if(faskeyi(2,2,2)) break;
	if(*s(2,128)=='P'){
	  *s(2,121)='N'; *s(2,122)='N'; fasupd(2);
	}
  }
  endsr:;
}




static HerschikGroepen()
{
  int16 k,g,start,rebuild_=YES,curs,z,z_base_,key,pos_,tbnewgroep[100];
	long	n;

	
	for(k=0;k<100;k++) tbnewgroep[k]=0;

  start=1;curs=2;
  FOREVER{
    redo:;
    if(rebuild_){
      scraddf(-1,0,0,0);z=1;
      scraddf(z++,1,25,2);
      scraddf(z++,4,1,3);scraddf(z++,4,7,3);  // titel 
			for(k=0;k<15;k++){
         scraddf(z++,5+k,3,2);scraddf(z++,5+k,4,2);scraddf(z++,5+k,10,2);  
			}
			scraddf(z++,23,1,8);scraddf(z++,23,11,8);  // functietoetsen 
		  scraddpicto(5,0,64,22,4,2,18,0,4,"Vorig");
		  scraddpicto(6,0,60,22,4,2,13,0,4,"Volgend");
      rebuild_=NO;
    }
    z=1;
		scrifld(z++,VarTextFmt(40,0),"Herschikken artikels in andere groepen");
		scrifld(z++,VarTextFmt(5,0),"Nieuw"); scrifld(z++,VarTextFmt(6,0),"Huidige groep");
		for(k=start;k<start+15;k++){
			if(k>=99) break;
      fasinit(52);*u(52,1)=k;
      g=fasgeti(52);
      scrifld(z++,fm_uu2,&tbnewgroep[k]); scrofld(z++,52,1,-1); scrofld(z++,52,14,-1);
		}
		scrifld(z++,VarTextFmt(9,0)," F1 stop");scrifld(z++,VarTextFmt(13,0)," F8 neem aan");
    key=scrupd(curs,0x87);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) goto endsr;
		if(key==108){
				if(DisplayWarning("Wenst U echt de groepen op artikels te wijzigen???",61,1)!=YES) goto endsr;
        break;
		}
				
    if(key==5005 || key==102) start-=15;
    if(key==5006 || key==103) {start+=15;if(start>=99-15) start=99-15;}
    if(start<1) start=1;
  }

	scrget(1,170);scrifld(10,VarTextFmt(63,0),"Bezig met wijzigen artikelfiches ...");scrupd(-3,0);
 
  fasinit(6); n=0;
  FOREVER{
    *u(6,1)=++n;
		if((n%500)==0){scrget(1,170);scrfld(18,6,1);scrupd(-3,0);}
    g=fasgeti(6);
    if(g==47)break;
    if(g!=46){		/* deleted record */
			
			if(tbnewgroep[*u(6,9)]) {*u(6,9)=tbnewgroep[*u(6,9)]; fasupd(6);}
		}
  }
	scrget(1,170);scrifld(10,VarTextFmt(63,0),"Bezig met wijzigen prijsafspraken ...");scrupd(-3,0);
 
  fasinit(9); n=0;
  FOREVER{
    if(fldlen(9,1)==4) *l(9,1)=++n; else *u(9,1)=++n;
		if((n%500)==0){scrget(1,170);scrfld(18,9,1);scrupd(-3,0);}
    g=fasgeti(9);
    if(g==47)break;
    if(g!=46){		/* deleted record */
			
			if(*u(9,19) && *u(9,19)<99 && tbnewgroep[*u(9,19)]) {*u(9,19)=tbnewgroep[*u(9,19)]; fasupd(9);}
		}
  }
	if(fldlen(16,1)==0) goto endsr;
	scrget(1,170);scrifld(10,VarTextFmt(63,0),"Bezig met wijzigen historieken ...");scrupd(-3,0);
  fasinit(16); n=0;
  FOREVER{
    *l(16,1)=++n;
		if((n%500)==0){scrnum=0;scrget(1,170);scrfld(18,16,1);scrupd(-3,0);}
    g=fasgeti(16);
    if(g==47)break;
    if(g!=46){		/* deleted record */
			if(*l(16,23) && *l(16,23)<99 && tbnewgroep[*l(16,23)]) {*l(16,23)=tbnewgroep[*l(16,23)]; fasupd(16);}
		}
  }
  endsr:;
  fasinfo(6,101);
}




static ChangeGrbNr()
{
  int16 g,j,k,key;
  char password[9],str_[10];
  uint16 n;
  long grbold_=0,grbnew_=0;
 
	if(fldlen(4,1)==0) goto endsr;
  fileopen(3);fileopen(4); 
	FOREVER{
		redo:;
		scrget(1,170);
		scrifld(4,VarTextFmt(40,0),"Wijzigen GRB-rekeningen in GRB en STK... ");
  
		scrifld(8,VarTextFmt(40,0),"Geef OUDE rekening ");
		scrifld(9,fm_ugrb,&grbold_);
 		scrifld(10,VarTextFmt(40,0),"Geef NIEUWE rekening");
		scrifld(11,fm_ugrb,&grbnew_);
		scrifld(16,VarTextFmt(40,0),"F1 stop     F8 begin aanpassen");
  
		key=scrupd(1,0x481);
		if(key==101) break;
		if(grbold_==0 || grbnew_==0) {errnum=38;goto redo;}
		if(key!=108) goto redo;
		fasinit(3);*l(3,2)=grbold_;if(faskeyi(3,1,0)){errnum=2;goto redo;}
		fasinit(3);*l(3,2)=grbnew_;if(faskeyi(3,1,0)==0){errnum=31;goto redo;}
		fasinit(3);*l(3,2)=grbold_;  faskeyi(3,1,0); *l(3,2)=grbnew_; if(fasupd(3)){errnum=31;goto redo;}

		scrnum=0;scrget(1,170);scrifld(8,VarTextFmt(40,0),"Boekingen aanpassen ...");scrupd(-3,0);
		if(fldlen(4,6)) {fileopen(4);change_fas(4,6,grbold_,grbnew_);}
	} 
  fasflush(0);
  endsr:;
  ovlexit(-1);
}

static change_fas(stu_,fld_,grbold_,grbnew_)
int16 stu_,fld_;
long grbold_,grbnew_;
{
  int16 k,len1_;
  uint16 g,err_pos_=0;
	long n;

  fasinit(stu_);
  n=0; len1_=fldlen(stu_,1);
  FOREVER{
next:;
    if(len1_==4) *l(stu_,1)=++n; else *u(stu_,1)=++n;
		if((n%500)==0){scrget(1,170);scrfld(18,stu_,1);scrupd(-3,0);}
    g=fasgeti(stu_);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
			if(*l(stu_,fld_)==grbold_){*l(stu_,fld_)=grbnew_;fasupd(stu_);}
		}
  }
  fasinfo(stu_,101);
}

static RoundBkhBedragen() // opnieuw afronden bedragen nav grb-balans niet in evenwicht
{
  int16 g,k,dd,mm,yy;
  long n,jn_,rek_,kltcent,levcent;

  if(fldlen(4,1)==0) goto endsr;
  fasunlck(0); fileopen(4);fileopen(1);fileopen(2);fileopen(3);
  sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);
	if(DisplayWarning("Wenst U echt de bedragen in de boekhouding te controleren (afronden)???",61,1)!=YES) goto endsr;
  scrget(1,170);scrifld(10,VarTextFmt(63,0),"Bezig met controle...");scrupd(-3,0);
	jddate(*u(25,2),&yy,&mm,&dd);
  fasinit(4);fasinit(3);
  n=0;scrnum=0;
	FOREVER{
		next:;
    *l(4,1)=++n;
		if((n%100)==0){scrifld(20,fm_ol8,&n);scrupd(-3,0);}
    g=fasgeti(4);
    if(g==47)break;
    if(g!=46){/* deleted record */
			for(k=32;k<=34;k++){
				if(fldlen(4,k)==8){
					*d(4,k)=valu_cnv("EUR","EUR",(double)(*d(4,k)),(double)0.01);
				}
			}
			fasupd(4);
		}
	}
	endsr:;
}

CorrectCentRekening() // controleren of centralitierekening 4000/4400 goed is ingevuld
{
  int16 g,dd,mm,yy;
  long n,jn_,rek_,kltcent,levcent;

 
  fasunlck(0); fileopen(4);fileopen(1);fileopen(2);fileopen(3);
  sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);
	if(DisplayWarning("Wenst U echt de boekhouding te controleren (4000/4400)???",61,1)!=YES) goto endsr;
  scrget(1,170);scrifld(10,VarTextFmt(63,0),"Bezig met controle...");scrupd(-3,0);
	jddate(*u(25,2),&yy,&mm,&dd);
  fasinit(4);fasinit(3);
  n=0;scrnum=0;
	FOREVER{
		next:;
    *l(4,1)=++n;
		if((n%100)==0){scrifld(20,fm_ol8,&n);scrupd(-3,0);}
    g=fasgeti(4);
    if(g==47)break;
    if(g!=46){/* deleted record */
			rek_=*l(4,6);
			fasinit(3);*l(3,2)=*l(4,6);
			if(*l(4,6)==0 || faskeyi(3,1,0)){
//scrget(1,170);
//jn_=*s(4,2); scrifld(1,fm_nr,&jn_);
//scrfld(2,4,3);
//scrfld(3,4,4);
//scrfld(4,4,5);
//scrfld(5,4,6);
//scrupd(-1,0);
//if(*u(4,4)>*u(25,2)-30){
//	dt_=*u(4,4);
//}
				if(*u(4,5)>=1 && *u(4,5)<30000) *l(4,6)=levcent;
				else if(*u(4,5)>=30000 && *u(4,5)<60000) *l(4,6)=kltcent;
			  else{
					fasinit(3);*u(3,1)=*u(4,5)-60000; 
					if(fasgeti(3)==0) *l(4,6)=*u(3,2);
				}
				fasupd(4);
			}
		}
	}
	endsr:;
}

static ConvertJamaRek2IBAN()
{
	uint16 n,g,k;

	if(DisplayWarning("Wenst U echt de IBAN en BIC in te vullen op leveranciersfiches?",61,1)==NO) return 0; 
  scrget(1,7);scrupd(-3,0);
	fileopen(1);
	n=0;
	FOREVER{
		next:;
		*u(1,1)=++n;
		g=fasgeti(1);
		if(g==47)break;
		if(g!=46){
			for(k=0;k<5;k++) if(*(s(1,12)+k)!='\0') break;
			if(*s(1,18)){
				if(IbanTools(s(1,18),s(1,19),s(1,12),1)==0) {fasupd(1);goto next;}
			}
			if(k<5) IbanTools(s(1,18),s(1,19),s(1,12),2); // Belgische invullen
			else{*s(1,18)=0; *s(1,19)=0;} // anders clearen
			fasupd(1);
		}
	}
}



static SpecialTools()
{
	char choice='\0';
  int16 key;
	  
	if(!CheckPw(0,10,0)) ovlexit(-1);

  FOREVER {
    scrget(1,252);
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
    key=scrupd(2,0x0401);
    if(key<101){
      switch (choice){
				case '1': UpSys(); break;
				case '2': Reset1Veld(); break;
				case '3': ExecuteOvl(); break;
				case '4': ovlcall(2501,0);break;
				case '5': CopyVeldToOther(); break;
				case '6': AdjustExtendedLogging(); break;
				case '7': Kill1Record(); break;
				case '8': DeleteAllRecords(); break;
				case 'D': ovlcall(2504,0); break;
#if _DEBUG || FLAGDEM
				case 'P': SetPeppol_Debug_Productie(); break;
#endif
				default:  errnum=34; break;
      }
    }
    if(key==101 || key==111) break;
  }
}

static SetPeppol_Debug_Productie()
{
	int16 GEENdebug_;

	sysget(1284, 2, &GEENdebug_);
	if(GEENdebug_){
		if(DisplayWarning("Peppolfuncties in DEBUG-mode zetten? (BTW-nummers nakijken!)",61,1)){
			GEENdebug_=0; sysput(1284, 2, &GEENdebug_);
		}
	}
	else{
		if(DisplayWarning("Peppolfuncties in PRODUCTIE-mode zetten? (PAS OP: ECHT VERSTUREN!!!)",61,1)){
			GEENdebug_=1; sysput(1284, 2, &GEENdebug_);
		}
	}
}
	
static UpSys()
{
  int16 curs=1,z,key,j,k;
  char sysval[100],type,str_[100];
  uint16 lengte,syspos;
 
  syspos=0;type='\0';lengte=0;zero(sysval,sizeof sysval);
  FOREVER{
    redo:;
    scrnum=0;scrget(1,248);z=1;
    scrifld(z++,fm_uu5,&syspos);
    scrifld(z++,fm_us1_U,&type);
    scrifld(z++,fm_uu2,&lengte);
    key=scrupd(curs,0xE1);
    if(key==101 || key==106) break;
    if(syspos<34 || syspos>32700) {curs=1; errnum=34; goto redo;}
    if(type=='\0') {curs=2;errnum=38;goto redo;}
    if(type=='S' && (lengte<1 || lengte>70)){curs=3;errnum=34;goto redo;}
    switch (type){
      case 'S' : sysget(syspos,lengte,sysval);copy(fm_us30,fmt,sizeof fm_us30);
		 fmt[2]=lengte; break;
      case 'U' : lengte=2; sysget(syspos,lengte,sysval);
		 copy(fm_uu5,fmt,sizeof fm_uu5);
		 break;
      case 'I' : lengte=2; sysget(syspos,lengte,sysval);
		 copy(fm_ui5,fmt,sizeof fm_ui5);
		 break;
      case 'L' : lengte=4; sysget(syspos,lengte,sysval);
		 copy(fm_ul8,fmt,sizeof fm_ul8);
		 break;
      case 'F' : lengte=4; sysget(syspos,lengte,sysval);
		 copy(fm_uf6_2,fmt,sizeof fm_uf6_2);
		 break;
      case 'G' : lengte=4; sysget(syspos,lengte,sysval);
		 copy(fm_ugrb,fmt,sizeof fm_ugrb);
		 break;
      case 'J' : lengte=2; sysget(syspos,lengte,sysval);
		 copy(fm_udat,fmt,sizeof fm_udat);
		 break;
      case 'D' : lengte=8; sysget(syspos,lengte,sysval);
		 copy(fm_ud6_2,fmt,sizeof fm_ud6_2);
		 break;
      case 'H' : if(lengte<1 || lengte>4) errnum=34;
				         else{
									 sysget(syspos,lengte,str_);
									 zero(sysval,sizeof sysval);j=0;
									 for(k=lengte-1;k>=0;k--) {byte2hex(str_[k],&sysval[j]); j+=2;}
									 copy(fm_u09AF,fmt,sizeof fm_u09AF); fmt[2]=lengte*2;
									 break;
								 }
      default :  errnum=34; curs=2; break;
    }
    if(errnum) goto redo;
	
    scrnum=0;scrget(1,248);z=1;
    scrifld(z++,fm_ou5,&syspos);
    scrifld(z++,fm_os1,&type);
    scrifld(z++,fm_ou2,&lengte);
    scrifld(z++,fmt,sysval);
    key=scrupd(4,0xA1);
    if(key!=101 && key!=106){
			if(type=='H') {
				zero(str_,sizeof str_); j=(lengte-1)*2;
				for(k=0;k<lengte;k++) {str_[k]=hex2byte(&sysval[j]);j-=2;}
				sysput(syspos,lengte,str_);
			}
      else sysput(syspos,lengte,sysval);
    }
    syspos=0;type='\0';lengte=0;zero(sysval,sizeof sysval);
    curs=1;
  }
  endsr:;
}

static Reset1Veld()
{
  int16 j,z,g,key,fld_,len1_,flen_,copyfld_,curs=1;
  long n;
  char buf_[200],buf1_[200];
  char chg_allways_='N',*ps_,*pn_;
  
  
	zero(buf_,sizeof buf_);
  for(j=0;j<15;j++){ // eerste alle files opengooien
    sysget(300+17*j,15,buf_);
    if(buf_[0]) fasopen(buf_,0);
  }
  stu=0;fld_=0;copyfld_=0;
  FOREVER{
redo:;
		scrnum=0;scrget(1,253);z=1;
    scrifld(z++,fm_uu2,&stu);scrifld(-z,fm_uu3,&fld_);z++;
		if(fld_<1 || fld_>200 || fldlen(stu,fld_)==0) scrifld(z++,VarTextFmt(10,0),"FOUT!"); 
		else scrifld(z++,VarTextFmt(20,0),s(stu,-fld_)); 
		scraddf(z,23,41,8);scrifld(z++,VarTextFmt(18,0)," F8 Vul waarde in ");
    key=scrupd(curs,0xE1);curs=1;
    if(key==101 || key==106) break;
    if(stu==0) {curs=1; errnum=38; goto redo;}
		if(fld_<=1) {curs=2; errnum=34; goto redo;}
		if(fldlen(stu,fld_)==0) {curs=1; errnum=34; goto redo;}
		len1_=fldlen(stu,1); if(len1_==0) {curs=1; errnum=34; goto redo;} // recordnummer moet bestaan 
		fasinfo(stu,6); if(len1_==4) n=*l(stu,1); else n=*u(stu,1);
    if(n==0) {curs=1; errnum=34; goto redo;}// er moeten ook records in zitten (geen work)
		if(key==18) curs=fldcurs+1;
  	if(key!=108) goto redo;
		fmt_get(stu,fld_);fmt[1]|=0x40;zero(buf_,sizeof buf_);zero(buf1_,sizeof buf1_);
		curs=3;
		redo_upd:;
		scrnum=0;scrget(1,253);z=1;
    scrifld(z++,fm_ou2,&stu);scrifld(z++,fm_ou3,&fld_);
		if(fld_==0) z++;
		else if(fld_<1 || fld_>200 || fldlen(stu,fld_)==0) scrifld(z++,VarTextFmt(10,0),"FOUT!"); 
		else scrifld(z++,VarTextFmt(20,0),s(stu,-fld_)); 
		scrifld(-z,fmt,buf_);z++;
		scrifld(-z,fm_uu3,&copyfld_);z++;
		if(copyfld_==0) z++;
		else if(copyfld_<1 || copyfld_>200 || fldlen(stu,copyfld_)==0) scrifld(z++,VarTextFmt(10,0),"FOUT!"); 
		else scrifld(z++,VarTextFmt(20,0),s(stu,-copyfld_)); 
		scrifld(z++,fm_uJN,&chg_allways_);
		scrifld(z++,fmt,buf1_);
		scraddf(z,23,41,8);scrifld(z++,VarTextFmt(13,0)," F8 Voer uit ");
    key=scrupd(curs,0xE1);curs=3;
		if(key==101) break;
		if(copyfld_){
			for(z=0;z<fldlen(stu,fld_);z++) if(buf_[z]!='\0') break;
			if(z<fldlen(stu,fld_)){curs=5;errnum=52;goto redo_upd;}
			if(copyfld_<2 || copyfld_==fld_){curs=5;errnum=52;goto redo_upd;}
			if(fldlen(stu,fld_)!=fldlen(stu,copyfld_)){ // bij string mag het afwijken
				if(fldlen(stu,copyfld_)==0) {curs=5;errnum=34;goto redo_upd;}
				fmt_get(stu,fld_);if((fmt[1]&0x38)!=0x08) {curs=5;errnum=34;goto redo_upd;}
				fmt_get(stu,copyfld_);if((fmt[1]&0x38)!=0x08) {curs=5;errnum=34;goto redo_upd;}
			}
		}
		if(key==18) curs=fldcurs+1;
		if(key!=108) goto redo_upd;
    if(key==108){
			if(copyfld_ && fldlen(stu,fld_)!=fldlen(stu,copyfld_)){
				if(DisplayWarning("De lengte van de velden zijn verschillend! Toch doorgaan?",61,1)==NO) goto redo_upd;
			}
			if(stu==6){
				if(ovltest(2215)){
  				seldata.prx_klt=0;
  				seldata.selp_use=NO;
  				if(ovlcall(2215,4)) break;
				}
			}
			if(stu==1 || stu==2){
				selp_use=NO;
        if(selp_ask()) break;
			}
			if(warn_ok(0)==NO) break;
			scrget(1,7);scrupd(-3,0);scraddfield(100,1,20,0);
			fasinit(stu); len1_=fldlen(stu,1); n=0; flen_=fldlen(stu,fld_);ps_=s(stu,fld_);
			if(copyfld_){
				pn_=s(stu,copyfld_); 
				if(flen_>fldlen(stu,copyfld_)) flen_=fldlen(stu,copyfld_);
			}
			else pn_=buf_;
			fasunlck(-2); // critical 
			FOREVER{
			next:;
        if(len1_==4) *l(stu,1)=++n; else *u(stu,1)=++n;
				if((n%1000)==0){scrifld(100,fm_ol8,&n);scrupd(-3,0);}
        g=fasgeti(stu);
        if(g==47)break;
        if(g==0){
					if(stu==6){
						if(DirCall_DRK2215_SelectArtikel()==NO) goto next;
					}
					if(stu==1 || stu==2){
						if(selp_tst()==NO) goto next;
					}
					if(chg_allways_!='J'){
						for(j=0;j<flen_;j++) if(*(ps_+j)!=buf1_[j]) break;
						if(j<flen_) goto next;
					}
					copy(pn_,s(stu,fld_),flen_); fasupd(stu);
				}
      }
      break;
		}
  }
}

static Kill1Record()
{
  int16 j,z,key,stu_=0,curs=1;
  long record_;
  char buf_[200];
  
  
	zero(buf_,sizeof buf_);
  for(j=0;j<15;j++){ // eerste alle files opengooien
    sysget(300+17*j,15,buf_);
    if(buf_[0]) fasopen(buf_,0);
  }
  stu_=0;record_=0;
  FOREVER{
redo:;
		scrnum=0;scrget(1,268);z=1;
    scrifld(z++,fm_uu2,&stu_);scrifld(-z,fm_ul8,&record_);z++;
		if(stu_<1 || stu_>200 || fldlen(stu_,1)==0) scrifld(z++,VarTextFmt(10,0),"FOUT!"); 
		else {fasinfo(stu_,7);scrifld(z++,VarTextFmt(20,0),s(stu_,1)); }
    key=scrupd(curs,0xE1);curs=1;
    if(key==101 || key==106) break;
    if(stu_<1 || stu_>99) {curs=1; errnum=38; goto redo;}
		if(record_<1 || (fldlen(stu_,1)==2 && record_>60000)) {curs=2; errnum=34; goto redo;}
		fasinit(stu_); 
		if(fldlen(stu_,1)==4)*l(stu_,1)=record_; else *u(stu_,1)=record_;
		if(fasgetu(stu_)){errnum=39;curs=2; goto redo;}
		if(key==18) curs=fldcurs+1;
  	if(key==108){
			 if(DisplayWarning("Wenst U echt deze record te schrappen?",61,1)) faskill(stu_);
		}
  }
}

static DeleteAllRecords()
{
  int16 j,z,g,key,stu_=0,curs=1,len1_;
  long n;
  char buf_[200];
  
  
	zero(buf_,sizeof buf_);
  for(j=0;j<15;j++){ // eerste alle files opengooien
    sysget(300+17*j,15,buf_);
    if(buf_[0]) fasopen(buf_,0);
  }
  stu_=0;
  FOREVER{
redo:;
		scrnum=0;scrget(1,268);z=1;
    scrifld(-z,fm_uu2,&stu_);z++;
		if(stu_<1 || stu_>99 || fldlen(stu_,1)==0) scrifld(z++,VarTextFmt(10,0),"FOUT!"); 
		else {fasinfo(stu_,7);scrifld(z++,VarTextFmt(20,0),s(stu_,1)); }
    key=scrupd(curs,0xE1);curs=1;
    if(key==101 || key==106) break;
    if(stu_<1 || stu_>99) {curs=1; errnum=38; goto redo;}
		if(key==18) curs=fldcurs+1;
  	if(key==108){
		  if(DisplayWarning("Wenst U echt ALLE records van deze tabel te schrappen?",61,1)){
				scrget(1,7);scrupd(-3,0);scraddfield(100,1,20,0);
				fasinit(stu_); n=0; len1_=fldlen(stu_,1);
				fasunlck(-2); // critical 
				FOREVER{
				next:;
					if(len1_==4) *l(stu_,1)=++n; else *u(stu_,1)=++n;
					if((n%1000)==0){scrifld(100,fm_ol8,&n);scrupd(-3,0);}
					g=fasgeti(stu_);
					if(g==47)break;
					if(g==0) faskill(stu_);
				}
			}
		}
  }
}

static ExecuteOvl()
{
  uint16 z,key,ovlnr_=0,param_=0;
  
  FOREVER{
    redo:;
    scrnum=0;scrget(1,251);z=1;
    scrifld(z++,fm_uu4,&ovlnr_);
		scrifld(z++,fm_uu4,&param_);
    key=scrupd(1,0x81);
    if(key==101 || key==106) break;
    if(ovlnr_<2) {errnum=38; goto redo;}
		if(key==108 && ovltest(ovlnr_)) {
			if(param_) ovlcall(ovlnr_,param_);  else ovlexit(ovlnr_);
			break;
		}
	}
}

static CopyVeldToOther()
{
  int16 j,z,g,key,stu_,fromfld_,tofld_,flen_,len1_,curs=3;
	char buf_[200],only_emptyfld_;
  long n;

  
	zero(buf_,sizeof buf_);
  for(j=0;j<15;j++){ // eerste alle files opengooien
    sysget(300+17*j,15,buf_);
    if(buf_[0]) fasopen(buf_,0);
  }
  stu_=0;fromfld_=0;tofld_=0;only_emptyfld_='N';

  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,3,10,0xA);
    scraddf(z++,6,5,0);scraddf(z++,6,43,2);scraddf(z++,6,46,0);scraddf(z++,6,47,2);scraddf(z++,6,50,0);scraddf(z++,6,53,0x9);
    scraddf(z++,8,5,0);scraddf(z++,8,43,2);scraddf(z++,8,49,0x9);
		scraddf(z++,11,5,0);scraddf(z++,11,49,2);
		scraddf(z++,23,1,8);scraddf(z++,23,11,8);scraddf(z++,23,27,8);
    z=1;
    scrifld(z++,VarTextFmt(61,0)," Kopieren veld naar een ander veld (binnen zelfde structuur) ");
		scrifld(z++,VarTextFmt(40,0),"Geef te kopieren structuur en veld : ("); scrifld(z++,fm_uu2,&stu_);
    scrifld(z++,fm_os1,","); scrifld(-z,fm_uu3,&fromfld_);z++;scrifld(z++,fm_os1,")");
		if(fromfld_==0) z++;
		else if(fromfld_<1 || fromfld_>200 || fldlen(stu_,fromfld_)==0) scrifld(z++,VarTextFmt(10,0),"FOUT!"); 
		else scrifld(z++,VarTextFmt(20,0),s(stu_,-fromfld_)); 
    scrifld(z++,VarTextFmt(40,0),"Geef het nieuwe veld ............. : ");scrifld(-z,fm_uu3,&tofld_);z++;
		if(tofld_==0) z++;
		else if(tofld_<1 || tofld_>200 || fldlen(stu_,tofld_)==0) scrifld(z++,VarTextFmt(10,0),"FOUT!"); 
		else scrifld(z++,VarTextFmt(20,0),s(stu_,-tofld_)); 
    scrifld(z++,VarTextFmt(44,0),"Enkel kopieren indien nieuwe veld leeg is : ");scrifld(z++,fm_uJN,&only_emptyfld_);
    scrifld(z++,VarTextFmt(9,0)," F1 stop ");scrifld(z++,VarTextFmt(15,0)," F7 herdisplay ");
		scrifld(z++,VarTextFmt(19,0)," F8 begin kopieren ");
    key=scrupd(curs,0xC1);curs=1;
    if(key==101 || key==106) break;
    if(stu_==0) {curs=3; errnum=38; goto redo;}
		if(fromfld_<=1) {curs=5; errnum=34; goto redo;}
		if(fldlen(stu_,fromfld_)==0) {curs=5; errnum=34; goto redo;}
		if(tofld_==0 || tofld_==fromfld_ || fldlen(stu_,fromfld_)!=fldlen(stu_,tofld_)) {curs=8; errnum=34; goto redo;}
		if(fldlen(stu_,1)==0) {curs=3; errnum=34; goto redo;} // recordnummer moet bestaan 
		fasinfo(stu_,6);len1_=fldlen(stu_,1);
    if(len1_==4) n=*l(stu_,1); else n=*u(stu_,1);
    if(n==0) {curs=1; errnum=34; goto redo;}// er moeten ook records in zitten (geen work)
		if(key==18) curs=fldcurs+1;
		if(key!=108) goto redo;
    if(key==108){
			if(warn_ok(0)==NO) break;
			scrget(1,7);scrupd(-3,0);scraddfield(100,1,20,0);
			fasinit(stu_); n=0; flen_=fldlen(stu_,fromfld_);
			fasunlck(-2); // critical 
			FOREVER{
			next:;
        if(len1_==4) *l(stu_,1)=++n; else *u(stu_,1)=++n;
				if((n%1000)==0){scrifld(100,fm_ol8,&n);scrupd(-3,0);}
        g=fasgeti(stu_);
        if(g==47)break;
        if(g==0){
					if(only_emptyfld_=='J'){
						for(g=0;g<flen_;g++) if(*(s(stu_,tofld_)+g)!=0) break;
						if(g<flen_) goto next;
					}
					copy(s(stu_,fromfld_),s(stu_,tofld_),flen_); fasupd(stu_);
				}
      }
      break;
		}
  }
}

static AdjustExtendedLogging()
{
  uint16 z,key;
	char valstr_[25],cmdstr_[60];
	  
	zero(valstr_,sizeof valstr_);
	ExecJmsCommand(valstr_,20,"GetIniKeyValue|DataBaseSettings|ExtendedLogging");
	FOREVER{
  redo:;
		scraddf(-1,0,0,0);z=1;
		scraddf(z++,3,15,0xA);
		scraddf(z++,6,5,0);scraddf(z++,6,37,2);
		scraddf(z++,23,1,8);scraddf(z++,23,11,8);
		z=1;
		scrifld(z++,VarTextFmt(38,0)," Aanzetten/afzetten extended logging ");
		scrifld(z++,VarTextFmt(31,0),"Geef de waarde (0=uit,1=aan) : "); scrifld(z++,fm_us1,valstr_);
		scrifld(z++,VarTextFmt(9,0)," F1 stop ");scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
		key=scrupd(3,0x81);
		if(key==101 || key==106) break;
		if(valstr_[0]<'0' || valstr_[0]>'1') {errnum=38; goto redo;}
		zero(cmdstr_,sizeof cmdstr_);
		z=copy0("SetIniKeyValue|DataBaseSettings|ExtendedLogging|",cmdstr_,59);cmdstr_[z]=valstr_[0];
		ExecJmsCommand(valstr_,20,cmdstr_);break;
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
   
static parm_eur()
{
  int16 z,key,curs=3;
  long grb_d_ak,grb_d_vk,grb_d_fi;
					
  sysget(1201,4,&grb_d_ak);
  sysget(1205,4,&grb_d_vk);
  sysget(1209,4,&grb_d_fi);
  FOREVER{
    redo:;
    scrget(1,201);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_os3,def_munt);
    scrifld(z++,fm_ugrb,&grb_d_ak);
    scrifld(z++,fm_ugrb,&grb_d_vk);
    scrifld(z++,fm_ugrb,&grb_d_fi);
    key=scrupd(curs,0xA1); curs=3;
    if(key==101 || key==106) goto endsr;
    if(fldlen(4,0)){
      if(grb_d_ak==0 || grb_d_ak==-1){curs=5;errnum=38;goto redo;}
      if(grb_d_vk==0 || grb_d_vk==-1){curs=6;errnum=38;goto redo;}
    }
    if(key==108) break;
  }
  sysput(1201,4,&grb_d_ak);
  sysput(1205,4,&grb_d_vk);
  sysput(1209,4,&grb_d_fi);
  return YES;
endsr:;
  return NO;
}
 
static search(stu_, mod_)
{
	int16 parmbak[8], fuval;

	copy((char*)parmcall, (char*)parmbak, sizeof parmcall);
	zero((char*)parmcall, sizeof parmcall);
	parmcall[0] = mod_;
//#if 0
//	if(stu_<=2) parmcall[1]=7; // bits : 0 = display, 1=update, 2=add
//	else parmcall[1]=3; // GEEN ADD
//#endif
	parmcall[2] = 0;
	parmcall[3] = 0;
//#ifdef STRAATKEY
//	if(stu_==2) parmcall[4]=STRAATKEY;
//#endif
	parmcall[7] = 0x04;
	fuval = ovlcall(2900, stu_);
	copy((char*)parmbak, (char*)parmcall, sizeof parmcall);
	return fuval;
}

static verantwoordelijke_btw_aangifte()
{
	int16 z_, key_, curs_ = 2;
	uint16 verantwoordelijke_, retval_ = NO;

	sysget(1729, 2, &verantwoordelijke_); fasinit(1);
	fileopen(1);
	if (verantwoordelijke_) {
		fasinit(1);
		*u(1, 1) = verantwoordelijke_;
		fasgeti(1);
	}

	FOREVER {
		scrget(1, 283);
		z_ = 1;
		scrfld(1, 25, 1);
		scrfld(2, 1, 3);
		scraddpicto(1, 2, 0, 0, 2, 1, 112, 0, 4, "Uitgebreid zoeken");
		key_ = scrupd(curs_, 0xA1);
		curs_ = 2;

		if (key_ == 101 || key_ == 106)
			goto endsr;

		if (*s(1, 3) == '\0'){
			fasinit(1); verantwoordelijke_ = 0;
		}
		else {
			if (search(1, 0))	continue;
			verantwoordelijke_ = *u(1, 1);
		}

		if (key_ == 108) {
			sysput(1729, 2, &verantwoordelijke_);
			break;
		}
	}

	retval_ = YES;

endsr:
	return retval_;
}
 
static ask_kod(new_kod_)
char *new_kod_;
{
  int16 key;
  char buf_[5];
					
  zero(buf_,sizeof buf_); copy(s(25,3),buf_,3);
  FOREVER{
    redo:
    scrget(1,179);
    scrifld(1,fm_us3,buf_);
    key=scrupd(1,0x0081);
    if(key==101) return NO;
    if(buf_[0]=='\0') goto redo;
    if(key==108){copy(buf_,new_kod_,3); break;}
  }
  return YES;
}

static warn_ok(mode_)/* 0=boekhouding, 1=voorraad */
int16 mode_;
{
  int16 key;
  char shure_='N';
 
  FOREVER{
    if(mode_==0) scrget(1,203); else scrget(1,204);
    scrifld(1,fm_uJN,&shure_);
    key=scrupd(1,0x19);
    if(key==101 || key==105) return NO;
    if(key==104 && shure_=='J') return YES;
  }
}
 
static taal()
{
  int16 k,key,z;
 
  if(fldlen(1,16)!=1 && fldlen(2,24)!=1) return NO;/* geen taal*/

  sysget(2212,4,&b[212]);
  scrget(1,190);
  z=1;
  for(k=0;k<4;k++) scrifld(z++,fm_us1_U,&b[212+k]);
  key=scrupd(1,0x04A1);
  if(key!=106){
    updated=YES;
    sysput(2212,4,&b[212]);
  }
  if(key==111) ovl_exit(-1);
  if(key==101) return YES;
  return NO;
}
 
static c_10_jn(z,s)
int16 z, *s;
{
  if(*s==1) (*(char *)s='J'); else (*(char *)s='N');
  scrifld(z,fm_uJN,s);
}

static c_12_dw(z,s)
int16 z, *s;
{
  if(*s==2) (*(char *)s='W'); else (*(char *)s='D');
  scrifld(z,fm_u_WD,s);
}
 
static c_jn_10(s)
int16 *s;
{
  if(*(char *)s=='J') *s=1; else *s=0;
}

static c_dw_12(s)
int16 *s;
{
  if(*(char *)s=='W') *s=2; else *s=1;
}

static ok(pos)
int16 pos;
{
  int16 k;

  sysget(pos,2,&k);
  return k;
}

static get_JN(sys_,pos_)
int16 sys_,pos_;
{
  int16 k;
  char byte;

  sysget(sys_,1,&byte);
  for(k=pos_;k<pos_+8;k++){
    if(byte & 1) b[k]='J'; else b[k]='N';
    byte=byte>>1;
  }
}

static put_JN(sys_,pos_)
int16 sys_,pos_;
{
  int16 k;
  char byte;

  byte=0;
  for(k=pos_+7;k>=pos_;k--){
    byte=byte<<1;
    if(b[k]=='J') byte=byte | 1;
  }
  sysput(sys_,1,&byte);
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
  ovlexit(ovlnr);
}

static uint16 make_pw(ps)
char *ps;
{
  int16 k;
  uint16 pw;
 
  if(*ps=='\0') return 0;
  pw=0;
  for(k=0;k<8;k++){
    if(*ps=='\0' || *ps=='~' || *ps=='#') break;
    pw=pw*7+*ps++ +1;
  }
  if(pw==0) pw++;
  return pw;
}


static pwlevget(type,nr)
int16 type,nr;
{
  return ((int16)(niveaus[type][nr/4]>>(2*(nr%4))) &0x3);
}

static pwlevset(type,val,nr)
int16 type,nr,val;
{
  int16 j;
  uint16 mask;

  j=nr/4;
  mask=(3<<(2*(nr%4)))^0xFFFF;
  niveaus[type][j]=niveaus[type][j]&mask;
  niveaus[type][j]=niveaus[type][j]| (val<<(2*(nr%4)));
}

static int copy0(char *ps,char *pd,int max)
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
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

static byte2hex(byte,pd)
char byte,*pd;
{
  char b;
  int16 k;

  for(k=1;k>=0;k--){
    b=byte>>(k*4);b=(b&0xF)+'0';
    if(b>'9') b=b-'9'-1+'A';
    *pd++=b;
  }
}
 
static char hex2byte(ps)
char *ps;
{
  int16 k,j;
  char b;

  b=0;
  for(k=0;k<2;k++){
    if(*ps=='\0') break;
    if(*ps>='a' && *ps<='z') *ps=*ps-'a'+'A';
    j=*ps++ -'0';
    if(j>9) j=j+'0'-'A'+10;
    b=b*16+j;
  }
  return (char)b;
}
 
static zeros(pd,len)
char *pd;
uint16 len;
{
  while(len--) *pd++='\0';
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
  int16 k,curs,z,curs_taal,key;
 
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
		if(bfnr==2){
			if(fldlen(stu,200)){
				if(*u(stu,200)==1){
					scrchat(z-1,0xB); 
					scraddpicto(7,z-1,0,0,2,1,70,0,3,"Maak actief");
				}
				else{
					scrchat(z-1,0xFF);
					if(*u(stu,200)==0) scraddpicto(7,z-1,0,0,2,1,71,0,4,"Blokkeer");
					else scraddpicto(7,z-1,0,0,2,1,71,0,0,"Blokkeer");
				}
			}
		}
    for(k=3;k<16;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,16);
    for(k=17;k<MAXFLD;k++) scrfld(z++,stu,k);
    key=scrupd(curs,0x0080);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5007 && fldlen(stu,200)){ // blokkeer
			if(*u(stu,200)==0) *u(stu,200)=1; else *u(stu,200)=0;
			goto redo_l;
		}
    if(taal_chk(16)) {curs=curs_taal;goto redo_l;}
  }

  else if(stu==2){/* klanten */
    curs=2;
    redo_k:;
    scrget(2,7);  scrinq();
    z=1;
    scrifld(z++,fm_os20,selp_txt[men_keuze]);
    if(klcd) scrfld(z++,stu,2); else scrofld(z++,stu,1,-1);
		if(bfnr==2){
			if(fldlen(stu,200)){
				if(*u(stu,200)==1){
					scrchat(z-1,0xB); 
					scraddpicto(7,z-1,0,0,2,1,70,0,3,"Maak actief");
				}
				else{
					scrchat(z-1,0xFF);
					if(*u(stu,200)==0) scraddpicto(7,z-1,0,0,2,1,71,0,4,"Blokkeer");
					else scraddpicto(7,z-1,0,0,2,1,71,0,0,"Blokkeer");
				}
			}
		}
    for(k=3;k<24;k++) scrfld(z++,stu,k);
    curs_taal=z;
    taal_upd(z++,24);
    for(k=25;k<MAXFLD;k++) scrfld(z++,stu,k);
    key=scrupd(curs,0x0080);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5007 && fldlen(stu,200)){ // blokkeer
			if(*u(stu,200)==0) *u(stu,200)=1; else *u(stu,200)=0;
			goto redo_k;
		}
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

  for(k=2;k<201;k++){
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