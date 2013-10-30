/* This program is covered by the GNU GPL license. Please see the file: COPYING.gz for the license info. */
/* original author: anthony_sully@ltx.com */

/* May 99 Anthony Sully, LTX Corp. Created original file for C6201, lots of hardcoded stuff!!! */
/* Feb 00 Anthony Sully, LTX Corp. Modified for C6202/3, still lots of hardcoded stuff!!! */
/* Sept. 02 Anthony Sully, LTX Corp. Modified for microcontroller translations (Venus first)
                                     started work removing hardcoded stuff. Added requirement
                                     for the gct_gen_mod.c output which now helps find the
                                     appropriate scan pins. At the moment only two are allowed.
                                     Waveformtables are currently ignored.*/
/* 09/28/02 Anthony Sully, LTX Corp. Changed cpm scan drive and strobe characters to use defines
                                     as opposed to hard coding them. Changed strobe character to
                                     match Dale's choice of 's' instead of 'C' (conflicting with
                                     clock wfms anyway).
                                     Begin adding wfm processing at the moment we will assume
                                     that the dset for scan hold cycles should be 1. */
/* 09/29/02 Anthony Sully, LTX Corp. Implemented code to properly look up the waveformtable
                                     information for both parallel vectors and scan cpm hold
                                     vectors. Modified Alias selections as well. For the scan
                                     hold I am assuming that the Dset=1 because that seemed
                                     to make the most sense, in most cases it doesn't matter
                                     because they are the same anyway in ScanCycleX. 
                                     Also, removed default waveformtable and default signal
                                     header as we are being explicit on every vector anyway.
                                     One minor issue remains in that the first cpm vector is
                                     all HOLD_CHAR. This may need to be driven to a set state,
                                     it also uses the pattern GCT as opposed to HOLD_CYCLE.
                                     Maybe keep the first dpm vector and stick it in CPM??? */

/* 10/27/02 Anthony Sully, LTX Corp. Fixed counts in repeats in CPM, it was off by one. */

/* 11/02/02 Anthony Sully, LTX Corp. Fixed compile script and includes so date can be brought in with
                                     gcc or cc */

/* 11/08/02 Anthony Sully, LTX Corp. Added pseudo-support for ScanSetUncoupled. The Polaris definition
                                     of scansetuncoupled defines that the scan vectors be sourced separately.
                                     What I have currently implemented will grab the information correctly
                                     but will source the vectors together. This is ok for the cases I have
                                     seen so far because what they are really doing is just sourcing one
                                     of the scanpins. By using the prefill/postfill the unused scanpin
                                     will be left blank and thus gets the prefill/postfill character. It
                                     totally ignores the other scanholdcycles. This implementation is not
                                     really correct but meets the current need. Fixing this would involve
                                     adding multiple hold vectors and re-doing the CPM pattern generation
                                     to keep track of which pin is being sourced when. This should be
                                     implemented if/when support for more than two scan pins is needed.
                                     Due to repeat loops in scan patterns pre_proc_dpm is now needed. */
                                     
/* 11/09/02 Anthony Sully, LTX Corp. Added support for repeat forever as last line of pattern if there are
                                     enough vectors to support it. Repeat forevers in anything but the last
                                     vector are not supported yet. Also, the pattern will get the wrong
                                     repeat count for parallel cpm-calling-dpm if there are not at least
                                     3 dpm vectors being called (1 for CPM calling DPM, 1 for COND CONT,
                                     and 1 for CJMP .) . It should still translate it just not compile
                                     and the fix is left to the user, no warnings are issued. 
                                     Added vector number, parallel number, and cyclenumber to dpm comments.
                                     Added vector number and cyclenumber to cpm comments. Added dummy
                                     vector to end of dpm for label position correctness. */                                 

/* 01/24/03 Anthony Sully, LTX Corp. Added FLAG(CONT ON) to microinstructions if repeat forever found */

/* 03/29/03 Anthony Sully, LTX Corp. Added GNU GPL info. Added ERROR CLASSES:
                                     FATAL_ERRORS -- cause immediate exit of program (usually file problems)
                                     BAD_ERRORS -- fatal errors that could produce corrupted output files
                                     NON_FATAL_ERRORS -- errors that generate files with useful output
                                     FYI -- informational warnings. Added username, hostname, and pwd to
                                     pattern header. Changed date get to 'C' functions instead of unix date.
                                     Turned off gzipping of *_cpm.evo pattern so the CPM_SCAN_OPT can be
                                     run directly. */

/* 04/04/03 Anthony Sully, LTX Corp. Added support for repeat forever loops as passed in from pre_proc_dpm.
                                     This only supports one repeat forever but does support a begin-end loop
                                     of multiple vectors. The repeat forever vectors are currently written
                                     into the dpm pattern as comments and to the cpm in the appropriate
                                     place. The cpm_scan_opt probably won't optimize this properly. */

/* 09/24/03 Anthony Sully, LTX Corp. Added support for user defined signal header (in cycletbl_mod.mod2),
                                     gct_gen_mod2. This is needed because some devices may have patterns
                                     with different widths. Added code to check that the cycletbl file has
                                     the same number of pins as the polaris pattern, exit if not the same.
                                     Same update to vector_convert_polaris. Added checks for any strstr or
                                     strchr statements to make sure they do something on NULL. */
/* 02/25/04 Anthony Sully, LTX Corp. Updated for scan auto gen (with -a). Modified how files are renamed
                                     and removed to use 'C' functions instead of system() */

/* 02/23/05 Anthony Sully, LTX Corp. Add support for repeat */

/* 11/20/05 Anthony Sully, LTX Corp. Fixed vector identification line so it uses the previously read GCTs_WFR
                                     instead of generically just GCT. This was an issue because of a DSP wftr
                                     which was PTM_2 and thus had no GCT in its name. Also fixed the extra
                                     carriage return after the signalheader. This was coming from the carriage
                                     return in the cycletbl_mod.mod2 file. Corrected the gzipping code so it
                                     would gzip autogen files as well. Added fpstatus file output instead of
                                     stdout. Created additional file for scan to list signalheaders and create
                                     them. updated to *_scanautogen3.c*/

/* 04/13/06 Anthony Sully, LTX Corp. Increased the allowable scan count 'MAXSCANCNT' from 7000 to 14000 */
/* 08/29/06 Anthony Sully, LTX Corp. Problem identifying SCANPINNUMBERS(SCANPININ/OUT) */
/* 06/29/08 Anthony Sully, LTX Corp. Added environment read of DEBUG_PROC */

#ifndef __GNUC__
#include "local_date.h"
#define __TIME__ ""
#endif

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define DEFAULT_SCAN_OPT "./CPM_SCAN_OPT "
/* C6203 defines */
#define FIND_SIGHDR_IN "ScanInOrder"
#define FIND_SIGHDR_OUT "ScanOutOrder"
#define MAXSCANORDERLEN 25
#define MAXSCANHDRLEN 30
#define FIND_CYCLE_HOLD "ScanCycle"
#define ASSUMED_DSET 1
#define MAXMODGCT 100

#define DRIVE_HIGH_ALIAS 'H'
#define DRIVE_LOW_ALIAS 'L'
#define DRIVE_HIGH_ALIAS2 'h'
#define DRIVE_LOW_ALIAS2 'l'
#define COMPARE_HIGH_ALIAS '1'
#define COMPARE_LOW_ALIAS '0'
#define COMPARE_HIGH_ALIAS2 'i'
#define COMPARE_LOW_ALIAS2 'o'
#define DONT_CARE_ALIAS 'X'
#define DONT_CARE_ALIAS2 '.'
#define SCAN_DRIVE_CPM 'D'
#define SCAN_STROBE_CPM 's'
#define HOLD_CHAR '-'
#define CPM_CALLING_DPM 'd'
char HOLD_VECTOR[1025];
char DPM_VECTOR[1025];   

#define HOLD_CYCLE "HOLD_CYCLE"

#define BEEP 0x07
#define FILENAMELEN 120
#define VECTORLEN 400
#define MULTILINESIZE 4096
#define READLINELEN 32767
#define MAXSCANLEN 32767
#define MAXERRORLEN 1025
#define MEMOSTRLEN 256
#define TEMPGZIPNAME "temp_gunzip_vc"
#define MAXRPT 2000
#define DFLTSGHDR "SH0"
#define MAXSIGHDRLEN 25
#define ENVISIONMAXSCANLEN 100
#define MAXWAVE 5000
#define MAXCYCLE 2000
#define MAXPINS 400
#define MAXSCANCNT 14000
#define MAXGCT 30
#define MAXGCTLEN 15
#define MAXALIAS 33
#define MAXPINLEN 10
#define MAXMSET 256
#define MAXDSET 256
#define MAXISET 15
#define MAXREPFOREVER 2
#define MAXREPFOREVERLINES 20
int QUIET=1;
FILE *fperrors,*fpstatus,*fpsignalheaders;
char infile1[FILENAMELEN];
long readlinenum=0;
long cyclecount=0,vectorcount=0;
char progstr[MEMOSTRLEN],datestr[MEMOSTRLEN],timestr[MEMOSTRLEN],compilestr[MEMOSTRLEN];/* concaternated strings */
char username[MEMOSTRLEN],hostname[MEMOSTRLEN],pwd[MEMOSTRLEN];
int SCANINPIN=0; /* TDI */
int SCANOUTPIN=0; /* TDO */
char NORMALSGHDR[MAXSIGHDRLEN];
int MOD2_SIZE;
/* function prototypes */
void outputvector(FILE *fpout1,int *lastitem,char *out_vector,char *pattern,char *WFT,char *DMI,long VN,int repeatcount,char *errorstr,char *comment);

