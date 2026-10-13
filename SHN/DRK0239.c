/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0239GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat DRK0239dat
#define ovlcod DRK0239cod
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
__declspec(dllimport) unsigned char PrintPaperNr;

char ovldat[] = "drk0239  00:01 21/12/10 (c) Jamadata";
/* beheer statistieken/historieken ahv stu 16  */
																			 // FLAGALB : exporteren historieken in XLS via F9
                                       // FLAGAST : exporteren historieken in TXT via F9
                                       // FLAGFRR / FLAGDWP /FLAGLVB /FLAGART/FLAGCOC/FLAGDUB/FLAGRUB/FLAGLEA/FLAGFLI/FLAGMAE/FLAGLOY : enkel VOO kolommen, geen drankgedoe 
                                       // FLAGGOU : specieke detail ivm gewicht/lotnummer 
																			 // FLAGOPS : punt U zichtbaar onder punt X
																			 // FLAGCOC : ref leverancier nemen ipv codenummer artikel
																			 // FLAGHDY : stuks/karton nemen ipv liters 	
																			 // FLAGSAP : gewicht nemen ipv liters 
									                     // FLAGMAE : enkel HIS tonen van deze plaat indien uit facturatie
								                       // FLAGRUB : Export naar XLS anders
																			 // FLAGVOG : uitschrijven historiek volgens systeem Prik&Tik
#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DUM             0
#define D_LIN_SCR       17
#define MAXRL           500
#define MAX_TBSTAT      5000
#define MAX_VJ          4
#define LEN_PTR         2+4+4+4
#define flag            uint16
#define MAXFLD          100
#define DIMBTW          8
#define Q_SCR           1000

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

#define NO_DRANK_STATISTIEK   0
// hier de VOO klanten zetten als ge geen liters, leeggoed en accijns wilt 
#if FLAGFRR || FLAGDWP || FLAGLVB || FLAGHDY || FLAGCOC || FLAGDUB || FLAGGOU || FLAGRUB || FLAGLEA || FLAGFLI || FLAGMAE || FLAGLOY
#undef  NO_DRANK_STATISTIEK   
#define NO_DRANK_STATISTIEK   1
#endif

extern int16 retcall,parmcall[8];
extern int16 ilength;
extern uint16 procid,onext;
extern char info[];
extern uint16 jamin1[5];

extern char *s();
static char *get_p();
extern int16 *i();
extern uint16 *u();
extern uint16 datejd();
extern long *l();
extern long val();
extern float *f();
extern double *d(),valu_cnv();
static double Round();
static uint16 hash(),HashTblin();

static int16 free;

static struct {
  char title[34];
  char firma[31];
  char hoofding[81];
  uint16 date;
  uint16 q_kol;
  uint16 reclen;
  long q_rec;
  long hdr_pos;
  long idx_pos;
  long bod_pos;
  long pos_niv7;
  int16 q_nivs;
} id;

#if NO_DRANK_STATISTIEK
static struct {
  char naam[16];
  char fmt[16];
  uint16 pos;
  uint16 len;
  int16 breedte;
  int16 prt_kol;
  uint16 codebits;
  uint16 bloknr;
} fld[1][8] = {
  "Omschrijving",
  7,0x88,30,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,30,30,0,0,0,
#if FLAGGOU
  "Gewicht",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,1,
#else
  "Aantal",
  6,0x95,7,0,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,1,
#endif
  "Bedrag",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,0,1,
  "Ft.kort",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,0,1,
  "Netto VW",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,2,
  "Netto AW",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,2,
  "Winst bd",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,2,
  "Netto W%",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,11,0,1,2
};
#else

static struct {
  char naam[16];
  char fmt[16];
  uint16 pos;
  uint16 len;
  int16 breedte;
  int16 prt_kol;
  uint16 codebits;
  uint16 bloknr;
} fld[1][19] = {
  "Omschrijving",
  7,0x88,30,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,30,30,0,0,0,
  "Aantal",
  6,0x95,7,0,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,1,
#if FLAGSAP
  "Gewicht",
#else 
  "Liters",
#endif
  6,0x95,7,0,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,10,0,0,1,
  "Fact.Bedrag",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,0,2,
  "Excl.acc.",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,0,2,
  "Bruto VW",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,3,
  "Excl.acc.",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,3,
  "Ft.kort",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,4,
  "Sem.kort",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,4,
  "Tuss.Brij",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,5,
  "Netto VW",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,6,
  "Netto AW",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,6,
  "Winst bd",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,6,
  "Netto W%",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,11,0,1,6
};
#endif
 
