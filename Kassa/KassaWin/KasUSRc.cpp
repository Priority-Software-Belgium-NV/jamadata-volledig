// KasUSRc.cpp: implementation of the CKasUSR class.
//
//////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4996)
// #define WINVER 0x0501  // was 500
// #define _WIN32_WINNT 0x0501  // was 500

#include "p:\jamacon\library\JamaConL.h"
#include "kashead.h"
#include "KasUSRc.h"

// #include "stdafx.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKasUSR::CKasUSR()
{
  key_size = sizeof(user_list[0]);
  ConUsrRef=-1;
}

CKasUSR::~CKasUSR()
{
  cl_kasusr();
}
 
extern int key_count, plulink, optiesgroep, MenuKeyDifColor, PromoKeyDifColor;

void CKasUSR::SelKeyConen(int type, void *p)

//          type = 0 : display eerste scherm en return (voor keyconen op kassa)
//                 1 : display en zoek keycoon. 
//                 2 : display en zoek keycoon voor extra-optie. p verwijst naar search_niveau 
//                <0 : do unkbchar(-type) en zet type op 1 

{

// int art_select(int key)

  unsigned char sear_niv[MAX_NIVEAU], new_niv[MAX_NIVEAU];
  char buf[500], *ps, first, snelkies, ok, beep_fl, key_buf[100];
  int PlatformNr, x,y,i,j,wissen,_ix,key_prev, _xpos, _ypos, xcnt, ycnt, key, keyb, optix1, optix2;
  int sear_level, len, keybuflen, consave;
  double _aantal;
	COLORREF ColorMenuKey, ColorKey, ColorPromoKey;
	CString PluStr;

  if (type!=0) {
    consave=ConSelect(ConUsrRef);
//    keychar=kbchar();
//    ConSelect(consave);
//    kbchar();
//    ConSelect(ConUsrRef);
  }

  if (type<0) {
    unkbchar(-type); // moet in deze CONSCREEN zijn !
    type=1;
  }

	ColorMenuKey=RGB(255,0,0);
  if (MenuKeyDifColor==1) ColorMenuKey=RGB(0x72,0x36,0x07);
  else if (MenuKeyDifColor==2) ColorMenuKey=RGB(0xF1,0x7C,0x04);
	else if (MenuKeyDifColor==3) ColorMenuKey=RGB(144,25,25);
	else if (MenuKeyDifColor==4) ColorMenuKey=RGB(0xcc,0x00,0x66);

	ColorPromoKey=RGB(255,0,0);
  if (PromoKeyDifColor==1) ColorPromoKey=RGB(0x72,0x36,0x07);
  else if (PromoKeyDifColor==2) ColorPromoKey=RGB(0xF1,0x7C,0x04);
	else if (PromoKeyDifColor==3) ColorPromoKey=RGB(144,25,25);
	else if (PromoKeyDifColor==4) ColorPromoKey=RGB(0xcc,0x00,0x66);

	
  PlatformNr=PlatformType(0);
  if (aantal==0.) _aantal=1.;
  else _aantal=aantal;
  aantal=1.;

  if (type==0) {
    for (i=0; i<MAX_NIVEAU; i++) sear_niv[i]=0;
  }
  else if (type==2) {
    movmem(p,sear_niv,MAX_NIVEAU);
    //disp_clr(0,1,80,24);
  }
  else {
    vrkused=0;
    len=sizeof(vrk); zeroes((char *)vrk,len);
    for (j=0; j<MAX_NIVEAU; j++) sear_niv[j]=0;
    //disp_clr(0,0,80,25);
  }
  for (sear_level=0; sear_level<MAX_NIVEAU; sear_level++) if (sear_niv[sear_level]) break;
  get_work(sear_niv,NO);
  wissen=YES; snelkies=NO; key_prev=-1; 
  FOREVER {
    if (kbtest(true)) goto retry;
//   next:;
    if (sear_niv[MAX_NIVEAU-2]==0) {
      _xpos=xpos; _ypos=ypos; xcnt=3; ycnt=6;
    }
    else {
      _xpos=0; _ypos=1; xcnt=8; ycnt=6;
    }
    for (y=0; y<ycnt; y++) {
      for (x=0; x<xcnt; x++) {
        ps=buf;
        for (j=0; j<3; j++) {
          for (i=0; i<8; i++) {
            if ((*ps=user_work[y][x].tekst[j][i])==0) {
              if (i=0) *ps++=' ';
              break;
            }
            ps++;
          }
          *ps++='\n';
        }
        *ps=0;
				ColorKey=RGB(255,0,0);
				PluStr=user_work[y][x].artcode;
				if (PluStr.GetLength()>0) {
					if (PluStr.GetAt(0)=='*') ColorKey=ColorMenuKey;
				  else {
				    PluStr='|'+PluStr+'|';
				    if (pKasPLU->PromoPLUs.Find(PluStr)>=0) ColorKey=ColorPromoKey;
				  }
				}
				disp_ikey(_xpos+x*10,_ypos+y*4, 10, 4, 1000+(y+1)*16+(x+1), buf, ColorKey); 
      }
    }
    if (type==0) return;

  redisp:;
    disp_key(71,0,8,1,22); wissen=NO;
    if (snelkies) {
      disp_key(0,0,12,1,90);
      disp_clr(30,0,20,1);
      if (vrkused>0) {
        conv_getal(vrk[vrkused-1].aantal,buf,5,2,2); buf[5]=0; disp_vid(14,0,buf,0);
        movmem(pKasPLU->art_info.naam,buf,20); buf[20]=0; disp_vid(30,0,buf,0);
      }
      if (plulink==0) {
        if (stuks_fl) disp_key(21,0,7,1,42); else disp_key(21,0,7,1,88);
      }
      disp_key(52,0,3,1,11);
      disp_key(56,0,3,1,12);
      disp_key(61,0,4,1,83);
      disp_key(66,0,4,1,84);
    }
    else {
		  disp_clr(0,0,70,1);
			disp_key(0,0,12,1,89);
		}
  retry:;
    key=kbchar();
    if (key<0x10000) {
      keyb=key;
      key=-key;
      if (keyb==0x02) { // STX
        keybuflen=0;
        FOREVER {
          key=kbchar();
          if (key==0x03) break; // ETX
          if (keybuflen<sizeof(key_buf)) key_buf[keybuflen++]=key;
        }
        key_buf[keybuflen]=0;
        _ix=pKasPLU->find_ean(key_buf);
        if (_ix>-1) {
          vrk[vrkused].stuks_fl=false;
          if (_ix>=1000000) {
            _ix-=1000000; vrk[vrkused].stuks_fl=true;
          }
          if (vrkused>0 && vrk[vrkused-1].plu_ix==_ix) {
            vrk[vrkused-1].aantal+=1.;
          }
          else {
            vrk[vrkused].plu_ix=_ix;
            vrk[vrkused++].aantal=1.;
          }
        }
        goto redisp;
      }
    }
    else {
      key=key/0x10000;
      if (key>1000) {
        x=((key-1000)%16)-1; y=((key-1000)/16)-1; 
        first=user_work[y][x].artcode[0];
        if (first=='*') {
          if (sear_niv[0]) beep_bad();
          else {
            for (j=0; j<MAX_NIVEAU-2; j++) sear_niv[j]=sear_niv[j+1];
            sear_niv[MAX_NIVEAU-2]=key-1000;
            get_work(sear_niv,NO);
            //disp_clr(0,1,80,24);

          }
        }
        else if (first) {
          _ix=pKasPLU->find_plu(user_work[y][x].artcode);
          if (_ix<0) {beep_fl=BAD; goto retry;}
          if (vrkused>0 && _ix==vrk[vrkused-1].plu_ix) {
            vrk[vrkused-1].aantal+=1.;
          }
          else {
            for (optix1=0; optix1<ExtraOptiesUsed; optix1++) {
              if (memcmp(pKasPLU->art_info.code_l,ExtraOpties[optix1].artcode,ARTCODE_LEN)==0) break;
            }
            for (optix2=0; optix2<ExtraOptiesUsed; optix2++) {
              if (memcmp(pKasPLU->art_info.code_lst,ExtraOpties[optix2].artcode,ARTCODE_LEN)==0) break;
            }
            if (optix1==ExtraOptiesUsed && optix2==ExtraOptiesUsed) { // geen opties nodig
              vrk[vrkused].plu_ix=_ix;
              vrk[vrkused].aantal=_aantal; 
              vrk[vrkused].stuks_fl=stuks_fl;
              if (type==2) vrk[vrkused].optie_fl=YES;
              vrkused++;
              key_prev=key;
            }
            else {
//              screen_save();
              movmem(pKasPLU->art_info.naam,buf,20); buf[20]=0; disp_vid(30,0,buf,0);
              for (i=0; i<_aantal; i++) {
                vrk[vrkused].plu_ix=_ix;
                vrk[vrkused].aantal=1.;
                vrk[vrkused++].stuks_fl=stuks_fl;
                sprintf(buf,"%3d/%-3d",i+1,(int)_aantal); disp_vid(20,0,buf,0);
                if (optix1<ExtraOptiesUsed) SelKeyConen(2,ExtraOpties[optix1].key);
                if (optix2<ExtraOptiesUsed) SelKeyConen(2,ExtraOpties[optix2].key);
                get_work(sear_niv,NO);
              }
//              screen_restore();
              key_prev=-1;
            }
            _aantal=1; // volgende keer altijd 1 stuk nemen !
            if (!snelkies) {
              goto endsr;
            }
          }
        }
		else  if(sear_niv[MAX_NIVEAU - 2] == 0) {// probleem lege knop op hoogste niveau (3 naast mekaar)
		  for (j = MAX_NIVEAU - 2; j >= 1; j--) sear_niv[j] = sear_niv[j - 1];
		  sear_niv[0] = 0;
		  if (sear_niv[MAX_NIVEAU - 2] == 0) goto endsr;
		  if (type == 2 && sear_niv[sear_level] == 0) goto endsr;
		  get_work(sear_niv, NO);
		  //disp_clr(0,1,80,24);
		}
      }
    }
/*
    for (x=0; x<8; x++) {
      if (wissen) disp_clr(x*10,0,10,25);
      for (y=0; y<6; y++) {
        disp_user(x*10+1,y*4+2,y*16+x+1017);
      }
    }
*/
/*		// deze code zorgde ervoor dat het laatste product 2 lijnen kreeg. Mag niet meer in Windowsversie ?? 07/03/08
    if ((key==83 || key==84 || key==90) && key_prev>=0) {
      disp_clr(34,0,20,1);
      vrk[vrkused].plu_ix=_ix;
      vrk[vrkused].aantal=1.;
      vrk[vrkused++].stuks_fl=stuks_fl;
      key_prev=-1;
    }
*/

    if (key==22) {/// vorig scherm 
      for (j=MAX_NIVEAU-2; j>=1; j--) sear_niv[j]=sear_niv[j-1];
      sear_niv[0]=0;
      if (sear_niv[MAX_NIVEAU-2]==0) goto endsr;
      if (type==2 && sear_niv[sear_level]==0) goto endsr;
      get_work(sear_niv,NO);
      //disp_clr(0,1,80,24);
    }
    else if (key==89 && snelkies==NO) {
      if (vrkused>0 && vrk[vrkused-1].aantal>0) vrk[vrkused-1].aantal-=1.;
      snelkies=YES;
    }
    if (key==90) break;
    if (key==11 && vrkused>0) vrk[vrkused-1].aantal+=1.;
    if (key==12 && vrkused>0) vrk[vrkused-1].aantal-=1.;
    if (key==42) stuks_fl=NO;
    if (key==88) stuks_fl=YES;
    if (key==83 || key==84) {
      movmem(sear_niv,new_niv,MAX_NIVEAU);
      j=new_niv[MAX_NIVEAU-2];
      y=(j-17)/16; x=(j-17)%16;
      for (j=MAX_NIVEAU-2; j>=1; j--) new_niv[j]=new_niv[j-1];
      new_niv[0]=0;
      get_work(new_niv,NO);
      ok=NO;
      if (key==83) {
        x--;
        for (i=y; i>=0; i--) {
          for (j=x; j>=0; j--) {
            if (user_work[i][j].artcode[0]=='*') {ok=YES; x=j; y=i; break;}
          }
          if (ok) break;
          x=8-1;
        }
      }
      else {
        x++;
        for (i=y; i<6; i++) {
          for (j=x; j<8; j++) {
            if (user_work[i][j].artcode[0]=='*') {ok=YES; x=j; y=i; break;}
          }
          if (ok) break;
          x=0;
        }
      }
      if (ok) {
        sear_niv[MAX_NIVEAU-2]=(y+1)*16+(x+1);
        beep_fl=GOOD;
      }
      else beep_fl=BAD;
      get_work(sear_niv,NO);
    }
  }  
endsr:;
 if (type!=0) ConSelect(consave);
}

