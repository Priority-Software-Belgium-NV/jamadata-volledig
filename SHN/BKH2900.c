/*32-01*/
#ifdef _WIN32
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* BKH2900GetD() {return &zzvw;}
#include "OvlShare.h"

#define ovldat BKH2900dat
#define ovlcod BKH2900cod
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

char ovldat[] = "bkh2900  00:01 11/07/01 (c) Jamadata";
 
#define FOREVER         while(1)
#define YES             1
#define NO              0

#define flag            uint16
#define ADDPOS          100
#define D_LIN_SCR       17
#define MAX_RECS        15000
#define MAX_SEARCH_KEYWORDS  10
#define MAX_FIELDS     300/* maximum number of fields in 1 structure */

extern char SearchText[]; // gebruikt in ovl2900
																													// search 

// FLAGCOC : zoek met + op lev.ref met key 11 en - zoek op lev.ref2 met key 12
// FLAGGBL : bij opzoeken artikel : in lijst ook 4 verkoopprijzen tonen
// FLAGENS : bij opzoeken artikel : in lijst ook 4 verkoopprijzen tonen



extern int16 retcall,parmcall[8];
extern char *s();
extern int16 *i();
extern uint16 *u(),dateadd();
extern long *l(),val();
extern float *f();
extern double *d(),valu_cnv();

static char fm_os72[]  = {7,0x88,72,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};

#if FLAGMAE
#define DIM_FICHES      8
#define DIM_SITEMS      15
static char *fichenm[DIM_FICHES]={"leverancier","klant","grootboekrekening","artikel","klantentoer","klantenkaart","","nummerplaat"};
static int fichestu[DIM_FICHES]={1,2,3,6,63,92,52,70};
static int SearchFldNrs[DIM_FICHES][DIM_SITEMS]={1,2,3,4,5,6,7,8,9,10,21,22,24,0,0,   // leverancier
																				 1,2,3,4,5,6,7,8,9,10,21,22,68,69,0,   // klant
																				 1,2,3,0,0,0,0,0,0, 0, 0, 0, 0,0,0,   // GRB-rekening
																				 1,2,3,4,5,6,8,66,0,0, 0, 0, 0,0,0,   // artikel
																				 3,0,0,0,0,0,0,0,0, 0, 0, 0, 0,0,0,   // klantentoer
	                                       1,2,3,4,5,6,7,8,9,10,11, 0, 0,0,0,   // klantenkaart
																				 1,2,3,0,0,0,0,0,0, 0, 0, 0, 0,0,0,  // artikelgroepen
																				 1,2,4,5,6,90,0,0,0, 0, 0, 0, 0,0,0};  // nummerplaten
#else
#define DIM_FICHES      7
#define DIM_SITEMS      20
static char *fichenm[DIM_FICHES]={"leverancier","klant","grootboekrekening","artikel","klantentoer","klantenkaart",""};
static int fichestu[DIM_FICHES]={1,2,3,6,63,92,52};
static int SearchFldNrs[DIM_FICHES][DIM_SITEMS]={1,2,3,4,5,6,7,8,9,10,21,22,24,0,0,0,0,0,0,0,   // leverancier
																				 1,2,3,4,5,6,7,8,9,10,20,21,22,68,69,143,70,0,0,0,   // klant
																				 1,2,3,0,0,0,0,0,0, 0, 0, 0, 0,0,0,0,0,0,0,0,   // GRB-rekening
																				 1,2,3,4,5,6,8,66,70,71,73, 0, 0,0,0,0,0,0,0,0,   // artikel
																				 3,0,0,0,0,0,0,0,0, 0, 0, 0, 0,0,0,0,0,0,0,0,   // klantentoer
	                                       1,2,3,4,5,6,7,8,9,10,11, 0, 0,0,0,0,0,0,0,0,   // klantenkaart
																				 1,2,3,0,0,0,0,0,0, 0, 0, 0, 0,0,0,0,0,0,0,0};  // artikelgroepen
#endif



static int AllKeywordsFound();
static void GetSearchKeyWords();
static void InitConvertTab();  // komt uit JMS

static long get_btw();
static char* GetString();
static char SearchKeywords[MAX_SEARCH_KEYWORDS][100];
static char ICSBTab[256];
static int16 retmain,stu,sys3876,zoekkey,zoekwijze,zoeklen;
static char searbuf[512],zoekstr[100],vptekst[10][10],sys2993;
static uint16 recs[MAX_RECS],recs_used,sear_stt;
static long zoekbtwnr;
static int16 len2,len3;
static uint16 *pu_s_1;
static char *ps_s_2,*ps_s_3;

 
#if 0
parm :0     structuur
      1     fasmngr-key
      2     #wrkrecord (of 0 bij 1e keer)
      4     bits
	      0 richting : 1=vooruit, 0=achteruit
	      1 display : "wacht even" 0=No, 1=Yes
	      2 vorige wrk-recs mogen weg : enkel nieuwe tabel overhouden
	      4 tijdsbeperking toepassen
	      5 (enkel bij exit : zie verder)
      5     aantal te laden fiche# per wrkrecord (slechts eenmalig)
	      Pas op : bij exit = aantal geladen fiche# in wrkrecord
      6     aantal gevonden records, waarna te returnen
      7     bits
	      2 bij grb : ENKEL rekeningen, waarop mag geboekt
	      3 bij grb : ENKEL rekeningen, alle rekeningen tonen
				4 bij KLT/ART : ENKEL actieve a.h.v.veld 6,200
				5 bij ART : altijd selectiescherm tonen, ook bij 1 artikel (DRK0214)
#endif