static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_odsp[]  = {7,0x88,79,0,0,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os25[]  = {7,0x88,25,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os8[]   = {7,0x88,8,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us5[]   = {7,0xC8,5,0,0,0,0};
static char fm_us1U[]  = {7,0xC8,1,0,1,0,0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_u04[]   = {10,0xD0,1,0,0x60,0xC0,0,0,4,0};
static char fm_of2_1[] = {6,0x94,2,1,0x70,0};
static char fm_of21_[] = {6,0x94,2,1,0x20,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf3_1[] = {6,0xD4,3,1,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_uf2_0[] = {6,0xD4,2,0,0x70,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_od6_2[] = {6,0x95,6,2,0x70,0};
static char fm_od5_4[] = {6,0x95,5,4,0x70,0};
static char fm_prijs[] = {6,0x95,5,3,0x70,0}; //od_5_3
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_u_ftnr[]= {6,0xD3,8,0,0x60,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uLF[]   = {11,0xC8,1,0,1,0,'L','L','F','F',0};
static char fm_uAN[]   = {11,0xC8,1,0,1,0,'A','A','N','N',0};
static char fm_uHV[]   = {11,0xC8,1,0,1,0,'H','H','V','V',0};
static char fm_uDMJ[]  = {13,0xC8,1,0,1,0,'D','D','M','M','J','J',0};
static char fm_uGMD[]  = {13,0xC8,1,0,1,0,'G','G','M','M','D','D',0};
static char fm_uAVOW[]  = {13,0xC8,1,0,1,0,'A','A','O','O','V','W',0};
static char fm_uAHKT[]  = {15,0xC8,1,0,1,0,'A','A','H','H','K','K','T','T',0};
static char fm_u_ALN[]= {13,0xC8,1,0,0x09,0,'A','A','L','L','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
 
static char *mnd_str[12]={"jan","feb","maa","apr","mei","jun","jul","aug","sep","okt","nov","dec"};
static char *Dagnaam[7]={"Maandag","Dinsdag","Woensdag","Donderdag","Vrijdag","Zaterdag","Zondag"};
static int16 dag_nr[7] = {2,3,4,5,6,0,1};
/* de variabelen */
static char *p_data;
static long *pl_80_1;

static int16 XlsRef,XlsRij,XlsKol,callparmval;
static int16 StylTotaal, StylDate, StylKlasse, StylNormal, StylTitel, Styl2Use;
static char ram[10000],buf_lk[1000];
static uint16 ram_recl,hash_len,dat_len,hash_val, KasKltRec[20];
static char seqo_str[750];
static char filnam[100],fmt_qlv[40],fmt_bdr[40],SkipKassaFt='N',SoortVerkopen;
static char fmt[40],skip_leegg,skip_kasverkopen,sel_soortklant[10],skip_gratis_art,HerberekenSemKorting;
static long seqo_pos,value,seqi_pos;
static int16 seqo_len,seqo_mode,pos,slen;
static uint16 dat_beg,dat_end,dat_vbeg,dat_vend,tb_periode[MAX_VJ+2][2],max_periode;
static uint16 inq_grp,inq_loc,fkey,comp_vj,skip_groepen[5];
static float tabel[103][MAX_VJ+2];
static double totaalbd,totaalst,tot_goed,tot_leeg;
static char def_munt[4],soort_waarde,groep_grafiek;
static int16 form_dat[8],prtnr,prmode,DisplayEhPrijs;
static int16 kdsp,kdsp_off=1,mast_stu,mast_pos,prt2pdf;
static char recbuf[8][MAXRL],nullen[128],prevbuf[50],grp_nr[105];
static long loffil,recnr,niv_pos[8],niv_first[8],indx[36],rec_working;
static long inq_mast,inq_klt,inq_art,inq_lev,inq_merk,inq_ftnr,ftnr_beg,ftnr_end;
static flag lvcd,klcd,chk_btoeg=NO,sear_stt,sys3876,AK_mode;
static char disp_str[55],sta_hoofd[80],CodeString[20];
static int16 q_niv=6;/* aantal niveaus incl niv. 7 (2 is dus het minimum) */
static long TbScreenRecs[50],TbDiversArtikel[10]; // divers artikel per mogelijk BTW%
static float TbBtwPct[8]; 
static float  hl_semkort,calc_sem,brij_tpct,brij_tbd;
static int16 sys2723,sys4397,sys3000;
static uint16 *pu_2_1,*pu_6_1,*pu_16_3;
static int16 *pi;
 
static int16 max_line,len_tblin;
static int ram_size;
static char *p_tblin;
   
static struct{
	uint16 rec;
  float aantal;
  char  code[15];
  char  omschr[40];
  float prx;
	float kort_pct;
	long  groep;
  float accijns;
  float btw;
  double totaal;
  double totaalAK;
  uint16 hash;
}tblin;



static int16 p_scr;
static struct{
  long rec16;
  double totaalbd;
  double totaalst;
} tbs[Q_SCR];

static int16 date2str();

#if FLAGBSA
static double gqlit1, gqlit2, gqstk1, gqstk2;
#endif

ovlcod(parmval)
int16 parmval;
{
  int16 z,j,k,key,iconen_[15],stu_;
  char choice;
	callparmval=parmval;								
  initload();fasunlck(-1);
  mast_stu=2;mast_pos=10; AK_mode=NO;DisplayEhPrijs=NO;inq_loc=0;
  switch(parmval){
 
    case 1 :/* automatisch klantenstatistiek vanuit ovl217 rapporten */
	      skip_leegg='J'; skip_gratis_art='N'; AK_mode=NO; stu_=2;
	      dat_beg=*u(27,2);dat_end=*u(27,3);inq_klt=*u(27,5);inq_mast=inq_klt;
				copy(s(stu_,1),buf_lk,fldlen(stu_,0));
	      if(calc_sta()) ovlcall(238,2);
				copy(buf_lk,s(stu_,1),fldlen(stu_,0));
	      ovlexit(-1);
	      break;
    case 2 :/* display historiek 1 klt of lev/art vanuit bv ovl240 */
	      dat_beg=*u(27,2);dat_end=*u(27,3); stu_=2;
	      inq_art=*u(27,6);
				if(*s(27,4)=='A') {AK_mode=NO;}/* artikels */
	      else if(*s(27,4)=='L'){/* leveranciers */
					AK_mode=YES;inq_lev=*u(27,5);stu_=1;
					if(fldlen(66,1) && *u(27,1)>=1 && *u(27,1)<=10) inq_loc=*u(27,1); // 1 filiaal vanuit ovl0255
				}
	      else {AK_mode=NO;inq_klt=*u(27,5);inq_lev=*u(27,7);stu_=2;}/* klanten */
				copy(s(stu_,1),buf_lk,fldlen(stu_,0));
				DisplayEhPrijs=YES;
	      display(1);
				copy(buf_lk,s(stu_,1),fldlen(stu_,0));
	      ovlexit(-1);
	      break;
    default:  break;
  }
  for(k=0;k<10;k++) if(TbDiversArtikel[k]!=0) break;	if(k>=10) upd_parameters(); // eerst diverse artikels invullen 
	zero(iconen_,sizeof iconen_);z=0;
	iconen_[z++]=1; // parameters
	if(ovltest(2503)) iconen_[z++]=6; // DM-module versie 05/2016 met 3 TAB-bladen
	else if(ovltest(2502)) iconen_[z++]=3; // nieuwe DM-module
	else if(sys3000 && ovltest(2500)) iconen_[z++]=2; // oude DM-module
	if(ovltest(2393)) iconen_[z++]=7; // AB InBev
	if((ovltest(2392) && fldlen(2,133)) || (ovltest(2390) && fldlen(6,8))) iconen_[z++]=4; // Coca-Cola
	if(ovltest(2391)) iconen_[z++]=5; // Haacht
	if(ovltest(2395)) iconen_[z++]=8; // Alken-Maes
	if(ovltest(2397)) iconen_[z++]=9; // Prik&Tik
	if(ovltest(2398)) iconen_[z++]=10; // Prik&Tik
  FOREVER{
		redo:;
    scrget(2,315);z=1;fasunlck(0);
		scraddpicto(50,0,78,3,2,1,105,1,7,"^!B0239A");
		scraddpicto(51,0,78,4,2,1,105,1,7,"^!B0239B");
		scraddpicto(52,0,78,9,2,1,105,1,7,"^!B0239C");
		j=0;
		for(k=0;k<10;k++){
			switch(iconen_[k]){
			  case 1 : scraddpicto(1,0,76-j++*4,22,4,2,59,0,4,"Parameters"); break;
			  case 2 : scraddpicto(2,0,76-j++*4,22,4,2,611,0,0,"DataMasters"); break;
				case 3 : scraddpicto(3,0,76-j++*4,22,4,2,611,0,0,"DataMasters Export"); break;
				case 4 : scraddpicto(4,0,76-j++*4,22,4,2,610,0,0,"Coca-Cola module"); break;
				case 5 : scraddpicto(5,0,76-j++*4,22,4,2,594,0,0,"Haacht module"); break;
				case 6 : scraddpicto(6,0,76-j++*4,22,4,2,611,0,0,"DataMasters/Colda"); break;
				case 7 : scraddpicto(7,0,76-j++*4,22,4,2,585,0,0,"AB InBev module"); break;
				case 8 : scraddpicto(8,0,76-j++*4,22,4,2,586,0,0,"Alken-Maes module"); break;
				case 9 : scraddpicto(9,0,76-j++*4,22,4,2,581,0,0,"Prik&Tik module"); break;
				case 10 : scraddpicto(10,0,76-j++*4,22,4,2,587,0,0,"Suntory module"); break;
				default : break;

			}
		}
		if(ovltest(2396)){
		  scraddf(116,17,5,0);
      scrifld(116,fm_os79,"Uitschrijven statistieken voor Moet-Hennessy ............... : M ");
		}
#if FLAGOPS
		  scraddf(117,17,5,0);
      scrifld(117,fm_os79,"Corrigeren commissies leveranciers ......................... : X ");
#endif
#if FLAGBSA
		  scraddf(117,18,5,0);
      scrifld(117,fm_os79,"Exporteren evolutiestatistieken naar Excel ................. : X ");
#endif
    scrfld(1,25,1);
    scrifld(2,fm_menu,&choice);
#if FLAGAST
		scraddfield(30,15,23,8);scrifld(30,VarTextFmt(22,0),"F9 Exporteren verkopen");
#endif
#if FLAGALB
		scraddfield(30,15,23,8);scrifld(30,VarTextFmt(22,0),"F9 Exporteren verkopen");
#endif
#if FLAGKMP
		scraddfield(30,15,23,8);scrifld(30,VarTextFmt(20,0),"F9 Verkopen naar TXT");
		scraddfield(31,36,23,8);scrifld(31,VarTextFmt(21,0),"F10 Aankopen naar TXT");
#endif
    key=scrupd(2,0x0701);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5050 && key<=5052) goto redo; // link help 
		if(key==5001){ upd_parameters();goto redo;}
		if(key==5002){ ovlcall(2500,0);goto redo;}
		if(key==5003){ ovlcall(2502,0);goto redo;}
		if(key==5004){ if(ovltest(2392) && fldlen(2,133)) ovlexit(2392); else ovlexit(2390); goto redo;}
		if(key==5005){ ovlexit(2391);goto redo;}
		if(key==5006){ ovlcall(2503,0);goto redo;}
		if(key==5007){ ovlcall(2393,0);goto redo;}
		if(key==5008){ ovlcall(2395,0);goto redo;}
		if(key==5009){ ovlcall(2397,0);goto redo;}
		if(key==5010){ if(fldlen(2,138)) ovlcall(2398,0); else errnum=12; goto redo;}
#if FLAGAST
		if(key==109) {exp_ASThis2txt(0); goto redo;}
#endif
#if FLAGALB
		if(key==109) {exp_ALBhis2XLS(0); goto redo;}
#endif
#if FLAGKMP
		if(key==109) {exp_his2txt(0); goto redo;}
		if(key==110) {exp_his2txt(1); goto redo;}
#endif
    AK_mode=NO;
    if(key==101 || key==111) ovlexit(*u(25,4));
		fasunlck(-1);
    switch(choice){
      case '1': disp_his();break;
      case '2': disp_sta(); break;
      case '3': ovlexit(238);break;
#if FLAGVOG
      case '4': exp_hisPT();break;
#else 
      case '4': exp_his();break;
#endif
      case '5': if(ServerVersion>1 || StdInMono) makegrafiek(); else errnum=12; break;
      case '6': ExportHis1Leverancier(); break;
      case '7': if(ovltest(255) && fldlen(16,15)) disp_AKhis(); else errnum=12;break;
      case '8': if(ovltest(255) && fldlen(16,15)) disp_AKsta(); else errnum=12;break;
      case 'A': wis_his();break;
			case 'F': print_ftlist(); break;
      case 'M': if(ovltest(2396)) ovlcall(2396,0); else errnum=12;break;
      case 'P': ovlexit(214);break;
      case 'T': if(ovltest(281) && fldlen(67,1)) ovlcall(281,0); else errnum=12;break;
#if FLAGOPS
			case 'X': CorrectHistoriek();break;
#elif FLAGBSA
			case 'X': exp_hisBSA();break;
#else
			case 'U': CorrectHistoriek();break;
#endif
			case 'V': VernieuwHistoriek();break;
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}

#include "Std\XlsFunc.c"


static disp_his()
{
  FOREVER{
    redo:
    if(ask_sel("Raadplegen historieken",0)) break;
    display(0);
  }
}

static disp_sta()
{
  FOREVER{
		redo:;
    if(ask_sel("Raadplegen statistieken",1)) break;
		if(inq_mast && mast_pos==10){
			seldata.selp_use=NO;
			if(ovlcall(2215,4)) goto redo;
		}
    if(calc_sta()) ovlcall(238,YES);
  }
}
 
static disp_AKhis()
{
  AK_mode=YES;
  FOREVER{
    redo:
    if(ask_AKsel("Raadplegen historieken",0)) break;
    display(0);
  }
}
 
static disp_AKsta()
{
  AK_mode=YES;
  FOREVER{
    if(ask_AKsel("Raadplegen statistieken",1)) break;
    if(calc_sta()) ovlcall(238,YES);
  }
}

static CorrectHistoriek()
{
	ram_size=75000;
  if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;zero(RamBon,ram_size);
  len_tblin=sizeof tblin;max_line=ram_size/len_tblin;
  p_tblin=(char *)&tblin.rec;
	zeroL(RamBon,RamBonSize);tot_leeg=0;tot_goed=0;
	  
   FOREVER{
		 if(AskCorrectieDate()) break;
		 LoadCorrectieRecords();
		 if(UpdateCorrectieRecords(NO)==NO){
			 SaveCorrectieRecords();
		 }
	 }
	 inq_ftnr=0;dat_beg=0;
}

static AskCorrectieDate()
{
  int16 key,z,curs=1;
 
  fasinit(2); if(inq_klt){*u(2,1)=inq_klt;fasgeti(2);}

  FOREVER{
    redo:;
    scrget(2,323);z=1;
		DisplayMenuTitel(1,"Ingeven correcties historieken",0x3);
    scrifld(z++,fm_udat,&dat_beg);
    scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    key=scrupd(curs,0x81);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		switch(key){
				case 5001 : if(search(2,98)) {curs=4;goto redo;} break;
				default : break;
		}

    if(key==101) return YES;
    if(dat_beg==0) {errnum=34;curs=1;goto redo;}
    if(*s(2,3)){
      if(search(2,0)){curs=2;goto redo;}
    } else fasinit(2);
    inq_klt=*u(2,1);
    if(key!=108) goto redo;
    break;
  }
  AK_mode=NO;
  inq_mast=inq_klt;mast_stu=2;mast_pos=10;
  endsr:;
  return NO;
}

static LoadCorrectieRecords()
{

	int16 jj,mm,dd,j, mode_;
	  
  
	zeroL(RamBon,RamBonSize);tot_leeg=0;tot_goed=0;
	jddate(dat_beg,&jj,&mm,&dd);
  inq_ftnr=(long)(jj)*10000+mm*100+dd;

	fasinit(16);*l(16,2)=inq_ftnr;mode_=1;j=0;
	FOREVER{
		if(faskeyi(16,3,mode_)) break; mode_=2;
		if(*l(16,2)!=inq_ftnr) break;
		if(mast_stu==2 && *l(16,10)==inq_mast){
			RamBon2Tblin(j);
			tblin.rec=*l(16,20);
			tblin.aantal=*d(16,30);
			copy(s(16,21),tblin.code,fldlen(16,21));
			copy(s(16,22),tblin.omschr,fldlen(16,22));
			if(*d(16,30)) tblin.prx=Round((double)(*d(16,31)/ *d(16,30)),(double)(0.01));
			tblin.accijns=*f(16,27);
			tblin.groep=*l(16,23);
			tblin.btw=*f(16,24);
			tblin.totaal=*d(16,31);
			tblin.totaalAK=*d(16,32);
			tblin.hash=HashTblin();
			Tblin2RamBon(j++); if(j>=max_line) break;
		}
	}
}

static UpdateCorrectieRecords(sel_mode_) // 0=update his, 1=selecteer artikels
{
	char def_inc;
  int16 curs,j,key,k,start_=0,z,z_base,q_per_line,nstart_,auto_enter,err_pos_,prxnr;
	uint16 sys3894;
	float prx_;

	if(sel_mode_){
		ram_size=75000;
		if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;zero(RamBon,ram_size);
		len_tblin=sizeof tblin;max_line=ram_size/len_tblin;
		p_tblin=(char *)&tblin.rec;
		zeroL(RamBon,RamBonSize);tot_leeg=0;tot_goed=0;
	}
  prxnr=*s(2,26)-'0';
  if(prxnr<0 || prxnr>9) prxnr=0;
  if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
	sysget(3894,2,(char *)&sys3894);
  if(sys3894 & (1<<prxnr)) def_inc='J';
  else def_inc='N';
	if(sel_mode_==0) CalcCorrectieRecords();
	q_per_line=6;	curs=1;err_pos_=0;
  FOREVER{
    redo:
    scrnum=0;if(sel_mode_==0) scrget(2,324); else scrget(2,326); z=1;
    j=start_+1; scrifld(z++,fm_ou3,&j);
    j=start_+D_LIN_SCR; scrifld(z++,fm_ou3,&j);
		if(sel_mode_==0){
      scrofld(z++,2,3,-1);scrifld(z++,fm_od6_2,&tot_goed);
      scrifld(z++,fm_odat,&dat_beg); scrifld(z++,fm_od6_2,&tot_leeg);
		} else z+=4;
    z_base=z;auto_enter=NO;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
      RamBon2Tblin(j);
      if(sel_mode_==0) dspdetln(z++,j,fm_uf5_0,&tblin.aantal); else z++;
    	auto_enter=YES;if(tblin.code[0]!='\0' && z!=err_pos_) auto_enter=NO;
      fmt_get(6,2);
      if(auto_enter){dspdetln(-z,j,fmt,tblin.code);z++;}
      else dspdetln(z++,j,fmt,tblin.code);
    	auto_enter=YES;if(tblin.omschr[0]!='\0' && z!=err_pos_) auto_enter=NO;
      fmt_get(6,3);
      if(auto_enter){dspdetln(-z,j,fmt,tblin.omschr);z++;}
      else dspdetln(z++,j,fmt,tblin.omschr);
			if(sel_mode_==0){
        fmt_get(6,21);dspdetln(z++,j,fmt,&tblin.prx);
	  		dspdetln(z++,j,fm_uf2_0,&tblin.kort_pct);
        dspdetln(z++,j,fm_od6_2,&tblin.totaal);
			} else z+=3;
    }
    key=scrupd(curs,0xF6);curs=z_base;

    auto_enter=NO;nstart_=start_;err_pos_=0;
    if(key==106){
      if(scr_ok("Wenst U echt de aanpassingen te annuleren ???")) return YES;
			else goto redo;
    }
 
    if(key==18){
      if(fldcurs<z_base){
				curs=fldcurs+1;goto redo;
      }
      auto_enter=YES;
      j=(fldcurs-z_base)/q_per_line;j+=start_;
      k=(fldcurs-z_base)%q_per_line;
      RamBon2Tblin(j);
      if(k==1 && tblin.code[0]=='\0') {curs=fldcurs+1;goto redo;}
      if(k==2 && tblin.omschr[0]=='\0') {curs=fldcurs+1;goto redo;}
    }

    if(key==105){
      k=(fldcurs-z_base)/q_per_line;
      if(fldcurs<z_base || k<0){errnum=34; curs=fldcurs;goto redo;}
      else {
				for(j=start_+k;j<max_line-1;j++){
				  RamBon2Tblin(j+1);Tblin2RamBon(j);
				}
				zero((char *)p_tblin,len_tblin);Tblin2RamBon(max_line-1);
			}
    }

    for(k=start_;k<(start_+D_LIN_SCR);k++){
      RamBon2Tblin(k);
      if((tblin.code[0] || tblin.omschr[0]) && tblin.hash!=HashTblin()){
				fasinit(6);
				if(tblin.code[0]) {*s(6,3)='.';copy(tblin.code,s(6,3)+1,fldlen(6,2));}
				else {copy(tblin.omschr,s(6,3),fldlen(6,3));}
				if(search(6,0)){
					curs=z_base+ (k-start_)*q_per_line +1; if(tblin.code[0]=='\0') curs++;
					err_pos_=curs;errnum=39;goto redo;
				}
				copy(s(6,2),tblin.code,fldlen(6,2));
				copy(s(6,3),tblin.omschr,fldlen(6,3));
				tblin.rec=*u(6,1);
				tblin.groep=*i(6,9);
				if(tblin.prx==0){
					prx_=*f(6,PrNrs[prxnr]); if(def_inc=='J') prx_=Round((double)( prx_/(1.+*f(6,28)/100.)),(double)(0.01));
					tblin.prx=prx_;
				}
				if(fldlen(6,30)) tblin.accijns=*f(6,30);
				tblin.btw=*f(6,28);
				tblin.hash=HashTblin();
      }
      else if(tblin.code[0]=='\0' && tblin.omschr[0]=='\0'){
				zero((char *)&tblin,len_tblin);
      }
      Tblin2RamBon(k);
    }
		if(sel_mode_==0) CalcCorrectieRecords();
		
    if(key==108){
	    if(sel_mode_==1 || scr_ok("Wenst U deze aanpassingen door te voeren ???")) break;
		}
    start_=nstart_;
    if(key==18 || auto_enter){ /* automatische bladskip op einde van scherm */
      for(k=0;k<D_LIN_SCR;k++){RamBon2Tblin(start_+k);if(tblin.aantal==0) break;}
      if(k==D_LIN_SCR) key=103;
    }
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=start_;k<start_+D_LIN_SCR;k++){RamBon2Tblin(k);if(tblin.omschr[0]=='\0') break;}
    if(k==start_+D_LIN_SCR) k=start_;curs=z_base + (k-start_)*q_per_line;
  }

  return NO;
}

static CalcCorrectieRecords()
{
	int16 k;
	double kort_;
	 						
	tot_leeg=0;tot_goed=0;
  
	for(k=0;k<max_line;k++){
		RamBon2Tblin(k);
		if(tblin.omschr[0] && tblin.rec && tblin.aantal){
			fasinit(6);*u(6,1)=tblin.rec;fasgeti(6);
			if(*i(6,9)==99){ // leeggoed 
				tblin.totaal=tblin.aantal*tblin.prx;
				tblin.totaalAK=tblin.aantal*tblin.prx;
				tot_leeg+=tblin.totaal;
			}
			else{
				kort_=0; 
				if(tblin.kort_pct) kort_=(tblin.prx-tblin.accijns)*tblin.kort_pct/100.;
				tblin.totaal=Round((double)((tblin.prx-kort_)*tblin.aantal),(double)(0.01));
				tblin.totaalAK=tblin.aantal* *f(6,18);
				tot_goed+=tblin.totaal;
			}
			Tblin2RamBon(k);
		}
	}
}

static SaveCorrectieRecords()
{

	int j,mode_;
	  
  fasunlck(-2);
	fasinit(16);*l(16,2)=inq_ftnr;mode_=1;j=0;
	FOREVER{ // eerst alle bestaande records deleten 
		if(faskeyi(16,3,mode_)) break; mode_=2;
		if(*l(16,2)!=inq_ftnr) break;
		if(mast_stu==2 && *l(16,10)==inq_mast) faskill(16);
	}

	for(j=0;j<max_line;j++){
		RamBon2Tblin(j);
		if(tblin.rec && tblin.aantal){
			fasinit(16);
			*l(16,2)=inq_ftnr; *u(16,3)=dat_beg; *l(16,10)=inq_mast;
			if(fldlen(16,12)) *l(16,12)=*l(16,10);
			fasinit(6);*u(6,1)=tblin.rec;fasgeti(6);
			*l(16,20)=tblin.rec;
			copy(tblin.code,s(16,21),fldlen(16,21));
			copy(tblin.omschr,s(16,22),fldlen(16,22));
			*l(16,23)=*u(6,9);
			*f(16,24)=tblin.btw;
			copy(s(6,10),s(16,25),fldlen(16,25));
			if(fldlen(6,31)) *f(16,26)=*f(6,31); if(*f(16,26)==0) *f(16,26)=1;
			*f(16,27)=tblin.accijns;
			*d(16,30)=tblin.aantal;
			*d(16,31)=tblin.totaal;
			*d(16,32)=tblin.totaalAK;
			fasadd(16);
		}
	}
	fasunlck(-1);
}



static dspdetln(z,j,fmt_,pvar_)
int16 z,j;
char *fmt_,*pvar_;
{
  char *vpos_;

  vpos_=RamBon+(j*len_tblin)+(pvar_-p_tblin);
  scrifld(z,fmt_,vpos_);
}

static uint16 HashTblin()
{
  char *ps;
  int16 len_;
  uint16 fuval=0;
					
  len_=sizeof tblin.code + sizeof tblin.omschr;ps=tblin.code;
  while(len_--){
    fuval=fuval*3+*(ps++);
  }
  return fuval;
}

static RamBon2Tblin(lin_)
int16 lin_;
{
   copy(RamBon+(lin_*len_tblin),p_tblin,len_tblin);
}
							
static Tblin2RamBon(lin_)
int16 lin_;
{
  copy(p_tblin,RamBon+(lin_*len_tblin),len_tblin);
}



static display(disp_opties)
int16 disp_opties;/* 1=ga direct naar einde */
{
  int16 j,key,ks;
  flag empty,goto_end=NO;
  char dsp_str_[20];

  if(disp_opties==1) goto_end=YES;
  if(AK_mode){inq_mast=inq_lev;mast_stu=1;mast_pos=15;}
  else {inq_mast=inq_klt;mast_stu=2;mast_pos=10;}
 
  zero(dsp_str_,sizeof dsp_str_);
  if(inq_mast) {
		if(inq_art) fkey=2;
		else if(faskeyi(16,4,1)==45) fkey=11;
		else fkey=4;
	}
  else if(inq_art){
		fkey=5; if(faskeyi(16,5,1)==45) fkey=1;
	}
  else {fkey=3; stcli_d(dsp_str_,(long)ftnr_beg,6,1);}
  redo_full:;
  p_scr=0; totaalbd=0;totaalst=0;
  fasinit(16);*l(16,mast_pos)=inq_mast; *l(16,20)=inq_art; *l(16,2)=ftnr_beg;
  FOREVER{
    scrnum=0;
    scrget(2,285);empty=YES;
//    scraddf(180,22,66,9);
		scraddpicto(1,0,78,23,2,1,583,0,0,"PDF");scraddpicto(2,0,77,2,2,1,64,0,4,"Prijs <-> Totaal");
		if(AK_mode) scraddf(100,2,2,0);
    if(p_scr>=Q_SCR-1) errnum=11;
    if(inq_mast) scrofld(1,mast_stu,3,-1);
    else if(inq_art) scrofld(1,6,3,-1);
    else scrifld(1,fm_os20,dsp_str_);
    p_scr++;scrifld(2,fm_ou4,&p_scr);p_scr--;
    scrifld(3,fm_os11," Zoeken...");
		if(DisplayEhPrijs) scrifld(4,fm_os11,"Fact.prijs"); else scrifld(4,fm_os11,"  Bedrag");
    for(j=0;j<18;j++){
      ks=add_line(j,YES);
      if(ks==NO) {
				if(goto_end && j==0){goto_end=NO;key=102; goto after_upd;}
				goto_end=NO;break;
			}
    }
    scrifld(3,fm_os11,"");
    scrifld(95,fmt_qlv,&totaalst);
    scrifld(96,fmt_bdr,&totaalbd);
		if(AK_mode) scrifld(100,VarTextFmt(7,0)," Bonnr ");
    next:;
		if(goto_end && ks!=NO && p_scr<(Q_SCR-3)){scrget(1,7);scrupd(-3,0); key=103;}
    else key=scrupd(-1,0x410F);
after_upd:;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) break;
    if(key==104 && ks!=NO){goto_end=YES;key=103;}
		prt2pdf=NO; if(key==5001){prt2pdf=YES;key=109;}
		if(key>=5005 && key<5005+18){
			DisplayHisDetail(key-5005);
			if(p_scr<=0){goto redo_full;}
      else{
				fasinit(16);
				if(tbs[p_scr].rec16){
					*l(16,1)=tbs[p_scr].rec16;fasgeti(16);
					totaalbd=tbs[p_scr].totaalbd;
					totaalst=tbs[p_scr].totaalst;
				}
				ks=YES;
      }
		}
		if(key==5002){
			if(DisplayEhPrijs) DisplayEhPrijs=NO; else DisplayEhPrijs=YES;
			if(p_scr<=0){goto redo_full;}
      else{
				fasinit(16);
				if(tbs[p_scr].rec16){
					*l(16,1)=tbs[p_scr].rec16;fasgeti(16);
					totaalbd=tbs[p_scr].totaalbd;
					totaalst=tbs[p_scr].totaalst;
				}
				ks=YES;
      }
		}

    if(key==109) {print();break;}
    if(key==102){
      p_scr--;
      if(p_scr<=0){goto redo_full;}
      else{
				fasinit(16);
				if(tbs[p_scr].rec16){
					*l(16,1)=tbs[p_scr].rec16;fasgeti(16);
					totaalbd=tbs[p_scr].totaalbd;
					totaalst=tbs[p_scr].totaalst;
				}
				ks=YES;
      }
    }
    if(ks==NO){
      if(key==108) break;
      else goto next;
    }
    else if(key==103){
      p_scr++; if(p_scr>=Q_SCR-2){p_scr--;errnum=11;}
    }
  }
  return YES;
}

static DisplayHisDetail(nr_)
int16 nr_;
{
	int16 key,z,updmode_=NO,curs=-1;

	fasinit(16);*l(16,1)=TbScreenRecs[nr_];fasgeti(16);
	fasinit(2);*u(2,1)=*l(16,10); if(*u(2,1)) fasgeti(2);
  fasinit(1);*u(1,1)=*l(16,15); 
	if(*u(1,1)>=30000){
  	if(*u(1,1)==30000) copy("Mutatie filiaal DEPOT",s(1,3),20);
		else sprintf_s(s(1,3),20,"Mutatie filiaal %d",*u(1,1)-30000);
	}	
	else if(*u(1,1)) fasgeti(1);
	fasinit(6);*u(6,1)=*l(16,20); if(*u(6,1)) fasgeti(6);
	FOREVER{
#if FLAGGOU
		scrget(2,561);
#else
		scrget(2,361);
#endif
		z=1;
		scrfld(z++,16,2);scrfld(z++,16,3);
    scrfld(z++,16,4);
    scrfld(z++,2,3);
		scrfld(z++,1,3);
#if FLAGCOC
		if(*s(6,8) && *s(16,22)!='*') scrfld(z++,6,8); else scrfld(z++,16,21); // ref lev tonen ipv codenr
#else
		scrfld(z++,16,21);
#endif
		scrfld(z++,16,22);
    scrfld(z++,16,23);scrfld(z++,16,24);
    scrfld(z++,16,25);scrfld(z++,16,26);
    scrfld(z++,16,30);scrfld(z++,16,31);
#if FLAGGOU
		scrfld(z++,16,29); // gewicht
		scrfld(z++,16,33);scrfld(z++,16,34);
		scrfld(z++,16,32);
    scrfld(z++,16,40); // lotnummer 
#else
		scrfld(z++,16,33);scrfld(z++,16,34);
		scrfld(z++,16,32);
		if(fldlen(66,1)) scrfld(z++,16,8); else z++;// filiaalnummer
    scrfld(z++,16,40); // lotnummer 

#endif
		curs=-1;if(updmode_) curs=8;
    key=scrupd(curs,0x1);
		if(key==112) updmode_=YES;
		if(key==101) break;
	}
	if(updmode_) fasupd(16);
}


static exp_his()
{
  int16 k,dsp_cnt_,fld_,jj,mm,dd;
  int16 mode,a_mode;
	uint16 ubd_;
	long last_klt;
  flag end=NO;
  double bd_,qlv_,qft_,qlit_,bd_ex_acc_;
  char str_[100];

  if(ask_sel("Exporteren artikelomzet naar Excel",2)) goto endsr;
  if(AK_mode){inq_mast=inq_lev;mast_stu=1;mast_pos=15;}
  else {inq_mast=inq_klt;mast_stu=2;mast_pos=10;}
	fasunlck(-2);

  zero(str_,sizeof str_);
  k=copy0("Artikelomzet ",str_,13);
 
  if(inq_art){fasinit(6);*u(6,1)=inq_art;fasgeti(6); k+=copy0(s(6,3),&str_[k],15);}
  else if(inq_mast){fasinit(mast_stu);*u(mast_stu,1)=inq_mast;fasgeti(mast_stu); k+=copy0(s(mast_stu,3),&str_[k],15);}
  else if(inq_lev){fasinit(1);*u(1,1)=inq_lev;fasgeti(1); k+=copy0(s(1,3),&str_[k],15);}

  str_[k++]=' ';k+=date2str(&str_[k],dat_beg,1);
  str_[k++]='-';k+=date2str(&str_[k],dat_end,1);
  cnv_fname(str_,k);
  k=copy0(".XLS",&str_[k],4);
  XlsRef=XlsCreate(str_);
  if(XlsRef<=0) {errnum=1;goto endsr;}

	XlsRij=1;XlsKol=1;
  if(inq_art){
//		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Artikel",0);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Nr",0);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Naam",0);
#if FLAGPED
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Adres",0);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Postcode",0);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Gemeente",0);
#endif
  }
  else{
//		XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Klant",0);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Code",0);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",0);
  }
#if FLAGSTB
	  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"FtNr",0);
    XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Datum",0);
#endif
#if FLAGDWP || FLAGLVB || FLAGGOU || FLAGLEA || FLAGLOY
	  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Gewicht",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Factuurbedrag",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal facturen",0);
#else
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal",0);
#if FLAGSAP || FLAGHDY
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Gewicht",0);
#else
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Volume",0);
#endif
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Factuurbedrag",0);
#if !NO_DRANK_STATISTIEK
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Excl.accijnzen",0);
#endif
#if FLAGSTB
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"LotNr/Verv.datum",0);
#else 
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal facturen",0);
#endif
#endif
	XlsRij++;
	dsp_cnt_=0;
  if(inq_art){
    fasinit(mast_stu);if(inq_mast){*u(mast_stu,1)=inq_mast;fasgeti(mast_stu);} a_mode=1;
    scrget(1,170);scrifld(5,fm_os38,"Bezig met :");
    FOREVER{
      next_klt:;
      if(faskeyi(mast_stu,2,a_mode)) break; a_mode=2;
			if(mast_stu==2 && sel_soortklant[0] && cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) goto next_klt;
			if((dsp_cnt_%50)==0) {scrfld(10,mast_stu,3);scrupd(-3,0);} dsp_cnt_++;

      fasinit(16);
      *l(16,20)=inq_art;
      *l(16,mast_pos)=*u(mast_stu,1); mode=1; end=NO;
      bd_=0;qlv_=0;qft_=0;qlit_=0;bd_ex_acc_=0;
      FOREVER{
	next:;
				if(faskeyi(16,2,mode)) end=YES; mode=2;
				if(*l(16,20)!=inq_art) end=YES;
				if(*l(16,mast_pos)!=*u(mast_stu,1)) end=YES;
				if(!end){
					if(ftnr_beg && *l(16,2)<ftnr_beg) goto next;
					if(ftnr_end && *l(16,2)>ftnr_end) goto next;
					if(*pu_16_3 <dat_beg) {*pu_16_3=dat_beg;mode=1; goto next;}
					if(*pu_16_3 >dat_end) {*pu_16_3=0xFFFF; mode=2;goto next;}
					if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
					if(mast_pos==10 && fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
					if(mast_pos==15 && *l(16,10)) goto next;/* geen klanten  */
				}
#if FLAGSTB
				bd_=0;qlv_=0;qft_=0;qlit_=0;bd_ex_acc_=0;
				if(end) break;
				fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
				qlv_+=*d(16,30);/* stuks */
				fld_=37;
				if(fldlen(6,fld_)) qlit_+=*d(16,30)* *f(6,fld_);/* LITERS */

				bd_+=*d(16,31);/* omzet */
				if(*d(16,31)) bd_ex_acc_+=*d(16,31)-(*d(16,30)* *f(16,27));/* omzet excl. accijns */
				qft_++;/* aantal facturen */
				if(end || qlv_ || bd_){
#else
				if(end){
#endif
					if(qlv_ || bd_){
						qlv_=Round(qlv_,(double)(0.01));
						qlit_=Round(qlit_,(double)(0.01));
						bd_=Round(bd_,(double)(0.01));
						bd_ex_acc_=Round(bd_ex_acc_,(double)(0.01));
						qft_=Round(qft_,(double)(0.01));
	
						XlsKol=1;
#if FLAGSTB
						WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
#endif
						zero(str_,sizeof str_);
						if(fldlen(mast_stu,2)==0) stcli_d(str_,(long)(*u(mast_stu,1)),5,1);
						else  copy0(s(mast_stu,2),str_,fldlen(mast_stu,2));
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
						zero(str_,sizeof str_);copy0(s(mast_stu,3),str_,fldlen(mast_stu,3));
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
#if FLAGPED
						zero(str_,sizeof str_);copy0(s(mast_stu,4),str_,fldlen(mast_stu,4));
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
						zero(str_,sizeof str_);copy0(s(mast_stu,5),str_,fldlen(mast_stu,5));
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
						zero(str_,sizeof str_);copy0(s(mast_stu,6),str_,fldlen(mast_stu,6));
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
#endif
#if FLAGSTB
						WriteFld2Xls(XlsRij,XlsKol++,16,2,0);
						zero(str_,sizeof str_);
						if(*u(16,3)){
						  jddate(*u(16,3),&jj,&mm,&dd);
							zero(str_,sizeof str_);sprintf_s(str_,sizeof str_,"%02d/%02d/%04d",dd,mm,jj);
						}
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
#endif

						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&qlv_,0);
						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&qlit_,0);
						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&bd_,0);
#if !NO_DRANK_STATISTIEK
						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&bd_ex_acc_,0);
#endif
#if FLAGSTB
						zero(str_,sizeof str_);copy0(s(16,40),str_,fldlen(16,40));
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
#else
						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&qft_,0);
#endif
						XlsRij++;
					}
#if FLAGSTB
			  	if(end) break;
					else goto next;
#else
					break;
#endif
				}
				fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
				qlv_+=*d(16,30);/* stuks */
#if FLAGGOU || FLAGHDY
				qlit_+=*d(16,29);
#else
				fld_=37;
#if FLAGDWP
				fld_=83;
#endif
#if FLAGLVB || FLAGSAP || FLAGLEA|| FLAGLOY
				fld_=38;
#endif
				if(fldlen(6,fld_)) qlit_+=*d(16,30)* *f(6,fld_);/* LITERS */
#endif
				bd_+=*d(16,31);/* omzet */
				if(*d(16,31)) bd_ex_acc_+=*d(16,31)-(*d(16,30)* *f(16,27));/* omzet excl. accijns */
				qft_++;/* aantal facturen */
      }
    }
  }
  else{
    fasinit(6);if(inq_art){*u(6,1)=inq_art;fasgeti(6);} a_mode=1;
    scrget(1,170);scrifld(5,fm_os38,"Bezig met artikel :");
    FOREVER{
      next_art:;
      if(faskeyi(6,2,a_mode)) break; a_mode=2;
      if(inq_art && inq_art!=*u(6,1)) break;
      if(mast_pos!=15 && inq_lev && *u(6,7)!=inq_lev) goto next_art;
			if(mast_pos!=15 && inq_merk && *u(6,101)!=inq_merk){ goto next_art;}
      if(inq_grp && *i(6,9)!=inq_grp) goto next_art;
			for(k=0;k<5;k++) if(skip_groepen[k] && skip_groepen[k]==*i(6,9)) goto next_art;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next_art;
      if(skip_leegg=='J' && *i(6,9)==99){goto next_art;}
			if((dsp_cnt_%50)==0) {scrfld(10,6,3);scrupd(-3,0);} dsp_cnt_++;
			fasinit(16);
      *l(16,20)=*u(6,1);
      *l(16,mast_pos)=inq_mast; mode=1; end=NO;
      bd_=0;qlv_=0;qft_=0;qlit_=0; bd_ex_acc_=0;last_klt=0xFFFF;
      FOREVER{
	next1:;
				if(faskeyi(16,1,mode)) end=YES; mode=2;
				if(*l(16,20)!=*u(6,1)) end=YES;
				if(!end){
					if(inq_mast && *l(16,mast_pos)!=inq_mast) goto next1;
					 if(ftnr_beg && *l(16,2)<ftnr_beg) goto next1;
					if(ftnr_end && *l(16,2)>ftnr_end) goto next1;
					if(*pu_16_3 <dat_beg) {*pu_16_3=dat_beg;mode=1; goto next1;}
					if(*pu_16_3 >dat_end) {*pu_16_3=0xFFFF; mode=2;goto next1;}
					if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next1;
					if(mast_pos==10){
						if(fldlen(16,15) && *l(16,15)) goto next1;/* geen leveranciers */
						if(sel_soortklant[0]){
							fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
							if(sel_soortklant[0] && cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) goto next1;
						}
					}
					if(mast_pos==15 && *l(16,10)) goto next1;/* geen klanten  */
				}
#if FLAGSTB
				bd_=0;qlv_=0;qft_=0;qlit_=0;bd_ex_acc_=0;
				if(end) break;
				fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
				qlv_+=*d(16,30);/* stuks */
				fld_=37;
				if(fldlen(6,fld_)) qlit_+=*d(16,30)* *f(6,fld_);/* LITERS */

				bd_+=*d(16,31);/* omzet */
				if(*d(16,31)) bd_ex_acc_+=*d(16,31)-(*d(16,30)* *f(16,27));/* omzet excl. accijns */
				qft_++;/* aantal facturen */
				if(end || qlv_ || bd_){
#else
				if(end){/* totalen per artikel */
#endif
					if(qlv_ || bd_){
						qlv_=Round(qlv_,(double)(0.01));
						qlit_=Round(qlit_,(double)(0.01));
						bd_=Round(bd_,(double)(0.01));
						bd_ex_acc_=Round(bd_ex_acc_,(double)(0.01));
						qft_=Round(qft_,(double)(0.01));
 						XlsKol=1;
#if FLAGSTB
						WriteFld2Xls(XlsRij,XlsKol++,2,3,0);
#endif
						zero(str_,sizeof str_);
#if FLAGART || FLAGCOC
						copy0(s(6,8),str_,fldlen(6,8));
#else
						copy0(s(6,2),str_,fldlen(6,2));
#endif
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
						zero(str_,sizeof str_);copy0(s(6,3),str_,fldlen(6,3));
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
#if FLAGSTB
						WriteFld2Xls(XlsRij,XlsKol++,16,2,0);
						zero(str_,sizeof str_);
						if(*u(16,3)){
						  jddate(*u(16,3),&jj,&mm,&dd);
							zero(str_,sizeof str_);sprintf_s(str_,sizeof str_,"%02d/%02d/%04d",dd,mm,jj);
						}
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
#endif
						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&qlv_,0);
						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&qlit_,0);
						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&bd_,0);
#if !NO_DRANK_STATISTIEK
						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&bd_ex_acc_,0);
#endif
#if FLAGSTB
						zero(str_,sizeof str_);copy0(s(16,40),str_,fldlen(16,40));
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,str_,0);
#else
						XlsWrite(XlsRef,XlsRij,XlsKol++,2,&qft_,0);
#endif
						XlsRij++;
					}
#if FLAGSTB
			  	if(end) break;
					else goto next1;
#else
					break;
#endif
				}
				fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
				qlv_+=*d(16,30);/* stuks */
#if FLAGGOU || FLAGHDY
				qlit_+=*d(16,29);
#else
				fld_=37;
#if FLAGDWP
				fld_=83;
#endif
#if FLAGLVB || FLAGSAP || FLAGLEA || FLAGLOY
				fld_=38;
#endif
				if(fldlen(6,fld_)) qlit_+=*d(16,30)* *f(6,fld_);/* LITERS */
#endif
				bd_+=*d(16,31);/* omzet */
				if(*d(16,31)) bd_ex_acc_+=*d(16,31)-(*d(16,30)* *f(16,27));/* omzet excl. accijns */
				qft_++;/* aantal facturen */
      }
    }
  }
  //XlsSaveAsPdf(XlsRef);
  XlsClose(XlsRef,1);
	fasunlck(-1);
  endsr:;
}


