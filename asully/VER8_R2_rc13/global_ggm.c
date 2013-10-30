/* gct_gen_mod_global.c global variable definitions */
/* Feb 00 Anthony Sully, LTX Corp. Created for C6202/3 after suffering through C6201 and
                                   spec. timing with alternate dsets. This file processes
                                   the polaris cycletbl.p file with minor edits to figure
                                   out what the dset selects are and creates a simplified
                                   version of this that is easy and quick to read for each
                                   pattern translation. */
/* Sept. 02 Anthony Sully, LTX Corp. Modified for microcontroller translations added smarts
                                   so it can also determine the scan pins. At the moment
                                   only one pair is allowed. */
/* 09/28/02 Anthony Sully, LTX Corp. Fixed a bug in the pin matching routine where it was
                                   matching a pin with a superset pinname. i.e. TMS was
                                   found as TMS2. This happened if the superset pin came
                                   first. Now lengths are also required to match. Also,
                                   added code to ignore non-alphanumeric lines.*/

/* 11/02/02 Anthony Sully, LTX Corp. Fixed compile script and includes so date can be brought in with
                                     gcc or cc */

/* 06/27/08 Anthony Sully, LTX Corp. Add support for reading device.p for pinlists, muxmode
                                     and hex pattern mode support as well as 
                                     VectorMapSet and VectorMapSetCycle */
/* 07/30/08-08/08/08 Anthony Sully, LTX Corp. Modified the waveform identification processing.
                                     We now read actable.p, crunch it, and try and find the
                                     DSET0,DSET1 wfm names in actable. From that we try and
                                     determine the REAL format, instead of guessing from the
                                     name. Also added duplicate pinlist checking warning. 
                                     Added new feature which attempts to generate a waveformtable
                                     file. The flaw with this is the conditional statements. A
                                     pure actable.p file would work perfectly. If there are lots
                                     of conditionals then we get too many waveform cells.
                                     Pattern characters are now determined from the waveform
                                     assignments since we generate both here.
                                     updated rev. to gct_gen_mod5.c (results create a .mod5 file) */
/* 12/12/08 - 12/15/08 Anthony Sully LTXCredence. Major revamp. lots of file buffering to memory now
                                     going on. Needed to support several new features. First was to
                                     optimize the number of cells generated. categories/devices/temps/enums
                                     are now tracked. actable now needs to be marked with START/STOP
                                     boundaries so sections can be tracked. This helps origin matching
                                     as well. Implemented an optimization technique where if the cell
                                     information matches, the cells (in the same section) are compressed
                                     together. Also, a post-process step will modify the original waveforms
                                     to deal with pending open windows over multiple cycles and also
                                     the close before open window problem. (not quite there yet...)
                                     Also, modified how scan data is stored so we can support multiple
                                     scan pins. mod file will be mod6. */

#include "includes_ggm.h"

CYCSETMD *cycsets;
int maxcycset;
CYCTBL *cyctbl;
int maxtbl;
VMS vmsets[MAXVMS];
int maxvmsets, VMparallel, VMfields;

char EO[MAXORIGINS][ORIGINSIZE + 1];
int EOCNT;

