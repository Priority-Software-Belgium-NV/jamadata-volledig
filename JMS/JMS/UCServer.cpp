// uc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <afxsock.h>
//#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <winbase.h>

#include "JMS.h"

#pragma pack(1)

char version[] = "UC       05.21 09/02/06 (c) Jamadata (Windows 32-bit).";

#define FOREVER while(1)
#define YES     1
#define NO      0
#define NULL    0
#define CRLF    "\r\n"
#define CR      "\r"
 
#define DLE     (char)16
#define SOH     (char)01
#define TYPMSG  (char)0x0F
#define TYPRES  (char)0x03
#define TYPACK  (char)0xF0
 
#define COMP_CODE       0xFE
 
#define RDWRMODE        OF_READWRITE
#define RDMODE          OF_READ | OF_SHARE_DENY_WRITE
#define CREAMODE        0
#define NSECPERMIN	600000000L
#define INT2CHECKHOLD   15          // check hold file every 15 seconds 

#define FILES_SIZE      3000/* size of buffer to hold uc?????.JAM file */
 
#define CMD_SIZE        16500
#define old_REC_SIZE    4096
#define REC_SIZE        16384  /* max. record size */
#define MAX_SUBDIR_DEPT 20

#define RTO      0/* no time-out may occur */
#define STO     60/* time - out of 30 sec. */
#define NET_INT 0x5C

#define DEF_SOCKPORT    5000

#define WATCH_TIMEOUT   45*100L/* Timeout van 45 seconden bij TCP/IP of MODEM-SLAVE */
/* anders springt het programma eruit, net als ESC */

WIN32_FIND_DATA fileinfo[MAX_SUBDIR_DEPT];
int hfileinfo[MAX_SUBDIR_DEPT];
int fileinfodept=0;
/*
struct FILEINFO {
  char resv[21];
  char attr;
  long time;
  long size;
  char name[13];
} fileinfo, info_save[10]; */

char file_loaded;
char flst_name[64], flst_del, *flst_p2;
int  file_pos, file_len, flst_ref=-1, flst_len2;
long flst_pos;
char saveCurrentDirectory[300];
char mas_flag, slav_flag, comp_flag, terminate_flag=false;
char prmtmode=NO, fatal_err, log_flag, log_status, deb_flag, dir_changed;
int here, there;
char del_def, alw_flag, exit_flag, subd_flag, iddisp_fl;
static char call_name[32], this_name[32]="Jamadata Server (JMS)", lst_item[100], excl_file[40];
char usr_file[65];
char rxdebfile[20]="RX000000";
char txdebfile[20]="TX000000";
long baud=19200, act_baud;
int com_port=0, rec_size=old_REC_SIZE; 
char rec_type;/* 0 : old_RECSIZE 1 : 1024, 2 : 256, 100 : RECSIZE */
char conn_type;
/*                             1 : Legacy -> Internal connection (same computer)
			       2 : Legacy -> RS-232 connection (cable)
			       3 : Legacy -> Idem but with modem protocol
			       4 : Legacy -> NETBIOS connection
                               5 : WinSock connection
*/
 
char UCStopFileName[100], path[64], source_save[10][64], dest_save[10][64];
//int ix_save=0;
char directory[50];
char fileslst[100], buffer[100], buf[5000];
unsigned char filebuf[REC_SIZE];
char mod_cmd[20][100];/* buffer for 20 commands of 100 bytes each */
int  mod_cnt;
int  bref;
char file_buf[FILES_SIZE];
int FileCntTransmitted=0, FileCntReceived=0, FileCntIdentical=0, FileCntError=0;

struct s_call {
  char type;
  char name[32];
} call={1}, *p_call;

struct s_Accept {
  char type;
  char name[32];
} Accept={2}, *p_Accept;

struct s_initra {
  char type;   
  char delflag;
  char alwflag;
  char compflag;
  char subdflag;
  char renflag;
  char rectype;
  char noeflag;
  char dummy[8];
  char path_mast[64];
  char path_slav[64];
} initra={3}, *p_initra;

struct s_reqope {
  char type;
  char dummy1;
  char alwflag;
  char compflag;
  char dummy[12];
  char name[64];
  char name_orig[64];
  long size;
  long time;
  short int attr;
} reqope={4}, *p_reqope;

struct s_repope {
  char type;
  char retcode;
} repope={5}, *p_repope;

struct s_reqwri {
  char type;
  char last;
  short int  size;
  short int  comp_size;
  char info[REC_SIZE];
} reqwri={6}, *p_reqwri;

struct s_repwri {
  char type;
  char retcode;
} repwri={7}, *p_repwri;

struct s_eot {
  char type;
} eot={8};
 
struct s_eos {
  char type;
} eos={9};

/* slave data zone */
char s_in_flag;
int  slav_status=-1;
char s_in_cmd [CMD_SIZE];
char s_out_cmd[CMD_SIZE];

extern unsigned jamin1[];
char *getenv();
long pos, tm_start, tm_last, watch_timeout;
long tm_conn;
 
struct {
  char path_source[64];
  char path_dest[64];
  char tx_flag;
  char ren_flag;
  char del_flag;
  char noe_flag;
} transfer;

struct {
  char mode[15];
  char found;
  char send_ok;
  char cpu_name[32];
  char tx_flag;
  int  ref;
  char name[15];
  char path[64];
  char attr;
  long size;
  long time;
  long pos;
  short int  tx_ok;
  short int  tx_err;
  short int  rx_ok;
  short int  rx_err;
} file[2];

WSADATA WSAData;
SOCKET l_sock=INVALID_SOCKET, sock=INVALID_SOCKET;
char FQDNServer[100];
int SockPort=DEF_SOCKPORT;
char rem_ipaddr[20], hold_flag[100];

struct ncb_fmt {
  char command;
  char retcode;
  char lsn;
  char num;
  char *pbuf;
  short unsigned ds;
  short unsigned length;
  char callname[16];
  char name[16];
  char rto;
  char sto;
  short int *postrout;
  short unsigned cs;
  char lana_num;
  char cmd_cplt;
  char reserved[14];
} ncb[2];

extern int tim_sign;

void proc();
int mod_time();
int slave();
void status(int type);
void check_type(int nr);
void send_cmd(char *s);
void rec_cmd();
void send_initra();
void send_open();
void send_write();
int compress(unsigned char *buf, int size);
int decompress(unsigned char *buf,int size);
int next_transfer();
void updenv(char *inppath);
int proc_open();
int proc_write();
void proc_close(int error);
void start_find();
int proc_subdir(int error);
void next_find();
int one_file(char *s);
void open_file();
void adj_recsize();
void make_fnme(char *filename, char *node_ext);
int pos_dir(char *filename,char make_fl);
void endit();
int get_string(char *d, char *s);
int get_getal(char *s);
unsigned get_hex(char *s);
void set_mode(int nr);
void wait(int hun);
void upd_wild(char *d, char *s);
void make_caps(char *s, int len);
int _cmpi(char *a, char *b, int len);
char *getfilename(int ix);
void save_parms();
void UTCAdjust(FILETIME *FileTime, int Local2UTC);
void proc_socket();
void accept_sock();
void sock_close();
void send_sock(int size, char *s);
void rec_sock();
void sock_recv_buf(char *s,int size);
SOCKET listen_socket(unsigned short);
SOCKET call_socket(const char *, unsigned short);