void CKasUSR::get_work(unsigned char *p_niveau, char erase)
{
  char *debug;
  int last, index, test, pos, x, y;
                                                                        
  zeros((char *)user_work,sizeof user_work);
  *(p_niveau+MAX_NIVEAU-1) = 0x11;
  last=find_niveau(p_niveau);
  index=last;
  FOREVER {
    debug = (char *)&user_list[index].key;
    test=memcmp(p_niveau,user_list[index].key,MAX_NIVEAU-1);
    if (test<0) break;
    pos=user_list[index].key[MAX_NIVEAU-1];
    if (pos && !test) {
      x=(pos/16)-1; y=(pos%16)-1;
      if (x<6 && y<8) {
        movmem(&user_list[index],&user_work[x][y],sizeof(user_work[0][0]));
        if (erase) {
          zeros((char *)&user_list[index],sizeof(user_list[0]));
        }
      }
    }
    if (index--==0) break;
  }
}
        
/*
void CKasUSR::put_work(unsigned char *p_niveau)
{
  int index, k, l;
                                                                        
  index=0;
  for (k=0; k<8; k++) {
    for (l=0; l<6; l++) {
      if (!test_used((char *)&user_work[l][k],sizeof(user_work[0][0]))) {
        while (!test_zero(&user_list[index],sizeof(user_list[0]))) {
          index++;
          if (index>=key_count) goto end // mvg nog na te kijken 
        }
        movmem(p_niveau,&user_work[l][k].key[0],MAX_NIVEAU-1);
        user_work[l][k].key[MAX_NIVEAU-1]=(l+1)*16+k+1;
        movmem(&user_work[l][k],&user_list[index++],sizeof(user_work[0][0]));
      }
    }
  }
  key_calc();
  end:;
}
 
void CKasUSR::key_calc(void)
{
  for (key_used=key_count-1; key_used>=0; key_used--) {
    if (user_list[key_used].key[MAX_NIVEAU-1]) break;
  }
}

int CKasUSR::test_zero(void *ss, int len)
{
  char *s;
  int ret;
 
  ret=YES; s=(char *)ss;
  while (len--) if (*s++) {ret=NO; break;}
  return ret;
}

int CKasUSR::test_used(char *s, int len)
{
  int ret;

  ret=YES;
  while (len--) if (*s++>' ') {ret=NO; break;}
  return ret;
}

wordt niet meer gebruikt ! */
 
