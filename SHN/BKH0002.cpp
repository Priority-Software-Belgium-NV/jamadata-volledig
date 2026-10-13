/*32-01*/
#include "Std\OVLCpp.h"
#include "OvlShare.h"
extern "C" char* BKH0002GetD() {return &zzvw;}


typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();
extern "C" char BKH0002dat[] = "bkh0002  00:19 06/09/11 (c) Jamadata";//stoppen/starten server en werkstations


#define FOREVER         while(1)
#define YES             1
#define NO              0

extern int16 procid;
//extern int16 jamin1[];
extern int16 prc_num[];

extern char *s();
extern uint16 *u();
static uint16 de_mod(),make_pw();
extern long *l();
static long makegrb();
extern double *d();

static char fm_menu[]  = {7,0x48,1,0,9,0,0};
static char fm_os6[]   = {7,0x88,6,0,0,0,0};
static char fm_os23[]   = {7,0x88,23,0,0,0,0};
static char fm_os30[]   = {7,0x88,30,0,0,0,0};
static char fm_os63[]  = {7,0x88,63,0,0,0,0};
static char fm_os4[]   = {7,0x88,4,0,0,0,0};
static char fm_us80[]  = {7,0xC8,80,0,0,0,0};
								

static void DisplayServiceMessage(char* tekst_, char attrib_);
static int16 CheckActiveUsers(void);
static void ServiceSlave(void);
static int16 StopServer(void);

  
extern "C" void BKH0002cod(int parmval)
{
  switch(parmval){
		case 0 : ServiceSlave(); ovlexit(1); break; // standby mode, en bij exit naar ovl0001 springen
		case 1 : retcall=CheckActiveUsers(); break; // toon actieve gebruikers , 0=iedereen is eruit (of geforceerd met F4)
		case 2 : retcall=StopServer(); break; // check active gebruikers en stop DB, 1=OK
		case 3 : JmsCmd("ControlDBSessions|SetOperational");break; // DB opstarten en posten vrijgeven 
		default : break;
  }
  ovlexit(-1);
}

//void MarkupTest()
//{
//  CMarkup xml;
//  xml.AddElem( "ORDER" );
//  xml.IntoElem();
//  xml.AddElem( "ITEM" );
//  xml.IntoElem();
//  xml.AddElem( "SN", "132487A-J" );
//  xml.AddElem( "NAME", "crank casing" );
//  xml.AddElem( "QTY", "1" );
//  xml.Save("C:\\Jamadata\\Sample.xml" );
//}

static int16 CheckActiveUsers(void)
{
	int tb_active[21], ActCnt=0, KritCnt=0,LinCnt,ix,ProcId,State,k,z,key;
  CString msg,reply,cstr_,keystr_;
	
	
  FOREVER {
    reply=JmsCmd("ControlDBSessions|GetSessionsInfo");
  
    msg.Format("Illegal reply with length = %d",reply.GetLength());
    if (reply.GetLength()>=10 && reply.Left(7).CompareNoCase("LINCNT=")==0) {
			zero((char *)&tb_active[0],sizeof tb_active);ActCnt=0; KritCnt=0;
      LinCnt=atol(reply.Mid(7));
      ix=0;
      while (ix>=0) {
        ix = reply.Find("\r\n",ix);
        if (ix<0) break;
        ix += 2;
        ProcId = atol(reply.Mid(ix,3));
        State = atol(reply.Mid(ix+4));
				if(ProcId!=procid){
				  if(ProcId/5>=0 && ProcId/5<20 && tb_active[ProcId/5]<State) tb_active[ProcId/5]=State;
          if (State==1) ActCnt++;
          else if (State==2) KritCnt++;
				}
      }
    }
		if(KritCnt==0 && ActCnt==0) break;
  	scrnum=0;scrget(3,1);z=1;
		for(k=0;k<35;k++){
			if(tb_active[k]){
				keystr_.Format("GetIniKeyValue|Post-%03d_Settings|Name",k+1);
				if(tb_active[k]) cstr_=JmsCmd(keystr_);
        scrifld(z,fm_os30, (char *)(LPCTSTR)cstr_);
				if(tb_active[k]==2){
					scrchat(z,0xA);
					scraddpicto(z,0,19,z+5,2,1,605,0,0,"Opgelet!"); 
				}
				z++;
				if(z>=15) break;
			}
		}
    key=scrupd(-1,0x49);
	  if(key==101) return 0;
		if(key==104) break;
  }
	return 1;
}

static int16 StopServer(void)
{
	CFile Cmd;
  CString CmdName = "JMT.CMD";
  CString Command,cstr_,message_;
	int16 executed=0;

	if(CheckActiveUsers()==0) return 0;
	scrget(1,7);scrupd(-3,0);
	cstr_=JmsCmd("ControlDBSessions|SetServiceMode");
#if _DEBUG
	message_=CString(NaamWerkPost); message_+=" is bezig met onderhoudswerkzaamheden.";
  JmsCmd("ControlDBSessions|SetServiceInfo|"+message_); // message naar de andere stations sturen
	return 1;
#endif
  Command.Format("RESETALLJMCEXCEPT %d\r\n",(ThisPostNr-1)*5+ThisScreenNr);
  _unlink(CmdName);
  Cmd.Open(CmdName,CFile::modeCreate|CFile::modeWrite,NULL);
  Cmd.Write(Command,Command.GetLength());
  Cmd.Close();
  if (ServerVersion==0) { // MONO
    HWND JMD=FindWindow("THE_JMD",NULL);
    PostMessage(JMD, 0x405, 0, 0); // PROC_RECEIVED_FILES -> de JMD moet deze file verwerken !
  }
  executed=0;
  for (int loop=0; loop<200; loop++) {
    Sleep(250);
    if(GetFileAttributes("JMT.CMD")==INVALID_FILE_ATTRIBUTES) {
      executed=YES;
      break;
    }
  }
  if (executed) {
		message_=CString(NaamWerkPost); message_+=" is bezig met onderhoudswerkzaamheden.";
    JmsCmd("ControlDBSessions|SetServiceInfo|"+message_); // message naar de andere stations sturen
	}
	return executed;
}


static void ServiceSlave(void)
{
	CString cstr_;
	  
	scrget(1,170);scrupd(-3,0);
	FOREVER{
		cstr_=JmsCmd("ControlDBSessions|GetServiceInfo"); 
		if(cstr_.CompareNoCase("Operational")==0) break;
		DisplayServiceMessage((char *)(LPCTSTR)cstr_,0xA);
	  Sleep(250);
	}
  fasinit(25); // om nieuwe start te forceren 
	ovlexit(1);
}

static void DisplayServiceMessage(char* tekst_, char attrib_)
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
	copy(fm_os63,fmt_,sizeof fm_os63);fmt_[2]=len_;
	scraddf(-1,0,0,0);
	scraddfield(200,beg_,10,attrib_);scrifld(200,fmt_,dsptekst_);
	scraddfield(201,32,15,0x2);scrifld(201,fm_os63,"Even geduld a.u.b.");
	scrupd(-3,0);
}