#if FLAGVOG
static exp_hisPT()
{
  int16 z,key,k,dsp_cnt_,curs=1;
  int16 mode;
	char str_[50];
	long lcode_;
	double bd_;

  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,2,25,2);
    scraddf(z++,4,5,0);scraddf(z++,4,24,2); scraddf(z++,4,34,0);scraddf(z++,4,41,2); // periode 
	  scraddf(z++,23,1,8);scraddf(z++,23,11,8);  // functietoetsen 
    z=1;
    DisplayMenuTitel(1,"Uitschrijven verkopen naar Excel (Prik&Tik)",0xA);z++;
    scrifld(z++,fm_os79,"Periode verkopen : ");
    scrifld(z++,fm_udat,&dat_beg);
    scrifld(z++,VarTextFmt(6,0),"t.e.m.");
    scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,VarTextFmt(9,0)," F1 stop ");scrifld(z++,VarTextFmt(23,0)," F8 begin uitschrijven ");
    key=scrupd(curs,0x81);curs=1;
    if(key==101) goto endsr;
    if(dat_beg==0) {curs=3;errnum=34;goto redo;}
    if(dat_end==0) {curs=5;errnum=34;goto redo;}
    if(dat_end<dat_beg) {curs=5;errnum=34;goto redo;}

    if(key!=108) goto redo;
    break;
  }

	fasunlck(-2);

  zero(str_,sizeof str_);
  k=copy0("Verkopen ",str_,13);
  str_[k++]=' ';k+=date2str(&str_[k],dat_beg,1);
  str_[k++]='-';k+=date2str(&str_[k],dat_end,1);
  cnv_fname(str_,k);
  k=copy0(".XLSX",&str_[k],5);
  XlsRef=XlsCreate(str_);
  if(XlsRef<=0) {errnum=1;goto endsr;}
	XlsSelectWorkSheet(XlsRef,1,"Verkopen");  // sheet verkopen
	XlsRij=1;XlsKol=1;
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Datum",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Code",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",0);
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Groep",0);
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"BTW",0);
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Accijns",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Klant",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"SoortKlant",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"VK-waarde",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"AK-waarde",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Margetotaal",0);
	XlsRij++;
	dsp_cnt_=0;
  scrget(1,170);fasinit(16);mode=1;
  FOREVER{
next1:;
		if(faskeyi(16,3,mode)) break; mode=2;
		if(fldlen(16,15) && *l(16,15)) goto next1;/* geen leveranciers */
		if(*pu_16_3 <dat_beg || *pu_16_3 >dat_end) goto next1;
		if(*d(16,30)==0 && *d(16,31)==0 && *d(16,32)==0) goto next1;
		if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next1;
		fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
		fasinit(52);*u(52,1)=*u(6,9);fasgeti(52); if(fldlen(52,24) && *s(52,24)=='J') goto next1;
		fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
		XlsKol=1;
		XlsWrite(XlsRef,XlsRij,XlsKol++,3,(char *)u(16,3),0); // ALS DATUM DOORGEVEN //WriteFld2Xls(XlsRij,XlsKol++,16,3,0);
		zero(str_,sizeof str_);copy(s(6,2),str_,fldlen(6,2)); lcode_=val(str_); WriteVar2Xls(XlsRij,XlsKol++,fm_ul7,&lcode_); // als getal uitschrijven    WriteFld2Xls(XlsRij,XlsKol++,6,1,0);
		WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
		WriteFld2Xls(XlsRij,XlsKol++,6,9,0);
		WriteFld2Xls(XlsRij,XlsKol++,6,28,0);
		bd_=Round((double)(*f(16,27)),(double)(0.001));WriteVar2Xls(XlsRij,XlsKol++,fm_od5_4,&bd_); // WriteFld2Xls(XlsRij,XlsKol++,16,27,0);
		WriteFld2Xls(XlsRij,XlsKol++,2,3,0);
		WriteFld2Xls(XlsRij,XlsKol++,2,54,0);
		*d(16,30)=Round((double)(*d(16,30)),(double)(0.01));WriteFld2Xls(XlsRij,XlsKol++,16,30,0);
		*d(16,31)=Round((double)(*d(16,31)),(double)(0.01));WriteFld2Xls(XlsRij,XlsKol++,16,31,0);
		*d(16,32)=Round((double)(*d(16,32)),(double)(0.01));WriteFld2Xls(XlsRij,XlsKol++,16,32,0);
		*d(16,31)-=*d(16,32);		WriteFld2Xls(XlsRij,XlsKol++,16,31,0);
		XlsRij++;
		if((dsp_cnt_%1000)==0) {scrfld(10,16,2);scrupd(-3,0);} dsp_cnt_++;
  }
	XlsSelectWorkSheet(XlsRef,2,"Groepen");  // sheet lijst groepen
	XlsRij=1;XlsKol=1;
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Nr",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",0);
	XlsRij++;
	for(k=1;k<100;k++){
		fasinit(52);*u(52,1)=k; fasgeti(52);
		if(*s(52,14)){
			XlsKol=1;
			WriteFld2Xls(XlsRij,XlsKol++,52,1,0);
			WriteFld2Xls(XlsRij,XlsKol++,52,14,0);
			XlsRij++;
		}
	}
  XlsClose(XlsRef,1);
	fasunlck(-1);
  endsr:;
}

#endif

#if FLAGBSA
static void exp_line(long klt_rec_, long art_rec_, double qstk1_, double qstk2_, double qlit1_, double qlit2_)
{
	double groei_stk_, groei_lit_, groei_perc_;

	if (qstk1_ || qstk2_ || qlit1_ || qlit2_)
	{
		if (klt_rec_)
		{
			fasinit(2);
			*l(2, 1) = klt_rec_;
			fasgeti(2);
		}

		if (art_rec_)
		{
			fasinit(6);
			*l(6, 1) = art_rec_;
			fasgeti(6);
		}

		groei_stk_ = qstk2_ - qstk1_;
		groei_lit_ = qlit2_ - qlit1_;
		groei_perc_ = qstk1_ && qstk2_ ? ((qstk2_ / qstk1_) - 1) * 100 : groei_stk_ < 0 ? -100 : groei_stk_ > 0 ? 100 : 0;
		qstk1_ = Round(qstk1_, (double)0.01);
		qstk2_ = Round(qstk2_, (double)0.01);
		qlit1_ = Round(qlit1_, (double)0.01);
		qlit2_ = Round(qlit2_, (double)0.01);
		groei_stk_ = Round(groei_stk_, (double)0.01);
		groei_lit_ = Round(groei_lit_, (double)0.01);
		groei_perc_ = Round(groei_perc_, (double)0.01);

		if (klt_rec_ || art_rec_)
		{
			XlsKol = 1;
			XlsWrite(XlsRef, XlsRij, XlsKol++, 0, s(2, 3), 0);
			XlsWrite(XlsRef, XlsRij, XlsKol++, 0, s(6, 3), 0);
		}
		else
			XlsKol = 3;

		XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &qstk1_, 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &qstk2_, 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &groei_stk_, 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &qlit1_, 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &qlit2_, 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &groei_lit_, 0);
		XlsWrite(XlsRef, XlsRij, XlsKol++, 2, &groei_perc_, 0);
		XlsRij++;

		gqstk1 += qstk1_;
		gqstk2 += qstk2_;
		gqlit1 += qlit1_;
		gqlit2 += qlit2_;
	}
}

static exp_hisBSA()
{
	char str_[50];
	double groei_lit_, groei_perc_, qlit1_, qlit2_, qstk1_, qstk2_;
	int old_art_ = 0, old_klt_ = 0;
	int16 a_mode_, cur_klt_, curs_ = 1, dsp_cnt_ = 0, k_, key_, mode_, z_;
	long lcode_;
	uint16 dat_beg_2_ = 0, dat_end_2_ = 0, end_;

	dat_beg = 0;
	dat_end = 0;

	FOREVER {
		z_ = 1;
		scraddf(-1, 0, 0, 0);
		scraddf(z_++, 2, 25, 2);
		scraddf(z_++, 4, 5, 0); scraddf(z_++, 4, 26, 2); scraddf(z_++, 4, 35, 0); scraddf(z_++, 4, 42, 2); // Periode 1
		scraddf(z_++, 5, 5, 0); scraddf(z_++, 5, 26, 2); scraddf(z_++, 5, 35, 0); scraddf(z_++, 5, 42, 2); // Periode 2
		scraddf(z_++, 7, 5, 0); scraddf(z_++, 7, 26, 2); // Klant
		scraddf(z_++, 8, 5, 0); scraddf(z_++, 8, 26, 2); // Artikel
		scraddf(z_++, 23, 1, 8); scraddf(z_++, 23, 11, 8); // Functietoetsen 
		z_ = 1;
		DisplayMenuTitel(1, "Eporteren evolutiestatistieken naar Excel", 0xA); z_++;
		scrifld(z_++, fm_os79, "Periode verkopen 1.:");
		scrifld(z_++, fm_udat, &dat_beg);
		scrifld(z_++, VarTextFmt(6, 0), "t.e.m.");
		scrifld(z_++, fm_udat, &dat_end);
		scrifld(z_++, fm_os79, "Periode verkopen 2.:");
		scrifld(z_++, fm_udat, &dat_beg_2_);
		scrifld(z_++, VarTextFmt(6, 0), "t.e.m.");
		scrifld(z_++, fm_udat, &dat_end_2_);
        scrifld(z_++, fm_os79, "Klant..............:"); scrfld(z_++, 2, 3); scraddpicto(1, z_-1, 0, 0, 2, 1, 112, 0, 4, "Uitgebreid zoeken");
        scrifld(z_++, fm_os79, "Artikel............:"); scrfld(z_++, 6, 3); scraddpicto(2, z_-1, 0, 0, 2, 1, 112, 0, 4, "Uitgebreid zoeken");
		scrifld(z_++, VarTextFmt(9, 0), " F1 stop "); scrifld(z_++, VarTextFmt(23, 0), " F8 begin uitschrijven ");
		key_ = scrupd(curs_, 0x81); curs_ = 1;

		if ((key_ / 0x100) == 1)
			key_ = (key_ & 0xFF) + 5000;

		// F1 stop
		if (key_ == 101)
			return YES;

		switch(key_) {
			case 5001:
				if (search(2, 98))
				{
					curs_ = 4;
					continue;
				}

				break;

			case 5002:
				if (search(6, 98))
				{
					curs_ = 5;
					continue;
				}
				
				break;

			default:
				break;
		}

		if (key_ != 108)
			continue;

		// Begindatum periode 1 moet ingevuld zijn
		if (dat_beg == 0)
		{
			curs_ = 3;
			errnum = 34;
			continue;
		}

		// Einddatum periode 1 moet ingevuld zijn
		if (dat_end == 0)
		{
			curs_ = 5;
			errnum = 34;
			continue;
		}

		// Einddatum periode 1 moet na begindatum periode 1 vallen
		if (dat_end < dat_beg)
		{
			curs_ = 5;
			errnum = 34;
			continue;
		}

		// Begindatum periode 2 moet ingevuld zijn
		if (dat_beg_2_ == 0)
		{
			curs_ = 7;
			errnum = 34;
			continue;
		}

		// Einddatum periode 2 moet ingevuld zijn
		if (dat_end_2_ == 0)
		{
			curs_ = 9;
			errnum = 34;
			continue;
		}

		// Einddatum periode 2 moet na begindatum periode 2 vallen
		if (dat_end_2_ < dat_beg_2_)
		{
			curs_ = 9;
			errnum = 34;
			continue;
		}

		if (*s(2, 3))
		{
		    if (search(2, 0))
			{
				curs_ = 11;
				continue;
			}
		}
		else fasinit(2);

		inq_klt = *u(2, 1);

		if (*s(6, 3))
		{
		    if (search(6, 0))
			{
				curs_=13;
				continue;
			}
		}
		else fasinit(6);

		inq_art = *u(6, 1);

		break;
	}

	fasunlck(-2);

	zero(str_, sizeof str_);
	copy0("Evolutiestatistieken", str_, 25);
	cnv_fname(str_, 25);
	copy0(".xls", &str_[strlen(str_)], 4);
	XlsRef = XlsCreate(str_);

	if (XlsRef <= 0)
	{
		errnum = 1;
		return NO;
	}

	XlsSelectWorkSheet(XlsRef, 1, "Evolutiestatistieken"); // Sheet evolutiestatistieken
	XlsRij = 1;
	XlsKol = 1;
	XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Klant", 0);
	XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Artikel", 0);
	zero(str_, sizeof str_);
	copy0("Aantal ", str_, 7);
	date2str(&str_[strlen(&str_)], dat_beg, 0);
	copy0(" tot ", &str_[strlen(&str_)], 5);
	date2str(&str_[strlen(&str_)], dat_end, 0);
	XlsWrite(XlsRef, XlsRij, XlsKol++, 0, str_, 0);
	zero(str_, sizeof str_);
	copy0("Aantal ", str_, 7);
	date2str(&str_[strlen(&str_)], dat_beg_2_, 0);
	copy0(" tot ", &str_[strlen(&str_)], 5);
	date2str(&str_[strlen(&str_)], dat_end_2_, 0);
	XlsWrite(XlsRef, XlsRij, XlsKol++, 0, str_, 0);
	XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Groei (Aantal)", 0);
	zero(str_, sizeof str_);
	copy0("Volume ", str_, 7);
	date2str(&str_[strlen(&str_)], dat_beg, 0);
	copy0(" tot ", &str_[strlen(&str_)], 5);
	date2str(&str_[strlen(&str_)], dat_end, 0);
	XlsWrite(XlsRef, XlsRij, XlsKol++, 0, str_, 0);
	zero(str_, sizeof str_);
	copy0("Volume ", str_, 7);
	date2str(&str_[strlen(&str_)], dat_beg_2_, 0);
	copy0(" tot ", &str_[strlen(&str_)], 5);
	date2str(&str_[strlen(&str_)], dat_end_2_, 0);
	XlsWrite(XlsRef, XlsRij, XlsKol++, 0, str_, 0);
	XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Groei (Volume)", 0);
	XlsWrite(XlsRef, XlsRij, XlsKol++, 0, "Groei (%)", 0);
	XlsRij++;

	gqstk1 = 0;
	gqstk2 = 0;
	gqlit1 = 0;
	gqlit2 = 0;

	// Klant geselecteerd of niks geselecteerd
	if (inq_klt || !inq_art)
	{
		fasinit(2);
		a_mode_ = 1;
	    scrget(1, 170);
	    scrget(1, 170);
		scrifld(5, fm_os38, "Bezig met klant:");
		scrifld(9, fm_os38, "Bezig met artikel:");

		FOREVER
		{
			if (inq_klt)
			{
				*u(2, 1) = inq_klt;
				
				if (fasgeti(2))
					break;
			}
			else
			{
				if (faskeyi(2, 2, a_mode_))
					break;
			
				a_mode_ = 2;
			}

			if (inq_klt && *u(2, 1) != inq_klt)
				break;

		    fasinit(16);
		    *u(16, 10) = *u(2, 1);
			mode_ = 1;
			end_ = NO;
			qstk1_ = 0;
			qstk2_ = 0;
		    qlit1_ = 0;
			qlit2_ = 0;

		    FOREVER
			{
				if (faskeyi(16, 11, mode_))
					end_ = YES;
				
				mode_ = 2;

				if(*u(16, 10) != *u(2, 1))
					end_ = YES;

				if (end_)
				{
					if (old_art_)
						exp_line(old_klt_, old_art_, qstk1_, qstk2_, qlit1_, qlit2_);

					break;
				}

				if (inq_art && *l(16, 20) != inq_art)
					continue;

				if (fldlen(16, 15) && *l(16, 15))
					continue;

				if (*l(16, 23) == 99)
					continue;

				if (*u(16, 3) < dat_beg)
				{
					*u(16, 3) = dat_beg;
					mode_ = 1;
					continue;
				}

				if ( *u(16, 3) > dat_end_2_)
				{
					*u(16, 3) = 0xFFFF;
					mode_ = 2;
					continue;
				}

				if (*u(16, 20) != old_art_ || *u(16, 10) != old_klt_)
				{
					if (old_art_)
						exp_line(old_klt_, old_art_, qstk1_, qstk2_, qlit1_, qlit2_);

					old_art_ = *u(16, 20);
					old_klt_ = *u(16, 10);
					qstk1_ = 0;
					qstk2_ = 0;
					qlit1_ = 0;
					qlit2_ = 0;
				}

				if (dsp_cnt_ % 50 == 0)
				{
					scrfld(7, 2, 3);
					scrfld(11, 16, 22);
					scrupd(-3, 0);
				}

				dsp_cnt_++;
			
				if (*u(16, 3) >= dat_beg && *u(16, 3) <= dat_end)
				{
					qstk1_ += *d(16, 30);
					qlit1_ += *d(16, 30) * *f(6, 37);
				}

				if (*u(16, 3) >= dat_beg_2_ && *u(16, 3) <= dat_end_2_)
				{
					qstk2_ += *d(16, 30);
					qlit2_ += *d(16, 30) * *f(6, 37);
				}
			}

			if (inq_klt)
				break;
		}
	}
	// Artikel geselecteerd
	else
	{
		fasinit(6);
	    scrget(1, 170);
	    scrget(1, 170);
		scrifld(5, fm_os38, "Bezig met klant:");
		scrifld(9, fm_os38, "Bezig met artikel:");

		*u(6, 1) = inq_art;
				
		if (fasgeti(6))
			goto endsr;

		fasinit(16);
		mode_ = 1;
		end_ = NO;
		qstk1_ = 0;
		qstk2_ = 0;
		qlit1_ = 0;
		qlit2_ = 0;

		FOREVER
		{
			if (faskeyi(16, 13, mode_))
				end_ = YES;
				
			mode_ = 2;

			if (end_)
			{
				if (old_art_)
					exp_line(old_klt_, old_art_, qstk1_, qstk2_, qlit1_, qlit2_);

				break;
			}

			if (*u(16, 20) != inq_art)
				continue;

			if (fldlen(16, 15) && *l(16, 15))
				continue;

			if (*l(16, 23) == 99)
				continue;

	        if (*u(16, 3) < dat_beg)
			{
				*u(16, 3) = dat_beg;
				mode_ = 1;
				continue;
			}

		    if ( *u(16, 3) > dat_end_2_)
			{
				*u(16, 3) = 0xFFFF;
				mode_ = 2;
				continue;
			}

			if (*l(16, 20) != old_art_ || *l(16, 10) != old_klt_)
			{
				if (old_art_)
					exp_line(old_klt_, old_art_, qstk1_, qstk2_, qlit1_, qlit2_);

				old_art_ = *l(16, 20);
				old_klt_ = *l(16, 10);
				qstk1_ = 0;
				qstk2_ = 0;
				qlit1_ = 0;
				qlit2_ = 0;
			}

			if (dsp_cnt_ % 50 == 0)
			{
				fasinit(2);
				*u(2, 1) = *u(16, 10);
				fasgeti(2);
				scrfld(7, 2, 3);
				scrfld(11, 16, 22);
				scrupd(-3, 0);
			}

			dsp_cnt_++;
			
			if (*u(16, 3) >= dat_beg && *u(16, 3) <= dat_end)
			{
				qstk1_ += *d(16, 30);
				qlit1_ += *d(16, 30) * *f(6, 37);
			}

			if (*u(16, 3) >= dat_beg_2_ && *u(16, 3) <= dat_end_2_)
			{
				qstk2_ += *d(16, 30);
				qlit2_ += *d(16, 30) * *f(6, 37);
			}
		}
	}

	// Klant en/of artikel geselecteerd
	if (inq_klt || inq_art)
		exp_line(0, 0, gqstk1, gqstk2, gqlit1, gqlit2);

endsr:
	XlsClose(XlsRef,1);
	fasunlck(-1);
}
#endif