ovlcod(parmval)
int16 parmval; // parmval = stu
{
  int16 mode_,pfiche_;
  char buf_[100];
  
  initload();
	stu=parmval; mode_=parmcall[0];
	copy(s(stu,2),buf_,(fldlen(stu,2)+fldlen(stu,3)));

	if(mode_==98){ // extra zoekfunctie met functietoetsen 
		for(pfiche_=0;DIM_FICHES;pfiche_++) if(stu==fichestu[pfiche_]) break; 
		if(pfiche_>=DIM_FICHES) mode_=0; // klassieke search 
	}
	retcall=ExecSearch(stu,mode_);
	//	FOREVER{
	//		scrget(1,1005);
	//		scrifld(1,fm_os20,fichenm[pfiche_]);
	//		scrfld(2,25,1);
	//		scrfld(3,stu,3);
	//		key=scrupd(3,0x0791);
	//		if(key==101) {errnum=39;retcall=YES;break;}
	//		copy(s(stu,3),buf1_,fldlen(stu,3));
	//		switch(key){
	//		  case 105  : copy("$",s(stu,3),1);copy(buf1_,s(stu,3)+1,fldlen(stu,3)-1); break; // btw-nummer	
	//		  case 109  : copy("..",s(stu,3),2);copy(buf1_,s(stu,3)+2,fldlen(stu,3)-2); break; // stuk codenummer 
	//			case 110  : copy("#",s(stu,3),1);copy(buf1_,s(stu,3)+1,fldlen(stu,3)-1); break; // stuk in naam 
	//			case 111  : copy("+",s(stu,3),1);copy(buf1_,s(stu,3)+1,fldlen(stu,3)-1); break; // straatnaam 
	//			case 112  : copy("=",s(stu,3),1);copy(buf1_,s(stu,3)+1,fldlen(stu,3)-1); break; // gemeente
	//			default   : break;
	//		}
	//		if(ExecSearch(stu,0)==0) {retcall=NO;break;}
	//		copy(buf1_,s(stu,3),fldlen(stu,3));
	//	}
	//}
	//else retcall=ExecSearch(stu,mode_);
	if(retcall){
	  fasinit(stu); copy(buf_,s(stu,2),fldlen(stu,2)+fldlen(stu,3));
  }
  else{
		zero(SearchText,SearchTextSize);
  }
  ovlexit(-1);
}

