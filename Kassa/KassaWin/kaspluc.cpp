// KasPLU.cpp: implementation of the CKasPLU class.
//
//////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4996)

// #define WINVER 0x0501  // was 500
// #define _WIN32_WINNT 0x0501  // was 500

#include "p:\jamacon\library\JamaConL.h"
#include "kashead.h"
#include "KasPLUc.h"

// #include "stdafx.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define KLEUR_FTOETS        RGB(0,127,0)
#define KLEUR_GRIJS         RGB(200,200,200)
#define KLEUR_TEDOEN        RGB(250,0,50)
#define KLEUR_VERWERKT      RGB(0,220,100)
#define KLEUR_PDA_ARTIKEL   RGB(250,100,100)
#define KLEUR_PDA_KLANT     RGB(50,175,150)
#define KLEUR_TITEL         RGB(255,200,100)
#define KLEUR_GROEN         RGB(0,220,100)
#define KLEUR_CYAAN         RGB(50,200,200)
#define KLEUR_ROOD          RGB(220,50,50)
#define KLEUR_OUDROOD       RGB(250,100,0)
#define KLEUR_GEEL          RGB(255,255,0)
#define KLEUR_LICHTBLAUW    RGB(200,250,225)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern int art_count, prx_count, ext_count, ean_count;

int CKasPLU::prx_ix;
static int FilterMode;
struct art_line *CKasPLU::artikel, CKasPLU::art_info;
struct _extra *CKasPLU::extra;

CKasPLU::CKasPLU()
{
  PromoPLUs="|";
	art_size=sizeof(artikel[0]);
  clncount=0;
  // alle pointers op NULL zetten zodat we bij RD_KASPLU maar 1 keer een malloc doen 
  SortIndex[0]=NULL;
  SortIndex[1]=NULL;
  SortIndex[2]=NULL;
  artikel=NULL; extra=NULL; ean_tab=NULL;
	prev_brwsfirst=0;
	prev_selected=0;
}

CKasPLU::~CKasPLU()
{
  free(SortIndex[0]);
  free(SortIndex[1]);
  free(SortIndex[2]);
  free(artikel); free(extra); free(ean_tab);


  cl_kasplu();
}

extern int def_digits;
extern char beep_fl;



