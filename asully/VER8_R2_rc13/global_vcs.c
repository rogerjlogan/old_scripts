#include <stdio.h>
#include "include_vcs.h"

char G_HOLD_VECTOR[NUMPINS];
char G_DPM_VECTOR[NUMPINS];
char G_SCANHOLD[NUMPINS];

int G_QUIET = 1, NOMUX = 0;
FILE *fperrors, *fpstatus, *fpsignalheaders, *fppatref;
char G_infile1[FILENAMELEN];
long G_readlinenum = 0;
long G_cyclecount = 0, G_vectorcount = 0;
char G_progstr[MEMOSTRLEN], G_datestr[MEMOSTRLEN], G_timestr[MEMOSTRLEN];
char G_compilestr[MEMOSTRLEN];	/* concaternated strings */
char G_username[MEMOSTRLEN], G_hostname[MEMOSTRLEN], G_pwd[MEMOSTRLEN];
int G_SCANINPIN = 0;			/* TDI */
int G_SCANOUTPIN = 0;			/* TDO */
char G_NORMALSGHDR[MAXSIGHDRLEN];
int G_MOD2_SIZE = 0;
int G_pinheadcount = 0;
char G_pinhead[SCANPINNUM][NUMPINS];
char G_GCTMODNAME[MAXMODGCT][MAXGCTLEN];
int G_GCTMODUSED[MAXMODGCT];
char G_VECTD0[MAXMODGCT][MAXPINS + 1], G_VECTD1[MAXMODGCT][MAXPINS + 1];
int G_maxgctSET = 0;

SCAN_INFO G_scandata[MAXSCANHDRS];
int G_scanhdrs = 0;
char priorstate[MAXPINS+1];

/* May 99 Anthony Sully, LTX Corp. Created original file for C6201, lots of hardcoded stuff!!! */
/* Feb 00 Anthony Sully, LTX Corp. Modified for C6202/3, still lots of hardcoded stuff!!! */
/* Sept. 02 Anthony Sully, LTX Corp. Modified for microcontroller translations (Venus first)
                                     started work removing hardcoded stuff. Added requirement
                                     for the gct_gen_mod.c output which now helps find the
                                     appropriate scan pins. At the moment only two are allowed.
                                     Waveformtables are currently ignored.*/
/* 09/28/02 Anthony Sully, LTX Corp. Changed cpm scan drive and strobe characters to use defines
                                     as opposed to hard coding them. Changed strobe character to
                                     match Dale's choice of 's' instead of 'C' (conflicting with
                                     clock wfms anyway).
                                     Begin adding wfm processing at the moment we will assume
                                     that the dset for scan hold cycles should be 1. */
/* 09/29/02 Anthony Sully, LTX Corp. Implemented code to properly look up the waveformtable
                                     information for both parallel vectors and scan cpm hold
                                     vectors. Modified Alias selections as well. For the scan
                                     hold I am assuming that the Dset=1 because that seemed
                                     to make the most sense, in most cases it doesn't matter
                                     because they are the same anyway in ScanCycleX. 
                                     Also, removed default waveformtable and default signal
                                     header as we are being explicit on every vector anyway.
                                     One minor issue remains in that the first cpm vector is
                                     all AM_continue. This may need to be driven to a set state,
                                     it also uses the pattern GCT as opposed to HOLD_CYCLE.
                                     Maybe keep the first dpm vector and stick it in CPM??? */

/* 10/27/02 Anthony Sully, LTX Corp. Fixed counts in repeats in CPM, it was off by one. */

/* 11/02/02 Anthony Sully, LTX Corp. Fixed compile script and includes so date can be brought in with
                                     gcc or cc */

