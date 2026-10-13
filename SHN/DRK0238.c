/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0238GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0238dat
#define ovlcod DRK0238cod
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

char ovldat[] = "drk0238  00:15 18/11/10 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
 
#define MAXRL           500
 
#define FLD_COUNT       100
#define KOL_COUNT       80
#define ROW_COUNT       25
#define DIM_QDET        19
#define LEN_PTR         2+4+4+4

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

extern char *s();
static char get_ul();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();
static double Round();

static struct {
  char title[34];
  char firma[31];
  char hoofding[81];
  uint16 date;
  uint16 q_kol;
  uint16 reclen;
  long q_rec;
  long hdr_pos;
  long idx_pos;
  long bod_pos;
  long pos_niv7;
  int16 q_nivs;
} id;

static struct {
  int16 h_pos;
  int16 blnccnt;
  int16 len;
  char *fmt;
  char *info;
  char *title;
  int16  pos_title;
  int16  blok_nr;
} *p_tab, tabel[FLD_COUNT];
static int16 tab_count;

static struct htype {
  uint16 length   :8;
  uint16 type_ex  :3;
  uint16 type     :3;
  uint16 ioclass  :2;
} *header;

static struct {
  long scr1boven;
  long scr1onder;
  long pos_hdr;
  long pos_first;
  int16 row_curs;
} niveau[8];

