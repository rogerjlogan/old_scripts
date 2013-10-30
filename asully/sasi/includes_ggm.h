/* gct_gen_mod_includes.h */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "common_includes.h"

#define DEBUG 0

#define READLINELEN 8000
#define CYCBUFFSIZE READLINELEN*1000
#define FILENAMELEN 120
#define MEMOSTRLEN 1024
#define NUMPINS 1026
#define PINSIZE 2048
#define GCTSIZE 120
#define MAXlists 2000
#define WF_EXPR_LEN 1000

#define MAX_EDGES 6
#define FINDME_SIZE 4000

#define PBCYC "PUSH_CYC"
#define PBWFT "zpbMIStrobeOffEdges"
#define PBEDGES "zpbStrobeOffEdges"
#define PBCOMMON "zpb_COMMON"

#define MAX_MOD_CODES 25
#define MC_DUPE '!'
struct MODCODE {
	int ALLD0[MAX_MOD_CODES + 1];
	int ALLD1[MAX_MOD_CODES + 1];
	int D0cnt;
	int D1cnt;
	int D0c;
	int D1c;
	int cellcntD0[MAX_MOD_CODES + 2];	/* plus 2 for 'after' cellcnt */
	int cellcntD1[MAX_MOD_CODES + 2];
} MODCODE;

#define MAX_CELLLEN 100
#define MAX_CELLPINLEN 2048

enum PT {
	PT_NOPROBLEM,
	PT_CONTINUE,
	PT_CLOSE,
	PT_CLOSEOFF,
	PT_CLOSEOPEN,
	PT_CLOSEFLOATOPEN,
	PT_OFFOPEN,
	PT_OFFCLOSE,
	PT_OFFFLOATOPEN,
	PT_OPEN,
	PT_FLOATOPEN
};

typedef struct CELL_INFO {
	long filepos;				/* for fseek/ftell */
	int multidefnum;
	int formatnum;
	int actline;
	int formats[MAX_EDGES];
	int dupnum;
	char cdtcode, alias0, alias1,alias6,alias7;
	char cdtstr[MAX_MOD_CODES + 1];
	char wftname[MAX_CELLLEN];
	char cellname[MAX_CELLLEN];
	char pin[PINSIZE];
	char cellexpr[20 * READLINELEN + 1];
	int problemtype;
} CELL_INFO;
extern CELL_INFO *cellinfo;
extern int cellcnt, worstcasecellcnt;
#define MAXCELLS 1000

typedef struct PARAM_INFO {
	int actline, used;
	char param_def[MAX_CELLLEN];
	char cdtcode;
} PARAM_INFO;

extern PARAM_INFO *paraminfo;
extern int paramcnt;
#define MAX_PARAMS 20000

typedef struct PINLIST {
	char pinlistname[READLINELEN + 1];	/* name of the pingroup */
	char pinlists[NUMPINS + 1];	/* when complete, this will be asterisks for any pins existing in the group */
	char groups[READLINELEN + 1];	/* this is for groups inside groups, i.e. things that are not pins */
} PINLIST;
extern PINLIST *pinlist;
extern int maxdevpin, maxpin, groupcount, maxlists;

#define MAXCYCSETS 20000
#define CYCLEN 50
typedef struct CYCSETMD {
	char tblname[CYCLEN + 1];
	char dset0[CYCLEN + 1], dset1[CYCLEN + 1];
	char pin[READLINELEN + 1];
} CYCSETMD;
extern CYCSETMD *cycsets;
extern int maxcycset;

#define MAXCYCROWS 400
#define MAXCYCTBL 400
typedef struct CYCTBL {
	char tblname[CYCLEN + 1];
	int rows[MAXCYCROWS], maxrow, valid[MAXCYCROWS];
} CYCTBL;
extern CYCTBL *cyctbl;
extern int maxtbl;

