/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* 0.01 03/03/10 dr1 */
#define DUM     0

static int16 q_niv=6;/* aantal niveaus incl niv. 7 (2 is dus het minimum) */

static struct _tb {
  char *hoofding;
  int16 drv_stu;/* 0=geen driver, struct# van de driver */
  int16 drv_key;/* if 0 : dan volgens recordnr. */
  int16 sta_key;/* key# in sta.fas */
} tb[] = {
	"Evol.klanten: ",
	2,2,                                             /* klt.fas, key# 2 */
	11,
	"Evol.artikel: ",
	0,0,
	13,
	"Rendement klanten periode : ",
	2,2,                                             /* klt.fas, key# 2 */
	11,
	"Rendement artikels periode : ",
	0,0,
	13,
	"Klantenomzet periode : ",
	2,2,/* klt.fas, key# 2 */
	11,
	"Artikelomzet periode : ",
	0,0,
	13,
	"Omzet per leverancier periode : ",
	0,0,
	1,
	"Klantenkortingen periode : ",
	2,2,/* klt.fas, key# 2 */
	11,
	"Klantenomzet per maand periode : ",
	2,2,/* klt.fas, key# 2 */
	11,
	"Artikelomzet per maand periode : ",
	0,0,
	13,
	//////////  DEZE LAATSTE 2 WORDEN ENKEL GENOMEN INDIEN OVL255 -- ZIE OVLCOD HIERONDER !!!!!!! ////////
	"Aankopen per leverancier periode : ",
	1,2,/* lev.fas, key# 2 */
	11,
	"Aankopen per artikel periode : ",
	0,0,
	13
};
static struct _tb *tx;

static struct {
  char naam[16];
  char fmt[16];
  uint16 pos;
  uint16 len;
  int16 breedte;
  int16 prt_kol;
  uint16 codebits;
  uint16 bloknr;
} fld[5][14] = {
  "Omschrijving",
  7,0x88,30,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,30,31,0,0,0,
  "Waarde",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,14,0,0,1,
  "Vorige per",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,14,0,0,1,
  "Evol.waarde",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,0,1,
  "Evol. %",
  6,0x95,5,2,0x60,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,9,0,0,1,
  "Stuks",
  6,0x95,8,0,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,0,2,
  "Vorige per",
  6,0x95,8,0,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,0,2,
  "Evol.stuks",
  6,0x95,8,0,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,0,2,
  "Evol. %",
  6,0x95,6,2,0x60,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,11,0,0,2,
  "Adres",
  7,0x88,30,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,30,30,0,0,3,
  "Postc.",
  7,0x88,7,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,7,7,0,0,3,
  "Plaats",
  7,0x88,25,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,25,25,0,0,3,
  "E-mail",
  7,0x88,40,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,40,40,0,0,3,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "Omschrijving",
  7,0x88,39,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,39,40,0,0,0,
  "VK-waarde",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,14,0,0,1,
  "AK-waarde",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,14,0,0,1,
  "Winst bdr",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,13,0,0,1,
  "Winst %",
  6,0x95,5,2,0x60,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,9,0,0,1,
  "Adres",
  7,0x88,30,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,30,30,0,0,2,
  "Postc.",
  7,0x88,7,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,7,7,0,0,2,
  "Plaats",
  7,0x88,25,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,25,25,0,0,2,
  "E-mail",
  7,0x88,40,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,40,40,0,0,2,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "Omschrijving",
  7,0x88,39,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,39,40,0,0,0,
  "Aantal",
  6,0x95,7,0,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,11,0,0,1,
  "Liters",
  6,0x95,9,0,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,11,0,0,1,
  "Bedrag",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,14,0,1,2,
  "Excl.acc.",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,14,0,1,2,
  "Adres",
  7,0x88,30,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,30,30,0,0,3,
  "Postc.",
  7,0x88,7,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,7,7,0,0,3,
  "Plaats",
  7,0x88,25,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,25,25,0,0,3,
  "E-mail",
  7,0x88,40,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,40,40,0,0,3,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "Omschrijving",
  7,0x88,30,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,30,31,0,0,0,
  "Aantal",
  6,0x95,7,0,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,1,
  "Liters",
  6,0x95,9,0,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,11,0,0,1,
  "Bedrag",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,14,0,0,1,
  "Excl.acc.",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,14,0,0,1,
  "Ft.kort",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,2,
  "Sem.kort",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,2,
  "Tuss.Brij",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,3,
  "Netto VW",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,14,0,1,4,
  "Netto AW",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,14,0,1,4,
  "N.winst",
  6,0x95,7,2,0x70,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,12,0,1,4,
  "Netto W%",
  6,0x95,6,2,0x60,0,0,0,0,0,0,0,0,0,0,0,
  DUM,8,10,0,1,4,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "",
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,DUM,DUM,0,0,0,
  "Omschrijving",
  7,0x88,35,0,0,0,0,0,0,0,0,0,0,0,0,0,
  DUM,30,35,0,0,0,
	"JAN",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,1,
  "FEB",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,1,
  "MAA",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,1,
  "APR",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,1,
  "MEI",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,2,
  "JUN",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,2,
  "JUL",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,2,
  "AUG",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,2,
  "SEP",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,3,
  "OKT",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,3,
  "NOV",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,3,
  "DEC",
  6,0x95,6,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,10,0,0,3,
  "TOTAAL",
  6,0x95,8,2,0x70,0,0,0,0,0,0,0,0,0,0,0,/* double*/
  DUM,8,13,0,0,4
};

extern uint16 code_seg, data_seg;

static int16 maandnr,mnd_beg,mnd_end,yy,mm,dd,fld_sel_klt=54,KltRecFld=10,KltKeyNr=11;
static char hdrbuf[15][80],skip_gratis_art='N',skip_kasverkopen='N',OnlyGratisArt='N',HerberekenSemKorting='N',StatMndAantal='N';
static char StatOpLevAdres='N',skip_leegg,buf500[500],sel_klt[10],SkipKassaFt='N';
static uint16 inq_grp=0,grp_niet[3],dat_beg,dat_end,dat_vbeg,dat_vend,inq_filiaal;
static long inq_lev=0,inq_merk=0,inq_klt=0;
static float  hl_semkort,calc_sem,brij_tpct,brij_tbd;

static int16 date2str();
ovlcod()
{
  fileopen(1);
  fileopen(2);
  fileopen(6);
  fileopen(13);
		//////////  DEZE LAATSTE 2 WORDEN ENKEL GENOMEN INDIEN OVL255  !!!!!!! ////////
	q_statist=sizeof tb/sizeof tb[0]; if(!ovltest(255)) q_statist-=2;// aankoopstatistieken NIET berekenen
  ovlcod1();
  ovlexit(-1);
}

