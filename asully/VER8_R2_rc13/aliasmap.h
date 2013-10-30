#define MODVER ".mod8"
#define SCANLINE '?'
/* drvdata,drvhi,drvlo,drvcomp */
#define FC_DRIVEHI 'H'
#define FC_DRIVELO 'L'
#define FC_DRIVEDATA 'D'		/* used in mod file */
#define FC_DRIVECOMP 'd'
/* drvoff */
#define FC_DRIVEOFF 'X'			/* used in mod file */
#define FC_MASK 'x' /* used in priorstate */
/* estbdata,estbcomp,estblo,estbhi */
#define FC_EDGEHI '1'
#define FC_EDGELO '0'
#define FC_EDGEDATA 'E'			/* used in mod file */
#define FC_EDGECOMP 'e'
/* estbZ */
#define FC_EDGEFLOAT 'F'		/* used in mod file */
/* latch */
#define FC_LATCH 'Q'			/* this is for store edge */
/* stbdata,stbcomp,stblo,stbhi */
#define FC_WINDOWHI '^'
#define FC_WINDOWLO 'v'
#define FC_WINDOWDATA 'W'		/* used in mod file */
#define FC_WINDOWCOMP 'w'
#define FC_WINDOWOPEN 'O'		/* used in mod file */
/* stbZ */
#define FC_WINDOWFLOAT 'f'		/* used in mod file */
#define FC_WINDOWOPENZ 'Z'		/* used in mod file */
/* stboff,stboffdata,stboffcomp,stbofflo,stboffhi */
#define FC_STROBEOFF 'k'		/* i.e. kill window */
#define FC_DRVSTRBOFF 'K'		/* wavesetoff can do both */
#define FC_NULLEDGE 'n'			/* used in mod file */
#define FC_NULLEDGE_DRV 'N'			/* used in mod file */
/* mux clock data different, ChanSecond */
#define FC_MUXCLOCK 'C'
/* you need parentheses around the calculation in the next line, otherwise 47-47=-2! */
#define FC_DUMMY (FC_EDGELO-1)	/* this is to offset the earliest alphanum char. This is '/' */
#define FC_ASCII '_'
#define FC_NOMUX '~'
#define FC_BAD '?'				/* used if nothing else is set, ideally this should never happen */
/* stdwfms */
/* SBC HLHn LHLn */
/* NR  Hnnn Lnnn */
/* RTO HHnn LHnn */
/* RTZ HLnn LLnn */
/* STB XWkn XWkn */
/* ESTB X1nn X0nn */
/* STBZ Xfkn xfkn */
/* ESTBZ XFnn XFnn */
/* CLK HLnn LLnn Data-independent, Invert: LHnn/HHnn */
/* DCLK HLHL LLLL Data-independent Invert: LHLH/HHHH */
/* OFF Xknn Xknn */
/* CONT nnnn nnnn */

/* basic definitions:*/
#define AM_scanin 'D'			/* 'S' */
#define AM_scanout 'S'			/* 'S' */
#define AM_cpmdpm 'd'			/* 'S' */
#define AM_continue '-'			/* '*' cellname use 's' */
#define AM_continueLO '_'		/* we're now distinguishing drive continues from strobe continues */
#define AM_continueDRV '>'	/* we're now distinguishing drive continues from strobe continues */
#define AM_driveHID1 'H'		/* '*' */
#define AM_driveLOD1 'L'		/* '*' */
#define AM_driveHID0 'h'		/* '*' */
#define AM_driveLOD0 'l'		/* '*' */
#define AM_edgestbLOD0 '0'		/* '*' */
#define AM_edgestbHID0 '1'		/* '*' */
#define AM_edgestbLOD1 '2'		/* '*' */
#define AM_edgestbHID1 '3'		/* '*' */
#define AM_maskD0 'x'			/* '*' */
#define AM_maskHID0 'X'			/* '*' */
/* decided against ./, because they don't work well in strings */
#define AM_maskD1 'm'       /* '*' */	/* was x */
#define AM_maskHID1 'M'     /* '*' */	/* , */
/* these are valid windowopen with proper windowclose */
/* we're changing this so the pattern will match for either */
/*    but the format codes above will specify the type and keep it different */
#define AM_windowLOD0 '0'		/* '*' */
#define AM_windowHID0 '1'		/* '*' */
#define AM_windowLOD1 '2'		/* '*' */
#define AM_windowHID1 '3'		/* '*' */
#define AM_windowfloatD0 'F'  /* '*' */	/* assume DATA independent was t/T */
#define AM_windowfloatD1 'f'  /* '*' */	/* assume DATA independent was t/T */
#define AM_edgefloatD0 'F'    /* '*' */	/* was f/F */
#define AM_edgefloatD1 'f'    /* '*' */	/* was f/F */
/* assume we need drive off HI/LO */
/* decided against ./, because they don't work well in strings,swapped again y/z  */
#define AM_driveoffLOD0 'y'		/* '*' */
#define AM_driveoffHID0 'z'		/* '*' */
#define AM_driveoffLOD1 'Y'		/* '*' */
#define AM_driveoffHID1 'Z'		/* '*' */
/* mux drive clock alternating data, assume DSET independence.... */
#define AM_driveoffLOHI 'c'		/* '*' */
#define AM_driveoffHILO 'C'		/* '*' */
/* multicycle waveforms openNOclose,closeopen,strobeoff,continuestrobe: */
/* mark all these as 'o' */
/* decided against ./, because they don't work well in strings */
/* e/k and E/K devolve to z/Z y/Y if masked... !!!or if prior wasn't strobe!!! */
#define AM_strobeoffLOD0 'e'
#define AM_strobeoffHID0 'k'
#define AM_strobeoffLOD1 'E'
#define AM_strobeoffHID1 'K'
#define AM_strobefloatoffD0 'g'
#define AM_strobefloatoffD1 'G'
#define AM_NOMUX ' '

/* following are arbitrary (push back close data): in EVX2 mode */

#define AM_DONOTHINGPAD '.'

#define AM_close1LO '4'
#define AM_close1HI '5'
#define AM_close2LO '6'
#define AM_close2HI '7'
#define AM_close3LO '8'
#define AM_close3HI '9'
#define AM_close4LO 'a'
#define AM_close4HI 'A'
#define AM_close5LO 'b'
#define AM_close5HI 'B'
#define AM_close6LO 'i'
#define AM_close6HI 'I'
#define AM_close7LO 'j'
#define AM_close7HI 'J'
#define AM_close8LO 'o'
#define AM_close8HI 'O'
#define AM_close9LO 'p'
#define AM_close9HI 'P'
#define AM_close10LO 'q'
#define AM_close10HI 'Q'
#define AM_close11LO 't'
#define AM_close11HI 'T'
#define AM_close12LO 'u'
#define AM_close12HI 'U'

#define AM_MISC1 'v'
#define AM_MISC2 'V'
#define AM_MISC3 'w'
#define AM_MISC4 'W'

#define AM_BOGUS '?'
/* the 'R' are reserved for close waveforms, * is standard,  D is cpmdpm, S is scan, > DriveCont */
#define AM_ALLTS "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpP.>rRsStTuUvVwWxXyYzZ-_"	/* 63 chars */
#define AM_allts "****..........**DS********....******......**...S........********"	/* 63 chars */
