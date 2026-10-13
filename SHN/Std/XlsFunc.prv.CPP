/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

#define FASMNGR 5
extern "C" void CnvJamaChar(char *pString,int16 MaxLen,int16 CnvMode);// CnvMode : 0=Jama->Windows CP1250, 1:Windows CP1250->Jama

static double XlsRound(double bd_,int q_decim_)
{
	int k;
  double wrk1_,wrk2_,wrk3_,add_,result_,bd_afr_;
 
	bd_afr_=1.; 
	for(k=0;k<q_decim_;k++) bd_afr_/=10.;
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
  return (double)(result_);
}

static int fas_ret(char *s)
{
  int *pi32;
  waittask(6,0);
  if (ilength<4) {sys_err(122,ilength); return 0;}
  pi32 = (int *) info;
  return *pi32;
}

static int XlsCreate(char *name)
{
  int16 i;

  pi = (int16 *) info;
  *pi++ = 7; // Nieuw type, bij 1 werd automatisch ruimte voor grafiek voorzien, moet men nu zelf doen !
  i = 2;
  FOREVER {
    info[i++] = *name;
    if (!*name) break;
    name++;
  }
  sendtask(FASMNGR,6,202,info,i);
  return fas_ret(info+2);
}

static int XlsOpen(char *name) // XLS open for read
{
  int16 i;

  pi = (int16 *) info;
  *pi++ = 13; // open for read
  i = 2;
  FOREVER {
    info[i++] = *name;
    if (!*name) break;
    name++;
  }
  sendtask(FASMNGR,6,202,info,i);
  return fas_ret(info+2);
}


static int XlsClose(int16 ref,int16 Action) // 2=attach to mail
{
  pi = (int16 *) info;
  *pi++ = 2;
  *pi++ = ref;
  *pi++ = Action;
  sendtask(FASMNGR,6,202,info,6);
  return fas_ret(info+2);
}


static int XlsSaveAsPdf(int16 ref)
{
  pi = (int16 *) info;
  *pi++ = 3;
  *pi++ = ref;
  sendtask(FASMNGR,6,202,info,4);
  return fas_ret(info+2);
}

static int XlsGetMaxKol(int16 ref)
{
  pi = (int16 *) info;
  *pi++ = 14;
  *pi++ = ref;
  sendtask(FASMNGR,6,202,info,4);
  return fas_ret(info+2);
}

static int XlsGetMaxRij(int16 ref)
{
  pi = (int16 *) info;
  *pi++ = 15;
  *pi++ = ref;
  sendtask(FASMNGR,6,202,info,4);
  return fas_ret(info+2);
}

static int XlsWrite(int16 ref,int16 rownr,int16 colnr,int16 type,char *val, int16 StyleIx)
{
  int16 i, j, len, XlsType;

	XlsType=4; 
	if (StyleIx) {
		XlsType=12;
	}
  pi = (int16 *) info;
  *pi++ = XlsType;  // vroeger 4, toen 5 x int16 en *pData, nu 6 x int16 + 4 spares en *pData
  *pi++ = ref;
  *pi++ = rownr;
  *pi++ = colnr;
  *pi++ = type;
	i=10;
	if (XlsType==12) {
		*pi++ = StyleIx;
		*pi++=0;
		*pi++=0;
		*pi++=0;
		*pi++=0;
		i=20;
	}
	len=0;

  if (type==1) len=4;
  else if (type==2) len=8;
  else if (type==3) len=2;
  if (len==0) {
    while (val[len]) len++;
    len++;
  }
  for (j=0; j<len; j++) info[i+j]=val[j];
  i+=j;
  sendtask(FASMNGR,6,202,info,i);
  return fas_ret(info+2);
}

static int XlsReadString(int16 ref,int16 rownr,int16 colnr,char *ret_string, int16 MaxLen) 
{
  int16 i, len, XlsType;
	int ret_;

	XlsType=16; 
  pi = (int16 *) info;
  *pi++ = XlsType;  
  *pi++ = ref;
  *pi++ = rownr;
  *pi++ = colnr;
  *pi++ = 0; // type labelm max 750 karakters
	i=10;
  sendtask(FASMNGR,6,202,info,i);
  ret_=fas_ret(info+2);
	len=*(int *)&info[4]; if(len>MaxLen) len=MaxLen; // lengte van returnstring zit op info[4]
	memcpy(ret_string,info+8,len); CnvJamaChar(ret_string,len,1);
	return len;
}

static int XlsReadInt(int16 ref,int16 rownr,int16 colnr) 
{
  int16 i, XlsType;
	int ret_,retval_;

	XlsType=16; 
  pi = (int16 *) info;
  *pi++ = XlsType;  
  *pi++ = ref;
  *pi++ = rownr;
  *pi++ = colnr;
  *pi++ = 1; // type int
	i=10;
  sendtask(FASMNGR,6,202,info,i);
  ret_=fas_ret(info+2);
	retval_=*(int *)&info[8]; 
	return retval_;
}