ExecSearch(stu,mode_)
int16 stu,mode_;
{
  int16 byte,nr_,j,k,key,z,start_,lijnpos,q_,filtermode_,retval_,filter_used_=NO,dsp_mode_=0,ori_mode_;
  char zoek_arg[51],*pzoek,str_[30],lijn_attrib_,buf1000_[1000];
  unsigned short funckeys;
  long lbd_,last_rec_;

	copy(s(stu,1),buf1000_,fldlen(stu,0));ori_mode_=mode_;
	full_redo:;
  scrget(1,7);scrupd(-3,0);filtermode_=NO;
	if(stu==52) mode_=98; // altijd via wildsearch
	ps_s_2=s(stu,2);ps_s_3=s(stu,3);pu_s_1=u(stu,1);
  len3=fldlen(stu,3);
  len2=fldlen(stu,2);//if(len2 && faskeyi(stu,1,0)==45) len2=0; // indien geen key, dan ook geen code 
#if FLAGMAE
	if(stu==70) len3=0;
#endif
  zero((char *)&recs[0],sizeof recs);recs_used=0;
	if(stu==41) copy(ps_s_2,zoek_arg,len2); else copy(ps_s_3,zoek_arg,len3); zoek_arg[len3]='\0';
	if(stu==52 || mode_==98){zoekwijze=98;DoWildSearch(dsp_mode_); goto end_fill_tabel;}
#if FLAGMAE
	if(stu==70 && mode_==98){
		copy(s(70,5),zoek_arg,fldlen(70,5));
		zoekwijze=98;DoWildSearch(); goto end_fill_tabel;}
#endif
	filtermode_=NO; if(mode_==99) {filtermode_=YES;mode_=0;}
  if(mode_){ // mode_ 0: naam of code#, mode_ 2 of 3: volgens dat veld 
	  if(*s(stu,mode_)=='\0'){errnum=38;goto end;}
  }
  else{
    if(filtermode_==NO && *s(stu,3)=='\0'){errnum=38;goto end;}
  }
	
  copy(SearchText,searbuf,sizeof searbuf);//if(searbuf[0]=='\0') zero(searbuf,sizeof searbuf);
  zero(SearchText,SearchTextSize);
  for(k=0;k<(len2+len3);k++) if(searbuf[k]!=*(ps_s_2+k)) break;
  copy(s(stu,2),searbuf,len2+len3);
  fasinit(stu); copy(searbuf,s(stu,2),len2+len3);
  if(k==(len2+len3) && searbuf[ADDPOS]==stu && bittst(parmcall[1],2)){// ga fiche adden bij 2e oproepen 
    switch(stu){
      case 1  : nr_=2911; break;
      case 2  : nr_=2921; break;
      case 3  : nr_=2931; break;
      case 6  : nr_=2961; break;
      case 92 : nr_=294; break;
      default : nr_=0; break;
    }
    if(nr_){
			*u(stu,1)=0;
      ovlcall(nr_,2);
      if(*u(stu,1)){// toevoegen gelukt
				zero(SearchText,SearchTextSize);
				retcall=NO;errnum=0;ovlexit(-1);
			} 
		  else{
				errnum=39; goto end;
		  }
		}
  }
  *pu_s_1=0;
  if(mode_==2){
		if(stu==3 || stu==41 || stu==70){
				errnum=faskeyi(stu,1,0);goto end;// direct zoeken 
		}
		else{
		  *ps_s_3='.';copy(ps_s_2,ps_s_3+1,len2);
		}
  }
  copy(ps_s_3,zoek_arg,len3);zoek_arg[len3]='\0';
  zoekkey=2;zoekwijze=0;  // gewoon op naam zoeken als default nemen
  zoeklen=Copy2ZoekStr(&zoek_arg[0],len3,len3);pzoek=ps_s_3;
  byte=zoek_arg[0];
  if(filtermode_==NO && byte=='\0') {errnum=38;goto end;}
  if(byte=='.'){//  zoek op codenummer 
		if(len2 && zoek_arg[1]=='.'){ // .. is zoeken op stuk codenummer 
			zoekwijze=1; zoekkey=1;
			zoeklen=Copy2ZoekStr(&zoek_arg[2],len3-2,len2);
			fasinit(stu);pzoek=ps_s_2;
			goto fill_tabel;
		}
		if(stu==3){// selectie op stuk codenummer 
			zoekwijze=1;zoekkey=1;
			zoeklen=Copy2ZoekStr(&zoek_arg[1],len3-1,8);
			fasinit(3);//grb_comp(&zoek_arg[1],ps_s_2);pzoek=ps_s_2;
			goto fill_tabel;
    }
    if(len2==0) byte='?';
    else {mode_=2;copy(&zoek_arg[1],ps_s_2,len2);}
  }
  if(byte=='?'){ // zoek op recordnummer 
    *pu_s_1=val(&zoek_arg[1]);mode_=1;
  }
  if(byte>='0' && byte<='9'){ // codenummer
		mode_=2;
    if(stu==3) grb_comp(&zoek_arg[0],ps_s_2);
    else{
			if(len2 && stu!=92) {copy(&zoek_arg[0],ps_s_2,len2);}
			else{
				if(stu!=6 || (sys3876&0x01) ){*pu_s_1=val(&zoek_arg[0]);mode_=1;}
				else mode_=3;
			}
    }
  }
  zoekkey=2;zoekwijze=0;  // gewoon op naam zoeken als default nemen
  zoeklen=Copy2ZoekStr(&zoek_arg[0],len3,len3);pzoek=ps_s_3;

  if(mode_==1){errnum=fasgeti(stu);if(errnum) errnum=39; goto end;}// op record
  if(mode_==2){
		if(stu==29){// zoek op stuk van postcode
			zoekkey=1; zoekwijze=1;  // postcode met directe key
			zoeklen=Copy2ZoekStr(s(29,2),len2,len2); pzoek=s(29,2);
			goto fill_tabel;
		}
		else if(stu==6 && (sys3876&2)){// zoek op stuk van artikelcode 
			zoekkey=1; zoekwijze=1;  // artikelreferentie met directe key
			zoeklen=Copy2ZoekStr(s(6,2),len2,len2); pzoek=s(6,2);
			goto fill_tabel;
		}
		else{
			errnum=faskeyi(stu,1,0);goto end;// direct zoeken 
		}
  }   
  // speciale zoekmethodes definieren 
	
  if(byte=='+'){
		if(stu==6 && fldlen(6,8)){// zoek op referentie artikel
			zoekkey=7; zoekwijze=2;

			if(parmcall[4]) zoekkey=parmcall[4];  // artikelreferentie met directe key
			if(faskeyi(6,zoekkey,1)==45){zoekwijze=3;zoekkey=2;}  // artikelreferentie zonder key, alfa overlopen
			else *u(6,1)=0;
#if FLAGCOC
			zoekkey=11; zoekwijze=0; len3=fldlen(6,8); 
#endif
			zoeklen=Copy2ZoekStr(&zoek_arg[1],len3-1,fldlen(6,8));
			copy(&zoek_arg[1],s(6,8),zoeklen); pzoek=s(6,8);
			goto fill_tabel;
		}
		if(stu==1 || stu==2 || stu==92){// zoek op straatnaam
			zoekwijze=5;zoekkey=2;// straatnaam zonder key, alfa overlopen 
      if(parmcall[4]){		  
	    if(faskeyi(stu,parmcall[4],1)==0){zoekkey=parmcall[4];zoekwijze=4;}  // straatnaam met directe key
	  }
	  zoeklen=Copy2ZoekStr(&zoek_arg[1],len3-1,fldlen(stu,4));
	  copy(&zoek_arg[1],s(stu,4),zoeklen); 
		zero(s(stu,3),len3);pzoek=s(stu,4);
	  goto fill_tabel;
    }
  }
#if FLAGCOC
	  if(byte=='-'){
			if(stu==6 && fldlen(6,11) && fldlen(6,11)){// zoek op 2-de referentie artikel
				zoekkey=12; zoekwijze=0;
				if(parmcall[4]) zoekkey=parmcall[4];  // artikelreferentie met directe key
				if(faskeyi(6,zoekkey,1)==45){zoekwijze=3;zoekkey=2;}  // artikelreferentie zonder key, alfa overlopen
				else *u(6,1)=0;
				zoeklen=Copy2ZoekStr(&zoek_arg[1],len3-1,fldlen(6,11));
				copy(&zoek_arg[1],s(6,11),zoeklen); pzoek=s(6,11);
				goto fill_tabel;
			}
		}
#endif
	  if(byte=='-'){
			if(stu==1 || stu==2){// zoek toch op naam owv beginnend met cijfer
				zoekkey=2;zoekwijze=0;  // gewoon op naam zoeken 
				goto fill_tabel;
			}
		}
  if(byte=='='){
		if(stu==1 || stu==2 || stu==92){// zoek op straatnaam
			zoekwijze=9;zoekkey=2;// gemeente zonder key, alfa overlopen 
  	  zoeklen=Copy2ZoekStr(&zoek_arg[1],len3-1,fldlen(stu,6));
	    copy(&zoek_arg[1],s(stu,6),zoeklen); 
			zero(s(stu,3),len3); pzoek=s(stu,6);
	    goto fill_tabel;
    }
  }
  if(byte=='#'){// zoek op stuk van de naam
    zoekkey=2;zoekwijze=6;  // alfa overlopen 
    zoeklen=Copy2ZoekStr(&zoek_arg[1],len3-1,len3);
		zero(s(stu,3),len3);pzoek=s(stu,3);
		goto fill_tabel;
  }
  if(byte=='$'){
		if(stu<3){// zoek op btw-nummer
			zoekkey=2;zoekwijze=7;  // alfa overlopen 
			zoekbtwnr=get_btw(&zoek_arg[1]);
			if(zoekbtwnr==0 && errnum==29) goto end;
			zero(s(stu,3),len3);pzoek=s(stu,10);
			goto fill_tabel;
		}
		else if(stu==6){ // zoek op artikelbarcode
			errnum=ZoekArtikelOpBarcode(&zoek_arg[1]); goto end;
		}
		else if(stu==92){ // zoek op barcode/EID
			errnum=ZoekKaartOpBarcode(&zoek_arg[1]); goto end;
		}
	}
fill_tabel:;
  mode_=1;if(!(filtermode_ && *pzoek==0) && (zoekwijze==0 || zoekwijze==4)) mode_=5;last_rec_=*u(stu,1);
  FOREVER{
next:;
		if(recs_used>=MAX_RECS) break;
		if(mode_==5){
			fasinit(stu);*u(stu,1)=last_rec_;
		  copy(zoekstr,pzoek,len3-1); // len3-1 owv dat de faskey niet goed werkt als ge volledige omschrijving intikt (probleem GRB)
		  if(faskeyi(stu,zoekkey,5)) break;	
		}
		else{
			if(faskeyi(stu,zoekkey,mode_)) break; mode_=2;
		}
		last_rec_=*u(stu,1);
		if(filtermode_&& *u(stu,1)<SearchFilterTabelSize && SearchFilterTabel[*u(stu,1)]==0) {filter_used_=YES;goto next;}
		if(stu==3 && (parmcall[7] & 0x04) && *s(3,5)!='J') goto next;// check op boeken toegestaan
		if((stu==2 || stu==6) && (parmcall[7] & 0x08) && !filtermode_ && fldlen(stu,200) && *u(stu,200)) goto next;// check op NIET actief
		if(dsp_mode_==1 && *u(stu,200)) goto next;
		if(dsp_mode_==2 && *u(stu,200)==0) goto next;
		switch(zoekwijze){
			case 1 : if(stu==3){zero(str_,sizeof str_);grb_deco(str_,l(3,2));pzoek=str_;}
						 if(cmpstrU(pzoek,zoekstr,zoeklen)==0){recs[recs_used++]=*pu_s_1;}// stuk codenummer 
					 else goto next; //end_fill_tabel;
						 break;
			case 2 : if(cmpstrU(pzoek,zoekstr,zoeklen)==0){recs[recs_used++]=*pu_s_1;}// artikelreferentie met key
					 else goto end_fill_tabel;
						 break;
			case 3 : if(cmpstrU(pzoek,zoekstr,zoeklen)==0){recs[recs_used++]=*pu_s_1;}// artikelreferentie zonder key
					 else goto next;
						 break;
			case 4 : if(cmpstrU(pzoek,zoekstr,zoeklen)==0){recs[recs_used++]=*pu_s_1;}// straatnaam met key
					 else goto end_fill_tabel;
						 break;
			case 5 : if(cmpstrU(pzoek,zoekstr,zoeklen)==0){recs[recs_used++]=*pu_s_1;}// straatnaam zonder key
					 else goto next;
						 break;
			case 6 : for(j=0;j<len3-zoeklen;j++) if(cmpstrU(ps_s_3+j,&zoekstr,zoeklen)==0) break;// zoek op stuk van naam 
					 if(j>=len3-zoeklen) goto next;
     		   recs[recs_used++]=*pu_s_1;
			   break;
      case 7 : lbd_=*l(stu,10);// zoek op BTW-nummer 
		           if(lbd_==zoekbtwnr) recs[recs_used++]=*pu_s_1;
			         else goto next;
		           break;
			case 9 : if(cmpstrU(pzoek,zoekstr,zoeklen)==0){recs[recs_used++]=*pu_s_1;}// straatnaam zonder key
					     else goto next;
			         break;
      default : recs[recs_used++]=*pu_s_1; break;
		}
  }
end_fill_tabel:;
  if(recs_used==0){errnum=39;goto end;}
  if(recs_used==1){
		if(stu!=6 || !(parmcall[7] & 0x10)){
		  fasinit(stu);*u(stu,1)=recs[0];fasgeti(stu);errnum=0; goto end;
		}
	}

  start_=0; nr_=0; lijnpos=0; scrnum=0;
  FOREVER{
    redo:;
    scrnum=0;scrget(1,96);q_=0;
#if FLAGGBL || FLAGENS
		if(stu==6){
			scraddf(50,2,44,3); scrifld(50,VarTextFmt(6,0),vptekst[0]);
			scraddf(51,2,51,3); scrifld(51,VarTextFmt(6,0),vptekst[1]);
			scraddf(52,2,58,3); scrifld(52,VarTextFmt(6,0),vptekst[4]);
			scraddf(53,2,65,3); scrifld(53,VarTextFmt(6,0),vptekst[5]);
			scraddf(54,2,74,3); scrifld(54,VarTextFmt(4,0),"PlMg");
		}
#endif
#if FLAGOLH
		if(stu==6){
			scraddf(50,2,63,3); scrifld(50,VarTextFmt(10,0),"Kassaprijs");
			scraddf(54,2,74,3); scrifld(54,VarTextFmt(5,0),"Stock");
		}
#endif
    funckeys=0x82E1;
		if(start_>0) {
#if FLAGOLH 
      scraddpicto(1,0,76,0,4,2,18,0,4,"up"); 
#else
      scraddpicto(1,0,76,2,4,2,18,0,4,"up"); 
#endif
      funckeys+=2;
    }
		if((start_+D_LIN_SCR)<recs_used) {
      scraddpicto(2,0,76,21,4,2,13,0,4,"down"); 
      funckeys+=4;
    }
		if(fldlen(stu,200)){
			scraddf(111,22,52,8);
			if(dsp_mode_==0) scrifld(111,VarTextFmt(12,0)," F10 actief ");
			else if(dsp_mode_==1) scrifld(111,VarTextFmt(17,0)," F10 geblokkeerd ");
			else scrifld(111,VarTextFmt(11,0)," F10 allen ");
		}
		scrifld(1,fm_os38,zoek_arg);z=2;
    for(k=start_;k<start_+D_LIN_SCR;k++){
		  if(k>=recs_used) break;
		  fasinit(stu);*pu_s_1=recs[k];fasgeti(stu);
      k++;scrifld(z++,fm_ou4,&k);k--;
			DisplayLine(z++);q_++;
			lijn_attrib_=0xFF;
			if(q_==(lijnpos+1)) lijn_attrib_=0x08;
  		if(stu==2 && *(s(2,3)+fldlen(2,3)-1)=='!' && (q_!=(lijnpos+1))) lijn_attrib_=0x7;
			else if((stu==2  || stu==1) && fldlen(stu,200) && *i(stu,200) && (q_!=(lijnpos+1))) lijn_attrib_=0xB;
			else if(stu==6){
				if(fldlen(6,200) && *i(6,200) && (q_!=(lijnpos+1))) lijn_attrib_=0xB; // 1-ste lijn in het rood, blokkeert pijltjestoetsen 
				else if(sys2993!='J' && fldlen(6,102) && *i(6,102) && (q_!=(lijnpos+1))) lijn_attrib_=0x2; // 0x9; // 1-ste lijn in het rood, blokkeert pijltjestoetsen 
			}
#if FLAGLEA // droogkuisartikels in het groen zetten 
			if(stu==6){
				if(*u(6,9)==5) lijn_attrib_=0x9;
				else if(lijn_attrib_==0x08) lijn_attrib_=0xFF; // geen blauwe lijn
			}
#endif
  		scrchat(z-1,lijn_attrib_); 
    }
    scrifld(36,fm_uu4,&nr_);
    key=scrupd(36,funckeys);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if((key==15 || key==108) && stu==6 && (parmcall[7] & 0x10)) key=107; // ovl214 : enkel bekijken 
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
											 start_-=D_LIN_SCR; if(start_<0) start_=0;lijnpos=0;scrnum=0;
										 }
										 break;
			case 13      :// PgDn 
			case 5002    :
			case 103     : if((start_+D_LIN_SCR)<recs_used) {start_+=D_LIN_SCR;lijnpos=0;scrnum=0;}
										 break;
			case 10      : start_=0;lijnpos=0;scrnum=0;// HOME 
										 break;
			case 11      : start_=recs_used-D_LIN_SCR;if(start_<0) start_=0;// END 
										 lijnpos=0;scrnum=0;
										 break;
			case 101     :
			case 106     : errnum=39;goto end;// annuleer 
										 break;
			case 107     : if(stu>3 && stu!=6) break; // enkel 1,2,3,6 GEEN 92 owv zichzelf oproepen
										 if(nr_>recs_used) errnum=34;// aanpassen fiche 
										 else{
											 if(nr_>0) *pu_s_1=recs[nr_-1];
											 else *pu_s_1=recs[start_+lijnpos];
											 nr_=0; errnum=fasgetu(stu);
											 if(stu==92) ovlcall(294,0); else ovlcall(2900+stu*10+1,0); // 2911 2921 2931 2961 
										}
										break;
			case 18      :// ENTER 
			case 15      : // TAB  
			case 108     : if(nr_>recs_used) errnum=34;// neem aan en exit 
										 else{
											 if(nr_>0) *pu_s_1=recs[nr_-1];
											 else *pu_s_1=recs[start_+lijnpos];
											 nr_=0; errnum=fasgetu(stu);
											 goto end;
										 }
										 break;
			case 110     : dsp_mode_++; if(dsp_mode_>2) dsp_mode_=0; 
				             copy(buf1000_,s(stu,1),fldlen(stu,0)); mode_=ori_mode_;
										 goto full_redo; // 0=alles, 1=geactiveerd, 2=geblokkeerd
			default      : break;
    }
  }
 