//compatibility lattice headers
void movmem(char *source, char *dest, int size);
void strmfn(char *file,char *drive,char *path,char *node,char *ext);
void strsfn(char *file,char *drive,char *path,char *node,char *ext);
void strmfe(char *newname, char *oldname, char *ext);
void stcgfe(char *ext,char *filename);
int dopen(char *filename,int mode, int extra);
int dcreat(const char *filename, int pmode);
int dwrite(int handle, const void *buffer, unsigned int count);
int dread(int handle, void *buffer, unsigned int count);
long dseek(int handle,long pos, int mode);
int dclose(int handle);
int getfa(char *filename);
int chgfa(char *filename, int fa);
int chgft(int fHandle, long ft);
long getft(int fHandle); 
unsigned stci_d(char s,int in,int outlen);
int stch_i(char *s,unsigned *r);
int stcd_i(char *s,int *r);
int stcd_li(char *s,long *li);
void stcli_d (char *s,long l,int digits,char *lzerosup);
int stcd_df(char *s,double *df);
void stcdf_d (char *s,double df,int digits,char *lzerosup);
long get_hun();

CString UcCurrentDir;

int mod_time()
{
  long act;

  if (slav_flag) {
    act=get_hun();
    if (watch_timeout<act) return YES;
  }
  return NO;
}

int slave()
{
  int reconnect=NO;
//  int slav_status_prev;

  if (!slav_flag) goto end;
  here=1; there=0;
  if (s_in_flag) {
    watch_timeout=get_hun()+WATCH_TIMEOUT;
    switch (slav_status) {
      case -1:
	      check_type(1);
	      p_call=(struct s_call *)s_in_cmd;
	      movmem(p_call->name,file[there].cpu_name,sizeof(file[0].cpu_name));
	      if (conn_type>1) {
	        printf("\rSlave mode. Connected to master : %-1s\r\n\r\n",file[there].cpu_name);
          LogAdd(0,0,"Connected to KeyConenKassa",file[there].cpu_name);
	      }
	      movmem(this_name,Accept.name,sizeof(Accept.name));
	      send_cmd((char *)&Accept);
	      slav_status=100;
	      break;
      case 100:
	switch (*s_in_cmd) {
	  case 3:
	    slav_status=103;
	    break;
	  case 4: /* reqope */
	    slav_status=101;
	    break;
	  case 9:
	    slav_status=-1;
	    reconnect=YES;
	    break;
	  default:
	    check_type(4);
	    break;
	}
	break;
      case 102:
	      check_type(6);
	      p_reqwri=(struct s_reqwri *)s_in_cmd;
	      repwri.retcode=proc_write();
	      send_cmd((char *)&repwri);
	      if (repwri.retcode || p_reqwri->last) {
	        proc_close(repwri.retcode);
	        status(2);
	        slav_status=100;
	      }
	      else {
	        status(1);
	        slav_status=102;
	      }
	      break;
      case 105:
	      check_type(5);
	      p_repope=(struct s_repope *)s_in_cmd;
	      if (p_repope->retcode) {
	        if (iddisp_fl || p_repope->retcode>1) {
	          printf("%-40s -> ",file[here].path);
	          if (p_repope->retcode==1) {
	            printf("Identical file already exists !\r\n");
              FileCntIdentical++;
	          }
	          else if (p_repope->retcode==99) printf("Excluded !\r\n");
	          else {
	            printf("Impossible to create !\r\n");
              FileCntError++;
	          }
	        }
	        slav_status=108;
	      }
	      else {
	        status(0);
	        slav_status=106;
	        file[here].tx_err++;
	      }
	      break;
      case 107:
	      check_type(7);
	      p_repwri=(struct s_repwri *)s_in_cmd;
	      if (p_repwri->retcode) {
	        printf("\rProblems to write on destination (%3d).                                    \r\n",p_repwri->retcode);
	        status(3);
	        slav_status=108;
	      }
	      else if (reqwri.last) {
	        status(2);
	        file[here].send_ok=YES;
          file[here].tx_err--;
	        file[here].tx_ok++;
          FileCntTransmitted++;
	        slav_status=108;
	      }
	      else slav_status=106;
	      break;
    }
    s_in_flag=NO;
  }
  else {
    if ((conn_type==3 || conn_type==5) && mod_time()) {
      if (slav_status!=-1) {
        status(4); reconnect=3;
      }
    }
  }

  switch (slav_status) {
    case 101:
      p_reqope=(struct s_reqope *)s_in_cmd;
      repope.retcode=proc_open();
      send_cmd((char *)&repope);
      if (repope.retcode) {
	      if (iddisp_fl || repope.retcode>1) {
	        printf("%-40s -> ",file[here].path);
          if (repope.retcode==1) {FileCntIdentical++; printf("Identical file already exists !\r\n");}
          if (repope.retcode==2) {FileCntError++; printf("Impossible to open file for output !\r\n");}
          if (repope.retcode==3) {FileCntError++; printf("Impossible to create directory !\r\n");}
	        if (repope.retcode==99) printf("Excluded !\r\n");
	      }
	      slav_status=100;
      }
      else {
	      status(0);
	      slav_status=102;
	      file[here].rx_err++;
      }
      break;
    case 103:
      p_initra=(struct s_initra *)s_in_cmd;
      alw_flag=p_initra->alwflag;
      transfer.del_flag=p_initra->delflag;
      transfer.ren_flag=p_initra->renflag;
      transfer.noe_flag=p_initra->noeflag;
      comp_flag=p_initra->compflag;
      subd_flag=p_initra->subdflag;
      rec_type=p_initra->rectype;
      adj_recsize();
      movmem(p_initra->path_mast,transfer.path_dest,sizeof(transfer.path_dest));
      movmem(p_initra->path_slav,transfer.path_source,sizeof(transfer.path_source));
      start_find();
      if (file[here].found) slav_status=104;
      else {
	      send_cmd((char *)&eot);
	      slav_status=100;
      }
      break;
    case 104:
      send_open();
      slav_status=105;
      break;
    case 106:
      send_write();
      status(1);
      slav_status=107;
      break;
    case 108:
      next_find();
      if (file[here].found) slav_status=104;
      else {
	      send_cmd((char *)&eot);
	      slav_status=100;
      }
      break;
  }
  if (reconnect) {
    CString cstr;
    cstr.Format("Connection with %s closed, FileCount: Txmit=%d Rcve=%d Same=%d Error=%d",file[there].cpu_name,FileCntTransmitted,FileCntReceived,FileCntIdentical,FileCntError);
    LogAdd(0,0,cstr);
  }
 end:;
  return reconnect;
}

