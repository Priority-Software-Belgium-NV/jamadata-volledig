// MailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JMS.h"
#include "MailDlg.h"

extern bool JmsExtendedLogging;

#ifndef JMSVIEWER
#using <mscorlib.dll>
#using <System.dll> // nodig om ::Net te mogen gebruiken
//#using "MailBee.NET.dll"
//#using <JMSNet.dll>
// nieuwe key : MN700-CD057AD7052305A705ADD149150D-2BA7
// vers. 5 & 6: MN700-CD057AD7052305A705ADD149150D-2BA7
#include <direct.h>
#include <sys/timeb.h>
#include <time.h>

using namespace System;
using namespace System::Net;
using namespace JMSNet;
using namespace JMSMailOAuth;

//using namespace System::Net::Mail;
//using namespace System::Net::Mime;
using namespace System::Threading;
using namespace System::ComponentModel;

using namespace MailBee;
using namespace MailBee::AddressCheck;
using namespace MailBee::Mime;
using namespace MailBee::Security;
using namespace MailBee::ImapMail;
using namespace MailBee::SmtpMail;
using namespace MailBee::Outlook;
using namespace MailBee::Mime;
#endif

// CMailDlg dialog

IMPLEMENT_DYNAMIC(CMailDlg, CDialog)

CMailDlg::CMailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMailDlg::IDD, pParent)
  , MailSubDir(_T(""))
  , ScanMailDirBusy(false)
{
  theApp.MailServerhThread=(HANDLE) -1L; // set to invalid handle value so the OnTimer in JMSDLG will start the UCServer ...
#ifndef JMSVIEWER
	IPAddress^ IPNr = (IPAddress ^) Net::Dns::GetHostByName(Net::Dns::GetHostName())->AddressList->GetValue(0);
	array<unsigned char>^ IP = IPNr->GetAddressBytes();
	IpNumber.Format("%d.%d.%d.%d",IP[0],IP[1],IP[2],IP[3]);
	CFile ipf;
	CString ipnam=PathProg;
	ipnam+="JMS.inf";
	ipf.Open(ipnam,CFile::modeWrite | CFile::modeCreate,0);
	ipf.Write(IpNumber,IpNumber.GetLength());
	ipf.Write("\r\n",2);
	ipf.Close();
  theApp.Mail2SendEvent = CreateEvent(NULL,FALSE,FALSE,NULL); // default security attributes, auto-reset event, initial state is nonsignaled
  theApp.MailServerWatchDog= 0;
#endif
}

CMailDlg::~CMailDlg()
{
#ifndef JMSVIEWER
  if (theApp.MailServerhThread!=(HANDLE)-1L) {
    TerminateThread(theApp.MailServerhThread,0);
    theApp.MailServerhThread=(HANDLE)-1L;
  }
  CloseHandle(theApp.Mail2SendEvent);
#endif
}

void CMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMailDlg, CDialog)
	ON_BN_CLICKED(IDC_btnSendTestMail, &CMailDlg::OnBnClickedbtnsendtestmail)
  ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CMailDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

// ("pop.em.be|marctest@key.be|jamadata|Inbox|1|10", 83)
CString CMailDlg::GetMailEnveloppes(CString Cmd, unsigned short OrigId)
//(CString Server, CString UserName, CString Password, CString Folder, int First, int MaxCount)
{
	CString strReturn="@%!";

#ifndef JMSVIEWER
	int i,j=0;
	CString Server, UserName, Password, Folder;
	int First, MaxCount;

	i=Cmd.Find("|",j);
	if (i>0) Server=Cmd.Mid(j,i-j);
	j=i+1;
	i=Cmd.Find("|",j);
	if (i>0) UserName=Cmd.Mid(j,i-j);
	j=i+1;
	i=Cmd.Find("|",j);
	if (i>0) Password=Cmd.Mid(j,i-j);
	j=i+1;
	i=Cmd.Find("|",j);
	if (i>0) Folder=Cmd.Mid(j,i-j);
	j=i+1;
	i=Cmd.Find("|",j);
	if (i>0) First=atol(Cmd.Mid(j,i-j));
	j=i+1;
	i=Cmd.GetLength();
	if (i>0) MaxCount=atol(Cmd.Mid(j,i-j));

  CString cstr;
  Imap::LicenseKey="MN120-9058A7AF596A58C5585E063E4602-DB0D";
  Imap^ p = gcnew Imap();
  p->ThrowExceptions=false;
	p->Connect(gcnew String(Server));
	p->Login(gcnew String(UserName), gcnew String(Password));
	p->SelectFolder(gcnew String(Folder));
  cstr.Format("%d:%d",First,First+MaxCount-1); // Is 1-based, not zero based
	EnvelopeCollection^ envs = p->DownloadEnvelopes(gcnew String(cstr), false, EnvelopeParts::MailBeeEnvelope | EnvelopeParts::BodyStructure, 0); // download 0 bytes of body ...
  if (envs) {
		cstr.Format("MsgCount=%d\r\n",p->MessageCount);
		strReturn=cstr;
		for (int i=0; i<envs->Count; i++) {
			Envelope^ env=envs->default[i];
			cstr.Format("Msg:%d|Date:%s|From:%s|Subject:%s",env->MessageNumber,env->DateReceived.ToString(),env->From->ToString(),env->Subject);
			strReturn+=cstr;
			ImapBodyStructureCollection^ parts = env->BodyStructure->GetAllParts();
			int AttCount=1;
			for (int i=0; i<parts->Count; i++) {
				ImapBodyStructure^ part=parts->default[i];
				if (part->Filename) {
					cstr.Format("|Attach#%d:%s",AttCount++,part->Filename);
					strReturn+=cstr;
				}
			}
			strReturn+="\r\n";
		}
	}
	p->Disconnect();
#endif
  return strReturn;
}

