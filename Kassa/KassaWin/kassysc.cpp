// KasSYSc.cpp: implementation of the CKasPLU class.
//
//////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4996)

// #define WINVER 0x0501  // was 500
// #define _WIN32_WINNT 0x0501  // was 500


#include "p:\jamacon\library\JamaConL.h"
#include "kashead.h"
#include "KasSYSc.h"

//#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int fref_sys=-1;

CKasSYS::CKasSYS()
{
}

CKasSYS::~CKasSYS()
{
}


extern int epson_fl;
extern char *txtfin[], txttxt[200][150], Ftxttxt[200][150], *txtbet[], *Ftxtbet[], *txtdag[], *Ftxtdag[], *txtmnd[], *Ftxtmnd[];
                
char bpi_file[64] = "kaslay.bpi";
int groep_leeg = 99;
int prtbnum=1;
int pen_delay=0;
int prtnum=0, NoPrtCut=0, DefNoPrtCut=0;
int herctab[10];
int ss1_delay=10, ss2_delay=20;
short int leeg_sys[10]={1,3,0,0,0,0,0,0,0,0};
short int prx_sys[10]={0,0,0,0,0,0,0,0,0,0};
short int vrk_lade [10] = {1,2,3,1,1,1,1,1,1,1};
short int ex_ticket;
unsigned tick_type, kaslogfl;
int comnr_lade = 1;
int lade_aantal=1;
int PWOpenLade=0;
int chk_kassier=0;
int notime_fl=0;
int no_prtkas,fl_freedelity, fl_KasCtrl, SoortKassa;
char weeg_lead[4], weeg_type, weeg_cpos, weeg_clen;
char tomra_lead[5], tomra_path[33], tomra_plu[11];
char weeg_epos, weeg_elen, weeg_edig;
int lijn_round;
int not_check;
int testmax;
int leegok;
char back_file[60];
int back_time;
struct s_valuta {
  char naam[4];
  float coeff;
  char lade;
  char digits;
} valuta[10] = {"EUR",1.,1,2,"EUR",1.,1,2,"EUR",1.,1,2,"EUR",1.,1,2,
                "EUR",1.,1,2,"EUR",1.,1,2,"EUR",1.,1,2,"EUR",1.,1,2,
                "EUR",1.,1,2,"EUR",1.,1,2};
struct s_valuta2 {
  float round;
  char dummy[6];
} valuta2[10];
float def_round, btw_round;
char def_valuta[4], TotaalOp5CentAfronden, PromoNotOnHorecaPrice;
int def_digits, EigenPrijsOpStuksAllowed;
int ladetype=0;
double BedragTotaalafronding=0; 
long dag_aantal=100;
long rec_aantal=30000;
int cf_cont=0, cf_art=1, cf_groep=1, cf_btw=1, cf_financ;
int cf_periode=0;/* 0=allemaal, 1=enkel selectie, 2=van eerste t/m laatste */
int cf_cumper=1;/* 0=ganse periode, 1=dag, 2=week, 3=maand */
int tf_dagres=0;/* ticket# elke dag resetten */
int cf_vkptype=0;/* 0=allemaal, 1 partik., 2 bons/fakt., 3 apart */
int cf_verknr=0;/* 0=allemaal, 1 verk. A, 2 = B, 3 = C */
unsigned faktnr=0;/* laatst gebruikt faktuurnummer */
int fakt_allow=0;
int teg_allow=0;/* tegoedbons allowed, def. is NEE */
int bc_option=0;/* barcode option installed */
int prx_count=1;/* aantal prijzen (buiten st-prijs) */
int fl_open_lade;/* Geldlade opening loggen (1) of niet (0) */
int specialfl=0; // bit 0 -> Kredietknop altijd tonen B1 ->enkel indien gemarkeerde klant (met !)
int art_count=2000;
int key_count=2000;
int plulink=0;  // Koppelingsvelden in kasplu beteken : 0 -> leeggoed, 1 -> optie vragen
int optiesgroep=0;
int optiestype=0; // bit 0 -> Opties activeren  bit 1 -> eenheidsprijs artikel aanpassen met optie
int ep_digits=0; // standaard 0 -> neem aantal digits over van valuta
int tafel_cnt;  // Aantal tafels : zo 0->klassieke bons, anders aantal. Niet meer dan 30 !!!
int HoursOpenAfterMidnight=0;    
float BTWBONPercentage=0.;   // bv. voor bereide maaltijden ter plaatse gegeten 12 %
float BTWBONDrankPercentage=0.;   // bv. voor drank bij bereide maaltijden ter plaatse gegeten 21 %
int DrankGroep=0;  // om groep te selecteren voor drank (zie BTWBONDrankPercentage).
int krt_count=0;
int euroticket=0;
int krtsort=0;
int krt_bits=0;
char krt_lead[6];
int ext_count=0;/* aantal extra in te lezen EAN-codes */
long lay_workspace=75000L;
int btw_holland;/* btw-berekening op elk kaseticket ? */
int totflags;/* Flags over layout kastotalen : bit 0 = 1 dan tijd & datum op kastotalen (van F9)
                                                   1 = 1 dan GEEN tot per klant  */
