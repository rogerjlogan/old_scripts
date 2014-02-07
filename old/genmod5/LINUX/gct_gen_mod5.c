/* Feb 00 Anthony Sully, LTX Corp. Created for C6202/3 after suffering through C6201 and
                                   spec. timing with alternate dsets. This file processes
                                   the polaris cycletbl.p file with minor edits to figure
                                   out what the dset selects are and creates a simplified
                                   version of this that is easy and quick to read for each
                                   pattern translation. */
/* Sept. 02 Anthony Sully, LTX Corp. Modified for microcontroller translations added smarts
                                   so it can also determine the scan pins. At the moment
                                   only one pair is allowed. */
/* 09/28/02 Anthony Sully, LTX Corp. Fixed a bug in the pin matching routine where it was
                                   matching a pin with a superset pinname. i.e. TMS was
                                   found as TMS2. This happened if the superset pin came
                                   first. Now lengths are also required to match. Also,
                                   added code to ignore non-alphanumeric lines.*/

/* 11/02/02 Anthony Sully, LTX Corp. Fixed compile script and includes so date can be brought in with
                                     gcc or cc */

/* 06/27/08 Anthony Sully, LTX Corp. Add support for reading device.p for pinlists, muxmode
                                     and hex pattern mode support as well as 
                                     VectorMapSet and VectorMapSetCycle */
/* 07/30/08-08/08/08 Anthony Sully, LTX Corp. Modified the waveform identification processing.
                                     We now read actable.p, crunch it, and try and find the
                                     DSET0,DSET1 wfm names in actable. From that we try and
                                     determine the REAL format, instead of guessing from the
                                     name. Also added duplicate pinlist checking warning. 
                                     Added new feature which attempts to generate a waveformtable
                                     file. The flaw with this is the conditional statements. A
                                     pure actable.p file would work perfectly. If there are lots
                                     of conditionals then we get too many waveform cells.
                                     Pattern characters are now determined from the waveform
                                     assignments since we generate both here.
                                     updated rev. to gct_gen_mod5.c (results create a .mod5 file) */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ggm_includes.h"

