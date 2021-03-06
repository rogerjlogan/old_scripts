#!/usr/local/bin/python2.6-2.6.4

import time
localtime = time.asctime(time.localtime(time.time()))
start_time = time.time()
_logfile_="log.txt"
_padchar_ = '-'
_file_header_=\
    """
    #   Script File Name: evo2avc.py
    #   Author: Roger Logan
    #   Version: 3.0
    #   Property of Anora, LLC
    #   Script Run Date:"""+localtime+"""
    #   Description: Converts evo patterns to avc's (Fusion to 93k)
    #                based on sighdrs_ports.txt that must be generated by hand
    #                Currently only supports DPM pattterns...
    #                (or CPM's with just RPT micro-instructions ONLY)
    #   Output: *.avc, """+_logfile_

__RD_ERROR__ = "Make sure you have permissions to READ files in this directory."
__WR_ERROR__ = "Make sure you have permissions to WRITE files in this directory."

_debug_ = False

_absmaxlen_=0
_fuschars_=''
_93k_chars_=''
_xp_msg_=''
_mp_msg_=''
_noports_msg_=''
_nocharmap_msg_=''
_chars_used_={}
_files_converted_ = {}

import re
import gzip
import string
import sys
from string import maketrans
from string import whitespace as ws

def translate(vectorStr):
    """
    requirement:from string import maketrans
    This will switch out characters from Fusion convention to 93K convention
    """
    intab = _fuschars_
    outtab = _93k_chars_
    trantab = maketrans(intab,outtab)
    vectorStr = vectorStr.translate(trantab,ws);#translate characters and remove ws
    return vectorStr
def mkPinHdr(pinlist,ignore_pins):
    global _absmaxlen_
    hdr_offset = "#         "
    padpinstr = hdr_offset
    maxlen=len(max(pinlist,key=len))
    _absmaxlen_=max(_absmaxlen_,maxlen)
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
def getPins(sighdr_content):
    global _evo_sh_,_avc_sh_,_ports_,_out_sh_
    global _extra_pins_,_missing_pins_
    global _xp_msg_,_mp_msg_,_noports_msg_,_nocharmap_msg_
    global _fuschars_,_93k_chars_,_chars_used_
    evoPat = re.compile(r'EVO_SIG_HDR\s*:\s*(?P<evo_sh>.*?)\s*;',re.DOTALL)
    avcPat = re.compile(r'AVC_SIG_HDR\s*:\s*(?P<avc_sh>.*?)\s*;',re.DOTALL)
    chrPat = re.compile(r'CHAR_MAP\s*:\s*(?P<char_map>.*?)\s*;',re.DOTALL)
    sighdr_content = re.sub(r'\#(.*?)\n','',sighdr_content)
    evoObj = evoPat.search(sighdr_content)
    avcObj = avcPat.search(sighdr_content)
    chrObj = chrPat.search(sighdr_content)
    if not evoObj:
        sys.exit("ERROR !!! EVO_SIG_HDR not found! Make sure to delimit pins with ';' Exiting ...")
    if not avcObj:
        sys.exit("ERROR !!! AVC_SIG_HDR not found! Make sure to delimit pins with ';' Exiting ...")
    _evo_sh_ = evoObj.group('evo_sh').split()
    _avc_sh_ = avcObj.group('avc_sh').split()



#
#    _extra_pins_ = list(set(_evo_sh_)-set(_avc_sh_))#in pattern to be converted but not in desired avc signal header
#    _missing_pins_ = list(set(_avc_sh_)-set(_evo_sh_))#in desired avc signal header but not in pattern to be converted
#    if len(_extra_pins_):
#        _xp_msg_ = "\n# WARNING ! Found Extra pins   (unwanted data in patterns ???)\n# Ignoring these pins from EVO_SIG_HDR and their data\n#\t"+' '.join(_extra_pins_)+'\n'
#        print _xp_msg_
#    if len(_missing_pins_):
#        _mp_msg_ = "\n# WARNING ! Found Missing pins (no data is availabe for these pins in patterns)\n# Padding these pins with '"+_padchar_+"' to match AVC_SIG_HDR"
#        _mp_msg_ += "\n# These will be denoted with '*' at top of column\n#\t"+' '.join(_missing_pins_)+'\n\n'
#        print _mp_msg_
#    _out_sh_ = [x for x in _avc_sh_ if x not in _extra_pins_]# new sigheader preserving order (padding missing pins and deleting extra pins))
#    _chars_used_ = dict.fromkeys(_out_sh_, '')
#    #prtObj is list of tuple pairs but each pair is backwards and each element of those tuples could contain ws
#    #so we are...
#    #      (1) reversing pair
#    #      (2) splitting the now 2nd element on comma and stripping each of those pins of ws
#    #      (3) repacking pins into comma separated string
#    #      (4) return a dictionary
##        _ports_ = dict([[port.strip(),','.join([p.strip() for p in pinlist.split(',')])] for pinlist,port in prtObj])
#        _ports_['_allpins_'] = ','.join(_out_sh_)
#    if not chrObj:
#        _nocharmap_msg_="\n# Warning !!! No CHAR_MAP found.  Characters will not be changed!\n\n"
#        print _nocharmap_msg_
#    else:
#        for pair in chrObj.group('char_map').split(','):
#            _fuschars_ += pair[1]
#            _93k_chars_ += pair[2]
    return
