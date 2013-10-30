"""
    Requirements:
         - Python2.3 or higher
    Function:
        Used to convert A5-80 patterns to Fusion Patterns
"""
__progfile__ = "v580pat.py"
__version__ = "v1.0"
__author__ = "AUTHOR: Roger Logan, Anora, Test Engineer, Dallas, TX"
__date__ = "LAST MODIFIED: August 14, 2013"

#__sighdr__ = \
#['DOUT_TXN','DOUT_TXP','RBC0','MRBC0','RBC1','MRBC1','RD0','MRD0','RD1','MRD1','RD2','MRD2','RD3','MRD3','RD4',\
#'MRD4','RD5','MRD5','RD6','MRD6','RD7','MRD7','RD8','MRD8','RD9','MRD9','SYNC','MSYNC','RC0','RC1','TC0','TC1',\
#'DIN_RXN','DIN_RXP','LCKREFN','LOOPEN','TESTEN','REFCLK','TD0','MTD0','TD1','MTD1','TD2','MTD2','TD3',\
#'MTD3','TD4','MTD4','TD5','MTD5','TD6','MTD6','TD7','MTD7','TD8','MTD8','TD9','MTD9','SYNCEN','TRIG','SUPER_TRIG']
__sighdr__ = \
['DIN_RXN','DIN_RXP','DOUT_TXN','DOUT_TXP','RBC0','RBC1',\
'MRBC0','MRBC1','RD0','RD1','RD2','RD3','RD4','RD5','RD6',\
'RD7','RD8','RD9','MRD0','MRD1','MRD2','MRD3','MRD4','MRD5',\
'MRD6','MRD7','MRD8','MRD9','TD0','TD1','TD2','TD3','TD4',\
'TD5','TD6','TD7','TD8','TD9','MTD0','MTD1','MTD2','MTD3',\
'MTD4','MTD5','MTD6','MTD7','MTD8','MTD9','SYNC','MSYNC',\
'SYNCEN','RC0','RC1','TC0','TC1','LCKREFN','LOOPEN','TESTEN',\
'REFCLK','TRIG','SUPER_TRIG']

__pingroups__ = \
{\
'CONTY_POS'     :['RBC0','RBC1','RD0','RD1','RD2','RD3','RD4','RD5','RD6','RD7','RD8','RD9','SYNC','DIN_RXN','DIN_RXP','REFCLK'],\
'CONTY_NEG'     :['RBC0','RBC1','RD0','RD1','RD2','RD3','RD4','RD5','RD6','RD7','RD8','RD9','SYNC','DIN_RXN','DIN_RXP','LCKREFN','LOOPEN','TESTEN','REFCLK','TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9','SYNCEN'],\
'TD_INS'        :['TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9'],\
'RD_OUTS'       :['RD0','RD1','RD2','RD3','RD4','RD5','RD6','RD7','RD8','RD9','SYNC'],\
'TX_PINS'       :['DOUT_TXP','DOUT_TXN'],\
'CLK_OUTS'      :['DOUT_TXP','DOUT_TXN'],\
'CLK_OUTS'      :['RBC0','RBC1'],\
'CTRL_PINS'     :['LOOPEN','REFCLK','SYNCEN','TESTEN','LCKREFN'],\
'FAST_CTRL_PINS':['LOOPEN','SYNCEN','TESTEN','LCKREFN'],\
'TTL_PINS'      :['TD_INS','RD_OUTS','CLK_OUTS','CTRL_PINS'],\
'TTL_INS'       :['TD_INS','CTRL_PINS','TRIG'],\
'FAST_TTL_INS'  :['TD_INS','FAST_CTRL_PINS','TRIG'],\
'TTL_OUTS'      :['RD_OUTS','CLK_OUTS','SYNC'],\
'ALL_INS'       :['TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9','LOOPEN','SYNCEN','TESTEN','LCKREFN','DIN_RXN','REFCLK','DIN_RXP'],\
'FAST_INS'      :['TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9','LOOPEN','SYNCEN','TESTEN','LCKREFN'],\
'ALL_OUTS'      :['RD9','RD8','RD7','RD6','RD5','RD4','RD3','RD2','RD1','RD0','SYNC','DOUT_TXN','DOUT_TXP','RBC0','RBC1'],\
'ALL_PINS'      :['ALL_INS','ALL_OUTS'],\
'PECL_PINS'     :['DOUT_TXN','DOUT_TXP','DIN_RXN','DIN_RXP'],\
'MUX_ODD'       :['RD0','RD1','RD2','RD3','RD4','RD5','RD6','RD7','RD8','RD9'],\
'MUX_EVEN'      :['MRD0','MRD1','MRD2','MRD3','MRD4','MRD5','MRD6','MRD7','MRD8','MRD9'],\
'MUX_PINS'      :['RD0','RD1','RD2','RD3','RD4','RD5','RD6','RD7','RD8','RD9','SYNC','RBC0','RBC1','MRD0','MRD1','MRD2','MRD3','MRD4','MRD5','MRD6','MRD7','MRD8','MRD9','MSYNC','MRBC0','MRBC1'],\
'MUX_INS'       :['MTD0','MTD1','MTD2','MTD3','MTD4','MTD5','MTD6','MTD7','MTD8','MTD9'],\
'ALLDIG'        :['SUPER_TRIG','LOOPEN','TESTEN','SYNCEN','LCKREFN','RD9','RD8','RD7','RD6','RD5','RD4','RD3','RD2','RD1','RD0','SYNC','DIN_RXN','DIN_RXP','TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9']\
}
__delims__ = ['(*','*)','{','}','/*','*/','\"',';']

