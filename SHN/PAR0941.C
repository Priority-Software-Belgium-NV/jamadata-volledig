/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* dem */
/* facturatiemodule voor rechtstreekse facturatie vanuit KeyConen-kassa via ovlcall vanuit ovl0900  */
/* soort program */
#define FLAG248         YES
/* modules voor dit soort program */
#define BOEKEXEC        YES
#define FICHEEXEC       YES
#define HISTUPEXEC      YES
#define KONTRUPEXEC     YES
#define PRINTEXEC       YES
#define PRTBDR          YES
#define SCREXEC         NO

#define KAS2JMCFACTUUR   YES
#undef  DEF_INPUT
#define DEF_INPUT				NO
#undef  CONTRACT
#define CONTRACT				NO
#undef  BONFILE
#define BONFILE         NO

#undef  FACT2CODABOX    
#define FACT2CODABOX    NO /* factuur uitschrijven in UBL en versturen via CodaBox, DRK2240 moet bestaan! */

#define SCRNUM          24
#if FLAG240E
extern char *facttxt[];
extern char *credntxt[];
#else
static char *facttxt[4] = {"Factuur","Facture","Invoice","Rechnung"};
static char *credntxt[4]= {"Creditnota","Note de cr…dit","Creditnote","Creditnota"};
#endif