/********************************/
/*                              */
/*      main() function         */
/*                              */
/********************************/
int main (int argc,char *argv[]){

/*******************************************/
/*  VARIABLES                              */
/*******************************************/
/* file variables */
FILE *fpin1,*fpin2,*fpin3,*fpout1,*fpwaves;
int filein1=0,filein2=0,filein3=0,filein4=0;
char infile1[FILENAMELEN];
char infile2[FILENAMELEN];
char infile3[FILENAMELEN];
char infile4[FILENAMELEN];
char outfile1[FILENAMELEN];
char pattern[FILENAMELEN];
char pinheader[PINSIZE][NUMPINS];

/* buffers */
char readstr[READLINELEN];
char progstr[MEMOSTRLEN],datestr[MEMOSTRLEN],timestr[MEMOSTRLEN],compilestr[MEMOSTRLEN];/* concaternated strings */
char vector[NUMPINS],CELL1[MEMOSTRLEN],CELL2[MEMOSTRLEN];
char CELL1P[MEMOSTRLEN],CELL2P[MEMOSTRLEN],CELL1C[MEMOSTRLEN],CELL2C[MEMOSTRLEN];
char PREVGCT[GCTSIZE],PINNAME[PINSIZE];
char tempgrpexpand[READLINELEN*20+1],tempgrpexpand2[READLINELEN*20+1];
char VectorMapSet[READLINELEN+1];
char hexproc[READLINELEN+1],fieldset[READLINELEN+1],hex_or_bin;
char muxpin[READLINELEN+1];
int sizehead;

/* control parameters */
int pin,gctstart,gctend,pinstart,pinend;
int flag_group,mode,fieldcount,device_pingroup;
/* temporary variables */
int i,j,k,l;
char *ptr0,*ptr,*ptr1,*ptr2,*ptr3,*ptrSCAN;

int stwf2,plen,plens,c1wf,c2wf,wftpending;
//int hex1chkwf,hex2chkwf;
long linenum=0;
int actablelines;

int used_line[ACTABLELINES],wfmcode0,wfmcode1;

struct FORMAT_SEARCH fmt_srch;

char fmtline0[ACTABLELEN],fmtline1[ACTABLELEN];/* line storage string */

char newwavetable[50],tperiod[50];
int START_WFMT=0;

newwavetable[0]='\0';
strcpy(tperiod,"DUMMY_TPERIOD_FIXME");
/* convert this to a long string for direct searching */
for (i=0;i<SIZE_WAVETYPES-1;i++) {
   if (*(&wavetypes[0][0]+i)=='\0') wavetypefull[i]=' ';
   else wavetypefull[i]=*(&wavetypes[0][0]+i);
   }
wavetypefull[i-1]='\0';

for (i=0;i<SIZE_EDGETYPE-1;i++) {
   if (*(&edgetypes[0][0]+i)=='\0') edgetypefull[i]=' ';
   else edgetypefull[i]=*(&edgetypes[0][0]+i);
   }
edgetypefull[i-1]='\0';

/***************************************************/
/* command line stuff */
/***************************************************/

pinlist=(PINLIST *)calloc(MAXlists,sizeof(PINLIST));
if (pinlist==NULL) {fprintf(stderr,"Could not allocate memory for pinlist, exiting\n");exit(1);}
fprintf(stderr,"allocated [%d] bytes for PINLIST @%p\n",(MAXlists)*(sizeof(PINLIST)),pinlist);

cellinfo=(CELL_INFO *)calloc(MAXCELLS,sizeof(CELL_INFO));
if (cellinfo==NULL) {fprintf(stderr,"Could not allocate memory for cellinfo, exiting\n");exit(1);}
fprintf(stderr,"allocated [%d] bytes for CELL_INFO @%p\n",(MAXCELLS)*(sizeof(CELL_INFO)),cellinfo);
cellcnt=0;

//EO=(char *[MAXORIGINS][ORIGINSIZE+1]) calloc(MAXORIGINS,ORIGINSIZE+1);
//if (EO==NULL) {fprintf(stderr,"Could not allocate memory for ENABLE ORIGINS, exiting\n");exit(1);}
EOCNT=0;
if (argc>1) {
   if (strchr((char *)argv[1],'-')!=NULL){
      if (strchr((char *)argv[1],'f')!=NULL && argc>=3) filein1 = 1;
      if (strchr((char *)argv[1],'p')!=NULL && argc>=4) filein2 = 1;
      if (strchr((char *)argv[1],'d')!=NULL && argc>=5) filein3 = 1;
      if (strchr((char *)argv[1],'a')!=NULL && argc>=6) filein4 = 1;
      }   
   }
   
strcpy(progstr,__FILE__);
strcpy(datestr,__DATE__);
strcpy(timestr,__TIME__);
strcpy(compilestr,argv[0]);
fprintf(stderr,"\n\n%s:%s, by Anthony Sully\n covered by GNU GPL license, see the file COPYING.gz in the source directory\n",compilestr,progstr);
if (argc==1) {
   fprintf(stderr,"\n%s: %s\n",progstr,compilestr);
   fprintf(stderr,"%s by Anthony Sully\n",datestr);
   fprintf(stderr,"options are:\n");
   fprintf(stderr,"f => cycletbl_mod file follows\n");
   fprintf(stderr,"p => pin file follows\n");
   fprintf(stderr,"d => device.p follows (optional)\n\n");
   fprintf(stderr,"a => actable.p follows (optional)\n\n");
   fprintf(stderr,"\nUsage:%s -fp GCTinfo.file pin.file\n",argv[0]);
   fprintf(stderr,"\n or  :%s -fpda GCTinfo.file pin.file device.p actable.p\n",argv[0]);
   fprintf(stderr,"NEW:reading device.p is now supported for pinlists\n");
   fprintf(stderr,"NEW:reading actable.p is now supported for processing cell types\n");
   exit(0);
   }

/*****************/
/*  FILE STUFF   */
/*****************/

/* open input file */
if (filein1) strcpy(infile1,(char *) argv[2]);
/* open pin file */
if (filein2) strcpy(infile2,(char *) argv[3]);
/* open device.p file */
if (filein3) strcpy(infile3,(char *) argv[4]);
/* open actable_mod.p file */
if (filein4) strcpy(infile4,(char *) argv[5]);

strcpy(outfile1,infile1);
i=0;
while (NULL!=(ptr=strchr(outfile1,'/'))){
   i=(ptr-outfile1);
   outfile1[i]=' ';i++;
   }
j=0;
while(NULL==strchr(". ",outfile1[i]) && i<strlen(outfile1) ) pattern[j++]=outfile1[i++];
pattern[j]='\0';
fprintf(stdout,"\nGCT file:%s\n",pattern);
if (NULL==(fpin1=fopen(infile1,"r"))) {
   fprintf(stderr,"\nInput file [%s] not found\n",infile1);
   exit(1);
   }
fprintf(stderr,"input file1<%s> ok\n",infile1);
if (NULL==(fpin2=fopen(infile2,"r"))) {
   fprintf(stderr,"\nInput file [%s] not found\n",infile2);
   exit(1);
   }
if (NULL==(fpin3=fopen(infile3,"r"))) {
   fprintf(stderr,"\nInput file [%s] not found\n",infile3);
   exit(1);
   }
fprintf(stderr,"input file2<%s> ok\n",infile2);
   sprintf(outfile1,"%s%s",pattern,MODVER);
   if (NULL==(fpout1=fopen(outfile1,"w"))) {
      fprintf(stderr,"\nCould not open output file [%s] for output\n",outfile1);
      exit(1);
      }
fprintf(fpout1,"#USE_SIGNAL_HEADER:SH0\n");
if (filein1==0 ) {
   fprintf(stderr,"Inline syntax:\n%s -fpda %s %s %s %s\n",argv[0],infile1,infile2,infile3,infile4);
   }

process_pins(fpin2,fpin3,infile3,muxpin);
orgcnt=0;
acwaves=NULL;
actablelines=parse_actable(infile4,used_line,tperiod);
fprintf(stderr,"ACWAVES@=%p\n",acwaves);
fflush(stdout);

PREVGCT[0]='\0';   /* yes , it is ASCII 0 not \0*/
for (pin=0;pin<maxpin;pin++) vector[pin]='0';
vector[maxpin]='\0';

if (NULL==(fpwaves=fopen(WFTMODVER,"w"))) {
   fprintf(stderr,"\nCan't open file [%s]\n",WFTMODVER);
   exit(1);
   }

/***************************************************/
/* BEGIN MAIN LOOP */
/***************************************************/
VectorMapSet[0]='\0';
fieldcount='A';
for(i=0;i<maxpin;i++) fieldset[i]=hexproc[i]='.';
fieldset[i]=hexproc[i]='\0';
wftpending=0;
while(fgets(readstr,READLINELEN-1,fpin1) != NULL ){
   linenum++;
   readstr[strlen(readstr)-1] = '\0';/* remove trailing \n */
   for (j=i=0;i<strlen(readstr);i++) {/* strip whitespace */
      if (isgraph((int)readstr[i])){tempgrpexpand2[j]=readstr[i];j++;}
      } /* end strip white space */
   if (NULL!=(ptr2=(strstr(tempgrpexpand2,"VectorMapSetCycle")))) {
      }

   else if (NULL!=(ptr2=(strstr(readstr,"VectorMapSet")))) {
      if (NULL!=(ptrSCAN=(strstr(readstr,"Scan")))) {
         if (strstr(readstr,"ScanInOrderVM")!=NULL || strstr(readstr,"ScanInVM")!=NULL ){
            ptr2=ptr3=NULL;
            ptr1=strchr(readstr,',');/* first comma */
            if (ptr1!=NULL) ptr2=strchr(ptr1+1,',');/* second */
            if (ptr2!=NULL) ptr3=strchr(ptr2+1,',');/* third comma */
            for (i=0,ptr=ptr2+1;ptr<ptr3;ptr++) if (*ptr!=' ') {PINNAME[i]=*ptr;i++;}
            PINNAME[i]='\0';
            plen=strlen(PINNAME);
            for (pin=0;pin<maxpin;pin++) {
               if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==0 ) break;/* check that the pinname matches(or is a substring of the pinfile pin */
               if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==1 &&(PIN[pin][plen]=='0' || PIN[pin][plen]=='1'|| PIN[pin][plen]=='2' || PIN[pin][plen]=='3'|| PIN[pin][plen]=='m')) break;/* check that the pinname matches(or is a substring of the pinfile pin */
               }
            fprintf(fpout1,"?SCANINPIN:%s %d\n",PINNAME,pin+1);
            }
         else if (strstr(readstr,"ScanOutOrderVM")!=NULL || strstr(readstr,"ScanOutVM")!=NULL ){
            ptr2=ptr3=NULL;
            ptr1=strchr(readstr,',');/* first comma */
            if (ptr1!=NULL) ptr2=strchr(ptr1+1,',');/* second */
            if (ptr2!=NULL) ptr3=strchr(ptr2+1,',');/* third comma */
            for (i=0,ptr=ptr2+1;ptr<ptr3;ptr++) if (*ptr!=' ') {PINNAME[i]=*ptr;i++;}
            PINNAME[i]='\0';
            plen=strlen(PINNAME);
            for (pin=0;pin<maxpin;pin++) {
               if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==0 ) break;/* check that the pinname matches(or is a substring of the pinfile pin */
               if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==1 &&(PIN[pin][plen]=='0' || PIN[pin][plen]=='1'|| PIN[pin][plen]=='2' || PIN[pin][plen]=='3'|| PIN[pin][plen]=='m')) break;/* check that the pinname matches(or is a substring of the pinfile pin */
               }
            fprintf(fpout1,"?SCANOUTPIN:%s %d\n",PINNAME,pin+1);
            }
         }
      else {
         if      (NULL!=strstr(tempgrpexpand2,"Hex"   )) hex_or_bin='H';
         else if (NULL!=strstr(tempgrpexpand2,"Binary")) hex_or_bin='B';
         ptr=strchr(tempgrpexpand2,',');
         ptr0=strchr(tempgrpexpand2,'(');
         if (ptr!=NULL) ptr2=strchr(ptr+1,','); else ptr2=NULL;
         if (ptr2!=NULL) ptr3=strchr(ptr2+1,','); else ptr3=NULL;
         if (ptr0!=NULL && ptr!=NULL) {
            *ptr='\0';
            if (strstr(ptr0+1,"Scan")!=NULL) ; /* shouldn't hit this now... if its a scan then skip it here */
            else if (VectorMapSet[0]=='\0') strcpy(VectorMapSet,ptr0+1);
            else if (0!=strcmp(VectorMapSet,ptr0+1)) {
               fprintf(stderr,"************\nMultiple VectorMapSets not supported in [%s]\n",infile1);
               fprintf(stderr,"Please request support or split the file!!!\n*************\n");
               exit(7);
               }
            *ptr=',';
            }
         if (ptr2!=NULL && ptr3!=NULL) {
            *ptr3='\0';
            strcpy(tempgrpexpand,ptr2+1);
            *ptr3=',';
            }
         for (i=0;i<maxlists;i++) if (0==strcmp(tempgrpexpand,pinlist[i].pinlistname)){
            for (j=0;j<maxpin;j++) if (pinlist[i].pinlists[j]=='*') {
               hexproc[j]=hex_or_bin;
               fieldset[j]=fieldcount;
               }
            break;
            }   
         fieldcount++;
         }
      }
   /* get subcomponent boundaries of line */
   else if (NULL!=(ptr2=(strstr(readstr,"CycleSetMD")))) {
      gctstart=(int)(strchr(readstr,'(')-&readstr[0])+1;
      gctend=(int)(strchr(readstr,',')-&readstr[0])-1;
      readstr[gctend+1]='~'; /* Disable for next comma search */
      ptr3=strchr(readstr,',');
      if (ptr3==NULL) continue;/* it might be in a comment.... */
      stwf2=(int)(ptr3-&readstr[0])+1;
      readstr[stwf2-1]='~';
      ptr3=strchr(readstr,',');
      if (ptr3==NULL) continue;/* it might still be in a comment.... */
      pinstart=(int)(ptr3-&readstr[0])+1;
      ptr3=strchr(readstr,')');
      if (ptr3==NULL) continue;/* it might still be in a comment.... */
      pinend=(int)(ptr3-&readstr[0])-1;
   
      if(DEBUG) fprintf(stdout,"<%s>\ngs%d ge%d ps%d pe%d\n",readstr,gctstart,gctend,pinstart,pinend);
   
      /* get subcomponents */
   
      for (j=0,i=gctstart;i<=gctend;i++) if(readstr[i]!=' ' && readstr[i]!='\t') GCTNAME[j++]=readstr[i];
      GCTNAME[j]='\0';
      if (DEBUG) fprintf(stdout,"GCTNAME=[%s]\n",GCTNAME);
   
      for (j=0,i=pinstart;i<=pinend;i++) if(readstr[i]!=' ' && readstr[i]!='\t') PINNAME[j++]=readstr[i];
      PINNAME[j]='\0';
      if (DEBUG) fprintf(stdout,"PINNAME=[%s]\n",PINNAME);
      device_pingroup=-1;
      flag_group=0;
      if (NULL!=(ptr=strstr(PINNAME,"xx"))) {
         flag_group=1;
         *ptr='\0';
         if(DEBUG) fprintf(stdout,"PINGROUP <%s> IDENTIFIED\n",PINNAME);
         }
      plen=strlen(PINNAME);
      plens=strlen(PIN[pin]);
      for (pin=0;pin<maxpin;pin++) {
         plens=strlen(PIN[pin]);
         if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==0 && plens==plen) break;/* check that the pinname matches(or is a substring of the pinfile pin */
         if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==1 &&(PIN[pin][plen]=='0' || PIN[pin][plen]=='1'|| PIN[pin][plen]=='2' || PIN[pin][plen]=='3'|| PIN[pin][plen]=='m')) break;/* check that the pinname matches(or is a substring of the pinfile pin */
         }
      if (pin==maxpin) {/* need to check groups */
         for (i=0;i<maxlists;i++) {
            if (0==strcmp(pinlist[i].pinlistname,PINNAME)) {device_pingroup=i;break;}
            }
         if (i==maxlists) {
            fprintf(stderr,"SE:*** PIN <%s> not found\n...skipping\n",PINNAME);
            fprintf(stdout,"SO:*** PIN <%s> not found\n...skipping\n",PINNAME);
            continue;
            }
         }
      if (flag_group){
         groupcount=0;
         for (;pin<maxpin;pin++) {
            if (strstr(PIN[pin],PINNAME)==PIN[pin]) groupcount++;
            else break;
            }
         /* if(DEBUG) */ fprintf(stdout,"PINGROUP <%s> FOUND, GROUPCOUNT=%d\n",PINNAME,groupcount);
         pin-=groupcount;
         }
   
      
      for(j=0,i=gctend+2;i<stwf2-1;i++) if(readstr[i]!=' ' && readstr[i]!='\t') CELL1[j++]=readstr[i];
      CELL1[j]='\0';
   
      for(j=0,i=stwf2;i<pinstart-1;i++) if(readstr[i]!=' ' && readstr[i]!='\t') CELL2[j++]=readstr[i];
      CELL2[j]='\0';
   
      if(DEBUG) fprintf(stdout,"CELL1=[%s],CELL2=[%s]\n",CELL1,CELL2);
   
      /* compare waveform definitions */
      mode = ' ';/* hopefully this gives us a double don't care???? */
      c1wf=c2wf=0;
   /* allowed formats: DWF, SWF, ContinueWF, CWF, OffWF, offWF */
