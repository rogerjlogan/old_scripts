import re
import array
import gzip
import string
import sys
import pprint
#import os

#define orig and new signal headers here
__orig_sh__ = ['DUT_PM','DUT_PM_','SCOPE_TRIGGER','AIC_XTALI','LAN_LINKON','LAN_SPEED100','LAN_ACTIVITY','PC_SPEED100','LCD_AC_NCS','LAN_FDUPLEX','EJTAG_TCK','JTAG_TCK','GPIO0','GPIO2','GPIO3','GPIO4','LCD_HSYNC_RNW','LCD_VSYNC_A0','CODEC_CLKIN','RST_N','REFCLKI','CODEC_DCLK','CODEC_DIN','LAN_RXM','PC_RXM','LAN_RXP','PC_RXP','PHY_EXRES','PHY_TSTA','PC_LINKON','PC_ACTIVITY','PC_FDUPLEX','CODEC_DOUT','CODEC_CLKOUT','CODEC_RESET_N','CODEC_INT','CODEC_CS_N','CODEC_FS','CODEC_RINGIN4','CODEC_RINGIN3','CODEC_RINGIN2','CODEC_RINGIN1','LCD_PD00','LCD_PD01','LCD_PD02','LCD_PD03','LCD_PD04','LCD_PD05','LCD_PD06','LCD_PD07','LCD_PD08','LCD_PD09','LCD_PD10','LCD_PD11','LCD_PD12','LCD_PD13','LCD_PD14','LCD_PD15','KEYPAD15','KEYPAD14','KEYPAD13','KEYPAD12','KEYPAD11','KEYPAD10','KEYPAD09','KEYPAD08','KEYPAD07','KEYPAD06','KEYPAD05','KEYPAD04','KEYPAD03','KEYPAD02','KEYPAD01','KEYPAD00','TEST','RST_N_OUT','SSP0','SSP1','SSP2','SSP3','EJTAG_DINT','EJTAG_SYS_RST_N','EJTAG_TRST0_N','EJTAG_TRST1_N','EJTAG_TDI','EJTAG_TDO','EJTAG_TMS','JTAG_EMU0','JTAG_EMU1','JTAG_TRST_N','JTAG_TDI','JTAG_TDO','JTAG_TMS','VLYNQ5_CLK','VLYNQ5_RXD0','VLYNQ5_RXD1','VLYNQ5_TXD0','VLYNQ5_TXD1','VLYNQ3_CLK','VLYNQ3_RXD0','VLYNQ3_TXD0','USB_PULLE','USB_DM','USB_DP','MBSP_RCLK','MBSP_TCLK','MBSP_RD','MBSP_TD','MBSP_RFS','MBSP_TFS','AIC_XTALO','GPIO1','GPIO5','GPIO6','GPIO7','AIC_OUTM2_150','AIC_OUTP2_150','AIC_OUTP1_150','AIC_OUTM1_150','AIC_OUTP_600','AIC_OUTM_600','AIC_LN_INP','AIC_LN_INM','AIC_CID_INP','AIC_CID_INM','AIC_HN_INP','AIC_HN_INM','AIC_HD_INP','AIC_HD_INM','AIC_MIC_INP','AIC_MIC_INM','AIC_LCD','AIC_MICBIAS','AIC_OUTM_8','AIC_OUTP_8','VR_ENZ','LCD_PCLK_E','LCD_MCLK','LAN_TXP','LAN_TXM','PC_TXM','PC_TXP','ALT_CLK','REFCLKO','EM_A00','EM_A01','EM_A02','EM_A03','EM_A04','EM_A05','EM_A06','EM_A07','EM_A08','EM_A09','EM_A10','EM_A11','EM_A12','EM_A13','EM_A14','EM_A15','EM_A16','EM_A17','EM_A18','EM_A19','EM_A20','EM_A21','EM_A22','EM_A23','EM_D00','EM_D01','EM_D02','EM_D03','EM_D04','EM_D05','EM_D06','EM_D07','EM_D08','EM_D09','EM_D10','EM_D11','EM_D12','EM_D13','EM_D14','EM_D15','EM_D16','EM_D17','EM_D18','EM_D19','EM_D20','EM_D21','EM_D22','EM_D23','EM_D24','EM_D25','EM_D26','EM_D27','EM_D28','EM_D29','EM_D30','EM_D31','EM_WE_DQM0','EM_WE_DQM1','EM_WE_DQM2','EM_WE_DQM3','EM_CS0','EM_CS1','EM_CS2','EM_CS3','EM_CS4','EM_CS5','EM_SDCLK','EM_SDCKE','EM_WAIT','EM_HIZ','EM_RAS','EM_CAS','EM_WE','EM_RNW','EM_OE','UART_RD','UART_TD','UART_RTS','UART_CTS']
__new_sh__ = ['EM_D01','PC_SPEED100','GPIO7','LCD_PD12','LCD_PD05','EM_A19','EJTAG_TCK','JTAG_TCK','EJTAG_TRST1_N','KEYPAD15','EM_WAIT','EM_SDCKE','EM_A12','EM_D23','EJTAG_TDI','VLYNQ5_CLK','SSP3','EM_A07','LCD_PD06','CODEC_RINGIN2','AIC_MICBIAS','VR_VBASE1','LAN_TXP','KEYPAD09','KEYPAD08','UART_CTS','PC_FDUPLEX','GPIO3','EM_D03','LAN_SPEED100','EM_WE_DQM0','AIC_HN_INP','JTAG_EMU1','LCD_PCLK_E','VR_ENZ','EM_D28','UART_RTS','RST_N','KEYPAD12','EJTAG_TMS','AIC_CID_INM','EM_D18','EM_A11','LAN_ACTIVITY','EM_D31','LCD_PD09','JTAG_TDO','EM_D26','LCD_PD15','EM_CAS','EM_D15','KEYPAD06','EM_A17','VLYNQ5_RXD0','USB_PULLE','EM_CS2','LAN_TXM','EM_A03','SSP2','KEYPAD13','MBSP_TFS','AIC_OSC_RTN','EM_A05','KEYPAD02','AIC_LN_INM','GPIO0','AIC_MIC_INP','RST_N_OUT','EM_RAS','EM_CS0','UART_RD','EM_A15','EM_D13','EM_CS4','MBSP_TCLK','CODEC_DIN','CODEC_RINGIN4','LCD_MCLK','VLYNQ5_TXD1','SSP0','AIC_OUTM2_150','VR_VBASE3','EM_A22','AIC_OUTP2_150','EM_D25','KEYPAD11','CODEC_FS','EJTAG_SYS_RST_N','AIC_HD_INM','EM_WE_DQM2','AIC_XTALI','MBSP_RD','GPIO2','VDDS_W16','PHY_EXRES_RTN','AIC_OUTP_600','CODEC_CLKOUT','AIC_OUTM_8','GPIO6','EM_D21','LAN_LINKON','EM_A13','EM_D05','PC_RXM','EM_D11','GPIO4','CODEC_DCLK','TEST','LCD_PD03','UART_TD','EM_D07','ALT_CLK','EM_WE_DQM3','LCD_PD04','EM_A04','CODEC_RINGIN3','EM_D08','EM_SDCLK','LCD_PD07','LCD_PD11','AIC_OUTP1_150','VLYNQ3_TXD0','EM_D20','PC_TXP','MBSP_TD','EM_HIZ','AIC_OUTM1_150','EM_A20','VDD_L9','LCD_PD13','KEYPAD07','LCD_PD14','KEYPAD10','REFCLKO','EM_A23','EM_WE','AIC_LN_INP','EM_A06','EM_A01','EJTAG_TDO','EM_A18','LAN_RXM','JTAG_EMU0','EM_D10','AIC_XTALO','CODEC_RINGIN1','EM_D04','EM_D29','EM_D19','REFCLKI','LCD_PD08','EM_A00','AIC_OUTP_8','LCD_HSYNC_RNW','LCD_AC_NCS','EM_D02','KEYPAD00','GPIO1','EM_D30','REF_OSC_RTN','PC_TXM','AIC_HN_INM','MBSP_RFS','EM_A10','VLYNQ3_RXD0','EJTAG_DINT','LCD_PD00','LAN_FDUPLEX','CODEC_CS_N','PC_ACTIVITY','AIC_MIC_INM','EM_D17','CODEC_INT','EM_WE_DQM1','PC_RXP','MBSP_RCLK','EM_D00','EM_CS1','KEYPAD04','GPIO5','EM_D09','KEYPAD03','JTAG_TRST_N','JTAG_TMS','PC_LINKON','VLYNQ3_CLK','JTAG_TDI','EJTAG_TRST0_N','EM_A02','KEYPAD05','AIC_CID_INP','EM_D16','EM_A09','LCD_PD01','EM_A14','EM_CS5','VR_VBASE2','EM_D22','PHY_TSTA','LAN_RXP','EM_RNW','USB_DM','PHY_EXRES','CODEC_RESET_N','AIC_LCD','KEYPAD01','EM_OE','EM_D24','EM_A21','EM_CS3','EM_D06','EM_D12','LCD_PD10','KEYPAD14','LCD_PD02','AIC_OUTM_600','CODEC_CLKIN','EM_D27','EM_D14','CODEC_DOUT','VLYNQ5_TXD0','AIC_HD_INP','EM_A08','SSP1','EM_A16','VLYNQ5_RXD1','USB_DP','LCD_VSYNC_A0']
__wavetable__ = "ePHY Wavetable"

