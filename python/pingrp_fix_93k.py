import re
import array
import gzip
import string
import sys
import pprint
import os

__verbose__ = True

pinPat = re.compile(r'DFPN(?:.*)\((\w+)\)(?:.*)\n')
pgrpPat = re.compile(r'DFGP\s+(?P<mode>\w+),\((?P<pins>.*?)\),\((?P<name>\w+)\)\s*\n')
egrpPat = re.compile(r'DFGE\s+(?P<mode>\w+),\"(?P<expr>.*?)\",\((?P<name>\w+)\)')

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default
    def __getitem__(self, key):
        if not self.has_key(key):
            self[key] = self.default()
        return dict.__getitem__(self, key)
#End Ddict()

def containsAny(str, set):
    """Check whether 'str' contains ANY of the chars in 'set'"""
    return 1 in [c in str for c in set]

def containsAll(str, set):
    """Check whether 'str' contains ALL of the chars in 'set'"""
    return 0 not in [c in str for c in set]

if __name__ == "__main__":
    if len(sys.argv[1:]) != 1:
        print "Usage : python "+sys.argv[0]+" <93k_pinconfig_file>"
        sys.exit()
    f = open(sys.argv[1],'r')
    lines = f.readlines()
    f.close()
    pins=pinPat.findall(''.join(lines))
    if not pins:
        print "ERROR: No digital pins found !!!"
        sys.exit()
    pingroups = Ddict(dict)
    for line in lines:#first loop to get pin based groups
        pgrpObj=pgrpPat.search(line)
        if pgrpObj:
            name = pgrpObj.group('name')
            mode = pgrpObj.group('mode')
            if not containsAny(mode,('I','O','IO')):
                print "Unknown mode! Exiting"
                print "group name:",name
                print "mode      :",mode
                sys.exit()
            rawpins = pgrpObj.group('pins')
            pinlist = rawpins.split(',')
            for pin in pinlist:
                if pin not in pins:
                    print "ERRRO !!! Unkown pin element ! Exiting..."
                    print "group name:",name
                    print "elem      :",pin
                    sys.exit()
            if name in pingroups.keys():
                if mode in pingroups[name].keys():
                    print "\n\nWARNING !!!! Duplicate pin group found !"
                    if __verbose__:
                        print "group name:",name
                        print "mode      :",mode
            pingroups[name][mode] = pinlist
    #End for
    allpingroups = pingroups
    ostr=''
    for line in lines:#this loop is for analyzing and consolidating expression based groups
        newline = line
        egrpObj=egrpPat.search(line)
        if egrpObj:
            name = egrpObj.group('name')
            mode = egrpObj.group('mode')
            expr = egrpObj.group('expr')
            elems = re.findall(r"[\w']+", expr)
            if name in allpingroups.keys():
                if mode in allpingroups[name].keys():
                    print "\n\nWARNING !!!! Duplicate pin group found ! Updating."
                    if __verbose__:
                        print "group name:",name
                        print "mode      :",mode
            allpingroups[name][mode] = elems
            found = False
            for elem in elems:
                if elem in allpingroups.keys():
                    if mode == 'IO' or mode in allpingroups[elem].keys():
                        found = True
                        break
                else:#not a pingroup
                    if elem not in pins:
                        print "ERRRO !!! Unkown pin element ! Exiting..."
                        print "group name:",name
                        print "elem      :",elem
                        sys.exit()
            if not found and not '-' in expr:
                #all elements are pins and extra check for subtraction which would mean there is a group expression
                if mode == 'IO':
                    newline = "DFGP I,("+','.join(elems)+"),("+name+")\n"
                    newline += "DFGP O,("+','.join(elems)+"),("+name+")\n"
                else:
                    newline = "DFGP "+mode+",("+','.join(elems)+"),("+name+")\n"
            
        ostr += newline
    fn = os.path.splitext(sys.argv[1])[0]
    ext = os.path.splitext(sys.argv[1])[1]
    f = open(fn+'_new'+ext,'w')
    f.write(ostr)
    f.close()
