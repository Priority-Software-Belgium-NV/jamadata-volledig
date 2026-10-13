/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0292GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0292dat
#define ovlcod DRK0292cod
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

char ovldat[] = "drk0292  00:02 05/11/10 (c) Jamadata";
/* aanpassen blokjes */
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_TB          200
#define MAXFLD          100

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
static float calc_pnt();
extern double *d();
static double round();
static char *p_data,pos2byte();
static long *pl_80_1;

extern int16 retcall,parmcall[8];
extern uint16 procid;
extern char info[];
 
static int16 stu=6,free;
static int16 lvcd,klcd;
static float btw_pct[8];

static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us8[]   = {7,0xC8,8,0,0,0,0};
static char fm_us5[]   = {7,0xC8,5,0,0,0,0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ou5[]   = {6,0x91,5,0,0x60,0};
static char fm_ou3[]   = {6,0x91,3,0,0x60,0};
static char fm_uu3[]   = {6,0xD1,3,0,0x60,0};
static char fm_uu3_[]   = {6,0xD1,3,0,0x00,0};
static char fm_uu2[]   = {6,0xD1,2,0,0x60,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf3_1[] = {6,0xD4,3,1,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_of4_1[] = {6,0x94,3,1,0x60,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,1,0,'A','A','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_udat[]  = {4,0xC0,1,'/'};

static char vptekst[100],stuksprx[10];
static float net_winst[10];

static char KASSAfas2sif[32]  = {160,133,131,132,135,130,138,136,137,161,141,140,    // enkel gebruiken voor kassa!
		   139,162,149,147,148,163,151,150,129,154,248,21,
		   254,27,26,24,25,0,0,128};
		
static char seqo_str[500],sys3896[6];
static char filnam[40],oldnm[50],hpos[5],npos[5],*ps_53_2;
static char stubuf[2][150],fmt[40];
static char markpos[5],*ps_6_3,sys3956,sys3957;
static long seqo_pos,value;
static int16 stu6_len,seqo_len,seqo_mode,pos,h_off,curs_pos[5],k_level;
static uint16 dat_beg,dat_end,sys3772;
static flag sys3894,sys3618,init_scr;
static flag chk_btoeg=NO,arcd=YES;
static flag sear_stt,sys3876,sys4124,sys3652;
static float sys3614,*pf_6_28;
static int16 def_taal,len6_2,curspos;


static struct{
  char omschr[4][8];
  char o_code[8];
  uint16 rec_6;
  uint16 rec_53;
} tbu[8][6];

static char df_bpmode,df_fpmode;
static float df_bpval,df_fpval,df_pafr;
static int16 tb_ktypes[6],max_kprx;
									
static struct{
  float kas_prx[6];
  float bak_punt;
  float stk_punt;
  char  promocode;
  char promotekst[30];
  uint16 promoflag;                              /* 0=geen promo, 1=promo */
} tba;


// Werking : op s(53,2) zit de positie van het blokje. Dit is 4 bytes (1 per niveau).
//           De byte bestaat uit verticaal+1/horzontaal+1 vb 0x28 --> 2-de rij, 8-ste blokje (dus vanaf 1 tellen!)
//           De 4-de byte is het blokje, de linkse zijn de hogerliggende blokjes 
// vb 00 00 53 21 : scherm 1 : menublokje rij 5, kol 3 - en dan scherm 2 blokje rij 2 kol 1
//       --> dus hoe dieper hoe minder nullen links



ovlcod()
{
  initload();
	fasunlck(-1);
//  ConLook(1);
  upd_keys();
  fasinfo(53,101); fasflush(0);
//  ConLook(0);
  ovlexit(-1);
}

static upd_keys()
{
  int16 k;

  zeros(hpos,sizeof hpos);	hpos[3]=0x11;
  zeros(markpos,5); for(k=0;k<5;k++) curs_pos[k]=1; k_level=0;
  FOREVER{
    load_keys();
    copy(hpos,npos,5);
    h_off=0; if(hpos[0]==0 && hpos[1]==0 && hpos[2]==0) h_off=5;
    dsp_keys();
    write_keys();
    if(npos[4]==1) break;
    copy(npos,hpos,5);
  }
  if(sys4124){
    if(scr_ok("Wenst U de Key-Conen uit te schrijven voor de kassa ???")){
			fasunlck(-2);
      dump_keys();
			fasunlck(-1);
		}
  }
}
 
static load_keys()
{
  int16 mode_,h_,v_;
  char byte_;
 
  zeros((char *)&tbu[0][0].omschr[0][0],sizeof tbu);
  fasinit(53);copy(hpos,ps_53_2,4);mode_=1;
  FOREVER{
    if(faskeyi(53,1,mode_)) break;mode_=2;
    if(cmp_str(ps_53_2,hpos,3)) break;
    byte_=*(ps_53_2+3);
    h_=(byte_ & 0x0F)-1;v_=((byte_ & 0xF0)>>4)-1;
    if((h_>=0 && h_<8) && (v_>=0 && v_<6)){
      copy(s(53,6),(char *)&tbu[h_][v_].omschr[0][0],32);
      copy(s(53,6),(char *)&tbu[h_][v_].o_code[0],8);
      tbu[h_][v_].rec_6=*u(53,10);
      if(tbu[h_][v_].rec_6) {/* indien code veranderd is, nieuwe code nemen */
				fasinit(6);*u(6,1)=tbu[h_][v_].rec_6;fasgeti(6);
				copy(s(6,2),(char *)&tbu[h_][v_].o_code[0],len6_2);
				copy(s(6,2),(char *)&tbu[h_][v_].omschr[0][0],len6_2);
      }
      tbu[h_][v_].rec_53=*u(53,1);
    }
  }
}
 
static dsp_keys()
{
  int16 curs=1,j,k,key,z,mask,h_,v_,n,max_h_,max_v_,min_h_,min_v_;
  char *ps_,pos_[5],*p_fmt_;
								
  max_h_=99;max_v_=99; zero(pos_,sizeof pos_);
  if(sys3956){
    max_h_=(sys3956 & 0x0F)-1;max_v_=((sys3956 & 0xF0)>>4)-1;
  }
  min_h_=-1;min_v_=-1;
  if(sys3957){
    for(k=0;k<3;k++) if(hpos[k] && hpos[k]>sys3957) break;
    if(k<3 && hpos[k]<sys3957) k=3;
    if(k>=3){
      min_h_=(sys3957 & 0x0F)-1;min_v_=((sys3957 & 0xF0)>>4)-1;
    }
  }
  init_scr=YES;curs=curs_pos[k_level];
  FOREVER{
    redo:;
    if(init_scr){
      scraddf(-1,0,0,0);z=1;
      for(k=h_off;k<8;k++){
				for(j=0;j<24;j++){
					if(j%4) mask=0x6;
					else mask=0x2;
					if((j/4)>=max_v_ && (k-h_off)>=max_h_) mask&=0xFD;
					if((j/4)<=min_v_ && (k-h_off)<=min_h_) mask&=0xFD;
					scraddf(z++,j,k*10,mask);
				}
      }
      init_scr=NO;
    }
    z=1;  copy(hpos,pos_,5);
    for(k=0;k<8-h_off;k++){
      for(j=0;j<6;j++){
				for(n=0;n<4;n++){
					if(j>=max_v_ && k>=max_h_) p_fmt_=fm_os8;
					else p_fmt_=fm_us8;
					if(n==1 || n==2) scrifld(z,p_fmt_,tbu[k][j].omschr[n]);
					else scrifld(-z,p_fmt_,tbu[k][j].omschr[n]);
					pos_[3]=pos2byte(k,j);
					if(n==0) mask=0x2; 
					else { 
						mask=0x6; 
						if(tbu[k][j].omschr[0][0]=='*') mask=0x9;
						else if(tbu[k][j].omschr[0][0]) mask=0xA; // else mask=0xA; 
					}
					if(j>=max_v_ && k>=max_h_) mask&=0xFD;
					if(j<=min_v_ && k<=min_h_) mask&=0xFD;
					if(cmp_str(markpos,pos_,4)==0){mask|=4; scrchat(z,mask);}
					else scrchat(z,mask);
					z++;
				}
      }
    }
    key=scrupd(curs,0x8AED); curs=fldcurs;curspos=fldcurs;
    h_=(curspos-1)/24; v_=(curspos-1-(h_*24)) /4;
    ps_=tbu[h_][v_].omschr[0];
    if(key==12){/* vorige key */
      h_--;
      if(h_<0) {v_--;h_=8-h_off-1;}
      if(v_<0) v_=5;
      curs=h_*24+v_*4+1;goto redo;
    }
    if(key==13){/* volgende key */
      h_++;
      if(h_>=8-h_off) {v_++;h_=0;}
      if(v_>=6 || v_>=max_v_) v_=0;
      curs=h_*24+v_*4+1;goto redo;
    }
    if(key==18){
      j=(curspos-1-(h_*24))%4;
      ps_=&tbu[h_][v_].omschr[0][0];
      if(j==0){/* auto-enter op artikelcode */
	curs=chk_keys(h_,v_,YES);
	if(curs) goto redo;
      }
      if(j==3){
				if((h_+1)<(8-h_off)) curs=(h_+1)*24+v_*4 +1;
				else if((v_+1)<6 && (v_+1)<max_v_) curs=(v_+1)*4 +1;
				else curs=1;
      }
      else curs=curspos+1;
      goto redo;
    }
    if(key==112){
      curs=curspos;init_scr=YES;
      dsp_help();
      goto redo;
    }
 
    if(key==103){/* markeer key */
      zeros(markpos,5);
      for(k=0;k<4;k++) if(tbu[h_][v_].omschr[k][0]!='\0') break;
      if(k>=4) {errnum=38;curs=h_*24+v_*4+1;goto redo;}
      copy(hpos,markpos,5);markpos[3]=pos2byte(h_,v_);
      curs=curspos; goto redo;
    }
    if(key==106){                                             /* schrap key */
      *ps_='\0';
      curs=chk_keys(h_,v_,YES);
      if(curs) goto redo;
      zeros(ps_,32); curs=curspos;goto redo;
      pos_[3]=pos2byte(h_,v_);
      if(cmp_str(markpos,pos_,4)==0) zeros(markpos,5);
    }
    curs=chk_keys(0,0,NO);
    if(curs) goto redo;
    if(key==107){/* display artikel */
      if(tbu[h_][v_].rec_6==0){
				errnum=38;curs=h_*24+v_*4+1;goto redo;
      }
      curs=curspos;
      fasinit(6);*u(6,1)=tbu[h_][v_].rec_6;fasgeti(6);
      dsp_art();
      init_scr=YES;
      goto redo;
    }
    if(key==104){                                        /* move marked key */
      for(k=0;k<4;k++) if(tbu[h_][v_].omschr[k][0]!='\0') break;
      if(k<4) {errnum=31;curs=h_*24+v_*4+1;goto redo;}/* TO moet leeg zijn */
      for(k=0;k<4;k++) if(markpos[k]!='\0') break;/* geen markering */
      if(k>=4) {errnum=39;curs=h_*24+v_*4+1;goto redo;}
      write_keys();
      fasinit(53); pos_[3]=pos2byte(h_,v_);
			k=move_keys(0,markpos,pos_,NO,NO);
      if(k) errnum=9;
      else{
				fasinit(53); pos_[3]=pos2byte(h_,v_);
				move_keys(0,markpos,pos_,NO,YES);
				copy(pos_,markpos,4);
      }
      load_keys();
      curs=curspos;goto redo;
    }
    if(curs) goto redo;
    if(key==101) {npos[4]=1; break;}
    if(key==112) dsp_help();
    if(key==108){
      if(tbu[h_][v_].omschr[0][0]!='*'){
				errnum=34;
				curs=h_*24+v_*4+1;
				goto redo;
      }
      if(hpos[0]){curs=h_*24+v_*4+1;goto redo;}/* max 4 niveaus */
      npos[0]=hpos[1];npos[1]=hpos[2];npos[2]=pos2byte(h_,v_);
      npos[3]=0x11;npos[4]=0;
      curs_pos[k_level]=curspos;k_level++;
      break;
    }
    if(key==110){
      if(hpos[2]==0){curs=h_*24+v_*4+1;goto redo;}/* hoogste niveau */
      npos[1]=hpos[0];npos[2]=hpos[1];
      npos[3]=0x11;npos[0]=0;
      curs_pos[k_level]=1;k_level--;
      break;
    }
  }
  endsr:;
}
 
static move_keys(lev_,po_,pn_,no_more,change)
int16 change,no_more;
char *po_,*pn_;
{
  uint16 len_,rec_,mode_,stop_,n;
  char pos_[5],npos_[5],byte_,lastpos_[5];

	zero(pos_,sizeof pos_);zero(npos_,sizeof npos_);zero(lastpos_,sizeof lastpos_);
  if(lev_>3) return NO;
  rec_=*u(53,1);
  fasinit(53);copy(po_,ps_53_2,4);mode_=1;copy(ps_53_2,lastpos_,4);
  FOREVER{
		copy(lastpos_,ps_53_2,4);*u(53,1)=0;
    if(faskeyi(53,1,mode_)) break; mode_=2;
		copy(ps_53_2,lastpos_,4);
    len_=4; if(lev_) len_=3;
    if(cmp_str(po_,ps_53_2,len_)) break;
		if(*pn_==0){ // ge zit op het laagste niveau, dieper gaat niet
			if(no_more) return YES;
			copy(ps_53_2+1,pos_,3);pos_[3]=0x11;
			copy(pn_+1,npos_,3-lev_);copy(&pos_[3-lev_],&npos_[3-lev_],lev_+1);
			stop_=NO;if(*pn_) stop_=YES;
			if(move_keys(lev_+1,pos_,npos_,stop_,change)) return YES;
		}
    if(change){
      copy(ps_53_2,pos_,4);
      len_=4; if(lev_) len_=3;
      copy(pn_,ps_53_2,len_);
      for(n=0;n<4;n++){
				byte_=*(ps_53_2+n);byte_=0xFF-byte_;
				*(s(53,20)+n)=byte_;
      }
      errnum=fasupd(53);

      if(lev_==0) return NO;
      copy(pos_,ps_53_2,4);
    }
    pn_[3]=*(ps_53_2+3);
  }
  fasinit(53);*u(53,1)=rec_; if(rec_) fasgeti(53);
  return NO;
}

static dsp_help()
{
  int16 z;
 
  scrget(1,170);z=1;
  scrifld(z++,fm_os79,"             Gebruik van de toetsen");
  z++;
  scrifld(z++,fm_os79," F1   Stop");
  scrifld(z++,fm_os79," F3   Markeer de KEY-COON waarop de cursor staat, om dit later te verplaatsen.");
  scrifld(z++,fm_os79,"      Een gemarkeerde KEY-COON zal flikkeren.");
  scrifld(z++,fm_os79," F4   Verplaats de gemarkeerde KEY-COON naar de plaats waar de cursor staat.");
  scrifld(z++,fm_os79,"      De verplaatste KEY-COON blijft gemarkeerd en kan dus, door nogmaals op de");
  scrifld(z++,fm_os79,"      F4 te drukken, telkens op een andere plaats gezet worden.");
  scrifld(z++,fm_os79," F6   Schrap deze KEY-COON. Een KEY-COON kan niet gewist worden, indien er zich");
  scrifld(z++,fm_os79,"      een MENU onder bevindt. Zonodig dient U vooraf alle KEY-CONEN uit te wis-");
  scrifld(z++,fm_os79,"      sen die op dit onderliggend MENU voorkomen.");
  scrifld(z++,fm_os79," F7   Raadpleeg artikelfiche");
  scrifld(z++,fm_os79," F8   Ga naar het onderliggend MENU. Dit kan alleen zo er een '*' ingevuld is");
  scrifld(z++,fm_os79,"      als eerste teken op het PLU-nummer.");
  scrifld(z++,fm_os79," F10  Keer terug uit dit MENU naar een niveau hoger.");
  scrifld(z++,fm_os79," F12  Help (dit scherm)");
  z++;
  scrifld(z++,fm_os79," PgUp Ga naar volgende KEY-COON");
  scrifld(z++,fm_os79," PgDn Ga naar vorige KEY-COON");
  z+=3;
  scrifld(z++,fm_os79,"         Druk op F8 om terug te keren ...");
  scrupd(-1,0x81);
}
 
static dsp_art()
{
  int16 j,k,key,z,pos_1_4_;
  float bak_pr_;
				
  pos_1_4_=s(1,4)-s(1,1);
 
  fasinit(52);
  fasinit(1);*u(1,1)=*u(6,7);fasgeti(1);
  copy(s(1,1),stubuf[0],pos_1_4_);
  if(fldlen(6,101)){
    fasinit(1);*u(1,1)=*u(6,101); fasgeti(1);
    copy(s(1,1),stubuf[1],pos_1_4_);
  }
  if(*u(6,9)){*u(52,1)=*u(6,9);fasgeti(52);}
  bak_pr_=*f(6,PrNrs[tb_ktypes[0]]);
  get_prx();
  for(k=0;k<max_kprx;k++){
    *f(6,PrNrs[tb_ktypes[k]])=tba.kas_prx[k];
  }
  calcnet();
  FOREVER{
    scrnum=0;scrget(2,19); z=1;
    scrfld(z++,25,1);
    if(len6_2) scrfld(z++,6,2); else scrofld(z++,6,1,-1);
    for(k=3;k<=6;k++) scrfld(z++,6,k);
    if(tba.promoflag) scrchat(3,0x03);
    scrbfld(z++,1,1+lvcd,stubuf[0],YES);
    scrbfld(z++,1,3,stubuf[0],NO);
    scrfld(z++,6,8);
    if(fldlen(6,101)) scrbfld(z++,1,3,stubuf[1],NO);
    scrfld(-z,6,9);z++;scrofld(z++,52,14,-1);
		if(fldlen(6,103)){scrfld(z++,6,103);z++;}
    for(k=10;k<=20;k++) scrfld(z++,6,k);
    for(k=0;k<6;k++){
      if(fldlen(6,PrNrs[k])){
				scrifld(z++,fm_os6,&vptekst[k*10]);
				for(j=0;j<6;j++) if(PrNrs[tb_ktypes[j]]==PrNrs[k]) break;
				scrfld(z++,6,PrNrs[k]);
				if(j==0 && *f(6,PrNrs[k])!=bak_pr_) scrchat(z-1,0x3);
				else scrchat(z-1,0xFF);
				if((j<6) || (sys3894 & 1<<k)) scrifld(z++,fm_os5,"Incl.");
				else scrifld(z++,fm_os5,"Excl.");
				scrifld(z++,fm_of4_1,&net_winst[k]);
      }
      else for(j=0;j<4;j++) streepje(z++);
    }
    key=scrupd(-1,0x181);curspos=fldcurs;
    if(key==109) artik_bis();
    if(key==101 || key==108) break;
  }
}
 
static scrbfld(z,stu_,fld_,stubuf_,fl_output_)
int16 z,stu_,fld_;
char *stubuf_;
{
  char *pvar_,*pdum_;

  if(fieldspc(stu_,fld_,&pdum_,fmt)>0){
    if(fl_output_) fmt[1]&=0xBF;
    pvar_=stubuf_+ (s(stu_,fld_)-s(stu_,1));
    scrifld(z,fmt,pvar_);
  }
}
 
static artik_bis()
{
  int16 k,curs=3,key,z;
 
  FOREVER{
    redo_a:
    scrget(2,20); z=1;
    if(len6_2) scrofld(z++,6,2,-1); else scrofld(z++,6,1,-1);
    scrofld(z++,6,3,-1);
    for(k=27;k<=79;k++) scrfld(z++,6,k);
    for(k=81;k<101;k++) scrfld(z++,6,k);
    key=scrupd(-1,0x01E1);curs=3;curspos=fldcurs;
    if(key==106) break;
    if(key!=108 && key!=101 && key!=109) goto redo_a;
    else break;
  }
  return key;
}

static get_prx()
{
  int16 k,m,pos_;
  float add_;
 
  pos_=0;
  if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(25,2)) pos_=10;
  zero((char *)&tba.kas_prx[0],sizeof tba);
  for(k=0;k<max_kprx;k++){
    tba.kas_prx[k]=*f(6,PrNrs[tb_ktypes[k]+pos_]);
    if(tba.kas_prx[k]<0) add_=-.5; else add_=.5;
    if(!(sys3894 & (1<<tb_ktypes[k]))) tba.kas_prx[k]*=1.+ *pf_6_28/100.;
    if(tba.kas_prx[k]!=*f(6,PrNrs[tb_ktypes[k]+pos_])) tba.kas_prx[k]=round(tba.kas_prx[k]);
  }
  if(*i(6,9)==99){/* geen punten of promoties op leeggoed */
    tba.bak_punt=-1; tba.stk_punt=-1; goto endsr;
  }
  tba.bak_punt=calc_pnt(tba.kas_prx[0],df_bpmode,df_bpval);
  if(*f(6,31)>1 || tba.kas_prx[max_kprx-1]<tba.kas_prx[0]){
    tba.stk_punt=calc_pnt(tba.kas_prx[max_kprx-1],df_fpmode,df_fpval);
  }
  else {/* zoniet de bak-parameters nemen */
    tba.stk_punt=calc_pnt(tba.kas_prx[max_kprx-1],df_bpmode,df_bpval);
  }

  if(fldlen(93,1)==0){
    if(fldlen(6,74)) tba.promocode=*s(6,74);
    goto endsr;
  }
  fasinit(93);*u(93,2)=*u(6,1);
  m=get_promo(1,*u(6,1),0,0);
  if(m){/* leverancier + groep */
    m=get_promo(2,0,*u(6,7),*u(6,9));
    if(m){/* leverancier */
      m=get_promo(2,0,*u(6,7),0);
    }
    if(m){/* groep */
      m=get_promo(2,0,0,*u(6,9));
    }
  }
  if(m==0){
    for(k=0;k<max_kprx;k++){
      if(*f(93,11+k)) tba.kas_prx[k]=*f(93,11+k);
    }
    tba.promocode=*s(93,25);
    tba.bak_punt=calc_pnt(tba.kas_prx[0],*s(93,20),*f(93,21));
    tba.stk_punt=calc_pnt(tba.kas_prx[0],*s(93,22),*f(93,23));
    copy(s(93,30),tba.promotekst,fldlen(93,30));
    tba.promoflag=YES;
  }
  endsr:;
}
 
static get_promo(keynr_,arec_,lrec_,grp_)
int16 keynr_;
uint16 arec_,lrec_,grp_;
{
  int16 mode_;
						
  fasinit(93);*u(93,2)=arec_;*u(93,3)=lrec_;*u(93,4)=grp_; mode_=1;
  FOREVER{
    if(faskeyi(93,keynr_,mode_)) break; mode_=2;
    if(keynr_==1){
      if(*u(93,2)!=arec_) break;
    }
    else{
      if(*u(93,3)!=lrec_) break;
      if(*u(93,4)!=grp_) break;
    }
    if(*u(25,2)>=*u(93,7) && (*u(93,8)==0 || *u(25,2)<=*u(93,8))) return NO;
  }
  return YES;
}
 
 
static float calc_pnt(prx_,pmode_,pval_)
float prx_,pval_;
char pmode_;
{
  float val_=0,val1_;

  if(pmode_=='G') return (float)(-1);
  if(pmode_=='P') return (float)pval_;
  if(pmode_=='%'){
    val_=prx_ * (pval_/100.);
    if(df_pafr){
      val1_=(long)(val_ / df_pafr);
      val_=val1_*df_pafr;
    }
  }
  return (float)val_;
}

static calcnet()
{
  int16 j,k;
  float accijns_,net_,q_stuks;
									
  if(*f(6,18)) goto calc_wpct;
  net_=*f(6,12);
  accijns_=*f(6,30);
  net_-=accijns_;
  for(k=0;k<3;k++) if(fldlen(6,14+k)) net_*=(100.-*f(6,14+k))/100.;
  if(fldlen(6,17)) net_-=*f(6,17);
	net_+=accijns_; 
	if(sys3652){ // afhaal en losvergoeding erbij tellen 
		if(fldlen(6,19)) {
			if(sys3652==2) net_*=(100.+*f(6,19))/100.;  // als %
			else net_+=*f(6,19);
		}
		if(fldlen(6,20)) net_+=*f(6,20);
	}
  *f(6,18)=net_;
  calc_wpct:;
  for(k=0;k<6;k++){
    if(fldlen(6,PrNrs[k]) && *f(6,18)){
      q_stuks=0;
      if(stuksprx[k]=='J' && fldlen(6,31)) q_stuks=*f(6,31);
      if(q_stuks==0) q_stuks=1;
      net_=*f(6,PrNrs[k]);
      for(j=0;j<6;j++) if(PrNrs[tb_ktypes[j]]==PrNrs[k]) break;/* KASPR= incl BTW */
      if((j<6) || (sys3894 & 1<<k)) net_/=1.+*f(6,28)/100.;
      net_winst[k]=((net_-(*f(6,18)/q_stuks))/ (*f(6,18)/q_stuks)) * 100.;
    }
    else net_winst[k]=0;
  }
}

static chk_keys(hor_,vert_,mode_)
int16 hor_,vert_,mode_;
{
  int16 j,k,h_,v_,curs,end_,pos_;
  char *ps_,str_[5];

  for(h_=hor_;h_<8-h_off;h_++){
    for(v_=vert_;v_<6;v_++){
      ps_=tbu[h_][v_].omschr[0];
      if(cmp_str(ps_,tbu[h_][v_].o_code,8)){/* controle op menu's */
	if(tbu[h_][v_].o_code[0]=='*' && *ps_!='*' && hpos[0]==0){
	  fasinit(53);
	  str_[0]=hpos[1];str_[1]=hpos[2];str_[2]=pos2byte(h_,v_);
	  str_[3]=0x11;copy(str_,ps_53_2,4);
	  k=faskeyi(53,1,1);
	  if(k==0 && cmp_str(ps_53_2,str_,3)==0){
	    errnum=34;copy(tbu[h_][v_].o_code,ps_,8);
	    curs=h_*24+v_*4+1;
	    return curs;
	  }
	}
      }
      if(*ps_=='\0' || *ps_=='*'){
	copy(ps_,tbu[h_][v_].o_code,8);tbu[h_][v_].rec_6=0;
      }
      else{
				if(cmp_str(ps_,tbu[h_][v_].o_code,8)){
					init_scr=YES;
					fasinit(6);copy(ps_,s(6,3),8);
					curs=fldcurs;
					if(search(6,0)) {curs=h_*24+v_*4+1;return curs;}
					fldcurs=curs;
					copy(s(6,2),ps_,len6_2);*(ps_+len6_2)='\0';
					copy(ps_,tbu[h_][v_].o_code,8);
					tbu[h_][v_].rec_6=*u(6,1);
					ps_=tbu[h_][v_].omschr[1];
					for(k=0;k<3;k++) if(*(ps_+k*8)!='\0') break;
					if(k>=3){
						pos_=0;end_=NO;
						for(k=0;k<3;k++){
							for(j=0;j<8;j++){
								if(*(ps_6_3+pos_)=='\0') {end_=YES;break;}
								else if(*(ps_6_3+pos_)==' ') break;
								else {*(ps_+k*8+j)=*(ps_6_3+pos_);pos_++;}
								if(pos_>=fldlen(6,3)) {end_=YES;break;}
							}
							if(end_) break;
							if(j>=8){/* naar volgend woord skippen */
								while(*(ps_6_3+pos_) && *(ps_6_3+pos_)!=' ' && pos_<fldlen(6,3)){
									pos_++;
								}
							}
							while(*(ps_6_3+pos_)==' ' && pos_<fldlen(6,3)){pos_++;}/* leading blanks */
							if(*(ps_6_3+pos_)=='\0' || end_) break;
						}
					}
				}
      }
      if(mode_) goto endsr;
    }
  }
  endsr:;
  return NO;
}
 
static write_keys()
{
  char *ps_,byte_;
  int16 v_,h_,n;
							
  for(h_=0;h_<8;h_++){
    for(v_=0;v_<6;v_++){
      ps_=tbu[h_][v_].omschr[0];
      for(n=0;n<4;n++) if(tbu[h_][v_].omschr[n][0]) break;
      fasinit(53);*u(53,1)=tbu[h_][v_].rec_53;
			if(*u(53,1)) fasgeti(53);
      if(n<4){
				copy(hpos,ps_53_2,3);
				byte_=pos2byte(h_,v_); copy(&byte_,ps_53_2+3,1);
				copy((char *)&tbu[h_][v_].omschr[0][0],s(53,6),32);
				*u(53,10)=tbu[h_][v_].rec_6;
				for(n=0;n<4;n++){
					byte_=*(ps_53_2+n);byte_=0xFF-byte_;
					*(s(53,20)+n)=byte_;
				}
				if(*u(53,1)==0) errnum=fasadd(53); else fasupd(53);
      }
      else if(*u(53,1)) faskill(53);
    }
  }
}

static char pos2byte(hor_,vert_)
int16 hor_,vert_;
{
  char h_,v_,byte_;
 
  h_=hor_+1;v_=vert_+1;
  byte_=(v_<<4) | h_;
  return byte_;
}

static dump_keys()
{
  int16 mode_;
 
  scrget(1,170);
  mk_name(3902,"kasusr.dat"); fasclos(-2);
  errnum=fasopen(filnam,2);if(errnum) goto endsr;
  scrget(1,7);scrupd(-3,0);
  fasinit(80);seqo_pos=0;seqo_mode=2;
  fasinit(53);mode_=2;
  FOREVER{
    if(faskeyi(53,2,mode_)) break; mode_=2;
    copy(s(53,2),p_data,4);
 
    zeros(seqo_str,sizeof seqo_str);
    copy(s(53,7),seqo_str,24);
    copy(s(53,6),&seqo_str[24],5);pos=29;
    KASSAcnv_char();
    copy(seqo_str,p_data+4,29); seqo_len=33;
    seqo_flush();
  }
  fasclos(-2);
  endsr:;
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

static KASSAcnv_char()
{
  int16 k;
 
  for(k=0;k<pos;k++){
    if(seqo_str[k]>=0x80 && seqo_str[k]<0x80+sizeof KASSAfas2sif){
      seqo_str[k]=KASSAfas2sif[seqo_str[k]-0x80];
    }
  }
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

static nextline()
{
  free=prtline();
}

static double round(bedrag_)
double bedrag_;
{
  float add;
							
  add=sys3614;
  if(sys3618==0) add/=2.;
  add=add*.999999;
  if(sys3614>0.0001){
    bedrag_=((long)((bedrag_+add)/sys3614)) * sys3614;
  }
  return bedrag_;
}

static streepje(fldnr)
int16 fldnr;
{
  scrifld(fldnr,fm_os1,"-");
}

static initload()
{
  int16 k,nr_;
 
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(9);
  fileopen(11);
			
  sysget(1918,2,&sear_stt);
  sysget(3614,4,&sys3614);
  sysget(3618,2,&sys3618);
	sysget(3652,2,&sys3652);
  sysget(3772,2,&sys3772);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);
  sysget(3896,6,&sys3896[0]);
  sysget(3956,1,&sys3956);
  sysget(3957,1,&sys3957);
  sysget(4124,2,&sys4124);

  sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[60]);
  sysget(4670,6,stuksprx);
	sysget(4780,4,&stuksprx[6]);

  sysget(3982,1,&df_bpmode);
  sysget(3983,4,&df_bpval);
  sysget(3987,1,&df_fpmode);
  sysget(3988,4,&df_fpval);
  sysget(3992,4,&df_pafr);
  zero((char *)&tb_ktypes[0],sizeof tb_ktypes); max_kprx=0;
  for(k=0;k<6;k++){
    if(sys3896[k]){
      nr_=sys3896[k]-'0';
      if(nr_>=0 && nr_<=9 && fldlen(6,PrNrs[nr_])){
				tb_ktypes[max_kprx++]=nr_;
      }
    }
  }

  sysget(3678,2,&def_taal);

  len6_2=fldlen(6,2); if(len6_2>7) len6_2=7;
  ps_6_3=s(6,3);
  ps_53_2=s(53,2);
  pf_6_28=f(6,28);
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

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

static zeros(pd,len)
char *pd;
int16 len;
{
  int16 k;

  for(k=0;k<len;k++) *(pd+k)='\0';
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
