/* gct_gen_mod_find_origin.c */
/* find_origin(){} */

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

int find_origin(char *WF, char org[MAX_EDGES + 1][WF_EXPR_LEN],
				int LASTSTART, char *from)
{
	int i, j, ret;
	char lvl, stprcdt[STARTSTOPCNT];
	/* first find the section code and its lvl */
	ret = local_origin(WF, org, LASTSTART, from);	/* check the exact section first */
	if (ret < 0) {
		return (ret);
	}
	lvl = startstop[LASTSTART].lvl;

	/* now find all prior pending lvls */
	for (j = lvl - '1'; j >= 0; j--) {
		for (i = LASTSTART - 1; i >= 0; i--) {
			/* must be a start and one for each lvl */
			if (startstop[i].type == SSSTART
				&& startstop[i].lvl == j + '0') {
				stprcdt[j] = startstop[i].cdtcode;
				break;			/* out of i loop */
			}
		}
	}
	/* now find the continuations of each lvl */
	for (j = lvl - '1'; j >= 0; j--) {
		for (i = LASTSTART + 1; i < maxstartstop; i++) {
			if (startstop[i].type == SSSTOP /* this was 's' change to SSTOP 10/23/2009 APS, needs verify!!! */
				&& startstop[i].cdtcode == stprcdt[j]) {
				ret = local_origin(WF, org, i - 1, from);
				if (ret < 0) {
					return (-10 + ret);
				}

			}
		}
	}
	return (0);
}

