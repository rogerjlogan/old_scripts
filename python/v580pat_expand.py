import re
import gzip
import string
import sys
import os
from pprint import pprint
import inspect

_debug_ = True

_muxchar_ = '-'
_maskchar_ = 'X'
_maskpins_ = ['REFCLK','DIN_RXN','DIN_RXP','DOUT_TXN','DOUT_TXP','TC1','TC0','RC0','RC1']
_expand_rpts_ = False
_outdir_ = "EvosRaw_notexpanded"

_muxpins_ = {\
    'TD0':'MTD0',\
    'TD1':'MTD1',\
    'TD2':'MTD2',\
    'TD3':'MTD3',\
    'TD4':'MTD4',\
    'TD5':'MTD5',\
    'TD6':'MTD6',\
    'TD7':'MTD7',\
    'TD8':'MTD8',\
    'TD9':'MTD9',\
    'RD0':'MRD0',\
    'RD1':'MRD1',\
    'RD2':'MRD2',\
    'RD3':'MRD3',\
    'RD4':'MRD4',\
    'RD5':'MRD5',\
    'RD6':'MRD6',\
    'RD7':'MRD7',\
    'RD8':'MRD8',\
    'RD9':'MRD9'}

_muxkey_ = {\
    'cc':'LLLL',\
    'cK':'LLLH',\
    'ck':'LLHL',\
    'cC':'LLHH',\
    'Kc':'LHLL',\
    'KK':'LHLH',\
    'Kk':'LHHL',\
    'KC':'LHHH',\
    'kc':'HLLL',\
    'kK':'HLLH',\
    'kk':'HLHL',\
    'kC':'HLHH',\
    'Cc':'HHLL',\
    'CK':'HHLH',\
    'Ck':'HHHL',\
    'CC':'HHHH',\
    'CX':'HHXX',\
    'XC':'XXHH',\
    'cX':'LLXX',\
    'Xc':'XXLL',\
    'kX':'HLXX',\
    'Xk':'XXHL',\
    'KX':'LHXX',\
    'XK':'XXLH',\
    'LL':'L-L-',\
    'LH':'L-H-',\
    'HL':'H-L-',\
    'HH':'H-H-',\
    '00':'XXXs',\
    '01':'XXXr',\
    '10':'XXXR',\
    '11':'XXXS',\
    '0X':'XXX2',\
    '1X':'XXX3',\
    'X0':'XXX0',\
    'X1':'XXX1',\
    'XX':'XXXX',\
    'XL':'XXL-',\
    'LX':'L-XX',\
    'XH':'XXH-',\
    'HX':'H-XX',\
    '--':'----'}

def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno
#End lineno()

_EVHDR_ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
_RD_ERROR_ = "Make sure you have permissions to READ files in this directory."
_WR_ERROR_ = "Make sure you have permissions to WRITE files in this directory."

rptPtrn = re.compile(r'\bREPEAT\b\s+(?P<rpt>\d+)\s*')
def parsevect(sh,data,tset,instr,comm):
    rptObj = rptPtrn.search(instr)
    rpt = 1 if not rptObj else int(rptObj.group('rpt'))
    if rpt>1:instr=''
    if len(instr):instr='<'+instr+'>'
    #mask designated masked pins
    data = ''.join([c if _sighdrs_[sh][i] not in _maskpins_ else _maskchar_ for i,c in enumerate(data)])
    data4x = [data for i in range(4)]
    if _debug_:pprint(data)
    for pin in _muxpins_:
        i1=_sighdrs_[sh].index(pin)
        i2=_sighdrs_[sh].index(_muxpins_[pin])
        dd=data[i1]+data[i2]
        for i in range(4):
            thisdata = bytearray(data4x[i])
            thisdata[i1]=_muxkey_[dd][i]
            thisdata[i2]=_muxchar_
            if i<3:
                thisdata=re.sub(r'[01]','X',thisdata)
            data4x[i]=str(thisdata)
    if _debug_:pprint(data4x)
    _4lines=''
    for i in range(4):
        _4lines+='* '+data4x[i]+' * '+tset+'; '+instr+'\"'+str(i+1)+' of 4\"'+comm+'\n'
    ostr=''
    if rpt>1:
        if _expand_rpts_ :
            for i in range(rpt):
                ostr+=_4lines[:-1]+' \"REPEAT '+str(i+1)+'/'+str(rpt)+'\"\n'
        else:
            ostr+=_4lines[:-1]+' \"<REPEAT '+str(rpt)+'>\"\n'
    else:
        ostr=_4lines
    return ostr
