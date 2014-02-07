/* parse_cyctbl() {} */

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
#include "aliasmap.h"

int parse_cyctbl(int actablelines, char *infile4, FILE * fpwaves,
				 FILE * fpinherit, FILE * fp_mod_file, int maxcyclen, char *muxpin)
{
	int OVERFLOWCHK = 0;
	int k, i, j, tbl, row;
	int forwardD0 = 0, forwardD1 = 0;
	int roger, pinorder[NUMPINS];
	char piningroup[NUMPINS + 1], PINNAME[PINSIZE];
	char CELL1[MEMOSTRLEN], CELL2[MEMOSTRLEN];
	char CELL1P[MEMOSTRLEN], CELL2P[MEMOSTRLEN];
	char CELL1C[MEMOSTRLEN], CELL2C[MEMOSTRLEN];
	char filler[CYCLEN + 1];
	struct FORMAT_SEARCH fmt_srch;
	struct MODCODE mc;
	int lmodcodeD0, lmodcodeD1;
	char dsetval0[NUMPINS], dsetval1[NUMPINS], tbuf[MEMOSTRLEN];
	long tell;
	char *actablebuf, *inheritbuf, *actablelist;
	WARNING = 0;
	k = 0;

	actablebuf = malloc(actablebufsize + 1);
	if (actablebuf == NULL) {
		fprintf(stderr,
				"Could not allocate memory for actablebuf, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for actablebuf, exiting\n");
		exit(1);
	}
	for (i = 0; i < actablebufsize + 1; i++)
		*(actablebuf + i) = '\0';
	fprintf(fpstatus,
			"allocated [%d] bytes for actablebuf @%p, source[%s,%d,%s]\n",
			actablebufsize, actablebuf, __FILE__, __LINE__, __FUNCTION__);

	inheritbuf = malloc(inheritbufsize + 1);
	if (inheritbuf == NULL) {
		fprintf(stderr,
				"Could not allocate memory for inheritbuf, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for inheritbuf, exiting\n");
		exit(1);
	}
	for (i = 0; i < inheritbufsize + 1; i++)
		*(inheritbuf + i) = '\0';
	fprintf(fpstatus,
			"allocated [%d] bytes for inheritbuf @%p, source[%s,%d,%s]\n",
			inheritbufsize, inheritbuf, __FILE__, __LINE__, __FUNCTION__);

	actablelist = malloc(actablelistsize + 1);
	if (actablebuf == NULL) {
		fprintf(stderr,
				"Could not allocate memory for actablelist, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for actablelist, exiting\n");
		exit(1);
	}
	for (i = 0; i < actablelistsize + 1; i++)
		*(actablelist + i) = '\0';

	fprintf(fpstatus,
			"allocated [%d] bytes for actablelist @%p, source[%s,%d,%s]\n",
			actablelistsize, actablelist, __FILE__, __LINE__,
			__FUNCTION__);
	actablebuf[0] = actablebuf[actablebufsize] = '\0';
	inheritbuf[0] = inheritbuf[inheritbufsize] = '\0';
	actablelist[0] = actablelist[actablelistsize] = '\0';

/* add muxpins to PINNAME */

/* add muxpins to "ALLPINS" */
	strcpy(PINNAME, "ALLPINS");
	if (NOMUX == 0 ) {
		for (i = 0; i < maxpin; i++) {
			if (muxpin[i] == 'M') {
				sprintf(tbuf, "+%sm", PIN[i]);
				strcat(PINNAME, tbuf);
			}
		}
	}
	
	fprintf(fpwaves, "WaveformTable %s {\n    Period \"%s\";\n","COMMON_WFT", tperiod);
	fprintf(fpwaves, "   Comment=\"This should be included in the second column of the zipper for all waveforms references\";\n");
	fprintf(fpwaves, "Cell \"%s\" %c CPM_CALLING_DPM {\n   Data 3 Other;\n   Drive {\n      EntryState DriveOn;\n      }\n   }\n",
			PINNAME, AM_cpmdpm);
	fprintf(fpwaves, "Cell \"%s\" %c HOLD_STATE {\n   Data 6;\n   Drive {\n      EntryState DriveOn;\n      }\n   }\n",
			PINNAME, AM_continueDRV);
	fprintf(fpwaves, "Cell \"%s\" %c SCANIN {\n   Data 6 Serial;\n   Drive {\n      EntryState DriveOn;\n      }\n   }\n",
			PINNAME, AM_scanin);
	fprintf(fpwaves, "Cell \"%s\" %c SCANOUT {\n   Data 6 Serial;\n   Drive {\n      EntryState DriveOn;\n      }\n   }\n",
			PINNAME, AM_scanout);
	fprintf(fpwaves, "}\n");
	fprintf(fpwaves, "WaveformTable %s {\n    Period \"%s\";\n", "ACTABLE", tperiod);
	fprintf(fpwaves, "   Comment=\"This table is mostly formats/Cells. All pins are not necessarily covered. The actual waveformtables inherit from these cells and associate pins into those waveformtables \";\n");

	fprintf(stderr, "processing:\n");
	for (tbl = 0; tbl < maxtbl; tbl++) {
		fprintf(stderr, "[%-20s]  ", cyctbl[tbl].tblname);
		if ((tbl % 4) == 3) fputc('\n', stderr);
		fflush(stderr);
		for (i = 0; i < maxpin; i++) {
			dsetval0[i] = FC_BAD;
			dsetval1[i] = FC_BAD;
		}
		dsetval0[maxpin] = '\0';
		dsetval1[maxpin] = '\0';
		for (i = 0; i < sizeof(PBCYC); i++) filler[i] = ' '; filler[i] = '\0';

		fprintf(fpinherit, "WaveformTable %s {\n   Period \"%s %s\";\n", cyctbl[tbl].tblname, tperiod, filler);
		if (maxstartstop == 0)
			fprintf(fpinherit,
					"   Comment=\"This table has NOT been verified!!!! Origins could be mis-applied if the origin is set elsewhere, but this specific polaris waveform doesnt set origins!!! It is up to the end user to fix and verify this!!!\";\n");

		for (row = 0; row < cyctbl[tbl].maxrow; row++) {
			if (cyctbl[tbl].valid[row] == 0) continue;		/* it was replaced with a pin replace */
			strcpy(CELL1, cycsets[cyctbl[tbl].rows[row]].dset0);
			strcpy(CELL2, cycsets[cyctbl[tbl].rows[row]].dset1);
			roger = resolve_list(cycsets[cyctbl[tbl].rows[row]].pin, piningroup, '1', '0', pinorder);
			strcpy(PINNAME, cycsets[cyctbl[tbl].rows[row]].pin);
/* add muxpins to PINNAME */
			MUXFLAG = 0;
			if (NOMUX == 0) {
				for (i = 0; i < maxpin; i++) {
					if (muxpin[i] == 'M' && piningroup[i] == '1') {
						MUXFLAG = 1;
						sprintf(tbuf, "+%sm", PIN[i]);
						strcat(PINNAME, tbuf);
					}
				}
			}
			sprintf(CELL1P, "(%s)", CELL1);	/* have to close because it could find something shorter */
			sprintf(CELL2P, "(%s)", CELL2);	/* have to close because it could find something shorter */
			sprintf(CELL1C, "(%s,", CELL1);	/* have to close because it could find something shorter */
			sprintf(CELL2C, "(%s,", CELL2);	/* have to close because it could find something shorter */

			fmt_srch.dset0cnt = fmt_srch.dset1cnt = 0;

			fprintf(fpstatus, "===\n");
			fprintf(fpstatus, "   finding C[%s] C[%s] %s\n", CELL1, CELL2, __FUNCTION__);
			lmodcodeD0 = lmodcodeD1 = FC_BAD;
			mc.D0cnt = mc.D1cnt = 0;
//===============
			for (i = 0; i < actablelines; i++) {
				/* this is ok because effectively its a loop of DSET0 and a loop of DSET1 */
				/* it will group the DSET pairs together */
				forwardD0 = forwardD1 = 0;
//          if (i>230 && i<240) fprintf(stdout,"C[%d][%s][%s][%s][%s]\n",i,CELL2P,CELL2C,acwaves[i].w,acwaves[i-1].w);
				if (strstr(acwaves[i].w, CELL1P) != NULL || strstr(acwaves[i].w, CELL1C) != NULL) {
// boundary1.........................................................................
					fprintf(fpstatus, "---\n");
					tell = ftell(fpwaves);	/* FIXME:this won't work now! */
					LASTI = i;
					mc.cellcntD0[mc.D0cnt] = cellcnt;	/* this is the 'before' cellcnt */
					process_waveforms(actablelines, cyctbl[tbl].tblname, cyclebuff, &tell, i, &forwardD0,
						 PINNAME, 0, fmt_srch.dset0cnt, &lmodcodeD0);
//            mc.D0c=lmodcodeD0; /* this is updated in remove duplicate cells */
					mc.ALLD0[mc.D0cnt++] = lmodcodeD0;
					mc.cellcntD0[mc.D0cnt] = cellcnt;	/* this is the 'after' cellcnt */
					if (mc.D0cnt > MAX_MOD_CODES)
						fprintf(stderr, "Too many mod codes source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					if (actablebuf[actablebufsize] != '\0')
						fprintf(stderr, "WARNING:actablebuf maxed, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					if (inheritbuf[inheritbufsize] != '\0')
						fprintf(stderr, "WARNING:inheritbuf maxed, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					if (actablelist[actablelistsize] != '\0')
						fprintf(stderr, "WARNING:actablelist maxed, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					if (OVERFLOWCHK != 0) {
						fprintf(stderr, "2OBAD i[%d], source[%s,%d,%s]\n", OVERFLOWCHK, __FILE__, __LINE__, __FUNCTION__);
						exit(1);
					}
					if (i < 0) {
						fprintf(stderr, "2BAD i[%s], source[%s,%d,%s]\n", acwaves[LASTI].w, __FILE__, __LINE__, __FUNCTION__);
						exit(1);
					}
				}
//boundary2..................................................................
//          if (i>230 && i<240) fprintf(stdout,"B[%d][%s][%s][%s][%s]\n",i,CELL2P,CELL2C,acwaves[i].w,acwaves[i-1].w);

				if (strstr(acwaves[i].w, CELL2P) != NULL || strstr(acwaves[i].w, CELL2C) != NULL) {
					fprintf(fpstatus, "---\n");
					mc.cellcntD1[mc.D1cnt] = cellcnt;	/* this is the 'before' cellcnt */
//              fprintf(stdout,"Z[%d][%s][%s][%s][%s]\n",i,CELL2P,CELL2C,acwaves[i].w,acwaves[i-1].w);
					process_waveforms(actablelines, cyctbl[tbl].tblname, cyclebuff, &tell, i, &forwardD1,
						 PINNAME, 1, fmt_srch.dset1cnt, &lmodcodeD1);
//            mc.D1c=lmodcodeD1; /* this is updated in remove duplicate cells */
					mc.ALLD1[mc.D1cnt++] = lmodcodeD1;
					mc.cellcntD1[mc.D1cnt] = cellcnt;	/* this is the 'after' cellcnt */
					if (mc.D1cnt > MAX_MOD_CODES)
						fprintf(stderr, "Too many mod codes source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					if (actablebuf[actablebufsize] != '\0')
						fprintf(stderr, "WARNING:actablebuf maxed, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					if (inheritbuf[inheritbufsize] != '\0')
						fprintf(stderr, "WARNING:inheritbuf maxed, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					if (actablelist[actablelistsize] != '\0')
						fprintf(stderr, "WARNING:actablelist maxed, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					if (OVERFLOWCHK != 0) {
						fprintf(stderr, "2OBAD2 OVERFLOWCHK[%d], source[%s,%d,%s]\n", OVERFLOWCHK, __FILE__, __LINE__, __FUNCTION__);
						exit(1);
					}
					if (i < 0) {
						fprintf(stderr, "2BAD2 i[%s], source[%s,%d,%s]\n", acwaves[LASTI].w, __FILE__, __LINE__, __FUNCTION__);
						exit(1);
					}
				}
				if (forwardD0 < 0 || forwardD1 < 0 || forwardD0 > MAX_EDGES
					|| forwardD1 > MAX_EDGES) {
					fprintf(stderr, "forward variable corrupted,fD0[%d] fD1[%d] in source[%s,%d,%s]\n",
							forwardD0, forwardD1, __FILE__, __LINE__, __FUNCTION__);
					exit(1);
				}
				/* This will move the pointer past the present set if it was more than one read */
//          if (i>230 && i<240) fprintf(stdout,"D[%d][%d]\n",forwardD0,forwardD1);
				if (forwardD0 > 0 || forwardD1 > 0) {
					if (forwardD0 > forwardD1) i += (forwardD0 - 1);
					else i += (forwardD1 - 1);	/* -1 because for loop does ++ */
//            fprintf(stdout,"THISNEXT[%s],%s\n",acwaves[i+1].w,__FUNCTION__);
				}

//boundary3..................................................................
			}					/* end of actablelines loop */
			remove_dupe_cells(cyclebuff, &mc);
			/* this function takes cyclebuff (global) as input and separates it */
			actablebuf[0] = '\0';
			inheritbuf[0] = '\0';
//      fprintf(fppreopt,"\n************************\nAFTER DUPE REMOVAL\n%s\n************************\n",cyclebuff);
			separate_actable(actablebuf, inheritbuf, actablelist, &mc);
			cyclebuff[0] = '\0';
//      fprintf(fpwaves,"%s",cyclebuff);
			fprintf(fpwaves, "%s", actablebuf);
			fprintf(fpinherit, "%s", inheritbuf);

			/* propagate this to all pins in the group */
			for (j = 0; j < maxpin; j++)
				if (piningroup[j] == '1') {
					dsetval0[j] = mc.D0c;
					dsetval1[j] = mc.D1c;
				}

		}						/* end tbl row... */
		/* { for brace matching... */
		fprintf(fpinherit, "}\n");	/* close the tbl */
		for (i = 0; i < (maxcyclen - strlen(cyctbl[tbl].tblname)); i++) filler[i] = ' ';
		filler[i] = '\0';
		fprintf(fp_mod_file, "<%s>%s[%s][%s]\n", cyctbl[tbl].tblname, filler, dsetval0, dsetval1);
//===============

	}							/* tbl */
	if (NOMUX) fprintf(fp_mod_file, "#REMOVE_MUX\n");
	fputc('\n', stderr);
	fprintf(fpwaves, "}\n");	/* close the tbl */
	if (WARNING > 0) {
		fprintf(stderr, "*** There were %d advisories written to %s ***\n", WARNING, TRANSLATION_STATUS);
		fprintf(stderr, "You should validate and/or fix these. source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
	}
	if (actablebuf[actablebufsize] != '\0')
		fprintf(stderr, "WARNING:actablebuf maxed, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
	if (inheritbuf[inheritbufsize] != '\0')
		fprintf(stderr, "WARNING:inheritbuf maxed, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
	if (actablelist[actablelistsize] != '\0')
		fprintf(stderr, "WARNING:actablelist maxed, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}
