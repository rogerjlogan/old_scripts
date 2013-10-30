#include <stdio.h>
#include "common_includes.h"
#define REV 18.0

#ifndef __GNUC__
#include "local_date.h"
#define __TIME__ ""
#endif

#define MAXCPMTODPMLINES 100
#define MAXCPMOPTLINES 1000
#define READLINELEN 2000
#define MULTILINESIZE 32767
#define MULTILINESIZEBIG 200000
#define FILENAMELEN 120
#define MAXWAVE 5000
#define MAXCYCLE 2000
#define MAXPINS 400
#define MAXGCT 150
#define MAXGCTLEN 200
#define MAXALIAS 200
#define MAXPINLEN 10
#define MAXERRORLEN 1025
#define MAXRPT 2000
#define VECTORLEN 256
#define MAXMSET 256
#define MAXDSET 256
#define MAXISET 256
#define MAXMODGCT 200
#define MEMOSTRLEN 256
#define MAXGCTDSET 200
#define DPM_COUNT_file "DpM_CoUnT"
#define PAT_REF_FILE "translation_patref.txt"

#define DFLTSGHDR "SH0"
/* from vector_convert_scan2.c, for optimization */
#define MAXSIGHDRLEN 25
/* #define NORMALSGHDR "SH0" */
#define NO_DMI "NO_DMI"
#define NO_WFT "NO_WFT"
#define NO_VECTOR "NO_VECT"
#define NO_COMMENT "NO_COMM"
#define NO_MICROINSTR "NO_MICRO"

#define NO_REPEAT 1
#define VECTOR_DONE -1
#define VECTOR_FLUSH -2
#define VECTOR_DONT_PRINT -3
#define MAX_RPT_CPM 65535
#define MAX_RPT_DPM 2047
typedef int boolean;
#define  TRUE 1
#define FALSE 0

#define DEF_WFT "DEF_WFT"
#define PUSHBACK_CYCLE "PUSHBACK_CYCLE"
char REMAP_DEF_WFT[MAXGCTLEN + 1];

struct SETvS {
	char *MSETPTR, *DSETPTR, *ISETPTR, *WFT, GCTMODNAME[MAXMODGCT][MAXGCTLEN + 1];
	char VECTMOD[2][MAXMODGCT][MAXPINS + 1];
	int maxgctDSET;
	int used[MAXMODGCT];
};
extern struct SETvS SETS;

struct FILETABLE {
	char *vect, *vecte;
	char *wftref, *wftrefe;
	char *sighdr, *sighdre;
	char *microinstr, *microinstre;
	char *comment, *commente;
};

typedef struct PBSET {
	char WFTREF[MAXGCTLEN + 1];
	char DSET0[MAXPINS + 1];
	char DSET1[MAXPINS + 1];
	} PBSET;
extern int maxpb;
extern PBSET *pbset;

//typedef FILETABLE TD_FILETABLE;

/* function prototypes */
int outputvector(FILE * fpout1, char *out_vector, char *WFT, char *DMI, long repeatcount, char *comment, char *microinstr, int CPM,int line);
int outputvector_evX2(FILE * fpout1, char *out_vector, char *WFT, char *DMI, long repeatcount, char *comment, char *microinstr, int CPM, char *pb_vector,int line);
char *get_count(char *ptr, int offset, long *count, int call);
int deal_with_shutdown(char *line, char *ptr, FILE * fpin1, char *pb_vector);
int deal_with_comment(FILE * fpout1, char *mod_vector, char *comment, int *commentcount, int *commentflag, int *commentON, int vectorflag);
int check_SET(int beginflag, char *mod_vector, const char *SET, int *notgood, int MAX, char SETPTR[]);
int vector_convert(int *beginflag, char *vector, char *mod_vector, struct SETvS *SETS, char *out_vector1, char *DMI, char *pb_vector);
int cpmoptimize(char *pattern);
int pare_comment(char *newcomment, char *oldcomment);
int read_gct_dset_info (char *readstr, char *name, char *gctD0, char *gctD1, int *count, int maxv);

/* special shared functions: */
int alias_vcpvcs(int vect, int vmset, int vdset, int dset0val, int dset1val,int priorstate);
int chksumout(FILE * fpout1, char *open, char *close);

#define NUMPINS 1026
#define PINSIZE 50
#define RET_FOREVER -1

extern boolean DEBUG;			/* off by default */
extern char progstr[MEMOSTRLEN], datestr[MEMOSTRLEN], timestr[MEMOSTRLEN], compilestr[MEMOSTRLEN], mydate[101];	/* concaternated strings */
extern char env[READLINELEN + 1], *endptr;

extern boolean QUIET;
extern boolean SUPPRESS_COMMENTS;
extern boolean REPEAT_COMPRESSION;
extern int CPM, found_shut;
extern char dummy_vector[MULTILINESIZE], cpmdpm_vector[MULTILINESIZE],EVX2VECT[MULTILINESIZE];
/* the following are globabls for convenience in functions */
extern FILE *fperrors, *tempfile, *fpstatus, *fppatref;
extern char infile_orig[FILENAMELEN];
extern long readlinenum, VC, VN, VNIR, countrpts;

extern char username[MEMOSTRLEN], hostname[MEMOSTRLEN], pwd[MEMOSTRLEN];
extern char tempgunzipname[FILENAMELEN];
extern int gzip, gunzip;
extern char NORMALSGHDR[MAXSIGHDRLEN + 1];
extern int MOD2_SIZE;


extern int pinheadcount;
extern char pinhead[PINSIZE][NUMPINS];
extern char priorstate[NUMPINS+1],priorvect[NUMPINS+1];
extern int EVX2,NOEVX2,NOMUX;
/* had to make the following global so other routines could output the shutdown: */
extern char vector_shut1[MULTILINESIZE], vector_shut2[MULTILINESIZE];
