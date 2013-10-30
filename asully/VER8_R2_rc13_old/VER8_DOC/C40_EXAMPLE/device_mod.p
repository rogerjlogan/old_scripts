


































 




 










	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
	
	


procedure DeviceTableSet;

const
  MINV    =  -2v;           
  MAXV    =   8v;           
  MINI    = -50ma;          
  MAXI    =  50ma;          
  MINVSUB =  -5v;           
  MINVDD  =  -2v;           
  MAXVDD  =   8v;           
  MINVDDI = -200000;        
  MAXVDDI = 2000000;        

var
  devicetablename : String;


begin

 case TITestType of
 Probe:
 begin

 if (pg5patt) then     
  begin
   DeviceTableOpen;

   devicetablename := 'TMS320C40ProbeDeviceTable';
   DeviceTableSetName(devicetablename);








 
 
 

   PinSetMP(GD31,         1,  {F32}  248,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD30,         2,  {E31}  247,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD29,         3,  {H30}  216,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD28,         4,  {C33}   96,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD27,         5,  {G31}  215,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD26,         6,  {D34}   95,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD25,         8,  {E33}  176,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD24,         9,  {H32}   56,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD23,        10,  {F34}  175,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD22,        11,  {K30}   55,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD21,        12,  {G33}  136,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD20,        13,  {J31}   16,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD19,        14,  {H34}  135,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD18,        15,  {K32}   15,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD17,        16,  {M30}  214,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD16,        17,  {L31}   94,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD15,        22,  {J33}  213,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD14,        23,  {M32}   93,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD13,        24,  {K34}  174,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD12,        25,  {N31}   54,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD11,        26,  {L33}  173,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD10,        27,  {P32}   53,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD9,         28,  {M34}  134,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD8,         29,  {R31}   14,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD7,         30,  {N33}  133,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD6,         31,  {T32}   13,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD5,         32,  {P34}  246,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD4,         34,  {R33}  245,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD3,         35,  {U31}  212,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD2,         36,  {T34}   92,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD1,         37,  {V32}  211,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GD0,         38,  {U33}   91,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GCE1_,       39,  {V34}  172,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GRDY1_,      40,  {W31}   52,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GLOCK_,      43,  {W33}  171,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GCE0_,       46, {AA33}   51,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GRDY0_,      47,  {Y32}  132,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GDE_,        48, {AA31}   12,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(TCK,         49,  {Y34}  131,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(TDO,         50, {AB34}   11,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(TDI,         51, {AC35}  210,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(TMS,         52,  {W35}   90,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(TRS,         53, {AE35}  209,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(EMU0,        54, {AA35}   89,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(EMU1,        55, {AD34}  170,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GPAGE1,      58, {AB32}   50,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GRW1_,       59, {AC31}  169,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GSTRB1_,     60, {AC33}   49,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GSTAT0,      61, {AD32}  130,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GSTAT1,      62, {AE33}   10,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GSTAT2,      64, {AF34}  129,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GSTAT3,      65, {AE31}    9,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GPAGE0,      66, {AG33}  244,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GRW0_,       67, {AF32}  243,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GSTRB0_,     68, {AD30}  208,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GAE_,        69, {AG31}   88,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(RESETLOC1,   70, {AH34}  207,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(RESETLOC0,   72, {AF30}   87,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(RESET_,      73, {AJ33}  168,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CRDY5_,      74, {AH32}   48,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CSTRB5_,     75, {AK34}  167,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CACK5_,      76, {AJ31}   47,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CREQ5_,      77, {AL33}  128,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CRDY4_,      78, {AH30}    8,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CSTRB4_,     79, {AM34}  127,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CACK4_,      80, {AK32}    7,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CREQ4_,      81, {AN33}  206,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C5D7,        85, {AL31}   86,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C5D6,        86, {AM32}  205,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C5D5,        87, {AP32}   85,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C5D4,        88, {AM30}  166,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C5D3,        89, {AN31}   46,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C5D2,        90, {AK28}  165,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C5D1,        91, {AP30}   45,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C5D0,        92, {AL29}  126,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C4D7,        94, {AM28}    6,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C4D6,        95, {AN29}  125,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C4D5,        96, {AK26}    5,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C4D4,        97, {AP28}  242,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C4D3,        98, {AL27}  241,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C4D2,        99, {AK24}  204,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C4D1,       100, {AM26}   84,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C4D0,       101, {AN27}  203,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C3D7,       105, {AP26}   83,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C3D6,       106, {AL25}  164,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C3D5,       107, {AN25}   44,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C3D4,       108, {AM24}  163,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C3D3,       109, {AP24}   43,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C3D2,       110, {AL23}  124,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C3D1,       111, {AN23}    4,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C3D0,       112, {AM22}  123,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C2D7,       115, {AP22}    3,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C2D6,       116, {AL21}  202,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C2D5,       117, {AN21}   82,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C2D4,       118, {AM20}  201,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C2D3,       119, {AP20}   81,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C2D2,       120, {AL19}  162,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C2D1,       121, {AN19}   42,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C2D0,       122, {AM18}  161,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CRDY3_,     126, {AL17}   41,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CSTRB3_,    127, {AP18}  122,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CACK3_,     128, {AM16}    2,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CREQ3_,     129, {AN17}  121,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CRDY2_,     132, {AL15}    1,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CSTRB2_,    133, {AP16}  240,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CACK2_,     134, {AM14}  120,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CREQ2_,     135, {AN15}  239,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CRDY1_,     137, {AP14}  119,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CSTRB1_,    138, {AL13}  200,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CACK1_,     139, {AN13}   80,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CREQ1_,     140, {AM12}  199,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CRDY0_,     141, {AP12}   79,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CSTRB0_,    142, {AL11}  160,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CACK0_,     143, {AN11}   40,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(CREQ0_,     144, {AM10}  159,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C1D7,       149, {AP10}   39,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C1D6,       150,  {AL9}  238,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C1D5,       151,  {AN9}  118,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C1D4,       152, {AK10}  237,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C1D3,       153, {AK12}  117,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C1D2,       154,  {AM8}  198,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C1D1,       155,  {AP8}   78,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C1D0,       156,  {AL7}  197,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C0D7,       158,  {AK8}   77,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C0D6,       159,  {AN7}  158,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C0D5,       160,  {AM6}   38,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C0D4,       161,  {AP6}  157,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C0D3,       162,  {AM4}   37,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C0D2,       163,  {AN5}  256,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C0D1,       164,  {AL5}  255,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(C0D0,       165,  {AP4}  236,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(ROMEN,      168,  {AK4}  116,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(IIOF0,      169,  {AN3}  235,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(IIOF1,      171,  {AL3}  115,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(IIOF2,      172,  {AH6}  196,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(IIOF3,      173,  {AK2}   76,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(NMI_,       174,  {AJ5}  195,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LSTRB0_,    175,  {AJ3}   75,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LRW0_,      176,  {AH4}  156,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LPAGE0,     177,  {AH2}   36,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LRDY0_,     178,  {AF6}  155,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LCE0_,      179,  {AG5}   35,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LSTRB1_,    180,  {AD6}  234,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LRW1_,      181,  {AF4}  114,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LPAGE1,     184,  {AG3}  233,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LRDY1_,     185,  {AE5}  113,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LCE1_,      186,  {AF2}  194,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LDE_,       187,  {AD4}   74,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(TCLK0,      188,  {AE3}  193,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(TCLK1,      189,  {AD2}   73,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(H3,         190,  {AC5}  154,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(H1,         191,  {AC3}   34,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LAE_,       192,  {AB4}  153,    {I }   I,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LLOCK_,     194,  {AA5}   33,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LSTAT0,     195,  {AA3}  254,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LSTAT1,     196,   {Y4}  253,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LSTAT2,     197,   {Y2}  232,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LSTAT3,     198,   {W5}  112,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(IACK_,      199,   {W3}  231,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(X1,         202,   {W1}  111,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA30,       207,   {U5}   72,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA29,       208,   {V4}   71,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA28,       209,   {T4}  152,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA27,       210,   {U3}   32,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA26,       212,   {T2}  151,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA25,       213,   {R5}   31,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA24,       214,   {R3}  230,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA23,       215,   {P4}  110,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA22,       216,   {P2}  229,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA21,       217,   {N5}  109,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA20,       218,   {N3}  190,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA19,       219,   {M4}   70,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA18,       220,   {M2}  189,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA17,       221,   {L5}   69,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA16,       222,   {L3}  150,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA15,       226,   {K2}   30,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA14,       227,   {K4}  149,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA13,       228,   {J3}   29,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA12,       229,   {J5}  252,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA11,       230,   {M6}  251,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA10,       231,   {K6}  228,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA9,        232,   {H2}  108,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA8,        233,   {H4}  227,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA7,        234,   {G3}  107,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA6,        235,   {G5}  188,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA5,        236,   {F2}   68,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA4,        237,   {H6}  187,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA3,        239,   {F4}   67,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA2,        240,   {E3}  148,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA1,        241,   {D4}   28,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LA0,        242,   {D2}  147,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD31,       245,   {F6}   27,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD30,       246,   {E5}  226,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD29,       247,   {C3}  106,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD28,       248,   {D6}  225,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD27,       250,   {F8}  105,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD26,       251,   {B4}  186,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD25,       252,   {E7}   66,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD24,       253,   {C5}  185,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD23,       254,   {D8}   65,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD22,       255,   {B6}  146,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD21,       256,  {F10}   26,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD20,       257,   {C7}  145,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD19,       258,   {E9}   25,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD18,       259,   {B8}  250,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD17,       260,  {D10}  249,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD16,       265,  {F12}  224,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD15,       266,  {E11}  104,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD14,       267,   {C9}  223,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD13,       268,  {D12}  103,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD12,       269,  {B10}  184,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD11,       270,  {E13}   64,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD10,       271,  {C11}  183,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD9,        272,  {D14}   63,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD8,        273,  {B12}  144,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD7,        274,  {E15}   24,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD6,        275,  {C13}  143,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD5,        276,  {D16}   23,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD4,        278,  {E17}  222,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD3,        279,  {B14}  102,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD2,        280,  {D18}  221,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD1,        281,  {C15}  101,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(LD0,        282,  {E19}  182,    {IO}  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA30,       287,  {B16}   62,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA29,       288,  {D20}  181,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA28,       289,  {C17}   61,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA27,       291,  {B18}  142,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA26,       292,  {E21}   22,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA25,       293,  {B20}  141,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA24,       294,  {D22}   21,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA23,       295,  {C19}  220,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA22,       296,  {E23}  100,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA21,       297,  {B22}  219,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA20,       298,  {D24}   99,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA19,       299,  {C21}  180,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA18,       300,  {E25}   60,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA17,       301,  {B24}  179,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA16,       305,  {C23}   59,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA15,       306,  {D26}  140,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA14,       307,  {B26}   20,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA13,       308,  {E27}  139,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA12,       309,  {C25}   19,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA11,       310,  {F26}  218,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA10,       311,  {B28}   98,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA9,        312,  {D28}  217,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA8,        313,  {C27}   97,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA7,        314,  {E29}  178,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA6,        315,  {F24}   58,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA5,        316,  {F28}  177,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA4,        317,  {B30}   57,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA3,        319,  {C29}  138,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA2,        320,  {D30}   18,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA1,        321,  {B32}  137,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);
   PinSetMP(GA0,        322,  {D32}   17,    {O }  IO,  MINV,   MAXV,   MINI,   MAXI);      

   PinSetMuxMP(X2CLKIN, 203,  {AA1}  191,192, {I}   I,  MINV,   MAXV,   MINI,   MAXI);

   PinSetSupply(VDD,   44,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
   PinSetSupply(DVDD,   7,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
   PinSetSupply(VSUB, 325,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
   PinSetSupply(VSS,   18,     Ground,        0,       0,       0,       0   );

   
   
   
   
   
   
   
   
   
   
   
   
   

   DeviceTableClose;
  end 
 else             
  begin

 DeviceTableOpen;

 devicetablename := 'TMS320C40ProbeDeviceTable';
 DeviceTableSetName(devicetablename);

 
 

  PinSetMP(GD31,         1,  {F32}  205,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD30,         2,  {E31}   46,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD29,         3,  {H30}  166,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD28,         4,  {C33}   45,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD27,         5,  {G31}  165,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD26,         6,  {D34}    6,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD25,         8,  {E33}  126,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD24,         9,  {H32}    5,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD23,        10,  {F34}  125,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD22,        11,  {K30}  241,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD21,        12,  {G33}  242,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD20,        13,  {J31}   84,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD19,        14,  {H34}  204,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD18,        15,  {K32}   83,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD17,        16,  {M30}  203,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD16,        17,  {L31}   44,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD15,        22,  {J33}  164,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD14,        23,  {M32}   43,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD13,        24,  {K34}  163,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD12,        25,  {N31}    4,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD11,        26,  {L33}  124,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD10,        27,  {P32}    3,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD9,         28,  {M34}  123,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD8,         29,  {R31}   82,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD7,         30,  {N33}  202,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD6,         31,  {T32}   81,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD5,         32,  {P34}  201,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD4,         34,  {R33}   42,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD3,         35,  {U31}  162,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD2,         36,  {T34}   41,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD1,         37,  {V32}  161,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD0,         38,  {U33}    2,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GCE1_,       39,  {V34}  122,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRDY1_,      40,  {W31}    1,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GLOCK_,      43,  {W33}  121, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GCE0_,       46, {AA33}  120,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRDY0_,      47,  {Y32}  240,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GDE_,        48, {AA31}  119,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCK,         49,  {Y34}  239,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TDO,         50, {AB34}   80, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TDI,         51, {AC35}  200,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TMS,         52,  {W35}   79,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TRS,         53, {AE35}  199,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(EMU0,        54, {AA35}   40,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(EMU1,        55, {AD34}  160,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GPAGE1,      58, {AB32}   39, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRW1_,       59, {AC31}  159, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTRB1_,     60, {AC33}  118, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT0,      61, {AD32}  238, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT1,      62, {AE33}  117, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT2,      64, {AF34}  237, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT3,      65, {AE31}   78, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GPAGE0,      66, {AG33}  198, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRW0_,       67, {AF32}   77, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTRB0_,     68, {AD30}  197, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GAE_,        69, {AG31}   38,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESETLOC1,   70, {AH34}  158,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESETLOC0,   72, {AF30}   37,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESET_,      73, {AJ33}  157,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY5_,      74, {AH32}  255,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB5_,     75, {AK34}  256,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK5_,      76, {AJ31}  116,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ5_,      77, {AL33}  236,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY4_,      78, {AH30}  115,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB4_,     79, {AM34}  235,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK4_,      80, {AK32}   76,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ4_,      81, {AN33}  196,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D7,        85, {AL31}   75,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D6,        86, {AM32}  195,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D5,        87, {AP32}   36,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D4,        88, {AM30}  156,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D3,        89, {AN31}   35,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D2,        90, {AK28}  155,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D1,        91, {AP30}  114,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D0,        92, {AL29}  234,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D7,        94, {AM28}  113,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D6,        95, {AN29}  233,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D5,        96, {AK26}   74,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D4,        97, {AP28}  194,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D3,        98, {AL27}   73,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D2,        99, {AK24}  193,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D1,       100, {AM26}   34,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D0,       101, {AN27}  154,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D7,       105, {AP26}   33,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D6,       106, {AL25}  153,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D5,       107, {AN25}  253,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D4,       108, {AM24}  254,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D3,       109, {AP24}  112,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D2,       110, {AL23}  232,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D1,       111, {AN23}  111,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D0,       112, {AM22}  231,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D7,       115, {AP22}   72,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D6,       116, {AL21}  192,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D5,       117, {AN21}   71,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D4,       118, {AM20}  191,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D3,       119, {AP20}   32,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D2,       120, {AL19}  152,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D1,       121, {AN19}   31,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D0,       122, {AM18}  151,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY3_,     126, {AL17}  110,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB3_,    127, {AP18}  230,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK3_,     128, {AM16}  109,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ3_,     129, {AN17}  229,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY2_,     132, {AL15}   70,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB2_,    133, {AP16}  190,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK2_,     134, {AM14}   69,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ2_,     135, {AN15}  189,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY1_,     137, {AP14}   30,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB1_,    138, {AL13}  150,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK1_,     139, {AN13}   29,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ1_,     140, {AM12}  149,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY0_,     141, {AP12}  251,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB0_,    142, {AL11}  252,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK0_,     143, {AN11}  108,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ0_,     144, {AM10}  228,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D7,       149, {AP10}  107,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D6,       150,  {AL9}  227,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D5,       151,  {AN9}   68,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D4,       152, {AK10}  188,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D3,       153, {AK12}   67,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D2,       154,  {AM8}  187,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D1,       155,  {AP8}   28,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D0,       156,  {AL7}  148,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D7,       158,  {AK8}   27,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D6,       159,  {AN7}  147,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D5,       160,  {AM6}  106,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D4,       161,  {AP6}  226,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D3,       162,  {AM4}  105,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D2,       163,  {AN5}  225,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D1,       164,  {AL5}   66,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D0,       165,  {AP4}  186,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(ROMEN,      168,  {AK4}   65,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF0,      169,  {AN3}  185,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF1,      171,  {AL3}   26,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF2,      172,  {AH6}  146,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF3,      173,  {AK2}   25,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(NMI_,       174,  {AJ5}  145,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTRB0_,    175,  {AJ3}  249, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRW0_,      176,  {AH4}  250, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LPAGE0,     177,  {AH2}  104, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRDY0_,     178,  {AF6}  224,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LCE0_,      179,  {AG5}  103,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTRB1_,    180,  {AD6}  223, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRW1_,      181,  {AF4}   64, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LPAGE1,     184,  {AG3}  184, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRDY1_,     185,  {AE5}   63,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LCE1_,      186,  {AF2}  183,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LDE_,       187,  {AD4}   24,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCLK0,      188,  {AE3}  144,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCLK1,      189,  {AD2}   23,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(H3,         190,  {AC5}  143, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(H1,         191,  {AC3}  102, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LAE_,       192,  {AB4}  222,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LLOCK_,     194,  {AA5}  101, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT0,     195,  {AA3}  221, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT1,     196,   {Y4}   62, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT2,     197,   {Y2}  182, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT3,     198,   {W5}   61, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IACK_,      199,   {W3}  181, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(X1,         202,   {W1}  142, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA30,       207,   {U5}  141, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA29,       208,   {V4}  100, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA28,       209,   {T4}  220, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA27,       210,   {U3}   99, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA26,       212,   {T2}  219, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA25,       213,   {R5}   60, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA24,       214,   {R3}  180, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA23,       215,   {P4}   59, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA22,       216,   {P2}  179, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA21,       217,   {N5}   20, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA20,       218,   {N3}  140, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA19,       219,   {M4}   19, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA18,       220,   {M2}  139, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA17,       221,   {L5}   98, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA16,       222,   {L3}  218, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA15,       226,   {K2}   97, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA14,       227,   {K4}  217, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA13,       228,   {J3}   58, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA12,       229,   {J5}  178, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA11,       230,   {M6}   57, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA10,       231,   {K6}  177, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA9,        232,   {H2}   18, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA8,        233,   {H4}  138, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA7,        234,   {G3}   17, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA6,        235,   {G5}  137, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA5,        236,   {F2}  247, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA4,        237,   {H6}  248, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA3,        239,   {F4}   96, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA2,        240,   {E3}  216, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA1,        241,   {D4}   95, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA0,        242,   {D2}  215, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD31,       245,   {F6}   56,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD30,       246,   {E5}  176,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD29,       247,   {C3}   55,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD28,       248,   {D6}  175,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD27,       250,   {F8}   16,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD26,       251,   {B4}  136,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD25,       252,   {E7}   15,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD24,       253,   {C5}  135,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD23,       254,   {D8}   94,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD22,       255,   {B6}  214,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD21,       256,  {F10}   93,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD20,       257,   {C7}  213,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD19,       258,   {E9}   54,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD18,       259,   {B8}  174,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD17,       260,  {D10}   53,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD16,       265,  {F12}  173,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD15,       266,  {E11}   14,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD14,       267,   {C9}  134,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD13,       268,  {D12}   13,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD12,       269,  {B10}  133,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD11,       270,  {E13}  245,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD10,       271,  {C11}  246,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD9,        272,  {D14}   92,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD8,        273,  {B12}  212,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD7,        274,  {E15}   91,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD6,        275,  {C13}  211,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD5,        276,  {D16}   52,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD4,        278,  {E17}  172,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD3,        279,  {B14}   51,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD2,        280,  {D18}  171,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD1,        281,  {C15}   12,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD0,        282,  {E19}  132,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA30,       287,  {B16}   11, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA29,       288,  {D20}  131, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA28,       289,  {C17}   90, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA27,       291,  {B18}  210, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA26,       292,  {E21}   89, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA25,       293,  {B20}  209, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA24,       294,  {D22}   50, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA23,       295,  {C19}  170, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA22,       296,  {E23}   49, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA21,       297,  {B22}  169, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA20,       298,  {D24}   10, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA19,       299,  {C21}  130, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA18,       300,  {E25}    9, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA17,       301,  {B24}  129, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA16,       305,  {C23}  243, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA15,       306,  {D26}  244, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA14,       307,  {B26}   88, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA13,       308,  {E27}  208, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA12,       309,  {C25}   87, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA11,       310,  {F26}  207, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA10,       311,  {B28}   48, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA9,        312,  {D28}  168, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA8,        313,  {C27}   47, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA7,        314,  {E29}  167, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA6,        315,  {F24}    8, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA5,        316,  {F28}  128, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA4,        317,  {B30}    7, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA3,        319,  {C29}  127, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA2,        320,  {D30}   86, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA1,        321,  {B32}  206, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA0,        322,  {D32}   85, {O}IO,  MINV,   MAXV,   MINI,   MAXI);

  PinSetMuxMP(X2CLKIN, 203,  {AA1}   21,22,  I,  MINV,   MAXV,   MINI,   MAXI);


  PinSetSupply(VDD,   44,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(DVDD,   7,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSUB, 325,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSS,   18,     Ground,        0,       0,       0,       0   );

 
 
 
 
 
 
 
 
 
 
 
 
 

 DeviceTableClose;

 end; 
end;  
 Pre_Burnin, Final, QA, Final_QA:
 begin 

 case TIDeviceType of
 SMJ320C40GFM_pg3x_40MHz, SMJ320C40GFM_pg5x_40MHz, SMJ320C40GFM_pg5x_50MHz,
 SMJ320C40GFM_pg5x_60MHz, MPM11856KGDC:
 begin

 DeviceTableOpen;
 devicetablename := 'TMS320C40PackageDeviceTable';
 DeviceTableSetName(devicetablename);

 
 

  PinSetMP(GD31,         1,  {F32}    5,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD30,         2,  {E31}  165,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD29,         3,  {H30}  166,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD28,         4,  {C33}   86,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD27,         5,  {G31}  126,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD26,         6,  {D34}   46,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD25,         8,  {E33}   45,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD24,         9,  {H32}  242,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD23,        10,  {F34}  125,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD22,        11,  {K30}   83,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD21,        12,  {G33}    6,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD20,        13,  {J31}  204,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD19,        14,  {H34}  241,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD18,        15,  {K32}   44,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD17,        16,  {M30}  163,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD16,        17,  {L31}   84,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD15,        22,  {J33}  203,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD14,        23,  {M32}    4,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD13,        24,  {K34}   43,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD12,        25,  {N31}   81,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD11,        26,  {L33}  164,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD10,        27,  {P32}  123,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD9,         28,  {M34}    3,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD8,         29,  {R31}   82,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD7,         30,  {N33}  124,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD6,         31,  {T32}   42,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD5,         32,  {P34}  162,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD4,         34,  {R33}  161,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD3,         35,  {U31}  121,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD2,         36,  {T34}  122,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD1,         37,  {V32}  240,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD0,         38,  {U33}  202,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GCE1_,       39,  {V34}  201,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRDY1_,      40,  {W31}  239,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GLOCK_,      43,  {W33}    2, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GCE0_,       46, {AA33}   80,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRDY0_,      47,  {Y32}  200,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GDE_,        48, {AA31}  199,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCK,         49,  {Y34}  120,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TDO,         50, {AB34}  129, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TDI,         51, {AC35}    1,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TMS,         52,  {W35}   41,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TRS,         53, {AE35}  118,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(EMU0,        54, {AA35}  119,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(EMU1,        55, {AD34}   40,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GPAGE1,      58, {AB32}  160, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRW1_,       59, {AC31}  159, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTRB1_,     60, {AC33}   79, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT0,      61, {AD32}  238, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT1,      62, {AE33}   39, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT2,      64, {AF34}  117, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT3,      65, {AE31}  237, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GPAGE0,      66, {AG33}   78, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRW0_,       67, {AF32}  197, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTRB0_,     68, {AD30}   37, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GAE_,        69, {AG31}  158,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESETLOC1,   70, {AH34}   77,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESETLOC0,   72, {AF30}  198,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESET_,      73, {AJ33}   38,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY5_,      74, {AH32}  157,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB5_,     75, {AK34}  255,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK5_,      76, {AJ31}  256,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ5_,      77, {AL33}  235,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY4_,      78, {AH30}  236,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB4_,     79, {AM34}  196,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK4_,      80, {AK32}  116,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ4_,      81, {AN33}  156,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D7,        85, {AL31}  195,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D6,        86, {AM32}  115,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D5,        87, {AP32}   75,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D4,        88, {AM30}   76,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D3,        89, {AN31}  234,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D2,        90, {AK28}  233,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D1,        91, {AP30}   35,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D0,        92, {AL29}  155,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D7,        94, {AM28}  114,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D6,        95, {AN29}  194,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D5,        96, {AK26}   36,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D4,        97, {AP28}  113,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D3,        98, {AL27}  193,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D2,        99, {AK24}   34,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D1,       100, {AM26}  154,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D0,       101, {AN27}   74,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D7,       105, {AP26}  153,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D6,       106, {AL25}  232,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D5,       107, {AN25}   73,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D4,       108, {AM24}  231,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D3,       109, {AP24}   33,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D2,       110, {AL23}  192,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D1,       111, {AN23}  253,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D0,       112, {AM22}  191,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D7,       115, {AP22}  254,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D6,       116, {AL21}  111,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D5,       117, {AN21}  112,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D4,       118, {AM20}  152,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D3,       119, {AP20}  151,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D2,       120, {AL19}   71,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D1,       121, {AN19}   72,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D0,       122, {AM18}  230,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY3_,     126, {AL17}  229,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB3_,    127, {AP18}   32,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK3_,     128, {AM16}  190,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ3_,     129, {AN17}   31,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY2_,     132, {AL15}  150,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB2_,    133, {AP16}  189,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK2_,     134, {AM14}  149,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ2_,     135, {AN15}  110,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY1_,     137, {AP14}  109,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB1_,    138, {AL13}  252,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK1_,     139, {AN13}   70,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ1_,     140, {AM12}  228,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY0_,     141, {AP12}   69,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB0_,    142, {AL11}  188,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK0_,     143, {AN11}  227,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ0_,     144, {AM10}  187,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D7,       149, {AP10}   29,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D6,       150,  {AL9}  148,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D5,       151,  {AN9}  251,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D4,       152, {AK10}   30,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D3,       153, {AK12}  186,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D2,       154,  {AM8}  147,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D1,       155,  {AP8}  108,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D0,       156,  {AL7}  226,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D7,       158,  {AK8}  107,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D6,       159,  {AN7}   68,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D5,       160,  {AM6}  225,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D4,       161,  {AP6}   67,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D3,       162,  {AM4}  185,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D2,       163,  {AN5}   28,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D1,       164,  {AL5}  105,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D0,       165,  {AP4}   27,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(ROMEN,      168,  {AK4}  145,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF0,      169,  {AN3}  106,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF1,      171,  {AL3}   66,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF2,      172,  {AH6}   25,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF3,      173,  {AK2}   65,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(NMI_,       174,  {AJ5}  146,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTRB0_,    175,  {AJ3}   26, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRW0_,      176,  {AH4}  224, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LPAGE0,     177,  {AH2}  249, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRDY0_,     178,  {AF6}  250,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LCE0_,      179,  {AG5}  223,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTRB1_,    180,  {AD6}   23, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRW1_,      181,  {AF4}  184, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LPAGE1,     184,  {AG3}  104, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRDY1_,     185,  {AE5}  183,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LCE1_,      186,  {AF2}  103,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LDE_,       187,  {AD4}  144,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCLK0,      188,  {AE3}   64,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCLK1,      189,  {AD2}   63,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(H3,         190,  {AC5}  143, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(H1,         191,  {AC3}   24, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LAE_,       192,  {AB4}  222,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LLOCK_,     194,  {AA5}  221, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT0,     195,  {AA3}   62, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT1,     196,   {Y4}  182, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT2,     197,   {Y2}   61, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT3,     198,   {W5}  181, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IACK_,      199,   {W3}   21, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(X1,         202,   {W1}   22, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA30,       207,   {U5}  141, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA29,       208,   {V4}  142, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA28,       209,   {T4}  220, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA27,       210,   {U3}  100, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA26,       212,   {T2}   99, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA25,       213,   {R5}  180, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA24,       214,   {R3}  219, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA23,       215,   {P4}  179, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA22,       216,   {P2}   60, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA21,       217,   {N5}  140, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA20,       218,   {N3}   59, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA19,       219,   {M4}  139, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA18,       220,   {M2}   20, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA17,       221,   {L5}  218, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA16,       222,   {L3}   98, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA15,       226,   {K2}   97, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA14,       227,   {K4}  217, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA13,       228,   {J3}   58, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA12,       229,   {J5}  178, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA11,       230,   {M6}   19, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA10,       231,   {K6}  248, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA9,        232,   {H2}   57, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA8,        233,   {H4}  177, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA7,        234,   {G3}   18, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA6,        235,   {G5}  137, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA5,        236,   {F2}   17, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA4,        237,   {H6}  138, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA3,        239,   {F4}  247, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA2,        240,   {E3}   96, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA1,        241,   {D4}  176, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA0,        242,   {D2}  215, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD31,       245,   {F6}   55,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD30,       246,   {E5}   56,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD29,       247,   {C3}   95,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD28,       248,   {D6}   16,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD27,       250,   {F8}  213,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD26,       251,   {B4}  175,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD25,       252,   {E7}  135,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD24,       253,   {C5}  136,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD23,       254,   {D8}   94,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD22,       255,   {B6}   15,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD21,       256,  {F10}  216,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD20,       257,   {C7}  214,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD19,       258,   {E9}  174,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD18,       259,   {B8}   93,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD17,       260,  {D10}  173,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD16,       265,  {F12}   92,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD15,       266,  {E11}   14,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD14,       267,   {C9}   54,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD13,       268,  {D12}   13,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD12,       269,  {B10}   53,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD11,       270,  {E13}   91,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD10,       271,  {C11}  133,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD9,        272,  {D14}  134,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD8,        273,  {B12}  245,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD7,        274,  {E15}   51,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD6,        275,  {C13}  246,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD5,        276,  {D16}  211,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD4,        278,  {E17}  171,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD3,        279,  {B14}  212,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD2,        280,  {D18}  132,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD1,        281,  {C15}   52,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD0,        282,  {E19}  131,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA30,       287,  {B16}  172, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA29,       288,  {D20}  209, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA28,       289,  {C17}   12, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA27,       291,  {B18}   11, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA26,       292,  {E21}   50, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA25,       293,  {B20}   90, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA24,       294,  {D22}  169, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA23,       295,  {C19}  210, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA22,       296,  {E23}  130, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA21,       297,  {B22}   49, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA20,       298,  {D24}   87, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA19,       299,  {C21}   89, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA18,       300,  {E25}  244, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA17,       301,  {B24}    9, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA16,       305,  {C23}   10, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA15,       306,  {D26}  208, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA14,       307,  {B26}   88, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA13,       308,  {E27}    8, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA12,       309,  {C25}  243, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA11,       310,  {F26}   47, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA10,       311,  {B28}   48, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA9,        312,  {D28}  167, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA8,        313,  {C27}  168, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA7,        314,  {E29}    7, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA6,        315,  {F24}  170, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA5,        316,  {F28}  207, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA4,        317,  {B30}  127, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA3,        319,  {C29}  128, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA2,        320,  {D30}  206, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA1,        321,  {B32}  205, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA0,        322,  {D32}   85, {O}IO,  MINV,   MAXV,   MINI,   MAXI);

  PinSetMuxMP(X2CLKIN, 203,  {AA1}  101,102, I,  MINV,   MAXV,   MINI,   MAXI);


  PinSetSupply(VDD,   44,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(DVDD,   7,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSUB, 325,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSS,   18,     Ground,        0,       0,       0,       0   );

 
 
 
 
 
 
 
 
 
 
 
 
 

 DeviceTableClose;

 end; 

 TMS320C41QFP:
 begin 

 DeviceTableOpen;

 devicetablename := 'TMS320C41PackageDeviceTable';
 DeviceTableSetName(devicetablename); 

 
 

  PinSetMP(GPAGE0,       1,          25, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT3,       2,         146, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT2,       3,          66, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT1,       4,         145, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT0,       5,          65, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTRB1_,      6,         186, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRW1_,        7,          26, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GPAGE1,       8,         185, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(EMU1,         9,         105,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(EMU0,        10,         106,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TRS,         11,          27,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TMS,         12,         147,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TDI,         13,          28,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TDO,         14,         148, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCK,         15,          67,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GDE_,        16,         187,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRDY0_,      17,          68,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GCE0_,       18,         188,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GLOCK_,      19,         107, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRDY1_,      20,         108,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GCE1_,       21,         149,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD0,         22,          29,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD1,         23,          30,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD2,         24,         150,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD3,         25,          69,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD4,         26,         189,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD5,         27,          70,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD6,         28,         190,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD7,         29,         109,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD8,         30,         110,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD9,         31,          31,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD10,        32,         151,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD11,        33,          32,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD12,        34,         152,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD13,        35,          71,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD14,        36,         191,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD15,        37,          72,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD16,        38,         192,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD17,        39,         111,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD18,        40,         112,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD19,        41,          33,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD20,        42,         153,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD21,        43,          34,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD22,        44,         154,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD23,        45,         193,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD24,        46,         155,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD25,        47,          74,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD26,        48,          73,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD27,        49,          35,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD28,        50,         113,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD29,        51,         194,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD30,        52,          36,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD31,        53,         114,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA0,         66,          76, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA1,         67,          75, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA2,         68,         196, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA3,         69,         115, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA4,         70,         116, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA5,         71,          37, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA6,         72,         157, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA7,         73,          38, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA8,         74,         158, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA9,         75,          77, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA10,        76,         197, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA11,        77,          78, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA12,        78,         198, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA13,        79,         117, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA14,        80,         118, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA15,        81,          39, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA16,        82,         159, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA17,        83,         160, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA18,        84,          40, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA19,        85,          79, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA20,        86,         199, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA21,        87,          80, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA22,        88,         200, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA23,        89,         119, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA24,        90,         120, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD0,         91,           1,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD1,         92,         121,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD2,         93,           2,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD3,         94,         122,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD4,         95,          41,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD5,         96,         161,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD6,         97,          42,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD7,         98,         162,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD8,         99,          81,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD9,        100,          82,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD10,       101,           3,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD11,       102,         123,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD12,       103,           4,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD13,       104,          43,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD14,       105,         124,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD15,       106,         163,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD16,       107,         164,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD17,       108,          44,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD18,       109,          83,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD19,       110,           5,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD20,       111,          84,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD21,       112,         166,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD22,       113,          45,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD23,       114,         125,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD24,       115,          86,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD25,       116,         165,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD26,       117,           6,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD27,       118,          85,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD28,       119,          46,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD29,       120,         126,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD30,       133,           8,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD31,       134,          47,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA0,        135,          48, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA1,        136,         128, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA2,        137,         167, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA3,        138,         168, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA4,        139,          87, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA5,        140,          88, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA6,        141,           9, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA7,        142,         129, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA8,        143,         130, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA9,        144,          10, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA10,       145,          49, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA11,       146,         169, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA12,       147,          50, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA13,       148,         170, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA14,       149,          89, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA15,       150,          90, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA16,       151,          11, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA17,       152,         131, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA18,       153,          12, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA19,       154,         132, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA20,       155,          51, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA21,       156,         171, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA22,       157,          52, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(X1,         159,         172, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IACK_,      160,          13, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT3,     161,         133, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT2,     162,          14, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT1,     163,          53, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT0,     164,         134, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LLOCK_,     165,         173, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LAE_,       166,          54,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(H1,         167,         174, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(H3,         168,          93, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCLK0,      169,          94,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LDE_,       170,          15,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LCE1_,      171,         135,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRDY1_,     172,          95,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LPAGE1,     173,          55, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRW1_,      174,         136, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTRB1_,    175,         137, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LCE0_,      176,         176,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRDY0_,     177,          16,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LPAGE0,     178,          96, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRW0_,      179,          56, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTRB0_,    180,         175, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(NMI_,       181,          17,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF3,      182,         138,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF2,      183,         177,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF1,      184,          18,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF0,      185,          57,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(ROMEN,      186,          58,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ2_,     199,         178,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK2_,     200,          97,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB2_,    201,         139,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY2_,     202,          19,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ3_,     203,          98,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK3_,     204,          20,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB3_,    205,         140,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY3_,     206,          59,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D0,       207,         179,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D1,       208,          60,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D2,       209,         180,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D3,       210,          99,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D4,       211,         181,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D5,       212,          22,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D6,       213,         142,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D7,       214,          62,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D0,       215,         182,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D1,       216,          61,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D2,       217,         143,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D3,       218,         102,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D4,       219,         101,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D5,       220,          24,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D6,       221,         144,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D7,       222,          23,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESET_,     235,         184,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESETLOC0,  236,          63,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESETLOC1,  237,         183,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GAE_,       238,         104,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTRB0_,    239,         103, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRW0_,      240,          64, {O}IO,  MINV,   MAXV,   MINI,   MAXI);

  PinSetMuxMP(X2CLKIN, 158,          91,92,  I,  MINV,   MAXV,   MINI,   MAXI);


  PinSetSupply(VDD,   61,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(DVDD,  58,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSUB,  65,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSS,   54,     Ground,        0,       0,       0,       0   );

 
 
 
 
 
 
 
 

 DeviceTableClose;

 end; 

  SMJ320C40HFHM_pg3x_40MHz, SMJ320C40HFHM_pg5x_40MHz, SMJ320C40HFHM_pg5x_50MHz,
  SMJ320C40HFHM_pg5x_60MHz:
   begin

   case SystemClassGet of
    MegaOne:
     begin

 DeviceTableOpen;

 devicetablename := 'TMS320C40PackageDeviceTable';
 DeviceTableSetName(devicetablename);

 
 

  PinSetMP(GD31,	1,	65,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD30,	2,	185,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD29,	3,	66,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD28,	4,	186,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD27,	5,	105,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD26,	6,	225,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD25,	8,	106,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD24,	9,	226,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD23,	10,	27,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD22,	11,	147,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD21,	12,	28,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD20,	13,	148,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD19,	14,	67,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD18,	15,	187,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD17,	16,	68,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD16,	17,	188,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD15,	25,	107,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD14,	26,	227,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD13,	27,	108,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD12,	28,	228,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD11,	29,	251,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD10,	30,	252,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD9,		31,	29,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD8,		32,	149,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD7,		33,	30,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD6,		34,	150,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD5,		35,	69,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD4,		37,	189,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD3,		38,	70,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD2,		39,	190,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD1,		40,	109,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD0,		41,	229,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GCE1_,	42,	110,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GRDY1_,	43,	230,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GLOCK_,	48,	31,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GCE0_,	51,	151,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GRDY0_,	52,	32,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GDE_,	53,	152,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TCK,		54,	71,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TDO,		55,	191,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TDI,		56,	72,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TMS,		57,	192,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TRS,		58,	111,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(EMU0,	59,	231,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(EMU1,	60,	112,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GPAGE1,	64,	232,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GRW1_,	65,	253,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTRB1_,	66,	254,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTAT0,	67,	33,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTAT1,	68,	153,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTAT2,	70,	34,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTAT3,	71,	154,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GPAGE0,	72,	73,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GRW0_,	73,	193,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTRB0_,	74,	74,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GAE_,	75,	194,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(RESETLOC1, 	76,	 113,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(RESETLOC0, 	78,	 233,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(RESET_,	79,	114,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY5_,	80,	234,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB5_,	81,	35,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK5_,	82,	155,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ5_,	83,	36,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY4_,	84,	156,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB4_,	85,	75,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK4_,	86,	195,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ4_,	87,	76,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D7,	92,	196,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D6,	93,	115,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D5,	94,	235,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D4,	95,	116,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D3,	96,	236,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D2,	97,	255,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D1,	98,	256,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D0,	99,	37,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D7,	101,	157,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D6,	102,	38,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D5,	103,	158,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D4,	104,	77,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D3,	105,	197,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D2,	106,	78,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D1,	107,	198,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D0,	108,	117,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D7,	113,	237,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D6,	114,	118,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D5,	115,	238,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D4,	116,	39,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D3,	117,	159,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D2,	118,	40,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D1,	119,	160,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D0,	120,	79,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D7,	124,	199,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D6,	125,	80,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D5,	126,	200,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D4,	127,	119,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D3,	128,	239,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D2,	129,	120,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D1,	130,	240,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D0,	131,	1,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY3_,	136,	121,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB3_,	137,	2,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK3_,	138,	122,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ3_,	139,	41,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY2_,	142,	161,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB2_,	143,	42,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK2_,	144,	162,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ2_,	145,	81,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY1_,	147,	201,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB1_,	148,	82,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK1_,	149,	202,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ1_,	150,	3,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY0_,	151,	123,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB0_,	152,	4,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK0_,	153,	124,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ0_,	154,	43,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D7,	161,	163,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D6,	162,	44,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D5,	163,	164,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D4,	164,	83,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D3,	165,	203,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D2,	166,	84,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D1,	167,	204,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D0,	168,	241,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D7,	170,	242,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D6,	171,	5,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D5,	172,	125,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D4,	173,	6,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D3,	174,	126,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D2,	175,	45,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D1,	176,	165,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D0,	177,	46,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(ROMEN,	180,	166,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IIOF0,	181,	85,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IIOF1,	184,	205,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IIOF2,	185,	86,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IIOF3,	186,	206,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(NMI_,	187,	7,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTRB0_,	188,	127,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LRW0_,	189,	8,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LPAGE0,	190,	128,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LRDY0_,	191,	47,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LCE0_,	192,	167,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTRB1_,	193,	48,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LRW1_,	194,	168,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LPAGE1,	197,	87,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LRDY1_,	198,	207,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LCE1_,	199,	88,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LDE_,	200,	208,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TCLK0,	201,	243,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TCLK1,	202,	244,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(H3,		203,	9,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(H1,		204,	129,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LAE_,	205,	10,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LLOCK_,	207,	130,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTAT0,	208,	49,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTAT1,	209,	169,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTAT2,	210,	50,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTAT3,	211,	170,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IACK_,	212,	209,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(X1,		215,	210,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA30,	222,	11,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA29,	223,	131,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA28,	224,	12,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA27,	225,	132,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA26,	227,	51,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA25,	228,	171,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA24,	229,	52,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA23,	230,	172,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA22,	231,	91,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA21,	232,	211,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA20,	233,	92,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA19,	234,	212,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA18,	235,	245,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA17,	236,	246,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA16,	237,	13,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA15,	244,	133,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA14,	245,	14,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA13,	246,	134,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA12,	247,	53,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA11,	248,	173,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA10,	249,	54,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA9,		250,	174,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA8,		251,	93,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA7,		252,	213,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA6,		253,	94,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA5,		254,	214,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA4,		255,	15,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA3,		257,	135,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA2,		258,	16,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA1,		259,	136,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA0,		260,	55,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD31,	264,	175,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD30,	265,	56,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD29,	266,	176,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD28,	267,	95,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD27,	269,	215,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD26,	270,	96,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD25,	271,	216,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD24,	272,	248,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD23,	273,	17,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD22,	274,	247,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD21,	275,	137,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD20,	276,	18,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD19,	277,	138,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD18,	278,	57,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD17,	279,	177,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD16,	286,	58,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD15,	287,	178,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD14,	288,	97,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD13,	289,	217,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD12,	290,	98,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD11,	291,	218,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD10,	292,	19,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD9,		293,	139,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD8,		294,	20,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD7,		295,	140,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD6,		296,	59,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD5,		297,	179,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD4,		299,	180,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD3,		300,	99,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD2,		301,	60,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD1,		302,	219,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD0,		303,	100,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA30,	310,	220,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA29,	311,	21,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA28,	312,	141,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA27,	314,	22,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA26,	315,	142,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA25,	316,	61,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA24,	317,	181,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA23,	318,	62,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA22,	319,	182,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA21,	320,	101,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA20,	321,	221,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA19,	322,	102,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA18,	323,	23,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA17,	324,	222,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA16,	331,	143,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA15,	332,	24,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA14,	333,	144,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA13,	334,	63,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA12,	335,	183,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA11,	336,	64,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA10,	337,	184,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA9,		338,	103,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA8,		339,	223,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA7,		340,	104,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA6,		341,	224,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA5,		342,	249,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA4,		343,	250,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA3,		345,	25,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA2,		346,	145,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA1,		347,	26,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA0,		348,	146,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);

  PinSetMuxMP(X2CLKIN, 216,	 89,90,	 I,	MINV,	MAXV,	MINI,	MAXI);

  PinSetSupply(VDD,   49,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(DVDD,   7,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSUB, 352,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSS,   18,     Ground,        0,       0,       0,       0   );


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 DeviceTableClose;

   end;      

Polaris50, Polaris100: 
   begin
 
     if not motherboard then
     begin
                                      
 DeviceTableOpen;
 devicetablename := 'TMS320C40PackageDeviceTable';
 DeviceTableSetName(devicetablename);

 
 

   PinSet(GD31,  	1,	67,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD30,  	2,	199,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD29,  	3,	68,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD28,  	4,	197,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD27,  	5,	131,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD26,  	6,	198,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD25,  	8,	72,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD24,  	9,	136,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD23,  	10,	134,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD22,  	11,	71,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD21,  	12,	135,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD20,  	13,	133,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD19,  	14,	194,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD18,  	15,	193,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD17,  	16,	256,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD16,  	17,	70,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD15,  	25,	69,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD14,  	26,	255,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD13,	        27,	66,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD12,   	28,	65,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD11,  	29,	130,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD10,  	30,	129,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD9,   	31,	252,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD8,   	32,	251,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD7,   	33,	124,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD6,   	34,	123,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD5,   	35,	254,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD4,   	37,	6,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD3,   	38,	253,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD2,   	39,	250,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD1,   	40,	249,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GD0,   	41,	5,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GCE1_,  	42,	2,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GRDY1_,        43,	128,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GLOCK_,        48,	1,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GCE0_,   	51,	127,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GRDY0_,        52,	126,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GDE_,	        53,	188,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(TCK,    	54,	125,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(TDO,   	55,	187,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(TDI,   	56,	8,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(TMS,    	57,	192,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(TRS,	        58,	7,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(EMU0,  	59,	191,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(EMU1,  	60,	4,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GPAGE1,        64,	122,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GRW1_,  	65,	3,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GSTRB1_,       66,	121,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GSTAT0,        67,	189,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GSTAT1,        68,	190,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GSTAT2,        70,	116,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GSTAT3,        71,	186,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GPAGE0,        72,	115,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GRW0_,	        73,	185,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GSTRB0_,       74,	60,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GAE_,    	75,	244,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(RESETLOC1, 	76,	 59,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(RESETLOC0, 	78,	 243,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(RESET_,	79,	64,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CRDY5_,	80,	120,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CSTRB5_,	81,	63,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CACK5_,	82,	119,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CREQ5_,	83,	118,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CRDY4_,	84,	248,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CSTRB4_,	85,	117,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CACK4_,	86,	246,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CREQ4_,	87,	247,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C5D7,	        92,	245,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C5D6,   	93,	62,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C5D5,   	94,	61,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C5D4,  	95,	58,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C5D3,  	96,	114,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C5D2,   	97,	57,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C5D1,  	98,	113,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C5D0,  	99,	241,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C4D7,  	101,	242,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C4D6,  	102,	108,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C4D5,  	103,	180,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C4D4,  	104,	107,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C4D3,  	105,	179,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C4D2,  	106,	52,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C4D1,  	107,	184,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C4D0,  	108,	51,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C3D7,  	113,	183,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C3D6,  	114,	56,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C3D5,  	115,	112,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C3D4,  	116,	55,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C3D3,  	117,	111,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C3D2,  	118,	110,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C3D1,  	119,	182,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C3D0,  	120,	109,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C2D7,  	124,	181,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C2D6,  	125,	54,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C2D5,  	126,	178,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C2D4,  	127,	53,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C2D3,  	128,	177,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C2D2,  	129,	50,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C2D1,  	130,	106,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C2D0,  	131,	49,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CRDY3_,	136,	105,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CSTRB3_,	137,	44,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CACK3_,	138,	43,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CREQ3_,	139,	236,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CRDY2_,	142,	48,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CSTRB2_,	143,	235,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CACK2_,	144,	47,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CREQ2_,	145,	240,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CRDY1_,	147,	102,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CSTRB1_,	148,	46,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CACK1_,	149,	239,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CREQ1_,	150,	42,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CRDY0_,	151,	101,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CSTRB0_,	152,	45,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CACK0_,	153,	41,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(CREQ0_,	154,	238,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C1D7,  	161,	237,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C1D6,  	162,	99,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C1D5,  	163,	100,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C1D4,  	164,	234,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C1D3,  	165,	104,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C1D2,  	166,	98,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C1D1,  	167,	233,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C1D0,  	168,	103,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C0D7,  	170,	97,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C0D6,  	171,	35,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C0D5,  	172,	36,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C0D4,  	173,	171,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C0D3,  	174,	175,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C0D2,  	175,	176,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C0D1,  	176,	172,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(C0D0,  	177,	39,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(ROMEN,  	180,	173,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(IIOF0,  	181,	40,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(IIOF1,	        184,	174,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(IIOF2,  	185,	38,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(IIOF3,	        186,	37,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(NMI_,  	187,	156,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LSTRB0_,	188,	155,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LRW0_, 	189,	170,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LPAGE0,	190,	34,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LRDY0_,	191,	33,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LCE0_,	        192,	169,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LSTRB1_,	193,	92,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LRW1_, 	194,	228,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LPAGE1,	197,	91,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LRDY1_,	198,	227,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LCE1_,	        199,	96,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LDE_,   	200,	160,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(TCLK0,  	201,	95,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(TCLK1,  	202,	159,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(H3,		203,	231,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(H1,		204,	232,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LAE_,  	205,	94,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LLOCK_,	207,	230,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LSTAT0,	208,	93,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LSTAT1,	209,	229,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LSTAT2,	210,	226,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LSTAT3,	211,	28,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(IACK_,	        212,	225,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(X1,		215,	158,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA30,   	222,	157,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA29,  	223,	27,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA28,  	224,	164,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA27,  	225,	32,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA26,  	227,	163,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA25,  	228,	31,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA24,  	229,	168,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA23,  	230,	30,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA22,  	231,	167,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA21,  	232,	29,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA20,  	233,	153,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA19,  	234,	154,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA18,  	235,	26,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA17,  	236,	25,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA16,  	237,	166,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA15,  	244,	165,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA14,  	245,	162,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA13,  	246,	84,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA12,  	247,	161,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA11,  	248,	83,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA10,  	249,	220,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA9,		250,	88,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA8,		251,	219,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA7,		252,	87,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA6,		253,	148,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA5,		254,	86,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA4,		255,	147,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA3,		257,	85,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA2,		258,	224,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA1,		259,	81,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LA0,		260,	82,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD31,  	264,	223,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD30,  	265,	152,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD29,  	266,	222,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD28,  	267,	221,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD27,  	269,	20,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD26,  	270,	19,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD25,  	271,	24,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD24,  	272,	151,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD23,  	273,	23,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD22,  	274,	218,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD21,  	275,	217,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD20,  	276,	212,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD19,  	277,	22,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD18,  	278,	211,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD17,  	279,	21,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD16,  	286,	216,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD15,  	287,	18,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD14,  	288,	215,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD13,  	289,	150,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD12,  	290,	17,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD11,  	291,	76,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD10,  	292,	149,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD9,		293,	75,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD8,		294,	214,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD7,		295,	80,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD6,		296,	213,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD5,		297,	79,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD4,		299,	210,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD3,		300,	78,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD2,		301,	209,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD1,		302,	77,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(LD0,		303,	146,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA30,  	310,	74,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA29,  	311,	145,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA28,  	312,	73,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA27,  	314,	140,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA26,  	315,	204,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA25,  	316,	139,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA24,  	317,	203,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA23,  	318,	12,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA22,  	319,	208,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA21,  	320,	207,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA20,  	321,	11,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA19,  	322,	144,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA18,  	323,	16,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA17,  	324,	143,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA16,  	331,	15,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA15,  	332,	206,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA14,  	333,	142,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA13,  	334,	205,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA12,  	335,	141,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA11,  	336,	202,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA10,  	337,	14,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA9,		338,	201,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA8,		339,	13,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA7,		340,	138,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA6,		341,	10,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA5,		342,	137,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA4,		343,	9,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA3,		345,	196,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA2,		346,	195,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA1,		347,	200,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSet(GA0,		348,	132,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);

  PinSetMux(X2CLKIN,	216,	89,90, I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetSupply(VDD,      49,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(DVDD,      7,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSUB,    352,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSS,      18,     Ground,        0,       0,       0,       0   );


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 DeviceTableClose;

  end 

    else
     begin 
                                 
     DeviceTableOpen;
       devicetablename:='TMS320C40PackageDeviceTable';
       DeviceTableSetName(devicetablename);
 
 
 

  PinSetMP(GD31,	1,	187,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD30,	2,	184,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD29,	3,	249,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD28,	4,	185,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD27,	5,	222,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD26,	6,	225,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD25,	8,	224,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD24,	9,	226,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD23,	10,	186,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD22,	11,	182,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD21,	12,	188,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD20,	13,	250,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD19,	14,	217,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD18,	15,	181,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD17,	16,	223,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD16,	17,	141,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD15,	25,	221,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD14,	26,	103,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD13,	27,	183,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD12,	28,	145,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD11,	29,	101,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD10,	30,	107,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD9, 	31,	105,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD8, 	32,	143,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD7, 	33,	147,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD6, 	34,	148,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD5, 	35,	144,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD4, 	37,	106,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD3, 	38,	102,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD2, 	39,	108,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD1, 	40,	146,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GD0, 	41,	104,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GCE1_,	42,	21,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GRDY1_,	43,	63,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GLOCK_,	48,	61,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GCE0_,	51,	23,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GRDY0_,	52,	24,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GDE_,	53,	142,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TCK, 	54,	62,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TDO, 	55,	64,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TDI, 	56,	173,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TMS, 	57,	22,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TRS, 	58,	177,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(EMU0,	59,	211,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(EMU1,	60,	219,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GPAGE1,	64,	179,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GRW1_,	65,	246,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTRB1_,	66,	180,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTAT0,	67,	218,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTAT1,	68,	212,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTAT2,	70,	220,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTAT3,	71,	174,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GPAGE0,	72,	178,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GRW0_,	73,	213,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GSTRB0_,	74,	139,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GAE_,	75,	247,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(RESETLOC1, 	76,	175,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(RESETLOC0, 	78,	215,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(RESET_,	79,	216,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY5_,	80,	57,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB5_,	81,	176,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK5_,	82,	248,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ5_,	83,	17,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY4_,	84,	214,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB4_,	85,	97,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK4_,	86,	172,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ4_,	87,	99,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D7,	92,	59,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D6,	93,	137,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D5,	94,	19,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D4,	95,	60,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D3,	96,	138,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D2,	97,	20,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D1,	98,	100,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C5D0,	99,	140,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D7,	101,	98,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D6,	102,	58,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D5,	103,	171,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D4,	104,	245,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D3,	105,	18,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D2,	106,	207,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D1,	107,	209,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C4D0,	108,	51,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D7,	113,	243,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D6,	114,	53,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D5,	115,	169,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D4,	116,	170,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D3,	117,	91,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D2,	118,	244,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D1,	119,	210,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C3D0,	120,	13,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D7,	124,	208,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D6,	125,	93,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D5,	126,	14,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D4,	127,	95,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D3,	128,	15,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D2,	129,	92,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D1,	130,	55,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C2D0,	131,	56,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY3_,	136,	16,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB3_,	137,	96,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK3_,	138,	54,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ3_,	139,	94,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY2_,	142,	241,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB2_,	143,	167,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK2_,	144,	52,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ2_,	145,	165,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY1_,	147,    128,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB1_,	148,	205,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK1_,	149,	206,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ1_,	150,	117,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CRDY0_,	151,	166,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CSTRB0_,	152,	168,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CACK0_,	153,	159,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(CREQ0_,	154,	242,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D7,	161,	129,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D6,	162,	160,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D5,	163,	135,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D4,	164,	131,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D3,	165,	118,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D2,	166,	133,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D1,	167,	134,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C1D0,	168,	41,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D7,	170,	132,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D6,	171,	81,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D5,	172,	136,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D4,	173,	130,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D3,	174,	82,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D2,	175,	09,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D1,	176,	11,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(C0D0,	177,	50,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(ROMEN,	180,	90,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IIOF0,	181,	49,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IIOF1,	184,	42,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IIOF2,	185,	89,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IIOF3,	186,	12,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(NMI_,	187,	77,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTRB0_,	188,	10,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LRW0_,	189,	161,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LPAGE0,	190,	39,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LRDY0_,	191,	203,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LCE0_,	192,	201,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTRB1_,	193,	40,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LRW1_,	194,	163,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LPAGE1,	197,	164,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LRDY1_,	198,	202,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LCE1_,	199,	78,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LDE_,	200,	204,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TCLK0,	201,	162,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(TCLK1,	202,	195,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(H3,  	203,	121,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(H1,  	204,	127,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LAE_,	205,	235,	 I,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LLOCK_,	207,	123,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTAT0,	208,	236,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTAT1,	209,	125,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTAT2,	210,	126,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LSTAT3,	211,	196,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(IACK_,	212,	124,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(X1,  	215,	122,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA30,	222,	87,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA29,	223,	113,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA28,	224,	07,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA27,	225,	47,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA26,	227,	48,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA25,	228,	08,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA24,	229,	155,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA23,	230,	88,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA22,	231,	43,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA21,	232,	156,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA20,	233,	45,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA19,	234,	83,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA18,	235,	114,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA17,	236,	05,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA16,	237,	06,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA15,	244,	75,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA14,	245,	84,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA13,	246,	46,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA12,	247,	73,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA11,	248,	44,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA10,	249,	197,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA9, 	250,	35,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA8, 	251,	239,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA7, 	252,	237,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA6, 	253,	36,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA5, 	254,	199,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA4, 	255,	200,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA3, 	257,	238,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA2, 	258,	240,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA1, 	259,	74,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LA0, 	260,	198,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD31,	264,	157,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD30,	265,	158,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD29,	266,	119,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD28,	267,	120,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD27,	269,	71,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD26,	270,	01,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD25,	271,	03,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD24,	272,	69,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD23,	273,	04,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD22,	274,	02,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD21,	275,	70,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD20,	276,	37,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD19,	277,	79,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD18,	278,	72,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD17,	279,	80,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD16,	286,	38,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD15,	287,	231,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD14,	288,	233,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD13,	289,	255,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD12,	290,	193,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD11,	291,	256,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD10,	292,	234,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD9, 	293,	194,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD8, 	294,	153,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD7, 	295,	115,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD6, 	296,	232,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD5, 	297,	116,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD4, 	299,	251,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD3, 	300,	154,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD2, 	301,	33,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD1, 	302,	189,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(LD0, 	303,	76,	IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA30,	310,	34,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA29,	311,	190,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA28,	312,	31,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA27,	314,	252,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA26,	315,	29,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA25,	316,	30,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA24,	317,	109,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA23,	318,	32,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA22,	319,	191,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA21,	320,	151,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA20,	321,	253,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA19,	322,	254,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA18,	323,	152,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA17,	324,	192,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA16,	331,	227,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA15,	332,	110,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA14,	333,	229,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA13,	334,	230,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA12,	335,	65,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA11,	336,	228,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA10,	337,	149,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA9, 	338,	27,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA8, 	339,	111,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA7, 	340,	112,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA6, 	341,	28,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA5, 	342,	150,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA4, 	343,	25,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA3, 	345,	67,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA2, 	346,	66,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA1, 	347,	26,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
  PinSetMP(GA0, 	348,	68,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);

  PinSetMuxMP(X2CLKIN,	216,	85,86, I,	MINV,	MAXV,	MINI,	MAXI);

  PinSetSupply(VDD,   49,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(DVDD,   7,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSUB, 352,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSS,   18,     Ground,        0,       0,       0,       0   );


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

DeviceTableClose;

     end;  
    end;  
  end;   
end;  

  SM320C40TAB_pg3x_40MHz, SM320C40TAB_pg5x_40MHz, SM320C40TAB_pg5x_50MHz,
  SM320C40TAB_pg5x_60MHz, TMS320C40TAL_pg3x_50MHz, TMS320C40TAL_pg5x_60MHz:
   begin
				
				
     if not motherboard then
     begin

 DeviceTableOpen;

 devicetablename := 'TMS320C40PackageDeviceTable';
 DeviceTableSetName(devicetablename);

 
 

   

  PinSetMP(GD31,         1,   241,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD30,         2,    45,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD29,         3,   125,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD28,         4,   242,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD27,         5,    84,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD26,         6,   126,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD25,         8,   204,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD24,         9,   164,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD23,        10,    06,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD22,        11,    05,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD21,        12,   203,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD20,        13,    44,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD19,        14,    83,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD18,        15,    43,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD17,        16,   163,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD16,        17,    03,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD15,        21,   123,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD14,        22,    04,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD13,        23,   124,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD12,        24,    82,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD11,        25,    81,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD10,        26,   202,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD9,         27,   201,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD8,         28,    42,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD7,         29,    41,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD6,         30,   162,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD5,         31,   161,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD4,         33,    01,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD3,         34,   122,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD2,         35,    02,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD1,         36,   121,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GD0,         37,   239,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GCE1_,       38,   120,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GRDY1_,      39,   240,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GLOCK_,      42,   119,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GCE0_,       45,   199, {O}I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GRDY0_,      46,    80,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GDE_,        47,   200,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(TCK,         48,    79,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(TDO,         49,   159,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(TDI,         50,    39, {O}I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(TMS,         51,   160,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(TRS,         52,   238,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(EMU0,        53,    40,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(EMU1,        54,   118,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GPAGE1,      57,   237,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GRW1_,       58,   117, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GSTRB1_,     59,    78, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GSTAT0,      60,    77, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GSTAT1,      61,   198, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GSTAT2,      63,   197, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GSTAT3,      64,   158, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GPAGE0,      65,    38, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GRW0_,       66,    75, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GSTRB0_,     67,    37, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GAE_,        68,   255, {O}I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(RESETLOC1,   69,   157,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(RESETLOC0,   71,   236,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(RESET_,      72,   235,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CRDY5_,      73,   256,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CSTRB5_,     74,   156,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CACK5_,      75,   195,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CREQ5_,      76,   115,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CRDY4_,      77,   116,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CSTRB4_,     78,    36,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CACK4_,      79,    76,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CREQ4_,      80,   196,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C5D7,        84,   114,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C5D6,        85,   113,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C5D5,        86,   194,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C5D4,        87,    35,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C5D3,        88,   234,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C5D2,        89,   233,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C5D1,        90,   193,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C5D0,        91,   155,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C4D7,        93,    74,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C4D6,        94,    34,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C4D5,        95,    73,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C4D4,        96,   154,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C4D3,        97,    33,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C4D2,        98,   153,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C4D1,        99,   253,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C4D0,       100,   254,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C3D7,       104,   112,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C3D6,       105,   232,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C3D5,       106,   111,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C3D4,       107,   231,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C3D3,       108,    72,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C3D2,       109,   192,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C3D1,       110,    71,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C3D0,       111,   191,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C2D7,       114,    32,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C2D6,       115,   152,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C2D5,       116,   151,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C2D4,       117,   110,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C2D3,       118,    31,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C2D2,       119,   230,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C2D1,       120,   229,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C2D0,       121,   109,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CRDY3_,     125,    70,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CSTRB3_,    126,   190,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CACK3_,     127,   189,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CREQ3_,     128,    69,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CRDY2_,     131,   150,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CSTRB2_,    132,    29,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CACK2_,     133,   149,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CREQ2_,     134,    30,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CRDY1_,     136,   252,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CSTRB1_,    137,   228,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CACK1_,     138,   251,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CREQ1_,     139,   108,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CRDY0_,     140,   188,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CSTRB0_,    141,   107,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CACK0_,     142,   227,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(CREQ0_,     143,    68,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C1D7,       148,   187,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C1D6,       149,    67,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C1D5,       150,   148,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C1D4,       151,    28,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C1D3,       152,   106,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C1D2,       153,    27,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C1D1,       154,   226,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C1D0,       155,   185,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C0D7,       157,   105,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C0D6,       158,   147,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C0D5,       159,    65,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C0D4,       160,    66,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C0D3,       161,   186,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C0D2,       162,   225,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C0D1,       163,   224,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(C0D0,       164,   146,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(ROMEN,      167,   104,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(IIOF0,      168,    26,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(IIOF1,      170,   250,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(IIOF2,      171,   223,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(IIOF3,      172,   145,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(NMI_,       173,    25,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LSTRB0_,    174,   103,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LRW0_,      175,    63, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LPAGE0,     176,   184, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LRDY0_,     177,   249, {O}I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LCE0_,      178,    64,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LSTRB1_,    179,    24,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LRW1_,      180,   183, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LPAGE1,     183,    23, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LRDY1_,     184,   144, {O}I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LCE1_,      185,   143,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LDE_,       186,   222,    I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(TCLK0,      187,   101,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(TCLK1,      188,   102,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(H3,         189,   221,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(H1,         190,   182, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LAE_,       191,    62, {O}I ,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LLOCK_,     193,   181,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LSTAT0,     194,    61, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LSTAT1,     195,   142, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LSTAT2,     196,    22, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LSTAT3,     197,   141, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(IACK_,      198,    21, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(X1,         201,   220, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA30,       206,   219, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA29,       207,    60, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA28,       208,   180, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA27,       209,    59, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA26,       211,   179, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA25,       212,   140, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA24,       213,    20, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA23,       214,    19, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA22,       215,   139, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA21,       216,   217, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA20,       217,    98, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA19,       218,    97, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA18,       219,   218, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA17,       220,   178, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA16,       221,    58, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA15,       225,   177, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA14,       226,   138, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA13,       227,    57, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA12,       228,   215, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA11,       229,    17, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA10,       230,   137, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA9,        231,    18, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA8,        232,    56, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA7,        233,    95, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA6,        234,   216, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA5,        235,   247, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA4,        236,   175, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA3,        238,    96, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA2,        239,   248, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA1,        240,    55, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LA0,        241,   176, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD31,       244,   213, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD30,       245,   136,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD29,       246,    15,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD28,       247,    94,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD27,       249,    16,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD26,       250,   214,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD25,       251,    93,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD24,       252,   173,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD23,       253,   135,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD22,       254,    54,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD21,       255,   174,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD20,       256,    53,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD19,       257,   134,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD18,       258,    14,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD17,       259,   133,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD16,       264,   245,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD15,       265,   246,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD14,       266,    13,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD13,       267,    92,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD12,       268,   211,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD11,       269,    91,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD10,       270,   212,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD9,        271,    52,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD8,        272,   172,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD7,        273,    51,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD6,        274,   171,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD5,        275,    12,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD4,        277,   132,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD3,        278,   131,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD2,        279,    90,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD1,        280,    11,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(LD0,        281,   210,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA30,       286,   209,    IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA29,       287,    89, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA28,       288,   170, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA27,       290,    49, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA26,       291,   169, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA25,       292,    50, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA24,       293,   129, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA23,       294,   130, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA22,       295,    10, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA21,       296,    09, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA20,       297,   208, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA19,       298,   244, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA18,       299,    88, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA17,       300,   243, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA16,       304,   207, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA15,       305,   167, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA14,       306,   168, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA13,       307,    48, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA12,       308,    87, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA11,       309,    46, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA10,       310,    08, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA9,        311,   128, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA8,        312,    47, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA7,        313,   166, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA6,        314,    85, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA5,        315,    86, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA4,        316,    07, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA3,        318,   205, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA2,        319,   206, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA1,        320,   127, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
  PinSetMP(GA0,        321,   165, {O}IO,  MINV,   MAXV,   MINI,   MAXI);        
                                                                                 
  PinSetMuxMP(X2CLKIN, 202,   99 ,100, I,  MINV,   MAXV,   MINI,   MAXI);        
                                                                                 
                                                                                 
  PinSetSupply(VDD,   43,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);   
  PinSetSupply(DVDD,   7,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);   
  PinSetSupply(VSUB, 324,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);   
  PinSetSupply(VSS,   18,     Ground,        0,       0,       0,       0   );   
                                                                                 
  
  
        
        
        
        
        
        
        
        
        
        
        
                                                                                 
 DeviceTableClose;   

   end  

    else
    begin 

 DeviceTableOpen;
  devicetablename:='TMS320C40PackageDeviceTable';
  DeviceTableSetName(devicetablename);

 
 

    PinSet(GD31,	7,	113,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD30,	8,	247,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD29,	9,	245,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD28,	10,	246,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD27,	11,	59,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD26,	12,	116,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD25,	15,	248,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD24,	16,	181,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD23,	17,	60,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD22,	18,	114,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD21,	19,	49,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD20,	20,	183,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD19,	21,	184,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD18,	22,	182,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD17,	23,	243,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD16,	24,	52,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD15,	33,	120,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD14,	34,	117,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD13,	35,	179,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD12,	36,	50,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD11,	37,	233,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD10,	38,	119,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD9,		39,	56,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD8,		40,	118,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD7,		41,	115,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD6,		42,	234,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD5,		43,	169,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD4,		46,	53,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD3,		47,	51,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD2,		48,	172,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD1,		49,	170,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GD0,		50,	55,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GCE1_,	51,	237,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GRDY1_,	52,	54,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GLOCK_,	58,	235,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GCE0_,	63,	240,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GRDY0_,	64,	238,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GDE_,	65,	236,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(TCK,		66,	105,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(TDO,		67,	108,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(TDI,		68,	239,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(TMS,		69,	173,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(TRS,		70,	174,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(EMU0,	71,	171,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(EMU1,	72,	106,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GPAGE1,	77,	107,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GRW1_,	78,	41,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GSTRB1_,	79,	44,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GSTAT0,	80,	175,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GSTAT1,	81,	176,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GSTAT2,	84,	42,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GSTAT3,	85,	225,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GPAGE0,	86,	111,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GRW0_,	87,	109,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GSTRB0_,	88,	110,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GAE_,	89,	43,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(RESETLOC1, 	90,	228,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(RESETLOC0, 	93,	112,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(RESET_,	94,	45,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CRDY5_,	95,	227,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CSTRB5_,	96,	226,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CACK5_,	97,	161,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CREQ5_,	98,	47,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CRDY4_,	99,	48,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CSTRB4_,	100,	46,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CACK4_,	101,	166,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CREQ4_,	102,	163,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C5D7,	120,	99,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C5D6,	121,	164,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C5D5,	122,	162,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C5D4,	123,	231,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C5D3,	124,	229,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C5D2,	125,	230,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C5D1,	126,	102,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C5D0,	127,	97,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C4D7,	130,	232,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C4D6,	131,	165,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C4D5,	132,	35,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C4D4,	133,	100,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C4D3,	134,	98,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C4D2,	135,	167,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C4D1,	136,	168,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C4D0,	137,	101,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C3D7,	144,	38,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C3D6,	145,	33,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C3D5,	146,	36,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C3D4,	147,	103,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C3D3,	148,	104,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C3D2,	149,	37,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C3D1,	150,	219,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C3D0,	151,	34,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C2D7,	156,	220,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C2D6,	157,	217,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C2D5,	158,	218,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C2D4,	159,	39,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C2D3,	160,	40,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C2D2,	161,	221,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C2D1,	162,	155,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C2D0,	163,	153,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CRDY3_,	171,	223,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CSTRB3_,	172,	224,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CACK3_,	173,	222,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CREQ3_,	174,	156,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CRDY2_,	179,	157,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CSTRB2_,	180,	91,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CACK2_,	181,	154,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CREQ2_,	182,	89,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CRDY1_,	185,	158,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CSTRB1_,	186,	92,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CACK1_,	187,	90,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CREQ1_,	188,	25,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CRDY0_,	189,	159,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CSTRB0_,	190,	160,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CACK0_,	191,	93,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(CREQ0_,	192,	27,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C1D7,	201,	95,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C1D6,	202,	96,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C1D5,	203,	94,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C1D4,	204,	28,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C1D3,	205,	26,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C1D2,	206,	209,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C1D1,	207,	31,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C1D0,	208,	29,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C0D7,	211,	212,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C0D6,	212,	210,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C0D5,	213,	215,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C0D4,	214,	32,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C0D3,	215,	30,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C0D2,	225,	145,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C0D1,	226,	151,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(C0D0,	227,	216,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(ROMEN,	232,	152,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(IIOF0,	233,	149,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(IIOF1,	236,	148,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(IIOF2,	237,	146,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(IIOF3,	238,	87,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(NMI_,	239,	150,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LSTRB0_,	240,	213,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LRW0_,	241,	211,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LPAGE0,	242,	81,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LRDY0_,	243,	84,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LCE0_,	244,	23,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LSTRB1_,	245,	85,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LRW1_,	246,	214,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LPAGE1,	251,	88,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LRDY1_,	252,	86,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LCE1_,	253,	147,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LDE_,	254,	82,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(TCLK0,	255,	17,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(TCLK1,	256,	207,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(H3,		257,	21,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(H1,		258,	22,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LAE_,	259,	83,	 I,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LLOCK_,	262,	208,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LSTAT0,	263,	24,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LSTAT1,	264,	203,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LSTAT2,	265,	19,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LSTAT3,	266,	20,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(IACK_,	267,	18,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(X1,		272,	201,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA30,	281,	206,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA29,	282,	78,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA28,	283,	204,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA27,	284,	205,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA26,	287,	77,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA25,	288,	11,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA24,	289,	139,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA23,	290,	202,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA22,	291,	137,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA21,	292,	141,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA20,	293,	80,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA19,	294,	14,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA18,	295,	140,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA17,	296,	142,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA16,	297,	138,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA15,	304,	79,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA14,	305,	13,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA13,	306,	197,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA12,	307,	75,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA11,	308,	73,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA10,	309,	74,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA9,		310,	15,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA8,		311,	16,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA7,		312,	198,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA6,		313,	76,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA5,		314,	9,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA4,		315,	10,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA3,		318,	131,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA2,		319,	12,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA1,		320,	193,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LA0,		321,	196,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD31,	334,	194,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD30,	335,	199,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD29,	336,	200,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD28,	337,	134,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD27,	340,	129,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD26,	341,	135,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD25,	342,	133,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD24,	343,	70,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD23,	344,	195,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD22,	345,	130,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD21,	346,	65,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD20,	347,	71,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD19,	348,	136,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD18,	349,	3,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD17,	350,	132,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD16,	359,	72,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD15,	360,	69,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD14,	361,	6,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD13,	362,	67,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD12,	363,	66,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD11,	364,	1,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD10,	365,	7,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD9,		366,	5,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD8,		367,	4,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD7,		368,	68,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD6,		369,	2,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD5,		370,	249,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD4,		373,	251,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD3,		374,	252,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD2,		375,	250,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD1,		376,	185,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(LD0,		377,	8,	IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA30,	387,	186,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA29,	388,	121,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA28,	389,	255,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA27,	392,	187,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA26,	393,	122,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA25,	394,	57,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA24,	395,	191,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA23,	396,	256,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA22,	397,	253,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA21,	398,	188,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA20,	399,	58,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA19,	400,	241,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA18,	401,	127,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA17,	402,	192,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA16,	409,	254,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA15,	410,	123,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA14,	411,	244,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA13,	412,	242,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA12,	413,	128,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA11,	414,	125,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA10,	415,	189,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA9,		416,	124,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA8,		417,	177,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA7,		418,	180,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA6,		419,	63,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA5,		420,	126,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA4,		421,	190,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA3,		424,	178,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA2,		425,	64,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA1,		426,	61,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);
    PinSet(GA0,		427,	62,	{O}IO,	MINV,	MAXV,	MINI,	MAXI);

    PinSetMux(X2CLKIN,  274,    143,144, I,     MINV,   MAXV,   MINI,   MAXI);
 
    PinSetSupply(VDD,   59,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
    PinSetSupply(DVDD,  13,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
    PinSetSupply(VSUB, 432,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
    PinSetSupply(VSS,   25,     Ground,        0,       0,       0,       0   );

 DeviceTableClose;

       end;
     end; 
   end; 
 end;

 IDSEngr:
 begin

 DeviceTableOpen;

 devicetablename := 'TMS320C40IDSDeviceTable';
 DeviceTableSetName(devicetablename);

 
 

  PinSetMP(GD31,         1,  {F32}   44,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD30,         2,  {E31}    6,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD29,         3,  {H30}    5,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD28,         4,  {C33}   84,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD27,         5,  {G31}    9,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD26,         6,  {D34}  204,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD25,         8,  {E33}   83,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD24,         9,  {H32}  201,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD23,        10,  {F34}  203,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD22,        11,  {K30}   43,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD21,        12,  {G33}  202,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD20,        13,  {J31}  241,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD19,        14,  {H34}  164,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD18,        15,  {K32}  161,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD17,        16,  {M30}    3,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD16,        17,  {L31}    4,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD15,        22,  {J33}  162,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD14,        23,  {M32}  122,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD13,        24,  {K34}  163,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD12,        25,  {N31}   82,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD11,        26,  {L33}   41,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD10,        27,  {P32}   81,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD9,         28,  {M34}  124,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD8,         29,  {R31}   42,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD7,         30,  {N33}  121,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD6,         31,  {T32}    2,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD5,         32,  {P34}  123,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD4,         34,  {R33}    1,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD3,         35,  {U31}  235,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD2,         36,  {T34}  120,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD1,         37,  {V32}  236,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GD0,         38,  {U33}  256,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GCE1_,       39,  {V34}  119,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRDY1_,      40,  {W31}  196,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GLOCK_,      43,  {W33}  240, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GCE0_,       46, {AA33}  239,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRDY0_,      47,  {Y32}  195,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GDE_,        48, {AA31}  156,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCK,         49,  {Y34}   79,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TDO,         50, {AB34}   39, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TDI,         51, {AC35}  118,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TMS,         52,  {W35}   80,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TRS,         53, {AE35}   78,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(EMU0,        54, {AA35}   40,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(EMU1,        55, {AD34}  117,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GPAGE1,      58, {AB32}  155, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRW1_,       59, {AC31}  234, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTRB1_,     60, {AC33}  200, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT0,      61, {AD32}  199, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT1,      62, {AE33}  160, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT2,      64, {AF34}   77, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTAT3,      65, {AE31}  194, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GPAGE0,      66, {AG33}  238, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GRW0_,       67, {AF32}  159, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GSTRB0_,     68, {AD30}  233, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GAE_,        69, {AG31}  154,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESETLOC1,   70, {AH34}   38,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESETLOC0,   72, {AF30}  193,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(RESET_,      73, {AJ33}  198,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY5_,      74, {AH32}  237,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB5_,     75, {AK34}   37,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK5_,      76, {AJ31}  231,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ5_,      77, {AL33}  158,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY4_,      78, {AH30}  153,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB4_,     79, {AM34}  254,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK4_,      80, {AK32}  197,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ4_,      81, {AN33}  255,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D7,        85, {AL31}  192,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D6,        86, {AM32}  157,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D5,        87, {AP32}  232,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D4,        88, {AM30}  115,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D3,        89, {AN31}  116,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D2,        90, {AK28}  152,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D1,        91, {AP30}  253,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C5D0,        92, {AL29}  191,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D7,        94, {AM28}   75,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D6,        95, {AN29}   76,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D5,        96, {AK26}  230,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D4,        97, {AP28}  252,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D3,        98, {AL27}  151,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D2,        99, {AK24}  190,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D1,       100, {AM26}   35,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C4D0,       101, {AN27}   36,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D7,       105, {AP26}  228,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D6,       106, {AL25}  229,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D5,       107, {AN25}  114,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D4,       108, {AM24}  113,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D3,       109, {AP24}  227,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D2,       110, {AL23}  189,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D1,       111, {AN23}   74,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C3D0,       112, {AM22}  150,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D7,       115, {AP22}  188,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D6,       116, {AL21}  149,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D5,       117, {AN21}   73,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D4,       118, {AM20}  251,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D3,       119, {AP20}  187,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D2,       120, {AL19}  108,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D1,       121, {AN19}   34,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C2D0,       122, {AM18}   33,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY3_,     126, {AL17}  107,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB3_,    127, {AP18}  148,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK3_,     128, {AM16}   68,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ3_,     129, {AN17}  112,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY2_,     132, {AL15}   67,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB2_,    133, {AP16}  147,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK2_,     134, {AM14}   28,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ2_,     135, {AN15}  111,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY1_,     137, {AP14}  226,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB1_,    138, {AL13}   27,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK1_,     139, {AN13}   72,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ1_,     140, {AM12}   71,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CRDY0_,     141, {AP12}  225,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CSTRB0_,    142, {AL11}  105,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CACK0_,     143, {AN11}   32,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(CREQ0_,     144, {AM10}   31,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D7,       149, {AP10}  186,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D6,       150,  {AL9}   65,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D5,       151,  {AN9}  110,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D4,       152, {AK10}   66,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D3,       153, {AK12}  106,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D2,       154,  {AM8}  109,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D1,       155,  {AP8}  185,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C1D0,       156,  {AL7}   25,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D7,       158,  {AK8}   26,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D6,       159,  {AN7}   70,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D5,       160,  {AM6}   69,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D4,       161,  {AP6}  146,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D3,       162,  {AM4}   29,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D2,       163,  {AN5}   30,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D1,       164,  {AL5}  249,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(C0D0,       165,  {AP4}  145,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(ROMEN,      168,  {AK4}  184,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF0,      169,  {AN3}  224,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF1,      171,  {AL3}  223,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF2,      172,  {AH6}  103,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IIOF3,      173,  {AK2}  250,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(NMI_,       174,  {AJ5}  104,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTRB0_,    175,  {AJ3}  183, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRW0_,      176,  {AH4}  144, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LPAGE0,     177,  {AH2}  100, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRDY0_,     178,  {AF6}   63,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LCE0_,      179,  {AG5}   64,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTRB1_,    180,  {AD6}   23, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRW1_,      181,  {AF4}  222, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LPAGE1,     184,  {AG3}  143, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LRDY1_,     185,  {AE5}   24,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LCE1_,      186,  {AF2}   99,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LDE_,       187,  {AD4}  182,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCLK0,      188,  {AE3}  221,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(TCLK1,      189,  {AD2}   20,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(H3,         190,  {AC5}  102, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(H1,         191,  {AC3}  181, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LAE_,       192,  {AB4}  101,     I,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LLOCK_,     194,  {AA5}   62, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT0,     195,  {AA3}  142, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT1,     196,   {Y4}   61, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT2,     197,   {Y2}   19, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LSTAT3,     198,   {W5}   22, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(IACK_,      199,   {W3}  141, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(X1,         202,   {W1}   98, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA30,       207,   {U5}   21, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA29,       208,   {V4}  220, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA28,       209,   {T4}  248, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA27,       210,   {U3}  219, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA26,       212,   {T2}   97, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA25,       213,   {R5}  216, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA24,       214,   {R3}  180, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA23,       215,   {P4}  215, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA22,       216,   {P2}   58, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA21,       217,   {N5}  176, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA20,       218,   {N3}  179, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA19,       219,   {M4}  140, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA18,       220,   {M2}   57, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA17,       221,   {L5}  136, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA16,       222,   {L3}  139, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA15,       226,   {K2}   18, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA14,       227,   {K4}  218, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA13,       228,   {J3}  217, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA12,       229,   {J5}  214, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA11,       230,   {M6}  175, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA10,       231,   {K6}  135, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA9,        232,   {H2}   17, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA8,        233,   {H4}  178, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA7,        234,   {G3}  177, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA6,        235,   {G5}  174, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA5,        236,   {F2}  133, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA4,        237,   {H6}  213, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA3,        239,   {F4}  138, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA2,        240,   {E3}  137, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA1,        241,   {D4}  134, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LA0,        242,   {D2}  246, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD31,       245,   {F6}  212,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD30,       246,   {E5}  173,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD29,       247,   {C3}  247,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD28,       248,   {D6}   95,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD27,       250,   {F8}  172,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD26,       251,   {B4}  244,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD25,       252,   {E7}  211,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD24,       253,   {C5}   96,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD23,       254,   {D8}   55,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD22,       255,   {B6}  208,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD21,       256,  {F10}  132,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD20,       257,   {C7}   56,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD19,       258,   {E9}  171,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD18,       259,   {B8}  207,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD17,       260,  {D10}   15,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD16,       265,  {F12}  210,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD15,       266,  {E11}  131,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD14,       267,   {C9}   16,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD13,       268,  {D12}   93,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD12,       269,  {B10}  168,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD11,       270,  {E13}  209,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD10,       271,  {C11}   94,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD9,        272,  {D14}  170,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD8,        273,  {B12}  167,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD7,        274,  {E15}  169,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD6,        275,  {C13}   54,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD5,        276,  {D16}  130,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD4,        278,  {E17}  129,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD3,        279,  {B14}  128,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD2,        280,  {D18}   13,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD1,        281,  {C15}   53,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(LD0,        282,  {E19}  243,    IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA30,       287,  {B16}  127, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA29,       288,  {D20}   88, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA28,       289,  {C17}   14, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA27,       291,  {B18}  206, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA26,       292,  {E21}   87, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA25,       293,  {B20}  205, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA24,       294,  {D22}   48, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA23,       295,  {C19}  245, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA22,       296,  {E23}   47, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA21,       297,  {B22}  166, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA20,       298,  {D24}   52, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA19,       299,  {C21}   92, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA18,       300,  {E25}    7, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA17,       301,  {B24}  165, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA16,       305,  {C23}   91, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA15,       306,  {D26}   12, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA14,       307,  {B26}  126, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA13,       308,  {E27}   85, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA12,       309,  {C25}   51, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA11,       310,  {F26}   86, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA10,       311,  {B28}  125, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA9,        312,  {D28}   90, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA8,        313,  {C27}   11, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA7,        314,  {E29}   45, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA6,        315,  {F24}    8, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA5,        316,  {F28}   46, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA4,        317,  {B30}  242, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA3,        319,  {C29}   89, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA2,        320,  {D30}   50, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA1,        321,  {B32}   49, {O}IO,  MINV,   MAXV,   MINI,   MAXI);
  PinSetMP(GA0,        322,  {D32}   10, {O}IO,  MINV,   MAXV,   MINI,   MAXI);

  PinSetMuxMP(X2CLKIN, 203,  {AA1}   59,60,  I,  MINV,   MAXV,   MINI,   MAXI);


  PinSetSupply(VDD,   44,     Supply1,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(DVDD,   7,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSUB, 325,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
  PinSetSupply(VSS,   18,     Ground,        0,       0,       0,       0   );

 
 
 
 
 
 
 
 
 
 
 
 
 

 DeviceTableClose;

 end; 
 end; 


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	





  PinListSet (CLKOUTS, H1,H3);

  PinListSet (LDBUS, LD31,LD30,LD29,LD28,LD27,LD26,LD25,LD24,LD23,LD22,LD21,
                     LD20,LD19,LD18,LD17,LD16,LD15,LD14,LD13,LD12,LD11,LD10,
                     LD9,LD8,LD7,LD6,LD5,LD4,LD3,LD2,LD1,LD0);

  PinListSet (LCTL,  LLOCK_,
                     LRW1_,LRW0_,LSTRB1_,LSTRB0_,
                     LRDY1_,LRDY0_,LPAGE1,LPAGE0,
                     LSTAT3,LSTAT2,LSTAT1,LSTAT0,
                     LAE_,LDE_,LCE1_,LCE0_);

  PinListSet (GDBUS, GD31,GD30,GD29,GD28,GD27,GD26,GD25,GD24,GD23,GD22,GD21,
                     GD20,GD19,GD18,GD17,GD16,GD15,GD14,GD13,GD12,GD11,GD10,
                     GD9,GD8,GD7,GD6,GD5,GD4,GD3,GD2,GD1,GD0);

  PinListSet (GCTL,  GLOCK_,
                     GRW1_,GRW0_,GSTRB1_,GSTRB0_,
                     GRDY1_,GRDY0_,GPAGE1,GPAGE0,
                     GSTAT3,GSTAT2,GSTAT1,GSTAT0,
                     GAE_,GDE_,GCE1_,GCE0_);

  PinListSet (STAT,  LSTAT3,LSTAT2,LSTAT1,LSTAT0,GSTAT3,GSTAT2,GSTAT1,GSTAT0);
  PinListSet (LOCK_, LLOCK_,GLOCK_);
  PinListSet (RDY_,  LRDY1_,LRDY0_,GRDY1_,GRDY0_);
  PinListSet (ENB_,  LAE_,LDE_,LCE1_,LCE0_,GAE_,GDE_,GCE1_,GCE0_);

  PinListSet (CONTROL, IACK_,NMI_,IIOF3,IIOF2,IIOF1,IIOF0,
                       ROMEN,RESET_,RESETLOC1,RESETLOC0);

  PinListSet (IIOF, IIOF3,IIOF2,IIOF1,IIOF0);
  PinListSet (RESETLOC, RESETLOC1,RESETLOC0);

  PinListSet (EMU, EMU0,EMU1);

  PinListSet (JTAG, TCK,TDI,TDO,TMS,TRS);

  PinListSet (JTINPUTS, TDI,TMS);


 case TIDeviceType of
 SMJ320C40GFM_pg3x_40MHz, SMJ320C40GFM_pg5x_40MHz, SMJ320C40GFM_pg5x_50MHz,
 SMJ320C40GFM_pg5x_60MHz, SMJ320C40HFHM_pg3x_40MHz, SMJ320C40HFHM_pg5x_40MHz,
 SMJ320C40HFHM_pg5x_50MHz, SMJ320C40HFHM_pg5x_60MHz, SM320C40TAB_pg3x_40MHz,
 SM320C40TAB_pg5x_40MHz, SM320C40TAB_pg5x_50MHz, SM320C40TAB_pg5x_60MHz,
 TMS320C40TAL_pg3x_50MHz, TMS320C40TAL_pg5x_60MHz, MPM11856KGDC:
 begin





  PinListSet (LABUS, LA30,LA29,LA28,LA27,LA26,LA25,LA24,LA23,LA22,LA21,
                     LA20,LA19,LA18,LA17,LA16,LA15,LA14,LA13,LA12,LA11,LA10,
                     LA9,LA8,LA7,LA6,LA5,LA4,LA3,LA2,LA1,LA0);

  PinListSet (GABUS, GA30,GA29,GA28,GA27,GA26,GA25,GA24,GA23,GA22,GA21,
                     GA20,GA19,GA18,GA17,GA16,GA15,GA14,GA13,GA12,GA11,GA10,
                     GA9,GA8,GA7,GA6,GA5,GA4,GA3,GA2,GA1,GA0);

  PinListSet (TIMERS, TCLK0,TCLK1);

  PinListSet (COMPORT0, C0D7,C0D6,C0D5,C0D4,C0D3,C0D2,C0D1,C0D0,
                        CRDY0_,CSTRB0_,CREQ0_,CACK0_);

  PinListSet (COMPORT1, C1D7,C1D6,C1D5,C1D4,C1D3,C1D2,C1D1,C1D0,
                        CRDY1_,CSTRB1_,CREQ1_,CACK1_);

  PinListSet (COMPORT2, C2D7,C2D6,C2D5,C2D4,C2D3,C2D2,C2D1,C2D0,
                        CRDY2_,CSTRB2_,CREQ2_,CACK2_);

  PinListSet (COMPORT3, C3D7,C3D6,C3D5,C3D4,C3D3,C3D2,C3D1,C3D0,
                        CRDY3_,CSTRB3_,CREQ3_,CACK3_);

  PinListSet (COMPORT4, C4D7,C4D6,C4D5,C4D4,C4D3,C4D2,C4D1,C4D0,
                        CRDY4_,CSTRB4_,CREQ4_,CACK4_);

  PinListSet (COMPORT5, C5D7,C5D6,C5D5,C5D4,C5D3,C5D2,C5D1,C5D0,
                        CRDY5_,CSTRB5_,CREQ5_,CACK5_);

  PinListSet (CD,     C0D7,C0D6,C0D5,C0D4,C0D3,C0D2,C0D1,C0D0,
                      C1D7,C1D6,C1D5,C1D4,C1D3,C1D2,C1D1,C1D0,
                      C2D7,C2D6,C2D5,C2D4,C2D3,C2D2,C2D1,C2D0,
                      C3D7,C3D6,C3D5,C3D4,C3D3,C3D2,C3D1,C3D0,
                      C4D7,C4D6,C4D5,C4D4,C4D3,C4D2,C4D1,C4D0,
                      C5D7,C5D6,C5D5,C5D4,C5D3,C5D2,C5D1,C5D0);
  PinListSet (CRDY_,  CRDY0_,CRDY1_,CRDY2_,CRDY3_,CRDY4_,CRDY5_);
  PinListSet (CSTRB_, CSTRB0_,CSTRB1_,CSTRB2_,CSTRB3_,CSTRB4_,CSTRB5_);
  PinListSet (CREQ_,  CREQ0_,CREQ1_,CREQ2_,CREQ3_,CREQ4_,CREQ5_);
  PinListSet (CACK_,  CACK0_,CACK1_,CACK2_,CACK3_,CACK4_,CACK5_);
  PinListSet (COMPORT_CNTL, CRDY_, CSTRB_, CREQ_, CACK_);


  PinListSet (FIELD1,  X2CLKIN,X1);        
  PinListSet (FIELD2,  CLKOUTS);           
  PinListSet (FIELD3,  LDBUS);             
  PinListSet (FIELD4,  LABUS);             
  PinListSet (FIELD5,  LCTL);              
  PinListSet (FIELD6,  GDBUS);             
  PinListSet (FIELD7,  GABUS);             
  PinListSet (FIELD8,  GCTL);              
  PinListSet (FIELD9,  CONTROL);           
  PinListSet (FIELD10, JTAG,TIMERS,EMU);   
  PinListSet (FIELD11, COMPORT0);          
  PinListSet (FIELD12, COMPORT1);          
  PinListSet (FIELD13, COMPORT2);          
  PinListSet (FIELD14, COMPORT3);          
  PinListSet (FIELD15, COMPORT4);          
  PinListSet (FIELD16, COMPORT5);          


  PinListSet (INPUTS, LRDY1_,LRDY0_,LAE_,LDE_,LCE1_,LCE0_,    
                      GRDY1_,GRDY0_,GAE_,GDE_,GCE1_,GCE0_,    
                      ROMEN,RESET_,RESETLOC1,RESETLOC0,NMI_,  
                      TCK,TDI,TMS,TRS);

  PinListSet (OUTPUTS, X1,CLKOUTS,LABUS,LRW1_,LRW0_,LSTRB1_,  
                       LSTRB0_,LPAGE1,LPAGE0,LSTAT3,LSTAT2,   
                       LSTAT1,LSTAT0,LLOCK_,GABUS,GRW1_,GRW0_,
                       GSTRB1_,GSTRB0_,GPAGE1,GPAGE0,GSTAT3,
                       GSTAT2,GSTAT1,GSTAT0,GLOCK_,IACK_,TDO);

  PinListSet (OUTPUTS_NO_X1, CLKOUTS,LABUS,LRW1_,LRW0_,LSTRB1_,  
                       LSTRB0_,LPAGE1,LPAGE0,LSTAT3,LSTAT2,   
                       LSTAT1,LSTAT0,LLOCK_,GABUS,GRW1_,GRW0_,
                       GSTRB1_,GSTRB0_,GPAGE1,GPAGE0,GSTAT3,
                       GSTAT2,GSTAT1,GSTAT0,GLOCK_,IACK_,TDO);

  PinListSet (IOPINS, LDBUS,GDBUS,IIOF3,IIOF2,IIOF1,IIOF0,    
                      TIMERS,EMU,COMPORT0,COMPORT1,COMPORT2,
                      COMPORT3,COMPORT4,COMPORT5);

  PinListSet (IOPINS_NO_LDBUS, GDBUS,IIOF3,IIOF2,IIOF1,IIOF0, 
                      TIMERS,EMU,COMPORT0,COMPORT1,COMPORT2,
                      COMPORT3,COMPORT4,COMPORT5);

  PinListSet (IOPINS_NO_CD, LDBUS, GDBUS,IIOF3,IIOF2,IIOF1,IIOF0, 
                      TIMERS,EMU,CRDY_,CSTRB_,CREQ_,CACK_);












  PinListSet (EVENPINS, GD30,GD28,GD26,GD25,GD23,GD21,GD19,GD17,GD15,GD13,GD11,
                        GD9,GD7,GD5,GD4,GD2,GD0,GRDY1_,GCE0_,GDE_,TDO,TMS,EMU0,
                        GPAGE1,GSTRB1_,GSTAT1,GSTAT2,GPAGE0,GSTRB0_,RESETLOC1,
                        RESETLOC0,CRDY5_,CACK5_,CRDY4_,CACK4_,C5D6,C5D4,C5D2,
                        C5D0,C4D7,C4D5,C4D3,C4D1,C3D6,C3D4,C3D2,C3D0,C2D6,C2D4,
                        C2D2,C2D0,CRDY3_,CACK3_,CRDY2_,CACK2_,CSTRB1_,CREQ1_,
                        CSTRB0_,CREQ0_,C1D6,C1D4,C1D2,C1D0,C0D7,C0D5,C0D3,C0D1,
                        ROMEN,IIOF2,NMI_,LRW0_,LRDY0_,LSTRB1_,LPAGE1,LCE1_,
                        TCLK0,H3,LAE_,LLOCK_,LSTAT1,LSTAT3,X1,LA29,LA27,LA26,
                        LA24,LA22,LA20,LA18,LA16,LA15,LA13,LA11,LA9,LA7,LA5,
                        LA2,LA0,LD30,LD28,LD27,LD25,LD23,LD21,LD19,LD17,LD15,
                        LD13,LD11,LD9,LD7,LD5,LD4,LD2,LD0,GA29,GA26,GA24,GA22,
                        GA20,GA18,GA15,GA13,GA11,GA9,GA7,GA5,GA2,GA0);

  PinListSet (ODDPINS,  GD31,GD29,GD27,GD24,GD22,GD20,GD18,GD16,GD14,GD12,GD10,
                        GD8,GD6,GD3,GD1,GCE1_,GLOCK_,GRDY0_,TCK,TDI,TRS,EMU1,
                        GRW1_,GSTAT0,GSTAT3,GRW0_,GAE_,RESET_,CSTRB5_,CREQ5_,
                        CSTRB4_,CREQ4_,C5D7,C5D5,C5D3,C5D1,C4D6,C4D4,C4D2,C4D0,
                        C3D7,C3D5,C3D3,C3D1,C2D7,C2D5,C2D3,C2D1,CSTRB3_,CREQ3_,
                        CSTRB2_,CREQ2_,CRDY1_,CACK1_,CRDY0_,CACK0_,C1D7,C1D5,
                        C1D3,C1D1,C0D6,C0D4,C0D2,C0D0,IIOF0,IIOF1,IIOF3,LSTRB0_,
                        LPAGE0,LCE0_,LRW1_,LRDY1_,LDE_,TCLK1,H1,LSTAT0,LSTAT2,
                        IACK_,X2CLKIN,LA30,LA28,LA25,LA23,LA21,LA19,LA17,LA14,
                        LA12,LA10,LA8,LA6,LA4,LA3,LA1,LD31,LD29,LD26,LD24,LD22,
                        LD20,LD18,LD16,LD14,LD12,LD10,LD8,LD6,LD3,LD1,GA30,GA28,
                        GA27,GA25,GA23,GA21,GA19,GA17,GA16,GA14,GA12,GA10,GA8,
                        GA6,GA4,GA3,GA1);

  PinListSet (ALLPINS,  EVENPINS,ODDPINS);          








  PinListSet (EVENINS, GRDY1_,GCE0_,GDE_,           
                       RESETLOC1,RESETLOC0,ROMEN,
                       NMI_,LRDY0_,LCE1_,LAE_);

  PinListSet (ODDINS,  GCE1_,GRDY0_,                
                       GAE_,RESET_,LCE0_,
                       LRDY1_,LDE_);

  PinListSet (PMUINS,  TCK,TDI,TMS);                
                                                    

  PinListSet (TESTINS, EVENINS,ODDINS,X2CLKIN);     

  PinListSet (NOTESTINS, PMUINS,TRS);               
                                                    
                                                    

  PinListSet (ALLOUTS, OUTPUTS);                    
                                                    

  PinListSet (ALLIOS, IOPINS);                      
                                                    
                                                    








  PinListSet (EVENTRISTATE, GD30,GD28,GD26,GD25,GD23,GD21,GD19,GD17,GD15,GD13,GD11,
                            GD9,GD7,GD5,GD4,GD2,GD0,GPAGE1,GSTRB1_,GPAGE0,GSTRB0_,
                            CRDY5_,CACK5_,CRDY4_,CACK4_,C5D6,C5D4,C5D2,C5D0,C4D7,
                            C4D5,C4D3,C4D1,C3D6,C3D4,C3D2,C3D0,C2D6,C2D4,C2D2,C2D0,
                            CRDY3_,CACK3_,CRDY2_,CACK2_,CSTRB1_,CREQ1_,CSTRB0_,CREQ0_,
                            C1D6,C1D4,C1D2,C1D0,C0D7,C0D5,C0D3,C0D1,IIOF2,LRW0_,LSTRB1_,
                            LPAGE1,TCLK0,LA29,LA27,LA26,LA24,LA22,LA20,LA18,LA16,LA15,
                            LA13,LA11,LA9,LA7,LA5,LA2,LA0,LD30,LD28,LD27,LD25,LD23,LD21,
                            LD19,LD17,LD15,LD13,LD11,LD9,LD7,LD5,LD4,LD2,LD0,GA29,GA26,
                            GA24,GA22,GA20,GA18,GA15,GA13,GA11,GA9,GA7,GA5,GA2,GA0);

  PinListSet (ODDTRISTATE,  GD31,GD29,GD27,GD24,GD22,GD20,GD18,GD16,GD14,GD12,GD10,
                            GD8,GD6,GD3,GD1,GRW1_,GRW0_,CSTRB5_,CREQ5_,CSTRB4_,CREQ4_,
                            C5D7,C5D5,C5D3,C5D1,C4D6,C4D4,C4D2,C4D0,C3D7,C3D5,C3D3,C3D1,
                            C2D7,C2D5,C2D3,C2D1,CSTRB3_,CREQ3_,CSTRB2_,CREQ2_,CRDY1_,
                            CACK1_,CRDY0_,CACK0_,C1D7,C1D5,C1D3,C1D1,C0D6,C0D4,C0D2,C0D0,
                            IIOF0,IIOF1,IIOF3,LSTRB0_,LPAGE0,LRW1_,TCLK1,LA30,LA28,LA25,
                            LA23,LA21,LA19,LA17,LA14,LA12,LA10,LA8,LA6,LA4,LA3,LA1,LD31,
                            LD29,LD26,LD24,LD22,LD20,LD18,LD16,LD14,LD12,LD10,LD8,LD6,LD3,
                            LD1,GA30,GA28,GA27,GA25,GA23,GA21,GA19,GA17,GA16,GA14,GA12,
                            GA10,GA8,GA6,GA4,GA3,GA1);

  PinListSet (ALLTRISTATE,  EVENTRISTATE,ODDTRISTATE); 


  PinListSet (NOTRISTATEOUTS, X1,CLKOUTS,      
                              LSTAT3,LSTAT2,LSTAT1,LSTAT0,LLOCK_,
                              GSTAT3,GSTAT2,GSTAT1,GSTAT0,GLOCK_,IACK_,TDO);

  PinListSet (NOTRISTATEIOS,  EMU);            








  PinListSet (MUXPINS, X2CLKIN);

 end; 
 
TMS320C41QFP:
 begin





  PinListSet (LABUS, LA22,LA21,
                     LA20,LA19,LA18,LA17,LA16,LA15,LA14,LA13,LA12,LA11,LA10,
                     LA9,LA8,LA7,LA6,LA5,LA4,LA3,LA2,LA1,LA0);

  PinListSet (GABUS, GA24,GA23,GA22,GA21,
                     GA20,GA19,GA18,GA17,GA16,GA15,GA14,GA13,GA12,GA11,GA10,
                     GA9,GA8,GA7,GA6,GA5,GA4,GA3,GA2,GA1,GA0);

  PinListSet (TIMERS, TCLK0);

  PinListSet (COMPORT2, C2D7,C2D6,C2D5,C2D4,C2D3,C2D2,C2D1,C2D0,
                        CRDY2_,CSTRB2_,CREQ2_,CACK2_);

  PinListSet (COMPORT3, C3D7,C3D6,C3D5,C3D4,C3D3,C3D2,C3D1,C3D0,
                        CRDY3_,CSTRB3_,CREQ3_,CACK3_);

  PinListSet (CD,     C2D7,C2D6,C2D5,C2D4,C2D3,C2D2,C2D1,C2D0,
                      C3D7,C3D6,C3D5,C3D4,C3D3,C3D2,C3D1,C3D0);
  PinListSet (CRDY_,  CRDY2_,CRDY3_);
  PinListSet (CSTRB_, CSTRB2_,CSTRB3_);
  PinListSet (CREQ_,  CREQ2_,CREQ3_);
  PinListSet (CACK_,  CACK2_,CACK3_);


  PinListSet (FIELD1,  X2CLKIN,X1);        
  PinListSet (FIELD2,  CLKOUTS);           
  PinListSet (FIELD3,  LDBUS);             
  PinListSet (FIELD4,  LABUS);             
  PinListSet (FIELD5,  LCTL);              
  PinListSet (FIELD6,  GDBUS);             
  PinListSet (FIELD7,  GABUS);             
  PinListSet (FIELD8,  GCTL);              
  PinListSet (FIELD9,  CONTROL);           
  PinListSet (FIELD10, JTAG,TIMERS,EMU);   
  PinListSet (FIELD13, COMPORT2);          
  PinListSet (FIELD14, COMPORT3);          


  PinListSet (INPUTS, LRDY1_,LRDY0_,LAE_,LDE_,LCE1_,LCE0_,    
                      GRDY1_,GRDY0_,GAE_,GDE_,GCE1_,GCE0_,    
                      ROMEN,RESET_,RESETLOC1,RESETLOC0,NMI_,  
                      TCK,TDI,TMS,TRS);

  PinListSet (OUTPUTS, X1,CLKOUTS,LABUS,LRW1_,LRW0_,LSTRB1_,  
                       LSTRB0_,LPAGE1,LPAGE0,LSTAT3,LSTAT2,   
                       LSTAT1,LSTAT0,LLOCK_,GABUS,GRW1_,GRW0_,
                       GSTRB1_,GSTRB0_,GPAGE1,GPAGE0,GSTAT3,
                       GSTAT2,GSTAT1,GSTAT0,GLOCK_,IACK_,TDO);

  PinListSet (OUTPUTS_NO_X1,CLKOUTS,LABUS,LRW1_,LRW0_,LSTRB1_,  
                       LSTRB0_,LPAGE1,LPAGE0,LSTAT3,LSTAT2,   
                       LSTAT1,LSTAT0,LLOCK_,GABUS,GRW1_,GRW0_,
                       GSTRB1_,GSTRB0_,GPAGE1,GPAGE0,GSTAT3,
                       GSTAT2,GSTAT1,GSTAT0,GLOCK_,IACK_,TDO);


  PinListSet (IOPINS, LDBUS,GDBUS,IIOF3,IIOF2,IIOF1,IIOF0,    
                      TIMERS,EMU,COMPORT2,COMPORT3);

  PinListSet (IOPINS_NO_LDBUS,GDBUS,IIOF3,IIOF2,IIOF1,IIOF0,    
                     TIMERS,EMU,COMPORT2,COMPORT3);

  PinListSet (IOPINS_NO_CD, LDBUS, GDBUS,IIOF3,IIOF2,IIOF1,IIOF0, 
                      TIMERS,EMU,CRDY_,CSTRB_,CREQ_,CACK_);












  PinListSet (EVENPINS, GD30,GD28,GD26,GD24,GD22,GD20,GD18,GD16,GD14,GD12,
                        GD10,GD8,GD6,GD4,GD2,GD0,GRDY1_,GCE0_,GDE_,TDO,TMS,
                        EMU0,GPAGE1,GSTRB1_,GSTAT1,GSTAT3,GRW0_,GAE_,
                        RESETLOC0,C3D7,C3D5,C3D3,C3D1,C2D7,C2D5,C2D3,C2D1,
                        CRDY3_,CACK3_,CRDY2_,CACK2_,ROMEN,IIOF1,IIOF3,
                        LSTRB0_,LPAGE0,LCE0_,LRW1_,LRDY1_,LDE_,H3,LAE_,
                        LSTAT0,LSTAT2,IACK_,X2CLKIN,LA21,LA19,LA17,LA15,
                        LA13,LA11,LA9,LA7,LA5,LA3,LA1,LD31,LD29,LD27,LD25,
                        LD23,LD21,LD19,LD17,LD15,LD13,LD11,LD9,LD7,LD5,LD3,
                        LD1,GA24,GA22,GA20,GA18,GA16,GA14,GA12,GA10,GA8,
                        GA6,GA4,GA2,GA0);

  PinListSet (ODDPINS,  GD31,GD29,GD27,GD25,GD23,GD21,GD19,GD17,GD15,GD13,
                        GD11,GD9,GD7,GD5,GD3,GD1,GCE1_,GLOCK_,GRDY0_,TCK,
                        TDI,TRS,EMU1,GRW1_,GSTAT0,GSTAT2,GPAGE0,GSTRB0_,
                        RESETLOC1,RESET_,C3D6,C3D4,C3D2,C3D0,C2D6,C2D4,
                        C2D2,C2D0,CSTRB3_,CREQ3_,CSTRB2_,CREQ2_,IIOF0,
                        IIOF2,NMI_,LRW0_,LRDY0_,LSTRB1_,LPAGE1,LCE1_,TCLK0,
                        H1,LLOCK_,LSTAT1,LSTAT3,X1,LA22,LA20,LA18,LA16,
                        LA14,LA12,LA10,LA8,LA6,LA4,LA2,LA0,LD30,LD28,LD26,
                        LD24,LD22,LD20,LD18,LD16,LD14,LD12,LD10,LD8,LD6,
                        LD4,LD2,LD0,GA23,GA21,GA19,GA17,GA15,GA13,GA11,GA9,
                        GA7,GA5,GA3,GA1);

  PinListSet (ALLPINS,  EVENPINS,ODDPINS);          








  PinListSet (EVENINS, GRDY1_,GCE0_,GDE_,           
                       GAE_,RESETLOC0,ROMEN,
                       LCE0_,LRDY1_,LDE_,LAE_);

  PinListSet (ODDINS,  GCE1_,GRDY0_,                
                       RESETLOC1,RESET_,NMI_,
                       LRDY0_,LCE1_);

  PinListSet (PMUINS,  TCK,TDI,TMS);                
                                                    

  PinListSet (TESTINS, EVENINS,ODDINS,X2CLKIN);     

  PinListSet (NOTESTINS, PMUINS,TRS);               
                                                    
                                                    

  PinListSet (ALLOUTS, OUTPUTS);                    
                                                    

  PinListSet (ALLIOS, IOPINS);                      
                                                    
                                                    








  PinListSet (EVENTRISTATE, GD30,GD28,GD26,GD24,GD22,GD20,GD18,GD16,GD14,
                            GD12,GD10,GD8,GD6,GD4,GD2,GD0,GPAGE1,GSTRB1_,
                            GRW0_,C3D7,C3D5,C3D3,C3D1,C2D7,C2D5,C2D3,C2D1,
                            CRDY3_,CACK3_,CRDY2_,CACK2_,IIOF1,IIOF3,
                            LSTRB0_,LPAGE0,LRW1_,LA21,LA19,LA17,LA15,LA13,
                            LA11,LA9,LA7,LA5,LA3,LA1,LD31,LD29,LD27,LD25,
                            LD23,LD21,LD19,LD17,LD15,LD13,LD11,LD9,LD7,LD5,
                            LD3,LD1,GA24,GA22,GA20,GA18,GA16,GA14,GA12,
                            GA10,GA8,GA6,GA4,GA2,GA0);

  PinListSet (ODDTRISTATE,  GD31,GD29,GD27,GD25,GD23,GD21,GD19,GD17,GD15,
                            GD13,GD11,GD9,GD7,GD5,GD3,GD1,GRW1_,GPAGE0,
                            GSTRB0_,C3D6,C3D4,C3D2,C3D0,C2D6,C2D4,C2D2,
                            C2D0,CSTRB3_,CREQ3_,CSTRB2_,CREQ2_,IIOF0,IIOF2,
                            LRW0_,LSTRB1_,LPAGE1,TCLK0,LA22,LA20,LA18,LA16,
                            LA14,LA12,LA10,LA8,LA6,LA4,LA2,LA0,LD30,LD28,
                            LD26,LD24,LD22,LD20,LD18,LD16,LD14,LD12,LD10,
                            LD8,LD6,LD4,LD2,LD0,GA23,GA21,GA19,GA17,GA15,
                            GA13,GA11,GA9,GA7,GA5,GA3,GA1);

  PinListSet (ALLTRISTATE,  EVENTRISTATE,ODDTRISTATE); 


  PinListSet (NOTRISTATEOUTS, X1,CLKOUTS,      
                              LSTAT3,LSTAT2,LSTAT1,LSTAT0,LLOCK_,
                              GSTAT3,GSTAT2,GSTAT1,GSTAT0,GLOCK_,IACK_,TDO);

  PinListSet (NOTRISTATEIOS,  EMU);            








  PinListSet (MUXPINS, X2CLKIN);

 end; 
 end; 

end; 


	
        
	
	
        
        
        
        
        
        
        
        
        
        
        
        
	
        
        
	
	

procedure PinListInit;
begin

  PinListSetNull(X2CLKIN);
  PinListSetNull(X1);
  PinListSetNull(H1);
  PinListSetNull(H3);

  PinListSetNull(LD31);
  PinListSetNull(LD30);
  PinListSetNull(LD29);
  PinListSetNull(LD28);
  PinListSetNull(LD27);
  PinListSetNull(LD26);
  PinListSetNull(LD25);
  PinListSetNull(LD24);
  PinListSetNull(LD23);
  PinListSetNull(LD22);
  PinListSetNull(LD21);
  PinListSetNull(LD20);
  PinListSetNull(LD19);
  PinListSetNull(LD18);
  PinListSetNull(LD17);
  PinListSetNull(LD16);
  PinListSetNull(LD15);
  PinListSetNull(LD14);
  PinListSetNull(LD13);
  PinListSetNull(LD12);
  PinListSetNull(LD11);
  PinListSetNull(LD10);
  PinListSetNull(LD9);
  PinListSetNull(LD8);
  PinListSetNull(LD7);
  PinListSetNull(LD6);
  PinListSetNull(LD5);
  PinListSetNull(LD4);
  PinListSetNull(LD3);
  PinListSetNull(LD2);
  PinListSetNull(LD1);
  PinListSetNull(LD0);

  PinListSetNull(LA30);
  PinListSetNull(LA29);
  PinListSetNull(LA28);
  PinListSetNull(LA27);
  PinListSetNull(LA26);
  PinListSetNull(LA25);
  PinListSetNull(LA24);
  PinListSetNull(LA23);
  PinListSetNull(LA22);
  PinListSetNull(LA21);
  PinListSetNull(LA20);
  PinListSetNull(LA19);
  PinListSetNull(LA18);
  PinListSetNull(LA17);
  PinListSetNull(LA16);
  PinListSetNull(LA15);
  PinListSetNull(LA14);
  PinListSetNull(LA13);
  PinListSetNull(LA12);
  PinListSetNull(LA11);
  PinListSetNull(LA10);
  PinListSetNull(LA9);
  PinListSetNull(LA8);
  PinListSetNull(LA7);
  PinListSetNull(LA6);
  PinListSetNull(LA5);
  PinListSetNull(LA4);
  PinListSetNull(LA3);
  PinListSetNull(LA2);
  PinListSetNull(LA1);
  PinListSetNull(LA0);

  PinListSetNull(LRW1_);
  PinListSetNull(LRW0_);
  PinListSetNull(LSTRB1_);
  PinListSetNull(LSTRB0_);
  PinListSetNull(LRDY1_);
  PinListSetNull(LRDY0_);
  PinListSetNull(LPAGE1);
  PinListSetNull(LPAGE0);
  PinListSetNull(LSTAT3);
  PinListSetNull(LSTAT2);
  PinListSetNull(LSTAT1);
  PinListSetNull(LSTAT0);
  PinListSetNull(LLOCK_);
  PinListSetNull(LAE_);
  PinListSetNull(LDE_);
  PinListSetNull(LCE1_);
  PinListSetNull(LCE0_);

  PinListSetNull(GD31);
  PinListSetNull(GD30);
  PinListSetNull(GD29);
  PinListSetNull(GD28);
  PinListSetNull(GD27);
  PinListSetNull(GD26);
  PinListSetNull(GD25);
  PinListSetNull(GD24);
  PinListSetNull(GD23);
  PinListSetNull(GD22);
  PinListSetNull(GD21);
  PinListSetNull(GD20);
  PinListSetNull(GD19);
  PinListSetNull(GD18);
  PinListSetNull(GD17);
  PinListSetNull(GD16);
  PinListSetNull(GD15);
  PinListSetNull(GD14);
  PinListSetNull(GD13);
  PinListSetNull(GD12);
  PinListSetNull(GD11);
  PinListSetNull(GD10);
  PinListSetNull(GD9);
  PinListSetNull(GD8);
  PinListSetNull(GD7);
  PinListSetNull(GD6);
  PinListSetNull(GD5);
  PinListSetNull(GD4);
  PinListSetNull(GD3);
  PinListSetNull(GD2);
  PinListSetNull(GD1);
  PinListSetNull(GD0);

  PinListSetNull(GA30);
  PinListSetNull(GA29);
  PinListSetNull(GA28);
  PinListSetNull(GA27);
  PinListSetNull(GA26);
  PinListSetNull(GA25);
  PinListSetNull(GA24);
  PinListSetNull(GA23);
  PinListSetNull(GA22);
  PinListSetNull(GA21);
  PinListSetNull(GA20);
  PinListSetNull(GA19);
  PinListSetNull(GA18);
  PinListSetNull(GA17);
  PinListSetNull(GA16);
  PinListSetNull(GA15);
  PinListSetNull(GA14);
  PinListSetNull(GA13);
  PinListSetNull(GA12);
  PinListSetNull(GA11);
  PinListSetNull(GA10);
  PinListSetNull(GA9);
  PinListSetNull(GA8);
  PinListSetNull(GA7);
  PinListSetNull(GA6);
  PinListSetNull(GA5);
  PinListSetNull(GA4);
  PinListSetNull(GA3);
  PinListSetNull(GA2);
  PinListSetNull(GA1);
  PinListSetNull(GA0);

  PinListSetNull(GRW1_);
  PinListSetNull(GRW0_);
  PinListSetNull(GSTRB1_);
  PinListSetNull(GSTRB0_);
  PinListSetNull(GRDY1_);
  PinListSetNull(GRDY0_);
  PinListSetNull(GPAGE1);
  PinListSetNull(GPAGE0);
  PinListSetNull(GSTAT3);
  PinListSetNull(GSTAT2);
  PinListSetNull(GSTAT1);
  PinListSetNull(GSTAT0);
  PinListSetNull(GLOCK_);
  PinListSetNull(GAE_);
  PinListSetNull(GDE_);
  PinListSetNull(GCE1_);
  PinListSetNull(GCE0_);

  PinListSetNull(IACK_);
  PinListSetNull(NMI_);
  PinListSetNull(IIOF3);
  PinListSetNull(IIOF2);
  PinListSetNull(IIOF1);
  PinListSetNull(IIOF0);
  PinListSetNull(ROMEN);
  PinListSetNull(RESET_);
  PinListSetNull(RESETLOC1);
  PinListSetNull(RESETLOC0);

  PinListSetNull(TCLK0);
  PinListSetNull(TCLK1);

  PinListSetNull(EMU0);
  PinListSetNull(EMU1);

  PinListSetNull(TCK);
  PinListSetNull(TDI);
  PinListSetNull(TDO);
  PinListSetNull(TMS);
  PinListSetNull(TRS);

  PinListSetNull(C0D7);
  PinListSetNull(C0D6);
  PinListSetNull(C0D5);
  PinListSetNull(C0D4);
  PinListSetNull(C0D3);
  PinListSetNull(C0D2);
  PinListSetNull(C0D1);
  PinListSetNull(C0D0);
  PinListSetNull(CRDY0_);
  PinListSetNull(CSTRB0_);
  PinListSetNull(CREQ0_);
  PinListSetNull(CACK0_);

  PinListSetNull(C1D7);
  PinListSetNull(C1D6);
  PinListSetNull(C1D5);
  PinListSetNull(C1D4);
  PinListSetNull(C1D3);
  PinListSetNull(C1D2);
  PinListSetNull(C1D1);
  PinListSetNull(C1D0);
  PinListSetNull(CRDY1_);
  PinListSetNull(CSTRB1_);
  PinListSetNull(CREQ1_);
  PinListSetNull(CACK1_);

  PinListSetNull(C2D7);
  PinListSetNull(C2D6);
  PinListSetNull(C2D5);
  PinListSetNull(C2D4);
  PinListSetNull(C2D3);
  PinListSetNull(C2D2);
  PinListSetNull(C2D1);
  PinListSetNull(C2D0);
  PinListSetNull(CRDY2_);
  PinListSetNull(CSTRB2_);
  PinListSetNull(CREQ2_);
  PinListSetNull(CACK2_);

  PinListSetNull(C3D7);
  PinListSetNull(C3D6);
  PinListSetNull(C3D5);
  PinListSetNull(C3D4);
  PinListSetNull(C3D3);
  PinListSetNull(C3D2);
  PinListSetNull(C3D1);
  PinListSetNull(C3D0);
  PinListSetNull(CRDY3_);
  PinListSetNull(CSTRB3_);
  PinListSetNull(CREQ3_);
  PinListSetNull(CACK3_);

  PinListSetNull(C4D7);
  PinListSetNull(C4D6);
  PinListSetNull(C4D5);
  PinListSetNull(C4D4);
  PinListSetNull(C4D3);
  PinListSetNull(C4D2);
  PinListSetNull(C4D1);
  PinListSetNull(C4D0);
  PinListSetNull(CRDY4_);
  PinListSetNull(CSTRB4_);
  PinListSetNull(CREQ4_);
  PinListSetNull(CACK4_);

  PinListSetNull(C5D7);
  PinListSetNull(C5D6);
  PinListSetNull(C5D5);
  PinListSetNull(C5D4);
  PinListSetNull(C5D3);
  PinListSetNull(C5D2);
  PinListSetNull(C5D1);
  PinListSetNull(C5D0);
  PinListSetNull(CRDY5_);
  PinListSetNull(CSTRB5_);
  PinListSetNull(CREQ5_);
  PinListSetNull(CACK5_);

  PinListSetNull(CLKOUTS);
  PinListSetNull(LDBUS);
  PinListSetNull(LABUS);
  PinListSetNull(LCTL);
  PinListSetNull(GDBUS);
  PinListSetNull(GABUS);
  PinListSetNull(GCTL);
  PinListSetNull(STAT);
  PinListSetNull(LOCK_);
  PinListSetNull(RDY_);
  PinListSetNull(ENB_);
  PinListSetNull(CONTROL);
  PinListSetNull(IIOF);
  PinListSetNull(RESETLOC);
  PinListSetNull(TIMERS);
  PinListSetNull(EMU);
  PinListSetNull(JTAG);
  PinListSetNull(JTINPUTS);
  PinListSetNull(COMPORT0);
  PinListSetNull(COMPORT1);
  PinListSetNull(COMPORT2);
  PinListSetNull(COMPORT3);
  PinListSetNull(COMPORT4);
  PinListSetNull(COMPORT5);
  PinListSetNull(CD);
  PinListSetNull(CRDY_);
  PinListSetNull(CSTRB_);
  PinListSetNull(CREQ_);
  PinListSetNull(CACK_);

  PinListSetNull(FIELD1);
  PinListSetNull(FIELD2);
  PinListSetNull(FIELD3);
  PinListSetNull(FIELD4);
  PinListSetNull(FIELD5);
  PinListSetNull(FIELD6);
  PinListSetNull(FIELD7);
  PinListSetNull(FIELD8);
  PinListSetNull(FIELD9);
  PinListSetNull(FIELD10);
  PinListSetNull(FIELD11);
  PinListSetNull(FIELD12);
  PinListSetNull(FIELD13);
  PinListSetNull(FIELD14);
  PinListSetNull(FIELD15);
  PinListSetNull(FIELD16);

  PinListSetNull(INPUTS);
  PinListSetNull(OUTPUTS);
  PinListSetNull(IOPINS);
  PinListSetNull(EVENPINS);
  PinListSetNull(ODDPINS);
  PinListSetNull(ALLPINS);
  PinListSetNull(EVENINS);
  PinListSetNull(ODDINS);
  PinListSetNull(PMUINS);
  PinListSetNull(TESTINS);
  PinListSetNull(NOTESTINS);
  PinListSetNull(ALLOUTS);
  PinListSetNull(ALLIOS);
  PinListSetNull(EVENTRISTATE);
  PinListSetNull(ODDTRISTATE);
  PinListSetNull(ALLTRISTATE);
  PinListSetNull(NOTRISTATEOUTS);
  PinListSetNull(NOTRISTATEIOS);
  PinListSetNull(MUXPINS);

end; 

