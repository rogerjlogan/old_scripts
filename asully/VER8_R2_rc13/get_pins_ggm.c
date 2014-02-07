/* get_pins(){} get groups from files */

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

int get_pins(FILE * fpin2, FILE * fpin3, char *infile3, char *muxpin)
{
	char *ptr, *ptrEG, *ptrSP, *ptrEP, holdc;
	int i, j, k, actuallist, warnings = 0, EP, doitagain;
	char readstr[READLINELEN], pinname[READLINELEN + 1];
	char tempgrpexpand[READLINELEN * 20 + 1],tempgrpexpand2[READLINELEN * 20 + 1];
	for (i = 0; i < READLINELEN * 20 + 1; i++)tempgrpexpand[i] = tempgrpexpand2[i] = '\0';
	fprintf(stdout, "PROCESSING PINS\n");
	maxpin = maxdevpin = 0;
	while (fgets(readstr, READLINELEN - 1, fpin2) != NULL) {
		readstr[strlen(readstr) - 1] = '\0';	/* remove trailing \n */
		if (isalnum((int) readstr[0])) {
			for (i = 0, j = 0; i < strlen(readstr); i++)
				if (isgraph((int) readstr[i])) {
					PIN[maxpin][j] = readstr[i];
					j++;
				}
			PIN[maxpin++][j] = '\0';
		}
		if (maxpin == NUMPINS) {
			fprintf(stderr, "SE:MAXPIN exceeded, source[%s,%d,%s]\n",__FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "SO:** MAXPIN exceeded **\n");
			exit(2);
		}
	}
	fprintf(stdout, "MAXPIN=%d\n", maxpin);
	/* **** */
	for (i = 0; i < maxpin; i++) muxpin[i] = '.';
	while (fgets(readstr, READLINELEN - 1, fpin3) != NULL) {
		readstr[strlen(readstr) - 1] = '\0';	/* remove trailing \n */
		/* need to strip comments */
		if (strstr(readstr, "(*") != NULL || strstr(readstr, "*)") != NULL) {
			fprintf(stderr, "Please strip comments first in [%s]\n", infile3);
			fprintf(stderr, "Use nedit with RegExp search for:\\(\\*([^$]*)\\*\\)\n");
			fprintf(stderr, "and nothing in the replace with\n");
			fprintf(stderr, "Validate afterwards with normal seach for '(*' [the search above doesn't get multilines]\n");
			fprintf(stderr, "Sorry, this is easier than me figuring it out for you :-(, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
			exit(2);
		}
		if (NULL != strstr(readstr, "PinListSetNull"));	/* do nothing */
		else if (NULL != strstr(readstr, "EXCLUDE_THESE_GROUPS")) continue;			/* roger specific syntax */
		else if (NULL != strstr(readstr, "PinListSet")) {
			strcpy(tempgrpexpand, readstr);
			while ((ptr = strchr(readstr, ')')) == NULL) {
				fgets(readstr, READLINELEN - 1, fpin3);
				if (strstr(readstr, "(*") != NULL || strstr(readstr, "*)") != NULL) {
					fprintf(stderr, "Please strip comments first!\n");
					fprintf(stderr, "Use nedit with RegExp search for:\\(\\*([^$]*)\\*\\)\n");
					fprintf(stderr, "and nothing in the replace with\n");
					fprintf(stderr, "Sorry, this is easier than me figuring it out for you :-(, source[%s,%d,%s]\n",
						__FILE__, __LINE__, __FUNCTION__);
					exit(2);
				}

				strcat(tempgrpexpand, readstr);
			}
			for (j = i = 0; i < strlen(tempgrpexpand); i++) {	/* strip whitespace */
				if (isgraph((int) tempgrpexpand[i])) {
					tempgrpexpand2[j] = tempgrpexpand[i];
					j++;
				}
			}
			tempgrpexpand2[j] = '\0';
			ptr = strchr(tempgrpexpand2, '(');
			if (ptr == NULL) {
				fprintf(stderr,"NO OPEN PAREN in PinList [%s]\n",tempgrpexpand2);
				exit(1);
				}
			EP = 0;
			ptrEG = strchr(tempgrpexpand2, ',');
			if (ptrEG == NULL) {
				EP = 1;
				fprintf(stdout,"Found empty pin group [%s]\n",tempgrpexpand2);
				ptrEG = strchr(tempgrpexpand2,')');
				if (ptrEG == NULL) {
					fprintf(stderr,"%s Can't deal with [%s]\n",tempgrpexpand2,__FILE__);
					exit(1);
					}
				else {holdc = *ptrEG; *ptrEG = '\0';}
				}
			else {holdc = *ptrEG; *ptrEG = '\0'; }

			actuallist = maxlists;
			for (i = 0; i < maxlists; i++) {
				if (strcmp(pinlist[i].pinlistname, ptr + 1) == 0) {
					fprintf(fperrors, "**** WARNING: duplicate pinlist [%s] [%s]\n",
						ptr + 1, pinlist[i].pinlistname);
					warnings = 1;
					actuallist = i;
					break;
				}
			}
			
			if (actuallist == maxlists) { /* means we didn't find it already */
				pinlist[actuallist].pinlistname[0] = '\0';
				for (i = 0; i < maxpin; i++) pinlist[actuallist].pinlists[i] = '.';
				pinlist[actuallist].pinlists[i] = '\0';
				pinlist[actuallist].groups[0] = '\0';
				strcpy(pinlist[actuallist].pinlistname, ptr + 1);	/* copy in the groupname */
				fprintf(fpstatus,"GROUP[%d][%s]\n",maxlists,ptr + 1);
			}
			if (ptrEG != NULL) {*ptrEG = holdc; ptrSP = ptrEG+1;}

			while (EP == 0 && NULL != (ptrEP = strchr(ptrSP, ','))) {
				if (ptrEP == NULL) break;
				else {holdc = *ptrEP; *ptrEP = '\0';}
				strcpy(pinname, ptrSP);
				for (i = 0; i < maxpin; i++) {
					if (strcmp(PIN[i], pinname) == 0) {
						pinlist[actuallist].pinlists[i] = '*';
						break;
					}
				}
				if (i == maxpin && actuallist == maxlists) {
					strcat(pinlist[actuallist].groups, ptrSP);	/* not a pin */
					strcat(pinlist[actuallist].groups,","); /* force a comma */
					}
				*ptrEP = holdc; /* reset above with holdc now */
				ptrSP = ptrEP+1;
			}
			ptrEP = strchr(ptrSP, ')'); /* last pin */
			if (EP == 0 && ptrEP == NULL) {
				fprintf(stderr,"OOPS no Pinlist() close parenthesis found in [%s]\n",tempgrpexpand2);
				exit(1);
				}
			if (EP == 0) {
				holdc = *ptrEP; *ptrEP = '\0';
				strcpy(pinname, ptrSP);
				for (i = 0; i < maxpin; i++) {
					if (strcmp(PIN[i], pinname) == 0) {
						pinlist[actuallist].pinlists[i] = '*';
						break;
						}
					}
				}
			if (actuallist == maxlists) {
				if (EP == 0 && i == maxpin) {
					strcat(pinlist[actuallist].groups, ptrSP);	/* not a pin */
					strcat(pinlist[actuallist].groups,","); /* force a comma */
					}
				maxlists++;
				if (maxlists == MAXlists) {
					fprintf(stderr, "maxlists exceeded, source[%s,%d,%s]\n",
						__FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "maxlists exceeded\n");
					exit(2);
					}
				}
			if (EP == 0) *ptrEP = holdc;
			}

		else if (NULL != (ptr = (strstr(readstr, "PinSetMux")))) {	/* this will also find "PinSetMuxMP" & "PinSetMuxPP" */
			for (j = i = 0; i < strlen(readstr); i++) {	/* strip whitespace */
				if (isgraph((int) readstr[i])) {
					tempgrpexpand2[j] = readstr[i];
					j++;
				}
			}					/* end strip white space */
			ptrSP = strchr(tempgrpexpand2, '(');
			ptrEP = strchr(tempgrpexpand2, ',');
			if (ptrSP != NULL && ptrEP != NULL) {
				ptrSP++;
				fprintf(stdout, "found MUX![%s]\n", ptrSP);
				holdc = *ptrEP; *ptrEP = '\0';
				for (i = 0; i < maxdevpin; i++)
					if (0 == strcmp(ptrSP, DEVPIN[i])) break;
				if (i == maxdevpin) {	/* new pin def */
					strcpy(DEVPIN[maxdevpin], ptrSP);
					maxdevpin++;
					if (maxdevpin >= NUMPINS) {
						fprintf(stderr, "Too many pins from device file[%d] %s %d\n", maxdevpin,__FILE__,__LINE__);
						fprintf(fperrors, "Too many pins from device file[%d], source[%s,%d,%s]\n",
								maxdevpin, __FILE__, __LINE__, __FUNCTION__);
						exit(1);
					}
				}
				for (i = 0; i < maxpin; i++)
					if (0 == strcmp(ptrSP, PIN[i])) {
						muxpin[i] = 'M';
						break;
					}
				}
			}			/* else pinsetMux */
		else if (NULL != (ptr = (strstr(readstr, "PinSetNoTDR"))));	/* nothing to do */
		else if (NULL != (ptr = (strstr(readstr, "PinSet")))) {	/* this will find "PinSetMP" & "PinSetPP" */
			for (j = i = 0; i < strlen(readstr); i++) {	/* strip whitespace */
				if (isgraph((int) readstr[i])) {
					tempgrpexpand2[j] = readstr[i];
					j++;
				}
			}					/* end strip white space */
			ptrSP = strchr(tempgrpexpand2, '(');
			ptrEP = strchr(tempgrpexpand2, ',');
			if (ptrSP != NULL && ptrEP != NULL) {
				ptrSP++;
				holdc = *ptrEP; *ptrEP = '\0';
				for (i = 0; i < maxdevpin; i++)
					if (0 == strcmp(ptrSP, DEVPIN[i])) break;
				if (i == maxdevpin) {	/* new pin def */
					strcpy(DEVPIN[maxdevpin], ptrSP);
					fprintf(fpstatus,"PIN[%s]\n",DEVPIN[maxdevpin]);
					maxdevpin++;
					if (maxdevpin >= NUMPINS) {
						fprintf(stderr, "Too many pins from device file[%d] %s %d\n", maxdevpin,__FILE__,__LINE__);
						fprintf(fperrors, "Too many pins from device file[%d], source[%s,%d,%s]\n",
								maxdevpin, __FILE__, __LINE__, __FUNCTION__);
						exit(1);
					}
				}
			}
		}		/* else pinset */

	}
	/* this replaces any pingroups that are subcomponents of other pingroups with the individual pins */
	/* LOCATE SEE_FORCE_COMMA */
	for (doitagain = 0 ; doitagain <= 3; doitagain++) { /* need to run this more than once for out of order recursion */
		for (i = 0; i < maxlists; i++) {
			if (pinlist[i].groups[0] == '\0') continue;
			ptrSP = pinlist[i].groups;
			while (NULL	!=	(ptrEG = strchr(ptrSP, ','))) { /* always ending with ',' even if there is only one */
				holdc = *ptrEG;
				*ptrEG = '\0'; 
				for (j = 0; j < maxlists; j++) {
					if (j == i) continue;
					if (strcmp(ptrSP, pinlist[j].pinlistname) == 0) {
						for (k = 0; k < maxpin; k++)
							if (pinlist[j].pinlists[k] == '*') {
								pinlist[i].pinlists[k] = '*';
							}
						}
					}
				*ptrEG = holdc;
				ptrSP = ptrEG+1;
				} /* end while */
			}
		}
	fprintf(stderr, "GOOD! got groups!, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
/* do a pin validation */
	for (j = 0; j < maxpin; j++) PIN2DEV[j] = -1;
	for (j = (maxpin - 1); j > 0; j--)
		if (PIN[j][0] == '\0') maxpin--;
	for (j = (maxdevpin - 1); j > 0; j--)
		if (DEVPIN[j][0] == '\0') maxdevpin--;
	for (i = 0; i < maxdevpin; i++) {
		DEV2PIN[i] = -1;
		for (j = 0; j < maxpin; j++) {
			if (0 == strcmp(DEVPIN[i], PIN[j])) break;
		}
		if (j == maxpin) {
			fprintf(stdout, "Warning:device file pin[%s] does not exist in pinlist.txt file (could be ok), source[%s,%d,%s]\n",
					DEVPIN[i], __FILE__, __LINE__, __FUNCTION__);
			fprintf(fpstatus, "Warning:device file pin[%s] does not exist in pinlist.txt file (could be ok), source[%s,%d,%s]\n",
					DEVPIN[i], __FILE__, __LINE__, __FUNCTION__);
		}
		else {
			PIN2DEV[j] = i;
			DEV2PIN[i] = j;
		}
	}
	for (j = 0; j < maxpin; j++) {
		if (PIN2DEV[j] == -1) {
			fprintf(stdout, "Warning:pinlist.txt file pin[%s] does not exist in device file, source[%s,%d,%s]\n",
					PIN[j], __FILE__, __LINE__, __FUNCTION__);
			fprintf(fpstatus, "Warning:pinlist.txt file pin[%s] does not exist in device file, source[%s,%d,%s]\n",
					PIN[j], __FILE__, __LINE__, __FUNCTION__);
		}
	}
	if (warnings == 1)
		fprintf(stderr, "**********\n**** WARNING: duplicate pinlists see translation_errors.txt, source[%s,%d,%s] ***\n**********\n",
				__FILE__, __LINE__, __FUNCTION__);
	/* **** */
//	for (i = 0; i < maxlists; i++) {
//		fprintf(stdout, "%*s  [%s]", -10, "PINGROUP", pinlist[i].pinlists);
//		fprintf(stdout, "(*%s*)", pinlist[i].pinlistname);
//		fprintf(stdout, "{%s}\n", pinlist[i].groups);
//	}

	return (0);
}