vectPat = re.compile(r'^\s*\*\s*(?P<vector>.*?)\s*\*\s*(?P<sh>\w+?)?\s*(?P<wft>\w+?)?\s*;\s*(?:"(?:.*?)")?\s*(?P<uInst>\<.*?\>)?')
repPat = re.compile(r'\<\s*RPT\s+(?P<count>\d+)\s*\>')
def main(fileN,port,sighdr,inds=None):
    global _v_cnt_,_c_cnt_,_chars_used_,_files_converted_
    newfileN = fileN.replace('.evo','.avc')
    print '\tCreating '+newfileN
    if fileN not in _files_converted_:
        _files_converted_[fileN]=newfileN
    else:
        _files_converted_[fileN]=_files_converted_[fileN]+','+newfileN
    outFile = myOpen(newfileN,'w')
    outFile.write(_file_header_)
    outFile.write('\n\nFORMAT '+' '.join(sighdr)+';\n\n')
    if len(_xp_msg_):outFile.write(_xp_msg_)
    if len(_mp_msg_):outFile.write(_mp_msg_)
    if len(_nocharmap_msg_):outFile.write(_nocharmap_msg_)
    outFile.write(mkPinHdr(sighdr,_extra_pins_))
    _v_cnt_=0
    _c_cnt_=0
    for line in myOpen(fileN):
        repeat=1
        vecObj = vectPat.search(line)
        if vecObj:
            _v_cnt_+=1
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
                    sys.exit("ERROR !!! Unknown micro-instruction. Only RPT is translated at this time. Exiting ...")
            previous_cycle=_c_cnt_
            _c_cnt_+=repeat
            orig_vect = vecObj.group('vector')
            if len(_evo_sh_) != len(orig_vect):
                print "len(_evo_sh_) =",len(_evo_sh_)
                print "orig_vect     =",orig_vect
                print "len(orig_vect)   =",len(orig_vect)
                sys.exit("ERROR !!! Length of EVO_SIG_HDR doesn't match length of orig vector in pattern. Exiting ...")
            vectdata = translate(orig_vect)
            dictdata = dict(zip(_evo_sh_,list(vectdata)))
            #build new vector - pad wanted pins with 'X' and ignore unwanted data
            s=''
            for pin in sighdr:
                if pin in dictdata:
                    s+=dictdata[pin]
                    if dictdata[pin] not in _chars_used_[pin]:
                        _chars_used_[pin] = _chars_used_[pin]+dictdata[pin]
                else:
                    s+='X'
                    if 'X' not in _chars_used_[pin]:
                        _chars_used_[pin] = _chars_used_[pin]+'X'
            new_vect='R'+str(repeat).ljust(4)
            if len(new_vect)>5:new_vect+='\n     '
            new_vect+=" std "+''.join(s)
            if _c_cnt_-previous_cycle==1:
                new_vect+=' %'+str(_c_cnt_)+';\n'
            else:
                new_vect+=' %'+str(previous_cycle+1)+'-'+str(_c_cnt_)+';\n'
            outFile.write(new_vect)
    outFile.close()
    return

if __name__ == "__main__":
    print _file_header_
    main(sys.argv[1:])
    print "\nScript took",time.time() - start_time, "seconds"

#--------------------------------------------------------------------------------------------------------
# EOF
#--------------------------------------------------------------------------------------------------------





















#    if len(sys.argv) <3:
#        if len(sys.argv) <2 or sys.argv[1] != '-h':
#            print "\nUsage: [python] "+sys.argv[0]+" sighdrs_ports.txt *evo[.gz]"
#            print   "       [python] "+sys.argv[0]+" -m sighdrs_ports.txt *evo[.gz]"
#            print   "       [python] "+sys.argv[0]+" -h\n"
#        else:
#            if sys.argv[1] == '-h':
#                print _file_header_+_requirements_
#        sys.exit()
#    else:
#        print _file_header_
#    if sys.argv[1] == '-m':
#        _multiport_=True
#        arg1 = sys.argv[2]
#        args2plus = sys.argv[3:]
#        n=3
#    else:
#        _multiport_=False
#        arg1 = sys.argv[1]
#        args2plus = sys.argv[2:]
#        n=2
#    try:
#        infile = file(arg1, 'r')
#        sighdr_content = infile.read()
#    except IOError:
#       print "\nFile READ Error !!!: "+arg1+"\n"+__RD_ERROR__+"\n"
#    finally:
#        infile.close()
#    getPins(sighdr_content)
#    inds=[]
#    for ii,x in enumerate(args2plus):
#        try:
#            inds.append(int(x))
#        except ValueError:
#            break
#    
#    for fileN in sys.argv[ii+n:]:
#        print "Processing "+ fileN
#        for port,sighdr in _ports_.items():
#            main(fileN,port,sighdr.split(','),inds)
#        print '\tSuccess ! vectors='+str(_v_cnt_)+' cycles='+str(_c_cnt_)+'\n'
#    try:
#        print "\nCreating",_logfile_
#        logFile=open(_logfile_,'w')
#        if len(_nocharmap_msg_):
#            logFile.write(_nocharmap_msg_)
#        else:
#            logFile.write("\nCharacters that were converted (fusion:93k)\n")
#        for i,f in enumerate(_fuschars_):
#            logFile.write('\t'+f+':'+_93k_chars_[i]+'\n')
#        logFile.write("\nComplete list of characters used in all avc files generated\n")
#        for pin in _chars_used_:
#            logFile.write(pin.ljust(_absmaxlen_+2)+': '+_chars_used_[pin]+'\n')
#        logFile.write("\nList of patterns converted\n\n")
#        for f in _files_converted_:
#            logFile.write(f+' => '+_files_converted_[f]+'\n')
#    except IOError:
#        print "\nFile WRITE Error !!!: "+_logfile_+"\n"+__WR_ERROR__+"\n"
#    finally:
#        logFile.close()
#    print "\nScript took",time.time() - start_time, "seconds"
