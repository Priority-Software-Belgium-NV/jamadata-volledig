/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0065GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0065dat
#define ovlcod BKH0065cod
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

char ovldat[] = "bkh0065  00:10 16/09/10 (c) Jamadata";
/* BTW-aangifte */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16

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
} j_tab[81];/* 1 extra element */
 
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
} *sel_lst;


extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
static long val4_1();
extern float *f();
extern double *d(),valu_cnv();
static double round();

static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os70[]  = {7,0x88,70,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os12[]  = {7,0x88,12,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou2_[]  = {6,0x90,2,0,0x10,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x10,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_ui3[]   = {6,0xD1,3,0,0x60,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud8_2[] = {6,0xD5,8,2,0x70,0};
static char fm_ul9[]   = {6,0xD3,9,0,0x70,0};
static char fm_uf21_[] = {6,0xD4,2,1,0x20,0};
static char fm_ctrl[]  = {6,0x95,9,0,0x60,0};
static char fm_uJN[]   = {11,0xC8,1,0,0x09,0,'J','J','N','N',0};

static int16 vk_vakken[11]={0,1,2,3,44,45,46,47,48,49,54};
static int16 ak_vakken[15]={55,56,57,59,63,64,81,82,83,84,85,86,87,88};
static int16 dsp_vakken[30]={0,1,2,3,44,45,46,47,48,49,54,55,56,57,59,61,62,63,64,65,66,81,82,83,84,85,86,87,88,91};
static int16 form_dat[8],pr_mode,free,prtnr,taal;
static int16 stulk,arr_jr,pr_open,max_jrnl;
static int16 kwart,x_offset,y_offset,vak_xoff,lettype;
static uint16 stuknr,rekennr,ref_yy,ref_jr,ref_vl;
static uint16 dt_beg,dt_end,jr_beg,jr_end,volg_beg,volg_end,dt_aangifte;
static uint16 last_arc,nr_journ,jr_typ,btwvaknr[5],bk_dat,inq_vak;
static double bedrag,bd_deb,bd_cre,max_afw,cum_vbd;
static long sub_mask,bkh_btwn,firmbtwn;
static double btw_bdjr[100],btw_bdt[100],btw_bdft[100],afronding;
static char naam[30],klnaam[30],omschr[40],rek_kod[9],def_munt[4];
static char sys1785,sys1786,buf_400[400],firma[350];
static char teruggave='N',bet_form='N',nihil_blst='N';;
static char lin2prt[100],fm_bdr[40],*p_data,p_old_doc,nm_teken[66];
static flag debit_allow=NO,credt_allow=NO,lvcd,klcd;
static flag analyt,opened[10],v86_used,v87_used,v88_used,sys1824,err_found,vak_modified;
static float btwpct[4],vak_pct[5],max_btw;
static char *ps_4_2;
static uint16 *pu_4_1,len4_1;
static long *pl_4_1;
static struct {
  char filnam[100];
  int16 h_off;
  int16 v_off;
  char naam[31];
  char hoedanig[31];
  char telefoon[21];
  uint16 verantwoordelijke;
} intervat;
						      /* de seqo-variabelen */

									
static char seqo_str[1000];
static char filnam[40];
static long seqo_pos,value;
static int16 seqo_len,seqo_mode,pos;


ovlcod()
{
  sel_lst=(struct _sel_lst*)u(26,1);
  if(sel_lst->jr || sel_lst->a_btw){
    initload();fasunlck(-1);
    execute();
  }
  ovl_exit(62);
}


static execute()
{
  int16 ks,key_mode;
  flag first=YES;

  scrget(1,6);scrupd(-3,0);
  fasinit(4);err_found=NO;
  if(jr_beg || volg_beg){*ps_4_2=jr_beg;*u(4,3)=volg_beg;}
  key_mode=1;
  FOREVER{
    ks=faskeyi(4,1,key_mode);key_mode=2;
    if((*ps_4_2>jr_end) || (*ps_4_2==jr_end && *u(4,3)>volg_end)) ks=YES;
    if(max_jrnl && *ps_4_2>max_jrnl) ks=YES;/* limiet journaal  */
    if(ks)*ps_4_2=255;
    if(!ks){
      if((*u(4,4)<dt_beg || *u(4,4)>dt_end)) goto next;
      if(fldlen(4,19) && ((sub_mask & *l(4,19))==0)) goto next;
      if(is_openjnl((int16)(*ps_4_2))) goto next;/* geen openingsjournaal */
    }
    if(*ps_4_2!=nr_journ || *u(4,3)!=stuknr){
      if(first==NO){
	end_btw(NO);
	if(*ps_4_2!=nr_journ) exit_jrn();
      }
      if(ks)break;
      if(*ps_4_2!=nr_journ) init_jrn();
      init_stk();
    }
    if(ks)break;
    add_bew();
    first=NO;
    next:;
  }
  if(pr_open) free=prtclose(); pr_open=NO;
  if(free==-1) {prtclose();ovl_exit(10);}
  endsr:;
}

static init_jrn()
{
  nr_journ=*ps_4_2;
  for(arr_jr=0;arr_jr<80;arr_jr++){
    if(nr_journ==j_tab[arr_jr].nr) break;
  }
  jr_typ=j_tab[arr_jr].typ;
  zeros((char *)btw_bdjr,sizeof btw_bdjr);
  if((last_arc==0 || dt_beg==(last_arc+1)) &&
      (*u(26,4)!=nr_journ || *u(26,5)==0)){
    fasinit(3);*l(3,2)=j_tab[arr_jr].fingrb;faskeyi(3,1,0);
    fasinit(5);*u(5,2)=*u(3,1)+60000;faskeyi(5,1,0);
  }
  if(jr_typ<3){
    if(jr_typ==1)stulk=1; else stulk=2;
  }
}

static init_stk()
{
  zeros(klnaam,sizeof klnaam);
  stuknr=*u(4,3);
}

static add_bew()/* voeg 1 boeking toe in tabel of print16 1 financiele lijn */
{

  if(analyt && ((*s(4,6) &0xF0)>>4)==9) goto endsr;
  makename();
  bedrag=*d(4,32);
  if(stulk==3 && *u(3,8)) add_btw();
  endsr:;
}

static makename()
{
  int16 len_;
  long long1;
  char ch_type;

  rekennr=*u(4,5);
  if(rekennr<30000){stulk=1;ch_type='L';}
  else if(rekennr<60000){stulk=2;rekennr=rekennr-30000;ch_type='K';}
  else {stulk=3;rekennr=rekennr-60000;ch_type='G';}
  long1=rekennr;
  if(!opened[stulk]) goto notfound;
  fasinit(stulk);
  *u(stulk,1)=rekennr;
  if(fasgeti(stulk)){
    notfound:;
    copy("???",naam,4);
    if(stulk<3)copy("???",klnaam,4);
    rek_kod[0]=ch_type;
    stcli_d(&rek_kod[1],long1,5,1);rek_kod[6]='\0';
    *s(3,6)='0';*s(3,7)='0';
    goto endsr;
  }
  len_=fldlen(stulk,3); if(len_>30) len_=30; zeros(naam,sizeof naam);
  copy(s(stulk,3),naam,len_);
  if(stulk<3)copy(s(stulk,3),klnaam,30);
  if(stulk!=3) {*s(3,6)='0';*s(3,7)='0';}
  if(stulk==3)grb_deco(rek_kod,l(4,6));
  else{
    rek_kod[0]=ch_type;
    if((stulk==1 && lvcd) || (stulk==2 && klcd)){
      rek_kod[1]=' ';
      copy(s(stulk,2),&rek_kod[2],6);
      if(fldlen(stulk,2)<6) rek_kod[2+fldlen(stulk,2)]='\0';
    }
    else{
      stcli_d(&rek_kod[1],long1,5,1);
      rek_kod[6]='\0';
    }
  }
  endsr:;
}


static exit_jrn()
{
  if(*ps_4_2==255){
    if(sel_lst->a_btw) prt_btw(YES);/* alle journalen samen */
  }
}

static initload()
{
  int16 z,j,k;
	char str_[10];

  fasunlck(0);
  sysget(1804,2,&k);
  if(k & 3) debit_allow=YES;
  if(k & 5) credt_allow=YES;

  if(credt_allow) fileopen(1);
  if(debit_allow) fileopen(2);
  for(k=3;k<=5;k++) fileopen(k);

  sysget(1008,16,&btwpct[0]);
  for(k=0;k<80;k++){
    sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
    j_tab[k].blz_n=j_tab[k].blz_o;
  }
  j_tab[80].nr=0;j_tab[80].typ=3;copy("???",&j_tab[80].nm[0],4);

  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);

  sysget(290,4,&bkh_btwn);
  sysget(294,4,def_munt);
  sysget(1024,20,&vak_pct[0]);
  sysget(1217,2,&max_jrnl);
  sysget(1416,2,&intervat.h_off);
  sysget(1418,2,&intervat.v_off);
  sysget(1420,30,intervat.naam);
  sysget(1450,30,intervat.hoedanig);
  sysget(1480,20,intervat.telefoon);
  sysget(1625,65,nm_teken);
  sysget(1729,2,&intervat.verantwoordelijke);
	if (intervat.verantwoordelijke) {
		fasinit(1);	*u(1, 1) = intervat.verantwoordelijke;
		if(fasgeti(1)){
			intervat.verantwoordelijke=0; sysput(1729,2,&intervat.verantwoordelijke);
		}
	}
  sysget(1785,1,&sys1785);
  sysget(1786,1,&sys1786);
  sysget(1824,2,&sys1824);
  sysget(1826,2,&x_offset);
  sysget(1828,2,&y_offset);
  sysget(1830,1,&p_old_doc);
  if(p_old_doc!='L' && p_old_doc!='D') {
    p_old_doc='L';
    sysput(1830,1,&p_old_doc);
  }
  sysget(1831,2,&vak_xoff);
  sysget(1858,2,&last_arc);
  sysget(1864,2,&kwart);
  sysget(1896,10,&btwvaknr[0]);
  sysget(3584,2,&taal); taal=0;/* if(taal!=1) taal=0; geen Frans */

  getsysprNew(3,form_dat,&pr_mode,&prtnr);

  dt_beg=*u(26,2);
  dt_end=*u(26,3);
  jr_beg=*u(26,4);volg_beg=*u(26,5);
  jr_end=*u(26,6);volg_end=*u(26,7);

  analyt=fldlen(4,11);
  sub_mask=*l(26,14);
  p_data=s(80,1)+4;
  ps_4_2=s(4,2);
  pu_4_1=u(4,1); pl_4_1=l(4,1); len4_1=fldlen(4,1);

  copy(fm_ud8_2,fm_bdr,sizeof fm_ud8_2); afronding=(double)0.01;
  max_afw=(double)60.;

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
      if(k>j || z<=10){                     /* enkel laatste 10 cijfers nemen */
	firmbtwn=(firmbtwn*10) + (firma[86+k]-'0');
      }
    }
  }
	if(firmbtwn>1000000000) {
    firmbtwn-= 1000000000L;
  	copy((char *)(&firmbtwn), str_, 4);
	  str_[3] |= 0x80; copy(str_, (char *)(&firmbtwn), 4);
	}
	if(cmpstr(&firma[86],"BE",2) && cmpstr(&firma[86],"be",2)) firmbtwn=0; // geen buitenlandse btw
  max_btw=0;
  for(k=0;k<5;k++) if(btwvaknr[k]==3) {max_btw=vak_pct[k];break;}
  // open_ctrl();
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


static open_ctrl()
{
  int16 z;
 
	getsysprNew(3,form_dat,&pr_mode,&prtnr);if(sel_lst->prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,4))!=0) ovl_exit(10);
  free=999;pr_open=YES;
  prtfld(25,1,-1);
  prttext("<t50b>Controle BTW-aangifte<b>");
  prttext("<t92>"); prtfld(26,2,-1);
  prttext(" - "); prtfld(26,3,-1);
  prttext("<t122>Blz.<ppp>.");
  prtbuf(1); z=1;
  prtitab(z,fm_uu2,&nr_journ,1,-1); prttitle(z++,"Jr",0x13);
  prtitab(z,fm_ou5,&stuknr,1,-1); prttitle(z++,"Nr.",0x13);
  prtitab(z,fm_odat,&bk_dat,1,-1); prttitle(z++,"Datum",0x43);
  prtitab(z,fm_os30,naam,1,30); prttitle(z++,"Omschrijving",3);
  prttab(z,3,2,1,-1);prttitle(z++,"Rekening",0x43);
  prtitab(z,fm_bdr,&bd_deb,1,-1); prttitle(z++,"D-Bedrag",0x13);
  prtitab(z,fm_bdr,&bd_cre,4,-1); prttitle(z++,"C-Bedrag",0x13);
  prttab(z,3,8,1,-1);prttitle(z++,"Vak",0x13);
  prtbuf(3);
  p_pdfname("Controle BTW-aangifte",dt_beg,dt_end);
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





static fileopen(nr_)
int16 nr_;
{
  int16 stu_,k;
  char filename[15];

  k=300+17*(nr_-1);
  sysget(k,15,filename);
  sysget(k+15,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(errnum=fasopen(filename,0)) ovlexit(10);
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  }
  opened[nr_]=YES;
}

static ovl_exit(nr)
int16 nr;
{
  ovlexit(nr);
}

static bit(byte_,bit_)
char byte_;
int16 bit_;
{
  if(byte_ & 1<<bit_) return YES;
  return NO;
}
 
static cmp_grb(p1,p2)
char *p1,*p2;
{
  int16 k;
  for(k=0;k<4;k++){
    if(*p1<*p2) return YES;
    else if(*p1!=*p2) break;
    p1++;p2++;
  }
  return NO;
}

static add_btw()
{
  int16 k,vak_,bad_vak_=NO;
  double bd_;

  if(*u(3,8)>100) *u(3,8)=81;
  vak_=*u(3,8)%100;
  if(vak_==0) goto endsr;
  for(k=0;k<(sizeof dsp_vakken)/2;k++) if(dsp_vakken[k]==vak_) break;
  bad_vak_=NO; if(vak_!=9 && k>=(sizeof dsp_vakken)/2) bad_vak_=YES;
  bd_=bedrag; bk_dat=*u(4,4);
  if(vak_==59 || vak_>80) bd_=-bd_;
  btw_bdft[vak_]-=bd_;
  if(jr_typ==1){
		if(vak_==86) v86_used=YES;/* markering intrastat-creditnota */
    if(vak_==88) v88_used=YES;/* markering intrastat-creditnota */
    if(vak_==87) v87_used=YES;/* markering medecontr-creditnota */
    for(k=0;k<(sizeof vk_vakken)/2;k++) if(vak_==vk_vakken[k]) break;
    if(!sys1824 && (bad_vak_ || k<(sizeof vk_vakken)/2)){
			if(!pr_open) open_ctrl();
      prttext("Aankoopfactuur ");prtifld(fm_ou5,&stuknr,-1);
      prttext(" : Ongeldige rekening (BTW-vak) : ");
      prtfld(3,2,-1);prttext(" ");prtfld(3,3,-1);
      nextline();
    }
  }
  else if(jr_typ==2){
    for(k=0;k<(sizeof ak_vakken)/2;k++) if(vak_==ak_vakken[k]) break;
    if(!sys1824 && (bad_vak_ || k<(sizeof ak_vakken)/2)){
			if(!pr_open) open_ctrl();
      prttext("Verkoopfactuur ");prtifld(fm_ou5,&stuknr,-1);
      prttext(" : Ongeldige rekening (BTW-vak): ");
      prtfld(3,2,-1);prttext(" ");prtfld(3,3,-1);
      nextline();
    }
  }
  endsr:;
}
 
static end_btw(det_mode_)/* YES = detail van vak drukken */
{/* btw_bdft bevat btw tabel van deze factuur of financiele lijn */
  int16 j,k;/* overboeken naar btw_bdjr en btw_bdt*/
  float bpct_;
  double bd_=0,bd818283,goed_,btw_,btw1_;

  btw_bdft[0]+=btw_bdft[9];btw_bdft[9]=0;
  for(k=0;k<100;k++) bd_+=btw_bdft[k];
  bd818283=btw_bdft[81]+btw_bdft[82]+btw_bdft[83];
  if(bd_<0 && jr_typ<=2){
/* creditnota verkopen */
    for(k=0;k<4;k++) if(btw_bdft[k]>0) break; if(k>=4) goto exec_CN;
    goed_=0;for(k=0;k<4;k++) goed_-=btw_bdft[k];
    btw_=round((double)(goed_*max_btw/100.)); btw1_=-btw_bdft[54];
    if((btw1_-btw_)<60 && btw1_<(btw_*0.05)) goto exec_CN;/* onder foutmarge */
    for(k=0;k<4;k++){
      if(btw_bdft[k]<0){
				bpct_=0;for(j=0;j<5;j++) if(btwvaknr[j]==k) {bpct_=vak_pct[j];break;}
				btw_=round((double)(btw_bdft[k]*bpct_/100.));
				btw_bdft[49]+=-btw_bdft[k];btw_bdft[k]=0;
				btw_bdft[54]+=-btw_; btw_bdft[64]+=-btw_;
      }
    }
    if(!sys1824){
			if(!pr_open) open_ctrl();
      prttext("Waarschuwing : verkoop-creditnota ");prtifld(fm_ou5,&stuknr,-1);
      prttext(" : gedeeltelijk als factuur en als creditnota verwerkt.");
      nextline();
      prttext("-----------------------------------------");nextline();
    }
    goto cn_OK;
    exec_CN:;
    btw_bdft[48]-=btw_bdft[46];btw_bdft[46]=0;
    btw_bdft[48]-=btw_bdft[44];btw_bdft[44]=0;
    for(k=0;k<=8;k++) {btw_bdft[49]-=btw_bdft[k];btw_bdft[k]=0;}
    btw_bdft[49]-=btw_bdft[45];btw_bdft[45]=0;
    btw_bdft[49]-=btw_bdft[47];btw_bdft[47]=0;
    btw_bdft[64]-=btw_bdft[54];btw_bdft[54]=0;
    btw_bdft[64]-=btw_bdft[58];btw_bdft[58]=0;
    cn_OK:;
/* creditnota aankopen */
    if(!is_nul(btw_bdft[86]) || !is_nul(btw_bdft[88]) || v86_used  || v88_used) btw_bdft[84]-=bd818283;
    else btw_bdft[85]-=bd818283;
    btw_bdft[63]-=btw_bdft[59];btw_bdft[59]=0;
  }
  if(!is_nul(btw_bdft[86])  || !is_nul(btw_bdft[88]) || v86_used || v88_used){
    if(is_nul(btw_bdft[88]) && v88_used==NO){/* indien GEEN 88, dan alles in 86 */
      btw_bdft[55]-=btw_bdft[86];
      btw_bdft[86]=bd818283;
      if(btw_bdft[55]>0 && btw_bdft[55]>btw_bdft[59]) btw_bdft[86]-=btw_bdft[55]-btw_bdft[59];
    }
    else{
      btw_bdft[55]-=btw_bdft[88];
      btw_bdft[88]=bd818283;
      if(btw_bdft[55]>0 && btw_bdft[55]>btw_bdft[59]) btw_bdft[88]-=btw_bdft[55]-btw_bdft[59];
    }
  }
  if(!is_nul(btw_bdft[87]) || v87_used){
    btw_bdft[56]-=btw_bdft[87];
    btw_bdft[87]=bd818283;
    if(btw_bdft[56]>0 && btw_bdft[56]>btw_bdft[59]) btw_bdft[87]-=btw_bdft[56]-btw_bdft[59];
  }
  if(det_mode_){
    if(btw_bdft[inq_vak]){
      cum_vbd+=btw_bdft[inq_vak];
      for(k=0;k<20;k++) prtinfo(k,0);nextline();
    }
  }
  else{
    if(!sys1824) chk_btw(YES);
    for(k=0;k<100;k++){btw_bdjr[k]+=btw_bdft[k];btw_bdt[k]+=btw_bdft[k];}
  }
  zeros((char *)btw_bdft,sizeof btw_bdft); v86_used=NO; v87_used=NO; v88_used=NO;
}

static chk_btw(p_det_)/* controle BTW-aangifte */
flag p_det_;
{
  int16 k,key_mode_,jr_;
  uint16 mast_[10],slave_[10],error_;
	char str_[20];
  long rec4_;
  float bpct_;
  double bd_,max_dif_;
/* goto endsr; */
 // if(pr_open==NO) open_ctrl();
  error_=NO;
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=1; mast_[1]=2; mast_[2]=3;
  slave_[0]=54;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle A */
  if(exist_vak(slave_,mast_)) error_=YES;/* controle B */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=55;
  slave_[0]=81;slave_[1]=82;slave_[2]=83;slave_[3]=84;slave_[4]=86;slave_[5]=88;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle C.1 */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=55;
  slave_[0]=84;slave_[1]=86; slave_[2]=88;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle C.2 */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=56;
  slave_[0]=81;slave_[1]=82;slave_[2]=83;slave_[3]=85;slave_[4]=87;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle D.1 */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=56;
  slave_[0]=85;slave_[1]=87;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle D.2 */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=59;
  slave_[0]=81;slave_[1]=82;slave_[2]=83;slave_[3]=84;slave_[4]=85;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle F */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=63;
  slave_[0]=85;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle G */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=64;
  slave_[0]=49;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle H */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=87;
  slave_[0]=56;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle I */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=86; mast_[1]=87;mast_[2]=88;
  slave_[0]=81;slave_[1]=82;slave_[2]=83;
  if(exist_vak(mast_,slave_)) error_=YES;/* controle K */
/* controle O */
  bpct_=0;for(k=0;k<5;k++) if(btwvaknr[k]==1) {bpct_=vak_pct[k];break;}
  bd_=round((double)(btw_bdft[1]*bpct_/100.));
  bpct_=0;for(k=0;k<5;k++) if(btwvaknr[k]==2) {bpct_=vak_pct[k];break;}
  bd_+=round((double)(btw_bdft[2]*bpct_/100.));
  bpct_=0;for(k=0;k<5;k++) if(btwvaknr[k]==3) {bpct_=vak_pct[k];break;}
  bd_+=round((double)(btw_bdft[3]*bpct_/100.));
  max_dif_=round(bd_*0.05); if(max_dif_<0) max_dif_=-max_dif_;if(max_dif_>max_afw) max_dif_=max_afw;
  if(btw_bdft[54]<(bd_-max_dif_) || btw_bdft[54]>(bd_+max_dif_)){
		if(!pr_open) open_ctrl();
    prttext("De berekende BTW op vakken 01+02+03 wijkt meer af dan 5% of 60 EUR van de aangegeven BTW in vak 54");
    nextline();
    error_=YES;
  }
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=55;
  slave_[0]=84;slave_[1]=86; slave_[2]=88;
  if(maxb_vak(mast_,slave_)) error_=YES;/* controle P */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=56;
  slave_[0]=85;slave_[1]=87;
  if(maxb_vak(mast_,slave_)) error_=YES;/* controle Q */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=59;
  slave_[0]=81;slave_[1]=82;slave_[2]=83;slave_[3]=84;slave_[4]=85;
  if(maxb_vak(mast_,slave_)) error_=YES;/* controle S */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=63;
  slave_[0]=85;
  if(maxb_vak(mast_,slave_)) error_=YES;/* controle T */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=64;
  slave_[0]=49;
  if(maxb_vak(mast_,slave_)) error_=YES;/* controle U */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=56;
  slave_[0]=85;slave_[1]=87;
  if(maxb_vak(mast_,slave_)) error_=YES;/* controle V */
  zeros((char *)mast_,sizeof mast_);zeros((char *)slave_,sizeof slave_);
  mast_[0]=55;mast_[1]=56;
  slave_[0]=84;slave_[1]=85;slave_[2]=86;slave_[3]=87;slave_[4]=88;
  if(maxb_vak(mast_,slave_)) error_=YES;/* controle W */
  if(p_det_==NO){
    if(kwart>1){
			if(!pr_open) open_ctrl();
      prttext("BTW-periode in parameters is fout !!!");nextline();
      error_=YES;
    }
	  if(firma[222]=='\0'){
			if(!pr_open) open_ctrl();
      prttext("Email-adres is NIET ingevuld in de parameters (+.1) !!!");nextline();
      error_=YES;
    }
		zero(str_,sizeof str_);  btw_deco(&str_[0],(long *)&firmbtwn,0);
    bd_=firmbtwn;
    if(firmbtwn==0 || (str_[0]!='0' && str_[0]!='1') /* bd_<100000000 */) {
			if(!pr_open) open_ctrl();
      prttext("BTW-nummer in parameters is fout of niet ingevuld !!!");nextline();
      error_=YES;
    }
    for(k=0;k<100;k++){
      if(btw_bdft[k]<0){
				if(!pr_open) open_ctrl();
				prttext("Het bedrag (");prtifld(fm_od8_2,&btw_bdft[k],-1);
				prttext(") in vak ");prtifld(fm_uu2_,&k,-1);prttext(" is negatief!");
				nextline();error_=YES;
      }
    }
  }
  if(error_){
    err_found=YES;
    if(p_det_){/* detail boekingen printen */
      jr_=*ps_4_2;
      rec4_=val4_1(); fasinit(4);*ps_4_2=nr_journ;*u(4,3)=stuknr;
      key_mode_=1;
      FOREVER{
	next:;
				if(faskeyi(4,1,key_mode_)) break;key_mode_=2;
				if((*ps_4_2>jr_end) || (*ps_4_2==jr_end && *u(4,3)>volg_end)) break;
				if(max_jrnl && *ps_4_2>max_jrnl) break;/* limiet journaal  */
				if((*u(4,4)<dt_beg || *u(4,4)>dt_end)) goto next;
				if(fldlen(4,19) && ((sub_mask & *l(4,19))==0)) goto next;
				if(is_openjnl((int16)(*ps_4_2))) goto next;     /* geen openingsjournaal */
				if(*ps_4_2!=nr_journ || *u(4,3)!=stuknr) break;
				fasinit(1);fasinit(2);fasinit(3); bd_deb=0;bd_cre=0;
				if(*d(4,32)<0) bd_cre=-*d(4,32); else bd_deb=*d(4,32);
				bk_dat=*u(4,4);
				makename();
				for(k=1;k<20;k++) prtinfo(k,0); nextline();
			}
			fasinit(4);chg4_1(rec4_);fasgeti(4);
			*ps_4_2=jr_;
			prttext("-----------------------------------------");nextline();
		}
		else {
			nextline();
			prttext("***   Deze fouten werden gevonden over TOTALE BTW-aangifte   ***");nextline();
			prttext("<eb> Stuur deze aangifte NIET op, want ze wordt NIET aanvaard !<eb>");nextline();
		}
	}
  endsr:;
}

static exist_vak(pmast_,pslave_)
uint16 *pmast_,*pslave_;/* elk een array van max 10 elementen */
{
  int16 k;
  flag ok1_,ok2_;

  ok1_=NO;
  for(k=0;k<10;k++){
    if(pmast_[k]==0) break;
    if(!is_nul(btw_bdft[pmast_[k]])){ok1_=YES; break;}
  }
  if(ok1_==NO) return NO;
  ok2_=NO;
  for(k=0;k<10;k++){
    if(pslave_[k]==0) break;
    if(!is_nul(btw_bdft[pslave_[k]])){ok2_=YES; break;}
  }
  if(ok2_==YES) return NO;
	if(!pr_open) open_ctrl();
  prttext("Er is BTW ingevuld in");
  for(k=0;k<10;k++){
   if(pmast_[k]==0) break;
   prttext(" ");prtifld(fm_uu2_,&pmast_[k],-1);
  }
  prttext(" en geen goederen/kosten in");
  for(k=0;k<10;k++){
   if(pslave_[k]==0) break;
   prttext(" ");prtifld(fm_uu2_,&pslave_[k],-1);
  }
  nextline();
  return YES;
}

static maxb_vak(pmast_,pslave_)
uint16 *pmast_,*pslave_;/* elk een array van max 10 elementen */
{/* som van pmast moet kleiner zijn dan max.btw op som van pslave*/
  int16 k;
  double bdm_,bds_,max_dif_;
									
  bdm_=0;
  for(k=0;k<10;k++){
    if(pmast_[k]==0) break;
    bdm_+=btw_bdft[pmast_[k]];
  }
  if(is_nul(bdm_)) return NO;/* indien geen masterbedrag dan OK */
  bds_=0;
  for(k=0;k<10;k++){
    if(pslave_[k]==0) break;
    bds_+=btw_bdft[pslave_[k]];
  }
  bds_=round(bds_*max_btw/100.);
  max_dif_=round(bds_*0.05); if(max_dif_>max_afw) max_dif_=max_afw;
  if(bdm_>(bds_+max_dif_)){
/* tolerantie van 5% of 60 eur */
		if(!pr_open) open_ctrl();
    prttext("De BTW (vak ");
    for(k=0;k<10;k++){
      if(pmast_[k]==0) break;
      if(k) prttext("+");prtifld(fm_uu2_,&pmast_[k],-1);
    }
    prttext(") is 5% of 60 EUR hoger dan ");
    prtifld(fm_uf21_,&max_btw,-1);prttext("% van goederen/kosten (vak ");
    for(k=0;k<10;k++){
      if(pslave_[k]==0) break;
      if(k) prttext("+");prtifld(fm_uu2_,&pslave_[k],-1);
    }
    prttext(")");
    nextline();
    return YES;
  }
  return NO;
}


static prt_btw(mode_)
flag mode_;
{
  int16 k;

  if(mode_) for(k=0;k<100;k++) btw_bdjr[k]=btw_bdt[k];
  if(btw_bdjr[61]<0) btw_bdjr[61]=-btw_bdjr[61];
  if(btw_bdjr[62]<0) btw_bdjr[62]=-btw_bdjr[62];
 
  btw_bdjr[71]=btw_bdjr[54]+btw_bdjr[55]+btw_bdjr[56]+btw_bdjr[57]+
    btw_bdjr[58]+btw_bdjr[61]+btw_bdjr[63];
  btw_bdjr[72]=btw_bdjr[59]+btw_bdjr[62]+btw_bdjr[64];
  btw_bdjr[71]-=btw_bdjr[72];
  if(btw_bdjr[71]<0){btw_bdjr[72]=-btw_bdjr[71];btw_bdjr[71]=0;}
  else btw_bdjr[72]=0;
  for(k=0;k<100;k++) btw_bdjr[k]=valu_cnv(def_munt,def_munt,btw_bdjr[k],afronding);
  for(k=0;k<100;k++) btw_bdft[k]=btw_bdjr[k];/* nodig voor controle */
  if(!sys1824) chk_btw(NO);/* totale controle */
  if(pr_open) {prtform(0);prtclose();pr_open=NO;}/* printer closen */
  if(sel_lst->rapport==0){
    if(dsp_btw()) goto endsr;
  }
  for(k=0;k<100;k++) btw_bdft[k]=btw_bdjr[k];/* nodig voor controle */
  if(vak_modified && !sys1824) chk_btw(NO);/* totale controle */
  if(pr_open) {prtform(0);prtclose();pr_open=NO;}
  prt_lbtw();/* lijst voor manuele invulling */
  fasclos(-2);
  if(pr_open) {prtform(0);prtclose();pr_open=NO;}
  endsr:;
}

static dsp_btw()
{
  int16 z,k,key,curs=-1;
  double bd1_,bd2_;

  vak_modified=NO;
  FOREVER{
    redo:;
    scrnum=0;scrget(1,219);z=1;
    if(vak_modified) scrifld(z++,fm_os12," AANGEPAST !");
    else z++;
    for(k=0;k<(sizeof dsp_vakken)/2;k++){
      scrifld(z++,fm_ou2_,&dsp_vakken[k]);
      scrifld(z++,fm_ud8_2,&btw_bdjr[dsp_vakken[k]]);
      if(btw_bdjr[dsp_vakken[k]]<0) scrchat(z-1,0x03);
    }
    scrifld(z++,fm_od8_2,&btw_bdjr[71]);
    scrifld(z++,fm_od8_2,&btw_bdjr[72]);
    if(err_found) scrifld(z++,fm_os70," Er zijn fouten gevonden in de aangifte, gelieve deze op te lossen !!!");
    else z++;
    if(btw_bdjr[44] || btw_bdjr[46]) scrifld(z++,fm_os70," Export EU (46) : vergeet niet de INTRACOMM. OPGAVE in te dienen !!!");
    else z++;
    key=scrupd(curs,0x3E1);curs=-1;
    if(key==101) return YES;
    if(key==109){
      prt_vdet(); key=106;
    }
    if(key==106) for(k=0;k<100;k++) btw_bdjr[k]=btw_bdt[k];
    btw_bdjr[71]=btw_bdjr[54]+btw_bdjr[55]+btw_bdjr[56]+btw_bdjr[57]+
      btw_bdjr[58]+btw_bdjr[61]+btw_bdjr[63];
    btw_bdjr[72]=btw_bdjr[59]+btw_bdjr[62]+btw_bdjr[64];
    btw_bdjr[71]-=btw_bdjr[72];
    if(btw_bdjr[71]<0){btw_bdjr[72]=-btw_bdjr[71];btw_bdjr[71]=0;}
    else btw_bdjr[72]=0;
    for(k=0;k<100;k++) btw_bdjr[k]=valu_cnv(def_munt,def_munt,btw_bdjr[k],afronding);
    if(key==110){
      if(curs==-1) curs=1; else curs=-1;
    }
    vak_modified=NO;
    for(k=0;k<100;k++) {
      if(k==71 || k==72) continue;
      bd1_=valu_cnv(def_munt,def_munt,btw_bdjr[k],afronding);
      bd2_=valu_cnv(def_munt,def_munt,btw_bdt[k],afronding);
      if(bd1_!=bd2_) break;
    }
    if(k<100) vak_modified=YES;
    if(key==108){
      if(ask_naam()){btw2xml();break;}
    }
  }
  return NO;
}
 
static prt_vdet()
{
  int16 ks,key_mode,z,key,k;
  flag first=YES;

  inq_vak=99;
  FOREVER{
    redo:;
    scrget(1,226);
    scrifld(1,fm_uu2_,&inq_vak);
    key=scrupd(1,0x81);
    if(key==101) goto endsr;
    for(k=0;k<(sizeof dsp_vakken)/2;k++) if(inq_vak==dsp_vakken[k]) break;
    if(k>=(sizeof dsp_vakken)/2){errnum=38;goto redo;}
    if(key==108) break;
  }


  if(pr_open) prtclose(); pr_open=NO;
  getsysprNew(3,form_dat,&pr_mode,&prtnr);if(sel_lst->prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) ovl_exit(10);
  free=999; pr_open=YES;


  prtfld(25,1,25);
  prttext("<t30b>Detail vak : ");prtifld(fm_uu2_,&inq_vak,-1);
  prttext("<bt50>"); prtfld(26,2,-1);
  prttext(" - "); prtfld(26,3,-1);
  prttext("<t72>Blz.<ppp>.");
  prtbuf(1); z=1;
  prtitab(z,fm_uu2,&nr_journ,3,-1); prttitle(z++,"Jr",0x13);
  prtitab(z,fm_ou5,&stuknr,3,-1); prttitle(z++,"Nr.",0x13);
  prtitab(z,fm_odat,&bk_dat,3,-1); prttitle(z++,"Datum",0x43);
  prtitab(z,fm_bdr,&btw_bdft[inq_vak],4,-1); prttitle(z++,"Bedrag",0x13);
  prtitab(z,fm_bdr,&cum_vbd,4,-1); prttitle(z++,"Cum.bedrag",0x13);
  prtbuf(3);
  p_pdfname("Detail vak BTW-aangifte",dt_beg,dt_end);
									
  scrget(1,6);scrupd(-3,0);
  sys1824=YES;/* GEEN fouten geven */
  zeros((char *)btw_bdft,sizeof btw_bdft); v86_used=NO; v87_used=NO; v88_used=NO;
  fasinit(4);stuknr=0;nr_journ=0;bk_dat=0;cum_vbd=0;
  if(jr_beg || volg_beg){*ps_4_2=jr_beg;*u(4,3)=volg_beg;}
  key_mode=1;
  FOREVER{
    ks=faskeyi(4,1,key_mode);key_mode=2;
    if((*ps_4_2>jr_end) || (*ps_4_2==jr_end && *u(4,3)>volg_end)) ks=YES;
    if(max_jrnl && *ps_4_2>max_jrnl) ks=YES;/* limiet journaal  */
    if(ks)*ps_4_2=255;
    if(!ks){
      if((*u(4,4)<dt_beg || *u(4,4)>dt_end)) goto next;
      if(fldlen(4,19) && ((sub_mask & *l(4,19))==0)) goto next;
      if(is_openjnl((int16)(*ps_4_2))) goto next;/* geen openingsjournaal */
    }
    if(*ps_4_2!=nr_journ || *u(4,3)!=stuknr){
      if(first==NO){
	end_btw(YES);
/*    if(*s(4,2)!=nr_journ) exit_jrn(); */
      }
      if(ks)break;
      if(*ps_4_2!=nr_journ) init_jrn();
      init_stk();
    }
    if(ks)break;
    add_bew();
    first=NO;
    next:;
  }
  if(cum_vbd){
    prttext("<t5b>Totaal vak ");prtifld(fm_uu2_,&inq_vak,-1);
    prttext(" : ");prtifld(fm_bdr,&cum_vbd,-1);nextline();
  }
  prtform(0);prtclose(); pr_open=NO;
  sysget(1824,2,&sys1824);/* flag herstellen */
  endsr:;
}


static prt_lbtw()/* vakken op lijst voor manuele opgave  */
{
  int16 jjjj,mm,dd,periode,jaartal;
  char str_[50];
						
  jddate(dt_end,&jjjj,&mm,&dd);
  if (kwart) periode=((mm+2)/3);
  else periode=mm;
  jaartal=jjjj;
  if(dt_aangifte==0) dt_aangifte=*u(25,2);
 
  if(pr_open) prtclose(); pr_open=NO;
  getsysprNew(3,form_dat,&pr_mode,&prtnr);if(sel_lst->prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,0))!=0) ovl_exit(10);
  free=999; pr_open=YES;
  
  p_pdfname("BTW-aangifte",dt_beg,dt_end);
 
  prtfld(25,1,30);prttext("<t40><b>B.T.W.-Aangifte<b>     ");
  prtfld(26,2,-1);prttext(" - ");prtfld(26,3,-1);
  nextline();nextline();

  prttext("Naam ... : ");prtifld(fm_os70,&firma[0],30);  nextline();
  prttext("Adres .. : ");prtifld(fm_os70,&firma[31],25);  nextline();
  prttext("Plaats . : ");prtifld(fm_os70,&firma[57],4);
  prttext(" ");prtifld(fm_os70,&firma[65],20);  nextline();
  zero(str_,sizeof str_);
  btw_deco(&str_[0],(long *)&firmbtwn,1); //str_[0]='0';stcli_d(&str_[1],(long)firmbtwn,9,0);
  prttext("BTW-nr . : ");prtifld(fm_os70,str_,15);  nextline();
  nextline();
  prttext("Periode  : ");
  zero(str_,sizeof str_);
  if(kwart){
    stcli_d(str_,(long)periode,1,1);str_[1]='/';
    stcli_d(&str_[2],(long)jjjj,4,1);
    prttext("Kwartaal ");prttext(str_);
  }
  else {
    stcli_d(str_,(long)periode,2,1);str_[2]='/';
    stcli_d(&str_[3],(long)jjjj,4,1);
    prttext("Maand ");prttext(str_);
  }
  nextline();
  prttext("Aanvraag tot terugbetaling : ");prtifld(fm_os70,&teruggave,1);nextline();
  prttext("Aanvraag betaalformulieren : ");prtifld(fm_os70,&bet_form,1);nextline();
  prttext("Naam intervat-bestand .... : ");prtifld(fm_os70,intervat.filnam,50);nextline();
  nextline();nextline();
									
  prttext("--- Uitgaande handelingen -----------------------");nextline();
  prt_lvak(0);
  prt_lvak(1);prt_lvak(2);prt_lvak(3); prt_lvak(44); prt_lvak(45); prt_lvak(46); prt_lvak(47);nextline();
  prt_lvak(48);prt_lvak(49);nextline();
  prttext("--- Inkomende handelingen -----------------------");nextline();
  prt_lvak(81); prt_lvak(82); prt_lvak(83);
  prt_lvak(84); prt_lvak(85); prt_lvak(86); prt_lvak(87); prt_lvak(88);nextline();
  prttext("--- Verschuldigde belasting ---------------------");nextline();
  prt_lvak(54); prt_lvak(55); prt_lvak(56); prt_lvak(57); prt_lvak(61);
  prt_lvak(63); prt_lvak(65); prt_lvak(101);nextline();
  prttext("--- Aftrekbare belasting ------------------------");nextline();
  prt_lvak(59); prt_lvak(62); prt_lvak(64); prt_lvak(66); prt_lvak(102);nextline();
  prttext("--- Saldo ---------------------------------------");nextline();
  prt_lvak(71); prt_lvak(72);nextline();
  prttext("--- Voorschot -----------------------------------");nextline();
  prt_lvak(91); nextline();
  prtform(0); prtclose(); pr_open=NO;
}

