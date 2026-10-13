/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0095GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0095dat
#define ovlcod BKH0095cod
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

char ovldat[] = "bkh0095  00:04 25/11/10 (c) Jamadata";
 
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DIM_LINES       500
#define MAX_LINE_LENGTH 100
#define SCR_LINES       20
#define flag            uint16

extern int16 procid;
extern char info[];
extern int16 retcall,parmcall[8];

static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_os80[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_dsp[]   = {9,0xC8,78,0,0,0,'@','@',0};

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
extern long val();
extern float *f();
extern double *d();

static struct{
  char omschr[80];
  char filename[25];
  uint16 nr;
  uint16 dt_beg;
  uint16 dt_end;
  uint16 dsp_direct;
} tb_files[50];
 
static char filename[25],BriefText[DIM_LINES][MAX_LINE_LENGTH];
static char browse_buf[100],hdr_info[75];
static int16 free,MaxLines,hdr_len,q_files,other_fil;
static uint16 direct_nr;
static int16 prt2pdf;

static long *pl_80_1;
static char *p_data;
static int16 def_taal;

 
ovlcod(parmval)
int16 parmval;
{
  int16 j,k,curs=1,key,z,start_,d_lin_scr=19,curspos_;
 
  initload();retcall=0;
	if(parmval==1){
		fasclos(-2);zero(tb_files,sizeof tb_files); copy("..\\Prog\\JamaMsg.JAM",tb_files[0].filename,21);
		if(fasopen(tb_files[0].filename,1)) goto endsr;
		fasinit(80);read_rec(0);
		if(*p_data=='{'){anal_hdr(p_data+1,0);}
		if(tb_files[0].dt_beg && *u(25,2)<tb_files[0].dt_beg) goto endsr;
		if(tb_files[0].dt_end && *u(25,2)>tb_files[0].dt_end) goto endsr;
		load_file(0);fasclos(-2);
		if(DisplayJamaMessage()) retcall=1;
		goto endsr;
	}
	zero(tb_files,sizeof tb_files);
	direct_nr=0;
  load_flist(); if(q_files==0) goto endsr;
  if(direct_nr){
    j=direct_nr-100;
    fasclos(-2);
    copy(tb_files[j].filename,filename,20);
    fasopen(filename,1);
    load_file(j);fasclos(-2);
    if(browse_file()) kill_brf(j);
    else if(tb_files[j].nr<1000) tb_files[j].nr+=1000;
    if(q_files<=1) goto endsr;
    direct_nr=0;
  }
  scrnum=0;start_=0;
  FOREVER{
    redo:
    scrnum=0;scrget(1,113);z=1; fm_dsp[2]=65; fm_dsp[1]=0xC8;/* update */
    for(j=start_;j<(start_+d_lin_scr);j++){
      if(j>=q_files) break;
      j++; scrifld(z++,fm_ou2,&j); j--;
      scrifld(-z,fm_dsp,tb_files[j].omschr);
      if(tb_files[j].nr>=1000) scrchat(z++,0x08);
      else scrchat(z++,0xFF);
    }
    key=scrupd(curs,0x4A1);curs=1;curspos_=fldcurs;
    if(key==101 || key==111) goto endsr;
    if(key==106){
      if(scr_ok("Wenst U echt ALLE berichten te schrappen ???")){
				for(j=0;j<q_files;j++) {kill_brf(j);j--;}
				goto endsr;
      }
    }
    if(key==108 || key==18){
      j=(curspos_-1)/2;j+=start_;
      redo_browse:;
      fasclos(-2);
      copy(tb_files[j].filename,filename,20);
      if(fasopen(filename,1)) goto redo;
      load_file(j);fasclos(-2);
      if(browse_file()) kill_brf(j);
      else if(tb_files[j].nr<1000) tb_files[j].nr+=1000;
      if(q_files==0) goto endsr;
      if(other_fil) {
				if((j+other_fil)>=0 && (other_fil+j)<q_files) j+=other_fil;
				goto redo_browse;
      }
    }
    if(key==102) start_-=d_lin_scr;
    if(key==103){
      start_+=d_lin_scr;
      if(start_>(q_files-d_lin_scr)) start_=q_files-d_lin_scr;
    }
    if(start_<0) start_=0;
    j=0;
    for(k=0;k<d_lin_scr;k++){if(k<=q_files && tb_files[k].nr<1000) {j=k;break;}}
    curs=1+j*2;
  }
endsr:;
	fasclos(-2);
  ovlexit(-1);
}

static ovl_exit(nr_)
int16 nr_;
{
  fasclos(-2);
	*u(25,4)=10;
  ovlexit(nr_);
}
 
static kill_brf(nr_)
int16 nr_;
{
  int16 k;
 
  fasclos(-2);fasinit(80);
  copy(tb_files[nr_].filename,filename,20);
  fasopen(filename,99);fasclos(-2);
  for(k=nr_;k<q_files-1;k++){
    copy((char *)&tb_files[k+1].omschr[0],(char *)&tb_files[k].omschr[0],sizeof tb_files[0]);
  }
  zeros((char *)&tb_files[q_files-1].omschr[0],sizeof tb_files[0]);
  q_files--;
}
 
static load_flist()
{
  int16 k,skip_;

  zeros((char *)&tb_files[0].omschr[0],sizeof tb_files); q_files=0;

  fasinit(80);zero(filename,sizeof filename);copy("..\\Prog\\brief??.jam",filename,19);
  fasopen(filename,102);/* eerste call voor dir */
  FOREVER {
    fasinfo(80,204);                            /* ophalen antwoord van dir */
    if (*s(80,1)=='\0') break;
		copy("..\\prog\\",tb_files[q_files].filename,8);copy(s(80,1),&tb_files[q_files++].filename[8],14);
    if(q_files>=50) break;
  }

  for(k=0;k<q_files;k++){
    fasclos(-2);
    zero(filename,sizeof filename);copy(tb_files[k].filename,filename,20);
    if(fasopen(filename,1)==0){
      fasinit(80);read_rec(0);
      if(*p_data=='{'){
				anal_hdr(p_data+1,k);
      }
      else copy(filename,tb_files[k].omschr,12);
      if(tb_files[k].dt_beg || tb_files[k].dt_end){
				skip_=NO;
				if(tb_files[k].dt_beg && *u(25,2)<tb_files[k].dt_beg) skip_=YES;
				if(tb_files[k].dt_end && *u(25,2)>tb_files[k].dt_end) skip_=YES;
				if(skip_){del_tblijn(k);k--;continue;}
				if(tb_files[k].dsp_direct) direct_nr=100+k;/* altijd tonen */
      }
      if(tb_files[k].dsp_direct && direct_nr==0) direct_nr=100+k;
      tb_files[k].nr=k;
    }
    else {del_tblijn(k);k--;}
  }
	fasclos(-2);
}

static del_tblijn(nr_)
int16 nr_;
{
  int16 k;
									
  for(k=nr_;k<q_files-1;k++){
    copy((char *)&tb_files[k+1].omschr[0],(char *)&tb_files[k].omschr[0],sizeof tb_files[0]);
  }
  zeros((char *)&tb_files[q_files-1].omschr[0],sizeof tb_files[0]);
  q_files--;
}

static DisplayJamaMessage()
{
  char byte;
  int16 j,k,z,count,kol,key;
 
  scrnum=0;scrget(1,259); z=1;
	scraddpicto(1,0,65,0,10,5,605,0,0,"Opgelet!"); 
  j=(76-hdr_len)/2; j+=3;
  scraddf(z,5,j,10); scrifld(z++,VarTextFmt(hdr_len,0),hdr_info);
  for(j=0;j<10;j++){
    if(j>=MaxLines) break;
    zeros(browse_buf,sizeof browse_buf);kol=0;
    for(k=0;k<MAX_LINE_LENGTH;k++){
			byte=BriefText[j][k];
			if(byte=='\0' || byte==0x0D) break;
			count=1;
			if(byte==9) {byte=' '; count=8;}/* expand TAB */
			while(count-->0){
				if(kol<100) browse_buf[kol++]=byte;
			}
    }
    disp_line(j+7,&z,&browse_buf[0]);
  }
  key=scrupd(-1,0x9);
  if(key==101) return NO;
  if(key==104) return YES;
  endsr:;
  return NO;
}


static browse_file()
{
  char byte;
  int16 j,k,z,count,kol,start,key;
 
  start=0; other_fil=0;
  FOREVER{
    redo:;
    scrnum=0;scrget(1,114); z=1;
    fm_dsp[2]=hdr_len; fm_dsp[1]=0x88;/* output only */
    j=(76-hdr_len)/2; j+=3;
    scraddf(z,0,j,10);
    scrifld(z++,fm_dsp,hdr_info);
    for(j=start;j<start+SCR_LINES;j++){
			if(j>=MaxLines) break;
      zeros(browse_buf,sizeof browse_buf);kol=0;
      for(k=0;k<MAX_LINE_LENGTH;k++){
				byte=BriefText[j][k];
				if(byte=='\0' || byte==0x0D) break;
				count=1;
				if(byte==9) {byte=' '; count=8;}// expand TAB 
				while(count-->0){
					if(kol<100) browse_buf[kol++]=byte;
				}
      }
      disp_line(j-start+2,&z,&browse_buf[0]);
    }
    key=scrupd(-1,0xFF3F);
    if(key==101) break;
    if(key==111) ovl_exit(-1);
    if(key==104){other_fil=-1;goto endsr;}
    if(key==105){other_fil=1;goto endsr;}
    if(key==106){
      if(scr_ok("Wenst U echt deze brief te schrappen ???")) return YES;
    }
    switch(key){/* konversie pijltjes naar funktietoetsen */
      case  8 : key=112;break;/* 1 lijn omhoog */
      case  9 : key=113;break;/* 1 lijn omlaag */
      case 10 : start=0;break;
      case 11 : start=MaxLines-SCR_LINES;break;
      case 12 : key=102;break;
      case 13 : key=103;break;
      default : break;
    }
    if(key==112) start-=1;
    if(key==113) {start+=1;if(start>=MaxLines) start-=1;}
    if(key==102) start-=SCR_LINES;
    if(key==103){
      start+=SCR_LINES;
      if(start>=MaxLines) start-=SCR_LINES;
    }
    if(start<0) start=0;
    prt2pdf=NO;if(key==110){prt2pdf=YES;key=109;}
    if(key==109) print_file();
  }
  endsr:;
  return NO;
}

static anal_hdr(ps_,nr_)
char *ps_;
int16 nr_;
{
  char kar_,kar1_;
  int16 n,len_;
 
  n=0;
  FOREVER{
    next:;
    kar_=*(ps_+n++);
    if(kar_=='\0' || kar_==0x0D || kar_=='}') break;
    if(kar_=='<'){
      kar1_=*(ps_+n);
      switch(kar1_){
				case 's' :;
				case 'S' : len_=get_date(ps_+1+n,&tb_files[nr_].dt_beg);n+=len_+1;break;
				case 't' :;
				case 'T' : len_=get_date(ps_+1+n,&tb_files[nr_].dt_end);n+=len_+1;break;
				case '!' : tb_files[nr_].dsp_direct=YES;n++;break;
				case '"' : len_=get_str(ps_+1+n,&tb_files[nr_].omschr[0]);n+=len_+1;break;
				default  : break;
      }
    }
  }
}

static get_date(ps_,dt_)
char *ps_;
uint16 *dt_;
{
  int16 k,dd,mm,jj;
  char kar_,str_[3];

  k=0;
  FOREVER{
    kar_=*(ps_+k);
    if(kar_=='\0' || kar_==0x0D || kar_=='}' || kar_=='>') break;
    k++;
  }
  if(k<6) {*dt_=0;goto endsr;}
  else{
    copy(ps_,str_,2);str_[2]=0;dd=val(str_);
    copy(ps_+2,str_,2);str_[2]=0;mm=val(str_);
    copy(ps_+4,str_,2);str_[2]=0;jj=val(str_);
    *dt_=datejd(jj,mm,dd);
  }
  endsr:;
  return k;
}
 
static get_str(ps_,pd_)
char *ps_,*pd_;
{
  int16 k;
  char kar_;
									
  k=0;
  FOREVER{
    kar_=*(ps_+k);
    if(kar_=='\0' || kar_==0x0D || kar_=='}' || kar_=='"' || kar_=='>') break;
    k++; if(k>=65) break;
  }
  copy(ps_,pd_,k);
  return k;
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

static print_file()
{
  char byte;
  int16 form_dat[8],pr_mode,prtnr;
  int16 j,k,count,kol;

  scrget(1,6);scrupd(-3,0);scrnum=0;
  getsysprNew(3,form_dat,&pr_mode,&prtnr); if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) goto endsr;
  free=999;
  prttext("<b>"); prttext(hdr_info); prttext("<b>");
  prttext("<t50>"); prtfld(25,2,-1); prttext("   P<pp>.");
  prtbuf(1);
  p_pdfname(hdr_info,*u(25,2),0);
 
  for(j=0;j<MaxLines;j++){
    zeros(browse_buf,sizeof browse_buf);kol=0;
    for(k=0;k<MAX_LINE_LENGTH;k++){
      byte=BriefText[j][k];
      if(byte=='\0' || byte==0x0D) break;
      count=1;
      if(byte==9) {byte=' '; count=8;}/* expand TAB */
      while(count-->0){
				if(kol<100) browse_buf[kol++]=byte;
      }
    }
    prtifld(fm_os80,browse_buf,-1);nextline();
  }
  prtform(0);prtclose();
  endsr:;
}

static disp_line(vt_,z,ps_)
int16 vt_,*z;
char *ps_;
{
  int16 j,n,k,q_kar_,h_pos,printed,stop_,used_;
  char kar_,kar1_,d_buf[100],mask_[4],dmask_[4];

  n=0;printed=NO;h_pos=3;q_kar_=0;
  zeros(d_buf,sizeof d_buf); zeros(dmask_,sizeof dmask_);
  FOREVER{
    next:;
    kar_=*(ps_+n++);
    if(kar_=='\0' || kar_==0x0D) break;
    if(kar_=='<'){
      stop_=NO; used_=NO; zeros(mask_,sizeof mask_);
      for(k=0;k<4;k++){
				kar1_=*(ps_+n+k);
				switch(kar1_){
					case 'b' : mask_[1]=1;used_=YES;break;
					case 'e' : mask_[3]=1;used_=YES;break;
					case 'u' : mask_[0]=1;used_=YES;break;
					case '>' : stop_=YES;break;
					default  : stop_=YES;used_=NO;break;
				}
				if(stop_) break;
      }
      if(used_){
				if(q_kar_){
					_dsp_fld(*z,vt_,h_pos,d_buf,q_kar_,dmask_);
					*z+=1;printed=YES;h_pos+=q_kar_;
					q_kar_=0; zeros(d_buf,sizeof d_buf);
				}
				for(j=0;j<4;j++){
					if(dmask_[j] != mask_[j]) dmask_[j]=1;
					else dmask_[j]=0;
				}
				n+=k+1;
				goto next;
      }
    }
    d_buf[q_kar_++]=kar_;
    if((h_pos+q_kar_)>76) break;
  }
  if(q_kar_ || printed==NO){
    if(q_kar_==0){d_buf[0]=' ';q_kar_=1;}/* lege lijn */
    _dsp_fld(*z,vt_,h_pos,d_buf,q_kar_,dmask_);
    *z+=1;printed=YES;h_pos+=q_kar_;
    q_kar_=0;
  }
}

static _dsp_fld(z,vt_,hz_,ps_,len_,mask_)
int16 z,vt_,hz_,len_;
char *ps_,*mask_;
{
  int16 k,attr_=0;
 
  for(k=0;k<4;k++){
    if(*(mask_+k)) attr_|=1<<k;
  }
  fm_dsp[2]=len_; fm_dsp[1]=0x88;/* output only */
  scraddf(z,vt_,hz_,attr_);
  scrifld(z,fm_dsp,ps_);
}

static load_file(nr_)/* inlezen pointers en header-info */
int16 nr_;
{
  int16 k,mode_=0,first;

  scrget(1,7);scrupd(-3,0);
	zero(BriefText,sizeof BriefText);MaxLines=0;
  fasinit(80);first=YES; 
	zeros(hdr_info,sizeof hdr_info); hdr_len=0;
  hdr_info[0]=' ';/* blanko vooraan zetten */
  for(k=0;k<75;k++){
    if(tb_files[nr_].omschr[k]=='\0') break;
    hdr_info[k+1]=tb_files[nr_].omschr[k];
  }
  hdr_info[k+1]=' ';/* blanko achteraan */
  hdr_len=k+2;
	 
  FOREVER{
    next:;
    if(read_rec(mode_)) break;
    mode_=1;
    if(first){
      if(*p_data=='{'){
				first=NO;
				goto next;
      }
      first=NO;
    }
		copy(p_data,BriefText[MaxLines++],MAX_LINE_LENGTH);
    if(MaxLines>=DIM_LINES) break;
  }
}

static read_rec(mode_)
int16 mode_;
{
  int16 j;
  flag eof_=NO;
  long pos_;

  if(mode_){
    for(j=0;j<256;j++) if(*(p_data+j)==0x0A || *(p_data+j)=='\0') break;
    if(*(p_data+j)==0x0A || *(p_data+j)=='\0') *pl_80_1+=(j+1);
    zeros(p_data,256);
  }
  pos_=*pl_80_1;
  if(fasseqi(80,1,256)) {eof_=YES;}
  if(eof_ && *p_data=='\0') return YES;
  else{/* positioneer terug op eerste karakter */
    *pl_80_1=pos_;
    return NO;
  }
}
 

 
static initload()
{
  sysget(3678,2,&def_taal);
								
  p_data=s(80,1)+4;
  pl_80_1=l(80,1);
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
 
static cmp_str(p1,p2,len)
int16 len;
char *p1,*p2;
{
  while(len--){
    if(*p1++!=*p2++)return 1;
  }
  return 0;
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
 
