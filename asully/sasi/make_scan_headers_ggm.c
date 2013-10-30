/* make_scan_headers() {} */

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

int make_scan_headers(FILE * fp_mod_file, char *muxpin)
{
	int vmset1, vmset2, vmcount, set, pin, muxcount;
	/* first match them up */
	vmcount = 0;
	for (vmset1 = 0; vmset1 < maxvmsets; vmset1++) {
		vmsets[vmset1].scanset = 0;
		vmsets[vmset1].scanpin = -1;
	}
	for (vmset1 = 0; vmset1 < maxvmsets; vmset1++) {	/* this includes the end one because it must be initialized also */
		if (vmsets[vmset1].scan == VMSPARALLEL
			|| vmsets[vmset1].scanset != 0)
			continue;
		vmcount++;
		vmsets[vmset1].scanset = vmcount;	/* preset the first occurance */
		for (vmset2 = vmset1 + 1; vmset2 < maxvmsets; vmset2++) {	/* now find any that match */
			if (vmsets[vmset2].scan == VMSPARALLEL
				|| vmsets[vmset2].scanset != 0)
				continue;
//         fprintf(stdout,"comp[%s]to[%s]\n",vmsets[vmset1].name,vmsets[vmset2].name);
			if (strcmp(vmsets[vmset1].name, vmsets[vmset2].name) == 0) {
				vmsets[vmset2].scanset = vmcount;
			}
		}
	}
	for (set = 1; set <= vmcount; set++) {	/* starts with one and ends with the last one */
		for (vmset1 = 0; vmset1 < maxvmsets; vmset1++) {
			if (vmsets[vmset1].scan == VMSPARALLEL
				|| vmsets[vmset1].scanset != set
				|| vmsets[vmset1].scanpin != -1)
				continue;
			muxcount = 0;
			for (pin = 0; pin < maxpin; pin++) {
				if (muxpin[pin] == 'M')
					muxcount++;
				if (strcmp(vmsets[vmset1].pinlist, PIN[pin]) == 0)
					vmsets[vmset1].scanpin = (pin + muxcount);
			}
			fprintf(fp_mod_file, "%c%s:%s[%d]", SCANLINE,
					vmsets[vmset1].name, vmsets[vmset1].pinlist,
					vmsets[vmset1].scanpin);
			for (vmset2 = vmset1 + 1; vmset2 < maxvmsets; vmset2++) {
				if (vmsets[vmset2].scanset == vmsets[vmset1].scanset) {
					muxcount = 0;
					for (pin = 0; pin < maxpin; pin++) {
						if (muxpin[pin] == 'M')
							muxcount++;
						if (strcmp(vmsets[vmset2].pinlist, PIN[pin]) == 0)
							vmsets[vmset2].scanpin = (pin + muxcount);
					}
					fprintf(fp_mod_file, ",%s[%d]", vmsets[vmset2].pinlist,
							vmsets[vmset2].scanpin);
				}
			}
			fputc('\n', fp_mod_file);
		}
	}
	return (0);
}
