/* gct_gen_mod_global.c global variable definitions */

#include "ggm_includes.h"

char EO[MAXORIGINS][ORIGINSIZE+1];
int EOCNT;

ACWAVES *acwaves;
ACWAVES *origins;
int orgcnt;
CELL_INFO *cellinfo;
int cellcnt;
ACTABLENAMES *actablenames;
int maxactablenames;
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
char wavetypes[][FMTLEN]={"WaveSetClk","WaveSetContinue","WaveSetDoubleClk","WaveSetNR","WaveSetOff","WaveSetRTO","WaveSetRTZ","WaveSetSBC","WaveSetStrobe","WaveSetStrobeZ","WaveSetEdgeStrobe","WaveSetEdgeStrobeZ","WaveSetDelayClk","WaveSetDelayDoubleClk","WaveSetDelayNR","WaveSetDelayOff","WaveSetDelayRTO","WaveSetDelayRTZ","WaveSetDelaySBC","WaveSetDelayStrobe","WaveSetDelayStrobeZ","WaveSetDelayEdgeStrobe","WaveSetDelayEdgeStrobeZ","EdgeSet","EdgeSetDelayData"};
//char wavedelaytypes[sizeof(wavetypes)/FMTLEN][FMTLEN];/* autogenerate from above  ... */
char edgetypes[][FMTLEN]={"DriveHigh","DriveLow","DriveData","DriveComplement","DriveOff","NullEdge","StrobeHigh","StrobeLow","StrobeData","StrobeComplement","StrobeOff","StrobeOffData","StrobeOffComplement","StrobeOffHigh","StrobeOffLow","StrobeZ","StrobeLatch","EdgeStrobeData","EdgeStrobeComplement","EdgeStrobeLow","EdgeStrobeHigh","EdgeStrobeZ"};
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
char GCTNAME[GCTSIZE];
int SIZE_WAVETYPES=sizeof(wavetypes);
int SIZE_EDGETYPE=sizeof(edgetypes);

char wavetypefull[sizeof(wavetypes)];
char edgetypefull[sizeof(edgetypes)];

char PIN[NUMPINS][PINSIZE];
int maxpin,groupcount,maxlists=0;
PINLIST *pinlist;
