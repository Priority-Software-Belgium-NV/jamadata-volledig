/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0237GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0237dat
#define ovlcod DRK0237cod
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

char ovldat[] = "drk0237  00*07 23/09/09 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define MAXRL           500
#define LEN_PTR         2+4+4+4

extern char *s();
static char *get_p();
extern int16 *i();
extern uint16 *u();
extern uint16 datejd();
extern long *l();
extern long val();
extern float *f();
extern double *d();
extern double valu_cnv();

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

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os25[]  = {7,0x88,25,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_uf3_0[] = {6,0xD4,3,0,0x70,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_odsp[]  = {7,0x88,79,0,0,0,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];
 
static int16 fil_nr,fld_msk[20],q_statist=0,kdsp,kdsp_off=1,NrNiv;
static char recbuf[8][MAXRL],nullen[128],prevbuf[50],def_munt[4],fmt[40],SorteerKlantOpOmzet='N';
static long loffil,recnr,niv_pos[8],niv_first[8],indx[36],rec_working;
static flag lvcd,klcd,chk_btoeg=NO,sear_stt,sys3876;
static uint16 KasKltRec[20];
static char disp_str[55],TxtTitel[100];
static struct _SortTabel{
	uint16 Record;
	double Bedrag;
} SortTabel[10000];
static int MaxSortTabel;
  
#include "par0237.c"

static int16 date2str();
  
ovlcod1()
{
  int16 key,j,k,z,z_base,onlynr=0,curspos_;
  uint16 dd,mm,yy,end_;
  char all='J',filnam[25];
  
  if(q_statist==0) q_statist=sizeof tb/sizeof tb[0];
  initload();
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,2,30,2);
  for(k=0;k<q_statist;k++) scraddf(z++,5+k,3,0);
  scraddf(z++,5+k+2,46,0);scraddf(z++,5+k+2,73,2);
  scraddf(z++,23,1,8);scraddf(z++,23,11,8);
  FOREVER{
    z=1;
		DisplayMenuTitel(1,"Herberekenen statistiek(en)",0xB);z++;
  //  scrifld(z++,fm_os79,"Herberekenen statistiek(en)");
    for(k=0;k<q_statist;k++){
      zeros(filnam,sizeof filnam);
      fasclos(-2);zeros((char *)id.title,sizeof id);
      stcli_d(&filnam[3],(long)(k+1),3,0);
      copy(".sta",&filnam[6],5);
      copy(s(25,3),filnam,3);
      if(fasopen(filnam,1)==0){
				readbytes(0L,(char *)&id,sizeof id);
      }
      else{
				copy_0(tb[k].hoofding,id.hoofding,60);
      }
      end_=NO;
      for(j=0;j<55;j++){
				if(id.hoofding[j]=='\0' || end_){
					if(!end_) id.hoofding[j]=' ';
					else id.hoofding[j]='.';
					end_=YES;
				}
      }
		  if(id.date){
				jddate(id.date,&yy,&mm,&dd);
				copy(" (",&id.hoofding[55],2);
				stcli_d(&id.hoofding[57],(long)dd,2,1);id.hoofding[59]='/';
				stcli_d(&id.hoofding[60],(long)mm,2,0);id.hoofding[62]='/';
				stcli_d(&id.hoofding[63],(long)yy,4,0);
      } else copy(" (  /  /    ",&id.hoofding[55],13);
      copy(") : ",&id.hoofding[67],4);
      k++;stcli_d(&id.hoofding[70],(long)k,2,1);k--;
      scrifld(z++,fm_os79,id.hoofding);
    }
    fasclos(-2);
    z_base=z;
    redo:;
    z=z_base;
    scrifld(z++,fm_os79,"U kiest (blanko=allemaal) :");
    scrifld(z++,fm_uu2,&onlynr);
    scrifld(z++,fm_os9," F1 stop");scrifld(z++,fm_os13," F8 neem aan");
    key=scrupd(1,0x2081);curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) break;
    if(onlynr>q_statist){
      errnum=34;goto redo;
    }
		if(key==251){
			if(curspos_>=2 && curspos_<=q_statist+1){ onlynr=curspos_-1;}
			else goto redo;
		}
    if(onlynr==0 && key!=108) goto redo;
    for(fil_nr=0;fil_nr<q_statist;fil_nr++) fld_msk[fil_nr]=fil_nr;
/* indien zelfde mask dan deze nu veranderen */
    if(onlynr==0) all='J'; else all='N';/* compatibel blijven met vorige versies */
    if(spec_ask(all,onlynr)) goto endsr;
 //   if(chk_users()) break;
		fasunlck(-2);
    if(all=='J') for(fil_nr=0;fil_nr<q_statist;fil_nr++) exec_fil();
    else{fil_nr=onlynr-1;exec_fil();}
		fasunlck(0);
    break;
  }
  endsr:;
}

