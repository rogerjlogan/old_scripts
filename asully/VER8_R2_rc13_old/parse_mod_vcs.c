#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include_vcs.h"
#include "aliasmap.h"

int parse_mod_file(char *infile2)
{
	FILE *fpin2;
	char muxpins[GENERALBUFLEN + 1], readline[GENERALBUFLEN + 1];
	char muxcopy0[GENERALBUFLEN + 1], muxcopy1[GENERALBUFLEN + 1];
	int vectorstart, vectorend, muxcount;
	int i, j, sl, dropcnt = 0;
	char *ptr0, *ptr1, *ptr0e, *ptr1e, *ptrZ;

	if (NULL == (fpin2 = fopen(infile2, "r"))) {
		fprintf(stderr, "\nFATAL_ERROR:Input file [%s] not found\n", infile2);
		fprintf(fperrors, "\nFATAL_ERROR:%s:Input file [%s] not found\n", G_progstr, infile2);
		exit(1);
	}

	if (!G_QUIET) fprintf(stdout, "input file2 ok\n");

	muxpins[0] = '\0';
	while (fgets(readline, GENERALBUFLEN - 1, fpin2) != NULL) {
		readline[strlen(readline) - 1] = '\0';
		if (NULL != strstr(readline, "#USE_SIGNAL_HEADER:")) {
			strcpy(G_NORMALSGHDR,  readline + strlen("#USE_SIGNAL_HEADER:"));
			fprintf(fpstatus, "*** USER DEFINED SIGNAL HEADER:<%s> *** [file:%s]\n", G_NORMALSGHDR, G_infile1);
		}
		else if (NULL != strstr(readline, "#REMOVE_MUX")) {
			NOMUX = 1;
			fprintf(stdout, "*** REMOVING_MUXPINS!\n");
			fprintf(fpstatus, "*** REMOVING_MUXPINS!\n");
		}
		else if (readline[0] == '<') {
			vectorstart = (int) (strchr(readline, '<') - &readline[0]) + 1;
			vectorend = (int) (strchr(readline, '>') - &readline[0]);
			readline[vectorend] = '\0';
			strcpy(G_GCTMODNAME[G_maxgctSET], &readline[vectorstart]);
			readline[vectorend] = '>';
			ptr0 = strchr(readline, '[');
			if (ptr0 == NULL) {
				fprintf(stderr, "FATAL_ERROR:BAD D0 GCT LINE![%s]\n", readline);
				fprintf(fperrors, "FATAL_ERROR:%s:BAD D0 GCT LINE![%s]\n", G_progstr, readline);
				exit(1);
			}
			ptr1 = strchr(ptr0 + 1, '[');
			if (ptr1 == NULL) {
				fprintf(stderr, "FATAL_ERROR:BAD D1 GCT LINE![%s]\n", readline);
				fprintf(fperrors, "FATAL_ERROR:%s:BAD D1 GCT LINE![%s]\n", G_progstr, readline);
				exit(1);
			}
			ptr0e = strchr(ptr0, ']');
			if (ptr0e == NULL) {
				fprintf(stderr, "FATAL_ERROR:BAD D0 GCT LINE![%s]\n", readline);
				fprintf(fperrors, "FATAL_ERROR:%s:BAD D0 GCT LINE![%s]\n", G_progstr, readline);
				exit(1);
			}
			ptr1e = strchr(ptr1, ']');
			if (ptr1e == NULL) {
				fprintf(stderr, "FATAL_ERROR:BAD D1 GCT LINE![%s]\n", readline);
				fprintf(fperrors, "FATAL_ERROR:%s:BAD D1 GCT LINE![%s]\n", G_progstr, readline);
				exit(1);
			}
			vectorstart = (int) (ptr0 - &readline[0]) + 1;
			vectorend = (int) (ptr0e - &readline[0]) - 1;
			G_MOD2_SIZE = vectorend - vectorstart + 1;
			for (j = 0, i = vectorstart; i <= vectorend; j++, i++) {
				G_VECTD0[G_maxgctSET][j] = readline[i];
//				if (G_VECTD0[G_maxgctSET][j]>'z' || G_VECTD0[G_maxgctSET][j]<'A') fprintf(stderr,"ERROR[%c]\n",G_VECTD0[G_maxgctSET][j]);
				}
			G_VECTD0[G_maxgctSET][j] = '\0';
			vectorstart = (int) (ptr1 - &readline[0]) + 1;
			vectorend = (int) (ptr1e - &readline[0]) - 1;
			for (j = 0, i = vectorstart; i <= vectorend; j++, i++) {
				G_VECTD1[G_maxgctSET][j] = readline[i];
//				if (G_VECTD1[G_maxgctSET][j]>'z' || G_VECTD1[G_maxgctSET][j]<'A') fprintf(stderr,"ERROR[%c]\n",G_VECTD1[G_maxgctSET][j]);
				}
			G_VECTD1[G_maxgctSET][j] = '\0';
			G_maxgctSET++;
		}
		else if (readline[0] == SCANLINE) {
			/* its a scan line. No more distinction between In and Out! */
			ptr0 = strchr(readline, ':');
			if (ptr0 == NULL) {
				fprintf(stderr, "FATAL_ERROR:BAD GCT SCAN DEF LINE![%s]\n", readline);
				fprintf(fperrors, "FATAL_ERROR:%s:BAD GCT SCAN DEF LINE![%s]\n", G_progstr, readline);
				exit(1);
			}
			*ptr0 = '\0';
			strcpy(G_scandata[G_scanhdrs].scanhdr, &readline[1]);
			G_scandata[G_scanhdrs].shlen = strlen(G_scandata[G_scanhdrs].scanhdr);
			sl = strlen(readline);
			G_scandata[G_scanhdrs].scanpins = 0;
			while ((ptr1 = strchr(ptr0 + 1, '[')) != NULL) {
				*ptr1 = '\0';
				strcpy(G_scandata[G_scanhdrs].scanpinname[G_scandata[G_scanhdrs].scanpins], ptr0 + 1);
				G_scandata[G_scanhdrs].index[G_scandata[G_scanhdrs].scanpins] = strtol(ptr1 + 1, &ptr0, 10);
				G_scandata[G_scanhdrs].scanpins++;
				ptr0++;
//				if ((ptr0 - readline) < (sl - 4)) ptr0++;
//				else break;
			}
			G_scanhdrs++;
			if (G_scanhdrs >= MAXSCANHDRS) {
				fprintf(stderr, "FATAL_ERROR:Too many scan headers![%s]\n", readline);
				fprintf(fperrors, "FATAL_ERROR:%s:Too many scan headers![%s]\n", G_progstr, readline);
				exit(1);
			}
		}

		else if (readline[0] == 'H') continue;			/* nothing to do if hexproc */
		else if (readline[0] == 'F') {
			ptrZ = readline;
			while (*ptrZ != '\0') {
				if (*ptrZ == '.') dropcnt++;
				ptrZ++;
			}
			fprintf(stdout, "DROPCNT[%d]\n", dropcnt);
			continue;
		}
		else if (readline[0] == 'M') {
			ptr0 = strchr(readline + 2, '[');
			if (ptr0 == NULL) {
				fprintf(stderr, "Error in mod file[%s],exiting\n", readline);
				exit(1);
			}
			strcpy(muxpins, ptr0);
			continue;
		}
		if (readline[0] == 'P') {
			continue;
		}						/* PINGROUP, these are really comments */
		if (readline[0] == '/') {
			strcpy(G_pinhead[G_pinheadcount], readline);
			G_pinheadcount++;
			continue;
		}						/* G_pinheader info */
	}

	if (muxpins[0] != '\0') {
		for (j = 0; j < G_maxgctSET; j++) {
			for (muxcount = i = 0; i < strlen(muxpins) - 1; i++) {
				muxcopy0[i + muxcount] = G_VECTD0[j][i];
				muxcopy1[i + muxcount] = G_VECTD1[j][i];
				if (muxpins[i] == 'M') {
					muxcount++;
					if (NOMUX == 0) {
						muxcopy0[i + muxcount] = G_VECTD0[j][i];
						muxcopy1[i + muxcount] = G_VECTD1[j][i];
					}
					else {
						muxcopy0[i + muxcount] = FC_NOMUX;
						muxcopy1[i + muxcount] = FC_NOMUX;
					}
				}
			}
			muxcopy0[i + muxcount] = '\0';
			muxcopy1[i + muxcount] = '\0';
			strcpy(G_VECTD0[j], muxcopy0);
			strcpy(G_VECTD1[j], muxcopy1);
		}						/* end maxgctDSET */
		G_MOD2_SIZE += muxcount;
	}
	G_MOD2_SIZE -= dropcnt;		/* reduce by any non-VM pins */
	fprintf(stdout, "MOD_SIZE{%d}\n", G_MOD2_SIZE);
	if (G_scanhdrs <= 0) {
		fprintf(fperrors, "ERROR: SCANPINS not properly identified in [%s] for [%s]\n", infile2, G_infile1);
		fprintf(stderr, "*** ERROR: SCANPINS not properly identified in [%s] for [%s] ***\n", infile2, G_infile1);
		exit(1);
	}
	/* FIXME APS: do we need to add mux pins here???? yes we do.. */
	for (j = i = 0; i <= (vectorend - vectorstart) + muxcount; i++) {
		G_HOLD_VECTOR[i] = AM_continueDRV;
		G_DPM_VECTOR[i] = AM_cpmdpm;
		G_SCANHOLD[i] = AM_continueDRV;
		if (muxpins[i+j] == 'M') {
			if (NOMUX) {
				G_HOLD_VECTOR[i+1] = AM_NOMUX;
				G_DPM_VECTOR[i+1] = AM_NOMUX;
				G_SCANHOLD[i+1] = AM_NOMUX;
			}
			else {
				G_HOLD_VECTOR[i+1] = AM_continueDRV;
				G_DPM_VECTOR[i+1] = AM_cpmdpm;
				G_SCANHOLD[i+1] = AM_continueDRV;
			}	
			j--;
			i++;
		}
	}
	G_HOLD_VECTOR[i] = '\0';
	G_DPM_VECTOR[i] = '\0';
	G_SCANHOLD[i] = '\0';

	return (0);
}
