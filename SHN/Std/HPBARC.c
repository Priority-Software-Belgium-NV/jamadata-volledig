/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* merge routines voor etiketten op hp-laser */
/* HpBarc.mer file 00.01 22/10/99 (c) Jamadata */

static char ean_bits[3][10][7] = {
/*
   EAN - A */
 
	0,0,1,1,0,1,0,
	0,1,1,0,0,1,0,
	0,1,0,0,1,1,0,
	1,1,1,1,0,1,0,
	1,0,0,0,1,1,0,
	1,1,0,0,0,1,0,
	1,0,1,1,1,1,0,
	1,1,1,0,1,1,0,
	1,1,0,1,1,1,0,
	0,0,1,0,1,1,0,
/*
   EAN - B */
 
	1,0,0,1,1,1,0,
	1,1,0,0,1,1,0,
	0,1,1,0,1,1,0,
	1,0,0,0,0,1,0,
	0,1,1,1,0,1,0,
	1,1,1,0,0,1,0,
	0,0,0,1,0,1,0,
	0,1,0,0,0,1,0,
	0,0,1,0,0,1,0,
	0,1,0,1,1,1,0,
/*
   EAN - C */
 
	1,1,1,0,0,1,0,
	1,1,0,0,1,1,0,
	1,1,0,1,1,0,0,
	1,0,0,0,0,1,0,
	1,0,1,1,1,0,0,
	1,0,0,1,1,1,0,
	1,0,1,0,0,0,0,
	1,0,0,0,1,0,0,
	1,0,0,1,0,0,0,
	1,1,1,0,1,0,0};

static char ean_set[10][6] = {
/*
    0->A    1->B */

	0,0,0,0,0,0,
	0,0,1,0,1,1,
	0,0,1,1,0,1,
	0,0,1,1,1,0,
	0,1,0,0,1,1,
	0,1,1,0,0,1,
	0,1,1,1,0,0,
	0,1,0,1,0,1,
	0,1,0,1,1,0,
	0,1,1,0,1,0
};

static char sep_bits[4] = {1,0,1,0};

static int16 lbreedte[64] = {116,240,240,245,245,226,208,260,244,95,188,245,202,285,
		    243,260,225,260,242,223,208,245,228,285,228,228,206,194,
		    210,173,215,173,145,194,219,108,132,219,112,321,219,194,
		    215,215,173,149,132,215,194,280,198,194,173,194,186,198,
		    194,198,194,194,194,194,194,150};

static prtean(x_pos,y_pos,x_size,y_size,yl_size,s)
int16 x_pos,y_pos, x_size, y_size, yl_size;
char *s;
{
  int16 k, set_ix, digit;
 
  if(*s=='\0') goto endsr;
  for(k=0;k<13;k++) if(*(s+k)=='\0') break;
  if(k==8){/* EAN 8 */
    prtean8(x_pos,y_pos,x_size,y_size,yl_size,s);
    goto endsr;
  }
  push();
  ean13c(s);
  set_ix=(s[0]-'0')%10;
  mov(x_pos,y_pos);
  bar_sep(x_size, yl_size);
  for (k=1; k<=6; k++) {
    digit=(s[k]-'0')%10;
    bar_unit(x_size, y_size,ean_bits[ean_set[set_ix][k-1]][digit]);
  }
  bar_sep(x_size, yl_size);
  for (k=7; k<13; k++) {
    digit=(s[k]-'0')%10;
    bar_unit(x_size, y_size,ean_bits[2][digit]);
  }
  bar_sep(x_size, yl_size);
  pop();
  endsr:;
}

static prtean8(x_pos,y_pos,x_size,y_size,yl_size,s)/* sp + 4(A) + sp + 4(C) + sp */
int16 x_pos,y_pos, x_size, y_size, yl_size;
char *s;
{
  int16 k, digit;
 
  if(*s=='\0') goto endsr;
  push();
  ean8c(s);
  mov(x_pos,y_pos);
  bar_sep(x_size, yl_size);
  for (k=0; k<=3; k++) {
    digit=(s[k]-'0')%10;
    bar_unit(x_size, y_size,ean_bits[0][digit]);
  }
  bar_sep(x_size, yl_size);
  for (k=4; k<8; k++) {
    digit=(s[k]-'0')%10;
    bar_unit(x_size, y_size,ean_bits[2][digit]);
  }
  bar_sep(x_size, yl_size);
  pop();
  endsr:;
}

