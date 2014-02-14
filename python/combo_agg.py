import re
import gzip
import string
import sys

same = False

pinPat = re.compile(r'^\s*PINS\s+(?P<pins>.*)\s*$')
wsPat = re.compile(r'\s',re.DOTALL)
_pinlist_ = {}
_combos_ = {}
ofilename = 'big5_8ns.cmb'

def main(fileN):
    global _pinlist_,_combos_
    print "processing "+ fileN
    lastpinlist=[]
    for line in open(fileN):
        thisline = line.strip()
        pinObj = pinPat.search(line)
        if '#' in line or 'DDC' in line or len(thisline)<2:
            continue
        elif pinObj:
            lastpinlist=[]
            for pin in pinObj.group('pins').split():
                lastpinlist.append(pin.strip())
        else:
            thiscombo=' '.join(re.sub(wsPat,'',line))
            for pin in lastpinlist:
                if pin not in _combos_:
                    _combos_[pin]=[]
                if thiscombo not in _combos_[pin]:
                    _combos_[pin].append(thiscombo)
    return

if __name__ == "__main__":
    if len(sys.argv) <2:
        print "Usage : python " + sys.argv[0] + " <files>"
        sys.exit()
    for fileN in sys.argv[1:]:
        main(fileN)
    ofile=open(ofilename,'w')
    for pin in _combos_:
        ofile.write('\n\nPIN '+pin+'\n')
        ofile.write('\n'.join(_combos_[pin]))
    ofile.close()
    print "\n\nSUCCESS !",ofilename,"created !"
