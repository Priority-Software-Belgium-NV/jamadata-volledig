#include "Std\OVLCpp.h"
extern "C" char* BKH2801GetD() {return &zzvw;} // MailMerge en send
#include "OvlShare.h"

#define FOREVER         while(1)
#define YES             1
#define NO              0

extern "C" char BKH2801dat[] = "bkh2801  00:01 07/02/11 (c) Jamadata"; // ovl om mail te versturen, op te via ovlcall 
																																			// VERVANGEN DOOR SendMail IN CPPSHARE.CPP (dus deze ovl wordt niet meer gebruikt)

static char fm_titel[]  = {7,0x88,80,0,0,0,0};
static char fm_os50[]  = {7,0x88,50,0,0,0,0};
static char fm_os30[]  = {7,0x88,30,0,0,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_us50[]  = {7,0xC8,50,0,0,0,0};

static bool CheckEmailAdres(char *email_, int len_,int internetcheck_);
static void DisplayMenuTitel(int ypos_,char *tekst_,char attrib_);
static CString Double2String(double getal,long mode); // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
static int GetEmailStandaard(void); // 1=EML, rest = MSG
static CString Int2String(int getal){return Double2String((double) getal,0); }
static void SendMail(int send_mode);
static int ZCstr2Arr(CString cstr_, char *p_arr_, int max_len_);
  
extern "C" void BKH2801cod(int parmval)
{
	retcall=YES;
	SendMail(parmval);
	ovlexit(-1);
}

static void SendMail(int send_mode)
{
  int z,k,key,pos_,pos1_;
	char buf_[20],mailprofiel_;
  CString cstr_,cstr1_,keystr_,template_,mergefields_,cmd_;

	retcall=YES;

	 
	// emailadres checken en eventueel opvragen
	
	if(CheckEmailAdres(MailMergeData[5],sizeof MailMergeData[5],NO)==false){
		FOREVER{
			redo:;
			scrget(1,249);z=1;
			scrifld(z++,fm_os50,MailMergeData[0]);
			scrifld(z++,fm_os50,MailMergeData[1]);
			scrifld(z++,fm_os6,MailMergeData[2]);scrifld(z++,fm_os30,MailMergeData[3]);
			scrifld(z++,fm_us50,MailMergeData[5]);
			key=scrupd(5,0x81);
			if(key==101){retcall=NO;goto endsr;}
			if(CheckEmailAdres(MailMergeData[5],sizeof MailMergeData[5],NO)==false){errnum=38; goto redo;}
			if(key==108) break;
		}
	}
	sysget(18481,1,&mailprofiel_);if(mailprofiel_>9) mailprofiel_=0;
	// template checken en erbij halen met de mergefields
	scrget(1,7);scrupd(-3,0);
	scraddf(-1,0,0,0);DisplayMenuTitel(10,"Bezig met opmaken mail. Even geduld aub...",0x2);
	zeros(buf_,sizeof buf_);template_="";mergefields_="";
	if(MailMergeFormaat>0 && MailMergeFormaat<=30){
		sysget(18004+(MailMergeFormaat-1)*16,5,buf_); template_=CString(buf_);
		if(MailMergeTaal) template_+=CString(MailMergeTaal);
	}
	mergefields_=CString("");
	if(template_.GetLength()!=0){ // indien ingevuld dan ophalen, anders lege mail
  	cstr_="[";cstr_+=template_+"]";
	  cstr1_=JmsCmd("GetMailTemplates");
	  if(cstr1_.Find(cstr_)>=0){// zoeken of [xxxx] ergens ertussen staat
	    mergefields_=JmsCmd("GetTemplateMergeFields|"+template_);
	  } 
	}
  
	// versturen van de mail 
	cmd_ = "MergeTemplateAndMail\r\n";
  cmd_+= "Template|" + template_ + "\r\n";  
	if(send_mode==1){ // in serie zonder tussenkomst
		cmd_+= "Action|ToSend\r\n";    
	}
	else{ // mail tonen om te versturen 
    if(GetEmailStandaard()) cmd_+= "Action|UserEML\r\n";         // UserEML, UserMSG, PreviewEML, PreviewMSG, ToSend, ToCheck 
	  else cmd_+= "Action|UserMSG\r\n";     
	}
	cmd_+= "To|"+CString(MailMergeData[5])+"|"+CString(MailMergeData[0])+"\r\n"; //  To|email|naam\r\n
   
   //    cmd_+= "CC|jan@jamadata.be|Jan Van Gestel\r\n";
  //     cmd_+= "BCC|marc_vg@hotmail.com\r\n";
	if(mailprofiel_){ // afwijkend mailprofiel
		zeros(buf_,sizeof buf_); buf_[0]='0'+mailprofiel_;
    cmd_+= "MailProfile|"+CString(buf_)+"\r\n"; 
	}
	for(k=0;k<10;k++){
		if(MailMergeBijlage[k]==0) continue;
		cmd_+= "AttachJamaFileRef|"+Int2String(MailMergeBijlage[k])+"\r\n";  // JamaFileRef die ge terugkrijgt bij PrtClose()  of XlsSave()
	}
	
	if(mergefields_.GetLength()){ // keywords vervangen 
		pos_=0;pos1_=0;
		FOREVER{
		
			pos1_=mergefields_.Find('\n',pos_+1); if(pos1_<0) break;
			cstr_=mergefields_.Mid(pos_,pos1_-pos_);
			for(k=0;k<DIM_MAILMERGEKEYWORDS;k++){
					if(cstr_.CompareNoCase(MailMergeKeywords[k])>=0){
	          cmd_+= "Replace|"+CString(MailMergeKeywords[k])+"|"+CString(MailMergeData[k])+"\r\n";   // hier een lijst opgeven van alle 'merge-fields' (zie hoger)
			    }
			}
			pos_=pos1_+1;
		}
	}
  cstr_=JmsCmd(cmd_); // de mail versturen 
  if(cstr_.CompareNoCase("OK")!=0) retcall=NO;    // OK als het gelukt is !
	endsr:;
  ovlexit(-1);
}

static bool CheckEmailAdres(char *email_, int len_,int internetcheck_)
{
  int k,at_fnd_,punt_fnd_;
 	CString keystr_,cstr_;


  if(internetcheck_){		// emailadres checken via internet  ... duurt wel 1 min
		keystr_="CheckEmailAddress|";keystr_+=CString(email_);
    cstr_=JmsCmd(keystr_);  // duurt wel lang voor respons 
    if(cstr_.CompareNoCase("OK")!=0) return false; 
	}
	else{ // korte test op @ en .
    at_fnd_=0; punt_fnd_=0;
    for(k=0;k<len_;k++){
      if(*(email_+k)=='\0') break;
      if(*(email_+k)=='@') at_fnd_++;
      if(*(email_+k)=='.' && at_fnd_) punt_fnd_++;
    }
    if(at_fnd_!=1 || punt_fnd_==0 || k<4) return false; 
	}
	return true;
}
 

static CString Double2String(double getal,long mode)  // mode 0,1,2,... number of decimals  -1=as needed, dec.point=komma
{ 
 
  CString fuval,S;

  if(mode<0){
    fuval.Format(TEXT("%lf"),getal);
    if(fuval.Find(TEXT("."))>=0){
      while(1){
        if(fuval.Right(1)=="0") fuval=fuval.Left(fuval.GetLength()-1);
        else break;
      }
      if(fuval.Right(1)==".") fuval=fuval.Left(fuval.GetLength()-1);
    }
  }
  else{
    S="%8."+CString((char)('0'+mode))+"lf";
    fuval.Format(S,getal);
  }
  fuval.TrimLeft();
  fuval.Replace('.',',');
  return fuval;
}

static void DisplayMenuTitel(int ypos_,char *tekst_,char attrib_)
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

static int GetEmailStandaard(void) // 0 = MSG, rest = EML
{
  char buf_[10];
  CString cstr_,cstr1_,keystr_;

  keystr_.Format("GetIniKeyValue|Post-%03d",ThisPostNr); keystr_+="_Settings|";
  cstr1_="DisplayEmailAsEML"; cstr_=JmsCmd(keystr_+cstr1_);ZCstr2Arr(cstr_,buf_,4);
  return atoi(buf_);
      
}

static int ZCstr2Arr(CString cstr_, char *p_arr_, int max_len_)
{

  int k,len_;
  
  if(cstr_.GetLength()==0) return 0;
  
  len_=max_len_;
  if(len_==-1 || len_>cstr_.GetLength()) len_=cstr_.GetLength();
  for(k=0;k<len_;k++)  *(p_arr_+k)=cstr_.GetAt(k);
  if(len_>=max_len_) len_--; *(p_arr_+len_)='\0'; 

  return len_;
}