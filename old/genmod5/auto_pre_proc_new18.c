/* This program is covered by the GNU GPL license. Please see the file: COPYING.gz for the license info. */
/* original author: anthony_sully@ltx.com */

/* pre_proc.c -> PRE_PROC_DPM/PRE_PROC_CPM - preprocess polaris patterns and add microinstructions as necessary 
                                             actual pattern conversion happens with vector_convert_polaris or 
                                             vector_convert_scan */
/* Sept.02 Anthony Sully, LTX Corp. Created this file to pre-process the microcontroller
                                   .vpl patterns to find:
                                    1) repeat blocks and expand them
                                    2) match blocks and add cpm microinstructions
                                    3) repeat forever statements and add cpm microinstructions.
                                    Normally, it will try to create a DPM pattern as that
                                    will be most efficient test_time-wise and saves
                                    precious cpm. If (2) or (3) above are found then
                                    CPM must be used so the program will re-call itself
                                    as PRE_PROC_CPM (executable name is hardcoded!!!)
                                    and generate cpm loops for (1) instead. */

/* 09/28/02 Anthony Sully, LTX Corp. Fixed code for match loop search so 'match' did not
                                     have to be at the left margin. Now it finds 'match'
                                     and then determines if there is an open comment ahead
                                     of it. Note that this may not work properly for block
                                     comments or comments ahead of the match instruction
                                     as no close is looked for. A similar thing is done
                                     with repeats.
                                     Added the translation_error.txt output as in
                                     vector_convert_polaris2.c
                                     Added support for .gz and .Z input files.*/

/* 09/30/02 Anthony Sully, LTX Corp. Fixed OOPS where the new code for opening compressed
                                     files wiped out the code for opening the file if it
                                     was not compressed. */

/* 10/02/02 Anthony Sully, LTX Corp. Found that match loops were not creating the correct
                                     label if a repeat loop occured inside. Made a localized
                                     variable so each level would have its own copy. */

/* 10/09/02 Anthony Sully, LTX Corp. Had to increase the buffer sizes to allow nested loops
                                     of two vectors with the inner loop of 5000 and an outer
                                     loop of 10. Also, added an approximate comparison to
                                     give an error message about excceding the buffer size
                                     instead of crashing without any indication. */

/* 10/12/02 Anthony Sully, LTX Corp. Created new version 4 which includes the capability to
                                     create a CPM calling DPM pattern if a match is found and
                                     the vectors before this vector total at least 100. This
                                     adds complexity but will help in reducing CPM usage which
                                     appears to be a big issue. If a match is found it will
                                     close out the current file and move it to DPM_original_name.
                                     The CPM pattern will then take on the original_name. This
                                     also makes translation faster as it does not waste the
                                     original file read. Appropriate modifications were also
                                     made to vector_convert_polaris4.c to accomodate this option.
                                     All this should happen automatically, all the user needs to
                                     do is add the DPM_%s patterns to the PatternMap and to the
                                     threads as SetRefs. If CPM only is desired then call the
                                     executable as PRE_PROC_CPM. Added variable appr_vc to
                                     get an approximate vector count by searching for GCT.
                                     This code does not make cpm calling dpm for repeat forever.
                                     Fixed the CMJP +2 over the STOP FAIL
                                     Modified the name of the uncompressed file to use the
                                     name of the source file with a .tmpgunzip tacked on
                                     the end.
                                     Fixed a problem in the input file uncompression routine,
                                     it was not exiting if the input file was not found.
                                     Under Linux there appears to be a crash on program exit
                                     under certain circumstances. I have not been able to
                                     determine what causes it yet. However, the files seem
                                     to complete correctly and I have added a print to stderr
                                     at the very end indicating that the program completed
                                     sucessfully. */

/* 10/19/02 Anthony Sully, LTX Corp. Fixed some issues with file name locations. The program will
                                     now correctly read files in remote protected directories. All
                                     new files will be created in the current working directory. */

/* 11/02/02 Anthony Sully, LTX Corp. Fixed compile script and includes so date can be brought in with
                                     gcc or cc */

