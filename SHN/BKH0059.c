/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0059GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0059dat
#define ovlcod BKH0059cod
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

char ovldat[] = "bkh0059  00:21 20/05/10 (c) Jamadata";
/* BTW-listing - EU intr.opgave  Intervat versie 1.3 */
/* enkel code S (vak 44) en L (46 en rest) worden gebruikt */

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_EU          27/* excl. Belgie */
#define DIM_DBLBTW      800
#define DIM_KLTDBLBTW   100

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us2[]   = {7,0xC8,2,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1U[]  = {7,0xC8,1,0,1,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os3[]  = {7,0x88,3,0,0,0,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ui3[]   = {6,0xD1,3,0,0x60,0};
static char fm_ol9[]   = {6,0x93,9,0,0x70,0};
static char fm_ul5[]   = {6,0xD3,5,0,0x70,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};
static char fm_ud82_[] = {6,0xD5,8,2,0x60,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_udat_s[]= {4,0xC0,0xE,'/'};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};

extern char *s();
extern int16 *i();
extern uint16 *u();
extern uint16 datejd();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();

static char *eu_land[DIM_EU]={"BG","CY","DK","DE","EE","FI","FR","EL","XI","HU","HR","IE","IT","LV","LT","LU",
		       "MT","NL","AT","PL","PT","RO","SI","SK","ES","CZ","SE"};

static struct {
  char naam[31];
  char hoedanig[31];
  char telefoon[21];
	uint16 verantwoordelijke;
} intervat;

static char prt_nbtw='N',firma[350],typ[3]={'L','S','T'};
static char nm_teken[70];
static int16 free,stu_lk=2,stu_01lk=1,linenr,jrnal_btw[100],kwartaal;
static int16 qklt,btw_periode;

static int16 form_dat[8],pr_mode,prtnr;
static uint16 journl,j_typ;
static uint16 dt_bew,searcnr,volgnr,last_arc,clean_prev[3];
static int16 prt2pdf;
static long kltcent,levcent;
								
static char buf750[750],buf1000[1000];
static flag allow_yr=NO;
static struct {
  uint16 rec;
  double omzet;
  double btw;
} tb_kltdbl[DIM_KLTDBLBTW];

static int16 taal;
static uint16 jaarbtw,dt_prt,dt_beg,dt_end,r_dblbtw[DIM_DBLBTW];
static double omzet,belast,bdkw[3];
static long min_btw,btws[5],noomzet[10],firmbtwn;
static flag sear_stt,code[2],lvcd,klcd,chk_btoeg=NO,addfromstk,add_sal;
static flag sys1794,sys3876,sys2682,analyt,sys1790;
static char filnam[50],fm_bdr[40],fm_vbdr[40];

static char seqo_str[1000];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;

static flag Prt2Xls=NO;
extern int16 ilength; // XLS
static int XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol;
static int16 *pi; // XLS
static int16 StylTotaal, StylGrpTot, StylKlasse, StylNormal, StylDate, StylTitel, Styl2Use;


				
static char *p_data;
static char def_munt[4];
static char *ps_4_2;
static uint16 *pu_4_3,*pu_4_4,*pu_4_5;
static double *pd_4_32,*pd_5_35,*pd_5_36;
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;

#include "Std\XlsFunc.c"

static int16 get_klttotaal();
 
ovlcod()
{
  int16 curs=1,key,z;
  char choice;

  initload();
  dt_prt=*u(25,2);
  FOREVER{
		redo:;
    scrget(1,40);z=1;fasunlck(0);
    z=1;
    scrfld(z++,25,1);
		scraddpicto(50,0,78,3,2,1,105,1,7,"^!B0059A");
		scraddpicto(51,0,78,9,2,1,105,1,7,"^!B0059B");
		scraddpicto(1,0,67,19,4,2,60,0,4,"^*financien.belgium.be/nl/E-services/Intervat"); // int nr, int fld, int h, int v, int hlen, int vlen, int PicNr, int ButNr, int ButCol, char *pAltText)
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001) goto redo; // link intervat
		if(key==5050) goto redo; // link help BTW-listing
		if(key==5051) goto redo; // link help INT-listing
    if(key==111) ovl_exit(10);
    if(key==101) break;
		fasunlck(-1);
    switch(choice){
      case '1': ontbreken();break;
      case '2': printb_lst();break;
      case '3': dump_blst(); break;
      case '4': if(fldlen(2,22) && fldlen(5,44)) printk_lst(); else errnum=12; break;
      case '5': if(fldlen(2,22) && fldlen(5,44)) dump_klst();else errnum=12; break;
      case 'F': if(!ovltest( 79)) errnum=12; else ovlexit(79); break;
      case 'U': upd();break;
      default: errnum=34; break;
    }
  }
  endsr:;
  ovl_exit(-1);
}


static ontbreken()
{
  int16 curs=1,k,key,z,cnt;
  long btwnr_;
  double bd_;

  FOREVER{
    redo:;
    scrget(1,41);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_uu4,&jaarbtw);
    scrifld(z++,fm_ul5,&min_btw);
    key=scrupd(curs,0x0781);curs=1;
    if(key==101) goto endsr;
    if(key==111) ovl_exit(10);
    if(chk_year(jaarbtw)) {curs=2;goto redo;}
    prt2pdf=NO;if(key==109){prt2pdf=YES;key=108;}
    if(key==108) break;
  }
 
  getsysprNew(3,form_dat,&pr_mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  free=999;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,30); prttext("<t32b>"); prttext("Ontbrekende BTW-nummers/NIET BTW-plichtigen met omzet");
  prttext("<b>, jaar ");prtifld(fm_uu4,&jaarbtw,-1);
  prttext("<t100>"); prtfld(25,2,-1); prttext("<t125>Blz.<ppp>.");
  prtbuf(1);
  z=1;
  prttab(z,stu_lk,code[stu_01lk]+1,2,-1); prttitle(z++,"Code",3);
  prttab(z,stu_lk,3,1,30); prttitle(z++,"Naam",3);
  prttab(z,stu_lk,4,1,25); prttitle(z++,"Straat & Nummer",3);
  prttab(z,stu_lk,6,1,20); prttitle(z++,"Gemeente",3);
  prttab(z,stu_lk,10,0,-1); prttitle(z++,"BTW-nummer",3);
  prttab(z,5,35,2,-1); prttitle(z++,"Omzet",0x13);
  prttab(z,stu_lk,8,0,-1); prttitle(z++,"Telefoon",3);
  prtbuf(3);
  p_pdfname("Ontbrekende BTW-nummers",dt_end,0);


  cnt=0;
  fasinit(stu_lk);
  while(free>=0){
    if(faskeyi(stu_lk,2,2)) break;
    btwnr_=(*l(stu_lk,10))&0xBFFFFFFF;                   /* zonder egal.bit */
    if(btwnr_==999999999 || btwnr_==0 || *(s(stu_lk,10)+3) & 0x40){
      get_btwbd();
      bd_=*pd_5_35;
      if((addfromstk || *u(5,1)) && !is_nul(bd_)){
	if(bd_>=min_btw || bd_<=-min_btw){
	  for(k=1;k<=15;k++) prtinfo(k,0);
	  nextline();cnt++;
	}
      }
    }
  }
  if(cnt){
    nextline();prttext("*** Aantal fiches :");
    *u(stu_lk,1)=cnt;prtfld(stu_lk,1,-1);nextline();
  }
  prtclose();
  endsr:;
}

static dump_klst()
{
  int16 curs=1,j,key,z;
	int16 mm,dd,pos_;
  // char str_[15];
									
  scrget(1,7);scrupd(-3,0);
  //sysget(120,14,str_); zero(firmabtw,sizeof firmabtw); j=0;
  //stcli_d(firmabtw,firmbtwn,9,0);
 
  if(jaarbtw==0) jddate(*u(25,2),&jaarbtw,&mm,&dd);
	zero(filnam,sizeof filnam); pos_=0;
	pos_+=copy0("Intr_Opgave_",&filnam[pos_],20);
	pos_+=copy0(s(25,3),&filnam[pos_],3);
	pos_+=copy0("_",&filnam[pos_],20);
	stcli_d(&filnam[pos_],(long)jaarbtw,4,1);pos_+=4;
	if(btw_periode){
	  pos_+=copy0("-KW",&filnam[pos_],20);
		stcli_d(&filnam[pos_],(long)kwartaal,1,0);pos_+=1;
	}
	else{
		pos_+=copy0("-",&filnam[pos_],20);
		stcli_d(&filnam[pos_],(long)kwartaal,2,0);pos_+=2;
	}
  pos_+=copy0(".xml",&filnam[pos_],20);

  FOREVER{
    redo:;
    scrget(1,215);z=1;
    scrfld(z++,25,1);
    if(btw_periode) scrifld(z++,fm_os10,"Kwartaal ..");
    else scrifld(z++,fm_os10,"Maand .....");
    scrifld(z++,fm_uu2,&kwartaal);
    scrifld(z++,fm_uu4,&jaarbtw);
    scrifld(z++,fm_udat,&dt_prt);
		scrifld(z++,VarTextFmt(34,1),&firma[222]);
    scrifld(z++,fm_os30,filnam);
    scrifld(z++,fm_os30,filnam);
    key=scrupd(curs,0x0481);
    if(key==101) goto endsr;
    if(key==111) ovl_exit(10);

    if(jaarbtw==0){curs=4;errnum=39;goto redo;}
    if(btw_periode){                                    /* kwartaal of jaar */
      if(kwartaal<1 || kwartaal>4){curs=3;errnum=34;goto redo;}
      dt_beg=datejd(jaarbtw,(kwartaal-1)*3+1,1);
      if(dt_beg<=last_arc){curs=3;errnum=34;goto redo;}
    }
    else {
      if(kwartaal<1 || kwartaal>12){curs=3;errnum=34;goto redo;}
      dt_beg=datejd(jaarbtw,kwartaal,1);
      if(dt_beg<=last_arc){curs=3;errnum=34;goto redo;}
    }
		if(firma[222]=='\0'){curs=6;errnum=38;goto redo;}
    if(key==108) break;
  }

  zero(filnam,sizeof filnam); pos_=0;
 
	pos_+=copy0("Intr_Opgave_",&filnam[pos_],20);
	pos_+=copy0(s(25,3),&filnam[pos_],3);
	pos_+=copy0("_",&filnam[pos_],20);
	stcli_d(&filnam[pos_],(long)jaarbtw,4,1);pos_+=4;
	if(btw_periode){
	  pos_+=copy0("-KW",&filnam[pos_],20);
		stcli_d(&filnam[pos_],(long)kwartaal,1,0);pos_+=1;
	}
	else{
		pos_+=copy0("-",&filnam[pos_],20);
		stcli_d(&filnam[pos_],(long)kwartaal,2,0);pos_+=2;
	}
  pos_+=copy0(".xml",&filnam[pos_],20);
	fasclos(-2); scrget(1,170);

  if(fasopen(filnam,12)) {errnum=1;goto endsr;}
  fasinit(80); seqo_pos=0;
  scrget(1,7);scrupd(-3,0);
  if(btw_periode){
    dt_beg=datejd(jaarbtw,(kwartaal-1)*3+1,1);
    z=jaarbtw;key=kwartaal;if(key==4){key=1;z++;} else key++;
    dt_end=datejd(z,(key-1)*3+1,1)-1;
  }
  else{
    dt_beg=datejd(jaarbtw,kwartaal,1);
    z=jaarbtw;key=kwartaal;if(key==12){key=1;z++;} else key++;
    dt_end=datejd(z,key,1)-1;
  }
  iopg2xml();
  endsr:;
}

static iopg2xml()/* uitschrijven intracommunautaire opgeve naar xml voor INTERVAT */
{
  int16 j,k,jjjj,mm,dd;
  long btwnr_;
  double bedrag_;
  char str_[80],lnd_[5],kar_,code_,btwstr_[15],str_period_[7];;
									
  jddate(dt_prt,&jjjj,&mm,&dd);
  zero(str_period_,sizeof str_period_);
  k=kwartaal; if(btw_periode) k+=30;
  stcli_d(str_period_,(long)k,2,0);
  stcli_d(&str_period_[2],(long)jaarbtw,4,0);

  scrget(1,7);scrupd(-3,0);
  fasinit(80);seqo_pos=0;zero(seqo_str,sizeof seqo_str);seqo_mode=2;pos=0;
  pos+=copy0("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>",&seqo_str[pos],150);add_crlf();dmp2file();
  pos+=copy0("<ns2:IntraConsignment xmlns=\"http://www.minfin.fgov.be/InputCommon\" xmlns:ns2=\"http://www.minfin.fgov.be/IntraConsignment\" IntraListingsNbr=\"1\">",&seqo_str[pos],250);add_crlf();dmp2file();

/* eerst de klanten doen voor de totale omzet te kennen */
  kwartcount();

  pos+=copy0("<ns2:IntraListing AmountSum=\"",&seqo_str[pos],50);
  pos+=bd2xstr(&seqo_str[pos],omzet,12); 
  pos+=copy0("\" DeclarantReference=\"",&seqo_str[pos],50);
  zero(str_,sizeof str_);
  btwnr_=firmbtwn; btw_deco(&str_[0],(long *)&btwnr_,0); // str_[0]='0';stcli_d(&str_[1],btwnr_,9,0);
  stcli_d(&str_[10],(long)(jaarbtw%100),2,0);
  k=kwartaal; if(btw_periode) k+=30;stcli_d(&str_[12],(long)(k),2,0);
  pos+=copy0(str_,&seqo_str[pos],14);
  pos+=copy0("\" ClientsNbr=\"",&seqo_str[pos],50);
  zero(str_,sizeof str_);
  stcli_d(str_,(long)qklt,6,1);for(k=0;k<6;k++) if(str_[k]!=' ') break;
  pos+=copy0(&str_[k],&seqo_str[pos],6-k);
  pos+=copy0("\" SequenceNumber=\"1\">",&seqo_str[pos],50);
  add_crlf();dmp2file();

  pos+=copy0("<ns2:Declarant>",&seqo_str[pos],20);add_crlf();
    btwnr_=firmbtwn; btw_deco(&str_[0],(long *)&btwnr_,0); // copy("0",&str_[0],1);stcli_d(&str_[1],btwnr_,9,0);
    dmpxmlstr("VATNumber",str_,12);
    dmpxmlstr("Name",&firma[0],30);
    dmpxmlstr("Street",&firma[31],25);
    dmpxmlstr("PostCode",&firma[57],4);
    dmpxmlstr("City",&firma[65],20);
    dmpxmlstr("CountryCode","BE",2);
    dmpxmlstr("EmailAddress",&firma[222],34);
  pos+=copy0("</ns2:Declarant>",&seqo_str[pos],20); add_crlf();

	// ENKEL VOOR BTW-AANGIFTE, NIET HIER !!!!


	//if (intervat.verantwoordelijke) {
	//	fasinit(1);
	//	*u(1, 1) = intervat.verantwoordelijke;
	//	fasgeti(1);

	//	pos += copy0("<ns2:Representative>", &seqo_str[pos], 20); add_crlf();
	//	zero(str_, sizeof str_);
	//	btwnr_ = *l(1, 10); btw_deco(&str_[0], &btwnr_, 0);
	//	pos += copy0("<RepresentativeID identificationType=\"NVAT\" issuedBy=\"BE\">", &seqo_str[pos], 60);
	//	pos += copy0(str_, &seqo_str[pos], strlen(str_));
	//	pos += copy0("</RepresentativeID>", &seqo_str[pos], 20); add_crlf();
	//	dmpxmlstr("Name", s(1, 3), 40);
	//	dmpxmlstr("Street", s(1, 4), 30);
	//	dmpxmlstr("PostCode", s(1, 5), 7);
	//	dmpxmlstr("City", s(1, 6), 25);
	//	dmpxmlstr("CountryCode", "BE", 2);
	//	dmpxmlstr("EmailAddress", s(1, 21), 40);
	//	dmpxmlstr("Phone", s(1, 8), 15);
	//	pos += copy0("</ns2:Representative>", &seqo_str[pos], 25); add_crlf();
	//}

  pos+=copy0("<ns2:Period>",&seqo_str[pos],20); 
    if(btw_periode){
      stcli_d(str_,(long)kwartaal,1,1);
      dmpxmlstr("ns2:Quarter",str_,1);
    }
    else {
      stcli_d(str_,(long)kwartaal,2,1);
      dmpxmlstr("ns2:Month",str_,2);
    }
    stcli_d(str_,(long)jaarbtw,4,1);
    dmpxmlstr("ns2:Year",str_,4);
  pos+=copy0("</ns2:Period>",&seqo_str[pos],20); add_crlf();
  dmp2file();

  fasinit(2);fasinit(5);
  scrget(1,170);scrifld(10,fm_os63,"Uitschrijven van ");
  omzet=0;linenr=0;
  zero((char *)&r_dblbtw[0],sizeof r_dblbtw);
  FOREVER{
    if(getkwnext()==NO) break;
    scrfld(12,2,3);scrupd(-3,0);
    zero(lnd_,sizeof lnd_); k=0;
    copy(s(2,22),lnd_,2);
    for(j=0;j<2;j++){
      if(lnd_[j]<'a' && lnd_[j]>'z' && lnd_[j]<'A' && lnd_[j]>'Z') break;
    }
    if(j<2) zero(lnd_,sizeof lnd_);/* ongeldig land */
/* indien in BTW-nr ook landcode, dan deze weglaten */
    j=0; if(cmpstrU(lnd_,s(2,22),2)==0) j=2;
    zero(btwstr_,sizeof btwstr_); k=0;
    for(j;j<fldlen(2,22);j++){
      kar_=*(s(2,22)+j);
      if((kar_>='0' && kar_<='9') || (kar_>='a' && kar_<='z') || (kar_>='A' && kar_<='Z')){
	btwstr_[k++]=kar_; if(k>=12) break;
      }
    }
    for(k=0;k<3;k++){
      if(bdkw[k]){
				code_=typ[k]; bedrag_=bdkw[k];
				omzet+=bdkw[k];
				linenr++;
				pos+=copy0("<ns2:IntraClient SequenceNumber=\"",&seqo_str[pos],45);
				stcli_d(str_,(long)linenr,4,1);dmpnetstr(str_,4);
				pos+=copy0("\">",&seqo_str[pos],2); add_crlf();
					pos+=copy0("<ns2:CompanyVATNumber issuedBy=\"",&seqo_str[pos],80); 
					pos+=copy0(lnd_,&seqo_str[pos],2);
					pos+=copy0("\">",&seqo_str[pos],20); 
					pos+=copy0(btwstr_,&seqo_str[pos],12);
					pos+=copy0("</ns2:CompanyVATNumber>",&seqo_str[pos],80);add_crlf();  
					dmpxmlstr("ns2:Code",&code_,1);
					bd2xml("ns2:Amount",bedrag_);
				pos+=copy0("</ns2:IntraClient>",&seqo_str[pos],20); add_crlf();
				dmp2file();
      }
    }
  }
  pos+=copy0("<ns2:Comment></ns2:Comment>",&seqo_str[pos],60); add_crlf();
  pos+=copy0("</ns2:IntraListing>",&seqo_str[pos],60); add_crlf();
  pos+=copy0("</ns2:IntraConsignment>",&seqo_str[pos],60); add_crlf();
  dmp2file();
  fasclos(-2);
  endsr:;
}

static strlen(ps_)
char *ps_;
{
  int16 k;
						
  for(k=0;k<132;k++) if(*(ps_+k)=='\0') break;
  return k;
}
 
static dump_blst()
{
  int16 curs=1,j,key,z,pos_;
  char str_[15];
						
  scrget(1,7);scrupd(-3,0);
  zero((char *)&r_dblbtw[0],sizeof r_dblbtw);
  //sysget(120,14,str_); zero(firmabtw,sizeof firmabtw); j=0;
  //stcli_d(firmabtw,firmbtwn,9,0);


  zero(filnam,sizeof filnam); pos_=0;

  FOREVER{
    redo:;
    scrget(1,58);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_uu4,&jaarbtw);
    scrifld(z++,fm_udat,&dt_prt);
    scrifld(z++,fm_ul5,&min_btw);
    scrifld(z++,fm_u_JN,&prt_nbtw);
		scrifld(z++,VarTextFmt(34,1),&firma[222]);
    scrifld(z++,fm_os30,filnam);
    key=scrupd(curs,0x0481); curs=2;
    if(key==101) goto endsr;
    if(key==111) ovl_exit(10);
    if(chk_year(jaarbtw)) {curs=2;goto redo;}
		if(firma[222]=='\0'){curs=6;errnum=38;goto redo;}
    zero(filnam,sizeof filnam); pos_=0;
		pos_+=copy0("BTW-Listing_",&filnam[pos_],20);
		pos_+=copy0(s(25,3),&filnam[pos_],3);
		pos_+=copy0("_",&filnam[pos_],20);
		stcli_d(&filnam[pos_],(long)jaarbtw,4,1);pos_+=4;
		pos_+=copy0(".xml",&filnam[pos_],20);
    if(key==108) break;
  }

  if(key==108){/* intervat */
		zero(filnam,sizeof filnam); pos_=0;
  	pos_+=copy0("BTW-Listing_",&filnam[pos_],20);
  	pos_+=copy0(s(25,3),&filnam[pos_],3);
	  pos_+=copy0("_",&filnam[pos_],20);
	  stcli_d(&filnam[pos_],(long)jaarbtw,4,1);pos_+=4;
    pos_+=copy0(".xml",&filnam[pos_],20);
  }
  fasclos(-2); scrget(1,170);

  if(fasopen(filnam,12)) {errnum=1;goto endsr;}
  fasinit(80); seqo_pos=0;
  scrget(1,7);scrupd(-3,0);
  if(key==108) {vat2xml(); }
  endsr:;
}

