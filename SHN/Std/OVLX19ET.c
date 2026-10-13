/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* Versie 00.01 25/08/00 : Merge routine voor klt/lev etiketten op inktjet/laser */
/* op 12/03/03 ook de print_screen routine toegevoegd */

static int16 sys3648;
static uint16 sys3650;
static char fas2sif[32]  = {160,133,131,132,135,130,138,136,137,161,141,140,
		   139,162,149,147,148,163,151,150,129,154,248,21,
		   254,27,26,24,25,0,0,128};

static prt_etik(mode_)
int16 mode_;/* 1= blad moet niet perse vol zijn */
{
  int16 j,k,vt,y_pos;
  int16 form_dat[8],pr_mode,prtnr;
  uint16 mrec_,recs_hor[15];
									
  sysget(3648,2,&sys3648);
  sysget(3650,2,&sys3650);
  mrec_=*u(stu,1);
  getsyspr(13,form_dat,&pr_mode,&prtnr);
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  scrget(1,6);
  if(q_hor>15) q_hor=10;

  while(free>=0 && tot_etik>0){
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) {free=-1;break;}
    prt_string("\x1B\x45");
    for(vt=0;vt<q_vert;vt++){
      y_pos=y_offset+vt*vt_dots;
      zero((char *)&recs_hor[0],sizeof recs_hor);k=0;
      for(j=0;j<q_hor;j++){
	for(k;k<DIM_LETIK;k++) if(tb_etik[k]) break;
	if(k<DIM_LETIK && tb_etik[k]){recs_hor[j]=tb_etik[k]; k++;}
	else recs_hor[j]=0;
      }
      prt_1rij(y_pos,recs_hor);
      for(j=0;j<q_hor;j++){
	if(recs_hor[j]){
	  for(k=0;k<DIM_LETIK;k++) if(tb_etik[k]==recs_hor[j]){
	    tb_etik[k]=0;tot_etik--;break;
	  }
	}
      }
    }
    prt_string("\x0C");
  }
  endsr:;
  *u(stu,1)=mrec_;fasgeti(stu);
}

static prt_1rij(b_y_pos_,recs)
uint16 b_y_pos_,recs[];
{
  int16 jj,hz,x_pos,y_pos;
  int16 kode_pos_;
  char p_str_[60];
									
  kode_pos_=-1; if(sys3648) kode_pos_=0;
  for(jj=0;jj<5;jj++){
    y_pos=b_y_pos_+jj*line_dots;
    zero(p_str_,sizeof p_str_);
    for(hz=0;hz<q_hor;hz++){
      x_pos=x_offset+hz*hz_dots;
      fasinit(stu);
      *u(stu,1)=recs[hz]; if(*u(stu,1)) fasgeti(stu);

      if(jj==kode_pos_){
	if(fldlen(stu,2)) scopy(s(stu,2),p_str_,fldlen(stu,2));
	else stcli_d(p_str_,(long)(*u(stu,1)),5,0);
	txt_abs(lettype,x_pos,y_pos,p_str_,"");
      }
      else if(jj==1+kode_pos_){
	de_heer(stu);
	scopy(nm_dehr,p_str_,35);
	txt_abs(lettype,x_pos,y_pos,p_str_,"B");
      }
      else if(jj==2+kode_pos_){
	if(sys3650 && stu==2){
	  scopy(s(stu,sys3650),p_str_,30);
	  txt_abs(lettype,x_pos,y_pos,p_str_,"");
	} else continue;
      }
      else if(jj==3+kode_pos_){
	scopy(s(stu,4),p_str_,30);
	txt_abs(lettype,x_pos,y_pos,p_str_,"");
      }
      else if(jj==4+kode_pos_){
	scopy(s(stu,5),p_str_,7);scopy(" ",&p_str_[7],1);
	scopy(s(stu,6),&p_str_[8],23);
	txt_abs(lettype,x_pos,y_pos,p_str_,"");
      }
      else if(jj==5+kode_pos_ && fldlen(stu,7)){
	scopy(s(stu,7),p_str_,30);
	txt_abs(lettype,x_pos,y_pos,p_str_,"");
      }
    }
  }
  endsr:;
}

static scopy(ps_,pd_,len_)
char *ps_,*pd_;
int16 len_;
{
  int16 k,sp_;

  sp_=NO;
  for(k=0;k<len_;k++){
    if(sp_==NO){
      if(*(ps_+k)=='\0') sp_=YES;
      else *(pd_+k)=*(ps_+k);
    }
    if(sp_==YES) *(pd_+k)=' ';
  }
}
 