CString CMailDlg::GetMailMessage(CString Cmd, unsigned short OrigId)
// (CString Server, CString UserName, CString Password, CString Folder, int Nr, bool DeleteFlag)
{
	CString strReturn="@%!";
  	
#ifndef JMSVIEWER
  int i,j=0;
	CString Server, UserName, Password, Folder;
	int Nr;
	bool DeleteFlag=false;

	i=Cmd.Find("|",j);
	if (i>0) Server=Cmd.Mid(j,i-j);
	j=i+1;
	i=Cmd.Find("|",j);
	if (i>0) UserName=Cmd.Mid(j,i-j);
	j=i+1;
	i=Cmd.Find("|",j);
	if (i>0) Password=Cmd.Mid(j,i-j);
	j=i+1;
	i=Cmd.Find("|",j);
	if (i>0) Folder=Cmd.Mid(j,i-j);
	j=i+1;
	i=Cmd.Find("|",j);
	if (i>0) Nr=atol(Cmd.Mid(j,i-j));
	j=i+1;
	i=Cmd.GetLength();
	if (i>0) {
		if (Cmd.Mid(j,1)=="1") DeleteFlag=true;
	}

	CString cstr, PathThisMail;
  Imap::LicenseKey="MN120-9058A7AF596A58C5585E063E4602-DB0D";
  Imap^ p = gcnew Imap();
  p->ThrowExceptions=false;
	p->Connect(gcnew String(Server));
	p->Login(gcnew String(UserName), gcnew String(Password));
	p->SelectFolder(gcnew String(Folder));
	MailMessage^ msg = p->DownloadEntireMessage(Nr, false);
	if (msg) {
		strReturn="";
		msg->Parser->HtmlToPlainMode=HtmlToPlainAutoConvert::IfNoPlain;
		cstr=msg->MessageID;
		PathThisMail=PathSpoolTemp+cstr.Mid(1,cstr.GetLength()-2)+"\\";
		CreateDirectory(PathThisMail,NULL);
		
		cstr.Format("Date:%s\r\n",msg->DateReceived.ToString());
		strReturn+=cstr;
		cstr.Format("From:%s\r\n",msg->From->ToString());
		strReturn+=cstr;
		cstr.Format("Subject:%s\r\n",msg->Subject);
		strReturn+=cstr;
		CString PathBody=PathThisMail+"Body.txt";
		cstr.Format("Body:%s\r\n",PathBody);
		strReturn+=cstr;
		CFile fil;
		fil.Open(PathBody,CFile::modeWrite | CFile::modeCreate,0);
		fil.Write(CString(msg->BodyPlainText),msg->BodyPlainText->Length);
		fil.Close();
		
		for (int i=0; i<msg->Attachments->Count; i++) {
			Attachment^ attach = msg->Attachments->default[i];
			CString PathAttach=PathThisMail+attach->Filename;
			cstr.Format("Attach#%d:%s\r\n",i+1,PathAttach);
			strReturn+=cstr;
			attach->Save(gcnew String(PathAttach), true);
		}
	}
	if (DeleteFlag) {
		cstr.Format("%d",Nr); 
		p->DeleteMessages(gcnew String(cstr),false);
	}
	p->Close();
	p->Disconnect();
#endif
  return strReturn;
}						

CString CMailDlg::GetTemplateNames()
{
  CString strReturn="";
#ifndef JMSVIEWER
	if (JMSVersion!='M' || StdInMono) {
		CFileFind finder;
		CString FindFileName=PathMailTemplates;
		FindFileName+="*.EML";
		BOOL bWorking = finder.FindFile(FindFileName);
		while (bWorking) {
			bWorking=finder.FindNextFile();
			if (finder.IsDirectory()) continue;
			strReturn+=("["+finder.GetFileTitle()+"]dummy");
			strReturn+="\r\n";
		}
		finder.Close();
	}
#endif
  return strReturn;
}

void CMailDlg::FindAllMergeFields(CString& strReturn, CString Text)
{
  int i=0, j=0, k=0;
  while (i>=0) {
    i=Text.Find("[",i);
    if (i<0) break;

    if (i>=0) {
      j=Text.Find("]",i);
      if (j>=0) k=Text.Find(" ",i);
      if (k<0 || k>j) {
        bool AlreadyAdded=false;
        CString strField=Text.Mid(i+1,j-i-1)+"\r\n";
        if (strReturn.GetLength()>=strField.GetLength()) {
          if (strReturn.Left(strField.GetLength())==strField) AlreadyAdded=true;
          k=strReturn.Find(strField);
          if (k>0 && strReturn.GetAt(k-1)=='\n') AlreadyAdded=true;
        }
        if (strField.CompareNoCase("endif\r\n")==0) AlreadyAdded=true; // de endif zit in de HTML code, is geen veld voor ons 
        if (!AlreadyAdded) strReturn+=strField;
      }
    }
    i+=1;
  }
}

