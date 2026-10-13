#define _WIN32_WINNT 0x0501

#include "afxwin.h"

#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;

#define  UseJMS	true
#define  OvlCpp true
#include "JamaConL.h"
#include "markup.h"

#define FOREVER         while(1)
#define YES             1
#define NO              0

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;

extern "C" int16 procid;
extern "C" int16 prc_num[];
extern "C" int16 busy_cnt;
extern "C" short int ThisPostNr;
extern "C" short int ThisScreenNr;
extern "C" unsigned short jamin1[];
extern "C" char info[];
extern "C" int16 retcall;
extern "C" int16 parmcall[];
extern "C" int16 reqproc, ilength;
extern "C" short int JMC4TEST;

extern "C" struct {
  int16 len;
  char *info;
} tab[];

extern "C" struct{
  char fval[4];
  char tval[4];
  double coef;
} vtab[];

extern "C" void reschedule();
extern "C" void sys_err(short int code,short int parm);
extern "C" short int ovltest(short int number);
extern "C" short int ovlexit(short int nr);
extern "C" short int ovlcall(short int nr,unsigned short bits);
extern "C" void sendtask(short int destprc,short int type,short int function,char *info,short int len);

extern "C" void waittask(int16 typ, int16 fun);
extern "C" void sleep(int16 procid, int16 stat);
extern "C" void copy(char *s, char *d, int16 len);
extern "C" void zeroL(char *p, long len);
extern "C" void zero(char *p, int16 len);
extern "C" double valu_cnv(char *ps_van_,char *ps_naar_,double bd_,double bd_afr_);

// Nieuwe routines (in OvlHand.CPP) 

CString JmsCmd(CString Cmd);