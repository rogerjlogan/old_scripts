(* APS: This is a made up file since I didn't have the correct file *)

  ACTable        = (
     Dut50AC,
     Dut67AC,
     Dut83AC,
     Dut83AC_C16Off,
     Dut100AC,
     Dut200AC,
     OpensAC,
     EasyAC,
     DutLooseAC,
     TIsearchlooseACTable,
     TIsearchACTable,
     TIfunctionalACTable
      );         
      
  DeviceType     = (
   PX3F16D28PJQ, 
   PX3F16D28HEQ,
   PX3F16D28APJQ, 
   PX3F16D28AHEQ,
   PX3F16D28BPJQ, 
   PX3F16D28BHEQ,
   Z1F281FxxPJM,
   S4D27FxxPJQ, 
   S4D27FxxHEQ,
   S4D26CSFxxPJQ, 
   S4D26CSFxxHEQ,
   S4D27RFxxPJM,
   HS4D27FxxIN,
  HS4D27RFxxIN,
  HS4D26CSFxxIN,
  PJQPack (* APS: this probably falls into some other grouping!!! *)
                   );
                   
  TempType       = (
                    Temp_N40_Degrees_C,
                    Temp_0_Degrees_C,
                    Temp_25_Degrees_C,
                    Temp_125_Degrees_C     (* T=125c ambient spec QA  *)
                    );
                    
(* APS: the rest of these are imported from F240 *)


  SoftBin        = ( 
                     NoResult, 
                     OpensFail,                 (* Parametric fail counter*)
                     ShortsFail                                            
                   );

TestName      =(TIopensTest,
                TIshortsTest,
                TIPTUIOddLo1Test
                );

  VectorMap    = ( TIVMAP,  ScanInOrderVM, ScanOutOrderVM );    
            
  TITypeOfTest   = (Probe, Final, FT2, FT3, Q100_FT1, Q100_FT2, Q100_FT3, QA, Engineering );

  Cycle             =   ( 
                        GCT0____,
                        GCT1____,
                        GCT2____,
                        GCT3____
                        );

  HardBin        = (DummyBIN00,                 (* This one can't be used *)
                    BIN01, 
                    BIN02, BIN03, BIN04, (* DeltaFlex use will only*)
                    BIN05, BIN06, BIN07, BIN08, (* include 1-6, but 32 can*)
                    BIN09, BIN10, BIN11, BIN12, (* be used with some      *)
                    BIN13, BIN14, BIN15, BIN16, (* handlers mainly probers*)
                    BIN17, BIN18, BIN19, BIN20,
                    BIN21, BIN22, BIN23, BIN24,
                    BIN25, BIN26, BIN27, BIN28, 
                    BIN29, BIN30, BIN31);
 
  CycleTable     = ( TIP50CycleTable,TIP100CycleTable); 