ACWAVES *acwaves;
ACWAVES *origins;
int orgcnt;
CELL_INFO *cellinfo;
int cellcnt, worstcasecellcnt = 0;
PARAM_INFO *paraminfo;
int paramcnt;
ACTABLENAMES *actablenames;
int maxactablenames;
STARTSTOP startstop[STARTSTOPCNTPRE];
int maxstartstop;
char alphabet[26 + 26 + 10 + 1] =
	{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" };;
char ENUMS[MAXENUMS][ENUMLEN + 1];
int maxenums;

// this is for strcat to the cyclebuff....
char *SCATcycle;
char *cyclebuff;
// this is for remove_dupe_cells() paired with SCATcycle
char *REMOVEDUPE;
/* polaris wave explanations: */
/* waveoff turns off strobe and driver */
/* wavesetcontinue no edges generated */
/* strobes are windows unless specified with 'edge' */
/* wavesetdelayNNN allows programming outside the cycle boundaries,
    last parameters indicate the number of cycles to push each edge out... i.e. '+period*N' */
/* there is no wavesetdelaycontinue */
//int  wavedrive[]        ={           0,                0,                 0,          1,           0,           1,          1,            1,              0,               0,                  0,                   0,        0,                 0};
//int  waveclock[]        ={           1,                0,                 1,          0,           0,           0,          0,            0,              0,               0,                  0,                   0,        0,                 0};
//int  wavestrobe[]       ={           0,                0,                 0,          0,           0,           0,          0,            0,              1,               0,                  1,                   0,        0,                 0};
//int  wavefloat[]        ={           0,                0,                 0,          0,           0,           0,          0,            0,              0,               1,                  0,                   1,        0,                 0};
//int  wavecontinue[]     ={           0,                1,                 0,          0,           0,           0,          0,            0,              0,               0,                  0,                   0,        0,                 0};
//int  waveoff[]          ={           0,                0,                 0,          0,           1,           0,          0,            0,              0,               0,                  0,                   0,        0,                 0};
char wavetypes[][FMTLEN] =
	{ "WaveSetClk", "WaveSetContinue", "WaveSetDoubleClk", "WaveSetNR",
"WaveSetOff", "WaveSetRTO", "WaveSetRTZ", "WaveSetSBC", "WaveSetStrobe", "WaveSetStrobeZ",
"WaveSetEdgeStrobe", "WaveSetEdgeStrobeZ", "WaveSetDelayClk", "WaveSetDelayDoubleClk",
"WaveSetDelayNR", "WaveSetDelayOff", "WaveSetDelayRTO", "WaveSetDelayRTZ",
"WaveSetDelaySBC", "WaveSetDelayStrobe", "WaveSetDelayStrobeZ", "WaveSetDelayEdgeStrobe",
"WaveSetDelayEdgeStrobeZ", "EdgeSet", "EdgeSetDelayData" };
//char wavedelaytypes[sizeof(wavetypes)/FMTLEN][FMTLEN];/* autogenerate from above  ... */
char edgetypes[][FMTLEN] =
	{ "DriveHigh", "DriveLow", "DriveData", "DriveComplement", "DriveOff",
"NullEdge", "StrobeHigh", "StrobeLow", "StrobeData", "StrobeComplement", "StrobeOff",
"StrobeOffData", "StrobeOffComplement", "StrobeOffHigh", "StrobeOffLow", "StrobeZ",
"StrobeLatch", "EdgeStrobeData", "EdgeStrobeComplement", "EdgeStrobeLow",
"EdgeStrobeHigh", "EdgeStrobeZ" };
//int  edgedrive[]        ={          1,         1,          1,                1,         0,         0,          0,           0,           0,                 0,          0,              0,                    0,              0,             0,        0,            0,               0,                     0,              0,               0,           0};
//int  driveoff[]         ={          0,         0,          0,                0,         0,         0,          0,           0,           0,                 0,          0,              0,                    0,              0,             0,        0,            1,               0,                     0,              0,               0,           0};
//int  edgestrobe[]       ={          0,         0,          0,                0,         0,         0,          1,           1,           1,                 1,          0,              0,                    0,              0,             0,        0,            0,               1,                     1,              1,               1,           0};
//int  edgefloat[]        ={          0,         0,          0,                0,         0,         0,          0,           0,           0,                 0,          0,              0,                    0,              0,             0,        1,            0,               0,                     0,              0,               0,           1};
//int  strobeoff[]        ={          0,         0,          0,                0,         1,         0,          0,           0,           0,                 0,          1,              1,                    1,              1,             1,        0,            1,               0,                     0,              0,               0,           0};
/* edge definitions: */
/* driver off only turns drive off doesn't affect strobe */
/* Null edge is empty */
/* again, strobes are windows unless specified with edge */
/* strobe off closes a window strobe */
/* strobe Z doesn't care about vector data */
/* EdgeSetDelayData specifies different times and voltages for the vector data (i.e. high at N low at M) */
/* EG0: DriveHigh,DriveLow,DriveOff */
/* EG1: DriveHigh,DriveLow,StrobeHigh,StrobeLow,StrobeZ */
/* EG2: DriveHigh,DriveLow,StrobeOff */
/* EdgeSet statements modify timing only of previous wavset statement */
int SIZE_WAVETYPES = sizeof(wavetypes);
int SIZE_EDGETYPE = sizeof(edgetypes);

char wavetypefull[sizeof(wavetypes)];
char edgetypefull[sizeof(edgetypes)];

char PIN[NUMPINS][PINSIZE];
char DEVPIN[NUMPINS][PINSIZE];
int PIN2DEV[NUMPINS], DEV2PIN[NUMPINS];
int maxdevpin, maxpin, groupcount, maxlists = 0;
PINLIST *pinlist;
FILE *fperrors, *fpstatus, *fppreopt;

int WARNING;
char tperiod[50];

int LASTI;
int ACTABLE, ACDATA;
int G_maxdev, G_maxtmp, G_maxtst, G_maxrem;
char enumstr[50][100];
int EVX2 = 0, PBSTROBE = 0, PBCLOSE = 0, NOPUSHCYC = 0, NOMUX = 0, MUXFLAG = 0;