#if FLAGALB
static exp_ALBhis2XLS(akmode_)
int16 akmode_;
{
  int16 j,k,dsp_cnt_=0,fld_,a_mode;
  int16 mode,key16_=2;
	uint16 dt_;
  char str_[100];

	zero(str_,sizeof str_);
  if(akmode_){
		if(ask_AKsel("Exporteren aankoophistorieken naar TXT-bestand",2)) goto endsr;
    AK_mode=YES;inq_mast=inq_lev;mast_stu=1;mast_pos=15;
    k=copy0("Aankoophistorieken ",str_,25);
	}
  else {
		if(ask_sel("Exporteren verkoophistorieken naar XLS-bestand",2)) goto endsr;
		AK_mode=NO; inq_mast=inq_klt;mast_stu=2;mast_pos=10;
		k=copy0("Verkoophistorieken ",str_,25);
	}
	fasunlck(-2);key16_=2;
  if(inq_art){key16_=1; fasinit(6);*u(6,1)=inq_art;fasgeti(6); k+=copy0(s(6,3),&str_[k],15);}
  else if(inq_mast){fasinit(mast_stu);*u(mast_stu,1)=inq_mast;fasgeti(mast_stu); k+=copy0(s(mast_stu,3),&str_[k],15);}
  else if(inq_lev){fasinit(1);*u(1,1)=inq_lev;fasgeti(1); k+=copy0(s(1,3),&str_[k],15);}

  str_[k++]=' ';k+=date2str(&str_[k],dat_beg,1);
  str_[k++]='-';k+=date2str(&str_[k],dat_end,1);
  cnv_fname(str_,k);
  k=copy0(".XLS",&str_[k],4);
  XlsRef=XlsCreate(str_);
  if(XlsRef<=0) {errnum=30;goto endsr;}
	XlsSelectWorkSheet(XlsRef,1,"Historieken");

	StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
	StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
	StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);


  scrget(1,7);scrupd(-3,0);
  XlsRij=1;XlsKol=1;
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Datum",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Naam",StylTitel);
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Postcode",StylTitel);
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Stad",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Code",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal",StylTitel);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Factuurbedrag",StylTitel);
  XlsRij++;


  if(inq_art){
    fasinit(mast_stu);if(inq_mast){*u(mast_stu,1)=inq_mast;fasgeti(mast_stu);} a_mode=1;
    scrget(1,170);scrifld(5,fm_os38,"Bezig met :");
    FOREVER{
      next_klt:;
      if(faskeyi(mast_stu,2,a_mode)) break; a_mode=2;
			if(mast_stu==2 && sel_soortklant[0] && cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) goto next_klt;
			if((dsp_cnt_%50)==0) {scrfld(10,mast_stu,3);scrupd(-3,0);} dsp_cnt_++;

      fasinit(16);
      *l(16,20)=inq_art;
      *l(16,mast_pos)=*u(mast_stu,1); mode=1; 
      FOREVER{
	next:;
				if(faskeyi(16,2,mode)) break; mode=2;
				if(*l(16,20)!=inq_art) break;
				if(*l(16,mast_pos)!=*u(mast_stu,1)) break;
				if(ftnr_beg && *l(16,2)<ftnr_beg) goto next;
				if(ftnr_end && *l(16,2)>ftnr_end) goto next;
				if(*pu_16_3 <dat_beg) {*pu_16_3=dat_beg;mode=1; goto next;}
				if(*pu_16_3 >dat_end) {*pu_16_3=0xFFFF; mode=2;goto next;}
				if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
				if(mast_pos==10 && fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
				if(mast_pos==15 && *l(16,10)) goto next;/* geen klanten  */
				fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
				fasinit(52);*u(52,1)=*u(6,9);fasgeti(52);
				XlsKol=1;
		//		XlsWrite(XlsRef,XlsRij,XlsKol++,3,(char *)u(16,3),StylDate); // ALS DATUM DOORGEVEN //WriteFld2Xls(XlsRij,XlsKol++,16,3,0);
				WriteFld2Xls(XlsRij,XlsKol++,16,3,StylDate);
				WriteFld2Xls(XlsRij,XlsKol++,2,3,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,2,5,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,2,6,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
				*d(16,30)=Round((double)(*d(16,30)),(double)(0.01));WriteFld2Xls(XlsRij,XlsKol++,16,30,StylNormal);
				*d(16,31)=Round((double)(*d(16,31)),(double)(0.01));WriteFld2Xls(XlsRij,XlsKol++,16,31,StylNormal);
				XlsRij++;
			}
		}
	}
	else{
    fasinit(6);if(inq_art){*u(6,1)=inq_art;fasgeti(6);} a_mode=1;
    scrget(1,170);scrifld(5,fm_os38,"Bezig met artikel :");
    FOREVER{
      next_art:;
      if(faskeyi(6,2,a_mode)) break; a_mode=2;
      if(inq_art && inq_art!=*u(6,1)) break;
      if(mast_pos!=15 && inq_lev && *u(6,7)!=inq_lev) goto next_art;
			if(mast_pos!=15 && inq_merk && *u(6,101)!=inq_merk){ goto next_art;}
      if(inq_grp && *i(6,9)!=inq_grp) goto next_art;
			for(k=0;k<5;k++) if(skip_groepen[k] && skip_groepen[k]==*i(6,9)) goto next_art;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next_art;
      if(skip_leegg=='J' && *i(6,9)==99){goto next_art;}
			if((dsp_cnt_%50)==0) {scrfld(10,6,3);scrupd(-3,0);} dsp_cnt_++;
			fasinit(16);
      *l(16,20)=*u(6,1);
      *l(16,mast_pos)=inq_mast; mode=1;
      FOREVER{
	next1:;
				if(faskeyi(16,1,mode)) break; mode=2;
				if(*l(16,20)!=*u(6,1)) break;
				if(inq_mast && *l(16,mast_pos)!=inq_mast) goto next1;
					if(ftnr_beg && *l(16,2)<ftnr_beg) goto next1;
				if(ftnr_end && *l(16,2)>ftnr_end) goto next1;
				if(*pu_16_3 <dat_beg) {*pu_16_3=dat_beg;mode=1; goto next1;}
				if(*pu_16_3 >dat_end) {*pu_16_3=0xFFFF; mode=2;goto next1;}
				if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next1;
				if(mast_pos==10){
					if(fldlen(16,15) && *l(16,15)) goto next1;/* geen leveranciers */
					if(sel_soortklant[0]){
						fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
						if(sel_soortklant[0] && cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) goto next1;
					}
				}
				if(mast_pos==15 && *l(16,10)) goto next1;/* geen klanten  */
				fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
				fasinit(52);*u(52,1)=*u(6,9);fasgeti(52);
				XlsKol=1;
				WriteFld2Xls(XlsRij,XlsKol++,16,3,StylDate);
				WriteFld2Xls(XlsRij,XlsKol++,2,3,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,2,5,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,2,6,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,6,2,StylNormal);
				WriteFld2Xls(XlsRij,XlsKol++,6,3,StylNormal);
				*d(16,30)=Round((double)(*d(16,30)),(double)(0.01));WriteFld2Xls(XlsRij,XlsKol++,16,30,StylNormal);
				*d(16,31)=Round((double)(*d(16,31)),(double)(0.01));WriteFld2Xls(XlsRij,XlsKol++,16,31,StylNormal);
				XlsRij++;
			}	
		}
	}
  XlsClose(XlsRef,1);
	fasunlck(-1);
  endsr:;
}

#endif

#if FLAGKMP
static exp_his2txt(akmode_)
int16 akmode_;
{
  int16 j,k,dsp_cnt_,fld_;
  int16 mode;
  char str_[100];

	zero(str_,sizeof str_);
  if(akmode_){
		if(ask_AKsel("Exporteren aankoophistorieken naar TXT-bestand",2)) goto endsr;
    AK_mode=YES;inq_mast=inq_lev;mast_stu=1;mast_pos=15;
    k=copy0("Aankoophistorieken ",str_,25);
	}
  else {
		if(ask_sel("Exporteren verkoophistorieken naar TXT-bestand",2)) goto endsr;
		AK_mode=NO; inq_mast=inq_klt;mast_stu=2;mast_pos=10;
		k=copy0("Verkoophistorieken ",str_,25);
	}
	fasunlck(-2);
  if(inq_art){fasinit(6);*u(6,1)=inq_art;fasgeti(6); k+=copy0(s(6,3),&str_[k],15);}
  else if(inq_mast){fasinit(mast_stu);*u(mast_stu,1)=inq_mast;fasgeti(mast_stu); k+=copy0(s(mast_stu,3),&str_[k],15);}
  else if(inq_lev){fasinit(1);*u(1,1)=inq_lev;fasgeti(1); k+=copy0(s(1,3),&str_[k],15);}

  str_[k++]=' ';k+=date2str(&str_[k],dat_beg,1);
  str_[k++]='-';k+=date2str(&str_[k],dat_end,1);
  cnv_fname(str_,k);
  k=copy0(".TXT",&str_[k],4);
  errnum=fasopen(str_,12);if(errnum) goto endsr;
  scrget(1,170);scrifld(5,fm_os38,"Bezig met ");scrupd(-3,0);
  fasinit(80);seqo_pos=0;seqo_mode=2;seqo_len=0;
	zero(seqo_str,sizeof seqo_str);pos=0;
	char2str("FtNr",5);
	char2str("Datum",5);
	if(AK_mode){
  	char2str("LevNr",5);
	  char2str("LevNaam",10);
	}
	else{
  	char2str("KltNr",5);
	  char2str("KltNaam",10);
	}
	char2str("ArtNr",5);
	char2str("ArtNaam",10);
	char2str("GrpNr",5);
	char2str("GrpNaam",10);
	char2str("Aantal",10);
	char2str("Volume",10);
	char2str("VK-waarde",10);
  char2str("AK-waarde",10);
  char2str("Leeggoed",10);
	CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
	seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
/* dumpen */
	seqo_len=0;
	for(j=0;j<pos;j+=280){
		if((j+280)>pos) seqo_len=pos-j;
		else seqo_len=280;
		copy(&seqo_str[j],s(80,1)+4,seqo_len);
		seqo_flush();
	}


	dsp_cnt_=0;
	fasinit(16); *u(16,3)=dat_beg;mode=1;
	FOREVER{
		next:;
		if(faskeyi(16,10,mode)) break; mode=2;
		if(*pu_16_3 >dat_end) break;
		if(inq_art && *l(16,20)!=inq_art) goto next;
		if(inq_mast && *l(16,mast_pos)!=inq_mast) goto next;
		if(ftnr_beg && *l(16,2)<ftnr_beg) goto next;
		if(ftnr_end && *l(16,2)>ftnr_end) goto next;
		if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
		if(mast_pos==10){
			if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
			if(sel_soortklant[0] && cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) goto next;	
		}
		else{
			if(mast_pos==15 && *l(16,10)) goto next;/* geen klanten  */
			fasinit(1);*u(1,1)=*l(16,15);
			if(*u(1,1)>=30000){
				if(*u(1,1)==30000) copy("Mutatie filiaal DEPOT",s(1,3),20);
				else sprintf_s(s(1,3),20,"Mutatie filiaal %d",*u(1,1)-30000);
			}
			else if(*u(1,1)) fasgeti(1);
		}
		fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
		fasinit(52);*u(52,1)=*u(6,9);fasgeti(52);
		zero(seqo_str,sizeof seqo_str);pos=0;
		seqo_fld(16,2);
		seqo_fld(16,3);
		if(AK_mode){seqo_fld(1,1);seqo_fld(1,3);}
		else{seqo_fld(2,1);seqo_fld(2,3);}
		seqo_fld(6,2);seqo_fld(6,3);
		seqo_fld(52,1);seqo_fld(52,14);
		seqo_fld(16,30);/* stuks */
		*d(16,30)=*d(16,30)* *f(6,37); seqo_fld(16,30);/* LITERS */
		if(*i(6,9)==99){char2str("",1);char2str("",1);seqo_fld(16,31);}
		else{seqo_fld(16,31);/* omzet */	seqo_fld(16,32);/* AK-waarde */ char2str("",1);}
		CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
		seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
	/* dumpen */
		seqo_len=0;
		for(j=0;j<pos;j+=280){
			if((j+280)>pos) seqo_len=pos-j;
			else seqo_len=280;
			copy(&seqo_str[j],s(80,1)+4,seqo_len);
			seqo_flush();
		}
		if((dsp_cnt_%1000)==0) {scrfld(10,mast_stu,3);scrupd(-3,0);} dsp_cnt_++;
	}
  fasclos(-2);
	fasunlck(-1);
  endsr:;
}

#endif

#if FLAGAST
static exp_ASThis2txt(akmode_)
int16 akmode_;
{
  int16 j,k,fld_;
  int16 mode;
	long dsp_cnt_=0;
  char str_[100];

	zero(str_,sizeof str_);
  if(akmode_){
		if(ask_AKsel("Exporteren aankoophistorieken naar TXT-bestand",2)) goto endsr;
    AK_mode=YES;inq_mast=inq_lev;mast_stu=1;mast_pos=15;
    k=copy0("Aankoophistorieken",str_,25);
	}
  else {
		if(ask_sel("Exporteren verkoophistorieken naar TXT-bestand",2)) goto endsr;
		AK_mode=NO; inq_mast=inq_klt;mast_stu=2;mast_pos=10;
		k=copy0("Verkopen",str_,25);
	}
	fasunlck(-2);
  //if(inq_art){fasinit(6);*u(6,1)=inq_art;fasgeti(6); k+=copy0(s(6,3),&str_[k],15);}
  //else if(inq_mast){fasinit(mast_stu);*u(mast_stu,1)=inq_mast;fasgeti(mast_stu); k+=copy0(s(mast_stu,3),&str_[k],15);}
  //else if(inq_lev){fasinit(1);*u(1,1)=inq_lev;fasgeti(1); k+=copy0(s(1,3),&str_[k],15);}

  //str_[k++]=' ';k+=date2str(&str_[k],dat_beg,1);
  //str_[k++]='-';k+=date2str(&str_[k],dat_end,1);
  cnv_fname(str_,k);
  k=copy0(".TXT",&str_[k],4);
  errnum=fasopen(str_,12);if(errnum) goto endsr;
  scrget(1,170);scrifld(5,fm_os38,"Bezig met ");scrupd(-3,0);
  fasinit(80);seqo_pos=0;seqo_mode=2;seqo_len=0;
	zero(seqo_str,sizeof seqo_str);pos=0;
	char2str("FtNr",5);
	char2str("Datum",5);
	char2str("Filiaal",7);
	if(AK_mode){
  	char2str("LevNr",5);
//	  char2str("LevNaam",10);
	}
	else{
  	char2str("KltNr",5);
//	  char2str("KltNaam",10);
	}
	char2str("ArtNr",5);
	char2str("ArtNaam",10);
	char2str("GrpNr",5);
//	char2str("GrpNaam",10);
	char2str("Aantal",10);
	char2str("Volume",10);
	char2str("VK-waarde",10);
  char2str("AK-waarde",10);
  char2str("Leeggoed",10);
	CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
	seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
/* dumpen */
	seqo_len=0;
	for(j=0;j<pos;j+=280){
		if((j+280)>pos) seqo_len=pos-j;
		else seqo_len=280;
		copy(&seqo_str[j],s(80,1)+4,seqo_len);
		seqo_flush();
	}


	dsp_cnt_=0;
	fasinit(16); mode=1;
	FOREVER{
		next:;
		if(faskeyi(16,3,mode)) break; mode=2;
		if(*pu_16_3 <dat_beg || *pu_16_3 >dat_end) goto next;
		if(inq_art && *l(16,20)!=inq_art) goto next;
		if(inq_mast && *l(16,mast_pos)!=inq_mast) goto next;
		if(ftnr_beg && *l(16,2)<ftnr_beg) goto next;
		if(ftnr_end && *l(16,2)>ftnr_end) goto next;
		if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
		if(mast_pos==10){
			if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
			if(sel_soortklant[0] && cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) goto next;	
		}
		else{
			if(mast_pos==15 && *l(16,10)) goto next;/* geen klanten  */
			fasinit(1);*u(1,1)=*l(16,15);
			if(*u(1,1)>=30000){
				if(*u(1,1)==30000) copy("Mutatie filiaal DEPOT",s(1,3),20);
				else sprintf_s(s(1,3),20,"Mutatie filiaal %d",*u(1,1)-30000);
			}
			else if(*u(1,1)) fasgeti(1);
		}
		fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
		fasinit(52);*u(52,1)=*u(6,9);fasgeti(52);
		zero(seqo_str,sizeof seqo_str);pos=0;
		seqo_fld(16,2);
		seqo_fld(16,3);
		seqo_fld(16,8);
		if(AK_mode){seqo_fld(1,1);}// mseqo_fld(1,3);}
		else{seqo_fld(2,2);} //seqo_fld(2,3);}
		seqo_fld(6,2); seqo_fld(6,3);
		seqo_fld(52,1);// seqo_fld(52,14);
		seqo_fld(16,30);/* stuks */
		*d(16,30)=*d(16,30)* *f(6,37); seqo_fld(16,30);/* LITERS */
		if(*i(6,9)==99){char2str("",1);char2str("",1);seqo_fld(16,31);}
		else{seqo_fld(16,31);/* omzet */	seqo_fld(16,32);/* AK-waarde */ char2str("",1);}
		CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
		seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
	/* dumpen */
		seqo_len=0;
		for(j=0;j<pos;j+=280){
			if((j+280)>pos) seqo_len=pos-j;
			else seqo_len=280;
			copy(&seqo_str[j],s(80,1)+4,seqo_len);
			seqo_flush();
		}
		if((dsp_cnt_%1000)==0) {scrfld(10,mast_stu,3);scrupd(-3,0);} dsp_cnt_++;
	}
  fasclos(-2);

	scrnum=0;scrget(1,170);scrifld(10,VarTextFmt(50),"Exporteren klanten ...."); scrupd(-3,0);
	fasunlck(-2); dsp_cnt_=0;
  k=copy0("Klanten.TXT",&str_[k],4);
  errnum=fasopen("Klanten.TXT",12);if(errnum) goto endsr;
  fasinit(80);seqo_pos=0;seqo_mode=2;seqo_len=0;
	zero(seqo_str,sizeof seqo_str);pos=0;
 	char2str("KltNr",5);
  char2str("KltNaam",7);
  char2str("Adres",10);
  char2str("PostCode",10);
  char2str("Gemeente",10);
  char2str("BTW-nummer",10);
  char2str("Telefoon",10);
  char2str("E-mail",10);
  char2str("Prijstype",10);
  char2str("SoortKlant",10);
	CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
	seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
/* dumpen */
	seqo_len=0;
	for(j=0;j<pos;j+=280){
		if((j+280)>pos) seqo_len=pos-j;
		else seqo_len=280;
		copy(&seqo_str[j],s(80,1)+4,seqo_len);
		seqo_flush();
	}
  fasinit(2);mode=1;
	FOREVER{
		if(faskeyi(2,2,mode)) break; mode=2;
		zero(seqo_str,sizeof seqo_str);pos=0;
		seqo_fld(2,2);
		seqo_fld(2,3);
		seqo_fld(2,4);
		seqo_fld(2,5);
		seqo_fld(2,6);
		seqo_fld(2,10);
		seqo_fld(2,8);
		seqo_fld(2,21);
		seqo_fld(2,26);
    seqo_fld(2,54);
		CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
		seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
	/* dumpen */
		seqo_len=0;
		for(j=0;j<pos;j+=280){
			if((j+280)>pos) seqo_len=pos-j;
			else seqo_len=280;
			copy(&seqo_str[j],s(80,1)+4,seqo_len);
			seqo_flush();
		}
		if((dsp_cnt_%500)==0) {scrfld(15,2,3);scrupd(-3,0);} dsp_cnt_++;
	}
	fasclos(-2);
	fasunlck(-1);
  endsr:;
}

#endif

static makegrafiek()
{
  int16 j,k,n,mode,rij_,kolom_,mm_beg,yy_beg,yy,dd,mm,ref_,ok_;
  int16 key,z,curs=1,used_,err_,sw,max_rij,is_kassavk_;
  uint16 dt_,dt_graf[50];
  long last_klt,last_art,color;
  char str_[80],*txtwaarde_,nm_lev[50],nm_merk[50];
  double bd_;
 
  if(AK_mode){inq_mast=inq_lev;mast_stu=1;mast_pos=15;}
  else {inq_mast=inq_klt;mast_stu=2;mast_pos=10;}
  if(skip_leegg=='\0') skip_leegg='J';
	if(skip_gratis_art=='\0') skip_gratis_art='N';
	if(skip_kasverkopen=='\0') skip_kasverkopen='N';
  if(groep_grafiek=='\0') groep_grafiek='M';
  if(soort_waarde=='\0') soort_waarde='O';
	if(SoortVerkopen=='\0') SoortVerkopen='T';
  fasinit(1); if(inq_lev){*u(1,1)=inq_lev;fasgeti(1);} copy(s(1,3),nm_lev,fldlen(1,3));
  fasinit(2); if(inq_klt){*u(2,1)=inq_klt;fasgeti(2);}
  fasinit(6); if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
  fasinit(1); if(inq_merk){*u(1,1)=inq_merk;fasgeti(1);} copy(s(1,3),nm_merk,fldlen(1,3)); 
  FOREVER{
    redo:;
    scrget(2,316);z=1;

    DisplayMenuTitel(1,"Opmaken grafiek",0x3);z++;
    scrifld(z++,fm_udat,&dat_beg);
    scrifld(z++,fm_udat,&dat_end);
    scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		if(fldlen(2,54)){fmt_get(2,54);scrifld(z++,fmt,sel_soortklant);} else z++;
    scrfld(z++,6,3);scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    fmt_get(1,3);scrifld(z++,fmt,nm_lev);scraddpicto(3,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    if(fldlen(6,101)){
		  fmt_get(1,3);scrifld(z++,fmt,nm_merk);scraddpicto(4,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		} else z++;
    scrifld(z++,fm_uu2,&inq_grp);
    scrifld(z++,fm_uGMD,&groep_grafiek);
    scrifld(z++,fm_uAVOW,&soort_waarde);
		scrifld(z++,fm_uAHKT,&SoortVerkopen);
    scrifld(z++,fm_u04,&comp_vj);
    scrifld(z++,fm_uJN,&skip_leegg);
	//	scrifld(z++,fm_uJN,&skip_kasverkopen);
    key=scrupd(curs,0x81);curs=1;
    if(key==101) goto endsr;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		switch(key){
				case 5001 : if(search(2,98)) {curs=4;goto redo;} break;
				case 5002 : if(search(6,98)) {curs=6;goto redo;} break;
				case 5003 : copy(nm_lev,s(1,3),fldlen(1,3));
					          if(search(1,98)){curs=7; goto redo;} 
										else copy(s(1,3),nm_lev,fldlen(1,3));
										break;
				case 5004 : copy(nm_merk,s(1,3),fldlen(1,3));
					          if(search(1,98)){curs=8; goto redo;} 
										else copy(s(1,3),nm_merk,fldlen(1,3));
										break;
				default : break;
		}
		if(dat_beg==0) {errnum=34;curs=2;goto redo;}
    if(dat_end<dat_beg) {curs=3;errnum=34;goto redo;}
    if(*s(2,3)){
      if(search(2,0)){curs=4;goto redo;}
    } else fasinit(2);
    inq_klt=*u(2,1);
    if(*s(6,3)){
      if(search(6,0)){curs=6;goto redo;}
    } else fasinit(6);
    inq_art=*u(6,1);
		if(nm_lev[0]){
      fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=7;goto redo;}
	    copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
    } else inq_lev=0;
	  if(nm_merk[0]){
      fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=8;goto redo;}
	    copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
    } else inq_merk=0;
    if(comp_vj<0 || comp_vj>MAX_VJ) {errnum=34;curs=11;goto redo;}
		if(comp_vj && SoortVerkopen=='A'){
			{errnum=34;curs=13;goto redo;}
		}
    if(comp_vj){/* periode mag dan niet meer dan 1 jaar zijn */
      jddate(dat_beg,&yy,&mm,&dd);
      dt_=datejd(yy+1,mm,dd);
      if(dat_end>=dt_) {curs=3; errnum=76; goto redo;}
    }
 
    if(key==108) break;
  }
  if(AK_mode){inq_mast=inq_lev;mast_stu=1;mast_pos=15;}
  else {inq_mast=inq_klt;mast_stu=2;mast_pos=10;}
	fasunlck(-2);
  scrget(1,170);scrifld(5,fm_odsp,"Berekenen grafiekgegevens...");scrupd(-3,0);
  zero((char *)&tb_periode[0][0], sizeof tb_periode);max_periode=0;
	if(SoortVerkopen=='A'){
		max_periode+=2;
	}
	else{
		for(k=comp_vj;k>0;k--){
			jddate(dat_beg,&yy,&mm,&dd);
			tb_periode[max_periode][0]=datejd(yy-k,mm,dd);
			jddate(dat_end,&yy,&mm,&dd);
			tb_periode[max_periode][1]=datejd(yy-k,mm,dd);
			max_periode++;
		}
	}
  tb_periode[max_periode][0]=dat_beg;
  tb_periode[max_periode][1]=dat_end;
  max_periode++;
  zero((char *)&tabel[0][0], sizeof tabel);
  zero((char *)&dt_graf[0],sizeof dt_graf);
  jddate(dat_beg,&yy_beg,&mm_beg,&dd);
  dt_=dat_beg;
	if(NO /* SoortVerkopen=='A'*/){
		for(max_rij=0;max_rij<2;max_rij++){
			dt_graf[max_rij]=dt_;
		}
	}
	else{
		for(max_rij=0;max_rij<50;max_rij++){
			jddate(dt_,&yy,&mm,&dd);
			mm++;if(mm>12) {mm=1;yy++;}
			dt_=datejd(yy,mm,1)-1;
			if(dt_>dat_end) dt_=dat_end;
			dt_graf[max_rij]=dt_;
			dt_++;
			if(dt_>=dat_end) break;
		}
	}
  max_rij++;
  fasinit(mast_stu);
  for(k=0;k<105;k++) grp_nr[k]=k;
  fasinit(16);*l(16,mast_pos)=inq_mast;*l(16,20)=inq_art;
  fkey=2; if(inq_mast==0 && inq_art) fkey=1;
  last_klt=0xFFFF; last_art=0xFFFF; mode=1;used_=NO;
  FOREVER{
    next:;
    if(faskeyi(16,fkey,mode)) break; mode=2;
    dsp_working();
    if(mast_pos==10 && fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
    if(mast_pos==15 && *l(16,10)) goto next;/* geen klanten  */
		is_kassavk_=NO;
		if(fldlen(16,39) && *s(16,39)==YES){
			if(SoortVerkopen=='H') goto next;
			else is_kassavk_=YES;
		}
		if(is_kassavk_==NO){
			for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,10)==KasKltRec[j]) break;
			if(j<10){
				if(SoortVerkopen=='H') goto next;
			  else is_kassavk_=YES;
			}
			else if(SoortVerkopen=='K') goto next;
		}
    if(fkey==2){
      if(*l(16,mast_pos)!=last_klt){
				err_=NO;
				if(inq_mast && *l(16,mast_pos)!=inq_mast) break;
				else{
					fasinit(mast_stu);*u(mast_stu,1)=*l(16,mast_pos); if(fasgeti(mast_stu)) err_=YES;
					if(!err_ && sel_soortklant[0] && cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) err_=YES;
				}
				if(err_){
					*l(16,mast_pos)+=1;*l(16,20)=0;*pu_16_3=0;mode=1;
					goto next;
				}
				last_klt=*l(16,mast_pos);used_=NO;last_art=0xFFFF;
			}
			if(*l(16,20)!=last_art){
				err_=NO;
				if(inq_art && *l(16,20)!=inq_art) err_=YES;
				if(err_==NO){
					fasinit(6);*u(6,1)=*l(16,20); if(fasgeti(6)) err_=YES;
					if(inq_grp && *i(6,9)!=inq_grp) err_=YES;
					if(skip_leegg=='J' && *u(6,9)==99) err_=YES;
					if(mast_pos!=15 && inq_lev && *u(6,7)!=inq_lev) err_=YES;
					if(mast_pos!=15 && inq_merk && *u(6,101)!=inq_merk) err_=YES;
				}
				if(err_) {*l(16,20)+=1;*pu_16_3=0;mode=1;goto next;}
				last_art=*l(16,20);
      }
    }
    else{
      if(inq_art && *l(16,20)!=inq_art) break;
			fasinit(6);*u(6,1)=*l(16,20); if(fasgeti(6)) goto next;
			if(inq_grp && *i(6,9)!=inq_grp) goto next;
			if(skip_leegg=='J' && *u(6,9)==99) goto next;
			if(mast_pos!=15 && inq_lev && *u(6,7)!=inq_lev) goto next;
			if(mast_pos!=15 && inq_merk && *u(6,101)!=inq_merk) goto next;
			
      if(*l(16,mast_pos)!=last_klt){
				err_=NO;
				fasinit(mast_stu);*u(mast_stu,1)=*l(16,mast_pos); if(fasgeti(mast_stu)) err_=YES;
				if(!err_ && sel_soortklant[0] && cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) err_=YES;
				if(err_){
					*l(16,mast_pos)+=1;*pu_16_3=0;mode=1; goto next;
				}
				last_klt=*l(16,mast_pos);used_=NO;
      }
    }
    if(*pu_16_3 < tb_periode[0][0]) {*pu_16_3=tb_periode[0][0];mode=1; goto next;}
    if(*pu_16_3 > tb_periode[max_periode-1][1]) {*pu_16_3=0xFFFF;mode=2; goto next;}
		if(SoortVerkopen=='A'){
			if(is_kassavk_) kolom_=0;
			else kolom_=1;
			ok_=YES;
		}
		else{
			ok_=NO;
			for(kolom_=0;kolom_<max_periode;kolom_++){
				if(*pu_16_3>=tb_periode[kolom_][0] && *pu_16_3<=tb_periode[kolom_][1]) {ok_=YES;break;}
 
				if(*pu_16_3<tb_periode[kolom_][0]){*pu_16_3=tb_periode[kolom_][0];mode=1;break;}
				if(*pu_16_3>tb_periode[kolom_][1]) continue;

			}
		}
    if(ok_==NO) goto next;/* buiten periode */

		if(groep_grafiek=='D'){/* totalen per dag */
		  rij_=*pu_16_3 % 7;if(rij_>=0 && rij_<=6) rij_=dag_nr[rij_];
		}
    else if(groep_grafiek=='G'){/* totalen par groep */
      rij_=*u(6,9)-1; if(rij_<0 || rij_>98) rij_=0;
    }
    else{/* totalen per maand */
      if(*pu_16_3<dat_beg){
				jddate(*pu_16_3,&yy,&mm,&dd);
				yy=yy_beg; if(mm<mm_beg) yy++;/* geen kalenderjaar */
				dt_=datejd(yy,mm,1);/* converteren naar 1-ste dag v/d/ maand */
			}
      else dt_=*pu_16_3;
      for(rij_=0;rij_<max_rij;rij_++) if(dt_graf[rij_]>=dt_) break;
    }
    bd_=0;
    switch(soort_waarde){
      case 'O' : bd_=*d(16,31); break;/* netto VW */
      case 'A' : bd_=*d(16,30); break;/* stuks */
#if FLAGGOU || FLAGHDY
      case 'V' : bd_=*d(16,29); break;/* gewicht */
#endif
#if FLAGSAP
      case 'V' : bd_=*d(16,30)* *f(6,38); break;/* gewicht */
#endif
#if !FLAGSAP && !FLAGGOU && !FLAGHDY
      case 'V' : bd_=*d(16,30)* *f(6,37); break;/* liters */
#endif
      case 'W' : bd_=*d(16,31)-*d(16,32); break;/* winst */
      default  : break;
    }
    tabel[rij_][kolom_]+=bd_;
    tabel[102][kolom_]+=bd_;/* totaal */
		if(SoortVerkopen=='A'){
			tabel[rij_][2]+=bd_;
      tabel[102][2]+=bd_;/* totaal */
		}
		//else{
  //    tabel[rij_][kolom_]+=bd_;
  //    tabel[102][kolom_]+=bd_;/* totaal */
		//}
    used_=YES;
  }
  scrnum=0;scrget(1,170);scrifld(10,fm_os63,"Uitschrijven gegevens naar GRAFIEK.TXT");scrupd(-3,0);
  if(groep_grafiek=='G' || groep_grafiek=='D'){
    for(k=0;k<100;k++){/* totaal per groep */
      for(j=0;j<max_periode;j++){
				tabel[k][MAX_VJ+1]+=tabel[k][j];
      }
    }
    n=MAX_VJ+1;
		if(groep_grafiek!='D' ){
			FOREVER{/* sorteren */
				sw=NO;
				for(k=0;k<99;k++){
					if(tabel[grp_nr[k]][n]<tabel[grp_nr[k+1]][n]){
						j=grp_nr[k];grp_nr[k]=grp_nr[k+1];grp_nr[k+1]=j;
						sw=YES;
					}
				}
				if(sw==NO) break;
			}
		}
    dsp_working();
    for(max_rij=0;max_rij<10;max_rij++){
      if(tabel[grp_nr[max_rij]][n]==0) break;
    }
    for(k=0;k<100;k++){
      for(j=0;j<max_periode;j++){
				tabel[100][j]+=tabel[grp_nr[k]][j];/* totaal */
				if(k>=max_rij){/* totaal rest */
					tabel[101][j]+=tabel[grp_nr[k]][j];
					tabel[101][MAX_VJ+1]+=tabel[grp_nr[k]][j];
				}
      }
    }
		dsp_working();
    zero(str_,sizeof str_);
    k=copy0("Stat_",str_,5);
    if(inq_mast){fasinit(mast_stu);*u(mast_stu,1)=inq_mast;fasgeti(mast_stu); k+=copy0(s(mast_stu,3),&str_[k],15);}
    else if(inq_art){fasinit(6);*u(6,1)=inq_art;fasgeti(6); k+=copy0(s(6,3),&str_[k],15);}
    else{
			if(SoortVerkopen=='K') k+=copy0("Kassaverkopen",&str_[k],13);
			else if(SoortVerkopen=='H') k+=copy0("Horecaverkopen",&str_[k],14);
			else k+=copy0("Totaal",&str_[k],6);
		}
    cnv_fname(str_,k);
    k=copy0(".XLS",&str_[k],4);
    ref_=XlsCreate(str_);
    if(ref_<=0) {errnum=1;return NO;}
    XlsRij=1+XLS_FIRST_DATA_ROW;XlsKol=1;
    XlsWrite(ref_,XlsRij,XlsKol++,0,"Groep",0);
    txtwaarde_="";
    switch(soort_waarde){
      case 'O' : txtwaarde_="Omzet"; break;/* netto VW */
      case 'A' : txtwaarde_="Stuks"; break;/* stuks */
#if FLAGGOU || FLAGSAP
      case 'V' : txtwaarde_="Gewicht"; break;/* volume */
#else
      case 'V' : txtwaarde_="Volume"; break;/* volume */
#endif
      case 'W' : txtwaarde_="Winst"; break;/* winst */
      default  : txtwaarde_=""; break;
    }
    for(k=0;k<max_periode;k++){
			dsp_working();
			if(SoortVerkopen=='A'){
				if(k==0) XlsWrite(ref_,XlsRij,XlsKol++,0,"Kassa",0);
				else if(k==1) XlsWrite(ref_,XlsRij,XlsKol++,0,"Horeca",0);
				else XlsWrite(ref_,XlsRij,XlsKol++,0,txtwaarde_,0);
			}
			else{
				if(k==max_periode-1) XlsWrite(ref_,XlsRij,XlsKol++,0,txtwaarde_,0);
				else {
					jddate(tb_periode[k][0],&yy,&mm,&dd);
					stcli_d(str_,(long)yy,4,1);
					XlsWrite(ref_,XlsRij,XlsKol++,0,str_,0);
				}
			}
    }
		XlsRij++;
    for(k=0;k<max_rij+1;k++){
      XlsKol=1;n=k; if(k>=max_rij) n=101;
			if(groep_grafiek=='D'){
				zero(str_,sizeof str_); 
				if(grp_nr[n]>=0 && grp_nr[n]<=6) copy0(Dagnaam[grp_nr[n]],str_,10);
        else copy0("Overig",str_,10);
        if(n==101 && tabel[101][MAX_VJ+1]==0) break;
				XlsWrite(ref_,XlsRij+k,XlsKol++,0,str_,0);
			}
			else{
				fasinit(52);*u(52,1)=grp_nr[n]+1;zero(str_,sizeof str_);
				if(n==101) copy0("Overig",str_,10);
				else{
					if(fasgeti(52)==0) copy0(s(52,14),str_,fldlen(52,14));
				}
				if(n==101 && tabel[101][MAX_VJ+1]==0) break;
				XlsWrite(ref_,XlsRij+k,XlsKol++,0,str_,0);
			}
      for(j=0;j<max_periode;j++){
				bd_=Round((double)tabel[grp_nr[n]][j],(double)(0.01));
				XlsWrite(ref_,XlsRij+k,XlsKol++,2,&bd_,0);
      }
    }
    k++; XlsKol=1;
    XlsWrite(ref_,XlsRij+k,XlsKol++,0,"Totaal",0);/* totaal uitschrijven */
    for(j=0;j<max_periode;j++){
      bd_=Round((double)tabel[102][j],(double)(0.01));
      XlsWrite(ref_,XlsRij+k,XlsKol++,2,&bd_,0);
    }
    zero(str_,sizeof str_);k=0;
    if(inq_mast){fasinit(mast_stu);*u(mast_stu,1)=inq_mast;fasgeti(mast_stu); k=copy0(s(mast_stu,3),str_,40);}
    else if(inq_art){fasinit(6);*u(6,1)=inq_art;fasgeti(6); k=copy0(s(6,3),str_,30);}
    else{
			if(SoortVerkopen=='K') k=copy0("Kassaverkopen",&str_[k],13);
			else if(SoortVerkopen=='H') k=copy0("Horecaverkopen",&str_[k],14);
			else k=copy0("Totaal",&str_[k],6);
		}
    str_[k++]=' '; // copy("\x0D\x0A",&str_[k],2);k+=2;
    k+=date2str(&str_[k],dat_beg,0);
    str_[k++]='-';k+=date2str(&str_[k],dat_end,0);
    k=max_rij+1; if(n==101 && tabel[grp_nr[101]][MAX_VJ+1]==0) k=max_rij;
    XlsChart(ref_,k,max_periode,0,str_);
    color=0x00FF00L;
/*  XlsGraf(ref_,1,1,color); */
   // XlsSaveAsPdf(ref_);
    XlsClose(ref_,1);
  }
  else{
    zero(str_,sizeof str_);
    k=copy0("Stat_",str_,5);
    if(inq_mast){fasinit(mast_stu);*u(mast_stu,1)=inq_mast;fasgeti(mast_stu); k+=copy0(s(mast_stu,3),&str_[k],15);}
    else if(inq_art){fasinit(6);*u(6,1)=inq_art;fasgeti(6); k+=copy0(s(6,3),&str_[k],15);}
    else{
			if(SoortVerkopen=='K') k+=copy0("Kassaverkopen",&str_[k],13);
			else if(SoortVerkopen=='H') k+=copy0("Horecaverkopen",&str_[k],14);
			else k+=copy0("Totaal",&str_[k],6);
		}
    cnv_fname(str_,k);
    k=copy0(".XLS",&str_[k],4);
    ref_=XlsCreate(str_);
    if(ref_<=0) {errnum=1;return NO;}
		XlsRij=1+XLS_FIRST_DATA_ROW;XlsKol=1; 
		XlsWrite(ref_,XlsRij,XlsKol++,0,"Periode",0);
    txtwaarde_="";
    switch(soort_waarde){
      case 'O' : txtwaarde_="Omzet"; break;                     /* netto VW */
      case 'A' : txtwaarde_="Stuks"; break;                        /* stuks */
#if FLAGGOU || FLAGSAP || FLAGHDY
      case 'V' : txtwaarde_="Gewicht"; break;/* volume */
#else
      case 'V' : txtwaarde_="Volume"; break;/* volume */
#endif
      case 'W' : txtwaarde_="Winst"; break;                        /* winst */
      default  : txtwaarde_=""; break;
    }

    for(k=0;k<max_periode;k++){
			if(SoortVerkopen=='A'){
				if(k==0) XlsWrite(ref_,XlsRij,XlsKol++,0,"Kassa",0);
				else if(k==1) XlsWrite(ref_,XlsRij,XlsKol++,0,"Horeca",0);
				else XlsWrite(ref_,XlsRij,XlsKol++,0,txtwaarde_,0);
			}
			else{
				if(k==max_periode-1) XlsWrite(ref_,XlsRij,XlsKol++,0,txtwaarde_,0);
				else {
					jddate(tb_periode[k][0],&yy,&mm,&dd);
					stcli_d(str_,(long)yy,4,1);
					XlsWrite(ref_,XlsRij,XlsKol++,0,str_,0);
				}
			}





    //  if(k==max_periode-1) XlsWrite(ref_,XlsRij,XlsKol++,0,txtwaarde_,0);
    //  else {
				//jddate(tb_periode[k][0],&yy,&mm,&dd);
				//stcli_d(str_,(long)yy,4,1);
				//XlsWrite(ref_,XlsRij,XlsKol++,0,str_,0);
    //  }
    }
		XlsRij++;
    for(k=0;k<max_rij;k++){
			dsp_working();
      XlsKol=1;

      jddate(dt_graf[k],&yy,&mm,&dd);
      zero(str_,sizeof str_); str_[0]=' '; // str_[0]='\'';
      if(mm>=1 && mm<=12) copy(mnd_str[mm-1],&str_[1],3);
      else copy("   ",&str_[1],3);
      if(max_periode<=1){
				str_[4]=' ';
				stcli_d(&str_[5],(long)yy,4,0);
      }
      XlsWrite(ref_,XlsRij+k,XlsKol++,0,str_,0);

      for(j=0;j<max_periode;j++){
				bd_=Round((double)tabel[k][j],(double)(0.01)) ;
				XlsWrite(ref_,XlsRij+k,XlsKol++,2,&bd_,0);
      }
    }
    k++; XlsKol=1;
    XlsWrite(ref_,XlsRij+k,XlsKol++,0,"Totaal",0);          /* totaal uitschrijven */
    for(j=0;j<max_periode;j++){
      bd_=Round((double)tabel[102][j],(double)(0.01));
      XlsWrite(ref_,XlsRij+k,XlsKol++,2,&bd_,0);
    }

    zero(str_,sizeof str_);k=0;
    if(inq_mast){fasinit(mast_stu);*u(mast_stu,1)=inq_mast;fasgeti(mast_stu); k=copy0(s(mast_stu,3),str_,40);}
    else if(inq_art){fasinit(6);*u(6,1)=inq_art;fasgeti(6); k=copy0(s(6,3),str_,30);}
    else{
			if(SoortVerkopen=='K') k=copy0("Kassaverkopen",&str_[k],13);
			else if(SoortVerkopen=='H') k=copy0("Horecaverkopen",&str_[k],14);
			else k=copy0("Totaal",&str_[k],6);
		}
    str_[k++]=' ';// copy("\x0D\x0A",&str_[k],2);k+=2;
    k+=date2str(&str_[k],dat_beg,0);
    str_[k++]='-';k+=date2str(&str_[k],dat_end,0);
    XlsChart(ref_,max_rij,max_periode/*XlsKol-2*/,0,str_);
    color=0x00FF00L;
/*  XlsGraf(ref_,qkol_-1,1,color); */
    // XlsSaveAsPdf(ref_);
    XlsClose(ref_,1);
  }
	fasunlck(-1);
  endsr:;
}

