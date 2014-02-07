/* auto_pre_proc_new include files */

#define REV 18.0
#ifndef __GNUC__
#include "local_date.h"
#define __TIME__ ""
#endif

#include <stdio.h>

#define MODVER ".mod5"
#define GCT_GEN_MODVER "GCT_GEN_MOD5"

#define VECTOR_CONVERT_SCAN "./VCS_NEW -fgza"
#define VECTOR_CONVERT_POLARIS "./VCP_NEW -fgroz"
#define PRE_PROC_CPM "PRE_PROC_CPM"
#define PRE_PROC_DPM "PRE_PROC_DPM"
#define AUTO_PRE_PROC "AUTO_PRE_PROC"
#define MEMOSTRLEN 256
#define READLINELEN 2050
#define BIG_BUFFER_SIZE 4000000
#define MED_BUFFER_SIZE 1200000
#define def_MAX_LOOP_SIZE 1000000
#define MAX_COUNT 65535

#define RET_GOOD 0
#define RET_MATCH 1
#define RET_REPEAT_FOREVER 2
#define RET_IGNORING_STATEMENT 3
#define RET_NORMAL 4
#define RET_REPEAT_FOREVER_SCAN 5
#define RET_LOOP_SIZE_TOO_BIG 6
#define RET_BAD_INFILE -1
#define RET_BAD_OUTFILE -2
#define RET_CPM_NEEDED -3
#define RET_NOT_ENOUGH_MEMORY -4
#define RET_FOREVER -1
#define MXFIELD 400
#define NUMPINS 1026
#define PINSIZE 50
#define FORCE_DPM 1
#define FORCE_DPM 1
#define POLARIS_PINS 376
#define COMMENT 500
#define LABEL 50
#define MDI 17
#define WFTREF 25
#define SPACES 25
#define RPT_LVLNUMS 5
#define MAXPATLINES 500000
#define NOT_VECTOR -1
#define MDISET -2

/* struct definitions: */
#define NO_MATCH -1
struct LOOP_LINES {
   char vector[POLARIS_PINS+SPACES+1];
   char comment[COMMENT];
   char label[LABEL];
#define VT_NONE 0
#define VT_Vector 1
#define VT_SET 2
   int VectorType;
   int vc;
   int shutdownvect;
   int begin;
   int end;
   int beginpointtoend,endpointtobegin;
   int level;
   int noaction;
   int repeatcnt;
   int inmatch,matchcnt;
   int vectisbefore;
   int dummy;
   };

/* function prototypes */
int deal_with_match(FILE *fpin1,FILE *fpout1,char *ptr,int *repeat_nesting,long *loop_number,
                      char *vector,int *repeat_cnts,char *retbuff,char *patnameptr);
int deal_with_repeat_DPM(FILE *fpin1,FILE *fpout1,char *ptr,int *repeat_nesting,long *loop_number,
                      char *vector,int *repeat_cnts,char *retbuff);
int deal_with_repeat_CPM(FILE *fpin1,FILE *fpout1,char *ptr,int *repeat_nesting,long *loop_number,
                      char *vector,int *repeat_cnts,char *retbuff,char *patnameptr);
char * get_count_orig(char *ptr,int offset, long *count,char *vector);
int get_count(char *ptr);
int expand_vector(char *newvector,char *vector,char *ptr,int callfrom,char *file);
int strip_comments(char *vector,char *comments,int *incomment);
int check_for_begin(char *vector,int *begin_loc,int *loopnest);
int check_for_end(char *vector,int *end_loc,int loopnest);
int check_for_repeat(char *vector,int *repeat_loc,int *repeatloop,int loopnest);
int check_for_shutdown(char *vector,int *shutdown_loc);
int check_for_match(char *vector,int *match_loc,int *matchloop);
int check_for_align(char *vector);
int check_for_scan(char *vector);
int check_for_vector(char *vector,char *result_vector,int *vs,int *ve,char *label);

int check_for_SET(char *vector,char *result_vector,int *vs,int *ve);
int check_for_subroutine(char *vector);

int output_cpm(int *SUPER_CNT,struct LOOP_LINES  *SUPER);
int output_cpm_dpm(int *SUPER_CNT,struct LOOP_LINES  *SUPER);
int output_dpm(int *SUPER_CNT,struct LOOP_LINES  *SUPER);
int output_scan(char *outfile1,char *CYCLETBL,int *SUPER_CNT,struct LOOP_LINES  *SUPER);
int out_rpt_dpm(struct LOOP_LINES *SUPER,int rpt,int at,int lvl,int *exitat,int *exitlvl,int *cc);
int out_begin_dpm(struct LOOP_LINES *SUPER,int at,int lvl,int *exitat,int *exitlvl,int *cc);


/* externs: */
extern int debug;
extern FILE *fperrors,*fpin1,*fpout1,*fpstatus,*fp_cycmod3;
extern long readlinenum,cpm_calling_dpm_count,appr_vc,countlines;
extern char infile_orig[READLINELEN+1];
extern char progstr[MEMOSTRLEN],datestr[MEMOSTRLEN],timestr[MEMOSTRLEN],compilestr[MEMOSTRLEN];/* concaternated strings */
extern char tempgunzipname[READLINELEN+1];
extern int SCAN,lastwascont;
extern long MAX_LOOP_SIZE;
extern int FORCEDPM;
extern int repeat_count_buffer[4];/* max 4 counter nesting */
extern char hexfield[READLINELEN+1],newvector[READLINELEN+1];
extern char hexproc[READLINELEN+1],muxpin[READLINELEN+1];
extern int fieldcount[MXFIELD],fieldtype[MXFIELD],fieldstart[MXFIELD],fields,fhlen;
extern int phd_st[MXFIELD],phd_sp[MXFIELD],cmma[MXFIELD];
extern char infile_base[READLINELEN+1];