static prt_lvak(nr_)
int16 nr_;
{
  double bd_=0;
 
  if(nr_==101) {
    bd_=btw_bdjr[54]+btw_bdjr[55]+btw_bdjr[56]+btw_bdjr[57]+btw_bdjr[61]+btw_bdjr[63];
  }
  else if(nr_==102){
    bd_=btw_bdjr[59]+btw_bdjr[62]+btw_bdjr[64];
  }
  else if(nr_>=0 && nr_<=99){
    bd_=btw_bdjr[nr_];
  }
  prttext("<t20>");prtifld(fm_bdr,&bd_,-1);
  if(nr_==101) {
    prttext("  Subtotaal XX");
  }
  else if(nr_==102){
    prttext("  Subtotaal YY");
  }
  else if(nr_>=0 && nr_<=99){
    prttext("  Vak ");prtifld(fm_uu2_,&nr_,-1);
  }
  nextline();
}

static ask_naam()
{
  int16 curs=1,z,key,pos_;
	int16 jjjj,mm,dd,periode;
									
  if(dt_aangifte==0) dt_aangifte=*u(25,2);
	jddate(dt_end,&jjjj,&mm,&dd);
  if (kwart) periode=((mm+2)/3);
  else periode=mm;
 
  zero(intervat.filnam,sizeof intervat.filnam); pos_=0;
  // copy("BTW-",intervat.filnam,4);copy(s(25,3),&intervat.filnam[4],3);
  // copy(".XML",&intervat.filnam[7],4);

	pos_+=copy0("BTW-aangifte_",&intervat.filnam[pos_],20);
	pos_+=copy0(s(25,3),&intervat.filnam[pos_],3);
	pos_+=copy0("_",&intervat.filnam[pos_],20);
	stcli_d(&intervat.filnam[pos_],(long)jjjj,4,1);pos_+=4;
	if(kwart){
	  pos_+=copy0("-KW",&intervat.filnam[pos_],20);
		stcli_d(&intervat.filnam[pos_],(long)periode,1,0);pos_+=1;
	}
	else{
		pos_+=copy0("-",&intervat.filnam[pos_],20);
		stcli_d(&intervat.filnam[pos_],(long)periode,2,0);pos_+=2;
	}
  pos_+=copy0(".xml",&intervat.filnam[pos_],20);
  fasinit(1); 
	if (intervat.verantwoordelijke) {
		*u(1, 1) = intervat.verantwoordelijke;fasgeti(1);
	}


  FOREVER{
    redo:
    scrget(1,241);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_uJN,&teruggave);
    scrifld(z++,fm_uJN,&bet_form);
		scrifld(z++,fm_us30,&firma[222]);
    scrifld(z++,fm_os30,intervat.filnam);
		scrfld(z++,1,3);
    scrifld(z++,fm_os30,intervat.filnam);
    key=scrupd(curs,0x81);curs=1;
    if(key==101) return NO;
		if(firma[222]=='\0'){curs=4;errnum=38;goto redo;}
		if(*s(1,3)){
			if(Search(1,0)) {curs=6;goto redo;}
		} else fasinit(1);
		intervat.verantwoordelijke=*u(1,1); sysput(1729,2,&intervat.verantwoordelijke);
    if(key==108){
      fasclos(-2);
      errnum=fasopen(intervat.filnam,12);if(errnum) goto redo;
      break;
    }
  }
  return YES;
}

