(***********************************************************************)
(***								     ***)
(***                     320X240 TEST PROGRAM 	                     ***)
(***			 --------------------   		     ***)
(***								     ***)
(***	 		File Name:  device.p			     ***)
(***								     ***)
(***   								     ***)
(***   Revision History:					     ***)
(***    A0   RS     01/01/97    First cut @ TMX320F240 PG1.0         ***)
(***    A1   DDD    04/01/97    First cut @ TMX320F240 PG1.1         ***)
(***    B0   RS     07/01/97    First cut @ TMX320F240 PG2.0 (probe) ***)
(***    B2   RS     10/01/97    First cut @ TMX320F240 PG2.0 (QA)    ***)
(***    B3   DDD    11/01/97    First cut @ TMP320F240 PG2.0         ***)
(***    C0   RS     03/25/98    First cut @ TMP320F240 PG3.1         ***)
(***	C2   RS	    05/15/98	First cut @ TMS320F240 PG3.2	     ***)
(***	C3   RS	    06/01/98	First cut @ TMX320C240 PG1.0	     ***)
(***				Added C240 code to F240 C2 Program   ***)
(***	C4   RS	    07/01/98	First cut @ TMX320C240 PG1.1	     ***)
(***********************************************************************)


procedure DeviceTableSet;

var
    devicetablename : String;

const
    MINV    = -4v;                 (* Minimum pin voltage allowed         *)
    MAXV    = 9v;                  (* Maximum pin voltage allowed         *)
    MINI    = -50ma;               (* Minimum pin current allowed         *)
    MAXI    = 50ma;                (* Maximum pin current allowed         *)
    MINVCC  = -4v;                 (* Minimum VCC voltage allowed         *)
    MAXVCC  = 11v;                 (* Maximum VCC voltage allowed         *)
    MINVCCI =-800000;              (* Minimum VCC current allowed in ua   *)
    MAXVCCI = 4000000;             (* Maximum VCC current allowed in ua   *)

   (* 19-Dec-96 begin add adc test                                        *)
    AMINV   = -10v;
    AMAXV   =  10v;
    AMINI   = -50ma;
    AMAXI   =  50ma;
   (* 19-Dec-96 end add adc test                                          *)

begin

case TIDeviceType of

F240_Probe, C240_Probe:
begin

    DeviceTableOpen;
    devicetablename:= 'ProbeDeviceTable';
    DeviceTableSetName(devicetablename);

