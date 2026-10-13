/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* drk */
/* bon-module voor aanmaken leveringsbons vanuit KeyConen-kassa via ovlcall vanuit ovl0900 */
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
 
#define KAS2JMCBON      YES
#define KAS2JMC_DISPLAY_EINDE   NO  // toon eindscherm 
#undef  DEF_INPUT
#define DEF_INPUT				NO
#undef  CONTRACT
#define CONTRACT				NO

#define SCRNUM          101

#if 0 
#undef  FIRMAPRT
#define FIRMAPRT        YES
#undef  EMPTYBLAD
#define EMPTYBLAD       YES
#undef  LAYOUT
#define LAYOUT          NO
#endif

#if FLAG240E
extern char *facttxt[];
extern char *credntxt[];
#else
static char *facttxt[4] = {"Leveringsbon","Note d'envoi","Delivery note","Lieferungsschein"};
static char *credntxt[4]= {"Leveringsbon","Note d'envoi","Delivery note","Lieferungsschein"};
#endif
