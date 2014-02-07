import re
import gzip
import string
import sys

same = False

fus_sh = ['TEST','RST_N','RST_N_OUT','SSP0','SSP1','SSP2','SSP3','EJTAG_DINT','EJTAG_SYS_RST_N','EJTAG_TRST0_N','EJTAG_TRST1_N','EJTAG_TCK','EJTAG_TDI','EJTAG_TDO','EJTAG_TMS','JTAG_EMU0','JTAG_EMU1','JTAG_TRST_N','JTAG_TCK','JTAG_TDI','JTAG_TDO','JTAG_TMS','VLYNQ5_CLK','VLYNQ5_RXD0','VLYNQ5_RXD1','VLYNQ5_TXD0','VLYNQ5_TXD1','VLYNQ3_CLK','VLYNQ3_RXD0','VLYNQ3_TXD0','USB_PULLE','USB_DM','USB_DP','MBSP_RCLK','MBSP_TCLK','MBSP_RD','MBSP_TD','MBSP_RFS','MBSP_TFS','VR_VBASE2','AIC_XTALI','AIC_XTALO','GPIO0','GPIO1','GPIO2','GPIO3','GPIO4','GPIO5','GPIO6','GPIO7','AIC_OUTM2_150','AIC_OUTP2_150','AIC_OUTP1_150','AIC_OUTM1_150','AIC_OUTP_600','AIC_OUTM_600','AIC_LN_INP','AIC_LN_INM','AIC_CID_INP','AIC_CID_INM','AIC_HN_INP','AIC_HN_INM','AIC_HD_INP','AIC_HD_INM','AIC_MIC_INP','AIC_MIC_INM','AIC_LCD','AIC_MICBIAS','AIC_OUTM_8','AIC_OUTP_8','VR_ENZ','VR_VBASE1','KEYPAD00','KEYPAD01','KEYPAD02','KEYPAD03','KEYPAD04','KEYPAD05','KEYPAD06','KEYPAD07','KEYPAD08','KEYPAD09','KEYPAD10','KEYPAD11','KEYPAD12','KEYPAD13','KEYPAD14','KEYPAD15','LCD_AC_NCS','LCD_PCLK_E','LCD_MCLK','LCD_HSYNC_RNW','LCD_VSYNC_A0','LCD_PD00','LCD_PD01','LCD_PD02','LCD_PD03','LCD_PD04','LCD_PD05','LCD_PD06','LCD_PD07','LCD_PD08','LCD_PD09','LCD_PD10','LCD_PD11','LCD_PD12','LCD_PD13','LCD_PD14','LCD_PD15','LAN_SPEED100','LAN_LINKON','LAN_ACTIVITY','LAN_FDUPLEX','PC_SPEED100','PC_LINKON','PC_ACTIVITY','PC_FDUPLEX','VR_VBASE3','PHY_EXRES','PHY_TSTA','LAN_RXP','LAN_RXM','LAN_TXP','LAN_TXM','PC_TXM','PC_TXP','PC_RXM','PC_RXP','ALT_CLK','REFCLKI','REFCLKO','CODEC_DCLK','CODEC_DIN','CODEC_DOUT','CODEC_CLKIN','CODEC_RINGIN1','CODEC_RINGIN2','CODEC_RINGIN3','CODEC_RINGIN4','CODEC_FS','CODEC_CS_N','CODEC_INT','CODEC_RESET_N','CODEC_CLKOUT','EM_A00','EM_A01','EM_A02','EM_A03','EM_A04','EM_A05','EM_A06','EM_A07','EM_A08','EM_A09','EM_A10','EM_A11','EM_A12','EM_A13','EM_A14','EM_A15','EM_A16','EM_A17','EM_A18','EM_A19','EM_A20','EM_A21','EM_A22','EM_A23','EM_D00','EM_D01','EM_D02','EM_D03','EM_D04','EM_D05','EM_D06','EM_D07','EM_D08','EM_D09','EM_D10','EM_D11','EM_D12','EM_D13','EM_D14','EM_D15','EM_D16','EM_D17','EM_D18','EM_D19','EM_D20','EM_D21','EM_D22','EM_D23','EM_D24','EM_D25','EM_D26','EM_D27','EM_D28','EM_D29','EM_D30','EM_D31','EM_WE_DQM0','EM_WE_DQM1','EM_WE_DQM2','EM_WE_DQM3','EM_CS0','EM_CS1','EM_CS2','EM_CS3','EM_CS4','EM_CS5','EM_SDCLK','EM_SDCKE','EM_WAIT','EM_HIZ','EM_RAS','EM_CAS','EM_WE','EM_RNW','EM_OE','UART_RD','UART_TD','UART_RTS','UART_CTS']
jazz_sh = ['AIC_XTALI','EJTAG_SYS_RST_N','EJTAG_TCK','GPIO1','LAN_SPEED100','REFCLKI','TEST','VLYNQ3_CLK','VLYNQ5_CLK','AIC_LCD','AIC_MICBIAS','AIC_OSC_RTN','AIC_OUTM_600','AIC_OUTM_8','AIC_OUTM1_150','AIC_OUTM2_150','AIC_OUTP_600','AIC_OUTP_8','AIC_OUTP1_150','AIC_OUTP2_150','AIC_XTALO','ALT_CLK','CODEC_CLKIN','CODEC_CLKOUT','CODEC_CS_N','CODEC_DCLK','CODEC_DIN','CODEC_DOUT','CODEC_FS','CODEC_INT','CODEC_RESET_N','CODEC_RINGIN1','CODEC_RINGIN2','CODEC_RINGIN3','CODEC_RINGIN4','EJTAG_DINT','EJTAG_TDI','EJTAG_TDO','EJTAG_TMS','EJTAG_TRST0_N','EJTAG_TRST1_N','EM_A00','EM_A01','EM_A02','EM_A03','EM_A04','EM_A05','EM_A06','EM_A07','EM_A08','EM_A09','EM_A10','EM_A11','EM_A12','EM_A13','EM_A14','EM_A15','EM_A16','EM_A17','EM_A18','EM_A19','EM_A20','EM_A21','EM_A22','EM_A23','EM_CAS','EM_CS0','EM_CS1','EM_CS2','EM_CS3','EM_CS4','EM_CS5','EM_D00','EM_D01','EM_D02','EM_D03','EM_D04','EM_D05','EM_D06','EM_D07','EM_D08','EM_D09','EM_D10','EM_D11','EM_D12','EM_D13','EM_D14','EM_D15','EM_D16','EM_D17','EM_D18','EM_D19','EM_D20','EM_D21','EM_D22','EM_D23','EM_D24','EM_D25','EM_D26','EM_D27','EM_D28','EM_D29','EM_D30','EM_D31','EM_HIZ','EM_OE','EM_RAS','EM_RNW','EM_SDCKE','EM_SDCLK','EM_WAIT','EM_WE','EM_WE_DQM0','EM_WE_DQM1','EM_WE_DQM2','EM_WE_DQM3','GPIO0','GPIO2','GPIO3','GPIO4','GPIO5','GPIO6','GPIO7','JTAG_EMU0','JTAG_EMU1','JTAG_TCK','JTAG_TDI','JTAG_TDO','JTAG_TMS','JTAG_TRST_N','KEYPAD00','KEYPAD01','KEYPAD02','KEYPAD03','KEYPAD04','KEYPAD05','KEYPAD06','KEYPAD07','KEYPAD08','KEYPAD09','KEYPAD10','KEYPAD11','KEYPAD12','KEYPAD13','KEYPAD14','KEYPAD15','LAN_ACTIVITY','LAN_FDUPLEX','LAN_LINKON','LCD_AC_nCS','LCD_HSYNC_RnW','LCD_MCLK','LCD_PCLK_E','LCD_PD00','LCD_PD01','LCD_PD02','LCD_PD03','LCD_PD04','LCD_PD05','LCD_PD06','LCD_PD07','LCD_PD08','LCD_PD09','LCD_PD10','LCD_PD11','LCD_PD12','LCD_PD13','LCD_PD14','LCD_PD15','LCD_VSYNC_A0','MBSP_RCLK','MBSP_RD','MBSP_RFS','MBSP_TCLK','MBSP_TD','MBSP_TFS','PC_ACTIVITY','PC_FDUPLEX','PC_LINKON','PC_SPEED100','PHY_EXRES','PHY_EXRES_RTN','PHY_TSTA','REF_OSC_RTN','REFCLKO','RST_N','RST_N_OUT','SSP0','SSP1','SSP2','SSP3','UART_CTS','UART_RD','UART_RTS','UART_TD','USB_DM','USB_DP','USB_PULLE','VLYNQ3_RXD0','VLYNQ3_TXD0','VLYNQ5_RXD0','VLYNQ5_RXD1','VLYNQ5_TXD0','VLYNQ5_TXD1','VR_ENZ']
_ignore_pins_ = ['AIC_OSC_RTN','PHY_EXRES_RTN','REF_OSC_RTN']