#define MAXVMS 200
typedef struct vectormapsets {
	char name[READLINELEN + 1];	/* name of the scan header */
	int field;					/* order */
	char pinlist[NUMPINS + 1];
	int type;					/* hex or bin, see below */
	int scan;					/* see below */
	int scanset;				/* different for each header */
	int scanpin;				/* pin number */
} VMS;
extern VMS vmsets[MAXVMS];
extern int maxvmsets, VMparallel, VMfields;	/* number of vmsets and the parallel one */
#define VMSBINARY 1
#define VMSHEX 2
#define VMSPARALLEL 0
#define VMSSCANIN 1
#define VMSSCANOUT 2
#define VMSSCANOTHER 3

#define MAX_MATCH_FMT 50
struct FORMAT_SEARCH {
	int wfmln0[MAX_MATCH_FMT];	/* all DSET0 waveforms that match */
	int wfmln1[MAX_MATCH_FMT];	/* all DSET0 waveforms that match */
	int wftype0[MAX_MATCH_FMT];	/* actual wfmtype that match */
	int wftype1[MAX_MATCH_FMT];	/* actual wfmtype that match */
	int edgetp0[MAX_MATCH_FMT];	/* actual edgtype that match if EdgeSet* (could be four edges) */
	int edgetp1[MAX_MATCH_FMT];	/* actual edgtype that match if EdgeSet* (could be four edges) */
	int edgenum0[MAX_MATCH_FMT];	/* Edge number 1-4 */
	int edgenum1[MAX_MATCH_FMT];	/* Edge number 1-4 */
	int dset0cnt, dset1cnt;
};

/* globals: */
#define MAXORIGINS 1000
#define ORIGINSIZE 200
#define ACTABLELEN 2000
#define ACTABLELINES 5000
typedef struct ACWAVES {
	char w[ACTABLELEN + 1];
	int loc, laststart;
} ACWAVES;
extern ACWAVES *acwaves;
extern ACWAVES *origins;

typedef struct ACTABLENAMES {
	char name[MAXACTABLES + 1][MAXACTABLENAMELEN + 1];
} ACTABLENAMES;
extern ACTABLENAMES *actablenames;
extern int maxactablenames;
#define FMTLEN 30

/* this is for A-Z,a-z,0-9  we could add '_' but.... */
#define STARTSTOPCNT 26+26+10
#define STARTSTOPCNTPRE 400
extern char alphabet[STARTSTOPCNT + 1];
#define MAXENUMS 100
typedef struct STARTSTOP {
	int loc, line;
#define SSSTART 'b'
#define SSSTOP 'e'
	int startpt2stop;
	int ucat, udev, utst, utmp, urem;
	char type;					/* 'b' for start, 'e' for stop */
	char lvl;					/* '0' for current */
	char cdtcode;
	char enumtype[MAXENUMS + 1], cattype[MAXACTABLES + 1];
	char expr[READLINELEN + 1];
} STARTSTOP;
extern STARTSTOP startstop[STARTSTOPCNTPRE];
extern int maxstartstop;
extern char ENUMS[MAXENUMS][ENUMLEN + 1];
extern int maxenums;

/* extern refs to ggm_global.c: */
extern char EO[MAXORIGINS][ORIGINSIZE + 1];
extern int EOCNT;

extern int orgcnt;
extern int cellcnt;
extern char wavetypes[][FMTLEN];
extern char edgetypes[][FMTLEN];
extern char wavetypefull[];
extern char edgetypefull[];
extern int SIZE_WAVETYPES;
extern int SIZE_EDGETYPE;
extern char PIN[NUMPINS][PINSIZE];
extern char DEVPIN[NUMPINS][PINSIZE];
extern int PIN2DEV[NUMPINS], DEV2PIN[NUMPINS];

extern FILE *fperrors, *fpstatus, *fppreopt;

extern char *cyclebuff;
// this is for strcat to the cyclebuff....
extern char *SCATcycle;
// this is for remove_dupe_cells() paired with SCATcycle
extern char *REMOVEDUPE;

