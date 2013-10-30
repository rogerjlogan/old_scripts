#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "includes_ggm.h"
#include "aliasmap.h"

#define PBELEMENTS 1000
typedef struct PB {
	char cellstr[READLINELEN +1];
	char compareopen[READLINELEN+1]; /* this will be '\0' if compareclose only */
	char compareclose[READLINELEN+1];
	} PB;

typedef struct ALIASLIST {
	char nocat[READLINELEN+1];
	int alias1,alias2,oldal1,oldal2;
	} ALIASLIST;

typedef struct CPB {
	char pb[2][NUMPINS + 1];
	} CPB;

int purge_actable(FILE * fpinherit, FILE *fp_mod_file, char *muxpin) {
	long tell, rwpos, tellinh, tellinh2;
	int pinorder[NUMPINS];
	int i, j, k, row, tbl;
	int ret, inactable, maxcellnumber, found, removecells,pushback,pushbackindex = 0,two_one,oddeven;
	int pba=0, pbc=0, whichalias, anew1, anew2, aold1, aold2, dsetascii;
	FILE *fpact, *fpactpurge;
	struct PB *pblist;
	struct ALIASLIST *aliaslist;
	struct CPB *cycpb;
	struct stat statbuf;
	off_t filesize, celllistsize;
	char pinlist[READLINELEN + 1];
	char pinbinarycyc[READLINELEN + 1], PINF[100];
	char *wfcelllist;
	char cellname[READLINELEN + 1], cellnamef[READLINELEN+1], hold[READLINELEN+1];
	char purgedfile[FILENAMELEN];
	char readstr[READLINELEN + 1],cellbuff[READLINELEN+1],nocat[READLINELEN+1];
	char *ptrQ1, *ptrQ2, *ptrk, *ptrs, *ptra, *ptrIN, testaliases[10], tempbuff[sizeof(PBCYC)+1];
	char pbd0[READLINELEN + 1], pbd1[READLINELEN + 1];
	const char pbstr[65] = PBCHARS;
   char bm;

	ret = stat(WFTMODVER, &statbuf);
	if (ret == 0) filesize = statbuf.st_size;
	else {
		fprintf(stderr, "Can't determine filesize for [%s], source[%s,%d,%s]\n",
				WFTMODVER, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Can't determine filesize for [%s]\n", WFTMODVER);
		exit(1);
	}
	if (NULL == (fpact = fopen(WFTMODVER, "r"))) {
		fprintf(stderr, "\nfile [%s] not found, source[%s,%d,%s]\n", WFTMODVER, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nfile [%s] not found\n", WFTMODVER);
		exit(1);
	}
	celllistsize = filesize / 20;	/* the 20 is a rough guess, calculations on C40 showed divide by 400! */
//  fprintf(stdout,"CLS=%ld\n",celllistsize);
	wfcelllist = calloc((size_t) (celllistsize + 1), MAX_CELLLEN + 1);
	if (wfcelllist == NULL) {
		fprintf(stderr, "Could not allocate memory for waveform cell list in memory, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Could not allocate memory for waveform cell list in memory\n");
		exit(1);
	}

	aliaslist = (ALIASLIST *) calloc(PBELEMENTS, sizeof(ALIASLIST));
	if (aliaslist == NULL) {
		fprintf(stderr, "Could not allocate memory for alias list in memory, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Could not allocate memory for alias list in memory\n");
		exit(1);
		}

	pblist = (PB *) calloc(PBELEMENTS, sizeof(PB));
	if (pblist == NULL) {
		fprintf(stderr, "Could not allocate memory for pushback cell list in memory, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Could not allocate memory for pushback cell list in memory\n");
		exit(1);
		}

	cycpb = (CPB *) calloc(MAXCYCTBL, sizeof(CPB));
	if (cycpb == NULL) {
		fprintf(stderr, "Could not allocate memory for cycpb in memory, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Could not allocate memory for cycpb in memory\n");
		exit(1);
	}
	strcpy(purgedfile, WFTMODVER_RED);
	if (ACDATA) strcpy(purgedfile, "/dev/null");
	if (NULL == (fpactpurge = fopen(purgedfile, "w"))) {
		fprintf(stderr, "\nfile [%s] not found, source[%s,%d,%s]\n", purgedfile, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nfile [%s] not found\n", purgedfile);
		exit(1);
	}
	removecells = maxcellnumber = inactable = 0;
	while (fgets(readstr, READLINELEN - 1, fpact) != NULL) {
		readstr[strlen(readstr) - 1] = '\0';	/* remove trailing \n */
		if (inactable == 0 && strstr(readstr, "WaveformTable ACTABLE") != NULL) {
			inactable = 1;
			fprintf(fpactpurge, "%s\n", readstr);
			fprintf(fpactpurge, "//This table has purged cells to the first instance of each cell\n");
			fprintf(fpactpurge, "// this means not all possible pins are listed for the group\n");
			fprintf(fpactpurge, "// The %s file deals with the correct pins\n", WFTINHVER);
		}
		else if (inactable == 0) fprintf(fpactpurge, "%s\n", readstr);
		else if (strstr(readstr, "Cell \"") == NULL) {
			fprintf(fpactpurge, "%s\n", readstr);
			}
		else {					/* found a Cell */
			strcpy(cellnamef,readstr);
			ptrQ1 = strchr(readstr, '\"');
			if (ptrQ1 != NULL) ptrQ2 = strchr(ptrQ1 + 1, '\"');
			strcpy(cellname, ptrQ2);
			for (found = i = 0; i < maxcellnumber; i++) {	/* see if we've seen this one before */
				if (strcmp(cellname, (wfcelllist + i * (MAX_CELLLEN + 1))) == 0) {	/* cells match, erase */
					found = 1;
					removecells++;
					while (fgets(readstr, READLINELEN - 1, fpact) != NULL) {
						if (strstr(readstr, "Cell \"") != NULL || (readstr[0] == '/' && readstr[1] == '/')) {	/* found new, rewind and break */
							fseek(fpact, tell, SEEK_SET);
							break;
						}
						else {
							tell = ftell(fpact);
						}
					}
				}				/* if cells match */
			}					/* for i to maxcell */
			if (found == 0) {	/* cell was not found in the list */
				pushback = 0;
				if (strstr(cellname,"DSET0kW")!=NULL   || strstr(cellname,"DSET1kW")!=NULL  ||
					 strstr(cellname,"DSET0kXW")!=NULL  || strstr(cellname,"DSET1kXW")!=NULL ||
					 strstr(cellname,"DSET0XkW")!=NULL  || strstr(cellname,"DSET1XkW")!=NULL ||
					 strstr(cellname,"DSET0kXf")!=NULL  || strstr(cellname,"DSET1kXf")!=NULL ||
					 strstr(cellname,"DSET0Xkf")!=NULL  || strstr(cellname,"DSET1Xkf")!=NULL ||
					 strstr(cellname,"DSET0kXf")!=NULL  || strstr(cellname,"DSET1kXf")!=NULL ||
					 strstr(cellname,"DSET0kXD")!=NULL  || strstr(cellname,"DSET1kXD")!=NULL ||
					 strstr(cellname,"DSET0XkD")!=NULL  || strstr(cellname,"DSET1XkD")!=NULL ||
					 strstr(cellname,"DSET0kD") !=NULL  || strstr(cellname,"DSET1kD") !=NULL ||
					 strstr(cellname,"DSET0kDD")!=NULL  || strstr(cellname,"DSET1kDD")!=NULL ||
					 strstr(cellname,"DSET0kDDD") !=NULL|| strstr(cellname,"DSET1kDDD") !=NULL ) pushback = 1; /* close open */
				else if (strstr(cellname,"WkWk")!=NULL || strstr(cellname,"fkfk")!=NULL) pushback = 2; /* double window */
				if (pushback) {
					cellbuff[0]='\0';
					while (fgets(readstr, READLINELEN - 1, fpact) != NULL) {
						if (strstr(readstr,"Cell")!=NULL) break;
						rwpos=ftell(fpact);
						strcat(cellbuff,readstr);
						}
					}
				if (NOPUSHCYC==0 && pushback && (ptrk=strstr(cellbuff,"EntryState Compare"))!=NULL) {
					*(ptrk-1) = '/';
					fputc('=',stdout);
					*(ptrk-2) = '/'; /* this comments the original EntryStateCompare */
					}
				if (NOPUSHCYC==0 && pushback==1 && (ptrk=strstr(cellbuff,"CompareClose"))!=NULL) {
					*(ptrk-1) = '/';
					fputc('+',stdout);
					*(ptrk-2) = '/'; /* this comments the original edge */
					ptrs = strchr(ptrk,';');
					if (ptrs != NULL) *(ptrs-1) = '\0'; /* this should wipe close quote and semicolon */
					strcpy(hold,ptrk);
					sprintf(tempbuff," + %s\"",PBCYC);
					strcat(hold,tempbuff);
					strcpy(pblist[pushbackindex].cellstr,cellnamef); /* this saves the edge somewhere */
					strcpy(pblist[pushbackindex].compareclose,hold); /* this saves the edge somewhere */
					pblist[pushbackindex].compareopen[0] = '\0'; /* no entry here */
					pushbackindex++;
					if (pushbackindex >= PBELEMENTS) exit(1);
					*(ptrs-1) = '\"';
					}
				if (NOPUSHCYC==0 && pushback==2 && (ptrk=strstr(cellbuff,"CompareOpen"))!=NULL) { /* double window */
					fputc('<',stdout);
					*(ptrk-1) = '/';
					*(ptrk-2) = '/'; /* this comments the original edge */
					ptrs = strchr(ptrk,';');
					if (ptrs != NULL) *(ptrs-1) = '\0'; /* this should wipe close quote and semicolon */
					strcpy(hold,ptrk);
					sprintf(tempbuff," + %s\"",PBCYC);
					strcat(hold,tempbuff);
					strcpy(pblist[pushbackindex].cellstr,cellnamef); /* this saves the edge somewhere */
					strcpy(pblist[pushbackindex].compareopen,hold); /* this saves the edge somewhere */
					/* pushbackindex++; */ /* no increment because we also get the next CompareClose */
					/* if (pushbackindex >= PBELEMENTS) exit(1); */
					*(ptrs-1) = '\"';
					}
				if (NOPUSHCYC==0 && pushback==2 && (ptrk=strstr(cellbuff,"CompareClose"))!=NULL) { /* double window */
					fputc('>',stdout);
					*(ptrk-1) = '/';
					*(ptrk-2) = '/'; /* this comments the original edge */
					ptrs = strchr(ptrk,';');
					if (ptrs != NULL) *(ptrs-1) = '\0'; /* this should wipe close quote and semicolon */
					strcpy(hold,ptrk);
					sprintf(tempbuff," + %s\"",PBCYC);
					strcat(hold,tempbuff);
					strcat(pblist[pushbackindex].compareclose,hold); /* this saves the edge somewhere */
					pushbackindex++;
					if (pushbackindex >= PBELEMENTS) exit(1);
					*(ptrs-1) = '\"';
					}
				if (pushback == 0) fprintf(fpactpurge, "%s\n", readstr);
				else {
					fprintf(fpactpurge,"%s\n%s",pblist[pushbackindex-1].cellstr,cellbuff);
					fseek(fpact,rwpos,SEEK_SET); /* move back to previous read */
					}
				strcpy((wfcelllist + maxcellnumber * (MAX_CELLLEN + 1)), cellname);
				maxcellnumber++;
				if (maxcellnumber > celllistsize) {
					fprintf(stderr, "Too many cells in compaction, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
					exit(1);
					}

			}					/* not found */
		}						/* for i to maxcell */
	}							/* found a cell */
	fprintf(stderr, "Purged %d duplicate Cells\n", removecells);
	fprintf(fpactpurge, "%s\n", readstr);	/* return the  last line (usually brace close) */
	if (EVX2 && NOPUSHCYC==0) {
		tellinh = tellinh2 = ftell(fpinherit);
		rewind(fpinherit);
		while (fgets(readstr, READLINELEN - 1, fpinherit) != NULL) {
			if (strstr(readstr,"Period")!=NULL) {
				ptrQ1 = strchr(readstr, '\"');
				if (ptrQ1 == NULL) continue;
				ptrQ2 = strchr(ptrQ1 + 1,'\"');
				if (ptrQ2 == NULL) continue;
				ptrQ2 -= sizeof(PBCYC);
				*(ptrQ2++) = '-';
				for (i=0;i<sizeof(PBCYC);i++) *(ptrQ2++) = PBCYC[i];
				fseek(fpinherit, tellinh2, SEEK_SET);
				fprintf(fpinherit,"%s", readstr); /* rewrite modified line with pushback cyc */
				}
			tellinh2 = ftell(fpinherit); /* keep beginning of last line */
			}
		fseek(fpinherit, tellinh, SEEK_SET);
		
		
		fprintf(fpactpurge,"WaveformTable %s {\n",PBEDGES); bm='}';
		fprintf(fpactpurge,"   Period \"%s\";\n",PBCYC);
		fprintf(fpactpurge,"   Comment=\"The aliases in this table are based on the source Cell, they get remapped in the %s table\";\n",PBWFT);
		fprintf(fpinherit,"WaveformTable %s {\n",PBWFT); bm='}';
		fprintf(fpinherit,"   Period \"%s\";\n",PBCYC);
		fprintf(fpinherit,"   Comment=\"These aliases are arbitrarily assigned (in order, hopefully it doesnt run out) source alias available in %s\";\n",PBEDGES);
#define ODD 1
#define EVEN 0
		fflush(fpinherit);
		fflush(fpactpurge);

		for (tbl=0; tbl<maxtbl; tbl++) {
			for (k=0;k<maxpin;k++) {
				cycpb[tbl].pb[0][k] = cycpb[tbl].pb[1][k] = AM_DONOTHINGPAD;
			}
			cycpb[tbl].pb[0][k] = cycpb[tbl].pb[1][k] = '\0';
//			fprintf(stdout,"<%s>[%s][%s]\n",cyctbl[tbl].tblname, cycpb[tbl].pb[0],cycpb[tbl].pb[1]);
			}

		for (i=0;i<pushbackindex;i++) {
			dsetascii = '0'; 
			if (strstr(pblist[i].cellstr,"DSET1") != NULL) dsetascii = '1';
			two_one = 2;
			sprintf(testaliases,"%c/%c",AM_edgestbLOD0,AM_maskD0);
			ptra = strstr(pblist[i].cellstr,testaliases);
			if (ptra != NULL) {oddeven = EVEN; two_one = 1; *(ptra+1) = *(ptra+2) = ' ';}
			sprintf(testaliases,"%c/%c",AM_edgestbHID0,AM_maskHID0);
			ptra = strstr(pblist[i].cellstr,testaliases);
			if (ptra != NULL) {oddeven = ODD; two_one = 1; *(ptra+1) = *(ptra+2) = ' ';}
			sprintf(testaliases,"%c/%c",AM_edgestbLOD1,AM_maskD1);
			ptra = strstr(pblist[i].cellstr,testaliases);
			if (ptra != NULL) {oddeven = EVEN; two_one = 1; *(ptra+1) = *(ptra+2) = ' ';}
			sprintf(testaliases,"%c/%c",AM_edgestbHID1,AM_maskHID1);
			ptra = strstr(pblist[i].cellstr,testaliases);
			if (ptra != NULL) {oddeven = ODD; two_one = 1; *(ptra+1) = *(ptra+2) = ' ';}
			sprintf(testaliases,"%c/%c/%c/%c",AM_edgestbLOD0,AM_edgestbHID0,AM_maskD0,AM_maskHID0);
			ptra = strstr(pblist[i].cellstr,testaliases);
			if (ptra != NULL) {two_one = 2; *(ptra+3) = *(ptra+4) =  *(ptra+5) = *(ptra+6) =' ';}
			sprintf(testaliases,"%c/%c/%c/%c",AM_edgestbLOD1,AM_edgestbHID1,AM_maskD1,AM_maskHID1);
			ptra = strstr(pblist[i].cellstr,testaliases);
			if (ptra != NULL) {two_one = 2; *(ptra+3) = *(ptra+4) = *(ptra+5) = *(ptra+6) = ' ';}
		
			if (two_one == 1) {
				if (pblist[i].compareopen[0]=='\0')	fprintf(fpactpurge, "   C%s\n      Data %c;\n      Drive {\n         EntryState DriveOff;\n      }\n      Compare {\n         EntryState CompareOpenData;\n         Waveform {\n            %s;\n         }\n      }\n   }\n",
					&pblist[i].cellstr[1], oddeven?'1':'0', pblist[i].compareclose);

				else											fprintf(fpactpurge, "   C%s\n      Data %c;\n      Drive {\n         EntryState DriveOff;\n      }\n      Compare {\n         EntryState CompareOpenData;\n         Waveform {\n            %s;\n            %s;\n         }\n      }\n   }\n",
					&pblist[i].cellstr[1], oddeven?'1':'0', pblist[i].compareopen, pblist[i].compareclose);
				}
			else {
				if (pblist[i].compareopen[0]=='\0')	fprintf(fpactpurge, "   C%s\n      Data 0/1;\n      Drive {\n         EntryState DriveOff;\n      }\n      Compare {\n         EntryState CompareOpenData;\n         Waveform {\n            %s;\n         }\n      }\n   }\n",
					&pblist[i].cellstr[1], pblist[i].compareclose);

				else											fprintf(fpactpurge, "   C%s\n      Data 0/1;\n      Drive {\n         EntryState DriveOff;\n      }\n      Compare {\n         EntryState CompareOpenData;\n         Waveform {\n            %s;\n            %s;\n         }\n      }\n   }\n",
					&pblist[i].cellstr[1], pblist[i].compareopen, pblist[i].compareclose);
				}
/* NOW create the inherit entries */
			if (two_one == 2) {
				if ((ptrs = strchr(&pblist[i].cellstr[1],'/')) != NULL) {
					ptrk = ptrs + 2; 
					ptrIN = ptrs;
					while ( *ptrk == ' ') ptrk++;
					strcpy(cellbuff, ptrk );
					cellbuff[strlen(cellbuff)-1] = '\0';
					strcpy(nocat,cellbuff);
					ptra = strstr(nocat,"_cat_");
					ptra = strstr(nocat,"DSET");
					if (*(ptra-1) == 'A' || *(ptra-1) == 'B') ptra--;
					*ptra = '\0';
					for (j=0;j<pbc;j++) {
						if (strstr(aliaslist[j].nocat,nocat)!=NULL) {
							*(ptrIN-1) = aliaslist[j].alias1;
							*(ptrIN+1) = aliaslist[j].alias2;
							break;
							}
						}
					if (j == pbc) {
						strcpy(aliaslist[pbc].nocat,cellbuff);
						aold1 = aliaslist[pbc].oldal1 = *(ptrIN-1);
						aold2 = aliaslist[pbc].oldal2 = *(ptrIN+1);
						anew1 = aliaslist[pbc].alias1 = pbstr[pba];
						anew2 = aliaslist[pbc].alias2 = pbstr[pba+1];
						*(ptrIN-1) = pbstr[pba];
						*(ptrIN+1) = pbstr[pba+1];
						pbc++;
						pba += 2;
						}
					bm='{';fprintf(fpinherit,"   C%s Inherit %s.%s; }\n",&pblist[i].cellstr[1], PBEDGES, cellbuff);
					}
				}
			else {
				ptrk = NULL;
				sprintf(testaliases," %c ",AM_edgestbLOD0);
				if ((ptrs = strstr(&pblist[i].cellstr[1],testaliases)) != NULL) { ptrIN = ptrs; ptrk = ptrs + 2; }
				sprintf(testaliases," %c ",AM_edgestbHID0);
				if ((ptrs = strstr(&pblist[i].cellstr[1],testaliases)) != NULL) { ptrIN = ptrs; ptrk = ptrs + 2; }
				sprintf(testaliases," %c ",AM_edgestbLOD1);
				if ((ptrs = strstr(&pblist[i].cellstr[1],testaliases)) != NULL) { ptrIN = ptrs; ptrk = ptrs + 2; }
				sprintf(testaliases," %c ",AM_edgestbHID1);
				if ((ptrs = strstr(&pblist[i].cellstr[1],testaliases)) != NULL) { ptrIN = ptrs; ptrk = ptrs + 2; }
				if (ptrk!=NULL) {
					while (*ptrk == ' ') ptrk++;
					strcpy(cellbuff, ptrk );
					cellbuff[strlen(cellbuff)-1] = '\0';
					strcpy(nocat,cellbuff);
//					ptra = strstr(nocat,"_cat_");
					ptra = strstr(nocat,"DSET");
					whichalias = 0;
					if      (*(ptra-1) == 'A')	{whichalias = 1; ptra--;}
					else if (*(ptra-1) == 'B')	{whichalias = 2; ptra--;}
					*ptra = '\0';
					for (j=0;j<pbc;j++) {
						if (strstr(aliaslist[j].nocat,nocat)!=NULL) {
							if (aliaslist[j].oldal1 != *(ptrIN+1)) aold2 = aliaslist[j].oldal2 = *(ptrIN+1); /* add in second alias if separate */
							if (whichalias == 1) *(ptrIN+1) = aliaslist[j].alias1;
							else                 *(ptrIN+1) = aliaslist[j].alias2;
							break;
							}
						}
					if (j == pbc) {
						strcpy(aliaslist[pbc].nocat,cellbuff);
						anew1 = aliaslist[pbc].alias1 = pbstr[pba];
						anew2 = aliaslist[pbc].alias2 = pbstr[pba+1];
						if (whichalias == 1)	{ aold1 = aliaslist[pbc].oldal1 = *(ptrIN+1); aold2 = aliaslist[pbc].oldal2 = '_'; *(ptrIN+1) = pbstr[pba]; }
						else 						{ aold1 = aliaslist[pbc].oldal1 = *(ptrIN+1); aold2 = aliaslist[pbc].oldal2 = '_'; *(ptrIN+1) = pbstr[pba+1]; }
						pbc++;
						pba += 2;
						}
					bm='{';fprintf(fpinherit,"   C%s Inherit %s.%s; }\n",&pblist[i].cellstr[1], PBEDGES, cellbuff);
					}
				}
			if (aold2 == '_') continue; /* second alias not found yet, assuming everything has two aliases.... */
			ptrIN = strchr(pblist[i].cellstr,'\"');
			if (ptrIN != NULL) ptrk = strchr(ptrIN+1,'\"');
			pinlist[0] = '\0';
			if ((ptrIN != NULL) && (ptrk != NULL)) { *ptrk = '\0'; strcpy(pinlist,ptrIN+1); *ptrk = '\"'; }
// 		resolve_list(pinlist, pinbinary, '1', '0',pinorder);
//			fprintf(stdout,"#~PBD%c,%c,%c,%c,%c\n#!PBD[%s]\n", dsetascii, aold1, aold2, anew1, anew2, pinbinary);
			for (tbl=0; tbl<maxtbl; tbl++) {
				for (row=0; row<cyctbl[tbl].maxrow; row++) {
					if (cyctbl[tbl].valid[row] == 0) continue; /* it was replaced with a pingroup */
					sprintf(pbd0," %s_",cycsets[cyctbl[tbl].rows[row]].dset0); /* make the strings unique */
					sprintf(pbd1," %s_",cycsets[cyctbl[tbl].rows[row]].dset1); /* make the strings unique */
					if ( (strstr(pblist[i].cellstr,pbd0) != NULL ) || (strstr(pblist[i].cellstr,pbd1) != NULL ) ) {
						resolve_list(cycsets[cyctbl[tbl].rows[row]].pin, pinbinarycyc, '1', '0', pinorder);
						for (k=0; k<maxpin; k++) {
//							if (pinbinary[k] == '1' && pinbinarycyc[k] == '1') {
							if (pinbinarycyc[k] == '1') {
								if (cycpb[tbl].pb[dsetascii-'0'][k] == AM_DONOTHINGPAD) ;
								else if (cycpb[tbl].pb[dsetascii-'0'][k] == anew1) ;
								else {
									fprintf(fpstatus,"REMAP [%s][%d],%c,%c,%c,%d,T%d,D%d,K%d\n",
										cyctbl[tbl].tblname,k,cycpb[tbl].pb[dsetascii-'0'][k],anew1,anew2,cycpb[tbl].pb[dsetascii-'0'][k],tbl,dsetascii-'0',k);
									fprintf(fpstatus,"[%d][%s][%s]\n",tbl,cycpb[tbl].pb[0],cycpb[tbl].pb[1]);
									}
								cycpb[tbl].pb[dsetascii-'0'][k] = anew1;
								} /* yep, they exist in both pin lists */
							} /* next pin, k */
						}/* one of the two dsets exist in the cell we are trying to add */
					} /* next row */
				} /* next cyctbl */
			} /* next cell to check */
		for (tbl=0;tbl<maxtbl;tbl++) {
			fprintf(fp_mod_file,"#PB<%s>[%s][%s]\n",cyctbl[tbl].tblname, cycpb[tbl].pb[0],cycpb[tbl].pb[1]);
			}

		bm='{';fprintf(fpactpurge,"}\n");
		bm='{';fprintf(fpinherit,"}\n"); 
		fprintf(stdout,"Created %d lookups\n",pbc);
		fprintf(fpactpurge,"WaveformTable %s {\n", PBCOMMON); bm = '}';
		fprintf(fpactpurge,"   Period \"%s\";\n",PBCYC);
		if (MUXFLAG && NOMUX == 0) strcpy(PINF,"ALLPINS+MUXSECONDARYPINS");
		else strcpy(PINF,"ALLPINS");
		fprintf(fpactpurge,"   Cell \"%s\" %c CONTINUE_Entry_STROBELO {\n   Data 0;\n   Drive {\n      EntryState DriveOn;\n      }\n   Compare {\n      EntryState CompareOpenLow;\n      }\n   }\n", PINF,AM_continueLO);
		fprintf(fpactpurge,"   Cell \"%s\" %c CONTINUE_Entry_STROBEHI {\n   Data 1;\n   Drive {\n      EntryState DriveOn;\n      }\n   Compare {\n      EntryState CompareOpenHigh;\n      }\n   }\n", PINF,AM_continue);
		fprintf(fpactpurge,"   Cell \"%s\" %c DUMMY_PUSHFWD_CYCLE_NOACTION {\n   Data 6;\n   Drive {\n      EntryState DriveOn;\n      }\n   }\n", PINF,AM_DONOTHINGPAD);
		for (i=0;i<pbc;i++) {
			fprintf(fpactpurge,"   Cell \"%s\" %c FILL%02d_%c { Inherit %s.DUMMY_PUSHFWD_CYCLE_NOACTION;}\n",
				PINF,aliaslist[i].alias1,i,aliaslist[i].oldal1,PBCOMMON);
			fprintf(fpactpurge,"   Cell \"%s\" %c FILL%02d_%c { Inherit %s.DUMMY_PUSHFWD_CYCLE_NOACTION;}\n",
				PINF,aliaslist[i].alias2,i,aliaslist[i].oldal2,PBCOMMON);
			}
		fprintf(fpactpurge,"}\n");
	}
	if (NOPUSHCYC==1 && EVX2) {
		fprintf(fpactpurge,"//This file was run with EVX2 mode disabled (GCT_GEN_MOD used: \'-n\').\n");
		fprintf(fpactpurge,"//Any multicycle window strobes might not be handled correctly!\n");
		fprintf(fpactpurge,"//This means that failing WINDOW strobes might not flag failures correctly.\n");
		fprintf(fpactpurge,"//This is the responsibility of the individual engineer to see this is properly handled.\n");
		fprintf(fpinherit,"//This file was run with EVX2 mode disabled (GCT_GEN_MOD used: \'-n\').\n");
		fprintf(fpinherit,"//Any multicycle window strobes might not be handled correctly!\n");
		fprintf(fpinherit,"//This means that failing WINDOW strobes might not flag failures correctly.\n");
		fprintf(fpinherit,"//This is the responsibility of the individual engineer to see this is properly handled.\n");
		}
	fclose(fpact);
	fclose(fpactpurge);
	free(cycpb);
	free(aliaslist);
	free(pblist);
	return (0);
}