static struct {
  char prt;
  char newpage;
  char separate;
  char bold;
  long pos;
  long qlines;
} prt_parm[9];

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou1[]   = {6,0x90,1,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_ul8[]   = {6,0xD3,8,0,0x70,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_osdum[] = {7,0x88,255,0,0,0,0};

static char fm_string[]= {7,0x88,1,0,0,0,0};

extern char info[];extern int16 procid;

extern int16 ilength;
static int16 XlsFldNr[150],XlsStu,MaxXlsFldNr,XlsRef,XlsRij,XlsKol,Prt2Xls,XlsSkipBlancs;
static int16 *pi;
static int16 StylTotaal, StylGrpTot, StylKlasse, StylNormal, StylTitel, Styl2Use;

static int16 fil_nr,f_nr,beg_pos[ROW_COUNT],curs_row,old_row,niv_dsp,free,f_nr_sel;
static int16 prt_hpos[FLD_COUNT],prt_niv,niv_toprt,max_scr,q_statist,q_hdr_lin;
static int16 lvcd,klcd,max_hlen,bytes_ok,best_fnd;
static int16 prt2pdf,autoprint_;
static char recbuf[MAXRL],new_page='N',selbuf[81],blok_sel[10],prt_lo2hi='J',OmshrijvingNiv0[50];
static char fmt[40];
static long loffil,recnr,pos_first,pos_next,pos_head,pos_row[DIM_QDET];
static long best_pos,single_file;
static flag Rscr_exis,scr;

static struct {
  char naam[16];
  char fmt[16];
  uint16 pos;
  uint16 len;
  int16 breedte;
  int16 prt_kol;
  uint16 codebits;
  uint16 blok_nr;
} *p_fld, fld[FLD_COUNT];

ovlcod(parmval)
int16 parmval;
{
  initload();
  if(parmval==1){scr=YES; single_file=YES; exec(YES);}
  else if(parmval==2){scr=NO; autoprint_=YES; single_file=YES; exec(YES);}
  else{
    single_file=NO;
    FOREVER{
      if(exec_ask()==YES) goto endsr;
      exec(NO);
      if(!scr) break;
    }
  }
  endsr:;
  fasclos(-2);/* zeker alles closen */
  ovlexit(-1);
}

static exec(mode_)
int16 mode_;/* YES = TMPxxx.STA */
{
  char filnam[15];
  int16 k;
 
  fasunlck(-1);
	zeros((char *)fld,sizeof fld);
  zeros(recbuf,sizeof recbuf);recnr=0;
  if(mode_){
    copy("TMP",filnam,3);
    stcli_d(&filnam[3],(long)(procid),3,0);
    copy(".sta",&filnam[6],5);
  }
  else{
    stcli_d(&filnam[3],(long)(fil_nr+1),3,0);
    copy(".sta",&filnam[6],5);
    copy(s(25,3),filnam,3);
  }
  if(fasopen(filnam,1)){errnum=1;goto endsr;}
  readbytes(0L,(char *)&id,sizeof id);
  for(k=0;k<id.q_kol;k++){
    readbytes(id.hdr_pos+k*64L,(char *)&fld[k],sizeof fld[0]);
  }
  if(scr) disp(); else print(0L,id.q_rec-1,0);
  endsr:;
  fasclos(-2);
	fasunlck(0);
}

static exec_ask()
{
  int16 key,j,k,z,z_base,fil_=0,curspos_;
  uint16 dd,mm,yy,end_;
  char mode='B',filnam[25];

  redo_full:;
  scraddf(-1,0,0,0);z=1;scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0238A");
  scraddf(z++,2,20,2);
  for(k=0;k<q_statist;k++) scraddf(z++,4+k,3,0x100); // om curs hand te zetten 
  scraddf(z++,5+k,64,0);scraddf(z++,5+k,74,2);

	f_nr=z;
	k=funkdsp(0," F1 stop",23);
	k=funkdsp(k," F8 Bekijk",23);
  k=funkdsp(k," F9 Herbereken statistiek(en)",23);
  k=funkdsp(k," F10 Druk af / pdf",23);
  
  FOREVER{
    z=1;
//    scrodsp(z++,fm_os79," Raadplegen/afdrukken statistieken ");
		DisplayMenuTitel(1,"Raadplegen/afdrukken statistieken",0x3);z++;
    for(k=0;k<q_statist;k++){
      zeros(filnam,sizeof filnam);
      fasclos(-2);zeros((char *)id.title,sizeof id);
      stcli_d(&filnam[3],(long)(k+1),3,0);
      copy(".sta",&filnam[6],5);
      copy(s(25,3),filnam,3);
      if(fasopen(filnam,1)==0){
				readbytes(0L,(char *)&id,sizeof id);
      }
      end_=NO;
      for(j=0;j<55;j++){
				if(id.hoofding[j]=='\0' || end_){
					if(!end_) id.hoofding[j]=' ';
					else {
						if(id.hoofding[0]) id.hoofding[j]='.'; // alleen als er ook een statistiek is
					}
					end_=YES;
				}
      }
			if(id.date){
				jddate(id.date,&yy,&mm,&dd);
				copy(" (",&id.hoofding[55],2);
				stcli_d(&id.hoofding[57],(long)dd,2,1);id.hoofding[59]='/';
				stcli_d(&id.hoofding[60],(long)mm,2,0);id.hoofding[62]='/';
				stcli_d(&id.hoofding[63],(long)yy,4,0);
      } else copy("  /  /    ",&id.hoofding[57],11);
      copy(") : ",&id.hoofding[67],4);
      k++;stcli_d(&id.hoofding[71],(long)k,2,1);k--;
	/*
      if(id.date){
				jddate(id.date,&yy,&mm,&dd);
				stcli_d(&id.hoofding[60],(long)dd,6,1);id.hoofding[66]='/';
				stcli_d(&id.hoofding[67],(long)mm,2,0);id.hoofding[69]='/';
				stcli_d(&id.hoofding[70],(long)yy,4,0);
      } else copy("      /  /",&id.hoofding[60],11);
	*/
      scrifld(z++,fm_os79,id.hoofding);
    }
    z_base=z;
    redo:;
    z=z_base;
    scrifld(z++,fm_os79,"U kiest ? ");
    scrifld(z++,fm_uu2,&fil_);
    key=scrupd(1,0x2381);curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) return YES;
    if(key==109){
      fasclos(-2);
      if(ovltest(237)) ovlcall(237,0);
			sysget(3954,2,&q_statist);
      goto redo_full;
    }
		if(key==251){
			if(curspos_>=2 && curspos_<=q_statist+1){ fil_=curspos_-1;key=108;}
			else goto redo;
		}
    if(fil_<1){ errnum=34;goto redo;}
		scr=YES;if(key==110) scr=NO;
    fil_nr=fil_-1;
    break;
  }
  endsr:;
  return NO;
}

static scrodsp(z,fmt_,pvar_)
int16 z;
char *fmt_,*pvar_;
{
	int k;
	char newfmt_[20];
	 

	if(fmt_[1]!=0x88) scrifld(z,fmt_,pvar_); // geen output tekst 
	else {
	  copy(fmt_,newfmt_,20);
		for(k=0;k<fmt_[2];k++) if(*(pvar_+k)=='\0') break;
		newfmt_[2]=k;scrifld(z,newfmt_,pvar_);
	}
}


static disp()
{
  int16 k,j,r,key,screennr[8],rows_used,horiznr=0,q_scr,val_,pmode_=NO,low_niv_,curspos_;
  char kar_;
  uint16 action=999;
  long from_,to_;
  flag direction=NO;

  zeros((char *)&screennr[0],sizeof screennr);
  q_scr=cnt_scr();   
	readrec(0); low_niv_=*(uint16 *)&recbuf[0] & 0x07;
  old_row=-99;niv_dsp=8;curs_row=0;pos_row[0]=id.pos_niv7;goto_niv(7);
  load_tab(horiznr);
  FOREVER{
    redo:;
    if(action>=3) dsp_header();
    if(action>=2){dsp_1lin(-2,pos_head);/*screennr[niv_dsp]=0;*/}
    if(action>=1){
      pos_next=pos_first;
      if(screennr[niv_dsp]==0) niveau[niv_dsp].scr1boven=pos_first;
      if(direction==0){
				for(k=0;k<DIM_QDET;){
					dsp_1lin(k++,pos_next);
					pos_next=*(long *)&recbuf[6];
					if(screennr[niv_dsp]==0) niveau[niv_dsp].scr1onder=pos_next;
					if(pos_next==0) break;
				}
				rows_used=k;
				while(k<DIM_QDET) dsp_1lin(k++,0L);
      }
      else {
				readbytes(pos_first,recbuf,10);
				for(k=DIM_QDET-1;k>=0;k--){
					pos_first=*(long *)&recbuf[2];
					dsp_1lin(k,pos_first);
				}
				rows_used=DIM_QDET;
      }
    }
    scrifld(f_nr_sel,fm_us20,selbuf);
    if(curs_row>=rows_used) curs_row=rows_used-1;
    if(curs_row!=old_row) dsp_c_row();
    if(pmode_) {key=108;}
    else{
			if(screennr[niv_dsp]!=0) scrchat(1000+2,0); else scrchat(1000+2,1);
			if(pos_next!=0) scrchat(1000+3,0); else scrchat(1000+3,1);
			if(horiznr>0) scrchat(1000+6,0); else scrchat(1000+6,1);
			if((horiznr+1)<max_scr) scrchat(1000+7,0); else scrchat(1000+7,1);
      if (niv_dsp<7) scrchat(1000+9,0); else scrchat(1000+9,1);
      if (niv_dsp>(low_niv_+1)) scrchat(1000+10,0); else scrchat(1000+10,1);
      if (niv_dsp<7) scrchat(1000+11,0); else scrchat(1000+11,1);
      key=scrupd(1,0x63FF);action=0;direction=NO;curspos_=fldcurs;
    }
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101 || key==5001) break; // stop 
		if(key==111 || key==5011){ // hoogste niveau
      if(niv_dsp<7){action=goto_niv(7); goto redo;}
      else break;
    }
/*  if(key==101) break; */
    if(selbuf[0] && selbuf[0]!='+') {zoek();action=1;screennr[niv_dsp]=9999;goto redo;}
    else{
      switch(key){/* konversie pijltjes naar funktietoetsen */
				case  6 : key=106;break;
				case  7 : key=107;break;
				case  8 : key=104;break;
				case  9 : key=105;break;
				case 12 : key=102;break;
				case 13 : key=103;break;
				default : break;
		  }
      switch(key){
				case 10 : kar_=selbuf[0];selbuf[0]=0x1;
									zoek();action=1;screennr[niv_dsp]=9999;
									selbuf[0]=kar_;
									break;
				case 11 : kar_=selbuf[0];selbuf[0]=0xFF;
									zoek();action=1;screennr[niv_dsp]=9999;
									selbuf[0]=kar_;
									break;
				case 5004:
				case 104: if(curs_row){curs_row--;break;}
									if(screennr[niv_dsp]==0) break;
									curs_row=DIM_QDET-1;// moet nu nog 107 uitvoeren 
				case 5002: // page up
				case 102: if(screennr[niv_dsp]==0) break;
									if(niveau[niv_dsp].scr1onder==0 || pos_first<=niveau[niv_dsp].scr1onder){
										pos_first=niveau[niv_dsp].scr1boven;action=1;screennr[niv_dsp]=0;break;
									}
									direction=YES;action=1;screennr[niv_dsp]--;break;
				case 5005: 
				case 105: if(curs_row<rows_used-1){curs_row++;break;}
									if(pos_next==0) break;
									curs_row=0;// moet nu nog 108 uitvoeren 
				case 5003: // page down
				case 103: if(pos_next==0) break;
									pos_first=pos_next;action=1;screennr[niv_dsp]++;break;
				case 5006:
				case 106: if(selbuf[0]=='+') val_=q_scr; else val_=1;
									if(horiznr>=val_){horiznr-=val_;action=3;load_tab(horiznr);}
									break;
				case 5007:
				case 107: if(selbuf[0]=='+') val_=q_scr; else val_=1;
									if(horiznr+val_<max_scr){horiznr+=val_;action=3;load_tab(horiznr);}
									break;
				case 5009:
				case 109: if(niv_dsp<7) action=goto_niv(niv_dsp+1); break;
				case 5010:
				case 110: if(niv_dsp) action=goto_niv(niv_dsp-1); break;
				case 5008:
				case 108: if(single_file){
										if(pmode_==NO){
											if(niv_dsp>=7) print(0L,id.q_rec-1,0);
											else {
												action=goto_niv(niv_dsp+1);pmode_=YES;
											}
										}
										else{
											from_=pos_row[curs_row];
											FOREVER{
												readbytes(from_,recbuf,LEN_PTR);
												if(*(long *)&recbuf[10]==0) break;
												from_=*(long *)&recbuf[10];
											}
											from_=(from_-id.bod_pos)/id.reclen;
											to_=(pos_row[curs_row]-id.bod_pos)/id.reclen;
											print(from_,to_,8-niv_dsp+1);
											pmode_=NO;
										}
									}
									else{
										from_=pos_row[curs_row];
										FOREVER{
											readbytes(from_,recbuf,LEN_PTR);
											if(*(long *)&recbuf[10]==0) break;
											from_=*(long *)&recbuf[10];
										}
										from_=(from_-id.bod_pos)/id.reclen;
										to_=(pos_row[curs_row]-id.bod_pos)/id.reclen;
										print(from_,to_,8-niv_dsp+1);
									}
									action=3; break;            
          case 251:
            k=curspos_; // om value te kunnen zien in DEBUG
            j=-1;
            for (r=0; r<rows_used; r++) {
              for(k=0;k<tab_count;k++){
                if (curspos_==(beg_pos[4+r]+k)) {
                  j=curs_row=r;
                  break;
                }
              }
              if (k<tab_count) break;
            }
            if (j!=-1 && curs_row==old_row) { // double click
              if(niv_dsp) action=goto_niv(niv_dsp-1); 
            }
            else {
              for(k=0;k<tab_count;k++){
                if ((curspos_==beg_pos[2]+k)) {
                  if (niv_dsp<7) action=goto_niv(niv_dsp+1); // op bovenste lijn geclickt !
                  break;
                }
              }
            }
            break;
				default : break;
			}
	  }
	}
}