/* 11/07/02 Anthony Sully, LTX Corp. Saturn application has some some differences in Scan patterns.
                                     It has had repeat compression enabled on the parallel vectors
                                     so it looks like we will need pre_proc to deal with that first.
                                     I have modified this code to check if is a scan pattern and
                                     if so expand the repeats and ignore the fact that there is a
                                     repeat forever which would force the repeats into CPM block
                                     loops also. Due to the longer scan chain lengths I also had
                                     to fix a line wrap issue where it was assuming the carriage
                                     return always existed and wrote over the last character in
                                     the string which in this case was actually a scan bit. This
                                     code needs to be fixed in the other 'C' programs as well.
                                     Actually, it looks like they are wrapping their code at 2048
                                     characters so I think the best thing to do is bump mine as well,
                                     being careful not to cause lack of memory problems though.
                                     Updated to rev.5 */

/* 12/10/02 Anthony Sully, LTX Corp. Found problem with continuous microinstructions. I was leaving
                                     the FLAG(CONT ON) out. */

/* 01/25/02 Anthony Sully, LTX Corp. Fixed error message if syntax was wrong. Added autolaunch of
                                     vector_convert_scan if SCAN.
                                     Updated rev. to match vector_convert_polaris6.c */                                    

/* 03/10/03 Anthony Sully, LTX Corp. Added support for approximate output line count. Removed
                                     annoying warning messages about scan if we are not doing scan.
                                     Fixed minor path problem with PRE_PROC_CPM and VCS by adding ./ in
                                     front of command. Reclassified errors into four classes:
                                     FATAL_ERRORS -- cause immediate exit of program (usually file problems)
                                     BAD_ERRORS -- fatal errors that could produce corrupted output files
                                     NON_FATAL_ERRORS -- errors that generate files with useful output
                                     FYI -- informational warnings. */

/* program now: auto_pre_proc6.c */
/* 03/29/03 Anthony Sully, LTX Corp. Added auto call of vector_convert_polaris. Added GNU license comments */

/* 04/11/03 Anthony Sully, LTX Corp. Fixed several issues with optimzation (CJMP,repeat forever) Added limits
                                     on how much to expand to dpm (MAX_LOOP_SIZE). Repeat forevers no longer
                                     force patterns to use full CPM looping (i.e. buffer leading vectors to
                                     DPM instead of loop) had to add buffering for this. Do the best we can
                                     if not given cycletbl_mod.mod2. Third optional parameter is now debug
                                     index. Added some additional checks for repeat statements found inside
                                     comments. Added third parameter to force loop size control of DPM to
                                     CPM. Bumped up MAX_LOOP_SIZE to 1M after determining what was wrong in
                                     vector_convert_polaris6a.c */

/* 05/10/03 Anthony Sully, LTX Corp. Found a subtle problem with repeat forever blocks. If there were normal
                                     repeat blocks inside (i.e. NZCx) the converter was not restoring the
                                     condition to CONT. Added a variable to keep track of whether CONT was the
                                     last condition. This was found in the Saturn operating.vpl file.  */
/* 02/25/04 Anthony Sully, LTX Corp. Modified to call as scan autogen (VCS -a). Modifed to use remove() and
                                     rename() instead of system() */

/* 03/23/04 Anthony Sully, LTX Corp. Had some issues with rename using the wrong filename. Fixed. Added
                                     error checking printouts after rename and remove using perror. */
/* 03/31/04 Anthony Sully, LTX Corp. Found a carriage return in a string name sprintf. Fixed! */
/* 02/06/05 Anthony Sully, LTX Corp. Added a comment processing skip in the loop. If a brace comment is opened
                                     then incomment is turned on and all data is pass through until close brace
                                     is found. This ASSUMES no nesting of brace comments!!!! It also skips the
                                     line in its entirety if it finds open brace.
                                     Updated as: nsf_auto_pre_proc9.c*/
/* 03/10/05 Anthony Sully, LTX Corp. Pattern from T3 with various issues, some wrong, some suboptimal:
                                     1) Nested counter weren't restoring the right NZCx before the CJMP. fixed
                                     2) Load counter are allowing values greater than 65535 (status message given)
                                     3) Simple loops with high inner loops causing CPM to be required (and
                                        being too big for HFi (4K) CPM (not fixed)
                                     4) Better buffering scheme needed in more complex situations (not fixed)
                                     5) Too many hold vectors needed for micro instructions (post process
                                        optimization (not really preproc's job).
                                     6) Move the status messages to a temp file instead of fpstatus. fixed
                                     Saved as nsf_auto_pre_proc10.c */

/* 05/10/05 Anthony Sully, LTX Corp. FX1 has a different MatchPipeline (145 vs 143). Updated code to use
                                     generic MatchPipeline variable. Saved as nsf_auto_pre_proc11.c */
