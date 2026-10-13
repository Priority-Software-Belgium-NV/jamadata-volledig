/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* drk */
/* toerlijsten */
/* soort program */
#define FLAG252         YES
/* modules voor dit soort program */
#define BOEKEXEC        NO
#define FICHEEXEC       NO
#define HANDTEKENING    NO
#define HISTUPEXEC      NO
#define KONTRUPEXEC     NO
#define PRINTEXEC       YES
#define PRTBDR          YES
#define SCREXEC         NO


#define BONLIST2XLS     YES /* ovl0252 : mogelijkheid om bons uit te schrijven voor Dropon */
 
//#undef  FIRMAPRT
//#define FIRMAPRT        YES
//#undef  EMPTYBLAD
//#define EMPTYBLAD       YES
#if 0
#undef  LAYOUT
#define LAYOUT          NO
#endif

#define SCRNUM          101
#if FLAG240E
extern char *facttxt[];
extern char *credntxt[];
#else
static char *facttxt[4] = {"Leveringsbon","Note d'envoi","Delivery note","Lieferungsschein"};
static char *credntxt[4]= {"Leveringsbon","Note d'envoi","Delivery note","Lieferungsschein"};
#endif
