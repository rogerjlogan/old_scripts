(* sccsidgctmain:= '@(#) gctmain.gct 1.1 9/28/89 11:57:15 c TI';  *)
(***********************************************************************)
(*                        SCCS    INFO                                 *)
(*                                                                     *)
(*        MODULE          : gctmain.gct                                *)
(*        VERSION NO.     : 1.1                                        *)
(*        FILE CREATED    : 9/28/89 11:57:15                           *)
(*        PREVIOUS DELTA  : 9/28/89 11:42:23                           *)
(*        SCCS FILE       : /s/knester/brahma/new/source/SCCS/s.gctmain.gct *)
(*        copyright         Texas Instruments, Inc.                    *)
(*                                                                     *)
(***********************************************************************)

(***********************************************************************)
(***								     ***)
(***			 TMS320C31 TEST PROGRAM 		     ***)
(***			 ---------------------- 		     ***)
(***								     ***)
(***	 File Name:  gctmain.gct 				     ***)
(***	 Origin: 320C30          				     ***)
(***     Current Revision: 00                                        ***)
(***								     ***)
(***	    Revision History:					     ***)
(***								     ***)
(***	    00 DM 09/17/90  Program generation. 		     ***)
(***                                                                 ***)
(***    rev 320C31B7                                                 ***)
(***    960603 K.Delling                                             ***)
(***    - Changed Drive Wave on C1 from TESTdriveWF to TEST1driveWF. ***)
(***    960604 K.Delling                                             ***)
(***    - Changed Drive Wave on SCANIN from TESTdriveWF to           ***)
(***      SCANINdriveWF.                                             ***)
(***********************************************************************)

    (*				SERPORT DRDSP1 CYCLE			    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDSP1Cycle,   DUMPclkWF,	CLKINdriveWF,	   X2CLKIN );
     CycleSetMD(DRDSP1Cycle,   H1strobeWF,	ALLoffWF,	   H1	   );
     CycleSetMD(DRDSP1Cycle,   H3strobeWF,	ALLoffWF,	   H3	   );
     CycleSetMD(DRDSP1Cycle,   STRB_strobeWF,	ALLoffWF,	   STRB_   );
     CycleSetMD(DRDSP1Cycle,   DBUSstrobeWF,	DBUSdriveWF,	   DBUS    );
     CycleSetMD(DRDSP1Cycle,   ABUSstrobeWF,	ABUSstrobeWF,	   ABUS    );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	RDY_driveWF,	   RDY_    );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	RESET_driveWF,	   RESET_  );
     CycleSetMD(DRDSP1Cycle,   XFstrobeWF,	XFdriveWF,	   XF0	   );
     CycleSetMD(DRDSP1Cycle,   XFstrobeWF,	XFdriveWF,	   XF1	   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	INT_driveWF,	   EXTINT  );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	ContinueWF,	   DR0	   );
     CycleSetMD(DRDSP1Cycle,   EXDXstrobe1WF,	ContinueWF,	   DX0	   );
     CycleSetMD(DRDSP1Cycle,   ContinueWF,	ContinueWF,	   FSR0    );
     CycleSetMD(DRDSP1Cycle,   ContinueWF,	EXFSXdrive1WF,	   FSX0    );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	EXSPCLKRdrive1WF,   CLKR0   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	EXSPCLKXdrive1WF,   CLKX0   );
     CycleSetMD(DRDSP1Cycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP1Cycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP1Cycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP1Cycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	SCANINdriveWF,	  SCANIN  );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	TESTdriveWF,	   C0	   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	TEST1driveWF,	   C1	   );
     CycleSetMD(DRDSP1Cycle,   TESTstrobeWF,	ALLoffWF,	   SCANOUT );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*				SERPORT DRDSP1 CYCLE			    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDSP1ACycle,   DUMPclkWF,	CLKINdriveWF,	   X2CLKIN );
     CycleSetMD(DRDSP1ACycle,   H1strobeWF,	ALLoffWF,	   H1	   );
     CycleSetMD(DRDSP1ACycle,   H3strobeWF,	ALLoffWF,	   H3	   );
     CycleSetMD(DRDSP1ACycle,   STRB_strobeWF,	ALLoffWF,	   STRB_   );
     CycleSetMD(DRDSP1ACycle,   DBUSstrobeWF,	DBUSdriveWF,	   DBUS    );
     CycleSetMD(DRDSP1ACycle,   ABUSstrobeWF,	ABUSstrobeWF,	   ABUS    );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	RDY_driveWF,	   RDY_    );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	RESET_driveWF,	   RESET_  );
     CycleSetMD(DRDSP1ACycle,   XFstrobeWF,	XFdriveWF,	   XF0	   );
     CycleSetMD(DRDSP1ACycle,   XFstrobeWF,	XFdriveWF,	   XF1	   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	INT_driveWF,	   EXTINT  );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	ContinueWF,	   DR0	   );
     CycleSetMD(DRDSP1ACycle,   EXDXAstrobe1WF,	ContinueWF,	   DX0	   );
     CycleSetMD(DRDSP1ACycle,   ContinueWF,	ContinueWF,	   FSR0    );
     CycleSetMD(DRDSP1ACycle,   ContinueWF,	EXFSXdrive1WF,	   FSX0    );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	EXSPCLKRdrive1WF,   CLKR0   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	EXSPCLKXdrive1WF,   CLKX0   );
     CycleSetMD(DRDSP1ACycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP1ACycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP1ACycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP1ACycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	SCANINdriveWF,	  SCANIN  );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	TESTdriveWF,	   C0	   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	TEST1driveWF,	   C1	   );
     CycleSetMD(DRDSP1ACycle,   TESTstrobeWF,	ALLoffWF,	   SCANOUT );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*				SERPORT DRDSP1 CYCLE			    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDSP1AaCycle,   DUMPclkWF,	CLKINdriveWF,	   X2CLKIN );
     CycleSetMD(DRDSP1AaCycle,   H1strobeWF,	ALLoffWF,	   H1	   );
     CycleSetMD(DRDSP1AaCycle,   H3strobeWF,	ALLoffWF,	   H3	   );
     CycleSetMD(DRDSP1AaCycle,   STRB_strobeWF,	ALLoffWF,	   STRB_   );
     CycleSetMD(DRDSP1AaCycle,   DBUSstrobeWF,	DBUSdriveWF,	   DBUS    );
     CycleSetMD(DRDSP1AaCycle,   ABUSstrobeWF,	ABUSstrobeWF,	   ABUS    );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	RDY_driveWF,	   RDY_    );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	RESET_driveWF,	   RESET_  );
     CycleSetMD(DRDSP1AaCycle,   XFstrobeWF,	XFdriveWF,	   XF0	   );
     CycleSetMD(DRDSP1AaCycle,   XFstrobeWF,	XFdriveWF,	   XF1	   );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	INT_driveWF,	   EXTINT  );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	ContinueWF,	   DR0	   );
     CycleSetMD(DRDSP1AaCycle,   EXDXAastrobe1WF,ContinueWF,	   DX0	   );
     CycleSetMD(DRDSP1AaCycle,   ContinueWF,	ContinueWF,	   FSR0    );
     CycleSetMD(DRDSP1AaCycle,   ContinueWF,	EXFSXadrive1WF,	   FSX0    );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	EXSPCLKRdrive1WF,   CLKR0   );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	EXSPCLKXdrive1WF,   CLKX0   );
     CycleSetMD(DRDSP1AaCycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP1AaCycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP1AaCycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP1AaCycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	SCANINdriveWF,	  SCANIN  );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	TESTdriveWF,	   C0	   );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,	TEST1driveWF,	   C1	   );
     CycleSetMD(DRDSP1AaCycle,   TESTstrobeWF,	ALLoffWF,	   SCANOUT );
     CycleSetMD(DRDSP1AaCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				 DW1SP1 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW1SP1Cycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(DW1SP1Cycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(DW1SP1Cycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(DW1SP1Cycle,	  DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DW1SP1Cycle,	  ContinueWF,	   ABUSstrobeWF,      ABUS    );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(DW1SP1Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(DW1SP1Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   ContinueWF,	      DR0     );
     CycleSetMD(DW1SP1Cycle,	  EXDXstrobe1WF,   ContinueWF,	      DX0     );
     CycleSetMD(DW1SP1Cycle,	  ContinueWF,	   ContinueWF,	      FSR0    );
     CycleSetMD(DW1SP1Cycle,	  ContinueWF,	   EXFSXdrive1WF,     FSX0    );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   EXSPCLKRdrive1WF,   CLKR0   );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   EXSPCLKXdrive1WF,   CLKX0   );
     CycleSetMD(DW1SP1Cycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW1SP1Cycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(DW1SP1Cycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(DW1SP1Cycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(DW1SP1Cycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(DW1SP1Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*			DW2SP1 CYCLE   SECOND WRITE CYCLE		    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2SP1Cycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(DW2SP1Cycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(DW2SP1Cycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(DW2SP1Cycle,	  DBUSendstrobeWF, ContinueWF,	      DBUS    );
     CycleSetMD(DW2SP1Cycle,	  ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(DW2SP1Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(DW2SP1Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   ContinueWF,	      DR0     );
     CycleSetMD(DW2SP1Cycle,	  EXDXstrobe1WF,   ContinueWF,	      DX0     );
     CycleSetMD(DW2SP1Cycle,	  ContinueWF,	   ContinueWF,	      FSR0    );
     CycleSetMD(DW2SP1Cycle,	  ContinueWF,	   EXFSXdrive1WF,     FSX0    );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   EXSPCLKRdrive1WF,   CLKR0   );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   EXSPCLKXdrive1WF,   CLKX0   );
     CycleSetMD(DW2SP1Cycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2SP1Cycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(DW2SP1Cycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(DW2SP1Cycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(DW2SP1Cycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(DW2SP1Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				 DWRSP1 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWRSP1Cycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWRSP1Cycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWRSP1Cycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWRSP1Cycle,	 ContinueWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWRSP1Cycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWRSP1Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWRSP1Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  ContinueWF,	     DR0     );
     CycleSetMD(DWRSP1Cycle,	 EXDXstrobe1WF,   ContinueWF,	     DX0     );
     CycleSetMD(DWRSP1Cycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWRSP1Cycle,	 ContinueWF,	  EXFSXdrive1WF,     FSX0    );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  EXSPCLKRdrive1WF,   CLKR0   );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  EXSPCLKXdrive1WF,   CLKX0   );
     CycleSetMD(DWRSP1Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRSP1Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWRSP1Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWRSP1Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWRSP1Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWRSP1Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				DWWSP1 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWWSP1Cycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWWSP1Cycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWWSP1Cycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWWSP1Cycle,	 DBUSstrobeWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWWSP1Cycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWWSP1Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWWSP1Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  ContinueWF,	     DR0     );
     CycleSetMD(DWWSP1Cycle,	 EXDXstrobe1WF,   ContinueWF,	     DX0     );
     CycleSetMD(DWWSP1Cycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWWSP1Cycle,	 ContinueWF,	  EXFSXdrive1WF,     FSX0    );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  EXSPCLKRdrive1WF,   CLKR0   );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  EXSPCLKXdrive1WF,   CLKX0   );
     CycleSetMD(DWWSP1Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP1Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP1Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP1Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWWSP1Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWWSP1Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				DWWSP1A CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWWSP1ACycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWWSP1ACycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWWSP1ACycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWWSP1ACycle,	 DBUSstrobeWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWWSP1ACycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWWSP1ACycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWWSP1ACycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  ContinueWF,	     DR0     );
     CycleSetMD(DWWSP1ACycle,	 EXDXAstrobe1WF,   ContinueWF,	     DX0     );
     CycleSetMD(DWWSP1ACycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWWSP1ACycle,	 ContinueWF,	  EXFSXdrive1WF,     FSX0    );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  EXSPCLKRdrive1WF,   CLKR0   );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  EXSPCLKXdrive1WF,   CLKX0   );
     CycleSetMD(DWWSP1ACycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP1ACycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP1ACycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP1ACycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWWSP1ACycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWWSP1ACycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWWSP1ACycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				DWWSP1Aa CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWWSP1AaCycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWWSP1AaCycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWWSP1AaCycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWWSP1AaCycle,	 DBUSstrobeWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWWSP1AaCycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWWSP1AaCycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWWSP1AaCycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  ContinueWF,	     DR0     );
     CycleSetMD(DWWSP1AaCycle,	 EXDXAastrobe1WF,   ContinueWF,	     DX0     );
     CycleSetMD(DWWSP1AaCycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWWSP1AaCycle,	 ContinueWF,	  EXFSXadrive1WF,     FSX0    );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  EXSPCLKRdrive1WF,   CLKR0   );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  EXSPCLKXdrive1WF,   CLKX0   );
     CycleSetMD(DWWSP1AaCycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP1AaCycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP1AaCycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP1AaCycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  SCANINdriveWF,	     SCANIN  );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWWSP1AaCycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWWSP1AaCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				SERPORT DRDSP2 CYCLE			    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDSP2Cycle,   DUMPclkWF,	CLKINdriveWF,	   X2CLKIN );
     CycleSetMD(DRDSP2Cycle,   H1strobeWF,	ALLoffWF,	   H1	   );
     CycleSetMD(DRDSP2Cycle,   H3strobeWF,	ALLoffWF,	   H3	   );
     CycleSetMD(DRDSP2Cycle,   STRB_strobeWF,	ALLoffWF,	   STRB_   );
     CycleSetMD(DRDSP2Cycle,   DBUSstrobeWF,	DBUSdriveWF,	   DBUS    );
     CycleSetMD(DRDSP2Cycle,   ABUSstrobeWF,	ABUSstrobeWF,	   ABUS    );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	RDY_driveWF,	   RDY_    );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	RESET_driveWF,	   RESET_  );
     CycleSetMD(DRDSP2Cycle,   XFstrobeWF,	XFdriveWF,	   XF0	   );
     CycleSetMD(DRDSP2Cycle,   XFstrobeWF,	XFdriveWF,	   XF1	   );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	INT_driveWF,	   EXTINT  );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	EXDRdrive2WF,	   DR0	   );
     CycleSetMD(DRDSP2Cycle,   ContinueWF,	ContinueWF,	   DX0	   );
     CycleSetMD(DRDSP2Cycle,   EXFSRVdrive2WF,	EXFSRFdrive2WF,    FSR0    );
     CycleSetMD(DRDSP2Cycle,   ContinueWF,	EXFSXdrive2WF,	   FSX0    );
     CycleSetMD(DRDSP2Cycle,   ContinueWF,	EXSPCLKRdrive2WF,   CLKR0   );
     CycleSetMD(DRDSP2Cycle,   ContinueWF,	EXSPCLKXdrive2WF,   CLKX0   );
     CycleSetMD(DRDSP2Cycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP2Cycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP2Cycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP2Cycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	SCANINdriveWF,	  SCANIN  );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	TESTdriveWF,	   C0	   );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	TEST1driveWF,	   C1	   );
     CycleSetMD(DRDSP2Cycle,   TESTstrobeWF,	ALLoffWF,	   SCANOUT );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				 DW1SP2 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW1SP2Cycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(DW1SP2Cycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(DW1SP2Cycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(DW1SP2Cycle,	  DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,	   ABUSstrobeWF,      ABUS    );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(DW1SP2Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(DW1SP2Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   EXDRdrive2WF,      DR0     );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,	   ContinueWF,	      DX0     );
     CycleSetMD(DW1SP2Cycle,	  EXFSRVdrive2WF,  EXFSRFdrive2WF,    FSR0    );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,	   EXFSXdrive2WF,     FSX0    );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,	   EXSPCLKRdrive2WF,   CLKR0   );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,	   EXSPCLKXdrive2WF,   CLKX0   );
     CycleSetMD(DW1SP2Cycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW1SP2Cycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(DW1SP2Cycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(DW1SP2Cycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(DW1SP2Cycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(DW1SP2Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*			DW2SP2 CYCLE   SECOND WRITE CYCLE		    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2SP2Cycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(DW2SP2Cycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(DW2SP2Cycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(DW2SP2Cycle,	  DBUSendstrobeWF, ContinueWF,	      DBUS    );
     CycleSetMD(DW2SP2Cycle,	  ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(DW2SP2Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(DW2SP2Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   EXDRdrive2WF,      DR0     );
     CycleSetMD(DW2SP2Cycle,	  ContinueWF,	   ContinueWF,	      DX0     );
     CycleSetMD(DW2SP2Cycle,	  EXFSRVdrive2WF,  EXFSRFdrive2WF,    FSR0    );
     CycleSetMD(DW2SP2Cycle,	  ContinueWF,	   EXFSXdrive2WF,     FSX0    );
     CycleSetMD(DW2SP2Cycle,	  ContinueWF,	   EXSPCLKRdrive2WF,   CLKR0   );
     CycleSetMD(DW2SP2Cycle,	  ContinueWF,	   EXSPCLKXdrive2WF,   CLKX0   );
     CycleSetMD(DW2SP2Cycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2SP2Cycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(DW2SP2Cycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(DW2SP2Cycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(DW2SP2Cycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(DW2SP2Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				 DWRSP2 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWRSP2Cycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWRSP2Cycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWRSP2Cycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWRSP2Cycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWRSP2Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWRSP2Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  EXDRdrive2WF,      DR0     );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,	  ContinueWF,	     DX0     );
     CycleSetMD(DWRSP2Cycle,	 EXFSRVdrive2WF,  EXFSRFdrive2WF,    FSR0    );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,	  EXFSXdrive2WF,     FSX0    );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,	  EXSPCLKRdrive2WF,   CLKR0   );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,	  EXSPCLKXdrive2WF,   CLKX0   );
     CycleSetMD(DWRSP2Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRSP2Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWRSP2Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWRSP2Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  SCANINdriveWF,	     SCANIN  );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWRSP2Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWRSP2Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				DWWSP2 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWWSP2Cycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWWSP2Cycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWWSP2Cycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWWSP2Cycle,	 DBUSstrobeWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWWSP2Cycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWWSP2Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWWSP2Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  EXDRdrive2WF,      DR0     );
     CycleSetMD(DWWSP2Cycle,	 ContinueWF,	  ContinueWF,	     DX0     );
     CycleSetMD(DWWSP2Cycle,	 EXFSRVdrive2WF,  EXFSRFdrive2WF,    FSR0    );
     CycleSetMD(DWWSP2Cycle,	 ContinueWF,	  EXFSXdrive2WF,     FSX0    );
     CycleSetMD(DWWSP2Cycle,	 ContinueWF,	  EXSPCLKRdrive2WF,   CLKR0   );
     CycleSetMD(DWWSP2Cycle,	 ContinueWF,	  EXSPCLKXdrive2WF,   CLKX0   );
     CycleSetMD(DWWSP2Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP2Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP2Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP2Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  SCANINdriveWF,	     SCANIN  );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWWSP2Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWWSP2Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				SERPORT DRDSP4 CYCLE			    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDSP4Cycle,   DUMPclkWF,	CLKINdriveWF,	   X2CLKIN );
     CycleSetMD(DRDSP4Cycle,   H1strobeWF,	ALLoffWF,	   H1	   );
     CycleSetMD(DRDSP4Cycle,   H3strobeWF,	ALLoffWF,	   H3	   );
     CycleSetMD(DRDSP4Cycle,   STRB_strobeWF,	ALLoffWF,	   STRB_   );
     CycleSetMD(DRDSP4Cycle,   DBUSstrobeWF,	DBUSdriveWF,	   DBUS    );
     CycleSetMD(DRDSP4Cycle,   ABUSstrobeWF,	ABUSstrobeWF,	   ABUS    );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	RDY_driveWF,	   RDY_    );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	RESET_driveWF,	   RESET_  );
     CycleSetMD(DRDSP4Cycle,   XFstrobeWF,	XFdriveWF,	   XF0	   );
     CycleSetMD(DRDSP4Cycle,   XFstrobeWF,	XFdriveWF,	   XF1	   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	INT_driveWF,	   EXTINT  );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	ContinueWF,	   DR0	   );
     CycleSetMD(DRDSP4Cycle,   EXDXstrobe4WF,	ContinueWF,	   DX0	   );
     CycleSetMD(DRDSP4Cycle,   ContinueWF,	ContinueWF,	   FSR0    );
     CycleSetMD(DRDSP4Cycle,   ContinueWF,	ContinueWF,	   FSX0    );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	EXSPCLKRdrive4WF,   CLKR0   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	EXSPCLKXdrive4WF,   CLKX0   );
     CycleSetMD(DRDSP4Cycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP4Cycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP4Cycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP4Cycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	SCANINdriveWF,	  SCANIN  );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	TESTdriveWF,	   C0	   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	TEST1driveWF,	   C1	   );
     CycleSetMD(DRDSP4Cycle,   TESTstrobeWF,	ALLoffWF,	   SCANOUT );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				 DW1SP4 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW1SP4Cycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(DW1SP4Cycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(DW1SP4Cycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(DW1SP4Cycle,	  DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DW1SP4Cycle,	  ContinueWF,	   ABUSstrobeWF,      ABUS    );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(DW1SP4Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(DW1SP4Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   ContinueWF,	      DR0     );
     CycleSetMD(DW1SP4Cycle,	  EXDXstrobe4WF,   ContinueWF,	      DX0     );
     CycleSetMD(DW1SP4Cycle,	  ContinueWF,	   ContinueWF,	      FSR0    );
     CycleSetMD(DW1SP4Cycle,	  ContinueWF,	   ContinueWF,	      FSX0    );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   EXSPCLKRdrive4WF,   CLKR0   );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   EXSPCLKXdrive4WF,   CLKX0   );
     CycleSetMD(DW1SP4Cycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW1SP4Cycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(DW1SP4Cycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(DW1SP4Cycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(DW1SP4Cycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(DW1SP4Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*			DW2SP4 CYCLE   SECOND WRITE CYCLE		    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2SP4Cycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(DW2SP4Cycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(DW2SP4Cycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(DW2SP4Cycle,	  DBUSendstrobeWF, ContinueWF,	      DBUS    );
     CycleSetMD(DW2SP4Cycle,	  ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(DW2SP4Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(DW2SP4Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   ContinueWF,	      DR0     );
     CycleSetMD(DW2SP4Cycle,	  EXDXstrobe4WF,   ContinueWF,	      DX0     );
     CycleSetMD(DW2SP4Cycle,	  ContinueWF,	   ContinueWF,	      FSR0    );
     CycleSetMD(DW2SP4Cycle,	  ContinueWF,	   ContinueWF,	      FSX0    );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   EXSPCLKRdrive4WF,   CLKR0   );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   EXSPCLKXdrive4WF,   CLKX0   );
     CycleSetMD(DW2SP4Cycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2SP4Cycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(DW2SP4Cycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(DW2SP4Cycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(DW2SP4Cycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(DW2SP4Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*			TDDXZ CYCLE   SECOND WRITE CYCLE		    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(TDDXZCycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(TDDXZCycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(TDDXZCycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(TDDXZCycle,	  DBUSendstrobeWF, ContinueWF,	      DBUS    );
     CycleSetMD(TDDXZCycle,	  ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(TDDXZCycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(TDDXZCycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   ContinueWF,	      DR0     );
     CycleSetMD(TDDXZCycle,	  TDDXZstrobeWF,   TDDXZstrobeWF,     DX0     );
     CycleSetMD(TDDXZCycle,	  ContinueWF,	   ContinueWF,	      FSR0    );
     CycleSetMD(TDDXZCycle,	  ContinueWF,	   ContinueWF,	      FSX0    );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   EXSPCLKRdrive4WF,   CLKR0   );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   EXSPCLKXdrive4WF,   CLKX0   );
     CycleSetMD(TDDXZCycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(TDDXZCycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(TDDXZCycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(TDDXZCycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(TDDXZCycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(TDDXZCycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(TDDXZCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				 DWRSP4 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWRSP4Cycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWRSP4Cycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWRSP4Cycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWRSP4Cycle,	 ContinueWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWRSP4Cycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWRSP4Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWRSP4Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  ContinueWF,	     DR0     );
     CycleSetMD(DWRSP4Cycle,	 EXDXstrobe4WF,   ContinueWF,	     DX0     );
     CycleSetMD(DWRSP4Cycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWRSP4Cycle,	 ContinueWF,	  ContinueWF,	     FSX0    );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  EXSPCLKRdrive4WF,   CLKR0   );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  EXSPCLKXdrive4WF,   CLKX0   );
     CycleSetMD(DWRSP4Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRSP4Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWRSP4Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWRSP4Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  SCANINdriveWF,	     SCANIN  );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWRSP4Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWRSP4Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				DWWSP4 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWWSP4Cycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWWSP4Cycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWWSP4Cycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWWSP4Cycle,	 DBUSstrobeWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWWSP4Cycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWWSP4Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWWSP4Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  ContinueWF,	     DR0     );
     CycleSetMD(DWWSP4Cycle,	 EXDXstrobe4WF,   ContinueWF,	     DX0     );
     CycleSetMD(DWWSP4Cycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWWSP4Cycle,	 ContinueWF,	  ContinueWF,	     FSX0    );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  EXSPCLKRdrive4WF,   CLKR0   );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  EXSPCLKXdrive4WF,   CLKX0   );
     CycleSetMD(DWWSP4Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP4Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP4Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP4Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  SCANINdriveWF,	     SCANIN  );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWWSP4Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWWSP4Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				SERPORT DRDSP5 CYCLE			    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DRDSP5Cycle,   DUMPclkWF,	CLKINdriveWF,	   X2CLKIN );
     CycleSetMD(DRDSP5Cycle,   H1strobeWF,	ALLoffWF,	   H1	   );
     CycleSetMD(DRDSP5Cycle,   H3strobeWF,	ALLoffWF,	   H3	   );
     CycleSetMD(DRDSP5Cycle,   STRB_strobeWF,	ALLoffWF,	   STRB_   );
     CycleSetMD(DRDSP5Cycle,   DBUSstrobeWF,	DBUSdriveWF,	   DBUS    );
     CycleSetMD(DRDSP5Cycle,   ABUSstrobeWF,	ABUSstrobeWF,	   ABUS    );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	RDY_driveWF,	   RDY_    );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	RESET_driveWF,	   RESET_  );
     CycleSetMD(DRDSP5Cycle,   XFstrobeWF,	XFdriveWF,	   XF0	   );
     CycleSetMD(DRDSP5Cycle,   XFstrobeWF,	XFdriveWF,	   XF1	   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	INT_driveWF,	   EXTINT  );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	EXDRdrive5WF,	   DR0	   );
     CycleSetMD(DRDSP5Cycle,   ContinueWF,	ContinueWF,	   DX0	   );
     CycleSetMD(DRDSP5Cycle,   ContinueWF,	ContinueWF,	   FSR0    );
     CycleSetMD(DRDSP5Cycle,   ContinueWF,	ContinueWF,	   FSX0    );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	EXSPCLKRdrive5WF,   CLKR0   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	EXSPCLKXdrive5WF,   CLKX0   );
     CycleSetMD(DRDSP5Cycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP5Cycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP5Cycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP5Cycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	SCANINdriveWF,	  SCANIN  );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	TESTdriveWF,	   C0	   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	TEST1driveWF,	   C1	   );
     CycleSetMD(DRDSP5Cycle,   TESTstrobeWF,	ALLoffWF,	   SCANOUT );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				 DW1SP5 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW1SP5Cycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(DW1SP5Cycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(DW1SP5Cycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(DW1SP5Cycle,	  DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DW1SP5Cycle,	  ContinueWF,	   ABUSstrobeWF,      ABUS    );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(DW1SP5Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(DW1SP5Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   EXDRdrive5WF,      DR0     );
     CycleSetMD(DW1SP5Cycle,	  ContinueWF,	   ContinueWF,	      DX0     );
     CycleSetMD(DW1SP5Cycle,	  ContinueWF,	   ContinueWF,	      FSR0    );
     CycleSetMD(DW1SP5Cycle,	  ContinueWF,	   ContinueWF,	      FSX0    );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   EXSPCLKRdrive5WF,   CLKR0   );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   EXSPCLKXdrive5WF,   CLKX0   );
     CycleSetMD(DW1SP5Cycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW1SP5Cycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(DW1SP5Cycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(DW1SP5Cycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(DW1SP5Cycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(DW1SP5Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*			DW2SP5 CYCLE   SECOND WRITE CYCLE		    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2SP5Cycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(DW2SP5Cycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(DW2SP5Cycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(DW2SP5Cycle,	  DBUSendstrobeWF, ContinueWF,	      DBUS    );
     CycleSetMD(DW2SP5Cycle,	  ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(DW2SP5Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(DW2SP5Cycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   EXDRdrive5WF,      DR0     );
     CycleSetMD(DW2SP5Cycle,	  ContinueWF,	   ContinueWF,	      DX0     );
     CycleSetMD(DW2SP5Cycle,	  ContinueWF,	   ContinueWF,	      FSR0    );
     CycleSetMD(DW2SP5Cycle,	  ContinueWF,	   ContinueWF,	      FSX0    );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   EXSPCLKRdrive5WF,   CLKR0   );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   EXSPCLKXdrive5WF,   CLKX0   );
     CycleSetMD(DW2SP5Cycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2SP5Cycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(DW2SP5Cycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(DW2SP5Cycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(DW2SP5Cycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(DW2SP5Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				 DWRSP5 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWRSP5Cycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWRSP5Cycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWRSP5Cycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWRSP5Cycle,	 ContinueWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWRSP5Cycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWRSP5Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWRSP5Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  EXDRdrive5WF,      DR0     );
     CycleSetMD(DWRSP5Cycle,	 ContinueWF,	  ContinueWF,	     DX0     );
     CycleSetMD(DWRSP5Cycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWRSP5Cycle,	 ContinueWF,	  ContinueWF,	     FSX0    );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  EXSPCLKRdrive5WF,   CLKR0   );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  EXSPCLKXdrive5WF,   CLKX0   );
     CycleSetMD(DWRSP5Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRSP5Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWRSP5Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWRSP5Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  SCANINdriveWF,	     SCANIN  );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWRSP5Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWRSP5Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				DWWSP5 CYCLE				    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWWSP5Cycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(DWWSP5Cycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(DWWSP5Cycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(DWWSP5Cycle,	 DBUSstrobeWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(DWWSP5Cycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(DWWSP5Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(DWWSP5Cycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  EXDRdrive5WF,      DR0     );
     CycleSetMD(DWWSP5Cycle,	 ContinueWF,	  ContinueWF,	     DX0     );
     CycleSetMD(DWWSP5Cycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWWSP5Cycle,	 ContinueWF,	  ContinueWF,	     FSX0    );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  EXSPCLKRdrive5WF,   CLKR0   );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  EXSPCLKXdrive5WF,   CLKX0   );
     CycleSetMD(DWWSP5Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP5Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP5Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP5Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  SCANINdriveWF,	     SCANIN  );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWWSP5Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWWSP5Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                          STANDARD DRDMRD CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDCycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDCycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDCycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DRDCycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDCycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDCycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDCycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDCycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DRDCycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDCycle,   ALLoffWF,        ALLoffWF,          X1      );
     CycleSetMD(DRDCycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DRDCycle,   DRGPIOstrobeWF,  DRGPIOdriveWF,     DR0     );
     CycleSetMD(DRDCycle,   DXGPIOstrobeWF,  DXGPIOdriveWF,     DX0     );
     CycleSetMD(DRDCycle,   FSRGPIOstrobeWF, FSRGPIOdriveWF,    FSR0    );
     CycleSetMD(DRDCycle,   FSXGPIOstrobeWF, FSXGPIOdriveWF,    FSX0    );
     CycleSetMD(DRDCycle,   CLKRGPIOstrobeWF,CLKRGPIOdriveWF,   CLKR0   );
     CycleSetMD(DRDCycle,   CLKXGPIOstrobeWF,CLKXGPIOdriveWF,   CLKX0   );
     CycleSetMD(DRDCycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDCycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDCycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDCycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
    (*									    *)
    (*                           DW1MRD CYCLE                               *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW1Cycle,      ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW1Cycle,      H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DW1Cycle,      H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DW1Cycle,      STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DW1Cycle,      DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DW1Cycle,      ContinueWF,      ABUSstrobeWF,      ABUS    );
     CycleSetMD(DW1Cycle,      ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DW1Cycle,      ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DW1Cycle,      XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DW1Cycle,      XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DW1Cycle,      ALLoffWF,        ALLoffWF,          X1      );
     CycleSetMD(DW1Cycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW1Cycle,   DRGPIOstrobeWF,  DRGPIOdriveWF,     DR0     );
     CycleSetMD(DW1Cycle,   DXGPIOstrobeWF,  DXGPIOdriveWF,     DX0     );
     CycleSetMD(DW1Cycle,   FSRGPIOstrobeWF, FSXGPIOdriveWF,    FSR0    );
     CycleSetMD(DW1Cycle,   FSXGPIOstrobeWF, FSXGPIOdriveWF,    FSX0    );
     CycleSetMD(DW1Cycle,   CLKRGPIOstrobeWF,CLKRGPIOdriveWF,   CLKR0   );
     CycleSetMD(DW1Cycle,   CLKXGPIOstrobeWF,CLKXGPIOdriveWF,   CLKX0   );
     CycleSetMD(DW1Cycle,      TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW1Cycle,      ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW1Cycle,      HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DW1Cycle,      ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DW1Cycle,      IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DW1Cycle,      RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DW1Cycle,      ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW1Cycle,      ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW1Cycle,      ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DW1Cycle,      ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DW1Cycle,      TESTstrobeWF,    ALLoffWF,          SCANOUT );
    (*									    *)
    (*                  DW2MRD CYCLE   SECOND WRITE CYCLE                   *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2Cycle,      ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2Cycle,      H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DW2Cycle,      H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DW2Cycle,      STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DW2Cycle,      DBUSendstrobeWF, ContinueWF,        DBUS    );
     CycleSetMD(DW2Cycle,      ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2Cycle,      ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DW2Cycle,      ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DW2Cycle,      XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DW2Cycle,      XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DW2Cycle,      ALLoffWF,        ALLoffWF,          X1      );
     CycleSetMD(DW2Cycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW2Cycle,   DRGPIOstrobeWF,  DRGPIOdriveWF,     DR0     );
     CycleSetMD(DW2Cycle,   DXGPIOstrobeWF,  DXGPIOdriveWF,     DX0     );
     CycleSetMD(DW2Cycle,   FSRGPIOstrobeWF, FSXGPIOdriveWF,    FSR0    );
     CycleSetMD(DW2Cycle,   FSXGPIOstrobeWF, FSXGPIOdriveWF,    FSX0    );
     CycleSetMD(DW2Cycle,   CLKRGPIOstrobeWF,CLKRGPIOdriveWF,   CLKR0   );
     CycleSetMD(DW2Cycle,   CLKXGPIOstrobeWF,CLKXGPIOdriveWF,   CLKX0   );
     CycleSetMD(DW2Cycle,      TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2Cycle,      ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2Cycle,      HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DW2Cycle,      ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DW2Cycle,      IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DW2Cycle,      RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DW2Cycle,      ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2Cycle,      ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2Cycle,      ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DW2Cycle,      ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DW2Cycle,      TESTstrobeWF,    ALLoffWF,          SCANOUT );
    (*									    *)
    (*                           DWRMRD CYCLE                               *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWRCycle,     ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWRCycle,     H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DWRCycle,     H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DWRCycle,     STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DWRCycle,     ContinueWF,      DBUSdriveWF,       DBUS    );
     CycleSetMD(DWRCycle,     ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWRCycle,     ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DWRCycle,     ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DWRCycle,     XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DWRCycle,     XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DWRCycle,     ALLoffWF,        ALLoffWF,          X1      );
     CycleSetMD(DWRCycle,     ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DWRCycle,   DRGPIOstrobeWF,  DRGPIOdriveWF,     DR0     );
     CycleSetMD(DWRCycle,   DXGPIOstrobeWF,  DXGPIOdriveWF,     DX0     );
     CycleSetMD(DWRCycle,   FSRGPIOstrobeWF, FSXGPIOdriveWF,    FSR0    );
     CycleSetMD(DWRCycle,   FSXGPIOstrobeWF, FSXGPIOdriveWF,    FSX0    );
     CycleSetMD(DWRCycle,   CLKRGPIOstrobeWF,CLKRGPIOdriveWF,   CLKR0   );
     CycleSetMD(DWRCycle,   CLKXGPIOstrobeWF,CLKXGPIOdriveWF,   CLKX0   );
     CycleSetMD(DWRCycle,     TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DWRCycle,     ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRCycle,     HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DWRCycle,     ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DWRCycle,     IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DWRCycle,     RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DWRCycle,     ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRCycle,     ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWRCycle,     ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DWRCycle,     ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DWRCycle,     TESTstrobeWF,    ALLoffWF,          SCANOUT );
    (*									    *)
    (*                          DWWMRDA CYCLE                                *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWWCycle,     ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWWCycle,     H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DWWCycle,     H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DWWCycle,     STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DWWCycle,     DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DWWCycle,     ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWWCycle,     ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DWWCycle,     ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DWWCycle,     XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DWWCycle,     XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DWWCycle,     ALLoffWF,        ALLoffWF,          X1      );
     CycleSetMD(DWWCycle,     ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DWWCycle,     DRGPIOstrobeWF,      DRGPIOdriveWF,         DR0     );
     CycleSetMD(DWWCycle,     DXGPIOstrobeWF,      DXGPIOdriveWF,         DX0     );
     CycleSetMD(DWWCycle,     FSRGPIOstrobeWF,     FSRGPIOdriveWF,        FSR0    );
     CycleSetMD(DWWCycle,     FSXGPIOstrobeWF,     FSXGPIOdriveWF,        FSX0    );
     CycleSetMD(DWWCycle,     CLKRGPIOstrobeWF,    CLKRGPIOdriveWF,       CLKR0   );
     CycleSetMD(DWWCycle,     CLKXGPIOstrobeWF,    CLKXGPIOdriveWF,       CLKX0   );
     CycleSetMD(DWWCycle,     TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DWWCycle,     ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWCycle,     HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DWWCycle,     ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DWWCycle,     IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DWWCycle,     RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DWWCycle,     ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWCycle,     ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWWCycle,     ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DWWCycle,     ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DWWCycle,     TESTstrobeWF,    ALLoffWF,          SCANOUT );
    (*									    *)
    (*                          ALLOFF DRD  CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(ALLOFFcycle,   DUMPclkWF,  CLKINdriveWF,   X2CLKIN );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,       ALLoffWF,   H1      );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,       ALLoffWF,   H3      );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,       ALLoffWF,   STRB_   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,    DBUSdriveWF,   DBUS    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,      ALLoffWF ,   ABUS    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,    RDY_driveWF,   RDY_    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,  RESET_driveWF,   RESET_  );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,      XFdriveWF,   XF0     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,      XFdriveWF,   XF1     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,    INT_driveWF,   EXTINT  );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,      DRdriveWF,   DR0     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,      DXdriveWF,   DX0     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,     FSRdriveWF,   FSR0    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,     FSXdriveWF,   FSX0    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,    CLKRdriveWF,   CLKR0   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,    CLKXdriveWF,   CLKX0   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,    TCLKdriveWF,   TPINS   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,   HOLD_driveWF,   HOLD_   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,       ALLoffWF,   HOLDA_  );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,     MCSdriveWF,   MCS     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,       ALLoffWF,   IACK_   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,       ALLoffWF,   RW_     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,   MCMP_driveWF,   MCMP_   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,  SCANINdriveWF,   SCANIN  );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,    TESTdriveWF,   C0      );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,   TEST1driveWF,   C1      );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,       ALLoffWF,   SCANOUT );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,       ALLoffWF,   X1      );