static exec()
{
  int16 k;
  uint16 a,used;
  char filnam[15];
 
  zeros(recbuf[0],sizeof recbuf);recnr=0;rec_working=0;kdsp=0;kdsp_off=1;
  zero(disp_str,sizeof disp_str);
  zeros((char *)niv_pos,sizeof niv_pos);
  zeros((char *)&id,sizeof id);
  zeros((char *)&indx,sizeof indx);
  stcli_d(&filnam[3],(long)(fil_nr+1),3,0);
  copy(".sta",&filnam[6],5);
  copy(s(25,3),filnam,3);
  if(fasopen(filnam,2)){errnum=63;scrget(1,170);scrupd(-1,0);goto endsr;}
  loffil=0;fasclos(-2);fasopen(filnam,3);

  copy("\xF2Vers 00001 15/03/90 (c) Jamadata\x1A",id.title,34);
  copy(s(25,1),id.firma,sizeof id.firma);
  copy_0(tx->hoofding,id.hoofding,sizeof id.hoofding);

  id.date=*u(25,2);id.q_nivs=q_niv;
  id.hdr_pos=512;
  id.idx_pos=id.hdr_pos+100*64L;
  id.bod_pos=((long)(id.idx_pos+sizeof indx)/64+1)*64;
  id.reclen=LEN_PTR;
  for(k=0;k<sizeof fld[fld_msk[fil_nr]]/sizeof fld[fld_msk[fil_nr]][0];k++){
    if(fld[fld_msk[fil_nr]][k].naam[0]){
      fld[fld_msk[fil_nr]][k].pos=id.reclen;
      id.reclen+=fld[fld_msk[fil_nr]][k].len;
      writebytes(id.hdr_pos+k*64L,(char *)&fld[fld_msk[fil_nr]][k],sizeof fld[fld_msk[fil_nr]][k]);
      id.q_kol++;
    }
  }

  if(tx->drv_stu==0) exec1drv();
  else{
    fileopen(tx->drv_stu);
    if(tx->drv_key==0){
      fasinfo(tx->drv_stu,1);
      used=*u(tx->drv_stu,1);
 
      for(a=1;a<=used;a++){
				*u(tx->drv_stu,1)=a;
				if(fasgetu(tx->drv_stu)==0){
					exec1drv();
				}
      }
    }
    else{
			if(tx->drv_stu==2 && SorteerKlantOpOmzet=='J'){ // sorteertabel wordt in par237 aangemaakt owv selecties
				for(a=0;a<=MaxSortTabel;a++){
					*u(tx->drv_stu,1)=SortTabel[a].Record;
					if(fasgetu(tx->drv_stu)==0){
						exec1drv();
					}
				}
			}
			else{
				fasinit(tx->drv_stu);
				FOREVER{
					if(faskeyi(tx->drv_stu,tx->drv_key,2)) break;
					exec1drv();
				}
			}
    }
  }
  for(k=0;k<3;k++){
    if(fld[fld_msk[fil_nr]][k].len>8) copy("Totaal",get_p(7,k),7);
  }
  add_rec(7);
  writebytes(0L,(char *)&id,sizeof id);
/* for(k=0;k<36;k++) if(indx[k]==0) indx[k]=indx[0]; */
  writebytes(id.idx_pos,(char *)&indx,sizeof indx);
  fasflush(0);
	fasclos(-2);
  endsr:;
}

