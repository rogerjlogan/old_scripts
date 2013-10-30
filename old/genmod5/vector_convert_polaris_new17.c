/* This program is covered by the GNU GPL license. Please see the file: COPYING.gz for the license info. */
/* original author: anthony_sully@ltx.com */

/*  vector_convert_polaris7.c     */
/* May  99 Anthony Sully, LTX Corp: Original file created for C6201 translation */
/* Feb. 00 Anthony Sully, LTX Corp. Enhanced code to deal with waveforms better for C6202 */
/* Oct. 00 Anthony Sully, LTX Corp. Minor tweaks for C6203 */
/* Sept.02 Anthony Sully, LTX Corp. Reorganized code for readability and added enhancements
                                    required for Venus (microcontroller group) translation.
                                    Created input preprocessing program (pre_proc.c) to deal
                                    with the repeat block compression and match loops that
                                    microcontroller group patterns use. This implies that
                                    the translator can now generate dpm and/or cpm patterns
                                    based on the input from pre_proc.c */
/* 09/23/02 Anthony Sully, LTX Corp. Tweaked the character choices to match Dale's choices
                                    for the alternate Dset o/i/l/h */                                 
/* 09/28/02 Anthony Sully, LTX Corp. 1) Added option for removing the input .proc input file
                                    automatically (-r) on success. As a safety feature it
                                    will not delete the file if it contains .vpl
                                    2) Modified program to create a running log file 
                                   'translation_errors.txt' of all this the program is not 
                                    happy about. This file will be created if it does not exist
                                    and appended to if it does exist. It will give the file name
                                    of the offending pattern and the line number of the problem,
                                    if appropriate. This file should be reviewed after translation
                                    completes. 
                                    3) Started adding these comments for rev. information.
                                    4) Modified alias assignments so they are defines for consistency.
                                    5) Added option (-a) to pad with two characters. This is intended
                                    to be used with DUT-to-PM or scope triggers and may be useful for
                                    ADC or Flash testing. This also changes the signal header to
                                    PADSGHDR. 
                                    6) Removed default signal header and default waveformtables as
                                    we are being explicit on each vector anyway. */
/* 10/01/02 Anthony Sully, LTX Corp Changed where the end label is placed for CPM patterns */            
/* 10/08/02 Anthony Sully, LTX Corp Found a problem with repeat expansion. The max repeat prints
                                    were not printing although the remainder was. Turned out that
                                    the exceeding max repeat code was in the wrong place (although
                                    the code itself was correct. Tried one pattern that had this
                                    problem and it did seem to fix the failure. Again, this is in
                                    the nasty code so be careful if you touch it!!!! Updated to
                                    vector_convert_polaris3.c */
/* 10/09/02 Anthony Sully, LTX Corp A similar problem was found where the last vector was not printing
                                    its repeat. This was fixed so the RPT would be printed and if the
                                    repeat exceeded the max repeat the max repeats would be printed
                                    then the end label then the remainder RPT. This was also fixed
                                    for the CPM portion of the code. */
/* 10/12/02 Anthony Sully, LTX Corp. Created new version 4 which includes the capability to
                                     create a CPM calling DPM pattern if a match is found and
                                     the vectors before this vector total at least 100. This
                                     adds complexity but will help in reducing CPM usage which
                                     appears to be a big issue. If this situation is setup
                                     by pre_proc4.c then vector_convert_polaris4.c knows to
                                     translate the DPM_%s file first to get the number of
                                     vectors for DPM call. 
                                     After translating the DPM it will rescan the DPM_%s.proc file
                                     to get the MSET/DSET information and then proceed to generate
                                     the CPM pattern. Similar modifications where also made
                                     to pre_proc4.c to setup this option. All that the user needs
                                     to do is add the DPM_%s patterns to the PatternMap.
                                     Modified the name of the uncompressed file to use the name of
                                     the source file with a .tmpgunzip tacked on the end. This
                                     makes the file unique.
                                     Also fixed a problem where the last vector of a DPM pattern
                                     was being repeated, once with a RPT and once without.
                                     Modified final print to indicate what type of vectors 
                                     (CPM or DPM) were generated when giving the count. */
/* 10/18/02 Anthony Sully, LTX Corp. (rev.5) Added two new options (-o and -O) which will try to
                                     optimize the CPM microinstructions and waveformtable references.
                                     (-O is for 'fixing' uncompressed pre-existing cpm patterns and
                                     can also be used on scan cpm patterns to remove the HOLD_CYCLE
                                     wfts). The waveformtable ref. optimization finds the first
                                     non-DEF_WFT, non-ScanCycle, and non-HOLD_CYCLE waveformtable
                                     ref. and replaces any of the DEF_WFT or HOLD_CYCLE references
                                     with that. The general optimization tries to reduce redundant CPM
                                     vectors by replacing small loops with RPTs and moving
                                     microinstructions onto real vectors. The idea was to reduce
                                     problems in match loops not to necessarily reduce the size of CPM.
                                     It also attempts to preserve the comments in the right place. At
                                     the moment it preserves both the original pattern and the new
                                     pattern. The original will be moved to __patternname.evo (and
                                     compressed if the VCP was given the compressed option). Also,
                                     fixed the program so sources can be located in a remote secure
                                     directory. All new files will be created in the local directory. */
/* 10/27/02 Anthony Sully, LTX Corp. Undefined code for RPTP optimization as it does not work correctly
                                     unless the pipeline is pre-filled with fails. */
/* 11/02/02 Anthony Sully, LTX Corp. Fixed compile script and includes so date can be brought in with
                                     gcc or cc */
/* 01/25/03 Anthony Sully, LTX Corp. Modified CPM pattern generation: If CPM pattern has only RPT microinstructions
                                     in the first MAXCPMTODPMLINES then that many will be buffered into DPM memory.
                                     Set up the CPM to call those DPM vectors. Separated MAXCPMTODPMLINES and
                                     MAXCPMOPTLINES. Now upto MAXCPMOPTLINES(1000) vectors can be optimized in dpm.
                                     Vectors upto the first non-DPM microinstruction will be buffered in blocks of
                                     MAXCPMTODPMLINES(100). Separating them gets better compression. Fixed various
                                     subtle problems with CPM patterns (pass through of end;, labels with negative
                                     numbers etc, (some of which was actually fixed in pre_proc6.c).
                                     Updated vector_convert_polaris to rev.6 */
/* 01/29/03 Anthony Sully, LTX Corp. Fixed comment close search in optimize routine to truncate at the end of the
                                     string if the comment did not close due to a long comment */
/* 03/10/03 Anthony Sully, LTX Corp. Modified error messages to give clues as to what happened. There are now four
                                     classes of ERRORS: 
                                     FATAL_ERRORS -- cause immediate exit of program (usually file problems)
                                     BAD_ERRORS -- fatal errors that could produce corrupted output files
                                     NON_FATAL_ERRORS -- errors that generate files with useful output
                                     FYI -- informational warnings. */
/* 03/29/03 Anthony Sully, LTX Corp. Added optimization for CJMP with previous vector RPT added GNU GPL license info.
                                     Found an issue with optimization where if the pattern already had
                                     CPM_CALLING_DPM and then decided that it might be able to optimize it could
                                     damage the original DPM pattern. To fix this I now keep the original DPM
                                     as DPM_ and the DPM optimization happen in DPMO_ (this was noticed in 
                                     venus:DPM_HET_PROG_PSA.vpl) Added translation of shutdown vectors. Due to the
                                     fact that these vectors are not usually needed the translated vectors are written
                                     to the fperrors file (this is also because this file has global visibility).
                                     Added username, hostname, and pwd to pattern header.
                                     Changed date get to 'C' functions instead of unix date. Modified CJMP optimization
                                     to not care whether there was a DC4 or not. This would fix issues if continuous
                                     patterns were used or if another. Increased the size of printhold in
                                     the outputvector function to allow for large repeat expansions. */

/* 04/10/03 Anthony Sully, LTX Corp. Fixed problems with DPM_COUNT so the filename is now unique */
/* 05/05/03 Anthony Sully, LTX Corp. Fixed problem with optimization where the DC?,CJMP optimization was taking
                                     precedence over the CJMP .-1 optimization because the DC? was not looked for.
                                     Added the DC? part of the search back in and this fixed the venus haltpat
                                     problem. This then brought up the fact that if there is a .-anything it
                                     should be optimized as well (the reason I took out the DC4 part). Fixed this
                                     as well. */

/* 09/24/03 Anthony Sully, LTX Corp. Added support for user defined signal header (in cycletbl_mod.mod2),
                                     gct_gen_mod2. This is needed because some devices may have patterns with
                                     different widths. Added code to check that the cycletbl file has the same
                                     number of pins as the polaris pattern, exit if not the same. Same update
                                     to vector_convert_scan as well. Also, fixed an issue where a empty line
                                     in a shutdown loop was causing a sigsegv. Turned out a pointer was not
                                     checked against NULL. Added NULL check to all valid strstr and strchr ptr
                                     assignments. */
/* 02/25/04 Anthony Sully, LTX Corp. modified how files are renamed and removed to use 'C' calls instead of system() */

/* 03/23/04 Anthony Sully, LTX Corp. added some error messages for rename() and remove() files */

/* 07/26/04 Anthony Sully, LTX Corp. Found issue with commented out match. Comment open gets left pending
                                     in DPM pattern, CPM pattern doesn't know it should be commented. 
                                     Made DPM_COUNT more unique. Added pending comment count to DPM_COUNT file.*/
/* 01/31/05 Anthony Sully, LTX Corp. Based on user input, modified how optimized cpm start label was named.
                                     Originally, the newly optimized start label was $patname_begin_real_st
                                     and the preoptimized label was $patname_begin. NOW: optimized start
                                     label is $patname_begin and the original is $patname_begin_orig. */
/* 02/06/05 Anthony Sully, LTX Corp. Added a line to remove the annoying DpM_CoUnT_* files. Added warning for files
                                     that don't contain enough vectors and cycles. 
                                     Updated as vector_convert_polaris9.c */
/* 03/10/05 Anthony Sully, LTX Corp. Pattern from T3 with various issues, some wrong, some suboptimal:
                                     6) Move the status messages to a temp file instead of stdout
                                     See nsf_auto_pre_proc10.c
                                     Bill also identified an issue with T3 where the cpm to dpm optimization
                                     was creating more than 65535 cycles in dpm and the optimization
                                     step wasn't treating large count correctly in cpm. This is fixed. 
                                     Short patterns now pad to meet the 16vector/64cycle rule for HFi and by
                                     extrapolation HF. */
/* 06/05/05 Anthony Sully, LTX Corp. Fixed some minor issues for repeat padding and removed the repeat 512
                                     after the RET as envision now processes this automatically in the thread.
                                     Found some serious flaws (they had been noted already) in the optimization
                                     routines. 1) It was not checking that the CJMP opt3 was jumping to the
                                     immediately previous vector label. 2) It was only optimizing DC4,CJMP not
                                     DC3,CJMP etc. Both of these issues were fixed.
                                     Added the preprocess revision at the top of the file also.
                                     Optimized CPM patterns will have this at the end. Unoptimized CPM will
                                     have it at the top. DPM will also have it at the top. Not sure about
                                     DPMO_%s patterns. (check the cpm in this case!)
                                     Updated to vector_convert_polaris11.c */
/* 07/14/05 Anthony Sully, LTX Corp. Changed behavior on EXCEEDING BUFFER SIZE statements (around line 900).
                                     Previous action was to exit. New action is to empty the buffer and
                                     continue. Updated to rev.12 */
/* 07/27/05 Anthony Sully, LTX Corp. moved the "optpreprocrev" print statement in the CPM optimization 
                                     before the final brace print as enVision appears unhappy with it after
                                     the closing brace. No update to revision.  */
/* 07/30/05 Anthony Sully, LTX Corp. Found errors in the June05 update (for padding out CPM/DPM) that the
                                     repeat count (VNIR) for DPM was off if the last DPM vector had a repeat.
                                     This has been fixed and VNIR is now shown in the comments. Also found
                                     that in the optimization routines it was adding an extra SDP to the
                                     "MODE(IFAIL ON,...)" optimization. Updated to rev.13.0  */

/* 09/14/05 Anthony Sully, LTX Corp. Bumped max GCTs from 30 to 100. Added addition check for is_microinstruction
                                     wft_is_empty. Added preremove of DPM_COUNT file. */  

/* 11/20/05 Anthony Sully, LTX Corp. Added command line option to generate dpm count file for cpm requested dpm
                                     translation. Did not bump file rev but did bump internal rev to 14.1 */
                                     
/* 05/11/06 Anthony Sully, LTX Corp. Joel had an issue with match loops not getting translated. It turned out
                                     that due to a waveform table being passed in with the microinstruction
                                     it did not recognize it as a microinstruction. I don't quite understand
                                     how anything worked without this fix but the fix was to change the
                                     vector_is_microinstr from wft_is_empty to (0==strcmp(wft,DEF_WFT) ||
                                     wft_is_empty). Updated to 15.0 */
/* 06/29/08 Anthony Sully, LTX Corp. Added support for reading DEBUG_PROC environment variable */
/* 07/21/08 Anthony Sully, LTX Corp. Moved shutdown detect to after the comment check stuff */
/* 08/09/08 Anthony Sully, LTX Corp. New character set, again. New rev.17 Now VCP_NEW */
#define REV 17.0