__complex_pats__ = {'CISCO':1,'COMMA2':1,'latency':1,'meas_latency_130':1,'VCO_PAT':1,'RAW_INT':2,'RELOCK':2,'icc':2,'RAW_EXT':3,'RISEFALL':4,\
'P2R3_2':0,'LCREV3_a':0,'LCREV3':0,'N_TREE':0,'P2CR_3':0,'P2LC_4_a':0,'P2LC_4':0,'P2RX_5':0,'P2TX_1':0,'RX2REV3':0,'RXREV3':0,'RX':0,'TX_a':0,'TX':0}
__complex_vectLsts__ = \
{\
0:['DOUT_TXN','DOUT_TXP','RBC0','RBC1','RD0','RD1','RD2','RD3','RD4','RD5','RD6','RD7','RD8','RD9',\
'SYNC','RC0','RC1','TC0','TC1','DIN_RXN','DIN_RXP','LCKREFN','LOOPEN','SYNCEN','TESTEN','REFCLK',\
'TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9'],\
1:['SUPER_TRIG','TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9',\
'MTD0','MTD1','MTD2','MTD3','MTD4','MTD5','MTD6','MTD7','MTD8','MTD9',\
'LOOPEN','SYNCEN','TESTEN','LCKREFN','RD0','RD1','RD2','RD3','RD4','RD5',\
'RD6','RD7','RD8','RD9','MRD0','MRD1','MRD2','MRD3','MRD4','MRD5','MRD6',\
'MRD7','MRD8','MRD9','SYNC','MSYNC','RBC0','MRBC0','RBC1','MRBC1','TRIG'],\
2:['SUPER_TRIG','TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9',\
'MTD0','MTD1','MTD2','MTD3','MTD4','MTD5','MTD6','MTD7','MTD8','MTD9',\
'LOOPEN','SYNCEN','TESTEN','LCKREFN','RD0','MRD0','RD1','MRD1','RD2','MRD2',\
'RD3','MRD3','RD4','MRD4','RD5','MRD5','RD6','MRD6','RD7','MRD7','RD8',\
'MRD8','RD9','MRD9','SYNC','MSYNC','RBC0','MRBC0','RBC1','MRBC1','TRIG'],\
3:['SUPER_TRIG','TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9',\
'MTD0','MTD1','MTD2','MTD3','MTD4','MTD5','MTD6','MTD7','MTD8','MTD9',\
'LOOPEN','SYNCEN','TESTEN','LCKREFN','RD0','MRD0','RD1','MRD1','RD2','MRD2',\
'RD3','MRD3','RD4','MRD4','RD5','MRD5','RD6','MRD6','RD7','MRD7','RD8',\
'MRD8','RD9','MRD9','SYNC','MSYNC','RBC0','MRBC0','RBC1','MRBC1','TRIG','DOUT_TXP'],\
4:['SUPER_TRIG','TD0','TD1','TD2','TD3','TD4','TD5','TD6','TD7','TD8','TD9',\
'LOOPEN','SYNCEN','TESTEN','LCKREFN','RD0','MRD0','RD1','MRD1','RD2','MRD2',\
'RD3','MRD3','RD4','MRD4','RD5','MRD5','RD6','MRD6','RD7','MRD7','RD8',\
'MRD8','RD9','MRD9','SYNC','MSYNC','RBC0','MRBC0','RBC1','MRBC1','TRIG'],\
}
__complex_warning__ = \
"##### Things to do BEFORE running this script:\n\
1) Make sure each vector has a TSET to be found OR THAT VECTOR WILL BE IGNORED.\n\
   If any vectors don't have a TSET, then copy the last used TSET # from a vector somewhere above that vector.\n\
2) Replace any subroutine calls in line with subroutine vectors.\n\
   Usually the subroutine is at the bottom, but could be in another vector file.\n\
3) Update this script\'s global variables __complex_pats__ and __complex_vectLsts__\n\
   (In the future, my intention was to do all of this dynamically like with the simple patterns.)\n\
##### Things to do AFTER running this script:\n\
1) Manually convert all micro-instructions placed between \"<\" and \">\" AFTER running the script.\n\
   Everything that comes before TSET is considered a mico-instruction.\n"

