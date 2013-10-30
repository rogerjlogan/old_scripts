






























        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        

procedure CycleTableSet;

begin

if ( cycletable in [TIallCycleTable, SCACycleTable] ) then
 begin

  CycleTableOpen(  SCACycleTable );


    
    
    
    
    
    
  CycleSet  (   NO_EVENT,     ContinueWF,ALLPINS);


  CycleSetMD(   ShutSCA,       ContinueWF,        ContinueWF,           ADC );
  CycleSetMD(   ShutSCA,      ContinueWF,       ContinueWF,       TRIGINS );
  CycleSetMD(   ShutSCA,    ContinueWF,     ContinueWF,           RX1 );
  CycleSetMD(   ShutSCA,    ContinueWF,     ContinueWF,           RX2 );
  CycleSetMD(   ShutSCA,             ContinueWF,         ContinueWF,         C8_SO );
  CycleSetMD(   ShutSCA,     ContinueWF,     ContinueWF,         C8_SI );
  CycleSetMD(   ShutSCA,     ContinueWF,         ContinueWF,         C8_C1 );
  CycleSetMD(   ShutSCA,     ContinueWF,         ContinueWF,         C8_C0 );
  CycleSetMD(   ShutSCA,     ContinueWF,      ContinueWF,     C8_CLKOUT );
  CycleSetMD(   ShutSCA,        ContinueWF,     ContinueWF,       C8_BRL2 );
  CycleSetMD(   ShutSCA,        ContinueWF,     ContinueWF,       C8_BRL1 );
  CycleSetMD(   ShutSCA,        ContinueWF,          ContinueWF,        C8_REL );
  CycleSetMD(   ShutSCA,        ContinueWF,      ContinueWF,    C8_SHFTCLK );
  CycleSetMD(   ShutSCA,        ContinueWF,        ContinueWF,      C8_DPOUT );
  CycleSetMD(   ShutSCA,      ContinueWF,       ContinueWF,       C8_TEST );
  CycleSetMD(   ShutSCA,     ContinueWF,      ContinueWF,        nRESET );
  CycleSetMD(   ShutSCA,     OSCIN_singleWF,    OSCIN_singleWF,         OSCIN );
  CycleSetMD(   ShutSCA,     OSCOUT_singleWF,      ContinueWF,         OSCOUT );
  CycleSetMD(   ShutSCA,      ContinueWF,       ContinueWF,      C16_TEST );
  CycleSetMD(   ShutSCA,     ContinueWF,      ContinueWF,      DP_CLKIN );
  CycleSetMD(   ShutSCA,      ContinueWF,       ContinueWF,     C16_DPOUT );
  CycleSetMD(   ShutSCA,      ContinueWF,      ContinueWF,   C16_SHFTCLK );
  CycleSetMD(   ShutSCA,        ContinueWF,         ContinueWF,       C16_REL );
  CycleSetMD(   ShutSCA,     ContinueWF,      ContinueWF,        PORTB );
  CycleSetMD(   ShutSCA,         ContinueWF,      ContinueWF,       PORTC );
  CycleSetMD(   ShutSCA,       ContinueWF,    ContinueWF,       EXTINT2 );
  CycleSetMD(   ShutSCA,       ContinueWF,    ContinueWF,       EXTINT1 );
  CycleSetMD(   ShutSCA,       ContinueWF,    ContinueWF,       EXTINT0 );
  CycleSetMD(   ShutSCA,       ContinueWF,          ContinueWF,        C16_SO );
  CycleSetMD(   ShutSCA,   ContinueWF,    ContinueWF,        C16_SI );
  CycleSetMD(   ShutSCA,        ContinueWF,         ContinueWF,        C16_C1 );
  CycleSetMD(   ShutSCA,        ContinueWF,         ContinueWF,        C16_C0 );
  CycleSetMD(   ShutSCA,       ContinueWF,    ContinueWF,      C16_BRL2 );
  CycleSetMD(   ShutSCA,       ContinueWF,    ContinueWF,      C16_BRL1 );
  CycleSetMD(   ShutSCA,          ContinueWF,      ContinueWF,        CLKOUT );
  CycleSetMD(   ShutSCA,          ContinueWF,      ContinueWF,         TCAP4 );
  CycleSetMD(   ShutSCA,          ContinueWF, ContinueWF,                 TCMP3 );
  CycleSetMD(   ShutSCA,          ContinueWF,      ContinueWF,         TCMP2 );
  CycleSetMD(   ShutSCA,          ContinueWF,     ContinueWF,        SCICLK );
  CycleSetMD(   ShutSCA,          ContinueWF,     ContinueWF,        SCITXD );
  CycleSetMD(   ShutSCA,           ContinueWF,        ContinueWF,           TO4 );
  CycleSetMD(   ShutSCA,           ContinueWF,        ContinueWF,           TO3 );
  CycleSetMD(   ShutSCA,           ContinueWF,        ContinueWF,           TO2 );
  CycleSetMD(   ShutSCA,           ContinueWF,        ContinueWF,           TO1 );
  CycleSetMD(   ShutSCA,          ContinueWF,    ContinueWF,       SPISOMI );
  CycleSetMD(   ShutSCA,          ContinueWF,    ContinueWF,       SPISIMO );
  CycleSetMD(   ShutSCA,          ContinueWF,     ContinueWF,        SPICLK );
  CycleSetMD(   ShutSCA,          ContinueWF,     ContinueWF,        SPISTB );
  CycleSetMD(   ShutSCA,       ContinueWF,        ContinueWF,          DIV2 );
  CycleSetMD(   ShutSCA,       ContinueWF,        ContinueWF,          MUL2 );
  CycleSetMD(   ShutSCA,       ContinueWF,        ContinueWF,         PLLEN );
  CycleSetMD(   ShutSCA,       ContinueWF,        ContinueWF,       C16_VPP );
  CycleSetMD(   ShutSCA,       ContinueWF,        ContinueWF,        C8_VPP );
  CycleSetMD(   ShutSCA,        ContinueWF,         ContinueWF,       CANPINS );



  CycleSetMD(   SCL_0,      TRIG_driveWF,       TRIG_driveWF,       TRIGINS );
  CycleSetMD(   SCL_0,       ADC_driveWF,        ADC_driveWF,           ADC );
  CycleSetMD(   SCL_0,    PORTC_strobeWF,      PORTC_driveWF,         PORTC );
  CycleSetMD(   SCL_0,     GPIO_strobeWF,      Timer_driveWF,         TCAP4 );
  CycleSetMD(   SCL_0,     GPIO_strobeWF,      Timer_driveWF,         TCMP2 );
  CycleSetMD(   SCL_0,     GPIO_strobeWF,     Timer_strobeWF,         TCMP3 );
  CycleSetMD(   SCL_0,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX1 );
  CycleSetMD(   SCL_0,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX2 );
  CycleSetMD(   SCL_0,ScanOut_nextcyc_strobeWF,     PORTA_strobeWF,         C8_SO );
  CycleSetMD(   SCL_0,     PORTA_driveWF,     ScanIn_driveWF,         C8_SI );
  CycleSetMD(   SCL_0,     PORTA_driveWF,         C1_driveWF,         C8_C1 );
  CycleSetMD(   SCL_0,     PORTA_driveWF,         C0_driveWF,         C8_C0 );
  CycleSetMD(   SCL_0,      CLK_strobeWF,      PORTA_driveWF,     C8_CLKOUT );
  CycleSetMD(   SCL_0,   C8BRL2_strobeWF,     C8BRL2_driveWF,       C8_BRL2 );
  CycleSetMD(   SCL_0,   C8BRL1_strobeWF,     C8BRL1_driveWF,       C8_BRL1 );
  CycleSetMD(   SCL_0,    C8REL_strobeWF,     C8REL_strobeWF,        C8_REL );
  CycleSetMD(   SCL_0,C8SHFTCLK_strobeWF, C8SHFTCLK_strobeWF,    C8_SHFTCLK );
  CycleSetMD(   SCL_0,  C8DPOUT_strobeWF,   C8DPOUT_strobeWF,      C8_DPOUT );
  CycleSetMD(   SCL_0,      TEST_driveWF,       TEST_driveWF,       C8_TEST );
  CycleSetMD(   SCL_0,    RESET_strobeWF,      RESET_driveWF,        nRESET );
  CycleSetMD(   SCL_0,              NrWF,     OSCIN_singleWF,         OSCIN );
  CycleSetMD(   SCL_0,   OSCOUT_singleWF,    OSCOUT_strobeWF,        OSCOUT );
  CycleSetMD(   SCL_0,      TEST_driveWF,       TEST_driveWF,      C16_TEST );
  CycleSetMD(   SCL_0,     DPCLK_driveWF,      DPCLK_driveWF,      DP_CLKIN );
  CycleSetMD(   SCL_0, C16DPOUT_strobeWF,  C16DPOUT_strobeWF,     C16_DPOUT );
  CycleSetMD(   SCL_0,C16SHFTCLK_strobeWF, C16SHFTCLK_strobeWF,   C16_SHFTCLK );
  CycleSetMD(   SCL_0,   C16REL_strobeWF,    C16REL_strobeWF,       C16_REL );
  CycleSetMD(   SCL_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B6 );
  CycleSetMD(   SCL_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B5 );
  CycleSetMD(   SCL_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B4 );
  CycleSetMD(   SCL_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B3 );
  CycleSetMD(   SCL_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B2 );
  CycleSetMD(   SCL_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B1 );
  CycleSetMD(   SCL_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B0 );
  CycleSetMD(   SCL_0,  EXTINT2_strobeWF,    EXTINT2_driveWF,       EXTINT2 );
  CycleSetMD(   SCL_0,  EXTINT2_strobeWF,    EXTINT1_driveWF,       EXTINT1 );
  CycleSetMD(   SCL_0,  EXTINT2_strobeWF,    EXTINT0_driveWF,       EXTINT0 );
  CycleSetMD(   SCL_0,ScanOut_nextcyc_strobeWF,     PORTA_strobeWF,        C16_SO );
  CycleSetMD(   SCL_0,     PORTA_driveWF,     ScanIn_driveWF,        C16_SI );
  CycleSetMD(   SCL_0,     PORTA_driveWF,         C1_driveWF,        C16_C1 );
  CycleSetMD(   SCL_0,     PORTA_driveWF,         C0_driveWF,        C16_C0 );
  CycleSetMD(   SCL_0,  C16BRL1_strobeWF,    C16BRL2_driveWF,      C16_BRL2 );
  CycleSetMD(   SCL_0,  C16BRL1_strobeWF,    C16BRL1_driveWF,      C16_BRL1 );
  CycleSetMD(   SCL_0,      CLK_strobeWF,      PORTA_driveWF,        CLKOUT );
  CycleSetMD(   SCL_0,     GPIO_strobeWF,     SCIclk_driveWF,        SCICLK );
  CycleSetMD(   SCL_0,     GPIO_strobeWF,     SCItxd_driveWF,        SCITXD );
  CycleSetMD(   SCL_0,      TO4_strobeWF,        TO4_driveWF,           TO4 );
  CycleSetMD(   SCL_0,      TO3_strobeWF,        TO3_driveWF,           TO3 );
  CycleSetMD(   SCL_0,      TO2_strobeWF,        TO2_driveWF,           TO2 );
  CycleSetMD(   SCL_0,      TO1_strobeWF,        TO1_driveWF,           TO1 );
  CycleSetMD(   SCL_0,     GPIO_strobeWF,    SPIsomi_driveWF,       SPISOMI );
  CycleSetMD(   SCL_0,     GPIO_strobeWF,    SPIsimo_driveWF,       SPISIMO );
  CycleSetMD(   SCL_0,     GPIO_strobeWF,     SPIclk_driveWF,        SPICLK );
  CycleSetMD(   SCL_0,     GPIO_strobeWF,     SPIstb_driveWF,        SPISTB );
  CycleSetMD(   SCL_0,       OSC_driveWF,        OSC_driveWF,          DIV2 );
  CycleSetMD(   SCL_0,       OSC_driveWF,        OSC_driveWF,          MUL2 );
  CycleSetMD(   SCL_0,       PLL_driveWF,       PLL_driveWF,         PLLEN );
  CycleSetMD(   SCL_0,      VPP_strobeWF,        VPP_driveWF,       C16_VPP );
  CycleSetMD(   SCL_0,      VPP_strobeWF,        VPP_driveWF,        C8_VPP );
  CycleSetMD(   SCL_0,             OffWF,              OffWF,       CANPINS );


  CycleSetMD(   SCL_1,      TRIG_driveWF,       TRIG_driveWF,       TRIGINS );
  CycleSetMD(   SCL_1,       ADC_driveWF,        ADC_driveWF,           ADC );
  CycleSetMD(   SCL_1,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX1 );
  CycleSetMD(   SCL_1,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX2 );
  CycleSetMD(   SCL_1,ScanOut_nextcyc_strobeWF, ScanOut_nextcyc_strobeWF,         C8_SO );
  CycleSetMD(   SCL_1,    ScanIn_driveWF,     ScanIn_driveWF,         C8_SI );
  CycleSetMD(   SCL_1,        C1_driveWF,         C1_driveWF,         C8_C1 );
  CycleSetMD(   SCL_1,        C0_driveWF,         C0_driveWF,         C8_C0 );
  CycleSetMD(   SCL_1,      CLK_strobeWF,       CLK_strobeWF,     C8_CLKOUT );
  CycleSetMD(   SCL_1,   C8BRL2_strobeWF,    C8BRL2_strobeWF,       C8_BRL2 );
  CycleSetMD(   SCL_1,   C8BRL1_strobeWF,    C8BRL1_strobeWF,       C8_BRL1 );
  CycleSetMD(   SCL_1,    C8REL_strobeWF,     C8REL_strobeWF,        C8_REL );
  CycleSetMD(   SCL_1,C8SHFTCLK_strobeWF, C8SHFTCLK_strobeWF,    C8_SHFTCLK );
  CycleSetMD(   SCL_1,  C8DPOUT_strobeWF,   C8DPOUT_strobeWF,      C8_DPOUT );
  CycleSetMD(   SCL_1,      TEST_driveWF,       TEST_driveWF,       C8_TEST );
  CycleSetMD(   SCL_1,    RESET_strobeWF,      RESET_driveWF,        nRESET );
  CycleSetMD(   SCL_1,    OSCIN_singleWF,     OSCIN_singleWF,         OSCIN );
  CycleSetMD(   SCL_1,   OSCOUT_singleWF,    OSCOUT_strobeWF,        OSCOUT );
  CycleSetMD(   SCL_1,      TEST_driveWF,       TEST_driveWF,      C16_TEST );
  CycleSetMD(   SCL_1,     DPCLK_driveWF,      DPCLK_driveWF,      DP_CLKIN );
  CycleSetMD(   SCL_1, C16DPOUT_strobeWF,  C16DPOUT_strobeWF,     C16_DPOUT );
  CycleSetMD(   SCL_1,C16SHFTCLK_strobeWF, C16SHFTCLK_strobeWF,   C16_SHFTCLK );
  CycleSetMD(   SCL_1,   C16REL_strobeWF,    C16REL_strobeWF,       C16_REL );
  CycleSetMD(   SCL_1,    PORTB_strobeWF,      PORTB_driveWF,        C16_B6 );
  CycleSetMD(   SCL_1,    PORTB_strobeWF,      PORTB_driveWF,        C16_B5 );
  CycleSetMD(   SCL_1,    PORTB_strobeWF,      PORTB_driveWF,        C16_B4 );
  CycleSetMD(   SCL_1,    PORTB_strobeWF,      PORTB_driveWF,        C16_B3 );
  CycleSetMD(   SCL_1,    PORTB_strobeWF,      PORTB_driveWF,        C16_B2 );
  CycleSetMD(   SCL_1,    PORTB_strobeWF,      PORTB_driveWF,        C16_B1 );
  CycleSetMD(   SCL_1,    PORTB_strobeWF,      PORTB_driveWF,        C16_B0 );
  CycleSetMD(   SCL_1,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_6 );
  CycleSetMD(   SCL_1,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_5 );
  CycleSetMD(   SCL_1,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_4 );
  CycleSetMD(   SCL_1,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_3 );
  CycleSetMD(   SCL_1,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_2 );
  CycleSetMD(   SCL_1,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_1 );
  CycleSetMD(   SCL_1,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_0 );
  CycleSetMD(   SCL_1,  EXTINT2_strobeWF,    EXTINT2_driveWF,       EXTINT2 );
  CycleSetMD(   SCL_1,  EXTINT1_strobeWF,    EXTINT1_driveWF,       EXTINT1 );
  CycleSetMD(   SCL_1,  EXTINT0_strobeWF,    EXTINT0_driveWF,       EXTINT0 );
  CycleSetMD(   SCL_1,ScanOut_nextcyc_strobeWF,     PORTA_strobeWF,        C16_SO );
  CycleSetMD(   SCL_1,    PORTA_strobeWF,     ScanIn_driveWF,        C16_SI );
  CycleSetMD(   SCL_1,    PORTA_strobeWF,         C1_driveWF,        C16_C1 );
  CycleSetMD(   SCL_1,    PORTA_strobeWF,         C0_driveWF,        C16_C0 );
  CycleSetMD(   SCL_1,  C16BRL2_strobeWF,    C16BRL2_driveWF,      C16_BRL2 );
  CycleSetMD(   SCL_1,  C16BRL1_strobeWF,    C16BRL1_driveWF,      C16_BRL1 );
  CycleSetMD(   SCL_1,      CLK_strobeWF,       CLK_strobeWF,        CLKOUT );
  CycleSetMD(   SCL_1,    Timer_strobeWF,      Timer_driveWF,         TCAP4 );
  CycleSetMD(   SCL_1,    Timer_strobeWF,     Timer_strobeWF,         TCMP3 );
  CycleSetMD(   SCL_1,    Timer_strobeWF,      Timer_driveWF,         TCMP2 );
  CycleSetMD(   SCL_1,   SCIclk_strobeWF,     SCIclk_driveWF,        SCICLK );
  CycleSetMD(   SCL_1,   SCItxd_strobeWF,     SCItxd_driveWF,        SCITXD );
  CycleSetMD(   SCL_1,       TO4_driveWF,        TO4_driveWF,           TO4 );
  CycleSetMD(   SCL_1,       TO3_driveWF,        TO3_driveWF,           TO3 );
  CycleSetMD(   SCL_1,       TO2_driveWF,        TO2_driveWF,           TO2 );
  CycleSetMD(   SCL_1,       TO1_driveWF,        TO1_driveWF,           TO1 );
  CycleSetMD(   SCL_1,  SPIsomi_strobeWF,    SPIsomi_driveWF,       SPISOMI );
  CycleSetMD(   SCL_1,  SPIsimo_strobeWF,    SPIsimo_driveWF,       SPISIMO );
  CycleSetMD(   SCL_1,   SPIclk_strobeWF,     SPIclk_driveWF,        SPICLK );
  CycleSetMD(   SCL_1,   SPIstb_strobeWF,     SPIstb_driveWF,        SPISTB );
  CycleSetMD(   SCL_1,       OSC_driveWF,        OSC_driveWF,          DIV2 );
  CycleSetMD(   SCL_1,       OSC_driveWF,        OSC_driveWF,          MUL2 );
  CycleSetMD(   SCL_1,       PLL_driveWF,        PLL_driveWF,         PLLEN );
  CycleSetMD(   SCL_1,       VPP_driveWF,        VPP_driveWF,       C16_VPP );
  CycleSetMD(   SCL_1,       VPP_driveWF,        VPP_driveWF,        C8_VPP );
  CycleSetMD(   SCL_1,             OffWF,              OffWF,       CANPINS );


  CycleSetMD(   SCL_2,      TRIG_driveWF,       TRIG_driveWF,       TRIGINS );
  CycleSetMD(   SCL_2,       ADC_driveWF,        ADC_driveWF,           ADC );
  CycleSetMD(   SCL_2,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX1 );
  CycleSetMD(   SCL_2,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX2 );
  CycleSetMD(   SCL_2,ScanOut_nextcyc_strobeWF,     PORTA_strobeWF,         C8_SO );
  CycleSetMD(   SCL_2,    PORTA_strobeWF,     ScanIn_driveWF,         C8_SI );
  CycleSetMD(   SCL_2,    PORTA_strobeWF,         C1_driveWF,         C8_C1 );
  CycleSetMD(   SCL_2,    PORTA_strobeWF,         C0_driveWF,         C8_C0 );
  CycleSetMD(   SCL_2,      CLK_strobeWF,       CLK_strobeWF,     C8_CLKOUT );
  CycleSetMD(   SCL_2,   C8BRL2_strobeWF,     C8BRL2_driveWF,       C8_BRL2 );
  CycleSetMD(   SCL_2,   C8BRL1_strobeWF,     C8BRL1_driveWF,       C8_BRL1 );
  CycleSetMD(   SCL_2,    C8REL_strobeWF,     C8REL_strobeWF,        C8_REL );
  CycleSetMD(   SCL_2,C8SHFTCLK_strobeWF, C8SHFTCLK_strobeWF,    C8_SHFTCLK );
  CycleSetMD(   SCL_2,  C8DPOUT_strobeWF,   C8DPOUT_strobeWF,      C8_DPOUT );
  CycleSetMD(   SCL_2,      TEST_driveWF,       TEST_driveWF,       C8_TEST );
  CycleSetMD(   SCL_2,    RESET_strobeWF,      RESET_driveWF,        nRESET );
  CycleSetMD(   SCL_2,    OSCIN_singleWF,     OSCIN_singleWF,         OSCIN );
  CycleSetMD(   SCL_2,   OSCOUT_singleWF,    OSCOUT_strobeWF,        OSCOUT );
  CycleSetMD(   SCL_2,      TEST_driveWF,       TEST_driveWF,      C16_TEST );
  CycleSetMD(   SCL_2,     DPCLK_driveWF,      DPCLK_driveWF,      DP_CLKIN );
  CycleSetMD(   SCL_2, C16DPOUT_strobeWF,  C16DPOUT_strobeWF,     C16_DPOUT );
  CycleSetMD(   SCL_2,C16SHFTCLK_strobeWF, C16SHFTCLK_strobeWF,   C16_SHFTCLK );
  CycleSetMD(   SCL_2,   C16REL_strobeWF,    C16REL_strobeWF,       C16_REL );
  CycleSetMD(   SCL_2,    PORTB_strobeWF,     PORTB_strobeWF,        C16_B6 );
  CycleSetMD(   SCL_2,    PORTB_strobeWF,     PORTB_strobeWF,        C16_B5 );
  CycleSetMD(   SCL_2,    PORTB_strobeWF,     PORTB_strobeWF,        C16_B4 );
  CycleSetMD(   SCL_2,    PORTB_strobeWF,     PORTB_strobeWF,        C16_B3 );
  CycleSetMD(   SCL_2,    PORTB_strobeWF,     PORTB_strobeWF,        C16_B2 );
  CycleSetMD(   SCL_2,    PORTB_strobeWF,     PORTB_strobeWF,        C16_B1 );
  CycleSetMD(   SCL_2,    PORTB_strobeWF,     PORTB_strobeWF,        C16_B0 );
  CycleSetMD(   SCL_2,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_6 );
  CycleSetMD(   SCL_2,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_5 );
  CycleSetMD(   SCL_2,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_4 );
  CycleSetMD(   SCL_2,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_3 );
  CycleSetMD(   SCL_2,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_2 );
  CycleSetMD(   SCL_2,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_1 );
  CycleSetMD(   SCL_2,    PORTC_strobeWF,      PORTC_driveWF,       C16_C_0 );
  CycleSetMD(   SCL_2,  EXTINT2_strobeWF,    EXTINT2_driveWF,       EXTINT2 );
  CycleSetMD(   SCL_2,  EXTINT1_strobeWF,   EXTINT1_strobeWF,       EXTINT1 );
  CycleSetMD(   SCL_2,  EXTINT0_strobeWF,   EXTINT0_strobeWF,       EXTINT0 );
  CycleSetMD(   SCL_2,ScanOut_nextcyc_strobeWF,      PORTA_driveWF,        C16_SO );
  CycleSetMD(   SCL_2,    ScanIn_driveWF,     ScanIn_driveWF,        C16_SI );
  CycleSetMD(   SCL_2,        C1_driveWF,         C1_driveWF,        C16_C1 );
  CycleSetMD(   SCL_2,        C0_driveWF,         C0_driveWF,        C16_C0 );
  CycleSetMD(   SCL_2,  C16BRL2_strobeWF,   C16BRL2_strobeWF,      C16_BRL2 );
  CycleSetMD(   SCL_2,  C16BRL1_strobeWF,   C16BRL1_strobeWF,      C16_BRL1 );
  CycleSetMD(   SCL_2,      CLK_strobeWF,      PORTA_driveWF,        CLKOUT );
  CycleSetMD(   SCL_2,    Timer_strobeWF,     Timer_strobeWF,         TCAP4 );
  CycleSetMD(   SCL_2,    Timer_strobeWF,     Timer_strobeWF,         TCMP3 );
  CycleSetMD(   SCL_2,    Timer_strobeWF,      Timer_driveWF,         TCMP2 );
  CycleSetMD(   SCL_2,   SCIclk_strobeWF,     SCIclk_driveWF,        SCICLK );
  CycleSetMD(   SCL_2,   SCItxd_strobeWF,     SCItxd_driveWF,        SCITXD );
  CycleSetMD(   SCL_2,      TO4_strobeWF,        TO4_driveWF,           TO4 );
  CycleSetMD(   SCL_2,      TO3_strobeWF,        TO3_driveWF,           TO3 );
  CycleSetMD(   SCL_2,      TO2_strobeWF,        TO2_driveWF,           TO2 );
  CycleSetMD(   SCL_2,      TO1_strobeWF,        TO1_driveWF,           TO1 );
  CycleSetMD(   SCL_2,  SPIsomi_strobeWF,    SPIsomi_driveWF,       SPISOMI );
  CycleSetMD(   SCL_2,  SPIsimo_strobeWF,    SPIsimo_driveWF,       SPISIMO );
  CycleSetMD(   SCL_2,   SPIclk_strobeWF,     SPIclk_driveWF,        SPICLK );
  CycleSetMD(   SCL_2,   SPIstb_strobeWF,     SPIstb_driveWF,        SPISTB );
  CycleSetMD(   SCL_2,       OSC_driveWF,        OSC_driveWF,          DIV2 );
  CycleSetMD(   SCL_2,       OSC_driveWF,        OSC_driveWF,          MUL2 );
  CycleSetMD(   SCL_2,       PLL_driveWF,        PLL_driveWF,         PLLEN );
  CycleSetMD(   SCL_2,       VPP_driveWF,        VPP_driveWF,       C16_VPP );
  CycleSetMD(   SCL_2,       VPP_driveWF,        VPP_driveWF,        C8_VPP );
  CycleSetMD(   SCL_2,             OffWF,              OffWF,       CANPINS );

  CycleSetMD(   SCL_3,      TRIG_driveWF,       TRIG_driveWF,       TRIGINS );
  CycleSetMD(   SCL_3,       ADC_driveWF,        ADC_driveWF,           ADC );
  CycleSetMD(   SCL_3,  EXTINT2_strobeWF,   EXTINT2_strobeWF,     Interrupt );
  CycleSetMD(   SCL_3,    PORTC_strobeWF,     PORTC_strobeWF,         PORTC );
  CycleSetMD(   SCL_3,    PORTB_strobeWF,     PORTB_strobeWF,         PORTB );
  CycleSetMD(   SCL_3,     GPIO_strobeWF,      GPIO_strobeWF,     Timer_C16 );
  CycleSetMD(   SCL_3,     GPIO_strobeWF,      GPIO_strobeWF,           SPI );
  CycleSetMD(   SCL_3,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX1 );
  CycleSetMD(   SCL_3,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX2 );
  CycleSetMD(   SCL_3,     PORTA_driveWF,      PORTA_driveWF,         C8_SO );
  CycleSetMD(   SCL_3,    PORTA_strobeWF,     ScanIn_driveWF,         C8_SI );
  CycleSetMD(   SCL_3,    PORTA_strobeWF,         C1_driveWF,         C8_C1 );
  CycleSetMD(   SCL_3,    PORTA_strobeWF,         C0_driveWF,         C8_C0 );
  CycleSetMD(   SCL_3,     PORTA_driveWF,      PORTA_driveWF,     C8_CLKOUT );
  CycleSetMD(   SCL_3,   C8BRL2_strobeWF,     C8BRL2_driveWF,       C8_BRL2 );
  CycleSetMD(   SCL_3,   C8BRL1_strobeWF,     C8BRL1_driveWF,       C8_BRL1 );
  CycleSetMD(   SCL_3,    C8REL_strobeWF,     C8REL_strobeWF,        C8_REL );
  CycleSetMD(   SCL_3,C8SHFTCLK_strobeWF, C8SHFTCLK_strobeWF,    C8_SHFTCLK );
  CycleSetMD(   SCL_3,  C8DPOUT_strobeWF,   C8DPOUT_strobeWF,      C8_DPOUT );
  CycleSetMD(   SCL_3,      TEST_driveWF,       TEST_driveWF,       C8_TEST );
  CycleSetMD(   SCL_3,    RESET_strobeWF,      RESET_driveWF,        nRESET );
  CycleSetMD(   SCL_3,    OSCIN_singleWF,     OSCIN_singleWF,         OSCIN );
  CycleSetMD(   SCL_3,   OSCOUT_singleWF,    OSCOUT_strobeWF,        OSCOUT );
  CycleSetMD(   SCL_3,      TEST_driveWF,       TEST_driveWF,      C16_TEST );
  CycleSetMD(   SCL_3,     DPCLK_driveWF,      DPCLK_driveWF,      DP_CLKIN );
  CycleSetMD(   SCL_3, C16DPOUT_strobeWF,  C16DPOUT_strobeWF,     C16_DPOUT );
  CycleSetMD(   SCL_3,C16SHFTCLK_strobeWF, C16SHFTCLK_strobeWF,   C16_SHFTCLK );
  CycleSetMD(   SCL_3,   C16REL_strobeWF,    C16REL_strobeWF,       C16_REL );
  CycleSetMD(   SCL_3,ScanOut_nextcyc_strobeWF, ScanOut_nextcyc_strobeWF,        C16_SO );
  CycleSetMD(   SCL_3,    ScanIn_driveWF,     ScanIn_driveWF,        C16_SI );
  CycleSetMD(   SCL_3,        C1_driveWF,         C1_driveWF,        C16_C1 );
  CycleSetMD(   SCL_3,        C0_driveWF,         C0_driveWF,        C16_C0 );
  CycleSetMD(   SCL_3,  C16BRL1_strobeWF,   C16BRL1_strobeWF,      C16_BRL2 );
  CycleSetMD(   SCL_3,  C16BRL1_strobeWF,   C16BRL1_strobeWF,      C16_BRL1 );
  CycleSetMD(   SCL_3,      CLK_strobeWF,       CLK_strobeWF,        CLKOUT );
  CycleSetMD(   SCL_3,     GPIO_strobeWF,      GPIO_strobeWF,        SCICLK );
  CycleSetMD(   SCL_3,     GPIO_strobeWF,      GPIO_strobeWF,        SCITXD );
  CycleSetMD(   SCL_3,      TO4_strobeWF,       TO4_strobeWF,           TO4 );
  CycleSetMD(   SCL_3,      TO3_strobeWF,       TO3_strobeWF,           TO3 );
  CycleSetMD(   SCL_3,      TO2_strobeWF,       TO2_strobeWF,           TO2 );
  CycleSetMD(   SCL_3,      TO1_strobeWF,       TO1_strobeWF,           TO1 );
  CycleSetMD(   SCL_3,       OSC_driveWF,        OSC_driveWF,          DIV2 );
  CycleSetMD(   SCL_3,       OSC_driveWF,        OSC_driveWF,          MUL2 );
  CycleSetMD(   SCL_3,       PLL_driveWF,        PLL_driveWF,         PLLEN );
  CycleSetMD(   SCL_3,       VPP_driveWF,        VPP_driveWF,       C16_VPP );
  CycleSetMD(   SCL_3,       VPP_driveWF,        VPP_driveWF,        C8_VPP );
  CycleSetMD(   SCL_3,             OffWF,              OffWF,       CANPINS );


  CycleSetMD(   SCLHALT,       ADC_driveWF,        ADC_driveWF,           ADC );
  CycleSetMD(   SCLHALT,      TRIG_driveWF,       TRIG_driveWF,       TRIGINS );
  CycleSetMD(   SCLHALT,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX1 );
  CycleSetMD(   SCLHALT,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX2 );
  CycleSetMD(   SCLHALT,ScanOut_nextcyc_strobeWF,     PORTA_driveWF,         C8_SO );
  CycleSetMD(   SCLHALT,     PORTA_driveWF,     ScanIn_driveWF,         C8_SI );
  CycleSetMD(   SCLHALT,     PORTA_driveWF,         C1_driveWF,         C8_C1 );
  CycleSetMD(   SCLHALT,     PORTA_driveWF,         C0_driveWF,         C8_C0 );
  CycleSetMD(   SCLHALT,     PORTA_driveWF,      PORTA_driveWF,     C8_CLKOUT );
  CycleSetMD(   SCLHALT,   C8BRL2_strobeWF,     C8BRL2_driveWF,       C8_BRL2 );
  CycleSetMD(   SCLHALT,   C8BRL1_strobeWF,     C8BRL1_driveWF,       C8_BRL1 );
  CycleSetMD(   SCLHALT,    C8REL_strobeWF,     C8REL_strobeWF,        C8_REL );
  CycleSetMD(   SCLHALT,C8SHFTCLK_strobeWF, C8SHFTCLK_strobeWF,    C8_SHFTCLK );
  CycleSetMD(   SCLHALT,  C8DPOUT_strobeWF,   C8DPOUT_strobeWF,      C8_DPOUT );
  CycleSetMD(   SCLHALT,      TEST_driveWF,       TEST_driveWF,       C8_TEST );
  CycleSetMD(   SCLHALT,    RESET_strobeWF,      RESET_driveWF,        nRESET );
  CycleSetMD(   SCLHALT,      GPIO_driveWF,    OSCIN_singleWF,         OSCIN );
  CycleSetMD(   SCLHALT,   OSCOUT_strobeWF,    OSCOUT_strobeWF,        OSCOUT );
  CycleSetMD(   SCLHALT,      TEST_driveWF,       TEST_driveWF,      C16_TEST );
  CycleSetMD(   SCLHALT,     DPCLK_driveWF,      DPCLK_driveWF,      DP_CLKIN );
  CycleSetMD(   SCLHALT, C16DPOUT_strobeWF,  C16DPOUT_strobeWF,     C16_DPOUT );
  CycleSetMD(   SCLHALT,C16SHFTCLK_strobeWF, C16SHFTCLK_strobeWF,   C16_SHFTCLK );
  CycleSetMD(   SCLHALT,   C16REL_strobeWF,    C16REL_strobeWF,       C16_REL );
  CycleSetMD(   SCLHALT,     PORTB_driveWF,      PORTB_driveWF,       PORTB );
  CycleSetMD(   SCLHALT,    PORTC_strobeWF,      PORTC_driveWF,       PORTC );
  CycleSetMD(   SCLHALT,  EXTINT2_strobeWF,    EXTINT2_driveWF,       EXTINT2 );
  CycleSetMD(   SCLHALT,  EXTINT2_strobeWF,    EXTINT1_driveWF,       EXTINT1 );
  CycleSetMD(   SCLHALT,  EXTINT2_strobeWF,    EXTINT0_driveWF,       EXTINT0 );
  CycleSetMD(   SCLHALT,ScanOut_nextcyc_strobeWF, PORTA_driveWF,       C16_SO );
  CycleSetMD(   SCLHALT,    ScanIn_driveWF,     ScanIn_driveWF,        C16_SI );
  CycleSetMD(   SCLHALT,        C1_driveWF,         C1_driveWF,        C16_C1 );
  CycleSetMD(   SCLHALT,        C0_driveWF,         C0_driveWF,        C16_C0 );
  CycleSetMD(   SCLHALT,  C16BRL1_strobeWF,    C16BRL2_driveWF,      C16_BRL2 );
  CycleSetMD(   SCLHALT,  C16BRL1_strobeWF,    C16BRL1_driveWF,      C16_BRL1 );
  CycleSetMD(   SCLHALT,     PORTA_driveWF,      PORTA_driveWF,        CLKOUT );
  CycleSetMD(   SCLHALT,     GPIO_strobeWF,      Timer_driveWF,         TCAP4 );
  CycleSetMD(   SCLHALT,     GPIO_strobeWF,     Timer_strobeWF,         TCMP3 );
  CycleSetMD(   SCLHALT,     GPIO_strobeWF,      Timer_driveWF,         TCMP2 );
  CycleSetMD(   SCLHALT,     GPIO_strobeWF,     SCIclk_driveWF,        SCICLK );
  CycleSetMD(   SCLHALT,     GPIO_strobeWF,     SCItxd_driveWF,        SCITXD );
  CycleSetMD(   SCLHALT,      TO4_strobeWF,        TO4_driveWF,           TO4 );
  CycleSetMD(   SCLHALT,      TO3_strobeWF,        TO3_driveWF,           TO3 );
  CycleSetMD(   SCLHALT,      TO2_strobeWF,        TO2_driveWF,           TO2 );
  CycleSetMD(   SCLHALT,      TO1_strobeWF,        TO1_driveWF,           TO1 );
  CycleSetMD(   SCLHALT,     GPIO_strobeWF,    SPIsomi_driveWF,       SPISOMI );
  CycleSetMD(   SCLHALT,     GPIO_strobeWF,    SPIsimo_driveWF,       SPISIMO );
  CycleSetMD(   SCLHALT,     GPIO_strobeWF,     SPIclk_driveWF,        SPICLK );
  CycleSetMD(   SCLHALT,     GPIO_strobeWF,     SPIstb_driveWF,        SPISTB );
  CycleSetMD(   SCLHALT,       OSC_driveWF,        OSC_driveWF,          DIV2 );
  CycleSetMD(   SCLHALT,       OSC_driveWF,        OSC_driveWF,          MUL2 );
  CycleSetMD(   SCLHALT,       PLL_driveWF,        PLL_driveWF,         PLLEN );
  CycleSetMD(   SCLHALT,      VPP_strobeWF,        VPP_driveWF,       C16_VPP );
  CycleSetMD(   SCLHALT,      VPP_strobeWF,        VPP_driveWF,        C8_VPP );
  CycleSetMD(   SCLHALT,       CAN_driveWF,        CAN_driveWF,         RXCAN );
  CycleSetMD(   SCLHALT,             OffWF,              OffWF,         TXCAN );

  CycleSetMD(   CAN_0,      TRIG_driveWF,       TRIG_driveWF,       TRIGINS );
  CycleSetMD(   CAN_0,       ADC_driveWF,        ADC_driveWF,           ADC );
  CycleSetMD(   CAN_0,    PORTC_strobeWF,      PORTC_driveWF,         PORTC );
  CycleSetMD(   CAN_0,     GPIO_strobeWF,      Timer_driveWF,         TCAP4 );
  CycleSetMD(   CAN_0,     GPIO_strobeWF,      Timer_driveWF,         TCMP2 );
  CycleSetMD(   CAN_0,     GPIO_strobeWF,     Timer_strobeWF,         TCMP3 );
  CycleSetMD(   CAN_0,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX1 );
  CycleSetMD(   CAN_0,    SCIrxd_driveWF,     SCIrxd_driveWF,           RX2 );
  CycleSetMD(   CAN_0,ScanOut_nextcyc_strobeWF, ScanOut_nextcyc_strobeWF,         C8_SO );
  CycleSetMD(   CAN_0,    ScanIn_driveWF,     ScanIn_driveWF,         C8_SI );
  CycleSetMD(   CAN_0,        C1_driveWF,         C1_driveWF,         C8_C1 );
  CycleSetMD(   CAN_0,        C0_driveWF,         C0_driveWF,         C8_C0 );
  CycleSetMD(   CAN_0,      CLK_strobeWF,       CLK_strobeWF,     C8_CLKOUT );
  CycleSetMD(   CAN_0,   C8BRL2_strobeWF,    C8BRL2_driveWF,       C8_BRL2 );
  CycleSetMD(   CAN_0,   C8BRL1_strobeWF,    C8BRL1_driveWF,       C8_BRL1 );
  CycleSetMD(   CAN_0,    C8REL_strobeWF,     C8REL_strobeWF,        C8_REL );
  CycleSetMD(   CAN_0,C8SHFTCLK_strobeWF, C8SHFTCLK_strobeWF,    C8_SHFTCLK );
  CycleSetMD(   CAN_0,  C8DPOUT_strobeWF,   C8DPOUT_strobeWF,      C8_DPOUT );
  CycleSetMD(   CAN_0,      TEST_driveWF,       TEST_driveWF,       C8_TEST );
  CycleSetMD(   CAN_0,    RESET_strobeWF,      RESET_driveWF,        nRESET );
  CycleSetMD(   CAN_0,    OSCIN_singleWF,     OSCIN_singleWF,         OSCIN );
  CycleSetMD(   CAN_0,   OSCOUT_singleWF,    OSCOUT_strobeWF,        OSCOUT );
  CycleSetMD(   CAN_0,      TEST_driveWF,       TEST_driveWF,      C16_TEST );
  CycleSetMD(   CAN_0,     DPCLK_driveWF,      DPCLK_driveWF,      DP_CLKIN );
  CycleSetMD(   CAN_0, C16DPOUT_strobeWF,  C16DPOUT_strobeWF,     C16_DPOUT );
  CycleSetMD(   CAN_0,C16SHFTCLK_strobeWF, C16SHFTCLK_strobeWF,   C16_SHFTCLK );
  CycleSetMD(   CAN_0,   C16REL_strobeWF,    C16REL_strobeWF,       C16_REL );
  CycleSetMD(   CAN_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B6 );
  CycleSetMD(   CAN_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B5 );
  CycleSetMD(   CAN_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B4 );
  CycleSetMD(   CAN_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B3 );
  CycleSetMD(   CAN_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B2 );
  CycleSetMD(   CAN_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B1 );
  CycleSetMD(   CAN_0,    PORTB_strobeWF,      PORTB_driveWF,        C16_B0 );
  CycleSetMD(   CAN_0,  EXTINT2_strobeWF,    EXTINT2_driveWF,       EXTINT2 );
  CycleSetMD(   CAN_0,  EXTINT2_strobeWF,    EXTINT1_driveWF,       EXTINT1 );
  CycleSetMD(   CAN_0,  EXTINT2_strobeWF,    EXTINT0_driveWF,       EXTINT0 );
  CycleSetMD(   CAN_0,ScanOut_nextcyc_strobeWF, ScanOut_nextcyc_strobeWF,        C16_SO );
  CycleSetMD(   CAN_0,    ScanIn_driveWF,     ScanIn_driveWF,        C16_SI );
  CycleSetMD(   CAN_0,        C1_driveWF,         C1_driveWF,        C16_C1 );
  CycleSetMD(   CAN_0,        C0_driveWF,         C0_driveWF,        C16_C0 );
  CycleSetMD(   CAN_0,  C16BRL1_strobeWF,    C16BRL2_driveWF,      C16_BRL2 );
  CycleSetMD(   CAN_0,  C16BRL1_strobeWF,    C16BRL1_driveWF,      C16_BRL1 );
  CycleSetMD(   CAN_0,      CLK_strobeWF,       CLK_strobeWF,        CLKOUT );
  CycleSetMD(   CAN_0,     GPIO_strobeWF,     SCIclk_driveWF,        SCICLK );
  CycleSetMD(   CAN_0,     GPIO_strobeWF,     SCItxd_driveWF,        SCITXD );
  CycleSetMD(   CAN_0,      TO4_strobeWF,        TO4_driveWF,           TO4 );
  CycleSetMD(   CAN_0,      TO3_strobeWF,        TO3_driveWF,           TO3 );
  CycleSetMD(   CAN_0,      TO2_strobeWF,        TO2_driveWF,           TO2 );
  CycleSetMD(   CAN_0,      TO1_strobeWF,        TO1_driveWF,           TO1 );
  CycleSetMD(   CAN_0,     GPIO_strobeWF,    SPIsomi_driveWF,       SPISOMI );
  CycleSetMD(   CAN_0,     GPIO_strobeWF,    SPIsimo_driveWF,       SPISIMO );
  CycleSetMD(   CAN_0,     GPIO_strobeWF,     SPIclk_driveWF,        SPICLK );
  CycleSetMD(   CAN_0,     GPIO_strobeWF,     SPIstb_driveWF,        SPISTB );
  CycleSetMD(   CAN_0,       OSC_driveWF,        OSC_driveWF,          DIV2 );
  CycleSetMD(   CAN_0,       OSC_driveWF,        OSC_driveWF,          MUL2 );
  CycleSetMD(   CAN_0,       PLL_driveWF,        PLL_driveWF,         PLLEN );
  CycleSetMD(   CAN_0,       VPP_driveWF,        VPP_driveWF,       C16_VPP );
  CycleSetMD(   CAN_0,       VPP_driveWF,        VPP_driveWF,        C8_VPP );
  CycleSetMD(   CAN_0,       CAN_driveWF,        CAN_driveWF,         RXCAN );
  CycleSetMD(   CAN_0,      CAN_strobeWF,       CAN_strobeWF,         TXCAN );

  CycleSetMD(   MATCH_0,     ContinueWF,       ContinueWF,       TRIGINS );
  CycleSetMD(   MATCH_0,     ContinueWF,       ContinueWF,           ADC );
  CycleSetMD(   MATCH_0,    ContinueWF,     ContinueWF,           RX1 );
  CycleSetMD(   MATCH_0,    ContinueWF,     ContinueWF,           RX2 );
  CycleSetMD(   MATCH_0,    ContinueWF,       ContinueWF,     C8_CLKOUT );
  CycleSetMD(   MATCH_0,   ContinueWF,    ContinueWF,       C8_BRL2 );
  CycleSetMD(   MATCH_0,   ContinueWF,    ContinueWF,       C8_BRL1 );
  CycleSetMD(   MATCH_0,    ContinueWF,     ContinueWF,        C8_REL );
  CycleSetMD(   MATCH_0,  ContinueWF,        ContinueWF,    MAILBOX );
  CycleSetMD(   MATCH_0,   ContinueWF,       ContinueWF,       C8_TEST );
  CycleSetMD(   MATCH_0,     ContinueWF,      ContinueWF,        nRESET );
  CycleSetMD(   MATCH_0,    OSCIN_singleWF,     OSCIN_singleWF,         OSCIN );
  CycleSetMD(   MATCH_0,   OSCOUT_singleWF,    ContinueWF,        OSCOUT );
  CycleSetMD(   MATCH_0,      ContinueWF,       ContinueWF,      C16_TEST );
  CycleSetMD(   MATCH_0,  ContinueWF,    ContinueWF,       C16_REL );
  CycleSetMD(   MATCH_0,  ContinueWF,     ContinueWF,       PORTB );
  CycleSetMD(   MATCH_0,  ContinueWF,     ContinueWF,       PORTC );
  CycleSetMD(   MATCH_0,  ContinueWF,    ContinueWF,       Interrupt );
  CycleSetMD(   MATCH_0,  ContinueWF,     ContinueWF,            TAP );
  CycleSetMD(   MATCH_0,  ContinueWF,    ContinueWF,      C16_BRL2 );
  CycleSetMD(   MATCH_0,  ContinueWF,    ContinueWF,      C16_BRL1 );
  CycleSetMD(   MATCH_0,      CLK_matchWF,       CLK_strobeWF,        CLKOUT );
  CycleSetMD(   MATCH_0,   ContinueWF,      ContinueWF,      Timer_C16 );
  CycleSetMD(   MATCH_0,   ContinueWF,     ContinueWF,        SCI);
  CycleSetMD(   MATCH_0,  ContinueWF,        ContinueWF,      TRIGOUTS );
  CycleSetMD(   MATCH_0,  ContinueWF,    ContinueWF,       SPI );
  CycleSetMD(   MATCH_0,       ContinueWF,        ContinueWF,          DIV2 );
  CycleSetMD(   MATCH_0,       ContinueWF,        ContinueWF,          MUL2 );
  CycleSetMD(   MATCH_0,       ContinueWF,        ContinueWF,         PLLEN );
  CycleSetMD(   MATCH_0,       ContinueWF,        ContinueWF,       C16_VPP );
  CycleSetMD(   MATCH_0,       ContinueWF,        ContinueWF,        C8_VPP );
  CycleSetMD(   MATCH_0,       ContinueWF,          ContinueWF,       CANPINS );

  CycleSetMD(   MATCH_SWP,      ContinueWF,         ContinueWF,   SWPMatchPins);
  CycleSetMD(   MATCH_SWP,      SO_matchWF,         ContinueWF,          C8_SO);
  CycleSetMD(   MATCH_SWP,      SO_matchWF,         ContinueWF,         C16_SO);
  CycleSetMD(   MATCH_SWP,   OSCIN_singleWF,    OSCIN_singleWF,         OSCIN );

 
    
    
    
    
    

    VectorMapSet (     TVVectorMap,  1,            Rst_Clk , Binary );
    VectorMapSet (     TVVectorMap,  2,                TAP , Binary );
    VectorMapSet (     TVVectorMap,  3,           ModeTest , Binary );
    VectorMapSet (     TVVectorMap,  4,                SCI , Binary );
    VectorMapSet (     TVVectorMap,  5,                SPI , Binary );
    VectorMapSet (     TVVectorMap,  6,          Timer_C16 , Binary );
    VectorMapSet (     TVVectorMap,  7,              PORTB , Binary );
    VectorMapSet (     TVVectorMap,  8,              PORTC , Binary );
    VectorMapSet (     TVVectorMap,  9,                BRL , Binary );
    VectorMapSet (     TVVectorMap, 10,          Interrupt , Binary );
    VectorMapSet (     TVVectorMap, 11,            MAILBOX , Binary );
    VectorMapSet (     TVVectorMap, 12,                ADC , Binary );
    VectorMapSet (     TVVectorMap, 13,            TRIGGER , Binary );
    VectorMapSet (     TVVectorMap, 14,            CANPINS , Binary );

      VectorMapSetCycleAll (TVVectorMap);

  CycleTableClose;

 end else writeln('ERROR : CycleTableSet call with unkown cycletablename');

end; 
