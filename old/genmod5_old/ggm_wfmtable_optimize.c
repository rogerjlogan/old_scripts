/* gct_gen_mod_wfmtable_optimize.c */
/* wfmtable_optimize(){} */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ggm_includes.h"

/* DONE:prescan through the file search for 'ACTTable': TIparametricACTable, and record any names found */
/*   TIACTableSet( TIparametricACTable ); */
/* DONE:create a pointer table to each cell definition */
/* it should contain: */
/* waveformtable,original actableline,cellname, pin, multidefnum, & four edge formats */
/* now run through each of the multidefs and see if the formats match */
/* if they match throw each of the timing specs into a spec table and replace with a spec variable */
/* need at least 60000 entries for 320C!!! */
/**/
/* Once optimized, then run through and see if any cellnames can merge pin groups */

int wfmtable_optimize(){
   /* stage1: see if it references the same actable line; if it does then we can compress... pins...*/
   return(0);
   }