static prt_string(string)
char *string;
{
  char *_string;
  int16 len;

  len=0; _string=string;
  while (*_string++) len++;
  prt_bin(string,len);
}

static prt_bin(string,len)
char *string;
int16 len;
{
  char fm[8];
 
  fm[0]=7; fm[1]=0x88; fm[2]=len%256; fm[3]=len/256; fm[4]=0; fm[5]=0; fm[6]=0;
  if (len>0) prtifld(fm,string,-2);
}
 
/* print-routine voor inktjet-printer */
/* DjPCL3.mer file 00.01 18/05/95 (c) Jamadata */

static txt_abs(size,x_pos,y_pos,ps_,attr)
char *ps_,*attr;
int16 size, x_pos, y_pos;
{
  int16 len_,stroke_weight, style;
  char und=NO;
 
  len_=0;
  while (*(ps_+len_++)) {}
  cnv_char(ps_,len_);

  stroke_weight=0;
  style=0;
  while (*attr) {
    if (*attr=='B') stroke_weight=3;
    else if (*attr=='I') style=1;
    else if (*attr=='U') und=YES;
    attr++;
  }
  mov_abs(x_pos,y_pos);
  sel_prop(size,stroke_weight,style);
  if (und) prt_string("\x1B&d0D");
  prt_string(ps_);
  if (und) prt_string("\x1B&d@");
}
 
static sel_prop(size,stroke_weight,style)
int16 size,stroke_weight,style;
{
  prt_string("\x1B(10U");
  prt_string("\x1B(s1p(s"); prt_int(size); prt_string("v"); prt_int(style); prt_string("s");
  prt_int(stroke_weight); prt_string("B");
}

static mov_abs(x_pos,y_pos)
int16 x_pos, y_pos;
{
  prt_string("\x1B*p");
  prt_int(x_pos); prt_string("x");
  prt_string("*p");
  prt_int(y_pos); prt_string("Y");
}
 
static prt_int(getal)
int16 getal;
{
  char buf[20];
  int16 j;
									
  stcli_d(buf,(long)getal,5,1);
					      /*  sprintf(buf,"%5d",getal); */
  for (j=0; j<sizeof(buf); j++) {
    if (buf[j]>='0' && buf[j]<='9') {prt_string(&buf[j]); break;}
  }
}
 
static cnv_char(ps_,len_)                           /* convert jama-ascii to ascii */
char *ps_;
int16 len_;
{
  int16 k,q_ele_;
  char kar_;
									
  q_ele_=sizeof fas2sif;
  for(k=0;k<len_;k++){
    kar_=*(ps_+k);
    if(kar_>=0x80 && kar_<0x80+q_ele_){
      *(ps_+k)=fas2sif[kar_-0x80];
    }
  }
}
 
static print_screen(open_prt_)/* 0 niet openen/sluiten, 1 = openen en sluiten 2=openen/nt sluiten */
int16 open_prt_;
{
  int16 j,k,n,lattr_,attr_,q_info_;
  int16 form_dat[8],pr_mode,prtnr;
  char pbuf_[85];
 
  if(open_prt_){
    getsyspr(1,form_dat,&pr_mode,&prtnr);
    if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,4))!=0) goto endsr;
  }
  for(k=0;k<23;k++) {
    scrupd(-2,k);
    copy(&info[0],s(80,1)+4,160);
    lattr_=0; zero(pbuf_,sizeof pbuf_);n=0;
    for(j=0;j<80;j++){
      attr_=info[j*2+1];
      if(attr_!=lattr_ && n>0){
	prt_attr(lattr_);prttext(pbuf_);prt_attr(lattr_);
	zero(pbuf_,sizeof pbuf_);
	n=0;
      }
      lattr_=attr_;pbuf_[n++]=info[j*2];
    }
    if(n>0){
      prt_attr(lattr_);prttext(pbuf_);prt_attr(lattr_);
      nextline();
    }
  }
  nextline();
  if(open_prt_==YES){
    if(fldlen(22,1)){
      q_info_=get_info(NO);
      if(q_info_) print_info(q_info_);
    }
    prtclose();
  }
  endsr:;
}
 
static prt_attr(attr_)
char attr_;
{
  if(attr_ &(1<<0)) prttext("<u>");
  if(attr_ &(1<<1)) prttext("<b>");
}
 
static print_info(q_info_)
int16 q_info_;
{
  int16 k;
					
  nextline();
  for(k=0;k<q_info_;k++){
    ram2stu(22,k);
    prttext("<t10>");prtfld(22,4,-1);
    prttext("  ");prtfld(22,6,-1);
    prttext("  ");prtfld(22,10,-1);
    nextline();
  }
  nextline();
}
