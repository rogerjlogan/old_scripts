import re
import gzip
import string
import sys

pincombos={}
fmtPtrn = re.compile(r'^\s*FORMAT\s+(?P<pins>.*?)\s*(?P<semicolon>;)?\s*$')
vecPtrn = re.compile(r'^\s*R(?P<rpt>\d+?)\s*(?P<wvt>\w+?)\s+(?P<vec>\w+?)\s+(?:%.*?)?\s*;\s*$')
def main(fileN):
    print "processing "+ fileN
    prev_vect=''
    with open(fileN) as FileObj:
        isformat=False
        formatfound=False
        for line in FileObj:
            if not isformat and not formatfound:
                if  'FORMAT' in line:
                    fmtObj = fmtPtrn.search(line)
                    for pin in fmtObj.group(1).split():
                        if pin not in pincombos:
                            continue
                    if fmtObj.group(2) != None:
                        continue
                else:
                    print line
            vecObj = vecPtrn.search(line)
            if vecObj:
                rpt = vecObj.group('rpt')
                wvt = vecObj.group('wvt')
                com = vecObj.group('com')
                sys.exit()




    return

if __name__ == "__main__":
    if len(sys.argv) <2:
        print "Usage : python " + sys.argv[0] + " <files>"
        sys.exit()
    for fileN in sys.argv[1:]:
        main(fileN)



