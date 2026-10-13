/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* DRK0234GetD() {return &zzvw;}

extern "C" int16 CheckPw(int16 type,int16 nr,int16 aard_);
extern "C" int CopyMoveFile(char *FromFile,char *ToFile,int DeleteOriginal); // kopieren van een file
extern "C" void CnvJamaChar(char *pString,int16 MaxLen,int16 CnvMode);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) ;
extern "C" int ShowSavedDocument(int16 MastStuNr, long MastRecord, int16 SoortDocument, uint16 dat_beg, uint16 dat_end) ;
extern "C" int16 Search(int stu_,int mod_);
extern "C" char *VarTextFmt(int len_,int update_);
extern "C" int DirCall_DRK2215_SelectArtikel(void);


typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;

static int16 ovlcall();
__declspec(dllimport) unsigned char PrintPaperNr;
 
extern "C" char DRK0234dat[] = "drk0234  00:10 07/03/18 (c) Jamadata"; //  herafdrukken facturen/uitschrijven naar ASCII met TAB-delimiters 

       // FLAGDWP EN FLAGLVB : apart AK veld 70 (ipv 41) owv reeds in gebruik
       // FLAGART : 6,8 = code, en kleur=lotnummer 	

#define FOREVER         while(1)
#define YES             1
#define NO              0
#define flag            uint16
#define DIM_TB          200
#define MAXFLD          100
#define DIMBTW          8


extern char *s();
extern int16 *i();
extern uint16 *u();
extern long *l(), val();
extern float *f();
extern double *d();
extern double valu_cnv();
extern int16 retcall,parmcall[8];
extern int16 procid;
extern char info[];