end:;
  retval_=NO;
  if(errnum) retval_=YES;
	if(stu==3 && retval_==NO && (parmcall[7] & 0x04) && *s(3,5)!='J'){errnum=24;retval_=YES;}// check op boeken toegestaan
	if((stu==2 || stu==6) && retval_==NO && !filtermode_ && (parmcall[7] & 0x08) && fldlen(stu,200) && *u(stu,200)) {errnum=63;retval_=YES;}// check op NIET actief
  if(retval_){
		fasinit(stu); copy(searbuf,s(stu,2),len2+len3);
		copy(searbuf,SearchText,len2+len3);
		if(filtermode_==NO) SearchText[ADDPOS]=stu;// NIET in filtermode
		else {if(filter_used_) errnum=14;}
  }
  else{
		zero(SearchText,SearchTextSize);
  }
  return retval_;
}


static DisplayLine(z)
int16 z;
{
  char *pd,buf1_[20],buf_[121];
  int16 g,k;
  long lbd_;

  zero(buf_,sizeof buf_);  pd=&buf_[0];
#if FLAGCOC

	if(stu==6 && zoekkey==11 || zoekkey==12){
	  if(len2==0){stcli_d(pd,(long)(*u(stu,1)),5,1);pd+=5;}
	  else copy(s(stu,2),pd,len2);
	  for(g=0;g<len2;g++){if(*pd=='\0') *pd=' ';pd++;}
	  *pd++=' ';
    if(zoekkey==11){
			g=copy0(s(stu,8),pd,fldlen(stu,8));
			for(g=0;g<fldlen(stu,8);g++){if(*pd=='\0') *pd=' ';pd++;}
		}
		else{
			g=copy0(s(stu,11),pd,fldlen(stu,11));
			for(g=0;g<fldlen(stu,11);g++){if(*pd=='\0') *pd=' ';pd++;}
		}
		*pd++=' '; pd+=copy0(s(stu,3),pd,fldlen(6,3));
		//if(fldlen(6,33)){
		//		stcli_d(&buf_[58],(long)(*f(6,33)),5,1);
		//		for(g=58;g>=0;g--) if(buf_[g]=='\0') buf_[g]=' ';
		//}
	}
	else
#endif
  if(zoekwijze==2 || zoekwijze==3){// artikel via referentie leverancier 
		g=copy0(s(stu,8),pd,fldlen(stu,8));
		for(g=0;g<fldlen(stu,8);g++){if(*pd=='\0') *pd=' ';pd++;}
		*pd++=' ';g=copy0(s(stu,2),pd,fldlen(stu,2));
		for(g=0;g<fldlen(stu,2);g++){if(*pd=='\0') *pd=' ';pd++;}
		*pd++=' '; pd+=copy0(s(stu,3),pd,len3);
#if FLAGGBL || FLAGENS
		copy0(s(6,29),&buf_[67],5);
		for(g=67;g>=0;g--) if(buf_[g]=='\0') buf_[g]=' ';
#else
		if(fldlen(6,33)){
				stcli_d(&buf_[67],(long)(*f(6,33)),5,1);
				for(g=67;g>=0;g--) if(buf_[g]=='\0') buf_[g]=' ';
		}
#endif
  }
  else if(zoekwijze==4 || zoekwijze==5){// klant/leverancier via straatnaam  
		g=copy0(s(stu,4),pd,fldlen(stu,4));
		for(g=0;g<fldlen(stu,4);g++){if(*pd=='\0') *pd=' ';pd++;}
		*pd++=' '; pd+=copy0(s(stu,3),pd,len3);
  }
  else if(zoekwijze==7){// zoeken op BTW-nummer 
		zero(buf1_,sizeof buf1_);
		lbd_=*l(stu,10)&0xBFFFFFFF;
		if(lbd_==000000000){} // copy("000.000.000",buf_,11);
			else{
				btw_deco(&buf_[0],(long *)&lbd_,0);
			//stcli_d(&buf1_[0],lbd_,9,0);
			//copy(&buf1_[0],&buf_[0],3);buf_[3]='.';
			//copy(&buf1_[3],&buf_[4],3);buf_[7]='.';
			//copy(&buf1_[6],&buf_[8],3);
		}
		for(g=0;g<12;g++){if(*pd=='\0') *pd=' ';pd++;}
		copy0(s(stu,3),pd,len3);
		for(g=0;g<len3;g++){if(*pd=='\0') *pd=' ';pd++;}
		*pd++=' ';g=copy0(s(stu,6),pd,fldlen(stu,6));
  }
  else if(zoekwijze==9){// klant/leverancier via gemeente  
		g=copy0(s(stu,6),pd,fldlen(stu,6));
		for(g=0;g<fldlen(stu,6);g++){if(*pd=='\0') *pd=' ';pd++;}
		*pd++=' '; pd+=copy0(s(stu,3),pd,len3);
  }
  else { 
		if(stu==3){
			grb_deco(buf_,l(3,2));for(g=0;g<8;g++){if(*pd=='\0') *pd=' ';pd++;}
		}
		else{
				if(len2==0 || stu==52 || stu==92){stcli_d(pd,(long)(*u(stu,1)),5,1);pd+=5;}
				else copy(s(stu,2),pd,len2);
				for(g=0;g<len2;g++){if(*pd=='\0') *pd=' ';pd++;}
		}
    *pd++=' ';
#if FLAGMAE
		if(stu==70){
			g=copy0(s(70,4),pd,fldlen(70,4));
			for(g=0;g<fldlen(70,4);g++){if(*pd=='\0') *pd=' ';pd++;}
			g=copy0(s(70,5),pd,fldlen(70,5));
			for(g=0;g<fldlen(70,5);g++){if(*pd=='\0') *pd=' ';pd++;}
			g=copy0(s(70,6),pd,fldlen(70,6));
		}
#endif
		if(stu==52) g=copy0(s(stu,14),pd,fldlen(52,14)); else	g=copy0(s(stu,3),pd,len3);
		pd+=g;
		if(stu<3 || stu==92){
			if(YES){ // (sear_stt & 1) || stu==92 || zoekwijze==98){
				if(g>=30) *(pd++)='-';
				else{
  				for(g;g<30;g++){if(*pd=='\0') *pd=' ';pd++;}
				}
				pd+=copy0(s(stu,4),pd,fldlen(stu,4));
				*(pd++)='-';
				pd+=copy0(s(stu,6),pd,fldlen(stu,6));
			}
			else{
				for(g;g<len3;g++){if(*pd=='\0') *pd=' ';pd++;}
				*(pd++)=' ';pd+=copy0(s(stu,6),pd,fldlen(stu,6));
			}
		}
		if(stu==6){
#if FLAGOLH
		zero(buf1_,sizeof buf1_);k=Fld2String(6,21,buf1_,15);
		copy(buf1_,&buf_[59+7-k],k);
#endif
			if(fldlen(6,33)){
#if FLAGCRA // totale stock van alle filialen tonen
			fasinit(66);*u(66,2)=*u(6,1); faskeyi(66,1,0);
			for(g=0;g<10;g++) if(fldlen(66,11+g*15)) *f(6,33)+=*f(66,11+g*15);
#endif
				stcli_d(&buf_[67],(long)(*f(6,33)),5,1);
				for(g=67;g>=0;g--) if(buf_[g]=='\0') buf_[g]=' ';
			}
#if FLAGGBL || FLAGENS
    zero(buf_,sizeof buf_);  pd=&buf_[0];
		g=copy0(s(stu,2),pd,fldlen(stu,2));
		for(g=0;g<fldlen(stu,2);g++){if(*pd=='\0') *pd=' ';pd++;}
		*pd++=' '; copy0(s(stu,3),pd,len3); 
		for(g=0;g<len3;g++){if(*pd=='\0') *pd=' ';pd++;}
		zero(buf1_,sizeof buf1_);k=Fld2String(6,21,buf1_,15);
		if(k<7){for(g=k;g<7;g++) *pd++=' ';copy(buf1_,pd,k); pd+=k;}
		else{copy(&buf1_[k-7],pd,7); pd+=7;}
		zero(buf1_,sizeof buf1_);k=Fld2String(6,22,buf1_,15);
		if(k<7){for(g=k;g<7;g++) *pd++=' ';copy(buf1_,pd,k); pd+=k;}
		else{copy(&buf1_[k-7],pd,7); pd+=7;}
		zero(buf1_,sizeof buf1_);k=Fld2String(6,25,buf1_,15);
		if(k<7){for(g=k;g<7;g++) *pd++=' ';copy(buf1_,pd,k); pd+=k;}
		else{copy(&buf1_[k-7],pd,7); pd+=7;}
		zero(buf1_,sizeof buf1_);k=Fld2String(6,26,buf1_,15);
		if(k<7){for(g=k;g<7;g++) *pd++=' ';copy(buf1_,pd,k); pd+=k;}
		else{copy(&buf1_[k-7],pd,7); pd+=7;}

		//*pd++=' '; 
		copy0(s(6,29),&buf_[67],5);
		for(g=67;g>=0;g--) if(buf_[g]=='\0') buf_[g]=' ';
		//if(fldlen(6,33)){
		//		stcli_d(&buf_[67],(long)(*f(6,33)),5,1);
		//		for(g=67;g>=0;g--) if(buf_[g]=='\0') buf_[g]=' ';
		//}


#endif
		}
  }
  scrifld(z,fm_os72,buf_);
}
 