int MapEuroChequeFlag=0; // 1-> PIN
int XZTotaalDispFlag=0; // 1-> display toets
int ConfigFlags=0; // diverse configuratie bits
int contflag;
int kortflag;
int TaalTicket; // 1=Frans
int PrtOnWRKPutFlag,KeepWRKBon420,PromoOpStuksAllowed;
int MenuKeyDifColor, PromoKeyDifColor;
char wrkpath[64];
char TicketShare[81], LaserShare[81],TextVarBetWijze[3][11];
char PayCardServer[32];
char PluCreditCost[11],CreditCardViaBetaalterminal;
char HDDSerialNr[20];					 
int MinFreeCreditCost;
int pcl3flag=0;
int VKPDADisplayBlockedFlag=0;
int KeyboardType=0; // 0-> ABCD  1->AZERTY

float krtperc, krtfull, krtvalue;
 
char prt_head[10][41] = {
  "       Drinkservice 't Computerke       ",
  "          Tel.: 011/440.775            ",
};
char prt_foot[2][41];

char prt_krtfull[5][41] = {
  "*                                       ",
  "       text can be changed by           ",
  "       using kasparm.exe                ",
  "*                                       ",
  "                                        ",
};

char reclame[6][11][22] = {
  "                     ",
  "                     ",
  "                     ",
  " This text can be    ",
  " changed by using    ",
  "     KASPARM         ",
};

char txt_tegoedbon[5][41];
char fakt_head[20][51];
char fakt_vtekst[3][81];
int  fakt_dist, fakt_sp1;

char grp_bits[100];
 
struct {
  char promo;
  char gratis; /// ?????
  char sortnr;
  char dummy[7];
} grp_extra[100];
 
struct {
  short int formule;
  float getal[4];
  char dummy[7];
} promo_desc[20];
 
struct s_grp_info {
  char naam[20];
  float btw;
} grp_info[100];
 
struct layout bet_layout[30] =
{
  22,52, 2,28,3,
  38,52, 6, 8,3,
  41,72, 6, 8,3,
  37,52,10, 8,3,
  40,62,10, 8,3,
  16,72,10, 8,3,
  36,52,14,28,3,
  35,52,18,28,3,
  39,52,22,28,3,
};

struct layout bet_krediet =
{ 78,62,6,8,3
};
 
