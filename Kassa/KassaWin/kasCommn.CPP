// KASCOMMN.CPP

// KASCONT1

//static char version[] = "KASCONT  00.15 31/12/01";
 
 
extern char grp_bits[];
 
struct {
  unsigned short datum;
  long first_rec;
} dag;

extern char *txtjn[], *txtper[], *txtcumper[], *txtmnd[], *txtfin[];
extern char *txtgroep[], *txtart[], *txtmnd[], *txtsel[], *txtvkp[];
extern char *txtcont[], *txtverk[];
extern char beep_fl;
extern int cf_periode, cf_cont, cf_art, cf_groep, cf_btw, cf_cumper, cf_financ,SoortKassa;
extern int groep_leeg, cf_vkptype, _vkptype, cf_verknr, not_check, totflags, clncount;
extern unsigned jddatum;
extern int NoPrtCut, DefNoPrtCut, EigenPrijsOpStuksAllowed;
extern int def_digits, ep_digits;
extern char prt_head[10][41], HDDSerialNr[20];
extern char def_valuta[],TotaalOp5CentAfronden, PromoNotOnHorecaPrice;
extern float def_round, btw_round;
extern double BedragTotaalafronding;
extern int optiestype, optiesgroep, XZTotaalDispFlag;
extern double BedragTotaalafronding;

char PrtSuspended=NO; // als er een error was, dan op YES. Wordt per ticket gecleared !
char CustSuspended=NO; // als er een error was, dan op YES. 
int PrintControl2PDF=NO;

static int _periode, _cont, _art, _groep, _btw, _financ, _verknr, ZTotaalPrintingBusy=NO;
static long LastZTotaalPrintedRecords, LastZTotaalProofPrintedRecords, LastZTotaalPrintedSeqNr,TotSpoolBytes;
static char ticket_first[50], ticket_last[50];
static int _select, etikstar[10], etikstop[10];
extern int lst_maand, lst_week, lst_dag, _cumper, _printed, contflag, ConfigFlags;
static double fin_totaal[2*VAL_COUNT+1];
static double grp_totaal, art_totaal, fin_reg[1+2*VAL_COUNT][FIN_COUNT], eCheqTotSubGrpt[SUBGRP_COUNT];
static double grp_chk, art_chk, btw_chk, finv_chk, fino_chk;
static int klt_totaal, tickstar[4], tickstop[4];
extern double btw_totaal;

static char fin_attr[FIN_COUNT] = {
  1,0,0,1,15,0,0,1,1,1, 1,1,1,0,0,1,1,1,1,1,1,1,1,1, 15,0,0,1,1,1,0,0,1,15,1,1,1,1,1,0 // nog juistzetten
};
static char fin_prt[FIN_COUNT] = {
  0,1,2,3,4,5,6,7,8,9, 10,11,12,13,14,15,22,23,30,31,32,28,29,33, 16,17,18,19,20,21,24,25,26,27,34,35,36,37,38,39  // nog juistzetten
};
 
static struct {
  char selected;
  char maand;
  char week;
  int  pos;
  long first_rec;
  long next_rec;
  unsigned datum;
} day[100];
int day_used;

struct s_art_cumul {
  int plu_ix;
  char code[ARTCODE_LEN];
  char naam[20];
  int groep;
  int st_verp;
  double aantal;
  double aantal_st;
  double totaal;
} *art_cumul, *art_lin;
int cumart_size=sizeof(art_cumul[0]), cumart_count=CUMART_COUNT, cumart_used;
 
struct s_grp_cumul {
  double aantal;
  double totaal;
  float percent;
	char btw_used[4];
  float btw[4];
	double btw_aantal[4];
  double btw_totaal[4];
} *grp_cumul, *grp_lin;
int cumgrp_size=sizeof(grp_cumul[0]), cumgrp_count=CUMGRP_COUNT;
 
char *getml();
unsigned datejd();
long log_getrec();
double round_it();

// variabelen 
static unsigned jdlast;
int logref, LogCtrlRef;





/* --------------------------- Declaratie functies ---------------------- */

static int _cmpstr(char *s1, char *s2, int len);
static int _compare(char *p1, char *p2, int dummy);
static void _end(void);
static void _initial(void);
static void _upd(char *txt[], int *pi, int x, int y);
static void add_data(void);
static void calc_data(char fast);
static int chk_exec(void);
static void chk_init(void);
static void clr_data(void);
static void druk_af(void);
static int  find_artix(int plu_ix);
static void get_cf(void);
static void kalender(void);
static void mark_selectie(void);
static void prt_data(void);
static void put_cf(void);
static void sel_disp(void);
static int sel_upd(void);
static int week_nr(unsigned datum);
static char * CopyString(char *s, char * p);
////////////////




void Komma2Punt(char *s)
{
	while (*s) {
		if (*s==',') *s='.';
		s++;
	}
}

void get_memcumul(void)
{
  long needed;
 
  needed=(long)cumart_count * cumart_size;
  art_cumul=(struct s_art_cumul *)getml(needed);
  if ((long)art_cumul == 0L) disp_exit("GETML voor ART_CUMUL werkt niet");
  needed=(long)cumgrp_count * cumgrp_size;
  grp_cumul=(struct s_grp_cumul *)getml(needed);
  if ((long)grp_cumul == 0L) disp_exit("GETML voor GRP_CUMUL werkt niet");
}
 
void rls_memcumul(void)
{
  long needed;
 
  needed=(long)cumart_count * cumart_size;
  rlsml((char *) art_cumul, needed);
  needed=(long)cumgrp_count * cumgrp_size;
  rlsml((char *) grp_cumul, needed);
}

void log_ZTotaalHeaderUpdate();


static int LogThisAction(int ticketNr, int lijnnr, int soortactie) // soortactie : 0=neg. ticket, 1=clr_ticket, 2=clr_line , 3=lade_open 
{
  int i,ix_,lref_;
	CString cstr_,cdump_,cbasis_;
	struct s_lijn* pl;
	 
	lref_=dopen("KasCtrl.dat",RDWRMODE);
	if (lref_<0) goto endsr;
  dseek(lref_,0L,2); // eof

  get_tijd();tijd[21]='\0';cbasis_=CString(tijd); cbasis_+="  ";
	switch(soortactie){
	  case 0 : cbasis_+="NEG_TICKET"; break;
	  case 1 : cbasis_+="WIS_TICKET"; break;
	  case 2 : cbasis_+="WIS_LIJN  "; break;
		case 3 : cbasis_+="LADE_OPEN "; break;
		default :cbasis_+="ONBEKEND  "; break;
	}
  cbasis_+=": ";
	if(soortactie==3){// loggen alarm
		cdump_=cbasis_;
		cdump_+="Lade geopend met alarm\x0D\x0A";
		dwrite(lref_,(char *)(LPCTSTR)cdump_,cdump_.GetLength());
		dclose(lref_);
		goto endsr;
	}
	i=0;if(soortactie==2) i=lijnnr;
	for (i; i<p_vrk->used; i++) {
		if(soortactie==2 && i!=lijnnr) break;
		pl=&p_vrk->lijn[i];


		if(pl->groep>=1 && pl->groep<=99){
			ix_=-1;
			if (pl->code[0]) ix_=kasplu.plu_req(pl->code,ARTCODE_LEN);
			cdump_=cbasis_;
//			if(ix_>=0) cdump_+=CString(kasplu.art_info.code,ARTCODE_LEN); else cdump_+="     ";cdump_+="  ";
						
			if(ix_>=0) cdump_+=CString(kasplu.art_info.naam); else cdump_+=CString(grp_info[pl->groep].naam);cdump_+="  ";
			if(cdump_.GetLength()<65) cdump_+=CString("                                        ",65-cdump_.GetLength());
  		cstr_.Format("%5.2f",pl->aantal); cdump_+=cstr_;cdump_+="  ";
			cstr_.Format("%5.2f",pl->prijs); cdump_+=cstr_;cdump_+="  ";
			cstr_.Format("%5.2f",pl->totaal); cdump_+=cstr_;cdump_+="  ";
			cdump_+="\x0D\x0A";
			dwrite(lref_,(char *)(LPCTSTR)cdump_,cdump_.GetLength());
		}
	}
	dclose(lref_);
endsr:;
	return 0;
}


void DrukZTotaal()
{  
	int day_ix;
	char lijn[50];
	CString cstr;
	
	_cumper=0;
	_periode=0;
  _vkptype=0;
	_verknr=0;
	_btw=1;
  _financ=1;
	ZTotaalPrintingBusy=YES; totflags=0;
  for (day_ix=0; day_ix<day_used; day_ix++) {
	  if (day[day_ix].next_rec>LastZTotaalPrintedRecords) day[day_ix].selected=YES;
		else day[day_ix].selected=NO;
	}
	ticket_first[0]=0;
	ticket_last[0]=0;
	
  prt_hoofd(2);
	LastZTotaalProofPrintedRecords=0;
  druk_af();

	if (LastZTotaalProofPrintedRecords<=LastZTotaalPrintedRecords) { // geen records found !
	  if (NoPrtCut == NO) prt_hoofd(YES); 
		prt_close();
		_clr_ticket();
	}
	else {  
		prt_nl(" "); 
		prt_cod(2); prt_cod(3); prt_nl("********************"); prt_cod(4);
		cstr.Format("  %s Nr:%-d",txttxt[87],LastZTotaalPrintedSeqNr+1);
		prt_cod(2); prt_cod(3); prt_nl((char*)cstr.operator LPCTSTR()); prt_cod(4);
		if (getenv("jama-kassa")!=NULL) {
			_clr_text(lijn); copynaam(getenv("jama-kassa"),lijn+7,20); prt_cod(2); prt_cod(3); lijn[20]=0; prt_nl(lijn); prt_cod(4);
		}

		prt_nl(" ");
		_clr_text(lijn); copynaam(txttxt[88],lijn,20); copynaam(ticket_first+8,lijn+15,4); copynaam(ticket_first+20,lijn+20,20);
		prt_nl(lijn);
		_clr_text(lijn); copynaam(txttxt[89],lijn,20); copynaam(ticket_last+8,lijn+15,4); copynaam(ticket_last+20,lijn+20,20);
		prt_nl(lijn);
		prt_nl(" ");

		totflags=1;
		prt_time();
		totflags=0;

		if (NoPrtCut == NO) prt_hoofd(YES); 
		prt_close();
		_clr_ticket();

		if(ConMessageBox(txttxt[91],txttxt[90],MB_YESNO | MB_ICONEXCLAMATION |MB_ICONWARNING)==IDYES) {

			if(ConMessageBox(txttxt[95],txttxt[90],MB_YESNO)==IDYES) {
				_btw=0;
				_financ=0;
				_cont=1;
				prt_hoofd(2);
				druk_af();
				prt_hoofd(YES);
				prt_close();
				_clr_ticket();
			}

			LastZTotaalPrintedRecords=LastZTotaalProofPrintedRecords;
			LastZTotaalPrintedSeqNr++;
			log_ZTotaalHeaderUpdate();

		}
		else ConMessageBox(txttxt[92],txttxt[90],MB_OK | MB_ICONEXCLAMATION |MB_ICONWARNING);
	}

	ZTotaalPrintingBusy=NO;
  get_cf();
}

static char * CopyString(char *s, char * p)
{
	while (*p) *s++=*p++;
	return s;
}

extern unsigned kaslogfl;


void controle(int PdfAllowed)
{
  int key;
	short jj,mm,dd;
	unsigned dt_kalender_,prev_dt_;
	char nm_pdffile[20];
	CString cstr;
	CFile fil;
 
  _initial();
	dt_kalender_=jddatum;
#if CONTROL2PDF
	char *b;
	b = new char[CTRLPDFSIZE];
	unsigned short int *w = (unsigned short int *)b;

	w[0] = 0x09B0;
	w[1] = 0x0DB4;
	w[2] = 0x0000;
	w[3] = 0x0056;
	w[4] = 0x0076;
	w[5] = 0x0076;
	w[6] = 0x0000;
	w[7] = 0x0304; /// was 0x0304;
	w[8] = 0x0B06;
	w[9] = 0x0450;
	w[10]= 0x0100;
	w[11]= 0x0000;
	JMU_s = (char *) &w[12];
	JMU_s = CopyString(JMU_s,"\xE0\xD4[landscape;]|\xF0");
	TotSpoolBytes=50;
	PrintControl2PDF=NO;
#endif
 start:;
  cls();
  if (contflag&1) _cont=NO;

  disp_panel(0,0,30, 9,PANEL_VER_SMALLER | PANEL_WITH_EDGE,RGB(255,255,0));
  if (kaslogfl&2) { // kaslog per maand, enkel 1 maand tonen met vooruit/achteruit knop
		disp_key(0,9,10,2,23); // vorig
		disp_key(20,9,10,2,24); // volgend
  }  
	else{
    disp_panel(0,8,30, 9,PANEL_VER_SMALLER | PANEL_WITH_EDGE,RGB(255,255,0));
    disp_panel(0,16,30, 9,PANEL_VER_SMALLER | PANEL_WITH_EDGE,RGB(255,255,0));
	}

  disp_key(31, 0, 9,2,44); //druk af 

  disp_ikey(41,0,10,2,501," Maak pdf "); // pdf
	if (XZTotaalDispFlag) disp_ikey(52, 0, 12, 2, 500, txttxt[87]);// z-totaal
  //cstr.Format("%-24s %-31s",GetPtrTxtKey(45),txtper[_periode]); disp_ikey(31, 2,55,2,45, (char *)cstr.operator LPCTSTR());
  disp_key(31, 2,26,2,45);
	disp_key(31, 4,26,2,92); //,txtkey[92]);
  disp_key(31, 6,26,2,106); //,txtkey[106]);
  disp_key(31, 8,26,2,50); //,txtkey[50]);
  disp_key(37,10,20,2,46); //,txtkey[46]);
  disp_key(37,12,20,2,47); //,txtkey[47]);
  disp_key(37,14,20,2,48); //,txtkey[48]);
  disp_key(37,16,20,2,49); //,txtkey[49]);
  disp_key(37,18,20,2,55); //,txtkey[55]);
  disp_key(31,20,26,2,82); //,txtkey[82]);
  disp_key(31,22,29,2,81); //,txtkey[81]);
  disp_key(60,22,19,2,111); //,txtkey[111]);
  disp_key(31,24,38,2,51); //,txtkey[51]);
  disp_key(71, 0, 8,2,22); // ,txtkey[22]);
  disp_vid(58, 2,txtper[_periode],0);
  disp_vid(58, 4,txtvkp[_vkptype],0);
  disp_vid(58, 6,txtverk[_verknr],0);
  disp_vid(58, 8,txtcumper[_cumper],0);
  disp_vid(58,10,txtcont[_cont],0);
  disp_vid(58,12,txtart[_art],0);
  disp_vid(58,14,txtgroep[_groep],0);
  disp_vid(58,16,txtjn[_btw],0);
  disp_vid(58,18,txtjn[_financ],0);
  disp_vid(58,20,txtsel[_select],0);
  beep_fl=NO;
  kalender();
  FOREVER {
    mark_selectie(); sel_disp();
		key=kbchar();beep_fl=GOOD; PrintControl2PDF=NO;
		if ((key / 0x10000) == 0 && (key / 0x100) == 110) { PrintControl2PDF = YES; key = 44; } // verborgen F10 om in PDF af te drukken
		else key/=0x10000; // keycoon
//		key=kbchar()/0x10000; 
		if (key==500) {
		  DrukZTotaal();
			return;
		}
		if(key==501){PrintControl2PDF=YES;key=44;}
    if (key==22) goto end;
		else if(key==23){ // maand achteruit
			prev_dt_=dt_kalender_;
			jddate(dt_kalender_,&jj,&mm,&dd);
			mm--; if(mm<1){mm=12; jj--;} 
     dt_kalender_=datejd(jj,mm,1);
			dclose(logref);
			log_open(-1,dt_kalender_);
			if(logref<0){
				dt_kalender_=prev_dt_; log_open(-1,dt_kalender_);
			}
			goto start;
		}
		else if(key==24){ // maand vooruit
			prev_dt_=dt_kalender_;
			jddate(dt_kalender_,&jj,&mm,&dd);
			mm++; if(mm>12){mm=1; jj++;} 
			dt_kalender_=datejd(jj,mm,1);
			if(dt_kalender_<jddatum){
  			dclose(logref);
	  		log_open(-1,dt_kalender_);
		  	if(logref<0){
			  	dt_kalender_=prev_dt_; log_open(-1,dt_kalender_);
			  }
			} else dt_kalender_=prev_dt_;
			goto start;
		}
    else if (key==44) break;
    else if (key==0) {
			key=sel_upd(); 
      if(key==501){	PrintControl2PDF=YES;key=44;break;} // verborgen F10 om in PDF af te drukken		
			else beep_fl=NO;
		}
    else switch (key) {
      case 45: _upd(txtper   ,&_periode,58, 2); break;
      case 92: _upd(txtvkp   ,&_vkptype,58, 4); break;
      case 106:_upd(txtverk  ,&_verknr, 58, 6); break;
      case 50: _upd(txtcumper,&_cumper ,58, 8); break;
      case 46:
        if (!(contflag&1)) _upd(txtcont  ,&_cont   ,58,10);
        break;
      case 47: _upd(txtart   ,&_art    ,58,12); break;
      case 48: _upd(txtgroep ,&_groep  ,58,14); break;
      case 49: _upd(txtjn    ,&_btw    ,58,16); break;
      case 55: _upd(txtjn    ,&_financ ,58,18); break;
      case 82: _upd(txtsel   ,&_select ,58,20); break;
      case 81: upd_grp(); goto start;
      case 111:upd_eti(); goto start;
      case 51: put_cf(); break;
      default: beep_fl=BAD;
    }
  }
  beep_ok();
	if(PrintControl2PDF){
		cls();ConStyle(0);
		disp_vid(10,10,"De pdf wordt aangemaakt. Even geduld aub...",0);kbcharnw();
	}
  if (_vkptype==3 || _vkptype==4) {
    if (_vkptype==4) {_vkptype=0; druk_af(); _cont=NO;}
    _vkptype=1; druk_af(); //_cont=NO;
    _vkptype=2; druk_af();
  }
  else druk_af();
  beep_fl=NO;

#if CONTROL2PDF
	if(PrintControl2PDF){
		int len = (JMU_s-b);

		fil.Open("control.spl",CFile::modeCreate|CFile::modeWrite);
		fil.Write(b,len);
		fil.Close();

//		if(pDocControle==NULL){
		pDocControle=new CJmuDoc();
	
		pDocControle->ReadDocument("control.spl",0,true);
		for (int j=0; j<4; j++) {
			pDocControle->BedrukkingFlag[j]=false;
		}
		memset(nm_pdffile,0,sizeof nm_pdffile);
    jddate(lst_dag,&jj,&mm,&dd);
    if (_cumper==1) {
			sprintf_s(nm_pdffile,20,"%04d%02d%02d.pdf",jj,mm,dd);
				//int2str(dd,lijn+ 5, 2); lijn[ 7]='/';
				//int2str(mm,lijn+ 8,-2); lijn[10]='/';
				//int2str(jj,lijn+11,-4); lijn[20]=0;
    }
    else if (_cumper==2) {
			sprintf_s(nm_pdffile,20,"%04dWK%02d.pdf",jj,lst_week);
      //movmem(txttxt[15],lijn+ 4,4);
      //int2str(lst_week,lijn + 9,2); lijn[11]='/';
      //int2str(jj,lijn+12, 4); lijn[20]=0;
    }
    else if (_cumper==3) {
			sprintf_s(nm_pdffile,20,"%04d_%3s.pdf",jj,txtmnd[lst_maand-1]);
      //movmem(txtmnd[lst_maand-1],lijn+6,3);
      //int2str(jj,lijn+10, 4); lijn[20]=0;
    }
    else {
			sprintf_s(nm_pdffile,20,"Globaal.pdf");
    }
		pDocControle->Convert2Pdf("control.spl",nm_pdffile); // "Controle.pdf");
		CFile::Remove("control.spl");
		//if (pDocControle) {
		//	delete pDocControle;
		//	pDocControle=NULL;
		//};
//	KASSA LOOPT VAST (CONSELECT) ALS IK DIT DOE : 	::ShellExecute(NULL,"OPEN","Controle.pdf",NULL,NULL,SW_SHOW);
		PrintControl2PDF=NO; // uit veiligheid
	}
#endif

end:;
#if CONTROL2PDF
	delete [] b;
#endif
  if (kaslogfl&2) { // kaslog per maand, zeker recente kaslog openen
		dclose(logref);log_open(-1,0);
  }  
  _end();
}