static btw2xml()                 /* uitschrijven in xml voor aangifte via internet */
{
  int16 jjjj,mm,dd,periode,jaartal;
  long btwnr_;
  char str_[50];
									
  jddate(dt_end,&jjjj,&mm,&dd);
  if (kwart) periode=((mm+2)/3);
  else periode=mm;
  jaartal=jjjj;
  if(dt_aangifte==0) dt_aangifte=*u(25,2);

  scrget(1,6);scrupd(-3,0);
	fasinit(80);seqo_pos=0;seqo_mode=2;pos=0;
  pos+=copy0("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>",&seqo_str[pos],100);add_eor();dmp2file();
  pos+=copy0("<ns2:VATConsignment xmlns=\"http://www.minfin.fgov.be/InputCommon\" xmlns:ns2=\"http://www.minfin.fgov.be/VATConsignment\" VATDeclarationsNbr=\"1\">",&seqo_str[pos],150); add_eor();dmp2file();

	if (intervat.verantwoordelijke) {
		fasinit(1);
		*u(1, 1) = intervat.verantwoordelijke;
		fasgeti(1);

		pos += copy0("<ns2:Representative>", &seqo_str[pos], 20); add_eor();
		zero(str_, sizeof str_);
		btwnr_ = *l(1, 10); btw_deco(&str_[0], &btwnr_, 0);
		pos += copy0("<RepresentativeID identificationType=\"NVAT\" otherQlf=\"token\" issuedBy=\"BE\">", &seqo_str[pos], 100);
		pos += copy0(str_, &seqo_str[pos], strlen(str_));
		pos += copy0("</RepresentativeID>", &seqo_str[pos], 20); add_eor();
		dmpxmlstr("Name", s(1, 3), 40);
		dmpxmlstr("Street", s(1, 4), 30);
		dmpxmlstr("PostCode", s(1, 5), 7);
		dmpxmlstr("City", s(1, 6), 25);
		dmpxmlstr("CountryCode", "BE", 2);
		dmpxmlstr("EmailAddress", s(1, 21), 40);
		dmpxmlstr("Phone", s(1, 8), 15);
		pos += copy0("</ns2:Representative>", &seqo_str[pos], 25); add_eor();
		zero(str_,sizeof str_);
    btwnr_=*l(1,10); btw_deco(&str_[0],(long *)&btwnr_,0); // str_[0]='0';stcli_d(&str_[1],btwnr_,9,0);
    stcli_d(&str_[10],(long)(jjjj%100),2,0);stcli_d(&str_[12],(long)(periode+kwart*20),2,0);
		dmpxmlstr("ns2:RepresentativeReference",str_,14);
	}
  pos+=copy0("<ns2:VATDeclaration DeclarantReference=\"",&seqo_str[pos],100);
	zero(str_,sizeof str_);
  btwnr_=firmbtwn; btw_deco(&str_[0],(long *)&btwnr_,0); // str_[0]='0';stcli_d(&str_[1],btwnr_,9,0);
  stcli_d(&str_[10],(long)(jjjj%100),2,0);stcli_d(&str_[12],(long)(periode+kwart*20),2,0);
  pos+=copy0(str_,&seqo_str[pos],14);
	pos+=copy0("\" SequenceNumber=\"1\">",&seqo_str[pos],30);add_eor();dmp2file();

  pos+=copy0("<ns2:Declarant>",&seqo_str[pos],20); add_eor();
    btwnr_=firmbtwn; btw_deco(&str_[0],(long *)&btwnr_,0); // copy("0",&str_[0],1);stcli_d(&str_[1],btwnr_,9,0);
    dmpxmlstr("VATNumber",str_,12);
    dmpxmlstr("Name",&firma[0],30);
    dmpxmlstr("Street",&firma[31],25);
    dmpxmlstr("PostCode",&firma[57],4);
    dmpxmlstr("City",&firma[65],20);
    dmpxmlstr("CountryCode","BE",2);
    dmpxmlstr("EmailAddress",&firma[222],34);
  pos+=copy0("</ns2:Declarant>",&seqo_str[pos],20); add_eor();



  pos+=copy0("<ns2:Period>",&seqo_str[pos],20); add_eor();
    if(kwart){
      stcli_d(str_,(long)periode,1,1);
      dmpxmlstr("ns2:Quarter",str_,1);
    }
    else {
      stcli_d(str_,(long)periode,2,1);
      dmpxmlstr("ns2:Month",str_,2);
    }
    stcli_d(str_,(long)jjjj,4,1);
    dmpxmlstr("ns2:Year",str_,4);
  pos+=copy0("</ns2:Period>",&seqo_str[pos],20); add_eor();
  dmp2file();

  pos+=copy0("<ns2:Data>",&seqo_str[pos],20); add_eor();
    vak2xml(0);vak2xml(1); vak2xml(2); vak2xml(3);
    vak2xml(44); vak2xml(45); vak2xml(46); vak2xml(47); vak2xml(48);  vak2xml(49);
    vak2xml(54); vak2xml(55);  vak2xml(56);  vak2xml(57);  vak2xml(59);
    vak2xml(61); vak2xml(62);  vak2xml(63);  vak2xml(64);
    vak2xml(71); vak2xml(72);
    vak2xml(81);vak2xml(82);vak2xml(83);vak2xml(84);
    vak2xml(85);vak2xml(86);vak2xml(87);vak2xml(88);
    vak2xml(91);
  pos+=copy0("</ns2:Data>",&seqo_str[pos],20); add_eor();
  dmp2file();

  pos+=copy0("<ns2:ClientListingNihil>",&seqo_str[pos],30);
  if(nihil_blst=='J') pos+=copy0("YES",&seqo_str[pos],5);
  else pos+=copy0("NO",&seqo_str[pos],5);
  pos+=copy0("</ns2:ClientListingNihil>",&seqo_str[pos],30);
  add_eor();dmp2file();

  pos+=copy0("<ns2:Ask Restitution=\"",&seqo_str[pos],30);
  if(teruggave=='J') pos+=copy0("YES\"",&seqo_str[pos],5);
  else pos+=copy0("NO\"",&seqo_str[pos],5);
  pos+=copy0(" Payment=\"",&seqo_str[pos],20);
  if(bet_form=='J') pos+=copy0("YES\"",&seqo_str[pos],5);
  else pos+=copy0("NO\"",&seqo_str[pos],5);
  pos+=copy0("/>",&seqo_str[pos],20);
  add_eor();dmp2file();

  pos+=copy0("<ns2:Comment/>",&seqo_str[pos],20);add_eor();dmp2file();
  pos+=copy0("</ns2:VATDeclaration>",&seqo_str[pos],30);add_eor();dmp2file();
  pos+=copy0("</ns2:VATConsignment>",&seqo_str[pos],30);add_eor();dmp2file();


  fasclos(-2);
  endsr:;
}
 