struct layout keyb_layout[60] =
{
  2000+'A', 4,17,3,1,
  2000+'B', 8,17,3,1,
  2000+'C',12,17,3,1,
  2000+'D',16,17,3,1,
  2000+'E',20,17,3,1,
  2000+'F',24,17,3,1,
  2000+'G',28,17,3,1,
  2000+'H',32,17,3,1,
  2000+'I',36,17,3,1,
  2000+'J',40,17,3,1,
  2000+'K', 4,19,3,1,
  2000+'L', 8,19,3,1,
  2000+'M',12,19,3,1,
  2000+'N',16,19,3,1,
  2000+'O',20,19,3,1,
  2000+'P',24,19,3,1,
  2000+'Q',28,19,3,1,
  2000+'R',32,19,3,1,
  2000+'S',36,19,3,1,
  2000+'T',40,19,3,1,
  2000+'/', 4,21,3,1,
  2000+'-', 8,21,3,1,
  2000+'U',12,21,3,1,
  2000+'V',16,21,3,1,
  2000+'W',20,21,3,1,
  2000+'X',24,21,3,1,
  2000+'Y',28,21,3,1,
  2000+'Z',32,21,3,1,
  2000+'.',36,21,3,1,
  2000+',',40,21,3,1,
  57     ,12,23,23,1,
  58     ,40,23, 3,1,
  73     ,50,17, 9,1,
  59     ,50,19, 4,1,
  60     ,55,19, 4,1,
  61     ,50,21, 4,1,
  62     ,55,21, 4,1,
  63     ,50,23, 9,1,
  2000+'7',66,17,3,1,
  2000+'8',70,17,3,1,
  2000+'9',74,17,3,1,
  2000+'4',66,19,3,1,
  2000+'5',70,19,3,1,
  2000+'6',74,19,3,1,
  2000+'1',66,21,3,1,
  2000+'2',70,21,3,1,
  2000+'3',74,21,3,1,
  2000+'0',66,23,7,1,
  2000+'.',74,23,3,1,
};

struct layout key_layout[100] =
{
  18, 1, 0, 8, 1,
  13, 1, 6, 8, 3,
   7, 1,10, 8, 3,
   4, 1,14, 8, 3,
   1, 1,18, 8, 3,
   0, 1,22, 8, 3,
  74,11,22, 3, 3,
  75,16,22, 3, 3,
  19,11, 0, 8, 1,
  14,11, 6, 8, 1,
  21,11, 8, 8, 1,
   8,11,10, 8, 3,
   5,11,14, 8, 3,
   2,11,18, 8, 3,
  20,21, 0, 8, 1,
  53,21, 6, 8, 3,
   9,21,10, 8, 3,
   6,21,14, 8, 3,
   3,21,18, 8, 3,
  10,21,22, 8, 3,
  26,31, 0, 8, 1,
  15,31, 6, 8, 3,
  17,31,10, 8, 3,
  12,31,14, 8, 3,
  11,31,18, 8, 3,
  32,31,22, 8, 3,
  27,41, 0, 8, 1,
  42,41, 6, 8, 3,
  30,41,10, 8, 1,
  31,41,12, 8, 1,
  33,41,14, 8, 1,
  52,41,16, 8, 1,
  54,41,18, 8, 1,
  43,41,20, 8, 1,
  34,41,22, 8, 3,
  28,52, 0, 8, 1,
1017,52, 2, 1, 0,
1033,52, 6, 1, 0,
1049,52,10, 1, 0,
1065,52,14, 1, 0,
1081,52,18, 1, 0,
1097,52,22, 1, 0,
  29,62, 0, 8, 1,
1018,62, 2, 1, 0,
1034,62, 6, 1, 0,
1050,62,10, 1, 0,
1066,62,14, 1, 0,
1082,62,18, 1, 0,
1098,62,22, 1, 0,
  56,72, 0, 8, 1,
1019,72, 2, 1, 0,
1035,72, 6, 1, 0,
1051,72,10, 1, 0,
1067,72,14, 1, 0,
1083,72,18, 1, 0,
1099,72,22, 1, 0
};


/* --------------------------- Declaratie functies ---------------------- */

////////////////

