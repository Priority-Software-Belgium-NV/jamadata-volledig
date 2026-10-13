/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
#include "locale.h"
extern "C" char* BKH0009GetD() {return &zzvw;}
extern "C" int16 CheckPw(int16 type,int16 nr,int16 aard_);
extern "C" void CnvJamaChar(char *pString,int16 MaxLen,int16 CnvMode);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama
extern "C" int DisplayWarning(char *ptxt, int icoon,int mode); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
extern "C" int IbanTools(char *pIBAN,char *pBIC,char *pJamaRek,int16 ToolNr); // 0 = check iban/bic, 1=check+fill bic, 2=convert jamarek -> IBAN/BIC


typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();
extern "C" char BKH0009dat[] = "bkh0009  00:19 28/02/11 (c) Jamadata";


#define FOREVER         while(1)
#define YES             1
#define NO              0

extern int16 procid;
//extern int16 jamin1[];
extern int16 prc_num[];
extern char RamBon[];

extern char *s();
extern uint16 *u();
extern long *l();
static long makegrb();
extern double *d();

static char fm_os60[]  = {7,0x88,60,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_os3[]   = {7,0x88,3,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_us80[]  = {7,0xC8,80,0,0,0,0};
static char fm_ou4[]   = {6,0x90,4,0,0x60,0};
static char fm_uu4[]   = {6,0xD0,4,0,0x60,0};

static struct {
  char name[4];
  float coef;
} valtab[13];
/*			
extern struct{
  char fval[4];
  char tval[4];
  double coef;
} vtab[30];
*/
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
  char dummy[25];
} j_tab;

static char def_munt[4],zerobytes[16*2],mast_munt;
static int16 cnt;
static uint16 dt_hardware;
static char BootDossier[4],BootSequence[21],StandaardDossier[4]; 
static int DisplayJamadataBrief;
static CFile fil;


static void ask_sys(void);
static void ClearSysPosNrCheck(void);
static void CheckServerMode();
static bool FasFileOpen(int16 nr_);
static void GetJmsParms(void);
static void load_valu(void);
static int SelectDossierUitLijst(void);
static int ZCstr2Arr(CString cstr_, char *p_arr_, int max_len_);



extern "C" void BKH0009cod()
{
  int k,n,len_,flen_,pos,color_,startup_jms_=NO;
	short int yy,mm,dd,post_,hjj_,hmm_,hdd_;
	uint16 MinBkhDatum;
	char kar_,Brek_[15],Iban_[43],Bic_[12];
  char *cpc_,str_[50];
	CString cstr_;

  setlocale(LC_ALL, ""); // nodig voor CMarkup voor conversie UTF2A e.d.	
redo:;
  if(sysopen("","")) {sys_err(108,0); FOREVER reschedule();}
	CheckServerMode();
	GetJmsParms();
	if(procid==1 && *u(25,4)==0){ // alleen post-0 en 1 maal om signaal te geven dat jmc opgestart is
    fil.Open("JMC.OK",CFile::modeCreate|CFile::modeWrite,0);
		fil.Write("X",1);
    fil.Close();
		startup_jms_=YES; // om aan te geven dat dit de opstart van de jms is.
	}

  fasinfo(80,201);dt_hardware=*l(80,1);
  if(*u(25,2)==0) *u(25,2)=dt_hardware;
	if(fldlen(25,11)) *s(25,11)=0;
  sysget(1788,2,&k); sysget(34,31,s(25,1));
	sysget(18480,1,&kar_); if(kar_<1 || kar_>8) color_=DefaultBackGroundColor; else color_=kar_; scrchat(-1,color_); // eerste keer kleur juistzetten
	if(startup_jms_){
		n=0; sysput(3774,2,&n);sysput(3776,2,&n);sysput(3778,2,&n);sysput(3780,2,&n); // blokkering bon/factuur opheffen bij reboot
  }

  if(k) ask_sys();
  else{
		if(strcmpi(BootSequence,"+T3900^6C")!=0){ // niet bij kassa-jmc
      if(CheckPw(0,39,1)==0) goto redo;
		}
    copy("FAS",s(25,3),3);
  }
	if(startup_jms_){
		n=0; sysput(3774,2,&n);sysput(3776,2,&n);sysput(3778,2,&n);sysput(3780,2,&n); // blokkering bon/factuur opheffen bij reboot
  }
  ClearSysPosNrCheck();// blokkering bon/factuur opheffen bij reboot

  sysget(34,31,s(25,1));
  fasinfo(80,201);dt_hardware=*l(80,1);
  if(*u(25,2)==0) *u(25,2)=dt_hardware;
	sysget(18480,1,&kar_); if(kar_<1 || kar_>8) color_=DefaultBackGroundColor; else color_=kar_; scrchat(-1,color_); // kleur juistzetten
	zero(Brek_,sizeof Brek_);sysget(135,14,Brek_);
	zero(Iban_,sizeof Iban_);sysget(1219,42,Iban_);
	zero(Bic_,sizeof Bic_);sysget(1261,11,Bic_);
	if(Iban_[0]=='\0' && Brek_[0]){
		copy(Brek_,Iban_,15);
		if(IbanTools(Iban_,Bic_,Brek_,1)==NO){
			sysput(1219,42,Iban_);sysput(1261,11,Bic_);
		}
	}
	for(k=0;k<5;k++){
  	sysget(2300,2,&MinBkhDatum);
	  if(MinBkhDatum && *u(25,2)>(MinBkhDatum+600)){
 		  jddate(MinBkhDatum,&yy,&mm,&dd); yy=yy%100; yy++;
		  MinBkhDatum=datejd(yy,mm,dd);
		  if(*u(25,2)>MinBkhDatum) sysput(2300,2,&MinBkhDatum);
    } 
		else break;
	}
  load_valu();/* laad alles wat met valuta te maken heeft */
  if(fldlen(26,14)) *l(26,14)=0xFFFFFFFF;
  if(*u(25,4)!=10 && *u(25,4)!=210){
		if(procid==1 && fldlen(29,1)){ // postnummers invullen 
			FasFileOpen(15);
			fasinit(29);*u(29,1)=1; if(fasgeti(29)==0) goto postcode_OK; // is al ingevuld
			if (!fil.Open(_T("PostCode.csv"),CFile::modeRead,0)) goto postcode_OK;
			flen_ = (int)fil.GetLength();
			cpc_ = RamBon;
			fil.Read(cpc_,flen_);
 			fil.Close();
			for (int k=0; k<flen_; ) {
				fasinit(29);
				pos=k;while (cpc_[pos]!=';') pos++;
				len_=pos-k; if(len_>fldlen(29,2)) len_=fldlen(29,2); copy(&cpc_[k],s(29,2),len_);
				k=++pos;
				while (cpc_[pos]!=';' && cpc_[pos]!='\r') pos++;
				len_=pos-k; if(len_>fldlen(29,3)) len_=fldlen(29,3); 
				zero(str_,sizeof str_); copy(&cpc_[k],str_,len_); CnvJamaChar(str_,len_,1);
				for(n=0;n<len_;n++) if(str_[n]>=0x80 && str_[n]<0xA0) break;
				if(n<len_) memcpy(s(29,3),str_,len_); // indien speciale karakters dan niet in hoofdletters zetten
				else{
  				cstr_=CString(str_);cstr_.MakeUpper();memcpy(s(29,3),(char *)(LPCTSTR)cstr_,len_);
				}				
				k=++pos;
				if(cpc_[pos]=='1') *s(29,4)=1;
				fasadd(29);
				while (cpc_[pos++]!='\n'){if(pos>=flen_) break;}
				k=pos++;
			}
postcode_OK:;
		}
		if(DisplayJamadataBrief) ovlcall(95,0);

		if (strcmpi(BootSequence,"+T3900^6C")==0) ovlexit(900);
		if(BootSequence[0]){
      char TmpBuf[80];
      sprintf_s(TmpBuf,sizeof(TmpBuf),"^0F%s",BootSequence);
      scrnum=0;scrget(1,7);
      scraddfield(100,10,18,0);
      scrifld(100,fm_os60,"                 Druk <TAB> aub of");
      scraddfield(101,10,20,0);
      scrifld(101,fm_os60,"update uw Jamadata Desktop om dit scherm te vermijden");
      scraddfield(300,0,0,0xAA);
      scrifld(300,fm_us80,TmpBuf);
      scrupd(-1,0);
		}
	}
	if(ovltest(2397) && ThisScreenNr==1){ // waarschuwing om verkopen door te sturen naar P&T (V.4 + icoon)
		sysget(8746,2,(char *)&post_); if(post_==0) post_=1;
		if(ThisPostNr==post_){ // op deze post
			jddate(*u(25,2),&hjj_,&hmm_,&hdd_);
			if(hdd_>=5 && hdd_<=10){ // enkel tussen de 5-de en 10-de van de maand
				sysget(8742,2,(char *)&mm); 
	      sysget(8744,2,(char *)&yy); 
				hmm_--; if(hmm_<1) {hmm_=12;hjj_--;}
				if(mm && (yy<hjj_ || mm<hmm_)){// indien nog niet verstuurd
					DisplayWarning("Gelieve de verkopen door te sturen naar Prik&Tik.", 581,0); // mode : 0=OK, 1=JA/NEE icoon : 605=!, 61=stop
				}
			}
		}
	}

  if(*u(25,4)==210) ovlexit(210); else ovlexit(10);
}

static void ClearSysPosNrCheck(void)
{
  int16 k,this_proc;

	for(k=0;k<16;k++){
  	sysget((3774+k*2),2,&this_proc);
    if(this_proc==procid){this_proc=0;sysput((3774+k*2),2,&this_proc);}
	}
}

static bool FasFileOpen(int16 nr_)
{
  int16 stu_,k;
  char filename[15];
							
  k=300+17*(nr_-1);
  sysget(k,15,filename);
  sysget(k+15,2,&stu_);
  if(fldlen(stu_,1)>0){
    if(fasopen(filename,0)) return false;
		else return true;
	}
  return false;
}



static void GetJmsParms(void)
{
 	int k;
	char buf_[10];
	CString cstr_,cstr1_,keystr_;

	for(k=0;k<MAX_WERKPOST;k++){ // MINSTENS 1 post met masterfuncties zetten
	  keystr_="GetIniKeyValue|Post-"; 
	  zero(buf_,sizeof buf_);stcli_d(&buf_[0],(long)(k+1),3,0); keystr_+=CString(buf_);
	  keystr_+="_Settings|";
		cstr_=JmsCmd(keystr_+CString("AllowMasterFunctions"));
		if(atol(cstr_)==1) break;
	}
	if(k>=MAX_WERKPOST) JmsCmd("SetIniKeyValue|Post-001_Settings|AllowMasterFunctions|1");

	cstr_=JmsCmd("GetIniKeyValue|JamaSettings|StdInMono"); if(cstr_=="1") StdInMono=1; else StdInMono=0;
	cstr_=JmsCmd("GetIniKeyValue|DataBaseSettings|StdDossier1");cstr_.MakeUpper(); ZCstr2Arr(cstr_,StandaardDossier,4); 
	keystr_.Format("GetIniKeyValue|Post-%03d",ThisPostNr); keystr_+="_Settings|";
	if(ThisScreenNr==1){
	  cstr1_="DisplayJamadataBrief"; cstr_=JmsCmd(keystr_+cstr1_);ZCstr2Arr(cstr_,buf_,4);DisplayJamadataBrief=atoi(buf_);
	}
	cstr1_="AllowMasterFunctions"; cstr_=JmsCmd(keystr_+cstr1_);ZCstr2Arr(cstr_,buf_,4);AllowMasterFunctions=atoi(buf_);
	cstr1_="Name"; cstr_=JmsCmd(keystr_+cstr1_);ZCstr2Arr(cstr_,NaamWerkPost,21);
	cstr1_="MemberOfFiliaal"; cstr_=JmsCmd(keystr_+cstr1_);ZCstr2Arr(cstr_,buf_,4);WerkpostFiliaalNr=atoi(buf_);
	cstr1_.Format("Scherm-%03d_BootDossier",ThisScreenNr); cstr_=JmsCmd(keystr_+cstr1_);
	// indien bootdossier==FAS en standaard!=FAS, dan GEEN bootdossier invullen (foute combinatie)
	if(cmpstr(StandaardDossier,"FAS",3)==0 || cstr_.CompareNoCase("FAS")!=0) ZCstr2Arr(cstr_,BootDossier,4);
	cstr1_.Format("Scherm-%03d_BootSequence",ThisScreenNr); cstr_=JmsCmd(keystr_+cstr1_);ZCstr2Arr(cstr_,BootSequence,21);
	cstr1_.Format("Scherm-%03d_BackGroundColor",ThisScreenNr); cstr_=JmsCmd(keystr_+cstr1_);ZCstr2Arr(cstr_,buf_,4);DefaultBackGroundColor=atoi(buf_);
	cstr_=JmsCmd("GetJMSVersion"); ServerVersion=0;
	if(cstr_=="M") ServerVersion=SERVER_MONO;
	else if(cstr_=="L") ServerVersion=SERVER_LIGHT;
	else if(cstr_=="S") ServerVersion=SERVER_STANDAARD;
	else if(cstr_=="P") ServerVersion=3;
	WarnForProgramUpdate=0;
	if(ThisScreenNr==1){WarnForProgramUpdate=0;}
}

static void CheckServerMode()
{
	CString strJmsMode;
	int len_;

  FOREVER {
    strJmsMode=JmsCmd("ControlDBSessions|GetServiceInfo");
		len_=strJmsMode.GetLength();
    if (len_==0 || strJmsMode.CompareNoCase("OPERATIONAL")==0) return;
		if(len_>60) len_=60;
    scrnum=0;scrget(1,254);// display van de oorzaak, elke 1 seconde 
    scraddfield(1,10+(60-len_)/2,9,2);
    scrifld(1,fm_os60,(char *)(LPCTSTR)strJmsMode);
    scrupd(-3,0);
    Sleep(1000);
  }
}




static void ask_sys(void)
{
  int16 key,k,no_ask_;
  char buf_[5];
	CString cstr_;
  
	no_ask_=NO;
	if(*s(25,3)=='\0' && BootDossier[0]){
		copy(BootDossier,s(25,3),3);no_ask_=YES;
	}
	
  *s(25,1)='\0';
  FOREVER{
    sysclose();
    redo:
    scrnum=0;scrget(1,179);
	  if(AllowMasterFunctions) scraddpicto(2,0,76,22,4,2,56,0,4,"Parameters"); 
    scrfld(1,25,3);
    scrfld(2,25,1);
    scraddpicto(1,1,0,0,2,1,107,0,4,"Herdisplay"); 
		if(no_ask_){key=108;no_ask_=NO;}
    else key=scrupd(1,0x00C0);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key==5001) key=107; // herdisplay
		if(key==5002){
			if(SelectDossierUitLijst()) key=108;
			else goto redo; 
		}
    *s(25,1)='\0';
    if(!*s(25,3)) goto redo;
    zero(buf_,sizeof buf_);copy("00",&buf_[0],2);
    copy(s(25,3),&buf_[2],3);
    for(k=4;;k--) if(buf_[k]) break;
		cstr_=CString(&buf_[k-2]).Mid(0,3);
    // indien standaarddossier1 NIET FAS is, dan mag FAS niet gebruikt worden als dossier (JMS neemt dan dit standaard dossier)
		if(cmpstr(StandaardDossier,"FAS",3) && cstr_.CompareNoCase("FAS")==0){errnum=34;goto redo;}
    copy(&buf_[k-2],s(25,3),3);
    if(sysopen(s(25,3),"")) {errnum=34;goto redo;}
		if(strcmpi(BootSequence,"+T3900^6C")!=0){ // niet bij kassa-jmc
      if(CheckPw(0,39,1)==0) goto redo;
		}
    sysget(34,31,s(25,1));

    if(key!=107) break;
  }
}

