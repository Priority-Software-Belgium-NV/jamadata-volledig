/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* shn */
/* facturatie vanuit bons */
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
 
#define SCRNUM          24
#if FLAG240E
extern char *facttxt[];
extern char *credntxt[];
#else
static char *facttxt[4] = {"Factuur","Facture","Invoice","Rechnung"};
static char *credntxt[4]= {"Creditnota","Note de cr…dit","Creditnote","Creditnota"};
#endif