int CKasPLU::search(char *search, int SortIx)
{
  int old_brwsfirst, brwsfirst=0, PlatformNr, inp_kar_, FindOff=0, old_screen,MaxArtUsed;
  char buf[100], find[100], findnetto[100];
  bool FirstSearch=true;
  int j, i, k, key, aantal, prevsel, x, y, attr, selected, findix,last_findix,old_findix,filterchanged_=NO;
  int begin,last,ret,test, testcurs, ix, mouse_vt_begin, mouse_hz_begin, mouse_hz_len, q_lin_scr;
 
  PlatformNr=PlatformType(0);MaxArtUsed=art_used;
  if(PlatformNr!=2) old_screen=ConSelect(PluConRef); 
  FilterMode=NO;filterchanged_=NO;
  CopyNettoChar(search,find,sizeof(artikel[0].naamnetto));
  if (SortIx<0 || SortIx>1){prev_brwsfirst=0;selected=-1;	prev_selected=-1; SortIx=1;}
  if(PlatformNr==2){ 
    KeyboardSet(TRUE);
    cls();
    if(vdmax_h!=30 || vdmax_v!=10) ConSizeWindow(30,10);
  
    q_lin_scr=7;mouse_vt_begin=1;mouse_hz_begin=1; mouse_hz_len=30; 
    disp_panel(0,0,30,14,0,RGB(255,255,255));
    disp_panel(0,0,30,1,0,RGB(10,255,255));
    vdposp(1,0); attribute=-1;
    disp_key(vdmax_h-16,vdmax_v-2,8,2,0x17);
    disp_key(vdmax_h-8,vdmax_v-2,8,2,0x18);
    disp_key(0,vdmax_v-2,7,2,0x16);
    disp_key(7,vdmax_v-2,7,2,0x70);
  }
  else{
		disp_clr(0,0,80,25);
    q_lin_scr=23;mouse_vt_begin=1;mouse_hz_begin=13; mouse_hz_len=55;
    disp_panel(12,0,58,25,PANEL_HOR_SMALLER | PANEL_WITH_EDGE, RGB(255,255,0));

    disp_key(70, 0,10,2,22);
    disp_key(70, 2,10,3,23);
    disp_key(70,22,10,3,24);
    disp_key( 0, 0,12,2,112);
    buf[0]=' '; buf[2]=' '; buf[3]=0;

    for (j=0; j<26; j++) {
      y = 7 + (j/3) * 2;
      x = (j%3) * 4; 
      buf[1]='A'+j;
      disp_ikey(x,y,4,2,2000+buf[1],buf);
    }

    for (j=9; j>=0; j--) {
      y = 15 + ((j-9)/2) *2;
      x = 70 + (j%2) * 5;
      buf[1]='0'+j;
      disp_ikey(x,y,5,2,2000+buf[1],buf);
    }
    disp_key(70,18,10,2,112);
    disp_key(70,20,10,2,114);
    buf[1]=' ';
    disp_ikey(8,23,4,2,2000+' ',buf);
		disp_key(0,3,6,2,58);
    disp_key(6,3,6,2,83);
		if(!FilterMode) disp_ikey(0,5,12,2,5002,"zoek in naam",KLEUR_FTOETS);
		else disp_ikey(0,5,12,2,5002,"zoek",KLEUR_FTOETS);
    disp_key(70,5,10,2,83);
  }
   
  for (findix=0; findix<sizeof(find); findix++) if (find[findix]==0) break;
  if(findix==0) {
    if(prev_brwsfirst){brwsfirst=prev_brwsfirst;SortIx=prev_sortix;}
    else{brwsfirst=0;SortIx=1;}
  }
  selected=-1; old_findix=findix-1; 
  FOREVER {
    if (findix!=old_findix || filterchanged_) {
			MaxArtUsed=art_used; filterchanged_=NO;
      if(findix>0) {
				if(FilterMode){
					SortIx=2; MaxArtUsed=MakeSpecSortTabel(find);
					brwsfirst=0;
				}
				else{
					if((find[0]>='0' && find[0]<='9') || find[0]=='.') {
						SortIx=0; // sorteren volgens kode 
					}
					else SortIx=1; // sorteren volgens naam 
					FindOff=0;
					if (find[0]=='.') FindOff=1;
					for (k=findix; k<sizeof(find); k++) find[k]=0;
					CopyNettoChar(find+FindOff, findnetto, findix-FindOff);
					begin=0; last=art_used-1; ix=-1;
					FOREVER {
						test = (begin+last)/2;
						if (SortIx==0) ret=memcmp(find+FindOff,artikel[SortIndex[SortIx][test]].code,ARTCODE_LEN);
						else ret=memcmp(findnetto,artikel[SortIndex[SortIx][test]].naamnetto,ARTNAAM_LEN);
						if (ret<0) {
							last=test-1;
							if (begin>last) {
								testcurs=test-1;
								if (testcurs<0) testcurs=0;
								break;
							}
						}
						else if (ret>0) {
							begin=test+1;
							if (begin>last) {
								testcurs=test+1;
								if (testcurs>=art_used) testcurs=art_used-1;
								break;
							}
						}
						else {
							selected=ix=test;
							if (FirstSearch) goto endsr;
							break;
						}
					}
					if (ret!=0) {
						for (k=0; k<(int)sizeof(find)-FindOff; k++) {
							if (find[k+FindOff]==0) {
								test=testcurs;
								break;
							}
							if (SortIx==0 && find[k+FindOff]!=artikel[SortIndex[SortIx][testcurs]].code[k]) break;
							if (SortIx==1 && findnetto[k]!=artikel[SortIndex[SortIx][testcurs]].naamnetto[k]) break;
						}
						selected=ix=test;
					}
					brwsfirst=ix;
				}
			}
      else {
				if(FilterMode){memcpy((char *)&SortIndex[2][0],(char *)&SortIndex[1][0],sizeof SortIndex[0]);MaxArtUsed=art_used;}
				brwsfirst=prev_brwsfirst;
				selected=prev_selected;
      }
      if (brwsfirst<0) brwsfirst=0;
      if (brwsfirst>=art_used) brwsfirst=art_used-1;
    }
    old_brwsfirst=brwsfirst; old_findix=findix; FirstSearch=false;
   
    aantal=q_lin_scr;
    if ((brwsfirst+aantal)>MaxArtUsed) aantal=MaxArtUsed-brwsfirst;
    for (j=0; j<aantal; j++) {
      p_art=&artikel[SortIndex[SortIx][brwsfirst+j]];
      if ((j+brwsfirst)==selected) attr=8; else attr=2;
      for (i=0; i<sizeof(buf); i++) buf[i]=' ';
      if (PlatformNr==2) {
        k=0;
        if (SortIx==0) { // codenummer
          for (i=0; i<sizeof (p_art->code); i++) {
            if (p_art->code[i]==0) break;
            buf[i]=p_art->code[i];
					}
					k=ARTNAAM_LEN;
								if (k>20) k=20;
								for (i=0; i<k; i++) {
									if (p_art->naam[i]==0) break;
									buf[i+ARTCODE_LEN+1]=p_art->naam[i]; 
					}
				}
        else {
          k=ARTNAAM_LEN;
          if (k>30) k=30;
          for (i=0; i<k; i++) {
            if (p_art->naam[i]==0) break;
            buf[i]=p_art->naam[i]; 
					}
				}
        buf[vdmax_h]=0;         
      }
      else {
        for (i=0; i<ARTCODE_LEN; i++) {
          if (p_art->code[i]==0) break;
          buf[i]=p_art->code[i];
				}
        for (i=0; i<ARTNAAM_LEN; i++) {
          if (p_art->naam[i]==0) break;
          buf[i+ARTCODE_LEN+1]=p_art->naam[i]; 
				}
        conv_getal(p_art->prijs[CKasPLU::prx_ix],buf+ARTCODE_LEN+ARTNAAM_LEN+1,8,0,def_digits);
        conv_getal(p_art->st_prijs,buf+ARTCODE_LEN+ARTNAAM_LEN+8+1,8,0,def_digits);
        buf[ARTCODE_LEN+ARTNAAM_LEN+8+8+1]=0;
      }
			if (p_art->ex_text[0]) attr=15;
      disp_vid(mouse_hz_begin,mouse_vt_begin+j,buf,attr);
    }

    for (i=0; i<sizeof(buf); i++) buf[i]=' ';
    buf[ARTCODE_LEN+ARTNAAM_LEN+16+1]=0;
    buf[vdmax_h]=0;
    for (j=aantal; j<q_lin_scr; j++) {
      disp_vid(mouse_hz_begin,mouse_vt_begin+j,buf,2);
    }

    prevsel=selected; old_brwsfirst=brwsfirst;
    
    if(PlatformNr==2) vdposp(0,1); else vdposp(3,1);
    find[findix]=0;
    for (i=0; i<20; i++) {
			if (i<findix) buf[i]=find[i];
			else buf[i]=' ';
    }

    buf[i]=0;
    if(PlatformNr==2){
      tkdsp(buf);
    }
    else {
			j=findix-10; 
			if(j<0) j=0; else if(j>10) j=10;
			vdposp(2,1);
      for (i=0+j; i<j+10; i++) vdchar(buf[i]);
    }
    if(PlatformNr==2) vdposp(0,1+findix);
    else {
			j=findix-10; if(j<0) j=findix; else j=10; vdposp(2,1+j);
    }
    curson(2);
    key=kbchar();
    cursof();
    inp_kar_=0;
    if (key&0xFFFF0000) {
      key/=0x10000;
      if (key>=0 && key<=9) key='0'+key;
      else key=-key; // keycoon = negatieve key
    }
    
    if(key>=0x20 && key<=0x7D) {
      inp_kar_=key; key=0;
      if (inp_kar_>='a' && inp_kar_<='z')  inp_kar_+='A'-'a';
    }
    else if(key>255) key=key/256;
    if(key==101){selected=-1; goto endsr;}
    switch(key){
      case   -58 : // wis/clear
            zeros(find,sizeof find); findix=0;selected=-1; old_findix=findix-1; 
						brwsfirst=0;prev_brwsfirst=0;selected=-1;
						FilterMode=NO;SortIx=1;disp_ikey(0,5,12,2,5002,"zoek in naam",KLEUR_FTOETS);
            break;
      case -83  : // backspace <<
      case   3  :
            if (findix>0) findix--;
            find[findix]=0;
            break;
      case   8  :
            if(selected==-1) selected=brwsfirst;   // pijl up
            else selected--;
            if(selected<0) selected=0;
            if(selected<brwsfirst) brwsfirst-=(q_lin_scr-1);
            break;
      case  9   :
            if(selected==-1) selected=brwsfirst;  // pijl dn
            else selected++;
            if(selected>=MaxArtUsed) selected--;
            if(selected>=brwsfirst+aantal) brwsfirst+=(aantal-1);
            break;
      case  10  : brwsfirst=0; break;  // home
      case  11  : brwsfirst=MaxArtUsed; break; // end 

      case  18  :
      case 108  :
      case -0x70: if (selected>=0) goto endsr; break;

      case -114  :
						if (selected>=0) k=SortIndex[SortIx][selected];
									SortIx++; findix=0; zeros(find,sizeof find); old_findix=0;
									if (SortIx>1) SortIx=0; // enkel alfa of kode 
									brwsfirst=0;
									if (selected>=0){
										for (selected=0; selected<MaxArtUsed; selected++) if (k==SortIndex[SortIx][selected]) break;
										if(selected>=MaxArtUsed) selected=0;
										brwsfirst=selected;
						}
            break;
      case 251  :
            k=-1;                // left mouse 
            if(mspos_h>=mouse_hz_begin && mspos_h<mouse_hz_begin+mouse_hz_len) k=mspos_v-mouse_vt_begin; 
            if(k>=0 && k<q_lin_scr && brwsfirst+k<MaxArtUsed) {
              if(selected==brwsfirst+k) goto endsr;   // double click
              selected=brwsfirst+k;
						}
						break;
      case 252  :
            k=-1;   // right mouse 
						if(mspos_h>=mouse_hz_begin && mspos_h<mouse_hz_begin+mouse_hz_len) k=mspos_v-mouse_vt_begin; 
						if(k>=0 && k<q_lin_scr && brwsfirst+k<MaxArtUsed) {
              selected=brwsfirst+k;
              goto endsr;
            }
	    break;
      case -0x16 : selected=-1; goto endsr; break;
      case  12  :
      case -0x17: brwsfirst-=(q_lin_scr-1); break; // keycoon pgup
      case  13  :
      case -0x18: brwsfirst+=(q_lin_scr-1); break; // keycoon pgdn
			case -5002: if(!FilterMode) FilterMode=YES; else FilterMode=NO;
						      if(!FilterMode) disp_ikey(0,5,12,2,5002,"zoek in naam",KLEUR_FTOETS);
		              else disp_ikey(0,5,12,2,5002,"zoek",KLEUR_FTOETS);
          				filterchanged_=YES;last_findix=0;brwsfirst=0;selected=-1;
									break;
      default   : break;
    }
    if (brwsfirst >= MaxArtUsed) brwsfirst=MaxArtUsed-q_lin_scr;
    if (brwsfirst<0) brwsfirst=0;
    if(inp_kar_ && findix<20) find[findix++]=inp_kar_;
    if(old_brwsfirst!=brwsfirst && key!=8 && key!=9) selected=brwsfirst;
  }
 endsr:;
  if (selected>=0) {
		if(SortIx==2){prev_selected=0;prev_brwsfirst=0;prev_sortix=1;} // na zoeken in naam, default alfa terugkomen
		else{prev_selected=selected; prev_brwsfirst=brwsfirst; prev_sortix=SortIx;}
    selected=SortIndex[SortIx][selected];
    movmem(&artikel[selected],&art_info,sizeof(art_info));
  }
  if(PlatformNr!=2) ConSelect(old_screen);
  if(PlatformNr==2){ KeyboardSet(FALSE);}
  return selected;
}