static vat2xml()/* uitschrijven BTW-listing in xml voor intervat */
{
  int16 k,jjjj,mm,dd;
  int16 q_klt_;
  long btwnr_;
  char str_[80];
									
  jddate(dt_prt,&jjjj,&mm,&dd);

  scrget(1,7);scrupd(-3,0);
  fasinit(80);seqo_pos=0;zero(seqo_str,sizeof seqo_str);seqo_mode=2;pos=0;
  pos+=copy0("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>",&seqo_str[pos],150);add_crlf();dmp2file();
  pos+=copy0("<ns2:ClientListingConsignment xmlns=\"http://www.minfin.fgov.be/InputCommon\" xmlns:ns2=\"http://www.minfin.fgov.be/ClientListingConsignment\" ClientListingsNbr=\"1\">",&seqo_str[pos],250);add_crlf();dmp2file();

 // eerst de klanten doen voor de totale omzet te kennen 
  zero((char *)&r_dblbtw[0],sizeof r_dblbtw);
  omzet=0;belast=0;linenr=0;
  fasinit(stu_lk);fasinit(5);
  scrget(1,170);scrifld(10,fm_os63,"Berekenen van ");
  FOREVER{
    if(faskeyi(stu_lk,2,2)) break;
    q_klt_=get_klttotaal();
    if(q_klt_ && (*pd_5_35>=min_btw || *pd_5_35<=-min_btw)){
      linenr++;scrupd(-3,0);
      omzet+=*pd_5_35;belast+=*pd_5_36;
      fasgeti(stu_lk);/* herstel de_heer */
    }
  }

  pos+=copy0("<ns2:ClientListing VATAmountSum=\"",&seqo_str[pos],50);
  pos+=bd2xstr(&seqo_str[pos],belast,12); 
  pos+=copy0("\" TurnOverSum=\"",&seqo_str[pos],50);
  pos+=bd2xstr(&seqo_str[pos],omzet,12); 
  pos+=copy0("\" DeclarantReference=\"",&seqo_str[pos],50);
  zero(str_,sizeof str_);
  btwnr_=firmbtwn; btw_deco(&str_[0],(long *)&btwnr_,0); //str_[0]='0';stcli_d(&str_[1],btwnr_,9,0);
  stcli_d(&str_[10],(long)(jaarbtw),4,0);
  pos+=copy0(str_,&seqo_str[pos],14);
  pos+=copy0("\" ClientsNbr=\"",&seqo_str[pos],50);
  zero(str_,sizeof str_);
  stcli_d(str_,(long)linenr,6,1);for(k=0;k<6;k++) if(str_[k]!=' ') break;
  pos+=copy0(&str_[k],&seqo_str[pos],6-k);
  pos+=copy0("\" SequenceNumber=\"1\">",&seqo_str[pos],50);
  add_crlf();dmp2file();

  pos+=copy0("<ns2:Declarant>",&seqo_str[pos],20);add_crlf();
    btwnr_=firmbtwn; btw_deco(&str_[0],(long *)&btwnr_,0); // copy("0",&str_[0],1);stcli_d(&str_[1],btwnr_,9,0);
    dmpxmlstr("VATNumber",str_,12);
    dmpxmlstr("Name",&firma[0],30);
    dmpxmlstr("Street",&firma[31],25);
    dmpxmlstr("PostCode",&firma[57],4);
    dmpxmlstr("City",&firma[65],20);
    dmpxmlstr("CountryCode","BE",2);
    dmpxmlstr("EmailAddress",&firma[222],34);
  pos+=copy0("</ns2:Declarant>",&seqo_str[pos],20); add_crlf();
/* ENKEL VOOR BTW-AANGIFTE, NIET HIER !!!!!
	if (intervat.verantwoordelijke) {
		fasinit(1);
		*u(1, 1) = intervat.verantwoordelijke;
		fasgeti(1);

		pos += copy0("<ns2:Representative>", &seqo_str[pos], 20); add_crlf();
		zero(str_, sizeof str_);
		btwnr_ = *l(1, 10); btw_deco(&str_[0], &btwnr_, 0);
		pos += copy0("<RepresentativeID identificationType=\"NVAT\" issuedBy=\"BE\">", &seqo_str[pos], 60);
		pos += copy0(str_, &seqo_str[pos], strlen(str_));
		pos += copy0("</RepresentativeID>", &seqo_str[pos], 20); add_crlf();
		dmpxmlstr("Name", s(1, 3), 40);
		dmpxmlstr("Street", s(1, 4), 30);
		dmpxmlstr("PostCode", s(1, 5), 7);
		dmpxmlstr("City", s(1, 6), 25);
		dmpxmlstr("CountryCode", "BE", 2);
		dmpxmlstr("EmailAddress", s(1, 21), 40);
		dmpxmlstr("Phone", s(1, 8), 15);
		pos += copy0("</ns2:Representative>", &seqo_str[pos], 25); add_crlf();
	}*/




  zero(str_,sizeof str_);stcli_d(str_,(long)jaarbtw,4,0);dmpxmlstr("ns2:Period",str_,4);

  zero((char *)&r_dblbtw[0],sizeof r_dblbtw);
  omzet=0;belast=0;linenr=0;
  fasinit(stu_lk);fasinit(5);
  scrget(1,170);scrifld(10,fm_os63,"Uitschrijven van ");
  FOREVER{
    if(faskeyi(stu_lk,2,2)) break;
    q_klt_=get_klttotaal();
    if(q_klt_ && (*pd_5_35>=min_btw || *pd_5_35<=-min_btw)){
      linenr++;scrupd(-3,0);
      pos+=copy0("<ns2:Client SequenceNumber=\"",&seqo_str[pos],45);
      stcli_d(str_,(long)linenr,4,1);dmpnetstr(str_,4);
      pos+=copy0("\">",&seqo_str[pos],2); add_crlf();
	pos+=copy0("<ns2:CompanyVATNumber issuedBy=\"BE\">",&seqo_str[pos],80); 
	zero(str_,sizeof str_);
	btwnr_=*l(stu_lk,10)&0xBFFFFFFF; btw_deco(str_,(long *)&btwnr_,0); //str_[0]='0';stcli_d(&str_[1],btwnr_,9,0);
        pos+=copy0(str_,&seqo_str[pos],10); 
        pos+=copy0("</ns2:CompanyVATNumber>",&seqo_str[pos],80);add_crlf(); 
					bd2xml("ns2:TurnOver",*pd_5_35);      
	bd2xml("ns2:VATAmount",*pd_5_36);

      pos+=copy0("</ns2:Client>",&seqo_str[pos],20); add_crlf();
      omzet+=*pd_5_35;belast+=*pd_5_36;
      fasgeti(stu_lk);/* herstel de_heer */
      dmp2file();
    }
  }
  pos+=copy0("<ns2:Comment></ns2:Comment>",&seqo_str[pos],60); add_crlf();
  pos+=copy0("</ns2:ClientListing>",&seqo_str[pos],60); add_crlf();
  pos+=copy0("</ns2:ClientListingConsignment>",&seqo_str[pos],60); add_crlf();
  dmp2file();
  fasclos(-2);
  endsr:;
}
 