#ifndef __GNUC__
#include "local_date.h"
#define __TIME__ ""
#endif

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXCPMTODPMLINES 100
#define MAXCPMOPTLINES 1000
#define READLINELEN 2000
#define MULTILINESIZE 32767
#define MULTILINESIZEBIG 200000
#define FILENAMELEN 120
#define MAXWAVE 5000
#define MAXCYCLE 2000
#define MAXPINS 400
#define MAXGCT 100
#define MAXGCTLEN 15
#define MAXALIAS 33
#define MAXPINLEN 10
#define MAXERRORLEN 1025
#define MAXRPT 2000
#define VECTORLEN 256
#define MAXMSET 256
#define MAXDSET 256
#define MAXISET 15
#define MAXMODGCT 100
#define MEMOSTRLEN 256
#define MAXGCTDSET 200
#define transl_err_file "translation_errors.txt"
#define transl_status_file "translation_status.txt"
#define DPM_COUNT_file "DpM_CoUnT"

#define HOLD_CHAR '-'
#define CPMDPM_CHAR 'd'

#define PADCHAR 'L'
#define PADCHARNOT 'H'

#define PADSGHDR "SH0_PAD"
#define DFLTSGHDR "SH0"
#define DEF_WFT "DEF_WFT"
/* from vector_convert_scan2.c, for optimization */
#define MAXSIGHDRLEN 25
#define HOLD_CYCLE "HOLD_CYCLE"
/* #define NORMALSGHDR "SH0" */

#define NO_DMI "~"
#define NO_WFT "~"
#define NO_VECTOR "~"
#define NO_COMMENT "~"
#define NO_MICROINSTR "~"

#define NO_REPEAT 1
#define VECTOR_DONE -1
#define MAX_RPT_CPM 65535
#define MAX_RPT_DPM 2047

struct SETvS {
   char *MSETPTR,*DSETPTR,*ISETPTR,*WFT,GCTMODNAME[MAXMODGCT][MAXGCTLEN+1],VECTMOD[MAXMODGCT][MAXPINS+1];
   int maxgctDSET;
   };
struct SETvS SETS;

typedef int boolean;
#define  TRUE 1
#define FALSE 0
/* global vars:*/

boolean DEBUG=FALSE;     /* off by default */
char progstr[MEMOSTRLEN],datestr[MEMOSTRLEN],timestr[MEMOSTRLEN],compilestr[MEMOSTRLEN],mydate[101];/* concaternated strings */
char env[READLINELEN+1],*endptr;

boolean QUIET=TRUE;
boolean SUPPRESS_COMMENTS=FALSE;
boolean REPEAT_COMPRESSION=TRUE;
int CPM=0,addpad=0;
char dummy_vector[MULTILINESIZE],cpmdpm_vector[MULTILINESIZE];
/* the following are globabls for convenience in functions */
FILE *fperrors,*tempfile,*fpstatus;
char infile_orig[FILENAMELEN];
long readlinenum=0,VC,VN=0,VNIR=0,countrpts=0;

char username[MEMOSTRLEN],hostname[MEMOSTRLEN],pwd[MEMOSTRLEN];
char tempgunzipname[FILENAMELEN];
int gzip=0,gunzip=0;
char NORMALSGHDR[MAXSIGHDRLEN+1];
int MOD2_SIZE;

/* function prototypes */
int outputvector(FILE *fpout1,char *out_vector,char *WFT,char *DMI,long repeatcount,char *comment,char *microinstr,int CPM);
char * get_count(char *ptr,int offset,long *count,int call);
int deal_with_shutdown(char *line,char *ptr,FILE *fpin1);
int deal_with_comment(FILE *fpout1,char *mod_vector,char *comment,int *commentcount,int *commentflag,int *commentON,int vectorflag);
int check_SET(int beginflag,char *mod_vector,const char *SET,int *notgood,int MAX,char SETPTR[]);
int vector_convert(int *beginflag,char *vector,char *mod_vector,struct SETvS *SETS,char *out_vector1,char *DMI);
int cpmoptimize(char *pattern);


#define NUMPINS 1026
#define PINSIZE 50
int pinheadcount=0;
char pinhead[PINSIZE][NUMPINS];

/* begin main function */
int main (int argc,char *argv[],char *envp[]){

/* file variables */
FILE *fpin1,*fpout1,*fpin2;
time_t generictime;
int filein1=0,filein2=0;
char infile_local[FILENAMELEN];
char outfile1[FILENAMELEN];
char pattern[FILENAMELEN];
/* mode settings */

/* buffers */
char printstring[MULTILINESIZE+1],vector[READLINELEN];
char mod_vector[MULTILINESIZE],keep_vector[MULTILINESIZE];
char  out_vector1[READLINELEN],     comment[MULTILINESIZE+1],     WFT[MAXGCTLEN+1];
char DMI[15];/* only do repeat compression in VX125 mode */
char readstr[READLINELEN];
/* char GCTMODNAME[MAXMODGCT][MAXGCTLEN+1],VECTMOD[MAXMODGCT][MAXPINS+1]; */

char *MSETPTR,*DSETPTR,*ISETPTR;
/* concaternated strings */

/* control parameters */
int commentflag,beginflag,vectorflag=0,commentON,commentcount,newcommentcount,errorflag;
int notgood=0,rv,remove_pre=0,CPMOPTIMIZE=0,writecount=0;
int gctstart,gctend,vectorstart,vectorend,maxgctDSET,scnt=0;

/* temporary variables */
int i,j;
long t1,repeatdec,cpmcallingdpmcount;
char tempstr[READLINELEN+1],*ptr,*ptr1,*retptr;
char *ptrOB,*ptrCB,*ptrLT,*ptrGT,*ptrOPEN,*ptrCLOSE;
char preprocessrev[READLINELEN+1];
int vl;
char muxpins[READLINELEN+1],muxcopy[READLINELEN+1];
int muxcount;

if (getenv("DEBUG_PROC")==NULL) DEBUG=FALSE;
else {strcpy(env,getenv("DEBUG_PROC"));DEBUG=TRUE;fprintf(stderr,"Turning on DEBUG!\n");}

strcpy(NORMALSGHDR,DFLTSGHDR);
/* command line stuff */
if (argc>1) {
   if (strchr((char *)argv[1],'-')!=NULL){
      if (strchr((char *)argv[1],'s')!=NULL) QUIET = TRUE;
      if (strchr((char *)argv[1],'f')!=NULL && argc>=3) filein1 = 1;
      if (strchr((char *)argv[1],'g')!=NULL && argc>=4) filein2 = 1;
      if (strchr((char *)argv[1],'z')!=NULL ) gzip=1;
      if (strchr((char *)argv[1],'r')!=NULL ) remove_pre=1; 
      if (strchr((char *)argv[1],'a')!=NULL ) addpad=1;
      if (strchr((char *)argv[1],'o')!=NULL ) CPMOPTIMIZE=1;
      if (strchr((char *)argv[1],'O')!=NULL ) CPMOPTIMIZE=2;
      if (strchr((char *)argv[1],'c')!=NULL ) writecount=1;
      }
   else QUIET=0;
   }
if (argc==1) QUIET=0;
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
   fprintf(stderr,"options are: -s => silent\n");
   fprintf(stderr,"f => pattern file\n");
   fprintf(stderr,"g => GCT mod file\n");
   fprintf(stderr,"z => run gzip on output pattern file\n");
   fprintf(stderr,"r => remove input file (i.e. .proc file)\n");
   fprintf(stderr,"a => add two pad chars.(for DUT_to_PM or scopetrig %c%c)\n",PADCHAR,PADCHARNOT);
   fprintf(stderr,"o => post process any CPM patterns to optimize vectors/microinstructions\n");
   fprintf(stderr,"O(caps) => optimize CPM pattern only (no translation)\n");
   fprintf(stderr,"c => write dpm count to a file for cpm processing\n");
   fprintf(stderr,"\nUsage:%s -fzgor PAT.proc cycletbl.mod2\n",compilestr);
   }
if (NULL==(fperrors=fopen(transl_err_file,"a"))) {
   fprintf(stderr,"\nFATAL_ERROR:Could not open %s for output\n",transl_err_file);
   exit(1);
   }
if (NULL==(fpstatus=fopen(transl_status_file,"a"))) {
   fprintf(stderr,"\nFATAL_ERROR:Could not open %s for output\n",transl_status_file);
   exit(1);
   }

/* open pattern input file */
if (filein1) strcpy(infile_orig,(char *) argv[2]);
else {
   fprintf(stderr,"Enter input PATTERN file: ");
   fgets(infile_orig,FILENAMELEN,stdin);
   infile_orig[strlen(infile_orig)-1]='\0';/* fgets gives the \n so clear it!! */
   }
strcpy(infile_local,infile_orig);
t1=0;
while (NULL!=(ptr=strchr(infile_local,'/'))){
   t1=(ptr-infile_local);
   infile_local[t1]=' ';t1++;
   }
j=0;
while(NULL==strchr(". ",infile_local[t1]) && t1<strlen(infile_local) ) pattern[j++]=infile_local[t1++];
pattern[j]='\0';
fprintf(stderr,"\npattern_name:%s\n",pattern);
if (!QUIET) fprintf(fpstatus,"\npattern_name:%s\n",pattern);

if (CPMOPTIMIZE==2) {CPM=2;goto CPMOPTIMIZE_ONLY;}

t1=strlen(infile_local);
if ((infile_orig[t1-3]=='.' && infile_orig[t1-2]=='g' && infile_orig[t1-1]=='z')||(infile_orig[t1-2]=='.' && infile_orig[t1-1]=='Z') ){/* compressed input file */
   if (NULL!=(fpin1=fopen(infile_orig,"r"))) {
      fclose(fpin1);
      sprintf(tempgunzipname,"%s.tmpgunzip",pattern);
      sprintf(tempstr,"gunzip -c %s >%s",infile_orig,tempgunzipname);
      fprintf(fpstatus,"%s\n",tempstr);
      system(tempstr);/* unzip to temporary file */
      if (NULL==(fpin1=fopen(tempgunzipname,"r"))) {
         fprintf(stderr,"\nFATAL_ERROR:Uncompressed input file [%s] not found\n",tempgunzipname);
         fprintf(fperrors,"\nFATAL_ERROR:%s:Uncompressed input file [%s] not found\n",progstr,tempgunzipname);
         exit(1);
         }
      gunzip=1;
      }
   else {
      fprintf(stderr,"\nFATAL_ERROR:Input file [%s] not found\n",infile_orig);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Input file [%s] not found\n",progstr,infile_orig);
      exit(1);
      }
   }
else {
   if (NULL==(fpin1=fopen(infile_orig,"r"))) {
      fprintf(stderr,"\nFATAL_ERROR:Input file [%s] not found\n",infile_orig);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Input file [%s] not found\n",progstr,infile_orig);
      exit(1);
      }
   }
if (!QUIET) fprintf(stderr,"input file1 ok\n");
infile_local[0]='\0';
if (filein2) strcpy(infile_local,(char *) argv[3]);
else {
   fprintf(stderr,"Enter input gct summary file: ");
   fgets(infile_local,FILENAMELEN,stdin);
   infile_local[strlen(infile_local)-1]='\0';/* fgets gives the \n so clear it!! */
   }
if (NULL==(fpin2=fopen(infile_local,"r"))) {
   fprintf(stderr,"\nFATAL_ERROR:Input file [%s] not found\n",infile_local);
   fprintf(fperrors,"\nFATAL_ERROR:%s:Input file [%s] not found\n",progstr,infile_local);
   exit(1);
   }
if (!QUIET) fprintf(stderr,"input file2 ok\n");

if (1){/* pattern output file */
   sprintf(outfile1,"%s.evo",pattern);
   if (NULL==(fpout1=fopen(outfile1,"w"))) {
      fprintf(stderr,"\nFATAL_ERROR:Could not open output file [%s] for output\n",outfile1);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open output file [%s] for output\n",progstr,outfile1);
      exit(1);
      }
   }

/* get ALT D-set information */
maxgctDSET=0;
muxpins[0]='\0';
while(fgets(readstr,READLINELEN-1,fpin2) != NULL ){
   readstr[strlen(readstr)-1] = '\0';/* remove trailing \n */
   if (NULL!=strstr(readstr,"#USE_SIGNAL_HEADER:")) {
      strcpy(NORMALSGHDR,readstr+strlen("#USE_SIGNAL_HEADER:"));
      fprintf(fpstatus,"*** USER DEFINED SIGNAL HEADER:<%s> ***\n",NORMALSGHDR);
      continue;
      }
   if (readstr[0]=='H') continue; /* nothing to do if hexproc */
   if (readstr[0]=='F') continue; /* nothing to do if fields */
   if (readstr[0]=='M') {strcpy(muxpins,readstr+2);continue;}
   if (readstr[0]=='P') {;continue;}/* PINGROUP, these are really comments */
   if (readstr[0]=='/') {strcpy(pinhead[pinheadcount],readstr);pinheadcount++;continue;}/* pinheader info */

   ptrLT=strchr(readstr,'<');
   ptrGT=strchr(readstr,'>');
   ptrOB=strchr(readstr,'[');
   ptrCB=strchr(readstr,']');
   if (ptrLT==NULL || ptrGT==NULL || ptrOB==NULL || ptrCB==NULL) continue;/* anything else isn't a GCT set */

   gctstart=(int)(ptrLT-&readstr[0])+1;
   gctend=(int)(ptrGT-&readstr[0])-1;
   vectorstart=(int)(ptrOB-&readstr[0])+1;
   vectorend=(int)(ptrCB-&readstr[0])-1;
   MOD2_SIZE=vectorend-vectorstart+1;
   for (j=0,i=gctstart;i<=gctend;j++,i++) SETS.GCTMODNAME[maxgctDSET][j]=readstr[i];
   SETS.GCTMODNAME[maxgctDSET][j]='\0';
   for (j=0,i=vectorstart;i<=vectorend;j++,i++) SETS.VECTMOD[maxgctDSET][j]=readstr[i];
   SETS.VECTMOD[maxgctDSET][j]='\0';
   maxgctDSET++;
   }

