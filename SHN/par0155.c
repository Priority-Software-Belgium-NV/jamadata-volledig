/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* kee */
#define FLAG155         YES
#define ARTEXIST        YES
#define BACKORDER       YES
#define BOEKALLO        NO/* maak een interne diversen boeking */
#define BOEK_JOURNL     95/* diversen journaal voor boeking */
#define B_LST_BON       YES
#define DOUBLE_RAM      NO/* verdubbel aantal lijnen via wrk-manager */
#define DOUBLE_FACT     3                              /* verdubbel-factor  */
#define EMPTYBLAD       YES
#define FIRMAPRT        YES
#define HISTOR          NO
#define LAYOUT          YES
#define PDA_INPUT       YES             /* invullen uit bestand moblogBS.dat */
#define STATISTIEK      NO
#define USE_2ADR        NO
#define VREEMMUN        NO

#define PRINTEXEC       YES
#define PRTBDR          NO
#define THISTYP         20
#define PREVTYP         0
#define DT_EXEC0        NO
#define LAST_VFA        3924
#define SCRNUM          104
 
static char *facttxt[4] = {"Leveringsbon","Bon de commande","Orderform","Bestellung"};
static char *credntxt[4]= {"Leveringsbon","Bon de commande","Orderform","Bestellung"};
 
#define D_LIN_SCR        15
#define DEFLVPRT        'J'
 
 