static vak2xml(nr_)
int16 nr_;
{
  int16 k;
	double bd_,bd1_,bd2_;
  long lbd1_,lbd2_;
  char str_[15],strnr_[4];
 
  if(nr_<0) goto endsr;
  if((nr_!=71 || !is_nul(btw_bdjr[72])) && is_nul(btw_bdjr[nr_])) goto endsr;
 
  bd_=btw_bdjr[nr_]; if(bd_<0) bd_=-bd_;/* altijd positief */

  zero(strnr_,sizeof strnr_);
  pos+=copy0("<ns2:Amount GridNumber=\"",&seqo_str[pos],30); 
  if(nr_<10) stcli_d(&str_[0],(long)nr_,1,0);
  else stcli_d(&str_[0],(long)nr_,2,0);
  pos+=copy0(str_,&seqo_str[pos],2); pos+=copy0("\">",&seqo_str[pos],2); 


  zero(str_,sizeof str_);
  bd1_=(long)(bd_);
  bd2_=(long)((bd_-bd1_)*(double)(100.) +(double).49);
  lbd1_=(long)(bd1_+.49); lbd2_=(long)(bd2_+.49);
  stcli_d(str_,lbd1_,8,1);str_[8]='.'; stcli_d(&str_[9],lbd2_,2,0);
	for(k=0;k<10;k++) if(str_[k]!=' ') break;
  pos+=copy0(&str_[k],&seqo_str[pos],12-k); pos+=copy0("</ns2:Amount>",&seqo_str[pos],30); 
  add_eor();dmp2file();
  endsr:;
}