static ExportHis1Leverancier()// universele export gelijkaardig aan Coca-Cola-module
{
  int16 j,k,z,key,curs=1,mode_,dd,mm,jj;
  int16 used_,knr_;
  char fil_coc[50],buf_[100],sel_verpl='\0',SelSoortKlant[10],SelTypeKlant,SelLevRef,SelLevFabr,buf1000_[1000];
  uint16 *p_lev_,SelGroepen[5],chkgrp_,last_art;
	double aantal_,bedrag_;
  long lbd_;

	struct{
    uint16 ArtRec;
    float KltAantal;
  } TbStat[MAX_TBSTAT];
  int16 MaxStat=0;
  uint16 RecLev=0,InqKlt=0;
	
	zero((char *)&TbStat[0].ArtRec, sizeof TbStat);
	zero((char *)SelGroepen,sizeof SelGroepen);
  fasinit(1);fasinit(2);fasinit(6);SelLevFabr='L';
	SelLevRef='N';if(fldlen(6,8)==0) SelLevRef='N';
  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,2,12,3);
    scraddf(z++,5,5,0);scraddf(z++,5,34,2); scraddf(z++,5,43,0);scraddf(z++,5,50,2);
		scraddf(z++,7,5,9);
    scraddf(z++,8,5,0);scraddf(z++,8,34,2);
		scraddf(z++,9,34,0);scraddf(z++,9,68,2);scraddf(z++,9,69,0);
    scraddf(z++,11,5,0);scraddf(z++,11,34,2);
		scraddf(z++,12,5,0);scraddf(z++,12,44,2);
		scraddf(z++,13,5,0);scraddf(z++,13,44,2);scraddf(z++,13,47,2);scraddf(z++,13,50,2);scraddf(z++,13,53,2);scraddf(z++,13,56,2);
		scraddf(z++,14,5,9);
		scraddf(z++,15,5,0);scraddf(z++,15,34,2);
		scraddf(z++,16,5,0);scraddf(z++,16,44,2);
		scraddf(z++,17,5,0);scraddf(z++,17,44,2);
		scraddf(z++,18,5,0);scraddf(z++,18,44,2);
    scraddf(z++,23,1,8);scraddf(z++,23,11,8);scraddf(z++,23,25,8);scraddf(z++,23,41,8);
    z=1;
    scrifld(z++,VarTextFmt(55,0),"Exporteren omzetgegevens van klanten voor 1 leverancier");
    scrifld(z++,fm_os79,"Selectie periode ......... :");
    scrifld(z++,fm_udat,&dat_beg);
    scrifld(z++,VarTextFmt(9,0),"t.e.m.");
    scrifld(z++,fm_udat,&dat_end);
		scrifld(z++,VarTextFmt(19,0)," Selectie artikels "); 
    scrifld(z++,fm_os79,"Leverancier .............. :");scrfld(z++,1,3);
		scrifld(z++,fm_os79,"(Leverancier of Fabrikant (L/F) :");scrifld(z++,fm_uLF,&SelLevFabr); scrifld(z++,fm_os1,")");
    scrifld(z++,fm_os79,"Selectie 1 artikel ....... :");scrfld(z++,6,3);
		scrifld(z++,fm_os79,"Referentie leverancier ingevuld (J/N):"); if(fldlen(6,8)) scrifld(z++,fm_uJN,&SelLevRef); else z++;
		scrifld(z++,fm_os79,"Selectie groep(en) ................. :"); for(k=0;k<5;k++) scrifld(z++,fm_uu2,&SelGroepen[k]); 
		scrifld(z++,VarTextFmt(18,0)," Selectie klanten ");
		scrifld(z++,fm_os79,"Selectie 1 klant ......... :");scrfld(z++,2,3);
		scrifld(z++,fm_os79,"Selectie soort klant ............... :"); scrfld(z++,2,54);
    scrifld(z++,fm_os79,"Selectie prijstype (0-5) ........... :"); scrfld(z++,2,26);
		scrifld(z++,fm_os79,"Selectie Verplichting soft ......... :"); scrifld(z++,fm_us1U,&sel_verpl);
    scrifld(z++,VarTextFmt(9,0)," F1 stop");scrifld(z++,fm_os13," F8 neem aan"); scrifld(z++,VarTextFmt(30,0)," F9 kies artikels en neem aan ");
    key=scrupd(curs,0x381);curs=1;
    if(key==101) return YES;
    if(dat_beg==0) {errnum=34;goto redo;}
    if(dat_end<dat_beg) {curs=5;errnum=34;goto redo;}
		if(*s(1,3)){
      if(search(1,0)){curs=8;goto redo;}
		} else fasinit(1);
    RecLev=*u(1,1);
    if(*s(6,3)){
			if(search(6,0)){curs=12;goto redo;}
		} else fasinit(6);
		inq_art=*u(6,1);
		if(*s(2,3)){
      if(search(2,0)){curs=28;goto redo;}
			InqKlt=*u(2,1);
		} else InqKlt=0;
    InqKlt=*u(2,1);