static spec_ask(all,onlynr)
char all;
int16 onlynr;
{
  int16 j,k,key,z,curs=1,rebuild_=YES,dd1_,mm1_,jj1_,key21_exist_;
  char str_[25],str1_[25],nm_lev[50],nm_merk[50];
/* indien nodig hier de fld_msk aanpassen */
  skip_leegg='J';skip_gratis_art='N';OnlyGratisArt='N'; skip_kasverkopen='N'; SkipKassaFt='N';
  fld_msk[1]=0;
  fld_msk[2]=1;
  fld_msk[3]=1;
  fld_msk[4]=2;
  fld_msk[5]=2;
  fld_msk[6]=2;
  fld_msk[7]=3;
  fld_msk[8]=4;
  fld_msk[9]=4;
  fld_msk[10]=2;
  fld_msk[11]=2;
 
  fasinit(1);fasinit(6);fasinit(2);
  copy(s(1,3),nm_lev,fldlen(1,3));copy(s(1,3),nm_merk,fldlen(1,3));
	key21_exist_=NO; if(fldlen(16,12) && faskeyi(16,21,1)!=45) key21_exist_=YES;
 
  FOREVER{
    redo:;
    if(rebuild_){
      scraddf(-1,0,0,0);z=1;
      scraddf(z++,2,25,2);
      scraddf(z++,4,5,0);scraddf(z++,4,35,2); scraddf(z++,4,45,0);scraddf(z++,4,52,2); // periode 
      scraddf(z++,6,5,0);scraddf(z++,6,35,2);  // datum vergelijken VJ
			scraddf(z++,7, 5,0);scraddf(z++,7,35,2); // selectie leverancier
	    scraddf(z++,8, 5,0);scraddf(z++,8,35,2); // selectie merk/fabrikant
      scraddf(z++,9, 5,0);scraddf(z++,9,35,2); // selectie 1 klant
      scraddf(z++,10, 5,0);scraddf(z++,10,35,2); if(fldlen(2,fld_sel_klt)>1) scraddf(z++,10,43,0); // selectie soort cafe + eventueel selectie tekst;
			scraddf(z++,11, 5,0);scraddf(z++,11,35,2); // selectie enkel gratis artikels
			scraddf(z++,12, 5,0);scraddf(z++,12,35,2); // selectie 1 groep
			scraddf(z++,13, 5,0);scraddf(z++,13,35,2); // selectie 1 filiaal
      scraddf(z++,14, 5,0);scraddf(z++,14,40,2);scraddf(z++,14,43,2);scraddf(z++,14,46,2); // 3 groepen overslaan
			scraddf(z++,15, 5,0);scraddf(z++,15,40,2); // gratis artikels overslaan
      scraddf(z++,16, 5,0);scraddf(z++,16,40,2); // leeggoed overslaan 
      scraddf(z++,17, 5,0);scraddf(z++,17,40,2); // kasverkopen overslaan 
			scraddf(z++,18, 5,0);scraddf(z++,18,40,2); // facturen aan kassa
			scraddf(z++,19, 5,0);scraddf(z++,19,35,2); // statistiek op leveringsadres
			scraddf(z++,20, 5,0);scraddf(z++,20,35,2); // klanten sorteren op omzet
			scraddf(z++,21, 5,0);scraddf(z++,21,65,2); // sem. korting herberekenen
			scraddf(z++,22, 5,0);scraddf(z++,22,48,2); // aantallen op maandstatistiek
			scraddf(z++,23,1,8);scraddf(z++,23,11,8);  // functietoetsen 
      rebuild_=NO;
    }
    z=1;
		zero(TxtTitel,sizeof TxtTitel); k=copy0("Berekenen van statistiek : ",&TxtTitel[0],30);
		if(all=='J') copy0("ALLEMAAL",&TxtTitel[k],20); else copy0(tb[onlynr-1].hoofding,&TxtTitel[k],50);
		for(k;k<90;k++) if(cmpstr(&TxtTitel[k],"periode",7)==0){TxtTitel[k]='\0';break;}
    DisplayMenuTitel(1,TxtTitel,0xA);z++;
    scrifld(z++,fm_os79,"Periode statistieken ...... :");
    scrifld(z++,fm_udat,&dat_beg);
    scrifld(z++,fm_os9,"t.e.m.");
    scrifld(z++,fm_udat,&dat_end);
    scrifld(z++,fm_os79,"Stat.1/2 begin vergelijking :");
    scrifld(z++,fm_udat,&dat_vbeg);
    scrifld(z++,fm_os79,"Selectie 1 leverancier .... :");
    scrifld(z++,fm_us40,nm_lev);
		if(fldlen(6,101)){
			scrifld(z++,fm_os79,"Selectie 1 merk/fabrikant . :");
		 	scrifld(z++,fm_us40,nm_merk);
		} else z+=2;
    scrifld(z++,fm_os79,"Selectie 1 klant .......... :");
    scrfld(z++,2,3);
		scrifld(z++,fm_os79,"Selectie soort klant/cafe.. :");
    fmt_get(2,fld_sel_klt);scrifld(z++,fmt,sel_klt); if(fldlen(2,fld_sel_klt)>1) scrifld(z++,fm_os79,"(* = deze positie niet controleren)");
    scrifld(z++,fm_os79,"Enkel gratis artikels ..... :");
    scrifld(z++,fm_uJN,&OnlyGratisArt);
    scrifld(z++,fm_os79,"Selectie 1 groep .......... :");
    scrifld(z++,fm_uu2,&inq_grp);
		if(fldlen(8,48) && fldlen(16,8)){
      scrifld(z++,fm_os79,"Selectie 1 filiaal (1-10,99):");
      scrifld(z++,fm_uu2,&inq_filiaal);
		} else z+=2;
    scrifld(z++,fm_os79,"NIET opnemen : - artikelgroep(en):");
    scrifld(z++,fm_uu2,&grp_niet[0]);
    scrifld(z++,fm_uu2,&grp_niet[1]);
    scrifld(z++,fm_uu2,&grp_niet[2]);
    scrifld(z++,fm_os79,"               - gratis artikels :");
    scrifld(z++,fm_uJN,&skip_gratis_art);
    scrifld(z++,fm_os79,"               - leeggoed ...... :");
    scrifld(z++,fm_uJN,&skip_leegg);
    scrifld(z++,fm_os79,"               - kassaverkopen . :");
    scrifld(z++,fm_uJN,&skip_kasverkopen);
		if(fldlen(16,39)){
      scrifld(z++,fm_os79,"               - kassafacturen . :");
      scrifld(z++,fm_uJN,&SkipKassaFt);
		} else z+=2;
		if(key21_exist_){
		  scrifld(z++,fm_os79,"Statistiek op leveringsadres:");
      scrifld(z++,fm_uJN,&StatOpLevAdres);
		}
		else z+=2;
		scrifld(z++,fm_os79,"Klanten sorteren op omzet . :");
    scrifld(z++,fm_uJN,&SorteerKlantOpOmzet);
		scrifld(z++,fm_os79,"Bereken semestriele korting a.h.v. huidige prijsafspraken : ");
    scrifld(z++,fm_uJN,&HerberekenSemKorting);
		scrifld(z++,fm_os79,"Maandstatistiek : Aantallen ipv bedragen : ");
    scrifld(z++,fm_uJN,&StatMndAantal);
    scrifld(z++,fm_os9," F1 stop");scrifld(z++,fm_os13," F8 neem aan");
    key=scrupd(curs,0x81);curs=1;
    if(key==101) return YES;
    if(dat_beg==0) {curs=3;errnum=34;goto redo;}
    if(dat_end==0) {curs=5;errnum=34;goto redo;}
    if(dat_end<dat_beg) {curs=5;errnum=34;goto redo;}
    if(all=='J' || onlynr<3){
      if(dat_vbeg==0){// periode automatisch op 1 jaar eerder zetten 
        jddate(dat_beg,&yy,&mm,&dd); yy--; if(yy<0) yy=99;
        dat_vbeg=datejd(yy,mm,dd);
      } 
      if(dat_vbeg==0 || dat_vbeg>=dat_beg) {curs=7;errnum=34;goto redo;}
      dat_vend=0;
      if(dat_vbeg){
        jddate(dat_beg,&yy,&mm,&dd); 
        jddate(dat_vbeg,&jj1_,&mm1_,&dd1_);
        if(mm==mm1_ && dd==dd1_){ // eindperiode gelijkzetten 
          jddate(dat_end,&yy,&mm,&dd);yy--; if(yy<0) yy=99; dat_vend=datejd(yy,mm,dd);
        }
        if(dat_vend<dat_vbeg) dat_vend=dat_vbeg + (dat_end-dat_beg); // aantal dagen erbij tellen
        if(dat_vend>dat_beg) {errnum=34;curs=7;goto redo;}
      }
      if(dat_vend>=dat_beg) dat_vend=dat_beg-1;
    }
    if(nm_lev[0]){
      rebuild_=YES;
	    fasinit(1);copy(nm_lev,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=9;goto redo;}
	    copy(s(1,3),nm_lev,fldlen(1,3)); inq_lev=*u(1,1);
    } else inq_lev=0;
	  if(nm_merk[0]){
      rebuild_=YES;
	    fasinit(1);copy(nm_merk,s(1,3),fldlen(1,3));
      if(search(1,0)){curs=11;goto redo;}
	    copy(s(1,3),nm_merk,fldlen(1,3)); inq_merk=*u(1,1);
    } else inq_merk=0;
    
    if(*s(2,3)){
      rebuild_=YES;
      if(search(2,0)){curs=13;goto redo;}
    } else fasinit(2);
    inq_klt=*u(2,1);
    if(key!=108) goto redo;
    break;
  }
	if(StatOpLevAdres=='J'){
		KltRecFld=12; KltKeyNr=21;
	  for(k=0;k<q_statist;k++){
			if(tb[k].sta_key==11) tb[k].sta_key=21;
		}
	}
  zeros(str_,sizeof str_);
  k=date2str(str_,dat_beg);
  str_[k++]='-';date2str(&str_[k],dat_end);
  zeros(str1_,sizeof str1_);
  k=date2str(str1_,dat_vbeg);
  str1_[k++]='-';date2str(&str1_[k],dat_vend);

  for(j=0;j<q_statist;j++){
    k=copy_0(tb[j].hoofding,hdrbuf[j],sizeof hdrbuf[0]);
    k+=copy_0(str_,&hdrbuf[j][k],25);
    if(j<2){
      k+=copy_0(" tov ",&hdrbuf[j][k],5);
      k+=copy_0(str1_,&hdrbuf[j][k],25);
    }
		if((j==8 || j==9) && StatMndAantal=='J'){
			 k+=copy_0(" (aantal) ",&hdrbuf[j][k],10);
		}
    if((inq_merk || inq_lev) && k<40 && j>=2){
	  fasinit(1);if(inq_merk) *u(1,1)=inq_merk; else *u(1,1)=inq_lev; fasgeti(1);
      copy(" (",&hdrbuf[j][k],2);k+=2;
      k+=copy_0(s(1,3),&hdrbuf[j][k],7);
      hdrbuf[j][k]=')';
    }
    tb[j].hoofding=hdrbuf[j];
  }
	if(SorteerKlantOpOmzet=='J') MakeSortTabel();
	if(StatMndAantal=='J'){
		for(k=1;k<14;k++) fld[4][k].fmt[3]=0;
	}
  endsr:;
  return NO;
}

  
static exec1drv()
{
  switch(fil_nr){
    case 0 : lus001();break;
    case 1 : lus002();break;
    case 2 : lus003();break;
    case 3 : lus004();break;
    case 4 : lus005(2);break;
    case 5 : lus006(2);break;
    case 6 : lus007();break;
    case 7 : lus008();break;
    case 8 : lus009(2);break;
		case 9 : lus010();break;
    case 10 : lus005(1);break;
    case 11 : lus006(1);break;
  }
}