/* known polaris format statements:
  EdgeSet(---,Edge,fmt,time):
     fmt:DriveHigh
         DriveLow
         DriveData
         DriveOff
         StrobeHigh
         StrobeLow
         StrobeData
         StrobeOff
         StrobeOffHigh
         StrobeOffLow
  EdgeSetDelayData(---,Edge,ChFirst,fmt,LVLS,time,cyclesout,fmt...
                            ^^^ which pin of mux pin 
1  WaveSetClk       (DSET1): L/H   (DSET0, when two different): l/h
3  WaveSetContinue  continue: -
4  WaveSetDoubleClk (DSET1): L/H   (DSET0, when two different): l/h
1  WaveSetNR        (DSET1): L/H   (DSET0, when two different): l/h
5  WaveSetOff       X/.
1  WaveSetRTO       (DSET1): L/H   (DSET0, when two different): l/h
1  WaveSetRTZ       (DSET1): L/H   (DSET0, when two different): l/h
1  WaveSetSBC       (DSET1): L/H   (DSET0, when two different): l/h
2  WaveSetStrobe    (DSET0): 0/1   (DSET1, when two different): o/i
6  WaveSetStrobeZ   F/f
*/
//      fprintf(stdout,"===LOOKING FOR [%s][%s]===\n",CELL1,CELL2);
      sprintf(CELL1P,"(%s)",CELL1); /* have to close because it could find something shorter */
      sprintf(CELL2P,"(%s)",CELL2); /* have to close because it could find something shorter */
      sprintf(CELL1C,"(%s,",CELL1); /* have to close because it could find something shorter */
      sprintf(CELL2C,"(%s,",CELL2); /* have to close because it could find something shorter */
      fmt_srch.dset0cnt=fmt_srch.dset1cnt=0;
      for(i=0;i<actablelines;i++){
         if (strstr(acwaves->w[i],CELL1P)!=NULL ||
             strstr(acwaves->w[i],CELL1C)!=NULL) {
            if (0!=strcmp(newwavetable,GCTNAME)) {
               if (START_WFMT==0) {
                  fprintf(fpwaves,"enVision:\"bl8:R10.3.2.WW0104:S3.0\"; /* 5.7 */\n");
                  START_WFMT=1;
                  }
               else fprintf(fpwaves,"}\n");
               fprintf(fpwaves,"WaveformTable %s {\n   Period \"%s\";\n",GCTNAME,tperiod);
               fprintf(fpwaves,"\tComment=\"This table has NOT been verified!!!! Origins could be mis-applied if the origin is set elsewhere, but this specific polaris waveform doesnt set origins!!! It is up to the end user to fix and verify this!!!\";\n");
               strcpy(newwavetable,GCTNAME);
               }
            process_waveforms(fpwaves,&actablelines,&i,PINNAME,used_line,(strcmp(CELL1,CELL2)!=0)?0:3,fmt_srch.dset0cnt,tperiod,&wfmcode0,&wfmcode1);
            fmt_srch.wfmln0[fmt_srch.dset0cnt]=i;
            strcpy(fmtline0,acwaves->w[i]);
//            fprintf(stdout,"0FMTLN[%s]%s\n",fmtline0,CELL1C);
            ptr=strchr(fmtline0,'('); /* we wouldn't be here if there wasn't a '(' */
            if (ptr==NULL) continue; /* well...., ok we might get here, so validate! */
            *ptr='\0';
            ptr2=strstr(wavetypefull,fmtline0);
            if (ptr2==NULL) {fprintf(stderr,"0Can't identify %d WaveSet format [%s],exiting\n",fmt_srch.dset0cnt,fmtline0);exit(1);}
            else fmt_srch.wftype0[fmt_srch.dset0cnt]=(ptr2-wavetypefull)/FMTLEN;
            *ptr='(';/* fix it back */
            if (strstr(fmtline0,"EdgeSet")!=NULL) { /* its an EdgeSet definition, need additonal search */
            /* if the waveform is already defined, these only modify times of previous WaveSets... */
               ptr1=strchr(fmtline0,',');/* find first comma */
               j=*(ptr1+5); /* Edge1 || Edge2 || Edge3 || Edge4 */
               ptr2=strchr(ptr1+1,','); /* find second comma, format follows */
               ptr3=strchr(ptr2+1,',');/* find third comma */
               if (ptr3==NULL) ptr3=strchr(ptr2+1,')');/* in case we only have two commas */
//               fprintf(stdout,"0ES:p1[%s]\n    p2[%s]\n    p3[%s]\n",ptr1,ptr2,ptr3);
               if (strstr(fmtline0,"EdgeSetDelayDataPinList")!=NULL) {
                  /* (wave,edge,ch,ET0,vth0,time0,dly0,ET1,vth1,time1,dly1,pinlist) */
                  ptr2=ptr3;
                  ptr3=strchr(ptr2+1,',');/* so we need the third and fourth commas */
                  if (ptr3==NULL) ptr3=strchr(ptr2+1,')');/* in case we are a comma short */
                  }
               else if (strstr(fmtline0,"EdgeSetDelayData")!=NULL) {
                  /* (wave,edge,ch,ET0,vth0,time0,dly0,ET1,vth1,time1,dly1) */
                  ptr2=ptr3;
                  ptr3=strchr(ptr2+1,',');/* so we need the third and fourth commas */
                  if (ptr3==NULL) ptr3=strchr(ptr2+1,')');/* in case we are a comma short */
                  }
               else if (strstr(fmtline0,"EdgeSetDelayPinList")!=NULL) {/* (wave,edge,ET,time,dly,pinlist) */
                  }
               else if (strstr(fmtline0,"EdgeSetDelay")!=NULL) {/* (wave,edge,ET,time,dly) */
                  }
               else if (strstr(fmtline0,"EdgeSetPinList")!=NULL) {/* (wave,edge,ET,time,pinlist) */
                  }
               else {/* (wave,edge,ET,time) */
                  }
               *ptr3='\0';
               ptr0=strstr(edgetypefull,ptr2+1);
               if (ptr0==NULL) {fprintf(stderr,"9Can't identify %d EdgeSet format p1[%s]p2[%s]p3[%s,exiting\n",fmt_srch.dset0cnt,ptr1,ptr2,ptr3);exit(1);}
               else {
//                  fprintf(stdout,"E#0\n");
                  *ptr3=',';
                  fmt_srch.wftype0[fmt_srch.dset0cnt]=(ptr0-edgetypefull)/FMTLEN;
                  fmt_srch.edgenum0[fmt_srch.dset0cnt]=j;
                  }
               }
            fmt_srch.dset0cnt++;
            if (fmt_srch.dset0cnt==MAX_MATCH_FMT) {
               fprintf(stderr,"Too many matching DSET0 formats in actable[%s],exiting\n",CELL1C);
               exit(1);
               }
            }
         if (strstr(acwaves->w[i],CELL2P)!=NULL ||
             strstr(acwaves->w[i],CELL2C)!=NULL) {
            if (0!=strcmp(newwavetable,GCTNAME)) {
               if (START_WFMT==0) {
                  fprintf(fpwaves,"enVision:\"bl8:R10.3.2.WW0104:S3.0\"; /* 5.7 */\n");
                  START_WFMT=1;
                  }
               else fprintf(fpwaves,"}\n");
               wftpending=0;/* this is sort of redundant because it gets reset three lines down! */
               fprintf(fpwaves,"WaveformTable %s {\n   Period \"%s\";\n",GCTNAME,tperiod);
               fprintf(fpwaves,"\tComment=\"This table has NOT been verified!!!! Origins could be mis-applied if the origin is set elsewhere, but this specific polaris waveform doesnt set origins!!! It is up to the end user to fix and verify this!!!\";\n");
               wftpending=1;
               strcpy(newwavetable,GCTNAME);
               }
            if (strcmp(CELL1,CELL2)!=0) { /* only process if cells are different */
               process_waveforms(fpwaves,&actablelines,&i,PINNAME,used_line,1,fmt_srch.dset1cnt,tperiod,&wfmcode0,&wfmcode1);
               }
            fmt_srch.wfmln1[fmt_srch.dset1cnt]=i;
            strcpy(fmtline1,acwaves->w[i]);
//            fprintf(stdout,"1FMTLN[%s]%s\n",fmtline1,CELL2C);
            ptr=strchr(fmtline1,'('); /* we wouldn't be here if there wasn't a '(' */
            *ptr='\0';
            ptr2=strstr(wavetypefull,fmtline1);
            if (ptr2==NULL) {fprintf(stderr,"[%s]1Can't identify %d WaveSet format [%s],exiting\n",wavetypefull,fmt_srch.dset1cnt,fmtline1);exit(1);}
            else fmt_srch.wftype1[fmt_srch.dset1cnt]=(ptr2-wavetypefull)/FMTLEN;
            *ptr='(';/* fix it back */
            fmt_srch.edgenum1[fmt_srch.dset1cnt]=0;
            if (fmtline1[0]=='E') { /* its an EdgeSet definition, need additonal search */
               ptr1=strchr(fmtline1,',');/* find first comma */
               j=*(ptr1+5); /* Edge1 || Edge2 || Edge3 || Edge4 */
               ptr2=strchr(ptr1+1,','); /* find second comma, format follows */
               ptr3=strchr(ptr2+1,','); /* find third comma */
//               fprintf(stdout,"1ES:p1[%s]\n    p2[%s]\n    p3[%s]\n",ptr1,ptr2,ptr3);
               if (ptr3==NULL) ptr3=strchr(ptr2+1,')'); /* in case there are two commas */
               if (*(ptr2+1)=='C') { /* EdgeSetDelayData has ,Channel, then format */
//                  fprintf(stdout,"1Its a Channel\n");
                  ptr2=ptr3;
                  ptr3=strchr(ptr2+1,',');/* so we need the third and fourth commas */
                  if (ptr3==NULL) ptr3=strchr(ptr2+1,')');/* in case we are short a comma */
                  }
               *ptr3='\0';
               ptr0=strstr(edgetypefull,ptr2+1);
               if (ptr0==NULL) {fprintf(stderr,"1Can't identify %d EdgeSet format p1[%s]p2[%s]p3[%s,exiting\n",fmt_srch.dset1cnt,ptr1,ptr2,ptr3);exit(1);}
               else {
//                  fprintf(stdout,"E#1\n");
                  *ptr3=',';
                  fmt_srch.wftype1[fmt_srch.dset1cnt]=(ptr0-edgetypefull)/FMTLEN;
                  fmt_srch.edgenum1[fmt_srch.dset1cnt]=j;
                  }
               }
            fmt_srch.dset1cnt++;
            if (fmt_srch.dset1cnt==MAX_MATCH_FMT) {
               fprintf(stderr,"Too many matching DSET1 formats in actable[%s],exiting\n",CELL2C);
               exit(1);
               }
            }
         }
      /* as code 0 does not exist we can subtract -1 from each 1->9 => 0-8 max 64+32=96 */
      mode=(wfmcode0-1)+10*(wfmcode1-1)+' ';