static dsp_1lin(row_,pos_)
int16 row_;
long pos_;
{
  int16 k,z,line;
  flag firsttime=NO;

  line=row_+4;
  if(beg_pos[line]==0){firsttime=YES;beg_pos[line]=f_nr;}
  z=beg_pos[line];
  if(pos_==0) zeros(recbuf,sizeof recbuf);
  else readbytes(pos_,recbuf,id.reclen);
  if(row_==old_row) old_row=-99;
  for(k=0;k<tab_count;k++){
    if(firsttime) scraddf(f_nr++,line,tabel[k].h_pos,0x100); // om curs hand te zetten !!! mvg
    scrifld(z++,tabel[k].fmt,tabel[k].info);
  }
  if(row_==curs_row) dsp_c_row();
  pos_row[row_]=pos_;
}

static dsp_c_row()
{
  int16 k;

  for(k=0;k<tab_count;k++){
    if(old_row!=-99) scrchat(beg_pos[4+old_row]+k,0);
    scrchat(beg_pos[4+curs_row]+k,8);
/*  break;       cursor alleen in linkse kolom */
  }
  old_row=curs_row;
}

static cnt_scr()
{
  int16 k,kol_start=1,stop_=NO,cnt;
									
  max_scr=1;cnt=1;
  FOREVER{
    tab_clr(); load1_tab(0);
    for(k=kol_start;k<FLD_COUNT;k++){
      if(fld[k].fmt[0]){
	load1_tab(k);
	if(tabel[tab_count].h_pos>KOL_COUNT) {break;}
	if(tab_count>2 && tabel[tab_count-1].blok_nr){
	  if(tabel[tab_count-1].blok_nr != tabel[tab_count-2].blok_nr){stop_=YES;break;}
	}
      }
    }
    if(stop_==NO) cnt++;
    if(k==FLD_COUNT) break;
    kol_start=k;max_scr++;
  }
  if(stop_==NO) return 1;
  else return cnt;
}
 
static load_tab(nr)
int16 nr;
{
  int16 j,k,kol_start=1;
 
  for(j=0;j<nr+1;j++){
    tab_clr(); load1_tab(0);
    for(k=kol_start;k<FLD_COUNT;k++){
      if(fld[k].fmt[0]){
	load1_tab(k);
	if(tabel[tab_count].h_pos>KOL_COUNT) {tab_count--; break;}
	if(tab_count>2 && tabel[tab_count-1].blok_nr){
	  if(tabel[tab_count-1].blok_nr != tabel[tab_count-2].blok_nr){tab_count--;break;}
	}
      }
    }
    kol_start=k;
  }
  Rscr_exis=YES;if(k==FLD_COUNT) Rscr_exis=NO;
}