static char fm_os80[]  = {7,0x88,80,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os38[]  = {7,0x88,38,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os25[]  = {7,0x88,25,0,0,0,0};
static char fm_os20[]  = {7,0x88,20,0,0,0,0};
static char fm_os15[]  = {7,0x88,15,0,0,0,0};
static char fm_os13[]  = {7,0x88,13,0,0,0,0};
static char fm_os11[]  = {7,0x88,11,0,0,0,0};
static char fm_os9[]   = {7,0x88,9,0,0,0,0};
static char fm_os5[]   = {7,0x88,5,0,0,0,0};
static char fm_os1[]   = {7,0x88,1,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};
static char fm_us30[]  = {7,0xC8,30,0,0,0,0};
static char fm_us20[]  = {7,0xC8,20,0,0,0,0};
static char fm_us15[]  = {7,0xC8,15,0,0,0,0};
static char fm_us5[]   = {7,0xC8,5,0,0,0,0};
static char fm_u_05[]  = {9,0xC8,1,0,1,0,'0','5',0};
static char fm_ou5[]   = {6,0x90,5,0,0x60,0};
static char fm_ou3[]   = {6,0x90,3,0,0x60,0};
static char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
static char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
static char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
static char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
static char fm_uf8_0[] = {6,0xD4,8,0,0x70,0};
static char fm_uf6_2[] = {6,0xD4,6,2,0x70,0};
static char fm_uf6_0[] = {6,0xD4,6,0,0x70,0};
static char fm_uf5_2[] = {6,0xD4,5,2,0x70,0};
static char fm_uf3_1[] = {6,0xD4,3,1,0x70,0};
static char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
static char fm_od8_2[] = {6,0x95,8,2,0x70,0};
static char fm_ud7_2[] = {6,0xD5,7,2,0x70,0};
static char fm_ud7_0[] = {6,0xD5,7,0,0x70,0};
static char fm_of3_0[] = {6,0x94,3,0,0x60,0};
static char fm_ul7[]   = {6,0xD3,7,0,0x70,0};
static char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
static char fm_uAN[]   = {11,0xC8,1,0,1,0,'A','A','N','N',0};
static char fm_uHV[]   = {11,0xC8,1,0,1,0,'H','H','V','V',0};
static char fm_uDMJ[]  = {13,0xC8,1,0,1,0,'D','D','M','M','J','J',0};
static char fm_uAVW[]  = {11,0xC8,1,0,1,0,'A','A','V','W',0};
static char fm_u_ALN[]= {13,0xC8,1,0,0x09,0,'A','A','L','L','N','N',0};
static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_udat[]  = {4,0xC0,1,'/'};
static char fm_odat[]  = {4,0x80,1,'/'};


/* --------------------------- Declaratie functies ---------------------- */
static int CheckFtFile(char *fname_, uint16 ftdate_, uint16 krec_);
static void _his_upd(uint16 rec_, double *qlv_, double *bd_);
static void _sta_upd(uint16 rec_, float *qlv_, float *bd_, uint16 kol_);
static void art_stat(void);
static void char2str(char *ps_, int16 len_);
static int corr_ft(uint16 ft_nr_, int16 mode_);
static void dump_58(void);
static int dump_ft(void);
static void fact2sif(void);
static void fact2sta(int16 fiche_);
static void fileopen(int16 nr_);
static void flt2str(float bd_);
static int fmt_get(int16 stu_, int16 elet_);
static void historiek_upd(void);
static void initload(void);
static void kil_bkh(void);
static void kil_his(void);
static void kill(void);
static void kill_bkh(void);
static void kill_ft(void);
static void klt_stat(void);
static int ok_kill(void);
static void out_ft(void);
static double round(double value_);
static int scr_ok(char *ptxt);
static int seqi_rec(char *ps_, int16 len_);
static void seqo_fld(int16 stu_, int16 fld_);
static void seqo_flush(void);
static void ShowFailedMails(void);
static void statistiek_upd(void);
static void streepje(int16 nr_);
static void stu_add(int16 stu_, int16 elet_, float *pf1);
static void val2str(int16 mode_);
static void vkp_upd(void);
/* ---------------------------------------------------------------------- */

static int16 stu=6,sfree;
static int16 lvcd,klcd;
static float btw_pct[DIMBTW];


 
/* de variabelen */
static char *p_data;
static long *pl_80_1;

static char seqo_str[1000],kil_ok[10],sel_code[15],sel_detail='H';
static char filnam[40],out_JN[10],fmt[40],buf750[750],ftname[50];
static long seqo_pos,value,seqi_pos;
static int16 seqo_len,seqo_mode,pos,kill_mode,filiaal,fld_AW=41,jaartal;
static uint16 ft_beg,ft_end,journl,last_arc,MinBkhDatum,dt_beg,dt_end,inq_klt,stat_klt,orig_klt;
static double prx_afrond;
static char def_munt[4],ft_munt[4],sortbuf[1000];
static long TbDiversArtikel[10]; // divers artikel per mogelijk BTW%
static float TbBtwPct[8]; 

static int16 len58_15,len58_35,len8_23;
static char *ps_58_16,*ps_8_23,*ps_58_15;
static uint16 *pu_2_1,*pu_6_1,*pu_58_14;
static long *pl_58_32;
static float *pf_58_20,*pf_58_31;
static double *pd_58_35;

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


extern "C" void DRK0234cod(int16 parmval)
{
  int16 curs=1,z,key;
  char choice;
#if FLAGLVB
	fld_AW=70;
#endif
#if FLAGDWP
	fld_AW=70;
#endif

  initload();
  FOREVER{
		redo:;
		scrget(3,1);z=1;fasunlck(0);
		scraddpicto(50,0,76,0,4,2,105,1,7,"^!B0234A");
		if(fldlen(7,1)){
			scraddpicto(1,0,68,21,6,3,559,0,0,"NIET verzonden mails"); 
			scraddpicto(2,0,74,21,6,3,558,0,0,"Verzonden mails"); 
		}
    scrfld(z++,25,1);
    scrifld(z++,fm_menu,&choice);
    key=scrupd(curs,0x0401);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
    if(key==5050) goto redo; // link help 
    if(key==5001){
			ShowFailedMails() ;
      goto redo;
    }
    if(key==5002){
			ShowSavedDocument(2,0,1,0,0) ;
      goto redo;
    }
    if(key==101 || key==111) break;
		fasunlck(-1);
    switch(choice){
      case '1': *u(26,1)=0; ovlexit(257);break; // herafdrukken
      case '2': fact2sif();break;
			case 'C': if(ovltest(2240) && fldlen(4,1)) ovlcall(257,3);break;
      case 'P': if(ovltest(33)) ovlcall(33,2); else errnum=34; 
				        break;
      case 'X': if(CheckPw(1,13,0)) kill_bkh(); break;
      case 'U': if((ovltest(21) || fldlen(4,1)==0) && CheckPw(1,13,0)) kill(); break;
      case 'S': if(fldlen(60,1)) fact2sta(0);break;/* corrigeren statistieken */
      case 'H': if(fldlen(16,1)) fact2sta(1);break;/* corrigeren historieken */
      case 'O': if(fldlen(58,44)) fact2sta(2);break;/* corrigeren omzetfiches */ 
      case 'B': if(fldlen(4,1)) fact2sta(5);break;/* schrappen facturen in boekhouding */
      default : errnum=34; break;
    }
  }
  ovlexit(-1);
}


static void kill_bkh(void)
{
  int16 g,z,key,curs=2;
  uint16 bkh_allow_,dt_beg_,dt_end_;
  long n;
    
  bkh_allow_=YES; dt_beg_=0;dt_end_=0;
  if(fldlen(4,0)==0) bkh_allow_=NO;
  if(ovltest(11)) bkh_allow_=NO;
  if(ovltest(141)) bkh_allow_=NO;
  if(bkh_allow_==NO) goto endsr;
  scraddf(-1,0,0,0);z=1;
  scraddf(z++,4,22,1);
  scraddf(z++,10,7,0); scraddf(z++,10,17,2);
  scraddf(z++,10,27,0); scraddf(z++,10,36,2);
  scraddf(z++,16,7,0); scraddf(z++,16,30,2);
  scraddf(z++,23,1,8);scraddf(z++,23,15,8);
  FOREVER{
    redo:;
    z=1;
    scrifld(z++,fm_os38,"  Wissen verouderde factuur-gegevens");
    scrifld(z++,fm_os63,"Periode : ");
    scrifld(z++,fm_udat,&dt_beg_);
    scrifld(z++,fm_os63,"t.e.m. : ");
    scrifld(z++,fm_udat,&dt_end_);
    scrifld(z++,fm_os63,"Laatste datum gewist : ");
    scrifld(z++,fm_odat,&last_arc);
    scrifld(z++,fm_os13," F1 Stop");scrifld(z++,fm_os13," F8 neem aan");
    key=scrupd(curs,0x81); curs=2;
    if(key==101) goto endsr;
    if(dt_beg_==0) {curs=3; errnum=38;goto redo;}
    if(dt_end_==0) {curs=5;errnum=38;goto redo;}
    if(dt_end_<dt_beg_){curs=5;errnum=33;goto redo;}
    if(key==108) break;
  }
  if(scr_ok("Wenst U echt de verouderde gegevens te schrappen ???")==NO) goto endsr;
  scrget(1,7);scrupd(-3,0);
	fasunlck(-2);
  fasinit(4);
  n=0;scrnum=0;
  FOREVER{
    *l(4,1)=++n;
    g=fasgeti(4);
    if(g==47)break;
    if(g!=46){                                            /* deleted record */
      if((*u(4,4)>=dt_beg_ && *u(4,4)<=dt_end_)) faskill(4);
    }
  }
	fasunlck(-1);
  last_arc=dt_end_; sysput(1858,2,&last_arc);
  fasinfo(4,101);
  endsr:;
}
									

static void fact2sif(void)
{
  int16 z,curs=1,key,mm,dd;
						
  jddate(*u(25,2),&jaartal,&mm,&dd);
  jaartal%=100;
  if(filnam[0]=='\0') copy("FACTUREN.TXT",filnam,13);
  FOREVER{
    redo:;
    scrget(3,2);z=1;
    scrifld(z++,fm_us30,filnam);
    scrifld(z++,fm_uu5,&ft_beg);
    scrifld(z++,fm_uu5,&ft_end);
    scrifld(z++,fm_udat,&dt_beg);
    scrifld(z++,fm_udat,&dt_end);
    fmt_get(58,15);scrifld(z++,fmt,sel_code);
    scrifld(z++,fm_uHV,&sel_detail);
    scrifld(z++,fm_uu2_,&jaartal);
    key=scrupd(curs,0x81); curs=1;
    if(key==101) goto endsr;
    if(ft_beg==0) {errnum=34;curs=2;goto redo;}
    if(ft_end==0) {errnum=34;curs=3;goto redo;}
    if(key==108) break;
  }
  scrget(1,170); z=1;
  scrifld(1,fm_os63,"Uitschrijven gegevens");
  scrifld(5,fm_os63,"Bezig met uitschrijven factuur-gegevens ...  ");
  scrifld(10,fm_os63,"Bezig met factuur : ");
  out_ft();
  endsr:;
}

static void ShowFailedMails(void) 
{
	int16 z,key,j,k,start,max_,mode_,sort_key,curs,mstu_,mbad_,ScreenLines=17,ShowAll=NO;
	long recs_[5000],mrec_;
	char buf_[100],mtype_,bad_code_[100][12],bad_name_[100][25];
	CString cstr_,cmd_;
	char fm_udat[]  = {4,0xC0,1,'/'};
  char fm_uLK[]  = {11,0xC8,1,0,0x09,0,'K','K','L','L',0};

  CString fname_,ft_search_;
	uint16 dat_end=0;
	SYSTEMTIME st_,fsystime_;
	WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
  FILETIME FtimeEnd,loc_ftime_;
	 
	if(fldlen(7,0)==0) {errnum=12; goto endsr;}
	 
	
//	GetLocalTime(&st_);
//	jddate((int)(dat_end),&jj,&mm,&dd);
//	st_.wDay=dd;st_.wMonth=mm;st_.wYear=jj;st_.wHour=17;st_.wMinute=50;SystemTimeToFileTime(&st_,&FtimeEnd);


	redo_full:;
	zero(&bad_name_[0][0],sizeof bad_name_);
	zero(&bad_code_[0][0],sizeof bad_code_);max_=0;mbad_=1;
	ft_search_=CString("..\\Mail\\Failed\\*.*");
	hSearch = FindFirstFile (ft_search_, &FileData);
	FOREVER{

		if (hSearch == INVALID_HANDLE_VALUE) break;
		if ((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) goto nextfile;                      // geen directory 
//			if (CompareFileTime(&FileData.ftLastWriteTime,&FtimeEnd)>0) {goto nextfile;} // na de gewenste periode 
		fname_=CString("..\\Mail\\Failed\\");fname_+=CString(FileData.cFileName);
		cstr_=CString(FileData.cFileName); k=cstr_.Find('.'); if(k!=12 && k!=14) goto nextfile;
		if(k==14) cstr_=cstr_.Mid(2,12);
		fasinit(7);copy((char *)(LPCTSTR)cstr_,s(7,2),12);
		if(faskeyi(7,1,0)==0)	recs_[max_++]=*l(7,1);
		else if(ShowAll && mbad_<100) {copy((char *)(LPCTSTR)cstr_,bad_code_[mbad_],12); 	recs_[max_++]=-mbad_;mbad_++;}
		if(max_>5000) break;
//			remove(fname_);
		nextfile:;
		if(FindNextFile (hSearch, &FileData)==false) break;
	}
	FindClose(hSearch);

	if(max_==0) errnum=39;// goto endsr;}

	start=0;curs=2;
	FOREVER{
		scrnum=0; scrget(3,5);z=1;
		for(j=start;j<start+ScreenLines;j++){
    	if(j>=max_) break;
			fasinit(7);
			if(recs_[j]<=0) {
				copy(bad_code_[-recs_[j]],s(7,17),12);
				mstu_=2;fasinit(2);
			}
			else{
  			fasinit(7); *l(7,1)=recs_[j];fasgeti(7);
				mstu_=*u(7,10);	
				if(mstu_){fasinit(mstu_);*u(mstu_,1)=*l(7,11);fasgeti(mstu_);}
				else {mstu_=2;fasinit(2);}
			}
			scrofld(z++,mstu_,3,33);scrofld(z++,7,4,-1);
			  scraddpicto(1+j-start,z-1,2,0,2,1,570,0,0,"Bekijk mail"); 
				scraddpicto(1+ScreenLines+j-start,z-1,5,0,2,1,569,0,0,"Verstuur mail"); 
			scrofld(z++,7,17,25);

			scraddpicto(1+ScreenLines*2+j-start,z-1,0,0,2,1,540,0,0,"Schrap mail"); 
		}
		key=scrupd(-1,0x207);
		if(key==101) break;
		if(key==110){
			if(ShowAll) ShowAll=NO; else ShowAll=YES;
			goto redo_full;
		}
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5001 && key<5001+ScreenLines){
			zero(buf_,sizeof buf_);
			fasinit(7);	*l(7,1)=recs_[key-5001+start]; 
			if(*l(7,1)>0) fasgeti(7); else copy(bad_code_[-recs_[key-5001+start]],s(7,2),12);
			copy(s(7,2),buf_,12);
			cstr_.Format("GetIniKeyValue|Post-%03d_Settings|DisplayEmailAsEML",ThisPostNr); 
			if(atoi(JmsCmd(cstr_))==1) cmd_= "ViewMail|EML|";  else cmd_= "ViewMail|MSG|";     
			cmd_+=CString(buf_);
			cstr_=JmsCmd(cmd_);
		}
		if(key>=5001+ScreenLines && key<5001+ScreenLines*2){
			z=key-5001-ScreenLines+start;
			fasinit(7);
			if(recs_[z]<=0) {
				copy(bad_code_[-recs_[z]],s(7,17),12); copy(bad_code_[-recs_[z]],s(7,2),12);
			}
			else{
  			fasinit(7); *l(7,1)=recs_[z];fasgeti(7);
			}
			zero(buf_,sizeof buf_);
			cstr_.Format("..\\Mail\\Failed\\%s.EML",s(7,2)); copy((char *)(LPCTSTR)cstr_,buf_,cstr_.GetLength());
			cstr_.Format("..\\Mail\\Outbox\\%s.EML",s(7,2)); copy((char *)(LPCTSTR)cstr_,&buf_[50],cstr_.GetLength());
			CopyMoveFile(buf_,&buf_[50],YES); // kopieren naar outbox
	  	goto redo_full;
		}
		if(key>=5001+ScreenLines*2 && key<5001+ScreenLines*3){
			z=key-5001-ScreenLines*2+start;
			fasinit(7);
			if(recs_[z]<=0) {
				copy(bad_code_[-recs_[z]],s(7,17),12); copy(bad_code_[-recs_[z]],s(7,2),12);
			}
			else{
  			fasinit(7); *l(7,1)=recs_[z];fasgeti(7);
			}
			zero(buf_,sizeof buf_); copy(s(7,17),buf_,fldlen(7,17));
			cstr_.Format("Wenst u echt mail \"%s\" te SCHRAPPEN?",buf_);
			if(DisplayWarning((char *)(LPCTSTR)cstr_,605,1)==YES){
				cstr_.Format("..\\Mail\\Failed\\%s.EML",s(7,2));
				zero(buf_,sizeof buf_); copy((char *)(LPCTSTR)cstr_,buf_,cstr_.GetLength());
	      remove(buf_);
				if(*l(7,1)>0) faskill(7);
		  	goto redo_full;
			}
		}
		if(key==102) start-=18;
		if(key==103) {start+=18;if(start>=max_-18) start=max_-18;}
		if(start<0) start=0;
	}
	endsr:;
}



static void out_ft(void)
{
  int16 k,n;
  uint16 ft_nr,nr_pos_;
							
/* mk_name(3902,"ARTIKEL.TXT"); */
  fasclos(-2);fasunlck(-2);
  errnum=fasopen(filnam,2);if(errnum) goto endsr;
  fasinit(80);seqo_pos=0;seqo_mode=2;
 
  zeros(ftname,sizeof ftname);
  sysget(4704,25,ftname);
  for(k=0;k<25;k++) if(ftname[k]=='\0') break;
  copy(s(25,3),&ftname[k],3); ftname[k+3]='\0';
  for(k=0;k<25;k++) if(ftname[k]=='\0') break;
  nr_pos_=k;

  fasinit(6);
  n=0;
  for(ft_nr=ft_beg;ft_nr<=ft_end;ft_nr++){
    stcli_d(&ftname[nr_pos_],(long)ft_nr,5,0);
    scrifld(11,fm_ou5,&ft_nr);scrupd(-3,0);
    ftname[nr_pos_+5]='.';stcli_d(&ftname[nr_pos_+6],(long)jaartal,2,0);
    ftname[nr_pos_+8]='\0';
    if(fasopen(ftname,1)){
      ftname[nr_pos_+8]='X';
      if(fasopen(ftname,1)) continue;
    }
    dump_ft();
  }
  fasflush(0);
  fasclos(-2);fasunlck(-1);
  endsr:;
}


static void dump_58(void)
{
  int16 k;
 
  zeros(seqo_str,sizeof seqo_str);pos=0;
  seqo_fld(8,2);/* factuurnummer */
  seqo_fld(8,8);/* factuur datum */
  if(fldlen(2,2)) seqo_fld(2,2); else seqo_fld(2,1);/* code klant */
  seqo_fld(2,3);/* naam klant */
  seqo_fld(8,43);/* chauffer code */
  seqo_fld(8,44);/* chauffeur naam */
  seqo_fld(8,45);/* uur vertrek */
  seqo_fld(58,3);/* lijnnummer op factuur */
  seqo_fld(58,14);/* record# artikel */
  seqo_fld(58,15);/* code artikel */
  seqo_fld(58,16);/* omschrijving artikel */
  if(sel_detail=='H'){
    seqo_fld(58,7);/* aantal */
    seqo_fld(58,62);/* Stuk of Pallet */
    seqo_fld(58,12);/* eenheid */
    seqo_fld(58,13);/* gewicht */
    seqo_fld(58,31);/* totaal aantal */
    seqo_fld(58,71);/* lot-nummer */
  }
  else{
    seqo_fld(58,31);/* totaal aantal */
    seqo_fld(58,62);/* Stuk/Pallet */
    seqo_fld(58,12);/* eenheid */
    seqo_fld(58,13);/* gewicht */
    if(fldlen(58,23) && *f(58,23)) seqo_fld(58,23); else seqo_fld(58,20);/* eh.prijs */
    seqo_fld(58,21);/* kort % */
    seqo_fld(58,35);/* totaalbedrag */
    seqo_fld(58,47);/* tot leegg */
    seqo_fld(8,23);/* munt */
    seqo_fld(58,24);/* BTW % */
    if(fldlen(58,26)) seqo_fld(58,26); else seqo_fld(58,25);/* GRB */
    seqo_fld(58,34);/* groep */
    seqo_fld(58,38);/* accijns */
    seqo_fld(58,fld_AW);/* ak-waarde */
    seqo_fld(58,52);/* tot korting */
    seqo_fld(58,53);/* tot semestrieel */
  }
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
}
 

/*
static void scraddf(int16 fld, int16 v, int16 h, int16 attr)
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

*/

static void initload(void)
{

  int16 j,k;
  char *pdum_;
 
  fasunlck(0);
  fileopen(2);
  fileopen(4);
  fileopen(6);
	if(fldlen(7,1)) fileopen(7);
  fileopen(8);
  fileopen(9);
  fileopen(10);
  if(fldlen(66,1)) fileopen(12);
  if(fldlen(16,1)) fileopen(13);
  fileopen(14);
			
  sysget(294,4,def_munt);
	sysget(2900,40,(char *)&TbDiversArtikel[0]);
	sysget(1048,32,(char *)&TbBtwPct[0]); // 8 mogelijke pct
  sysget(1048,32,&btw_pct[0]);
  sysget(1858,2,&last_arc);
  sysget(2300,2,&MinBkhDatum);if(MinBkhDatum<last_arc) MinBkhDatum=last_arc;
  sysget(2166,2,&journl);

  fieldspc(58,20,&pdum_,fmt);
  k=fmt[3];
  prx_afrond=1.; for(j=0;j<k;j++) prx_afrond/=10.;

  pu_2_1=u(2,1);
  pu_6_1=u(6,1);
  ps_8_23=s(8,23); len8_23=fldlen(8,23);
  pu_58_14=u(58,14);
  len58_15=fldlen(58,15);
  ps_58_15=s(58,15);
  ps_58_16=s(58,16);
  pf_58_20=f(58,20);
  pf_58_31=f(58,31);
  pl_58_32=l(58,32);
  len58_35=fldlen(58,35); pd_58_35=d(58,35);

  pl_80_1=l(80,1);
  p_data=s(80,1)+4;

}


static int dump_ft(void)/* inlezen factuur */
{
  int16 j,k,len_,pos_,len1_;
									
  fasinit(80);  seqi_pos=0;
  zeros((char *)&ft_stu.ft_nr,sizeof ft_stu);

  if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)) return YES;
  if(dt_beg && ft_stu.ft_date<dt_beg) return YES;
  if(dt_end && ft_stu.ft_date>dt_end) return YES;
  fasinit(8);
  if(seqi_rec(buf750,ft_stu.stu8len)) return YES;
  pos_=0;
  for(k=0;k<200;k++){
    len_=fldlen(8,k+1);
    len1_=ft_stu.stu8[k][0];
    if(len_){
			if(len1_){
				if(len1_<len_) len_=len1_;
				copy(&buf750[pos_],s(8,k+1),len_); pos_+=len1_;
      }
    } else pos_+=len1_;
  }
  *u(8,2)=ft_stu.ft_nr;*u(8,8)=ft_stu.ft_date;copy(ps_8_23,ft_munt,len8_23);
  *u(2,1)=*u(8,3);fasgeti(2);
  scrofld(15,8,2,-1);scrofld(16,8,8,-1);scrofld(17,2,3,-1);
  for(j=0;j<200;j++){
    fasinit(58);
    if(seqi_rec(buf750,ft_stu.stu58len)) break;
    pos_=0;
    for(k=0;k<200;k++){
      len_=fldlen(58,k+1);
      len1_=ft_stu.stu58[k][0];
      if(len_){
				if(len1_){
					if(len1_<len_) len_=len1_;
					copy(&buf750[pos_],s(58,k+1),len_); pos_+=len1_;
				}
      } else pos_+=len1_;
    }
    if(sel_code[0]=='\0' || cmpstr(ps_58_15,sel_code,len58_15)==0) dump_58();
  }
  endsr:;
  fasflush(0);
  return NO;
}