int CKasUSR::find_niveau(unsigned char *p_niveau)
{
  int begin,last,ret,test;

  begin=0; last=key_used-1;
  FOREVER {
    test = (begin+last)/2;
    ret=memcmp(p_niveau,user_list[test].key,MAX_NIVEAU);
    if (ret>0) {
      last=test-1;
      if (last<begin) break;
    }
    else if (ret<0) {
      begin=test+1;
      if (begin>last) break;
    }
    else break;
  }
  return test;
}
 
void CKasUSR::cl_kasusr()
{
  long needed;

  needed=(long)key_count * key_size;
	if (needed) rlsml((char *)user_list,needed);
}
 
void CKasUSR::rd_kasusr(int line)
{
  const unsigned char intab[] = {  /* input convert table  intern'l keyb. -> JAMASCII */
 /*  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F          */
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,   /* 0X */
    16, 17, 18, 19, 20,151, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,   /* 1X */
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,   /* 2X */
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,   /* 3X */
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,   /* 4X */
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,   /* 5X */
    96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,   /* 6X */
   112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,   /* 7X */
   159,148,133,130,131,129,  0,132,135,136,134,140,139,138,  0,  0,   /* 8X */
     0,  0,  0,143,144,142,147,146,  0,  0,149,155,156,  0,  0,  0,   /* 9X */
   128,137,141,145,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* AX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* BX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* CX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* DX */
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* EX */
     0,  0,  0,  0,  0,  0,  0,  0,150,  0,  0,  0,  0,  0,152,  0};  /* FX */
  char *p, tmpbuf[100];
  int i, j, k, artlen_dif_;
  int fref;
  long len, size, needed;
 
  needed=(long)key_count * key_size;
  sprintf(&tmpbuf[0],"Reading KASUSR.DAT (count=%5d) ...",key_count);
  SplashText(&tmpbuf[0]);
  user_list=(struct keys *)getml(needed);
  if ((long)user_list == 0L) {
    tkdspnl("GETML voor KEYS werkt niet");
    kbchar();
    _moexit(0);
    exit(0);
  }
  p=(char *)user_list; len=needed;
  while (len--) *p++=0;
 
  fref=dopen("kasusr.dat",RDWRMODE);
  if (fref<0) goto end;
  len=dseek(fref,0L,2);
  if (len>needed) {
    tkdspnl("Teveel key's in KASUSR.DAT");
    kbchar();
    _moexit(0);
    exit(0);
  }
	else if(len<4) goto end; // lege of geen geldige file
  dseek(fref,0L,0);artlen_dif_=5-ARTCODE_LEN; // kasusr is VAST op 5 tekens 
  p = (char *) user_list;
  while (len) {
    size=len;
    if(size>key_size+artlen_dif_) size=key_size+artlen_dif_;
    // if (size>30000) size=30000;
    dread(fref,p,(int)size);
    p+=key_size;
    len-=size;
  }
  dclose(fref);

  for (key_used=key_count-1; key_used>=0; key_used--) {
    if (user_list[key_used].key[MAX_NIVEAU-1]) {
      key_used++;
      break;
    }
  }

	for (i=0; i<key_used; i++) {
	  for (j=0; j<TEKST_COUNT; j++) {
		  for (k=0; k<8; k++) {
        if (user_list[i].tekst[j][k]>0x7F) user_list[i].tekst[j][k]=intab[user_list[i].tekst[j][k]];
			}
		}
	}

  ExtraOptiesUsed=0;
	if (optiesgroep) {
		for (i=0; i<key_used; i++) {
			p=user_list[i].artcode;
			if (*p=='*' && *(p+1)>' ') {
				movmem(p+1,ExtraOpties[ExtraOptiesUsed].artcode,ARTCODE_LEN-1);
				for (j=0; j<ARTCODE_LEN-1; j++) {
					if (ExtraOpties[ExtraOptiesUsed].artcode[j]==0) break;
				}
				for (; j<ARTCODE_LEN; j++) ExtraOpties[ExtraOptiesUsed].artcode[j]=0;
				movmem(user_list[i].key+1,ExtraOpties[ExtraOptiesUsed].key,MAX_NIVEAU-1);
				ExtraOpties[ExtraOptiesUsed++].key[MAX_NIVEAU-1]=0;
			}
		}
  }
 end:;

  int consave=ConSelect(-1);
  ConStyle(CON_STYLE_NOBACKGROUND);
  cls();
  ConUsrRef=ConSelect(consave);
}