static add_rec(niv_)
int16 niv_;
{
  int16 k;
  char firstbyte;
  long pos_;

  if(*(int16 *)&recbuf[niv_][0]==0) *(uint16 *)&recbuf[niv_][0]=0x8000+niv_;
  pos_=id.bod_pos+recnr*id.reclen;
  if(niv_pos[niv_]) writebytes(niv_pos[niv_]+6,&pos_,4);
  *(long *)&recbuf[niv_][2]=niv_pos[niv_];
  niv_pos[niv_]=pos_;for(k=niv_-1;k>=0;k--) niv_pos[k]=0;
  if(niv_){*(long *)&recbuf[niv_][10]=niv_first[niv_-1];niv_first[niv_-1]=0;}
  writerec(recnr++,niv_);
  if(recnr>id.q_rec) id.q_rec=recnr;
  if(niv_==7 && id.pos_niv7==0) id.pos_niv7=pos_;
  if(niv_first[niv_]==0) niv_first[niv_]=pos_;
  if(niv_==6){
    k=fld[fld_msk[fil_nr]][0].len;  fm_odsp[2]=k;
    scrifld(18,fm_odsp,get_p(6,0));scrupd(-3,0);/* hoogste niveau displayen */
    for(k=0;k<10;k++){
      firstbyte=recbuf[niv_][LEN_PTR+k];/* leading spaties wegdoen */
      if(firstbyte!=' ') break;
    }
    if(firstbyte>='a' && firstbyte<='z') firstbyte+=-'a'+'A';
    if(firstbyte<'0') firstbyte=0;
    else if(firstbyte<='9') firstbyte-='0';
    else if(firstbyte<'A') firstbyte=10;
    else if(firstbyte<='Z') firstbyte+=-'A'+10;
    else firstbyte='Z'-'A'+10;
    for(k=0;k<=firstbyte;k++) if(indx[k]==0) indx[k]=pos_;
  }
  zeros(recbuf[niv_],sizeof recbuf[0]);
}
 
static char *get_p(niv,kolom)
int16 niv,kolom;
{
  return &recbuf[niv][fld[fld_msk[fil_nr]][kolom].pos];
}

static dsp_working()
{
  rec_working++;
  if((rec_working%10000)==0) scrupd(-3,0);
  //if((rec_working%1000)==0){
  //  if(kdsp_off==-1){if((kdsp%10)!=9) disp_str[kdsp]=' ';}
  //  else {if((kdsp%10)==9) disp_str[kdsp]='|'; else disp_str[kdsp]='*';}
  //  scrifld(22,fm_os63,&disp_str);scrupd(-3,0);
  //  kdsp+=kdsp_off;
  //  if(kdsp>=50){kdsp--;kdsp_off=-1;}
  //  else if(kdsp<0) {kdsp=0;kdsp_off=1;}
  //}
}


static exec_fil()
{
  tx=&tb[fil_nr];
  scrnum=0;
  scrget(1,170);
  scrifld(10,fm_os79,"Samenstellen van statistiek nr. ");
  fil_nr++;scrifld(12,fm_ou3,&fil_nr);fil_nr--;scrupd(-3,0);
  exec();
}
 