static bd2xml(xname_,bd_)
char *xname_;
double bd_;
{
  char str_[15];
 
  zero(str_,sizeof str_);
  bd2xstr(str_,bd_,12);
  dmpxmlstr(xname_,str_,12);
  endsr:;
}


static bd2xstr(ps_,bd_,totlen_)
char *ps_;
double bd_;
int16 totlen_;
{
  int16 k,negat_,len_;
  double bd1_,bd2_;
  long lbd1_,lbd2_;
  char str_[15];
 
 
  bd_=valu_cnv("EUR","EUR",bd_,(double)(0.01));
	negat_=NO; if(bd_<0){negat_=YES;bd_=-bd_;}

  zero(str_,sizeof str_);
  bd1_=(long)(bd_);
  bd2_=(long)((bd_-bd1_)*(double)(100.) +(double).49);
  lbd1_=(long)(bd1_+.49); lbd2_=(long)(bd2_+.49);
  stcli_d(str_,lbd1_,8,1);str_[8]='.'; stcli_d(&str_[9],lbd2_,2,0);
  if(negat_){                                             /* negatief getal */
    for(k=0;k<10;k++) if(str_[k]!=' ') break;
    if(k>0) str_[k-1]='-';
  }
  for(k=0;k<10;k++) if(str_[k]!=' ') break;
  len_=copy0(&str_[k],ps_,12-k); 
  
  return len_;
}


