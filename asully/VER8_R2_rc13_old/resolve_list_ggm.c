/* resolve_list(){} process envision type pinlists from cycletbl */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "includes_ggm.h"

int resolve_list(char *PINLIST, char *PINBINARY, char YES, char NO, int pinorder[NUMPINS]) {
	int pin, group, roger = 0, len, done, foundsomething = 0, pincount = 0;
	char *ptr1, *ptr2, *ptrT;
	char pinorgroup[100], PINLISTCOPY[5000];
//   fprintf(stderr,"Entering resolve list!!!, source[%s,%d,%s]\n",__FILE__,__LINE__,__FUNCTION__);
	for (pin = 0; pin < maxpin; pin++) {
		PINBINARY[pin] = NO;
		pinorder[pin] = -1;
	}
	PINBINARY[maxpin] = '\0';

	len = strlen(PINLIST);
	/* pad it with a plus so the last group works */
	PINLIST[len] = '+';
	PINLIST[len + 1] = '\0';
	strcpy(PINLISTCOPY, PINLIST);
	ptr1 = PINLIST;
	while ((NULL != (ptr2 = strchr(ptr1, '+')))) {
		done = 0;
		roger++;
		*ptr2 = '\0';
		strcpy(pinorgroup, ptr1);
		*ptr2 = '+';
		for (group = 0; group < maxlists && done == 0; group++) {
			if (strcmp(pinorgroup, pinlist[group].pinlistname) == 0) {
				for (pin = 0; pin < maxpin; pin++) {
					if (pinlist[group].pinlists[pin] == '*') {
						PINBINARY[pin] = YES;
						done = 1;
						foundsomething = 1;
						pinorder[pin] = pincount++;
					}
				}
			}
		}
		for (pin = 0; pin < maxpin && done == 0; pin++) {
			if (strcmp(pinorgroup, PIN[pin]) == 0) {
				PINBINARY[pin] = YES;
				done = 1;
				foundsomething = 1;
				pinorder[pin] = pincount++;
			}
		}
		if (done == 1) {
			for (ptrT = ptr1; ptrT <= ptr2; ptrT++) {
				*(PINLISTCOPY + (ptrT - PINLIST)) = ' ';
			}
		}
		else {
			*ptr2 = '\0';
			PINLIST[len] = '\0';	/* fix it back before printing */
			PINLISTCOPY[len] = '\0';	/* fix it back before printing */
			fprintf(stderr, "[%s] was neither a pin or a group in ", ptr1);
			*ptr2 = '+';
			fprintf(stderr, " [%s]\nDid you leave it out of pinlist.txt? source[%s,%d,%s]\n",
					PINLIST, __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "[%s]\n First Non-whitespace was neither a pin or a group in [%s]\n",
					PINLISTCOPY, PINLIST);
			exit(1);
			roger = -1;
		}
		ptr1 = ptr2 + 1;
	}
	if (foundsomething == 0) {
		PINLIST[len] = '\0';	/* fix it back before printing */
		PINLISTCOPY[len] = '\0';	/* fix it back before printing */
		fprintf(stderr, "No pins or groups found in [%s], source[%s,%d,%s]\n",
				PINLIST, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "No pins or groups found in [%s]\n,skipping this group/information!\n",
				PINLIST);
		roger = -1;
	}
	PINLIST[len] = '\0';
	roger--;
//   fprintf(fpstatus,"RC%d<PINLIST:%s>\n",roger,PINLIST);
//   fprintf(fpstatus,"<PINBIN :%s>\n",PINBINARY);
//   fprintf(stderr,"Done resolve list!!!, source[%s,%d,%s]\n",__FILE__,__LINE__,__FUNCTION__);
	return (roger);
}