if (muxpins[0]!='\0') {
   for (j=0;j<maxgctDSET;j++) {
      if (DEBUG) fprintf(stdout,"GCTIN [%s]\nMUXPIN<%s>{%d}\n",SETS.VECTMOD[j],muxpins,MOD2_SIZE);
      for (muxcount=i=0;i<strlen(muxpins);i++) {
         muxcopy[i+muxcount]=SETS.VECTMOD[j][i];
         if (muxpins[i]=='M') {
            muxcount++;
            muxcopy[i+muxcount]=SETS.VECTMOD[j][i];
            }
         }
      muxcopy[i+muxcount]='\0';
      strcpy(SETS.VECTMOD[j],muxcopy);
      if (DEBUG)fprintf(stdout,"GCTOUT[%s]\n",SETS.VECTMOD[j]);
      } /* end maxgctDSET */
   }
MOD2_SIZE+=muxcount;fprintf(stdout,"{%d}\n",MOD2_SIZE);
/* create a dummy vector for microinstruction only lines, base it on sizeof GCT pin file */
for (j=0,i=vectorstart;i<=vectorend;j++,i++) {
   dummy_vector[j]=HOLD_CHAR;
   cpmdpm_vector[j]=CPMDPM_CHAR;
   }
for (i=1;i<=muxcount;j++,i++) {
   fprintf(stderr,"ADDING %d MUXPINS[%d]\n",muxcount,i);
   dummy_vector[j]=HOLD_CHAR;
   cpmdpm_vector[j]=CPMDPM_CHAR;
   }
dummy_vector[j]='\0';
cpmdpm_vector[j]='\0';
fclose(fpin2);

/* allocate buffers */
MSETPTR=(char *)malloc((unsigned)(VECTORLEN*MAXMSET));
DSETPTR=(char *)malloc((unsigned)(VECTORLEN*MAXDSET));
ISETPTR=(char *)malloc((unsigned)(VECTORLEN*MAXISET));
if (MSETPTR==NULL) fprintf(stderr,"FATAL_ERROR:Could not allocate msetptr\n");
if (MSETPTR==NULL) fprintf(fperrors,"FATAL_ERROR:%s:Could not allocate msetptr[%s]\n",progstr,infile_orig);
if (DSETPTR==NULL) fprintf(stderr,"FATAL_ERROR:Could not allocate dsetptr\n");
if (DSETPTR==NULL) fprintf(fperrors,"FATAL_ERROR:%s:Could not allocate dsetptr[%s]\n",progstr,infile_orig);
if (ISETPTR==NULL) fprintf(stderr,"FATAL_ERROR:Could not allocate isetptr\n");
if (ISETPTR==NULL) fprintf(fperrors,"FATAL_ERROR:%s:Could not allocate isetptr[%s]\n",progstr,infile_orig);
if (MSETPTR==NULL || DSETPTR==NULL || ISETPTR==NULL) exit(6);
if (!QUIET) fprintf(stderr,"Memory allocated ok\n");

SETS.MSETPTR=MSETPTR;
SETS.DSETPTR=DSETPTR;
SETS.maxgctDSET=maxgctDSET;
SETS.ISETPTR=ISETPTR;
SETS.WFT=WFT;
/* SETS.GCTMODNAME=GCTMODNAME;
SETS.VECTMOD=VECTMOD; */

   /***********************************************/
   /*                                             */
   /*    do some initial setup and checks         */
   /*                                             */
   /***********************************************/
fgets(vector,READLINELEN-1,fpin1);
readlinenum++;
printstring[0]='\0';
comment[0]='\0';
beginflag=0;
errorflag=0;
commentON=0;
repeatdec=1;
commentcount=0;
if (strstr(vector,"(*-FLAG-This must be a CPM pattern-*)")!=0) {CPM=1;}
if (strstr(vector,"(*-FLAG-This must be a CPM_CALLING_DPM pattern-*)")!=0) {
   CPM=2;
   /* cannot use the -r here, use -z if requested on this program call */
   /* added 'c' option to write dpm count */
   sprintf(tempstr,"%s -fgc%c DPM_%s %s",compilestr,(gzip)?'z':' ',argv[2],argv[3]);
   fprintf(stderr,"Running %s on the dpm portion\n",compilestr);
   system(tempstr);
   fprintf(fpstatus,"Returning from [%s]\n",tempstr);
   sprintf(tempstr,"%s_DPM_%s",DPM_COUNT_file,pattern);
   if(NULL==(tempfile=fopen(tempstr,"r"))) {
      fprintf(stderr,"\nFATAL_ERROR:Could not open %s for input\n",tempstr);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open %s for input\n",progstr,tempstr);
      exit(1);
      }
   fscanf(tempfile,"%ld,%d\n",&cpmcallingdpmcount,&newcommentcount);
   if (newcommentcount>0) fprintf(stderr,"There were %d pending DPM comments!!!\n",newcommentcount);
   commentcount+=newcommentcount;
   if (commentcount>0) commentON=1;
   fclose(tempfile);
   fprintf(stderr,"CPM calling DPM count=%ld[%s]\n",cpmcallingdpmcount,tempstr);
   /* remove count file: */
   remove(tempstr);
   sprintf(tempstr,"DPM_%s",argv[2]);
   if(NULL==(tempfile=fopen(tempstr,"r"))) {
      fprintf(stderr,"\nFATAL_ERROR:Could not open %s for input again\n",tempstr);
      fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open %s for input again[%s]\n",progstr,tempstr,infile_orig);
      exit(1);
      }
   beginflag=1;
   while(fgets(vector,READLINELEN-1,tempfile) != NULL ){
      if (NULL!=(ptrOPEN=strstr(vector,"(*")) && NULL!=(ptrCLOSE=strstr(vector,"*)"))) {
         while(ptrOPEN!=(ptrCLOSE+1)) *ptrOPEN++=' '; /* wipe out comment with spaces */
         }
      rv=check_SET(beginflag,vector,"MSet",&notgood,MAXMSET,MSETPTR);
      if (1==rv) break;
      if (2==rv) {scnt++;continue;}
      rv=check_SET(beginflag,vector,"DSet",&notgood,MAXDSET,DSETPTR);
      if (1==rv) break;
      if (2==rv) {scnt++;continue;}
      rv=check_SET(beginflag,vector,"ISet",&notgood,MAXISET,ISETPTR);
      if (1==rv) break;
      if (2==rv) break;/* STOP if found Iset */
      }
   fclose(tempfile);
   fprintf(fpstatus,"\nSuccessfully got Mset/Dset total=[%d] and final Iset Info from %s\n",scnt,tempstr);
   beginflag=1;
   vectorflag=1;
   }
fprintf(fpout1,"enVisionObject:\"bl8:R5.7\";\n\n");
fprintf(fpout1,"Pattern %s {\n",pattern);
if (!CPM) fprintf(fpout1,"    Type Dpm;\n");
if ( CPM) fprintf(fpout1,"    Type Cpm;\n");
/* fprintf(fpout1,"    Default WaveformTable %s;\n",DEF_WFT); */
/* fprintf(fpout1,"    Default SignalHeader %s;\n",DFLTSGHDR); */

fprintf(fpout1,"\" Pattern convertor: %s REV:%2.1f:%s by Anthony Sully compile_date:%s@%s\"\n",compilestr,REV,progstr,__DATE__,__TIME__);
fprintf(fpout1,"\"      Pattern converted on:%s by:%s on host:%s \"\n\"      in pwd:%s\"\n",mydate,username,hostname,pwd);
fprintf(fpout1,"\"Alias assignments:\"\n");
fprintf(fpout1,"\"                                        \"\n");
fprintf(fpout1,"\"DSET0 DSET1                             \"\n");
fprintf(fpout1,"\"l/h    *L/H drive             0x02      \"\n");
fprintf(fpout1,"\"X/.*   x/, driveoffcompareoff 0x09 9=8+1\"\n");
fprintf(fpout1,"\"z/Z    y/Y driveoff only      0x01      \"\n");
fprintf(fpout1,"\"e/E*   k/K EndWindow          0x08      \"\n");
fprintf(fpout1,"\"0/1*   o/i EdgeStrobe         0x03      \"\n");
fprintf(fpout1,"\"w/W*   v/V WindowStrobe       0x04      \"\n");
fprintf(fpout1,"\"f/F*   g/G FloatStrobe        0x05      \"\n");
fprintf(fpout1,"\"u/U*   t/T FloatWindow        0x06      \"\n");
fprintf(fpout1,"\"-          Continue           0x07      \"\n");
fprintf(fpout1,"\"d          CPM/DPM                      \"\n");
fprintf(fpout1,"\"s/D        scan out/in                  \"\n");
fprintf(fpout1,"\"                                        \"\n");
if (addpad){
   fprintf(fpout1,"\n\n\" NOTE: **** Two pad characters added to the END of the vector!!!! *****\"\n");
   fprintf(fpout1,    "\"       ****  and SignalHeader switched to   %-17s!!!! *****\"\n\n",PADSGHDR);
   }
for (i=0;i<pinheadcount;i++) fprintf(fpout1,"\" %s\"\n",&pinhead[i][2]);/* get past // */
VC=0;

fprintf(fpout1,"$%s_begin\n",pattern);
if (CPM==2) {
   fprintf(fpout1,"* %s* %s %s; <LDA DPM_%s_begin>\n",dummy_vector,DEF_WFT,NORMALSGHDR,pattern);
   fprintf(fpout1,"* %s* %s %s; <RPT 64>\n",dummy_vector,DEF_WFT,NORMALSGHDR);VNIR+=64;
   VC += 2;
   while (cpmcallingdpmcount>MAX_RPT_CPM) {
      fprintf(fpout1,"* %s * %s %s;<RPT %ld,SDP>\n",cpmdpm_vector,DEF_WFT,NORMALSGHDR,(long)MAX_RPT_CPM);VNIR+=MAX_RPT_CPM;
      VC++;
      cpmcallingdpmcount-=MAX_RPT_CPM;
      }
   fprintf(fpout1,"* %s * %s %s;<RPT %ld,SDP>\n",cpmdpm_vector,DEF_WFT,NORMALSGHDR,cpmcallingdpmcount);VNIR+=cpmcallingdpmcount;
   VC++;
   }
if (!CPM) {
   vector[strlen(vector)-1] = '\0'; /* remove trailing \n */
   fprintf(fpout1,"\"%s\"\n",vector);
   VC++;
   }
   /***********************************************/
   /*                                             */
   /*    begin main loop for file processing      */
   /*                                             */
   /***********************************************/