/* 05/18/05 Anthony Sully, LTX Corp. Backed off the array size increase from 3/10. It causes seg faults
                                     due to excessive memory allocation. Still need a better solution for
                                     nested begins. */
/* 06/05/05 Anthony Sully, LTX Corp. Pattern EHB_code_exe from APEC1 had a repeat statement with a simple
                                     brace comment after it. This repeat was the beginning of a block.
                                     Due to the comment, the translator was throwing out the line completely.
                                     I have fixed this to preserve everything before the open brace and
                                     "re-attach" it to everything after the brace (even over multiline).
                                     (precommenthold,postcommenthold). Added a comment to the top of the
                                     pattern to show the preprocess revision. Updated to nsf_auto_pre_proc12.c */
/* 07/14/05 Anthony Sully, LTX Corp. Added new option to force dpm (actually its a command name check FORCE_DPM).
                                     This implies that a user can make the decision that he (or she) really
                                     wants a big DPM pattern instead of a looped CPM pattern. Added some syntax
                                     statements also. Preserved the 12. revision but bumped it to a .1 */

/* 09/14/05 Anthony Sully, LTX Corp. Added error message and abort (leaving .proc file) if align Polaris instruction
                                     is found. Also added code for ignoring Scan in comments. 
                                     skipped rev. to 14.0.  */

/* 06/28/08 Anthony Sully, LTX Corp. Added support for hex fields, and mux mode (from gct_gen_mod3.c) */
/* 08/09/08 Anthony Sully, LTX Corp. modified for new processing technique rev. 18 */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "appn_includes.h"

#ifndef __GNUC__
#include "local_date.h"
#define __TIME__ ""
#endif

