import time
localtime = time.asctime(time.localtime(time.time()))
start_time = time.time()
_file_header_=\
"""
#   Script File Name: wvt_fus2dvc.py
#   Author: Roger Logan
#   Version: 1.0
#   Property of Anora, LLC
#   Script Run Date:"""+localtime+"""
#   Description: Converts multiple WaveformTable's to 93k dvc's (Fusion to 93k)
"""
import re
import gzip
import string
import sys
import getopt
import commands
from pprint import pprint as pp
import inspect
def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno

_debug_ = False
_pins_      = [] # list of all pins from adapterboard
_pingroups_ = {} # dict of pingroups and their pins (all elements reduced to pins.. not other pingroups)
_waves_     = {} # all wavetables to be converted and their elements (include default waveformtable, if necessary)

pinPtrn = re.compile("Pin\s*\{\s*Name\s*=\s*(?P<pin>\w+)\s*;")
def getPins(content,fileN):
    global _pins_
    _pins_ = list(set(pinPtrn.findall(content))) # make pins unique (in case more than one adapterboard was passed)
    if not len(_pins_):
        sys.exit("ERROR !!! No pins found in "+fileN+" Exiting ! ...")
#End getPins()

pgPtrn = re.compile("PinGroup\s+(?P<pgname>\w+)\s*\{\s*Group\s*=\s*Expr\s*\{\s*String\s*=\s*\"\s*(?P<pins>.*?)\s*\";\s*\}\s*\}",re.DOTALL)
def getPinGroups(content,fileN):
    global _pingroups_
    groupLst=pgPtrn.findall(content)
    if not len(groupLst):
        sys.exit("ERROR !!! No pingroups found in "+fileN+" Exiting ! ...")
    rawgroups = {}
    for pg,rawpins in groupLst:
        rawgroups[pg]=rawpins
    _pingroups_=dict.fromkeys(rawgroups, '')
    for pg in rawgroups:
        _pingroups_[pg]=[]
        elems = re.sub(r'\s*([\+-])\s*',r',\1',rawgroups[pg].strip()).split(',')
        for n,elem in enumerate(elems):
            elem = elem.strip()
            if not len(elem):continue
            if elem[0]=='-':
                print "\nWARNING !!! Subtraction found in pingroup:",pg,"! You should convert this group by hand !"
                continue
            elif elem[0]=='+':
                _pingroups_[pg].append(elem[1:])
            else:
                _pingroups_[pg].append(elem)
#End getPinGroups()

cellhdrPtrn = re.compile(r'\"\s*(?P<pins>\S+)\s*"\s+(?P<chars>\S+)\s+(?P<cellname>\w+)')
def getWaves(content,fileN):
    global _waves_
    def getDelimContents(string,st_delim='{',sp_delim='}'):
        """Get contents of delimiters even if nested"""
        stack = []
        start,started = 0,False
        itemname=''
        for i, c in enumerate(string):
            if not started and c != st_delim:
                itemname+=c
            elif c == st_delim:
                if not started:
                    start=i
                    started = True
                stack.append(i)
            elif c == sp_delim and stack:
                stack.pop()
            elif not stack: # we must be done
                break
        return itemname.strip(),i,string.strip()[start-1:i] # let's include delims in return
    #End getDelimContents()
    def getAll(objname,string,named=True):
        _string=string
        header=''
        items={}
        while True:
            i = _string.find(objname)
            if i==-1:break
            str2chk = _string[i+len(objname):]
            itemname,stopi,itemcontent = getDelimContents(str2chk)
            if not len(itemname) and named:break
            elif not named:itemname=objname
            items[itemname]=itemcontent
            if not len(header):header=''
            _string=_string[stopi:]