/* begin main function */
int main (int argc,char *argv[]){

/* file variables */
FILE *fpin1,*fpin2,*fpout1,*fpout2;
time_t generictime;
int filein1=0;
int filein2=0;
char infile2[FILENAMELEN],infilebuf[FILENAMELEN];
char outfile1[FILENAMELEN],outfile2[FILENAMELEN];
char pattern[FILENAMELEN], mydate[101];

/* mode settings */
int debug=0,gzip=0,gunzip=0,autogen=0;
char env[READLINELEN+1],*endptr;

/* buffers */
char printstring[READLINELEN+MAXERRORLEN+1],vector[READLINELEN],mod_vector[READLINELEN],keep_vector[MULTILINESIZE];
char prev_vector1[READLINELEN],prev_comment[READLINELEN],prev_WFT[MAXGCTLEN+1],prev_errorstr[MAXERRORLEN+1];
char  out_vector1[READLINELEN],     comment[READLINELEN],     WFT[MAXGCTLEN+1],     errorstr[MAXERRORLEN+1];
char DMI[15],prev_DMI[15];/* only do repeat compression in VX125 mode */
char scaninpinname[READLINELEN],scanoutpinname[READLINELEN];
char SCANIN[MAXSCANLEN],SCANOUT[MAXSCANLEN],SCANHOLD[READLINELEN],SCANSETSTR[200],SCANGCT[MAXGCTLEN];
char SCANHDR[MAXSCANHDRLEN],PSCANHDR[MAXSCANHDRLEN],SCANINORDER[MAXSCANORDERLEN],SCANOUTORDER[MAXSCANORDERLEN],SCANINALIAS[MAXSCANORDERLEN],LASTGCT[MAXGCTLEN],SCANRGCT[MAXSCANCNT][MAXGCTLEN];
char SCANOUTSEL[MAXSCANORDERLEN],GCTMODNAME[READLINELEN][MAXGCTLEN];
char *MSETPTR,*DSETPTR,*ISETPTR;
int SCANFOR[MAXSCANCNT],SCANCNT=0,maxgctSET=0,maxrepforever=0,foundgoodgct=0;
long SCANAT[MAXSCANCNT],SCANATR[MAXSCANCNT];
long REPFOREVER[MAXREPFOREVER],REPFOREVEREND[MAXREPFOREVER];
char REPFOREVERVEC[MAXREPFOREVERLINES][READLINELEN];
int REPFOREVEROPEN=0,REPFOREVERLINES=0;
char VECTMOD[MAXMODGCT][MAXPINS+1];
/* concaternated strings */

/* control parameters */
int commentflag,beginflag,vectorflag,lastitem,commentON,commentcount,errorflag,scanhold,mlscan,end;
int repeatcount,notgood=0,pinnum,outpos,verrorflag,scanfor,scanlength,scanflag,scanflaghold;
long VN=0,prev_VN,repeatdec,VMSCAN,scanat,scanatr,LINE=0,li;

/* temporary variables */
int i,j,t1,t2,t3,t4,t5,t10,t11,vect,msel,dsel,isel,vmset,vdset,viset,AC,wftfind,rc,m;
char tempstr[READLINELEN+1],*ptr,*ptr1,*ptr2,*tptr;

int vl,vectorstart,vectorend,GCTMATCHMOD;

char muxpins[READLINELEN+1],muxcopy[READLINELEN+1];
int muxcount;

if (getenv("DEBUG_PROC")==NULL) debug=0;
else {strcpy(env,getenv("DEBUG_PROC"));debug=strtol(env,&endptr,0);fprintf(stderr,"Turning on DEBUG!\n");}

/* command line stuff */
strcpy(NORMALSGHDR,DFLTSGHDR);
if (argc>1) {
   if (strchr((char *)argv[1],'-')!=NULL){
      if (strchr((char *)argv[1],'s')!=NULL) QUIET = 1;
      if (strchr((char *)argv[1],'f')!=NULL && argc>=3) filein1 = 1;
      if (strchr((char *)argv[1],'g')!=NULL && argc>=4) filein2 = 1;
      if (strchr((char *)argv[1],'z')!=NULL ) gzip=1; 
      if (strchr((char *)argv[1],'a')!=NULL ) autogen=1; 
      }   
   }
strcpy(progstr,__FILE__);
strcpy(datestr,__DATE__);
strcpy(timestr,__TIME__);
if (getenv("PWD")!=NULL) strcpy(pwd,getenv("PWD"));
if (getenv("hostname")!=NULL) strcpy(hostname,getenv("hostname"));
else if (getenv("HOSTNAME")!=NULL) strcpy(hostname,getenv("HOSTNAME"));
/* the following works for CDE, don't know about others */
else if (NULL!=getenv("SESSION_SVR")) strcpy(hostname,getenv("SESSION_SVR"));
else strcpy(hostname,"UNKNOWN_HOSTNAME");

if (getenv("USER")!=NULL) strcpy(username,getenv("USER"));
strcpy(compilestr,argv[0]);
generictime=time(0);
strcpy(mydate,ctime(&generictime));
mydate[strlen(mydate)-1]='\0';
fprintf(stderr,"\n\n%s:%s, by Anthony Sully\n covered by GNU GPL license, see the file COPYING.gz in the source directory\n",compilestr,progstr);
if (!QUIET) {
   fprintf(stderr,"\n%s: %s\n",progstr,compilestr);
   fprintf(stderr,"%s by Anthony Sully\n",datestr);
   fprintf(stderr,"options are: -s => silent(script)\n");
   fprintf(stderr,"f => pattern file\n");
   fprintf(stderr,"g => gct info file\n");
   fprintf(stderr,"z => run gzip on .evo\n");
   fprintf(stderr,"a => use autogen cpm\n");
   fprintf(stderr,"\nUsage:%s -fz PAT.file \n",argv[0]);
   }

if (NULL==(fperrors=fopen("translation_errors.txt","a"))) {
   fprintf(stderr,"\nCould not open translation_errors.txt for output\n");
   exit(1);
   }

if (NULL==(fpstatus=fopen("translation_status.txt","a"))) {
   fprintf(stderr,"\nCould not open translation_status.txt for output\n");
   exit(1);
   }

if (NULL==(fpsignalheaders=fopen("scan_signalheaders.txt","a"))) {
   fprintf(stderr,"\nCould not open scan_signalheaders.txt for output\n");
   exit(1);
   }

/* open pattern input file */
if (filein1) strcpy(infile1,(char *) argv[2]);
else {
   fprintf(stderr,"Enter input PATTERN file: ");
   fgets(infile1,FILENAMELEN,stdin);
   infile1[strlen(infile1)-1]='\0';/* fgets gives the \n so clear it!! */
   }
strcpy(infilebuf,infile1);
t1=0;
while (NULL!=(ptr=strchr(infile1,'/'))){
   t1=(ptr-infile1);
   infile1[t1]=' ';t1++;
   }
j=0;
while(NULL==strchr(". ",infile1[t1]) && t1<strlen(infile1) ) pattern[j++]=infile1[t1++];
pattern[j]='\0';
strcpy(infile1,infilebuf);/* recopy the fullname and path */
t1=strlen(infile1);
fprintf(stderr,"\npattern_name:%s\n",pattern);
if ((infile1[t1-3]=='.' && infile1[t1-2]=='g' && infile1[t1-1]=='z')||(infile1[t1-2]=='.' && infile1[t1-1]=='Z') ){/* compressed input file */
   if (NULL!=(fpin1=fopen(infile1,"r"))) {
      fclose(fpin1);
      sprintf(tempstr,"gunzip -c %s >%s",infile1,TEMPGZIPNAME);
      fprintf(stderr,"%s\n",tempstr);
      system(tempstr);/* unzip to temporary file */
      if (NULL==(fpin1=fopen(TEMPGZIPNAME,"r"))) {
         fprintf(stderr,"\nFATAL_ERROR:Compressed input file [%s] not found\n",infile1);
         fprintf(fperrors,"\nFATAL_ERROR:%s:Compressed input file [%s] not found\n",progstr,infile1);
         exit(1);
         }
      gunzip=1;
      }
   else {
      fprintf(stderr,"\nFATAL_ERROR:Input file [%s] not found\n",infile1);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Input file [%s] not found\n",progstr,infile1);
      exit(1);
      }
   }
else {
   if (NULL==(fpin1=fopen(infile1,"r"))) {
      fprintf(stderr,"\nFATAL_ERROR:Input file [%s] not found\n",infile1);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Input file [%s] not found\n",progstr,infile1);
      exit(1);
      }
   }
if (!QUIET) fprintf(stdout,"input file1 ok\n");

infile2[0]='\0';
if (filein2) strcpy(infile2,(char *) argv[3]);
else {
   fprintf(stderr,"Enter input gct summary file: ");
   fgets(infile2,FILENAMELEN,stdin);
   infile2[strlen(infile2)-1]='\0';/* fgets gives the \n so clear it!! */
   }
if (NULL==(fpin2=fopen(infile2,"r"))) {
   fprintf(stderr,"\nFATAL_ERROR:Input file [%s] not found\n",infile2);
   fprintf(fperrors,"\nFATAL_ERROR:%s:Input file [%s] not found\n",progstr,infile2);
   exit(1);
   }

if (!QUIET) fprintf(stdout,"input file2 ok\n");

muxpins[0]='\0';
while(fgets(vector,READLINELEN-1,fpin2) != NULL ){
   vector[strlen(vector)-1]='\0';
   if (NULL!=strstr(vector,"#USE_SIGNAL_HEADER:")) {
      strcpy(NORMALSGHDR,vector+strlen("#USE_SIGNAL_HEADER:"));
      fprintf(fpstatus,"*** USER DEFINED SIGNAL HEADER:<%s> *** [file:%s]\n",NORMALSGHDR,infile1);
      }
   else if (vector[0]=='<') {
      vectorstart=(int)(strchr(vector,'<')-&vector[0])+1;
      vectorend=(int)(strchr(vector,'>')-&vector[0]);
      vector[vectorend]='\0';
      strcpy(GCTMODNAME[maxgctSET],&vector[vectorstart]);
      vector[vectorend]='>';
      vectorstart=(int)(strchr(vector,'[')-&vector[0])+1;
      vectorend=(int)(strchr(vector,']')-&vector[0])-1;
      MOD2_SIZE=vectorend-vectorstart+1;
      for (j=0,i=vectorstart;i<=vectorend;j++,i++) VECTMOD[maxgctSET][j]=vector[i];
      VECTMOD[maxgctSET][j]='\0';
      maxgctSET++;
      }
   else if (NULL!=strstr(vector,"?SCANINPIN")) {
/*  old code:    i=strlen(vector)-1;*/ /* -1 accounts for \n */
/*      while (vector[i]!=' ') i--; */
/*      i++; */
      i=strlen("?SCANINPIN:");
      for(;i<strlen(vector);i++) if (vector[i]==' ' || vector[i]=='\t') break;
      SCANINPIN=strtol(&vector[i],(char **)NULL,10);
/*    SCANINPIN=0;
      while (i<strlen(vector)-1) SCANINPIN=SCANINPIN*10+vector[i++]-'0';*/ /* -1 accounts for \n */
      ptr=strchr(vector,':')+1;
      if (*ptr==' ') ptr++;
      for (i=0;*ptr!=' ';i++,ptr++) scaninpinname[i]=*ptr;
      ptr++;*ptr='\0';
      }
   else if (NULL!=strstr(vector,"?SCANOUTPIN")) {
/*  old code:    i=strlen(vector);*/ /* -1 accounts for \n */
/*      while (vector[i]!=' ' && vector[i]!='\t') i--; */
/*      i++; */
      i=strlen("?SCANOUTPIN:");
      for(;i<strlen(vector);i++) if (vector[i]==' ' || vector[i]=='\t') break;
      SCANOUTPIN=strtol(&vector[i],(char **)NULL,10);
/*      SCANOUTPIN=0;
      while (i<strlen(vector)-1) SCANOUTPIN=SCANOUTPIN*10+vector[i++]-'0';*/ /* -1 accounts for \n */
      ptr=strchr(vector,':')+1;
      if (*ptr==' ') ptr++;
      for (i=0;*ptr!=' ';i++,ptr++) scanoutpinname[i]=*ptr;
      ptr++;*ptr='\0';
      }
   else if (vector[0]=='H') continue;/* nothing to do if hexproc */
   else if (vector[0]=='F') continue;/* nothing to do if fields */
   else if (vector[0]=='M') {strcpy(muxpins,vector+2);continue;}
   }

if (muxpins[0]!='\0') {
   for (j=0;j<maxgctSET;j++) {
      fprintf(stdout,"GCTIN [%s]\n",VECTMOD[j]);
      for (muxcount=i=0;i<strlen(muxpins)-1;i++) {
         muxcopy[i+muxcount]=VECTMOD[j][i];
         if (muxpins[i]=='M') {
            muxcount++;MOD2_SIZE++;
            muxcopy[i+muxcount]=VECTMOD[j][i];
            }
         }
      muxcopy[i+muxcount]='\0';
      strcpy(VECTMOD[j],muxcopy);
      fprintf(stdout,"GCTOUT[%s]\n",VECTMOD[j]);
      } /* end maxgctDSET */
   }


fprintf(fpstatus,"SCANINPIN:%d,SCANOUTPIN:%d [file:%s]\n",SCANINPIN,SCANOUTPIN,infile1);
if (SCANINPIN<=0 && SCANOUTPIN<=0) {
   fprintf(fperrors,"ERROR SCANPINS not properly identified in [%s] for [%s]\n",infile2,infile1);
   fprintf(stderr,"*** ERROR SCANPINS not properly identified in [%s] for [%s] ***\n",infile2,infile1);
   exit(1);
   }
else fprintf(stderr,"SCANPINS[%d][%d]\n",SCANINPIN,SCANOUTPIN);
for (i=0;i<=(vectorend-vectorstart);i++){
   HOLD_VECTOR[i]='-';
   DPM_VECTOR[i]='d';
   SCANHOLD[i]='-';
   }
HOLD_VECTOR[i]='\0';
DPM_VECTOR[i]='\0';
SCANHOLD[i]='\0';

if (1){/* pattern dpm output file */
   sprintf(outfile1,"%s_dpm.evo",pattern);
   if (NULL==(fpout1=fopen(outfile1,"w"))) {
      fprintf(stderr,"\nFATAL_ERROR:Could not open output file [%s] for output\n",outfile1);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open output file [%s] for output\n",progstr,outfile1);
      exit(1);
      }
   }
if (1){/* pattern cpm output file */
   sprintf(outfile2,"%s_cpm.evo",pattern);
   if (NULL==(fpout2=fopen(outfile2,"w"))) {
      fprintf(stderr,"\nFATAL_ERROR:Could not open output file [%s] for output\n",outfile2);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open output file [%s] for output\n",progstr,outfile2);
      exit(1);
      }
   }

if (!QUIET &&  filein1==0 ) {
   fprintf(stderr,"Inline syntax:\n%s -fz %s\n",argv[0],infile1);
   }
/* allocate buffers */
MSETPTR=(char *)malloc((unsigned)(VECTORLEN*MAXMSET));
DSETPTR=(char *)malloc((unsigned)(VECTORLEN*MAXDSET));
ISETPTR=(char *)malloc((unsigned)(VECTORLEN*MAXISET));
if (MSETPTR==NULL) fprintf(stderr,"FATAL_ERROR:Could not allocate msetptr\n");
if (MSETPTR==NULL) fprintf(fperrors,"FATAL_ERROR:%s:Could not allocate msetptr\n",progstr);
if (DSETPTR==NULL) fprintf(stderr,"FATAL_ERROR:Could not allocate dsetptr\n");
if (DSETPTR==NULL) fprintf(fperrors,"FATAL_ERROR:%s:Could not allocate dsetptr\n",progstr);
if (ISETPTR==NULL) fprintf(stderr,"FATAL_ERROR:Could not allocate isetptr\n");
if (ISETPTR==NULL) fprintf(fperrors,"FATAL_ERROR:%s:Could not allocate isetptr\n",progstr);

if (MSETPTR==NULL || DSETPTR==NULL || ISETPTR==NULL) exit(6);
if (!QUIET) fprintf(stdout,"Memory allocated ok\n");

   /***********************************************/
   /*                                             */
   /*    begin main loop for file processing      */
   /*                                             */
   /***********************************************/
fprintf(fpout1,"enVisionObject:\"bl8:R5.7\";\n\n");
fprintf(fpout1,"Pattern %s {\n",pattern);
fprintf(fpout1,"    Type Dpm;\n");
/* fprintf(fpout1,"    Default WaveformTable %s;\n","DEFWFT"); */
/* fprintf(fpout1,"    Default SignalHeader %s;\n",NORMALSGHDR); */

fprintf(fpout1,"\" Pattern convertor: %s:%s by Anthony Sully compile_date:%s@%s\"\n",compilestr,progstr,__DATE__,__TIME__);
fprintf(fpout1,"\"      Pattern converted on:%s by:%s on host:%s \"\n\"      in pwd:%s\"\n",mydate,username,hostname,pwd);
fprintf(fpout1,"\"Alias assignments: Drive (Dr=1) %c,%c\"\n",DRIVE_LOW_ALIAS,DRIVE_HIGH_ALIAS);
fprintf(fpout1,"\"                   Drive (Dr=0) %c,%c\"\n",DRIVE_LOW_ALIAS2,DRIVE_HIGH_ALIAS2);
fprintf(fpout1,"\"                   Strobe(Dr=0,M=1) %c,%c\"\n",COMPARE_LOW_ALIAS,COMPARE_HIGH_ALIAS);
fprintf(fpout1,"\"                   Strobe(Dr=1,M=1) %c,%c\"\n",COMPARE_LOW_ALIAS2,COMPARE_HIGH_ALIAS2);
fprintf(fpout1,"\"                   Mask  (Dr=0,M=0) %c,%c\"\n",DONT_CARE_ALIAS,DONT_CARE_ALIAS2);

fprintf(fpout1,"$%s_dpm_st\n",pattern);
errorstr[0]='\0';
printstring[0]='\0';
comment[0]='\0';
beginflag=0;
lastitem=0;
errorflag=0;
repeatcount=1;
commentON=0;
repeatdec=0;
VMSCAN=0;
scanflag=0;
scanat=scanatr=-1;
PSCANHDR[0]='\0';
scanflaghold=0;
while(fgets(vector,READLINELEN-1,fpin1) != NULL ){
   readlinenum++;
   LINE++;
   scanhold=0;
   if (strstr(vector,"begin")==0 && REPFOREVEROPEN==1) {
      REPFOREVEREND[maxrepforever-1]=-1;
      REPFOREVEROPEN=0;
      } /* no begin block */
   if (strstr(vector,"begin")!=0 && REPFOREVEROPEN==1) { /* begin block repeat forever */
      REPFOREVEROPEN=2;
      REPFOREVERLINES=0;
      continue;
      }
   if (strstr(vector,"end")!=0 && REPFOREVEROPEN==2) { /* end of repeat forever block */
      REPFOREVEROPEN=0;
      REPFOREVEREND[maxrepforever-1]=VN;
      }
   ptr =strstr(vector,"ScanIn");
   ptr1=strstr(vector,"ScanOut");
   mlscan=1;
   if ((NULL==ptr)&&(NULL==ptr1)) mlscan=0;
   ptr=strstr(vector,"ScanSetCoupled");
   if (ptr!=NULL) mlscan=0;/* ScanSetCoupled can contain ScanIn/ScanOut so clear if this is the case */
   ptr=strstr(vector,"ScanSetUncoupled");
   if (ptr!=NULL) mlscan=0;/* ScanSetCoupled can contain ScanIn/ScanOut so clear if this is the case */
   ptr2=strchr(vector,')');
   if (mlscan && ptr2!=NULL) mlscan = 0;
   if (mlscan==0) {
      strcpy(mod_vector,vector);
      mod_vector[strlen(mod_vector)-1]='\0';
      }
   else {
      /* getting possible multiline string */
      strcpy(mod_vector,vector);
      j=strlen(mod_vector)-1;end=0;/* add to end of current str */
      while (!end ) {
         t1=fgetc(fpin1);
         if (t1==EOF) end=1;
         else if (t1=='\n') ;
         else if (t1==';') { mlscan=0; end=1; }
         else if (t1==')') { mod_vector[j++]=t1; mlscan=0; end=1; } 
         else mod_vector[j++]=t1;
         }
      mod_vector[j]='\0';
      }
   if (debug) fprintf(stdout,"V[%s]\n",mod_vector);
   commentflag=0;
   vl=strlen(mod_vector);
   for (i=0;i<vl;i++) { /* simplify comments */
      if (mod_vector[i]=='(' && mod_vector[i+1]=='*') {mod_vector[i]='{'; mod_vector[i+1]=' ';}
      else if (mod_vector[i]=='*' && mod_vector[i+1]==')') {mod_vector[i]='}'; mod_vector[i+1]=' ';}
      }
   if (vl==0) continue;
   if (debug) fprintf(stdout,"V:%s\n",mod_vector);
   if (NULL!=(ptr=strstr(mod_vector,"Shutdown"))) {
      if ((ptr-mod_vector)<=7) {/* Shutdown SUBROUTINE */
         if(debug*0+1)fprintf(fpstatus,"INSIDE Shutdown:%s [file:%s]\n",mod_vector,infile1);
         fgets(vector,READLINELEN-1,fpin1);
         readlinenum++;
         if (NULL!=(ptr=strstr(vector,"begin"))) {
             if(debug*0+1)fprintf(fpstatus,"Throwing out Shutdown:%s [file:%s]\n",vector,infile1);
             while(fgets(vector,READLINELEN-1,fpin1) != NULL ){
                readlinenum++;
                if(debug*0+1)fprintf(fpstatus,"Throwing out Shutdown:%s [file %s]\n",vector,infile1);
                if (NULL!=(ptr=strstr(vector,"end"))) break;
                }
             }
         }
      }
   if (commentON && NULL==strchr(mod_vector,'}')) {strcat(comment,mod_vector);continue; }
   else if (commentON){
      strcat(keep_vector,mod_vector);
      strcpy(mod_vector,keep_vector);
      vl=strlen(mod_vector);
      ptr1=strchr(mod_vector,'}');
      if (ptr1==NULL) ptr1=mod_vector+strlen(mod_vector);
      /* seek until comment end*/
      for (i=(int)(ptr1-mod_vector);i<vl;i++) {
         if (mod_vector[i]=='{' ) commentcount++;
         if (mod_vector[i]=='}' ) commentcount--;
         if (commentcount==0) break;
         }
      if (commentcount==0) {
         commentflag=1;
         mod_vector[i]='\0';
         mod_vector[j]=' ';
         commentON=0;
         if (strlen(ptr1)+strlen(comment)>MULTILINESIZE) {
            fprintf(fpstatus,"BIG COMMENT <%s> [file:%s]\n",comment,infile1);
            comment[0]='\0';
            }
         strcat(comment,ptr1);
         for (j=j;j<=i;j++) mod_vector[j]=' ';
         if (NULL!=(ptr1=strchr(mod_vector,'{'))) continue;
         }
      else {
         commentON=1;
         mod_vector[j]=' ';
         strcat(comment,ptr1);
         continue;
         }
      }
   while (NULL!=(ptr1=strchr(mod_vector,'{')) && commentON==0 ){
      j=(int)(ptr1-mod_vector);
      /* seek until comment end*/
      for (i=(int)(ptr1-mod_vector);i<vl;i++) {
         if (mod_vector[i]=='{' ) commentcount++;
         if (mod_vector[i]=='}' ) commentcount--;
         if (commentcount==0) break;
         }
      if (commentcount==0) {
         commentflag=1;
         mod_vector[i]='\0';
         mod_vector[j]=' ';
         if (strlen(ptr1)+strlen(comment)>MULTILINESIZE) {
            fprintf(fpstatus,"BIG COMMENT <%s> [file:%s]\n",comment,infile1);
            comment[0]='\0';
            }
         strcat(comment,ptr1);
         for (j=j;j<=i;j++) mod_vector[j]=' ';
         if (NULL!=(ptr1=strchr(mod_vector,'{'))) continue;
         }
      else {
         commentON=1;
         mod_vector[j]=' ';
         if (strlen(ptr1)+strlen(comment)>MULTILINESIZE) {
            fprintf(fpstatus,"BIG COMMENT <%s> [file:%s]\n",comment,infile1);
            comment[0]='\0';
            }
         strcat(comment,ptr1);
         continue;
         }
      }
   if (commentON) { /* need more lines */
      strcpy(keep_vector,mod_vector);
      continue;
      }
   if (debug) fprintf(stdout,"comment=<%s>",comment);
   if (beginflag==0 && NULL!=(ptr=strstr(mod_vector,"begin"))) {
      beginflag=1;
      if (debug) fprintf(stdout,"found begin\n");
      continue;
      }
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"end"))) {
      if (debug) fprintf(stdout,"found end\n");
      if (scanflag==1) scanflag=2;/* if inside scanvector and end is found then we are complete*/
      else continue;
      }
   if (NULL!=(ptr=strstr(mod_vector,"ChainLength"))) {
      tptr=strchr(mod_vector,'(');
      if (tptr==NULL) continue;
      else t1=tptr-&mod_vector[0]+1;
      tptr=strchr(mod_vector,')');
      if (tptr==NULL) continue;
      t2=tptr-&mod_vector[0];
      scanlength=0;
      for (i=t1;i<t2;i++) if (isdigit((int)mod_vector[i])) scanlength=scanlength*10+mod_vector[i]-'0';
      fprintf(fpstatus,"Scan chain length=%d [file:%s]\n",scanlength,infile1);
      continue;
      }
   if (NULL!=(ptr=strstr(mod_vector,"ScanTest"))) {
      tptr=strstr(mod_vector,"For");
      if (tptr==NULL) continue;
      else t1=tptr-&mod_vector[0]+3;
      tptr=strstr(mod_vector,"At");
      if (tptr==NULL) continue;
      else t2=tptr-&mod_vector[0];
      tptr=strchr(mod_vector,')');
      if (tptr==NULL) continue;
      else t3=tptr-&mod_vector[0];
      scanfor=scanat=0;
      for (i=t1;i<t2;i++) if (isdigit((int)mod_vector[i])) scanfor=scanfor*10+mod_vector[i]-'0';
      for (i=t2+2;i<t3;i++) if (isdigit((int)mod_vector[i])) scanat=scanat*10+mod_vector[i]-'0';
      scanatr=(VN-1);
      t1=0;
      if (SCANCNT>1) {
         t1=SCANAT[SCANCNT-1]-SCANAT[SCANCNT-2];
         t2=SCANATR[SCANCNT-1]-SCANATR[SCANCNT-2];
         }
      if (debug) fprintf(stdout,"Scan for %d cycles at cycle:%ld (or %ld) cpmdelta=%d (or %d)\n",scanfor,scanat,scanatr,t1,t2);
      SCANFOR[SCANCNT]=scanfor;
      SCANAT[SCANCNT]=scanat;
      strcpy(SCANRGCT[SCANCNT],LASTGCT);
      sprintf(SCANHDR,"SCAN%s%s_%d",SCANINORDER,SCANOUTORDER,scanfor);
/* SignalHeader SCANVMVM_105 {
    Signals {
        TDI { Scan, ScanLength = 105, Fill = L, PostFill; }
        TDO { Scan, ScanLength = 105, Fill = X, PostFill; }
       
    }
}
*/ 


      if (0!=strcmp(SCANHDR,PSCANHDR)) {
         fprintf(fpsignalheaders,"SignalHeader %s { Signals { %s { Scan, ScanLength = %d, Fill = L, PostFill; } %s { Scan, ScanLength = %d, Fill = X, PostFill; }}}       //file:%s]\n",SCANHDR,scaninpinname,scanlength,scanoutpinname,scanlength,infile1);
         }
      strcpy(PSCANHDR,SCANHDR);
      continue;
      }
   if (NULL!=(ptr=strstr(mod_vector,"ScanSetCoupled"))) {
      strcpy(SCANSETSTR,mod_vector);
      if (debug) fprintf(stdout,"scansetname=[%s]\n",SCANSETSTR);
      ptr=strstr(mod_vector,FIND_SIGHDR_IN);
      if (ptr==NULL) continue;
      i=0;ptr+=strlen(FIND_SIGHDR_IN);
      while(isalnum((int)*ptr)&&i<MAXSCANORDERLEN) {
         SCANINORDER[i++]=*ptr++;
         }
      SCANINORDER[i]='\0';   
      fprintf(fpstatus,"scaninname=[%s] [file:%s]\n",SCANINORDER,infile1);

      ptr=strstr(mod_vector,FIND_SIGHDR_OUT);
      if (ptr==NULL) continue;
      strcpy(SCANOUTSEL,ptr);
      i=0;ptr+=strlen(FIND_SIGHDR_OUT);
      while(isalnum((int)*ptr)&&i<MAXSCANORDERLEN) {
         SCANOUTORDER[i++]=*ptr++;
         }
      SCANOUTSEL[strlen(FIND_SIGHDR_OUT)+i]='\0';
      SCANOUTORDER[i]='\0';
      fprintf(fpstatus,"scanoutname=[%s] [file:%s]\n",SCANOUTORDER,infile1);
      continue;
      }/* end scansetcoupled */
   if (NULL!=(ptr=strstr(mod_vector,"ScanSetUncoupled"))) {
      strcpy(SCANSETSTR,mod_vector);
      if (debug) fprintf(stdout,"scansetname=[%s]\n",SCANSETSTR);
      ptr=strstr(mod_vector,FIND_SIGHDR_IN);
      if (ptr==NULL) continue;
      i=0;ptr+=strlen(FIND_SIGHDR_IN);
      while(isalnum((int)*ptr)&&i<MAXSCANORDERLEN) {
         SCANINORDER[i++]=*ptr++;
         }
      SCANINORDER[i]='\0';   
      fprintf(fpstatus,"scaninnameUN=[%s] [file:%s]\n",SCANINORDER,infile1);

      ptr=strstr(mod_vector,FIND_SIGHDR_OUT);
      if (ptr==NULL) continue;
      strcpy(SCANOUTSEL,ptr);
      i=0;ptr+=strlen(FIND_SIGHDR_OUT);
      while(isalnum((int)*ptr)&&i<MAXSCANORDERLEN) {
         SCANOUTORDER[i++]=*ptr++;
         }
      SCANOUTSEL[strlen(FIND_SIGHDR_OUT)+i]='\0';
      SCANOUTORDER[i]='\0';
      fprintf(fpstatus,"scanoutnameUN=[%s] [file:%s]\n",SCANOUTORDER,infile1);
      continue;
      }/* end scansetcoupled */
   if (scanflaghold==0 && NULL!=(ptr=strstr(mod_vector,FIND_CYCLE_HOLD))) {
      if(debug) fprintf(stdout,"scanhold=[%s]\n",mod_vector);
      scanflaghold=1;
      sprintf(SCANGCT,"%s%c",FIND_CYCLE_HOLD,*(ptr+strlen(FIND_CYCLE_HOLD)));
      /* now find in stored list */
      for (wftfind=0;wftfind<maxgctSET;wftfind++){
         if(debug) fprintf(stdout,"%d,GCTMODNAME=%s,SCANGCT=%s\n",wftfind,GCTMODNAME[wftfind],SCANGCT);
         if (NULL!=strstr(GCTMODNAME[wftfind],SCANGCT) && strlen(GCTMODNAME[wftfind])==strlen(SCANGCT)) break;
         }
      if (i==maxgctSET) {/* WFT NOT FOUND, at the moment assume this doesn't happen */
         fprintf(stderr,"Error WFT not found[%s]\n",SCANGCT);
         fprintf(fperrors,"NON_FATAL_ERROR:%s:Error WFT not found[%s]in file[%s]line%ld\n",progstr,SCANGCT,infile1,readlinenum);
         }
      
      tptr=strchr(mod_vector,'[');
      if (tptr==NULL) continue;
      t1=tptr-&mod_vector[0]+1;
      tptr=strchr(mod_vector,']');
      if (tptr==NULL) continue;
      t2=tptr-&mod_vector[0];
      j=0;
      if(debug) fprintf(stdout,"%d,GCTMODNAME=%s,SCANGCT=%s,VM=[%s]\n",wftfind,GCTMODNAME[wftfind],SCANGCT,VECTMOD[wftfind]);
      for (m=0,i=t1;i<t2;i++,m++) {
         if(debug)fprintf(stdout,"%d,%c|",(mod_vector[i]-'0'),VECTMOD[wftfind][m]);
         switch((mod_vector[i]-'0')*100+VECTMOD[wftfind][m]){
            case 100+'1':/* reversed,strobe clock /drive strobe treat as reversed*/
            case 100+'A':/* drive is strobe & strobe is off */
            case 100+'C':/* both are strobes */
            case 100+'F':/* both are same and strobe */
            case 100+'a':rc=COMPARE_HIGH_ALIAS;break;/* drive is strobe strobe is cont */
            case 100+'0':/* normal,strobe/clock? treat as normal */
            case 100+'2':/* drive normal strobe cont, strobe is cont/drive is clock treat as normal drive*/
            case 100+'3':/* drive normal strobe off, drive clock, strobe off treat as d=d/s=o*/
            case 100+'D':/* both are drives,drive/clock assume as drives ,strobe clock /drive treat as double drive*/
            case 100+'E':rc=DRIVE_HIGH_ALIAS;break;/* both are same and drive,both are clock,treat as drives*/
            case 100+'4':/* strobe normal drive cont */
            case 100+'6':/* both are cont */
            case 100+'8':/* drive cont, strobe off */
            case 100+'b':rc=HOLD_CHAR;break;/* strobe is drive & drive is cont, strobe clock /drive continue treat as s=d/d=c*/
            case 100+'5':/* strobe normal drive off */
            case 100+'7':/* both are off */
            case 100+'9':/* drive off, strobe cont */
            case 100+'B':rc=DONT_CARE_ALIAS2;break;/* strobe is drive & drive is off,strobe clock/drive off treat as s=d/d=o*/
            case '1':/* reversed,strobe clock /drive strobe treat as reversed*/
            case 'A':/* drive is strobe & strobe is off */
            case 'C':/* both are strobes */
            case 'F':/* both are same and strobe */
            case 'a':rc=COMPARE_LOW_ALIAS;break;/* drive is strobe strobe is cont */
            case '0':/* normal,strobe/clock? treat as normal */
            case '2':/* drive normal strobe cont, strobe is cont/drive is clock treat as normal drive*/
            case '3':/* drive normal strobe off, drive clock, strobe off treat as d=d/s=o*/
            case 'D':/* both are drives,drive/clock assume as drives ,strobe clock /drive treat as double drive*/
            case 'E':rc=DRIVE_LOW_ALIAS;break;/* both are same and drive,both are clock,treat as drives*/
            case '4':/* strobe normal drive cont */
            case '6':/* both are cont */
            case '8':/* drive cont, strobe off */
            case 'b':rc=HOLD_CHAR;break;/* strobe is drive & drive is cont, strobe clock /drive continue treat as s=d/d=c*/
            case '5':/* strobe normal drive off */
            case '7':/* both are off */
            case '9':/* drive off, strobe cont */
            case 'B':rc=DONT_CARE_ALIAS;break;/* strobe is drive & drive is off,strobe clock/drive off treat as s=d/d=o*/
            default:rc='?';
            }
         SCANHOLD[j++]=rc;
         }
      if(debug)fprintf(stdout,"\nDONE With HOLD \n");
      SCANHOLD[j]='\0';         
      scanhold=1;
      while (t2<strlen(mod_vector)) {
         if (mod_vector[t2]==')') {t2=0;break;} /* close with parenthesis */
         t2++;
         }
      while (t2!=0) {
         if (NULL==fgets(mod_vector,READLINELEN-1,fpin1)) {t2=0;break;}
         readlinenum++;
         LINE++;
         t2=0;
         while (t2<strlen(mod_vector)) {/* read hold cycle until fully closed */
            if (mod_vector[t2]==')') {t2=0;break;} /* close with parenthesis */
            t2++;
            }
         }
      } /* end scanhold vector */
   if (NULL!=(ptr=strstr(mod_vector,"ScanIn"))) {
      scanflag+=1;
      if (NULL!=(ptr=strchr(mod_vector,'('))){
         t1=ptr-&mod_vector[0];
         mod_vector[t1]=' '; /* there are double parenthesis around the vector */
         tptr=strchr(mod_vector,'(');
         if (tptr==NULL) continue;
         t1=tptr-&mod_vector[0]+1;
         SCANINALIAS[0]=DRIVE_LOW_ALIAS;
         SCANINALIAS[1]=DRIVE_HIGH_ALIAS;
         if (mlscan==0) {
            tptr=strchr(mod_vector,')');
            if (tptr==NULL) continue;
            t2=tptr-&mod_vector[0];
            j=0;
            for (i=t1;i<t2;i++) SCANIN[j++]=SCANINALIAS[mod_vector[i]-'0'];
            SCANIN[j]='\0';
            }
         if (mlscan==1) {
            fprintf(stderr,"FATAL_ERROR:NOT CODED YET!...exiting\n");
            fprintf(fperrors,"FATAL_ERROR:%s:NOT CODED YET!...exiting.in file[%s]line%ld\n",progstr,infile1,readlinenum);
            exit(1);
            }
         if (debug) fprintf(stdout,"Scan IN vector=%s\n",SCANIN);
         }
      else SCANIN[0]='\0';/* No scanin */
      }/* end scan in vector */
   if (NULL!=(ptr=strstr(mod_vector,"ScanOut"))) {
      scanflag+=1;
      if (NULL!=(ptr=strchr(mod_vector,'('))){
         t1=ptr-&mod_vector[0];
         mod_vector[t1]=' '; /* there are double parenthesis around the vector */
         tptr=strchr(mod_vector,'(');
         if (tptr==NULL) continue;
         t1=tptr-&mod_vector[0]+1;
         SCANINALIAS[0]=COMPARE_LOW_ALIAS;
         SCANINALIAS[1]=COMPARE_HIGH_ALIAS;
         SCANINALIAS[2]=DONT_CARE_ALIAS;
         if (mlscan==0) {
            tptr=strchr(mod_vector,')');
            if (tptr==NULL) continue;
            t2=tptr-&mod_vector[0];
            j=0;
            for (i=t1;i<t2;i++) {
               if(mod_vector[i]=='X') t1=2;
               else t1=mod_vector[i]-'0';
               SCANOUT[j++]=SCANINALIAS[t1];
               }
            SCANOUT[j]='\0';
            }
         if (mlscan==1) {
            fprintf(stderr,"FATAL_ERROR:NOT CODED YET!...exiting\n");
            fprintf(fperrors,"FATAL_ERROR:%s:NOT CODED YET!...exiting.in file[%s]line%ld\n",progstr,infile1,readlinenum);
            exit(1);
            }
         if (debug) fprintf(stdout,"Scan OUT vector=%s\n",SCANOUT);
         }
      else SCANOUT[0]='\0'; /* no scanout */
      } /* end scan out vector */
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"repeat forever"))) {
      /* we need to check here for begin block and log it also */
      REPFOREVER[maxrepforever]=VN;
      REPFOREVEROPEN=1;
      maxrepforever++;
      if (maxrepforever==MAXREPFOREVER) {
         fprintf(stderr,"BAD_ERROR:found too many repeat forevers...ignoring\n");
         fprintf(fperrors,"BAD_ERROR:%s:found too many repeat forevers...ignoring.in file[%s]line%ld\n",progstr,infile1,readlinenum);
         notgood=2;
         }
      continue;
      }
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"repeat"))) {
      repeatdec=0;
      ptr+=7;
      while(isdigit((int)*ptr)){
         repeatdec=repeatdec*10+(*ptr-'0');
         ptr++;
         }
      fprintf(fpstatus,"found repeat [%ld] [file:%s]\n",repeatdec,infile1);
      }/* end repeat */
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"MSet"))) {
      t1=0;
      ptr=strchr(mod_vector,'[');
      if (ptr==NULL){
         fprintf(stderr,"BAD_ERROR:MSET ERROR [%s]",mod_vector);
         fprintf(fperrors,"BAD_ERROR:MSET ERROR:%s [%s].in file[%s]line%ld",progstr,mod_vector,infile1,readlinenum);
         notgood=1;
         break;
         }
      else {
         *ptr='%';
         ptr++;
         while (*ptr!=']'){
            if (isdigit((int)*ptr)) t1=10*t1+(*ptr-'0');
            ptr++;
            }
         if (t1>MAXMSET) {
            fprintf(stderr,"BAD_ERROR:Exceeded MAXMSET\n...continuing\n");
            fprintf(fperrors,"BAD_ERROR:%s:Exceeded MAXMSET\n...continuing.in file[%s]line%ld\n",progstr,infile1,readlinenum);
            notgood=1;
            break;
            }
         if (debug) fprintf(stdout,"In MSet [%d]\n",t1);
         ptr=strchr(mod_vector,'[');
         if (ptr==NULL){
            fprintf(stderr,"BAD_ERROR:MSET ERROR [%s]",mod_vector);
            fprintf(fperrors,"BAD_ERROR:MSET ERROR:%s [%s].in file[%s]line%ld",progstr,mod_vector,infile1,readlinenum);
            notgood=1;
            break;
            }
         ptr++;
         t2=0;
         while (*ptr!=']'){
            MSETPTR[t1*VECTORLEN+t2]=*ptr-'0';
            ptr++;
            t2++;
            }
         continue;         
         }
      }/* end MSET */
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"DSet"))) {
      t1=0;
      ptr=strchr(mod_vector,'[');
      if (ptr==NULL){
         fprintf(stderr,"BAD_ERROR:DSET ERROR [%s]",mod_vector);
         fprintf(fperrors,"BAD_ERROR:DSET ERROR:%s [%s].in file[%s]line%ld",progstr,mod_vector,infile1,readlinenum);
         notgood=1;
         break;
         }
      else {
         *ptr='%';
         ptr++;
         while (*ptr!=']'){
            if (isdigit((int)*ptr))t1=10*t1+(*ptr-'0');
            ptr++;
            }
         if (t1>MAXDSET) {
            fprintf(stderr,"BAD_ERROR:Exceeded MAXDSET\n...continuing\n");
            fprintf(fperrors,"BAD_ERROR:%s:Exceeded MAXDSET\n...continuing.in file[%s]line%ld\n",progstr,infile1,readlinenum);
            notgood=1;
            break;
            }
         if (debug) fprintf(stdout,"In DSet [%d]\n",t1);
         ptr=strchr(mod_vector,'[');
         if (ptr==NULL){
            fprintf(stderr,"BAD_ERROR:DSET ERROR [%s]",mod_vector);
            fprintf(fperrors,"BAD_ERROR:DSET ERROR:%s [%s].in file[%s]line%ld",progstr,mod_vector,infile1,readlinenum);
            notgood=1;
            break;
            }
         ptr++;
         t2=0;
         while (*ptr!=']'){
            DSETPTR[t1*VECTORLEN+t2]=*ptr-'0';
            ptr++;
            t2++;
            }
         continue;
         }
      }/* end DSET */
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"ISet"))) {
      t1=0;
      ptr=strchr(mod_vector,'[');
      if (ptr==NULL){
         fprintf(stderr,"BAD_ERROR:ISET ERROR [%s]",mod_vector);
         fprintf(fperrors,"BAD_ERROR:ISET ERROR:%s [%s].in file[%s]line%ld",progstr,mod_vector,infile1,readlinenum);
         notgood=1;
         break;
         }
      else {
         *ptr='%';
         ptr++;
         while (*ptr!=']'){
            if (isdigit((int)*ptr))t1=10*t1+(*ptr-'0');
            ptr++;
            }
         if (t1>MAXISET) {
            fprintf(stderr,"BAD_ERROR:Exceeded MAXISET\n...exiting\n");
            fprintf(fperrors,"BAD_ERROR:%s:Exceeded MAXISET\n...exiting.in file[%s]line%ld\n",progstr,infile1,readlinenum);
            notgood=1;
            break;
            }
         if (debug) fprintf(stdout,"In ISet [%d]\n",t1);
         ptr=strchr(mod_vector,'[');
         if (ptr==NULL){
            fprintf(stderr,"BAD_ERROR:ISET ERROR [%s]",mod_vector);
            fprintf(fperrors,"BAD_ERROR:ISET ERROR:%s [%s].in file[%s]line%ld",progstr,mod_vector,infile1,readlinenum);
            notgood=1;
            break;
            }
         ptr++;
         t2=0;
         while (*ptr!=']'){
            ISETPTR[t1*VECTORLEN+t2]=*ptr-'0';
            ptr++;
            t2++;
            }
         continue;
         }
      }/* end ISET */   
   if (scanhold==1){
      strcpy(mod_vector,SCANHOLD);
      t4=0;t5=strlen(SCANHOLD);
      if (debug) fprintf(stdout,"In SCANHOLD[%s]\nb=%d,e=%d,l=%d\n",SCANHOLD,t4,t5,t5-t4);
      outpos=0;
      pinnum=0;
      verrorflag=0;
      scanhold=0;
      if (0==strcmp(SCANOUTSEL,FIND_SIGHDR_OUT)) {
         SCANHOLD[SCANOUTPIN-1]=SCAN_STROBE_CPM;
         fprintf(fpstatus,"scanout=%d [file:%s]\n",SCANOUTPIN,infile1);
         }
      SCANHOLD[SCANINPIN-1]=SCAN_DRIVE_CPM;
      SCANHOLD[SCANOUTPIN-1]=SCAN_STROBE_CPM;
      if (debug) fprintf(stdout,"SCANHOLDVECTOR={%s}\n",SCANHOLD);
      } /* end grab scan hold vector */
   vectorflag=0;
   foundgoodgct=0;
   for (i=0;i<maxgctSET;i++) if (NULL!=(ptr=strstr(mod_vector,GCTMODNAME[i]))) {foundgoodgct=1;break;}
   if ((commentON==0 && beginflag>=1 && foundgoodgct==1) ) {
      /* real vector */
      vectorflag=1;
      j=0; beginflag=2;
      while (0==isspace((int)*ptr) && *ptr!='(') WFT[j++]=*(ptr++);
      WFT[j]='\0';
      strcpy(LASTGCT,WFT);
      GCTMATCHMOD=0;
      for (wftfind=0;wftfind<maxgctSET;wftfind++){
         if(debug) fprintf(stdout,"%d,GCTMODNAME=%s,WFT=%s\n",wftfind,GCTMODNAME[wftfind],WFT);
         if (NULL!=strstr(GCTMODNAME[wftfind],WFT) && strlen(GCTMODNAME[wftfind])==strlen(WFT)) {GCTMATCHMOD=1;break;}
         }
      if (i==maxgctSET) {/* WFT NOT FOUND, at the moment assume this doesn't happen */
         fprintf(stderr,"BAD_ERROR:Error WFT not found[%s]\n",WFT);
         fprintf(fperrors,"BAD_ERROR:%s:Error WFT not found[%s].in file[%s]line%ld\n",progstr,WFT,infile1,readlinenum);
         }
      VN++;
      cyclecount++;
      vectorcount++;
      ptr=strchr(mod_vector,'(');
      if (ptr==NULL) continue;
      ptr++;
      msel=0; dsel=0; isel=0;
      /* MSET */
      while (*ptr!=','){
         if (isdigit((int)*ptr))msel=10*msel+(*ptr-'0');
         ptr++;
         }
      /* DSET */
      ptr++;
      while (*ptr!=','){
         if (isdigit((int)*ptr))dsel=10*dsel+(*ptr-'0');
         ptr++;
         }
      /* ISET */
      ptr++;
      while (*ptr!=')'){
         if (isdigit((int)*ptr))isel=10*isel+(*ptr-'0');
         ptr++;
         }
      ptr=strchr(mod_vector,'[');
      if (ptr==NULL) continue;
      t4=(ptr-mod_vector)+1;
      ptr=strchr(mod_vector,']');
      if (ptr==NULL) continue;
      t5=(ptr-mod_vector);
      if (debug) fprintf(stdout,"In vector,WFT=[%s],M=%d,D=%d,I=%d,b=%d,e=%d,l=%d\n",WFT,t1,t2,t3,t4,t5,t5-t4);
      outpos=0;
      pinnum=0;
      verrorflag=0;
      sprintf(DMI,"(%d,%d,%d)",msel,dsel,isel);
      if ((t5-t4)!=MOD2_SIZE) {
         fprintf(stderr,"FATAL_ERROR: Number of pins<%d> in pattern <%s> does not match pins in cycletbl definition file<%d>\n",t5-t4,infile1,MOD2_SIZE);
         fprintf(fperrors,"FATAL_ERROR:%s: Number of pins<%d> in pattern <%s> does not match pins in cycletbl definition file<%d>\n",progstr,t5-t4,infile1,MOD2_SIZE);
         exit(9);
         }
      for (m=0,i=t4;i<t5;i++,m++){
         vect=mod_vector[i]-'0';
         vmset=MSETPTR[msel*VECTORLEN+m];
         vdset=DSETPTR[dsel*VECTORLEN+m];
         viset=ISETPTR[isel*VECTORLEN+m];
         if (viset==1) vect=1-vect;
         t11=vdset*4+vmset*2+vect;
         t10='0'; 
         if (GCTMATCHMOD) t10=VECTMOD[wftfind][m];
         switch (t10){/* D=0 is strobe D=1 is drive */
            case '0':break;/* normal meanings for mdi */
            case '1':t11=(1-vdset)*4+vmset*2+vect;break;/* reversed */
            case '2':t11=(vdset==0)?'-':t11;break;/* drive normal strobe cont */
            case '3':t11=(vdset==0)?vect:t11;break;/* drive normal strobe off */
            case '4':t11=(vdset==0)?t11:'-';break;/* strobe normal drive cont */
            case '5':t11=(vdset==0)?t11:vect;break;/* strobe normal drive off */
            case '6':t11='-';break;/* both are cont */
            case '7':t11=vect;break;/* both are off */
            case '8':t11=(vdset==0)?vect:'-';break;/* drive cont, strobe off */
            case '9':t11=(vdset==0)?'-':vect;break;/* drive off, strobe cont */
            case 'a':t11=(vdset==0)?'-':vmset*2+vect;break;/* drive is strobe strobe is cont */
            case 'A':t11=(vdset==0)?vect:vmset*2+vect;break;/* drive is strobe & strobe is off */
            case 'b':t11=(vdset==0)?4+vmset*2+vect:'-';break;/* strobe is drive & drive is cont */
            case 'B':t11=(vdset==0)?4+vmset*2+vect:vect;break;/* strobe is drive & drive is off */
            case 'C':t11=(vdset==0)?vmset*2+vect:'0'+vmset*2+vect;break;/* both are strobes */
            case 'D':t11=(vdset==0)?'A'+vect:t11;break;/* both are drives */
            case 'E':t11=4+vmset*2+vect;break;/* both are same and drive */
            case 'F':t11=vmset*2+vect;break;/* both are same and strobe */
            }
         switch(t11){  /* D=1=DRIVE, M=1=COMPARE */
            case 0:AC=DONT_CARE_ALIAS;break;/* D=0,M=0,V=0 */
            case 1:AC=DONT_CARE_ALIAS2;break;/* D=0,M=0,V=1 */
            case 2:AC=COMPARE_LOW_ALIAS;break;/* D=0,M=1,V=0 */
            case 3:AC=COMPARE_HIGH_ALIAS;break;/* D=0,M=1,V=1 */
            case 4:AC=DRIVE_LOW_ALIAS;break;/* D=1,M=0,V=0 */
            case 5:AC=DRIVE_HIGH_ALIAS;break;/* D=1,M=0,V=1 */
            case 6:AC=DRIVE_LOW_ALIAS;break;/* D=1,M=1,V=0 */
            case 7:AC=DRIVE_HIGH_ALIAS;break;/* D=1,M=1,V=1 */
            case '-':AC=HOLD_CHAR;break;/* D=1,M=1,V=1 */
            case '0':AC=DONT_CARE_ALIAS;break;/* D=1,M=1,V=0 */
            case '1':AC=DONT_CARE_ALIAS2;break;/* D=1,M=1,V=1 */
            case '2':AC=COMPARE_LOW_ALIAS2;break;/* D=1,M=1,V=0  */
            case '3':AC=COMPARE_HIGH_ALIAS2;break;/* D=1,M=1,V=1 */
            case 'A':AC=DRIVE_LOW_ALIAS2;break;/* D=0,M=1,V=0 */
            case 'B':AC=DRIVE_HIGH_ALIAS2;break;/* D=0,M=1,V=1 */
            default:verrorflag=1;
            }
           out_vector1[m]=AC;
           outpos++;
         }
      if (verrorflag==1) {
         fprintf(stderr,"BAD_ERROR:Error in vector [%s]\n",vector);
         fprintf(fperrors,"BAD_ERROR:%s:Error in vector [%s].in file[%s]line%ld\n",progstr,vector,infile1,readlinenum);
         }
      out_vector1[outpos] = '\0';
      if (REPFOREVEROPEN==2) {
         strcpy(REPFOREVERVEC[REPFOREVERLINES],out_vector1);
         fprintf(fpout1,"\"\n\"*%s* this is a repeat forever vector",out_vector1);
         out_vector1[0]='\0';
         vectorflag=0;
         REPFOREVERLINES++;
         }
      }
