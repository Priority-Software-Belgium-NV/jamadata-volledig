char version[] = "KASKEYS   00.04 07/02/07 (c) Jamadata Geel";

#define WINVER 0x500

#include "stdafx.h"
#include "p:\jamacon\library\JamaConL.h"
#include "..\kassawin\kashead.h"
#include "kaskeys.h"
#include "..\kassawin\kassysc.h"

#define MAX_KEYCOON_FILE 2000

struct sKeyCoon {
  short int Type;
  char Text[40];
} KeyCoon [MAX_KEYCOON_FILE];
int KeySort[MAX_KEYCOON_FILE];
int cnt;

extern int fref_sys;
extern int crtindex, crtdata, video;
// extern unsigned hercnum, herctab[];

char config[10], beep_fl;
extern unsigned jamin1[5];

int epson_fl=0;
static struct layout *p_lay;
extern struct layout key_layout[], keyb_layout[], bet_layout[], bet_krediet;
extern unsigned reg_ds, mulfunok;
void UpdateSize();

CKasSYS kassys;
 
void main(int argc, char *argv[]) // !!! WERKT NIET, COMPILEREN VANUIT STUDIO 2010 (P:\JAMACON\KASSAW\KASSAW.SLN) !!!
{
	unsigned char buf[10];
	int len, i, j, ixmin;
	unsigned char *s;

  moinit(0,1);

  kassys.rd_kassys(0); 
  if (fref_sys<0) {printf("KASSYS.DAT -> File not found"); exit(1);}
 
  int ref = dopen("KeyCoonN.jam",0x8000);
  if (ref!=-1) {
    dread(ref,(char *)buf,2);
    if (buf[0]!=0xFC || buf[1]!=0x01) goto skip;
    len=30000;
    s=(unsigned char *)&KeyCoon[0];
    while (true) {
      if (dread(ref,(char *)s,len)!=len) break;
      s+=len;
    }
   skip:;
    dclose(ref);
  }

  for (i=0; i<MAX_KEYCOON_FILE; i++) {
		if (KeyCoon[i].Text[0]==0) break;
		KeyCoon[i].Type=1; // indicate used
	}
	cnt=i;
   
  for (j=0; j<cnt; j++) {
		ixmin=9999;
		for (i=0; i<cnt; i++) {
			if (ixmin==9999 && KeyCoon[i].Type==1) ixmin=i;
			if (KeyCoon[i].Type==1 && (memcmp(KeyCoon[ixmin].Text,KeyCoon[i].Text,sizeof(KeyCoon[0].Text))>0)) ixmin=i;
		}
		KeySort[j]=ixmin;
		KeyCoon[ixmin].Type=0;
	}

  moinit(0,1);
  SetProgramName("KasKeys");
  ConStyle(CON_STYLE_NOBACKGROUND);
  if (key_layout[0].x_pos==1) {
    if(ConMessageBox(_T("Wenst U de keyconen te vergroten ?"),_T("Inlezen blokjes"),MB_YESNO | MB_ICONEXCLAMATION |MB_ICONWARNING)==IDYES) UpdateSize();
  }
  cls();
  update();
  if(ConMessageBox(_T("Wenst U de aanpassingen weg te schrijven ?"),_T("Aanpassen blokjes"),MB_YESNO | MB_ICONEXCLAMATION |MB_ICONWARNING)==IDYES) {
    disp_clr(0,0,80,25);
    disp_vid(0,0,"Writing file(s) ...",0);
    wr_fullsys();
  }
  _moexit(0);
}

int update(void)
{
  FOREVER {
    if (updkey(&key_layout[0],100)==256) return 0;
    if (updkey(&keyb_layout[0],60)==256) return 0;
    if (updkey(&bet_layout[0],30)==256) return 0;
  }
}

void UpdateSize()
{
  int i, x;

  for(i=0;i<100;i++){ // 00 en 000 eruit halen 
    if(key_layout[i].key_numb==75 || key_layout[i].key_numb==74) key_layout[i].key_numb=-1;
  }
  sort_lkey(&key_layout[0],100); // key 000 weg 
  for (i=0; i<100; i++) {
    if (key_layout[i].y_pos==0) {
      x=(key_layout[i].x_pos/10);
      key_layout[i].x_pos=x*10;
      key_layout[i].x_len=10;
    }
    else if (key_layout[i].x_pos==1 || key_layout[i].x_pos==11 || key_layout[i].x_pos==16 || key_layout[i].x_pos==21 || key_layout[i].x_pos==31 || key_layout[i].x_pos==41 ) {
      key_layout[i].x_pos--;
      key_layout[i].x_len+=2;
      key_layout[i].y_pos--;
      key_layout[i].y_len++;
    }
  }

  for (i=0; i<60; i++) {
    if (keyb_layout[i].y_pos==17 || keyb_layout[i].y_pos==19 || keyb_layout[i].y_pos==21 ||keyb_layout[i].y_pos==23) {
      keyb_layout[i].x_pos--;
      keyb_layout[i].x_len++;
      keyb_layout[i].y_len++;
    }
  }

  for (i=0; i<30; i++) {
    if (bet_layout[i].x_pos==52 || bet_layout[i].x_pos==62 || bet_layout[i].x_pos==72) {
      bet_layout[i].x_pos-=2;
      bet_layout[i].x_len+=2;
      bet_layout[i].y_pos--;
      bet_layout[i].y_len++;
    }
    else if (bet_layout[i].x_pos==68) {
      bet_layout[i].x_pos-=3;
      bet_layout[i].x_len+=3;
      bet_layout[i].y_pos--;
      bet_layout[i].y_len++;
    }
 
  }
  
}