CString CMailDlg::GetTemplateMergeFields(CString TemplateRef)
{
  CString strReturn="";
#ifndef JMSVIEWER
	if (JMSVersion!='M' || StdInMono) {
		try {
			CString TemplateFileName=PathMailTemplates+TemplateRef+".EML";
			String^ EmlFilePath=gcnew String(TemplateFileName);
			MailMessage^ msg = gcnew MailMessage();
			if (msg->LoadMessage(EmlFilePath)) {
				FindAllMergeFields(strReturn, CString(msg->Subject));
				FindAllMergeFields(strReturn, CString(msg->BodyPlainText));
				FindAllMergeFields(strReturn, CString(msg->BodyHtmlText));
				if (strReturn.GetLength()==0) strReturn="\r\n";
			}
		}
		catch (MailBeeException^ e) {
			LogAdd(77,0,"Fatal Exception while GetTemplateMergeFields",e->Message);
			e->~MailBeeException();
		}
	}
#endif
  return strReturn;
}

CString CMailDlg::ViewMail(CString Cmd, unsigned short OrigId)
{
  CString strReturn="@%!";

#ifndef JMSVIEWER
  if (Cmd.GetLength()>=16) {
    bool MsgFlag=false;
    if (Cmd.Mid(0,3).CompareNoCase("MSG")==0) MsgFlag=true;
    CString MailRefNr=Cmd.Mid(4);
    CString MailRef=MailRefNr+".EML";
    CString EmlFilePath=PathMailSent+MailRef;
    if (GetFileAttributes(EmlFilePath)!=INVALID_FILE_ATTRIBUTES) strReturn="OK=SENT";
    else {
      EmlFilePath=PathMailFailed+MailRef;
      if (GetFileAttributes(EmlFilePath)!=INVALID_FILE_ATTRIBUTES) strReturn="OK=FAILED";
      else {
        EmlFilePath=PathMailOutbox+MailRef;
        if (GetFileAttributes(EmlFilePath)!=INVALID_FILE_ATTRIBUTES) strReturn="OK=OUTBOX";
        else {
          EmlFilePath=PathMailToCheck+MailRef;
          if (GetFileAttributes(EmlFilePath)!=INVALID_FILE_ATTRIBUTES) strReturn="OK=TOCHECK";
        }
      }
    }
    if (strReturn.GetLength()) {
      try {
        CString TempFilePath, ToClientPost;
				if (JMSVersion=='M') {
					ToClientPost=PathSpoolTemp;
				}
				else {
	        ToClientPost.Format("%sPost-%03d\\",PathSpoolToClient,1+OrigId/5);
		      CreateDirectory(ToClientPost,NULL);
				}
				if (MsgFlag) {
          TempFilePath.Format("%s%s.msg",ToClientPost,MailRefNr);
          MsgConvert::LicenseKey="MN120-9058A7AF596A58C5585E063E4602-DB0D";
          MsgConvert^ MsgConv = gcnew MsgConvert();
          //MsgConv->HtmlToRtfMethod = HtmlToRtfConversionMethod::None; 
          MsgConv->EmlToMsg(gcnew String(EmlFilePath),gcnew String(TempFilePath));
        }
        else {
          TempFilePath.Format("%s%s.eml",ToClientPost,MailRefNr);
          MailMessage^ msg = gcnew MailMessage();
          msg->LoadMessage(gcnew String(EmlFilePath));
          msg->Headers->Remove("X-Unsent");
          msg->SaveMessage(gcnew String(TempFilePath));
        }
        if (theApp.JmsTestConfigFlag || JMSVersion=='M') { 
          ::ShellExecute(NULL,"open",TempFilePath,NULL,NULL,SW_SHOW);
        }
        else {
					int PostNr=1+OrigId/5;
					if (PostWnd[PostNr-1]==0) {
						LogAdd(112,0,"hWnd for JMH not filled in, so Txmit of eMail slow for PostNr=",PostNr);
					}
					::PostMessage(PostWnd[PostNr-1],WM_USER+2,0,0); // proc_send2peer ...
					if (JmsExtendedLogging) {
						CString cstr;
						cstr.Format("Txfer to Post-%03d = %s", 1+OrigId/5, TempFilePath);
						LogAdd(0,1,cstr);
					}
        }
      }
      catch (MailBeeException^ e) {
        LogAdd(102,0,"Fatal Exception while ViewMail",e->Message);
				e->~MailBeeException();
        strReturn="BAD";
      }
    }
  }
#endif
  return strReturn;
}
CString CMailDlg::MakeMailKeyword(char *keyword_)
{
	CString strReturn;

	if(MailProfileNr==0) strReturn=CString(keyword_);
	else strReturn.Format("%s%d",keyword_,MailProfileNr); 
	return strReturn;

}