#define VECTOR 1
#define STRING 2
#define LABEL 3

   if(debug) fprintf(stdout,"at%ld atr%ld vn%ld vectortrue%d\n",scanat,scanatr,VN-1,vectorflag);
   if (beginflag==2 && vectorflag){
      t1=1;
      if (debug) fprintf(stdout,"FFFFF %s\n",out_vector1);
      repeatcount=repeatdec;
      outputvector(fpout1,&lastitem,out_vector1,pattern,WFT,DMI,VN,repeatcount,errorstr,comment);
      repeatcount=1;
      repeatdec=0;
      }
   if (scanflag==2) { /* SPIT OUT SCAN VECTOR both scanin and scanout if available  */
      SCANATR[SCANCNT++]=VN-1;
      if (debug) fprintf(stdout,"Outputing scan vector\n");
      if (SCANCNT>MAXSCANCNT) {
         fprintf(stderr,"FATAL_ERROR:Maximum number of SCAN vectors exceeded...exiting\n");
         fprintf(fperrors,"FATAL_ERROR:%s:Maximum number of SCAN vectors exceeded...exiting.in file[%s]line%ld\n",progstr,infile1,readlinenum);
         exit(9);
         }
      scanflag=0;
      if (lastitem==STRING) fprintf(fpout1,"\"\n");
      t1=(scanlength+ENVISIONMAXSCANLEN-1)/ENVISIONMAXSCANLEN-1;
      VMSCAN += 1;
      cyclecount+=scanlength;
      vectorcount++;
      fprintf(fpout1,"*");
      i=0;
      if (SCANIN[0]!='\0'){
         for (i=0;i<t1;i++) {
            t2=SCANIN[ENVISIONMAXSCANLEN+i*ENVISIONMAXSCANLEN];
            SCANIN[ENVISIONMAXSCANLEN+i*ENVISIONMAXSCANLEN]='\0';
            fprintf(fpout1,"%s\n",&SCANIN[i*ENVISIONMAXSCANLEN]);
            SCANIN[ENVISIONMAXSCANLEN+i*ENVISIONMAXSCANLEN]=t2;
            }
         }
      fprintf(fpout1,"%s;\n",&SCANIN[i*ENVISIONMAXSCANLEN]);
      i=0;
      if (SCANOUT[0]!='\0'){
         for (i=0;i<t1;i++) {
            t2=SCANOUT[ENVISIONMAXSCANLEN+i*ENVISIONMAXSCANLEN];
            SCANOUT[ENVISIONMAXSCANLEN+i*ENVISIONMAXSCANLEN]='\0';
            fprintf(fpout1,"%s\n",&SCANOUT[i*ENVISIONMAXSCANLEN]);
            SCANOUT[ENVISIONMAXSCANLEN+i*ENVISIONMAXSCANLEN]=t2;
            }
         }
      fprintf(fpout1,"%s;* %s %s;\"SCAN VECTOR %d:LCC=%ld\"",&SCANOUT[i*ENVISIONMAXSCANLEN],SCANGCT,SCANHDR,SCANCNT,cyclecount);
      lastitem=VECTOR;
      }
   if (beginflag==1) {
      /* discard these comments */
      /* fprintf(fpout1,"\"%s\"\n",comment); */      
      comment[0]='\0';
      DMI[0]='\0';
      }      
   if (beginflag==0) {
      fprintf(fpout1,"\"%s\"\n",comment);
      comment[0]='\0';
      DMI[0]='\0';
      }      
   } /* end of while vector */
   
   /********************/
   /* End of main loop */ 
   /********************/

