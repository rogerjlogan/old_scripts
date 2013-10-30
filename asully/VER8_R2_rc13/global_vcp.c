#include "include_vcp.h"
/* global vars:*/

boolean DEBUG = FALSE;			/* off by default */
char progstr[MEMOSTRLEN], datestr[MEMOSTRLEN], timestr[MEMOSTRLEN], compilestr[MEMOSTRLEN], mydate[101];	/* concaternated strings */
char env[READLINELEN + 1], *endptr;

boolean QUIET = TRUE;
boolean SUPPRESS_COMMENTS = FALSE;
boolean REPEAT_COMPRESSION = TRUE;
int CPM = 0, found_shut = 0;
char dummy_vector[MULTILINESIZE], cpmdpm_vector[MULTILINESIZE],EVX2VECT[MULTILINESIZE];
/* the following are globabls for convenience in functions */
FILE *fperrors, *tempfile, *fpstatus, *fppatref;
char infile_orig[FILENAMELEN];
long readlinenum = 0, VC, VN = 0, VNIR = 0, countrpts = 0;

char username[MEMOSTRLEN], hostname[MEMOSTRLEN], pwd[MEMOSTRLEN];
char tempgunzipname[FILENAMELEN];
int gzip = 0, gunzip = 0;
char NORMALSGHDR[MAXSIGHDRLEN + 1];
int MOD2_SIZE;

struct SETvS SETS;
struct PBSET *pbset;
int maxpb;

int pinheadcount = 0;
char pinhead[PINSIZE][NUMPINS];
char REMAP_DEF_WFT[MAXGCTLEN + 1];
char priorstate[NUMPINS+1],priorvect[NUMPINS+1];
int EVX2 = 0,NOEVX2 = 0,NOMUX = 0;
/* had to make the following global so other routines could output the shutdown: */
char vector_shut1[MULTILINESIZE], vector_shut2[MULTILINESIZE];