__conversion_msg__ = \
"\"The following character conversions were made:\"\n\
\"L to 0 :cmp:low                                        ,drv:hiz   ,loads:on\"\n\
\"H to 1 :cmp:high                                       ,drv:hiz   ,loads:on\"\n\
\"0 to L :cmp:mask                                       ,drv:low   ,loads:off\"\n\
\"1 to H :cmp:mask                                       ,drv:high  ,loads:off\"\n\
\"M to F :cmp:expect midband (invalid level)             ,drv:hiz   ,loads:on\"\n\
\"00 (double drive) to c :cmp:mask                       ,drv:low,drv:low   ,loads:off\"\n\
\"11 (double drive) to C :cmp:mask                       ,drv:high,drv:high ,loads:off\"\n\
\"10 (double drive) to k :cmp:mask                       ,drv:high,drv:low  ,loads:off\"\n\
\"01 (double drive) to K :cmp:mask                       ,drv:low,drv:high  ,loads:off\"\n\
\"V to V :(no change)cmp:expect valid level (not midband),drv:hiz   ,loads:on\"\n\
\"X to X :(no change)cmp:mask                            ,drv:hiz   ,loads:on\"\n\
\"- to - :(no change)cmp:runtime repeat                  ,drv:repeat,loads:repeat\"\n\n"

import sys
import re
import pprint
import os
#import string
from string import *
import time

__EVHDR__ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
__VERBOSE__ = True

__HDR_COMMENTS__ = ""
__DUMMYVECT__ = ""

#Error Messages
__PERMISSIONS_ERR__ = "If file was input, check to see if it exists and that read permissions are allowed for you.\n"
__PERMISSIONS_ERR__ += "Also, check that write permissions are allowed for this directory, as this scripts creates a file."
__V580PAT__ = "<somepat>.tp" #generated from executing the following command while in image editor 'iprc -map PROGRAM.tl somepat.pat'
__PINLISTHDR__ = ""
__VECTORBODY__ = ""
__UNKNOWN_DATA__ = ""
__SIMPLEVECTLST__ = []
__PATTERN__ = ""

class TextException(Exception): pass

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default
    def __getitem__(self, key):
        if not self.has_key(key):
            self[key] = self.default()
        return dict.__getitem__(self, key)
