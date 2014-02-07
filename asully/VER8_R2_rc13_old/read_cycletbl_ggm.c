/* read_cycletbl() {} */

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

int read_cycletbl(char *fname) {
	FILE *fpin, *fpin1;
	struct stat statbuf;
	off_t filesize, pos;
	long fileininhst;
	int i, j, k, ret, sp, cnt;
	int ininherit;
	int tmaxcyclen, maxcyclen = 0;
	int pinorder[NUMPINS], fullpinorder[NUMPINS];
	char *cstptr, *cendptr, *cyctablein, *mytable;
	char *ptrfind;
	char readstr[READLINELEN + 1];
	char *ptrOP, *ptrCL;
	char vmpb[NUMPINS + 1];
	char vmpins[READLINELEN + 1];

	ret = stat(fname, &statbuf);
	if (ret == 0)
		filesize = statbuf.st_size;
	else {
		fprintf(stderr,
				"Can't determine filesize for [%s], source[%s,%d,%s]\n",
				fname, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Can't determine filesize for [%s]\n", fname);
		exit(1);
	}
	cyctablein = malloc((size_t) (filesize + 1));
	if (cyctablein == NULL) {
		fprintf(stderr,
				"Could not allocate memory for [%s] file in memory, source[%s,%d,%s]\n",
				fname, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for [%s] file in memory\n",
				fname);
		exit(1);
	}
	for (i = 0; i < filesize + 1; i++)
		*(cyctablein + i) = '\0';
	if (NULL == (fpin = fopen(fname, "r"))) {
		fprintf(stderr,
				"\ncycletable file [%s] not found, source[%s,%d,%s]\n",
				fname, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\ncycletable file [%s] not found\n", fname);
		exit(1);
	}
	fprintf(fpstatus,
			"allocated [%ld] bytes for cyctablein, source[%s,%d,%s]\n",
			filesize, __FILE__, __LINE__, __FUNCTION__);
	fread(cyctablein, (size_t) filesize, 1, fpin);
	fclose(fpin);
	pos = 0;
	/* Clear the comments */
	mytable = cyctablein;
	fprintf(stdout, "Erasing cycletable comments...\n");
	while (pos < filesize && (cstptr = strstr(mytable, "(*")) != NULL) {
		cendptr = strstr(mytable, "*)");
		while (cstptr <= (cendptr + 1)) {	/* +1 => get '(' through the ')' */
			*cstptr++ = ' ';
			pos = cstptr - cyctablein;
		}
		mytable = cendptr + 1;
	}
	pos = 0;
	mytable = cyctablein;
	while (pos < filesize && (cstptr = strstr(mytable, "{")) != NULL) {
		cendptr = strstr(mytable, "}");
		while (cstptr <= (cendptr)) {	/* no +1 for '{' '}' */
			*cstptr++ = ' ';
			pos = cstptr - cyctablein;
		}
		mytable = cendptr + 1;
	}
	fprintf(stdout, "Done erasing cycletable comments...\n");
	cyctablein[filesize] = '\0';	/* just to make sure */
	sp = pos = 0;
	mytable = cyctablein;
	while (pos < filesize) {
		/* make sure terminating () have a ';' */
		/* protect against long lines: */
		if (sp > READLINELEN) {
			fprintf(stderr,
					"There's a really long unterminated statement in the cycletble file\n");
			fprintf(stderr,
					"(carriage returns get removed causing wrap)\n");
			fprintf(stderr,
					"which doesn't get a semi-colon within [%d] bytes.\n",
					READLINELEN);
			fprintf(stderr,
					"You'll need to do something with this line...\n");
			fprintf(stderr,
					"The string starts with [%60.60s], source[%s,%d,%s]\n",
					readstr, __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
		if (pos > 1 && cyctablein[pos] == ')'
			&& cyctablein[pos + 1] == '\n') {
			if (cyctablein[pos - 1] != '*')
				cyctablein[pos + 1] = ';';
		}
		/* do the same except check with spaces after (), add ';' */
		else if (pos > 1 && cyctablein[pos] == ')'
				 && cyctablein[pos - 1] != '*'
				 && cyctablein[pos + 1] == ' ') {
			for (i = 1; cyctablein[pos + i] == ' ' && (pos + i) < filesize;
				 i++);
			if (cyctablein[pos + i] == '\n') {
				cyctablein[pos + 1] = ';';
			}
		}
		if (isspace(cyctablein[pos])) {
			pos++;
		}						/* don't store if white space */
		else if (NULL != (ptrfind = (strstr(readstr, "#begininheritlist")))) {	/* don't forget we stripped whitespace!!!! */
			ininherit = 1;
			fprintf(stderr, "Entering inherit table!, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
			fileininhst = ftell(fpin1);
			sp = 0;
			readstr[sp] = '0';
			pos++;				/* advance */
		}
		else if (NULL != (ptrfind = (strstr(readstr, "#endinheritlist")))) {	/* don't forget we stripped whitespace!!!! */
			fprintf(stderr,
					"Exiting inherit table![%d], source[%s,%d,%s]\n", i,
					__FILE__, __LINE__, __FUNCTION__);
			ininherit = -1;
			sp = 0;
			readstr[sp] = '0';
			pos++;				/* advance */
		}
		else if (cyctablein[pos] != ';') {
			readstr[sp] = cyctablein[pos];
			sp++;
			pos++;
			readstr[sp] = '\0';	/* keep it permanently terminated, for debug etc */
		}
		else if (cyctablein[pos] == ';') {	/* found end of statement */
			if (readstr[0] == '\0' && readstr[0] == '\n') {
				readstr[0] = '\0';
				sp = 0;			/* clear the string, i.e. don't print it */
				pos++;			/* advance */
			}
			else if (NULL != (ptrfind = strstr(readstr, "CycleSetMD"))) {
				tmaxcyclen = add_cyclesetMD(ptrfind);
				if (tmaxcyclen > maxcyclen)
					maxcyclen = tmaxcyclen;
				readstr[0] = '\0';
				sp = 0;
				pos++;			/* advance */
			}
			else if (NULL != (ptrfind = strstr(readstr, "CycleSet"))) {
				tmaxcyclen = add_cycleset(ptrfind);
				if (tmaxcyclen > maxcyclen)
					maxcyclen = tmaxcyclen;
				readstr[0] = '\0';
				sp = 0;
				pos++;			/* advance */
			}
			else if (NULL !=
					 (ptrfind =
					  (strstr(readstr, "VectorMapSetCycleAll")))) {
				ptrOP = strchr(ptrfind, '(');
				ptrCL = strchr(ptrfind, ')');
				if (ptrOP == NULL || ptrCL == NULL) {
					fprintf(stderr,
							"Bad syntax in VectorMapSetCycleAll(n). exiting..., source[%s,%d,%s]\n",
							__FILE__, __LINE__, __FUNCTION__);
					exit(1);
				}
				*ptrCL = '\0';
				VMparallel = -1;
				VMfields = 0;
				for (i = 0; i < maxvmsets; i++) {
					if (VMparallel == -1
						&& strcmp(vmsets[i].name, ptrOP + 1) == 0) {
						VMparallel = i;
					}
					if (vmsets[i].field > VMfields)
						VMfields = vmsets[i].field;
				}
				if (VMparallel == -1) {
					fprintf(stderr,
							"Could not locate VectorMapSetCycleAll(%s) in the list of %d, source[%s,%d,%s]\n",
							ptrOP + 1, maxvmsets, __FILE__, __LINE__,
							__FUNCTION__);
					fprintf(stderr, "Here's the list:\n");
					for (i = 0; i < maxvmsets; i++)
						fprintf(stderr, "%s-f[%d],", vmsets[i].name,
								vmsets[i].field);
					fputc('\n', stderr);
					exit(1);
				}
				*ptrCL = ')';
				readstr[0] = '\0';
				sp = 0;
				pos++;			/* advance */
			}
			else if (NULL !=
					 (ptrfind = (strstr(readstr, "VectorMapSetCycle")))) {
				ptrOP = strchr(ptrfind, '(');
				ptrCL = strchr(ptrfind, ',');
				if (ptrCL == NULL)
					ptrCL = strchr(ptrfind, ')');
				if (ptrOP == NULL || ptrCL == NULL) {
					fprintf(stderr,
							"Bad syntax in VectorMapSetCycle(n). exiting..., source[%s,%d,%s]\n",
							__FILE__, __LINE__, __FUNCTION__);
					exit(1);
				}
				*ptrCL = '\0';
				VMparallel = -1;
				for (i = 0; i < maxvmsets; i++) {
					if ((strcmp(vmsets[i].name, ptrOP + 1) == 0)
						&& vmsets[i].field == 1) {
						VMparallel = i;
					}
					if (vmsets[i].field > VMfields)
						VMfields = vmsets[i].field;
				}
				if (VMparallel == -1) {
					fprintf(stderr,
							"Could not locate VectorMapSetCycle(%s) in the list of %d, source[%s,%d,%s]\n",
							ptrOP + 1, maxvmsets, __FILE__, __LINE__,
							__FUNCTION__);
					fprintf(stderr, "Here's the list:\n");
					for (i = 0; i < maxvmsets; i++)
						fprintf(stderr, "%s-f[%d],", vmsets[i].name,
								vmsets[i].field);
					fputc('\n', stderr);
					exit(1);
				}
				*ptrCL = ')';
				readstr[0] = '\0';
				sp = 0;
				pos++;			/* advance */
			}
			else if (NULL != (ptrfind = (strstr(readstr, "VectorMapSet")))) {
				add_vectormapset(ptrfind);
				readstr[0] = '\0';
				sp = 0;
				pos++;			/* advance */
			}
			else {				/* its some sort of other bogus data... */
				readstr[0] = '\0';
				sp = 0;
				pos++;			/* advance */
			}
		}						/* end of statement, i.e. ';' */
	}							/* end of while */
	fprintf(stdout, "Done reading cycletable\n");
	for (j = 0; j < maxpin; j++) fullpinorder[j] = -1;
	pos=0;
	for (j = 1; j <= VMfields; j++) {
		for (i = 0; i < maxvmsets; i++) {
			if (vmsets[i].field != j)
				continue;
			if (strcmp(vmsets[i].name,vmsets[VMparallel].name)!=0) {
				fprintf(fpstatus,"VMS:NOT VMSC[%s]->%s\n",vmsets[VMparallel].name,vmsets[i].name);
				continue;
				}
			strcpy(vmpins, vmsets[i].pinlist);
			resolve_list(vmpins, vmpb, '*', '.', pinorder);
			for (cnt = k = 0; k < maxpin; k++) {
				if (pinorder[k] == -1) continue;
				else if (fullpinorder[k] != -1) {
					fprintf(stdout, "Pin listed twice in pingroup[%s]\n",
							vmpins);
				}
				else {
					cnt++;
					fullpinorder[k] = pos + pinorder[k];
				}
			}
			pos += cnt;
		}
	}
	for (i = 0; i < maxpin; i++) {
		fprintf(fpstatus, "PIN[%s]PinList:[%d]VectorMap:[%d]\n", PIN[i], i,
				fullpinorder[i]);
		if (fullpinorder[i] == -1) {
			fprintf(stderr,
					"*** Warning:pinlist.txt pin[%s] doesn't exist in vectormapset (could be ok). See [%s] & help doc\n",
					PIN[i], TRANSLATION_STATUS);
			fprintf(stderr,
					"    This might just be a non-pattern pin, source[%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
			fprintf(fpstatus,
					"*** Warning:pinlist.txt pin[%s] doesn't exist in vectormapset (could be ok). See [%s] & help doc\n",
					PIN[i], TRANSLATION_STATUS);
		}
		else if (i != fullpinorder[i]) {
			fprintf(stderr,
					"*** Error:pinlist.txt vs vectormapset mismatch[%s] order[%d] See [%s]\n",
					PIN[i], fullpinorder[i], TRANSLATION_STATUS);
			fprintf(fperrors,
					"*** Error:pinlist.txt vs vectormapset mismatch[%s] order[%d] See [%s]\n",
					PIN[i], fullpinorder[i], TRANSLATION_STATUS);
		}
	}
	return (maxcyclen);
}

int add_cyclesetMD(char *ptrfind)
{
	char *ptrOP, *ptrCL, *ptrcomma1, *ptrcomma2, *ptrcomma3, hold;
	int len;
	ptrOP = strchr(ptrfind, '(');
	ptrCL = strchr(ptrfind, ')');
	if (ptrOP == NULL || ptrCL == NULL)
		return (-1);			/* no parenthesis */
	ptrcomma1 = strchr(ptrfind, ',');
	if (ptrcomma1 != NULL) {
		ptrcomma2 = strchr(ptrcomma1 + 1, ',');
		if (ptrcomma2 != NULL) {
			ptrcomma3 = strchr(ptrcomma2 + 1, ',');
			if (ptrcomma3 == NULL)
				return (-1);	/* not 3 commas */
		}
		else
			return (-1);		/* only one comma */
	}							/* end of comma finds */
	else
		return (-1);			/* no commas */
	len = ptrcomma1 - ptrOP;
	hold = *ptrcomma1;
	*ptrcomma1 = '\0';
	strcpy(cycsets[maxcycset].tblname, ptrOP + 1);
	*ptrcomma1 = hold;
	hold = *ptrcomma2;
	*ptrcomma2 = '\0';
	strcpy(cycsets[maxcycset].dset0, ptrcomma1 + 1);
	*ptrcomma2 = hold;
	hold = *ptrcomma3;
	*ptrcomma3 = '\0';
	strcpy(cycsets[maxcycset].dset1, ptrcomma2 + 1);
	*ptrcomma3 = hold;
	hold = *ptrCL;
	*ptrCL = '\0';
	strcpy(cycsets[maxcycset].pin, ptrcomma3 + 1);
	*ptrCL = hold;
	maxcycset++;
	if (maxcycset > MAXCYCSETS) {
		fprintf(stderr, "Too many cyclesets[%d], source[%s,%d,%s]\n",
				maxcycset, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Too many cyclesets[%d]\n", maxcycset);
	}
	return (len);
}

int add_cycleset(char *ptrfind)
{
	char *ptrOP, *ptrCL, *ptrcomma1, *ptrcomma2, hold;
	int len;
	ptrOP = strchr(ptrfind, '(');
	ptrCL = strchr(ptrfind, ')');
	if (ptrOP == NULL || ptrCL == NULL)
		return (-1);			/* no parenthesis */
	ptrcomma1 = strchr(ptrfind, ',');
	if (ptrcomma1 != NULL) {
		ptrcomma2 = strchr(ptrcomma1 + 1, ',');
		if (ptrcomma2 != NULL) {
		}
		else
			return (-1);		/* only one comma */
	}							/* end of comma finds */
	else
		return (-1);			/* no commas */
	len = ptrcomma1 - ptrOP;
	hold = *ptrcomma1;
	*ptrcomma1 = '\0';
	strcpy(cycsets[maxcycset].tblname, ptrOP + 1);
	*ptrcomma1 = hold;
	hold = *ptrcomma2;
	*ptrcomma2 = '\0';
	/* this is the same as CycleSetMD but the dsets reference the same wave */
	strcpy(cycsets[maxcycset].dset0, ptrcomma1 + 1);
	strcpy(cycsets[maxcycset].dset1, ptrcomma1 + 1);
	*ptrcomma2 = hold;
	hold = *ptrCL;
	*ptrCL = '\0';
	strcpy(cycsets[maxcycset].pin, ptrcomma2 + 1);
	*ptrCL = hold;
	maxcycset++;
	if (maxcycset > MAXCYCSETS) {
		fprintf(stderr, "Too many cyclesets[%d], source[%s,%d,%s]\n",
				maxcycset, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Too many cyclesets[%d]\n", maxcycset);
	}
	return (len);
}

int add_vectormapset(char *ptrfind)
{
	char *ptrOP, *ptrCL, *ptrcomma1, *ptrcomma2, *ptrcomma3, hold,
		field[50];
	int i;
	ptrOP = strchr(ptrfind, '(');
	ptrCL = strchr(ptrfind, ')');
	if (ptrOP == NULL || ptrCL == NULL)
		return (-1);			/* no parenthesis */
	ptrcomma1 = strchr(ptrfind, ',');
	if (ptrcomma1 != NULL) {
		ptrcomma2 = strchr(ptrcomma1 + 1, ',');
		if (ptrcomma2 != NULL) {
			ptrcomma3 = strchr(ptrcomma2 + 1, ',');
			if (ptrcomma3 == NULL)
				return (-1);	/* not 3 commas */
		}
		else
			return (-1);		/* only one comma */
	}							/* end of comma finds */
	else
		return (-1);			/* no commas */
	hold = *ptrcomma1;
	*ptrcomma1 = '\0';
	strcpy(vmsets[maxvmsets].name, ptrOP + 1);
	*ptrcomma1 = hold;
	hold = *ptrcomma2;
	*ptrcomma2 = '\0';
	strcpy(field, ptrcomma1 + 1);
	*ptrcomma2 = hold;
	vmsets[maxvmsets].field = strtol(field, NULL, 10);
	fprintf(fpstatus,"VMS:[%s]<%d>\n",vmsets[maxvmsets].name,vmsets[maxvmsets].field);
	hold = *ptrcomma3;
	*ptrcomma3 = '\0';
	strcpy(vmsets[maxvmsets].pinlist, ptrcomma2 + 1);
	*ptrcomma3 = hold;
	hold = *ptrCL;
	*ptrCL = '\0';
	if (strstr(ptrcomma3 + 1, "Hex") != NULL)
		vmsets[maxvmsets].type = VMSHEX;
	else if (strstr(ptrcomma3 + 1, "Binary") != NULL)
		vmsets[maxvmsets].type = VMSBINARY;
	else {
		fprintf(stderr,
				"Unknown VectorMapSet setting [%s](should be Hex or Binary), source[%s,%d,%s]\n",
				ptrcomma3 + 1, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Unknown VectorMapSet setting [%s](should be Hex or Binary)\n",
				ptrcomma3 + 1);
		exit(1);
	}
	*ptrCL = hold;
	strcpy(field, vmsets[maxvmsets].name);
	for (i = 0; i < strlen(field); i++)
		field[i] = tolower(field[i]);
	if (strstr(vmsets[maxvmsets].name, "ScanIn") != NULL)
		vmsets[maxvmsets].scan = VMSSCANIN;
	else if (strstr(vmsets[maxvmsets].name, "ScanOut") != NULL)
		vmsets[maxvmsets].scan = VMSSCANOUT;
	else if (strstr(field, "scan") != NULL)
		vmsets[maxvmsets].scan = VMSSCANOTHER;
	else
		vmsets[maxvmsets].scan = VMSPARALLEL;
	maxvmsets++;
	if (maxvmsets > MAXCYCSETS) {
		fprintf(stderr, "Too many vmsets[%d], source[%s,%d,%s]\n",
				maxvmsets, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Too many vmsets[%d]\n", maxvmsets);
	}
	return (0);
}
