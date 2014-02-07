/* This program is covered by the GNU GPL license. Please see the file: COPYING.gz for the license info. */
/* original author: anthony_sully@ltx.com */

#ifndef __GNUC__
#include "local_date.h"
#define __TIME__ ""
#endif

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "include_vcs.h"
#include "aliasmap.h"
#include "chksum.cksum"

/* begin main function */
int main(int argc, char *argv[])
{

	/* file variables */
	FILE *fpin1, *fpout1, *fpout2;
	time_t generictime;

	long VN = 0, prev_VN, repeatdec, vmscan, scanat, scanatr, line = 0, linecnt, li;
	long scanatreal[MAXSCANCNT];
	long repforever[MAXREPFOREVER], repforeverend[MAXREPFOREVER];

	int commentflag, beginflag, vectorflag, lastitem;
	int commentON, errorflag, scanhold, EMuMSET = 0, EMuDSET = 0, EMuISET = 0;
//   int commentcount;
	int repeatcount, notgood = 0, pinnum, outpos, verrorflag;
	int scanfor, scanflag, scanflaghold, nomatch, found;
	int scanlength[MAXSCANNUM], scanhdrtbl[MAXSCANTBLLEN][MAXSCANNUM], maxscantbl = 0;
	int i, j, t1, t2, t3, t4, t5;
	int vect, msel, dsel, isel, vmset, vdset, viset, AC, wftfind;
	int lastmset, lastdset, lastiset;	/* doesn't need to be static since it is in main */
	int dset0val, dset1val;
	int debug = 0, gzip = 0, gunzip = 0, autogen = 0;
	int filein1 = 0, filein2 = 0;
	int repforeveropen = 0, repforeverlines = 0;
	int scanafor[MAXSCANCNT], scancnt = 0, scanpin;
	int maxrepforever = 0, foundgoodgct = 0;
	int vl, gctmatchmod, sl1, sl2, pc, bc, SSCdone, SSC, SSUC;
	int shindex[2], shlen[2], shpos[2];
	int SCANINWHICH = 0, sighdrfileexists;
	int NO_BACKGROUND_GZIP = 0, oktoprintcomment = 0;

	char infile2[FILENAMELEN], infilebuf[FILENAMELEN];
	char outfile1[FILENAMELEN], outfile2[FILENAMELEN];
	char pattern[FILENAMELEN], mydate[101];
	char env[GENERALBUFLEN + 1], *endptr;
	char printstring[READLINELEN + MAXERRORLEN + 1], vector[READLINELEN + 1];
	char mod_vector[READLINELEN + 1], keep_vector[READLINELEN + 1];
	char prev_vector1[READLINELEN + 1], prev_comment[READLINELEN + 1];
	char prev_WFT[MAXGCTLEN + 1], prev_errorstr[MAXERRORLEN + 1];
	char out_vector1[READLINELEN + 1], comment[READLINELEN + 1], WFT[MAXGCTLEN + 1], errorstr[MAXERRORLEN + 1];
	char dmi[15], prev_dmi[15];	/* only do repeat compression in VX125 mode */
	char buf_ssc[READLINELEN + 1], scansetstr[READLINELEN + 1];
	char scanin[8][MAXSCANLEN], scanout[8][MAXSCANLEN], scangct[MAXGCTLEN];
	char scanhdr[MAXSCANHDRLEN], pscanhdr[MAXSCANHDRLEN], scaninalias[MAXSCANORDERLEN];
	char LASTGCT[MAXGCTLEN], SCANRGCT[MAXSCANCNT][MAXGCTLEN];
	char scanoutSEL[MAXSCANORDERLEN], scanlbl[MAXSCANHDRLEN];
	char *Msetptr, *Dsetptr, *Isetptr;
	char repforevervec[MAXREPFOREVERLINES][READLINELEN + 1];
	char tempstr[READLINELEN + 1], *ptr, *tptr, *ptrk, *ptrSC;
//   char *ptr1;
	if (getenv("PROC_NO_BACKGROUND_GZIP") != NULL) NO_BACKGROUND_GZIP = 1;
	if (getenv("DEBUG_PROC") == NULL) debug = 0;
	else {
		strcpy(env, getenv("DEBUG_PROC"));
		debug = strtol(env, &endptr, 0);
		fprintf(stderr, "Turning on DEBUG![%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
	}

	/* command line stuff */
	strcpy(G_NORMALSGHDR, DFLTSGHDR);
	if (argc > 1) {
		if (strchr((char *) argv[1], '-') != NULL) {
			if (strchr((char *) argv[1], 's') != NULL) G_QUIET = 1;
			if (strchr((char *) argv[1], 'f') != NULL && argc >= 3) filein1 = 1;
			if (strchr((char *) argv[1], 'g') != NULL && argc >= 4) filein2 = 1;
			if (strchr((char *) argv[1], 'z') != NULL) gzip = 1;
			if (strchr((char *) argv[1], 'a') != NULL) autogen = 1;
		}
	}
	strcpy(G_progstr, __FILE__);
	strcpy(G_datestr, __DATE__);
	strcpy(G_timestr, __TIME__);
	if (getenv("PWD") != NULL) strcpy(G_pwd, getenv("PWD"));
	if (getenv("hostname") != NULL) strcpy(G_hostname, getenv("hostname"));
	else if (getenv("HOSTNAME") != NULL) strcpy(G_hostname, getenv("HOSTNAME"));
	/* the following works for CDE, don't know about others */
	else if (NULL != getenv("SESSION_SVR")) strcpy(G_hostname, getenv("SESSION_SVR"));
	else strcpy(G_hostname, "UNKNOWN_HOSTNAME");

	if (getenv("USER") != NULL) strcpy(G_username, getenv("USER"));
	strcpy(G_compilestr, argv[0]);
	generictime = time(0);
	strcpy(mydate, ctime(&generictime));
	mydate[strlen(mydate) - 1] = '\0';
	fprintf(stderr, "\n\n\nThis code is supplied under the LTX-Credence Shareware License.\n");
	fprintf(stderr, "Please see the LSLV1.2 file in the document directory for a full text.\n\n\n");
	if (!G_QUIET) {
		fprintf(stderr, "\n%s: %s\n", G_progstr, G_compilestr);
		fprintf(stderr, "%s by Anthony Sully\n", G_datestr);
		fprintf(stderr, "options are: -s => silent(script)\n");
		fprintf(stderr, "f => pattern file\n");
		fprintf(stderr, "g => gct info file\n");
		fprintf(stderr, "z => run gzip on .evo\n");
		fprintf(stderr, "a => use autogen cpm\n");
		fprintf(stderr, "\nUsage:%s -fz PAT.file \n", argv[0]);
	}

	if (NULL == (fperrors = fopen(TRANSLATION_ERRORS, "a"))) {
		fprintf(stderr, "\nCould not open %s for output[%s,%d,%s]\n",
				TRANSLATION_ERRORS, __FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}

	if (NULL == (fpstatus = fopen(TRANSLATION_STATUS, "a"))) {
		fprintf(stderr, "\nCould not open %s for output[%s,%d,%s]\n",
				TRANSLATION_STATUS, __FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}

	sighdrfileexists = 0;
	if (NULL != (fpsignalheaders = fopen(SCAN_HDR_FILE, "r"))) {
		fclose(fpsignalheaders);
		sighdrfileexists = 1;
	}
	if (NULL == (fpsignalheaders = fopen(SCAN_HDR_FILE, "a"))) {
		fprintf(stderr, "\nCould not open %s for output[%s,%d,%s]\n", SCAN_HDR_FILE, __FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}
	if (sighdrfileexists == 0) {
		fprintf(fpsignalheaders, "enVision:\"bl8:R10.3.2.WW0104:S3.0\"; /* 5.7 */\n\n");
	}

	/* open pattern input file */
	if (filein1) strcpy(G_infile1, (char *) argv[2]);
	else {
		fprintf(stderr, "Pattern not provided, exiting[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}

	strcpy(infilebuf, G_infile1);
	t1 = 0;
	while (NULL != (ptr = strchr(G_infile1, '/'))) {
		t1 = (ptr - G_infile1);
		G_infile1[t1] = ' ';
		t1++;
	}
	j = 0;
	while (NULL == strchr(". ", G_infile1[t1]) && t1 < strlen(G_infile1)) pattern[j++] = G_infile1[t1++];
	pattern[j] = '\0';
	strcpy(G_infile1, infilebuf);	/* recopy the fullname and path */
	t1 = strlen(G_infile1);
	fprintf(stderr, "\npattern_name:%s[%s,%d,%s]\n", pattern, __FILE__, __LINE__, __FUNCTION__);
	if ((G_infile1[t1 - 3] == '.' && G_infile1[t1 - 2] == 'g' && G_infile1[t1 - 1] == 'z') || (G_infile1[t1 - 2] == '.' && G_infile1[t1 - 1] == 'Z')) {	/* compressed input file */
		if (NULL != (fpin1 = fopen(G_infile1, "r"))) {
			fclose(fpin1);
			sprintf(tempstr, "gunzip -c %s >%s", G_infile1, TEMPGZIPNAME);
			fprintf(stderr, "%s[%s,%d,%s]\n", tempstr, __FILE__, __LINE__, __FUNCTION__);
			system(tempstr);	/* unzip to temporary file */
			if (NULL == (fpin1 = fopen(TEMPGZIPNAME, "r"))) {
				fprintf(stderr, "\nFATAL_ERROR:Compressed input file [%s] not found[%s,%d,%s]\n",
						G_infile1, __FILE__, __LINE__, __FUNCTION__);
				fprintf(fperrors, "\nFATAL_ERROR:%s:Compressed input file [%s] not found\n",
						G_progstr, G_infile1);
				exit(1);
			}
			gunzip = 1;
		}
		else {
			fprintf(stderr, "\nFATAL_ERROR:Input file [%s] not found[%s,%d,%s]\n",
					G_infile1, __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "\nFATAL_ERROR:%s:Input file [%s] not found\n",
					G_progstr, G_infile1);
			exit(1);
		}
	}
	else {
		if (NULL == (fpin1 = fopen(G_infile1, "r"))) {
			fprintf(stderr, "\nFATAL_ERROR:Input file [%s] not found[%s,%d,%s]\n",
					G_infile1, __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "\nFATAL_ERROR:%s:Input file [%s] not found\n",
					G_progstr, G_infile1);
			exit(1);
		}
	}
	if (!G_QUIET) fprintf(stdout, "input file1 ok\n");

	infile2[0] = '\0';
	if (filein2) strcpy(infile2, (char *) argv[3]);
	else {
		fprintf(stderr, "No cycletabl.mod8 file given,exiting[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}

	parse_mod_file(infile2);

	if (1) {					/* pattern dpm output file */
		sprintf(outfile1, "%s_dpm.evo", pattern);
		if (NULL == (fpout1 = fopen(outfile1, "w"))) {
			fprintf(stderr, "\nFATAL_ERROR:Could not open output file [%s] for output[%s,%d,%s]\n",
					outfile1, __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "\nFATAL_ERROR:%s:Could not open output file [%s] for output\n",
					G_progstr, outfile1);
			exit(1);
		}
	}
	if (1) {					/* pattern cpm output file */
		sprintf(outfile2, "%s_cpm.evo", pattern);
		if (NULL == (fpout2 = fopen(outfile2, "w"))) {
			fprintf(stderr, "\nFATAL_ERROR:Could not open output file [%s] for output[%s,%d,%s]\n",
					outfile2, __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "\nFATAL_ERROR:%s:Could not open output file [%s] for output\n",
					G_progstr, outfile2);
			exit(1);
		}
	}

	if (!G_QUIET && filein1 == 0) {
		fprintf(stderr, "Inline syntax:\n%s -fz %s\n[%s,%d,%s]\n", argv[0],
				G_infile1, __FILE__, __LINE__, __FUNCTION__);
	}

	/* allocate buffers */
	Msetptr = (char *) malloc((unsigned) (VECTORLEN * MAXMSET));
	Dsetptr = (char *) malloc((unsigned) (VECTORLEN * MAXDSET));
	Isetptr = (char *) malloc((unsigned) (VECTORLEN * MAXISET));
	if (Msetptr == NULL)
		fprintf(stderr, "FATAL_ERROR:Could not allocate msetptr[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
	if (Msetptr == NULL)
		fprintf(fperrors, "FATAL_ERROR:%s:Could not allocate msetptr\n",
				G_progstr);
	if (Dsetptr == NULL)
		fprintf(stderr, "FATAL_ERROR:Could not allocate dsetptr[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
	if (Dsetptr == NULL)
		fprintf(fperrors, "FATAL_ERROR:%s:Could not allocate dsetptr\n",
				G_progstr);
	if (Isetptr == NULL)
		fprintf(stderr, "FATAL_ERROR:Could not allocate isetptr[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
	if (Isetptr == NULL)
		fprintf(fperrors, "FATAL_ERROR:%s:Could not allocate isetptr\n", G_progstr);

	if (Msetptr == NULL || Dsetptr == NULL || Isetptr == NULL)
		exit(6);
	if (!G_QUIET) fprintf(stdout, "Memory allocated ok\n");

	/* the following will initialize any unused mset to the default values */
	for (i = 0; i < MAXMSET; i++)
		for (j = 0; j < MAXPINS; j++) Msetptr[i * VECTORLEN + j] = Dsetptr[i * VECTORLEN + j] = 1;
	for (i = 0; i < MAXISET; i++)
		for (j = 0; j < MAXPINS; j++) Isetptr[i * VECTORLEN + j] = 0;

	fprintf(fpout1, "enVisionObject:\"bl8:R5.7\";\n\n");
	fprintf(fpout1, "Pattern %s {\n", pattern);
	fprintf(fpout1, "    Type Dpm;\n");

	/* Delay this so we can get the default background: */
	/* fprintf(fpout1,"    Default WaveformTable %s;\n","DEFWFT"); */
	/* fprintf(fpout1,"    Default SignalHeader %s;\n",G_NORMALSGHDR); */
	/* fprintf(fpout1,"\" Pattern convertor: %s:%s by Anthony Sully compile_date:%s@%s\"\n",G_compilestr,G_progstr,__DATE__,__TIME__); */
	/* fprintf(fpout1,"\"      Pattern converted on:%s by:%s on host:%s \"\n\"      in pwd:%s\"\n",mydate,G_username,G_hostname,G_pwd); */
	/* fprintf(fpout1,"$%s_dpm_st\n",pattern); */
	errorstr[0] = '\0';
	printstring[0] = '\0';
	comment[0] = '\0';
	beginflag = 0;
	lastitem = 0;
	errorflag = 0;
	repeatcount = 1;
	commentON = 0;
	repeatdec = 0;
	vmscan = 0;
	scanflag = 0;
	scanat = scanatr = -1;
	pscanhdr[0] = '\0';
	scanflaghold = 0;

   /***********************************************/
	/*                                             */
	/*    begin main loop for file processing      */
	/*                                             */
   /***********************************************/
	while (fgets(vector, READLINELEN - 1, fpin1) != NULL) {
//      fprintf(stdout,"%s",vector);
		G_readlinenum++;
		line++;
		scanhold = 0;
		if (strstr(vector, "//SHUTDOWN_B") != NULL) {
			/* search until we find the "//SHUTDOWN_E", the last "SHUTDOWN__" will be saved... */
		}						/* process shutdown vector */
		else if (strstr(vector, "begin") == NULL && repforeveropen == 1) {
			repforeverend[maxrepforever - 1] = -1;
			repforeveropen = 0;
		}						/* no begin block */
		else if (strstr(vector, "begin") != NULL && repforeveropen == 1) {	/* begin block repeat forever */
			repforeveropen = 2;
			repforeverlines = 0;
			continue;
		}
		else if (strstr(vector, "end") != NULL && repforeveropen == 2) {	/* end of repeat forever block */
			repforeveropen = 0;
			repforeverend[maxrepforever - 1] = VN;
		}
		else {					/* end else general vector stuff */
			strcpy(mod_vector, vector);
			if (debug) fprintf(stdout, "V[%s]\n", mod_vector);
			commentflag = 0;
			vl = strlen(mod_vector);

			/* simplify comments */
			for (i = 0; i < vl; i++) {
				if (mod_vector[i] == '(' && mod_vector[i + 1] == '*') {
					mod_vector[i] = '{';
					mod_vector[i + 1] = ' ';
				}
				else if (mod_vector[i] == '*' && mod_vector[i + 1] == ')') {
					mod_vector[i] = '}';
					mod_vector[i + 1] = ' ';
				}
			}

			if (vl == 0) continue;
//          if (NULL!=(ptr=strstr(mod_vector,"Shutdown"))) {
//             if ((ptr-mod_vector)<=7) {/* Shutdown SUBROUTINE */
//                if(debug*0+1)fprintf(fpstatus,"INSIDE Shutdown:%s [file:%s]\n",mod_vector,G_infile1);
//                fgets(vector,READLINELEN-1,fpin1);
//                G_readlinenum++;
//                if (NULL!=(ptr=strstr(vector,"begin"))) {
//                    if(debug*0+1)fprintf(fpstatus,"Throwing out Shutdown:%s [file:%s]\n",vector,G_infile1);
//                    while(fgets(vector,READLINELEN-1,fpin1) != NULL ){
//                       G_readlinenum++;
//                       if(debug*0+1)fprintf(fpstatus,"Throwing out Shutdown:%s [file %s]\n",vector,G_infile1);
//                       if (NULL!=(ptr=strstr(vector,"end"))) break;
//                       }
//                    }
//                }
//             }
			if (commentON && NULL == strchr(mod_vector, '}')) {
				strcat(comment, mod_vector);
				continue;
			}

//          else if (commentON) {
//             strcat(keep_vector,mod_vector);
//             strcpy(mod_vector,keep_vector);
//             vl=strlen(mod_vector);
//             ptr1=strchr(mod_vector,'}');
//             if (ptr1==NULL) ptr1=mod_vector+strlen(mod_vector);
//             /* seek until comment end*/
//             for (i=(int)(ptr1-mod_vector);i<vl;i++) {
//                if (mod_vector[i]=='{' ) commentcount++;
//                if (mod_vector[i]=='}' ) commentcount--;
//                if (commentcount==0) break;
//                }
//             if (commentcount==0) {
//                commentflag=1;
//                mod_vector[i]='\0';
//                mod_vector[j]=' ';
//                commentON=0;
//                if (strlen(ptr1)+strlen(comment)>MULTILINESIZE) {
//                   fprintf(fpstatus,"BIG COMMENT <%s> [file:%s]\n",comment,G_infile1);
//                   comment[0]='\0';
//                   }
//                strcat(comment,ptr1);
//                for (j=j;j<=i;j++) mod_vector[j]=' ';
//                if (NULL!=(ptr1=strchr(mod_vector,'{'))) continue;
//                }
//             else {
//                commentON=1;
//                mod_vector[j]=' ';
//                strcat(comment,ptr1);
//                continue;
//                }
//             } /* no comment pending */

//          while (NULL!=(ptr1=strchr(mod_vector,'{')) && commentON==0 ) { /* begin comment */
//             j=(int)(ptr1-mod_vector);
//             /* seek until comment end*/
//             for (i=(int)(ptr1-mod_vector);i<vl;i++) {
//                if (mod_vector[i]=='{' ) commentcount++;
//                if (mod_vector[i]=='}' ) commentcount--;
//                if (commentcount==0) break;
//                }
//             if (commentcount==0) {
//                commentflag=1;
//                mod_vector[i]='\0';
//                mod_vector[j]=' ';
//                if (strlen(ptr1)+strlen(comment)>MULTILINESIZE) {
//                   fprintf(fpstatus,"BIG COMMENT <%s> [file:%s]\n",comment,G_infile1);
//                   comment[0]='\0';
//                   }
//                strcat(comment,ptr1);
//                for (j=j;j<=i;j++) mod_vector[j]=' ';
//                if (NULL!=(ptr1=strchr(mod_vector,'{'))) continue;
//                }
//             else {
//                commentON=1;
//                mod_vector[j]=' ';
//                if (strlen(ptr1)+strlen(comment)>MULTILINESIZE) {
//                   fprintf(fpstatus,"BIG COMMENT <%s> [file:%s]\n",comment,G_infile1);
//                   comment[0]='\0';
//                   }
//                strcat(comment,ptr1);
//                continue;
//                }
//             } /* end comment */
			if (commentON) {	/* need more lines */
				strcpy(keep_vector, mod_vector);
				continue;
			}
			if (debug) fprintf(stdout, "comment=<%s>", comment);
			if (beginflag == 0 && NULL != (ptr = strstr(mod_vector, "begin"))) {
				beginflag = 1;
				if (debug) fprintf(stdout, "found begin\n");
				continue;
			}
			if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, "end"))) {
				if (debug) fprintf(stdout, "found end\n");
				if (scanflag == 1) scanflag = 2;	/* if inside scanvector and end is found then we are complete */
				else continue;
			}
			if (NULL != (ptr = strstr(mod_vector, "ChainLength"))) {
				tptr = strchr(mod_vector, '(');
				if (tptr == NULL) continue;
				/* scanlength[0] is the max, scanlength[1] is first */
				scanlength[0] = scanlength[1] = (int) strtol(tptr + 1, &ptr, 10);
				for (scanpin = 2; scanpin < MAXSCANNUM; scanpin++) scanlength[scanpin] = -1;
				scanpin = 2;
				while (*ptr == ',') {
					tptr = ptr + 1;
					scanlength[scanpin] = (int) strtol(tptr + 1, &ptr, 10);
					if (scanlength[scanpin] > scanlength[0]) scanlength[0] = scanlength[scanpin];	/* get max */
					scanpin++;
					if (scanpin > MAXSCANNUM) break;
				}
				for (found = -1, nomatch = i = 0; i < maxscantbl; i++) {
					for (j = 1; j < MAXSCANNUM; j++) {
						if (scanhdrtbl[i][j] != scanlength[j]) nomatch = 1;
					}
					if (nomatch == 0) found = i;
				}
				if (found == -1) {
					/* SignalHeader SCANVMVM_105 {
					   Signals {
					   TDI { Scan, ScanLength = 105, Fill = L, PostFill; }
					   TDO { Scan, ScanLength = 105, Fill = X, PostFill; }
					   }
					   } */
					sprintf(scanhdr, "SCANHDR_%d_%d_%05d", shindex[0], shindex[1], scanlength[0]);
					fprintf(fpsignalheaders, "SignalHeader %s {Signals {", scanhdr);
					for (scanpin = 0; scanpin < G_scandata[shindex[0]].scanpins; scanpin++) {
						fprintf(fpsignalheaders, " %s { Scan, ScanLength = %05d, Fill = L, PostFill; }", G_scandata[shindex[SCANINWHICH]].scanpinname[scanpin], scanlength[0]);	/* use the max for now */
					}
					for (scanpin = 0; scanpin < G_scandata[shindex[1]].scanpins; scanpin++) {
						fprintf(fpsignalheaders, " %s { Scan, ScanLength = %05d, Fill = X, PostFill; }", G_scandata[shindex[1 - SCANINWHICH]].scanpinname[scanpin], scanlength[0]);	/* use the max for now */
					}
					fprintf(fpsignalheaders, "}} //see [%s] for pat to header mapping\n", TRANSLATION_STATUS);
					fprintf(fpstatus,"SCANHDR_%d_%d_%05d[%s]\n", shindex[0], shindex[1], scanlength[0],G_infile1);
					for (scanpin = 0; scanpin < MAXSCANNUM; scanpin++) {
						scanhdrtbl[found][scanpin] = scanlength[scanpin];
					}
					maxscantbl++;
					if (maxscantbl > MAXSCANTBLLEN) {
						fprintf(stderr, "Too many scan lengths in pattern[%s][%s,%d,%s]\n",
								G_infile1, __FILE__, __LINE__, __FUNCTION__);
						exit(1);
					}
				}

				fprintf(fpstatus, "Scan chain length=%d [file:%s]\n", scanlength[0], G_infile1);
				continue;
			}

			if (NULL != (ptr = strstr(mod_vector, "ScanTest"))) {
				/* FIXME APS: actually the thing inside is a tagname, maybe we should make it a label? */
				strcpy(scanlbl, ptr + strlen("ScanTest") + 1);
				ptr = strchr(scanlbl,')');
				if (ptr != NULL) *ptr = '\0';
				ptr = strchr(scanlbl,' ');
				if (ptr != NULL) *ptr = '\0';
				/* FIXME APS: need to record how long the chain is for CPM SDP repeat */
				/*            and how many parallel repeats since the last one */
				scanfor = scanat = 0;
				scanatr = (VN - 1);
				scanafor[scancnt] = scanlength[0];	/* scanlength[0] is the max of all */
				scanatreal[scancnt] = scanatr;
				strcpy(SCANRGCT[scancnt], LASTGCT);
				scancnt++;
				continue;
			}

			SSC = SSUC = 0;
			if (NULL != (ptr = strstr(mod_vector, "ScanSetCoupled"))) {
				SSC = 1;
				for (i = 0; i < (sizeof("ScanSetCoupled") - 1); i++) mod_vector[i] = ' ';
			}
			if (NULL != (ptr = strstr(mod_vector, "ScanSetUnCoupled"))) {
				SSUC = 1;
				for (i = 0; i < (sizeof("ScanSetUnCoupled") - 1); i++) mod_vector[i] = ' ';
			}
			if (SSC == 1 || SSUC == 1) {
				/* This should be at the top of the file */
				/* It specifies the two scanhdrs, the gctname, and the hold vector(s) */
				/* FIXME APS: uncoupled will source with two vectors, input first then output */
				sl1 = strlen(mod_vector);
				for (pc = i = 0; i < sl1; i++) {	/* count the open parentheses */
					if (mod_vector[i] == '(') pc++;
					if (mod_vector[i] == ')') pc--;
				}
				if (pc > 0) {	/* if it matches then we are good, else get more lines */
					bc = SSCdone = 0;
					while (!SSCdone) {
						fgets(buf_ssc, READLINELEN - 1, fpin1);	/* FIXME APS: assume only one extra read to complete */
						sl2 = strlen(buf_ssc);
//                  fprintf(stdout,"SSCR1[%s]\n",buf_ssc);
						for (i = 0; i < sl2; i++) {
							if (buf_ssc[i] == '{') bc++;	/* these are designed to find some of the comments */
							if (buf_ssc[i] == '}') {
								buf_ssc[i] = ' ';
								bc--;
							}
							/* FIXME APS: we should look for the (* *) too, but we won't */
							if (buf_ssc[i] == '(') pc++;
							if (buf_ssc[i] == ')') pc--;
							if (bc > 0) buf_ssc[i] = ' ';	/* blank out if we are in comment */
						}
//                  fprintf(stdout,"SSCR2[%s]\n",buf_ssc);
						if (pc == 0 && bc == 0) SSCdone = 1;
						if ((sl1 + sl2) > READLINELEN) {
							fprintf(stderr,"Line too long to wrap[%s], exiting[%s,%d,%s]\n",
									buf_ssc, __FILE__, __LINE__, __FUNCTION__);
							exit(1);
						}
						strcat(mod_vector, buf_ssc);
						sl1 += sl2;
					}
				}
				strcpy(scansetstr, mod_vector);
				if (debug) fprintf(stdout, "scansetname=[%s]\n", scansetstr);
				for (j = 0; j < 2; j++) {
					shindex[j] = shlen[j] = -1;
					for (i = 0; i < G_scanhdrs; i++) {
						ptr = strstr(mod_vector, G_scandata[i].scanhdr);
						if (ptr != NULL && shlen[j] < G_scandata[i].shlen) {
							ptrk = ptr;
							shindex[j] = i;
							shlen[j] = G_scandata[i].shlen;
							shpos[j] = ptrk - mod_vector;
						}
					}
					if (shindex[j] == -1) {
						fprintf(stderr,"Scan header%d not found[%s], exiting[%s,%d,%s]\n",
								j, scansetstr, __FILE__, __LINE__, __FUNCTION__);
						exit(1);
					}
					fprintf(fpstatus, "scan%d=[%s] [file:%s]\n", j, G_scandata[shindex[j]].scanhdr, G_infile1);
					for (i = 0; i < shlen[j]; i++)
						*(ptrk++) = ' ';	/* blank it out after we've identified it */
				}				/* j loop */
				if (shpos[0] > shpos[1]) {	/* reverse them */
					fprintf(fpstatus, "Swapping scan0 with scan1 for proper ordering\n");
					i = shindex[0];
					shindex[0] = shindex[1];
					shindex[1] = i;
				}
				/* need to convert scansetstr to scangct,G_SCANHOLD */
				ptr = strchr(mod_vector, '[');
				if (ptr == NULL) {
					fprintf(stderr, "Bad scanset(un)coupled[%s][%s,%d,%s]\n",
							mod_vector, __FILE__, __LINE__, __FUNCTION__);
					exit(1);
				}
				*ptr = ' ';
				i = 0;
				ptr++;
				while (ptr <= mod_vector + sl1) {
					if (*ptr == ']') {
						G_SCANHOLD[i] = '\0';
						fprintf(stderr,"FOUND SCAN END[%s]\n",mod_vector);
						*ptr = ' ';
						break;
					}
					G_SCANHOLD[i] = *ptr;
					*ptr = ' ';
					ptr++;
					i++;
				}
				/* FIXME APS: need to get second vector if ScanSetUnCoupled */
				for (j = i = 0; i < sl1; i++) {
					if (mod_vector[i] != ' ' && mod_vector[i] != '\t' &&
						mod_vector[i] != '(' && mod_vector[i] != ')' &&
						mod_vector[i] != ';' && mod_vector[i] != '\n')
						scangct[j++] = mod_vector[i];
				}
				scangct[j] = '\0';
				for (i = 0; i < G_maxgctSET; i++) {
					if (strcmp(G_GCTMODNAME[i], scangct) == 0) break;
				}
				if (i == G_maxgctSET) {
					fprintf(stderr, "Couldn't find ScanGCT[%s][%s,%d,%s]\n", scangct, __FILE__, __LINE__, __FUNCTION__);
					exit(1);
				}
				G_GCTMODUSED[i] = REFISSCAN;
				sl1 = strlen(G_SCANHOLD);
				for (j = 0; j < sl1; j++) {
					if (G_VECTD0[i][j] != G_VECTD1[i][j]) {
						fprintf(stderr, "Inconsistent DSET0/1 format: [%c] & [%c] in[%s] pin[%d] [%s,%d,%s]\n",
								(int) G_VECTD0[i][j], (int) G_VECTD1[i][j],
								scangct, j, __FILE__, __LINE__, __FUNCTION__);
					}
					/* FIXME APS: we're going to only pick D0 for now, should be mostly the same */
					/* picking DSET=0, MSET=0 (mask) */
					G_SCANHOLD[j] = alias_vcpvcs(G_SCANHOLD[j], 0, 0, G_VECTD0[i][j], G_VECTD1[i][j],FC_BAD);/* priorstate for now, unknown */
				}

				if (strstr(G_scandata[shindex[0]].scanhdr, "ScanOut") != NULL) SCANINWHICH = 1;
				for (j = 0; j < G_scandata[shindex[0]].scanpins; j++)
					G_SCANHOLD[G_scandata[shindex[0]].index[j]] = (SCANINWHICH == 1) ? AM_scanout : AM_scanin;
				for (j = 0; j < G_scandata[shindex[1]].scanpins; j++)
					G_SCANHOLD[G_scandata[shindex[1]].index[j]] = (SCANINWHICH == 1) ? AM_scanin : AM_scanout;
				fprintf(fpout1, "   Default WaveformTable %s;\n", scangct);
				fprintf(fpout1, "   Default SignalHeader %s;\n", G_NORMALSGHDR);
				fprintf(fpout1, "   Default Background *%s*;\n", G_SCANHOLD);
				fprintf(fpout1, "//autogen_vcs %lld %d\n", CKS_autogen8_vcs_c, FS_autogen8_vcs_c);
				fprintf(fpout1, "//alias_vcpvcs %lld %d\n", CKS_alias_vcpvcs_c, FS_alias_vcpvcs_c);
				fprintf(fpout1, "//aliasmap %lld %d\n", CKS_aliasmap_h, FS_aliasmap_h);
				fprintf(fpout1, "//global %lld %d\n", CKS_global_vcs_c, FS_global_vcs_c);
				fprintf(fpout1, "//include %lld %d\n", CKS_include_vcs_h, FS_include_vcs_h);
				fprintf(fpout1, "//common_includes %lld %d\n", CKS_common_includes_h, FS_common_includes_h);
				fprintf(fpout1, "//outputvector %lld %d\n", CKS_outputvector_vcs_c, FS_outputvector_vcs_c);
				fprintf(fpout1, "//parse_mod %lld %d\n", CKS_parse_mod_vcs_c, FS_parse_mod_vcs_c);
				chksumout(fpout1, "\"", "\"");
				fprintf(fpout1, "\" Pattern convertor: %s:%s by Anthony Sully compile_date:%s@%s\"\n",
						G_compilestr, G_progstr, __DATE__, __TIME__);
				oktoprintcomment = 1;
				fprintf(fpout1, "\"      Pattern converted on:%s by:%s on host:%s \"\n\"      in pwd:%s\"\n",
						mydate, G_username, G_hostname, G_pwd);
				fprintf(fpout1, "$%s_dpm_st\n", pattern);
				continue;
			}					/* end scansetcoupled || scansetuncoupled */
			if (NULL != (ptr = strstr(mod_vector, "ScanIn"))) {
				ptrSC = strchr(mod_vector,'('); /* there are double parenthesis around the vector */
				if (ptrSC == NULL ) continue;
				scanflag += 1;
				for (scanpin = 0; scanpin < G_scandata[shindex[SCANINWHICH]].scanpins; scanpin++) {
//					fprintf(stdout,"SCANIN[%s]%d\n", ptrSC, strlen(ptrSC));
					if (NULL != (ptr = strchr(ptrSC, '('))) {	/* there are parenthesis around the sub-vector */
						t1 = ptr - ptrSC + 1;
						scaninalias[0] = AM_driveLOD1;
						scaninalias[1] = AM_driveHID1;
						tptr = strchr(ptrSC, ')');
						if (tptr == NULL) {
							linecnt = 1;
							while (fgets(vector, READLINELEN - 1, fpin1) != NULL) {
								fprintf(stderr, "Getting Multiline scanin[%ld]!\n", linecnt++);
// 							vector[strlen(vector)-1]='\0';/* remove carriage return */
								fprintf(stdout, "V[%s]%d\n", vector, strlen(vector));
								if (strchr(vector, ')') != NULL) {
									if (strlen(ptrSC) + strlen(vector) > scanlength[0] + sizeof("ScanIn ( () ) ; ")) {
										fprintf(stderr, "MULTILINE SCANIN TOO LONG FOR[%s]chainlen=%d\n",
												pattern, scanlength[0]);
										fprintf(fperrors, "MULTILINE SCANIN TOO LONG FOR[%s]chainlen=%d\n",
												pattern, scanlength[0]);
										exit(1);
									}
									strcat(ptrSC, vector);
									tptr = strchr(ptrSC, ')');
									break;
								}
								else strcat(ptrSC, vector);
							}
						}
						t2 = tptr - ptrSC;
						j = 0;
						for (i = t1; i < t2; i++) {
							if      (ptrSC[i] == '0') scanin[scanpin][j++] = scaninalias[ptrSC[i] - '0'];
							else if (ptrSC[i] == '1') scanin[scanpin][j++] = scaninalias[ptrSC[i] - '0'];
							else ;
							}
						scanin[scanpin][j] = '\0';
						if (debug) fprintf(stdout, "Scan IN vector=%s\n", scanin[scanpin]);
					}
					else scanin[scanpin][0] = '\0';	/* No scanin */
					ptrSC = strchr(ptrSC,',');
					if (ptrSC == NULL) break;
					ptrSC++; /* move past ',' if there are more than one sub-vectors */
				}	/* end scan in sub-vector */
			}	/* end of ScanIn */
			if (NULL != (ptr = strstr(mod_vector, "ScanOut"))) {
				ptrSC = strchr(mod_vector,'('); /* there are double parenthesis around the vector */
				if (ptrSC == NULL ) continue;
				scanflag += 1;
				for (scanpin = 0; scanpin < G_scandata[shindex[1-SCANINWHICH]].scanpins; scanpin++) {
//					fprintf(stdout,"SCANOUT[%s]%d\n", ptrSC, strlen(ptrSC));
					if (NULL != (ptr = strchr(ptrSC, '('))) {	/* there are parenthesis around the sub-vector */
						t1 = ptr - ptrSC;
						scaninalias[0] = AM_edgestbLOD0;
						scaninalias[1] = AM_edgestbHID0;
						scaninalias[2] = AM_maskD0;
						tptr = strchr(ptrSC, ')');
						if (tptr == NULL) {
							linecnt = 1;
							while (fgets(vector, READLINELEN - 1, fpin1) != NULL) {
								fprintf(stderr, "Getting Multiline scanout[%ld]!\n", linecnt++);
//                     vector[strlen(vector)-1]='\0';/* remove carriage return */
								fprintf(stdout, "V[%s]%d\n", vector, strlen(vector));
								if (NULL != strchr(vector, ')')) {
									if (strlen(ptrSC) + strlen(vector) > scanlength[1] + sizeof("ScanOut ( () ) ; ")) {
										fprintf(stderr, "MULTILINE SCANOUT TOO LONG FOR[%s]chainlen=%d\n", pattern, scanlength[1]);
										fprintf(fperrors, "MULTILINE SCANOUT TOO LONG FOR[%s]chainlen=%d\n", pattern, scanlength[1]);
										exit(1);
									}
									strcat(ptrSC, vector);
									tptr = strchr(ptrSC, ')');
									break;
								}
								else strcat(ptrSC, vector);
							}
						}
						t2 = tptr - ptrSC;
						j = 0;
						for (i = t1; i < t2; i++) {
							if      (ptrSC[i] == 'X') scanout[scanpin][j++] = scaninalias[2];
							else if (ptrSC[i] == '0') scanout[scanpin][j++] = scaninalias[ptrSC[i] - '0'];
							else if (ptrSC[i] == '1') scanout[scanpin][j++] = scaninalias[ptrSC[i] - '0'];
							else ;
						}
						scanout[scanpin][j] = '\0';
						if (debug) fprintf(stdout, "Scan OUT vector=%s\n", scanout[scanpin]);
					}
					else scanout[scanpin][0] = '\0';	/* no scanout */
					ptrSC = strchr(ptrSC,',');
					ptrSC++; /* move past ',' if there are more than one sub-vectors */
				}	/* end scan out vector */
			}	/* end of ScanOut */
			if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, "repeat forever"))) {
				/* we need to check here for begin block and log it also */
				repforever[maxrepforever] = VN;
				repforeveropen = 1;
				maxrepforever++;
				if (maxrepforever == MAXREPFOREVER) {
					fprintf(stderr, "BAD_ERROR:found too many repeat forevers...ignoring[%s,%d,%s]\n",
							__FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "BAD_ERROR:%s:found too many repeat forevers...ignoring.in file[%s]line%ld\n",
							G_progstr, G_infile1, G_readlinenum);
					notgood = 2;
				}
				continue;
			}
			if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, "repeat"))) {
				repeatdec = 0;
				ptr += 7;
				while (isdigit((int) *ptr)) {
					repeatdec = repeatdec * 10 + (*ptr - '0');
					ptr++;
				}
				fprintf(fpstatus, "found repeat [%ld] [file:%s]\n", repeatdec, G_infile1);
			}					/* end repeat */
			if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, "MSet"))) {
				t1 = 0;
				ptr = strchr(mod_vector, '[');
				if (ptr == NULL) {
					fprintf(stderr, "BAD_ERROR:MSET ERROR [%s][%s,%d,%s]\n",
							mod_vector, __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "BAD_ERROR:MSET ERROR:%s [%s].in file[%s]line%ld",
							G_progstr, mod_vector, G_infile1, G_readlinenum);
					notgood = 1;
					break;
				}
				else {
					*ptr = '%';
					ptr++;
					while (*ptr != ']') {
						if (isdigit((int) *ptr)) t1 = 10 * t1 + (*ptr - '0');
						ptr++;
					}
					if (t1 > MAXMSET) {
						fprintf(stderr, "BAD_ERROR:Exceeded MAXMSET\n...continuing[%s,%d,%s]\n",
								__FILE__, __LINE__, __FUNCTION__);
						fprintf(fperrors, "BAD_ERROR:%s:Exceeded MAXMSET\n...continuing.in file[%s]line%ld\n",
								G_progstr, G_infile1, G_readlinenum);
						notgood = 1;
						break;
					}
					if (debug) fprintf(stdout, "In MSet [%d]\n", t1);
					ptr = strchr(mod_vector, '[');
					if (ptr == NULL) {
						fprintf(stderr, "BAD_ERROR:MSET ERROR [%s][%s,%d,%s]\n",
								mod_vector, __FILE__, __LINE__, __FUNCTION__);
						fprintf(fperrors, "BAD_ERROR:MSET ERROR:%s [%s].in file[%s]line%ld",
								G_progstr, mod_vector, G_infile1, G_readlinenum);
						notgood = 1;
						break;
					}
					ptr++;
					t2 = 0;
					while (*ptr != ']') {
						Msetptr[t1 * VECTORLEN + t2] = *ptr - '0';
						ptr++;
						t2++;
					}
					continue;
				}
			}					/* end MSET */
			if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, "DSet"))) {
				t1 = 0;
				ptr = strchr(mod_vector, '[');
				if (ptr == NULL) {
					fprintf(stderr, "BAD_ERROR:DSET ERROR [%s][%s,%d,%s]\n",
							mod_vector, __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "BAD_ERROR:DSET ERROR:%s [%s].in file[%s]line%ld",
							G_progstr, mod_vector, G_infile1, G_readlinenum);
					notgood = 1;
					break;
				}
				else {
					*ptr = '%';
					ptr++;
					while (*ptr != ']') {
						if (isdigit((int) *ptr)) t1 = 10 * t1 + (*ptr - '0');
						ptr++;
					}
					if (t1 > MAXDSET) {
						fprintf(stderr, "BAD_ERROR:Exceeded MAXDSET\n...continuing[%s,%d,%s]\n",
								__FILE__, __LINE__, __FUNCTION__);
						fprintf(fperrors, "BAD_ERROR:%s:Exceeded MAXDSET\n...continuing.in file[%s]line%ld\n",
								G_progstr, G_infile1, G_readlinenum);
						notgood = 1;
						break;
					}
					if (debug)
						fprintf(stdout, "In DSet [%d]\n", t1);
					ptr = strchr(mod_vector, '[');
					if (ptr == NULL) {
						fprintf(stderr, "BAD_ERROR:DSET ERROR [%s][%s,%d,%s]\n",
								mod_vector, __FILE__, __LINE__, __FUNCTION__);
						fprintf(fperrors, "BAD_ERROR:DSET ERROR:%s [%s].in file[%s]line%ld",
								G_progstr, mod_vector, G_infile1, G_readlinenum);
						notgood = 1;
						break;
					}
					ptr++;
					t2 = 0;
					while (*ptr != ']') {
						Dsetptr[t1 * VECTORLEN + t2] = *ptr - '0';
						ptr++;
						t2++;
					}
					continue;
				}
			}					/* end DSET */
			if (beginflag >= 1
				&& NULL != (ptr = strstr(mod_vector, "ISet"))) {
				t1 = 0;
				ptr = strchr(mod_vector, '[');
				if (ptr == NULL) {
					fprintf(stderr, "BAD_ERROR:ISET ERROR [%s][%s,%d,%s]\n",
							mod_vector, __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "BAD_ERROR:ISET ERROR:%s [%s].in file[%s]line%ld",
							G_progstr, mod_vector, G_infile1, G_readlinenum);
					notgood = 1;
					break;
				}
				else {
					*ptr = '%';
					ptr++;
					while (*ptr != ']') {
						if (isdigit((int) *ptr)) t1 = 10 * t1 + (*ptr - '0');
						ptr++;
					}
					if (t1 > MAXISET) {
						fprintf(stderr, "BAD_ERROR:Exceeded MAXISET\n...exiting[%s,%d,%s]\n",
								__FILE__, __LINE__, __FUNCTION__);
						fprintf(fperrors, "BAD_ERROR:%s:Exceeded MAXISET\n...exiting.in file[%s]line%ld\n",
								G_progstr, G_infile1, G_readlinenum);
						notgood = 1;
						break;
					}
					if (debug) fprintf(stdout, "In ISet [%d]\n", t1);
					ptr = strchr(mod_vector, '[');
					if (ptr == NULL) {
						fprintf(stderr, "BAD_ERROR:ISET ERROR [%s][%s,%d,%s]\n",
								mod_vector, __FILE__, __LINE__, __FUNCTION__);
						fprintf(fperrors, "BAD_ERROR:ISET ERROR:%s [%s].in file[%s]line%ld",
								G_progstr, mod_vector, G_infile1, G_readlinenum);
						notgood = 1;
						break;
					}
					ptr++;
					t2 = 0;
					while (*ptr != ']') {
						Isetptr[t1 * VECTORLEN + t2] = *ptr - '0';
						ptr++;
						t2++;
					}
					continue;
				}
			}					/* end ISET */
			if (scanhold == 1) {
				strcpy(mod_vector, G_SCANHOLD);
				t4 = 0;
				t5 = strlen(G_SCANHOLD);
				if (debug) fprintf(stdout, "In SCANHOLD[%s]\nb=%d,e=%d,l=%d\n", G_SCANHOLD, t4, t5, t5 - t4);
				outpos = 0;
				pinnum = 0;
				verrorflag = 0;
				scanhold = 0;
				if (0 == strcmp(scanoutSEL, FIND_SIGHDR_OUT)) {
					G_SCANHOLD[G_SCANOUTPIN - 1] = AM_scanout;
					fprintf(fpstatus, "scanout=%d [file:%s]\n", G_SCANOUTPIN, G_infile1);
				}
				G_SCANHOLD[G_SCANINPIN - 1] = AM_scanin;
				G_SCANHOLD[G_SCANOUTPIN - 1] = AM_scanout;
				if (debug) fprintf(stdout, "SCANHOLDVECTOR={%s}\n", G_SCANHOLD);
			}					/* end grab scan hold vector */
			vectorflag = 0;
			foundgoodgct = 0;
			for (i = 0; i < G_maxgctSET; i++)
				if (NULL != (ptr = strstr(mod_vector, G_GCTMODNAME[i]))) {
					foundgoodgct = 1;
					G_GCTMODUSED[i] = REFISVECT;
					break;
				}
			if ((commentON == 0 && beginflag >= 1 && foundgoodgct == 1)) {
				/* real vector */
				vectorflag = 1;
				j = 0;
				beginflag = 2;
				while (0 == isspace((int) *ptr) && *ptr != '(') WFT[j++] = *(ptr++);
				WFT[j] = '\0';
				strcpy(LASTGCT, WFT);
				gctmatchmod = 0;
				for (wftfind = 0; wftfind < G_maxgctSET; wftfind++) {
					if (debug) fprintf(stdout, "%d,GCTMODNAME=%s,WFT=%s\n", wftfind, G_GCTMODNAME[wftfind], WFT);
					if (NULL != strstr(G_GCTMODNAME[wftfind], WFT) && strlen(G_GCTMODNAME[wftfind]) == strlen(WFT)) {
						gctmatchmod = 1;
						G_GCTMODUSED[wftfind] = REFISVECT;
						break;
					}
				}
				if (i == G_maxgctSET) {	/* WFT NOT FOUND, at the moment assume this doesn't happen */
					fprintf(stderr, "BAD_ERROR:Error WFT not found[%s][%s,%d,%s]\n",
							WFT, __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "BAD_ERROR:%s:Error WFT not found[%s].in file[%s]line%ld\n",
							G_progstr, WFT, G_infile1, G_readlinenum);
				}
				VN++;
				G_cyclecount++;
				G_vectorcount++;
				ptr = strchr(mod_vector, '(');
				if (ptr == NULL) continue;
				ptr++;
				msel = 0;
				dsel = 0;
				isel = 0;
				/* MSET */
				while (*ptr != ',') {
					if (isdigit((int) *ptr)) msel = 10 * msel + (*ptr - '0');
					ptr++;
				}
				/* DSET */
				ptr++;
				while (*ptr != ',') {
					if (isdigit((int) *ptr)) dsel = 10 * dsel + (*ptr - '0');
					ptr++;
				}
				/* ISET */
				ptr++;
				while (*ptr != ')') {
					if (isdigit((int) *ptr)) isel = 10 * isel + (*ptr - '0');
					ptr++;
				}
				ptr = strchr(mod_vector, '[');
				if (ptr == NULL) continue;
				t4 = (ptr - mod_vector) + 1;
				ptr = strchr(mod_vector, ']');
				if (ptr == NULL) continue;
				t5 = (ptr - mod_vector);
				if (debug) fprintf(stdout, "In vector,WFT=[%s],M=%d,D=%d,I=%d,b=%d,e=%d,l=%d\n",
							WFT, t1, t2, t3, t4, t5, t5 - t4);
				outpos = 0;
				pinnum = 0;
				verrorflag = 0;
				sprintf(dmi, "(%d,%d,%d)", msel, dsel, isel);
				if ((t5 - t4) != G_MOD2_SIZE) {
					fprintf(stderr, "FATAL_ERROR: Number of pins<%d> in pattern <%s> does not match pins in cycletbl definition file<%d>\n[%s,%d,%s]\n",
							t5 - t4, G_infile1, G_MOD2_SIZE, __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "FATAL_ERROR:%s: Number of pins<%d> in pattern <%s> does not match pins in cycletbl definition file<%d>\n[%s]\n",
							G_progstr, t5 - t4, G_infile1, G_MOD2_SIZE,mod_vector);
					exit(9);
				}
				/* added 06/11/2009, used specifically in subroutines to get the prior mset/dset */
				if (msel == 0) {
					if (EMuMSET == 0) {
						EMuMSET = 1;
						fprintf(fpstatus, "pat[%s] uses mset[0]; using previous mset\n", pattern);
					}
					msel = lastmset;
				}
				else lastmset = msel;
				if (dsel == 0) {
					if (EMuDSET == 0) {
						EMuDSET = 1;
						fprintf(fpstatus, "pat[%s] uses dset[0]; using previous dset\n", pattern);
					}
					dsel = lastdset;
				}
				else lastdset = dsel;
				if (isel == 0) {
					if (EMuISET == 0) {
						EMuISET = 1;
						fprintf(fpstatus, "pat[%s] uses iset[0]; using previous iset\n", pattern);
					}
					isel = lastiset;
				}
				else lastiset = isel;
				for (pinnum = 0, i = t4; i < t5; i++, pinnum++) {
					vect = mod_vector[i] - '0';
					vmset = Msetptr[msel * VECTORLEN + pinnum];
					vdset = Dsetptr[dsel * VECTORLEN + pinnum];
					viset = Isetptr[isel * VECTORLEN + pinnum];
					if (viset == 1) vect = 1 - vect;
					dset0val = G_VECTD0[wftfind][pinnum];
					dset1val = G_VECTD1[wftfind][pinnum];
					AC = alias_vcpvcs(vect, vmset, vdset, dset0val, dset1val,FC_BAD);
					if (AC == AM_continue ) { /* this is high */
//						if (priorstate[pinnum] == FC_WINDOWOPEN || priorstate[pinnum] == FC_WINDOWOPENZ ) {
//							fprintf(fpstatus,"CONTINUE CHANGE1! AC[%c] => AM[%c] on pinnum[%d]\n", AC,AM_continueLO,pinnum);
//							AC = AM_continueLO;
//							}
//						else if (priorstate[pinnum] != FC_WINDOWOPEN && priorstate[pinnum] != FC_WINDOWOPENZ) {
						if (priorstate[pinnum] != FC_WINDOWOPEN && priorstate[pinnum] != FC_WINDOWOPENZ) {
							fprintf(fpstatus,"CONTINUE CHANGE2! AC[%c] => AM[%c] on pinnum[%d]\n", AC,AM_continueDRV,pinnum);
							AC = AM_continueDRV;
							}
						}
					else if (AC == AM_continueLO ) { /* this is low */
//						if (priorstate[pinnum] == FC_WINDOWOPEN || priorstate[pinnum] == FC_WINDOWOPENZ) {
//							fprintf(fpstatus,"CONTINUE CHANGE3! AC[%c] => AM[%c] on pinnum[%d]\n", AC,AM_continue,pinnum);
//							AC = AM_continue;
//							}
//						else if (priorstate[pinnum] != FC_WINDOWOPEN && priorstate[pinnum] != FC_WINDOWOPENZ) {
						if (priorstate[pinnum] != FC_WINDOWOPEN && priorstate[pinnum] != FC_WINDOWOPENZ) {
							fprintf(fpstatus,"CONTINUE CHANGE4! AC[%c] => AM[%c] on pinnum[%d]\n", AC,AM_continueDRV,pinnum);
							AC = AM_continueDRV;
							}
						}
					else priorstate[pinnum] = (vdset == 0) ?dset0val:dset1val; /* modify if not continue */
					out_vector1[pinnum] = AC;
					outpos++;
				}
				if (verrorflag == 1) {
					fprintf(stderr, "BAD_ERROR:Error in vector [%s][%s,%d,%s]\n", vector, __FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "BAD_ERROR:%s:Error in vector [%s].in file[%s]line%ld\n", G_progstr, vector, G_infile1, G_readlinenum);
				}
				out_vector1[outpos] = '\0';
				if (repforeveropen == 2) {
					strcpy(repforevervec[repforeverlines], out_vector1);
					fprintf(fpout1, "\"\n\"*%s* this is a repeat forever vector", out_vector1);
					out_vector1[0] = '\0';
					vectorflag = 0;
					repforeverlines++;
				}
			}

			if (debug) fprintf(stdout, "at%ld atr%ld vn%ld vectortrue%d\n",
						scanat, scanatr, VN - 1, vectorflag);
			if (beginflag == 2 && vectorflag) {
				t1 = 1;
				if (debug) fprintf(stdout, "FFFFF %s\n", out_vector1);
				repeatcount = repeatdec;
				outputvector(fpout1, &lastitem, out_vector1, pattern, WFT, dmi, VN, repeatcount, errorstr, comment);
				repeatcount = 1;
				repeatdec = 0;
			}
			if (scanflag == 2 ) {	/* SPIT OUT SCAN VECTOR both scanin and scanout if available  */
				scanatreal[scancnt++] = VN - 1;
				if (debug) fprintf(stdout, "Outputing scan vector\n");
				if (scancnt > MAXSCANCNT) {
					fprintf(stderr, "FATAL_ERROR:Maximum number of SCAN vectors exceeded...exiting[%s,%d,%s]\n",
							__FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "FATAL_ERROR:%s:Maximum number of SCAN vectors exceeded...exiting.in file[%s]line%ld\n",
							G_progstr, G_infile1, G_readlinenum);
					exit(9);
				}
				scanflag = 0;
				if (lastitem == STRING) fprintf(fpout1, "\"\n");
				if (scanlbl[0] != '\0') {fprintf(fpout1,"$%s%d\n", scanlbl, scancnt-1); scanlbl[0] = '\0';}
				t1 = (scanlength[0] + ENVISIONMAXSCANLEN - 1) / ENVISIONMAXSCANLEN - 1;
				vmscan += 1;
				G_cyclecount += scanlength[0];
				G_vectorcount++;
				fputc('*',fpout1);
				for (scanpin = 0; scanpin < G_scandata[shindex[SCANINWHICH]].scanpins; scanpin++) {
					i = 0;
					if (scanin[scanpin][0] != '\0') {
						for (i = 0; i < t1; i++) {
							t2 = scanin[scanpin][ENVISIONMAXSCANLEN + i * ENVISIONMAXSCANLEN];
							scanin[scanpin][ENVISIONMAXSCANLEN + i * ENVISIONMAXSCANLEN] = '\0';
							fprintf(fpout1, "%s\n", &scanin[scanpin][i * ENVISIONMAXSCANLEN]);
							scanin[scanpin][ENVISIONMAXSCANLEN + i * ENVISIONMAXSCANLEN] = t2;
						}
					}
					fprintf(fpout1, "%s;\n", &scanin[scanpin][i * ENVISIONMAXSCANLEN]);
				}
				for (scanpin = 0; scanpin < G_scandata[shindex[1-SCANINWHICH]].scanpins; scanpin++) {
					i = 0;
					if (scanout[scanpin][0] != '\0') {
						for (i = 0; i < t1; i++) {
							t2 = scanout[scanpin][ENVISIONMAXSCANLEN + i * ENVISIONMAXSCANLEN];
							scanout[scanpin][ENVISIONMAXSCANLEN + i * ENVISIONMAXSCANLEN] = '\0';
							fprintf(fpout1, "%s\n", &scanout[scanpin][i * ENVISIONMAXSCANLEN]);
							scanout[scanpin][ENVISIONMAXSCANLEN + i * ENVISIONMAXSCANLEN] = t2;
						}
					}
					fprintf(fpout1, "%s;* %s %s;\"SCAN VECTOR %d:LCC=%ld\"\n",
							&scanout[scanpin][i * ENVISIONMAXSCANLEN], scangct, scanhdr, scancnt-1, G_cyclecount);
				}
				lastitem = VECTOR;
			}
			if (beginflag == 1) {
				/* discard these comments */
				/* fprintf(fpout1,"\"%s\"\n",comment); */
				comment[0] = '\0';
				dmi[0] = '\0';
			}
			if (beginflag == 0 && oktoprintcomment == 1) {
				fprintf(fpout1, "\"%s\"\n", comment);
				comment[0] = '\0';
				dmi[0] = '\0';
			}
		}						/* end else general vector stuff */
	}							/* end of while vector */

	  /********************/
	/* End of main loop */
	  /********************/

	if (lastitem == STRING) fputc('\"', fpout1);
	lastitem = LABEL;
	fprintf(fpout1, "\n$end\n");
	if (prev_vector1[0] != '\0') {
		/* fprintf(stdout,"HHHHH\n"); */
		outputvector(fpout1, &lastitem, prev_vector1, pattern, prev_WFT,
					 prev_dmi, prev_VN, repeatcount, prev_errorstr, prev_comment);
		if (lastitem == STRING) fputc('\"', fpout1);
	}
	else {
		if (lastitem == STRING) fputc('\"', fpout1);
		fprintf(fpout1, "*%s* %s %s; \"DUMMY VECTOR, not executed\"\n", G_HOLD_VECTOR, SCANRGCT[0], G_NORMALSGHDR);
	}
	/* { bm */ fprintf(fpout1, "\n}\n");