int CKasPLU::MakeSpecSortTabel(char *pfind_) // voor zoeken in stuk omschrijving
{
	 CString cfind_,cnaam_;
	 int k,max_=0;;
	 	 
   zeros((char *)&SortIndex[2][0],sizeof SortIndex[0]);
	 cfind_=CString(pfind_,12); cfind_.MakeUpper(); cfind_.Trim();
	 	
	 for(k=0;k<art_used;k++){
		 cnaam_=CString(artikel[SortIndex[1][k]].naam,ARTNAAM_LEN);cnaam_.MakeUpper(); cnaam_.Trim();
		 if(cnaam_.Find(cfind_,0)>=0) SortIndex[2][max_++]=SortIndex[1][k];
	 }
   return max_;
}

int CKasPLU::plu_req(char *ss, int len)
{
  char *s;
  int ix, j;
  char code[sizeof(artikel[0].code)+1];
 
  j=0; s=ss;
  while (j<sizeof(artikel[0].code)) {
    if (*s==0 || len==0) break;
    if (*s>' ') {
      code[j]=*s; j++;
    }
    *s++; len--;
  }
  while (j<sizeof(artikel[0].code)) code[j++]=0;
  ix=find_plu(code);
  if (ix>=0) {
    movmem(&artikel[ix],&art_info,sizeof(art_info)); last_ix=ix;
    movmem(ss,last_buf,len);
  }
  return ix;
}

void CKasPLU::plu_upd(int ix)
{
  if (ix<0) ix=art_used++;
  movmem(&art_info,&artikel[ix],sizeof(art_info));
  Sort(1);
}

int CKasPLU::find_plu(char *plu)
{
  int begin,last,ret,test, ix;
                                                        
  begin=0; last=art_used-1; ix=-1;
  FOREVER {
    test = (begin+last)/2;
    ret=memcmp(plu,artikel[SortIndex[0][test]].code,sizeof(artikel[0].code));
    if (ret<0) {
      last=test-1;
      if (last<begin) break;
    }
    else if (ret>0) {
      begin=test+1;
      if (begin>last) break;
    }
    else {
      ix=SortIndex[0][test];
      break;
    }
  }
  if (ix>=0) {
    movmem(&artikel[ix],&art_info,sizeof(art_info));
  }
  return ix;
}



