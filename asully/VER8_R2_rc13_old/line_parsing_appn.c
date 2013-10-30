/* appn_line_parsing.c: routines to break pattern lines up */
/* int strip_comments(){} */
/* int check_for_begin(){} */
/* int check_for_end(){} */
/* int check_for_repeat(){} */
/* int check_for_match(){} */
/* int check_for_shutdown(){} */
/* int check_for_align_until(){} */
/* int check_for_subroutine(){} */
/* int check_for_scan(){} */
/* int check_for_vector(){} */
/* int check_for_SET(){} */
/* int get_count(){} */
/* char * get_count_orig(){} */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "includes_appn.h"

int strip_comments(char *vector, char *comments, int *incomment)
{
#define DISCARD_LEN 500
	char *ptrOPEN, *ptrCLOSE, discard[DISCARD_LEN + 1];
	int cp = 0, db;
	/* FIXME: APS we need something here which will continue reading until we get the
	   ending comment close. Better yet, convert multiline comments into separately
	   commented lines. */
	//comments[0]='\0'; /* assume main function deals with printing and clearing/reseting */
	while (strstr(vector, "(*") != NULL) {
		(*incomment)++;
		if ((ptrOPEN = strstr(vector, "(*")) != NULL) {	/* comments */
			ptrCLOSE = strstr(vector, "*)");
			if (ptrCLOSE != NULL) {
				(*incomment)--;
				*(ptrOPEN++) = ' ';
				*(ptrOPEN++) = ' ';	/* wipe out (**) but don't save */
				if ((ptrCLOSE - ptrOPEN) + cp > COMMENT) {	/* ignore this comment because its too big */
					if ((ptrCLOSE - ptrOPEN) > DISCARD_LEN) {
						fprintf(stderr,
								"can't process extra long comment in [%s], ignoring\n",
								infile_orig);
						fprintf(fpstatus,
								"can't process extra long comment in [%s], ignoring\n",
								infile_orig);
						while (ptrOPEN < ptrCLOSE) {	/* no storing at all */
							*(ptrOPEN++) = ' ';	/* remove comment */
						}
					}
					else {
						db = 0;
						while (ptrOPEN < ptrCLOSE) {	/*we're ok here because its less than DISCARD_LEN */
							discard[db++] = *ptrOPEN;
							*(ptrOPEN++) = ' ';	/* remove comment */
						}
						discard[db] = '\0';
						fprintf(fpstatus,
								"Throwing away long comment in [%s]:[%s]\n",
								infile_orig, discard);
					}
				}
				else {
					while (ptrOPEN < ptrCLOSE) {	/* it should fit with no problem */
						comments[cp++] = *ptrOPEN;
						*ptrOPEN++ = ' ';	/* erase comments in buffer, but keep comments */
					}
				}
				*(ptrOPEN++) = ' ';
				*(ptrOPEN++) = ' ';	/* wipe out (**) but don't save */
			}
			else {				/* multiline comment */
				ptrCLOSE = vector + strlen(vector) - 1;	/* (*++++*\0 */
				/* seen one pattern where the comment close was wrong and only had '*' */
				/*    so print a warning to fperrors about this, hopefully we pick it up in the next line */
				if (*ptrCLOSE == '*')
					fprintf(fperrors,
							"could be unterminated comment in [%s]:[%s]\n",
							infile_orig, vector);
				*(ptrOPEN++) = ' ';
				*(ptrOPEN++) = ' ';	/* wipe out (**) but don't save */
				if ((ptrCLOSE - ptrOPEN) + cp > COMMENT) {	/* ignore this comment because its too big */
					if ((ptrCLOSE - ptrOPEN) > DISCARD_LEN) {
						fprintf(stderr,
								"can't process extra long comment in [%s], ignoring\n",
								infile_orig);
						fprintf(fpstatus,
								"can't process extra long comment in [%s], ignoring\n",
								infile_orig);
						while (ptrOPEN < ptrCLOSE) {	/* no storing at all */
							*(ptrOPEN++) = ' ';	/* remove comment */
						}
					}
					else {
						db = 0;
						while (ptrOPEN < ptrCLOSE) {	/*we're ok here because its less than DISCARD_LEN */
							discard[db++] = *ptrOPEN;
							*(ptrOPEN++) = ' ';	/* remove comment */
						}
						discard[db] = '\0';
						fprintf(fpstatus,
								"Throwing away long comment in [%s]:[%s]\n",
								infile_orig, discard);
					}
				}
				else {
					while (ptrOPEN < ptrCLOSE) {
						comments[cp++] = *ptrOPEN;
						*ptrOPEN++ = ' ';	/* wipe out comments */
					}
				}
				*(ptrOPEN++) = ' ';
				*(ptrOPEN++) = ' ';	/* wipe out (**) but don't save */
			}
		}
	}
	while (strchr(vector, '{') != NULL) {	/* } to match */
		(*incomment)++;
		if ((ptrOPEN = strchr(vector, '{')) != NULL) {	/* } to match */
			/* { to match */ ptrCLOSE = strchr(vector, '}');
			if (ptrCLOSE != NULL) {
				(*incomment)--;
				*(ptrOPEN++) = ' ';	/* wipe out {},but don't save */
				if ((ptrCLOSE - ptrOPEN) + cp > COMMENT) {	/* ignore this comment because its too big */
					if ((ptrCLOSE - ptrOPEN) > DISCARD_LEN) {
						fprintf(stderr,
								"can't process extra long comment in [%s], ignoring\n",
								infile_orig);
						fprintf(fpstatus,
								"can't process extra long comment in [%s], ignoring\n",
								infile_orig);
						while (ptrOPEN < ptrCLOSE) {	/* no storing at all */
							*(ptrOPEN++) = ' ';	/* remove comment */
						}
					}
					else {
						db = 0;
						while (ptrOPEN < ptrCLOSE) {	/*we're ok here because its less than DISCARD_LEN */
							discard[db++] = *ptrOPEN;
							*(ptrOPEN++) = ' ';	/* remove comment */
						}
						discard[db] = '\0';
						fprintf(fpstatus,
								"Throwing away long comment in [%s]:[%s]\n",
								infile_orig, discard);
					}
				}
				else {
					while (ptrOPEN < ptrCLOSE) {	/* it should fit with no problem */
						comments[cp++] = *ptrOPEN;
						*ptrOPEN++ = ' ';	/* erase comments in buffer, but keep comments */
					}
				}
				*(ptrOPEN++) = ' ';	/* wipe out {},but don't save */
			}
			else {				/* multiline comment */
				ptrCLOSE = vector + strlen(vector) - 1;	/* (*++++*\0 */
				/* seen one pattern where the comment close was wrong and only had '*' */
				/*    so print a warning to fperrors about this, hopefully we pick it up in the next line */
				if (*ptrCLOSE == '*')
					fprintf(fperrors,
							"could be unterminated comment in [%s]:[%s]\n",
							infile_orig, vector);
				*(ptrOPEN++) = ' ';
				*(ptrOPEN++) = ' ';	/* wipe out (**) but don't save */
				if ((ptrCLOSE - ptrOPEN) + cp > COMMENT) {	/* ignore this comment because its too big */
					if ((ptrCLOSE - ptrOPEN) > DISCARD_LEN) {
						fprintf(stderr,
								"can't process extra long comment in [%s], ignoring\n",
								infile_orig);
						fprintf(fpstatus,
								"can't process extra long comment in [%s], ignoring\n",
								infile_orig);
						while (ptrOPEN < ptrCLOSE) {	/* no storing at all */
							*(ptrOPEN++) = ' ';	/* remove comment */
						}
					}
					else {
						db = 0;
						while (ptrOPEN < ptrCLOSE) {	/*we're ok here because its less than DISCARD_LEN */
							discard[db++] = *ptrOPEN;
							*(ptrOPEN++) = ' ';	/* remove comment */
						}
						discard[db] = '\0';
						fprintf(fpstatus,
								"Throwing away long comment in [%s]:[%s]\n",
								infile_orig, discard);
					}
				}
				else {
					while (ptrOPEN < ptrCLOSE) {
						comments[cp++] = *ptrOPEN;
						*ptrOPEN++ = ' ';	/* wipe out comments */
					}
				}
				*(ptrOPEN++) = ' ';	/* wipe out (**) but don't save */
			}



		}
	}
	/* (* */
	if ((ptrCLOSE = strstr(vector, "*)")) != NULL) {
		(*incomment)--;
		*ptrCLOSE = '\0';
		strcat(comments, vector);
		cp += strlen(vector);
		ptrOPEN = vector;		/* (the ptrCLOSE+1 gets us through the *) */
		for (ptrOPEN = vector; ptrOPEN <= (ptrCLOSE + 1); ptrOPEN++)
			*ptrOPEN = ' ';
	}
	/* { */
	if ((ptrCLOSE = strstr(vector, "}")) != NULL) {
		(*incomment)--;
		*ptrCLOSE = '\0';
		strcat(comments, vector);
		cp += strlen(vector);
		ptrOPEN = vector;
		for (ptrOPEN = vector; ptrOPEN <= ptrCLOSE; ptrOPEN++)
			*ptrOPEN = ' ';
	}

	comments[cp] = '\0';
	return (cp);
}

