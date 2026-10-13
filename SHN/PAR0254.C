/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* dr1 */
/* facturatie leveringsbons van kassa */
/* soort program */
#define FLAG248         YES
/* modules voor dit soort program */
#define BOEKEXEC        YES
#define FICHEEXEC       YES
/* stock is reeds in kas aangepast */
#define HISTUPEXEC      YES
#define KONTRUPEXEC     YES
#define PRINTEXEC       YES
#define PRTBDR          YES
#define SCREXEC         YES
#define STOCK_UPD       NO
#undef  NO_ART_UPD
#define NO_ART_UPD      YES/* GEEN artikelfiche updaten (stock, omzet..) */
				
#define THISTYP         180
#define PREVTYP         120
#define DT_EXEC0        YES
#define LAST_VFA        3718

/* speciale facturatie vanuit kas */
#undef  BONFILE
#define BONFILE         NO
#undef  KASINPUT
#define KASINPUT        YES
/* indien enkel inboeken van KLEINE facturen
#undef  BOEKKASF
#define BOEKKASF        YES                      // Inboeken kassa-facturen
*/
 
#undef  CONTRACT
#define CONTRACT        NO/* wegens plaatsgebrek !!! */
#undef  STATISTIEK
#define STATISTIEK      NO                       /* wegens plaatsgebrek !!! */
#undef  DEF_INPUT
#define DEF_INPUT       NO                       /* wegens plaatsgebrek !!! */

 
#define SCRNUM          24
#if FLAG240E
extern char *facttxt[];
extern char *credntxt[];
#else
static char *facttxt[4] = {"Factuur","Facture","Invoice","Rechnung"};
static char *credntxt[4]= {"Creditnota","Note de cr…dit","Creditnote","Creditnota"};
#endif