if (lastitem==STRING) fputc('\"',fpout1);
lastitem=LABEL;
fprintf(fpout1,"\n$end\n");
if (prev_vector1[0]!='\0') {
   /* fprintf(stdout,"HHHHH\n"); */
   outputvector(fpout1,&lastitem,prev_vector1,pattern,prev_WFT,prev_DMI,prev_VN,repeatcount,prev_errorstr,prev_comment);
   if (lastitem==STRING) fputc('\"',fpout1);
   }
else {
   if (lastitem==STRING) fputc('\"',fpout1);
   fprintf(fpout1,"*%s* %s %s; \"DUMMY VECTOR, not executed\"\n",HOLD_VECTOR,SCANRGCT[0],NORMALSGHDR);
   }
/* { bm */ fprintf(fpout1,"\n}\n"); 

fclose(fpin1);
fclose(fpout1);
if (autogen) {
   fprintf(stderr,"Adding default background to %s_dpm.evo\n",pattern);
   if (NULL==(fpin1=fopen(outfile1,"r"))) {
      fprintf(stderr,"\nFATAL_ERROR:Could not open file [%s] for reading\n",outfile1);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open file [%s] for reading\n",progstr,outfile1);
      exit(1);
      }
   sprintf(tempstr,"%s_scanautogen.evo",pattern);
   if (NULL==(fpout1=fopen(tempstr,"w"))) {
      fprintf(stderr,"\nFATAL_ERROR:Could not open file [%s] for writing\n",tempstr);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open file [%s] for writing\n",progstr,tempstr);
      exit(1);
      }
while (fgets(vector,READLINELEN-1,fpin1) !=NULL){
   if (NULL!=strstr(vector,"Type Dpm;")) {
      fprintf(fpout1,"   Type Dpm;\n");
      fprintf(fpout1,"   Default WaveformTable %s;\n",SCANGCT);
      fprintf(fpout1,"   Default SignalHeader %s;\n",NORMALSGHDR);
      fprintf(fpout1,"   Default Background *%s*;\n",SCANHOLD);
      }
   else fprintf(fpout1,"%s",vector);
   }
fclose(fpout1);
fclose(fpin1);
remove(outfile1);
}

