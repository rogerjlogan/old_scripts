/* gct_gen_mod_includes.h */

#include <stdio.h>

#define DEBUG 0

#define READLINELEN 2000
#define FILENAMELEN 120
#define MEMOSTRLEN 256
#define NUMPINS 1026
#define PINSIZE 50
#define GCTSIZE 30
#define MAXlists 200
#define MODVER ".mod5"
#define WFTMODVER "Waveforms_GCTGENMOD5.evo"

/* function prototypes: */
int parse_actable(char *fname,int used_line[],char *tperiod);
int process_waveforms(FILE *fpwaves,int *fmtcnt,int *which,char *pin,int used_line[],int DSET,int CNT,char *tperiod,int *code0,int *code1);
int process_edgesetdelay_waveform(FILE *fpwaves,int *fmtcnt,int *which,char *pin,int used_line[],int DSET,int CNT,char *tperiod,int *code0,int *code1);
int process_edgeset_waveform(FILE *fpwaves,int *fmtcnt,int *which,char *pin,int used_line[],int DSET,int CNT,char *tperiod,int *code0,int *code1);
int find_origin(char *WF,char *org1,char *org2,char *org3,char *org4);
int process_pins(FILE *fpin2,FILE *fpin3,char *infile3,char *muxpin);

typedef struct CELL_INFO {
   long filepos;/* for fseek/ftell */
   int multidefnum;
   int formatnum;
   int actline;
   int formats[4];
   char wftname[20];
   char cellname[25];
   char pin[100];
   } CELL_INFO;

typedef struct PINLIST {
   char pinlistname[READLINELEN+1];
   char pinlists[NUMPINS+1];
   char groups[READLINELEN+1];
   } PINLIST;

#define MAX_MATCH_FMT 25
struct FORMAT_SEARCH {
   int wfmln0[MAX_MATCH_FMT]; /* all DSET0 waveforms that match */
   int wfmln1[MAX_MATCH_FMT]; /* all DSET0 waveforms that match */
   int wftype0[MAX_MATCH_FMT];/* actual wfmtype that match */
   int wftype1[MAX_MATCH_FMT];/* actual wfmtype that match */
   int edgetp0[MAX_MATCH_FMT];/* actual edgtype that match if EdgeSet* (could be four edges)*/
   int edgetp1[MAX_MATCH_FMT];/* actual edgtype that match if EdgeSet* (could be four edges)*/
   int edgenum0[MAX_MATCH_FMT];/* Edge number 1-4 */
   int edgenum1[MAX_MATCH_FMT];/* Edge number 1-4 */
   int dset0cnt,dset1cnt;
   };

/* globals: */
#define MAXORIGINS 1000
#define ORIGINSIZE 200
#define ACTABLELEN 500
#define ACTABLELINES 5000
typedef struct ACWAVES {
   char w[ACTABLELINES+1][ACTABLELEN+1];
   } ACWAVES;
#define MAXCELLS 100000

#define MAXACTABLES 200
#define MAXACTABLENAMELEN 50
typedef struct ACTABLENAMES {
   char name[MAXACTABLES+1][MAXACTABLENAMELEN+1];
   } ACTABLENAMES;
#define FMTLEN 30
#define MAXCELLS 100000

/* extern refs to ggm_global.c: */
extern char EO[MAXORIGINS][ORIGINSIZE+1];
extern int EOCNT;

extern ACWAVES *acwaves;
extern ACWAVES *origins;
extern int orgcnt;
extern CELL_INFO *cellinfo;
extern int cellcnt;
extern ACTABLENAMES *actablenames;
extern int maxactablenames;
extern char wavetypes[][FMTLEN];
extern char edgetypes[][FMTLEN];
extern char GCTNAME[GCTSIZE];
extern char wavetypefull[];
extern char edgetypefull[];
extern int SIZE_WAVETYPES;
extern int SIZE_EDGETYPE;
extern char PIN[NUMPINS][PINSIZE];
extern int maxpin,groupcount,maxlists;
extern PINLIST *pinlist;