/* ------------------------------------------------- */
	if (NULL == (fppatref = fopen(PAT_REF_FILE, "a"))) {
		fprintf(stderr, "\nCould not open %s for output[%s,%d,%s]\n",
				PAT_REF_FILE, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nCould not open %s for output[%s,%d,%s]\n",
				PAT_REF_FILE, __FILE__, __LINE__, __FUNCTION__);
	}
	else {
		fprintf(fppatref, "PATREF:[%-30s]:", pattern); // -30.30s
		for (i = 0; i < G_maxgctSET; i++) {
			if (G_GCTMODUSED[i] == REFISVECT) fprintf(fppatref, "|%-25s", G_GCTMODNAME[i]); // was -25.25s
			if (G_GCTMODUSED[i] == REFISSCAN) fprintf(fppatref, "^%-25s", G_GCTMODNAME[i]); // was -25.25s
		}
		fputc('\n', fppatref);
		fclose(fppatref);
	}

/* ------------------------------------------------- */
	fclose(fpin1);
	fclose(fpout1);
	if (autogen) {
		sprintf(tempstr, "%s_scanautogen.evo", pattern);
		rename(outfile1, tempstr);
	}

	if (notgood == 1) {
		sprintf(tempstr, "%s_dpm.evo", pattern);
		remove(tempstr);		/* remove dpm file */
		sprintf(tempstr, "%s_cpm.evo", pattern);
		remove(tempstr);		/* remove cpm file */
		if (gunzip) remove(TEMPGZIPNAME);	/* remove temporary input file */
		fprintf(stderr, "*** File %s was not successful!!! ***[%s,%d,%s]\n",
				G_infile1, __FILE__, __LINE__, __FUNCTION__);
		fprintf(stderr, "parallel vectors successfully processed:%ld\n", VN);
		fprintf(stderr, "scan     vectors successfully processed:%ld \n", vmscan);
		fprintf(fperrors, "BAD_ERROR:%s:*** File %s was not successful!!! ***[%s,%d,%s]\n",
				G_progstr, G_infile1, __FILE__, __LINE__, __FUNCTION__);
	}
	else if (notgood == 2) {
		if (gunzip) remove(TEMPGZIPNAME);	/* remove temporary input file */
		if (NULL != strstr(G_infile1, ".proc")) {
			/* fprintf(fperrors,"FYI:removing %s file\n",G_infile1); */
			fprintf(stderr, "removing %s file[%s,%d,%s]\n", G_infile1,
					__FILE__, __LINE__, __FUNCTION__);
//         if (debug==0) remove(G_infile1);/* remove temporary .proc file */
		}
		fprintf(stderr, "--- File %s has untranslated microcode!!! ---[%s,%d,%s]\n",
				G_infile1, __FILE__, __LINE__, __FUNCTION__);
		fprintf(stderr, "parallel vectors successfully processed:%ld\n", VN);
		fprintf(stderr, "scan     vectors successfully processed:%ld \n", vmscan);
		fprintf(fperrors, "FYI:%s:--- File %s has untranslated microcode!!! ---\n", G_progstr, G_infile1);
		if (autogen) {
			if (NO_BACKGROUND_GZIP) sprintf(tempstr, "gzip -f %s_scanautogen.evo", pattern);
			else sprintf(tempstr, "gzip -f %s_scanautogen.evo &", pattern);
		}
		else {
			if (NO_BACKGROUND_GZIP) sprintf(tempstr, "gzip -f %s_dpm.evo", pattern);
			else sprintf(tempstr, "gzip -f %s_dpm.evo &", pattern);
		}
		if (gzip) system(tempstr);	/* gzip dpm file */
	}
	else {
		fprintf(stderr, "parallel vectors successfully processed: %ld[%s,%d,%s]\n",
				VN, __FILE__, __LINE__, __FUNCTION__);
		fprintf(stderr, "scan     vectors successfully processed: %ld = %d\n", vmscan, scancnt - 1);
		if (autogen) {
			if (NO_BACKGROUND_GZIP) sprintf(tempstr, "gzip -f %s_scanautogen.evo", pattern);
			else sprintf(tempstr, "gzip -f %s_scanautogen.evo &", pattern);
		}
		else {
			if (NO_BACKGROUND_GZIP) sprintf(tempstr, "gzip -f %s_dpm.evo", pattern);
			else sprintf(tempstr, "gzip -f %s_dpm.evo &", pattern);
		}
		if (gzip) system(tempstr);	/* gzip dpm file */
		if (gunzip) remove(TEMPGZIPNAME);	/* remove temporary input file */
		if (NULL != strstr(G_infile1, ".proc")) {
			/* printf(fperrors,"FYI:removing %s file\n",G_infile1); */
			fprintf(stderr, "removing %s file[%s,%d,%s]\n", G_infile1, __FILE__, __LINE__, __FUNCTION__);
			remove(G_infile1);	/* remove temporary .proc file */
		}
	}

	/* generate CPM file */
	t1 = scanatreal[1] - scanatreal[0];
	fprintf(stdout, "Parallel vectors between SCAN vectors:%d\n", t1);	/* ,%d\n,  t3 */
	for (i = 2; i < scancnt; i++) {
		t2 = scanatreal[i] - scanatreal[i - 1];
		if (t2 != t1) {
			fprintf(fpstatus, "Parallel vector count between SCAN vectors %d is different(%d to %d) at (%ld) [file:%s]\n",
					i, t2, t1, scanatreal[i], G_infile1);
			t1 = t2;
		}
	}
	fprintf(fpout2, "enVisionObject:\"bl8:R5.7\";\n\n");
	fprintf(fpout2, "Pattern %s_cpm {\n", pattern);
	fprintf(fpout2, "    Type Cpm;\n");
	/* fprintf(fpout2,"    Default WaveformTable %s;\n","DEFWFT"); */
	/* fprintf(fpout2,"    Default SignalHeader %s;\n",G_NORMALSGHDR); */

	fprintf(fpout2, "\" Pattern convertor: %s:%s by Anthony Sully compile_date:%s@%s\"\n",
			G_compilestr, G_progstr, __DATE__, __TIME__);
	fprintf(fpout2, "\"      Pattern converted on:%s by:%s on host:%s \"\n\"      in pwd: %s\"\n",
			mydate, G_username, G_hostname, G_pwd);
	fprintf(fpout2, "\"Alias assignments: Drive (Dr=1) %c,%c\"\n", AM_driveLOD1, AM_driveHID1);
	fprintf(fpout2, "\"                   Drive (Dr=0) %c,%c\"\n", AM_driveLOD0, AM_driveHID0);
	fprintf(fpout2, "\"                   Strobe(Dr=0,M=1) %c,%c\"\n", AM_edgestbLOD0, AM_edgestbHID0);
	fprintf(fpout2, "\"                   Strobe(Dr=1,M=1) %c,%c\"\n", AM_edgestbLOD1, AM_edgestbHID1);
	fprintf(fpout2, "\"                   Mask  (Dr=0,M=0) %c,%c\"\n", AM_maskD0, AM_maskHID0);
	fprintf(fpout2, "\"                   CPM call DPM     %c  \"\n", AM_cpmdpm);
	fprintf(fpout2, "\"                   SCAN DRIVE     %c  \"\n", AM_scanin);
	fprintf(fpout2, "\"                   SCAN STROBE     %c  \"\n", AM_scanout);
	fprintf(fpout2, "$%s_cpm_st\n", pattern);
	if (notgood == 1) fprintf(fpout2, "\"*** File %s was not successful!!! ***\"\n", G_infile1);
	if (notgood == 2) fprintf(fpout2, "\"--- File %s has untranslated microcode!!! ---\"\n", G_infile1);
	if (notgood == 1)
		fprintf(stderr, "*** File %s was not successful!!! ***[%s,%d,%s]\n",
				G_infile1, __FILE__, __LINE__, __FUNCTION__);
	if (notgood == 2)
		fprintf(stderr, "--- File %s has untranslated microcode!!! ---\n", G_infile1);
	if (notgood == 1)
		fprintf(fperrors, "BAD_ERROR:%s:*** File %s was not successful!!! ***\n", G_progstr, G_infile1);
	if (notgood == 2)
		fprintf(fperrors, "BAD_ERROR:%s:--- File %s has untranslated microcode!!! ---\n", G_progstr, G_infile1);

	fprintf(fpout2, "*%s* %s %s; <SWCCPM,LDA %s_dpm_st>\n", G_HOLD_VECTOR, SCANRGCT[0], G_NORMALSGHDR, pattern);
	fprintf(fpout2, "*%s* %s %s; <RPT DpmPipeline,SWCDPM>\n", G_HOLD_VECTOR, HOLD_CYCLE, G_NORMALSGHDR);
	G_cyclecount = 1 + 65;		/* +65 is because of the above two lines */
	G_vectorcount = 0 + 2;		/* +2 is because of the above two lines */
	for (li = 0; li < scancnt; li++) {
		if (debug)
			fprintf(stdout, "%5ld %s %ld %d %ld\n", li, SCANRGCT[li], scanatreal[li], scanafor[li],
					scanatreal[li] - ((li == 0) ? 0 : scanatreal[li - 1] + 1) + 1);
	}
	if (maxrepforever == 0) {
		for (li = 0; li < scancnt; li++) {
			fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,RPT %ld>\"%ld:%ld\"\n",
					G_DPM_VECTOR, SCANRGCT[li], G_NORMALSGHDR,
					scanatreal[li] - ((li == 0) ? 0 : scanatreal[li - 1] + 1) + 1, G_vectorcount, G_cyclecount);
			G_cyclecount +=
				scanatreal[li] - ((li == 0) ? 0 : scanatreal[li - 1] + 1) + 1;
			G_vectorcount++;
			fprintf(fpout2, "*%s* %s %s; <SWCCPM,SDP,RPT %d>\"%ld:%ld\"\n",
					G_SCANHOLD, scangct, G_NORMALSGHDR, scanafor[li], G_vectorcount, G_cyclecount);
			G_cyclecount += scanafor[li];
			G_vectorcount++;
		}
		if ((VN - 1) > scanatreal[scancnt - 1]) {
			fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,RPT %ld>\"%ld:%ld\"\n",
					G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR,
					(VN - 1) - scanatreal[scancnt - 1], G_vectorcount, G_cyclecount);
		}
	}
	else {
		for (li = 0; li < scancnt; li++) {
			fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",
					G_DPM_VECTOR, SCANRGCT[li], G_NORMALSGHDR,
					scanatreal[li] - ((li == 0) ? 0 : scanatreal[li - 1] + 1) + 1);
			fprintf(fpout2, "*%s* %s %s; <SWCCPM,SDP,RPT %d>\n",
					G_SCANHOLD, scangct, G_NORMALSGHDR, scanafor[li]);
		}
		fprintf(stdout, "REPEAT FOREVER at %ld\n", repforever[0]);
		if ((VN - 1) > scanatreal[scancnt - 1] && (VN - 1) == repforever[0]
			&& repforeverend[0] == -1) {
			if ((VN - 1) - scanatreal[scancnt - 1] - 3 > 4) {
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR,
						(VN - 1) - scanatreal[scancnt - 1] - 3);
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,COND CONT>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,FLAG(CONT ON)>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,CJMP .>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
			}
			else {
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR,
						(VN - 1) - scanatreal[scancnt - 1] - 1);
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,COND CONT>\n",
						G_HOLD_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,FLAG(CONT ON)>\n",
						G_HOLD_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,CJMP .>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
			}
		}
		else if ((VN - 1) > scanatreal[scancnt - 1] && (VN - 1) > repforever[0]) {
			repforever[0] = 9999999;
			if ((VN - 1) - scanatreal[scancnt - 1] - 3 > 4) {
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR,
						(VN - 1) - scanatreal[scancnt - 1] - 3 - (repforeverlines - 1));
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,COND CONT>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,FLAG(CONT ON)>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
				for (i = 0; i < repforeverlines - 1; i++) {
					fprintf(fpout2, "*%s* %s %s;\"REP FOREVER BLOCK:line%d\"\n",
							repforevervec[i], SCANRGCT[scancnt - 1], G_NORMALSGHDR, i + 1);
				}
				fprintf(fpout2, "*%s* %s %s;<CJMP .-%d>\"REP FOREVER END BLOCK\"\n",
						repforevervec[i], SCANRGCT[scancnt - 1],
						G_NORMALSGHDR, repforeverlines - 1);
			}
			else {
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,RPT %ld>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR,
						(VN - 1) - scanatreal[scancnt - 1] - 3 - (repforeverlines - 1));
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,COND CONT>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
				fprintf(fpout2, "*%s* %s %s; <SWCDPM,SDP,FLAG(CONT ON)>\n",
						G_DPM_VECTOR, SCANRGCT[scancnt - 1], G_NORMALSGHDR);
				for (i = 0; i < repforeverlines - 1; i++) {
					fprintf(fpout2, "*%s* %s %s;\"REP FOREVER BLOCK:line%d\"\n",
							repforevervec[i], SCANRGCT[scancnt - 1], G_NORMALSGHDR, i + 1);
				}
				fprintf(fpout2, "*%s* %s %s;<CJMP .-%d>\"REP FOREVER END BLOCK\"\n",
						repforevervec[i], SCANRGCT[scancnt - 1], G_NORMALSGHDR, repforeverlines - 1);
			}
		}
		else {
			fprintf(stderr, "NON_FATAL_ERROR:REPEAT FOREVER NEEDED BUT NOT SURE WHERE IT GOES!!![%s,%d,%s]\n",
					__FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "NON_FATAL_ERROR:%s:REPEAT FOREVER NEEDED BUT NOT SURE WHERE IT GOES!!! in file[%s]line%ld\n",
					G_progstr, G_infile1, G_readlinenum);
		}
	}
	fprintf(fpout2, "$%s_cpm_end\n*%s* %s %s; <RET>\n", pattern, G_HOLD_VECTOR, HOLD_CYCLE, G_NORMALSGHDR);
