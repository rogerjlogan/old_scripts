/* appn_globals.c: global definitions for auto_pre_proc_new */

#include <stdio.h>
#include "appn_includes.h"

/* globals for convenience in functions */
int debug=0;
/* debug:
   1 in/out return deal_with*
   2 general status
   4 repeat count function
   8 deal_with* status messages
   16 vector dump */
   
FILE *fperrors,*fpin1,*fpout1,*fpstatus,*fp_cycmod3;

long readlinenum=0,cpm_calling_dpm_count=0,appr_vc=0,countlines=0;
char infile_orig[READLINELEN+1];
char progstr[MEMOSTRLEN],datestr[MEMOSTRLEN],timestr[MEMOSTRLEN],compilestr[MEMOSTRLEN];/* concaternated strings */
char tempgunzipname[READLINELEN+1];
int SCAN=0,lastwascont=0;
long MAX_LOOP_SIZE=def_MAX_LOOP_SIZE;
int FORCEDPM=0;
int repeat_count_buffer[4];/* max 4 counter nesting */
char hexfield[READLINELEN+1],newvector[READLINELEN+1];
char hexproc[READLINELEN+1],muxpin[READLINELEN+1];
int fieldcount[MXFIELD],fieldtype[MXFIELD],fieldstart[MXFIELD],fields=0,fhlen=0;
int phd_st[MXFIELD],phd_sp[MXFIELD],cmma[MXFIELD];
