/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* dr1 */
/* bekijken/afdrukken gemaakte facturen */
/* soort program */
#define FLAG248         YES
/* modules voor dit soort program */
#define BOEKEXEC        YES
#define FICHEEXEC       NO
#define HISTUPEXEC      YES
#define KONTRUPEXEC     YES
#define PRINTEXEC       YES
#define PRTBDR          YES
#define SCREXEC         YES
/* speciale facturatie rechtstreeks */

#undef  ARTEXIST
#define ARTEXIST        NO
#undef  BONFILE
#define BONFILE         NO
#undef  FT_HERAFDRUK
#define FT_HERAFDRUK    YES
 
#define SCRNUM          24
#if FLAG240E
extern char *facttxt[];
extern char *credntxt[];
#else
static char *facttxt[4] = {"Factuur","Facture","Invoice","Rechnung"};
static char *credntxt[4]= {"Creditnota","Note de cr…dit","Creditnote","Creditnota"};
#endif