static ZoekArtikelOpBarcode(pzoek_)
char *pzoek_;
{
	fasinit(6);errnum=0;
	if(fldlen(64,0)){
		fasinit(64);copy(pzoek_,s(64,2),fldlen(64,2));
		if(faskeyi(64,1,1)==0){
			if(cmpstr(pzoek_,s(64,2),fldlen(64,2))==0){// gevonden
				fasinit(6);*u(6,1)=*u(64,3);errnum=fasgeti(6);
				goto endsr;
			}
		}
	}
	fasinit(6);
#if FLAGCOC
		fasinit(6);copy(pzoek_,s(6,2),fldlen(6,2));
		if(faskeyi(6,1,0)) {fasinit(6);errnum=39;}
		goto endsr;
#endif

	if(fldlen(6,70)==0){errnum=39;goto endsr;}
	FOREVER{
		if(faskeyi(6,1,2)) break;
		if(cmpstr(pzoek_,s(6,70),fldlen(6,70))==0) goto endsr; // gevonden
		if(fldlen(6,71) && cmpstr(pzoek_,s(6,71),fldlen(6,71))==0) goto endsr; // gevonden
	}
	fasinit(6);errnum=39;
endsr:;
	return errnum;
}

static ZoekKaartOpBarcode(pzoek_)
char *pzoek_;
{
	int16 len_,g;
	char bstr_[10],str_[10];
	long bar_pref; 
	int ValidRR=NO;
	char basebuf[25], modcbuf[5];
	int base,modc;
	
	sysget(4120,4,&bar_pref);  copy("25",bstr_,2); stcli_d(&bstr_[2],(long)bar_pref,5,0);
	fasinit(92);errnum=0;
	for(len_=0;len_<25;len_++) if(*(pzoek_+len_)=='\0') break;
	if(len_<=5) { // kaartnummer van invulformulier
		*u(92,1)=val(pzoek_); 
	}
	else if(len_==13 && cmpstr(pzoek_,bstr_,7)==0){ // EAN13 van kaart
		memset(str_,0,sizeof str_);copy(pzoek_+7,str_,5);
		*u(92,1)=val(str_);
	}
	else if(fldlen(96,0)){ // RR-nr van EID of andere kaart
		fasinit(96);
		if (len_==20) { // indien barcode van eID, dan enkel rijksregister nemen 
			memcpy(basebuf,pzoek_,9); basebuf[9]=0;base=atol(basebuf);
			memcpy(modcbuf,pzoek_+9,2); modcbuf[2]=0; modc=atol(modcbuf);
			if ((base%97+modc)==97) ValidRR=YES;
			else if (((2000000000+base)%97+modc)==97) ValidRR=YES; // voor personen geboren na 1/1/2000
			if (ValidRR) memcpy(s(96,2),pzoek_,11); 
		}
		if(*s(96,2)=='\0') copy(pzoek_,s(96,2),fldlen(96,2));
		g=faskeyi(96,1,0); // naturel
		if(g){EncryptStr(s(96,2),fldlen(96,2));g=faskeyi(96,1,0);}
		if(g==0) *u(92,1)=*u(96,3);
	}
  if(*u(92,1)){if(fasgeti(92)) *u(92,1)=0;}
	if(*u(92,1)==0){fasinit(92);errnum=39;}
	return errnum;
}