static ean8c(p)
char *p;
{
  int16 k, sum,factor_;

  for (k=0; k<8; k++) {
    if (*(p+k)==0) return YES;
  }
  sum=0; factor_=3;
  for (k=6; k>=0; k--) {
    sum+=(*(p+k)-'0')*factor_;
    factor_=4-factor_;
  }
  *(p+7)='0'+(10-(sum%10))%10;
  return NO;
}
 
static prt_logo(x_pos,y_pos,filnam_,breedte_,hoogte_)
int16 x_pos, y_pos, breedte_,hoogte_;
char *filnam_;
{
  long size_=0,len_,pos_;
 
  if(fasopen(filnam_,1)) goto endsr;
  fasinit(80);
  FOREVER{
    if(fasseqi(80,1,256+4)) break;
  }
  size_=*l(80,1);
  if(size_==0) {fasclos(-2); goto endsr;}
  push();
  mov(x_pos,y_pos);
  prt_string("\x1B**"); prt_int(breedte_); prt_string("s");
  prt_int(hoogte_); prt_string("t");
  prt_long(size_); prt_string("W");
  fasinit(80);pos_=0;len_=256;if(len_>size_) len_=size_;
  FOREVER{
    *l(80,1)=pos_;
    fasseqi(80,1,len_+4);
    pos_+=len_;
    prt_bin(s(80,1)+4,len_);
    len_=size_-pos_;
    if(len_<=0) break;
    if(len_>256) len_=256;
  }
  fasclos(-2);
  pop();
  endsr:;
}

static logo(x_pos,y_pos,s,size)
char *s;
int16 x_pos, y_pos, size;
{
  push();
  mov(x_pos,y_pos);
  prt_bin(s,size);
  pop();
}
 
static ean13c(p)
char *p;
{
  int16 k, sum;

  for (k=0; k<12; k++) {
    if (*(p+k)==0) return YES;
  }
  sum=0;
  for (k=0; k<6; k++) {
    sum+=((*p-'0')+3*(*(p+1)-'0'));
    p+=2;
  }
  *p='0'+(10-(sum%10))%10;
  return NO;
}

static bar_sep(x_size,y_size)
int16 x_size,y_size;
{
  do_unit(x_size,y_size,sep_bits,4);
}

static bar_unit(x_size,y_size,bits)
char *bits;
int16 x_size, y_size;
{
  do_unit(x_size,y_size,bits,7);
}

static do_unit(x_size,y_size,bits,count)
int16 x_size, y_size, count;
char *bits;
{
  int16 ks, k,j;
 
  ks=0;
  FOREVER {
    for (k=ks; k<count; k++) {
      if (bits[k]) break;
    }
    for (j=k; j<count; j++) {
      if (!bits[j]) break;
    }
    if (k>0) mov(x_size*(k-ks),0);
    if (j>k) {
      prt_string("\x1B*c"); prt_int(x_size*(j-k)); prt_string("a");
      prt_string("*c"); prt_int(y_size); prt_string("b*c0P");
      mov(x_size*(j-k),0);
    }
    ks=j;
    if (ks==count) break;
  }
}

/* end specifiek barcode, rest hulp voor kaders e.d.
*/

static txt(size,x_pos,y_pos,ps_,attr)
char *ps_,*attr;
int16 size, x_pos, y_pos;
{
  int16 stroke_weight, style;
  char und=NO;
 
  stroke_weight=0;
  style=0;
  while (*attr) {
    if (*attr=='B') stroke_weight=3;
    else if (*attr=='I') style=1;
    else if (*attr=='U') und=YES;
    attr++;
  }
  push();
  mov(x_pos,y_pos);
  sel_prop(size,stroke_weight,style);
  if (und) prt_string("\x1B&d0D");
  prt_string(ps_);
  if (und) prt_string("\x1B&d@");
  pop();
}
 
static sel_prop(size,stroke_weight,style)
int16 size,stroke_weight,style;
{
  prt_string("\x1B(s1p(s"); prt_int(size); prt_string("v"); prt_int(style); prt_string("s");
  prt_int(stroke_weight); prt_string("B");
}

