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
(***     rev 320C31A4                                                ***)
(***     920720 W.Fluke                                              ***)
(***     - Added GCT SyncDRDCycle to test twHHmin, trHmax, and tfHmax***)
(***        during sunc-up.                                          ***)
(***     - Added GCT SDRDCycle to use during sync-up.                ***)
(***                                                                 ***)
(***     rev 320C31A5                                                ***)
(***     930408 W.Fluke                                              ***)
(***     - Added GCT DWRXFCycle to test tdH3HXFIO.                   ***)
(***                                                                 ***)
(***     rev 320C31A9                                                ***)
(***     940602 W.Fluke                                              ***)
(***     - Added GCT DRDESCKCycle, DW1ESCKCycle, DW2ESCKCycle, and   ***)
(***       DWRESCKCycle for the case when CLKX is external.          ***)
(***     940605 W.Fluke                                              ***)
(***     - Added DRDStopCycle for the clock stop mode.               ***)
(***     940626 W.Fluke                                              ***)
(***     - Added IDDQCycle for IDDQ test.                            ***)
(***								     ***)
(***	 940712 J.Drake						     ***)
(***	 - Added DW2ACycle to compensate for locations where STRB_   ***)
(***	   falls on H1 rising edge instead of H1 falling edge        ***)
(***                                                                 ***)
(***     rev 320C31B2                                                ***)
(***     950113 J.Drake                                              ***)
(***     - Added all xxxSPxCycles for SERPORT7Patterns, as they need ***)
(***       the specCycleTable serial port timings.                   ***)
(***     950126 J.Drake                                              ***)
(***     - Added EXTDXdrive, EXTDX(A,Aa)strobe1, EXTDRdrive2,        ***)
(***       EXFSRdrive2, EXTDRdrive4, and EXTDXstrobe4 waveforms for  ***)
(***       new SERPORT7Patterns.                                     ***)
(***    950216 J.Drake                                               ***)
(***    - Removed EXTDRdrive4WF and added EXTDRdrive5WF for correct  ***)
(***      DR drive in the SERPORT7Patterns.                          ***)
(***    - Changed all EXSPCLKX/RdrivexWF's to SPCLKX/RdrivexWF's as  ***)
(***      the new SERPORT7 patterns start the clocks on the opposite ***)
(***      H1 edge as the old SERPORT7 patterns.                      ***)
(***    - Removed GCT's DWWSP1A and DRDSP1Aa as they are no longer   ***)
(***      needed for SERPORT7 patterns.                              ***)
(***    - Added GCT's DW2SP5Aa and TDDXZ to test and characterize    ***)
(***      tdDXZ, td(CH-DX)V, and tsuFSXECLKX max.                    ***)
(***    - Added EXFSRdrive1WF to test tsuFSRECLKRL in SERPORT7.      ***)
(***    950228 J.Drake                                               ***)
(***    - Modified DRDbCycle to use STRB_bstrobe and ABUSbstrobeWF's ***)
(***      for use in new ChrTime3 routine to find tdSL-AV.           ***)
(***                                                                 ***)
(***    rev 320C31B7                                                 ***)
(***    960603 K.Delling                                             ***)
(***    - Changed Drive Wave on C1 from TESTdriveWF to TEST1driveWF. ***)
(***    960604 K.Delling                                             ***)
(***    - Changed Drive Wave on SCANIN from TESTdriveWF to           ***)
(***      SCANINdriveWF.                                             ***)
(***                                                                 ***)
(***    rev 320C31C1                                                 ***)
(***    980512 K.Delling                                             ***)
(***    - Added IDLECycle for Idle2 test                             ***)
(***********************************************************************)

    (*									    *)
    (*                          ALLOFF DRD  CYCLE                           *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)


     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF,          H1      );


     CycleSetMD(ALLOFFcycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF,          H1      );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF,          H3      );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF,          STRB_   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        DBUSdriveWF,       DBUS    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF ,         ABUS    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        XFdriveWF,         XF0     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        XFdriveWF,         XF1     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        DRdriveWF,         DR0     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        DXdriveWF,         DX0     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        FSRdriveWF,        FSR0    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        FSXdriveWF,        FSX0    );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        CLKRdriveWF,       CLKR0   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        CLKXdriveWF,       CLKX0   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        TCLKdriveWF,       TPINS   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF,          HOLDA_  );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF,          IACK_   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF,          RW_     );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF,          SCANOUT );
     CycleSetMD(ALLOFFcycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*						                           *)
    (*                   IDDQ CYCLE (Modified DRD  CYCLE)                   *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(IDDQCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(IDDQCycle,   H1strobeWF,      MCSdriveWF,        H1      );
     CycleSetMD(IDDQCycle,   H3strobeWF,      MCSdriveWF,        H3      );
     CycleSetMD(IDDQCycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(IDDQCycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(IDDQCycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(IDDQCycle,   ALLoffWF,        RDY_driveNRWF,     RDY_    );
     CycleSetMD(IDDQCycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(IDDQCycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(IDDQCycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(IDDQCycle,   INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(IDDQCycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(IDDQCycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(IDDQCycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(IDDQCycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(IDDQCycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(IDDQCycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(IDDQCycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(IDDQCycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(IDDQCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(IDDQCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(IDDQCycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(IDDQCycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(IDDQCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(IDDQCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(IDDQCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(IDDQCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(IDDQCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(IDDQCycle,   ALLoffWF,        ALLoffWF,          X1      );

    (*						                           *)
    (*                          STANDARD DRD  CYCLE                         *)
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
     CycleSetMD(DRDCycle,   INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(DRDCycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDCycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDCycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDCycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DRDCycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDCycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
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
     CycleSetMD(DRDCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*						                           *)
    (*               EXTERNAL SERIAL PORT CLOCK - DRD  CYCLE                *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDESCKCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDESCKCycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDESCKCycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDESCKCycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DRDESCKCycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDESCKCycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDESCKCycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDESCKCycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDESCKCycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DRDESCKCycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDESCKCycle,   INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(DRDESCKCycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDESCKCycle,   DXECLKXstrobeWF, DXdriveWF,         DX0     );
     CycleSetMD(DRDESCKCycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDESCKCycle,   FSXECLKXstrobeWF,FSXdriveWF,        FSX0    );
     CycleSetMD(DRDESCKCycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDESCKCycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDESCKCycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDESCKCycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDESCKCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDESCKCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDESCKCycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDESCKCycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDESCKCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDESCKCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDESCKCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDESCKCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDESCKCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDESCKCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*                           SDRD  CYCLE                                *)
    (*               used during sync-up for binary searches                *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(SDRDCycle, DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(SDRDCycle, SH1strobeWF,     SH1strobeWF,       H1      );
     CycleSetMD(SDRDCycle, SH3strobeWF,     SH3strobeWF,       H3      );
     CycleSetMD(SDRDCycle, STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(SDRDCycle, DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(SDRDCycle, ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(SDRDCycle, ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(SDRDCycle, ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(SDRDCycle, XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(SDRDCycle, XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(SDRDCycle, INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(SDRDCycle, DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(SDRDCycle, DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(SDRDCycle, FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(SDRDCycle, FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(SDRDCycle, SCLKRstrobeWF,   CLKRdriveWF,       CLKR0   );
     CycleSetMD(SDRDCycle, SCLKXstrobeWF,   CLKXdriveWF,       CLKX0   );
     CycleSetMD(SDRDCycle, STCLKstrobeWF,   TCLKdriveWF,       TPINS   );
     CycleSetMD(SDRDCycle, ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(SDRDCycle, HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(SDRDCycle, ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(SDRDCycle, IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(SDRDCycle, RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(SDRDCycle, ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(SDRDCycle, ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(SDRDCycle, ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(SDRDCycle, ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(SDRDCycle, TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(SDRDCycle, ALLoffWF,        ALLoffWF,          X1      );
    (*						                           *)
    (*                      Sync-Up DRD  CYCLE                              *)
    (*        used to verify H1,H3,CLKX/R pw,tr,tf after syncup.            *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(SyncDRDCycle, DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(SyncDRDCycle, SyncH1LstrobeWF, SyncH1HstrobeWF,   H1      );
     CycleSetMD(SyncDRDCycle, SyncH3LstrobeWF, SyncH3HstrobeWF,   H3      );
     CycleSetMD(SyncDRDCycle, STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(SyncDRDCycle, DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(SyncDRDCycle, ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(SyncDRDCycle, ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(SyncDRDCycle, ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(SyncDRDCycle, XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(SyncDRDCycle, XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(SyncDRDCycle, INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(SyncDRDCycle, DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(SyncDRDCycle, DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(SyncDRDCycle, FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(SyncDRDCycle, FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(SyncDRDCycle,SyncCLKRLstrobeWF,SyncCLKRHstrobeWF, CLKR0   );
     CycleSetMD(SyncDRDCycle,SyncCLKXLstrobeWF,SyncCLKXHstrobeWF, CLKX0   );
     CycleSetMD(SyncDRDCycle, TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(SyncDRDCycle, ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(SyncDRDCycle, HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(SyncDRDCycle, ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(SyncDRDCycle, IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(SyncDRDCycle, RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(SyncDRDCycle, ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(SyncDRDCycle, ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(SyncDRDCycle, ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(SyncDRDCycle, ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(SyncDRDCycle, TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(SyncDRDCycle, ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                          CUSTOM DRDCI CYCLE                       *)
    (*	Used in EXTINTRPTPattern for External Interupt twINT test.	    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDCICycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDCICycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDCICycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDCICycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DRDCICycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDCICycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDCICycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDCICycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDCICycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DRDCICycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDCICycle,   ALLoffWF,        ContinueWF,        EXTINT  );
     CycleSetMD(DRDCICycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDCICycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDCICycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDCICycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DRDCICycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDCICycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDCICycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDCICycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDCICycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDCICycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDCICycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDCICycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDCICycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDCICycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDCICycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDCICycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDCICycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDCICycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*						                            *)
    (*                          DRD STOP CYCLE                              *)
    (*     Used in POWERdownPattern for the clock stop mode INT_ signal     *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDStopCycle, DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDStopCycle, H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDStopCycle, H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDStopCycle, STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DRDStopCycle, DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDStopCycle, ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDStopCycle, ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDStopCycle, ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDStopCycle, XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DRDStopCycle, XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDStopCycle, INT_BdriveWF,    INT_CLKSTPdriveWF, EXTINT  );
     CycleSetMD(DRDStopCycle, DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDStopCycle, DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDStopCycle, FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDStopCycle, FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DRDStopCycle, CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDStopCycle, CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDStopCycle, TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDStopCycle, ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDStopCycle, HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDStopCycle, ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDStopCycle, IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDStopCycle, RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDStopCycle, ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDStopCycle, ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDStopCycle, ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDStopCycle, ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDStopCycle, TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDStopCycle, ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                           DW1  CYCLE                               *)
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
     CycleSetMD(DW1Cycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW1Cycle,      DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DW1Cycle,      DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DW1Cycle,      FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DW1Cycle,      FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DW1Cycle,      CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DW1Cycle,      CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
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
     CycleSetMD(DW1Cycle,      ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*               EXTERNAL SERIAL PORT CLOCK - DW1  CYCLE                *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW1ESCKCycle,      H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DW1ESCKCycle,      H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DW1ESCKCycle,      STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DW1ESCKCycle,      DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DW1ESCKCycle,      ContinueWF,      ABUSstrobeWF,      ABUS    );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DW1ESCKCycle,      XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DW1ESCKCycle,      XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW1ESCKCycle,      DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DW1ESCKCycle,      DXECLKXstrobeWF, DXdriveWF,         DX0     );
     CycleSetMD(DW1ESCKCycle,      FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DW1ESCKCycle,      FSXECLKXstrobeWF,FSXdriveWF,        FSX0    );
     CycleSetMD(DW1ESCKCycle,      CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DW1ESCKCycle,      CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DW1ESCKCycle,      TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW1ESCKCycle,      HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DW1ESCKCycle,      IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DW1ESCKCycle,      RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DW1ESCKCycle,      TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DW1ESCKCycle,      ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                  DW2  CYCLE   SECOND WRITE CYCLE                   *)
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
     CycleSetMD(DW2Cycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW2Cycle,      DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DW2Cycle,      DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DW2Cycle,      FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DW2Cycle,      FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DW2Cycle,      CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DW2Cycle,      CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
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
     CycleSetMD(DW2Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                  DW2A CYCLE   SECOND WRITE CYCLE                     *)
    (*		WITH CORRECTION FOR STRB_ FALLING ON H1 RISING		    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2ACycle,      ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2ACycle,      H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DW2ACycle,      H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DW2ACycle,      STRB_astrobeWF,  ALLoffWF,          STRB_   );
     CycleSetMD(DW2ACycle,      DBUSendstrobeWF, ContinueWF,        DBUS    );
     CycleSetMD(DW2ACycle,      ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2ACycle,      ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DW2ACycle,      ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DW2ACycle,      XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DW2ACycle,      XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DW2ACycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW2ACycle,      DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DW2ACycle,      DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DW2ACycle,      FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DW2ACycle,      FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DW2ACycle,      CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DW2ACycle,      CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DW2ACycle,      TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2ACycle,      ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2ACycle,      HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DW2ACycle,      ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DW2ACycle,      IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DW2ACycle,      RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DW2ACycle,      ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2ACycle,      ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2ACycle,      ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DW2ACycle,      ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DW2ACycle,      TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DW2ACycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*    EXTERNAL SERIAL PORT CLOCK - DW2  CYCLE   SECOND WRITE CYCLE      *)
    (*       								    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2ESCKCycle,      H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DW2ESCKCycle,      H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DW2ESCKCycle,      STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DW2ESCKCycle,      DBUSendstrobeWF, ContinueWF,        DBUS    );
     CycleSetMD(DW2ESCKCycle,      ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DW2ESCKCycle,      XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DW2ESCKCycle,      XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW2ESCKCycle,      DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DW2ESCKCycle,      DXECLKXstrobeWF, DXdriveWF,         DX0     );
     CycleSetMD(DW2ESCKCycle,      FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DW2ESCKCycle,      FSXECLKXstrobeWF,FSXdriveWF,        FSX0    );
     CycleSetMD(DW2ESCKCycle,      CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DW2ESCKCycle,      CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DW2ESCKCycle,      TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2ESCKCycle,      HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DW2ESCKCycle,      IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DW2ESCKCycle,      RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DW2ESCKCycle,      TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DW2ESCKCycle,      ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                           DWR  CYCLE                               *)
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
     CycleSetMD(DWRCycle,     ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DWRCycle,     DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DWRCycle,     DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DWRCycle,     FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DWRCycle,     FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DWRCycle,     CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DWRCycle,     CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
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
     CycleSetMD(DWRCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*             EXTERNAL SERIAL PORT CLOCK - DWR  CYCLE                  *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWRESCKCycle,     H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DWRESCKCycle,     H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DWRESCKCycle,     STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DWRESCKCycle,     ContinueWF,      DBUSdriveWF,       DBUS    );
     CycleSetMD(DWRESCKCycle,     ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DWRESCKCycle,     XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DWRESCKCycle,     XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DWRESCKCycle,     DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DWRESCKCycle,     DXECLKXstrobeWF, DXdriveWF,         DX0     );
     CycleSetMD(DWRESCKCycle,     FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DWRESCKCycle,     FSXECLKXstrobeWF,FSXdriveWF,        FSX0    );
     CycleSetMD(DWRESCKCycle,     CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DWRESCKCycle,     CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DWRESCKCycle,     TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRESCKCycle,     HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DWRESCKCycle,     IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DWRESCKCycle,     RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DWRESCKCycle,     TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DWRESCKCycle,     ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                           DWRXF  CYCLE                               *)
    (*   Used to test tdH3HXFIO on XF0 and XF1.                             *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWRXFCycle,     ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWRXFCycle,     H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DWRXFCycle,     H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DWRXFCycle,     STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DWRXFCycle,     ContinueWF,      DBUSdriveWF,       DBUS    );
     CycleSetMD(DWRXFCycle,     ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWRXFCycle,     ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DWRXFCycle,     ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DWRXFCycle,     XFIOstrobeWF,    XFdriveWF,         XF0     );
     CycleSetMD(DWRXFCycle,     XFIOstrobeWF,    XFdriveWF,         XF1     );
     CycleSetMD(DWRXFCycle,     ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DWRXFCycle,     DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DWRXFCycle,     DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DWRXFCycle,     FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DWRXFCycle,     FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DWRXFCycle,     CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DWRXFCycle,     CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DWRXFCycle,     TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DWRXFCycle,     ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRXFCycle,     HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DWRXFCycle,     ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DWRXFCycle,     IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DWRXFCycle,     RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DWRXFCycle,     ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRXFCycle,     ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWRXFCycle,     ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DWRXFCycle,     ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DWRXFCycle,     TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DWRXFCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                          DWW  CYCLE                                *)
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
     CycleSetMD(DWWCycle,     ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DWWCycle,     DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DWWCycle,     DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DWWCycle,     FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DWWCycle,     FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DWWCycle,     CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DWWCycle,     CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
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
     CycleSetMD(DWWCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                  DRDH9  CYCLE for HOLD timings                    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDH9Cycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDH9Cycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDH9Cycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDH9Cycle,  HOLDSTRB_strobeWF,ALLoffWF,          STRB_   );
     CycleSetMD(DRDH9Cycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDH9Cycle,   HOLDABUSstrobeWF,HOLDABUSstrobeWF,  ABUS    );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDH9Cycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DRDH9Cycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DRDH9Cycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDH9Cycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDH9Cycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDH9Cycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DRDH9Cycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDH9Cycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDH9Cycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDH9Cycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDH9Cycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDH9Cycle,   HOLDRW_strobeWF, ALLoffWF,          RW_     );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDH9Cycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDH9Cycle,   ALLoffWF,        ALLoffWF,          X1      );

    (*									    *)
    (*                         DRDH7 CYCLE  for HOLD timings             *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDH7Cycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDH7Cycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDH7Cycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDH7Cycle,   HOLDSTRB_HstrobeWF,   ALLoffWF,     STRB_   );
     CycleSetMD(DRDH7Cycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDH7Cycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDH7Cycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DRDH7Cycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DRDH7Cycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDH7Cycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDH7Cycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDH7Cycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DRDH7Cycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDH7Cycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDH7Cycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDH7Cycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDH7Cycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDH7Cycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDH7Cycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDH7Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                          STANDARD DRDSIGI CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDSIGICycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDSIGICycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDSIGICycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDSIGICycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DRDSIGICycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDSIGICycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDSIGICycle,   XF0SIGIstrobeWF, XFdriveWF,         XF0     );
     CycleSetMD(DRDSIGICycle,   XFstrobeWF,      XF1SIGIdriveWF,    XF1     );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DRDSIGICycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDSIGICycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDSIGICycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDSIGICycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DRDSIGICycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDSIGICycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDSIGICycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDSIGICycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDSIGICycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDSIGICycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDSIGICycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDSIGICycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                           DW1SIGI CYCLE                               *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW1SIGICycle,      H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DW1SIGICycle,      H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DW1SIGICycle,      STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DW1SIGICycle,      DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DW1SIGICycle,      ContinueWF,      ABUSstrobeWF,      ABUS    );
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DW1SIGICycle,      XF0SIGIstrobeWF, XFdriveWF,         XF0     );
     CycleSetMD(DW1SIGICycle,      XFstrobeWF,      XF1SIGIdriveWF,    XF1     );
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW1SIGICycle,      DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DW1SIGICycle,      DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DW1SIGICycle,      FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DW1SIGICycle,      FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DW1SIGICycle,      CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DW1SIGICycle,      CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DW1SIGICycle,      TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW1SIGICycle,      HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DW1SIGICycle,      IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DW1SIGICycle,      RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DW1SIGICycle,      ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DW1SIGICycle,      TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DW1SIGICycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                  DW2SIGI CYCLE   SECOND WRITE CYCLE                   *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2SIGICycle,      H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DW2SIGICycle,      H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DW2SIGICycle,      STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DW2SIGICycle,      DBUSendstrobeWF, ContinueWF,        DBUS    );
     CycleSetMD(DW2SIGICycle,      ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DW2SIGICycle,      XF0SIGIstrobeWF, XFdriveWF,         XF0     );
     CycleSetMD(DW2SIGICycle,      XFstrobeWF,      XF1SIGIdriveWF,    XF1     );
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW2SIGICycle,      DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DW2SIGICycle,      DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DW2SIGICycle,      FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DW2SIGICycle,      FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DW2SIGICycle,      CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DW2SIGICycle,      CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DW2SIGICycle,      TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2SIGICycle,      HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DW2SIGICycle,      IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DW2SIGICycle,      RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DW2SIGICycle,      ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DW2SIGICycle,      TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DW2SIGICycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                           DWRSIGI CYCLE                               *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWRSIGICycle,     H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DWRSIGICycle,     H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DWRSIGICycle,     STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DWRSIGICycle,     ContinueWF,      DBUSdriveWF,       DBUS    );
     CycleSetMD(DWRSIGICycle,     ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DWRSIGICycle,     XF0SIGIstrobeWF, XFdriveWF,         XF0     );
     CycleSetMD(DWRSIGICycle,     XFstrobeWF,      XF1SIGIdriveWF,    XF1     );
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DWRSIGICycle,     DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DWRSIGICycle,     DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DWRSIGICycle,     FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DWRSIGICycle,     FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DWRSIGICycle,     CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DWRSIGICycle,     CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DWRSIGICycle,     TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRSIGICycle,     HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DWRSIGICycle,     IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DWRSIGICycle,     RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DWRSIGICycle,     ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DWRSIGICycle,     TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DWRSIGICycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                          STANDARD DRDLDII CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDLDIICycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDLDIICycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDLDIICycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDLDIICycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DRDLDIICycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDLDIICycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDLDIICycle,   XF0LDIIstrobeWF, XFdriveWF,         XF0     );
     CycleSetMD(DRDLDIICycle,   XFstrobeWF,      XF1LDIIdriveWF,    XF1     );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DRDLDIICycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDLDIICycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDLDIICycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDLDIICycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DRDLDIICycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDLDIICycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDLDIICycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDLDIICycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDLDIICycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDLDIICycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDLDIICycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDLDIICycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                          STANDARD DRDSTII CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDSTIICycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDSTIICycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDSTIICycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDSTIICycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DRDSTIICycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDSTIICycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDSTIICycle,   XF0STIIstrobeWF, XFdriveWF,         XF0     );
     CycleSetMD(DRDSTIICycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DRDSTIICycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDSTIICycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDSTIICycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDSTIICycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DRDSTIICycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDSTIICycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDSTIICycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDSTIICycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDSTIICycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDSTIICycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDSTIICycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDSTIICycle,   ALLoffWF,        ALLoffWF,          X1      );

    (*									    *)
    (*                          STANDARD XF1OI CYCLE                        *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(XF1OICycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(XF1OICycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(XF1OICycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(XF1OICycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(XF1OICycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(XF1OICycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(XF1OICycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(XF1OICycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(XF1OICycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(XF1OICycle,   XFOIstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(XF1OICycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(XF1OICycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(XF1OICycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(XF1OICycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(XF1OICycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(XF1OICycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(XF1OICycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(XF1OICycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(XF1OICycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(XF1OICycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(XF1OICycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(XF1OICycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(XF1OICycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(XF1OICycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(XF1OICycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(XF1OICycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(XF1OICycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(XF1OICycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(XF1OICycle,   ALLoffWF,        ALLoffWF,          X1      );
   (*									    *)
    (*                          STANDARD XFIO CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(XFIOCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(XFIOCycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(XFIOCycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(XFIOCycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(XFIOCycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(XFIOCycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(XFIOCycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(XFIOCycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(XFIOCycle,   XFIOstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(XFIOCycle,   XFIOstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(XFIOCycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(XFIOCycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(XFIOCycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(XFIOCycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(XFIOCycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(XFIOCycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(XFIOCycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(XFIOCycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(XFIOCycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(XFIOCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(XFIOCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(XFIOCycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(XFIOCycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(XFIOCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(XFIOCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(XFIOCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(XFIOCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(XFIOCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(XFIOCycle,   ALLoffWF,        ALLoffWF,          X1      );
   (*									    *)
    (*                          STANDARD XF0OI CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(XF0OICycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(XF0OICycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(XF0OICycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(XF0OICycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(XF0OICycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(XF0OICycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(XF0OICycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(XF0OICycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(XF0OICycle,   XFOIstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(XF0OICycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(XF0OICycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(XF0OICycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(XF0OICycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(XF0OICycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(XF0OICycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(XF0OICycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(XF0OICycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(XF0OICycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(XF0OICycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(XF0OICycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(XF0OICycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(XF0OICycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(XF0OICycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(XF0OICycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(XF0OICycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(XF0OICycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(XF0OICycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(XF0OICycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(XF0OICycle,   ALLoffWF,        ALLoffWF,          X1      );
   (*									    *)
    (*                          STANDARD TIMGPIO CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(TIMGPIOCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(TIMGPIOCycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(TIMGPIOCycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(TIMGPIOCycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(TIMGPIOCycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(TIMGPIOCycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(TIMGPIOCycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(TIMGPIOCycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(TIMGPIOCycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(TIMGPIOCycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(TIMGPIOCycle,   INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(TIMGPIOCycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(TIMGPIOCycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(TIMGPIOCycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(TIMGPIOCycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(TIMGPIOCycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(TIMGPIOCycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(TIMGPIOCycle,   TIMGPIOstrobeWF, TIMGPIOdriveWF,    TPINS   );
     CycleSetMD(TIMGPIOCycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(TIMGPIOCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(TIMGPIOCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(TIMGPIOCycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(TIMGPIOCycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(TIMGPIOCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(TIMGPIOCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(TIMGPIOCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(TIMGPIOCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(TIMGPIOCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(TIMGPIOCycle,   ALLoffWF,        ALLoffWF,          X1      );


    (*									    *)
    (*                          STANDARD DRDa CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DRDaCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDaCycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDaCycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDaCycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DRDaCycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDaCycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDaCycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDaCycle,   ALLoffWF,        RESETHIGH_driveWF, RESET_  );
     CycleSetMD(DRDaCycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DRDaCycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDaCycle,   INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(DRDaCycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDaCycle,   DXastrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDaCycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDaCycle,   FSXstrobeWF,     FSXadriveWF,        FSX0    );
     CycleSetMD(DRDaCycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDaCycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDaCycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDaCycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDaCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDaCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDaCycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDaCycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDaCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDaCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDaCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDaCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDaCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDaCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*               HOLDTR Cycle for Address Bus                           *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(HOLDTRCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(HOLDTRCycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(HOLDTRCycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	ALLoffWF,	   STRB_   );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,  DBUSdriveWF,       DBUS    );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,  ABUSstrobeWF,      ABUS    );
     CycleSetMD(HOLDTRCycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(HOLDTRCycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	XFdriveWF,	   XF0	   );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	XFdriveWF,	   XF1	   );
     CycleSetMD(HOLDTRCycle,   ALLoffWF,        ALLoffWF,          X1      );
     CycleSetMD(HOLDTRCycle,   ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	DRdriveWF,	   DR0	   );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	DXdriveWF,	   DX0	   );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	FSRdriveWF,	   FSR0    );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	FSXdriveWF,	   FSX0    );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	CLKRdriveWF,	   CLKR0   );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	CLKXdriveWF,	   CLKX0   );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(HOLDTRCycle,   HOLD_BdriveWF,   HOLD_driveWF,      HOLD_   );
     CycleSetMD(HOLDTRCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(HOLDTRCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(HOLDTRCycle,   HOLDTRstrobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(HOLDTRCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(HOLDTRCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(HOLDTRCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(HOLDTRCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(HOLDTRCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
    (*									    *)
    (*                          STANDARD DRD  CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(MCSCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(MCSCycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(MCSCycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(MCSCycle,   MCS_ABUSstrobeWF,ALLoffWF,          STRB_   );
     CycleSetMD(MCSCycle,   DBUSdriveWF,     MCS_ABUSstrobeWF,   DBUS    );
     CycleSetMD(MCSCycle,   MCS_ABUSstrobeWF,MCS_ABUSstrobeWF,  ABUS    );
     CycleSetMD(MCSCycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(MCSCycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(MCSCycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(MCSCycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(MCSCycle,   INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(MCSCycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(MCSCycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(MCSCycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(MCSCycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(MCSCycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(MCSCycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(MCSCycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(MCSCycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(MCSCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(MCSCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(MCSCycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(MCSCycle,   MCS_ABUSstrobeWF,ALLoffWF,          RW_     );
     CycleSetMD(MCSCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(MCSCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(MCSCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(MCSCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(MCSCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(MCSCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                          STANDARD DRDb  CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDbCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDbCycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDbCycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDbCycle,   STRB_bstrobeWF,  ALLoffWF,          STRB_   );
     CycleSetMD(DRDbCycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDbCycle,   ABUSbstrobeWF,   ABUSbstrobeWF,     ABUS    );
     CycleSetMD(DRDbCycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDbCycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDbCycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DRDbCycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDbCycle,   INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(DRDbCycle,   DRstrobeWF,      DRdriveWF,         DR0     );
     CycleSetMD(DRDbCycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDbCycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDbCycle,   FSXstrobeWF,     FSXbdriveWF,       FSX0    );
     CycleSetMD(DRDbCycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDbCycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDbCycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDbCycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDbCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDbCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDbCycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDbCycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDbCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDbCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDbCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDbCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDbCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDbCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                          STANDARD DRD  CYCLE                       *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(DRDthCycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DRDthCycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DRDthCycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DRDthCycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DRDthCycle,   DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DRDthCycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(DRDthCycle,   ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DRDthCycle,   ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DRDthCycle,   XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DRDthCycle,   XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DRDthCycle,   INT_BdriveWF,    INT_driveWF,       EXTINT  );
     CycleSetMD(DRDthCycle,   DRstrobeWF,      DRthdriveWF,         DR0     );
     CycleSetMD(DRDthCycle,   DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DRDthCycle,   FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DRDthCycle,   FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DRDthCycle,   CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DRDthCycle,   CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DRDthCycle,   TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DRDthCycle,   ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DRDthCycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DRDthCycle,   ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DRDthCycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DRDthCycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DRDthCycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DRDthCycle,   ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DRDthCycle,   ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DRDthCycle,   ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DRDthCycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DRDthCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                           DW1  CYCLE                               *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW1thCycle,      ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW1thCycle,      H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DW1thCycle,      H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DW1thCycle,      STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DW1thCycle,      DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DW1thCycle,      ContinueWF,      ABUSstrobeWF,      ABUS    );
     CycleSetMD(DW1thCycle,      ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DW1thCycle,      ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DW1thCycle,      XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DW1thCycle,      XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DW1thCycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW1thCycle,      DRstrobeWF,      DRthdriveWF,         DR0     );
     CycleSetMD(DW1thCycle,      DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DW1thCycle,      FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DW1thCycle,      FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DW1thCycle,      CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DW1thCycle,      CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DW1thCycle,      TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW1thCycle,      ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW1thCycle,      HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DW1thCycle,      ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DW1thCycle,      IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DW1thCycle,      RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DW1thCycle,      ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW1thCycle,      ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW1thCycle,      ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DW1thCycle,      ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DW1thCycle,      TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DW1thCycle,      ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                  DW2  CYCLE   SECOND WRITE CYCLE                   *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2thCycle,      ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2thCycle,      H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DW2thCycle,      H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DW2thCycle,      STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DW2thCycle,      DBUSendstrobeWF, ContinueWF,        DBUS    );
     CycleSetMD(DW2thCycle,      ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2thCycle,      ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DW2thCycle,      ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DW2thCycle,      XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DW2thCycle,      XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DW2thCycle,      ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DW2thCycle,      DRstrobeWF,      DRthdriveWF,         DR0     );
     CycleSetMD(DW2thCycle,      DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DW2thCycle,      FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DW2thCycle,      FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DW2thCycle,      CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DW2thCycle,      CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DW2thCycle,      TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2thCycle,      ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2thCycle,      HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DW2thCycle,      ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DW2thCycle,      IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DW2thCycle,      RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DW2thCycle,      ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2thCycle,      ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2thCycle,      ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DW2thCycle,      ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DW2thCycle,      TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DW2thCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                           DWR  CYCLE                               *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWRthCycle,     ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWRthCycle,     H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DWRthCycle,     H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DWRthCycle,     STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DWRthCycle,     ContinueWF,      DBUSdriveWF,       DBUS    );
     CycleSetMD(DWRthCycle,     ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWRthCycle,     ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DWRthCycle,     ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DWRthCycle,     XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DWRthCycle,     XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DWRthCycle,     ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DWRthCycle,     DRstrobeWF,      DRthdriveWF,         DR0     );
     CycleSetMD(DWRthCycle,     DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DWRthCycle,     FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DWRthCycle,     FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DWRthCycle,     CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DWRthCycle,     CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DWRthCycle,     TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DWRthCycle,     ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRthCycle,     HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DWRthCycle,     ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DWRthCycle,     IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DWRthCycle,     RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DWRthCycle,     ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRthCycle,     ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWRthCycle,     ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DWRthCycle,     ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DWRthCycle,     TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DWRthCycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*                          DWW  CYCLE                                *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DWWthCycle,     ALLoffWF,        CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DWWthCycle,     H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(DWWthCycle,     H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(DWWthCycle,     STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(DWWthCycle,     DBUSstrobeWF,    DBUSdriveWF,       DBUS    );
     CycleSetMD(DWWthCycle,     ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(DWWthCycle,     ALLoffWF,        RDY_driveWF,       RDY_    );
     CycleSetMD(DWWthCycle,     ALLoffWF,        RESET_driveWF,     RESET_  );
     CycleSetMD(DWWthCycle,     XFstrobeWF,      XFdriveWF,         XF0     );
     CycleSetMD(DWWthCycle,     XFstrobeWF,      XFdriveWF,         XF1     );
     CycleSetMD(DWWthCycle,     ALLoffWF,        INT_driveWF,       EXTINT  );
     CycleSetMD(DWWthCycle,     DRstrobeWF,      DRthdriveWF,         DR0     );
     CycleSetMD(DWWthCycle,     DXstrobeWF,      DXdriveWF,         DX0     );
     CycleSetMD(DWWthCycle,     FSRstrobeWF,     FSRdriveWF,        FSR0    );
     CycleSetMD(DWWthCycle,     FSXstrobeWF,     FSXdriveWF,        FSX0    );
     CycleSetMD(DWWthCycle,     CLKRstrobeWF,    CLKRdriveWF,       CLKR0   );
     CycleSetMD(DWWthCycle,     CLKXstrobeWF,    CLKXdriveWF,       CLKX0   );
     CycleSetMD(DWWthCycle,     TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DWWthCycle,     ALLoffWF,        HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWthCycle,     HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(DWWthCycle,     ALLoffWF,        MCSdriveWF,        MCS     );
     CycleSetMD(DWWthCycle,     IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(DWWthCycle,     RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(DWWthCycle,     ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWthCycle,     ALLoffWF,        SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWWthCycle,     ALLoffWF,        TESTdriveWF,       C0      );
     CycleSetMD(DWWthCycle,     ALLoffWF,        TEST1driveWF,       C1      );
     CycleSetMD(DWWthCycle,     TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(DWWthCycle,   ALLoffWF,        ALLoffWF,          X1      );

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
     CycleSetMD(DRDSP1Cycle,   EXTDXstrobe1WF,	EXTDXdriveWF,	   DX0	   );
     CycleSetMD(DRDSP1Cycle,   ContinueWF,	EXFSRdrive1WF,	   FSR0    );
     CycleSetMD(DRDSP1Cycle,   ContinueWF,	EXFSXdrive1WF,	   FSX0    );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	SPCLKRdrive1WF,    CLKR0   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	SPCLKXdrive1WF,    CLKX0   );
     CycleSetMD(DRDSP1Cycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP1Cycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP1Cycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP1Cycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	SCANINdriveWF,	   SCANIN  );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	TESTdriveWF,	   C0	   );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,	TEST1driveWF,	   C1	   );
     CycleSetMD(DRDSP1Cycle,   TESTstrobeWF,	ALLoffWF,	   SCANOUT );
     CycleSetMD(DRDSP1Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*				SERPORT DRDSP1A CYCLE			    *)
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
     CycleSetMD(DRDSP1ACycle,   EXTDXAstrobe1WF,EXTDXdriveWF,	   DX0	   );
     CycleSetMD(DRDSP1ACycle,   ContinueWF,	EXFSRdrive1WF,	   FSR0    );
     CycleSetMD(DRDSP1ACycle,   ContinueWF,	EXFSXdrive1WF,	   FSX0    );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	SPCLKRdrive1WF,    CLKR0   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	SPCLKXdrive1WF,    CLKX0   );
     CycleSetMD(DRDSP1ACycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP1ACycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP1ACycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP1ACycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	SCANINdriveWF,	   SCANIN  );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	TESTdriveWF,	   C0	   );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,	TEST1driveWF,	   C1	   );
     CycleSetMD(DRDSP1ACycle,   TESTstrobeWF,	ALLoffWF,	   SCANOUT );
     CycleSetMD(DRDSP1ACycle,   ALLoffWF,        ALLoffWF,          X1      );
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
     CycleSetMD(DW1SP1Cycle,	  EXTDXstrobe1WF,  EXTDXdriveWF,      DX0     );
     CycleSetMD(DW1SP1Cycle,	  ContinueWF,	   EXFSRdrive1WF,     FSR0    );
     CycleSetMD(DW1SP1Cycle,	  ContinueWF,	   EXFSXdrive1WF,     FSX0    );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   SPCLKRdrive1WF,    CLKR0   );
     CycleSetMD(DW1SP1Cycle,	  ALLoffWF,	   SPCLKXdrive1WF,    CLKX0   );
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
     CycleSetMD(DW2SP1Cycle,	  EXTDXstrobe1WF,  EXTDXdriveWF,      DX0     );
     CycleSetMD(DW2SP1Cycle,	  ContinueWF,	   EXFSRdrive1WF,     FSR0    );
     CycleSetMD(DW2SP1Cycle,	  ContinueWF,	   EXFSXdrive1WF,     FSX0    );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   SPCLKRdrive1WF,    CLKR0   );
     CycleSetMD(DW2SP1Cycle,	  ALLoffWF,	   SPCLKXdrive1WF,    CLKX0   );
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
     CycleSetMD(DWRSP1Cycle,	 EXTDXstrobe1WF,  EXTDXdriveWF,	     DX0     );
     CycleSetMD(DWRSP1Cycle,	 ContinueWF,	  EXFSRdrive1WF,     FSR0    );
     CycleSetMD(DWRSP1Cycle,	 ContinueWF,	  EXFSXdrive1WF,     FSX0    );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  SPCLKRdrive1WF,    CLKR0   );
     CycleSetMD(DWRSP1Cycle,	 ALLoffWF,	  SPCLKXdrive1WF,    CLKX0   );
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
     CycleSetMD(DWWSP1Cycle,	 EXTDXstrobe1WF,  EXTDXdriveWF,	     DX0     );
     CycleSetMD(DWWSP1Cycle,	 ContinueWF,	  EXFSRdrive1WF,     FSR0    );
     CycleSetMD(DWWSP1Cycle,	 ContinueWF,	  EXFSXdrive1WF,     FSX0    );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  SPCLKRdrive1WF,    CLKR0   );
     CycleSetMD(DWWSP1Cycle,	 ALLoffWF,	  SPCLKXdrive1WF,    CLKX0   );
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
     CycleSetMD(DWWSP1AaCycle,	 EXTDXAastrobe1WF,EXTDXdriveWF,	     DX0     );
     CycleSetMD(DWWSP1AaCycle,	 ContinueWF,	  EXFSRdrive1WF,     FSR0    );
     CycleSetMD(DWWSP1AaCycle,	 ContinueWF,	  ContinueWF,        FSX0    );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  SPCLKRdrive1WF,    CLKR0   );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  SPCLKXdrive1WF,    CLKX0   );
     CycleSetMD(DWWSP1AaCycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP1AaCycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP1AaCycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP1AaCycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP1AaCycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
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
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	EXTDRdrive2WF,	   DR0	   );
     CycleSetMD(DRDSP2Cycle,   ContinueWF,	EXTDXdriveWF,	   DX0	   );
     CycleSetMD(DRDSP2Cycle,   ContinueWF,	EXFSRdrive2WF,     FSR0    );
     CycleSetMD(DRDSP2Cycle,   ContinueWF,	ContinueWF,	   FSX0    );
     CycleSetMD(DRDSP2Cycle,   ContinueWF,	SPCLKRdrive2WF,    CLKR0   );
     CycleSetMD(DRDSP2Cycle,   ContinueWF,	SPCLKXdrive2WF,    CLKX0   );
     CycleSetMD(DRDSP2Cycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP2Cycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP2Cycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP2Cycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP2Cycle,   ALLoffWF,	SCANINdriveWF,	   SCANIN  );
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
     CycleSetMD(DW1SP2Cycle,	  ALLoffWF,	   EXTDRdrive2WF,     DR0     );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,	   EXTDXdriveWF,      DX0     );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,      EXFSRdrive2WF,     FSR0    );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,	   ContinueWF,        FSX0    );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,	   SPCLKRdrive2WF,    CLKR0   );
     CycleSetMD(DW1SP2Cycle,	  ContinueWF,	   SPCLKXdrive2WF,    CLKX0   );
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
     CycleSetMD(DW2SP2Cycle,	  ALLoffWF,	   EXTDRdrive2WF,     DR0     );
     CycleSetMD(DW2SP2Cycle,	  ContinueWF,	   EXTDXdriveWF,      DX0     );
     CycleSetMD(DW2SP2Cycle,	  ContinueWF,      EXFSRdrive2WF,     FSR0    );
     CycleSetMD(DW2SP2Cycle,	  ContinueWF,	   EXFSXdrive2WF,     FSX0    );
     CycleSetMD(DW2SP2Cycle,	  ContinueWF,	   SPCLKRdrive2WF,    CLKR0   );
     CycleSetMD(DW2SP2Cycle,	  ContinueWF,	   SPCLKXdrive2WF,    CLKX0   );
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
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  EXTDRdrive2WF,     DR0     );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,	  EXTDXdriveWF,	     DX0     );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,      EXFSRdrive2WF,     FSR0    );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,	  ContinueWF,        FSX0    );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,	  SPCLKRdrive2WF,    CLKR0   );
     CycleSetMD(DWRSP2Cycle,	 ContinueWF,	  SPCLKXdrive2WF,    CLKX0   );
     CycleSetMD(DWRSP2Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRSP2Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWRSP2Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWRSP2Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRSP2Cycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
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
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  EXTDRdrive2WF,     DR0     );
     CycleSetMD(DWWSP2Cycle,	 ContinueWF,	  EXTDXdriveWF,	     DX0     );
     CycleSetMD(DWWSP2Cycle,	 ContinueWF,      EXFSRdrive2WF,     FSR0    );
     CycleSetMD(DWWSP2Cycle,	 ContinueWF,	  ContinueWF,        FSX0    );
     CycleSetMD(DWWSP2Cycle,	 ContinueWF,	  SPCLKRdrive2WF,  CLKR0   );
     CycleSetMD(DWWSP2Cycle,	 ContinueWF,	  SPCLKXdrive2WF,  CLKX0   );
     CycleSetMD(DWWSP2Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP2Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP2Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP2Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP2Cycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
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
     CycleSetMD(DRDSP4Cycle,   EXTDXstrobe4WF,	EXTDXdriveWF,	   DX0	   );
     CycleSetMD(DRDSP4Cycle,   ContinueWF,	ContinueWF,	   FSR0    );
     CycleSetMD(DRDSP4Cycle,   ContinueWF,	FSXdriveWF,	   FSX0    );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	SPCLKRdrive4WF,    CLKR0   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	SPCLKXdrive4WF,    CLKX0   );
     CycleSetMD(DRDSP4Cycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP4Cycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP4Cycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP4Cycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP4Cycle,   ALLoffWF,	SCANINdriveWF,	   SCANIN  );
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
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   ContinueWF,        DR0     );
     CycleSetMD(DW1SP4Cycle,	  EXTDXstrobe4WF,  EXTDXdriveWF,      DX0     );
     CycleSetMD(DW1SP4Cycle,	  ContinueWF,	   ContinueWF,	      FSR0    );
     CycleSetMD(DW1SP4Cycle,	  ContinueWF,	   FSXdriveWF,	      FSX0    );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   SPCLKRdrive4WF,    CLKR0   );
     CycleSetMD(DW1SP4Cycle,	  ALLoffWF,	   SPCLKXdrive4WF,    CLKX0   );
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
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   ContinueWF,        DR0     );
     CycleSetMD(DW2SP4Cycle,	  EXTDXstrobe4WF,  EXTDXdriveWF,      DX0     );
     CycleSetMD(DW2SP4Cycle,	  ContinueWF,	   ContinueWF,	      FSR0    );
     CycleSetMD(DW2SP4Cycle,	  ContinueWF,	   FSXdriveWF,	      FSX0    );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   SPCLKRdrive4WF,    CLKR0   );
     CycleSetMD(DW2SP4Cycle,	  ALLoffWF,	   SPCLKXdrive4WF,    CLKX0   );
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
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  ContinueWF,        DR0     );
     CycleSetMD(DWRSP4Cycle,	 EXTDXstrobe4WF,  EXTDXdriveWF,      DX0     );
     CycleSetMD(DWRSP4Cycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWRSP4Cycle,	 ContinueWF,	  FSXdriveWF,	     FSX0    );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  SPCLKRdrive4WF,    CLKR0   );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  SPCLKXdrive4WF,    CLKX0   );
     CycleSetMD(DWRSP4Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRSP4Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWRSP4Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWRSP4Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRSP4Cycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
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
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  ContinueWF,        DR0     );
     CycleSetMD(DWWSP4Cycle,	 EXTDXstrobe4WF,  EXTDXdriveWF,	     DX0     );
     CycleSetMD(DWWSP4Cycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(DWWSP4Cycle,	 ContinueWF,	  FSXdriveWF,	     FSX0    );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  SPCLKRdrive4WF,    CLKR0   );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  SPCLKXdrive4WF,    CLKX0   );
     CycleSetMD(DWWSP4Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP4Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP4Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP4Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWWSP4Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWWSP4Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWWSP4Cycle,   ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*				TDDXZ CYCLE (Modified DWWSP4)		    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  CLKINdriveWF,      X2CLKIN );
     CycleSetMD(TDDXZCycle,	 H1strobeWF,	  ALLoffWF,	     H1      );
     CycleSetMD(TDDXZCycle,	 H3strobeWF,	  ALLoffWF,	     H3      );
     CycleSetMD(TDDXZCycle,	 STRB_strobeWF,   ALLoffWF,	     STRB_   );
     CycleSetMD(TDDXZCycle,	 DBUSstrobeWF,	  DBUSdriveWF,	     DBUS    );
     CycleSetMD(TDDXZCycle,	 ABUSwrtbgnstrobeWF, ABUSstrobeWF,   ABUS    );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  RDY_driveWF,	     RDY_    );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  RESET_driveWF,     RESET_  );
     CycleSetMD(TDDXZCycle,	 XFstrobeWF,	  XFdriveWF,	     XF0     );
     CycleSetMD(TDDXZCycle,	 XFstrobeWF,	  XFdriveWF,	     XF1     );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  INT_driveWF,	     EXTINT  );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  ContinueWF,        DR0     );
     CycleSetMD(TDDXZCycle,	 TDDXZstrobeWF,   TDDXZstrobeWF,     DX0     );
     CycleSetMD(TDDXZCycle,	 ContinueWF,	  ContinueWF,	     FSR0    );
     CycleSetMD(TDDXZCycle,	 ContinueWF,	  FSXdriveWF,	     FSX0    );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  SPCLKRdrive4WF,    CLKR0   );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  SPCLKXdrive4WF,    CLKX0   );
     CycleSetMD(TDDXZCycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(TDDXZCycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(TDDXZCycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(TDDXZCycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(TDDXZCycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(TDDXZCycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(TDDXZCycle,   	 ALLoffWF,        ALLoffWF,          X1      );
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
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	EXTDRdrive5WF,	   DR0	   );
     CycleSetMD(DRDSP5Cycle,   ContinueWF,	EXTDXdriveWF,	   DX0	   );
     CycleSetMD(DRDSP5Cycle,   ContinueWF,	FSRdriveWF,	   FSR0    );
     CycleSetMD(DRDSP5Cycle,   ContinueWF,	ContinueWF,	   FSX0    );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	SPCLKRdrive5WF,    CLKR0   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	SPCLKXdrive5WF,    CLKX0   );
     CycleSetMD(DRDSP5Cycle,   TCLKstrobeWF,	TCLKdriveWF,	   TPINS   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	HOLD_driveWF,	   HOLD_   );
     CycleSetMD(DRDSP5Cycle,   HOLDA_strobeWF,	ALLoffWF,	   HOLDA_  );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	MCSdriveWF,	   MCS	   );
     CycleSetMD(DRDSP5Cycle,   IACK_strobeWF,	ALLoffWF,	   IACK_   );
     CycleSetMD(DRDSP5Cycle,   RW_strobeWF,	ALLoffWF,	   RW_	   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	MCMP_driveWF,	   MCMP_   );
     CycleSetMD(DRDSP5Cycle,   ALLoffWF,	SCANINdriveWF,	   SCANIN  );
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
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   EXTDRdrive5WF,     DR0     );
     CycleSetMD(DW1SP5Cycle,	  ContinueWF,	   EXTDXdriveWF,      DX0     );
     CycleSetMD(DW1SP5Cycle,	  ContinueWF,	   FSRdriveWF,	      FSR0    );
     CycleSetMD(DW1SP5Cycle,	  ContinueWF,	   ContinueWF,	      FSX0    );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   SPCLKRdrive5WF,    CLKR0   );
     CycleSetMD(DW1SP5Cycle,	  ALLoffWF,	   SPCLKXdrive5WF,    CLKX0   );
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
     CycleSetMD(DW1SP5Cycle,   	  ALLoffWF,        ALLoffWF,          X1      );
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
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   EXTDRdrive5WF,     DR0     );
     CycleSetMD(DW2SP5Cycle,	  ContinueWF,	   EXTDXdriveWF,      DX0     );
     CycleSetMD(DW2SP5Cycle,	  ContinueWF,	   FSRdriveWF,	      FSR0    );
     CycleSetMD(DW2SP5Cycle,	  ContinueWF,	   ContinueWF,	      FSX0    );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   SPCLKRdrive5WF,    CLKR0   );
     CycleSetMD(DW2SP5Cycle,	  ALLoffWF,	   SPCLKXdrive5WF,    CLKX0   );
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
     CycleSetMD(DW2SP5Cycle,      ALLoffWF,        ALLoffWF,          X1      );
    (*									    *)
    (*			DW2SP5Aa CYCLE   SECOND WRITE CYCLE		    *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   CLKINdriveWF,      X2CLKIN );
     CycleSetMD(DW2SP5AaCycle,	  H1strobeWF,	   ALLoffWF,	      H1      );
     CycleSetMD(DW2SP5AaCycle,	  H3strobeWF,	   ALLoffWF,	      H3      );
     CycleSetMD(DW2SP5AaCycle,	  STRB_strobeWF,   ALLoffWF,	      STRB_   );
     CycleSetMD(DW2SP5AaCycle,	  DBUSendstrobeWF, ContinueWF,	      DBUS    );
     CycleSetMD(DW2SP5AaCycle,	  ABUSwrtendstrobeWF, ContinueWF,     ABUS    );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   RDY_driveWF,       RDY_    );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   RESET_driveWF,     RESET_  );
     CycleSetMD(DW2SP5AaCycle,	  XFstrobeWF,	   XFdriveWF,	      XF0     );
     CycleSetMD(DW2SP5AaCycle,	  XFstrobeWF,	   XFdriveWF,	      XF1     );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   INT_driveWF,       EXTINT  );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   EXTDRdrive5WF,     DR0     );
     CycleSetMD(DW2SP5AaCycle,	  ContinueWF,	   EXTDXdriveWF,      DX0     );
     CycleSetMD(DW2SP5AaCycle,	  ContinueWF,	   FSRdriveWF,	      FSR0    );
     CycleSetMD(DW2SP5AaCycle,	  ContinueWF,	   EXFSXdrive5WF,     FSX0    );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   SPCLKRdrive5WF,    CLKR0   );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   SPCLKXdrive5WF,    CLKX0   );
     CycleSetMD(DW2SP5AaCycle,	  TCLKstrobeWF,    TCLKdriveWF,       TPINS   );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   HOLD_driveWF,      HOLD_   );
     CycleSetMD(DW2SP5AaCycle,	  HOLDA_strobeWF,  ALLoffWF,	      HOLDA_  );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   MCSdriveWF,	      MCS     );
     CycleSetMD(DW2SP5AaCycle,	  IACK_strobeWF,   ALLoffWF,	      IACK_   );
     CycleSetMD(DW2SP5AaCycle,	  RW_strobeWF,	   ALLoffWF,	      RW_     );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   MCMP_driveWF,      MCMP_   );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   SCANINdriveWF,     SCANIN  );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   TESTdriveWF,       C0      );
     CycleSetMD(DW2SP5AaCycle,	  ALLoffWF,	   TEST1driveWF,       C1      );
     CycleSetMD(DW2SP5AaCycle,	  TESTstrobeWF,    ALLoffWF,	      SCANOUT );
     CycleSetMD(DW2SP5AaCycle,    ALLoffWF,        ALLoffWF,          X1      );
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
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  EXTDRdrive5WF,     DR0     );
     CycleSetMD(DWRSP5Cycle,	 ContinueWF,	  EXTDXdriveWF,	     DX0     );
     CycleSetMD(DWRSP5Cycle,	 ContinueWF,	  FSRdriveWF,	     FSR0    );
     CycleSetMD(DWRSP5Cycle,	 ContinueWF,	  ContinueWF,	     FSX0    );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  SPCLKRdrive5WF,    CLKR0   );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  SPCLKXdrive5WF,    CLKX0   );
     CycleSetMD(DWRSP5Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWRSP5Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWRSP5Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWRSP5Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWRSP5Cycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
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
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  EXTDRdrive5WF,     DR0     );
     CycleSetMD(DWWSP5Cycle,	 ContinueWF,	  EXTDXdriveWF,	     DX0     );
     CycleSetMD(DWWSP5Cycle,	 ContinueWF,	  FSRdriveWF,	     FSR0    );
     CycleSetMD(DWWSP5Cycle,	 ContinueWF,	  ContinueWF,	     FSX0    );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  SPCLKRdrive5WF,    CLKR0   );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  SPCLKXdrive5WF,    CLKX0   );
     CycleSetMD(DWWSP5Cycle,	 TCLKstrobeWF,	  TCLKdriveWF,	     TPINS   );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  HOLD_driveWF,      HOLD_   );
     CycleSetMD(DWWSP5Cycle,	 HOLDA_strobeWF,  ALLoffWF,	     HOLDA_  );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  MCSdriveWF,	     MCS     );
     CycleSetMD(DWWSP5Cycle,	 IACK_strobeWF,   ALLoffWF,	     IACK_   );
     CycleSetMD(DWWSP5Cycle,	 RW_strobeWF,	  ALLoffWF,	     RW_     );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  MCMP_driveWF,      MCMP_   );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  SCANINdriveWF,     SCANIN  );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  TESTdriveWF,	     C0      );
     CycleSetMD(DWWSP5Cycle,	 ALLoffWF,	  TEST1driveWF,	     C1      );
     CycleSetMD(DWWSP5Cycle,	 TESTstrobeWF,	  ALLoffWF,	     SCANOUT );
     CycleSetMD(DWWSP5Cycle,   ALLoffWF,        ALLoffWF,          X1      );

    (*						                           *)
    (*                          STANDARD IDLE  CYCLE                         *)
    (*									    *)
    (*	       Global Cycle	Compare Wave	 Drive Wave	    PinList *)
    (*		Type (GCT)     (from AC Table)	(from AC Table) 	    *)
    (*									    *)

     CycleSetMD(IDLECycle,   DUMPclkWF,       CLKINdriveWF,      X2CLKIN );
     CycleSetMD(IDLECycle,   H1strobeWF,      ALLoffWF,          H1      );
     CycleSetMD(IDLECycle,   H3strobeWF,      ALLoffWF,          H3      );
     CycleSetMD(IDLECycle,   STRB_strobeWF,   ALLoffWF,          STRB_   );
     CycleSetMD(IDLECycle,   DBUSstrobeWF,    MCMP_driveWF,      DBUS    );
     CycleSetMD(IDLECycle,   ABUSstrobeWF,    ABUSstrobeWF,      ABUS    );
     CycleSetMD(IDLECycle,   ALLoffWF,        MCMP_driveWF,      RDY_    );
     CycleSetMD(IDLECycle,   ALLoffWF,        MCMP_driveWF,      RESET_  );
     CycleSetMD(IDLECycle,   XFstrobeWF,      MCMP_driveWF,      XF0     );
     CycleSetMD(IDLECycle,   XFstrobeWF,      MCMP_driveWF,      XF1     );
     CycleSetMD(IDLECycle,   INT_BdriveWF,    MCMP_driveWF,      EXTINT  );
     CycleSetMD(IDLECycle,   DRstrobeWF,      MCMP_driveWF,      DR0     );
     CycleSetMD(IDLECycle,   DXstrobeWF,      MCMP_driveWF,      DX0     );
     CycleSetMD(IDLECycle,   FSRstrobeWF,     MCMP_driveWF,      FSR0    );
     CycleSetMD(IDLECycle,   FSXstrobeWF,     MCMP_driveWF,      FSX0    );
     CycleSetMD(IDLECycle,   CLKRstrobeWF,    MCMP_driveWF,      CLKR0   );
     CycleSetMD(IDLECycle,   CLKXstrobeWF,    MCMP_driveWF,      CLKX0   );
     CycleSetMD(IDLECycle,   TCLKstrobeWF,    MCMP_driveWF,      TPINS   );
     CycleSetMD(IDLECycle,   ALLoffWF,        MCMP_driveWF,      HOLD_   );
     CycleSetMD(IDLECycle,   HOLDA_strobeWF,  ALLoffWF,          HOLDA_  );
     CycleSetMD(IDLECycle,   ALLoffWF,        MCMP_driveWF,      MCS     );
     CycleSetMD(IDLECycle,   IACK_strobeWF,   ALLoffWF,          IACK_   );
     CycleSetMD(IDLECycle,   RW_strobeWF,     ALLoffWF,          RW_     );
     CycleSetMD(IDLECycle,   ALLoffWF,        MCMP_driveWF,      MCMP_   );
     CycleSetMD(IDLECycle,   ALLoffWF,        MCMP_driveWF,      SCANIN  );
     CycleSetMD(IDLECycle,   ALLoffWF,        MCMP_driveWF,      C0      );
     CycleSetMD(IDLECycle,   ALLoffWF,        MCMP_driveWF,      C1      );
     CycleSetMD(IDLECycle,   TESTstrobeWF,    ALLoffWF,          SCANOUT );
     CycleSetMD(IDLECycle,   ALLoffWF,        ALLoffWF,          X1      );