int local_origin(char *WF, char org[MAX_EDGES + 1][WF_EXPR_LEN],
				 int LASTSTART, char *from)
{
	int j, done, sl, eb, n, ESO, OS, ESOP, ERO, EOy, laststart;
	char *name, *ptr0, *ptr1, *ptr1C, *tptr,
		field[MAX_EDGES + 1][WF_EXPR_LEN], type[WF_EXPR_LEN], hold;
	for (n = 0; n < orgcnt; n++) {
		name = origins[n].w;
		laststart = origins[n].laststart;	/* while in this section */
		/* if there aren't any start/stops then we create ENORGS (specs etc) */
		if (LASTSTART == laststart || maxstartstop == 0);	/* process everything at the same level */
		else if (LASTSTART < laststart)
			break;				/* think we can exit early... */
		else
			continue;
		j = 0;
		ptr0 = strchr(name, '(');
		if (ptr0 == NULL) {
			fprintf(fperrors,
					"could not find '(' in [%s][%s], source[%s,%d,%s]\n",
					name, ptr0, __FILE__, __LINE__, __FUNCTION__);
			fprintf(stderr,
					"could not find '(' in [%s][%s], source[%s,%d,%s]\n",
					name, ptr0, __FILE__, __LINE__, __FUNCTION__);
			return (-1);
		}
		hold = *ptr0;
		*ptr0 = '\0';
		strcpy(type, name);
		*ptr0 = hold;
		ptr0++;
		eb = 0;
		done = 0;
		sl = strlen(name);
		ESO = OS = ESOP = ERO = 0;
		if (0 == strcmp(type, "EdgeSetOriginPinList"))
			ESOP = 1;
		else if (0 == strcmp(type, "EdgeSetOrigin"))
			ESO = 1;
		else if (0 == strcmp(type, "EdgeResetOrigin"))
			ERO = 1;
		else if (0 == strcmp(type, "OriginSet"))
			OS = 1;
		while (!done) {
			ptr1 = strchr(ptr0, ',');
			ptr1C = strrchr(ptr0, ')');
			if (ptr1 == NULL && ptr1C == NULL) {
				done = 1;
				break;
			}
			if (ptr1 == NULL && ptr1C != NULL)
				ptr1 = ptr1C;
			if (ptr1C < ptr1 && ptr1C != NULL) {
				ptr1 = ptr1C;
				done = 1;
			}					/* this is for the case when it finds a ',' after a ')'. e.g.: */
			//WaveSetNR(INT_CLKSTPdriveWF,0ns)elseWaveSetNR(INT_CLKSTPdriveWF,t[tcCI]-t[tsuINTCLKSTP]+dtcf+1ns)
			if (ptr1 == NULL)
				break;			/* in case there is nothing useful */
			if (ptr1 > name + sl)
				break;			/* in case there is nothing useful */
			hold = *ptr1;
			*ptr1 = '\0';
			strcpy(field[j], ptr0);
			*ptr1 = hold;
			while (NULL != (tptr = strstr(field[j], "div"))) {
				*tptr = ' ';	/* d */
				*(tptr + 1) = ' ';	/* i */
				*(tptr + 2) = '/';	/* v */
			}
			while (NULL != (tptr = strstr(field[j], "t["))) {
				*tptr = ' ';	/* t */
				*(tptr + 1) = ' ';	/* [ */
			}
			while (NULL != (tptr = strstr(field[j], "]"))) {
				*tptr = ' ';	/* ] */
			}
			ptr0 = ptr1 + 1;
			j++;
			if (done)
				break;
		}
		if (maxstartstop == 0)
			sprintf(type, "ENORG_%s", WF);
		EOy = 0;
		if (WF == NULL || field[0] == NULL) {
			fprintf(stderr, "WF or field is NULL!!!, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
			fprintf(stdout,
					"WF=%s,F[0]=%s,F[1]=%s,F[2]=%s,F[3]=%s, from=%s\n", WF,
					field[0], field[1], field[2], field[3], from);
			return (-2);
		}
		if (WF[0] == '\0' || field[0][0] == '\0') {
			fprintf(stderr, "WF or field is empty!!!, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
			fprintf(stdout,
					"WF[0]=%s,F[0]=%s,F[1]=%s,F[2]=%s,F[3]=%s, from=%s\n",
					WF, field[0], field[1], field[2], field[3], from);
			return (-3);
		}
		if (0 == strncmp(field[0], WF, WF_EXPR_LEN) && (ESO || ESOP)) {	/* OS set means assign value only so we ignore */
			if (0 == strcmp(field[1], "Edge1")) {
				if (maxstartstop == 0)
					sprintf(&org[1][0], "+%s*%s", field[2], type);
				else
					sprintf(&org[1][0], "+%s", field[2]);
				EOy = 1;
			}
			if (0 == strcmp(field[1], "Edge2")) {
				if (maxstartstop == 0)
					sprintf(&org[2][0], "+%s*%s", field[2], type);
				else
					sprintf(&org[2][0], "+%s", field[2]);
				EOy = 1;
			}
			if (0 == strcmp(field[1], "Edge3")) {
				if (maxstartstop == 0)
					sprintf(&org[3][0], "+%s*%s", field[2], type);
				else
					sprintf(&org[3][0], "+%s", field[2]);
				EOy = 1;
			}
			if (0 == strcmp(field[1], "Edge4")) {
				if (maxstartstop == 0)
					sprintf(&org[4][0], "+%s*%s", field[2], type);
				else
					sprintf(&org[4][0], "+%s", field[2]);
				EOy = 1;
			}
			if (0 == strcmp(field[1], "Edge5")) {
				if (maxstartstop == 0)
					sprintf(&org[5][0], "+%s*%s", field[2], type);
				else
					sprintf(&org[5][0], "+%s", field[2]);
				EOy = 1;
			}
		}
		if (EOy) {
			for (j = 0; j < EOCNT; j++)
				if (0 == strcmp(EO[j], type))
					break;		/* already exists!!! */
			if (j == EOCNT) {
				strcpy(EO[EOCNT], type);
				EOCNT++;
				if (EOCNT >= MAXORIGINS) {
					fprintf(stderr,
							"Too many origins!!!,holding..., source[%s,%d,%s]\n",
							__FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "Too many origins!!!,holding...\n");
					EOCNT = MAXORIGINS - 1;
				}
			}
		}
	}
	return (0);
}