extern char tperiod[50];

extern int WARNING;

#define actablebufsize 60000
#define inheritbufsize 60000
#define actablelistsize 60000

extern int LASTI;
extern int ACTABLE, ACDATA;
extern int G_maxdev, G_maxtmp, G_maxtst, G_maxrem;
extern char enumstr[50][100];
extern int EVX2, PBSTROBE, PBCLOSE, NOPUSHCYC, NOMUX, MUXFLAG;

/* function prototypes: */

int read_cycletbl(char *fname);
int make_hexmuxlist(FILE * fp_mod_file, char *muxpin, int maxcyclen);
int make_scan_headers(FILE * fp_mod_file, char *muxpin);
int add_cyclesetMD(char *ptrfind);
int add_cycleset(char *ptrfind);
int compact_cycletbl();
int add_vectormapset(char *readstr);
int parse_cyctbl(int actablelines, char *infile4, FILE * fpwaves,
				 FILE * fpinherit, FILE * fp_mod_file, int maxcyclen, char *muxpin);
int purge_actable(FILE * fpinherit, FILE *fp_mod_file, char *muxpin);

int separate_actable(char *actablebuf, char *inheritbuf, char *actablelist, struct MODCODE *mc);
int add_to_inherit(char *cellname, char *cnstptr, char *inheritbuff);
int remove_dupe_cells(char *cyclebuff, struct MODCODE *mc);

int parse_actable(char *fname, FILE * fpwaves);
int process_waveforms(int actablelines, char *GCTNAME, char *cyclebuff, long *tell, int which,
		 int *forward, char *pin, int DSET, int CNT, int *modcode);
int process_edgesetdelay_waveform(int actablelines, char *GCTNAME, char *cyclebuff, long *tell, int which,
		 int *forward, char *pin, int DSET, int CNT, int *modcode, char name[][FINDME_SIZE + 1], int en[], int enable_edge[]);
int break_up_edges(int actablelines, int en[], int enable_edge[], char name[][FINDME_SIZE + 1], char *temp, int which, int *forward);
int reduce_expressions(int ne, int en[], char name[][FINDME_SIZE + 1], char field[][100][WF_EXPR_LEN]);
int edgeset_make_wfms(char *cyclebuff, char field[MAX_EDGES + 1][100][WF_EXPR_LEN], int en[MAX_EDGES + 1], int ne, int neST,
		 char org[MAX_EDGES + 1][WF_EXPR_LEN], int DSET, int delay[], int nDELAYDATA[MAX_EDGES + 1]);
int mod_add_close_ESD(char field[][100][WF_EXPR_LEN],
		 char org[][WF_EXPR_LEN], int nDELAYDATA[], int en[], int ne, int neST, int formatpick[], int delay[]);
int chk_problem_type(int code, int lcoden[],  char field[][100][WF_EXPR_LEN], char *GCTNAME, char *dupwarn);

/* EdgeSetDelayPinList(wave,edge,edgetype,time,delay,pinlist) */
/* EdgeSetDelayDataPinList(wave,edge,chan,edgetype0,vth0,time0,delay0,edgetype1,vth1,time1,delay1,pinlist) */
#define MF_EDGESETDATA 12
#define MF_EDGESET 6

int find_origin(char *WF, char org[MAX_EDGES + 1][WF_EXPR_LEN], int LASTSTART, char *from);	/* a wrapped to get all pending lvls */
int local_origin(char *WF, char org[MAX_EDGES + 1][WF_EXPR_LEN], int LASTSTART, char *from);
int get_pins(FILE * fpin2, FILE * fpin3, char *infile3, char *muxpin);
int resolve_list(char *PINLIST, char *PINBINARY, char YESCHAR, char NOCHAR, int pinorder[NUMPINS]);
int write_partial(char *actablein, off_t filesize);
int write_params();
int write_paramsINHC();
