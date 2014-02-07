#include "includes_ggm.h"
#include "includes_build.h"

char ALLDEVICE[ENUMLEN + 1], ALLTEMP[ENUMLEN + 1], ALLTEST[ENUMLEN + 1],
	OTHERENUM[ENUMLEN + 1], OTHERENUM[ENUMLEN + 1];

GGMENUMS *Genums;
int enumcount = 0, maxenumlen = 0;

GGMCAT *Gcat;
int catcount = 0, maxactlen = 0;

SPECS *specs;
int maxspecs;

WFTREF *Gwftref;
int maxref=0;

/* in reality there can't be many more than 26+26 letters.... */
/* however, the letters can get reused. This is really how many STARTS exist */
/* C40 had 28, VC33 had 142... */
char catcodes[MAXCATCODE][2048 + 1], catstr[MAXCATCODE];

int codecnt = 0;
