/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0006GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0006dat
#define ovlcod BKH0006cod
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

char ovldat[] = "bkh0006  00:14 02/08/10 (c) Jamadata";
 
#define FOREVER         while(1)
#define YES             1
#define NO              0

extern int16 prc_num[];
extern int16 jamin1[];
extern uint16 procid;
extern char info[];

static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_ol3[]   = {6,0x93,3,0,0x70,0};
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_count[] = {6,0xD0,5,0,0x20,0};

extern int16 jamin1[];
static char filname[15];
static uint16 do_count,real_cnt;
static long tick_beg,tick_end,tot_qget;

extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l();
static long get_aantal(),getticks();
extern float *f();
extern double *d();
static int16 stu;
static int16 def_taal;

ovlcod()
{

  initload();
  disp_new();
  ovlexit(*u(25,4));
}

static disp_new()
{
  int16 j,z,key,offset_;
  long aantal_,max_aantal_,warn_aantal_;
	char max_str_[30];

	if(ServerVersion==SERVER_MONO && StdInMono==0) max_aantal_=60000;
	else if(ServerVersion==SERVER_LIGHT || StdInMono) max_aantal_=120000;
	else max_aantal_=10000000;// oneindig
	warn_aantal_=max_aantal_*0.9; // op 90% in het rood zetten
	zero(max_str_,sizeof max_str_); 
	if(max_aantal_<=120000){copy("Max. aantal : ",max_str_,14);stcli_d(&max_str_[14],max_aantal_,6,1);}
  redo:;
  scrnum=0; scrget(1,247);z=1;
	if(max_aantal_<=120000){scraddf(101,23,15,2);scrifld(101,fm_os20,max_str_);} // Limiet db tonen 
  if(do_count){
    scraddf(100,23,75,2);
    scrifld(73,fm_os15,"Berekenen ..."); scrupd(-3,0);
    tick_beg=getticks();tot_qget=0;
  }
  /* scrofld(z++,25,2,-1); */offset_=1;
  for(j=0;j<15;j++){
    sysget(300+17*j,15,filname);
    sysget(315+17*j,2,&stu);
    if(filname[0]){
      z=offset_;
      if(fasopen(filname,0)){
				scrifld(z++,fm_os15,filname);
				scrifld(z++,fm_os5,"FOUT!");
				for(z=offset_;z<offset_+2;z++) scrchat(z,0xB);
				offset_+=4; if(offset_>=72) offset_=3;
      }
      else{
				fasinit(stu);fasinfo(stu,7);scrifld(z++,fm_os20,s(stu,1));
				aantal_=get_aantal(stu); scrifld(z++,fm_ol8,&aantal_);
				offset_+=4; if(offset_>=72) offset_=3;
				FOREVER{
					fasinfo(stu,5);/* nog structuren in deze file ? */
					stu=*u(stu,1);
					if(stu==0) break;
					z=offset_;
					fasinit(stu);fasinfo(stu,7);scrifld(z++,fm_os20,s(stu,1));
					aantal_=get_aantal(stu); scrifld(z++,fm_ol8,&aantal_);
					if(aantal_>=warn_aantal_){ // in het rood zetten 
						for(z=offset_;z<offset_+2;z++) scrchat(z,0xB);
					}
					scrupd(-3,0);
					offset_+=4; if(offset_>=72) offset_=3;
				}
      }
      fasclos(-4);
    }
  }
  if(do_count){
    tick_end=getticks();
    if(((tick_end-tick_beg)*55)!=0){
      aantal_=tot_qget/((tick_end-tick_beg)*55);
      scrifld(100,fm_ol3,&aantal_);scrupd(-3,0);
    }
    scrifld(73,fm_os15,"Echte aantallen");scrchat(73,0x2);
  }
  key=scrupd(-1,0x04C9);
  if(key==107) {do_count=YES;goto redo;}
  if(key==104) fasinfo(80,1102);
  ovlexit(*u(25,4));
}

static long get_aantal(stu_)
int16 stu_;
{
  long n,g,cnt,len1_;
									
  len1_=fldlen(stu_,1);
  if(do_count==NO) {
    fasinfo(stu_,6);
    if(len1_==4) cnt=*l(stu_,1); else cnt=*u(stu_,1);
  }
  else{
    fasinit(stu_); n=0; cnt=0;
    FOREVER{
      if(len1_==4) *l(stu_,1)=++n; else *u(stu_,1)=++n;
      g=fasgeti(stu_);
      tot_qget++;
      if(g==47)break;
      if(g!=46){cnt++; }/* deleted record */
    }
    if(len1_==4) *l(stu_,1)=cnt; else *u(stu_,1)=cnt;
    real_cnt=cnt;
  }
  return cnt;
}
 
static initload()
{
  sysget(3678,2,&def_taal);
								
}
 
static long getticks()
{
  long ticks;

  jamin1[0]=0x1A;
  jamin1[1]=0;
  jamint();
  ticks=(jamin1[3]*0x10000L)+jamin1[4];
  return ticks;
}
 
static scraddf(fld,v,h,attr)
int16 fld,v,h,attr;
{
  int16 *pi;
					
  pi=(int16 *)info;
  *(pi+0)=fld;
  *(pi+1)=v;
  *(pi+2)=h;
  *(pi+3)=attr;
  sendtask(procid+20,3,11,info,8);
  scrnum=0;
}