static lus001()
{
  int16 j,k,mode=1,len_;
  char last_code[10];
  long last_art=0xFFFF;
  flag end=NO,used=NO;
  uint16 last_grp=0xFFFF,bits;
									
  if(inq_klt && *u(2,1)!=inq_klt) goto endsr;
	if(sel_klt[0] && WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto endsr;
#if 0
  for(len_=0;len_<fldlen(2,2);len_++) if(*(s(2,2)+len_)=='\0') break;
  copy(s(2,2),get_p(6,0),len_);copy(" ",get_p(6,0)+len_,1);
#endif
  len_=(int)fld[fld_msk[fil_nr]][0].fmt[2]; CopyStrField(2,3,get_p(6,0),len_);
	CopyStrField(2,4,get_p(6,9),30);
	CopyStrField(2,5,get_p(6,10),7);
	CopyStrField(2,6,get_p(6,11),25);
  CopyStrField(2,21,get_p(6,12),40);
	
  fasinit(16); last_code[0]=0xFF;
  *l(16,KltRecFld)=*u(2,1);
  FOREVER{
    next:;
    if(faskeyi(16,tx->sta_key,mode)) end=YES; mode=2;
    dsp_working();
    if(*l(16,KltRecFld)!=*u(2,1)) end=YES;
    if(!end){
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){goto next;}
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
			if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,KltRecFld)==KasKltRec[j]){goto next;}}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
      if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(inq_lev && *u(6,7)!=inq_lev){goto next;}
	    if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(*u(16,3) <dat_beg){
				if(*u(16,3) <dat_vbeg) {*u(16,3)=dat_vbeg;mode=1; goto next;}
				if(*u(16,3) >dat_vend) {*u(16,3)=dat_beg; mode=1;goto next;}
      }
      else{
	      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF;mode=2; goto next;}
      }
    }
    if(end && used==NO) break;
    bits=0;
    if(end) bits|=0x0F;
    if(cmp_str(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
    if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;

    if(bits & 0x04){
      fasinit(6);*u(6,1)=last_art;fasgeti(6);
      for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
      copy(s(6,2),get_p(4,0),len_);copy(" ",get_p(4,0)+len_,1);
      copy(s(6,3),get_p(4,0)+len_+1,30-(len_+1));
      add_rec(4);
    }
    if(bits & 0x02){
      fasinit(52);*u(52,1)=last_grp;fasgeti(52);
      stcli_d(get_p(5,0),(long)last_grp,2,0);copy(" ",get_p(5,0)+2,1);
      copy(s(52,14),get_p(5,0)+3,15);
      add_rec(5);
    }
    last_grp=*l(16,23);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    if(end){add_rec(6);break;}
    for(k=3;k<8;k++){
      if(*u(16,3)>=dat_beg && *u(16,3)<=dat_end){
				*(double *)get_p(k,1)+=*d(16,31);
				*(double *)get_p(k,5)+=*d(16,30);
      }
      else {
				*(double *)get_p(k,2)+=*d(16,31);
				*(double *)get_p(k,6)+=*d(16,30);
      }
      *(double *)get_p(k,3)=*(double *)get_p(k,1)-*(double *)get_p(k,2);
      if(*(double *)get_p(k,2)){
				*(double *)get_p(k,4)=(*(double *)get_p(k,3)/ *(double *)get_p(k,2))*100;
      } else *(double *)get_p(k,4)=0;
      *(double *)get_p(k,7)=*(double *)get_p(k,5)-*(double *)get_p(k,6);
      if(*(double *)get_p(k,6)){
				*(double *)get_p(k,8)=(*(double *)get_p(k,7)/ *(double *)get_p(k,6))*100;
      } else *(double *)get_p(k,8)=0;
    }
    copy("Factuur : ",get_p(3,0),10);k=10;
    stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(3,0)+k,3);k+=3;
    k+=date2str(get_p(3,0)+k,*u(16,3));
    add_rec(3);
    used=YES;
  }
  endsr:;
}