//	fprintf(fpout2, "*%s* %s %s; <RPT 512>\n}\n", G_HOLD_VECTOR, HOLD_CYCLE, G_NORMALSGHDR);
	fprintf(fpout2, "}\n"); /* decided to remove the <RPT 512> requirement as enVision does this for threads now */
	fclose(fpout2);
	if (autogen && maxrepforever == 0) {
		fprintf(stderr, "FYI4:SCAN AUTOGEN used for: %s_dpm.evo[%s,%d,%s]\n",
				pattern, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fpstatus, "FYI4:SCAN AUTOGEN used for: %s_dpm.evo\n", pattern);
		remove(outfile2);
	}
	else {
		if (autogen) {
			fprintf(stderr, "FYI5:SCAN AUTOGEN could NOT be used for: %s_dpm.evo[%s,%d,%s]\n",
					pattern, __FILE__, __LINE__, __FUNCTION__);
			fprintf(fpstatus, "FYI5:SCAN AUTOGEN could NOT be used for: %s_dpm.evo\n", pattern);
		}
		if (NO_BACKGROUND_GZIP) sprintf(tempstr, "gzip -f %s_cpm.evo", pattern);
		else sprintf(tempstr, "gzip -f %s_cpm.evo &", pattern);
		if (gzip) system(tempstr);	/* gzip cpm file */
		if (repforeverlines > 0 || maxrepforever > 0) {
			fprintf(stderr, "FYI3:%s: DO NOT optimize the CPM with:\n%s %s[%s,%d,%s]\n",
					G_compilestr, DEFAULT_SCAN_OPT, outfile2, __FILE__, __LINE__, __FUNCTION__);
			fprintf(fpstatus, "FYI3:%s: DO NOT optimize the CPM with:%s %s\n",
					G_compilestr, DEFAULT_SCAN_OPT, outfile2);
		}
		else {
			fprintf(stderr, "FYI2:%s: You may wish to optimize the CPM with:\n%s %s[%s,%d,%s]\n",
					G_compilestr, DEFAULT_SCAN_OPT, outfile2, __FILE__, __LINE__, __FUNCTION__);
			fprintf(fpstatus, "FYI2:%s: You may wish to optimize the CPM with:%s %s\n",
					G_compilestr, DEFAULT_SCAN_OPT, outfile2);
		}
	}
	return (0);
}