void CKasSYS::readmem(long lpos, void *s, unsigned len)
{
  char *pd;
  long size;
	char *p;

  if (fref_sys<=0) return;

	p=(char *)s;
  pd = p;                      
  dseek(fref_sys,lpos,0);
  while(len){
    size=len;
    if(size>30000) size=30000;
    dread(fref_sys,pd,(int)size);
    pd+=size;
    len-=size;
  }
}

void CKasSYS::rd_kassys(int line)
{
  int i, k;
 
  SplashText("Reading KASSYS.DAT ...");
  fref_sys=dopen("kassys.dat",RDWRMODE);
  if (fref_sys<0) goto end;
  readmem( 64L,&bpi_file,64);
  readmem(512L,&grp_info,2400);
  readmem(2912L,&grp_bits,100);
  readmem(3012L,&back_file,58);
  readmem(3070L,&back_time,2);
  readmem(3072L,&comnr_lade,2);
  readmem(3074L,&herctab,10*sizeof(int));
  readmem(3094L,&tick_type,2);
  readmem(3096L,&lade_aantal,2);
  readmem(3098L,&valuta,50);
  for (k=0; k<5; k++) {
    for (i=0; i<sizeof(valuta[0].naam); i++) {
      if (valuta[k].naam[i]>='a' && valuta[k].naam[i]<='z') valuta[k].naam[i]+=('A'-'a');
    }
  }
  readmem(3198L,&teg_allow,2);
  readmem(3200L,&leeg_sys,20);
  readmem(3220L,&prx_sys,20);
  readmem(3240L,vrk_lade,20);
  readmem(3260L,&ladetype,2);
  readmem(3262L,&bc_option,2);
  readmem(3264L,&art_count,2);
  readmem(3266L,&key_count,2);
  readmem(3268L,&lay_workspace,4);
  readmem(3272L,&pen_delay,2);
  readmem(3274L,&ext_count,2);
  readmem(3276L,&testmax,2);
  readmem(3278L,&leegok,2);
  readmem(3280L,&krt_count,2);
  readmem(3282L,&euroticket,2); if (euroticket==0) euroticket=1;
  readmem(3284L,&kortflag,2);
  readmem(3286L,wrkpath,64);
  readmem(3350L,&plulink,2);
  readmem(3352L,&tafel_cnt,2);
  readmem(3354L,&HoursOpenAfterMidnight,2);
  readmem(3356L,&BTWBONPercentage,4);  // bv. voor bereide maaltijden ter plaatse gegeten 12 % na 1/1/10
  readmem(3360L,&PrtOnWRKPutFlag,2);
  readmem(3362L,&optiesgroep,2);
  readmem(3364L,&optiestype,2);
  readmem(3366L,&ep_digits,2);
	readmem(3368L,PayCardServer,32);
	readmem(3400L,&MapEuroChequeFlag,2);
	readmem(3402L,&KeyboardType,2);
	switch (MapEuroChequeFlag) {
	  case 1:
		  txtfin[8]="PIN";
			txtbet[7]=txtfin[8];
			break;
	}
	bcopy("CashAut",GetPtrTxtKey(41),8);
  if (kortflag==1) bcopy("E-SUBTOT",GetPtrTxtKey(32),9);

	readmem(3404L,&XZTotaalDispFlag,2);
	readmem(3406L,&PluCreditCost,5); PluCreditCost[5]=0; // is 11 bytes long
	readmem(3415L,&CreditCardViaBetaalterminal,1); 
	readmem(3416L,&VKPDADisplayBlockedFlag,1); 
	readmem(3417L,&MinFreeCreditCost,2);
	readmem(3419L,&PromoKeyDifColor, 1);
	readmem(3420L,&DrankGroep,2); // groepnummer van de dranken (zie hieronder)
  readmem(3422L,&BTWBONDrankPercentage,4);  // BTW voor drank bij bereide maaltijden ter plaatse gegeten 21 na 1/1/10 %
	readmem(3426L,&ConfigFlags,2);
	readmem(3428L,&KeepWRKBon420,2); 
	if(KeepWRKBon420){ // wrk-bonnen 1=laatste 70, 2=laatste 140... NIET  deleten na opladen (=zelfde biermanden)
		if(KeepWRKBon420<1 || KeepWRKBon420>5) KeepWRKBon420=1; 
		KeepWRKBon420=490-70*KeepWRKBon420; // echt als vanaf-nr zetten
	}
	readmem(3430L,&PromoOpStuksAllowed, 2);
	readmem(3432L,&TaalTicket, 2);
	if(TaalTicket==1){
		bcopy(Ftxttxt,txttxt,sizeof txttxt);
		for(k=0;k<35;k++) txtbet[k]=Ftxtbet[k];
		for(k=0;k<7;k++) txtdag[k]=Ftxtdag[k];
		for(k=0;k<12;k++) txtmnd[k]=Ftxtmnd[k];

	}
	readmem(3470L,&btw_round,4); if (!btw_round) btw_round=1.;
  readmem(3474L,def_valuta,4);
  readmem(3478L,&def_round,4);
  readmem(3482L,&def_digits,1);
  if (def_valuta[0]<=' ') {
    movmem("EUR",def_valuta,4);
    def_digits=2;
    def_round=(float).01;
  }
	readmem(3483L,&MenuKeyDifColor,1);
  readmem(3484L,valuta2,50);
	readmem(3534L,&TotaalOp5CentAfronden,1); if(TotaalOp5CentAfronden=='\0') {TotaalOp5CentAfronden='C';writmem(3534L,&TotaalOp5CentAfronden,1);}
  readmem(3535L, &PromoNotOnHorecaPrice, 1); if (PromoNotOnHorecaPrice == '\0') { PromoNotOnHorecaPrice = 'N'; writmem(3535L, &PromoNotOnHorecaPrice, 1); }
  readmem(3536L, &EigenPrijsOpStuksAllowed, 2);
  readmem(3550L, HDDSerialNr, 20);								  
  readmem(3584L,&groep_leeg,2);
  readmem(3586L,&dag_aantal,2);
  readmem(3588L,&rec_aantal,4);
  readmem(3592L,&cf_cont,2);
  readmem(3594L,&cf_art,2);
  readmem(3596L,&cf_groep,2);
  readmem(3598L,&cf_btw,2);
  readmem(3600L,&cf_financ,2);
  readmem(3602L,&cf_periode,2);
  readmem(3604L,&cf_cumper,2);
  readmem(3606L,&tf_dagres,2);
  readmem(3608L,&prx_count,2);
  readmem(3610L,&faktnr,2);
  readmem(3612L,&fakt_allow,2);
  readmem(3614L,&ss1_delay,2);
  readmem(3616L,&ss2_delay,2);
  readmem(3618L,&fl_open_lade,2);
  readmem(3620L,&cf_vkptype,2);
  readmem(3622L,&krtsort,2);
  readmem(3624L,&chk_kassier,2);
  readmem(3626L,&no_prtkas,2);
  readmem(3628L,&cf_verknr,2);
  readmem(3630L,&btw_holland,2);
  readmem(3632L,&totflags,2);
  readmem(3634L,&contflag,2);
  readmem(3636L,&krtperc,4);
  readmem(3640L,&krtfull,4);
  readmem(3644L,&krtvalue,4);
  readmem(3648L,&krt_lead,6);
  readmem(3654L,&krt_bits,2);
  readmem(3656L,&kaslogfl,2);
	readmem(3658L,&specialfl,2);
	readmem(3660L,&PWOpenLade,2);
	readmem(3662L,&tomra_lead,4);
	readmem(3666L,&tomra_plu,10);
	readmem(3676L,&tomra_path,32);
  readmem(3708L,&pcl3flag,2);
  readmem(3710L,&prtbnum,2);
  readmem(3712L,&prtnum,2);
  readmem(3716L, &NoPrtCut, 2); if (NoPrtCut > 1) NoPrtCut = 0; DefNoPrtCut = NoPrtCut;// uit veiligheid voor rommel in kassys.dat
  readmem(4096L,prt_head,410);
  readmem(4506L,prt_foot,82);
  readmem(4016L,&ex_ticket,2);
  readmem(4018L,&notime_fl,2);
  readmem(4020L,&weeg_type,1);
  readmem(4021L,&weeg_lead,4);
  readmem(4025L,&weeg_cpos,1);
  readmem(4026L,&weeg_clen,1);
  readmem(4027L,&weeg_epos,1);
  readmem(4028L,&weeg_elen,1);
  readmem(4029L,&weeg_edig,1);
  readmem(4030L,&lijn_round,2);
  readmem(4032L,&not_check,2);
  readmem(4034L,&fl_freedelity,2);
  readmem(4036L,&SoortKassa,2);
	readmem(4038L,&fl_KasCtrl,2);

	for(k=0;k<3;k++){ // teksten variabele betaalknoppen/fin.verslag aanpassen volgens parameters
		readmem((long)(4040+k*10),&TextVarBetWijze[k][0],10);
		if(TextVarBetWijze[k][0]){
			txtfin[30+k]=TextVarBetWijze[k];
			txtbet[24+k]=txtfin[30+k];
			bcopy(&TextVarBetWijze[k][0],GetPtrTxtKey(130+k),11);
		}
	}
  for(k=0;k<30;k++) readmem((long)(4608+k*14),&bet_layout[k],10);
  readmem(5312L,&bet_krediet,10);
  for(k=0;k<60;k++) readmem((long)(5376+k*14),&keyb_layout[k],10);
  for(k=0;k<100;k++) readmem((long)(7168+k*14),&key_layout[k],10);
  readmem(9216L,&reclame,1452);
  readmem(10752L,&grp_extra,1000);
  readmem(11776L,&promo_desc,500);
  readmem(12288L,&fakt_head,1020);
  readmem(13308L,&fakt_vtekst,243);
  readmem(13551L,&fakt_dist,2);
  readmem(13553L,&fakt_sp1,2);
  readmem(13868L,&prt_krtfull,sizeof(prt_krtfull));
  readmem(14073L,TicketShare,80); TicketShare[80]=0;
  readmem(14153L,LaserShare, 80); LaserShare[80] =0;
  readmem(14313L,&txt_tegoedbon,205); // 5*41
  end:;

	if (XZTotaalDispFlag) tf_dagres=0;

}

