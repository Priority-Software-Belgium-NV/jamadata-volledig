/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH0001GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH0001dat
#define ovlcod BKH0001cod
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

char ovldat[] = "bkh0001  00:06 25/05/07 (c) Jamadata";

#define FOREVER         while(1)
#define YES             1
#define NO              0

ovlcod()
{
  int16 k;

//	ovlcall(3000,0);
	

  if(sysopen("","")) {sys_err(108,0); FOREVER reschedule();}
  sysget(3678,2,&k);                                                /* taal */
  if(k){
    if(scropen(1,"bscr.FRA")){
      scropen(1,"bscr.scr");
    }
  }
  else scropen(1,"bscr.scr");
  scropen(2,"sscr.scr");
	fasclos(-2); // om na een blokkage de files te releasen 
  ovlexit(9);
}