static double XlsReadDouble(int16 ref,int16 rownr,int16 colnr) 
{
  int16 i, XlsType;
	int ret_;
	double retval_;

	XlsType=16; 
  pi = (int16 *) info;
  *pi++ = XlsType;  
  *pi++ = ref;
  *pi++ = rownr;
  *pi++ = colnr;
  *pi++ = 2; // type double
	i=10;
  sendtask(FASMNGR,6,202,info,i);
  ret_=fas_ret(info+2);
	retval_=*(double *)&info[8]; 
	return retval_;
}

static short unsigned XlsReadDate(int16 ref,int16 rownr,int16 colnr) 
{
  int16 i, XlsType;
	int ret_;
	short unsigned retval_;

	XlsType=16; 
  pi = (int16 *) info;
  *pi++ = XlsType;  
  *pi++ = ref;
  *pi++ = rownr;
  *pi++ = colnr;
  *pi++ = 3; // type date
	i=10;
  sendtask(FASMNGR,6,202,info,i);
  ret_=fas_ret(info+2);
	retval_=*(short unsigned *)&info[8]; 
	return retval_;
}


static int XlsSelectWorkSheet(int16 ref,int16 WksNr,char *WksName) // WknNr = 1, 2, ... WksCount
{
  int16 i;
 
  pi = (int16 *) info;
  *pi++ = 8;
  *pi++ = ref;
  *pi++ = WksNr;

  i=6;
  if (WksName==0) WksName="";
  FOREVER {
    info[i++] = *WksName;
    if (!*WksName) break;
    WksName++;
  }
  sendtask(FASMNGR,6,202,info,i);
  return fas_ret(info+2);
}

static int XlsChart(int16 ref,int16 rowcnt,int16 colcnt,int16 chartType,char *title)
{
  int16 i;
 
  pi = (int16 *) info;
  *pi++ = 5;
  *pi++ = ref;
  *pi++ = rowcnt;
  *pi++ = colcnt;
  *pi++ = chartType;
  i=10;

   FOREVER {
    info[i++] = *title;
    if (!*title) break;
    title++;
  }
  sendtask(FASMNGR,6,202,info,i);
  return fas_ret(info+2);
}
 
static int XlsGraf(int16 ref,int16 colnr,int16 chartType,long Color)
{
  int16 i;
  long *pl;
 
  pi = (int16 *) info;
  *pi++ = 6;
  *pi++ = ref;
  *pi++ = colnr;
  *pi++ = chartType;
  pl=(long *)pi;
  *pl++ = Color;
  pi=(int16 *)pl;

  i=12;

  sendtask(FASMNGR,6,202,info,i);
  return fas_ret(info+2);
}

static int XlsRowSize(int16 ref,int16 rownr,int16 size)
{
  int16 i;

  pi = (int16 *) info;
  *pi++ = 9;
  *pi++ = ref;
  *pi++ = rownr;
  *pi++ = size;
  i=8;
  sendtask(FASMNGR,6,202,info,i);
  return fas_ret(info+2);
}

static int XlsColumnSize(int16 ref,int16 rownr,int16 size)
{
  int16 i;

  pi = (int16 *) info;
  *pi++ = 10;
  *pi++ = ref;
  *pi++ = rownr;
  *pi++ = size;
  i=8;
  sendtask(FASMNGR,6,202,info,i);
  return fas_ret(info+2);
}

static int XlsStyle(int16 ref, char *NumFormat,int16 Size,long Color,int16 BoldFlag,int16 ItalicFlag,int16 UnderlineFlag,int16 HorAlignment,int16 VerAlignment,long BackCol,int16 Pattern,int16 Kader,long KaderCol,int16 Lock,int16 Hide)
{
  int16 i, j, len;

  pi = (int16 *) info;
  *pi++ = 11;
  *pi++ = ref;
  *pi++ = Size;
  memcpy(pi,&Color,4);
  pi++; pi++;
  *pi++ = BoldFlag;
  *pi++ = ItalicFlag;
  *pi++ = UnderlineFlag;
  *pi++ = HorAlignment;
  *pi++ = VerAlignment;
  memcpy(pi,&BackCol,4);
  pi++; pi++;
  *pi++ = Pattern;
  *pi++ = Kader;
  memcpy(pi,&KaderCol,4);
  pi++; pi++;
  *pi++ = Lock;
  *pi++ = Hide;
  *pi++ = 0;
  *pi++ = 0;
  i=20*2; len=0;

  while (NumFormat[len]) len++;
  len++;

  for (j=0; j<len; j++) info[i+j]=NumFormat[j];
  i+=j;
  sendtask(FASMNGR,6,202,info,i);
  return fas_ret(info+2);
}