bool IsSendByGmail(CString cmd) {
	char kar_;
	int i, j;
	CString action_ = "", relayServer_ = "1", security_;

	i = cmd.Find("RelayServer|", 0);

	if (i > 0) {
		j = cmd.Find("\r\n", i + 12);

		if (j > i)
			kar_ = cmd.GetAt(i + 12);

		if (kar_ >= '1' && kar_ <= '2')
			relayServer_ = kar_;
	}

	i = cmd.Find("Action|", 0);

	if (i > 0) {
		j = cmd.Find("\r\n", i + 7);

		if (j > 1)
			action_ = cmd.Mid(i + 7, j - i - 7);
	}

	security_ = theApp.iniFile.getKeyValue("Relay" + relayServer_ + "Security", "MailSettings");
	return security_.CompareNoCase("GMAIL") == 0 && action_.CompareNoCase("TOSEND") == 0;
}

CString CMailDlg::MergeTemplateAndMail(CString Cmd, unsigned short OrigId)
{
	CString strReturn = "@%!";

#ifndef JMSVIEWER
	CString MailRefNr, TempFilePath, TmpNumberFilePath, ToClientPost, SaveFolder, RelayServer = "1";
	bool AllowSendButton = false, OpenEml = false, OpenMsg = false, Eml2Send = false;
	char kar_;
	CFile TmpNumberFile;
	int p = 0, i, j;
	MailMessage^ msg;

	// Check if it's to send by GMail
	if (IsSendByGmail(Cmd))
		return GMail::SendMail(gcnew String(PathMailTemplates), gcnew String(PathSpoolFiles), gcnew String(Cmd));

	MailProfileNr = 0;
	i = Cmd.Find("MailProfile|", 0);
	if (i > 0) {
		i += 12; j = Cmd.Find("\r\n", i);
		if (j > i) kar_ = Cmd.GetAt(i);
		if (kar_ >= '1' && kar_ <= '9') MailProfileNr = kar_ - '0';
	}
	p = 0;
	if (Cmd.Mid(0, 9).MakeLower() != "template|") return strReturn;
	p += 9;
	i = Cmd.Find("\r\n", p);
	if (i < 0) return strReturn;

	CString TemplateRef = Cmd.Mid(p, i - p);
	String^ strTemplateRef = gcnew String(TemplateRef);
	p = i + 2;
	if (JMSVersion == 'M' && !StdInMono) strTemplateRef = "";
	strTemplateRef = "[" + strTemplateRef + "]";
	int TempLen = strTemplateRef->Length;
	bool FoundTemplate = false;

	try {
		msg = gcnew MailMessage();
		if (TempLen > 2) { // wanneer er een template ingevuld is, dan die gaan zoeken ...
			CString TemplateFileName = PathMailTemplates + TemplateRef + ".EML";
			String^ EmlFilePath = gcnew String(TemplateFileName);
			if (GetFileAttributes(TemplateFileName) != INVALID_FILE_ATTRIBUTES) {
				msg->LoadMessage(EmlFilePath);
				if (JmsExtendedLogging) LogAdd(0, 1, "E-Mail Template loaded", EmlFilePath);
				// verwijder templatenaam uit subject
				msg->Subject = msg->Subject->Replace(strTemplateRef, "");
				// wis alle bestaande e-mailadressen die nog in template zouden zitten van eventuele upload e.d.
				msg->From = gcnew EmailAddress("");
				msg->To->Clear();
				msg->Cc->Clear();
				msg->Bcc->Clear();
				msg->ReplyTo->Clear();
			}
		}

		// zet de datum en uur op datum van nu
		msg->Date = DateTime::Now;
		// voeg de standaard instellingen uit JMS.ini toe (BCC, reply-to, notification, ...)
		msg->Bcc->Add(gcnew String(theApp.iniFile.getKeyValue(MakeMailKeyword("MailBcc"), "MailSettings")));
		msg->ReplyTo->Add(gcnew String(theApp.iniFile.getKeyValue(MakeMailKeyword("MailReplyTo"), "MailSettings")));
		msg->ConfirmRead = gcnew String(theApp.iniFile.getKeyValue(MakeMailKeyword("MailConfirmReadTo"), "MailSettings"));
		msg->ConfirmReceipt = gcnew String(theApp.iniFile.getKeyValue(MakeMailKeyword("MailConfirmReceiptTo"), "MailSettings"));

		/*** Winmail is met Tnef, maar we kunnen er niet veel aan doen, er zit een stuk van de body tekst in ...
		for (i=0; i<msg->Attachments->Count; i++) {
		  Attachment^ att=msg->Attachments->default[i];
		  if (att->IsTnef) {
			att->GetAttachmentsFromTnef()->SaveAll("C:\\Temp");
		  }
		}
		*/

		while (p < Cmd.GetLength()) {
			i = Cmd.Find("|", p);
			String^ strCmd = gcnew String(Cmd.Mid(p, i - p));
			p = i + 1;
			i = Cmd.Find("|", p);
			j = Cmd.Find("\r", p);
			if (i<0 || i>j) i = j;
			String^ strParm1 = gcnew String(Cmd.Mid(p, i - p));
			String^ strParm2 = gcnew String("");
			if (Cmd.GetAt(i) == '|') {
				p = i + 1;
				i = Cmd.Find("\r", p);
				strParm2 = gcnew String(Cmd.Mid(p, i - p));
			}
			p = Cmd.Find("\r\n", p);
			if (p < 0) p = Cmd.GetLength();
			else p += 2;
			strCmd = strCmd->ToUpper();

			if (strCmd == "TO") {
				msg->To->Add(strParm1, strParm2); // remark (3-de parm) gebruiken we (nog) niet ...
			}
			else if (strCmd == "CC") {
				msg->Cc->Add(strParm1, strParm2); // remark (3-de parm) gebruiken we (nog) niet ...
			}
			else if (strCmd == "BCC") {
				msg->Bcc->Add(strParm1, strParm2); // remark (3-de parm) gebruiken we (nog) niet ...
			}
			else if (strCmd == "ATTACHJAMAFILEREF") {
				CString JamaFileName;
				JamaFileName.Format("%s%08X*.*", PathSpoolFiles, Convert::ToInt32(strParm1));
				bool AttachmentAddedFlag = false;
				for (int Retry = 0; Retry < 120; Retry++) {
					CFileFind AttFinder;
					BOOL bWorking = AttFinder.FindFile(JamaFileName);
					while (bWorking) {
						bWorking = AttFinder.FindNextFile();
						CString FriendlyName = AttFinder.GetFilePath();
						int l = FriendlyName.Find("$");
						if (l >= 0) FriendlyName = FriendlyName.Mid(l + 1);
						String^ strFileName = gcnew String(AttFinder.GetFilePath());
						String^ strFriendlyName = gcnew String(FriendlyName);
						TRACE("Adding %s as %s\n", strFileName, strFriendlyName);
						try {
							msg->Attachments->Add(strFileName, strFriendlyName);
							if (JmsExtendedLogging) LogAdd(0, 1, "E-Mail attachment added", strFileName);
							AttachmentAddedFlag = true;
						}
						catch (...) {
							CString cstr;
							cstr.Format("Attachment '%s' could not be added", strFriendlyName);
							LogAdd(108, 0, cstr, strFileName);
						}
					}
					AttFinder.Close();
					if (AttachmentAddedFlag) break;
					TRACE("Wait 500 msec for attachement ...\n");
					Sleep(500);  // wacht halve seconde
				}
				if (!AttachmentAddedFlag) {
					LogAdd(107, 0, "Attachment for mail not found within 60 seconds", JamaFileName);
				}
			}
			else if (strCmd == "ATTACHTHISFILE") { // zelf file opgegeven
				CString JamaFileName;
				JamaFileName.Format("%s%s", PathProg, strParm1);
				// JamaFileName.Format("%s%08X*.*",PathSpoolFiles,Convert::ToInt32(strParm1));
				bool AttachmentAddedFlag = false;
				for (int Retry = 0; Retry < 120; Retry++) {
					CFileFind AttFinder;
					BOOL bWorking = AttFinder.FindFile(JamaFileName);
					while (bWorking) {
						bWorking = AttFinder.FindNextFile();
						CString FriendlyName = AttFinder.GetFilePath();
						int l = FriendlyName.ReverseFind('\\');
						if (l >= 0) FriendlyName = FriendlyName.Mid(l + 1);
						String^ strFileName = gcnew String(AttFinder.GetFilePath());
						String^ strFriendlyName = gcnew String(FriendlyName);
						TRACE("Adding %s as %s\n", strFileName, strFriendlyName);
						try {
							msg->Attachments->Add(strFileName, strFriendlyName);
							if (JmsExtendedLogging) LogAdd(0, 1, "E-Mail attachment added", strFileName);
							AttachmentAddedFlag = true;
						}
						catch (...) {
							CString cstr;
							cstr.Format("Attachment '%s' could not be added", strFriendlyName);
							LogAdd(108, 0, cstr, strFileName);
						}
					}
					AttFinder.Close();
					if (AttachmentAddedFlag) break;
					TRACE("Wait 500 msec for attachement ...\n");
					Sleep(500);  // wacht halve seconde
				}
				if (!AttachmentAddedFlag) {
					LogAdd(107, 0, "Attachment for mail not found within 60 seconds", JamaFileName);
				}
			}
			else if (strCmd == "REPLACE") {
				strParm1 = "[" + strParm1 + "]";
				msg->Subject = msg->Subject->Replace(strParm1, strParm2);
				msg->BodyHtmlText = msg->BodyHtmlText->Replace(strParm1, strParm2);
				msg->BodyPlainText = msg->BodyPlainText->Replace(strParm1, strParm2);
			}
			else if (strCmd == "ACTION") {
				if (strParm1->ToUpper() == "USEREML") {
					AllowSendButton = true;
					OpenEml = true;
				}
				else if (strParm1->ToUpper() == "USERMSG") {
					AllowSendButton = true;
					OpenMsg = true;
				}
				else if (strParm1->ToUpper() == "PREVIEWEML") {
					AllowSendButton = false;
					OpenEml = true;
				}
				else if (strParm1->ToUpper() == "PREVIEWMSG") {
					AllowSendButton = false;
					OpenMsg = true;
				}
				else if (strParm1->ToUpper() == "TOCHECK") {
					SaveFolder = PathMailToCheck;
				}
				else if (strParm1->ToUpper() == "TOSEND") {
					Eml2Send = true;
					SaveFolder = PathMailOutbox;
				}
			}
			else if (strCmd == "RELAYSERVER") {
				RelayServer = strParm1;

				if (RelayServer != "1" && RelayServer != "2")
					RelayServer = "1";
			}
		}

		if (JMSVersion == 'M') {
			ToClientPost = PathSpoolTemp;
		}
		else {
			ToClientPost.Format("%sPost-%03d\\", PathSpoolToClient, 1 + OrigId / 5);
			CreateDirectory(ToClientPost, NULL);
		}

		// Create MailRefNr
		double now = COleDateTime::GetCurrentTime().operator double();
		int Days = (int)now;
		struct _timeb timebuffer;
		_ftime(&timebuffer);
		int Secs = timebuffer.time % 86400;
		int mSecs = timebuffer.millitm;
		MailRefNr.Format("%04X%05X%03X", Days, Secs, mSecs);

		if (SaveFolder.GetLength() > 0) { // mail wordt opgeslagen om te verzenden, dus de afzender al invullen
			CString afzender_ = theApp.iniFile.getKeyValue("Relay" + RelayServer + "UserName", "MailSettings");

			if (afzender_.IsEmpty())
				afzender_ = theApp.iniFile.getKeyValue(MakeMailKeyword("MailFromAddress"), "MailSettings");
			else {
				EmailAddressValidator^ valid = gcnew EmailAddressValidator("MN120-9058A7AF596A58C5585E063E4602-DB0D");
				valid->ValidationLevel = AddressValidationLevel::RegexCheck;
				AddressValidationLevel result_ = valid->Verify(gcnew String(afzender_));

				if (result_ != AddressValidationLevel::OK)
					afzender_ = theApp.iniFile.getKeyValue(MakeMailKeyword("MailFromAddress"), "MailSettings");
			}

			msg->From = gcnew EmailAddress(gcnew String(afzender_), gcnew String(theApp.iniFile.getKeyValue(MakeMailKeyword("MailFromName"), "MailSettings")));
		}

		if (AllowSendButton) msg->Headers->Add("X-Unsent", "1", true);
		if (OpenEml) TempFilePath.Format("%s%s-%s.eml", ToClientPost, RelayServer, MailRefNr);
		else TempFilePath.Format("%s%s-%s.eml", PathSpoolTemp, RelayServer, MailRefNr);
		String^ EmlFilePath = gcnew String(TempFilePath);
		msg->SaveMessage(EmlFilePath);
		if (OpenMsg) {
			TempFilePath.Format("%s%s-%s.msg", ToClientPost, RelayServer, MailRefNr);
			String^ MsgFilePath = gcnew String(TempFilePath);
			MsgConvert::LicenseKey = "MN120-9058A7AF596A58C5585E063E4602-DB0D";
			MsgConvert^ MsgConv = gcnew MsgConvert();
			MsgConv->HtmlToRtfMethod = HtmlToRtfConversionMethod::None;
			if (AllowSendButton) MsgConv->MsgAsDraft = true;
			MsgConv->MsgAsUnicode = false;
			MsgConv->EmlToMsg(EmlFilePath, MsgFilePath);
		}
		if (OpenMsg || OpenEml) {
			if (theApp.JmsTestConfigFlag || JMSVersion == 'M') {
				if (OpenMsg && JMSVersion == 'M') ::ShellExecute(NULL, "open", CString(TempFilePath), NULL, NULL, SW_SHOW);
				else ::ShellExecute(NULL, "open", CString(EmlFilePath), NULL, NULL, SW_SHOW);  // in debug altijd de EML versie openen
			}
			else {
				int PostNr = 1 + OrigId / 5;
				if (PostWnd[PostNr - 1] == 0) {
					LogAdd(111, 0, "hWnd for JMH not filled in, so Txmit of eMail slow for PostNr=", PostNr);
				}
				else ::PostMessage(PostWnd[PostNr - 1], WM_USER + 2, 0, 0); // proc_send2peer ...
				if (JmsExtendedLogging) {
					CString cstr;
					cstr.Format("Txfer to Post-%03d = %s", 1 + OrigId / 5, TempFilePath);
					LogAdd(0, 1, cstr);
				}
			}
			strReturn = "OK";
		}
		else {
			TempFilePath.Format("%s%s-%s.eml", SaveFolder, RelayServer, MailRefNr);
			EmlFilePath = gcnew String(TempFilePath);
			msg->SaveMessage(EmlFilePath);
			if (JmsExtendedLogging) LogAdd(0, 1, "E-Mail saved to", EmlFilePath);
			Eml2Send = true;
			strReturn.Format("OK=%s", MailRefNr);
		}
	}
	catch (MailBeeException^ e) {
		LogAdd(76, 0, "Fatal Exception while MergeTemplateAndMail", e->Message);
		e->~MailBeeException();
	}
	if (Eml2Send) SetEvent(theApp.Mail2SendEvent);
#endif

	return strReturn;
}