static dmpxmlstr(xname_,ps_,maxlen_)
char *xname_,*ps_;
int16 maxlen_;
{
  int16 k,len_,slen_,nm_beg_,ps_beg_;

  nm_beg_=-1;
  for(len_=0;len_<20;len_++){
    if(nm_beg_<0 && xname_[len_]!=' ') nm_beg_=len_;
    if(xname_[len_]=='\0') break;
  }
  if(nm_beg_>0) len_-=nm_beg_; else nm_beg_=0;/* leading blanks */

  ps_beg_=-1;
  for(slen_=0;slen_<maxlen_;slen_++){
    if(ps_beg_<0 && ps_[slen_]!=' ') ps_beg_=slen_;
    if(ps_[slen_]=='\0') break;
  }
  if(ps_beg_>0) slen_-=ps_beg_; else ps_beg_=0;/* leading blanks */

  if(slen_==0){/* lege string */
    seqo_str[pos++]='<';pos+=copy0(&xname_[nm_beg_],&seqo_str[pos],len_);
    pos+=copy0("/>",&seqo_str[pos],2);
  }
  else{
    seqo_str[pos++]='<';pos+=copy0(&xname_[nm_beg_],&seqo_str[pos],len_);seqo_str[pos++]='>';
    copy(&ps_[ps_beg_],&seqo_str[pos],slen_);
    for(k=0;k<slen_;k++){
      if(seqo_str[pos+k]=='<') seqo_str[pos+k]=' ';
      if(seqo_str[pos+k]=='>') seqo_str[pos+k]=' ';
      if(seqo_str[pos+k]=='&') seqo_str[pos+k]=' ';
    }
    pos+=slen_;
    pos+=copy0("</",&seqo_str[pos],2);pos+=copy0(&xname_[nm_beg_],&seqo_str[pos],len_);seqo_str[pos++]='>';
  }
  add_crlf();
}
 
static dmpnetstr(ps_,maxlen_)
char *ps_;
int16 maxlen_;
{
  int16 k,slen_,ps_beg_;

  ps_beg_=-1;
  for(slen_=0;slen_<maxlen_;slen_++){
    if(ps_beg_<0 && ps_[slen_]!=' ') ps_beg_=slen_;
    if(ps_[slen_]=='\0') break;
  }
  if(ps_beg_>0) slen_-=ps_beg_; else ps_beg_=0;/* leading blanks */
  if(slen_){
    copy(&ps_[ps_beg_],&seqo_str[pos],slen_);
    for(k=0;k<slen_;k++){
      if(seqo_str[pos+k]=='<') seqo_str[pos+k]=' ';
      if(seqo_str[pos+k]=='>') seqo_str[pos+k]=' ';
      if(seqo_str[pos+k]=='&') seqo_str[pos+k]=' ';
    }
    pos+=slen_;
  }
}

static dmp2file()
{
  int16 k;
 
  CnvJamaChar(seqo_str,pos,0);
  seqo_len=0;
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
/*  seqo_flush(); */
    if(seqo_len){
      fasseqo(80,seqo_mode,seqo_len+4);
      seqo_pos+=seqo_len;
      *l(80,1)=seqo_pos;
      seqo_len=0;
    }
  }
  pos=0;
}

static add_crlf()
{
  seqo_str[pos++]=0x0D;
  seqo_str[pos++]=0x0A;
}
 
static chk_year(btw_jr)
uint16 btw_jr;
{
  int16 jj,mm,dd;
 
  if(btw_jr<=2000) {errnum=34; return YES;}

  addfromstk=NO;add_sal=NO;
  if(last_arc){
    jddate(last_arc,&jj,&mm,&dd);
    if(btw_jr<jj){errnum=37;return YES;}
  }
  dt_beg=datejd(btw_jr,1,1);
  if(dt_beg<last_arc){add_sal=YES;dt_beg=last_arc+1;}
  dt_end=datejd(btw_jr,12,31);
  if(dt_end>last_arc){addfromstk=YES;}
  return NO;
}

static seq_clos()
{
  seqo_flush();
  fasclos(-2);
  fasflush(0);
  endsr:;
}

static seqo_long(get,len_)
long get;
int16 len_;
{
  char buf_[20];

  stcli_d(&buf_[0],get,len_,0);
  seqo_txt(&buf_[0],len_,' ');
}

static seqo_txt(ps,len_,fill_kar)
int16 len_;
char *ps,fill_kar;
{
  int16 k,add_blnc=NO;

  for(k=0;k<len_;k++){
    if(add_blnc || *ps=='\0') {add_blnc=YES;seqo_1(fill_kar);}
    else seqo_1(*ps);
    ps++;
  }
}

static add_eor()
{
  seqo_1(0x0D);seqo_1(0x0A);
  seqo_flush();
}

static seqo_1(byte_)
char byte_;
{
  *(s(80,1)+4+seqo_len++)=byte_;
  if(seqo_len>200){
    *l(80,1)=seqo_pos;
    fasseqo(80,2,seqo_len+4);
    seqo_pos+=seqo_len;seqo_len=0;
  }
}

static seqo_flush()
{
  if(seqo_len){
    *l(80,1)=seqo_pos;
    fasseqo(80,2,seqo_len+4);
    seqo_pos+=seqo_len;seqo_len=0;
  }
}
 