int CKasPLU::get_plu(int ix)
{
  if (ix>=0 && ix<art_used) {
    movmem(&artikel[ix],&art_info,sizeof(art_info));
  }
  else ix=-1;
  return ix;
}


int CKasPLU::_ccompare(char *s1,char *s2, int dum)
{
  int i;
  UNALIGNED int *rec1, *rec2;
  char *c1, *c2;
                
  rec1=(int *)s1; rec2=(int *)s2;
  c1=artikel[*rec1].code; c2=artikel[*rec2].code;                                  
  for (i=0; i<ARTCODE_LEN; i++) {
    if (*c1<*c2) return -1;
    else if (*c1>*c2) return 1;
    else {c1++; c2++;}
  }
  return 0;
}

int CKasPLU::lcompare(char *s1, char *s2, int dum)
{
  long *l1, *l2;

  l1=(long *)s1; l2=(long *)s2;
  if (*l1<*l2) return -1;
  if (*l1>*l2) return 1;
  return 0;
}

int CKasPLU::_ncompare(char *s1, char *s2, int dum)
{
  int i;
  UNALIGNED int *rec1, *rec2;
  char *n1, *n2;

  rec1=(int *)s1; rec2=(int *)s2;
  n1=artikel[*rec1].naamnetto; n2=artikel[*rec2].naamnetto;
  for (i=0; i<ARTNAAM_LEN; i++) {
    if (*n1<*n2) return -1;
    else if (*n1>*n2) return 1;
    else {n1++; n2++;}
  }
  return 0;
}


void CKasPLU::cl_kasplu()
{
/*

  long art_needed, needed;
  int i;

  art_needed=(long)art_count * art_size;
	if (art_needed) rlsml((char *)artikel,art_needed);
  for (i=0; i<3; i++) {
    needed=sizeof(int)*art_count;
    if (needed && SortIndex[i]!=NULL) rlsml((char *)SortIndex[i],needed);
  }
  needed=(long)ext_count * sizeof(struct _extra);
	if (needed) rlsml((char *)extra,needed);
  needed=(long)ean_count * sizeof(int);
  if (needed) rlsml((char *)ean_tab, needed);
*/
}

void CKasPLU::rd_kasplu(int line)
{
  char *p;
  long len, art_needed, needed;
  int fref, i, j;
 
  art_needed=(long)art_count * art_size;
  if(PlatformType(0)!=2){
    sprintf((char *)_read_buf,"Reading KASPLU.DAT (Count=%5d) ...",art_count);
    SplashText((char *)_read_buf);
  }
  if(artikel==NULL) artikel=(struct art_line *)malloc(art_needed);
  if(artikel==NULL) {
    tkdspnl("MALLOC voor ARTIKELEN werkt niet");
    kbchar(); _moexit(0); exit(0);
  }
  p=(char *)artikel; len=art_needed;
  while (len--) *p++=0;

  for (i=0; i<3; i++) {
    needed=sizeof(int)*art_count;
    if(SortIndex[i]==NULL) SortIndex[i]=(int *)malloc(needed);
    if (SortIndex[i]==NULL) {
      tkdspnl("MALLOC voor INDEXEN werkt niet");
      kbchar(); _moexit(0); exit(0);
    }
  }

  p=(char *)malloc(32100L); // 100 bytes teveel nemen, hij zet er zeker 1 byte achter. Gevonden met VC++
  if (p == NULL) {
    tkdspnl("MALLOC voor BUFFER bij KASPLU werkt niet");
    kbchar(); _moexit(0); exit(0);
  }

  buf_large=(unsigned char *)p; buf_len=32000;
 
  fref=dopen("kasplu.dat",RDWRMODE);
  if (fref<0) goto no_plu;
  art_used=0; buf_rdptr=0; buf_used=0;
  while (art_used < art_count) {
    if (_read_line(fref)) break;
    if (parse_line()) {
		  if (artikel[art_used].ex_text[0]  || artikel[art_used].PromoFormule) AddPromoPlu(artikel[art_used].code);
      CopyNettoChar(artikel[art_used].naam,artikel[art_used].naamnetto,sizeof(artikel[0].naamnetto));
      art_used++;
    }
  }
  if (art_used==art_count) {
    tkdspnl("Too many items in KASPLU");
    kbchar();
    _moexit(0);
    exit(0);
  }

  dclose(fref);

  if(PlatformType(0)!=2){
    sprintf((char *)_read_buf,"Sorting KASPLU.DAT (Used=%5d) ...",art_used);
    SplashText((char *)_read_buf);
  }
  for (i=0; i<art_count; i++) SortIndex[0][i]=SortIndex[1][i]=SortIndex[2][i]=i;
  Sort(1);
 no_plu:;
  
	if (GetFileAttributes("KasPluEx.DAT")!=INVALID_FILE_ATTRIBUTES) ext_count+=20000;

  if (ext_count) {
    if(PlatformType(0)!=2) SplashText("Reading KASEXT.DAT ...");
    needed=(long)ext_count * sizeof(struct _extra);
    if(extra==NULL) extra=(struct _extra *)malloc(needed);
    if (extra == NULL) {
      tkdspnl("MALLOC voor EXTRA struct werkt niet");
      kbchar(); _moexit(0); exit(0);
    }
  }
	ext_used=0; buf_rdptr=0; buf_used=0;

  fref=dopen("KASEXT.DAT",RDWRMODE);
  if (fref>=0) {
		while (ext_used < ext_count) {
			if (_read_line(fref)) break;
			if (parse_extra()) ext_used++;
		}
		if (ext_used==ext_count) {
			tkdspnl("Teveel artikelen in KASEXT");
			kbchar();
			_moexit(0);
			exit(0);
		}

		dclose(fref);
	}

  fref=dopen("KasPluEx.dat",RDWRMODE);
  if (fref>=0) {
		struct _extra *p_ext;
    buf_rdptr=0; buf_used=0;
		while (ext_used < ext_count-2) {
			if (_read_line(fref)) break;
			parse_line();
			if (artikel[art_used].ean[0]) {
				p_ext=&extra[ext_used];
				p_ext->plu_ix=plu_req(artikel[art_used].code,ARTCODE_LEN);
				p_ext->stuks_fl=NO;
				memcpy(p_ext->ean,artikel[art_used].ean,sizeof(extra[0].ean));
				if(p_ext->plu_ix>=0) ext_used++;
			}
			if (artikel[art_used].ean_st[0]) {
				p_ext=&extra[ext_used];
				p_ext->plu_ix=plu_req(artikel[art_used].code,ARTCODE_LEN);
				p_ext->stuks_fl=YES;
				memcpy(p_ext->ean,artikel[art_used].ean_st,sizeof(extra[0].ean));
				if(p_ext->plu_ix>=0) ext_used++;
			}
		}
		if (ext_used>=ext_count) {
			tkdspnl("Teveel artikelen in KASEXT");
			kbchar();
			_moexit(0);
			exit(0);
		}
		dclose(fref);
	}
	 
  fref=dopen("kasclean.dat",RDWRMODE);
  clncount=0;
  if (fref>=0) {
    buf_used=0; buf_rdptr=0;
    while (clncount<MAXCLN) {
      if (_read_line(fref)) break;
      parse_pos=0;
      cln[clncount].pos=(long)get_getal();
      cln[clncount].unit=(long)get_getal();
      cln[clncount++].prx=(float)get_getal();
    }
    dclose(fref);
    jsort(&cln[0].pos,clncount,sizeof(struct s_cln),(int(*)(char *, char *, int))CKasPLU::lcompare);
  }
 
  free(p); // buffer geheugen direct terug vrijgeven 
 
  if(PlatformType(0)!=2) SplashText("Sorting EAN-numbers ...");
  ean_count=art_count*2;
  needed=(long)ean_count * sizeof(int);
  if(ean_tab==NULL) ean_tab=(int *)malloc(needed);
  if (ean_tab == NULL) {
    tkdspnl("GETML voor EAN-TAB werkt niet");
    kbchar(); _moexit(0); exit(0);
  }
  p_art=&artikel[0]; ean_used=0;
  for (i=0; i<art_used; i++) {
    for (j=0; j<sizeof(artikel[0].ean); j++) {
      if (p_art->ean[j]) {
        ean_tab[ean_used++]=i*2;
        break;
      }
    }
    for (j=0; j<sizeof(artikel[0].ean_st); j++) {
      if (p_art->ean_st[j]) {
        ean_tab[ean_used++]=i*2+1;
        break;
      }
    }
    p_art++;
  }
  for (i=0; i<ext_used; i++) {
    ean_tab[ean_used++]=200000+i;
  }
  Sort(2);

  int plusave=ConSelect(-1);
  if(PlatformType(0)!=2)  ConStyle(CON_STYLE_NOBACKGROUND); // niet bij PDA
  cls();
  PluConRef=ConSelect(plusave);
}