int updkey(struct layout lay[],int count)
{
  char byte[5],mode_pijl_=1;
  int i, j,key,prevselected;

  for(i=0;i<sizeof byte; i++) byte[i]='\0';

  i=0;byte[0]=char(219);
  for (i=0; i<count; i++) {
		if (lay[i].x_len<0 || lay[i].y_len<0) {
			i=i;
		}
    if (lay[i].key_numb>=1000 && lay[i].x_len>0 && lay[i].y_len==0) {
      lay[i].y_len=1;
    }

  }
  i=0;

  prevselected=i;
	FOREVER {
   next:;
		if (!kbtest()) {
			disp_clr(0,0,80,25);
			for (j=0; j<count; j++) {
				if (lay[j].x_len!=0 && lay[j].y_len!=0) {
					if (lay[j].key_numb>=32000) lay[j].key_numb=10;
					if (j==i) {
 						if (mode_pijl_==1) disp_key(lay[i].x_pos,lay[i].y_pos,lay[i].x_len,lay[i].y_len,lay[i].key_numb,0xFFFF00);
  					else disp_key(lay[i].x_pos,lay[i].y_pos,lay[i].x_len,lay[i].y_len,lay[i].key_numb,0x00FFFF);
					}
					else disp_key(lay[j].x_pos,lay[j].y_pos,lay[j].x_len,lay[j].y_len,lay[j].key_numb);
				}
			}
		}
				
		p_lay=&lay[i];
    if (p_lay->key_numb<0) i++;
    else {
      if(mode_pijl_==0) ConTitle("Normal mode");
      else if(mode_pijl_==1) ConTitle("MOVE KEYCOON");
      else if(mode_pijl_==2) ConTitle("RESIZE KEYCOON");
			ReturnRightClick=true;
      key=kbchar();
			if ((key==0xFC00) && mode_pijl_==1) {
			  p_lay->x_pos=mspos_h;
				p_lay->y_pos=mspos_v;
				goto next;
			}

      if ((key&0xFFFF)==0) {
        key=key/0x10000;
        for (j=0; j<count; j++) {
          if (lay[j].key_numb==key) {
						if (i==j) {
							if (mode_pijl_==1) mode_pijl_=2;
							else mode_pijl_=1;
						}
						i=j;
            goto next;
          }
        }
      }
      if (key==256 || key==32){sort_lkey(&lay[0],count); return key;} // esc = 256 of space 32
      key/=256;
      if(key<6 || key>9 && key!=105) mode_pijl_=0;
     redo:;
      switch (key) {
   
      case 112 : dsp_help(); break;


  	  case 8: // up
	      if(mode_pijl_==1) p_lay->y_pos--;
	      else if(mode_pijl_==2) p_lay->y_len--;
	      break;
	    case 9: // dn
	      if(mode_pijl_==1) p_lay->y_pos++;
	      else if(mode_pijl_==2) p_lay->y_len++;
	      break;
	    case 6: // left
	      if(mode_pijl_==1) p_lay->x_pos--;
	      else if(mode_pijl_==2) p_lay->x_len--;
	      break;
	    case 7: // right
	      if(mode_pijl_==1) p_lay->x_pos++;
	      else if(mode_pijl_==2) p_lay->x_len++;
	      break;
	    case 107: p_lay->key_numb=select_key(p_lay->key_numb); break;
	    case 105: mode_pijl_++; if(mode_pijl_>2) mode_pijl_=0; break;
	    case 5: // del
	      p_lay->key_numb=-1; 
	      key=7; goto redo; // go left 
	      break;
	    case 4: // ins
	      for (i=0; i<count; i++) {
	        if (lay[i].key_numb<0 || (lay[i].x_len==0 && lay[i].y_len==0)) break;
	      }
	      p_lay=&lay[i];
	      p_lay->x_pos=0; p_lay->y_pos=0; p_lay->x_len=4; p_lay->y_len=2;
	      p_lay->key_numb=104;
	      break;
      }
      if (p_lay->y_pos<0) p_lay->y_pos=0;
      if (p_lay->y_pos>24)p_lay->y_pos=24;
      if (p_lay->y_len<0) p_lay->y_len=0;
      if (p_lay->y_len>24)p_lay->y_len=24;
      if (p_lay->x_pos<0) p_lay->x_pos=0;
      if (p_lay->x_pos>79)p_lay->x_pos=79;
      if (p_lay->x_len<0) p_lay->x_len=0;
      if (p_lay->x_len>79)p_lay->x_len=27;
    }
  }
}