void CMailDlg::SendTestMail(void)
{
  
  CString MergeCmd;
  MergeCmd = "Template|BON1FR\r\n";
  MergeCmd +="Action|UserMSG\r\n";
  MergeCmd +="To|jaak@jamadata.be|Cafe mevrouw Lea Vandenbosse - Schepers\r\n";
  MergeCmd +="AttachJamaFileRef|62\r\n";
  CString Reply = MergeTemplateAndMail(MergeCmd, 83);

	//CString cstr2 = GetMailEnveloppes("pop.em.be|marctest@key.be|jamadata|Inbox|1|10", 83);
	//CString cstr3 = GetMailMessage("pop.em.be|marctest@key.be|jamadata|Inbox|3|0", 83);
	return;

  //CString MergeCmd;
  CString cstr=GetTemplateNames();

  cstr=ViewMail("EML|9FEAA717E4B1", 83);
  cstr=ViewMail("MSG|9FEAA717E4B1", 83);

  CString Templ = GetTemplateMergeFields("FACT1");

  MergeCmd = "Template|BON1FR\r\n";
  MergeCmd +="Action|UserMSG\r\n";
  MergeCmd +="To|jaak@jamadata.be|Cafe mevrouw Lea Vandenbosse - Schepers\r\n";
  MergeCmd +="AttachJamaFileRef|62\r\n";
  Reply = MergeTemplateAndMail(MergeCmd, 83);

  MergeCmd = "Template|RAP1\r\n";  
  MergeCmd+= "Action|ToSend\r\n"; // UserEML, UserMSG, PreviewEML, PreviewMSG, ToSend, ToCheck 
  MergeCmd+= "To|jaak@jamadata.be|Jaak Geerits\r\n";
  MergeCmd+= "To|support@jamadata.be|Support Jamadata\r\n";
  MergeCmd+= "CC|johan@jamadata.be|Johan Aerts\r\n";
  MergeCmd+= "BCC|jaak.geerits@priority-software.com\r\n";
  MergeCmd+= "AttachJamaFileRef|51\r\n";
  MergeCmd+= "AttachJamaFileRef|55\r\n";
  MergeCmd+= "Replace|KlantNaam|De Plezante Hoek\r\n";
  MergeCmd+= "Replace|SaldoVervallen|233,10\r\n";

  CString Reply2 = MergeTemplateAndMail(MergeCmd, 83);

  return;

  //CString Templ = GetTemplateMergeFields("RAP3N");
  CString Last = Templ.Right(4);
  return;
}