while(fgets(vector,READLINELEN-1,fpin1) != NULL ){
   if (strstr(vector,"{-FLAG-preprocessed with")!=0) {
      strcpy(preprocessrev,vector);
      preprocessrev[strlen(preprocessrev)-1]='\0';/* remove the carriage return */
      fprintf(fpout1,"\"%s\"\n",preprocessrev);
      preprocessrev[0]='\0';
      continue;
      }
   readlinenum++;
   if ((readlinenum % 2500)==0) {fprintf(fpstatus,"Reading line %ld\n",readlinenum);fflush(fpstatus);}
   commentflag=0;
   vector[strlen(vector)-1] = '\0';/* remove trailing \n */
   strcpy(mod_vector,vector);
   vl=strlen(mod_vector);
   if (vector[0]=='$') { /* label was passed in */
      outputvector(fpout1,vector,NO_WFT,NO_DMI,NO_REPEAT,NO_COMMENT,NO_MICROINSTR,CPM);
      continue;
      }
   if (vector[0]=='<') {/* microinstruction was passed in */
      outputvector(fpout1,dummy_vector,DEF_WFT,NO_DMI,NO_REPEAT,NO_COMMENT,vector,CPM);
      VC++;
      continue;
      }
   for (i=0;i<vl;i++) { /* simplify comments */
      if (mod_vector[i]=='(' && mod_vector[i+1]=='*') {mod_vector[i]='{'; mod_vector[i+1]=' ';}
      else if (mod_vector[i]=='*' && mod_vector[i+1]==')') {mod_vector[i]='}'; mod_vector[i+1]=' ';}
      else if (mod_vector[i]=='*') mod_vector[i]='x';
      else if (mod_vector[i]=='"') mod_vector[i]='#';
      }
   if (vl==0) continue;/* empty line */
   if (DEBUG) fprintf(fpstatus,"V:%s\n",mod_vector);
   /* moved shutdown detect to after the comment check stuff */
   /* if we have an open comment and there is nothing to close it then add whatever we found to 'comment' */
   if (commentON && NULL==strchr(mod_vector,'}')) {strcat(comment,mod_vector);continue; }
   /* otherwise lets see if we can close it */
   else if (commentON){
      if (1==deal_with_comment(fpout1,mod_vector,comment,&commentcount,&commentflag,&commentON,vectorflag));
      continue;
      }
/* this means there is a comment and we are not currently inside a block */
   while (NULL!=(ptr1=strchr(mod_vector,'{')) && commentON==0 ){
      if (1==deal_with_comment(fpout1,mod_vector,comment,&commentcount,&commentflag,&commentON,vectorflag));
         continue;
      }
   if (commentON) { /* need more lines */
      strcpy(keep_vector,mod_vector);
      continue;
      }
   if (NULL!=(ptr=strstr(mod_vector,"Shutdown")) || NULL!=(ptr=strstr(mod_vector,"ShutDown")) ) {
      deal_with_shutdown(mod_vector,ptr,fpin1);
      }/* end if shutdown */
   if (DEBUG) fprintf(fpstatus,"comment=<%s>",comment);
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"begin"))) {
      fprintf(stderr,"NON_FATAL_ERROR:found internal begin around proc line[%ld]...ignoring. Run pre_proc  or  check file for two patterns in one\n",readlinenum);
      fprintf(fperrors,"NON_FATAL_ERROR:%s:found internal begin...proc ignoring[%s]line:%ld. Run pre_proc or check file for two patterns in one\n",progstr,infile_orig,readlinenum);
      notgood=-1;
      continue;
      }
   if (beginflag==0 && NULL!=(ptr=strstr(mod_vector,"begin"))) {
      beginflag=1;
      if (DEBUG) fprintf(fpstatus,"found begin\n");
      outputvector(fpout1,NO_VECTOR,NO_WFT,NO_DMI,NO_REPEAT,comment,NO_MICROINSTR,CPM);
      continue;
      }
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"end"))) {
      if (DEBUG) fprintf(fpstatus,"found end\n");
      continue;
      }
   if (NULL!=(ptr=strstr(mod_vector,"Scan"))) {
      fprintf(stderr,"BAD_ERROR: Scan pattern!!!...exiting\n");
      fprintf(fperrors,"BAD_ERROR:%s: Scan pattern!!!...exiting[%s]line:%ld\n",progstr,infile_orig,readlinenum);
      notgood=1;
      break;
      }
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"repeat forever"))) {
      fprintf(stderr,"BAD_ERROR:found repeat forever...exiting. This should have been caught with PRE_PROC\n");
      fprintf(fperrors,"BAD_ERROR:%s:found repeat forever...[%s]line:%ld This should have been caught with PRE_PROC\n",progstr,infile_orig,readlinenum);
      notgood=1;
      break;
      }
   if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,"repeat"))) {
      retptr=get_count(ptr,sizeof("repeat"),&repeatdec,1);
      fprintf(fpstatus,"found repeat [%ld]\n",repeatdec);
      VNIR=VNIR+repeatdec-1;
      continue;
      }
   rv=check_SET(beginflag,mod_vector,"MSet",&notgood,MAXMSET,MSETPTR);
   if (1==rv) break;
   if (2==rv) continue;
   rv=check_SET(beginflag,mod_vector,"DSet",&notgood,MAXDSET,DSETPTR);
   if (1==rv) break;
   if (2==rv) continue;
   rv=check_SET(beginflag,mod_vector,"ISet",&notgood,MAXISET,ISETPTR);
   if (1==rv) break;
   if (2==rv) continue;
  
   if (commentON==0 && beginflag>=1 && NULL!=strchr(mod_vector,'[') && 
           NULL!=strchr(mod_vector,']') && NULL!=strchr(mod_vector,'[') && NULL!=strchr(mod_vector,'[')) {
      vectorflag=1;
      vector_convert(&beginflag,vector,mod_vector,&SETS,out_vector1,DMI);
      repeatdec=outputvector(fpout1,out_vector1,WFT,DMI,repeatdec,comment,NO_MICROINSTR,CPM);

      }
      
   } /* end of while vector */
   
   /********************/
   /* End of main loop */ 
   /********************/

sprintf(vector,"$%s_end",pattern);
outputvector(fpout1,vector,NO_WFT,NO_DMI,VECTOR_DONE,NO_COMMENT,NO_MICROINSTR,CPM);
if (commentON) fprintf(stderr,"[%d] COMMENT(s) PENDING!!!\n",commentcount);
fclose(fpin1);
fclose(fpout1);
if (gunzip) {
   if (0!=remove(tempgunzipname)) perror("Error removing ungzipped temp file");
   }
CPMOPTIMIZE_ONLY: 
if (notgood==1) {
   sprintf(tempstr,"%s.evo",pattern);
   if (0!=remove(tempstr)) perror("Error removing BAD output file");
   fprintf(stderr,"BAD_ERROR: File %s was not successful!!! \n",infile_orig);
   fprintf(fperrors,"BAD_ERROR:%s: File [%s] was not successful!!! \n",progstr,infile_orig);
   }
else {
   if (notgood==-1) {
      fprintf(stderr,"NON_FATAL_ERROR: File %s had internal begin!!!\n",infile_orig);
      fprintf(fperrors,"NON_FATAL_ERROR:%s: File [%s] had internal beginl!!!\n",progstr,infile_orig);
      }
   if (CPMOPTIMIZE && CPM) {
      i=cpmoptimize(pattern);
      if (gzip && i==0){
         sprintf(readstr,"gzip -f __%s.evo &",pattern);
         system(readstr); /* gzip old cpm file */
         }
      }
   if (gzip) {
      sprintf(tempstr,"gzip -f %s.evo &",pattern);
      system(tempstr); /* gzip new cpm pattern */
      }
   sprintf(tempstr,"%s_DPM_%s",DPM_COUNT_file,pattern);
   if (CPM==2) if (0!=remove(tempstr))perror("Can't remove *_DPM_* file");
   if (CPM==0 && writecount) {
   sprintf(tempstr,"%s_%s",DPM_COUNT_file,pattern);
      if(NULL==(tempfile=fopen(tempstr,"w"))) {
         fprintf(stderr,"\nFATAL_ERROR: Could not open %s for output\n",tempstr);
         fprintf(fperrors,"\nFATAL_ERROR:%s: Could not open %s for output\n",progstr,tempstr);
         exit(1);
         }
      fprintf(tempfile,"%ld,%d\n",VNIR,commentcount);
      fclose(tempfile);
      }
   if (remove_pre && DEBUG==FALSE) {
      if (NULL==strstr(infile_orig,".vpl")) {
         fprintf(fpstatus,"removing [%s]\n",infile_orig);
         if (0!=remove(infile_orig)) perror ("Error removing .proc file"); 
         if (CPM==2) {
            sprintf(tempstr,"DPM_%s",infile_orig);
            if (0!=remove(tempstr)) perror ("Error removing DPM_*.proc file");
            }
         }
      else {
         fprintf(fpstatus,"File [%s] contains .vpl, not removing!!!\n",infile_orig);
         }
      }
   }
return(0);
}

/***************************************************************************************/
/***************************************************************************************/
/** WARNING: The code in this rountine for repeat compression is quite complicated.   **/
/**          This routine buffers results from one call to the next.                  **/
/**          Any modifications to this code can result in broken output.              **/
/**          Do not modify this section without fully testing the modifications       **/
/**          thoroughly. Debugging lines are left in the code to help verify the      **/
/**          correct operation, change the value of DEBUG to enable these prints.nedit      **/
/***************************************************************************************/
/***************************************************************************************/
int outputvector(FILE *fpout1,char *out_vector,char *wft,char *DMI,long repeatcount,char *comment,
                 char *microinstr,int CPM){
char tempstr[MULTILINESIZE+1],tempstr2[MULTILINESIZE+1],commentstr[MULTILINESIZE+1];
static char vector_hold[READLINELEN+1],wft_hold[MAXGCTLEN+1];
static char printhold[MULTILINESIZEBIG+1];
static long repeat_counter,line_cnt=0;
static long VMR=0,VRE=0;
boolean vector_matches_prev,vector_is_vector,vector_is_new;
boolean vector_is_microinstr,vector_is_label,is_last_vector,wft_is_empty,vector_is_empty;
int max_repeat,printholdlen;

if (line_cnt==0){
   printhold[0]='\0';
   printholdlen=0;
   commentstr[0]='\0';
   strcpy(vector_hold,NO_VECTOR);
   strcpy(wft_hold,NO_WFT);
   repeat_counter=0;
   }
wft_is_empty =          ( 0 == strcmp(wft,NO_WFT) );
vector_is_empty =       ( 0 == strcmp(out_vector,NO_VECTOR) );
is_last_vector =        ( repeatcount==VECTOR_DONE );
vector_is_microinstr=( out_vector[0] == HOLD_CHAR && (0==strcmp(wft,DEF_WFT)||wft_is_empty) );
vector_is_label=     ( out_vector[0] == '$' );
vector_is_vector=    ( !vector_is_label &&
                       !vector_is_microinstr &&
                       !wft_is_empty &&
                       !vector_is_empty );
vector_matches_prev= ( vector_is_vector &&
                       0 == strcmp(out_vector,vector_hold) &&
                       0 == strcmp(wft,wft_hold) );
vector_is_new=       ( (vector_is_vector &&
                       !vector_matches_prev ) ||
                       !REPEAT_COMPRESSION);
max_repeat=          ((CPM==0)?MAX_RPT_DPM:MAX_RPT_CPM);
if (DEBUG) fprintf(fpstatus,"===========================================================\n");
if (DEBUG) fprintf(fpstatus,"OAV[%s]<%s>{%s}\n",out_vector,microinstr,wft);
if (DEBUG) fprintf(fpstatus,"WE=%d,VE=%d,ILV=%d,VIM=%d,VIL=%d,VIV=%d,VMP=%d,VIN=%d\n",
               wft_is_empty,vector_is_empty,is_last_vector,
               vector_is_microinstr,vector_is_label,vector_is_vector,vector_matches_prev,
               vector_is_new);
if (is_last_vector ) {/* this is to correctly deal with the end label */
   if (!CPM) {
      if (repeat_counter>1 ) {
         while (repeat_counter>max_repeat){
           fprintf(fpout1,"%s <RPT %d>\n",printhold,max_repeat);/* it is wrong to have "VNIR+=max_repeat;" here!!! */
            VC++;
            repeat_counter -= max_repeat;
            VRE++;
            }
         fprintf(fpout1,"%s\n",out_vector); /* output the end label */
         fprintf(fpout1,"%s <RPT %ld>\"VNIR0=%ld\"\n",printhold,repeat_counter,VNIR);/* it is wrong to have "VNIR+=max_repeat;" here!!! */
         VC++;
         }
      else {
         fprintf(fpout1,"%s\n",out_vector);
         if (commentstr[0]=='\0'|| SUPPRESS_COMMENTS) {fprintf(fpout1,"%s\"VNIR1=%ld\"\n",printhold,VNIR); VC++;}  /* if there isn't a comment don't print one */
         else                                         {fprintf(fpout1,"%s \"VNIR2=%ld%s\"\n",printhold,VNIR,commentstr);VC++;}
         }
      }
/* If CPM then we need to spit out the last vector BEFORE the end label because we add the RET and RPT 512 */
   if (CPM) {
      if (repeat_counter>1 ) {
         while (repeat_counter>max_repeat){
            fprintf(fpout1,"%s <RPT %d>\n",printhold,max_repeat);/* it is wrong to have "VNIR+=max_repeat;" here!!! */
            VC++;
            repeat_counter -= max_repeat;
            VRE++;
            }
         fprintf(fpout1,"%s <RPT %ld>\n ",printhold,repeat_counter);/* it is wrong to have "VNIR+=max_repeat;" here!!! */
         VC++;
         }
      else {
         if (commentstr[0]=='\0'|| SUPPRESS_COMMENTS) {fprintf(fpout1,"%s\n",printhold);VC++;}   /* if there isn't a comment don't print one */
         else                                         {fprintf(fpout1,"%s \"%s\"\n",printhold,commentstr);VC++;}
         }
      fprintf(fpout1,"%s\n",out_vector); /* output the end label */
      if (addpad==0){
         fprintf(fpout1,"* %s * %s %s;<RET>\n",dummy_vector,DEF_WFT,NORMALSGHDR); /* output the end label */
/*         fprintf(fpout1,"* %s * %s %s;<RPT 512>\n",dummy_vector,DEF_WFT,NORMALSGHDR); */ /* output the end label */
         VC+=1;
         }
      else {
         fprintf(fpout1,"* %s %c%c* %s %s;<RET>\n",dummy_vector,PADCHAR,PADCHARNOT,DEF_WFT,PADSGHDR); /* output the end label */
/*         fprintf(fpout1,"* %s %c%c* %s %s;<RPT 512>\n",dummy_vector,PADCHAR,PADCHARNOT,DEF_WFT,PADSGHDR); */ /* output the end label */
         VC+=1;
         }
      }
   if (VNIR<64 || VC<16) {
      fprintf(fperrors,"NON_fatal_error:%s:File [%s] does not have enough vectors[%ld]/cycles[%ld], padding with hold cycles\n",progstr,infile_orig,VC,VNIR);
      fprintf(stderr,"NON_fatal_error:%s:File [%s] does not have enough vectors[%ld]/cycles[%ld], padding with hold cycles\n",progstr,infile_orig,VC,VNIR);
      for(VC=VC;VC<16;VC++,VNIR++) fprintf(fpout1,"* %s * %s %s;\"pad vector VNIR3=%ld\"\n",dummy_vector,wft_hold,NORMALSGHDR,VNIR);
      if (VNIR<64) {
         fprintf(fpout1,"* %s * %s %s;<RPT %ld>\"pad vector VNIR4=%ld\"\n",dummy_vector,wft_hold,NORMALSGHDR,64-VNIR,VNIR);
         VNIR += (64-(VNIR+(16-VC)));
         }
      }
   fprintf(fpout1,"\"VNIR5=%ld\"\n}\n",VNIR); /* output the end label */
   fprintf(stderr,"\n%ld lines printed\n",line_cnt);
   fprintf(stderr,"%ld %s vectors successfully processed.\n",VN,(CPM)?"CPM":"DPM");
   fprintf(stderr,"Total cycle count:%ld Total Vector count:%ld\n",VNIR,VC);
   fprintf(stderr,"vector count reduced by %ld with repeat compression.\n",VMR);
   fprintf(stderr,"vector count increased by %ld due to repeat expansion.\n",VRE);
   return(0);
   } /* end of vector is last! */
if ((vector_is_new||vector_is_label||vector_is_microinstr) && printhold[0]!=0){
   if (DEBUG) fprintf(fpstatus,"OV[%s]<%s>\n",out_vector,microinstr);
   if (DEBUG) fprintf(fpstatus,"~R_C:%ldRC:%ld,H:%s\n",repeat_counter,repeatcount,printhold);
      if (repeat_counter>1 ) {
         if (DEBUG) fprintf(fpstatus,"#R_C:%ldRC:%ld,H:%s\n",repeat_counter,repeatcount,printhold);
         strcpy(tempstr2,printhold);
         printhold[0]='\0';
         printholdlen=0;
         while (repeat_counter>max_repeat){
         if ((repeatcount % 2500)==0) fprintf(fpstatus,"[%ld]MAX REPEAT %d reached...continuing\n",countrpts,max_repeat);
         countrpts++;
         if (DEBUG) fprintf(fpstatus,"$R_C:%ldRC:%ld,H:%s\n",repeat_counter,repeatcount,printhold);
            sprintf(tempstr,"%s <RPT %d>\n",tempstr2,max_repeat);
            if (printholdlen+strlen(tempstr)>MULTILINESIZEBIG) {
               VC++;fprintf(fpout1,"%s\n",printhold);printhold[0]='\0';
               fprintf(stderr,"EXCEEDING BUFFERSIZE at %d ... emptying buffer\n",__LINE__);
               fprintf(fperrors,"EXCEEDING BUFFERSIZE at %d ...emptying buffer\n",__LINE__);
               }
            strcat(printhold,tempstr);
            printholdlen+=strlen(tempstr);            
            repeat_counter -= max_repeat;
            VRE++;
            }
         sprintf(tempstr,"%s <RPT %ld> ",tempstr2,repeat_counter);
         if (printholdlen+strlen(tempstr)>MULTILINESIZEBIG) {
            VC++;fprintf(fpout1,"%s\n",printhold);printhold[0]='\0';
            fprintf(stderr,"EXCEEDING BUFFERSIZE at %d ... emptying buffer\n",__LINE__);
            fprintf(fperrors,"EXCEEDING BUFFERSIZE at %d ...emptying buffer\n",__LINE__);
            }
         strcat(printhold,tempstr);
         printholdlen+=strlen(tempstr);            
         if (DEBUG) fprintf(fpstatus,"^R_C:%ldRC:%ld,H:%s\n",repeat_counter,repeatcount,printhold);
         }
   if (commentstr[0]=='\0'|| SUPPRESS_COMMENTS) {VC++;fprintf(fpout1,"%s\n",printhold);}   /* if there isn't a comment don't print one */
   else                                         {VC++;fprintf(fpout1,"%s \"VNIR7=%ld %s\"\n",printhold,VNIR,commentstr);}
   commentstr[0]='\0';
   printhold[0]='\0';
   printholdlen=0;
   repeat_counter=0;
   }
if (DEBUG) fprintf(fpstatus,"!R_C:%ldRC:%ld,H:%s\n",repeat_counter,repeatcount,printhold);
if ( vector_is_vector ) {
   repeat_counter += repeatcount;
   if (DEBUG) fprintf(fpstatus,"@R_C:%ldRC:%ld,H:%s\n",repeat_counter,repeatcount,printhold);
   if ( vector_matches_prev && REPEAT_COMPRESSION)  { 
      /* looks like we can compress the vector */
      VMR++;
      }
   else {
      if (addpad==0) sprintf(printhold,"* %s* %s %s;",out_vector,wft,NORMALSGHDR);
      else           sprintf(printhold,"* %s%c%c* %s %s;",out_vector,PADCHAR,PADCHARNOT,wft,PADSGHDR);
      }
   printholdlen=strlen(printhold);
   VN++;
   VNIR++;
   strcpy(vector_hold,out_vector);/* keep for check repeat compression */
   strcpy(wft_hold,wft);
   }

else if (vector_is_label) { 
   sprintf(tempstr,"%s",out_vector);
   strcpy(printhold,tempstr);
   printholdlen=strlen(printhold);
   strcpy(vector_hold,NO_VECTOR); /* keep for check repeat compression */
   strcpy(wft_hold,NO_WFT);
   }
else if (vector_is_microinstr) { 
   /* we should really try to put something here to combine the microinstruction onto the previous vector */
   if (DEBUG) fprintf(fpstatus,"&R_C:%ldRC:%ld,H:%s\n",repeat_counter,repeatcount,printhold);
   if (addpad==0) sprintf(tempstr,"* %s* %s %s; %s",out_vector,DEF_WFT,NORMALSGHDR,microinstr);
   else           sprintf(tempstr,"* %s%c%c* %s %s; %s",out_vector,PADCHAR,PADCHARNOT,DEF_WFT,PADSGHDR,microinstr);
   strcpy(printhold,tempstr);
   printholdlen=strlen(printhold);
   strcpy(vector_hold,out_vector); /* keep for check repeat compression */
   strcpy(wft_hold,DEF_WFT);
   }
if (0!=strcmp(DMI,NO_DMI)){
   if (strlen(DMI)+strlen(commentstr)<MULTILINESIZE) strcat(commentstr,DMI);/* keep as much as possible */
   strcpy(DMI,NO_DMI);
   }
if (0!=strcmp(comment,NO_COMMENT)) {/* there's a comment ... */
   if (strlen(comment)+strlen(commentstr)<MULTILINESIZE) strcat(commentstr,comment);/* keep as much as possible */
   comment[0]='\0'; /* strcpy(comment,NO_COMMENT); */
   }
line_cnt++;
if (DEBUG) fflush(fpout1);/* this helps to get as much info out to the file before a crash */
if (DEBUG) fprintf(fpstatus,"=R_C:%ldRC:%ld,H:%s\n",repeat_counter,repeatcount,printhold);
repeatcount=1;
return(repeatcount);
}

