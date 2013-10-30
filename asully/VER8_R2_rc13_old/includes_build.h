#include "common_includes.h"
#define READLINELEN 8000
#define MAXENUMCODE 200
#define MAXCATCODE 1000
#define PARAMLEN 50
#define MAXSPECS 8000
#define EXPRLEN 1000

extern char ALLDEVICE[ENUMLEN + 1], ALLTEMP[ENUMLEN + 1],
	ALLTEST[ENUMLEN + 1], OTHERENUM[ENUMLEN + 1];

typedef struct GGMENUMS {
	char name[ENUMLEN + 1];
	int col;					/* find the plus */
#define GE_DEVICE 1
#define GE_TEMP 2
#define GE_TEST 3
#define GE_OTHER 4
	int type;
} GGMENUMS;

typedef struct GGMCAT {
	char name[MAXACTABLENAMELEN + 1];
	int col;					/* find the plus */
} GGMCAT;

typedef struct SPECS {
	char expr[EXPRLEN + PARAMLEN + 1];
	char param[PARAMLEN + 1];
	char CODE, LVL, REF;
} SPECS;

typedef struct WFTREF {
	char wftref[MAXACTABLENAMELEN];
} WFTREF;
#define MAXREF 250

extern GGMCAT *Gcat;
extern GGMENUMS *Genums;
extern SPECS *specs;
extern WFTREF *Gwftref;

extern int enumcount, maxenumlen;
extern int catcount, maxactlen;
extern int maxspecs,maxref;


/* in reality there can't be many more than 26+26 letters.... */
/* however, the letters can get reused. This is really how many STARTS exist */
/* C40 had 28, VC33 had 142... */
extern char catcodes[MAXCATCODE][2048 + 1], catstr[MAXCATCODE];

typedef struct CATCODE {
	char cat[2048 + 1];
	char enums[2048 + 1];
	int el, bl, lvl;
	char ch;
	int fromtbl;
} CATCODE;


int codecnt;

/* functions: */
void error(char *ptr, int line);
int read_ggm(FILE * fpggm);
int write_params();
int read_pat_ref();