if (notgood==1) {
   sprintf(tempstr,"%s_dpm.evo",pattern);
   remove(tempstr); /* remove dpm file */
   sprintf(tempstr,"%s_cpm.evo",pattern);
   remove(tempstr); /* remove cpm file */
   if (gunzip) remove(TEMPGZIPNAME);/* remove temporary input file */
   fprintf(stderr,"*** File %s was not successful!!! ***\n",infile1);
   fprintf(stderr,"parallel vectors successfully processed:%ld\n",VN);
   fprintf(stderr,"scan     vectors successfully processed:%ld \n",VMSCAN);
   fprintf(fperrors,"BAD_ERROR:%s:*** File %s was not successful!!! ***\n",progstr,infile1);
   }
else if (notgood==2) {
   if (gunzip) remove(TEMPGZIPNAME);/* remove temporary input file */
   if (NULL!=strstr(infile1,".proc")) {
      /* fprintf(fperrors,"FYI:removing %s file\n",infile1); */
      fprintf(stderr,"removing %s file\n",infile1);
      if (debug==0) remove(infile1);/* remove temporary .proc file */
      }
   fprintf(stderr,"--- File %s has untranslated microcode!!! ---\n",infile1);
   fprintf(stderr,"parallel vectors successfully processed:%ld\n",VN);
   fprintf(stderr,"scan     vectors successfully processed:%ld \n",VMSCAN);
   fprintf(fperrors,"FYI:%s:--- File %s has untranslated microcode!!! ---\n",progstr,infile1);
   if (autogen) sprintf(tempstr,"gzip -f %s_scanautogen.evo &",pattern);
   else sprintf(tempstr,"gzip -f %s_dpm.evo &",pattern);
   if (gzip) system(tempstr); /* gzip dpm file */
   }