static EncryptStr(char *ps_,int maxlen_)
{
	int16 len_,j,k,kar_used_;
	char str_[40],kar_;

	zero(str_,sizeof str_);kar_used_=NO;
	for(len_=0;len_<maxlen_;len_++) {
		kar_=*(ps_+len_);
		if(kar_=='\0') break;
		str_[len_]=kar_;
		if(kar_<'0' || kar_>'9') kar_used_=YES;
	}
	if(len_==0 || len_!=11 || kar_used_) goto endsr; // enkel 11 cijfers encrypteren
	for(k=0;k<11;k++){
		j=(str_[k]-'0')*3; if(k<10) j+=str_[k+1]-'0'; // laatste cijfer enkel *3
		if(j<26) str_[k]='A'+j;
		else if(j<36) str_[k]='0'+j-26;
		else str_[k]='a'+j-36;
	}
	*ps_='X'; copy(str_,ps_+1,11);
	endsr:;
}


static DoWildSearch(dsp_mode_)
int16 dsp_mode_;
{

	char SearchField[200];
  char FullRecDens[3000];
  int k,FullRecDensLen=0,check_actief_,fkey_=2;

  memset(recs,0,sizeof recs);recs_used=0;
	memset(SearchField,0,sizeof SearchField); 
	copy(s(stu,3),SearchField,fldlen(stu,3));
#if FLAGMAE
	if(stu==70){
		memset(SearchField,0,sizeof SearchField); 
	  copy(s(stu,5),SearchField,fldlen(stu,5));
	}
#endif
	if(stu==52){
		for(k=1;k<100;k++){
			fasinit(52);*u(52,1)=k;fasgeti(52);
			if(*s(52,14)) recs[recs_used++]=*u(stu,1);
		}
	}
	else{
		GetSearchKeyWords(SearchField);
		check_actief_=NO; if((stu==2 || stu==6) && (parmcall[7] & 0x08) && fldlen(stu,200)) check_actief_=YES;
#if FLAGMAE
		if(stu==70) fkey_=1;
#endif
		fasinit(stu);
		FOREVER {
			next:;
			if(faskeyi(stu,fkey_,2)) break;
			FullRecDensLen=MakeFullRecDens(stu,FullRecDens);
			if (AllKeywordsFound(FullRecDens,FullRecDensLen)==NO) goto next;// record voldoet
			if(check_actief_==NO || *u(stu,200)==0){  // check op NIET actief
				if(dsp_mode_==1 && *u(stu,200)) goto next;
	      if(dsp_mode_==2 && *u(stu,200)==0) goto next;
			}
	    recs[recs_used++]=*u(stu,1);
			if(recs_used>=MAX_RECS) break; // tabel vol
		}
	}
}