static load1_tab(kol_)
int16 kol_;
{
  p_fld=&fld[kol_];
  tab_add(p_fld->fmt,&recbuf[p_fld->pos],p_fld->breedte,p_fld->naam,p_fld->blok_nr);
}

static tab_clr()
{
  zeros((char *)tabel,sizeof tabel);
  tab_count=0;
}

static tab_add(fmt,info,breedte,naam,blok_nr)
char *fmt,*info,*naam;
int16 breedte,blok_nr;
{
  char numerisch;
  int16 k;
 
  p_tab=&tabel[tab_count]; numerisch=NO;
  p_tab->fmt = fmt;
  p_tab->info= info;
  k=get_flen(fmt);
  if (k<0) {numerisch=YES; k=-k;}
  p_tab->len=k;
  p_tab->blnccnt =breedte-p_tab->len;
  if (p_tab->blnccnt<0) p_tab->blnccnt=0;
  p_tab->title= naam;
  p_tab->blok_nr=blok_nr;
  k=0;
  if (numerisch) {
    k=p_tab->len - get_slen(naam);
  }
  p_tab->pos_title=p_tab->h_pos+k;
  k=p_tab->h_pos+breedte; p_tab++; p_tab->h_pos=k;
  tab_count++;
}

static goto_niv(niv_)
int16 niv_;
{
  long pos_;

  if(niv_<niv_dsp){
    pos_=pos_row[curs_row];
    readbytes(pos_,recbuf,LEN_PTR);
    if(*(long *)&recbuf[10]==0) return NO;
    if(niv_dsp!=8){
      niveau[niv_dsp].pos_hdr=pos_head;
      niveau[niv_dsp].pos_first=pos_first;
      niveau[niv_dsp].row_curs=curs_row;
    }
    pos_head=pos_;
    pos_first=*(long *)&recbuf[10];
    curs_row=0;
  }
  else{
    pos_head=niveau[niv_].pos_hdr;
    pos_first=niveau[niv_].pos_first;
    curs_row=niveau[niv_].row_curs;
  }
  niv_dsp=niv_;return 2;
}

static dsp_header()
{
  int16 k;
 
  scraddf(-1,0,0,0); f_nr=1; zeros((char *)beg_pos,sizeof beg_pos);
  scraddf(f_nr,0,(80-get_slen(id.hoofding))/2,8); scrstring(f_nr++,id.hoofding);
  for(k=0;k<tab_count;k++){
    scraddf(f_nr,1,tabel[k].pos_title,3); scrstring(f_nr++,tabel[k].title);
  }

  for(k=0;k<80;k++) recbuf[k]=186;
  scraddf(f_nr,3,0,0); scrifld(f_nr++,fm_os79,recbuf);// lijn boven 
  scraddf(f_nr,23,0,0); scrifld(f_nr++,fm_os79,recbuf);// lijn onder 
	
	f_nr_sel=f_nr; scraddf(f_nr++,3,55,0,0);
	scraddpicto(6,0,0,3,4,1,16,0,4,"links"); 
	scraddpicto(7,0,76,3,4,1,17,0,4,"rechts"); 
	scraddpicto(1,0,20,3,2,1,31,0,3,"stop"); 
	scraddpicto(2,0,8,3,2,1,93,0,4,"scherm op"); 
	scraddpicto(3,0,10,3,2,1,92,0,4,"scherm neer"); 
	//scraddpicto(4,0,8,3,2,1,18,0,4,"lijn op"); 
	//scraddpicto(5,0,10,3,2,1,13,0,4,"lijn neer"); 

	if(id.q_nivs!=2){
	scraddpicto(8,0,5,3,2,1,103,0,4,"druk af"); 
	scraddpicto(9,0,13,3,2,1,142,0,4,"detail -"); 
	scraddpicto(10,0,15,3,2,1,141,0,4,"detail +"); 
	scraddpicto(11,0,17,3,2,1,63,0,4,"home"); 
//  scraddpicto(12,0,20,3,2,1,578,0,0,"testje");
	}
	/*
  if(id.q_nivs!=2){
    k=funkdsp(40," F8 print",22);
    k=funkdsp(k," F9 detail-",22);
    k=funkdsp(k," F10 detail+",22);
  }
  f_nr_sel=f_nr; scraddf(f_nr++,22,0,0);
  k=funkdsp(0," F1 stop",23);
	k=funkdsp(k," F2 Scherm op",23);
  k=funkdsp(k," F3 Scherm neer",23);
  k=funkdsp(k," F4 op",23);
  k=funkdsp(k," F5 neer",23);
  k=funkdsp(k," F6 <--",23);
  k=funkdsp(k," F7 -->",23);
  */
}

static zoek()
{
  int16 k,len1,len2,found=NO;

  if(niv_dsp==7){
    k=get_ul(selbuf[0]);
    if(k<'0') k=0;
    else if(k<='9') k-='0';
    else if(k<'A') k=10;
    else if(k<='Z') k+=-'A'+10;
    else k='Z'-'A'+10;
    readbytes(id.idx_pos+k*4L,&pos_first,4);
    if(pos_first==0 && k){
      while(--k){
	readbytes(id.idx_pos+k*4L,&pos_first,4);
	if(pos_first) break;
      }
    }
  }
  else pos_first=niveau[niv_dsp].scr1boven;
  len1=sizeof selbuf; len2=get_flen(fld[0].fmt);
  best_pos=0; best_fnd=0;
  FOREVER{
    readbytes(pos_first,recbuf,id.reclen);
    k=comp_str(selbuf,&recbuf[LEN_PTR],len1,len2);
    if(k==0 || k==2) {found=YES;goto endsr;}
    if(best_fnd<bytes_ok){best_pos=pos_first;best_fnd=bytes_ok;}
    if(*(long *)&recbuf[6]==0) break;
    pos_first=*(long *)&recbuf[6];
  }
  endsr:;
  if(found==NO && best_pos) pos_first=best_pos;/* zetten op beste match */
  curs_row=0;
  zeros(selbuf,sizeof selbuf);
}

