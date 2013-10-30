#include <stdio.h>
#include "common_includes.h"

#define DEFAULT_SCAN_OPT "./CPM_SCAN_OPT "
/* C6203 defines */
#define FIND_SIGHDR_IN "ScanInOrder"
#define FIND_SIGHDR_OUT "ScanOutOrder"
#define MAXSCANORDERLEN 25
#define MAXSCANHDRLEN 30
#define FIND_CYCLE_HOLD "ScanCycle"
#define ASSUMED_DSET 1
#define MAXMODGCT 100

#define DRIVEold_HIGH_ALIAS 'H'
#define DRIVEold_LOW_ALIAS 'L'
#define DRIVEold_HIGH_ALIAS2 'h'
#define DRIVEold_LOW_ALIAS2 'l'
#define COMPAREold_HIGH_ALIAS '1'
#define COMPAREold_LOW_ALIAS '0'
#define COMPAREold_HIGH_ALIAS2 'i'
#define COMPAREold_LOW_ALIAS2 'o'
#define DONT_CAREold_ALIAS 'X'
#define DONT_CAREold_ALIAS2 '.'

#define HOLD_CYCLE "HOLD_CYCLE"

#define BEEP 0x07
#define FILENAMELEN 120
#define VECTORLEN 400
#define MULTILINESIZE 70000
#define READLINELEN 70000
#define GENERALBUFLEN 32767
#define MAXSCANLEN 65535
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
#define MAXGCTLEN 25
#define MAXALIAS 33
#define MAXPINLEN 10
#define MAXMSET 256
#define MAXDSET 256
#define MAXISET 256
#define MAXHDRLEN 32
#define MAXSCANHDRS 64
#define MAXSCANNUM 16
#define MAXSCANTBLLEN 800 /* was 60 */
#define SCANPINNUM 50
#define MAXSCANPINS 64
#define NUMPINS 1026
#define MAXREPFOREVER 2
#define MAXREPFOREVERLINES 20
#define VECTOR 1
#define STRING 2
#define LABEL 3

#define REFISVECT 1
#define REFISSCAN 2

typedef struct SCAN_INFO {
	char scanpinname[MAXSCANPINS][SCANPINNUM + 1];
	char scanhdr[MAXHDRLEN + 1];
	int index[MAXSCANPINS], shlen, scanpins;
} SCAN_INFO;

extern SCAN_INFO G_scandata[MAXSCANHDRS];
extern int G_scanhdrs;

extern char G_HOLD_VECTOR[NUMPINS];
extern char G_DPM_VECTOR[NUMPINS];
extern char G_SCANHOLD[NUMPINS];

extern int G_QUIET, NOMUX;
extern FILE *fperrors, *fpstatus, *fpsignalheaders, *fppatref;
extern char G_infile1[FILENAMELEN];
extern long G_readlinenum;
extern long G_cyclecount, G_vectorcount;
extern char G_progstr[MEMOSTRLEN], G_datestr[MEMOSTRLEN], G_timestr[MEMOSTRLEN];
extern char G_compilestr[MEMOSTRLEN];	/* concaternated strings */
extern char G_username[MEMOSTRLEN], G_hostname[MEMOSTRLEN], G_pwd[MEMOSTRLEN];
extern int G_SCANINPIN;			/* TDI */
extern int G_SCANOUTPIN;		/* TDO */
extern char G_NORMALSGHDR[MAXSIGHDRLEN];
extern int G_MOD2_SIZE;
extern int G_pinheadcount;
extern char G_pinhead[SCANPINNUM][NUMPINS];
extern char G_GCTMODNAME[MAXMODGCT][MAXGCTLEN];
extern int G_GCTMODUSED[MAXMODGCT];
extern char G_VECTD0[MAXMODGCT][MAXPINS + 1], G_VECTD1[MAXMODGCT][MAXPINS + 1];
extern char G_SCANPIN[MAXSCANHDRS][MAXPINLEN + 1];
extern int G_maxgctSET;
extern char priorstate[MAXPINS+1];

/* function prototypes */
void outputvector(FILE * fpout1, int *lastitem, char *out_vector,
				  char *pattern, char *WFT, char *DMI, long VN,
				  int repeatcount, char *errorstr, char *comment);
int parse_mod_file(char *infile2);

/* special shared functions: */
int alias_vcpvcs(int vect, int vmset, int vdset, int dset0val, int dset1val,int priorstate);
int chksumout(FILE * fpout1, char *open, char *close);
