/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* shn */
/* bonbeheer */
/* soort program */
#define FLAG244         YES
/* modules voor dit soort program */
#define BOEKEXEC        NO
#define FICHEEXEC       NO
#define HANDTEKENING    NO
#define HISTUPEXEC      NO
#define KONTRUPEXEC     NO
#define PRINTEXEC       YES
#define PRTBDR          YES
#define SCREXEC         YES

//#undef  FIRMAPRT
//#define FIRMAPRT        YES
//#undef  EMPTYBLAD
//#define EMPTYBLAD       YES
 
#define SCRNUM          101
#if FLAG240E
extern char *facttxt[];
extern char *credntxt[];
#else
static char *facttxt[4] = {"Leveringsbon","Note d'envoi","Delivery note","Lieferungsschein"};
static char *credntxt[4]= {"Leveringsbon","Note d'envoi","Delivery note","Lieferungsschein"};
#endif