void CKasSYS::upd_sys(void)
{
  if (fref_sys<=0) return;

  writmem(2912L,&grp_bits,100);
  writmem(3550L, HDDSerialNr, 20);								  
  writmem(3592L,&cf_cont,2);
  writmem(3594L,&cf_art,2);
  writmem(3596L,&cf_groep,2);
  writmem(3598L,&cf_btw,2);
  writmem(3600L,&cf_financ,2);
  writmem(3602L,&cf_periode,2);
  writmem(3604L,&cf_cumper,2);
  writmem(3610L,&faktnr,2);
  writmem(3620L,&cf_vkptype,2);
  writmem(3622L,&krtsort,2);
  writmem(3628L,&cf_verknr,2);
  writmem(4016L,&ex_ticket,2);
  
  dflush(fref_sys);
}



void CKasSYS::writmem(long lpos, void *s, unsigned len)
{
  long size;
  char *ps, *p;

  if (fref_sys<=0) return;

	p=(char *)s;
  ps=p;
  dseek(fref_sys,lpos,0);
  while(len){
    size=len;
    if(size>30000) size=30000;
    dwrite(fref_sys,ps,(int)size);
    ps+=size;
    len-=size;
  }
}
 

void CKasSYS::cl_kassys()
{
  if (fref_sys>=0) {
	  dclose(fref_sys);
		fref_sys=-1;
	}
}