static void kalender(void)
{
  char buf[12];
  int i, dagen, lijn, j, dg, attr, day_ix, x, y, week, dag_nr,q_maanden_=3;
  short jj, mm, dd;
	int dag_aantal,maand;
  unsigned datum, jd_eerste, jd_volgende;
  long next_rec;
 
  zeroes((char *)&day[0],sizeof(day));
  day_used=0;
  dag_aantal=1+log_getdag(-1);
  if (dag_aantal==0) {get_tijd(); dag.datum=jddatum;}
  if (dag.datum>jddatum) dag.datum=jddatum; /* door MS-DOS datum terug te zetten
                                               kan men langer dan 3 maanden
                                               terug gaan tov laatste boeking */

  jddate(dag.datum,&jj,&mm,&dd);
	if (kaslogfl&2) { // kaslog per maand, enkel 1 maand tonen met vooruit/achteruit knop
		q_maanden_=1;
	}
	else{
    mm-=2; if (mm<1) {mm+=12; jj--;}
		q_maanden_=3;
	}
  jd_eerste=datejd(jj,mm,1); dg=(jd_eerste+2)%7;
  dag.datum=0;/* voor lege dagen */
  dag_nr=0; log_getdag(dag_nr++); day_ix=0;
  next_rec=log_getrec((long)-1);
  for (j=0; j<q_maanden_; j++) {
    buf[0]=' ';
    movmem(txtmnd[mm-1],&buf[1],3); buf[4]='.'; buf[5]=' ';
    int2str(jj,&buf[6],4); buf[10]=' '; buf[11]=0;
    disp_vid(12,1+j*8,buf,0); lijn=2+j*8;
    maand=mm++; if (mm>12) {mm-=12; jj++;}
    jd_volgende=datejd(jj,mm,1);
    dagen=jd_volgende-jd_eerste; buf[2]=0;
    week=week_nr(jd_eerste);
    for (i=1; i<=dagen; i++) {
      datum=jd_eerste+i-1;
      attr=0; x=7+dg*3; y=lijn;
      day[day_ix].maand=maand;
      day[day_ix].week=week;
      FOREVER {
        if (dag.datum==0xFFFF) break;
        if (dag.datum>jddatum || datum>dag.datum) {
          if (dag_nr>dag_aantal) dag.datum=0xFFFF;
          else log_getdag(dag_nr++);
        }
        if (dag.datum<=jddatum && datum<=dag.datum) break;
      }
/* oude code ipv van de FOREVER lus
      while (datum>dag.datum) {
        if (dag_nr>dag_aantal) dag.datum=0xFFFF;
        else log_getdag(dag_nr++);
      }
*/
			if (dag.first_rec==next_rec) {
			}
      else if (datum==dag.datum) {
        day[day_ix].datum=datum;
        day[day_ix].first_rec=dag.first_rec;
        attr=8;
        day[day_ix].pos=y*80+x;
      }
      int2str(i,buf,2); disp_vid(x,y,buf,attr);
      int2str(week,buf,2); disp_vid(2,y,buf,0);
      if (++dg==7) {dg=0; lijn++; week=week_nr(datum+1);}
      day_ix++;
    }
    jd_eerste=jd_volgende;
  }
  day_used=day_ix;
/* vul next_rec in */
  for (i=day_used-1; i>=0; i--) {
    if (day[i].datum) {
      day[i].next_rec=next_rec;
      next_rec=day[i].first_rec;
    }
  }
}

static int week_nr(unsigned datum)
{
  int j,week,dg,adj;
	short jj, mm, dd;
  unsigned nieuwjaar;

  jddate(datum,&jj,&mm,&dd);
  nieuwjaar=datejd(jj,1,1);
  dg=(nieuwjaar+2)%7;
  if (dg<=3) adj=dg; else adj=dg-7;/* nieuwjaar <= do, dan in week 1 */
  j=datum-(nieuwjaar-adj);
  if (j<0) {
    nieuwjaar=datejd(jj-1,1,1);
    dg=(nieuwjaar+2)%7;
    if (dg<=3) adj=dg; else adj=-dg;
    j=datum-(nieuwjaar-adj);
  }
  week=1+j/7;
  return week;
}
 
static void sel_disp(void)
{
  char buf[3];
  int i,pos,attr;
	short jj, mm, dd;
 
  for (i=0; i<day_used; i++) {
    pos=day[i].pos;
    if (pos) {
      if (day[i].selected) attr=15; else attr=8;
      jddate(day[i].datum,&jj,&mm,&dd);
      buf[0]=' ';
      int2str(dd,buf,2); buf[2]=0;
      disp_vid(pos%80,pos/80,buf,attr);
    }
  }
}
 
static int sel_upd(void)
{
  int i,j,x,y,pos,dg,i_start, i_stop,ret_key_=0;

  x=mspos_h; y=mspos_v;
  pos=x+y*80;
  if(mspos_h<=1 && mspos_v<=1) return 110; // linksboven in kalender gedrukt : verborgen toets voor controleband in PDF
  for (i=0; i<day_used; i++) {
    if (pos==day[i].pos || pos==day[i].pos+1) {
      i_start=i; i_stop=i;
      if (contflag&2) {
        dg=(day[i].datum+2)%7;
        if (dg>=5 && dg<=6) {  
          i_start=i+5-dg;
          i_stop =i_start+2;
          _cumper=0;
        }
        if (dg==0) {
          i_start=i-2;
          if (i_start<0) i_start=0;
          i_stop=i;
          _cumper=0;
        }
      }
      for (j=i_start; j<=i_stop; j++) {
        if (day[j].datum) day[j].selected=day[j].selected^1;
      }
      break;
    }
  }
  if (i>=day_used) beep_bad(); else beep_ok();
	return 0;
}
 
static void _upd(char *txt[], int *pi, int x, int y)
{
  if (txt[++*pi]==0) *pi=0;
  disp_clr(x,y,80-x,1);
  disp_vid(x,y,txt[*pi],0);
}

static void _initial(void)
{
  get_cf();
  _printed=NO;
}

static void _end(void)
{
  if (NoPrtCut==NO && _printed) prt_hoofd(YES);
  prt_close();
  _clr_ticket();
}
 
static void get_cf(void)
{
  _periode=cf_periode; _cont=cf_cont; _art=cf_art; _groep=cf_groep;
  _btw=cf_btw; _cumper=cf_cumper; _financ=cf_financ; _select=0;
  _vkptype=cf_vkptype; _verknr=cf_verknr;
}

static void put_cf(void)
{
  cf_periode=_periode; cf_cont=_cont; cf_art=_art; cf_groep=_groep;
  cf_btw=_btw; cf_cumper=_cumper; cf_financ=_financ; cf_vkptype=_vkptype;
  cf_verknr=_verknr;
  kassys.upd_sys();
}
 
static void druk_af(void)
{
  char _week, _maand, cont_used, fl_partic, fl_retour, fl_eti, fl_used;
  int j,day_ix, _vkpsave, nr;
  long rec_ix, prev_ix;

  if (_cont || _art || _groep || _btw || _financ) {
    clr_data();
    lst_maand=-1; lst_week=-1; lst_dag=-1; _week=NO; _maand=NO;
    cont_used=NO;
    for (day_ix=0; day_ix<day_used; day_ix++) {
      if (day[day_ix].selected) {
        if (lst_maand!=day[day_ix].maand) {
          if (lst_maand>0) _maand=YES;
        }
        if (lst_week!=day[day_ix].week) {
          if (lst_week>0) _week=YES;
        }
        if (_cumper==1 || (_cumper==2 && _week) || (_cumper==3 && _maand)) {
          prt_data();
          clr_data();
          _week=NO; _maand=NO; cont_used=NO;
        }
        lst_dag=day[day_ix].datum; lst_week=day[day_ix].week;
        lst_maand=day[day_ix].maand;
        rec_ix=day[day_ix].first_rec;
        while (rec_ix<day[day_ix].next_rec) {
          prev_ix=rec_ix;
          rec_ix=log_getrec(rec_ix);
          clnrec(prev_ix);
          fl_partic=YES; fl_retour=NO;
          fl_eti=NO; fl_used=NO; nr=-1;
          for (j=0; j<p_vrk->used; j++) {
            if (p_vrk->lijn[j].groep==GRP_TIJD) {
              stcd_i(&p_vrk->lijn[j].text[8],&nr);
              break;
            }
          }
          for (j=0; j<4; j++) {
            if (etikstar[j]) {
              fl_used=YES;
              if ((etikstar[j]<=nr) && (nr<=etikstop[j])) fl_eti=YES;
            }
          }
          if (!fl_used) fl_eti=YES;
          if (!fl_eti) goto next;
          j=p_vrk->lijn[p_vrk->used-1].text[2];
          if (_verknr && (_verknr!=(j-'A'+1))) goto next;
          for (j=p_vrk->used-1; j>=0; j--) {/* laatste lijn is datum */
            p_lin=(struct s_lijn *)&p_vrk->lijn[j].text;
            if (p_lin->groep==GRP_FAKT) fl_partic=NO;
            else if (p_lin->groep==GRP_TEGOED) fl_retour=YES;
            else if (p_lin->totaal<0.) {
              if (p_lin->groep>0 && p_lin->groep<1000 && p_lin->groep!=groep_leeg) {
                fl_retour=YES;
              }
              else if (p_lin->groep==GRP_TOTAAL) {
                fl_retour=YES;
              }
            }
            if (p_lin->groep!=GRP_TIJD) adj_text(j);
          }
					if (ZTotaalPrintingBusy) {
						if (rec_ix<=LastZTotaalPrintedRecords) goto next;
					}
          if (_vkptype==0 || (_vkptype==1 && fl_partic) || (_vkptype==2 && !fl_partic)) {
            if (_cont) { /* deze routine staat nu in deze lus, vroeger stond het ervoor !! */
              if (!cont_used) {
                cont_used=YES;
                _vkpsave=_vkptype; _vkptype=0;
                prt_titel(txttxt[8],"");
                _vkptype=_vkpsave;
                if (totflags&4) prtlstnr(day[day_ix].first_rec);
              }
              if (_cont!=2 || fl_retour) prt_body(1);
            }
            chk_init();
						if (!ticket_first[0]) memcpy(ticket_first,p_vrk->lijn[p_vrk->used-1].text,41);
						memcpy(ticket_last,p_vrk->lijn[p_vrk->used-1].text,41);
						LastZTotaalProofPrintedRecords=rec_ix;
            add_data();
            if (!not_check) chk_exec();
          }
         next:;
        }
      }
    }
    if (cont_used) prt_time();
    prt_data();
	if (NoPrtCut) {prt_nl(" ");	prt_nl(" "); }
  }
	prt_close();
}

static void chk_init(void)
{
  art_chk =art_totaal;
  grp_chk =grp_totaal;
  btw_chk =btw_totaal;
  finv_chk=fin_reg[0][ 4];
  fino_chk=fin_reg[0][16]-fin_reg[0][27];
}

static int chk_exec(void)
{
  char err, line[45];
  double diff, diff2,max_diff;
 
  calc_data(1);
  if (art_chk+art_totaal) diff=art_totaal-art_chk;
  else if (grp_chk+grp_totaal) diff=grp_totaal-grp_chk;
  else if (btw_chk+btw_totaal) diff=btw_totaal-btw_chk;
  else if (finv_chk+fin_reg[0][4]) diff=fin_reg[0][4]-finv_chk;
  else if (fino_chk+fin_reg[0][16]-fin_reg[0][27]) diff=fin_reg[0][16]-fin_reg[0][27]-fino_chk;
  else return NO;
  err=NO;
  diff2=art_totaal-art_chk;
	max_diff=def_round;
	if (btw_round>def_round) max_diff=btw_round;
	max_diff*=1.4999;
  if (diff2 && ((diff2-diff>max_diff)||(diff2-diff<-max_diff))) err=YES;
  diff2=grp_totaal-grp_chk;
  if (diff2 && ((diff2-diff>max_diff)||(diff2-diff<-max_diff))) err=YES;
  diff2=btw_totaal-btw_chk;
  if (diff2 && ((diff2-diff>max_diff)||(diff2-diff<-max_diff))) err=YES;
  diff2=fin_reg[0][4]-finv_chk;
  if (diff2 && ((diff2-diff>max_diff)||(diff2-diff<-max_diff))) err=YES;
  diff2=fin_reg[0][16]-fin_reg[0][27]-fino_chk;
  if (diff2 && ((diff2-diff>max_diff)||(diff2-diff<-max_diff))) err=YES;
  if (err) {
    prt_nl("***************************************");
    prt_nl("Error on total checksum. Check this :");
    prt_body(1);
    _clr_text(line);
    conv_getal(diff,line+0,13,YES,2);
    conv_getal(diff2,  line+13,13,YES,2);
    prt_nl(line);
    _clr_text(line);
    conv_getal(art_totaal,line+0,13,YES,2);
    conv_getal(art_chk,  line+13,13,YES,2);
    conv_getal(art_totaal-art_chk,line+26,13,YES,2);
    prt_nl(line);
    _clr_text(line);
    conv_getal(grp_totaal,line+0,13,YES,2);
    conv_getal(grp_chk,  line+13,13,YES,2);
    conv_getal(grp_totaal-grp_chk,line+26,13,YES,2);
    prt_nl(line);
    _clr_text(line);
    conv_getal(btw_totaal,line+0,13,YES,2);
    conv_getal(btw_chk,  line+13,13,YES,2);
    conv_getal(btw_totaal-btw_chk,line+26,13,YES,2);
    prt_nl(line);
    _clr_text(line);
    conv_getal(fin_reg[0][ 4],line+0,13,YES,2);
    conv_getal(finv_chk,     line+13,13,YES,2);
    conv_getal(fin_reg[0][ 4]-finv_chk,line+26,13,YES,2);
    prt_nl(line);
    _clr_text(line);
    conv_getal(fin_reg[0][16],line+0,13,YES,2);
    conv_getal(fino_chk,     line+13,13,YES,2);
    conv_getal(fin_reg[0][16]-fin_reg[0][27]-fino_chk,line+26,13,YES,2);
    prt_nl(line);
    prt_nl("***************************************");
  }
  return YES;
}
 
static void add_data()
{
  char *p;
  int i, j, b, ix, used, grp_ix, subgrp_ix, plu_ix, art_ix, len, val_ix;
  double coeff, tot_grp_n_selected;

  val_ix=0; coeff=1.;
  klt_totaal++;
  used=p_vrk->used; p_lin=(struct s_lijn *)&p_vrk->lijn[0].text;
  tot_grp_n_selected=0.; plu_ix=-1;
  for (i=0; i<used; i++) {
    grp_ix=p_lin->groep; ix=-1;
    if (grp_ix>=-9 && grp_ix<1000) {
 
      if ((plu_ix=kasplu.plu_req(p_lin->code,ARTCODE_LEN))<0) {
        p=(char *)&kasplu.art_info; len=sizeof(kasplu.art_info);
        while (len-->0) *p++=0;
        kasplu.art_info.code[0]='G';
        if (grp_ix<0) {
          for (j=i-1; j>=0; j--) {
            if (p_vrk->lijn[j].groep!=groep_leeg) {
              grp_ix=p_vrk->lijn[j].groep;
              break;
            }
          }
          if (grp_ix<0 || grp_ix>=1000) grp_ix=1;
        }
        int2str(grp_ix,&kasplu.art_info.code[1],3);
        movmem("} ",kasplu.art_info.naam,2);
        movmem(grp_info[grp_ix].naam,&kasplu.art_info.naam[2],18);
        kasplu.art_info.groep=grp_ix;
        plu_ix=-1-grp_ix;
      }
      if (grp_ix<0) grp_ix=kasplu.art_info.groep;/* korting, use groep of artikel */

      if (_select==1 && grp_ix>=0 && grp_bits[grp_ix]&1) {
        tot_grp_n_selected+=p_lin->totaal;
        goto skip;                         /* zie ook verder voor kortingen */
      }
      ix=0;      /* indien niet geselecteerd, dan ook niet bij goederen mee */

      if (grp_ix<0 && plu_ix>=0) {
        grp_ix=kasplu.art_info.groep;
        if (_select==1 && grp_ix>=0 && grp_bits[grp_ix]&1) {
          tot_grp_n_selected+=p_lin->totaal;
          goto skip;/* skippen van korting in niet-geselect. groepen */
        }
      }
 
      if (_art) {
        art_ix=find_artix(plu_ix);
        art_lin=&art_cumul[art_ix];
        if (!art_lin->code[0]) {
          movmem(kasplu.art_info.code,art_lin->code,sizeof(kasplu.art_info.code));
          movmem(kasplu.art_info.naam,art_lin->naam,sizeof(kasplu.art_info.naam));
          art_lin->groep=kasplu.art_info.groep;
          art_lin->st_verp=kasplu.art_info.st_verp;
        }
        if (p_lin->bits & 1) art_lin->aantal_st+=p_lin->aantal;
        else art_lin->aantal+=p_lin->aantal;
        art_lin->totaal+=p_lin->totaal;
      }
      if (grp_ix>0) {
        grp_lin=&grp_cumul[grp_ix];
        if ((p_lin->bits & 1) && kasplu.art_info.st_verp>1) {
          grp_lin->aantal+=(p_lin->aantal/kasplu.art_info.st_verp);
        }
        else grp_lin->aantal+=p_lin->aantal;
        grp_lin->totaal+=p_lin->totaal;
				for (b=0; b<4; b++) {
				  if (p_lin->btw==grp_lin->btw[b]) break;
				}
				if (b==4) {
				  for (b=0; b<4; b++) {
					  if (!grp_lin->btw_used[b]) {
						  grp_lin->btw_used[b]=YES;
						  grp_lin->btw[b]=p_lin->btw;
						  break;
						}
					}
				}
				if (b<4) {
				  grp_lin->btw_aantal[b]+=p_lin->aantal;
					grp_lin->btw_totaal[b]+=p_lin->totaal;
				}
      }
 
      add_btw();
 
      if (grp_ix==groep_leeg) {
        if (p_lin->totaal>0) ix=1; else ix=2;
      }
     skip:;
    }
 
		subgrp_ix=-1;
    if (_financ && ((grp_ix>=1000 && grp_ix<1030) || (grp_ix>=1040 && grp_ix<1050))) {
      switch (grp_ix) {
        case GRP_TEGOED:        ix=14; break;
        case GRP_TERUG:         ix= 6; break;
        case GRP_GELD:          ix= 5; break;
				case GRP_VOORSCHOT_B:		ix=24; break;
				case GRP_VOORSCHOT_R:		ix=25; break;
        case GRP_ECHEQUE:
					subgrp_ix=(int)(p_lin->aantal+.001);
					ix= 8; break;
        case GRP_BANCONT:       ix= 9; break;
        case GRP_MAALTIJD:      ix=11; break;
        case GRP_TGBON:         ix=13; break;
        case GRP_LEVERBON:      ix=12; break;
        case GRP_CREDIT:        ix=10; break;
        case GRP_TBSALDO:       ix=19; break;
        case GRP_DIVUITGAVE:    ix=20; break;
        case GRP_DIVONTVANG:    ix=21; break;
        case GRP_ZEGELS:        ix=22; break;
        case GRP_MOBIEL:        ix=23; break;
        case GRP_CDBON_VRK:     ix=28; break;
        case GRP_CDBON_BET:     ix=29; break;
        case GRP_VAR_BET1:      ix=30; break;
        case GRP_VAR_BET2:      ix=31; break;
        case GRP_VAR_BET3:      ix=32; break;
		case GRP_AFRONDING:     ix=33; break;
		case GRP_EMAALTIJD:      ix = 34; break;
		case GRP_EECOCHEQUE:      ix = 35; break;
		case GRP_ECADEAUBON:      ix = 36; break;
		case GRP_ECONSUMBON:      ix = 37; break;
		case GRP_CASHAUT:         ix = 38; break;
        default:                ix=-1; break;
      }
    }

    if (ix>=0) {
      if (ix==12 || ix==19 || ix==29) { // || ix==21 || ix==20) {
        p_lin->totaal = -p_lin->totaal;
      }
      fin_reg[val_ix][ix]+=p_lin->totaal;/* in de valuta zelf */
      if (val_ix) fin_reg[val_ix+10][ix]+=round_it(p_lin->totaal*coeff,def_round);
			if (subgrp_ix>=0 && subgrp_ix<SUBGRP_COUNT) eCheqTotSubGrpt[subgrp_ix]+=p_lin->totaal;
    }

    if (_financ && (grp_ix==GRP_CONVERT)) {
      j=(int)p_lin->btw;
      if (j>0 && j<=VAL_COUNT) {
        val_ix=j; coeff=p_lin->aantal;
      }
      else {val_ix=0; coeff=1.;}
    }
 
    p_lin++;
  }
  if (_financ) fin_reg[0][5]-=tot_grp_n_selected;
}