static get_klt(mode)
int16 mode;
{
  long btwnr_;
  double bd_;

  FOREVER{
    if(faskeyi(stu_lk,2,2)) return NO;
    btwnr_=(*l(stu_lk,10))&0xBFFFFFFF;/* zonder egal.bit */
    if(btwnr_==999999999 || btwnr_==0 || *(s(stu_lk,10)+3) & 0x40){
      get_btwbd();
      bd_=*pd_5_35;
      if((addfromstk || *u(5,1)) && !is_nul(bd_)){
	if(bd_>=min_btw || bd_<=-min_btw) return YES;
      }
      if(mode) return YES;
    }
  }
}

static get_btwbd()
{
  int16 journl,k,ks,key_mode,mode_;
  uint16 mst_rec_,volgnr,dat_bk;
  long rec4_;
  double ebtw,eomz;
  flag klt_mode;

  mst_rec_=*u(stu_lk,1)+stu_01lk*30000;
  fasinit(5);
  if(add_sal){
    *u(5,2)=mst_rec_;
    faskeyi(5,1,0);
  }
  if(addfromstk==NO) goto endsr;/* volledig jaar is gearchiveerd */
  fasinit(4);*u(4,5)=mst_rec_; *pu_4_4=dt_beg;mode_=1;
  FOREVER{
    next:;
    if(faskeyi(4,4,mode_)) break; mode_=2;
    if(*pu_4_5!=mst_rec_) break;
    if(*pu_4_4<dt_beg || *pu_4_4>dt_end) goto next;
    if(jrnal_btw[*ps_4_2]==0) goto next;/* alleen aank/verkoopjrnl */
    rec4_=*l(4,1);
    klt_mode=NO; if(*pu_4_5>=30000) klt_mode=YES;
    eomz=0;ebtw=0;
    journl=*ps_4_2;volgnr=*pu_4_3;dat_bk=*pu_4_4;
    fasinit(4);
    *ps_4_2=journl;*pu_4_3=volgnr;
    key_mode=1;
    FOREVER{/* sommeer omzet van 1 stuk */
      ks=faskeyi(4,1,key_mode);key_mode=2;
      if(ks) break;
      if(journl!=*ps_4_2 || volgnr!=*pu_4_3) break;
      if(*pu_4_5>=60000 && *pu_4_4==dat_bk){
				if(!analyt || ((*s(4,6) &0xF0)>>4)!=9){
					if(klt_mode){*pd_4_32=-*pd_4_32;}
					for(k=0;k<5;k++){
						if(*l(4,6)==btws[k]) break;
					}
					if(k<5){ebtw+=*pd_4_32;}
					else{
						for(k=0;k<10;k++){
							if(*l(4,6)==noomzet[k]) break;
						}
						if(k==10){eomz+=*pd_4_32;}
					}
				}
      }
    }
    *pd_5_35+=eomz;*pd_5_36+=ebtw;
    *l(5,7)+=eomz;*l(5,8)+=ebtw;
/* 5,20 =buitenland, dus btw=normaal 0 (tenzij bij aankoop, als */
/* er geboekt is op BTW EEG, dan moet die meegeteld worden) */
    if(fldlen(5,20)) *l(5,20)+=eomz+ebtw;
    if(fldlen(5,44)) *d(5,44)+=eomz+ebtw;
    fasinit(4);*l(4,1)=rec4_;fasgeti(4);/* originele terug laden */
  }
  endsr:;
}

static int16 cnt_dblbtw()
{
  uint16 rec_,g,n,pdbl_,*pu_lk_1;
  int16 p_klt_;
  long btwnr_,*p_btwnr_;
									
  zero((char *)&tb_kltdbl[0].rec,sizeof tb_kltdbl); p_klt_=0;
  pu_lk_1=u(stu_lk,1);
  p_btwnr_=l(stu_lk,10);btwnr_=*p_btwnr_;rec_=*u(stu_lk,1);
  for(pdbl_=0;pdbl_<DIM_DBLBTW;pdbl_++) if(r_dblbtw[pdbl_]==0 || rec_==r_dblbtw[pdbl_]) break;
  if(r_dblbtw[pdbl_]!=0 && pdbl_<DIM_DBLBTW) goto endsr;
  tb_kltdbl[p_klt_++].rec=rec_;
  btwnr_=*p_btwnr_ & 0xBFFFFFFF;
  if(btwnr_==000000000 || btwnr_==999999999 || *(s(stu_lk,10)+3) & 0x40) goto endsr;
  copy(s(stu_lk,1),buf1000,fldlen(stu_lk,0));
  fasinit(stu_lk); n=0;
  FOREVER{
    *pu_lk_1=++n;
    g=fasgeti(stu_lk);
    if(g==47)break;
    if(g!=46 && n!=rec_){/* deleted record */
      if(*p_btwnr_==btwnr_) {
	tb_kltdbl[p_klt_++].rec=n;r_dblbtw[pdbl_++]=n;
	if(p_klt_>=DIM_KLTDBLBTW) break;
	if(pdbl_>=DIM_DBLBTW) break;
      }
    }
  }
  copy(buf1000,s(stu_lk,1),fldlen(stu_lk,0));
  endsr:;
  return p_klt_;
}

static get_stkbd()
{
  int16 keyx,key_mode,journl,k;
  uint16 volgnr,dt_;
  long recnr;
	double bd0_,bd1_;

  fasinit(4);keyx=1;*u(4,5)=*u(stu_lk,1)+stu_01lk*30000;
  zero((char *)&bdkw[0],sizeof bdkw);
  FOREVER{
    if(faskeyi(4,4,keyx)) break;
    keyx=2;
    if(*u(4,5)!=*u(stu_lk,1)+stu_01lk*30000) break;
    journl=*s(4,2);volgnr=*u(4,3);dt_=*u(4,4);
    if(jrnal_btw[journl] && dt_>=dt_beg && dt_<=dt_end){
      recnr=*l(4,1);
      fasinit(4);*s(4,2)=journl;*u(4,3)=volgnr;key_mode=1;
			bd0_=0;bd1_=0;
      FOREVER{
				if(faskeyi(4,1,key_mode)) break;key_mode=2;
				if(journl!=*s(4,2) || volgnr!=*u(4,3)) break;
				if(*u(4,5)>=60000 && *u(4,4)==dt_){
					if(!analyt || ((*s(4,6) &0xF0)>>4)!=9){
						fasinit(3);*u(3,1)=*u(4,5)-60000;fasgeti(3);
						if(*u(3,8)==54){bd0_=0;bd1_=0;break;} // er werd BTW gerekend en dan factuur skippen
						if(stu_01lk){*pd_4_32=-*pd_4_32;}
						for(k=0;k<10;k++){
							if(*l(4,6)==noomzet[k]) break;
						}
						if(k==10){
							if(*u(3,8)==44)  bd1_+=*pd_4_32;
							else if(*u(3,8)) bd0_+=*pd_4_32;
						}
					}
				}
      }
			bdkw[0]+=bd0_;bdkw[1]+=bd1_;
      fasinit(4);*l(4,1)=recnr;fasgeti(4);
    }
  }
}

static upd()
{
  int16 curs=1,key,z;

  addfromstk=NO;/* enkel gearchiveerde omzet */
  FOREVER{
    fasinit(stu_lk);
    redo:
    scrget(1,5);z=1;
    scrifld(z++,fm_os20,"BTW-listing");
    scrfld(z++,25,1);
    scrifld(z++,fm_os20,"te raadplegen");
    scrfld(z++,stu_lk,3);
    key=scrupd(curs,0x0481);
    if(key==101) goto endsr;
    if(key==111) ovl_exit(10);
    if(search(stu_lk,0)) goto redo;
    btw_upd();
  }
  fasflush(0);
  endsr:;
}

static btw_upd()
{
  int16 curs=1,key,z;
  double total;

  get_btwbd();
  FOREVER{
    scrget(1,42);z=1;
    scrfld(z++,25,1);
    scrofld(z++,stu_lk,code[stu_01lk]+1,-1);
    scrofld(z++,stu_lk,3,-1);

    scrfld(z++,5,35);
    scrfld(z++,5,36);
    total=*pd_5_35+*pd_5_36; scrifld(z++,fm_bdr,&total);
    if(fldlen(5,44)){
      for(key=0;key<6;key+=2) scrfld(z++,5,44+key);
    }
    key=scrupd(curs,0x04A1);
    if(key==106) goto endsr;
    if(key==111) ovl_exit(10);
    if(key>=101) break;
  }
  if(*u(5,1)) fasupd(5);
  else{
    key=0;
    if(*l(5,7) || *l(5,8) || (fldlen(5,20) && *l(5,20))) key=1;
    if(!is_nul(*pd_5_35) || !is_nul(*pd_5_36) || (fldlen(5,44) && !is_nul(*d(5,44)))) key=1;
    if(key){
      fasinfo(5,1);
      if(*u(5,1)==0){
	*u(5,2)=0;fasadd(5);/* maak 1e record */
	*u(5,2)=*u(stu_lk,1)+stu_01lk*30000;fasadd(5);/* write 2e record */
	fasinit(5);*u(5,1)=1;fasupd(5);/* init 1e record */
      }
      else fasadd(5);
    }
  }
  endsr:;
}