void CMailDlg::OnBnClickedbtnsendtestmail()
{
	// TODO: Add your control notification handler code here
	SendTestMail();

/* om code te testen via knop testmail
	CString strReturn = "@%!";
	CString CBE = "";

	SVC ^svc = gcnew SVC();
	System::String ^Reply = gcnew System::String("");
	System::Boolean ret = svc->IbanityShowLicence("c05eb410-6149-4f28-aa91-92e8e748894d", Reply);
 	strReturn = Reply;

	if (strReturn == "") strReturn = "@%!";
	// return strReturn;
  */
}

void CMailDlg::OnOK()
{
	//CDialog::OnOK(); // wegdoen of <ENTER> closed de dialog
}

CString CMailDlg::CheckEmailAddress(CString EmailAddress)
{
  CString strReturn="Bad";
#ifndef JMSVIEWER
  String^ strImapServer=gcnew String(theApp.iniFile.getKeyValue(MakeMailKeyword("ImapServer"),"MailSettings"));

  if (strImapServer->Substring(0,4)->ToLower()=="dir:") {
    return "Demo version";
  }

  try {
	Smtp::LicenseKey = "MN120-9058A7AF596A58C5585E063E4602-DB0D";
//oud    Smtp::LicenseKey="MN700-CD057AD7052305A705ADD149150D-2BA7";
    Smtp^ mailer = gcnew Smtp();
    mailer->ThrowExceptions=false;
    mailer->DnsServers->Autodetect();
    mailer->From->AsString = "info@jamadata.be";
    mailer->To->AsString = gcnew String(EmailAddress);
    mailer->Subject = "Nieuwsbrief";
    mailer->BodyPlainText = "This is our weekly newsletter.";
    TestSendResult ret=mailer->TestSend(SendFailureThreshold::AnyRecipientsFailed);
    switch (ret) {
      case TestSendResult::OK:  strReturn="OK"; break;
      case TestSendResult::BadSender:  strReturn="BadSender"; break;
      case TestSendResult::BadRecipient:  strReturn="BadRecipient"; break;
      case TestSendResult::NoAcceptedRecipients:  strReturn="NoAcceptedRecipients"; break;
      case TestSendResult::NegativeSmtpResponse:  strReturn="NegativeSmtpResponse"; break;
      default: strReturn="Unkown Error"; break;
    }
    TRACE(EmailAddress); TRACE(strReturn); TRACE("\r\n");
  }
  catch (MailBeeException^ e) {
    LogAdd(74,0,"Fatal Exception while CheckEmailAddress",e->Message);
		e->~MailBeeException();
  }
#endif
  return strReturn;
}