/* 11/08/02 Anthony Sully, LTX Corp. Added pseudo-support for ScanSetUncoupled. The Polaris definition
                                     of scansetuncoupled defines that the scan vectors be sourced separately.
                                     What I have currently implemented will grab the information correctly
                                     but will source the vectors together. This is ok for the cases I have
                                     seen so far because what they are really doing is just sourcing one
                                     of the scanpins. By using the prefill/postfill the unused scanpin
                                     will be left blank and thus gets the prefill/postfill character. It
                                     totally ignores the other scanholdcycles. This implementation is not
                                     really correct but meets the current need. Fixing this would involve
                                     adding multiple hold vectors and re-doing the CPM pattern generation
                                     to keep track of which pin is being sourced when. This should be
                                     implemented if/when support for more than two scan pins is needed.
                                     Due to repeat loops in scan patterns pre_proc_dpm is now needed. */

/* 11/09/02 Anthony Sully, LTX Corp. Added support for repeat forever as last line of pattern if there are
                                     enough vectors to support it. Repeat forevers in anything but the last
                                     vector are not supported yet. Also, the pattern will get the wrong
                                     repeat count for parallel cpm-calling-dpm if there are not at least
                                     3 dpm vectors being called (1 for CPM calling DPM, 1 for COND CONT,
                                     and 1 for CJMP .) . It should still translate it just not compile
                                     and the fix is left to the user, no warnings are issued. 
                                     Added vector number, parallel number, and cyclenumber to dpm comments.
                                     Added vector number and cyclenumber to cpm comments. Added dummy
                                     vector to end of dpm for label position correctness. */

/* 01/24/03 Anthony Sully, LTX Corp. Added FLAG(CONT ON) to microinstructions if repeat forever found */

/* 03/29/03 Anthony Sully, LTX Corp. Added GNU GPL info. Added ERROR CLASSES:
                                     FATAL_ERRORS -- cause immediate exit of program (usually file problems)
                                     BAD_ERRORS -- fatal errors that could produce corrupted output files
                                     NON_FATAL_ERRORS -- errors that generate files with useful output
                                     FYI -- informational warnings. Added username, hostname, and pwd to
                                     pattern header. Changed date get to 'C' functions instead of unix date.
                                     Turned off gzipping of *_cpm.evo pattern so the CPM_SCAN_OPT can be
                                     run directly. */

/* 04/04/03 Anthony Sully, LTX Corp. Added support for repeat forever loops as passed in from pre_proc_dpm.
                                     This only supports one repeat forever but does support a begin-end loop
                                     of multiple vectors. The repeat forever vectors are currently written
                                     into the dpm pattern as comments and to the cpm in the appropriate
                                     place. The cpm_scan_opt probably won't optimize this properly. */

/* 09/24/03 Anthony Sully, LTX Corp. Added support for user defined signal header (in cycletbl_mod.mod2),
                                     gct_gen_mod2. This is needed because some devices may have patterns
                                     with different widths. Added code to check that the cycletbl file has
                                     the same number of pins as the polaris pattern, exit if not the same.
                                     Same update to vector_convert_polaris. Added checks for any strstr or
                                     strchr statements to make sure they do something on NULL. */
/* 02/25/04 Anthony Sully, LTX Corp. Updated for scan auto gen (with -a). Modified how files are renamed
                                     and removed to use 'C' functions instead of system() */

/* 02/23/05 Anthony Sully, LTX Corp. Add support for repeat */

/* 11/20/05 Anthony Sully, LTX Corp. Fixed vector identification line so it uses the previously read GCTs_WFR
                                     instead of generically just GCT. This was an issue because of a DSP wftr
                                     which was PTM_2 and thus had no GCT in its name. Also fixed the extra
                                     carriage return after the signalheader. This was coming from the carriage
                                     return in the cycletbl_mod.mod2 file. Corrected the gzipping code so it
                                     would gzip autogen files as well. Added fpstatus file output instead of
                                     stdout. Created additional file for scan to list signalheaders and create
                                     them. updated to *_scanautogen3.c*/

/* 04/13/06 Anthony Sully, LTX Corp. Increased the allowable scan count 'MAXSCANCNT' from 7000 to 14000 */
/* 08/29/06 Anthony Sully, LTX Corp. Problem identifying SCANPINNUMBERS(SCANPININ/OUT) */
/* 06/29/08 Anthony Sully, LTX Corp. Added environment read of DEBUG_PROC */
