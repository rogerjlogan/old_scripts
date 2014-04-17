import time
localtime = time.asctime(time.localtime(time.time()))

__fuschars__  = "LH01" #L,H = drives  0,1 = strobes
__93k_chars__ = "01LH" #0,1 = drives  L,H = strobes

_file_header_ = \
"""
#   Script File Name: evo2avc.py
#   Author: Roger Logan
#   Version: 1.0
#   Property of Anora, LLC
#   Script Run Date:"""+localtime+"""
#   Description: Converts evo patterns to avc (Fusion to 93k)
#                based on signalheaders.txt that must be generated by hand
#       L,H changed to 0,1 for drives
#       0,1 changed to H,L for strobes
"""
_requirements_ = \
"""
#   Required file:signalheaders.txt
#       This file should have EVO_SIG_HDR and AVC_SIG_HDR defined:
#         Example:
#           EVO_SIG_HDR:TEST RST_N SSPO TCK;
#           AVC_SIG_HDR:TEST RST_N SSPO TDO;
#       Note: Pins should be space separated and delimited by ';'
#             EVO_SIG_HDR must match in length with evos to be converted
#             If a pin is in EVO_SIG_HDR but not in AVC_SIG_HDR, then it will be DELETED (example TCK).
#             If a pin is in AVC_SIG_HDR but not in EVO_SIG_HDR, then is will be PADDED with 'X' (example TDO)
#             Padded pins will be marked with '*' at top of column
#   Currently only supports DPM pattterns (or CPM's with just RPT micro-instructions ONLY)

"""
import re
import gzip
import string
import sys
from string import maketrans
from string import whitespace as ws

__RD_ERROR__ = "Make sure you have permissions to READ files in this directory."
__WR_ERROR__ = "Make sure you have permissions to WRITE files in this directory."

def translate(vectorStr):
    """
    requirement:from string import maketrans
    This will switch out characters from Fusion convention to 93K convention
    """
    intab = __fuschars__
    outtab = __93k_chars__
    trantab = maketrans(intab,outtab)
    vectorStr = vectorStr.translate(trantab,ws);#translate characters and remove ws
    return vectorStr
#End translate()

def getheader(pinlist,ignore_pins):
    hdr_offset = "#         "
    padpinstr = hdr_offset
    maxlen=len(max(pinlist,key=len))
    padpins=[]
    for pin in pinlist:
        if pin not in ignore_pins:
            padpins.append(pin.ljust(maxlen))
        if pin in _missing_pins_:
            padpinstr+='*'
        else:
            padpinstr+=' '
    padpinstr+='\n'
    hdr = []
    for c in range(1,maxlen+1):
        row = hdr_offset
        for p in padpins:
            row += p[c-1]
        hdr.append(row)
    return padpinstr+"\n".join(hdr)+'\n'+padpinstr

def myOpen(fileN, mode="r"):
    if fileN.endswith('.gz'):
        return gzip.open(fileN,mode)
    return open(fileN,mode)

evoPat = re.compile(r'EVO_SIG_HDR\s*:\s*(?P<evo_sh>.*?)\s*;',re.DOTALL)
avcPat = re.compile(r'AVC_SIG_HDR\s*:\s*(?P<avc_sh>.*?)\s*;',re.DOTALL)
def getPins(sighdr_content):
    evoObj = evoPat.search(sighdr_content)
    avcObj = avcPat.search(sighdr_content)
    if not evoObj:
        sys.exit("ERROR !!! EVO_SIG_HDR not found! Make sure to delimit pins with ';' Exiting ...")
    if not avcObj:
        sys.exit("ERROR !!! AVC_SIG_HDR not found! Make sure to delimit pins with ';' Exiting ...")
    global _evo_sh_,_avc_sh_,_extra_pins_,_missing_pins_,_out_sh_,_xp_found_,_xp_msg_,_mp_found_,_mp_msg_
    _evo_sh_ = [x.upper() for x in evoObj.group('evo_sh').split()]#force uppercase
    _avc_sh_ = [x.upper() for x in avcObj.group('avc_sh').split()]#force uppercase
    _extra_pins_ = list(set(_evo_sh_)-set(_avc_sh_))#in pattern to be converted but not in desired avc signal header
    _missing_pins_ = list(set(_avc_sh_)-set(_evo_sh_))#in desired avc signal header but not in pattern to be converted
    if len(_extra_pins_):
        _xp_found_=True
        _xp_msg_ = "\n# WARNING ! Found Extra pins   (unwanted data in patterns ???)\n# Ignoring these pins from EVO_SIG_HDR and their data\n#\t"+' '.join(_extra_pins_)+'\n'
        print _xp_msg_
    if len(_missing_pins_):
        _mp_found_=True
        _mp_msg_ = "\n# WARNING ! Found Missing pins (no data is availabe for these pins in patterns)\n# Padding these pins with 'X' to match AVC_SIG_HDR"
        _mp_msg_ += "\n# These will be denoted with '*' at top of column\n#\t"+' '.join(_missing_pins_)+'\n\n'
        print _mp_msg_
    _out_sh_ = [x for x in _avc_sh_ if x not in _extra_pins_]# new sigheader preserving order (padding missing pins and deleting extra pins))
    return