#if !FLAGRUB
		if(key!=109 && RecLev==0 && inq_art==0) {errnum=38;curs=8;goto redo;}
#endif
		copy(s(2,54),SelSoortKlant,fldlen(2,54));SelTypeKlant=*s(2,26);
		if(fldlen(2,80)==0) sel_verpl='\0';
    if(key==109){
			zero((char *)&TbStat[0].ArtRec, sizeof TbStat);MaxStat=0;
			UpdateCorrectieRecords(YES); // zelf ingeven artikels
			for(k=0;k<max_line;k++){
				RamBon2Tblin(k);
				if(tblin.rec){		
					TbStat[MaxStat++].ArtRec=tblin.rec;
					if(MaxStat>=MAX_TBSTAT) break;
				}
			}
			if(MaxStat==0) goto redo;
		}
    if(key!=108 && key!=109) goto redo;

		zero(fil_coc,sizeof fil_coc);
		k=copy0("STAT_",fil_coc,5);
		k+=copy0(s(25,1),&fil_coc[k],25);fil_coc[k++]='_';
    jddate(dat_end,&jj,&mm,&dd); 
		stcli_d(&fil_coc[k],(long)(dd),2,0);k+=2;
		stcli_d(&fil_coc[k],(long)(mm),2,0);k+=2;
		stcli_d(&fil_coc[k],(long)(jj),4,0);k+=4;
		copy0(".XLS",&fil_coc[k],4);
    XlsRef=XlsCreate(fil_coc);
    if(XlsRef<=0) {errnum=30;curs=12;goto redo;}
	  XlsRij=1;XlsKol=1;
    break;
  }
	scrget(1,7);scrupd(-3,0);
	chkgrp_=NO;for(k=0;k<5;k++) if(SelGroepen[k]){chkgrp_=YES;break;}
	p_lev_=u(6,7); if(fldlen(6,101) && SelLevFabr=='F') p_lev_=u(6,101);
	if(key==108){
		fasinit(6); mode_=1;MaxStat=0;
		FOREVER{
			next6:;
			if(faskeyi(6,2,mode_)) break; mode_=2;
			if(inq_art && *u(6,1)!=inq_art) goto next6;
			if(RecLev && *p_lev_!=RecLev) goto next6;
			if(SelLevRef=='J' && *s(6,8)=='\0') goto next6;
			if(chkgrp_){
				for(k=0;k<5;k++) if(SelGroepen[k]==*i(6,9)) break;
				if(k>=5) goto next6;
			}
			TbStat[MaxStat++].ArtRec=*u(6,1);
			if(MaxStat>=MAX_TBSTAT) break;
		}
	}
#if !FLAGRUB
  for(k=0;k<7;k++) XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",0); // leeg
  for(k=0;k<MaxStat;k++){
		fasinit(6);*u(6,1)=TbStat[k].ArtRec;fasgeti(6);
		WriteFld2Xls(XlsRij,XlsKol++,6,3,0);
	} 
	XlsRij++;XlsKol=1;
#endif
#if !FLAGRUB
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"NR",0);
#endif
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"KlantNr",0);
#if !FLAGRUB
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"BTW-nummer",0);
#endif
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Naam",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Straat",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"PostCode",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Plaats",0);
#if FLAGRUB
	XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Emailadres",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Vertegenwoordiger",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Code",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omschrijving",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Aantal",0);
  XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Omzet",0);
#else
  for(k=0;k<MaxStat;k++){
		fasinit(6);*u(6,1)=TbStat[k].ArtRec;fasgeti(6);
		WriteFld2Xls(XlsRij,XlsKol++,6,31,0);
	} 
	XlsRij++;XlsKol=1;
#endif
	XlsRij++;XlsKol=1;

  scrget(1,170);
  fasinit(2);knr_=1;
  FOREVER{
    next_klt:;
    if(faskeyi(2,2,2)) break;
		if(InqKlt && *u(2,1)!=InqKlt) goto next_klt;
		if(FindTextInString(&sel_verpl,1,s(2,80),fldlen(2,80))==NO) goto next_klt;
//    if(sel_verpl && sel_verpl!=*s(2,80)) goto next_klt;
		if(SelSoortKlant[0] && cmpstr(SelSoortKlant,s(2,54),fldlen(2,54))) goto next_klt;
		if(SelTypeKlant && SelTypeKlant!=*s(2,26)) goto next_klt;
    scrfld(5,2,3);scrupd(-3,0);
    for(k=0;k<MaxStat;k++) TbStat[k].KltAantal=0;used_=NO;aantal_=0;bedrag_=0;

    fasinit(16);*l(16,10)=*pu_2_1; mode_=1;last_art=0xFFFF;
    FOREVER{
      next:;
      if(faskeyi(16,2,mode_)) break; mode_=2;
      if(*l(16,10)!=*pu_2_1) break;
      for(k=0;k<MaxStat;k++) if(*l(16,20)==TbStat[k].ArtRec) break;
      if(k>=MaxStat) {*l(16,20)+=1;*u(16,3)=0;mode_=1;goto next;}
      if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode_=1; goto next;}
      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode_=2;goto next;}
#if FLAGRUB
			if(last_art!=*l(16,20)){
				if(used_){
					fasinit(6); *u(6,1)=last_art;fasgeti(6);
					XlsKol=1;
					WriteFld2Xls(XlsRij,XlsKol++,2,1+klcd,0);// CustID
					WriteFld2Xls(XlsRij,XlsKol++,2,3,0); // Name
					WriteFld2Xls(XlsRij,XlsKol++,2,4,0); //Street_NR
					zero(buf_,sizeof buf_);j=0;
					for(k=0;k<fldlen(2,5);k++){
						if(*(s(2,5)+k)=='\0') break;
						if(*(s(2,5)+k)>='0' && *(s(2,5)+k)<='9') buf_[j++]=*(s(2,5)+k);
					}
  				XlsWrite(XlsRef,XlsRij,XlsKol++,0,buf_,0); // PostCode (enkel cijfers!)
					WriteFld2Xls(XlsRij,XlsKol++,2,6,0); // City
					WriteFld2Xls(XlsRij,XlsKol++,2,21,0); // emailadres
					WriteFld2Xls(XlsRij,XlsKol++,2,28,0); // vertegenwoordiger
				  WriteFld2Xls(XlsRij,XlsKol++,6,2,0); // Name
					WriteFld2Xls(XlsRij,XlsKol++,6,3,0); //Street_NR
					*d(16,30)=aantal_;*d(16,31)=bedrag_;
					XlsWrite(XlsRef,XlsRij,XlsKol++,2,&aantal_,0);
					XlsWrite(XlsRef,XlsRij,XlsKol++,2,&bedrag_,0);
		/*			WriteFld2Xls(XlsRij,XlsKol++,16,30,0); 
					WriteFld2Xls(XlsRij,XlsKol++,16,31,0); */
					XlsRij++;
					fasgeti(16);
				}
				aantal_=0;bedrag_=0;used_=0;
				fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
			}
#endif
			last_art=*l(16,20);
			aantal_+=*d(16,30); bedrag_+=*d(16,31);
      TbStat[k].KltAantal+=*d(16,30);
      used_=YES;
    }
    if(used_){
		  copy(s(2,1),buf1000_,fldlen(2,0));
#if FLAGRUB

			fasinit(6); *u(6,1)=last_art;fasgeti(6);

			XlsKol=1;
			WriteFld2Xls(XlsRij,XlsKol++,2,1+klcd,0);// CustID
			WriteFld2Xls(XlsRij,XlsKol++,2,3,0); // Name
			WriteFld2Xls(XlsRij,XlsKol++,2,4,0); //Street_NR
			zero(buf_,sizeof buf_);j=0;
			for(k=0;k<fldlen(2,5);k++){
				if(*(s(2,5)+k)=='\0') break;
				if(*(s(2,5)+k)>='0' && *(s(2,5)+k)<='9') buf_[j++]=*(s(2,5)+k);
			}
  		XlsWrite(XlsRef,XlsRij,XlsKol++,0,buf_,0); // PostCode (enkel cijfers!)
			WriteFld2Xls(XlsRij,XlsKol++,2,6,0); // City
			WriteFld2Xls(XlsRij,XlsKol++,2,21,0); // emailadres
			WriteFld2Xls(XlsRij,XlsKol++,2,28,0); // vertegenwoordiger
			WriteFld2Xls(XlsRij,XlsKol++,6,2,0); // Name
			WriteFld2Xls(XlsRij,XlsKol++,6,3,0); //Street_NR
			*d(16,30)=aantal_;*d(16,31)=bedrag_;
			XlsWrite(XlsRef,XlsRij,XlsKol++,2,&aantal_,0);
			XlsWrite(XlsRef,XlsRij,XlsKol++,2,&bedrag_,0);
	/*		WriteFld2Xls(XlsRij,XlsKol++,16,30,0); 
			WriteFld2Xls(XlsRij,XlsKol++,16,31,0); */
			XlsRij++;
#else
      for(k=0;k<4;k++){// afwijkend leveradres uitschrijven
				if(fldlen(2,143+k) && *s(2,143+k)) copy(s(2,143+k),s(2,3+k),fldlen(2,3+k));
			}
      lbd_=knr_++;XlsWrite(XlsRef,XlsRij,XlsKol++,1,&lbd_,0); // CustNR 
      WriteFld2Xls(XlsRij,XlsKol++,2,1+klcd,0);// CustID

      lbd_=*l(2,10)&0xBFFFFFFF;/* BTW-nummer */
      zero(buf_,sizeof buf_);
      if(lbd_==000000000) XlsWrite(XlsRef,XlsRij,XlsKol++,0,"",0); // VAT
      else{
				copy("BE-",buf_,3);
				btw_deco(&buf_[3],(long *)&lbd_,1);
				//stcli_d(&buf_[20],lbd_,9,0);
				//copy("BE-0",buf_,4);
				//copy(&buf_[20],&buf_[4],3);buf_[7]='.';
				//copy(&buf_[23],&buf_[8],3);buf_[11]='.';
				//copy(&buf_[26],&buf_[12],3);
				XlsWrite(XlsRef,XlsRij,XlsKol++,0,buf_,0); // VAT
      }
      WriteFld2Xls(XlsRij,XlsKol++,2,3,0); // Name
			WriteFld2Xls(XlsRij,XlsKol++,2,4,0); //Street_NR
			zero(buf_,sizeof buf_);j=0;
			for(k=0;k<fldlen(2,5);k++){
				if(*(s(2,5)+k)=='\0') break;
				if(*(s(2,5)+k)>='0' && *(s(2,5)+k)<='9') buf_[j++]=*(s(2,5)+k);
			}
  		XlsWrite(XlsRef,XlsRij,XlsKol++,0,buf_,0); // PostCode (enkel cijfers!)
			WriteFld2Xls(XlsRij,XlsKol++,2,6,0); // City
			for(k=0;k<MaxStat;k++){lbd_=TbStat[k].KltAantal;XlsWrite(XlsRef,XlsRij,XlsKol++,1,&lbd_,0);} 
			XlsRij++;XlsKol=1;
#endif
			copy(buf1000_,s(2,1),fldlen(2,0));
    }
  }
  endsr:;
  XlsClose(XlsRef,1);// fasclos(-2);
}
 
static copy0(ps,pd,len_)
char *ps,*pd;
int16 len_;
{
  int16 fuval=0;
				
  while(*ps){
    *pd++=*ps++;
    fuval++;
    if(fuval>=len_) break;
  }
  *pd='\0';
  return fuval;
}

static print()
{
  int16 z;

  prtclose();
  getsysprNew(5,form_dat,&prmode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,prmode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1);prttext("<t40b>");prttext("Historieken");prttext("<b> ");
  prtifld(fm_udat,&dat_beg,-1);prttext(" t.e.m. ");prtifld(fm_udat,&dat_end,-1);
  prttext("<t90>");prtfld(25,2,-1);
  prttext("<t120>Blz.<ppp>.");
  prtbuf(1);z=1;
/*  prttab(z,16,1,1,-1); prttitle(z++,"Recnr",0x13); */
  prttab(z,16,2,1,-1);
	if(AK_mode) prttitle(z++,"Bonnr",0x13); else prttitle(z++,"Ft.nr",0x13);
  prttab(z,16,3,1,-1); prttitle(z++,"Datum",0x13);
  prttab(z,mast_stu,3,1,30);
  if(mast_stu==1) prttitle(z++,"Leverancier",3);else prttitle(z++,"Klant",3);
  fmt_get(16,21); prtitab(z,fmt,CodeString,1,-1); prttitle(z++,"Code",3);
  prttab(z,16,22,1,-1); prttitle(z++,"Artikel",3);
  prttab(z,16,30,1,-1); prttitle(z++,"Aantal",0x13);
#if FLAGGOU
  prttab(z,16,29,1,-1); prttitle(z++,"Gewicht",0x13);
#endif
  prttab(z,16,31,1,-1); prttitle(z++,"Bedrag",0x13);
  prtbuf(3);
	p_pdfname("Historieken",dat_beg,dat_end);
  free=999;
  fasinit(16);*l(16,mast_pos)=inq_mast; *l(16,20)=inq_art; *l(16,2)=ftnr_beg;
  totaalbd=0; totaalst=0;
  FOREVER{
    if(add_line(0,NO)==NO) break;
  }
  fasinit(16); zero(CodeString,sizeof CodeString);
	copy("Totaal ==>",s(16,22),15);*d(16,31)=totaalbd;
#if FLAGGOU
	*d(16,29)=totaalst;
#else
	*d(16,30)=totaalst;
#endif
  nextline(); for(z=0;z<20;z++) prtinfo(z,2); nextline();
  prtform(0);
  prtclose();
  endsr:;
}
 
