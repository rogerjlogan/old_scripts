/* make specific category inherit tables from menu prompts */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "includes_build.h"

/********************************/
/*										*/
/*		main() function			*/
/*										*/
/********************************/
int main(int argc, char *argv[])
{
	FILE *fpinherit;
//  FILE *fpwaveforms;
	FILE *fpspecific, *fpinhcontrol,*fplog;
	char mydate[101];
	time_t generictime;

	char readstr[READLINELEN + 1], formatstr[50], cathold[READLINELEN + 1];
	char progstr[MEMOSTRLEN], datestr[MEMOSTRLEN], timestr[MEMOSTRLEN], compilestr[MEMOSTRLEN];	/* concaternated strings */
	char *ptrOB, *ptrUC, *ptrCAT;
	int devsel, catsel, tempsel, testsel, enumsel,enumstart=0;
	int devmenu, tempmenu, testmenu, enummenu;
	char CC, yn[1000];
	char extendfilename[2048];
	int i, j, n;

	strcpy(progstr, __FILE__);
	strcpy(datestr, __DATE__);
	strcpy(timestr, __TIME__);
	strcpy(compilestr, argv[0]);
	fprintf(stderr,"\n\n\nThis code is supplied under the LTX-Credence Shareware License.\n");
	fprintf(stderr,"Please see the LSLV1.2 file in the document directory for a full text.\n\n\n");

	if (NULL == (fpinhcontrol = fopen(INHCONTROL, "r"))) {	/* "Waveforms_actable.evo" */
		fprintf(stderr, "\nFATAL_ERROR:%s:Could not open %s for output\n",progstr, INHCONTROL);
		exit(1);
	}

	if (NULL == (fpinherit = fopen(WFTINHVER, "r"))) {	/* "Waveforms_Inherit_tables.evo" */
		fprintf(stderr, "\nFATAL_ERROR:%s:Could not open %s for output\n",progstr, WFTINHVER);
		exit(1);
	}

	Gcat = (GGMCAT *) calloc(MAXCATCODE, sizeof(GGMCAT));
	if (Gcat == NULL) {
		fprintf(stderr,"Could not allocate memory for Gcat,source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}

	Genums = (GGMENUMS *) calloc(MAXENUMCODE, sizeof(GGMENUMS));
	if (Genums == NULL) {
		fprintf(stderr,"Could not allocate memory for Genums,source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}

	specs = (SPECS *) calloc(MAXSPECS, sizeof(SPECS));
	if (specs == NULL) {
		fprintf(stderr,"Could not allocate memory for SPECS,source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}

	read_ggm(fpinhcontrol);
//	fclose(fpinhcontrol); /* this is now closed in read_ggm() */
	write_params();
fprintf(stderr,"A[%s]\n",argv[1]);
	if (argc>1) {
		for (j=0;j<catcount;j++) {
			if (strcmp(argv[1],Gcat[j].name) == 0) {catsel=j;break;}
			}
		if (argc>2) {
			for (j=0;j<enumcount;j++) {
				if (ALLDEVICE[j] == '.') continue;
				if (strcmp(argv[2],Genums[j].name) == 0) {devsel=j;break;}
				}
			}
		if (argc>3) {
			for (j=0;j<enumcount;j++) {
				if (ALLTEMP[j] == '.') continue;
				if (strcmp(argv[3],Genums[j].name) == 0) {tempsel=j;break;}
				}
			}
		if (argc>4) {
			for (j=0;j<enumcount;j++) {
				if (ALLTEST[j] == '.') continue;
				if (strcmp(argv[4],Genums[j].name) == 0) {testsel=j;break;}
				}
			}
		if (argc>5) {
			for (j=0;j<enumcount;j++) {
				if (ALLTEST[j] != '.' || ALLTEMP[j] != '.' || ALLDEVICE[j] != '.') continue;
				if (strcmp(argv[5],Genums[j].name) == 0) {enumsel=j;break;}
				}
			}
		}

	else {
		REDOALL:
		sprintf(formatstr, "(%%03d) %%-%ds   ", maxactlen);
		for (i = 0; i < catcount; i++) {
			fprintf(stderr, formatstr, i, Gcat[i].name);
			if (i % 3 == 2)
				fputc('\n', stderr);
		}
		fprintf(stderr, "\nCat?");
		REDOCAT:
		n = scanf("%d", &catsel);
		if (n != 1 || catsel < 0) goto REDOCAT;
		fputc('\n', stderr);

//b1[11111111111111]E[11111111111111111111111]<000>UC[A] L[0008831]STR[STOP(ALLENUMS,ALLTABLES)]
/* so, 2 for //, 3 for b1[, catcount for 1111..., 3 for ]E[		 ] */
		sprintf(formatstr, "(%%03d) %%-%ds   ", maxenumlen);

		for (j = i = 0; i < enumcount; i++) {
			if (ALLDEVICE[i] == '.') continue;
			fprintf(stderr, formatstr, j, Genums[i].name);
			if (j % 3 == 2) fputc('\n', stderr);
			enumstart++;
			j++;
		}
		fprintf(stderr, "\nDevice?");
		REDODEV:
		n = scanf("%d", &devmenu);
		if (n != 1 || devmenu < 0 || devmenu >= j) goto REDODEV;
		for (j = i = 0; i < enumcount; i++) {	/* need to flip 'sel' back into the 'i' equivalent */
			if (ALLDEVICE[i] == '.') continue;
			if (devmenu == j) {
				devsel = i;
				break;
			}
			j++;
		}
		fputc('\n', stderr);

		for (j = i = 0; i < enumcount; i++) {
			if (ALLTEMP[i] == '.') continue;
			fprintf(stderr, formatstr, j, Genums[i].name);
			if (j % 3 == 2) fputc('\n', stderr);
			enumstart++;
			j++;
		}
		fprintf(stderr, "\nTemp?");
		REDOTEMP:
		n = scanf("%d", &tempmenu);
		if (n != 1 || tempmenu < 0 || tempmenu >= j) goto REDOTEMP;
		for (j = i = 0; i < enumcount; i++) {	/* need to flip 'sel' back into the 'i' equivalent */
			if (ALLTEMP[i] == '.') continue;
			if (tempmenu == j) {
				tempsel = i;
				break;
			}
			j++;
		}
		fputc('\n', stderr);

		for (j = i = 0; i < enumcount; i++) {
			if (ALLTEST[i] == '.') continue;
			fprintf(stderr, formatstr, j, Genums[i].name);
			if (j % 3 == 2) fputc('\n', stderr);
			enumstart++;
			j++;
		}
		fprintf(stderr, "\nTest?");
		REDOTEST:
		n = scanf("%d", &testmenu);
		if (n != 1 || testmenu < 0 || testmenu >= j) goto REDOTEST;
		for (j = i = 0; i < enumcount; i++) {	/* need to flip 'sel' back into the 'i' equivalent */
			if (ALLTEST[i] == '.') continue;
			if (testmenu == j) {
				testsel = i;
				break;
			}
			j++;
		}
		fputc('\n', stderr);

//	fprintf(stderr,"TST[%s]\nTMP[%s]\nDEV[%s]\n",ALLTEST,ALLTEMP,ALLDEVICE);

		for (j = i = 0; i < enumcount; i++) {
			if (ALLTEST[i] != '.' || ALLTEMP[i] != '.' || ALLDEVICE[i] != '.') continue;
			fprintf(stderr, formatstr, j, Genums[i].name);
			if (j % 3 == 2) fputc('\n', stderr);
			j++;
		}
		fprintf(stderr, "\nEnum?");
		if (j > 0) {
		REDOENUM:
			n = scanf("%d", &enummenu);
			if (n != 1 || enummenu < 0 || enummenu >= j) goto REDOENUM;
			for (j = i = 0; i < enumcount; i++) {	/* need to flip 'sel' back into the 'i' equivalent */
				if (ALLTEST[i] != '.' || ALLTEMP[i] != '.' || ALLDEVICE[i] != '.') continue;
				if (enummenu == j) {
					enumsel = i;
					break;
				}
				j++;
			}
			fputc('\n', stderr);
		}
		else
			enumsel = -1;

		fprintf(stderr, "CAT:  (%d) %s\n", catsel, Gcat[catsel].name);
		fprintf(stderr, "DEV:  (%d,%d) %s\n", devmenu, devsel, Genums[devsel].name);
		fprintf(stderr, "TEMP: (%d,%d) %s\n", tempmenu, tempsel, Genums[tempsel].name);
		fprintf(stderr, "TEST: (%d,%d) %s\n", testmenu, testsel, Genums[testsel].name);
		if (enumsel != -1)
			fprintf(stderr, "ENUM: (%d,%d) %s\n", enummenu, enumsel, Genums[enumsel].name);
		fprintf(stderr, "Is this correct?(Y/n)");
		n = scanf("%s", yn);
		if (yn[0] == 'N' || yn[0] == 'n') goto REDOALL;
		if (NULL == (fplog = fopen("BIM.log", "a"))) {
			fprintf(stderr, "\nNON-FATAL_ERROR:%s:Could not open %s for output\n",progstr,"BIM.log");
		}
		else {
			if (enumsel == -1){
				fprintf(fplog,"BUILD_INHERIT_MENU %s %s %s %s\n",Gcat[catsel].name, Genums[devsel].name, Genums[tempsel].name, Genums[testsel].name);
				}
			else {
				fprintf(fplog,"BUILD_INHERIT_MENU %s %s %s %s %s\n",Gcat[catsel].name, Genums[devsel].name, Genums[tempsel].name, Genums[testsel].name, Genums[enumsel].name);
			}
		fclose(fplog);
		}
	}
	catstr[0] = '\0';
	n = 0;

	if (enumsel == -1) {
		for (i = 0; i < codecnt; i++) {
//          fprintf(stdout,"ChkFor[%d,%d,%d,%d]\n",5+catsel,5+catcount+3+tempsel,5+catcount+3+testsel,5+catcount+3+devsel);
			if (catcodes[i][5 + catsel] == '1' &&
				catcodes[i][5 + catcount + 3 + tempsel] == '1' &&
				catcodes[i][5 + catcount + 3 + testsel] == '1' &&
				catcodes[i][5 + catcount + 3 + devsel] == '1') {
				fprintf(stdout, "<<%s>>\n", catcodes[i]);
				ptrUC = strstr(catcodes[i], "UC[");
				CC = *(ptrUC + 3);
				if (strchr(catstr, CC) == NULL) {
					catstr[n] = CC;
					n++;
					catstr[n] = '\0';
				}
				if (n >= MAXCATCODE) error("Too many catcodes", __LINE__);
			}

		}
	}
	if (enumsel != -1) {
		for (i = 0; i < codecnt; i++) {
			if (catcodes[i][5 + catsel] == '1' &&
				catcodes[i][5 + catcount + 3 + tempsel] == '1' &&
				catcodes[i][5 + catcount + 3 + testsel] == '1' &&
				catcodes[i][5 + catcount + 3 + devsel] == '1' &&
				catcodes[i][5 + catcount + 3 + enumsel] == '1') {
				fprintf(stdout, "E<%s>>\n", catcodes[i]);
				ptrUC = strstr(catcodes[i], "UC[");
				CC = *(ptrUC + 3);
				if (strchr(catstr, CC) == NULL) {
					catstr[n] = CC;
					n++;
					catstr[n] = '\0';
				}
				if (n >= MAXCATCODE) error("Too many catcodes", __LINE__);
			}

		}
	}
	fprintf(stdout, "catstr:[%s]\n", catstr);

	sprintf(extendfilename, "%s_%s.evo", WFTINHSPECIFIC, catstr);
	if (NULL == (fpspecific = fopen(extendfilename, "w"))) {
		fprintf(stderr, "\nFATAL_ERROR:%s:Could not open %s for output\n", progstr, extendfilename);
		exit(1);
	}

	fprintf(fpspecific, "%s\n\n", ENVISIONTOP);

	time(&generictime);
	ctime_r(&generictime,mydate);
	mydate[strlen(mydate) - 1] = '\0';
	fprintf(fpspecific, "//Build_menu Compile date:%s\n//Category_%s[%s,%s,%s,%s] run date:%s\n",
			datestr, catstr, Gcat[catsel].name, Genums[devsel].name,
			Genums[tempsel].name, Genums[testsel].name, mydate);


	while (fgets(readstr, READLINELEN - 1, fpinherit) != NULL) {
		if (strstr(readstr, ENVISIONTOP) != NULL) continue;
		if ((ptrCAT = strstr(readstr, "_cat_")) == NULL) {	/* not found */
			if (strstr(readstr, "WaveformTable") != NULL) {
				ptrOB = strchr(readstr, '{');	/* } */
				if (ptrOB != NULL) *(ptrOB - 1) = '\0';
				strcat(readstr, "_");
				strcat(readstr, catstr);	/* update the Waveformtable name with the selection */
				fprintf(fpspecific, "%s {\n", readstr);
			}
			else fprintf(fpspecific, "%s", readstr);
		}
		else {					/* found _cat_ */
			strcpy(cathold, ptrCAT + sizeof("_cat_") - 1);
			ptrOB = strchr(cathold, '{');	/* } */
			if (ptrOB != NULL) *(ptrOB - 1) = '\0';
//          fprintf(stdout,"[%s,%s]",cathold,catstr);
			for (i = 0; i < n; i++) {
				if (strchr(cathold, catstr[i]) != NULL) {
					fprintf(fpspecific, "%s", readstr);
					break;
				}
			}
		}
	}
	fprintf(stderr, "processed %d entries\n", catcount);

	read_pat_ref(); /* if translation_patref.txt is available then read it, count in patref */

	if (maxref>0) {
		fprintf(fpspecific,"PatternSequence %s_%s_PatSeq {\n",Gcat[catsel].name,catstr);
		fprintf(fpspecific,"//   Thread[0] = My_Thread;\n");
		fprintf(fpspecific,"   Zipper = Zipper {\n");
		for (i=0;i<maxref;i++) {
			fprintf(fpspecific,"      Row { PolMod8PatGrp, %s = { %s_%s, COMMON_WFT } }\n",Gwftref[i].wftref,Gwftref[i].wftref,catstr);
			}
		fprintf(fpspecific,"   evAutoBasePeriod = True;\n}\n}\n");
		}
	fclose(fpspecific);
	fclose(fpinherit);
	return (0);
}

void error(char *ptr, int line)
{
	fprintf(stderr, "Bad syntax[%s] called from %s, line %d\n", ptr, __FILE__, line);
	exit(1);
}