#        print 'header:<'+header+'>'
#        sys.exit()
        return header.strip(),items
    #End getAll()
    wavetop,waves = getAll('WaveformTable',content)
    for wvt in waves:
        celltop,cells = getAll('Cell',waves[wvt])
        for cellhdr in cells:
            cellhdrObj = cellhdrPtrn.search(cellhdr)
            if not cellhdrObj:
                sys.exit("\n\nERROR !!! Unknown syntax in WaveformTable: "+wvt+" ! Exiting ...")
            drive = getAll('Drive',cells[cellhdr],False)
            strobe = getAll('Compare',cells[cellhdr],False)
            if _debug_:
                print '-----------------------------------------------'
                print 'wavename       :',wvt
                print 'wavetop        :',wavetop
                print 'cellhdr        :',cellhdr
                print 'celltop        :',celltop
                print 'cellname       :',cellhdrObj.group('cellname')
                print 'pins           :',cellhdrObj.group('pins')
                print 'chars          :',cellhdrObj.group('chars')
                print 'drive          :',drive
                print 'strbe          :',strobe
                print 'cells[cellhdr] :',cells[cellhdr]
                print '-----------------------------------------------'
            
            
            
            

def main(argv):
    global _debug_
    def usage():
        usgstr = """\
        \n\n\tMake sure each file only contains objects that you need.
                Note 1:Comments will be auto-stripped from each file.
                Note 2: if wavetables in separate files, then concatenate all wavetables to be converted into one file
                    Example: cat ./wavetables/*evo > wavetables.evo
                Note 3: if Default WaveformTable (denoted by double name) is needed, include it in actable.evo.
                        Often, this object is located in cycletbl.evo.
                        The double name is changed to name__name when used in Inherit statements in other WaveformTable's.
                
                Usages: (order doesn't matter - just keep paired items together .. ie: -d device.evo)
                   python """+sys.argv[0]+""" [opt_opt] [req_opt1] arg1 [req_opt2] arg2 [req_opt3] arg3
                Optional Options [opt_opt]:
                    -h, --help                                  show this help message and exit
                    --debug                                     make lots of noise (default is off)
                Required Options [req_optX]:
                    -d device.evo,  --device=device.evo         looking for at least one "Adapterboard" object to get list of all the pins
                    -p pinlist.evo, --pinlist=pinlist.evo       looking for all "PinGroup" objects and their pins
                    -a actable.evo, --actable=actable.evo       looking for all "WaveformTable" objects to be converted
                Examples:
                   python """+sys.argv[0]+""" -h
                   python """+sys.argv[0]+""" -d device.evo -p pinlist.evo -a actable.evo
                   python """+sys.argv[0]+""" --pinlist=pinlist.evo --device=device.evo --actable=actable.evo
                   python """+sys.argv[0]+""" -a actable.evo -p pinlist.evo -d device.evo --debug
        \n\n"""
        print usgstr
        sys.exit(2)
    #End usage()
    def getContents(fileN,strip_comments=True):
        """
        returns contents of file stripped of C type comments (default) or without being stripped
        """
        if strip_comments:# pass file through C compiler to strip comments
            contents = commands.getoutput("sed 's/a/aA/g;s/__/aB/g;s/#/aC/g' "+fileN+" |\
                                           gcc -P -E - | \
                                           sed 's/aC/#/g; s/aB/__/g;s/aA/a/g'");
        else:
            infile = open(fileN)
            contents = infile.read()
            infile.close()
        return contents
    #End getContents()
    try:
        opts, args = getopt.getopt(argv, 'hd:p:a:', ['help', 'device=', 'pinlist=', 'actable=', 'debug'])
        if not opts or len(opts)<3:usage()
    except getopt.GetoptError:usage()
    for opt, arg in opts:
        if opt in ('-h', '--help'):usage()
        elif opt == '--debug':
            _debug_ = True
    for opt, arg in opts:
        if opt in ('-d', '--device'):
            getPins(getContents(arg),arg)       # populate _pins_
        elif opt in ('-p', '--pinlist'):
            getPinGroups(getContents(arg),arg)  # populate _pingroups_
        elif opt in ('-a', '--actable'):
            getWaves(getContents(arg),arg)      # populate _waves_

#End main()

if __name__ == "__main__":
    print _file_header_
    main(sys.argv[1:])
    print "\nScript took",time.time() - start_time, "seconds"

