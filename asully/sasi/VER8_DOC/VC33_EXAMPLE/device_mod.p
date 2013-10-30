














































	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

procedure DeviceTableSet;

var
        devicetablename :   String;

const
	MINV	=   -2v  ;		
	MAXV	=    8v  ;		
	MINI	=  -50ma ;		
	MAXI	=   50ma ;		
	MINVCC	=   -2v  ;		
	MAXVCC	=   15v  ;		
	MINVCCI = -200000;		
	MAXVCCI =  1000000;		
	MINVSUBS =   -5v  ;		
	MAXVSUBS =    2v  ;		
	MINISUBS = -300000;		
	MAXISUBS =  300000;		

begin

 case TITestType of
   Probe:
   begin
     DeviceTableOpen;
     devicetablename:= 'TMS320VC33ProbeDeviceTable';
     DeviceTableSetName(devicetablename);
       
       

  PinSetPP (     A20,      1,    68,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A19,      3,    67,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A18,      4,    72,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A17,      5,    71,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A16,      7,    70,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A15,      8,    69,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A14,     10,    66,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A13,     11,    65,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A12,     13,     6,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A11,     14,     5,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A10,     16,     2,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A9,     17,     1,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A8,     19,     8,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A7,     20,     7,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A6,     21,     4,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A5,     22,     3,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A4,     24,    60,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A3,     26,    59,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A2,     27,    64,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A1,     29,    63,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A0,     30,    62,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (  PAGE3_,	  32,    61,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (  PAGE2_,	  33,    58,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (  PAGE1_,     35,    57,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (  PAGE0_,     36,   108,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      H1,     38,   107,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      H3,     39,    52,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (   STRB_,     41,    51,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     RW_,     42,    56,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (   IACK_,	  44,    55,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (    RDY_,	  45,   110,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (   HOLD_,	  47,   109,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (  HOLDA_,	  48,    54,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D31,	  50,    53,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D30,	  51,    50,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D29,	  52,    49,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D28,	  54,    44,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D27,	  55,    43,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D26,	  57,    48,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D25,	  58,    47,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D24,	  59,    46,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D23,	  61,    45,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D22,	  62,    42,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D21,	  64,    41,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D20,	  65,   100,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D19,	  67,    99,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D18,	  68,    98,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D17,	  70,    97,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D16,	  71,    36,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D15,	  73,    35,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D14,	  74,    40,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D13,	  75,    39,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D12,	  76,    38,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D11,	  78,    37,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D10,	  79,    34,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D9,	  81,    33,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D8,	  82,    92,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D7,	  84,    91,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D6,	  85,    96,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D5,	  87,    95,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D4,	  88,    94,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D3,	  90,    93,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D2,	  91,    90,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D1,	  92,    89,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D0,	  93,    28,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (    EMU1,	  95,    27,    IO, MINV, MAXV, MINI, MAXI);            
  PinSetPP (    EMU0,	  96,    32,    IO, MINV, MAXV, MINI, MAXI);		
  PinSetPP (     TCK,	  98,    31,     I, MINV, MAXV, MINI, MAXI);		
  PinSetPP (     TDO,	  99,    30,     O, MINV, MAXV, MINI, MAXI);	
  PinSetPP (     TDI,	 100,    29,     I, MINV, MAXV, MINI, MAXI);		
  PinSetPP (     TMS,	 102,    26,     I, MINV, MAXV, MINI, MAXI);		
  PinSetPP (   TRST_,	 103,    25,     I, MINV, MAXV, MINI, MAXI);		
  PinSetPP (     DR0,	 104,    84,    IO, MINV, MAXV, MINI, MAXI);	
  PinSetPP (    FSR0,	 106,    83,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   CLKR0,	 107,    88,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   CLKX0,	 109,    87,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (    FSX0,	 110,    86,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     DX0,	 111,    85,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   TCLK1,	 113,    82,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   TCLK0,	 114,    81,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     XF1,	 116,    20,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     XF0,	 117,    19,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   INT3_,	 119,    24,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (   INT2_,	 120,    23,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (   INT1_,	 121,    22,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (   INT0_,	 122,    21,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (EDGEMODE,    124,    18,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (    MCBL,	 125,    17,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (  RESET_,	 127,    76,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (    SHZ_,	 128,    75,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (      X1,	 132,    78,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (CLKMODE1,    135,    11,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (CLKMODE0,    136,    16,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (    RSV1,	 138,    15,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (    RSV0,	 139,    14,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A23,	 141,    13,     O, MINV, MAXV, MINI, MAXI); 	
  PinSetPP (     A22,	 142,    10,     O, MINV, MAXV, MINI, MAXI);	
  PinSetPP (     A21,	 144,     9,     O, MINV, MAXV, MINI, MAXI);
	  
PinSetMuxPP ( EXTCLK,    130,   79,80, I, MINV, MAXV, MINI, MAXI);	       
PinSetMuxPP (X2CLKIN,    133,   73,74, I, MINV, MAXV, MINI, MAXI);             



  PinSetSupply(    VDD,   12,     Supply1,    MINVCC, MAXVCC, MINVCCI,MAXVCCI);
  PinSetSupply(   DVDD,    6,     Supply2,    MINVCC, MAXVCC, MINVCCI,MAXVCCI);
  PinSetSupply( PLLVDD,  131,     Supply3,    MINVCC, MAXVCC, MINVCCI,MAXVCCI);
  PinSetSupply(    Vss,    2,     Ground,        0,      0,      0,      0   );
















     DeviceTableClose;
   end;  

   Final_Handler,  QA_Handler,  PRE_Burnin_Handler,
   Final_Handtest, QA_Handtest, PRE_Burnin_Handtest:

  case TIDeviceType of
  TMS320VC33PGE75, SMVC33PGEA12EP :



   begin
     DeviceTableOpen;
     devicetablename:= 'TMS320VC33DeviceTable';
     DeviceTableSetName(devicetablename);

       
       


  PinSetPP (     A20,      1,    57,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A19,      3,    58,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A18,      4,    61,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A17,      5,    62,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A16,      7,    63,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A15,      8,    64,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A14,     10,    59,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A13,     11,    60,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A12,     13,     3,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A11,     14,     4,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A10,     16,     7,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A9,     17,     8,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A8,     19,     1,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A7,     20,     2,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A6,     21,     5,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A5,     22,     6,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A4,     24,    65,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A3,     26,    66,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A2,     27,    69,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A1,     29,    70,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      A0,     30,    71,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (  PAGE3_,	  32,    72,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (  PAGE2_,	  33,    67,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (  PAGE1_,     35,    68,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (  PAGE0_,     36,     9,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      H1,     38,    10,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (      H3,     39,    13,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (   STRB_,     41,    14,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     RW_,     42,    15,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (   IACK_,	  44,    16,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (    RDY_,	  45,    11,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (   HOLD_,	  47,    12,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (  HOLDA_,	  48,    73,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D31,	  50,    74,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D30,	  51,    77,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D29,	  52,    78,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D28,	  54,    79,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D27,	  55,    80,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D26,	  57,    75,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D25,	  58,    76,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D24,	  59,    17,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D23,	  61,    18,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D22,	  62,    21,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D21,	  64,    22,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D20,	  65,    23,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D19,	  67,    24,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D18,	  68,    19,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D17,	  70,    20,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D16,	  71,    81,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D15,	  73,    82,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D14,	  74,    85,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D13,	  75,    86,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D12,	  76,    87,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D11,	  78,    88,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     D10,	  79,    83,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D9,	  81,    84,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D8,	  82,    25,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D7,	  84,    26,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D6,	  85,    29,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D5,	  87,    30,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D4,	  88,    31,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D3,	  90,    32,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D2,	  91,    27,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D1,	  92,    28,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (      D0,	  93,    89,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (    EMU1,	  95,    90,    IO, MINV, MAXV, MINI, MAXI);            
  PinSetPP (    EMU0,	  96,    93,    IO, MINV, MAXV, MINI, MAXI);		
  PinSetPP (     TCK,	  98,    94,     I, MINV, MAXV, MINI, MAXI);		
  PinSetPP (     TDO,	  99,    95,     O, MINV, MAXV, MINI, MAXI);	
  PinSetPP (     TDI,	 100,    96,     I, MINV, MAXV, MINI, MAXI);		
  PinSetPP (     TMS,	 102,    91,     I, MINV, MAXV, MINI, MAXI);		
  PinSetPP (   TRST_,	 103,    92,     I, MINV, MAXV, MINI, MAXI);		
  PinSetPP (     DR0,	 104,    33,    IO, MINV, MAXV, MINI, MAXI);	
  PinSetPP (    FSR0,	 106,    34,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   CLKR0,	 107,    37,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   CLKX0,	 109,    38,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (    FSX0,	 110,    39,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     DX0,	 111,    40,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   TCLK1,	 113,    35,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   TCLK0,	 114,    36,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     XF1,	 116,    97,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     XF0,	 117,    98,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (   INT3_,	 119,    99,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (   INT2_,	 120,   100,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (   INT1_,	 121,    41,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (   INT0_,	 122,    42,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (EDGEMODE,    124,   101,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (    MCBL,	 125,   102,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (  RESET_,	 127,    45,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (    SHZ_,	 128,    46,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (      X1,	 132,    43,     O, MINV, MAXV, MINI, MAXI);
  PinSetPP (CLKMODE1,    135,    44,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (CLKMODE0,    136,    53,     I, MINV, MAXV, MINI, MAXI);
  PinSetPP (    RSV1,	 138,    54,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (    RSV0,	 139,    55,    IO, MINV, MAXV, MINI, MAXI);
  PinSetPP (     A23,	 141,    56,     O, MINV, MAXV, MINI, MAXI); 	
  PinSetPP (     A22,	 142,    51,     O, MINV, MAXV, MINI, MAXI);	
  PinSetPP (     A21,	 144,    52,     O, MINV, MAXV, MINI, MAXI);
	  
PinSetMuxPP ( EXTCLK,    130,   47,48,   I, MINV, MAXV, MINI, MAXI);	  
PinSetMuxPP (X2CLKIN,    133,   49,50,   I, MINV, MAXV, MINI, MAXI);

  PinSetSupply(    VDD,   12,     Supply1,    MINVCC, MAXVCC, MINVCCI,MAXVCCI);
  PinSetSupply(   DVDD,    6,     Supply2,    MINVCC, MAXVCC, MINVCCI,MAXVCCI);
  PinSetSupply( PLLVDD,  131,     Supply3,    MINVCC, MAXVCC, MINVCCI,MAXVCCI);
  PinSetSupply(    Vss,    2,     Ground,        0,      0,      0,      0   );
















     DeviceTableClose;
   end;
 end; 
end; 

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	






  PinListSet (DBUS, D31,D30,D29,D28,D27,D26,D25,D24,D23,D22,D21,D20,D19,D18,D17,
		    D16,D15,D14,D13,D12,D11,D10,D9,D8,D7,D6,D5,D4,D3,D2,D1,D0);

  PinListSet (ABUS, A23,A22,A21,A20,A19,A18,A17,A16,A15,A14,A13,A12,A11,A10,A9,
		    A8,A7,A6,A5,A4,A3,A2,A1,A0);

  PinListSet (EXTINT,INT3_,INT2_,INT1_,INT0_);        			


  PinListSet (CONTROL, RESET_,IACK_,MCBL,XF1,XF0);    			

  PinListSet (CLKOUTS, H1,H3);			      			

  PinListSet (SPPINS, CLKX0,CLKR0,DX0,DR0,FSX0,FSR0);        		

  PinListSet (TPINS, TCLK0,TCLK1);		      			

  PinListSet (ETPINS, EMU0, EMU1);                    			

  PinListSet (EXTMEMCONTROL, RW_,STRB_,RDY_,HOLD_,HOLDA_ );

  PinListSet (INPUTS, RDY_,TMS,INT3_,INT2_,INT1_,INT0_,EDGEMODE,	
              SHZ_,CLKMODE0,MCBL,HOLD_,TDI,TRST_,RESET_,		
              CLKMODE1);			                           
									
  PinListUnSet(INPUTS, MCBL);

  PinListSet (OUTPUTS, ABUS,HOLDA_,IACK_,PAGE3_,PAGE2_,PAGE1_,PAGE0_,	
              RW_,STRB_,TDO,X1); 	       			        

  PinListSet (IOPINS, DBUS,XF1,XF0,SPPINS,TPINS,EMU0,EMU1,RSV0,RSV1);   













  PinListSet (EVENPINS, A20,A18,A16,A14,A12,A10,A8,A6,A4,A2,A0,
              PAGE2_,PAGE0_,RW_,H3,HOLDA_,RDY_,D30,D28,D26,D24,
              D22,D20,D18,D16,D14,D12,D10,D8,D6,D4,D2,D0,EMU0,
              TDO,TMS,DR0,CLKR0,FSX0,TCLK1,XF1,INT3_,INT1_,
              EDGEMODE,SHZ_,CLKMODE0,X2CLKIN,RSV1,MCBL,A22);

  PinListSet (ODDPINS, A21,A19,A17,A15,A13,A11,A9,A7,A5,A3,A1,
              PAGE3_,PAGE1_,STRB_,H1,IACK_,HOLD_,D31,D29,D27,
              D25,D23,D21,D19,D17,D15,D13,D11,D9,D7,D5,D3,D1,
              EMU1,TCK,TDI,TRST_,FSR0,CLKX0,DX0,TCLK0,XF0,INT2_,
              INT0_,RESET_,CLKMODE1,X1,EXTCLK,RSV0,A23);

  PinListSet (ALLPINS, EVENPINS, ODDPINS);	 


  PinListSet (OPENPINS,
	      HOLDA_,STRB_,RESET_,XF0,INT0_,INT2_,DR0,FSR0,CLKX0,DX0,
	      TCLK1,A23,A21,A19,A17,A15,A12,A10,A8,A6,A4,A2,A0,EMU1,MCBL,
	      D30,D28,D26,D25,D23,D21,D19,D17,D15,D13,D11,D9,D7,D5,D3,D1,H1,
              X2CLKIN,HOLD_,RDY_,RW_,XF1,IACK_,INT1_,INT3_,CLKR0,FSX0,
	      TCLK0,A22,A20,A18,A16,A14,A13,A11,A9,A7,A5,A3,A1,EMU0,SHZ_,
	      D31,D29,D27,D24,D22,D20,D18,D16,D14,D12,D10,D8,D6,D4,D2,D0,H3,
              CLKMODE0,CLKMODE1,PAGE0_,PAGE1_,PAGE2_,PAGE3_,EDGEMODE,
              EXTCLK,RSV0,RSV1,TCK,TDO,TDI,TMS,TRST_,X1);









  PinListSet (EVENINS, RDY_, EDGEMODE, SHZ_, CLKMODE0,
              INT0_,INT2_);            		                        

  PinListSet (ODDINS,HOLD_, RESET_, CLKMODE1,
              INT1_,INT3_,MCBL);                                       	

  PinListSet (INPU_1, TDI, TCK, TMS);                                  
  PinListSet (INPD_1, TRST_);                                            

  PinListSet (TESTINS, ODDINS, EVENINS, X2CLKIN);                       


  PinListSet (NOTESTINS, INPU_1, INPD_1);                               
                                                                        

  PinListSet (ALLOUTS, OUTPUTS,H1,H3);		   
						   

  PinListSet (ICCQDisconnectPinList, OUTPUTS,H1,H3,TCK);

  PinListSet (ALLIOS, IOPINS);  		   
	      					   
						   



  PinListSet (EVENTRISTATE, A22,A20,A18,A16,A14,A12,A10,A8,A6,
             A4,A2,A0,PAGE3_,PAGE0_,HOLDA_,IACK_,D30,D28,D26,D24,
             D22,D20,D18,D16,D14,D12,D10,D8,D6,D4,D2,D0,DR0,
             CLKR0,FSX0,TCLK1,XF1);

  PinListSet (ODDTRISTATE,A23,A21,A19,A17,A15,A13,A11,A9,A7,
             A5,A3,A1,STRB_,PAGE2_,PAGE1_,RW_,D31,D29,D27,D25,D23,
             D21,D19,D17,D15,D13,D11,D9,D7,D5,D3,D1,FSR0,
	     CLKX0,DX0,TCLK0,XF0);

  PinListSet (NOTRISTATEIO, RSV0, RSV1, EMU0, EMU1);

  PinListSet (ALLTRISTATE,EVENTRISTATE,ODDTRISTATE);


  PinListSet (MUXPINS, EXTCLK);

  PinListSet (PMUTRIS, INT0_,INT1_,INT2_,INT3_,	MCBL);    


  PinListSet (FIELD1,  DBUS);   		   			
  PinListSet (FIELD2,  ABUS);			   			
  PinListSet (FIELD3,  XF0,XF1);		   			
  PinListSet (FIELD4,  CLKX0,CLKR0,DX0,DR0,FSX0,FSR0); 		   	
  PinListSet (FIELD5,  TCLK0,TCLK1);		   			
  PinListSet (FIELD6,  RW_,STRB_,RDY_,HOLD_,HOLDA_);	          	
  PinListSet (FIELD7,  RESET_,MCBL,SHZ_,IACK_);    			
  PinListSet (FIELD8,  EMU0,EMU1,RSV0,RSV1);				
  PinListSet (FIELD9,  INT3_,INT2_,INT1_,INT0_); 			
  PinListSet (FIELD10, X2CLKIN,H1,H3);					
  PinListSet (FIELD11, EXTCLK,X1);		   			
  PinListSet (FIELD12, TCK,TDI,TDO,TMS,TRST_);	   			
  PinListSet (FIELD13, PAGE0_,PAGE1_,PAGE2_,PAGE3_);			
  PinListSet (FIELD14, CLKMODE0,CLKMODE1,EDGEMODE);          		
end;


