/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* print-routine voor inktjet-printer */
/* DjPCL3.mer file 00.01 18/05/95 (c) Jamadata */

static txt_abs(size,x_pos,y_pos,s,attr)
char *attr;
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
  mov_abs(x_pos,y_pos);
  sel_prop(size,stroke_weight,style);
  if (und) prt_string("\x1B&d0D");
  prt_string(s);
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