#End getPins()

vectPat = re.compile(r'^\s*\*\s*(?P<vector>.*?)\s*\*\s*(?P<sh>\w+?)?\s*(?P<wft>\w+?)?\s*;\s*(?P<uInst>\<.*?\>)?')
repPat = re.compile(r'\<\s*RPT\s+(?P<count>\d+)\s*\>')
_xp_found_=False
_mp_found_=False
def main(fileN, inds=None):
    print "processing "+ fileN
    outFile = myOpen(fileN.replace(".evo",".avc"),'w')
    outFile.write(_file_header_)
    outFile.write('\nFORMAT '+' '.join(_out_sh_)+';\n\n')
    if _xp_found_:
        outFile.write(_xp_msg_)
    if _mp_found_:
        outFile.write(_mp_msg_)
    outFile.write(getheader(_out_sh_,_extra_pins_))
    cycle_count=0
    for vector_count,line in enumerate(myOpen(fileN)):
        repeat=1
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
                else:
                    sys.exit("ERROR !!! Unknow micro-instruction. Only RPT is translated at this time. Exiting ...")
            previous_cycle=cycle_count
            cycle_count+=repeat
            orig_vect = vecObj.group('vector')
            if len(_evo_sh_) != len(orig_vect):
                print "len(_evo_sh_) =",len(_evo_sh_)
                print "orig_vect     =",orig_vect
                print "len(orig_vect)   =",len(orig_vect)
                sys.exit("ERROR !!! Length of EVO_SIG_HDR doesn't match length of orig vector in pattern. Exiting ...")
            vectdata = translate(orig_vect)
            dictdata = dict(zip(_evo_sh_,list(vectdata)))
            #pad wanted pins with 'X' and ignore unwanted data
            s=''
            for pin in _out_sh_:
                if pin in dictdata:
                    s+=dictdata[pin]
                else:
                    s+='X'
            new_vect='R'+str(repeat).ljust(4)
            if len(new_vect)>5:new_vect+='\n     '
            new_vect+=" std "+''.join(s)
            if cycle_count-previous_cycle==1:
                new_vect+=' %'+str(cycle_count)+';\n'
            else:
                new_vect+=' %'+str(previous_cycle+1)+'-'+str(cycle_count)+';\n'
            outFile.write(new_vect)
    outFile.close()
    return
#End main()

if __name__ == "__main__":
    if len(sys.argv) <3:
        print _file_header_+_requirements_
        print "\nUsage : python "+sys.argv[0]+" signalheaders.txt *evo(.gz)\n"
        sys.exit()
    else:
        print _file_header_
    try:
        infile = file(sys.argv[1], 'r')
        sighdr_content = infile.read()
        infile.close()
    except:
        exit("\nFile READ Error !!!: "+sys.argv[1]+"\n"+__RD_ERROR__+"\n")
    getPins(sighdr_content)
    inds=[]
    for ii,x in enumerate(sys.argv[2:]):
        try:
            inds.append(int(x))
        except ValueError:
            break
    
    for fileN in sys.argv[ii+2:]:
        main(fileN, inds)