int check_for_begin(char *vector, int *begin_loc, int *loopnest)
{
	char *BP;
	*begin_loc = -1;
	if ((BP = strstr(vector, "begin")) != NULL) {
		*begin_loc = BP - vector;
		*(BP + 0) = ' ';		/* b */
		*(BP + 1) = ' ';		/* e */
		*(BP + 2) = ' ';		/* g */
		*(BP + 3) = ' ';		/* i */
		*(BP + 4) = ' ';		/* n */
		(*loopnest)++;
		if (*(loopnest) > MAXLOOPDEPTH)
			MAXLOOPDEPTH = *(loopnest);
		BEGINCNT++;
//      fprintf(stdout,"BEGIN[%d]![%s]\n",*loopnest,infile_orig);
		if ((*loopnest) > 5) {
			fprintf(fperrors,
					"FATAL:Loop nesting too deep[%d] in [%s]!,exiting\n",
					*loopnest, infile_orig);
			fprintf(stderr,
					"FATAL:Loop nesting too deep[%d] in [%s]!,exiting\n",
					*loopnest, infile_orig);
			exit(1);
		}
	}
	return (0);
}

int check_for_end(char *vector, int *end_loc, int loopnest)
{
	char *EP;
	int i;
	*end_loc = -1;
	if ((EP = strstr(vector, "end")) != NULL) {
//      fprintf(stdout,"END[%d]![%s]\n",loopnest,infile_orig);
		ENDCNT++;
		*end_loc = EP - vector;
		*(EP + 0) = ' ';		/* e */
		*(EP + 1) = ' ';		/* n */
		*(EP + 2) = ' ';		/* d */
		i = 3;
		while (*(EP + i) != ';' && *(EP + i) != '\n' && *(EP + i) != '\0'
			   && i < MAXPATLINES) {
			*(EP + i) = ' ';	/* blank any chars upto the ';' or '\n' */
			i++;
		}
		*(EP + i) = ' ';		/* blank the ';' after 'end' */
	}
	return (0);
}