static int SelectDossierUitLijst(void)
{
	int k,key,z,pdos_,start_,d_lin_scr=17;
	CFileFind finder;
	BOOL bWorking;
  CString frfile_,cstr_;
	CString FasSubDir="..\\FAS\\";
	struct {
		char code[4];
		char naam[31];
	} tb_dos[200];
	  
	zeroL(tb_dos[0].code,sizeof tb_dos);pdos_=0;
	bWorking = finder.FindFile(FasSubDir+CString("sys.*"));
	while (bWorking) {
		bWorking = finder.FindNextFile();
	  if (finder.IsDirectory()) continue;
		frfile_=finder.GetFileName();
		k=frfile_.ReverseFind('.');
		if(k && k<frfile_.GetLength()){
			cstr_=frfile_.Mid(k+1);cstr_.MakeUpper();
			    // indien standaarddossier1 NIET FAS is, dan mag FAS niet gebruikt worden als dossier (JMS neemt dan dit standaard dossier)
			if(cmpstr(StandaardDossier,"FAS",3)==0 || cstr_.CompareNoCase("FAS")!=0){
				ZCstr2Arr(cstr_,tb_dos[pdos_].code,4);
				if(sysopen(tb_dos[pdos_].code,"?")==0)	sysget(34,31,tb_dos[pdos_++].naam);
			}
		}
		if(pdos_>=200) break;
  }
	finder.Close();

	start_=0; 
  FOREVER{
    scrnum=0;scrget(1,258);z=1;
		if(start_>0) {
      scraddpicto(22,0,61,5,4,2,18,0,4,"up"); 
    }
		if((start_+d_lin_scr)<pdos_) {
      scraddpicto(23,0,61,20,4,2,13,0,4,"down"); 
    }
    for(k=start_;k<start_+d_lin_scr;k++){
		  if(k>=pdos_) break;
			scrifld(z++,fm_os3,tb_dos[k].code);scrifld(z++,fm_os30,tb_dos[k].naam);
			scraddpicto(1+(k-start_),0,18,5+(k-start_),2,1,55,0,6,"selecteer");
    }
    key=scrupd(-1,0x7);
		if ((key/0x100)==1) key=(key&0xFF)+5000;
		if(key>=5001 && key<5001+17){copy(tb_dos[key-5001+start_].code,s(25,3),3);return YES;}
    switch(key){
			case 5022    :
			case 102     : if(start_>0){start_-=d_lin_scr; if(start_<0) start_=0;}
										 break;
			case 5023    :
			case 103     : if((start_+d_lin_scr)<pdos_) start_+=d_lin_scr;
										 break;
			case 101     : goto end;// annuleer 
										 break;
			default      : break;
    }
  }
 
end:;
  return NO;
}
  
