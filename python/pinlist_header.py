import sys
import re
import pprint
import os
#import string
from string import *
import time

__pins__ = [] #raw pinlist
__pinhdr__ = "" #vertical pinlist string

def buildPinlistHeader():
    global __pinhdr__
    maxlen=len(max(__pins__,key=len))
    padpins=[]
    for pin in __pins__:
        padpins.append(pin.ljust(maxlen))
    hdr = []
    for c in range(1,maxlen+1):
        row = "\""
        for p in padpins:
            row += p[c-1]
        row += "\""
        hdr.append(row)
    __pinhdr__ = join(hdr,"\n")

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __pins__
    __pins__ = ['TEST','RST_N','RST_N_OUT','SSP0','SSP1','SSP2','SSP3','EJTAG_DINT','EJTAG_SYS_RST_N','EJTAG_TRST0_N','EJTAG_TRST1_N','EJTAG_TCK','EJTAG_TDI','EJTAG_TDO','EJTAG_TMS','JTAG_EMU0','JTAG_EMU1','JTAG_TRST_N','JTAG_TCK','JTAG_TDI','JTAG_TDO','JTAG_TMS','VLYNQ5_CLK','VLYNQ5_RXD0','VLYNQ5_RXD1','VLYNQ5_TXD0','VLYNQ5_TXD1','VLYNQ3_CLK','VLYNQ3_RXD0','VLYNQ3_TXD0','USB_PULLE','USB_DM','USB_DP','MBSP_RCLK','MBSP_TCLK','MBSP_RD','MBSP_TD','MBSP_RFS','MBSP_TFS','VR_VBASE2','AIC_XTALI','AIC_XTALO','GPIO0','GPIO1','GPIO2','GPIO3','GPIO4','GPIO5','GPIO6','GPIO7','AIC_OUTM2_150','AIC_OUTP2_150','AIC_OUTP1_150','AIC_OUTM1_150','AIC_OUTP_600','AIC_OUTM_600','AIC_LN_INP','AIC_LN_INM','AIC_CID_INP','AIC_CID_INM','AIC_HN_INP','AIC_HN_INM','AIC_HD_INP','AIC_HD_INM','AIC_MIC_INP','AIC_MIC_INM','AIC_LCD','AIC_MICBIAS','AIC_OUTM_8','AIC_OUTP_8','VR_ENZ','VR_VBASE1','KEYPAD00','KEYPAD01','KEYPAD02','KEYPAD03','KEYPAD04','KEYPAD05','KEYPAD06','KEYPAD07','KEYPAD08','KEYPAD09','KEYPAD10','KEYPAD11','KEYPAD12','KEYPAD13','KEYPAD14','KEYPAD15','LCD_AC_NCS','LCD_PCLK_E','LCD_MCLK','LCD_HSYNC_RNW','LCD_VSYNC_A0','LCD_PD00','LCD_PD01','LCD_PD02','LCD_PD03','LCD_PD04','LCD_PD05','LCD_PD06','LCD_PD07','LCD_PD08','LCD_PD09','LCD_PD10','LCD_PD11','LCD_PD12','LCD_PD13','LCD_PD14','LCD_PD15','LAN_SPEED100','LAN_LINKON','LAN_ACTIVITY','LAN_FDUPLEX','PC_SPEED100','PC_LINKON','PC_ACTIVITY','PC_FDUPLEX','VR_VBASE3','PHY_EXRES','PHY_TSTA','LAN_RXP','LAN_RXM','LAN_TXP','LAN_TXM','PC_TXM','PC_TXP','PC_RXM','PC_RXP','ALT_CLK','REFCLKI','REFCLKO','CODEC_DCLK','CODEC_DIN','CODEC_DOUT','CODEC_CLKIN','CODEC_RINGIN1','CODEC_RINGIN2','CODEC_RINGIN3','CODEC_RINGIN4','CODEC_FS','CODEC_CS_N','CODEC_INT','CODEC_RESET_N','CODEC_CLKOUT','EM_A00','EM_A01','EM_A02','EM_A03','EM_A04','EM_A05','EM_A06','EM_A07','EM_A08','EM_A09','EM_A10','EM_A11','EM_A12','EM_A13','EM_A14','EM_A15','EM_A16','EM_A17','EM_A18','EM_A19','EM_A20','EM_A21','EM_A22','EM_A23','EM_D00','EM_D01','EM_D02','EM_D03','EM_D04','EM_D05','EM_D06','EM_D07','EM_D08','EM_D09','EM_D10','EM_D11','EM_D12','EM_D13','EM_D14','EM_D15','EM_D16','EM_D17','EM_D18','EM_D19','EM_D20','EM_D21','EM_D22','EM_D23','EM_D24','EM_D25','EM_D26','EM_D27','EM_D28','EM_D29','EM_D30','EM_D31','EM_WE_DQM0','EM_WE_DQM1','EM_WE_DQM2','EM_WE_DQM3','EM_CS0','EM_CS1','EM_CS2','EM_CS3','EM_CS4','EM_CS5','EM_SDCLK','EM_SDCKE','EM_WAIT','EM_HIZ','EM_RAS','EM_CAS','EM_WE','EM_RNW','EM_OE','UART_RD','UART_TD','UART_RTS','UART_CTS']
    buildPinlistHeader()
    print __pinhdr__

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