static print_ftlist()
{
  int16 z,first_;
	double bd_goed_,bd_leegg_;
	long last_klt_,last_ft_;
	uint16 used_,last_dt_,mode_;
  
	mast_stu=2;
	if(ask_sel("Historiek per factuur",2)) goto endsr;
	prtclose();prt2pdf=YES;
  getsysprNew(5,form_dat,&prmode,&prtnr);if(prt2pdf) PrintPaperNr=0;
  if((errnum=prtopen(prtnr,form_dat,6,132,prmode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1);prttext("<t40b>");prttext("Historiek per factuur");prttext("<b> ");
  prtifld(fm_udat,&dat_beg,-1);prttext(" t.e.m. ");prtifld(fm_udat,&dat_end,-1);
  prttext("<t90>");prtfld(25,2,-1);
  prttext("<t120>Blz.<ppp>.");
  prtbuf(1);z=1;
/*  prttab(z,16,1,1,-1); prttitle(z++,"Recnr",0x13); */
  prtitab(z,fm_u_ftnr,&last_ft_,1,-1);prttitle(z++,"FactNr",0x13);
  prtitab(z,fm_udat,&last_dt_,1,-1); prttitle(z++,"Datum",0x13);
  prttab(z,mast_stu,3,1,30);
  if(mast_stu==1) prttitle(z++,"Leverancier",3);else prttitle(z++,"Klant",3);
  prtitab(z,fm_ud7_2,&bd_goed_,1,-1); prttitle(z++,"Goederen",0x13);
	prtitab(z,fm_ud7_2,&bd_leegg_,1,-1); prttitle(z++,"Leegggoed",0x13);
  prtbuf(3);
	p_pdfname("Historiek per factuur",dat_beg,dat_end);
  free=999;
  fasinit(16);*l(16,mast_pos)=inq_mast; *l(16,20)=inq_art; *l(16,2)=ftnr_beg;*u(16,3)=dat_beg;
	last_klt_=0;last_ft_=0;last_dt_=0;used_=NO;bd_goed_=0;bd_leegg_=0;
  totaalbd=0; totaalst=0;  mode_=1;
  FOREVER{
		next:;
		if(faskeyi(16,3,mode_)) break; mode_=2;
    if(ftnr_beg && *l(16,2)<ftnr_beg) goto next;
		if(ftnr_end && *l(16,2)>ftnr_end) break;
    if(dat_beg && *pu_16_3<dat_beg) {*pu_16_3=dat_beg; mode_=1; goto next;} 
    if(dat_end && *pu_16_3>dat_end) {*pu_16_3=0xFFFF; goto next;}
		if(*l(16,15)) goto next; // geen leveranciers
		if(inq_art && *l(16,20)!=inq_art) goto next;
		if(inq_klt && *l(16,mast_pos)!=inq_klt) goto next;
		if(last_klt_!=*l(16,10) || last_ft_!=*l(16,2) || last_dt_!=*u(16,3)){
			if(used_){
				for(z=0;z<20;z++) prtinfo(z,0); 
				nextline();
			}
			last_klt_=0;last_ft_=0;last_dt_=0;used_=NO;bd_goed_=0;bd_leegg_=0;
			fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
			last_klt_=*l(16,10); last_ft_=*l(16,2); last_dt_=*u(16,3);used_=YES;
		}
		if(*l(16,23)==99) bd_leegg_+=*d(16,31); else bd_goed_+=*d(16,31);
  }
	if(used_){
	  for(z=0;z<20;z++) prtinfo(z,0); 
		nextline();
	}
  prtform(0);
  prtclose();
  endsr:;
}



static add_line(line,dsp_flag)
int16 line;
flag dsp_flag;
{
  int16 k,end_=NO;

  FOREVER{
    next:;
    if(faskeyi(16,fkey,2)) end_=YES;
    if(end_) return NO;
    if(inq_mast && *l(16,mast_pos)!=inq_mast) return NO;
    if(inq_art && *l(16,20)!=inq_art) {
      if(fkey!=11) return NO;
      goto next;
    }
#if FLAGMAE
		if(callparmval==2 && *u(8,31) && *u(16,9) && *u(16,9)!=*u(8,31)) goto next; // historiek vanuit 240, op plaatniveau
#endif
    if(mast_pos==10){
			if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
			if(inq_mast==0 && sel_soortklant[0]){
				fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
				if(cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) goto next;
			}
			if(inq_lev || inq_merk){
				fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
				if(inq_lev && *u(6,7)!=inq_lev) goto next;
				if(inq_merk && *u(6,101)!=inq_merk){ goto next;}
			}
		}
    if(mast_pos==15 && *l(16,10)) goto next;/* geen klanten  */
    if(inq_art==0 && ftnr_beg==0 && skip_leegg=='J' && *l(16,23)==99) {
      goto next;
    }
    if(inq_grp && *l(16,23)!=inq_grp){goto next;}
		for(k=0;k<5;k++) if(skip_groepen[k] && skip_groepen[k]==*l(16,23)) goto next;
		if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
    if(skip_leegg=='J' && *l(16,23)==99){goto next;}
    if(ftnr_beg && *l(16,2)<ftnr_beg) goto next;
		if(ftnr_end && *l(16,2)>ftnr_end){if(fkey==3) return NO; else goto next;}
    if(dat_beg && *pu_16_3<dat_beg){*pu_16_3=dat_beg; goto next;}
    if(dat_end && *pu_16_3>dat_end){*pu_16_3=0xFFFF; goto next;}
		if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
		if(AK_mode && fldlen(16,8) && inq_loc && inq_loc!=*u(16,8)) goto next;
    break;
  }
  totaalbd+=*d(16,31);
#if FLAGGOU
	totaalst+=*d(16,29); // gewicht
#else
	totaalst+=*d(16,30);
#endif
	fasinit(mast_stu);*u(mast_stu,1)=*l(16,mast_pos);
	if(mast_stu==1 && mast_pos==15 && *u(1,1)>=30000){
  	if(*u(1,1)==30000) copy("Mutatie filiaal DEPOT",s(1,3),20);
		else sprintf_s(s(1,3),20,"Mutatie filiaal %d",*u(1,1)-30000);
	}	
	else if(*u(mast_stu,1)) fasgeti(mast_stu);
  if(dsp_flag){
    if(fkey==3) copy(s(16,12),s(mast_stu,3),fldlen(mast_stu,3));
    scrfld(5+line*5,16,2);
    scrfld(6+line*5,16,3);scraddpicto(line+5,0,20,4+line,1,1,112,0,6,"Detail");
    if(fkey==1 || fkey==5) {
      scrofld(7+line*5,mast_stu,3,30);
    }
    else scrofld(7+line*5,16,22,30);
#if FLAGGOU
    scrfld(8+line*5,16,29); // gewicht 
#else
    scrfld(8+line*5,16,30);
#endif
		if(DisplayEhPrijs){
#if FLAGGOU
			if(*d(16,29)) *d(16,31)=Round((double)(*d(16,31)/ *d(16,29)),(double)(0.001));
#else
			if(*d(16,30)) *d(16,31)=Round((double)(*d(16,31)/ *d(16,30)),(double)(0.001));
#endif
			scrifld(9+line*5,fm_prijs,d(16,31));
		}
		else scrfld(9+line*5,16,31);
		TbScreenRecs[line]=*l(16,1);
  }
  else{
#if FLAGCOC
		fasinit(6); *u(6,1)=*l(16,20); if(*u(6,1)) fasgeti(6);
		if(*s(6,8) && *s(16,22)!='*') copy(s(6,8),CodeString,fldlen(6,8));
		else copy(s(16,21),CodeString,fldlen(16,21));
#else
		copy(s(16,21),CodeString,fldlen(16,21));
#endif
    for(k=0;k<20;k++) prtinfo(k,0);
    nextline();
  }
  tbs[p_scr+1].rec16=*l(16,1);
  tbs[p_scr+1].totaalbd=totaalbd;
  tbs[p_scr+1].totaalst=totaalst;
  return YES;
}


static ask_sel(ptitel,sel_mode_)/* 0=klt/art/ft 1=klt/art 2=geen */
char *ptitel;
int16 sel_mode_;
{
  int16 key,k,z,curs=1,dsp_warning_=NO;
  char nm_lev[50],nm_merk[50];

  if(cmpstr(ptitel,"Schrap",6)==0) dsp_warning_=YES;
	if(skip_leegg=='\0') skip_leegg='J';
	if(skip_gratis_art=='\0') skip_gratis_art='N';
	if(HerberekenSemKorting=='\0') HerberekenSemKorting='N';
	if(fldlen(6,41)==0) skip_leegg='N';
  fasinit(1); if(inq_lev){*u(1,1)=inq_lev;fasgeti(1);} copy(s(1,3),nm_lev,fldlen(1,3));
  fasinit(2); if(inq_klt){*u(2,1)=inq_klt;fasgeti(2);}
  fasinit(6); if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
  fasinit(1); if(inq_merk){*u(1,1)=inq_merk;fasgeti(1);} copy(s(1,3),nm_merk,fldlen(1,3)); 
	if(SkipKassaFt=='\0') SkipKassaFt='N';

  FOREVER{
    redo:;
    scrget(2,314);z=1;
		DisplayMenuTitel(0,ptitel,0x3);z++;
		if(dsp_warning_) scraddpicto(32,0,65,0,12,6,605,0,0,"Opgelet!"); 
    scrifld(z++,fm_udat,&dat_beg);
    scrifld(z++,fm_udat,&dat_end);
    scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrfld(z++,6,3);scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    fmt_get(1,3);scrifld(z++,fmt,nm_lev);scraddpicto(3,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    if(fldlen(6,101)){
      fmt_get(1,3);scrifld(z++,fmt,nm_merk);scraddpicto(4,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    } else scrifld(z++,fm_os1,"-");
		scrifld(z++,fm_uu2,&inq_grp);scraddpicto(5,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		if(fldlen(2,54)){fmt_get(2,54);scrifld(z++,fmt,sel_soortklant);} else z++;

    scrifld(z++,fm_u_ftnr,&ftnr_beg);scrifld(z++,fm_u_ftnr,&ftnr_end);
		for(k=0;k<5;k++) scrifld(z++,fm_uu2,&skip_groepen[k]);
		scrifld(z++,fm_uJN,&skip_gratis_art);
    if(fldlen(6,41)) scrifld(z++,fm_uJN,&skip_leegg); else scrifld(z++,fm_os1,"-");
		if(fldlen(16,39)) scrifld(z++,fm_uJN,&SkipKassaFt); else scrifld(z++,fm_os1,"-");
#if !FLAGLEA
		scrifld(z++,fm_uJN,&HerberekenSemKorting);
#endif
		key=scrupd(curs,0x81);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		switch(key){
				case 5001 : if(search(2,98)) {curs=4;goto redo;} break;
				case 5002 : if(search(6,98)) {curs=5;goto redo;} break;
				case 5003 : copy(nm_lev,s(1,3),fldlen(1,3));
					          if(search(1,98)){curs=6; goto redo;} 
										else copy(s(1,3),nm_lev,fldlen(1,3));
										break;
				case 5004 : copy(nm_merk,s(1,3),fldlen(1,3));
					          if(search(1,98)){curs=7; goto redo;} 
										else copy(s(1,3),nm_merk,fldlen(1,3));
										break;
				case 5005 : if(search(52,98)){curs=8; goto redo;} 
										else inq_grp=*u(52,1);
										break;
				default : break;
		}

    if(key==101) return YES;
    if(dat_beg==0) {errnum=34;curs=2;goto redo;}
    if(dat_end<dat_beg) {curs=3;errnum=34;goto redo;}
    if(*s(2,3)){
      if(search(2,0)){curs=4;goto redo;}
    } else fasinit(2);
    inq_klt=*u(2,1);
    if(*s(6,3)){
      if(search(6,0)){curs=5;goto redo;}
    } else fasinit(6);
    inq_art=*u(6,1);
		if(nm_lev[0]){
      fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=6;goto redo;}
	    copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
    } else inq_lev=0;
	  if(nm_merk[0]){
      fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=7;goto redo;}
	    copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
    } else inq_merk=0;

    if(sel_mode_==YES && inq_klt==0 && inq_art==0) {errnum=34;curs=4;goto redo;}
#if FLAGSTB
    if(sel_mode_==2 && inq_klt==0 && inq_art==0) {errnum=34;curs=4;goto redo;}
#endif
    if(sel_mode_==NO && inq_klt==0 && inq_art==0 && ftnr_beg==0) {errnum=34;curs=4;goto redo;}
    if(key!=108) goto redo;
    break;
  }
  AK_mode=NO;
  if(AK_mode){inq_mast=inq_lev;mast_stu=1;mast_pos=15;}
  else {inq_mast=inq_klt;mast_stu=2;mast_pos=10;}
  endsr:;
  return NO;
}
 
static ask_AKsel(ptitel,sel_mode_)/* AANKOOP     0=lev/art/ft 1=lev/art 2=geen */
char *ptitel;
int16 sel_mode_;
{
  int16 key,z,curs=1;
	char nm_lev[50],nm_merk[50];
 
  if(skip_leegg=='\0') skip_leegg='J';
  fasinit(1); if(inq_lev){*u(1,1)=inq_lev;fasgeti(1);} copy(s(1,3),nm_lev,fldlen(1,3));
  fasinit(6); if(inq_art){*u(6,1)=inq_art;fasgeti(6);}
  fasinit(1); if(inq_merk){*u(1,1)=inq_merk;fasgeti(1);} copy(s(1,3),nm_merk,fldlen(1,3)); 
 
  FOREVER{
    redo:;
    scrget(2,321);z=1;
		DisplayMenuTitel(1,ptitel,0x3);z++;
   
    scrifld(z++,fm_udat,&dat_beg);
    scrifld(z++,fm_udat,&dat_end);
 		fmt_get(1,3);scrifld(z++,fmt,nm_lev);scraddpicto(3,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrfld(z++,6,3);scraddpicto(2,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		if(fldlen(6,101)){
      fmt_get(1,3);scrifld(z++,fmt,nm_merk);scraddpicto(3,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    } else z++;
    scrifld(z++,fm_uu2,&inq_grp);
    scrifld(z++,fm_u_ftnr,&ftnr_beg);scrifld(z++,fm_u_ftnr,&ftnr_end);
    scrifld(z++,fm_uJN,&skip_leegg);
    key=scrupd(curs,0x81);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		switch(key){
			case 5001 : copy(nm_lev,s(1,3),fldlen(1,3));
				          if(search(1,98)){curs=4; goto redo;} 
									else copy(s(1,3),nm_lev,fldlen(1,3));
									break;
			case 5002 : if(search(6,98)) {curs=5;goto redo;} break;
			case 5003 : copy(nm_merk,s(1,3),fldlen(1,3));
				          if(search(1,98)){curs=6; goto redo;} 
									else copy(s(1,3),nm_merk,fldlen(1,3));
									break;
			default : break;
		}

    if(key==101) return YES;
    if(dat_beg==0) {errnum=34;curs=2;goto redo;}
    if(dat_end<dat_beg) {curs=3;errnum=34;goto redo;}
		if(nm_lev[0]){
      fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=4;goto redo;}
	    copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
    } else inq_lev=0;
    if(*s(6,3)){
      if(search(6,0)){curs=5;goto redo;}
    } else fasinit(6);
    inq_art=*u(6,1);
		if(nm_merk[0]){
      fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=6;goto redo;}
	    copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
    } else inq_merk=0;
    if(sel_mode_==YES && inq_lev==0 && inq_art==0) {errnum=34;curs=4;goto redo;}
    if(sel_mode_==NO && inq_lev==0 && inq_art==0 && ftnr_beg==0) {errnum=34;curs=4;goto redo;}
    if(key!=108) goto redo;
    break;
  }
  endsr:;
  AK_mode=YES;
  if(AK_mode){inq_mast=inq_lev;mast_stu=1;mast_pos=15;}
  else {inq_mast=inq_klt;mast_stu=2;mast_pos=10;}
  return NO;
}


static VernieuwHistoriek()
{
  int16 g;
  long n=0;
 
  if(DisplayWarning("Wenst U echt de groepen + art.nrs van de historieken te vernieuwen?",61)==NO) goto endsr;
  rec_working=0;kdsp=0;kdsp_off=1;
  zero(disp_str,sizeof disp_str);
  scrget(1,170); scrifld(10,fm_os63,"Bezig met vernieuwen ....");scrupd(-3,0);
	fasunlck(-2);
  fasinit(16);
  FOREVER{
    next:;
    *l(16,1)=++n;
		g=fasgeti(16); if((n%500)==0) {scrifld(15,fm_ul7,&n);scrupd(-3,0);}
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
      fasinit(6);*u(6,1)=*l(16,20); if(fasgeti(6)) goto next;
			copy(s(6,2),s(16,21),fldlen(16,21));
			*l(16,23)=*u(6,9);
			if(fldlen(6,103) && fldlen(16,28)) *u(16,28)=*u(6,103); // subgroep
			fasupd(16);
		}
  }
	fasunlck(-1);
  endsr:;
}


static wis_his()
{
  int16 g,k,art_selectie_;
	char kar_='\0';
  long n=0,qkilled_;
 
	
	skip_leegg='N';
  if(ask_sel("Schrappen verouderde historieken",2)) goto endsr;
  if(DisplayWarning("Wenst U echt de geselecteerde historieken te schrappen???",61)==NO) goto endsr;
  if(AK_mode){inq_mast=inq_lev;mast_stu=1;mast_pos=15;}
  else {inq_mast=inq_klt;mast_stu=2;mast_pos=10;}
  rec_working=0;kdsp=0;kdsp_off=1;
  zero(disp_str,sizeof disp_str);
  scrget(1,170); scrifld(10,fm_os63,"Bezig met wissen ....");scrupd(-3,0);
	art_selectie_=NO;
	if(skip_leegg=='J' || inq_lev || inq_merk || inq_grp) art_selectie_=YES;
	for(k=0;k<5;k++) if(skip_groepen[k]){art_selectie_=YES;break;}

	fasunlck(-2);
  fasinit(16);n=0;qkilled_=0;
  FOREVER{
    next:;
    *l(16,1)=++n;
    g=fasgeti(16); dsp_working();
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
			if((n%1000)==0){
				if(kar_==0) kar_='*'; else kar_=0;
				scrifld(22,fm_os1,&kar_);
				scrifld(23,fm_ul7,&qkilled_);
				scrupd(-3,0);
			}
/*  if(faskeyi(16,1,2)) break; */
      if(inq_mast && *l(16,mast_pos)!=inq_mast) goto next;
      if(inq_art && *l(16,20)!=inq_art) goto next;

      if(ftnr_beg && *l(16,2)<ftnr_beg) goto next;
			if(ftnr_end && *l(16,2)>ftnr_end) goto next;
      if(dat_beg && *pu_16_3<dat_beg) goto next;
      if(dat_end && *pu_16_3>dat_end) goto next;
      if(art_selectie_){
        fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
        if(mast_pos!=15 && inq_lev && *u(6,7)!=inq_lev) goto next;
			  if(mast_pos!=15 && inq_merk && *u(6,101)!=inq_merk){ goto next;}
        if(inq_grp && *i(6,9)!=inq_grp) goto next;
			  for(k=0;k<5;k++) if(skip_groepen[k] && skip_groepen[k]==*i(6,9)) goto next;
        if(skip_leegg=='J' && *i(6,9)==99){goto next;}
				if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
			}
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;

      faskill(16);qkilled_++;
    }
  }
	fasunlck(-1);
  endsr:;
}

static DisplayWarning(ptxt, icoon)
char *ptxt;
int icoon;
{
  int16 key,color_;

	color_=0; if(icoon<500) color_=3;
  scrget(1,169);
	if(icoon) scraddpicto(1,0,32,1,12,6,icoon,0,color_,"Opgelet!"); 
  scrifld(12,fm_os63,ptxt);
redo_upd:;
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  else if(key==105) return NO;
	else goto redo_upd;
}



static DisplayMenuTitel(ypos_,tekst_,attrib_)
int ypos_;
char *tekst_,attrib_;
{
  int len_,beg_;
	char fmt_[40],dsptekst_[100];
   
	zero(dsptekst_,sizeof dsptekst_);dsptekst_[0]=' ';
  for(len_=0;len_<80;len_++){
		if(tekst_[len_]=='\0') break;
		dsptekst_[len_+1]=tekst_[len_];
	}
	len_+=1;dsptekst_[len_++]=' ';if(len_>80) len_=80;
  beg_=(80-len_)/2; if(beg_<1) beg_=1; 
	copy(fm_titel,fmt_,sizeof fm_titel);fmt_[2]=len_;
	scraddfield(200,beg_,ypos_,attrib_);scrifld(200,fmt_,dsptekst_);
}

static calc_sta()
{
  int16 n,k,mode=1,len_,sta_key;
  char last_code[20],str_[50];
  long last_art=0xFFFF,last_klt=0xFFFF;
  double bd_,bd_semkorting_,bd_tussenkomst_;
  flag end=NO,used=NO;
  uint16 last_grp=0xFFFF,bits;

  zero(str_,sizeof str_);
  k=date2str(str_,dat_beg,0);
  str_[k++]='-';date2str(&str_[k],dat_end,0);
						
  k=copy_0("Omzet ",sta_hoofd,6);
  k+=copy_0(str_,&sta_hoofd[k],25);
  if(AK_mode==NO && inq_lev && k<40){
		fasinit(1);*u(1,1)=inq_lev;fasgeti(1);
    copy(" (",&sta_hoofd[k],2);k+=2;
    k+=copy_0(s(1,3),&sta_hoofd[k],7);
    sta_hoofd[k]=')';
  }
									
  if(open_sta_file()==NO) return NO;
  scrget(1,170);scrifld(5,fm_odsp,"Berekenen statistiek");
  fasunlck(-2);
  fasinit(16); last_code[0]=0xFF;
  *l(16,mast_pos)=inq_mast;*l(16,20)=inq_art;mode=1;
  if(inq_mast) sta_key=11; else sta_key=1;
  FOREVER{
    next:;
    if(faskeyi(16,sta_key,mode)) end=YES; mode=2;
    dsp_working();
    if(inq_mast && *l(16,mast_pos)!=inq_mast) end=YES;
    if(!end && inq_art && *l(16,20)!=inq_art) {
      if(inq_mast) goto next; else end=YES;
    }
    if(!end){
      if(ftnr_beg && *l(16,2)<ftnr_beg) goto next;
			if(ftnr_end && *l(16,2)>ftnr_end) goto next;
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
			for(k=0;k<5;k++) if(skip_groepen[k] && skip_groepen[k]==*l(16,23)) goto next;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
      if(skip_leegg=='J' && *l(16,23)==99){goto next;}
      if(mast_pos==10){
				if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
				if(inq_mast==0 && sel_soortklant[0]){
					fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
					if(sel_soortklant[0] && cmpstr(s(2,54),sel_soortklant,fldlen(2,54))) goto next;
				}
			}
      if(mast_pos==15 && *l(16,10)) goto next;/* geen klanten  */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(mast_pos!=15 && inq_lev && *u(6,7)!=inq_lev){ goto next;}
			if(mast_pos!=15 && inq_merk && *u(6,101)!=inq_merk){ goto next;}
      if(*pu_16_3 <dat_beg) {*pu_16_3=dat_beg;mode=1; goto next;}
      if(*pu_16_3 >dat_end) {*pu_16_3=0xFFFF; mode=2;goto next;}
			if(inq_mast && mast_pos==10){
        if(DirCall_DRK2215_SelectArtikel()==NO) goto next;
			}
    }
    if(end && used==NO) break;
    if(inq_mast){/* groep -> artikel -> factuur */
      bits=0;
      if(end) bits|=0x0F;
      if(cmpstr(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
      if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;

      if(bits & 0x04){
				fasinit(6);*u(6,1)=last_art;fasgeti(6);
#if FLAGCOC
				k=2; if(*s(6,8)) k=8;
				for(len_=0;len_<fldlen(6,k);len_++) if(*(s(6,k)+len_)=='\0') break;
				copy(s(6,k),get_p(5,0),len_);copy(" ",get_p(5,0)+len_,1);
#else
				for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
				copy(s(6,2),get_p(5,0),len_);copy(" ",get_p(5,0)+len_,1);
#endif
				copy(s(6,3),get_p(5,0)+len_+1,30-(len_+1));
				add_rec(5);
      }
      if(bits & 0x02){
				fasinit(52);*u(52,1)=last_grp;fasgeti(52);
				stcli_d(get_p(6,0),(long)last_grp,2,0);copy(" ",get_p(6,0)+2,1);
				copy(s(52,14),get_p(6,0)+3,15);
				add_rec(6);
      }
    }
    else{/* klant -> factuur */
      bits=0;
      if(end) bits|=0x0F;
      if(*l(16,mast_pos)!=last_klt && last_klt!=0xFFFF) bits|=0x0E;
      if(bits & 0x02){
				fasinit(mast_stu);*u(mast_stu,1)=last_klt;
				if(mast_stu==1 && *u(1,1)>=30000){
  				if(*u(1,1)==30000) copy("Mutatie filiaal DEPOT",s(1,3),20);
					else sprintf_s(s(1,3),20,"Mutatie filiaal %d",*u(1,1)-30000);
				}	
				else fasgeti(mast_stu);
				copy(s(mast_stu,3),get_p(6,0),30);
				add_rec(6);
      }
    }
    last_grp=*l(16,23);last_klt=*l(16,mast_pos);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    if(end) break;
		fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
		if(AK_mode==NO && HerberekenSemKorting=='J') CalcSemKorting();
    for(k=4;k<8;k++){
#if NO_DRANK_STATISTIEK// VOO zonder DRK gedoe 
#if FLAGGOU
      *(double *)get_p(k,1)+=*d(16,29);/* gewicht */
#else
      *(double *)get_p(k,1)+=*d(16,30);/* stuks */
#endif
      bd_=*d(16,31)+*d(16,33);
      *(double *)get_p(k,2)+=bd_;/* bruto-omzet */
      *(double *)get_p(k,3)+=*d(16,33);/* factuur-korting */
      *(double *)get_p(k,4)+=*d(16,31); /* netto VW GEEN BRIJ tussenkomst en sem.korting */
      *(double *)get_p(k,5)+=*d(16,32);/* AK-waarde */
      bd_=*(double *)get_p(k,4)-*(double *)get_p(k,5);
      *(double *)get_p(k,6)=bd_;/* NETTO winst */
      if(*(double *)get_p(k,5)){/* NETTO winst % */
	      *(double *)get_p(k,7)=(bd_/ *(double *)get_p(k,5))*100;
      } else *(double *)get_p(k,7)=0;
#else
			*(double *)get_p(k,1)+=*d(16,30);/* stuks */
#if FLAGSAP
      *(double *)get_p(k,2)+=*d(16,30)* *f(6,38);/* GEWICHT */
#else
      *(double *)get_p(k,2)+=*d(16,30)* *f(6,37);/* LITERS */
#endif
      bd_=*d(16,31);
      *(double *)get_p(k,3)+=bd_;/* factuurbedrag */
      if(bd_) *(double *)get_p(k,4)+=bd_-(*d(16,30)* *f(16,27));/* excl.acc */
      bd_=*d(16,31)+*d(16,33);
      *(double *)get_p(k,5)+=bd_;/* bruto-omzet */
      if(bd_) *(double *)get_p(k,6)+=bd_-(*d(16,30)* *f(16,27));/* excl.acc */
      *(double *)get_p(k,7)+=*d(16,33);/* factuur-korting */
	 		if(AK_mode==NO && HerberekenSemKorting=='J'){
				 if(*d(16,31)==0) {hl_semkort=0.,calc_sem=0.,brij_tpct=0.,brij_tbd=0.;}
				 bd_semkorting_=(*d(16,31)-(*d(16,30)* *f(16,27))) * calc_sem/100.;  // netto ex acc en dan korting
				 bd_semkorting_+=*d(16,30)*hl_semkort;
				 bd_tussenkomst_=(bd_-(*d(16,30)* *f(16,27))) * brij_tpct/100.; // bruto ex acc en dan korting 
				 bd_tussenkomst_+=*d(16,30)*brij_tbd;
			}
			else {
				bd_semkorting_=*d(16,34);bd_tussenkomst_=*d(16,35);
			}
      *(double *)get_p(k,8)+=bd_semkorting_;/* sem.korting */
      *(double *)get_p(k,9)+=bd_tussenkomst_;/* tussenkomst brouwerij  */
      *(double *)get_p(k,10)+=*d(16,31)-bd_semkorting_+bd_tussenkomst_;/* netto VW */
      *(double *)get_p(k,11)+=*d(16,32);/* AK-waarde */
      bd_=*(double *)get_p(k,10)-*(double *)get_p(k,11);
      *(double *)get_p(k,12)=bd_;/* NETTO winst */
      if(*(double *)get_p(k,11)){/* NETTO winst % */
	      *(double *)get_p(k,13)=(bd_/ *(double *)get_p(k,11))*100;
      } else *(double *)get_p(k,13)=0;
#endif
    }
    if(inq_mast) n=4; else n=5;
		if(AK_mode){copy("Bon :",get_p(n,0),9);k=5;}
		else{copy("Factuur :",get_p(n,0),9);k=9;}
    stcli_d(get_p(n,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(n,0)+k,3);k+=3;
    k+=date2str(get_p(n,0)+k,*pu_16_3,0);
    add_rec(n);
    used=YES;
  }
  if(used==NO){
    for(k=4;k<7;k++){
      copy("Geen bewegingen",get_p(k,0),15);add_rec(k);
    }
  }
  if(inq_mast){
    fasinit(mast_stu);*u(mast_stu,1)=inq_mast;fasgeti(mast_stu);
    copy(s(mast_stu,3),get_p(7,0),30);
  }
  else{
    fasinit(6);*u(6,1)=inq_art;fasgeti(6);
    for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
    copy(s(6,2),get_p(7,0),len_);copy(" ",get_p(7,0)+len_,1);
    copy(s(6,3),get_p(7,0)+len_+1,30-(len_+1));
  }
  add_rec(7);
  writebytes(0L,(char *)&id,sizeof id);
  writebytes(id.idx_pos,(char *)&indx[0],sizeof indx);
  fasflush(0);
  fasclos(-2);
	fasunlck(-1);
  endsr:;
  return YES;
}
 
static open_sta_file()
{
  int16 k;
  char filnam[15];
 
  zero(recbuf[0],sizeof recbuf);recnr=0;rec_working=0;kdsp=0;kdsp_off=1;
  zero(disp_str,sizeof disp_str);
  zero((char *)niv_pos,sizeof niv_pos);
  zero((char *)&id,sizeof id);
  zero((char *)&indx[0],sizeof indx);
  copy("TMP",filnam,3);
  stcli_d(&filnam[3],(long)(procid),3,0);
  copy(".sta",&filnam[6],5);
  if(fasopen(filnam,2)){errnum=63;scrget(1,170);return NO;}
  loffil=0;fasclos(-2);fasopen(filnam,3);

  copy("\xF2Vers 00001 15/03/90 (c) Jamadata\x1A",id.title,34);
  copy(s(25,1),id.firma,sizeof id.firma);
  copy_0(sta_hoofd,id.hoofding,sizeof id.hoofding);

  id.date=*u(25,2);id.q_nivs=q_niv;
  id.hdr_pos=512;
  id.idx_pos=id.hdr_pos+100*64L;
  id.bod_pos=((long)(id.idx_pos+sizeof indx)/64+1)*64;
  id.reclen=LEN_PTR;
  for(k=0;k<sizeof fld[0]/sizeof fld[0][0];k++){
    if(fld[0][k].naam[0]){
      fld[0][k].pos=id.reclen;
      id.reclen+=fld[0][k].len;
      writebytes(id.hdr_pos+k*64L,(char *)&fld[0][k],sizeof fld[0][k]);
      id.q_kol++;
    }
  }
  return YES;
}

static CalcSemKorting()
{
  int16 m;
  float nokort;

	hl_semkort=0.,calc_sem=0.,brij_tpct=0.,brij_tbd=0.;
	if(fldlen(2,56)) calc_sem=*f(2,56);
  nokort=NO;
	if(fldlen(6,104) && *s(6,104)=='J') nokort=YES;
  *u(52,1)=*i(6,9);
  if(fasgeti(52)==0){
    if(fldlen(52,21) && *s(52,21)=='N') nokort=YES;
  }
  fasinit(9);*u(9,2)=*u(2,1);*u(9,3)=*u(6,1);
  m=get_contr(1);if(m==0) nokort=NO;// wel korting indien expliciet contract op artikel
  if(m && fldlen(9,18)){ // leverancier
    *u(9,18)=*u(6,7);*u(9,19)=*u(6,9);m=get_contr(2);
    if(m){
      *u(9,19)=0;m=get_contr(2);
    }
	  if(m && fldlen(6,101)){ // merk/ producent 
      *u(9,18)=*u(6,101)+30000;*u(9,19)=*u(6,9);m=get_contr(2);
      if(m){
        *u(9,19)=0;m=get_contr(2);
      }
    }
    if(m){
      *u(9,18)=0;*u(9,19)=*u(6,9);m=get_contr(2);
      if(m==0 && (fldlen(6,104)==0 || *s(6,104)!='J')) nokort=NO;/* wel korting indien expleciet contract op groep */
    }
  }
  if(m==0){
    if(fldlen(9,21)) hl_semkort=*f(9,21);
    calc_sem=*f(9,22);
    if(fldlen(9,23)) brij_tpct=*f(9,23);
    if(fldlen(9,24)) brij_tbd=*f(9,24);
  }
endsr:;
	if(nokort){
		hl_semkort=0.,calc_sem=0.,brij_tpct=0.,brij_tbd=0.;
	}
	else{
		if(fldlen(6,37)==0 || *f(6,37)==0){hl_semkort=0;}
		else{/* omrekenen naar verpakking */
			hl_semkort=hl_semkort* *f(6,37)/100;
		}
	}
}

static get_contr(keynr_)
int16 keynr_;
{
  int16 k;

  if(faskeyi(9,keynr_,0)) return YES;
  for(k=0;k<3;k++) if(*f(9,6+k)) return NO;
  for(k=20;k<=24;k++){
    if(fldlen(9,k) && *f(9,k)) return NO;
  }
  if(fldlen(9,16) && *i(9,16)) return NO;
  return YES;
}

static upd_parameters()
{
  int16 k,z,key,curs=1;
  char *pdum,dumm_[10],*pvar;
						
  sysget(2900,40,(char *)&TbDiversArtikel[0]);
	sysget(1048,32,(char *)&TbBtwPct[0]); // 8 mogelijke pct

  pdum=&dumm_[0];
  ram_recl=s(6,3)-s(6,1)+fldlen(6,3) + 2;// + 2 bytes hash 
  hash_len=fldlen(6,1)+ fldlen(6,2)+fldlen(6,3);
  dat_len=hash_len;
  zero(ram,sizeof ram);
  for(k=0;k<10;k++){
    fasinit(6);*u(6,1)=TbDiversArtikel[k];if(*u(6,1)) fasgeti(6);
    hash_val=hash(6);
    stu2ram(6,k);
  }

  FOREVER{
    redo:;
    scrget(2,322);z=1;
    for(k=0;k<10;k++){
			if((k>0 && k<8 && TbBtwPct[k]==0) || k==8) {z+=2;continue;}  // wordt niet gebruikt
			if(k==9) scrifld(z++,fm_os8,"Leeggoed");
      else if(k==0) scrifld(z++,fm_of21_,&TbBtwPct[k]);
			else scrifld(z++,fm_of2_1,&TbBtwPct[k]);
      if(fieldspc(6,3,&pdum,fmt)>0){
				pvar=ram+(k*ram_recl + (s(6,3)-s(6,1)));
				scrifld(z++,fmt,pvar);
      }
    }
    key=scrupd(curs,0xE1);curs=1;
    if(key==111) ovlexit(-1);
    if(key==106) break;

    for(k=0;k<10;k++){
			if(k==8) continue;
      ram2stu(6,k);
      if((k==0 || k==9 || TbBtwPct[k]) && (*s(6,3)=='\0' || hash_val!=hash(6))){
				if(search(6,0)){
					errnum=39;curs=2+k*2;goto redo;
				}
				hash_val=hash(6);
      }
      else if(*s(6,3)=='\0'){fasinit(6);hash_val=0;}
      TbDiversArtikel[k]=*u(6,1);
      stu2ram(6,k);
    }

    if(key==101 || key==108){
      sysput(2900,40,(char *)&TbDiversArtikel[0]);
      break;
    }
  }
}

static ram2stu(stu_,lin_)
int16 stu_,lin_;
{
  copy(ram+(lin_*ram_recl),s(stu_,1),dat_len);
  copy(ram+(lin_*ram_recl)+dat_len,&hash_val,2);
}
						
static stu2ram(stu_,lin_)
int16 stu_,lin_;
{
  copy(s(stu_,1),ram+(lin_*ram_recl),dat_len);
  copy(&hash_val,ram+(lin_*ram_recl)+dat_len,2);
}

static uint16 hash(stu_)
int16 stu_;
{
  char *ps;
  int16 k;
  uint16 fuval=0;
				
  k=hash_len;ps=s(stu_,1);
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
}

static add_rec(niv_)
int16 niv_;
{
  int16 k;
  char firstbyte;
  long pos_;

  if(*(int16 *)&recbuf[niv_][0]==0) *(uint16 *)&recbuf[niv_][0]=0x8000+niv_;
  pos_=id.bod_pos+recnr*id.reclen;
  if(niv_pos[niv_]) writebytes(niv_pos[niv_]+6,&pos_,4);
  *(long *)&recbuf[niv_][2]=niv_pos[niv_];
  niv_pos[niv_]=pos_;for(k=niv_-1;k>=0;k--) niv_pos[k]=0;
  if(niv_){*(long *)&recbuf[niv_][10]=niv_first[niv_-1];niv_first[niv_-1]=0;}
  writerec(recnr++,niv_);
  if(recnr>id.q_rec) id.q_rec=recnr;
  if(niv_==7 && id.pos_niv7==0) id.pos_niv7=pos_;
  if(niv_first[niv_]==0) niv_first[niv_]=pos_;
  if(niv_==6){
    k=fld[0][0].len;  fm_odsp[2]=k;
    scrifld(18,fm_odsp,get_p(6,0));scrupd(-3,0);/* hoogste niveau displayen */
    for(k=0;k<10;k++){
      firstbyte=recbuf[niv_][LEN_PTR+k];/* leading spaties wegdoen */
      if(firstbyte!=' ') break;
    }
    if(firstbyte>='a' && firstbyte<='z') firstbyte+=-'a'+'A';
    if(firstbyte<'0') firstbyte=0;
    else if(firstbyte<='9') firstbyte-='0';
    else if(firstbyte<'A') firstbyte=10;
    else if(firstbyte<='Z') firstbyte+=-'A'+10;
    else firstbyte='Z'-'A'+10;
    for(k=0;k<=firstbyte;k++) if(indx[k]==0) indx[k]=pos_;
  }
  zero(recbuf[niv_],sizeof recbuf[0]);
}
 
static char *get_p(niv,kolom)
int16 niv,kolom;
{
  return &recbuf[niv][fld[0][kolom].pos];
}

static dsp_working()
{
  rec_working++;
  //if((rec_working%250)==0){
  //  if(kdsp_off==-1){if((kdsp%10)!=9) disp_str[kdsp]=' ';}
  //  else {if((kdsp%10)==9) disp_str[kdsp]='|'; else disp_str[kdsp]='*';}
  //  scrifld(22,fm_os63,disp_str);scrupd(-3,0);
  //  kdsp+=kdsp_off;
  //  if(kdsp>=50){kdsp--;kdsp_off=-1;}
  //  else if(kdsp<0) {kdsp=0;kdsp_off=1;}
  //}
}
 
static writerec(recnr_,bufnr_)
int16 bufnr_;
long recnr_;
{
  long pos_;

  pos_=id.bod_pos+recnr_*id.reclen;
  extend(pos_);
  writebytes(pos_,recbuf[bufnr_],id.reclen);
}

static writebytes(pos_,ps,len)
long pos_;
int16 len;
char *ps;
{
  int16 k;

  extend(pos_);
  if(pos_+len>loffil) loffil=pos_+len;
  while(len){
    k=len; if(k>250) k=250;
    *l(80,1)=pos_;
    copy(ps,s(80,1)+4,k);
    fasseqo(80,3,k+4);
    pos_+=k;ps+=k;len-=k;
  }
}
 
static extend(pos_)
long pos_;
{
  long l;

  while(pos_>loffil){
    l=pos_-loffil;if(l>128) l=128;
    writebytes(loffil,nullen,(int16)l);
  }
}

static int16 date2str(str_,date_,no_delim_)
char *str_;
uint16 date_,no_delim_;
{
  int16 dd,mm,jj,len_=0;
 
  if(date_==0) goto endsr;
  jddate(date_,&jj,&mm,&dd);
  stcli_d(&str_[len_],(long)dd,2,0);len_+=2;if(!no_delim_) str_[len_++]='/';
  stcli_d(&str_[len_],(long)mm,2,0);len_+=2;if(!no_delim_) str_[len_++]='/';
  stcli_d(&str_[len_],(long)jj,4,0);len_+=4;
  endsr:;
  return len_;
}

static copy_0(ps,pd,len)
char *ps,*pd;
int16 len;
{
  int16 k;
 
  for(k=0;k<len;k++) if(*(ps+k)=='\0') break;
  copy(ps,pd,k);
  return k;
}

static nextline()
{
  free=prtline();
}


static scraddf(fld,v,h,attr)
int16 fld,v,h,attr;
{
  int16 *pi;
				
  pi=(int16 *)info;
  *(pi+0)=fld;
  *(pi+1)=v;
  *(pi+2)=h;
  *(pi+3)=attr;
  sendtask(procid+20,3,11,info,8);
  scrnum=0;
}

static initload()
{

  char *pdum_;
 
  fasunlck(0);
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(13);
			
  sysget(294,4,def_munt);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
	sysget(1048,32,(char *)&TbBtwPct[0]); // 8 mogelijke pct
  sysget(2723,2,&sys2723);
	sysget(3000,2,&sys3000); // datamasters
  sysget(4294,40,(char *)&KasKltRec[0]);
  sysget(4397,2,&sys4397);
  fieldspc(16,30,&pdum_,fmt_qlv);
  fieldspc(16,31,&pdum_,fmt_bdr);
  fasinit(80);fasinfo(80,207);

  pu_2_1=u(2,1);
  pu_6_1=u(6,1);
  pu_16_3=u(16,3);

  pl_80_1=l(80,1);
  p_data=s(80,1)+4;
  zero(&seldata.data_begin,sizeof seldata); seldata.dt_s_beg=*u(25,2)-730;

	StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
	StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
	StylTitel=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,0,0,KLEUR_LICHTBLAUW,1,1,0,NO,NO);
}

static seqo_fld(stu_,fld_)
int16 stu_,fld_;
{
  int16 yy,mm,dd;
  float fbd_;
  char str_[25];
 
  if(fldlen(stu_,fld_)==0) goto endsr;
  fmt_get(stu_,fld_);
  if(fmt[1]==0xC8 || fmt[1]==0x88){/* string */
    char2str(s(stu_,fld_),fldlen(stu_,fld_));
  }
  if(fmt[1]==0xD0 || fmt[1]==0x90){/* uint16 */
    fbd_=*u(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xD1 || fmt[1]==0x91){/* integer */
    fbd_=*i(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xD3 || fmt[1]==0x93){/* long */
    fbd_=*l(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xD4 || fmt[1]==0x94){/* float */
    fbd_=*f(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xD5 || fmt[1]==0x95){/* double */
    fbd_=*d(stu_,fld_);
    flt2str(fbd_);seqo_str[pos++]=0x09;
  }
  if(fmt[1]==0xC0 || fmt[1]==0x80){/* date */
    if(*u(stu_,fld_)==0) seqo_str[pos++]=0x09;
    else{
      jddate(*u(stu_,fld_),&yy,&mm,&dd);
      stcli_d(str_,(long)dd,2,0);str_[2]='/';
      stcli_d(&str_[3],(long)mm,2,0);str_[5]='/';
      stcli_d(&str_[6],(long)yy,4,0);
      char2str(str_,10);
    }
  }
  if(fmt[1]==0xA8 || fmt[1]==0xE8){/* grb */
    zero(str_,sizeof str_);
    grb_deco(str_,l(stu_,fld_));
    char2str(str_,10);
  }
	if(fmt[1]==0x98 || fmt[1]==0xD8){// btw
		zero(str_,sizeof str_);
		if(*l(stu_,fld_)){
			copy("BE-",str_,3);btw_deco(&str_[3],(long *)s(stu_,fld_),1);
	    //{copy("BE-0",str_,4);btw_deco(&str_[4],(long *)s(stu_,fld_),1);}
	  }
		char2str(str_,15);
	}
  endsr:;
}

static cnv_fname(ps_,len_)
char *ps_;
int16 len_;
{
  char kar_;
  int16 k;
									
  for(k=0;k<len_;k++){
    kar_=*(ps_+k);
    if(kar_==0) break;
    if(kar_>='A' && kar_<='Z') continue;
    if(kar_>='a' && kar_<='z') continue;
    if(kar_>='0' && kar_<='9') continue;
    if(kar_==' ' || kar_=='-' || kar_=='_') continue;
    *(ps_+k)=' ';
  }
}

static char2str(ps_,len_)
char *ps_;
int16 len_;
{
  int16 k,orig_pos_;
 
  orig_pos_=pos;
  if(len_){
    copy(ps_,&seqo_str[pos],len_);while(seqo_str[pos]) pos++;
    for(k=orig_pos_;k<pos;k++){
      if(seqo_str[k]==0x09) seqo_str[k]='.';/* delete | */
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;/* delete trailing blanks */
    pos++;
  }
  seqo_str[pos++]=0x09;
}

static flt2str(bdf_)
float bdf_;
{

  int16 k,negat_;
  double bd_,bd1_,bd2_;
  long lbd1_,lbd2_;
  char str_[15];
 
  bd_=valu_cnv("EUR","EUR",(double)(bdf_),(double)(0.01));
	negat_=NO; if(bd_<0){negat_=YES;bd_=-bd_;}

  zero(str_,sizeof str_);
  bd1_=(long)(bd_);
  bd2_=(long)((bd_-bd1_)*(double)(100.) +(double).49);
  lbd1_=(long)(bd1_+.49); lbd2_=(long)(bd2_+.49);
  stcli_d(str_,lbd1_,8,1);
	if(lbd2_){str_[8]=','; stcli_d(&str_[9],lbd2_,2,0);}
  if(negat_){                                             /* negatief getal */
    for(k=0;k<10;k++) if(str_[k]!=' ') break;
    if(k>0) str_[k-1]='-';
  }
  for(k=0;k<10;k++) if(str_[k]!=' ') break;
  pos+=copy0(&str_[k],&seqo_str[pos],12-k); 
}

 
static seqo_flush()
{
  if(seqo_len){
    *l(80,1)=seqo_pos;
    fasseqo(80,seqo_mode,seqo_len+4);
    seqo_pos+=seqo_len;
    seqo_len=0;
  }
}
 
static fmt_get(stu_,elet_)
int16 stu_,elet_;
{
  int16 k;
  char *pdum,dummy_[10];
					
  pdum=&dummy_[0];
  k=fieldspc(stu_,elet_,&pdum,fmt);
  if(k>0) return k;
  return 0;
}
 
static fileopen(nr_)
int16 nr_;
{
  int16 stu_,k;
  char filename[15];
							
  k=300+17*(nr_-1);
  sysget(k,15,filename);
  sysget(k+15,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(errnum=fasopen(filename,0)) ovlexit(-1);
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;}
  }
}
 
static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os1,"-");
}

static p_pdfname(naam_,dt_beg_,dt_end_)
char *naam_;
uint16 dt_beg_,dt_end_;
{
  int16 pos_,slen_,len_,dd,mm,yy;
  char buf_[30],string[100];
				
  zero(string,sizeof string);
  for(slen_=0;slen_<50;slen_++){
    if(naam_[slen_]=='\0') break;
    string[slen_]=naam_[slen_];
  }
  if(dt_beg_){
    string[slen_++]=' ';
    jddate(dt_beg_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[slen_],(long)dd,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)mm,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)yy,2,0);slen_+=2;
  }
  if(dt_end_){
    if(dt_beg_){copy(" - ",&string[slen_],3);slen_+=3;}
    jddate(dt_end_,&yy,&mm,&dd);yy%=100;
    stcli_d(&string[slen_],(long)dd,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)mm,2,0);string[slen_+2]='/';slen_+=3;
    stcli_d(&string[slen_],(long)yy,2,0);slen_+=2;
  }
  for(dd=0;dd<slen_;dd++) if(string[dd]=='\\' || string[dd]=='/') string[dd]='-';
  pos_=0;
  FOREVER{
    if(slen_<=0) break;
    zero(buf_,sizeof buf_);
    copy("\xD0\xCF",buf_,2);
    if(slen_>25) len_=25; else len_=slen_;
		if(string[pos_+len_-1]=='.') string[pos_+len_-1]=' '; // geen punt op einde van naam 
    copy(&string[pos_],&buf_[2],len_);
    buf_[2+len_]=0xD0;
    prttext(buf_);
    slen_-=len_;pos_+=len_;
  }
}
static double Round(bd_,bd_afr_)
double bd_,bd_afr_;
{
  double wrk1_,wrk2_,wrk3_,add_,result_;
 
  result_=bd_;
  add_=0.500001;
  if(result_<0) add_=-add_;
  if(bd_afr_>0.00001){
    if(bd_afr_<=1.){
      wrk1_=(long int)result_;
      wrk2_=result_-wrk1_;
    } else{wrk1_=0.;wrk2_=result_;}
    wrk3_=wrk2_/bd_afr_;
    wrk2_=(double)((long)((wrk2_/bd_afr_)+add_)) * bd_afr_;
    result_=wrk1_+wrk2_;
  }
  endsr:;
  return (double)(result_);
}

static scr_ok(ptxt)
char *ptxt;
{
  int16 key;

  scrget(1,169);
  scrifld(12,fm_os63,ptxt);
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  return NO;
}
 
static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
#if 0
  if(stu_<=2) parmcall[1]=7;          bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3;                                            GEEN ADD
#endif
  if(stu_==6) parmcall[1]=0;
  parmcall[2]=0;
  parmcall[3]=0;
#ifdef STRAATKEY
  if(stu_==2) parmcall[4]=STRAATKEY;
#endif
  parmcall[7]=0x04;
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}