else {
   fprintf(stderr,"parallel vectors successfully processed: %ld\n",VN);
   fprintf(stderr,"scan     vectors successfully processed: %ld %d\n",VMSCAN,SCANCNT);
   if (autogen) sprintf(tempstr,"gzip -f %s_scanautogen.evo &",pattern);
   else sprintf(tempstr,"gzip -f %s_dpm.evo &",pattern);
   if (gzip) system(tempstr); /* gzip dpm file */
   if (gunzip) remove(TEMPGZIPNAME);/* remove temporary input file */
   if (NULL!=strstr(infile1,".proc")) {
      /* printf(fperrors,"FYI:removing %s file\n",infile1); */
      fprintf(stderr,"removing %s file\n",infile1);
      remove(infile1); /* remove temporary .proc file */
      }
   }

/* generate CPM file */
t1=SCANATR[1]-SCANATR[0];
t3=SCANAT[1]-SCANAT[0];
fprintf(stdout,"Parallel vectors between SCAN vectors:%d\n",t1); /* ,%d\n,  t3 */
for (i=2;i<SCANCNT;i++) {
   t2=SCANATR[i]-SCANATR[i-1];
   t4=SCANAT[i]-SCANAT[i-1];
   if ( t2!=t1 ) {/* || t3!=t4 */
      fprintf(fpstatus,"Parallel vector count between SCAN vectors %d is different(%d to %d) at (%ld) [file:%s]\n",i,t2,t1,SCANATR[i],infile1);
      t1=t2;t3=t4;
      }
   }