void status(int type)
{
  char disp, buf[100], *s;
  long now, length, remain,secremain,timtot;
  float kbpsec;
 
  if (conn_type==1 && here==1) goto end;
  if (type==0) {
    tm_start=get_hun(); tm_last=tm_start;
    if (file[here].tx_flag) s="Transmitting";
    else s="Receiving";
    sprintf(buf,"%-21s %1s\r\n",s,file[here].path);
    printf(buf);
    //if (log_flag) log_add(1,buf);
    if (file[here].tx_flag) s="To";
    else s="From";
    sprintf(buf,"%-4s %-16s %1s\r\n",s,file[there].cpu_name,file[there].path);
    printf(buf);
    //if (log_flag) log_add(1,buf);
  }
  else {
    disp=NO;
    if (type==2 || type==4) disp=YES;
    now=get_hun();
    if (now > tm_last+100) disp=YES;
    if (type==3) disp=NO;
    if (disp) {
      length=(long)(.5+file[here].size/1024);
      if (length==0) length=1L;
      remain=(file[here].size - file[here].pos)/1024;
      kbpsec=(float)(file[here].pos/((now-tm_start)*10.));
      secremain=(long)(remain/kbpsec);
      if (type==4) printf("\r\n");
      sprintf(buf,"\rLength :%5ld Kb      Remain :%5ld Kb %5ld sec      Kb/sec :%7.2f",length,remain,secremain,kbpsec);
      printf(buf); _flushall();
      if (type==4) {
	      //sprintf(buffer,"%1s\r\n",buf);
	      //log_add(1,buffer);
	      //log_add(1,"!!!!!!   TIME-OUT   !!!!!!\r\n");
      }
      if (type==2) printf("\r\n");
      tm_last=now;
    }
    if (type==2 && log_flag) {
      timtot=(long)(.5+(now-tm_start)/100.);
      if (timtot==0) timtot=1L;
      //sprintf(buf,"Length :%5ld Kb      Txmit-time :%5ld sec      Kb/sec :%7.2f\r\n",length,timtot,kbpsec);
      //log_add(1,buf);
    }
    if (type>=2) printf("\r\n");
  }
 end:;
}
 
void check_type(int nr)
{
  int status;
  char *s;
 
  if (here==0) {/* master code s=m_in_cmd; status=mas_status;*/}
  else {s=s_in_cmd; status=slav_status;}
  if (nr!=*s) {
    CString cstr;
    cstr.Format("Status :%3d. Expecting CMD:%2d but received CMD:%2d",status,nr,(int)*s);
    LogAdd(58,0,"UC-Server",cstr);
  }
}
 
void send_cmd(char *s)
{
  int cmd_size;

  cmd_size=CMD_SIZE;
  switch(*s) {
    case 1: cmd_size=sizeof(struct s_call); break;
    case 2: cmd_size=sizeof(struct s_Accept); break;
    case 3: cmd_size=sizeof(struct s_initra); break;
    case 4: cmd_size=sizeof(struct s_reqope); break;
    case 5: cmd_size=sizeof(struct s_repope); break;
    case 6:
      cmd_size=sizeof(struct s_reqwri)-REC_SIZE+reqwri.comp_size;
      break;
    case 7: cmd_size=sizeof(struct s_repwri); break;
    case 8: cmd_size=sizeof(struct s_eot); break;
    case 9: cmd_size=sizeof(struct s_eos); break;
  }
  send_sock(cmd_size,s);
}

void rec_cmd()
{
  rec_sock();
}

void send_initra()
{
  initra.delflag=transfer.del_flag;
  initra.renflag=transfer.ren_flag;
  initra.noeflag=transfer.noe_flag;
  initra.alwflag=alw_flag;
  initra.compflag=comp_flag;
  initra.subdflag=subd_flag;
  initra.rectype=rec_type;
  movmem(transfer.path_dest,initra.path_mast,sizeof(transfer.path_dest));
  movmem(transfer.path_source,initra.path_slav,sizeof(transfer.path_source));
  send_cmd((char *)&initra);
}
 
void send_open()
{
  char drive[3], path[64], node[9], ext[4];
  char _driv[3], _path[64], _node[9], _ext[4];
							
  reqope.alwflag=alw_flag;
  movmem(transfer.path_dest,reqope.name,sizeof(transfer.path_dest));
  strsfn(reqope.name,drive,path,node,ext);
  strsfn(file[here].name,_driv,_path,_node,_ext);
  if (node[0]==0) {node[0]='*'; node[1]=0;}
  if (ext[0]==0) {ext[0]='*'; ext[1]=0;}
  upd_wild(node,_node);
  upd_wild(ext,_ext);
  strmfn(reqope.name,drive,path,node,ext);
  movmem(reqope.name,file[there].path,sizeof(file[0].path));
  reqope.size=file[here].size;
  reqope.time=file[here].time;
  reqope.attr=file[here].attr;
  movmem(file[here].path,reqope.name_orig,sizeof(file[0].path));
  send_cmd((char *)&reqope);
}

void send_write()
{
  int read_size, comp_size;
  char no_compress;
 
  no_compress=NO;
  if (conn_type==1 || comp_flag==YES) no_compress=YES;
  else {
    read_size=dread(file[here].ref,filebuf,rec_size);
    comp_size=compress(filebuf,read_size);
    if (comp_size>=read_size) {/* hypotetisch geval : compres wordt groter ! */
      dseek(file[here].ref,file[here].pos,0);
      no_compress=YES;
    }
    else movmem((char *)filebuf,reqwri.info,comp_size);
  }
  if (no_compress) {
    read_size=dread(file[here].ref,reqwri.info,rec_size);
    comp_size=read_size;/* to inform other party that no compress is needed */
  }
  reqwri.size=read_size;
  reqwri.comp_size=comp_size;
  file[here].pos+=read_size;
  if (file[here].pos>=file[here].size) reqwri.last=YES; else reqwri.last=NO;
  send_cmd((char *)&reqwri);
}

int compress(unsigned char *buf, int size)
{
  unsigned char byte;
  int wr_ptr, rd_ptr, i;

  wr_ptr=0; rd_ptr=0;
  while (rd_ptr<size) {
    if (wr_ptr>rd_ptr) {wr_ptr=size+1; break;}/* indicate compress failed */
    byte=buf[rd_ptr];
    i=1;
    while (byte==buf[rd_ptr+i] && i<255 && (rd_ptr+i)<size) i++;
    if (i>=4 || byte==COMP_CODE) {
      buf[wr_ptr++]=(unsigned char)COMP_CODE;
      buf[wr_ptr++]=byte;
      buf[wr_ptr++]=i;
      rd_ptr+=i;
    }
    else {
      while (i-->0) buf[wr_ptr++]=buf[rd_ptr++];
    }
  }
  return wr_ptr;
}