#End Ddict()

def buildPinlistHeader():
    global __PINLISTHDR__
    maxlen=len(max(__sighdr__,key=len))
    padpins=[]
    for pin in __sighdr__:
        padpins.append(pin.ljust(maxlen))
    hdr = []
    for c in range(1,maxlen+1):
        row = "\" "
        for p in padpins:
            row += p[c-1]
        row += " \""
        hdr.append(row)
    __PINLISTHDR__ = join(hdr,"\n")
#End buildPinlistHeader

def getHdrComments(content):
    global __HDR_COMMENTS__
    p=re.compile("^(?P<hdrcomm>.*?)filetype",re.DOTALL)
    hdrcomm=p.search(content)
    __HDR_COMMENTS__=hdrcomm.group('hdrcomm')
#End getHdrComments()

def reOrgVect(vect,complex_type):
    global __DUMMYVECT__
    newvectLst = ['X' for x in range(len(__sighdr__))]
    if not len(__DUMMYVECT__):
        dummy = ''.join(newvectLst)
        __DUMMYVECT__ = "\n* "+dummy+" * TSET1 SH0;"
    for p in __sighdr__:
        vectorLst = __complex_vectLsts__[complex_type]
        if p in vectorLst:
            newvectLst[__sighdr__.index(p)] = vect[vectorLst.index(p)]
        elif p[0] == 'M' and complex_type == 0:#this is simple pattern and a mux pin (duplicate data from primary pin)
            newvectLst[__sighdr__.index(p)] = vect[vectorLst.index(p[1:])]
    return ''.join(newvectLst)
#End reOrgVect

def translate(vectorStr):
    """
    requirement:from string import maketrans
    A5-80 character defintions:
     'L' => cmp:low                             ,drv:hiz   ,loads:on    
     'H' => cmp:high                            ,drv:hiz   ,loads:on    
     'X' => cmp:mask                            ,drv:hiz   ,loads:on    
     'M' => cmp:expect midband (invalid level)  ,drv:hiz   ,loads:on    
     'V' => cmp:expect valid level (not midband),drv:hiz   ,loads:on    
     '-' => cmp:runtime repeat                  ,drv:repeat,loads:repeat
     '0' => cmp:mask                            ,drv:low   ,loads:off   
     '1' => cmp:mask                            ,drv:high  ,loads:off   
    """
    intab  = 'LHXMV-01' #A5-80 convention
    outtab = '01XFV-LH' #TI fusion convention
    trantab = maketrans(intab, outtab)
    vectorStr = vectorStr.translate(trantab, ' ');#2nd arg are chars to remove/delete from string
    return vectorStr
#End translate()

#def getSimpVectLst(content):
#    global __SIMPLEVECTLST__
#    p=re.compile("vector\s*\(\s*\(\s*(?P<vectlst>.*?)\s*\)\s*\)",re.DOTALL)
#    vectlst=p.search(content)
#    vectlst=vectlst.group('vectlst')
#    __SIMPLEVECTLST__ = split(vectlst,",")
#    __SIMPLEVECTLST__ = map(lambda p: p.strip(), __SIMPLEVECTLST__) #strip ws from each element
##End getSimpVectLst()

def getDoubleClkChar(char1,char2):
    char = "?"
    if char1 == '0' and char2 == '0':
        char = "c"
    elif char1 == '1' and char2 == '1':
        char = "C"
    elif char1 == '1' and char2 == '0':
        char = "k"
    elif char1 == '0' and char2 == '1':
        char = "K"
    else:
        print "ERROR!!!!\n",char1,char2
    return char
#End getDoubleClkChar()

