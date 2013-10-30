procedure SccsIdentificationdevice;
  var
    SccsId	:   String;
  begin
writeln(execFile,'PROC:SccsIdentificationdevice');

    SccsId:= '@(#) device.p 1.5 10/5/94 10:33:03 c TI';
  
writeln(execFile,'PROCEND:SccsIdentificationdevice');
end;

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 


procedure DeviceTableSet;

const
  MINV    =  -2v;            
  MAXV    =   8v;            
  MINI    = -50ma;           
  MAXI    =  50ma;           
  MINVSUB =  -5v;            
  MINVDD  =  -2v;            
  MAXVDD  =   8.5v;          
  MINVDDI = -200000;         
  MAXVDDI =  2000000;        

var
  devicetablename : String;


begin
writeln(execFile,'PROC:DeviceTableSet');


 case TITestType of

 Pre_Burnin, Final, QA:
 begin
   DeviceTableOpen;

   devicetablename := 'TMX320C44GGCDeviceTable';
   DeviceTableSetName(devicetablename);

    
    
    
    
    
    
    
    
    


    
    
    



   PinSetMP(GA0,        149,     146,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA1,        150,      26,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA10,       160,      63,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA11,       162,     183,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA12,       165,     144,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA13,       166,     222,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA14,       167,     143,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA15,       168,      23,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA16,       169,      24,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA17,       170,     221,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA18,       171,     102,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA19,       174,     181,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA2,        151,     145,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA20,       175,     101,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA21,       176,     182,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA22,       177,      61,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA23,       178,     142,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA3,        152,      25,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA4,        154,     104,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA5,        155,     224,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA6,        156,      64,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA7,        157,     103,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA8,        158,     184,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GA9,        159,     223,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GAE_,        57,      38,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C1D0,       269,     209,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C1D1,       271,     210,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C1D2,       274,      50,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C1D3,       276,     207,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C1D4,       278,      48,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C1D5,       280,       8,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C1D6,       283,      87,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C1D7,       286,     127,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C2D0,        26,       2,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C2D1,        27,     120,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C2D2,        29,     200,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C2D3,        30,       1,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C2D4,        31,     119,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C2D5,        32,     240,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C2D6,        33,     239,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C2D7,        34,      79,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C4D0,        87,     254,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C4D1,        88,     154,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C4D2,        90,     253,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C4D3,        92,     232,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C4D4,        94,      33,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C4D5,        97,     112,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C4D6,        99,      32,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C4D7,       100,     191,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C5D0,        37,     199,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C5D1,        39,      80,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C5D2,        41,     160,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C5D3,        42,      39,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C5D4,        45,     159,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C5D5,        46,      40,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C5D6,        47,     238,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(C5D7,        48,     117,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CACK1_,      13,     202,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CACK2_,      21,      42,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CACK4_,      73,     156,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CACK5_,      50,     198,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CDIR1,       19,     122,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CDIR2,       18,     201,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CDIR4,       16,      81,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CDIR5,       15,     161,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GCE0_,       93,     111,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GCE1_,      101,     151,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CRDY1_,       8,       4,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CRDY2_,      23,     121,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CRDY4_,      85,      74,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CRDY5_,      53,     237,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CREQ1_,      11,      82,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CREQ2_,      20,     162,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CREQ4_,      71,      75,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CREQ5_,      49,     118,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CSTRB1_,     14,     123,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CSTRB2_,     22,      41,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CSTRB4_,     84,     193,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(CSTRB5_,     52,      77,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD0,        104,     152,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD1,        105,     109,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD10,       115,     189,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD11,       118,      29,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD12,       120,     108,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD13,       122,     149,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD14,       123,     251,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD15,       125,     228,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD16,       127,     227,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD17,       128,     187,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD18,       129,     107,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD19,       130,     188,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD2,        106,      31,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD20,       131,      68,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD21,       132,     148,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD22,       135,      67,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD23,       136,     106,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD24,       137,      28,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD25,       138,      27,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD26,       140,     186,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD27,       141,     225,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD28,       142,     105,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD29,       143,      66,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD3,        107,     229,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD30,       144,     185,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD31,       145,      65,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD4,        108,     230,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD5,        110,      69,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD6,        111,     110,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD7,        112,      30,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD8,        113,      70,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GD9,        114,     150,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GDE_,        89,     194,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(EMU0,        75,      35,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(EMU1,        74,     155,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(H1,         266,      90,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(H3,         268,      49,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(IACK_,      270,      10,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(IIOF0,       10,      43,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(IIOF1,        9,     124,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(IIOF2,        5,      44,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(IIOF3,        4,     163,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA0,        232,      15,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA1,        233,      16,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA10,       243,      14,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA11,       245,     173,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA12,       248,      13,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA13,       249,     134,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA14,       250,      92,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA15,       251,      91,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA16,       252,     133,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA17,       253,     212,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA18,       254,     211,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA19,       255,      52,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA2,        234,     136,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA20,       257,     132,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA21,       258,      51,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA22,       259,     131,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA23,       260,     172,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA3,        235,     175,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA4,        237,      94,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA5,        238,     135,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA6,        239,      54,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA7,        240,      93,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA8,        241,     213,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LA9,        242,     214,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LAE_,       287,       7,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LCE0_,      297,     203,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LCE1_,      292,     166,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD0,        183,     141,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD1,        184,      21,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD10,       200,      59,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD11,       203,      19,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD12,       204,     218,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD13,       205,     139,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD14,       206,      98,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD15,       208,      97,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD16,       210,     217,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD17,       211,      57,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD18,       212,      58,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD19,       213,     178,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD2,        185,     220,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD20,       215,     177,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD21,       216,      18,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD22,       219,     138,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD23,       220,      17,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD24,       221,     247,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD25,       222,     137,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD26,       224,     216,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD27,       225,      96,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD28,       226,     215,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD29,       227,      56,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD3,        186,     100,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD30,       228,     176,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD31,       229,      55,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD4,        187,      99,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD5,        192,     179,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD6,        194,      20,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD7,        195,     219,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD8,        196,     140,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LD9,        197,     180,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LDE_,       291,      46,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LLOCK_,     284,     206,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GLOCK_,       95,      71,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LPAGE0,     299,       6,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LPAGE1,     294,      45,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LRDY0_,     298,     241,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LRDY1_,     293,      85,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LRW0_,      300,      83,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LRW1_,      295,       5,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LSTAT0,     279,      88,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LSTAT1,     277,       9,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LSTAT2,     275,     129,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LSTAT3,     273,     170,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LSTRB0_,    301,      84,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(LSTRB1_,    296,     204,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(NMI_,         3,     164,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GPAGE0,      60,     116,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GPAGE1,      72,      36,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GRDY0_,      91,     231,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GRDY1_,      98,      72,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(RESET_,      54,     197,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(RESETLOC0,   55,      78,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(RESETLOC1,   56,      37,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(ROMEN,       12,       3,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GRW0_,       59,     157,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GRW1_,       70,     196,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GSTAT0,      68,      76,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GSTAT1,      66,     235,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GSTAT2,      64,     115,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GSTAT3,      61,     236,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GSTRB0_,     58,     158,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(GSTRB1_,     69,     195,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(TCK,         86,      34,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(TCLK0,      290,     205,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(TCLK1,      289,      86,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(TDI,         76,     234,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(TDO,         80,     113,      IO,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(TMS,         82,     233,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(TRS,         81,      73,       I,  MINV,   MAXV,   MINI,  MAXI);
   PinSetMP(X1,         264,      89,      IO,  MINV,   MAXV,   MINI,  MAXI);
 

   PinSetMuxMP(X2CLKIN,  263,   11, 12,     I,  MINV,   MAXV,   MINI,   MAXI);

     PinSetSupply( VDD,   38,     Supply2,     MINVDD,  MAXVDD, MINVDDI, MAXVDDI);
     PinSetSupply(VSUB,  146,     Supply3,     MINVSUB, MAXVDD, MINVDDI, MAXVDDI);
     PinSetSupply(VSS,    36,     Ground,        0,       0,       0,       0   );

     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     


    DeviceTableClose;
   end;   

  end;   

 
writeln(execFile,'PROCEND:DeviceTableSet');
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


 
 
 

  PinListSet (LABUS, LA23,LA22,LA21,LA20,LA19,LA18,LA17,
                     LA16,LA15,LA14,LA13,LA12,LA11,LA10,
                     LA9,LA8,LA7,LA6,LA5,LA4,LA3,LA2,LA1,LA0);

  PinListSet (GABUS, GA23,GA22,GA21,GA20,GA19,GA18,GA17,
                     GA16,GA15,GA14,GA13,GA12,GA11,GA10,
                     GA9,GA8,GA7,GA6,GA5,GA4,GA3,GA2,GA1,GA0);

  PinListSet (TIMERS, TCLK0,TCLK1);

  PinListSet (CDIR,     CDIR1,CDIR2,CDIR4,CDIR5);

  PinListSet (COMPORT1, C1D7,C1D6,C1D5,C1D4,C1D3,C1D2,C1D1,C1D0,
                        CRDY1_,CSTRB1_,CREQ1_,CACK1_);

  PinListSet (COMPORT2, C2D7,C2D6,C2D5,C2D4,C2D3,C2D2,C2D1,C2D0,
                        CRDY2_,CSTRB2_,CREQ2_,CACK2_);


  PinListSet (COMPORT4, C4D7,C4D6,C4D5,C4D4,C4D3,C4D2,C4D1,C4D0,
                        CRDY4_,CSTRB4_,CREQ4_,CACK4_);

  PinListSet (COMPORT5, C5D7,C5D6,C5D5,C5D4,C5D3,C5D2,C5D1,C5D0,
                        CRDY5_,CSTRB5_,CREQ5_,CACK5_);

  PinListSet (CD,     C1D7,C1D6,C1D5,C1D4,C1D3,C1D2,C1D1,C1D0,
                      C2D7,C2D6,C2D5,C2D4,C2D3,C2D2,C2D1,C2D0,
                      C4D7,C4D6,C4D5,C4D4,C4D3,C4D2,C4D1,C4D0,
                      C5D7,C5D6,C5D5,C5D4,C5D3,C5D2,C5D1,C5D0);

  PinListSet (CRDY_,  CRDY1_,CRDY2_,CRDY4_,CRDY5_);
  PinListSet (CSTRB_, CSTRB1_,CSTRB2_,CSTRB4_,CSTRB5_);
  PinListSet (CREQ_,  CREQ1_,CREQ2_,CREQ4_,CREQ5_);
  PinListSet (CACK_,  CACK1_,CACK2_,CACK4_,CACK5_);
  PinListSet (CSTRBCRDY_,  CRDY1_,CRDY2_,CRDY4_,CRDY5_,
              CSTRB1_,CSTRB2_,CSTRB4_,CSTRB5_);


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
  PinListSet (FIELD11, CDIR);               
  PinListSet (FIELD12, COMPORT1);           
  PinListSet (FIELD13, COMPORT2);           
  PinListSet (FIELD14, COMPORT4);           
  PinListSet (FIELD15, COMPORT5);           


  PinListSet (INPUTS, LRDY1_,LRDY0_,LAE_,LDE_,LCE1_,LCE0_,     
                      GRDY1_,GRDY0_,GAE_,GDE_,GCE1_,GCE0_,     
                      ROMEN,RESET_,RESETLOC1,RESETLOC0,NMI_,   
                      TCK,TDI,TMS,TRS);

  PinListSet (OUTPUTS, X1,CLKOUTS,LABUS,LRW1_,LRW0_,LSTRB1_,   
                       LSTRB0_,LPAGE1,LPAGE0,LSTAT3,LSTAT2,    
                       LSTAT1,LSTAT0,LLOCK_,GABUS,GRW1_,GRW0_,
                       GSTRB1_,GSTRB0_,GPAGE1,GPAGE0,GSTAT3,
                       GSTAT2,GSTAT1,GSTAT0,GLOCK_,IACK_,TDO,
                       CDIR);

  PinListSet (OUTPUTS_NO_X1, CLKOUTS,LABUS,LRW1_,LRW0_,LSTRB1_,   
                       LSTRB0_,LPAGE1,LPAGE0,LSTAT3,LSTAT2,    
                       LSTAT1,LSTAT0,LLOCK_,GABUS,GRW1_,GRW0_,
                       GSTRB1_,GSTRB0_,GPAGE1,GPAGE0,GSTAT3,
                       GSTAT2,GSTAT1,GSTAT0,GLOCK_,IACK_,TDO,
                       CDIR);

  PinListSet (IOPINS, LDBUS,GDBUS,IIOF3,IIOF2,IIOF1,IIOF0,     
                      TIMERS,EMU,COMPORT1,COMPORT2,
                      COMPORT4,COMPORT5);

  PinListSet (IOPINS_NO_LDBUS_CSTRBCRDY, GDBUS,IIOF3,IIOF2,IIOF1,IIOF0,
  
                      TIMERS,EMU,CREQ_,CACK_,CD);

  PinListSet (IOPINS_NO_CSTRBCRDY, LDBUS,GDBUS,IIOF3,IIOF2,    
                      IIOF1,IIOF0,TIMERS,EMU, 
                      CREQ_,CACK_,CD);


 
 
 

 
 
 
 
 

case TITestType of 

Pre_Burnin, Final, QA :
  begin 


  PinListSet (EVENPINS, GA3,GA1,GD30,GD28,GD26,GD25,GD23,GD21,GD19,GD17,GD13,GD12,GD11,
                        GD9,GD7,GD5,GD4,GD2,GD0,C4D7,GRDY1_,C4D4,C4D3,C4D2,C4D1,TCK,CSTRB4_,
                        TMS,TDO,TDI,EMU1,GPAGE1,GRW1_,GSTAT0,GSTAT1,GSTAT2,GPAGE0,GSTRB0_,RESETLOC1,
                        RESET_,CSTRB5_,CACK5_,C5D7,C5D5,C5D3,C2D7,C2D5,C2D3,C2D0,
                        CSTRB2_,CREQ2_,CDIR2,CDIR4,CSTRB1_,ROMEN,IIOF0,CRDY1_,IIOF3,
                        LRW0_,LRDY0_,LSTRB1_,LPAGE1,LCE1_,TCLK0,C1D7,LLOCK_,C1D5,C1D4,C1D3,C1D2,
                        IACK_,H3,H1,X1,LA23,LA21,LA18,LA16,LA14,
                        LA12,LA9,LA7,LA5,LA2,LA0,LD30,LD28,LD26,LD25,LD23,
                        LD21,LD18,LD16,LD15,LD14,LD12,LD10,LD8,LD6,LD5,LD3,LD1,
                        GA23,GA21,GA19,GA17,GA15,GA13,GA11,GA10,GA8,GA6,GA4);

  PinListSet (ODDPINS,  GA2,GA0,GD31,GD29,GD27,GD24,GD22,GD20,GD18,GD16,GD15,GD14,GD10,
                        GD8,GD6,GD3,GD1,GCE1_,C4D6,C4D5,GLOCK_,GCE0_,GRDY0_,GDE_,C4D0,CRDY4_,
                        TRS,EMU0,CACK4_,CREQ4_,GSTRB1_,GSTAT3,GRW0_,GAE_,
                        RESETLOC0,CRDY5_,CREQ5_,
                        C5D6,C5D4,C5D2,C5D1,C5D0,C2D6,C2D4,C2D2,C2D1,CRDY2_,CACK2_,
                        CDIR1,CDIR5,CACK1_,CREQ1_,IIOF1,IIOF2,NMI_,LSTRB0_,
                        LPAGE0,LCE0_,LRW1_,LRDY1_,LDE_,TCLK1,LAE_,C1D6,LSTAT0,LSTAT1,
                        LSTAT2,LSTAT3,C1D1,C1D0,LA22,LA20,LA19,LA17,LA15,
                        LA13,LA11,LA10,LA8,LA6,LA4,LA3,LA1,LD31,LD29,LD27,LD24,LD22,
                        LD20,LD19,LD17,LD13,LD11,LD9,LD7,LD4,LD2,LD0,    
                        GA22,GA20,GA18,GA16,GA14,GA12,GA9,GA7,GA5,X2CLKIN);


  PinListSet (ALLPINS,  EVENPINS,ODDPINS);           


 
 
 
 
 

  PinListSet (EVENINS, GRDY1_,      
                       RESETLOC1,RESET_,ROMEN,
                       LRDY0_,LCE1_);

  PinListSet (ODDINS,  GRDY0_,GCE0_,GCE1_,GDE_,NMI_,                  
                       GAE_,RESETLOC0,LDE_,LAE_,LCE0_,
                       LRDY1_);

  PinListSet (PMUINS,  TCK,TDI,TMS);                 
                                                     

  PinListSet (TESTINS, EVENINS,ODDINS,X2CLKIN);      

  PinListSet (NOTESTINS, PMUINS,TRS);                
                                                     
                                                     

  PinListSet (ALLOUTS, OUTPUTS);                     
                                                     

  PinListSet (ALLIOS, IOPINS);                       
                                                     
                                                     


 
 
 
 
 


  PinListSet (EVENTRISTATE, GA3,GA1,GD30,GD28,GD26,GD25,GD23,GD21,GD19,GD17,GD13,GD12,GD11,
                            GD9,GD7,GD5,GD4,GD2,GD0,C4D7,C4D4,C4D3,C4D2,C4D1,CSTRB4_,
                            GPAGE1,GRW1_,GPAGE0,GSTRB0_,
                            CSTRB5_,CACK5_,C5D7,C5D5,C5D3,C2D7,C2D5,C2D3,C2D0,
                            CSTRB2_,CREQ2_,CSTRB1_,IIOF0,CRDY1_,IIOF3,
                            LRW0_,LSTRB1_,LPAGE1,TCLK0,C1D7,C1D5,C1D4,C1D3,C1D2,
                            LA23,LA21,LA18,LA16,LA14,
                            LA12,LA9,LA7,LA5,LA2,LA0,LD30,LD28,LD26,LD25,LD23,
                            LD21,LD18,LD16,LD15,LD14,LD12,LD10,LD8,LD6,LD5,LD3,LD1,
                            GA23,GA21,GA19,GA17,GA15,GA13,GA11,GA10,GA8,GA6,GA4);

  PinListSet (ODDTRISTATE,  GA2,GA0,GD31,GD29,GD27,GD24,GD22,GD20,GD18,GD16,GD15,GD14,GD10,
                            GD8,GD6,GD3,GD1,C4D6,C4D5,C4D0,CRDY4_,
                            CACK4_,CREQ4_,GSTRB1_,GRW0_,CRDY5_,CREQ5_,
                            C5D6,C5D4,C5D2,C5D1,C5D0,C2D6,C2D4,C2D2,C2D1,CRDY2_,CACK2_,
                            CACK1_,CREQ1_,IIOF1,IIOF2,LSTRB0_,
                            LPAGE0,LRW1_,TCLK1,C1D6,
                            C1D1,C1D0,LA22,LA20,LA19,LA17,LA15,
                            LA13,LA11,LA10,LA8,LA6,LA4,LA3,LA1,LD31,LD29,LD27,LD24,LD22,
                            LD20,LD19,LD17,LD13,LD11,LD9,LD7,LD4,LD2,LD0,    
                            GA22,GA20,GA18,GA16,GA14,GA12,GA9,GA7,GA5);


  PinListSet (ALLTRISTATE,  EVENTRISTATE,ODDTRISTATE);  


  PinListSet (NOTRISTATEOUTS, X1,CLKOUTS,CDIR,     
                              LSTAT3,LSTAT2,LSTAT1,LSTAT0,LLOCK_,
                              GSTAT3,GSTAT2,GSTAT1,GSTAT0,GLOCK_,IACK_,TDO);

  PinListSet (NOTRISTATEIOS,  EMU);                

 end;  
 
writeln(execFile,'PROCEND:DeviceTableSet');
end;  
 
 
 
 
 

  PinListSet (MUXPINS, X2CLKIN);

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
  PinListSetNull(CDIR1);

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
  PinListSetNull(CDIR2);

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
  PinListSetNull(CDIR4);

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
  PinListSetNull(CDIR5);

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
  PinListSetNull(COMPORT1);
  PinListSetNull(COMPORT2);
  PinListSetNull(COMPORT4);
  PinListSetNull(COMPORT5);
  PinListSetNull(CDIR);
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
  PinListSetNull(OUTPUTS_NO_X1);
  PinListSetNull(IOPINS);
  PinListSetNull(IOPINS_NO_LDBUS_CSTRBCRDY);
  PinListSetNull(IOPINS_NO_CSTRBCRDY);
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