int decompress(unsigned char *buf,int size)
{
  int byte, count;
  int rd_ptr, wr_ptr;
 
  movmem((char *)buf,(char *)filebuf,size);
  wr_ptr=0; rd_ptr=0;
  while (rd_ptr<size) {
    if (filebuf[rd_ptr]==COMP_CODE) {
      rd_ptr++;
      byte=filebuf[rd_ptr++];
      count=filebuf[rd_ptr++];
      while (count-->0) {
	buf[wr_ptr++]=byte;
      }
    }
    else buf[wr_ptr++]=filebuf[rd_ptr++];
  }
  return wr_ptr;
}
 
int next_transfer()
{
  int i, j, k;
  char *p1, *p2;
  int readlen, len1, len2, ref;
 
  if (fileslst[0] && !file_loaded) {
    flst_ref=-1;
    ref=dopen(fileslst,RDMODE,0);
    if (ref<0) {
      CString cstr;
      cstr.Format("List of files not found : %1s",fileslst);
      LogAdd(58,0,"UC-Server",cstr);
    }
    file_len=dread(ref,file_buf,sizeof(file_buf));
    dclose(ref);
    if (file_len==sizeof(file_buf)) {
      CString cstr;
      cstr.Format("File %1s larger than buffer",fileslst);
      LogAdd(58,0,"UC-Server",cstr);
    }
    file_pos=0; file_loaded=YES;
  }
  FOREVER {
   next:;
    if (flst_ref>=0) {
      dseek(flst_ref,flst_pos,0);
      j=dread(flst_ref,buffer,60);
      if (j<=2) {
	dclose(flst_ref);
	if (flst_del) remove(flst_name);
	flst_ref=-1;
	goto next;
      }
      for (i=0; i<j; i++) {
	if (buffer[i]>' ') break;
      }
      if (i==j) {flst_pos+=j; goto next;}
      for (k=i+1; k<j; k++) {
	if (buffer[k]<=' ') break;
      }
      p1=buffer+i; len1=k-i;
      p2=flst_p2; len2=flst_len2;
      for (k++; k<j; k++) {
	if (buffer[k]>=' ') break;
      }
      flst_pos+=k;
    }
    else {
      if (file_loaded) {
	if (file_pos>=file_len-3) break;
	movmem(file_buf+file_pos,lst_item,sizeof(lst_item));
	readlen=sizeof(lst_item);
	if (readlen>(file_len-file_pos)) readlen=file_len-file_pos;
	for (i=0; i<sizeof(lst_item); i++) {
	  if (lst_item[i]<' ') {
	    lst_item[i++]=0;
	    for (; i<sizeof(lst_item); i++) {
	      if (lst_item[i]>' ') break;
	    }
	    file_pos+=i;
	    break;
	  }
	}
      }
      if (lst_item[0]<' ') break;
      make_caps(lst_item,sizeof(lst_item));
      for (i=0; i<sizeof(lst_item); i++) {
	if (lst_item[i]=='{') break;
      }
      if (i==sizeof(lst_item)) {
        CString cstr;
        cstr.Format("Not {to} or {from} found !");
        LogAdd(58,0,"UC-Server",cstr);
      }
      if (_cmpi(&lst_item[i],"{to}",4)==0) transfer.tx_flag=1;
      else if (_cmpi(&lst_item[i],"{from}",6)==0) transfer.tx_flag=0;
      else {
        CString cstr;
        cstr.Format("Only {to} and {from} are allowed !");
        LogAdd(58,0,"UC-Server",cstr);
      }
      p1=lst_item;
      for (i=0; i<sizeof(lst_item); i++) {
	if (lst_item[i]<=' ') break;
      }
      len1=i;
      for (; i<sizeof(lst_item); i++) {
	if (lst_item[i]=='}') break;
      }
      for (i++; i<sizeof(lst_item); i++) {
	if (lst_item[i]>' ') break;
      }
      p2=&lst_item[i]; len2=i;
      for (; i<sizeof(lst_item); i++) {
	if (lst_item[i]<=' ') break;
      }
      len2=i-len2;
 
      transfer.ren_flag=NO;
      transfer.del_flag=del_def;
      transfer.noe_flag=NO;
      flst_del=NO;
      for (; i<sizeof(lst_item); i++) {
	if (lst_item[i]<' ') break;
	if (lst_item[i]>' ') {
	  if (_cmpi(&lst_item[i],"/dellst",7)==0) {flst_del=YES; i+=7;}
	  if (_cmpi(&lst_item[i],"/ren",4)==0) {transfer.ren_flag=YES; i+=4;}
	  if (_cmpi(&lst_item[i],"/del",4)==0) {transfer.del_flag=YES; i+=4;}
	  if (_cmpi(&lst_item[i],"/noexist",8)==0) {transfer.noe_flag=YES; i+=8;}
	  else break;
	}
      }

      if (*p1=='[') {
	for (i=1; i<len1; i++) {
	  if (*(p1+i)==']') {*(p1+i)=0; break;}
	}
	movmem(p1+1,flst_name,sizeof(flst_name));
	flst_ref=dopen(flst_name,RDMODE,0);
        flst_pos=0L;
	flst_p2=p2; flst_len2=len2;
	goto next;/* volgende transfer */
      }
    }
 
    if (transfer.tx_flag) {
      movmem(p1,transfer.path_source,len1); transfer.path_source[len1]=0;
      movmem(p2,transfer.path_dest,len2); transfer.path_dest[len2]=0;
    }
    else {
      movmem(p2,transfer.path_source,len2); transfer.path_source[len2]=0;
      movmem(p1,transfer.path_dest,len1); transfer.path_dest[len1]=0;
    }
    updenv(transfer.path_source);
    updenv(transfer.path_dest);
 
    lst_item[0]=0;
    return YES;
  }
  return NO;
}

void updenv(char *inppath)
{
  int i, j, k;
  char *p;
 
  k=0;
  for (i=0; i<sizeof(path); i++) {
    if (!inppath[i]) break;
    if (inppath[i]=='%') {
      j=0;
      for (i++; i<sizeof(path); i++) {
	if (inppath[i]=='%') break;
	buf[j++]=inppath[i];
      }
      if (j>0) {
	buf[j]=0;
	p=getenv(buf);
      }
      if (p==0 || j==0) p="";
      while (*p) {
	path[k++]=*p++;
      }
    }
    else path[k++]=inppath[i];
  }
  for (; k<sizeof(path); k++) path[k]=0;
  movmem(path,inppath,sizeof(path));
}
 