_end_sh_ = [x.upper() for x in jazz_sh]

if same:
    _beg_sh_ = [x.upper() for x in jazz_sh]
else:
    _beg_sh_ = [x.upper() for x in fus_sh]

vectPat = re.compile(r'^\s*\*\s*(?P<vector>.*?)\s*\*\s*(?P<sh>\w+?)?\s*(?P<wft>\w+?)?\s*;\s*(?P<uInst>\<.*?\>)?')
repPat = re.compile(r'\<\s*RPT\s+(?P<count>\d+)\s*\>')

def getheader(pinlist,ignore_pins):
    offset=3
    maxlen=len(max(pinlist,key=len))
    padpins=[]
    for pin in pinlist:
        if pin not in ignore_pins:
            padpins.append(pin.ljust(maxlen))
    hdr = []
    for c in range(1,maxlen):
        row = "\""
        for p in padpins:
            row += p[c-1]
        row += "\""
        hdr.append(row)
    return "\n".join(hdr)+'\n'

def myOpen(fileN, mode="r"):
    if fileN.endswith('.gz'):
        return gzip.open(fileN,mode)
    return open(fileN,mode)

def main(fileN, inds=None):
    print "processing "+ fileN
    outFile = myOpen(fileN.replace(".evo",".cmp.evo"),'w')
    outFile.write(getheader(_end_sh_,_ignore_pins_))

    repeat=1
    for line in myOpen(fileN):
        vecObj = vectPat.search(line)
        if vecObj:
            if vecObj.group('sh') == None:
                sh = ''
            else:
                sh = vecObj.group('sh')
            if vecObj.group('wft') == None:
                wft = ''
            else:
                wft = vecObj.group('wft')
            if vecObj.group('uInst') == None:
                uInst = ''
            else:
                uInst = vecObj.group('uInst')
                repObj = repPat.search(uInst)
                if repObj:
                    repeat=int(repObj.group('count'))
                    uInst = ''
                    
            orig_vect = re.sub('\s',"",vecObj.group('vector'))
            if len(_beg_sh_) != len(orig_vect):
                print "len(_beg_sh_) =",len(_beg_sh_)
                print "orig_vect     =",orig_vect
                print "len(orig_vect)   =",len(orig_vect)
                sys.exit("ERROR !!! Length of orig signal header doesn't match length of orig vector in pattern. Exiting ...")
            orig_vect_dict = dict(zip(_beg_sh_,list(orig_vect)))
            new_vect='*'
            for pin in _end_sh_:
                if pin in orig_vect_dict and pin not in _ignore_pins_:
                    new_vect+=orig_vect_dict[pin]
            new_vect+='*'+sh+wft+';'+uInst+'\n'
            for x in range(repeat):
                outFile.write(new_vect)
    outFile.close()
    return

if __name__ == "__main__":
    if len(sys.argv) <2:
        print "Usage : python " + sys.argv[0] + " <files>"
        sys.exit()
    inds=[]
    for ii,x in enumerate(sys.argv[1:]):
        try:
            inds.append(int(x))
        except ValueError:
            break
    
    for fileN in sys.argv[ii+1:]:
        main(fileN, inds)