static void GetSearchKeyWords(s)
char* s;
{
  int i, len, keyix;
  char buf[100];

  for (i=0; i<MAX_SEARCH_KEYWORDS; i++) SearchKeywords[i][0]=0; 
  keyix=0;
  while (keyix<MAX_SEARCH_KEYWORDS) {
    while (*s==' ') s++;
    len=0;
    while (*s && *s!=' ') {
      if (len>=sizeof(buf)) return;
      buf[len++]=*s++;
    }
    buf[len++]=0;
    if (len>0) GetSearchText(buf,SearchKeywords[keyix++],len); // om de 0 achteraan toe te voegen !
    if (!*s) break;
  }
}
  
static int GetSearchText(s,d,len)  // analoog aan JMS (composekey)
char *s,*d;
int len;
{
  char c;
  int l=len, outlen=0;

  while (l-->0) {
    if (!*s) break;
	  c=ICSBTab[*(unsigned char *)s++];
  	if (c) {
      *d++=c;
      outlen++;
    }
	}
  if (outlen<len) *d=0;
  return outlen;
}

static int MakeFullRecDens(stunr, FullRecDens)
int stunr;
char* FullRecDens;
{
  unsigned char Desc[100]; // zeker genoeg nemen,
  unsigned char *p=0;
	char  *d,buf750[750];
  int tbnr_,snr_,len, outlen=0, lenadd,fldnr;
  d=FullRecDens;

	for(tbnr_=0;tbnr_<DIM_FICHES;tbnr_++) if(stunr==fichestu[tbnr_]) break; 

  for (snr_=0; snr_<DIM_SITEMS; snr_++) {
		fldnr=SearchFldNrs[tbnr_][snr_];
		if(fldnr==0) continue;
		if(fldnr==1 && fldlen(stunr,2)) continue; // indien code, dan geen recordnummer
    len=fieldspc(stunr,fldnr,&p,Desc);
    if (len==0) continue;
		len=Fld2String(stunr,fldnr,buf750,500);
 		lenadd=GetSearchText(buf750,d,len);
    if (lenadd>0) {
      d+=lenadd;
      *d++=0;
      outlen+=(lenadd+1);
    }
  }
  *d++=0;
  return outlen;
}