static void kill(void)
{
  int16 k,curs=3,key,z,mm,dd;
  uint16 ft_nr,dt_ft_;
  char ofname[50],subdir[25];
 
  ft_nr=0;
  jddate(*u(25,2),&jaartal,&mm,&dd);
  sysget(4704,25,subdir); dt_ft_=0;
  jaartal%=100; copy("JJJJJ",kil_ok,5);
  FOREVER{
    redo:;
    scrget(3,3); z=1;
    scrfld(z++,25,1);
    scrifld(z++,fm_uu2_,&jaartal);
    scrifld(z++,fm_uu5,&ft_nr);
		scrifld(z++,fm_udat,&dt_ft_);
    scrifld(z++,fm_os25,subdir);
    for(k=0;k<10;k++){
      switch(k){
				case 0 : if(fldlen(4,0)) scrifld(z++,fm_uJN,&kil_ok[k]);
					 else {kil_ok[k]='N';streepje(z++);}
					 break;
				case 1 : if(fldlen(2,57)) scrifld(z++,fm_uJN,&kil_ok[k]);
					 else {kil_ok[k]='N';streepje(z++);}
					 break;
				case 2 : if(fldlen(6,33) || fldlen(6,57)) scrifld(z++,fm_uJN,&kil_ok[k]);
					 else {kil_ok[k]='N';streepje(z++);}
					 break;
				case 3 : if(fldlen(6,76) && fldlen(58,44) && fldlen(9,27)) scrifld(z++,fm_uJN,&kil_ok[k]);
					 else {kil_ok[k]='N';streepje(z++);}
					 break;
				case 4 : if(fldlen(60,22) || fldlen(16,2)) scrifld(z++,fm_uJN,&kil_ok[k]);
					 else {kil_ok[k]='N';streepje(z++);}
					 break;
				default: break;
      }
    }
    key=scrupd(curs,0x281); curs=3;
		if(key==110) ovlexit(21);
    if(key==101) break;
    zeros(ofname,sizeof ofname); sysget(4704,25,ofname);
    for(k=0;k<25;k++) if(ofname[k]=='\0') break;
    copy(s(25,3),&ofname[k],3);ofname[k+3]='\0';
    for(k=0;k<25;k++) if(ofname[k]=='\0') break;
    stcli_d(&ofname[k],(long)ft_nr,5,0);
    ofname[k+5]='.';stcli_d(&ofname[k+6],(long)jaartal,2,0);
    fasclos(-2);
    ofname[k+8]='\0';
		if(CheckFtFile(ofname,dt_ft_,0)==NO){
			ofname[k+8]='A';
			if(CheckFtFile(ofname,dt_ft_,0)==NO){ errnum=1;goto redo;}
		}

		//if(dt_ft_){
		//	if(CheckFtFile(ofname,dt_ft_,0)==NO){
		//		ofname[k+8]='A';
		//		if(CheckFtFile(ofname,dt_ft_,0)==NO){ errnum=1;goto redo;}
		//	}
		//}
		//else{// er zijn er 2 : men moet een datum ingeven om de juiste te kiezen
		//	ofname[k+8]='A';
		//	if(fasopen(ofname,1)==0){curs=4;errnum=38;goto redo;}
		//}
		if(fasopen(ofname,1)) {
      ofname[k+8]='X';
      if(fasopen(ofname,1)) {errnum=1;goto redo;}
    }
    for(k=0;k<5;k++) if(kil_ok[k]=='J') break;
    if(k>=5){curs=4;errnum=34;goto redo;}
    if(key==108){
			fasunlck(-2);
      if(ok_kill()){
				kill_ft();
				fasclos(-2); fasopen(ofname,99); fasflush(0);
      }
			fasunlck(-1);
    }
  }
  endsr:;
  fasclos(-2);
}