static lus002()
{
  int16 j,k,mode=1,len_;
  char last_code[10];
  long last_art=0xFFFF,last_klt=0xFFFF;
  flag end=NO,used=NO;
  uint16 last_grp=0xFFFF,bits;
									
  fasinit(16); last_code[0]=0xFF;
  FOREVER{
    next:;
    if(faskeyi(16,tx->sta_key,mode)) end=YES; mode=2;
    dsp_working();
    if(!end){
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){goto next;}
			if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,10)==KasKltRec[j]){goto next;}}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
      if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(inq_lev && *u(6,7)!=inq_lev){goto next;}
		  if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(inq_klt && *l(16,10)!=inq_klt){goto next;}
			if(sel_klt[0]){
        fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
        if(WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto next;
      }
      if(*u(16,3) <dat_beg){
				if(*u(16,3) <dat_vbeg) {*u(16,3)=dat_vbeg;mode=1; goto next;}
				if(*u(16,3) >dat_vend) {*u(16,3)=dat_beg; mode=1;goto next;}
      }
      else{
				if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF;mode=2; goto next;}
      }
    }

    bits=0;
    if(end) bits|=0x0F;
    if(*l(16,10)!=last_klt && last_klt!=0xFFFF) bits|=0x08;
    if(cmp_str(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
    if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;

    if(bits & 0x08){
      fasinit(2);*u(2,1)=last_klt;fasgeti(2);
      len_=(int)fld[fld_msk[fil_nr]][0].fmt[2];CopyStrField(2,3,get_p(4,0),len_);
			CopyStrField(2,4,get_p(4,9),30);
			CopyStrField(2,5,get_p(4,10),7);
			CopyStrField(2,6,get_p(4,11),25);
			CopyStrField(2,21,get_p(4,12),40);
      add_rec(4);
    }
    if(bits & 0x04){
      fasinit(6);*u(6,1)=last_art;fasgeti(6);
      for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
      copy(s(6,2),get_p(5,0),len_);copy(" ",get_p(5,0)+len_,1);
      copy(s(6,3),get_p(5,0)+len_+1,30-(len_+1));
      add_rec(5);
    }
    if(bits & 0x02){
      fasinit(52);*u(52,1)=last_grp;fasgeti(52);
      stcli_d(get_p(6,0),(long)last_grp,2,0);copy(" ",get_p(6,0)+2,1);
      copy(s(52,14),get_p(6,0)+3,15);
      add_rec(6);
    }
    last_grp=*l(16,23);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    last_klt=*l(16,10);
    if(end) break;
    for(k=3;k<8;k++){
      if(*u(16,3)>=dat_beg && *u(16,3)<=dat_end){
				*(double *)get_p(k,1)+=*d(16,31);
				*(double *)get_p(k,5)+=*d(16,30);
      }
      else {
				*(double *)get_p(k,2)+=*d(16,31);
				*(double *)get_p(k,6)+=*d(16,30);
      }
      *(double *)get_p(k,3)=*(double *)get_p(k,1)-*(double *)get_p(k,2);
      if(*(double *)get_p(k,2)){
				*(double *)get_p(k,4)=(*(double *)get_p(k,3)/ *(double *)get_p(k,2))*100;
      } else *(double *)get_p(k,4)=0;
      *(double *)get_p(k,7)=*(double *)get_p(k,5)-*(double *)get_p(k,6);
      if(*(double *)get_p(k,6)){
				*(double *)get_p(k,8)=(*(double *)get_p(k,7)/ *(double *)get_p(k,6))*100;
      } else *(double *)get_p(k,8)=0;
    }
    copy("Factuur : ",get_p(3,0),10);k=10;
    stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(3,0)+k,3);k+=3;
    k+=date2str(get_p(3,0)+k,*u(16,3));
    add_rec(3);
    used=YES;
  }
}
 
static lus003()
{
  int16 j,k,mode=1,len_;
  char last_code[10];
  long last_art=0xFFFF;
  flag end=NO,used=NO;
  uint16 last_grp=0xFFFF,bits;
									
  if(inq_klt && *u(2,1)!=inq_klt) goto endsr;
	if(sel_klt[0] && WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto endsr;
#if 0
  for(len_=0;len_<fldlen(2,2);len_++) if(*(s(2,2)+len_)=='\0') break;
  copy(s(2,2),get_p(6,0),len_);copy(" ",get_p(6,0)+len_,1);
#endif
  len_=(int)fld[fld_msk[fil_nr]][0].fmt[2];CopyStrField(2,3,get_p(6,0),len_);
	CopyStrField(2,4,get_p(6,5),30);
	CopyStrField(2,5,get_p(6,6),7);
	CopyStrField(2,6,get_p(6,7),25);
	CopyStrField(2,21,get_p(6,8),40);

  fasinit(16); last_code[0]=0xFF;
  *l(16,KltRecFld)=*u(2,1);
  FOREVER{
    next:;
    if(faskeyi(16,tx->sta_key,mode)) end=YES; mode=2;
    dsp_working();
    if(*l(16,KltRecFld)!=*u(2,1)) end=YES;
    if(!end){
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){ goto next;}
			if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,KltRecFld)==KasKltRec[j]){goto next;}}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
      if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(inq_lev && *u(6,7)!=inq_lev){goto next;}
			if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode=1; goto next;}
      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode=2;goto next;}
    }
    if(end && used==NO) break;
    bits=0;
    if(end) bits|=0x0F;
    if(cmp_str(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
    if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;

    if(bits & 0x04){
      fasinit(6);*u(6,1)=last_art;fasgeti(6);
      for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
      copy(s(6,2),get_p(4,0),len_);copy(" ",get_p(4,0)+len_,1);
      CopyStrField(6,3,get_p(4,0)+len_+1,39-(len_+1));
      add_rec(4);
    }
    if(bits & 0x02){
      fasinit(52);*u(52,1)=last_grp;fasgeti(52);
      stcli_d(get_p(5,0),(long)last_grp,2,0);copy(" ",get_p(5,0)+2,1);
      copy(s(52,14),get_p(5,0)+3,15);
      add_rec(5);
    }
    last_grp=*l(16,23);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    if(end){add_rec(6);break;}
    for(k=3;k<8;k++){
      *(double *)get_p(k,1)+=*d(16,31);/* VW */
      *(double *)get_p(k,2)+=*d(16,32);/* AW */
      *(double *)get_p(k,3)=*(double *)get_p(k,1)-*(double *)get_p(k,2);
      if(*(double *)get_p(k,2)){
				*(double *)get_p(k,4)=(*(double *)get_p(k,3)/ *(double *)get_p(k,2))*100;
      } else *(double *)get_p(k,4)=0;
    }
    copy("Factuur : ",get_p(3,0),10);k=10;
    stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(3,0)+k,3);k+=3;
    k+=date2str(get_p(3,0)+k,*u(16,3));
    add_rec(3);
    used=YES;
  }
  endsr:;
}