static printb_lst()
{
  int16 curs=1,key,z;

  FOREVER{
    redo:;
    scrget(1,43);z=1;
		if(sys1790&0x04) scraddpicto(2,0,76,22,4,2,573,0,0,"Maak XLS"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_uu4,&jaarbtw);
    scrifld(z++,fm_udat,&dt_prt);
    scrifld(z++,fm_ul5,&min_btw);
    scrifld(z++,fm_u_JN,&prt_nbtw);
    key=scrupd(curs,0x0581);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) goto endsr;
    if(key==111) ovl_exit(10);
    if(chk_year(jaarbtw)) {curs=2;goto redo;}
//    if(addfromstk){
//      if(dsp_warn()) goto redo;
//    }
    prt2pdf=NO;if(key==109){prt2pdf=YES;key=108;}
		Prt2Xls=NO;if(key==5002){Prt2Xls=YES;key=108;}
    if(key==108) break;
  }
  btw_list();
  endsr:;
}

static btw_list()
{
  int16 k,z,q_klt_,cnt_dklt_,listnr,pos_,pmode_;
  uint16 rec_lk_;
	long btwnr_;
	char buf_[50];

	zero((char *)&r_dblbtw[0],sizeof r_dblbtw);
  omzet=0;belast=0;linenr=0;

	if(Prt2Xls){
		zero(buf_,sizeof buf_);
		sprintf_s(buf_,sizeof buf_,"BTW-listing leveringen %d",jaarbtw);
		XlsRef=OpenXlsFile(buf_,0,0);
    if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsSelectWorkSheet(XlsRef,1,"BTW-listing");
		XlsColumnSize(XlsRef,3,40);XlsColumnSize(XlsRef,4,30);XlsColumnSize(XlsRef,5,25);XlsColumnSize(XlsRef,6,15);
//XlsStyle(ref, char *NumFormat,Size, long /*COLORREF*/ Color, BoldFlag, ItalicFlag, UnderlineFlag,HorAlignment, VerAlignment,
//	long /*COLORREF*/ BackCol, int16 Pattern, Kader, KaderCol, Lock, Hide)
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
		StylGrpTot=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_BEIGE,1,1,0,NO,NO);
		StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);

		XlsRij=1;XlsKol=1;Styl2Use=StylTitel;
	  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Nr",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Code",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Naam",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Adres",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Gemeente",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"BTW-nummer",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omzet",Styl2Use);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"BTW",Styl2Use);
		XlsRij++;
	}
	else{
		getsysprNew(3,form_dat,&pr_mode,&prtnr);
		if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
		if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
		free=999;
		scrget(1,6);scrupd(-3,0);

		prtfld(25,1,25);
		prttext("<t30b>BTW-listing leveringen ");
		if(addfromstk) prttext("<u>");/* markering onvolledige archivatie */
		prtifld(fm_uu4,&jaarbtw,-1);
		if(addfromstk) prttext("<u>");
		prttext("<t90>Datum : "); prtifld(fm_udat,&dt_prt,-1); prttext("<t120>Blz.<ppp>.");
		prtbuf(1);
		z=1;
		prtitab(z,fm_uu4,&listnr,1,-1); prttitle(z++,"Nr",3);
		prttab(z,stu_lk,code[stu_01lk]+1,2,-1); prttitle(z++,"Code",3);
		prttab(z,stu_lk,3,1,30); prttitle(z++,"Naam",3);
		prttab(z,stu_lk,4,1,25); prttitle(z++,"Straat & Nummer",3);
		prttab(z,stu_lk,6,1,20); prttitle(z++,"Gemeente",3);
		prttab(z,stu_lk,10,1,-1); prttitle(z++,"BTW-nummer",3);
		prttab(z,5,35,1,-1); prttitle(z++,"Omzet",0x13);
		prttab(z,5,36,1,-1); prttitle(z++,"BTW",0x13);
		prtbuf(3);
		p_pdfname("BTW-listing",dt_end,0);
	}

  fasinit(stu_lk); cnt_dklt_=0; listnr=0;
  scrget(1,170);scrifld(10,fm_os63,"Berekenen/controleren van ");
  while(free>=0){
    next_klt:;
    if(faskeyi(stu_lk,2,2)) break; rec_lk_=*u(stu_lk,1);
    q_klt_=get_klttotaal(); if(q_klt_==0) goto next_klt;
    if(*pd_5_35>=min_btw || *pd_5_35<=-min_btw || min_btw==0){
      listnr++;scrupd(-3,0);
      btwnr_=(*l(stu_lk,10))&0xBFFFFFFF;/* zonder egal.bit */
      pmode_=0; if(btwnr_==999999999 || btwnr_==0 || *(s(stu_lk,10)+3) & 0x40) pmode_=1;
			if(Prt2Xls){
				XlsKol=1;
				WriteVar2Xls(XlsRij,XlsKol++,fm_uu4,&listnr,0);
				WriteFld2Xls(XlsRij,XlsKol++,stu_lk,code[stu_01lk]+1,0);
				WriteFld2Xls(XlsRij,XlsKol++,stu_lk,3,0);
				WriteFld2Xls(XlsRij,XlsKol++,stu_lk,4,0);
				WriteFld2Xls(XlsRij,XlsKol++,stu_lk,6,0);
				WriteFld2Xls(XlsRij,XlsKol++,stu_lk,10,0);
				WriteFld2Xls(XlsRij,XlsKol++,5,35,0);
				WriteFld2Xls(XlsRij,XlsKol++,5,36,0);
				XlsRij++;
			}
			else{
			   for(k=1;k<=15;k++) prtinfo(k,pmode_);nextline();
			}
      if(q_klt_>1){/* dubbele BTW-nummers afdrukken */
				for(z=1;z<q_klt_;z++){
					if(is_nul(tb_kltdbl[z].omzet)) continue;
					*u(stu_lk,1)=tb_kltdbl[z].rec; fasgeti(stu_lk);
					if(Prt2Xls){
						XlsKol=2;
						WriteFld2Xls(XlsRij,XlsKol++,stu_lk,code[stu_01lk]+1,0);
						WriteFld2Xls(XlsRij,XlsKol++,stu_lk,3,0);
						WriteFld2Xls(XlsRij,XlsKol++,stu_lk,4,0);
						WriteFld2Xls(XlsRij,XlsKol++,stu_lk,6,0);
						WriteFld2Xls(XlsRij,XlsKol++,stu_lk,10,0);
						XlsRij++;
					}
					else{
						for(k=2;k<7;k++) prtinfo(k,2);nextline();
					}
					cnt_dklt_++;
				}
				*u(stu_lk,1)=rec_lk_; fasgeti(stu_lk);
      }
      linenr++;
      omzet+=*pd_5_35;belast+=*pd_5_36;
    }
  }
	if(Prt2Xls) XlsClose(XlsRef,1);
	else{
		nextline();
		prttext("Totaal aantal klanten : ");prtifld(fm_uu4,&linenr,-1); nextline();
		prttext("Totaal omzet excl.BTW : ");prtifld(fm_bdr,&omzet,-1);
		prttext(" EUR"); nextline();
		prttext("Totaal BTW .......... : ");prtifld(fm_bdr,&belast,-1);
		prttext(" EUR"); nextline();
		zero(filnam,sizeof filnam); pos_=0;
		pos_+=copy0("BTW-Listing_",&filnam[pos_],20);
		pos_+=copy0(s(25,3),&filnam[pos_],3);
		pos_+=copy0("_",&filnam[pos_],20);
		stcli_d(&filnam[pos_],(long)jaarbtw,4,1);pos_+=4;
		pos_+=copy0(".xml",&filnam[pos_],20);
		prttext("Naam intervat-bestand : ");prtifld(fm_os63,filnam,30);nextline();
		if(cnt_dklt_){
			nextline();
			prttext("<b>WAARSCHUWING : Er werden");prtifld(fm_ou3,&cnt_dklt_,-1);
			prttext(" dubbele BTW-nummers gevonden (zie klanten in het vet)!<b>");
			nextline();
			prttext("<b>De bedragen van deze klanten werden opgeteld in de eerste BTW-nummer.<b>");
			nextline();
		}
		prtform(0);
		prtclose();
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
	pos_+=copy0(".XLS",&string[pos_],4);
	
  pos_=XlsCreate(string);
	return pos_;
}