(*              Pin           Pad    Tester    Pin  Minimum Maximum Minimum Maximum*)
(*              Name          Number Pin #     Type Voltage Voltage Current Current*)
   PinSetPP  	(WEN        ,   1 ,   79,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(RNW        ,   4 ,   78,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(BRN        ,   5 ,   77,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(STRBN      ,   6 ,   74,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D0         ,   9 ,   73,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D1         ,  10 ,   12,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D2         ,  11 ,   11,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D3         ,  12 ,   16,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP     (D4         ,  15 ,   13,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D5         ,  16 ,   10,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D6         ,  17 ,    9,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D7         ,  18 ,   68,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D8         ,  19 ,   67,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D9         ,  22 ,   72,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D10        ,  23 ,   71,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D11        ,  24 ,   70,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D12        ,  25 ,   69,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D13        ,  26 ,   66,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D14        ,  27 ,   65,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(D15        ,  28 ,  124,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(TCK        ,  30 ,  123,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(TDI        ,  31 ,    6,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(TRSTN      ,  32 ,    5,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(TMS        ,  33 ,    2,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(TDO        ,  34 ,    1,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(RSN        ,  35 ,  126,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(READY      ,  36 ,  125,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(MPMCN      ,  37 ,    8,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(EMU0       ,  38 ,    7,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(EMU1       ,  39 ,    4,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(NMIN       ,  40 ,    3,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(LVDOVRD    ,  41 ,  116,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PMTMODE    ,  42 ,  115,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(SCIRXD     ,  44 ,   60,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(SCITXD     ,  45 ,   59,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(SPISIMO    ,  46 ,   64,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(SPISOMI    ,  49 ,   63,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(SPICLK     ,  50 ,  118,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(SPISTE     ,  53 ,   62,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PDPINT     ,  54 ,   61,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(XINT1      ,  55 ,   58,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(XINT2      ,  56 ,   57,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(XINT3      ,  57 ,  108,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(OSCBYPN    ,  58 ,  107,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(XTAL2      ,  59 ,   52,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMuxPP 	(CLKIN      ,  60 ,   55,56,    I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCSOC     ,  65 ,  110,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMuxPP  (CLKOUT1    ,  66 ,   53,54,   IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(XF         ,  67 ,   50,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(BION       ,  68 ,   49,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(CAP1       ,  69,    44,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(CAP2       ,  70,    43,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(CAP3       ,  71 ,   48,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(CAP4       ,  72 ,   47,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN0     ,  74 ,   46,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN1     ,  75 ,   45,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN2     ,  76 ,   42,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN3     ,  77 ,   41,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN4     ,  78 ,  100,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN5     ,  79 ,   99,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN6     ,  80 ,   98,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN7     ,  81 ,   97,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN15    ,  82 ,   36,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN14    ,  83 ,   35,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN13    ,  84 ,   40,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN12    ,  85 ,   39,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP     (VREFHI     ,  87 ,   38,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN11    ,  90 ,   37,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN10    ,  91 ,   34,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN9     ,  92 ,   33,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ADCIN8     ,  93 ,   92,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PWM1       ,  96 ,   91,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PWM2       ,  97 ,   96,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PWM3       ,  98 ,   95,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PWM4       ,  99 ,   94,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PWM5       , 100 ,   93,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PWM6       , 101 ,   90,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PWM7       , 102 ,   89,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PWM8       , 103 ,   28,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PWM9       , 104 ,   27,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(T1PWM      , 107 ,   32,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(T2PWM      , 108 ,   31,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(T3PWM      , 109 ,   30,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(TMRDIR     , 110 ,   29,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(TMRCLK     , 111 ,   26,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A0         , 112 ,   25,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A1         , 113 ,   84,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A2         , 114 ,   83,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A3         , 116 ,   88,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A4         , 117 ,   87,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A5         , 118 ,   86,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A6         , 119 ,   85,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A7         , 120 ,   82,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A8         , 121 ,   81,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A9         , 124 ,   20,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A10        , 125 ,   19,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A11        , 126 ,   24,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A12        , 127 ,   23,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A13        , 128 ,   22,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A14        , 129 ,   21,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(A15        , 130 ,   18,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(DSN        , 131 ,   17,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(ISN        , 132 ,   76,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(PSN        , 133 ,   75,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetPP  	(RDN        , 134 ,   80,       O, MINV,   MAXV,   MINI,   MAXI );

  PinSetNoTDR(VREFHI);

     (*       Power Supply Pins are                                   *)
     (*       Ground Pins are                                         *)

  PinSetSupply(CVdd      ,   7 , Supply1 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(CVdd      ,  60 , Supply1 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );

  PinSetSupply(DVdd      ,   2 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  13 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  21 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  47 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  62 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  93 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      , 103 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      , 121 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );

  PinSetSupply(Vcca      ,  84 , Supply3 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );

  PinSetSupply(Vccp      ,  51 , Supply4 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );

{  PinSetSupply(VccD5B    ,  52 , Supply6 ,	 MINVCC, MAXVCC, MINVCCI, MAXVCCI );}

  PinSetSupply(TPAD      , 43   , Supply7 ,        MINVCC, MAXVCC, MINVCCI, MAXVCCI );

  PinSetSupply(DVss      ,   3 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  14 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  20 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  29 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  46 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  61 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  71 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  92 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      , 104 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      , 113 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      , 120 , Ground ,           0  ,    0  ,    0   ,    0);

  PinSetSupply(CVss      ,   8 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(CVss      ,  59 , Ground ,           0  ,    0  ,    0   ,    0);

  PinSetSupply(Vssa      ,  87 , Ground ,           0  ,    0  ,    0   ,    0);

  PinSetSupply(VREFLO    ,  86 , Ground,            0  ,    0  ,    0   ,    0);

  DeviceTableClose;

 end;     (* Probe *)

F240_132QFP, C240_132QFP:
 begin

    DeviceTableOpen;
    devicetablename:= 'Final132DeviceTable';
    DeviceTableSetName(devicetablename);

if (mso_tester) then
begin
     (* 19-Dec-96 begin add adc test                                        *)

  PinSetWSA(ADCINPUTP     ,  531 , WSA_LFAwgPin1_Plus, WSA_I, AMINV, AMAXV, AMINI, AMAXI);
  PinListSetNull(ADCINPUTN);           (* temporary until final rev of APC due out in 3/97 *)
  PinSetTrigger( DIOTRIGGER,      1);  (*VPL trigger field -> bit 1   left to right*)
  PinSetTrigger( AWGTRIGGER_CLK,  2);  (*VPL trigger field -> bit 2   left to right*)
  PinSetTrigger( AWGTRIGGER_START,3);  (*VPL trigger field -> bit 3   left to right*)
     (* 19-Dec-96 end add adc test                                          *)
end;

(*              Pin           Pad    Tester    Pin  Minimum Maximum Minimum Maximum*)
(*              Name          Number Pin #     Type Voltage Voltage Current Current*)
   PinSet  	(WEN        ,   1 ,   80,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(RNW        ,   4 ,   79,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(BRN        ,   5 ,   77,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(STRBN      ,   6 ,   73,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D0         ,   9 ,    9,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D1         ,  10 ,   10,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D2         ,  11 ,   11,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D3         ,  12 ,   12,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D4         ,  15 ,   13,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D5         ,  16 ,   14,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D6         ,  17 ,   15,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D7         ,  18 ,   16,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D8         ,  19 ,   17,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D9         ,  22 ,   18,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D10        ,  23 ,   19,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D11        ,  24 ,   20,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D12        ,  25 ,   21,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D13        ,  26 ,   22,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D14        ,  27 ,   23,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(D15        ,  28 ,   24,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(TCK        ,  30 ,   75,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(TDI        ,  31 ,   84,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(TRSTN      ,  32 ,   82,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(TMS        ,  33 ,   87,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(TDO        ,  34 ,   85,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(RSN        ,  35 ,   88,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(READY      ,  36 ,   86,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(MPMCN      ,  37 ,   83,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(EMU0       ,  38 ,   81,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(EMU1       ,  39 ,   26,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(NMIN       ,  40 ,   89,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(LVDOVRD    ,  41 ,   28,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PMTMODE    ,  42 ,   31,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(SCIRXD     ,  43 ,   27,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(SCITXD     ,  44 ,   91,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(SPISIMO    ,  45 ,   30,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(SPISOMI    ,  48 ,   29,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(SPICLK     ,  49 ,   95,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(SPISTE     ,  51 ,   32,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PDPINT     ,  52 ,   25,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(XINT1      ,  53 ,   96,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(XINT2      ,  54 ,   90,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(XINT3      ,  55 ,   44,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(OSCBYPN    ,  56 ,   92,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(XTAL2      ,  57 ,   42,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMux    (CLKIN      ,  58 ,   93,94,    I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCSOC     ,  63 ,   48,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMux    (CLKOUT1    ,  64 ,  101,102,  IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(XF         ,  65 ,   46,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(BION       ,  66 ,  108,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(CAP1       ,  67  , 106,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(CAP2       ,  68  , 100,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(CAP3       ,  69 ,  105,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(CAP4       ,  70 ,   37,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN0     ,  72 ,   45,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN1     ,  73 ,   43,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN2     ,  74 ,   47,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN3     ,  75 ,   97,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN4     ,  76 ,   41,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN5     ,  77 ,   99,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN6     ,  78 ,  110,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN7     ,  79 ,  103,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN15    ,  80 ,  111,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN14    ,  81 ,  107,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN13    ,  82 ,  104,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN12    ,  83 ,  112,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet     (VREFHI     ,  85 ,   33,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN11    ,  88 ,   34,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN10    ,  89 ,  109,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN9     ,  90 ,   39,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ADCIN8     ,  91 ,   36,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PWM1       ,  94 ,   98,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PWM2       ,  95 ,   38,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PWM3       ,  96 ,   35,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PWM4       ,  97 ,   50,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PWM5       ,  98 ,   52,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PWM6       ,  99 ,   54,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PWM7       , 100 ,   56,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PWM8       , 101 ,   55,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PWM9       , 102 ,   53,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(T1PWM      , 105 ,   51,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(T2PWM      , 106 ,   49,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(T3PWM      , 107 ,  114,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(TMRDIR     , 108 ,  115,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(TMRCLK     , 109 ,  113,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A0         , 110 ,  116,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A1         , 111 ,   59,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A2         , 112 ,   57,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A3         , 114 ,   62,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A4         , 115 ,   60,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A5         , 116 ,   58,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A6         , 117 ,   63,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A7         , 118 ,   64,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A8         , 119 ,   61,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A9         , 122 ,   65,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A10        , 123 ,   67,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A11        , 124 ,   71,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A12        , 125 ,   69,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A13        , 126 ,   70,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A14        , 127 ,   72,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(A15        , 128 ,   66,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(DSN        , 129 ,   68,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(ISN        , 130 ,   78,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(PSN        , 131 ,   76,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSet  	(RDN        , 132 ,   74,       O, MINV,   MAXV,   MINI,   MAXI );

  PinSetNoTDR(VREFHI);

     (*       Power Supply Pins are                                   *)
     (*       Ground Pins are                                         *)

  PinSetSupply(CVdd      ,   7 , Supply1 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(CVdd      ,  60 , Supply1 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );

  PinSetSupply(DVdd      ,   2 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  13 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  21 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  47 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  62 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      ,  93 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      , 103 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  PinSetSupply(DVdd      , 121 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );

  PinSetSupply(Vcca      ,  84 , Supply3 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  
  PinSetSupply(Vccp      ,  50 , Supply4 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );

  PinSetSupply(CVss      ,   8 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(CVss      ,  59 , Ground ,           0  ,    0  ,    0   ,    0);

  PinSetSupply(DVss      ,   3 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  14 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  20 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  29 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  46 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  61 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  71 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      ,  92 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      , 104 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      , 113 , Ground ,           0  ,    0  ,    0   ,    0);
  PinSetSupply(DVss      , 120 , Ground ,           0  ,    0  ,    0   ,    0);

  PinSetSupply(Vssa      ,  87 , Ground ,           0  ,    0  ,    0   ,    0);

  PinSetSupply(VREFLO    ,  86 , Ground,            0  ,    0  ,    0   ,    0);

  DeviceTableClose;

end;  (* X240_132PQ *)

end; (* case TIDeviceType *)

	(*                                                     *)
	(*             Define Pin Lists                        *)
	(*                                                     *)

     PinListSet     (EVENPINS,RNW,STRBN,D1,D3,D5,D7,D9,D11,D13,D15,TCK,TRSTN,TDO,
                     READY,EMU0,NMIN,PMTMODE,SCITXD,SPISOMI,PDPINT,XINT2,
                     OSCBYPN,CLKIN,CLKOUT1,BION,CAP2,CAP4,
                     ADCIN0,ADCIN2,ADCIN4,ADCIN6,ADCIN15,ADCIN13,ADCIN11,ADCIN9,
                     PWM1,PWM3,PWM5,PWM7,PWM9,T2PWM,
 		     TMRDIR,A0,A2,A3,A5,A7,A9,A11,A13,A15,ISN,RDN);

     PinListSet     (ODDPINS,WEN,BRN,D0,D2,D4,D6,D8,D10,D12,D14,TDI,TMS,RSN,
                     MPMCN,EMU1,LVDOVRD,SCIRXD,SPISIMO,SPICLK,SPISTE,
                     XINT1,XINT3,XTAL2,ADCSOC,XF,CAP1,CAP3,
                     ADCIN1,ADCIN3,ADCIN5,ADCIN7,ADCIN14,ADCIN12,VREFHI,ADCIN10,
                     ADCIN8,PWM2,PWM4,PWM6,PWM8,T1PWM,
                     T3PWM,TMRCLK,A1,A4,A6,A8,A10,A12,A14,DSN,PSN);

     PinListSet     (EVENINS,TCK,TRSTN,READY,NMIN,PMTMODE,PDPINT,OSCBYPN,CLKIN,
			ADCIN2,ADCIN4,ADCIN6,ADCIN11,ADCIN13,ADCIN15);

     PinListSet     (ODDINS,ADCIN3,ADCIN5,ADCIN7,ADCIN10,ADCIN12,ADCIN14,LVDOVRD,
		     MPMCN,XINT1,VREFHI,TDI,TMS);

     PinListSet     (ABUS,A15,A14,A13,A12,A11,A10,A9,A8,A7,A6,A5,A4,A3,A2,A1,A0);
     PinListSet     (DBUS,D15,D14,D13,D12,D11,D10,D9,D8,D7,D6,D5,D4,D3,D2,D1,D0);
     PinListSet     (ABTIME, PSN,DSN,ISN,RNW,BRN);
     PinListSet     (ACTRL, PSN,DSN,ISN);

     PinListSet     (ADCINS,ADCIN2,ADCIN3,ADCIN4,ADCIN5,ADCIN6,ADCIN7,
                            ADCIN10,ADCIN11,ADCIN12,ADCIN13,ADCIN14,ADCIN15);

     PinListSet     (ADCIOS,ADCIN0,ADCIN1,ADCIN8,ADCIN9);

     PinListSet     (EVENADCINS,ADCIN2,ADCIN4,ADCIN6,ADCIN11,ADCIN13,ADCIN15);
     PinListSet     (EVENADCIOS,ADCIN0,ADCIN9);

     PinListSet     (ODDADCINS,ADCIN3,ADCIN5,ADCIN7,ADCIN10,ADCIN12,ADCIN14);
     PinListSet     (ODDADCIOS,ADCIN1,ADCIN8);

     PinListSet     (INDOWNS,TRSTN,PMTMODE);            (* I/P pins with pull downs *)
     PinListSet     (INUPS,TDI,TMS,TCK);	        (* I/P pins with pull ups - LVDOVRD removed for PG3.2 silicon*)
     PinListSet     (IOUPS,EMU0,EMU1);                  (* I/O pins with pull ups *)
     PinListSetNull (IOUPS);                            (* non-std due to boundary-off requirements *)

     PinListSet     (EVENINLEAKINS,EVENINS);
     PinListUnSet   (EVENINLEAKINS,EVENADCINS);
     PinListUnSet   (EVENINLEAKINS,INUPS);		(* Take out pins with pull-ups *)
     PinListUnSet   (EVENINLEAKINS,INDOWNS);		(* Take out pins with pull-downs *)

     PinListSet     (ODDINLEAKINS,ODDINS);
     PinListUnSet   (ODDINLEAKINS,ODDADCINS);
     PinListUnSet   (ODDINLEAKINS,VREFHI);
     PinListUnSet   (ODDINLEAKINS,INUPS);		(* Take out pins with pull-ups *)
     PinListUnSet   (ODDINLEAKINS,INDOWNS);		(* Take out pins with pull-downs *)

     PinListSet     (EVENTRISTATE,RNW,STRBN,D1,D3,D5,D7,D9,D11,D13,D15,TDO,EMU0,SCITXD,
			SPISOMI,XINT2,CLKOUT1,BION,CAP2,CAP4,ADCIN0,ADCIN9,PWM1,PWM3,PWM5,
			PWM7,PWM9,T2PWM,TMRDIR,A0,A2,A3,A5,A7,A9,A11,A13,A15,ISN,RDN);
     PinListUnSet   (EVENTRISTATE,EMU0); 
     PinListUnSet   (EVENTRISTATE,ADCIN0); 
     PinListUnSet   (EVENTRISTATE,ADCIN9);

     PinListSet     (ODDTRISTATE,WEN,BRN,D0,D2,D4,D6,D8,D10,D12,D14,RSN,EMU1,SCIRXD,
			SPISIMO,SPICLK,SPISTE,XINT3,XTAL2,ADCSOC,XF,CAP1,CAP3,
			ADCIN1,ADCIN8,PWM2,PWM4,PWM6,PWM8,T1PWM,T3PWM,TMRCLK,
			A1,A4,A6,A8,A10,A12,A14,DSN,PSN);
     PinListUnSet   (ODDTRISTATE,EMU1);
     PinListUnSet   (ODDTRISTATE,ADCIN1); 
     PinListUnSet   (ODDTRISTATE,ADCIN8); 
     PinListUnSet   (ODDTRISTATE,RSN); 
     PinListUnSet   (ODDTRISTATE,XTAL2);

     PinListSet     (ALLINS,				(* All inputs *)
			EVENINS,ODDINS);		

     PinListSet	    (ALLTRISTATE,			(* PinList for trilkg test*)
			EVENTRISTATE,ODDTRISTATE,EVENADCIOS,ODDADCIOS);

     PinListSet     (ALLIOS,ABUS,DBUS,ADCIN0,ADCIN1,ADCIN9,ADCIN8,PWM7,PWM8,
                     PWM9,T1PWM,T2PWM,T3PWM,TMRDIR,TMRCLK,
                     ADCSOC,CAP1,CAP2,CAP3,CAP4,XF,CLKOUT1,RSN,
                     BION,SCITXD,SCIRXD,SPISIMO,SPISOMI,
                     SPICLK,SPISTE,XINT2,XINT3,EMU0,EMU1);

     PinListSet     (ALLOUTS,TDO,DSN,PSN,ISN,RNW,STRBN,WEN,RDN,BRN,PWM1,PWM2,
                     PWM3,PWM4,PWM5,PWM6,XTAL2);

     PinListSet     (ALLPINS, EVENPINS, ODDPINS);
     PinListSet     (SHORTSPINS, ALLPINS);
     PinListSet     (OPENSPINS, ALLPINS);


     PinListSet	    (INPUTS, ALLINS);
     PinListUnSet   (INPUTS, CLKIN);

     PinListSet	    (TESTINS,				
			ALLINS);			
     PinListUnSet   (TESTINS,INUPS);
     PinListUnSet   (TESTINS,INDOWNS);

     PinListSet     (LOOSEIOS, ALLIOS);
     PinListUnSet   (LOOSEIOS, RSN);

     PinListSet     (LOOSEOUTS, ALLOUTS);
     PinListUnSet   (LOOSEOUTS, XTAL2);

     PinListSet     (TIMINGIOS, ALLIOS);
     PinListUnSet   (TIMINGIOS, RSN);

     PinListSet     (TIMINGOUTS, ALLOUTS);
     PinListUnSet   (TIMINGOUTS, XTAL2);

     PinListSet     (ALLINLEAKOUTS, ALLOUTS);

     PinListSet     (ALLINLEAKIOS,
			ALLIOS);		
     PinListUnSet   (ALLINLEAKIOS,EMU0);
     PinListUnSet   (ALLINLEAKIOS,EMU1);

     PinListSet(PTULEAK1,INDOWNS);

(* VREFHI WAS REMOVED FROM PTULEAK2 DUE TO TESTER MEASUREMENT PROBLEM *)
     PinListSet(PTULEAK2,EMU0,EMU1,ODDINLEAKINS,EVENINLEAKINS,ODDADCINS,EVENADCINS,INUPS);

     PinListSet(PTULEAK3,ODDTRISTATE,EVENTRISTATE,ODDADCIOS,EVENADCIOS,IOUPS);

     PinListSetNull (NOINLEAKTESTINS);

     PinListSet     (NOTRILKGTESTIOS, ALLOUTS,ALLIOS);
     PinListUnSet   (NOTRILKGTESTIOS, ODDTRISTATE);
     PinListUnSet   (NOTRILKGTESTIOS, ODDADCIOS);
     PinListUnSet   (NOTRILKGTESTIOS, EVENTRISTATE);
     PinListUnSet   (NOTRILKGTESTIOS, EVENADCIOS);
     PinListUnSet   (NOTRILKGTESTIOS, EMU0);
     PinListUnSet   (NOTRILKGTESTIOS, EMU1);

     PinListSet     (NOPTUITESTPINS, ALLPINS);
     PinListUnSet   (NOPTUITESTPINS, INDOWNS);
     PinListUnSet   (NOPTUITESTPINS, EMU0);
     PinListUnSet   (NOPTUITESTPINS, EMU1);
     PinListUnSet   (NOPTUITESTPINS, ODDINLEAKINS);
     PinListUnSet   (NOPTUITESTPINS, EVENINLEAKINS);
     PinListUnSet   (NOPTUITESTPINS, ODDADCINS);
     PinListUnSet   (NOPTUITESTPINS, EVENADCINS);
     PinListUnSet   (NOPTUITESTPINS, INUPS);
     PinListUnSet   (NOPTUITESTPINS, VREFHI);
     PinListUnSet   (NOPTUITESTPINS, ODDTRISTATE);
     PinListUnSet   (NOPTUITESTPINS, EVENTRISTATE);
     PinListUnSet   (NOPTUITESTPINS, ODDADCIOS);
     PinListUnSet   (NOPTUITESTPINS, EVENADCIOS);
     PinListUnSet   (NOPTUITESTPINS, IOUPS);
  
     PinListSet(MASKED,RSN);

     PinListSetNull(NCPINS);

     PinListSet(IDDQDISCONNECT,
                INUPS,INDOWNS,IOUPS,EMU0,EMU1,              (* Pull-ups,Pull-down *)
                CLKOUT1,ABUS,XF,                         (* driving I/O's *)
                ALLOUTS);                               (* outputs *)

{     PinListUnSet(IDDQDISCONNECT,LVDOVRD);}	(* NEED TO DRIVE HIGH FOR LOW IDDQ MEASUREMENTS - LVDOVRD pu removed for PG3.2 silicon *)

     PinListSet     (MUXPINS,
                        CLKIN,CLKOUT1);
   
(* FLASH Group PinList *)

     PinListSet     (TABUS,A14,A13,A12,A11,A10,A9,A8,A7,A6,A5,A4,A3,A2,A1,A0);
     PinListSet     (TTCR,SCITXD,SCIRXD,SPISIMO,SPISOMI,SPICLK,SPISTE);
     PinListSet     (TSP,CLKOUT1,BION,XF,ADCSOC,CAP1,CAP2,CAP3,CAP4);
     PinListSet     (TWRITE,PWM8);
     PinListSet     (TERASE,PWM9);
     PinListSet     (TVER1,XINT3);
     PinListSet     (TVER0,XINT2);
     PinListSet     (TRESET,T3PWM);
     PinListSet     (TCE,PWM7);
     PinListSet     (TLP,T2PWM);
     PinListSet     (TEXE,T1PWM);
     PinListSet     (TDBUS,D15,D14,D13,D12,D11,D10,D9,D8,D7,D6,D5,D4,D3,D2,D1,D0);
(*     PinListSet     (TPMT,DIV2,BION);*)
     PinListSet     (NonFlashINS,CLKIN,XINT1,PDPINT,TCK,TDI,TMS,TRSTN,READY,
                     OSCBYPN,MPMCN,NMIN,ADCIN2,ADCIN3,ADCIN4,ADCIN5,ADCIN6,
                     ADCIN7,ADCIN10,ADCIN11,ADCIN12,ADCIN13,ADCIN14,ADCIN15,
                     VREFHI);
     PinListSet     (NonFlashOUT,XTAL2,TDO,ABTIME,RDN,WEN,STRBN,PWM1,PWM2,PWM3,
                     PWM4,PWM5,PWM6);
     PinListSet     (NonFlashIOS,A15,RSN,EMU0,EMU1,ADCIN0,ADCIN1,ADCIN8,ADCIN9,
                     TMRDIR,TMRCLK);

     (*                                                                     *)
     (*       Pattern Fields		                                    *)
     (*                                                                     *)
     PinListSet	    (FIELD1 ,RSN,CLKIN,CLKIN,CLKOUT1,CLKOUT1,XTAL2,OSCBYPN);
     PinListSet     (FIELD2 ,A15,A14,A13,A12,A11,A10,A9,A8,A7,A6,A5,A4,A3,A2,A1,A0);
     PinListSet     (FIELD3 ,D15,D14,D13,D12,D11,D10,D9,D8,D7,D6,D5,D4,D3,D2,D1,D0);
     PinListSet     (FIELD4 ,TCK,TDI,TDO,TMS,TRSTN,EMU0,EMU1);
     PinListSet     (FIELD5 ,DSN,PSN,ISN,READY,RNW,BRN,WEN,RDN,STRBN);
     PinListSet     (FIELD6 ,MPMCN,NMIN,BION,XF,XINT1,XINT2,XINT3);
     PinListSet     (FIELD7 ,ADCIN15,ADCIN14,ADCIN13,ADCIN12,ADCIN11,ADCIN10,ADCIN9,ADCIN8
			    ,ADCIN7,ADCIN6,ADCIN5,ADCIN4,ADCIN3,ADCIN2,ADCIN1,ADCIN0);
     PinListSet     (FIELD8 ,PWM7,PWM8,PWM9,T1PWM,T2PWM,T3PWM);
     PinListSet     (FIELD9 ,TMRDIR,TMRCLK,ADCSOC,CAP1,CAP2,CAP3,CAP4);
     PinListSet     (FIELD10,SCITXD,SCIRXD,SPISIMO,SPISOMI,SPICLK,SPISTE);
     PinListSet     (FIELD11,PWM1,PWM2,PWM3,PWM4,PWM5,PWM6);
     PinListSet	    (FIELD12,PDPINT,PMTMODE,VREFHI,LVDOVRD);

     PinListSetNull(noPinList);

     (* 19-Dec-96 begin add adc test                                        *)
     PinListSet (LECPINS,D9,D8,D7,D6,D5,D4,D3,D2,D1,D0);
     (* 19-Dec-96 end add adc test                                          *)
end;