void CKasPLU::AddPromoPlu(char *plu)
{
  if (*plu) {
		char code[ARTCODE_LEN+1];
    memcpy(code,plu,ARTCODE_LEN);
		code[ARTCODE_LEN]=0;
  	PromoPLUs+=code;
		PromoPLUs+='|';
	}
}

void CKasPLU::Sort(int type) {
  if (type==1) {
    jsort(SortIndex[0],art_used,sizeof(int),(int(*)(char *, char *, int))CKasPLU::_ccompare); 
    jsort(SortIndex[1],art_used,sizeof(int),(int(*)(char *, char *, int))CKasPLU::_ncompare); 
  }
  else if (type==2) {
    jsort(ean_tab,(long)ean_used,sizeof(int),(int(*)(char *, char *, int))CKasPLU::_ecompare);
  }
}

int CKasPLU::get_string(char *to, int _max)
{
  unsigned char byte;
  int i, empty=YES;
 
  for (i=parse_pos; i<sizeof(_read_buf); i++) {
    byte = _read_buf[i];
    if (byte=='\0') break;
    if (byte=='|') {i++; break;}
    if (byte>=' ' && _max>0) {
      if (byte>' ') empty=NO;
      *to++=byte; _max--;
    }
  }
  parse_pos=i;
  while (_max-->0) *to++='\0';
  return empty;
}

double CKasPLU::get_getal(void)
{
  char reg_kom,byte,min_sign=NO;
  int i, j, fract, reg_da;
  double reg;
                                                
  reg_kom=NO; reg_da=0; reg=0;
  for (i=parse_pos; i<sizeof(_read_buf); i++) {
    byte = _read_buf[i];
    if (byte=='\0') break;
    if (byte=='|') {i++; break;}
 
    if (byte>='0' && byte<='9') {
      if (!reg_kom) {
        reg*=10; reg+=(byte-'0');
      }
      else if (reg_kom) {
        j=reg_da; fract=10; while (j--) fract*=10;
        reg+=(double)(byte-'0')/fract;
        reg_da++;
      }
    }
    else if (byte=='.') reg_kom=1;
		else if (byte==',') reg_kom=1;
    else if (byte=='-') min_sign=YES;
  }
  if (min_sign) reg=-reg;
  parse_pos=i;
  return reg;
}
 
int CKasPLU::parse_extra(void)
{
  char code[ARTCODE_LEN], empty_code, empty_ean;
  static struct _extra *p_ext;
 
  parse_pos=0;
  p_ext=&extra[ext_used];
  empty_code=get_string(code,ARTCODE_LEN);
  p_ext->plu_ix=plu_req(code,ARTCODE_LEN);
  p_ext->stuks_fl=(char)get_getal();
  empty_ean=get_string(p_ext->ean,ARTEAN_LEN);
  if (empty_code || empty_ean || p_ext->plu_ix<0) return NO;
  return YES;
}
 