static int16 WriteVar2Xls(int16 rij_,int16 kol_,char *fmt_,char *pvar_,int16 StylIx)
{
	char str_[150];
	uint16 ubd_;
	long lbd_;
	double dbd_;


  zero(str_,sizeof str_);
	if(fmt_[1]==0xC8 || fmt_[1]==0x88){// string 
		copy0(pvar_,str_,fmt_[2]);CnvJamaChar(str_,sizeof str_,0);
		XlsWrite(XlsRef,rij_,kol_,0,str_,StylIx);
	}
	else if(fmt_[1]==0xD0 || fmt_[1]==0x90){// uint16 
		lbd_=*(uint16 *)pvar_;XlsWrite(XlsRef,rij_,kol_,1,(char *)&lbd_,StylIx);
	}
	else if(fmt_[1]==0xD1 || fmt_[1]==0x91){// integer 
		lbd_=*(int16 *)pvar_;XlsWrite(XlsRef,rij_,kol_,1,(char *)&lbd_,StylIx);
	}
	else if(fmt_[1]==0xD3 || fmt_[1]==0x93){// long 
		lbd_=*(long *)pvar_;XlsWrite(XlsRef,rij_,kol_,1,(char *)&lbd_,StylIx);
	}
	else if(fmt_[1]==0xD4 || fmt_[1]==0x94){// float 
		dbd_=XlsRound((double)(*(float *)pvar_),(int)(fmt_[3]));XlsWrite(XlsRef,rij_,kol_,2,(char *)&dbd_,StylIx);
	}
	else if(fmt_[1]==0xD5 || fmt_[1]==0x95){// double 
		dbd_=XlsRound((double)(*(double *)pvar_),(int)(fmt_[3]));XlsWrite(XlsRef,rij_,kol_,2,(char *)&dbd_,StylIx);
	}
	else if(fmt_[1]==0xC0 || fmt_[1]==0x80){// date 
		ubd_=*(uint16 *)pvar_;if(ubd_) XlsWrite(XlsRef,rij_,kol_,3,(char *)&ubd_,StylIx); // OOK StyleNr met numformat dd/mm/yyyy  aanmaken en meegeven !!!!
	}
	else if(fmt_[1]==0xA8 || fmt_[1]==0xE8){// grb 
		grb_deco(str_,(long *)pvar_);if(*(long *)pvar_) XlsWrite(XlsRef,rij_,kol_,0,str_,StylIx);
	}
	else if(fmt_[1]==0xA0 || fmt_[1]==0xE0){// rekening 
		rek_deco(str_,(unsigned char *)pvar_,1);XlsWrite(XlsRef,rij_,kol_,0,str_,StylIx);
	}
	else if(fmt_[1]==0x98 || fmt_[1]==0xD8){// btw
		if(*(long *)pvar_){copy("BE-",str_,3);btw_deco(&str_[3],(long *)pvar_,1);XlsWrite(XlsRef,rij_,kol_,0,str_,StylIx);}
	}
	return 1;
}