def getVectorData(content):
    global __VECTORBODY__,__UNKNOWN_DATA__
    print "Converting vectors..."
    complex_type = __complex_pats__[__PATTERN__]
    vectLst =  __complex_vectLsts__[complex_type]
    if complex_type == 0:#simple patterns
        vectPat  = re.compile("^\s*(?:\w+:|)\s*(?P<micro>.*?)\s*TSET\s+(?P<tset>\d+?)\s+(?P<vect>.*?)\s*;\s*(?P<comm>.*)\s*$")
    elif complex_type == 1 or complex_type == 2:
        #            REPEAT 45        TSET 2  0 1010101010 1010101010 1010101010 1010101010 1101           00000000000000000000 XX XXXX X;
        vectPat  = re.compile("^\s*(?:\w+:|)\s*(?P<micro>.*?)\s+TSET\s+(?P<tset>\d+?)"
                              "\s+(?P<field1>.*?)\s+(?P<field2>.*?)\s+(?P<field3>.*?)\s+(?P<field4>.*?)\s+(?P<field5>.*?)"
                              "\s+(?P<field6>.*?)\s+(?P<field7>.*?)\s+(?P<field8>.*?)\s+(?P<field9>.*?)\s+(?P<field10>.*?)\s*;\s*(?P<comm>.*)\s*$")
    elif complex_type == 3:
        #    REPEAT 45       TSET 2  0 0011111010 1010101010 1010101010 1010101010 0101 00000000000000000000 00 0000 0 0 X;
        vectPat  = re.compile("^\s*(?:\w+:|)\s*(?P<micro>.*?)\s+TSET\s+(?P<tset>\d+?)"
                              "\s+(?P<field1>.*?)\s+(?P<field2>.*?)\s+(?P<field3>.*?)\s+(?P<field4>.*?)\s+(?P<field5>.*?)"
                              "\s+(?P<field6>.*?)\s+(?P<field7>.*?)\s+(?P<field8>.*?)\s+(?P<field9>.*?)\s+(?P<field10>.*?)"
                              "\s+(?P<field11>.*?)\s+(?P<field12>.*?)\s*;\s*(?P<comm>.*)\s*$")
    elif complex_type == 4:
        #    REPEAT 8750   TSET 2 0 1111100000 1111100000 0000 XXXXXXXXXXXXXXXXXXXX 00 0000 1;
        vectPat  = re.compile("^\s*(?:\w+:|)\s*(?P<micro>.*?)\s+TSET\s+(?P<tset>\d+?)"
                              "\s+(?P<field1>.*?)\s+(?P<field2>.*?)\s+(?P<field3>.*?)\s+(?P<field4>.*?)\s+(?P<field5>.*?)"
                              "\s+(?P<field6>.*?)\s+(?P<field7>.*?)\s+(?P<field8>.*?)\s*;\s*(?P<comm>.*)\s*$")
    else:
        print "\n\n### ERROR !!!! Unknown type of complex pattern !!!\n\n"
    
    globallabelPat = re.compile("^\s*GLOBAL\s*(?P<label>\w+):(.*TSET\s+\d+|\s*$)")
    labelPat = re.compile("^\s*(?P<label>\w+):(.*TSET\s+\d+|\s*$)")
    contentLst = content.split('\n')
    n=0
    for line in contentLst:
        labelObj = labelPat.search(line)
        globallabelObj = globallabelPat.search(line)
        vectObj  = vectPat.search(line)
        if globallabelObj:
            __VECTORBODY__+="\n$"+globallabelObj.group('label')+" \"GLOBAL (this label may be used by other patterns)\""
        elif labelObj:
            __VECTORBODY__+="\n$"+labelObj.group('label')
        if vectObj:
            micro  = vectObj.group('micro')
            tset   = vectObj.group('tset')
            comm   = vectObj.group('comm')
            for s in __delims__:
                comm=comm.replace(s,' ')
            if complex_type == 0:#simple patterns
                vect = vectObj.group('vect')
            elif complex_type == 1 or complex_type == 2:
                f1 = vectObj.group('field1')
                f2 = vectObj.group('field2')
                f3 = vectObj.group('field3')
                f4 = vectObj.group('field4')
                f5 = vectObj.group('field5')
                f6 = vectObj.group('field6')
                f7 = vectObj.group('field7')
                f8 = vectObj.group('field8')
                f9  = vectObj.group('field9')
                f10 = vectObj.group('field10')
                vect = f1
                for i,bit in enumerate(f2):
                    vect += getDoubleClkChar(f2[i],f3[i])
                for i,bit in enumerate(f4):
                    vect += getDoubleClkChar(f4[i],f5[i])
                vect += f6+f7+f8+f9+f10
            elif complex_type == 3:
                f1 = vectObj.group('field1')
                f2 = vectObj.group('field2')
                f3 = vectObj.group('field3')
                f4 = vectObj.group('field4')
                f5 = vectObj.group('field5')
                f6 = vectObj.group('field6')
                f7 = vectObj.group('field7')
                f8 = vectObj.group('field8')
                f9  = vectObj.group('field9')
                f10 = vectObj.group('field10')
                f11 = vectObj.group('field11')
                f12 = vectObj.group('field12')
                vect = f1
                for i,bit in enumerate(f2):
                    vect += getDoubleClkChar(f2[i],f3[i])
                for i,bit in enumerate(f4):
                    vect += getDoubleClkChar(f4[i],f5[i])
                vect += f6+f7+f8+f9
                for i,bit in enumerate(f10):
                    vect += getDoubleClkChar(f10[i],f11[i])
                vect += f12
            elif complex_type == 4:
                f1 = vectObj.group('field1')
                f2 = vectObj.group('field2')
                f3 = vectObj.group('field3')
                f4 = vectObj.group('field4')
                f5 = vectObj.group('field5')
                f6 = vectObj.group('field6')
                f7 = vectObj.group('field7')
                f8 = vectObj.group('field8')
                vect = f1
                for i,bit in enumerate(f2):
                    vect += getDoubleClkChar(f2[i],f3[i])
                vect += f4+f5+f6+f7+f8
            else:
                print "\n\n### ERROR !!!! Unknown type of complex pattern !!!\n\n"
            vect=translate(vect)
            vect=reOrgVect(vect,complex_type)
            n=n+1
            if len(micro):
                micro = "<"+micro+">"
            __VECTORBODY__+="\n* "+vect+" * TSET"+tset+" SH0; "+micro+"\"# "+str(n)+" "+comm+"\""
        else:
            __UNKNOWN_DATA__ += line+'\n'
    #End for