void RunMailServer(void* dummy)
{
	bool firstRun = true;
	bool working;
	int port;
	CFileFind finder;
	CString emlFilePath;
	CString failedFilePath;
	CString fileName;
	CString findFileName;
	CString logName;
	CString msgConvertedPath;
	CString relayServer;
	CString security;
	CString sentFilePath;
	CString serverPrefix;

#ifndef JMSVIEWER
	MailBee::Global::LicenseKey = "MN120-9058A7AF596A58C5585E063E4602-DB0D";

	while (!JMSShuttingDown) {
		try {
			theApp.MailServerWatchDog = 0; // Reset de watchdog (na 3 minuten geen reset, dan wordt MailServer herstart in JMSDLG.CPP)

			if (!firstRun)
				WaitForSingleObject(theApp.Mail2SendEvent, 60 * 1000); // wacht 1 minuut of tot event fired is (dan is er een mail to send)
			else {
				LogAdd(0, 1, "MailServer starting-up");
				firstRun = false;
			}

			findFileName = PathMailTemplates + R"(Msg2Eml\*.msg)";
			working = finder.FindFile(findFileName);

			while (working) {
				working = finder.FindNextFile();

				if (finder.IsDirectory())
					continue;

				MsgConvert^ msgConv = gcnew MsgConvert();
				emlFilePath = PathMailTemplates + finder.GetFileTitle() + ".eml";
				msgConv->MsgToEml(gcnew String(finder.GetFilePath()), gcnew String(emlFilePath));
				msgConvertedPath = PathMailTemplates + R"(Msg2Eml\Converted\)" + finder.GetFileName();
				_unlink(msgConvertedPath);
				MoveFile(finder.GetFilePath(), msgConvertedPath);
			}

			if (theApp.JmsTestConfigFlag)
				continue;

			findFileName = PathMailOutbox + "*.eml";
			working = finder.FindFile(findFileName);

			while (working) {
				working = finder.FindNextFile();

				if (finder.IsDirectory())
					continue;

				relayServer = "1";
				fileName = finder.GetFileName();

				if (fileName[1] == '-')
				{
					relayServer = fileName[0];

					if (relayServer != "1" && relayServer != "2")
						relayServer = "1";
				}

				MailMessage^ msg = gcnew MailMessage();

				if (msg->LoadMessage(gcnew String(finder.GetFilePath()))) {
					Smtp^ mailer = gcnew Smtp();
					mailer->ThrowExceptions = false;
					serverPrefix = "Relay" + relayServer;
					SmtpServer^ smptServer = gcnew SmtpServer();
					smptServer->AccountName = gcnew String(theApp.iniFile.getKeyValue(serverPrefix + "UserName", "MailSettings"));
					smptServer->Name = gcnew String(theApp.iniFile.getKeyValue(serverPrefix + "Server", "MailSettings"));
					smptServer->Password = gcnew String(theApp.iniFile.getKeyValue(serverPrefix + "Password", "MailSettings"));
					port = atol(theApp.iniFile.getKeyValue(serverPrefix + "Port", "MailSettings"));

					if (port)
						smptServer->Port = port;

					smptServer->Priority = 10;
					security = theApp.iniFile.getKeyValue(serverPrefix + "Security", "MailSettings").MakeUpper();

					if (security == "AUTO")
						smptServer->AuthMethods = AuthenticationMethods::Auto;
					else if (security == "SPA")
						smptServer->AuthMethods = AuthenticationMethods::SaslNtlm;
					else if (security == "NONE")
						smptServer->AuthMethods = AuthenticationMethods::None;

					mailer->SmtpServers->Add(smptServer);
					mailer->Message = msg;

					if (mailer->Send()) {
						sentFilePath = PathMailSent + finder.GetFileName();
						_unlink(sentFilePath);
						MoveFile(finder.GetFilePath(), sentFilePath);
						Sleep(7200); // maximaal 7,2 mails per minuut (500 mails per uur), om mobistar en andere smtp policies niet te schenden (PWH 16/05/13),
					}
					else {
						// Probeer een 2-de keer, nu met logging
						mailer->Log->Enabled = true;
						logName = PathJamaRoot + R"(ToGeel\)" + finder.GetFileName() + ".log";
						mailer->Log->Filename = gcnew String(logName);

						if (mailer->Send()) {
							sentFilePath = PathMailSent + finder.GetFileName();
							_unlink(sentFilePath);
							_unlink(logName);
							MoveFile(finder.GetFilePath(), sentFilePath);
						}
						else {
							failedFilePath = PathMailFailed + finder.GetFileName();
							_unlink(failedFilePath);
							MoveFile(finder.GetFilePath(), failedFilePath);
							LogAdd(101, 0, "SMTP-Mailer failed for", finder.GetFileName());
						}
					}
				}
			}
		}
		catch (MailBeeException^ e) {
			LogAdd(73, 0, "Fatal Exception while periodic thread 'MailServer'", e->Message);
			e->~MailBeeException();
		}
	}
#endif
}