static comp_str(p1,p2,len1,len2)
char *p1, *p2;
int16 len1,len2;
{
  int16 k1=0,k2=0;
  char b1,b2;

  bytes_ok=0;
  FOREVER{
    FOREVER{
      if(k1>=len1) {len1=-1;break;}
      b1=*(p1+k1); k1++;
      if(b1=='\0'){len1=-1; break;}/* 0-byte found */
      if(b1>='a' && b1<='z') b1=b1-'a'+'A';
      if((b1>='A' && b1<='Z') || (b1>='0' && b1<='9') || (b1=='?')) break;
      if(b1=='*') return 0;
    }
    FOREVER{
      if(k2>=len2) {len2=-1;break;}
      b2=*(p2+k2); k2++;
      if(b2=='\0'){len2=-1; break;}/* 0-byte found */
      if(b2>='a' && b2<='z') b2=b2-'a'+'A';
      if((b2>='A' && b2<='Z') || (b2>='0' && b2<='9')) break;
    }
    if(len1<0) return NO;
    if(len2<0) return YES;
 
    if(b1=='?') b1=b2;
    if(b1<b2) return YES;
    if(b1>b2) return YES;
    bytes_ok++;
  }
}

static char get_ul(byte)
char byte;
{
  if(byte>='a' && byte<='z') byte+=-'a'+'A';
  return byte;
}




static print(from_,to_,niv_)
long from_,to_;
int16 niv_;
{
  int16 j,k,pos_,form_dat[8],pr_mode,prtnr,rniv_,char_line,filecount_=1;
  long l,qlines_,qblancs_;
  char str_[150];

  if(ask_prt(from_,to_,niv_)) goto endsr;
  calc_hlen();
  char_line=132; if(max_hlen<80) char_line=80;
	qlines_=1; qblancs_=0;prt_niv=0;
	if(Prt2Xls){ // XLS is bij ask_prt al geopend
		scrget(1,7);scrupd(-3,0);
		XlsSkipBlancs=YES;
		StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
		StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
		StylGrpTot=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_BEIGE,1,1,0,NO,NO);
		StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);

		XlsRij=1;XlsKol=1;Styl2Use=StylNormal;

		for(k=0;k<FLD_COUNT;k++){
			if(fld[k].fmt[0]=='\0') break;
			if(fld[k].blok_nr>0 && fld[k].blok_nr<10){
				if(blok_sel[fld[k].blok_nr]!='J') goto next;
			}
			XlsWrite(XlsRef,0,XlsKol++,0,fld[k].naam,0);
			next:;
		}
		XlsRij++;XlsKol=1;prt_niv=0;
  	goto no_hdr;
	}
  scrget(1,6);scrupd(-3,0);
  getsysprNew(5,form_dat,&pr_mode,&prtnr);if(prt2pdf)PrintPaperNr=0;
  k=2;
  if(niv_>2){/* +++ */
    zero(str_,sizeof str_);
    if(char_line==80) {copy("<t27b>",str_,6);pos_=6;}
    else {copy("<t35b>",str_,6);pos_=6;}
    k=3;
  }
  if((errnum=prtopen(prtnr,form_dat,6,char_line,pr_mode,k))!=0) goto endsr;
  free=999;
  for(k=0;k<80;k++) if(id.hoofding[k]=='\0') break;
  if(char_line==80){
    prtfld(25,1,23); prttext("<t26b>"); prttext(id.hoofding); prttext("<b>");
		if((k+27)<62){prttext("<t62>"); prtifld(fm_udat,u(25,2),-1);}
		prttext("<t72>Blz.<ppp>.");
  }
  else{
    prtfld(25,1,-1); prttext("<t35b>");
    if(k<30) prttext("<b>");prttext(id.hoofding);
    if(k<30) prttext("<b>");prttext("<b><t95>");
    prtfld(25,2,-1); prttext("<t120>Blz.<ppp>.");
  }
  prtbuf(1);

  if(niv_>2){
    for(k=2;k<niv_;k++){
      if(k<niv_-1) l=niveau[8-k].pos_hdr; else l=pos_head;
      readbytes(l,recbuf,id.reclen);
      if(k>2){copy(" -> ",&str_[pos_],4); pos_+=4;}
      for(j=0;j<fld[0].fmt[2]; j++){
	if(recbuf[fld[0].pos+j]=='\0') break;
	str_[pos_++]=recbuf[fld[0].pos+j];
	if(pos_>=80) break;
      }
      if(pos_>=80) break;
    }
    prttext(str_);prttext("<b>");
    prtbuf(2);
  }
	zeros(str_,sizeof str_);k=copy0(id.hoofding,str_,100);
	if(cmp_str(OmshrijvingNiv0,"Totaal",6)) {copy(" - ",&str_[k],3); k+=3; copy0(OmshrijvingNiv0,&str_[k],20);}
  p_pdfname(str_,0,0);
 
  prt_hdr();
no_hdr:;
  readrec(to_); rniv_=*(uint16 *)&recbuf[0] & 0x07;
  if(prt_lo2hi!='J') det_loop(from_,to_,rniv_);
  else{
    for(l=from_;l<=to_;l++){
      readrec(l);
      prt_det();
			if(Prt2Xls && XlsRij>32500){
				XlsClose(XlsRef,1);
				XlsSkipBlancs=YES;
				zero(str_,sizeof str_); filecount_++;
				pos_=copy0(id.hoofding,&str_,60);
				pos_+=copy0(" Deel ",&str_[pos_],8);str_[pos_++]='0'+filecount_;
				XlsRef=OpenXlsFile(str_,0);
				if(XlsRef<=0) {errnum=1;break;}
				StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
				StylTotaal  =XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_DONKERGROEN,1,1,0,NO,NO);
				StylGrpTot=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_BEIGE,1,1,0,NO,NO);
				StylKlasse=XlsStyle(XlsRef,"",10,0x00,YES,NO,NO,0,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
				StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);

				XlsRij=1;XlsKol=1;Styl2Use=StylNormal;
//				DisplayWarning("Teveel detail geselecteerd : niet alle gegevens werden uitgeschreven!",605,0);
//				errnum=64; break;
			}
    }
  }
	if(Prt2Xls)	XlsClose(XlsRef,1);
	else{ prtform(0); prtclose();}
  endsr:;
}