#End getVectorData()

def makeOutputFile():
    header=__EVHDR__
    header=header+__HDR_COMMENTS__
    header=header+"Pattern "+__PATTERN__+" {\n"
    header=header+"Type Cpm;\n"
    header=header+__CREATION_MSG__
    header=header+__conversion_msg__
    header=header+"\"##################\"\n\"   WARNING!!!  You must manually convert micro-instructions between < and > below\"\n\"##################\"\n\n"
    header=header+__PINLISTHDR__+"\n"
    header=header+"$"+__PATTERN__+"_begin"
    footer="\n$"+__PATTERN__+"_end"
    footer=footer+__DUMMYVECT__+"\n}"
    outfile = open(__PATTERN__+'.evo', "w")
    outfile.write(header+__VECTORBODY__+footer)
    outfile.close()
#End makeOutputFile()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __PATTERN__,__CREATION_MSG__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1 or args[0][-3:]!=".tp":
        err="\nusage: python "+__progfile__+" "+__V580PAT__
        sys.exit(err)
    try:
        infile = file(args[0], 'r')
        content = infile.read()
        infile.close()
    except:
        err="File Error: "+args[0]+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    __PATTERN__=args[0][0:len(args[0])-3]
    localtime = time.asctime(time.localtime(time.time()))
    __CREATION_MSG__ = "\"Pattern generated by: "+__progfile__+" "+__version__+"\"\n\""+__author__+"\"\n\"PATTERN CREATION DATE: "+str(localtime)+"\"\n\n"
    
    getHdrComments(content)
    buildPinlistHeader()
    print '\n\n'
    getVectorData(content)
    makeOutputFile()

    print __complex_warning__

    print __progfile__+" "+__version__
    print __author__
    print __date__
    print "SUCCESS!!! NEW FILE CREATED: "+__PATTERN__+'.evo'+"\n\n"


#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