/***************************************************************************************/

#define RET_FOREVER -1   
char * get_count(char *ptr,int offset,long *count,int call){
char *retptr;

*count=0;
retptr=ptr+offset;
while (!isdigit((int)*retptr) && *retptr!=0) retptr++;
while(isdigit((int)*retptr)){
   *count=*count*10+(*retptr-'0');
   retptr++;
   }
if (*count==0){/* check for 'forever' */
   if (NULL!=strstr(ptr,"forever")) *count=RET_FOREVER;
   }
return(retptr);
}

/***************************************************************************************/

int deal_with_shutdown(char *line,char *ptr,FILE *fpin1){
int beginflag=2,counter=0;
char vector[READLINELEN+1],mod_vector[READLINELEN+1],outvector1[READLINELEN+1];
char DMI[15];
if ((ptr-line)<=7) {/* Shutdown SUBROUTINE */
if (DEBUG+TRUE) fprintf(fpstatus,"INSIDE Shutdown:%s\n",line);
fgets(vector,READLINELEN-1,fpin1);
readlinenum++;
if (NULL!=(ptr=strstr(vector,"begin"))) {
    fprintf(stderr,"\nFYI:%s,%s:Shutdown vectors available in %s\n\n",compilestr,infile_orig,transl_err_file);
    if (DEBUG) fprintf(fpstatus,"Throwing out Shutdown:%s",vector);
    while(fgets(vector,READLINELEN-1,fpin1) != NULL ){
       readlinenum++;
       counter++;
       if (DEBUG) fprintf(fpstatus,"Throwing out Shutdown:%s",vector);
       if (NULL!=(ptr=strstr(vector,"end"))) break;
       strcpy(mod_vector,vector);
       vector_convert(&beginflag,vector,mod_vector,&SETS,outvector1,DMI);
       if (outvector1[0]!='\0') fprintf(fperrors,"FYI:%s,%s:SHUTDOWN%d:[%s]\n",compilestr,infile_orig,counter,outvector1);
       }/* end while */
    }/* end if begin */
}/* end ptr<7 */
return(0);
}

/***************************************************************************************/

int deal_with_comment(FILE *fpout1,char *mod_vector,char *comment,int *commentcount,int *commentflag,int *commentON,int vectorflag){
int i,vl,j,commentstart=-1,commentend=0;
/* seek until comment end*/
vl=strlen(mod_vector);
for (i=0;i<=vl;i++) {
   if      (mod_vector[i]=='{' && commentstart==-1 ) {(*commentcount)++;commentstart=i;}
   else if (mod_vector[i]=='{' && commentstart!=-1 ) {(*commentcount)++;}
   if (mod_vector[i]=='}' ) {(*commentcount)--;commentend=i;}
   }

if (*commentcount==0) {/* we can close the comment. there will be no pending comments */
   *commentflag=1;
   if (commentend!=-1) mod_vector[commentend]='\0';/* temporarily mark the final comment close with an end later we will restore it to space */
   if (commentstart!=-1) mod_vector[commentstart]=' ';
   else commentstart=0;/* set the comment to start at the beginning if there was not comment open */
   i=0;
   while (mod_vector[commentstart]==' ' && i<3) {commentstart++;i++;}/* remove leading space accounting for comment markers */
   *commentON=0;
   if ((commentend-commentstart)+strlen(comment)>MULTILINESIZE) {
      if (1) fprintf(fpstatus,"BIG COMMENT <%s>\n",comment);
      if (0)fprintf(fpstatus,"found BIG COMMENT\n");
      comment[0]='\0';/* wipe out anything we had here */
      }
   strcat(comment,&mod_vector[commentstart]);
   if (vectorflag==0) {
      fprintf(fpout1,"//%s\n",comment);
      comment[0]='\0';
      }
   /* the idea here is to blank the line out where the comment was */
   for (j=commentstart;j<=commentend;j++) mod_vector[j]=' ';/* this actually writes over the \0 we wrote above */
   }
else {/* the comment needs to remain open */
   *commentON=1;
   mod_vector[commentstart]=' ';
   if ((vl-commentstart)+strlen(comment)>MULTILINESIZE) {
      if(1)fprintf(fpstatus,"BIG COMMENT <%s>\n",comment);
      if(0)fprintf(fpstatus,"found BIG COMMENT\n");
      comment[0]='\0';
      }
   strcat(comment,&mod_vector[commentstart]);
   for (j=commentstart;j<=vl;j++) mod_vector[j]=' ';/* this actually writes over the \0 we wrote above */
   }
return(0);
}

/***************************************************************************************/

int check_SET(int beginflag,char *mod_vector,const char *SET,int *notgood,int MAX,char SETPTR[]){
long t1,t2;
char *ptr;
if (beginflag>=1 && NULL!=(ptr=strstr(mod_vector,SET))) {
  t1=0;
  ptr=strchr(mod_vector,'[');
  if (ptr==NULL){
     fprintf(stderr,"%s BAD_ERROR: [%s]",SET,mod_vector);
     fprintf(fperrors,"BAD_ERROR:%s:%s [%s]file[%s]line:%ld\n",progstr,SET,mod_vector,infile_orig,readlinenum);
     *notgood=1;
     return (1);
     }
  else {
     *ptr='%';
     ptr=get_count(ptr,1,&t1,2);
     if (t1>MAX) {
        fprintf(stderr,"Exceeded MAX%s\n...exiting\n",SET);
        fprintf(fpstatus,"Exceeded MAX%s...exiting.file[%s]line:%ld\n",SET,infile_orig,readlinenum);
        *notgood=1;
        return(1);
        }
     if (0) fprintf(stderr,"In %s [%ld]\n",SET,t1);
     ptr=strchr(mod_vector,'[');
     if (ptr==NULL) return(1);
     ptr++;
     t2=0;
     while (*ptr!=']'){
        SETPTR[t1*VECTORLEN+t2]=*ptr-'0';
        ptr++;
        t2++;
        }
     return(2);         
     }
  }
return(0);
}

/***************************************************************************************/