int CKasPLU::parse_line(void)
{
  char prijs_used, empty_code, empty_naam, buf_[20];
  int j, dd, mm, jj;
  unsigned dttoday_, dt_pbeg_ = 0, dt_pend_ = 0;

  parse_pos = 0;
  p_art = &artikel[art_used];
  empty_code = get_string(p_art->code, sizeof(artikel[0].code)); // A
  empty_naam = get_string(p_art->naam, sizeof(artikel[0].naam)); // B
  p_art->groep = (int)(get_getal() + .5); // C
  p_art->btw = (float)get_getal(); // D
  prijs_used = NO;
  for (j = 0; j < prx_count; j++) { // bij 5 prijzen 40125 : E-H
	p_art->prijs[j] = (float)get_getal();
	if (p_art->prijs[j]) prijs_used = YES;
  }
  p_art->st_prijs = (float)get_getal(); // I
  get_string(p_art->code_l, sizeof(artikel[0].code_l)); // J
  get_string(p_art->code_lst, sizeof(artikel[0].code_lst));// K
  p_art->st_verp = (int)(get_getal() + .5);// L
  get_string(&p_art->promo, sizeof(artikel[0].promo));// M
  get_string(p_art->ean, ARTEAN_LEN);// N
  get_string(p_art->ean_st, ARTEAN_LEN);// O
  p_art->punten = (float)get_getal();// P
  p_art->punten_st = (float)get_getal();// Q
  get_string((char *)&p_art->ex_text, sizeof(artikel[0].ex_text));// R
  get_string((char *)&p_art->alt_code, sizeof(artikel[0].alt_code));  // S kol 19 : code P&T voor Freedelity

  if (get_string(buf_, 20) == NO) { // T datum nieuwe promotie/ einde promotie
	zeros(&buf_[10], 5);
	movmem(&buf_[0], &buf_[10], 2); dd = val(&buf_[10]);
	movmem(&buf_[3], &buf_[10], 2); mm = val(&buf_[10]);
	movmem(&buf_[6], &buf_[10], 2); jj = val(&buf_[10]); jj += 2000;
	dt_pbeg_ = datejd(jj, mm, dd);
  }

  if (get_string(buf_, 20) == NO) { // U einddatum nieuwe promotie/ einde promotie
	zeros(&buf_[10], 5);
	movmem(&buf_[0], &buf_[10], 2); dd = val(&buf_[10]);
	movmem(&buf_[3], &buf_[10], 2); mm = val(&buf_[10]);
	movmem(&buf_[6], &buf_[10], 2); jj = val(&buf_[10]); jj += 2000;
	dt_pend_ = datejd(jj, mm, dd);
  }
  dttoday_ = dateget();
  if (dt_pbeg_ == 0 || dt_pend_ == 0 || dt_pbeg_ > dttoday_ || dt_pend_ < dttoday_) { // pointer in file verder zetten
	for (j = 0; j < prx_count; j++) get_string(buf_, 1); // nieuwe promoprijzen
	get_string(buf_, 1);// nieuwe promoprijzen
	get_string(buf_, 1);// nieuwe promoprijzen
	get_string(buf_, 1);// nieuwe promopunten
	get_string(buf_, 1);// nieuwe promopunten stuks
	get_string(buf_, 1);// nieuwe promotekst
  }
  else { // V
	prijs_used = NO;
	for (j = 0; j < prx_count; j++) { // V..Z nieuwe promoprijzen
	  p_art->prijs[j] = (float)get_getal();
	  if (p_art->prijs[j]) prijs_used = YES;
	}
	p_art->st_prijs = (float)get_getal();// nieuwe promoprijzen
	get_string(&p_art->promo, sizeof(artikel[0].promo));// AA promo-code
	p_art->punten = (float)get_getal();// AB promo-punten bak
	p_art->punten_st = (float)get_getal();// AC promo-punten stuk
	get_string((char *)&p_art->ex_text, sizeof(artikel[0].ex_text));// AD promo-tekst 
  }
    
  if (!(dt_pbeg_ == 0 || dt_pend_ == 0 || dt_pbeg_ > dttoday_ || dt_pend_ < dttoday_)) { // AE - AX promo op datum, directe promo overslaan 
	for (j = 0; j < 10; j++) get_string(buf_, 1); // huidige promo overslaan
  }
  p_art->PromoFormule = (int)get_getal();// AE/AO Promoformule
  get_string((char *)&p_art->PromoBakFles,1);// AF/AP  promo bak/fles
  for (j = 0; j < 4; j++) { // AG-AJ / AQ-AT
	if(j==1 && p_art->PromoFormule==8) get_string((char *)&p_art->PromoGratisArtCode, ARTCODE_LEN);// promo gratis artikel
	else p_art->PromoFormuleGetallen[j] = (float)get_getal();// Promoformule getallen
  }
  get_string((char *)&p_art->PromoGratisTekst, ARTNAAM_LEN);// AK/AU promo gratis tekst
  p_art->PromoGroepsCode = (long)get_getal();// AL/ AV Promo groepscode
  p_art->MaxPromoPerTicket = (int)get_getal();//  AM/ AW Max. Promo per ticket
  get_string(buf_, 1);// AN/ AX dummy
  if (dt_pbeg_ == 0 || dt_pend_ == 0 || dt_pbeg_ > dttoday_ || dt_pend_ < dttoday_) { // directe promo,  promo op datum overslaan 
	for (j = 0; j < 10; j++) get_string(buf_, 1); // huidige promo overslaan
  }

  if (!p_art->groep && !p_art->btw && !prijs_used) return NO;
  else if (empty_naam || empty_code) return NO;
  else return YES;
}

int CKasPLU::_read_line(int fref)
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
  int i,byte;
 
  for (i=0; i<(sizeof(_read_buf));) {
    if (buf_rdptr==buf_used) {
      buf_used=dread(fref,buf_large,buf_len); buf_rdptr=0;
      buf_large[buf_used]=0;
      if (buf_used==0) {
        if (i>0) break;
        else return YES; /* geen info meer */
      }
    }
    byte=buf_large[buf_rdptr++];
    if (byte>=128) {
      if (byte==128) byte=0x9F;
      else byte=intab[byte];
    }
    if (i>0) {
      if (byte=='\n') break; /* return alleen niet-empty lines */

      if (byte>=' ') _read_buf[i++]=byte;
    }
    else {
      if (byte>' ') _read_buf[i++]=byte; /* skip leading blanks */
    }
  }
  _read_buf[i]=0;
  return NO;
}

void CKasPLU::CopyNettoChar(char *s, char *d, int len)
{
  int i;
  unsigned char byt;

  for (i=0; i<len; i++) {
    byt=*s++;
    if (!byt) break;
		if (byt>=128) {
		  if (byt<=131) byt='A';
			else if (byt==132) byt='C';
			else if (byt<=136) byt='E';
			else if (byt<=140) byt='I';
			else if (byt<=144) byt='O';
			else if (byt<=149) byt='U';
		}
    if (byt>='a' && byt<='z') byt+='A'-'a';
    if ((byt>='A' && byt<='Z') || (byt>='0' && byt<='9')) *d++=byt;
  }
  *d=0;
}

 
/* laatste */