//      fprintf(stdout,"Pin[%s]C0[%d]C1[%d]CC%d[%c]\n",PINNAME,wfmcode0,wfmcode1,mode,mode);
      if (strcmp(PREVGCT,GCTNAME)==0) {
         if (device_pingroup>-1) {/* place result in all pins in the group */
            for(j=0;j<maxpin;j++) if (pinlist[device_pingroup].pinlists[j]=='*') vector[j]=mode;
            }
         else if (flag_group==0) vector[pin]=mode;
         else if (flag_group) for (j=0;j<=groupcount;j++) vector[pin+j]=mode;
          }
          
      else {
         if (PREVGCT[0]!='\0') fprintf(fpout1,"<%s>[%s]\n",PREVGCT,vector);
         strcpy(PREVGCT,GCTNAME);
         for (i=0;i<maxpin;i++) vector[i]='0';
         vector[maxpin]='\0';

         if (device_pingroup>-1) {/* place result in all pins in the group */
            for(j=0;j<maxpin;j++) if (pinlist[device_pingroup].pinlists[j]=='*') vector[j]=mode;
            }
         else if (flag_group==0) vector[pin]=mode;
         else for (j=0;j<=groupcount;j++) vector[pin+j]=mode;

         }
      }/* end cyclesetMD */
   }