static box(dikte, x_pos,y_pos,x_len,y_len)
int16 dikte, x_pos, y_pos, x_len, y_len;
{
  push();
  mov(x_pos-dikte/2,y_pos-dikte/2);
  prt_string("\x1B*c"); prt_int(x_len+dikte); prt_string("a");
  prt_string("*c"); prt_int(dikte); prt_string("b*c0P");
  prt_string("\x1B*c"); prt_int(dikte); prt_string("a");
  prt_string("*c"); prt_int(y_len+dikte); prt_string("b*c0P");
  mov(x_len,0);
  prt_string("\x1B*c"); prt_int(dikte); prt_string("a");
  prt_string("*c"); prt_int(y_len+dikte); prt_string("b*c0P");
  mov(-x_len,y_len);
  prt_string("\x1B*c"); prt_int(x_len+dikte); prt_string("a");
  prt_string("*c"); prt_int(dikte); prt_string("b*c0P");
  pop();
}

static block(rast,x_pos,y_pos,x_len,y_len)
int16 rast, x_pos, y_pos, x_len, y_len;
{
  push();
  prt_string("\x1B*c"); prt_int(rast); prt_string("G");
  mov(x_pos,y_pos);
  prt_string("\x1B*c"); prt_int(x_len); prt_string("a");
  prt_string("*c"); prt_int(y_len); prt_string("b*c2P");
  pop();
}
 
static push()
{
  prt_string("\x1B&f0S");
}

static pop()
{
  prt_string("\x1B&f1S");
}
 
static mov(x_pos,y_pos)
int16 x_pos, y_pos;
{
  if (x_pos<0) {
    prt_string("\x1B*p-"); x_pos=-x_pos;
  }
  else prt_string("\x1B*p+");
  prt_int(x_pos); prt_string("x");
  if (y_pos<0) {
    prt_string("*p-"); y_pos=-y_pos;
  }
  else prt_string("*p+");
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

static prt_long(getal)
long getal;
{
  char buf[20];
  int16 j;
									
  stcli_d(buf,(long)getal,7,1);
					      /*  sprintf(buf,"%5d",getal); */
  for (j=0; j<sizeof(buf); j++) {
    if (buf[j]>='0' && buf[j]<='9') {prt_string(&buf[j]); break;}
  }
}

static cent_txt(dikte_,bpos_,epos_,ps_)
char *ps_;
int16 dikte_,bpos_,epos_;
{
  int16 j,pos_;
  char kar_;
  float qpunten_;

  j=0; qpunten_=0;
  FOREVER{
    kar_=*(ps_+j++);
    if(kar_=='\0') break;
    if(kar_==' ') qpunten_+=lbreedte[0];
    else if(kar_>='A' && kar_<='Z') qpunten_+=lbreedte[1+(kar_-'A')];
    else if(kar_>='a' && kar_<='z') qpunten_+=lbreedte[27+(kar_-'a')];
    else if(kar_>='0' && kar_<='0') qpunten_+=lbreedte[53+(kar_-'0')];
    else qpunten_+=lbreedte[63];
  }
  if(dikte_) qpunten_=(qpunten_* ((float)dikte_/90.))+.49;
  pos_=(epos_-bpos_-qpunten_)/2;
  if(pos_<0) pos_=bpos_; else pos_+=bpos_;
  return pos_;
}

static pal_str(dst_,src_,len_)   // veld -> string, zoals zeros+copy+cnv_char in prt_etik
char *dst_,*src_;
int16 len_;
{
  zeros(dst_,50);
  if(len_>49) len_=49;
  copy(src_,dst_,len_);
  CnvJamaChar(dst_,len_,0);
}

static pal_breedte(dikte_,ps_)   // breedte van tekst in punten (zelfde rekenwijze als cent_txt)
char *ps_;
int16 dikte_;
{
  int16 j=0;
  char kar_;
  float qpunten_=0;

  FOREVER{
    kar_=*(ps_+j++);
    if(kar_=='\0') break;
    if(kar_==' ') qpunten_+=lbreedte[0];
    else if(kar_>='A' && kar_<='Z') qpunten_+=lbreedte[1+(kar_-'A')];
    else if(kar_>='a' && kar_<='z') qpunten_+=lbreedte[27+(kar_-'a')];
    else qpunten_+=lbreedte[63];
  }
  return (int16)(qpunten_*((float)dikte_/90.)+.49);
}

static pal_txt(dikte_,bpos_,epos_,vpos_,ps_,attr_,centreer_)   // tekst, automatisch kleiner als hij niet past
int16 dikte_,bpos_,epos_,vpos_,centreer_;
char *ps_,*attr_;
{
  while(dikte_>8 && pal_breedte(dikte_,ps_)>(epos_-bpos_)) dikte_--;
  if(centreer_) bpos_=cent_txt(dikte_,bpos_,epos_,ps_);
  txt(dikte_,bpos_,vpos_,ps_,attr_);
}