//static stuks_fl;
 
int *ean_tab, ean_used, ean_count;

extern struct _extra *extra;



/*
	Barcode-lezer : STX <DATA> ETX
									
	ofwel           <DATA> CR (kan alleen serieel, COM : 11 -14
									
	Als data begint met :
									
	      cijfer : dan is het een EAN nummer.
									
	      $-teken: dan is het een commando specifiek voor barcodes
		       Het volgende teken is een commando (0-9,A-Z).
									
			    0 -> Overrule BAK/FLES naar BAK  (hoewel fles)
			    1 -> Overrule BAK/FLES naar FLES (hoewel bakcode)
									
	      %-teken: Dan is het een KEY-COON die men wenst uit te voeren.
		       De twee volgende tekens zijn HEXADECIMAAL de toetscode.
									
	In de <DATA> string kan of een EAN nummer zijn, ofwel een keten van
	commando's (bv. $1$A%1E%01)
*/



/*
int bc_process(int exec_rout)
{
  char key_buf[20];
  int pos, len, key, key_touched, parm, special,i;
  int nr, punten;

  len=0; key_touched=0; parm=-1;
  if (!bc_no_stxetx) bc_get(); // to skip STX 
  FOREVER {
    key=bc_get();
    if (key==-1) return 0; // time-out, om kas niet te blokkeren 
    if (bc_no_stxetx) {
      if (key==0x0D) break;
    }
    else {
      if (key==0x03) break;
    }
    if (len<sizeof(key_buf)) key_buf[len++]=key;
  }
  key_buf[len]=0;

  nr=-1;
  if (len==5 && stcd_i(key_buf,&i)==5 && i<krt_used) nr=i;
  else if (len==13 && key_buf[0]=='2' && key_buf[1]=='4') {
    for (i=0; i<5; i++) {
      if (key_buf[2+i]!=krt_lead[i]) break;
    }
    if (i==5) {
      key_buf[7+5]=0;
      stcd_i(key_buf+7,&punten);
    }
    p_vrk->lijn[p_vrk->used].groep=GRP_PUNTEXTRA;
    p_vrk->lijn[p_vrk->used].aantal=(float)punten;
    p_vrk->punten[p_vrk->used]=(float)punten;
    adj_lijn(p_vrk->used++);
    art_calc(NO); disp_fl=YES;
    return 0;
  }
  else if (len==13 && key_buf[0]=='2' && key_buf[1]=='5') {
    for (i=0; i<5; i++) {
      if (key_buf[2+i]!=krt_lead[i]) break;
    }
    if (i==5) {
      key_buf[7+5]=0;
      stcd_i(key_buf+7,&nr);
    }
  }    
  if (nr>=0) {
    p_vrk->krtnr=nr;
    dsp_krtinfo();
    return 0;
  }
  
  pos=0;
  while (pos<len) {
    if (key_buf[pos]>='0' && key_buf[pos]<='9' && exec_rout) {
      special=NO;
      if (weeg_type) {
        special=weeg_type;
        if (weeg_type==3) special=1;
        for (i=0; i<3; i++) {
          if (weeg_lead[i]==0) break;
          else if (weeg_lead[i]!=key_buf[pos+i]) {
            special=NO;
            break;
          }
        }
      }
      if (special) {
        if (special==2) {
          for (i=0; i<weeg_elen; i++) {
            if (i==(weeg_elen-weeg_edig)) numkey(10);
            numkey(key_buf[pos+weeg_epos+i]-'0');
          }
          maal(0);
        }
        for (i=0; i<weeg_clen; i++) numkey(key_buf[pos+weeg_cpos+i]-'0');
        plu(0);
        if (beep_fl==GOOD) {
          if (special==1) {
            for (i=0; i<weeg_elen; i++) {
              if (i==(weeg_elen-weeg_edig)) numkey(10);
              numkey(key_buf[pos+weeg_epos+i]-'0');
            }
            if (weeg_type==3) numkey(12);
            eenh_prijs(0);
          }
        }
      }
      else if (add_ean(key_buf+pos)) {
        movmem(key_buf+pos,ean_last,sizeof(ean_last));
        beep_bad(); beep_fl=NO;
        disp_vid(2,4,key_buf+pos,8);
      }
      break;
    }
    else if (key_buf[pos]=='$') {
      switch (key_buf[pos+1]) {
        case '0': bak_fles=0; p_vrk->stuks_flag=NO; break;
        case '1': bak_fles=1; p_vrk->stuks_flag=YES; break;
        case '2': p_vrk->leeg_flag|=1; break;
        case '3': p_vrk->leeg_flag&=0xFFFE; break;
        case '4': p_vrk->leeg_flag|=2; break;
        case '5': p_vrk->leeg_flag&=0xFFFD; break;
      }
      disp_window();
      pos+=2;
    }
    else if (key_buf[pos]=='+') {
      parm=16*hex2dec(key_buf[pos+1])+hex2dec(key_buf[pos+2]);
      pos+=3;
    }
    else if (key_buf[pos]=='%') {
      key_touched=16*hex2dec(key_buf[pos+1])+hex2dec(key_buf[pos+2]);
      if (key_touched<MAX_KEYS && exec_rout) {
        if (parm>=0) (*toetsen[key_touched].rout)(parm);
        else (*toetsen[key_touched].rout)(toetsen[key_touched].argument);
      }
      if (key_touched==13) bak_fles=-1;
      pos+=3;
    }
    else break;
  }
  return key_touched;
}

int CKasPLU::add_ean(char *ean)
{
  int ix, idem_fl;
 
  ix=find_ean(ean);
  if (ix>=0) {
    plu_ix=ix;
    movmem(&artikel[ix],&art_info,sizeof(art_info));
    idem_fl=NO;
    if (bak_fles>=0) p_vrk->stuks_flag=bak_fles;
    if (p_vrk->used>0) {
      ix=p_vrk->used-1;
      while (ix>0) {
        if (!(p_vrk->lijn[ix].bits & AUTO_LEEG)) break;
        ix--;
      }
      if (compare(art_info.code,p_vrk->lijn[ix].code,ARTCODE_LEN)==0) {
        stuks_fl = p_vrk->lijn[ix].bits & STUKS;
        if ((stuks_fl && p_vrk->stuks_flag) || (!stuks_fl && !p_vrk->stuks_flag)) {
          idem_fl=YES;
        }
      }
    }
    if (add_art(idem_fl)) beep_fl=BAD; else beep_fl=GOOD;
    bak_fles=-1;
    clr_line();
  }
  else {
    beep_fl=BAD;
    return YES;
  }
  return NO;
}
 

*/


