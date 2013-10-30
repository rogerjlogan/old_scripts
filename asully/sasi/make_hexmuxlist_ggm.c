/* make_hexmuxlist() {} */

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


int make_hexmuxlist(FILE * fp_mod_file, char *muxpin, int maxcyclen)
{
	char hexproc[NUMPINS + 1], fieldset[NUMPINS + 1];
	int i, j, k, l, vmset, find, pin, list, pos, maxfields, found;
	char pinheader[PINSIZE][NUMPINS];
	int sizehead;
	find = 1;
	maxfields = 0;
	pos = 0;
	for (i = 0; i < maxvmsets; i++) {
		if (vmsets[i].scan == VMSPARALLEL && vmsets[i].field > maxfields) {
//         fprintf(stdout,"MF%s[%d][%s][%d]\n",vmsets[i].name,vmsets[i].field,vmsets[i].pinlist,vmsets[i].type);
			maxfields = vmsets[i].field;
		}
	}
	for (pin = 0; pin < maxpin; pin++)
		hexproc[pin] = fieldset[pin] = '.';
	for (find = 1; find <= maxfields; find++) {
		for (vmset = 0; vmset < maxvmsets; vmset++) {
			if (vmsets[vmset].field == find) {
//         fprintf(stdout,"FIELD[%2d]%s\n",vmset,vmsets[vmset].pinlist);
				found = 0;
				for (list = 0; list < maxlists; list++)
					if (0 ==
						strcmp(vmsets[vmset].pinlist,
							   pinlist[list].pinlistname)) {
						found = 1;
						for (pin = 0; pin < maxpin; pin++)
							if (pinlist[list].pinlists[pin] == '*') {
								hexproc[pin] =
									(vmsets[vmset].type ==
									 VMSHEX) ? 'H' : 'B';
								fieldset[pin] = vmset + 'A';
								pos++;
							}
						break;
					}			/* list */
				if (!found) {	/* not a group */
					for (pin = 0; pin < maxpin; pin++) {
						if (0 == strcmp(vmsets[vmset].pinlist, PIN[pin])) {
							hexproc[pin] =
								(vmsets[vmset].type == VMSHEX) ? 'H' : 'B';
							fieldset[pin] = vmset + 'A';
							pos++;
							break;
						}
					}
				}
				break;
			}
		}
	}
	hexproc[maxpin] = fieldset[maxpin] = '\0';
	fprintf(fp_mod_file, "#pin descriptors:\n");
	/* the following prints use the width specifier as a parameter */
	for (sizehead = pin = 0; pin < maxpin; pin++)
		if (strlen(PIN[pin]) > sizehead)
			sizehead = strlen(PIN[pin]);
	if (sizehead < PINSIZE) {
		for (pin = 0; pin < maxpin; pin++) {
			for (i = 0; i < strlen(PIN[pin]); i++)
				pinheader[i][pin] = PIN[pin][i];
			for (; i < sizehead; i++)
				pinheader[i][pin] = ' ';
		}
		for (pin = 0; pin < sizehead; pin++) {
			pinheader[pin][maxpin] = '\0';
		}
// No mux pad, see code below....
//      for (k=pin=0;pin<maxpin;pin++) {
//         if (muxpin[pin]=='M') {
//            for (l=maxpin+k;l>pin+k;l--) for (j=0;j<sizehead;j++) pinheader[j][l]=pinheader[j][l-1];
//            k++;
//            }
//         }
		for (j = 0; j < sizehead; j++)
			fprintf(fp_mod_file, "# %*s[%s][%s]\n", -maxcyclen, "pins:",
					pinheader[j], pinheader[j]);
	}
	fprintf(fp_mod_file, "#Note:muxpins marked in MUXSECONDARYPINS but are left off the other vector data...\n");
	fprintf(fp_mod_file, "#AUTO_PRE_PROC will correctly deal with them and VCP/VCS will expand cycle info above.\n");
	fprintf(fp_mod_file, "%*s  [%s]\n", -maxcyclen, "MUXSECONDARYPINS", muxpin);
	fprintf(fp_mod_file, "%*s  [%s]\n", -maxcyclen, "HEXPROC", hexproc);
	fprintf(fp_mod_file, "%*s  [%s]\n", -maxcyclen, "FIELDS", fieldset);
	for (list = 0; list < maxlists; list++) {
		fprintf(fp_mod_file, "%*s  [%s]", -maxcyclen, "PINGROUP", pinlist[list].pinlists);
		fprintf(fp_mod_file, "(*%s*)", pinlist[list].pinlistname);
		fprintf(fp_mod_file, "{%s}\n", pinlist[list].groups);
	}
	for (sizehead = pin = 0; pin < maxpin; pin++)
		if (strlen(PIN[pin]) > sizehead) sizehead = strlen(PIN[pin]);
	if (sizehead < PINSIZE) {
		for (pin = 0; pin < maxpin; pin++) {
			for (i = 0; i < strlen(PIN[pin]); i++) pinheader[i][pin] = PIN[pin][i];
			for (; i < sizehead; i++) pinheader[i][pin] = ' ';
		}
		for (pin = 0; pin < sizehead; pin++) {
			pinheader[pin][maxpin] = '\0';
		}
		for (k = pin = 0; pin < maxpin; pin++) {
			if (muxpin[pin] == 'M') {
				for (l = maxpin + k; l > pin + k; l--)
					for (j = 0; j < sizehead; j++) pinheader[j][l] = pinheader[j][l - 1];
				k++;
			}
		}
		for (j = 0; j < sizehead; j++)
			fprintf(fp_mod_file, "//%s\n", pinheader[j]);
	}
	return (0);
}