int check_for_repeat(char *vector, int *repeat_loc, int *repeatloop,
					 int loopnest)
{
	char *RP;
	*repeat_loc = -1;
	if ((RP = strstr(vector, "repeat")) != NULL) {
		REPEATCNT++;
		*repeat_loc = RP - vector;
		*(RP + 0) = ' ';		/* r */
		*(RP + 1) = ' ';		/* e */
		*(RP + 2) = ' ';		/* p */
		*(RP + 3) = ' ';		/* e */
		*(RP + 4) = ' ';		/* a */
		*(RP + 5) = ' ';		/* t */
		if (*(RP + 6) != ' ' || *(RP + 6) != '\t')
			*repeatloop = get_count(RP + 6);
		else
			*repeatloop = get_count(RP + 7);
      fprintf(stdout,"REPEAT[%d]![%s]=%d\n",loopnest,infile_orig,*repeatloop);
		if (*repeatloop == RET_FOREVER) {
			*(RP + 7) = ' ';	/* f */
			*(RP + 8) = ' ';	/* o */
			*(RP + 9) = ' ';	/* r */
			*(RP + 10) = ' ';	/* e */
			*(RP + 11) = ' ';	/* v */
			*(RP + 12) = ' ';	/* e */
			*(RP + 13) = ' ';	/* r */
			return (RET_FOREVER);
		}
	}
	else
		*repeatloop = 0;
	return (0);
}