static void prt_data()
{
  calc_data(0);
  if (_art && art_totaal) prt_art();
  if (_groep && grp_totaal) prt_groep();
  if (_btw && btw_totaal) prt_btw(YES);
  if (_financ && fin_totaal[0]) prt_financ();
}
 
void prt_art()
{
  char line[45], *header;
  int art_ix, last_grp, len;
                                                
  header=txttxt[17];
  if (_art>=3) header="";
  prt_titel(txttxt[9],header);
  last_grp=-1;
  for (art_ix=0; art_ix<cumart_used; art_ix++) {
    art_lin=&art_cumul[art_ix];
    if (_art>=3 && last_grp!=art_lin->groep) {
      prt_gtot(last_grp);
      _clr_text(line);
      if (last_grp>=0) prt_nl(line);
      copynaam(grp_info[art_lin->groep].naam,line,20); line[20]=0;
      prt_cod(2); prt_cod(3); prt_nl(line); prt_cod(4);
      last_grp=art_lin->groep;
      prt_nlu(txttxt[17]);
    }
    _clr_text(line);
    copynaam(art_lin->code,line  ,ARTCODE_LEN);
    copynaam(art_lin->naam,line+6,20);
    len=8;
    if (art_lin->aantal_st) {
      line[30]='/';
      conv_getal(art_lin->aantal_st,line+31,2,0x04,2);
      len=5;
    }
    conv_getal(art_lin->aantal,line+25,len,0x04,0);
    conv_getal(art_lin->totaal,line+33,7,0x00,def_digits);
    if (art_lin->aantal || art_lin->totaal<-def_round/2 || art_lin->totaal>def_round/2) {
      prt_nl(line);
    }
  }
  if (_art>=3) {prt_gtot(last_grp); prt_cod(7);}
  print_footer(art_totaal);
  prt_time();
	prt_close();
}

void prt_gtot(int last_grp)
{
  char line[45];
  int i;
 
  if (last_grp>0 && grp_cumul[last_grp].totaal) {
    _clr_text(line);
    prt_cod(2);
    _clr_text(line); for (i=0; i<40; i++) line[i]='-'; prt_nl(line);
    prt_cod(2);
    copynaam(txttxt[14],line+6,8);
    conv_getal(grp_cumul[last_grp].aantal,line+20,10,YES,2);
    conv_getal(grp_cumul[last_grp].totaal,line+30,10,YES,2);
    prt_nl(line);
  }
}

void prt_groep()
{
  char line[45];
  int grp_ix, i;
                                                
  prt_titel(txttxt[10],txttxt[13]);
  for (grp_ix=0; grp_ix<CUMGRP_COUNT; grp_ix++) {
    if (grp_cumul[grp_ix].totaal) {
      _clr_text(line);
      int2str(grp_ix,line+0,3);
      if (_groep>1) {
        copynaam(grp_info[grp_ix].naam,line+4,20);
        prt_nl(line); _clr_text(line);
      }
      conv_getal(grp_cumul[grp_ix].aantal,line+6,12,YES,2);
      conv_getal(grp_cumul[grp_ix].totaal,line+19,12,YES,def_digits);
      if (grp_ix!=groep_leeg) {
        sprintf(line+32,"%6.1f %%",grp_cumul[grp_ix].percent);
      }
      prt_nl(line);
      if (_groep>3) {
				for (i=0; i<4; i++) {
				  if (grp_cumul[grp_ix].btw[i]==0) continue;
					_clr_text(line);
					conv_getal(grp_cumul[grp_ix].btw[i],line,4,YES,2);
					conv_getal(grp_cumul[grp_ix].btw_aantal[i],line+6,12,YES,def_digits);
					conv_getal(grp_cumul[grp_ix].btw_totaal[i],line+19,12,YES,def_digits);
					prt_cod(2); prt_nl(line);
				}
      }
      if (_groep>2) {_clr_text(line); prt_nl(line);}
    }
  }
  print_footer(grp_totaal);
  prt_time();
  prt_close();
}
  
void prt_financ()
{
  char line[45], attr, digits, _digits;
  double klt_bedrag, TotaleCheq=0.,bd_;
  int pos, j, ii, i, _i, val_ix, digcnt;
                                     
	for (j=0; j<SUBGRP_COUNT; j++) {
		TotaleCheq+=eCheqTotSubGrpt[j];
	}
	fin_reg[0][8]-=TotaleCheq;

  prt_titel(txttxt[22],""); val_ix=0;
  for (val_ix=0; val_ix<=VAL_COUNT; val_ix++) {
    if (fin_reg[val_ix][16]==0 && fin_reg[val_ix][19]==0) goto skip;
    if (val_ix>0) {
      prt_nl("");
      prt_cod(2); prt_nl("----------------------------------------");
      _clr_text(line); prt_cod(2); prt_cod(3);
      sprintf(line+22,txttxt[54],valuta[val_ix-1].naam);
      prt_nl(line+20); prt_cod(4);
      prt_nl("");
      digits=valuta[val_ix-1].digits;
    }
    else digits=def_digits;
    for (_i=0; _i<FIN_COUNT; _i++) {
      i=fin_prt[_i];
      attr=fin_attr[_i];
      _digits=digits;
      if (i==17 && fin_reg[val_ix][i]<1.) _digits=6;
      if (fin_reg[val_ix][i] || (val_ix==0 && i==8 && TotaleCheq)) {
        _clr_text(line); pos=0;
        if (attr&1) prt_cod(2);
        if (attr&4) {prt_cod(3); pos=20;}
				copynaam(txtfin[i],line+pos,25);
        if (i==18) {
          _digits=def_digits;
          for (j=39; j>=0; j--) if (line[j]>' ') break;
          j+=2;
          copynaam(def_valuta,line+j,3);
        }
        digcnt=15;
				if (attr==0) digcnt-=3;
				if (fin_reg[val_ix][i]){
					bd_=fin_reg[val_ix][i]; if(i==28) bd_=-bd_; // bij verkoop cadeaubon negatief zetten
					conv_getal(bd_,line+25,digcnt,0x05,_digits);
				}
        prt_nl(line+pos);
        if (pos==20) prt_cod(4);
        if (attr&2) prt_nl("========================================");
        if (attr&8) {_clr_text(line); prt_nl(line);}
			}
      if (val_ix==0 && i==7) {
        for (j=1; j<=VAL_COUNT; j++) {
          if (fin_reg[j][16]) {
            _clr_text(line); prt_cod(2);
            sprintf(line,txttxt[54],valuta[j-1].naam);
            for (ii=0; ii<40; ii++) if (line[ii]==0) {line[ii]=' '; break;}
            conv_getal(fin_reg[j+10][16],line+25,15,0x05,digits);
            prt_nl(line);
          }
        }
      }
			if (val_ix==0 && i==8 && TotaleCheq!=0.) { // eCheques
				for (j=0; j<SUBGRP_COUNT; j++) {
					if (eCheqTotSubGrpt[j]<-0.001 || eCheqTotSubGrpt[j]>0.001) {
						_clr_text(line);
						switch (j) {
							case 4: copynaam("  Sodexo",line,30); break;
							case 5: copynaam("  Edenred",line,30); break;
							case 6: copynaam("  PayFair-Monizze",line,30); break;
							case 7: copynaam("  RES",line,30); break;
							default:copynaam("  Unknown",line,30); break;
						}
						conv_getal(eCheqTotSubGrpt[j],line+25,15,0x05,2);
						prt_nl(line);
					}
				}
			}    }
   skip:;
    if (val_ix==0) {
      if (!ZTotaalPrintingBusy && ((totflags&2)==0)) {
        prt_cod(3); _clr_text(line);
        copynaam(txttxt[52],line+20,20);
        conv_getal((double)klt_totaal,line+35,5,0x05,2);
        prt_nl(line+20); prt_cod(4);
        if (klt_totaal) klt_bedrag=fin_reg[0][4]/klt_totaal; else klt_bedrag=0.;
        klt_bedrag=round_it(klt_bedrag,btw_round);
        prt_cod(3); _clr_text(line);
        copynaam(txttxt[55],line+20,20);
        conv_getal((double)klt_bedrag,line+33,7,0x05,digits);
        prt_nl(line+20); prt_cod(4);
      }
    }
  }

  prt_time();
  prt_close();
}

static int _compare(char *p1, char *p2, int dummy)
{
  struct s_art_cumul *p_art1, *p_art2;

	p_art1=(struct s_art_cumul *)p1; p_art2=(struct s_art_cumul *)p2;
	if (_art>=3) {
    if (p_art1->groep < p_art2->groep) return -1;
    if (p_art1->groep > p_art2->groep) return  1;
  }
  if (_art==1 || _art==3) {
    return _cmpstr(p_art1->code,p_art2->code,ARTCODE_LEN);
  }
  if (_art==2 || _art==4) {
    return _cmpstr(p_art1->naam,p_art2->naam,sizeof(p_art2->naam));
  }
  return 0;
}

void clnrec(long recix)
{
  int i, j, reccnt, recalc;
  long k;
  char buf[200];
  double corr;

  if (kasplu.clncount>0) {
    reccnt=0; corr=0.;
    sprintf(buf,"recix=%6ld   first=%6ld   prx=%6f  unit=%4d",recix,kasplu.cln[0].pos,kasplu.cln[0].prx,kasplu.cln[0].unit);
    /* debdump(buf); */
    for (j=0; j<kasplu.clncount; j++) {
      recalc=NO;
      if (kasplu.cln[j].pos>=recix && kasplu.cln[j].pos<(recix+p_vrk->used-reccnt)) {
        k=kasplu.cln[j].pos-recix-reccnt;
        corr+=p_vrk->lijn[k].totaal;
        if (kasplu.cln[j].unit) {
          p_vrk->lijn[k].aantal=(float)kasplu.cln[j].unit;
          recalc=YES;
        }
        if (kasplu.cln[j].prx!=0.) {
          p_vrk->lijn[k].prijs=kasplu.cln[j].prx;
          recalc=YES;
        }
        if (!recalc) {
          movmem((char *)p_vrk->lijn[k+1].code,(char *)p_vrk->lijn[k].code,sizeof(struct s_lijn)*(p_vrk->used-reccnt-k));
          reccnt++;
        }
        else {
          recalc=NO;
          p_vrk->lijn[k].totaal=p_vrk->lijn[k].prijs * p_vrk->lijn[k].aantal;
          corr-=p_vrk->lijn[k].totaal;
        }
      }
    }
    if (corr!=0.) {
      p_vrk->used-=reccnt;
      k=-1;
      for (i=0; i<p_vrk->used; i++) {
        switch (p_vrk->lijn[i].groep) {
          case GRP_GELD:
            k=i;
          case GRP_TOTAAL:
          case GRP_GOEDEREN:
          case GRP_TBSALDO: 
            p_vrk->lijn[i].totaal-=corr;
            break;
          case GRP_TERUG:   
            p_vrk->lijn[i].totaal+=corr;
            if (k>=0) p_vrk->lijn[k].totaal+=corr;
            break;
          case GRP_EURO:
            p_vrk->lijn[i].totaal-=(corr/valuta[(int)p_vrk->lijn[i].btw-1].coeff);
            break;
        }
      }
    }
  }
}
                                        
static int _cmpstr(char *s1,char *s2,int len)
{
  while (len-->0) {
    if (*s1<*s2) return -1;
    else if (*s1>*s2) return 1;
    else {s1++; s2++;}
  }
  return 0;
}
 
static void calc_data(char fast)
{
  int i, ix, art_ix, grp_ix, val_ix;
  long l;
  float f;
  double d;

  if (_art>=1 && _art<=4) {
    if (!fast) jsort(art_cumul,(long) cumart_used,sizeof(struct s_art_cumul),_compare);
    art_totaal=0.;
    for (art_ix=0; art_ix<cumart_used; art_ix++) {
      if (!fast) {
        art_lin=&art_cumul[art_ix];
        l=(long)art_lin->aantal_st;
        if (art_lin->st_verp>1) {
          art_lin->aantal_st=l%art_lin->st_verp;
          art_lin->aantal  +=l/art_lin->st_verp;
        }
      }
      art_totaal+=art_cumul[art_ix].totaal;
    }
  }

  grp_totaal=0.;
  for (grp_ix=0; grp_ix<CUMGRP_COUNT; grp_ix++) {
    if (grp_ix!=groep_leeg) grp_totaal+=grp_cumul[grp_ix].totaal;
  }
  if (!fast && grp_totaal) {
    f=0.; ix=-1; d=0.;
    for (grp_ix=0; grp_ix<CUMGRP_COUNT; grp_ix++) {
      if (grp_ix!=groep_leeg) {
        grp_cumul[grp_ix].percent=(float)(grp_cumul[grp_ix].totaal*100./grp_totaal);
        if (grp_cumul[grp_ix].percent>f) {
          f=grp_cumul[grp_ix].percent; ix=grp_ix;
        }
        grp_cumul[grp_ix].totaal=round_it(grp_cumul[grp_ix].totaal,btw_round);
        d+=grp_cumul[grp_ix].totaal;
      }
    }
    grp_totaal=round_it(grp_totaal,btw_round);
    d-=grp_totaal;
    if (d!=0 && ix>0) {
      grp_cumul[ix].totaal-=d;
    }
  }
  grp_totaal+=grp_cumul[groep_leeg].totaal;

  if (!fast) calc_btw();
  else sum_btw();

  for (val_ix=0; val_ix<=2*VAL_COUNT; val_ix++) {  // hier nakijken 22/02/16
    fin_totaal[val_ix]=0.;
    fin_reg[val_ix][3]=fin_reg[val_ix][1]+fin_reg[val_ix][2];
    fin_reg[val_ix][4]=fin_reg[val_ix][0]+fin_reg[val_ix][3];
    fin_reg[val_ix][26]=fin_reg[val_ix][24]+fin_reg[val_ix][25];
		fin_reg[val_ix][27]=fin_reg[val_ix][19]+fin_reg[val_ix][20]+fin_reg[val_ix][21]+fin_reg[val_ix][26]; 
    if (fast) {
      fin_reg[val_ix][16]=fin_reg[val_ix][ 5]-fin_reg[val_ix][ 6]
                         +fin_reg[val_ix][ 8]+fin_reg[val_ix][ 9]
                         +fin_reg[val_ix][10]+fin_reg[val_ix][11]
                         +fin_reg[val_ix][12]-fin_reg[val_ix][13]
                         -fin_reg[val_ix][14]+fin_reg[val_ix][22]
                         +fin_reg[val_ix][23]
												 -fin_reg[val_ix][28]+fin_reg[val_ix][29] // cadeaubon
												 +fin_reg[val_ix][30]+fin_reg[val_ix][31]+fin_reg[val_ix][32] // variabele betaalknoppen
												 +fin_reg[val_ix][33]; // afronding op 5 cent
							+fin_reg[val_ix][34] + fin_reg[val_ix][35] + fin_reg[val_ix][36] + fin_reg[val_ix][37] // e-maaltijd, e-ecocheque, e-cadeaubon, e-consumbon
							+ fin_reg[val_ix][38]; // CashAut
    }
    else {
      fin_reg[val_ix][6]=-fin_reg[val_ix][6];
      fin_reg[val_ix][7]=fin_reg[val_ix][5]+fin_reg[val_ix][6];
      fin_reg[val_ix][13]=-fin_reg[val_ix][13];
      fin_reg[val_ix][14]=-fin_reg[val_ix][14];
      fin_reg[val_ix][15]=fin_reg[val_ix][13]+fin_reg[val_ix][14];
      fin_reg[val_ix][16]=fin_reg[val_ix][22]+fin_reg[val_ix][23]-fin_reg[val_ix][28]+fin_reg[val_ix][29];
      for (ix=7; ix<=14; ix++) fin_reg[val_ix][16]+=fin_reg[val_ix][ix];
			for (ix=30; ix<=32; ix++) fin_reg[val_ix][16]+=fin_reg[val_ix][ix];// variabele betaalknoppen 1-3 
			fin_reg[val_ix][16]+=fin_reg[val_ix][33]; // afronding kasticket op 5 cent
			for (ix = 34; ix <= 38; ix++) fin_reg[val_ix][16] += fin_reg[val_ix][ix]; // e-maaltijd, e-ecocheque, e-cadeaubon, e-consumbon, CashAut
      for (ix=0; ix<FIN_COUNT; ix++) {
        fin_totaal[val_ix]+=fin_reg[val_ix][ix];
      }
    }
  }
  for (i=1; i<=10; i++) {
    fin_reg[0][16]+=fin_reg[i+10][16];
    if (!fast) {
      if (fin_reg[i+10][16]) fin_reg[i][17]=fin_reg[i+10][16]/fin_reg[i][16];
      fin_reg[i][18]=fin_reg[i+10][16];
    }
  }
}
 
