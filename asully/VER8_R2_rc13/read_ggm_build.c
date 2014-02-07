#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes_build.h"

int read_ggm(FILE * fpggm)
{
	char readstr[READLINELEN + 1];
	char *ptrplus, *ptrdot, *ptract;
	char *ptrOB, *ptrCB, *ptr;
	int sl, i, pos;

	while (fgets(readstr, READLINELEN - 1, fpggm) != NULL) {
		readstr[strlen(readstr) - 1] = '\0';	/* remove trailing \n */
		ptrdot = strchr(readstr, '.');
		ptrplus = strchr(readstr, '+');
		ptract = NULL;
		if (ptrdot != NULL && ptrplus != NULL) {
			ptract = (ptrplus < ptrdot) ? ptrplus : ptrdot;
		}
		if (strstr(readstr, "//ACT") != NULL && ptract != NULL) {
			/* //ACT+............. [TIsearchACTable][000] */
			ptrOB = strchr(ptract, '[');
			ptrCB = strchr(ptract, ']');
			if (ptrOB == NULL || ptrCB == NULL)
				error(ptract, __LINE__);
			*ptrCB = '\0';
			strcpy(Gcat[catcount].name, ptrOB + 1);
			sl = strlen(Gcat[catcount].name);
			if (sl > maxactlen)
				maxactlen = sl;
			Gcat[catcount].col = ptrplus - ptract;
			catcount++;
			if (catcount > MAXACTABLES)
				error("too many actables", __LINE__);
		}
		else if (strstr(readstr, "//ENUM") != NULL && ptract != NULL) {
			/* //ENUM                    +......................[Temp_N40_Degrees_C][000] */
			ptrOB = strchr(ptract, '[');
			ptrCB = strchr(ptract, ']');
			if (ptrOB == NULL || ptrCB == NULL)
				error(ptract, __LINE__);
			*ptrCB = '\0';
			strcpy(Genums[enumcount].name, ptrOB + 1);
			sl = strlen(Genums[enumcount].name);
			if (sl > maxenumlen)
				maxenumlen = sl;
			Genums[enumcount].col = ptrplus - ptract;
			enumcount++;
			if (enumcount > MAXENUMCODE)
				error("too many enums", __LINE__);
		}
		else if (strstr(readstr, "//DEVICE") != NULL && ptract != NULL) {	/* only one */
			/* //DEVICE               ..........++++......... */
			strcpy(ALLDEVICE, ptract);
		}
		else if (strstr(readstr, "//TEMP") != NULL && ptract != NULL) {	/* only one */
			/* //TEMP                    ++++++++++............. */
			strcpy(ALLTEMP, ptract);
		}
		else if (strstr(readstr, "//TEST") != NULL && ptract != NULL) {	/* only one */
			/* //TEST                    ..............+++++++++ */
			strcpy(ALLTEST, ptract);
		}
		else if (strstr(readstr, "//b") != NULL
				 && strstr(readstr, "UC[") != NULL) {
			/* //b1[11111111111111]E[11111111111111111111111]<000>UC[A] L[0008831]STR[STOP(ALLENUMS,ALLTABLES)] */
			strcpy(catcodes[codecnt], readstr);
			codecnt++;
			if (codecnt >= MAXCATCODE)
				error("too many catcodes", __LINE__);
		}
		else if (strstr(readstr, "//") != NULL
				 && strstr(readstr, "CAT[") != NULL) {
			/* //AB:CAT[TIsearchACTable] */
		}
		else if (strstr(readstr, "//end category grouping") != NULL) {
//          break;
		}
		else if (readstr[0] == '[') {
			strcpy(specs[maxspecs].expr, readstr);
			maxspecs++;
			if (maxspecs > MAXSPECS)
				error("too many specs", __LINE__);
		}
	}
	for (i = 0; i < enumcount; i++)
		OTHERENUM[i] = '+';
	OTHERENUM[i] = '\0';

	while (NULL != (ptr = strchr(ALLDEVICE, '+'))) {
		*ptr = '*';
		pos = (ptr - ALLDEVICE);
		*(OTHERENUM + pos) = '.';
		for (i = 0; i < enumcount; i++) {
			if (Genums[i].col == pos) {
				Genums[i].type = GE_DEVICE;
				break;
			}
		}
	}
	while (NULL != (ptr = strchr(ALLTEMP, '+'))) {
		*ptr = '*';
		pos = (ptr - ALLTEMP);
		*(OTHERENUM + pos) = '.';
		for (i = 0; i < enumcount; i++) {
			if (Genums[i].col == pos) {
				Genums[i].type = GE_TEMP;
				break;
			}
		}
	}
	while (NULL != (ptr = strchr(ALLTEST, '+'))) {
		*ptr = '*';
		pos = (ptr - ALLTEST);
		*(OTHERENUM + pos) = '.';
		for (i = 0; i < enumcount; i++) {
			if (Genums[i].col == pos) {
				Genums[i].type = GE_TEST;
				break;
			}
		}
	}
	while (NULL != (ptr = strchr(OTHERENUM, '+'))) {
		*ptr = '*';
		pos = (ptr - OTHERENUM);
		for (i = 0; i < enumcount; i++) {
			if (Genums[i].col == pos) {
				Genums[i].type = GE_OTHER;
				break;
			}
		}
	}

	fclose(fpggm);
	return (0);
}