int check_for_match(char *vector, int *match_loc, int *matchloop)
{
	char *MP;
	*match_loc = NO_MATCH;
	if ((MP = strstr(vector, "match repeat")) != NULL) {	/* this is the official way, but FIXME: APS I'm assuming only one space */
		*match_loc = MP - vector;
		*(MP + 0) = ' ';		/* m */
		*(MP + 1) = ' ';		/* a */
		*(MP + 2) = ' ';		/* t */
		*(MP + 3) = ' ';		/* c */
		*(MP + 4) = ' ';		/* h */
		*(MP + 5) = ' ';		/*   */
		*(MP + 6) = ' ';		/* r */
		*(MP + 7) = ' ';		/* e */
		*(MP + 8) = ' ';		/* p */
		*(MP + 9) = ' ';		/* e */
		*(MP + 10) = ' ';		/* a */
		*(MP + 11) = ' ';		/* t */
		*matchloop = get_count(MP + 12);
		fprintf(stdout, "MATCH![%s]=%d\n", infile_orig,*matchloop);
	}
	else if ((MP = strstr(vector, "match")) != NULL) {	/* this is the abreviated way that we're used to */
		*match_loc = MP - vector;
		*(MP + 0) = ' ';		/* m */
		*(MP + 1) = ' ';		/* a */
		*(MP + 2) = ' ';		/* t */
		*(MP + 3) = ' ';		/* c */
		*(MP + 4) = ' ';		/* h */
		*matchloop = get_count(MP + 5);
		fprintf(stdout, "MATCH![%s]=%d\n", infile_orig,*matchloop);
	}
	return (0);
}

int check_for_shutdown(char *vector, int *shutdown_loc)
{
	char *SD, *SD1;
	*shutdown_loc = -1;
	if ((SD = strstr(vector, "shutdown")) != NULL ||
		(SD1 = strstr(vector, "Shutdown")) != NULL) {
		if (SD == NULL && SD1 != NULL)
			SD = SD1;
		fprintf(stdout, "SHUTDOWN![%s]\n", infile_orig);
		*shutdown_loc = SD - vector;
		*(SD + 0) = ' ';		/* S */
		*(SD + 1) = ' ';		/* h */
		*(SD + 2) = ' ';		/* u */
		*(SD + 3) = ' ';		/* t */
		*(SD + 4) = ' ';		/* d */
		*(SD + 5) = ' ';		/* o */
		*(SD + 6) = ' ';		/* w */
		*(SD + 7) = ' ';		/* n */
	}
	return (0);
}

int check_for_align_until(char *vector)
{
	/* no need to do anything with aligns */
	char *AP;
	int align_loc;
	align_loc = -1;
	if ((AP = strstr(vector, "align")) != NULL) {
		fprintf(fperrors,
				"FYI_align_FOUND:found align Polaris instruction in %s! skipping\n",
				infile_orig);
		fprintf(fpstatus,
				"FYI_align_FOUND:found align Polaris instruction in %s! skipping\n",
				infile_orig);
		align_loc = AP - vector;
		*(AP + 0) = ' ';		/* a */
		*(AP + 1) = ' ';		/* l */
		*(AP + 2) = ' ';		/* i */
		*(AP + 3) = ' ';		/* g */
		*(AP + 4) = ' ';		/* n */
	}
	if ((AP = strstr(vector, "until pass")) != NULL) {
		fprintf(fperrors,
				"FYI_until_pass_FOUND:found until pass Polaris instruction in %s! skipping\n",
				infile_orig);
		fprintf(fpstatus,
				"FYI_until_pass_FOUND:found until pass Polaris instruction in %s! skipping\n",
				infile_orig);
		align_loc = AP - vector;
		*(AP + 0) = ' ';		/* u */
		*(AP + 1) = ' ';		/* n */
		*(AP + 2) = ' ';		/* t */
		*(AP + 3) = ' ';		/* i */
		*(AP + 4) = ' ';		/* l */
		*(AP + 5) = ' ';		/*   */
		*(AP + 6) = ' ';		/* p */
		*(AP + 7) = ' ';		/* a */
		*(AP + 8) = ' ';		/* s */
		*(AP + 9) = ' ';		/* s */
		if (*(AP + 10) == ';')
			*(AP + 10) = ' ';	/* ; */
	}
	return (0);
}

