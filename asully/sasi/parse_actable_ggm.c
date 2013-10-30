/* gct_gen_mod_parse_actable.c parse_actable() {} */

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

#define MAXLVL 50

int parse_actable(char *fname, FILE * fpwaves)
{
	FILE *fpin, *fpenums, *fpinhcontrol;
	char *cstptr, *cendptr, *actablein, *mytable, *ptrOP, *ptrCL, *ptrfind;
	char *ptrELSE;
	char readstr[READLINELEN + 1], readstr2[READLINELEN + 1], readstrSP[READLINELEN + 1];
	char an1[MAXACTABLENAMELEN + 1], an2[MAXACTABLENAMELEN + 1];
	char an3[MAXACTABLENAMELEN + 1], an4[MAXACTABLENAMELEN + 1], an5[MAXACTABLENAMELEN + 1];
	int cdtcount, laststart, found;
	int goodtbl, goodenum, gcedev, gcetmp, gcetst;
	int i, j, k, ret, sp, spSP, fmcnt, pos;
	int discardwhendone, start, lvl, maxlvl = 0, startstack[MAXLVL];
	int lastwasbndry, inenum, line;
	char holdenum[MAXENUMS + 1];
	int udevt, utstt, utmpt, ucatt, uremt;
	char alltemp, alltest, alldevice, *ptrPRECAT, *ptr, *ptrend;
	struct stat statbuf;
	off_t filesize;

/* these are for the subcomponents of enums */
	char ALLDEVICE[ENUMLEN + 1], ALLTEMP[ENUMLEN + 1], ALLTEST[ENUMLEN + 1], ALLENUMS[ENUMLEN + 1];

/* these are for unique checking */
	char ucattype[STARTSTOPCNTPRE][MAXACTABLES + 1];
	char devtype[STARTSTOPCNTPRE][MAXENUMS + 1], tsttype[STARTSTOPCNTPRE][MAXENUMS + 1];
	char tmptype[STARTSTOPCNTPRE][MAXENUMS + 1], remtype[STARTSTOPCNTPRE][MAXENUMS + 1];

/* these are for optimization */
	int optcat, optdev, opttst, opttmp, optrem, validchk;
	struct list {
		int cat, dev, tst, tmp, rem;
	} optlist[STARTSTOPCNTPRE + 1];
	int optlistcnt = 0;
	char INH_CONTROL[500];

	strcpy(INH_CONTROL, INHCONTROL);
	if (ACDATA == 1) {
		strcpy(INH_CONTROL, DATACONTROL);
		fprintf(stdout, "Outputting to [%s]\n", INH_CONTROL);
	}

	if (NULL == (fpinhcontrol = fopen(INH_CONTROL, "w"))) {
		fprintf(stderr, "\nCan't open file [%s], source[%s,%d,%s]\n", INH_CONTROL, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nCan't open file [%s]\n", INH_CONTROL);
		exit(1);
	}

/* open and read enums.evo, needed for case/if START/STOP parsing... */
	if (NULL == (fpenums = fopen(ENUMSFILE, "r"))) {
		fprintf(stderr, "\nInput file [%s] not found, source[%s,%d,%s]\n", "enums.evo", __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nInput file [%s] not found\n", "enums.evo");
		exit(1);
	}

/* read in enums */
	for (i = 0; i < ENUMLEN; i++) ALLDEVICE[i] = ALLTEMP[i] = ALLTEST[i] = '0';
	ALLDEVICE[ENUMLEN] = ALLTEMP[ENUMLEN] = ALLTEST[ENUMLEN] = '\0';
	alldevice = alltemp = alltest = '0';
	inenum = 0;
	G_maxdev = G_maxtmp = G_maxtst = G_maxrem = 0;
	while (fgets(readstr, READLINELEN - 1, fpenums) != NULL) {
		readstr[strlen(readstr) - 1] = '\0';	/* remove trailing \n */
		if (strstr(readstr, "enum") != NULL) {
			/* only these three have an ALLNNNN definition, any others MUST be explicit. */
			/* these will also pickup TITestTemp,TIDeviceType, and TITestType */
			alltemp = alldevice = alltest = '.';
			if (strstr(readstr, "TestTemp") != NULL) {
				alltemp = '+';
				alldevice = alltest = '.';
			}
			else if (strstr(readstr, "DeviceType") != NULL) {
				alldevice = '+';
				alltemp = alltest = '.';
			}
			else if (strstr(readstr, "TestType") != NULL) {
				alltest = '+';
				alldevice = alltemp = '.';
			}
			else {
				strcpy(enumstr[G_maxrem], &readstr[sizeof("enum")]);	/* FIXME APS: Needs more work! */
				ptr = strchr(enumstr[G_maxrem], ' ');
				if (ptr != NULL) *ptr = '\0';
				G_maxrem++;
			}
			inenum = 1;
		}
		else if (strchr(readstr, '{') != NULL) continue;
		else if (strchr(readstr, '}') != NULL) inenum = 0;
		else if (inenum == 1) {
			for (i = 0, j = 0; i < strlen(readstr); i++) {
				if (readstr[i] == ' ' || readstr[i] == '\t' || readstr[i] == ',') continue;
				else readstr2[j++] = readstr[i];
			}
			readstr2[j] = '\0';
			if (strlen(readstr2) > ENUMLEN) {
				fprintf(stderr, "enum[%s] is too long for buffer of size [%d]. Truncating....,source[%s,%d,%s]\n",
						readstr, ENUMLEN, __FILE__, __LINE__, __FUNCTION__);
				fprintf(fperrors, "enum[%s] is too long for buffer of size [%d]. Truncating....\n",
						readstr, ENUMLEN);
				readstr[ENUMLEN] = '\0';
			}
			/* write in bits for which ever one is currently active */
			ALLDEVICE[maxenums] = alldevice;
			if (alldevice == '+') G_maxdev++;
			ALLTEMP[maxenums] = alltemp;
			if (alltemp == '+') G_maxtmp++;
			ALLTEST[maxenums] = alltest;
			if (alltest == '+') G_maxtst++;
			ALLENUMS[maxenums] = '1';
			strcpy(ENUMS[maxenums], readstr2);
			maxenums++;
			if (maxenums > MAXENUMS) {
				fprintf(stderr, "Too many enums[%d] at [%s]. Exiting....,source[%s,%d,%s]\n",
						maxenums, readstr, __FILE__, __LINE__, __FUNCTION__);
				fprintf(fperrors, "Too many enums[%d] at [%s]. Exiting....\n", maxenums, readstr);
				exit(1);
			}
		}
		else;					/* this is for un-identified sections */
	}
	fclose(fpenums);
	ALLDEVICE[maxenums] = ALLTEMP[maxenums] = ALLTEST[maxenums] = ALLENUMS[maxenums] = '\0';
	ret = stat(fname, &statbuf);
	if (ret == 0) filesize = statbuf.st_size;
	else {
		fprintf(stderr, "Can't determine filesize for [%s], source[%s,%d,%s]\n", fname, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Can't determine filesize for [%s]\n", fname);
		exit(1);
	}

	if (NULL == (fpin = fopen(fname, "r"))) {
		fprintf(stderr, "\nInput file [%s] not found, source[%s,%d,%s]\n", fname, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nInput file [%s] not found\n", fname);
		exit(1);
	}
	fprintf(fpstatus, "SIZEOF(ACWAVES)=%d, source[%s,%d,%s]\n", sizeof(ACWAVES), __FILE__, __LINE__, __FUNCTION__);
	fprintf(fpstatus, "ACTABLELINES=%d, source[%s,%d,%s]\n", ACTABLELINES + 1, __FILE__, __LINE__, __FUNCTION__);
	acwaves = (ACWAVES *) calloc(ACTABLELINES + 1, sizeof(ACWAVES));
	if (acwaves == NULL) {
		fprintf(stderr, "Could not allocate memory for acwaves in [%s], source[%s,%d,%s]\n", fname, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Could not allocate memory for acwaves in [%s]\n", fname);
		exit(1);
	}
	fprintf(fpstatus, "allocated [%d] bytes for acwaves @%p, source[%s,%d,%s]\n",
			(ACTABLELINES + 1) * sizeof(ACWAVES), acwaves, __FILE__, __LINE__, __FUNCTION__);

	origins = (ACWAVES *) calloc(ACTABLELINES + 1, sizeof(ACWAVES));
	if (origins == NULL) {
		fprintf(stderr, "Could not allocate memory for origins in [%s], source[%s,%d,%s]\n", fname, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Could not allocate memory for origins in [%s]\n", fname);
		exit(1);
	}
	fprintf(fpstatus, "allocated [%d] bytes for origins @%p, source[%s,%d,%s]\n",
			(ACTABLELINES + 1) * sizeof(ACWAVES), origins, __FILE__, __LINE__, __FUNCTION__);

	actablenames = (ACTABLENAMES *) calloc(MAXACTABLES + 1, MAXACTABLENAMELEN + 1);
	if (actablenames == NULL) {
		fprintf(stderr, "Could not allocate memory for actablenames in [%s],source[%s,%d,%s]\n",
				fname, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Could not allocate memory for actablenames in [%s]\n", fname);
		exit(1);
	}
	fprintf(fpstatus, "allocated [%d] bytes for actablenames @%p,source[%s,%d,%s]\n",
			(MAXACTABLES + 1) * (MAXACTABLENAMELEN + 1), actablenames, __FILE__, __LINE__, __FUNCTION__);

	actablein = malloc((size_t) (filesize + 1));
	if (actablein == NULL) {
		fprintf(stderr, "Could not allocate memory for [%s] file in memory, source[%s,%d,%s]\n",
				fname, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Could not allocate memory for [%s] file in memory\n", fname);
		exit(1);
	}
	for (i = 0; i < filesize + 1; i++) *(actablein + i) = '\0';
	fprintf(fpstatus, "allocated [%ld] bytes for actablein, source[%s,%d,%s]\n",
			filesize, __FILE__, __LINE__, __FUNCTION__);

	fread(actablein, (size_t) filesize, 1, fpin);
	fclose(fpin);

	actablein[filesize] = '\0';	/* just to make sure */
	pos = 0;
	mytable = actablein;

/* Clear the comments */
	fprintf(stdout, "Erasing actable comments...\n");
	while (pos < filesize && (cstptr = strstr(mytable, "(*")) != NULL) {
		cendptr = strstr(mytable, "*)");
		while (cstptr <= (cendptr + 1)) {	/* +1 => get '(' through the ')' */
			if (*cstptr == '\n') cstptr++;		/* don't erase the carriage returns so we can still track lines */
			else *cstptr++ = ' ';
			pos = cstptr - actablein;
		}
		mytable = cendptr + 1;
	}
//fprintf(stdout,"END (**)%d->%ld\n",mytable-actablein,(long)filesize);
	pos = 0;
	mytable = actablein;
	while (pos < filesize && (cstptr = strstr(mytable, "{")) != NULL) {
		cendptr = strstr(mytable, "}");
		while (cstptr <= (cendptr)) {	/* no +1 for '{' '}' */
			if (*cstptr == '\n') cstptr++;		/* don't erase the carriage returns so we can still track lines */
			else *cstptr++ = ' ';
			pos = cstptr - actablein;
		}
		mytable = cendptr + 1;
	}
//fprintf(stdout,"END {}%d->%ld\n",mytable-actablein,(long)filesize);
	fprintf(stdout, "Done erasing actable comments...\n");

	maxactablenames = 0;
	maxstartstop = start = 0;

	write_partial(actablein, filesize);

	discardwhendone = 0;
	readstr[0] = '\0';
	lastwasbndry = 0;
	laststart = -1;				/* in case we don't find any */
	fmcnt = sp = spSP = pos = 0;
	line = 1;
	while (pos < filesize) {
		/* The next line will force a ';' if we close a function but forget the semi-colon */
		/* We ignore this if the last close is a comment. This is primarily intended for the */
		/* START/STOP addin functions to mark conditional sections. */
		/* protect against long lines: */
		if (sp > READLINELEN) {
			fprintf(stderr, "There's a really long unterminated statement in the actable file, source: source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
			fprintf(stderr, "(carriage returns get removed causing wrap)\n");
			fprintf(stderr, "which doesn't get a semi-colon within [%d] bytes.\n", READLINELEN);
			fprintf(stderr, "You'll need to do something with this line...\n");
			fprintf(stderr, "The string starts with [%60.60s]\n", readstr);
			exit(1);
		}
		if (actablein[pos] == '\n') {
			line++;
			actablein[pos] = ' ';
		}
//  fputc(actablein[pos],stdout);fflush(stdout);
		if (pos > 1 && actablein[pos] == ')' && actablein[pos + 1] == '\n') {
			/* this is if a function missed a ';' after it, replace the carriage return with the ';' */
			if (actablein[pos - 1] != '*') actablein[pos + 1] = ';';
			line++;
		}
		else if (pos > 1 && actablein[pos] == ')'
				 && actablein[pos - 1] != '*'
				 && actablein[pos + 1] == ' ') {
			/* this is if a function missed a ';' after it and has spaces..., */
			/* replace the carriage return with the ';' */
			for (i = 1; actablein[pos + i] == ' '; i++);
			if (actablein[pos + i] == '\n') {
				actablein[pos + 1] = ';';
				line++;
				actablein[pos + i] = ' ';
			}
		}
/* move the semicolon forward if there is a space in front of it */
		if (pos > 1 && actablein[pos] == ';' && actablein[pos - 1] == ' ') {
			while (actablein[pos - 1] == ' ') {
				actablein[pos - 1] = ';';
				actablein[pos] = ' ';
				pos--;
			}
		}

		if ((ptrELSE = strstr(readstr, "else")) != NULL) {
			pos--;
//      line--;
			actablein[pos--] = ' ';
			actablein[pos--] = ' ';
			actablein[pos--] = ' ';
			actablein[pos--] = ';';
			*(ptrELSE + 1) = *(ptrELSE + 2) = *(ptrELSE + 3) = ' ';
			sp -= 4;
			spSP -= 4;
			*ptrELSE = ';';
		}
		else if ((ptrELSE = strstr(readstr, "then")) != NULL) {
			pos--;
//      line--;
			actablein[pos--] = ' ';
			actablein[pos--] = ' ';
			actablein[pos--] = ' ';
			actablein[pos--] = ';';
			*(ptrELSE + 1) = *(ptrELSE + 2) = *(ptrELSE + 3) = ' ';
			sp -= 4;
			spSP -= 4;
			*ptrELSE = ';';
		}
		else if ((ptrELSE = strstr(readstr, "begin")) != NULL) {
			pos--;
//      line--;
			if (ptrELSE == readstr || *(ptrELSE-1) == ':' || *(ptrELSE-1) == 'o') { /* last is 'do begin' */
				actablein[pos--] = ' ';
				actablein[pos--] = ' ';
				actablein[pos--] = ' ';
				actablein[pos--] = ' ';
				actablein[pos--] = ';';
				*(ptrELSE + 1) = *(ptrELSE + 2) = *(ptrELSE + 3) = *(ptrELSE + 4) = ' ';
				sp -= 5;
				spSP -= 5;
				*ptrELSE = ';';
				}
			else {
				fprintf(stdout,"WRONG \"begin\" REPLACE![%s]\n",readstr);
				*ptrELSE = '~';
				actablein[pos - 4] = '~';
				pos++;
				}
			}
		else if ((ptrELSE = strstr(readstr, "end")) != NULL) {
			pos--;				/* ends almost always have semicolons */
			if (actablein[pos] == 'd' && actablein[pos - 1] == 'n'
				&& actablein[pos - 2] == 'e' && ptrELSE == readstr) {
				actablein[pos] = ' ';
				actablein[pos - 1] = ' ';
				actablein[pos - 2] = ' ';
				*(ptrELSE + 1) = *(ptrELSE + 2) = ' ';
				*ptrELSE = ' ';
				sp -= 3;
				spSP -= 3;
			}
			else {
				fprintf(stdout,"WRONG \"end\" REPLACE![%s]\n",readstr);
//				fprintf(stdout, "WRONG \"end\" REPLACE![%c%c%c]\n",
//						actablein[pos - 2], actablein[pos - 1], actablein[pos]);
				*ptrELSE = '~';
				actablein[pos - 2] = '~';
				pos++;
			}
		}
		else if (isspace(actablein[pos])) {
			pos++;
			readstrSP[spSP++] = ' ';
			readstrSP[spSP] = '\0';
		}						/* don't store if white space */
		else if (actablein[pos] != ';') {
			readstrSP[spSP++] = readstr[sp++] = actablein[pos];
			pos++;
			readstrSP[spSP] = readstr[sp] = '\0';	/* keep it permanently terminated, for debug etc */
		}
		else if (actablein[pos] == ';') {	/* found end of statement */
			if (readstr[0] == '\0' || readstr[0] == '\n') {
				readstrSP[0] = readstr[0] = '\0';
				spSP = sp = 0;	/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
			else if (strstr(readstr, ":=") != NULL) {	/* this is for equations */
//          fprintf(fpstatus,"EQUATION[%s]\n",readstr);
				strcpy(paraminfo[paramcnt].param_def, readstr);
				paraminfo[paramcnt].actline = line;
				paramcnt++;
				if (paramcnt > MAX_PARAMS) {
					fprintf(stderr, "Too many ac_parameters, Exiting[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "Too many ac_parameters, Exiting[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					exit(1);
				}
				readstrSP[0] = readstr[0] = '\0';
				spSP = sp = 0;	/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
			else if (NULL != (ptrfind = strstr(readstr, "PeriodSetAll"))) {
				ptrOP = strchr(ptrfind, '(');
				ptrCL = strchr(ptrfind, ')');
				j = 0;
				if (ptrOP != NULL && ptrCL != NULL) {
					ptrOP++;
					while (ptrOP < ptrCL) {
						tperiod[j] = *ptrOP;
						if (*ptrOP == '[') {	/* wipe out t[ */
							tperiod[j - 1] = ' ';
							tperiod[j] = ' ';
						}
						else if (*ptrOP == ']') {	/* wipe out ] */
							tperiod[j] = ' ';
						}
						j++;
						ptrOP++;
					}
				}
				tperiod[j] = '\0';
				readstrSP[0] = readstr[0] = '\0';
				spSP = sp = 0;	/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
			else if (NULL != (ptrfind = strstr(readstr, "procedureTIACTableSet"))) {
				/* skip if its the procedure definition */
				readstrSP[0] = readstr[0] = '\0';
				spSP = sp = 0;	/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
			else if (NULL != (ptrfind = strstr(readstr, "TIACTableSet")) ||
					 NULL != (ptrfind = strstr(readstr, "TITimingSet"))) {
				ptrOP = strchr(readstr, '(');
				ptrCL = strchr(readstr, ')');
				j = 0;
				if (ptrOP != NULL && ptrCL != NULL) {
					ptrOP++;
					while (ptrOP < ptrCL) {
						actablenames->name[maxactablenames][j] = *ptrOP;
						j++;
						ptrOP++;
					}
				}
				actablenames->name[maxactablenames][j] = '\0';
				maxactablenames++;
				if (maxactablenames >= MAXACTABLES) {
					fprintf(stderr, "Too many actables %d in [%s], near [%s], source[%s,%d,%s]\n",
							maxactablenames, fname, readstr, __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "Too many actables %d in [%s], near [%s]\n", maxactablenames, fname, readstr);
					exit(1);
				}
				readstrSP[0] = readstr[0] = '\0';
				spSP = sp = 0;	/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
			else if (NULL != (ptrfind = strstr(readstrSP, "START")) ||
					 NULL != (ptrfind = strstr(readstrSP, "STOP"))) {
				startstop[start].loc = pos - strlen(readstrSP);
				startstop[start].line = line;
				strcpy(startstop[start].expr, ptrfind);
				if (NULL != strstr(readstrSP, "START"))
					laststart = start;
				if (start == maxstartstop) {
					maxstartstop++;
					start++;
					if (maxstartstop > STARTSTOPCNTPRE) {
						fprintf(fperrors, "Too many STARTSTOPS %d in [%s], near [%s]\n", maxstartstop, fname, readstrSP);
						fprintf(stderr, "Too many STARTSTOPS %d in [%s], near [%s], source[%s,%d,%s]\n",
								maxstartstop, fname, readstrSP, __FILE__, __LINE__, __FUNCTION__);
						exit(1);
					}
				}
				else start++;	/* if for some reason there are more stops so far than starts */
				readstrSP[0] = readstr[0] = '\0';
				spSP = sp = 0;	/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
			else if (NULL != (ptrfind = strstr(readstr, "~="))) {
				/* this was changed above from ':=', assignment, ignore... */
				readstrSP[0] = readstr[0] = '\0';
				spSP = sp = 0;	/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
			else if (NULL != (ptrfind = strstr(readstr, "OriginSet")) ||
					 NULL != (ptrfind = strstr(readstr, "EdgeSetOrigin")) ||
					 NULL != (ptrfind = strstr(readstr, "EdgeResetOrigin"))) {
				strcpy(origins[orgcnt].w, readstr);
				origins[orgcnt].loc = pos - sp;
				origins[orgcnt].laststart = laststart;
				orgcnt++;
				if (orgcnt >= ACTABLELINES) {
					fprintf(stderr, "Too many origins %d in [%s], near [%s], source[%s,%d,%s]\n",
							orgcnt, fname, readstr, __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "Too many origins %d in [%s], near [%s]\n",
							orgcnt, fname, readstr);
					exit(1);
				}
				readstrSP[0] = readstr[0] = '\0';
				spSP = sp = 0;	/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
			else {				/* write it to acwaves */
				strcpy(acwaves[fmcnt].w, readstr);
//          fprintf(stdout,"VV[%s]\n",acwaves[fmcnt].w);
				acwaves[fmcnt].loc = pos - sp;
				acwaves[fmcnt].laststart = laststart;
				fmcnt++;
				if (fmcnt >= ACTABLELINES) {
					fprintf(stderr, "Too many lines %d in [%s], near [%s], source[%s,%d,%s]\n",
							fmcnt, fname, readstr, __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "Too many lines %d in [%s], near [%s]\n", fmcnt, fname, readstr);
					exit(1);
				}
				readstrSP[0] = readstr[0] = '\0';
				spSP = sp = 0;	/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
		}						/* found end of statement */
	}							/* while */

	for (i=0; i < fmcnt; i++) {
		if ((ptrend = strstr(acwaves[i].w,"~nd")) != NULL) {
			fprintf(stdout,"BACKREPLACE[%s]\n",acwaves[i].w);
			*ptrend = 'e';
			}
		if ((ptrend = strstr(acwaves[i].w,"~egin")) != NULL) {
			fprintf(stdout,"BACKREPLACE[%s]\n",acwaves[i].w);
			*ptrend = 'b';
			}
		}

	fprintf(stderr, "Completely processed %d items from %s, source[%s,%d,%s]\n",
			fmcnt, fname, __FILE__, __LINE__, __FUNCTION__);
	if (DEBUG)
		for (i = 0; i < fmcnt; i++)
			fprintf(stdout, "%07d_%s\n", acwaves[i].loc, acwaves[i].w);
	fprintf(stdout, "-------------------------------------\n");
	lvl = '0';
	cdtcount = 0;

/* first actables */
	for (i = 0; i < maxactablenames; i++) readstr[i] = '.';
	readstr[i] = '\0';
	fprintf(fpinhcontrol, "//begin category strings\n");
	for (i = 0; i < maxactablenames; i++) {
		readstr[i] = '+';
		fprintf(fpinhcontrol, "//ACT%s [%s][%03d]\n", readstr, actablenames->name[i], i);
		readstr[i] = '.';
	}
	fprintf(fpinhcontrol, "//end category strings\n");
	fprintf(fpstatus, "There are %d ACcategories\n", maxactablenames);
	fprintf(stderr, "There are %d ACcategories, source[%s,%d,%s]\n",
			maxactablenames, __FILE__, __LINE__, __FUNCTION__);

/* now enums */
	for (i = 0; i < maxenums; i++) readstr[i] = '.';
	readstr[i] = '\0';
	fprintf(fpinhcontrol, "//begin enum strings\n");
	for (i = 0; i < maxactablenames; i++) {
		readstr2[i] = ' ';
		fprintf(fpstatus, "ACTABLE[%d][%s]\n", i, actablenames->name[i]);
	}
	readstr2[i] = '\0';
	fprintf(fpinhcontrol, "//DEVICE%s%s\n", readstr2, ALLDEVICE);
	fprintf(fpinhcontrol, "//TEMP  %s%s\n", readstr2, ALLTEMP);
	fprintf(fpinhcontrol, "//TEST  %s%s\n", readstr2, ALLTEST);
	for (i = 0; i < maxenums; i++) {
		readstr[i] = '+';
		fprintf(fpinhcontrol, "//ENUM%s  %s[%s][%03d]\n", readstr2, readstr, ENUMS[i], i);
		readstr[i] = '.';
	}
	fprintf(fpinhcontrol, "//end enum strings\n");

	fprintf(fpinhcontrol, "//begin category markers\n");
	for (i = 0; i < maxstartstop; i++) {
		j = 0;
		while (actablein[startstop[i].loc + j] != ';') j++;
		actablein[startstop[i].loc + j] = '\0';
//  strcpy(startstop[i].expr,&actablein[startstop[i].loc]);
		actablein[startstop[i].loc + j] = ';';
		startstop[i].type = 'X';
		if (strstr(startstop[i].expr, "START") != NULL) {
			startstop[i].type = SSSTART;
			lvl++;
			startstack[lvl - '0'] = i;
		}
		if (strstr(startstop[i].expr, "STOP") != NULL) {
			startstop[i].type = SSSTOP;
			lvl--;
		}
		if ((lvl - '0') > maxlvl) maxlvl = lvl - '0';
		startstop[i].lvl = lvl;

		/* first, initialize the categories and enums to all zero */
		for (k = 0; k < maxactablenames; k++) startstop[i].cattype[k] = '0';
		for (k = 0; k < maxenums; k++) startstop[i].enumtype[k] = '0';
		/* then, if the ALLnnn for its type exist set them all to one */
		if (maxactablenames < 1) {
			fprintf(stdout, "No categories logged... Did you include the ACTableSet statements????\n");
			fprintf(fperrors, "No categories logged... Did you include the ACTableSet statements????\n");
			fprintf(fpinhcontrol, "//No categories logged... Did you include the ACTableSet statements????\n");
		}
		if (strstr(startstop[i].expr, "ALLTABLES") != NULL) {
			for (k = 0; k < maxactablenames; k++) startstop[i].cattype[k] = '1';
		}
		else if (strstr(startstop[i].expr, "ALLTABLE") != NULL) {
			fprintf(stderr, "Incorrect usage:ALLTABLE, Correct syntax is: ALLTABLES,fix and re-run, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
		}
		else if (strstr(startstop[i].expr, "ALLACTABLE") != NULL) {
			fprintf(stderr, "Incorrect usage:ALLACTABLE(S), Correct syntax is: ALLTABLES,fix and re-run, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
		}
		if (strstr(startstop[i].expr, "ALLENUMS") != NULL) {
			for (k = 0; k < maxenums; k++) startstop[i].enumtype[k] = '1';
		}
		else if (strstr(startstop[i].expr, "ALLENUM") != NULL) {
			fprintf(stderr, "Incorrect usage:ALLENUM, Correct syntax is: ALLENUMS,fix and re-run, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
		}
		if (strstr(startstop[i].expr, "ALLTEMPS") != NULL) {
			for (k = 0; k < maxenums; k++)
				if (ALLTEMP[k] == '+') startstop[i].enumtype[k] = '1';
		}
		else if (strstr(startstop[i].expr, "ALLTEMP") != NULL) {
			fprintf(stderr, "Incorrect usage:ALLTEMP, Correct syntax is: ALLTEMPS,fix and re-run, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
		}
		if (strstr(startstop[i].expr, "ALLTESTS") != NULL) {
			for (k = 0; k < maxenums; k++)
				if (ALLTEST[k] == '+') startstop[i].enumtype[k] = '1';
		}
		else if (strstr(startstop[i].expr, "ALLTEST") != NULL) {
			fprintf(stderr, "Incorrect usage:ALLTEST, Correct syntax is: ALLTESTS,fix and re-run, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
		}
		if (strstr(startstop[i].expr, "ALLDEVICES") != NULL) {
			for (k = 0; k < maxenums; k++)
				if (ALLDEVICE[k] == '+') startstop[i].enumtype[k] = '1';
		}
		else if (strstr(startstop[i].expr, "ALLDEVICE") != NULL) {
			fprintf(stderr, "Incorrect usage:ALLDEVICE, Correct syntax is: ALLDEVICES,fix and re-run, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
		}
		for (goodtbl = k = 0; k < maxactablenames; k++) {
			strcpy(an1, actablenames->name[k]);
			strcpy(an2, an1);
			strcpy(an3, an1);
			strcpy(an4, an1);
			strcpy(an5, an1);
			strcat(an1, ",");
			strcat(an4, "+");
			strcat(an2, ")");
			strcat(an5, " ");
			strcat(an3, "-");	/* if its ALLTABLES-n1-n2-n3) (specifically n1 or n2) */
			/* separate ifs needed due to the need for the PRECAT pointer */
			if ((ptrPRECAT = strstr(startstop[i].expr, an1)) != NULL)
				startstop[i].cattype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			else if ((ptrPRECAT = strstr(startstop[i].expr, an5)) != NULL)
				startstop[i].cattype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			else if ((ptrPRECAT = strstr(startstop[i].expr, an4)) != NULL)
				startstop[i].cattype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			else if ((ptrPRECAT = strstr(startstop[i].expr, an2)) != NULL)
				startstop[i].cattype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			else if ((ptrPRECAT = strstr(startstop[i].expr, an3)) != NULL)
				startstop[i].cattype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			if (startstop[i].cattype[k] == '1') {
				goodtbl++;
			}
		}
		startstop[i].cattype[k] = '\0';

/* now enums */
		for (goodenum = gcedev = gcetmp = gcetst = k = 0; k < maxenums; k++) {
			strcpy(an1, ENUMS[k]);
			strcpy(an2, an1);
			strcpy(an3, an1);
			strcpy(an4, an1);
			strcpy(an5, an1);
			strcat(an1, ",");
			strcat(an4, "+");
			strcat(an2, ")");
			strcat(an5, " ");
			strcat(an3, "-");	/* if its ALLENUMS-n1-n2-n3) (specifically n1 or n2) */
			/* separate ifs needed due to the need for the PRECAT pointer */
			if ((ptrPRECAT = strstr(startstop[i].expr, an1)) != NULL)
				startstop[i].enumtype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			else if ((ptrPRECAT = strstr(startstop[i].expr, an4)) != NULL)
				startstop[i].enumtype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			else if ((ptrPRECAT = strstr(startstop[i].expr, an5)) != NULL)
				startstop[i].enumtype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			else if ((ptrPRECAT = strstr(startstop[i].expr, an2)) != NULL)
				startstop[i].enumtype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			else if ((ptrPRECAT = strstr(startstop[i].expr, an3)) != NULL)
				startstop[i].enumtype[k] = (*(ptrPRECAT - 1) == '-') ? '0' : '1';
			if (startstop[i].enumtype[k] == '1') {
				goodenum++;
			}
			if (ALLDEVICE[k] == '+' && startstop[i].enumtype[k] == '1') gcedev++;
			if (ALLTEMP[k] == '+' && startstop[i].enumtype[k] == '1') gcetmp++;
			if (ALLTEST[k] == '+' && startstop[i].enumtype[k] == '1') gcetst++;
		}
		startstop[i].enumtype[k] = '\0';
		if (goodtbl == 0) {
			fprintf(fperrors, "BAD START/STOP, No ACTABLE found line[%d], fix and re-run, see %s:\n%s\n",
					startstop[i].line, INH_CONTROL, startstop[i].expr);
			fprintf(stdout, "*** BAD START/STOP, No ACTABLE found line[%d]***, fix and re-run, see %s\n",
					startstop[i].line, INH_CONTROL);
		}
		if (goodenum == 0) {
			fprintf(fperrors, "BAD START/STOP, No ENUM found line[%d], fix and re-run, see %s:\n%s\n",
					startstop[i].line, INH_CONTROL, startstop[i].expr);
			fprintf(stdout, "*** BAD START/STOP, No ENUM found line[%d] ***, fix and re-run, see %s\n",
					startstop[i].line, INH_CONTROL);
		}
		if (gcedev == 0) {
			fprintf(fperrors, "BAD START/STOP, No DEVICETYPE found line[%d], fix and re-run, see %s:\n%s\n",
					startstop[i].line, INH_CONTROL, startstop[i].expr);
			fprintf(stdout, "*** BAD START/STOP, No DEVICETYPE found line[%d] ***, fix and re-run, see %s\n",
					startstop[i].line, INH_CONTROL);
		}
		if (gcetmp == 0) {
			fprintf(fperrors, "BAD START/STOP, No TESTTEMP found line[%d], fix and re-run, see %s:\n%s\n",
					startstop[i].line, INH_CONTROL, startstop[i].expr);
			fprintf(stdout, "*** BAD START/STOP, No TESTTEMP found line[%d] ***, fix and re-run, see %s\n",
					startstop[i].line, INH_CONTROL);
		}
		if (gcetst == 0) {
			fprintf(fperrors, "BAD START/STOP, No TESTTYPE found line[%d], fix and re-run, see %s:\n%s\n",
					startstop[i].line, INH_CONTROL, startstop[i].expr);
			fprintf(stdout, "*** BAD START/STOP, No TESTTYPE found line[%d] ***, fix and re-run, see %s\n",
					startstop[i].line, INH_CONTROL);
		}
		if (goodtbl == 0 || goodenum == 0 || gcedev == 0 || gcetmp == 0 || gcetst == 0)
			fprintf(fpinhcontrol,
					"//BAD:%s ([0] is BAD) CAT[%d]DEV[%d]TST[%d]TMP[%d]ENUM[%d]\n",
					startstop[i].expr, goodtbl, gcedev, gcetst, gcetmp, goodenum);

		if (i != 0) {
			if (strcmp(startstop[i].cattype, startstop[i - 1].cattype) == 0
				&& strcmp(startstop[i].enumtype, startstop[i - 1].enumtype) == 0
				&& startstop[i].type == startstop[i - 1].type) {
				fprintf(stderr, "Double START (or STOP) of same definition. Was Line[%d] supposed to be a STOP (START)?\n",
						startstop[i].line);
				fprintf(fpinhcontrol, "//Double START (or STOP) of same definition. Was Line[%d] supposed to be a STOP (START)?\n",
						startstop[i].line);
				fprintf(fpinhcontrol, "//BADa[%d][%s][%c][%c]\n", i,
						startstop[i - 1].cattype, startstop[i - 1].type, startstop[i - 1].lvl);
				fprintf(fpinhcontrol, "//BADb[%d][%s][%c][%c]\n", i,
						startstop[i].cattype, startstop[i].type, startstop[i].lvl);
				fprintf(fperrors, "Double START (or STOP) of same definition. Was Line[%d] supposed to be a STOP (START)?\n",
						startstop[i].line);
			}
		}


		/* remove any not set on prior level */
		if (i > 1 && lvl > '0') {
			for (k = 0; k < maxactablenames; k++) {	/* ends are now at the same lvl as the prior begin! */
				if (startstop[i].cattype[k] == '1' &&
						startstop[startstack[lvl - ((startstop[i].type == SSSTOP) ? '0' : '1')]].cattype[k] == '0')
					startstop[i].cattype[k] = '.';
			}
			for (k = 0; k < maxenums; k++) {	/* ends are now at the same lvl as the prior begin! */
				if (startstop[i].enumtype[k] == '1' &&
					startstop[startstack[lvl - ((startstop[i].type == SSSTOP) ? '0' : '1')]].enumtype[k] == '0')
					startstop[i].enumtype[k] = '.';
			}
		}

		for (j = 0; j < maxactablenames; j++) if (startstop[i].cattype[j] == '.') startstop[i].cattype[j] = '0';
		for (j = 0; j < maxenums; j++) if (startstop[i].enumtype[j] == '.') startstop[i].enumtype[j] = '0';
	}

	udevt = utstt = utmpt = ucatt = uremt = 0;
	for (i = 0; i < maxstartstop; i++) {
		startstop[i].ucat = startstop[i].udev = startstop[i].utst = startstop[i].utmp = startstop[i].urem = -1;
		if (startstop[i].type == SSSTOP) continue;			/* only process the begins */

		for (j = 0; j < ucatt; j++)
			if (strcmp(startstop[i].cattype, ucattype[j]) == 0) {
				startstop[i].ucat = j;
				break;
			}
		if (j == ucatt) {
			startstop[i].ucat = j;
			strcpy(ucattype[ucatt], startstop[i].cattype);
			ucatt++;			/* needs error check? */
		}
		strcpy(holdenum, startstop[i].enumtype);
		for (k = 0; k < maxenums; k++)
			if (ALLDEVICE[k] != '+') holdenum[k] = '.';
		if (strchr(holdenum, '1') != NULL) {
			for (j = 0; j < udevt; j++)
				if (strcmp(holdenum, devtype[j]) == 0) {
					startstop[i].udev = j;
					break;
				}
			if (j == udevt) {
				startstop[i].udev = j;
				strcpy(devtype[udevt], holdenum);
				udevt++;		/* needs error check? */
			}
		}
		strcpy(holdenum, startstop[i].enumtype);
		for (k = 0; k < maxenums; k++)
			if (ALLTEMP[k] != '+') holdenum[k] = '.';
		if (strchr(holdenum, '1') != NULL) {
			for (j = 0; j < utmpt; j++)
				if (strcmp(holdenum, tmptype[j]) == 0) {
					startstop[i].utmp = j;
					break;
				}
			if (j == utmpt) {
				startstop[i].utmp = j;
				strcpy(tmptype[utmpt], holdenum);
				utmpt++;		/* needs error check? */
			}
		}
		strcpy(holdenum, startstop[i].enumtype);
		for (k = 0; k < maxenums; k++)
			if (ALLTEST[k] != '+') holdenum[k] = '.';
		if (strchr(holdenum, '1') != NULL) {
			for (j = 0; j < utstt; j++)
				if (strcmp(holdenum, tsttype[j]) == 0) {
					startstop[i].utst = j;
					break;
				}
			if (j == utstt) {
				startstop[i].utst = j;
				strcpy(tsttype[utstt], holdenum);
				utstt++;		/* needs error check? */
			}
		}
		strcpy(holdenum, startstop[i].enumtype);
		for (k = 0; k < maxenums; k++) {
			if (ALLTEST[k] == '+' || ALLTEMP[k] == '+' || ALLDEVICE[k] == '+') holdenum[k] = '.';
		}
		if (strchr(holdenum, '1') != NULL) {
			for (j = 0; j < uremt; j++)
				if (strcmp(holdenum, remtype[j]) == 0) {
					startstop[i].urem = j;
					break;
				}
			if (j == uremt) {
				startstop[i].urem = j;
				strcpy(remtype[uremt], holdenum);
				uremt++;		/* needs error check? */
			}
		}
	}
	fprintf(stdout, "UNIQUE CAT:%d TMP:%d DEV:%d TST:%d REM:%d\n", ucatt, utmpt, udevt, utstt, uremt);
	for (i = 0; i < ucatt; i++) fprintf(fpinhcontrol, "//%02dcat[%s]\n", i, ucattype[i]);
	for (i = 0; i < udevt; i++) fprintf(fpinhcontrol, "//%02ddev[%s]\n", i, devtype[i]);
	for (i = 0; i < utstt; i++) fprintf(fpinhcontrol, "//%02dtst[%s]\n", i, tsttype[i]);
	for (i = 0; i < utmpt; i++) fprintf(fpinhcontrol, "//%02dtmp[%s]\n", i, tmptype[i]);
	for (i = 0; i < uremt; i++) fprintf(fpinhcontrol, "//%02drem[%s]\n", i, remtype[i]);
/* this block will find the combinations of cat/dev/tst/tmp/enums and assign it a code */
	for (k = 0; k < maxstartstop; k++) {
//  if (startstop[k].type==SSSTOP) continue;
		optcat = optdev = opttst = opttmp = optrem = 0;
		fprintf(fpstatus, "SS%c%c %03d:", startstop[k].type, startstop[k].lvl, k);
		if (ucatt > 1) {
			fprintf(fpstatus, "  cat:");
			for (validchk = j = 0; j < ucatt; j++) {
				if (strcmp(startstop[k].cattype, ucattype[j]) == 0) {
					validchk = 1;
					optcat = j;
					fprintf(fpstatus, "%d ", j);
				}
			}
			if (validchk == 0) fprintf(fpstatus, "Missing cat ");
		}
		if (udevt > 1) {
			fprintf(fpstatus, "  dev:");
			strcpy(holdenum, startstop[k].enumtype);
			for (i = 0; i < maxenums; i++) {
				if (ALLDEVICE[i] != '+') holdenum[i] = '.';
			}
			for (validchk = j = 0; j < udevt; j++) {
				if (strcmp(holdenum, devtype[j]) == 0) {
					validchk = 1;
					optdev = j;
					fprintf(fpstatus, "%d ", j);
				}
			}
			if (validchk == 0) fprintf(fpstatus, "Missing device ");
		}
		if (utstt > 1) {
			fprintf(fpstatus, "  test:");
			strcpy(holdenum, startstop[k].enumtype);
			for (i = 0; i < maxenums; i++) {
				if (ALLTEST[i] != '+') holdenum[i] = '.';
			}
			for (validchk = j = 0; j <= utstt; j++) {
				if (strcmp(holdenum, tsttype[j]) == 0) {
					validchk = 1;
					opttst = j;
					fprintf(fpstatus, "%d ", j);
				}
			}
			if (validchk == 0) fprintf(fpstatus, "Missing test ");
		}
		if (utmpt > 1) {
			fprintf(fpstatus, "  temp:");
			strcpy(holdenum, startstop[k].enumtype);
			for (i = 0; i < maxenums; i++) {
				if (ALLTEMP[i] != '+') holdenum[i] = '.';
			}
			for (validchk = j = 0; j < utmpt; j++) {
				if (strcmp(holdenum, tmptype[j]) == 0) {
					validchk = 1;
					opttmp = j;
					fprintf(fpstatus, "%d ", j);
				}
			}
			if (validchk == 0) fprintf(fpstatus, "Missing temp ");
		}
		if (uremt > 1) {
			fprintf(fpstatus, "  otherenum:");
			strcpy(holdenum, startstop[k].enumtype);
			for (i = 0; i < maxenums; i++) {
				if (ALLTEST[i] == '+' || ALLTEMP[i] == '+' || ALLDEVICE[i] == '+') holdenum[i] = '.';
			}
			for (validchk = j = 0; j < uremt; j++) {
				if (strcmp(holdenum, remtype[j]) == 0) {
					validchk = 1;
					optrem = j;
					fprintf(fpstatus, "%d ", j);
				}
			}
			if (validchk == 0) fprintf(fpstatus, "Missing remaining-enum ");
		}
		for (i = 0; i < optlistcnt; i++) {
			if (optlist[i].cat == optcat && optlist[i].dev == optdev
				&& optlist[i].tst == opttst && optlist[i].tmp == opttmp
				&& optlist[i].rem == optrem) break;
		}
		if (i == optlistcnt) {	/* new */
			optlist[i].cat = optcat;
			optlist[i].dev = optdev;
			optlist[i].tst = opttst;
			optlist[i].tmp = opttmp;
			optlist[i].rem = optrem;
			optlistcnt++;
			if (optlistcnt > STARTSTOPCNT) {
				fprintf(stderr, "Too many condition codes[%d], source[%s,%d,%s]\n",
						optlistcnt, __FILE__, __LINE__, __FUNCTION__);
				fprintf(fperrors, "Too many condition codes[%d], source[%s,%d,%s]\n",
						optlistcnt, __FILE__, __LINE__, __FUNCTION__);
				exit(1);
			}
		}
		startstop[k].cdtcode = alphabet[i];
		fprintf(fpinhcontrol, "//%c%c[%s]E[%s]<%03d>UC[%c] P[%07d]L[%07d]STR[%s]\n",
				startstop[k].type,
				startstop[k].lvl + ((startstop[k].type == SSSTOP) ? 1 : 0),
				startstop[k].cattype, startstop[k].enumtype, i,
				startstop[k].cdtcode, startstop[k].loc, startstop[k].line,
				startstop[k].expr);
		fprintf(fpstatus, " cdt=%c\n", startstop[k].cdtcode);
	}

	fprintf(fpinhcontrol, "//end category markers\n");

	fprintf(fpstatus, "There are %d unique category/device/temp combinations\n", optlistcnt);
	fprintf(stderr, "There are %d unique category/device/temp combinations, source[%s,%d,%s]\n",
			optlistcnt, __FILE__, __LINE__, __FUNCTION__);
	if (lvl != '0') {
		fprintf(stderr, "=================================================\n");
		fprintf(stderr, "*** Mismatched START/STOP[%d]!!! (+START-STOP), source[%s,%d,%s] ***\n",
				lvl - '0', __FILE__, __LINE__, __FUNCTION__);
		fprintf(stderr, "=================================================\n");
		fprintf(fperrors, "*** Mismatched START/STOP[%d]!!! (+START-STOP)***\n", lvl - '0');
	}
	fprintf(fpinhcontrol, "//begin category grouping\n");
	for (j = 0; j < maxactablenames; j++) {
		k = 0;
		readstr[0] = '\0';
		for (i = 0; i < maxstartstop; i++)
			if (startstop[i].type == SSSTART && startstop[i].cattype[j] == '1') {
				if (strchr(readstr, startstop[i].cdtcode) == NULL) {
					readstr[k] = startstop[i].cdtcode;
					k++;
					readstr[k] = '\0';
				}
			}
		fprintf(fpinhcontrol, "//%s:CAT[%s]\n", readstr, actablenames->name[j]);
	}
/* NEW 4/27/2009: find the matching start stops */
	for (i = 0; i < maxstartstop; i++) {
		found = 0;
		if (startstop[i].type == SSSTART) {	/* find its begin */
			for (j = i + 1; j < maxstartstop; j++) {	/* !first STOP! must happen after the START! */
				if (startstop[j].cdtcode == startstop[i].cdtcode && startstop[j].type == SSSTOP) {
					startstop[i].startpt2stop = j;	/* terminate on first occurance */
//              fprintf(stdout,"StSM[%d,%d,%c], source[%s,%d,%s]\n",i,j,startstop[i].cdtcode,__FILE__,__LINE__,__FUNCTION__);
					found = 1;
					break;
				}
			}
			if (found == 0) {
				fprintf(stderr, "match start to stop, NOT FOUND!i[%d],cdt[%c],line[%d], source[%s,%d,%s]\n",
						i, startstop[i].cdtcode, startstop[i].line, __FILE__, __LINE__, __FUNCTION__);
				exit(1);
			}
		}
	}



	fprintf(fpinhcontrol, "//end category grouping\n");
	fputc('\n', fpwaves);
	fclose(fpinhcontrol);
	free(actablein);
	return (fmcnt);
}

int write_paramsINHC()
{
	int i, ss, bl, el, deep, depth, done=0, cdtbw; /* added init for done */
	int uniquecat, uniquedev, uniquetst, uniquetmp, uniquerem;
	char *ptr, exprbuf[500];
	FILE *fpinhcontrol;
	char INH_CONTROL[500];

	strcpy(INH_CONTROL, INHCONTROL);
	if (ACDATA == 1) {
		strcpy(INH_CONTROL, DATACONTROL);
		fprintf(stdout, "Outputting to [%s]\n", INH_CONTROL);
	}

	if (NULL == (fpinhcontrol = fopen(INH_CONTROL, "a"))) {
		fprintf(stderr, "\nCan't open file [%s], source[%s,%d,%s]\n", INH_CONTROL, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nCan't open file [%s]\n", INH_CONTROL);
		exit(1);
	}

	uniquecat = uniquedev = uniquetst = uniquetmp = uniquerem = 0;
	for (ss = 0, deep = '0'; ss < maxstartstop; ss++) {	/* deep is an ascii character not an integer! */
		if (startstop[ss].lvl > deep) deep = startstop[ss].lvl;
		if (startstop[ss].udev > uniquedev) uniquedev = startstop[ss].udev;
		if (startstop[ss].utst > uniquetst) uniquetst = startstop[ss].utst;
		if (startstop[ss].utmp > uniquetmp) uniquetmp = startstop[ss].utmp;
		if (startstop[ss].urem > uniquerem) uniquerem = startstop[ss].urem;
		if (startstop[ss].ucat > uniquecat) uniquecat = startstop[ss].ucat;
	}

	for (i = 0; i < paramcnt; i++) {
		paraminfo[i].used = 0;
	}
	for (depth = deep; depth > '0'; depth--) {	/* depth is an ascii character not a integer! */
		cdtbw = '?';
		for (ss = 0; ss < maxstartstop && done == 0; ss++) {
			if (startstop[ss].type != SSSTART) continue;		/* is start */
			if (startstop[ss].lvl == (depth - 1)) {
				cdtbw = startstop[ss].cdtcode;
			}
			if (depth != startstop[ss].lvl) continue;
			bl = startstop[ss].line;
			el = startstop[startstop[ss].startpt2stop].line;
			for (i = 0; i < paramcnt; i++) {
				if (paraminfo[i].used != 0) continue;
				if (paraminfo[i].actline > bl && paraminfo[i].actline < el) {
					strcpy(exprbuf, paraminfo[i].param_def);
					while (NULL != (ptr = strstr(exprbuf, "t["))) {
						*ptr = ' ';
						*(ptr + 1) = ' ';
					}
					while (NULL != (ptr = strstr(exprbuf, "]"))) {
						*ptr = ' ';
					}
					while (NULL != (ptr = strstr(exprbuf, "div"))) {
						if (isdigit(*(ptr + 3))) {
							*ptr = ' ';
							*(ptr + 1) = '/';
							*(ptr + 2) = ' ';
						}
					}
					while (NULL != (ptr = strstr(exprbuf, ":="))) {
						*ptr = '=';
						*(ptr + 1) = '\"';
					}			/* remap ':=' to '="' */
					fprintf(fpinhcontrol, "[%c%c%c]%s\";//", startstop[ss].cdtcode, depth, cdtbw, exprbuf);
					fprintf(fpinhcontrol, " %d\n", paraminfo[i].actline);
					paraminfo[i].used = 1;	/* DEV[%d]TMP[%d]TST[%d]REM[%d] %d\n */
				}
			}
		}
	}
	fclose(fpinhcontrol);
	return (0);
}

int write_partial(char *actablein, off_t filesize)
{
	FILE *fpdummy;
	int i;
	if (NULL == (fpdummy = fopen(ACTLINES, "w"))) {
		fprintf(stderr, "\nCan't open file %s\n", ACTLINES);
		exit(1);
	}
	for (i = 0; i < filesize; i++) fputc(actablein[i], fpdummy);
	fclose(fpdummy);
	return (0);
}