static int CheckFtFile(char *fname_, uint16 ftdate_, uint16 krec_)
{
	short int pos_,k,len_,len1_;


	fasclos(-2);
	if(fasopen(fname_,1)) return NO;
  fasinit(80);zeros((char *)&ft_stu.ft_nr,sizeof ft_stu);seqi_pos=0;
	if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)){fasclos(-2);return NO;}
  if(seqi_rec(sortbuf,ft_stu.stu8len)) {fasclos(-2);return NO;}
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
	  if(*u(8,3)!=krec_) {fasclos(-2);return NO;}
	}
	else if(ftdate_ && ft_stu.ft_date!=ftdate_) {fasclos(-2);return NO;}
	fasclos(-2);
	return YES;
}



static int ok_kill(void)
{
  int16 k,pos_,len1_,len_,key,z;

  fasinit(80);  seqi_pos=0;
  zeros((char *)&ft_stu.ft_nr,sizeof ft_stu);
								
  if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)) return NO;
  fasinit(8);
  if(seqi_rec(buf750,ft_stu.stu8len)) return NO;
  pos_=0;
  for(k=0;k<200;k++){
    len_=fldlen(8,k+1);
    len1_=ft_stu.stu8[k][0];
    if(len_){
      if(len1_){
				if(len1_<len_) len_=len1_;
				copy(&buf750[pos_],s(8,k+1),len_); pos_+=len1_;
      }
    } else pos_+=len1_;
  }
	if(ft_stu.ft_date<=last_arc || ft_stu.ft_date<=MinBkhDatum) {errnum=37;return NO;}
  *u(8,2)=ft_stu.ft_nr;*u(8,8)=ft_stu.ft_date;copy(ps_8_23,ft_munt,len8_23);
  *u(2,1)=*u(8,3);fasgeti(2);
 
  scrget(3,4);z=1;
  scrofld(z++,25,1,-1);
  scrofld(z++,2,3,-1);
  scrofld(z++,8,2,-1);
  scrofld(z++,8,8,-1);
  scrifld(z++,fm_od8_2,&ft_stu.belastbt);
  scrifld(z++,fm_od8_2,&ft_stu.btw_tot);
  scrifld(z++,fm_od8_2,&ft_stu.tot_leeg);
  scrifld(z++,fm_od8_2,&ft_stu.alg_tot);
  key=scrupd(-1,0x19);
  if(key==104) return YES;
  else return NO;
}