static lus004()
{
  int16 j,k,mode=1,len_;
  char last_code[10];
  long last_art=0xFFFF,last_klt=0xFFFF;
  flag end=NO,used=NO;
  uint16 last_grp=0xFFFF,bits;
									
  fasinit(16); last_code[0]=0xFF;
  FOREVER{
    next:;
    if(faskeyi(16,tx->sta_key,mode)) end=YES; mode=2;
    dsp_working();
    if(!end){
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){goto next;}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,10)==KasKltRec[j]){goto next;}}
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
      if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(inq_lev && *u(6,7)!=inq_lev){goto next;}
		  if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(inq_klt && *l(16,10)!=inq_klt){goto next;}
			if(sel_klt[0]){
        fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
        if(WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto next;
      }
      if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode=1; goto next;}
      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode=2;goto next;}
    }
									
    bits=0;
    if(end) bits|=0x0F;
    if(*l(16,10)!=last_klt && last_klt!=0xFFFF) bits|=0x08;
    if(cmp_str(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
    if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;

    if(bits & 0x08){
      fasinit(2);*u(2,1)=last_klt;fasgeti(2);
      len_=(int)fld[fld_msk[fil_nr]][0].fmt[2];CopyStrField(2,3,get_p(4,0),len_);
			CopyStrField(2,4,get_p(4,5),30);
			CopyStrField(2,5,get_p(4,6),7);
			CopyStrField(2,6,get_p(4,7),25);
			CopyStrField(2,21,get_p(4,8),40);
      add_rec(4);
    }
    if(bits & 0x04){
      fasinit(6);*u(6,1)=last_art;fasgeti(6);
      for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
      copy(s(6,2),get_p(5,0),len_);copy(" ",get_p(5,0)+len_,1);
      CopyStrField(6,3,get_p(5,0)+len_+1,39-(len_+1));
      add_rec(5);
    }
    if(bits & 0x02){
      fasinit(52);*u(52,1)=last_grp;fasgeti(52);
      stcli_d(get_p(6,0),(long)last_grp,2,0);copy(" ",get_p(6,0)+2,1);
      copy(s(52,14),get_p(6,0)+3,15);
      add_rec(6);
    }
    last_grp=*l(16,23);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    last_klt=*l(16,10);
    if(end) break;
    for(k=3;k<8;k++){
      *(double *)get_p(k,1)+=*d(16,31);                          /* VW */
      *(double *)get_p(k,2)+=*d(16,32);                          /* AW */
      *(double *)get_p(k,3)=*(double *)get_p(k,1)-*(double *)get_p(k,2);
      if(*(double *)get_p(k,2)){
				*(double *)get_p(k,4)=(*(double *)get_p(k,3)/ *(double *)get_p(k,2))*100;
      } else *(double *)get_p(k,4)=0;
    }
    copy("Factuur : ",get_p(3,0),10);k=10;
    stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(3,0)+k,3);k+=3;
    k+=date2str(get_p(3,0)+k,*u(16,3));
    add_rec(3);
    used=YES;
  }
}
 
static lus005(kl_stu_)
int16 kl_stu_;
{
  int16 j,k,mode=1,len_,kl_pos_;
  char last_code[10];
  long last_art=0xFFFF;
  flag end=NO,used=NO;
  uint16 last_grp=0xFFFF,bits;

  if(kl_stu_==1) kl_pos_=15; else kl_pos_=KltRecFld;
  if(kl_stu_==2 && inq_klt && *u(2,1)!=inq_klt) goto endsr;
	if(kl_stu_==2 && sel_klt[0] && WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto endsr;
  if(kl_stu_==1 && inq_lev && *u(1,1)!=inq_lev) goto endsr;
 
#if 0
  for(len_=0;len_<fldlen(kl_stu_,2);len_++) if(*(s(kl_stu_,2)+len_)=='\0') break;
  copy(s(kl_stu_,2),get_p(6,0),len_);copy(" ",get_p(6,0)+len_,1);
#endif
  len_=(int)fld[fld_msk[fil_nr]][0].fmt[2];CopyStrField(kl_stu_,3,get_p(6,0),len_);
	CopyStrField(kl_stu_,4,get_p(6,5),30);
	CopyStrField(kl_stu_,5,get_p(6,6),7);
	CopyStrField(kl_stu_,6,get_p(6,7),25);
	CopyStrField(kl_stu_,21,get_p(6,8),40);

  fasinit(16); last_code[0]=0xFF;
  *l(16,kl_pos_)=*u(kl_stu_,1);
  FOREVER{
    next:;
    if(faskeyi(16,tx->sta_key,mode)) end=YES; mode=2;
    dsp_working();
    if(*l(16,kl_pos_)!=*u(kl_stu_,1)) end=YES;
    if(!end){
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){goto next;}
			if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,KltRecFld)==KasKltRec[j]){goto next;}}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
      if(kl_stu_==2 && fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      if(kl_stu_==1 && *l(16,10)) goto next;/* geen klanten */
	  if(kl_stu_==1 && *l(16,15)>=30000) goto next;/* geen stockmutaties */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(kl_stu_==2 && inq_lev && *u(6,7)!=inq_lev){goto next;}
		  if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode=1; goto next;}
      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode=2;goto next;}
    }
    if(end && used==NO) break;
    bits=0;
    if(end) bits|=0x0F;
    if(cmp_str(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
    if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;

    if(bits & 0x04){
      fasinit(6);*u(6,1)=last_art;fasgeti(6);
      for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
      copy(s(6,2),get_p(4,0),len_);copy(" ",get_p(4,0)+len_,1);
      CopyStrField(6,3,get_p(4,0)+len_+1,39-(len_+1));
      add_rec(4);
    }
    if(bits & 0x02){
      fasinit(52);*u(52,1)=last_grp;fasgeti(52);
      stcli_d(get_p(5,0),(long)last_grp,2,0);copy(" ",get_p(5,0)+2,1);
      copy(s(52,14),get_p(5,0)+3,15);
      add_rec(5);
    }
    last_grp=*l(16,23);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    if(end){add_rec(6);break;}
    fasinit(6);*u(6,1)=last_art;fasgeti(6);
    for(k=3;k<8;k++){
      *(double *)get_p(k,1)+=*d(16,30);/* stuks */
      *(double *)get_p(k,2)+=*d(16,30)* *f(6,37);/* LITERS */
      *(double *)get_p(k,3)+=*d(16,31);/* omzet */
      if(*d(16,31)) *(double *)get_p(k,4)+=*d(16,31)-(*d(16,30)* *f(16,27));/* excl. acc */
    }
    copy("Factuur : ",get_p(3,0),10);k=10;
    stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(3,0)+k,3);k+=3;
    k+=date2str(get_p(3,0)+k,*u(16,3));
    add_rec(3);
    used=YES;
  }
  endsr:;
}
 