static void clr_data()
{
  char *p;
  long len;

  klt_totaal=0;
  len=(long)cumart_count * cumart_size;
  p=(char *)art_cumul;
  while (len--) *p++=0;
  cumart_used=0;
  len=(long)cumgrp_count * cumgrp_size;
  p=(char *)grp_cumul;
  while (len--) *p++=0;
  clr_btw();
  len=sizeof(fin_reg);
  p=(char *)&fin_reg[0][0];
	while (len--) *p++=0;
  for (int i=0; i<SUBGRP_COUNT; i++) eCheqTotSubGrpt[i]=0;
	art_totaal=0.;
  grp_totaal=0.;
  btw_totaal=0.;
}
 
static int find_artix(int plu_ix)
{
  int i;
 
  for (i=0; i<cumart_used; i++) {
    if (art_cumul[i].plu_ix == plu_ix) return i;
  }
  art_cumul[cumart_used++].plu_ix=plu_ix;
  if (cumart_used>=CUMART_COUNT) disp_exit("To much different ART sold");
  return cumart_used-1;
}
 
static void mark_selectie()
{
  int j, eerste, laatste, i, week, maand, dg, i_start, i_stop;

  for (j=0; j<day_used; j++) day[j].selected&=1;
  if (_periode==0) {
    for (j=0; j<day_used; j++) {
      if (day[j].datum) day[j].selected|=2;
    }
  }
  else if (_periode==1) {
    for (j=0; j<day_used; j++) {
      if (day[j].selected&1) {
        week=-1; maand=-1;
        if (_cumper==2) week=day[j].week;
        else if (_cumper==3) maand=day[j].maand;
        for (i=0; i<day_used; i++) {
          if ((day[i].maand==maand || day[i].week==week) && day[i].datum)
            day[i].selected|=2;
        }
      }
    }
  }
  else if (_periode==2) {
    for (eerste=0; eerste<day_used; eerste++) if (day[eerste].selected) break;
    for (laatste=day_used-1; laatste>=0; laatste--) if (day[laatste].selected) break;
    for (j=eerste; j<=laatste; j++) {
      if (day[j].datum) day[j].selected|=2;
    }
  }
  else if (_periode==3) {
    for (j=day_used-1; j>=0; j--) {
      if (day[j].datum) {day[j].selected|=2; break;}
    }
  }
  if (contflag&2) {
    for (i=0; i<=day_used; i++) {
      if (day[i].selected&2) {
        i_start=-1; i_stop=-1;
        dg=(day[i].datum+2)%7;
        if (dg>=5 && dg<=6) {
          i_start=i+5-dg;
          i_stop =i_start+2;
          if (i_stop>day_used) i_stop=day_used;
          _cumper=0;
          disp_vid(58, 8,txtcumper[_cumper],0);
        }
        if (dg==0) {
          i_start=i-2;
          if (i_start<0) i_start=0;
          i_stop=i;
          _cumper=0;
          disp_vid(58, 8,txtcumper[_cumper],0);
        }
        if (i_start>0) {
          for (j=i_start; j<=i_stop; j++) {
            if (day[j].datum) day[j].selected=day[j].selected|2;
          }
        }
      }
    }
  }
}

void upd_eti()
{
  int key,i,ticketnr;
  char text[10];

  ticketnr=log_getticket()-1;
  if (ticketnr==0) goto end;
  disp_clr(0,0,80,25);
  disp_vid(30,3,GetPtrTxtKey(111),1);
  disp_key(71,0,8,1,22);
  FOREVER {
    for (i=0; i<4; i++) {
      disp_ikey(15,5+i*2,5,1,83+(i+1)*1000,GetPtrTxtKey(83));
      if (etikstar[i]==0) {movmem("  -  ",text,6); etikstop[i]=0;}
      else {
        if (etikstar[i]>ticketnr) etikstar[i]=ticketnr;
        if (etikstar[i]<1) etikstar[i]=1;
        if (etikstar[i]<etikstop[i-1]) etikstar[i]=etikstop[i-1];
        int2str(etikstar[i],text,5);
        text[5]=0;
      }
      disp_vid(22,5+i*2,text,0);
      disp_ikey(28,5+i*2,5,1,84+(i+1)*1000,GetPtrTxtKey(84));
      disp_vid(37,5+i*2,txttxt[65],1);
      disp_ikey(45,5+i*2,5,1,583+(i+1)*1000,GetPtrTxtKey(83));
      if (text[2]!='-') {
        if (etikstop[i]==0) etikstop[i]=ticketnr;
        if (etikstop[i]<etikstar[i]) etikstop[i]=etikstar[i];
        if (etikstop[i]>ticketnr) etikstop[i]=ticketnr;
        int2str(etikstop[i],text,5);
        text[5]=0;
      }
      disp_vid(52,5+i*2,text,0);
      disp_ikey(58,5+i*2,5,1,584+(i+1)*1000,GetPtrTxtKey(84));
    }
    key=kbchar()/0x10000;
    if (key==22) break;
    else beep_fl=BAD;
    if (key>1000) {
      i=(key/1000)-1; key%=1000;
      if (key==83) {
        etikstar[i]--;
        if ((i>0) && (etikstar[i]<etikstop[i-1])) etikstar[i]=0;
      }
      if (key==84) etikstar[i]++;
      if (key==583) {
        etikstop[i]--;
        if (etikstop[i]<etikstar[i]) etikstop[i]=etikstar[i];
      }
      if (key==584) etikstop[i]++;
    }
  }
 end:;
}
 
void upd_grp()
{
  char buf[5], naam[13],all;
  int key,e,t,x,y,nr,j,attr;
 
  disp_clr(0,0,80,25);
  disp_vid(24,0,txttxt[50],1);
  disp_vid(0,24,txttxt[51],0);
  disp_key(71,0,8,1,22);
  all=YES;
  FOREVER {
    nr=0; e=0; t=0; buf[0]=' '; buf[1]=' '; buf[2]=' '; buf[3]=' '; buf[4]=0;
    naam[12]=0;
    for (y=2; y<=21; y++) {
      for (x=0; x<=66; x+=16) {
        if (all) {
          buf[1]='0'+e;
          disp_vid(x,y,buf,8);
          if (++e==10) {
            buf[0]='0'+(++t);
            e=0;
          }
        }
        movmem(grp_info[nr].naam,naam,12);
        for (j=0; j<=11; j++) if (!naam[j]) break;
        for (;j<=11; j++) naam[j]=' ';
        if (grp_bits[nr] & 1) attr=8; else attr=2; // is omgekeerd van vroeger
        disp_vid(x+3,y,naam,attr);
        nr++;
      }
    }
    all=NO;
    key=kbchar();
    if (key==22*0x10000) break;
    else if (key==251*0x100) {
      nr=(mspos_h/16)+(mspos_v-2)*5;
      grp_bits[nr] ^= 1;
    }
    else beep_fl=BAD;
  }
  kassys.upd_sys();
}

// KASCONT2.CPP

/*
extern struct s_lijn *p_lin;

extern struct s_verkopen *verkopen, *p_vrk;

extern char txttxt[100][80], tijd[];
extern int groep_leeg;
extern int totflags;
extern char beep_fl;
extern char *txtmnd[];
extern int def_digits;
extern char def_valuta[];
extern float def_round, btw_round;

*/
 
int lst_maand, lst_week, lst_dag, _printed, _cumper, _vkptype;
double btw_totaal, round_it();

long log_getrec();

/* --------------------------- Declaratie functies ---------------------- */

static int find_btwix(void);

///////////////

void prt_btw(char statist)
{
  char line[45];
  int btw_ix, i, leegg_ix, prtcnt;
  float kleinste;
  double _btw, _basis;
                                                
  if (statist==1) prt_titel(txttxt[11],txttxt[16]);
  else if (statist==2) {
    add_text("----------------------------------------");
    add_text(txttxt[16]);
  }
  _btw=0.; _basis=_btw; leegg_ix=-1;
  FOREVER {
    kleinste=100.;
    for (i=0; i<btw_used; i++) {
      if (btw_cumul[i].btw_perc==-1. && statist==1) {
        leegg_ix=i; btw_cumul[i].btw_perc=1000.;
      }
      if (btw_cumul[i].totaal && btw_cumul[i].btw_perc<kleinste) {
        kleinste=btw_cumul[i].btw_perc;
        btw_ix=i;
      }
    }
    if (kleinste==100.) break;
    _clr_text(line);
    if (btw_cumul[btw_ix].btw_perc==-1.) {
      copynaam(txttxt[21],line,8);
    }
    else {
      conv_getal((double)btw_cumul[btw_ix].btw_perc,line,6,YES,2);
      conv_getal(btw_cumul[btw_ix].basis,line+9,10,YES,def_digits);
      conv_getal(btw_cumul[btw_ix].btw  ,line+19,10,YES,def_digits);
    }
    conv_getal(btw_cumul[btw_ix].totaal,line+30,10,YES,def_digits);
    if (statist==1) prt_nl(line);
    else add_text(line);
    _basis += btw_cumul[btw_ix].basis;
    _btw += btw_cumul[btw_ix].btw;
    btw_cumul[btw_ix].btw_perc=1000.;
  }
  if (statist==1) {
    if (leegg_ix>=0) btw_totaal-=btw_cumul[leegg_ix].totaal;
    print_footer(btw_totaal);
    if (leegg_ix>=0) {
      prt_cod(2); prt_cod(3);
      _clr_text(line); copynaam(txttxt[21],line,8);
      conv_getal(btw_cumul[leegg_ix].totaal,line+8,12,YES,def_digits);
      line[20]=0;
      prt_nl(line); prt_cod(4);
    }
    prt_time();
	if (NoPrtCut) {} //  { prt_nl(" ");	prt_nl(" "); }
	else {
	  prtcnt = 5 + btw_used + 3;
	  if (!ZTotaalPrintingBusy) {
		while (prtcnt < MIN_BTW_LEN) {
		  prt_nl(""); prtcnt++;
		}
	  }
	}
  }
  else if (statist==0) {
    add_text("----------------------------------------");
    _clr_text(line); copynaam(txttxt[14],line,8);
    conv_getal(_basis,line+9,10,YES,def_digits);
    conv_getal(_btw  ,line+19,10,YES,def_digits);
    conv_getal(btw_totaal,line+30,10,YES,def_digits);
    add_text(line); (p_lin-1)->groep=GRP_T_R;
  }
  else if (statist==2) {
    add_text("----------------------------------------");
  }
  prt_close();
}
 
void prt_time(void)
{
  char line[45];
 
 
  if (totflags & 1) {
    get_tijd();
    _clr_text(line);
    movmem(tijd,line,20);
    line[20]=0;
    prt_cod(2); prt_cod(3);
    prt_nl(line); prt_cod(4);
  }
}
 
void sum_btw(void)
{
  int btw_ix;
 
  btw_totaal=0.;
  for (btw_ix=0; btw_ix<btw_used; btw_ix++) {
    btw_totaal+=btw_cumul[btw_ix].totaal;
  }
  btw_totaal=round_it(btw_totaal,btw_round);
}
 
void calc_btw(void)
{
  int btw_ix, max_ix;
  double max_btw, totaal;

  btw_totaal=0.; totaal=0; max_ix=-1; max_btw=-1;
  for (btw_ix=0; btw_ix<btw_used; btw_ix++) {
    btw_totaal+=btw_cumul[btw_ix].totaal;
    btw_cumul[btw_ix].totaal = round_it(btw_cumul[btw_ix].totaal,btw_round);
    totaal+=btw_cumul[btw_ix].totaal;
    if (btw_cumul[btw_ix].btw_perc>0 && btw_cumul[btw_ix].totaal>max_btw) {
      max_btw=btw_cumul[btw_ix].totaal; max_ix=btw_ix;
    }
  }
  btw_totaal=round_it(btw_totaal,btw_round);
  totaal-=btw_totaal;
  if (totaal!=0 && max_ix>0) {
    btw_cumul[max_ix].totaal-=totaal;
  }
  for (btw_ix=0; btw_ix<btw_used; btw_ix++) {
    if (btw_cumul[btw_ix].btw_perc >= 0) {
      btw_cumul[btw_ix].basis=round_it(btw_cumul[btw_ix].totaal/(1.+btw_cumul[btw_ix].btw_perc/100.),btw_round);
      btw_cumul[btw_ix].btw  =btw_cumul[btw_ix].totaal-btw_cumul[btw_ix].basis;
    }
  }
}
 
void clr_btw(void)
{
  char *p;
  long len;
 
  btw_used=0;
  len=sizeof(btw_cumul);
  p=(char *)&btw_cumul;
  while (len--) *p++=0;
}
 
void add_btw(void)
{
  int btw_ix;
 
  btw_ix=find_btwix();
  btw_cumul[btw_ix].totaal+=p_lin->totaal;
}
 
static int find_btwix(void)
{
  int ix;
  float btw;

  btw=p_lin->btw;
  if (p_lin->groep == groep_leeg) btw=-1;
  for (ix=0; ix<btw_used; ix++) {
    if (btw_cumul[ix].btw_perc == btw) break;
  }
  if (ix==btw_used) {
    if (btw_used<CUMBTW_COUNT) {
      btw_cumul[ix].btw_perc=btw;
      btw_used++;
    }
    else disp_exit("Teveel verschillende BTW-percentages");
  }
  return ix;
}
 
void print_footer(double getal)
{
  char line[45];
  int i;
 
  _clr_text(line); for (i=0; i<40; i++) line[i]='-'; prt_nl(line);
  prt_cod(2); prt_cod(3);
  _clr_text(line); copynaam(txttxt[14],line,8);
  conv_getal(getal,line+8,12,YES,def_digits);
  line[20]=0;
  prt_nl(line); prt_cod(4);
}

void prt_titel(char *s, char *s2)
{
  char lijn[45];
  char cut_flag;
  int j;
	short jj, mm, dd;
 
  if (ZTotaalPrintingBusy) {
		prt_nl(" ");
		prt_nl(" ");
		prt_nl("****************************************");
    _clr_text(lijn);
		copynaam(s,lijn,20); prt_cod(2); prt_cod(3); lijn[20]=0; prt_nl(lijn); prt_cod(4);
    prt_nl(" ");
		if (*s2) {
		  _clr_text(lijn);
			copynaam(s2,lijn,40); prt_nlu(lijn);
		}
		_printed=YES;
	  return;
	}

  cut_flag=NO; _printed=YES;
  prt_cod(0); j=0;
  FOREVER {
    _clr_text(lijn);
    if (j==2) copynaam(s,lijn,20);
    else if (j==3) {
      jddate(lst_dag,&jj,&mm,&dd);
      if (_cumper==1) {
        int2str(dd,lijn+ 5, 2); lijn[ 7]='/';
        int2str(mm,lijn+ 8,-2); lijn[10]='/';
        int2str(jj,lijn+11,-4); lijn[20]=0;
      }
      else if (_cumper==2) {
        movmem(txttxt[15],lijn+ 4,4);
        int2str(lst_week,lijn + 9,2); lijn[11]='/';
        int2str(jj,lijn+12, 4); lijn[20]=0;
      }
      else if (_cumper==3) {
        movmem(txtmnd[lst_maand-1],lijn+6,3);
        int2str(jj,lijn+10, 4); lijn[20]=0;
      }
    }
    else if (j==4) {
      if (_vkptype>=1 && _vkptype<=2) copynaam(txttxt[59+_vkptype],lijn,20);
    }
    if (j>=2 && j<=4) {prt_cod(2); prt_cod(3); lijn[20]=0;}
    if (j==5) {copynaam(s2,lijn,40); prt_nlu(lijn);}
    else prt_nl(lijn);
    if (lijn[20]==0) prt_cod(4);
    cut_flag|=prt_cut(2+j++);
    if (j>=6 && cut_flag) break;
  }
}

// KASFUNC1

#define PEN_DELAY       4
#define REL_DEBOUNCE     40
#define DEP_DEBOUNCE     10
#define SAME_COUNT        5/* aantal identieke meting, max. 10 */
#define MAX_XDIF          2/* maximaal verschil tussen 2 metingen */
#define MAX_YDIF          1
#define MOUSE_X         640 /* 640 en 800 voor w2k*/
#define MOUSE_Y         200 /* 200  voor klassiek kassa, 600 (of 480 ?) voor w2k in full-screen */
 
#define BEEP_LEN        100

#define TIMER_CR        0x43
#define TIMER_P2        0x42
#define PPI_B           0x61
 
#define COL_RESET       0x3DB
#define COL_PENSTAT     0x3DA
#define COL_SWMASK      0x004
#define COL_TRMASK      0x002
 
#define HERC_RESET      0x3BB
#define HERC_PENSTAT    0x3BA
#define HERC_SWMASK     0x004
#define HERC_TRMASK     0x002
 
struct {
  char addr[4];
  int  port;
} mio_possible[2] = {
  "1A0", 0x1A0,
  "1E0", 0x1E0
};
int mio=0, herc_switch=0;
static int mulfunad=0x1A0;/* poort eigen Multifunction PCB */
unsigned mulfunok=NO;/* flag : 1=multifuncion exist */
char dsel_herc[8] = { (char)0xFF,(char)0xFC,(char)0xFA,(char)0xF6,(char)0xEE,(char)0xDE,(char)0xBE,(char)0x7E};
unsigned mouse_x=MOUSE_X, mouse_y=MOUSE_Y;
 
static char attr_bw     [] = {/* bw card, monochr */
   (char)0x07, (char)0x01, (char)0x0F, (char)0x09, (char)0x87, (char)0x81, (char)0x8F, (char)0x89,
   (char)0x70, (char)0x71, (char)0x78, (char)0x79, (char)0xF0, (char)0xF1, (char)0xF8, (char)0xF9};
static char attr_col    [] = {
   (char)0x0E, (char)0x0E, (char)0x0F, (char)0x0C, (char)0x8B, (char)0x8D, (char)0x8E, (char)0x8C,/* col card, colour */
   (char)0x1F, (char)0x2F, (char)0x5E, (char)0x4E, (char)0x9F, (char)0xAF, (char)0xDE, (char)0xCE};
 
static char *attr;/* pointer to selected attribute txlate table */
unsigned video, crtindex, crtdata, pen_ok=YES, mous_ok=NO;
static char key_x, key_y, col_card;
static int crtstat, last_pos, mous_h, mous_v;
static unsigned p_reset, p_penstat, mask_switch, mask_trigger;
static unsigned ss_buf[2000], entry_pos, entry_form;
static char buf_wis[160], videobuf[160];
char buf_leeg[40], buf_tekst[40], buf[1000], videosave[4000];
static int hercold;

static char keygetfl=NO;
static int keygetbuf;
int hercnum, bc_flag=NO, bc_allowed=NO, bc_no_stxetx=NO;
 