static void load_valu(void)
{
  int16 j,k;
  char to_munt_[4];

  fasunlck(0);
  sysget( 294,4,def_munt);
  if(def_munt[0]=='\0') {copy("EUR",def_munt,4);sysput( 294,4,def_munt);}
  sysget(1200,1,&mast_munt);
  if(mast_munt=='\0') {mast_munt='E';sysput(1200,1,&mast_munt);}
  if(fldlen(26,17)) *s(26,17)=mast_munt;
  if(cmpstr(def_munt,"EUR",3)==0) *s(26,17)='E';

  for(k=0;k<30;k++) zero((char *)&vtab[k].fval,sizeof vtab[0]);
  copy("BEF",vtab[0].fval,3);
  copy("EUR",vtab[0].tval,3);
  vtab[0].coef=(double)(40.3399);

  sysget(2560,96,&valtab[0].name[0]);
  sysget( 294,4,def_munt);
  if(mast_munt=='E') copy("EUR",to_munt_,3);
  else copy(def_munt,to_munt_,3);
  for(k=0;k<12;k++){
    if(valtab[k].name[0]=='\0' || valtab[k].coef==0) continue;
    for(j=0;j<30;j++){/* zoek rechtstreekse combinatie */
      if(vtab[j].fval[0]=='\0') {break;}
      if(cmpstr(valtab[k].name,vtab[j].fval,3)) continue;
      if(cmpstr(to_munt_,vtab[j].tval,3)) continue;
      break;
    }
    if(j<30){
      copy(valtab[k].name,vtab[j].fval,3); copy(to_munt_,vtab[j].tval,3);
      vtab[j].coef=valtab[k].coef;/* vtab[j].coef=(double)(1.)/vtab[j].coef; */
    }
  }
  if(cmpstr(to_munt_,"EUR",3)){  /* DEF-munt moet in BEIDE richtingen staan */
    for(k=0;k<30;k++){                     /* zoek rechtstreekse combinatie */
      if(vtab[k].fval[0]=='\0') {break;}
      if(cmpstr("EUR",vtab[k].fval,3)) continue;
      if(cmpstr(def_munt,vtab[k].tval,3)) continue;
      break;
    }
    if(k<30 && vtab[k].fval[0]=='\0'){
      for(j=0;j<30;j++){                      /* zoek omgekeerde combinatie */
	if(vtab[j].fval[0]=='\0') {break;}
	if(cmpstr("EUR",vtab[j].tval,3)) continue;
	if(cmpstr(def_munt,vtab[j].fval,3)) continue;
	break;
      }
      if(vtab[j].fval[0]!='\0'){                                /* gevonden */
	copy(vtab[j].fval,vtab[k].tval,3);
	copy(vtab[j].tval,vtab[k].fval,3);
	vtab[k].coef=vtab[j].coef; vtab[k].coef=(double)(1.)/vtab[k].coef;
      }
    }
  }
  sysflush();
}

static int ZCstr2Arr(CString cstr_, char *p_arr_, int max_len_)
{

  int k,len_;
  
	if(cstr_.GetLength()==0){*p_arr_='\0'; return 0;}
  
  len_=max_len_;
  if(len_==-1 || len_>cstr_.GetLength()) len_=cstr_.GetLength();
  for(k=0;k<len_;k++)  *(p_arr_+k)=cstr_.GetAt(k);
  if(len_>=max_len_) len_--; *(p_arr_+len_)='\0'; 

  return len_;
}