__label_file__ = "label_indeces.txt"

__wave_map__ = {\
                   '0' :'\x00',\
                   '1' :'\x01',\
                   'L' :'\x02',\
                   'H' :'\x03',\
                   'X' :'\x04',\
                   'Z' :'\x05',\
                   'z' :'\x05',\
                   '-' :'\x06',\
                   '.' :'\x04',\
                   'x' :'\x04',\
               }

lablPat = re.compile(r'^\s*\$(\w+)')
vectPat = re.compile(r'^\s*\*\s*(?P<vector>.*?)\s*\*\s*(?P<sh_wft>.*?)\s*;')
#labPat = re.compile(

def myOpen(fileN, mode="r"):
    if fileN.endswith('.gz'):
        return gzip.open(fileN,mode)
    return open(fileN,mode)

def getCharStr(char):
    if char not in __wave_map__.keys():
        sys.exit("Unmapped character in string: "+char)
    return __wave_map__[char]

def main(fileN, inds=None):
    
    print "processing "+ fileN
    outFile = myOpen(fileN.replace(".evo",".binl"),'w')

    index=0
    label_found = False
    label,label_str = '',''
    for line in myOpen(fileN):
        labObj = lablPat.search(line)
        vecObj = vectPat.search(line)
        if labObj:
            label_found = True
            label = labObj.group()
        elif vecObj:
            orig_vect = re.sub('\s',"",vecObj.group('vector'))
            if len(__orig_sh__) != len(orig_vect):
                sys.exit("ERROR !!! Length of orig signal header doesn't match length of orig vector in pattern. Exiting ...")
            orig_vect_dict = dict(zip(__orig_sh__,list(orig_vect)))
            index += 1
            if label_found:
                label_found = False
                label_str += label+", "+str(index-1)+"\n"
            new_vect_dict = {}
            if index == 1:
                pin_vect_dict = {}
            for pin in __new_sh__:
                if pin in orig_vect_dict.keys():
                    new_vect_dict[pin] = getCharStr(orig_vect_dict[pin])
                    if index == 1:
                        pin_vect_dict[pin] = new_vect_dict[pin]
                    else:
                        pin_vect_dict[pin] = pin_vect_dict[pin] + new_vect_dict[pin]
                else:
                    new_vect_dict[pin] = getCharStr('X')
                    if index == 1:
                        pin_vect_dict[pin] = getCharStr('X')
                    else:
                        pin_vect_dict[pin] = pin_vect_dict[pin] + getCharStr('X')
    f=open(__label_file__,"w")
    f.write(label_str)
    f.close
    header = "hp93000,vector,0.1\n"+\
             "DMAS PARA,SM,8,(@)\n"+\
             "DMAS SQPG,SM,4,(@)\n"+\
             "SQLB \""+fileN[:-4]+"\",MAIN,0,3,\""+__wavetable__+"\"\n"+\
             "SQLA LBL,\""+fileN[:-4]+"\",\"PARA_MEM=SM,PARA_MCTX=DEFAULT\"\n"+\
             "SQPG 0,STVA,0,,,(@)\n"+\
             "SQPG 1,STSA,,,,(@)\n"+\
             "SQPG 2,GENV,"+str(index)+",,,(@)\n"+\
             "SQPG 3,STOP,,,,(@)\n"+\
             "WSDM 1,2\n"
    outstring = header
    for k,v in pin_vect_dict.items():
        outstring += "VECD PARA,SM,0,"+str(index)+",("+k+'),#9'+str(index).rjust(9,'0')+v+'\n'
    outstring += "NOOP \"7.2.1\",,,\n"
    outFile.write(outstring)
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