static dmpxmlstr(xname_,ps_,maxlen_)
char *xname_,*ps_;
int16 maxlen_;
{
  int16 k,len_,slen_,nm_beg_,ps_beg_;

  nm_beg_=-1;
  for(len_=0;len_<30;len_++){
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
  add_eor();
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

static add_eor()
{
  seqo_str[pos++]=0x0D;
  seqo_str[pos++]=0x0A;
}
 
static bd2str(ps_,bd_)
char *ps_;
double bd_;
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
  len_=8;
  stcli_d(ps_,val1_,len_,1);
  if(negat_){/* negatief getal */
    for(k=0;k<len_;k++) if(*(ps_+k)!=' ') break;
    if(k>0) *(ps_+k-1)='-';
  }
  *(ps_+len_)=',';
  stcli_d(ps_+len_+1,val_,2,0);
}

static ctrl2str(ps_,bd_)
char *ps_;
double bd_;
{
  char str_[20];
  double bd1_,bd2_;
  long lbd1_,lbd2_;
								
  bd2_=bd_/1000000;
  bd1_=(long)(bd_/1000000);
  bd2_=(long)((bd2_-bd1_)*(double)(1000000.) +(double).49);
  lbd1_=(long)(bd1_+.49); lbd2_=(long)(bd2_+.49);
  copy("          ",str_,10);
  stcli_d(&str_[6],(long)lbd1_,6,1);
  if(lbd1_) stcli_d(&str_[12],(long)lbd2_,6,0);
  else stcli_d(&str_[6],(long)lbd2_,6,1);
  copy(str_,ps_,18);
}

static double round(value_)
double value_;
{
  double bd_;
						
  bd_=valu_cnv(def_munt,def_munt,value_,afronding);
  return (double)(bd_);
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

static nextline()
{
  free=prtline();
}
 
static zeros(pd,len)
char *pd;
uint16 len;
{
  while(len--) *pd++='\0';
}
 
static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

static is_openjnl(jn_)
int16 jn_;
{
  int16 k;
 
  for(k=0;k<80;k++){
    if(j_tab[k].nr==jn_){
      if(j_tab[k].typ==8) return YES; else return NO;
    }
  }
  return NO;
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
 