static lus006(kl_stu_)
int16 kl_stu_;
{
  int16 j,k,mode=1,len_,kl_pos_;
  char last_code[10];
  long last_art=0xFFFF,last_klt=0xFFFF;
  flag end=NO;
  uint16 last_grp=0xFFFF,bits;
									
  if(kl_stu_==1) kl_pos_=15; else kl_pos_=10;
  fasinit(16); last_code[0]=0xFF;
  FOREVER{
    next:;
    if(faskeyi(16,tx->sta_key,mode)) end=YES; mode=2;
/* scrfld(18,16,1); */
    dsp_working();
    if(!end){
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){goto next;}
			if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,10)==KasKltRec[j]){goto next;}}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
      if(kl_stu_==2 && fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      if(kl_stu_==1 && *l(16,10)) goto next;/* geen klanten */
	  if(kl_stu_==1 && *l(16,15)>=30000) goto next;/* geen stockmutaties */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(kl_stu_==2 && inq_lev && *u(6,7)!=inq_lev){goto next;}
		  if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(kl_stu_==2 && inq_klt && *l(16,10)!=inq_klt){goto next;}
			if(kl_stu_==2 && sel_klt[0]){
        fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
        if(WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto next;
      }
      if(kl_stu_==1 && inq_lev && *l(16,15)!=inq_lev){goto next;}
      if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode=1; goto next;}
      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode=2;goto next;}
    }

    bits=0;
    if(end) bits|=0x0F;
    if(*l(16,kl_pos_)!=last_klt && last_klt!=0xFFFF) bits|=0x08;
    if(cmp_str(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
    if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;
									
    if(bits & 0x08){
      fasinit(kl_stu_);*u(kl_stu_,1)=last_klt;fasgeti(kl_stu_);
      len_=(int)fld[fld_msk[fil_nr]][0].fmt[2];CopyStrField(kl_stu_,3,get_p(4,0),len_);
			CopyStrField(kl_stu_,4,get_p(4,5),30);
			CopyStrField(kl_stu_,5,get_p(4,6),7);
			CopyStrField(kl_stu_,6,get_p(4,7),25);
			CopyStrField(kl_stu_,21,get_p(4,8),40);
      add_rec(4);
    }
    if(bits & 0x04){
      fasinit(6);*u(6,1)=last_art;fasgeti(6);
      for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
      copy(s(6,2),get_p(5,0),len_);copy(" ",get_p(5,0)+len_,1);
      CopyStrField(6,3,get_p(5,0)+len_+1,39-(len_+1));
      add_rec(5);
    }
    if(bits & 0x02){
      fasinit(52);*u(52,1)=last_grp;fasgeti(52);
      stcli_d(get_p(6,0),(long)last_grp,2,0);copy(" ",get_p(6,0)+2,1);
      copy(s(52,14),get_p(6,0)+3,15);
      add_rec(6);
    }
    last_grp=*l(16,23);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    last_klt=*l(16,kl_pos_);
    if(end) break;
    fasinit(6);*u(6,1)=last_art;fasgeti(6);
    for(k=3;k<8;k++){
      *(double *)get_p(k,1)+=*d(16,30);/* stuks */
      *(double *)get_p(k,2)+=*d(16,30)* *f(6,37);/* LITERS */
      *(double *)get_p(k,3)+=*d(16,31);/* omzet */
      if(*d(16,31)) *(double *)get_p(k,4)+=*d(16,31)-(*d(16,30)* *f(16,27));/* excl.ac */
    }
    copy("Factuur : ",get_p(3,0),10);k=10;
    stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(3,0)+k,3);k+=3;
    k+=date2str(get_p(3,0)+k,*u(16,3));
    add_rec(3);
  }
}
 
static lus007()
{
  int16 j,k,mode=1,a_mode,len_,pos_;
  long last_art=0xFFFF,last_klt=0xFFFF;
  flag end=NO,used=NO,l_used=NO;
  uint16 bits,last_lev=0xFFFF;
									
  fasinit(6);a_mode=1;
  FOREVER{
    end=NO;
    next_art:;
    if(faskeyi(6,4,a_mode)) end=YES; a_mode=2;
    if(!end){
      if(inq_lev && *u(6,7)!=inq_lev) goto next_art;
		  if(inq_merk && *u(6,101)!=inq_merk){goto next_art;}
      if(inq_grp && *i(6,9)!=inq_grp) goto next_art;
      for(j=0;j<3;j++) if(grp_niet[j] && *i(6,9)==grp_niet[j]) goto next_art;
      if(skip_leegg=='J' && *i(6,9)==99) goto next_art;
    }
    if(end || (last_lev!=0xFFFF && last_lev!=*u(6,7))){
      fasinit(1);*u(1,1)=last_lev;fasgeti(1);
      len_=(int)fld[fld_msk[fil_nr]][0].fmt[2];CopyStrField(1,3,get_p(6,0),len_);
			CopyStrField(1,4,get_p(6,5),30);
			CopyStrField(1,5,get_p(6,6),7);
			CopyStrField(1,6,get_p(6,7),25);
			CopyStrField(1,21,get_p(6,8),40);
			if(l_used) add_rec(6);
      if(end) break;
      l_used=NO;
    }
    last_lev=*u(6,7);

    fasinit(16); last_klt=0xFFFF; used=NO;
    *l(16,20)=*u(6,1); mode=1; end=NO;
    FOREVER{
      next:;
      if(faskeyi(16,1,mode)) end=YES; mode=2;
      dsp_working();
      if(*l(16,20)!=*u(6,1)) end=YES;
      if(!end){
	      if(inq_klt && *l(16,10)!=inq_klt){goto next;}
				if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode=1; goto next;}
				if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode=2;goto next;}
				if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
				if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
				if(OnlyGratisArt=='J' && *d(16,31)) goto next;
				if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
				if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
				if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,10)==KasKltRec[j]){goto next;}}
				if(sel_klt[0]){
					fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
					if(WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto next;
				}
      }
      if(end && used==NO) break;
      bits=0;
      if(end) bits|=0x0F;
      if(last_klt!=*l(16,10) && last_klt!=0xFFFF) bits|=0x0C;
      if(bits & 0x04){
				fasinit(2);*u(2,1)=last_klt;fasgeti(2);
				for(len_=0;len_<fldlen(2,2);len_++) if(*(s(2,2)+len_)=='\0') break;
				copy(s(2,2),get_p(4,0),len_);copy(" ",get_p(4,0)+len_,1);pos_=len_+1;
        len_=(int)fld[fld_msk[fil_nr]][0].fmt[2]-pos_;CopyStrField(2,3,get_p(4,0)+pos_,len_);
				CopyStrField(2,4,get_p(4,5),30);
				CopyStrField(2,5,get_p(4,6),7);
				CopyStrField(2,6,get_p(4,7),25);
				CopyStrField(2,21,get_p(4,8),40);
				add_rec(4);
      }
      if(bits & 0x02){
				for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
				copy(s(6,2),get_p(5,0),len_);copy(" ",get_p(5,0)+len_,1);pos_=len_+1;
				len_=(int)fld[fld_msk[fil_nr]][0].fmt[2]-pos_;CopyStrField(6,3,get_p(5,0)+pos_,len_);
//			len_=(int)fld[fld_msk[fil_nr]][0].fmt[2]-(len_+1);
	
				add_rec(5);
      }
      if(end) break;
      last_art=*l(16,20); last_klt=*l(16,10);
      for(k=3;k<8;k++){
				*(double *)get_p(k,1)+=*d(16,30);/* stuks */
				*(double *)get_p(k,2)+=*d(16,30)* *f(6,37);/* LITERS */
				*(double *)get_p(k,3)+=*d(16,31);/* omzet */
				if(*d(16,31)) *(double *)get_p(k,4)+=*d(16,31)-(*d(16,30)* *f(16,27));/* excl.acc */
      }
      copy("Factuur : ",get_p(3,0),10);k=10;
      stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
      copy(" - ",get_p(3,0)+k,3);k+=3;
      k+=date2str(get_p(3,0)+k,*u(16,3));
      add_rec(3);
      used=YES;l_used=YES;
    }
  }
}
 