static readrec(recnr_,bufnr_)
int16 bufnr_;
long recnr_;
{
  long pos_;

  pos_=id.bod_pos+recnr_*id.reclen;
  readbytes(pos_,recbuf[bufnr_],id.reclen);
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

static writerec(recnr_,bufnr_)
int16 bufnr_;
long recnr_;
{
  long pos_;

  pos_=id.bod_pos+recnr_*id.reclen;
  extend(pos_);
  writebytes(pos_,recbuf[bufnr_],id.reclen);
}

static writebytes(pos_,ps,len)
long pos_;
int16 len;
char *ps;
{
  int16 k;

  extend(pos_);
  if(pos_+len>loffil) loffil=pos_+len;
  while(len){
    k=len; if(k>250) k=250;
    *l(80,1)=pos_;
    copy(ps,s(80,1)+4,k);
    fasseqo(80,3,k+4);
    pos_+=k;ps+=k;len-=k;
  }
}
 
static extend(pos_)
long pos_;
{
  long l;

  while(pos_>loffil){
    l=pos_-loffil;if(l>128) l=128;
    writebytes(loffil,nullen,(int16)l);
  }
}

static initload()
{
  fasunlck(0);

  if(fldlen(16,1)) fileopen(13);
	fileopen(14);
/* q_statist=sizeof tb/sizeof tb[0]; */

  sysget(294,3,def_munt);
  sysget(1918,2,&sear_stt);
  sysget(3876,2,&sys3876);
  sysput(3954,2,&q_statist);
  sysget(4294,40,(char *)&KasKltRec[0]);
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
 
static zeros(pd,len)
char *pd;
uint16 len;
{
  while(len--) *pd++='\0';
}

static chk_users()
{
  int16 k,key,z;
 
  fasinfo(80,203); k=*u(80,1)-1;
  if(k==0) goto endsr;

  scraddf(-1,0,0,0);z=1;
  scraddf(z++,8,25,6);
  scraddf(z++,12,15,0);scraddf(z++,12,28,2);scraddf(z++,12,31,0);
  scraddf(z++,14,15,0);
  scraddf(z++,23,1,8);scraddf(z++,23,11,8);
  FOREVER{
    redo:;
    z=1;
    scrifld(z++,fm_os79," W A A R S C H U W I N G ");
    scrifld(z++,fm_os79,"Er zijn nog ");scrifld(z++,fm_uu2,&k);
    scrifld(z++,fm_os79,"andere gebruiker(s) aktief !");
    scrifld(z++,fm_os79,"Controleer dat er NIEMAND met statistieken bezig is.");
    scrifld(z++,fm_os9," F1 stop");scrifld(z++,fm_os13," F4 alles OK ");
    key=scrupd(-1,0x9);
    if(key==101) return YES;
    if(key==104) break;
  }
  endsr:;
  return NO;
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

static cmp_str(p1,p2,len)
char *p1,*p2;
int16 len;
{
  while(len--) if(*p1++!=*p2++) return YES;
  return NO;
}
 
static int16 date2str(str_,date_)
char *str_;
uint16 date_;
{
  int16 dd,mm,jj,len_=0;
 
  if(date_==0) goto endsr;
  jddate(date_,&jj,&mm,&dd);jj%=100;
  stcli_d(&str_[len_],(long)dd,2,0);len_+=2;str_[len_++]='/';
  stcli_d(&str_[len_],(long)mm,2,0);len_+=2;str_[len_++]='/';
  stcli_d(&str_[len_],(long)jj,2,0);len_+=2;
  endsr:;
  return len_;
}

static copy_0(ps,pd,len)
char *ps,*pd;
int16 len;
{
  int16 k;
 
  for(k=0;k<len;k++) if(*(ps+k)=='\0') break;
  copy(ps,pd,k);
  return k;
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

static CopyStrField(stu_,fld_,pd_,max_len_)
int16 stu_,fld_,max_len_;
char *pd_;
{
	if(max_len_>fldlen(stu_,fld_)) max_len_=fldlen(stu_,fld_);
	copy(s(stu_,fld_),pd_,max_len_);
}
   
/** MAG LATER WEG, zo SCRADDF in SCRFUNC opgenomen is ***/

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
static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
								
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
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