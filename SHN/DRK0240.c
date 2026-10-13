/*32-01*/
#ifdef  _WIN32
#pragma pack(1)
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
__declspec(dllimport) unsigned char PrintOverlayRef;

#include "OvlShare.h"



char ovldat[] = "drk0240  00*25 05/01/11 (c) Jamadata";
     // FLAGABT : berekenen aantal palletten met functietoets F9 in dsp_detail() + bijhorende factuurnr vragen bij creditnota + HLkorting is NIET per HL maar per bak
     // FLAGALB : omzet op lev.adres bijhouden indien 2,52=='J'
     // FLAGALS : handlingkosten 
     // FLAGARS : NOOIT automatisch mailen B02 (via sys2696)
     // FLAGAST : BTW-eenheid : aan 0% factureren + boeken op 709xxx + aparte tekst op factuur
     // FLAGBLI : lev.adres tonen bij kassa-facturatie
     // FLAGBDT : brandstof ALTIJD inc. BTW
     // FLAGBSA : enkel in sommige firma's BTW op 0 zetten bij buitenl.BTWnummer + speciale intrastat bijwerking
     // FLAGCMB : CO2-gekoppeld artikel (6,79) + tot.gewicht tonen op scherm (=HL-volume)
     // FLAGCOR : setallbtw()
     // FLAGCRA : Indien facturatie aan kassaklant, dan ook de de stock van dat filiaal verhogen
     // FLAGCRL : referentie in opmerking boekhouding zetten + geen F9 neem deze nummer bij leveringsbons
     // FLAGDKR : opmerking klantenfiche afdrukken op lijst bons / 2e factuur bijhouden als PDF ipv af te drukken
     // FLAGDLA : korting EUR na % rekenen, dus wordt bij HLkorting geteld
     // FLAGDLT : aparte layout voor KARWEI (kassafactuur 8,74 op 1)
     // FLAGDMS : ristourno boeken op 499100 (D) en 499200 (C) buiten BTW
     // FLAGDUB : veld 58,60 tonen ipv 58,26 in dsp_detail
     // FLAGDU3 : gratis artikels de accijns toch rekenen + particuliere verkopen op 1 klant (DIV2) bijhouden
		 // FLAGEBO : flessen 5% bijtellen
     // FLAGEET : facturen drankgigant 2x drukken + bij prijstype A, steeds 2% winst nemen
     // FLAGEPD : korting EUR na % rekenen, dus wordt bij HLkorting geteld, betalingen drukken op bon/factuur
     // FLAGFLI : veld 58,60 tonen ipv 58,26 in dsp_detail
     // FLAGGSN : Kredietbeperking als disconto en boeken op DISCONTO VERKOOP
     // FLAGGRS : specifieke kolommen bij bonlijst in XLS 
     // FLAGLAT : factuur zonder layout drukken met F5 (dsp_tot)	
     // FLAGMIN : Bij aanpassen bons, deze default maar 1 keer afdrukken.  
     // FLAGMIM : Adres-etiket drukken met F5 (dsp_tot)
     // FLAGPMC : Kredietbeperking (VAST 4%) (voor 30/11/14 :boeken op DISCONTO VERKOOP) + offertes zonder opslaan
     // FLAGOPS : aantal afdrukken (dsp_tot) en wis dubbel artikels
     // FLAGPAU : lijst bons op aparte formaat 14 	
     // FLAGPED : NIET meer sinds 18/1/21 : paletkortingen en baktoeslag via 58,70/58,71(!) en 8,34/8,35  
     // FLAGQIC : Kredietbeperking klt-fiche omgedraaid (2,44 =wel kredietbeperking)
     // FLAGPWH : aantal zelf berekenen bij 'B' + KREDIETBEPERKING 
     // FLAGSCE : kassafacturen op 702xxx
     // FLAGSCP : geen korting indien stuks
     // FLAGSEG : totaalprijs  en korting (58,60)! en (58,22)
     // FLAGSMM : naam werkpost invullen in bonopmerking + wis dubbel artikels via F10
     // FLAGVDW : korting EUR na % rekenen, flessen 10% bijtellen
     // FLAGVLA : tekstfile kunnen ingeven
     // FLAGVNT : BTW niet automatisch op 0 zetten bij buitenl.BTWnummer
     // FLAGVRK : facturatie uit bons : factuurnummer moet zelfde als bonnummer zijn	
     // FLAGVRL : GEEN lijnnummers in dsp_detail owv plaatsgebrek
     // FLAGWAT : setallbtw()
     // FLAGWYN : opmerking doorgeven aan expert/m 

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define DIM8            100
#define DIM58           800
#define EL_BKH          80
#define DF_GRB          16
#define OPMLEN          20
#define BTWDIV          2
#define BTWDIM          8+BTWDIV
#define MAXFLD          120
#define MINFREE         20
#define flag            uint16
#define DIM_TKLT        400
#define MAP_OFFERTE     "..\\Offerte\\"

#define KLEUR_BEIGE         0xEBAE15
#define KLEUR_DONKERGROEN   0x21A72B //125A23
#define KLEUR_LICHTGROEN    0xC4D79B
#define KLEUR_LICHTBLAUW    0xC4D9DD
#define KLEUR_WIT           0xFFFFFF

#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_RDWR         0x0002  /* open for reading and writing */
#define O_APPEND       0x0008  /* writes done at eof */
#define O_CREAT        0x0100  /* create and open file */
#define O_TRUNC        0x0200  /* open and truncate */
#define O_EXCL         0x0400  /* open only if file doesn't already exist */
#define O_TEXT         0x4000  /* file mode is text (translated) */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */




extern char RamBon[];
extern int RamBonSize;
extern char SelectedFileName[100];
#include "par0240.c"
#ifdef OVL0241_C
#include "par0241.c"
#endif
#ifdef OVL0242_C
#include "par0242.c"
#endif
#ifdef OVL0243_C
#include "par0243.c"
#endif
#ifdef OVL0244_C
#include "par0244.c"
#endif
#ifdef OVL0245_C
#include "par0245.c"
#endif
#ifdef OVL0246_C
#include "par0246.c"
#endif
#ifdef OVL0247_C
#include "par0247.c"
#endif
#ifdef OVL0248_C
#include "par0248.c"
#endif
#ifdef OVL0249_C
#include "par0249.c"
#endif
#ifdef OVL0250_C
#include "par0250.c"
#endif
#ifdef OVL0251_C
#include "par0251.c"
#endif
#ifdef OVL0252_C
#include "par0252.c"
#endif
#ifdef OVL0253_C
#include "par0253.c"
#endif
#ifdef OVL0254_C
#include "par0254.c"
#endif
#ifdef OVL0255_C
#include "par0255.c"
#endif
#ifdef OVL0256_C
#include "par0256.c"
#endif
#ifdef OVL0257_C
#include "par0257.c"
#endif
#ifdef OVL0258_C
#include "par0258.c"
#endif
#ifdef OVL0259_C
#include "par0259.c"
#endif
#ifdef OVL0941_C
#include "par0941.c"
#endif
#ifdef OVL0942_C
#include "par0942.c"
#endif
#ifdef OVL0943_C
#include "par0943.c"
#endif
#ifdef OVL0944_C
#include "par0944.c"
#endif
#ifdef OVL0945_C
#include "par0945.c"
#endif
#ifdef OVL0946_C
#include "par0946.c"
#endif
#ifdef OVL0947_C
#include "par0947.c"
#endif
#ifdef OVL0948_C
#include "par0948.c"
#endif
#ifdef OVL0949_C
#include "par0949.c"
#endif
#ifdef OVL0950_C
#include "par0950.c"
#endif
#ifdef OVL0951_C
#include "par0951.c"
#endif
#ifdef OVL0952_C
#include "par0952.c"
#endif
#ifdef OVL0953_C
#include "par0953.c"
#endif
#ifdef OVL0954_C
#include "par0954.c"
#endif
#ifdef OVL0955_C
#include "par0955.c"
#endif
#ifdef OVL0956_C
#include "par0956.c"
#endif
#ifdef OVL0957_C
#include "par0957.c"
#endif
#ifdef OVL0958_C
#include "par0958.c"
#endif
#ifdef OVL0959_C
#include "par0959.c"
#endif
 
#define BEDRAG          double
static char fmeobd[]   = {6,0x95,6,2,0x70,0};                          /* fm_od9_2 */
static char fmeobdk[]  = {6,0x95,5,2,0x70,0};
static char fmeobdk1[] = {6,0x95,6,2,0x60,0};                    /* geen 1000-punt */
static char fmeobdk2[] = {6,0x95,6,2,0x60,0};
									
static char fmfobd[]   = {6,0x95,9,0,0x70,0};                          /* fm_od9_0 */
static char fmfobdk[]  = {6,0x95,7,0,0x70,0};
static char fmfobdk1[] = {6,0x95,7,0,0x70,0};
static char fmfobdk2[] = {6,0x95,7,0,0x70,0};
#define TABT            "<t69>"
									
static char fm_obd[40],fm_obdk[40],fm_obdk1[40],fm_obdk2[40];

static char *voldtxt[4] = {"Voldaan","Pour acquit","Received","Betrag erhalten"};

static struct {
  int16 begpos;
  int16 lengte;
  char *txt[4];
} firm[10] = {116,17,"Telefoon","N� t�l�phone","Telephone","Telefon",
	     170,17,"Fax","Fax","Fax","Fax",
	      86,15,"B.T.W. nr.","N� T.V.A.","VAT No","M.W.S.",
	     101,14,"Bankrek.","Banque","Bank","Bank",
	     134,12,"RPR","RPM","RLP","RJP",
	     149,20,"Erkenningsnr","","","",
	     188,30,"Website","Website","Website","",
	     222,30,"E-mail","E-mail","E-mail","",
	     256,30,"IBAN","IBAN","IBAN","IBAN",
	     298,11,"BIC","BIC","BIC","BIC"};

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_us75[]  = {7,0xC8,75,0,0,0,0};
static char fm_us60[]  = {7,0xC8,60,0,0,0,0};
static char fm_us40[]  = {7,0xC8,40,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us25[]  = {7,0xC8,25,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us7[]   = {7,0xC8,7,0,0,0,0};
static char fm_us1[]   = {7,0xC8,1,0,0,0,0};
static char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
static char fm_us1_U[] = {7,0xC8,1,0,1,0,0};
static char fm_os79[]  = {7,0x88,79,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os60[]  = {7,0x88,60,0,0,0,0};
static char fm_os59[]  = {7,0x88,59,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os40[]  = {7,0x88,40,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os25[]  = {7,0x88,25,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os14[]  = {7,0x88,14,0,0,0,0};
static char fm_os10[]  = {7,0x88,10,0,0,0,0};
static char fm_os7[]   = {7,0x88,7,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os2[]   = {7,0x88,2,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_ui4[]   = {6,0xD1,4,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_uu1[]   = {6,0xD0,1,0,0x60,0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_ou2[]   = {6,0x90,2,0,0x60,0};
static char fm_ud5_2[] = {6,0xD5,5,2,0x70,0};
static char fm_od5_2[] = {6,0x95,5,2,0x70,0};
static char fm_od4_2[] = {6,0x95,4,2,0x70,0};
static char fm_od42_[] = {6,0x95,4,2,0x60,0};
static char fm_od62_[] = {6,0x95,6,2,0x60,0};
static char fm_uf60[]  = {6,0xD4,6,0,0x60,0};
static char fm_of6_0[] = {6,0x94,6,0,0x70,0};
static char fm_of6_2[] = {6,0x94,6,2,0x70,0};
static char fm_of5_3[] = {6,0x94,5,3,0x70,0};
static char fm_of4_2[] = {6,0x94,4,2,0x70,0};
static char fm_of40_[] = {6,0x94,4,0,0x60,0};
static char fm_of62_[] = {6,0x94,6,2,0x60,0};
static char fm_of3_1[] = {6,0x94,3,1,0x70,0};
static char fm_uf3_3[] = {6,0xD4,3,3,0x70,0};
static char fm_uf2_0[] = {6,0xD4,2,0,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_uf2_2[] = {6,0xD4,2,2,0x70,0};
static char fm_uf21_[] = {6,0xD4,2,1,0x20,0};
static char fm_ol06[]   = {6,0x93,6,0,0x00,0}; // voor factuurnummers met jaartal
static char fm_ol8[]   = {6,0x93,8,0,0x70,0};
static char fm_ul8[]   = {6,0xD3,8,0,0x70,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};
static char fm_ogrb[]  = {2,0xA8};
static char fm_ugrb[]  = {2,0xE8};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_u_BG[]  = {11,0xC8,1,0,1,0,'B','B','G','G',0};
static char fm_u_JNS[]  = {13,0xC8,1,0,1,0,'J','J','N','N','S','S',0};
static char fm_u_JNA[]  = {13,0xC8,1,0,1,0,'J','J','N','N','A','A',0};
static char fm_u_JN_[]  = {13,0xC8,1,0,1,0,'J','J','N','N',' ',' ',0};
static char fm_u_JN[]  = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_o_JN[]  = {11,0x88,1,0,1,0,'J','J','N','N',0};
static char fm_u_04[]  = {10,0xD0,1,0,0x60,0xC0,0,0,4,0};
static char fm_uref[]  = {11,0xC8,8,0,1,0,'A','Z','0','9',0};
static char fm_us_09[] = {9,0xC8,1,0,1,0,'0','9',0};

extern char *s();
static flag yet_booked();
extern int16 *i();
extern uint16 *u(),dateadd(),get_date();
static uint16 find_grb(),sear_grb(),hash();
extern long *l(),val();
static long makegrb();
extern float *f();
extern double *d(),valu_cnv();
static double getsaldo();
static BEDRAG round(),integ();

extern int16 retcall,parmcall[8];
extern uint16 procid,onext;
extern char info[];

static float get_num();
static char *p_data,*rec_ele();
static long *pl_80_1;
static unsigned SpoolFileNr;
static int16 ft_off,max_kassa;
static char *maand_str[12]={"JAN","FEB","MRT","APR","MEI","JUN","JUL","AUG","SEP","OKT","NOV","DEC"};
static int16 det_nr[]={7,9,10,11,62,15,16,19,20,21,24,27,25,26,71,89};
static int16 stu,mode,free,journl,boek_JN='J',stock_JN='J',z_base,hash_len,filiaal,DefaultFiliaal,SysPosNrCheck,BlockAutoSend,FactureerBonDirect;
static int16 def_qfact,btw_kol,zz,stu58_len,notfound,kasjrnl,inq_kassa,PageNr,PageCount,DubbelA4Mode,KassaPrxNr,KassaPrxNrStuk;
static int16 b2228,b3604,b3606,sys2989, taaltxt=0,taal_nr,q_per_line,Year,Month,Day;
static int16 form_dat[8],prtnr,pr_mode,stu_80_ix,prxnr,kastype,selprt12=1,skip_off,mnd_strt,inq_filiaal;
static uint16 ft_date,ft_nr,last_vf,last_vfa,last_arc,MinBkhDatum,verv_dt,disk_dt,sel_toer[5],bkhref_ftnr;
static uint16 klt_div1,klt_div2,max_line,osalkasa,last_17a,last_17,rec_kas,rec_BCkas,PrijsDatum;
static uint16 selrec8[DIM8],rec_8[DIM8],rec_58[DIM58],Ix58[DIM58],last_vt[2],dt_bon_beg,dt_bon_end,sys3952;
static uint16 rec_r,lgrec_r,toer_klt[DIM_TKLT],toer_qbons[DIM_TKLT],inq_toer,new_date,a_rec_nr,InqBonNr,RecLevKostArt;
static int16 seqo_len,SeqiMode=1,pos;
static long ram_size,tb_grbnotfound[20];
static uint16 stat_klt,orig_klt,rec_d_vk,last_art,inq_lev,inq_art,inq_klt,nr_beg,nr_end,inq_grp;
static char firma[350],def_ext[2],def_inc,verv_term[4],*ram,b3598[6],osalmunt,nm_fil[10],inq_eenheid[3][5],inq_magaz[10],OnlyKassaBons,sel_bonref[20],sel_exclude_bonref[20];
static char opm_foot[4][75],nm_dehr[43],std_txt[4][61],opm_bkh[20],ft_munt[3],boekvalu,OriFtFileName[50],SelectieAlleVoldaneBons,InqMaggefactureerd;
static char fmt[40],prt_levbon,ft_tijdstp,strblist[80],add_ftvk,SelExt,CheckPeppolKlant;
static char def_munt[4],leeggcod[20],sortbuf[1000],buf1000[1000],oldnm[43],txtfile[30],SelectieMagGefactureerd='A';
static char filnam[80],txtbuf[300],werkveld[25],sys3896[6],FtPdfFilename[50];
static char seqo_str[500],sif_fil[20],KommaKarakter='.',FieldSeparator='|',OutputMapUbl[50],MapPdfFacturen[50],MapPdfBons[50],ExtraBijlageFactuurmail[50];
static char nm_loc[10][6],fles_r,ref_offerte[10];
static float def_btw,btw_glob,btw_pct[BTWDIM],max_btw;
static float tot_kort,tot_leeg,semestpc,brij_tpct,brij_tbd,hl_korting,hl_semkort,BtwLeveringskost;
static long grb_kas,grb_BCkas,grb_d_vk,lbedrag,a_grbrek;
static long TbDiversArtikel[10]; // divers artikel per mogelijk BTW%
static long fil_pos[50],begfpos;
static long seqo_pos,value,sfree;
static BEDRAG alg_tot,belastbt,btw_tot,btw_bas[BTWDIM],incl_bas[BTWDIM],disk_bd,kredietbp_bd,tot_subs,tot_AKWgoed,KM_heffing;
static BEDRAG btw_bd[BTWDIM],semestbd,winst_bd,v_alg_tot,tot_promo,kort_btw[BTWDIM],BdBetaaldBC,BdBetaaldCASH;
static double ealg_tot,ft_afrond,prx_afrond,klt_saldo,tot_accijns;
static double omzet,osalkas,tot_voors,trans_kost,TotaalVervallenFacturen;
static float winst_pc,tot_gewicht;
static float prx_r,kort_r,aant_r,lgprx_r,lgaant_r;
static flag disk_ei,art_exist,bkh_exist,k_omz_exist,prt_error,auto_enter,UseAKPrijs,FlagVervallenFacturen,ViaToer;
static flag hist_exist,lev_ask,waard_inc,sear_stt,vm_munt,lvcd,klcd,chk_btoeg,SCE_kassaFT,SPEC_factuurflag;
static flag stuk_per_stuk=YES,keepdata,sys2170,sys1787,newkort,nokort,chk_nr,DoBlokkeerCheck=YES;
static flag sys3876,centiem,sys1862,lgadded,sys3894,sys3918,upd_mode,sys4608,sys4400,fl_multibon;
static flag prt_KOPIE,sys4408,sys2696,sys3586,sys2727,prt2pdf,sys2940,sys1804;
#if FLAGALS
static float hk_pct[2][2];
static long hk_omzgrb[8],hk_kostgrb[2];
#endif
static uint16 dt_kvk[20],loc_klt[20],loc_nr[20];
static char nm_kassa[20][6];
// XLS
extern int16 ilength;
static int16 XlsRef,XlsRij,XlsKol;
static int16 *pi;
// einde xls

static int16 len2_14,len58_25,len58_15,len58_35,len8_23,len58_62,len2_3,len6_3;
static char *ps_2_3,*ps_58_15,*ps_58_16,*ps_58_25,*ps_8_23,*ps_58_62,*ps_6_3;
static uint16 *pu_8_28,*pu_2_1,*pu_58_1,*pu_6_1,*pu_58_14;
static long *pl_58_32;
static float *pf_58_24;
static float *pf_58_20,*pf_58_21,*pf_58_31,calc_sem,calc_kort,calc_prx,calc_kfr,calc_defprx;
static double *pd_58_35;
static long kltcent,grb_notf;
static char talen[4];
static uint16 q_paletstick;

static struct {
  uint16 nr;
  uint16 typ;
  char nm[16];
  uint16 lastnr;
  long fingrb;
  long saldo;
  double saldo_vm;
  char munt[4];
  uint16 blz_o;
  uint16 blz_n;
  char mast_munt;
  double e_saldo;
} j_tab[80];

#if FLAGEPD
static struct{
	char BetCode[10];
	uint16 Jnl[10];
} PaySettings;

// SPECIFIEK 
static struct _BetTabel {
	uint16 Datum;
	double Bedrag;
	uint16 Proces;
	char Bcode;
} BetTabel[30];
static uint16 BetCount;
//

#endif

static struct{
  uint16 ft_nr;
  uint16 ft_date;
  uint16 stu8len;
  uint16 stu58len;
  double alg_tot;
  double belastbt;
  double btw_tot;
  double tot_leeg;
  char opm_foot[4][75];
  int16 stu8[200][2];
  int16 stu58[200][2];
} ft_stu;




#if BOEKALLO && BOEKEXEC
static uint16 rec_nr[EL_BKH],df_recnr[DF_GRB];
static long grb_tb[EL_BKH],opmhoev[EL_BKH];
static BEDRAG bedrag[EL_BKH];
static char df_rek[DF_GRB][4];
#endif
 
#if PDA_LGRETOUR | PDA_VERKOOP | PDA_TRACEER

			
static struct{
  uint16 krec;
  uint16 bonnr;
  char filename[30];
  char datestr[15];
  char timestr[10];
	double bd_betaald;
} pdabons[50];
			
static int16 q_pdabons,pbonnr=-1;
#endif
 
#if COPY_FACT
static int16 smode,seqo_pos,sfree;
#endif

static struct{
  char eenh[5];
  float q_bak;
  float q_fles;
} cent[20];

static struct{
  char code[2];
  char naam[10];
} chauffeur[10];
 
#if INTRASTAT
static int16 intr_stel;
static struct _intras{ // zelfde houden als stu4 !
  int16 stelsel;
  char staat1[2];
  int16 vervoer;
  int16 transakt;
  char goedercod[8];
  double gewicht;
  double aanveenh;
	char staat_ori[2];
} *p_intras, bkh_intras[EL_BKH];
#endif

#if SEARBFLEN
static float btwpct[4];
static uint16 vers_298;
static char taal_i;
static char searbuf[SEARBFLEN+1];
#endif


#if BONLIST2XLS
#include "Std\XlsFunc.c"
#endif



#if FLAG253/* uitschrijven bon naar ascii */
ovlcod()
{
  int16 k;
 
  initload();
  upd_mode=YES;
  FOREVER{
    ft_init(YES);
redo:
		fasunlck(-1);
    if(!get_klt("uit te schrijven",YES)) break;
    if(!load_bon(NO,0)) goto redo;
    select_mnt();
    calc();/* totalen echte bon en kassaprijs laten zien */
    v_alg_tot=alg_tot;
    prxnr=*s(2,26)-'0';
    if(prxnr<0 || prxnr>9) prxnr=0;
    if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
    def_inc='N';if(sys3894 & (1<<prxnr)) def_inc='J';
    for(k=0;k<max_line;k++){
      ram2stu(k);
      if(*pu_58_14){
	fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
	*pf_58_20=*f(6,PrNrs[prxnr]);
	if(len58_62 && *ps_58_62=='S' && *f(58,63)!=0){/* bij benadering juist */
	  *pf_58_20/=*f(58,63);*pf_58_20=round((double)(*pf_58_20));
	}
	*pf_58_24=*f(6,28);
	*s(58,27)=def_inc;
	*pf_58_21=0;
      }
      stu2ram(k);
    }
    calc();
    alg_tot-=tot_leeg;/* leeggoed is altijd 0, dus goederen+BTW */
    if(dsp_tot(2)==NO) goto redo;
    if(!bon2sif()) goto redo;
    fasflush(0);
  }
  ovlexit(-1);
}


static bon2sif()
{
  int16 z,k,key,kas_,clip_;
  uint16 rec_;
  char str_[20],*ps_,*pd_;
	float factor_;
							
  pl_80_1=l(80,1);
  p_data=s(80,1)+4;
  sysget(4676,20,sif_fil);
  FOREVER{
    redo:;
    scrget(2,143);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_us20,&sif_fil);
    key=scrupd(2,0x81);
    if(key==101) return YES;
    if(key==108){
      zero(filnam,sizeof filnam); kas_=99;
      for(k=0;k<10;k++){
				sysget(4294+k*2,2,&rec_);
				if(rec_==*pu_2_1) break;
      }
      if(k<10){
				zero(str_,sizeof str_);
				copy("TO\\KASSA-",str_,9);
				stcli_d(&str_[9],(long)(k+1),2,0);
				str_[11]='\\';
				mk_name(3902,str_);
				pd_=filnam; ps_=sif_fil;
				while(*pd_) pd_++;
				while(*ps_!='\0') *pd_++=*ps_++;
				kas_=k;
      }
      else mk_name(3902,sif_fil);
/*    mk_name(3902,sif_fil); */
      fasclos(-2);
      if(fasopen(filnam,2)){errnum=53;goto redo;}
			break;
    }
  }
  scrget(1,7);scrupd(-3,0);
	fasunlck(-2);
  fasinit(80);seqo_pos=0;SeqiMode=2;
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*f(58,7) && *u(58,14) && *s(58,16)){
      if(sys4408){/* code langer dan 5, recordnummer ipv codenummer */
	zero(s(58,15),fldlen(58,15));
	stcli_d(s(58,15),(long)(*u(58,14)),5,0);
      }
      make_str();
      dump_str();
    }
  }
  fasflush(0);
#if FLAGSAS
  fasclos(-2); kas_=0; // altijd naar filiaal
#else
  *l(80,1)=0xFFFFFFFF;
  fasseqo(80,SeqiMode,4);/* correct date/time */
  fasclos(-2);
  fasopen(filnam,103);/* archive bit afzetten */
  fasclos(-2);
  sysput(4676,20,sif_fil);
#endif
/* stock van depot muteren naar kassa */
  if(fldlen(66,1)!=0 && kas_!=99 && scr_ok("Wenst U deze stock te muteren naar de winkel ?")==YES){
    for(k=0;k<max_line;k++){
      ram2stu(k);
      if(*f(58,7) && *u(58,14) && *s(58,16)){
				fasinit(6);*pu_6_1=*u(58,14);fasgeti(6);
				clip_=NO;
				if(fldlen(6,102) && *u(6,102)){// is dit een clip?
					factor_=*f(6,31);
					*u(6,1)=*u(6,102);fasgeti(6);
#if FLAGSAS | FLAGGRS | FLAGALB  | FLAGAST
					clip_=YES; // gekoppeld, altijd moederfiche bijwerken
#else
					if(*f(6,31)!=factor_) clip_=YES;
#endif
					fasinit(6);*u(6,1)=*u(58,14);fasgeti(6);
				}
				factor_=1.;
				if(clip_){// stock/omzet op moederfiche bijwerken
					factor_=*f(6,31);
					*u(6,1)=*u(6,102);fasgeti(6);
					if(*f(6,31)) factor_/=*f(6,31); else factor_=1.;
				}
				fasinit(66),*u(66,2)=*u(6,1);
				if(faskeyi(66,1,0)){fasinit(66); *u(66,2)=*u(6,1);fasadd(66);faskeyi(66,1,0);}
				*f(6,33)-=*pf_58_31*factor_;
				*f(66,11+kas_*15)+=*pf_58_31*factor_;
				*f(66,14+kas_*15)+=*pf_58_31*factor_;
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				if(*u(66,1)){fasupd(66);fasupd(6);}
      }
    }
  }
	fasunlck(-1);
  endsr:;
}

static make_str()
{
  zeros(seqo_str,sizeof seqo_str);pos=0;
  char2str(15,5);
  flt2str(7);seqo_str[pos++]='|';
  char2str(62,1);
  seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
}
 
static char2str(nr_,max_len_)
int16 nr_,max_len_;
{
  int16 len_,k,orig_pos_;
 
  orig_pos_=pos;
  len_=fldlen(58,nr_); if(len_>max_len_) len_=max_len_;
  if(len_){
    copy(s(58,nr_),&seqo_str[pos],len_);while(seqo_str[pos]) pos++;
    for(k=orig_pos_;k<pos;k++){
      if(seqo_str[k]=='|') seqo_str[k]='.';/* delete | */
    }
    pos--;
    while(seqo_str[pos]==' ') pos--;/* delete trailing blanks */
    pos++;
  }
  seqo_str[pos++]='|';
}

static flt2str(nr_)
int16 nr_;
{
  double bedrag_,add_=0;
  long val_;
								
  bedrag_=*f(58,nr_);if(bedrag_<0) add_=-.5; else add_=.5;
  if(bedrag_!=*f(58,nr_)) bedrag_=round(bedrag_);
  val_=bedrag_*100+add_;value=val_/100;
  val2str(0);
  value=val_-value*100;
  if(value){
    seqo_str[pos++]='.';
    if(value<0) value=-value;val2str(1);
  }
}

static val2str(mode_)
int16 mode_;
{
  int16 k;
  char buff[15];

  zeros(buff,sizeof buff);
  if(mode_==0){
    stcli_d(&buff[0],value,10,1);
    for(k=0;k<10;k++){
      if(buff[k]=='\0') break;
      if(buff[k]!=' ') seqo_str[pos++]=buff[k];
    }
  }
  else{
    if(value<0) value=-value;
    stcli_d(&buff[0],value,2,0);
    for(k=1;k>=0;k--) if(buff[k]!='0') break;
    copy(&buff[0],&seqo_str[pos],k+1);pos+=k+1;
  }
}
 
static dump_str()
{
  int16 k;
 
  seqo_len=0;
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
    seqo_flush();
  }
}
 
static seqo_flush()
{
  if(seqo_len){
    fasseqo(80,SeqiMode,seqo_len+4);
    seqo_pos+=seqo_len;
    *l(80,1)=seqo_pos;
    seqo_len=0;
  }
}

// #include "DRK024015.c"
#endif

#if FACT_RISTOURNO & FLAG248 // automatische facturatie van de semestriele kortingen a.h.v. historieken
ovlcod()
{
  int16 curs=1,j,k,z,key,kmode_,mode16_,yy,mm,dd;
	uint16 krec_;
  flag first=YES;
	char HerberekenSemKorting='N',ftxt_[50];
	double tot_korting_,bd_semkorting_;

  initload();
redo_full:;
  ft_date=*u(25,2);upd_mode=NO;chk_nr=YES;
	ft_init(YES);

  FOREVER{
    redo:
    scrget(2,325);z=1;fasunlck(-1);scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0240B");
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dt_bon_beg);
    scrifld(z++,fm_udat,&dt_bon_end);
  	scrfld(z++,2,3);
		scrifld(z++,fm_us1_U,&ft_tijdstp);
		scrifld(z++,fm_u_JN,&HerberekenSemKorting);
    key=scrupd(curs,0x4E1);curs=1;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5050) goto redo; // link help 
    if(key==101) ovl_exit(218);
    if(key==111) ovl_exit(0);
    if(dt_bon_beg==0){errnum=34;curs=2;goto redo;} 
    if(dt_bon_end<dt_bon_beg){errnum=36;curs=3;goto redo;}
    if(*s(2,3)){
      if(search(2,0)){curs=4;goto redo;}
    } else fasinit(2);
		inq_klt=*u(2,1);
		if(ft_tijdstp=='\0' && inq_klt==0){errnum=38;curs=4;goto redo;}
		if(key==108) break;
	}
	zero(ftxt_,sizeof ftxt_);copy("*periode ",ftxt_,9);k=9;
  jddate(dt_bon_beg,&yy,&mm,&dd);yy%=100;
  stcli_d(&ftxt_[k],(long)dd,2,0);ftxt_[k+2]='/';k+=3;
  stcli_d(&ftxt_[k],(long)mm,2,0);ftxt_[k+2]='/';k+=3;
  stcli_d(&ftxt_[k],(long)yy,2,0);k+=2;
  copy(" - ",&ftxt_[k],3);k+=3;
  jddate(dt_bon_end,&yy,&mm,&dd);yy%=100;
  stcli_d(&ftxt_[k],(long)dd,2,0);ftxt_[k+2]='/';k+=3;
  stcli_d(&ftxt_[k],(long)mm,2,0);ftxt_[k+2]='/';k+=3;
  stcli_d(&ftxt_[k],(long)yy,2,0);
  
	scrget(1,6);scrupd(-3,0);
	fasinit(2); if(inq_klt) {*u(2,1)=inq_klt;fasgeti(2);} chk_nr=YES; kmode_=1;first=YES;
	krec_=*u(2,1);
	FOREVER{
		if(krec_){fasinit(2);*u(2,1)=krec_;fasgeti(2);}
		next2:;
		if(faskeyi(2,2,kmode_)) break; kmode_=2;
		krec_=*u(2,1);
		if(inq_klt && *u(2,1)!=inq_klt) break;
		if(ft_tijdstp && ft_tijdstp!=*s(2,55)) goto next2;
		ft_init(NO);init58(0,NO);
		ram2stu(0);	copy("*Afrekening periodieke korting",s(58,16),fldlen(58,16)); stu2ram(0);
		ram2stu(1);	copy(ftxt_,s(58,16),fldlen(58,16)); stu2ram(1);
		ram2stu(2);	copy("*",s(58,16),1); stu2ram(2);
		fasinit(16); 
		*l(16,10)=krec_;mode16_=1; tot_korting_=0;
		FOREVER{
			next16:;
			if(faskeyi(16,11,mode16_)) break; mode16_=2;
			if(*l(16,10)!=krec_) break;
			if(*u(16,3) <dt_bon_beg) {*u(16,3)=dt_bon_beg;mode16_=1; goto next16;}
			if(*u(16,3) >dt_bon_end) {*u(16,3)=0xFFFF; mode16_=2;goto next16;}
			if(fldlen(16,15) && *l(16,15)) goto next16;/* geen leveranciers */
			if(*d(16,31)==0) goto next16; // gratis artikel
			fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
	 		if(HerberekenSemKorting=='J'){
				CalcSemKorting();
				if(*d(16,31)==0) {hl_semkort=0.,calc_sem=0.,brij_tpct=0.,brij_tbd=0.;}
				bd_semkorting_=(*d(16,31)-(*d(16,30)* *f(16,27))) * calc_sem/100.;  // netto ex acc en dan korting
				bd_semkorting_+=*d(16,30)*hl_semkort;
			}
			else {
				bd_semkorting_=*d(16,34);
			}
			if(bd_semkorting_==0) goto next16;
			for(k=0;k<max_line;k++){
				ram2stu(k);
				if(*u(58,14)==*u(6,1) || *s(58,16)=='\0') break;
			}
			if(k<max_line-5){
				*u(58,14)=*u(6,1);
				copy(s(6,2),s(58,15),fldlen(58,15));
				*s(58,16)='*'; copy(s(6,3),s(58,16)+1,fldlen(58,16)-1);
				*f(58,24)=*f(6,28);
				*f(58,7)+=*d(16,30); 
				*f(58,53)+=bd_semkorting_; tot_korting_+=bd_semkorting_;
				*f(58,21)=0; if(fldlen(58,43)) *f(58,43)=0;
#ifdef KN_GRBEXT
				if(fldlen(58,25)) *s(58,25)=KN_GRBEXT;
#else
				if(fldlen(58,25)) *s(58,25)='9';
#endif
				stu2ram(k);
			}
		}
		if(tot_korting_==0) goto next2;
		for(k=0;k<max_line;k++){
			ram2stu(k);
			if(*u(58,14)){
				if(*f(58,7)) *f(58,20)-=*f(58,53)/ *f(58,7);
				stu2ram(k);
			}
		}
    sysget(last_vfa,2,&last_vf);
    ft_nr=last_vf+1;
    if(first){
//	    if(!facturatie()) goto endsr;
	    first=NO;
    }
    prt2pdf=0;keepdata=YES;
  	if(exec()) {last_vf=ft_nr;}
//    else break;
    if(free<0) goto endsr;
  }
	goto redo_full;
  endsr:;
  ovlexit(-1);
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
#if !FLAGABT // bij ABT is hl-korting steeds per bak en niet per hl
			hl_semkort=hl_semkort* *f(6,37)/100;
#endif
		}
	}
}
#endif


#if FLAG252/* toerlijsten */
ovlcod()
{
  int16 curs,j,k,key,z,alarm_=YES,len_63_3;
  char list_[5],*pdum_;
  uint16 rec_,z_list_;

  initload();
  ft_date=*u(25,2);upd_mode=YES;chk_nr=YES;InqBonNr=0; InqMaggefactureerd='\0';

  fasinit(58); if(faskeyi(58,2,2)) alarm_=NO; inq_lev=0; inq_art=0;nr_beg=0;nr_end=0;inq_klt=0;
  zero((char *)&sel_toer[0],sizeof sel_toer); zero(&inq_eenheid[0][0],sizeof inq_eenheid);
	zero(inq_magaz,sizeof inq_magaz);
	zero(sel_bonref,sizeof sel_bonref);zero(sel_exclude_bonref,sizeof sel_exclude_bonref);
  for(k=0;k<5;k++) list_[k]='N'; new_date=0; fasinit(63);fasinit(1);fasinit(6);fasinit(2);
	dt_bon_beg=*u(26,2); dt_bon_end=*u(26,3);
/*  if(dt_bon_end==0) dt_bon_end=*u(25,2);*/ curs=1;
  fasinit(63);zeroL(ram,ram_size);  fieldspc(63,3,&pdum_,fmt); len_63_3=fldlen(63,3);
  FOREVER{
    redo:
    scrnum=0;scrget(2,137);z=1;fasunlck(-1); scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dt_bon_beg);
    scrifld(z++,fm_udat,&dt_bon_end);
#if FLAGNLT
    for(k=0;k<3;k++) scrifld(z++,fmt,ram+len_63_3*k);
    scraddf(70,7,4,0); scrifld(70,VarTextFmt(34,0),"Selectie grootboekextentie (0/1) :");
		z++;
    scrifld(z++,fm_us_09,&SelExt);
#else
    for(k=0;k<5;k++) scrifld(z++,fmt,ram+len_63_3*k);
#endif
/*  scrfld(z++,63,3); */
	scrfld(z++,2,3);
    scrifld(z++,fm_uu5,&nr_beg);
    scrifld(z++,fm_uu5,&nr_end);
		if(fldlen(8,30)) scrifld(z++,fm_u_JN_,&InqMaggefactureerd); else z++;
    scrfld(z++,1,3);
		scrifld(z++,fm_uu2,&inq_grp);
    scrfld(z++,6,3);
		for(k=0;k<3;k++) scrifld(z++,fm_us3U,inq_eenheid[k]);
		fmt_get(6,29); scrifld(z++,fmt,inq_magaz);
		scrifld(z++,fm_us20,sel_bonref);
		scrifld(z++,fm_us20,sel_exclude_bonref);
    z_list_=z;
    for(k=1;k<4;k++){
			scrifld(z++,fm_u_JN,&list_[k]);
#if BONLIST2XLS
			if(k==2) scraddpicto(2,z-1,2,0,2,1,573,0,0,"Lijst bons in excel"); 
#endif
		}
    scrifld(z++,fm_u_JN,&list_[0]);
    scrifld(z++,fm_udat,&new_date);
    if(alarm_) scrifld(z++,fm_u_JN,&list_[4]);
    key=scrupd(curs,0x4E1);curs=1;
    if ((key/0x100)==1) key=(key&0xFF)+5000;
    prt2pdf=NO;if(key==5001){prt2pdf=YES;key=108;}
    if(key==101) ovl_exit(218);
    if(key==111) ovl_exit(0);
/*  if(dt_bon_beg==0){errnum=34;curs=2;goto redo;} */
    if(dt_bon_end==0){errnum=34;curs=3;goto redo;}
    for(k=0;k<5;k++){
      fasinit(63);copy(ram+len_63_3*k,s(63,3),len_63_3);
      if(*s(63,3)){
				if(search(63,0)){curs=4+k;goto redo;}
      } else fasinit(63);
      copy(s(63,3),ram+len_63_3*k,len_63_3);sel_toer[k]=*u(63,1);
    }
    if(*s(2,3)){
      if(search(2,0)){curs=9;goto redo;}
    } else fasinit(2);
    if(*s(1,3)){
      if(search(1,0)){curs=12;goto redo;}
    } else fasinit(1);
    if(*ps_6_3){
      if(search(6,0)){curs=14;goto redo;}
    } else fasinit(6);
		if(key!=5002){ 
      for(k=0;k<5;k++) if(list_[k]=='J') break;
      if(k>=5){curs=z_list_;errnum=34;goto redo;}
		}
    /* inq_toer=*u(63,1);*/ inq_lev=*u(1,1); inq_art=*u(6,1); inq_klt=*u(2,1);
    if(key==108 || key==5002){
      inq_toer=NO;for(k=0;k<5;k++) if(sel_toer[k]) inq_toer=YES;
      zero(toer_klt,sizeof toer_klt);zero(toer_qbons,sizeof toer_qbons);
			if(inq_klt){toer_klt[0]=inq_klt;break;}
			else if(inq_toer){
  			if(fldlen(8,39)==0){/* alle klanten van toer nemen */
					for(k=0;k<5;k++){
						if(sel_toer[k]==0) continue;
						fasinit(63);*u(63,1)=sel_toer[k];fasgeti(63);
						for(z=0;z< fldlen(63,10); z+=2){
							rec_=*(uint16 *)(s(63,10)+z);
							for(j=0;j<DIM_TKLT;j++) if(rec_==toer_klt[j] || toer_klt[j]==0) break;
							if(j<DIM_TKLT) toer_klt[j]=rec_;
						}
					}
				} else fill_toer();
      } else fill_toer();
      if(disp_toer(1)) ovlexit(-1);
      else break;
    }
  }
	*u(26,2)=dt_bon_beg; *u(26,3)=dt_bon_end;
	if(key==5002) list_1toer(NO,YES);
  if(list_[0]=='J') bons_1toer();
  if(list_[1]=='J') centr_1toer();
  if(list_[2]=='J') list_1toer(NO,NO);
  if(list_[3]=='J') list_1toer(YES,NO);
  if(list_[4]=='J') alarm_1toer();
  ovlexit(-1);
}



/* routines voor routelijsten */
 
static bons_1toer()
{
  int16 n,k,mode_,jj,mm,dd;
  uint16 rec_,last_8=0;

	if(prt2pdf){
		getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
    if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) ovlexit(10);
		prttext("\xD0\xCD\xD0");  prtline();
		p_pdfname("Bons",dt_bon_beg,dt_bon_end);
//		prt_string("\x1B&f1S\x1B&f0S\x1B*p+1000x*p+200Y\x1B(s1p(s20v0s3B");
		prttext("Bons "); prtifld(fm_udat,&dt_bon_beg,-1); prttext(" t.e.m. ");prtifld(fm_udat,&dt_bon_end,-1);
 //   prt_string("\x1B&f1S\x1B&f0S\x1B*p+400x*p+1500Y\x1B(s1p(s30v0s3B");
  //  /* prtfld(2,3,-1); // */ prt_string(s(2,3));
    prtline();
    prtform(0);
    prtclose();
	}


  for(n=0;n<DIM_TKLT;n++){
    rec_=toer_klt[n];*u(2,1)=rec_;
    if(fasgeti(2)==0){
      last_8=0;
      FOREVER{
				ft_init(YES);
				*u(2,1)=rec_;fasgeti(2);
				fasinit(8);
				if(last_8){*u(8,1)=last_8;fasgeti(8);}
				else {*u(8,3)=rec_;mode_=1;}
				next:
				if(faskeyi(8,1,mode_)) break; mode_=2;
				if(*u(8,3)!=rec_) break;
				if(dt_bon_end<*u(8,8)) break;
			#if BACKORDER
				if(*u(8,36)) goto next;
			#endif
				if(inq_toer && fldlen(8,39)){
					for(k=0;k<5;k++) if(sel_toer[k] && *u(8,39)==sel_toer[k]) break;
					if(k>=5) goto next;
				}
				if(nr_beg && nr_beg>*u(8,2)) goto next;
				if(nr_end && nr_end<*u(8,2)) goto next;
				if(InqMaggefactureerd && *s(8,30)!=InqMaggefactureerd) goto next;
				if(sel_bonref[0] && cmpstr0U(sel_bonref,s(8,25),20)) goto next;
				if(sel_exclude_bonref[0] && cmpstr0U(sel_exclude_bonref,s(8,25),20)==0) goto next;
				if(dt_bon_beg && dt_bon_beg>*u(8,8)) goto next;
				last_8=*u(8,1); rec_8[0]=last_8;
				if(!load_bon(NO,0)) goto next;
				rec_8[0]=*u(8,1);
				select_mnt();
				if(verv_dt==0){
					copy(s(2,13),verv_term,3); verv_term[3]='\0';
					if(cmpstr(verv_term,"E9",2)==0){ // 1-15 : 5-de volgende maand, erboven de 20-ste volgende maand
						jddate(ft_date,&jj,&mm,&dd); jj%=100;
						if(dd<=15) dd=5; else dd=20;
						mm++; if(mm>12) {mm=1; jj++;}
						verv_dt=datejd(jj,mm,dd);
					}
					else verv_dt=dateadd(ft_date,verv_term);
				}
				if(fldlen(2,40) && *s(2,40)=='J'){
					copy("Waar en echt verklaard voor de som van :",opm_foot[0],40);
				}
				for(k=0;k<4;k++) copy(s(8,65+k),opm_foot[k],fldlen(8,65+k));
				calc();
				prt_error=NO;
				ft_prt();
				if(prt_error) exit_hfdmenu();
      }
    }
  }
	if(prt2pdf){
		getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
		if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) ovlexit(10);
		//  prttext("\xD0\xCE\xD0");
			prttext("\xD0\xCC\xD0");
			prtline();
			prtform(0);
			prtclose();
	}
}

static centr_1toer()
{
  int16 z,j,k,kk,mode_,mode1_,ptoer_;
  uint16 rec_,last_58;
  char fles_r;
  float q_bak_,q_fles_,gewicht_,tot_qlv_,tot_gew_,tot_liters_,liters_;
  double bd_r, lg_r, bedrag_=0;

  prtclose();
  getsysprNew(5,form_dat,&mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,80,mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prttext("<b>Centralisatie bons<b>");
  if(inq_toer){
    prttext("<t22>");
    for(k=0;k<5;k++){
      if(sel_toer[k]){*u(63,1)=sel_toer[k];fasgeti(63);prttext(" ");prtfld(63,3,-1);}
    }
  }
  prttext("   Periode : ");
  prtifld(fm_udat,&dt_bon_beg,-1);prttext(" t.e.m. ");prtifld(fm_udat,&dt_bon_end,-1);
  prttext("<t72>");prttext("Blz.<ppp>.");
  prtbuf(1);z=1;
  prttab(z,58,15,1,-1); prttitle(z++,"Code",3);
  prttab(z,58,16,2,-1); prttitle(z++,"Omschrijving",3);
  prttab(z,58,31,2,-1); prttitle(z++,"Aantal",0x13);
  if(fldlen(58,62)){
    prttab(z,58,62,1,-1); prttitle(z++,"S",3);
  }
#if CENT_BEDR
  prttab(z,58,35,1,-1); prttitle(z++,"Bedrag",0x13);
  prttab(z,58,47,1,-1); prttitle(z++,"Leeggoed",0x13);
  prttab(z,58,24,1,-1); prttitle(z++,"BTW%",0x13);
#else
  prttab(z,6,10,1,-1); prttitle(z++,"Eh",3);
#if FLAGGRS
  prttab(z,6,37,1,-1); prttitle(z++,"Inhoud",0x13);
  prttab(z,6,68,1,-1); prttitle(z++,"ABV",0x13);
#else
  prttab(z,6,38,1,-1); prttitle(z++,"Gewicht",0x13);
#endif
#if FLAGAST // sorteren op plaats magazijn filiaal 1 Waarloos
	prttab(z,58,101,1,-1); prttitle(z++,"Mg",3);
#else
  prttab(z,6,29,1,-1); prttitle(z++,"Mg",3);
#endif
#endif
 
  prtbuf(3);
	p_pdfname("Centralisatie bons",dt_bon_beg,dt_bon_end);
  free=999;
  scrget(1,7);scrupd(-3,0);
  if(inq_klt){
	fasinit(2);*u(2,1)=inq_klt;fasgeti(2);
    prttext("<e>");prtfld(2,3,35);prtfld(2,1,-1);prttext("<e>");nextline();
    prttext("<e>");prtfld(2,4,-1);prttext("<e>");nextline();
    prttext("<e>");prtfld(2,5,-1);prttext(" "); prtfld(2,6,-1);prttext("<e>");nextline();
	nextline();
  }



  zeros((char *)&cent[0].eenh[0],sizeof cent);
  tot_qlv_=0;tot_gew_=0; tot_liters_=0;
  j=0;
  ft_init(YES); fles_r='\0';
  for(ptoer_=0;ptoer_<DIM_TKLT;ptoer_++){
    rec_=toer_klt[ptoer_];
    if(rec_==0) continue;
    fasinit(8);*u(8,3)=rec_;*u(8,8)=dt_bon_beg;mode_=1;
    FOREVER{
      next_8:;
      if(faskeyi(8,1,mode_)) break; mode_=2;
      if(*u(8,3)!=rec_) break;
      if(dt_bon_end<*u(8,8)) break;
#if BACKORDER
      if(*u(8,36)) goto next_8;
#endif
      if(inq_toer && fldlen(8,39)){
				for(k=0;k<5;k++) if(sel_toer[k] && *u(8,39)==sel_toer[k]) break;
				if(k>=5) goto next_8;
      }
      if(nr_beg && nr_beg>*u(8,2)) goto next_8;
      if(nr_end && nr_end<*u(8,2)) goto next_8;
			if(InqMaggefactureerd && *s(8,30)!=InqMaggefactureerd) goto next_8;
      if(dt_bon_beg && dt_bon_beg>*u(8,8)) goto next_8;
			if(sel_bonref[0] && cmpstr0U(sel_bonref,s(8,25),20)) goto next_8;
			if(sel_exclude_bonref[0] && cmpstr0U(sel_exclude_bonref,s(8,25),20)==0) goto next_8;
      fasinit(58);*u(58,2)=*u(8,1);mode1_=1;
      FOREVER{
				next_58:;
				if(faskeyi(58,1,mode1_)) break; mode1_=2;
				if(*u(58,2)!=*u(8,1)) break;
				if(*f(58,7)==0) goto next_58;
				if(inq_art && *u(58,14)!=inq_art) goto next_58;
				if(inq_grp && *u(58,34)!=inq_grp) goto next_58;
				if(inq_magaz[0] && cmpstr0U(inq_magaz,s(58,101),fldlen(58,101))) goto next_58;
				if(inq_eenheid[0][0] || inq_eenheid[1][0] || inq_eenheid[2][0]){ 
					for(k=0;k<3;k++) {
						if(inq_eenheid[k][0] && cmpstr(inq_eenheid[k],s(58,12),fldlen(58,12))==0) break;
					}
					if(k>=3) goto next_58;
				}
				if(inq_lev){
					fasinit(6);*u(6,1)=*u(58,14); if(*u(6,1)) fasgeti(6);
					if(inq_lev!=*u(6,7)) goto next_58;
				}
				last_58=*u(58,1);
				if(fldlen(58,62) && *s(58,62)=='P'){/* palletten in bakken drukken */
					*f(58,7)=*pf_58_31;*s(58,62)='\0';
				}
				stu2ram(j);
				rec_r=*u(58,14);aant_r=*f(58,31);if(fldlen(58,62)) fles_r=*s(58,62);
				bd_r=*pd_58_35;lg_r=*f(58,47);
				if(rec_r){
					for(kk=0;kk<j;kk++){
						ram2stu(kk);
						if(rec_r==*u(58,14) && (fldlen(58,62)==0 || fles_r==*s(58,62))){
							*f(58,7)+=aant_r; *pd_58_35+=bd_r; *f(58,47)+=lg_r;
							stu2ram(kk);
							init58(j--,NO);
							break;
						}
					}
				}
				j++;
				if(j>=max_line-1) {errnum=64;break; }/* veiligheid overflow */
				*u(58,1)=last_58;fasgeti(58);
      }
    }
  }
#if FLAGAST // sorteren op plaats magazijn filiaal 1 Waarloos
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*u(58,14)){
//      fasinit(6);*u(6,1)=*u(58,14); fasgeti(6);
			fasinit(66);*u(66,2)=*u(58,14);faskeyi(66,1,0);
      copy(s(66,20),s(58,101),fldlen(58,101));
			stu2ram(k);
    }
	}
	SortBon(101);
#else
  SortBon(0);
  if(fldlen(6,29)) sort_mag();
#endif
  scrget(1,6);scrupd(-3,0);
  if(inq_lev){
    *u(1,1)=inq_lev;fasgeti(1);prttext("<b>Leverancier : ");
    prtfld(1,3,-1);nextline();nextline();
  }

  tot_leeg=0;
  zero((char *)btw_bas,sizeof btw_bas);

  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*s(58,16)){
      fasinit(6);*u(6,1)=*u(58,14); if(*u(6,1)) fasgeti(6);
      *pf_58_31=*f(58,7);q_bak_=0;q_fles_=0; if(*f(6,31)==0) *f(6,31)=1;
      if(fldlen(58,62) && *s(58,62)=='S') q_fles_=*f(58,31); else q_bak_=*f(58,31);
      if(fldlen(6,37)){
				liters_=q_bak_* *f(6,37);
				liters_+=q_fles_ * *f(6,37)/ *f(6,31);
				*f(6,37)=liters_; tot_liters_+=liters_;
      }
      if(fldlen(6,38)){
				gewicht_=q_bak_* *f(6,38);
				gewicht_+=q_fles_ * *f(6,38)/ *f(6,31);
				*f(6,38)=gewicht_; tot_gew_+=gewicht_;
      }
			if(fldlen(58,62) && *s(58,62)=='S')  tot_qlv_+=*f(58,31)/ *f(58,63); 
      else tot_qlv_+=*f(58,31);
      for(j=0;j<20;j++){
	if(cent[j].q_bak==0 && cent[j].q_fles==0) break;
	if(cmp_str(s(6,10),cent[j].eenh,fldlen(6,10))==0) break;
      }
      if(j<20){
	copy(s(6,10),cent[j].eenh,fldlen(6,10));
	cent[j].q_bak+=q_bak_;cent[j].q_fles+=q_fles_;
      }


      j=btw_tab((BEDRAG)bedrag_);
      btw_bas[j]+=*pd_58_35;
      tot_leeg+=*f(58,47);

      for(j=1;j<=15;j++) prtinfo(j,0);nextline();
    }
    if(free<0) goto endsr;
  }
  fasinit(58);fasinit(6);
  copy("TOTAAL ==>",s(58,16),10);*f(6,38)=tot_gew_; if(fldlen(6,37)) *f(6,37)=tot_liters_;*f(58,31)=tot_qlv_;
  nextline();
  for(k=0;k<20;k++) prtinfo(k,2);nextline();nextline();nextline();
  prttext("<t10><e>Centralisatie");nextline();nextline();
  for(k=0;k<20;k++){
    if(cent[k].q_bak || cent[k].q_fles){
      prttext("<t5>");copy(cent[k].eenh,s(6,10),fldlen(6,10));prtfld(6,10,-1);
      prttext("   ");*f(58,31)=cent[k].q_bak;prtfld(58,31,-1);
      prttext("   ");*f(58,31)=cent[k].q_fles;prtfld(58,31,-1);
      nextline();
    }
  }
#if CENT_BEDR
  belastbt=0;
  for(k=0;k<BTWDIM-BTWDIV;k++){
    belastbt+=btw_bas[k];
  }
  btw_tot=0;
  for(k=0;k<BTWDIM;k++){
    btw_bd[k]=round((double)(btw_bas[k]*btw_pct[k])/100.);
    btw_tot+=btw_bd[k];
  }
  tot_leeg=round((double)tot_leeg);
  alg_tot=belastbt+btw_tot+tot_leeg;
 
  nextline();
  prttext("----------- Totalen per BTW% ------------");nextline();nextline();
  for(j=0;j<3;j++){
    for(k=0;k<BTWDIM-BTWDIV+1;k++){
      if(btw_bas[k]){
	prtblank(2);
	if(j==0){prtblank(3);prtifld(fm_uf21_,&btw_pct[k],-1);
	  prttext(" %   ");}
	else{
	  if(j==1) bedrag_=btw_bas[k];
	  if(j==2) bedrag_=btw_bd[k];
	  prtifld(fmeobd,&bedrag_,-1);prtblank(1);
	}
      }
    }
    if(j==0){
      prttext("<t59>Leeggoed:");
      bedrag_=tot_leeg;
    }
    else if(j==1){
      prttext("<t59>Goederen:");
      bedrag_=belastbt;
    }
    else{
      prttext("<t61>B.T.W.:");
      bedrag_=btw_tot;
    }
    prttext(TABT);prtifld(fmeobd,&bedrag_,-1);
    nextline();nextline();
  }
  prttext("<t60>TOTAAL :");
  prttext(TABT);prtifld(fmeobd,&alg_tot,-1);
  nextline();
#endif
  prtform(0);
  prtclose();
  endsr:;
}

static list_1toer(p_bondet,prt2xls)
int16 p_bondet,prt2xls;
{
  int16 z,j,k,kk,n,mode_,mode1_,nr_,first_,z_art_,q_kar_,dd,mm,jj,chk_artik_;
  uint16 rec_, StylFill,StylNormal,StylDate;
  double bd_btot_,bd_tot_,bd_goed_,tot_goed_,bd_akw_,tot_akw_,bon_gewicht_,tot_gewicht_;
  float q_stuks_=0,bdf_,tot_bak_,tot_fles_,qBAK_,qVAT_;
	char frfile_[100],tofile_[100],mapdivers_[50];

	chk_artik_=NO; 
	if(inq_art || inq_lev || inq_grp || inq_magaz[0]) chk_artik_=YES;
	for(k=0;k<3;k++) if(inq_eenheid[k][0]) chk_artik_=YES;
#if BONLIST2XLS
	sysget(19650,50,mapdivers_);
	if(prt2xls){
		scrget(1,7);scrupd(-3,0);
#if FLAGSHN
    jddate(dt_bon_end,&jj,&mm,&dd);
		zero(tofile_,sizeof tofile_);sprintf_s(tofile_,100,"Toerlijst %02d-%02d-%04d.xls",dd,mm,jj);
		XlsRef=XlsCreate(tofile_);
		if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsRij=1;XlsKol=1;
		XlsColumnSize(XlsRef,1,40);
		XlsColumnSize(XlsRef,2,35);
		XlsColumnSize(XlsRef,3,10);
		XlsColumnSize(XlsRef,4,30);
		XlsColumnSize(XlsRef,8,15);
		XlsColumnSize(XlsRef,9,30);
		StylFill  =XlsStyle(XlsRef,"",12,0x00,NO,NO,NO,1,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,1,0,KLEUR_WIT,1,1,0,YES,NO);
	  XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,0,XlsKol++,0,"Client",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Street",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"PostCode",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"City",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Product",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Quantity",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Weight",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Phone",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Email",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"ServiceTime",StylNormal);
		XlsRij++;XlsKol=1;
#else
		if(mapdivers_[0]=='\0'){ // indien geen map dan sturen naar werkpost
			jddate(dt_bon_end,&jj,&mm,&dd);
  		zero(tofile_,sizeof tofile_);sprintf_s(tofile_,100,"Lijst bons %02d-%02d-%04d.xls",dd,mm,jj);
		}
		else{
      zero(tofile_,sizeof tofile_);copy("BonLijst.xls",tofile_,13);
		}
		XlsRef=XlsCreate(tofile_);
		if(XlsRef<=0) {errnum=1;goto endsr;}
		XlsRij=1;XlsKol=1;
		z=0;
#if FLAGAST
		z=2;
#endif
		XlsColumnSize(XlsRef,1,40);
		XlsColumnSize(XlsRef,6+z,35);
		XlsColumnSize(XlsRef,7+z,10);
		XlsColumnSize(XlsRef,8+z,30);
		XlsColumnSize(XlsRef,9+z,40);
		XlsColumnSize(XlsRef,10+z,40);
		XlsColumnSize(XlsRef,13+z,40);
		XlsColumnSize(XlsRef,14+z,15);
		StylFill  =XlsStyle(XlsRef,"",12,0x00,NO,NO,NO,1,0,KLEUR_LICHTGROEN,1,1,0,NO,NO);
		StylNormal=XlsStyle(XlsRef,"",10,0x00,NO,NO,NO,1,0,KLEUR_WIT,1,1,0,YES,NO);
		StylDate=XlsStyle(XlsRef,"dd/mm/yyyy",10,0x00,NO,NO,NO,0,0,KLEUR_WIT,1,1,0,NO,NO);
	  XlsRij=1;XlsKol=1;
		XlsWrite(XlsRef,0,XlsKol++,0,"Klant",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"BonNr",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Datum",StylNormal);
#if FLAGAST
		XlsWrite(XlsRef,0,XlsKol++,0,"Filiaal",StylNormal);
#endif

		XlsWrite(XlsRef,0,XlsKol++,0,"Aantal VAT",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Aantal BAK",StylNormal);
#if FLAGAST
		XlsWrite(XlsRef,0,XlsKol++,0,"Totaal",StylNormal);
#endif
		XlsWrite(XlsRef,0,XlsKol++,0,"Straat",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"PostCode",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Stad",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Opmerking",StylNormal);
		XlsKol++; // opmerking 2
#if FLAGGRS
		XlsWrite(XlsRef,0,XlsKol++,0,"Totaal",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0," ",StylNormal); // winstbedrag
		XlsWrite(XlsRef,0,XlsKol++,0,"Toegang",StylNormal);
		XlsWrite(XlsRef,0,XlsKol++,0,"Laadkant",StylNormal);
#endif
		XlsRij++;XlsKol=1;
#endif
		goto no_header;

	}
#endif


  prtclose();
#if FLAGPAU
	 getsysprNew(15,form_dat,&mode,&prtnr); // op matrix printer, aparte formaat 
#else
  getsysprNew(5,form_dat,&mode,&prtnr);
#endif
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  q_kar_=96;
  if((errnum=prtopen(prtnr,form_dat,6,q_kar_,mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  if(p_bondet) prttext("<b>Laadlijst"); else prttext("<b>Lijst bons");
  if(inq_toer){
    prttext("<t22>");
    for(k=0;k<5;k++){
      if(sel_toer[k]){*u(63,1)=sel_toer[k];fasgeti(63);prttext(" ");prtfld(63,3,-1);}
    }
  }
  prttext("   Periode : ");
  prtifld(fm_udat,&dt_bon_beg,-1);prttext(" t.e.m. ");prtifld(fm_udat,&dt_bon_end,-1);
  prttext("<t72>");prttext("Blz.<ppp>.");
  prtbuf(1);z=1;
  nr_=1; if(fldlen(2,2)) nr_=2;

  prttab(z,2,nr_,1,-1); prttitle(z++,"Code",3);
	if(p_bondet){ prttab(z,2,3,1,20); prttitle(z++,"Klant",3);}
	else{
		prttab(z,2,3,1,30); prttitle(z++,"Klant",3);
// geen plaats voor   	prttab(z,2,8,1,-1); prttitle(z++,"Telefoon",3);
	}
  prttab(z,8,2,1,-1); prttitle(z++,"Bonnr",0x13);
  prttab(z,8,8,3,-1); prttitle(z++,"Datum",0x43);
	if(!p_bondet){
		prttab(z,8,11,1,-1); prttitle(z++,"Totaal",0x13);
		prttab(z,8,25,3,-1); prttitle(z++,"Referentie",3);
	}

  if(fldlen(8,50)==1){prttab(z,8,50,1,-1); prttitle(z++,"A",3);}
  if(fldlen(8,52)){prttab(z,8,52,1,-1); prttitle(z++,"V",0x13);}
#if LBONS_WINST
  prtitab(z,fmeobd,&winst_bd,1,-1); prttitle(z++,"Winst",0x13);
  prtitab(z,fm_of3_1,&winst_pc,1,-1); prttitle(z++,"W%",0x13);
#endif
  z_art_=z;
  if(p_bondet){
    prttab(z,58,31,1,-1); prttitle(z++,"Aantal",0x13);
    prttab(z,58,62,1,-1); prttitle(z++,"S",3);
    prttab(z,58,16,1,-1); prttitle(z++,"Omschrijving",3);
#if FLAGGRS || FLAGGSN
    prttab(z,58,101,1,-1); prttitle(z++,"PlMag",3);
#else 
	  prttab(z,58,15,1,-1); prttitle(z++,"Code",3);
#endif
#if LBONS_PR
    prttab(z,58,20,1,-1); prttitle(z++,"Eh.pr",0x13);
    prttab(z,58,35,1,-1); prttitle(z++,"Bedrag",0x13);
#endif
  }
  prtbuf(3);
	if(p_bondet) p_pdfname("Laadlijst",dt_bon_beg,dt_bon_end);
	else p_pdfname("Lijst bons",dt_bon_beg,dt_bon_end);
no_header:;
  free=999;
  bd_goed_=0;tot_goed_=0;bd_akw_=0;tot_akw_=0;tot_gewicht_=0; tot_bak_=0; tot_fles_=0;qBAK_=0;qVAT_=0;
  scrget(1,6);scrupd(-3,0);bd_btot_=0;bd_tot_=0; bon_gewicht_=0;tot_bak_=0; tot_fles_=0;
  j=0;
  for(n=0;n<DIM_TKLT;n++){
    rec_=toer_klt[n];
    if(rec_==0) continue;
    fasinit(8);*u(8,3)=rec_;*u(8,8)=dt_bon_beg;mode_=1;
    FOREVER{
      next_8:;
      if(faskeyi(8,1,mode_)) break; mode_=2;
      if(*u(8,3)!=rec_) break;
      if(dt_bon_end<*u(8,8)) break;
#if BACKORDER
      if(*u(8,36)) goto next_8;
#endif
      if(dt_bon_beg>*u(8,8)) goto next_8;
      if(nr_beg && nr_beg>*u(8,2)) goto next_8;
      if(nr_end && nr_end<*u(8,2)) goto next_8;
			if(InqMaggefactureerd && *s(8,30)!=InqMaggefactureerd) goto next_8;
			if(sel_bonref[0] && cmpstr0U(sel_bonref,s(8,25),20)) goto next_8;
			if(sel_exclude_bonref[0] && cmpstr0U(sel_exclude_bonref,s(8,25),20)==0) goto next_8;
      if(inq_toer && fldlen(8,39)){
				for(k=0;k<5;k++) if(sel_toer[k] && *u(8,39)==sel_toer[k]) break;
				if(k>=5) goto next_8;
      }
			if(chk_artik_){
				fasinit(58);*u(58,2)=*u(8,1);mode1_=1;
				FOREVER{
					next581_:;
					if(faskeyi(58,1,mode1_)) goto next_8; mode1_=2;
					if(*u(58,2)!=*u(8,1)) goto next_8;
					if(inq_art && *u(58,14)!=inq_art) goto next581_;
					if(inq_grp && *u(58,34)!=inq_grp) goto next581_;
					if(inq_magaz[0] && cmpstr0U(inq_magaz,s(58,101),fldlen(58,101))) goto next581_;
					if(inq_eenheid[0][0] || inq_eenheid[1][0] || inq_eenheid[2][0]){ 
						for(k=0;k<3;k++) {
							if(inq_eenheid[k][0] && cmpstr(inq_eenheid[k],s(58,12),fldlen(58,12))==0) break;
						}
						if(k>=3) goto next581_;
					}
					if(inq_lev){
						fasinit(6);*u(6,1)=*u(58,14); if(*u(6,1)) fasgeti(6);
						if(inq_lev!=*u(6,7)) goto next581_;
					}
					break;
				}
			}
      fasinit(2);*u(2,1)=*u(8,3);fasgeti(2);
      first_=YES;
#if LBONS_WINST || BONLIST2XLS
      fasinit(58);*u(58,2)=*u(8,1);mode1_=1;
      bd_goed_=0;bd_akw_=0;bon_gewicht_=0;tot_bak_=0; tot_fles_=0;qBAK_=0;qVAT_=0;
      FOREVER{
				n58_:;
				if(faskeyi(58,1,mode1_)) break; mode1_=2;
				if(*u(58,2)!=*u(8,1)) break;
				if(*f(58,7)==0 && *s(58,16)!='*') goto n58_;
				if(inq_art && *u(58,14)!=inq_art) goto n58_;
				if(inq_grp && *u(58,34)!=inq_grp) goto n58_;
				if(inq_magaz[0] && cmpstr0U(inq_magaz,s(58,101),fldlen(58,101))) goto n58_;
				if(inq_eenheid[0][0] || inq_eenheid[1][0] || inq_eenheid[2][0]){ 
					for(k=0;k<3;k++) {
						if(inq_eenheid[k][0] && cmpstr(inq_eenheid[k],s(58,12),fldlen(58,12))==0) break;
					}
					if(k>=3) goto n58_;
				}
				if(inq_lev){
					fasinit(6);*u(6,1)=*u(58,14); if(*u(6,1)) fasgeti(6);
					if(inq_lev!=*u(6,7)) goto n58_;
				}
				if(fldlen(58,12) && cmpstrU("BAK",s(58,12),3)==0) qBAK_+=*f(58,31);
				if(fldlen(58,12) && cmpstrU("VAT",s(58,12),3)==0) qVAT_+=*f(58,31);
				if(fldlen(58,13)){
					bdf_=*pf_58_31* *f(58,13);
					if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
					bon_gewicht_+=bdf_;
				}
				if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) tot_bak_+=*f(58,31)/=*f(58,63);
				else tot_bak_+=*f(58,31);
				bd_goed_+=*pd_58_35;
				bdf_=*f(58,41) * *pf_58_31;
				if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
				bd_akw_+=bdf_;
      }
      winst_bd=bd_goed_-bd_akw_;tot_goed_+=bd_goed_;tot_akw_+=bd_akw_;
      if(bd_akw_) winst_pc=winst_bd/bd_akw_*100.; else winst_pc=0;
#endif
      if(p_bondet==NO || prt2xls){

				if(prt2xls){
#if BONLIST2XLS
		      XlsKol=1;
#if FLAGSHN
          for(k=14;k<=17;k++) WriteFld2Xls(XlsRij,XlsKol++,8,k,StylNormal);
					XlsWrite(XlsRef,XlsRij,XlsKol++,0,"Colli",StylNormal);
					*f(58,20)=tot_bak_; WriteFld2Xls(XlsRij,XlsKol++,58,20,StylNormal);
					*f(58,20)=bon_gewicht_; WriteFld2Xls(XlsRij,XlsKol++,58,20,StylNormal);
		      WriteFld2Xls(XlsRij,XlsKol++,2,8,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,2,21,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,2,31,StylNormal);
#else
					WriteFld2Xls(XlsRij,XlsKol++,2,3,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,8,2,StylNormal);
					XlsWrite(XlsRef,XlsRij,XlsKol++,3,(char *)u(8,8),StylDate); // ALS DATUM DOORGEVEN   WriteFld2Xls(XlsRij,XlsKol++,8,8,StylNormal);
#if FLAGAST
					if(fldlen(8,48)){
						filiaal=*u(8,48);
						if(filiaal==99 || filiaal==0) copy("DEPOT",nm_fil,6);
						else if(filiaal>0 && filiaal<=10 && fldlen(66,11+(filiaal-1)*15) && nm_loc[filiaal-1][0]) copy(nm_loc[filiaal-1],nm_fil,6);
						else zero(nm_fil,sizeof nm_fil);
						XlsWrite(XlsRef,XlsRij,XlsKol++,0,nm_fil,StylNormal);
					}

#endif
					*f(58,20)=qVAT_; WriteFld2Xls(XlsRij,XlsKol++,58,20,StylNormal);
					*f(58,20)=qBAK_; WriteFld2Xls(XlsRij,XlsKol++,58,20,StylNormal);
#if FLAGAST
					WriteFld2Xls(XlsRij,XlsKol++,8,11,StylNormal);
#endif
          for(k=4;k<=6;k++) WriteFld2Xls(XlsRij,XlsKol++,2,k,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,8,65,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,8,66,StylNormal);
#if FLAGGRS
					WriteFld2Xls(XlsRij,XlsKol++,8,11,StylNormal);
					*f(58,20)=winst_bd; WriteFld2Xls(XlsRij,XlsKol++,58,20,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,2,70,StylNormal);
					WriteFld2Xls(XlsRij,XlsKol++,2,71,StylNormal);
#endif
#endif
					XlsRij++;
#endif
					goto next_8;
				}
				else{
				  for(j=1;j<z_art_;j++) prtinfo(j,0);
				}
				first_=NO;
      }
      else {
				zero((char *)&cent[0].eenh[0],sizeof cent);bd_btot_=0;bon_gewicht_=0;tot_bak_=0; tot_fles_=0;
				fasinit(58);*u(58,2)=*u(8,1);mode1_=1;
				FOREVER{
					next_58:;
					if(faskeyi(58,1,mode1_)) break; mode1_=2;
					if(*u(58,2)!=*u(8,1)) break;
					if(*f(58,7)==0 && *s(58,16)!='*') goto next_58;
					if(inq_art && *u(58,14)!=inq_art) goto next_58;
					if(inq_grp && *u(58,34)!=inq_grp) goto next_58;
					if(inq_magaz[0] && cmpstr0U(inq_magaz,s(58,101),fldlen(58,101))) goto next_58;
					if(inq_eenheid[0][0] || inq_eenheid[1][0] || inq_eenheid[2][0]){ 
						for(k=0;k<3;k++) {
							if(inq_eenheid[k][0] && cmpstr(inq_eenheid[k],s(58,12),fldlen(58,12))==0) break;
						}
						if(k>=3) goto next_58;
					}
					if(inq_lev){
						fasinit(6);*u(6,1)=*u(58,14); if(*u(6,1)) fasgeti(6);
						if(inq_lev!=*u(6,7)) goto next_58;
					}
					if(first_){
						for(j=1;j<z_art_;j++) prtinfo(j,0);
						first_=NO;
					}
					if(fldlen(58,12)){
						for(j=0;j<20;j++){
							if(cent[j].q_bak==0 && cent[j].q_fles==0) break;
							if(cmpstr(s(58,12),cent[j].eenh,fldlen(58,12))==0) break;
						}
						if(j<20){
							copy(s(58,12),cent[j].eenh,fldlen(58,12));
							if(fldlen(58,62) && *s(58,62)=='S') cent[j].q_fles+=*pf_58_31;
							else cent[j].q_bak+=*pf_58_31;
						}
						if(*i(58,34)<99){
							if(fldlen(58,62) && *s(58,62)=='S') tot_fles_+=*pf_58_31;
							else tot_bak_+=*pf_58_31;
						}
					}
					if(fldlen(58,13)){
						bdf_=*pf_58_31* *f(58,13);
						if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
						bon_gewicht_+=bdf_;
					}
					bd_btot_+=*pd_58_35;
					for(j=z_art_;j<20;j++) prtinfo(j,0);nextline();
					if(inq_art) q_stuks_+=*pf_58_31;
				}
#if FLAGDKR
				if(*s(2,65)){
					nextline();prtfld(2,65,-1); nextline();nextline();
				}
#endif
	j=0; k=0; if(inq_art) k=5;/* niet bij 1 artikel */
	for(k;k<5;k++){
	  if(cent[k].q_bak || cent[k].q_fles) {
	    if(j==0){prttext("    Totaal ");}
	    else prttext(", ");
	    j++;
	    prtifld(fm_os3,cent[k].eenh,-1);prttext(":");
	    prtifld(fm_of40_,&cent[k].q_bak,-1);
	    if(cent[k].q_fles){
	      prttext("/");
	      prtifld(fm_of40_,&cent[k].q_fles,-1);
	    }
	  }
	}
	if(inq_art==0 && (tot_bak_ || tot_fles_)){
		j=1;
		prttext("  TOTAAL:"); 	prtifld(fm_of40_,&tot_bak_,-1);
	  if(tot_fles_){prttext("/"); prtifld(fm_of40_,&tot_fles_,-1);}
	}
#if LBONS_PR
	if(j){*pd_58_35=bd_btot_;prttext("<t78b>Goederen :");prtfld(58,35,-1);}
	bd_tot_+=bd_btot_;
#endif
	if(j) nextline();
	if(fldlen(58,13) && bon_gewicht_){
		prttext("    Totaal gewicht:"); prtifld(fm_od5_2,&bon_gewicht_,-1); nextline();
		tot_gewicht_+=bon_gewicht_;
	}
	if(p_bondet && fldlen(8,25) && *s(8,25)){
		prttext("    Referentie: "); prtfld(8,25,-1);nextline();
	}
	if(inq_art==0 && first_==NO) {for(j=0;j<9;j++) prttext("----------");nextline();}
      }
      if(first_==NO) nextline();
    }
  }
#if BONLIST2XLS
	if(prt2xls){
		if(mapdivers_[0]=='\0') SpoolFileNr=XlsClose(XlsRef,1); // indien niet ingevuld, dan naar post sturen 
		else{
			SpoolFileNr=XlsClose(XlsRef,2);
			sprintf_s(frfile_,100,"..\\Spool\\Files\\%08X-%03d-$BonLijst.xls",SpoolFileNr,procid); // dit is de gewenste naam		
			sprintf_s(tofile_,100,"%sBonLijst.xls",mapdivers_); // dit is de gewenste naam		
			for(k=0;k<50;k++){
				if(FileExist(frfile_)){
					if(CopyMoveFile(frfile_,tofile_,0)) break;
				}
			}
		}
		//if(mapdivers_[0]=='\0') XlsClose(XlsRef,1); // indien geen map dan sturen naar werkpost
		//else XlsClose(XlsRef,2);
		goto endsr;
	}
#endif
  if(inq_art && q_stuks_) {
    nextline();
    prttext("Totaal stuks : ");prtifld(fm_of6_0,&q_stuks_,-1);
#if LBONS_PR
    *pd_58_35=bd_tot_;prttext("<t78b>Goederen :");prtfld(58,35,-1);
#endif
    nextline();
  }
#if LBONS_WINST
  fasinit(2);fasinit(8);copy("Totaal -->",s(2,3),15);
  winst_bd=tot_goed_-tot_akw_;
  if(tot_akw_) winst_pc=winst_bd/tot_akw_*100.; else winst_pc=0;
  for(j=1;j<z_art_;j++) prtinfo(j,2);nextline();
#endif
	if(fldlen(58,13) && tot_gewicht_){
		prttext("Totaal gewicht:"); prtifld(fm_od5_2,&tot_gewicht_,-1); nextline();
		tot_gewicht_+=bon_gewicht_;
	}
  prtform(0);
  prtclose();
  endsr:;
}
 
static alarm_1toer()
{
  int16 z,k,mode_;
  float qlv_,cstock_;

  prtclose();
  getsysprNew(5,form_dat,&mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,80,mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prttext("<b>Stock-tekorten op bons");
  if(inq_toer){
    prttext("<t25>");
    for(k=0;k<5;k++){
      if(sel_toer[k]){*u(63,1)=sel_toer[k];fasgeti(63);prttext(" ");prtfld(63,3,-1);}
    }
  }
  prttext("   Periode : ");
  prtifld(fm_udat,&dt_bon_beg,-1);prttext(" t.e.m. ");prtifld(fm_udat,&dt_bon_end,-1);
  prttext("<t72>");prttext("Blz.<ppp>.");
  prtbuf(1);z=1;
  prttab(z,2,klcd+1,2,-1); prttitle(z++,"Code",3);
  prttab(z,2,3,2,30); prttitle(z++,"Naam",3);
  prttab(z,8,2,2,-1); prttitle(z++,"Bonnr",0x13);
  prttab(z,8,8,2,-1); prttitle(z++,"Datum",0x43);
  prttab(z,58,31,2,-1); prttitle(z++,"Aantal",0x13);
  if(fldlen(58,62)){
    prttab(z,58,62,3,-1); prttitle(z++,"S",3);
  }
  prtitab(z,fm_of6_0,&cstock_,3,-1); prttitle(z++,"Cum.stock",0x13);

  prtbuf(3);
	p_pdfname("Stock-tekorten op bons",dt_bon_beg,dt_bon_end);
  free=999;
  scrget(1,7);scrupd(-3,0);

  if(inq_lev){
    *u(1,1)=inq_lev;fasgeti(1);prttext("<b>Leverancier : ");
    prtfld(1,3,-1);nextline();nextline();
  }

  fasinit(6);
  FOREVER{
    next_art:;
    if(faskeyi(6,1,2)) break;
    if(inq_lev && inq_lev!=*u(6,7)) goto next_art;
    if(inq_art && *u(58,14)!=inq_art) goto next_art;
		if(inq_grp && *u(58,34)!=inq_grp) goto next_art;
		if(inq_magaz[0] && cmpstr0U(inq_magaz,s(58,101),fldlen(58,101))) goto next_art;
		if(inq_eenheid[0][0] || inq_eenheid[1][0] || inq_eenheid[2][0]){ 
			for(k=0;k<3;k++) {
				if(inq_eenheid[k][0] && cmpstr(inq_eenheid[k],s(58,12),fldlen(58,12))==0) break;
			}
			if(k>=3) goto next_art;
		}
    fasinit(58);*pu_58_14=*pu_6_1;mode_=1; cstock_=0;
    FOREVER{
      next58:;
      if(faskeyi(58,2,mode_)) break; mode_=2;
      if(*u(58,14)!=*u(6,1)) break;
      fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
      if(dt_bon_end<*u(8,8)) goto next58;
#if BACKORDER
      if(*u(8,36)) goto next58;
#endif
      if(nr_beg && nr_beg>*u(8,2)) goto next58;
      if(nr_end && nr_end<*u(8,2)) goto next58;
			if(InqMaggefactureerd && *s(8,30)!=InqMaggefactureerd) goto next58;
			if(sel_bonref[0] && cmpstr0U(sel_bonref,s(8,25),20)) goto next58;
			if(sel_exclude_bonref[0] && cmpstr0U(sel_exclude_bonref,s(8,25),20)==0) goto next58;
      if(inq_toer && fldlen(8,39)){
	for(k=0;k<5;k++) if(sel_toer[k] && *u(8,39)==sel_toer[k]) break;
	if(k>=5) goto next58;
      }
      if(dt_bon_beg && dt_bon_beg>*u(8,8)) goto next58;

      qlv_=*pf_58_31;
      if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)!=0) qlv_/=*f(58,63);
      cstock_+=qlv_;
    }
    if(cstock_==0 || cstock_< *f(6,33)) goto next_art;
    nextline();
    prttext("<b>");prtfld(6,2,-1); prttext("  ");prtfld(6,3,-1);
    prttext("      Stock :");prtfld(6,33,-1);nextline();
    nextline();
    fasinit(58);*u(58,14)=*u(6,1);mode_=1; cstock_=*f(6,33);
    FOREVER{
      next2:;
      if(faskeyi(58,2,mode_)) break; mode_=2;
      if(*u(58,14)!=*u(6,1)) break;
      fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
      if(dt_bon_end<*u(8,8)) goto next2;
#if BACKORDER
      if(*u(8,36)) goto next2;
#endif
      if(nr_beg && nr_beg>*u(8,2)) goto next2;
      if(nr_end && nr_end<*u(8,2)) goto next2;
			if(InqMaggefactureerd && *s(8,30)!=InqMaggefactureerd) goto next2;
			if(sel_bonref[0] && cmpstr0U(sel_bonref,s(8,25),20)) goto next2;
			if(sel_exclude_bonref[0] && cmpstr0U(sel_exclude_bonref,s(8,25),20)==0) goto next2;
      if(inq_toer && fldlen(8,39)){
	for(k=0;k<5;k++) if(sel_toer[k] && *u(8,39)==sel_toer[k]) break;
	if(k>=5) goto next2;
      }
      if(dt_bon_beg && dt_bon_beg>*u(8,8)) goto next2;
								
      fasinit(2);*u(2,1)=*u(8,3);fasgeti(2);
      qlv_=*pf_58_31;
      if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)!=0) qlv_/=*f(58,63);
      cstock_-=qlv_;
      for(k=0;k<20;k++) prtinfo(k,0);nextline();
    }
  }
  prtform(0);
  prtclose();
  endsr:;
}
 
static fill_toer()
{
  int16 g,k,used_,mode_;
 
  scrget(1,7);scrupd(-3,0);
  fasinit(8);
  FOREVER{
next:;
		if(faskeyi(8,2,2)) break;
#if BACKORDER
    if(*u(8,36)) goto next;
#endif
    if(inq_toer && fldlen(8,39)){
			for(k=0;k<5;k++) if(sel_toer[k] && *u(8,39)==sel_toer[k]) break;
			if(k>=5) goto next;
    }
    if(dt_bon_beg && *u(8,8)<dt_bon_beg) goto next;
    if(dt_bon_end && *u(8,8)>dt_bon_end) goto next;
    if(nr_beg && nr_beg>*u(8,2)) goto next;
    if(nr_end && nr_end<*u(8,2)) goto next;
		if(InqMaggefactureerd && *s(8,30)!=InqMaggefactureerd) goto next;
		if(sel_bonref[0] && cmpstr0U(sel_bonref,s(8,25),20)) goto next;
		if(sel_exclude_bonref[0] && cmpstr0U(sel_exclude_bonref,s(8,25),20)==0) goto next;
#if FLAGNLT
		if(SelExt){
			fasinit(2);*u(2,1)=*u(8,3);fasgeti(2);
			if(*s(2,25)!=SelExt) goto next;
		}
#endif
		if(inq_art || inq_grp){
			fasinit(58);*u(58,2)=*u(8,1);used_=NO;mode_=1;
			FOREVER{
				if(faskeyi(58,1,mode_)) break; mode_=2;
				if(*u(58,2)!=*u(8,1)) break;
				if(inq_grp && *u(58,34)==inq_grp) {used_=YES;break;}
				if(inq_art && *u(58,14)==inq_art){used_=YES;break;}
			}
			if(used_==NO) goto next;
		}
    for(k=0;k<DIM_TKLT;k++){
			if(toer_klt[k]==*u(8,3)) break;
    }
    if(k>=DIM_TKLT){
			for(k=0;k<DIM_TKLT;k++) if(toer_klt[k]==0) break;
    }
		if(k<DIM_TKLT) {toer_klt[k]=*u(8,3);toer_qbons[k]++;}
  }
}
 
static sort_mag()
{
  int16 k,len_,sw,max_;
  char str1[10],*ps_;
 
  len_=fldlen(6,29);ps_=s(6,29);
  max_=max_line-1;
  for(max_;max_>=0;max_--){ram2stu(max_); if(test_line()) break;}
  FOREVER{/* sorteren */
    sw=NO;
    for(k=0;k<max_;k++){
      ram2stu(k);
      fasinit(6);
      if(*ps_58_16!='*' && *pu_58_14){
				*u(6,1)=*pu_58_14; fasgeti(6);
      }
      copy(ps_,str1,len_);
      ram2stu(k+1);
      fasinit(6);
      if(*ps_58_16!='*' && *pu_58_14){
				*u(6,1)=*pu_58_14; fasgeti(6);
      }
      if(test_line()){
				if(cmp_srt(str1,ps_,len_)==1){
					ram2stu(k);
					copy(s(58,1),sortbuf,fldlen(58,0));
					ram2stu(k+1);
					stu2ram(k);
					copy(sortbuf,s(58,1),fldlen(58,0));
					stu2ram(k+1);
					sw=YES;
				}
      }
    }
    if(sw==NO) break;
  }
}

static cmpstr0U(p1,p2,len) // p1 bepaalt ook de lengte
char *p1,*p2;
int16 len;
{
  char b1,b2;
					
  while(len--){
    b1=*p1++;b2=*p2++;
		if(b1==0) break; // stoppen op 0
    if(b1>='a' && b1<='z') b1=b1-'a'+'A';
    if(b2>='a' && b2<='z') b2=b2-'a'+'A';
    if(b1!=b2)return 1;
  }
  return 0;
}

// #include "DRK024013.c"
#endif

#if FLAG241/* maken kasticket */
ovlcod()
{
  int16 j,k,key;
	uint16 tiknr_;

  initload();
  ft_date=*u(25,2); chk_nr=YES;

  FOREVER{
    ft_init(YES);prt_levbon='J';upd_mode=NO;fasunlck(-1);alg_tot=0;
    *pu_2_1=klt_div2;fasgeti(2);
    prxnr=*s(2,26)-'0';
    if(prxnr<0 || prxnr>9) prxnr=0;
    if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
    def_inc='N';if(sys3894 & (1<<prxnr)) def_inc='J';
    select_mnt(); init58(0,NO);

    redo:
    if(dsp_detail()==NO) break;
#if KASSASIMULATIE
		if((k=dsp_totTICKET())==NO) break;
#else
    if((k=dsp_tot(NO))==NO) break;
#endif
    if(k>1)goto redo;
    load_sysnr(NO);
    *u(8,2)=last_vf+1; *u(8,8)=*u(25,2);

    prt_error=NO;
    if(prt_levbon=='J') print_strook();
    if(prt_error) goto redo;
    FOREVER{
      scrget(2,28);
#if !KASSASIMULATIE
      scraddf(50,6,17,0); scrifld(50,fm_os14,"Te betalen : ");
      scraddf(51,6,30,2); scrifld(51,fm_obd,&alg_tot);
#endif
      key=scrupd(0xFFFF,0xF58);
      if(key==105) break;
      if(key==104) print_strook();
      if(key==107) goto redo;
			if(key==112) {
				if(DisplayWarning("Wenst u echt dit document te annuleren?",61,1)==YES){ClearSysPosNrCheck();return NO;}
			}
    }
    scrget(1,7);scrupd(-3,0);
    last_vf=*u(8,2); tiknr_=last_vf;
    sysput(last_vfa,2,&last_vf);/* ticketnummer wegschrijven */

    j=0;
    for(k=0;k<max_line;k++){/* lege lijnen terug schrappen */
      ram2stu(k);
      if(test_line()){/* enkel echte artikels */
	*u(58,3)=j;
	stu2ram(j++);
      }
    }
    init58(j,NO);
#if KASSASIMULATIE && TICKETAPART
		if(BdBetaaldCASH){
			fasinit(58);
			sprintf_s(s(58,16),30,"*Betaald geld : %5.2f EUR",BdBetaaldCASH);
			*u(58,3)=j;	stu2ram(j++);
		}
		if(BdBetaaldBC){
			fasinit(58);
			sprintf_s(s(58,16),30,"*Betaald BC : %5.2f EUR",BdBetaaldBC);
			*u(58,3)=j;	stu2ram(j++);
		}
#endif
    if(test_kontb(j+1)){/* indien geen bons */
      ft_init(NO);
      sysget(3718,2,&last_vf);
      *u(8,3)=*pu_2_1;*u(8,2)=last_vf+1;
				for(k=0;k<6;k++){
					copy(s(2,2+k),s(8,13+k),fldlen(8,13+k));
					if(k && fldlen(2,142+k) && *s(2,142+k)) copy(s(2,142+k),s(8,13+k),fldlen(8,13+k)); // afwijkend leveringsadres zonder codenummer
				}
      if(fldlen(8,33)){
	if(fldlen(2,35) && *s(8,33)=='\0') *s(8,33)=*s(2,35);
      }
#if SPLITS_UPNR
      last_vf++; sysput(3718,2,&last_vf);/* nummer wegschrijven */
#endif
    }
    else{
#if TICKETAPART
			ins_lin(0); fasinit(58);*s(58,16)='*';stcli_d(s(58,16)+1,(long)(tiknr_),5,1);stu2ram(0);
			j++;
			for(k=0;k<max_line;k++){
        fasinit(58);*u(58,2)=*u(8,1);*u(58,3)=k;
				if(faskeyi(58,1,0)==0){*u(58,3)=j; stu2ram(j++);}
        if(j>=max_line) break;
			}
			if(fldlen(8,21)) *f(8,21)+=BdBetaaldCASH+BdBetaaldBC;
#else
			add_kontb(j);
#endif
		}
    select_mnt();
    calc();
    write_konb();
    ClearSysPosNrCheck();
    sysflush();
  }
  ovl_exit(218);
}
#endif
 
#if KASINPUT/* facturatie van kassa-facturen */
ovlcod()
{
  int16 curs=1,key,z;
  char choice,str_[30];

  initload();
  ft_date=*u(25,2);def_inc='J'; chk_nr=YES;
  redo:;
#if BOEKKASF
  if(ask_in_dt("Inboeken facturen van kassa",YES)) goto endsr;
#else
  if(ask_in_dt("Facturatie leveringsbons kassa",YES)) goto endsr;
#endif
  zero(str_,sizeof str_); fasclos(-2);
  if(inq_kassa){
    copy("kassa-00",str_,8);stcli_d(&str_[6],(long)inq_kassa,2,0);str_[8]=0x5C;
    copy("KASFAC.DAT",&str_[9],11);
    mk_name(3936,str_);
  }
  else sysget(4572,32,filnam);
	KommaKarakter='.',FieldSeparator='|';SeqiMode=3;fasclos(-2);
  if(errnum=fasopen(filnam,3)) goto endsr;
  add_nklant();/* nieuwe klanten direct toevoegen */
#if ANAL_ASK & FLAG248 & !KASINPUT & !FT_HERAFDRUK
  if(ask_a_rek()) goto endsr;
#endif
#if BOEKKASF
  boek_kasf();
#else
  FOREVER{
    scrget(2,21);z=1;fasunlck(0);
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
    if(key==101) break;
    if(key==111) ovl_exit(0);
    switch(choice){
      case '1': ft_1_kas();break;
      case 'S': ft_ser_kas();break;
      case 'U': kil_1_kas();break;
      default : errnum=34; break;
    }
  }
#endif
  endsr:;
  fasclos(-2);
  ovl_exit(218);
}

/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* routines voor factureren van bons uit keyconenkassa */
/* versie 00.08 10/12/03 */
/* Volgende velden MOETEN bestaan : 8,22 en 2,2 */
/* Bij de klanten ook best de straatnaam in key 2 opnemen */

//static long fil_pos[50],begfpos;

#if !BOEKKASF
static ft_1_kas()
{
  stuk_per_stuk=YES;begfpos=0;
  FOREVER{
		fasunlck(-1);
    ft_init(YES);ft_nr=last_vf+1;
    redo:
    if(!ask_klt("af te printen"))break;
    if(!searc_bon(NO))goto redo;
    select_mnt();
    fill_58();
    select_mnt();
    keepdata=YES;
    if(exec()){
      kill_kas();
      last_vf=ft_nr;
    }
    fasflush(0);
  }
}

static ft_ser_kas()
{
  flag first=YES,k_fnd_,k;
  long min_kod_,max_kod_,lbd_;
  char str_[10];
  uint16 krec_;
 
	if(DisplayWarning("Wenst U echt de KASSA-bons IN SERIE te factureren?",605,1)==NO) goto endsr;
	fasunlck(-2);
  stuk_per_stuk=NO; chk_nr=YES;
  scrget(1,7);scrupd(-3,0);
#if SORT_KBON/* klanten alfabetisch */
  fasinit(2);begfpos=0;
  zero((char *)&rec_58[0],sizeof rec_58);
  searc_bon(YES);
  fasinit(2);begfpos=0; krec_=0;
  FOREVER{
    ft_init(YES);ft_nr=last_vf+1; begfpos=0;
    next_klt:;
    fasinit(2); if(krec_){*pu_2_1=krec_;fasgeti(2);}
    if(faskeyi(2,2,2)) break;
    krec_=*pu_2_1;
    for(k=0;k<DIM58;k++) if(rec_58[k]==0 || rec_58[k]==*pu_2_1) break;
    if(rec_58[k]==0 || k>=DIM58) goto next_klt;
    begfpos=0;
    if(!searc_bon(NO))goto next_klt;
    if(first){
      if(!facturatie()) break;
      first=NO;
      scrget(1,7);scrupd(-3,0);
    }
    if(fldlen(2,33)){
      if(ft_tijdstp && ft_tijdstp!=*s(2,33)) goto next_klt;
    }

    select_mnt();
    fill_58();
    select_mnt();
    keepdata=YES;prt2pdf=0;
    if(exec()){
      kill_kas();
      last_vf=ft_nr;
    }
    fasflush(0);
  }
#endif
  fasinit(2);begfpos=0;
  FOREVER{
    ft_init(YES);ft_nr=last_vf+1; k_fnd_=NO;chk_nr=YES;
    if(first){
      if(!facturatie()) break;
      first=NO;
      scrget(1,7);scrupd(-3,0);
    }
    fasinit(2);
    if(!searc_bon(NO)) break;
    k_fnd_=NO;
    if(fldlen(2,2) && *s(2,2)){/* probeer zoeken op nummer */
      if(faskeyi(2,1,0)==NO) k_fnd_=YES;
    }
    else if(*u(2,1)){
      if(fasgeti(2)==0) k_fnd_=YES;
    }
    if(k_fnd_==NO){/* probeer zoeken op naam */
      copy(s(2,1),buf1000,fldlen(2,0));
      if(faskeyi(2,2,0)){
	if(fldlen(2,2)){/* automatisch codenummer zoeken 9xxxx */
	  fasinit(2);
	  max_kod_=9;min_kod_=9; for(k=0;k<fldlen(2,2)-1;k++) {min_kod_*=10;max_kod_=max_kod_*10+9;}
	  for(lbd_=min_kod_;lbd_<max_kod_;lbd_++){
	    fasinit(2);
	    stcli_d(s(2,2),lbd_,fldlen(2,2),0);
	    if(faskeyi(2,1,0)) break;
	  }
	  stcli_d(str_,lbd_,fldlen(2,2),0);
	}
	copy(buf1000,s(2,1),fldlen(2,0));
	if(fldlen(2,2)) copy(str_,s(2,2),fldlen(2,2));
	if(fldlen(2,36)>0) *u(2,36)=def_qfact;
	// if(fldlen(2,44)>0) *s(2,44)='J';
	if(fldlen(2,25)) *s(2,25)='0';
#if FLAGEET
  if(fldlen(2,25)) *s(2,25)='1';
#endif
	*s(2,26)=sys3896[0];
	for(k=fldlen(2,3)-1;k>=0;k--){if(*(s(2,3)+k)==' ') *(s(2,3)+k)='\0'; else break;} // trailing blanks wegdoen
	if(fasadd(2)) break;/* probeer toe te voegen */
      }
    }
    select_mnt();
    fill_58();
    select_mnt();
    keepdata=YES;
    if(exec()){
      begfpos=fil_pos[0];/* tot hier zijn ze al gedaan */
      kill_kas();
      last_vf=ft_nr;
    }
    else break;
    if(free<0) break;
  }
endsr:;
	fasunlck(0);
}
 
static kil_1_kas()
{
  int16 j,k,z,key,start,mode_;
  char str_[15];
 
  stuk_per_stuk=YES;begfpos=0;
  FOREVER{
    redo:
    if(!ask_klt("te SCHRAPPEN"))break;
    if(!searc_bon(NO))goto redo;
    for(k=0;k<50;k++){
      if(fil_pos[k]<0) break;
    }
    start=0;
    FOREVER{
      scrget(2,32);z=1;
      scrofld(z++,2,3,-1);
      for(j=start;j<k;j++){
	j++;scrifld(z++,fm_ou2,&j);j--;
	fasinit(80);*pl_80_1=fil_pos[j]; mode_=0;
	FOREVER{
	  if(read_rec(mode_)) continue; mode_=2;
	  if(cmp_str(rec_ele(0),"H1",2)==NO) break;
	}
	zero(str_,sizeof str_);copy(rec_ele(1),str_,ele_len(1));
	scrifld(z++,fm_os10,str_);
	z++;
	zero(str_,sizeof str_);copy(rec_ele(2),str_,ele_len(2));
	scrifld(z++,fm_os10,str_);
	if(j==start+14) break;
      }
      j=0;scrifld(62,fm_uu2,&j);
      key=scrupd(1,0x87);
      if(key==101) {goto redo;}
      if(j>0 && j<=k) {
	j--;for(k=0;k<50;k++) if(k!=j) fil_pos[k]=-1;
	kill_kas();
	break;
      }
	
      if(key==102) start-=15;
      if(key==103) {start+=15;if(start>k-15) start=k-15;}
      if(start<0) start=0;
    }
    fasflush(0);
  }
}
#endif
 
#if BOEKKASF
static boek_kasf()
{
  int16 first=YES,k_fnd_,k,z,key;
  long min_kod_,max_kod_,lbd_;
  char str_[10];
  uint16 krec_;
  double bd_;
 
  stuk_per_stuk=NO; chk_nr=YES;
  scrget(1,7);scrupd(-3,0);
  fasinit(2);begfpos=0;
  FOREVER{
    ft_init(YES);ft_nr=last_vf+1; k_fnd_=NO;chk_nr=YES;
    fasinit(2);
    if(!searc_bon(NO)) break;
    k_fnd_=NO;
    if(fldlen(2,2) && *s(2,2)){/* probeer zoeken op nummer */
      if(faskeyi(2,1,0)==NO) k_fnd_=YES;
    }
    else if(*u(2,1)){
      if(fasgeti(2)==0) k_fnd_=YES;
    }
    if(k_fnd_==NO){/* probeer zoeken op naam */
      copy(s(2,1),buf1000,fldlen(2,0));
      if(faskeyi(2,2,0)){
	if(fldlen(2,2)){/* automatisch codenummer zoeken 9xxxx */
	  fasinit(2);
	  max_kod_=9;min_kod_=9; for(k=0;k<fldlen(2,2)-1;k++) {min_kod_*=10;max_kod_=max_kod_*10+9;}
	  for(lbd_=min_kod_;lbd_<max_kod_;lbd_++){
	    fasinit(2);
	    stcli_d(s(2,2),lbd_,fldlen(2,2),0);
	    if(faskeyi(2,1,0)) break;
	  }
	  stcli_d(str_,lbd_,fldlen(2,2),0);
	}
	copy(buf1000,s(2,1),fldlen(2,0));
	if(fldlen(2,2)) copy(str_,s(2,2),fldlen(2,2));
	if(fldlen(2,36)>0) *u(2,36)=def_qfact;
	// if(fldlen(2,44)>0) *s(2,44)='J';
	if(fldlen(2,25)) *s(2,25)='0';
#if FLAGEET
  if(fldlen(2,25)) *s(2,25)='1';
#endif
	*s(2,26)=sys3896[0];
	if(fasadd(2)) break;/* probeer toe te voegen */
      }
    }
    select_mnt();
    fill_58();
    select_mnt();
    calc();
    keepdata=YES;
    scrnum=0;scrget(2,275);z=1;
    scrfld(z++,8,2);
    scrfld(z++,8,8);
    scrfld(z++,2,3);
    scrfld(z++,2,4);
    scrfld(z++,2,5); scrfld(z++,2,6);
    bd_=belastbt+btw_tot;scrifld(z++,fm_obd,&bd_);
    bd_=tot_leeg;scrifld(z++,fm_obd,&bd_);
    scrifld(z++,fm_obd,&alg_tot);
    errnum=0; ftchk();
    if(errnum){
      errnum=59;key=scrupd(-1,0x21);
      if(key==101) break;
      begfpos=fil_pos[0]+1;
    }
    else{
      if(exec()){
	begfpos=fil_pos[0];/* tot hier zijn ze al gedaan */
	kill_kas();
	last_vf=ft_nr;
      }
      else break;
    }
    if(free<0) break;
  }
  endsr:;
}
#endif
 
static ask_klt(ptxt)
char *ptxt;
{
  int16 key,z,curs;
				
  curs=3;
/*  fasinit(2);fasinit(8); */
  redo:
  scrget(2,23);z=1;
  scrfld(z++,25,1);
  scrifld(z++,fm_os25,ptxt);
  scrfld(z++,2,3);
  scrifld(z++,fm_udat,&dt_bon_beg);
  scrifld(z++,fm_udat,&dt_bon_end);
  key=scrupd(curs,0x0481);curs=3;
  if(key==101) return NO;
  if(key==111) ovl_exit(0);
  if(search(2,0)) goto redo;
  return YES;
}
 

 
static char buf_wrk[2][30];

static cmp_cod(p1,p2,len)
char *p1,*p2;
int16 len;
{
  int16 j,k;

  zeros(buf_wrk,sizeof buf_wrk);
  for(k=0;k<len;k++) if(*p1==FieldSeparator) break; else buf_wrk[0][k]=*p1++;
  copy(p2,buf_wrk[1],len);
  for(j=0;j<2;j++){
    for(k=len-1;k>=0;k--){
      if(buf_wrk[j][k]==' ' || buf_wrk[j][k]=='\0') buf_wrk[j][k]='\0';
      else break;
    }
  }
  for(k=0;k<len;k++){
    if(buf_wrk[0][k]!=buf_wrk[1][k]) return YES;
    if(buf_wrk[0][k]=='\0') break;
  }
  return NO;
}

static kill_kas()
{
  int16 k;
  char str_[50];
						

  zero(str_,sizeof str_); fasclos(-2);
  if(inq_kassa){
    copy("kassa-00",str_,8);stcli_d(&str_[6],(long)inq_kassa,2,0);str_[8]=0x5C;
    copy("KASFAC.DAT",&str_[9],11);
    mk_name(3936,str_);
  }
  else sysget(4572,32,filnam);
	KommaKarakter='.',FieldSeparator='|';SeqiMode=3;
  if(errnum=fasopen(filnam,3)) goto endsr;

#if 0
  fasclos(-2);
  sysget(4572,32,filnm_);
  if(errnum=fasopen(filnm_,3)) goto endsr;
#endif
	fasunlck(-2);
  for(k=0;k<50;k++){
    if(fil_pos[k]>=0){
      fasinit(80);*pl_80_1=fil_pos[k];
      read_rec(0);
      *(rec_ele(0)+1)='9';
      fasseqo(80,SeqiMode,256);
    }
  }
  endsr:;
}
 
static get_btw(ps,len_)
char *ps;
int len_;
{
  int16 j,k;
  long btw_nr_;
	char str_[10];

 	j=0;btw_nr_=0;
  for(k=0;k<len_;k++) {
    if(*(ps+k)>='0' && *(ps+k)<='9'){
      btw_nr_=btw_nr_*10+*(ps+k)-'0'; j++;
    }
    if(j>=10) break;
  }
  if(j!=9 && j!=10) btw_nr_=0;
  if (btw_nr_ > 1000000000) {
		btw_nr_ -= 1000000000L;
		bcopy((char *)(&btw_nr_), str_, 4);
		str_[3] |= 0x80; bcopy(str_, (char *)(&btw_nr_), 4);
	}
	*l(2,10)=btw_nr_;
}



// #include "DRK024011.c"
#endif
 
#if KAS2FACT// facturatie van kassa-verkopen via stu 91(groot- of kleinhandel) 
ovlcod()
{
  initload();
  ft_date=*u(25,2);def_inc='J'; chk_nr=YES;
  kas2fact();
  ovl_exit(218);
}
#if KAS2GROOTH/* groothandelfacturatie van kassa-verkopen MET detail */

/*  "dr1246   00*01 04/10/00 (c) Jamadata"; */
/* routines voor het maken van factuur GROOTHANDEL aan kleinhandel */
/* de aantallen + artikels worden genomen van verkopen keyconenkassa (stu 91) */
/* op factuur komt de volledige detail van de artikels volgens stu 91 */
/* prijzen+kortingen worden genomen van de klant die men opgeeft */
/* Wanneer niet alle artikels op 1 factuur gaan, wordt automatisch een 2-de gemaakt */

static kas2fact()
{
  int16 g,k;
  uint16 gklt_;
							
  sysget(3974,2,&ft_off);
  if(ft_off && fldlen(91,11+(ft_off*5))==0) ft_off=0;
  for(max_kassa=0;max_kassa<10;max_kassa++){
    if(fldlen(91,11+(max_kassa*5))==0) break;
    if(fldlen(91,11+((max_kassa+ft_off)*5))==0) break;
  }
	if(ft_off && max_kassa>ft_off) max_kassa=ft_off; // veiligheid voor ft_offset
  fasinit(8); fasinit(2); gklt_=*pu_2_1; upd_mode=NO;chk_nr=YES;last_art=0;
  if(ask_in_dt("DETAIL-facturatie van kassa-verkopen",NO)) goto endsr;
	fasunlck(-2);
  FOREVER{
    for(k=0;k<2;k++) last_vt[k]=*u(8,19+k);
    sysget(last_vfa,2,&last_vf);
    ft_init(YES);ft_nr=last_vf+1;
    if(gklt_){*pu_2_1=gklt_;fasgeti(2);}
    for(k=0;k<2;k++) *u(8,19+k)=last_vt[k];
    g=read_91();keepdata=YES;
    last_art=*u(6,1);
    if(g==0 || g==10) break;/* niks meer gevonden */

    if(exec()==NO) break;
    last_vf=ft_nr;gklt_=*pu_2_1;
    if(g>=10) break;/* geen volgende meer */
  }
	fasunlck(-1);
  endsr:;
}

static read_91()
{
  int16 j=0,k,mode_,dd,mm,yy,end_,used_;
  float qlv_,q_st_,q_bak_,q_stuks,vw_;
									
  scrget(1,7);scrupd(-3,0);

  ram2stu(j);
  copy("*Verkopen ",ps_58_16,10);
  jddate(dt_bon_beg,&yy,&mm,&dd);
  stcli_d(ps_58_16+10,(long)dd,2,0);*(ps_58_16+12)='/';
  stcli_d(ps_58_16+13,(long)mm,2,0);
  copy("-",ps_58_16+15,1);
  jddate(dt_bon_end,&yy,&mm,&dd);
  stcli_d(ps_58_16+16,(long)dd,2,0);*(ps_58_16+18)='/';
  stcli_d(ps_58_16+19,(long)mm,2,0);
  if(last_art) copy("(vervolg)",ps_58_16+21,9);
  stu2ram(j++);
  ram2stu(j); *ps_58_16='*';stu2ram(j++);
  fasinit(6); if(last_art) {*u(6,1)=last_art;fasgeti(6);}
  end_=NO; used_=NO;
  FOREVER{
    if(faskeyi(6,1,2)) {end_=YES;break;}
    fasinit(91);*u(91,2)=*u(6,1);*u(91,3)=dt_bon_beg;mode_=1;qlv_=0;vw_=0;
    FOREVER{
      next_bew:;
      if(faskeyi(91,1,mode_)) break;mode_=2;
      if(*u(6,1)!=*u(91,2)) break;
      if(dt_bon_beg && *u(91,3)< dt_bon_beg) goto next_bew;
      if(dt_bon_end && *u(91,3)>dt_bon_end) break;
      if(inq_kassa){
				qlv_+=*f(91,11+(inq_kassa-1)*5);
				vw_+=*f(91,13+(inq_kassa-1)*5);
				if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
					qlv_+=*f(91,11+(inq_kassa-1+ft_off)*5);
					vw_+=*f(91,13+(inq_kassa-1+ft_off)*5);
				}
      }
      else{
				for(k=0;k<max_kassa;k++){
					if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue; // hoort niet bij dit filiaal
					if(fldlen(91,11+k*5)){
						qlv_+=*f(91,11+k*5);
						vw_+=*f(91,13+k*5);
					}
					if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
						qlv_+=*f(91,11+(k+ft_off)*5);
						vw_+=*f(91,13+(k+ft_off)*5);
					}
				}
      }
    }
    if(*i(6,9)==99 && *f(6,24)==0 && vw_){
      if(qlv_>0 && vw_<0) qlv_=1;/* leeggoed retour als 1 artikel */
      else vw_=vw_/qlv_;
    }
    if(qlv_){
      used_=YES;
      ram2stu(j);
      copy(s(6,2),s(58,15),len58_15);
      copy(s(6,3),ps_58_16,fldlen(58,16));
      q_st_=0; q_bak_=0; q_stuks=0;
      if(fldlen(6,31)) q_stuks=*f(6,31);
      if(q_stuks<1) q_stuks=1;
      q_bak_=(long)(qlv_); q_st_=0;
      if(q_stuks>1 && qlv_){
	q_st_=(long)(((qlv_-q_bak_)*q_stuks)+0.49);
      } else q_st_=0;
      if(*i(6,9)==99 && *f(6,24)==0 && vw_) *pf_58_20=vw_;
/* VW_ invullen om later prijs te kunnen berekenen indien 0 op artikelfiche */
      if(q_bak_){*f(58,7)=q_bak_;*f(58,41)=(vw_/qlv_)*q_bak_; stu2ram(j++);}
      if(q_st_){*f(58,7)=q_st_;*f(58,41)=vw_-*f(58,41);*s(58,62)='S';stu2ram(j++);}
      if(j>=(max_line-5)) break;
    }
  }
  endsr:;
  j=0; if(end_) j=10;
  if(used_) j++;
  return j;
}

//#include "DRK024016.c"
#else/* facturatie van kassa-verkopen zonder detail */

/*  "dr1247   00*01 04/10/00 (c) Jamadata"; */
/* routines voor maken FACTUUR van verkopen keyconenkassa */
/* versie 00.01 25/04/94 */

static kas2fact()
{
  int16 k;

  sysget(3974,2,&ft_off);
  if(ft_off && fldlen(91,11+(ft_off*5))==0) ft_off=0;
  for(max_kassa=0;max_kassa<10;max_kassa++){
    if(fldlen(91,11+(max_kassa*5))==0) break;
    if(fldlen(91,11+((max_kassa+ft_off)*5))==0) break;
  }
	if(ft_off && max_kassa>ft_off) max_kassa=ft_off; // veiligheid voor ft_offset
  fasinit(8); upd_mode=NO;chk_nr=YES;
  FOREVER{
		fasunlck(-1);
    for(k=0;k<2;k++) last_vt[k]=*u(8,19+k);
    sysget(last_vfa,2,&last_vf);
    ft_init(YES);ft_nr=last_vf+1;
    for(k=0;k<2;k++) *u(8,19+k)=last_vt[k];
    if(ask_in_dt("Facturatie van kassa-verkopen",NO)) break;
    if(inq_kassa){
      sysget(4294+(inq_kassa-1)*2,2,(char *)pu_2_1);
      if(*pu_2_1) fasgeti(2);
    }
		else if(inq_filiaal){
			for(k=0;k<10;k++) if(loc_nr[k]==inq_filiaal) break;
			if(k<10){*u(2,1)=loc_klt[k]; fasgeti(2);}
			else{
        sysget(4294+(1-1)*2,2,(char *)pu_2_1);
        if(*pu_2_1) fasgeti(2);
			}
		  if(fldlen(8,48)) *u(8,48)=inq_filiaal; 
		}
    else {/* klant van kassa 1 nemen */
      sysget(4294+(1-1)*2,2,(char *)pu_2_1);
      if(*pu_2_1) fasgeti(2);
    }
		fasunlck(-2);
    read_91();keepdata=YES;
    if(exec()==NO) break;
    last_vf=ft_nr;
  }
	fasunlck(-1);
}

static read_91()
{
  int16 k,mode,dd,mm,yy;
  float aw,vw;
  long rekenc,a_reken;
									
  scrget(1,7);scrupd(-3,0);

  ram2stu(0);
#if KAS_DOORVK/* doorverkoop naar kassa-firma */
  copy("*Verkopen van   ",ps_58_16,16);
#else
  copy("*Kassa-verkopen ",ps_58_16,16);
#endif
  jddate(dt_bon_beg,&yy,&mm,&dd);
  stcli_d(ps_58_16+16,(long)dd,2,0);*(ps_58_16+18)='/';
  stcli_d(ps_58_16+19,(long)mm,2,0);
  copy("-",ps_58_16+21,1);
  jddate(dt_bon_end,&yy,&mm,&dd);
  stcli_d(ps_58_16+22,(long)dd,2,0);*(ps_58_16+24)='/';
  stcli_d(ps_58_16+25,(long)mm,2,0);
  stu2ram(0);
  ram2stu(1); *ps_58_16='*';stu2ram(1);

  fasinit(91);*u(91,3)=dt_bon_beg;mode=1;
  FOREVER{
    next_bew:;
    if(faskeyi(91,2,mode)) break;mode=2;
    if(dt_bon_beg && *u(91,3)< dt_bon_beg) goto next_bew;
    if(dt_bon_end && *u(91,3)>dt_bon_end) break;
    fasinit(6);*u(6,1)=*u(91,2);fasgeti(6);
    if(fasgeti(6)) goto next_bew;
    aw=0;vw=0;
    if(inq_kassa){
      aw+=*f(91,12+(inq_kassa-1)*5);
      vw+=*f(91,13+(inq_kassa-1)*5);
      if(ft_off && add_ftvk=='J' && fldlen(91,11+(inq_kassa-1+ft_off)*5)){
				aw+=*f(91,12+(inq_kassa-1+ft_off)*5);
				vw+=*f(91,13+(inq_kassa-1+ft_off)*5);
      }
    }
    else{
      for(k=0;k<max_kassa;k++){
				if(nm_kassa[k][0]=='\0') continue;
				if(inq_filiaal && loc_nr[k]!=inq_filiaal) continue; // hoort niet bij dit filiaal
				if(fldlen(91,11+k*5)){
					aw+=*f(91,12+k*5);
					vw+=*f(91,13+k*5);
				}
				if(ft_off && add_ftvk=='J' && fldlen(91,11+(k+ft_off)*5)){
					aw+=*f(91,12+(k+ft_off)*5);
					vw+=*f(91,13+(k+ft_off)*5);
				}
      }
    }
    if(aw==0 && vw==0) goto next_bew;
#if (BOEKALLO & BOEKEXEC)
    fasinit(58);
    if(len58_25 && fldlen(6,39)) copy(s(6,39),ps_58_25,len58_25);
    if(fldlen(6,40) && fldlen(58,26)) *l(58,26)=*l(6,40);
    *f(58,24)=*f(6,28); *i(58,34)=*i(6,9);
    if(*i(58,34)!=99) a_reken=makegrb();
    else a_reken=*(long *)&df_rek[12][0];
#endif

    for(k=2;k<max_line;k++){
      ram2stu(k);
      if(*ps_58_16=='\0') break;
      if(fldlen(58,26) && fldlen(6,40) && *l(6,40) ){
	if(*l(6,40)==*l(58,26)) break;
      }
      else{
	if((fldlen(58,26)==0 || *l(58,26)==0) && cmp_str(s(58,25),s(6,39),fldlen(6,39))==0 && *f(58,24)==*f(6,28)){
#if (BOEKALLO & BOEKEXEC)/* controle op volledige grootboekrekening */
	  if(*i(58,34)!=99) rekenc=makegrb();
	  else rekenc=*(long *)&df_rek[12][0];
	  if(a_reken==rekenc) break;
#else
	  if((*i(58,34)!=99 && *i(6,9)!=99) || *i(58,34)==*i(6,9)) break;
#endif
	}
      }
    }
    if(k<max_line){
      if(*ps_58_16=='\0'){
	if(len58_25 && fldlen(6,39)) copy(s(6,39),ps_58_25,len58_25);
	if(fldlen(6,40) && fldlen(58,26)) *l(58,26)=*l(6,40);
	*f(58,24)=*f(6,28); *i(58,34)=*i(6,9);
#if (BOEKALLO & BOEKEXEC)
	if(*i(58,34)!=99) rekenc=makegrb();
	else rekenc=*(long *)&df_rek[12][0];
	if(sear_grb(rekenc)==60000){
	  errnum=0;
	  sear_grb(grb_notf);
	}
#endif
	if(fldlen(3,0)){
	  *s(58,16)='*';copy(s(3,3),s(58,16)+1,fldlen(3,3));
	  if(*l(3,2)==grb_notf) copy(s(6,2),s(58,16)+10,5);
	}
	else{
	  if(*i(58,34)==99) copy("*Leeggoed",s(58,16),10);
	  else{
	    copy("*Verkopen aan ",s(58,16),14);
	    stcli_d(s(58,16)+14,(long)(*f(58,24)),2,1);
	    copy(" %",s(58,16)+16,2);
	  }
	}
	*f(58,7)=1;
      }
#if KAS_DOORVK
      *f(58,20)+=aw; if(fldlen(58,27)) *s(58,27)='N';
#else
      *f(58,20)+=vw; if(fldlen(58,27)) *s(58,27)='J';
      if(fldlen(58,41) && *i(6,9)!=99){/* geen leeggoed */
	*f(58,41)+=aw;
      }
#endif
      if(*i(58,34)==99){
	*f(58,49)=1;*f(58,46)+=vw; *f(58,47)+=vw;
      }
      stu2ram(k);
    }
  }
}

// #include "DRK024014.c"
#endif
#endif

#if KAS2BON/* leveringsbon van kassa-verkopen */
ovlcod()
{
  initload();
  ft_date=*u(25,2);def_inc='J'; chk_nr=YES;
  kas_bon();
  fasclos(-2);
  ovl_exit(218);
}

/* "dr1251   00*01 10/12/03 (c) Jamadata"; */
/* routines voor maken leveringsbon van verkopen keyconenkassa */
/* versie 00.01 22/03/94 */

static struct _header {
  char versie[32];
  long lade_pos;
  int16  lade_aantal;
  int16  lade_len;
  long dag_pos;
  int16  dag_len;
  int16  dag_aantal;
  int16  dag_used;
  long rec_pos;
  long rec_len;
  long rec_aantal;
  long rec_used;
  int16 ticketnr;
} header;

static struct _dag {
  uint16 datum;
  long first_rec;
};
	
static struct s_lijn{
  char bits;/* bit 0 = stuks, 1=autoleeg */
  char code[5];
  float aantal;
  int16 groep;
  float btw;
  float prijs;
  double totaal;
};

static kas_bon()
{
  int16 k;
 
  upd_mode=NO; dt_bon_end=0;
  FOREVER{
    ft_init(YES);*u(8,2)=last_vf+1;prt_levbon=DEFLVPRT;q_paletstick=1;
    if(fldlen(8,30) && *s(8,30)=='\0') *s(8,30)=MAG_GEFACT;
    if(ask_1dag()) break;
    *u(8,8)=ft_date;
    execfil();
    SortBon(0);
    redo:
    if(dsp_detail()==NO) break;
    calc();
    if((k=dsp_tot(NO))==NO) break;
    if(k>1)goto redo;

#if PRINTEXEC
    prt_error=NO;
    if(prt_levbon=='J') ft_prt();
    if(prt_error) goto redo;
		if(prt2pdf==2) {ft_prt();_sleep(3000);MailDocument(0);prt2pdf=0;}
#endif
    scrget(1,7);scrupd(-3,0);
    if(free!=-1){
			fasunlck(-2);
#if FICHEEXEC
			fasunlck(-2);
      if(stock_JN=='J' || stock_JN=='S'){
#if STATISTIEK
	statistiek_upd();
#endif
#if ARTEXIST
	if(art_exist && stock_JN=='J') art_stat();
#endif
	if(k_omz_exist) klt_stat();
      }
#endif
      fasflush(0);
    }
    write_bon();
    last_vf=*u(8,2);
		fasunlck(-1);
  }
}

static ask_1dag()
{
  int16 z,key,curs=1;
  char *pd,filnam[30],kasnr='1';
 
  fasinit(2);
  FOREVER{
    redo:;
    scrget(2,120);z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&ft_date); scrifld(z++,fm_udat,&dt_bon_end);
    scrfld(z++,2,3);
    scrifld(z++,fm_us1,&kasnr);
    key=scrupd(curs,0x0481);
    if(key==101) return YES;
    if(key==111) ovl_exit(-1);
    if(ft_date==0) {curs=2;errnum=38;goto redo;}
    if(search(2,0)){curs=3;goto redo;}
    if(kasnr<'1' && kasnr>'9') {errnum=38;curs=4;goto redo;}
    fasclos(-2);
    pd=filnam;
    sysget(3936,16,filnam);
    while(*pd) pd++;
    copy("kaslog0",pd,7);pd+=7;
    *pd=kasnr;pd++;
    copy(".dat",pd,5);
		KommaKarakter='.',FieldSeparator='|';SeqiMode=1;
    if(fasopen(filnam,1)){curs=4;goto redo;}
    if(key==108) break;
  }
  return NO;
}

static execfil()
{
  int16 j,k;
  struct _dag *dg_1,*dg_2;

  fasinit(80);seqo_pos=0;
  scrget(1,7);scrupd(-3,0);
  fasseqi(80,1,sizeof header+4);
  copy(s(80,1)+4,&header,sizeof header);
  for(k=0;k<header.dag_used;k++){
    *l(80,1)=header.dag_pos+k*header.dag_len;
    fasseqi(80,1,header.dag_len*2+4);
    dg_1=(struct _dag *)(s(80,1)+4);dg_2=dg_1+1;
    if(k==(header.dag_used-1)) dg_2->first_rec=header.rec_used;
    if(dg_1->datum>=ft_date && dg_1->datum<=dt_bon_end){
      fill_1dg(dg_1->first_rec,dg_2->first_rec-1);
    }
  }
  fasclos(-2);
  for(j=0;j<max_line;j++){                           /* korrigeren eh_prijs */
    ram2stu(j);
    if(*f(58,7)){
      *f(58,20)=*f(58,20)/ *f(58,7);
      *f(58,46)=*f(58,46)/ *f(58,7);
      stu2ram(j);
    }
    else if(*u(58,14) && *f(58,20)==0){                /* lege lijn wegdoen */
      for(k=j+1;k<max_line;k++){ram2stu(k);stu2ram(k-1);}
      init58(max_line-1,YES);
      j--;
    }
  }
  endsr:;
}

static fill_1dg(r_beg,r_end)
long r_beg,r_end;
{
  int16 j,k,len_,via_groep,last_58=-1,g;
  char fles,last_art[10];
  long a;
  struct s_lijn *pslin;
  uint16 last_rec=0xFFFF;

  fasinit(6);len_=fldlen(6,2);if(len_>5) len_=5; copy(s(6,2),last_art,len_);
  for(a=r_beg;a<=r_end;a++){
    *l(80,1)=header.rec_pos+a*header.rec_len;
    pslin=(struct s_lijn *)(s(80,1)+4);
    fasseqi(80,1,sizeof *pslin+4);
    if(((pslin->bits & 0x80)==0) && pslin->groep>=-9 && pslin->groep<=999){
      fasinit(6); via_groep=YES;
      if(pslin->code[0]){
	copy(pslin->code,s(6,2),len_);
	if(sys4408){
	  *u(6,1)=val(s(6,2));
	  g=fasgetu(6);
	}
	else{
	  g=faskeyu(6,1,0);
	}
	if(g==0) via_groep=NO;
      }
      if(via_groep){
	if(pslin->groep>=1){                            /* verkoop op groep */
	  *s(6,2)='G';stcli_d(s(6,2)+1,(long)pslin->groep,2,0);
	}
	else{
	  copy(last_art,s(6,2),fldlen(6,2));/* korting op groep */
	}
      }
      copy(s(6,2),last_art,fldlen(6,2));
      if(faskeyu(6,1,0)==0){
	fles='\0';if((pslin->bits & 1) && *f(6,31)) fles='S';
	if(last_rec == *u(6,1) && pslin->aantal==0){
	  if(last_58>=0 && last_58<max_line){
	    ram2stu(last_58);
	    *f(58,20)+=pslin->totaal;
	    stu2ram(last_58);
	  }
	}
	else{
	  for(j=0;j<max_line;j++){
	    ram2stu(j);
	    if((*u(6,1)==*u(58,14) && *s(58,62)==fles) || *u(58,14)==0){
	      *u(58,14)=*u(6,1);
	      copy(s(6,2),s(58,15),fldlen(58,15));
	      copy(s(6,3),s(58,16),fldlen(58,16));
	      *f(58,7)+=pslin->aantal;
	      *f(58,20)+=pslin->totaal;/* tijdelijk totaal in ehpr optellen */
	      *s(58,62)=fles;
	      *s(58,27)='J';
	      *pf_58_24=*f(6,28); if(*s(8,26)=='J') *pf_58_24=0;
	      if(len58_25 && fldlen(6,39)) copy(s(6,39),ps_58_25,len58_25);
	      if(fldlen(6,40) && fldlen(58,26)) *l(58,26)=*l(6,40);
	      *i(58,34)=*i(6,9);
	      if(fldlen(6,38) && fldlen(58,13)) *f(58,13)=*f(6,38);
	      if(fldlen(58,50)){
				  if(fldlen(6,84)) *f(58,50)=*f(6,84);
				  else if(fldlen(6,37)) *f(58,50)=*f(6,37);
			  }
	      if(fldlen(58,51)) *i(58,51)=*i(6,85);
	      if(fldlen(58,54)) *f(58,54)=*f(6,83);
	      *f(58,43)=semestpc;
	      if(*i(58,34)==99){
		*u(58,48)=*u(58,14);
		*f(58,46)=*pf_58_20;
		*f(58,49)=1;
	      }
	      if(fldlen(58,63)){*f(58,63)=*f(6,31);if(*f(58,63)==0) *f(58,63)=1;}
	      if(fldlen(58,41) && *i(6,9)!=99){/* geen leeggoed */
		*f(58,41)=*f(6,18);
		if(fldlen(58,62)){
		  if(*s(58,62)=='S' && *f(58,63)!=0) *f(58,41)/=*f(58,63);
		}
	      }
	      stu2ram(j); last_58=j;
	      break;
	    }
	  }
	}
	last_rec=*u(6,1);
      }
    }
  }
}
 
		
// #include "DRK024012.c"
#endif

#if FLAG244 & !KAS2JMCBON & !KAS2BON & !SAMENVOEGEN & !PDA_LGRETOUR/* leveringsbons */
ovlcod(parmval)
int16 parmval;
{
  int16 curs=1,z;
	int key;
  char choice;

  initload();
  ft_date=*u(25,2); chk_nr=YES;
#if !WEB_ADD
	if(parmval==1){// oproepen vanuit andere ovl
		fasinit(2);*u(2,1)=*u(27,5);fasgeti(2);
		upd_bon(YES); ovlexit(-1);
	} 
#endif
#if WEB_ADD
  web_add();
#else
  FOREVER{
		redo:;
    scrget(2,22);z=1;fasunlck(0);
#if FLAGALS // parameters handlingkosten
		scraddpicto(1,0,76,22,4,2,59,0,4,"Parameters");
#endif
#if PDA_TRACEER
		AddTextKey(20,30,22,25,2,10001,"Toevoegen\ntraceergegevens",0x007FFF);
#endif
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if((key/0x10000)>0) key/=0x10000;
#if PDA_TRACEER
		if(key==10001){
      ft_date=*u(25,2);
      upd_mode=YES; chk_nr=YES;
			FOREVER{
		next_klt:;
				pbonnr=-1;
				if(disp_pbon(1)) break;
				upd_bon(NO);
			}
		  goto redo;
		}
#endif
#if FLAGALS
		if(key==5001){hk_parm();goto redo;}
#endif
    if(key==101) ovl_exit(218);
    if(key==111) ovl_exit(0);
		fasunlck(-1);
    switch(choice){
      case '1': upd_bon(NO);break;
      case '2': add_bon(0);break;
#if !FLAGEPD
      case '3': kil_bon();break;
#endif
			case '4':
#if B_LST_BON
#if FLAGVVL
				        VVL_bon_lst();
#else
								if(ovltest(252)) ovlexit(252); else bon_lst();
#endif
#else
								if(ovltest(252)) ovlexit(252);
#endif
				        break;
#if B_LST_ART
      case '5': art_lst();break;
#endif
      case 'U': kil_ALLbon();break;
      default : errnum=34; break;
    }
  }
#endif
  ovl_exit(218);
}
#endif

#if FLAGALS
static hk_parm()// parameters handlingkost
{
  int16 j,k,z,key;
									
  sysget(5350,32,(char *)&hk_omzgrb[0]);
  sysget(5382,8,(char *)&hk_kostgrb[0]);
  sysget(5390,16,(char *)&hk_pct[0][0]);
  FOREVER{
    scrget(2,500);z=1;
    for(k=0;k<2;k++) scrifld(z++,fm_uf2_2,&hk_pct[k][0]);
    for(k=0;k<2;k++) scrifld(z++,fm_uf2_2,&hk_pct[k][1]);
    for(k=0;k<2;k++) scrifld(z++,fm_ugrb,&hk_kostgrb[k]);
    for(k=0;k<8;k++) scrifld(z++,fm_ugrb,&hk_omzgrb[k]);
    key=scrupd(1,0xA1);
    if(key==106) break;
    if(key==101 || key==108){
      sysput(5350,32,(char *)&hk_omzgrb[0]);
      sysput(5382,8,(char *)&hk_kostgrb[0]);
      sysput(5390,16,(char *)&hk_pct[0][0]);
      sysflush();
      break;
    }
  }
  sysget(5350,32,(char *)&hk_omzgrb[0]);
  sysget(5382,8,(char *)&hk_kostgrb[0]);
  sysget(5390,16,(char *)&hk_pct[0][0]);
}
#endif

#if WEB_ADD // bestelsysteem All-Drinks
static struct{
  char klantnaam[50];
  char datestr[40];
} tb_mails[50];
		
static char *p_buf1000,bstPOP[40],bstADRES[40],bstPW[25];
static int16 q_mails,mailnr;
/* JMS-settings

[Klant_Specifieke_Settings]
BestelSysteemPOP=pop.em.be
BestelSysteemADRES=orderint@all-drinks.be
BestelSysteemPW=WTK864
*/


static web_add()
{
  int16 z,key;
  uint16 rec_;
 
	zero(bstPOP,sizeof bstPOP); ExecJmsCommand(bstPOP,sizeof bstPOP,"GetIniKeyValue|Klant_Specifieke_Settings|BestelSysteemPOP");
	zero(bstADRES,sizeof bstADRES); ExecJmsCommand(bstADRES,sizeof bstADRES,"GetIniKeyValue|Klant_Specifieke_Settings|BestelSysteemADRES");
	zero(bstPW,sizeof bstPW); ExecJmsCommand(bstPW,sizeof bstPW,"GetIniKeyValue|Klant_Specifieke_Settings|BestelSysteemPW");

  p_buf1000=buf1000;
  upd_mode=NO; chk_nr=YES;
  FOREVER{
    next_klt:;
    if(disp_mail()) break;
    rec_=*pu_2_1;
    sysget(last_vfa,2,&last_vf);
    ft_init(YES);
    *pu_2_1=rec_;fasgeti(2); fasinit(62);
    if(load_mail(mailnr,NO)==NO) goto next_klt;
    if(*s(62,5)) DisplayMemo(2);
    copy(s(62,5),txtbuf,300);
    *u(8,2)=last_vf+1;prt_levbon=DEFLVPRT;q_paletstick=1;
    if(exec()==NO) goto next_klt;
    write_bon(); load_mail(mailnr,YES);
    last_vf=*u(8,2);
  }
  endsr:;
}
 
static disp_mail()
{
  int16 j,k,curs=1,key,z,start_,d_lin_scr=19,curspos_;
 
	scrget(1,7);scrupd(-3,0);
  load_mlist(); if(q_mails==0) return YES;
  scrnum=0;start_=0;
  FOREVER{
    redo:
    scrnum=0;scrget(2,230);z=1;
    for(j=start_;j<(start_+d_lin_scr);j++){
      if(j>=q_mails) break;
      j++; scrifld(z++,fm_ou2,&j); j--;

      fasinit(2);copy(tb_mails[j].klantnaam,s(2,3),fldlen(2,3));// *pu_2_1=tb_mails[j].krec; fasgeti(2);
      scrfld(-z,2,3);z++;
      scrifld(z++,fm_os25,tb_mails[j].datestr);
    }
    key=scrupd(curs,0x4A7);curs=1;curspos_=fldcurs;
    if(key==101 || key==111) goto endsr;
    if(key==106){
      j=curspos_/3;j+=start_;
      if(scr_ok("Wenst U echt deze bestelling te schrappen ???")){
				load_mail(j,YES);
				load_mlist(); if(q_mails==0) return YES;
				start_=0;goto redo;
      }
    }
    if(key==108 || key==18){
      j=curspos_/3;j+=start_;
      mailnr=j; return NO;
    }
    if(key==102) start_-=d_lin_scr;
    if(key==103){
      start_+=d_lin_scr;
      if(start_>(q_mails-d_lin_scr)) start_=q_mails-d_lin_scr;
    }
    if(start_<0) start_=0;
  }
  endsr:;
  return YES;
}

static load_mail(nr_,kill_mail_)
int16 nr_,kill_mail_;
{
  int16 j,k,n,len_,mode_,bfound_,pos_opm_=0,first_,get_bak_,get_pal_,pal_used_;
  float qlv_;
	char workbuf_[5000],jcmd_[200], filnam_[200];
	
	scrget(1,7);scrupd(-3,0);
  zero(jcmd_,sizeof jcmd_);n=0;zero(workbuf_,sizeof workbuf_); zero(filnam_,sizeof filnam_); 
	n=copy0("GetMailMessage|",jcmd_,40);
	n+=copy0(bstPOP,&jcmd_[n],40);jcmd_[n++]='|';
	n+=copy0(bstADRES,&jcmd_[n],40);jcmd_[n++]='|';
	n+=copy0(bstPW,&jcmd_[n],40);
	n+=copy0("|Inbox|",&jcmd_[n],25);
	stcli_d(&jcmd_[n],(long)(nr_+1),2,1);n+=2;
	if(kill_mail_){
		n=copy0("|1",&jcmd_[n],25); 
	  ExecJmsCommand(workbuf_,sizeof workbuf_,jcmd_);
		goto endsr;
	}
	n=copy0("|0",&jcmd_[n],25); 
	ExecJmsCommand(workbuf_,sizeof workbuf_,jcmd_);
	for(k=0;k<1000;k++) if(cmpstr(&workbuf_[k],"Body:",5)==0) break;
	k+=5;	if(k>=1000) return NO;
	for(j=k;j<1000;j++) if(cmpstr(&workbuf_[j],"Body.txt",8)==0) break;
	j+=8;if(j>=1000) return NO;
	copy(&workbuf_[k],filnam_,j-k);
  fasclos(-2);if(fasopen(filnam_,1)!=0) return NO;
	p_buf1000=buf1000;

  fasinit(80);mode_=0; bfound_=NO;fasinit(2);
  FOREVER{
    next1:;
    if(read_rec(mode_)) break; mode_=1;
    if(bfound_==NO){
      if(cmpstr(p_data,"###beg###",9)==0) bfound_=YES;
      goto next1;
    }
    else {
      if(cmpstr(p_data,"###end###",9)==0) break;
      copy2buf();
      if(cmpstr(p_buf1000,"1D",2)) goto next1;
      fasinit(2);len_=ele_len(1);
      if(fldlen(2,2)){
				if(len_>fldlen(2,2)) len_=fldlen(2,2);
				copy(rec_ele(1),s(2,2),len_);
				if(faskeyi(2,1,0)) goto next1;
      }
      else {
				if(len_>fldlen(2,3)) len_=fldlen(2,3);
				copy(rec_ele(1),s(2,3),len_);
				*u(2,1)=val(s(2,3));
				if(*u(2,1)==0) goto next1;
				if(fasgeti(2)) goto next1;
      }
      break;
    }
  }
	if(*u(2,1)==0){fasclos(-2);return NO;}
	
  scrget(1,7);scrupd(-3,0);
  j=0; first_=YES;get_bak_=YES; get_pal_=YES; pal_used_=NO;
  init58(j,NO);/* om korting klant in te vullen */
  redo_load:;
  fasinit(80);mode_=0; bfound_=NO;
#if WEB_APART/* eerst bakken en dan paletten */
  if(first_){get_bak_=YES;get_pal_=NO;}
  else {get_bak_=NO;get_pal_=YES;}
#endif
 
  FOREVER{
    next2:;
    if(read_rec(mode_)) break; mode_=1;
    if(bfound_==NO){
      if(cmpstr(p_data,"###beg###",9)==0) bfound_=YES;
      goto next2;
    }
    else {
      if(cmpstr(p_data,"###end###",9)==0) break;
      copy2buf();
      if(cmp_str(rec_ele(0),"1D",2)==NO){/* nieuwe lijst */
				if(j>=max_line-3) break;
				ram2stu(j);
				len_=ele_len(4); if(len_>fldlen(58,16)-1) len_=fldlen(58,16)-1;
				*ps_58_16='*';copy(rec_ele(4),ps_58_16+1,len_);
				stu2ram(j++);keepdata=YES;
				if(first_) len_=ele_len(7); else len_=0;/* opm slechts 1 keer laden */
				if(len_>300-pos_opm_) len_=300-pos_opm_;if(len_<0) len_=0;
				copy(rec_ele(7),s(62,5)+pos_opm_,len_);pos_opm_+=len_;
      }
      if(cmp_str(rec_ele(0),"2D",2)==NO){/* artikel */
				if(j>=max_line-3) break;
				ram2stu(j);
				len_=ele_len(1); if(len_>fldlen(6,2)) len_=fldlen(6,2);
				fasinit(6);copy(rec_ele(1),s(6,2),len_);faskeyi(6,1,0);
				copy(s(6,2),ps_58_15,len58_15);
				copy(s(6,3),ps_58_16,fldlen(58,16));
				if(get_bak_){
					qlv_=get_num(2);
					if(qlv_){*f(58,7)=qlv_; stu2ram(j++);}
					if(get_num(4)) pal_used_=YES;
				}
				if(get_pal_){
					qlv_=get_num(4);
					if(qlv_){*f(58,7)=qlv_;*s(58,62)='P'; stu2ram(j++);}
				}
				keepdata=YES;

				/* fout oplossen, soms wordt de CR/LF weggelaten */
				if(ele_len(6)==0 || cmpstr(rec_ele(6),"2D",2)) goto no_fout;
				if(j>=max_line-3) break;
				ram2stu(j);
				len_=ele_len(7); if(len_>fldlen(6,2)) len_=fldlen(6,2);
				fasinit(6);copy(rec_ele(7),s(6,2),len_);faskeyi(6,1,0);
				copy(s(6,2),ps_58_15,len58_15);
				copy(s(6,3),ps_58_16,fldlen(58,16));
 
				if(get_bak_){
		  		qlv_=get_num(8);
		  		if(qlv_){*f(58,7)=qlv_; stu2ram(j++);}
	  			if(get_num(10)) pal_used_=YES;
				}
				if(get_pal_){
	  			qlv_=get_num(10);
	  			if(qlv_){*f(58,7)=qlv_;*s(58,62)='P'; stu2ram(j++);}
	  		}
	  		keepdata=YES;
	  		no_fout:;
      }
    }
  }
#if WEB_APART/* opnieuw om de paletten te adden */
  if(first_ && pal_used_) {first_=NO;goto redo_load;}
#endif
endsr:;
	fasclos(-2);
  return YES;
}

static load_mlist()
{
  int16 n,j,k,pos_;
	char workbuf_[5000],jcmd_[200];
	
  zero((char *)tb_mails,sizeof tb_mails); q_mails=0;
  zero(jcmd_,sizeof jcmd_);n=0;
	n=copy0("GetMailEnveloppes|",jcmd_,40);
	n+=copy0(bstPOP,&jcmd_[n],40);jcmd_[n++]='|';
	n+=copy0(bstADRES,&jcmd_[n],40);jcmd_[n++]='|';
	n+=copy0(bstPW,&jcmd_[n],40);
	n+=copy0("|Inbox|1|50",&jcmd_[n],25);
	zero(workbuf_,sizeof workbuf_); ExecJmsCommand(workbuf_,sizeof workbuf_,jcmd_);
	pos_=0;
	for(n=0;n<50;n++){
		p_buf1000=&workbuf_[pos_];
		if(cmp_str(rec_ele(0),"Msg:",4)==0 && ele_len(1)>4){
			copy(rec_ele(1)+5,tb_mails[q_mails].datestr,ele_len(1)-5);
			for(k=0;k<ele_len(3)-4; k++) if(cmpstr(rec_ele(3)+k,".dll",4)==0) break;
			if(k<ele_len(3)-4) copy(rec_ele(3)+k+4,tb_mails[q_mails].klantnaam,ele_len(3)-(k+4));
			q_mails++;
		}
    for(j=pos_;j<5000;j++) if(workbuf_[j]==0x0A || workbuf_[j]=='\0') break;
		if(j>=5000 || workbuf_[j]=='\0') break;
		pos_=j+1;
  }
}
 

static copy2buf()
{
  int16 j,k,end_;
							
  zero(buf1000,sizeof buf1000);j=0;
  FOREVER{
    for(k=0;k<256;k++){
      if(*(p_data+k)==0x0D || *(p_data+k)=='\0') break;
      buf1000[j++]=*(p_data+k);
      if(j>400) break;
    }
    if(j>400) break;
    if(k>0 && j>0 && *(p_buf1000+j-1)=='\\'){
      buf1000[--j]='\0';
      if(j>400) break;
      end_=NO;
      FOREVER{
	if(read_rec(1)){end_=YES; break;}
	if(*p_data!=0x0D) break;/* skip lege lijnen */
      }
      if(end_) break;
    }
    else break;
  }
}
#endif

#if PDA_BESTELLING & SCREXEC & !FT_HERAFDRUK// verkopen met PDA */
static LoadPdaBestelling()
{
  int16 key,z,k,len_,mode_,loaded_=0;
  uint16 dt_,pda_nr=0,pdad_beg=0,pdad_end=0;

  char str_[25];

  if(pdad_beg==0 && pdad_end==0){
    pdad_beg=*u(25,2);pdad_end=*u(25,2);
  }
  FOREVER{
redo:;
		scraddf(-1,0,0,0);z=1;
	  DisplayMenuTitel(4,"Inlezen bestelling van PDA",0xA);
    scraddf(z++,10,4,0); scraddf(z++,10,31,2); scraddf(z++,10,40,0); scraddf(z++,10,47,2); scraddf(z++,10,57,0);
		scraddf(z++,12,4,0); scraddf(z++,12,31,2); scraddf(z++,12,37,0); 
    scraddf(z++,23,1,8); scraddf(z++,23,12,8);
    z=1;
		scrifld(z++,VarTextFmt(27,0),"Selectie periode opnames : ");scrifld(z++,fm_udat,&pdad_beg);
		scrifld(z++,VarTextFmt(7,0),"t.e.m. ");scrifld(z++,fm_udat,&pdad_end);	scrifld(z++,VarTextFmt(46,0),"(blanco=alles)");
		scrifld(z++,VarTextFmt(27,0),"Selectie 1 specifieke PDA: ");scrifld(z++,fm_uu2,&pda_nr); scrifld(z++,VarTextFmt(46,0),"(1-10 of blanco)");
    scrifld(z++,VarTextFmt(10,0)," F1 terug "); scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
    key=scrupd(1,0x81);
		if(key==101) return 0;
		if(key==108) break;
  }

  load_BS:;
  zero(str_,sizeof str_);
  if(pda_nr){
    copy("PDA-",str_,4);stcli_d(&str_[4],(long)pda_nr,2,0);
    copy("\\moblogBS.dat",&str_[6],14);
  }
  else  copy("moblogBS.dat",&str_[0],14);
  mk_name(4410,str_);
//   mk_name(4410,"moblogBS.dat"); 
  fasclos(-2);if(fasopen(filnam,1)!=0) return NO;
	KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
  scrget(1,7);scrupd(-3,0);
  fasinit(80);mode_=0;loaded_=0;
 
  FOREVER{
    next:;
    if(read_rec(mode_)) break; mode_=1;
    if(get_num(3)==0) goto next;//  geen aantal 
    len_=ele_len(2); if(len_>fldlen(6,2)) len_=fldlen(6,2);
    if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;// begin eruit 
    fasinit(6);copy(rec_ele(2),s(6,2),len_);
    if(sys4408){
      *pu_6_1=val(s(6,2));
      if(*pu_6_1) fasgeti(6);
    }
    else faskeyi(6,1,0);
    dt_=get_date(0);
    if(pdad_beg && dt_<pdad_beg) goto next;
    if(pdad_end && dt_>pdad_end) goto next;
    //if(do_sel_lev_){
    //  if(*u(6,7)!=*u(1,1)){
				//if(GetAKFiche(*u(6,1),*u(1,1),*u(25,2))==NO) goto next;
    //  }
    //}
    for(k=0;k<max_line;k++){
      ram2stu(k);
      if(test_line()==NO) break;
    }
    if(k>=max_line-2) return NO;
		*u(58,14)=*u(6,1);
    copy(s(6,2),ps_58_15,len58_15);
    copy(s(6,3),ps_58_16,fldlen(58,16));
    *f(58,7)=get_num(3);
    if(len58_62){
      if(*rec_ele(4)=='J') *ps_58_62='S';
      else if(*rec_ele(4)=='P') *ps_58_62='P';
    }
		//if(CnvPdaAantal2LevAantal=='J' && fldlen(11,68) && *s(58,62)!='S' && *s(58,62)!='P'){
		//	if(GetAKFiche(*u(6,1),*u(1,1),*u(25,2))){
		//		if(*f(6,31)==0) *f(6,31)=1;
		//		if(*f(11,68)>0 && *f(6,31)>0 && *f(6,31)!=*f(11,68)){
		//			*f(58,7)*= *f(6,31)/ *f(11,68);// aantal in leveranciers	verpakking zetten  
		//		}
		//	}
		//}
    stu2ram(k);loaded_++;
  }
  endsr:;
  fasclos(-2);
  return loaded_;
}


#endif

#if PDA_VERKOOP & SCREXEC & !FT_HERAFDRUK// verkopen met PDA */

static uint16 GetPdaBonDate(nr);  // read date DD/MM/JJJJ starting at pos


static LoadArtikelsFromPda()
{
	int16 j,curs=1,k,n,nr_,mode_,key,len_,z,start_,d_lin_scr=15,curspos_,t_nr_;
  char str_[150],kar_;
  char choice,last_alg_[10];
	float last_aqlv_;

	redo_full:;
  zeros((char *)&pdabons[0].krec,sizeof pdabons); q_pdabons=0;
  mk_name(4410,"V*.DAT");fasclos(-2);
  fasinit(80);fasopen(filnam,102);/* eerste call voor dir */
  FOREVER {
    fasinfo(80,204);                            /* ophalen antwoord van dir */
    if (*s(80,1)=='\0') break;
    copy(s(80,1),pdabons[q_pdabons++].filename,14);
    if(q_pdabons>=50) break;
  }
	fasclos(-2);
	if(q_pdabons==0){errnum=14; return NO;}
  for(nr_=0;nr_<q_pdabons;nr_++){ // info-gegevens ophalen
		zero(str_,sizeof str_);
		pdabons[nr_].krec=pdabons[nr_].filename[1]-'0'; // verkoper
		mk_name(4410,pdabons[nr_].filename);
		KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
		fasinit(80);fasclos(-2);if(fasopen(filnam,1)!=0) continue;
		if(read_rec(0)) continue;
		len_=ele_len(0); if(len_>15) len_=15;
		copy(rec_ele(0),pdabons[nr_].datestr,len_);// datum
		len_=ele_len(1); if(len_>10) len_=10;
		copy(rec_ele(1),pdabons[nr_].timestr,len_);// uur
		fasclos(-2); 
	}
  scrnum=0;start_=0;curs=-1;
  FOREVER{
    redo:
    scrnum=0;scrget(2,371);z=1;
    for(j=start_;j<(start_+d_lin_scr);j++){
      if(j>=q_pdabons) break;
      j++; scrifld(z++,fm_ou2,&j); j--;
      kar_=pdabons[j].filename[1]+1; scrifld(z++,fm_os1,&kar_); // VxDDHHMM.dat
      scrifld(z++,fm_os10,pdabons[j].datestr);
      scrifld(z++,fm_os6,pdabons[j].timestr);
			scraddpicto(1+j-start_,z-1,9,0,2,1,514,0,0,"Artikels toevoegen"); 
			scraddpicto(16+j-start_,z-1,13,0,2,1,540,0,0,"Schrap pdabon"); 
	  }
    key=scrupd(-1,0x7);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) goto endsr;
		if(key>=5001 && key<=5015){ // voeg artikels toe
			nr_=key-5001+start_;
			if(DisplayPdaVerkoopbon(nr_)==NO) goto redo;
			mk_name(4410,pdabons[nr_].filename);
			KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
			fasclos(-2);if(fasopen(filnam,1)!=0) return NO;

			scrget(1,7);scrupd(-3,0);
			fasinit(80);mode_=0;
			for(k=max_line-1;k>=0;k--){
				ram2stu(k);
				if(test_line()) break;
			}
			k++; if(k>=max_line-2) return NO;
			ram2stu(k); copy("*",ps_58_16,8); // copy(pdabons[nr_].datestr,ps_58_16+1,15);
			if(len58_62) *ps_58_62='S';
			stu2ram(k++); last_aqlv_=0; zero(last_alg_,sizeof last_alg_);
			FOREVER{
				next:;
				if(read_rec(mode_)) break; mode_=1;
				if(get_num(2)==0) goto next;/* geen aantal */
				len_=ele_len(2); if(len_>fldlen(6,2)) len_=fldlen(6,2);
				if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;/* begin eruit */
				ram2stu(k);
				fasinit(6);copy(rec_ele(2),s(6,2),len_);
				if(sys4408){
					*pu_6_1=val(s(6,2));
					if(*pu_6_1) fasgeti(6);
				}
				else faskeyi(6,1,0);
//				fasinit(6);copy(rec_ele(2),s(6,2),len_);faskeyi(6,1,0);
				*pu_58_14=*pu_6_1;
				copy(s(6,2),ps_58_15,len58_15);
				t_nr_=taal_nr; if(*s(6,3+t_nr_)=='\0') t_nr_=0;
				copy(s(6,3+t_nr_),ps_58_16,fldlen(58,16));
				copy(s(6,3),ps_58_16,fldlen(58,16));
				*f(58,7)=get_num(3);
				if(fldlen(58,62) && *rec_ele(4)=='J') *s(58,62)='S';
				if(*i(6,9)==99 && *f(58,7)==last_aqlv_ && cmpstr(s(6,2),last_alg_,fldlen(6,2))==0){ // automatisch leeggoed 
					last_aqlv_=0; zero(last_alg_,sizeof last_alg_);
				}
				else{ // bijhouden voor automatisch leeggoed
					if(*i(6,9)!=99){ // enkel artikels, niet bij leeggoed
						last_aqlv_=*f(58,7); 
						if(*s(58,62)=='S') copy(s(6,44),last_alg_,fldlen(6,44)); 
						else copy(s(6,41),last_alg_,fldlen(6,41)); 
					}
					else{last_aqlv_=0; zero(last_alg_,sizeof last_alg_);}
				  stu2ram(k++); 
					if(k>=max_line) return NO;
				}
			}
			fasclos(-2);KillPdaVerkoopBon(nr_);
			return YES;
		}
		if(key>=5016 && key<=5030){ // delete PDAbon
			nr_=key-5016+start_;
      if(scr_ok("Wenst U echt deze pda-bon te schrappen ???")){
				KillPdaVerkoopBon(nr_);
				goto redo_full;
      }
		}

		
    if(key==102) start_-=d_lin_scr;
    if(key==103){
      start_+=d_lin_scr;
      if(start_>=q_pdabons) start_=q_pdabons-d_lin_scr;
    }
    if(start_<0) start_=0;
  }
endsr:;
	// Opkuisen directory : OK-bestanden van 15 dagen of ouder schrappen
	scrget(1,7);scrupd(-3,0);
	zeros((char *)&pdabons[0].krec,sizeof pdabons); q_pdabons=0;
  mk_name(4410,"V*.OK");
  fasclos(-2);fasinit(80);fasopen(filnam,102);/* eerste call voor dir */
  FOREVER {
    fasinfo(80,204);                            /* ophalen antwoord van dir */
    if (*s(80,1)=='\0') break;
    copy(s(80,1),pdabons[q_pdabons++].filename,14);
    if(q_pdabons>=50) break;
  }
	fasclos(-2);
	for(k=0;k<q_pdabons;k++){
		mk_name(4410,pdabons[k].filename);
		KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
		fasclos(-2);if(fasopen(filnam,1)!=0) continue;
		fasinit(80);if(read_rec(0)){fasclos(-2);continue;}
		if(GetPdaBonDate(0)<*u(25,2)-15){
			fasclos(-2);fasopen(filnam,99); // deleten
		}
	}
	fasclos(-2);
	return NO;
}

static KillPdaVerkoopBon(nr_)/* renamen naar OK */
int16 nr_;
{
  int16 n;
  char str_[100];
  
	fasunlck(-2);
  zero(str_,sizeof str_);
  mk_name(4410,pdabons[nr_].filename);
  for(n=0;n<50;n++) if(filnam[n]=='\0') break;
  if(n>3){/* OK eerst deleten */
    copy("OK",&filnam[n-3],3);
    fasclos(-2);
    fasopen(filnam,99);
  }
  mk_name(4410,pdabons[nr_].filename);
  for(n=0;n<50;n++) if(filnam[n]=='\0') break;
  copy(filnam,str_,n);str_[n]='|';
  copy(filnam,&str_[n+1],n);
  for(n=0;n<100;n++) if(str_[n]=='\0') break;
  copy("OK",&str_[n-3],3);
  fasclos(-2);
  fasopen(str_,100);
}

static DisplayPdaVerkoopbon(nr_)
int16 nr_;
{
	int mode_,pf_,lin_,z,key,len_,k;
	char str_[15];
	long fpos_[10];
	 
	mk_name(4410,pdabons[nr_].filename);
	KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
	fasclos(-2);if(fasopen(filnam,1)!=0) return NO;

	fasinit(80);mode_=0;zero(fpos_,sizeof fpos_);pf_=0;
	FOREVER{
		scrnum=0;scrget(2,372);z=1;
		fasinit(80);*l(80,1)=fpos_[pf_];mode_=0; lin_=0;
		FOREVER{
			next:;
			if(read_rec(mode_)) break; mode_=1;
			if(get_num(2)==0) goto next;/* geen aantal */
			fpos_[pf_+1]=*l(80,1);
			len_=ele_len(2); if(len_>fldlen(6,2)) len_=fldlen(6,2);
			if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;/* begin eruit */
			fasinit(6);
      len_=get_str(s(6,2),2,fldlen(6,2)); if(len_==0) goto next;
			if(sys4408){
				*pu_6_1=val(s(6,2));
				if(*pu_6_1) k=fasgeti(6); else k=1;
			}
			else k=faskeyi(6,1,0);
			zero(str_,sizeof str_);copy(rec_ele(0),str_,10); scrifld(z++,VarTextFmt(10,0),str_);
			zero(str_,sizeof str_);copy(rec_ele(1),str_,10); scrifld(z++,VarTextFmt(5,0),str_);
			scrofld(z++,6,2,-1);
			scrofld(z++,6,3,-1);
			*f(58,7)=get_num(3); scrofld(z++,58,7,-1);
			if(fldlen(58,62) && *rec_ele(4)=='J') *s(58,62)='S'; scrofld(z++,58,62,-1);
			lin_++;if(lin_>=18) break;
		}
		key=scrupd(-1,0x87);
		if(key==108) break;
		if(key==101) {fasclos(-2); return NO;}
		if(key==102 && pf_) pf_--;
		if(key==103 && lin_>=18 && pf_<9) pf_++;
	}
	fasclos(-2);
	return YES;
}



static uint16 GetPdaBonDate(nr)              /* read date DD/MM/JJJJ starting at pos  */
int16 nr;
{
  int16 k=0,getal_[3],p_getal_;
  uint16 dt_=0;
  char *pos;
									
  zero(getal_,sizeof getal_);p_getal_=0;
  dt_=0; pos=rec_ele(nr); if(ele_len(nr)==0) goto endsr;
  FOREVER{
    if(*(pos+k)=='|' || *(pos+k)==0x0D  || *(pos+k)=='\0') break;
    if(*(pos+k)=='/'){p_getal_++;if(p_getal_>2) break;}
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
	getal_[p_getal_]=getal_[p_getal_]*10 + (*(pos+k)-'0');
      }
    }
    k++;
  }
  getal_[2]%=100;
  if(getal_[0]>=1 && getal_[0]<=31 && getal_[1]>=1 && getal_[1]<=12 && getal_[2]>=0 && getal_[2]<=99) dt_=datejd(getal_[2],getal_[1],getal_[0]);
  endsr:;
  return (uint16) dt_;
}
#endif





#if FLAG244 & PDA_LGRETOUR & !KAS2BON & !SAMENVOEGEN/* retourbons PDA */
ovlcod()
{
  int16 curs=1,key,z;
  char choice;

  initload();
  ft_date=*u(25,2);
  upd_mode=YES; chk_nr=YES;
  FOREVER{
next_klt:;
		pbonnr=-1;
    if(disp_pbon(0)) break;
    upd_bon(NO);
  }
  ovlexit(-1);
}

static add_pbon()
{
  int16 k,n,len_,mode_=0,nr_;

  nr_=pbonnr;
  mk_name(4440,pdabons[nr_].filename);
	KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
  fasclos(-2);if(fasopen(filnam,1)!=0) return NO;

  scrget(1,7);scrupd(-3,0);
  fasinit(80);mode_=0;
  for(k=max_line-1;k>=0;k--){
    ram2stu(k);
    if(test_line()) break;
  }
  k++; if(k>=max_line-2) return NO;
  ram2stu(k); copy("*RETOUR ",ps_58_16,8); copy(pdabons[nr_].datestr,ps_58_16+8,15);
  if(len58_62) *ps_58_62='S';
  stu2ram(k++);
  FOREVER{
    next:;
    if(read_rec(mode_)) break; mode_=1;
    if(get_num(2)==0) goto next;/* geen aantal */
    len_=ele_len(2); if(len_>fldlen(6,2)) len_=fldlen(6,2);
    if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;/* begin eruit */
    ram2stu(k);
    fasinit(6);copy(rec_ele(2),s(6,2),len_);
		if(sys4408){*u(6,1)=val(s(6,2));	if(*u(6,1)) fasgeti(6);}
		else faskeyi(6,1,0);	
    *pu_58_14=*pu_6_1;
    copy(s(6,2),ps_58_15,len58_15);
    copy(s(6,3),ps_58_16,fldlen(58,16));
    *f(58,7)=get_num(3);
    if(fldlen(58,62) && *rec_ele(4)=='J') *s(58,62)='S';
    stu2ram(k++); if(k>=max_line) return NO;
  }
	if(pdabons[pbonnr].bd_betaald && fldlen(8,21)) *f(8,21)+=pdabons[pbonnr].bd_betaald;
  return YES;
}


#endif

#if TRACEERDATA
static int CheckTraceerData()
{
	int k,fl_leegaantal=NO;
	float aantal_=0,factor_;

	for(k=0;k<10;k++) if(fldlen(58,136+k*4) && (*u(58,137+k*4) || *s(58,138+k*4) || *s(58,139+k*4))){
		if(*f(58,136+k*4)) aantal_+=*f(58,136+k*4); else fl_leegaantal=YES;
	}
	factor_=1.; if(*f(58,31)<0) factor_=-1.;
	if(fl_leegaantal || (*f(58,7) && aantal_>=*f(58,31)*factor_)) return 4; // groen
	else if(*s(58,135)=='J') return 3; // rood
	return 0; // grijs
}


static DisplayTraceerData(nr_)
int16 nr_;
{
	int16 k,z,key,curs;

	ram2stu(nr_); 
	curs=5; if(test_line()==NO) curs=-1;
	FOREVER{
		scrnum=0;scrget(2,378);z=1;
	  scraddpicto(1,0,0,0,4,2,93,0,4,"vorig"); 
		scraddpicto(2,0,76,0,4,2,92,0,4,"volgend"); 
		nr_++;scrifld(z++,fm_ou3,&nr_); nr_--;
		scrofld(z++,58,16,-1);
		scrofld(z++,58,31,-1);
		if(*s(58,135)=='J') scrifld(z++,VarTextFmt(12,0)," VERPLICHT! "); else z++;
		for(k=0;k<10;k++){
		  scrfld(z++,58,136+k*4);
		  scrfld(z++,58,137+k*4);
		  scrfld(z++,58,138+k*4);
		  scrfld(z++,58,139+k*4);
		}
		key=scrupd(curs,0xA1);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101 || key==106) break;
		if(key==108) {stu2ram(nr_);break;}
		if(key==5001 || key==5002){
			stu2ram(nr_);
			if(key==5001 && nr_>0) nr_--;
			else if(key==5002 && nr_<max_line-1) nr_++;
			ram2stu(nr_);
			curs=5; if(test_line()==NO) curs=-1;
		}
	}
  endsr:;
}
#endif



#if FLAG244 & (PDA_LGRETOUR | PDA_TRACEER) & !KAS2BON & !SAMENVOEGEN/* retourbons PDA */
/* PDA_LGRETOUR : aanpassen bons a.h.v. leeggoed terug van PDA */
/* PDA_TRACEER : aanpassen bons a.h.v. traceerdata van PDA */
 
static disp_pbon(datatype_) // 0=retourbons , 1=traceergegevens
int16 datatype_;
{
  int16 j,n,curs=1,key,z,start_,len_,d_lin_scr=19,curspos_,lst_verwerkt_=NO;
	char str_[100];
 
  pbonnr=-1;
	load_plist(datatype_,lst_verwerkt_);// if(q_pdabons==0){errnum=14;return YES;}
  scrnum=0;start_=0;
  FOREVER{
    redo:
    scrnum=0;scrget(2,288);z=1;
	  if(lst_verwerkt_){
			if(datatype_==0){
				DisplayMenuTitel(0,"Overzicht geschrapte/verwerkte retourbons",0xB);
				scraddpicto(3,0,76,0,4,2,105,1,7,"^!B0240C"); // help 
			}
			else DisplayMenuTitel(0,"Overzicht geschrapte/verwerkte traceergegevens",0xB);
//		  scraddfield(200,(80-len_)/2,1,0xB);
		  scraddpicto(2,0,76,22,4,2,589,0,0,"Toon niet verwerkte lijst");
		  scraddpicto(4,0,72,22,4,2,133,0,3,"Schrap ALLE verwerkte lijnen");
		}
		else{
			if(datatype_==0){
				DisplayMenuTitel(0,"Overzicht nog te verwerken retourbons van PDA",0x9);
				scraddpicto(3,0,76,0,4,2,105,1,7,"^!B0240C"); // help 
			}
			else DisplayMenuTitel(0,"Overzicht nog te verwerken traceergegevens van PDA",0x9);
//		  scraddfield(200,(80-len_)/2,1,0x9);
			scraddpicto(2,0,76,22,4,2,600,0,0,"Toon verwerkte lijst");
		}
//		k=start_+1; if(k>=q_pdabons_) k=q_pdabons_; scrifld(z++,fm_ou3,&k);
//		k+=d_lin_scr_-1; if(k>=q_pdabons) k=q_pdabons; scrifld(z++,fm_ou3,&k);
    for(j=start_;j<(start_+d_lin_scr);j++){
      if(j>=q_pdabons) break;
      j++; scrifld(z++,fm_ou2,&j); j--;
			fasinit(2); *pu_2_1=pdabons[j].krec; if(*u(2,1)){fasgeti(2);}
      scrofld(z++,2,3,-1);
      scrifld(z++,fm_ou5,&pdabons[j].bonnr);
      scrifld(z++,fm_os10,pdabons[j].datestr);
      scrifld(z++,fm_os6,pdabons[j].timestr);
			if(lst_verwerkt_) scraddpicto(10+j-start_,z-1,6,0,2,1,589,0,4,"Zet in verwerk-lijst"); 
			else scraddpicto(10+j-start_,z-1,6,0,2,1,125,0,4,"Verwerk"); 
			scraddpicto(30+j-start_,z-1,9,0,2,1,133,0,3,"Schrap"); 
    }
    key=scrupd(-1,0x4A7);curs=1;curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
//		if(key==5001){ UpdateParameters();goto redo;}
		if(key==5002){
			if(lst_verwerkt_) lst_verwerkt_=NO; else lst_verwerkt_=YES;
			start_=0;key=107;
		}
		if(key==5003) goto redo; // link help 
		if(key==5004 && lst_verwerkt_){ // schrap ALLE verwerkte lijnen
			if(DisplayWarning("Wenst u echt ALLE verwerkte PDA-bons te schrappen?",605,1)==YES){
				for(j=0;j<q_pdabons;j++) kill_pbon(j);
				FOREVER{
					pbonnr=-1;
					load_plist(datatype_,lst_verwerkt_); if(q_pdabons==0) break;
					for(j=0;j<q_pdabons;j++) kill_pbon(j);
				}
 		  	key=107;
			}
		}
		if(key>=5010 && key<5010+d_lin_scr){ // boek of terugzetten
			pbonnr=key-5010+start_;
			if(lst_verwerkt_){ // terugzetten 
				mk_name(4440,pdabons[pbonnr].filename); zero(str_,sizeof str_);
				for(n=0;n<50;n++) if(filnam[n]=='\0') break;
				copy(filnam,str_,n);str_[n]='|';
				copy(filnam,&str_[n+1],n);
				for(n=0;n<100;n++) if(str_[n]=='\0') break;
				copy("DAT",&str_[n-2],4);
				fasclos(-2);
				fasopen(str_,100); // renamen naar DAT
				key=107;
			}
			else{ // boeken
  			fasinit(2);*pu_2_1=pdabons[pbonnr].krec; if(*u(2,1)) fasgeti(2);
				if(DisplayPdaTraceerData(datatype_)==YES) return NO;
        else goto redo;
			}
		}
		if(key>=5030 && key<5030+d_lin_scr){ // schrap
			if(lst_verwerkt_ || DisplayWarning("PDA-bon is nog niet verwerkt! Wenst U deze echt te schrappen?",605,1)==YES){
  			j=key-5030+start_;
	      kill_pbon(j);
		  	key=107;
			}
		}
		if(key==107){load_plist(datatype_,lst_verwerkt_);start_=0;goto redo;}
		if(key==101 || key==111) {pbonnr=-1;goto endsr;}
 
    if(key==102) start_-=d_lin_scr;
    if(key==103){
      start_+=d_lin_scr;
      if(start_>(q_pdabons-d_lin_scr)) start_=q_pdabons-d_lin_scr;
    }
    if(start_<0) start_=0;
  }
  endsr:;
  return YES;
}

static DisplayPdaTraceerData(datatype_) // 0=retourbons , 1=traceergegevens
int16 datatype_;
{
  int16 j,k,len_,len_sscc_,z,key,mode_,max_,jj_,mm_,dd_,retval_=NO,reclen_,ptype_,via_sscc_,bad_;
  uint16 vdate_;
	float aantal_,q_pallet_,fbd_;
  char date_str_[15],time_str_[15],lotnr_[20],str_[20],sscc_[20],stuks_;
  uint16 dt_;
  long fpos,start,beg_start;

	ptype_=*s(2,26)-'0'; if(ptype_<0 || ptype_>9) ptype_=0;
	reclen_=75; if(datatype_==1) reclen_=150;
	  
  mk_name(4440,pdabons[pbonnr].filename);
	KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
  fasclos(-2);if(fasopen(filnam,1)!=0) return NO;

	fpos=0;start=0;max_=30000;fasinit(80);mode_=0;
  for(beg_start=0;beg_start<max_;beg_start++){
    next1:;
    if(read_rec(mode_)) {max_=beg_start;break;} mode_=1;
    fasinit(6); via_sscc_=NO; bad_=NO;
    len_=get_str(s(6,2),2,fldlen(6,2));
		if(datatype_==1){
			len_sscc_= get_str(sscc_,10,fldlen(67,13)); 
			if(len_==0){
				if(len_sscc_==0) continue;
				bad_=NO;
				fasinit(67); copy(sscc_,s(67,13), len_sscc_);
				if(faskeyi(67,3,1)) bad_=YES; // continue;
				if(!bad_ && cmpstr(s(67,13),sscc_,len_sscc_)) bad_=YES; //continue;
				if(!bad_ && *u(67,3)>=30000) bad_=YES; // continue; // enkel op aankoop kijken
				fasinit(6);*u(6,1)=*u(67,2); if(!bad_) fasgeti(6);
				via_sscc_=YES;
			}
		}
		else if(len_==0) continue;
    if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0) continue;
    else{
			if(via_sscc_==NO){
        if(sys4408){
        	*pu_6_1=val(s(6,2));
	        if(*pu_6_1) k=fasgeti(6); else k=1;
        }
        else k=faskeyi(6,1,0);
			}
 //     if(inq_art && inq_art!=*u(6,1)) continue;
    }
    break;
  }
  fpos=0;start=beg_start;max_=30000;fasinit(80);mode_=0;
  FOREVER{
    redo:;
    fpos=(long)(start)*reclen_;fasinit(80);*pl_80_1=fpos;mode_=0;
    scrnum=0; z=1;
		if(datatype_==0){
			scrget(2,380); 
			scrifld(z++,fmeobdk,&pdabons[pbonnr].bd_betaald);
		}
		else scrget(2,379);
    for(j=start;j<start+18;j++){
      next:;
      if(read_rec(mode_)) {max_=j;break;} mode_=1;
      fasinit(6); via_sscc_=NO; bad_=NO;
      len_=get_str(s(6,2),2,fldlen(6,2)); 
			if(datatype_==1){
    		if(cmpstr("SSCC",s(6,2),4)==0) len_=0; // enkel sscc geladen
				len_sscc_= get_str(sscc_,10,fldlen(67,13)); 
				if(len_==0){
					if(len_sscc_==0) goto next;
					bad_=NO;
					fasinit(67); copy(sscc_,s(67,13), len_sscc_);
					if(faskeyi(67,3,1)) bad_=YES; // goto next;
					if(!bad_ && cmpstr(s(67,13),sscc_,len_sscc_)) bad_=YES; // goto next;
					if(!bad_ && *u(67,3)>=30000) bad_=YES; // goto next; // enkel op aankoop kijken
				  fasinit(6);*u(6,1)=*u(67,2); 
					if(!bad_) fasgeti(6); 
					else {fasinit(67);copy(sscc_,s(6,3),len_sscc_);} // als fout
				  via_sscc_=YES;
				}
			}
			else if(len_==0) goto next;
      if(cmpstr(s(6,2),"SUBTOTAAL",fldlen(6,2))==0) goto next;
			if(via_sscc_==NO){
				if(sys4408){
					*pu_6_1=val(s(6,2));
					if(*pu_6_1) k=fasgeti(6); else k=1;
				}
				else k=faskeyi(6,1,0);
			}
//				if(inq_art && inq_art!=*u(6,1)) goto next;
			aantal_=get_num(3); //    if(get_num(2)==0) goto next;/* geen aantal */
			stuks_='\0'; get_str(&stuks_,4,1);
			if(stuks_=='J' && *f(6,31)>1) *f(6,PrNrs[ptype_])=valu_cnv("EUR","EUR",(double)(*f(6,PrNrs[ptype_])/ *f(6,31)),(double)(0.01));
			vdate_=0;zero(lotnr_,sizeof lotnr_);zero(sscc_,sizeof sscc_);
			len_= get_str(lotnr_,7,sizeof lotnr_); 
			zero(str_,sizeof str_);len_= get_str(str_,8,sizeof str_); 
			if(len_==6){
				zero(&str_[10],3); copy(&str_[0],&str_[10],2); jj_=val(&str_[10]);
				zero(&str_[10],3); copy(&str_[2],&str_[10],2); mm_=val(&str_[10]);
				zero(&str_[10],3); copy(&str_[4],&str_[10],2); dd_=val(&str_[10]);
				if(jj_ && mm_ && dd_) vdate_=datejd(jj_,mm_,dd_);
			}
//			if(lotnr_[0]=='\0' && vdate_==0) goto next;
			if(datatype_==1){
				q_pallet_=get_num(9);
				len_= get_str(sscc_,10,sizeof sscc_); 
				if(via_sscc_){
					if(lotnr_[0]=='\0') copy(s(67,12),lotnr_,fldlen(67,12));
					if(q_pallet_==0) q_pallet_=*f(67,10);
					if(vdate_==0) vdate_=*u(67,11);
				}
  			if(lotnr_[0]=='\0' && vdate_==0 && sscc_[0]=='\0') goto next;
				if(aantal_==0) aantal_=q_pallet_;
			}
      len_=get_str(date_str_,0,10); date_str_[len_]='\0';
      len_=get_str(time_str_,1,10); time_str_[len_]='\0';
      scrifld(z++,fm_os10,date_str_);
      scrifld(z++,VarTextFmt(5,0),time_str_);
      scrofld(z++,6,3,-1);
      scrifld(z++,fm_of40_,&aantal_);
			if(datatype_==0) {
				if(stuks_=='J') scrifld(z++,fm_os1,"S"); else z++;
			}
			if(datatype_==0){
				scrifld(z++,fm_of4_2,f(6,PrNrs[ptype_]));
				fbd_=*f(6,PrNrs[ptype_])*aantal_; scrifld(z++,fm_of6_2,&fbd_);
			}
			else{
        scrifld(z++,fm_odat,&vdate_);
	  		scrifld(z++,VarTextFmt(13,0),lotnr_);
			}
    }
    key=scrupd(-1,0x1AF);
    if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) {retval_=NO;break;}
    if(key==102){
      start-=18;if(start<beg_start) start=beg_start;
    }
    if(key==103) {
      start+=18;if(start>=max_-18) start=max_-18;
      if(start<beg_start) start=beg_start;
    }
    if(key==108){retval_=YES;break;}
    if(start<beg_start) start=beg_start;
  }
  fasclos(-2); 
endsr:;
	return retval_;
}



static kill_pbon(nr_)// DAT renamen naar OK, of OK deleten
int16 nr_;
{
  int16 n;
  char str_[100];
  
	fasunlck(-2);
  zero(str_,sizeof str_);
  mk_name(4440,pdabons[nr_].filename);
	for(n=0;n<50;n++) if(filnam[n]=='\0') break;
	if(n>3 && cmpstr(&filnam[n-2],"OK",2)==0){fasclos(-2); fasopen(filnam,99);} // verwerkte deleten 
	else{ // DAT renamen naar OK
		if(n>3){// OK eerst deleten 
			copy("OK",&filnam[n-3],3);
			fasclos(-2);
			fasopen(filnam,99);
		}
		mk_name(4440,pdabons[nr_].filename);
		for(n=0;n<50;n++) if(filnam[n]=='\0') break;
		copy(filnam,str_,n);str_[n]='|';
		copy(filnam,&str_[n+1],n);
		for(n=0;n<100;n++) if(str_[n]=='\0') break;
		copy("OK",&str_[n-3],3);
		fasclos(-2);
		fasopen(str_,100); // renamen naar OK
	}
}
 
static load_plist(datatype_,fl_verwerkt_) // 0=retourbons , 1=traceergegevens
int16 datatype_,fl_verwerkt_;
{
  int16 k;

	scrget(1,7);scrupd(-3,0);
  zeros((char *)&pdabons[0].krec,sizeof pdabons); q_pdabons=0;
	if(datatype_==0){
    if(fl_verwerkt_) mk_name(4440,"B*.OK"); else mk_name(4440,"B*.DAT");
	}
	else{
    if(fl_verwerkt_) mk_name(4440,"TU*.OK"); else mk_name(4440,"TU*.DAT");
	}
  fasopen(filnam,102);/* eerste call voor dir */
  FOREVER {
		fasinit(80);
    fasinfo(80,204);                            /* ophalen antwoord van dir */
    if (*s(80,1)=='\0') break;
    copy(s(80,1),pdabons[q_pdabons++].filename,20);
    if(q_pdabons>=50) break;
  }
  for(k=0;k<q_pdabons;k++) get_phdr(datatype_,k);
}
 
static get_phdr(datatype_,nr_) // 0=retourbons , 1=traceergegevens
int16 datatype_,nr_;
{
  int16 len_;
  char str_[20];
 
  zero(str_,sizeof str_);
  if(datatype_==0) copy(&pdabons[nr_].filename[1],str_,5); else copy(&pdabons[nr_].filename[2],str_,5); 
	pdabons[nr_].krec=val(str_);
  mk_name(4440,pdabons[nr_].filename);
	KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
  fasinit(80);fasclos(-2);if(fasopen(filnam,1)!=0) return YES;

  if(read_rec(0)) return YES;
  len_=ele_len(0); if(len_>15) len_=15;
  copy(rec_ele(0),pdabons[nr_].datestr,len_);
  len_=ele_len(1); if(len_>10) len_=10;
  copy(rec_ele(1),pdabons[nr_].timestr,len_);
  pdabons[nr_].bonnr=get_num(5);
	if(datatype_==0) pdabons[nr_].bd_betaald=get_num(6);
  fasclos(-2); return NO;
}

#if PDA_TRACEER
static AddPDATracedata2Doc(int select_pdabon)
{
	int16 j,k,n,ok_,len_,len_sscc_,via_sscc_,bad_,mode_=0,mode6_,nr_,jj_,mm_,dd_,stu_=2; // !!!!
	uint16 vdate_,krec_,retval_=0,rec6_,rec6_same_[10],q_same_;
	float aantal_,q_pallet_,totq_;
	char lotnr_[20],str_[20],sscc_[20],ean_bak_[15],ean_stuk_[15];

	krec_=*u(stu_,1);
	if(select_pdabon){
	  if(disp_pbon(1)) {retval_=0; goto endsr;}
	}
	else if(pbonnr<0) {retval_=0;goto endsr;}
  nr_=pbonnr;
  mk_name(4440,pdabons[nr_].filename);
	KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
  fasclos(-2);if(fasopen(filnam,1)!=0) {retval_=0; goto endsr;}

  scrget(1,7);scrupd(-3,0);
  fasinit(80);mode_=0;
  FOREVER{
    next:;
    if(read_rec(mode_)) break; mode_=1;
    aantal_=get_num(3); //    if(get_num(2)==0) goto next;/* geen aantal */
    len_= get_str(s(6,2),2,fldlen(6,2)); 
    if(cmpstr("SUBTOTAAL",rec_ele(2),9)==0) goto next;/* begin eruit */
    fasinit(6); via_sscc_=NO;bad_=NO;
    len_=get_str(s(6,2),2,fldlen(6,2)); 
		if(cmpstr("SSCC",s(6,2),4)==0) len_=0; // enkel sscc geladen
		len_sscc_= get_str(sscc_,10,fldlen(67,13)); 
		if(len_==0){
			if(len_sscc_==0) goto next;
			bad_=NO;
			fasinit(67); copy(sscc_,s(67,13), len_sscc_);
			if(faskeyi(67,3,1)) bad_=YES; // goto next;
			if(cmpstr(s(67,13),sscc_,len_sscc_)) bad_=YES; // goto next;
			if(*u(67,3)>=30000) bad_=YES; // goto next; // enkel op aankoop kijken
			fasinit(6);*u(6,1)=*u(67,2); 
			if(!bad_) fasgeti(6); 
			else {fasinit(67);copy(sscc_,s(6,3),len_sscc_);} // als fout
			via_sscc_=YES;
		}
		else{
  		if(sys4408){*u(6,1)=val(s(6,2));	if(*u(6,1)) fasgeti(6);}
	  	else faskeyi(6,1,0);		
		  if(faskeyi(6,1,0)) goto next;
		}
		vdate_=0;zero(lotnr_,sizeof lotnr_);zero(sscc_,sizeof sscc_);
    len_= get_str(lotnr_,7,sizeof lotnr_); 

    zero(str_,sizeof str_);len_= get_str(str_,8,sizeof str_); 
		if(len_==6){
			zero(&str_[10],3); copy(&str_[0],&str_[10],2); jj_=val(&str_[10]);
			zero(&str_[10],3); copy(&str_[2],&str_[10],2); mm_=val(&str_[10]);
			zero(&str_[10],3); copy(&str_[4],&str_[10],2); dd_=val(&str_[10]);
      if(jj_ && mm_ && dd_) vdate_=datejd(jj_,mm_,dd_);
		}
		q_pallet_=get_num(9);
		len_= get_str(sscc_,10,sizeof sscc_); 
		if(via_sscc_){
			if(lotnr_[0]=='\0') copy(s(67,12),lotnr_,fldlen(67,12));
			if(q_pallet_==0) q_pallet_=*f(67,10);
			if(vdate_==0) vdate_=*u(67,11);
		}
		if(lotnr_[0]=='\0' && vdate_==0 && sscc_[0]=='\0') goto next;
		if(aantal_==0) aantal_=q_pallet_; 
		if(via_sscc_ && bad_){j=max_line; goto add_art_op_bon;}
		rec6_=*u(6,1);
		zero((char *)rec6_same_,sizeof rec6_same_);q_same_=0;
		rec6_same_[q_same_++]=rec6_;copy(s(6,70),ean_bak_,fldlen(6,70)); copy(s(6,71),ean_stuk_,fldlen(6,71)); 
		if(ean_bak_[0]){ // bepalen ahv barcode welke artikels er nog zijn...acc vrij en exp hebben dezelfde barcode
		  fasinit(6); copy(ean_bak_,s(6,70),fldlen(6,70)); mode_=1;
		  FOREVER{
				if(faskeyi(6,10,mode_)) break; mode_=2;
				if(cmpstr(s(6,70),ean_bak_,fldlen(6,70))) break;
				for(j=0;j<q_same_;j++) if(*u(6,1)==rec6_same_[j]) break;
				if(j>=q_same_ && q_same_<10) rec6_same_[q_same_++]=*u(6,1);
			}
		}
		if(ean_stuk_[0]){
		  fasinit(6); copy(ean_stuk_,s(6,71),fldlen(6,71)); mode_=1;
		  FOREVER{
				if(faskeyi(6,11,mode_)) break; mode_=2;
				if(cmpstr(s(6,71),ean_stuk_,fldlen(6,71))) break;
				for(j=0;j<q_same_;j++) if(*u(6,1)==rec6_same_[j]) break;
				if(j>=q_same_ && q_same_<10) rec6_same_[q_same_++]=*u(6,1);
			}
		}
		fasinit(6);*u(6,1)=rec6_;fasgeti(6);
		for(j=0;j<max_line;j++){
			ram2stu(j);
			for(n=0;n<q_same_;n++) {
				if(*u(58,14)==rec6_same_[n]) break;
			}
			if(n<q_same_){
				rec6_=rec6_same_[n];
				fasinit(6);*u(6,1)=rec6_;fasgeti(6);
				break;
			}
		}
		if(j>=max_line && fldlen(6,102) && *u(6,102)==0){ // indien niet gevonden, dan kijken of het soms een deelverpakking is (probleem zelfde product acc.vrij)
	    fasinit(6);*u(6,102)=rec6_;mode6_=1;
			for(k=0;k<10;k++){ // is er een deelverpakking op de bon?
    		if(faskeyi(6,15,mode_)) break; mode6_=2;
		    if(*u(6,102)!=rec6_) break;
				for(j=0;j<max_line;j++){
					ram2stu(j);
					if(*u(58,14)==*u(6,1)){rec6_=*u(6,1); break;}
				}
			  if(j<max_line) break;
  		}
		}
		*u(6,1)=rec6_;fasgeti(6);
		for(j=0;j<max_line;j++){
			ram2stu(j);
			if(*u(58,14)==*u(6,1)){
				ok_=NO; totq_=0;
				for(k=0;k<10;k++){
					if(fldlen(58,136+k*4)==0) break;
					totq_+=*f(58,136+k*4); if(*f(58,7) && totq_>=*f(58,31)) break; // aantal is al uitgesplitst
					if(*u(58,137+k*4)==0 && *s(58,138+k*4)=='\0') {ok_=YES;break;}
					if(sscc_[0]){if(cmpstr(sscc_,s(58,139+k*4),fldlen(58,139+k*4))==0) {ok_=YES;break;}}
					else if(lotnr_[0]){if(cmpstr(lotnr_,s(58,138+k*4),fldlen(58,138+k*4))==0) {ok_=YES;break;}}
					else if(vdate_ && vdate_==*u(58,137+k*4)) {ok_=YES;break;}
  			}
				if(ok_){	
					*f(58,136+k*4)+=aantal_;
					copy(lotnr_,s(58,138+k*4),fldlen(58,138+k*4));
					copy(sscc_,s(58,139+k*4),fldlen(58,139+k*4));
					*u(58,137+k*4)=vdate_;
//					if(*u(58,17)==0) *f(58,7)+=aantal_; // indien nieuw artikel dan aantal verhogen
					stu2ram(j);
					totq_=0;
					for(k=0;k<10;k++){ // kijken of TRC lijnen vol zijn voor deze lijn, zo ja dan direct al opsplitsaen
					  if(fldlen(58,136+k*4)==0) break;
					  if(*u(58,137+k*4)==0 && *s(58,138+k*4)=='\0') break;
					  totq_+=*f(58,136+k*4);
					}
					if((k>=10 || fldlen(58,136+k*4)==0) && totq_<*f(58,31)){ // aantal TRC-lijnen onvoldioende om alles op te zetten, direct al uitsplitsen
						*f(58,7)=totq_;*s(58,62)=' '; totq_=*f(58,31)-totq_; *f(58,31)=*f(58,7); *u(58,17)=0; 
						stu2ram(j);
						ins_lin(j+1);
						ram2stu(j); *f(58,7)=totq_; *f(58,31)=totq_; 
						for(k=0;k<10;k++) if(fldlen(58,136+k+4)) zero(s(58,136+k*4), s(58,140+k*4)-s(58,136+k*4));
						stu2ram(j+1);
					}
					break;
				}
			}
		}
add_art_op_bon:;
		if(j>=max_line){
			for(j=max_line-1;j>=0;j--){
				ram2stu(j);
				if(test_line()) break;
			}
			j++;
			if(j>=0){
				ram2stu(j);
				*u(58,14)=*u(6,1); copy(s(6,2),s(58,15),fldlen(58,15)); copy(s(6,3),s(58,16),fldlen(58,16)); // *f(58,7)=aantal_;
				k=0; *f(58,136+k*4)+=aantal_;
				copy(lotnr_,s(58,138+k*4),fldlen(58,138+k*4));
				copy(sscc_,s(58,139+k*4),fldlen(58,139+k*4));
				*u(58,137+k*4)=vdate_;
				stu2ram(j); 
			}
		}
	}
	for(j=0;j<max_line;j++){ // aantal op bon invullen ahv scanning bij nieuw artikel
		ram2stu(j);
		if(*u(58,14) && *f(58,7)==0){
			for(k=0;k<10;k++){
				if(fldlen(58,136+k*4)==0) break;
				if(*f(58,136+k*4) && (*s(58,138+k*4) || *u(58,137+k*4) || *s(58,139+k*4))) *f(58,7)+=*f(58,136+k*4);
  		}
      stu2ram(j);
		}
	}

	fasclos(-2);kill_pbon(pbonnr);pbonnr=-1;
	retval_=YES;
endsr:;
  if(krec_){fasinit(stu_);*u(stu_,1)=krec_;fasgeti(stu_);}
	return retval_;
}
#endif

#endif


#if FT_HERAFDRUK/* bekijken/herafdrukken gemaakte facturen */
ovlcod(parmval)
int16 parmval;
{
  int16 curs=1,key,z;
  char choice;
									
  if(fldlen(4,0)){fileopen(4);bkh_exist=YES;}
  if(fldlen(86,0)) fileopen(10);

  initload(); ft_init(YES); ft_nr=0; chk_nr=NO;
#if LEVERINGSKOST  || KM_HEFFING 
		fasinit(6);*u(6,1)=RecLevKostArt; 
		if(fasgeti(6)==0) BtwLeveringskost=*f(6,28);
		else BtwLeveringskost=def_btw;
#endif
  if(parmval==1){/* automatisch voor 1 klant */
    hprt_1klt(1);
    ovlexit(-1);
  }
	if(parmval==3){ // controle foute peppoil vanuit 234
		DisplayBadPeppolList();
		ovlexit(-1);
	}



  if(*u(26,1)==YES && *u(26,2) && *u(26,5)){/* oproepen vanuit ovl014 / OVL023 */
    ft_nr=*u(26,5);ft_date=*u(26,2);
		if(*u(2,1)==0) *u(2,1)=*u(26,26);
    if(parmval==2) hprt_1ft(ft_nr,*u(2,1),YES); else hprt_1ft(ft_nr,*u(2,1),NO);
    ovlexit(-1);
  }
  FOREVER{
    scrget(2,219);z=1;fasunlck(0);
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
    if(key==101) ovlexit(-1);
    if(key==111) ovlexit(*u(25,4));
		fasunlck(-1);
    switch(choice){
      case '1': hprt_1ft(0,0,NO);break;
      case '2': hprt_1klt(0);break;
      case '3': hprt_reeks(0);break;
 #if BOEKALLO && BOEKEXEC
      case 'B': hprt_reeks(1);break;/* corrigeren boekhouding */
#endif
#if SAVEPDFFACTUUR
      case 'P': hprt_reeks(4);break;/* Aanmaken pdf's  */
#endif
      default : errnum=34; break;
    }
  }
  endsr:;
  ovlexit(-1);
}

static DisplayBadPeppolList()
{
	int key,start_,ScreenLines=18,ok_,max_jn_,jpos_;
	int16 z,k,n,curs=2,max_,jrn_nr_[5]; // aartal,mm,dd,jj,ft_jaar_,zk_via_file;
  char ofname[40],subdir[25];
  uint16 ft_beg,ft_end,dt_beg_=0,dt_end_=0,jaartal,mm,dd,jj,pos_A,mode_;

	struct {
		uint16 ft_nr;
		uint16 ft_date;
		uint16 krec;
		double bedrag;
		uint16 status;
	} tb_bad[200+1];

	jddate(*u(25,2),&jaartal,&mm,&dd);
  sysget(4704,25,subdir); chk_nr=0;
  jaartal%=100; ft_beg=0;ft_end=0;
	
  for(k=0;k<5;k++) jrn_nr_[k]=0;
max_jn_=0;
  for(k=0;k<80;k++){
    if(j_tab[k].nr && j_tab[k].typ==2) jrn_nr_[max_jn_++]=j_tab[k].nr;
    if(max_jn_>=5) break;
  }

full_redo:;
	ft_init(YES); ft_nr=0;
  sysget(4704,25,subdir); chk_nr=0; curs=2;
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,12,10,0);scraddf(z++,12,30,2);
  scraddf(z++,12,39,0);scraddf(z++,12,46,2);
  scraddf(z++,23,1,8);scraddf(z++,23,11,8);
  FOREVER{
    redo:;
    z=1;
    DisplayMenuTitel(6,"Controleren verzending facturen via peppol",0xA);
    scrifld(z++,fm_os63,"Selectie periode :");
    scrifld(z++,fm_udat,&dt_beg_);
    scrifld(z++,fm_os10,"t.e.m.");
    scrifld(z++,fm_udat,&dt_end_);
    scrifld(z++,VarTextFmt(9,0)," F1 stop ");scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
    key=scrupd(curs,0x81);curs=2;
    if(key==101) goto endsr;
    if(dt_beg_==0) {curs=2;errnum=38;goto redo;}
    if(dt_end_==0) {curs=3;errnum=38;goto redo;}
    if(key==108) break;
  }
  scrget(1,7);scrupd(-3,0);

	zero((char *)&tb_bad[0].ft_nr, sizeof tb_bad);max_=0;
	for(jpos_=0;jpos_<max_jn_;jpos_++){
		fasinit(4); *s(4,2)=jrn_nr_[jpos_]; *u(4,4)=dt_beg_;ft_nr=0; mode_=1;
		FOREVER{
			next4:;
			if(faskeyi(4,5,mode_)) break; mode_=2;
			if(*s(4,2)!=jrn_nr_[jpos_]) break;
			if(*u(4,4)>dt_end_) break;
  		if(ft_nr==*u(4,3)) goto next4;
			ft_nr=*u(4,3);
			if((ft_nr%10)==0){
				scrnum=0;scrget(1,7);scrifld(1,fm_ou5,&ft_nr);scrupd(-3,0);
			}
			copy(subdir,ofname,25);
			for(k=0;k<25;k++) if(ofname[k]=='\0') break;
			copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
			for(k=0;k<40;k++) if(ofname[k]=='\0') break;
			stcli_d(&ofname[k],(long)ft_nr,5,0);
			ofname[k+5]='.';stcli_d(&ofname[k+6],(long)jaartal,2,0);pos_A=k+8;
			ofname[pos_A]='A'; // steeds de meest recente nemen
	redo_file:;
			fasclos(-2); SeqiMode=1;
			if(fasopen(ofname,1)){
				fasclos(-2);
				ofname[pos_A]='\0';
				if(fasopen(ofname,1)){
					fasclos(-2);
					ofname[pos_A]='X';
					if(fasopen(ofname,1)) continue;
				}
			}
			ft_init(NO);
			init58(0,NO);
			load_file(); keepdata=YES; upd_mode=YES;
			fasclos(-2);
			if(dt_beg_ && ft_date<dt_beg_) goto next_file;
			if(dt_end_ && ft_date>dt_end_) goto next_file;
			if ((fldlen(2,137) && *s(2,137)=='\0') && *l(2,10)==0) goto next_file; // particulier
			if(*u(8,77)==1) goto next_file;
			if(*s(8,76)){
				n=DisplayVerzendStatus(8,0); // haal status op
				if(n==1) goto next_file; // haal status op
			}
			tb_bad[max_].ft_nr=ft_nr; tb_bad[max_].ft_date=ft_date; tb_bad[max_].krec=*u(2,1); tb_bad[max_].status=n;
			if(fldlen(8,11)) tb_bad[max_].bedrag=*d(8,11);
			max_++;
			if(max_>=200) break;
	next_file:;
			if(ofname[pos_A]=='A'){ ofname[pos_A]='\0'; goto redo_file;}
		}
  }

  start_=0; 
  FOREVER{
		redo_scr:;
    scrnum=0;scrget(2,328);z=1;
	  start_++;scrifld(z++,fm_ou3,&start_);start_--;scrifld(z++,fm_ou3,&max_);
    for(k=start_;k<start_+ScreenLines;k++){
			if(k>=max_) break;
			fasinit(2);*u(2,1)=tb_bad[k].krec; fasgeti(2);
			scrofld(z++,2,3,40); 
			scrifld(z++,fm_ou5,&tb_bad[k].ft_nr);
  		scrifld(z++,fm_odat,&tb_bad[k].ft_date);
  		scrifld(z++,fmeobd,&tb_bad[k].bedrag);
			scraddpicto(10+k-start_,z-1,1,0,2,1,43,0,6,"Factuur");
    }
    key=scrupd(-1,0x207);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==110){
			for(k=0;k<max_;k++){ // alles proberen door te sturen
				ft_nr=tb_bad[k].ft_nr;ft_date=tb_bad[k].ft_date;*u(26,2)=tb_bad[k].ft_date;
				*u(2,1)=tb_bad[k].krec; fasgeti(2);
				if ((fldlen(2,137) && *s(2,137)=='\0') && *l(2,10)==0) continue; // particulier
				if(ovlcall(2240,20)!=1) continue; // niet geregistreerd
				hprt_1ft(ft_nr,*u(2,1),2);
			}
			goto full_redo; // terug naar beginscherm omdat direct controleren te snel is en foute info geeft

			//for(n=0;n<max_;n++){ // terug controleren of het gelukt is
			//	ft_nr=tb_bad[n].ft_nr;ft_date=tb_bad[n].ft_date;*u(26,2)=tb_bad[n].ft_date;
			//  *u(2,1)=tb_bad[n].krec; fasgeti(2);
			//	if ((fldlen(2,137) && *s(2,137)=='\0') && *l(2,10)==0) continue; // particulier
			//	copy(subdir,ofname,25);
			//	for(k=0;k<25;k++) if(ofname[k]=='\0') break;
			//	copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
			//	for(k=0;k<40;k++) if(ofname[k]=='\0') break;
			//	stcli_d(&ofname[k],(long)ft_nr,5,0);
			//	ofname[k+5]='.';stcli_d(&ofname[k+6],(long)jaartal,2,0);pos_A=k+8;
			//	ofname[pos_A]='A'; // steeds de meest recente nemen
			//	fasclos(-2); SeqiMode=1;
			//	if(fasopen(ofname,1)){
			//		fasclos(-2);
			//		ofname[pos_A]='\0';
			//		if(fasopen(ofname,1)){
			//			fasclos(-2);
			//			ofname[pos_A]='X';
			//			if(fasopen(ofname,1)) continue;
			//		}
			//	}
			//	ft_init(NO);
			//	init58(0,NO);
			//	load_file(); keepdata=YES; upd_mode=YES;
			//	fasclos(-2);
			//	if(dt_beg_ && ft_date<dt_beg_) goto next_file;
			//	if(dt_end_ && ft_date>dt_end_) goto next_file;
			//	if ((fldlen(2,137) && *s(2,137)=='\0') && *l(2,10)==0) continue; // particulier
			//	ok_=NO;
			//	if(*u(8,77)==1) ok_=YES;
			//	if(ok_==NO && *s(8,76)){
			//		z=DisplayVerzendStatus(8,0); // haal status op
			//		if(z==1) ok_=YES;
			//	}
			//	if(ok_){
			//		for(n; n<max_;n++) copy((char *)&tb_bad[n+1].ft_nr, (char *)&tb_bad[n].ft_nr,sizeof tb_bad[0]);
			//		zero((char *)&tb_bad[max_].ft_nr, sizeof tb_bad[0]);max_--;
			//		n--; if(n<0) break;
			//	}
			//}
			//start_=0;goto redo_scr;
		}

		if(key>=5010 && key<5010+ScreenLines){
			ft_nr=tb_bad[start_+key-5010].ft_nr;ft_date=tb_bad[start_+key-5010].ft_date;*u(26,2)=tb_bad[start_+key-5010].ft_date;
			*u(2,1)=tb_bad[start_+key-5010].krec; fasgeti(2);
			hprt_1ft(ft_nr,*u(2,1),NO);
			ok_=NO;
		  if(*u(8,77)==1) ok_=YES;
			if(ok_==NO && *s(8,76)){
				n=DisplayVerzendStatus(8,0); // haal status op
				if(n==1) ok_=YES;
			}
			if(ok_){
				for(k=start_+key-5010; k<max_;k++) copy((char *)&tb_bad[k+1].ft_nr, (char *)&tb_bad[k].ft_nr,sizeof tb_bad[0]);
				zero((char *)&tb_bad[max_].ft_nr, sizeof tb_bad[0]);max_--;
				start_--; if(start_<0) start_=0;
			}
			goto redo_scr;
	  }		

    switch(key){
			case 12      :// PgUp 
	//		case 5001    :
			case 102     : if(start_>0){
											 start_-=ScreenLines; if(start_<0) start_=0;scrnum=0;
										 }
										 break;
			case 13      :// PgDn 
	//		case 5002      :// PgDn 
			case 103     : if((start_+ScreenLines)<max_) {start_+=ScreenLines;scrnum=0;}
										 break;
			case 101     :
			case 106     : goto endsr;// annuleer 
										 break;
			default      : break;
    }
	}
	endsr:;
	
}

static hprt_1ft(ftn_,krec_,automode_)
uint16 ftn_,krec_,automode_;
{
  int16 k,curs=2,key,z,jaartal,mm,dd,jj,use_first_=NO,nr_=0,use_Afile=NO;
  char ofname[50],subdir[25];

	struct {
	  uint16 krec;
		uint16 dt;
	  double bd;
	} ft_[2];

  // dt_bon_beg=*u(27,2);dt_bon_end=*u(27,3);
	if(ftn_){

    jddate(*u(26,2),&jaartal,&mm,&dd);
    ft_nr=ftn_;
		if(mnd_strt!=1){// indien boekjaar NIET op 1/1 begint, dan uitkijken met overlappende factuurnummers
			if(mm>=mnd_strt) use_Afile=YES; // indien in nieuw BOEKjaar van huidig kalenderjaar
		}
  }
  else{
    ft_init(YES); ft_nr=0;
    jddate(*u(25,2),&jaartal,&mm,&dd);
  }
  sysget(4704,25,subdir); chk_nr=0;
  jaartal%=100; if(fldlen(4,0)) curs=3;

  FOREVER{
    if(ftn_) goto no_screen;
    redo:;
    scrget(2,177); z=1; if(fldlen(7,1)) scraddpicto(2,0,75,22,4,2,570,0,0,"Mail"); 
    scrfld(z++,25,1);
    scrifld(z++,fm_uu5,&ft_nr);
    scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		scrifld(z++,fm_udat,&dt_bon_beg);scrifld(z++,fm_udat,&dt_bon_end);
    scrifld(z++,fm_uu2_,&jaartal);
    scrifld(z++,fm_us20,subdir);
    key=scrupd(curs,0x81); curs=2;
		use_first_=NO;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==5001){
      if(search(2,98)) {curs=3; goto redo;}
		}
		if(key==101) break;
		if(*s(2,3)){if(search(2,0)){curs=3; goto redo;}}
		if(key==5002){
			if(*u(2,1)==0){curs=3; errnum=38; goto redo;}
			ShowSavedDocument(2,(long)(*u(2,1)),1,dt_bon_beg,dt_bon_end) ;
      goto redo;
		}
    if(ft_nr==0){
      if(sear_ft(jaartal,NO,NO)) {curs=3; goto redo;}
			use_first_=YES;
    }
		else if(/* *s(2,3)=='\0' && */mnd_strt!=1){
			zero((char *)&ft_[0].krec,sizeof ft_);
			zero(ofname,sizeof ofname);
      copy(subdir,ofname,25);
      for(k=0;k<25;k++) if(ofname[k]=='\0') break;
      copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
      for(k=0;k<40;k++) if(ofname[k]=='\0') break;
      stcli_d(&ofname[k],(long)ft_nr,5,0);
      ofname[k+5]='.';stcli_d(&ofname[k+6],(long)jaartal,2,0);
      z=0;
			ofname[k+8]='A';
			fasclos(-2);
			if(CheckFtFile(ofname,0,0)){
				ft_[z].krec=*u(8,3);ft_[z].dt=ft_stu.ft_date; ft_[z].bd=ft_stu.alg_tot; 
				z++;
			}
			ofname[k+8]='\0';fasclos(-2);
			if(CheckFtFile(ofname,0,0)){
				ft_[z].krec=*u(8,3);ft_[z].dt=ft_stu.ft_date; ft_[z].bd=ft_stu.alg_tot; 
				z++;
			}			
			if(z==0) {fasclos(-2); curs=2;errnum=1;goto redo;}
			else if(z==2){
				nr_=0; scrnum=0;
				FOREVER{
					redo96:;
					scrnum=0;scrget(1,96);
					scrifld(1,fm_ou5,&ft_nr);z=2;
					*u(2,1)=ft_[0].krec; fasgeti(2);
					k=1;scrifld(z++,fm_ou3,&k);k--; scrofld(z++,2,3,-1);
					*u(2,1)=ft_[1].krec; fasgeti(2);
					k=2;scrifld(z++,fm_ou3,&k);scrofld(z++,2,3,-1);
					scrifld(36,fm_uu3,&nr_);
					key=scrupd(36,0x81);
					if ((key/0x100)==1) key=(key&0xFF)+5000;
					use_first_=YES;
					if(key==101){errnum=39;goto redo;} // annuleer 
					if(nr_<1 || nr_>2) errnum=34;
					else {use_first_=2-nr_; fasinit(2); *u(2,1)=ft_[nr_-1].krec;break;}
				}
			}
			fasclos(-2);
		}
    no_screen:;
    zero(ofname,sizeof ofname);
    copy(subdir,ofname,25);
/* sysget(4704,25,ofname); */
    for(k=0;k<25;k++) if(ofname[k]=='\0') break;
    copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
    for(k=0;k<40;k++) if(ofname[k]=='\0') break;
    stcli_d(&ofname[k],(long)ft_nr,5,0);
    ofname[k+5]='.';stcli_d(&ofname[k+6],(long)jaartal,2,0);
    fasclos(-2);
    ofname[k+8]='\0';
		KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
		if(use_Afile || (use_first_ && mnd_strt!=1)){ // eerst kijken of het via de A-file moet gebeuren 
			ofname[k+8]='A';ofname[k+9]='\0';
			if(CheckFtFile(ofname,ft_date,krec_)==NO){ofname[k+8]='\0';}
		}
		if(ftn_ && krec_){  // extra controleren of het wel echt van die klant is 
			if(CheckFtFile(ofname,ft_date,krec_)==NO){
				ofname[k+8]='\0';
			  if(CheckFtFile(ofname,ft_date,krec_)==NO){
			    ofname[k+8]='X';
			    if(CheckFtFile(ofname,ft_date,krec_)==NO) break; // niet gevonden
				}
			}
		}
		fasclos(-2);
		if(fasopen(ofname,1)){
      ofname[k+8]='X';
      if(fasopen(ofname,1)) {
				errnum=1;
				if(ftn_) break; else goto redo;
      }
    }
		copy(ofname,OriFtFileName,50);
    ft_init(NO);
    init58(0,NO);
    load_file(); keepdata=YES; upd_mode=YES;
		if(automode_){
			prt2pdf=1;
      if(verv_dt==0){
				copy(s(2,13),verv_term,3); verv_term[3]='\0';
				if(cmpstr(verv_term,"E9",2)==0){ // 1-15 : 5-de volgende maand, erboven de 20-ste volgende maand
					jddate(ft_date,&jj,&mm,&dd); jj%=100;
					if(dd<=15) dd=5; else dd=20;
					mm++; if(mm>12) {mm=1; jj++;}
					verv_dt=datejd(jj,mm,dd);
				}
				else	verv_dt=dateadd(ft_date,verv_term);
      }
#if DISCONTO
      if(disk_dt==0 && len2_14){
				copy(s(2,15),verv_term,3);
				disk_dt=dateadd(ft_date,verv_term);
      }
#endif
      select_mnt();
      if(fldlen(2,24)) taaltxt=*s(2,24);
#if LETTERSC==NO
      if(fldlen(2,40) && *s(2,40)=='J'){
#if THV_flag
				copy("F�r die richtigkeit der summe von :",opm_foot[0],40);
#else
				copy("Waar en echt verklaard voor de som van :",opm_foot[0],40);
#endif
      }
#endif
      calc();
			if(automode_==2) hfd_scr(YES);
			else{
        prt_error=NO; prt_KOPIE=YES;
        ft_prt();
			}
      fasclos(-2);
			break;
		}
    else if(exec_257()) break;
    fasclos(-2);
    if(ftn_) break;
  }
  endsr:;
}
 
static hprt_1klt(mode_)
int16 mode_;/* 1=auto via stu 27 */
{
  int16 k,n,curs=2,key,z,jaartal,mm,dd,jj,ft_jaar_,zk_via_file;
  char ofname[40],subdir[25];
						
  ft_init(YES); ft_nr=0; chk_nr=NO;
  jddate(*u(25,2),&jaartal,&mm,&dd);
  sysget(4704,25,subdir);
  jaartal%=100;
  if(mode_){
    dt_bon_beg=*u(27,2);dt_bon_end=*u(27,3);
    fasinit(2);*u(2,1)=*u(27,5);fasgeti(2);
    prt2pdf=YES;
  }

  FOREVER{
    redo:;
    scrget(2,220); z=1;scraddpicto(1,0,76,22,4,2,583,0,0,"Maak PDF"); 
    scrfld(z++,25,1);
    scrfld(z++,2,3);
    scrifld(z++,fm_udat,&dt_bon_beg);scrifld(z++,fm_udat,&dt_bon_end);
    scrifld(z++,fm_us20,subdir);
    if(mode_) key=109;
    else key=scrupd(curs,0x381); curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) break;
    if(search(2,0)){curs=2; goto redo;}
    if(dt_bon_beg==0) {curs=3; errnum=38;goto redo;}
    jddate(dt_bon_beg,&jaartal,&mm,&dd);
    jaartal%=100;
		zk_via_file=NO; if(key==110){zk_via_file=YES;key=109;}
    prt2pdf=NO;if(key==109 || key==5001){prt2pdf=YES;key=108;}
    if(sear_ft(jaartal,YES,zk_via_file)) {curs=3; goto redo;}
		if(prt2pdf && !mode_){
			getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
      if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) ovlexit(10);
			prttext("\xD0\xCD\xD0");  prtline();
			p_pdfname(s(2,3),dt_bon_beg,dt_bon_end);
			prt_string("\x1B&f1S\x1B&f0S\x1B*p+1000x*p+200Y\x1B(s1p(s20v0s3B");
			prttext("Facturen "); prtifld(fm_udat,&dt_bon_beg,-1); prttext(" t.e.m. ");prtifld(fm_udat,&dt_bon_end,-1);
      prt_string("\x1B&f1S\x1B&f0S\x1B*p+400x*p+1500Y\x1B(s1p(s30v0s3B");
      /* prtfld(2,3,-1); // */ prt_string(s(2,3));
      prtline();
      prtform(0);
      prtclose();
		}
    for(n=0;n<DIM58/2;n++){// datum op 2-de helft van array
      if(rec_58[n]==0) break;
      ft_nr=rec_58[n]; ft_jaar_=jaartal;
			if(rec_58[n+DIM58/2]){
			  jddate(rec_58[n+DIM58/2],&ft_jaar_,&mm,&dd); ft_jaar_%=100;
			}
      zero(ofname,sizeof ofname);
      copy(subdir,ofname,25);
/* sysget(4704,25,ofname); */
      for(k=0;k<25;k++) if(ofname[k]=='\0') break;
      copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
      for(k=0;k<40;k++) if(ofname[k]=='\0') break;
      stcli_d(&ofname[k],(long)ft_nr,5,0);
      ofname[k+5]='.';stcli_d(&ofname[k+6],(long)ft_jaar_,2,0);
      ofname[k+8]='\0';

			if(mnd_strt!=1){ // eerst kijken of het via de A-file moet gebeuren 
				ofname[k+8]='A';ofname[k+9]='\0';
				if(CheckFtFile(ofname,ft_date,*u(2,1))==NO){ofname[k+8]='\0';}
			}
	    fasclos(-2);
			KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
      if(fasopen(ofname,1)){
				ofname[k+8]='X';
				if(fasopen(ofname,1)) {errnum=1;continue;}
				if(CheckFtFile(ofname,ft_date,*u(2,1))==NO) continue;
      }
      ft_init(NO);
      init58(0,NO);
      load_file(); keepdata=YES; upd_mode=YES;
      if(verv_dt==0){
				copy(s(2,13),verv_term,3); verv_term[3]='\0';
				if(cmpstr(verv_term,"E9",2)==0){ // 1-15 : 5-de volgende maand, erboven de 20-ste volgende maand
					jddate(ft_date,&jj,&mm,&dd); jj%=100;
					if(dd<=15) dd=5; else dd=20;
					mm++; if(mm>12) {mm=1; jj++;}
					verv_dt=datejd(jj,mm,dd);
				}
				else	verv_dt=dateadd(ft_date,verv_term);
      }
#if DISCONTO
      if(disk_dt==0 && len2_14){
				copy(s(2,15),verv_term,3);
				disk_dt=dateadd(ft_date,verv_term);
      }
#endif
      select_mnt();
      if(fldlen(2,24)) taaltxt=*s(2,24);
#if LETTERSC==NO
      if(fldlen(2,40) && *s(2,40)=='J'){
#if THV_flag
				copy("F�r die richtigkeit der summe von :",opm_foot[0],40);
#else
				copy("Waar en echt verklaard voor de som van :",opm_foot[0],40);
#endif
      }
#endif
      calc();
      prt_error=NO; prt_KOPIE=YES;
      ft_prt();
      if(prt_error) break;
      fasclos(-2);
    }
		if(prt2pdf && !mode_){
		  getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
			if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) ovlexit(10);
			//  prttext("\xD0\xCE\xD0");
				prttext("\xD0\xCC\xD0");
				prtline();
				prtform(0);
				prtclose();
#if FLAGCRA
				ovlexit(-1); // owv dat de facturen toch nog worden afgedrukt
#endif
		}
    if(mode_) break;
  }
  endsr:;
}
 
static CheckFtFile(fname_,ftdate_,krec_)
char *fname_;
uint16 ftdate_,krec_;
{
	int pos_,k,len_,len1_,retval_=NO;


	fasclos(-2);
	if(fasopen(fname_,1)) return NO;
  fasinit(80);zero((char *)&ft_stu.ft_nr,sizeof ft_stu);
	if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)) goto endsr;
  if(seqi_rec(sortbuf,ft_stu.stu8len)) goto endsr;
	pos_=0;
	for(k=0;k<200;k++){
		len_=fldlen(8,k+1);	len1_=ft_stu.stu8[k][0];
		if(len_){
			if(len1_){
				if(len1_<len_) len_=len1_;
				copy(&sortbuf[pos_],s(8,k+1),len_);
			}
			pos_+=len1_;
		}
	}
	if(krec_){
	  if(*u(8,3)!=krec_) goto endsr;
		if(dt_bon_beg && ft_stu.ft_date<dt_bon_beg) goto endsr;
		if(dt_bon_end && ft_stu.ft_date>dt_bon_end) goto endsr;
	}
	else if(ftdate_ && ft_stu.ft_date!=ftdate_) goto endsr;
	retval_=YES;
	endsr:;
	fasclos(-2);
	return retval_;
}

static hprt_reeks(mode)// 0=drukken, 1=boeken 2=uitschrijven in UBL , 3=hermailen facturen , 4=uitschrijven pdf's
int16 mode;
{
  int16 j,k,curs=2,key,z,jaartal,mm,dd,jj,pos_A,ref_yy_,ref_jn_,ref_nr_,mail_direct_;
  char ofname[40],subdir[25];
  uint16 ft_beg,ft_end,n,aparte_pdf_,dt_beg_=0,dt_end_=0;

  ft_init(YES); ft_nr=0;
  jddate(*u(25,2),&jaartal,&mm,&dd);
  sysget(4704,25,subdir); chk_nr=0;
  jaartal%=100; ft_beg=0;ft_end=0;
	KommaKarakter='.',FieldSeparator='|';
  FOREVER{
    redo:;
    scrget(2,276); z=1;
		if(mode==1) {
			scraddf(50,7,20,6);
      scrifld(50,VarTextFmt(30,0),"  Herboeken van de facturen!");
		}
		else if(mode==2) {
			scraddf(50,7,20,6);
      scrifld(50,VarTextFmt(30,0),"  Uitschrijven facturen in XML!");
		}
		else if(mode==3) {
			scraddf(50,7,20,6);
      scrifld(50,VarTextFmt(30,0),"  Opnieuw mailen facturen!");
		}
		else if(mode==4) {
			scraddf(50,7,20,6);
      scrifld(50,VarTextFmt(40,0),"  Opnieuw uitschrijven facturen in pdf!");
		}
    scrfld(z++,25,1);
    scrifld(z++,fm_uu5,&ft_beg);
    scrifld(z++,fm_uu5,&ft_end);
    scrifld(z++,fm_udat,&dt_beg_);
    scrifld(z++,fm_udat,&dt_end_);
    scrifld(z++,fm_uu2_,&jaartal);
    scrifld(z++,fm_us20,subdir);
    key=scrupd(curs,0x399); curs=2;
    if(key==101) goto endsr;
    if(ft_beg==0) {curs=2;errnum=38;goto redo;}
    if(ft_end==0) {curs=3;errnum=38;goto redo;}
    prt2pdf=NO; aparte_pdf_=NO;
#if FACT2XML
		if(key==104 && mode==0){
			if(DisplayWarning("Wenst u echt deze reeks facturen uit te schrijven in UBL?",605,1)==YES){
			  mode=2; prt2pdf=YES;key=108; // reeks facturen uitschrijven in UBL 
			}
		}
#endif
		if(key==105 && mode==0){
			if(DisplayWarning("Wenst u echt deze reeks facturen opnieuw te mailen?",605,1)==YES){
			  mode=3; prt2pdf=YES;key=108; // reeks facturen opnieuw mailen  
			}
		}
		if(key==109){prt2pdf=YES;key=108;}
		if(key==110){prt2pdf=YES;aparte_pdf_=YES;key=108;}
    if(key==108) break;
  }
  scrget(1,7);scrupd(-3,0);
	if(mode!=2 && mode!=3 && mode!=4 && prt2pdf && aparte_pdf_==NO){
		getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
    if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) ovlexit(10);
		zero(ofname,sizeof ofname); copy("Facturen ",ofname,9);
		stcli_d(&ofname[9],(long)(2000+jaartal),4,0); copy(" : ",&ofname[13],3);
		stcli_d(&ofname[16],(long)(ft_beg),5,1); copy(" - ",&ofname[21],3);
		stcli_d(&ofname[24],(long)(ft_end),5,1);
		prttext("\xD0\xCD\xD0");  prtline();
		p_pdfname(ofname,0,0);
		prt_string("\x1B&f1S\x1B&f0S\x1B*p+1000x*p+200Y\x1B(s1p(s20v0s3B");
		prt_string(s(25,1));
		prt_string("\x1B&f1S\x1B&f0S\x1B*p+200x*p+1500Y\x1B(s1p(s40v0s3B");
		prt_string(ofname);
		prtline();
		prtform(0);
		prtclose();
	}


  for(n=ft_beg;n<=ft_end;n++){
		ft_nr=n;
#if (BOEKALLO && BOEKEXEC) || SAVEPDFFACTUUR
    if((mode==1 || mode==2 || mode==3 || mode==4) && (ft_nr%100)==0){scrget(1,170);scrifld(15,fm_ou5,&ft_nr);scrupd(-3,0);}
#endif
    zero(ofname,sizeof ofname);
    copy(subdir,ofname,25);
    for(k=0;k<25;k++) if(ofname[k]=='\0') break;
    copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
    for(k=0;k<40;k++) if(ofname[k]=='\0') break;
    stcli_d(&ofname[k],(long)ft_nr,5,0);
    ofname[k+5]='.';stcli_d(&ofname[k+6],(long)jaartal,2,0);pos_A=k+8;
		ofname[pos_A]='A'; // steeds de meest recente nemen
redo_file:;
    fasclos(-2); SeqiMode=1;
    if(fasopen(ofname,1)){
			fasclos(-2);
			ofname[pos_A]='\0';
      if(fasopen(ofname,1)){
				fasclos(-2);
        ofname[pos_A]='X';
        if(fasopen(ofname,1)) continue;
			}
    }
    ft_init(NO);
    init58(0,NO);
    load_file(); keepdata=YES; upd_mode=YES;
		if(dt_beg_ && ft_date<dt_beg_) goto next_file;
		if(dt_end_ && ft_date>dt_end_) goto next_file;
#if BOEKALLO && BOEKEXEC
    if(mode==1){/* controle op dubbele facturen */
		  if((ft_nr%100)==0){scrnum=0;scrget(1,170);scrifld(11,fm_ou5,&ft_nr);scrupd(-3,0);} // om de 500 facturen
			ref_yy_=0;ref_jn_=0;ref_nr_=0;
#if FLAGSCE // facturen kassa op 702
			SCE_kassaFT=NO;
			for(k=0;k<max_line;k++){
				ram2stu(k);
				for(j=0;j<23;j++) if(cmpstrU("VOLDAAN",ps_58_16+j,7)==0) break;
				if(j>=23) continue;
				for(j=0;j<25;j++) if(cmpstrU("KASSA",ps_58_16+j,5)==0) break;
				if(j>=25) continue;
				break;
			}
			if(k<max_line) SCE_kassaFT=YES;
#endif
#if FLAGDDB 
			for(k=0;k<max_line;k++){
				ram2stu(k);
				if(*l(58,26)==0){
					if(*i(58,34)!=99 && *f(58,24)==0) grb_comp("700000",l(58,26));
					else if(*f(58,24)==6) grb_comp("700100",l(58,26));
					else if(*f(58,24)==12) grb_comp("700200",l(58,26));
					else grb_comp("700300",l(58,26));
					stu2ram(k);
				}
			}
      fasinit(4);*s(4,2)=journl;*u(4,3)=ft_nr;key=1;
      FOREVER{
        if(faskeyi(4,1,key)) break;key=2;
        if(*s(4,2)!=journl || *u(4,3)!=ft_nr) break;
        if(*u(4,4)==ft_date){
					if(*u(4,5)<60000){ref_yy_=*s(4,8);ref_jn_=*s(4,9);ref_nr_=*u(4,10);}
					faskill(4);
				}					 
      }
#else
      if(yet_booked(journl,ft_nr,ft_date)) continue;
#endif
    }
#endif
    if(verv_dt==0){
      copy(s(2,13),verv_term,3); verv_term[3]='\0';
			if(cmpstr(verv_term,"E9",2)==0){ // 1-15 : 5-de volgende maand, erboven de 20-ste volgende maand
				jddate(ft_date,&jj,&mm,&dd); jj%=100;
				if(dd<=15) dd=5; else dd=20;
				mm++; if(mm>12) {mm=1; jj++;}
				verv_dt=datejd(jj,mm,dd);
			}
			else verv_dt=dateadd(ft_date,verv_term);
    }
#if DISCONTO
    if(disk_dt==0 && len2_14){
      copy(s(2,15),verv_term,3);
      disk_dt=dateadd(ft_date,verv_term);
    }
#endif
    select_mnt();
    if(fldlen(2,24)) taaltxt=*s(2,24);
#if LETTERSC==NO
    if(fldlen(2,40) && *s(2,40)=='J'){
#if THV_flag
      copy("F�r die richtigkeit der summe von :",opm_foot[0],40);
#else
      copy("Waar en echt verklaard voor de som van :",opm_foot[0],40);
#endif
    }
#endif
    calc();
    prt_error=NO; prt_KOPIE=YES;
#if BOEKALLO && BOEKEXEC
    if(mode==1) boekbkh(); 
		else if(mode==0) ft_prt();
#if FLAGOPS
		if(mode==1 && (ref_yy_ || ref_jn_ || ref_nr_)){ // referentie op origineel zetten 
       fasinit(4);*s(4,2)=journl;*u(4,3)=ft_nr;key=1;
       FOREVER{
         if(faskeyi(4,1,key)) break;key=2;
         if(*s(4,2)!=journl || *u(4,3)!=ft_nr) break;
         if(*u(4,4)==ft_date){
					 if(*u(4,5)<60000){*s(4,8)=ref_yy_;*s(4,9)=ref_jn_;*u(4,10)=ref_nr_;fasupd(4);break;}
				 }					 
       }
		}
#endif
#else
    if(mode!=2 && mode!=3 && mode!=4) ft_prt();
#endif
    if(prt_error) break;
    fasclos(-2);

	  if(mode==3){ // hermailen facturen 
	    mail_direct_=NO; 
    	if(fldlen(2,121) && *s(2,121)=='J' && *s(8,22)=='J') mail_direct_=YES;
	    if(fldlen(2,122) && *s(2,122)=='J' && *s(2,21) && *s(8,22)!='J') mail_direct_=YES;
			if(mail_direct_){
				prt2pdf=2; ft_prt();
				scrnum=0;scrget(1,7);scrifld(1,VarTextFmt(25,0),"Mailen factuur...");scrupd(-3,0);
				_sleep(3000); // 3 seconde wachten owv problemen layout
				FOREVER{
					if(MailDocument(1))break;
					if(DisplayWarning("Mailen NIET gelukt! Nogmaals proberen?",605,1)==NO) goto endsr;
				}
			}
		}
#if SAVEPDFFACTUUR
	  if(mode==4){ // heruitschrijven facturen in PDF
			SaveFactuur2Pdf();
		}
#endif

#if FACT2XML & !EET_RIST
		if(mode==2 && OutputMapUbl[0]){
			j=prt2pdf;
		  prt2pdf=2; ft_prt();
			if(*s(8,25)=='\0'){
				if(*u(8,8)==0) *u(8,8)=ft_date;
				jddate(*u(8,8),&Year,&Month,&Day);sprintf_s(s(8,25),fldlen(8,25),"%02d/%02d/%04d",Day,Month,Year);
			}
  		*u(8,2)=ft_nr; *u(8,8)=ft_date;MailMergeBijlage[0]=SpoolFileNr;
			scrget(1,170);scrifld(15,fm_ou5,&ft_nr);scrupd(-3,0);
#if FACT2XMLSPECIAL
#if FLAGVBE
      VBEFactuur2Pdf();
#endif
			if(ovltest(2141)) ovlcall(2141,0); else ovlcall(2240,11); 
#else
			ovlcall(2240,0);
#endif

			prt2pdf=j;
		}
#endif
next_file:;
		if(ofname[pos_A]=='A'){ ofname[pos_A]='\0'; goto redo_file;}
//		if(mnd_strt!=1 && ofname[pos_A]!='A') {ofname[pos_A]='A';goto redo_file;}
  }
	if(mode!=2 && mode!=3  && mode!=4 && prt2pdf && aparte_pdf_==NO){
		getsysprNew(5,form_dat,&pr_mode,&prtnr);PrintPaperNr=0;
		if((errnum=prtopen(prtnr,form_dat,6,80,pr_mode,3))!=0) ovlexit(10);
		prttext("\xD0\xCC\xD0");	prtline();
		prtclose();
	}
  endsr:;
}
 
static exec_257()
{
  int16 curs,k,key,z,fuval=NO;

  if(dsp_hoofding()) goto endsr;
  if(fldlen(2,24)) taaltxt=*s(2,24);
#if LETTERSC==NO
  if(fldlen(2,40) && *s(2,40)=='J'){
#if THV_flag
    copy("F�r die richtigkeit der summe von :",opm_foot[0],40);
#else
    copy("Waar en echt verklaard voor de som van :",opm_foot[0],40);
#endif
  }
#endif
  if(stuk_per_stuk){
    if(*pu_2_1==klt_div1 || *pu_2_1==klt_div2 || lev_ask){
      if(ask_lev_adr()) goto endsr;
    }
  }
  redo:
#if SCREXEC
  if(dsp_detail()==NO) goto endsr;
#endif
  calc();
  if((k=dsp_tot(NO))==NO) goto endsr;
  if(k>1)goto redo;
#if PRINTEXEC
  prt_error=NO; prt_KOPIE=YES;
  if(YES){
    for(k=0;k<1 /* *pu_8_28 */;k++) {ft_prt();prt_KOPIE=YES;}
	  if(prt_error){errnum=13;goto redo;}
		if(prt2pdf==2) {MailDocument(0);prt2pdf=0;}
    if(stuk_per_stuk){
      FOREVER{
	scrget(2,28);key=scrupd(0xFFFF,0x58);
	if(key==105) break;
	if(key==104) ft_prt();
	if(key==107) goto redo;
      }
    }
  }
#endif
  scrget(1,7);scrupd(-3,0);
  if(free!=-1){
		ClearSysPosNrCheck();
    sysflush();fasflush(0);
  }
  fuval=YES;
  endsr:;
  return fuval;
}
 
static sear_ft(jaartal_,all_,zoek_via_file_)
int16 jaartal_,all_,zoek_via_file_;
{
  int16 mode_,j,k,pnr_,z,key,start_,stu_,len_,len1_,yy,mm,dd;
  long recs_[DIM58];
  uint16 n,krec_,dt_beg,dt_end,p_tb,pos_,nr_beg_,nr_end_;
  char ofname[40],subdir[25],str_[10];
  char rstu_[DIM58];

  scrget(1,7);scrupd(-3,0); zeros((char *)&rec_58[0],sizeof rec_58);/* array gebruiken voor ftnrs en datums */
	sysget(4704,25,subdir);
  if(all_){
    dt_beg=dt_bon_beg;dt_end=dt_bon_end;
    if(dt_end==0) dt_end=datejd(jaartal_,12,31);
  }
  else{
    dt_beg=dt_bon_beg;dt_end=dt_bon_end;
		if(dt_beg==0){dt_beg=datejd(jaartal_,1,1); dt_end=datejd(jaartal_,12,31);}
  }
  krec_=*u(2,1)+30000; p_tb=0;
  zero((char *)&recs_[0],sizeof recs_); zero(rstu_,sizeof rstu_);

#if !BOEKALLO
	zoek_via_file_=YES;
#endif
	if(zoek_via_file_==NO){
		if(dt_beg<last_arc && fldlen(86,0)){
			fasinit(86);*u(86,5)=krec_; mode_=1;
			FOREVER{
				next_86:;
				if(faskeyi(86,4,mode_)) break; mode_=2;
				if(*u(86,5)!=krec_) break;
				if(*u(86,4)<dt_beg || (dt_end && *u(86,4)>dt_end)) goto next_86;
				if(*s(86,2)!=journl && !((sys1862 & 0x100) && *s(86,2)==journl+1)) goto next_86;
				recs_[p_tb]=*l(86,1);rstu_[p_tb]=86;
				rec_58[p_tb]=*u(86,3);rec_58[p_tb+DIM58/2]=*u(86,4);// datum op 2-de helft van array
				p_tb++; if(p_tb>=DIM58/2) break;
			}
		}
		if(fldlen(4,0)){
			fasinit(4);*u(4,5)=krec_; mode_=1;
			FOREVER{
				next_4:;
				if(faskeyi(4,4,mode_)) break; mode_=2;
				if(*u(4,5)!=krec_) break;
				if(*u(4,4)<dt_beg || (dt_end && *u(4,4)>dt_end)) goto next_4;
				if(*s(4,2)!=journl  && !((sys1862 & 0x100) && *s(4,2)==journl+1)) goto next_4;
				recs_[p_tb]=*l(4,1);rstu_[p_tb]=4;
				rec_58[p_tb]=*u(4,3);rec_58[p_tb+DIM58/2]=*u(4,4); // datum op 2-de helft van array
				p_tb++; if(p_tb>=DIM58/2) break;
			}
		}
	}
	else{
		sysget(4704,25,subdir);

		copy(subdir,ofname,25);
		for(k=0;k<25;k++) if(ofname[k]=='\0') break;
		copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
		for(k=0;k<40;k++) if(ofname[k]=='\0') break;
		pnr_=k;
		copy("*.",&ofname[k],2);k+=2;
		stcli_d(&ofname[k],(long)jaartal_,2,0);k+=2;
		copy("*",&ofname[k],2);nr_beg_=0;nr_end_=0;

		fasclos(-2);fasopen(ofname,102);/* eerste call voor dir */
		FOREVER {
			fasinfo(80,204);                            /* ophalen antwoord van dir */
			if (*s(80,1)=='\0') break;
			copy(s(80,1)+3,str_,5);str_[5]='\0';
			n=val(str_);
			if(n>0){
				if(nr_beg_==0 || n<nr_beg_) nr_beg_=n;
				if(nr_end_==0 || n>nr_end_) nr_end_=n;
			}
		}

		KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
		copy(subdir,ofname,25);
		for(k=0;k<25;k++) if(ofname[k]=='\0') break;
		copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
		for(k=0;k<40;k++) if(ofname[k]=='\0') break;
		pnr_=k; stcli_d(&ofname[k],(long)0,5,0);
		ofname[pnr_+5]='.';stcli_d(&ofname[pnr_+6],(long)jaartal_,2,0);
			/* +++ */
		for(n=nr_beg_;n<=nr_end_;n++){
			ofname[pnr_+8]='\0';
			stcli_d(&ofname[pnr_],(long)n,5,0); ofname[pnr_+5]='.';
			fasclos(-2);
	    if(fasopen(ofname,1)){
				ofname[pnr_+8]='A';
				if(fasopen(ofname,1)) ofname[pnr_+8]='X';
			}
			fasclos(-2);	
			if(CheckFtFile(ofname,0,*u(2,1))) {
				rec_58[p_tb]=n; p_tb++; if(p_tb>=DIM58) break;
				continue;
			}
		}
	}
 
  if(p_tb==0) {errnum=39; return YES;}
  if(all_) return NO;/* geen selectie */
	KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
	zero(ofname,sizeof ofname);copy(subdir,ofname,25);
	for(pnr_=0;pnr_<25;pnr_++) if(ofname[pnr_]=='\0') break;
	copy(s(25,3),&ofname[pnr_],3);ofname[pnr_+3]='\0';pnr_+=3;
  start_=0;
  FOREVER{
    scrnum=0;
#if FLAGABT		
		scrget(2,501);
#else 
		scrget(2,179);
#endif
		z=1;
    scrofld(z++,2,3,-1);
    for(j=start_;j<p_tb;j++){
      j++;scrifld(z++,fm_ou3,&j);j--;
			if(!zoek_via_file_){ // via bkh
				stu_=rstu_[j];fasinit(stu_);*l(stu_,1)=recs_[j];fasgeti(stu_);
				scrofld(z++,stu_,4,-1);
				scrofld(z++,stu_,3,-1);
				scrofld(z++,stu_,32,-1);
#if FLAGABT
				stcli_d(&ofname[pnr_],(long)(*u(stu_,3)),5,0); ofname[pnr_+5]='.';
				jddate(*u(stu_,4),&yy,&mm,&dd); yy%=100;	stcli_d(&ofname[pnr_+6],(long)yy,2,0);
 				fasclos(-2); SeqiMode=1;
				ofname[pnr_+8]='\0';
				if(CheckFtFile(ofname,0,*u(2,1))==NO) ofname[pnr_+8]='A';
				if(fasopen(ofname,1)){
					ofname[pnr_+8]='X';
					if(fasopen(ofname,1)) {z+=3; goto next;}
				}
				load_fthdrfile();
				scrofld(z++,8,25,10);
				scrofld(z++,8,51,10);
				scrofld(z++,8,50,10);
#else
				scrofld(z++,stu_,28,-1);
#endif
			}
			else{ // via ftkopie
				stcli_d(&ofname[pnr_],(long)rec_58[j],5,0); ofname[pnr_+5]='.';
				fasclos(-2); SeqiMode=1;
				ofname[pnr_+8]='\0';
				if(CheckFtFile(ofname,0,*u(2,1))==NO) ofname[pnr_+8]='A';
				if(fasopen(ofname,1)){
					ofname[pnr_+8]='X';
					if(fasopen(ofname,1)) continue;
				}
				fasinit(80);zero((char *)&ft_stu.ft_nr,sizeof ft_stu);
				if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)) continue;
				fasinit(8);*u(8,2)=ft_stu.ft_nr;*u(8,8)=ft_stu.ft_date;
				scrofld(z++,8,8,-1);
				scrofld(z++,8,2,-1);
				scrifld(z++,fmeobd,&ft_stu.alg_tot);
				z++;
			}
			next:;
      if(j==start_+14) break;
    }
    k=77;
#if FLAGABT
		k=107;
#endif
    j=0;scrifld(k,fm_uu3,&j);
    key=scrupd(1,0x87);
    if(key==101) {errnum=39;return YES;}
    if(j>0 && j<=p_tb) {
      if(!zoek_via_file_){ // via bkh
				stu_=rstu_[j-1];fasinit(stu_);*l(stu_,1)=recs_[j-1];fasgeti(stu_);
				ft_nr=*u(stu_,3); ft_date=*u(stu_,4); break;
			}
			else{
				ft_nr=rec_58[j-1]; ft_date=0;break;
			}
    }
    if(key==102) start_-=15;
    if(key==103) {start_+=15;if(start_>p_tb-15) start_=p_tb-15;}
    if(start_<0) start_=0;
  }
  return NO;
}
 

#if FLAGABT
static load_fthdrfile()/* inlezen factuur */
{
  int16 j,k,len_,pos_,len1_;
									
  fasinit(80);zero((char *)&ft_stu.ft_nr,sizeof ft_stu);

  if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)) return YES;

  ft_nr=ft_stu.ft_nr;ft_date=ft_stu.ft_date;
  for(k=0;k<4;k++){
    copy(&ft_stu.opm_foot[k][0],&opm_foot[k][0],sizeof ft_stu.opm_foot[k]);
  }
  if(seqi_rec(sortbuf,ft_stu.stu8len)) return YES;
  pos_=0;
  for(k=0;k<200;k++){
    len_=fldlen(8,k+1);
    len1_=ft_stu.stu8[k][0];
    if(len_){
      if(len1_){
	if(len1_<len_) len_=len1_;
	copy(&sortbuf[pos_],s(8,k+1),len_);
      }
    }
    pos_+=len1_;
  }
 endsr:;
  fasclos(-2);
  fasflush(0);
  return NO;
}

#endif


static load_file()/* inlezen factuur */
{
  int16 j,k,len_,pos_,len1_;
									
  fasinit(80);zero((char *)&ft_stu.ft_nr,sizeof ft_stu);

  if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)) return YES;

  ft_nr=ft_stu.ft_nr;ft_date=ft_stu.ft_date;
  for(k=0;k<4;k++){
    copy(&ft_stu.opm_foot[k][0],&opm_foot[k][0],sizeof ft_stu.opm_foot[k]);
  }
  if(seqi_rec(sortbuf,ft_stu.stu8len)) return YES;
  pos_=0;
  for(k=0;k<200;k++){
    len_=fldlen(8,k+1);
    len1_=ft_stu.stu8[k][0];
    if(len_){
      if(len1_){
	if(len1_<len_) len_=len1_;
	copy(&sortbuf[pos_],s(8,k+1),len_);
      }
    }
    pos_+=len1_;
  }
  for(j=0;j<max_line;j++){
    ram2stu(j);
    if(seqi_rec(sortbuf,ft_stu.stu58len)) break;
    pos_=0;
    for(k=0;k<200;k++){
      len_=fldlen(58,k+1);
      len1_=ft_stu.stu58[k][0];
      if(len_){
	if(len1_){
	  if(len1_<len_) len_=len1_;
	  copy(&sortbuf[pos_],s(58,k+1),len_);
	}
      }
      pos_+=len1_;
    }
    stu2ram(j);
  }
  endsr:;
  *pu_2_1=*u(8,3);fasgeti(2);
	for(k=0;k<4;k++) {
		if(fldlen(8,65+k) && *s(8,65+k)) copy(s(8,65+k),opm_foot[k],fldlen(8,65+k)); // opmerkingen terug opladen 
	}
  fasclos(-2);
  fasflush(0);
  return NO;
}

// #include "DRK024017.c"
#endif

static seqi_rec(ps_,len_)
char *ps_;
int16 len_;
{
  int16 k,slen_;
				
  slen_=0;
  for(k=0;k<len_;k+=280){
    if((k+280)>len_) slen_=len_-k;
    else slen_=280;
    if(fasseqi(80,1,slen_+4)) break;
    copy(s(80,1)+4,ps_+k,slen_);
  }
  if(k<len_) return YES;
  else return NO;
}

#if FLAG244 & SAMENVOEGEN/* samenvoegen leveringsbons */
ovlcod()
{
  int16 j,k,key;
  flag splitsen;
  uint16 rec1_;
  float k_perc_;

  initload();
  ft_date=*u(25,2); chk_nr=YES;

  FOREVER{
    ft_init(YES);prt_levbon='N';upd_mode=YES;splitsen=NO;
#if UPD_PRTBON
    prt_levbon='J';
#endif
    redo:
    if(!get_klt("samen te voegen",NO))break;
    if(!load_bon(YES,NO))goto redo;
    select_mnt();
    SortBon(0);
    for(k=0;k<max_line;k++){/* origineel aantal invullen voor splitsen */
      ram2stu(k);*f(58,61)=*pf_58_31;stu2ram(k);
    }
    if(exec()){
      write_bon();
      kill();/* delete originele bons */
    }
#if SPLITS_BON
    splitsen=chk_qlv();
    orig_klt=*pu_2_1; k_perc_=0;
    if(splitsen){
      v_alg_tot=alg_tot;
      ft_init(NO);
#if !ALB_flag
      fasinit(2);
#endif
      redo_2:;
      scrget(2,131);
      scrfld(1,2,3);
      scrifld(2,fm_uf2_0,&k_perc_);
      key=scrupd(1,0xA0);
      if(key==106) goto no_splits;
      if(search(2,0)) goto redo_2;
      if(key!=108) goto redo_2;
      scrget(1,7);scrupd(-3,0);
      select_mnt();
      if(k_perc_) *f(2,18)=k_perc_;
      *u(8,1)=0;j=0;/* resterend gedeelte op andere bon zetten */
      for(k=0;k<max_line;k++){/* eerst overtollige lijnen schrappen */
	ram2stu(k);
	if(*pu_58_14 && *f(58,61)){
	  *pf_58_31=-*f(58,61);*f(58,7)=*pf_58_31;
	  *pu_58_1=0;*u(58,2)=0;*u(58,3)=j;
		if(fldlen(58,62) && *s(58,62)=='P') *s(58,62)='\0';
	  stu2ram(j++);
	}
      }
      init58(j,NO);
#if SPLITS_OMZET/* gedeelte semestriele korting bijhouden op klant */
      rec1_=*pu_2_1;fasinit(2);*pu_2_1=orig_klt;fasgeti(2);
      calc();
      if(fldlen(2,64)) *f(2,64)+=semestbd;fasupd(2);
      fasinit(2);*pu_2_1=rec1_;fasgeti(2);
      if(k_perc_) *f(2,18)=k_perc_;
#endif

#if SPLITS_KAS_PR/* prijzen nemen van nieuwe klant */
      prxnr=*s(2,26)-'0';
      if(prxnr<0 || prxnr>9) prxnr=0;
      if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
      semestpc=*f(2,56);
      def_inc='N';if(sys3894 & (1<<prxnr)) def_inc='J';
      *u(8,1)=0;j=0;
      for(k=0;k<max_line;k++){
	ram2stu(k);
	if(*f(58,7)){
	  *pu_58_1=0;*u(58,2)=0;*u(58,3)=j;
	  *pf_58_20=0;*u(58,17)=0;
	  *pf_58_24=def_btw;
	  *s(58,27)=def_inc;
	  if(len58_25) copy(def_ext,ps_58_25,len58_25);
	  *pf_58_21=*f(2,18);
	  stu2ram(j++);
	}
      }
      init58(j,NO);
#endif

#if SCREXEC
			if(fldlen(8,48)) filiaal=*u(8,48);
			DoBlokkeerCheck=NO;
      FOREVER{
	if(dsp_detail()==NO) goto no_splits;
	if((k=dsp_tot(YES))==NO) goto no_splits;
#if SPLITS_TICKET
	if(k==1){
	  prt_error=NO;
	  print_strook();
	  if(prt_error==NO) break;
	}
#else
	if(k==1) break;
#endif
      }
#endif
      scrget(1,7);scrupd(-3,0);
      j=0;
      for(k=0;k<max_line;k++){/* lege lijnen terug schrappen */
	ram2stu(k);
	if(*pu_58_14 && *pf_58_31){/* enkel echte artikels */
	  *u(58,3)=j;
	  stu2ram(j++);
	}
      }
      init58(j,NO);
      load_sysnr(YES);
      if(*pu_2_1==orig_klt || test_kontb(j)){/* indien zelfde klant of geen bons */
				ft_init(NO);
				sysget(last_vfa,2,&last_vf);
				*u(8,3)=*pu_2_1;*u(8,2)=last_vf+1;
				for(k=0;k<6;k++){
					copy(s(2,2+k),s(8,13+k),fldlen(8,13+k));
					if(fldlen(2,142+k) && *s(2,142+k)) copy(s(2,142+k),s(8,13+k),fldlen(8,13+k)); // afwijkend leveringsadres
				}
				if(fldlen(8,33)){
				  if(fldlen(2,35) && *s(8,33)=='\0') *s(8,33)=*s(2,35);
				}
#if SPLITS_UPNR
				last_vf++; sysput(last_vfa,2,&last_vf);/* nummer wegschrijven */
#endif
      }
      else {
	add_kontb(j);
      }
      select_mnt();
      calc();
      write_konb();
			ClearSysPosNrCheck();
    sysflush();
#if KORT_DELAYED/* gedeelte  korting bijhouden op klant */
      rec1_=*pu_2_1;fasinit(2);*pu_2_1=orig_klt;fasgeti(2);
      if(fldlen(2,49) && *s(2,49)=='J'){
	*f(2,50)+=tot_kort;fasupd(2);
      }
      fasinit(2);*pu_2_1=rec1_;fasgeti(2);
#endif
#if SPLIST_STATIST && STATISTIEK/* gedeelte  korting bijhouden op klant */
      rec1_=*pu_2_1;fasinit(2);*pu_2_1=orig_klt;fasgeti(2);
      statistiek_upd(YES);
      fasinit(2);*pu_2_1=rec1_;fasgeti(2);
#endif
    }
    no_splits:;
#endif
  }
  ovl_exit(218);
}
#endif

#if FLAG248 & !FACT_RISTOURNO & !KAS2JMCFACTUUR & !KAS2JMCBON & !KAS2FACT & !FT_HERAFDRUK & !KASINPUT | FLAG242/* facturatie uit leveringsbons */
ovlcod(parmval) // parmval : 0=normaal , 1=direct factureren van 1 bon (opgeroepen door ovl244)
int16 parmval;
{
  int16 curs=1,key,z;
  char choice;

  initload();
  ft_date=*u(25,2);upd_mode=NO; chk_nr=YES;prt_levbon=DEFLVPRT;q_paletstick=1;

#if BONFILE==NO
  ft_manu();
#else
	if(parmval==1){
		ft_1bon_direct(); // bonrecord zit in 26,5
		ovl_exit(-1);
	}
#if NO_FT_SER
  ft_1ft();
#else
	if(sys2989) ft_1ft();
	else{
		FOREVER{
			scrget(2,21);z=1;
			scrfld(z++,25,1);
			scrifld(z++,fm_menu,&choice);
			key=scrupd(curs,0x0401);
			if(key==101) break;
			if(key==111) ovl_exit(0);
			switch(choice){
				case '1': ft_1ft();break;
				case 'S': ft_serie();break;
				default : errnum=34; break;
			}
		}
	}
#endif
#endif
  ovl_exit(218);
}
#endif

#if FLAG248 & KAS2JMCFACTUUR //  rechtstreekse facturatie van kassafactuur via JMC
ovlcod(parmval) // parmval : 0=berekenen , 1=factureren, 99=printertest
int16 parmval;
{
	int16 j,k,key,fuval=NO,mode_,change_,q_exemp_,mail_direct_,SendViaCodabox_=YES,ori_prt2pdf_,t_nr_,yy,mm,dd;
	long TbDiversArtikel[10]; // divers artikel per mogelijk BTW%
	char txt_[150];
  
  initload();
  CallingOvl=941;	
  ft_date=*u(25,2);upd_mode=NO; chk_nr=YES;prt_levbon=DEFLVPRT;q_paletstick=1;
	verv_dt=0;disk_dt=0;kredietbp_bd=0;KM_heffing=0;winst_pc=0;winst_bd=0;stuk_per_stuk=NO;
  zero(opm_foot[0],sizeof opm_foot);stat_klt=0;keepdata=YES;
  zero(opm_bkh,sizeof opm_bkh);
	btw_glob=99;
  sysget(last_vfa,2,&last_vf);ft_nr=last_vf+1;

	if(parmval==99){
		ft_init(YES);prt_KOPIE=0;
		ft_nr=9999; 
		for(k=3;k<7;k++) copy("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",s(2,k),fldlen(2,k));
		copy("Printer-test",s(8,25),fldlen(8,25));
    ram2stu(0);
		*f(58,7)=999; copy("AAAAA",s(58,15),fldlen(58,15));copy("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",s(58,16),fldlen(58,16));*f(58,20)=9; 
    stu2ram(0);
		ram2stu(1);
		*f(58,7)=9; copy("CCCCC",s(58,15),fldlen(58,15));copy("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",s(58,16),fldlen(58,16));
		*f(58,20)=9999; *f(58,21)=10;
    stu2ram(1); select_mnt();
		calc();
		ft_prt();
		goto endsr;
//		retcall=0;ovlexit(0);
	}

	// hier de aangepaste exec
  fasunlck(0);
	if(dsp_hoofding()) goto endsr;

#if FLAGSAS
	if(*s(2,42)=='J'){ // bij feestklant de naam vragen
  	if(ask_lev_adr()) goto endsr;
	}
#endif

#if FLAGBLI
	if(ask_lev_adr()) goto endsr;
#endif
#if STOCK_OP_LOCATIE
	if(fldlen(8,48)){ // voor de veiligheid nogmaals invullen
		sysget(2854,2,u(8,48)); if(*u(8,48)<1 || *u(8,48)>10) *u(8,48)=99; // firma in apart journaal
	  if(WerkpostFiliaalNr && WerkpostFiliaalNr<=10 && nm_loc[WerkpostFiliaalNr-1][0]) *u(8,48)=WerkpostFiliaalNr;
	}
#endif

	fasunlck(-1);
#if FLAGEET & DRANKGIGANT
	if(*pu_8_28<2) *pu_8_28=2;
#endif
  for(k=0;k<2;k++) *u(8,19+k)=last_vt[k];
  if(fldlen(2,24)) taaltxt=*s(2,24);
  if(fldlen(8,30) && *s(8,30)=='\0') *s(8,30)=MAG_GEFACT;
	if(fldlen(8,74)) *s(8,74)=YES; // om aan te duiden dat het van de kassa komt
	if(fldlen(8,70)) *u(8,70)=procid;
	if(fldlen(8,72)) *u(8,72)=*u(25,2);

#if FLAG244 | FLAG242
  if(fldlen(8,33)){if(fldlen(2,35)==0) *s(8,33)='N';}
#endif
	sysget(2900,40,(char *)&TbDiversArtikel[0]); // zie parameters V.2.+
	for(k=0;k<max_line;k++){ // stuk van dsp_detail
		ram2stu(k); j=*i(58,34);
    if(*s(8,26)=='J') *pf_58_24=0;
    if((*ps_58_15 || *ps_58_16) && *ps_58_16!='*' && *u(58,17)!=hash()){
			fasinit(6);copy(s(58,15),s(6,2),fldlen(6,2));
			if(faskeyi(6,1,0)){
				if(*i(58,34)==99){ 
			    *pu_58_14=TbDiversArtikel[9];*u(58,48)=TbDiversArtikel[9];
				} // leeggoed divers
		    else {
		    	for(j=0;j<8;j++) if(*f(58,24)==btw_pct[j]) break;
    			if(j<8) *pu_58_14=TbDiversArtikel[j];
    		}	
		    *u(6,1)=*pu_58_14; if(*u(6,1)) fasgeti(6);
			}		
			else copy(s(6,2),ps_58_15,len58_15);
			if(*s(58,16)=='+') *s(58,16)='*'; // kortingslijn
			else{
				*pu_58_14=*pu_6_1;
				t_nr_=taal_nr; if(*s(6,3+t_nr_)=='\0') t_nr_=0;
				copy(s(6,3+t_nr_),ps_58_16,fldlen(58,16));
				if(*f(58,20)==0) *f(58,20)=0.00001; // om te vermijden dat gratis artikels toch een prijs krijgen
		  }
			stu2ram(k);
			Fill58FromNewArtikel(k);

		}
		if(*i(58,34)==99){
			*u(58,48)=*pu_58_14;
			*f(58,46)=*pf_58_20;
			*f(58,49)=1;
		}
		if(*ps_58_16=='*'){
			if(fldlen(58,50)) *f(58,50)=0;
			if(fldlen(58,51)) *i(58,51)=0;
			if(fldlen(58,54)) *f(58,54)=0;
			if(fldlen(58,63)) *f(58,63)=1;
	#if !KAS2FACT
			*f(58,46)=0;*u(58,48)=0;*f(58,49)=0;
	#endif
			*f(58,38)=0;
	#if AFHAALVERG
			zero(s(58,55),s(58,58)-s(58,55));
	#endif
	#if LOSVERGOED
			zero(s(58,58),s(58,61)-s(58,58));
	#endif
	#if PALET_KORTING
			zero(s(58,67),s(58,70)-s(58,67));
	#endif
		}

		if(btw_glob!=99) *pf_58_24=btw_glob;
		*pf_58_24=round((double)(*pf_58_24)); // om vieze dingen ver na komma weg te doen 
		stu2ram(k);
	}
  calc();
#if KAS2JMC_DISPLAY_EINDE  // toon eindscherm 
	redo_dsp_tot:;
	if(dsp_tot(NO)!=YES) goto endsr;
#endif
	zero((char *)&FactuurTotalen.ft_nr,sizeof FactuurTotalen);
	FactuurTotalen.ft_date=ft_date;
	//FactuurTotalen.ft_nr;
  FactuurTotalen.alg_tot=alg_tot;
  FactuurTotalen.belastbt=belastbt;
  FactuurTotalen.btw_tot=btw_tot;
  FactuurTotalen.tot_leeg=tot_leeg;
	if(parmval==0){fuval=YES;goto endsr;} // berekenen is OK
//   if((k=dsp_tot(NO))==NO) goto endsr;
  load_sysnr(NO);
  if(chk_nr){
    ft_nr=last_vf+1;
    if(ftchk()){
      FOREVER{
				scrget(2,138);
				scrifld(1,fm_uu5,&ft_nr);
				key=scrupd(1,0x82);
				if(key==102) goto endsr;   // exit met fout
				ftchk();
				if(errnum==0) break;
      }
    }
  }
#if PRINTEXEC
  prt_error=NO; prt_KOPIE=NO; mail_direct_=NO; SendViaCodabox_=NO;
	if(fldlen(2,121) && *s(2,121)=='J' && *s(8,22)=='J') mail_direct_=YES;
	if(fldlen(2,122) && *s(2,122)=='J' && *s(2,21) && *s(8,22)!='J') mail_direct_=YES;
#if FACT2CODABOX
	if(fldlen(2,128) && *s(2,128)=='P' && prt2pdf!=2) {
		if(*s(8,25)=='\0'){ // er moet een referentie meegegeven worden in codabax
#if FLAGJAN || FLAGTOL
		 sprintf_s(s(8,25),15,"%s-%05d","Peppol",ft_nr);
     // jddate(*u(8,8),&Year,&Month,&Day);sprintf_s(s(8,25),fldlen(8,25),"%02d/%02d/%04d",Day,Month,Year);
#else
     copy("Kasticket ",s(8,25),10);
     jddate(*u(8,8),&yy,&mm,&dd); yy%=100;
     stcli_d(s(8,25)+10,(long)dd,2,0);*(s(8,25)+12)='-';
     stcli_d(s(8,25)+13,(long)mm,2,0);*(s(8,25)+15)='-';
     stcli_d(s(8,25)+16,(long)yy,2,0);
#endif
		}
		SendViaCodabox_=YES; // mail_direct_=NO; // indien peppol, dan niet mailen
	}
#endif
#if FLAGARS
	if(sys2696) mail_direct_=NO; // nooit automatisch mailen vanuit B02
#endif
  if(YES){
#if FLAGDU3  // facturen aan kassa op A4 tijdelijk tot kettingpapier op is (maart 2019)
	 *pu_8_28=2; if(*s(8,22)!='J') *pu_8_28=3; // niet voldane facturen 3X drukken
#endif
    q_exemp_=*pu_8_28;
		if(SendViaCodabox_==NO && fldlen(2,128) && *s(2,128)=='P') q_exemp_--;
    if(q_exemp_>1 && (prt2pdf /* || SendViaCodabox_*/ )) q_exemp_=1;/* slechts 1x bij pdf/mail */

		if(mail_direct_ || SendViaCodabox_ || prt2pdf==2){
redo_mail:;
//		if((mail_direct_ || SendViaCodabox_) && prt2pdf!=2){
#if NO_FT_KOPIEPRT || SAVEPDFFACTUUR
			q_exemp_-=2; // q_exemp_=0;
//			q_exemp_--; if(prt2pdf==2 && q_exemp_<1) q_exemp_=1;
#else
			if(q_exemp_>1) {q_exemp_--;prt_KOPIE+=1;}
			else q_exemp_=1;
#endif
			if(mail_direct_ || prt2pdf==2){
				ori_prt2pdf_=prt2pdf;prt2pdf=2; ft_prt();prt2pdf=ori_prt2pdf_;
				scrnum=0;scrget(1,7);scrifld(1,VarTextFmt(25,0),"Mailen factuur...");scrupd(-3,0);
				_sleep(3000); // 3 seconde wachten owv problemen layout
				FOREVER{
					if(mail_direct_){	if(MailDocument(1))break;}
					else {if(MailDocument(0))break;}
					if(DisplayWarning("Mailen NIET gelukt! Nogmaals proberen?",605,1)==NO){
#if KAS2JMC_DISPLAY_EINDE  					
						if(mail_direct_==NO) goto redo_dsp_tot; // toon eindscherm opnieuw bij probleem manuele mail
#endif
						goto endsr;
					}
				}
				if(prt2pdf==2) {
				  prt2pdf=0;
#if KAS2JMC_DISPLAY_EINDE  // toon eindscherm 
			      goto redo_dsp_tot;
#endif
				}
			}
			if(SendViaCodabox_){
				ori_prt2pdf_=prt2pdf;prt2pdf=2; ft_prt();prt2pdf=ori_prt2pdf_;
				scrnum=0;scrget(1,7);scrupd(-3,0);
				_sleep(1000); // 3 seconde wachten owv problemen layout
				if(*s(8,25)=='\0'){
				  if(*u(8,8)==0) *u(8,8)=ft_date;
				  jddate(*u(8,8),&Year,&Month,&Day);sprintf_s(s(8,25),fldlen(8,25),"%02d/%02d/%04d",Day,Month,Year);
			  }
				*u(8,2)=ft_nr; *u(8,8)=ft_date;MailMergeBijlage[0]=SpoolFileNr;
				scrnum=0;scrget(1,170); 
				scrifld(5,fm_os63,"Bezig met factuur te versturen via peppol...");
				scrupd(-3,0);
				ovlcall(2240,10);
				//if(ovlcall(2240,10)){ // indien niet gelukt, dan proberen te mailen + extra afdruk
				//	SendViaCodabox_=NO;q_exemp_++;
				//	if(mail_direct_==NO && (*s(2,21) || (fldlen(2,129) && *s(2,129)))){ mail_direct_=YES; goto redo_mail;} 
				//}
				//FOREVER{
				//	if(ovlcall(2240,10)) break;
				//	if(DisplayWarning("Versturen naar Codabox NIET gelukt! Nogmaals proberen?",605,1)==NO) goto endsr;
				//}
			}
    	if(fldlen(7,0) && ((mail_direct_ && MailUniqueID[0]!='\0') || (SendViaCodabox_ && CodaboxRefID[0]!='\0'))){
				fasinit(7);
				if(SendViaCodabox_){
					copy(CodaboxUniqueID,s(7,2),18); *i(7,5)=1; copy(CodaboxRefID,s(7,6),fldlen(7,6)); *u(7,7)=*u(8,77); *u(7,8)=*u(8,78);
				}
				else{
					copy(MailUniqueID,s(7,2),12);
				}
				*u(7,4)=*u(25,2); 
				*u(7,10)=2;*l(7,11)=*u(2,1);
				*u(7,15)=1;*u(7,16)=1+(procid/5);
				if(alg_tot>=0) k=copy0(facttxt[0],s(7,17),20);	else k=copy0(credntxt[0],s(7,17),20);
        stcli_d(s(7,17)+k,(long)(ft_nr),6,1);
				fasadd(7);
			}
			mail_direct_=NO; SendViaCodabox_=NO;
			q_exemp_--;prt_KOPIE+=1;
#if !FLAGSMM && !FLAGALB && !FLAGQIC && !NO_FT_KOPIEPRT && !SAVEPDFFACTUUR
			if(def_qfact && q_exemp_<1) q_exemp_=1; 
#endif
			k=fldlen(2,21); if(k>fldlen(8,55)) k=fldlen(8,55);copy(s(2,21),s(8,55),k); // als bewijs bijhouden 
			if(prt2pdf==2) prt2pdf=0;
		}
#if FLAGSTO
		if(q_exemp_>1) q_exemp_=1; // max 1 afdruk
#endif
#if FLAGSAS || FLAGLIK
		q_exemp_=0; // nooit factuur afdrukken aan de kassa
#endif
    for(k=0;k<q_exemp_;k++) {
#if (SAVEPDFFACTUUR || NO_FT_KOPIEPRT) && FLAG248 && !FT_HERAFDRUK
			if(!(k && k>=(q_exemp_-1))) 
#endif
			  ft_prt();
			prt_KOPIE+=1;
		}
    if(prt_error){errnum=13;goto endsr;}

  }
#endif
  scrget(1,7);scrupd(-3,0);
  if(free!=-1){

#if FICHEEXEC
		fasunlck(-2);
    if(stock_JN=='J' || stock_JN=='S'){
#if STATISTIEK
      statistiek_upd(NO);
#endif
#if HISTORIEK
      historiek_upd();
#endif
#if ARTEXIST && (!BONFILE || !STOCK244)  // stock wordt hier NIET aangepast (=bij inlezen OVL0290), maar is nodig voor omzetfiches
      if(art_exist) art_stat();
#endif
      if(k_omz_exist) klt_stat();
    }
#endif
#if FLAG248 & DUMP_CFT
    if(sys2940!=1) seqo_cft();
#endif
#if BOEKALLO & BOEKEXEC & !FT_HERAFDRUK
		fasunlck(-2);
    if(bkh_exist && boek_JN=='J') boekbkh();
#endif
    if(chk_nr || !bkh_exist){
			FactuurTotalen.ft_nr=ft_nr; // pas als alles OK is
      last_vf=ft_nr;
      sysput(last_vfa,2,&last_vf);
    }
		ClearSysPosNrCheck();
    sysflush();fasflush(0);
  }
#if FLAG248 && !FT_HERAFDRUK && MAIL_FT2BKH 
    MailFactuur2Boekhouder(); // definieren in parlay.c cfr ERL
#endif
#if !FT_HERAFDRUK && FACT2XML
		if(OutputMapUbl[0]){
		  prt2pdf=2; ft_prt();
			if(*s(8,25)=='\0'){
				if(*u(8,8)==0) *u(8,8)=ft_date;
				jddate(*u(8,8),&Year,&Month,&Day);sprintf_s(s(8,25),fldlen(8,25),"%02d/%02d/%04d",Day,Month,Year);
			}
  		*u(8,2)=ft_nr; *u(8,8)=ft_date;MailMergeBijlage[0]=SpoolFileNr;
#if FACT2XMLSPECIAL
#if FLAGVBE
      VBEFactuur2Pdf();
#endif
			if(ovltest(2141)) ovlcall(2141,0); else ovlcall(2240,11); 
#else
			ovlcall(2240,0);
#endif
		}
#endif

	if(fldlen(2,121) && *s(2,121)=='J' && *s(8,22)=='J') mail_direct_=YES;
	if(fldlen(2,122) && *s(2,122)=='J' && *s(2,21) && *s(8,22)!='J') mail_direct_=YES;
#if FACT2CODABOX
	if(fldlen(2,128) && *s(2,128)=='P') {/* mail_direct_=NO; */ SendViaCodabox_=YES;}
#endif
#if FLAGARS
	if(sys2696) mail_direct_=NO; // nooit automatisch mailen vanuit B02
#endif
  fuval=YES; 
	if(SendViaCodabox_) fuval=3;
	else if(mail_direct_) fuval=2; 
#if NO // YES // !KAS2JMC_DISPLAY_EINDE   
	if(fuval==2 || fuval==3){
		if(SendViaCodabox_ && mail_direct_){
      zero(txt_,sizeof txt_); k=copy0("De factuur werd gemaild EN via peppol electronisch verstuurd",txt_,50);
		}
		else if(fuval==2){
  		zero(txt_,sizeof txt_); k=copy0("De factuur werd gemaild naar ",txt_,30);
	  	if(fldlen(2,129) && *s(2,129)) copy0(s(2,129),&txt_[k],fldlen(2,129)); // mailadres boekhouder 
      else copy0(s(2,21),&txt_[k],fldlen(2,21));
		}
		else{
      zero(txt_,sizeof txt_); k=copy0("De factuur werd via peppol electronisch verstuurd",txt_,50);
		}
		DisplayWarning(txt_,569,2); _sleep(2000);
	}
#endif
endsr:;
	ClearSysPosNrCheck();
  retcall=fuval;
  ovlexit(-1);
}
#endif

#if FLAG244 & KAS2JMCBON //  aanmaken leveringsbons vanuit KeyConen-kassa via ovlcall vanuit ovl0900
ovlcod(parmval) // parmval : 0=berekenen , 1=factureren
int16 parmval;
{
	int16 j,k,key,fuval=NO,mode_,change_,q_exemp_,mail_direct_,ori_prt2pdf_,t_nr_,dd,mm,yy;
	long TbDiversArtikel[10]; // divers artikel per mogelijk BTW%
  
  initload();
  ft_date=*u(25,2);upd_mode=NO; chk_nr=YES;prt_levbon=DEFLVPRT;q_paletstick=1;
	verv_dt=0;disk_dt=0;winst_pc=0;winst_bd=0;stuk_per_stuk=NO;
  zero(opm_foot[0],sizeof opm_foot);stat_klt=0;keepdata=YES;
  zero(opm_bkh,sizeof opm_bkh);
	btw_glob=99;
  sysget(last_vfa,2,&last_vf);ft_nr=last_vf+1;

#if FACT2CODABOX
	if(fldlen(2,128) && *s(2,128)=='P') {
		if(*s(8,25)=='\0'){ // er moet een referentie meegegeven worden in codabax
#if FLAGJAN || FLAGTOL
		 sprintf_s(s(8,25),15,"%s-%05d","Peppol",ft_nr);
//		 jddate(*u(8,8),&Year,&Month,&Day);sprintf_s(s(8,25),fldlen(8,25),"%02d/%02d/%04d",Day,Month,Year);
#else
     copy("Kasticket ",s(8,25),10);
     jddate(*u(8,8),&yy,&mm,&dd); yy%=100;
     stcli_d(s(8,25)+10,(long)dd,2,0);*(s(8,25)+12)='-';
     stcli_d(s(8,25)+13,(long)mm,2,0);*(s(8,25)+15)='-';
     stcli_d(s(8,25)+16,(long)yy,2,0);
#endif
		}
	}
#endif

	// hier de aangepaste exec
  fasunlck(0);
	if(dsp_hoofding()) goto endsr;
#if FLAGSAS
	if(*s(2,42)=='J'){ // bij feestklant de naam vragen
  	if(ask_lev_adr()) goto endsr;
	}
#endif
	fasunlck(-1);
  if(fldlen(8,30) && *s(8,30)=='\0') *s(8,30)=MAG_GEFACT;
	if(fldlen(8,33)){
	  if(fldlen(2,35) && *s(8,33)=='\0') *s(8,33)=*s(2,35);
	}
#if STOCK_OP_LOCATIE
	if(fldlen(8,48)){ // voor de veiligheid nogmaals invullen
		sysget(2854,2,u(8,48)); if(*u(8,48)<1 || *u(8,48)>10) *u(8,48)=99; // firma in apart journaal
	  if(WerkpostFiliaalNr && WerkpostFiliaalNr<=10 && nm_loc[WerkpostFiliaalNr-1][0]) *u(8,48)=WerkpostFiliaalNr;
	}
#endif
  if(fldlen(8,74)) *s(8,74)=YES; // om aan te duiden dat het van de kassa komt
  for(k=0;k<2;k++) *u(8,19+k)=last_vt[k];
  if(fldlen(2,24)) taaltxt=*s(2,24);
	sysget(2900,40,(char *)&TbDiversArtikel[0]); // zie parameters V.4
	for(k=0;k<max_line;k++){ // stuk van dsp_detail
		ram2stu(k); j=*i(58,34);
    if(*s(8,26)=='J') *pf_58_24=0;
    if((*ps_58_15 || *ps_58_16) && *ps_58_16!='*' && *u(58,17)!=hash()){
			fasinit(6);copy(s(58,15),s(6,2),fldlen(6,2));
			if(faskeyi(6,1,0)){
				if(*i(58,34)==99){ 
			    *pu_58_14=TbDiversArtikel[9];*u(58,48)=TbDiversArtikel[9];
				} // leeggoed divers
		    else {
		    	for(j=0;j<8;j++) if(*f(58,24)==btw_pct[j]) break;
    			if(j<8) *pu_58_14=TbDiversArtikel[j];
    		}	
		    *u(6,1)=*pu_58_14; if(*u(6,1)) fasgeti(6);
			}		
			else copy(s(6,2),ps_58_15,len58_15);
			if(*s(58,16)=='+') *s(58,16)='*'; // kortingslijn
			else{
				*pu_58_14=*pu_6_1;
				t_nr_=taal_nr; if(*s(6,3+t_nr_)=='\0') t_nr_=0;
				copy(s(6,3+t_nr_),ps_58_16,fldlen(58,16));
				if(*f(58,20)==0) *f(58,20)=0.00001; // om te vermijden dat gratis artikels toch een prijs krijgen
			}
			stu2ram(k);
			Fill58FromNewArtikel(k);
		}
		if(*i(58,34)==99){
			*u(58,48)=*pu_58_14;
			*f(58,46)=*pf_58_20;
			*f(58,49)=1;
		}
		if(*ps_58_16=='*'){
			if(fldlen(58,50)) *f(58,50)=0;
			if(fldlen(58,51)) *i(58,51)=0;
			if(fldlen(58,54)) *f(58,54)=0;
			if(fldlen(58,63)) *f(58,63)=1;
	#if !KAS2FACT
			*f(58,46)=0;*u(58,48)=0;*f(58,49)=0;
	#endif
			*f(58,38)=0;
	#if AFHAALVERG
			zero(s(58,55),s(58,58)-s(58,55));
	#endif
	#if LOSVERGOED
			zero(s(58,58),s(58,61)-s(58,58));
	#endif
	#if PALET_KORTING
			zero(s(58,67),s(58,70)-s(58,67));
	#endif
		}

		if(btw_glob!=99) *pf_58_24=btw_glob;
		*pf_58_24=round((double)(*pf_58_24)); // om vieze dingen ver na komma weg te doen 
		stu2ram(k);
	}
  calc();
#if KAS2JMC_DISPLAY_EINDE  // toon eindscherm 
	if(dsp_tot(NO)!=YES) goto endsr;
#endif
	zero((char *)&FactuurTotalen.ft_nr,sizeof FactuurTotalen);
	FactuurTotalen.ft_date=ft_date;
	//FactuurTotalen.ft_nr;
  FactuurTotalen.alg_tot=alg_tot;
  FactuurTotalen.belastbt=belastbt;
  FactuurTotalen.btw_tot=btw_tot;
  FactuurTotalen.tot_leeg=tot_leeg;
	if(parmval==0){fuval=YES;goto endsr;} // berekenen is OK
//   if((k=dsp_tot(NO))==NO) goto endsr;
  load_sysnr(NO);
  if(chk_nr){
    if(upd_mode==NO){
      *u(8,2)=last_vf+1;
			copy(s(8,1),buf1000,fldlen(8,0));
			for(k=0;k<5;k++) { // voor het geval dat de vorige bonnr niet goed is weggeschreven
				if(faskeyi(8,2,0)) break;
				last_vf++; *u(8,2)=last_vf+1;
			}
			copy(buf1000,s(8,1),fldlen(8,0));*u(8,2)=last_vf+1;
    }
  }
#if BONSORT && (FLAG244 || (FLAG248 && BONFILE==NO))
  SortBon(0);
#endif
#if BONSEQNR && !FLAG248/* aantal updates van bon bijhouden */
  if(fldlen(8,52)) *u(8,52)+=1;
#endif
#if PRINTEXEC
  prt_error=NO; prt_KOPIE=NO; mail_direct_=NO;
#if FLAGDU3  // facturen aan kassa op A4 tijdelijk tot kettingpapier op is (maart 2019)
	 /* if(*pu_8_28<2)  */ *pu_8_28=2;
#endif
#if FLAG248 | FLAG242 | (FLAG244 && PRTBON2X)
  if(prt_levbon=='J'){
    q_exemp_=*pu_8_28;
#if FLAG244 | FLAG242
#ifdef PRTBON_Q
    q_exemp_=PRTBON_Q;
#endif
#endif
    if(prt2pdf) q_exemp_=1;/* slechts 1x bij pdf/mail */
#if !FLAG248 && FLAGMIN
		if(upd_mode) q_exemp_=1;
#endif
    for(k=0;k<q_exemp_;k++) {ft_prt();prt_KOPIE+=1;}
    if(prt_error){errnum=13;goto endsr;}
		if(prt2pdf==2) {ft_prt();_sleep(3000);MailDocument(0);prt2pdf=0;}
  }
#else
	if(prt_levbon=='J') {ft_prt();prt_KOPIE+=1;}
  if(prt_error){errnum=13;goto endsr;}
	if(prt2pdf==2) {MailDocument(0);prt2pdf=0;}
#endif
#endif

  scrget(1,7);scrupd(-3,0);
  if(free!=-1){

#if FICHEEXEC
		fasunlck(-2);
    if(stock_JN=='J' || stock_JN=='S'){
#if STATISTIEK
      statistiek_upd(NO);
#endif
#if HISTORIEK
      historiek_upd();
#endif
#if ARTEXIST && (!BONFILE || !STOCK244)
      if(art_exist && stock_JN=='J') art_stat();
#endif
      if(k_omz_exist) klt_stat();
    }
#endif
    if(chk_nr || !bkh_exist){
			FactuurTotalen.ft_nr=ft_nr; // pas als alles OK is
      last_vf=*u(8,2);
      sysput(last_vfa,2,&last_vf);
    }
		ClearSysPosNrCheck();
    sysflush();fasflush(0);
  }
	write_bon();
#if KORT_DELAYED
  if(*f(8,21) && *f(2,50)){
    if(*f(8,21)<*f(2,50)) *f(2,50)-=*f(8,21);
    else *f(2,50)=0;
    fasupd(2);
  }
#endif
  
  fuval=YES;
endsr:;
	ClearSysPosNrCheck();
  retcall=fuval;
  ovlexit(-1);
}
#endif

#if FLAG244 && MAILREST/* stuur mail van gesplitst gedeelte */
							
static char seqo_str[1000];
static long seqo_pos;
static int16 seqo_len,SeqiMode,pos;

static out_t_mai()
{
  int16 n,len_,jj_,mm_,dd_,j,k;
  char mailnam[80];
  long dt_key;
							
/* eerst uitschrijven naar .MAX, en indien klaar renamen naar MAI  */
  p_data=s(80,1)+4;
  jddate(*u(25,2),&jj_,&mm_,&dd_);dt_key=dd_;
  fasinit(80);fasinfo(80,202); dt_key=dt_key*100000+*l(80,1);
  mk_name(4341,"out\\");
  for(n=0;n<60;n++) if(filnam[n]=='\0') break;
  zero(mailnam,sizeof mailnam);
  mailnam[0]='T';stcli_d(&mailnam[1],dt_key,7,0);copy(".MAX",&mailnam[8],5);
  for(n=0;n<60;n++) if(filnam[n]=='\0') break;
  scopy0(mailnam,&filnam[n]); 
  errnum=fasopen(filnam,2);if(errnum) goto endsr;

  fasinit(80);seqo_pos=0;pos=0;SeqiMode=2;
  pos=scopy0("#mailtoaddr=",seqo_str);
  pos+=scopy0(s(2,21),&seqo_str[pos]);
  dump_rec();
  pos=scopy0("#mailfromaddr=",seqo_str);
  pos+=scopy0(&firma[firm[7].begpos],&seqo_str[pos]);
  dump_rec();
  pos=scopy0("#mailsubject=Uw bestelling van ",seqo_str);
  jddate(*u(8,8),&jj_,&mm_,&dd_);
  stcli_d(&seqo_str[pos],(long)dd_,2,0);pos+=2;seqo_str[pos++]='/';
  stcli_d(&seqo_str[pos],(long)mm_,2,0);pos+=2;seqo_str[pos++]='/';
  stcli_d(&seqo_str[pos],(long)jj_,4,0);pos+=4;
  pos+=scopy0(" : niet voorradige producten",&seqo_str[pos]);
  dump_rec();dump_rec();
  pos=scopy0("Beste klant,",seqo_str);
  dump_rec();dump_rec();
  pos=scopy0("Helaas kunnen we bovenvermelde bestelling niet volledig uitvoeren.",seqo_str);
  dump_rec();dump_rec();
  pos=scopy0("Volgende artikel(s) zullen ontbreken bij de volgende levering :",seqo_str);
  dump_rec();dump_rec();
  for(k=0;k<max_line;k++){/* lege lijnen terug schrappen */
    ram2stu(k);
    if(*ps_58_16){/* indien omschrijving */
      pos=scopy0("      ",seqo_str);
      if(*f(58,7)){
	stcli_d(&seqo_str[pos],(long)(*f(58,7)),5,1);pos+=5;
      }
      else pos+=scopy0("     ",&seqo_str[pos]);
      if(*ps_58_62=='S') pos+=scopy0(" stk ",&seqo_str[pos]);
      else if(*ps_58_62=='P') pos+=scopy0(" pal ",&seqo_str[pos]);
      else pos+=scopy0("     ",&seqo_str[pos]);
      pos+=scopy0(ps_58_15,&seqo_str[pos]);seqo_str[pos++]=' ';
      j=0;if(*ps_58_16=='*') j=1;
      pos+=scopy0(ps_58_16,&seqo_str[pos]);
      dump_rec();
    }
  }
  dump_rec();
  for(k=0;k<4;k++){
    if(opm_foot[k][0]!='\0'){
      pos=scopy0(opm_foot[k],seqo_str); dump_rec();
    }
  }
  dump_rec();

  pos=scopy0("Gelieve deze opnieuw te bestellen bij Uw volgende order.",seqo_str);
  dump_rec();dump_rec();
  pos=scopy0("Dank U",seqo_str);
  dump_rec();
  fasflush(0);
  fasclos(-2);
/* nu renamen van MAX naar .MAI */
  for(n=0;n<60;n++) if(filnam[n]=='\0') break;
  n=scopy0(filnam,mailnam);
  filnam[n++]='|';len_=scopy0(mailnam,&filnam[n]);
  filnam[n+len_-1]='I';
  fasclos(-2);
  fasopen(filnam,100);
  endsr:;
}

static dump_rec()
{
  int16 k;
 
  CnvJamaChar(seqo_str,pos,0);/* convert jamascii to std-ascii */
  seqo_str[pos++]=0x0D;seqo_str[pos++]=0x0A;
/* artikel dumpen */
  seqo_len=0;
  for(k=0;k<pos;k+=280){
    if((k+280)>pos) seqo_len=pos-k;
    else seqo_len=280;
    copy(&seqo_str[k],s(80,1)+4,seqo_len);
    seqo_flush();
  }
  zero(seqo_str,sizeof seqo_str);pos=0;
}
 
static scopy0(ps,pd)
char *ps,*pd;
{
  int16 fuval=0;
		
  while(*ps){
    *pd++=*ps++;
    fuval++;
  }
  *pd='\0';
  return fuval;
}

static seqo_flush()
{
  if(seqo_len){
    fasseqo(80,2,seqo_len+4);
    seqo_pos+=seqo_len;
    *l(80,1)=seqo_pos;
    seqo_len=0;
  }
}
#endif
 

static load_sysnr(just_blok)
int16 just_blok;
{
  int16 sec_=0,k,busy_proc,last_proc_=0;
	char cmd_str_[100],postnaam_[30];
                                                            
  if((upd_mode==NO && chk_nr) || just_blok){
    FOREVER{
redo_wait:;
			sysflush();
      sysget(SysPosNrCheck,2,&busy_proc);
      if(busy_proc && busy_proc!=procid) {
				if(busy_proc!=last_proc_){
					zero(cmd_str_,sizeof cmd_str_);zero(postnaam_,sizeof postnaam_);
					k=copy0("GetIniKeyValue|Post-",&cmd_str_[0],50);
					stcli_d(&cmd_str_[k],(long)(1+busy_proc/5),3,0);k+=3;
					k+=copy0("_Settings|Name",&cmd_str_[k],50);
					ExecJmsCommand(postnaam_,25,cmd_str_);
					last_proc_=busy_proc;
				}
#if FLAG248
        sprintf(buf1000,"       Factuurnummer bezet door %s (Post-%d, Scherm-%d)",postnaam_,1+(busy_proc/5),busy_proc%5);
#else
				sprintf(buf1000,"       Bonnummer bezet door %s (Post-%d, Scherm-%d)",postnaam_,1+(busy_proc/5),busy_proc%5);
#endif
        scrget(1,170);
        scrifld(10,fm_os79,buf1000);
        scrifld(14,fm_os79,"                          Even geduld a.u.b.");
#if KAS2JMCFACTUUR | KAS2JMCBON   // scherm laten wijzigen om de 2 seconden zodat kassa niet op timeout gaat
				if((sec_%2)==0) scrifld(1,fm_ou5,&sec_);
#endif
        scrupd(-3,0);
        _sleep(1000);sec_++;
      }
      else{
				sysput(SysPosNrCheck,2,&procid);
				sysflush();
				if(just_blok==NO) sysget(last_vfa,2,&last_vf);
				for(k=0;k<10;k++){
					sysget(SysPosNrCheck,2,&busy_proc);/* dubbele check */
					if(busy_proc!=procid) goto redo_wait;
				}
				break;
      }
    }
  }
}

static ClearSysPosNrCheck()
{
  int16 busy_proc;
	  
	sysget(SysPosNrCheck,2,&busy_proc);
  if(busy_proc==procid){busy_proc=0;sysput(SysPosNrCheck,2,&busy_proc);}
}


static select_mnt()
{
  if(len8_23) copy(ps_8_23,ft_munt,3);
  if(ft_munt[0]=='\0') copy(def_munt,ft_munt,3);
  errnum=0;
  valu_cnv(ft_munt,def_munt,1.,1.);
  if(errnum) copy(def_munt,ft_munt,3);
  if(cmpstr(ft_munt,"BEF",3) || cmpstr(ft_munt,"EUR",3)==0){
    copy(fmeobd,fm_obd,sizeof fmeobd);
    copy(fmeobdk,fm_obdk,sizeof fmeobdk);
    copy(fmeobdk1,fm_obdk1,sizeof fmeobdk1);
    copy(fmeobdk2,fm_obdk2,sizeof fmeobdk2);
    ft_afrond=0.01; vm_munt=YES;
  }
  else{
    copy(fmfobd,fm_obd,sizeof fmfobd);
    copy(fmfobdk,fm_obdk,sizeof fmfobdk);
    copy(fmfobdk1,fm_obdk1,sizeof fmfobdk1);
    copy(fmfobdk2,fm_obdk2,sizeof fmfobdk2);
    ft_afrond=1.; vm_munt=NO;
  }
}

static calc()
{
  int16 j,k,reken_lgg_;
  BEDRAG belastb_,tot_incl=0,tot_dif,lin_incl,kort_,ori_belastb_,ori_belastbtot_;
  float prx_,prx1_,bdf_,bd_accijn=0,prx_r,tot_afh_los,lg_btw_=0;
  flag tot_chk=YES;
  uint16 rec_,rec_lg_=0;

	select_mnt();
  tot_gewicht=0;tot_kort=0;tot_leeg=0;semestbd=0;tot_AKWgoed=0;winst_pc=0;tot_subs=0;KM_heffing=0;
  tot_promo=0;trans_kost=0;tot_accijns=0;ori_belastbtot_=0;
  zero((char *)&cent[0].eenh[0],sizeof cent);
  zero((char *)btw_bas,sizeof btw_bas);winst_bd=0;
  zero((char *)incl_bas,sizeof incl_bas);winst_bd=0;
  zero((char *)&kort_btw[0],sizeof kort_btw);
//	if(fldlen(2,128) && *s(2,128)=='P' && *s(2,21)) tot_chk=NO;// niet bij electronische facturatie, want dan kan UBL fout zijn
#if KM_HEFFING || LEVERINGSKOST
	if(fldlen(8,46)) KM_heffing=*f(8,46);
#endif
#if SUBSIDIE 
	copy(s(2,1),buf1000,fldlen(2,0));
#if !FLAG248 // controleren op subsidieadres bij bons als het bestaat 
	if(fldlen(2,52)==2 && *u(2,52) && *u(2,52)!=*u(2,1)){
		rec_=*u(2,1);
		*u(2,1)=*u(2,52);fasgeti(2);
		copy(s(2,1),buf1000,fldlen(2,0));
		fasinit(2); *u(2,1)=rec_;fasgeti(2);
	}
#endif
#if FLAG248 && !FT_HERAFDRUK & !FACT_RISTOURNO
	if(orig_klt && orig_klt!=*u(2,1)) {// controleren op originele klant
		rec_=*u(2,1);
		fasinit(2); *u(2,1)=orig_klt;fasgeti(2);
	  if(fldlen(2,52)==2 && *u(2,52) && *u(2,52)!=*u(2,1)){ // op subsidieklant van origineel als ie bestaat
		  *u(2,1)=*u(2,52);fasgeti(2);
		}
		copy(s(2,1),buf1000,fldlen(2,0));
		fasinit(2); *u(2,1)=rec_;fasgeti(2);
	}
#endif
#endif
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(test_line()==NO){
      rec_=*pu_58_1;init58(k,YES);ram2stu(k);*pu_58_1=rec_;
    }
#if FT_HERAFDRUK && KORTTOT/* correctie bij kassa-facturen */
    if(*d(58,42)==0 && *pd_58_35) *d(58,42)=*pd_58_35;
#endif
#if !FT_HERAFDRUK
    *pf_58_31=*f(58,7);
    if(fldlen(58,8)){
#if DRI_flag
      if(*f(58,8)) *pf_58_31*=*f(58,8);
#else
      if(*ps_58_62=='P' && *f(58,8)) *pf_58_31*=*f(58,8);
#endif
    }
#if FLAGTHE
		if(*f(58,9))  *pf_58_31*=*f(58,9); // lm
#endif
#endif
#if QNUL
    if(*pf_58_31==0) *pf_58_31=1;
#endif
    if(fldlen(58,12)){
      for(j=0;j<20;j++){
	if(cent[j].q_bak==0 && cent[j].q_fles==0) break;
	if(cmpstr(s(58,12),cent[j].eenh,fldlen(58,12))==0) break;
      }
      if(j<20){
	copy(s(58,12),cent[j].eenh,fldlen(58,12));
	if(len58_62 && *ps_58_62=='S') cent[j].q_fles+=*pf_58_31;
	else cent[j].q_bak+=*pf_58_31;
      }
    }
    if(fldlen(58,47)){
#if KASINPUT | FT_HERAFDRUK
      tot_leeg+=*f(58,47);/* NIET uitrekenen, maar totaal nemen */
#else
			reken_lgg_=YES; 
#if !KAS2JMCFACTUUR && !KAS2JMCBON // bij kassafactuur altijd leeggoed tellen omdat kassa dat niet weet
			if(fldlen(2,34) && *s(2,34)=='J') reken_lgg_=NO; 
#endif
#if FLAGDBT || FLAGDCQ || FLAGCRA
			if(reken_lgg_ || *u(58,14)==*u(58,48)) *f(58,47)=*f(58,46)* *pf_58_31* *f(58,49); // geen leeggoed : GEKOPPELD totaal 0 maken. om toch in statistiek te krijgen
#else
			if(reken_lgg_) *f(58,47)=*f(58,46)* *pf_58_31* *f(58,49); // geen leeggoed : totaal 0 maken. om toch in statistiek te krijgen
#endif
#if FLAGSTO
			else{
				if(*u(58,14)==*u(58,48)) *f(58,47)=*f(58,46)* *pf_58_31* *f(58,49); // leeggoed wel tellen indien leeggoed artikel
			  else *f(58,47)=0;
			}
#else
			else *f(58,47)=0;
#endif
      tot_leeg+=*f(58,47);
#if DRI_flag
      if(*f(58,47) && rec_lg_==0){
	rec_lg_=*u(58,48);
	fasinit(6);*u(6,1)=rec_lg_;fasgeti(6);
	lg_btw_=*f(6,28);
      }
#endif
#endif
    }
    tot_afh_los=0;
#if AFHAALVERG
    if(fldlen(58,56)){
#if !FT_HERAFDRUK
      *f(58,56)=*f(58,55)* *pf_58_31;
#endif
      tot_afh_los+=*f(58,56);
    }
#endif
#if LOSVERGOED
    if(fldlen(58,59)){
      if(*pf_58_20){
#if !FT_HERAFDRUK
	*f(58,59)=*f(58,58)* *pf_58_31;
#endif
	tot_afh_los+=*f(58,59);
      } else *f(58,59)=0;
    }
#endif

#if PALET_KORTING
#if NO // FLAGPED
    if(fldlen(58,68) && *i(58,34)!=99){
      *f(58,68)=(*f(58,70)-*f(58,71))* *pf_58_31;
      if(*s(58,27)=='J') *f(58,68)/=1.+*pf_58_24/100.;
      tot_afh_los+=*f(58,68);
    }
#else
    if(fldlen(58,69)){
#if !FT_HERAFDRUK
      *f(58,68)=*f(58,67)* *pf_58_31;
#endif
      tot_afh_los+=*f(58,68);
    }
#endif
#endif
    prx_=*pf_58_20;
#if FLAGSEG
    prx_-=*f(58,22);/* korting in geld */
#endif
#if FLAGDUB  || FLAGSEG || FLAGFLI
    if(fldlen(58,60) && *s(58,60)=='J' && *pf_58_31){/* ehprijs = totaal bedrag */
      prx_/= *pf_58_31;
    }
#endif
    if(*i(58,34)==99) prx_=0;
#if BTWINCL
    lin_incl=round((double)(prx_* *pf_58_31)); tot_incl+=lin_incl;
    if(fldlen(58,27)){
      if(*s(58,27)=='J') prx_/=1.+*pf_58_24/100.;
      else if(test_line() && lin_incl) tot_chk=NO; // indien excl. lijn MET bedrag dan controle stoppen 
    }
/* tot_chk=NO;    anders wordt leeggoed afgerond ! */
#if !FT_HERAFDRUK
    if(fldlen(58,23)) *f(58,23)=prx_;
#endif
#endif
#if FLAGDU3 /* gratis artikels de accijns toch rekenen */
    if(prx_==0 && *i(58,34)!=99) prx_=*f(58,38);
#endif
#if FLAGTOL // geen rekening houden met accijns
		bd_accijn=0;
#else
    bd_accijn=*f(58,38);
#endif
    if(prx_>=0){/* bedrag accijns mag niet groter zijn de ehpr */
      if(bd_accijn>prx_) bd_accijn=prx_;
    }
    else {
      bd_accijn=-bd_accijn;
      if(bd_accijn<prx_) bd_accijn=prx_;
    }
#if NO // FLAGPED
    prx_=prx_-*f(58,70) + *f(58,71);          /* paletkorting + toeslag bak */
    if(*f(58,70)!=0 || *f(58,71)!=0) tot_chk=NO;
#endif
    prx_r=prx_;
#if !FT_HERAFDRUK
    if(fldlen(58,97)){/* tussenkomst brouwerij */
      *f(58,97)=0;
      if(fldlen(58,95)) *f(58,97)=(prx_r-bd_accijn)* *f(58,95)/100.;/* % */
      if(fldlen(58,96)) *f(58,97)+=*f(58,96);/* kort bd */
      *f(58,97)*=*pf_58_31;/* totale tussenkomst */
/*  *f(58,97)=valu_cnv(def_munt,def_munt,(double)(*f(58,97)),(double)0.01); */
    }
#endif
    if(fldlen(58,21)){
#if KORTTOT & !FT_HERAFDRUK
      *l(58,39)=valu_cnv(ft_munt,def_munt,(double)(prx_* *pf_58_31),(double)1.);
      bdf_=0.00001; if((prx_* *pf_58_31)<0) bdf_=-bdf_;/* correct afronding */
      if(fldlen(58,42)) *d(58,42)=valu_cnv(ft_munt,ft_munt,(double)(prx_* *pf_58_31+bdf_),ft_afrond);
#endif
#if (FLAG244 | FLAG252) & NO_BONKORT
#if SMT_flag/* selectief voor 1 klant */
      if(*s(2,66)=='J')
#endif
#if NWL_flag/* selectief per klant */
      if(*s(2,42)!='J')
#endif
      goto no_k_perc;
#endif
#if (FLAG244 | FLAG252) & KORT_DELAYED
      if(fldlen(2,49) && *s(2,49)=='J') goto no_k_perc;
#endif
      if(*pf_58_21){
#ifdef ALB_flag
	if(*s(2,71)=='J') prx_=prx_ * (100.- *pf_58_21)/100.;
	else
#endif
#if FLAGDSV
	bdf_=1. + *pf_58_21/100.;
	if(bdf_) prx_=(prx_-bd_accijn)/bdf_+bd_accijn;
#else
	prx_=(prx_-bd_accijn)*(100.- *pf_58_21)/100.+bd_accijn;
#endif
#if FLAGVVL
	prx_=(long)(prx_*100+.5)/100.;
#endif
#if BTWINCL
	if(prx_)tot_chk=NO;
#endif
      }
#if EXTEND_KORT
      for(j=0;j<10;j++){
				if(prx_ && *(s(8,53)+j)=='J'){/* 53+54 als 1 string genomen */
#if !FT_HERAFDRUK
				if(j<5) bdf_=(prx_-bd_accijn)* *f(58,102+j*3)/100.;
				else bdf_=*f(58,102+j*3);
				*f(58,103+j*3)=bdf_* *pf_58_31;
#endif
	  tot_afh_los+=*f(58,103+j*3);
	} else *f(58,103+j*3)=0;
      }
#endif
      if(fldlen(58,36) && prx_>0){
				bdf_=*f(58,36);
				if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
				prx_-=bdf_;
      }
      no_k_perc:;
#if FACT_PROMO
      bdf_=prx_;
      if(*f(58,91)){
				prx_=(prx_-bd_accijn)*(100.- *f(58,91))/100.+bd_accijn;
      }
      if(prx_>0) prx_-=*f(58,92); // niet bij gratis 
      *f(58,94)=(bdf_-prx_)* *pf_58_31;
      tot_promo+=*f(58,94);
#if BTWINCL
      if(*f(58,94)) tot_chk=NO;
#endif
#endif
#if !FLAGSEG
      if(fldlen(58,22)){
	*f(58,22)=prx_r-prx_;
#if FLAGVVL
	*f(58,22)=(long)(*f(58,22)*100+.5)/100.;
#endif
      }
#endif
    }
    *f(58,52)=(prx_r-prx_)* *pf_58_31;
#ifdef ALB_flag
    if(*s(2,71)=='J') *f(58,53)=(prx_r * *pf_58_31)* *f(58,43)/100.;
    else
#endif
    *f(58,53)=((tot_afh_los+((prx_-bd_accijn)* *pf_58_31)))* *f(58,43)/100.;
#if !FT_HERAFDRUK
    if(fldlen(58,37) && prx_>0){
      bdf_=*f(58,37) * *pf_58_31;
      if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
      *f(58,53)+=bdf_;
    }
#endif
    *f(58,53)=round((double)(*f(58,53)));
    semestbd+=*f(58,53);
    bdf_=0.00001; if((prx_* *pf_58_31)<0) bdf_=-bdf_;/* correct afronding */
    belastb_=round((double)((prx_* *pf_58_31+bdf_)+tot_afh_los));
    tot_accijns+=bd_accijn* *pf_58_31;
    if(fldlen(58,41)){
      bdf_=*f(58,41) * *pf_58_31;
      if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
#if KAS2GROOTH
      if(*i(58,34)!=99)
#endif
	tot_AKWgoed+=bdf_;
    }
#if DISKIMME
		ori_belastb_=belastb_;
    if(fldlen(2,14)==4) bdf_=*f(2,14); else bdf_=*i(2,14);
    if(bdf_){
      belastb_=round((double)belastb_*(1.-bdf_/100.));
    }
		
#endif
    j=btw_tab((BEDRAG)belastb_);
    if(fldlen(58,33)) *s(58,33)=j+btw_kol;
    btw_bas[j]+=belastb_;
#if BTWINCL
    incl_bas[j]+=lin_incl;
#endif
    *pd_58_35=belastb_;
#if DISKIMME
		*pd_58_35=ori_belastb_; // toch brutobedrag op factuur, in parlay extra lijn disconto
		ori_belastbtot_+=ori_belastb_;
#endif
/*  *pl_58_32=valu_cnv(ft_munt,def_munt,(double)belastb_,(double)1.); */
#if TRANS_KOST
#if FLAGALS
    if(*l(58,26) && (fldlen(2,49)==0 || *s(2,49)!='J')){ // vraag GEEN handlingkost tellen
      for(j=0;j<8;j++) if(*l(58,26)==hk_omzgrb[j]) break;
      if(j<8){
	       j=0; if(*s(2,48)!='A') j=1; // if(*s(2,26)!='0') j=1;
				 if(*s(8,31)=='N') bdf_=hk_pct[j][1]; else bdf_=hk_pct[j][0];
	       if(*f(58,31)<0) trans_kost-=*pd_58_35 * bdf_/100.; else trans_kost+=*pd_58_35 * bdf_/100.; // bij terugname ook handlingkost tellen
      }
    }
#else
    if((*pd_58_35 || *i(58,34)==99) && *ps_58_16!='*' && *pu_58_14 && *ps_58_62!='P'){
      fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
      bdf_=*pf_58_31* *f(6,84);
      if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
      if(*f(58,31)<0) trans_kost-=bdf_; else trans_kost+=bdf_; // bij terugname ook handlingkost tellen
      if(fldlen(8,31) && *s(8,31)!='J') trans_kost=0;/* geen rekenen */
    }
#endif
#endif
#if KORTTOT
#if LEN_flag
    if(*ps_58_62!='S' && *i(58,34)!=99 && *pu_58_14 && *ps_58_16!='*'){
      fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
      j=*s(2,26)-'0';
      if(j<0 || j>9) j=0;
      if(fldlen(6,PrNrs[j])==0) j=0;
      prx1_=*f(6,PrNrs[j]);
/*  prx1_=valu_cnv(def_munt,ft_munt,(double)(*f(6,PrNrs[j])),prx_afrond); */
      if(*s(58,27)=='J') prx1_/=1.+*pf_58_24/100.;
      if(prx1_>prx_){
	*d(58,42)=round((double)(prx1_* *pf_58_31));
	*f(58,52)=*d(58,42)-*pd_58_35;
      }
    }
#endif
    j=btw_tab((BEDRAG)belastb_);
		kort_=*d(58,42)-*pd_58_35; kort_=round(kort_);
    kort_btw[j]+=kort_; //*d(58,42)-*pd_58_35;
    tot_kort+=kort_; // *d(58,42)-*pd_58_35;
#endif
    if(fldlen(58,13)){
      bdf_=*pf_58_31* *f(58,13);
      if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
      tot_gewicht+=bdf_;
    }
#if SUBSIDIE
#if !FT_HERAFDRUK
    if(buf1000[s(2,39)-s(2,1)]=='J' && *pu_58_14 && *ps_58_16!='*'){
      for(j=0;j<fldlen(2,120)/2;j++) if(*pu_58_14==*(uint16 *)(&buf1000[s(2,120)-s(2,1)+j*2])) break;
      if(j<fldlen(2,120)/2 || fldlen(2,120)==0){
				fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
				bdf_=*pf_58_31;
				if(len58_62){
					if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
				}
				bdf_*=*f(6,37);
				*f(58,29)=valu_cnv(def_munt,ft_munt,(double)(*f(6,65)*bdf_),prx_afrond);
				tot_subs+=*f(58,29);
      } else *f(58,29)=0;
    }
#else
		tot_subs+=*f(58,29);
#endif
#endif
    stu2ram(k);
  }

#if TRANS_KOST/* transactie-kost aan 21% goederen tellen */
  if(trans_kost){
    trans_kost=round((double)trans_kost);
    fasinit(58); belastb_=trans_kost;
    *pf_58_24=def_btw;
    if(*s(8,26)=='J') *pf_58_24=0;
    j=btw_tab((BEDRAG)belastb_);
    btw_bas[j]+=belastb_;
    tot_chk=NO;
  }
#endif
#if LEVERINGSKOST || (KM_HEFFING && !FLAGAST) /* transactie-kost aan 21% goederen tellen */
  if(KM_heffing){
    KM_heffing=round((double)KM_heffing);
    fasinit(58); belastb_=KM_heffing;
    *pf_58_24=BtwLeveringskost;
    j=btw_tab((BEDRAG)belastb_);
    btw_bas[j]+=belastb_;
    tot_chk=NO;
  }
#endif
#if DRI_flag/* verpakking 21% als goederen tellen */
  if(tot_leeg){
    tot_leeg=round((double)tot_leeg);
    fasinit(58);*f(58,24)=lg_btw_; belastb_=tot_leeg;
    j=btw_tab((BEDRAG)belastb_);
    if(fldlen(58,33)) *s(58,33)=j+btw_kol;
    btw_bas[j]+=belastb_;
    tot_chk=NO;
  }
#endif
  belastbt=0;
  for(k=0;k<BTWDIM-BTWDIV;k++){
#if BTWINCL
    if(tot_chk){
//      btw_bas[k]=round((double)(incl_bas[k]/(1.+btw_pct[k]/100.)));
    }
#endif
    belastbt+=btw_bas[k];
  }
  btw_tot=0;
  for(k=0;k<BTWDIM;k++){
    btw_bd[k]=round((double)(btw_bas[k]*btw_pct[k])/100.);
    btw_tot+=btw_bd[k];
  }
  tot_leeg=round((double)tot_leeg);
  tot_accijns=round((double)tot_accijns);
  tot_subs=round((double)tot_subs);
  tot_incl+=tot_leeg-tot_subs;
  alg_tot=belastbt+btw_tot+tot_leeg-tot_subs;
  belastb_=tot_AKWgoed; if(sys3586==1) belastb_=belastbt;
  if(fldlen(58,41) && belastb_){
    winst_pc=((belastbt-tot_AKWgoed)/ belastb_)* 100.;
    winst_bd=belastbt-tot_AKWgoed;
  }
#if DRI_flag/* verpakking zit al in belastbaar */
  alg_tot-=tot_leeg;
#endif
#if BTWINCL
  if(tot_chk){
    tot_dif=tot_incl-alg_tot;
		tot_dif=round(tot_dif);
    if(tot_dif){/* eerst proberen op default btw % */
			for(k=0;k<BTWDIM;k++) if(!is_nul(round((double)(incl_bas[k]-btw_bd[k]-btw_bas[k]))))  break;
  //    for(k=0;k<BTWDIM;k++) if(btw_bd[k] && btw_pct[k]==def_btw) break;
      if(k>=BTWDIM){
				for(k=0;k<BTWDIM;k++) if(btw_bd[k] && btw_pct[k]!=0) break;
      }
      if(k<BTWDIM){
        int kk_,bestidx_; double bestres_,res_,linc_,factor_;
        btw_bas[k]+=tot_dif;
        /* lijnniveau-correctie: zet de afrondingscent op de lijn met de grootste
           afrondingsrest (rond-naar-beneden) ipv enkel op de groepstotalen, zodat
           de som van de lijnen exact het Jamadata-totaal geeft en de UBL geen
           aparte "Afronding"-lijn nodig heeft */
        bestidx_=-1; bestres_=-1.e9;
        for(kk_=0;kk_<max_line;kk_++){
          ram2stu(kk_);
          if(test_line()==NO) continue;
          if(*i(58,34)==99 || is_nul((double)(*d(58,35)))) continue;
          if(btw_tab((BEDRAG)(*d(58,35)))!=k) continue;
					factor_=1.; if(*d(58,35)<0) factor_=-1.;
          linc_=round((double)(*f(58,20) * *f(58,31)))*factor_;
          res_=linc_/(1.+ *f(58,24)/100.) - *d(58,35)*factor_;
          if(res_>bestres_){bestres_=res_; bestidx_=kk_;}
        }
        if(bestidx_>=0){
          ram2stu(bestidx_); 
					*d(58,35)+=tot_dif; 
					if(*f(58,31) && *f(58,21)==0) *f(58,23)=valu_cnv(def_munt,def_munt,(double)(*d(58,35)/ *f(58,31)),prx_afrond); // ehprijs ook corrigeren
					stu2ram(bestidx_);	
				}
      }
      belastbt+=tot_dif;
      alg_tot+=tot_dif;
    }
  }
#endif
#if KM_HEFFING && FLAGAST // dit is als het buiten BTW is
	alg_tot+=KM_heffing;
#endif
  kredietbp_bd=0; 
#if KREDIETBEPERK
	bdf_=0;
  if(alg_tot>0 &&  *s(8,22)!='J' && (fldlen(8,21)==0 || *f(8,21)<alg_tot)){
#ifdef KREDIETBP_PCT
		bdf_=KREDIETBP_PCT;
#else 
		if(fldlen(2,14)){
			 if(fldlen(2,14)==4) bdf_=*f(2,14); else bdf_=*i(2,14);
		}
#endif
#if FLAGQIC
		if(fldlen(2,44) && *s(2,44)!='J') bdf_=0; // J = WEL kredietbeperking
#else
		if(fldlen(2,44) && *s(2,44)=='J') bdf_=0; // GEEN kredietbeperking
#endif
		kredietbp_bd=round((double)(alg_tot* bdf_)/100.);
	}
#endif
  disk_bd=0;
#if DISCONTO
  if(len2_14 && (alg_tot>0)){
    if(fldlen(2,14)==4) bdf_=*f(2,14); else bdf_=*i(2,14);
#if FLAGPMC
		bdf_=4.; // VAST 4% kredietbeperking 
#endif
    disk_bd=alg_tot;
    if(disk_ei) disk_bd-=(btw_tot + tot_leeg);
#if DISKIMME
		disk_bd=ori_belastbtot_;
#endif
#if DISC_NOACC
    disk_bd-=tot_accijns;
#endif
    disk_bd=round((double)(disk_bd* bdf_)/100.);
    if(disk_bd<0) disk_bd=0;
  }
#endif
#if KASINPUT
	if(*s(8,22)!='J' && is_nul(valu_cnv(ft_munt,"EUR",(double)(alg_tot-*f(8,21)),(double)0.05))) *s(8,22)='J'; // om cash-afronding weg te doen
#endif
  if(cmpstr(ft_munt,"EUR",3)){
    ealg_tot=valu_cnv(ft_munt,"EUR",(double)alg_tot,(double)0.01);
  } else ealg_tot=0;
}

static fill_astock()/* fill actuele stock in */
{
  int16 k,mode_=1,muteer_=NO,fnr_;
  uint16 rec58_,arec_;
  float stock_,qlv_,factor_=1.;
 
  if(test_line()==NO || *ps_58_16=='*'){stock_=0;goto endsr;}
 
  copy(s(58,1),sortbuf,fldlen(58,0)); 
  copy(s(8,1),buf1000,fldlen(8,0));
	fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6); arec_=*u(6,1); factor_=*f(6,31);if(factor_==0) factor_=1.;
	if(fldlen(6,102) && *u(6,102)){ // stock van moederfiche nemen
		*u(6,1)=*u(6,102); 
		if(fasgeti(6)==0) {
			arec_=*u(6,1); if(*f(6,31)) factor_= *f(6,31)/factor_;
		}
		else {fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6); arec_=*u(6,1);factor_=1;}
	} else factor_=1.;
#if STOCK_OP_LOCATIE
#if FLAGAST
	if(DefaultFiliaal==0 || DefaultFiliaal==99){
		for(k=0;k<10;k++) if(orig_klt==loc_klt[k]) break;
		if(k<10 && loc_nr[k]) muteer_=YES;
	}
#endif
  if(muteer_==NO && fldlen(8,48) && filiaal>0 && filiaal<=10){
		fasinit(66);*u(66,2)=arec_;faskeyi(66,1,0);
    stock_=*f(66,11+(filiaal-1)*15)*factor_;goto calc_bonstock;
  }
#endif    
  stock_=*f(6,33)*factor_; 
#if FLAGCHA // controle doen op minimumstock
  stock_-=*f(6,36);
#endif
	calc_bonstock:;
	rec58_=*pu_58_1;
#if !STOCK244
  fasinit(58);*u(58,14)=*u(6,1);mode_=1;
  FOREVER{
    next:;
    if(faskeyi(58,2,mode_)) break; mode_=2;
    if(*u(58,14)!=*u(6,1)) break;
    if(*pu_58_1==rec58_) goto next;
    fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);

#if FLAGGRS || FLAGCRA // geen rekening houden met bestelde goederen
		if(*u(8,36) && *u(8,36)==10) goto next;
#endif
#if BACKORDER
    if(*u(8,36) && *u(8,36)!=10 && *u(8,36)!=20) goto next;
#endif
		fnr_=3;
#if STOCK_OP_LOCATIE
		if(*u(8,36)==20){ // stockmutatie
  		if(filiaal>0 && filiaal<=10){
				if(*u(8,3)==filiaal) fnr_=3;
				else if(*u(8,38)==filiaal) fnr_=38;
				else goto next; // geen van filiaal of naar filiaal
			}
			else{
				if(*u(8,3)<1 && *u(8,3)>10) fnr_=3;
				else if(*u(8,38)<1 && *u(8,38)>10) fnr_=38;
				else goto next; // geen van filiaal of naar filiaal
			}
		}
		else {
 		  if(filiaal>0 && filiaal<=10){
				if(*u(8,48)!=filiaal)  goto next; // geen van filiaal of naar filiaal
			}
			else{
				if(*u(8,48)>0 && *u(8,48)<=10) goto next;
			}
		}
#endif
    qlv_=*pf_58_31;
    if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) qlv_/=*f(58,63);
		if(fldlen(8,36)){
			if(*u(8,36)==20){ // mutatiebon
				if(fnr_==3) stock_+=qlv_*factor_; // mutatie naar dit filiaal
				else stock_-=qlv_*factor_; // mutatie van dit filiaal naar ander filiaal
			}
			else if(*u(8,36)==10) stock_+=qlv_*factor_; // bestelbons leveranciers bijtellen
			else stock_-=qlv_*factor_; // leveringsbons
		}
    else stock_-=qlv_*factor_;
  }
  copy(sortbuf,s(58,1),fldlen(58,0));
  copy(buf1000,s(8,1),fldlen(8,0));
#endif
  endsr:;
  if(fldlen(58,100)) *f(58,100)=stock_;
}
 
#if (FLAG244 & SPLITS_BON) | FLAG241
static chk_qlv()
{
  int16 k,fuval=NO;
  flag pos_;
  float qlv_,oqlv_;

  for(k=0;k<max_line;k++){
    ram2stu(k);
#if !SAMENVOEGEN
    *f(58,61)=0;
    if(*pu_58_1){
#else
    if(*pu_58_14 && *ps_58_16){
#endif
      pos_=YES;
      if(*ps_58_16=='\0') qlv_=0;/*  lijn geschrapt */
      else {
	qlv_=*pf_58_31;
#if SAMENVOEGEN
	oqlv_=*f(58,61);
#else
	fasgeti(58);oqlv_=*pf_58_31;
#endif
	pos_=YES;if(oqlv_<0) pos_=NO;
	qlv_-=oqlv_;
	ram2stu(k);
	*f(58,61)=0;
      }
      if((pos_==YES && qlv_<0) || (pos_==NO && qlv_>0)){
	fuval=YES;
	*f(58,61)=qlv_;
      }
    }
    stu2ram(k);
  }
  return fuval;
}

static add_kontb(j)
int16 j;
{
  int16 k,kk;
  uint16 rec_r;
  float aant_r,bd_r;
  char stk_r='\0',stk_='\0';

  for(k=0;k<max_line;k++){
    fasinit(58);*u(58,2)=*u(8,1);*u(58,3)=k;
    if(faskeyi(58,1,0)==0){
      stu2ram(j);
      rec_r=*pu_58_14;aant_r=*f(58,7);if(len58_62) stk_r=*ps_58_62;
      bd_r=*pd_58_35;
      if(rec_r){
	for(kk=0;kk<j;kk++){
	  ram2stu(kk);
	  if(len58_62) stk_=*ps_58_62;
	  if(rec_r==*pu_58_14 && stk_==stk_r){
	    *f(58,7)=*f(58,7)+aant_r;stu2ram(kk);
#if !SPLITS_KAS_PR
	    bd_r+=*pd_58_35;/* de eh.prijs als gemiddelde nemen */
	    if(*f(58,7) && *i(58,34)!=99){
	      *pf_58_20=bd_r/ *f(58,7);
	      *pf_58_21=0;*s(58,27)='N';
	    }
	    *pd_58_35=bd_r;
#endif
	    stu2ram(kk);
	    init58(j,NO); j--;
	    break;
	  }
	}
      }
      j++;
    }
  }
  init58(j,NO);
  keepdata=YES;
}
 
static test_kontb(pos_)/* testen of er een bon bestaat met voldoende plaats */
int16 pos_;
{
  float aant_r;
  uint16 rec_r;
  int16 j,k,kk,mode_;
  char stk_='\0',stk_r='\0';
 
  fasinit(8);*u(8,3)=*pu_2_1;mode_=1;
  FOREVER{
    next:;
    if(faskeyi(8,1,mode_)) return YES; mode_=2;
    if(*u(8,3)!=*pu_2_1) return YES;
    mode_=2;
#if BACKORDER
    if(*u(8,36)) goto next;
#endif
#if FLAGEPD
		if(*u(8,8)!=*u(25,2)) goto next; // 1 bon per dag
#endif
    j=pos_;
    for(k=0;k<max_line;k++){
      fasinit(58);*u(58,2)=*u(8,1);*u(58,3)=k;
      if(faskeyi(58,1,0)==0){
#if TICKETAPART // altijd toevoegen
				j++;
#else
				rec_r=*pu_58_14;aant_r=*f(58,7); if(len58_62) stk_r=*ps_58_62;
				if(rec_r){
					for(kk=0;kk<j;kk++){
						ram2stu(kk);
						if(len58_62) stk_=*ps_58_62;
						if(rec_r==*pu_58_14 && stk_r==stk_) break;
					}
					if(kk>=j) j++;
				}
				else j++;
#endif
      }
      if(j>=max_line) break;
    }
#if FLAGHOE
	  if(j<100) break; // gesplitste bon mag max 100 lijnen zijn 
#else
		if(j<max_line) break;
#endif
  }
  return NO;
}

static write_konb()
{
  int16 g,k;
  uint16 rec_,rec8_;
	
	fasunlck(-2);
  *u(8,3)=*pu_2_1;
	if(fldlen(8,11)) *d(8,11)=alg_tot;
  if(*u(8,1)){
		if(fldlen(8,71)) *u(8,71)=procid;
		if(fldlen(8,72)) *u(8,72)=*u(25,2);
		g=fasupd(8); 
	}
	else{
		if(fldlen(8,70)) *u(8,70)=procid;
		if(fldlen(8,72)) *u(8,72)=*u(25,2);
		g=fasadd(8);
	}
  rec8_=*u(8,1);
  if(errnum==0) errnum=g;
  for(k=0;k<max_line;k++){
    fasinit(58);*u(58,2)=rec8_;*u(58,3)=k;
    if(faskeyi(58,1,0)==0) faskill(58);
    ram2stu(k); *pu_58_1=0;/* bon uit fas deleten en ram adden */
    if(*ps_58_16 || *pu_58_14){
      *u(58,2)=rec8_;
      *u(58,3)=k;
      if(fldlen(58,61)) *f(58,61)=*pf_58_31;
      g=fasadd(58);
    }
    if(errnum==0) errnum=g;
  }
  fasflush(0);
}
#endif

#if ARTEXIST
static get_prx(mode) // mode = NO : leeggoed 
int16 mode;
{
  int16 j,k,m,pos_,vpos_=0;
  float kort_=0,vp_=0,vpn_,vpp_,k_fr_=0,acc_,qlv_;
  flag aant_flag;
  uint16 pr_klt_;
 
  pr_klt_=*pu_2_1;
#if USE_FTAFSPR
  if(fldlen(2,51) && *u(2,51)) pr_klt_=*u(2,51);
#endif
  pos_=0;vpos_=0; PrijsDatum=*u(6,11);
	if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(8,8)) {pos_=94;vpos_=10;PrijsDatum=*u(6,105);}
  newkort=NO;nokort=NO;calc_kort=0;calc_sem=-99;brij_tpct=0;brij_tbd=0;
  hl_korting=0;hl_semkort=0; calc_defprx=0;

#if LASTPRX
  if(calc_prx==0){
    fasinit(10);*u(10,2)=pr_klt_+30000;vp_=0;
    FOREVER{
      if(faskeyi(10,2,2)) break;
      if(*u(10,2)!=pr_klt_+30000) break;
      if(*u(10,3)==*pu_6_1) {vp_=*f(10,7);kort_=0;}
    }
    if(vp_) {newkort=YES;goto endsr;}
  }
#endif
	if(fldlen(6,104) && *s(6,104)=='J') nokort=YES;
  *u(52,1)=*i(6,9);
  vp_=0;aant_flag=NO;kort_=0;
  if(fldlen(6,PrNrs[vpos_])) vp_=*f(6,PrNrs[vpos_]);
  if(fasgeti(52)==0){
    for(j=0;j<5;j++){
      if(fldlen(52,15+j)>0){
	if(*s(52,15+j)=='>'){
	  if(*f(58,7)<val(s(52,15+j)+1)) break;
	  vp_=*f(6,PrNrs[1+vpos_+j]);aant_flag=YES;
	}
      }
    }
    if(fldlen(52,21) && *s(52,21)=='N') nokort=YES;
    if(aant_flag) {newkort=YES;goto vp_ok;}
  }
	if(UseAKPrijs){
		vp_=*f(6,18+pos_);
#if FLAGEET
		if(*i(6,9)!=99) vp_=round((double)(vp_*1.02)); // AKprijs steeds 2% winstnemen
#endif
#if FLAGSAS
		if(*i(6,9)!=99) vp_=round((double)(vp_*1.01)); // AKprijs steeds 1% winstnemen
#endif
	}
  else {
#if FLAGWLM || FLAGDCP // kassa stuksprijs nemen indien kassaprijs
    if(mode && len58_62 && *ps_58_62=='S' && *f(58,63)!=0 && prxnr==KassaPrxNr) vp_=*f(6,PrNrs[vpos_+KassaPrxNrStuk])* *f(58,63);
		else
#endif
  		vp_=*f(6,PrNrs[vpos_+prxnr]);
	}
	calc_defprx=vp_;
  vp_ok:
#if CONTRACT
  fasinit(9);*u(9,2)=pr_klt_;*u(9,3)=*pu_6_1;
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
    if(fldlen(9,72) && *u(9,72) && *u(9,72)<=*u(8,8)){
      if(*f(9,75)) vp_=*f(9,75);
      if(*f(9,73)) kort_=*f(9,73);
      if(*f(9,74)) k_fr_=*f(9,74);
      if(fldlen(9,81)) hl_korting=*f(9,81);
      if(fldlen(9,82)) hl_semkort=*f(9,82);
      calc_sem=*f(9,76); PrijsDatum=*u(9,72);
    }
    else{
      if(*f(9,8)) vp_=*f(9,8);
      if(*f(9,6)) kort_=*f(9,6);
      if(*f(9,7)) k_fr_=*f(9,7);
      if(fldlen(9,20)) hl_korting=*f(9,20);
      if(fldlen(9,21)) hl_semkort=*f(9,21);
      calc_sem=*f(9,22);
    }
    if(fldlen(9,23)) brij_tpct=*f(9,23);
    if(fldlen(9,24)) brij_tbd=*f(9,24);
    if(fldlen(9,88)){/* contrakt afhank. van het aantal */
      qlv_=*f(58,7);
      if(len58_62 && fldlen(58,8)){
				if(*ps_58_62=='P' && *f(58,8)) qlv_*=*f(58,8);
      }
      k=0;
      for(k=0;k<9;k++){
				if(fldlen(9,88+k*5) && *f(9,88+k*5)){
					if(qlv_<*f(9,88+k*5)) break;
				}
				else break;
			}
			k--;
			if(k>=0){
				kort_=0;vp_=0;k_fr_=0;
				if(*f(9,92+k*5)) vp_=*f(9,92+k*5);
				if(*f(9,89+k*5)) kort_=*f(9,89+k*5);
				if(*f(9,91+k*5)) k_fr_=*f(9,91+k*5);
				calc_sem=*f(9,90+k*5);
				if(fldlen(9,72) && *u(9,72) && *u(9,72)<=*u(8,8)){
					if(fldlen(9,77+k)) vp_=*f(9,77+k);
				}
      }
    }
    newkort=YES;
  }
#endif
endsr:;
#if FLAGSCP
	if(*s(58,62)=='S') {
		kort_=0;k_fr_=0; calc_kort=0;calc_sem=-99;brij_tpct=0;brij_tbd=0; hl_korting=0;hl_semkort=0;
		nokort=YES;
	}
#endif
	acc_=*f(6,30);
#if FT_ACC_FREE
	if(fldlen(2,88) && *s(2,88)=='J'){
		vp_-=acc_;acc_=0;
	}
#endif
  if(fldlen(52,23) && *s(52,23)=='J' && kort_){
#ifdef ALB_flag
    if(*s(2,71)=='J') acc_=0;
#endif
    k_fr_+=(vp_-acc_) * kort_/100.; kort_=0;
  }
#if !FLAGEPD && !FLAGVDW && !FLAGDLA// EUR korting als hl-korting gebruiken
  if(k_fr_) vp_-=k_fr_;
#endif
  if(mode && len58_62){
    if(*ps_58_62=='S' && *f(58,63)!=0){
#if FLAG241
      if(prxnr<8) vp_=*f(6,PrNrs[prxnr+1]);
      else vp_/=*f(58,63);
#else
      vp_/=*f(58,63); calc_defprx/=*f(58,63);
#if FLAGVDW // flessen 10% bijtellen
			if(*f(58,63)>1) vp_*=1.1;
#endif
#if FLAGEBO // flessen 5% bijtellen
			if(*f(58,63)>1) vp_*=1.05;
#endif
#if FLAGJRN // flessen 5 cent 
			if(*f(58,63)>1) vp_+=0.05;
#endif
#if FEC_flag/* stuksprijs = type 1 */
      if(prxnr==3) vp_/=*f(58,63);
      else vp_=*f(6,21+1);
#endif
#endif
    }
  }
  calc_kort=kort_;
	calc_defprx=valu_cnv(def_munt,ft_munt,(double)calc_defprx,prx_afrond);
  calc_prx=valu_cnv(def_munt,ft_munt,(double)vp_,prx_afrond);
  calc_kfr=valu_cnv(def_munt,ft_munt,(double)k_fr_,prx_afrond);
  if(fldlen(6,37)==0 || *f(6,37)==0){hl_korting=0;hl_semkort=0;}
  else{/* omrekenen naar verpakking */
#if !FLAGABT // bij ABT is hl-korting steeds per bak en niet per hl
    hl_korting=hl_korting* *f(6,37)/100;
    hl_semkort=hl_semkort* *f(6,37)/100;
#endif
  }
#if FLAGEPD ||  FLAGVDW ||  FLAGDLA// EUR korting als hl-korting gebruiken
	hl_korting+=calc_kfr;calc_kfr=0;
#endif
}
#endif

#if BOEKALLO & BOEKEXEC
static boekbkh()
{
  int16 g,j,k,jj,pgrb_defbtw;
	uint16 changed_,searcnr, mode_,bonnr_,ref_yy,dum1,dum2;
  long rekenc;
  double bd_,bd_verg_=0,tot_verg_=0,bd1_;
  char munt_[4],str_[10];

	fasunlck(-2);
	bkhref_ftnr=0;
#if FLAGABT && FLAG248 && !FT_HERAFDRUK
  if(alg_tot<0) AskFtReferentie();
#endif
#if INTRASTAT
  zero((char *)&bkh_intras[0],sizeof bkh_intras);
#endif
  zero((char *)&bedrag[0],sizeof bedrag);
  zero((char *)&grb_tb[0],sizeof grb_tb);
  zero((char *)&opmhoev[0],sizeof opmhoev);
#if BONFILE & BONR2BKH
  copy(strblist,opm_bkh,sizeof opm_bkh);
#endif
#if ALB_flag || FLAGLAT || FLAGPSN /* indien lev.klant anders dan in opmerking zetten */
  if(cmpstr(ps_2_3,s(8,14),20))
	  copy(s(8,14),opm_bkh,20);
#endif
#if FLAGABT
	if(*s(8,50)) copy(s(8,50),opm_bkh,20);
  else copy(s(8,17),opm_bkh,20);
#endif
#if FLAGCRL
  copy(s(8,25),opm_bkh,20);
#endif
#if FLAGVBE
  copy(FtPdfFilename,opm_bkh,20);
#endif
	if(fldlen(2,42) && *s(2,42)=='J' && cmpstr(ps_2_3,s(8,14),20)) copy(s(8,14),opm_bkh,20); // bij feestklant de naam in opmerking zetten 
  j=1;
#if 0
#if KORTTOT & KORTBKH
  if(!is_nul((double)tot_kort)){
    bedrag[j]=tot_kort;rec_nr[j]=df_recnr[14];
    grb_tb[j]=*(long *)&df_rek[14][0];
    j++;
  }
#endif
#endif
#if TRANS_KOST
  if(!is_nul(trans_kost)){
    bedrag[j]=-trans_kost;
#if FLAGALS
    if(*s(2,48)=='A') rekenc=hk_kostgrb[0]; else rekenc=hk_kostgrb[1];
    if(sear_grb(rekenc)==60000){errnum=0;rekenc=grb_notf;}
    rec_nr[j]=sear_grb(rekenc);
    grb_tb[j]=rekenc;
#else
    rec_nr[j]=df_recnr[14];
    grb_tb[j]=*(long *)&df_rek[14][0];
#endif
    j++;
  }
#endif

#if (AFHAALVERG | LOSVERGOED) & VERGOEDBKH
  if(!is_nul((double)tot_afh_los)){
    bedrag[j]=tot_afh_los;rec_nr[j]=df_recnr[14];
    grb_tb[j]=*(long *)&df_rek[14][0];
    j++;
  }
#endif
#if DISKIMME
  if(!is_nul((double)disk_bd)){
    bedrag[j]=-disk_bd;
		rec_nr[j]=df_recnr[6];
    grb_tb[j]=*(long *)&df_rek[6][0];
    j++;
  }
#endif
#if FLAGDMS // ristourno boeken op 499100 (D) en 499200 (C) buiten BTW
  if(!is_nul(tot_kort)){
    bedrag[j]=tot_kort;grb_comp("499100",&rekenc);
    rec_nr[j]=sear_grb(rekenc);
    grb_tb[j]=rekenc;
    j++;
		bedrag[j]=-tot_kort;grb_comp("499200",&rekenc);
    rec_nr[j]=sear_grb(rekenc);
    grb_tb[j]=rekenc;
    j++;
  }
#endif
#if KREDIETBEPERK && KREDIETBP_BKH /* kredietbeperking boeken op disconto-rekening */
  if(!is_nul((double)kredietbp_bd)){
    bedrag[j]=-kredietbp_bd;rec_nr[j]=df_recnr[6];
    grb_tb[j]=*(long *)&df_rek[6][0];
    j++;
  }
#endif
#if KM_HEFFING || LEVERINGSKOST /* km-heffing boeken op def_grb[15] */
  if(!is_nul((double)KM_heffing)){
    bedrag[j]=-KM_heffing;rec_nr[j]=df_recnr[15];
    grb_tb[j]=*(long *)&df_rek[15][0];
    j++;
  }
#endif
#if FLAGGSN //  kredietbeperking als disconto 
  if(!is_nul((double)disk_bd)){
    bedrag[j]=-disk_bd;rec_nr[j]=df_recnr[6];
    grb_tb[j]=*(long *)&df_rek[6][0];
    j++;
  }
#endif

  if(!is_nul((double)tot_subs)){
    bedrag[j]=tot_subs;
    rec_nr[j]=df_recnr[13];grb_tb[j]=*(long *)&df_rek[13][0];
    j++;
  }

  if(!is_nul((double)tot_leeg)){
    bedrag[j]=-tot_leeg;
    rec_nr[j]=df_recnr[12];grb_tb[j]=*(long *)&df_rek[12][0];
    j++;
	}
#if FLAGKMP  // voorraad leeggoed afboeken
	if(!is_nul((double)tot_leeg)){ // leeggoedwaarde afboeken
    bedrag[j]=tot_leeg;
		grb_comp("709900",&rekenc);
		grb_tb[j]=rekenc;
    if( (rec_nr[j]=sear_grb(rekenc)) ==60000){
      errnum=0;
      rec_nr[j]=sear_grb(grb_notf);
      grb_tb[j]=grb_notf;
    }
    j++;
    bedrag[j]=-tot_leeg;
		grb_comp("310000",&rekenc);
		grb_tb[j]=rekenc;
    if( (rec_nr[j]=sear_grb(rekenc)) ==60000){
      errnum=0;
      rec_nr[j]=sear_grb(grb_notf);
      grb_tb[j]=grb_notf;
    }
    j++;
	}
	if(!is_nul((double)tot_AKWgoed)){ // stockwaarde afboeken
    bedrag[j]=tot_AKWgoed;
		grb_comp("709400",&rekenc);
		grb_tb[j]=rekenc;
    if( (rec_nr[j]=sear_grb(rekenc)) ==60000){
      errnum=0;
      rec_nr[j]=sear_grb(grb_notf);
      grb_tb[j]=grb_notf;
    }
    j++;
    bedrag[j]=-tot_AKWgoed;
		grb_comp("340000",&rekenc);
		grb_tb[j]=rekenc;
    if( (rec_nr[j]=sear_grb(rekenc)) ==60000){
      errnum=0;
      rec_nr[j]=sear_grb(grb_notf);
      grb_tb[j]=grb_notf;
    }
    j++;
	}
#endif
  bedrag[j]=-btw_tot;
  rec_nr[j]=df_recnr[1];grb_tb[j]=*(long *)&df_rek[1][0];
  jj=j+1; pgrb_defbtw=0;
  for(k=0;k<max_line;k++){
    ram2stu(k);
#if LEN_flag
    if(*pl_58_32 || *d(58,42) || (len58_35 && *pd_58_35)){
#else
    if(*pd_58_35){
#endif
#if FT_HERAFDRUK
			if(fldlen(58,25)){
  			if(*u(58,14)){
					fasinit(6);*u(6,1)=*u(58,14); fasgeti(6);
					*s(58,25)=*s(6,39);
				}
			  if(*s(58,25)=='\0') *s(58,25)='0'; // bij inlezen facturen, indien dit een nieuw veld is, default 0
			}

#endif
      rekenc=makegrb();
      if(sear_grb(rekenc)==60000){errnum=0;rekenc=grb_notf;}
      for(g=2;g<EL_BKH;g++){
	if(rekenc==grb_tb[g]){
#if INTRASTAT
	  if(cmpstr(s(58,30),(char *)&bkh_intras[g].stelsel,16)==0 && cmpstr(s(58,30)+32,(char *)&bkh_intras[0].staat_ori,2)==0)
#endif
	    break;
	}
      }
      if(g==EL_BKH){
	for(g=2;g<EL_BKH;g++){
	  if(is_nul((double)bedrag[g])){
	    grb_tb[g]=rekenc;
	    if( (rec_nr[g]=sear_grb(rekenc)) ==60000){
	      errnum=0;
	      rec_nr[g]=sear_grb(grb_notf);
	      grb_tb[g]=grb_notf;
	    }
			else if(pgrb_defbtw==0 && *f(58,24)==def_btw) pgrb_defbtw=g; // default rekening bijhouden voor verschillen
#if INTRASTAT
	    copy(s(58,30),(char *)&bkh_intras[g].stelsel,16);
			if(fldlen(4,57)){ copy(s(58,30)+32,bkh_intras[g].staat_ori,2); if(bkh_intras[g].staat_ori[0]=='\0') copy("BE",bkh_intras[g].staat_ori,2); }
#endif
	    break;
	  }
	}
      }
      bd_=*pd_58_35;
#if DISKIMME  // verlaagd bedrag nemen
    if(fldlen(2,14)==4) bd1_=*f(2,14); else bd1_=*i(2,14);
    if(bd1_){
      bd_=round((double)bd_*(1.-bd1_/100.));
    }
#endif



#if KORTTOT & KORTBKH
      if(fldlen(58,42)) bd_=*d(58,42);
      else bd_=*l(58,39);
#endif
#if (AFHAALVERG | LOSVERGOED) & BOEK_VERG
      bd_verg_=0;
      if(fldlen(58,56) && *f(58,56)) bd_verg_+=*f(58,56);
      if(fldlen(58,59) && *f(58,59)) bd_verg_+=*f(58,59);
      bedrag[g]+=bd_verg_;tot_verg_+=bd_verg_;
#endif
      bedrag[g]-=bd_;opmhoev[g]+=*pf_58_31;
#if INTRASTAT
      bkh_intras[g].gewicht+=p_intras->gewicht;
      bkh_intras[g].aanveenh+=p_intras->aanveenh;
#endif
    }
  }
#if (AFHAALVERG | LOSVERGOED) & BOEK_VERG
  if(!is_nul(tot_verg_)){
    for(k=1;k<EL_BKH;k++) if(is_nul((double)bedrag[k])) break;
    if(k<EL_BKH){
      bedrag[k]-=tot_verg_;rec_nr[k]=df_recnr[14];
      grb_tb[k]=*(long *)&df_rek[14][0];
    }
  }
#endif
#if KORTTOT & KORTBKH
  for(j=0;j<BTWDIM;j++){
    if(!is_nul(kort_btw[j])){
      rekenc=*(long *)&df_rek[14][0];
      zero(str_,sizeof str_);
#if FLAGSMM
			if(*s(2,22)) copy("701900", str_,6);
			else grb_deco(str_,&rekenc);
#else
      grb_deco(str_,&rekenc);
#endif
      for(k=0;k<8;k++) if(str_[k]=='\0') break; k-=2; if(k<0) k=0;
      stcli_d(&str_[k],(long)(btw_pct[j]),2,0);
#if FT_ACC_FREE
	  	if(fldlen(2,88) && *s(2,88)=='J'){ // aparte rekening boeken (71 of 701)
				for(g=0;g<6;g++) if(b3598[g]=='\0') break; g--;
#if FLAGSMM
        str_[2]='2'; 
#else 
	  		if(g>1) str_[g-1]='1';
#endif
  		}
#endif
      grb_comp(str_,&rekenc);
      if(sear_grb(rekenc)==60000){errnum=0;rekenc=*(long *)&df_rek[14][0];}
      for(k=1;k<EL_BKH;k++) if(is_nul((double)bedrag[k])) break;
      if(k<EL_BKH){
	grb_tb[k]=rekenc;rec_nr[k]=sear_grb(rekenc);
	rec_nr[k]=sear_grb(rekenc);
	bedrag[k]=kort_btw[j];
      }
    }
  }
#endif
  for(k=1;k<EL_BKH;k++) bedrag[0]-=bedrag[k];
	bd1_=alg_tot;
#if DISKIMME
	bd1_+=disk_bd;/* correctie alg_tot */
#endif
#if KREDIETBEPERK && KREDIETBP_BKH
	bd1_+=kredietbp_bd;/* correctie alg_tot */
#endif
//#if KM_HEFFING
//	bd1_+=KM_heffing;/* correctie alg_tot */
//#endif
#if FLAGGSN // || FLAGPMC
  bd1_+=disk_bd;/* correctie alg_tot */
#endif
  bd_=bedrag[0]-bd1_;
  if(!is_nul(bd_)){
		if(pgrb_defbtw && !is_nul(bedrag[pgrb_defbtw])) k=pgrb_defbtw; // proberen op default BTW
		else{
      for(k=jj;k<EL_BKH;k++) if(!is_nul((double)bedrag[k])) break;/* liefst goederen */
      if(k==EL_BKH) for(k=1;k<jj;k++) if(!is_nul((double)bedrag[k])) break;
		}
    bedrag[k]-=bd1_-bedrag[0];
    bedrag[0]=bd1_;
  }
  rec_nr[0]=*u(2,1)+30000;
  omzet=0;for(k=jj;k<EL_BKH;k++) omzet-=bedrag[k];
  boek();
#if FLAGEPD & BONFILE // betalingen gefactureerde bons switchen naar deze factuur
  copy(s(8,1),buf1000,fldlen(8,0));searcnr=orig_klt+30000;
  for(jj=0;jj<DIM8;jj++){
    if(rec_8[jj]==0) break;
    fasinit(8);*u(8,1)=rec_8[jj];fasgeti(8);
		FOREVER{
		  fasinit(4); *u(4,5)=searcnr;mode_=1; changed_=NO;
			FOREVER{
				if(faskeyi(4,4,mode_)) break; mode_=2;
				if(*u(4,5)!=searcnr) break;
				if(*s(4,8)!=0 || *s(4,9)!=0 || *u(4,10)!=0) break;
				if(cmpstr(s(4,28),"BON",3)==0){// betaling bon 
					j=0; zero(str_,sizeof str_);
					for(k=0;k<6;k++){
						if(*(s(4,28)+3+k)<'0' || *(s(4,28)+3+k)>'9') {
							if(j) break;
						}
						else str_[j++]=*(s(4,28)+3+k);
					}
					bonnr_=val(str_);
					if(*u(8,2)==bonnr_){
						*u(4,5)=*u(2,1)+30000; 
						*l(4,6)=kltcent;
						jddate(ft_date,&ref_yy,&dum1,&dum2);
						*s(4,8)=ref_yy%100; if(*s(4,8)<50) *s(4,8)+=100;           /* y2000 */
						*s(4,9)=journl;
						*u(4,10)=ft_nr;
						fasupd(4);changed_=YES; break;
					}
				}
			}
			if(changed_==NO) break;
		}
	}
	copy(buf1000,s(8,1),fldlen(8,0));
#endif
#if VOLD2KAS
  if(sys2170 && (*s(8,22)=='J' || *s(8,22)=='B')){
    boekkas();
		if(*s(8,22)=='J'){ // enkel bij geld, niet bij BC
			sysget(osalkasa,8,&osalkas);
			if(osalmunt=='E'){
				osalkas+=valu_cnv(ft_munt,"EUR",(double)bedrag[0],(double)0.01);
			}
			else{
				osalkas+=valu_cnv(ft_munt,def_munt,(double)bedrag[0],(double)1.);
			}
			sysput(osalkasa,8,&osalkas);
			sysflush();
		}
  }
#endif
}
#endif

#if BOEKALLO & BOEKEXEC
static boek()
{
  int16 k,g,opmnr=0,ref_yy,dum1,dum2,vm_;
  long bd_bef,tot_bef=0;
  double bd_eur,tot_eur=0,ebd_;
 
	fasunlck(-2);
  if(ft_munt[0]=='\0') copy(def_munt,ft_munt,3);
  vm_=YES;if(cmpstr(ft_munt,"EUR",3)==0 || cmp_str(ft_munt,def_munt,3)==0) vm_=NO;
  if(cmpstr(ft_munt,"EUR",3)==0 || cmpstr(def_munt,"EUR",3)==0) boekvalu='E';
  else boekvalu='F';
  for(g=0;g<EL_BKH;g++){
    if(!is_nul((double)bedrag[g]) || g==0){/* ook 0-facturen wegschrijven */
      initrec(4);
      bd_bef=valu_cnv(ft_munt,def_munt,(double)bedrag[g],(double)1.);
      bd_eur=valu_cnv(ft_munt,"EUR",(double)bedrag[g],(double)0.01);
      tot_bef+=bd_bef; tot_eur+=bd_eur;
      *l(4,7)=bd_bef; *d(4,32)=bd_eur;
      *u(4,5)=rec_nr[g];
      if(boekvalu=='E') *s(4,31)='E'; else *s(4,31)='F';
      if(rec_nr[g]<60000){
	*l(4,6)=kltcent;
	jddate(*u(4,4),&ref_yy,&dum1,&dum2);
	*s(4,8)=ref_yy%100; if(*s(4,8)<50) *s(4,8)+=100;           /* y2000 */
	*s(4,9)=journl;
	if(bkhref_ftnr==0) *u(4,10)=*u(4,3); else *u(4,10)=bkhref_ftnr;
	if(fldlen(4,13)) *l(4,13)=omzet;
	*d(4,33)=valu_cnv(ft_munt,"EUR",omzet,(double)0.01);
	if(fldlen(4,37)){
		if(*s(8,22)=='J' || ((alg_tot)-*f(8,21))==0) *u(4,37)=1;
	}
	for(k=0;k<5;k++){/* totalen onthouden voor externe bkh-pgm */
	  ebd_=valu_cnv(ft_munt,"EUR",(double)btw_bas[k],(double)0.01);
	  copy((char *)&ebd_,s(4,38)+k*8,8);
	}
	ebd_=valu_cnv(ft_munt,"EUR",(double)btw_tot,(double)0.01);
	copy((char*)&ebd_,s(4,38)+40,8);
	if(fldlen(4,15) && cmpstr(ft_munt,def_munt,3) && cmpstr(ft_munt,"EUR",3)){
	  copy(ft_munt,s(4,15),3);
	  *d(4,16)=alg_tot;
#if KREDIETBEPERK && KREDIETBP_BKH
		*f(4,17)=kredietbp_bd;
#else
	  *f(4,17)=disk_bd;
#endif
	}
      }
      else{
	*l(4,6)=grb_tb[g];
      }
      if(g==0){
	*u(4,20)=ft_date;
	*u(4,21)=verv_dt;
#if KREDIETBEPERK && KREDIETBP_BKH
	*u(4,22)=verv_dt;  // moet op vervaldatum
#else
	*u(4,22)=disk_dt;
#endif

#if KREDIETBEPERK && KREDIETBP_BKH
	*f(4,26)=kredietbp_bd;
	*d(4,34)=valu_cnv(ft_munt,def_munt,(double)kredietbp_bd,(double)0.01);
#else
	*f(4,26)=disk_bd;
	*d(4,34)=valu_cnv(ft_munt,def_munt,(double)disk_bd,(double)0.01);
#endif
	if(vm_) {copy(ft_munt,s(4,24),3); *d(4,25)=alg_tot;}
	else copy(def_munt,s(4,24),3);
      }

      if(g==0 || ((sys1787&0x20) && opmhoev[g])){
				if(g==0) copy(opm_bkh,s(4,28),20);
				else stcli_d(s(4,28),opmhoev[g],7,1);
#if FLAGWYN
				if(g==0) copy(s(8,24),s(4,28),20); // Uw referte om mee te geven aan Expert/M
#endif
#if FLAGREY
				if(g==0) copy(s(8,25),s(4,28),20); // Uw referte om mee te geven aan Expert/M
#endif
      }
#if BOEK_EXTERN
      if(*l(4,6)==*(long *)(&df_rek[1][0])){/* basistarieven BTW in btw-boeking zetten */
				for(k=0;k<5;k++){         /* totalen onthouden voor externe bkh-pgm */
					bd_bef=valu_cnv(ft_munt,def_munt,(double)btw_bas[k],(double)1.);
					copy((char *)&bd_bef,s(4,28)+k*4,4);
				}
      }
#endif
#if INTRASTAT
      copy((char *)&bkh_intras[g].stelsel,s(4,48),sizeof bkh_intras[0]);
#endif
			if(fldlen(4,60)) *u(4,60)=procid;
      errnum=fasadd(4);
    }
  }
#if (ANAL_ASK || ANAL_FILIAAL) & FLAG248 & !KASINPUT & !FT_HERAFDRUK
#if ANAL_FILIAAL // analytisch per filiaal 90FF
	a_rec_nr=0;a_grbrek=0; filiaal=*u(8,48);
	if(fldlen(8,48) && filiaal>0 && filiaal<=10){
		fasinit(3);	sprintf_s(s(3,3),10,"90%02d",filiaal);
		grb_comp(s(3,3),l(3,2)); if(faskeyi(3,1,0)==0){a_grbrek=*l(3,2);a_rec_nr=*u(3,1)+60000;}
	}
#endif
  if(a_rec_nr==0) goto no_anal;
  for(g=1;g<EL_BKH;g++){
    if(is_nul((double)bedrag[g])) continue;
    for(k=0;k<DF_GRB;k++) if(rec_nr[g]==df_recnr[k]) break;
    if(k<DF_GRB) continue;
    initrec(4);
    bd_bef=valu_cnv(ft_munt,def_munt,(double)bedrag[g],(double)1.);
    bd_eur=valu_cnv(ft_munt,"EUR",(double)bedrag[g],(double)0.01);
    *l(4,7)=bd_bef; *d(4,32)=bd_eur;
    *u(4,5)=a_rec_nr; *l(4,6)=a_grbrek;
    *l(4,11)=grb_tb[g];
    if(boekvalu=='E') *s(4,31)='E'; else *s(4,31)='F';
		if(fldlen(4,60)) *u(4,60)=procid;
    errnum=fasadd(4);
  }
  no_anal:;
#endif
}
#endif

#if BOEKALLO & BOEKEXEC & VOLD2KAS
static boekkas()
{
  int16 k,ref_yy,mm,dd;
  uint16 boekdt_;
  char bf750[750];

	fasunlck(-2);
  boekdt_=0;
#if FLAG248 & BONFILE & VOLD_BONDAT/* kasboeking op bondatum */
  copy(s(8,1),bf750,fldlen(8,0));
  for(k=0;k<DIM8;k++){
    if(rec_8[k]==0) break;
    fasinit(8);*u(8,1)=rec_8[k];fasgeti(8);
    if(*u(8,8)>boekdt_) boekdt_=*u(8,8);/* op datum recentste bon */
  }
  copy(bf750,s(8,1),fldlen(8,0));
#endif
  if(boekdt_==0) boekdt_=ft_date;

  initrec(4);
  *s(4,2)=kasjrnl;/* kasboeking */
  *u(4,4)=boekdt_;
  *l(4,7)=valu_cnv(ft_munt,def_munt,(double)bedrag[0],(double)1.);
  *d(4,32)=valu_cnv(ft_munt,"EUR",(double)bedrag[0],(double)0.01);
	if(*s(8,22)=='B'){ // betaald met bancontact
    *u(4,5)=rec_BCkas;  // GRB uit kasverslag (V.2.4)
    *l(4,6)=grb_BCkas;
	}
	else{
	  *u(4,5)=rec_kas;
    *l(4,6)=grb_kas;
	}
  if(boekvalu=='E') *s(4,31)='E'; else *s(4,31)='F';
  jddate(boekdt_,&ref_yy,&mm,&dd);
  if(kastype==4) *u(4,3)=mm*100+dd;
  else *u(4,3)=++last_17;
	if(fldlen(4,60)) *u(4,60)=procid;
  errnum=fasadd(4);
 
  *l(4,7)=-*l(4,7); *d(4,32)=-*d(4,32);/* klantboeking */
  *u(4,5)=30000+*pu_2_1;
  *l(4,6)=kltcent;
  *s(4,8)=ref_yy%100; if(*s(4,8)<50) *s(4,8)+=100;           /* y2000 */
  *s(4,9)=journl;
  *u(4,10)=ft_nr;
	if(fldlen(4,60)) *u(4,60)=procid;
  errnum=fasadd(4);
  sysput(last_17a,2,&last_17);
}
#endif

#if BONFILE
static kill()
{
  int16 k,mode_;

	fasunlck(-2);
  for(k=0;k<DIM58;k++){
    *pu_58_1=rec_58[k];
    if(*pu_58_1) faskill(58);
  }
  for(k=0;k<DIM8;k++){
    if(rec_8[k]){
      fasinit(58);*u(58,2)=rec_8[k]; mode_=1;
      FOREVER{/* nog eens extra controleren */
	if(faskeyu(58,1,mode_)) break; mode_=2;
	if(*u(58,2)!=rec_8[k]) break;
	faskill(58);
      }
      *u(8,1)=rec_8[k];faskill(8);
    }
  }
}
#endif

#if BONFILE & !KAS2BON
static load_bon(mode_,mode1) // mode_ YES=meerdere bons     mode1: YES=facturatie
int16 mode_,mode1;
{
  int16 g=0,k,j=0,h=0,kk,q_lines,pbl_,off_;
  uint16 mm,yy,dd,last_dt_,oklt_,rverv_dat_;
  flag first=YES,compress_,samenv_=NO,no_addlin_=NO;
  char last_vold=0xFF,last_mnt[3],last_8_31=0xFF,rlotnr_[40],rsscc_[20],nm_ft_klant_[50];
	float promo_rpr_,promo_rpct_,promo_rbd_;

  scrget(1,7);scrupd(-3,0);
#if FLAG248 && ADDLEVNAAM && BONFILE && !FT_HERAFDRUK 
  oklt_=*pu_2_1;
  if(fldlen(2,51) && *u(2,51) && sys3918==NO){/* vanaf nu in stu-2 het FACT-adres */
    *pu_2_1=*u(2,51);fasgeti(2);
  }
	copy(s(2,3),nm_ft_klant_,fldlen(2,3));
	fasinit(2);*u(2,1)=oklt_; fasgeti(2);
#endif

#if SAMENVOEGEN
  samenv_=YES;
#endif
#if FLAG248 && MULTIBON
	mode_=fl_multibon;
#endif
#if FLAG248/* indien diverse klant dan ALTIJD bon per bon factureren */
#if !FLAGEPD
  if(*u(2,1)==klt_div1 || *u(2,1)==klt_div2 || (fldlen(2,42) && *s(2,42)=='J')) mode_=NO;
#endif
#if MULTI_PER_KLT || ALB_flag || KAD_FLAG
    if(fldlen(2,37) && *s(2,37)=='J') mode_=NO;/* per bon factuur */
#endif
#endif
  if(fldlen(2,24)) taaltxt=*s(2,24);
  tot_voors=0;KM_heffing=0;last_mnt[0]=0xFF;
  zero(strblist,sizeof strblist); copy("BON",strblist,3);pbl_=3;
  zero((char *)&rec_8[0],sizeof rec_8);
  zero((char *)&rec_58[0],sizeof rec_58);
  FOREVER{
    if(first==NO){
      if(g==DIM8) break;
      if(faskeyi(8,1,2)) break;
    }
    if(*u(8,3)!=*u(2,1)) break;
		if(mode1){ // facturatie
      if(fldlen(8,30) && (*s(8,30)!='J' && SelectieAlleVoldaneBons!='J')) goto next;
		  if(fldlen(8,74) && OnlyKassaBons=='J' && *s(8,74)!=YES) goto next;
			if(SelectieAlleVoldaneBons=='J' && *s(8,22)!='J') goto next;
		}
#if BACKORDER
    if(*u(8,36)) goto next;
#endif
    if(dt_bon_beg && *u(8,8)<dt_bon_beg) goto next;
    if(dt_bon_end && *u(8,8)>dt_bon_end) goto next;
		if(InqBonNr && *u(8,2)!=InqBonNr) goto next; // met bonnummer opgeroepen, dan deze bon alleen
#if FLAG248
#if MULTIBON_SELECT 
		if(selrec8[0]!=0xFFFF){ // 0xFFFF = seriefacturatie
      for(k=0;k<DIM8;k++) if(selrec8[k]==*u(8,1)) break;
      if(k>=DIM8) goto next;
		}
#endif
    if(dt_bon_beg && *u(8,8)<dt_bon_beg) goto next;
    if(len8_23){
      if(last_mnt[0]==0xFF) copy(ps_8_23,last_mnt,3);
      if(cmpstr(ps_8_23,last_mnt,3)) goto next;
    }
    if(last_vold==0xFF){if(*s(8,22)=='J')last_vold='J'; else last_vold='N';}
    else {
      if(last_vold!=*s(8,22)) goto next;
    }
#if FLAGALS
    if(last_8_31==0xFF){if(*s(8,31)=='J')last_8_31='J'; else last_8_31='N';}
    else {
      if(last_8_31!=*s(8,31)) goto next;
    }
#endif
    if(dt_bon_end && *u(8,8)>dt_bon_end) break;
    if(mode_ && full_test(j,h)) break;
    if(first==NO) strblist[pbl_++]=',';
    dd=5; if(*u(8,2)<100) dd=3; else if(*u(8,2)<1000) dd=4;
    stcli_d(&strblist[pbl_],(long)(*u(8,2)),dd,1);if(pbl_<34) pbl_+=dd;
#endif
#if ADDLIN==NO || ADDORSEP || FLAGWYN
//#if FLAGWYN
//		if(fl_multibon==YES) goto no_add_nr;
//#endif
#if ADDORSEP
    if(fldlen(2,37)==0 || *s(2,37)=='J') goto no_add_nr;
#endif
#if FLAG248/* bonnummer toevoegen */
    
#if !NO_ADDBNR 
		if(first==NO){
			fasinit(58);*s(58,16)='*'; stu2ram(j++);
		}
#endif
#if FLAG248 && ADDLEVNAAM && BONFILE && !FT_HERAFDRUK 
		if(cmpstr(s(8,14),nm_ft_klant_,fldlen(8,14))){

			fasinit(58); *s(58,16)='*'; copy(s(8,14),s(58,16)+1,fldlen(58,16)-1);
			stu2ram(j++);
		}
#endif
		if(fldlen(8,61) && *u(8,61)==0) *u(8,61)=*u(8,2); // nodig voor peppol
		if(fldlen(8,62) && *u(8,62)==0) *u(8,62)=*u(8,8); // nodig voor peppol
		fasinit(58);
    mm=*u(8,2); off_=0;
		if(taaltxt==2)  copy("*Note ",ps_58_16,6);
    else copy("*Bon :",ps_58_16,6);
		stcli_d(ps_58_16+6,(long)mm,5,1);
#if FLAGSTN
		copy(" van/de ",ps_58_16+11,8); off_=3;
#else
    if(taaltxt==1) copy(" de  ",ps_58_16+11,5);
		else if(taaltxt==2) copy(" of  ",ps_58_16+11,5);
		else  copy(" van ",ps_58_16+11,5);
#endif		
#if ALB_flag
    copy("*Levering van ",ps_58_16,16);off_=-2;
#endif
    jddate(*u(8,8),&yy,&mm,&dd);
    stcli_d(ps_58_16+16+off_,(long)dd,2,0);*(ps_58_16+18+off_)='/';
    stcli_d(ps_58_16+19+off_,(long)mm,2,0);*(ps_58_16+21+off_)='/';
    stcli_d(ps_58_16+22+off_,(long)yy,4,0);
#if ALB_flag
    copy(ps_58_16,opm_foot[3],27);
#endif

#if NO_ADDBNR
    fasinit(58);
#endif
    stu2ram(j++);
#endif
    if(first==NO){
      fasinit(58); *s(58,16)='*';
      if(fldlen(8,25)){
				copy(s(8,25),s(58,16)+1,fldlen(8,25));
#if NO_ADDBNR
				stu2ram(j++);
#else
				if(*s(8,25)) stu2ram(j++);
#endif
      }
    }
#endif
    no_add_nr:;
    if(fldlen(8,21) && mode1) tot_voors+=*f(8,21);
#if KM_HEFFING || LEVERINGSKOST
		if(fldlen(8,46) && mode1) KM_heffing+=*f(8,46);
#endif
#if FLAG248 && (FLAGJRN || FLAGSAS)
    for(k=0;k<4;k++){
			if(fldlen(8,65+k) && *s(8,65+k)){
				for(mm=0;mm<4;mm++) if(opm_foot[mm][0]=='\0') break;
			  if(mm<4) copy(s(8,65+k),opm_foot[mm],fldlen(8,65+k));
			}
		}
#endif
#if STOCK_OP_LOCATIE
	if(fldlen(8,48)) filiaal=*u(8,48);
#endif
    rec_8[g++]=*u(8,1); q_lines=0;
    for(k=0;k<max_line;k++){
      fasinit(58);*u(58,2)=*u(8,1);*u(58,3)=k;
      if(faskeyi(58,1,0)) goto next_det;
      rec_58[h++]=*pu_58_1; q_lines++;
#if ARTEXIST
      *u(58,17)=hash();
#endif
#if (ADDLIN || ADDORSEP) && (FLAG248 || SAMENVOEGEN)
			if(*s(58,16)=='*' && fldlen(58,62) && *s(58,62)=='S') no_addlin_=YES;
#if ADDORSEP
      if(no_addlin_ || (fldlen(2,37) && *s(2,37)!='J')) {
#if FLAG248 & DEF_INPUT
	if(!(*pf_58_31==0 && *pu_58_14))
#endif
	stu2ram(j++);
	goto next_det;
      }
#endif
#if FACT_PROMO/* GEEN promoties samentellen */
      if(*f(58,94)){stu2ram(j++);goto next_det;}
#endif
      if(upd_mode==NO || samenv_){/* niet samentellen bij updating */
				stu2ram(j);
#if FACT_PROMO
        promo_rpr_=*f(58,90);promo_rpct_=*f(58,91);promo_rbd_=*f(58,92);				  
#endif				 
				prx_r=*pf_58_20;kort_r=*pf_58_21;rec_r=*pu_58_14;aant_r=*f(58,7);
				if(fldlen(58,62)) fles_r=*s(58,62);
				lgprx_r=*f(58,46);lgrec_r=*u(58,48);lgaant_r=*f(58,49);
#if NO // FLAGPED
			  pkrt_r=*f(58,70);tsl_r=*f(58,71);
#else
				if(fldlen(58,71)) copy(s(58,71),rlotnr_,fldlen(58,71));
#endif
#if TRACEERDATA 
				copy(s(58,138),rlotnr_,fldlen(58,138)); copy(s(58,139),rsscc_,fldlen(58,139));rverv_dat_=*u(58,137);
#endif
#if INTRASTAT
				copy(s(58,30),(char *)&bkh_intras[0].stelsel,sizeof bkh_intras[0]);
#endif
				if(rec_r==0) goto no_recr;
#if FLAG248 & DEF_INPUT
				if(aant_r==0) init58(j--,NO);/* lege lijnen overslaan */
				else {
#endif
#if FLAGPCQ
					no_addlin_=NO; // altijd samentellen
#endif
					kk=0;  if(no_addlin_) kk=j; // niet samentellen bij afgescheiden blokken (bv weborders)
					for(kk;kk<j;kk++){
						ram2stu(kk);
						compress_=YES;
						if(prx_r!=*pf_58_20 || kort_r!=*pf_58_21) compress_=NO;
#if NO // FLAGPED
						if(pkrt_r!=*f(58,70) || tsl_r!=*f(58,71)) compress_=NO;
#else
#if !FLAGDCN // niet kijken naar lotnr
				    if(fldlen(58,71) && cmpstr(s(58,71),rlotnr_,fldlen(58,71))) compress_=NO;
#endif
#endif
#if TRACEERDATA // geen verschillende traceerdata samentellen
//				    if(*u(58,136)!=rverv_dat_ || cmpstr(s(58,137),rlotnr_,fldlen(58,137))) compress_=NO;
						if(*u(58,137) || *s(58,138) || *s(58,139)) compress_=NO; // niet samenvoegen indien traceerdata
#endif
#if FACT_PROMO
            if(promo_rpr_!=*f(58,90) || promo_rpct_!=*f(58,91) || promo_rbd_!=*f(58,92)) compress_=NO;				  
#endif				 

						if(rec_r!=*pu_58_14 || lgprx_r!=*f(58,46)) compress_=NO;
						if(lgrec_r!=*u(58,48) || lgaant_r!=*f(58,49)) compress_=NO;
						if(fldlen(58,62) && *s(58,62)!=fles_r) compress_=NO;
#if INTRASTAT
				    if(cmpstr(s(58,30),(char *)&bkh_intras[0].stelsel,16)) compress_=NO;
						if(cmpstr(s(58,30)+32,(char *)&bkh_intras[0].staat_ori,2)) compress_=NO;
#endif
						if(compress_){
							*f(58,7)+=aant_r;
#if INTRASTAT
				      p_intras->gewicht+=bkh_intras[0].gewicht;
				      p_intras->aanveenh+=bkh_intras[0].aanveenh;
#endif
							stu2ram(kk);
							init58(j--,NO);
							break;
						}
					}
					*pu_58_1=rec_58[h-1];fasgeti(58);
#if FLAG248 & DEF_INPUT
				}
#endif
				no_recr:;
				j++;
      }
      else stu2ram(j++);
#else
#if FLAG248 & DEF_INPUT
      if(!(*pf_58_31==0 && *pu_58_14))
#endif
      stu2ram(j++);
#endif
      next_det:;
    }
    if(fldlen(8,5)){
      if(q_lines!=*u(8,5)) errnum=73;
    }
    if(mode_==NO) break;/* slechts 1 bon laden */
    next:;
    first=NO;
  }
  if(g==0) return NO;
  init58(j,NO);
  if(mode_){*u(8,1)=rec_8[0];fasgetu(8);}
  if(mode1 && fldlen(8,21)) *f(8,21)=tot_voors;
#if KM_HEFFING  || LEVERINGSKOST
		if(fldlen(8,46) && mode1) *f(8,46)=KM_heffing;
    if(*f(8,46)){
			fasinit(6);*u(6,1)=RecLevKostArt; 
			if(fasgeti(6)==0) BtwLeveringskost=*f(6,28);
			else BtwLeveringskost=def_btw;
			if(btw_glob!=99) *pf_58_24=btw_glob;
		}
#endif
#if SAMENVOEGEN
				      /* forceren om deze bon TOE TE VOEGEN */
  *u(8,1)=0; *u(8,8)=ft_date;
  for(j=0;j<max_line;j++){ram2stu(j);*u(58,1)=0;stu2ram(j);}
#endif
#if FLAG248 & ADD_LEV_DATUM
#if ADDLIN || ADDORSEP
#if ADDORSEP
    if(fldlen(2,37) && *s(2,37)!='J') goto no_add_levdate;
#endif
  copy(s(8,1),buf1000,fldlen(8,0));j=0;last_dt_=0;
  for(k=0;k<DIM8;k++){
    if(rec_8[k]==0) break;
    fasinit(8);*u(8,1)=rec_8[k];fasgeti(8);
		if(*u(8,8)==last_dt_) continue;
		last_dt_=*u(8,8);
    ins_lin(j);ram2stu(j);
    fasinit(58);
#if FLAGMOR
    mm=*u(8,2); 
    copy("*Bon :",ps_58_16,6);stcli_d(ps_58_16+6,(long)mm,5,1);
   	copy(" van ",ps_58_16+11,5);
    jddate(*u(8,8),&yy,&mm,&dd);
    stcli_d(ps_58_16+16,(long)dd,2,0);*(ps_58_16+18)='/';
    stcli_d(ps_58_16+19,(long)mm,2,0);*(ps_58_16+21)='/';
    stcli_d(ps_58_16+22,(long)yy,4,0);
#else
		copy("*Levering van ",ps_58_16,16);
    jddate(*u(8,8),&yy,&mm,&dd);
    stcli_d(ps_58_16+14,(long)dd,2,0);*(ps_58_16+16)='/';
    stcli_d(ps_58_16+17,(long)mm,2,0);*(ps_58_16+19)='/';
    stcli_d(ps_58_16+20,(long)yy,4,0);
#endif
    stu2ram(j++);
  }
  copy(buf1000,s(8,1),fldlen(8,0));
	no_add_levdate:;
#endif
#endif
  keepdata=YES;
  return YES;
}
#endif
 
#if (FLAG248 & BONFILE) | SAMENVOEGEN
static full_test(j,h)
int16 j,h;
{
  int16 k,kk;
  flag compress_;
 
  fasinit(58);
  for(k=0;k<max_line;k++){
    fasinit(58);*u(58,2)=*u(8,1);*u(58,3)=k;
    if(faskeyi(58,1,0)==0){
      h++; if(h>=DIM58) return YES;/* overflow record tabel */
#if ADDLIN || ADDORSEP
#if ADDORSEP
      if(fldlen(2,37) && *s(2,37)!='J') {
#if FLAG248 & DEF_INPUT
	if(!(*pf_58_31==0 && *pu_58_14))
#endif
	stu2ram(j++);
	goto next_det;
      }
#endif
      prx_r=*pf_58_20;kort_r=*pf_58_21;rec_r=*pu_58_14;aant_r=*f(58,7);
			if(fldlen(58,62)) fles_r=*s(58,62);
      lgprx_r=*f(58,46);lgrec_r=*u(58,48);lgaant_r=*f(58,49);
#if INTRASTAT
      copy(s(58,30),(char *)&bkh_intras[0].stelsel,sizeof bkh_intras[0]);
#endif
      if(rec_r){
	for(kk=0;kk<j;kk++){
	  ram2stu(kk);
	  compress_=YES;
	  if(prx_r!=*pf_58_20 || kort_r!=*pf_58_21) compress_=NO;
	  if(rec_r!=*pu_58_14 || lgprx_r!=*f(58,46)) compress_=NO;
	  if(lgrec_r!=*u(58,48) || lgaant_r!=*f(58,49)) compress_=NO;
		if(fldlen(58,62) && *s(58,62)!=fles_r) compress_=NO;
#if INTRASTAT
	  if(cmpstr(s(58,30),(char *)&bkh_intras[0].stelsel,16)) compress_=NO;
		if(cmpstr(s(58,30)+32,(char *)&bkh_intras[0].staat_ori,2)) compress_=NO;
#endif
	  if(compress_) break;
	}
	if(kk>=j) j++;
      }
      else
#if FLAG248 & DEF_INPUT
	  if(!(*pf_58_31==0 && *pu_58_14))
#endif
	   j++ ;
#else
#if FLAG248 & DEF_INPUT
	  if(!(*pf_58_31==0 && *pu_58_14))
#endif
      j++;
#endif
      next_det:;
      if(j>=(max_line-1)) return YES;
    }
  }
  return NO;
}
#endif
 
#if (FLAG244 & BONFILE) | KAS2BON
static write_bon()
{
  int16 g,k,q_lines;
  flag empty=YES;
  uint16 rec8_,rec_;
	char buf50_[50];

  fasunlck(-2);
	*u(8,3)=*u(2,1);errnum=0; q_lines=0;
  if(fldlen(8,11)) *d(8,11)=alg_tot;
	for(k=0;k<4;k++) copy(opm_foot[k],s(8,65+k),fldlen(8,65+k));
  if(*u(8,1)){
		if(fldlen(8,71)) *u(8,71)=procid;
		if(fldlen(8,72)) *u(8,72)=*u(25,2);
		g=fasupd(8); 
	}
	else{
		if(fldlen(8,70)) *u(8,70)=procid;
		if(fldlen(8,72)) *u(8,72)=*u(25,2);
		g=fasadd(8);
	}
  rec8_=*u(8,1);
  if(errnum==0) errnum=g;
  for(k=0;k<max_line;k++){
    fasinit(58);*u(58,2)=rec8_;*u(58,3)=k;
    if(faskeyi(58,1,0)==0) faskill(58);
    ram2stu(k); *pu_58_1=0;
/* bij updaten moet aantal ingevuld zijn */
#if FLAGCRA
    if((*ps_58_16 || *pu_58_14) && (*f(58,7) || *ps_58_16=='*' || *s(58,62)=='N')){ // lege lijnen ook niet bij nieuwe bon wegschrijven
#else
    if((*ps_58_16 || *pu_58_14) && (upd_mode==NO || *f(58,7) || *ps_58_16=='*' || *s(58,62)=='N')){ // N = niet voorradig
#endif
      *u(58,2)=*u(8,1);
      *u(58,3)=k;
      if(fldlen(58,61)) *f(58,61)=*pf_58_31;
			if(fldlen(58,72)) *u(58,72)=*u(8,8);
      if(*pu_58_1) g=fasupd(58); else g=fasadd(58);
      if(*u(58,2)!=rec8_){
	sys_err(990,*u(58,2));
	sys_err(991,rec8_);
      }
      q_lines++;empty=NO;
    }
    else if(*pu_58_1) g=faskill(58);
    if(errnum==0) errnum=g;
  }
#if FLAGEPD
	empty=NO; // nooit schrappen
#endif
  if(upd_mode && empty==YES){
    if(scr_ok("Bontotaal is 0, mag deze bon geschrapt worden ?")) faskill(8);
    else{
      if(fldlen(8,5)){*u(8,5)=0;fasupd(8);}
    }
  }
  else{
    if(fldlen(8,5)){*u(8,5)=q_lines;fasupd(8);}
  }
  if(errnum){
    if(errnum==48||errnum==49)errnum=9;
    scrget(1,170);
    scrifld(5,fm_os63,"    Fout tijdens het wegschrijven van de bon.");
    scrifld(10,fm_os63,"     Druk <TAB> om verder te gaan.");
    scrupd(-1,0);
    scrget(1,7);scrupd(-3,0);
  }
#if FLAGFIS && FLAG244
	if(upd_mode==NO && prt_levbon=='N'){
		zero(buf50_,sizeof buf50_);
		sprintf_s(buf50_,50,"Nummer van deze bon : %d",*u(8,2));
		DisplayWarning(buf50_,584,0);
	}
#endif

  fasflush(0);
}
#endif
 
#if FLAG244 | BONFILE & !KAS2BON
static get_klt(ptxt,mode_)/* mode_ : YES = 1 bon, NO = alle bons, 10=klant is al ingevuld */
char *ptxt;
int16 mode_;
{
  int16 j,g,k,key,fkey=1,z,curs=3,start=0,sel_mode_;
  uint16 msk_,nr_,n;
	char sel8jn_[DIM8],last_selmaggefactureerd_='A',last_ft_tijdstp_='\0', buf1000_[1000];

	if(mode_==10) {
		fasinit(2);*u(2,1)=*u(27,5);fasgeti(2);
		sel_mode_=2;goto select_bon;
	}

	InqBonNr=0;
#if MULTIBON_SELECT && FLAG248
	SelectieMagGefactureerd='J';
	for(k=0;k<DIM8;k++){
#if FLAGWYN
		sel8jn_[k]='N'; 
#else
		sel8jn_[k]='J'; 
#endif
		selrec8[k]=0;
	}
#endif

  msk_=0x681; if(mode_==2) msk_=0x0781;
#if PDA_LGRETOUR || PDA_TRACEER
	if(pbonnr<0) fasinit(2);
#else
  fasinit(2);
#endif
	zero((char *)&SearchFilterTabel[0],SearchFilterTabelSize); 
	n=0;scrget(1,7);scrupd(-3,0);
  FOREVER{
		*u(8,1)=++n;
    g=fasgetu(8);
    if(g==47)break;
		if(fldlen(8,30) && *s(8,30)!='J') *s(8,30)='N';
		if((fldlen(8,36)==0 || *u(8,36)==0) && *u(8,3)<SearchFilterTabelSize && 
			(fldlen(8,30)==0  || SelectieMagGefactureerd=='A' || SelectieMagGefactureerd==*s(8,30))) SearchFilterTabel[*u(8,3)]=1;
	}
	if(fldlen(2,33) && ft_tijdstp){
		copy(s(2,1),buf1000_,fldlen(2,0));
		for(k=0;k<SearchFilterTabelSize;k++){
			if(SearchFilterTabel[k]==1){
				fasinit(2);*u(2,1)=k; fasgeti(2);;
	      if(ft_tijdstp!=*s(2,33)) SearchFilterTabel[k]=0;
      }
		}
		copy(buf1000_,s(2,1),fldlen(2,0));
	}
  fasinit(8);
  redo:
  scrget(2,23);z=1;
  scrfld(z++,25,1);
  scrifld(z++,fm_os25,ptxt);
  scrfld(z++,2,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
  scrifld(z++,fm_udat,&dt_bon_beg);
  scrifld(z++,fm_udat,&dt_bon_end);
	if(fldlen(8,30)) scrifld(z++,fm_u_JNA,&SelectieMagGefactureerd);
	if(fldlen(2,33)) scrifld(z++,fm_us1_U,&ft_tijdstp);
  key=scrupd(3,msk_);curs=3;
	if ((key/0x100)==1) key=(key&0xFF)+5000;
  if(key==101) return NO;
  if(key==111) ovl_exit(0);
	if(SelectieMagGefactureerd!=last_selmaggefactureerd_ || last_ft_tijdstp_!=ft_tijdstp){  // indien men wijzigt dan andere default tabel laden
		zero((char *)&SearchFilterTabel[0],SearchFilterTabelSize);
		n=0;scrget(1,7);scrupd(-3,0);
		FOREVER{
			*u(8,1)=++n;
			g=fasgetu(8);
			if(g==47)break;
			if(fldlen(8,30) && *s(8,30)!='J') *s(8,30)='N';
			if((fldlen(8,36)==0 || *u(8,36)==0) && *u(8,3)<SearchFilterTabelSize && 
				(fldlen(8,30)==0  || SelectieMagGefactureerd=='A' || SelectieMagGefactureerd==*s(8,30))) SearchFilterTabel[*u(8,3)]=1;
		}
		if(fldlen(2,33) && ft_tijdstp){
			copy(s(2,1),buf1000_,fldlen(2,0));
			for(k=0;k<SearchFilterTabelSize;k++){
				if(SearchFilterTabel[k]==1){
					fasinit(2);*u(2,1)=k; fasgeti(2);;
					if(ft_tijdstp!=*s(2,33)) SearchFilterTabel[k]=0;
				}
			}
			copy(buf1000_,s(2,1),fldlen(2,0));
		}
		last_selmaggefactureerd_=SelectieMagGefactureerd; last_ft_tijdstp_=ft_tijdstp;
	}
	sel_mode_=99;	if(key==5001) sel_mode_=98;
	InqBonNr=0;
	if(*s(2,3)=='+'){
		nr_=val(s(2,3)+1);
		if(nr_==0) {errnum=38;goto redo;}
		fasinit(8);
		n=0;scrget(1,7);scrupd(-3,0);
		FOREVER{
			*u(8,1)=++n;
			g=fasgetu(8);
			if(g==47)break;
			if(g!=46){/* deleted record */
				if(*u(8,2)==nr_ && (fldlen(8,36)==0 || *u(8,36)==0)){
					fasinit(2);*u(2,1)=*u(8,3); fasgeti(2);
					InqBonNr=nr_;sel_mode_=-1; // om geen search te doen
					break;
				}
			}
		}
	}
	if(key==109) sel_mode_=0;// bij normale search enkel klanten met bons tonen, bij F9 iedereen
	if(sel_mode_>=0 && search(2,sel_mode_)) goto redo;
  if(key==110){ovlcall(2922,1); goto redo;}

#if FLAG244 & !PDA_LGRETOUR & !SAMENVOEGEN & !WEB_ADD
  if(key==109){add_bon(*u(2,1));upd_mode=YES;fasinit(8);goto redo;}
#endif
  sel_mode_=mode_;
#if FLAG248       
//#if FLAGWYN// indien geen periode ingevuld, dan steeds bon per bon 
//	if(dt_bon_beg==0){ sel_mode_=YES;fl_multibon=NO;}
//#endif
  if(*u(2,1)==klt_div1 || *u(2,1)==klt_div2 || (fldlen(2,42) && *s(2,42)=='J')) sel_mode_=YES;// indien diverse klant dan ALTIJD bon per bon factureren 
#if MULTI_PER_KLT || ALB_flag
    if(fldlen(2,37) && *s(2,37)=='J') sel_mode_=YES;/* per bon factuur */
#endif
#endif
select_bon:;
  fasinit(8);*u(8,3)=*u(2,1);*u(8,8)=dt_bon_beg;fkey=1;
  for(k=0;k<DIM8;k++){
#if !(MULTIBON_SELECT && FLAG248)
    if(k==1 && sel_mode_==NO) break;
#endif
    next_8:;
    if(faskeyu(8,1,fkey)) break;
    fkey=2;
    if(*u(8,3)!=*u(2,1)) break;
    if(dt_bon_beg && *u(8,8)<dt_bon_beg) goto next_8;
    if(dt_bon_end && *u(8,8)>dt_bon_end) goto next_8;
#if BACKORDER
    if(*u(8,36)) goto next_8;
#endif
		if(InqBonNr && InqBonNr!=*u(8,2)) goto next_8;
		if(fldlen(8,30) && *s(8,30)!='J') *s(8,30)='N';
		if(fldlen(8,30) && SelectieMagGefactureerd!='A' && SelectieMagGefactureerd!=*s(8,30)) goto next_8;
#if PDA_LGRETOUR
    if(pbonnr>=0 && pdabons[pbonnr].bonnr && pdabons[pbonnr].bonnr==*u(8,2)){
      rec_8[0]=*u(8,1);k=1; break;/* stoppen bij juiste bon */
    }
#endif
    rec_8[k]=*u(8,1);
  }
  if(k==0) {
		errnum=14;fasinit(8);
		if(mode_==10) return NO;
		goto redo;
	}
#if MULTIBON_SELECT && FLAG248
  if(k>=1){
#else
  if(k>1){
#endif
    FOREVER{
			redo32:;
#if MULTIBON_SELECT && FLAG248
			scrget(2,36);
#else 
      scrget(2,32);
#endif
			z=1;
      scrofld(z++,2,3,-1);
      for(j=start;j<k;j++){
				fasinit(8);*u(8,1)=rec_8[j];fasgeti(8);
				j++;scrifld(z++,fm_ou2,&j);j--;
#if MULTIBON_SELECT && FLAG248
	      scrifld(z++,fm_u_JN,&sel8jn_[j]);
#endif
				scrofld(z++,8,8,-1);
				scrofld(z++,8,25,-1);
				scrofld(z++,8,2,-1);
#if MULTIBON_SELECT && FLAG248
	      scrofld(z++,8,11,-1);
#endif
				if(j==start+14) break;
      }
#if !(MULTIBON_SELECT && FLAG248)
      j=0;scrifld(62,fm_uu2,&j);
#endif
      key=scrupd(1,0x87);
      if(key==101) {
				if(mode_==10) return NO;
				fasinit(8);goto redo;
			}
//      if(j>0 && j<=k) {rec_8[0]=rec_8[j-1];break;}
      if(key==102) start-=15;
      if(key==103) {start+=15;if(start>k-15) start=k-15;}
      if(start<0) start=0;
#if MULTIBON_SELECT && FLAG248
			if(key!=108) goto redo32;
			for(j=0;j<k;j++) if(sel8jn_[j]=='J') break;
			if(j<k){
				for(j=0;j<k;j++) if(sel8jn_[j]=='J') selrec8[j]=rec_8[j];
				break;
			}
#else
			if(j>0 && j<=k) {rec_8[0]=rec_8[j-1];break;}
#endif
    }
  }
  *u(8,1)=rec_8[0];fasgetu(8);
#if FLAG248
  if(fldlen(8,49)){
    if(*u(8,49) && *u(8,49)!=procid){
      if(scr_ok("Bon in gebruik door ander scherm! Toch doorgaan???")==NO) return NO;
     }
   }
#endif
  return YES;
}
#endif

#if FLAG244 & BONFILE
static ok_kil()
{
  int16 key;

  redo:
  scrget(1,10);
  scrifld(1,fm_os25,"Leveringsbons");
  scrfld(2,25,1);
  scrofld(3,2,3,-1);
  scrofld(4,8,2,-1);
  scrofld(5,8,8,-1);
#if ARTEXIST && FLAG244 && STOCK244        /* stock aanpassen op bon-niveau */
  scraddf(10,22,45,8);  scrifld(10,VarTextFmt(35,0)," F10 Schrap zonder stockaanpassing ");
#endif
  key=scrupd(0xFFFF,0x619);
  if(key==111) ovl_exit(0);
  if(key==101) return NO;
  if(key!=104 && key!=105 && key!=110) {errnum=21;goto redo;}
  if(key==104) return YES;
  if(key==110) return 2;
  return NO;
}
#endif
 
#if FLAG244 & B_LST_ART & !SAMENVOEGEN & !PDA_LGRETOUR & !KAS2JMCBON 
static art_lst()
{
  int16 j,z;

  prtclose();
  getsysprNew(5,form_dat,&mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1);prttext("<t40b>");prttext("Artikels op bons");prttext("<b>");
  prttext("<t60>");prtfld(25,2,-1);
  prttext("<t72>Blz.<ppp>.");
  prtbuf(1);z=1;
  if(fldlen(2,2)) prttab(z,2,2,1,-1);
  else prttab(z,2,1,1,-1); prttitle(z++,"Code",3);
  prttab(z,2,3,1,-1); prttitle(z++,"Klant",3);
  prttab(z,8,8,1,-1); prttitle(z++,"Lev.dt.",0x13);
  prttab(z,8,2,1,-1); prttitle(z++,"Bonnr",0x13);
  if(len58_15){prttab(z,58,15,1,-1); prttitle(z++,"Code",3);}
  prttab(z,58,16,1,-1); prttitle(z++,"Omschrijving",3);
  prttab(z,58,31,1,-1); prttitle(z++,"Aantal",0x13);
  prttab(z,58,20,1,-1); prttitle(z++,"Prijs",0x13);
  prtbuf(3);
	p_pdfname("Artikels op bons",dt_bon_beg,dt_bon_end);
  free=999;
  fasinit(58);copy(ps_58_15,ram,len58_15);*(float *)&ram[20]=0.;
  FOREVER{
    fasinit(2);fasinit(8);
    if(faskeyi(58,5,2)) break;
    if(cmpstr(ps_58_15,ram,len58_15)) art_subt();
    copy(ps_58_15,ram,len58_15);
    *u(8,1)=*u(58,2);fasgeti(8);
    *u(2,1)=*u(8,3);fasgeti(2);
    for(j=1;j<=15;j++) prtinfo(j,0);nextline();
    *(float *)&ram[20]+=*pf_58_31;
    if(free<0) break;
  }
  art_subt();
  prtclose();
  endsr:;
  exit_hfdmenu();
}

static art_subt()
{
  int16 k;
  uint16 rec_;

  if(*(float *)&ram[20]){
    rec_=*pu_58_1;
    fasinit(58);
    copy(ram,ps_58_15,len58_15);copy("Totaal",ps_58_16,7);
    *pf_58_31=*(float *)&ram[20];
    for(k=1;k<=15;k++) prtinfo(k,0);nextline();
    nextline();
    *(float *)&ram[20]=0;
    *pu_58_1=rec_;fasgeti(58);
  }
}
#endif
 
static ovl_exit(nr_)
int16 nr_;
{
	ClearSysPosNrCheck();
  sysflush();
  fasflush(0);
  prtclose();
  if(sizeof ovl_tabel!=2 && nr_==218) ovlexit(218);
  exit_hfdmenu();
}

#if FLAG248 & DUMP_CFT
static seqo_cft()/* dumpen kopie van factuur */
{
  int16 k,yy,mm,dd,len_;
  uint16 rec8_;
  char ofname[50],*pdum_;

#if SAVEPDFFACTUUR && FLAG248 && !FT_HERAFDRUK
	if(SaveFactuur2Pdf()==NO) ft_prt();
#endif

	for(k=0;k<4;k++) copy(opm_foot[k],s(8,65+k),fldlen(8,65+k)); // opmerkingen bijhouden 
  fasclos(-2); 
  jddate(ft_date,&yy,&mm,&dd); zero(ofname,sizeof ofname);
  yy%=100;
  sysget(4704,25,ofname);
  for(k=0;k<25;k++) if(ofname[k]=='\0') break;
  copy(s(25,3),&ofname[k],3); ofname[k+3]='\0';
  for(k=0;k<25;k++) if(ofname[k]=='\0') break;
  stcli_d(&ofname[k],(long)ft_nr,5,0);
  ofname[k+5]='.';stcli_d(&ofname[k+6],(long)yy,2,0); 

	if(mnd_strt!=1){// indien boekjaar NIET op 1/1 begint, dan uitkijken met overlappende factuurnummers
		if(mm>=mnd_strt){ // indien in nieuw BOEKjaar van huidig kalenderjaar
			fasclos(-2);
			if(fasopen(ofname,1)==0){// factuurfile bestaat reeds, dan A toevoegen aan suffix, dus KKKnnnnn.jjA
				ofname[k+8]='A';
			}
			fasclos(-2);
		}
	}
	fasclos(-2);
#if FT_HERAFDRUK  // aanpassing doen in originele bestandsnaam (zie load_file)
	copy(OriFtFileName,ofname,50);
#endif
  if(fasopen(ofname,2)){
    scrget(1,170);
    scrifld(5,fm_os63,"       Kan de factuur-KOPIE NIET wegschrijven !!!");
    scrifld(6,fm_os63,"    Gelieve Jamadata te bellen om dit op te lossen !!!");
    scrifld(10,fm_os63,"          Druk op F8 om verder te gaan...");
    scrupd(-1,0x81);
    scrget(1,7);scrupd(-3,0);
    return YES;
  }
  fasinit(80);

  zero((char *)&ft_stu.ft_nr,sizeof ft_stu);
  ft_stu.ft_nr=ft_nr;ft_stu.ft_date=ft_date;
  ft_stu.stu8len=fldlen(8,0);
  ft_stu.stu58len=fldlen(58,0);
  ft_stu.alg_tot=alg_tot;
  ft_stu.belastbt=belastbt;
  ft_stu.btw_tot=btw_tot;
  ft_stu.tot_leeg=tot_leeg;
  for(k=0;k<4;k++){
    copy(&opm_foot[k][0],&ft_stu.opm_foot[k][0],sizeof ft_stu.opm_foot[k]);
  }
  for(k=0;k<200;k++){
    len_=fldlen(8,k+1);
    if(len_){
      fieldspc(8,k+1,&pdum_,fmt);
      ft_stu.stu8[k][0]=len_;
      ft_stu.stu8[k][1]=fmt[1];
    }
  }
  for(k=0;k<200;k++){
    len_=fldlen(58,k+1);
    if(len_){
      fieldspc(58,k+1,&pdum_,fmt);
      ft_stu.stu58[k][0]=len_;
      ft_stu.stu58[k][1]=fmt[1];
    }
  }
  seqo_rec((char *)&ft_stu.ft_nr,sizeof ft_stu);

  *u(8,3)=*u(2,1);errnum=0;
  if(fldlen(8,11)) *d(8,11)=alg_tot;
  seqo_rec(s(8,1),fldlen(8,0));
  rec8_=*u(8,1);
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if((*ps_58_16 || *pu_58_14) && (*f(58,7) || *ps_58_16=='*' || ARTEXIST==NO)){
      *u(58,2)=*u(8,1);
      *u(58,3)=k;
      seqo_rec(s(58,1),fldlen(58,0));
    }
  }
  fasclos(-2);
  fasflush(0);
}

static seqo_rec(ps_,len_)
char *ps_;
int16 len_;
{
  int16 k,slen_;

  slen_=0;
  for(k=0;k<len_;k+=280){
    if((k+280)>len_) slen_=len_-k;
    else slen_=280;
    copy(ps_+k,s(80,1)+4,slen_);
    fasseqo(80,2,slen_+4);
  }
}
#endif
 
#if LAYOUT
#include "parlay.c"
#else
#include "std\DRKparlay.c"
#endif
 
//#include "DRK0240bi.c"

#if FLAG248 & LETTERSC

// voor juiste tekst in parlay.c zie DCN

static char *aant0txt[2][19]={{"een","twee","drie","vier","vijf","zes","zeven","acht","negen",
	    "tien","elf","twaalf","dertien","veertien","vijftien","zestien",
	    "zeventien","achttien","negentien"},
		 {"un","deux","trois","quatre","cinq","six","sept","huit","neuf",
	    "dix","onze","douze","treize","quatorze","quinze","seize",
	    "dix-sept","dix-huit","dix-neuf"}};

static char *aant1txt[2][8]={{"twintig","dertig","veertig","vijftig","zestig","zeventig",
	    "tachtig","negentig"},
		 {"vingt","trente","quarante","cinquante","soixante","septante",
	    "quatre-vingt","nonante"}};
static int16 letschrp=0,taal_let;
static char letschrb[132];

static letschr(get_,marg_,len_)
double get_;
int16 marg_,len_;
{
  int16 taal_;
  long bd_,dec_;
  char munt_[4];
 
  taal_let=0; if(taaltxt==1) taal_let=1;
  copy(ft_munt,munt_,3);munt_[3]='\0';
  if(get_<0) get_=-get_;
  bd_=get_; dec_=(long)(get_*100.+.49)-(bd_*100);
  letschrp=0;
  if(taaltxt==1){
    letschr0(bd_/1000000L,marg_,len_,2,"million ");
    letschr0(bd_/1000L,marg_,len_,1,"mille ");
  }
  else {
    letschr0(bd_/1000000L,marg_,len_,2,"miljoen ");
    letschr0(bd_/1000L,marg_,len_,1,"duizend ");
  }
  letschr0(bd_,marg_,len_,0," ");
  letschra(munt_,marg_,len_);
  if(dec_){
    if(taaltxt==1) letschra(" et ",marg_,len_);
    else letschra(" en ",marg_,len_);
    letschr0(dec_,marg_,len_,0," ");
    if(taaltxt==1 && dec_>1) letschra("cents",marg_,len_); else letschra("cent",marg_,len_);
  }
  if(letschrp){
    letschra("",marg_,0);
  }
}
 
static letschr0(get_,marg_,len_,niv_,txtbas_)
long get_;
int16 marg_,len_,niv_;
char *txtbas_;
{
  int16 j,k;

  get_=get_%1000;if(get_==0) goto endsr;
  if(get_==1 && niv_==1) goto pt1;/* eenduizend */
  k=get_/100;
  if(k){
    if(k>1) letschra(aant0txt[taal_let][k-1],marg_,len_);
    if(taaltxt==1){
			if(k>1) letschra("cents ",marg_,len_); else letschra("cent ",marg_,len_);
		}
    else letschra("honderd",marg_,len_);
  }
  get_=get_%100;
  if(get_){
    if(get_<20){
      letschra(aant0txt[taal_let][get_-1],marg_,len_);
    }
    else{
      if(taal_let==1){
	j=get_/10;
	if(j){
	  letschra(aant1txt[taal_let][j-2],marg_,len_);
	}
	k=get_%10;
	if(taal_let){
		if(j && k) letschra("-",marg_,len_);
		else if(j==8 && k==0) letschra("s",marg_,len_); // correctie quatre-vingtS
	}
	if(k) letschra(aant0txt[taal_let][k-1],marg_,len_);
      }
      else{
	k=get_%10;
	if(k) letschra(aant0txt[taal_let][k-1],marg_,len_);
	j=get_/10;
	if(j){
	  if(k){
	    if(taaltxt==1) letschra("et",marg_,len_);
	    else letschra("en",marg_,len_);
	  }
	  letschra(aant1txt[taal_let][j-2],marg_,len_);
	}
      }
    }
  }
  pt1:;
  letschra(txtbas_,marg_,len_);
  endsr:;
}
 
static letschra(ps,marg_,len_)
char *ps;
int16 marg_,len_;
{
  int16 k=0;

  while(*(ps+k)) k++;
  if(letschrp+k>len_){
    prtblank(marg_);prttext(letschrb);nextline();
    letschrp=0;
  }
  copy(ps,&letschrb[letschrp],k+1);
  letschrp+=k;
}

// #include "DRK024010.c"
#endif
 
#if (FLAG248 & !FACT_RISTOURNO & (BONFILE==NO) & (KASINPUT==NO)) | FLAG242/* manuele facturatie */
static ft_manu()
{
  int16 k;
 
  fasinit(8); upd_mode=NO;chk_nr=YES;
  FOREVER{
    for(k=0;k<2;k++) last_vt[k]=*u(8,19+k);
    sysget(last_vfa,2,&last_vf);
    ft_init(YES);ft_nr=last_vf+1;
#if FLAG242
		*u(8,2)=last_vf+1;
#endif
    for(k=0;k<2;k++) *u(8,19+k)=last_vt[k];
    if(exec()==NO) break;
    last_vf=ft_nr;
  }
}
#endif

#if FLAG248 & BONFILE
static ft_1bon_direct() // bonrecord zit in 26,5
{
  stuk_per_stuk=YES;upd_mode=NO;chk_nr=YES;
  sysget(last_vfa,2,&last_vf);
  ft_init(YES);ft_nr=last_vf+1;chk_nr=YES;
redo:
	fl_multibon=NO;
	fasinit(8); *u(8,1)=*u(26,5);
	if(*u(8,1)==0 || fasgeti(8)) goto endsr;
#if MULTIBON_SELECT && FLAG248
	selrec8[0]=*u(8,1);
#endif

	fasinit(2);*u(2,1)=*u(8,3); fasgeti(2);
  if(!facturatie()) goto endsr;
  if(!load_bon(NO,1))goto endsr;
  select_mnt();
#if (ADDLIN || ADDORSEP) & (!NO_ART_SORT)
#if ADDORSEP
  if(fldlen(2,37)==0 || *s(2,37)=='J')
#endif
    SortBon(0);
#endif
  if(exec()){
    kill();
    last_vf=ft_nr;
  }
  fasinfo(8,101);
  fasflush(0);
  endsr:;
}
#endif



#if FLAG248 & BONFILE
static ft_1ft()
{
  stuk_per_stuk=YES;upd_mode=NO;chk_nr=YES;
  FOREVER{
    sysget(last_vfa,2,&last_vf);
    ft_init(YES);ft_nr=last_vf+1;chk_nr=YES;
redo:
		fl_multibon=MULTIBON;
#if ALB_flag || !MULTIBON
    if(!get_klt("te factureren",YES))break;
#else
    if(!get_klt("te factureren",NO))break;
#endif
    if(!facturatie()) break;
    if(!load_bon(MULTIBON,1))goto redo;
#if STOCK_OP_LOCATIE
	if(fldlen(8,48)) *u(8,48)=filiaal;
#endif
    select_mnt();

#if (ADDLIN || ADDORSEP) & (!NO_ART_SORT)
#if ADDORSEP
    if(fldlen(2,37)==0 || *s(2,37)=='J')
#endif
#if FLAGWYN
    if(fl_multibon)
#endif
      SortBon(0);
#endif
    if(exec()){
      kill();
      last_vf=ft_nr;
    }
    fasinfo(8,101);
    fasflush(0);
  }
}
#endif

#if FLAG248 & BONFILE
static ft_serie()
{
  int16 ks,fkey,mode_;
  flag first=YES;
  uint16 g,n,krec_;

	if(DisplayWarning("Wenst U echt de bons IN SERIE te factureren?",605,1)==NO) goto endsr;
  stuk_per_stuk=NO;fl_multibon=MULTIBON;InqBonNr=0;
  fkey=2;if(sys3952 ==1) fkey=1;
  scrget(1,6);scrupd(-3,0);
  fasinit(2); chk_nr=YES;
  FOREVER{
    ks=faskeyi(2,fkey,2);
    if(ks) break;
    krec_=*pu_2_1;
    ft_init(NO);mode_=1;
    FOREVER{
      *pu_2_1=krec_;fasgeti(2);fasinit(8);*u(8,3)=*pu_2_1; chk_nr=YES;
      next_8:;
      if(faskeyu(8,1,mode_)) break; mode_=2;
      if(*u(8,3)!=*pu_2_1) break;
#if BACKORDER
      if(*u(8,36)) goto next_8;
#endif
      sysget(last_vfa,2,&last_vf);
      ft_nr=last_vf+1;
      if(first){
	if(!facturatie()) goto endsr;
	first=NO;
      }
      if(fldlen(2,33)){
	if(ft_tijdstp && ft_tijdstp!=*s(2,33)) break;
      }
#if MULTIBON_SELECT
			selrec8[0]=0xFFFF; // om aan te duiden dat hier niet op geselecteerd moet worden
#endif
      if(load_bon(MULTIBON,1)){
#if (ADDLIN || ADDORSEP) & (!NO_ART_SORT)
#if ADDORSEP
	if(fldlen(2,37)==0 || *s(2,37)=='J')
#endif
	  SortBon(0);
#endif
#if STOCK_OP_LOCATIE
	      if(fldlen(8,48)) *u(8,48)=filiaal;
#endif
	      prt2pdf=0;
				if(exec()) {kill();last_vf=ft_nr;}
				else goto endsr;
      }
      else break;
      if(free<0) goto endsr;
    }
    *pu_2_1=krec_;fasgeti(2);
  }
  endsr:;
  fasinit(58);                            /* scannen op losgeslagen records */
  n=0;scrget(1,7);scrupd(-3,0);fasunlck(-2);
  FOREVER{
    *pu_58_1=++n;
    g=fasgetu(58);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
      fasinit(8);*u(8,1)=*u(58,2);
      if(fasgeti(8)){
				faskill(58);
			}
    }
  }
  fasinfo(8,101);fasflush(0);

}
#endif

static ft_init(mode_)
int16 mode_;/* NO = enkel stu 8 clearen */
{

#if FLAG248 & BOEKALLO & !FT_HERAFDRUK/* controle op voldoende plaats om te boeken */
	if(CheckForFreeSpace(4,MINFREE)) ovl_exit(-1);/* onvoldoende vrije records */
#endif
#if FLAG248 & HISTORIEK & !FT_HERAFDRUK/* controle op voldoende plaats om te boeken */
	if(CheckForFreeSpace(16,200)) ovl_exit(-1);/* onvoldoende vrije records */
#endif
  if(mode_) fasinit(2);
  fasinit(8);
  *s(8,22)=DEF_VOLD;
  *s(8,26)='N';btw_glob=99;
  zero(ft_munt,sizeof ft_munt);
  if(len8_23) copy(def_munt,ps_8_23,3);
#if TRANS_KOST
  if(fldlen(8,31)) *s(8,31)='J';
#endif

  *pu_8_28=def_qfact;
#if FLAG244 | KAS2BON | FLAG252 | FLAG242 | FLAG241
  *pu_8_28=1;
  *u(8,8)=ft_date;
	if(fldlen(8,30) && *s(8,30)=='\0') *s(8,30)=MAG_GEFACT;
#endif
#if STOCK_OP_LOCATIE
	if(fldlen(8,48)){
		sysget(2854,2,u(8,48)); if(*u(8,48)<1 || *u(8,48)>10) *u(8,48)=99; // firma in apart journaal
	  if(WerkpostFiliaalNr && WerkpostFiliaalNr<=10 && nm_loc[WerkpostFiliaalNr-1][0]) *u(8,48)=WerkpostFiliaalNr;
	}
	// if(fldlen(8,48)) *u(8,48)= DefaultFiliaal;
#endif
#if KAS2JMCFACTUUR || KAS2JMCBON || KASINPUT
	if(fldlen(8,74)) *s(8,74)=YES; // om aan te duiden dat het van de kassa komt
#endif
#if FLAGVBE && KAS2FACT
	if(fldlen(8,74)) *s(8,74)=YES; // om aan te duiden dat het van de kassa komt
#endif
#if FLAGDLT && KARWEIWERKEN
	if(fldlen(8,74)) *s(8,74)=YES; // om aan te duiden dat het van de kassa komt
#endif
	if(fldlen(8,70)) *u(8,70)=procid;
	if(fldlen(8,72)) *u(8,72)=*u(25,2);
  verv_dt=0;disk_dt=0;winst_pc=0;winst_bd=0;
  zero(opm_foot[0],sizeof opm_foot);stat_klt=0;
  zero(opm_bkh,sizeof opm_bkh);
  if(mode_){
    init58(0,NO);keepdata=NO;
		if(ovltest(2241) || ovltest(2394) || ovltest(2295) || ovltest(2296))	zero(BestelFileUsed,sizeof BestelFileUsed); 
  }
  lgadded=NO;
	DoBlokkeerCheck=YES;
}
 
static init58(start_,mode_)
int16 start_,mode_;
{
  int16 k;

  fasinit(58);
  *pf_58_24=def_btw;
  if(fldlen(58,27)) *s(58,27)=def_inc;
  if(len58_25) copy(def_ext,ps_58_25,len58_25);
  *pf_58_21=*f(2,18);
#if EET_RIST
  if(fldlen(2,56)) *pf_58_21=*f(2,56);
#endif
#if FLAGDUB || FLAGSEG || FLAGFLI
 if(fldlen(58,60)) *s(58,60)='N';
#endif
  for(k=start_;k<max_line;k++) {stu2ram(k);if(mode_) break;}
}

static initload()
{
  int16 j,k;
  char *pdum_;

  fasunlck(0);
  fileopen(1);
  fileopen(2); if(fldlen(2,64)) k_omz_exist=YES;
  fileopen(3);
  fileopen(4);
  fileopen(6); if(fldlen(66,1)) fileopen(12);/* stocklocaties */
	if(fldlen(7,1)) fileopen(7);
	fileopen(8);
	if(fldlen(22,1)) fileopen(15);
  fileopen(9);
	if(fldlen(16,1)) fileopen(13);
#if STOCK_OP_LOCATIE
  fileopen(12);
  sysget(2854,2,&filiaal);
  sysget(2854,2,&DefaultFiliaal);
#endif

#if STATISTIEK & (FICHEEXEC | SPLITS_STATIST | BLOK_ART)
  fileopen(14);
#endif
	zero((char *)tb_grbnotfound,sizeof tb_grbnotfound);notfound=0;
  ram=RamBon;
  ram_size=125000;
#ifdef DOUBLE_FACT
  ram_size*=DOUBLE_FACT;
#endif
  if(ram_size>RamBonSize-200) ram_size=RamBonSize-200;
#if !KAS2JMCFACTUUR & !KAS2JMCBON 
	zeroL(ram,RamBonSize-200 /* ram_size */);
#endif
  stu58_len=fldlen(58,0);max_line=ram_size/stu58_len;
  sysget(3636,4,&grb_notf);

#if BOEKALLO & BOEKEXEC
  if(bkh_exist){
    sysget(784,4,&kltcent);
    find_grb(kltcent);
    find_grb(grb_notf);
    for(k=0;k<DF_GRB;k++){
      sysget(788+k*4,4,&df_rek[k][0]);
      if(df_rek[k][0]!=0xFF && df_rek[k][0]!=0x00){
			df_recnr[k]=find_grb(*(long *)&df_rek[k][0]);
      }
    }
#if KM_HEFFING || LEVERINGSKOST /* km-heffing def_grb[15] uit veiligheid altijd rekening */
		if(df_rek[15][0]==0xFF || df_rek[15][0]==0x00){
			*(long *)&df_rek[15][0]=grb_notf;
			df_recnr[15]=find_grb(*(long *)&df_rek[15][0]);
		}
#endif
#if 0
    sysget(1205,4,&grb_d_vk);
    if(grb_d_vk==0 || grb_d_vk==-1) {errnum=16; ovlexit(-1);}
    rec_d_vk=find_grb(grb_d_vk);
#endif
	 if(notfound){
			errnum=2;
			scrnum=0;scrget(1,170);
			for(k=0;k<notfound && k<15;k++) scrifld(k+1,fm_ogrb,&tb_grbnotfound[k]);
			scrifld(18,fm_os63,"      Druk F8 om terug te keren ....");
			scrupd(-1,0x80);
			exit_hfdmenu();
		}
    if(df_recnr[12]==0) {errnum=82;exit_hfdmenu();}
  }
#endif
  sysget( 294,4,def_munt);
#if INTRASTAT
  sysget( 626,2,&intr_stel); intr_stel=29;
  p_intras=(struct _intras *)s(58,30);
#endif
	sysget(1317, 1, &CheckPeppolKlant);
	sysget(1804,2,&sys1804);
  sysget(1858,2,&last_arc);
	sysget(2300,2,&MinBkhDatum);if((MinBkhDatum || sys1804) && MinBkhDatum<last_arc) MinBkhDatum=last_arc;
#if FLAG244 | KAS2BON | FLAG252 | FLAG242 | FLAG241
#ifdef LAST_VFA
  last_vfa=LAST_VFA;
#else
  last_vfa=3718;
#endif
  sysget(last_vfa,2,&last_vf);
#else
  sysget(2166,2,&journl);
#if KN_JOURNL/* apart credietnota journaal */
  journl++;
#endif

#ifdef BOEK_JOURNL/* afwijkend journaal */
  journl=BOEK_JOURNL;
#endif
  for(k=0;k<80;k++){
    sysget(10240+k*80,2,&last_vf);
    if(last_vf==journl)break;
  }
  if(k==80){errnum=4;exit_hfdmenu();}
  last_vfa=10260+k*80;
  sysget(last_vfa,2,&last_vf);
#endif
  SysPosNrCheck=3774;//facturen 
	if(last_vfa==3718) SysPosNrCheck=3776; // leveringsbons
	else if(last_vfa==3922) SysPosNrCheck=3778; // bestelbons 
  sysget(  34,256,firma);
  sysget(1219,42,&firma[256]);
  sysget(1261,11,&firma[298]);
#if !FLAGHOE
	if(firma[101] && firma[256]){ // IBAN bij voorkeur gebruiken voor rekeningnummer
		copy(&firm[8].begpos,&firm[3].begpos,sizeof firm[0]); 
		firm[8].begpos+=41; // om IBAN te misleiden
	}
#endif
  sysget(1787,1,&sys1787);
  sysget(1862,2,&sys1862);
  sysget(1866,2,&mnd_strt);
  sysget(1918,2,&sear_stt);
  sysget(1920,61,std_txt[0]);
  sysget(1981,61,std_txt[1]);
  sysget(2042,61,std_txt[2]);
  sysget(2103,61,std_txt[3]);
  sysget(2164,2,&disk_ei);
#if VOLD2KAS
  sysget(2168,2,&kasjrnl);
  sysget(2170,2,&sys2170);
#endif
	for(k=0;k<80;k++) sysget(10240+k*80,sizeof j_tab[0],(char *)&j_tab[k]);
  sysget(2172,2,&btw_kol);
  sysget(1048,32,&btw_pct[0]);
  sysget(2208,2,&skip_off);
  sysget(2216,2,&klt_div1);
  sysget(2218,2,&klt_div2);
  sysget(2220,2,&lev_ask);
  sysget(2222,2,&def_qfact);
  sysget(2224,2,&waard_inc);
  sysget(1080,4,&max_btw);
  sysget(2228,2,&b2228);
  sysget(1084,4,&def_btw);
	sysget(2696,2,&sys2696);/* om verschil tussen 2 firma's te maken */
  sysget(2727,2,&sys2727);
  sysget(2770,60,(char *)&nm_loc[0][0]);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
	sysget(2940,2,&sys2940);// 1=GEEN herafdruk bijhouden 
	sysget(2991,2,&RecLevKostArt);
	sysget(3192,50,ExtraBijlageFactuurmail);
  sysget(3586,2,&sys3586);
  sysget(3598,6,b3598);
  sysget(3604,2,&b3604);
  sysget(3606,2,&b3606);
  sysget(3608,2,def_ext);
	sysget(2989,2,&sys2989);
  sysget(3876,2,&sys3876);
  sysget(3894,2,&sys3894);def_inc='N';
  sysget(3896,6,&sys3896[0]);
  j=0; for(k=0;k<6;k++) if(sys3896[k]>='0' && sys3896[k]<='9') j++;
  KassaPrxNr=sys3896[0]-'0'; if(j) KassaPrxNrStuk=sys3896[j-1]-'0';
  sysget(3918,2,&sys3918);
  sysget(3952,2,&sys3952);
  sysget(2730,40,(char *)&loc_nr[0]);
  sysget(4134,120,(char *)&nm_kassa[0][0]);
  sysget(4254,40,(char *)&dt_kvk[0]);
  sysget(4294,40,(char *)&loc_klt[0]);
	sysget(4400,2,&sys4400);
  sysget(4408,2,&sys4408);
  sysget(4608,2,&sys4608);
#if FLAGALS
  sysget(5350,32,(char *)&hk_omzgrb[0]);
  sysget(5382,8,(char *)&hk_kostgrb[0]);
  sysget(5390,16,(char *)&hk_pct[0][0]);
#endif
  sysget(5576,120,&chauffeur[0].code[0]);
	sysget(19500,50,OutputMapUbl); 
	sysget(20450,50,MapPdfFacturen);
	sysget(20950,50,MapPdfBons);
#if SEARBFLEN
  sysget( 298,2,&vers_298);
#endif
  sysget(2212,4,talen);
#if SELECT_PRTNR
	k=11;
#if !FLAG248
  k=10;
#endif
  getsysprNew(k,form_dat,&mode,&prtnr);
	selprt12=prtnr;
#if FLAGDMS
	selprt12=1;
#endif
#endif
#if FLAGEPD
	for(k=0;k<10;k++){
		sysget(6500+k*3,1,(char *)&PaySettings.BetCode[k]);
		sysget(6501+k*3,2,(char *)&PaySettings.Jnl[k]);
	}
#endif
#if VOLD2KAS & BOEKEXEC
  for(k=0;k<80;k++){
    sysget(10240+k*80,2,&j);
    if(j==kasjrnl)break;
  }
  if(k==80)exit_hfdmenu();
  sysget(10242+k*80,2,&kastype);
  osalkasa=10287+k*80;
  sysget(10286+k*80,1,&osalmunt);
  osalmunt='E';
  sysget(osalkasa,8,&osalkas);
  last_17a=10260+k*80;
  sysget(last_17a,2,&last_17);
  sysget(10262+k*80,4,&grb_kas);
  rec_kas=sear_grb(grb_kas);
  sysget(18538,4,&grb_BCkas); // rekening bancontact uit kasverslag (V.2.4 en parameters)
	if(grb_BCkas==0 || grb_BCkas==-1) grb_BCkas=grb_notf;
  rec_BCkas=sear_grb(grb_BCkas);
#endif

  pl_80_1=l(80,1);
  p_data=s(80,1)+4;
	fl_multibon=MULTIBON;
#if FEC_flag
#if !DEF_BOEKJN
  boek_JN='N';stock_JN='N';
#endif
#endif
 
  dt_bon_beg=0;/* dt_bon_end=*u(25,2); */
  fieldspc(58,20,&pdum_,fmt);
  k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;

  ps_2_3=s(2,3);len2_3=fldlen(2,3);
  len2_14=fldlen(2,14);
  pu_2_1=u(2,1);
  pu_6_1=u(6,1);
  ps_6_3=s(6,3);len6_3=fldlen(6,3);
  ps_8_23=s(8,23); len8_23=fldlen(8,23);
  pu_8_28=u(8,28);
  pu_58_1=u(58,1);
  pu_58_14=u(58,14);
  len58_15=fldlen(58,15);
  ps_58_15=s(58,15);
  ps_58_16=s(58,16);
  pf_58_20=f(58,20);
  pf_58_21=f(58,21);
  pf_58_24=f(58,24);
  ps_58_25=s(58,25);len58_25=fldlen(58,25);
  pf_58_31=f(58,31);
  pl_58_32=l(58,32);
  len58_35=fldlen(58,35); pd_58_35=d(58,35);
  ps_58_62=s(58,62);len58_62=fldlen(58,62);
  hash_len=fldlen(58,14)+len58_15+fldlen(58,16);
#if ANAL_ASK & FLAG248 & !KASINPUT & !FT_HERAFDRUK
  if(ask_a_rek()) ovl_exit(-1);
#endif
#if ILB_flag
  k=sizeof det_nr/2; det_nr[k-1]=35;
#endif
}

static exec()
{
  int16 curs,n,k,key,z,fuval=NO,mode_,change_,q_exemp_,mail_direct_,SendViaCodabox_,ori_prt2pdf_,found_;
	uint16 searcnr_;
	char str_[210];
	   
  fasunlck(0);
	if(dsp_hoofding()) goto endsr;
	fasunlck(-2);
#if FLAG248 & BONFILE
  orig_klt=*pu_2_1;
  if(fldlen(2,51) && *u(2,51) && sys3918==NO){/* vanaf nu in stu-2 het FACT-adres */
#if LEV_OMZET
#if FLAGALB
		if(*s(2,52)=='J') // afhankelijk per klant, PAS OP : relatieadres hiervoor gebruikt!
#endif
    stat_klt=*pu_2_1;
#endif
	  if(fldlen(8,12)) *u(8,12)=*pu_2_1; // record# lev.adres
    *pu_2_1=*u(2,51);fasgeti(2);
  }
#endif

#if FLAG248 & !SUBSIDIE  & !FACT_RISTOURNO
	if(fldlen(2,52)==2 && *u(2,52)) stat_klt=*u(2,52);
#endif
  for(k=0;k<2;k++) *u(8,19+k)=last_vt[k];
  if(fldlen(2,24)) taaltxt=*s(2,24);
#if FLAG244 && FLAGJAC 
	if(*s(8,32)=='J') taaltxt=3; // proforma factuur
	else taaltxt=0;
#endif
#if LETTERSC==NO
  if(fldlen(2,40) && *s(2,40)=='J'){
#if THV_flag
    copy("F�r die richtigkeit der summe von :",opm_foot[0],40);
#else
		if(taaltxt==1) copy("Certifi� Sinc�re et V�ritable � la somme de ",opm_foot[0],45);
    copy("Waar en echt verklaard voor de som van :",opm_foot[0],40);

#endif
  }
#endif

  if(stuk_per_stuk){
    if(*pu_2_1==klt_div1 || *pu_2_1==klt_div2 || lev_ask || (fldlen(2,42) && *s(2,42)=='J')){
      if(ask_lev_adr()) goto endsr;
    }
  }
  redo:
#if SCREXEC
  if(dsp_detail()==NO) goto endsr;
#endif
  calc();
#if INTRASTAT & (FLAG244 | !BONFILE)
  fill_intra();
#endif
#if GRS_flag
  if(fldlen(62,1)){
    fasinit(62);*u(62,2)=*pu_2_1;
    if(faskeyi(62,1,0)==0){
      for(k=0;k<5;k++) if(*s(62,5+k)) break;
      if(k<5) {DisplayMemo(2);fasupd(62);}
    }
  }
#endif
redo_dsp_tot:;
  if((k=dsp_tot(NO))==NO) goto endsr;
  if(k>1)goto redo;
#if FLAGABT && FLAG248 && !FT_HERAFDRUK // controle of er al een factuur gemaakt is met deze leeggoedreferentie
	if(stuk_per_stuk && *s(8,50)){
	  searcnr_=*u(2,1)+30000; found_=NO;
		fasinit(4);*u(4,5)=searcnr_;mode_=1;
		FOREVER{
			if(faskeyi(4,4,mode_)) break; mode_=2;
			if(*u(4,5)!=searcnr_) break;
			if(*s(4,2)==journl && *u(4,4)>(ft_date-120) && *s(4,28) && cmpstr(s(4,28),s(8,50),15)==0){
				found_=YES; break;
			}
		}
		if(found_){
			zero(str_,sizeof str_);sprintf_s(str_,80,"Leeggoedreferentie %s is al geboekt...toch verdergaan?",s(8,50));
			if(DisplayWarning(str_,61,1) ==NO) goto redo;
		}
	}


#endif
	ori_prt2pdf_=prt2pdf; 
  load_sysnr(NO);
  if(chk_nr){
#if FLAG248
    ft_nr=last_vf+1;
#if BOEKKASF
    ft_nr=*u(8,2);/* nummer van kasfactuurke */
#endif
    if(ftchk()){
      FOREVER{
	scrget(2,138);
	scrifld(1,fm_uu5,&ft_nr);
	key=scrupd(1,0x82);
	if(key==102) goto redo;
	ftchk();
	if(errnum==0) break;
      }
    }
#else
    if(upd_mode==NO){
      *u(8,2)=last_vf+1;
 			copy(s(8,1),buf1000,fldlen(8,0));
			for(k=0;k<5;k++) { // voor het geval dat de vorige bonnr niet goed is weggeschreven
				if(faskeyi(8,2,0)) break;
				last_vf++; *u(8,2)=last_vf+1;
			}
			copy(buf1000,s(8,1),fldlen(8,0));*u(8,2)=last_vf+1;
    }
#endif
  }
	else{
#if FLAG248 & !FT_HERAFDRUK
    if(ftchk()){ // indien F9 deze nummer, dan toch nog controleren op dubbele nummer bij facturatie
      FOREVER{
	      scrget(2,138);
	 		  scrifld(1,fm_uu5,&ft_nr);
			  key=scrupd(1,0x82);
			  if(key==102) goto redo;
			  ftchk();
			  if(errnum==0) break;
      }
    }
#endif
	}


#if BONSORT && (FLAG244 || (FLAG248 && BONFILE==NO))
  SortBon(0);
#endif
#if BONSEQNR && !FLAG248/* aantal updates van bon bijhouden */
  if(fldlen(8,52)) *u(8,52)+=1;
#endif
#if PRINTEXEC
  prt_error=NO; prt_KOPIE=NO; mail_direct_=NO;SendViaCodabox_=NO;
#if FLAG248 && !FT_HERAFDRUK && !EET_RIST
	if(BlockAutoSend==NO){
	  if(fldlen(2,121) && *s(2,121)=='J' && *s(8,22)=='J') mail_direct_=YES;
  	if(fldlen(2,122) && *s(2,122)=='J' && *s(2,21) && *s(8,22)!='J') mail_direct_=YES;
#if FACT2CODABOX
		if(fldlen(2,128) && (*s(2,128)=='P' || *s(2,128)=='E')/* && prt2pdf!=2 */){ SendViaCodabox_=YES;/* mail_direct_=NO; */} // indien peppol, dan niet mailen
#endif
  	if(fldlen(2,21) && *s(2,21)=='\0') {mail_direct_=NO;} // uit veiligheid
	}
#endif



#if FLAGARS
	if(sys2696) mail_direct_=NO; // nooit automatisch mailen vanuit B02
#endif
#if FLAG248 | FLAG242 | (FLAG244 && PRTBON2X)
#if FLAG248 | FLAG242
  if(YES){
#if FLAGEET & DRANKGIGANT & !FT_HERAFDRUK & !KAS2FACT
	if(*pu_8_28<2) *pu_8_28=2;
#endif
#if FLAGDU3 && (KAS2JMCBON || KAS2JMCFACTUUR) // facturen aan kassa op A4 tijdelijk tot kettingpapier op is (maart 2019)
/*	if(*pu_8_28<2) */ *pu_8_28=2;
#endif
#else
  if(prt_levbon=='J'){
#endif
    q_exemp_=*pu_8_28;
#if FLAG244 | FLAG242
#ifdef PRTBON_Q
    q_exemp_=PRTBON_Q;
		if(FactureerBonDirect) q_exemp_=1; // maar 1 keer afdrukken als hij direct wordt gefactureerd (knop)
#if PRTLAADBON && !FLAGAST 
	if(upd_mode==NO) q_exemp_=1; // laadbon maar 1 keer
#endif
#endif
#endif
#if FLAG248// && (SAVEPDFFACTUUR || NO_FT_KOPIEPRT)
	if(prt2pdf==1) {ft_prt();prt2pdf=0; q_exemp_--;}
#endif
	  if(q_exemp_!=1 && prt2pdf) q_exemp_=1;/* slechts 1x bij pdf/mail */
#if !FLAG248 && FLAGMIN
		if(upd_mode) q_exemp_=1;
#endif

#if (SAVEPDFFACTUUR || NO_FT_KOPIEPRT) && FLAG248 && !FT_HERAFDRUK
			q_exemp_-=2; // minstens 3 om een kopie af te drukken
#endif
		if(mail_direct_ || SendViaCodabox_ || prt2pdf==2){
#if !(SAVEPDFFACTUUR || NO_FT_KOPIEPRT)
			if(q_exemp_>1) {q_exemp_--;prt_KOPIE+=1;}
			else q_exemp_=1;
#endif
#if !FLAGSMM && !FLAGALB && !FLAGQIC  && !NO_FT_KOPIEPRT && !SAVEPDFFACTUUR
			if(def_qfact && q_exemp_<1) q_exemp_=1; 
#endif
#if !FLAG248
			q_exemp_=0; //  iet drukken als ge op mail drukt
#endif
		}
#if FLAGGRS || FLAGEET // indien pdf of mail, dan NOOIT drukken
		if(ori_prt2pdf_) q_exemp_=0;
#endif
		ori_prt2pdf_=prt2pdf; if(prt2pdf==2) prt2pdf=0; // anders gaat hij enkel file aanmaken
    for(k=0;k<q_exemp_;k++) {
		  ft_prt();
			prt_KOPIE+=1;
		}
		prt2pdf=ori_prt2pdf_; 
    if(prt_error){errnum=13;goto redo;}
		if(prt2pdf==2) {
			ft_prt();
			scrget(1,7);scrifld(1,VarTextFmt(25,0),"Mailen document...");scrupd(-3,0);
			_sleep(3000);
			MailDocument(0);prt2pdf=0;
		}
#if (FLAGAST || FLAGWYN || FLAGFIS) && FLAG244
    if(NO){  // geen F4/F5 bij bons
#else
    if(stuk_per_stuk && FactureerBonDirect==NO){
#endif
      FOREVER{
				scrget(2,28);key=scrupd(0xFFFF,0xF58);
				if(key==105) break;
				if(key==104) ft_prt();
#if !BONSEQNR
				if(key==107) goto redo;
				if(key==112) {
					if(DisplayWarning("Wenst u echt dit document te annuleren?",61,1)==YES){ClearSysPosNrCheck();return NO;}
				}
#endif
			}
    }
		if((SendViaCodabox_ || mail_direct_) && prt2pdf!=2){
			if(SendViaCodabox_){
				ori_prt2pdf_=prt2pdf;prt2pdf=2; prt_KOPIE=0; ft_prt();prt2pdf=ori_prt2pdf_;
				if(*s(8,25)=='\0'){
				  if(*u(8,8)==0) *u(8,8)=ft_date;
				  jddate(*u(8,8),&Year,&Month,&Day);sprintf_s(s(8,25),fldlen(8,25),"%02d/%02d/%04d",Day,Month,Year);
			  }
				scrget(1,7);scrifld(1,VarTextFmt(25,0),"Versturen document...");scrupd(-3,0);
				*u(8,2)=ft_nr; *u(8,8)=ft_date;MailMergeBijlage[0]=SpoolFileNr;
#if FLAG248 & BONFILE
			  if(stuk_per_stuk==NO) _sleep(3000);  // probleem foute XML : 3 sec wachten zodat server op adem kan komen 
#endif
				FOREVER{
					if(ovlcall(2240,10)) break;
					zero(str_,sizeof str_);sprintf_s(str_,sizeof str_,"Communicatieprobleem PEPPOL - %30s - Nogmaals proberen?",s(2,3));
					if(DisplayWarning(str_,605,1)==NO){
						if(stuk_per_stuk) goto redo; else return NO;
					}
				}
			}

			if(mail_direct_){
				ori_prt2pdf_=prt2pdf;prt2pdf=2; prt_KOPIE=0; ft_prt();prt2pdf=ori_prt2pdf_;
				scrget(1,7);scrifld(1,VarTextFmt(25,0),"Mailen document...");scrupd(-3,0);
  			if(stuk_per_stuk==NO) _sleep(3000);  // probleem foute XML : 3 sec wachten zodat server op adem kan komen 
				FOREVER{
					if(MailDocument(1))break;
					if(DisplayWarning("Mailen NIET gelukt! Nogmaals proberen?",605,1)==NO){
						if(stuk_per_stuk) goto redo; else return NO;
					}
				}
			}

    	if(fldlen(7,0) && ((mail_direct_ && MailUniqueID[0]!='\0') || (SendViaCodabox_ && CodaboxRefID[0]!='\0'))){
				fasinit(7);
				if(SendViaCodabox_){
					copy(CodaboxUniqueID,s(7,2),18); *i(7,5)=1; copy(CodaboxRefID,s(7,6),fldlen(7,6)); *u(7,7)=*u(8,77); *u(7,8)=*u(8,78);
				}
				else{
					copy(MailUniqueID,s(7,2),12);
				}
				*u(7,4)=*u(25,2); 
				*u(7,10)=2;*l(7,11)=*u(2,1);
				*u(7,15)=1;*u(7,16)=1+(procid/5);
				if(alg_tot>=0) k=copy0(facttxt[0],s(7,17),20);	else k=copy0(credntxt[0],s(7,17),20);
        stcli_d(s(7,17)+k,(long)(ft_nr),6,1);
				fasadd(7);
			}
			mail_direct_=NO; SendViaCodabox_=NO;
			q_exemp_--;
#if !FLAGSMM && !FLAGALB && !FLAGQIC  && !NO_FT_KOPIEPRT && !SAVEPDFFACTUUR
			if(def_qfact && q_exemp_<1) q_exemp_=1; prt_KOPIE+=1;
#endif
			k=fldlen(2,21); if(k>fldlen(8,55)) k=fldlen(8,55);copy(s(2,21),s(8,55),k); // als bewijs bijhouden 
		}

  }
#else
	if(prt_levbon=='J') {ft_prt();prt_KOPIE+=1;}
  if(prt_error)
#if FLAG244 | (BONFILE==NO)
    goto redo;
#else
    exit_hfdmenu();
#endif
	if(prt2pdf==2) {
		ft_prt();
		scrget(1,7);scrifld(1,VarTextFmt(25,0),"Mailen document...");scrupd(-3,0);
		_sleep(3000);MailDocument(0);prt2pdf=0;
	}
#if PRTBONRET
  FOREVER{
#if FLAG244 & BON2FACTUUR
		if(FactureerBonDirect) break; // niet vragen bij direct bon factureren
#endif
    scrget(2,28);key=scrupd(0xFFFF,0xF58);
    if(key==105) break;
    if(key==104) {ft_prt();prt_KOPIE+=1;}
#if !BONSEQNR
    if(key==107) goto redo;
		if(key==112){
			if(DisplayWarning("Wenst u echt dit document te annuleren?",61,1)==YES){ClearSysPosNrCheck();return NO;}
		}			
#endif
  }
#endif
#endif
#endif
  scrget(1,7);scrupd(-3,0);
  if(free!=-1){
#if ARTEXIST && FLAG244 && STOCK244/* stock aanpassen op bon-niveau */
    change_=YES;
#if BVI_flag/* gekoppeld aan vraag mag gefactureerd worden */
    if(upd_mode){
      copy(s(8,1),sortbuf,fldlen(8,0));
      fasgeti(8);
      if(*s(8,30)!='J') change_=NO;
      copy(sortbuf,s(8,1),fldlen(8,0));
    }
#endif
    if(upd_mode && change_==YES){/* vorige stock corrigeren */
      fasinit(58);*u(58,2)=*u(8,1); mode_=1;
      FOREVER{
	if(faskeyi(58,1,mode_)) break; mode_=2;
	if(*u(58,2)!=*u(8,1)) break;
	upd_artstock(YES);
      }
    }
    for(k=0;k<max_line;k++){/* stock bijwerken */
      ram2stu(k);
#if BVI_flag/* gekoppeld aan vraag mag gefactureerd worden */
      if(*s(8,30)=='J')
#endif
      upd_artstock(NO);
    }
#if 0
    if(scr_ok("Wenst U de stock aan te passen voor deze bon ???")){
      art_stat();
      if(fldlen(8,41)) *s(8,41)=YES;
    }
#endif
#endif
#if FICHEEXEC
		fasunlck(-2);
    if(stock_JN=='J' || stock_JN=='S'){
#if STATISTIEK
      statistiek_upd(NO);
#endif
#if HISTORIEK
      historiek_upd();
#endif
#if ARTEXIST && (!BONFILE || !STOCK244)
      if(art_exist  && stock_JN=='J') art_stat();
#endif
      if(k_omz_exist) klt_stat();
    }
#if FRI_flag
    else{/* wel statistieken bijwerken */
#if HISTORIEK
      historiek_upd();
#endif
#if STATISTIEK
      statistiek_upd(NO);
#endif
      if(k_omz_exist) klt_stat();
    }
#endif
#endif
#if FLAG248 & DUMP_CFT
    if(sys2940!=1) seqo_cft();
#endif
#if BOEKALLO & BOEKEXEC & !FT_HERAFDRUK
		fasunlck(-2);
    if(bkh_exist && boek_JN=='J') boekbkh();
#endif
#if FLAG248
    if(chk_nr || !bkh_exist){
      last_vf=ft_nr;
      sysput(last_vfa,2,&last_vf);
    }
#if !FT_HERAFDRUK && MAIL_FT2BKH && !EET_RIST 
    MailFactuur2Boekhouder(); // definieren in parlay.c cfr ERL
#endif

#if !FT_HERAFDRUK && FACT2XML && !EET_RIST
		if(OutputMapUbl[0]){
			if(*s(8,25)=='\0'){
				if(*u(8,8)==0) *u(8,8)=ft_date;
				jddate(*u(8,8),&Year,&Month,&Day);sprintf_s(s(8,25),fldlen(8,25),"%02d/%02d/%04d",Day,Month,Year);
			}
		  prt2pdf=2; ft_prt();
			scrget(1,7);scrifld(1,VarTextFmt(25,0),"Versturen document...");scrupd(-3,0);
#if FLAG248 & BONFILE
			if(stuk_per_stuk==NO) _sleep(3000);  // probleem foute XML : 3 sec wachten zodat server op adem kan komen 
#endif
  		*u(8,2)=ft_nr; *u(8,8)=ft_date;MailMergeBijlage[0]=SpoolFileNr;
#if FACT2XMLSPECIAL
#if FLAGVBE
      VBEFactuur2Pdf();
#endif
			if(ovltest(2141)) ovlcall(2141,0); else ovlcall(2240,11); 
#else
			ovlcall(2240,0);
#endif
		}
#endif
#else
    if(upd_mode==NO){       /* bonnummer ALTIJD wegschrijven bij nieuwe bon */
      last_vf=*u(8,2);
#if FLAGVRC || FLAGAST || FLAGFIS // niet bij F9 neem deze nummer
		if(chk_nr)
#endif
      sysput(last_vfa,2,&last_vf);

    }
#endif
		ClearSysPosNrCheck();
    sysflush();fasflush(0);
#if FLAG244 || (FLAG248 && !BONFILE && !FT_HERAFDRUK)
		for(k=0;k<2;k++){
			if(ovltest(2394) && *(uint16 *)(&BestelFileUsed[k][100])==2394){
#if FLAG248
		    if(ovlcall(2394,2)){ // boodschap sturen dat ie verwerkt is (=boodschap 01 sturen en renamen naar .DONE)
#else
				if(ovlcall(2394,1)){ // boodschap sturen dat ie ingegeven is (enkel renamen naar .OK) 
#endif
 //  			for(k=0;k<2;k++) if(BestelFileUsed[k][0] && *(uint16 *)(&BestelFileUsed[k][100])==2394) fasopen(BestelFileUsed[k],99); // deleten 
			    zero(BestelFileUsed[k],sizeof BestelFileUsed[0]); // om later te deleten
				}
			}
		}

#endif
#if FLAG248 && BONFILE && !FT_HERAFDRUK
		if(ovltest(2394)){ //	&& (*(uint16 *)(&BestelFileUsed[0][100])==2394 || (*s(8,24) && *(s(8,24)+fldlen(8,24)-1)==1))){
      copy(s(8,1),buf1000,fldlen(8,0));
			for(z=0;z<DIM8;z++){ // voor elke bon met CCEP-order dit met status 01 bevestigen
				if(rec_8[z]==0) break;
				fasinit(8);*u(8,1)=rec_8[z];fasgeti(8);
				if(*s(8,24) && *(s(8,24)+fldlen(8,24)-1)==1){
					if(ovlcall(2394,2)){ // boodschap sturen dat ie verwerkt is (=boodschap 01 sturen en renamen naar .DONE)
   					for(k=0;k<2;k++) if(BestelFileUsed[k][0] && *(uint16 *)(&BestelFileUsed[k][100])==2394) zero(BestelFileUsed[k],sizeof BestelFileUsed[0]);
						// bzero(BestelFileUsed,sizeof BestelFileUsed); // om later te deleten
					}
					else DisplayWarning("Bevestiging versturen naar Coca-Cola NIET gelukt. Doe dit manueel!",605,0);
				}
			}
			copy(buf1000,s(8,1),fldlen(8,0));
		}
#endif
	}
	if(ovltest(2241)){
		for(k=0;k<2;k++) if(BestelFileUsed[k][0]  && *(uint16 *)(&BestelFileUsed[k][100])==2241) {
			fasopen(BestelFileUsed[k],99); // deleten 
  		zero(BestelFileUsed[k],sizeof BestelFileUsed[0]); 
		}
	}
	if(ovltest(2295) || ovltest(2296)){
		for(k=0;k<2;k++) if(BestelFileUsed[k][0]  && (*(uint16 *)(&BestelFileUsed[k][100])==2295 || *(uint16 *)(&BestelFileUsed[k][100])==2296)){
			zero(str_,sizeof str_);
      for(n=0;n<100;n++) if(BestelFileUsed[k][n]=='\0') break;
			copy(BestelFileUsed[k],str_,n);str_[n]='|';
			copy(BestelFileUsed[k],&str_[n+1],n);
			for(n=0;n<200;n++) if(str_[n]=='\0') break;
			copy("DONE",&str_[n-3],4);
			fasclos(-2);
			fasopen(str_,100);  // renamen naar .DONE				
			zero(BestelFileUsed[k],sizeof BestelFileUsed[0]); 
		}
	}
  fuval=YES;
  endsr:;
  return fuval;
}

#if FLAGEPD && !FLAG255 // betalingsgegevens laden van bon/factuur
static int LoadBetaling(uint16 krec_, uint16 nr_, uint16 date_, uint16 bonmode_) // bonmode_ : 1= bon, 0=factuur
{
	uint16 searcnr,bonnr_,sw;
	int16 j,k,found_=NO,mode_,r_yy_,r_jr_,r_vl_;
	char str_[10],buf100_[100];
	long rec4_;
	 
	searcnr=krec_+30000; if(BetCount>=20) return BetCount;
	if(bonmode_==NO){ // factuur
		fasinit(4);*u(4,5)=searcnr;mode_=1;
		FOREVER{
			if(faskeyi(4,4,mode_)) break; mode_=2;
			if(*u(4,5)!=searcnr) break;
			if(*s(4,2)==journl && *u(4,3)==nr_){found_=YES; break;}
		}
		if(found_==NO) return 0;
		r_yy_=*s(4,8);r_jr_=*s(4,9);r_vl_=*u(4,10);rec4_=*l(4,1);
		fasinit(4); *u(4,5)=searcnr; *s(4,8)=r_yy_;*s(4,9)=r_jr_;*u(4,10)=r_vl_;mode_=1; 
		FOREVER{
			if(faskeyi(4,4,2)) break; mode_=2;
			if(*u(4,5)!=searcnr) break;
			if(r_yy_!=*s(4,8) || r_jr_!=*s(4,9) || r_vl_!=*u(4,10)) break;
			if(*l(4,1)!=rec4_){
				BetTabel[BetCount].Datum=*u(4,4);
				BetTabel[BetCount].Bedrag=-*d(4,32);
				BetTabel[BetCount].Proces=*u(4,60);
				for(k=0;k<10;k++) if(*s(4,2)==PaySettings.Jnl[k]) break;
				if(k<10) BetTabel[BetCount].Bcode=PaySettings.BetCode[k];
				else BetTabel[BetCount].Bcode='O';
				BetCount++;
			}
			if(BetCount>30) break;
		}
	}
	else{ // bon
		fasinit(4);*u(4,5)=searcnr;mode_=1;
		FOREVER{
			if(faskeyi(4,4,mode_)) break; mode_=2;
			if(*u(4,5)!=searcnr) break;
			if(*s(4,8)!=0 || *s(4,9)!=0 || *u(4,10)!=0) break;
			if(cmpstr(s(4,28),"BON",3)==0){// betaling bon 
				j=0; zero(str_,sizeof str_);
				for(k=0;k<6;k++){
					if(*(s(4,28)+3+k)<'0' || *(s(4,28)+3+k)>'9') {
						if(j) break;
					}
					else str_[j++]=*(s(4,28)+3+k);
				}
			  bonnr_=val(str_);
				if(bonnr_==nr_){
					BetTabel[BetCount].Datum=*u(4,4);
					BetTabel[BetCount].Bedrag=-*d(4,32);
					BetTabel[BetCount].Proces=*u(4,60);
					for(k=0;k<10;k++) if(*s(4,2)==PaySettings.Jnl[k]) break;
					if(k<10) BetTabel[BetCount].Bcode=PaySettings.BetCode[k];
					else BetTabel[BetCount].Bcode='O';
					BetCount++;
				}
			}
			if(BetCount>30) break;
		}
	}
  FOREVER{// sorteren 
    sw=NO;
    for(k=0;k<BetCount-1;k++){
			if(BetTabel[k].Datum>BetTabel[k+1].Datum || (BetTabel[k].Datum==BetTabel[k+1].Datum && BetTabel[k].Bcode>BetTabel[k+1].Bcode)){
				copy((char *)&BetTabel[k].Datum,buf100_,sizeof BetTabel[0]);
				copy((char *)&BetTabel[k+1].Datum,(char *)&BetTabel[k].Datum,sizeof BetTabel[0]);
				copy(buf100_,(char *)&BetTabel[k+1].Datum,sizeof BetTabel[0]);
				sw=YES;
			}
		}
		if(sw==NO) break;
	}
	return BetCount;
}
#endif

#if FLAGPED
static WarnKredietlimiet()
{
  int k,p_adr_=0,fld_adres_=21,key;
	uint16 dt_,nr_,yy,mm,dd;
	double bd_;
  
	FOREVER{
		redo:;
		scrget(1,170);
		scraddf(100,23,0,8); scrifld(100,VarTextFmt(7,0)," F4 Ja ");
		scraddf(101,23,8,8); scrifld(101,VarTextFmt(8,0)," F5 Nee ");
		scraddf(102,23,20,8); scrifld(102,VarTextFmt(33,0)," F9 stuur tekort-mail naar klant ");
		scraddpicto(1,0,32,1,12,6,61,0,3,"Opgelet!"); 
		scraddfield(200,7,12,0x2);scrifld(200,VarTextFmt(66,0),"Deze klant heeft zijn kredietlimiet overschreden! Toch doorgaan?");
		key=scrupd(-1,0x118);
		if(key==104){
#if FLAGPED
			if(CheckPw(1,2,0)){
#else
			if(CheckPw(1,3,0)){
#endif
			  scrget(1,7);scrupd(-3,0);return YES;
			}
		}
		else if(key==105) return NO;
		else if(key==109){ // mail sturen
	// keywords invullen 
			zero(MailMergeData[0],sizeof MailMergeData); MailSaveAdres='N';
			dt_=*u(25,2);
			bd_=*l(2,45);
			for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
				if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy(s(2,3),MailMergeData[k],fldlen(2,3)); continue;}
				if(cmpstr(MailMergeKeywords[k],"ADRES",5)==0){copy(s(2,4),MailMergeData[k],fldlen(2,4)); continue;}
				if(cmpstr(MailMergeKeywords[k],"POSTCODE",8)==0){copy(s(2,5),MailMergeData[k],fldlen(2,5)); continue;}
				if(cmpstr(MailMergeKeywords[k],"GEMEENTE",8)==0){copy(s(2,6),MailMergeData[k],fldlen(2,6)); continue;}
		
				if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){p_adr_=k;copy(s(2,fld_adres_),MailMergeData[k],fldlen(2,fld_adres_)); continue;}
				if(fldlen(2,130) && fld_adres_==21 && cmpstr(MailMergeKeywords[k],"CC_EMAILADRES",13)==0){copy(s(2,130),MailMergeData[k],fldlen(2,130)); continue;}
				if(cmpstr(MailMergeKeywords[k],"DATUM",5)==0){
					jddate(dt_,&yy,&mm,&dd);
					stcli_d(&MailMergeData[k][0],(long)dd,2,0);MailMergeData[k][2]='/';
					stcli_d(&MailMergeData[k][3],(long)mm,2,0);MailMergeData[k][5]='/';
					stcli_d(&MailMergeData[k][6],(long)yy,4,0);
					continue;
				}
				if(cmpstr(MailMergeKeywords[k],"TOTAALBEDRAG",12)==0){double2str(MailMergeData[k],(double)(bd_)); continue;}
				if(cmpstr(MailMergeKeywords[k],"FIRMATELEFOON",13)==0){copy(&firma[116],MailMergeData[k],15); continue;}
				if(cmpstr(MailMergeKeywords[k],"FIRMAEMAIL",10)==0){copy(&firma[222],MailMergeData[k],30); continue;}
			}
			zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage); // voor de veiligheid
			zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);
			zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate); copy("KREDL",MailMergeSpecialTemplate,5);
			MailMergeFormaat=10; 
			if(fldlen(2,24)) MailMergeTaal=talen[taaltxt]; else MailMergeTaal='\0';
			k=SendMail(0); 
			if(k && MailSaveAdres=='J'){copy(MailMergeData[p_adr_],s(2,fld_adres_),fldlen(2,fld_adres_));fasupd(2);} // email adres bewaren
			goto redo;
		}
		else goto redo;
	}
  return NO;
}
#endif


static MailDocument(SendMode)
int SendMode;
{
  int k,p_adr_=0,fld_adres_=21;
	uint16 dt_,nr_,yy,mm,dd;
	char mailprofiel_;
	double bd_;
	  
		// keywords invullen 
#if FLAGWLM
	mailprofiel_=0;
#if SPEC_LAYOUT  // Beercompany
	mailprofiel_=1;
#endif
	sysput(18481,1,&mailprofiel_);
#endif
	zero(MailMergeData[0],sizeof MailMergeData); MailSaveAdres='N';
#if FLAG248
	dt_=ft_date;nr_=ft_nr;
  if(fldlen(2,129) && *s(2,129)) fld_adres_=129; // apart bkh-adres
#else
	dt_=*u(8,8);nr_=*u(8,2);
#endif
	bd_=alg_tot;
	for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
		if(cmpstr(MailMergeKeywords[k],"FIRMANAAM",4)==0){copy(&firma[0],MailMergeData[k],30); continue;}
		if(cmpstr(MailMergeKeywords[k],"NAAM",4)==0){copy(s(2,3),MailMergeData[k],fldlen(2,3)); continue;}
		if(cmpstr(MailMergeKeywords[k],"ADRES",5)==0){copy(s(2,4),MailMergeData[k],fldlen(2,4)); continue;}
		if(cmpstr(MailMergeKeywords[k],"POSTCODE",8)==0){copy(s(2,5),MailMergeData[k],fldlen(2,5)); continue;}
		if(cmpstr(MailMergeKeywords[k],"GEMEENTE",8)==0){copy(s(2,6),MailMergeData[k],fldlen(2,6)); continue;}
		
		if(cmpstr(MailMergeKeywords[k],"EMAILADRES",10)==0){p_adr_=k;copy(s(2,fld_adres_),MailMergeData[k],fldlen(2,fld_adres_)); continue;}
		if(fldlen(2,130) && fld_adres_==21 && cmpstr(MailMergeKeywords[k],"CC_EMAILADRES",13)==0){copy(s(2,130),MailMergeData[k],fldlen(2,130)); continue;}

		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNAAM",12)==0){
			 if(alg_tot>=0) copy0(facttxt[taaltxt],MailMergeData[k],50);
			 else copy0(credntxt[taaltxt],MailMergeData[k],50);
			 continue;
		}
		if(cmpstr(MailMergeKeywords[k],"DOCUMENTNUMMER",13)==0){stcli_d(MailMergeData[k],(long)nr_,5,1); continue;}
		if(cmpstr(MailMergeKeywords[k],"DATUM",5)==0){
			jddate(dt_,&yy,&mm,&dd);
      stcli_d(&MailMergeData[k][0],(long)dd,2,0);MailMergeData[k][2]='/';
      stcli_d(&MailMergeData[k][3],(long)mm,2,0);MailMergeData[k][5]='/';
      stcli_d(&MailMergeData[k][6],(long)yy,4,0);
			continue;
		}
		if(cmpstr(MailMergeKeywords[k],"TOTAALBEDRAG",12)==0){double2str(MailMergeData[k],(double)(bd_)); continue;}
	}
	zero((char *)&MailMergeFileBijlage[0][0],sizeof MailMergeFileBijlage); // voor de veiligheid
#if FLAG248 && !FLAGGBL
	if(ExtraBijlageFactuurmail[0]){
		if(FileExist(ExtraBijlageFactuurmail))  copy(ExtraBijlageFactuurmail,MailMergeFileBijlage[0],sizeof ExtraBijlageFactuurmail);
	}
#endif
	zero((char *)&MailMergeBijlage[0],sizeof MailMergeBijlage);MailMergeBijlage[0]=SpoolFileNr;
	zero(MailMergeSpecialTemplate,sizeof MailMergeSpecialTemplate);
#if FLAG248
	MailMergeFormaat=11; 
#if FLAGWLM && SPEC_LAYOUT  // Beercompany
	MailMergeFormaat=12; 
#endif
#else
	MailMergeFormaat=10; 
#endif
	if(fldlen(2,24)) MailMergeTaal=talen[taaltxt]; else MailMergeTaal='\0';
	k=SendMail(SendMode); 
	if(k && MailSaveAdres=='J'){copy(MailMergeData[p_adr_],s(2,fld_adres_),fldlen(2,fld_adres_));fasupd(2);} // email adres bewaren
#if FLAGWLM
	mailprofiel_=0;	sysput(18481,1,&mailprofiel_); // resetten
#endif
	return k;
}

static int double2str(ps_,bd_)
char *ps_;
double bd_;
{
  int k,len_=0;
  char buff[15];
  double bedrag_,add_=0;
  long val_,value;
							
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*100+add_;value=val_/100;
 
  zero(buff,sizeof buff);
  stcli_d(&buff[0],value,10,1);
  for(k=0;k<10;k++){
    if(buff[k]=='\0') break;
    if(buff[k]!=' ') *(ps_+len_++)=buff[k];
  }
  value=val_-value*100;
  if(value){
    *(ps_+len_++)=',';
    if(value<0) value=-value;
    zero(buff,sizeof buff);
    stcli_d(&buff[0],value,2,0);
    for(k=1;k>=0;k--) if(buff[k]!='0') break;
    copy(&buff[0],ps_+len_,k+1);len_+=k+1;
  }
  return len_;
}

static dsp_hoofding()
{
  int16 j,k,ok_,ret_,new_document_,kol,dd,mm,jj;
  char byte,ori_prxnr_;
  uint16 dt_,rec_;

#if FLAG244 | (BONFILE==NO)
redo_full:;
	if(fldlen(8,40)) ori_prxnr_=*s(8,40);
  if(hfd_scr(NO)==YES) return YES;
  taal_nr=0; if(fldlen(2,24)) taal_nr=*s(2,24); UseAKPrijs=NO;prxnr=0;
  if(fldlen(8,40) && *s(8,40)) prxnr=*s(8,40); else prxnr=*s(2,26);
	if(prxnr=='A') UseAKPrijs=YES; else prxnr=prxnr-'0';
  if(prxnr<0 || prxnr>9) prxnr=0;
  if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
  if(!UseAKPrijs && (sys3894 & (1<<prxnr))) def_inc='J';
  else def_inc='N';
  if(fldlen(8,40) && upd_mode && *s(8,40)!=ori_prxnr_){
		if(DisplayWarning("Wenst U de prijzen van de artikels op bon te wijzigen naar nieuwe prijstype?",61,1)==YES) {
			for(k=0;k<max_line;k++){ram2stu(k);*f(58,20)=0;*f(58,21)=0;*u(58,17)=0;stu2ram(k);}
		}
	}
#if ARTEXIST
  FOREVER{
    if(fldlen(6,3+taal_nr)) break;
    taal_nr=0;
  }
#endif
	new_document_=YES; if(keepdata) new_document_=NO;
	if(new_document_==NO && *u(8,1)==0 && BestelFileUsed[0][0] && *(uint16 *)(&BestelFileUsed[0][100])==2394) new_document_=YES; // bij CocaCola toch toevoegen
	if(fldlen(22,7)) DispInfoAlarm(2);
  if(fldlen(62,1)){
    fasinit(62);*u(62,2)=*pu_2_1; ok_=NO;
    if(faskeyi(62,1,0)==0){
      for(k=0;k<5;k++) if(*s(62,5+k)) break;
      if(k<5) ok_=YES;
#if !KAS2JMCFACTUUR & !KAS2JMCBON 
      for(k=0;k<30;k++) if(fldlen(62,12+k*5) && *u(62,12+k*5)) break;
      if(k<30) ok_=YES;
#endif
    }
    if(ok_){
#if !KAS2JMCFACTUUR & !KAS2JMCBON 
      if(ovltest(2922)){
#if FT_HERAFDRUK // geen afhalen laten toevoegen bij herafdruk
				ret_=ovlcall(2922,1);
#else
				ret_=ovlcall(2922,2);
#endif
				if(ret_==0) goto redo_full;
				if(ret_==2){
					if(keepdata==NO) init58(0,NO);
					/* if(*s(62,9))*/ add_afhaling(-1);
					for(k=0;k<30;k++){
						if(fldlen(62,12+k*5) && *u(62,12+k*5)) add_afhaling(k);
					}
					/* if(*s(62,9))*/ add_afhaling(99);
				}
      }
      else DisplayMemo(2);
#else
// wordt bij zoeken klant getoond			klt_memo();
#endif
      fasupd(62);
    }
  }

#if DEF_INPUT
#if !FLAGAST
  if(new_document_){
		LoadArtikelsFromBestelbonKlant();
  }
#endif
#endif
#endif
#if (FLAG244 && !KAS2JMCBON) || (FLAG248 && !BONFILE && !FT_HERAFDRUK && !KAS2JMCFACTUUR) // mogelijke verhuringen tonen bij nieuwe bon/factuur 
#if FLAGCRA
	if(NO){ // nooit tonen bij CRA
#else
	if(ovltest(264)){
#endif
#if FLAG244
	  if(upd_mode==NO)
#endif
		LoadVerhuring();
	}
#endif
	

  if(keepdata==NO) init58(0,NO);
#if FACT2CODABOX && FLAG248 && !FT_HERAFDRUK
	if(CheckPeppolKlant=='J' && fldlen(2,128) && *s(2,128)!='P' && *l(2,10)!=999999999 && *l(2,10)!=0){ // automatisch versturen via pweppol indien geregistreerd
		if(ovlcall(2240,20)>0){*s(2,128)='P'; fasupd(2);}
	}
#endif
  if(verv_dt==0){
    copy(s(2,13),verv_term,3); verv_term[3]='\0';
		if(cmpstr(verv_term,"E9",2)==0){ // 1-15 : 5-de volgende maand, erboven de 20-ste volgende maand
			jddate(ft_date,&jj,&mm,&dd); jj%=100;
			if(dd<=15) dd=5; else dd=20;
			mm++; if(mm>12) {mm=1; jj++;}
			verv_dt=datejd(jj,mm,dd);
		}
		else{
			k=0; if(verv_term[0]=='E') k=val(&verv_term[1]);
			if(k>5){/* DSB : einde maand + x dagen */
				verv_dt=dateadd(ft_date,"E0"); verv_dt+=k;
			}
			else verv_dt=dateadd(ft_date,verv_term);
		}
  }
#if DISCONTO
  if(disk_dt==0 && len2_14){
    copy(s(2,15),verv_term,3);
    disk_dt=dateadd(ft_date,verv_term);
  }
#endif
  select_mnt();
  if(keepdata==NO){
    init58(0,NO);
    fasclos(-2);
#if FILETXT
#if FLAGVRL || FLAGVLA
    copy(txtfile,nm_dehr,sizeof txtfile);
#else
    copy("factx.txt",nm_dehr,10);
    nm_dehr[4]=talen[taaltxt];
#endif
    if(fasopen(nm_dehr,1)) goto next;
		inp_clr();k=0;kol=0;
    FOREVER{
      byte=get_byte();
      if(!byte) break;
      if(kol==0) ram2stu(k);
      if(byte==0x0D){
	get_byte();/* skip linefeed */
	stu2ram(k++);kol=0;
      }
      else{
	if(kol<fldlen(58,16)) *(ps_58_16+kol++)=byte;
      }
    }
    keepdata=YES;
    fasclos(-2);
#endif
    next:;
  }
#if !DKR_flag
#if FLAGAST
	if(*s(2,71)=='J') btw_glob=0; // BTW-eenheid
#endif
#if FLAGBSA // enkel in sommige firma's BTW op 0 zetten bij buitenl.BTWnummer
  if(!sys2696 && *s(2,22) && btw_glob==99) btw_glob=0;
#else
#if !KAS2JMCBON && !KAS2JMCFACTUUR && !KASINPUT && !FLAGVNT // NIET doen bij kassafacturen, want dan neemt hij BTW-in bedragen als exclusief
  if(fldlen(2,22) && *s(2,22) && *s(2,22)!='.' && btw_glob==99) btw_glob=0;
#endif
#endif
#endif
#if FLAGCOR || FLAGWAT
  if(fldlen(2,22) && *s(2,22)) set_allbtw(0.);
#endif
  semestpc=*f(2,56);
#if KM_HEFFING
  if(*f(8,46)){
		fasinit(6);*u(6,1)=RecLevKostArt; 
		if(fasgeti(6)==0) BtwLeveringskost=*f(6,28);
		else BtwLeveringskost=def_btw;
	}
#endif
	if(btw_glob!=99) BtwLeveringskost=btw_glob;
  return NO;
}
 
static LoadArtikelsFromBestelbonKlant(void)
{
	int k,max_,beg_,t_nr_;
	uint16 rec_;

	if(fldlen(2,120)<50) goto endsr;

  if(stat_klt==0) stat_klt=*pu_2_1;
  rec_=*pu_2_1;fasinit(2);*pu_2_1=stat_klt;fasgeti(2);
	for(k=max_line-1; k>=0;k--){ram2stu(k); if(test_line()) break;}
	if(k<=0){ init58(0,NO);k=0;}
	else k++;
  beg_=k; max_=fldlen(2,120)/2;
  if(max_>max_line) max_=max_line;
  for(k=0;k<max_;k++){
    ram2stu(beg_+k);
		fasinit(6);
    if(*pu_6_1=*(uint16 *)(s(2,120)+k*2)){
			fasgeti(6);
			*pu_58_14=*pu_6_1;
			copy(s(6,2),ps_58_15,len58_15);
			t_nr_=taal_nr;if(*s(6,3+t_nr_)=='\0') t_nr_=0;
			copy(s(6,3+t_nr_),ps_58_16,fldlen(58,16));
    }
    stu2ram(beg_+k);
  }
  fasinit(2);*pu_2_1=rec_;fasgeti(2);
  keepdata=YES;
	endsr:;
}

static hfd_scr(auto_peppol_)
int16 auto_peppol_;
{
  int16 curs=1,k,key,z,z_extra_,len_,ask_scrupd=YES,curspos_,smode_,curs_offset_,keymask_,hz_;
  char fld8_33,cmplast_toer_[50],buf100_[100];
  uint16 dt_,qfact_,rec_,krec_,q_weborders_=0;
	double kredietlimiet_;
  flag flag_qfact,fl_upd_all_=NO;

	if(ovltest(2241) || ovltest(2394) || ovltest(2295) || ovltest(2296))	zero(BestelFileUsed,sizeof BestelFileUsed); // om later te deleten
#if !FLAGJAC
	if(ovltest(2296)) q_weborders_=ovlcall(2296,3);
#endif
#if FLAG244 && TOER_UPD
  fasinit(63);*u(63,1)=*u(8,39); if(*u(63,1)) fasgeti(63);
	copy(s(63,1),cmplast_toer_,s(63,4)-s(63,1));
#endif
#if KASINPUT || KAS2JMCFACTUUR || KAS2JMCBON 
  if(stuk_per_stuk==NO){
    ask_scrupd=NO;
    for(k=0;k<6;k++){
      copy(s(2,2+k),s(8,13+k),fldlen(8,13+k));
    }
  }
#endif

	boek_JN='J';stock_JN='J';

  for(k=0;k<2;k++) *u(8,19+k)=last_vt[k];
  if(fldlen(8,30) && *s(8,30)=='\0') *s(8,30)=MAG_GEFACT;
#if FLAG244 | FLAG242
  if(fldlen(8,33)){if(fldlen(2,35)==0) *s(8,33)='N';}
#endif
#if FLAGSMM && FLAG244
  if(upd_mode==NO) copy(NaamWerkPost,s(8,50),fldlen(8,50));
#endif
#if FLAGPMC && FLAG242
	 copy0(facttxt[0],s(8,24),fldlen(8,24));
	 *s(8,33)='J';
#endif
  flag_qfact=NO; fld8_33=0;if(fldlen(8,33)) fld8_33=*s(8,33);
  if(upd_mode || ask_scrupd==NO) copy(ps_2_3,nm_dehr,len2_3);
  else zero(nm_dehr,sizeof nm_dehr);
	curs_offset_=0;
#if FLAG248
	if(fldlen(8,10)) curs_offset_=1;
#endif
	if(auto_peppol_) {key=5999;goto no_screen;}
  FOREVER{
    redo:
    qfact_=*pu_8_28;
    scrnum=0;scrget(2,SCRNUM);z=1;z_extra_=110;
#if FLAG244
    if(upd_mode && (fldlen(8,70) || fldlen(8,71) || fldlen(8,72))) scraddpicto(5,0,78,0,2,1,64,0,0x007FFF,"Info"); 
#endif
#if FLAG248 && FT_HERAFDRUK
    if(fldlen(8,76)) scraddpicto(6,0,76,0,4,2,537,0,0,"Info verzending"); 
#endif
    scrfld(z++,25,1);
   	scrfld(-z,2,3);z++;
		if(*(s(2,3)+fldlen(2,3)-1)=='!') scrchat(z-1,0xB);
	  else scrchat(z-1,0xFF);
#if !FT_HERAFDRUK		
		scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
		scraddpicto(2,z-1,2,0,2,1,64,0,4,"Klantenfiche");
		hz_=76;
#if FLAG244 || FLAG242 || (FLAG248 && !BONFILE && !FT_HERAFDRUK)
		if(ovltest(2394) && (upd_mode==NO || *s(8,24)=='\0') ) {scraddpicto(4,0,hz_,20,4,2,610,0,0,"Laad bestelling Coca-Cola"); hz_-=4;}
		if(ovltest(2241) && upd_mode==NO) {scraddpicto(3,0,hz_,20,4,2,77,0,4,"Laad klantbestelling"); hz_-=4;}
#if !FLAGJAC
		if(ovltest(2296) && upd_mode==NO) {
			if(q_weborders_) scraddpicto(7,0,hz_,20,4,2,32,0,4,"Laad weborder"); else scraddpicto(7,0,hz_,20,4,2,32,0,0,"Laad weborder");
			hz_-=4;
		}
#endif
#if FLAGVDW || FLAGDDB
		if(ovltest(2295) && upd_mode==NO) {scraddpicto(7,0,hz_,20,4,2,525,0,0,"Laad weborder"); hz_-=4;}
#endif
#endif
#endif 
#if FLAG244 & !KAS2JMCBON
		if(upd_mode) {scraddf(z_extra_,22,5,8);scrifld(z_extra_++,VarTextFmt(22,0)," F10 druk deze bon af ");} // enkel afdrukken 
#endif
	  if(klcd) scrofld(z++,8,13,-1); else z++;
    for(k=2;k<5;k++) scrofld(z++,8,13+k,-1);
#if FLAGVRL  || FLAGVLA
    scrifld(z++,fm_us20,txtfile);
#endif
#if FLAG248
    scrifld(z++,fm_udat,&ft_date);
		if(fldlen(8,10)) scrfld(z++,8,10); 
#endif
#if FLAG244 | FLAG242
#if FLAGPMC && FLAG242
		scrfld(z++,8,24);
#else 
    if(upd_mode==NO || fl_upd_all_) scrfld(z++,8,2); else scrofld(z++,8,2,-1);
#endif
    scrfld(z++,8,8);
#if !FLAG242
    if(fldlen(8,30)) scrfld(z++,8,30); else streepje(z++);
#endif
#endif
#if FLAG248
    scrifld(z++,fm_uu5,&ft_nr);
#else
#if FLAGCRA
		scrofld(z++,2,33,-1);
#else
    z++;
#endif
#endif
#if FLAG244
    scrifld(z++,fm_u_JN,&prt_levbon);
#endif
    for(k=0;k<2;k++) scrfld(z++,8,19+k);
    scrfld(z++,8,28);
    scrifld(z++,fm_uf21_,&btw_glob);
#if FLAG242
#if OFFERTE
    scrifld(z++,fm_udat,&verv_dt);
#endif
    goto puntx;
#endif
    scrfld(z++,8,26);
    fld_test(z++,8,23);
    fld_test(z++,8,21);
    fld_test(z++,8,22);
#if SELECT_PRTNR
      scrifld(z++,fm_uu2,&selprt12);
#endif

#if FICHEEXEC
    if(art_exist || k_omz_exist){			
			if(fl_upd_all_) scrifld(z++,fm_u_JNS,&stock_JN); else scrifld(z++,fm_os1,&stock_JN); 
		} else
#endif
    streepje(z++);

#if BOEKALLO & BOEKEXEC & !FT_HERAFDRUK
    if(bkh_exist){
      if(fl_upd_all_) scrifld(z++,fm_u_JN,&boek_JN); else scrifld(z++,fm_os1,&boek_JN);
//      scrifld(z++,fm_o_JN,&boek_JN);
      scrifld(z++,fm_us20,opm_bkh);
    }
    else
#endif
    {streepje(z++);streepje(z++);}

#if FLAG248 && !EET_RIST
    scrifld(z++,fm_udat,&verv_dt);
#else
    streepje(z++);
#endif

#if BOEKEXEC & DISCONTO | FLAGSAS | THV_flag | DISC244
    if(len2_14){
      scrfld(z++,2,14);
      scrifld(z++,fm_udat,&disk_dt);
    } else
#endif
    {streepje(z++);streepje(z++);}
#if AFHAALVERG || TRANS_KOST
    if(fldlen(8,31)) scrfld(z++,8,31); else
#endif
    streepje(z++);
#if LOSVERGOED 
    if(fldlen(8,32)) scrfld(z++,8,32); else
#endif
    streepje(z++);
#if FLAG244
    if(fldlen(8,33)) scrfld(z++,8,33);
    else z++;
#if FLAGJAC  // FLAGJAC : gebruikt voor proforma-factuur
    scrfld(z++,8,32); 
#endif
#endif
#if PALET_KORTING
    if(fldlen(8,34)) scrfld(z++,8,34);
#endif
    if(fldlen(8,40)) scrfld(z++,8,40); else z++; // afwijkend prijstype
#if KM_HEFFING 
    scrfld(z++,8,46);
#endif
#if FLAG244 && TOER_UPD
    scrfld(z++,63,3); scraddpicto(9,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
#endif
#if FLAGCRA && FLAG244
		scrofld(z++,2,34,-1);
#endif
#if FLAGCHA
    scrfld(z++,8,53);  // RES-%
#endif
#if EXTEND_KORT
    scrfld(z++,8,53);
    scrfld(z++,8,54);
#endif

    puntx:

#if FT_HERAFDRUK
    curs=-1;/* enkel bekijken */
#endif
    if(ask_scrupd==NO){ask_scrupd=YES;key=108;}
    else{
			keymask_=0xDE1;
#if FLAG244 & !KAS2JMCBON
			if(upd_mode) keymask_=0xFE1;
#endif
      key=scrupd(curs,keymask_);curs=1;
    }
		curspos_=fldcurs;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
no_screen:;
#if FLAG248 && FT_HERAFDRUK && FACT2CODABOX
		if(key==5999){
			*u(8,2)=ft_nr; 
			if(OutputMapUbl[0]){
 				if(*s(8,25)=='\0') sprintf_s(s(8,25),15,"%s-%05d","Peppol",ft_nr); 
  			calc();
	      prt2pdf=2; ft_prt();
		  	if(*u(8,8)==0) *u(8,8)=ft_date;
 		    *u(8,2)=ft_nr; *u(8,8)=ft_date;MailMergeBijlage[0]=SpoolFileNr;
			  scrnum=0;scrget(1,7);scrifld(1,VarTextFmt(25,0),"Versturen document...");scrupd(-3,0);
			  _sleep(3000);
#if _DEBUG
				ovlcall(2240,0);
#else
 				ovlcall(2240,10);	 
				seqo_cft(); // om ID en status weg te schrijven in ftkopie
#endif
			}
			return YES;
		}
#endif
    if(key==101 || key==106) return YES;
    if(key==111) ovl_exit(0);
		if(key==5003){
			if(ovlcall(2241,0)) keepdata=YES;
			else {errnum=14; goto redo;}
		}
		if(key==5004){
			copy(s(2,1),buf1000,fldlen(2,0));
			if(ovlcall(2394,0)){
				if(fldlen(2,18) && *f(2,18)){ // korting van klantenfiche invullen 
					for(k=0;k<max_line;k++){
						ram2stu(k);
						if(test_line()){
							if(*f(58,20)==0){*f(58,21)=*f(2,18); stu2ram(k);}
						}
					}
				}
				if(upd_mode) copy(buf1000,s(2,1),fldlen(2,0)); // originele klant terugzetten
				keepdata=YES;
			}
			else {copy(buf1000,s(2,1),fldlen(2,0));errnum=14; goto redo;}
		}
#if FLAG244
		if(key==5005){DisplayBonInfo(); curs=curspos_;goto redo;}
#endif
#if FLAG248 && FT_HERAFDRUK && FACT2CODABOX
		if(key==5006){
			*u(8,2)=ft_nr; 
			k=DisplayVerzendStatus(8,1); 
			if(k==99 && OutputMapUbl[0]){
				if(DisplayWarning("Wenst u echt deze factuur te versturen via peppol?",605,1)==YES){// echt versturen
  				if(*s(8,25)=='\0') sprintf_s(s(8,25),15,"%s-%05d","Peppol",ft_nr); 
	  			calc();
		      prt2pdf=2; ft_prt();
			  	if(*u(8,8)==0) *u(8,8)=ft_date;
  		    *u(8,2)=ft_nr; *u(8,8)=ft_date;MailMergeBijlage[0]=SpoolFileNr;
#if _DEBUG
					ovlcall(2240,0);
#else
  				ovlcall(2240,10);	 
					seqo_cft(); // om ID en status weg te schrijven in ftkopie
#endif
				}
			}
			curs=curspos_;goto redo;
		}
#endif
		if (key == 5007) {
			if (ovltest(2296)) {
				if (ovlcall(2296, 2)) {
					for (k = 0; k < 2; k++) {
						if (fldlen(8, 65 + k) && *s(8, 65 + k))
							copy(s(8, 65 + k), opm_foot[k], fldlen(8, 65 + k));
					}


					keepdata=YES;
				}
			  else {errnum=14; goto redo;}
			}
			else{
				if(ovlcall(2295,2)) keepdata=YES;
			  else {errnum=14; goto redo;}
			}
		}
		smode_=0;if(key==5001) smode_=98;
#if !FT_HERAFDRUK
		if(key==112){if(fl_upd_all_) fl_upd_all_=NO; else fl_upd_all_=YES; goto redo;}
#endif
    if(*pu_8_28!=qfact_) flag_qfact=YES;
    if(len8_23){
			if(*s(8,23)=='\0') copy(def_munt,s(8,23),len8_23);
      valu_cnv(s(8,23),def_munt,1.,1.);
      if(errnum){curs=curs_offset_+14;goto redo;}
    }
		select_mnt();
    if(smode_==98 || *pu_2_1==0 || cmpstr(ps_2_3,nm_dehr,len2_3)){
      if(search(2,smode_)) goto redo;

      copy(ps_2_3,nm_dehr,len2_3);
#if FLAGAST
	    if(*s(2,71)=='J') btw_glob=0; // BTW-eenheid
#endif
#ifdef REN_flag
      if(*s(2,22)) btw_glob=0;
#endif
      rec_=*pu_2_1;
      if(fldlen(2,51) && *u(2,51) && sys3918){
				*pu_2_1=*u(2,51);fasgetu(2);
      }
      for(k=0;k<6;k++){
	
#if EET_flag/* altijd kopieren */
				if(YES)
#else
				if(rec_!=*u(8,3) || upd_mode==NO)
#endif
			  copy(s(2,2+k),s(8,13+k),fldlen(8,13+k));
				if(fldlen(2,142+k) && *s(2,142+k)) copy(s(2,142+k),s(8,13+k),fldlen(8,13+k)); // afwijkend leveringsadres
      }
      *pu_2_1=rec_;fasgetu(2);
#if FLAG244 & KORT_DELAYED
#if NVJ_flag
      if(upd_mode==NO && *f(8,21)==0) *f(8,21)=*f(2,50);
#else
      if(upd_mode==NO && *f(8,21)==0 && *f(2,50)>0) *f(8,21)=*f(2,50);
#endif
#endif

#if !KAS2JMCFACTUUR && !KAS2JMCBON &&	!KAS2FACT && !FT_HERAFDRUK && !KASINPUT
#if KM_HEFFING
      if(upd_mode==NO && fldlen(8,46) && fldlen(2,41) && *f(8,46)==0) *f(8,46)=*f(2,41);
#endif
#if LEVERINGSKOST 
      if(upd_mode==NO && fldlen(8,46) && RecLevKostArt){
				fasinit(6);*u(6,1)=RecLevKostArt; 
				if(fasgeti(6)==0){
					get_prx(); BtwLeveringskost=*f(6,28);
					 if(*s(8,26)=='J') *pf_58_24=0;
					*f(8,46)=calc_prx;
				}
			}
#endif
#endif
      len_=*s(2,26)-'0';
      if(len_<0 || len_>9) len_=0;
      if(fldlen(6,PrNrs[len_])==0) len_=0;
      if(sys3894 & (1<<len_)) def_inc='J';
      else def_inc='N';
#if FLAG244 | FLAG242
      if(fldlen(8,33)){
				if(fldlen(2,35) && fld8_33=='\0'){*s(8,33)=*s(2,35);fld8_33=*s(8,33);}
      }
#endif
#if FLAGCHA
      copy(s(2,81),s(8,53),fldlen(8,53));
#endif
#if EXTEND_KORT
      copy(s(2,81),s(8,53),fldlen(8,53));
      copy(s(2,82),s(8,54),fldlen(8,54));
#endif
      if(fldlen(2,24)) taaltxt=*s(2,24);
      if(fldlen(2,23) && *s(2,23)) copy(s(2,23),ps_8_23,len8_23);
#if FLAG244 && TOER_UPD
			if(fldlen(2,38) && *s(2,38) && !(upd_mode==NO && ViaToer)){
				fasinit(63); zero(cmplast_toer_,sizeof cmplast_toer_);copy(s(2,38),s(63,3),fldlen(63,3));
  		}
#endif
#if FLAGAST
  for(k=0;k<10;k++) if(*u(2,1)==loc_klt[k]) break;  // indien klant een kassaklant is, dan steeds dit filiaal nemen
  if(k<10 && loc_nr[k]) *u(8,48)=loc_nr[k];
	else if(*u(8,48)==0){
		if(WerkpostFiliaalNr && WerkpostFiliaalNr<=10 && nm_loc[WerkpostFiliaalNr-1][0]) *u(8,48)=WerkpostFiliaalNr;
		else if(DefaultFiliaal) *u(8,48)=DefaultFiliaal; // firma in apart journaal
	}
#endif
#if FLAGALS
			*u(8,48)=*u(2,72);
#endif
    }
		if(key==5002){ovlcall(2921,1); curs=curspos_; goto redo;}
    k=ftchk();if(errnum){curs=curs_offset_+k+7;goto redo;}
#if FLAG248 & !FT_HERAFDRUK & !KASINPUT
		if(fldlen(8,10) && *u(8,10)==0) *u(8,10)=ft_date;
#endif
    if(flag_qfact==NO && fldlen(2,36)) *pu_8_28=*u(2,36);
#if FLAGPMC && FLAG242
		*pu_8_28=1;
#endif 
#if FLAG244
		if(*u(8,8)==0){curs=8;errnum=38;goto redo;}
#endif
    if(def_qfact && *pu_8_28<1){
#if FT_HERAFDRUK			
		  *pu_8_28=1;
#else
			errnum=38;curs=curs_offset_+11;goto redo;
#endif		
		}
#if KMP_flag & !FT_HERAFDRUK & !KASINPUT
    if(*s(8,22)=='J' && *f(8,21)==0){curs=curs_offset_+15;errnum=38;goto redo;}
#endif

#if SELECT_PRTNR
    if(selprt12<1 || selprt12>3) {errnum=34;goto redo;}
#endif
#if FLAG244 && TOER_UPD
		if(key==5009){
			if(search(63,98)) goto redo;
		}
    else if(*s(63,3)){
			if(cmp_str(s(63,1),cmplast_toer_,s(63,4)-s(63,1))){
        if(search(63,0)) goto redo;
			}
    }
    else {fasinit(63);}
    *u(8,39)=*u(63,1); copy(s(63,1),cmplast_toer_,s(63,4)-s(63,1));
#endif
		if(key==18){curs=curspos_+1;	goto redo;}
#if FLAG244 & !KAS2JMCBON
		if(key==110){
			select_mnt();
			calc(); 
#if FLAGVOE
			for(k=0;k<2;k++)
#endif
			  ft_prt();
			return YES;
		}
#endif
		if(key!=108 && key!=109) goto redo;
#if BLOK_KLANT && BOEKALLO && !FT_HERAFDRUK
		krec_=*pu_2_1;
#if FLAG244  // indien facturatieadres, dan checken op facturatieklant
		if(fldlen(2,51) && *u(2,51)){
			*pu_2_1=*u(2,51);fasgeti(2);
		}
#endif
#if FLAGDDB && FLAG244
		klt_saldo=getsaldo((uint16)(*pu_2_1+(uint16)30000));
		if(TotaalVervallenFacturen>0 || (*l(2,45) && klt_saldo>=*l(2,45))){
			fasinit(2);*pu_2_1=krec_;fasgeti(2);
			zero(buf100_,sizeof buf100_);
			sprintf_s(buf100_,85,"Openstaand saldo van %5.2f EUR (%5.2f vervallen)! Toch doorgaan?",klt_saldo,TotaalVervallenFacturen);
      if(DisplayWarning(buf100_,605,1)==NO) goto redo;
		}
		fasinit(2);*pu_2_1=krec_;fasgeti(2);
		goto saldo_OK;
#endif


#if FLAGDKR && FLAG244
		klt_saldo=getsaldo((uint16)(*pu_2_1+(uint16)30000));
		if(TotaalVervallenFacturen>0){
			zero(buf100_,sizeof buf100_);
			sprintf_s(buf100_,75,"Klant heeft vervallen facturen voor %5.2f EUR! Toch doorgaan?",TotaalVervallenFacturen);
      if(DisplayWarning(buf100_,605,1)==NO) goto redo;
		}
#endif


		kredietlimiet_=0; if(fldlen(2,45)) kredietlimiet_=*l(2,45);
		if(kredietlimiet_){
			klt_saldo=getsaldo((uint16)(*pu_2_1+(uint16)30000));
		}
		fasinit(2);*pu_2_1=krec_;fasgeti(2);
#if FLAGVRC
		if(kredietlimiet_ && klt_saldo>=kredietlimiet_ && FlagVervallenFacturen){
#else
		if(kredietlimiet_ && klt_saldo>=kredietlimiet_){
#endif
#if FLAGPED
			if(WarnKredietlimiet()!=YES) {errnum=63;goto redo;}
#else
			if(DisplayWarning("Deze klant heeft zijn kredietlimiet overschreden! Toch doorgaan?",61,1)!=YES) {errnum=63;goto redo;}
#endif
		}	
saldo_OK:;
#endif

		if(key==109){
#if !FLAG248 && (FLAGGBL || FLAGCRL)
			key=108; break; // nooit bij bons
#endif
			if(DisplayWarning("Wenst U echt een afwijkende bon/factuurnummer te gebruiken?",605,1)==YES) break;
		}
		if(key==108) break;
  }
#if BONSEQNR && !FLAG248
  if(key==109) key=108;/* altijd nieuwe nummer */
#endif
  chk_nr=YES;
  if(key==109) chk_nr=NO;
#if EET_RIST
  chk_nr=NO;
#endif
	 orig_klt=*pu_2_1;
#if FLAG248
   if(fldlen(2,51) && *u(2,51) && sys3918==NO) {/* vanaf nu in stu-2 het FACT-adres*/
#if LEV_OMZET
#if FLAGALB 
		if(*s(2,52)=='J')  // afhankelijk per klant, PAS OP : relatieadres hiervoor gebruikt!
#endif
    stat_klt=*pu_2_1;
#endif
		if(fldlen(8,12)) *u(8,12)=*pu_2_1; // record# lev.adres
    *pu_2_1=*u(2,51);fasgeti(2);
  }
  *u(8,8)=ft_date;
#endif
#if FLAG244 | FLAG242/* bijhouden van laatst gebruikte datum */
  if(upd_mode==NO) ft_date=*u(8,8);
#endif
  for(k=0;k<2;k++) last_vt[k]=*u(8,19+k);

#if FLAGDU4 && FLAG244 && ARTEXIST
	for (k = 0; k < 2; k++) {
		if (BestelFileUsed[k][0] && (*(uint16 *)(&BestelFileUsed[k][100]) == 2296))
			break;
	}
							
	if (k < 2) {
		// We hebben een weborder
		for (k = 0; k < max_line; k++) {
			ram2stu(k);
			fasinit(6);
			*u(6, 1) = *u(58, 14);

			if (*u(6, 1) && fasgeti(6) == 0) {
				Fill58FromNewArtikel(k);
			}
		}

		SortBon(101);
	}
#endif

  endsr:;
  return NO;
}

#if SCREXEC
static dsp_detail()
{
  int16 curs=1,j,tlen_,key,k,start_=0,k_k,pos_15,err_pos=0,t_nr_,m,nstart_,curspos_,kleur_;
  uint16 rec_,mask_;
  BEDRAG waarde=0;
  float vp_,bdf_,tot_qlv_,qlv_, tot_hl_;
  flag sr_nm;
  char *pdum,dumm_[10],*pvar,attr_;
  pdum=&dumm_[0];
 
#if SCREXEC==NO
  return YES;
#else
#if KASINPUT
  if(stuk_per_stuk==NO) return YES;
#endif
#if !FT_HERAFDRUK
  if(btw_glob!=99) set_allbtw(btw_glob);
#endif
  q_per_line=1;
#if FLAGVRL // GEEN lijnnrs owv plaatsgebrek
	q_per_line=0; 
#endif
  for(k=0;k<sizeof det_nr/2;k++){
#if FLAGSEG
    if(det_nr[k]==21) det_nr[k]=22;
    if(det_nr[k]==26) det_nr[k]=60;
#endif
#if FLAGDUB || FLAGFLI
    if(det_nr[k]==26) det_nr[k]=60;
#endif
    if(det_nr[k]==15) pos_15=q_per_line;
    if(fldlen(58,det_nr[k])>0) q_per_line++;
  }
#if KN_JOURNL && !BONFILE
	tlen_=12;
#else
  for(tlen_=0;tlen_<15;tlen_++) if(facttxt[0][tlen_]=='\0') break;
#endif
#if STOCK_OP_LOCATIE
	if(fldlen(8,48)){
		filiaal=*u(8,48);
    if(filiaal==99 || filiaal==0) copy("DEPOT",nm_fil,6);
    else if(filiaal>0 && filiaal<=10 && fldlen(66,11+(filiaal-1)*15) && nm_loc[filiaal-1][0]) copy(nm_loc[filiaal-1],nm_fil,6);
	  else zero(nm_fil,sizeof nm_fil);
	}
#endif	  
  FOREVER{
    redo:
    scrget(2,27); 
#if !FT_HERAFDRUK && !KASINPUT && (FLAG244 || (FLAG248 & !BONFILE)) 
		scraddpicto(1,0,76,22,4,2,514,0,0,"Extra opties"); 
#endif
#if FLAG244 && PRTFEESTBON
		scraddpicto(3,0,59,0,4,2,542,0,0,"Ingave retour feestbon"); 
#endif
    copy(fm_os79,fmt,sizeof fm_os79);fmt[2]=tlen_;
    scraddf(199,0,80-tlen_,6);
#if KN_JOURNL && !BONFILE
	  scrifld(199,fmt,"Creditnota's");
#else
    scrifld(199,fmt,facttxt[0]);
#endif
#if BARC_USED
    scraddf(195,22,55,2);
    scrifld(-195,fm_us20,werkveld);
		scraddfield(300,0,0,0xAA);
		scrifld(300,fm_os59,"^0A^08|^12");
#endif
    zz=1;
    scrofld(zz++,2,3,-1);
    scrfld(zz++,8,25);

#if FLAGWYN
    scrfld(zz++,8,24);
#endif
#if FLAGJAC
		tot_qlv_=0; for(k=0;k<max_line;k++) {ram2stu(k);if(*f(58,7)) tot_qlv_+=*f(58,31);}
		scrifld(zz++,fm_of6_0,&tot_qlv_);
#endif
#if !FLAGABT
    if(fldlen(8,50)) scrfld(zz++,8,50);
#endif
    if(fldlen(8,51)) scrfld(zz++,8,51);
#if DISP_WI_FR
    scrifld(zz++,fm_obd,&winst_bd);
#endif
#if LEVERINGSKOST
    scrfld(zz++,8,46);
#endif
#if FLAGABT
    if(fldlen(8,50)) scrfld(zz++,8,50);
#endif
#if STOCK_OP_LOCATIE
		if(fldlen(8,48)){scrfld(-zz,8,48);zz++; scrifld(zz++,fm_os6,nm_fil);}
#endif
    if(fldlen(8,43)){scrfld(-zz,8,43);zz++; scrfld(zz++,8,44);}
    scrifld(zz++,fm_obd,&waarde);
#if FLAGCMB
		tot_hl_=round((double)(tot_gewicht/100));
		scrifld(zz++,fm_of4_2,&tot_hl_);
#endif
    if(fldlen(58,41)){
      scrifld(zz++,fm_of3_1,&winst_pc);
    }
#if NO // FLAGPED
		scrfld(zz++,8,34); scrfld(zz++,8,35);
#endif
    z_base=zz;auto_enter=NO;
    for(j=start_;j<(start_+D_LIN_SCR);j++){
#if FLAGVRL // GEEN lijnnrs owv plaatsgebrek
#else
      j++; scrifld(zz++,fm_ou3,&j); j--;
#endif
      ram2stu(j);
      for(k=0;k<sizeof det_nr/2;k++){
				k_k=det_nr[k];
				if(fieldspc(58,k_k,&pdum,fmt)>0){
					pvar=ram+(j*stu58_len)+(s(58,k_k)-s(58,1));
					if(sys4608 & 1){
						auto_enter=YES;
						if((k_k!=15 && k_k!=16)||(*pvar!='\0' && zz!=err_pos)) auto_enter=NO;
						if(auto_enter){
							if(k_k==15){
					if(*(ram+(j*stu58_len)+(s(58,16)-s(58,1)))!='\0') auto_enter=NO;
							}
							else{
					if(*(ram+(j*stu58_len)+(s(58,15)-s(58,1)))!='\0') auto_enter=NO;
							}
						}
					}
					if(auto_enter){scrifld(-zz,fmt,pvar);zz++;}
					else scrifld(zz++,fmt,pvar);
					if(k_k==16){ // geblokkeerd artikel in het rood zetten
						if(fldlen(58,40) && *s(58,40)==1)  scrchat(zz-1,0x0B); else scrchat(zz-1,0xFF);
					}
#if FLAGGRS
					if(k_k==16){ // vaten in andere kleur zetten 
						if(cmpstr(s(58,12),"VAT",3)==0)  scrchat(zz-1,0x0A); else scrchat(zz-1,0xFF);
					}
#endif
#if FLAGPED
					if(k_k==16){ // vaten in andere kleur zetten 
						if(*i(58,34)==1)  scrchat(zz-1,0x0A); else scrchat(zz-1,0xFF);
					}
#endif
#if !FT_HERAFDRUK && ARTSEARCHICOON 
					if(k_k==16) scraddpicto(10+j-start_,zz-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
#endif

#if TRACEERDATA
					if(k_k==16) {
						scraddpicto(28+j-start_,zz-1,2,0,2,1,64,0,CheckTraceerData(),"Lotnummer/vervaldatum"); 
					}
#endif
					if(k_k==20){
#if ALARM_WINST
						attr_=0xFF;
						if(*pu_58_14 && *ps_58_16!='*'){
#if FLAGPSN || FLAGJAC || FLAGCRL
							if(*f(58,73) && *f(58,73)!=*f(58,20)) attr_=0x0A; // prijsafspraak met vaste prijs
#endif

#if FLAGPSN
							else if(*f(58,37) || *f(58,43)) attr_=0x0E; // prijsafspraak met uitgestelde korting
#endif

							bdf_=*f(58,41) * *pf_58_31;
#if FLAGNEY
							bdf_*=1.05; // alarm al geven indien onder 5% winst
#endif
#if FLAGPWH
							bdf_*=1.10; // alarm al geven indien onder 10% winst
#endif
							if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bdf_/=*f(58,63);
							if(bdf_<0 && *pd_58_35>bdf_) attr_=0x0B;
							else if(bdf_>=0 && *pd_58_35<bdf_) attr_=0x0B;
						} 
						scrchat(zz-1,attr_);
#else
						if((*ps_58_15 || *ps_58_16) && *ps_58_16!='*' && *pf_58_20==0){
							scrchat(zz-1,0x0B);
						} else scrchat(zz-1,0xFF);
#endif
				  }
#if CHK_STOCK && !KASINPUT
					if(k_k==7 && *ps_58_16!='*' && *pu_58_14){
						qlv_=*f(58,31); if(fldlen(58,62) && *s(58,62)=='S' && *f(58,63)) qlv_/=*f(58,63);
						if(fldlen(58,100)){
							fill_astock();
							if(*f(58,100)< qlv_) scrchat(zz-1,0x0B); else scrchat(zz-1,0xFF);
						}
						else{
							fasinit(6);*u(6,1)=*pu_58_14; fasgeti(6);
							if(*f(6,33)< qlv_) scrchat(zz-1,0x0B); else scrchat(zz-1,0xFF);
						}
					} else if(k_k==7) scrchat(zz-1,0xFF);
#endif
#if KORT_WARNING
					if(k_k==21){ // korting rood kleuren indien direct of semstrieel kort% of hlkorting
						if(*f(58,21) || *f(58,36) || *f(58,37) || *f(58,43))  scrchat(zz-1,0x0A); else scrchat(zz-1,0xFF);
					}
#endif
				}
      }
    }
#if KASINPUT
    lgadded=YES;/* geen automatische leeggoed */
#endif
    if(lgadded) mask_=0x6FE; else mask_=0x7FE;
    redo_upd:;
#if FT_HERAFDRUK
    curs=-1; mask_=0xE6;/* enkel bekijken */
#endif
    key=scrupd(curs,mask_);curs=1;curspos_=fldcurs;

    auto_enter=NO;nstart_=start_;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
#if !FT_HERAFDRUK && !KASINPUT && (FLAG244 || (FLAG248 & !BONFILE))
    if(key==5001){DisplayExtraFuncties();key=107;} // extra opties
#endif
#if ARTSEARCHICOON
		if(key>=5010 && key<5010+D_LIN_SCR){
			k=key-5010+start_;
			ram2stu(k);fasinit(6);
			if(len58_15 && *ps_58_15) {*ps_6_3='.';copy(ps_58_15,ps_6_3+1,len58_15);}
			else {copy(ps_58_16,ps_6_3,len6_3);sr_nm=YES;}
			if(search(6,98)){
				curs=cursget(k-start_,15); if(*ps_58_15=='\0') curs++;
				err_pos=curs;errnum=39;goto redo;
			}
			else {
				copy(s(6,2),s(58,15),fldlen(58,15));
				t_nr_=taal_nr; if(*s(6,3+t_nr_)=='\0') t_nr_=0;
				copy(s(6,3+t_nr_),ps_58_16,fldlen(58,16));
				stu2ram(k);
			}
		}
#endif

#if BARC_USED
    if(key==18 && werkveld[0]){
      for(k=0;k<max_line;k++){
	ram2stu(k);
	if(test_line()==NO) break;
      }
      if(k<max_line){exec_work();stu2ram(k);}
      else{curs=curspos_;errnum=11;goto redo;}
      if(k>=start_+D_LIN_SCR) nstart_=k;
      key=107;
    }
#endif
#if STOCK_OP_LOCATIE 

		if(fldlen(8,48)){
			filiaal=*u(8,48); zero(nm_fil,sizeof nm_fil);
      if(filiaal==99 || filiaal==0) copy("DEPOT",nm_fil,6);
			else if(filiaal>0 && filiaal<=10 && fldlen(66,11+(filiaal-1)*15) && nm_loc[filiaal-1][0]) copy(nm_loc[filiaal-1],nm_fil,6);
#if !FT_HERAFDRUK 
  		else {curs=3;errnum=34;goto redo;}
#endif
		}
		else{
  		k=*u(8,43);
	  	if(k==0 || k==99)copy("DEPOT",s(8,44),6);
		  else if(k>=1  && k<=10 && fldlen(66,11+(k-1)*15) && nm_loc[k-1][0]) {
			  copy(nm_loc[k-1],s(8,44),6);
		  }
#if !FT_HERAFDRUK
			else {zero(s(8,44),fldlen(8,44));curs=3;errnum=34;goto redo;}
#endif
		}
#else
		if(fldlen(8,43) && fldlen(8,44)){
			for(k=0;k<10;k++){
				if(cmpstr(s(8,43),chauffeur[k].code,2)==0) break;
			}
			if(k<10) copy(chauffeur[k].naam,s(8,44),10);
			else zero(s(8,44),fldlen(8,44));
#if !FT_HERAFDRUK
			if(*s(8,43) && *s(8,44)=='\0') {curs=3;errnum=34;goto redo;}
#endif
		}
#endif

    if(key==18){
      if(z_base==0 || curspos_<z_base){
				curs=curspos_+1; goto redo;
      }
      auto_enter=YES;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      k=(curspos_-z_base)%q_per_line;
      if(k==pos_15) k_k=15; else k_k=16;
      ram2stu(j);
      if(*s(58,k_k)=='\0' || *s(58,k_k)=='*'){curs=curspos_+1;goto redo_upd;}
    }
    if(key==106){
#if FT_HERAFDRUK
			return NO;
#else 
			if(alg_tot==0) return NO;
      else if(scr_ok("Wenst U echt deze bon/factuur te annuleren ?")) return NO;
#endif
    }
    if(key==104){
      j=(curspos_-z_base)/q_per_line;j+=start_;
      ram2stu(j);
      rec_=*pu_58_1;
      init58(j,YES);
      ram2stu(j);
      *pu_58_1=rec_;
      stu2ram(j);
			curs=cursget(j-start_,0);goto redo;
    }
    if(key==105){
      j=(curspos_-z_base)/q_per_line;j+=start_;
      ins_lin(j);
    }
		if(key==112){
			j=(curspos_-z_base)/q_per_line;j+=start_;
      ram2stu(j);
      rec_=*pu_58_1;
      init58(j,YES);
			ram2stu(j);
			copy("*-----------------------------------------",s(58,16),fldlen(58,16));
      *pu_58_1=rec_;
      stu2ram(j);
//			curs=cursget(j-start_,0);goto redo;
		}
    redo_loop:;
    err_pos=0;
    for(k=start_;k<(start_+D_LIN_SCR);k++){
      ram2stu(k);k_k=k-start_;
      if(*s(8,26)=='J') *pf_58_24=0;
#if ARTEXIST & !FT_HERAFDRUK
      if((*ps_58_15 || *ps_58_16) && *ps_58_16!='*' && *u(58,17)!=hash()){
				fasinit(6);
				sr_nm=NO;
				if(len58_15 && *ps_58_15) {*ps_6_3='.';copy(ps_58_15,ps_6_3+1,len58_15);}
				else {copy(ps_58_16,ps_6_3,len6_3);sr_nm=YES;}
				if(search(6,0)){
					curs=cursget(k_k,15); if(*ps_58_15=='\0') curs++;
					err_pos=curs;errnum=39;goto redo;
				}
#if FLAG244 | (FLAG248 & !BONFILE)
#if BLOK_ART && (FLAG244 | (FLAG248 & !BONFILE))
				if(blokkeer_art()){
					if(fldlen(58,40)) *s(58,40)=1; // enkel omschrijving in het rood zetten 
					else{
						curs=cursget(k_k,15); if(*ps_58_15=='\0') curs++;
						err_pos=curs;errnum=39;goto redo;
					}
				} else if(fldlen(58,40)) *s(58,40)=0;
#endif
#if !FLAGKEE
				if(fldlen(22,7)) DispInfoAlarm(6);
#endif
#endif
				copy(s(6,2),ps_58_15,len58_15);
				*pu_58_14=*pu_6_1;
				if(sr_nm || *ps_58_16=='\0'){
					t_nr_=taal_nr; if(*s(6,3+t_nr_)=='\0') t_nr_=0;
					copy(s(6,3+t_nr_),ps_58_16,fldlen(58,16));
				}
				stu2ram(k);
		  	Fill58FromNewArtikel(k);
			}   
			if(*i(58,34)==99){
				*u(58,48)=*pu_58_14;
				*f(58,46)=*pf_58_20;
				*f(58,49)=1;
			}
			if(*ps_58_16=='*'){
				if(fldlen(58,50)) *f(58,50)=0;
				if(fldlen(58,51)) *i(58,51)=0;
				if(fldlen(58,54)) *f(58,54)=0;
				if(fldlen(58,63)) *f(58,63)=1;
#if !KAS2FACT
				*f(58,46)=0;*u(58,48)=0;*f(58,49)=0;
#endif
				*f(58,38)=0;
#if AFHAALVERG
    		zero(s(58,55),s(58,58)-s(58,55));
#endif
#if LOSVERGOED
				zero(s(58,58),s(58,61)-s(58,58));
#endif
#if PALET_KORTING
  			zero(s(58,67),s(58,70)-s(58,67));
#endif
			}

			if(btw_glob!=99) *pf_58_24=btw_glob;
			*pf_58_24=round((double)(*pf_58_24)); // om vieze dingen ver na komma weg te doen 
#endif
			stu2ram(k);
			if(btw_tab((BEDRAG)0)==8) {curs=cursget(k_k,24);errnum=34;goto redo;}
    }
    calc();
#if FLAG244 && PRTFEESTBON
		if(key==5003){key=107;DisplayAlsFeestbon();goto redo_loop;}
#endif
#if TRACEERDATA
		if(key>=5028 && key<5028+D_LIN_SCR){
			k=key-5028+start_;
			DisplayTraceerData(k);
		}
#endif
    if(key==108){/* volgende schermen controleren */
      scrget(1,7);scrupd(-3,0);
      start_+=D_LIN_SCR;
      if(start_>=max_line) goto ArtcontroleOK;
      else if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
      goto redo_loop;
ArtcontroleOK:;
#if TRACEERDATA & !FT_HERAFDRUK
			start_=nstart_;
			k=0;
#if FLAG244
			if(upd_mode==NO) k=max_line; // niet controleren bij nieuwe bon
#endif
  		for(k;k<max_line;k++){  // verplichte traceerdata ingevuld ?
				ram2stu(k);
				if(*f(58,7) && CheckTraceerData()==3){
					errnum=38;DisplayTraceerData(k); 
					ram2stu(k);
					if(CheckTraceerData()==3) {
						if(k<start_|| k>=start_+D_LIN_SCR) start_=k;
						curs=cursget(k,16);
						errnum=38; goto redo;
					}
					else k--;
				}
			}
#endif
#if KN_JOURNL && !BONFILE  // cfr Jacobs
			if(alg_tot<0 || DisplayWarning("Totaal is positief, toch in creditnota-journaal boeken?",61,1)==YES) break;
#else
			break;
#endif
		}

#if !KASINPUT
#if FLAGABT && ARTEXIST
    if(key==109){
			PalletAdd();calc();
			for(k=max_line-1;k>=0;k--) {ram2stu(k);if(test_line()) break;}
			k-=3; if(k<0) k=0; start_=k;curs=z_base; goto redo;
		}
#else
    if(key==109)leegadd(NO);
#endif
#if LEEG_APART
    if(key==110)leegadd(YES);
#endif
#if !FT_HERAFDRUK
    if(key==110){
			if(curspos_<=z_base) goto redo;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      ram2stu(j);
      if(*pu_58_14) LijnDetail(j);
			curs=curspos_;goto redo;
    }
#endif
#if !FT_HERAFDRUK
#if (HISTORIEK | STATISTIEK)
    if(key==111){
#else 
    if(key==111 && ovltest(233)){
#endif
			if(curspos_<=z_base) goto redo;
      j=(curspos_-z_base)/q_per_line;j+=start_;
      ram2stu(j);
      if(*pu_58_14){
				fasinit(27);*u(27,2)=ft_date-730;/* 2 jaar terug */
				*s(27,4)='K';*u(27,5)=*pu_2_1;
#if !LEV_OMZET
			  if(fldlen(2,51) && *u(2,51)) *u(27,5)=*u(2,51); // factuurklant tonen, want op leveradres zit niks
#endif
				*u(27,6)=*pu_58_14;
#if HISTORIEK
        ovlcall(239,2);
#else
#if STATISTIEK
				ovlcall(236,2);
#else
				ovlcall(233,2);
#endif
#endif
      }
			curs=curspos_;goto redo;
    }
#endif
#endif
    if(waard_inc) waarde=alg_tot; else waarde=belastbt;
    start_=nstart_;
    if(key==18 || auto_enter){/* automatische bladskip op einde van scherm */
      for(k=0;k<D_LIN_SCR;k++){ram2stu(k+start_);if(test_line()==NO) break;}
      if(k==D_LIN_SCR) key=103;
    }
    if(key==102) {start_-=D_LIN_SCR; if(start_<0) start_=0;}
    if(key==103) start_+=D_LIN_SCR;
    if(start_>(max_line-D_LIN_SCR)) start_=max_line-D_LIN_SCR;
    j=0;
    for(k=0;k<D_LIN_SCR;k++){ram2stu(k+start_);if(test_line()==NO) {j=k;break;}}
    curs=cursget(j,0);
  }
  return YES;
}
#endif
 
static cursget(lin_,fld_)
int16 lin_,fld_;
{
  int16 g=1,k;
						
  q_per_line=1;
#if FLAGVRL  // GEEN lijnnummers owv plaatsgebrek
	q_per_line=0; g=0;
#endif
  for(k=0;k<sizeof det_nr/2;k++){
    if(fld_ && det_nr[k]==fld_) g=q_per_line;
    if(fldlen(58,det_nr[k])>0) q_per_line++;
  }
  return (int16)(z_base+lin_*q_per_line+g);
}

#if FLAG244 && PRTFEESTBON
static DisplayAlsFeestbon()
{
  int16 j,k,n,curs,z,key,curspos_,start,emptynr_,used_;
  int16 InpAantal[500][4],max_,qfles_in_bak_,q_per_bak_;
	char  LosseFlessen[500],lgcodebak_[10],lgcodefles_[10];

	zero((char *)&InpAantal,sizeof InpAantal); 
  for(k=0;k<500;k++) LosseFlessen[k]='J';	
#if FLAGAST	// default retour-flessen steeds in bak
	zero(LosseFlessen,sizeof LosseFlessen);
#endif
	max_=max_line; if(max_>500) max_=500;
	start=0;curs=3;
	FOREVER{
		redo:;
		scrnum=0; scrget(2,382);z=1; used_=NO;
#if FLAGAST
   scraddf(130,3,59,0x09); scrifld(130,fm_os1,"L");
#endif
		scrofld(z++,2,3,-1); scrofld(z++,8,2,-1);
		for(j=start;j<start+18;j++){
			if(j>=max_) break;
			ram2stu(j);
			scrofld(z++,58,31,-1);scrofld(z++,58,16,-1);
			if(*u(58,14)){
				for(k=0;k<2;k++) scrifld(z++,fm_ui4,&InpAantal[j][k]);
#if FLAGAST
				scrifld(z++,fm_u_JN,&LosseFlessen[j]);
#else 
				z++;
#endif
				for(k=2;k<4;k++) scrifld(z++,fm_ui4,&InpAantal[j][k]);
				used_=YES;
			} else z+=5;
		}
		if(used_) curs=3; else curs=-1;
		key=scrupd(curs,0xA6);curs=1;curspos_=fldcurs;
  	if(key==106) goto endsr;
    if(key==108){
			if(used_) break;
			else break;
		}
    if(key==102) start-=18;
    if(key==103) {start+=18;if(start>=max_-18) start=max_-18;}
    if(start<0) start=0;
  }
	used_=NO;
	for(k=0;k<500;k++){
		for(j=0;j<4;j++) if(InpAantal[k][j]){used_=YES;break;}
		if(used_) break;
	}
	if(used_){
		if(scr_ok("Wenst u echt deze aantallen toe te voegen aan de bon?")==NO) goto endsr;
	} else goto endsr;
	for(emptynr_=max_line-1;emptynr_>0;emptynr_--){
		ram2stu(emptynr_); if(test_line()) break;
	}
	emptynr_++; used_=NO;
	for(j=0;j<max_;j++){
		qfles_in_bak_=0;
		for(k=0;k<2;k++){
			if(InpAantal[j][k]){ // volgoed terug
				if(used_==NO){
					fasinit(58);
#if BONSORT
					if(fldlen(58,62)) *s(58,62)='S';
#endif
					copy("*RETOUR",s(58,16),15); stu2ram(emptynr_++);used_=YES;
				}
				ram2stu(j);
				*f(58,7)=-InpAantal[j][k]; *u(58,1)=0;
				if(k==0){
					if(*s(58,62)){*s(58,62)='\0';*f(58,20)=0;*u(58,17)=0;}
				}
				else{
					if(*s(58,62)!='S'){*s(58,62)='S';*f(58,20)=0;*u(58,17)=0;}
					if(LosseFlessen[j]!='J') qfles_in_bak_+=InpAantal[j][k];
				}
				stu2ram(emptynr_++);
				if(emptynr_>=max_line) emptynr_--;
			}
		}
		for(k=2;k<4;k++){ // leeggoed terug
			if(InpAantal[j][k]){
				if(used_==NO){
					fasinit(58);
#if BONSORT
					if(fldlen(58,62)) *s(58,62)='S';
#endif
					copy("*RETOUR",s(58,16),15); stu2ram(emptynr_++);used_=YES;
				}
				ram2stu(j);
				fasinit(6); *u(6,1)=*u(58,14); if(fasgeti(6)) fasinit(6);
				if(*i(6,9)!=99){
  				if(k==2)	copy(s(6,41),s(6,2),fldlen(6,2)); 
	  			else copy(s(6,44),s(6,2),fldlen(6,2)); 
				}
				if(faskeyi(6,1,0)==0){
				  fasinit(58);
				  *f(58,7)=-InpAantal[j][k];
					*u(58,14)=*u(6,1);copy(s(6,2),s(58,15),fldlen(58,15));
					if(k==3 && LosseFlessen[j]!='J') qfles_in_bak_+=InpAantal[j][k];
					stu2ram(emptynr_++);
				}
				if(emptynr_>=max_line) emptynr_--;
			}
		}
		if(qfles_in_bak_){ // kratten van lege flessen berekenen
			ram2stu(j);
			fasinit(6); *u(6,1)=*u(58,14); if(fasgeti(6)) goto no_krat;
			q_per_bak_=*f(6,31); if(q_per_bak_<=1) goto no_krat;
			copy(s(6,41),lgcodebak_,fldlen(6,41)); 		copy(s(6,44),lgcodefles_,fldlen(6,44));
			fasinit(58);
      fasinit(6); copy(lgcodefles_,s(6,2),fldlen(6,2)); if(faskeyi(6,1,0)) goto no_krat; else *f(58,20)-=*f(6,21)*q_per_bak_; // bedrag losse flessen
			fasinit(6); copy(lgcodebak_,s(6,2),fldlen(6,2)); if(faskeyi(6,1,0)) goto no_krat; else  *f(58,20)+=*f(6,21); // bedrag volle bak
			k=qfles_in_bak_/q_per_bak_; *f(58,7)-=k; k=qfles_in_bak_%q_per_bak_; if(k) *f(58,7)-=1;
			*u(58,14)=*u(6,1);copy(s(6,2),s(58,15),fldlen(58,15));
			stu2ram(emptynr_++);		
			if(emptynr_>=max_line) emptynr_--;
no_krat:;
		}
	}
  endsr:;
}
#endif
  
static DisplayExtraFuncties()
{
	int z,k,key,used_=0,vt_,hz_;
	char choice='\0',menu_punten[15],tb_actie[15],dsp_lijn[80];

	FOREVER{
		scrget(2,353);z=1;
		scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0240A");
		used_=0;zero(dsp_lijn,sizeof dsp_lijn);zero(menu_punten,sizeof menu_punten);zero(tb_actie,sizeof tb_actie);
		z=20;hz_=34;vt_=3;
#if ARTEXIST
		AddTextKey(z++,hz_,vt_,15,2,10001,"codenummer",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		AddTextKey(z++,hz_,vt_,15,2,10002,"omschrijving",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		AddTextKey(z++,hz_,vt_,15,2,10003,"groep",0x00FF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		if(faskeyi(6,6,0)!=45){AddTextKey(z++,hz_,vt_,15,2,10004,"plaats\nmagazijn",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}}
		AddTextKey(z++,hz_,vt_,15,2,10005,"leverancier",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		if(faskeyi(6,14,0)!=45){AddTextKey(z++,hz_,vt_,15,2,10006,"merk\nproducent",0xFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}}
#endif
		z=30;hz_=34;vt_=8;
		if(ovltest(234)){
  		AddTextKey(z++,hz_,vt_,15,2,10011,"vorige factuur",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		}
#if ARTEXIST
    if(ovltest(266)){
  		AddTextKey(z++,hz_,vt_,15,2,10012,"offerte",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		}
#endif
    if(ovltest(264)){
  		AddTextKey(z++,hz_,vt_,15,2,10013,"verhuurbon",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		}
    if(ovltest(2241)){
  		AddTextKey(z++,hz_,vt_,15,2,10014,"bestelling\n(XLS)",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		}
    if(fldlen(2,120)>=50){
  		AddTextKey(z++,hz_,vt_,15,2,10020,"bestelbon\nklantenfiche",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		}
#if PDA_VERKOOP
		AddTextKey(z++,hz_,vt_,15,2,10015,"PDA-bon",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
#endif
#if PDA_BESTELLING
		AddTextKey(z++,hz_,vt_,15,2,10018,"PDA-bestelling",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
#endif
#if PDA_TRACEER & FLAG244
		AddTextKey(z++,hz_,vt_,15,2,10016,"PDA\ntraceerbon",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
#endif
#if FLAG244 || FLAG242 || (FLAG248 && !BONFILE && !FT_HERAFDRUK)
    if(ovltest(2394) && *s(8,24)=='\0'){
  		AddTextKey(z++,hz_,vt_,15,2,10017,"bon\rCoca-Cola",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		}
#endif
#if !FLAGJAC
#if FLAG244 || FLAG242 || (FLAG248 && !BONFILE && !FT_HERAFDRUK)
#if FLAGVDW
		if(ovltest(2295) || ovltest(2296)){
#else
    if(ovltest(2296)){
#endif
  		AddTextKey(z++,hz_,vt_,15,2,10022,"weborder",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
		}
#endif
#endif
#if FLAGPED & FLAG244
		AddTextKey(z++,hz_,vt_,15,2,10019,"bestelbon\nleverancier",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
#endif
#if FLAGAST & FLAG244
		AddTextKey(z++,hz_,vt_,15,2,10021,"artikels onder\nmin.stock",0x007FFF);hz_+=15;if(hz_>=75){hz_=34;vt_+=2;}
#endif
		z=1;
#if ARTEXIST
		if(lgadded==NO){
#if LG_APART
		 used_++; sprintf(dsp_lijn,"Zet leeggoed apart op bon/factuur  ........... : %d",used_);scrifld(z++,fm_os50,dsp_lijn);
	   menu_punten[used_-1]='0'+used_; tb_actie[used_-1]=1;
#else 
		 used_++; sprintf(dsp_lijn,"Maak leeggoed op 0 voor deze bon/factuur  .... : %d",used_);scrifld(z++,fm_os50,dsp_lijn);
	   menu_punten[used_-1]='0'+used_; tb_actie[used_-1]=1;
#endif
		}
#if FLAG244
		 used_++; sprintf(dsp_lijn,"Vernieuw alle prijzen/kortingen van deze bon . : %d",used_);scrifld(z++,fm_os50,dsp_lijn);
	   menu_punten[used_-1]='0'+used_; tb_actie[used_-1]=5;
#endif
#endif
    if(ovltest(2922)){
      used_++; sprintf(dsp_lijn,"Afhaling/klantenmemo ......................... : %d",used_);scrifld(z++,fm_os50,dsp_lijn);
		  menu_punten[used_-1]='0'+used_; tb_actie[used_-1]=2;
		}
#if HISTORIEK
		used_++; sprintf(dsp_lijn,"Toon historieken van deze klant .............. : %d",used_);scrifld(z++,fm_os50,dsp_lijn);
    menu_punten[used_-1]='0'+used_; tb_actie[used_-1]=3;
#endif
#if STATISTIEK
		used_++; sprintf(dsp_lijn,"Toon statistieken van deze klant ............. : %d",used_);scrifld(z++,fm_os50,dsp_lijn);
    menu_punten[used_-1]='0'+used_; tb_actie[used_-1]=4;
#endif
		z++;
		if(used_){
		  scrifld(6,fm_menu,&choice);
			key=scrupd(1,0x7FF);
		}
		else key=scrupd(1,0x7FF);
		if((key/0x10000)>0) key/=0x10000;
		switch(key){
		  case 101 : return 0; break;
			case 10001 : SortArtikelsOpBon(1); return 1; break;
			case 10002 : SortArtikelsOpBon(2); return 1; break;
			case 10003 : SortArtikelsOpBon(5); return 1; break;
			case 10004 : SortArtikelsOpBon(6); return 1; break;
			case 10005 : SortArtikelsOpBon(4); return 1; break;
			case 10006 : SortArtikelsOpBon(14); return 1; break;  
			case 10011 : LoadArtikelFromPreviousFactuur(); return 1; break;
//#if HISTORIEK
//			case 10011 : LoadArtikelFromHistoriek(); return 1; break;
//#endif
#if ARTEXIST
			case 10012 : LoadOfferte(); return 1; break;
#endif
			case 10013 : LoadVerhuring(); return 1; break;
			case 10014 : ovlcall(2241,0); return 1; break;
#if PDA_VERKOOP
			case 10015 : LoadArtikelsFromPda(); return 1; break;
#endif
#if FLAG244 && PDA_TRACEER
			case 10016 : AddPDATracedata2Doc(YES); return 1; break;
#endif
#if FLAG244 || FLAG242 || (FLAG248 && !BONFILE && !FT_HERAFDRUK)
			case 10017 : copy(s(2,1),buf1000,fldlen(2,0));
              		 ovlcall(2394,0); 
				           copy(buf1000,s(2,1),fldlen(2,0));
				           return 1; break;
#endif
#if PDA_BESTELLING
			case 10018 : LoadPdaBestelling(); return 1; break;
#endif
#if FLAG244 && FLAGPED
			case 10019 : LoadArtFromLevBestelling(); return 1; break;
#endif
			case 10020 : LoadArtikelsFromBestelbonKlant(); return 1; break;
#if FLAG244 && FLAGAST
			case 10021 : LoadArtOnderMinStock(); return 1; break;
#endif
#if FLAG244 || FLAG242 || (FLAG248 && !BONFILE && !FT_HERAFDRUK)
#if FLAGVDW
			case 10022 : if(ovlcall(2295,2)){
#else
			case 10022 : if(ovlcall(2296,2)){
#endif
					           for(k=0;k<2;k++) if(fldlen(8,65+k) && *s(8,65+k)) copy(s(8,65+k),opm_foot[k],fldlen(8,65+k));
            			 }
									 return 1; break;
#endif
			default : break;
		}
		errnum=0;
		for(k=0;k<10;k++) if(choice==menu_punten[k]) break;
    switch(tb_actie[k]){
#if LEEG_APART
      case  1 : leegadd(YES);break;
#else 
			case  1 : leegadd(NO);break;
#endif

			case  2 : if(ovlcall(2922,2)==2){
					        if(keepdata==NO) init58(0,NO);
					        if(*s(62,9)) add_afhaling(-1);
					        for(k=0;k<30;k++){
						        if(fldlen(62,12+k*5) && *u(62,12+k*5)) add_afhaling(k);
					        }
					        if(*s(62,9)) add_afhaling(99);
									fasupd(62);
        				}
                break;
#if HISTORIEK
			case  3 :  fasinit(27);*u(27,2)=ft_date-730;/* 2 jaar terug */
								 *s(27,4)='K';*u(27,5)=*pu_2_1;
#if !LEV_OMZET
								 if(fldlen(2,51) && *u(2,51)) *u(27,5)=*u(2,51); // factuurklant tonen, want op leveradres zit niks
#endif
								 ovlcall(239,2);
				         break;
#endif
#if STATISTIEK && !HISTORIEK
			case  4 :  fasinit(27);*u(27,2)=ft_date-730;/* 2 jaar terug */
								 *s(27,4)='K';*u(27,5)=*pu_2_1;
#if !LEV_OMZET
								 if(fldlen(2,51) && *u(2,51)) *u(27,5)=*u(2,51); // factuurklant tonen, want op leveradres zit niks
#endif
								 ovlcall(236,2);
				         break;
#endif
#if ARTEXIST
			case  5 : if(DisplayWarning("Wenst u echt ALLE prijzen op bon te vervangen door de huidige prijzen ???",61,1)) RenewPrijzen();
                break;
#endif
      default : errnum=34; break;
    }
		if(errnum!=34) break;
  }
}

#if ARTEXIST
static RenewPrijzen()
{
  int16 k,t_nr_;
	char fl_bak_;
  uint16 dt_bon_;
	float qlv_;

	dt_bon_=*u(8,8); *u(8,8)=*u(25,2);
  for(k=0;k<max_line;k++){
		ram2stu(k);
		if(test_line() && *u(58,14)){
			fasinit(6);*u(6,1)=*u(58,14);
			if(fasgeti(6)==0){
				qlv_=*f(58,7); if(fldlen(58,62)) fl_bak_=*s(58,62);
				init58(k,YES);
				ram2stu(k); 
				copy(s(6,2),ps_58_15,len58_15);
				*pu_58_14=*pu_6_1;
				t_nr_=taal_nr; if(*s(6,3+t_nr_)=='\0') t_nr_=0;
				copy(s(6,3+t_nr_),ps_58_16,fldlen(58,16));
				*f(58,7)=qlv_; if(fldlen(58,62)) *s(58,62)=fl_bak_;
				stu2ram(k);
				Fill58FromNewArtikel(k);
			}
		}
	}
	*u(8,8)=dt_bon_;
}
#endif


static SortArtikelsOpBon(sortkey_)
int16 sortkey_;
{
  int16 j,k,hz_,vt_,sw,max_,amode_,z,key,used_=0,fld_;
	char sortbuf[1000],choice,menu_punten[10],dsp_lijn[80];
  uint16 artrecs_[DIM58],pos_,reclev_,pos_lev_;

#if FLAGAST
	if(sortkey_==6) {SortBon(101);return 1;}
#endif
	reclev_=*u(1,1);
	if(faskeyi(6,sortkey_,0)==45) return 0; // key bestaat niet
	scrget(1,7);scrupd(-3,0);
  zero((char *)&artrecs_[0],sizeof artrecs_);max_=0;
	k=max_line-1; if(k>DIM58) k=DIM58-1;
  for(k;k>=0;k--){
		ram2stu(k);
		if(test_line()){
		  if(max_==0 ) max_=k+1;
		  if(*u(58,14)) artrecs_[k]=*u(58,14);
		} else artrecs_[k]=0xFFFF;
	}
	fasinit(6);pos_=30000;
	if(sortkey_==4 || sortkey_==14){
		pos_lev_=7; if(sortkey_==14) pos_lev_=101;
		fasinit(1);
		FOREVER{
			if(faskeyi(1,2,2)) break;
			fasinit(6);*u(6,pos_lev_)=*u(1,1);amode_=1;
			FOREVER{
				if(faskeyi(6,sortkey_,amode_)) break; amode_=2;
				if(*u(6,pos_lev_)!=*u(1,1)) break;
				for(k=0;k<max_;k++) if(artrecs_[k]==*u(6,1)) artrecs_[k]=pos_++;
			}
		}
	}
	else{
		FOREVER{
			if(faskeyi(6,sortkey_,2)) break;
			for(k=0;k<max_;k++) if(artrecs_[k]==*u(6,1)) artrecs_[k]=pos_++;
		}
	}
	max_--;
  FOREVER{/* sorteren */
    sw=NO;
    for(k=0;k<max_;k++){
			if(artrecs_[k]>artrecs_[k+1]){
			  ram2stu(k);
	      copy(s(58,1),sortbuf,fldlen(58,0));
	      ram2stu(k+1);
	      stu2ram(k);
	      copy(sortbuf,s(58,1),fldlen(58,0));
	      stu2ram(k+1);
				pos_=artrecs_[k];artrecs_[k]=artrecs_[k+1];artrecs_[k+1]=pos_;
	      sw=YES;
			}
    }
    if(sw==NO) break;
  }
	fasinit(1);if(reclev_){*u(1,1)=reclev_;fasgeti(1);}
	return 1;
}
#endif

static LoadVerhuring()
{
  int16 key, j,k,z,yy,mm,dd, curs=2,mode_,start_,max_,bonart_beg_,used_;
  uint16 last_b_,last_e_;
	char tb_lever[DIM_TKLT];

	if(fldlen(95,1)==0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  zero((char *)&toer_qbons[0],sizeof toer_qbons);
  mode_=1;
  fasinit(95);*u(95,2)=*u(2,1);k=0;
  FOREVER{
    next:;
    if(faskeyi(95,2,mode_)) break; mode_=2;
    if(*u(95,2)!=*u(2,1)) break;
    toer_qbons[k++]=*u(95,1);
    if(k>=DIM_TKLT) break;
  }
  if(k==0) {errnum=14;goto endsr;}
  max_=k;start_=0;
  zero(tb_lever,sizeof tb_lever);
  for(k=0;k<max_;k++) tb_lever[k]='N';
  FOREVER{
    scrnum=0;scrget(2,374); z=1;
    scrofld(z++,2,3,-1);
    z++; // scrifld(z++,fm_ou5,&bonnr);
    for(k=start_;k<start_+15;k++){
			if(toer_qbons[k]==0) break;
			fasinit(95);*u(95,1)=toer_qbons[k];fasgeti(95);
			fasinit(6);*u(6,1)=*u(95,3);
			if(*u(6,1)) fasgeti(6);
			else if(fldlen(95,13)) copy(s(95,13),s(6,3),fldlen(6,3));
			scrifld(z++,fm_u_JN,&tb_lever[k]);
			scrofld(z++,95,5,-1);
			scrofld(z++,95,4,-1);
			scrofld(z++,6,3,30);
			scrofld(z++,95,8,-1);
			scrofld(z++,95,6,-1);
			scrofld(z++,95,7,-1);
    }
    key=scrupd(1,0x287);
    if(key==101) goto endsr;
    if(key==102) start_-=15; 
    if(key==103){
			start_+=15; if(start_>=max_) start_=max_-15;
    }
		if(start_<0) start_=0;
    if(key==110){
			if(DisplayWarning("Wenst U echt de verhuringen te schrappen ZONDER kopieren?",61,1)==YES){
				for(k=0;k<DIM_TKLT;k++){
					if(tb_lever[k]=='J' && toer_qbons[k]!=0){
  					fasinit(95);*u(95,1)=toer_qbons[k];fasgeti(95);
						faskill(95);
					}
				}
				goto endsr;
			}
		}
		
    if(key==108) break;
  }
  scrget(1,7);scrupd(-3,0);
	for(bonart_beg_=max_line-1;bonart_beg_>=0;bonart_beg_--) {
		ram2stu(bonart_beg_); if(test_line()) break;
	}
	bonart_beg_++;
	last_b_=0xFFFF; last_e_=0xFFFF;used_=NO;
  for(k=0;k<DIM_TKLT;k++){
    if(tb_lever[k]!='J' || toer_qbons[k]==0) continue;
		if(bonart_beg_>=max_line) break;
    fasinit(95);*u(95,1)=toer_qbons[k];fasgeti(95);
		
    if(*u(95,6)!=last_b_ || *u(95,7)!=last_e_){
			if(bonart_beg_){ // niet als eerste lijn
  			ram2stu(bonart_beg_);
        *s(58,16)='*'; 
		  	stu2ram(bonart_beg_++); if(bonart_beg_>=max_line) break;
			}
      ram2stu(bonart_beg_);
      copy("*Periode : ",s(58,16),11);
      jddate(*u(95,6),&yy,&mm,&dd); yy=yy%100;
      stcli_d(s(58,16)+11,(long)dd,2,0);*(s(58,16)+13)='/';
      stcli_d(s(58,16)+14,(long)mm,2,0);*(s(58,16)+16)='/';
      stcli_d(s(58,16)+17,(long)yy,2,0);*(s(58,16)+19)='-';
      jddate(*u(95,7),&yy,&mm,&dd); yy=yy%100;
      stcli_d(s(58,16)+20,(long)dd,2,0);*(s(58,16)+22)='/';
      stcli_d(s(58,16)+23,(long)mm,2,0);*(s(58,16)+25)='/';
      stcli_d(s(58,16)+26,(long)yy,2,0);
      stu2ram(bonart_beg_++); if(bonart_beg_>=max_line) break;
			ram2stu(bonart_beg_);used_=YES;

      last_b_=*u(95,6);last_e_=*u(95,7);
    }
		ram2stu(bonart_beg_);
    fasinit(6);*u(6,1)=*u(95,3);
		if(*u(6,1)) fasgeti(6);
		else if(fldlen(95,13)) copy(s(95,13),s(6,3),fldlen(6,3));
    copy(s(6,2),s(58,15),fldlen(58,15));
    *u(58,14)=*u(6,1);
    copy(s(6,3),s(58,16),fldlen(58,16));
    *f(58,24)=*f(6,28);
    if(fldlen(58,25) && fldlen(6,39)) copy(s(6,39),s(58,25),fldlen(58,25));
    if(fldlen(6,40) && fldlen(58,26)) *l(58,26)=*l(6,40);
    *i(58,34)=*i(6,9);
    if(fldlen(58,27)) *s(58,27)=def_inc;
    if(fldlen(6,38) && fldlen(58,13)) *f(58,13)=*f(6,38);
    if(fldlen(58,8)) {*f(58,8)=*f(6,83); if(*f(58,8)==0) *f(58,8)=1;}
    if(fldlen(58,12)) copy(s(6,10),s(58,12),fldlen(58,12));
		if(fldlen(58,50)){
			if(fldlen(6,84)) *f(58,50)=*f(6,84);
			else if(fldlen(6,37)) *f(58,50)=*f(6,37);
		}
    if(fldlen(58,51)) *i(58,51)=*i(6,85);
    if(fldlen(58,54)) *f(58,54)=*f(6,83);
    if(fldlen(58,63)){*f(58,63)=*f(6,31);if(*f(58,63)==0) *f(58,63)=1;}
    *f(58,7)=*f(95,8);*f(58,31)=*f(95,8);
    *f(58,20)=*f(95,9);*l(58,32)=*d(95,10);
    *d(58,35)=*d(95,10);
    stu2ram(bonart_beg_++); if(bonart_beg_>=max_line) break;
  }
	if(used_ && bonart_beg_<max_line){
		keepdata=YES;
    ram2stu(bonart_beg_);*s(58,16)='*'; stu2ram(bonart_beg_); 
		if(DisplayWarning("Mogen de geselecteerde verhuringen geschrapt worden?",61,1)==YES){
			for(k=0;k<DIM_TKLT;k++){
				if(tb_lever[k]=='J' && toer_qbons[k]!=0){
  				fasinit(95);*u(95,1)=toer_qbons[k];fasgeti(95);
					faskill(95);
				}
			}
		}
	}
  endsr:;
}

#if ARTEXIST
static Fill58FromNewArtikel(nr_) // artikel moet klaarstaan EN stu58 gesaved in ram, wordt op einde ook terug gesaved in ram
int16 nr_;
{
	int16 j;
	float vp_,bdf_,vp_promo_,hoev_;
	uint16 rec_;

	ram2stu(nr_);PrijsDatum=0;
#if INTRASTAT
	zero(s(58,30),fldlen(58,30));
#endif
	if(fldlen(6,3+3) && fldlen(58,89) && *s(58,89)=='\0') copy(s(6,3+3),s(58,89),fldlen(58,89)); // extra omschrijving 
	if(fldlen(6,11) && *s(6,11)) copy(s(6,11),s(58,55),fldlen(58,55));
  else if(fldlen(6,8)) copy(s(6,8),s(58,55),fldlen(58,55));
	if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(8,8)) *pf_58_24=*f(6,28+94);
	else *pf_58_24=*f(6,28);
	if(*s(8,26)=='J') *pf_58_24=0;
	if(fldlen(58,101) && fldlen(6,29)) copy(s(6,29),s(58,101),fldlen(58,101));
	if(len58_25 && fldlen(6,39)) copy(s(6,39),ps_58_25,len58_25);
#if FLAGDAV
	if(prxnr==3) *s(58,25)='6'; // doorverkoop apart zetten 
#endif
	if(fldlen(6,40) && fldlen(58,26)) *l(58,26)=*l(6,40);
#if YES // !FLAGPED  // voor toeslag gebruikt 
	if(fldlen(58,71) && *s(58,71)=='\0') copy(s(6,100),s(58,71),fldlen(6,100));
#endif
	*i(58,34)=*i(6,9);
	if(fldlen(6,38) && fldlen(58,13)) *f(58,13)=*f(6,38);
#if DRI_flag
	if(fldlen(58,8)) {*f(58,8)=*f(6,31); if(*f(58,8)==0) *f(58,8)=1;}
#else
	if(fldlen(58,8)) {*f(58,8)=*f(6,83); if(*f(58,8)==0) *f(58,8)=1;}
#endif
	if(fldlen(58,12)) copy(s(6,10),s(58,12),fldlen(58,12));
	if(fldlen(58,50)){
		if(fldlen(6,84)) *f(58,50)=*f(6,84);
		else if(fldlen(6,37)) *f(58,50)=*f(6,37);
	}
	if(fldlen(58,51)) *i(58,51)=*i(6,85);
	if(fldlen(58,54)) *f(58,54)=*f(6,83);
	*f(58,43)=semestpc;
	if(fldlen(58,63)){*f(58,63)=*f(6,31);if(*f(58,63)==0) *f(58,63)=1;}
#if FACT_PROMO && !KAS2JMCFACTUUR && !KAS2JMCBON
	hoev_=*f(58,7);
	if(fldlen(58,8) && fldlen(58,62)){if(*ps_58_62=='P' && *f(58,8)) hoev_*=*f(58,8);}
	if((*u(8,8)>=*u(6,150) && *u(8,8)<=*u(6,151)) && *ps_58_62!='S' && (fldlen(6,153)==0 || hoev_>=*f(6,153))){
#if FACT_PROMO_REPL // promotie enkel toepassen indien voordeliger en NIET cumuleren
		if(prxnr<6){
  		for(j=0;j<4;j++)	copy(s(6,155+prxnr*5+j),s(58,90+j),fldlen(58,90+j));
		}
		else if(fldlen(6,149)==52) copy(s(6,149)+(prxnr-6)*13,s(58,90),13);
		vp_promo_= *f(58,90); if(vp_promo_==0) vp_promo_=*f(6,PrNrs[prxnr]);
		vp_promo_= round((double)((vp_promo_- *f(6,30)) * (100. - *f(58,91))/ 100. + *f(6,30) - *f(58,92)));
  	calc_prx=*pf_58_20; get_prx(YES);
    if(*f(58,20)) calc_prx=*f(58,20); if(fldlen(58,132)) *u(58,132)=PrijsDatum;
    calc_prx= round((double)((calc_prx - *f(6,30)) * (100. - calc_kort)/ 100. + *f(6,30) - hl_korting));
		if(*f(58,20)==0 && *s(58,93)=='J' && *s(6,154) && ((*f(58,90)==0 && *f(58,91)==0 && *f(58,92)==0) || vp_promo_<calc_prx)){
			stu2ram(nr_);
			if(ins_lin(nr_+1)){
				ram2stu(nr_+1);
				*ps_58_16='*';copy(s(6,154),ps_58_16+1,25);
				if(fldlen(58,101) && fldlen(6,29)) copy(s(6,29),s(58,101),fldlen(58,101));
				copy(s(6,2),ps_58_15,len58_15);
				*s(58,93)='J'; // om deze lijn bij afdrukken laadbon toch te drukken 
				if(fldlen(58,101) && fldlen(6,29)) copy(s(6,29),s(58,101),fldlen(58,101));
				stu2ram(nr_+1);
			}
			ram2stu(nr_);
		}
 		if(*f(58,90) || *f(58,91) || *f(58,92)){
			if(vp_promo_<calc_prx){
			  if(*f(58,90)) *f(58,20)=*f(58,90);  else *f(58,20)=*f(6,PrNrs[prxnr]);
			  *f(58,21)=*f(58,91);*f(58,36)=*f(58,92);
			  for(j=90;j<=92;j++) *f(58,j)=0; 
			  *s(58,93)='P';
			}
			else{
				zero(s(58,90),s(58,95)-s(58,90));
			}
	}
#else
		if(prxnr<6){
  		for(j=0;j<4;j++)	copy(s(6,155+prxnr*5+j),s(58,90+j),fldlen(58,90+j));
		}
		else if(fldlen(6,149)==52) copy(s(6,149)+(prxnr-6)*13,s(58,90),13);
		if(*pf_58_20==0){
			get_prx(YES); 
			vp_=*f(6,PrNrs[prxnr]);
			if(newkort && calc_prx!=vp_) {
				*pf_58_20=calc_prx;
				if(*f(58,90) && *f(58,90)< *pf_58_20) *pf_58_20=*f(58,90);  if(fldlen(58,132)) *u(58,132)=PrijsDatum;
			}
			else *pf_58_20=*f(58,90);
			if(*s(58,93)=='J'&& *s(6,154)){
				stu2ram(nr_);
				if(ins_lin(nr_+1)){
					ram2stu(nr_+1);
					*ps_58_16='*';copy(s(6,154),ps_58_16+1,25);
					if(fldlen(58,101) && fldlen(6,29)) copy(s(6,29),s(58,101),fldlen(58,101));
					copy(s(6,2),ps_58_15,len58_15);
					*u(58,14)=*u(6,1); *i(58,34)=*i(6,9);
					if(fldlen(58,101) && fldlen(6,29)) copy(s(6,29),s(58,101),fldlen(58,101));
					*s(58,93)='J'; // om deze lijn bij afdrukken laadbon toch te drukken 
					if(fldlen(58,101) && fldlen(6,29)) copy(s(6,29),s(58,101),fldlen(58,101));
					stu2ram(nr_+1);
				}
				ram2stu(nr_);
			}
		}
#endif
	}
#endif
#if FLAGFLI
	if(*s(6,69)){
		stu2ram(nr_);
		if(ins_lin(nr_+1)){
			ram2stu(nr_+1);
			*ps_58_16='*';copy(s(6,69),ps_58_16+1,fldlen(58,16)-1);
			stu2ram(nr_+1);
		}
		ram2stu(nr_);
	}
	if(*s(6,68)){
		stu2ram(nr_);
		if(ins_lin(nr_+1)){
			ram2stu(nr_+1);
			*ps_58_16='*';copy(s(6,68),ps_58_16+1,fldlen(58,16)-1);
			stu2ram(nr_+1);
		}
		ram2stu(nr_);
	}
#endif
#if AFHAALVERG
	extra_kort(55,31,78);
#endif
#if LOSVERGOED
	extra_kort(58,32,79);
#endif
#if PALET_KORTING
	if(*f(6,83) && *f(58,7)>=*f(6,83)) extra_kort(67,34,82);
#endif
#if EXTEND_KORT
	extra_ekort();
#endif

#if !KAS2BON && !KAS2FACT && !KAS2JMCFACTUUR // & !KAS2JMCBON  : bij bons wordt in ovl900 het automatisch leeggoed geskipt, dus dan wel invullen
	copy(s(6,41),leeggcod,fldlen(6,41));
	*f(58,49)=*f(6,42);
	if(fldlen(58,62)){
		if(*ps_58_62=='S'){
			copy(s(6,44),leeggcod,fldlen(6,44));
			*f(58,49)=1;
		}
	}
	rec_=*pu_6_1;fasinit(6);copy(leeggcod,s(6,2),fldlen(6,41));
//#if FLAGVDW
	if(leeggcod[0]){ // wel artikel halen maar bij calc() niet rekenen
//#else
//	if(leeggcod[0] && (fldlen(2,34)==0 || *s(2,34)!='J')){
//#endif
		if(search(6,2)==0){
			*u(58,48)=*pu_6_1;
			calc_prx=*f(6,PrNrs[prxnr]);
/*  calc_prx=valu_cnv(def_munt,ft_munt,(double)*f(6,21+prxnr),prx_afrond);*/
			get_prx(NO);
			if(calc_kort && nokort==NO) *f(58,46)=calc_prx * (100.-calc_kort)/100.;
			else *f(58,46)=calc_prx;
		}
	}
	*pu_6_1=rec_;fasgeti(6);
#endif
	if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(8,8)) *f(58,38)=*f(6,30+94);
	else *f(58,38)=*f(6,30);
#if FLAGWAT// geen accijnzen tellen voor export 
	if(*s(2,22)) *f(58,38)=0;
#endif
#if FT_ACC_FREE
	if(fldlen(2,88) && *s(2,88)=='J') *f(58,38)=0; // accijnsvrije facturatie 
#endif
	if(fldlen(58,62)){
		if(*ps_58_62=='S' && *f(58,63)!=0) *f(58,38)/=*f(58,63);
	}
	calc_prx=*pf_58_20;
#if !KAS2JMCFACTUUR & !KAS2JMCBON  // GEEN prijs halen, probleem gratis artikel 
	get_prx(YES); if(fldlen(58,132)) *u(58,132)=PrijsDatum;
#endif	
// #if FLAGJAC || FLAGPSN
	if(fldlen(58,73)) *f(58,73)=calc_defprx; // default vp in AK-prx zetten om laten prijskorting te kunnen berekenen
// #endif
#if FACT_PROMO_REPL
	if(*s(58,93)!='P'){
		if(calc_sem!=-99) *f(58,43)=calc_sem;// sem. kort. van contrakt 
		if(fldlen(58,36)) *f(58,36)=hl_korting;
		if(fldlen(58,37)) *f(58,37)=hl_semkort;
		if(fldlen(58,95)) *f(58,95)=brij_tpct;
		if(fldlen(58,96)) *f(58,96)=brij_tbd;
	}
#else
	if(calc_sem!=-99) *f(58,43)=calc_sem;// sem. kort. van contrakt 
	if(fldlen(58,36)) *f(58,36)=hl_korting;
	if(fldlen(58,37)) *f(58,37)=hl_semkort;
	if(fldlen(58,95)) *f(58,95)=brij_tpct;
	if(fldlen(58,96)) *f(58,96)=brij_tbd;
#endif
#if EET_RIST
	*f(58,21)=*f(58,43); *f(58,36)=*f(58,37);
#endif
	if(*pf_58_20==0){
		*s(58,27)=def_inc; *pf_58_20=calc_prx;
#if FLAGAST
	  if(*s(2,71)=='J' && def_inc=='J' && *f(6,28)){ // BTW-eenheid
			bdf_=*pf_58_20/(1.+*f(6,28)/100.);
			*pf_58_20=round((double)bdf_); *s(58,27)='N';
		}
#endif
/* bij buitenlander met kassaprijs : de prijs excl.btw zetten */
		if(fldlen(2,22) && *s(2,22) && *s(2,22)!='.' && def_inc=='J' && *f(6,28)){
			bdf_=*pf_58_20/(1.+*f(6,28)/100.);
			*pf_58_20=round((double)bdf_); *s(58,27)='N';
		}
#if NO // FLAGPED
		if(*i(58,34)!=99){
			if(*s(58,62)=='P'){*f(58,70)=*f(8,34); *f(58,71)=0;}
			else {*f(58,71)=*f(8,35);*f(58,70)=0;}
		}
		else {*f(58,70)=0;*f(58,71)=0;}
#endif
		if(fldlen(58,28)) *f(58,28)=calc_kfr;/* contraktkorting in fr */
	}		
#if FLAGBDT   /* brandstof ALTIJD inc. BTW */
	if(*i(58,34)>=40 && *i(58,34)<=44) *s(58,27)='J';/* brandstof ALTIJD inc. BTW */
#endif
#if EET_RIST/* ristourno berekeningsprogramma */
	if(*pf_58_21==0 && newkort==NO) *pf_58_21=semestpc;
	newkort=NO;
#endif
#if FACT_PROMO_REPL
	if(*s(58,93)!='P'){
  	if(*pf_58_21==0 || newkort) *pf_58_21=calc_kort;
  	if(nokort) {*pf_58_21=0;*f(58,43)=0;}
	}
#else
	if(*pf_58_21==0 || newkort) *pf_58_21=calc_kort;
	if(nokort) {*pf_58_21=0;*f(58,43)=0;}
#endif
	copy(s(6,76),s(58,44),fldlen(58,44));
#if TRACEERDATA
	copy(s(6,77),s(58,135),fldlen(58,135));
#endif

#if KAS2FACT && KAS2GROOTH
/* probleem van biermanden zonder prijs op art.fiche : kassaprijs - 10% */
/* de kassawaarde zit in 58,41 (Awaarde) */
	if(*pf_58_20==0 && (fldlen(58,41) && *f(58,41))){/* kassabedrag incl. btw zit in 58,35 */
		if(*f(58,7)==0) *f(58,7)=1;
		bdf_=*f(58,41)/ *f(58,7);
		if(*s(58,27)!='J') bdf_/=1.+*pf_58_24/100.;
		*pf_58_20=round((double)bdf_); *pf_58_21=10;/* 10% op kassaprijs */
	}
#endif
	if(fldlen(58,41) && *i(6,9)!=99 && *s(58,16)!='*'){
		if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(8,8)) *f(58,41)=*f(6,18+94);
		else *f(58,41)=*f(6,18);
	}

#if FLAGPWH // liters zelf berekenen
	if(*ps_58_62=='B' && *pf_58_20){
		bdf_=*f(58,7);
		*f(58,7)=valu_cnv("EUR","EUR",(double)(bdf_/ *pf_58_20),(double)0.01);
		*ps_58_62='\0';
	}
#endif
	*u(58,17)=hash();
#if FLAGCMB/* gekoppeld CO2-artikel */
	if(*pu_58_14 && *ps_58_16!='*'){
		stu2ram(nr_);
		fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
		if(*s(6,79)){
			vp_=*f(58,7);ins_lin(nr_+1);
			ram2stu(nr_+1);*f(58,7)=vp_; copy(s(6,79),ps_58_15,len58_15);
			stu2ram(nr_+1);ram2stu(nr_);
		}
	}
#endif


#if PALET_PRO
	if(*ps_58_62=='P'){
		stu2ram(nr_);
		fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
		if(*s(6,82)){
			vp_=*f(58,7);ins_lin(nr_+1);
			ram2stu(nr_+1);*f(58,7)=vp_; copy(s(6,82),ps_58_15,len58_15);
			stu2ram(nr_+1);ram2stu(nr_);
		}
	}
#endif
	if(fldlen(58,62) && *ps_58_62=='P' && fldlen(6,85)){
		stu2ram(nr_);
		fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
		if(*s(6,85)){
			vp_=*f(58,7);ins_lin(nr_+1);
			ram2stu(nr_+1);*f(58,7)=vp_; copy(s(6,85),ps_58_15,len58_15);
			stu2ram(nr_+1);ram2stu(nr_);
		}
	}

	stu2ram(nr_);

}
#endif

#if NO // HISTORIEK
static LoadArtikelFromHistoriek()
{
	uint16 dt_his_;
	int16 bonart_beg_,mode_,plijn_,k;
	long   ft_his_; 

	dt_his_=0;ft_his_=0;
	fasinit(16);*l(16,10)=*pu_2_1;mode_=1;
	FOREVER{
		if(faskeyi(16,2,mode_)) break; mode_=2;
		if(*l(16,10)!=*pu_2_1) break;
		if(*u(16,3)>dt_his_){
			dt_his_=*u(16,3); ft_his_=*l(16,2);
		}
		else if(*u(16,3)==dt_his_){// bij gelijke datum, de hoogste factuurnummer nemen 
			if(*l(16,2)>ft_his_) ft_his_=*l(16,2);
		}
	}
	if(dt_his_==0) {errnum=14; goto endsr;}

	for(bonart_beg_=max_line-1;bonart_beg_>=0;bonart_beg_--) {
		ram2stu(bonart_beg_); if(test_line()) break;
	}
	bonart_beg_++;
	fasinit(16);*l(16,2)=ft_his_;*u(16,3)=dt_his_;mode_=1;plijn_=bonart_beg_;
	FOREVER{
		next:;
		if(faskeyi(16,3,mode_)) break; mode_=2;
		if(*l(16,2)!=ft_his_) break;
		if(*u(16,3)!=dt_his_) goto next;
		if(*u(16,23)==99) goto next; // geen leeggoed
		for(k=bonart_beg_;k<plijn_;k++){ // controle op dubbel artikel
			ram2stu(k);if(*u(58,14)==*l(16,20)) goto next;
		}
		init58(plijn_,YES);
    ram2stu(plijn_);
    *u(58,14)=*l(16,20);copy(s(16,21),ps_58_15,len58_15);copy(s(16,22),ps_58_16,fldlen(58,16));
		stu2ram(plijn_++);
		if(plijn_>=max_line) break;
	}
	endsr:;
}
#endif

static LoadArtikelFromPreviousFactuur()
{
  int16 mode_,j,k,pnr_,z,key,start_,stu_,len_,len1_,bonart_beg_,curs=2,jaartal,mm,dd;
	uint16 ft_nr_,ft_date_,journl_;
  long recs_[DIM58];
  uint16 n,krec_,dt_beg,dt_end,p_tb,pos_,nr_beg_,nr_end_;
  char ofname[40],subdir[25],str_[10];
  char rstu_[DIM58];
	
  jddate(*u(25,2),&jaartal,&mm,&dd);
  sysget(4704,25,subdir); 
	sysget(2166,2,&journl_);
  jaartal%=100; 

  FOREVER{
    redo:;
    scrget(2,173); z=1;
    scrfld(z++,25,1);
//    scrifld(z++,fm_uu5,&ft_nr);
    scrofld(z++,2,3,-1);
    scrifld(z++,fm_uu2_,&jaartal);
    scrifld(z++,fm_us20,subdir);
    key=scrupd(curs,0x81); curs=2;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==101) break;

		scrget(1,7);scrupd(-3,0); 
		dt_beg=datejd(jaartal,1,1); dt_end=datejd(jaartal,12,31);
		krec_=*u(2,1)+30000; p_tb=0;
		zero((char *)&recs_[0],sizeof recs_); zero(rstu_,sizeof rstu_);

		if(dt_beg<last_arc && fldlen(86,0)){
			fasinit(86);*u(86,5)=krec_; mode_=1;
			FOREVER{
				next_86:;
				if(faskeyi(86,4,mode_)) break; mode_=2;
				if(*u(86,5)!=krec_) break;
				if(*u(86,4)<dt_beg || (dt_end && *u(86,4)>dt_end)) goto next_86;
				if(*s(86,2)!=journl_) goto next_86;
				recs_[p_tb]=*l(86,1);rstu_[p_tb]=86;
				p_tb++; if(p_tb>=DIM58/2) break;
			}
		}
		if(fldlen(4,0)){
			fasinit(4);*u(4,5)=krec_; mode_=1;
			FOREVER{
				next_4:;
				if(faskeyi(4,4,mode_)) break; mode_=2;
				if(*u(4,5)!=krec_) break;
				if(*u(4,4)<dt_beg || (dt_end && *u(4,4)>dt_end)) goto next_4;
				if(*s(4,2)!=journl_) goto next_4;
				recs_[p_tb]=*l(4,1);rstu_[p_tb]=4;
				p_tb++; if(p_tb>=DIM58/2) break;
			}
		}
 
		if(p_tb==0) {errnum=14; return YES;}
		start_=0;
		FOREVER{
			scrnum=0;scrget(2,179);z=1;
			scrofld(z++,2,3,-1);
			for(j=start_;j<p_tb;j++){
				j++;scrifld(z++,fm_ou3,&j);j--;
				stu_=rstu_[j];fasinit(stu_);*l(stu_,1)=recs_[j];fasgeti(stu_);
				scrofld(z++,stu_,4,-1);
				scrofld(z++,stu_,3,-1);
				scrofld(z++,stu_,32,-1);
				scrofld(z++,stu_,28,-1);
				if(j==start_+14) break;
			}
			j=0;scrifld(77,fm_uu3,&j);
			key=scrupd(1,0x87);
			if(key==101) {errnum=39;return NO;}
			if(j>0 && j<=p_tb) {
				stu_=rstu_[j-1];fasinit(stu_);*l(stu_,1)=recs_[j-1];fasgeti(stu_);
				ft_nr_=*u(stu_,3); ft_date_=*u(stu_,4); break;
			}
			if(key==102) start_-=15;
			if(key==103) {start_+=15;if(start_>p_tb-15) start_=p_tb-15;}
			if(start_<0) start_=0;
		}

    zero(ofname,sizeof ofname);
    copy(subdir,ofname,25);
    for(k=0;k<25;k++) if(ofname[k]=='\0') break;
    copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
    for(k=0;k<40;k++) if(ofname[k]=='\0') break;
    stcli_d(&ofname[k],(long)ft_nr_,5,0);
    ofname[k+5]='.';stcli_d(&ofname[k+6],(long)jaartal,2,0);
    fasclos(-2);
    ofname[k+8]='\0';
		KommaKarakter='.',FieldSeparator='|'; SeqiMode=1;
		if(mnd_strt!=1){ // eerst kijken of het via de A-file moet gebeuren 
			ofname[k+8]='A';ofname[k+9]='\0';
			fasclos(-2);
			if(fasopen(ofname,1)==0){
				fasinit(80);zero((char *)&ft_stu.ft_nr,sizeof ft_stu);
				if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)) goto endsr;
				if(ft_stu.ft_date!=ft_date_) ofname[k+8]='\0';
				fasclos(-2);
			} else ofname[k+8]='\0';
		}
		fasclos(-2);
		if(fasopen(ofname,1)){
      ofname[k+8]='X';
      if(fasopen(ofname,1)) {
				errnum=1;
				goto redo;
      }
    }
		break;		
	}
  fasinit(80);zero((char *)&ft_stu.ft_nr,sizeof ft_stu);

	if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)) {fasclos(-2); goto endsr;}
  for(k=0;k<4;k++){
    copy(&ft_stu.opm_foot[k][0],&opm_foot[k][0],sizeof ft_stu.opm_foot[k]);
  }
  if(seqi_rec(sortbuf,ft_stu.stu8len)) {fasclos(-2); goto endsr;}
	for(bonart_beg_=max_line-1;bonart_beg_>=0;bonart_beg_--) {
		ram2stu(bonart_beg_); if(test_line()) break;
	}
	bonart_beg_++;


  for(j=0;j<max_line;j++){
    ram2stu(bonart_beg_);
    if(seqi_rec(sortbuf,ft_stu.stu58len)) break;
    pos_=0;
    for(k=0;k<200;k++){
      len_=fldlen(58,k+1);
      len1_=ft_stu.stu58[k][0];
      if(len_){
				if(len1_){
					if(len1_<len_) len_=len1_;
					if(k==6 || k==14 || k==15 || k==61) copy(&sortbuf[pos_],s(58,k+1),len_); // selectieve velden kopieren 
					if(k==19 && *s(58,16)=='*') copy(&sortbuf[pos_],s(58,k+1),len_); // eh.prijs enkel bij los artikel
				}
      }
      pos_+=len1_;
    }
    if(*s(58,16)!='*' || *f(58,7)) stu2ram(bonart_beg_++); else init58(bonart_beg_,NO);
		if(bonart_beg_>=max_line) break;
  }
  fasclos(-2);
  endsr:;
}

#if BARC_USED
static exec_work()
{
									
  if(werkveld[0]<'0' || werkveld[0]>'9') copy(werkveld,ps_58_16,20);
  else{
    fasinit(6);copy(werkveld,s(6,70),fldlen(6,70));
    errnum=faskeyi(6,BARC_KEY,0);
    if(errnum || cmpstr(s(6,70),werkveld,fldlen(6,70))){
      fasinit(6);copy(werkveld,s(6,71),fldlen(6,71));
      errnum=faskeyi(6,BARC_KEY+1,0); if(errnum==0 && cmpstr(s(6,71),werkveld,fldlen(6,71))) errnum=39;
      if(errnum==0 && fldlen(58,62)) *s(58,62)='S';
    }
		if(errnum && fldlen(64,1)){
			fasinit(6); fasinit(64); copy(werkveld,s(64,2),fldlen(64,2));
      errnum=faskeyi(64,1,0);
      if(errnum==0){
				fasinit(6); *u(6,1)=*u(64,3); fasgeti(6);
				if(*u(64,5)==1 && fldlen(58,62)) *s(58,62)='S';
			}
		}
    copy(s(6,2),ps_58_15,len58_15);
    *pu_58_14=*pu_6_1;
    copy(s(6,3),ps_58_16,fldlen(58,16));
  }
  if(*f(58,7)==0) *f(58,7)=1;
  if(errnum==0) zeros(werkveld,sizeof werkveld);
  else screrr(-1);
  return NO;
}
#endif




#if FLAGABT && FLAG248 && !FT_HERAFDRUK
static AskFtReferentie()
{
  int16 z=1,key;

	bkhref_ftnr=0;
  FOREVER{
redo:;
		scraddf(-1,0,0,0);z=1;
	  DisplayMenuTitel(4,"Toewijzen creditnota aan factuur",0xA);
    scraddf(z++,10,4,0); scraddf(z++,10,50,2);
    scraddf(z++,23,1,8);
    z=1;
		scrifld(z++,VarTextFmt(46,0),"Factuurnummer waarover deze creditnota gaat : ");
    scrifld(z++,fm_uu5,&bkhref_ftnr);
    scrifld(z++,VarTextFmt(13,0)," F8 neem aan ");
    key=scrupd(1,0x80);
		if(key==108) break;
  }
}
#endif

#if FLAG244
static DisplayBonInfo()
{
  int16 z=1,key;
	char cpostnm_[20],upostnm_[20];

	zero(cpostnm_,sizeof cpostnm_);	zero(upostnm_,sizeof upostnm_);
	if(fldlen(8,70) && *u(8,70)) GetPostName(cpostnm_,*u(8,70));
	if(fldlen(8,71) && *u(8,71)) GetPostName(upostnm_,*u(8,71));

  FOREVER{
redo:;
		scraddf(-1,0,0,0);z=1;
	  DisplayMenuTitel(4,"Update-informatie bon",0xA);
    scraddf(z++,10,4,0); scraddf(z++,10,20,2);
		scraddf(z++,12,4,0); scraddf(z++,12,26,2);
		scraddf(z++,14,4,0); scraddf(z++,14,28,2);
    scraddf(z++,23,1,8);
    z=1;
		scrifld(z++,VarTextFmt(18,0),"Aangemaakt door "); scrifld(z++,VarTextFmt(15,0),cpostnm_);
		scrifld(z++,VarTextFmt(24,0),"Laatst aangepast door "); scrifld(z++,VarTextFmt(15,0),upostnm_);
		scrifld(z++,VarTextFmt(26,0),"Datum laatste wijziging ");scrofld(z++,8,72,-1);
    scrifld(z++,VarTextFmt(10,0)," F1 terug ");
    key=scrupd(-1,0x01);
		if(key==101) break;
  }
}
#endif


#if ARTEXIST && !FT_HERAFDRUK && !KASINPUT && (FLAG244 || (FLAG248 & !BONFILE))
static LoadOfferte()
{
  int16 z=1,key,j,k,bonart_beg_,off_met_aantal;
  char str_[20],buf1000[1000],off_inc_;


  FOREVER{
redo:;
		scraddf(-1,0,0,0);z=1;
	  DisplayMenuTitel(4,"Kopieer artikels van offerte",0xA);
    scraddf(z++,10,4,0); scraddf(z++,10,25,2);
    scraddf(z++,23,1,8);scraddf(z++,23,13,8);
    z=1;
		scrifld(z++,fm_os63,"Referentie offerte : ");
    scrifld(z++,fm_uref,ref_offerte);scraddpicto(1,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
    scrifld(z++,fm_os10," F1 stop");scrifld(z++,fm_os15," F8 zoek op ");
    key=scrupd(1,0x81);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==101) return NO;
		if(key==108){
		  if(SearchOfferte(YES)) goto redo;
	  }
		if(key==5001){
		  if(SearchOfferte(NO)) goto redo;
	  }
    if(ref_offerte[0]=='\0') {errnum=38; goto redo;}
    if(key==108 || key==5001){
      zero(filnam,sizeof filnam);k=0;
      k+=copy0(MAP_OFFERTE,&filnam[k],20);
      k+=copy0(ref_offerte,&filnam[k],sizeof ref_offerte);
      k+=copy0(".csv",&filnam[k],5);
      fasclos(-2);
			KommaKarakter=',',FieldSeparator=';'; SeqiMode=1;
      errnum=fasopen(filnam,1);if(!errnum) break;
    }
  }
	for(bonart_beg_=max_line-1;bonart_beg_>=0;bonart_beg_--) {
		ram2stu(bonart_beg_); if(test_line()) break;
	}
  bonart_beg_++;
  fasinit(80);
  if(read_rec(0)) {fasclos(-2); return NO;}

  z=0;
  z++; 
  z++; 
	copy(s(2,1),buf1000,fldlen(2,0));
  *u(2,1)=get_num(z++);fasgeti(2);

  if(fldlen(2,42) && *s(2,42)=='J'){ // bij feestklant het adres van de offerte overnemen 
		zero(s(2,3),fldlen(2,3));
    for(k=2;k<=7;k++) get_str(s(2,k),z++,fldlen(2,k));
  	if(*s(2,3) && *s(2,4) && cmpstr(s(2,3),s(8,14),fldlen(8,14))){
	  	for(k=0;k<4;k++) copy(s(2,3+k),s(8,14+k),fldlen(8,14+k));
		}
	}
	k=*s(2,26)-'0';
  if(k<0 || k>9) k=0; if(fldlen(6,PrNrs[k])==0) k=0;
  off_inc_='N';if(sys3894 & (1<<k)) off_inc_='J';
  copy(buf1000,s(2,1),fldlen(2,0));
	off_met_aantal=get_num(17);  // vast op 17 !
  for(k=bonart_beg_;k<max_line;k++){
    if(read_rec(1)) break; z=0;
    ram2stu(k);
    *u(58,14)=get_num(z++);  // -A- rec
    get_str(s(58,15),z++,fldlen(58,15)); // code
    get_str(s(58,16),z++,fldlen(58,16)); // omschrijving 
		fasinit(6); *u(6,1)=*u(58,14);
		if(fasgeti(6)==0){
		  stu2ram(k);
		  Fill58FromNewArtikel(k);
		}
    z++; // AP
    z++;  // accijns 
    *f(58,20)=get_num(z++); *s(58,27)=off_inc_; // -F-  VP basis
    *f(58,23)=get_num(z++);  // vp excl
    *f(58,21)=get_num(z++); // kort%
    z++;  // kort bdr
    *f(58,36)=get_num(z++); // hl korting
    z++; // ft korting
    z++; // -L- ft prx ex
    z++; // ft pxr in
    z++; // netto prx ex
    z++; // netto pex in
    *f(58,43)=get_num(z++); // sem %
    z++; // sem hlkoring
    z++; // totaal sem korting 
    z++; // inhoud
    *f(58,24)=get_num(z++); // -T- btw
    z++; // groep
    z++; // rec leegg
    z++; // aantal leegg
    z++; // prijs leegg
    z++; // winst%
		if(off_met_aantal) *f(58,7)=get_num(z++); else z++; // -Z- aantal
		z++;// totaal belastb
		z++;// totaal leeggoed
		z++; // brij_tk_pct
		z++; // brij_tk_eur
		z++; // brij_tk_tot
		if(off_met_aantal) get_str(s(58,62),z++,fldlen(58,62)); else z++; // -Z- aantal
		z++; // q_per_bak
		if(*f(58,20) && *f(58,20)==*f(58,23)) *s(58,27)='N'; // men heeft prijstype gewijzigd
    stu2ram(k);
  }
  fasflush(0);
  fasclos(-2);
	if(DisplayWarning("Mag deze ingelezen offerte definitief geschrapt worden???",605,1)==YES) fasopen(filnam,99);;	 // echt deleten
  endsr:;
  return YES;
}


static SearchOfferte(zoek_op_klant)
int16 zoek_op_klant;
{
	int16 j,k,curs=1,key,z,start_,d_lin_scr=17,nr_,q_,lijnpos;
	uint16 funckeys,inq_klt;
  uint16 dt_=0;
  char dstr_[10];
	char str_[150];
	int q_offertes;
	int16 dd_,mm_,jj_;

  struct{
    char filname[30];
    char referentie[15];
	  char klantstu[200];
    uint16 datum;
  } tb_offerte[500];

//	#define DIM_TB_OFFERTE  200
	copy(s(2,1),buf1000,fldlen(2,0));
	inq_klt=0; if(zoek_op_klant) inq_klt=*u(2,1); // if(ref_offerte[0]!='\0') inq_klt=0;
	KommaKarakter=',',FieldSeparator=';'; SeqiMode=1;
	zeroL(&tb_offerte[0].filname[0],sizeof tb_offerte); q_offertes=0;
	zero(filnam,sizeof filnam);k=0;
  k+=copy0(MAP_OFFERTE,&filnam[k],20);
  k+=copy0(ref_offerte,&filnam[k],sizeof ref_offerte);
  k+=copy0("*.csv",&filnam[k],5);
	fasclos(-2);fasinit(80);
  fasopen(filnam,102);/* eerste call voor dir */
  FOREVER {
		fasinit(80);
    fasinfo(80,204);                            /* ophalen antwoord van dir */
    if (*s(80,1)=='\0') break;
    copy(s(80,1),tb_offerte[q_offertes++].filname,14);
    if(q_offertes>=500) break;
  }
	if(q_offertes==0) {errnum=39;goto end;}

  for(j=0;j<q_offertes;j++) {
	  zero(filnam,sizeof filnam);k=0;
    k+=copy0(MAP_OFFERTE,&filnam[k],20);
		k+=copy0(tb_offerte[j].filname,&filnam[k],sizeof (tb_offerte[0].filname));
    fasclos(-2);
    errnum=fasopen(filnam,1);if(errnum) break;

		fasinit(80);fasinit(2);
		zero(seqo_str,sizeof seqo_str);pos=0;
		if(read_rec(0)) {fasclos(-2); errnum=39; goto end;}
		z=0;
		get_str(tb_offerte[j].referentie,z++,10);
		zero(str_,sizeof str_);get_str(str_,z++,10);
		dt_=0;
		if(str_[0]){
			zero(dstr_,sizeof dstr_);copy(&str_[0],dstr_,2);dd_=val(dstr_);
			zero(dstr_,sizeof dstr_);copy(&str_[3],dstr_,2);mm_=val(dstr_);
			zero(dstr_,sizeof dstr_);copy(&str_[6],dstr_,4);jj_=val(dstr_);
			if(dd_ && mm_ && jj_) dt_=datejd(jj_,mm_,dd_);
		}
		tb_offerte[j].datum=dt_;
		*u(2,1)=get_num(z++);
		if(inq_klt==0 || *u(2,1)==inq_klt){ 
  		for(k=2;k<=7;k++) get_str(s(2,k),z++,fldlen(2,k));
	  	copy(s(2,1),tb_offerte[j].klantstu,s(2,8)-s(2,1));
		}
		else{
			for(k=j+1;k<q_offertes;k++) copy(tb_offerte[k].filname,tb_offerte[k-1].filname,sizeof tb_offerte[0]);
			zero(tb_offerte[q_offertes-1].filname,sizeof tb_offerte[0]);
			j--;q_offertes--;
		}
    fasclos(-2);
	}
  
	start_=0; nr_=0; lijnpos=0; scrnum=0;
	scraddf(-1,0,0,0);
	FOREVER{
    redo:;
    scrnum=0;scrget(2,330);z=1; q_=0;
    funckeys=0x80A1;
		if(start_>0) {
      scraddpicto(1,0,75,1,4,2,18,0,4,"up"); 
      funckeys+=2;
    }
		if((start_+d_lin_scr)<q_offertes) {
      scraddpicto(2,0,75,21,4,2,13,0,4,"down"); 
      funckeys+=4;
    }
    for(k=start_;k<(start_+d_lin_scr);k++){
      if(k>=q_offertes)	break;
      k++; scrifld(z++,fm_ou3,&k); k--;
			scrifld(z++,VarTextFmt(8,0),&tb_offerte[k].referentie);
			zero(str_,sizeof str_);
			copy(tb_offerte[k].klantstu,s(2,1),s(2,8)-s(2,1));
      j=copy0(s(2,3),&str_[0],fldlen(2,3));j+=copy0(" - ",&str_[j],3); j+=copy0(s(2,4),&str_[j],fldlen(2,4));str_[j++]='-';j+=copy0(s(2,6),&str_[j],fldlen(2,6));
      scrifld(z++,fm_os50,str_);  if(q_==(lijnpos+1)) scrchat(z-1,0x8); else scrchat(z-1,0xFF);
			scrifld(z++,fm_odat,&tb_offerte[k].datum);
			scraddpicto(11+k-start_,z-1,1,0,2,1,540,0,0,"schrap"); 
    }
    scrifld(69,fm_uu3,&nr_);
    key=scrupd(36,funckeys);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5011 && key<5011+d_lin_scr){
			j=key-5011+start_;
			copy(tb_offerte[j].klantstu,s(2,1),s(2,8)-s(2,1));
			scrget(2,331);z=1;
			
			for(k=3;k<7;k++) scrfld(z++,2,k);
			scrifld(z++,fm_odat,&tb_offerte[j].datum);
			scrifld(z++,VarTextFmt(8,0),&tb_offerte[j].referentie);
			key=scrupd(-1,0x19);
			if(key==104){
			  zero(filnam,sizeof filnam);k=0;
        k+=copy0(MAP_OFFERTE,&filnam[k],20);
		    k+=copy0(tb_offerte[j].filname,&filnam[k],sizeof (tb_offerte[0].filname));
        fasclos(-2);
        errnum=fasopen(filnam,99);
				for(k=j+1;k<q_offertes;k++) copy(tb_offerte[k].filname,tb_offerte[k-1].filname,sizeof tb_offerte[0]);
		  	zero((char *)&tb_offerte[q_offertes-1].filname,sizeof tb_offerte[0]);
				q_offertes--;if(q_offertes==0) {errnum=39; goto end;}
			}
			goto redo;
		}

    switch(key){
			case 8       : lijnpos--;// pijl opmhoog 
										 if(lijnpos<0) lijnpos=q_-1;
										 break;
			case 9       : lijnpos++;// pijl omlaag 
										 if(lijnpos>=q_) lijnpos=0;
									   break;
			case 12      :// PgUp 
			case 5001    :
			case 102     : if(start_>0){
											 start_-=d_lin_scr; if(start_<0) start_=0;lijnpos=0;scrnum=0;
										 }
										 break;
			case 13      :// PgDn 
			case 5002    :
			case 103     : if((start_+d_lin_scr)<q_offertes) {start_+=d_lin_scr;lijnpos=0;scrnum=0;}
										 break;
			case 10      : start_=0;lijnpos=0;scrnum=0;// HOME 
										 break;
			case 11      : start_=q_offertes-d_lin_scr;if(start_<0) start_=0;// END 
										 lijnpos=0;scrnum=0;
										 break;
			case 101     :
			case 106     : errnum=39;goto end;// annuleer 
										 break;
			case 18      :// ENTER 
			case 15      : // TAB  
			case 108     : if(nr_<1 || nr_>q_offertes) {errnum=34; goto redo;}
										 else{
											 if(nr_>0) copy(tb_offerte[nr_-1].referentie,ref_offerte,sizeof ref_offerte);
											 else errnum=38;
											 goto end;
										 }
										 break;
			default      : break;
    }
  }
 
end:;
	copy(buf1000,s(2,1),fldlen(2,0));
  if(errnum) return YES;
	else return NO;

	
}

static uint16 str2date(datestr_)
char *datestr_;
{
 
  uint16 dt_=0;
  int16 dd_,mm_,jj_;
  char str_[10];
 
  if(datestr_[0]){
    zero(str_,sizeof str_);copy(&datestr_[0],str_,2);dd_=val(str_);
    zero(str_,sizeof str_);copy(&datestr_[3],str_,2);mm_=val(str_);
    zero(str_,sizeof str_);copy(&datestr_[6],str_,4);jj_=val(str_);
    if(dd_ && mm_ && jj_) dt_=datejd(jj_,mm_,dd_);
  }
  return dt_;
}

#endif

#if FLAGAST & FLAG244
static LoadArtOnderMinStock()
{
  int16 k,pos58_;
	float stock_,min_stock_,norm_stock_;
 

  seldata.prx_klt=0;
  seldata.selp_use=NO;
  if(ovlcall(2215,2)) goto endsr;
	for(pos58_=max_line-2;pos58_>=0;pos58_--){
		ram2stu(pos58_); if(test_line()) break;
	}
	pos58_++; if(pos58_>=max_line-2){errnum=11; goto endsr;}
  scrget(1,7);scrupd(-3,0);
  fasinit(6);
  FOREVER{
    redo:;
    if(faskeyi(6,2,2)) break; 
		if(*i(6,9)==99) goto redo;
    if(DirCall_DRK2215_SelectArtikel()==NO) goto redo;
  	stock_=0;norm_stock_=0;min_stock_=0;
		stock_=*f(6,33);min_stock_=*f(6,36);
		if(fldlen(6,35)) norm_stock_=*f(6,35); 
		if(fldlen(66,1) && filiaal!=99){
 				fasinit(66);*u(66,2)=*u(6,1);
				if(faskeyi(66,1,0)) fasinit(66);
		}
		if(filiaal>=1 && filiaal<=10 && nm_loc[filiaal-1][0]!='\0'){ // 1 filiaal
			if(fldlen(66,11+(filiaal-1)*15)) stock_=*f(66,11+(filiaal-1)*15);
			if(fldlen(66,12+(filiaal-1)*15)) min_stock_=*f(66,12+(filiaal-1)*15);
			if(fldlen(66,13+(filiaal-1)*15)) norm_stock_=*f(66,13+(filiaal-1)*15);
		}
		else if(filiaal==0 && fldlen(66,11)){ // alle filialen
			for(k=0;k<10;k++) if(fldlen(66,11+k*15)&& nm_loc[k][0]!='\0') stock_+=*f(66,11+k*15);
		}
		stock_=valu_cnv("EUR","EUR",(double)(stock_),(double)(0.001)); // om vieze dingen na komma weg te doen
		if(stock_ < min_stock_){
			fasinit(58);
			copy(s(6,2),ps_58_15,len58_15);
			*pu_58_14=*pu_6_1;
			copy(s(6,3),ps_58_16,fldlen(58,16));
			stu2ram(pos58_);
		  Fill58FromNewArtikel(pos58_);
			if(norm_stock_) *f(58,7)=valu_cnv("EUR","EUR",(double)(norm_stock_-stock_),(double)(1.0));// norm_stock_-stock_;
			else *f(58,7)=valu_cnv("EUR","EUR",(double)(min_stock_-stock_),(double)(1.0)); // min_stock_-stock_;
			if(*f(58,7)==0) *f(58,7)=1;
			stu2ram(pos58_++);
		}
		if(pos58_>max_line){errnum=11; break;}
	}
  endsr:;
}

#endif


#if FLAGPED
static LoadArtFromLevBestelling()
{
  int16 j,k,n,key,fkey,z,curs,start=0,curspos_,mode_;
	uint16 g,rec_;
 
	copy(s(8,1),buf1000,fldlen(8,0));

	zero((char *)&SearchFilterTabel[0],SearchFilterTabelSize);
	n=0;scrget(1,7);scrupd(-3,0);
	FOREVER{
  	*u(8,1)=++n;
     g=fasgetu(8);
     if(g==47)break;
		if(*i(8,36)==50 && *u(8,3)<SearchFilterTabelSize) SearchFilterTabel[*u(8,3)]=1;
	}
  curs=4;
  fasinit(1); fasinit(8);
  redo:
  scrget(2,163);z=1;
  scrifld(z++,fm_os25,"Geleverde bestelbons");
  scrfld(z++,25,1);
  scrifld(z++,fm_os25,"toe te voegen");
  scrfld(z++,1,3);scraddpicto(1,z-1,0,0,2,1,112,0,4,"uitgebreid zoeken"); 
  scrifld(z++,fm_udat,&dt_bon_beg);
  scrifld(z++,fm_udat,&dt_bon_end);
  streepje(z++); z++;
	streepje(z++);
  key=scrupd(curs,0x81);curs=4;curspos_=fldcurs;
	if ((key/0x100)==1) key=(key&0xFF)+5000;
  if(key==101) goto endsr;
	if(key==5001){if(search(1,98)) goto redo;}
	else if(search(1,0)) goto redo;
select_bon:;
	zero((char *)rec_8,sizeof rec_8);
  fasinit(8);*u(8,3)=*u(1,1);
  fkey=1;
  for(k=0;k<DIM8;k++){
    next:;
    if(faskeyu(8,1,fkey)) break;
    fkey=2;
    if(*u(8,3)!=*u(1,1)) break;
    if(dt_bon_beg && *u(8,8)<dt_bon_beg) goto next;
    if(dt_bon_end && *u(8,8)>dt_bon_end) goto next;
    if(*i(8,36)!=50) goto next;
    rec_8[k]=*u(8,1);
  }
  if(k==0) {fasinit(8);errnum=14;goto redo;}
  if(k>1){
    FOREVER{
      redo82:;
      scrget(2,32);z=1;
      scrofld(z++,1,3,-1);
      for(j=start;j<k;j++){
				fasinit(8);*u(8,1)=rec_8[j];fasgeti(8);
				j++;scrifld(z++,fm_ou2,&j);j--;
				scrofld(z++,8,8,-1);
				scrofld(z++,8,25,-1);
				scrofld(z++,8,2,-1);
				if(j==start+14) break;
      }
      j=0;scrifld(62,fm_uu2,&j);
      key=scrupd(1,0x87);
      if(key==101) {fasinit(8);goto redo;}
      if(key==102) start-=15;
      if(key==103) {start+=15;if(start>k-15) start=k-15;}
      if(start<0) start=0;
			if(j>0 && j<=k) {rec_8[0]=rec_8[j-1];break;}
    }
  }
  *u(8,1)=rec_8[0];fasgetu(8);
	
	for(n=max_line-1;n>=0;n--){
		ram2stu(n); if(test_line()) break;
	}
	n++;
	fasinit(58);*u(58,2)=*u(8,1);mode_=1;
	FOREVER{
		if(faskeyi(58,1,mode_)) break; mode_=2;
		if(*u(58,2)!=*u(8,1)) break;
		rec_=*u(58,1);
		*u(58,1)=0;*u(58,2)=0;*u(58,17)=0;*f(58,31)=0;*f(58,20)=0;*f(58,21)=0;
		stu2ram(n++); if(n>=max_line) break;
		*u(58,1)=rec_;fasgeti(58);
	}
endsr:;
	copy(buf1000,s(8,1),fldlen(8,0));
}

#endif

static dsp_tot(show_tot_)
int16 show_tot_;
{
  int16 k,z,z8_25_,curs=0,norm_curs_,z_extra_,mail_direct_,sendviacodabox_,tlen_,q_exemp_;
	int key;
	uint16 lastrec_;
  float tot_st_=0,inp_st_=0;
	char *pdoc_,spec_warn_txt[55],buf10_[10];
  BEDRAG bd_;

	mail_direct_=NO; sendviacodabox_=NO;zero(spec_warn_txt,sizeof spec_warn_txt);BlockAutoSend=NO; 
#if !FT_HERAFDRUK && !EET_RIST
	if(fldlen(2,121) && *s(2,121)=='J' && *s(8,22)=='J') mail_direct_=YES;
	if(fldlen(2,122) && *s(2,122)=='J' && *s(2,21) && *s(8,22)!='J') mail_direct_=YES;
	if(fldlen(2,128) && *s(2,128)=='P' /* && *s(2,21) */) {sendviacodabox_=YES;}
#endif
#if STOCKMUT_FT_LOC && FLAG248 && !FT_HERAFDRUK// indien levering aan filiaal, dan de stock van dat filiaal verhogen
	if(filiaal==0) filiaal=99; zero(buf10_,sizeof buf10_);
	for(k=0;k<10;k++) if(orig_klt==loc_klt[k]) break;
	if(k<10 && loc_nr[k] && loc_nr[k]!=filiaal){
		if(loc_nr[k]==99) copy("DEPOT",buf10_,6);
		else copy(nm_loc[loc_nr[k]-1],buf10_,6);
		sprintf_s(spec_warn_txt,50,"   *** STOCKMUTATIE van %s naar %s ***",nm_fil,buf10_);
	}
#endif

#if FLAGARS
	if(sys2696) mail_direct_=NO; // nooit automatisch mailen vanuit B02
#endif
	if(alg_tot>=0) pdoc_=facttxt[0]; else pdoc_=credntxt[0];
  for(tlen_=0;tlen_<15;tlen_++) if(pdoc_[tlen_]=='\0') break;
#if ((FLAGBLI | FLAGMLF) & KAS2JMCFACTUUR) | KAS2JMC_DISPLAY_EINDE
	ConStyle(0); cls();
	if(YES){
#else
  if(stuk_per_stuk/* || fldlen(58,13)*/){
#endif
redo:;
		scrnum=0;
#if FLAGOPS  || FLAGAST // || KM_HEFFING // PAS OP : als ge iets verandert, dan ook dit scherm controleren!!!! (aantal afdrukken)
		scrget(2,529);
#else
    scrget(2,329);
#endif		
		z=1; z_extra_=110;
		scraddpicto(1,0,72,22,4,2,583,0,0,"Maak PDF"); 
		scraddpicto(2,0,76,22,4,2,569,0,0,"Mail"); 
#if FLAG244 && PRTFEESTBON
		scraddpicto(3,0,68,22,4,2,542,0,0,"Druk feestbon"); 
#endif
    scraddf(199,0,79-tlen_,6); scrifld(199,VarTextFmt(tlen_,0),pdoc_);
#if !FT_HERAFDRUK && FLAG248
#if FLAGSAS & FLAG248 & !KAS2JMCFACTUUR & !KAS2FACT & !KASINPUT & !KAS2GROOTH & !FT_HERAFDRUK // SAS grote voldaan/niet voldaan knop
		AddTextKey(z_extra_++,35,18,17,3,10001,"NIET voldane\nfactuur",0xFF);
		AddTextKey(z_extra_++,60,18,17,3,10002,"Voldane\nfactuur",0x21A72B);
#endif

	  if(mail_direct_ || sendviacodabox_){
			scraddf(z_extra_,7,37,9); 
			if(mail_direct_ && sendviacodabox_) scrifld(z_extra_++,VarTextFmt(38,0)," Factuur wordt gemaild EN via peppol! ");
			else if(sendviacodabox_) scrifld(z_extra_++,VarTextFmt(38,0)," Factuur wordt verstuurd via peppol! ");
			else scrifld(z_extra_++,VarTextFmt(24,0)," Factuur wordt gemaild! ");
			scraddpicto(4,z_extra_-1,1,0,2,1,540,0,0,"NIET mailen/versturen"); 
		}
#endif
#if FLAG244 & BON2FACTUUR & !KAS2JMCBON
		if(show_tot_==0) AddTextKey(z_extra_++,62,18,17,3,10003,"Factureer\ndeze bon",0x21A72B); // enkel voor de bon zelf, niet bij splitsen ofzo
#endif
	  if(spec_warn_txt[0]){
			scraddf(z_extra_,14,15,0x0E); scrifld(z_extra_++,VarTextFmt(50,0),spec_warn_txt);
		}
#if KMP_flag & FLAG244
    scraddf(z_extra_,22,15,8); scrifld(z_extra_++,fm_os14," F5 RETOUR-bon");
#endif
#if PRTLAADBON  & FLAG244
#if FLAGDDB || FLAGBTS || FLAGOPS
		if(YES){
#else
		if(upd_mode){
#endif
			scraddf(z_extra_,22,15,8);  scrifld(z_extra_++,fm_os14," F5 laadbon ");}
		else {scraddf(z_extra_,22,15,8);  scrifld(z_extra_++,VarTextFmt(17,0)," F5 leveringsbon ");}
#endif
//#if FLAGDKR && FLAG244
//    scraddf(z_extra_,22,15,8); scrifld(z_extra_++,VarTextFmt(28,0)," F5 druk bon ZONDER laadbon ");
//#endif
#if FLAGVSP
    scraddf(z_extra_,22,15,8); scrifld(z_extra_++,fm_os20,"F5 druk traceerblad");
#endif
#if FLAGMIM
    scraddf(z_extra_,22,15,8); scrifld(z_extra_++,fm_os20,"F5 druk adres-etiket");
#endif
#if FLAGVND && FLAG244
    scraddf(z_extra_,22,15,8); scrifld(z_extra_++,VarTextFmt(22,0),"F5 druk bon met tekort");
#endif
#if FLAGOPS
    //scraddf(z_extra_,22,15,8); scrifld(z_extra_++,fm_os14," F5 wis dubbel");
#endif
#if (FLAGEPD || FLAGSMM) && !FLAG248
    scraddf(z_extra_,22,33,8); scrifld(z_extra_++,VarTextFmt(16,0)," F10 wis dubbel ");
#endif
#if WINSTBLAD
    scraddf(z_extra_,22,15,8); scrifld(z_extra_++,fm_os14," F5 winstblad ");
#endif
#if !FLAG248
    scraddf(z_extra_,23,52,8);
#if FLAGPED
		scrifld(z_extra_++,fm_os14," F9 laadbon ");
#else
    if(prt_levbon=='J') scrifld(z_extra_++,fm_os14," F9 geen print");
    else scrifld(z_extra_++,fm_os14," F9 print bon ");
#endif
#endif
#if PALLETSTICKERS
    scraddf(z_extra_,20,51,0);  scrifld(z_extra_++,VarTextFmt(22,0),"Aantal palletstickers:");
    scraddf(z_extra_,20,73,2);  scrifld(z_extra_++,fm_uu2,&q_paletstick);
    scraddpicto(5,0,76,20,2,1,103,0,4,"Druk palletstickers");
#endif

#if INTRASTAT
    scraddf(z_extra_,23,52,8); scrifld(z_extra_++,fm_os14," F9 intrastat ");
#endif
    if(show_tot_){/* 1=som, 2=verschil */
      if(show_tot_==YES) bd_=alg_tot+v_alg_tot;
      else bd_=v_alg_tot-alg_tot;
      scraddf(z_extra_,4,60,2); scrifld(z_extra_++,fm_obd,&bd_);
    }
    scrfld(z++,25,1);
    bd_=belastbt+btw_tot; scrifld(z++,fm_obd,&bd_);

#if FLAG248
		scrifld(z++,fm_ou5,&ft_nr);
#else
    if(upd_mode) scrofld(z++,8,2,-1); else z++;
#endif
    bd_=tot_leeg; scrifld(z++,fm_obd,&bd_);
#if FLAG248
		scrifld(z++,fm_udat,&ft_date);
#else
    scrfld(z++,8,8);
#endif
#if KM_HEFFING && FLAGAST
		scrifld(z++,fm_obd,&KM_heffing);
#endif
    scrifld(z++,fm_obd,&alg_tot);
#if FT_HERAFDRUK
		scrofld(z++,8,22,-1);
#else
		fld_test(z++,8,22);
#endif
	  z8_25_=z;scrfld(z++,8,25);
#if FLAGOPS
//    scraddf(z_extra_,4,50,0); scrifld(z_extra_++,fm_os25,"Aantal afdrukken :");
/*    scraddf(z_extra_,4,69,2);*/ scrfld(z++,8,28); curs=z-1;
#endif

		norm_curs_=z;
    for(k=0;k<4;k++)scrifld(z++,fm_us75,opm_foot[k]);
    for(k=0;k<2;k++){
      if(*u(8,19+k)) scrifld(z++,fm_os60,std_txt[*u(8,19+k)-1]);
      else z++;
    }
    if(fldlen(58,12)){
      tot_st_=0;
      for(k=0;k<5;k++){
				if(cent[k].q_bak || cent[k].q_fles) {
					scrifld(z++,fm_os3,cent[k].eenh);
					scrifld(z++,fm_of6_0,&cent[k].q_bak);
					scrifld(z++,fm_of6_0,&cent[k].q_fles);
					tot_st_+=cent[k].q_bak+cent[k].q_fles;
				}
      }
    }
		if(curs==0) curs=norm_curs_;
#if FLAGSAS & FLAG248 & !KAS2JMCFACTUUR & !KAS2FACT & !KASINPUT & !KAS2GROOTH & !FT_HERAFDRUK // SAS grote voldaan/niet voldaan knop
		key=scrupd(curs,0x73A);curs=norm_curs_;
#else


#if KAS2JMCFACTUUR || KAS2JMCBON
    key=scrupd(curs,0x80); // ze MOETEN in dit stadium F8 nemen
#else
    key=scrupd(curs,0x3BA);curs=norm_curs_;
#endif
#endif
	  prt2pdf=NO;
 		if((key/0x10000)>0) key/=0x10000; 
		else if ((key/0x100)==1) key=(key&0xFF)+5000;
		switch(key){
			case 5001 : prt_levbon='J'; prt2pdf=YES; key=108;	break; // pdf
			case 5002 : if((mail_direct_==YES || sendviacodabox_==YES) && ((fldlen(2,121) && *s(2,121)) || (fldlen(2,122) && *s(2,122)=='J'))){
#if FLAG248
				            if(scr_ok("Deze factuur wordt al AUTOMATISCH gemaild/verzonden!  Toch manueel (=2x) mailen???")){
#else 
				            if(YES){
#endif
				              prt_levbon='J';prt2pdf=2;key=108;  // mailen
										}
									}
									else{prt_levbon='J';prt2pdf=2;key=108;}
									break; // mailen
#if FLAG244 && PRTFEESTBON
			case 5003 : 	if(chk_nr && upd_mode==NO){
				              load_sysnr(NO); *u(8,2)=last_vf+1; // zou anders toch nog foute kunnen afdrukken dan dat ie weg gaat schrijven 
											pFeestbon();// feestbon, zie parlay.c !
              				prt_levbon='L'; key=108; 
										}
				            else pFeestbon(); // feestbon, zie parlay.c !
										break; 
#endif
			case 5004 : mail_direct_=NO; sendviacodabox_=NO; BlockAutoSend=YES; goto redo; break; // NIET automatisch mailen/verzenden
#if PALLETSTICKERS
			case 5005 : if(q_paletstick>0){
#if FLAG248
			              uint16 nr_=ft_nr;
			              if(chk_nr){sysget(last_vfa,2,&last_vf); ft_nr=last_vf+1;} // nieuwe factuur: nummer dat hij zal krijgen
			              pPalletStickers();
			              ft_nr=nr_;
#else
			              uint16 nr_=*u(8,2);
			              if(upd_mode==NO){sysget(last_vfa,2,&last_vf); *u(8,2)=last_vf+1;} // nieuwe bon: nummer dat hij zal krijgen
			              pPalletStickers();
			              *u(8,2)=nr_;
#endif
			            }
			            goto redo; break;
#endif

			case 10001 : *s(8,22)='N'; key=108; break;
			case 10002 : *s(8,22)='J'; key=108; break;
			default : break;
		}
    if(key==102)return 2;
    if(key==106){
#if FT_HERAFDRUK
			return NO;
#else 
			if(alg_tot==0) return NO;
      else if(scr_ok("Wenst U echt deze bon/factuur te annuleren ?")) return NO;
#endif
		}
#if FLAG244
		if(fldlen(8,61)) *u(8,61)=*u(8,2); // nodig voor peppol
		if(fldlen(8,62)) *u(8,62)=*u(8,8); // nodig voor peppol
#endif
#if FLAG248 // bij factuur al default iets invullen
		if(sendviacodabox_ && *s(8,25)=='\0') sprintf_s(s(8,25),15,"%s-%05d","Peppol",ft_nr); // errnum=38;curs=z8_25_;goto redo;}
#endif
#if FLAGVND & FLAG244
		SPEC_factuurflag=NO;
    if(key==105){SPEC_factuurflag=YES;prt_levbon='J';key=108;} // bon met tekorten 
#endif
#if FLAGLAT & FLAG248
		SPEC_factuurflag=NO;
    if(key==112){SPEC_factuurflag=YES;key=108;} // factuur zonder layout
#endif

#if SAVEPDFFACTUUR && FLAG248
	if(key==112){
		if(SaveFactuur2Pdf()==NO) errnum=1;
		key=0;
	}
#endif

//#if FLAGDKR & FLAG244
//		SPEC_factuurflag=NO;
//    if(key==105){prt_levbon='J';SPEC_factuurflag=YES;key=108;} // bon zonder laadbon
//#endif		
#if FACT_PROMO & DEF_INPUT & (FLAG244 || !BONFILE) & !FT_HERAFDRUK // promoteksten van lege artikels wegdoen
		lastrec_=0;
		for(k=0;k<max_line;k++){
			ram2stu(k);
			if(lastrec_ /* && *u(58,14)==lastrec_ */ && *s(58,16)=='*' && *s(58,93)=='J') {
        lastrec_=*pu_58_1;init58(k,YES); ram2stu(k); *pu_58_1=lastrec_; stu2ram(k);
				lastrec_=0;
			} 
			else if(*u(58,14) && *f(58,7)==0 && *s(58,16)!='*') lastrec_=*u(58,14);
			else lastrec_=0;
		}

#endif

#if PRTLAADBON  & FLAG244
    if(key==105){
// #if FLAGSMM	| FLAGGBL	| FLAGIDH | FLAGDEM
#if FLAGDDB || FLAGBTS || FLAGOPS
			if(YES){
#else
			if(upd_mode){
#endif
			  plaadbon();prt_levbon='N'; key=108; 
		  }
		  else{
				if(chk_nr && upd_mode==NO){load_sysnr(NO); *u(8,2)=last_vf+1;} // zou anders toch nog foute kunnen afdrukken dan dat ie weg gaat schrijven 
		  	upd_mode=YES; // om parlay.c te misleiden
        q_exemp_=*pu_8_28;
#if PRTBON2X
#ifdef PRTBON_Q
		    q_exemp_=PRTBON_Q;
#endif
#endif
#if FLAGVOE
				q_exemp_=2;
#endif
		  	prt_KOPIE=0;
        for(k=0;k<q_exemp_;k++) {ft_prt();prt_KOPIE+=1;}
				upd_mode=NO;prt_levbon='L'; key=108; 
		  }
		}
//#else
//			plaadbon();goto redo;}
//#endif
#endif
#if FLAG248 && (FACT2XML || FACT2CODABOX)
		if(key==105 && OutputMapUbl[0]){
		  prt2pdf=2; ft_prt();
			if(*s(8,25)=='\0'){
				if(*u(8,8)==0) *u(8,8)=ft_date;
				jddate(*u(8,8),&Year,&Month,&Day);sprintf_s(s(8,25),fldlen(8,25),"%02d/%02d/%04d",Day,Month,Year);
			}
  		*u(8,2)=ft_nr; *u(8,8)=ft_date;MailMergeBijlage[0]=SpoolFileNr;
#if FACT2CODABOX
	  	if(DisplayWarning("Wenst u echt deze factuur te versturen via peppol? NEE=uitschrijven",605,1)==YES){// echt versturen
				ovlcall(2240,10);	 
#if FT_HERAFDRUK
				seqo_cft(); // om ID en status weg te schrijven in ftkopie
#endif
			}
			else // uitschrijven
#if FACT2XMLSPECIAL
#if FLAGVBE
      VBEFactuur2Pdf();
#endif
			if(ovltest(2141)) ovlcall(2141,0); else ovlcall(2240,11); 
#else
			ovlcall(2240,0);
#endif	 
#else
#if FACT2XMLSPECIAL
#if FLAGVBE
      VBEFactuur2Pdf();
#endif
			if(ovltest(2141)) ovlcall(2141,0); else ovlcall(2240,11); 
#else
			ovlcall(2240,0);
#endif
#endif
		}
#endif
#if FLAGKMP & FLAG244
    if(key==105){retourbon();goto redo;}
#endif
#if FLAGVSP
    if(key==105){PrintTraceerBlad();goto redo;}
#endif
#if FLAGMIM
    if(key==105){DrukAdresEtiket();goto redo;}
#endif
#if FLAGOPS
    //if(key==105){cmp_dblart();goto redo;}
#endif
#if (FLAGEPD || FLAGSMM) && !FLAG248
    if(key==110){cmp_dblart();goto redo;}
#endif
#if WINSTBLAD
    if(key==105){winst_lst();goto redo;}
#endif
#if !FLAG248
    if(key==109){
#if FLAGPED
#if BONSORT && (FLAG244 || (FLAG248 && BONFILE==NO))
      SortBon(0);
#endif
			plaadbon();prt_levbon='N'; 
#else
      if(prt_levbon=='J') prt_levbon='N'; else prt_levbon='J';
#endif
      return YES;
    }
#endif
#if INTRASTAT
    if(key==109){upd_intra();goto redo;}
#endif
#if GOS_flag
#if FLAG244 | (FLAG248 && BONFILE==NO)
    if(inp_st_!=tot_st_){errnum=73; goto redo;}
#endif
#endif
    if(key==104){/* mailen */
      prt_levbon='J'; prt2pdf=2; key=108;
    }
    if(key==110){prt_levbon='J';prt2pdf=YES;key=108;}/* pdf */
#if FLAG244 & BON2FACTUUR
		if(key==10003){
#if !FLAGDDC && !FLAGVLO && !FLAGABT
			prt_levbon='J'; 
#endif
			FactureerBonDirect=YES; if(fldlen(8,30)) *s(8,30)='J';
			key=108;
		}
#endif
    if(key!=108) goto redo;
  }
  return YES;
}
 
#if FLAGVBE
static VBEFactuur2Pdf()
{
	int16 k,jj,mm,dd;
	char tofile_[100],map_[50];
	long lft_nr;

	sysget(6500, 50, map_);
	if(map_[0]=='\0') return NO;
	k=prt2pdf;
	prt2pdf=2; ft_prt(); _sleep(3000);
	prt2pdf=k;
	jddate(ft_date,&jj,&mm,&dd);  jj=jj%100;
  lft_nr=jj;lft_nr*=100000;lft_nr+=ft_nr;
	zero(tofile_,sizeof tofile_);sprintf_s(tofile_,100,"%s%010d.pdf",map_,lft_nr);
	if(CopySpoolNrToFile(SpoolFileNr,tofile_)) return YES; 
	else return NO; // niet gelukt
}

#endif

#if FLAG241 && KASSASIMULATIE
static dsp_totTICKET()
{
  int key,z,curs=0;
	double bd_,bd_cash_,bd_betaald_,bd_terug_;
  float tot_st_=0,inp_st_=0;
	char bet_code_;


	bd_cash_=valu_cnv("EUR","EUR",(double)(alg_tot),(double)(0.05)); bd_terug_=0;bet_code_='G';bd_betaald_=0;
	curs=5;
	FOREVER{
redo:;
		scrnum=0; scrget(2,58); z=1;
		AddTextKey(110,35,18,17,3,10001,"Volledig\ngeld",0x007FFF);
		AddTextKey(111,15,18,17,3,10002,"Volledig\nBancontact",0x21A72B);
    bd_=belastbt+btw_tot; scrifld(z++,fm_od5_2,&bd_);
    bd_=tot_leeg; scrifld(z++,fm_od5_2,&bd_);
    scrifld(z++,fm_od5_2,&alg_tot);  scrifld(z++,fm_od5_2,&bd_cash_);
		scrifld(z++,fm_u_BG,&bet_code_); scrifld(-z,fm_ud5_2,&bd_betaald_); z++;
		scrifld(z++,fm_od5_2,&bd_terug_);
		key=scrupd(curs,0x1A2);curs=fldcurs;
	  prt2pdf=NO;
 		if((key/0x10000)>0) key/=0x10000; 
		else if ((key/0x100)==1) key=(key&0xFF)+5000;
		switch(key){
			case 10001 : bet_code_='G';bd_betaald_=bd_cash_; key=108; break;
			case 10002 : bet_code_='B';bd_betaald_=alg_tot; key=108; break;
			default : break;
		}
    if(key==102)return 2;
    if(key==106){
			if(alg_tot==0) return NO;
      else if(scr_ok("Wenst U echt dit ticket te annuleren ?")) return NO;
		}
    if(key==109){prt_levbon='N'; key=108;}
		bd_terug_=bd_betaald_-alg_tot;
    if(key==108) break;
  }
	if(bd_betaald_>alg_tot) bd_betaald_=alg_tot;
	BdBetaaldBC=0;BdBetaaldCASH=0;
	if(bet_code_=='B') BdBetaaldBC=bd_betaald_;
	else BdBetaaldCASH=bd_betaald_; 
  return YES;
}
#endif

#if WINSTBLAD
#include "parwinst.c"
#endif
 
/* volgende schermen zitten in de includes (nodig voor SCRSTD.BAT) */
/* scrget(2,25); scrget(2,23); scrget(2,122); scrget(2,23); scrget(2,32); scrget(2,120); */
/* scrget(2,94); scrget(2,143); scrget(2,28); scrget(2,179); scrget(2,276); */
/* scrget(2,177); scrget(2,219); scrget(2,220); scrget(2,230);scrget(2,275); */
/* scrget(2,26); scrget(2,288); scrget(2,296); */
 
#if FLAG248 && SAVEPDFFACTUUR
static SaveFactuur2Pdf()
{
	int16 k,yy,mm,dd;
	char tofile_[100],buf_[10],kassamap_[10];

	if(MapPdfFacturen[0]=='\0') return NO;  // niet ingevuld, dan afdrukken

	k=prt2pdf;
	prt2pdf=2; ft_prt();
	prt2pdf=k;

	zero(FtPdfFilename,sizeof FtPdfFilename);zero(tofile_,sizeof tofile_);zero(buf_,sizeof buf_);copy(s(25,3),buf_,3);
	jddate(ft_date,&yy,&mm,&dd); 
	sprintf_s(FtPdfFilename,30,"%s-%d-%05d.pdf",buf_,yy,ft_nr);
#if FLAGEET && KAS2JMCFACTUUR // kassafacturen in map per kassa, wel bij de werkposten filiaalnr invullen (+.j.4)
	zero(kassamap_,sizeof kassamap_);
  k=WerkpostFiliaalNr; if(k<1 || k>10) k=1;
  sprintf_s(kassamap_,10,"Kassa-%02d\\",k);
	sprintf_s(tofile_,100,"%s%s%s",MapPdfFacturen,kassamap_,FtPdfFilename); // dit is de gewenste naam		
#else
	sprintf_s(tofile_,100,"%s%s",MapPdfFacturen,FtPdfFilename); // dit is de gewenste naam		
#endif
	if(mnd_strt!=1 && mm>=mnd_strt){// indien boekjaar NIET op 1/1 begint, dan uitkijken met overlappende factuurnummers
		if(FileExist(tofile_)){// indien bestaand, dan een A achter naam zetten
	    sprintf_s(FtPdfFilename,30,"%s-%d-%05dA.pdf",buf_,yy,ft_nr);
	    sprintf_s(tofile_,100,"%s%s",MapPdfFacturen,FtPdfFilename); // dit is de gewenste naam		
		}
	}
	if(CopySpoolNrToFile(SpoolFileNr,tofile_)) return YES; 
	else return NO; // niet gelukt
}
#endif
// #include "DRK0240i.c"

static PrintPdfNaam()// Filenaam PDF 
{
  int16 pos_,slen_,len_;
	uint16 nr_;
  char buf_[30],string[100],*ps_;
				
  zero(string,sizeof string);pos_=0;
	if(alg_tot>=0) pos_=copy0(facttxt[taaltxt],&string[0],30);
	else pos_=copy0(credntxt[taaltxt],&string[0],30);
#if !FLAG248
  nr_=*u(8,2);
#else
  nr_=ft_nr;
#endif
  stcli_d(&string[pos_],(long)(nr_),6,1);pos_+=6;
  slen_=pos_;pos_=0;
  FOREVER{
    if(slen_<=0) break;
    zero(buf_,sizeof buf_);
    copy("\xD0\xCF",buf_,2);
    if(slen_>25) len_=25; else len_=slen_;
    copy(&string[pos_],&buf_[2],len_);
    buf_[2+len_]=0xD0;
    prttext(buf_);
    slen_-=len_;pos_+=len_;
  }
}

static prt_pdfdata()/* initialiseren PDF */
{
  uint16 nr_;
  char str_[75];
 
  prttext("\xD0\xCF");
  if(alg_tot>=0) prttext(facttxt[taaltxt]); else prttext(credntxt[taaltxt]);
  zero(str_,sizeof str_);
#if !FLAG248
  nr_=*u(8,2);
#else
  nr_=ft_nr;
#endif
  stcli_d(str_,(long)(nr_),5,1);prttext(str_);
 prttext("\xD0");

}

#if (FLAG248 & BONFILE) | KASINPUT | FACT_RISTOURNO
static facturatie()
{
  int16 curs=1,k,key,z;
  uint16 rec_nr_,fl_upd_bkh_=NO;

  if(dt_bon_end==0) dt_bon_end=*u(25,2); if(OnlyKassaBons=='\0') OnlyKassaBons='N';
	if(SelectieAlleVoldaneBons=='\0') SelectieAlleVoldaneBons='N';
  ft_nr=last_vf+1;
#if FLAGVRK
	ft_nr=*u(8,2); // factuurnummer zelfde als bonnummer
#endif
  for(k=0;k<2;k++) *u(8,19+k)=last_vt[k];
  redo:
  scrnum=0;scrget(2,26);
  z=1;
  scrfld(z++,25,1);
  scrifld(z++,fm_udat,&ft_date);
  scrifld(z++,fm_uu5,&ft_nr);
  for(k=0;k<2;k++) scrfld(z++,8,19+k);
  if(art_exist || k_omz_exist){
		if(fl_upd_bkh_) scrifld(z++,fm_u_JNS,&stock_JN); else scrifld(z++,fm_os1,&stock_JN); 
	}
  else streepje(z++);
  if(bkh_exist){
		if(fl_upd_bkh_) scrifld(z++,fm_u_JN,&boek_JN); else scrifld(z++,fm_os1,&boek_JN);
	}
  else streepje(z++);
  scrifld(z++,fm_udat,&dt_bon_beg);
  scrifld(z++,fm_udat,&dt_bon_end);
  if(fldlen(2,33)) scrifld(z++,fm_us1_U,&ft_tijdstp);
  else streepje(z++);
  if(fldlen(8,74)) scrifld(z++,fm_u_JN,&OnlyKassaBons);
  else streepje(z++);
#if KASINPUT
	streepje(z++);
#else
	scrifld(z++,fm_u_JN,&SelectieAlleVoldaneBons);
#endif
  key=scrupd(curs,0x7E1);curs=1;
  if(key==101) return NO;
  if(key==111) ovl_exit(0);
  k=ftchk();if(errnum){curs=k+7;goto redo;}
	#if FLAG248 & !FT_HERAFDRUK
		if(key==112){if(fl_upd_bkh_) fl_upd_bkh_=NO; else fl_upd_bkh_=YES; goto redo;}
#endif
	if(key!=108 && !(key==109 && stuk_per_stuk)) goto redo;
#if FLAGVRK
	if(key==108) {key=109;chk_nr=NO;} // forceren om altijd deze nummer te nemen 
#else
  if(key==109 && stuk_per_stuk){
		if(DisplayWarning("Wenst U echt een afwijkende bon/factuurnummer te gebruiken?",605,1)==YES) chk_nr=NO;
	}
#endif
  for(k=0;k<2;k++) last_vt[k]=*u(8,19+k);
  return YES;
}
#endif

static add_afhaling(nr_)
int16 nr_;
{
  int16 j,k,t_nr_;
	
	fasinit(6);
  for(j=0;j<max_line;j++){ram2stu(j);if(test_line()==NO) break;}
  if(j>=max_line) goto endsr;
  init58(j,YES);
  if(nr_==-1){
    if(len58_62) *ps_58_62='S';
    *ps_58_16='*';copy(s(62,9),ps_58_16+1,25);
  }
  else if(nr_==99){
		if(len58_62) *ps_58_62='S';
    copy("*-----------------------------",ps_58_16,30);
		for(k=0;k<30;k++)	if(fldlen(62,12+k*5) && *u(62,12+k*5)) break;
    if(k>=30) zero(s(62,9),fldlen(62,9)); // enkel als alle artikels zijn overgezet
  }
  else {
		if(fldlen(62,9)<60 || *(s(62,9)+30+nr_)!='J') goto endsr; // niet geselecteerd
    *pu_6_1=*u(62,12+nr_*5); fasgeti(6);
    *f(58,7)=*f(62,10+nr_*5);*s(58,62)=*s(62,11+nr_*5);
    *pu_58_14=*pu_6_1;
    copy(s(6,2),ps_58_15,len58_15);
    t_nr_=taal_nr;if(*s(6,3+t_nr_)=='\0') t_nr_=0;
    copy(s(6,3+t_nr_),ps_58_16,fldlen(58,16));
    *f(62,10+nr_*5)=0;*s(62,11+nr_*5)=0;*u(62,12+nr_*5)=0;
    if(fldlen(62,13+nr_*5) && *s(62,13+nr_*5)=='J'){
			*f(58,20)=0.00001; // gratis
			for(k=0;k<fldlen(58,16)-7;k++) if(*(s(58,16)+k)=='\0') break;
			copy(" GRATIS",s(58,16)+k,7);
		}
  }
  stu2ram(j);
  keepdata=YES;
  endsr:;
}
/*
#if MAIL_ALLOW
static chk_email()
{
  int16 z,key,k,at_fnd_,punt_fnd_;
  char kar_;
							
  if(fldlen(2,21)==0) return NO;
							
  at_fnd_=0; punt_fnd_=0;
  for(k=0;k<fldlen(2,21);k++){
    kar_=*(s(2,21)+k);
    if(kar_=='\0') break;
    if(kar_=='@') at_fnd_++;
    if(kar_=='.' && at_fnd_) punt_fnd_++;
  }
  if(at_fnd_==1 && punt_fnd_>0) return YES;
  FOREVER{
    redo:;
    scrget(1,249); z=1;
    for(k=3;k<7;k++) scrofld(z++,2,k,-1);
    scrfld(z++,2,21);
    key=scrupd(1,0x81);
    if(key==101) return NO;
    at_fnd_=0; punt_fnd_=0;
    for(k=0;k<fldlen(2,21);k++){
      kar_=*(s(2,21)+k);
      if(kar_=='\0') break;
      if(kar_=='@') at_fnd_++;
      if(kar_=='.' && at_fnd_) punt_fnd_++;
    }
    if(at_fnd_!=1 || punt_fnd_==0) {errnum=34;goto redo;}
    if(key==108) {fasupd(2);return YES;}
  }
}
#endif
*/
#if FLAG244 & BONFILE & !SAMENVOEGEN & !PDA_LGRETOUR & !WEB_ADD
static add_bon(k_rec_)
uint16 k_rec_;
{
  int16 z,key;
  uint16 rec_;
 
  upd_mode=NO; ViaToer=NO; chk_nr=YES;FactureerBonDirect=NO;
#if !NO_TOER_ASK
  if(k_rec_==0 && fldlen(63,1) && fldlen(8,39)){
    fasinit(63);
    FOREVER{
      redo:;
      scrget(2,136);z=1;
      scrfld(z++,25,1);
      scrfld(z++,63,3);scraddpicto(9,z-1,0,0,2,1,112,0,4,"Uitgebreid zoeken"); 
      key=scrupd(2,0x481);
		  if ((key/0x100)==1) key=(key&0xFF)+5000;
      if(key==101) goto endsr;
      if(key==111) ovl_exit(-1);
			if(key==5009){
				if(search(63,98)) goto redo;
				key=108;
			}
      if(*s(63,3)){
				if(search(63,0)) goto redo;
				ViaToer=YES;
      }
      else {fasinit(63);ViaToer=NO;}
      inq_toer=*u(63,1);
      if(key==108) break;
    }
  }
#endif
  rec_=k_rec_;
  zero(toer_klt,sizeof toer_klt);zero(toer_qbons,sizeof toer_qbons);
  if(ViaToer) copy(s(63,10),toer_klt,fldlen(63,10));
	else inq_toer=0;
  FOREVER{
    next_klt:;
    if(k_rec_==0 && ViaToer){
      *u(63,1)=inq_toer;fasgeti(63);
      if(disp_toer(0)) break;
      rec_=*pu_2_1;
    }
    sysget(last_vfa,2,&last_vf);
    ft_init(YES);
    if(k_rec_ || ViaToer){*pu_2_1=rec_;fasgeti(2);}
    *u(8,2)=last_vf+1;prt_levbon=DEFLVPRT;q_paletstick=1;
    if(fldlen(8,39) && ViaToer) *u(8,39)=inq_toer;
#if FLAGGRS // verplichten om datum in te vullen
		*u(8,8)=0;
#endif
    if(exec()==NO){
      if(ViaToer){/* markering terug afzetten */
				for(z=0;z<DIM_TKLT;z++) if((*pu_2_1+30000)==toer_klt[z]) break;
				if(z<DIM_TKLT) toer_klt[z]-=30000;
				goto next_klt;
      }
      else break;
    }
    write_bon();
#if KORT_DELAYED
    if(*f(8,21) && *f(2,50)){
      if(*f(8,21)<*f(2,50)) *f(2,50)-=*f(8,21);
      else *f(2,50)=0;
      fasupd(2);
    }
#endif
    last_vf=*u(8,2);
#if FLAG244 & BON2FACTUUR
		if(FactureerBonDirect) {*u(26,5)=*u(8,1);ovlcall(248,1);FactureerBonDirect=NO;}
#endif
    if(k_rec_) break;
  }
  endsr:;
}
#endif
 
#if ANAL_ASK & FLAG248 & !KASINPUT & !FT_HERAFDRUK
static ask_a_rek()
{
  int16 key;
 
  fasinit(3); if(a_grbrek){*l(3,2)=a_grbrek;faskeyi(3,2,0);}
  FOREVER{
    redo:;
    scrget(2,296);
    scrfld(1,3,3);
    key=scrupd(1,0x81);
    if(key==101) return YES;
    if(*s(3,3)){
      if(search(3,0)) goto redo;
      if(((*s(3,2) &0xF0)>>4)!=9) {errnum=38; goto redo;}
      a_grbrek=*l(3,2);
      a_rec_nr=sear_grb(a_grbrek);
    } else{fasinit(3);a_grbrek=0;a_rec_nr=0;}
    if(key==108) break;
  }
  return NO;
}
#endif

#if BLOK_ART && (FLAG244 | (FLAG248 & !BONFILE))
static blokkeer_art()
{
	flag ok_=YES,max_,k;
	uint16 his_klt_;
	  
  if(DoBlokkeerCheck==NO) return NO;
	if(fldlen(2,120)){ // indien in bestelbon, dan OK
		max_=fldlen(2,120)/2;
    for(k=0;k<max_;k++) if(*u(6,1)==*(uint16 *)(s(2,120)+k*2)) break;
		if(k<max_) return NO;
	}
	his_klt_=*u(2,1);
#if FLAGSAS || FLAGVDW
	if(fldlen(2,51) && *u(2,51)) his_klt_=*u(2,51); 
#endif
	if(fldlen(16,1)){
    fasinit(16);*l(16,10)=his_klt_;*l(16,20)=*pu_6_1; *u(16,3)=ft_date-800;
		if(faskeyi(16,1,1)) ok_=NO;
    else if(*l(16,10)!=his_klt_ || *l(16,20)!=*pu_6_1 || *l(16,15)) ok_=NO; 	
#if FLAGSMM || FLAGSAS// moeten het 2x gekocht hebben
		if(ok_){
			if(faskeyi(16,1,2)) ok_=NO;
      else if(*l(16,10)!=his_klt_ || *l(16,20)!=*pu_6_1 || *l(16,15)) ok_=NO; 	
		}
#endif
	}
	else if(fldlen(60,1)){
    fasinit(60);*l(60,2)=his_klt_;*l(60,22)=*pu_6_1;
    if(faskeyi(60,1,0)==0) ok_=NO;
	}

	if(ok_==NO){
		if(fldlen(58,40)) return YES; // enkel rood displayen
		else{
      if(DisplayWarning("Deze klant heeft dit artikel nog nooit gekocht, toch toestaan?",61,1)==YES) return NO;
	  	else return YES;
		}
	}
	return NO;
}
#endif

#if FLAG244 & BONFILE & !SAMENVOEGEN & !WEB_ADD
static upd_bon(fl_automatic_)
int16 fl_automatic_;
{
  int16 j,k,key,first_=YES,ori_fil_;
	char ori_8_25_[50];
  flag splitsen,via_pdabon_=NO;
  uint16 rec1_;
  float k_perc_;

#if PDA_TRACEER
	via_pdabon_=NO; if(pbonnr>=0) via_pdabon_=YES;
#endif

  FOREVER{
    ft_init(YES);prt_levbon='N';upd_mode=YES;splitsen=NO;FactureerBonDirect=NO;
#if PDA_LGRETOUR || PDA_TRACEER
		if(pbonnr>=0){
      fasinit(2);
			if(pdabons[pbonnr].bonnr) {*s(2,3)='+'; stcli_d(s(2,3)+1,(long)(pdabons[pbonnr].bonnr),5,0);}
			else{*pu_2_1=pdabons[pbonnr].krec; if(*u(2,1)) fasgeti(2);}
		}
#endif
#if UPD_PRTBON
    prt_levbon='J';
#endif
redo:
		j=2; 
		if(fl_automatic_){
			j=10; if(first_==NO) break;
		}
		first_=NO;
   	if(!get_klt("aan te passen",j))break;
    if(!load_bon(NO,0))goto redo;
    if(fldlen(8,49)){
      if(*u(8,49) && *u(8,49)!=procid){
	if(scr_ok("Bon in gebruik door ander scherm! Toch doorgaan???")==NO) goto redo;
      }
      *u(8,49)=procid;fasupd(8);
    }
		for(k=0;k<4;k++) copy(s(8,65+k),opm_foot[k],fldlen(8,65+k));
#if PDA_TRACEER
		if(pbonnr>=0) AddPDATracedata2Doc(NO);
#endif
#if PDA_LGRETOUR
    if(add_pbon()==NO){errnum=11;goto redo;}
#endif
#if REY_flag
    if(fldlen(8,30)) *s(8,30)='J';
#endif
    if(exec()){
#if SPLITS_BON
      splitsen=chk_qlv();
#endif
/*    write_bon(); */
      if(splitsen && alg_tot==0){
	if(scr_ok("Bontotaal is 0, mag deze bon geschrapt worden ?")) kill();
	else write_bon();
      }
      else write_bon();
#if FLAG244 & BON2FACTUUR
			if(FactureerBonDirect) *u(26,5)=*u(8,1); 
#endif
#if PDA_LGRETOUR 
      if(pbonnr>=0) kill_pbon(pbonnr);
#endif
    }
    if(fldlen(8,49)){
      if(fasgeti(8)==0){
				*u(8,49)=0;fasupd(8);
			}
    }
#if SPLITS_BON
    orig_klt=*pu_2_1;ori_fil_=filiaal; k_perc_=0;
		copy(s(8,25),ori_8_25_,fldlen(8,25));
    if(splitsen){
      v_alg_tot=alg_tot;
#if !MAILREST
      ft_init(NO);
#if !ALB_flag
      fasinit(2);
#endif
#endif
      redo_2:;
      scrget(2,131);
      scrfld(1,2,3);
      scrifld(2,fm_uf2_0,&k_perc_);
      key=scrupd(1,0xA0);
      if(key==106) goto no_splits;
      if(search(2,0)) goto redo_2;
#if MAILREST
      if(*s(2,21)=='\0'){errnum=34;goto redo_2;}/* geen email-adres */
#endif
      if(key!=108) goto redo_2;
      scrget(1,7);scrupd(-3,0);
      select_mnt();
      if(k_perc_) *f(2,18)=k_perc_;
      *u(8,1)=0;j=0;/* resterend gedeelte op andere bon zetten */
      for(k=0;k<max_line;k++){/* eerst overtollige lijnen schrappen */
				ram2stu(k);
				if(*pu_58_1 && *f(58,61)){
					*pf_58_31=-*f(58,61);*f(58,7)=*pf_58_31;
					*pu_58_1=0;*u(58,2)=0;*u(58,3)=j;
					if(fldlen(58,62) && (*s(58,62)=='P' || *s(58,62)=='X')) *s(58,62)='\0'; // wordt terug in bakken gezet
					stu2ram(j++);
	}
      }
      init58(j,NO);
#if SPLITS_OMZET/* gedeelte semestriele korting bijhouden op klant */
      rec1_=*pu_2_1;fasinit(2);*pu_2_1=orig_klt;fasgeti(2);
      calc();
      if(fldlen(2,64)) *f(2,64)+=semestbd;fasupd(2);
      fasinit(2);*pu_2_1=rec1_;fasgeti(2);
      if(k_perc_) *f(2,18)=k_perc_;
#endif

#if SPLITS_KAS_PR/* prijzen nemen van nieuwe klant */
      prxnr=*s(2,26)-'0';
      if(prxnr<0 || prxnr>9) prxnr=0;
      if(fldlen(6,PrNrs[prxnr])==0) prxnr=0;
      semestpc=*f(2,56);
      def_inc='N';if(sys3894 & (1<<prxnr)) def_inc='J';
      *u(8,1)=0;j=0;
      for(k=0;k<max_line;k++){
				ram2stu(k);
				if(*f(58,7)){
					*pu_58_1=0;*u(58,2)=0;*u(58,3)=j;
					*pf_58_20=0;*u(58,17)=0;
					*pf_58_24=def_btw;
					*s(58,27)=def_inc;
					if(len58_25) copy(def_ext,ps_58_25,len58_25);
					*pf_58_21=*f(2,18);
					stu2ram(j++);
				}
      }
      init58(j,NO);
#endif

#if SCREXEC
			DoBlokkeerCheck=NO;
			if(fldlen(8,48)) {*u(8,48)=ori_fil_;filiaal=*u(8,48);}
			copy(ori_8_25_,s(8,25),fldlen(8,25));
      redo_detail:;
      FOREVER{
	if(dsp_detail()==NO) goto no_splits;
	if((k=dsp_tot(YES))==NO) goto no_splits;
#if SPLITS_TICKET
	if(k==1){
	  prt_error=NO;
	  print_strook();
	  if(prt_error==NO) break;
	}
#else
	if(k==1) break;
#endif
      }
#endif
      scrget(1,7);scrupd(-3,0);
#if MAILREST
      if(scr_ok("Wenst U echt deze tekorten door te mailen naar de klant ?")==YES){
	out_t_mai();
      }
      else goto redo_detail;
#else
      j=0;
      for(k=0;k<max_line;k++){/* lege lijnen terug schrappen */
	ram2stu(k);
	if(*pu_58_14 && *pf_58_31){/* enkel echte artikels */
	  *u(58,3)=j;
	  stu2ram(j++);
	}
      }
      init58(j,NO);

#if STOCK244/* stock van dit gedeelte aftrekken */
      for(k=0;k<max_line;k++){
	ram2stu(k);upd_artstock(NO);
      }
#endif
      load_sysnr(YES);
      if(*pu_2_1==orig_klt || test_kontb(j)){/* indien zelfde klant of geen bons */
				if(*s(8,25)) copy(s(8,25),ori_8_25_,fldlen(8,25));
	ft_init(NO);

	sysget(last_vfa,2,&last_vf);
	*u(8,3)=*pu_2_1;*u(8,2)=last_vf+1;
	if(fldlen(8,33)){
	  if(fldlen(2,35) && *s(8,33)=='\0') *s(8,33)=*s(2,35);
	}
	for(k=0;k<6;k++){
	  copy(s(2,2+k),s(8,13+k),fldlen(8,13+k));
	  if(fldlen(2,142+k) && *s(2,142+k)) copy(s(2,142+k),s(8,13+k),fldlen(8,13+k)); // afwijkend leveringsadres
	}
#if SPLITS_UPNR
	last_vf++; sysput(last_vfa,2,&last_vf);      /* nummer wegschrijven */
#endif
	if(fldlen(8,48)) *u(8,48)=filiaal;
	copy(ori_8_25_,s(8,25),fldlen(8,25));
#if KMP_flag
	load_sysnr(YES); sysget(last_vfa,2,&last_vf);
	*u(8,2)=last_vf+1;
	last_vf++; sysput(last_vfa,2,&last_vf);      /* nummer wegschrijven */
#endif
      }
      else {
	add_kontb(j);
      }
      select_mnt();
      calc();
      write_konb();
			ClearSysPosNrCheck();
      sysflush();
#if KORT_DELAYED/* gedeelte  korting bijhouden op klant */
      rec1_=*pu_2_1;fasinit(2);*pu_2_1=orig_klt;fasgeti(2);
      if(fldlen(2,49) && *s(2,49)=='J'){
	*f(2,50)+=tot_kort;fasupd(2);
      }
      fasinit(2);*pu_2_1=rec1_;fasgeti(2);
#endif
#if SPLIST_STATIST && STATISTIEK/* gedeelte  korting bijhouden op klant */
      rec1_=*pu_2_1;fasinit(2);*pu_2_1=orig_klt;fasgeti(2);
      statistiek_upd(YES);
      fasinit(2);*pu_2_1=rec1_;fasgeti(2);
#endif
#endif
    }
    no_splits:;
#endif
#if PDA_LGRETOUR
    break;
#endif
#if PDA_TRACEER
	if(via_pdabon_) break;
#endif
#if FLAG244 & BON2FACTUUR
		if(FactureerBonDirect) ovlcall(248,1);
#endif
  }
}
#endif

#if SCREXEC
static LijnDetail(nr_)
int16 nr_;
{
  uint16 dt_vrk_[5],fl_statistiek_;
	int16 curs=1,k,key,z,dd,mm,jj,mode_;
  float bd_,vrk_per_[3],qlv_bons_,pr_net_;
  char *pdum_;

redo_detail:;
	scrget(1,7);scrupd(-3,0);
  calc();
  ram2stu(nr_);
  if(fldlen(58,100)) fill_astock(); /* fill actuele stock in */
	stu2ram(nr_);

  fasinit(6); if(*pu_58_14){*pu_6_1=*pu_58_14;fasgeti(6);}

  jddate(*u(8,8),&jj,&mm,&dd); mm--;
  zero((char *)&vrk_per_[0],sizeof vrk_per_);fl_statistiek_=NO;
	if(*pu_58_14 && fldlen(16,1)){
		fl_statistiek_=YES;
		jddate(*u(8,8),&jj,&mm,&dd); mm++; if(mm>12){mm=1; jj++;}
	  for(k=3;k>=0;k--){
		  dt_vrk_[k]=datejd(jj,mm,1);
	  	mm--;if(mm<1){mm=12; jj--;}
	  }
		fasinit(16); *l(16,20)=*u(6,1);*l(16,10)=*u(2,1); mode_=1;
		FOREVER{
			next16:;
			if(faskeyi(16,1,mode_)) break; mode_=2;
			if(*l(16,20)!=*u(6,1)) break;
			if(*l(16,10)!=*u(2,1)) break;
			if(fldlen(16,15) && *l(16,15)) goto next16;/* geen aankopen */
			if(*u(16,3)<dt_vrk_[0] || *u(16,3)>=dt_vrk_[3]) goto next16;
			for(k=2;k>=0;k--) if(*u(16,3)>=dt_vrk_[k]) break;
			if(k>=0) vrk_per_[k]+=*d(16,30);
		}
		jddate(*u(8,8),&jj,&mm,&dd); mm--;
	}
  else if(fldlen(60,1) && *pu_58_14){
		fl_statistiek_=YES;
    fasinit(60); *l(60,22)=*pu_58_14; *l(60,2)=*u(2,1);mode_=1;
    FOREVER{
      next60:;
      if(faskeyi(60,1,mode_)) break; mode_=2;
      if(*l(60,22)!=*pu_58_14) break;
			if(*l(60,2)!=*u(2,1)) break;
      if(fldlen(60,12) && *l(60,12)) goto next60;/* geen aankopen */
      for(k=mm-2;k<=mm;k++){
				if(k<0) vrk_per_[k-mm+2]+=*f(60,124+12+k);
				else vrk_per_[k-mm+2]+=*f(60,112+k);
      }
    }
  }
	ram2stu(nr_);

  if(fldlen(66,1) && filiaal && filiaal!=99){/* stock op filiaal */
    fasinit(66);*u(66,2)=*pu_6_1;
		if(faskeyi(66,1,0)){
      fasinit(66);*u(66,2)=*pu_6_1;errnum=fasadd(66);
		}
		*f(6,33)=*f(66,11+(filiaal-1)*15); *f(6,36)=*f(66,12+(filiaal-1)*15); *f(6,35)=*f(66,13+(filiaal-1)*15); 
	}

  FOREVER{
redo:
		scrget(2,150);
		z=1;
    scrofld(z++,58,15,-1);
    scrofld(z++,58,16,-1);
		nr_++;scrifld(z++,fm_ou3,&nr_);nr_--;
    scrfld(z++,58,7); if(fldlen(58,62)) scrfld(z++,58,62); else z++;
		if(fldlen(6,102) && *u(6,102)) z+=2; // indien deelverpakking, dan is stock die van moeder
		else{
			scrifld(z++,fm_of6_0,f(6,33));
			qlv_bons_=0; 
			if(fldlen(58,100)){ 
				qlv_bons_=*f(6,33)-*f(58,100);scrifld(z++,fm_of6_0,&qlv_bons_);
        if(*u(58,14) && qlv_bons_) scraddpicto(1,z-1,0,0,2,1,112,0,4,"Toon klanten"); 
			} 
			else z++;
		}
		scrfld(z++,58,20);
		scrfld(z++,58,21);
			if(fldlen(58,100)) scrifld(z++,fm_of6_0,f(58,100)); else z++;
		scrofld(z++,58,22,-1);
		pr_net_=*f(58,23)-*f(58,22); scrifld(z++,fm_of5_3,&pr_net_);

      scrofld(z++,6,36,-1);
		  scrofld(z++,6,35,-1);
		scrfld(z++,58,43);
			if(fl_statistiek_){
				k=mm-2; if(k<0) k=12+k; scrifld(z++,fm_os3,maand_str[k]);
				scrifld(z++,fm_of6_0,&vrk_per_[0]);
			} else z+=2;
		scrofld(z++,58,52,-1);
			if(fl_statistiek_){
				k=mm-1; if(k<0) k=12+k; scrifld(z++,fm_os3,maand_str[k]);
				scrifld(z++,fm_of6_0,&vrk_per_[1]);
			} else z+=2;
		scrofld(z++,58,53,-1);
			if(fl_statistiek_){
				k=mm; if(k<0) k=12+k; scrifld(z++,fm_os3,maand_str[k]);
				scrifld(z++,fm_of6_0,&vrk_per_[2]);
			} else z+=2;
    scrofld(z++,58,35,-1);
    scrofld(z++,58,47,-1);
    key=scrupd(curs,0x03FF);curs=3;
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==106){ram2stu(nr_);break;}
    stu2ram(nr_);  calc(); ram2stu(nr_);
    if(key==5001){
			DisplayBonKlantenWithThisArt();
      goto redo_detail;
		}
    if(key==101 || key==108){
			break;
		}
    if(key==102){
      nr_--; if(nr_<0) nr_++;
      goto redo_detail; // ram2stu(nr_);calc(nr_,YES);
    }
    if(key==103){
      nr_++; if(nr_>=max_line) nr_--;
      goto redo_detail; // ram2stu(nr_);calc(nr_,YES);
    }
  }
}

static DisplayBonKlantenWithThisArt()
{
  int16 j,key,z,d_lin_scr_=19,start_,fnr_;
	uint16 brecs_[200],max_,krec_,rec58_,mode_;
	char buf58_[750];
	float qlv_;

  copy(s(58,1),buf58_,fldlen(58,0)); fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
  copy(s(8,1),buf1000,fldlen(8,0));
  krec_=*u(2,1); 
	 
  rec58_=*u(58,1);
  fasinit(58);*u(58,14)=*u(6,1);mode_=1;
	zero((char *)brecs_,sizeof brecs_); max_=0;
  FOREVER{
    next:;
    if(faskeyi(58,2,mode_)) break; mode_=2;
    if(*u(58,14)!=*u(6,1)) break;
    if(*u(58,1)==rec58_) goto next;
    fasinit(8);*u(8,1)=*u(58,2);fasgeti(8);
#if BACKORDER
    if(*u(8,36) && *u(8,36)!=20 && *u(8,36)!=180) goto next;
#endif
#if STOCK_OP_LOCATIE
		if(*u(8,36)==20){ // stockmutatie
			fnr_=48; if(fldlen(8,36) && *u(8,36)==20) fnr_=3;
  		if(filiaal>0 && filiaal<=10){
				if(*u(8,3)!=filiaal && *u(8,38)!=filiaal)  goto next; // geen van filiaal of naar filiaal
			}
			else{
				if((*u(8,fnr_)>0 && *u(8,fnr_)<=10) && (*u(8,38)>0 && *u(8,38)<=10)) goto next;
			}
		}
		else {
 		  if(filiaal>0 && filiaal<=10){
				if(*u(8,48)!=filiaal)  goto next; // geen van filiaal of naar filiaal
			}
			else{
				if(*u(8,48)>0 && *u(8,48)<=10) goto next;
			}
		}
#endif
		brecs_[max_++]=*u(58,1); if(max_>=200) break;
  }

  scrnum=0;start_=0;
  FOREVER{
    redo:
    scrnum=0;scrget(2,383);z=1;
		scrofld(z++,6,3,-1);
    for(j=start_;j<(start_+d_lin_scr_);j++){
      if(j>=max_) break;
      j++; scrifld(z++,fm_ou3,&j); j--;
			fasinit(58);*u(58,1)=brecs_[j]; fasgeti(58);
			fasinit(8);*u(8,1)=*u(58,2); fasgeti(8);
			fasinit(2);*u(2,1)=*u(8,3); fasgeti(2);
			qlv_=*f(58,31);	if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)!=0 && *s(58,16)!='*') qlv_/=*f(58,63);
#if BACKORDER && STOCK_OP_LOCATIE
      if(fldlen(8,48) && *u(8,36)==20){
				fasinit(2);copy("Mutatie/levering",s(2,3),25);
			}
#endif
			
			scrofld(z++,8,8,-1);
			scrofld(z++,2,3,-1);
			scrifld(z++,fm_of6_2,&qlv_);
    }
    key=scrupd(-1,0x7);
    if(key==101 || key==111) break;
    if(key==102) start_-=d_lin_scr_;
    if(key==103){
      start_+=d_lin_scr_;
      if(start_>(max_-d_lin_scr_)) start_=max_-d_lin_scr_;
    }
    if(start_<0) start_=0;
  }
	endsr:;
  copy(buf58_,s(58,1),fldlen(58,0));
  copy(buf1000,s(8,1),fldlen(8,0));
	fasinit(2); *u(2,1)=krec_; if(*u(2,1)) fasgeti(2);
}


#endif




#if KASINPUT
static fill_58()
{
  int16 g,j=0,k,mode_,beg_pos,n=0,dd_,mm_,jj_,lst_grp_,kortflag_;
  char kas_munt[4],lst_art_[10],buf_[10];
  double pr_;

/* fouten in kortingen kassa (Marc) : korting wordt met R1 gegeven, */
/* zelfde code#, maar groep is meestal 99 */
  sysget(4338,3,kas_munt);
  *s(8,22)='J';tot_voors=0; KM_heffing=0;
  for(k=0;k<50;k++){
    if(fil_pos[k]<0) goto next;
    fasinit(80);*pl_80_1=fil_pos[k];
    mode_=0;n=0;
    FOREVER{
      if(read_rec(mode_)) goto endsr;
      mode_=1;
      if(cmp_str(rec_ele(0),"H1",2)==NO){
				if(j>=max_line-3){fil_pos[k]=-1; goto next;}
				else beg_pos=j;
				n=0;
#if BOEKKASF
				dd_=val(rec_ele(1));
				mm_=val(rec_ele(1)+3);
				jj_=val(rec_ele(1)+6);
				ft_date=datejd(jj_,mm_,dd_); *u(8,8)=ft_date;
				ft_nr=get_num(2); *u(8,2)=ft_nr;
#endif
				ram2stu(j);
				copy("*Bon : ",ps_58_16,7);
				copy(rec_ele(2),ps_58_16+7,ele_len(2));
				copy(" van ",ps_58_16+7+ele_len(2),5);
				copy(rec_ele(1),ps_58_16+12+ele_len(2),ele_len(1));
				if(fldlen(58,27)) *s(58,27)='J';
				stu2ram(j++); zero(lst_art_,sizeof lst_art_);lst_grp_=0;
      }
      kortflag_=NO;
      redo_R1:;
      if(cmp_str(rec_ele(0),"R1",2)==NO){
				if(j>=max_line-3) {fil_pos[k]=-1;init58(beg_pos,NO);goto next;}
				ram2stu(j);
				copy(rec_ele(1),s(58,15),ele_len(1));
				copy(rec_ele(2),ps_58_16,ele_len(2));
			/* volgende lijn : om accenten en graden te verwijderen */
				for(g=0;g<fldlen(58,16);g++){
					if(*(ps_58_16+g)!=144 && *(ps_58_16+g)>127) *(ps_58_16+g)=' ';
				}
				*f(58,20)=get_num(6);
				if(n=find_art(beg_pos+1,j)){
					ram2stu(n);
				}
				if(kortflag_ && n==0){/* anders dubbel aantal in statistiek */
					*ps_58_16='*'; copy(rec_ele(2),ps_58_16+1,ele_len(2));
				}
				*i(58,34)=get_num(3);
				*f(58,24)=get_num(4);
				*f(58,7)+=get_num(5);
	
				*f(58,20)=get_num(6);
				if(cmpstr(s(58,15),lst_art_,fldlen(58,15))==0 && *f(58,20)<0 && *f(58,7)>0){ // kortingslijn (% of EUR) als los artikel zetten owv statistieken
					*s(58,16)='*'; copy(rec_ele(2),ps_58_16+1,ele_len(2));
				}
#if ARTEXIST
					fasinit(6);
					copy(s(58,15),s(6,2),len58_15);
					if(sys4408){
						*u(6,1)=val(s(6,2));
						g=fasgetu(6);
					}
					else{
						g=faskeyu(6,1,0);
					}
					if(g==0){
						copy(s(6,2),s(58,15),len58_15);
			/* omschrijving aanvullen */
						if(cmp_str(ps_6_3,ps_58_16,5)==0) copy(ps_6_3,ps_58_16,len6_3);
						*pu_58_14=*pu_6_1;
						if(len58_25 && fldlen(6,39)) copy(s(6,39),ps_58_25,len58_25);
						if(fldlen(58,63)){*f(58,63)=*f(6,31);if(*f(58,63)==0) *f(58,63)=1;}
						if(fldlen(58,62) && cmpstr("St:",ps_58_16,3)==0) *ps_58_62='S';
						if(fldlen(6,40) && fldlen(58,26)) *l(58,26)=*l(6,40);/* grb_rek checken */
						if(fldlen(58,41) && *i(6,9)!=99  && *s(58,16)!='*'){
							if(fldlen(6,105) && *u(6,105) && *u(6,105)<=*u(8,8)) *f(58,41)=*f(6,18+94);
							else *f(58,41)=*f(6,18);
						}
						*u(58,17)=hash();
					}
#endif
				if(*i(58,34)==99 && *f(58,24)==0){
					*f(58,46)=get_num(6);/* ehprijs leeggoed */
					*f(58,47)+=get_num(7);/* totaal leeggoed */
					if(*f(58,46)==0) *f(58,46)=*f(58,47);
					if(*f(58,46) && *f(58,7)){
						*f(58,49)=(*f(58,47)/ *f(58,46)) / *f(58,7);
					}
					else *f(58,49)=0;
				}
				else {
				  *pd_58_35+=get_num(7);
#if FLAGPWH
					pr_=*pd_58_35; if(*f(58,7)) pr_/=*f(58,7);
					*pf_58_20=valu_cnv("EUR","EUR",pr_,prx_afrond);
#endif
					if(*i(58,34)==99 && (*ps_58_15==' ' || *ps_58_15=='\0' || cmp_str(lst_art_,s(58,15),len58_15)==0)){
						copy(lst_art_,ps_58_15,len58_15);/* lege code naar origineel zetten */
						*i(58,34)=lst_grp_;/* fout in kassa die grp 99 geeft bij korting */
					}
				}
				if(fldlen(58,27)) *s(58,27)='J';
				copy(ps_58_15,lst_art_,len58_15);lst_grp_=*i(58,34);
				if(n) stu2ram(n); else stu2ram(j++);
			}
			kortflag_=NO;
			if(cmp_str(rec_ele(0),"R2",2)==NO){
			/* Korting als gewoon artikel beschouwen */
				zero(buf_,sizeof buf_);copy(rec_ele(1),buf_,ele_len(1));
				if(ele_len(1)==0 || *rec_ele(1)==' ' || cmp_str(lst_art_,buf_,len58_15)==0){
					*(rec_ele(0)+1)='1';kortflag_=YES;goto redo_R1;
				}
				if(n) ram2stu(n); else {j--;ram2stu(j);}
			/*  if(*f(58,7)) *f(58,49)=get_num(5) / *f(58,7);  */
				*f(58,46)=get_num(6);
				*f(58,47)+=get_num(7);
				if(*f(58,46)==0) *f(58,46)=*f(58,47);
				if(*f(58,46) && *f(58,7)){
					*f(58,49)=(*f(58,47)/ *f(58,46)) / *f(58,7);
				}
				else *f(58,49)=0;
				if(n) stu2ram(n); else stu2ram(j++);
      }
      if(cmp_str(rec_ele(0),"T1",2)==NO){
#if !ARTEXIST
				if(get_num(3)){
					if(j>=max_line-2) {fil_pos[k]=-1;init58(beg_pos,NO);goto next;}
					ram2stu(j);
					copy("Leeggoed terug",ps_58_16,15);
					*f(58,46)=-get_num(3);
					*f(58,49)=1;
					*f(58,7)=1;
					if(fldlen(58,27)) *s(58,27)='J';
					stu2ram(j++);
				}
#endif
				tot_voors+=get_num(5);
				if(get_num(6)) *s(8,22)='N';
				goto next;
      }
    }
    next:;
  }
  endsr:;
  if(*s(8,22)!='J') *f(8,21)=tot_voors;
}
#endif
 
#if FLAG244 & BONFILE & !SAMENVOEGEN & !PDA_LGRETOUR & !WEB_ADD
static kil_bon()
{
  int16 change_,mode_;
 
  upd_mode=YES;
  FOREVER{
    ft_init(YES);
    redo:
    if(!get_klt("te schrappen",YES)) break;
    if(!load_bon(NO,0)) goto redo;
    if(!(change_=ok_kil())) goto redo;
#if ARTEXIST && FLAG244 && STOCK244        /* stock aanpassen op bon-niveau */
#if BVI_flag                 /* gekoppeld aan vraag mag gefactureerd worden */
    if(upd_mode){
      copy(s(8,1),sortbuf,fldlen(8,0));
      fasgeti(8);
      if(*s(8,30)!='J') change_=NO;
      copy(sortbuf,s(8,1),fldlen(8,0));
    }
#endif
    if(upd_mode && change_==YES){                /* vorige stock corrigeren */
      fasinit(58);*u(58,2)=*u(8,1); mode_=1;
      FOREVER{
	if(faskeyi(58,1,mode_)) break; mode_=2;
	if(*u(58,2)!=*u(8,1)) break;
	upd_artstock(YES);
      }
    }
#endif
 
    kill();
    fasinfo(8,101);
    fasflush(0);
  }
}
#endif
 
#if ARTEXIST && (AFHAALVERG | LOSVERGOED | PALET_KORTING)
static extra_kort(pos_58,pos_8,pos_6)
int16 pos_58,pos_8,pos_6;
{
  char code_[10];
  uint16 rec_;
 
  zero(s(58,pos_58),s(58,pos_58+3)-s(58,pos_58));
  if(fldlen(6,pos_6) && *s(6,pos_6)){
    if(fldlen(8,pos_8) && *s(8,pos_8)=='J'){
      copy(s(6,pos_6),code_,fldlen(6,pos_6));
      rec_=*pu_6_1;fasinit(6);copy(code_,s(6,2),fldlen(6,pos_6));
      if(code_[0]){
	if(search(6,2)==0){
	  *u(58,pos_58+2)=*pu_6_1;
	  calc_prx=*f(6,PrNrs[prxnr]);
/* calc_prx=valu_cnv(def_munt,ft_munt,(double)*f(6,PrNrs[prxnr),prx_afrond); */
	  get_prx(YES);
	  if(calc_kort && nokort==NO) *f(58,pos_58)=-(calc_prx * (100.-calc_kort)/100.);
	  else *f(58,pos_58)=-calc_prx;
	}
      }
      *pu_6_1=rec_;fasgeti(6);
    }
    else {*u(58,pos_58+2)=0;*f(58,pos_58)=0;}
  }
}
#endif
 
#if ARTEXIST && EXTEND_KORT
static extra_ekort()
{
  int16 k;
  char code_[10];
  uint16 rec_;
 
  for(k=0;k<10;k++){
		if(fldlen(58,102+k*3)==0) continue;
    zero(s(58,102+k*3),s(58,105+k*3)-s(58,102+k*3));
    if(*s(6,90+k)){/* 53+54 als 1 string genomen */
      copy(s(6,90+k),code_,fldlen(6,90+k));
      rec_=*pu_6_1;fasinit(6);copy(code_,s(6,2),fldlen(6,90+k));
      if(search(6,2)==0){
				*u(58,104+k*3)=*pu_6_1;
				calc_prx=*f(6,PrNrs[prxnr]);
				get_prx(YES);
				if(calc_kort && nokort==NO) *f(58,102+k*3)=-(calc_prx * (100.-calc_kort)/100.);
				else *f(58,102+k*3)=-calc_prx;
      }
      *pu_6_1=rec_;fasgeti(6);
    }
    else {*u(58,104+k*3)=0;*f(58,102+k*3)=0;}
  }
}
#endif



 
static ask_lev_adr()
{
  int16 curs=1,k,key,z,klt_rood_;

#if FLAG248
  if(stat_klt==0){
    copy(ps_2_3,nm_dehr,len2_3);stat_klt=*pu_2_1;
    copy(ps_2_3,oldnm,len2_3);
  }
  else{
    copy(s(2,1),sortbuf,fldlen(2,0));
    fasinit(2);*pu_2_1=stat_klt;fasgeti(2);
    copy(ps_2_3,nm_dehr,len2_3);
    copy(ps_2_3,oldnm,len2_3);
    stat_klt=*pu_2_1;copy(sortbuf,s(2,1),fldlen(2,0));
  }
#endif

#if BOEKALLO
  klt_saldo=getsaldo((uint16)(*pu_2_1+(uint16)30000));
#endif
 
  FOREVER{
    redo:;
    scrget(2,25);z=1;
    scrfld(z++,25,1);
    if(fldlen(2,42) && *s(2,42)=='J'){ // feestklant cfr GRS voor parlay
      for(k=3;k<7;k++) scrfld(z++,8,11+k);
    }
    else {
		klt_rood_=NO;	if(*(s(2,3)+fldlen(2,3)-1)=='!') klt_rood_=YES;

		for(k=3;k<7;k++) {
			scrfld(z++,2,k);
			if(klt_rood_) scrchat(z-1,0xB); else scrchat(z-1,0xFF);
		}

    }
#if USE_2ADR || ADDLEVNAAM
		if(fldlen(2,42) && *s(2,42)=='J') z+=4; // feestklant : lev.adres wordt eerst al getoond
    else for(k=1;k<5;k++) scrfld(z++,8,13+k);
#endif
#if FLAG248
    scrifld(10,fm_us40,nm_dehr);
#endif
#if BOEKALLO
    scrifld(11,fm_os3,ft_munt);
    scrifld(12,fm_obd,&klt_saldo); if(FlagVervallenFacturen) scrchat(12,0xB); else scrchat(12,0xFF);
#if FLAG248
    scrifld(13,fm_us20,opm_bkh);
#endif
#endif
#if FT_HERAFDRUK
    curs=-1;/* enkel bekijken */
#endif
    key=scrupd(curs,0x02A0);
    if(key==106) return YES;
#if FLAG248
    if(nm_dehr[0]){
      if(cmpstr(nm_dehr,oldnm,len2_3)){
	copy(s(2,1),sortbuf,fldlen(2,0));
	fasinit(2);copy(nm_dehr,ps_2_3,len2_3);
	if(search(2,0)){
	  curs=10;copy(sortbuf,s(2,1),fldlen(2,0));
	  goto redo;
	}
	copy(ps_2_3,nm_dehr,len2_3);
	stat_klt=*pu_2_1;copy(sortbuf,s(2,1),fldlen(2,0));
      }
    }
    else{stat_klt=0;zero(nm_dehr,sizeof nm_dehr);}
    copy(nm_dehr,oldnm,len2_3);
#endif
#if USE_2ADR || ADDLEVNAAM
    if(key==110){
      copy(s(2,1),sortbuf,fldlen(2,0));
      fasinit(2);copy(s(8,14),ps_2_3,len2_3);
      if(search(2,0)){
	curs=6;copy(sortbuf,s(2,1),fldlen(2,0));
	goto redo;
      }
      for(k=0;k<4;k++) copy(s(2,3+k),s(8,14+k),fldlen(8,14+k));
      copy(sortbuf,s(2,1),fldlen(2,0));
    }
#endif
    if(key==108) break;
  }
  return NO;
}

#if BOEKALLO
static double getsaldo(searcnr)/* lev or klt only */
uint16 searcnr;
{
  int16 end_,ft_vervallen_;
  double saldo_=0;
  uint16 first, r_yy,r_jr,r_nr;
  double ebd_;

  fasinit(4); *u(4,5)=searcnr; FlagVervallenFacturen=NO; TotaalVervallenFacturen=0;

  first=YES; end_=NO; ft_vervallen_=NO; ebd_=0;
  FOREVER{
    if(faskeyi(4,4,2)) end_=YES;
    if(!end_ && *u(4,5)!=searcnr) end_=YES;
    if(!end_ && first){
      r_yy=*s(4,8); r_jr=*s(4,9); r_nr=*u(4,10);
      first=NO;
    }
    if(end_ || *s(4,8)!=r_yy || r_jr!=*s(4,9) || r_nr!=*u(4,10)){
			if(!is_nul(ebd_) && ebd_>0 && ft_vervallen_) {FlagVervallenFacturen=YES; TotaalVervallenFacturen+=ebd_;}
      saldo_+=ebd_;
      ft_vervallen_=0;ebd_=0;
      r_yy=*s(4,8); r_jr=*s(4,9); r_nr=*u(4,10);
      if(end_) break;
    }
#if FLAGDDB  // Periode staat standaard op contant, willen pas melding na 50 dagen
    if((*u(4,21)+50)<=*u(25,2)) ft_vervallen_=YES;
#else
    if(*u(4,21)<=*u(25,2)) ft_vervallen_=YES;
#endif
    ebd_+=*d(4,32);
  }
	if(TotaalVervallenFacturen>saldo_) TotaalVervallenFacturen=saldo_;
	if(saldo_<0) {FlagVervallenFacturen=NO;TotaalVervallenFacturen=0;}
	return (double) saldo_;
}
#endif


static DispInfoAlarm(stu_)
int16 stu_;
{
  int16 z,k,key,mode_,used_=NO;

  fasinit(22);	*u(22,2)=stu_;*u(22,3)=*u(stu_,1); mode_=1; k=0;
  FOREVER{
    next:;
    if(faskeyi(22,1,mode_)) break; mode_=2;
    if(*u(22,2)!=stu_) break;
    if(*u(22,3)!=*u(stu_,1)) break;
		if(*s(22,7)!='J') goto next;
		if(*u(22,4)>*u(25,2)) goto next;
		if(used_==NO){
			scrget(1,274); z=1;scraddpicto(1,0,35,0,10,5,605,0,0,"Alarm"); 
			scrofld(z++,stu_,3,-1);
			scrofld(z++,22,4,-1);
			scrofld(z++,22,10,-1);
			used_=YES;
		}
		else scrofld(z++,22,10,-1);
		if(z>7) break;
	}
	if(used_){
		FOREVER{
		  key=scrupd(-1,0x80);
		  if(key==108) break;
		}
  }
}


static DisplayMemo(stu_)
int16 stu_;
{
  int16 curs=2,dcurs_;
  int16 z,k,key;
	int16 only_dsp=NO; // hier niet van toepassing 
					
  FOREVER{
    redo:;
    scrget(2,122); z=1;
    scrofld(z++,stu_,3,-1);
		if(stu_==1){
			for(k=125;k<128;k++) scrfld(z++,1,k);
		}
		else{
      for(k=5;k<10;k++) scrfld(z++,62,k);
		}
    dcurs_=curs; if(only_dsp) dcurs_=-1;
    key=scrupd(dcurs_,0x80);
    if(key==15 && only_dsp){only_dsp=NO;goto redo;}
    if(key==108) break;
  }
}


#if !KASINPUT && ARTEXIST && FLAGABT // palletten berekenen en aanrekenen
static PalletAdd()
{
  int16 j,k;
  uint16 rec_;
	char palletcodes[10][5];
  float palletaantal[10];


	zero(palletcodes,sizeof palletcodes); zero((char *)&palletaantal[0],sizeof palletaantal);

	for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*i(58,34)!=99 && *u(58,14) && *s(58,16)!='*'){
			fasinit(6);*u(6,1)=*u(58,14);fasgeti(6);
			if(*s(6,82) && *f(6,83)){
				for(j=0;j<10;j++)	if(palletcodes[j][0]=='\0' || cmpstr(s(6,82),palletcodes[j],5)==0) break;
				if(j<10){
					copy(s(6,82),palletcodes[j],5);
					if(*s(58,62)=='P') palletaantal[j]+=*f(58,7);
					else	palletaantal[j]+=*f(58,7)/ *f(6,83);
				}
			}
		}
	}
  for(j=max_line-1;j>=0;j--) {ram2stu(j);if(test_line()) break;} j++; // op einde zetten 
  for(k=0;k<10;k++){
		if(palletcodes[k][0]=='\0') break;
		if(j>=max_line) break;
		if(palletaantal[k]==0) continue;
		ram2stu(j);
    if(*s(8,26)=='J') *pf_58_24=0;
		*f(58,7)=palletaantal[k];
		fasinit(6);copy(palletcodes[k],s(6,2),5);
		if(faskeyi(6,1,0)){ // niet gevonden
			copy(palletcodes[k],s(6,2),5); *f(58,7)=palletaantal[k];
			stu2ram(j);
		}
		else{
			copy(s(6,2),ps_58_15,len58_15);
			*pu_58_14=*pu_6_1;
			copy(s(6,3),ps_58_16,fldlen(58,16));
			stu2ram(j);
	  	Fill58FromNewArtikel(j);
		}
		j++;
	}
  calc();
}
#endif



#if !KASINPUT
static leegadd(mode_)/* NO=leeggoed gelijk, YES=leeggoed apart */
int16 mode_;
{
  int16 j,k,t_nr_;
  uint16 rec_;
  float hoev_,vp_;

	if(mode_==NO){
		for(k=0;k<max_line;k++){ // leeggoedlijnen deleten 
			ram2stu(k);
			if(*i(58,34)==99 && *d(58,35)==0){
				rec_=*pu_58_1;
				init58(k,YES);
				ram2stu(k);
				*pu_58_1=rec_;
				stu2ram(k);			
			}
		}
	}
	 
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*i(58,34)!=99 && *u(58,48)){
      rec_=*u(58,48);hoev_=*f(58,49)* *f(58,7);
			if(fldlen(58,8) && fldlen(58,62)){
        if(*ps_58_62=='P' && *f(58,8)) hoev_*=*f(58,8);
	    }
      for(j=0;j<max_line;j++){
				ram2stu(j);if(*pu_58_14==rec_) break;
      }
      if(j==max_line){
				for(j=max_line-1;j>=0;j--) {ram2stu(j);if(test_line()) break;}
				j++;ram2stu(j);
				fasinit(6);*pu_6_1=rec_;fasgeti(6);
				copy(s(6,2),ps_58_15,len58_15);
				*pu_58_14=*pu_6_1;
				t_nr_=taal_nr; if(*s(6,3+t_nr_)=='\0') t_nr_=0;
				copy(s(6,3+t_nr_),ps_58_16,fldlen(58,16));
				*pf_58_24=*f(6,28); if(*s(8,26)=='J') *pf_58_24=0;
				if(fldlen(58,12)) copy(s(6,10),s(58,12),fldlen(58,12));
				if(len58_25 && fldlen(6,39)) copy(s(6,39),ps_58_25,len58_25);
				if(fldlen(6,40) && fldlen(58,26)) *l(58,26)=*l(6,40);/* grb_rek checken ... jvgjvg*/
				*i(58,34)=*i(6,9);
				if(fldlen(6,38) && fldlen(58,13)) *f(58,13)=*f(6,38);
				*f(58,38)=*f(6,30);
			/* *f(58,38)=valu_cnv(def_munt,ft_munt,(double)*f(6,30),prx_afrond); */
				vp_=*f(6,PrNrs[prxnr]);
			/*    vp_=valu_cnv(def_munt,ft_munt,(double)vp_,prx_afrond); */
				copy(s(6,76),s(58,44),fldlen(58,44));
#if TRACEERDATA
				copy(s(6,77),s(58,135),fldlen(58,135));
#endif
	      if(fldlen(58,101) && fldlen(6,29)) copy(s(6,29),s(58,101),fldlen(58,101));
				*u(58,48)=*pu_58_14;
				*f(58,46)=vp_;*pf_58_20=vp_;
				*f(58,49)=1;
				*u(52,1)=*i(6,9);
				if(fasgeti(52)==0){
					if(fldlen(52,21) && *s(52,21)=='N'){
						*pf_58_21=0;*f(58,43)=0;
					}
				}
#if ARTEXIST
				*u(58,17)=hash();
#endif
      }
      if(mode_){
				*f(58,7)=*f(58,7)+hoev_;
				stu2ram(j);
				ram2stu(k);
				zero(s(58,46),s(58,50)-s(58,46));/* leeggoed op artikel wissen */
				stu2ram(k);
      }
      else{
				*f(58,7)=*f(58,7)-hoev_;
				stu2ram(j);
      }
    }
  }
  calc();
  if(mode_!=NO) lgadded=YES;
}
#endif

static ins_lin(nr_)
int16 nr_;
{
  int16 j;
						
  ram2stu(max_line-1);
  if(test_line()) return NO;/* geen plaats voor insert */
  for(j=max_line-1;j>nr_;j--){
    ram2stu(j-1);stu2ram(j);
  }
  init58(nr_,YES);
  return YES;
}

#if KASINPUT || KAS2FACT || KAS2BON
static ask_in_dt(ptxt,ftmode_)
char *ptxt;
uint16 ftmode_;
{
  int16 z,j,k,key,curs=3,type_,len_,fn_mast_,fn_kassa_;
  uint16 dt_last,allow_samenvoegen;
  char str_[50],def_file_[32],buf_[5001],nm_fil[10];

 
	inq_filiaal=0;zero(nm_fil,sizeof nm_fil);
  if(add_ftvk=='\0') add_ftvk='N';
#if KAS2GROOTH/* ALLE verkoop van kleinhandel */
#if !FLAGJAN  // niet bij JAN: facturen op kassa gaan direct naar groothandel
  add_ftvk='J';
#endif
#endif
	
	if(ftmode_){
		sysget(4572,32,def_file_);
		add_ftvk='N'; if(def_file_[0]) allow_samenvoegen=YES; else allow_samenvoegen=NO;j=0;
  	for(k=0;k<10;k++) {
			if(allow_samenvoegen==NO) break;
			if(nm_kassa[k][0]){
				j++;
				if(sys4400 & 0x02) copy("kasfac.dat",str_,15);
				else{
					copy("kassa-00",str_,8);j=k+1;stcli_d(&str_[6],(long)j,2,0);
					str_[8]=0x5C;copy("kasfac.dat",&str_[9],11);
				}
				mk_name(3936,str_);
				if(cmpstrU(filnam,def_file_,20)==0){allow_samenvoegen=NO;break;}
			}
		}
		if(allow_samenvoegen && j<=1) allow_samenvoegen=NO;
	}
#if BOEKKASF
	allow_samenvoegen=NO;
#endif
  inq_kassa=0;if(max_kassa==1) inq_kassa=1;
								
  if(dt_bon_beg==0) dt_bon_beg=*u(25,2); if(dt_bon_end==0) dt_bon_end=dt_bon_beg;
  FOREVER{
    redo:;
    if(ftmode_) scrget(2,355); else scrget(2,76);z=1;
    scrifld(z++,fm_os38,ptxt);
    scrfld(z++,25,1);
    scrifld(z++,fm_udat,&dt_bon_beg);scrifld(z++,fm_udat,&dt_bon_end);
    scrifld(z++,fm_uu2,&inq_kassa);
		if(ftmode_){
			if(def_file_[0]){
				fasopen(def_file_,102);/* eerste call voor dir */
				fasinfo(80,204);/* ophalen antwoord van dir */
				if(*s(80,1)){
					fasinit(80);fasinfo(80,205);/* get date  */
					scrifld(z++,fm_os20,s(80,1));
				} else z++;
			} else z++;
			if(allow_samenvoegen)	scraddpicto(1,0,75,5,4,2,34,0,4,"Samenvoegen factuurgegevens"); 
			for(k=0;k<10;k++) {
				if(nm_kassa[k][0]){
					scrifld(z++,fm_os6,&nm_kassa[k][0]);
					fasclos(-2);fasinit(80);
					if(sys4400 & 0x02) copy("kasfac.dat",str_,15);
					else{
						copy("kassa-00",str_,8);j=k+1;stcli_d(&str_[6],(long)j,2,0);
						str_[8]=0x5C;copy("kasfac.dat",&str_[9],11);
					}
					mk_name(3936,str_);
					fasopen(filnam,102);/* eerste call voor dir */
					fasinfo(80,204);/* ophalen antwoord van dir */
					if(*s(80,1)){
						fasinit(80);fasinfo(80,205);/* get date  */
						scrifld(z++,fm_os20,s(80,1));
					} else z++;
				} else z+=2;
      }

		}
		else{
			if(fldlen(66,11)){scrifld(-z,fm_uu2,&inq_filiaal);z++; scrifld(z++,fm_os6,nm_fil);}
		  else z+=2;
			if(ft_off>0) scrifld(z++,fm_u_JN,&add_ftvk);
			else streepje(z++);
			z++;
			for(k=0;k<5;k++) {
				scrifld(z++,fm_os6,&nm_kassa[k][0]);
				scrifld(z++,fm_odat,&dt_kvk[k]);
				scrifld(z++,fm_os6,&nm_kassa[k+5][0]);
				scrifld(z++,fm_odat,&dt_kvk[k+5]);
			}
		}
    key=scrupd(curs,0x481);curs=3;
		if ((key/0x100)==1) key=(key&0xFF)+5000;

		if(key==5001){ // factuurbestanden samenvoegen 
			if( (fn_mast_= dopen(def_file_, O_RDONLY|O_BINARY )) == -1 ){// indien niet bestaand, dan creeren
				if((fn_mast_= dopen(def_file_, O_CREAT|O_BINARY )) == -1 ){errnum=1;goto redo;}
			}
			dclose(fn_mast_);
	    if( (fn_mast_= dopen(def_file_, O_WRONLY|O_BINARY )) == -1 ){errnum=1;goto redo;}
			for(k=0;k<10;k++) {
				if(nm_kassa[k][0]){
					if(sys4400 & 0x02) copy("kasfac.dat",str_,15);
					else{
						copy("kassa-00",str_,8);j=k+1;stcli_d(&str_[6],(long)j,2,0);
						str_[8]=0x5C;copy("kasfac.dat",&str_[9],11);
					}
					mk_name(3936,str_);
					if( (fn_kassa_= dopen(filnam, O_RDONLY|O_BINARY )) == -1 )continue;
					FOREVER{
				  	len_=dread(fn_kassa_,buf_,5000);
			  		if(len_>0) j=dwrite(fn_mast_,buf_,len_);
			  		if(len_<5000){dclose(fn_kassa_); break;}
					}
				}
			}
			dclose(fn_mast_);
			goto redo; 
		}
		
    if(key==111) ovlexit(-1);
    if(key==101) return YES;
    if(dt_bon_end==0 || dt_bon_end<dt_bon_beg){curs=4;errnum=38;goto redo;}
		if(ftmode_ && allow_samenvoegen==NO && inq_kassa==0){curs=5; errnum=38;goto redo;}
    if(inq_kassa && (fldlen(91,11+(inq_kassa-1)*5)==0 || nm_kassa[inq_kassa-1][0]=='\0') ){
      curs=5;errnum=34;goto redo;
    }
    if(inq_filiaal<0 || (inq_filiaal>10 && inq_filiaal!=99)) {zero(nm_fil,sizeof nm_fil);curs=5; errnum=34;goto redo;}
		if(inq_filiaal && inq_filiaal<=10){
			if(fldlen(66,11+(inq_filiaal-1)*15)==0) {errnum=34;curs=5; goto redo;}
			copy(nm_loc[inq_filiaal-1],nm_fil,6);
		}
		else if(inq_filiaal==99) copy("DEPOT",nm_fil,6);
		else zero(nm_fil,sizeof nm_fil);
    if(key==18){curs=fldcurs+1;goto redo;}
#if BOEK_LOCATIE/* aparte GRB per locatie */
    if(inq_kassa==0) {curs=5; errnum=38; goto redo;}
    sysget(3598,6,b3598);
    if(loc_nr[inq_kassa-1]>=1 && loc_nr[inq_kassa-1]<=10){
      for(k=0;k<6;k++) if(b3598[k]=='\0') break;
      if(k>0) b3598[k-1]+=loc_nr[inq_kassa-1];
    }
#endif
#if BOEKKASF
    if(inq_kassa==0) {curs=5; errnum=38; goto redo;}
    if(dt_bon_end<=last_arc || dt_bon_end<=MinBkhDatum){curs=4;errnum=37;goto redo;}
    sysget(2725,2,&journl);
    journl+=inq_kassa-1;
    for(k=0;k<80;k++){
      sysget(10240+k*80,2,&last_vf);
      sysget(10242+k*80,2,&type_);
      if(type_==2 && last_vf==journl)break;
    }
    if(k==80){curs=5; errnum=4;goto redo;}
    last_vfa=10260+k*80;
    sysget(last_vfa,2,&last_vf);
#endif
    if(key==108) break;
  }
  return NO;
}
#endif


static cmpstrU(p1,p2,len)
char *p1,*p2;
int16 len;
{
  char b1,b2;
					
  while(len--){
    b1=*p1++;b2=*p2++;
    if(b1>='a' && b1<='z') b1=b1-'a'+'A';
    if(b2>='a' && b2<='z') b2=b2-'a'+'A';
    if(b1!=b2)return 1;
  }
  return 0;
}




static mk_name(adr_pref,ps)
uint16 adr_pref;
char *ps;
{
  char *pd;
				
  zero(filnam,sizeof filnam); pd=filnam;
  sysget(adr_pref,25,pd);
  while(*pd) pd++;
  while(*ps!='\0') *pd++=*ps++;
  *pd='\0';
}

#if (FLAG244 & BONFILE & !SAMENVOEGEN & !PDA_LGRETOUR) | FLAG252
static disp_toer(mode_)
int16 mode_;/* 0 = aanstippen, 1 = breaken */
{
  int16 g,j,k,n,curs,key,z,start_,h_len,d_lin_scr=17,curspos_;
  uint16 val_,h_val,ram_recl,max_klt_;
  char *pdum,dumm_[10],*pvar,*ps_;
 
  pdum=&dumm_[0];
  ram_recl=s(2,4)-s(2,1)+fldlen(2,8)+2;/* + 2 bytes hash */
  h_len=s(2,4)-s(2,1);
  max_klt_=DIM_TKLT; if(max_klt_*ram_recl>ram_size) max_klt_=ram_size/ram_recl;
  zeroL(ram,ram_size); curs=-1;
  for(k=0;k<max_klt_;k++){
    if(toer_klt[k]<30000 && curs==-1) curs=k;
  }
  if(curs==-1) {start_=0;curs=3;}
  else{
    start_=curs/d_lin_scr;curs=(curs-start_)*3+3;
  }

  for(k=0;k<d_lin_scr;k++){
    fasinit(2);*pu_2_1=toer_klt[start_+k];
    if(*pu_2_1>30000) *pu_2_1-=30000;
    fasgeti(2);
    n=h_len;ps_=s(2,1);h_val=0;
    while(n--) h_val=h_val*3+*(ps_++);
    copy(s(2,1),ram+(k*ram_recl),h_len);
    copy(s(2,8),ram+(k*ram_recl)+h_len,fldlen(2,8));
    copy(&h_val,ram+(k*ram_recl)+ram_recl-2,2);
  }

  scrnum=0;
  FOREVER{
    redo_t:
    scrget(2,135);z=1;
    scrofld(z++,63,3,-1);
    for(j=start_;j<(start_+d_lin_scr);j++){
      j++; scrifld(z,fm_ou3,&j); j--;
      if(toer_klt[j]>30000) scrchat(z++,0x08);
      else if(toer_qbons[j]>1) scrchat(z++,0x09);
			else scrchat(z++,0xFF);
      if(fieldspc(2,3,&pdum,fmt)>0){
				pvar=ram+((j-start_)*ram_recl + (s(2,3)-s(2,1)));
				scrifld(z,fmt,pvar);
				if(toer_qbons[j]>1) scrchat(z++,0x09);
			  else scrchat(z++,0xFF);
      }
      if(fieldspc(2,8,&pdum,fmt)>0){
				fmt[1]=0x88;/* output */
				pvar=ram+((j-start_)*ram_recl + h_len);
				scrifld(z++,fmt,pvar);
      }
    }
    key=scrupd(curs,0xFF);curs=1;curspos_=fldcurs;
    if(key==106 || key==101) return YES;
    if(key==104){/* insert */
      j=(curspos_-2)/3;
      for(k=max_klt_-2;k>=j+start_;k--){
				if(k<d_lin_scr+start_-1){
					copy(ram+((k-start_)*ram_recl),ram+((k-start_+1)*ram_recl),ram_recl);
				}
				toer_klt[k+1]=toer_klt[k];toer_qbons[k+1]=toer_qbons[k];
      }
      zero(ram+ram_recl*j,ram_recl);
      toer_klt[j+start_]=0;toer_qbons[j+start_]=0;
      curs=curspos_;
    }
    if(key==105){/* delete */
      j=(curspos_-2)/3;
      for(k=j+start_;k<max_klt_-1;k++){
				if(k<d_lin_scr+start_-1){
					copy(ram+((k-start_+1)*ram_recl),ram+((k-start_)*ram_recl),ram_recl);
				}
				toer_klt[k]=toer_klt[k+1];toer_qbons[k]=toer_qbons[k+1];
      }
      zero(ram+ram_recl*(d_lin_scr-1),ram_recl);
      toer_klt[max_klt_-1]=0;toer_qbons[max_klt_-1]=0;
      if((start_+d_lin_scr-1)<max_klt_){
				if(toer_klt[start_+d_lin_scr-1]>0){
					fasinit(2);*pu_2_1=toer_klt[start_+d_lin_scr-1];
					if(*pu_2_1>30000) *pu_2_1-=30000;
					fasgeti(2);
					n=h_len;ps_=s(2,1);h_val=0;
					while(n--) h_val=h_val*3+*(ps_++);
					copy(s(2,1),ram+((d_lin_scr-1)*ram_recl),h_len);
					copy(s(2,8),ram+((d_lin_scr-1)*ram_recl)+h_len,fldlen(2,8));
					copy(&h_val,ram+((d_lin_scr-1)*ram_recl)+ram_recl-2,2);
				}
				else zero(ram+(d_lin_scr-1)*ram_recl,ram_recl);
      }
      curs=curspos_;
    }
    for(k=start_;k<(start_+d_lin_scr);k++){
      copy(ram+((k-start_)*ram_recl),s(2,1),h_len);
      copy(ram+((k-start_)*ram_recl)+h_len,s(2,8),fldlen(2,8));
      copy(ram+((k-start_)*ram_recl)+ram_recl-2,&h_val,2);
      n=h_len;ps_=s(2,1);val_=0;
      while(n--) val_=val_*3+*(ps_++);
      if(*ps_2_3 && h_val!=val_){
				if(search(2,0)){
					errnum=39;curs=2+(k-start_)*3;goto redo_t;
				}
				toer_klt[k]=*pu_2_1;
				n=h_len;ps_=s(2,1);h_val=0;
				while(n--) h_val=h_val*3+*(ps_++);
						}
						else if(*ps_2_3=='\0'){
				fasinit(2);h_val=0;
				toer_klt[k]=*pu_2_1;
      }
      copy(s(2,1),ram+((k-start_)*ram_recl),h_len);
      copy(s(2,8),ram+((k-start_)*ram_recl)+h_len,fldlen(2,8));
      copy(&h_val,ram+((k-start_)*ram_recl)+ram_recl-2,2);
    }
    if(key==108){
      if(mode_==0){
				j=(curspos_-2)/3;
				copy(ram+(j*ram_recl),s(2,1),ram_recl-2);
				copy(ram+(j*ram_recl)+ram_recl-2,&h_val,2);
				if(fasgeti(2)==0){
					toer_klt[j+start_]=*pu_2_1+30000;
					break;
				}
      }
      else break;
    }
    if(key==102) {start_-=d_lin_scr; if(start_<0) start_=0;}
    if(key==103) start_+=d_lin_scr;
    if(start_>(max_klt_-d_lin_scr)) start_=max_klt_-d_lin_scr;
    for(k=0;k<d_lin_scr;k++){
      fasinit(2);*pu_2_1=toer_klt[start_+k];
      if(*pu_2_1>30000) *pu_2_1-=30000;
      fasgeti(2);
      n=h_len;ps_=s(2,1);h_val=0;
      while(n--) h_val=h_val*3+*(ps_++);
      copy(s(2,1),ram+(k*ram_recl),h_len);
      copy(s(2,8),ram+(k*ram_recl)+h_len,fldlen(2,8));
      copy(&h_val,ram+(k*ram_recl)+ram_recl-2,2);
    }
    j=0;
    for(k=0;k<d_lin_scr;k++){if(toer_klt[k]<30000) {j=k;break;}}
    if(key!=104 && key!=105) curs=2+j*3;
  }
  return NO;
}
#endif

#if ARTEXIST && FICHEEXEC/*  || STOCK244) */
static art_stat()
{
  int16 k,j,g;
  float belastbf,echt_gel_,accijn_=0,f_;

	fasunlck(-2);
	
  if(fldlen(2,51) && *u(2,51) && sys3918) stat_klt=*u(2,51);
  else if(stat_klt==0) stat_klt=*pu_2_1;

  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*ps_58_16!='*' && *pu_58_14){
      *pu_6_1=*pu_58_14;
      if(fasgetu(6)==0){
				if(*i(58,34)!=99){
					belastbf=*pd_58_35;
				}
				else belastbf=*f(58,47);
			/*  belastbf=valu_cnv(ft_munt,def_munt,(double)belastbf,prx_afrond); */
				f_=*pf_58_31;
				if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) f_/=*f(58,63);
				echt_gel_=-f_;
#if FICHEEXEC | STOCK244
#if PAU_flag
				if(*s(2,25)=='1'){/* factuur aan groothandel */
					stu_add(6,32,&f_); goto upd_6;/* geen art.stat */
				}
				else {
					if(sys2696==1) stu_add(6,32,&echt_gel_);/* factuur GRH aan horeca */
				}
#endif
				art_stadd(&echt_gel_,&belastbf,YES);
				upd_6:;
#if !NO_ART_UPD && !KAS2JMCFACTUUR // stock via kassa aangepast
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				fasupd(6);
#endif
				*pu_6_1=*pu_58_14; fasgeti(6);
#endif
      }

      if(fldlen(58,44) && fldlen(9,27)){
				if(*s(58,44)=='J'){
#ifdef NIJ_flag
				  if(*ps_58_62=='S') goto no_omzet;/* geen omzet voor flessen */
#endif
					fasinit(9);
					*u(9,2)=stat_klt;
					*u(9,3)=*pu_58_14;;
					if(faskeyi(9,1,0)) fasadd(9);
					echt_gel_=-echt_gel_;
					if(*s(58,44)=='J'){
						j=0;if(echt_gel_<0) j+=8;
						accijn_=*f(58,38)*echt_gel_;
			/*  accijn_=valu_cnv(ft_munt,def_munt,(double)accijn_,prx_afrond); */
						belastbf-=accijn_;
						for(g=0;g<=4;g+=4){
							stu_add(9,27+j+g,&echt_gel_);
							stu_add(9,28+j+g,&belastbf);
							if(fldlen(9,29+j+g)) stu_add(9,29+j+g,&accijn_);
							f_=*f(58,52);
			/*   f_=valu_cnv(ft_munt,def_munt,(double)*f(58,52),prx_afrond); */
							stu_add(9,47+j+g,&f_);
							f_=*f(58,53);
			/*   f_=valu_cnv(ft_munt,def_munt,(double)*f(58,53),prx_afrond); */
							stu_add(9,48+j+g,&f_);
						}
					}
					if(fldlen(9,43) && *s(58,44)=='J'){
						stu_add(9,43,&echt_gel_);
					}
					fasupd(9);
					no_omzet:;
				}
      }
      if(fldlen(58,48) && *u(58,48) && *pu_58_14!=*u(58,48)){
				fasinit(6);*pu_6_1=*u(58,48);fasgeti(6);
				echt_gel_=-(*f(58,49) * *pf_58_31);
#if FICHEEXEC | STOCK244
				f_=*f(58,47);
/*      f_=valu_cnv(ft_munt,def_munt,(double)*f(58,47),prx_afrond); */

#if PAU_flag
				if(*s(2,25)=='1'){                       /* factuur aan groothandel */
					stu_add(6,32,&f_); goto upd_6;                   /* geen art.stat */
				}
				else{
					if(sys2696==1) stu_add(6,32,&echt_gel_);/* factuur GRH aan horeca */
				}
#endif
				art_stadd(&echt_gel_,&f_,NO);

#if !NO_ART_UPD && !KAS2JMCFACTUUR // stock via kassa aangepast
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				if(sys2727==0) fasupd(6);
#endif
				fasinit(6);*pu_6_1=*u(58,48);fasgeti(6);
#endif

				if(fldlen(58,44) && fldlen(6,76) && fldlen(9,27)){
					if(*s(6,76)=='J'){
						fasinit(9);
						*u(9,2)=stat_klt;
						*u(9,3)=*pu_6_1;
						if(faskeyi(9,1,0)) fasadd(9);
						echt_gel_=*f(58,49) * *pf_58_31;
						if(*s(6,76)=='J'){
							j=0;if(echt_gel_<0) j+=8;
							belastbf=*f(58,47);
			/*  belastbf=valu_cnv(ft_munt,def_munt,(double)*f(58,47),prx_afrond); */
							for(g=0;g<=4;g+=4){
								stu_add(9,27+j+g,&echt_gel_);
								stu_add(9,28+j+g,&belastbf);
							}
						}
						if(fldlen(9,43) && *s(6,76)=='J'){
							stu_add(9,43,&echt_gel_);
						}
						fasupd(9);
					}
				}
      }

    }
  }
}
#endif

#if FICHEEXEC | STOCK244
static art_stadd(qlv_,bedrag_,echt_artikel_)
float *qlv_,*bedrag_;
int16 echt_artikel_;
{/* STOCK enkel aanpassen van echte artikels en niet van gekoppeld leeggoed */
  int16 k,g,clip_=NO,muteer_=NO;
  float q_,stockqlv_;
	uint16 arec_;

	arec_=*u(6,1);
	if(fldlen(6,102) && *u(6,102)){// is dit een clip?
		stockqlv_=*f(6,31);
		*u(6,1)=*u(6,102);fasgeti(6);
#if FLAGSAS | FLAGGRS | FLAGALB | FLAGAST
		clip_=YES; // gekoppeld, altijd moederfiche bijwerken
#else
		if(*f(6,31)!=stockqlv_) clip_=YES;
#endif
		fasinit(6);*u(6,1)=arec_;fasgeti(6);
	}		
	stockqlv_=1.;
	if(clip_){// indien deelverpakking, dan op hoofdartikel bijhouden 
		if(*f(6,31)>1) stockqlv_=*f(6,31);
		*u(6,1)=*u(6,102);
		if(fasgeti(6)){*u(6,1)=arec_;fasgeti(6);stockqlv_=1.;}
		else{
	    if(*f(6,31)) stockqlv_/=*f(6,31); else stockqlv_=1;
		}
	} 
	stockqlv_*=*qlv_; // in verhouding tot hoofdartikel
	fasunlck(-2);
#if STOCK_OP_LOCATIE
  if(fldlen(8,48)) filiaal=*u(8,48); // bij voorkeur 48, 43 is voor uitzonderingen
	else if(fldlen(8,43)) filiaal=*u(8,43);
#if FLAGAST
	if(DefaultFiliaal==0 || DefaultFiliaal==99){
		for(k=0;k<10;k++) if(orig_klt==loc_klt[k]) break;
		if(k<10 && loc_nr[k]){
  		filiaal=99;muteer_=YES;
		}
	}
#endif
  if(filiaal && filiaal!=99){/* stock op filiaal */
    fasinit(66);*u(66,2)=*pu_6_1;g=faskeyi(66,1,0);
    if(g){fasinit(66);*u(66,2)=*pu_6_1;errnum=fasadd(66);}
    if(echt_artikel_) stu_add(66,11+(filiaal-1)*15,&stockqlv_);/* stock */
    q_=-stockqlv_;
    stu_add(66,17+(filiaal-1)*15,&q_);
    if(fldlen(66,19+(filiaal-1)*15)) *u(66,19+(filiaal-1)*15)=ft_date;
#if !NO_ART_UPD && !KAS2JMCFACTUUR // stock via kassa aangepast
    if(*u(66,1)) fasupd(66); else fasadd(66);
#endif
#if FLAGKEE || FLAGCRA// indien factuur op andere kassaklant, dan die filiaalstock verhogen (PDA-Willekes)
		for(k=0;k<10;k++) if(*u(2,1)==loc_klt[k]) break;
		if(k<10){
			q_=-stockqlv_;
			if(echt_artikel_) stu_add(66,11+k*15,&q_);/* stock */
      stu_add(66,14+k*15,&q_);
      if(fldlen(66,16+k*15)) *u(66,16+k*15)=ft_date;
#if !NO_ART_UPD && !KAS2JMCFACTUUR // stock via kassa aangepast
      if(*u(66,1)) fasupd(66); else fasadd(66);
#endif
		}
#endif
    goto endsr;
  }
#endif
  if(echt_artikel_){// gekoppeld leeggoed NIET updaten omdat hier enkel het leeg leeggoed op wordt bijgehouden.
		stu_add(6,33,&stockqlv_);
		if(fldlen(6,48)) *u(6,48)=ft_date;
		q_=-stockqlv_;
		stu_add(6,57,&q_);
		stu_add(6,58,bedrag_);
		stu_add(6,59,&q_);
		stu_add(6,60,bedrag_);
	}
	endsr:;
#if STOCKMUT_FT_LOC // indien levering aan filiaal, dan de stock van dat filiaal verhogen
  if(fldlen(8,48)) filiaal=*u(8,48); // bij voorkeur 48, 43 is voor uitzonderingen
	else if(fldlen(8,43)) filiaal=*u(8,43);
	if(filiaal==0) filiaal=99;
	if(echt_artikel_){
#if FLAGAST
		if(muteer_ && filiaal!=99 && filiaal!=DefaultFiliaal){  // enkel doen als filiaal van dossier leeg is (=depot AST)
			q_=-stockqlv_;
        fasinit(66);*u(66,2)=*pu_6_1;g=faskeyi(66,1,0);
        if(g){fasinit(66);*u(66,2)=*pu_6_1;errnum=fasadd(66);}
				g=filiaal-1; 
				stu_add(66,11+g*15,&q_);// stock 
        stu_add(66,14+g*15,&q_); // aangekocht
        if(fldlen(66,16+g*15)) *u(66,16+g*15)=ft_date; // AK-datum
				fasupd(66);
			}
		}
#else

		for(k=0;k<10;k++) if(orig_klt==loc_klt[k]) break;
		if(k<10 && loc_nr[k] && loc_nr[k]!=filiaal){
			q_=-stockqlv_;
      if(loc_nr[k]==99){
				stu_add(6,33,&q_); // stock 
				stu_add(6,53,&q_); // aangekocht
		    stu_add(6,54,bedrag_);
		    stu_add(6,55,&q_);
		    stu_add(6,56,bedrag_);
			}
			else {
        fasinit(66);*u(66,2)=*pu_6_1;g=faskeyi(66,1,0);
        if(g){fasinit(66);*u(66,2)=*pu_6_1;errnum=fasadd(66);}
				g=loc_nr[k]-1; 
				stu_add(66,11+g*15,&q_);// stock 
        stu_add(66,14+g*15,&q_); // aangekocht
        if(fldlen(66,16+g*15)) *u(66,16+g*15)=ft_date; // AK-datum
				fasupd(66);
			}
		}
	}
#endif
#endif

}
#endif
 
#if FLAG244 && STOCK244
static upd_artstock(neg_)
flag neg_;
{
  float belastbf,f_;
	
  if(*ps_58_16=='*' || *pu_58_14==0) goto endsr;
  if(*i(58,34)!=99) belastbf=*pd_58_35;
  else belastbf=*f(58,47);
  f_=*pf_58_31;
  *pu_6_1=*pu_58_14;
  if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) f_/=*f(58,63);
  _upd_stock(*pu_58_14,&f_,&belastbf,neg_,YES);
  if(*u(58,48) && *pu_58_14!=*u(58,48)){
    f_=*f(58,49) * *pf_58_31;
    belastbf=*f(58,47);
/* belastbf=valu_cnv(ft_munt,def_munt,(double)*f(58,47),prx_afrond); */
    if(sys2727==0) _upd_stock(*u(58,48),&f_,&belastbf,neg_,NO);
  }
  endsr:;
}

static _upd_stock(rec_,q_,bd_,neg_,echt_artikel_)
uint16 rec_;
float *q_,*bd_;
flag neg_,echt_artikel_;
{
  float q_neg_;

  if(neg_){*q_=-*q_; *bd_=-*bd_;}
  q_neg_=-*q_;
  *pu_6_1=rec_;
  if(fasgetu(6)==0){
    art_stadd(&q_neg_,bd_,echt_artikel_);
		if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
    fasupd(6);
  }
}
#endif

#if FICHEEXEC
static klt_stat()
{
  int16 j,k;
  float belastbf,liters_=0,q_punten_=0;
  uint16 rec_;

	fasunlck(-2);
  belastbf=belastbt;
/*  belastbf=valu_cnv(ft_munt,def_munt,(double)belastbt,prx_afrond); */
  for(k=0;k<max_line;k++){
    ram2stu(k);
#if PUNTENPROMO
    if(*pu_58_14){
      fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
      q_punten_+=*pf_58_31* *f(6,68);
    }
#endif
    liters_+=*pf_58_31* *f(58,13);
  }
  rec_=*pu_2_1;
  if(fldlen(2,51) && *u(2,51) && sys3918) stat_klt=*u(2,51);
  else if(stat_klt==0) stat_klt=*pu_2_1;
  *pu_2_1=stat_klt;fasgetu(2);
  if(fldlen(2,47)) *u(2,47)=ft_date;
  stu_add(2,57,&belastbf);
  stu_add(2,58,&belastbf);
  stu_add(2,62,&liters_);
  stu_add(2,63,&liters_);
#if PUNTENPROMO
  stu_add(2,70,&q_punten_);
#endif
  if(fldlen(2,59)) *u(2,59)=*u(2,59)+1;
  *f(2,64)+=semestbd;
#if FLAG248 & KORT_DELAYED
  if(fldlen(2,50)){
    belastbf=tot_kort;
/* belastbf=valu_cnv(ft_munt,def_munt,(double)tot_kort,prx_afrond); */
    if(fldlen(2,49)==0 || *s(2,49)=='J') *f(2,50)+=belastbf;
  }
#endif
  fasupd(2);

#if FLAGVSP | STB_flag
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(*pu_58_14){
      for(j=0;j<5;j++){
	if(cmpstr(ps_58_15,s(2,80+j*2),5)==0) {*i(2,81+j*2)+=*pf_58_31;break;}
      }
      if(*u(58,48) && *u(58,48)!=*pu_58_14){/* leeggoed */
	fasinit(6);*u(6,1)=*u(58,48);fasgeti(6);
	for(j=0;j<5;j++){
	  if(cmpstr(s(6,2),s(2,80+j*2),5)==0) {*i(2,81+j*2)+=*pf_58_31;break;}
	}
      }
    }
  }
  fasupd(2);
#endif
  *pu_2_1=rec_;fasgetu(2);
}
#endif


#if STATISTIEK & (FICHEEXEC | SPLITS_STATIST)
static statistiek_upd(mode_)
int16 mode_;
{
  int16 k,dd=0,mm=0,jj=0,off_=0;
  float bd_,bd1_,qlv_;

	fasunlck(-2);
  if(fldlen(2,51) && *u(2,51) && sys3918) stat_klt=*u(2,51);
  else if(stat_klt==0) stat_klt=*pu_2_1;
  if(mode_){/* op vorig jaar bijhouden */
    stat_klt=*pu_2_1;off_=12;
  }
#if FLAGDU3/* particuliere verkopen op 1 klant bijhouden */
  if(fldlen(2,33) && *s(2,33)=='P' && klt_div2) stat_klt=klt_div2;
#endif
  jddate(ft_date,&jj,&mm,&dd);mm--;
#if LEVERINGSKOST || KM_HEFFING 
	if(*f(8,46)){
		fasinit(58);
		*f(58,24)=BtwLeveringskost; *f(58,63)=1;
		bd1_=1; bd_=*f(8,46);
		 _sta_upd(RecLevKostArt,&bd1_,&bd_,mm+off_);
	}
#endif
  for(k=0;k<max_line;k++){
    ram2stu(k);
    bd1_=*pf_58_31;if(len58_62) if(*ps_58_62=='S' && *f(58,63)!=0) bd1_/=*f(58,63);
    if(*pu_58_14 && *ps_58_16!='*'){/* artikel */
      bd_=*pd_58_35;
/* bd_=valu_cnv(ft_munt,def_munt,*pd_58_35,prx_afrond); */
      _sta_upd(*pu_58_14,&bd1_,&bd_,mm+off_);
    }
    if(fldlen(58,48) && *u(58,48)){/* leeggoed */
      if(*pu_58_14==*u(58,48)) qlv_=0; else qlv_=*f(58,49)* *pf_58_31;
      bd_=*f(58,47);
/* bd_=valu_cnv(ft_munt,def_munt,(double)*f(58,47),prx_afrond); */
      _sta_upd(*u(58,48),&qlv_,&bd_,mm+off_);
    }
    if(fldlen(58,57) && *u(58,57)){/* afhaalvergoeding */
      bd_=*f(58,56);
/*    bd_=valu_cnv(ft_munt,def_munt,(double)*f(58,56),prx_afrond); */
      _sta_upd(*u(58,57),&bd1_,&bd_,mm+off_);
    }
#if !FLAGDUB && !FLAGFLI && !FLAGSEG
    if(fldlen(58,60) && *u(58,60)){/* losvergoeding */
      bd_=*f(58,59);
/*  bd_=valu_cnv(ft_munt,def_munt,(double)*f(58,59),prx_afrond); */
      _sta_upd(*u(58,60),&bd1_,&bd_,mm+off_);
    }
#endif
  }
  endsr:;
}

static _sta_upd(rec_,qlv_,bd_,kol_)
uint16 rec_,kol_;
float *qlv_,*bd_;
{
  flag add_rec_;
  float bda_;

  fasinit(6);*pu_6_1=rec_;fasgeti(6);
  if(fldlen(6,76) && *s(6,76)!='J') goto endsr;
  fasinit(60);*l(60,22)=rec_;*l(60,2)=stat_klt;
  if(fldlen(2,28) && fldlen(60,4)) copy(s(2,28),s(60,4),fldlen(2,28));
  if(faskeyu(60,1,0)) add_rec_=YES;
  else add_rec_=NO;
#if FRI_flag
  if(add_rec_) goto endsr;/* geen nieuwe records meer bijmaken */
#endif
  if(fldlen(60,3)) *s(60,3)=*s(2,26);
  if(fldlen(60,24)) *i(60,24)=*i(6,9);
  if(fldlen(60,25)) *u(60,25)=*u(6,7);
  copy(s(6,2),s(60,23),fldlen(6,2));
  bda_=*qlv_* *f(6,18);
  stu_add(60,52+kol_,&bda_);/* ak-waarde */
  stu_add(60,82+kol_,bd_);/* vk-waarde */
  stu_add(60,112+kol_,qlv_);/* aantal */
  if(rec_==*pu_58_14){/* ENKEL op origineel artikel */
    bda_=*f(58,53);
/*  bda_=valu_cnv(ft_munt,def_munt,(double)*f(58,53),prx_afrond); */
    stu_add(60,142+kol_,&bda_);/* sem. korting */
    if(fldlen(58,52)){
      bda_=*f(58,52);
/*    bda_=valu_cnv(ft_munt,def_munt,(double)*f(58,52),prx_afrond); */
      stu_add(60,172+kol_,&bda_);/* directe korting */
    }
    if(fldlen(58,97)){
      bda_=*f(58,97);
/*    bda_=valu_cnv(ft_munt,def_munt,(double)*f(58,97),prx_afrond); */
      stu_add(60,202+kol_,&bda_);/* tussenkomst brouwerij  */
    }
    if(*qlv_ && *bd_==0){
      stu_add(60,232+kol_,qlv_);/* gratis artikels   */
    }
  }
  if(add_rec_) errnum=fasadd(60);
  else errnum=fasupd(60);
  if(errnum){
    if(errnum==48||errnum==49)errnum=9;
    scrget(1,170);
    scrifld(5,fm_os63,"    Fout tijdens het bijwerken van de statistieken.");
    scrifld(10,fm_os63,"     Druk <TAB> om verder te gaan.");
    scrupd(-1,0);
    scrget(1,7);scrupd(-3,0);
  }
  endsr:;
}
#endif

#if HISTORIEK
static historiek_upd()
{
  int16 j,k;
  double bd_,qlv_;

#if !ARTEXIST // bij facturatie verkopen kassa mag geen historiek worden bijgeghouden 
	goto endsr;
#endif
  if(fldlen(2,51) && *u(2,51) && sys3918) stat_klt=*u(2,51);
  else if(stat_klt==0) stat_klt=*pu_2_1;
#if FLAGDU3                  /* particuliere verkopen op 1 klant bijhouden */
  if(fldlen(2,33) && *s(2,33)=='P' && klt_div2) stat_klt=klt_div2;
#endif
  fasunlck(-2);
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(test_line()==NO) continue;
		if(*ps_58_16=='*') *pu_58_14=0;
		if(*pu_58_14==0 && (*pd_58_35 || *f(58,47))){// op divers artikel zetten 
		  if(*i(58,34)==99){ *pu_58_14=TbDiversArtikel[9];*u(58,48)=TbDiversArtikel[9];} // leeggoed divers
			else {
				for(j=0;j<8;j++) if(*f(58,24)==btw_pct[j]) break;
				if(j<8) *pu_58_14=TbDiversArtikel[j];
			}
		}

    if(*pu_58_14==0 || *pf_58_31==0) continue;
/* artikel */
    if(*i(58,34)!=99) bd_=*pd_58_35; else bd_=*f(58,47);
    bd_=round((double)bd_);
    qlv_=*pf_58_31;if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)!=0) qlv_/=*f(58,63);
    _his_upd(*pu_58_14,&qlv_,&bd_);
 
    if(fldlen(58,48) && *u(58,48) && *pu_58_14!=*u(58,48)){/* leeggoed */
      qlv_=*f(58,49)* *pf_58_31;
      bd_=round((double)*f(58,47));
      _his_upd(*u(58,48),&qlv_,&bd_);
    }
    if(fldlen(58,57) && *u(58,57)){/* afhaalvergoeding */
      bd_=round((double)*f(58,56));
      qlv_=*pf_58_31;if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)!=0) qlv_/=*f(58,63);
      _his_upd(*u(58,57),&qlv_,&bd_);
    }
#if !FLAGDUB && !FLAGSEG && !FLAGFLI// bij DUB heeft 58,60 andere betekenis 
    if(fldlen(58,60) && *u(58,60)){/* losvergoeding */
      bd_=round((double)*f(58,59));
      qlv_=*pf_58_31;if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)!=0) qlv_/=*f(58,63);
      _his_upd(*u(58,60),&qlv_,&bd_);
    }
#endif
  }
#if LEVERINGSKOST  || KM_HEFFING 
	if(*f(8,46) && RecLevKostArt){
		fasinit(58);
		*f(58,24)=BtwLeveringskost; *f(58,63)=1;
		qlv_=1; bd_=*f(8,46);
	 _his_upd(RecLevKostArt,&qlv_,&bd_);
	}
#endif


  endsr:;
}

static _his_upd(rec_,qlv_,bd_)
uint16 rec_;
double *qlv_,*bd_;
{
  int16 k,add_rec_=YES,mode_;
	float tr_aantal_,factor_;
 
  fasinit(6);*pu_6_1=rec_;fasgeti(6);
  if(*i(6,9)==99){/* leeggoed altijd probren samen te tellen */
    fasinit(16);
    *l(16,10)=stat_klt;
    *l(16,20)=*pu_6_1;
    *u(16,3)=ft_date;
    mode_=1;
    FOREVER{
      if(faskeyi(16,1,mode_)) break; mode_=2;
      if(*l(16,10)!=stat_klt) break;
      if(*l(16,20)!=*pu_6_1) break;
      if(*u(16,3)!=ft_date) break;
      if(*l(16,2)==ft_nr){add_rec_=NO;break;}
    }
  }
  if(add_rec_) fasinit(16);
  *l(16,2)=ft_nr;
  *u(16,3)=ft_date;
  copy(s(8,25),s(16,4),fldlen(16,4));
	if(fldlen(8,48) && fldlen(16,8)) *u(16,8)=*u(8,48); // filiaalnr
  *l(16,10)=stat_klt;
	if(fldlen(16,12)) *l(16,12)=orig_klt;
  if(fldlen(2,28) && fldlen(16,13)) copy(s(2,28),s(16,13),fldlen(2,28)); // vertegenwoordiger
  *l(16,20)=*pu_6_1;
  copy(s(6,2),s(16,21),fldlen(16,21));
  copy(s(6,3),s(16,22),fldlen(16,22));
  *l(16,23)=*u(6,9);
	if(fldlen(6,103) && fldlen(16,28)) *u(16,28)=*u(6,103); // subgroep
  *f(16,24)=*f(6,28);/* standaard BTW% */
  copy(s(6,10),s(16,25),fldlen(16,25));
  if(rec_==*pu_58_14){
    if(*s(58,16)) copy(s(58,16),s(16,22),fldlen(16,22));
		else copy(s(6,3),s(16,22),fldlen(16,22));
    *f(16,24)=*f(58,24);/* echt BTW% */
    *f(16,26)=*f(58,63);/* q_bak */
    if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)!=0) *f(16,27)=*f(58,38)* *f(58,63);/* accijns */
		else *f(16,27)=*f(58,38);
  }
  *d(16,30)+=*qlv_;
  *d(16,31)+=*bd_;
#if FT_ACC_FREE
		if(fldlen(2,88) && *s(2,88)=='J'){ // accijnsvrij
			*f(6,18)-=*f(6,30); 
		}
#endif
	if(fldlen(58,41) && *f(58,41)) *d(16,32)+=round((double)(*qlv_* *f(58,41)));
	else *d(16,32)+=round((double)(*qlv_* *f(6,18)));
#if KAS2JMCFACTUUR || KAS2JMCBON
	if(fldlen(16,39)) *s(16,39)=YES; // om aan te duiden dat het van de kassa komt
#endif
	if(fldlen(8,74) && fldlen(16,39)) *s(16,39)=*s(8,74); // om aan te duiden dat het van de kassa komt
  if(rec_==*pu_58_14){/* ENKEL op origineel artikel */
    if(fldlen(58,52)) *d(16,33)+=round((double)*f(58,52));
    if(fldlen(58,53)) *d(16,34)+=round((double)*f(58,53));
    if(fldlen(58,97)) *d(16,35)+=round((double)*f(58,97));
#if TRACEERDATA
		if(fldlen(16,40) && fldlen(58,138)) copy(s(58,138),s(16,40),fldlen(16,40)); // lotnummer 
		if(fldlen(16,41) && fldlen(58,137)) *u(16,41)=*u(58,137); // vervaldatum
#else 
		if(fldlen(16,40) && fldlen(58,71)) copy(s(58,71),s(16,40),fldlen(16,40)); // lotnummer oud systeem
#endif
  }
  if(add_rec_) errnum=fasadd(16);
  else errnum=fasupd(16);
#if TRACEERDATA
	if(rec_==*pu_58_14){/* ENKEL op origineel artikel */
		tr_aantal_=0; factor_=1.; if(*f(58,31)<0) factor_=-1.;
		for(k=0;k<10;k++)	if(fldlen(58,136+k*4) && (*u(58,137+k*4) || *s(58,138+k*4) || *s(58,139+k*4))) tr_aantal_+=*f(58,136+k*4)*factor_;
		tr_aantal_=*f(58,31)-tr_aantal_;
		for(k=0;k<10;k++){
			if(fldlen(58,136+k*4) && (*u(58,137+k*4) || *s(58,138+k*4) || *s(58,139+k*4))){
				fasinit(67);
				if(*f(58,136+k*4)) *f(67,10)=-*f(58,136+k*4)*factor_;
				else{*f(67,10)=-tr_aantal_;tr_aantal_=0;}
				if(*f(67,10)){
					*u(67,2)=*u(6,1); *u(67,3)=stat_klt+30000; *u(67,4)=ft_date; *u(67,5)=ft_nr; copy(s(8,25),s(67,9),fldlen(67,9));
					*u(67,11)=*u(58,137+k*4); copy(s(58,138+k*4),s(67,12),fldlen(67,12)); copy(s(58,139+k*4),s(67,13),fldlen(67,13));
					errnum=fasadd(67);
				}
			}
		}
	}
#endif
  endsr:;
}
#endif

static exit_hfdmenu()
{
	int16 busy_proc;
	 
  sysget(SysPosNrCheck,2,&busy_proc);
  if(busy_proc==procid){busy_proc=0;sysput(SysPosNrCheck,2,&busy_proc);sysflush();}

  ovlexit(*u(25,4));
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
	for(k=0;k<4;k++){
		if(fldlen(9,88+k*5) && *f(9,88+k*5)) return NO;
	}
  if(fldlen(9,16) && *i(9,16)) return NO;
  return YES;
}

static test_line()
{
  if(*ps_58_15 || *ps_58_16 || *pf_58_20) return YES;
  return NO;
}

static btw_tab(bd_)
BEDRAG bd_;
{
  int16 k;
  float btw_;

  btw_=round((double)(*pf_58_24));
  for(k=0;k<BTWDIM-BTWDIV;k++){
    if(btw_==btw_pct[k]) break;
  }
  return k;
}

static BEDRAG round(value_)
double value_;
{
  double bd_;
						
  bd_=valu_cnv(def_munt,def_munt,value_,ft_afrond);
  return (BEDRAG)(bd_);
}

static stu_add(stu_,elet_,pf1)
int16 stu_,elet_;
float *pf1;
{
  if(fldlen(stu_,elet_)){
    *f(stu_,elet_)+=*pf1;
  }
}

static MakeDeHeer(stu_,nm_dehr)
int16 stu_;
char *nm_dehr;
{
  int16 max_,xpos_,j,k;

	zero(nm_dehr,40);xpos_=0; 
  for(max_=0;max_<40;max_++){
		if(*(s(stu_,3)+max_)=='\0') break;
		if(*(s(stu_,3)+max_)=='*') xpos_=max_;
	}
	if(max_==40 && *(s(stu_,3)+39)=='!') max_--;
	if(xpos_ && xpos_>=max_-1) xpos_=0;
	if(xpos_==0){copy(s(stu_,3),nm_dehr,max_);goto endsr;}

	for(k=xpos_+1;k<max_;k++) if(*(s(stu_,3)+k)!=' ') break;
	j=copy0(s(stu_,3)+k,nm_dehr,max_-k);
	nm_dehr[j++]=' ';copy(s(stu_,3),&nm_dehr[j],xpos_);
endsr:;
}

#if PRTDUBBELA4
static OpenTempPrintFile(mode_)
{
	char filnam_[15];
	  
	copy("TMP",filnam,3);
  stcli_d(&filnam[3],(long)(procid),3,0);
  copy(".wrk",&filnam[6],5);
	fasclos(-2);
  if(fasopen(filnam,mode_)){errnum=63;scrget(1,170);return NO;}
  fasinit(80);seqo_pos=0;
  if(mode_==2){ // is nodig omdat eerst een nextline wordt gedaan om juiste free te kennen
	  *(p_data+seqo_pos++)=0x0D; *(p_data+seqo_pos++)=0x0A;
    fasseqo(80,2,seqo_pos+4);
    zero(p_data,256);seqo_pos=0; 
  }
	return YES;
}


static pprttext(ps_)
char *ps_;
{
  prttext(ps_);
  if(DubbelA4Mode){
    prtbuf(0);
    seqo_pos+=copy0(GetPtrInfo(),p_data+seqo_pos,100);
  }
}
 
static pprtblank(k)
int16 k;
{
  prtblank(k);
  if(DubbelA4Mode){
    prtbuf(0);
    seqo_pos+=copy0(GetPtrInfo(),p_data+seqo_pos,100);
  }
}

static pprtfld(stu_,ele_,mode_)
int16 stu_,ele_,mode_;
{
  prtfld(stu_,ele_,mode_);
  if(DubbelA4Mode){
    prtbuf(0);
    seqo_pos+=copy0(GetPtrInfo(),p_data+seqo_pos,100);
  }
}
 
static pprtifld(fmt_,pvar_,mode_)
char *fmt_,*pvar_;
int16 mode_;
{
  prtifld(fmt_,pvar_,mode_);
  if(DubbelA4Mode){
    prtbuf(0);
    seqo_pos+=copy0(GetPtrInfo(),p_data+seqo_pos,100);
  }
}
 
static nnextline()
{
  if(DubbelA4Mode){
    *(p_data+seqo_pos++)=0x0D; *(p_data+seqo_pos++)=0x0A;
    fasseqo(80,2,seqo_pos+4);
    zero(p_data,256);seqo_pos=0; free--;
    if(free<200 && (sfree==0 || sfree<free)) sfree=free+1;
  }
  else{
    nextline();
    if(free<200 && (sfree==0 || sfree<free)) sfree=free+1;
  }
}
 
static sskip_lin(line_)
int16 line_;
{
  if((line_+skip_off)>0){
    while(free>(line_+skip_off)) nnextline();
  }
}
 
static pprtform(mode_)
int16 mode_;
{
  if(DubbelA4Mode){seqo_pos+=copy0("<PAGE>",p_data+seqo_pos,6);nnextline();free=sfree;}
  else {prtform(mode_);free=999;}
}

static PrintDocFromWrk()
{
	int j,k,mode_,first_,used_,end_,count,kol;
	long fpos_;
	char browse_buf[250],byte;

	if(OpenTempPrintFile(1)==NO) goto endsr;
  fasinit(80);fpos_=0; first_=YES;end_=NO; used_=NO; mode_=0;

  FOREVER{
		redo:;
    if(read_rec(mode_)) end_=YES; mode_=1;
		if(end_){
		  if(first_==NO || used_==NO) break;
			prtform(0);
			fasinit(80);*l(80,1)=fpos_; mode_=0; first_=NO; end_=NO;used_=NO;
			goto redo;
		}
    if(cmpstr(p_data,"<PAGE>",6)==0){
			if(used_==NO) goto redo;
			prtform(0);
			if(first_){
				fasinit(80);*l(80,1)=fpos_; mode_=0; first_=NO; end_=NO;used_=NO;
			}
			else{
				first_=YES; mode_=1; end_=NO;used_=NO;fpos_=*l(80,1)+8;
			}
			goto redo;
    }
    zero(browse_buf,sizeof browse_buf);
    for(k=0;k<250;k++){
      byte=*(p_data+k);
      if(byte=='\0' || byte==0x0D) break;
			else browse_buf[k]=byte;
		}
		prttext(browse_buf); nextline();used_=YES;
  }
	fasclos(-2);
	OpenTempPrintFile(99); // wrk-file deleten
  prtform(0);prtclose();
	endsr:;
}


#endif
  



#if COPY_FACT
#if FLAG248
static sifopen(prtnr_,p_form_,lpi_,kol_,mode_,q_hdr_)
int16 prtnr_,lpi_,kol_,mode_,q_hdr_;
char *p_form_;
{
  int16 yy,mm,dd,k,sys3646;
  char ofname[40];
		
  fasclos(-2);
  jddate(ft_date,&yy,&mm,&dd);

  yy%=100;
  sysget(4704,25,ofname);sysget(3646,2,&sys3646);
  for(k=0;k<25;k++) if(ofname[k]=='\0') break;
  if(sys3646){
    copy(s(25,3),&ofname[k],3); ofname[k+3]='\0';
  }
  else {
    copy("FT",&ofname[k],2);ofname[k+2]='\0';
  }
  for(k=0;k<25;k++) if(ofname[k]=='\0') break;
  stcli_d(&ofname[k],(long)ft_nr,5,0);
  ofname[k+5]='.';stcli_d(&ofname[k+6],(long)yy,2,0);
  if(fasopen(ofname,2))return YES;
	SeqiMode=2;
  fasinit(80);seqo_pos=0; p_data=s(80,1)+4;
  copy(&prtnr_,p_data,2);copy(p_form_,p_data+2,16);
  copy(&lpi_,p_data+18,2);
  copy(&kol_,p_data+20,2);
  copy(&mode_,p_data+22,2); fasseqo(80,2,22+4);

  endsr:;
  return NO;
}
#endif

static pprttext(ps_)
char *ps_;
{
  prttext(ps_);
#if FLAG248
  if(smode){
    prtbuf(0);
    seqo_pos+=copy0(GetPtrInfo(),p_data+seqo_pos,100);
  }
#endif
}
 
static pprtblank(k)
int16 k;
{
  prtblank(k);
#if FLAG248
  if(smode){
    prtbuf(0);
    seqo_pos+=copy0(GetPtrInfo(),p_data+seqo_pos,100);
  }
#endif
}

static pprtfld(stu_,ele_,mode_)
int16 stu_,ele_,mode_;
{
  prtfld(stu_,ele_,mode_);
#if FLAG248
  if(smode){
    prtbuf(0);
    seqo_pos+=copy0(GetPtrInfo(),p_data+seqo_pos,100);
  }
#endif
}
 
static pprtifld(fmt_,pvar_,mode_)
char *fmt_,*pvar_;
int16 mode_;
{
  prtifld(fmt_,pvar_,mode_);
#if FLAG248
  if(smode){
    prtbuf(0);
    seqo_pos+=copy0(GetPtrInfo(),p_data+seqo_pos,100);
  }
#endif
}
 
static nnextline()
{
#if FLAG248
  if(smode){
    *(p_data+seqo_pos++)=0x0D; *(p_data+seqo_pos++)=0x0A;
    fasseqo(80,2,seqo_pos+4);
    zero(p_data,256);seqo_pos=0; free--;
  }
  else{
    nextline();
    if(free<200 && (sfree==0 || sfree<free)) sfree=free+1;
  }
#else
  nextline();
#endif
}
 
static sskip_lin(line_)
int16 line_;
{
  if((line_+skip_off)>0){
    while(free>(line_+skip_off)) nnextline();
  }
}
 
static pprtform(mode_)
int16 mode_;
{
#if FLAG248
  if(smode){seqo_pos+=copy0("<PAGE>",p_data+seqo_pos,6);nnextline();free=sfree;}
  else {prtform(mode_);free=999;}
#else
  prtform(mode_);free=999;
#endif
}
#endif
  
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

 
#if (FLAG244 & !KAS2JMCBON) & B_LST_BON & !SAMENVOEGEN & !PDA_LGRETOUR
static bon_lst()
{
  int16 j,z,fkey_,key;
 
  fasinit(2);
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,12,10,0);scraddf(z++,12,30,2);
  scraddf(z++,12,39,0);scraddf(z++,12,48,2);
  scraddf(z++,14,10,0);scraddf(z++,14,30,2);
  scraddf(z++,23,1,8);scraddf(z++,23,12,8);
  FOREVER{
    redo:;
    z=1;
    DisplayMenuTitel(6,"Afdrukken lijst bons",0x3);
    scrifld(z++,fm_os63,"Selectie periode :");
    scrifld(z++,fm_udat,&dt_bon_beg);
    scrifld(z++,fm_os10,"t.e.m.");
    scrifld(z++,fm_udat,&dt_bon_end);
    scrifld(z++,fm_os63,"Selectie klant . :");
    scrfld(z++,2,3);
    scrifld(z++,fm_os10," F1 stop");scrifld(z++,fm_os14," F8 neem aan");
    key=scrupd(1,0x81);
    if(*s(2,3)) {if(search(2,0)) goto redo;}
    else fasinit(2);
    orig_klt=*pu_2_1;
    if(key==101) goto endsr;
    if(key!=108) goto redo;
    break;
  }

  prtclose();
  getsysprNew(5,form_dat,&mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1);prttext("<t40b>");prttext("Leveringsbons");prttext("<b>");
  prttext("<t60>");prtfld(25,2,-1);
  prttext("<t72>Blz.<ppp>.");
  prtbuf(1);z=1;
  if(fldlen(2,2)) prttab(z,2,2,1,-1);
  else prttab(z,2,1,1,-1); prttitle(z++,"Code",3);
  prttab(z,2,3,1,-1); prttitle(z++,"Klant",3);
  prttab(z,8,8,1,-1); prttitle(z++,"Lev.dt.",0x13);
  prttab(z,8,2,6,-1); prttitle(z++,"Bonnr",0x13);
  prtbuf(3);
	p_pdfname("Lijst leveringsbons",dt_bon_beg,dt_bon_end);
  free=999;
  fasinit(8); fkey_=1; if(faskeyi(8,2,2)==0) fkey_=2;
  fasinit(8);
  FOREVER{
    next:;
    if(faskeyi(8,fkey_,2)) break;
#if BACKORDER
    if(*u(8,36)) goto next;
#endif
    if(orig_klt && *u(8,3)!=orig_klt) goto next;
    if(dt_bon_beg && *u(8,8)<dt_bon_beg) goto next;
    if(dt_bon_end && *u(8,8)>dt_bon_end) goto next;
    fasinit(2);*pu_2_1=*u(8,3);fasgeti(2);
    for(j=1;j<=15;j++) prtinfo(j,0);
    nextline();
    if(free<0) break;
    prt_det_bon();
  }
  prtclose();
  endsr:;
  exit_hfdmenu();
}
#endif

#if FLAG244 & !SAMENVOEGEN & !PDA_LGRETOUR
static prt_det_bon()
{
  int16 k=0,mode_;
  flag printed=NO;
  float hoev_;

  fasinit(58);*u(58,2)=*u(8,1);mode_=1;
  FOREVER{
    next:;
    if(faskeyi(58,1,mode_)) break;mode_=2;
    if(*u(58,2)!=*u(8,1)) break;
#if SPLITS_BON | DEF_INPUT
    if(*pf_58_31==0) goto next;
#endif
    prttext("<t20>");
    if(len58_15) {prtfld(58,15,-1);prtblank(2);}
    prtfld(58,16,-1);prtblank(2);
    prtfld(58,31,-1);prtblank(2);
    prtfld(58,20,-1);
    nextline();
    printed=YES;k++;
  }
  if(printed) nextline();
}
#endif

 
#if FLAGVVL & (FLAG244 & !KAS2JMCBON) & B_LST_BON & !SAMENVOEGEN & !PDA_LGRETOUR
static VVL_bon_lst()
{
  int16 j,k,z,fkey_,key,mode58_;
	double bd_ap,bon_ap,tot_ap,bd_vp,bon_vp,tot_vp,bd_winst;
  float winst_pct;
  uint16 last_klt;
		   
  fasinit(2);
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,12,10,0);scraddf(z++,12,30,2);
  scraddf(z++,12,39,0);scraddf(z++,12,48,2);
  scraddf(z++,14,10,0);scraddf(z++,14,30,2);
  scraddf(z++,23,1,8);scraddf(z++,23,12,8);
  FOREVER{
    redo:;
    z=1;
    DisplayMenuTitel(6,"Afdrukken lijst bons",0x3);
    scrifld(z++,fm_os63,"Selectie periode :");
    scrifld(z++,fm_udat,&dt_bon_beg);
    scrifld(z++,fm_os10,"t.e.m.");
    scrifld(z++,fm_udat,&dt_bon_end);
    scrifld(z++,fm_os63,"Selectie klant . :");
    scrfld(z++,2,3);
    scrifld(z++,fm_os10," F1 stop");scrifld(z++,fm_os14," F8 neem aan");
    key=scrupd(1,0x81);
    if(*s(2,3)) {if(search(2,0)) goto redo;}
    else fasinit(2);
    orig_klt=*pu_2_1;
    if(key==101) goto endsr;
    if(key!=108) goto redo;
    break;
  }

  prtclose();
  getsysprNew(5,form_dat,&mode,&prtnr);
	if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,mode,4))!=0) goto endsr;
  scrget(1,6);scrupd(-3,0);
  prtfld(25,1,-1);prttext("<t40b>");prttext("Leveringsbons");prttext("<b>");
  prttext("<t60>Periode : ");prtifld(fm_udat,&dt_bon_beg,-1);
  prttext(" - ");prtifld(fm_udat,&dt_bon_end,-1);
  prttext("<t95>");prtfld(25,2,-1);
  prttext("<t120>Blz.<ppp>.");
  prtbuf(1);z=1;
  prttab(z,8,8,1,-1); prttitle(z++,"Lev.dt.",0x13);
  prttab(z,8,2,1,-1); prttitle(z++,"Bonnr",0x13);
  prttab(z,58,15,1,-1); prttitle(z++,"Code",3);
  prttab(z,58,16,1,-1); prttitle(z++,"Omschrijving",3);
  prttab(z,58,31,1,-1); prttitle(z++,"Aant",0x13);
  prttab(z,58,20,1,-1); prttitle(z++,"Netto vp",0x13);
  prttab(z,6,18,1,-1); prttitle(z++,"Netto ap",0x13);
  prtitab(z,fmeobd,&bd_vp,1,-1); prttitle(z++,"VK-waarde",0x13);
  prtitab(z,fmeobd,&bd_ap,1,-1); prttitle(z++,"AK-waarde",0x13);
  prtitab(z,fmeobd,&bd_winst,1,-1); prttitle(z++,"Winst",0x13);
  prtitab(z,fm_of3_1,&winst_pct,1,-1); prttitle(z++,"W%",0x13);
  prtbuf(3);
	p_pdfname("Lijst leveringsbons",dt_bon_beg,dt_bon_end);
  free=999;
  fasinit(8); fkey_=1; if(faskeyi(8,2,2)==0) fkey_=2;
  fasinit(8);
	tot_ap=0;tot_vp=0;bon_ap=0;bon_vp=0;last_klt=0;
  FOREVER{
    next:;
    if(faskeyi(8,fkey_,2)) break;
#if BACKORDER
    if(*u(8,36)) goto next;
#endif
    if(orig_klt && *u(8,3)!=orig_klt) goto next;
    if(dt_bon_beg && *u(8,8)<dt_bon_beg) goto next;
    if(dt_bon_end && *u(8,8)>dt_bon_end) goto next;
    fasinit(2);*pu_2_1=*u(8,3);fasgeti(2);
    if(last_klt!=*u(2,1)){
      prttext("<t30><e>");
      j=1;if(fldlen(2,2)) j=2; prtfld(2,j,-1);
      prttext("  ");prtfld(2,3,-1);
      prttext("<e>");nextline();nextline();
      last_klt=*u(2,1);
    }
    for(j=1;j<=2;j++) prtinfo(j,0);

		fasinit(58);*u(58,2)=*u(8,1);mode58_=1;
		FOREVER{
			if(faskeyi(58,1,mode58_)) break;mode58_=2;
			if(*u(58,2)!=*u(8,1)) break;
			bd_vp=*d(58,35)-*f(58,53);
			if(*f(58,31)) *f(58,20)=bd_vp / *f(58,31);
			fasinit(6);*u(6,1)=*u(58,14);fasgeti(6);
			if(*i(6,9)==99) {/* leeggoed niet meetellen */
				for(k=3;k<6;k++) prtinfo(k,0);nextline();
			}
			else {
				bd_ap=*f(58,31)* *f(6,18);
				bd_winst=bd_vp-bd_ap;
				winst_pct=0; if(bd_ap) winst_pct=(bd_winst/bd_ap)*100.;
				for(k=3;k<20;k++) prtinfo(k,0);nextline();
				bon_ap+=bd_ap;bon_vp+=bd_vp;
			}
		}
		fasinit(58); fasinit(6);
		copy("Totaal bon",s(58,16),11);
		bd_ap=bon_ap;bd_vp=bon_vp;
		bd_winst=bd_vp-bd_ap;
		winst_pct=0; if(bd_ap) winst_pct=(bd_winst/bd_ap)*100.;
		for(k=3;k<20;k++) prtinfo(k,2);nextline(); nextline();
		tot_ap+=bon_ap;tot_vp+=bon_vp;bon_ap=0;bon_vp=0;
  }
  fasinit(58); fasinit(8); fasinit(2); fasinit(6);
  copy("Algemeen totaal",s(58,16),16);
  bd_ap=tot_ap;bd_vp=tot_vp;
  bd_winst=bd_vp-bd_ap;
  winst_pct=0; if(bd_ap) winst_pct=(bd_winst/bd_ap)*100.;
  for(j=1;j<20;j++) prtinfo(j,2);nextline(); nextline();
	prtform(0);
  prtclose();
  endsr:;
}
#endif

#if FLAG248 | FLAG244 | FLAG251 | FLAG252 | BONSORT
static SortBon(SortField)
int16 SortField;
{
  int16 j,k,len_,beg_,sw,max_,b_beg_,b_end_;
  char str1[35],str2[35],*ps_;
 

	if(SortField && fldlen(58,SortField)){len_=fldlen(58,SortField);ps_=s(58,SortField);}
	else{
    len_=len58_15;ps_=ps_58_15;
#if SORT_FLD
    if(fldlen(58,SORT_FLD)){len_=fldlen(58,SORT_FLD);ps_=s(58,SORT_FLD);}
#endif
	}
#if FLAGCRA  // opmerkingen onder artikel bij artikel laten bij sortering plaats magazijn
	if(SortField==0) SortField=SORT_FLD;
	if(SortField==101){
		zero(str1,sizeof str1);
		for(k=0;k<max_line;k++){
			ram2stu(k);
			if(*u(58,14)) copy(ps_,str1,len_);
			else if(*s(58,16)=='*') {copy(str1,ps_,len_);stu2ram(k);zero(str1,sizeof str1);}
			else zero(str1,sizeof str1);
		}
	}



#endif
  max_=max_line-1;
  for(max_;max_>=0;max_--){ram2stu(max_); if(test_line()) break;}
#if SCREXEC/* lege lijnen wissen, enkel nodig bij schermupdate */
  for(k=0;k<max_;k++){
    ram2stu(k);
    if(test_line()==NO){
      copy(s(58,1),sortbuf,fldlen(58,0));
      for(j=k;j<max_;j++){
				ram2stu(j+1);
				stu2ram(j);
      }
      copy(sortbuf,s(58,1),fldlen(58,0));
      stu2ram(max_); max_--; k--;
    }
  }
#endif

	beg_=0; max_++;b_beg_=-1; b_end_=-1;
	FOREVER{
next_blok:;
#if FLAGALB || FLAGKLV // na *s stoppen
		if(b_beg_>=0) break;
#endif
		if(beg_>=max_-1) break;
		b_beg_=-1; b_end_=-1;
	  for(k=beg_;k<max_;k++) {
      ram2stu(k); 
#if FLAGEPD
		  if(*ps_58_16=='*'){
#else
		  if(*ps_58_16=='*' && *s(58,62)=='S'){
#endif
#if FLAGALB || FLAGKLV
				if(b_beg_<beg_) b_beg_=k;
				b_end_=k; break;
#else
		  	if(b_beg_<beg_) continue;
				else {b_end_=k; break;}
#endif
		  }
		  else if(b_beg_<beg_) b_beg_=k;
	  }
		if(b_end_<0) b_end_=k;
		if(b_beg_<0) b_beg_=b_end_;
		if((b_end_-b_beg_)<2) {beg_=b_end_+1;goto next_blok;} // te weinig lijnen om te sorteren
		FOREVER{/* sorteren */
			sw=NO;
			for(k=b_beg_;k<b_end_-1;k++){
				ram2stu(k);
#if FRI_flag
				if(*ps_58_62=='P') str1[0]='\0'; else str1[0]='Z';
				if(*ps_=='\0' && *ps_58_16=='*') copy("ZZZZZ",&str1[1],5);
				else copy(ps_,&str1[1],len_);
#else
				copy(ps_,str1,len_);
#endif
				ram2stu(k+1);
				if(test_line()){
#if FRI_flag/* van hoog naar laag sorteren */
					if(*ps_58_62=='P') str2[0]='\0'; else str2[0]='Z';
					if(*ps_=='\0' && *ps_58_16=='*') copy("ZZZZZ",&str2[1],5);
					else copy(ps_,&str2[1],len_);
					if(cmp_srt(str1,str2,len_+1)==-1){
#else
					if(cmp_srt(str1,ps_,len_)==1){
#endif
						ram2stu(k);
						copy(s(58,1),sortbuf,fldlen(58,0));
						ram2stu(k+1);
						stu2ram(k);
						copy(sortbuf,s(58,1),fldlen(58,0));
						stu2ram(k+1);
						sw=YES;
					}
				}
			}
			if(sw==NO) break;
		}
		beg_=b_end_+1;
	}
}
#endif



static SortBonIndex()
{
  int16 j,k,len_,sw,max_;
  char str1[35],str2[35],*ps_;
 
  len_=len58_15;ps_=ps_58_15;
#if SORT_FLD
  if(fldlen(58,SORT_FLD)){len_=fldlen(58,SORT_FLD);ps_=s(58,SORT_FLD);}
#endif
	for(k=0;k<DIM58;k++) Ix58[k]=-1;
  max_=max_line-1;
  for(max_;max_>=0;max_--){ram2stu(max_); if(test_line()) break;}
	max_++;
  for(k=0;k<max_;k++){
    ram2stu(k);
    if(test_line()==NO){
      copy(s(58,1),sortbuf,fldlen(58,0));
      for(j=k;j<max_;j++){
				ram2stu(j+1);
				stu2ram(j);
      }
      copy(sortbuf,s(58,1),fldlen(58,0));
      stu2ram(max_); max_--;
    }
		Ix58[k]=k;
  }
  for(k=0;k<max_;k++) {
    ram2stu(k); if(*ps_58_62=='S' && *ps_58_16=='*'){max_=k-1; break;}
  }
  FOREVER{/* sorteren */
    sw=NO;
    for(k=0;k<max_;k++){
      ram2stu(Ix58[k]);
      copy(ps_,str1,len_);
      ram2stu(Ix58[k+1]);
      if(test_line()){
 				if(cmp_srt(str1,ps_,len_)==1){
					j=Ix58[k];Ix58[k]=Ix58[k+1];Ix58[k+1]=j;
					sw=YES;
				}
      }
    }
    if(sw==NO) break;
  }
}



static cmp_srt(p1,p2,len)
char *p1,*p2;
int16 len;
{
  while(len--){
    if(*p1>*p2) return 1;
    if(*p1<*p2) return -1;
    p1++;p2++;
  }
  return 0;
}



#if INTRASTAT & (FLAG244 | !BONFILE)
static fill_intra()
{
  int16 k,art_det;
  double intra_gew;
  long rekenc;
					
  intra_gew=0;
  for(k=0;k<max_line;k++){
    ram2stu(k);
    copy(s(58,30),s(4,48),sizeof bkh_intras[0]);art_det=NO;
    if(*pd_58_35){
      if(art_exist && *u(58,14) && *ps_58_16!='*'){
				art_det=YES;
				fasinit(6);*u(6,1)=*u(58,14);fasgeti(6);
#if FLAGBSA
				*d(4,55)=*f(6,37)* *pf_58_31; // gewicht :  gewone inhoud
				*d(4,56)=*pf_58_31; // anders gewone inhoud

#else
				if(fldlen(6,87)) *d(4,55)=*d(6,87)* *pf_58_31; // als intr.gewicht bestaat, dat dit nemen
				else if(fldlen(6,38)) *d(4,55)=*f(6,38)* *pf_58_31; // anders gewone gewicht
				if(fldlen(6,88)) *d(4,56)=*d(6,88)* *pf_58_31; // als aanv. eenheden bestaat, dan dit nemen
				else if(fldlen(6,37)) *d(4,56)=*f(6,37)* *pf_58_31; // anders gewone inhoud
#endif
      }
      if(*s(4,54)=='\0'){
				*i(4,48)=intr_stel;
				copy(s(2,74),s(4,49),fldlen(4,49));
				*i(4,51)=*i(2,75);
				*i(4,53)=*i(2,77);
				if(fldlen(4,57)) copy("BE",s(4,57),2);
				if(art_det){
					copy(s(6,86),s(4,54),fldlen(4,54));
				}
				else {
					rekenc=makegrb();
					if(sear_grb(rekenc)==60000){
						errnum=0;
						sear_grb(grb_notf);
					}
					copy(s(3,14),s(4,54),8);
				}
      }
      copy(s(4,48),s(58,30),sizeof bkh_intras[0]);
      intra_gew+=*d(4,55);
    }
    stu2ram(k);
  }
}
#endif

#if INTRASTAT
static upd_intra()
{
  int16 lin_=0,k,z,key;
	
  FOREVER{
    redo:;
    ram2stu(lin_);copy(s(58,30),s(4,48),sizeof bkh_intras[0]);
    scrget(2,35);z=1;
    k=lin_+1;scrifld(z++,fm_ou3,&k);
    scrofld(z++,58,15,-1); scrofld(z++,58,16,-1);
    scrofld(z++,58,31,-1);
    scrofld(z++,58,35,-1);
    for(k=48;k<=57;k++) scrfld(z++,4,k);
    key=scrupd(1,0xA7);
    if(key==106){ram2stu(lin_); goto redo;}
    copy(s(4,48),s(58,30),sizeof bkh_intras[0]);
    stu2ram(lin_);
    if(key==102){lin_--;if(lin_<0) lin_=0;}
    if(key==103){lin_++;if(lin_>=max_line) lin_--;}
    if(key==101 || key==108) break;
  }
}
#endif

#if INTRASTAT | (BOEKALLO & BOEKEXEC)
static long makegrb()
{
  int16 g,gg,kk;
  long rekenc;
  char reken[10];
 
  if(fldlen(58,26) && *l(58,26) && *s(58,26)!=0xFF ) rekenc=*l(58,26);
  else{
    zero(reken,sizeof reken);
    copy(b3598,reken,6);
#if FLAGAST
		if(*s(2,71)=='J') copy("709",reken,3); // BTW-eenheid
#endif
#if FLAGSCE
		if(SCE_kassaFT) copy("702",reken,3); // van herinlezen facturen
#if KASINPUT || KASSAFACTUUR || KAS2JMCFACTUUR // kassafacturen op 702
		copy("702",reken,3);
#endif
#endif

#if FLAGPED                             /* afhaalvergoeding op 74-rekening */
    if(*ps_58_25=='9') reken[1]='4';
#endif
    for(g=0;g<10;g++) if(reken[g]=='\0') break;
#if FLAGDU4
		if(*u(8,48)>=1 && *u(8,48)<=9) reken[g-1]='0'+*u(8,48);  // verkopen apart per filiaal 700xxxx 701xxxx, ....
#endif
#if EXPBTW01 // bij exportfactuur prefix 70, 700,... vervangen door 71, 701, ... 
#if FLAGAST
		if(*s(2,71)!='J'&& (*s(8,26)=='J' || btw_glob==0) && g) reken[g-1]='1';// niet bij BTW-eenheid
#else
		if((*s(8,26)=='J' || btw_glob==0) && g) reken[g-1]='1';
#endif
#endif
#if HOE_flag && (KASINPUT || KAS2FACT)/* boeken op 701xxx, 702xxx...(per kassa) */
    if(sys2696 && inq_kassa){/* enkel bij kleinhandel */
      if(g) stcli_d(&reken[g-1],(long)inq_kassa,1,0);
    }
#endif
#if FT_ACC_FREE
#if FLAGSMM
			if(*s(2,22) && g) reken[g-1]='1'; // gewoon eu = 701xxx
#endif
		if(fldlen(2,88) && *s(2,88)=='J'){ // aparte rekening boeken (71 of 701)
#if FLAGSMM
			if(g>1) reken[g-1]='2'; // acc vrij eu = 702xxx
#else 
			if(g>1) reken[g-1]='1';
#endif
		}
#endif
    if(fldlen(2,25)){
      copy(s(2,25),&reken[g],fldlen(2,25));
      for(g=0;g<10;g++) if(reken[g]=='\0') break;
    }
    if(len58_25){
      copy(ps_58_25,&reken[g],len58_25);
      for(g=0;g<10;g++) if(reken[g]=='\0') break;
    }
    if(b3604){
      stcli_d(&reken[g],(long)*i(58,34),b3604,0);
      g+=b3604;
    }
    if(b3606){
      kk=*pf_58_24;gg=*pf_58_24*10 - kk*10;/* gg = decimaal */
//#if EXPBTW01
//      if(*s(8,26)=='J'){kk=1;gg=0;}
//#endif
      stcli_d(&reken[g],(long)kk,2,0);
#if FLAGKEE
			stcli_d(&reken[g]+2,(long)(*u(8,48)),2,0); // SPECIFIEK rekening + filiaal erachter
#endif
      if(gg && b3606==2) stcli_d(&reken[g]+2,(long)gg,1,0);/* decimaal */
    }
//#if FLAGSHN
//		if(*f(58,24)==0 && *s(58,25)=='9') copy("460000",reken,7); // eigen cadeaubon
//#endif
    grb_comp(reken,&rekenc);
  }
  return (long)rekenc;
}
#endif

#if BOEKALLO & BOEKEXEC
static initrec(stu_)
int16 stu_;
{
  fasinit(stu_);
  *s(stu_,2)=journl;
  *u(stu_,3)=ft_nr;
  *u(stu_,4)=ft_date;
}
#endif




#if KASINPUT
static add_nklant()/* nieuwe klanten met code 99999999 toevoegen  */
{
  int16 mode_=0,j,k,len_,dd_,mm_,jj_;
  uint16 dt_,rec_,bon_ok_,bnr_;
  long pos_,min_kod_=1,max_kod_,lbd_;
  char str_[50];

  scrget(1,170);fasunlck(-2);
  scrifld(7,fm_os63,"Controleren/toevoegen nieuwe klanten ...");scrupd(-3,0);
  zero(str_,sizeof str_); fasclos(-2);
  if(inq_kassa){
    copy("kassa-00",str_,8);stcli_d(&str_[6],(long)inq_kassa,2,0);str_[8]=0x5C;
    copy("KASFAC.DAT",&str_[9],11);
    mk_name(3936,str_);
  }
  else sysget(4572,32,filnam);
	fasclos(-2);SeqiMode=3;
  if(errnum=fasopen(filnam,3)) goto endsr;
	
  fasinit(80);*l(80,1)=begfpos;
  FOREVER{
    next_bon:;
    if(read_rec(mode_)) goto endsr;
    mode_=1;
#if BOEKKASF
    if(cmp_str(rec_ele(0),"K1",2)==NO || cmp_str(rec_ele(0),"F1",2)==NO){
#else
    if(cmp_str(rec_ele(0),"L1",2)==NO){
#endif
      pos_=*pl_80_1;
      FOREVER{
				if(read_rec(1)) goto endsr;
				if(cmp_str(rec_ele(0),"H1",2)==NO){
					dd_=val(rec_ele(1));
					mm_=val(rec_ele(1)+3);
					jj_=val(rec_ele(1)+6);
					dt_=datejd(jj_,mm_,dd_);
					bnr_=get_num(2);
#if BOEKKASF
					if(bnr_<=last_vf) goto next_bon;
#endif
					if(dt_bon_beg && dt_<dt_bon_beg) goto next_bon;
					if(dt_bon_end && dt_>dt_bon_end) goto next_bon;
				}
				if(cmp_str(rec_ele(0),"H2",2)==NO) break;
      }
      if(cmpstr(rec_ele(1),"99999999",8)) goto next_bon;/* enkel nieuwe klanten */
			fasinit(2);
      for(j=2;j<6;j++){
				len_=sele_len(j);if(len_>fldlen(2,j+1)) len_=fldlen(2,j+1);
				copy(rec_ele(j),s(2,j+1),len_);
				if(len_<fldlen(2,j+1)){/* rest van veld uitvegen */
					zero(s(2,j+1)+len_,fldlen(2,j+1)-len_);
				}
      }
      if(faskeyi(2,2,0)==0){// klant bestaat en indien aangemaakt in ovl290, dan hier telefoon toevoegen (die info is daar niet)
		    len_=sele_len(6);if(len_>fldlen(2,8)) len_=fldlen(2,8);
			  if(len_ && *s(2,8)=='\0') {
					copy(rec_ele(6),s(2,8),len_);
		      if(len_<fldlen(2,8))zeros(s(2,8)+len_,fldlen(2,8)-len_); // rest van veld uitvegen 
	  			fasupd(2);	
				}
				goto next_bon;
			}
			fasinit(2);
      for(j=2;j<6;j++){
				len_=sele_len(j);if(len_>fldlen(2,j+1)) len_=fldlen(2,j+1);
				copy(rec_ele(j),s(2,j+1),len_);
				if(len_<fldlen(2,j+1)){/* rest van veld uitvegen */
					zero(s(2,j+1)+len_,fldlen(2,j+1)-len_);
				}
      }
      len_=sele_len(6);if(len_>fldlen(2,8)) len_=fldlen(2,8);
      copy(rec_ele(6),s(2,8),len_);
      if(len_<fldlen(2,8)){/* rest van veld uitvegen */
				zeros(s(2,8)+len_,fldlen(2,8)-len_);
      }
      get_btw(rec_ele(7),ele_len(7));
      if(fldlen(2,36) && *i(2,36)==0) *i(2,36)=def_qfact;
      copy(s(2,1),buf1000,fldlen(2,0));
      if(fldlen(2,2)){/* automatisch codenummer zoeken 9xxxx */
				fasinit(2);
				max_kod_=9;min_kod_=9; for(k=0;k<fldlen(2,2)-1;k++) {min_kod_*=10;max_kod_=max_kod_*10+9;}
				for(lbd_=min_kod_;lbd_<max_kod_;lbd_++){
					fasinit(2);
					stcli_d(s(2,2),lbd_,fldlen(2,2),0);
					if(faskeyi(2,1,0)) break;
				}
				stcli_d(str_,lbd_,fldlen(2,2),0);
      }
      copy(buf1000,s(2,1),fldlen(2,0));
      if(fldlen(2,2)) copy(str_,s(2,2),fldlen(2,2));
      if(fldlen(2,36)>0) *u(2,36)=def_qfact;
      // if(fldlen(2,44)>0) *s(2,44)='J';
      if(fldlen(2,25)) *s(2,25)='0';
#if FLAGEET
      if(fldlen(2,25)) *s(2,25)='1';
#endif
      if(fasadd(2)) break;/* probeer toe te voegen */
      scrfld(10,2,3);scrupd(-3,0);
    }
  }
  endsr:;
}

static sele_len(nr_)
int16 nr_;
{
  int16 len_;
  char *p;
					
  len_=ele_len(nr_);
  p=rec_ele(nr_)+len_-1;
  for(len_;len_>0;len_--) if(*p--!=' ') break;
  return len_;
}
#endif
 
#if KASINPUT
static searc_bon(k_sear_)/* NO : situeren van alle bons voor dezelfde code klant */
int16 k_sear_;/* YES : situeren van alle klanten */
{
  int16 mode_=0,j,k,len_,dd_,mm_,jj_;
  uint16 dt_,rec_,bon_ok_,bnr_,nrec_;
  long pos_;
  char str_[50],ncode_[10];

  for(k=0;k<sizeof fil_pos/sizeof fil_pos[0];k++) fil_pos[k]=-1;

  zero(str_,sizeof str_); fasclos(-2);
  if(inq_kassa){
    copy("kassa-00",str_,8);stcli_d(&str_[6],(long)inq_kassa,2,0);str_[8]=0x5C;
    copy("KASFAC.DAT",&str_[9],11);
    mk_name(3936,str_);
  }
  else sysget(4572,32,filnam);
	fasclos(-2);SeqiMode=3;
  if(errnum=fasopen(filnam,3)) goto endsr;
	
  fasinit(80);*l(80,1)=begfpos;
  for(k=0;k<50;k++){
    FOREVER{
      next_bon:;
      if(read_rec(mode_)) goto endsr;
      mode_=1;
#if BOEKKASF
      if(cmp_str(rec_ele(0),"K1",2)==NO || cmp_str(rec_ele(0),"F1",2)==NO){
#else
      if(cmp_str(rec_ele(0),"L1",2)==NO){
#endif
	pos_=*pl_80_1;
	FOREVER{
	  if(read_rec(1)) goto endsr;
	  if(cmp_str(rec_ele(0),"H1",2)==NO){
	    dd_=val(rec_ele(1));
	    mm_=val(rec_ele(1)+3);
	    jj_=val(rec_ele(1)+6);
	    dt_=datejd(jj_,mm_,dd_);
	    bnr_=get_num(2);
#if 0
#if BOEKKASF
	    if(bnr_<=last_vf) goto next_bon;
#endif
#endif
	    if(dt_bon_beg && dt_<dt_bon_beg) goto next_bon;
	    if(dt_bon_end && dt_>dt_bon_end) goto next_bon;
	  }
	  if(cmp_str(rec_ele(0),"H2",2)==NO) break;
	}
	bon_ok_=NO;
	zero(ncode_,sizeof ncode_);nrec_=0;
	if(cmpstr(rec_ele(1),"99999999",8)==0){
	  if(k) goto next_bon;/* nieuwe klant : bon per bon  */
	  copy(s(2,1),buf1000,fldlen(2,0));
	  len_=sele_len(2);if(len_>fldlen(2,3)) len_=fldlen(2,3);
	  copy(rec_ele(2),s(2,3),len_);
	  len_=sele_len(3);if(len_>fldlen(2,4)) len_=fldlen(2,4);
	  copy(rec_ele(3),s(2,4),len_);
	  if(faskeyi(2,2,0)==0){
	    copy(s(2,2),ncode_,fldlen(2,2));nrec_=*u(2,1);
	  }
	  copy(buf1000,s(2,1),fldlen(2,0));
	}
	if(fldlen(2,2) && nrec_==0){
	  if(*s(2,2)=='\0' || cmp_cod(rec_ele(1),s(2,2),fldlen(2,2))==NO || cmpstr(s(2,2),ncode_,fldlen(2,2))==0){
	    bon_ok_=YES;
	  }
	}
	else{
	  rec_=get_num(1);
		if(rec_==0){
			copy(s(2,1),buf1000,fldlen(2,0));
			fasinit(2);
			len_=sele_len(2);if(len_>fldlen(2,3)) len_=fldlen(2,3);
			copy(rec_ele(2),s(2,3),len_);
			if(faskeyi(2,2,0)) fasinit(2);
			rec_=*u(2,1);
			copy(buf1000,s(2,1),fldlen(2,0));
		}
	  if(*pu_2_1==0 || *pu_2_1==rec_ || *pu_2_1==nrec_){
	    if(nrec_) *pu_2_1=nrec_; else *pu_2_1=rec_;bon_ok_=YES;
	  }
	}
	if(k_sear_ || bon_ok_){
	  if(nrec_){
	    fasinit(2);*pu_2_1=nrec_;fasgeti(2);
	  }
	  else{
	    if(fldlen(2,2)){/* probeer zoeken op nummer */
	      len_=ele_len(1);if(len_>fldlen(2,2)) len_=fldlen(2,2);
	      copy(rec_ele(1),s(2,2),len_);
	      if(faskeyi(2,1,0)) fasinit(2);
	    }
	    else{
	      *pu_2_1=get_num(1);
			 	if(*u(2,1)==0){
					fasinit(2);
					len_=sele_len(2);if(len_>fldlen(2,3)) len_=fldlen(2,3);
					copy(rec_ele(2),s(2,3),len_);
					if(faskeyi(2,2,0)) fasinit(2);
				}
 	      if(fasgeti(2)) fasinit(2);
	    }
	  }
	}
	if(fldlen(2,33)){
	  if(ft_tijdstp && ft_tijdstp!=*s(2,33)){
	    fasinit(2); goto next_bon;
	  }
	}
	if(k_sear_){
	  for(j=0;j<DIM58;j++) if(rec_58[j]==0 || *pu_2_1==rec_58[j]) break;
	  rec_58[j]=*pu_2_1; fasinit(2);
	  goto next_bon;
	}
	if(bon_ok_){
	  for(j=2;j<6;j++){
	    len_=sele_len(j);if(len_>fldlen(2,j+1)) len_=fldlen(2,j+1);
	    copy(rec_ele(j),s(2,j+1),len_);
	    if(len_ && len_<fldlen(2,j+1)){/* rest van veld uitvegen */
	      zeros(s(2,j+1)+len_,fldlen(2,j+1)-len_);
	    }
	  }
	  len_=sele_len(6);if(len_>fldlen(2,8)) len_=fldlen(2,8);
	  copy(rec_ele(6),s(2,8),len_);
	  if(len_<fldlen(2,8)){/* rest van veld uitvegen */
	    zeros(s(2,8)+len_,fldlen(2,8)-len_);
	  }
	  get_btw(rec_ele(7),ele_len(7));
	  if(fldlen(2,36) && *i(2,36)==0) *i(2,36)=def_qfact;

	  fil_pos[k]=pos_;
	  if(cmpstr(rec_ele(1),"99999999",8)==0){/* nieuwe klant : 1 bon */
	  /* zero(s(2,2),fldlen(2,2)); */ goto endsr;
	  }
#if NO_KASKLTADR
	  else fasgeti(2);
#endif
	  break;
	}
      }
    }
#if KMP_flag || BOEKKASF
    break;
#endif
  }
  endsr:;
  if(fil_pos[0]>=0) return YES;
  else return NO;
}
 
static find_art(beg_,end_)
int16 beg_,end_;
{
  int16 k;
  char *ps_;

  for(k=beg_;k<end_;k++){
    ps_=ram+(k*stu58_len)+(s(58,15)-s(58,1));
    if(cmp_str(ps_58_15,ps_,len58_15)) goto next;
    ps_=ram+(k*stu58_len)+(s(58,16)-s(58,1));
    if(cmp_str(ps_58_16,ps_,fldlen(58,16))) goto next;
    ps_=ram+(k*stu58_len)+(s(58,20)-s(58,1));
    if(*pf_58_20 !=*(float *)ps_) goto next;
/*  if(cmp_str(s(58,20),ps_,fldlen(58,20))) goto next; */
    return k;/* match found */
    next:;
  }
  return NO;
}
 
static q_det(pos_)
long pos_;
{
  int16 fuval=0,mode_=0;
 
  fasinit(80);*pl_80_1=pos_;
  FOREVER{
    if(read_rec(mode_)) break;
    mode_=1;
    if(*rec_ele(0)=='T') break;
    else if(*rec_ele(0)=='R') fuval++;
  }
  fasinit(80);*pl_80_1=pos_;read_rec(0);
  return fuval;
}


#endif
 
#if FLAG244 & BONFILE & !SAMENVOEGEN & !WEB_ADD & !PDA_LGRETOUR
static kil_ALLbon()
{
	char dcode_[4];
  int16 z,key,stu_=8,g;
  uint16 n;
  
	zero(dcode_,sizeof dcode_);dt_bon_end=*u(25,2);
	FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,6,5,0);scraddf(z++,6,49,2);
		scraddf(z++,8,5,0);scraddf(z++,8,49,2);
		scraddf(z++,23,1,8);scraddf(z++,23,16,8);
		z=1;
    scrifld(z++,fm_os79,"Geef de code van dit dossier (beveiliging) : ");
    scrifld(z++,fm_us3U,dcode_);
    scrifld(z++,fm_os79,"Schrappen tot en met ..................... : ");
    scrifld(z++,fm_udat,&dt_bon_end);
    scrifld(z++,fm_os14," F1 stop");scrifld(z++,fm_os14," F8 ga verder");
    key=scrupd(1,0x81);
    if(key==101) goto endsr;
		if(cmpstr(dcode_,s(25,3),fldlen(25,3))) goto endsr;
    if(key==108) break;
	}
	if(DisplayWarning("Wenst U echt ALLE BONS TE SCHRAPPEN ??? ONHERROEPELIJK !!!!",605,1)==NO) goto endsr;
  if(scr_ok("Moet U nog facturen drukken van deze bons ?")==YES) goto endsr;
  stu_=8; scrget(1,7);scrupd(-3,0);fasunlck(-2);
  redo_stu:;
  fasinit(stu_); n=0;
  FOREVER{
    *u(stu_,1)=++n;
    g=fasgetu(stu_);
    if(g==47)break;
    if(g!=46){
			if(stu_==8){
  			if(*u(8,8)<=dt_bon_end) faskill(stu_);/* deleted record */
			}
			else{
				fasinit(8); *u(8,1)=*u(58,2); 
				if(fasgeti(8)) faskill(stu_);/* deleted record */
			}
		}
  }
  if(stu_==8){stu_=58;goto redo_stu;}
  fasinfo(8,101);fasflush(0);

  endsr:;
}
#endif
 
#if FLAGOPS | FLAGEPD | FLAGSMM
static cmp_dblart()/* zelfde artikels samentellen */
{
  int16 k,kk,compress_;
  uint16 rec_r,rec_;
  float aant_,hlkrt_r;
  char stk_r='\0',stk_='\0';

  for(k=0;k<max_line;k++){
    ram2stu(k);
		
		prx_r=*pf_58_20;kort_r=*pf_58_21;rec_r=*pu_58_14;
		if(fldlen(58,62)) fles_r=*s(58,62);
		lgprx_r=*f(58,46);lgrec_r=*u(58,48);lgaant_r=*f(58,49);
		if(fldlen(58,36)) hlkrt_r=*f(58,36);
    if(rec_r){
      for(kk=k+1;kk<max_line;kk++){
				ram2stu(kk);
				compress_=YES;
				if(prx_r!=*pf_58_20 || kort_r!=*pf_58_21) compress_=NO;
				if(fldlen(58,36) && hlkrt_r!=*f(58,36)) compress_=NO;
				if(rec_r!=*pu_58_14 || lgprx_r!=*f(58,46)) compress_=NO;
				if(lgrec_r!=*u(58,48) || lgaant_r!=*f(58,49)) compress_=NO;
				if(fldlen(58,62) && *s(58,62)!=fles_r) compress_=NO;
				if(compress_){
					aant_=*f(58,7);
					ram2stu(k);*f(58,7)+=aant_; stu2ram(k);
					ram2stu(kk);
					rec_=*pu_58_1;/* lijn deleten */
					init58(kk,YES);
					ram2stu(kk);
					*pu_58_1=rec_;
					stu2ram(kk);
				}
      }
    }
  }
  calc();
}
#endif
 
static scr_ok(ptxt)
char *ptxt;
{
  int16 key;

  scrget(1,169);
  scrifld(12,fm_os79,ptxt);
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  return NO;
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

static set_allbtw(tar_)
float tar_;
{
  int16 k;

  for(k=0;k<max_line;k++){
    ram2stu(k);
    *pf_58_24=tar_;
    stu2ram(k);
  }
	BtwLeveringskost=tar_;
}

static ftchk()
{
  int16 curs_=0;

#if FLAG248
  if(ft_nr<1){errnum=38;curs_=1;goto endsr;}
#endif
#if BOEKALLO & BOEKEXEC & !FT_HERAFDRUK
  if(last_arc){
    if(ft_date<=last_arc) {errnum=37;goto endsr;}
//    if((sys1862 & 8)==0) if(ft_date>last_arc+600) {errnum=61;goto endsr;}
  }
	if(MinBkhDatum){
    if(ft_date<=MinBkhDatum) {errnum=37;goto endsr;}
    if(ft_date>(*u(25,2)+10) || ft_date>(MinBkhDatum+600)) {errnum=61;goto endsr;}
  }
  if(yet_booked(journl,ft_nr,ft_date)){errnum=59;curs_=1;goto endsr;}
#endif
  endsr:;
  return curs_;
}

#if BOEKALLO & BOEKEXEC
static flag yet_booked(jrnl_,volgnr_,dt_)
int16 jrnl_;
uint16 volgnr_,dt_;
{
  int16 fkey_,jj,mm,dum;
  uint16 dt_beg,dt_end;
							
  if(sys1862 & 0x10) return NO;
  jddate(dt_,&jj,&mm,&dum);
  FOREVER{
    dt_end=datejd(++jj,mnd_strt,1);
    dt_beg=datejd(--jj,mnd_strt,1);
    if(dt_>=dt_beg) break;
    jj--;
  }
  fasinit(4);*s(4,2)=jrnl_;*u(4,3)=volgnr_;fkey_=1;
  FOREVER{
    if(faskeyi(4,1,fkey_)) break;fkey_=2;
    if(*s(4,2)!=jrnl_ || *u(4,3)!=volgnr_) break;
    if(*u(4,4)>=dt_beg && *u(4,4)<dt_end) return YES;
  }
  return NO;
}
#endif

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

static fileopen(nr_)
int16 nr_;
{
  int16 stu_;
  char filename[15];

  nr_--;
  sysget(300+17*nr_,15,filename);
  sysget(315+17*nr_,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(errnum=fasopen(filename,0)) exit_hfdmenu();
    if(stu_==1) {lvcd=YES; if(faskeyi(1,1,0)==45) lvcd=NO;}
    if(stu_==2) {klcd=YES; if(faskeyi(2,1,0)==45) klcd=NO;
      if(fldlen(2,57) || fldlen(2,58)) k_omz_exist=YES;
    }
    if(stu_==4) bkh_exist=YES;
    if(stu_==6) art_exist=YES;
#if HISTOR
    if(stu_==10) hist_exist=YES;
#endif
  }
}

static is_nul(bd_)
double bd_;
{
  if(bd_<0) bd_=-bd_;
  if(bd_<0.009) return YES;
  else return NO;
}

#if FILETXT
static inp_clr()
{
  fasinit(80); stu_80_ix=200;
}

static get_byte()
{
  if(stu_80_ix==200){
    fasseqi(80,1,200+4);
    stu_80_ix=0;
  }
  return (int16) *(s(80,1)+4+stu_80_ix++);
}
#endif

#if INTRASTAT | (BOEKALLO & BOEKEXEC)
static uint16 find_grb(rek_)
long rek_;
{
  uint16 fuval;

#if BOEK_EXTERN/* niet zoeken in grb.fas */
  if(fldlen(3,0)==0){
    if(rek_==-1) return 60000;
    else return 60001;
  }
#endif
  fuval=sear_grb(rek_);
  if(errnum) tb_grbnotfound[notfound++]=rek_;
  return fuval;
}
#endif
		
#if INTRASTAT | (BOEKALLO & BOEKEXEC)
static uint16 sear_grb(rek_)
long rek_;
{
#if BOEK_EXTERN                                   /* niet zoeken in grb.fas */
  if(fldlen(3,0)==0){
    if(rek_==-1) return 60000;
    else return 60001;
  }
#endif
  fasinit(3);*l(3,2)=rek_;
  search(3,2);
  return (uint16)(*u(3,1)+60000);
}
#endif

static ram2stu(lin_)
int16 lin_;
{
  copy(ram+(lin_*stu58_len),s(58,1),stu58_len);
}
						
static stu2ram(lin_)
int16 lin_;
{
  copy(s(58,1),ram+(lin_*stu58_len),stu58_len);
}

static fld_test(nr_,stu_,elet_)
int16 nr_,stu_,elet_;
{
  if(fldlen(stu_,elet_)) scrfld(nr_,stu_,elet_);
  else streepje(nr_);
}

static streepje(nr_)
int16 nr_;
{
  scrifld(nr_,fm_os2,"--");
}

static cmp_str(p1,p2,len)
int16 len;
char *p1,*p2;
{
  while(len--){
    if(*p1++!=*p2++)return 1;
  }
  return 0;
}

static BEDRAG integ(value_)
double value_;
{
  double afrond_;

  afrond_=.501; if(value_<0) afrond_=-.50;
  return (BEDRAG)(long)(value_+afrond_);
}

static skip_lin(line_)
int16 line_;
{
  if((line_+skip_off)>0){
    while(free>(line_+skip_off)) nextline();
  }
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
static prt_string(string)
char *string;
{
  char *_string;
  int16 len;

  len=0; _string=string;
  while (*_string++) len++;
  prt_bin(string,len);
}

static prt_bin(string,len)
char *string;
int16 len;
{
  char fm[8];
 
  fm[0]=7; fm[1]=0x88; fm[2]=len%256; fm[3]=len/256; fm[4]=0; fm[5]=0; fm[6]=0;
  if (len>0) prtifld(fm,string,-2);
}

#if ARTEXIST
static uint16 hash()
{
  char *ps;
  int16 k;
  uint16 fuval=0;

  k=hash_len;ps=s(58,14);
  while(k--) fuval=fuval*3+*(ps++);
  k=len58_62;ps=ps_58_62;
  while(k--) fuval=fuval*3+*(ps++);
  return fuval;
}
#endif

// Sequentiele routines ++++++++++++++++++++++++++++++

static read_rec(mode_)
int16 mode_;
{
  int16 j;
  flag eof_=NO;
  long pos_;

  if(mode_){
    for(j=0;j<256;j++) if(*(p_data+j)==0x0A || *(p_data+j)=='\0') break;
    if(*(p_data+j)==0x0A || *(p_data+j)=='\0') *pl_80_1+=(j+1);
    zeros(p_data,256);
  }
  pos_=*pl_80_1;
  if(fasseqi(80,SeqiMode,256)) {eof_=YES;}
  if(eof_ && *p_data=='\0') return YES;
  else{/* positioneer terug op eerste karakter */
    *pl_80_1=pos_;
    return NO;
  }
}

static float get_num(nr)                           /* read number starting at pos  */
int16 nr;
{
  int16 j=0,k=0,n;
  float val_=0,val1_;
  flag na_komma=NO,neg_get=NO;
  char *pos;
									
  pos=rec_ele(nr);
  FOREVER{
    if(*(pos+k)==FieldSeparator || *(pos+k)==0x0D) break;
#if KASINPUT || PDA_LGRETOUR || PDA_TRACEER/* facturatie van kassa-facturen kan allebei voorkomen */
    if(*(pos+k)=='.' || *(pos+k)==',') na_komma=YES;
#else
    if(*(pos+k)==KommaKarakter) na_komma=YES;
#endif
    else if(*(pos+k)=='-') neg_get=YES;
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
				if(na_komma==NO){
					val_=val_*10 + (*(pos+k)-'0');
				}
				else{
					j++;
					val1_=*(pos+k)-'0';
					for(n=0;n<j;n++) val1_=val1_/10;
					val_+= val1_;
				}
      }
    }
    k++;
  }
  if(neg_get) return (float) -val_;
  else return (float) val_;
}

static char *rec_ele(nr_)
int16 nr_;
{
  int16 k;
  char *p;
						
#if WEB_ADD
  p=p_buf1000;
#else
  p=p_data;
#endif
  for(k=0;k<nr_;k++){
    FOREVER{
      if(*p==FieldSeparator || *p==0xD || *p=='\0') break;
      p++;
    }
    p++;
  }
  return p;
}

static ele_len(nr_)
int16 nr_;
{
  int16 k=0;
  char *p;
								
  p=rec_ele(nr_);
  FOREVER{
    if(*p==FieldSeparator || *p==0x0D || *p==0x0A || *p=='\0') return k;
    p++;k++;
  }
}

static get_str(ps_,nr_,mlen_)
char *ps_,nr_;
int16 mlen_;
{
  int16 j,k,len_,add_,dbl_quot_;
  char *pos_,last_kar_;
						
  len_=ele_len(nr_);if(len_>mlen_) len_=mlen_;
  if(len_==0) return 0;
  pos_=rec_ele(nr_);dbl_quot_=NO;

  j=0;last_kar_='\0';
  for(k=0;k<len_;k++){
    add_=YES;
    if(add_ && *pos_==' ' && j==0) add_=NO;/* leading blancs */
    if(add_ && *pos_=='"' && last_kar_=='"') add_=NO;/* dubbel quotes */
    if(add_){*(ps_+j)=*pos_;last_kar_=*pos_;j++;}
    pos_++;
  }
  for(len_=j-1; len_>=0;len_--){/* trailing blancs */
    if(*(ps_+len_)!=' ') break; else *(ps_+len_)='\0';
  }
  if(dbl_quot_ && *(ps_+len_)=='"') {*(ps_+len_)='\0'; len_--;}
  len_++;
  CnvJamaChar(ps_,len_,1);
  return len_;
}

static uint16 get_date(nr)              /* read date DD/MM/JJJJ starting at pos  */
int16 nr;
{
  int16 k=0,getal_[3],p_getal_;
  uint16 dt_=0;
  char *pos;
									
  zero(getal_,sizeof getal_);p_getal_=0;
  dt_=0; pos=rec_ele(nr); if(ele_len(nr)==0) goto endsr;
  FOREVER{
    if(*(pos+k)==FieldSeparator || *(pos+k)==0x0D) break;
    if(*(pos+k)=='/'){p_getal_++;if(p_getal_>2) break;}
    else{
      if(*(pos+k)>='0'&& *(pos+k)<='9'){
	getal_[p_getal_]=getal_[p_getal_]*10 + (*(pos+k)-'0');
      }
    }
    k++;
  }
  getal_[2]%=100;
  dt_=datejd(getal_[2],getal_[1],getal_[0]);
  endsr:;
  return (uint16) dt_;
}



// einde sequentiele routines ++++++++++++++++++++++++++++++++++++++++++

static zeros(pd,len)
char *pd;
uint16 len;
{
  while(len--) *pd++='\0';
}

static p_pdfname(naam_,dt_beg_,dt_end_) // voor lijsten 
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


static search(stu_,mod_)
{
  int16 parmbak[8],fuval;
									
  copy((char *)parmcall,(char *)parmbak,sizeof parmcall);
  zero((char *)parmcall,sizeof parmcall);
  parmcall[0]=mod_;
  if(stu_<=2) parmcall[1]=7; // bits : 0 = display, 1=update, 2=add
  else parmcall[1]=3; // GEEN ADD
#if FT_HERAFDRUK
	parmcall[1]=3; // geen add
#endif
#if NO_ART_DSP
  if(stu_==6) parmcall[1]=0;
#endif
  parmcall[2]=0;
  parmcall[3]=0;
#ifdef STRAATKEY
  if(stu_==2) parmcall[4]=STRAATKEY;
#endif
#if FT_HERAFDRUK || FLAG252 // toch geblokkeerde klanten toestaan
  parmcall[7]=0x04;
#else 
	parmcall[7]=0x0C;
#endif
  fuval=ovlcall(2900,stu_);
  copy((char *)parmbak,(char *)parmcall,sizeof parmcall);
  return fuval;
}