int check_for_subroutine(char *vector)
{
	/* no need to do anything with aligns */
	char *AP;
	int subroutine_loc;
	subroutine_loc = -1;
	if ((AP = strstr(vector, "subroutine")) != NULL) {
		fprintf(fperrors,
				"FYI_SUBROUTINE_FOUND:found Polaris subroutine in [%s]! You must deal with this yourself\n",
				infile_orig);
		fprintf(fpstatus,
				"FYI_SUBROUTINE_FOUND:found Polaris subroutine in [%s]! You must deal with this yourself\n",
				infile_orig);
		subroutine_loc = AP - vector;
		*AP = '\0';				/* wipe out the line entirely!!! */
	}
	return (0);
}


int check_for_scan(char *vector)
{
	char *SP;
	int scan_loc;
	scan_loc = -1;
	if ((SP = strstr(vector, "ScanIn")) != NULL ||
		(SP = strstr(vector, "ScanOut")) != NULL ||
		(SP = strstr(vector, "ScanSetCoupled")) != NULL ||
		(SP = strstr(vector, "ScanTest")) != NULL ||
		(SP = strstr(vector, "ChainLength")) != NULL ||
		(SP = strstr(vector, "ScanSetUnCoupled")) != NULL) {
//      fprintf(fperrors,"FYI_SCAN_FOUND:found Scan[%s]\n",infile_orig);
		fprintf(fpstatus, "FYI_SCAN_FOUND:found Scan[%s]\n", infile_orig);
		scan_loc = SP - vector;
//      *(SP+0)=' ';/* S */
//      *(SP+1)=' ';/* c */
//      *(SP+2)=' ';/* a */
//      *(SP+3)=' ';/* n */
		return (1);				/* set return to TRUE */
	}
	return (0);					/* else not Scan */
}

int check_for_vector(char *vector, char *result_vector, int *vs, int *ve,
					 char *label)
{
	char *OP1, *CP1, *OB1, *CB1, *SC, hold, *LBL, *ptr;
	int PAR_FOUND = 0;
	label[0] = '\0';
	*vs = *ve = 0;
	if ((OP1 = strchr(vector, '(')) != NULL) PAR_FOUND++;
	if ((CP1 = strchr(vector, ')')) != NULL) PAR_FOUND++;
	if ((OB1 = strchr(vector, '[')) != NULL) PAR_FOUND++;
	if ((CB1 = strchr(vector, ']')) != NULL) PAR_FOUND++;
	if ((SC = strchr(vector, ';')) != NULL) PAR_FOUND++;
	else SC = vector+strlen(vector);
	if (PAR_FOUND < 4) return (0);				/* can't be VECTOR */
	if ((LBL = strchr(vector, ':')) != NULL) {	/* found a label! */
		hold = *LBL;
		*LBL = '\0';
		strcpy(label, vector);
		fprintf(fpstatus, "Found label [%s] in [%s]\n", label,
				infile_orig);
		for (ptr = vector; ptr <= LBL; ptr++)
			*ptr = ' ';
	}
	*vs = OB1 - vector;
	*ve = CB1 - vector;
	hold = *(SC + 1);
	*(SC + 1) = '\0';
	expand_vector(result_vector, vector, OB1, __LINE__, __FILE__);
	*(SC + 1) = hold;
	return (SC - vector);		/* this gives the location for the ';', i.e. the end of the vector */
}

