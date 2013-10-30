#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "include_vcp.h"
#include "aliasmap.h"

int vector_convert(int *beginflag, char *vector, char *mod_vector,
	struct SETvS *SETS, char *out_vector1, char *DMI, char *pb_vector) {
	char *ptr, *ptrPB, testvv[1025];
	long mset, dset, iset;
	static long lastmset, lastdset, lastiset;
	int vectb, vecte, vect, vmset, vdset, viset, j, AC, PB, rPB;
	int SET, GCTMATCHMOD, outpos, pinnum, i, verrorflag;
	int dset0val, dset1val, DSET3, testv;
	static int EMuMSET = 0, EMuDSET = 0, EMuISET = 0;
	const char pbstr[65] = PBCHARS;
	int trace = 0;
	
/* real vector */
	j = 0;
	*beginflag = 2;
	ptr = mod_vector;
	while (0 != isspace((int) *ptr)) ptr++;
	while (0 == isspace((int) *ptr) && *ptr != '(') SETS->WFT[j++] = *(ptr++);
	SETS->WFT[j] = '\0';
	GCTMATCHMOD = 0;
	SET = -1;
	for (SET = 0; SET < SETS->maxgctDSET; SET++) {
//		if (strcmp(SETS->WFT,"StbOffCondtnEven")==0) fprintf(stdout,"GCTX[%s]=%d\n",SETS->GCTMODNAME[SET],strcmp(SETS->WFT, SETS->GCTMODNAME[SET]));
		if (0 == strcmp(SETS->WFT, SETS->GCTMODNAME[SET])) {
			GCTMATCHMOD = 1;
			break;
			}
		}
	if (GCTMATCHMOD == 0) {
		fprintf(fperrors,"MOSTLY-FATAL:GCTSET NOT FOUND[%s] in mod file [%s],vectors will be don't care\n", SETS->WFT, infile_orig);
		fprintf(stderr,"MOSTLY-FATAL:GCTSET NOT FOUND[%s] in mod file [%s],vectors will be don't care\n", SETS->WFT, infile_orig);
	}
// APS: reenable the following line and change the search to debug character assignments
//	if (strcmp(SETS->WFT,"RESETCMPCycle")==0) {trace = 1; fputc('\n',stdout) ;} else trace = 0;
	SETS->used[SET] = 1;
	ptr = strchr(mod_vector, '(');
	if (ptr == NULL) return (1);
	iset = 0;
/* MSET */
	ptr = get_count(ptr, 1, &mset, 5);
/* DSET */
	ptr = get_count(ptr, 1, &dset, 6);
/* ISET */
	ptr = get_count(ptr, 1, &iset, 7);
	ptr = strchr(mod_vector, '[');
	if (ptr == NULL) return (1);
	vectb = (ptr - mod_vector) + 1;
	ptr = strchr(mod_vector, ']');
	if (ptr == NULL) return (1);
	vecte = (ptr - mod_vector);
	if (DEBUG)
		fprintf(fpstatus,"In vector,WFT=[%s],M=%ld,D=%ld,I=%ld,b=%d,e=%d,l=%d\n",
				SETS->WFT, mset, dset, iset, vectb, vecte, vecte - vectb);
	verrorflag = 0;
	sprintf(DMI, "(%ld,%ld,%ld)", mset, dset, iset);
	if ((vecte - vectb) != MOD2_SIZE) {
		fprintf(stderr,"FATAL_ERROR: Number of pins<%d> in pattern <%s> does not match pins in cycletbl definition file<%d> approxline: %ld\n",
				vecte - vectb, infile_orig, MOD2_SIZE, readlinenum);
		fprintf(fperrors,"FATAL_ERROR:%s: Number of pins<%d> in pattern <%s> does not match pins in cycletbl definition file<%d> approxline: %ld\n",
				progstr, vecte - vectb, infile_orig, MOD2_SIZE, readlinenum);
		exit(9);
	}
//fprintf(stdout,"%s(%ld)M[%d]\n",SETS->WFT,mset,SETS->DSETPTR[mset*VECTORLEN+1]);
	outpos = 0;
	pinnum = 0;					/* incremented at the end of this for loop */

/* added 06/11/2009, used specifically in subroutines to get the prior mset/dset */
	if (mset == 0) {
		if (EMuMSET == 0) {
			EMuMSET = 1;
			fprintf(fpstatus, "pat[%s] uses mset[0]; using previous mset\n", infile_orig);
		}
		mset = lastmset;
	}
	else
		lastmset = mset;
	if (dset == 0) {
		if (EMuDSET == 0) {
			EMuDSET = 1;
			fprintf(fpstatus, "pat[%s] uses dset[0]; using previous dset\n", infile_orig);
		}
		dset = lastdset;
	}
	else
		lastdset = dset;
	if (iset == 0) {
		if (EMuISET == 0) {
			EMuISET = 1;
			fprintf(fpstatus, "pat[%s] uses iset[0]; using previous iset\n", infile_orig);
		}
		iset = lastiset;
	}
	else
		lastiset = iset;
	testvv[vecte+1]='\0';
//	fprintf(stdout,"{%s}\n",priorstate);
	for (i = vectb; i < vecte; i++) {
		PB = AM_DONOTHINGPAD;
		vect = mod_vector[i] - '0';
		vmset = SETS->MSETPTR[mset * VECTORLEN + pinnum];
		vdset = SETS->DSETPTR[dset * VECTORLEN + pinnum];
		viset = SETS->ISETPTR[iset * VECTORLEN + pinnum];
		if (viset == 1) vect = 1 - vect;	/* invert the data state if ISET=1 */
		dset0val = SETS->VECTMOD[0][SET][pinnum];
		dset1val = SETS->VECTMOD[1][SET][pinnum];
		DSET3 = 0;
		if (trace == 1) {
			fprintf(stdout,"[%3d]0[%c]1[%c]M[%ld]m[%d]D[%ld]d[%d]i[%d]v[%d]p[%c]",pinnum,dset0val,dset1val,mset,vmset,dset,vdset,viset,vect,priorstate[pinnum]);
			}
		testvv[pinnum]='_';
		rPB = priorvect[pinnum];
		if (pbset[SET].DSET0[pinnum] == AM_NOMUX || pbset[SET].DSET1[pinnum] == AM_NOMUX) {PB = AM_NOMUX;testv='1';}
		else if (priorstate[pinnum] != FC_WINDOWOPEN && priorstate[pinnum] != FC_WINDOWOPENZ) {PB = AM_DONOTHINGPAD;testv='2';}
//		else if (pbset[SET].DSET0[pinnum] == AM_DONOTHINGPAD) {PB = AM_DONOTHINGPAD;testv='3';}
		else if (pbset[SET].DSET0[pinnum] == AM_DONOTHINGPAD) { /* this is a new waveform entry, if strobing we need to the entry state continue... */
			testv='3';
			PB = (vect == 0)?AM_continueLO:AM_continue;
			/* this probably gets re-set below... */
			}
		else if (vdset == 0) {PB = pbset[SET].DSET0[pinnum];testv='4';}
		else                 {PB = pbset[SET].DSET1[pinnum];testv='5';}
		if (((ptrPB = strchr(pbstr,PB)) != NULL) && (priorvect[pinnum] == '1')) PB = *(ptrPB+1);

		testvv[pinnum] = testv; /* for debugging... */

		AC = alias_vcpvcs(vect, vmset, vdset, dset0val, dset1val, priorstate[pinnum]);
		if (trace == 1) {
			fprintf(stdout,"AC[%c]",AC);
			}
//		if (PB == AM_DONOTHINGPAD); /* Nope this definitely shouldn't be uncommented! */
		else if (AC == AM_continueDRV ) {/* no action if drive continue */
			PB = AM_DONOTHINGPAD;
			testvv[pinnum] = '6'; /* patch in if continue for debug ... */
			}
		else if (AC == AM_continueLO || AC == AM_continue) {/* continue to strobe if strobe continue */
			PB = AC; /* this is a new waveform entry, if strobing we need to the entry state continue... */
			testvv[pinnum] = '7'; /* patch in if continue for debug ... */
			}
		else if (AC == AM_maskD0 || AC == AM_maskD1 || AC == AM_maskHID0 || AC == AM_maskHID1 ) {/* modify if not continue */
			priorstate[pinnum] = FC_MASK; /* this is set for the next vector.... */
			priorvect[pinnum] = vect + '0';
			testvv[pinnum] = '8'; /* patch in if continue for debug ... */
			}
		else if (AC == AM_strobeoffLOD0 || AC == AM_strobeoffHID0 ||
					AC == AM_strobeoffLOD1 || AC == AM_strobeoffHID1 || 
					AC == AM_strobefloatoffD0 || AC == AM_strobefloatoffD1) {/* continue to strobe if the current cycle closes */
			PB = (priorvect[pinnum] == '0')?AM_continueLO:AM_continue; /* this is a new waveform entry, if strobing we need to the entry state continue... */
			priorstate[pinnum] = (vdset == 0)?dset0val:dset1val; /* this is set for the next vector.... */
			testvv[pinnum] = '9'; /* patch in if continue for debug ... */
			}
		else if (AC == AM_maskD0 || AC == AM_maskD1 || AC == AM_maskHID0 || AC == AM_maskHID1 ) {/* modify if not continue */
			priorstate[pinnum] = FC_MASK; /* this is set for the next vector.... */
			priorvect[pinnum] = vect + '0';
			testvv[pinnum] = '0'; /* patch in if continue for debug ... */
			}
		else {/* modify if not continue */
			priorstate[pinnum] = (vdset == 0)?dset0val:dset1val; /* this is set for the next vector.... */
			priorvect[pinnum] = vect + '0';
			testvv[pinnum] = '$'; /* patch in if continue for debug ... */
			}
		if (trace == 1) {
			fprintf(stdout,"ACP[%c]\n",AC);
			}

		out_vector1[outpos] = AC;
		pb_vector[outpos] = PB;
		outpos++;
		pinnum++;
	}
//	fprintf(stdout,"<%s>\n%s\n",testvv,pb_vector);
	if (verrorflag == 1) fprintf(stderr, "NON_FATAL_ERROR:Error in vector [%s]\n", vector);
	if (verrorflag == 1 && 1)
		fprintf(fperrors,"NON_FATAL_ERROR:%s:Error in vector [%s]file[%s]line:%ld\n",progstr, vector, infile_orig, readlinenum);
	out_vector1[outpos] = '\0';
	pb_vector[outpos] = '\0';
	if (DEBUG) fprintf(fpstatus, "^%s\n", out_vector1);
	if (DEBUG) fprintf(fpstatus,"@%s\n", pb_vector);
	return (verrorflag);
}