static int16 get_klttotaal()
{
  int16 k,q_klt_;
  uint16 rec5_,rec_lk_;
  long btwnr_;
  double klt_omz_,klt_btw_;

  fasinit(5);q_klt_=0;
  btwnr_=*l(stu_lk,10)&0xBFFFFFFF;
  if((*l(stu_lk,10)==999999999 || btwnr_==000000000 || *(s(stu_lk,10)+3) & 0x40) && prt_nbtw!='J') return 0;
  get_btwbd(); if(is_nul(*pd_5_35)) return 0;
  scrofld(14,stu_lk,3,-1);
  q_klt_=cnt_dblbtw(); if(q_klt_==0) return 0;/* klt al gedaan */
  klt_omz_=0;klt_btw_=0;rec5_=0;rec_lk_=*u(stu_lk,1);
  for(k=0; k<q_klt_;k++){
    *u(stu_lk,1)=tb_kltdbl[k].rec; fasgeti(stu_lk);
    get_btwbd();
    tb_kltdbl[k].omzet=*pd_5_35; tb_kltdbl[k].btw=*pd_5_36;
    klt_omz_+=tb_kltdbl[k].omzet; klt_btw_+=tb_kltdbl[k].btw;
    if(rec5_==0) rec5_=*u(5,1);
  }
  *u(stu_lk,1)=rec_lk_; fasgeti(stu_lk);
  *pd_5_35=valu_cnv("EUR","EUR",(double)klt_omz_,(double)(0.01)); 
	*pd_5_36=valu_cnv("EUR","EUR",(double)klt_btw_,(double)(0.01)); 
	*u(5,1)=rec5_;
  if(!((addfromstk || *u(5,1)) && !is_nul(*pd_5_35))) return 0;
  endsr:;
  return q_klt_;
}

static printk_lst()
{
  int16 curs=1,key,z,dd,mm;
 
  if(jaarbtw==0) jddate(*u(25,2),&jaarbtw,&mm,&dd);
  FOREVER{
    redo:;
    scrget(1,83);z=1;
    scrfld(z++,25,1);
    if(btw_periode) scrifld(z++,fm_os10,"Kwartaal ..");
    else scrifld(z++,fm_os10,"Maand .....");
    scrifld(z++,fm_uu2,&kwartaal);
    scrifld(z++,fm_uu4,&jaarbtw);
    scrifld(z++,fm_udat,&dt_prt);
    key=scrupd(curs,0x0581);
    if(key==101) goto endsr;
    if(key==111) ovl_exit(10);
    if(jaarbtw==0){curs=4;errnum=39;goto redo;}
    if(btw_periode){/* kwartaal of jaar */
      if(kwartaal<1 || kwartaal>4){curs=3;errnum=34;goto redo;}
      dt_beg=datejd(jaarbtw,(kwartaal-1)*3+1,1);
      if(dt_beg<=last_arc){curs=3;errnum=34;goto redo;}
    }
    else {
      if(kwartaal<1 || kwartaal>12){curs=3;errnum=34;goto redo;}
      dt_beg=datejd(jaarbtw,kwartaal,1);
      if(dt_beg<=last_arc){curs=3;errnum=34;goto redo;}
    }
    prt2pdf=NO;if(key==109){prt2pdf=YES;key=108;}
    if(key==108) break;
  }
  scrget(1,7);scrupd(-3,0);
  if(btw_periode){
    dt_beg=datejd(jaarbtw,(kwartaal-1)*3+1,1);
    z=jaarbtw;key=kwartaal;if(key==4){key=1;z++;} else key++;
    dt_end=datejd(z,(key-1)*3+1,1)-1;
  }
  else{
    dt_beg=datejd(jaarbtw,kwartaal,1);
    z=jaarbtw;key=kwartaal;if(key==12){key=1;z++;} else key++;
    dt_end=datejd(z,key,1)-1;
  }
  kwartlist();
  endsr:;
}

static kwartcount()
{
  int16 k;

  fasinit(stu_lk);qklt=0;omzet=0;
  zero((char *)&r_dblbtw[0],sizeof r_dblbtw);
  while(getkwnext()){
    for(k=0;k<3;k++){
      if(bdkw[k]){qklt++; omzet+=bdkw[k];}
    }
  }
  endsr:;
}

static kwartlist()
{
  int16 j,k,z,listnr_,pos_;
  char lnd_[4],code_,btwnr_[20],kar_;
  double bedrag_,k_omzet[3];
									
  getsysprNew(3,form_dat,&pr_mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) goto endsr;
  free=999;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,25);
  prttext("<t30b>Intracommunautaire opgave, ");
  if(btw_periode) prttext("kwartaal "); else prttext("maand ");
  prtifld(fm_uu2,&kwartaal,-1);prttext("/");prtifld(fm_uu4,&jaarbtw,-1);
  prttext("<bt97>Datum : "); prtifld(fm_udat,&dt_prt,-1); prttext("<t120>Blz.<ppp>");
  prtbuf(1);
  z=1;
  prtitab(z,fm_uu4,&listnr_,1,-1); prttitle(z++,"Nr",0x13);
  prttab(z,stu_lk,code[stu_01lk]+1,2,-1); prttitle(z++,"Code",3);
  prttab(z,stu_lk,3,1,27); prttitle(z++,"Naam",3);
  prttab(z,stu_lk,4,1,25); prttitle(z++,"Straat & Nummer",3);
  prttab(z,stu_lk,6,1,17); prttitle(z++,"Gemeente",3);
  prttab(z,stu_lk,7,1,8); prttitle(z++,"Land",3);
  prtitab(z,fm_us2,lnd_,1,-1); prttitle(z++,"LC",3);
  prtitab(z,fm_us15,btwnr_,1,-1); prttitle(z++,"BTW-nummer",3);
  prtitab(z,fm_us1,&code_,1,-1); prttitle(z++,"C",3);
  prtitab(z,fm_bdr,&bedrag_,1,-1); prttitle(z++,"Bedrag",0x13);
  prtbuf(3);
  p_pdfname("Intracommunautaire opgave",dt_beg,dt_end);
 

  fasinit(stu_lk);zero((char *)&k_omzet[0],sizeof k_omzet);listnr_=0;
  zero((char *)&r_dblbtw[0],sizeof r_dblbtw);
  while(free>=0){
    if(getkwnext()==NO) break;
    scrget(1,170); scrfld(10,2,3);scrupd(-3,0);
    zero(lnd_,sizeof lnd_); k=0;
    copy(s(2,22),lnd_,2);
    for(j=0;j<2;j++){
      if(lnd_[j]<'a' && lnd_[j]>'z' && lnd_[j]<'A' && lnd_[j]>'Z') break;
    }
    if(j<2) zero(lnd_,sizeof lnd_);/* ongeldig land */
/* indien in BTW-nr ook landcode, dan deze weglaten */
    j=0; if(cmpstrU(lnd_,s(2,22),2)==0) j=2;
    zero(btwnr_,sizeof btwnr_); k=0;
    for(j;j<fldlen(2,22);j++){
      kar_=*(s(2,22)+j);
      if((kar_>='0' && kar_<='9') || (kar_>='a' && kar_<='z') || (kar_>='A' && kar_<='Z')){
	btwnr_[k++]=kar_;
      }
    }
    for(k=0;k<3;k++){
      if(bdkw[k]){
	code_=typ[k]; bedrag_=bdkw[k];listnr_++;
	for(j=0;j<20;j++) prtinfo(j,0);nextline();
	k_omzet[k]+=bdkw[k];
      }
    }
  }

  nextline();
  for(k=0;k<3;k++){
    if(k_omzet[k]){
      zero(btwnr_,sizeof btwnr_);zero(lnd_,sizeof lnd_);
      fasinit(stu_lk);copy("Totaal omzet excl. BTW",s(stu_lk,3),30);
      bedrag_=k_omzet[k];code_=typ[k];
      for(j=3;j<20;j++) prtinfo(j,2);nextline();
    }
  }
  prttext("Totaal aantal klanten : ");prtifld(fm_uu4,&listnr_,-1); nextline();
	zero(filnam,sizeof filnam); pos_=0;
	pos_+=copy0("Intr_Opgave_",&filnam[pos_],20);
	pos_+=copy0(s(25,3),&filnam[pos_],3);
	pos_+=copy0("_",&filnam[pos_],20);
	stcli_d(&filnam[pos_],(long)jaarbtw,4,1);pos_+=4;
	if(btw_periode){
	  pos_+=copy0("-KW",&filnam[pos_],20);
		stcli_d(&filnam[pos_],(long)kwartaal,1,0);pos_+=1;
	}
	else{
		pos_+=copy0("-",&filnam[pos_],20);
		stcli_d(&filnam[pos_],(long)kwartaal,2,0);pos_+=2;
	}
  pos_+=copy0(".xml",&filnam[pos_],20);
  prttext("Naam intervat-bestand : ");prtifld(fm_os63,filnam,30);nextline();
  prtform(0);
  prtclose();
  endsr:;
}