int check_for_SET(char *vector, char *result_vector, int *vs, int *ve)
{
	char *SP, *OP1, *CP1, *OP2, *CP2, *SC, hold;
	int SET_FOUND = 0;
	*vs = *ve = 0;
	if ((SP = strstr(vector, "MSet")) != NULL) {
		SET_FOUND = 1;
	}
	else if ((SP = strstr(vector, "DSet")) != NULL) {
		SET_FOUND = 2;
	}
	else if ((SP = strstr(vector, "ISet")) != NULL) {
		SET_FOUND = 3;
	}
	if ((SP = strstr(vector, "mset")) != NULL) {
		SET_FOUND = 1;
		*(SP + 0) = 'M';
		*(SP + 1) = 'S';
	}							/* capitalize it */
	else if ((SP = strstr(vector, "dset")) != NULL) {
		SET_FOUND = 2;
		*(SP + 0) = 'D';
		*(SP + 1) = 'S';
	}							/* capitalize it */
	else if ((SP = strstr(vector, "iset")) != NULL) {
		SET_FOUND = 3;
		*(SP + 0) = 'I';
		*(SP + 1) = 'S';
	}							/* capitalize it */
	if (SET_FOUND == 0) return (0);				/* can't be Set */
	if ((OP1 = strchr(vector, '[')) == NULL || (CP1 = strchr(vector, ']')) == NULL) return (0);				/* can't be Set */
	*OP1 = ' ';
	*CP1 = ' ';
	/* need two sets, one for Set, one for pinset info */
	if ((OP2 = strchr(vector, '[')) == NULL || (CP2 = strchr(vector, ']')) == NULL) return (0);				/* can't be Set */
	*OP1 = '[';
	*CP1 = ']';
	if ((SC = strchr(vector, ';')) == NULL) return (0);				/* can't be Set */
	*vs = SP - vector;
	*ve = SC - vector;
	hold = *(SC + 1);
	*(SC + 1) = '\0';
	expand_vector(result_vector, vector, OP2, __LINE__, __FILE__);
//	fprintf(stdout,"R[%s]\nV[%s]\n",result_vector,vector);
//  fprintf(fpstatus,"MSET/DSET/ISET[%d][%s]\n",SET_FOUND,result_vector);
	*(SC + 1) = hold;
	return (SC - vector);
}

int get_count(char *ptr)
{
	int retval;
	char *ptrl;
	retval = -2;
	if ((ptrl = strstr(ptr, "forever")) != NULL) {
		retval = RET_FOREVER;
	}
	else
		retval = (int) strtol(ptr, NULL, 10);
	if (retval == -2) {
		fprintf(stderr, "Unknown repeat count[%s],exiting\n", ptr);
		fprintf(fperrors, "Unknown repeat count[%s]\n", ptr);
		exit(1);
	}
	return (retval);
}


/* a simple function to get the size of the repeat or match */
char *get_count_orig(char *ptr, int offset, long *count, char *vector)
{
	char *retptr, *ptr2, *ptrt;
	int i, theressomethinginfront = 0, pos;

	*count = 0;
	ptrt = vector;
	retptr = ptr + offset;
	pos = ptr - vector;
	if (debug & 4)
		fprintf(fpstatus, "WE ACTUALLY MADE IT HERE %s\n", vector);
	for (i = 0; i < pos; i++)
		if (vector[i] != ' ' && vector[i] != '\t') {
			fprintf(fpstatus,
					"NON_FATAL_ERROR:We can't deal with this repeat!![%s]%d %d\n",
					vector, i, offset);
			fprintf(fperrors,
					"NON_FATAL_ERROR:%s:We can't deal with this repeat!![%s]%d %d\n",
					progstr, vector, i, offset);
			theressomethinginfront = 1;
			*count = 0;
			fprintf(fpout1, "%s", vector);
			return (0);
		}
	if ((ptr2 = strstr(vector, "(*")) != NULL && strstr(vector, "repeat") != 0) {	/* blank out any comments before looking at this vector */
		fprintf(fpstatus, "BLANKING COMMENT WITH REPEAT:[%s] to: ", ptr);
		for (i = (int) (ptr2 - ptrt); i < strlen(vector); i++) {
			if (vector[i] != '*' || vector[i + 1] != ')') {
				vector[i] = ' ';
			}
			else
				break;
		}
		if (vector[i] == '*' && vector[i + 1] == ')') {
			vector[i] = ' ';
			vector[i + 1] = ' ';
		}						/* finish off the tail */
		fprintf(fpstatus, "[%s]\n", vector);
	}
	while (!isdigit((int) *retptr) && *retptr != 0)
		retptr++;
	while (isdigit((int) *retptr)) {
		*count = *count * 10 + (*retptr - '0');
		retptr++;
	}
	if (debug & 4)
		fprintf(fpstatus, "WE ACTUALLY MADE IT HERE\n");
	if (*count == 0) {			/* check for 'forever' */
		if (0 != strstr(ptr, "forever"))
			*count = RET_FOREVER;
	}
	return (retptr);
}