extern char config[10], larg_f, beep_fl;
extern int bc_option, pen_delay, sprook, plulink;
long sizmem(), get_hun();
extern unsigned jamin1[5];
extern int touchtst; /* om aan te duiden dat TOUCH-PANEL rechtstreeks moet nagekeken
                        worden in de mouse-driver */
int touchtyp=1; /* 0 zo gewone muisdriver */


/* --------------------------- Declaratie functies ---------------------- */

static void _dsp(char *s);
static void beep(int freq, int time);

void disp_init(void)
{
  int i;

  for (i=0; i<80; i++) {
    buf_wis[i*2]=' '; buf_wis[i*2+1]=0;
  }


  if (bc_option>=11 && bc_option<20) {
    bc_option-=10;
    bc_no_stxetx=YES;
  }

// WINDOWS NOG AAN TE PASSEN
//  if (bc_option>=1 && bc_option<99) BCSER_EN(bc_option);
  
  get_tijd();/* om jddatum in te vullen */
}
 
void get_memory(long needed)
{
  char *s;
  int i;
  long size;
 
  i=(needed/1024L)+5;
  size=0;

  s=(char *)malloc(needed);
  if (s!=NULL) {
    size=needed;
  }

  free(s);

#if DEMO_VERSION
  if (size<needed || dateget()>=datejd(DEMO_EXPIRE)) {
#else
  if (size<needed) {
#endif
    sprintf(buf,"Out of memory : %10ld (Tot.: %10ld)",i * 1024L - size,needed);
    disp_exit(buf);
  }
}

bool FindExtraDisplay()
{
  if (!WindowsNT) return 0;
	
	typedef INT (*MYPROC)(LPTSTR); 

  HINSTANCE hinstLib; 
  MYPROC FindExtraDisplay; 
 
	char buf[1000];
  // Get a handle to the DLL module.
  buf[0]=0;
  hinstLib = LoadLibrary("LargDisp.dll"); 
   // If the handle is valid, try to get the function address.
  if (hinstLib != NULL) { 
    FindExtraDisplay = (MYPROC) GetProcAddress(hinstLib, "?FindExtraDisplay@@YAHPAD@Z");
    // If the function address is valid, call the function.
    if (FindExtraDisplay != NULL) {
			(FindExtraDisplay) (buf); 
			m_strExtraDisplayName=buf;
		}
    // Free the DLL module.
    FreeLibrary(hinstLib); 
  } 

	if (m_strExtraDisplayName.GetLength()) {
		HDC hDC=CreateDC("DISPLAY",m_strExtraDisplayName, NULL, NULL);
		CDC dc;
		ExtraDisplaySize.right=GetDeviceCaps(hDC,HORZRES);
		ExtraDisplaySize.bottom=GetDeviceCaps(hDC,VERTRES);
		DeleteDC(hDC);
	}
	return 0;
}

bool DisableExtraDisplay()
{

	if (GetSystemMetrics(SM_CXSCREEN)==1024) return 0;

	typedef INT (*MYPROC)(LPTSTR); 

  HINSTANCE hinstLib; 
  MYPROC DisableExtraDisplay; 
 
	char buf[1000];
  // Get a handle to the DLL module.
  sprintf(buf,m_strExtraDisplayName);
	if (buf[0]==0) return 1;
  hinstLib = LoadLibrary("LargDisp.dll"); 
   // If the handle is valid, try to get the function address.
  if (hinstLib != NULL) { 
    DisableExtraDisplay = (MYPROC) GetProcAddress(hinstLib, "?DisableExtraDisplay@@YAHPAD@Z");
    // If the function address is valid, call the function.
    if (DisableExtraDisplay != NULL) (DisableExtraDisplay) (buf); 
    // Free the DLL module.
    FreeLibrary(hinstLib); 
  } 
	return 0;
}


int disp_exit(char *s)
{
  int ret;
 

// WINDOWS NOG AAN TE PASSEN
//  if (bc_option && bc_option<99) {
//    BCSER_DI(bc_option);
//  }
  if (*s && *s!='.') {
    ret=255;
    printf(s);
    printf("\r\n");
    printf("Press <ENTER> ...                          ");
    //while (kbchar()!=0x0D);
  }
  else if (*s=='.') ret=1;
  else ret=0;

//	if (pAffDisplay) delete pAffDisplay;  
//	if (pCustDisplay) delete pCustDisplay;

  _disp_exit(s);
	if (m_strExtraDisplayName.GetLength()) DisableExtraDisplay();
  _exit(ret);
	return ret;
}


void cursor(int x, int y)
{
   vdposp(x,y);
}

void mous_en_curs()
{
}

void mous_di_curs()
{
}

/*                        
int pen_scan(char text_fl)
{
  int r16,r17,k,key,x,y,i,kd[10],xmin,xmax,ymin,ymax,xtot,ytot;

  if (beep_fl==GOOD) beep_ok();
  else if (beep_fl==BAD) beep_bad();
  beep_fl=NO; bc_flag=NO;
  FOREVER {
   retry:
    if (text_fl<2) {
      wait_released();
      wait_depressed();
      if (bc_flag) return -2;
    }
    else {
      if (!mous_ok) {
        if (!(jinp(p_penstat) & mask_trigger)) {
          key=-1; break;
        }
      }
      else {
        if (!(mous_bu_stat(&x,&y) & 1)) {key=-1; break;}
      }
    }
    if (!mous_ok) {
      i=0;
     again:;
      while (i<SAME_COUNT) {
        joutp(p_reset,0);
        while (!(jinp(p_penstat) & mask_trigger)) {   / * wait till triggered * /
          if (jinp(p_penstat) & mask_switch) goto retry;
        }
        joutp(crtindex,16); r16=(char)jinp(crtdata);
        joutp(crtindex,17); r17=(char)jinp(crtdata);
        kd[i]=r16*256+r17-pen_delay;
        i++;
        if (jinp(p_penstat) & mask_switch) goto retry;
      }
      xmin=10000; xmax=-1; ymin=10000; ymax=-1; xtot=0; ytot=0;
      for (i=0; i<SAME_COUNT; i++) {
        x=kd[i]%80; y=kd[i]/80;
        xtot+=x; ytot+=y;
        if (xmin>x) xmin=x;
        if (xmax<x) xmax=x;
        if (ymin>y) ymin=y;
        if (ymax<y) ymax=y;
      }
      if (xmax-xmin > MAX_XDIF || ymax-ymin > MAX_YDIF) {
        for (i=0; i<SAME_COUNT-1; i++) {
          kd[i]=kd[i+1];
        }
        goto again;
      }
      else {
        x=(xtot+SAME_COUNT/2)/SAME_COUNT;
        y=(ytot+SAME_COUNT/2)/SAME_COUNT;
        k=y*80+x;
      }
    }
    else {
      x=(mous_h*80)/mouse_x;
      y=(mous_v*25)/mouse_y;
      
      if (x>79) x=79;
      if (y>24) y=24;
      k=x+y*80;
    }
    if (k>=0 && k<2000) {
      last_pos=k;
      if ((key=keymap[k])!=-1) break;
      if (text_fl) break;
    }
    beep_bad();
  }
  if (key>=0) beep_tick();
  return key;
}
 
*/

/* void wait_released(void)
{
  int count, x, y;
 
  if (pen_ok) {
    count=REL_DEBOUNCE;
    while (count>0) {
      if (jinp(p_penstat) & mask_switch) count--;
      else count=REL_DEBOUNCE;
    }
  }
  else if (mous_ok) {
    while (mous_bu_stat(&x,&y) & 1);
  }
}
/

int pen_depressed(char bc_check)
{
//NOG OP TE LOSSEN WINDOWS
  return pen_down();
}


  int state, scancode;
 
  if (!pen_ok) {
    if (bc_check && bc_option) {
      if (bc_option%100==99) {
        FOREVER {
          scancode=kbcharnw(); //_bios_keybrd(_KEYBRD_READY);
          if (!scancode) break;
          if (scancode==0x3002) {bc_flag=YES; return YES;}
          keyget();
        }
      }
//      else if (BCSER_TS()) {bc_flag=YES; return YES;}
    }
    if (mous_ok) {
      return (mous_bu_stat(&mous_h,&mous_v) & 1);
    }
    else return NO;
  }
  state = !(jinp(p_penstat) & mask_switch);
  if (!state && bc_check && bc_option) {
    if (bc_option%100==99) {
      FOREVER {
        scancode=kbcharnw(); //_bios_keybrd(_KEYBRD_READY);
        if (!scancode) break;
        if (scancode==0x3002) {state=YES; bc_flag=YES; break;}
        keyget();
      }
    }
//    else if (BCSER_TS()) {state=YES; bc_flag=YES;}
  }
  return state;
}
 
void wait_depressed(void)
{
  int count, scancode;
                
  if (pen_ok) {
    count=DEP_DEBOUNCE;
    if (ss_enable) start_saver();
   depressed:;
    while (count>0) {
      if (!(jinp(p_penstat) & mask_switch)) {count--;}
      else {
        while (bc_allowed) {
          if (bc_allowed%100==99) {
            scancode=kbcharnw(); //_bios_keybrd(_KEYBRD_READY);
            if (!scancode) break;
            if (scancode==0x3002) {bc_flag=YES; goto end;}
            keyget();
          }
          else {
//            if (BCSER_TS()) {bc_flag=YES; goto end;}
            break;
          }
        }
        count=DEP_DEBOUNCE;
     }
    }
  }
  else if (mous_ok) {
    if (!touchtyp) mous_en_curs(); 
    if (ss_enable) start_saver();
    FOREVER {
      if (mous_bu_stat(&mous_h,&mous_v) & 1) {mous_di_curs(); break;}
      while (bc_allowed) {
        if (bc_allowed%100==99) {
          scancode=kbcharnw(); //_bios_keybrd(_KEYBRD_READY);
          if (!scancode) break;
          if (scancode==0x3002) {bc_flag=YES; goto end;}
          keyget();
        }
        else {
//          if (BCSER_TS()) {bc_flag=YES; goto end;}
          break;
        }
      }
    }
  }
 end:;
}
*/
 
void disp_num(int x_pos, int y_pos, double *pd, int dig, int dig_aft, int disp_punt)
{
  char buf[25];
                                        
  sprintf(buf,"%20.2f",*pd);
  disp_vid(x_pos,y_pos,buf,0);
}
 
void scr_clr(void)
{
  cls();
}

void int2str(int d, char *s, int len)
{
  int j;
  char buf[10], l_zero, leader;
 
  l_zero=NO;
  if (len<0) {len=-len; l_zero=YES;}
  if (d==0) {
    buf[0]='0';
    j=1;
  }
  else {
    j=stci_d(buf,d,sizeof(buf));
  }
  movmem(buf,s+len-j,j);
  if (l_zero) leader='0'; else leader=' ';
  for (j=len-j; j>0; j--) *(s+j-1)=leader;
}

double round_it(double getal, double round)
{
  long l;
                                
  if (round==0) return getal;
  if (getal<0.) getal-=(round/2.);
  else getal+=(round/2.);
  getal/=round;
  l=(long)getal;
  return (double) (l*round);
}

void copynaam(char *s, char *d, int len)
{
  while (len-->0) if (!*s) break; else *d++=*s++;
}

void zeroes(char *s, unsigned len)
{
  while (len--) *s++=0;
}

int compare(char *s1, char *s2, int len)
{
  while (len-->0) {
    if (*s1<*s2) return -1;
    else if (*s1>*s2) return 1;
    s1++; s2++;
  }
  return 0;
}

// KASFUNC2

// KASFUNC3.cpp

static unsigned com_port;
static char banner[64];
static int bannerlen=-1;

char tijd[30], prt_fil=NO; //PRT_FIL; 
int epson_fl=NO;
int ir300_fl=NO;
HANDLE PrtRef=INVALID_HANDLE_VALUE;
HANDLE CustRef=INVALID_HANDLE_VALUE;
int PrtNr=0;                      // 0 -> ticket, 1 -> Brede, 2 -> Controle, 3 -> CustomerDisplay 
unsigned jddatum;
int sprook=NO, sprofnd=NO;
 
extern char *txtdag[], *txtmnd[], ladetype, TicketShare[], LaserShare[];

extern char reclame[6][11][22];
extern int comnr_lade, mio, bc_option; 
extern short int prx_sys[VRK_COUNT], vrk_lade[VRK_COUNT], leeg_sys[VRK_COUNT];
long sizmem(), get_hun();
extern unsigned mulfunok;
extern int prtnum, prtbnum;
unsigned jamin1[5];

 
char dsel_lade[8] = { (char)0xFE,(char)0xFD,(char)0xFB,(char)0xF7,(char)0xEF,(char)0xDF,(char)0xBF,(char)0x7F};

flag sproinit=NO;

struct s_Prt {
  int type;
  char UNC[MAX_PATH];
  int baudrate;
  char suspended;
} Prt[4];           // 0 -> ticket, 1 -> Brede, 2 -> Controle, 3 -> CustomerDisplay 
  
struct s_PrtDrv {
  int cut_count;
  char cod[9][40];
  unsigned char spec[128];
} PrtDrv[6] = {
  {
    6,                  // 0 -> CBM-720
    {
      "\x11",
      "\x1B\x50\xFF",
      "\x13",
      "\x0E",
      "\x0F",
      "\x1B\x2D\x01",
      "\x1B\x2D\xFF",
      " \x0D\x0A",
    },
    { 
      0x43,0xCC,0xBE,0xDF,0xDB,0xDD,0x61,0x63,0xC1,0xBD,0xBF,0xD2,0xC6,0xC4,0xAE,0xBC,
      0x45,0x20,0x20,0xCB,0xC7,0xC9,0xD0,0xCE,0x20,0xC7,0xCC,0x20,0x20,0x20,0x20,0x20,
      0xDC,0xC3,0xC8,0xCD,0xD4,0xD3,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
      0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
      0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
      0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
      0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
      0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB5,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    }
  },
  {
    6,                  // 1 -> EPSON TM-88
    {
      "\x1B\x40\x1B\x74\x13",
      "\x1D\x56\xFF",
      "\x1B\x47\x31",
      "\x1D\x21\x10",
      "\x1D\x21\xFF",
      "\x1B\x2D\x01",
      "\x1B\x2D\xFF",
      " \x0D\x0A",
      "\x1B\x47\x30",
    },
    {  
       160,133,131,132,135,130,138,136,137,161,141,140,139,162,149,147, /* 8X */
       148,163,151,150,129,154,248, 21,254, 27, 26, 24, 25,126,126,213,/* 9X */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* AX */
       178,186,205,200,186,186,201,204,205,188,205,202,187,185,203,206, /* BX */
       178,179,196,192,179,179,218,195,196,217,196,193,191,180,194,197,/* CX */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* DX */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* EX */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,/* FX */  
    }
  },
  {
    0,                  // 2 -> HP LaserJet
    {
      "\x1B\x45\x1B\x39\x1B&l6D\x1B&l0L\x1B&s1C\x1B(10U\x0F\x1B&l0E",
      "\x1B(s3B",                                                /* boldface on */
      "\x1B(s0B",                                                        /* off */
      "\x1B&dD",                                                /* underline on */
      "\x1B&d@",                                                         /* off */
      "",                                                       /* elongated on */
      "",                                                                /* off */
      "\x0D\x0A",
    },
    {  
       160,133,131,132,135,130,138,136,137,161,141,140,139,162,149,147, /* 8X */
       148,163,151,150,129,154,248, 21,254, 27, 26, 24, 25,126,126,0x45,// 9X   E ipv EURO !
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* AX */
       178,186,205,200,186,186,201,204,205,188,205,202,187,185,203,206, /* BX */
       178,179,196,192,179,179,218,195,196,217,196,193,191,180,194,197,/* CX */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* DX */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* EX */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,/* FX */  
    }
  },
  {
    0,                  // 3 -> CUSTOMER DISPLAY
    {
      "\x1B\x3D\x02\x1B\x40\x1B\x74\x13\x1F\x43\xFF", // select DispDevice, Reset, Select Char Set, hide cursor
      "\x1D\x56\xFF",
      "\x1B\x47\x31",
      "\x1D\x21\x10",
      "\x1D\x21\xFF",
      "\x1B\x2D\x01",
      "\x1B\x2D\xFF",
      " \x0D\x0A",
      "\x1B\x47\x30",
    },
    {  
       160,133,131,132,135,130,138,136,137,161,141,140,139,162,149,147, /* 8X */
       148,163,151,150,129,154,248, 21,254, 27, 26, 24, 25,126,126,213,/* 9X */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* AX */
       178,186,205,200,186,186,201,204,205,188,205,202,187,185,203,206, /* BX */
       178,179,196,192,179,179,218,195,196,217,196,193,191,180,194,197,/* CX */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* DX */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* EX */
       126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,/* FX */  
    }
  },
  {
	0,                  // 4 -> HP LaserJet (wordt niet gebruikt)
	{
	  "\x1B\x45\x1B\x39\x1B&l6D\x1B&l0L\x1B&s1C\x1B(10U\x0F\x1B&l0E",
	  "\x1B(s3B",                                                /* boldface on */
	  "\x1B(s0B",                                                        /* off */
	  "\x1B&dD",                                                /* underline on */
	  "\x1B&d@",                                                         /* off */
	  "",                                                       /* elongated on */
	  "",                                                                /* off */
	  "\x0D\x0A",
	},
	{
	   160,133,131,132,135,130,138,136,137,161,141,140,139,162,149,147, /* 8X */
	   148,163,151,150,129,154,248, 21,254, 27, 26, 24, 25,126,126,0x45,// 9X   E ipv EURO !
	   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* AX */
	   178,186,205,200,186,186,201,204,205,188,205,202,187,185,203,206, /* BX */
	   178,179,196,192,179,179,218,195,196,217,196,193,191,180,194,197,/* CX */
	   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* DX */
	   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* EX */
	   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,/* FX */
	}
  },
 {
	0,                  // 5 -> PDF
	{
	  "",
	  "\xE1",                                                /* boldface on */
	  "\xE2",                                                        /* off */
	  "\xE3",                                                /* underline on */
	  "\xE4",                                                         /* off */
	  "",                                                       /* elongated on */
	  "",                                                                /* off */
	  "\x0D\x0A",
	},
	{
	   160,133,131,132,135,130,138,136,137,161,141,140,139,162,149,147, /* 8X */
	   148,163,151,150,129,154,248, 21,254, 27, 26, 24, 25,126,126,0x45,// 9X   E ipv EURO !
	   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* AX */
	   178,186,205,200,186,186,201,204,205,188,205,202,187,185,203,206, /* BX */
	   178,179,196,192,179,179,218,195,196,217,196,193,191,180,194,197,/* CX */
	   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* DX */
	   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* EX */
	   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,/* FX */
	}
 }
};


/* --------------------------- Declaratie functies ---------------------- */

///////////////

void joutp(int port, int data)
{
  //_outp(port,data);
}

int jinp(int port)
{
  return 0; //_inp(port);
}


int jamint(void)
{
	return 1;
}

void lade_init(void)
{
}

void o_lade(int byte)
{
  if (byte & 1) prt_lin("\x1Bp0\x19\xFA");
  if (byte & 2) prt_lin("\x1Bp1\x19\xFA");
}


void get_tijd(void)
{
  int j,uur,min;
	short jj, mm, dd;
	SYSTEMTIME st;
 
  GetLocalTime(&st);
  for (j=0; j<sizeof(tijd); j++) tijd[j]=' ';
  jddatum=dateget(); jddate(jddatum,&jj,&mm,&dd);
  uur = st.wHour;
	min = st.wMinute;
  j=(jddatum+3)%7; movmem(txtdag[j],&tijd[0],2);
  int2str(dd,&tijd[3],2);
  movmem(txtmnd[mm-1],&tijd[6],3);
  int2str(jj,&tijd[10],4);
  int2str(uur,&tijd[15],2); tijd[17]=':';
  int2str(min,&tijd[18],-2); tijd[20]=0;
}

long get_hun(void)
{
  int _uur, _min, _sec, _hun;
	SYSTEMTIME st;
 
  GetLocalTime(&st);
  _uur=st.wHour;
	_min=st.wMinute;
	_sec=st.wSecond;
	_hun=st.wMilliseconds/10;
  return (long) ((((_uur*60L)+_min)*60L)+_sec)*100L+_hun;
}

void wait_hun(int hundred)
{
  long now, start, timeout, offset;

  start=get_hun();
  timeout = start+hundred;
  offset = 24L*60L*60L*100L;
  FOREVER {
    now = get_hun();
    if (now>=start) {
      if (now>timeout) break;
    }
    else {
      if (now>timeout-offset) break;
    }
  }  
}
 
void prt_close(void)
{
	DWORD EvtMask=EV_TXEMPTY;

  if (PrtRef!=INVALID_HANDLE_VALUE) {
		if (Prt[PrtNr].baudrate==0) { // networkprinter ...
  		CloseHandle(PrtRef);
      PrtRef=INVALID_HANDLE_VALUE;
		}
  }
  Prt[PrtNr].suspended=PrtSuspended;
  if (PrtSuspended==YES) PrtSuspended=NO; // ev. printer opnieuw checken bij volgende print
}

void prt_init(void)
{
  int i, _prtnum;
  
  for (i=0; i<4; i++) Prt[i].suspended=false;
  Prt[0].type=TM88; Prt[0].baudrate=0;
  Prt[1].type=2; Prt[1].baudrate=0;
  Prt[2].type=0; Prt[2].baudrate=0;    // default voor WINTOUCH
	sprintf(Prt[2].UNC,"LPT1");
  Prt[3].type=VFD; Prt[3].baudrate=9600; 
  if (SoortKassa == 6) sprintf(Prt[3].UNC, "Com4"); // nieuwe panelpos 2023
  else if(SoortKassa==5) sprintf(Prt[3].UNC,"Com1");
  else if(SoortKassa==3 || SoortKassa==4) sprintf(Prt[3].UNC,"Com6"); 
  else sprintf(Prt[3].UNC,"Com4");



  for (i=0; i<2; i++) {  
    Prt[i].UNC[0]=0;
    if (i==0) _prtnum=prtnum;
    if (i==1) _prtnum=prtbnum;
    prt_close();

	if (i == 0 && _prtnum == 5) {// ticket in pdf, doen alsof netwerkprinter
	  PrintControl2PDF = YES; NoPrtCut = YES; DefNoPrtCut = YES;
	  _prtnum = 51;
	}
    if (_prtnum>=30 && _prtnum<=31) {
      Prt[i].type=TM88;
      _prtnum-=30;
    }
    if (_prtnum>=0 && _prtnum<=1) {
      sprintf(Prt[i].UNC,"LPT%1d:",_prtnum+1);
      if (i==0) {
			  Prt[i].type=CBM720;
				if (prtnum>=30 && prtnum<=31) Prt[i].type=TM88;
			}
      if (i==1) Prt[i].type=TM88;
    }
    if (_prtnum>=3 && _prtnum<=4) {
      Prt[i].type=TM88;
      sprintf(Prt[i].UNC,"Com3");
      Prt[i].baudrate=9600; 
			if (i==0) {
  			ir300_fl=YES;
				sprintf(Prt[3].UNC,"%s",Prt[0].UNC);
			}
    }
    if (_prtnum>=21 && _prtnum<24) {
      Prt[i].baudrate=2400;
      _prtnum-=10;
    }
    if (_prtnum>=11 && _prtnum<=14) {
      if (Prt[i].baudrate==0) Prt[i].baudrate=9600;     
      sprintf(Prt[i].UNC,"Com3");
      if (_prtnum==11) {
				sprintf(Prt[i].UNC,"Com1:");
		
				CString KeyName="";
				HKEY hk;
				long ret;
				char buf[1000];
				bool TicketPrinterDriverOnCom1=true;
				DWORD dummy, type, size;

        KeyName.Format(_T("SYSTEM\\CurrentControlSet\\Control\\Print\\Printers\\ticketprinter\\DsSpooler"));
        if (!RegCreateKeyEx(HKEY_LOCAL_MACHINE, KeyName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk,&dummy)) { 
				  size=sizeof(buf)-1;
					ret=RegQueryValueEx(hk,_T("UNCName"),0,&type,(LPBYTE)&buf,&size);
					if (ret==ERROR_SUCCESS) {
						buf[size]=0;
						if (strcmpi(buf+13,"\\ticketprinter")) TicketPrinterDriverOnCom1=false; // wintouch-01, 02, ...
						size=sizeof(buf)-1;
						ret=RegQueryValueEx(hk,_T("PortName"),0,&type,(LPBYTE)&buf,&size);
						if (ret==ERROR_SUCCESS) {
							buf[size]=0;
							if (strcmpi(buf,"Com1:")) TicketPrinterDriverOnCom1=false;
						}
						else TicketPrinterDriverOnCom1=false;
					}
					else TicketPrinterDriverOnCom1=false;
					RegCloseKey(hk);
				  
					if (TicketPrinterDriverOnCom1) Prt[i].baudrate=0; // PrinterSpooler Intercepts output on COM1:
				}
			}
      if (_prtnum==12) sprintf(Prt[i].UNC,"Com2");
      if (_prtnum==13) sprintf(Prt[i].UNC,"Com3");
      if (_prtnum==14) sprintf(Prt[i].UNC,"Com4");
      epson_fl=YES;
    }
    if (_prtnum>=51 && _prtnum<=59) {
      Prt[i].type=TM88;
      sprintf(Prt[i].UNC,TicketShare);
      if (_prtnum==52) sprintf(Prt[i].UNC,LaserShare);
    }
  }
}

void cust_open(void) {
 
	bool SerialPortFlag=false;

	if (Prt[3].baudrate) SerialPortFlag=true;

	CustRef=CreateFile(Prt[3].UNC,GENERIC_WRITE,
					0, // exclusive access
					NULL, // no security
					CREATE_ALWAYS,
					0, // no overlapped I/O
					NULL); // null template 

  if (SerialPortFlag) {
    COMMTIMEOUTS commTimeout;
    if(GetCommTimeouts(CustRef, &commTimeout)) {  
      commTimeout.WriteTotalTimeoutMultiplier=0;
      commTimeout.WriteTotalTimeoutConstant =1000; // 1 seconden time-out 
      SetCommTimeouts(CustRef, &commTimeout);
    }
    DCB m_dcb;
    SetupComm(CustRef, 128, 1024); // set buffer size, zou niet helpen voor output buffer
  	GetCommState(CustRef, &m_dcb);

   	m_dcb.ByteSize = 8;
  	m_dcb.Parity = NOPARITY;
 		m_dcb.StopBits = ONESTOPBIT;
 		m_dcb.fAbortOnError = FALSE;
    m_dcb.fOutxDsrFlow=FALSE;								// was voor 03/10/07 TRUE
    m_dcb.fOutxCtsFlow=FALSE;								// was voor 03/10/07 TRUE
  	m_dcb.fDtrControl=DTR_CONTROL_ENABLE;
		m_dcb.fRtsControl=RTS_CONTROL_ENABLE;		// stond er niet in voor 03/10/07 
    m_dcb.fDsrSensitivity=FALSE;						// stond er niet in voor 03/10/07
    m_dcb.BaudRate = Prt[3].baudrate;
    SetCommState(CustRef, &m_dcb);
  }
  if (CustRef==INVALID_HANDLE_VALUE) CustSuspended=YES;
}

void prt_open(void) {
 
	bool SerialPortFlag=false;

	if (Prt[PrtNr].baudrate) SerialPortFlag=true;

#if defined _xDEBUG
  ir300com="tst"+ir300com;
	PrtRef=CreateFile(ir300com,GENERIC_WRITE,
					0, // exclusive access
					NULL, // no security
					CREATE_ALWAYS, 
					0, // no overlapped I/O
					NULL); // null template 
#else 
  PrtSuspended=NO;
	PrtRef=CreateFile(Prt[PrtNr].UNC,GENERIC_WRITE,
					0, // exclusive access
					NULL, // no security
					CREATE_ALWAYS, 
					0, // no overlapped I/O
					NULL); // null template 

	if (SerialPortFlag) {
    COMMTIMEOUTS commTimeout;
    if(GetCommTimeouts(PrtRef, &commTimeout)) {  
      commTimeout.WriteTotalTimeoutConstant=15000; // 15 seconden time-out, was 5 seconden
      SetCommTimeouts(PrtRef, &commTimeout);
    }
    DCB m_dcb;
    SetupComm(PrtRef, 128, 1024); // set buffer size, zou niet helpen voor output buffer
  	GetCommState(PrtRef, &m_dcb);
//		CFile f;
//		f.Open("marcser.inf",CFile::modeWrite|CFile::modeCreate,NULL);
//		f.Write(&m_dcb,sizeof(m_dcb));
//		f.Close();
   	m_dcb.ByteSize = 8;
  	m_dcb.Parity = NOPARITY;
 		m_dcb.StopBits = ONESTOPBIT;
 		m_dcb.fAbortOnError = FALSE;
		m_dcb.fOutX=TRUE; // software FlowContol voor alle zekerheid
    m_dcb.fOutxDsrFlow=TRUE;
    m_dcb.fOutxCtsFlow=TRUE;
		m_dcb.fRtsControl=RTS_CONTROL_ENABLE;
		if (ir300_fl) {
		  m_dcb.fOutxCtsFlow=FALSE; // die lijn wordt op IR300 blijkbaar niet gebruikt en blokkeert de output
		}
  	m_dcb.BaudRate = Prt[PrtNr].baudrate;
    SetCommState(PrtRef, &m_dcb);
  }
  if (PrtRef==INVALID_HANDLE_VALUE) PrtSuspended=YES;

#endif
}

void prt_ean(char *s)
{
  if (Prt[PrtNr].type==TM88) {
    prt_lin("\x1Dh\x30");
    prt_lin("\x1Dk\x02"); prt_lin(s);
    prt_lin("\xFF");
    prt_nl("");
  }
}

void cust_disp(char *s)                //      cust_lin("\x1B@\x1B\x13\x0C");
{
	bool TruPrinter=false;
	char dbuf_[100];

  if (strcmpi(Prt[3].UNC,Prt[0].UNC)==0) TruPrinter=true;

  if (TruPrinter) {
		prt_lin("\x1B=\x02\x1F\x01");
    prt_cod(0);
    prt_lin(s);
    prt_lin("\x1B=\x01");
	}
	else {
		if(SoortKassa==4){
  		zeroes(dbuf_,sizeof(dbuf_));
	  	bcopy0("  ",dbuf_,2);	bcopy0(s,&dbuf_[2],20); bcopy0("  ",&dbuf_[22],2);
		  bcopy0("  ",&dbuf_[24],2);	bcopy0(s+20,&dbuf_[26],20);
		  cust_prt_cod(0); cust_prt_lin(dbuf_);
		}
		else {cust_prt_cod(0); cust_prt_lin(s);}
	}
}

void cust_init(void)
{
  char b,buf[100];
  int j;
  
  for (j=0; j<20; j++) {
    b=reclame[0][0][j];
    if (!b) break;
    else buf[j]=b;
  }
  for (; j<20; j++) buf[j]=' ';
  for (j=0; j<20; j++) {
    b=reclame[0][1][j];
    if (!b) break;
    else buf[j+20]=b;
  }
  for (; j<20; j++) buf[j+20]=' ';
  buf[40]=0;
  cust_disp(buf);
}

void cust_prt_char(char val)
{
  BOOL ret;
  DWORD iBytesWritten;

  if (CustRef==INVALID_HANDLE_VALUE) cust_open();

  if (CustSuspended) return;
  ret=WriteFile(CustRef, &val,1,&iBytesWritten,NULL);
  if (iBytesWritten!=1) {
    CustSuspended=YES;
    return;
  }
}

void prt_char(char val)
{
  BOOL ret;
  DWORD iBytesWritten;
  unsigned char *s;

#if CONTROL2PDF
  if(PrintControl2PDF){  
		s=(unsigned char *)&val;
		//if (PrtNr==1) JMU_prt_char(' '); // PCL factuur (1 naar rechts !)
	//	Prt[PrtNr].type=2;
		if(TotSpoolBytes<CTRLPDFSIZE-10){
			if (*s==0xFF) *JMU_s++=0;
			else {
				if (*s<128) *JMU_s++=*s;
				else *JMU_s++=PrtDrv[2 /* Prt[2].type */].spec[*s++-128];
			}

		}
		TotSpoolBytes++;
	}
	else{
		if (PrtRef==INVALID_HANDLE_VALUE) prt_open();
		if (PrtSuspended) return;
		ret=WriteFile(PrtRef, &val,1,&iBytesWritten,NULL);
		if (iBytesWritten!=1) {
			PrtSuspended=YES;
			return;
		}
	}
#else
  if (PrtRef==INVALID_HANDLE_VALUE) prt_open();

  if (PrtSuspended) return;
  ret=WriteFile(PrtRef, &val,1,&iBytesWritten,NULL);
  if (iBytesWritten!=1) {
    PrtSuspended=YES;
    return;
  }
#endif
}

void cust_prt_cod(int nr)
{
  cust_prt_lin(PrtDrv[Prt[3].type].cod[nr]);
}

void prt_cod(int nr)
{
#if CONTROL2PDF
  if (PrintControl2PDF) {
	if (nr == 1) {
	  if (TotSpoolBytes > 140) prt_nl("\x0C");
	}
//	else prt_lin(PrtDrv[Prt[PrtNr].type].cod[nr]); //++++
  }
  else {
	if (NoPrtCut == NO || nr!=1) prt_lin(PrtDrv[Prt[PrtNr].type].cod[nr]);
  }
#else
  if (NoPrtCut == NO || nr!=1) prt_lin(PrtDrv[Prt[PrtNr].type].cod[nr]);
#endif
}

void cust_prt_lin(char *sc)
{
  unsigned char *s;
	s=(unsigned char *)sc;
  while (*s) {
    if (*s==0xFF) {
      cust_prt_char(0); s++;
    }
    else {
      if (*s<128) cust_prt_char(*s++);  // || epson_flag   weggedaan voor conversie naar 
      else cust_prt_char(PrtDrv[Prt[3].type].spec[*s++-128]);
    }
  }
}

void prt_lin(char *sc)
{
  unsigned char *s;
	s=(unsigned char *)sc;
  while (*s) {
    if (*s==0xFF) {
      prt_char(0); s++;
    }
    else {
      if (*s<128) prt_char(*s++);  // || epson_flag   weggedaan voor conversie naar 
      else prt_char(PrtDrv[Prt[PrtNr].type].spec[*s++-128]);
    }
  }
}

void prt_nl(char *sc)
{
  unsigned char *s;
	s=(unsigned char *)sc;
  if (prtnum==0xFFFF) goto end;
  if (PrtNr==1) prt_char(' '); // PCL factuur (1 naar rechts !)
  while (*s) {
    if (*s==0xFF) {
      prt_char(0); s++;
    }
    else {
      if (*s<128) prt_char(*s++);
      else prt_char(PrtDrv[Prt[PrtNr].type].spec[*s++-128]);
    }
  }
  prt_char(0x0D);
  prt_char(0x0A);
  /*
  prt_cod(8);  zou niet meer nodig zijn.
                        Anders moet het verhuisd worden naar 9 of zo,
                        want op 8 zit er bij de IR-300 een Emphased code
                         in de kassys.dat die echter niet gebruikt ! */
  end:;
}

void prt_nlu(char *sc)
{
  char prev;
 
  unsigned char *s;
	s=(unsigned char *)sc;
  if (prtnum==0xFFFF) goto end;
  prev=' ';
  while (*s) {
    if (prev==' ' && *s>' ') prt_cod(5);
    else if (prev>' ' && *s==' ') prt_cod(6);
    if (*s<128) prt_char(*s);
    else prt_char(PrtDrv[Prt[PrtNr].type].spec[*s-128]);
    prev=*s++;
  }
  if (prev>' ') prt_cod(6);
  prt_char(0x0D);
  prt_char(0x0A);
  end:;
}
 

int bcopy0(char *ps_,char *pd_,int len_)
{
  int k;
 
  for(k=0;k<len_;k++){
    if(*ps_!=0) *pd_++=*ps_++; 
    else break;
  }
  if(k<len_) *pd_++='\0';

  return k;
}

// KASLOG.CPP

// Volgende 2 structs zitten ook in DRK0290.CPP

struct s_header{
  char versie[32];
  long lade_pos;
  short lade_aantal;
  short lade_len;
  long dag_pos;
  short dag_len;
  short dag_aantal;
  short dag_used;
  long rec_pos;
  long rec_len;
  long rec_aantal;
  long rec_used;
  short ticketnr;
	long LastZTotaalPrintedRecords;
	long LastZTotaalPrintedSeqNr;
} header;
static char versie[] = "KASLOG.DAT   Ver. 1.00\x1A";

struct {
  char valuta[3];
  long open_wissel;
  long open_bet;
  double bedrag[20];
} lade;

/*
struct {
  unsigned short datum;
  long first_rec;
} dag;
*/
 
extern char *txtbet[], *txtfin[];
extern char lade_valuta[][3], def_valuta[4], tijd[],TotaalOp5CentAfronden, PromoNotOnHorecaPrice;
extern short int prx_sys[VRK_COUNT], vrk_lade[VRK_COUNT], leeg_sys[VRK_COUNT];
extern int lade_aantal, vrk_ix, def_digits,fl_KasCtrl, EigenPrijsOpStuksAllowed;
extern unsigned kaslogfl;
extern unsigned jddatum;
extern long rec_aantal, dag_aantal;
extern int tf_dagres;
extern int HoursOpenAfterMidnight; 
extern double BedragTotaalafronding;
 


char *getml();
long log_getrec();
 

/* --------------------------- Declaratie functies ---------------------- */

static int  get_kas(int val_ix);
static void header_init(void);
static int  leeg_log(int line, char *logname);
static void put_kas(int val_ix);
static int _read_process();
static int  valid(long rec_ix);

/////////////////

void UpdateZSeqNrFile()
{
  int SeqRef;
  
	SeqRef=dcreat("kasseqnr.dat",CREAMODE);
  dwrite(SeqRef,(char *)&header.LastZTotaalPrintedSeqNr,sizeof(header.LastZTotaalPrintedSeqNr));
	dwrite(SeqRef,(char *)&header.ticketnr,sizeof(header.ticketnr));
	dclose(SeqRef);
}

static char logname[20];

void log_open(int line,unsigned date_)
{
  int status;
	short jj, mm, dd;
  unsigned jddatum;
 
  if(line>=0) disp_vid(0,line,"Opening KASLOG.DAT ...",0);
  movmem("kaslog.dat",logname,11);
  if (kaslogfl&1) {
    movmem("klyymmdd.dat",logname,13);
    if(date_==0) jddatum=dateget(); else jddatum=date_; jddate(jddatum,&jj,&mm,&dd);
    int2str(jj%100,&logname[2],-2);
    int2str(mm,&logname[4],-2);
    int2str(dd,&logname[6],-2);
  }  
  else if (kaslogfl&2) {
    movmem("klyyyymm.dat",logname,13);
    if(date_==0) jddatum=dateget(); else jddatum=date_; jddate(jddatum,&jj,&mm,&dd);
    int2str(jj,&logname[2],-4);
    int2str(mm,&logname[6],-2);
  }  
  logref=dopen(logname,RDWRMODE);
  if (logref<0){
		if(line<0) goto endsr; // openen voor controleband, enkel lezen, MOET bestaan, dus niet aanmaken
		else logref=leeg_log(line,logname);
	}
 retry:;
  status=dread(logref,(char *)&header,sizeof(header));
  if (status >= 0 && status<sizeof(header)) {
    log_close();
    logref=leeg_log(line,logname);
    goto retry;
  }
  if (memcmp(versie,header.versie,20)) disp_exit("KASLOG.DAT file not valid !");
  log_getdag(-1);
  jdlast=dag.datum;
	LastZTotaalPrintedRecords=header.LastZTotaalPrintedRecords;
	LastZTotaalPrintedSeqNr=header.LastZTotaalPrintedSeqNr;
	UpdateZSeqNrFile();
	if(fl_KasCtrl){
		LogCtrlRef=dopen("KasCtrl.dat",RDWRMODE);
		if (LogCtrlRef<0) LogCtrlRef=dcreat("KasCtrl.dat",CREAMODE);
  	dclose(LogCtrlRef);			
	}			
	endsr:;
}

void log_close(void)
{
  if (logref>=0) dclose(logref);
}

void log_copy(char file[])
{
  int bref, size;
  long loglen, len;
 
  bref=dopen(file,RDWRMODE);
  if (bref<0) bref=dcreat(file,CREAMODE);
  if (bref>=0) {
    loglen=dseek(logref,0L,2);
    dseek(logref,0L,0);
    len=sizeof(struct s_verkopen);
    if (len<32000) size=len; else size=32000;
    while (loglen>0) {
      len=loglen;
      if (len>size) len=size;
      dread(logref,(char *)p_vrk,(int)len);
      dwrite(bref,(char *)p_vrk,(int)len);
      loglen-=len;
    }
    dwrite(bref,(char *)p_vrk,0);
    dclose(bref);
    _clr_ticket();
  }
}

void prtlstnr(int _recix)
{
  struct s_lijn *p_save, w_lijn;

  p_save=p_lin;
  p_lin=&w_lijn;
  prt_nl("Last ticket :");
  dseek(logref,header.rec_pos+(_recix-2)*header.rec_len,0); 
  if (_read_process()!=2) {
    prt_nl("----");
  }
  p_lin=p_save;
}
 
void log_add(char incnrflag)
{
  char bits;
  long pos;
  int j, used, aantal, i, val_ix, val_old;
  short int groep;
  struct s_lijn templin;
 
	logheadcheck(1);
	get_kas(0); val_old=0;/* voor standaard BEF */
  used=p_vrk->used; aantal=0;
  pos=header.rec_pos+header.rec_used*header.rec_len;
  dseek(logref,pos,0);
  for (j=0; j<used; j++) {
    p_lin = &p_vrk->lijn[j];
    groep=p_lin->groep; bits=p_lin->bits;
    if (groep>=9990 && groep<=9999) {/* controle in VALID */
      bits|=0x80;
      templin.bits=bits; movmem(p_vrk->lijn[j].text,templin.code,20);
      movmem(&groep,templin.code+20,sizeof(groep));
      dwrite(logref,&templin.bits,(int)header.rec_len);
      templin.bits=bits; movmem(&p_vrk->lijn[j].text[20],templin.code,20);
      i=32767; movmem(&i,templin.code+20,sizeof(groep));
      dwrite(logref,&templin.bits,(int)header.rec_len);
      aantal+=2;
    }
    else {
      dwrite(logref,&p_lin->bits,(int)header.rec_len); aantal++;
    }
  }
  for (j=0; j<used; j++) {
    p_lin = &p_vrk->lijn[j];
    groep=p_lin->groep;
    if (groep==1002 || ((groep>=1010) && (groep!=1018) && (groep<=1029))  || (groep>=1040 && groep<=1049)) {
      val_ix=(int)p_lin->btw;
      if (val_ix!=val_old) {
        put_kas(val_old);
        val_old=val_ix;
        get_kas(val_ix);
      }
      if (groep==1002) lade.bedrag[0]-=p_lin->totaal;
      else if (groep==GRP_DIVUITGAVE) lade.bedrag[groep-1010]-=p_lin->totaal;
      else lade.bedrag[groep-1010]+=p_lin->totaal;
    }
  }
  put_kas(val_old);
  header.rec_used+=aantal;
  if (incnrflag) {
    header.ticketnr=next_ticketnr();
  }
	logheadcheck(2);
  logdump(0L,(char *)&header,sizeof(header));
  dflush(logref);
	dclose(logref);
	logref=dopen(logname,RDWRMODE);
	if (logref<0) {
		CString cstr;
		cstr.Format("Cannot reopen %s",logname);
		ConMessageBox(cstr,"Critical Error KeyConen",MB_OK);
		disp_exit(".");
	}
}

void log_ZTotaalHeaderUpdate()
{
 	header.LastZTotaalPrintedRecords=LastZTotaalPrintedRecords;
	header.LastZTotaalPrintedSeqNr=LastZTotaalPrintedSeqNr;
	logheadcheck(3);
  logdump(0L,(char *)&header,sizeof(header));
  UpdateZSeqNrFile();
}


void wis_kas(void)
{
  int val_ix;
 
  for (val_ix=0; val_ix<=VAL_COUNT; val_ix++) {
    if (!get_kas(val_ix)) break;
    zeroes((char *)&lade,sizeof(lade));
    put_kas(val_ix);
  }
}
 
void prt_kas(int dum)
{
  char line[45], *txt, digits;
  int i, val_ix;
  

  prt_nl("");
  prt_lin("       "); prt_cod(2);
  prt_lin(txttxt[22]); prt_lin(" : ");
  buf[0]='A'+vrk_ix; buf[1]=0; prt_nl(buf);
  prt_nl("");
  for (val_ix=0; val_ix<=VAL_COUNT; val_ix++) {
    if (!get_kas(val_ix)) {
		  if (val_ix==0) {
        prt_nl("Not yet available");
        prt_nl("Only after new KASLOG.DAT created");
        break;
			}
			continue;
    }
    if (lade.valuta[0]) {
      prt_nl("----------------------------------------");
      prt_cod(2); prt_cod(3);
      prt_lin("        ");
      movmem(lade.valuta,line,3); line[3]=0;
      prt_nl(line); prt_cod(4);
      for (i=0; i<40; i++) {
				if(i>=20 && i<30) continue; // blok 1030-1039 skippen 
        if (lade.bedrag[i]) {
          switch (i+1010) {
            case GRP_GELD:     txt=txtfin[ 7]; break;
            case GRP_ECHEQUE:  txt=txtfin[ 8]; break;
            case GRP_BANCONT:  txt=txtfin[ 9]; break;
            case GRP_MAALTIJD: txt=txtfin[11]; break;
            case GRP_LGTERUG:  txt=txtbet[05]; break;
            case GRP_LEVERBON: txt=txtfin[12]; break;
            case GRP_CREDIT:   txt=txtfin[10]; break;
            case GRP_MOBIEL:   txt=txtfin[23]; break;
            case GRP_TBSALDO:  txt=txtfin[19]; break;
            case GRP_DIVUITGAVE: txt=txtfin[20];break;
            case GRP_DIVONTVANG: txt=txtfin[21];break;
            case GRP_CDBON_VRK : txt=txtfin[28];break;
            case GRP_CDBON_BET : txt=txtfin[29];break;
            case GRP_VAR_BET1  : txt=txtfin[30];break;
            case GRP_VAR_BET2  : txt=txtfin[31];break;
            case GRP_VAR_BET3  : txt=txtfin[32];break;
			case GRP_EMAALTIJD: txt = txtfin[34]; break;
			case GRP_EECOCHEQUE: txt = txtfin[35]; break;
			case GRP_ECADEAUBON: txt = txtfin[36]; break;
			case GRP_ECONSUMBON: txt = txtfin[37]; break;
			case GRP_CASHAUT: txt = txtfin[38]; break;
            default: txt=""; break;
          }
          if (val_ix==0) digits=def_digits;
          else digits=valuta[val_ix-1].digits;
          _clr_text(line);
          copynaam(txt,line,20);
          conv_getal(lade.bedrag[i],line+20,20,0x05,digits);
          prt_nl(line);
        }
      }
      prt_nl("----------------------------------------");
      prt_nl("");
    }
  }
  get_tijd();
  _clr_text(line);
  movmem(tijd,line,20);
  line[20]=0;
  prt_cod(2); prt_cod(3);
  prt_nl(line); prt_cod(4);
  if(NoPrtCut==NO) prt_hoofd(YES);
  else { prt_nl(" ");	prt_nl(" "); }
  prt_close();
}

static int get_kas(int val_ix)
{
  int kas_ix;
  long lade_pos;
 
  kas_ix=val_ix+vrk_ix*(VAL_COUNT+1);/* 11 kassa-valuta's per verkoper */
  if (kas_ix<lade_aantal) {
    lade_pos=header.lade_pos+header.lade_len*kas_ix;
    dseek(logref,lade_pos,0);
    dread(logref,&lade,sizeof(lade));
    return YES;
  }
  return NO;
}

static void put_kas(int val_ix)
{
  int kas_ix;
  long lade_pos;
                                                                        
  kas_ix=val_ix+vrk_ix*(VAL_COUNT+1);/* 11 kassa-valuta's per verkoper */
  if (kas_ix<lade_aantal) {
    if (!lade.valuta[0] && lade.bedrag[0]) {
      if (val_ix==0) movmem(def_valuta,lade.valuta,3);
      else movmem(valuta[val_ix-1].naam,lade.valuta,3);
    }
    lade_pos=header.lade_pos+header.lade_len*kas_ix;
    dseek(logref,lade_pos,0);
    dwrite(logref,&lade,sizeof(lade));
    dflush(logref);
  }
}
 
int log_getdag(int nr)
{
  long int pos;

  if (header.dag_used==0) return -1;
  if (nr==-1) nr=header.dag_used-1;
  if (nr>=header.dag_used) return -1;
  pos=header.dag_pos+nr*header.dag_len;
  dseek(logref,pos,(int)0);
  dread(logref,&dag,header.dag_len);
  return nr;
}

void log_loadticket(int nr)
{
  char found;
  int t_nr,j;
  long pos,index;
 
  p_lin = &p_vrk->lijn[0]; found=NO;
  for (index=header.rec_used-1; index>=0; index--) {
    pos=header.rec_pos+index*header.rec_len;
    dseek(logref,pos,0);
    _read_process();
    if (valid(-1L)) {
      if (found && p_lin->bits&NEW_TICKET) break;
      if (p_lin->groep==GRP_TIJD) {
        if (found) {
          index+=2;
          break;
        }
        else {
          stcd_i(&p_lin->text[8],&t_nr);
          if (t_nr==nr) {
            found=YES;
          }
        }
      }
    }
  }
  if (found) {
    if (index<0) index=0;
    log_getrec(index);
    for (j=p_vrk->used-1; j>=0; j--) {
      if (p_vrk->lijn[j].groep != GRP_TIJD) adj_text(j);
    }
  }
}
 
void log_getstatist(long *p_dagused, long *p_dagtot, long *p_recused, long *p_rectot)
{
  *p_dagused=header.dag_used;
  *p_dagtot =header.dag_aantal;
  *p_recused=header.rec_used;
  *p_rectot =header.rec_aantal;
}
 
int log_getticket(void)
{
  int NightCorrection;
  long pos;
	SYSTEMTIME st;
 
	logheadcheck(4);
	GetLocalTime(&st);
  NightCorrection=0;
  if (st.wHour<=HoursOpenAfterMidnight) NightCorrection=1; // Eigenlijk moet die < zijn, maar ja. Nu 1 uur speling
  if (jdlast!=(jddatum-NightCorrection)) {
    pos=header.dag_pos + header.dag_used*header.dag_len;
    dag.datum=jddatum;
    dag.first_rec=header.rec_used;
    logdump(pos,(char *)&dag,sizeof(dag));
    jdlast=jddatum; header.dag_used++;
    if (tf_dagres) {
      header.ticketnr=0;
    }
  }
	logheadcheck(5);
  return next_ticketnr();
}
 
long log_getrec(long nr)
{
  char first, new_used, buf[50];
  unsigned processed;
  long rec_ix;
 
  if (nr==-1) return header.rec_used;
  _clr_ticket();
  dseek(logref,header.rec_pos+nr*header.rec_len,0); p_vrk->used=0;
  rec_ix=nr; first=YES; new_used=NO;
  FOREVER {
    if (p_vrk->used==LIN_COUNT) {
      sprintf(buf,"Too many at rec_ix %6ld",nr);
      prt_nl(buf);
      break;
    }
    if (rec_ix>=header.rec_used) break;
    p_lin = &p_vrk->lijn[p_vrk->used];
    processed=_read_process();
    rec_ix+=processed;
    if (first && p_lin->bits & NEW_TICKET) new_used=YES;
    else if (new_used && p_lin->bits&NEW_TICKET) {
      rec_ix-=processed; break;
    }
    if (!new_used && first && p_lin->bits&0x80) {
/* doe niets, mag er ooit wel eens uit !! */
    }
    else {
      valid(rec_ix-processed);
      p_vrk->used++; first=NO;
    }
    if (!new_used && p_lin->groep==GRP_TIJD) break;
  }
  return rec_ix;
}
 
static int valid(long rec_ix)
{
  unsigned char *s;
  int j,ok;
 
  ok=YES;
  if (p_lin->bits & 0x80) {
    if (p_lin->bits!=0x80 && p_lin->bits!=0xC0 && p_lin->bits!=0x82) ok=NO;
    s=(unsigned char *)p_lin->text;
    for (j=0; j<40; j++) {
      if (*s && *s<' ') ok=NO;
      s++;
    }
    if (p_lin->groep<9990 || p_lin->groep>9999) ok=NO;
  }
  else if ((p_lin->groep==GRP_PUNTEN) || (p_lin->groep==GRP_PUNTEXTRA)) {
    ok=YES; /* geen controle doen op info, wordt anders gebruikt ! */
  }
  else {
  /*                    op 19/12/94 : controle op codenummer eruit.
    s=p_lin->code;
    for (j=0; j<sizeof(p_lin->code); j++) {
      if (*s && (*s<'0' || *s>'9') && p_lin->groep!=GRP_CONVERT) ok=NO;
      s++;
    }
  */
    if (p_lin->btw<-1. || p_lin->btw>99.) ok=NO;
    if (p_lin->totaal<-999999. || p_lin->totaal>999999.) ok=NO;
  }
  if (!ok && rec_ix>=0) {
    sprintf(buf,"Bad record, ix=%6ld  pos=%3d",rec_ix,p_vrk->used+1);
    prt_nl(buf);
    p_lin->totaal=0.;
    p_lin->btw=0.;
    ok=YES;/* mvg : added this and previous line to get better info on error */
/* via check of the sums this ticket will be printed ! */
  }
  return ok;
}
 
static int _read_process()
{
  char bits;
  int groep, processed;
 
  dread(logref,&p_lin->bits,(int)header.rec_len); processed=1;
  bits=p_lin->bits;
  if (bits & 0x80) {
    movmem(p_lin->code,p_lin->text,20);
    movmem(p_lin->code+20,&groep,sizeof(groep));
    dread(logref,&p_lin->bits,header.rec_len); processed++;
    movmem(p_lin->code,&p_lin->text[20],20);
    zeroes(p_lin->code,sizeof(struct s_lijn)-sizeof(p_lin->bits)-sizeof(p_lin->text));
    p_lin->groep=groep;
    p_lin->bits=bits;
  }
  return processed;
}
 
int next_ticketnr(void)
{
  int next;

  next = header.ticketnr+1;
  if (next>=10000) next=1;
  return next;
}
 
static int leeg_log(int line, char *logname)
{
  char *s,*p;
  int i, len_avail, len_used;
  int SeqRef;
  long len;
 
  len_avail=sizeof(buf); s=buf;
  p=getml(32000L);
  if ((long)p != 0L) {
    s=p; len_avail=32000;
  }
  p=s; i=len_avail; while (i--) *p++=0;
  disp_vid(19,line,"=> Creating NEW ...",0);
  header_init();
  logref=dcreat(logname,CREAMODE);
  len = header.rec_pos + (long)header.rec_len * header.rec_aantal;
  while (len>0) {
    if (len>len_avail) len_used=len_avail; else len_used=len;
    dwrite(logref,s,len_used);
    len-=len_used;
  }

	SeqRef=dopen("kasseqnr.dat",RDWRMODE);
  dread(SeqRef,(char *)&header.LastZTotaalPrintedSeqNr,sizeof(header.LastZTotaalPrintedSeqNr));
	dread(SeqRef,(char *)&header.ticketnr,sizeof(header.ticketnr));
	dclose(SeqRef);

  dseek(logref,0L,0); dwrite(logref,(char *)&header,sizeof(header));
  dclose(logref);
  if (len_avail==32000) {
    if (rlsml(s,32000L)) disp_exit("Problems with rlsml-function");
  }
  return dopen(logname,RDWRMODE);
}
 
static void header_init(void)
{


  movmem(versie,header.versie,sizeof(versie));
  header.lade_pos   =256;
  header.lade_aantal=lade_aantal;
  header.lade_len   =sizeof(lade);
  header.dag_pos    =header.lade_pos + header.lade_aantal * header.lade_len;
  header.dag_aantal =(short) dag_aantal;
  header.dag_len    =sizeof(dag);
  header.dag_used   =0;
  header.rec_pos    =header.dag_pos + header.dag_aantal * header.dag_len;
  header.rec_len    =sizeof(struct s_lijn) - sizeof(p_lin->text);
  header.rec_aantal =rec_aantal;
  header.rec_used   =0;
}

void logheadcheck(int nr) 
{
	struct s_header _head;

	long CurrPos=dseek(logref,0,SEEK_CUR);
	dseek(logref,0L,0);
	dread(logref,&_head,sizeof (s_header));
	if (_head.rec_used > header.rec_used) {  // we gaan het aantal rec_used verminderen, zou niet mogen !!!
		char buf[100];
		sprintf(buf,"Error %d on writing to KASLOG ...",nr);
		int ref=dcreat("kascheck.log",CREAMODE);
		if (ref>=0) {
			dwrite(ref,buf,strlen(buf));
			dclose(ref);
		}
		disp_exit(buf);
	}
	dseek(logref,CurrPos,0L);
}

void logdump(long pos, char *s, int size)
{
  dseek(logref,pos,0);
  dwrite(logref,s,size);
}

void debdump(char *s)
{
  int fref, i;

  fref=dopen("kassa.deb",RDWRMODE);
  if (fref<0) fref=dcreat("kassa.deb",CREAMODE);
  if (fref>=0) {
    dseek(fref,0L,2);
    for (i=0; i<1000; i++) {
      if (!s[i]) break;
    }
    dwrite(fref,s,i);
    dwrite(fref,"\r\n",2);
    dclose(fref);
  }
}

// kasticke.cpp

extern char *txtbet[], txtvrk[], tijd[], krt_lead[];
                                                                        
extern char prt_head[10][41], fakt_head[20][51], prt_foot[2][41];
extern int groep_leeg;
extern short int prx_sys[VRK_COUNT], vrk_lade[VRK_COUNT], leeg_sys[VRK_COUNT];
extern int vrk_ix;
extern int plu_ix, ticketnr, notime_fl;
extern int def_digits, EigenPrijsOpStuksAllowed;
extern char def_valuta[], TotaalOp5CentAfronden, PromoNotOnHorecaPrice;
extern float def_round;
extern double BedragTotaalafronding;

void adj_text(int index)
{
  struct s_lijn *p_lin;
  char erase,*txt,*s, digits, cnv_digits, _digits, txtbuf[50];
  int j,aantal,groep,sup,off,dig,_ix,val_ix,pval_ix,SubtIsTekst_=NO;
  double suppleenh=0, suppltotaal=0;
   
  digits=def_digits; cnv_digits=def_digits;
  p_lin=(struct s_lijn *) p_vrk->lijn[index].text; s=p_lin->text;
  groep=p_lin->groep;
  if (groep>=9990 && groep<=9998) goto end;
  else if (groep==GRP_TIJD) {
    get_tijd(); ticketnr=log_getticket();
    if (notime_fl) tijd[15]=0;
    _clr_text(s);
    movmem(txtvrk,s,5);
    movmem("T:",s+6,2); int2str(ticketnr,s+8,-4);
    aantal=(int)(p_vrk->aantal[0]-p_vrk->aantal[1]+.5);
    movmem("A:",s+13,2);int2str(aantal,s+15,-3);
    if (notime_fl) movmem(tijd,s+26,15);
    else movmem(tijd,s+20,21);
    goto end;
  }
  else if (groep==GRP_FAKT) {
		if(p_lin->code[0]=='F') movmem(txttxt[105],s+20,20);
		else if(p_lin->code[0]=='L') movmem(txttxt[106],s+20,20);
		else movmem(txttxt[45],s+20,20);
    goto end;
  }
  else if (groep==GRP_PUNTEN) {
    _clr_text(s);
    goto end;
  }
  else if (groep==GRP_TERPLAATSE) {
    movmem(txttxt[80],s+20,20);
    goto end;
  }
  SubtIsTekst_ = NO; if (groep == GRP_SUBTOT && p_lin->bits) SubtIsTekst_ = YES; // subtotaal gebruikt om vervangende tekst te drukken
  txt="";
  erase=YES;
  if (SubtIsTekst_ || ((groep>=0 && groep <1000) && *(s+POS_NAAM)>' ')) erase=NO;
  if (groep == GRP_FKORT && *(s + POS_NAAM) > ' ' && p_lin->fl_promoLijn) erase = NO; // speciale tekst korting 1+1 gratis
  if (erase) {
    _clr_text(s);
    if (groep>=0 && groep<1000) {
      if (p_lin->code[0]) {
        _ix=kasplu.plu_req(p_lin->code,ARTCODE_LEN);
        if (_ix>=0) {
          plu_ix=_ix;
          txt=kasplu.art_info.naam;
          if (groep==0 || groep>99) {/* als er toen geen goede groep ingevuld was ... */
            groep=kasplu.art_info.groep;/* en nu wel ... */
            p_lin->groep=groep;
          }
        }
      }
      else if (groep>=0 && groep<100) txt=grp_info[groep].naam;
    }
  }
  if (groep<0 || groep>=1000) switch (groep) {
    case GRP_TOTAAL:   if(TotaalOp5CentAfronden=='C' && (BedragTotaalafronding<-0.005 || BedragTotaalafronding>0.005)) txt =txttxt[108]; else txt=txtbet[01]; break;
    case GRP_GELD:     txt=txtbet[02]; break;
    case GRP_ECHEQUE:  txt=txtbet[07]; break;
    case GRP_BANCONT:  txt=txtbet[06]; break;
    case GRP_MAALTIJD: txt=txtbet[03]; break;
    case GRP_TGBON:    txt=txtbet[05]; break;
    case GRP_LEVERBON: txt=txtbet[04]; break;
    case GRP_CREDIT:   txt=txtbet[8]; break;
    case GRP_MOBIEL:   txt=txtbet[19]; break;
    case GRP_TERUG:    txt=txtbet[9]; break;
    case GRP_TEGOED:   txt=txtbet[10]; break;
    case GRP_GOEDEREN: txt=txtbet[11]; break;
		case GRP_VOORSCHOT:txt=txtbet[32]; break;
		case GRP_AFRONDING:txt=txtbet[14]; break; // totaal afdrukken ipv afronding (33)
    case GRP_LGMEE:
      if ((p_lin+1)->groep==GRP_LGTERUG) txt=txtbet[12];
      else txt=txtbet[31];
      break;
    case GRP_LGTERUG:  txt=txtbet[18]; break;
		case GRP_VOORSCHOT_B: txt=txtbet[20]; break;
		case GRP_VOORSCHOT_R: txt=txtbet[21]; break;
		case GRP_FKORT:    txt = txttxt[4]; break;
    case GRP_PKORT:    txt=txttxt[5];  break;
    case GRP_SUBTOT:   txt=txttxt[6];  break;
    case GRP_TBSALDO:  txt=txtbet[13]; break;
    case GRP_DIVUITGAVE:txt=txtbet[15];break;
    case GRP_DIVONTVANG:txt=txtbet[16];break;
    case GRP_CDBON_VRK:txt=txtbet[22];break;
    case GRP_CDBON_BET:txt=txtbet[23];break;
    case GRP_ZEGELS:   txt=txtbet[17];break;
    case GRP_VAR_BET1: txt=txtbet[24];break;
    case GRP_VAR_BET2: txt=txtbet[25];break;
    case GRP_VAR_BET3: txt=txtbet[26];break;
	case GRP_EMAALTIJD: txt = txtbet[3]; break;
	case GRP_EECOCHEQUE: txt = txtbet[27]; break;
	case GRP_ECADEAUBON: txt = txtbet[28]; break;
	case GRP_ECONSUMBON: txt = txtbet[29]; break;
	case GRP_CASHAUT: txt = txtfin[38]; break;
    case GRP_MEETOTAAL:txt=txtbet[14]; break;
    case GRP_OPENLADE: txt=txttxt[59]; break;
    case GRP_EURO:     txt=txttxt[68]; break;
    case GRP_CONVERT:
      movmem(txtbet[30],txtbuf,sizeof(txtbuf));
      movmem(p_lin->code,&txtbuf[12],4);
			txt=txtbuf;
      break;
  }
  sup=0;
  if ((groep>=0 && groep<1000)) {
    suppleenh=0; suppltotaal=0;
    if (optiestype==1) {
      for (j=index+1; j<p_vrk->used; j++) {
        if (p_vrk->lijn[j].bits&AUTO_LEEG) {
          if (p_vrk->lijn[j].groep==optiesgroep) {
            suppleenh+=p_vrk->lijn[j].prijs;
            suppltotaal+=p_vrk->lijn[j].totaal;
          }
        }
        else break;
      }
    }
    if (p_lin->bits&AUTO_LEEG && p_lin->groep==groep_leeg) {
      txt=grp_info[groep_leeg].naam;
    }
    else if (p_lin->bits&AUTO_LEEG && (plulink==1 || (optiestype==1 && optiesgroep))) {
      // geen aantal afdrukken ...
    }
    else {
      if (p_lin->bits&STUKS) {movmem(txttxt[7],&p_lin->text[POS_AANTAL+4],2); dig=3;}
      else dig=5;
      conv_getal((double)p_lin->aantal,&p_lin->text[POS_AANTAL],dig,NO,3); // MARC, was vroeger 2
    }
  }
  else if ((groep>=1000 && groep<=1030)||(groep>=1040 && groep<=1049) ||groep==GRP_EURO) {
    val_ix=(int)p_lin->btw-1;
    j=valuta[val_ix].digits;
    if (val_ix>=0) digits=j;
    if (groep==GRP_CONVERT) {
      pval_ix=(int)(p_lin-1)->btw-1;  
      if (val_ix>=0) cnv_digits=def_digits;
      else cnv_digits=valuta[pval_ix].digits;
    }
    else {
      sup=3;
    }  
  }
  if (groep>=GRP_SUBTOT && groep<1000) {
    if (p_lin->bits&STUKS) off=1; else off=0;
    if (optiestype==1 && p_lin->groep==optiesgroep) {
      // druk geen prijs af !
    }
    else {
      _digits=digits;
      if (ep_digits) _digits=ep_digits;
	  if (SubtIsTekst_==NO) { // NIET indien subtotaal = vervangende tekst
		conv_getal((double)p_lin->prijs + suppleenh, &p_lin->text[POS_PRIJS + off], 7 - off, NO, _digits);
	  }
    }
  }
  else if (groep==GRP_CONVERT) {
    conv_getal((double)p_lin->prijs,p_lin->text,POS_PRIJS+7,YES,cnv_digits);
  }
  else if (groep==GRP_PUNTEXTRA) {
    copynaam(txttxt[70],s+POS_NAAM,POS_TOTAAL-POS_NAAM);
    conv_getal((double)p_lin->aantal,&p_lin->text[POS_AANTAL],5,NO,2);
    goto end;
  }    
  if (optiestype==1 && p_lin->groep==optiesgroep) {
    // druk geen prijs af !
  }
  else {
		if(p_lin->groep==GRP_AFRONDING) conv_getal((double)p_lin->prijs,&p_lin->text[POS_TOTAAL-sup],7+sup,YES,digits); // in prijs zit het totaal 
		else conv_getal((double)p_lin->totaal + suppltotaal,&p_lin->text[POS_TOTAAL-sup],7+sup,YES,digits);
	}
  off=0;
  if (groep>=1000 && groep<2000 && groep!=GRP_CONVERT&& groep!=GRP_VOORSCHOT_R && groep!=GRP_CDBON_VRK) off=7;
  if (SubtIsTekst_==NO && !(groep == GRP_FKORT && *(s + POS_NAAM) > ' ' && p_lin->fl_promoLijn)) {// NIET speciale tekst korting 1+1 gratis of vervangende tekst
	copynaam(txt, s + POS_NAAM + off, POS_TOTAAL - POS_NAAM - off);
  }
  if (groep==GRP_LGTERUG) adj_text(index-1);
  if (optiestype==1 && p_lin->groep==optiesgroep) {
    j=index-1;
    while (j>=0) {
      if ((p_vrk->lijn[j].bits&AUTO_LEEG)==0) {
        adj_text(j);
        break;
      }
      j--;
    }
  }

 end:;
}

void prt_body(char controle)
{
  char buf[14];
	bool PrtEanFlag=false;
  int i, j, k, nr, groep, off;
 
  for (j=0; j<p_vrk->used; j++) {
	for (k = j; k < p_vrk->used; k++) if (p_vrk->lijn[k].groep == GRP_SUBTOT) break;
	if (k < p_vrk->used && p_vrk->lijn[k].bits) j = k;
    off=0;
    groep=p_vrk->lijn[j].groep;

		if (groep==GRP_PUNTEN && controle==1 && (ConfigFlags&1)==0) {  // plaats besparen op controleband door punten niet af te drukken !
			j+=4;
			continue;
		}

		if (groep==GRP_VOORSCHOT_B) prt_nl("");
    if (((groep==GRP_FAKT)|| (groep==GRP_TERPLAATSE) || (groep==GRP_TIJD)||(groep==GRP_EURO))&&!controle) prt_cod(7);
    if ((groep>=1000 && groep<2000 && groep!=GRP_CDBON_VRK && groep!=GRP_CONVERT && groep!=GRP_PUNTEXTRA && groep!=GRP_VOORSCHOT_R) || groep==GRP_T_RB) {
      prt_cod(3); off=20;
    }
    if (groep==GRP_GOEDEREN || groep==GRP_TOTAAL || groep==GRP_TEGOED
        || groep==GRP_TERUG || groep==GRP_T_R || groep==GRP_T_RB
        || groep==GRP_MEETOTAAL || groep==GRP_OPENLADE) {
      prt_cod(2);
    }
    if (groep==GRP_T_U) prt_nlu(&p_vrk->lijn[j].text[off]);
    else prt_nl(&p_vrk->lijn[j].text[off]);
    if (groep==GRP_TIJD) {
      if (controle==0) {
        
      }    
      else if (controle==1) prt_cod(7);
      else if (controle==2 && (j+1)<p_vrk->used) prt_hoofd(NO);
    }
    if (off==20) prt_cod(4);
    if (groep==GRP_PUNTEN) {
      buf[0]='2'; buf[1]='5';
      for (i=0; i<5; i++) buf[2+i]=krt_lead[i];
      nr=(int)p_vrk->lijn[j].btw;
			if (nr>0) PrtEanFlag=true;
      for (i=0; i<5; i++) {
        buf[11-i]='0'+nr%10;
        nr=nr/10;
      }
      buf[12]=0;
      if (PrtEanFlag) prt_ean(buf);
      if ((p_vrk->lijn[j].aantal>0) && ((p_vrk->lijn[j].prijs+p_vrk->lijn[j].totaal)==0)) {
        /* verkoop niet op klantenkaart bijgeschreven .... */
        nr=(int)p_vrk->lijn[j].aantal;
        for (i=0; i<5; i++) {
          buf[11-i]='0'+nr%10;
          nr=nr/10;
        }
        buf[1]='4';
        prt_ean(buf);
      }
    }
  }
  if (!controle) {
    for (j=0; j<2; j++) {
      if (prt_foot[j][0]) prt_nl(prt_foot[j]);
    }
  }
	if(controle==1 && PrintControl2PDF) prt_nl("----------------------------------------");
}
 
void prt_hoofd(char kasticket)/* YES als firma-hoofding & kolom hoofding */
{
  char cut_flag, work[41];
  int lijn, j, last,font_,beg_=0;
 
  cut_flag=NO; work[40]=0;
  prt_cod(0);
  for (j=0; j<2; j++) prt_cod(7);
  lijn=2;
  if (kasticket) {
    for (j=0; j<10; j++) {
      if (prt_head[j][0]) {
        if (j==0) prt_cod(2);
		if (prt_head[j][0] == '*' && prt_head[j][1] == 0) {
		  if (PrintControl2PDF || NoPrtCut == YES) prt_nl(""); else prt_cod(7);
		}
        else{
          font_=0;beg_=0;
          if(prt_head[j][0]=='@'){
						if(prt_head[j][1]=='b' || prt_head[j][1]=='b'){ font_=1;beg_=2;} // bold 
						else if(prt_head[j][1]=='e' || prt_head[j][1]=='E'){font_=2;beg_=2;}  // elongated bold
					}
          if(font_==1) prt_cod(2);
          if(font_==2){prt_cod(2);prt_cod(3);}
					prt_nl(&prt_head[j][beg_]);
          if(font_==1) prt_cod(8);
          if(font_==2){prt_cod(8);prt_cod(4);}
				}
        cut_flag|=prt_cut(2+lijn++);
      }
    }
  }
  else {
    for (last=19; last>=0; last--) {
      if (fakt_head[last][0]) break;
    }
    for (j=0; j<last; j++) {
      if (j==0) prt_cod(2);
      movmem(fakt_head[j],work,40);
      font_=0;beg_=0;
      if(work[0]=='@'){
				if(work[1]=='b' || work[1]=='b'){ font_=1;beg_=2;} // bold 
				else if(work[1]=='e' || work[1]=='E'){font_=2;beg_=2;}  // elongated bold
      }
      if(font_==1) prt_cod(2);
      if(font_==2){prt_cod(2);prt_cod(3);}
      prt_nl(&work[beg_]);
      if(font_==1) prt_cod(8);
      if(font_==2){prt_cod(8);prt_cod(4);}
      cut_flag|=prt_cut(2+lijn++);
    }
  }
// Nog op te lossen WINDOWS
//  while (!cut_flag) {prt_cod(7); cut_flag|=prt_cut(2+(lijn++));}
  if (kasticket==YES) prt_nlu(txttxt[12]); /* als kasticket>2 dan ook niet */
  else prt_cod(7);
}

void add_text(char *s)
{
  p_lin->groep=GRP_TEXT;
  _clr_text(p_lin->text);
  copynaam(s,p_lin->text,40);
  p_lin++; p_vrk->used++;
}

void add_ix_text(int index, char *s)
{
  struct s_lijn *p_lin;

  p_lin=(struct s_lijn *) p_vrk->lijn[index].text;

  p_lin->groep=GRP_TEXT;
  _clr_text(p_lin->text);
  copynaam(s,p_lin->text,40);
}
 
void add_etext(char *s)
{
  p_lin->groep=GRP_T_RB;
  _clr_text(p_lin->text);
  copynaam(s,p_lin->text,40);
  p_lin++; p_vrk->used++;
}
 
int prt_cut(int line)
{
#if CONTROL2PDF
	if(PrintControl2PDF){  
	  if (line==3) {prt_cod(1); return YES;}
	}
	else {
    if (line==PrtDrv[Prt[PrtNr].type].cut_count) {prt_cod(1); return YES;}
	}
#else
  if (line==PrtDrv[Prt[PrtNr].type].cut_count) {prt_cod(1); return YES;}
#endif
  return NO;
}
 
void _clr_ticket(void)
{
  char *s;
  unsigned len;
  int _fl;
 
  _fl=p_vrk->bak_flag;
  len=sizeof(struct s_verkopen); s=(char *)&p_vrk->used;
  while (len-->0) *s++=0;
  p_vrk->leeg_flag=(char)leeg_sys[vrk_ix];
  p_vrk->prx_ix=prx_sys[vrk_ix];
  p_vrk->klant_nr=0;
  p_vrk->bak_flag=_fl;
	p_vrk->btw_holland=btw_holland;
}
 
void _clr_text(char *p)
{
  int j;
 
  for (j=0; j<sizeof(p_lin->text)-1; j++) *p++=' ';
  *p=0;
}

double str2dbl(char *s)
{
  bool negative=false,decim=false;
  double fuval=0,coef=1.;

  while(1){
    if(*s==' ');
		else if(*s=='+') negative=false;
    else if(*s=='-') negative=true;
    else if(*s>='0' && *s<='9'){
      if(decim){
        coef=coef/(float)10.;
        fuval+=(*s-'0')*coef;
      }
      else fuval=fuval*10+*s-'0';
    }
    else if(*s=='.' || *s==',') decim=true; 
    else break;
		s++;
  }
  if(negative) fuval=-fuval;
  return fuval;
}

double str2dbl(CString cstr) {
	return str2dbl((char *)(LPCTSTR)cstr);
}