fprintf(fpout2,"enVisionObject:\"bl8:R5.7\";\n\n");
fprintf(fpout2,"Pattern %s_cpm {\n",pattern);
fprintf(fpout2,"    Type Cpm;\n");
/* fprintf(fpout2,"    Default WaveformTable %s;\n","DEFWFT"); */
/* fprintf(fpout2,"    Default SignalHeader %s;\n",NORMALSGHDR); */

fprintf(fpout2,"\" Pattern convertor: %s:%s by Anthony Sully compile_date:%s@%s\"\n",compilestr,progstr,__DATE__,__TIME__);
fprintf(fpout2,"\"      Pattern converted on:%s by:%s on host:%s \"\n\"      in pwd: %s\"\n",mydate,username,hostname,pwd);
fprintf(fpout2,"\"Alias assignments: Drive (Dr=1) %c,%c\"\n",DRIVE_LOW_ALIAS,DRIVE_HIGH_ALIAS);
fprintf(fpout2,"\"                   Drive (Dr=0) %c,%c\"\n",DRIVE_LOW_ALIAS2,DRIVE_HIGH_ALIAS2);
fprintf(fpout2,"\"                   Strobe(Dr=0,M=1) %c,%c\"\n",COMPARE_LOW_ALIAS,COMPARE_HIGH_ALIAS);
fprintf(fpout2,"\"                   Strobe(Dr=1,M=1) %c,%c\"\n",COMPARE_LOW_ALIAS2,COMPARE_HIGH_ALIAS2);
fprintf(fpout2,"\"                   Mask  (Dr=0,M=0) %c,%c\"\n",DONT_CARE_ALIAS,DONT_CARE_ALIAS2);
fprintf(fpout2,"\"                   CPM call DPM     %c  \"\n",CPM_CALLING_DPM);
fprintf(fpout2,"\"                   SCAN DRIVE     %c  \"\n",SCAN_DRIVE_CPM);
fprintf(fpout2,"\"                   SCAN STROBE     %c  \"\n",SCAN_STROBE_CPM);
fprintf(fpout2,"$%s_cpm_st\n",pattern);
if (notgood==1) fprintf(fpout2,"\"*** File %s was not successful!!! ***\"\n",infile1);
if (notgood==2) fprintf(fpout2,"\"--- File %s has untranslated microcode!!! ---\"\n",infile1);
if (notgood==1) fprintf(stderr,"*** File %s was not successful!!! ***\n",infile1);
if (notgood==2) fprintf(stderr,"--- File %s has untranslated microcode!!! ---\n",infile1);
if (notgood==1) fprintf(fperrors,"BAD_ERROR:%s:*** File %s was not successful!!! ***\n",progstr,infile1);
if (notgood==2) fprintf(fperrors,"BAD_ERROR:%s:--- File %s has untranslated microcode!!! ---\n",progstr,infile1);