if (PREVGCT[0]!='\0') fprintf(fpout1,"<%s>[%s]\n",PREVGCT,vector);
fprintf(fpout1,"H[%s]\n",hexproc);
fprintf(fpout1,"F[%s]\n",fieldset);
fprintf(fpout1,"M[%s]\n",muxpin);
for (i=0;i<maxlists;i++) {
   fprintf(fpout1,"PINGROUP[%s]",pinlist[i].pinlists);
   fprintf(fpout1,"(*%s*)",pinlist[i].pinlistname);
   fprintf(fpout1,"{%s}\n",pinlist[i].groups);
   }

for (sizehead=i=0;i<maxpin;i++) if (strlen(PIN[i])>sizehead) sizehead=strlen(PIN[i]);
if (sizehead<PINSIZE) {
   for (i=0;i<maxpin;i++) {
      for (j=0;j<strlen(PIN[i]);j++) pinheader[j][i]=PIN[i][j];
      for (;j<sizehead;j++) pinheader[j][i]=' ';
      }
   for (j=0;j<sizehead;j++) {
      pinheader[j][maxpin]='\0';
      }
   for (k=i=0;i<maxpin;i++) {
      if (muxpin[i]=='M') {
         for (l=maxpin+k;l>i+k;l--) for (j=0;j<sizehead;j++) pinheader[j][l]=pinheader[j][l-1];
         k++;
         }
      }
   for (j=0;j<sizehead;j++) fprintf(fpout1,"//%s\n",pinheader[j]);
   }