#End parsevect()

_pats_created_=[]
patSHPtrn = re.compile(r'^Default SignalHeader (?P<sighdr>\w+);')
vectPtrn = re.compile(r'\*\s*(?P<data>.*?)\s*\*\s*(?P<tset>\w+?)?\s*;\s*(?:\<(?P<instr>.*?)\>?)?\s*(?P<comm>\".*\")?\s*$')
def main(inpathfn):
    in_path, fn = os.path.split(inpathfn)
    patname = os.path.splitext(fn)[0]
    print "Processing",fn,"..."
    global _pats_created_
    if not os.path.exists(_outdir_):
        try:
            os.makedirs(_outdir_)    
        except:exit("Directory WRITE/CREATE Error !!!: "+_outdir_+"\n"+_WR_ERROR_+"\nLine: "+str(lineno())+"\n\n")
    try:
        pathfn = os.path.join(_outdir_,patname+'.evo')
        patfile = open(pathfn, "w")
    except:exit("Directory WRITE/CREATE Error !!!: "+patname+".evo\n"+_WR_ERROR_+"\nLine: "+str(lineno())+"\n\n")
    _pats_created_.append(pathfn)
    prev_vect=''
    with open(inpathfn) as FileObj:
        sh_found=False
        for line in FileObj:
            if not sh_found:
                patSHObj = patSHPtrn.search(line)
                if patSHObj:
                    sh_found=True
                    sh = patSHObj.group('sighdr')
                    if sh not in _sighdrs_:
                        sys.exit("\n\nERROR !!! Unknown SignalHeader \'"+sh+"\' found in pattern \'"+fn+'\'\n\n')
                patfile.write(line)
            else:
                vectObj = vectPtrn.search(line)
                if vectObj:
                    data = vectObj.group('data')
                    tset = vectObj.group('tset')
                    tset = '' if tset==None else tset.strip()
                    instr = vectObj.group('instr')
                    instr = '' if instr==None else instr.strip()
                    comm = vectObj.group('comm')
                    comm = '' if comm==None else comm.strip()
                    patfile.write(parsevect(sh,data,tset,instr,comm))
                else:
                    patfile.write(line)
        patfile.close()
    return

sighdrPtrn = re.compile(r'SignalHeader\s+(\w+)\s*\{\s*Signals\s*\{\s*(?P<pins>.*?)\s*\}',re.DOTALL)
if __name__ == "__main__":
    if len(sys.argv) <3:
        sys.exit("Usage : python " + sys.argv[0] + "cycletbl.evo <path to pats>/*evos")
    cycfile = file(sys.argv[1], 'r')
    cyctbl = cycfile.read()
    cycfile.close()
    sighdrs=sighdrPtrn.findall(cyctbl)
    _sighdrs_ = {}
    for sh,pins in sighdrs:
        pins=re.sub(r'\s+',',',pins.replace('%',''))
        _sighdrs_[sh] = map(lambda p: p.strip(), pins.split(','))
    for pathfn in sys.argv[2:]:
        main(pathfn)
    print "\nSUCCESS !!! Files created:\n\n    "+'\n    '.join(_pats_created_)+"\n\n"
    print "WARNING !!! \""+_outdir_+"\" need lots of hand edits due the following:"
    print "     - Micro-instructions were preserved between \'<\' and \'>\' but not converted."
    print "     - Subroutines may exist as vectors below <HALT> micro-instruction, but must be placed where CALL exits."
    print "     - Patterns over 4k vectors will need to be modified as Cpm calling Dpm. pushCPMintoDPM.py may be an option.\n\n"