static int16 WriteFld2Xls(int16 rij_,int16 kol_,int16 stu_,int16 fld_,int16 StylIx)
{
	char str_[150],*pdum,dummy_[10],fmt_[40];
	uint16 ubd_;
	long lbd_;
	double dbd_;

	if(fldlen(stu_,fld_)==0) XlsWrite(XlsRef,rij_,kol_,0,"",StylIx);
	else{
		pdum=&dummy_[0];fieldspc(stu_,fld_,&pdum,fmt_); // fmt_get
    zero(str_,sizeof str_);
		if(fmt_[1]==0xC8 || fmt_[1]==0x88){// string 
			copy0(s(stu_,fld_),str_,fmt_[2]);CnvJamaChar(str_,sizeof str_,0);
			XlsWrite(XlsRef,rij_,kol_,0,str_,StylIx);
		}
		else if(fmt_[1]==0xD0 || fmt_[1]==0x90){// uint16 
			lbd_=*u(stu_,fld_);XlsWrite(XlsRef,rij_,kol_,1,(char *)&lbd_,StylIx);
		}
		else if(fmt_[1]==0xD1 || fmt_[1]==0x91){// integer 
			lbd_=*i(stu_,fld_);XlsWrite(XlsRef,rij_,kol_,1,(char *)&lbd_,StylIx);
		}
		else if(fmt_[1]==0xD3 || fmt_[1]==0x93){// long 
			lbd_=*l(stu_,fld_);XlsWrite(XlsRef,rij_,kol_,1,(char *)&lbd_,StylIx);
		}
		else if(fmt_[1]==0xD4 || fmt_[1]==0x94){// float 
			dbd_=XlsRound((double)(*f(stu_,fld_)),(int)(fmt_[3]));XlsWrite(XlsRef,rij_,kol_,2,(char *)&dbd_,StylIx);
		}
		else if(fmt_[1]==0xD5 || fmt_[1]==0x95){// double 
			dbd_=XlsRound((double)(*d(stu_,fld_)),(int)(fmt_[3]));XlsWrite(XlsRef,rij_,kol_,2,(char *)&dbd_,StylIx);
		}
		else if(fmt_[1]==0xC0 || fmt_[1]==0x80){// date 
			ubd_=*u(stu_,fld_);if(ubd_) XlsWrite(XlsRef,rij_,kol_,3,(char *)&ubd_,StylIx); // OOK StyleNr met numformat dd/mm/yyyy  aanmaken en meegeven !!!!
		}
		else if(fmt_[1]==0xA8 || fmt_[1]==0xE8){// grb 
			grb_deco(str_,l(stu_,fld_));if(*l(stu_,fld_)) XlsWrite(XlsRef,rij_,kol_,0,str_,StylIx);
		}
		else if(fmt_[1]==0xA0 || fmt_[1]==0xE0){// rekening 
			rek_deco(str_,(unsigned char *)s(stu_,fld_),1);XlsWrite(XlsRef,rij_,kol_,0,str_,StylIx);
		}
		else if(fmt_[1]==0x98 || fmt_[1]==0xD8){// btw
			if(*l(stu_,fld_)){copy("BE-",str_,3);btw_deco(&str_[3],l(stu_,fld_),1);XlsWrite(XlsRef,rij_,kol_,0,str_,StylIx);}
		}
	}
	return 1;
}

static void ReadXls2Fld(int16 ref,int16 rownr,int16 colnr,int16 stu_,int16 fld_) // lees direct in structuur
{
	char str_[150];
	uint16 ubd_,len_;
	long lbd_;
	double dbd_;
  int16 j,k;
  char *pdum,dummy_[10],fmt[40];
					
  pdum=&dummy_[0];
  k=fieldspc(stu_,fld_,&pdum,fmt);
  if(k<=0) goto endsr;

	if(fldlen(stu_,fld_)==0) goto endsr;

	zero(s(stu_,fld_),fldlen(stu_,fld_));
  zero(str_,sizeof str_);
	if(fmt[1]==0xC8 || fmt[1]==0x88){// string 
		XlsReadString(ref,rownr,colnr,s(stu_,fld_),fldlen(stu_,fld_));
	}
	else if(fmt[1]==0xD0 || fmt[1]==0x90){// uint16 
		*u(stu_,fld_)=XlsReadInt(ref,rownr,colnr);
	}
	else if(fmt[1]==0xD1 || fmt[1]==0x91){// integer 
		*i(stu_,fld_)=XlsReadInt(ref,rownr,colnr);
	}
	else if(fmt[1]==0xD3 || fmt[1]==0x93){// long 
		*l(stu_,fld_)=XlsReadInt(ref,rownr,colnr);
	}
	else if(fmt[1]==0xD4 || fmt[1]==0x94){// float 
		*f(stu_,fld_)=XlsRound(XlsReadDouble(ref,rownr,colnr),(int)(fmt[3]));
	}
	else if(fmt[1]==0xD5 || fmt[1]==0x95){// double 
		*d(stu_,fld_)=XlsRound(XlsReadDouble(ref,rownr,colnr),(int)(fmt[3]));
	}
	else if(fmt[1]==0xC0 || fmt[1]==0x80){// date 
		*u(stu_,fld_)=XlsReadDate(ref,rownr,colnr);
	}
	else if(fmt[1]==0xA8 || fmt[1]==0xE8){// grb 
		len_=XlsReadString(ref,rownr,colnr,str_,10); if(len_){grb_comp(str_,l(stu_,fld_));}
	}
	else if(fmt[1]==0xA0 || fmt[1]==0xE0){// rekening 
		len_=XlsReadString(ref,rownr,colnr,str_,15);
		if(len_>=12){
			if(len_>14) len_=14;
			j=20;
      for(k=0;k<len_;k++) if(str_[k]>='0' && str_[k]<='9') str_[j++]=str_[k];
      rek_comp(&str_[20],(unsigned char *)s(stu_,fld_));
		}
	}
	else if(fmt[1]==0x98 || fmt[1]==0xD8){// btw
		len_=XlsReadString(ref,rownr,colnr,str_,15);
		if(len_>=9){
			*l(stu_,fld_)=0;
			for(k=0;k<len_;k++) {
				if(str_[k]>='0' && str_[k]<='9') *l(stu_,fld_)=*l(stu_,fld_)*10+str_[k]-'0';
			}
		}	
	}
  endsr:;
}