void wr_fullsys(void)
{
  int k;

  for(k=0;k<30;k++) kassys.writmem((long)(4608+k*14),&bet_layout[k],10);
  for(k=0;k<60;k++) kassys.writmem((long)(5376+k*14),&keyb_layout[k],10);
  for(k=0;k<100;k++) kassys.writmem((long)(7168+k*14),&key_layout[k],10);
  kassys.upd_sys();
}

int select_key(int beg_key_)
{
  int key, x, y, first, nr;

  first=0;
  while (true) {
    cls();
    for (y=0; y<8; y++) {
      for (x=0; x<5; x++) {
				nr=y*5+x+first;
				if (nr>=cnt) goto done;
        disp_key(x*16,y*3,16,3,KeySort[nr]);
      }
    }
done:;
    key=kbchar();
    if (key/0x10000) break; // keycoon ingedrukt !
    if (key==13*256) {  // page down
      first+=40;
    }
    if (key==12*256) {  // page up
      first-=40;
      if (first<0) first=0;
    }
    if (key==10*256) first=0; // home
    if (key== 1*256) return beg_key_; // escape
  }
  cls();
  return key/0x10000; 
}
   
void sort_lkey(struct layout lay[],int count)
{
  int j,k,max_;
//  struct layout tmp_;

  max_=count-1; // gedelete blokjes schrappen 
  for(k=0;k<max_;){
    if(lay[k].key_numb<0 || (lay[k].x_len<=0 && lay[k].y_len<=0)){
      for(j=k;j<max_;j++) bcopy((char *)&lay[j+1].key_numb,(char *)&lay[j].key_numb,sizeof (struct layout));
      lay[max_].key_numb=-1;lay[max_].x_pos=0;lay[max_].x_len=0;lay[max_].y_pos=0; lay[max_].y_len=0;
      max_--;
    }
		else k++; // men kan er gedelete inschuiven en dus opnieuw op pos k testen !!!
  }

/*
  for(max_=0;max_<count;max_++) if(lay[max_].key_numb<0 || (lay[max_].x_len<=0 && lay[max_].y_len<=0)) break;
  FOREVER{
    sw_=NO;
    for(k=0;k<max_-1;k++){
      if(lay[k].x_pos>lay[k+1].x_pos || (lay[k].x_pos==lay[k+1].x_pos && lay[k].y_pos>lay[k+1].y_pos)){
        bcopy((char *)&lay[k].key_numb,(char *)&tmp_.key_numb,sizeof tmp_);
        bcopy((char *)&lay[k+1].key_numb,(char *)&lay[k].key_numb,sizeof tmp_);
        bcopy((char *)&tmp_.key_numb,(char *)&lay[k+1].key_numb,sizeof tmp_);
        sw_=YES;
      }
    }
    if(sw_==NO) break;
  }
*/
}

    
void dsp_help(void)
{

  disp_clr(0,0,80,25);
  disp_vid(25,1,"Gebruik van de toetsen",2);
   
  disp_vid(5,6,"F5   Verander PIJL-mode : M=Move, S=Size of blokje=ga naar een blokje",0);
  disp_vid(5,7,"F7   Zoek een functie voor dit blokje",0);

  disp_vid(5,9,"PgUp   Ga naar vorig blokje uit tabel",0);
  disp_vid(5,10,"PgDn   Ga naar volgend blokje uit tabel",0);
  disp_vid(5,11,"Home   Ga helemaal linksboven staan",0);
  disp_vid(5,12,"End    Ga helemaal rechtsonder staan",0);
  disp_vid(5,13,"PIJLEN : Zie functie-toets F5",0);
  disp_vid(5,14,"INS    : Maak nieuwe icoon (linksboven)",0);
  disp_vid(5,15,"DEL    : Delete huidig blokje",0);
  disp_vid(5,17,"SPATIE : Ga naar volgend scherm",0);
  disp_vid(5,18,"ESC    : Stop uit programma",0);

  disp_vid(15,21,"Druk op een toets om terug te keren...",2);
  kbchar();
  disp_clr(0,0,80,25);
}



void bcopy(char *pfrom_,char *pto_,int len_)
{
  int k;

  for(k=0;k<len_;k++) *(pto_+k)=*(pfrom_+k);
}




/*
///////////////// HISTORIEK AANPASSINGEN ////////////////////////////////////////////////
061106 JG Vergroten blokjes : 00 en 000 steeds wegdoen en probleem van sommige blokjes opgelost 


///////////////// EINDE HISTORIEK ///////////////////////////////////////////////////////

*/