static void kill_ft(void)
{
  int16 j,k,pos_,len_,len1_;

  filiaal=0;
	if(fldlen(8,48)) filiaal=*u(8,48);
  else if(fldlen(8,43)) filiaal=*u(8,43);
  if(filiaal<1 || filiaal>10) filiaal=0;
  if(filiaal && fldlen(66,11+(filiaal-1)*15)==0) filiaal=0;

  scrget(1,7);scrupd(-3,0);kill_mode=YES;
  for(j=0;j<200;j++){
    fasinit(58);
    if(seqi_rec(buf750,ft_stu.stu58len)) break;
    pos_=0;
    for(k=0;k<200;k++){
      len_=fldlen(58,k+1);
      len1_=ft_stu.stu58[k][0];
      if(len_){
				if(len1_){
					if(len1_<len_) len_=len1_;
					copy(&buf750[pos_],s(58,k+1),len_); pos_+=len1_;
				}
      } else pos_+=len1_;
    }
    art_stat();/* artikel + omzetfiche */
    statistiek_upd();/* statistieken */
  }
  kil_his();
  klt_stat();
  kil_bkh();
}


static void fact2sta(int16 fiche_)
{
  int16 k,n,z,curs=1,key,mm,dd;
  uint16 ft_nr,nr_pos_;
						
  jddate(*u(25,2),&jaartal,&mm,&dd);
  jaartal%=100;
  kill_mode=NO;fasinit(2);
  FOREVER{
    redo:;
    scraddf(-1,0,0,0);z=1;
    scraddf(z++,4,22,2);
    scraddf(z++,10,7,0); scraddf(z++,10,27,2);
    scraddf(z++,10,33,0); scraddf(z++,10,42,2);
    scraddf(z++,12,7,0); scraddf(z++,12,17,2);
    scraddf(z++,12,26,0); scraddf(z++,12,35,2);
    scraddf(z++,14,7,0); scraddf(z++,14,30,2);
    scraddf(z++,16,7,0); scraddf(z++,16,30,2);
    scraddf(z++,23,1,8);scraddf(z++,23,15,8);
    z=1;
    if(fiche_==0) scrifld(z++,fm_os63,"Corrigeren statistieken");
    else if(fiche_==1) scrifld(z++,fm_os63,"Corrigeren historieken");
		else if(fiche_==5) scrifld(z++,fm_os63,"Schrappen in boekhouding");
    else scrifld(z++,fm_os63,"Corrigeren omzetfiches");
    scrifld(z++,fm_os63,"Van factuurnummer : ");
    scrifld(z++,fm_uu5,&ft_beg);
    scrifld(z++,fm_os63,"t.e.m. : ");
    scrifld(z++,fm_uu5,&ft_end);
    scrifld(z++,fm_os63,"Periode : ");
    scrifld(z++,fm_udat,&dt_beg);
    scrifld(z++,fm_os63,"t.e.m. : ");
    scrifld(z++,fm_udat,&dt_end);
    scrifld(z++,fm_os63,"Jaartal facturen ... : ");
    scrifld(z++,fm_uu2_,&jaartal);
    scrifld(z++,fm_os63,"Selectie 1 klant ... : ");
    scrfld(z++,2,3);
    scrifld(z++,fm_os13," F1 Stop");scrifld(z++,fm_os13," F8 neem aan");
    key=scrupd(curs,0x81); curs=2;
    if(key==101) goto endsr;
    if(ft_beg==0) {errnum=34;curs=3;goto redo;}
    if(ft_end==0) {errnum=34;curs=5;goto redo;}
    if(*s(2,3)) {if(Search(2,0)) goto redo;}
    else fasinit(2);
    inq_klt=*u(2,1);
    if(key==108) break;
  }
  scrget(1,170);z=1;
  if(fiche_==0) scrifld(5,fm_os63,"Corrigeren statistieken");
  else if(fiche_==1) scrifld(5,fm_os63,"Corrigeren historieken");
  else scrifld(5,fm_os63,"Corrigeren omzetfiches");
  scrifld(10,fm_os63,"Bezig met factuur : ");
	scrupd(-3,0);						
  fasclos(-2);
 
  zeros(ftname,sizeof ftname);
  sysget(4704,25,ftname);
  for(k=0;k<25;k++) if(ftname[k]=='\0') break;
  copy(s(25,3),&ftname[k],3); ftname[k+3]='\0';
  for(k=0;k<25;k++) if(ftname[k]=='\0') break;
  nr_pos_=k;
	fasunlck(-2);
  fasinit(6);
  n=0;
  for(ft_nr=ft_beg;ft_nr<=ft_end;ft_nr++){
    stcli_d(&ftname[nr_pos_],(long)ft_nr,5,0);
		if((ft_nr%100)==0){scrifld(11,fm_ou5,&ft_nr);scrupd(-3,0);} // om de 500 facturen
    ftname[nr_pos_+5]='.';stcli_d(&ftname[nr_pos_+6],(long)jaartal,2,0);
    ftname[nr_pos_+8]='\0';
    fasclos(-2); if(fasopen(ftname,1)==0) corr_ft(ft_nr,fiche_);
		fasclos(-2); ftname[nr_pos_+8]='A'; if(fasopen(ftname,1)==0) corr_ft(ft_nr,fiche_);
		fasclos(-2); ftname[nr_pos_+8]='X';if(fasopen(ftname,1)==0) corr_ft(ft_nr,fiche_);
  }
  fasflush(0);
  fasclos(-2);
	fasunlck(-1);
  endsr:;
}


static int corr_ft(uint16 ft_nr_, int16 mode_)/* 0=statistiek 1=historiek 2=vkp+art , 5=factuur schrappen in bkh */
{
  int16 j,k,len_,pos_,len1_,mode16_;
									
  fasinit(80);  seqi_pos=0;
  zeros((char *)&ft_stu.ft_nr,sizeof ft_stu);

  if(seqi_rec((char *)&ft_stu.ft_nr,sizeof ft_stu)) return YES;
  if(ft_nr_!=ft_stu.ft_nr || ft_stu.stu8len>600) return NO;
  if(dt_beg && ft_stu.ft_date<dt_beg) return NO;
  if(dt_end && ft_stu.ft_date>dt_end) return NO;
	if(mode_==5){ // schrappen factuur in bkh
		kil_ok[0]='J';
		kil_bkh();
		return NO;
	}
  fasinit(8);
  if(seqi_rec(buf750,ft_stu.stu8len)) return YES;
  pos_=0;
  for(k=0;k<200;k++){
    len_=fldlen(8,k+1);
    len1_=ft_stu.stu8[k][0];
    if(len_){
      if(len1_){
				if(len1_<len_) len_=len1_;
				copy(&buf750[pos_],s(8,k+1),len_); pos_+=len1_;
      }
    } else if(len1_) pos_+=len1_;
  }
  *u(8,2)=ft_stu.ft_nr;*u(8,8)=ft_stu.ft_date;copy(ps_8_23,ft_munt,len8_23);
	if(*u(8,3)==0 || ft_nr_!=ft_stu.ft_nr){
		goto endsr; // slechte factuur
	}
	orig_klt=0;
	if(mode_==1 && fldlen(16,12)){ // bij historieken ook lev-record invullen 
		fasinit(2);
	  bcopy(s(8,14),s(2,3),fldlen(8,14));
	  bcopy(s(8,15),s(2,4),fldlen(8,15));
	  if(faskeyi(2,2,0)==0) orig_klt=*u(2,1); // recordnummer van leveradres zetten 
	}
	fasinit(2); if(*u(8,3)) *u(2,1)=*u(8,3);
	if(*u(2,1)==0 || fasgeti(2)){
		return NO;
	}
  if(inq_klt && *u(2,1)!=inq_klt) return NO;/* overslaan */
	stat_klt=*u(2,1);
	if(fldlen(2,52)==2 && *u(2,52)) {stat_klt=*u(2,52); orig_klt=*u(2,1);}

#if FLAGALB 
		if(*s(2,52)=='J') stat_klt=orig_klt; // afhankelijk per klant, PAS OP : relatieadres hiervoor gebruikt!
#endif

  scrofld(15,8,2,-1);scrofld(16,8,8,-1);scrofld(17,2,3,-1);
 
  if(mode_==1){/* bij historiek eerst oude factuur deleten */
    fasinit(16);
    *l(16,2)=*u(8,2);
    *u(16,3)=*u(8,8);mode16_=1;
    FOREVER{
      if(faskeyi(16,3,mode16_)) break; mode16_=2;
      if(*l(16,2)!=*u(8,2)) break;
      if(*u(16,3)!=*u(8,8)) break;
      faskill(16);
    }
  }

  for(j=0;j<1500;j++){
    fasinit(58);
    if(seqi_rec(buf750,ft_stu.stu58len)) break;
    pos_=0;
    for(k=0;k<200;k++){
      len_=fldlen(58,k+1);
      len1_=ft_stu.stu58[k][0];
      if(len_){
				if(len1_){
					if(len1_<len_) len_=len1_;
					copy(&buf750[pos_],s(58,k+1),len_); pos_+=len1_;
				}
      } else if(len1_) pos_+=len1_;
    }
    if(mode_==0) statistiek_upd();/* statistieken */
    if(mode_==1) historiek_upd();/* historiek */
    if(mode_==2) vkp_upd();/* omzet + artikel */
  }
  endsr:;
  fasflush(0);
  return NO;
}


