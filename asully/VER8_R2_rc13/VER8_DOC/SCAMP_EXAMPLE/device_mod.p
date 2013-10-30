





























procedure DeviceTableSet;

var
    devicetablename : String;

const
    MINV    = -4v;                 
    MAXV    = 8v;                  
    MINI    = -50ma;               
    MAXI    = 50ma;                
    MINVCC  = -4v;                 
    MAXVCC  = 8v;                  
    MINVCCI = -200000;             
    MAXVCCI = 400000;              












begin
    DeviceTableOpen;
case TIDeviceType of
   PX3F16D28PJQ, PX3F16D28HEQ,
   PX3F16D28APJQ, PX3F16D28AHEQ,
   PX3F16D28BPJQ, PX3F16D28BHEQ,
   Z1F281FxxPJM,
   S4D27FxxPJQ, S4D27FxxHEQ,
   S4D26CSFxxPJQ, S4D26CSFxxHEQ,
   S4D27RFxxPJM :
   begin
   PinSetMP  (TO4        ,   1 ,  65 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TO3        ,   2 ,  17 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TO2        ,   3 ,  66 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TO1        ,   4 ,  25 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPISTB     ,   5 ,  68 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPISOMI    ,   6 ,  26 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPISIMO    ,   7 ,  29 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPICLK     ,   8 ,  27 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_3    ,   9 ,  30 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_4    ,  10 ,  28 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_5    ,  11 ,  69 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_6    ,  12 ,  67 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T11        ,  15 ,  70 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T12        ,  16 ,  35 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T21        ,  18 ,  36 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T22        ,  19 ,  31,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (RX1        ,  21 ,  32 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (RX2        ,  22 ,  76 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN6        ,  23 ,  71 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN0        ,  24 ,  34 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN1        ,  25 ,  72 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN2        ,  26 ,  73 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN3        ,  27 ,  75 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN4        ,  28 ,  74 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN5        ,  29 ,  33 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T31        ,  31 ,  37 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T32        ,  32 ,  77 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T41        ,  34 ,  78 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T42        ,  35 ,  38 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_VPP     ,  37 ,  39 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_BRL1    ,  40 ,  80 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_BRL2    ,  41 ,  79 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_CLKOUT  ,  42 ,  41 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_REL     ,  44 ,   1 ,      O,  MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_SO      ,  45 ,   4 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_SI      ,  46 ,   2 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_C1      ,  47 ,  83 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_C0      ,  48 ,  43 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_DPOUT   ,  49 ,  84 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_SHFTCLK ,  50 ,  44 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_TEST    ,  51 ,  48 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (nRESET     ,  52 ,   5 ,     IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (DIV2       ,  53 ,  87 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (MUL2       ,  54 ,   8 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (DP_CLKIN   ,  55 ,  88 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_TEST   ,  56 ,  47 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (OSCOUT     ,  59 ,  9 ,       IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMuxMP (OSCIN    ,  60 ,  45,46,    I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (PLLEN      ,  61 ,  49 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_DPOUT  ,  65 ,  50 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_SHFTCLK,  66 ,  14 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TCMP3      ,  67 ,  89,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TCMP2      ,  68 ,  53 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_0    ,  69 ,  11 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_1    ,  70 ,  54 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_2    ,  71 ,  12 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B0     ,  72 ,  15 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B1     ,  74 ,  16 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B2     ,  75 ,  91 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B3     ,  76 ,  55 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B4     ,  77 ,  92 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B5     ,  78 ,  56 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B6     ,  79 ,  13 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_REL    ,  80 ,  96 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_SO     ,  81 ,  18 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_SI     ,  82 ,  98 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C1     ,  83 ,  57 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C0     ,  84 ,  19 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_BRL2   ,  85 ,  58 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_BRL1   ,  86 ,  20 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (CLKOUT     ,  88 ,  59 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TCAP4      ,  89 ,  99 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (EXTINT2    ,  90 ,  60 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (EXTINT1    ,  91 , 100 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (EXTINT0    ,  92 ,  61 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN7        ,  93 ,  21 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TXCAN      ,  94 ,  62 ,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (RXCAN      ,  95 ,  63 ,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_VPP    ,  96 ,  22 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN8        ,  98 ,  23 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SCICLK     ,  99 ,  64 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SCITXD     , 100 ,  24 ,      IO, MINV,   MAXV,   MINI,   MAXI );

     
     
   PinSetSupply(VDDC     ,  57 , Supply1 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VDDLC16  ,  73 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VSSC     ,  58 , Ground ,           0  ,    0  ,    0   ,    0);
   PinSetSupply(VDDPC16  ,  13 , Supply3 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VDDAC16  ,  17 , Supply4 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VDDC8    ,  36 , Supply5 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VDDPC8   ,  38 , Supply6 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VDDAC8   ,  30 , Supply7 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VDDPLL   ,  63 , Supply8 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
  end;

  HS4D27FxxIN,
  HS4D27RFxxIN :        
     begin
       if miho_site then
         begin 
   TIJPinSetPP  (TO4        ,   1,    36,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TO3        ,   2,    35,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TO2        ,   3,    40,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TO1        ,   4,    39,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SPISTB     ,   5,    38,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SPISOMI    ,   6,    37,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SPISIMO    ,   7,    34,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SPICLK     ,   8,    33,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_3    ,   9,    92,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_4    ,  10,    91,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_5    ,  11,    96,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_6    ,  12,    95,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T11        ,  15,    89,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T12        ,  16,    28,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T21        ,  18,    32,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T22        ,  19,    31,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (RX1        ,  21,    30,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (RX2        ,  22,    29,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN6        ,  23,    26,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN0        ,  24,    25,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN1        ,  25,    84,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN2        ,  26,    83,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN3        ,  27,    88,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN4        ,  28,    87,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN5        ,  29,    86,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T31        ,  31,    81,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T32        ,  32,    20,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T41        ,  34,    24,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T42        ,  35,    23,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_VPP     ,  38,    21,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_BRL1    ,  41,    17,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_BRL2    ,  42,    75,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_CLKOUT  ,  43,    79,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_REL     ,  46,    74,     O,  MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_SO      ,  47,    73,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_SI      ,  48,    12,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_C1      ,  49,    11,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_C0      ,  50,    16,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_DPOUT   ,  51,    14,     O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_SHFTCLK ,  52,    13,     O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_TEST    ,  53,    9 ,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (nRESET     ,  54,    71,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (DIV2       ,  55,    70,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (MUL2       ,  56,    69,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (DP_CLKIN   ,  57,    66,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_TEST   ,  58,    65,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (OSCOUT     ,  61,    8 ,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetMuxPP (OSCIN    ,  62,    3 , 4,  I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (PLLEN      ,  63,    7 ,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_DPOUT  ,  68,    6 ,     O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_SHFTCLK,  69,    5 ,     O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TCMP3      ,  70,    2 ,     O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TCMP2      ,  71,    1 ,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_0    ,  72,    60,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_1    ,  73,    59,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_2    ,  74,    64,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B0     ,  75,    63,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B1     ,  78,    61,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B2     ,  79,    58,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B3     ,  80,    57,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B4     ,  81,    52,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B5     ,  82,    51,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B6     ,  83,    56,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_REL    ,  84,    55,     O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_SO     ,  86,    54,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_SI     ,  87,    53,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C1     ,  88,    50,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C0     ,  89,    49,     IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_BRL2   ,  90,    108,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_BRL1   ,  91,    107,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (CLKOUT     ,  94,    111,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TCAP4      ,  95,    48 ,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (EXTINT2    ,  96,    47 ,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (EXTINT1    ,  97,    110,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (EXTINT0    ,  98,    109,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN7        ,  99,    46 ,    I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TXCAN      , 100,    105,     O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (RXCAN      , 101,    41 ,     I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_VPP    , 102,    102,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN8        , 105,    100,    I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SCICLK     , 106,    104,    IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SCITXD     , 107,    98 ,    IO, MINV,   MAXV,   MINI,   MAXI );

     
     
   PinSetSupply(VDDC     ,  57 , Supply1 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VDDAC16  ,  17 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VSSC     ,  58 , Ground ,           0  ,    0  ,    0   ,    0);


         end else begin
   PinSetMP  (TO4        ,   1 ,  65 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TO3        ,   2 ,  17 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TO2        ,   3 ,  66 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TO1        ,   4 ,  25 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPISTB     ,   5 ,  68 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPISOMI    ,   6 ,  26 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPISIMO    ,   7 ,  29 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPICLK     ,   8 ,  27 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_3    ,   9 ,  30 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_4    ,  10 ,  28 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_5    ,  11 ,  69 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_6    ,  12 ,  67 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T11        ,  15 ,  70 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T12        ,  16 ,  35 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T21        ,  18 ,  36 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T22        ,  19 ,  31,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (RX1        ,  21 ,  32 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (RX2        ,  22 ,  76 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN6        ,  23 ,  71 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN0        ,  24 ,  34 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN1        ,  25 ,  72 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN2        ,  26 ,  73 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN3        ,  27 ,  75 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN4        ,  28 ,  74 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN5        ,  29 ,  33 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T31        ,  31 ,  37 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T32        ,  32 ,  77 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T41        ,  34 ,  78 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T42        ,  35 ,  38 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_VPP     ,  37 ,  39 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_BRL1    ,  40 ,  80 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_BRL2    ,  41 ,  79 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_CLKOUT  ,  42 ,  41 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_REL     ,  44 ,   1 ,      O,  MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_SO      ,  45 ,   4 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_SI      ,  46 ,   2 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_C1      ,  47 ,  83 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_C0      ,  48 ,  43 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_DPOUT   ,  49 ,  84 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_SHFTCLK ,  50 ,  44 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_TEST    ,  51 ,  48 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (nRESET     ,  52 ,   5 ,     IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (DIV2       ,  53 ,  87 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (MUL2       ,  54 ,   8 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (DP_CLKIN   ,  55 ,  88 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_TEST   ,  56 ,  47 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (OSCOUT     ,  59 ,  9 ,       IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMuxMP (OSCIN    ,  60 ,  45,46,    I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (PLLEN      ,  61 ,  49 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_DPOUT  ,  65 ,  50 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_SHFTCLK,  66 ,  14 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TCMP3      ,  67 ,  89,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TCMP2      ,  68 ,  53 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_0    ,  69 ,  11 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_1    ,  70 ,  54 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_2    ,  71 ,  12 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B0     ,  72 ,  15 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B1     ,  74 ,  16 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B2     ,  75 ,  91 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B3     ,  76 ,  55 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B4     ,  77 ,  92 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B5     ,  78 ,  56 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B6     ,  79 ,  13 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_REL    ,  80 ,  96 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_SO     ,  81 ,  18 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_SI     ,  82 ,  98 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C1     ,  83 ,  57 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C0     ,  84 ,  19 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_BRL2   ,  85 ,  58 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_BRL1   ,  86 ,  20 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (CLKOUT     ,  88 ,  59 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TCAP4      ,  89 ,  99 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (EXTINT2    ,  90 ,  60 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (EXTINT1    ,  91 , 100 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (EXTINT0    ,  92 ,  61 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN7        ,  93 ,  21 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TXCAN      ,  94 ,  62 ,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (RXCAN      ,  95 ,  63 ,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_VPP    ,  96 ,  22 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN8        ,  98 ,  23 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SCICLK     ,  99 ,  64 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SCITXD     , 100 ,  24 ,      IO, MINV,   MAXV,   MINI,   MAXI );
     end; 
     
     
   PinSetSupply(VDDC     ,  57 , Supply1 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VDDAC16  ,  17 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VSSC     ,  58 , Ground ,           0  ,    0  ,    0   ,    0);

    end;
  HS4D26CSFxxIN :      
     begin
       if miho_site then begin
   TIJPinSetPP  (TO4        ,   1 ,  40   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TO3        ,   2 ,  39   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TO2        ,   3 ,  38   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TO1        ,   4 ,  37   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SPISTB     ,   5 ,  34   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SPISOMI    ,   6 ,  33   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SPISIMO    ,   7 ,  92   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SPICLK     ,   8 ,  91   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_3    ,   9 ,  96   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_4    ,  10 ,  95   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_5    ,  11 ,  94   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_6    ,  12 ,  93   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T11        ,  15 ,  28   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T12        ,  16 ,  27   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T21        ,  18 ,  32   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T22        ,  19 ,  31   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (RX1        ,  21 ,  30   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (RX2        ,  22 ,  29   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN6        ,  23 ,  26   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN0        ,  24 ,  25   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN1        ,  25 ,  84   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN2        ,  26 ,  83   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN3        ,  27 ,  88   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN4        ,  28 ,  87   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN5        ,  29 ,  86   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T31        ,  31 ,  20   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T32        ,  32 ,  19   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T41        ,  34 ,  22   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (T42        ,  35 ,  21   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_VPP     ,  37 ,  17   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_BRL1    ,  40 ,  79   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_BRL2    ,  41 ,  78   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_CLKOUT  ,  42 ,  77   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_REL     ,  44 ,  12   ,       O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_SO      ,  45 ,  11   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_SI      ,  46 ,  16   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_C1      ,  47 ,  15   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_C0      ,  48 ,  14   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_DPOUT   ,  49 ,  13   ,       O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_SHFTCLK ,  50 ,  10   ,       O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C8_TEST    ,  51 ,  72   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (nRESET     ,  52 ,  71   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (DIV2       ,  53 ,  70   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (MUL2       ,  54 ,  69   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (DP_CLKIN   ,  55 ,  66   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_TEST   ,  56 ,  65   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (OSCOUT     ,  59 ,  3    ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetMuxPP (OSCIN    ,  60 ,  7    , 8  ,  I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (PLLEN      ,  61 ,  6    ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_DPOUT  ,  65 ,  60   ,       O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_SHFTCLK,  66 ,  59   ,       O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TCMP3      ,  67 ,  64   ,       O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TCMP2      ,  68 ,  63   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_0    ,  69 ,  62   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_1    ,  70 ,  61   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C_2    ,  71 ,  58   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B0     ,  72 ,  57   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B1     ,  74 ,  52   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B2     ,  75 ,  51   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B3     ,  76 ,  56   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B4     ,  77 ,  55   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B5     ,  78 ,  54   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_B6     ,  79 ,  53   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_REL    ,  80 ,  50   ,       O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_SO     ,  81 ,  49   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_SI     ,  82 ,  108  ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C1     ,  83 ,  107  ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_C0     ,  84 ,  44   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_BRL2   ,  85 ,  43   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_BRL1   ,  86 ,  48   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (CLKOUT     ,  88 ,  109  ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TCAP4      ,  89 ,  46   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (EXTINT2    ,  90 ,  45   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (EXTINT1    ,  91 ,  105  ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (EXTINT0    ,  92 ,  41   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN7        ,  93 ,  102  ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (TXCAN      ,  94 ,  101  ,       O, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (RXCAN      ,  95 ,  100  ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (C16_VPP    ,  96 ,  99   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (AN8        ,  98 ,  97   ,       I, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SCICLK     ,  99 ,  36   ,      IO, MINV,   MAXV,   MINI,   MAXI );
   TIJPinSetPP  (SCITXD     , 100 ,  35   ,      IO, MINV,   MAXV,   MINI,   MAXI );

       end else begin
   PinSetMP  (TO4        ,   1 ,  65 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TO3        ,   2 ,  17 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TO2        ,   3 ,  66 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TO1        ,   4 ,  25 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPISTB     ,   5 ,  68 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPISOMI    ,   6 ,  26 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPISIMO    ,   7 ,  29 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SPICLK     ,   8 ,  27 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_3    ,   9 ,  30 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_4    ,  10 ,  28 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_5    ,  11 ,  69 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_6    ,  12 ,  67 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T11        ,  15 ,  70 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T12        ,  16 ,  35 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T21        ,  18 ,  36 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T22        ,  19 ,  31,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (RX1        ,  21 ,  32 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (RX2        ,  22 ,  76 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN6        ,  23 ,  71 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN0        ,  24 ,  34 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN1        ,  25 ,  72 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN2        ,  26 ,  73 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN3        ,  27 ,  75 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN4        ,  28 ,  74 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN5        ,  29 ,  33 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T31        ,  31 ,  37 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T32        ,  32 ,  77 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T41        ,  34 ,  78 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (T42        ,  35 ,  38 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_VPP     ,  37 ,  39 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_BRL1    ,  40 ,  80 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_BRL2    ,  41 ,  79 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_CLKOUT  ,  42 ,  41 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_REL     ,  44 ,   1 ,      O,  MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_SO      ,  45 ,   4 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_SI      ,  46 ,   2 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_C1      ,  47 ,  83 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_C0      ,  48 ,  43 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_DPOUT   ,  49 ,  84 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_SHFTCLK ,  50 ,  44 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C8_TEST    ,  51 ,  48 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (nRESET     ,  52 ,   5 ,     IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (DIV2       ,  53 ,  87 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (MUL2       ,  54 ,   8 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (DP_CLKIN   ,  55 ,  88 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_TEST   ,  56 ,  47 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (OSCOUT     ,  59 ,  9 ,       IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMuxMP (OSCIN    ,  60 ,  45,46,    I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (PLLEN      ,  61 ,  49 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_DPOUT  ,  65 ,  50 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_SHFTCLK,  66 ,  14 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TCMP3      ,  67 ,  89,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TCMP2      ,  68 ,  53 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_0    ,  69 ,  11 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_1    ,  70 ,  54 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C_2    ,  71 ,  12 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B0     ,  72 ,  15 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B1     ,  74 ,  16 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B2     ,  75 ,  91 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B3     ,  76 ,  55 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B4     ,  77 ,  92 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B5     ,  78 ,  56 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_B6     ,  79 ,  13 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_REL    ,  80 ,  96 ,      O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_SO     ,  81 ,  18 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_SI     ,  82 ,  98 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C1     ,  83 ,  57 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_C0     ,  84 ,  19 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_BRL2   ,  85 ,  58 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_BRL1   ,  86 ,  20 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (CLKOUT     ,  88 ,  59 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TCAP4      ,  89 ,  99 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (EXTINT2    ,  90 ,  60 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (EXTINT1    ,  91 , 100 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (EXTINT0    ,  92 ,  61 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN7        ,  93 ,  21 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (TXCAN      ,  94 ,  62 ,       O, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (RXCAN      ,  95 ,  63 ,       I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (C16_VPP    ,  96 ,  22 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (AN8        ,  98 ,  23 ,      I, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SCICLK     ,  99 ,  64 ,      IO, MINV,   MAXV,   MINI,   MAXI );
   PinSetMP  (SCITXD     , 100 ,  24 ,      IO, MINV,   MAXV,   MINI,   MAXI );
    end; 
     
     
   PinSetSupply(VDDC     ,  57 , Supply1 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VDDAC16  ,  17 , Supply2 ,       MINVCC, MAXVCC, MINVCCI, MAXVCCI );
   PinSetSupply(VSSC     ,  58 , Ground ,           0  ,    0  ,    0   ,    0);

     end;
end;         
  DeviceTableClose;

     
     
     
     PinListSet     (CANPINS, RXCAN, TXCAN);
     PinListSet     (TRIGINS,T11,T12,T21,T22,T31,T32,T41,T42);
     PinListSet     (TRIGOUTS,TO1,TO2,TO3,TO4);
     PinListSet     (TAPC8INS,C8_C0,C8_C1,C8_SI);
     PinListSet     (TAPC16INS,C16_C0,C16_C1,C16_SI);
     PinListSet     (HOUTS,CLKOUT,OSCOUT);
     PinListSet     (TRIGGER,T11,T12,T21,T22,T31,T32,T41,T42,TO1,TO2,TO3,TO4);
     PinListSet     (ADC,AN0,AN1,AN2,AN3,AN4,AN5,AN6,AN7,AN8);
     PinListSet     (MAILBOX,DP_CLKIN,C16_DPOUT,C16_SHFTCLK,C8_DPOUT,C8_SHFTCLK);
     PinListSet     (Interrupt,EXTINT2,EXTINT1,EXTINT0);
     PinListSet     (BRL,C16_BRL2,C16_BRL1,C16_REL,C8_BRL2,C8_BRL1,C8_REL);
     PinListSet     (PORTC,C16_C_6,C16_C_5,C16_C_4,C16_C_3,C16_C_2,C16_C_1,C16_C_0);
     PinListSet     (PORTB,C16_B6,C16_B5,C16_B4,C16_B3,C16_B2,C16_B1,C16_B0);
     PinListSet     (Timer_C16,TCAP4,TCMP3,TCMP2);
     PinListSet     (SPI,SPISOMI,SPISIMO,SPICLK,SPISTB);
     PinListSet     (SCI,SCITXD,RX1,RX2,SCICLK);
     PinListSet     (ModeTest,C16_VPP,C8_VPP,C16_TEST,C8_TEST,DIV2,MUL2,PLLEN
                    ,C8_CLKOUT);
     PinListSet     (TAP,C16_C1,C16_C0,C16_SI,C16_SO,C8_C1,C8_C0,C8_SI,C8_SO);
     PinListSet     (Rst_Clk,nRESET,CLKOUT,OSCIN,OSCIN,OSCOUT);
     

     PinListSetNull (UnusedPins);

     PinListSet	(LEAK_lessPINS,TRIGINS,C16_TEST,C8_TEST);
     PinListSet (MTrig234,TO2,TO3,TO4);
     PinListSet (MTrig134,TO1,TO3,TO4);
     PinListSet (MTrig124,TO1,TO2,TO4);
     PinListSet (MTrig123,TO1,TO2,TO3);
     PinListSet (InTrig1,T11,T12);
     PinListSet (InTrig2,T21,T22);
     PinListSet (InTrig3,T31,T32);
     PinListSet (InTrig4,T41,T42);
     PinListSet (VPP,C8_VPP,C16_VPP);

     PinListSet (ioc8,C8_BRL1,C8_BRL2);
     PinListSet (outc8,C8_REL);
     PinListSet (ioc16,PORTB,PORTC,
                        SPI,SCITXD,SCICLK,
                        Interrupt,TCMP2,TCAP4,
                        TRIGOUTS,
                        C16_BRL1,C16_BRL2);
     PinListSet (outc16,         
                         TXCAN);
                        

PinListSet(bipull10,SPISTB,
                         TO4,TO3,TO2,TO1,
                         TCMP2,
                         C16_C_0,C16_C_1) ;  
PinListSet(gate,C16_B0,C16_B1,C16_B2,C16_B3); 
PinListSet(gate05,SPISIMO,SPICLK); 
PinListSet(anad,C16_C_3,C16_C_4,C16_C_5,C16_C_6); 
PinListSet(opd20,TCMP3 );
PinListSet( opd10  , C16_REL);
PinListSet( pul250 , EXTINT2);
PinListSet( pul500 , C16_C_2 );
PinListSet( bipol33, SCITXD );
PinListSet(gpioc16,bipull10,gate,gate05,anad,opd20,opd10,pul250,pul500,bipol33);



       PinListSetNull(noPinList);

    
    

     PinListSet     (EVENINS,T12,T21,RX2,AN0,AN2,AN4,AN8,T32,T41,MUL2,C16_TEST);

     PinListSet     (ODDINS,T11,T22,RX1,AN6,AN1,AN3,AN5,AN7,T31,T42,C8_TEST,DIV2
                    ,DP_CLKIN,OSCIN,PLLEN,RXCAN);

     PinListSet     (EVENTRISTATE,TO3,TO1,SPISOMI,SPICLK,C16_C_4,C16_C_6,C8_BRL1
                    ,C8_CLKOUT,C8_SI,C8_C0,TCMP2,C16_C_1,C16_B0,C16_B1,C16_B3
                    ,C16_B5,C16_SI,C16_C0,C16_BRL1,CLKOUT,EXTINT2,EXTINT0
                    ,C16_VPP,SCITXD);
     PinListSet     (ODDTRISTATE,TO4,TO2,SPISTB,SPISIMO,C16_C_3,C16_C_5,C8_BRL2
                    ,C8_SO,C8_C1,C16_C_0,C16_C_2,C16_B2,C16_B4,C16_B6
                    ,C16_SO,C16_C1,C8_VPP,C16_BRL2,TCAP4,EXTINT1,SCICLK);
     PinListSet     (ALLIOS,AN0,AN1,AN2,AN3,AN4,AN5,AN6,AN7,AN8,T11,T12,T21,T22,
                     RX1,RX2
                    ,T31,T32,T41,T42,C8_SO,C8_SI,C8_C1,C8_C0,C8_CLKOUT,C8_BRL2
                    ,C8_BRL1,C8_REL,C8_SHFTCLK,C8_DPOUT,C8_TEST,nRESET,OSCIN
                    ,OSCOUT,C16_TEST,DP_CLKIN,C16_DPOUT,C16_SHFTCLK,C16_REL
                    ,C16_B6,C16_B5,C16_B4,C16_B3,C16_B2,C16_B1,C16_B0,C16_C_6
                    ,C16_C_5,C16_C_4,C16_C_3,C16_C_2,C16_C_1,C16_C_0,EXTINT2
                    ,EXTINT1,EXTINT0,C16_SO,C16_SI,C16_C1,C16_C0,C16_BRL2
                    ,C16_BRL1,CLKOUT,TCAP4,TCMP2,SCICLK,SCITXD,TO4,TO3,TO2
                    ,TO1,SPISOMI,SPISIMO,SPICLK,SPISTB,DIV2,MUL2,PLLEN,C16_VPP
                    ,C8_VPP);
     PinListSetNull (PMUINS);
     PinListSetNull (NOTESTINS);
     PinListSet     (TESTINS,EVENINS, ODDINS);
     PinListSetNull (MUXPINS);

     PinListSet     (ODDPINS,AN1,AN3,AN5,AN6,AN7,T11,T21,RX1,T31,T41,
                     C8_SO,C8_C1,C8_CLKOUT
                    ,C8_BRL1,C8_SHFTCLK,C8_TEST,OSCIN,C16_TEST,C16_DPOUT,C16_REL
                    ,C16_B5,C16_B3,C16_B1,C16_C_6,C16_C_4,C16_C_2,C16_C_0
                    ,EXTINT1,C16_SO,C16_C1,C16_BRL2,CLKOUT,TCMP3,SCICLK,TO4,TO2
                    ,SPISOMI,SPICLK,DIV2,PLLEN,C8_VPP,RXCAN);

     PinListSet     (EVENPINS,AN0,AN2,AN4,AN8,T12,T22,RX2,T32,T42,C8_SI,C8_C0
                    ,C8_BRL2,C8_REL,C8_DPOUT,nRESET,OSCOUT,DP_CLKIN,C16_SHFTCLK
                    ,C16_B6,C16_B4,C16_B2,C16_B0,C16_C_5,C16_C_3,C16_C_1,EXTINT2
                    ,EXTINT0,C16_SI,C16_C0,C16_BRL1,TCAP4,TCMP2,SCITXD,TO3,TO1
                    ,SPISIMO,SPISTB,MUL2,C16_VPP,TXCAN);

     PinListSet (ALLOUTS,C8_REL,C8_DPOUT,C8_SHFTCLK,OSCOUT,
                 C16_REL,C16_DPOUT,C16_SHFTCLK,TCMP3,TXCAN);
     PinListSet(ALLOUTS_NOSC,ALLOUTS);
     PinListUnSet(ALLOUTS_NOSC,OSCOUT);

     PinListSet (ALLINS, EVENINS, ODDINS, NOTESTINS);
     PinListSet (ALLTRISTATE, EVENTRISTATE, ODDTRISTATE);

     PinListSet (NOTRISTATEOUTS, ALLOUTS, ALLIOS);
               
     PinListUnSet  (NOTRISTATEOUTS, EVENTRISTATE);
               
     PinListUnSet  (NOTRISTATEOUTS, ODDTRISTATE);
               
               

     PinListSet  (ALLPINS, EVENPINS, ODDPINS);
     PinListSet  (SHORTSPINS, ALLPINS);
     PinListSet  (OPENSPINS, ALLPINS);
     PinListSet  (SWPMatchPins,ALLPINS);
     PinListUnSet(SWPMatchPins,C16_SO);
     PinListUnSet(SWPMatchPins,C8_SO);
     PinListUnSet(SWPMatchPins,OSCIN);

end;