/* begin main function */
int main (int argc,char *argv[]){
char env[READLINELEN+1],*endptr;
/* file variables */

/* buffers */
int pinheadcount=0;
char pinhead[PINSIZE][NUMPINS];
char vector[READLINELEN+1];
char *ptr,*ptr2,*ptr3,tempstr[READLINELEN+1],CYCLETBL[READLINELEN+1];
char outfile1[READLINELEN+1],pattern[READLINELEN+1],*patnameptr;
int i,j,incomment;
long gunzip=0,GIVE_CYCLETBL_WARNING=0;
char hexdebug1[MXFIELD],hexdebug2[MXFIELD],hexdebug3[MXFIELD];
int begin_loc,repeat_loc,match_loc,shutdown_loc,end_loc,CFV,CFS,CFRF,loopnest;
int vs,ve,flag_match,flag_scan,flag_repeatforever,max_rpt_depth,vc;
int inshutdown,first_match_line;
/* command line stuff */

struct stat statbuf;
off_t filesize;
int ret,pos,conv_vect;

int SUPER_CNT;
int begin_pending_index[8],last_repeat[8],max_repeat_block, repeat_calc,last_was_repeat;

struct LOOP_LINES *SUPER;
char *ptrSTART,*ptrNEXT;
char *patbuf;
char linebuf[POLARIS_PINS+SPACES+COMMENT+WFTREF+20+1];/* 20 is for MDI */

strcpy(progstr,__FILE__);
strcpy(datestr,__DATE__);
strcpy(timestr,__TIME__);
strcpy(compilestr,argv[0]);

if (getenv("DEBUG_PROC")==NULL) debug=0;
else {strcpy(env,getenv("DEBUG_PROC"));debug=strtol(env,&endptr,0);fprintf(stderr,"Turning on DEBUG!\n");}

fprintf(stderr,"\n\n%s:%s, by Anthony Sully\n covered by GNU GPL license, see the file COPYING.gz in the source directory\n",compilestr,progstr);
if (NULL==(fperrors=fopen("translation_errors.txt","a"))) {
   fprintf(stderr,"\nFATAL_ERROR:%s:Could not open translation_errors.txt for output\n",progstr);
   exit(1);
   }
if (NULL==(fpstatus=fopen("translation_status.txt","a"))) {/* replaces the fpstatus messages */
   fprintf(stderr,"\nFATAL_ERROR:%s:Could not open translation_status.txt for append output\n",progstr);
   exit(1);
   }

if (argc>=4 && isdigit(argv[3][0])) {
   fprintf(stderr,"FYI:Modifying max loop count threshold for DPM to CPM conversion from %ld to %ld\n",MAX_LOOP_SIZE,atol(argv[3]));
   fprintf(fperrors,"FYI:Modifying max loop count threshold for DPM to CPM conversion from %ld to %ld\n",MAX_LOOP_SIZE,atol(argv[3]));
   MAX_LOOP_SIZE=atol(argv[3]);
   }
if (strstr(argv[0],"FORCE_DPM")!=NULL) {fprintf(stderr,"Forcing DPM pattern\n");FORCEDPM=1;}

if (argc>=3) strcpy(CYCLETBL,(char *) argv[2]);
else {
   fprintf(stderr,"No Cycletbl_mod%s file given. This is now an error!,exiting\n",MODVER);
   fprintf(stderr,"Syntax:%s pattern.vpl.Z [cycletbl_mod%s] [debug_level]\n",argv[0],MODVER);
   fprintf(stderr,"If the third parameter starts with a number it will be assumed to be the debug level\n");
   fprintf(fperrors,"FATAL_ERROR:%s:No file given \n",progstr);
   exit(1);
   }

if ( argc>=3 && 0==strstr(CYCLETBL,MODVER) ) {
   fprintf(stderr,"This version requires a %s version %s file\n",MODVER,GCT_GEN_MODVER);
   fprintf(stderr,"Aborting....\n");
   exit(2);
   }

if (argc>=2) strcpy(infile_orig,(char *) argv[1]);
else {
   fprintf(stderr,"No file given\n");
   fprintf(stderr,"Syntax:%s pattern.vpl.Z [cycletbl_mod%s] [debug_level]\n",argv[0],MODVER);
   fprintf(stderr,"Program can be called as PRE_PROC_DPM(default), PRE_PROC_CPM(force cpm), or FORCE_DPM\n");
   fprintf(stderr,"If the second parameter starts with a number it will be assumed to be the debug level\n");
   fprintf(fperrors,"FATAL_ERROR:%s:No file given \n",progstr);
   exit(1);
   }
if (isdigit(CYCLETBL[0])) {
   debug=atoi(CYCLETBL);
   CYCLETBL[0]='\0';
   GIVE_CYCLETBL_WARNING=1;
   fprintf(stderr,"USING SECOND PARAMETER AS DEBUG LEVEL!!!!\n");
   }
//fprintf(fpstatus,"GOT2 cycl[%s]\n",CYCLETBL);

if (CYCLETBL[0]!='\0') {
//   fprintf(fpstatus,"GOT3 cycl[%s]\n",CYCLETBL);
   if (NULL!=(fp_cycmod3=fopen(CYCLETBL,"r"))) {
      hexproc[0]=hexfield[0]=muxpin[0]='\0';/* in case we don't find one! */
//      fprintf(fpstatus,"GOT4 cycl[%s]\n",CYCLETBL);
      while(fgets(vector,READLINELEN-1,fp_cycmod3) != NULL ){
         if (vector[0]=='H') strcpy(hexproc,vector+2);/* get past H[ */
         if (vector[0]=='F') strcpy(hexfield,vector+2);/* get past F[ */
         if (vector[0]=='M') strcpy(muxpin,vector+2);/* get past M[ */
         if (vector[0]=='/') {strcpy(pinhead[pinheadcount],vector);pinheadcount++;}/* pinheader info */
         }
      fclose(fp_cycmod3);
      }
   fhlen=strlen(hexproc);
   if (fhlen>0) {
      fhlen--;
      hexproc[fhlen]='\0';/* remove trailing ] */
      hexfield[fhlen]='\0';/* remove trailing ] */
      muxpin[fhlen]='\0';/* remove trailing ] */
      fieldcount[0]=0;
      fieldstart[0]=fields=0;
      for (i=0;i<fhlen;i++) {
//         fputc(hexproc[i],fpstatus);
         if (hexfield[i]==fields+'A') {fieldcount[fields]++;fieldtype[fields]=hexproc[i];}
         else {fields++;fieldstart[fields]=i;fieldcount[fields]=1;}
         if (muxpin[i]=='M') {
            fieldcount[fields]++;
            }
         }/* end for length */
      }/* end if fhlen>0 */
   for (j=0,i=0;i<fields;i++) {
      if (fieldtype[i]=='H') {
         phd_st[i]=j;
         phd_sp[i]=j+(int)((fieldcount[i]+3)/4)-1;/* allow for hex+comma, +3 is for round up... */
         j=cmma[i]=phd_sp[i]+1;
         j++;
         }
      else {/* binary */
         phd_st[i]=j;
         phd_sp[i]=j+fieldcount[i]-1;/* allow for comma */
         j=cmma[i]=phd_sp[i]+1;
         j++;
         }
      if (debug) fprintf(fpstatus,"ft[%c],fs[%d],fc[%d]st[%d]sp[%d]cm[%d]\n",
         fieldtype[i],fieldstart[i],fieldcount[i],
         phd_st[i],phd_sp[i],cmma[i]);
      }
   }/* end if CYCLETBL */
for(i=0;i<strlen(hexproc);i++) {hexdebug3[i]=',';hexdebug1[i]='.';}
hexdebug3[i]=hexdebug1[i]='\0';
strcpy(hexdebug2,hexdebug3);
for(i=0;i<fields;i++) {
   hexdebug1[fieldstart[i]]='^';
   hexdebug2[phd_st[i]]='S';
   hexdebug2[phd_sp[i]]='E';
   for(j=phd_st[i];j<=phd_sp[i];j++) hexdebug3[j]='A'+i;
   }
fprintf(fpstatus,"\nX_X   FT:FILE[%s]\n",infile_orig);
fprintf(fpstatus,"\nX_X   FT:"); for(i=0;i<fields;i++) fprintf(fpstatus,"__%c,",fieldtype[i]);
fprintf(fpstatus,"\nX_X   FC:"); for(i=0;i<fields;i++) fprintf(fpstatus,"%03d,",fieldcount[i]);
fprintf(fpstatus,"\nX_X   FS:"); for(i=0;i<fields;i++) fprintf(fpstatus,"%03d,",fieldstart[i]);
fprintf(fpstatus,"\nX_XPHDST:"); for(i=0;i<fields;i++) fprintf(fpstatus,"%03d,",phd_st[i]);
fprintf(fpstatus,"\nX_XPHDSP:"); for(i=0;i<fields;i++) fprintf(fpstatus,"%03d,",phd_sp[i]);
fprintf(fpstatus,"\nX_X CMMA:"); for(i=0;i<fields;i++) fprintf(fpstatus,"%03d,",cmma[i]);
fprintf(fpstatus,"\nX_Xcount:");
for(i=0;i<strlen(hexproc);i++) fputc('0'+i-10*(int)(i/10),fpstatus);fputc('\n',fpstatus);
fprintf(fpstatus,  "X_XHXPRC:"); fprintf(fpstatus,"%s\n",hexproc);
fprintf(fpstatus,  "X_XHXFLD:"); fprintf(fpstatus,"%s\n",hexfield);
fprintf(fpstatus,  "X_XHX_ST:"); fprintf(fpstatus,"%s\n",hexdebug1);
fprintf(fpstatus,  "X_XST_SP:"); fprintf(fpstatus,"%s\n",hexdebug2);
fprintf(fpstatus,  "X_XSIMFD:"); fprintf(fpstatus,"%s\n",hexdebug3);


strcpy(infile_base,infile_orig);
/* The following few lines check that the file actually exists before uncompressing it */
if (NULL==(fpin1=fopen(infile_orig,"r"))) {
   fprintf(stderr,"\nFATAL_ERROR:Compressed input file [%s] not found. can't gunzip...exiting\n",infile_orig);
   fprintf(fperrors,"\nFATAL_ERROR:%s:Compressed input file [%s] not found.\n",progstr,infile_orig);
   exit(1);
   }
fclose(fpin1);/* Only close it if we found that the compressed file exists */

ptr2=strrchr(infile_base,'/'); /* get the last '/' */
if (ptr2!=NULL) {
   strcpy(infile_base,ptr2);
   }

ptr=strrchr(infile_base,'.'); /* get the last '.' */
if (ptr!=NULL) {
   if (*(ptr+1)=='g' && *(ptr+2)=='z' && *(ptr+3)=='\0') gunzip=1;
   if (*(ptr+1)=='Z' && *(ptr+2)=='\0') gunzip=1;
   if (gunzip==1) {
      *ptr='\0';
      ptr3=strrchr(infile_base,'.'); /* get the last '.' i.e. .vpl */
      if (ptr3!=NULL) *ptr3='\0';
      sprintf(tempgunzipname,"%s.tmpgunzip",infile_base);
      sprintf(pattern,infile_base);
      sprintf(tempstr,"gunzip -c %s >%s",infile_orig,tempgunzipname);
      fprintf(fpstatus,"[%s]\n",tempstr);
      i=system(tempstr);/* unzip to temporary file */

      /* before opening figure out the size */
      ret=stat(tempgunzipname,&statbuf);

      if (NULL==(fpin1=fopen(tempgunzipname,"r"))) {
         fprintf(stderr,"\nFATAL_ERROR:Uncompressed input file [%s] not found.\n",tempgunzipname);
         fprintf(fperrors,"\nFATAL_ERROR:%s:Uncompressed input file [%s] not found.\n",progstr,tempgunzipname);
         exit(1);
         }
      }
   else {/* no uncompress needed */
      *ptr='\0';
      sprintf(pattern,infile_base);

      /* before opening figure out the size */
      ret=stat(infile_orig,&statbuf);

      if (NULL==(fpin1=fopen(infile_orig,"r"))) {
         fprintf(stderr,"\nFATAL_ERROR:Input file [%s] not found.\n",infile_orig);
         fprintf(fperrors,"\nFATAL_ERROR:%s:Input file [%s] not found.\n",progstr,infile_orig);
         exit(1);
         }
      }
   }
else {
   fprintf(stderr,"There is no .vpl extension[%s]\n,exiting\n",infile_orig);
   fprintf(fperrors,"There is no .vpl extension[%s]\n,exiting\n",infile_orig);
   exit(1);
   }

fprintf(stdout,"PRE_PROC_NEW:input file1 <%s> ok\n",(gunzip==1)?infile_base:infile_orig);
sprintf(outfile1,"%s.proc",pattern);
if (NULL==(fpout1=fopen(outfile1,"w"))) {
   fprintf(stderr,"\nFATAL_ERROR:Could not create output file [%s]\n",outfile1);
   fprintf(fperrors,"\nFATAL_ERROR:%s:Could not create output file [%s]\n",progstr,outfile1);
   exit(1);
   }
patnameptr=pattern;
fprintf(stderr,"\n%s/%s:<%s>\n",PRE_PROC_DPM,PRE_PROC_CPM,patnameptr);


for (i=0;i<pinheadcount;i++) fprintf(fpout1,"%s",pinhead[i]);

/* from above... */
if (ret==0) filesize=statbuf.st_size;
else {
   fprintf(stderr,"Can't determine filesize for [%s]\n",pattern);
   exit(1);
   }

SUPER=calloc(MAXPATLINES,sizeof(struct LOOP_LINES));
if (SUPER==NULL) {
   fprintf(stderr,"Could not allocate memory for %d LINES of size %d, exiting\n",MAXPATLINES,sizeof(struct LOOP_LINES));
   }
fprintf(stderr,"succesfully allocated memory for %d LINES of size %d, exiting\n",MAXPATLINES,sizeof(struct LOOP_LINES));

patbuf=malloc((size_t)(filesize+1));

if (patbuf==NULL) {
   fprintf(stderr,  "Could not allocate memory for [%s] file in memory\n",pattern);
   exit(1);
   }
fprintf(stderr,"allocated [%ld] bytes for patbuf\n",filesize);

fread(patbuf,(size_t)filesize,1,fpin1);
fclose(fpin1);
patbuf[filesize]='\0';/* just to make sure */
ptrSTART=patbuf;
vc=pos=SUPER_CNT=incomment=flag_scan=flag_match=flag_repeatforever=0;
loopnest=max_rpt_depth=max_repeat_block=last_was_repeat=inshutdown=0;
repeat_calc=1;
while(pos<filesize) {
   SUPER[SUPER_CNT].begin=SUPER[SUPER_CNT].end=0;
   SUPER[SUPER_CNT].dummy=1;/* initial to dummy. if its real, set it to zero */
   SUPER[SUPER_CNT].vc=-1;
   ptrNEXT=strchr(ptrSTART,'\n'); /* find end of line */
   *ptrNEXT='\0';
   strcpy(linebuf,ptrSTART);
   pos+=strlen(linebuf)+1; /* for the '\0' */
   *ptrNEXT='\n';
   readlinenum++;
   if (linebuf[0]=='\0') {ptrSTART=ptrNEXT+1;continue;} /* nothing to do */
/*---*/
   strip_comments(linebuf,SUPER[SUPER_CNT].comment,&incomment);
   if (incomment!=0) {ptrSTART=ptrNEXT+1;continue;} /* don't do anything else if its nested */
/*---*/
   CFRF=check_for_repeat(linebuf,&repeat_loc,&SUPER[SUPER_CNT].repeatcnt,loopnest);
   if (CFRF==RET_FOREVER) {
      flag_repeatforever=1;
      SUPER[SUPER_CNT].dummy=0;
      }
   if (SUPER[SUPER_CNT].repeatcnt>0) {
      SUPER[SUPER_CNT].dummy=0;
      if (loopnest<1) {/* we get one begin automatically for the pattern begin->end */
         fprintf(fperrors,"loop-nest problem, should be greater than zero[%s]\n",infile_orig);
         exit(1);
         }
      else {
         last_was_repeat=1;
         last_repeat[loopnest]=SUPER[SUPER_CNT].repeatcnt;
         }
      }
/*---*/
   check_for_match(linebuf,&match_loc,&SUPER[SUPER_CNT].matchcnt);
   if (match_loc!=NO_MATCH) {
      SUPER[SUPER_CNT].dummy=0;
      flag_match=1;
      first_match_line=SUPER_CNT;
      last_was_repeat=0;
      }
/*---*/
   check_for_begin(linebuf,&begin_loc,&loopnest); /* this can/will increment loopnest */
   if (begin_loc!=-1) {
      SUPER[SUPER_CNT].dummy=0;
      if (inshutdown>0) inshutdown++;
      SUPER[SUPER_CNT].shutdownvect=inshutdown;
      begin_pending_index[loopnest]=SUPER_CNT;
      SUPER[SUPER_CNT].begin=1;
      if (last_was_repeat==1) {
         if (loopnest>0) {
            repeat_calc *= last_repeat[loopnest-1];/* need to be one up */
            if (repeat_calc>max_repeat_block) max_repeat_block=repeat_calc;
            }
         SUPER[SUPER_CNT].beginpointtoend=0;
         }
      }
   else SUPER[SUPER_CNT].begin=0;
/*---*/
   check_for_end(linebuf,&end_loc,loopnest);
   if (end_loc!=-1) {
      SUPER[SUPER_CNT].end=1;
      SUPER[SUPER_CNT].dummy=0;
      if (inshutdown>0) inshutdown--;
      SUPER[SUPER_CNT].shutdownvect=inshutdown;
      if (inshutdown==1) inshutdown=0;
      SUPER[begin_pending_index[loopnest]].beginpointtoend=SUPER_CNT;
      SUPER[SUPER_CNT].endpointtobegin=begin_pending_index[loopnest];
      if (last_was_repeat) {
         if (loopnest>0){
            if (last_repeat[loopnest-1]!=0) repeat_calc /= last_repeat[loopnest-1];/* need to be one up */
            }
         }
      loopnest--;
      if (loopnest<0) {
         fprintf(fperrors,"FATAL:Found extra 'end;', error in [%s],exiting\n",infile_orig);
         exit(1);
         }
      }
   if (loopnest>max_rpt_depth) max_rpt_depth=loopnest;
   SUPER[SUPER_CNT].level=loopnest;
/*---*/
   check_for_shutdown(linebuf,&shutdown_loc);
   if (shutdown_loc!=-1) {
      SUPER[SUPER_CNT].dummy=0;
      last_was_repeat=0;
      SUPER[SUPER_CNT].shutdownvect=inshutdown=1;
      }
/*---*/
   check_for_align(linebuf);/* these do nothing useful other than flag */
   check_for_subroutine(linebuf);
/*---*/
   SCAN=check_for_scan(linebuf);
   if (SCAN) flag_scan=1;
/*---*/
   /* returns location of ';'  */
   SUPER[SUPER_CNT].VectorType=VT_NONE;
   CFS=check_for_SET(linebuf,SUPER[SUPER_CNT].vector,&vs,&ve);
   CFV=0;
   if (CFS!=0) {SUPER[SUPER_CNT].VectorType=VT_SET;SUPER[SUPER_CNT].dummy=0;SUPER[SUPER_CNT].label[0]='\0';}
/*---*/
   else {/* can't be vector if already SET */
      CFV=check_for_vector(linebuf,SUPER[SUPER_CNT].vector,&vs,&ve,SUPER[SUPER_CNT].label);
      }
   if (CFV) {
      SUPER[SUPER_CNT].dummy=0;
      SUPER[SUPER_CNT].vc=vc;
      vc++;
      SUPER[SUPER_CNT].VectorType=VT_Vector;
      SUPER[SUPER_CNT].shutdownvect=inshutdown;
      if (inshutdown==1) inshutdown=0;/* ==1 no begin-end loop, single vector, die */
      }
   if (CFV<repeat_loc) SUPER[SUPER_CNT].vectisbefore=1;
   else if (CFV<match_loc) SUPER[SUPER_CNT].vectisbefore=1;
   else SUPER[SUPER_CNT].vectisbefore=0;
/*---*/
   SUPER_CNT++;
   ptrSTART=ptrNEXT+1;
   }

/* write out a summary of the pattern */
for (i=0;i<SUPER_CNT;i++) if (SUPER[i].begin==1) break;
if (i!=SUPER_CNT) fprintf(fpstatus,"FileStat:First begin at %6d  in [%s]\n",i,infile_orig);
else fprintf(fpstatus,"FileStat:*Error no begin found* in [%s]\n",infile_orig);
fprintf(fpstatus,"FileStat:Got     %6d lines from [%s]\n",SUPER_CNT,infile_orig);
fprintf(fpstatus,"FileStat:vectors         %6d in [%s]\n",vc,infile_orig);
fprintf(fpstatus,"FileStat:Max loop depth      %2d in [%s]\n",max_rpt_depth,infile_orig);
fprintf(fpstatus,"FileStat:Max RPT depth count %2d in [%s]\n",max_repeat_block,infile_orig);
fprintf(fpstatus,"FileStat:Match?             %3s in [%s]\n",(flag_match==0)?"NO":"YES",infile_orig);
fprintf(fpstatus,"FileStat:Scan?              %3s in [%s]\n",(flag_scan==0)?"NO":"YES",infile_orig);
fprintf(fpstatus,"FileStat:Repeat forever?    %3s in [%s]\n",(flag_repeatforever==0)?"NO":"YES",infile_orig);

/* check for bad stuff */
if (vc==0) {
   fprintf(fperrors,"Fatal:Got no vectors from this pattern[%s]\n",infile_orig);
   if (incomment) fprintf(fperrors,"Fatal:Ended inside multiline comment!!!!\n");
   }
/***************************************/
/*         begin main loop             */
/***************************************/
fprintf(fpout1,"{-FLAG-preprocessed with %s REV:%2.1f:%s by Anthony Sully compile_date:%s@%s}\n",compilestr,REV,progstr,__DATE__,__TIME__);

if (flag_scan){
   fprintf(fpout1,"(*-FLAG-This must be a CPM pattern-*)\n");
   /* output as pure CPM pattern */
   conv_vect=output_scan(outfile1,CYCLETBL,&SUPER_CNT,SUPER);
   }

else if (max_repeat_block>1000000){
   fprintf(fpout1,"(*-FLAG-This must be a CPM pattern-*)\n");
   /* output as pure CPM pattern */
   conv_vect=output_cpm(&SUPER_CNT,SUPER);
   }

else if (flag_match || flag_repeatforever){
   fprintf(fpout1,"(*-FLAG-This must be a CPM_CALLING_DPM pattern-*)\n\n");
   /* output as CPM calling DPM pattern */
   conv_vect=output_cpm_dpm(&SUPER_CNT,SUPER);
   }

else {/* its just DPM */
   conv_vect=output_dpm(&SUPER_CNT,SUPER);
   }

fclose(fpout1);

if (gunzip) {
   if(0!=remove(tempgunzipname)) perror("Can't remove ungzipped file");
   }

if (!flag_scan) {
   fprintf(fpstatus,"FYI:%s:AUTO LAUNCHING vector_convert_polaris on pattern[%s]\n",progstr,outfile1);
   fprintf(stderr,"FYI:AUTO LAUNCHING vector_convert_polaris on pattern[%s]\n",outfile1);

   sprintf(tempstr,"%s %s %s",VECTOR_CONVERT_POLARIS,outfile1,CYCLETBL);
   system(tempstr); /* call VCP */
   fprintf(fpstatus,"Back from VCP\n");

   fprintf(stderr,"COMPLETED PROGRAM SUCCESSFULLY!\nGenerated at least %ld lines\n",countlines);
   fclose(fpstatus);
   fclose(fperrors);
   return(RET_GOOD);
   }
return(RET_GOOD);
}/* end of main program */