if (wftpending==1) fprintf(fpwaves,"}\n");/* close out the final waveformtable */
fprintf(fpwaves,"Spec EN_ORG {\n\tComment=\"You should really add this to the ACTABLE Spec\";\n\tCategory DEF_EN_ORG {\n");
for (i=0;i<EOCNT;i++)  fprintf(fpwaves,"\t\t%s = \"1\";\n",EO[i]);
fprintf(fpwaves,"\t}\n\tParamGlobals {\n");
for (i=0;i<EOCNT;i++)  fprintf(fpwaves,"\t\t%s { Type = SCALAR; }\n",EO[i]);
fprintf(fpwaves,"\t}\n}\n");
fprintf(fpwaves,"Mask MASK_EN_ORG {\n\tComment=\"You should really add this to the ACTABLE Mask\";\n");
for (i=0;i<EOCNT;i++)  fprintf(fpwaves,"\t%s = Typ;\n",EO[i]);
fprintf(fpwaves,"}\n");

for(i=0;i<cellcnt;i++) {
   fprintf(stdout,"#[%6d]WT[%20s]CN[%20s]P[%15s]fp[%6ld]MD#[%02d]FMT:[%4d][%4d][%4d][%4d]ACTL[%6d]\n",i,
      cellinfo[i].wftname,
      cellinfo[i].cellname,
      cellinfo[i].pin,
      cellinfo[i].filepos,
      cellinfo[i].multidefnum,
      cellinfo[i].formats[0],
      cellinfo[i].formats[1],
      cellinfo[i].formats[2],
      cellinfo[i].formats[3],
      cellinfo[i].actline);
   }
for(i=0;i<maxactablenames;i++) {
   fprintf(stdout,"ACT[%d][%s]\n",i,actablenames->name[i]);
   }

fclose(fpwaves);
fclose(fpout1);
fclose(fpin1);
fclose(fpin2);
free(acwaves);
return(0);
}  