int proc_open()
{
  char filename[15];
  long time, size;
 
  alw_flag=p_reqope->alwflag;
  file[here].attr=(char)p_reqope->attr;
  file[here].time=p_reqope->time;
  file[here].size=p_reqope->size;
  file[here].pos=0L;
  file[here].found=NO;
  movmem(p_reqope->name,file[here].path,sizeof(file[0].path));
  movmem(p_reqope->name_orig,file[there].path,sizeof(file[0].path));
  if (!pos_dir(p_reqope->name,YES)) {
    return 3;
  }
  make_fnme(p_reqope->name,filename);
  movmem(filename,file[here].name,sizeof(file[0].name));
  if (!_strcmpi(filename,excl_file)) return 99;/* skipped */
  if (conn_type!=1) printf("\rChecking : %-20s\r",filename);
  CString FilePath=UcCurrentDir;
  FilePath+=filename;
  file[here].ref=dopen((char*)(LPCTSTR)FilePath,RDWRMODE,0);
  if (file[here].ref<0) {
    if (errno==5) {
      chgfa((char*)(LPCTSTR)FilePath,0);
      file[here].ref=dopen((char*)(LPCTSTR)FilePath,RDWRMODE,0);
    }
    if (file[here].ref<0) {
      file[here].ref=dcreat((char*)(LPCTSTR)FilePath,CREAMODE);
      if (file[here].ref<0) {
	      return 2;
      }
    }
  }
  else {
    if (transfer.noe_flag) {
      dclose(file[here].ref);
      return 4;/* file already exists */
    }
  }
  time=getft(file[here].ref);
  size=dseek(file[here].ref,0L,2);
  dseek(file[here].ref,0L,0);
  if (size==file[here].size &&
      time==file[here].time &&
      alw_flag==NO) {
    dclose(file[here].ref);
    return 1;
  }
  file[here].found=YES; file[here].tx_flag=NO;
  return 0;
}

int proc_write()
{
  int new_size, written;
 
  if (p_reqwri->size > p_reqwri->comp_size) {
    new_size=decompress((unsigned char *)p_reqwri->info,p_reqwri->comp_size);
    if (new_size!=p_reqwri->size) {
      CString cstr;
      cstr.Format("Decompression failure from %4d to (%4d <-> %4d)",p_reqwri->comp_size,new_size,p_reqwri->size);
      LogAdd(58,0,"UC-Server",cstr);
    }
  }
  written=dwrite(file[here].ref,p_reqwri->info,p_reqwri->size);
  if (written != p_reqwri->size) return errno;
  file[here].pos+=written;
  return NO;
}

void proc_close(int error)
{
  char dummy[1];
  long size;
 
  if (error) {
    dclose(file[here].ref);
    CString FilePath=file[here].path;
    FilePath+=file[here].name;
    remove((char*)(LPCTSTR)FilePath);
    FileCntError++;
  }
  else {
    dwrite(file[here].ref,dummy,0);/* trucate file if shorter than orig */
    chgft(file[here].ref,file[here].time);
    if (file[here].size!=(size=dseek(file[here].ref,0L,2))) {
      CString cstr;
      cstr.Format("File size difference (%6ld/%6ld)",size,file[here].size);
      LogAdd(58,0,"UC-Server",cstr);
    }
    dclose(file[here].ref);
    chgfa(file[here].path,file[here].attr);
    file[here].rx_err--;
    file[here].rx_ok++;
    FileCntReceived++;
  }
}
 
void start_find()
{
  int error;
  char filename[15];
  
  file[here].found=NO; error=NO;
  hfileinfo[fileinfodept]=0;
  movmem(transfer.path_source,file[here].path,sizeof(file[0].path));
  if (pos_dir(transfer.path_source,NO)) {
    make_fnme(transfer.path_source,filename);
    fileinfodept=0;
    CString File2Find=UcCurrentDir+filename;
    hfileinfo[fileinfodept]=(int)(FindFirstFile(File2Find,&fileinfo[fileinfodept]));
    if (hfileinfo[fileinfodept]==(int)INVALID_HANDLE_VALUE) error=YES;
    if (!_strcmpi(getfilename(fileinfodept),excl_file)) {
      error=!FindNextFile((HANDLE)hfileinfo[fileinfodept],&fileinfo[fileinfodept]);
    }
    error=proc_subdir(error);
    if (!error) open_file();
    if (one_file(filename)) {
      FindClose((HANDLE)hfileinfo[fileinfodept]);
      hfileinfo[fileinfodept]=NULL;
    }
  }
}

char *getfilename(int ix)
{
  char *s;

  s=fileinfo[ix].cAlternateFileName;
  if (!*s) s=fileinfo[fileinfodept].cFileName;
  return s;
}