static lus008()
{
  int16 j,k,mode=1,len_;
  char last_code[10];
  long last_art=0xFFFF;
  double bd_,bd_semkorting_,bd_tussenkomst_;
  flag end=NO,used=NO;
  uint16 last_grp=0xFFFF,bits;
									
  if(inq_klt && *u(2,1)!=inq_klt) goto endsr;
	if(sel_klt[0] && WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto endsr;
#if 0
  for(len_=0;len_<fldlen(2,2);len_++) if(*(s(2,2)+len_)=='\0') break;
  copy(s(2,2),get_p(6,0),len_);copy(" ",get_p(6,0)+len_,1);
#endif
  copy(s(2,3),get_p(6,0),30);

  fasinit(16); last_code[0]=0xFF;
  *l(16,KltRecFld)=*u(2,1);
  FOREVER{
    next:;
    if(faskeyi(16,tx->sta_key,mode)) end=YES; mode=2;
    dsp_working();
    if(*l(16,KltRecFld)!=*u(2,1)) end=YES;
    if(!end){
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){goto next;}
			if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,KltRecFld)==KasKltRec[j]){goto next;}}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
      if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(inq_lev && *u(6,7)!=inq_lev){goto next;}
	    if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode=1; goto next;}
      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode=2;goto next;}
    }
    if(end && used==NO) break;
    bits=0;
    if(end) bits|=0x0F;
    if(cmp_str(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
    if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;

    if(bits & 0x04){
      fasinit(6);*u(6,1)=last_art;fasgeti(6);
      for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
      copy(s(6,2),get_p(4,0),len_);copy(" ",get_p(4,0)+len_,1);
      copy(s(6,3),get_p(4,0)+len_+1,30-(len_+1));
      add_rec(4);
    }
    if(bits & 0x02){
      fasinit(52);*u(52,1)=last_grp;fasgeti(52);
      stcli_d(get_p(5,0),(long)last_grp,2,0);copy(" ",get_p(5,0)+2,1);
      copy(s(52,14),get_p(5,0)+3,15);
      add_rec(5);
    }
    last_grp=*l(16,23);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    if(end){add_rec(6);break;}
    fasinit(6);*u(6,1)=last_art;fasgeti(6);
		if(HerberekenSemKorting=='J') CalcSemKorting();
    for(k=3;k<8;k++){
      *(double *)get_p(k,1)+=*d(16,30);/* stuks */
      *(double *)get_p(k,2)+=*d(16,30)* *f(6,37);/* LITERS */
      bd_=*d(16,31)+*d(16,33);
      *(double *)get_p(k,3)+=bd_;/* bruto-omzet */
      if(bd_) *(double *)get_p(k,4)+=bd_-(*d(16,30)* *f(16,27));/* excl.acc */
      *(double *)get_p(k,5)+=*d(16,33);/* factuur-korting */
			if(HerberekenSemKorting=='J'){
			   if(*d(16,31)==0) {hl_semkort=0.,calc_sem=0.,brij_tpct=0.,brij_tbd=0.;}
				 bd_semkorting_=(*d(16,31)-(*d(16,30)* *f(16,27))) * calc_sem/100.;  // netto ex acc en dan korting
				 bd_semkorting_+=*d(16,30)*hl_semkort;
				 bd_tussenkomst_=(bd_-(*d(16,30)* *f(16,27))) * brij_tpct/100.; // bruto ex acc en dan korting 
				 bd_tussenkomst_+=*d(16,30)*brij_tbd;
			}
			else {
				bd_semkorting_=*d(16,34);bd_tussenkomst_=*d(16,35);
			}
      *(double *)get_p(k,6)+=bd_semkorting_;/* sem.korting */
      *(double *)get_p(k,7)+=bd_tussenkomst_;/* tussenkomst brouwerij  */
      *(double *)get_p(k,8)+=*d(16,31)-bd_semkorting_+bd_tussenkomst_;/* netto VW */
      *(double *)get_p(k,9)+=*d(16,32);/* AK-waarde */
      bd_=*(double *)get_p(k,8)-*(double *)get_p(k,9);
      *(double *)get_p(k,10)=bd_;/* winst */
      if(*(double *)get_p(k,9)){/* NETTO winst % */
	      *(double *)get_p(k,11)=(bd_/ *(double *)get_p(k,9))*100;
      } else *(double *)get_p(k,11)=0;
    }
    copy("Factuur : ",get_p(3,0),10);k=10;
    stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(3,0)+k,3);k+=3;
    k+=date2str(get_p(3,0)+k,*u(16,3));
    add_rec(3);
    used=YES;
  }
  endsr:;
}

static lus009(kl_stu_)
int16 kl_stu_;
{
  int16 j,k,mode=1,len_,kl_pos_,jj_,mm_,dd_;
  char last_code[10];
  long last_art=0xFFFF;
  flag end=NO,used=NO;
  uint16 last_grp=0xFFFF,bits;

  if(kl_stu_==1) kl_pos_=15; else kl_pos_=KltRecFld;
  if(kl_stu_==2 && inq_klt && *u(2,1)!=inq_klt) goto endsr;
	if(kl_stu_==2 && sel_klt[0] && WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto endsr;
  if(kl_stu_==1 && inq_lev && *u(1,1)!=inq_lev) goto endsr;

#if 0
  for(len_=0;len_<fldlen(kl_stu_,2);len_++) if(*(s(kl_stu_,2)+len_)=='\0') break;
  copy(s(kl_stu_,2),get_p(6,0),len_);copy(" ",get_p(6,0)+len_,1);
#endif
  CopyStrField(kl_stu_,3,get_p(6,0),35);


  fasinit(16); last_code[0]=0xFF;
  *l(16,kl_pos_)=*u(kl_stu_,1);
  FOREVER{
    next:;
    if(faskeyi(16,tx->sta_key,mode)) end=YES; mode=2;
    dsp_working();
    if(*l(16,kl_pos_)!=*u(kl_stu_,1)) end=YES;
    if(!end){
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){goto next;}
			if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,KltRecFld)==KasKltRec[j]){goto next;}}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
      if(kl_stu_==2 && fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      if(kl_stu_==1 && *l(16,10)) goto next;/* geen klanten */
	  if(kl_stu_==1 && *l(16,15)>=30000) goto next;/* geen stockmutaties */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(kl_stu_==2 && inq_lev && *u(6,7)!=inq_lev){goto next;}
		  if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode=1; goto next;}
      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode=2;goto next;}
    }
    if(end && used==NO) break;
    bits=0;
    if(end) bits|=0x0F;
    if(cmp_str(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
    if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;

    if(bits & 0x04){
      fasinit(6);*u(6,1)=last_art;fasgeti(6);
      for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
      copy(s(6,2),get_p(4,0),len_);copy(" ",get_p(4,0)+len_,1);
      CopyStrField(6,3,get_p(4,0)+len_+1,39-(len_+1));
      add_rec(4);
    }
    if(bits & 0x02){
      fasinit(52);*u(52,1)=last_grp;fasgeti(52);
      stcli_d(get_p(5,0),(long)last_grp,2,0);copy(" ",get_p(5,0)+2,1);
      copy(s(52,14),get_p(5,0)+3,15);
      add_rec(5);
    }
    last_grp=*l(16,23);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    if(end){add_rec(6);break;}
    fasinit(6);*u(6,1)=last_art;fasgeti(6);
		jddate(*u(16,3),&jj_,&mm_,&dd_); if(mm_<1 || mm_>12) mm_=1;
    for(k=3;k<8;k++){
			if(StatMndAantal=='J'){
				*(double *)get_p(k,1+mm_-1)+=*d(16,30);/* stuks */
				*(double *)get_p(k,1+12)+=*d(16,30);/* stuks */
			}
			else{
				*(double *)get_p(k,1+mm_-1)+=*d(16,31);/* omzet */
			  *(double *)get_p(k,1+12)+=*d(16,31);/* omzet */
			}
      //*(double *)get_p(k,1)+=*d(16,30);/* stuks */
      //*(double *)get_p(k,2)+=*d(16,30)* *f(6,37);/* LITERS */
      //*(double *)get_p(k,3)+=*d(16,31);/* omzet */
      //if(*d(16,31)) *(double *)get_p(k,4)+=*d(16,31)-(*d(16,30)* *f(16,27));/* excl. acc */
    }
    copy("Factuur : ",get_p(3,0),10);k=10;
    stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(3,0)+k,3);k+=3;
    k+=date2str(get_p(3,0)+k,*u(16,3));
    add_rec(3);
    used=YES;
  }
  endsr:;
}