int CKasPLU::_ecompare(char *i1, char *i2, int len)
{
  UNALIGNED int *p1, *p2;
	char *s1, *s2;
  int j;
 
  p1=(int *)i1; p2=(int *)i2;
  if (*p1>=200000) s1=extra[*p1-200000].ean;
  else if (*p1%2==0) s1=artikel[*p1/2].ean;
  else s1=artikel[*p1/2].ean_st;
  if (*p2>=200000) s2=extra[*p2-200000].ean;
  else if (*p2%2==0) s2=artikel[*p2/2].ean;
  else s2=artikel[*p2/2].ean_st;
  for (j=0; j<ARTEAN_LEN; j++) {
    if (*s1<*s2) return -1;
    if (*s1>*s2) return  1;
    s1++; s2++;
  }
  return 0;
}

int CKasPLU::hex2dec(char byte)
{
  int ret;
 
  ret=byte-'0';
  if (ret<0) ret=0;
  else if (ret>9) {
    if (byte>='a' && byte<='z') byte+='A'-'a';
    ret=byte-'A'+10;
  }
  return ret;
}

void CKasPLU::anew_ean(char *artcode, char *ean_last, bool _stuksflag)
{

  char *s;
  int len_c, len_e, fref;

  len_c=0;
  while (artcode[len_c]) {
    len_c++;
    if (len_c==ARTCODE_LEN) break;
  }
  len_e=0;
  while (ean_last[len_e]) len_e++;
  if (len_c==0 || len_e==0) goto end;

  fref=dopen("KASEXT.DAT",RDWRMODE);
  if (fref<0) fref=dcreat("KASEXT.DAT",CREAMODE);
  if (fref<0) {
    tkdspnl("Impossible to open KASEXT.DAT");
    kbchar();
    _moexit(0);
    exit(0);
  }
  
  dseek(fref,0L,2);
  dwrite(fref,artcode,len_c);
  dwrite(fref,"|",1);
  s="0";
  if (_stuksflag) s="1";
  dwrite(fref,s,1);
  dwrite(fref,"|",1);
  dwrite(fref,ean_last,len_e);
  dwrite(fref,"\r\n",2);
  dclose(fref);
  extra[ext_used].plu_ix=plu_req(artcode,ARTCODE_LEN);
  extra[ext_used].stuks_fl=*s-'0';
  movmem(ean_last,extra[ext_used].ean,ARTEAN_LEN);
  ean_tab[ean_used++]=200000+ext_used++;
  Sort(2);
  ean_last[0]=0;
 end:;
}
 
int CKasPLU::find_ean(char *ean, int CntFlesInBak)    // return 1000000+recnr als het om STUKS gaat !!, -1 als niet gevonden !
{
  int begin,last,ret,test,ean_ptr,recix,len;
                                                
  begin=0; last=ean_used-1;
  if (ean_used<1) return -1;
  for (len=0; len<ARTEAN_LEN; len++) if (ean[len]==0) {len++; break;}  // len inclusief de 0 ! 
  FOREVER {
    test = (begin+last)/2;
    ean_ptr=ean_tab[test];
    if (ean_ptr>=200000) ret=memcmp(ean,extra[ean_ptr-200000].ean,len);
    else if (ean_ptr%2==0) ret=memcmp(ean,artikel[ean_ptr/2].ean,len);
    else ret=memcmp(ean,artikel[ean_ptr/2].ean_st,len);
    if (!ret) {
      if (ean_ptr>=200000) {
        recix=extra[ean_ptr-200000].plu_ix;
        movmem(&artikel[recix],&art_info,sizeof(art_info)); 
        if (extra[ean_ptr-200000].stuks_fl) recix+=1000000;
        return recix; 
      }
      recix=ean_ptr/2;
      if (ean_ptr%2!=0) {
			  recix+=1000000;
				if (CntFlesInBak>0) {
					recix=-1;
					FOREVER {
					  test--;
						ean_ptr=ean_tab[test];
						if (ean_ptr>200000 && memcmp(ean,extra[ean_ptr-200000].ean,len)) break;
						if (ean_ptr%2==0 && memcmp(ean,artikel[ean_ptr/2].ean,len)) break;
						if (ean_ptr%2==1 && memcmp(ean,artikel[ean_ptr/2].ean_st,len)) break;
					}
					FOREVER {
						test++;
					  ean_ptr=ean_tab[test];
						if (ean_ptr>200000 && memcmp(ean,extra[ean_ptr-200000].ean,len)) break;
						if (ean_ptr%2==0 && memcmp(ean,artikel[ean_ptr/2].ean,len)) break;
						if (ean_ptr%2==1 && memcmp(ean,artikel[ean_ptr/2].ean_st,len)==0 && CntFlesInBak==artikel[ean_ptr/2].st_verp) {
							recix=ean_ptr/2;
						  recix+=1000000;
							break;
						}
					}
				}
			}
			int _recix=recix;
			if (_recix>=1000000) _recix-=1000000;
      if (_recix>=0) movmem(&artikel[_recix],&art_info,sizeof(art_info));
      return recix;
    }
    else if (ret<0) {
      last=test-1;
      if (begin>last) return -1;
    }
    else {
      begin=test+1;
      if (begin>last) return -1;
    }
  }
}



/* laatste */

/*
///////////////// HISTORIEK AANPASSINGEN /////////////////////////////////////////////////////////
150306 JG De variabelen artikel, ean_tab en extra verhuisd van private --> PUBLIC (in de .H file)
081007 JG Probleem met keyboard bij search (wijziging in kbchar())



///////////////// EINDE HISTORIEK ////////////////////////////////////////////////////////////////

*/