int proc_subdir(int error)
{
  char drive[3], path[64], node[9], ext[4];
 
  FOREVER {
    if (fileinfodept==0 && !subd_flag && fileinfo[fileinfodept].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      if (hfileinfo[fileinfodept]==NULL) error=true;
      else error=!FindNextFile((HANDLE)hfileinfo[fileinfodept],&fileinfo[fileinfodept]);
      if (error) break;
	  continue;
    }
    
    if (!error) {
      if ((fileinfo[fileinfodept].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (fileinfodept<MAX_SUBDIR_DEPT)) {
        if (!strcmp(getfilename(fileinfodept),"..") || (!strcmp(getfilename(fileinfodept),"."))) {
	        error=!FindNextFile((HANDLE)hfileinfo[fileinfodept],&fileinfo[fileinfodept]);
	  	  }
	      else {
	        fileinfodept++;
	        strsfn(transfer.path_source,drive,path,node,ext);
	        sprintf(path,"%1s%1s%1s",path,"\\",getfilename(fileinfodept));
	        strmfn(transfer.path_source,drive,path,"*","*");
	        strsfn(transfer.path_dest,drive,path,node,ext);
	        sprintf(path,"%1s%1s%1s",path,"\\",getfilename(fileinfodept));
	        strmfn(transfer.path_dest,drive,path,"*","*");
          CString File2Find=fileinfo[fileinfodept].cFileName;
          File2Find+="\\*.*";
	        hfileinfo[fileinfodept]=(int)FindFirstFile(File2Find,&fileinfo[fileinfodept]);
		    }
      }
      else break;
    }
    else {
      if (hfileinfo[fileinfodept]==NULL) error=true;
      else FindClose((HANDLE)hfileinfo[fileinfodept]);
      if (fileinfodept>0) {
        fileinfodept--;
	      // SetCurrentDirectory(".."); is niet nodig denk ik ! Deze info zit in de 
	      error=!FindNextFile((HANDLE)hfileinfo[fileinfodept],&fileinfo[fileinfodept]);
      }
      else break;
    }
  }
  return error;
}

void next_find()
{
  char mwgname[80];
  int error;
 
  if (file[here].found) {
    dclose(file[here].ref);
    if (transfer.del_flag && file[here].send_ok) {
			CString FilePath=UcCurrentDir+file[here].name;
			remove(FilePath);
		}
    if (transfer.ren_flag && file[here].send_ok) {
      strmfe(mwgname,file[here].name,"old");
			CString MwgFilePath=UcCurrentDir+mwgname;
			CString FilePath=UcCurrentDir+file[here].name;
      remove(MwgFilePath);
      rename(FilePath,MwgFilePath);
    }
    file[here].found=NO;
  }
  if (hfileinfo[fileinfodept]==NULL) error=true;
  else error=!FindNextFile((HANDLE)hfileinfo[fileinfodept],&fileinfo[fileinfodept]);
  if (!_strcmpi(getfilename(fileinfodept),excl_file)) {
    error=!FindNextFile((HANDLE)hfileinfo[fileinfodept],&fileinfo[fileinfodept]);
  }
  error=proc_subdir(error);
  if (!error) {
    movmem(transfer.path_source,file[here].path,sizeof(file[0].path));
    open_file();
  }
  else file[here].found=NO;
}
 
int one_file(char *s)
{
  while (*s) {
    if (*s=='?' || *s=='*') return NO;
    s++;
  }
  return YES;
}
 
void open_file()
{
  char drive[3], node[9], ext[4];
  int i;
 
  file[here].found=YES; file[here].send_ok=NO;
  movmem(getfilename(fileinfodept),file[here].name,sizeof(file[0].name));
  CString FilePath=UcCurrentDir+file[here].name;
  file[here].attr=getfa((char *)(LPCTSTR)FilePath);
  printf("\rChecking : %-20s\r",file[here].name);
  file[here].ref=dopen((char *)(LPCTSTR)FilePath,RDMODE,0);
  if (file[here].ref<0) {
    CString cstr;
    cstr.Format("Impossible to open INPUT-file : %1s",(char *)(LPCTSTR)FilePath);
    LogAdd(58,0,"UC-Server",cstr);
  }
  file[here].time=getft(file[here].ref);
  file[here].size=dseek(file[here].ref,0L,2);
  file[here].pos=0L;
  file[here].tx_flag=YES;
  dseek(file[here].ref,0L,0);
  strsfn(file[here].path,drive,path,node,ext);
  stcgfe(ext,file[here].name);
  for (i=0; i<sizeof(node); i++) {
    if ((node[i]=file[here].name[i])=='.') {node[i]=0; break;}
    if (node[i]==0) break;
  }
  strmfn(file[here].path,drive,path,node,ext);
}
 
void adj_recsize()
{
  int size;
 
  size=old_REC_SIZE;
  if (rec_type==1) size=1024;
  if (rec_type==2) size=256;
  
  if (rec_type==100) rec_size=REC_SIZE;
  else if (rec_size>size) rec_size=size;
}

void make_fnme(char *filename, char *node_ext)
{
  char *s, *d, drive[3], path[64], node[9], ext[4];

  strsfn(filename,drive,path,node,ext);
  d=node_ext;
  s=node;
  while (*s) *d++=*s++;
  s=ext;
  if (*s) *d++='.';
  while (*s) *d++=*s++;
  *d=0;
}
 
int pos_dir(char *filename,char make_fl)
{
  char drive[3], path[300], node[50], ext[4], subdir[300],dummy[200];
  char *s, *d;

  dir_changed=YES;
  strsfn(filename,drive,path,node,ext);
  if (drive[0]<=' ') {
    strsfn(saveCurrentDirectory,drive,dummy,dummy,dummy);
  }
  strmfn(subdir,drive,path,"","");


  // Corrigeer alle path-names, voorlopig enkel transfer voor x:\kassa, x:\PDA en x:\JamaPDA ...
  // alles komt in PathJamaRoot (bv. c:\jamadata\) en subdirs kassa, Pda
  CString UcCurrentDirUpper;

  UcCurrentDir=UcCurrentDirUpper=subdir;
  UcCurrentDirUpper.MakeUpper();
  int i=UcCurrentDirUpper.Find("KASSA\\");
  if (i>=0) {
    UcCurrentDir=PathJamaRoot+"KASSA\\"+UcCurrentDir.Mid(i+6);
  }
  else {
    i=UcCurrentDirUpper.Find("JAMAPDA\\");
    if (i>=0) {
      UcCurrentDir=PathJamaRoot+"JamaPDA\\"+UcCurrentDir.Mid(i+8);
    }
    else {
      i=UcCurrentDirUpper.Find("PDA\\");
      if (i>=0) {
        UcCurrentDir=PathJamaRoot+"JamaPDA\\"+UcCurrentDir.Mid(i+4);
      }
      else UcCurrentDir="\\Bad\\"+UcCurrentDir;
    }
  }

  sprintf(subdir,"%s", (char *)(LPCTSTR)UcCurrentDir);

  // einde

  if (GetFileAttributes(subdir)!=INVALID_FILE_ATTRIBUTES) return YES;
  if (subdir[0] && make_fl) {
    s=subdir; d=path;
    while (*s) {
      while (*s) {
        if (*s=='\\') {
	        *d=0;
	        CreateDirectory(path,NULL);
	      }
        *d++=*s++;
      }
    }
    CreateDirectory(subdir,NULL);
    if (GetFileAttributes(subdir)!=INVALID_FILE_ATTRIBUTES) return YES;
  }
  return NO;
}

int get_string(char *d, char *s)
{
  int len;
 
  len=0; 
  FOREVER {
    if (!(*d=*s++)) break;
    if (*d!='"') {
      if (*d>='a' && *d<='z') *d+='A'-'a';
      d++;
    }
  }
  return len;
}

int get_getal(char *s)
{
  int getal;
 
  stcd_i(s,&getal);
  return getal;
}

unsigned get_hex(char *s)
{
  unsigned getal;
 
  stch_i(s,&getal);
  return getal;
}
 
void wait(int hun)
{
  long timeout;
 
  timeout=get_hun()+hun;
  while (timeout>get_hun());
}
 
void upd_wild(char *d, char *s)
{
  char complete;
 
  complete=NO;
  FOREVER {
    if (*d=='*') complete=YES;
    if (complete || *d=='?') {
      if ((*d++=*s++)==0) break;
    }
    else {
      if (*d++==0) break;
      if (*s) s++;
    }
  }
}
 
void make_caps(char *s, int len)
{
  while (len-->0) {
    if (*s>='a' && *s<='z') *s+='A'-'a';
    if (*s++==0) break;
  }
}
 
int _cmpi(char *a, char *b, int len)
{
  char aa, bb;

  while (len-->0) {
    aa=*a; bb=*b;
    if (aa>='a' && aa<='z') aa+='A'-'a';
    if (bb>='a' && bb<='z') bb+='A'-'a';
    if (aa<bb) return -1;
    if (aa>bb) return  1;
    a++; b++;
  }
  return 0;
}

/* socket modules */

void proc_socket()
{
  try {
  // Initiate Winsock.
    if (WSAStartup (MAKEWORD(1,1), &WSAData) != 0) {
      printf("No WinSocket found !\r\n");
    }
    if ((l_sock = listen_socket(SockPort)) == INVALID_SOCKET) { 
      perror("listen_socket");
    }
  } catch(...) {
  }
}

void accept_sock()
{
// accept will wait for incoming call, and will block. Use select()
  struct fd_set rf;
  struct timeval tv;
  SOCKADDR_IN sa;
  int state, size;
  
  try {
  rf.fd_count=1;
  rf.fd_array[0]=l_sock;
  tv.tv_sec=0; tv.tv_usec=0;
  state=select(0,&rf,NULL,NULL,&tv); // state==1 -> ready, connection pending

  if (state==1) {
    sock = accept(l_sock, NULL, NULL);
    if (sock == INVALID_SOCKET) {
      fprintf(stderr, "Error on accepting new connection!\n");
      return;
    }
    closesocket(l_sock); 
    size=sizeof(struct sockaddr);
    getpeername(sock,(SOCKADDR *)&sa,&size);
    movmem(inet_ntoa(sa.sin_addr),rem_ipaddr,sizeof(rem_ipaddr));
    printf("Connected to %1s !%40s\r\n",rem_ipaddr,"");
  }
  } catch(...) {
      return;
  }
}

void sock_close()
{
  try {
    closesocket(l_sock); l_sock=INVALID_SOCKET;
    closesocket(sock); sock=INVALID_SOCKET;
    WSACleanup();
  } catch(...) {
  }
}

SOCKET listen_socket(unsigned short portnum)
{ char   myname[256];
  SOCKET s;
  struct sockaddr_in sa;
  struct hostent *hp;

  try {
    memset(&sa, 0, sizeof(struct sockaddr_in)); /* clear our address */
    gethostname(myname, sizeof(myname));        /* who are we? */
    hp = gethostbyname(myname);                 /* get our address info */
    if (hp == NULL)                             /* we don't exist !? */
      return(INVALID_SOCKET);
    sa.sin_family = hp->h_addrtype;             /* this is our host address */
    sa.sin_port = htons(portnum);               /* this is our port number */
    s = socket(AF_INET, SOCK_STREAM, 0);        /* create the socket */
    if (s == INVALID_SOCKET)
      return INVALID_SOCKET;

    /* bind the socket to the internet address */
    if (bind(s, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) ==
        SOCKET_ERROR) {
      closesocket(s);
      return(INVALID_SOCKET);
    }
    listen(s, 1);                               /* max # of queued connects */
    return(s);
  } catch(...) {
  }
  return (INVALID_SOCKET);
}

SOCKET call_socket(const char *hostname, unsigned short portnum)
{ struct sockaddr_in sa;
  struct hostent     *hp;
  SOCKET s;

  try {
    hp = gethostbyname(hostname);
    if (hp == NULL) /* we don't know who this host is */
      return INVALID_SOCKET;

    memset(&sa,0,sizeof(sa));
    memcpy((char *)&sa.sin_addr, hp->h_addr, hp->h_length);   /* set address */
    sa.sin_family = hp->h_addrtype;
    sa.sin_port = htons((u_short)portnum);

    s = socket(hp->h_addrtype, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
      return INVALID_SOCKET;

    /* try to connect to the specified socket */
    if (connect(s, (struct sockaddr *)&sa, sizeof sa) == SOCKET_ERROR) {
      closesocket(s);
      return INVALID_SOCKET;
    }
    return s;
  } catch(...) {
  }
  return (INVALID_SOCKET);
}

void send_sock(int size, char *s)
{
  int i;
  char buf[CMD_SIZE+100];

  try {
    memcpy(buf,&size,2);
    memcpy(buf+2,s,size);
    if (deb_flag) TRACE("\r\nSending %5d characters : ",size);
    i=send(sock,buf,size+2,0);
    if (deb_flag) TRACE("OK.\r\n");
    if (i!=size+2) {
      TRACE("Problems with send through socket !\r\n");
    }
  }  catch(...) {
  }
}

void rec_sock()
{
  short int _size;
  char *s;
  unsigned long l;

  try {
  if (ioctlsocket(sock,FIONREAD,&l)) l=0;
  if (sock!=INVALID_SOCKET && l) {
    if (here==0) {
      //code van oude master
    }
    else {
      s=s_in_cmd;
      s_in_flag=YES;
    }
    sock_recv_buf((char *)&_size,sizeof(_size));
    if (deb_flag) printf("\r\nReceiving %5d characters : ",_size);
    if (_size<0 || _size>CMD_SIZE) {
      printf("Problems with receiving size info (%6d).\r\n",_size);
      return;
    }
    sock_recv_buf(s, _size);
    theApp.UCServerWatchDog=0; // er is een volledig pakket ontvangen !
    if (deb_flag) printf("OK.\r\n");
  }
  }  catch(...) {
      return;
  }
}

void sock_recv_buf(char *s,int size)
{
  int ret, used;

  try {
  used=0;
  while (used<size) {
    ret=recv(sock,&s[used],size-used,0);
    if (ret==SOCKET_ERROR) {
      printf("Problems with recv socket for %6d bytes !\r\n",size);
      return;
    }
    used+=ret;
  }
  }  catch(...) {
      return;
  }
}

//compatibility LATTICE library

void movmem(char *source, char *dest, int size)
{
  memmove(dest, source, size);
}

void strmfn(char *file,char *drive,char *path,char *node,char *ext)
{
  char path_flag, ext_flag;
  int len;
 
  len=64; path_flag=NO; ext_flag=YES;
  while (len-->0) {
    if (*drive) *file++=*drive++;
    else if (*path) {
      if ((*file++=*path++)!='\\') path_flag=YES;
    }
    else if (path_flag) {
      path_flag=NO; *file++='\\';
    }
    else if (*node) *file++=*node++;
    else if (*ext) {
      if (ext_flag) {*file++='.'; ext_flag=NO;}
      else *file++=*ext++;
    }
    else {
      *file=0;
      break;
    }
  }
}
 
void strsfn(char *file,char *drive,char *path,char *node,char *ext)
{
  int i, j, len;

  drive[0]=0; path[0]=0; node[0]=0; ext[0]=0;
  for (j=0; j<64; j++) {
    if (file[j]==0) break;
  }
  if (j==64) {file[63]=0; j=63;}
  len=j;
  i=0;
  if (file[i+1]==':') {movmem(&file[i],drive,2); drive[i+2]=0; i+=2;}
  for (j=len-1; j>=i; j--) {
    if (file[j]=='\\') break;
  }
  if (j==i) {/* path is \ */
    path[0]='\\'; path[1]=0;
    i++;
  }
  else if (j>i) {
    movmem(&file[i],path,j-i); path[j-i]=0; i=j+1;
  }
  for (j=i; j<len; j++) {
    if (file[j]=='.') break;
  }
  if (j>i) {
    movmem(&file[i],node,j-i); node[j-i]=0; i=j+1;
  }
  if (i<len) {
    movmem(&file[i],ext,len-i); ext[len-i]=0;
  }
}

void strmfe(char *newname, char *oldname, char *ext)
{
  char drive[3], path[200], node[200], dummy[20];

  strsfn(oldname,drive,path,node,dummy);
  strmfn(newname,drive,path,node,ext);
}

void stcgfe(char *ext,char *filename)
{
  char drive[3], path[200], node[200];

  strsfn(filename,drive,path,node,ext);
}

int dopen(char *filename,int mode, int extra)
{
  return _lopen(filename,mode);
}

int dcreat(const char *filename, int pmode)
{
  return _lcreat(filename,pmode);

}

int dwrite(int handle, const void *buffer, unsigned int count)
{
  return _lwrite(handle, (char *)buffer, count);
}

int dread(int handle, void *buffer, unsigned int count)
{
  return _lread(handle, buffer, count);
}

long dseek(int handle,long pos, int mode)
{
  return _llseek(handle, pos, mode);
}

int dclose(int handle)
{
  return _lclose(handle);
}

int getfa(char *filename) 
{
  return (GetFileAttributes(filename) & 0x3F);
}

int chgfa(char *filename, int fa)
{
  DWORD status;

  status=GetFileAttributes(filename);
  status = (status & 0xFFFFFFC0) | fa;
  return SetFileAttributes(filename,status);
}

long getft(int fHandle)
{
  FILETIME FileTime, dummy1, dummy2;
  long ret;
  WORD *FatDate, *FatTime;
   
  if (GetFileTime((HANDLE)fHandle,&dummy1,&dummy2,&FileTime)) {
    FatDate=(WORD *) &ret;
    FatDate++;
    FatTime=(WORD *) &ret;
    UTCAdjust(&FileTime,NO);
    FileTimeToDosDateTime(&FileTime, FatDate, FatTime);
   return ret;
  }
  else {
    return -1L;
  }
}

int chgft(int fHandle, long ft)
{
  FILETIME FileTime, dummy1, dummy2;
  WORD *FatDate, *FatTime;
  
  FatDate=(WORD *) &ft;
  FatDate++;
  FatTime=(WORD *) &ft;
  if (GetFileTime((HANDLE)fHandle,&dummy1,&dummy2,&FileTime)) {
    DosDateTimeToFileTime(*FatDate,*FatTime,&FileTime);
    UTCAdjust(&FileTime,YES);
    if (SetFileTime((HANDLE)fHandle,&dummy1,&dummy2,&FileTime)) {
      return 0;
    }
  }
  return -1;
}

void UTCAdjust(FILETIME *FileTime, int Local2UTC)
{
  DWORD64 *ft;
  _TIME_ZONE_INFORMATION TZInfo;
  LONG64 diff;

  ft=(DWORD64 *)FileTime;
  if (GetTimeZoneInformation(&TZInfo)!=TIME_ZONE_ID_UNKNOWN) {
    diff=(LONG64)TZInfo.Bias*NSECPERMIN;
    if (Local2UTC) *ft+=diff;
    else *ft-=diff; 
  }
}

unsigned stci_d(char *s,int in,int outlen)
{
  char buf[11];
  int i, j;

  for (i=0; i<11; i++) buf[i]=' ';
  i=0;
  if (in<0) {s[i++]='-'; in=-in;}
  if (in==0) s[i++]=0;
  else {
    j=10;
    while (in>0 && j>0) {
      buf[j]= in%10 + '0';
      in=in/10; j--;
    }
    j++;
    while (i<outlen) {
      if (j==11) break;
      s[i++]=buf[j++];
    }
  }
  s[i]=0;
  return i;
}

int stch_i(char *s,unsigned *r)
{
  int i;

  *r=0; i=0;
  while(*s) {
    if (*s>='a' && *s<='f') *s+='A'-'a';
    if (*s>='0' && *s<='9') *r=*r*16+*s-'0';
    else if (*s>='A' && *s<='F') *r=*r*16+10+*s-'A';
    else break;
  }
  return i;
}
 
int stcd_i(char *s,int *r)
{
  int neg,i,stop;

  *r=0; i=0; stop=0; neg=0;
  while(*s) {
    if ((*s>='0')&&(*s<='9')) *r=*r*10+*s-'0';
    else if (*s=='-') neg=1;
    else if (*s!='+') {stop=1; break;}
    i++;
    s++;
  }
  if(neg==1)*r=-*r;
  if(stop==1)i=-i;
  return(i);
}

int stcd_li(char *s,long *li)
{
  int neg,i,stop;
 
  *li=0; i=0; stop=0; neg=0;
  while(*s) {
    if ((*s>='0')&&(*s<='9')) *li=*li*10+*s-'0';
    else if (*s=='-') neg=1;
    else if (*s!='+') {stop=1; break;}
    i++;
    s++;
  }
  if(neg==1)*li=-*li;
  if(stop==1)i=-i;
  return(i);
}

void stcli_d (char *s,long l,int digits,char *lzerosup)
{
  int index, filler;

  if (lzerosup) filler=' ';
  else filler='0';
  for (index=0; index<digits; index++) s[index]=filler;
  s[digits]='\0';
  if (l<0) {s[0]='-'; l = -l;}
  index = digits-1;
  do {
    s[index] = l % 10 + '0';
    index--;
  } while ((l /= 10) > 0);
}

static int stcd_df(char *s,double *df)
{
  char ap;
  int neg,i,stop;
  double add;
 
  *df=0; i=0; stop=0; neg=0; ap=0; add=0.1;
  while(*s) {
    if ((*s>='0')&&(*s<='9')) {
      if (ap) {
        *df+=((*s-'0') * add);
        add/=10.;
      }
      else *df=*df*10+*s-'0';
    }
    else if (*s=='.' || *s==',') ap=1;
    else if (*s=='-') neg=1;
    else if (*s!='+') {stop=1; break;}
    i++;
    s++;
  }
  if(neg==1)  *df=-*df;
  if(stop==1) i=-i;
  return(i);
}

void stcdf_d (char *s,double df,int digits,char *lzerosup)
{
  long l_low, l_high;

  if (digits<10) {
    l_low = (long)df;
    stcli_d(s,l_low,digits,lzerosup);
  }
  else {
    l_high = (long)(df/1E6); l_low = (long)(df - l_high * 1E6);
    stcli_d(s,l_high,digits-6,lzerosup);
    stcli_d(s+6,l_low,6,0);
  }
}

long get_hun()
{
  DWORD ticks;
  long hun;
							
  ticks = GetTickCount();
  hun = ticks/10;
  return hun;
}

/* einde UC.cpp 

nu volgt nieuwe code om deze routines op te roepen in de JMS
*/
void RunUCServer(void* dummy)
{
  slav_flag=YES;
  conn_type=5;
  rec_type=100;
  SockPort=5000;
  iddisp_fl=YES;
  sprintf(saveCurrentDirectory,"%s", (char *)(LPCTSTR)PathProg);

  int reconnect;
  LogAdd(0,1,"UC-Server starting-up");
  while (!JMSShuttingDown) {
    if (l_sock==INVALID_SOCKET) proc_socket();
    slav_status=-1; 
    while (!JMSShuttingDown) {
      if (sock==INVALID_SOCKET) {
        accept_sock();
        if (sock==INVALID_SOCKET) {
					Sleep(1000);
  	      theApp.UCServerWatchDog=0;
				}
        else {
          LogAdd(0,1,"Connection received from",rem_ipaddr);
          FileCntTransmitted=FileCntReceived=FileCntIdentical=FileCntError=0;
          slav_status=-1;
        }
      }
      if (fatal_err || (reconnect=slave())) {
	      fatal_err=NO;
        LogAdd(0,1,"Connection ended:",rem_ipaddr);
        sock_close();
        break;
      }
      rec_cmd();/* check for incoming messages */
    }
  }
  if (JMSShuttingDown) theApp.UCServerWatchDog=0;
  sock_close();
  theApp.UCServerhThread=(HANDLE)-1L; // set handle to invalid !
}