static int AllKeywordsFound(FullRecDens, FullRecDensLen)
char* FullRecDens;
int FullRecDensLen;
{
  int i, j, k, KeyWordLen;
  
  for (i=0; i<MAX_SEARCH_KEYWORDS; i++) {
    KeyWordLen=strlen(SearchKeywords[i]);
    if (KeyWordLen==0) continue;
    if (FullRecDensLen<KeyWordLen) return NO;

    for (j=0; j<FullRecDensLen-KeyWordLen; j++) {
      for (k=0; k<KeyWordLen; k++) {
        if (SearchKeywords[i][k]!=FullRecDens[j+k]) break;
      }
      if (k>=KeyWordLen) break;
    }
    if (j>=FullRecDensLen-KeyWordLen) return NO;
  }
  return YES;
}



static copy0(ps,pd,max)
char *ps,*pd;
int16 max;
{
  int16 k;

  for(k=0;*ps && max--;ps++,pd++,k++) *pd=*ps;
  return k;
}
 
static initload()
{
  sysget(1918,2,&sear_stt);
	sysget(2993,1,&sys2993);
  sysget(3876,2,&sys3876);
	sysget(4610,60,vptekst);
	sysget(4740,40,&vptekst[6][0]);
	InitConvertTab();
} 

static void InitConvertTab()  // komt uit JMS
{
  int i;

	for (i=0; i<256; i++) {
		ICSBTab[i]=i;
	}
  ICSBTab[128]='A';
  ICSBTab[129]='A';
  ICSBTab[130]='A';
  ICSBTab[131]='A';
  ICSBTab[132]='C';
  ICSBTab[133]='E';
  ICSBTab[134]='E';
  ICSBTab[135]='E';
  ICSBTab[136]='E';
  ICSBTab[137]='I';
  ICSBTab[138]='I';
  ICSBTab[139]='I';
  ICSBTab[140]='I';
  ICSBTab[141]='O';
  ICSBTab[142]='O';
  ICSBTab[143]='O';
  ICSBTab[144]='O';
  ICSBTab[145]='U';
  ICSBTab[146]='U';
  ICSBTab[147]='U';
  ICSBTab[148]='U';
  ICSBTab[149]='U';
  ICSBTab[159]='E'; // euro teken

  for (i='a'; i<='z'; i++) {
		ICSBTab[i]=i-'a'+'A';
	}

	for (i=' '; i<'0'; i++) ICSBTab[i]=0;
	for (i='9'+1; i<'A'; i++) ICSBTab[i]=0;
	for (i='Z'+1; i<'a'; i++) ICSBTab[i]=0;
	for (i='z'+1; i<128; i++) ICSBTab[i]=0;
  for (i=150; i<255; i++) ICSBTab[i]=0;
}


static bittst(val_,bnr_)
uint16 val_,bnr_;
{
  if(val_ & (1<<bnr_)) return YES;
  else return NO;
}

static Copy2ZoekStr(ps3_,len3_,lenz_)
char *ps3_;
uint16 len3_,lenz_;
{
  uint16 k;
  for(k=0;k<len3_ && k<lenz_;k++){
	if(*(ps3_+k)=='\0') break;
	zoekstr[k]=*(ps3_+k);
  }
  zoekstr[k]='\0';
  return k;
}

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

static long get_btw(ps_)
char *ps_;
{
  int16 j,k;
  char kar_,str_[10];
  long btwnr_=0;

  j=0;k=0;
  FOREVER{
    kar_=*(ps_+k++);
    if(kar_=='\0') break;
    if(kar_>='0' && kar_<='9'){
      btwnr_=btwnr_*10+kar_-'0';
      if(j!=0 || kar_<='1') j++;/* eerste teken mag geen >1  zijn */
    }
    if(j==10) break;
  }
	if(j!=10) {errnum=29;btwnr_=0;}
	if (btwnr_ >= 1000000000L) {
	  btwnr_ -= 1000000000L;copy((char *)&btwnr_,str_,4); str_[3] |= 0x80; copy(str_,&btwnr_,4);
  }
  return btwnr_;
}