static getkwnext()
{
  int16 k,len_btwnr_,pdbl_,p_klt_;
  char lnd_[3],*p_btwnr_,btwnr_[20];
  uint16 *pu_lk_1,rec_,g,n;
  double k_bd_[3];
 
  pu_lk_1=u(stu_lk,1);
  p_btwnr_=s(stu_lk,22);len_btwnr_=fldlen(stu_lk,22);
  zero((char *)&k_bd_[0],sizeof k_bd_);
  zero((char *)&bdkw[0],sizeof bdkw);
 
  FOREVER{
    next:;
    if(faskeyi(stu_lk,2,2)) break;
    if(*s(stu_lk,22)=='\0') goto next;
    zero(lnd_,sizeof lnd_); k=0;
    copy(s(stu_lk,22),lnd_,2);/* 2 eerste letters BTW-nr */
    for(k=0;k<2;k++){
      if(lnd_[k]<'a' && lnd_[k]>'z' && lnd_[k]<'A' && lnd_[k]>'Z') break;
    }
    if(k<2) goto next;/* ongeldig land */
    for(k=0;k<DIM_EU;k++) if(cmpstrU(lnd_,eu_land[k],2)==0) break;
    if(k>=DIM_EU) goto next;
    zero((char *)&k_bd_[0],sizeof k_bd_);
    copy(p_btwnr_,btwnr_,len_btwnr_); rec_=*pu_lk_1;

    zero((char *)&tb_kltdbl[0].rec,sizeof tb_kltdbl); p_klt_=0;
    for(pdbl_=0;pdbl_<DIM_DBLBTW;pdbl_++) if(r_dblbtw[pdbl_]==0 || rec_==r_dblbtw[pdbl_]) break;
    if(r_dblbtw[pdbl_]!=0 && pdbl_<DIM_DBLBTW) goto next;
    fasinit(stu_lk); n=0;
    FOREVER{
      *pu_lk_1=++n;
      g=fasgeti(stu_lk);
      if(g==47)break;
      if(g!=46){/* deleted record */
	if(cmp_bbtwnr(btwnr_,p_btwnr_,len_btwnr_)==NO) {
	  get_stkbd();
	  for(k=0;k<3;k++) k_bd_[k]+=bdkw[k];
	  if(*pu_lk_1!=rec_){
	    r_dblbtw[pdbl_++]=n;p_klt_++;
	    if(p_klt_==1) r_dblbtw[pdbl_++]=rec_;
	  }
	  if(pdbl_>=DIM_DBLBTW) break;
	}
      }
    }
    *pu_lk_1=rec_;fasgeti(stu_lk);
    for(k=0;k<3;k++) bdkw[k]=valu_cnv("EUR","EUR",(double)(k_bd_[k]),(double)(0.01));
    if(bdkw[0] || bdkw[1] || bdkw[2]) return YES;
  }
  return NO;
}

static salfiltst()
{
  fasinfo(5,1);
  if(*u(5,1)==0) return NO;
  return YES;
}

static bd2str(ps_,bd_,totlen_)
char *ps_;
double bd_;
int16 totlen_;
{
  int16 k,len_,negat_;
  long val_,val1_;
									
  negat_=NO; if(bd_<0){negat_=YES;bd_=-bd_;}
  if(bd_>(double)(9999999)){/* behandelen als getal zonder decimalen */
    val1_=(long)(((bd_*100.)+.49)/100.); val_=0;
  }
  else {
    val_=(long)((bd_*100.)+.49); val1_=val_/(long)100;
    val_=val_-val1_*(long)100;
  }
  len_=totlen_-3;
  stcli_d(ps_,val1_,len_,1);
  if(negat_){/* negatief getal */
    for(k=0;k<len_;k++) if(*(ps_+k)!=' ') break;
    if(k>0) *(ps_+k-1)='-';
  }
  *(ps_+len_)=',';
  stcli_d(ps_+len_+1,val_,2,0);
}

static copy0(ps,pd,max_len_)
char *ps,*pd;
int16 max_len_;
{
  int16 fuval=0;
			
  while(*ps && max_len_--){
    *pd++=*ps++;
    fuval++;
  }
  *pd='\0';
  return fuval;
}
 
static initload()
{
  int16 j=0,k,z;
	char str_[10];

  fasunlck(0);
	fileopen(1);
  fileopen(stu_lk);
  allow_yr=NO; if(fldlen(86,1)>0) allow_yr=YES;
  if(allow_yr) fileopen(10);
									
  fileopen(3);
  fileopen(4);
  fileopen(5);

  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);
  sysget( 780,4,&levcent);
  sysget( 784,4,&kltcent);
  sysget( 788,5*4,&btws[0]);
  sysget( 968,10*4,&noomzet[0]);
  sysget(1625,65,nm_teken);
  sysget(1420,30,intervat.naam);
  sysget(1450,30,intervat.hoedanig);
  sysget(1480,20,intervat.telefoon);
	sysget(1790,2,&sys1790);
//  sysget(1729,2,&intervat.verantwoordelijke);
  sysget(1858,2,&last_arc);
  sysget(1864,2,&btw_periode);
  sysget(1872,4,&min_btw); if(min_btw==0) min_btw=250;
  sysget(1918,2,&sear_stt);
  sysget(2682,2,&sys2682);
  sysget(3876,2,&sys3876);

  for(k=0;k<80;k++){
    sysget(10242+k*80,2,(char *)&j);
    if(j<=2){
      sysget(10240+k*80,2,(char *)&j);
      jrnal_btw[j]=YES;/* A.K.+V.K. */
    }
  }
  analyt=fldlen(4,11);
 
  firmbtwn=0;z=0;j=-1;
  for(k=0;k<15;k++){
    if(firma[86+k]=='\0') break;
    if(firma[86+k]>='0' && firma[86+k]<='9'){
      z++;if(j==-1) j=k;
    }
  }
  for(k=0;k<15;k++){
    if(firma[86+k]=='\0') break;
    if(firma[86+k]>='0' && firma[86+k]<='9'){
      if(k>j || z<=10){                     /* enkel laatste 9 cijfers nemen */
	firmbtwn=(firmbtwn*10) + (firma[86+k]-'0');
      }
    }
  }
	if(firmbtwn>1000000000) {
    firmbtwn-= 1000000000L;
  	copy((char *)(&firmbtwn), str_, 4);
	  str_[3] |= 0x80; copy(str_, (char *)(&firmbtwn), 4);
	}

  copy(fm_ud8_2,fm_bdr,sizeof fm_ud8_2);
  copy(fm_ud82_,fm_vbdr,sizeof fm_ud82_);
  copy("EUR",def_munt,3);

  p_data=s(80,1)+4;
  ps_4_2=s(4,2);
  pu_4_3=u(4,3);
  pu_4_4=u(4,4);
  pu_4_5=u(4,5);
  pd_4_32=d(4,32);
  pd_5_35=d(5,35);
  pd_5_36=d(5,36);
  pu_4_1=u(4,1); pl_4_1=l(4,1); len4_1=fldlen(4,1);
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
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
  code[0]=lvcd;code[1]=klcd;
}

static ovl_exit(nr)
int16 nr;
{
  sysput(1872,4,&min_btw);
  ovlexit(nr);
}

static dsp_warn()
{
  int16 key;
					
  scrget(1,57);
  scrifld(1,fm_uu4,&jaarbtw);
  key=scrupd(-1,0x19);
  if(key==104){scrget(1,7);scrupd(-3,0);return NO;}
  return YES;
}

static cmpstrU(p1,p2,len)
char *p1,*p2;
int16 len;
{
  char kar1_,kar2_;
 
  while(len--){
    kar1_=*p1;
    if(kar1_>='a' && kar1_<='z') kar1_+='A'-'a';
    kar2_=*p2;
    if(kar2_>='a' && kar2_<='z') kar2_+='A'-'a';
    if(kar1_!=kar2_) return 1;
    p1++;p2++;
  }
  return 0;
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

static de_heer()
{
  int16 g,j,k,slen;
  char *px,nm_dehr[53];

  px=s(stu_lk,3);slen=fldlen(stu_lk,3);
  for(k=0;k<slen-1;k++){
    if(*(px+k)=='*')break;
  }
  if(k>=slen-2) goto endsr;
  else{
    for(g=k+1;g<slen;g++) if(*(px+g)!=' ') break;
    if(g>slen-1) copy(px,nm_dehr,slen);
    else{
      for(j=slen-1;j>=g;j--) if(*(px+j)>' ') break;
      j=j-g+1;
      copy(px+g,nm_dehr,j);
      nm_dehr[j++]=' ';
      g=slen-j;if(g>k) g=k;
      copy(px,&nm_dehr[j],g);
      nm_dehr[j+g]='\0';
    }
  }
  copy(nm_dehr,px,slen);
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
		if(string[pos_+len_-1]=='.') string[pos_+len_-1]=' '; // geen punt op einde van naam 
    copy(&string[pos_],&buf_[2],len_);
    buf_[2+len_]=0xD0;
    prttext(buf_);
    slen_-=len_;pos_+=len_;
  }
}

static nextline()
{
  free=prtline();
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

static cmp_bbtwnr(btw1_,btw2_,blen_)
char *btw1_,*btw2_;
int16 blen_;
{
  int16 k,l1_,l2_;
  char b1_[30],b2_[30];

  zero(b1_,sizeof b1_);zero(b2_,sizeof b2_);l1_=0;l2_=0;
  for(k=0;k<blen_;k++) {
    if(is_kar(btw1_[k])) b1_[l1_++]=btw1_[k];
    if(is_kar(btw2_[k])) b2_[l2_++]=btw2_[k];
  }
  return cmpstr(b1_,b2_,blen_);
}

static is_kar(b)
char b;
{
  if(b>='0' && b<='9') return YES;
  if(b>='a' && b<='z') return YES;
  if(b>='A' && b<='Z') return YES;
  return NO;
}