static void vkp_upd(void)
{
  int16 j,g;
  float belastbf=0,echt_gel_=0,accijn_=0,f_;
	
  stat_klt=*pu_2_1;

  if(*ps_58_16!='*' && *pu_58_14){
    *pu_6_1=*pu_58_14;
    if(fasgetu(6)==0){
      if(*is(58,34)!=99){
				belastbf=*pd_58_35;
      }
      else belastbf=*f(58,47);
      f_=*pf_58_31;
      if(fldlen(58,62)) if(*s(58,62)=='S') f_/=*f(58,63);
      echt_gel_=-f_;
      stu_add(6,33,&echt_gel_);
      if(fldlen(6,48)) *u(6,48)=*u(8,8);
      stu_add(6,57,&f_);
      stu_add(6,58,&belastbf);
      stu_add(6,59,&f_);
      stu_add(6,60,&belastbf);
upd_6:;
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
      fasupd(6);
			if(*is(58,34)!=99) {stu_add(2,57,&belastbf);fasupd(2);}
    }
    if(fldlen(58,44)){
      if(*i(6,9)!=99 /* *s(58,44)=='J'*/){
				fasinit(9);
				*u(9,2)=stat_klt;
				*u(9,3)=*pu_6_1;
				if(faskeyi(9,1,0)) fasadd(9);
				echt_gel_=-echt_gel_;
				if(YES /* *s(58,44)=='J'*/){
					j=0;if(echt_gel_<0) j+=8;
					accijn_=*f(58,38)*echt_gel_;
					belastbf-=accijn_;
					for(g=0;g<=4;g+=4){
						stu_add(9,27+j+g,&echt_gel_);
						stu_add(9,28+j+g,&belastbf);
						if(fldlen(9,29+j+g)) stu_add(9,29+j+g,&accijn_);
						f_=*f(58,52);
						stu_add(9,47+j+g,&f_);
						f_=*f(58,53);
						stu_add(9,48+j+g,&f_);
					}
				}
				if(fldlen(9,43) && YES /* *s(58,44)=='J'*/ ){
					stu_add(9,43,&echt_gel_);
				}
				fasupd(9);
	no_omzet:;
      }
    }
    if(NO /* fldlen(58,48) && *u(58,48) && *pu_58_14!=*u(58,48)*/){ // geen leeggoed
      fasinit(6);*pu_6_1=*u(58,48);fasgeti(6);
      echt_gel_=-(*f(58,49) * *pf_58_31);
      f_=*f(58,47);
  // NIET VAN VOLGOED     stu_add(6,33,&echt_gel_);
      if(fldlen(6,48)) *u(6,48)=*u(8,8);
      echt_gel_=-echt_gel_;
      stu_add(6,57,&echt_gel_);
      stu_add(6,58,&f_);
      stu_add(6,59,&echt_gel_);
      stu_add(6,60,&f_);
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
      fasupd(6);

      if(fldlen(58,44) && fldlen(6,76)){
				if(YES /* *s(6,76)=='J' */){
					fasinit(9);
					*u(9,2)=stat_klt;
					*u(9,3)=*pu_6_1;
					if(faskeyi(9,1,0)) fasadd(9);
					echt_gel_=*f(58,49) * *pf_58_31;
					if(*s(6,76)=='J'){
						j=0;if(echt_gel_<0) j+=8;
						belastbf=*f(58,47);
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
 

static void art_stat(void)
{
  int16 j,g,clip_=NO;
  float belastbf,echt_gel_,accijn_=0,f_;
  float q_,stockqlv_;
	uint16 arec_;
	
  if(kil_ok[2]!='J' && kil_ok[3]!='J') goto endsr;
  if(*s(58,16)=='*' || *u(58,14)==0) goto endsr;
  *pu_6_1=*pu_58_14; if(fasgetu(6)) goto endsr;

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

  if(*is(58,34)!=99){
    if(len58_35) belastbf=*pd_58_35; else belastbf=*pl_58_32;
  }
  else belastbf=*f(58,47);
  belastbf=valu_cnv(ft_munt,def_munt,(double)belastbf,prx_afrond);
  echt_gel_=*pf_58_31;
  if(fldlen(58,62)) if(*s(58,62)=='S' && *f(58,63)) echt_gel_/=*f(58,63);
	echt_gel_*=stockqlv_; // in verhouding tot hoofdartikel
  echt_gel_=-echt_gel_; belastbf=-belastbf;
  if(kil_ok[2]=='J'){
    if(filiaal){/* stock op filiaal */
      fasinit(66);*u(66,2)=*u(6,1);g=faskeyi(66,1,0);
      if(g){fasinit(66);*u(66,2)=*u(6,1);errnum=fasadd(66);}
      f_=-echt_gel_;
      stu_add(66,11+(filiaal-1)*15,&f_);/* stock */
      stu_add(66,17+(filiaal-1)*15,&echt_gel_);
      if(*u(66,1)) fasupd(66); else fasadd(66);
    }
    else{
      f_=-echt_gel_;
      stu_add(6,33,&f_);
      stu_add(6,57,&echt_gel_);
      stu_add(6,58,&belastbf);
      stu_add(6,59,&echt_gel_);
      stu_add(6,60,&belastbf);
			if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
      fasupd(6);
    }
  }
  if(*s(58,44)=='J' && kil_ok[3]=='J'){
    fasinit(9);
    *u(9,2)=*u(2,1);
    *u(9,3)=*u(6,1);
    if(faskeyi(9,1,0)==0){
      j=0;if(echt_gel_>0) j+=8;
      accijn_=*f(58,38)*echt_gel_;
      accijn_=valu_cnv(ft_munt,def_munt,(double)accijn_,prx_afrond);
      belastbf-=accijn_;
      for(g=0;g<=4;g+=4){
				stu_add(9,27+j+g,&echt_gel_);
				stu_add(9,28+j+g,&belastbf);
				if(fldlen(9,29+j+g)) stu_add(9,29+j+g,&accijn_);
				f_=-valu_cnv(ft_munt,def_munt,(double)*f(58,52),prx_afrond);
				stu_add(9,47+j+g,&f_);
				f_=-valu_cnv(ft_munt,def_munt,(double)*f(58,53),prx_afrond);
				stu_add(9,48+j+g,&f_);
      }
      fasupd(9);
    }
  }
  if(fldlen(58,48) && *u(58,48) && *pu_58_14!=*u(58,48)){
    fasinit(6);*pu_6_1=*u(58,48);fasgeti(6);
    echt_gel_=(*f(58,49) * *pf_58_31);
    belastbf=valu_cnv(ft_munt,def_munt,(double)*f(58,47),prx_afrond);
    belastbf=-belastbf;echt_gel_=-echt_gel_;
    if(kil_ok[2]=='J'){
      if(filiaal){/* stock op filiaal */
				fasinit(66);*u(66,2)=*u(6,1);g=faskeyi(66,1,0);
				if(g){fasinit(66);*u(66,2)=*u(6,1);errnum=fasadd(66);}
				f_=-echt_gel_;
				stu_add(66,11+(filiaal-1)*15,&f_);/* stock */
				stu_add(66,17+(filiaal-1)*15,&echt_gel_);
				if(*u(66,1)) fasupd(66); else fasadd(66);
      }
      else{
				f_=-echt_gel_;
	// NIET bij volgoed 			stu_add(6,33,&f_);
				stu_add(6,57,&echt_gel_);
				stu_add(6,58,&belastbf);
				stu_add(6,59,&echt_gel_);
				stu_add(6,60,&belastbf);
				if(fldlen(6,199)) *u(6,199)=*u(25,2); // datum laatste update
				fasupd(6);
      }
    }
    if(kil_ok[3]=='J' && *s(6,76)=='J'){
      fasinit(9);
      *u(9,2)=*u(2,1);
      *u(9,3)=*pu_6_1;
      if(faskeyi(9,1,0)==0){
				j=0;if(echt_gel_>0) j+=8;
				for(g=0;g<=4;g+=4){
					stu_add(9,27+j+g,&echt_gel_);
					stu_add(9,28+j+g,&belastbf);
				}
				fasupd(9);
      }
    }
  }
  endsr:;
}


static void klt_stat(void)
{
  float belastbf;

  if(kil_ok[1]!='J') goto endsr;
  belastbf=valu_cnv(ft_munt,def_munt,(double)ft_stu.belastbt,prx_afrond);
  belastbf=-belastbf;
  stu_add(2,57,&belastbf);
  stu_add(2,58,&belastbf);
  fasupd(2);
  endsr:;
}


static void historiek_upd(void)
{
  short int k;
	double bd_,qlv_;

//	stat_klt=*pu_2_1;
/* historiek */

	if((*pu_58_14==0 || *ps_58_16=='*') && (*pd_58_35 || *f(58,47))){// op divers artikel zetten 
		if(*is(58,34)==99){ 
			*pu_58_14=TbDiversArtikel[9];*u(58,48)=TbDiversArtikel[9];} // leeggoed divers
		else {
			for(k=0;k<8;k++) if(*f(58,24)==TbBtwPct[k]) break;
			if(k<8) *pu_58_14=TbDiversArtikel[k];
		}
		if(*pu_58_14 && *ps_58_16=='*') *ps_58_16='#';
	}
	if(fldlen(58,48) && *u(58,48)==0 && *f(58,47)) *u(58,48)=TbDiversArtikel[9];
#if FLAGGOU
  if(*pu_58_14 && *ps_58_16!='*' && (*pf_58_31 || *f(58,13))){/* artikel */
#else
	if(*pu_58_14 && *ps_58_16!='*' && *pf_58_31){/* artikel */
#endif
    if(*is(58,34)!=99) bd_=*pd_58_35; else bd_=*f(58,47);
    bd_=round((double)bd_);
#if FLAGGOU
		qlv_=*f(58,7);
#else
    qlv_=*pf_58_31;if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
#endif
    _his_upd(*pu_58_14,&qlv_,&bd_);
  }
  if(fldlen(58,48) && *u(58,48) && *pu_58_14!=*u(58,48)){/* leeggoed */
    qlv_=*f(58,49)* *pf_58_31;
    bd_=round((double)*f(58,47));
    _his_upd(*u(58,48),&qlv_,&bd_);
  }
  if(fldlen(58,57) && *u(58,57)){/* afhaalvergoeding */
    bd_=round((double)*f(58,56));
    qlv_=*pf_58_31;if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
    _his_upd(*u(58,57),&qlv_,&bd_);
  }
  if(fldlen(58,60) && *u(58,60)){/* losvergoeding */
    bd_=round((double)*f(58,59));
    qlv_=*pf_58_31;if(fldlen(58,62)) if(*s(58,62)=='S') qlv_/=*f(58,63);
    _his_upd(*u(58,60),&qlv_,&bd_);
  }
  endsr:;
}


static void _his_upd(uint16 rec_, double *qlv_, double *bd_)
{
  int16 add_rec_=YES,mode_;
									
  fasinit(6);*pu_6_1=rec_;fasgeti(6);
  if(*is(6,9)==99){               /* leeggoed altijd probren samen te tellen */
    fasinit(16);
    *l(16,10)=stat_klt;
		if(fldlen(16,12)) *l(16,12)=orig_klt;
    *l(16,20)=*pu_6_1;
    *u(16,3)=ft_stu.ft_date;
    mode_=1;
    FOREVER{
      if(faskeyi(16,1,mode_)) break; mode_=2;
      if(*l(16,10)!=stat_klt) break;
      if(*l(16,20)!=*pu_6_1) break;
      if(*u(16,3)!=ft_stu.ft_date) break;
      if(*l(16,2)==ft_stu.ft_nr){add_rec_=NO;break;}
    }
  }
  if(add_rec_) fasinit(16);

  *l(16,2)=ft_stu.ft_nr;
  *u(16,3)=ft_stu.ft_date;
  copy(s(8,25),s(16,4),fldlen(16,4));
	if(fldlen(8,48) && fldlen(16,8)) *u(16,8)=*u(8,48); // filiaalnr
  *l(16,10)=stat_klt;
	if(fldlen(16,12)) *l(16,12)=orig_klt;
  if(fldlen(2,28) && fldlen(16,13)) copy(s(2,28),s(16,13),fldlen(2,28)); // vertegenwoordiger
  *l(16,20)=*pu_6_1;
#if FLAGART
	copy(s(6,8),s(16,21),fldlen(16,21)); // SPECIFIEK 
  copy(s(58,15),s(16,40),fldlen(16,40)); // SPECIFIEK KLEUR
#else
  copy(s(6,2),s(16,21),fldlen(16,21));
#endif
  copy(s(6,3),s(16,22),fldlen(16,22));
  *l(16,23)=*u(6,9);
  *f(16,24)=*f(6,28);/* standaard BTW% */
  copy(s(6,10),s(16,25),fldlen(16,25));
  if(rec_==*pu_58_14){
    *f(16,24)=*f(58,24);/* echt BTW% */
    if(fldlen(58,63)) *f(16,26)=*f(58,63);/* q_bak */
    if(fldlen(58,38)) *f(16,27)=*f(58,38);/* accijns */
  }
  *d(16,30)+=*qlv_;
  *d(16,31)+=*bd_;
	if(fldlen(58,41) && *f(58,41)) *d(16,32)+=round((double)(*qlv_* *f(58,41)));
	else *d(16,32)+=round((double)(*qlv_* *f(6,18)));
  if(rec_==*pu_58_14){/* ENKEL op origineel artikel */
    if(fldlen(58,52)) *d(16,33)+=round((double)*f(58,52));
    if(fldlen(58,53)) *d(16,34)+=round((double)*f(58,53));
    if(fldlen(58,97)) *d(16,35)+=round((double)*f(58,97));
  }
	if(fldlen(8,74) && fldlen(16,39)) *s(16,39)=*s(8,74); // om aan te duiden dat het van de kassa komt
#if FLAGGOU
	copy(s(2,29),s(16,13),fldlen(16,13)); // GOU
  if(rec_==*pu_58_14){
		copy(s(58,71),s(16,40),fldlen(16,40)); // lotnr
		*d(16,29)=*f(58,13); // gewicht
		*d(16,35)= *qlv_ * *f(6,68); // GOU PROMO-punten
  }
	if(*d(16,29)) *d(16,32)=round((double)(*d(16,29)* *f(6,18))); // GOU gew x ap
	else *d(16,32)=round((double)(*qlv_* *f(6,18))); // GOU 
#endif
  if(add_rec_) errnum=fasadd(16);
  else errnum=fasupd(16);
 
  endsr:;
}


static void statistiek_upd(void)
{
  int16 dd=0,mm=0,jj=0,off_=0;
  float bd_,bd1_;

  if(kill_mode && kil_ok[4]!='J') goto endsr;
  if(fldlen(60,1)==0) goto endsr;
  jddate(ft_stu.ft_date,&jj,&mm,&dd);mm--;
  if(*pu_58_14 && *ps_58_16!='*'){/* artikel */
    if(*is(58,34)!=99){
      bd_=*pd_58_35;
    }
    else bd_=*f(58,47);
    bd_=valu_cnv(ft_munt,def_munt,(double)bd_,prx_afrond);
    bd1_=*pf_58_31;if(fldlen(58,62)) if(*s(58,62)=='S') bd1_/=*f(58,63);
    if(kill_mode){bd1_=-bd1_;bd_=-bd_;}
    _sta_upd(*pu_58_14,&bd1_,&bd_,mm+off_);
  }
  if(fldlen(58,48) && *u(58,48) && *pu_58_14!=*u(58,48)){/* leeggoed */
    bd1_=*f(58,49)* *pf_58_31;
    bd_=valu_cnv(ft_munt,def_munt,(double)*f(58,47),prx_afrond);
    if(kill_mode){bd1_=-bd1_;bd_=-bd_;}
    _sta_upd(*u(58,48),&bd1_,&bd_,mm+off_);
  }
  if(fldlen(58,57) && *u(58,57)){/* afhaalvergoeding */
    bd_=valu_cnv(ft_munt,def_munt,(double)*f(58,56),prx_afrond);
    bd1_=*pf_58_31;if(fldlen(58,62)) if(*s(58,62)=='S') bd1_/=*f(58,63);
    if(kill_mode){bd1_=-bd1_;bd_=-bd_;}
    _sta_upd(*u(58,57),&bd1_,&bd_,mm+off_);
  }
  if(fldlen(58,60) && *u(58,60)){/* losvergoeding */
    bd_=valu_cnv(ft_munt,def_munt,(double)*f(58,59),prx_afrond);
    bd1_=*pf_58_31;if(fldlen(58,62)) if(*s(58,62)=='S') bd1_/=*f(58,63);
    if(kill_mode){bd1_=-bd1_;bd_=-bd_;}
    _sta_upd(*u(58,60),&bd1_,&bd_,mm+off_);
  }
  endsr:;
}


static void _sta_upd(uint16 rec_, float *qlv_, float *bd_, uint16 kol_)
{
  flag add_rec_;
  float bda_;

  fasinit(6);*pu_6_1=rec_;fasgeti(6);
/*  if(fldlen(6,76) && *s(6,76)!='J') goto endsr; */
  fasinit(60);*l(60,22)=rec_;*l(60,2)=*u(2,1);
  if(fldlen(2,28) && fldlen(60,4)) copy(s(2,28),s(60,4),fldlen(2,28));
  if(faskeyu(60,1,0)){
    if(kill_mode) goto endsr;
    else add_rec_=YES;
  }
  else add_rec_=NO;
  if(fldlen(60,3)) *s(60,3)=*s(2,26);
  if(fldlen(60,24)) *is(60,24)=*is(6,9);
  if(fldlen(60,25)) *u(60,25)=*u(6,7);
  copy(s(6,2),s(60,23),fldlen(6,2));
  bda_=*qlv_* *f(6,18);
  stu_add(60,52+kol_,&bda_);/* ak-waarde */
  stu_add(60,82+kol_,bd_);/* vk-waarde */
  stu_add(60,112+kol_,qlv_);/* aantal */
  if(rec_==*pu_58_14){/* ENKEL op origineel artikel */
    bda_=valu_cnv(ft_munt,def_munt,(double)*f(58,53),prx_afrond);
    if(kill_mode) bda_=-bda_;
    stu_add(60,142+kol_,&bda_);/* sem. korting */
    if(fldlen(58,52)){
      bda_=valu_cnv(ft_munt,def_munt,(double)*f(58,52),prx_afrond);
      if(kill_mode) bda_=-bda_;
      stu_add(60,172+kol_,&bda_);/* directe korting */
    }
    if(fldlen(58,97)){
      bda_=valu_cnv(ft_munt,def_munt,(double)*f(58,97),prx_afrond);
      if(kill_mode) bda_=-bda_;
      stu_add(60,202+kol_,&bda_);/* tussenkomst brouwerij  */
    }
    if(*qlv_ && *bd_==0){
      stu_add(60,232+kol_,qlv_);/* gratis artikels   */
    }
  }
  if(add_rec_) errnum=fasadd(60);
  else errnum=fasupd(60);
  endsr:;
}


static void kil_bkh(void)
{
  int16 mode_;
						
  if(kil_ok[0]!='J') goto endsr;
  fasinit(4);
  *s(4,2)=journl;
  *u(4,3)=ft_stu.ft_nr;
  mode_=1;
  FOREVER{
    next:;
    if(faskeyu(4,1,mode_)) break; mode_=2;
    if(*s(4,2)!=journl || *u(4,3)!=ft_stu.ft_nr) break;
    if(*u(4,4)!=ft_stu.ft_date) goto next;
    faskill(4);
  }
  endsr:;
}


static void kil_his(void)
{
  int16 mode_;
							
  if(fldlen(16,1)==0 || kil_ok[4]!='J') goto endsr;
  fasinit(16);
  *l(16,2)=ft_stu.ft_nr;
  *u(16,3)=ft_stu.ft_date;
  mode_=1;
  FOREVER{
    next:;
    if(faskeyu(16,3,mode_)) break; mode_=2;
    if(*l(16,2)!=ft_stu.ft_nr) break;
    if(*u(16,3)!=ft_stu.ft_date) break;
    faskill(16);
  }
  endsr:;
}


static void stu_add(int16 stu_, int16 elet_, float *pf1)
{
  if(fldlen(stu_,elet_)){
    *f(stu_,elet_)+=*pf1;
  }
}
 

static int seqi_rec(char *ps_, int16 len_)
{
  int16 k,slen_;
				
  slen_=0;
  for(k=0;k<len_;k+=280){
    if((k+280)>len_) slen_=len_-k;
    else slen_=280;
    *l(80,1)=seqi_pos;
    if(fasseqi(80,1,slen_+4)) break;
    seqi_pos=*l(80,1);
    copy(s(80,1)+4,ps_+k,slen_);
  }
  if(k<len_) return YES;
  else return NO;
}
	

static void seqo_fld(int16 stu_, int16 fld_)
{
  int16 yy,mm,dd;
  float fbd_;
  char str_[15];
 
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
    fbd_=*is(stu_,fld_);
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
    zeros(str_,sizeof str_);
    grb_deco(str_,l(stu_,fld_));
    char2str(str_,10);
  }
  endsr:;
}


static void char2str(char *ps_, int16 len_)
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


static void flt2str(float bd_)
{
  double bedrag_,add_=0;
  long val_;
								
  bedrag_=bd_;if(bedrag_<0) add_=-.5; else add_=.5;
  val_=bedrag_*100+add_;value=val_/100;
	if(bd_<0 && value==0) seqo_str[pos++]='-'; // probleem teken bij 0,xxx
  val2str(0);
  value=val_-value*100;
  if(value){
    seqo_str[pos++]=',';
    if(value<0) value=-value;val2str(1);
  }
}


static void val2str(int16 mode_)
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
 

static void seqo_flush(void)
{
  if(seqo_len){
    *l(80,1)=seqo_pos;
    fasseqo(80,seqo_mode,seqo_len+4);
    seqo_pos+=seqo_len;
    seqo_len=0;
  }
}
 

static int fmt_get(int16 stu_, int16 elet_)
{
  int16 k;
  char *pdum,dummy_[10];
					
  pdum=&dummy_[0];
  k=fieldspc(stu_,elet_,&pdum,fmt);
  if(k>0) return k;
  return 0;
}
 

static void fileopen(int16 nr_)
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
 

static void streepje(int16 nr_)
{
  scrifld(nr_,fm_os1,"-");
}
 

static int scr_ok(char *ptxt)
{
  int16 key;

  scrget(1,169);
  scrifld(12,fm_os63,ptxt);
  key=scrupd(-1,0x18);
  if(key==104){scrget(1,7);scrupd(-3,0);return YES;}
  return NO;
}
 

static double round(double value_)
{
  double bd_;
							
  bd_=valu_cnv("EUR","EUR",value_,(double)(0.01));
  return (double)(bd_);
}



 