static det_loop(from_,to_,niv_)
long from_,to_;
int16 niv_;
{
  int16 rniv_;
  long l, bpos_;

  readrec(to_);prt_det();
  if(from_==to_) goto endsr;
  for(l=from_;l<to_;l++){
    readrec(l);
    rniv_=*(uint16 *)&recbuf[0] & 0x07;
    if(rniv_==niv_-1) break;
  }
  if(l==from_){/* onderliggend niveau is laagste */
    for(l=from_;l<to_;l++){
      readrec(l);prt_det();
    }
  }
  else{
    bpos_=from_;
    for(l=from_;l<to_;l++){
      readrec(l);
      rniv_=*(uint16 *)&recbuf[0] & 0x07;
      if(rniv_==niv_-1){
	det_loop(bpos_,l,rniv_);
	bpos_=l+1;
      }
    }
  }
  endsr:;
}

static ask_prt(from_,to_,niv_)
long from_,to_;
int16 niv_;
{
  int16 j,k,key,curs,z,high_niv_,low_niv_,curspos_;
  flag ask_blok=NO;
  long pos_,l;
  char str_[250];

  scrget(1,7);scrupd(-3,0);
  for(k=0;k<10;k++) blok_sel[k]=0xFF;
  readrec(from_); low_niv_=*(uint16 *)&recbuf[0] & 0x07;
  readrec(to_); high_niv_=*(uint16 *)&recbuf[0] & 0x07;
  zeros((char *)&prt_parm[0].prt,sizeof prt_parm); zeros(OmshrijvingNiv0,sizeof OmshrijvingNiv0);
  for(k=0;k<8;k++){
    if(k>=low_niv_ && (k>=low_niv_+1 || low_niv_>=high_niv_-1)){// laagste niveau (factuur) default op N zetten 
      prt_parm[k].prt='J';
    }
    else prt_parm[k].prt='N';
    prt_parm[k].newpage='N';
    prt_parm[k].separate='N';
    prt_parm[k].bold='N';
  }

  for(l=from_;l<=to_;l++){
    readrec(l);
    k=*(uint16 *)&recbuf[0] & 0x07;
    if(k>=0 && k<9) prt_parm[k].qlines++;
  }
/*  if(id.q_nivs==2) goto endsr; */
  for(k=0;k<FLD_COUNT;k++){
    if(fld[k].fmt[0]=='\0') break;
    if(fld[k].blok_nr>0 && fld[k].blok_nr<10){
      if(fld[k].codebits!=1) blok_sel[fld[k].blok_nr]='J';
      else blok_sel[fld[k].blok_nr]='N';
      ask_blok=YES;
    }
  }
  scraddf(-1,0,0,0);z=1;
	scraddpicto(1,0,72,22,4,2,583,0,0,"Maak PDF"); 
	scraddpicto(2,0,76,22,4,2,573,0,0,"Maak XLS"); 
  scraddf(z++,2,25,1);
  scraddf(z++,4,5,1);

  pos_=from_; curs=6;
  prt_parm[low_niv_].pos=from_;prt_parm[high_niv_].pos=to_;
  for(k=low_niv_;k<=high_niv_;k++){
    if(k!=low_niv_ && k!=high_niv_){
      while(pos_++<to_){
				readrec(pos_);
				j=*(uint16 *)&recbuf[0] & 0x07;
				if(j==k){prt_parm[k].pos=pos_;break;}
      }
    }
    scraddf(z++,curs,4,0);
/*  if(k!=low_niv_) scraddf(z++,curs,24,0); */
    scraddf(z++,curs,32,2);
    scraddf(z++,curs,36,9);
    curs++;
  }
  curs+=2;
  if(ask_blok){
    scraddf(z++,curs,5,1);curs+=2;
    for(k=0;k<10;k++){
      if(blok_sel[k]!=0xFF){
				scraddf(z++,curs,4,0);
				scraddf(z++,curs,11,0);
				scraddf(z++,curs,15,2);
				scraddf(z++,curs,18,9);
				curs++;
      }
    }
  }
  curs+=2;
  scraddf(z++,curs,4,0);scraddf(z++,curs,49,2);  curs++;
  scraddf(z++,23,1,8);scraddf(z++,23,11,8); scraddf(z++,23,25,8);
  curs=1;
  FOREVER{
    redo:;
    z=1;
 
    scrodsp(z++,fm_os79,"Afdrukken statistieken");
    scrodsp(z++,fm_os79,"Welke detail-lijnen wenst U af te drukken (L=aantal lijnen) :");
 
    copy(fld[0].fmt,fmt,16); if(fmt[2]>35) fmt[2]=35;
    for(k=high_niv_;k>=low_niv_;k--){
      readrec(prt_parm[k].pos);
      if(k==high_niv_){
				copy("Totaal ........ (     1",str_,23);
				copy0(&recbuf[fld[0].pos],OmshrijvingNiv0,fmt[2]);
      }
      else{
				copy("Detail niveau 1 (      ",str_,23);
				j=high_niv_-k;
				stcli_d(&str_[14],(long)(j),1,0);copy(" (",&str_[15],2);
  				stcli_d(&str_[17],prt_parm[k].qlines,6,1);
      }
      copy(" L):    (                                     )",&str_[23],50);
    
      scrifld(z++,fm_os79,str_);
      scrifld(-z,fm_uJN,&prt_parm[k].prt);z++;
      scrifld(z++,fmt,&recbuf[fld[0].pos]);
      if(prt_parm[k].prt=='J') scrchat(z-1,0x9); else scrchat(z-1,0xB);
    }
    if(ask_blok){
      scrodsp(z++,fm_os79,"Welke kolommen (=schermen) dienen afgedrukt te worden :");
      for(k=0;k<10;k++){
	if(blok_sel[k]!=0xFF){
	  zero(str_,sizeof str_);pos_=0;
	  for(j=0;j<FLD_COUNT;j++){
	    if(fld[j].fmt[0]=='\0') break;
	    if(fld[j].blok_nr==k){
	      pos_+=copy0(" | ",&str_[pos_],3);
	      pos_+=copy0(fld[j].naam,&str_[pos_],30);
	    }
	  }
	  pos_+=copy0(" |",&str_[pos_],3);
	  scrifld(z++,fm_os79,"Scherm   :   (                                                  )");
	  scrifld(z++,fm_ou1,&k);
	  scrifld(-z,fm_uJN,&blok_sel[k]);z++;
	  scrifld(z++,fm_os50,str_);
	  if(blok_sel[k]=='J') scrchat(z-1,0x9); else scrchat(z-1,0xB);
	}
      }
    }
    scrifld(z++,fm_os79,"Wenst U per hoofdstuk een nieuw blad (J/N) :");
    scrifld(z++,fm_uJN,&new_page);
#if 0
    scrifld(z++,fm_os79,"Lijst afdrukken van laag naar hoog (J/N)   :");
    scrifld(z++,fm_uJN,&prt_lo2hi);
#endif
    scrifld(z++,fm_os9," F1 stop");
    scrifld(z++,fm_os13," F8 druk af ");// scrifld(z++,fm_os13," F9 maak pdf");
    if(autoprint_) key=109;
    else key=scrupd(curs,0x181);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		prt2pdf=NO;if(key==5001 || key==109){prt2pdf=YES; key=108;} // pdf
    Prt2Xls=NO;if(key==5002){Prt2Xls=YES; key=108;} // xls
		if(key==101) return YES;
    if(key==18) curs=curspos_+1;
    if(key!=108) goto redo;
    j=0;
    for(k=low_niv_;k<=high_niv_;k++){
      if(k==6 && new_page=='J') prt_parm[k].newpage='J';
      if(prt_parm[k].prt=='J'){
				switch(j){
					case 1 : prt_parm[k].bold='J'; break;
					case 2 : prt_parm[k].separate='J';break;
					case 3 : prt_parm[k].separate='J';prt_parm[k].bold='J'; break;
					default: break;
				}
				j++;
      }
    }
    break;
  }
endsr:;
	if(Prt2Xls){ // xls hier al openen om juiste naam te krijgen
		scrget(1,7);scrupd(-3,0);
		XlsSkipBlancs=YES;
		zeros(str_,sizeof str_);k=copy0(id.hoofding,str_,100);
		if(cmp_str(OmshrijvingNiv0,"Totaal",6)) {copy(" - ",&str_[k],3); k+=3; copy0(OmshrijvingNiv0,&str_[k],20);}
		XlsRef=OpenXlsFile(str_,0);
    if(XlsRef<=0) {errnum=1;return YES;}
	}
/*   niv_toprt=7-niv_; if(niv_toprt>6) niv_toprt=6; */
  return NO;
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

static prt_hdr()
{
  int16 g,h,j,k,pos=0;

  prtform(0); q_hdr_lin=1;
  for(k=0;k<FLD_COUNT;k++){
    if(fld[k].fmt[0]=='\0') break;
    if(fld[k].blok_nr>0 && fld[k].blok_nr<10){
      if(blok_sel[fld[k].blok_nr]!='J') goto next;
    }
    if(fld[k].prt_kol){
      j=prt_hpos[fld[k].prt_kol-1];
      if(j<pos) {q_hdr_lin++;nextline();if(j) prtblank(j);}
      else {g=j-pos; if(g) prtblank(g);}
      pos=j;
    }
    prt_hpos[k]=pos;
    g=get_flen(fld[k].fmt);j=get_slen(fld[k].naam);h=fld[k].breedte-j;
    if(h && g<0) prtblank(h);
    prttext("<bu>");prttext(fld[k].naam);prttext("<bu>");
    if(h && g>=0) prtblank(h);
    pos+=fld[k].breedte;
    next:;
  }
  nextline();nextline();
}

static prt_det()
{
  int16 j,k,pos=0,niv_;
  flag extra=NO;
								
  niv_=*(uint16 *)&recbuf[0] & 0x07;
  if(prt_parm[niv_].prt!='J') goto endsr;
/*  if(niv_<niv_toprt) goto endsr; */
	Styl2Use=StylNormal;
  if(Prt2Xls==NO && new_page=='J'){
    if(prt_lo2hi!='J'){
      if(niv_==6 && niv_>=prt_niv) {prt_hdr();extra=YES;}
    }
    else{
      if(prt_niv==6 && niv_<prt_niv){prt_hdr();extra=YES;}
    }
  }
  if(Prt2Xls==NO && free<q_hdr_lin+1){prt_hdr();extra=YES;}
  else if(prt_niv!=niv_){
		if(Prt2Xls){
			if(!XlsSkipBlancs) {XlsRij++;XlsKol=1;}
		}
		else{
		  if(prt_lo2hi!='J' && free<=3) {prt_hdr();extra=YES;}
      else nextline();
		}
  }
  prt_niv=niv_;
  if(prt_parm[niv_].separate=='J'){
		if(Prt2Xls){
			Styl2Use=StylKlasse;
			if(!XlsSkipBlancs) {XlsRij++;XlsKol=1;}
		}
		else{
      if(free<4){prt_hdr();extra=YES;}
      for(k=0;k<max_hlen;k++) prttext("-"); nextline();
		}
  }
	
  if(prt_parm[niv_].bold=='J'){
	  if(Prt2Xls){
			if(Styl2Use==StylKlasse) Styl2Use=StylTotaal;
			else Styl2Use=StylGrpTot;
		}
		else prttext("<b>");
	}
  for(k=0;k<FLD_COUNT;k++){
    if(fld[k].fmt[0]=='\0') break;
    if(fld[k].blok_nr>0 && fld[k].blok_nr<10){
      if(blok_sel[fld[k].blok_nr]!='J') goto next;
    }
		if(Prt2Xls) WriteVar2Xls(XlsRij,XlsKol++,fld[k].fmt,&recbuf[fld[k].pos],Styl2Use);
		else{
			if(pos>prt_hpos[k]){nextline();pos=0;}
			if(pos<prt_hpos[k]) prtblank(prt_hpos[k]-pos);
			pos=prt_hpos[k];
	/*    if(niv_==7) prttext("<b>"); */
			prtifld(fld[k].fmt,&recbuf[fld[k].pos],-1);
			j=get_flen(fld[k].fmt); if(j<0) j=-j;
			pos+=j;
	/*   if(niv_==7) prttext("<b>"); */
		}
    next:;
  }
	if(Prt2Xls){
		XlsRij++;XlsKol=1;
		if(!XlsSkipBlancs && prt_parm[niv_].separate=='J')  {XlsRij++;XlsKol=1;}
	}
	else{
    if(prt_parm[niv_].bold=='J') prttext("<b>");
    nextline();
    if(prt_parm[niv_].separate=='J'){for(k=0;k<max_hlen;k++)  prttext("-"); nextline();}
	}
  endsr:;
}

static calc_hlen()
{
  int16 g,h,j,k,pos=0;
									
  max_hlen=1; q_hdr_lin=1;
  for(k=0;k<FLD_COUNT;k++){
    if(fld[k].fmt[0]=='\0') break;
    if(fld[k].blok_nr>0 && fld[k].blok_nr<10){
      if(blok_sel[fld[k].blok_nr]!='J') goto next;
    }
    if(fld[k].prt_kol){
      pos=prt_hpos[fld[k].prt_kol-1];
    }
    prt_hpos[k]=pos;
    g=get_flen(fld[k].fmt);j=get_slen(fld[k].naam);h=fld[k].breedte-j;
    pos+=fld[k].breedte;
    if(max_hlen<pos) max_hlen=pos;
    next:;
  }
}

static nextline()
{
  free=prtline();
}

static funkdsp(h,ptxt,lin_)
int16 h,lin_;
char *ptxt;
{
  int16 k;

  for(k=0;;) if(*(ptxt+k++)=='\0') break;
  fm_osdum[2]=k;
  scraddf(f_nr,lin_,h,8); scrifld(f_nr++,fm_osdum,ptxt);
  return h+k+1;
}
 
static scrstring(nr,s)
char *s;
int16 nr;
{
  fm_string[2]=get_slen(s);
  scrifld(nr,fm_string,s);
}
 
static readrec(recnr_)
long recnr_;
{
  long pos_;

  pos_=id.bod_pos+recnr_*id.reclen;
  readbytes(pos_,recbuf,id.reclen);
}

static readbytes(pos_,pd,len)
long pos_;
int16 len;
char *pd;
{
  int16 k;
			
  while(len){
    k=len; if(k>250) k=250;
    *l(80,1)=pos_;
    fasseqi(80,1,k+4);
    copy(s(80,1)+4,pd,k);
    pos_+=k;pd+=k;len-=k;
  }
}

static initload()
{
  fasunlck(0);
  fileopen(2);/* controle of iemand in deze ovl zit */

  sysget(3954,2,&q_statist);
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

static get_flen(desc)
char *desc;
{
  int16 len;
 
  len=0;
  header = (struct htype *) desc;
  if (!header->ioclass) len=0;/* dummy field */
  else switch (header->type) {
    case 0:
      len = 8;/* mvg -> later echte lengte te geven */
      break;
    case 1:
      len = *(int16 *)(desc+2);
      break;
    case 2:
      len = *(desc+2);
      if (*(desc+4)& 0x10) len+=((len-1)/3);
      if (*(desc+3)) len+=(*(desc+3)+1);
      len=-len;
      break;
    case 3:
      len = 11;
      break;
    case 4:
      len = 14;
      break;
    case 5:
      len = 8;
      break;
  }
  return len;
}
 
static get_slen(s)
char *s;
{
  int16 k;

  k=0;
  while (*s++) k++;
  return k;
}
 
static zeros(pd,len)
char *pd;
uint16 len;
{
  while(len--) *pd++='\0';
}

static cmp_str(p1,p2,len)
char *p1,*p2;
int16 len;
{
  while(len--) if(*p1++!=*p2++) return YES;
  return NO;
}

/** MAG LATER WEG, zo SCRADDF in SCRFUNC opgenomen is ***/

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
/* einde */

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

static double Round(bd_,q_decim_)
double bd_;
int q_decim_;
{
	int k;
  double wrk1_,wrk2_,wrk3_,add_,result_,bd_afr_;
 
	bd_afr_=1.; 
	for(k=0;k<q_decim_;k++) bd_afr_/=10.;
  result_=bd_;
  add_=0.500001;
  if(result_<0) add_=-add_;
  if(bd_afr_>0.00001){
    if(bd_afr_<=1.){
      wrk1_=(long int)result_;
      wrk2_=result_-wrk1_;
    } else{wrk1_=0.;wrk2_=result_;}
    wrk3_=wrk2_/bd_afr_;
    wrk2_=(double)((long)((wrk2_/bd_afr_)+add_)) * bd_afr_;
    result_=wrk1_+wrk2_;
  }
  endsr:;
  return (double)(result_);
}

#include "Std\XlsFunc.c"

static OpenXlsFile(text_,datum_)
char *text_;
unsigned datum_;
{
	int16 pos_,dd,mm,yy;
  char string[100];
				
  zero(string,sizeof string);
	pos_=copy0(text_,&string[0],60);
  if(datum_){
    string[pos_++]=' ';
    jddate(datum_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[pos_],(long)dd,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)mm,2,0);string[pos_+2]='-';pos_+=3;
    stcli_d(&string[pos_],(long)yy,2,0);pos_+=2;
  }
	for(dd=0;dd<pos_;dd++){
		if(string[dd]=='/') string[dd]='-';
		else if(string[dd]=='.' || string[dd]==':' || string[dd]==',') string[dd]=' ';
	}
	pos_+=copy0(".XLS",&string[pos_],4);

  pos_=XlsCreate(string);
	return pos_;
}


static p_pdfname(naam_,dt_beg_,dt_end_)
char *naam_;
uint16 dt_beg_,dt_end_;
{
  int16 pos_,slen_,len_,dd,mm,yy;
  char buf_[30],string[100];
				
  zero(string,sizeof string);
  for(slen_=0;slen_<60;slen_++){ //  pas op! 60 ipv 50
    if(naam_[slen_]=='\0') break;
    string[slen_]=naam_[slen_];
    if(string[slen_]==':') string[slen_]=' ';
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
 
 
 
