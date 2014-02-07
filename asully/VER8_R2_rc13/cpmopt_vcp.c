#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "include_vcp.h"
#include "aliasmap.h"


int cpmoptimize(char *pattern)
{
	FILE *fpin, *fpout, *fpoutdpm;
	char outfile1[READLINELEN + 1], outfiledpm[READLINELEN + 1],
		infile1[READLINELEN + 1];
	char vector[MAXCPMOPTLINES][READLINELEN + 1],
		header[MAXCPMOPTLINES][READLINELEN + 1];
	char cpmvector1[READLINELEN + 1], cpmvector2[READLINELEN + 1],
		cpmvector3[READLINELEN + 1];
	char cpmwft1[READLINELEN + 1], cpmwft2[READLINELEN + 1],
		cpmsh1[READLINELEN + 1], cpmsh2[READLINELEN + 1];
	char comment[MAXCPMOPTLINES][READLINELEN + 1];
	char uinstr[MAXCPMOPTLINES][FILENAMELEN + 1];
	char wft[MAXCPMOPTLINES][MAXGCTLEN], sh[MAXCPMOPTLINES][MAXGCTLEN];
	char lbltbl[MAXCPMOPTLINES][FILENAMELEN + 1], tmpstr[FILENAMELEN + 1];
	char readstr[READLINELEN + 1], prog[READLINELEN + 1], *ptr,
		new_wft[MAXGCTLEN];
	char optpreprocrev[READLINELEN + 1];
	int lbl_tbl[MAXCPMOPTLINES];
	int curptr = 0, maxlbls = 0, maxlines = 0, hdrcnt = 0, rev = 0;
	int got_uinstr = 0, using_dpm = 0, dpmcount = 0, cpmrptlda = 64;
	int ustart, uend, vstart, vend, lstart, lend, cstart, cend,
		printedDPMBUFF = 0;
	int i, j, k, tmp1, tmp2, ded, nzckeep;
	char CNTRSTR[25], tmplblstr[50];
	strcpy(prog, progstr);
	rev = prog[strlen(prog) - 1 - 2];
	prog[strlen(prog) - 1 - 2] = '\0';
	fprintf(stderr, "entering optimization routine\n");
	sprintf(outfile1, "_%s.evo", pattern);
	if (NULL == (fpout = fopen(outfile1, "w"))) {
		fprintf(stderr,
				"\nFATAL_ERROR:Could not open output file [_%s] for output(opt)\n",
				outfile1);
		fprintf(fperrors,
				"\nFATAL_ERROR:%s:Could not open output file [_%s] for output(opt)\n",
				progstr, outfile1);
		exit(1);
	}
	sprintf(outfiledpm, "DPMO_%s.evo", pattern);
	if (NULL == (fpoutdpm = fopen(outfiledpm, "w"))) {
		fprintf(stderr,
				"\nFATAL_ERROR:Could not open output file [_%s] for output(opt)\n",
				outfiledpm);
		fprintf(fperrors,
				"\nFATAL_ERROR:%s:Could not open output file [_%s] for output(opt)\n",
				progstr, outfiledpm);
		exit(1);
	}
	sprintf(infile1, "%s.evo", pattern);
	if (NULL == (fpin = fopen(infile1, "r"))) {
		fprintf(stderr,
				"\nFATAL_ERROR:Could not open input file [%s] for input(opt)\n",
				infile1);
		fprintf(fperrors,
				"\nFATAL_ERROR:%s:Could not open input file [%s] for input(opt)\n",
				progstr, infile1);
		exit(1);
	}
	optpreprocrev[0] = '\0';
	lstart = 0;
	while (fgets(readstr, READLINELEN - 1, fpin) != NULL) {	/* ~A */
		if (readstr[0] == '\"' && readstr[1] == '+' && lstart == 0) {	/* this is for the pinheader */
			continue;
		}
		if (NULL != strstr(readstr, "{-FLAG-preprocess")) {
			strcpy(optpreprocrev, readstr);
			continue;
		}
		if (strlen(readstr) >= READLINELEN - 2) {
			fprintf(fpstatus, "LONG LINE [%s]\n", readstr);
			/* if we have a long line it must be due to a comment so 'trash' the extra data here */
			while (fgets(cpmvector3, READLINELEN - 1, fpin) != NULL)
				if (strlen(cpmvector3) <= (READLINELEN - 2))
					break;
				else
					fprintf(fpstatus, "LONG LINE [%s]\n", cpmvector3);
			readstr[READLINELEN - 2] = '\"';
		}
		readstr[strlen(readstr) - 1] = '\0';	/* remove trailing \n */
		if (DEBUG)
			fprintf(fpstatus, "[%s]\n", readstr);
		if (readstr[0] == '$') {
			lstart = 1;
			lend = strlen(readstr);
			for (j = 0, i = lstart; i <= lend; j++, i++)
				lbltbl[maxlbls][j] = readstr[i];
			lbltbl[maxlbls][j] = '\0';
			lbl_tbl[maxlbls] = maxlines;
			maxlbls++;
			if (maxlbls >= MAXCPMOPTLINES) {
				fprintf(stderr,
						"NON_FATAL_ERROR:CPM pattern [%s.evo] is too big to optimize(lbl)\n",
						pattern);
				fprintf(fperrors,
						"NON_FATAL_ERROR:%s:cpm pattern [%s.evo] is too big to optimize(lbl)\n",
						progstr, pattern);
				fprintf(fpstatus, "FYI:removing _%s.evo and DPMO_%s.evo\n",
						pattern, pattern);
				sprintf(readstr, "_%s.evo", pattern);
				if (0 != remove(readstr))
					perror("Error removing _file");
				sprintf(readstr, "DPMO_%s.evo", pattern);
				if (0 != remove(readstr))
					perror("Error removing DPMO_ file");
				return (-1);
			}
		}
		else if (NULL != (ptr = strchr(readstr, '*'))) {	/* ~D */
			vstart = (int) (ptr - &readstr[0]) + 1;
			vend = (int) (strchr(&readstr[vstart], '*') - &readstr[0]) - 1;
			for (j = 0, i = vstart; i <= vend; j++, i++)
				vector[maxlines][j] = readstr[i];
			vector[maxlines][j] = '\0';
			tmp1 = vend + 2;
			j = 0;
			while (readstr[tmp1] == ' ')
				tmp1++;
			while (readstr[tmp1] != ' ')
				wft[maxlines][j++] = readstr[tmp1++];
			wft[maxlines][j] = '\0';
			j = 0;
			while (readstr[tmp1] == ' ')
				tmp1++;
			while (readstr[tmp1] != ';')
				sh[maxlines][j++] = readstr[tmp1++];
			sh[maxlines][j] = '\0';
			uinstr[maxlines][0] = '\0';
			if (NULL != (ptr = strchr(readstr, '<'))) {
				if (NULL != strstr(readstr, "LDA")
					|| NULL != strstr(readstr, "CJMP")
					|| NULL != strstr(readstr, "COND")
					|| NULL != strstr(readstr, "FLAG")
					|| NULL != strstr(readstr, "LC"))
					got_uinstr = 1;
				ustart = (int) (ptr - &readstr[0]) + 1;
				uend = (int) (strchr(readstr, '>') - &readstr[0]) - 1;
				for (j = 0, i = ustart; i <= uend; j++, i++)
					uinstr[maxlines][j] = readstr[i];
				uinstr[maxlines][j] = '\0';
			}
			comment[maxlines][0] = '\0';
			if (NULL != (ptr = strchr(readstr, '"'))) {
				cstart = (int) (ptr - &readstr[0]) + 1;
				cend = (int) (strchr(ptr + 1, '"') - &readstr[0]) - 1;
				/* added check here in case we truncated the comment due to exceeding the buffer size */
				for (j = 0, i = cstart; i <= cend && i < strlen(readstr);
					 j++, i++)
					comment[maxlines][j] = readstr[i];
				comment[maxlines][j] = '\0';
			}
			maxlines++;
			if (maxlines >= MAXCPMOPTLINES && dpmcount == 0) {
				fprintf(stderr,
						"NON_FATAL_ERROR:CPM pattern [%s.evo] is too big to optimize\n",
						pattern);
				fprintf(fperrors,
						"NON_FATAL_ERROR:%s:cpm pattern [%s.evo] is too big to optimize\n",
						progstr, pattern);
				fprintf(fpstatus,
						"FYI: removing _%s.evo and DPMO_%s.evo\n", pattern,
						pattern);
				sprintf(readstr, "_%s.evo", pattern);
				if (0 != remove(readstr))
					perror("Error removing _file (too big)");
				sprintf(readstr, "DPMO_%s.evo", pattern);
				if (0 != remove(readstr))
					perror("Error removing DPMO_ file (too big)");
				return (-1);
			}
			if (maxlines >= MAXCPMTODPMLINES) {	/* ~G */
				if (got_uinstr) {	/* ~H */
					/* we have hit a non-dpm microinstruction so we can do any more in dpm */
				}				/* ~H~ */
				else {			/* only repeats *//* ~I */
					if (!printedDPMBUFF) {
						fprintf(fpstatus,
								"FYI:part of CPM pattern [%s.evo] can be buffered to DPM\n",
								pattern);
						if (DEBUG)
							fprintf(fperrors,
									"FYI:%s:part of CPM pattern [%s.evo] can be buffered to DPM\n",
									progstr, pattern);
						/* fprintf(fpstatus,"we can probably put all these lines in DPM...\n"); */
						printedDPMBUFF = 1;
					}
					if (using_dpm == 0) {	/* only print header on first loop */
						fprintf(fpoutdpm,
								"enVisionObject:\"bl8:R5.7\";\n\n");
						fprintf(fpoutdpm, "Pattern DPMO_%s {\n", pattern);
						fprintf(fpoutdpm, "    Type Dpm;\n");
						fprintf(fpoutdpm,
								"\" Pattern convertor: %s:%s by Anthony Sully compile_date:%s@%s\"\n",
								compilestr, progstr, datestr, timestr);
						fprintf(fpoutdpm,
								"\"      Pattern converted on:%s by:%s on host:%s \"\n\"      in pwd: %s\"\n",
								mydate, username, hostname, pwd);
						fprintf(fpoutdpm, "$DPMO_%s_st\n", pattern);
						for (i = 0; i < pinheadcount; i++)
							fprintf(fpoutdpm, "\" %s\"\n", &pinhead[i][2]);
					}
					for (i = 0; i < maxlines; i++) {	/* ~K */
						if (dpmcount == 0) {	/* first vectors of dpm can be used in cpm for LDA and RPT 64 *//* ~L */
							strcpy(cpmvector1, vector[0]);	/* preserve the first dpm for the LDA/RPT 64 in cpm */
							strcpy(cpmwft1, wft[0]);
							strcpy(cpmsh1, sh[0]);
							strcpy(cpmvector2, vector[0]);	/* second cpm must be hold */
							for (j = 0; j < strlen(cpmvector2); j++)
								if (cpmvector2[j] != ' ')
									cpmvector2[j] = AM_continueDRV;
							strcpy(cpmwft2, wft[0]);
							strcpy(cpmsh2, sh[0]);
							if (uinstr[0][0] != '\0') {	/* there is a repeat on the first vector */
								fprintf(fpstatus,
										"RPT on first vector[%s]\n",
										uinstr[0]);
								j = atoi(uinstr[0] + strlen("RPT "));
								if (j > 64) {	/* Steal the first DPM for the first two cpm vectors */
									strcpy(cpmvector2, vector[0]);	/* make second cpm vector the rest of the RPT of dpm vector 1 */
									strcpy(cpmwft2, wft[0]);
									strcpy(cpmsh2, wft[0]);
									cpmrptlda = j - 1;
									dpmcount += 0;
									i++;
								}
								else if (j > 2) {	/* Steal part of the first DPM for the first cpm */
									dpmcount += 0;
									sprintf(uinstr[0], "RPT %d", j - 1);
								}
								else {	/* must be RPT 2 */
									uinstr[0][0] = '\0';	/* remove the RPT 2 microinstruction */
								}
							}	/* there is a repeat on the first vector */
							else {	/* no repeat on first was dpm now cpm vector; check second vector */
								fprintf(fpstatus,
										"no RPT on first vector\n");
								i++;
								if (uinstr[1] != '\0') {
									j = atoi(uinstr[1] + strlen("RPT "));
									if (j > 63) {
										strcpy(cpmvector2, vector[i]);	/* make second cpm vector the rest of the RPT of dpm vector 1 */
										strcpy(cpmwft2, wft[i]);
										strcpy(cpmsh2, sh[i]);
										cpmrptlda = j;
										dpmcount += 0;
										i++;
									}
									else {	/* Steal part of the first DPM for the first cpm */
									}
								}
							}
						}
						fprintf(fpoutdpm, "*%s * %s %s;", vector[i],
								wft[i], sh[i]);
						if (uinstr[i][0] != '\0') {
							/* hopefully only RPT */
							j = atoi(uinstr[i] + strlen("RPT ")) - 1;
							dpmcount += j;
							fprintf(fpoutdpm, "<%s>", uinstr[i]);
							uinstr[i][0] = '\0';
						}
						if (comment[i][0] != '\0') {	/* ~V */
							fprintf(fpoutdpm, "\"%s\"", comment[i]);
							comment[i][0] = '\0';
						}
						fputc('\n', fpoutdpm);
						dpmcount++;
					}			/* ~K~ */
					maxlines = 0;
					using_dpm = 1;
				}				/* ~I~ */
			}					/* ~G~ */
		}						/* ~D~ */
		else {
			if (maxlines == 0) {
				strcpy(header[hdrcnt], readstr);
				hdrcnt++;		/* we need to add a closing brace which we are not saving */
				if (NULL != (ptr = strstr(readstr, prog))) {
					if (*(ptr + strlen(prog)) == rev)
						fprintf(fpstatus, "translator rev. ok\n");
					else {
						fprintf(fpstatus,
								"FYI:%s:translator rev. does not match %c (%c in %s)\n",
								progstr, rev, *(ptr + strlen(prog)),
								pattern);
						fprintf(fperrors,
								"FYI:%s:translator rev. does not match %c (%c in %s)\n",
								progstr, rev, *(ptr + strlen(prog)),
								pattern);
					}
				}
			}
			else if (DEBUG)
				fprintf(fpstatus, "ignoring [%s]\n", readstr);
			if (hdrcnt >= MAXCPMOPTLINES) {
				fprintf(stderr,
						"NON_FATAL_ERROR:[%s.evo](hdr) CPM pattern is too big to optimize\n",
						pattern);
				fprintf(stderr,
						"NON_FATAL_ERROR:[%s](hdr) writing header and clearing... this could be wrong\n",
						pattern);
				fprintf(fperrors,
						"NON_FATAL_ERROR:%s (hdr)[%s.evo]cpm pattern is too big to optimize\n",
						progstr, pattern);
				fprintf(fperrors,
						"NON_FATAL_ERROR:%s (hdr)[%s.evo]writing header to file and clearing... this could be wrong \n",
						progstr, pattern);
/*         sprintf(readstr,"\\rm -f _%s.evo",pattern);
         system(readstr); remove output cpm optomized file 
         return(-1); */
				for (i = 0; i < hdrcnt; i++) {
					fprintf(fpout, "%s\n", header[i]);
				}
				hdrcnt = 0;
			}
		}
	}
	if (DEBUG)
		for (i = 0; i < maxlines; i++)
			fprintf(fpstatus, "vector=[%s]\n", vector[i]);
	if (DEBUG)
		for (i = 0; i < maxlines; i++)
			fprintf(fpstatus, "%d:uI=[%s]\n", i, uinstr[i]);
	if (DEBUG)
		for (i = 0; i < maxlines; i++)
			fprintf(fpstatus, "sh=[%s]\n", sh[i]);
	if (DEBUG)
		for (i = 0; i < maxlbls; i++)
			fprintf(fpstatus, "lbl=[%s]@[%d]\n", lbltbl[i], lbl_tbl[i]);

/* First get rid of DEF_WFT */
	for (i = 0; i < maxlines; i++) {
		if (DEBUG)
			fprintf(fpstatus, "wft=[%s]\n", wft[i]);
		/* if used for scan optimization then don't allow ScanCycles */
		if (0 != strcmp(wft[i], DEF_WFT) && NULL == strstr(wft[i], "Scan")) {
			strcpy(new_wft, wft[i]);
			break;
		}
	}
	fprintf(fpstatus, "replacing [%s] with [%s] \n", DEF_WFT, new_wft);
	for (i = 0; i < maxlines; i++) {
		if ((0 == strcmp(wft[i], DEF_WFT))) {
			strcpy(wft[i], new_wft);
		}
		if (DEBUG)
			fprintf(fpstatus, "wft=[%s]\n", wft[i]);
	}
/* Next we are cpm-calling-dpm followed by match (not RPTP) then we can probably reduce the
   SDP,RPT by two and push the ddd vector onto the LC1,and MODE IFAIL vectors. This is a
   one time only deal starting at vector 3 for RPT,SDP and checking vectors 4 and 5. */
	if (NULL != strstr(uinstr[2], "SDP") &&
		NULL != strstr(uinstr[3], "LC1") &&
		NULL != strstr(uinstr[4], "MODE(IFAIL ON")) {
		tmp1 = 0;
		k = 0;
		while (uinstr[2][sizeof("RPT ") - 1 + k] != ',')
			tmp1 = 10 * tmp1 + uinstr[2][sizeof("RPT ") - 1 + k++] - '0';
		if (tmp1 > 3) {
			fprintf(fpstatus,
					"OPT1:We have found a candidate for LDA/RPT/LC1/MODE(IFAIL),line[%d][%s][%s][%s]R[%d]\n",
					i, uinstr[2], uinstr[3], uinstr[4], tmp1);
			tmp1 -= 2;
			strcpy(vector[3], vector[2]);
			strcat(uinstr[3], ",SDP");
			strcpy(vector[4], vector[2]);
			/* strcat(uinstr[4],",SDP"); */
			sprintf(uinstr[2], "RPT %d,SDP", tmp1);
		}
	}

/* ok, now see if any of the DC4,CJMPs only jmp back one vector and that vector has a repeat 
   if all conditions are met then we can remove the loop */

	for (nzckeep = 1; nzckeep <= 4; nzckeep++) {	/* added nzckeep for loop 06/05/05 */
		for (i = 1; i < maxlines; i++) {
			sprintf(CNTRSTR, "DC%d,CJMP", nzckeep);
			if (NULL == strstr(uinstr[i], CNTRSTR)
				|| NULL == strstr(uinstr[i - 1], "RPT"))
				continue;
			strcpy(readstr, &uinstr[i][sizeof("DC?,CJMP ") - 1]);	/* ok its only a sizeof */
			for (j = 0; j < maxlbls; j++)
				if (0 == strcmp(lbltbl[j], readstr))
					break;
			if (j < maxlbls && lbl_tbl[j] == i - 1) {
				tmp1 = 0;
				k = 0;
				while (uinstr[i - 1][sizeof("RPT ") - 1 + k] != '\0') {
					/* fprintf(fpstatus,":%c",uinstr[i-1][sizeof("RPT ")-1+k]); */
					tmp1 =
						10 * tmp1 + uinstr[i - 1][sizeof("RPT ") - 1 +
												  k++] - '0';
				}
				tmp2 = 0;
				k = 0;
				while (uinstr[i - 3][sizeof("LC? ") - 1 + k] != '\0') {
					/* fprintf(fpstatus,";%c",uinstr[i-3][sizeof("RPT ")-1+k]); */
					tmp2 =
						10 * tmp2 + uinstr[i - 3][sizeof("RPT ") - 1 +
												  k++] - '0';
				}
				/* note that we need to increment the LC number to get
				   the real count for the repeat */
				tmp2++;
				tmp2 *= tmp1;
				fprintf(fpstatus,
						"OPT2:We have found a candidate for LOOP removal,line[%d][%s][%s]R[%d]\n",
						i, uinstr[i], lbltbl[j], tmp2);
				lbl_tbl[j] = -1;
				lbltbl[j][0] = '\0';
				if (tmp2 < 65535) {
					vector[i][0] = sh[i][0] = wft[i][0] = uinstr[i][0] =
						'\0';
					vector[i - 2][0] = sh[i - 2][0] = wft[i - 2][0] =
						uinstr[i - 2][0] = '\0';
					vector[i - 3][0] = sh[i - 3][0] = wft[i - 3][0] =
						uinstr[i - 3][0] = '\0';
					sprintf(uinstr[i - 1], "RPT %d", tmp2);
				}
				else if (tmp2 < 65535 * 2) {
					vector[i - 2][0] = sh[i - 2][0] = wft[i - 2][0] =
						uinstr[i - 2][0] = '\0';
					vector[i - 3][0] = sh[i - 3][0] = wft[i - 3][0] =
						uinstr[i - 3][0] = '\0';
					strcpy(vector[i], vector[i - 1]);
					sprintf(uinstr[i], "RPT %d", 65535);
					tmp2 -= 65535;
					sprintf(uinstr[i - 1], "RPT %d", tmp2);
				}
				else if (tmp2 < 65535 * 3) {
					vector[i - 3][0] = sh[i - 3][0] = wft[i - 3][0] =
						uinstr[i - 3][0] = '\0';
					strcpy(vector[i - 2], vector[i - 1]);
					strcpy(vector[i], vector[i - 1]);
					sprintf(uinstr[i - 2], "RPT %d", 65535);
					tmp2 -= 65535;
					sprintf(uinstr[i], "RPT %d", 65535);
					tmp2 -= 65535;
					sprintf(uinstr[i - 1], "RPT %d", tmp2);
				}
				else if (tmp2 < 65535 * 4) {
					strcpy(vector[i - 3], vector[i - 1]);
					strcpy(vector[i - 2], vector[i - 1]);
					strcpy(vector[i], vector[i - 1]);
					sprintf(uinstr[i - 3], "RPT %d", 65535);
					tmp2 -= 65535;
					sprintf(uinstr[i], "RPT %d", 65535);
					tmp2 -= 65535;
					sprintf(uinstr[j], "RPT %d", tmp2);
				}
			}
		}
	}							/* for nzckeep */
/* if DC4,CJMP without a label and previous vector does not have a microinstruction (except RPT) then
   move the DC4,CJMP back one and delete the --- */
	for (i = 1; i < maxlines; i++) {
		if (vector[i][0] == '\0' || vector[i - 1][0] == '\0')
			continue;
/*   if (NULL!=strstr(uinstr[i],"DC4,CJMP") && uinstr[i-1][0]=='\0' ){ */
		/* should probably check if there is a label in between */
/*      fprintf(fpstatus,"We have found a candidate for DC4,CJMP relocation,line[%d][%s]R[%d]\n",i,uinstr[i],tmp2);
      strcpy(uinstr[i-1],uinstr[i]);
      vector[i][0]=uinstr[i][0]=wft[i][0]='\0'; */
/* ***** THIS CODE IS NEW  NEEDS CHECKOUT ******* */
		if (NULL != strstr(uinstr[i], "DC4,CJMP")
			|| NULL != strstr(uinstr[i], "DC3,CJMP")
			|| NULL != strstr(uinstr[i], "DC2,CJMP")
			|| NULL != strstr(uinstr[i], "DC1,CJMP")) {
/*   if (NULL!=strstr(uinstr[i],"CJMP") ) { */
			if (strstr(uinstr[i - 1], "DC") == NULL && strstr(uinstr[i - 1], "LC") == NULL && strstr(uinstr[i - 1], "COND") == NULL && strstr(uinstr[i - 1], "LDA") == NULL && strstr(uinstr[i - 1], "LDA") == NULL && strstr(uinstr[i - 1], "MODE") == NULL && strstr(uinstr[i - 1], "FLAG") == NULL && strstr(uinstr[i - 1], "NZC") == NULL) {	/* added NZC 06/05/05 */
				/* we allow only RPT or nothing on the previous vector */
				ded = 0;
				if (strstr(uinstr[i - 1], "RPT") != NULL) {	/* decrement rpt copy extra vector down */
					fprintf(fpstatus, "It appears there is a RPT[%s]\n",
							uinstr[i - 1]);
					for (j = strlen("RPT "); j < strlen(uinstr[i - 1]);
						 j++)
						if (uinstr[i - 1][j] <= '9'
							&& uinstr[i - 1][j] >= '0') {
							ded = ded * 10 + uinstr[i - 1][j] - '0';
						}
				}
			}
			/* need check if there is a label in between!! for nested loops!!! */
			fprintf(fpstatus,
					"OPT3:We have found a candidate for DC?,CJMP relocation,line[%d][%s]R[%d]\n",
					i, uinstr[i], tmp2);
/*         fprintf(fpstatus,"OPT3:We have found a candidate for CJMP relocation,line[%d][%s]R[%d]\n",i,uinstr[i],tmp2); */
			strcpy(tmplblstr, &uinstr[i][0 + sizeof("DC?,CJMP ")]);
			for (j = 0; j < maxlbls; j++) {
				if (NULL != strstr(lbltbl[j], tmplblstr)) {
					fprintf(fpstatus, "found label %s %d %d %d\n",
							lbltbl[j], j, i, lbl_tbl[j]);
					if (lbl_tbl[j] != i - 2) {
						fprintf(fpstatus,
								"Nope, sorry loop not adjacent\n");
						ded = -1;
						continue;
					}
				}
			}
			if (ded == -1)
				continue;
			if (ded == 0) {
				fprintf(fpstatus, "There is no repeat\n");
				strcpy(uinstr[i - 1], uinstr[i]);
				vector[i][0] = uinstr[i][0] = wft[i][0] = '\0';
			}
			else if (ded == 2) {
				fprintf(fpstatus, "The repeat is 2\n");
				uinstr[i - 1][0] = '\0';
				strcpy(vector[i], vector[i - 1]);
			}
			else {
				fprintf(fpstatus, "The repeat is [%d]\n", ded);
				sprintf(uinstr[i - 1], "RPT %d", ded - 1);
				strcpy(vector[i], vector[i - 1]);
			}
		}
	}

/* Look for IFAIL OFF followed by IFAIL ON, remove both if found */
	for (i = 2; i < maxlines; i++) {
		if (vector[i][0] == '\0' || vector[i - 1][0] == '\0'
			|| vector[i - 2][0] == '\0')
			continue;
		if (NULL != strstr(uinstr[i], "MODE(IFAIL ON,TCI ON") &&
			NULL != strstr(uinstr[i - 2], "MODE(IFAIL OFF,TCI OFF)") &&
			NULL != strstr(uinstr[i - 1], "LC1")) {
			fprintf(fpstatus,
					"OPT4:We have found a candidate for IFAIL OFF/ON removal,line[%d][%s][%s][%s]\n",
					i, uinstr[i - 2], uinstr[i - 1], uinstr[i]);
			vector[i][0] = uinstr[i][0] = wft[i][0] = '\0';
			vector[i - 2][0] = uinstr[i - 2][0] = wft[i - 2][0] = '\0';
		}
	}
/* if LC4 without a label and previous vector does not have a microinstruction then
   move the LC4 back one and delete the --- */
	for (i = 1; i < maxlines; i++) {
		if (vector[i][0] == '\0' || vector[i - 1][0] == '\0')
			continue;
		if (NULL != strstr(uinstr[i], "LC4") && uinstr[i - 1][0] == '\0') {
			/* should probably check if there is a label in between */
			fprintf(fpstatus,
					"OPT5:We have found a candidate for LC4 relocation,line[%d][%s]\n",
					i, uinstr[i]);
			strcpy(uinstr[i - 1], uinstr[i]);
			vector[i][0] = uinstr[i][0] = wft[i][0] = '\0';
		}
	}
/* if CJMP .-xx without a label and previous vector does not have a microinstruction then
   move the CJMP .-xx  back one change to CJMP . and delete the --- */
	for (i = 1; i < maxlines; i++) {
		if (vector[i][0] == '\0' || vector[i - 1][0] == '\0')
			continue;
		if (NULL != strstr(uinstr[i], "CJMP .-")
			&& uinstr[i - 1][0] == '\0') {
			ded = 0;
			for (j = strlen("CJMP .-"); j < strlen(uinstr[i]); j++)
				if (uinstr[i][j] <= '9' && uinstr[i][j] >= '0') {
					ded = ded * 10 + uinstr[i][j] - '0';
				}
			/* should probably check if there is a label in between */
			fprintf(fpstatus,
					"OPT6:We have found a candidate for CJMP .-xx(%d) relocation,line[%d][%s]\n",
					ded, i, uinstr[i]);
			ded--;
			if (ded == 0)
				strcpy(uinstr[i - 1], "CJMP .");
			else
				sprintf(uinstr[i - 1], "CJMP .-%d", ded);
			vector[i][0] = uinstr[i][0] = wft[i][0] = '\0';
		}
	}
/* Now, check if FLAG SEQF,COND NZC1,then RPT >3 */
	for (i = 4; i < maxlines; i++) {
		if ((NULL != strstr(uinstr[i - 4], "FLAG(SEQF OFF)") &&
			 NULL != strstr(uinstr[i - 3], "COND NZC1") &&
			 vector[i - 2][0] == '\0' && vector[i - 1][0] == '\0' &&
			 NULL != strstr(uinstr[i], "RPT ")) ||
			(NULL != strstr(uinstr[i - 2], "FLAG(SEQF OFF)") &&
			 NULL != strstr(uinstr[i - 1], "COND NZC1") &&
			 NULL != strstr(uinstr[i], "RPT "))
			) {
			/* if the vector contains a strobe then invalidate the action */
			if (NULL != strchr(vector[i], '0')
				|| NULL != strchr(vector[i], '1')) {
				fprintf(fpstatus,
						"Sorry, there is a strobe on the RPT for (SEQF/CONDNZC1/RPT)\n");
				continue;
			}
			tmp1 = 0;
			k = 0;
			while (uinstr[i][sizeof("RPT ") - 1 + k] != '\0')
				tmp1 =
					10 * tmp1 + uinstr[i][sizeof("RPT ") - 1 + k++] - '0';
			if (tmp1 > 3) {
				tmp1 -= 2;
				if (vector[i - 1][0] != '\0') {
					fprintf(fpstatus,
							"OPT7a:We have found a candidate for 1SEQF/CONDNZC1/RPT,line[%d][%s][%s]R[%d]\n",
							i, uinstr[i - 2], uinstr[i - 1], tmp1 + 2);
					strcpy(vector[i - 2], vector[i]);
					strcpy(vector[i - 1], vector[i]);
					sprintf(uinstr[i], "RPT %d", tmp1);
				}
				else {
					fprintf(fpstatus,
							"OPT7b:We have found a candidate for 2SEQF/CONDNZC1/RPT,line[%d][%s][%s]R[%d]\n",
							i, uinstr[i - 4], uinstr[i - 3], tmp1 + 2);
					strcpy(vector[i - 4], vector[i]);
					strcpy(vector[i - 3], vector[i]);
					sprintf(uinstr[i], "RPT %d", tmp1);
				}
			}
		}
	}
/* further optimizations: */
/* look for loops with LC4 of 2 or less with only two active vectors; 
     expand this into straight line (LC4+1) */

/* ?) look for matches with repeats; replace --- with vector. */
/* ?) look for adjacent rpts; replace --- with vector.
     may be able to push vectors down if inside loop. */

/* We are done!! spit out pattern */
	for (i = 0; i < hdrcnt; i++)
		fprintf(fpout, "%s\n", header[i]);
	fprintf(fpstatus, "CPMRPTLDA:%d USING_DPM:%d\n", cpmrptlda, using_dpm);
	if (cpmrptlda > 0 && using_dpm) {
		strcpy(cpmvector3, cpmvector1);
		for (i = 0; i < strlen(cpmvector3); i++)
			if (cpmvector3[i] != ' ')
				cpmvector3[i] = AM_continueDRV;
		fprintf(fpoutdpm, "* %s * %s %s; \"DUMMY VECTOR\"\n}\n", cpmvector3, cpmwft1, cpmsh1);	/* close out dpm */
		fclose(fpoutdpm);
		sprintf(readstr, "gzip -f DPMO_%s.evo", pattern);
		system(readstr);		/* gzip DPMO_ file */
		fprintf(fpout, "$%s_begin\n", pattern);
		fprintf(fpout, "* %s * %s %s; <LDA DPMO_%s_st>\n", cpmvector1,
				cpmwft1, cpmsh1, pattern);
		fprintf(fpout, "* %s * %s %s; <RPT %d>\n", cpmvector2, cpmwft2,
				cpmsh2, cpmrptlda);
		for (i = 0; i < strlen(cpmvector1); i++)
			if (cpmvector1[i] != ' ')
				cpmvector1[i] = AM_cpmdpm;
		while (dpmcount > MAX_RPT_CPM) {
			fprintf(fpout, "* %s * %s %s;<RPT %ld,SDP>\n", cpmvector1,
					cpmwft2, cpmsh2, (long) MAX_RPT_CPM);
			dpmcount -= MAX_RPT_CPM;
		}
		fprintf(fpout, "* %s * %s %s; <RPT %d,SDP>\n", cpmvector1, cpmwft2,
				cpmsh2, dpmcount);
	}
	else {
		fclose(fpoutdpm);
		sprintf(readstr, "DPMO_%s.evo", pattern);
		fprintf(fpstatus, "removing empty dpm pattern [%s]\n", outfiledpm);
		if (0 != remove(readstr))
			perror("Error removing empty DPMO_ file");
	}

	curptr = 0;
	tmp1 = 0;
	sprintf(tmpstr, "%s_begin", pattern);
	for (i = 0; i < maxlines; i++) {
		if (lbl_tbl[curptr] == i) {
			if (NULL != strstr(lbltbl[curptr], tmpstr)) {
				fprintf(fpout, "$%s_orig\n", lbltbl[curptr]);
			}
			else
				fprintf(fpout, "$%s\n", lbltbl[curptr]);
			curptr++;
			while (lbl_tbl[curptr] == -1 && curptr < maxlbls)
				curptr++;
		}
		if (vector[i][0] != '\0') {
			fprintf(fpout, "*%s * %s %s; ", vector[i], wft[i], sh[i]);
			if (uinstr[i][0] != '\0')
				fprintf(fpout, "<%s>", uinstr[i]);
			if (comment[i][0] != '\0')
				fprintf(fpout, "\"%s\"", comment[i]);
			fputc('\n', fpout);
		}
		else
			tmp1++;
	}
	if (optpreprocrev[0] != '\0')
		fprintf(fpout, "%s", optpreprocrev);
	fprintf(fpout, "}\n");		/* we didn't save this when reading  */
	fclose(fpout);
	fprintf(fpstatus,
			"Optimizations have removed %d redundant vectors in[%s]\n",
			tmp1, pattern);
	fprintf(fpstatus,
			"DPM pattern optimizations removed %d redundant vectors in[%s]\n",
			dpmcount, pattern);
	fprintf(fpstatus, "Backing up original file,\n");
	sprintf(readstr, "__%s.evo", pattern);
	if (0 != rename(infile1, readstr))
		perror("Error backing up original file to __file");
	fprintf(fpstatus, " moving optimizied pattern to correct name\n");
	if (0 != rename(outfile1, infile1))
		perror("Error renaming new file to real name");
	return (0);
}