int vector_convert(int *beginflag,char *vector,char *mod_vector,struct SETvS *SETS,char *out_vector1,char *DMI){
char *ptr;
long mset,dset,iset;
int vectb,vecte,vect,vmset,vdset,viset,j,VMS,AC,SET,GCTMATCHMOD,outpos,pinnum,i,verrorflag;
int dset0val,dset1val;
/* real vector */
j=0; *beginflag=2;
ptr=mod_vector;
while (0!=isspace((int)*ptr))ptr++;
while (0==isspace((int)*ptr) && *ptr!='('   ) SETS->WFT[j++]=*(ptr++);
SETS->WFT[j]='\0';
GCTMATCHMOD=0;
SET=-1;
for (SET=0;SET<SETS->maxgctDSET;SET++) if (0==strcmp(SETS->WFT,SETS->GCTMODNAME[SET])){ GCTMATCHMOD=1;break;}
if (GCTMATCHMOD==0) {
   fprintf(fperrors,"MOSTLY-FATAL:GCTSET NOT FOUND[%s] in mod file [%s],vectors will be don't care\n",infile_orig,SETS->WFT);
   fprintf(stderr,"MOSTLY-FATAL:GCTSET NOT FOUND[%s] in mod file [%s],vectors will be don't care\n",infile_orig,SETS->WFT);
   }
ptr=strchr(mod_vector,'(');
if (ptr==NULL) return(1);
iset=0;
/* MSET */
ptr=get_count(ptr,1,&mset,5);
/* DSET */
ptr=get_count(ptr,1,&dset,6);
/* ISET */
ptr=get_count(ptr,1,&iset,7);
ptr=strchr(mod_vector,'[');
if (ptr==NULL) return(1);
vectb=(ptr-mod_vector)+1;
ptr=strchr(mod_vector,']');
if (ptr==NULL) return(1);
vecte=(ptr-mod_vector);
if (DEBUG) fprintf(fpstatus,"In vector,WFT=[%s],M=%ld,D=%ld,I=%ld,b=%d,e=%d,l=%d\n",SETS->WFT,mset,dset,iset,vectb,vecte,vecte-vectb);
outpos=0;
pinnum=0;
verrorflag=0;
sprintf(DMI,"(%ld,%ld,%ld)",mset,dset,iset);
if ((vecte-vectb)!=MOD2_SIZE) {
   fprintf(stderr,"FATAL_ERROR: Number of pins<%d> in pattern <%s> does not match pins in cycletbl definition file<%d> approxline: %ld\n",vecte-vectb,infile_orig,MOD2_SIZE,readlinenum);
   fprintf(fperrors,"FATAL_ERROR:%s: Number of pins<%d> in pattern <%s> does not match pins in cycletbl definition file<%d> approxline: %ld\n",progstr,vecte-vectb,infile_orig,MOD2_SIZE,readlinenum);
   exit(9);
   }
for (i=vectb;i<vecte;i++){
   vect=mod_vector[i]-'0';
   vmset=SETS->MSETPTR[mset*VECTORLEN+pinnum];
   vdset=SETS->DSETPTR[dset*VECTORLEN+pinnum];
   viset=SETS->ISETPTR[iset*VECTORLEN+pinnum];
   if (viset==1) vect=1-vect;/* invert the data state if ISET=1 */
   VMS=SETS->VECTMOD[SET][pinnum]-' ';
   dset1val=VMS/10;
   dset0val=VMS-dset1val*10;
   dset1val++;dset0val++;
/*DSET0 DSET1
l/h    *L/H drive             0x02
X/.*   x/, driveoffcompareoff 0x09 9=8+1
z/Z    y/Y driveoff only      0x01    
e/E*   k/K EndWindow          0x08
0/1*   o/i EdgeStrobe         0x03
w/W*   v/V WindowStrobe       0x04
f/F*   g/G FloatStrobe        0x05
u/U*   u/U FloatWindow        0x06
-          Continue           0x07
d          CPM/DPM
s/D        scan out/in
*/
   if (vdset==0) {
      switch(dset0val+(vmset==1)*0x010) {
         case 0x02:AC=(vect==0)?'l':'h';break;/* drive */
         case 0x09:AC=(vect==0)?'X':'.';break;/* driveoffcompareoff */
         case 0x01:AC=(vect==0)?'z':'Z';break;/* driveoff only */
         case 0x08:AC=(vect==0)?'e':'E';break;/* EndWindow */
         case 0x03:AC=(vect==0)?'0':'1';break;/* EdgeStrobe */
         case 0x04:AC=(vect==0)?'w':'W';break;/* WindowStrobe */
         case 0x05:AC=(vect==0)?'f':'F';break;/* FloatStrobe */
         case 0x06:AC=(vect==0)?'u':'U';break;/* FloatWindow */
         case 0x07:AC=(vect==0)?'-':'-';break;/* Continue */
/* MASK: */
         case 0x12:AC=(vect==0)?'l':'h';break;/* drive */
         case 0x19:AC=(vect==0)?'X':'.';break;/* driveoffcompareoff */
         case 0x11:AC=(vect==0)?'X':'.';break;/* driveoff only */
         case 0x18:AC=(vect==0)?'X':'.';break;/* EndWindow */
         case 0x13:AC=(vect==0)?'X':'.';break;/* EdgeStrobe */
         case 0x14:AC=(vect==0)?'X':'.';break;/* WindowStrobe */
         case 0x15:AC=(vect==0)?'X':'.';break;/* FloatStrobe */
         case 0x16:AC=(vect==0)?'.':'.';break;/* FloatWindow */
         case 0x17:AC=(vect==0)?'-':'-';break;/* Continue */
         }
      }
   else {/* DSET1 */
      switch(dset1val+(vmset==1)*0x010) {
         case 0x02:AC=(vect==0)?'L':'H';break;/* drive */
         case 0x09:AC=(vect==0)?'x':',';break;/* driveoffcompareoff */
         case 0x01:AC=(vect==0)?'y':'Y';break;/* driveoff only */
         case 0x08:AC=(vect==0)?'k':'K';break;/* EndWindow */
         case 0x03:AC=(vect==0)?'o':'i';break;/* EdgeStrobe */
         case 0x04:AC=(vect==0)?'v':'V';break;/* WindowStrobe */
         case 0x05:AC=(vect==0)?'g':'G';break;/* FloatStrobe */
         case 0x06:AC=(vect==0)?'t':'T';break;/* FloatWindow */
         case 0x07:AC=(vect==0)?'-':'-';break;/* Continue */
/* MASK: */
         case 0x12:AC=(vect==0)?'L':'H';break;/* drive */
         case 0x19:AC=(vect==0)?'X':'.';break;/* driveoffcompareoff */
         case 0x11:AC=(vect==0)?'X':'.';break;/* driveoff only */
         case 0x18:AC=(vect==0)?'X':'.';break;/* EndWindow */
         case 0x13:AC=(vect==0)?'X':'.';break;/* EdgeStrobe */
         case 0x14:AC=(vect==0)?'X':'.';break;/* WindowStrobe */
         case 0x15:AC=(vect==0)?'X':'.';break;/* FloatStrobe */
         case 0x16:AC=(vect==0)?'X':'.';break;/* FloatWindow */
         case 0x17:AC=(vect==0)?'-':'-';break;/* Continue */
         }
      }   
   out_vector1[outpos]=AC;
   outpos++; pinnum++;
   }
if ( verrorflag == 1) fprintf(stderr,"NON_FATAL_ERROR:Error in vector [%s]\n",vector);
if ( verrorflag == 1 && 1) fprintf(fperrors,"NON_FATAL_ERROR:%s:Error in vector [%s]file[%s]line:%ld\n",progstr,vector,infile_orig,readlinenum);
out_vector1[outpos] = '\0';
if (DEBUG) fprintf(fpstatus,"^%s\n",out_vector1);
return (verrorflag);
}