static lus010()
{
  int16 j,k,mode=1,len_,mm_,dd_,jj_;
  char last_code[10];
  long last_art=0xFFFF,last_klt=0xFFFF;
  flag end=NO,used=NO;
  uint16 last_grp=0xFFFF,bits;
									
  fasinit(16); last_code[0]=0xFF;
  FOREVER{
    next:;
    if(faskeyi(16,tx->sta_key,mode)) end=YES; mode=2;
    dsp_working();
    if(!end){
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){goto next;}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_kasverkopen=='J'){for(j=0;j<10;j++) if(KasKltRec[j] && *l(16,10)==KasKltRec[j]){goto next;}}
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
      if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(inq_lev && *u(6,7)!=inq_lev){goto next;}
		  if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(inq_klt && *l(16,10)!=inq_klt){goto next;}
			if(sel_klt[0]){
        fasinit(2);*u(2,1)=*l(16,10);fasgeti(2);
        if(WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) goto next;
      }
      if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode=1; goto next;}
      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode=2;goto next;}
    }
									
    bits=0;
    if(end) bits|=0x0F;
    if(*l(16,10)!=last_klt && last_klt!=0xFFFF) bits|=0x08;
    if(cmp_str(s(16,21),last_code,fldlen(16,21)) && last_code[0]!=0xFF) bits|=0x0C;
    if(*l(16,23)!=last_grp && last_grp!=0xFFFF) bits|=0x0E;

    if(bits & 0x08){
      fasinit(2);*u(2,1)=last_klt;fasgeti(2);
      len_=(int)fld[fld_msk[fil_nr]][0].fmt[2]; CopyStrField(2,3,get_p(4,0),len_);
      add_rec(4);
    }
    if(bits & 0x04){
      fasinit(6);*u(6,1)=last_art;fasgeti(6);
      for(len_=0;len_<fldlen(6,2);len_++) if(*(s(6,2)+len_)=='\0') break;
      copy(s(6,2),get_p(5,0),len_);copy(" ",get_p(5,0)+len_,1);
      CopyStrField(6,3,get_p(5,0)+len_+1,39-(len_+1));
      add_rec(5);
    }
    if(bits & 0x02){
      fasinit(52);*u(52,1)=last_grp;fasgeti(52);
      stcli_d(get_p(6,0),(long)last_grp,2,0);copy(" ",get_p(6,0)+2,1);
      copy(s(52,14),get_p(6,0)+3,15);
      add_rec(6);
    }
    last_grp=*l(16,23);
    last_art=*l(16,20); copy(s(16,21),last_code,fldlen(16,21));
    last_klt=*l(16,10);
    if(end) break;
		jddate(*u(16,3),&jj_,&mm_,&dd_); if(mm_<1 || mm_>12) mm_=1;
    for(k=3;k<8;k++){
			if(StatMndAantal=='J'){
				*(double *)get_p(k,1+mm_-1)+=*d(16,30);/* stuks */
				*(double *)get_p(k,1+12)+=*d(16,30);/* stuks */
			}
			else{
				*(double *)get_p(k,1+mm_-1)+=*d(16,31);/* omzet */
			  *(double *)get_p(k,1+12)+=*d(16,31);/* omzet */
			}
    }
    copy("Factuur : ",get_p(3,0),10);k=10;
    stcli_d(get_p(3,0)+k,(long)(*l(16,2)),8,1); k+=8;
    copy(" - ",get_p(3,0)+k,3);k+=3;
    k+=date2str(get_p(3,0)+k,*u(16,3));
    add_rec(3);
    used=YES;
  }
}

static MakeSortTabel()
{
	int16 j,k,sw,record_,mode;
	uint16 a,used;
	double bedrag_;

	scrnum=0;scrget(1,170);scrifld(10,fm_os79,"Sorteren klanten volgens omzet...");scrupd(-3,0);
	zeroL((char *)&SortTabel[0].Record,sizeof SortTabel);MaxSortTabel=0;
	fasinfo(2,1);  used=*u(2,1);
 
  for(a=1;a<=used;a++){
		*u(2,1)=a;
		if(fasgetu(2)!=0) continue;
		if(inq_klt && *u(2,1)!=inq_klt) continue;
	  if(sel_klt[0] && WildCardCmpstr(sel_klt,s(2,fld_sel_klt),fldlen(2,fld_sel_klt))) continue;
		if(skip_kasverkopen=='J'){
			for(j=0;j<10;j++) if(KasKltRec[j] && *u(2,1)==KasKltRec[j]) break;
			if(j<10) continue;
		}
		fasinit(16); *l(16,KltRecFld)=*u(2,1);mode=1;
		FOREVER{
			next:;
			if(faskeyi(16,KltKeyNr,mode)) break; mode=2;
			dsp_working();
			if(*l(16,KltRecFld)!=*u(2,1)) break;
      if(inq_grp && *l(16,23)!=inq_grp){goto next;}
			if(inq_filiaal && !(inq_filiaal==99 && *u(16,8)==0) && *u(16,8)!=inq_filiaal){goto next;}
      for(j=0;j<3;j++) if(grp_niet[j] && *l(16,23)==grp_niet[j]){goto next;}
      if(skip_leegg=='J' && *l(16,23)==99){ goto next;}
			if(OnlyGratisArt=='J' && *d(16,31)) goto next;
			if(skip_gratis_art=='J' && *d(16,31)==0) goto next;
			if(SkipKassaFt=='J' && fldlen(16,39) && *s(16,39)==YES) goto next;
      if(fldlen(16,15) && *l(16,15)) goto next;/* geen leveranciers */
      fasinit(6);*u(6,1)=*l(16,20);fasgeti(6);
      if(inq_lev && *u(6,7)!=inq_lev){goto next;}
			if(inq_merk && *u(6,101)!=inq_merk){goto next;}
      if(*u(16,3) <dat_beg) {*u(16,3)=dat_beg;mode=1; goto next;}
      if(*u(16,3) >dat_end) {*u(16,3)=0xFFFF; mode=2;goto next;}
			SortTabel[MaxSortTabel].Bedrag+=*d(16,31);
		}
	  if(SortTabel[MaxSortTabel].Bedrag){
			SortTabel[MaxSortTabel].Record=a;MaxSortTabel++;
			if(MaxSortTabel>=10000) break;
		}
	}
  FOREVER{/* sorteren */
    sw=NO;
    for(k=0;k<MaxSortTabel-1;k++){
      if(SortTabel[k].Bedrag<SortTabel[k+1].Bedrag){
				record_=SortTabel[k].Record;bedrag_=SortTabel[k].Bedrag;
				copy((char *)&SortTabel[k+1].Record,(char *)&SortTabel[k].Record,sizeof SortTabel[0]);
				SortTabel[k+1].Record=record_;SortTabel[k+1].Bedrag=bedrag_;
				sw=YES;
			}
    }
    if(sw==NO) break;
  }
}

static WildCardCmpstr(ps1_,ps2_,len_) // * = skip karakter
char *ps1_,*ps2_;
int16 len_;
{
	int16 k;

	for(k=0;k<len_;k++){
		if(*(ps1_+k)=='\0') break;
		if(*(ps1_+k)=='*') continue;
		if(*(ps1_+k)!=*(ps2_+k)) return YES;
	}
	return NO;
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
      if(m==0) nokort=NO;/* wel korting indien expleciet contract op groep */
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