fprintf(fpout2,"*%s* %s %s; <SWCCPM,LDA %s_dpm_st>\n",HOLD_VECTOR,SCANRGCT[0],NORMALSGHDR,pattern);
fprintf(fpout2,"*%s* %s %s; <RPT 64>\n",HOLD_VECTOR,HOLD_CYCLE,NORMALSGHDR);
cyclecount=1+65;/* +65 is because of the above two lines */
vectorcount=0+2;/* +2 is because of the above two lines */
for(li=0;li<SCANCNT;li++){ 
   if (debug) fprintf(stdout,"%5ld %s %ld %d %ld\n",li,SCANRGCT[li],SCANATR[li],SCANFOR[li],SCANATR[li]-((li==0)?0:SCANATR[li-1]+1)+1);
   }
if (maxrepforever==0) {
   for (li=0;li<SCANCNT;li++) {
      fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,RPT %ld>\"%ld:%ld\"\n",DPM_VECTOR,SCANRGCT[li],NORMALSGHDR,SCANATR[li]-((li==0)?0:SCANATR[li-1]+1)+1,vectorcount,cyclecount);
      cyclecount+=SCANATR[li]-((li==0)?0:SCANATR[li-1]+1)+1;
      vectorcount++;
      fprintf(fpout2,"*%s* %s %s; <SWCCPM,SDP,RPT %d>\"%ld:%ld\"\n",SCANHOLD,SCANGCT,NORMALSGHDR,SCANFOR[li],vectorcount,cyclecount);
      cyclecount+=SCANFOR[li];
      vectorcount++;
      }
   if ((VN-1)>SCANATR[SCANCNT-1]) {
       fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,RPT %ld>\"%ld:%ld\"\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR,(VN-1)-SCANATR[SCANCNT-1],vectorcount,cyclecount);
       }
   }
else {
   for (li=0;li<SCANCNT;li++) {
      fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",DPM_VECTOR,SCANRGCT[li],NORMALSGHDR,SCANATR[li]-((li==0)?0:SCANATR[li-1]+1)+1);
      fprintf(fpout2,"*%s* %s %s; <SWCCPM,SDP,RPT %d>\n",SCANHOLD,SCANGCT,NORMALSGHDR,SCANFOR[li]);
      }
   fprintf(stdout,"REPEAT FOREVER at %ld\n",REPFOREVER[0]);
   if ((VN-1)>SCANATR[SCANCNT-1] && (VN-1)==REPFOREVER[0] && REPFOREVEREND[0]==-1) {
       if( (VN-1)-SCANATR[SCANCNT-1]-3>4){
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR,(VN-1)-SCANATR[SCANCNT-1]-3);
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,COND CONT>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,FLAG(CONT ON)>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,CJMP .>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          }
       else {
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR,(VN-1)-SCANATR[SCANCNT-1]-1);
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,COND CONT>\n",HOLD_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,FLAG(CONT ON)>\n",HOLD_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,CJMP .>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          }
       }
   else if ((VN-1)>SCANATR[SCANCNT-1] && (VN-1)>REPFOREVER[0]) {
       REPFOREVER[0]=9999999;
       if( (VN-1)-SCANATR[SCANCNT-1]-3>4){
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR,(VN-1)-SCANATR[SCANCNT-1]-3-(REPFOREVERLINES-1));
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,COND CONT>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,FLAG(CONT ON)>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          for (i=0;i<REPFOREVERLINES-1;i++) {
             fprintf(fpout2,"*%s* %s %s;\"REP FOREVER BLOCK:line%d\"\n",REPFOREVERVEC[i],SCANRGCT[SCANCNT-1],NORMALSGHDR,i+1);
             }
          fprintf(fpout2,"*%s* %s %s;<CJMP .-%d>\"REP FOREVER END BLOCK\"\n",REPFOREVERVEC[i],SCANRGCT[SCANCNT-1],NORMALSGHDR,REPFOREVERLINES-1);
          }
       else {
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR,(VN-1)-SCANATR[SCANCNT-1]-3-(REPFOREVERLINES-1));
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,COND CONT>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          fprintf(fpout2,"*%s* %s %s; <SWCDPM,SDP,FLAG(CONT ON)>\n",DPM_VECTOR,SCANRGCT[SCANCNT-1],NORMALSGHDR);
          for (i=0;i<REPFOREVERLINES-1;i++) {
             fprintf(fpout2,"*%s* %s %s;\"REP FOREVER BLOCK:line%d\"\n",REPFOREVERVEC[i],SCANRGCT[SCANCNT-1],NORMALSGHDR,i+1);
             }
          fprintf(fpout2,"*%s* %s %s;<CJMP .-%d>\"REP FOREVER END BLOCK\"\n",REPFOREVERVEC[i],SCANRGCT[SCANCNT-1],NORMALSGHDR,REPFOREVERLINES-1);
          }
       }
   else {
      fprintf(stderr,"NON_FATAL_ERROR:REPEAT FOREVER NEEDED BUT NOT SURE WHERE IT GOES!!!\n");
      fprintf(fperrors,"NON_FATAL_ERROR:%s:REPEAT FOREVER NEEDED BUT NOT SURE WHERE IT GOES!!! in file[%s]line%ld\n",progstr,infile1,readlinenum);
      }
   }
fprintf(fpout2,"$%s_cpm_end\n*%s* %s %s; <RET>\n",pattern,HOLD_VECTOR,HOLD_CYCLE,NORMALSGHDR);
fprintf(fpout2,"*%s* %s %s; <RPT 512>\n}\n",HOLD_VECTOR,HOLD_CYCLE,NORMALSGHDR);
fclose(fpout2);
if (autogen && maxrepforever==0) {
   fprintf(stderr,"FYI4:CPM AUTOGEN used for: %s_dpm.evo\n",pattern);
   fprintf(fperrors,"FYI4:CPM AUTOGEN used for: %s_dpm.evo\n",pattern);
   remove(outfile2);
   }
else {
   if (autogen) {
      fprintf(stderr,"FYI5:CPM AUTOGEN could NOT be used for: %s_dpm.evo\n",pattern);
      fprintf(fperrors,"FYI5:CPM AUTOGEN could NOT be used for: %s_dpm.evo\n",pattern);
      }
   sprintf(tempstr,"gzip -f %s_cpm.evo &",pattern);
   /* if (gzip) system(tempstr);*/ /* gzip cpm file */
   if(REPFOREVERLINES>0 ||maxrepforever>0) {
      fprintf(stderr,"FYI3:%s: DO NOT optimize the CPM with:\n%s %s\n",compilestr,DEFAULT_SCAN_OPT,outfile2);
      fprintf(fperrors,"FYI3:%s: DO NOT optimize the CPM with:%s %s\n",compilestr,DEFAULT_SCAN_OPT,outfile2);
      }
   else {
      fprintf(stderr,"FYI2:%s: You may wish to optimize the CPM with:\n%s %s\n",compilestr,DEFAULT_SCAN_OPT,outfile2);
      fprintf(fperrors,"FYI2:%s: You may wish to optimize the CPM with:%s %s\n",compilestr,DEFAULT_SCAN_OPT,outfile2);
      }
   }
return(0);
}


void outputvector(FILE *fpout1,int *lastitem,char *out_vector,char *pattern,char *WFT,char *DMI,long VN,int repeatcount,char *errorstr,char *comment){
char tempstr[READLINELEN+1],printstr[READLINELEN+MAXERRORLEN+1];
int i;
printstr[0]='\0';
if (*lastitem==STRING && out_vector[0]!='\0') strcpy(printstr,"\"");

if (out_vector[0]!='\0') {
/*   sprintf(tempstr,"\n*%s00* %s_wft ; ",out_vector,pattern); */ /* now using default waveform table in header */
   sprintf(tempstr,"\n*%s* %s %s; ",out_vector,WFT,NORMALSGHDR);
/* added scope sync pins at end of vector APS 6/12/99*/
   strcat(printstr,tempstr);
   out_vector[0]='\0';
   *lastitem=VECTOR;
   }
if (repeatcount>1){
   sprintf(tempstr," <RPT %d> ",repeatcount);
   strcat(printstr,tempstr);      
   }
if (DMI[0]!='\0'){
   sprintf(tempstr,"\" V%ld:P%ld:C%ld %s",vectorcount-1,VN,cyclecount+65,DMI);/* +65 because of LDA and RPT 64 */
   strcat(printstr,tempstr);/* \""); */
   DMI[0]='\0';
   *lastitem=STRING;
   }
if (errorstr[0]!='\0'){
   if (*lastitem!=STRING) strcat(printstr,"\""); 
   strcat(printstr,errorstr);
   *lastitem=STRING;
   errorstr[0]='\0';
   }
if (comment[0]!='\0'){
   if (*lastitem!=STRING) strcat(printstr,"\""); 
   for(i=0;i<strlen(comment);i++) if(comment[i]=='"' ||comment[i]=='\'') comment[i]='~';
   strcat(printstr,comment);
   comment[0]='\0';
   *lastitem=STRING;
   }
if (repeatcount==-99) strcpy(out_vector,printstr);
else fprintf(fpout1,"%s",printstr);
}