int cpmoptimize (char *pattern){
FILE *fpin,*fpout,*fpoutdpm;
char outfile1[READLINELEN+1],outfiledpm[READLINELEN+1],infile1[READLINELEN+1];
char vector[MAXCPMOPTLINES][READLINELEN+1],header[MAXCPMOPTLINES][READLINELEN+1];
char cpmvector1[READLINELEN+1],cpmvector2[READLINELEN+1],cpmvector3[READLINELEN+1];
char cpmwft1[READLINELEN+1],cpmwft2[READLINELEN+1],cpmsh1[READLINELEN+1],cpmsh2[READLINELEN+1];
char comment[MAXCPMOPTLINES][READLINELEN+1];
char uinstr[MAXCPMOPTLINES][FILENAMELEN+1];
char wft[MAXCPMOPTLINES][MAXGCTLEN],sh[MAXCPMOPTLINES][MAXGCTLEN];
char lbltbl[MAXCPMOPTLINES][FILENAMELEN+1],tmpstr[FILENAMELEN+1];
char readstr[READLINELEN+1],prog[READLINELEN+1],*ptr,new_wft[MAXGCTLEN];
char optpreprocrev[READLINELEN+1];
int lbl_tbl[MAXCPMOPTLINES];
int curptr=0,maxlbls=0,maxlines=0,hdrcnt=0,rev=0;
int got_uinstr=0,using_dpm=0,dpmcount=0,cpmrptlda=64;
int ustart,uend,vstart,vend,lstart,lend,cstart,cend,printedDPMBUFF=0;
int i,j,k,tmp1,tmp2,ded,nzckeep;
char CNTRSTR[25],tmplblstr[50];
strcpy(prog,progstr);
rev=prog[strlen(prog)-1-2];
prog[strlen(prog)-1-2]='\0';
fprintf(stderr,"entering optimization routine\n");
sprintf(outfile1,"_%s.evo",pattern);
if (NULL==(fpout=fopen(outfile1,"w"))) {
   fprintf(stderr,"\nFATAL_ERROR:Could not open output file [_%s] for output(opt)\n",outfile1);
   fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open output file [_%s] for output(opt)\n",progstr,outfile1);
   exit(1);
   }
sprintf(outfiledpm,"DPMO_%s.evo",pattern);
if (NULL==(fpoutdpm=fopen(outfiledpm,"w"))) {
   fprintf(stderr,"\nFATAL_ERROR:Could not open output file [_%s] for output(opt)\n",outfiledpm);
   fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open output file [_%s] for output(opt)\n",progstr,outfiledpm);
   exit(1);
   }
sprintf(infile1,"%s.evo",pattern);
if (NULL==(fpin=fopen(infile1,"r"))) {
   fprintf(stderr,"\nFATAL_ERROR:Could not open input file [%s] for input(opt)\n",infile1);
   fprintf(fperrors,"\nFATAL_ERROR:%s:Could not open input file [%s] for input(opt)\n",progstr,infile1);
   exit(1);
   }
optpreprocrev[0]='\0';
lstart=0;
while(fgets(readstr,READLINELEN-1,fpin) != NULL ){/* ~A*/
   if (readstr[0]=='\"' && readstr[1]=='+' && lstart==0) {/* this is for the pinheader */
      continue;
      }
   if (NULL!=strstr(readstr,"{-FLAG-preprocess")) {
      strcpy(optpreprocrev,readstr);
      continue;
      }
   if (strlen(readstr)>=READLINELEN-2) {
       fprintf(fpstatus,"LONG LINE [%s]\n",readstr);
       /* if we have a long line it must be due to a comment so 'trash' the extra data here */
       while (fgets(cpmvector3,READLINELEN-1,fpin) != NULL) if (strlen(cpmvector3)<=(READLINELEN-2)) break; else fprintf(fpstatus,"LONG LINE [%s]\n",cpmvector3);
       readstr[READLINELEN-2]='\"';
       }
   readstr[strlen(readstr)-1] = '\0';/* remove trailing \n */
   if (DEBUG) fprintf(fpstatus,"[%s]\n",readstr);
   if (readstr[0]=='$') {
      lstart=1;
      lend=strlen(readstr);
      for (j=0,i=lstart;i<=lend;j++,i++) lbltbl[maxlbls][j]=readstr[i];
      lbltbl[maxlbls][j]='\0';
      lbl_tbl[maxlbls]=maxlines;
      maxlbls++;
      if (maxlbls>=MAXCPMOPTLINES) { 
         fprintf(stderr,"NON_FATAL_ERROR:CPM pattern [%s.evo] is too big to optimize(lbl)\n",pattern);
         fprintf(fperrors,"NON_FATAL_ERROR:%s:cpm pattern [%s.evo] is too big to optimize(lbl)\n",progstr,pattern);
         fprintf(fpstatus,"FYI:removing _%s.evo and DPMO_%s.evo\n",pattern,pattern);
         sprintf(readstr,"_%s.evo",pattern);
         if (0!=remove(readstr)) perror ("Error removing _file");
         sprintf(readstr,"DPMO_%s.evo",pattern);
         if (0!=remove(readstr)) perror ("Error removing DPMO_ file"); 
         return(-1);
         }
      }
   else if (NULL!=(ptr=strchr(readstr,'*'))){/* ~D */
      vstart=(int)(ptr-&readstr[0])+1;
      vend=(int)(strchr(&readstr[vstart],'*')-&readstr[0])-1;
      for (j=0,i=vstart;i<=vend;j++,i++) vector[maxlines][j]=readstr[i];
      vector[maxlines][j]='\0';
      tmp1=vend+2;
      j=0;
      while (readstr[tmp1]==' ') tmp1++;
      while (readstr[tmp1]!=' ') wft[maxlines][j++]=readstr[tmp1++];
      wft[maxlines][j]='\0';
      j=0;
      while (readstr[tmp1]==' ') tmp1++;
      while (readstr[tmp1]!=';') sh[maxlines][j++]=readstr[tmp1++];
      sh[maxlines][j]='\0';
      uinstr[maxlines][0]='\0';
      if (NULL!=(ptr=strchr(readstr,'<'))){
         if ( NULL!=strstr(readstr,"LDA")  || NULL!=strstr(readstr,"CJMP") || NULL!=strstr(readstr,"COND") || 
              NULL!=strstr(readstr,"FLAG") || NULL!=strstr(readstr,"LC") ) got_uinstr=1;
         ustart=(int)(ptr-&readstr[0])+1;
         uend=(int)(strchr(readstr,'>')-&readstr[0])-1;
         for (j=0,i=ustart;i<=uend;j++,i++) uinstr[maxlines][j]=readstr[i];
         uinstr[maxlines][j]='\0';
         }
      comment[maxlines][0]='\0';
      if (NULL!=(ptr=strchr(readstr,'"'))){
         cstart=(int)(ptr-&readstr[0])+1;
         cend=(int)(strchr(ptr+1,'"')-&readstr[0])-1;
         /* added check here in case we truncated the comment due to exceeding the buffer size */         
         for (j=0,i=cstart;i<=cend && i<strlen(readstr);j++,i++) comment[maxlines][j]=readstr[i];
         comment[maxlines][j]='\0';
         }
      maxlines++;
      if (maxlines>=MAXCPMOPTLINES && dpmcount==0) {
         fprintf(stderr,"NON_FATAL_ERROR:CPM pattern [%s.evo] is too big to optimize\n",pattern);
         fprintf(fperrors,"NON_FATAL_ERROR:%s:cpm pattern [%s.evo] is too big to optimize\n",progstr,pattern);
         fprintf(fpstatus,"FYI: removing _%s.evo and DPMO_%s.evo\n",pattern,pattern);
         sprintf(readstr,"_%s.evo",pattern);
         if (0!=remove(readstr)) perror("Error removing _file (too big)");
         sprintf(readstr,"DPMO_%s.evo",pattern);
         if (0!=remove(readstr)) perror("Error removing DPMO_ file (too big)");
         return(-1);
         }
      if (maxlines>=MAXCPMTODPMLINES) { /* ~G */
         if (got_uinstr){ /* ~H */
            /* we have hit a non-dpm microinstruction so we can do any more in dpm*/
            } /* ~H~ */
         else { /* only repeats */ /* ~I */
            if (!printedDPMBUFF) {
               fprintf(fpstatus,"FYI:part of CPM pattern [%s.evo] can be buffered to DPM\n",pattern);
               if(DEBUG)fprintf(fperrors,"FYI:%s:part of CPM pattern [%s.evo] can be buffered to DPM\n",progstr,pattern);
               /* fprintf(fpstatus,"we can probably put all these lines in DPM...\n"); */
               printedDPMBUFF=1;
               }
            if(using_dpm==0){ /* only print header on first loop */
               fprintf(fpoutdpm,"enVisionObject:\"bl8:R5.7\";\n\n");
               fprintf(fpoutdpm,"Pattern DPMO_%s {\n",pattern);
               fprintf(fpoutdpm,"    Type Dpm;\n");
               fprintf(fpoutdpm,"\" Pattern convertor: %s:%s by Anthony Sully compile_date:%s@%s\"\n",compilestr,progstr,datestr,timestr);
               fprintf(fpoutdpm,"\"      Pattern converted on:%s by:%s on host:%s \"\n\"      in pwd: %s\"\n",mydate,username,hostname,pwd);
               fprintf(fpoutdpm,"$DPMO_%s_st\n",pattern);
               for (i=0;i<pinheadcount;i++) fprintf(fpoutdpm,"\" %s\"\n",&pinhead[i][2]);
               }
            for(i=0;i<maxlines;i++){ /* ~K */
               if (dpmcount==0) {/* first vectors of dpm can be used in cpm for LDA and RPT 64 */ /* ~L */
                  strcpy(cpmvector1,vector[0]);/* preserve the first dpm for the LDA/RPT 64 in cpm */
                  strcpy(cpmwft1,wft[0]);
                  strcpy(cpmsh1,sh[0]);
                  strcpy(cpmvector2,vector[0]); /* second cpm must be hold */
                  for (j=0;j<strlen(cpmvector2);j++) if(cpmvector2[j]!=' ') cpmvector2[j]=HOLD_CHAR;
                  strcpy(cpmwft2,wft[0]); strcpy(cpmsh2,sh[0]);
                  if (uinstr[0][0]!='\0') { /* there is a repeat on the first vector */ 
                     fprintf(fpstatus,"RPT on first vector[%s]\n",uinstr[0]);
                     j=atoi(uinstr[0]+strlen("RPT "));
                     if (j>64) {/* Steal the first DPM for the first two cpm vectors */
                        strcpy(cpmvector2,vector[0]); /* make second cpm vector the rest of the RPT of dpm vector 1 */
                        strcpy(cpmwft2,wft[0]); strcpy(cpmsh2,wft[0]);
                        cpmrptlda=j-1; dpmcount+=0;
                        i++;
                        }
                     else if (j>2) {/* Steal part of the first DPM for the first cpm */
                        dpmcount+=0;
                        sprintf(uinstr[0],"RPT %d",j-1);
                        }
                     else { /* must be RPT 2 */
                        uinstr[0][0]='\0'; /* remove the RPT 2 microinstruction */
                        }
                     } /* there is a repeat on the first vector */ 
                  else { /* no repeat on first was dpm now cpm vector; check second vector */
                     fprintf(fpstatus,"no RPT on first vector\n");
                     i++;
                     if (uinstr[1]!='\0') {
                        j=atoi(uinstr[1]+strlen("RPT "));
                        if (j>63) {
                           strcpy(cpmvector2,vector[i]); /* make second cpm vector the rest of the RPT of dpm vector 1 */
                           strcpy(cpmwft2,wft[i]); strcpy(cpmsh2,sh[i]);
                           cpmrptlda=j; dpmcount+=0;
                           i++;
                           }
                        else {/* Steal part of the first DPM for the first cpm */
                           }
                        }
                     }
                  }
               fprintf(fpoutdpm,"*%s * %s %s;",vector[i],wft[i],sh[i]);
               if ( uinstr[i][0]!='\0') {
                  /* hopefully only RPT */
                  j=atoi(uinstr[i]+strlen("RPT "))-1;
                  dpmcount+=j;
                  fprintf(fpoutdpm,"<%s>",uinstr[i]);
                  uinstr[i][0]='\0';
                  }
               if (comment[i][0]!='\0') { /* ~V */
                  fprintf(fpoutdpm,"\"%s\"",comment[i]);
                  comment[i][0]='\0';
                  }
               fputc('\n',fpoutdpm);
               dpmcount++;
               } /* ~K~ */
            maxlines=0;
            using_dpm=1;
            } /* ~I~ */
         } /* ~G~ */
      } /* ~D~ */
   else {
      if (maxlines==0){
         strcpy(header[hdrcnt],readstr);
         hdrcnt++;/* we need to add a closing brace which we are not saving */
         if (NULL!=(ptr=strstr(readstr,prog))){
            if (*(ptr+strlen(prog))==rev) fprintf(fpstatus,"translator rev. ok\n");
            else {
               fprintf(fpstatus,"FYI:%s:translator rev. does not match %c (%c in %s)\n",progstr,rev,*(ptr+strlen(prog)),pattern);
               fprintf(fperrors,"FYI:%s:translator rev. does not match %c (%c in %s)\n",progstr,rev,*(ptr+strlen(prog)),pattern);
               }
            }
         }
      else if (DEBUG) fprintf(fpstatus,"ignoring [%s]\n",readstr);
      if (hdrcnt>=MAXCPMOPTLINES) {
         fprintf(stderr,"NON_FATAL_ERROR:[%s.evo](hdr) CPM pattern is too big to optimize\n",pattern);
         fprintf(stderr,"NON_FATAL_ERROR:[%s](hdr) writing header and clearing... this could be wrong\n",pattern);
         fprintf(fperrors,"NON_FATAL_ERROR:%s (hdr)[%s.evo]cpm pattern is too big to optimize\n",progstr,pattern);
         fprintf(fperrors,"NON_FATAL_ERROR:%s (hdr)[%s.evo]writing header to file and clearing... this could be wrong \n",progstr,pattern);
/*         sprintf(readstr,"\\rm -f _%s.evo",pattern);
         system(readstr); remove output cpm optomized file 
         return(-1); */
         for (i=0;i<hdrcnt;i++){
            fprintf(fpout,"%s\n",header[i]);
            }
         hdrcnt=0;
         }
      }
   }
if (DEBUG) for (i=0;i<maxlines;i++) fprintf(fpstatus,"vector=[%s]\n",vector[i]);
if (DEBUG) for (i=0;i<maxlines;i++) fprintf(fpstatus,"%d:uI=[%s]\n",i,uinstr[i]);
if (DEBUG) for (i=0;i<maxlines;i++) fprintf(fpstatus,"sh=[%s]\n",sh[i]);
if (DEBUG) for (i=0;i<maxlbls;i++) fprintf(fpstatus,"lbl=[%s]@[%d]\n",lbltbl[i],lbl_tbl[i]);

/* First get rid of DEF_WFT */
for (i=0;i<maxlines;i++) {
if (DEBUG)    fprintf(fpstatus,"wft=[%s]\n",wft[i]);
   /* if used for scan optimization then don't allow ScanCycles */
   if (0!=strcmp(wft[i],DEF_WFT) && NULL==strstr(wft[i],"Scan") ) {
      strcpy(new_wft,wft[i]);
      break;
      }
  }
fprintf(fpstatus,"replacing [%s] or [%s] with [%s] \n",DEF_WFT,HOLD_CYCLE,new_wft);
for (i=0;i<maxlines;i++) {
   if ((0==strcmp(wft[i],DEF_WFT)) || (0==strcmp(wft[i],HOLD_CYCLE))) {
      strcpy(wft[i],new_wft);
      }
  if (DEBUG) fprintf(fpstatus,"wft=[%s]\n",wft[i]);
  }
/* Next we are cpm-calling-dpm followed by match (not RPTP) then we can probably reduce the
   SDP,RPT by two and push the ddd vector onto the LC1,and MODE IFAIL vectors. This is a
   one time only deal starting at vector 3 for RPT,SDP and checking vectors 4 and 5. */
if (NULL!=strstr(uinstr[2],"SDP") && 
    NULL!=strstr(uinstr[3],"LC1") && 
    NULL!=strstr(uinstr[4],"MODE(IFAIL ON")) {
    tmp1=0;k=0;
    while(uinstr[2][sizeof("RPT ")-1+k]!=',') tmp1=10*tmp1+uinstr[2][sizeof("RPT ")-1+k++]-'0';
    if (tmp1>3) {
       fprintf(fpstatus,"OPT1:We have found a candidate for LDA/RPT/LC1/MODE(IFAIL),line[%d][%s][%s][%s]R[%d]\n",i,uinstr[2],uinstr[3],uinstr[4],tmp1);
       tmp1-=2;
       strcpy(vector[3],vector[2]);
       strcat(uinstr[3],",SDP");
       strcpy(vector[4],vector[2]);
       /* strcat(uinstr[4],",SDP"); */
       sprintf(uinstr[2],"RPT %d,SDP",tmp1);
       }
    }

/* ok, now see if any of the DC4,CJMPs only jmp back one vector and that vector has a repeat 
   if all conditions are met then we can remove the loop */

for (nzckeep=1;nzckeep<=4;nzckeep++) { /* added nzckeep for loop 06/05/05 */
   for (i=1;i<maxlines;i++){
      sprintf(CNTRSTR,"DC%d,CJMP",nzckeep);
      if (NULL==strstr(uinstr[i],CNTRSTR) || NULL==strstr(uinstr[i-1],"RPT") ) continue;
      strcpy(readstr,&uinstr[i][sizeof("DC?,CJMP ")-1]);/* ok its only a sizeof */
      for (j=0;j<maxlbls;j++) if (0==strcmp(lbltbl[j],readstr)) break;
      if (j<maxlbls && lbl_tbl[j]==i-1 ) {
         tmp1=0;k=0;
         while(uinstr[i-1][sizeof("RPT ")-1+k]!='\0') {
            /* fprintf(fpstatus,":%c",uinstr[i-1][sizeof("RPT ")-1+k]); */
            tmp1=10*tmp1+uinstr[i-1][sizeof("RPT ")-1+k++]-'0';
            }
         tmp2=0;k=0;
         while(uinstr[i-3][sizeof("LC? ")-1+k]!='\0') {
            /* fprintf(fpstatus,";%c",uinstr[i-3][sizeof("RPT ")-1+k]); */
            tmp2=10*tmp2+uinstr[i-3][sizeof("RPT ")-1+k++]-'0';
            }
         /* note that we need to increment the LC number to get
               the real count for the repeat */
         tmp2++;
         tmp2*=tmp1;
         fprintf(fpstatus,"OPT2:We have found a candidate for LOOP removal,line[%d][%s][%s]R[%d]\n",i,uinstr[i],lbltbl[j],tmp2);
         lbl_tbl[j]=-1;lbltbl[j][0]='\0';
         if (tmp2<65535) {
            vector[i  ][0]=sh[i  ][0]=wft[i  ][0]=uinstr[i  ][0]='\0';
            vector[i-2][0]=sh[i-2][0]=wft[i-2][0]=uinstr[i-2][0]='\0';
            vector[i-3][0]=sh[i-3][0]=wft[i-3][0]=uinstr[i-3][0]='\0';
            sprintf(uinstr[i-1],"RPT %d",tmp2);
            }
         else if (tmp2<65535*2) {
            vector[i-2][0]=sh[i-2][0]=wft[i-2][0]=uinstr[i-2][0]='\0';
            vector[i-3][0]=sh[i-3][0]=wft[i-3][0]=uinstr[i-3][0]='\0';
            strcpy(vector[i],vector[i-1]);
            sprintf(uinstr[i],"RPT %d",65535);tmp2-=65535;
            sprintf(uinstr[i-1],"RPT %d",tmp2);
            }
         else if (tmp2<65535*3) {
            vector[i-3][0]=sh[i-3][0]=wft[i-3][0]=uinstr[i-3][0]='\0';
            strcpy(vector[i-2],vector[i-1]);
            strcpy(vector[i],vector[i-1]);
            sprintf(uinstr[i-2],"RPT %d",65535);tmp2-=65535;
            sprintf(uinstr[i],"RPT %d",65535);tmp2-=65535;
            sprintf(uinstr[i-1],"RPT %d",tmp2);
            }
         else if (tmp2<65535*4) {
            strcpy(vector[i-3],vector[i-1]);
            strcpy(vector[i-2],vector[i-1]);
            strcpy(vector[i],vector[i-1]);
            sprintf(uinstr[i-3],"RPT %d",65535);tmp2-=65535;
            sprintf(uinstr[i],"RPT %d",65535);tmp2-=65535;
            sprintf(uinstr[j],"RPT %d",tmp2);
            }
         }
      }
   } /* for nzckeep */
/* if DC4,CJMP without a label and previous vector does not have a microinstruction (except RPT) then
   move the DC4,CJMP back one and delete the --- */
for (i=1;i<maxlines;i++){
   if (vector[i][0]=='\0' || vector[i-1][0]=='\0') continue;
/*   if (NULL!=strstr(uinstr[i],"DC4,CJMP") && uinstr[i-1][0]=='\0' ){ */
     /* should probably check if there is a label in between */
/*      fprintf(fpstatus,"We have found a candidate for DC4,CJMP relocation,line[%d][%s]R[%d]\n",i,uinstr[i],tmp2);
      strcpy(uinstr[i-1],uinstr[i]);
      vector[i][0]=uinstr[i][0]=wft[i][0]='\0'; */
/* ***** THIS CODE IS NEW  NEEDS CHECKOUT ******* */
   if (NULL!=strstr(uinstr[i],"DC4,CJMP") || NULL!=strstr(uinstr[i],"DC3,CJMP") ||
       NULL!=strstr(uinstr[i],"DC2,CJMP") || NULL!=strstr(uinstr[i],"DC1,CJMP")) {
/*   if (NULL!=strstr(uinstr[i],"CJMP") ) { */
      if (strstr(uinstr[i-1],"DC")==NULL && strstr(uinstr[i-1],"LC")==NULL 
         && strstr(uinstr[i-1],"COND")==NULL && strstr(uinstr[i-1],"LDA")==NULL
         && strstr(uinstr[i-1],"LDA")==NULL && strstr(uinstr[i-1],"MODE")==NULL
         && strstr(uinstr[i-1],"FLAG")==NULL && strstr(uinstr[i-1],"NZC")==NULL){/* added NZC 06/05/05 */
            /* we allow only RPT or nothing on the previous vector */
            ded=0;
            if (strstr(uinstr[i-1],"RPT")!=NULL){ /* decrement rpt copy extra vector down */
               fprintf(fpstatus,"It appears there is a RPT[%s]\n",uinstr[i-1]);
               for (j=strlen("RPT ");j<strlen(uinstr[i-1]);j++) if (uinstr[i-1][j]<='9' && uinstr[i-1][j]>='0') {
                  ded=ded*10+uinstr[i-1][j]-'0';
                  }
               }
            }
         /* need check if there is a label in between!! for nested loops!!! */
         fprintf(fpstatus,"OPT3:We have found a candidate for DC?,CJMP relocation,line[%d][%s]R[%d]\n",i,uinstr[i],tmp2);
/*         fprintf(fpstatus,"OPT3:We have found a candidate for CJMP relocation,line[%d][%s]R[%d]\n",i,uinstr[i],tmp2); */
         strcpy(tmplblstr,&uinstr[i][0+sizeof("DC?,CJMP ")]);
         for (j=0;j<maxlbls;j++) {
            if (NULL!=strstr(lbltbl[j],tmplblstr)) {
               fprintf(fpstatus,"found label %s %d %d %d\n",lbltbl[j],j,i,lbl_tbl[j]);
               if (lbl_tbl[j]!=i-2) {fprintf(fpstatus,"Nope, sorry loop not adjacent\n");ded=-1;continue;}
               }
            }
         if (ded==-1) continue;
         if (ded==0) {
            fprintf(fpstatus,"There is no repeat\n");
            strcpy(uinstr[i-1],uinstr[i]);
            vector[i][0]=uinstr[i][0]=wft[i][0]='\0';
            }
         else if (ded==2) {
            fprintf(fpstatus,"The repeat is 2\n");
            uinstr[i-1][0]='\0';
            strcpy(vector[i],vector[i-1]);
            }
         else {
            fprintf(fpstatus,"The repeat is [%d]\n",ded);
            sprintf(uinstr[i-1],"RPT %d",ded-1);
            strcpy(vector[i],vector[i-1]);
            }
         }
      }

/* Look for IFAIL OFF followed by IFAIL ON, remove both if found */
for (i=2;i<maxlines;i++){
   if (vector[i][0]=='\0' || vector[i-1][0]=='\0' || vector[i-2][0]=='\0') continue;
   if (NULL!=strstr(uinstr[i],"MODE(IFAIL ON,TCI ON") &&
       NULL!=strstr(uinstr[i-2],"MODE(IFAIL OFF,TCI OFF)") &&
       NULL!=strstr(uinstr[i-1],"LC1")) {
      fprintf(fpstatus,"OPT4:We have found a candidate for IFAIL OFF/ON removal,line[%d][%s][%s][%s]\n",i,uinstr[i-2],uinstr[i-1],uinstr[i]);
      vector[i][0]=uinstr[i][0]=wft[i][0]='\0';
      vector[i-2][0]=uinstr[i-2][0]=wft[i-2][0]='\0';
      }
   }
/* if LC4 without a label and previous vector does not have a microinstruction then
   move the LC4 back one and delete the --- */
for (i=1;i<maxlines;i++){
   if (vector[i][0]=='\0' || vector[i-1][0]=='\0') continue;
   if (NULL!=strstr(uinstr[i],"LC4") && uinstr[i-1][0]=='\0' ){
     /* should probably check if there is a label in between */
      fprintf(fpstatus,"OPT5:We have found a candidate for LC4 relocation,line[%d][%s]\n",i,uinstr[i]);
      strcpy(uinstr[i-1],uinstr[i]);
      vector[i][0]=uinstr[i][0]=wft[i][0]='\0';
      }
   }
/* if CJMP .-xx without a label and previous vector does not have a microinstruction then
   move the CJMP .-xx  back one change to CJMP . and delete the --- */
for (i=1;i<maxlines;i++){
   if (vector[i][0]=='\0' || vector[i-1][0]=='\0') continue;
   if (NULL!=strstr(uinstr[i],"CJMP .-") && uinstr[i-1][0]=='\0' ){
       ded=0;
       for (j=strlen("CJMP .-");j<strlen(uinstr[i]);j++) if (uinstr[i][j]<='9' && uinstr[i][j]>='0') {
           ded=ded*10+uinstr[i][j]-'0';
           }
     /* should probably check if there is a label in between */
      fprintf(fpstatus,"OPT6:We have found a candidate for CJMP .-xx(%d) relocation,line[%d][%s]\n",ded,i,uinstr[i]);
      ded--;
      if (ded==0) strcpy(uinstr[i-1],"CJMP .");
      else sprintf(uinstr[i-1],"CJMP .-%d",ded);
      vector[i][0]=uinstr[i][0]=wft[i][0]='\0';
      }
   }
/* Now, check if FLAG SEQF,COND NZC1,then RPT >3 */
for (i=4;i<maxlines;i++){
   if ((NULL!=strstr(uinstr[i-4],"FLAG(SEQF OFF)")  && 
       NULL!=strstr(uinstr[i-3],"COND NZC1")   &&
       vector[i-2][0]=='\0'  && vector[i-1][0]=='\0'  && 
       NULL!=strstr(uinstr[i],"RPT ")) ||
       (NULL!=strstr(uinstr[i-2],"FLAG(SEQF OFF)")  && 
       NULL!=strstr(uinstr[i-1],"COND NZC1")  &&
       NULL!=strstr(uinstr[i],"RPT "))
       ) {
       /* if the vector contains a strobe then invalidate the action */
       if (NULL!=strchr(vector[i],'0') ||NULL!=strchr(vector[i],'1')) {
          fprintf(fpstatus,"Sorry, there is a strobe on the RPT for (SEQF/CONDNZC1/RPT)\n");
          continue;
          }
       tmp1=0;k=0;
       while(uinstr[i][sizeof("RPT ")-1+k]!='\0') tmp1=10*tmp1+uinstr[i][sizeof("RPT ")-1+k++]-'0';
       if (tmp1>3) {
          tmp1-=2;
          if (vector[i-1][0]!='\0') {
             fprintf(fpstatus,"OPT7a:We have found a candidate for 1SEQF/CONDNZC1/RPT,line[%d][%s][%s]R[%d]\n",i,uinstr[i-2],uinstr[i-1],tmp1+2);
             strcpy(vector[i-2],vector[i]);
             strcpy(vector[i-1],vector[i]);
             sprintf(uinstr[i],"RPT %d",tmp1);
             }
          else {
             fprintf(fpstatus,"OPT7b:We have found a candidate for 2SEQF/CONDNZC1/RPT,line[%d][%s][%s]R[%d]\n",i,uinstr[i-4],uinstr[i-3],tmp1+2);
             strcpy(vector[i-4],vector[i]);
             strcpy(vector[i-3],vector[i]);
             sprintf(uinstr[i],"RPT %d",tmp1);
             }
          }
       }
   }
/* further optimizations: */
/* look for loops with LC4 of 2 or less with only two active vectors; 
     expand this into straight line (LC4+1) */

/* ?) look for matches with repeats; replace --- with vector. */
/* ?) look for adjacent rpts; replace --- with vector.
     may be able to push vectors down if inside loop. */

/* We are done!! spit out pattern */
for (i=0;i<hdrcnt;i++) fprintf(fpout,"%s\n",header[i]);
fprintf(fpstatus,"CPMRPTLDA:%d USING_DPM:%d\n",cpmrptlda,using_dpm);
if (cpmrptlda>0 && using_dpm){
   strcpy(cpmvector3,cpmvector1);
   for (i=0;i<strlen(cpmvector3);i++) if(cpmvector3[i]!=' ') cpmvector3[i]=HOLD_CHAR;
   fprintf(fpoutdpm,"* %s * %s %s; \"DUMMY VECTOR\"\n}\n",cpmvector3,cpmwft1,cpmsh1);/* close out dpm */
   fclose(fpoutdpm);
   sprintf(readstr,"gzip -f DPMO_%s.evo",pattern);
   system(readstr); /* gzip DPMO_ file */
   fprintf(fpout,"$%s_begin\n",pattern);
   fprintf(fpout,"* %s * %s %s; <LDA DPMO_%s_st>\n",cpmvector1,cpmwft1,cpmsh1,pattern);
   fprintf(fpout,"* %s * %s %s; <RPT %d>\n",cpmvector2,cpmwft2,cpmsh2,cpmrptlda);
   for (i=0;i<strlen(cpmvector1);i++) if(cpmvector1[i]!=' ') cpmvector1[i]=CPMDPM_CHAR;
   while (dpmcount>MAX_RPT_CPM) {
      fprintf(fpout,"* %s * %s %s;<RPT %ld,SDP>\n",cpmvector1,cpmwft2,cpmsh2,(long)MAX_RPT_CPM);
      dpmcount -= MAX_RPT_CPM;
      }
   fprintf(fpout,"* %s * %s %s; <RPT %d,SDP>\n",cpmvector1,cpmwft2,cpmsh2,dpmcount);
   }
else {
   fclose(fpoutdpm);
   sprintf(readstr,"DPMO_%s.evo",pattern);
   fprintf(fpstatus,"removing empty dpm pattern [%s]\n",outfiledpm);
   if (0!=remove(readstr)) perror ("Error removing empty DPMO_ file");
   }

curptr=0;
tmp1=0;
sprintf(tmpstr,"%s_begin",pattern);
for (i=0;i<maxlines;i++) {
   if (lbl_tbl[curptr]==i) {
      if (NULL!=strstr(lbltbl[curptr],tmpstr)) {
         fprintf(fpout,"$%s_orig\n",lbltbl[curptr]);
         }
      else fprintf(fpout,"$%s\n",lbltbl[curptr]);
      curptr++;
      while (lbl_tbl[curptr]==-1 && curptr<maxlbls) curptr++;
      }
   if (vector[i][0]!='\0') {
      fprintf(fpout,"*%s * %s %s; ",vector[i],wft[i],sh[i]);
      if ( uinstr[i][0]!='\0') fprintf(fpout,"<%s>",uinstr[i]);
      if (comment[i][0]!='\0') fprintf(fpout,"\"%s\"",comment[i]);
      fputc('\n',fpout);
      }
   else tmp1++;
   }
if (optpreprocrev[0]!='\0') fprintf(fpout,"%s",optpreprocrev);
fprintf(fpout,"}\n");/* we didn't save this when reading  */
fclose(fpout);
fprintf(fpstatus,"Optimizations have removed %d redundant vectors in[%s]\n",tmp1,pattern);
fprintf(fpstatus,"DPM pattern optimizations removed %d redundant vectors in[%s]\n",dpmcount,pattern);
fprintf(fpstatus,"Backing up original file,\n");
sprintf(readstr,"__%s.evo",pattern);
if (0!=rename(infile1,readstr)) perror("Error backing up original file to __file");
fprintf(fpstatus," moving optimizied pattern to correct name\n");
if (0!=rename(outfile1,infile1)) perror("Error renaming new file to real name"); 
return (0);
}
